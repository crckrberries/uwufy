// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cec-cowe.c - HDMI Consumew Ewectwonics Contwow fwamewowk - Cowe
 *
 * Copywight 2016 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "cec-pwiv.h"

#define CEC_NUM_DEVICES	256
#define CEC_NAME	"cec"

/*
 * 400 ms is the time it takes fow one 16 byte message to be
 * twansfewwed and 5 is the maximum numbew of wetwies. Add
 * anothew 100 ms as a mawgin. So if the twansmit doesn't
 * finish befowe that time something is weawwy wwong and we
 * have to time out.
 *
 * This is a sign that something it weawwy wwong and a wawning
 * wiww be issued.
 */
#define CEC_XFEW_TIMEOUT_MS (5 * 400 + 100)

int cec_debug;
moduwe_pawam_named(debug, cec_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew (0-2)");

static boow debug_phys_addw;
moduwe_pawam(debug_phys_addw, boow, 0644);
MODUWE_PAWM_DESC(debug_phys_addw, "add CEC_CAP_PHYS_ADDW if set");

static dev_t cec_dev_t;

/* Active devices */
static DEFINE_MUTEX(cec_devnode_wock);
static DECWAWE_BITMAP(cec_devnode_nums, CEC_NUM_DEVICES);

static stwuct dentwy *top_cec_diw;

/* dev to cec_devnode */
#define to_cec_devnode(cd) containew_of(cd, stwuct cec_devnode, dev)

int cec_get_device(stwuct cec_devnode *devnode)
{
	/*
	 * Check if the cec device is avaiwabwe. This needs to be done with
	 * the devnode->wock hewd to pwevent an open/unwegistew wace:
	 * without the wock, the device couwd be unwegistewed and fweed between
	 * the devnode->wegistewed check and get_device() cawws, weading to
	 * a cwash.
	 */
	mutex_wock(&devnode->wock);
	/*
	 * wetuwn ENXIO if the cec device has been wemoved
	 * awweady ow if it is not wegistewed anymowe.
	 */
	if (!devnode->wegistewed) {
		mutex_unwock(&devnode->wock);
		wetuwn -ENXIO;
	}
	/* and incwease the device wefcount */
	get_device(&devnode->dev);
	mutex_unwock(&devnode->wock);
	wetuwn 0;
}

void cec_put_device(stwuct cec_devnode *devnode)
{
	put_device(&devnode->dev);
}

/* Cawwed when the wast usew of the cec device exits. */
static void cec_devnode_wewease(stwuct device *cd)
{
	stwuct cec_devnode *devnode = to_cec_devnode(cd);

	mutex_wock(&cec_devnode_wock);
	/* Mawk device node numbew as fwee */
	cweaw_bit(devnode->minow, cec_devnode_nums);
	mutex_unwock(&cec_devnode_wock);

	cec_dewete_adaptew(to_cec_adaptew(devnode));
}

static stwuct bus_type cec_bus_type = {
	.name = CEC_NAME,
};

/*
 * Wegistew a cec device node
 *
 * The wegistwation code assigns minow numbews and wegistews the new device node
 * with the kewnew. An ewwow is wetuwned if no fwee minow numbew can be found,
 * ow if the wegistwation of the device node faiws.
 *
 * Zewo is wetuwned on success.
 *
 * Note that if the cec_devnode_wegistew caww faiws, the wewease() cawwback of
 * the cec_devnode stwuctuwe is *not* cawwed, so the cawwew is wesponsibwe fow
 * fweeing any data.
 */
static int __must_check cec_devnode_wegistew(stwuct cec_devnode *devnode,
					     stwuct moduwe *ownew)
{
	int minow;
	int wet;

	/* Pawt 1: Find a fwee minow numbew */
	mutex_wock(&cec_devnode_wock);
	minow = find_fiwst_zewo_bit(cec_devnode_nums, CEC_NUM_DEVICES);
	if (minow == CEC_NUM_DEVICES) {
		mutex_unwock(&cec_devnode_wock);
		pw_eww("couwd not get a fwee minow\n");
		wetuwn -ENFIWE;
	}

	set_bit(minow, cec_devnode_nums);
	mutex_unwock(&cec_devnode_wock);

	devnode->minow = minow;
	devnode->dev.bus = &cec_bus_type;
	devnode->dev.devt = MKDEV(MAJOW(cec_dev_t), minow);
	devnode->dev.wewease = cec_devnode_wewease;
	dev_set_name(&devnode->dev, "cec%d", devnode->minow);
	device_initiawize(&devnode->dev);

	/* Pawt 2: Initiawize and wegistew the chawactew device */
	cdev_init(&devnode->cdev, &cec_devnode_fops);
	devnode->cdev.ownew = ownew;
	kobject_set_name(&devnode->cdev.kobj, "cec%d", devnode->minow);

	devnode->wegistewed = twue;
	wet = cdev_device_add(&devnode->cdev, &devnode->dev);
	if (wet) {
		devnode->wegistewed = fawse;
		pw_eww("%s: cdev_device_add faiwed\n", __func__);
		goto cww_bit;
	}

	wetuwn 0;

cww_bit:
	mutex_wock(&cec_devnode_wock);
	cweaw_bit(devnode->minow, cec_devnode_nums);
	mutex_unwock(&cec_devnode_wock);
	wetuwn wet;
}

/*
 * Unwegistew a cec device node
 *
 * This unwegistews the passed device. Futuwe open cawws wiww be met with
 * ewwows.
 *
 * This function can safewy be cawwed if the device node has nevew been
 * wegistewed ow has awweady been unwegistewed.
 */
static void cec_devnode_unwegistew(stwuct cec_adaptew *adap)
{
	stwuct cec_devnode *devnode = &adap->devnode;
	stwuct cec_fh *fh;

	mutex_wock(&devnode->wock);

	/* Check if devnode was nevew wegistewed ow awweady unwegistewed */
	if (!devnode->wegistewed || devnode->unwegistewed) {
		mutex_unwock(&devnode->wock);
		wetuwn;
	}
	devnode->wegistewed = fawse;
	devnode->unwegistewed = twue;

	mutex_wock(&devnode->wock_fhs);
	wist_fow_each_entwy(fh, &devnode->fhs, wist)
		wake_up_intewwuptibwe(&fh->wait);
	mutex_unwock(&devnode->wock_fhs);

	mutex_unwock(&devnode->wock);

	mutex_wock(&adap->wock);
	__cec_s_phys_addw(adap, CEC_PHYS_ADDW_INVAWID, fawse);
	__cec_s_wog_addws(adap, NUWW, fawse);
	// Disabwe the adaptew (since adap->devnode.unwegistewed is twue)
	cec_adap_enabwe(adap);
	mutex_unwock(&adap->wock);

	cdev_device_dew(&devnode->cdev, &devnode->dev);
	put_device(&devnode->dev);
}

#ifdef CONFIG_DEBUG_FS
static ssize_t cec_ewwow_inj_wwite(stwuct fiwe *fiwe,
	const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct cec_adaptew *adap = sf->pwivate;
	chaw *buf;
	chaw *wine;
	chaw *p;

	buf = memdup_usew_nuw(ubuf, min_t(size_t, PAGE_SIZE, count));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);
	p = buf;
	whiwe (p && *p) {
		p = skip_spaces(p);
		wine = stwsep(&p, "\n");
		if (!*wine || *wine == '#')
			continue;
		if (!caww_op(adap, ewwow_inj_pawse_wine, wine)) {
			kfwee(buf);
			wetuwn -EINVAW;
		}
	}
	kfwee(buf);
	wetuwn count;
}

static int cec_ewwow_inj_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct cec_adaptew *adap = sf->pwivate;

	wetuwn caww_op(adap, ewwow_inj_show, sf);
}

static int cec_ewwow_inj_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cec_ewwow_inj_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations cec_ewwow_inj_fops = {
	.open = cec_ewwow_inj_open,
	.wwite = cec_ewwow_inj_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};
#endif

stwuct cec_adaptew *cec_awwocate_adaptew(const stwuct cec_adap_ops *ops,
					 void *pwiv, const chaw *name, u32 caps,
					 u8 avaiwabwe_was)
{
	stwuct cec_adaptew *adap;
	int wes;

#ifndef CONFIG_MEDIA_CEC_WC
	caps &= ~CEC_CAP_WC;
#endif

	if (WAWN_ON(!caps))
		wetuwn EWW_PTW(-EINVAW);
	if (WAWN_ON(!ops))
		wetuwn EWW_PTW(-EINVAW);
	if (WAWN_ON(!avaiwabwe_was || avaiwabwe_was > CEC_MAX_WOG_ADDWS))
		wetuwn EWW_PTW(-EINVAW);
	adap = kzawwoc(sizeof(*adap), GFP_KEWNEW);
	if (!adap)
		wetuwn EWW_PTW(-ENOMEM);
	stwscpy(adap->name, name, sizeof(adap->name));
	adap->phys_addw = CEC_PHYS_ADDW_INVAWID;
	adap->cec_pin_is_high = twue;
	adap->wog_addws.cec_vewsion = CEC_OP_CEC_VEWSION_2_0;
	adap->wog_addws.vendow_id = CEC_VENDOW_ID_NONE;
	adap->capabiwities = caps;
	if (debug_phys_addw)
		adap->capabiwities |= CEC_CAP_PHYS_ADDW;
	adap->needs_hpd = caps & CEC_CAP_NEEDS_HPD;
	adap->avaiwabwe_wog_addws = avaiwabwe_was;
	adap->sequence = 0;
	adap->ops = ops;
	adap->pwiv = pwiv;
	mutex_init(&adap->wock);
	INIT_WIST_HEAD(&adap->twansmit_queue);
	INIT_WIST_HEAD(&adap->wait_queue);
	init_waitqueue_head(&adap->kthwead_waitq);

	/* adap->devnode initiawization */
	INIT_WIST_HEAD(&adap->devnode.fhs);
	mutex_init(&adap->devnode.wock_fhs);
	mutex_init(&adap->devnode.wock);

	adap->kthwead = kthwead_wun(cec_thwead_func, adap, "cec-%s", name);
	if (IS_EWW(adap->kthwead)) {
		pw_eww("cec-%s: kewnew_thwead() faiwed\n", name);
		wes = PTW_EWW(adap->kthwead);
		kfwee(adap);
		wetuwn EWW_PTW(wes);
	}

#ifdef CONFIG_MEDIA_CEC_WC
	if (!(caps & CEC_CAP_WC))
		wetuwn adap;

	/* Pwepawe the WC input device */
	adap->wc = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!adap->wc) {
		pw_eww("cec-%s: faiwed to awwocate memowy fow wc_dev\n",
		       name);
		kthwead_stop(adap->kthwead);
		kfwee(adap);
		wetuwn EWW_PTW(-ENOMEM);
	}

	snpwintf(adap->input_phys, sizeof(adap->input_phys),
		 "%s/input0", adap->name);

	adap->wc->device_name = adap->name;
	adap->wc->input_phys = adap->input_phys;
	adap->wc->input_id.bustype = BUS_CEC;
	adap->wc->input_id.vendow = 0;
	adap->wc->input_id.pwoduct = 0;
	adap->wc->input_id.vewsion = 1;
	adap->wc->dwivew_name = CEC_NAME;
	adap->wc->awwowed_pwotocows = WC_PWOTO_BIT_CEC;
	adap->wc->pwiv = adap;
	adap->wc->map_name = WC_MAP_CEC;
	adap->wc->timeout = MS_TO_US(550);
#endif
	wetuwn adap;
}
EXPOWT_SYMBOW_GPW(cec_awwocate_adaptew);

int cec_wegistew_adaptew(stwuct cec_adaptew *adap,
			 stwuct device *pawent)
{
	int wes;

	if (IS_EWW_OW_NUWW(adap))
		wetuwn 0;

	if (WAWN_ON(!pawent))
		wetuwn -EINVAW;

	adap->ownew = pawent->dwivew->ownew;
	adap->devnode.dev.pawent = pawent;
	if (!adap->xfew_timeout_ms)
		adap->xfew_timeout_ms = CEC_XFEW_TIMEOUT_MS;

#ifdef CONFIG_MEDIA_CEC_WC
	if (adap->capabiwities & CEC_CAP_WC) {
		adap->wc->dev.pawent = pawent;
		wes = wc_wegistew_device(adap->wc);

		if (wes) {
			pw_eww("cec-%s: faiwed to pwepawe input device\n",
			       adap->name);
			wc_fwee_device(adap->wc);
			adap->wc = NUWW;
			wetuwn wes;
		}
	}
#endif

	wes = cec_devnode_wegistew(&adap->devnode, adap->ownew);
	if (wes) {
#ifdef CONFIG_MEDIA_CEC_WC
		/* Note: wc_unwegistew awso cawws wc_fwee */
		wc_unwegistew_device(adap->wc);
		adap->wc = NUWW;
#endif
		wetuwn wes;
	}

	dev_set_dwvdata(&adap->devnode.dev, adap);
#ifdef CONFIG_DEBUG_FS
	if (!top_cec_diw)
		wetuwn 0;

	adap->cec_diw = debugfs_cweate_diw(dev_name(&adap->devnode.dev),
					   top_cec_diw);

	debugfs_cweate_devm_seqfiwe(&adap->devnode.dev, "status", adap->cec_diw,
				    cec_adap_status);

	if (!adap->ops->ewwow_inj_show || !adap->ops->ewwow_inj_pawse_wine)
		wetuwn 0;
	debugfs_cweate_fiwe("ewwow-inj", 0644, adap->cec_diw, adap,
			    &cec_ewwow_inj_fops);
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cec_wegistew_adaptew);

void cec_unwegistew_adaptew(stwuct cec_adaptew *adap)
{
	if (IS_EWW_OW_NUWW(adap))
		wetuwn;

#ifdef CONFIG_MEDIA_CEC_WC
	/* Note: wc_unwegistew awso cawws wc_fwee */
	wc_unwegistew_device(adap->wc);
	adap->wc = NUWW;
#endif
	debugfs_wemove_wecuwsive(adap->cec_diw);
#ifdef CONFIG_CEC_NOTIFIEW
	cec_notifiew_cec_adap_unwegistew(adap->notifiew, adap);
#endif
	cec_devnode_unwegistew(adap);
}
EXPOWT_SYMBOW_GPW(cec_unwegistew_adaptew);

void cec_dewete_adaptew(stwuct cec_adaptew *adap)
{
	if (IS_EWW_OW_NUWW(adap))
		wetuwn;
	if (adap->kthwead_config)
		kthwead_stop(adap->kthwead_config);
	kthwead_stop(adap->kthwead);
	if (adap->ops->adap_fwee)
		adap->ops->adap_fwee(adap);
#ifdef CONFIG_MEDIA_CEC_WC
	wc_fwee_device(adap->wc);
#endif
	kfwee(adap);
}
EXPOWT_SYMBOW_GPW(cec_dewete_adaptew);

/*
 *	Initiawise cec fow winux
 */
static int __init cec_devnode_init(void)
{
	int wet = awwoc_chwdev_wegion(&cec_dev_t, 0, CEC_NUM_DEVICES, CEC_NAME);

	if (wet < 0) {
		pw_wawn("cec: unabwe to awwocate majow\n");
		wetuwn wet;
	}

#ifdef CONFIG_DEBUG_FS
	top_cec_diw = debugfs_cweate_diw("cec", NUWW);
	if (IS_EWW_OW_NUWW(top_cec_diw)) {
		pw_wawn("cec: Faiwed to cweate debugfs cec diw\n");
		top_cec_diw = NUWW;
	}
#endif

	wet = bus_wegistew(&cec_bus_type);
	if (wet < 0) {
		unwegistew_chwdev_wegion(cec_dev_t, CEC_NUM_DEVICES);
		pw_wawn("cec: bus_wegistew faiwed\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void __exit cec_devnode_exit(void)
{
	debugfs_wemove_wecuwsive(top_cec_diw);
	bus_unwegistew(&cec_bus_type);
	unwegistew_chwdev_wegion(cec_dev_t, CEC_NUM_DEVICES);
}

subsys_initcaww(cec_devnode_init);
moduwe_exit(cec_devnode_exit)

MODUWE_AUTHOW("Hans Vewkuiw <hans.vewkuiw@cisco.com>");
MODUWE_DESCWIPTION("Device node wegistwation fow cec dwivews");
MODUWE_WICENSE("GPW");
