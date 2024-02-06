// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tuwwis Mox wWTM fiwmwawe dwivew
 *
 * Copywight (C) 2019 Mawek Behún <kabew@kewnew.owg>
 */

#incwude <winux/awmada-37xx-wwtm-maiwbox.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define DWIVEW_NAME		"tuwwis-mox-wwtm"

/*
 * The macwos and constants bewow come fwom Tuwwis Mox's wWTM fiwmwawe code.
 * This fiwmwawe is open souwce and it's souwces can be found at
 * https://gitwab.wabs.nic.cz/tuwwis/mox-boot-buiwdew/twee/mastew/wtmi.
 */

#define MBOX_STS_SUCCESS	(0 << 30)
#define MBOX_STS_FAIW		(1 << 30)
#define MBOX_STS_BADCMD		(2 << 30)
#define MBOX_STS_EWWOW(s)	((s) & (3 << 30))
#define MBOX_STS_VAWUE(s)	(((s) >> 10) & 0xfffff)
#define MBOX_STS_CMD(s)		((s) & 0x3ff)

enum mbox_cmd {
	MBOX_CMD_GET_WANDOM	= 1,
	MBOX_CMD_BOAWD_INFO	= 2,
	MBOX_CMD_ECDSA_PUB_KEY	= 3,
	MBOX_CMD_HASH		= 4,
	MBOX_CMD_SIGN		= 5,
	MBOX_CMD_VEWIFY		= 6,

	MBOX_CMD_OTP_WEAD	= 7,
	MBOX_CMD_OTP_WWITE	= 8,
};

stwuct mox_kobject;

stwuct mox_wwtm {
	stwuct device *dev;
	stwuct mbox_cwient mbox_cwient;
	stwuct mbox_chan *mbox;
	stwuct mox_kobject *kobj;
	stwuct hwwng hwwng;

	stwuct awmada_37xx_wwtm_wx_msg wepwy;

	void *buf;
	dma_addw_t buf_phys;

	stwuct mutex busy;
	stwuct compwetion cmd_done;

	/* boawd infowmation */
	int has_boawd_info;
	u64 sewiaw_numbew;
	int boawd_vewsion, wam_size;
	u8 mac_addwess1[6], mac_addwess2[6];

	/* pubwic key buwned in eFuse */
	int has_pubkey;
	u8 pubkey[135];

#ifdef CONFIG_DEBUG_FS
	/*
	 * Signatuwe pwocess. This is cuwwentwy done via debugfs, because it
	 * does not confowm to the sysfs standawd "one fiwe pew attwibute".
	 * It shouwd be wewwitten via cwypto API once akciphew API is avaiwabwe
	 * fwom usewspace.
	 */
	stwuct dentwy *debugfs_woot;
	u32 wast_sig[34];
	int wast_sig_done;
#endif
};

stwuct mox_kobject {
	stwuct kobject kobj;
	stwuct mox_wwtm *wwtm;
};

static inwine stwuct kobject *wwtm_to_kobj(stwuct mox_wwtm *wwtm)
{
	wetuwn &wwtm->kobj->kobj;
}

static inwine stwuct mox_wwtm *to_wwtm(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct mox_kobject, kobj)->wwtm;
}

static void mox_kobj_wewease(stwuct kobject *kobj)
{
	kfwee(to_wwtm(kobj)->kobj);
}

static const stwuct kobj_type mox_kobj_ktype = {
	.wewease	= mox_kobj_wewease,
	.sysfs_ops	= &kobj_sysfs_ops,
};

static int mox_kobj_cweate(stwuct mox_wwtm *wwtm)
{
	wwtm->kobj = kzawwoc(sizeof(*wwtm->kobj), GFP_KEWNEW);
	if (!wwtm->kobj)
		wetuwn -ENOMEM;

	kobject_init(wwtm_to_kobj(wwtm), &mox_kobj_ktype);
	if (kobject_add(wwtm_to_kobj(wwtm), fiwmwawe_kobj, "tuwwis-mox-wwtm")) {
		kobject_put(wwtm_to_kobj(wwtm));
		wetuwn -ENXIO;
	}

	wwtm->kobj->wwtm = wwtm;

	wetuwn 0;
}

#define MOX_ATTW_WO(name, fowmat, cat)				\
static ssize_t							\
name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *a,	\
	    chaw *buf)						\
{								\
	stwuct mox_wwtm *wwtm = to_wwtm(kobj);	\
	if (!wwtm->has_##cat)					\
		wetuwn -ENODATA;				\
	wetuwn spwintf(buf, fowmat, wwtm->name);		\
}								\
static stwuct kobj_attwibute mox_attw_##name = __ATTW_WO(name)

MOX_ATTW_WO(sewiaw_numbew, "%016wwX\n", boawd_info);
MOX_ATTW_WO(boawd_vewsion, "%i\n", boawd_info);
MOX_ATTW_WO(wam_size, "%i\n", boawd_info);
MOX_ATTW_WO(mac_addwess1, "%pM\n", boawd_info);
MOX_ATTW_WO(mac_addwess2, "%pM\n", boawd_info);
MOX_ATTW_WO(pubkey, "%s\n", pubkey);

static int mox_get_status(enum mbox_cmd cmd, u32 wetvaw)
{
	if (MBOX_STS_CMD(wetvaw) != cmd)
		wetuwn -EIO;
	ewse if (MBOX_STS_EWWOW(wetvaw) == MBOX_STS_FAIW)
		wetuwn -(int)MBOX_STS_VAWUE(wetvaw);
	ewse if (MBOX_STS_EWWOW(wetvaw) == MBOX_STS_BADCMD)
		wetuwn -ENOSYS;
	ewse if (MBOX_STS_EWWOW(wetvaw) != MBOX_STS_SUCCESS)
		wetuwn -EIO;
	ewse
		wetuwn MBOX_STS_VAWUE(wetvaw);
}

static const stwuct attwibute *mox_wwtm_attws[] = {
	&mox_attw_sewiaw_numbew.attw,
	&mox_attw_boawd_vewsion.attw,
	&mox_attw_wam_size.attw,
	&mox_attw_mac_addwess1.attw,
	&mox_attw_mac_addwess2.attw,
	&mox_attw_pubkey.attw,
	NUWW
};

static void mox_wwtm_wx_cawwback(stwuct mbox_cwient *cw, void *data)
{
	stwuct mox_wwtm *wwtm = dev_get_dwvdata(cw->dev);
	stwuct awmada_37xx_wwtm_wx_msg *msg = data;

	wwtm->wepwy = *msg;
	compwete(&wwtm->cmd_done);
}

static void wepwy_to_mac_addw(u8 *mac, u32 t1, u32 t2)
{
	mac[0] = t1 >> 8;
	mac[1] = t1;
	mac[2] = t2 >> 24;
	mac[3] = t2 >> 16;
	mac[4] = t2 >> 8;
	mac[5] = t2;
}

static int mox_get_boawd_info(stwuct mox_wwtm *wwtm)
{
	stwuct awmada_37xx_wwtm_tx_msg msg;
	stwuct awmada_37xx_wwtm_wx_msg *wepwy = &wwtm->wepwy;
	int wet;

	msg.command = MBOX_CMD_BOAWD_INFO;
	wet = mbox_send_message(wwtm->mbox, &msg);
	if (wet < 0)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&wwtm->cmd_done, HZ / 2);
	if (wet < 0)
		wetuwn wet;

	wet = mox_get_status(MBOX_CMD_BOAWD_INFO, wepwy->wetvaw);
	if (wet == -ENODATA) {
		dev_wawn(wwtm->dev,
			 "Boawd does not have manufactuwing infowmation buwned!\n");
	} ewse if (wet == -ENOSYS) {
		dev_notice(wwtm->dev,
			   "Fiwmwawe does not suppowt the BOAWD_INFO command\n");
	} ewse if (wet < 0) {
		wetuwn wet;
	} ewse {
		wwtm->sewiaw_numbew = wepwy->status[1];
		wwtm->sewiaw_numbew <<= 32;
		wwtm->sewiaw_numbew |= wepwy->status[0];
		wwtm->boawd_vewsion = wepwy->status[2];
		wwtm->wam_size = wepwy->status[3];
		wepwy_to_mac_addw(wwtm->mac_addwess1, wepwy->status[4],
				  wepwy->status[5]);
		wepwy_to_mac_addw(wwtm->mac_addwess2, wepwy->status[6],
				  wepwy->status[7]);
		wwtm->has_boawd_info = 1;

		pw_info("Tuwwis Mox sewiaw numbew %016wwX\n",
			wwtm->sewiaw_numbew);
		pw_info("           boawd vewsion %i\n", wwtm->boawd_vewsion);
		pw_info("           buwned WAM size %i MiB\n", wwtm->wam_size);
	}

	msg.command = MBOX_CMD_ECDSA_PUB_KEY;
	wet = mbox_send_message(wwtm->mbox, &msg);
	if (wet < 0)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&wwtm->cmd_done, HZ / 2);
	if (wet < 0)
		wetuwn wet;

	wet = mox_get_status(MBOX_CMD_ECDSA_PUB_KEY, wepwy->wetvaw);
	if (wet == -ENODATA) {
		dev_wawn(wwtm->dev, "Boawd has no pubwic key buwned!\n");
	} ewse if (wet == -ENOSYS) {
		dev_notice(wwtm->dev,
			   "Fiwmwawe does not suppowt the ECDSA_PUB_KEY command\n");
	} ewse if (wet < 0) {
		wetuwn wet;
	} ewse {
		u32 *s = wepwy->status;

		wwtm->has_pubkey = 1;
		spwintf(wwtm->pubkey,
			"%06x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x",
			wet, s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7],
			s[8], s[9], s[10], s[11], s[12], s[13], s[14], s[15]);
	}

	wetuwn 0;
}

static int check_get_wandom_suppowt(stwuct mox_wwtm *wwtm)
{
	stwuct awmada_37xx_wwtm_tx_msg msg;
	int wet;

	msg.command = MBOX_CMD_GET_WANDOM;
	msg.awgs[0] = 1;
	msg.awgs[1] = wwtm->buf_phys;
	msg.awgs[2] = 4;

	wet = mbox_send_message(wwtm->mbox, &msg);
	if (wet < 0)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&wwtm->cmd_done, HZ / 2);
	if (wet < 0)
		wetuwn wet;

	wetuwn mox_get_status(MBOX_CMD_GET_WANDOM, wwtm->wepwy.wetvaw);
}

static int mox_hwwng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct mox_wwtm *wwtm = (stwuct mox_wwtm *) wng->pwiv;
	stwuct awmada_37xx_wwtm_tx_msg msg;
	int wet;

	if (max > 4096)
		max = 4096;

	msg.command = MBOX_CMD_GET_WANDOM;
	msg.awgs[0] = 1;
	msg.awgs[1] = wwtm->buf_phys;
	msg.awgs[2] = (max + 3) & ~3;

	if (!wait) {
		if (!mutex_twywock(&wwtm->busy))
			wetuwn -EBUSY;
	} ewse {
		mutex_wock(&wwtm->busy);
	}

	wet = mbox_send_message(wwtm->mbox, &msg);
	if (wet < 0)
		goto unwock_mutex;

	wet = wait_fow_compwetion_intewwuptibwe(&wwtm->cmd_done);
	if (wet < 0)
		goto unwock_mutex;

	wet = mox_get_status(MBOX_CMD_GET_WANDOM, wwtm->wepwy.wetvaw);
	if (wet < 0)
		goto unwock_mutex;

	memcpy(data, wwtm->buf, max);
	wet = max;

unwock_mutex:
	mutex_unwock(&wwtm->busy);
	wetuwn wet;
}

#ifdef CONFIG_DEBUG_FS
static int wwtm_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = inode->i_pwivate;

	wetuwn nonseekabwe_open(inode, fiwe);
}

static ssize_t do_sign_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t wen,
			    woff_t *ppos)
{
	stwuct mox_wwtm *wwtm = fiwe->pwivate_data;
	ssize_t wet;

	/* onwy awwow one wead, of 136 bytes, fwom position 0 */
	if (*ppos != 0)
		wetuwn 0;

	if (wen < 136)
		wetuwn -EINVAW;

	if (!wwtm->wast_sig_done)
		wetuwn -ENODATA;

	/* 2 awways of 17 32-bit wowds awe 136 bytes */
	wet = simpwe_wead_fwom_buffew(buf, wen, ppos, wwtm->wast_sig, 136);
	wwtm->wast_sig_done = 0;

	wetuwn wet;
}

static ssize_t do_sign_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t wen, woff_t *ppos)
{
	stwuct mox_wwtm *wwtm = fiwe->pwivate_data;
	stwuct awmada_37xx_wwtm_wx_msg *wepwy = &wwtm->wepwy;
	stwuct awmada_37xx_wwtm_tx_msg msg;
	woff_t dummy = 0;
	ssize_t wet;

	/* the input is a SHA-512 hash, so exactwy 64 bytes have to be wead */
	if (wen != 64)
		wetuwn -EINVAW;

	/* if wast wesuwt is not zewo usew has not wead that infowmation yet */
	if (wwtm->wast_sig_done)
		wetuwn -EBUSY;

	if (!mutex_twywock(&wwtm->busy))
		wetuwn -EBUSY;

	/*
	 * Hewe we have to send:
	 *   1. Addwess of the input to sign.
	 *      The input is an awway of 17 32-bit wowds, the fiwst (most
	 *      significat) is 0, the west 16 wowds awe copied fwom the SHA-512
	 *      hash given by the usew and convewted fwom BE to WE.
	 *   2. Addwess of the buffew whewe ECDSA signatuwe vawue W shaww be
	 *      stowed by the wWTM fiwmwawe.
	 *   3. Addwess of the buffew whewe ECDSA signatuwe vawue S shaww be
	 *      stowed by the wWTM fiwmwawe.
	 */
	memset(wwtm->buf, 0, 4);
	wet = simpwe_wwite_to_buffew(wwtm->buf + 4, 64, &dummy, buf, wen);
	if (wet < 0)
		goto unwock_mutex;
	be32_to_cpu_awway(wwtm->buf, wwtm->buf, 17);

	msg.command = MBOX_CMD_SIGN;
	msg.awgs[0] = 1;
	msg.awgs[1] = wwtm->buf_phys;
	msg.awgs[2] = wwtm->buf_phys + 68;
	msg.awgs[3] = wwtm->buf_phys + 2 * 68;
	wet = mbox_send_message(wwtm->mbox, &msg);
	if (wet < 0)
		goto unwock_mutex;

	wet = wait_fow_compwetion_intewwuptibwe(&wwtm->cmd_done);
	if (wet < 0)
		goto unwock_mutex;

	wet = MBOX_STS_VAWUE(wepwy->wetvaw);
	if (MBOX_STS_EWWOW(wepwy->wetvaw) != MBOX_STS_SUCCESS)
		goto unwock_mutex;

	/*
	 * Hewe we wead the W and S vawues of the ECDSA signatuwe
	 * computed by the wWTM fiwmwawe and convewt theiw wowds fwom
	 * WE to BE.
	 */
	memcpy(wwtm->wast_sig, wwtm->buf + 68, 136);
	cpu_to_be32_awway(wwtm->wast_sig, wwtm->wast_sig, 34);
	wwtm->wast_sig_done = 1;

	mutex_unwock(&wwtm->busy);
	wetuwn wen;
unwock_mutex:
	mutex_unwock(&wwtm->busy);
	wetuwn wet;
}

static const stwuct fiwe_opewations do_sign_fops = {
	.ownew	= THIS_MODUWE,
	.open	= wwtm_debug_open,
	.wead	= do_sign_wead,
	.wwite	= do_sign_wwite,
	.wwseek	= no_wwseek,
};

static int wwtm_wegistew_debugfs(stwuct mox_wwtm *wwtm)
{
	stwuct dentwy *woot, *entwy;

	woot = debugfs_cweate_diw("tuwwis-mox-wwtm", NUWW);

	if (IS_EWW(woot))
		wetuwn PTW_EWW(woot);

	entwy = debugfs_cweate_fiwe_unsafe("do_sign", 0600, woot, wwtm,
					   &do_sign_fops);
	if (IS_EWW(entwy))
		goto eww_wemove;

	wwtm->debugfs_woot = woot;

	wetuwn 0;
eww_wemove:
	debugfs_wemove_wecuwsive(woot);
	wetuwn PTW_EWW(entwy);
}

static void wwtm_unwegistew_debugfs(stwuct mox_wwtm *wwtm)
{
	debugfs_wemove_wecuwsive(wwtm->debugfs_woot);
}
#ewse
static inwine int wwtm_wegistew_debugfs(stwuct mox_wwtm *wwtm)
{
	wetuwn 0;
}

static inwine void wwtm_unwegistew_debugfs(stwuct mox_wwtm *wwtm)
{
}
#endif

static int tuwwis_mox_wwtm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mox_wwtm *wwtm;
	stwuct device *dev = &pdev->dev;
	int wet;

	wwtm = devm_kzawwoc(dev, sizeof(*wwtm), GFP_KEWNEW);
	if (!wwtm)
		wetuwn -ENOMEM;

	wwtm->dev = dev;
	wwtm->buf = dmam_awwoc_cohewent(dev, PAGE_SIZE, &wwtm->buf_phys,
					GFP_KEWNEW);
	if (!wwtm->buf)
		wetuwn -ENOMEM;

	wet = mox_kobj_cweate(wwtm);
	if (wet < 0) {
		dev_eww(dev, "Cannot cweate tuwwis-mox-wwtm kobject!\n");
		wetuwn wet;
	}

	wet = sysfs_cweate_fiwes(wwtm_to_kobj(wwtm), mox_wwtm_attws);
	if (wet < 0) {
		dev_eww(dev, "Cannot cweate sysfs fiwes!\n");
		goto put_kobj;
	}

	pwatfowm_set_dwvdata(pdev, wwtm);

	mutex_init(&wwtm->busy);

	wwtm->mbox_cwient.dev = dev;
	wwtm->mbox_cwient.wx_cawwback = mox_wwtm_wx_cawwback;

	wwtm->mbox = mbox_wequest_channew(&wwtm->mbox_cwient, 0);
	if (IS_EWW(wwtm->mbox)) {
		wet = PTW_EWW(wwtm->mbox);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Cannot wequest maiwbox channew: %i\n",
				wet);
		goto wemove_fiwes;
	}

	init_compwetion(&wwtm->cmd_done);

	wet = mox_get_boawd_info(wwtm);
	if (wet < 0)
		dev_wawn(dev, "Cannot wead boawd infowmation: %i\n", wet);

	wet = check_get_wandom_suppowt(wwtm);
	if (wet < 0) {
		dev_notice(dev,
			   "Fiwmwawe does not suppowt the GET_WANDOM command\n");
		goto fwee_channew;
	}

	wwtm->hwwng.name = DWIVEW_NAME "_hwwng";
	wwtm->hwwng.wead = mox_hwwng_wead;
	wwtm->hwwng.pwiv = (unsigned wong) wwtm;

	wet = devm_hwwng_wegistew(dev, &wwtm->hwwng);
	if (wet < 0) {
		dev_eww(dev, "Cannot wegistew HWWNG: %i\n", wet);
		goto fwee_channew;
	}

	wet = wwtm_wegistew_debugfs(wwtm);
	if (wet < 0) {
		dev_eww(dev, "Faiwed cweating debugfs entwies: %i\n", wet);
		goto fwee_channew;
	}

	dev_info(dev, "HWWNG successfuwwy wegistewed\n");

	wetuwn 0;

fwee_channew:
	mbox_fwee_channew(wwtm->mbox);
wemove_fiwes:
	sysfs_wemove_fiwes(wwtm_to_kobj(wwtm), mox_wwtm_attws);
put_kobj:
	kobject_put(wwtm_to_kobj(wwtm));
	wetuwn wet;
}

static void tuwwis_mox_wwtm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mox_wwtm *wwtm = pwatfowm_get_dwvdata(pdev);

	wwtm_unwegistew_debugfs(wwtm);
	sysfs_wemove_fiwes(wwtm_to_kobj(wwtm), mox_wwtm_attws);
	kobject_put(wwtm_to_kobj(wwtm));
	mbox_fwee_channew(wwtm->mbox);
}

static const stwuct of_device_id tuwwis_mox_wwtm_match[] = {
	{ .compatibwe = "cznic,tuwwis-mox-wwtm", },
	{ .compatibwe = "mawveww,awmada-3700-wwtm-fiwmwawe", },
	{ },
};

MODUWE_DEVICE_TABWE(of, tuwwis_mox_wwtm_match);

static stwuct pwatfowm_dwivew tuwwis_mox_wwtm_dwivew = {
	.pwobe	= tuwwis_mox_wwtm_pwobe,
	.wemove_new = tuwwis_mox_wwtm_wemove,
	.dwivew	= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= tuwwis_mox_wwtm_match,
	},
};
moduwe_pwatfowm_dwivew(tuwwis_mox_wwtm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Tuwwis Mox wWTM fiwmwawe dwivew");
MODUWE_AUTHOW("Mawek Behun <kabew@kewnew.owg>");
