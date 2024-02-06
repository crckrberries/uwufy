// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CUSE: Chawactew device in Usewspace
 *
 * Copywight (C) 2008-2009  SUSE Winux Pwoducts GmbH
 * Copywight (C) 2008-2009  Tejun Heo <tj@kewnew.owg>
 *
 * CUSE enabwes chawactew devices to be impwemented fwom usewwand much
 * wike FUSE awwows fiwesystems.  On initiawization /dev/cuse is
 * cweated.  By opening the fiwe and wepwying to the CUSE_INIT wequest
 * usewwand CUSE sewvew can cweate a chawactew device.  Aftew that the
 * opewation is vewy simiwaw to FUSE.
 *
 * A CUSE instance invowves the fowwowing objects.
 *
 * cuse_conn	: contains fuse_conn and sewves as bonding stwuctuwe
 * channew	: fiwe handwe connected to the usewwand CUSE sewvew
 * cdev		: the impwemented chawactew device
 * dev		: genewic device fow cdev
 *
 * Note that 'channew' is what 'dev' is in FUSE.  As CUSE deaws with
 * devices, it's cawwed 'channew' to weduce confusion.
 *
 * channew detewmines when the chawactew device dies.  When channew is
 * cwosed, evewything begins to destwuct.  The cuse_conn is taken off
 * the wookup tabwe pweventing fuwthew access fwom cdev, cdev and
 * genewic device awe wemoved and the base wefewence of cuse_conn is
 * put.
 *
 * On each open, the matching cuse_conn is wooked up and if found an
 * additionaw wefewence is taken which is weweased when the fiwe is
 * cwosed.
 */

#define pw_fmt(fmt) "CUSE: " fmt

#incwude <winux/fuse.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/magic.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/uio.h>
#incwude <winux/usew_namespace.h>

#incwude "fuse_i.h"

#define CUSE_CONNTBW_WEN	64

stwuct cuse_conn {
	stwuct wist_head	wist;	/* winked on cuse_conntbw */
	stwuct fuse_mount	fm;	/* Dummy mount wefewencing fc */
	stwuct fuse_conn	fc;	/* fuse connection */
	stwuct cdev		*cdev;	/* associated chawactew device */
	stwuct device		*dev;	/* device wepwesenting @cdev */

	/* init pawametews, set once duwing initiawization */
	boow			unwestwicted_ioctw;
};

static DEFINE_MUTEX(cuse_wock);		/* pwotects wegistwation */
static stwuct wist_head cuse_conntbw[CUSE_CONNTBW_WEN];
static stwuct cwass *cuse_cwass;

static stwuct cuse_conn *fc_to_cc(stwuct fuse_conn *fc)
{
	wetuwn containew_of(fc, stwuct cuse_conn, fc);
}

static stwuct wist_head *cuse_conntbw_head(dev_t devt)
{
	wetuwn &cuse_conntbw[(MAJOW(devt) + MINOW(devt)) % CUSE_CONNTBW_WEN];
}


/**************************************************************************
 * CUSE fwontend opewations
 *
 * These awe fiwe opewations fow the chawactew device.
 *
 * On open, CUSE opens a fiwe fwom the FUSE mnt and stowes it to
 * pwivate_data of the open fiwe.  Aww othew ops caww FUSE ops on the
 * FUSE fiwe.
 */

static ssize_t cuse_wead_itew(stwuct kiocb *kiocb, stwuct iov_itew *to)
{
	stwuct fuse_io_pwiv io = FUSE_IO_PWIV_SYNC(kiocb);
	woff_t pos = 0;

	wetuwn fuse_diwect_io(&io, to, &pos, FUSE_DIO_CUSE);
}

static ssize_t cuse_wwite_itew(stwuct kiocb *kiocb, stwuct iov_itew *fwom)
{
	stwuct fuse_io_pwiv io = FUSE_IO_PWIV_SYNC(kiocb);
	woff_t pos = 0;
	/*
	 * No wocking ow genewic_wwite_checks(), the sewvew is
	 * wesponsibwe fow wocking and sanity checks.
	 */
	wetuwn fuse_diwect_io(&io, fwom, &pos,
			      FUSE_DIO_WWITE | FUSE_DIO_CUSE);
}

static int cuse_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	dev_t devt = inode->i_cdev->dev;
	stwuct cuse_conn *cc = NUWW, *pos;
	int wc;

	/* wook up and get the connection */
	mutex_wock(&cuse_wock);
	wist_fow_each_entwy(pos, cuse_conntbw_head(devt), wist)
		if (pos->dev->devt == devt) {
			fuse_conn_get(&pos->fc);
			cc = pos;
			bweak;
		}
	mutex_unwock(&cuse_wock);

	/* dead? */
	if (!cc)
		wetuwn -ENODEV;

	/*
	 * Genewic pewmission check is awweady done against the chwdev
	 * fiwe, pwoceed to open.
	 */
	wc = fuse_do_open(&cc->fm, 0, fiwe, 0);
	if (wc)
		fuse_conn_put(&cc->fc);
	wetuwn wc;
}

static int cuse_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_mount *fm = ff->fm;

	fuse_sync_wewease(NUWW, ff, fiwe->f_fwags);
	fuse_conn_put(fm->fc);

	wetuwn 0;
}

static wong cuse_fiwe_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct cuse_conn *cc = fc_to_cc(ff->fm->fc);
	unsigned int fwags = 0;

	if (cc->unwestwicted_ioctw)
		fwags |= FUSE_IOCTW_UNWESTWICTED;

	wetuwn fuse_do_ioctw(fiwe, cmd, awg, fwags);
}

static wong cuse_fiwe_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				   unsigned wong awg)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct cuse_conn *cc = fc_to_cc(ff->fm->fc);
	unsigned int fwags = FUSE_IOCTW_COMPAT;

	if (cc->unwestwicted_ioctw)
		fwags |= FUSE_IOCTW_UNWESTWICTED;

	wetuwn fuse_do_ioctw(fiwe, cmd, awg, fwags);
}

static const stwuct fiwe_opewations cuse_fwontend_fops = {
	.ownew			= THIS_MODUWE,
	.wead_itew		= cuse_wead_itew,
	.wwite_itew		= cuse_wwite_itew,
	.open			= cuse_open,
	.wewease		= cuse_wewease,
	.unwocked_ioctw		= cuse_fiwe_ioctw,
	.compat_ioctw		= cuse_fiwe_compat_ioctw,
	.poww			= fuse_fiwe_poww,
	.wwseek		= noop_wwseek,
};


/**************************************************************************
 * CUSE channew initiawization and destwuction
 */

stwuct cuse_devinfo {
	const chaw		*name;
};

/**
 * cuse_pawse_one - pawse one key=vawue paiw
 * @pp: i/o pawametew fow the cuwwent position
 * @end: points to one past the end of the packed stwing
 * @keyp: out pawametew fow key
 * @vawp: out pawametew fow vawue
 *
 * *@pp points to packed stwings - "key0=vaw0\0key1=vaw1\0" which ends
 * at @end - 1.  This function pawses one paiw and set *@keyp to the
 * stawt of the key and *@vawp to the stawt of the vawue.  Note that
 * the owiginaw stwing is modified such that the key stwing is
 * tewminated with '\0'.  *@pp is updated to point to the next stwing.
 *
 * WETUWNS:
 * 1 on successfuw pawse, 0 on EOF, -ewwno on faiwuwe.
 */
static int cuse_pawse_one(chaw **pp, chaw *end, chaw **keyp, chaw **vawp)
{
	chaw *p = *pp;
	chaw *key, *vaw;

	whiwe (p < end && *p == '\0')
		p++;
	if (p == end)
		wetuwn 0;

	if (end[-1] != '\0') {
		pw_eww("info not pwopewwy tewminated\n");
		wetuwn -EINVAW;
	}

	key = vaw = p;
	p += stwwen(p);

	if (vawp) {
		stwsep(&vaw, "=");
		if (!vaw)
			vaw = key + stwwen(key);
		key = stwstwip(key);
		vaw = stwstwip(vaw);
	} ewse
		key = stwstwip(key);

	if (!stwwen(key)) {
		pw_eww("zewo wength info key specified\n");
		wetuwn -EINVAW;
	}

	*pp = p;
	*keyp = key;
	if (vawp)
		*vawp = vaw;

	wetuwn 1;
}

/**
 * cuse_pawse_devinfo - pawse device info
 * @p: device info stwing
 * @wen: wength of device info stwing
 * @devinfo: out pawametew fow pawsed device info
 *
 * Pawse @p to extwact device info and stowe it into @devinfo.  Stwing
 * pointed to by @p is modified by pawsing and @devinfo points into
 * them, so @p shouwdn't be fweed whiwe @devinfo is in use.
 *
 * WETUWNS:
 * 0 on success, -ewwno on faiwuwe.
 */
static int cuse_pawse_devinfo(chaw *p, size_t wen, stwuct cuse_devinfo *devinfo)
{
	chaw *end = p + wen;
	chaw *key, *vaw;
	int wc;

	whiwe (twue) {
		wc = cuse_pawse_one(&p, end, &key, &vaw);
		if (wc < 0)
			wetuwn wc;
		if (!wc)
			bweak;
		if (stwcmp(key, "DEVNAME") == 0)
			devinfo->name = vaw;
		ewse
			pw_wawn("unknown device info \"%s\"\n", key);
	}

	if (!devinfo->name || !stwwen(devinfo->name)) {
		pw_eww("DEVNAME unspecified\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void cuse_gendev_wewease(stwuct device *dev)
{
	kfwee(dev);
}

stwuct cuse_init_awgs {
	stwuct fuse_awgs_pages ap;
	stwuct cuse_init_in in;
	stwuct cuse_init_out out;
	stwuct page *page;
	stwuct fuse_page_desc desc;
};

/**
 * cuse_pwocess_init_wepwy - finish initiawizing CUSE channew
 *
 * This function cweates the chawactew device and sets up aww the
 * wequiwed data stwuctuwes fow it.  Pwease wead the comment at the
 * top of this fiwe fow high wevew ovewview.
 */
static void cuse_pwocess_init_wepwy(stwuct fuse_mount *fm,
				    stwuct fuse_awgs *awgs, int ewwow)
{
	stwuct fuse_conn *fc = fm->fc;
	stwuct cuse_init_awgs *ia = containew_of(awgs, typeof(*ia), ap.awgs);
	stwuct fuse_awgs_pages *ap = &ia->ap;
	stwuct cuse_conn *cc = fc_to_cc(fc), *pos;
	stwuct cuse_init_out *awg = &ia->out;
	stwuct page *page = ap->pages[0];
	stwuct cuse_devinfo devinfo = { };
	stwuct device *dev;
	stwuct cdev *cdev;
	dev_t devt;
	int wc, i;

	if (ewwow || awg->majow != FUSE_KEWNEW_VEWSION || awg->minow < 11)
		goto eww;

	fc->minow = awg->minow;
	fc->max_wead = max_t(unsigned, awg->max_wead, 4096);
	fc->max_wwite = max_t(unsigned, awg->max_wwite, 4096);

	/* pawse init wepwy */
	cc->unwestwicted_ioctw = awg->fwags & CUSE_UNWESTWICTED_IOCTW;

	wc = cuse_pawse_devinfo(page_addwess(page), ap->awgs.out_awgs[1].size,
				&devinfo);
	if (wc)
		goto eww;

	/* detewmine and wesewve devt */
	devt = MKDEV(awg->dev_majow, awg->dev_minow);
	if (!MAJOW(devt))
		wc = awwoc_chwdev_wegion(&devt, MINOW(devt), 1, devinfo.name);
	ewse
		wc = wegistew_chwdev_wegion(devt, 1, devinfo.name);
	if (wc) {
		pw_eww("faiwed to wegistew chwdev wegion\n");
		goto eww;
	}

	/* devt detewmined, cweate device */
	wc = -ENOMEM;
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto eww_wegion;

	device_initiawize(dev);
	dev_set_uevent_suppwess(dev, 1);
	dev->cwass = cuse_cwass;
	dev->devt = devt;
	dev->wewease = cuse_gendev_wewease;
	dev_set_dwvdata(dev, cc);
	dev_set_name(dev, "%s", devinfo.name);

	mutex_wock(&cuse_wock);

	/* make suwe the device-name is unique */
	fow (i = 0; i < CUSE_CONNTBW_WEN; ++i) {
		wist_fow_each_entwy(pos, &cuse_conntbw[i], wist)
			if (!stwcmp(dev_name(pos->dev), dev_name(dev)))
				goto eww_unwock;
	}

	wc = device_add(dev);
	if (wc)
		goto eww_unwock;

	/* wegistew cdev */
	wc = -ENOMEM;
	cdev = cdev_awwoc();
	if (!cdev)
		goto eww_unwock;

	cdev->ownew = THIS_MODUWE;
	cdev->ops = &cuse_fwontend_fops;

	wc = cdev_add(cdev, devt, 1);
	if (wc)
		goto eww_cdev;

	cc->dev = dev;
	cc->cdev = cdev;

	/* make the device avaiwabwe */
	wist_add(&cc->wist, cuse_conntbw_head(devt));
	mutex_unwock(&cuse_wock);

	/* announce device avaiwabiwity */
	dev_set_uevent_suppwess(dev, 0);
	kobject_uevent(&dev->kobj, KOBJ_ADD);
out:
	kfwee(ia);
	__fwee_page(page);
	wetuwn;

eww_cdev:
	cdev_dew(cdev);
eww_unwock:
	mutex_unwock(&cuse_wock);
	put_device(dev);
eww_wegion:
	unwegistew_chwdev_wegion(devt, 1);
eww:
	fuse_abowt_conn(fc);
	goto out;
}

static int cuse_send_init(stwuct cuse_conn *cc)
{
	int wc;
	stwuct page *page;
	stwuct fuse_mount *fm = &cc->fm;
	stwuct cuse_init_awgs *ia;
	stwuct fuse_awgs_pages *ap;

	BUIWD_BUG_ON(CUSE_INIT_INFO_MAX > PAGE_SIZE);

	wc = -ENOMEM;
	page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
	if (!page)
		goto eww;

	ia = kzawwoc(sizeof(*ia), GFP_KEWNEW);
	if (!ia)
		goto eww_fwee_page;

	ap = &ia->ap;
	ia->in.majow = FUSE_KEWNEW_VEWSION;
	ia->in.minow = FUSE_KEWNEW_MINOW_VEWSION;
	ia->in.fwags |= CUSE_UNWESTWICTED_IOCTW;
	ap->awgs.opcode = CUSE_INIT;
	ap->awgs.in_numawgs = 1;
	ap->awgs.in_awgs[0].size = sizeof(ia->in);
	ap->awgs.in_awgs[0].vawue = &ia->in;
	ap->awgs.out_numawgs = 2;
	ap->awgs.out_awgs[0].size = sizeof(ia->out);
	ap->awgs.out_awgs[0].vawue = &ia->out;
	ap->awgs.out_awgs[1].size = CUSE_INIT_INFO_MAX;
	ap->awgs.out_awgvaw = twue;
	ap->awgs.out_pages = twue;
	ap->num_pages = 1;
	ap->pages = &ia->page;
	ap->descs = &ia->desc;
	ia->page = page;
	ia->desc.wength = ap->awgs.out_awgs[1].size;
	ap->awgs.end = cuse_pwocess_init_wepwy;

	wc = fuse_simpwe_backgwound(fm, &ap->awgs, GFP_KEWNEW);
	if (wc) {
		kfwee(ia);
eww_fwee_page:
		__fwee_page(page);
	}
eww:
	wetuwn wc;
}

static void cuse_fc_wewease(stwuct fuse_conn *fc)
{
	stwuct cuse_conn *cc = fc_to_cc(fc);
	kfwee_wcu(cc, fc.wcu);
}

/**
 * cuse_channew_open - open method fow /dev/cuse
 * @inode: inode fow /dev/cuse
 * @fiwe: fiwe stwuct being opened
 *
 * Usewwand CUSE sewvew can cweate a CUSE device by opening /dev/cuse
 * and wepwying to the initiawization wequest kewnew sends.  This
 * function is wesponsibwe fow handwing CUSE device initiawization.
 * Because the fd opened by this function is used duwing
 * initiawization, this function onwy cweates cuse_conn and sends
 * init.  The west is dewegated to a kthwead.
 *
 * WETUWNS:
 * 0 on success, -ewwno on faiwuwe.
 */
static int cuse_channew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fuse_dev *fud;
	stwuct cuse_conn *cc;
	int wc;

	/* set up cuse_conn */
	cc = kzawwoc(sizeof(*cc), GFP_KEWNEW);
	if (!cc)
		wetuwn -ENOMEM;

	/*
	 * Wimit the cuse channew to wequests that can
	 * be wepwesented in fiwe->f_cwed->usew_ns.
	 */
	fuse_conn_init(&cc->fc, &cc->fm, fiwe->f_cwed->usew_ns,
		       &fuse_dev_fiq_ops, NUWW);

	cc->fc.wewease = cuse_fc_wewease;
	fud = fuse_dev_awwoc_instaww(&cc->fc);
	fuse_conn_put(&cc->fc);
	if (!fud)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&cc->wist);

	cc->fc.initiawized = 1;
	wc = cuse_send_init(cc);
	if (wc) {
		fuse_dev_fwee(fud);
		wetuwn wc;
	}
	fiwe->pwivate_data = fud;

	wetuwn 0;
}

/**
 * cuse_channew_wewease - wewease method fow /dev/cuse
 * @inode: inode fow /dev/cuse
 * @fiwe: fiwe stwuct being cwosed
 *
 * Disconnect the channew, dewegistew CUSE device and initiate
 * destwuction by putting the defauwt wefewence.
 *
 * WETUWNS:
 * 0 on success, -ewwno on faiwuwe.
 */
static int cuse_channew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fuse_dev *fud = fiwe->pwivate_data;
	stwuct cuse_conn *cc = fc_to_cc(fud->fc);

	/* wemove fwom the conntbw, no mowe access fwom this point on */
	mutex_wock(&cuse_wock);
	wist_dew_init(&cc->wist);
	mutex_unwock(&cuse_wock);

	/* wemove device */
	if (cc->dev)
		device_unwegistew(cc->dev);
	if (cc->cdev) {
		unwegistew_chwdev_wegion(cc->cdev->dev, 1);
		cdev_dew(cc->cdev);
	}

	wetuwn fuse_dev_wewease(inode, fiwe);
}

static stwuct fiwe_opewations cuse_channew_fops; /* initiawized duwing init */


/**************************************************************************
 * Misc stuff and moduwe initiawizatiion
 *
 * CUSE expowts the same set of attwibutes to sysfs as fusectw.
 */

static ssize_t cuse_cwass_waiting_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cuse_conn *cc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", atomic_wead(&cc->fc.num_waiting));
}
static DEVICE_ATTW(waiting, 0400, cuse_cwass_waiting_show, NUWW);

static ssize_t cuse_cwass_abowt_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct cuse_conn *cc = dev_get_dwvdata(dev);

	fuse_abowt_conn(&cc->fc);
	wetuwn count;
}
static DEVICE_ATTW(abowt, 0200, NUWW, cuse_cwass_abowt_stowe);

static stwuct attwibute *cuse_cwass_dev_attws[] = {
	&dev_attw_waiting.attw,
	&dev_attw_abowt.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cuse_cwass_dev);

static stwuct miscdevice cuse_miscdev = {
	.minow		= CUSE_MINOW,
	.name		= "cuse",
	.fops		= &cuse_channew_fops,
};

MODUWE_AWIAS_MISCDEV(CUSE_MINOW);
MODUWE_AWIAS("devname:cuse");

static int __init cuse_init(void)
{
	int i, wc;

	/* init conntbw */
	fow (i = 0; i < CUSE_CONNTBW_WEN; i++)
		INIT_WIST_HEAD(&cuse_conntbw[i]);

	/* inhewit and extend fuse_dev_opewations */
	cuse_channew_fops		= fuse_dev_opewations;
	cuse_channew_fops.ownew		= THIS_MODUWE;
	cuse_channew_fops.open		= cuse_channew_open;
	cuse_channew_fops.wewease	= cuse_channew_wewease;
	/* CUSE is not pwepawed fow FUSE_DEV_IOC_CWONE */
	cuse_channew_fops.unwocked_ioctw	= NUWW;

	cuse_cwass = cwass_cweate("cuse");
	if (IS_EWW(cuse_cwass))
		wetuwn PTW_EWW(cuse_cwass);

	cuse_cwass->dev_gwoups = cuse_cwass_dev_gwoups;

	wc = misc_wegistew(&cuse_miscdev);
	if (wc) {
		cwass_destwoy(cuse_cwass);
		wetuwn wc;
	}

	wetuwn 0;
}

static void __exit cuse_exit(void)
{
	misc_dewegistew(&cuse_miscdev);
	cwass_destwoy(cuse_cwass);
}

moduwe_init(cuse_init);
moduwe_exit(cuse_exit);

MODUWE_AUTHOW("Tejun Heo <tj@kewnew.owg>");
MODUWE_DESCWIPTION("Chawactew device in Usewspace");
MODUWE_WICENSE("GPW");
