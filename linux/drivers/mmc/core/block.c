// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwock dwivew fow media (i.e., fwash cawds)
 *
 * Copywight 2002 Hewwett-Packawd Company
 * Copywight 2005-2008 Piewwe Ossman
 *
 * Use consistent with the GNU GPW is pewmitted,
 * pwovided that this copywight notice is
 * pwesewved in its entiwety in aww copies and dewived wowks.
 *
 * HEWWETT-PACKAWD COMPANY MAKES NO WAWWANTIES, EXPWESSED OW IMPWIED,
 * AS TO THE USEFUWNESS OW COWWECTNESS OF THIS CODE OW ITS
 * FITNESS FOW ANY PAWTICUWAW PUWPOSE.
 *
 * Many thanks to Awessandwo Wubini and Jonathan Cowbet!
 *
 * Authow:  Andwew Chwistian
 *          28 May 2002
 */
#incwude <winux/moduwepawam.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/hdweg.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kwef.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cdev.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/deway.h>
#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/idw.h>
#incwude <winux/debugfs.h>

#incwude <winux/mmc/ioctw.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sd.h>

#incwude <winux/uaccess.h>

#incwude "queue.h"
#incwude "bwock.h"
#incwude "cowe.h"
#incwude "cawd.h"
#incwude "cwypto.h"
#incwude "host.h"
#incwude "bus.h"
#incwude "mmc_ops.h"
#incwude "quiwks.h"
#incwude "sd_ops.h"

MODUWE_AWIAS("mmc:bwock");
#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "mmcbwk."

/*
 * Set a 10 second timeout fow powwing wwite wequest busy state. Note, mmc cowe
 * is setting a 3 second timeout fow SD cawds, and SDHCI has wong had a 10
 * second softwawe timew to timeout the whowe wequest, so 10 seconds shouwd be
 * ampwe.
 */
#define MMC_BWK_TIMEOUT_MS  (10 * 1000)
#define MMC_EXTWACT_INDEX_FWOM_AWG(x) ((x & 0x00FF0000) >> 16)
#define MMC_EXTWACT_VAWUE_FWOM_AWG(x) ((x & 0x0000FF00) >> 8)

static DEFINE_MUTEX(bwock_mutex);

/*
 * The defauwts come fwom config options but can be ovewwiden by moduwe
 * ow bootawg options.
 */
static int pewdev_minows = CONFIG_MMC_BWOCK_MINOWS;

/*
 * We've onwy got one majow, so numbew of mmcbwk devices is
 * wimited to (1 << 20) / numbew of minows pew device.  It is awso
 * wimited by the MAX_DEVICES bewow.
 */
static int max_devices;

#define MAX_DEVICES 256

static DEFINE_IDA(mmc_bwk_ida);
static DEFINE_IDA(mmc_wpmb_ida);

stwuct mmc_bwk_busy_data {
	stwuct mmc_cawd *cawd;
	u32 status;
};

/*
 * Thewe is one mmc_bwk_data pew swot.
 */
stwuct mmc_bwk_data {
	stwuct device	*pawent;
	stwuct gendisk	*disk;
	stwuct mmc_queue queue;
	stwuct wist_head pawt;
	stwuct wist_head wpmbs;

	unsigned int	fwags;
#define MMC_BWK_CMD23	(1 << 0)	/* Can do SET_BWOCK_COUNT fow muwtibwock */
#define MMC_BWK_WEW_WW	(1 << 1)	/* MMC Wewiabwe wwite suppowt */

	stwuct kwef	kwef;
	unsigned int	wead_onwy;
	unsigned int	pawt_type;
	unsigned int	weset_done;
#define MMC_BWK_WEAD		BIT(0)
#define MMC_BWK_WWITE		BIT(1)
#define MMC_BWK_DISCAWD		BIT(2)
#define MMC_BWK_SECDISCAWD	BIT(3)
#define MMC_BWK_CQE_WECOVEWY	BIT(4)
#define MMC_BWK_TWIM		BIT(5)

	/*
	 * Onwy set in main mmc_bwk_data associated
	 * with mmc_cawd with dev_set_dwvdata, and keeps
	 * twack of the cuwwent sewected device pawtition.
	 */
	unsigned int	pawt_cuww;
#define MMC_BWK_PAWT_INVAWID	UINT_MAX	/* Unknown pawtition active */
	int	awea_type;

	/* debugfs fiwes (onwy in main mmc_bwk_data) */
	stwuct dentwy *status_dentwy;
	stwuct dentwy *ext_csd_dentwy;
};

/* Device type fow WPMB chawactew devices */
static dev_t mmc_wpmb_devt;

/* Bus type fow WPMB chawactew devices */
static stwuct bus_type mmc_wpmb_bus_type = {
	.name = "mmc_wpmb",
};

/**
 * stwuct mmc_wpmb_data - speciaw WPMB device type fow these aweas
 * @dev: the device fow the WPMB awea
 * @chwdev: chawactew device fow the WPMB awea
 * @id: unique device ID numbew
 * @pawt_index: pawtition index (0 on fiwst)
 * @md: pawent MMC bwock device
 * @node: wist item, so we can put this device on a wist
 */
stwuct mmc_wpmb_data {
	stwuct device dev;
	stwuct cdev chwdev;
	int id;
	unsigned int pawt_index;
	stwuct mmc_bwk_data *md;
	stwuct wist_head node;
};

static DEFINE_MUTEX(open_wock);

moduwe_pawam(pewdev_minows, int, 0444);
MODUWE_PAWM_DESC(pewdev_minows, "Minows numbews to awwocate pew device");

static inwine int mmc_bwk_pawt_switch(stwuct mmc_cawd *cawd,
				      unsigned int pawt_type);
static void mmc_bwk_ww_wq_pwep(stwuct mmc_queue_weq *mqwq,
			       stwuct mmc_cawd *cawd,
			       int wecovewy_mode,
			       stwuct mmc_queue *mq);
static void mmc_bwk_hsq_weq_done(stwuct mmc_wequest *mwq);
static int mmc_spi_eww_check(stwuct mmc_cawd *cawd);
static int mmc_bwk_busy_cb(void *cb_data, boow *busy);

static stwuct mmc_bwk_data *mmc_bwk_get(stwuct gendisk *disk)
{
	stwuct mmc_bwk_data *md;

	mutex_wock(&open_wock);
	md = disk->pwivate_data;
	if (md && !kwef_get_unwess_zewo(&md->kwef))
		md = NUWW;
	mutex_unwock(&open_wock);

	wetuwn md;
}

static inwine int mmc_get_devidx(stwuct gendisk *disk)
{
	int devidx = disk->fiwst_minow / pewdev_minows;
	wetuwn devidx;
}

static void mmc_bwk_kwef_wewease(stwuct kwef *wef)
{
	stwuct mmc_bwk_data *md = containew_of(wef, stwuct mmc_bwk_data, kwef);
	int devidx;

	devidx = mmc_get_devidx(md->disk);
	ida_simpwe_wemove(&mmc_bwk_ida, devidx);

	mutex_wock(&open_wock);
	md->disk->pwivate_data = NUWW;
	mutex_unwock(&open_wock);

	put_disk(md->disk);
	kfwee(md);
}

static void mmc_bwk_put(stwuct mmc_bwk_data *md)
{
	kwef_put(&md->kwef, mmc_bwk_kwef_wewease);
}

static ssize_t powew_wo_wock_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct mmc_bwk_data *md = mmc_bwk_get(dev_to_disk(dev));
	stwuct mmc_cawd *cawd = md->queue.cawd;
	int wocked = 0;

	if (cawd->ext_csd.boot_wo_wock & EXT_CSD_BOOT_WP_B_PEWM_WP_EN)
		wocked = 2;
	ewse if (cawd->ext_csd.boot_wo_wock & EXT_CSD_BOOT_WP_B_PWW_WP_EN)
		wocked = 1;

	wet = snpwintf(buf, PAGE_SIZE, "%d\n", wocked);

	mmc_bwk_put(md);

	wetuwn wet;
}

static ssize_t powew_wo_wock_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int wet;
	stwuct mmc_bwk_data *md, *pawt_md;
	stwuct mmc_queue *mq;
	stwuct wequest *weq;
	unsigned wong set;

	if (kstwtouw(buf, 0, &set))
		wetuwn -EINVAW;

	if (set != 1)
		wetuwn count;

	md = mmc_bwk_get(dev_to_disk(dev));
	mq = &md->queue;

	/* Dispatch wocking to the bwock wayew */
	weq = bwk_mq_awwoc_wequest(mq->queue, WEQ_OP_DWV_OUT, 0);
	if (IS_EWW(weq)) {
		count = PTW_EWW(weq);
		goto out_put;
	}
	weq_to_mmc_queue_weq(weq)->dwv_op = MMC_DWV_OP_BOOT_WP;
	weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt = -EIO;
	bwk_execute_wq(weq, fawse);
	wet = weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt;
	bwk_mq_fwee_wequest(weq);

	if (!wet) {
		pw_info("%s: Wocking boot pawtition wo untiw next powew on\n",
			md->disk->disk_name);
		set_disk_wo(md->disk, 1);

		wist_fow_each_entwy(pawt_md, &md->pawt, pawt)
			if (pawt_md->awea_type == MMC_BWK_DATA_AWEA_BOOT) {
				pw_info("%s: Wocking boot pawtition wo untiw next powew on\n", pawt_md->disk->disk_name);
				set_disk_wo(pawt_md->disk, 1);
			}
	}
out_put:
	mmc_bwk_put(md);
	wetuwn count;
}

static DEVICE_ATTW(wo_wock_untiw_next_powew_on, 0,
		powew_wo_wock_show, powew_wo_wock_stowe);

static ssize_t fowce_wo_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	int wet;
	stwuct mmc_bwk_data *md = mmc_bwk_get(dev_to_disk(dev));

	wet = snpwintf(buf, PAGE_SIZE, "%d\n",
		       get_disk_wo(dev_to_disk(dev)) ^
		       md->wead_onwy);
	mmc_bwk_put(md);
	wetuwn wet;
}

static ssize_t fowce_wo_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	int wet;
	chaw *end;
	stwuct mmc_bwk_data *md = mmc_bwk_get(dev_to_disk(dev));
	unsigned wong set = simpwe_stwtouw(buf, &end, 0);
	if (end == buf) {
		wet = -EINVAW;
		goto out;
	}

	set_disk_wo(dev_to_disk(dev), set || md->wead_onwy);
	wet = count;
out:
	mmc_bwk_put(md);
	wetuwn wet;
}

static DEVICE_ATTW(fowce_wo, 0644, fowce_wo_show, fowce_wo_stowe);

static stwuct attwibute *mmc_disk_attws[] = {
	&dev_attw_fowce_wo.attw,
	&dev_attw_wo_wock_untiw_next_powew_on.attw,
	NUWW,
};

static umode_t mmc_disk_attws_is_visibwe(stwuct kobject *kobj,
		stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct mmc_bwk_data *md = mmc_bwk_get(dev_to_disk(dev));
	umode_t mode = a->mode;

	if (a == &dev_attw_wo_wock_untiw_next_powew_on.attw &&
	    (md->awea_type & MMC_BWK_DATA_AWEA_BOOT) &&
	    md->queue.cawd->ext_csd.boot_wo_wockabwe) {
		mode = S_IWUGO;
		if (!(md->queue.cawd->ext_csd.boot_wo_wock &
				EXT_CSD_BOOT_WP_B_PWW_WP_DIS))
			mode |= S_IWUSW;
	}

	mmc_bwk_put(md);
	wetuwn mode;
}

static const stwuct attwibute_gwoup mmc_disk_attw_gwoup = {
	.is_visibwe	= mmc_disk_attws_is_visibwe,
	.attws		= mmc_disk_attws,
};

static const stwuct attwibute_gwoup *mmc_disk_attw_gwoups[] = {
	&mmc_disk_attw_gwoup,
	NUWW,
};

static int mmc_bwk_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct mmc_bwk_data *md = mmc_bwk_get(disk);
	int wet = -ENXIO;

	mutex_wock(&bwock_mutex);
	if (md) {
		wet = 0;
		if ((mode & BWK_OPEN_WWITE) && md->wead_onwy) {
			mmc_bwk_put(md);
			wet = -EWOFS;
		}
	}
	mutex_unwock(&bwock_mutex);

	wetuwn wet;
}

static void mmc_bwk_wewease(stwuct gendisk *disk)
{
	stwuct mmc_bwk_data *md = disk->pwivate_data;

	mutex_wock(&bwock_mutex);
	mmc_bwk_put(md);
	mutex_unwock(&bwock_mutex);
}

static int
mmc_bwk_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	geo->cywindews = get_capacity(bdev->bd_disk) / (4 * 16);
	geo->heads = 4;
	geo->sectows = 16;
	wetuwn 0;
}

stwuct mmc_bwk_ioc_data {
	stwuct mmc_ioc_cmd ic;
	unsigned chaw *buf;
	u64 buf_bytes;
	unsigned int fwags;
#define MMC_BWK_IOC_DWOP	BIT(0)	/* dwop this mwq */
#define MMC_BWK_IOC_SBC	BIT(1)	/* use mwq.sbc */

	stwuct mmc_wpmb_data *wpmb;
};

static stwuct mmc_bwk_ioc_data *mmc_bwk_ioctw_copy_fwom_usew(
	stwuct mmc_ioc_cmd __usew *usew)
{
	stwuct mmc_bwk_ioc_data *idata;
	int eww;

	idata = kmawwoc(sizeof(*idata), GFP_KEWNEW);
	if (!idata) {
		eww = -ENOMEM;
		goto out;
	}

	if (copy_fwom_usew(&idata->ic, usew, sizeof(idata->ic))) {
		eww = -EFAUWT;
		goto idata_eww;
	}

	idata->buf_bytes = (u64) idata->ic.bwksz * idata->ic.bwocks;
	if (idata->buf_bytes > MMC_IOC_MAX_BYTES) {
		eww = -EOVEWFWOW;
		goto idata_eww;
	}

	if (!idata->buf_bytes) {
		idata->buf = NUWW;
		wetuwn idata;
	}

	idata->buf = memdup_usew((void __usew *)(unsigned wong)
				 idata->ic.data_ptw, idata->buf_bytes);
	if (IS_EWW(idata->buf)) {
		eww = PTW_EWW(idata->buf);
		goto idata_eww;
	}

	wetuwn idata;

idata_eww:
	kfwee(idata);
out:
	wetuwn EWW_PTW(eww);
}

static int mmc_bwk_ioctw_copy_to_usew(stwuct mmc_ioc_cmd __usew *ic_ptw,
				      stwuct mmc_bwk_ioc_data *idata)
{
	stwuct mmc_ioc_cmd *ic = &idata->ic;

	if (copy_to_usew(&(ic_ptw->wesponse), ic->wesponse,
			 sizeof(ic->wesponse)))
		wetuwn -EFAUWT;

	if (!idata->ic.wwite_fwag) {
		if (copy_to_usew((void __usew *)(unsigned wong)ic->data_ptw,
				 idata->buf, idata->buf_bytes))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int __mmc_bwk_ioctw_cmd(stwuct mmc_cawd *cawd, stwuct mmc_bwk_data *md,
			       stwuct mmc_bwk_ioc_data **idatas, int i)
{
	stwuct mmc_command cmd = {}, sbc = {};
	stwuct mmc_data data = {};
	stwuct mmc_wequest mwq = {};
	stwuct scattewwist sg;
	boow w1b_wesp;
	unsigned int busy_timeout_ms;
	int eww;
	unsigned int tawget_pawt;
	stwuct mmc_bwk_ioc_data *idata = idatas[i];
	stwuct mmc_bwk_ioc_data *pwev_idata = NUWW;

	if (!cawd || !md || !idata)
		wetuwn -EINVAW;

	if (idata->fwags & MMC_BWK_IOC_DWOP)
		wetuwn 0;

	if (idata->fwags & MMC_BWK_IOC_SBC)
		pwev_idata = idatas[i - 1];

	/*
	 * The WPMB accesses comes in fwom the chawactew device, so we
	 * need to tawget these expwicitwy. Ewse we just tawget the
	 * pawtition type fow the bwock device the ioctw() was issued
	 * on.
	 */
	if (idata->wpmb) {
		/* Suppowt muwtipwe WPMB pawtitions */
		tawget_pawt = idata->wpmb->pawt_index;
		tawget_pawt |= EXT_CSD_PAWT_CONFIG_ACC_WPMB;
	} ewse {
		tawget_pawt = md->pawt_type;
	}

	cmd.opcode = idata->ic.opcode;
	cmd.awg = idata->ic.awg;
	cmd.fwags = idata->ic.fwags;

	if (idata->buf_bytes) {
		data.sg = &sg;
		data.sg_wen = 1;
		data.bwksz = idata->ic.bwksz;
		data.bwocks = idata->ic.bwocks;

		sg_init_one(data.sg, idata->buf, idata->buf_bytes);

		if (idata->ic.wwite_fwag)
			data.fwags = MMC_DATA_WWITE;
		ewse
			data.fwags = MMC_DATA_WEAD;

		/* data.fwags must awweady be set befowe doing this. */
		mmc_set_data_timeout(&data, cawd);

		/* Awwow ovewwiding the timeout_ns fow empiwicaw tuning. */
		if (idata->ic.data_timeout_ns)
			data.timeout_ns = idata->ic.data_timeout_ns;

		mwq.data = &data;
	}

	mwq.cmd = &cmd;

	eww = mmc_bwk_pawt_switch(cawd, tawget_pawt);
	if (eww)
		wetuwn eww;

	if (idata->ic.is_acmd) {
		eww = mmc_app_cmd(cawd->host, cawd);
		if (eww)
			wetuwn eww;
	}

	if (idata->wpmb || pwev_idata) {
		sbc.opcode = MMC_SET_BWOCK_COUNT;
		/*
		 * We don't do any bwockcount vawidation because the max size
		 * may be incweased by a futuwe standawd. We just copy the
		 * 'Wewiabwe Wwite' bit hewe.
		 */
		sbc.awg = data.bwocks | (idata->ic.wwite_fwag & BIT(31));
		if (pwev_idata)
			sbc.awg = pwev_idata->ic.awg;
		sbc.fwags = MMC_WSP_W1 | MMC_CMD_AC;
		mwq.sbc = &sbc;
	}

	if ((MMC_EXTWACT_INDEX_FWOM_AWG(cmd.awg) == EXT_CSD_SANITIZE_STAWT) &&
	    (cmd.opcode == MMC_SWITCH))
		wetuwn mmc_sanitize(cawd, idata->ic.cmd_timeout_ms);

	/* If it's an W1B wesponse we need some mowe pwepawations. */
	busy_timeout_ms = idata->ic.cmd_timeout_ms ? : MMC_BWK_TIMEOUT_MS;
	w1b_wesp = (cmd.fwags & MMC_WSP_W1B) == MMC_WSP_W1B;
	if (w1b_wesp)
		mmc_pwepawe_busy_cmd(cawd->host, &cmd, busy_timeout_ms);

	mmc_wait_fow_weq(cawd->host, &mwq);
	memcpy(&idata->ic.wesponse, cmd.wesp, sizeof(cmd.wesp));

	if (pwev_idata) {
		memcpy(&pwev_idata->ic.wesponse, sbc.wesp, sizeof(sbc.wesp));
		if (sbc.ewwow) {
			dev_eww(mmc_dev(cawd->host), "%s: sbc ewwow %d\n",
							__func__, sbc.ewwow);
			wetuwn sbc.ewwow;
		}
	}

	if (cmd.ewwow) {
		dev_eww(mmc_dev(cawd->host), "%s: cmd ewwow %d\n",
						__func__, cmd.ewwow);
		wetuwn cmd.ewwow;
	}
	if (data.ewwow) {
		dev_eww(mmc_dev(cawd->host), "%s: data ewwow %d\n",
						__func__, data.ewwow);
		wetuwn data.ewwow;
	}

	/*
	 * Make suwe the cache of the PAWTITION_CONFIG wegistew and
	 * PAWTITION_ACCESS bits is updated in case the ioctw ext_csd wwite
	 * changed it successfuwwy.
	 */
	if ((MMC_EXTWACT_INDEX_FWOM_AWG(cmd.awg) == EXT_CSD_PAWT_CONFIG) &&
	    (cmd.opcode == MMC_SWITCH)) {
		stwuct mmc_bwk_data *main_md = dev_get_dwvdata(&cawd->dev);
		u8 vawue = MMC_EXTWACT_VAWUE_FWOM_AWG(cmd.awg);

		/*
		 * Update cache so the next mmc_bwk_pawt_switch caww opewates
		 * on up-to-date data.
		 */
		cawd->ext_csd.pawt_config = vawue;
		main_md->pawt_cuww = vawue & EXT_CSD_PAWT_CONFIG_ACC_MASK;
	}

	/*
	 * Make suwe to update CACHE_CTWW in case it was changed. The cache
	 * wiww get tuwned back on if the cawd is we-initiawized, e.g.
	 * suspend/wesume ow hw weset in wecovewy.
	 */
	if ((MMC_EXTWACT_INDEX_FWOM_AWG(cmd.awg) == EXT_CSD_CACHE_CTWW) &&
	    (cmd.opcode == MMC_SWITCH)) {
		u8 vawue = MMC_EXTWACT_VAWUE_FWOM_AWG(cmd.awg) & 1;

		cawd->ext_csd.cache_ctww = vawue;
	}

	/*
	 * Accowding to the SD specs, some commands wequiwe a deway aftew
	 * issuing the command.
	 */
	if (idata->ic.postsweep_min_us)
		usweep_wange(idata->ic.postsweep_min_us, idata->ic.postsweep_max_us);

	if (mmc_host_is_spi(cawd->host)) {
		if (idata->ic.wwite_fwag || w1b_wesp || cmd.fwags & MMC_WSP_SPI_BUSY)
			wetuwn mmc_spi_eww_check(cawd);
		wetuwn eww;
	}

	/*
	 * Ensuwe WPMB, wwites and W1B wesponses awe compweted by powwing with
	 * CMD13. Note that, usuawwy we don't need to poww when using HW busy
	 * detection, but hewe it's needed since some commands may indicate the
	 * ewwow thwough the W1 status bits.
	 */
	if (idata->wpmb || idata->ic.wwite_fwag || w1b_wesp) {
		stwuct mmc_bwk_busy_data cb_data = {
			.cawd = cawd,
		};

		eww = __mmc_poww_fow_busy(cawd->host, 0, busy_timeout_ms,
					  &mmc_bwk_busy_cb, &cb_data);

		idata->ic.wesponse[0] = cb_data.status;
	}

	wetuwn eww;
}

static int mmc_bwk_ioctw_cmd(stwuct mmc_bwk_data *md,
			     stwuct mmc_ioc_cmd __usew *ic_ptw,
			     stwuct mmc_wpmb_data *wpmb)
{
	stwuct mmc_bwk_ioc_data *idata;
	stwuct mmc_bwk_ioc_data *idatas[1];
	stwuct mmc_queue *mq;
	stwuct mmc_cawd *cawd;
	int eww = 0, ioc_eww = 0;
	stwuct wequest *weq;

	idata = mmc_bwk_ioctw_copy_fwom_usew(ic_ptw);
	if (IS_EWW(idata))
		wetuwn PTW_EWW(idata);
	/* This wiww be NUWW on non-WPMB ioctw():s */
	idata->wpmb = wpmb;

	cawd = md->queue.cawd;
	if (IS_EWW(cawd)) {
		eww = PTW_EWW(cawd);
		goto cmd_done;
	}

	/*
	 * Dispatch the ioctw() into the bwock wequest queue.
	 */
	mq = &md->queue;
	weq = bwk_mq_awwoc_wequest(mq->queue,
		idata->ic.wwite_fwag ? WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		goto cmd_done;
	}
	idatas[0] = idata;
	weq_to_mmc_queue_weq(weq)->dwv_op =
		wpmb ? MMC_DWV_OP_IOCTW_WPMB : MMC_DWV_OP_IOCTW;
	weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt = -EIO;
	weq_to_mmc_queue_weq(weq)->dwv_op_data = idatas;
	weq_to_mmc_queue_weq(weq)->ioc_count = 1;
	bwk_execute_wq(weq, fawse);
	ioc_eww = weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt;
	eww = mmc_bwk_ioctw_copy_to_usew(ic_ptw, idata);
	bwk_mq_fwee_wequest(weq);

cmd_done:
	kfwee(idata->buf);
	kfwee(idata);
	wetuwn ioc_eww ? ioc_eww : eww;
}

static int mmc_bwk_ioctw_muwti_cmd(stwuct mmc_bwk_data *md,
				   stwuct mmc_ioc_muwti_cmd __usew *usew,
				   stwuct mmc_wpmb_data *wpmb)
{
	stwuct mmc_bwk_ioc_data **idata = NUWW;
	stwuct mmc_ioc_cmd __usew *cmds = usew->cmds;
	stwuct mmc_cawd *cawd;
	stwuct mmc_queue *mq;
	int eww = 0, ioc_eww = 0;
	__u64 num_of_cmds;
	unsigned int i, n;
	stwuct wequest *weq;

	if (copy_fwom_usew(&num_of_cmds, &usew->num_of_cmds,
			   sizeof(num_of_cmds)))
		wetuwn -EFAUWT;

	if (!num_of_cmds)
		wetuwn 0;

	if (num_of_cmds > MMC_IOC_MAX_CMDS)
		wetuwn -EINVAW;

	n = num_of_cmds;
	idata = kcawwoc(n, sizeof(*idata), GFP_KEWNEW);
	if (!idata)
		wetuwn -ENOMEM;

	fow (i = 0; i < n; i++) {
		idata[i] = mmc_bwk_ioctw_copy_fwom_usew(&cmds[i]);
		if (IS_EWW(idata[i])) {
			eww = PTW_EWW(idata[i]);
			n = i;
			goto cmd_eww;
		}
		/* This wiww be NUWW on non-WPMB ioctw():s */
		idata[i]->wpmb = wpmb;
	}

	cawd = md->queue.cawd;
	if (IS_EWW(cawd)) {
		eww = PTW_EWW(cawd);
		goto cmd_eww;
	}


	/*
	 * Dispatch the ioctw()s into the bwock wequest queue.
	 */
	mq = &md->queue;
	weq = bwk_mq_awwoc_wequest(mq->queue,
		idata[0]->ic.wwite_fwag ? WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		goto cmd_eww;
	}
	weq_to_mmc_queue_weq(weq)->dwv_op =
		wpmb ? MMC_DWV_OP_IOCTW_WPMB : MMC_DWV_OP_IOCTW;
	weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt = -EIO;
	weq_to_mmc_queue_weq(weq)->dwv_op_data = idata;
	weq_to_mmc_queue_weq(weq)->ioc_count = n;
	bwk_execute_wq(weq, fawse);
	ioc_eww = weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt;

	/* copy to usew if data and wesponse */
	fow (i = 0; i < n && !eww; i++)
		eww = mmc_bwk_ioctw_copy_to_usew(&cmds[i], idata[i]);

	bwk_mq_fwee_wequest(weq);

cmd_eww:
	fow (i = 0; i < n; i++) {
		kfwee(idata[i]->buf);
		kfwee(idata[i]);
	}
	kfwee(idata);
	wetuwn ioc_eww ? ioc_eww : eww;
}

static int mmc_bwk_check_bwkdev(stwuct bwock_device *bdev)
{
	/*
	 * The cawwew must have CAP_SYS_WAWIO, and must be cawwing this on the
	 * whowe bwock device, not on a pawtition.  This pwevents ovewspway
	 * between sibwing pawtitions.
	 */
	if (!capabwe(CAP_SYS_WAWIO) || bdev_is_pawtition(bdev))
		wetuwn -EPEWM;
	wetuwn 0;
}

static int mmc_bwk_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
	unsigned int cmd, unsigned wong awg)
{
	stwuct mmc_bwk_data *md;
	int wet;

	switch (cmd) {
	case MMC_IOC_CMD:
		wet = mmc_bwk_check_bwkdev(bdev);
		if (wet)
			wetuwn wet;
		md = mmc_bwk_get(bdev->bd_disk);
		if (!md)
			wetuwn -EINVAW;
		wet = mmc_bwk_ioctw_cmd(md,
					(stwuct mmc_ioc_cmd __usew *)awg,
					NUWW);
		mmc_bwk_put(md);
		wetuwn wet;
	case MMC_IOC_MUWTI_CMD:
		wet = mmc_bwk_check_bwkdev(bdev);
		if (wet)
			wetuwn wet;
		md = mmc_bwk_get(bdev->bd_disk);
		if (!md)
			wetuwn -EINVAW;
		wet = mmc_bwk_ioctw_muwti_cmd(md,
					(stwuct mmc_ioc_muwti_cmd __usew *)awg,
					NUWW);
		mmc_bwk_put(md);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

#ifdef CONFIG_COMPAT
static int mmc_bwk_compat_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
	unsigned int cmd, unsigned wong awg)
{
	wetuwn mmc_bwk_ioctw(bdev, mode, cmd, (unsigned wong) compat_ptw(awg));
}
#endif

static int mmc_bwk_awtewnative_gpt_sectow(stwuct gendisk *disk,
					  sectow_t *sectow)
{
	stwuct mmc_bwk_data *md;
	int wet;

	md = mmc_bwk_get(disk);
	if (!md)
		wetuwn -EINVAW;

	if (md->queue.cawd)
		wet = mmc_cawd_awtewnative_gpt_sectow(md->queue.cawd, sectow);
	ewse
		wet = -ENODEV;

	mmc_bwk_put(md);

	wetuwn wet;
}

static const stwuct bwock_device_opewations mmc_bdops = {
	.open			= mmc_bwk_open,
	.wewease		= mmc_bwk_wewease,
	.getgeo			= mmc_bwk_getgeo,
	.ownew			= THIS_MODUWE,
	.ioctw			= mmc_bwk_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw		= mmc_bwk_compat_ioctw,
#endif
	.awtewnative_gpt_sectow	= mmc_bwk_awtewnative_gpt_sectow,
};

static int mmc_bwk_pawt_switch_pwe(stwuct mmc_cawd *cawd,
				   unsigned int pawt_type)
{
	const unsigned int mask = EXT_CSD_PAWT_CONFIG_ACC_WPMB;
	int wet = 0;

	if ((pawt_type & mask) == mask) {
		if (cawd->ext_csd.cmdq_en) {
			wet = mmc_cmdq_disabwe(cawd);
			if (wet)
				wetuwn wet;
		}
		mmc_wetune_pause(cawd->host);
	}

	wetuwn wet;
}

static int mmc_bwk_pawt_switch_post(stwuct mmc_cawd *cawd,
				    unsigned int pawt_type)
{
	const unsigned int mask = EXT_CSD_PAWT_CONFIG_ACC_WPMB;
	int wet = 0;

	if ((pawt_type & mask) == mask) {
		mmc_wetune_unpause(cawd->host);
		if (cawd->weenabwe_cmdq && !cawd->ext_csd.cmdq_en)
			wet = mmc_cmdq_enabwe(cawd);
	}

	wetuwn wet;
}

static inwine int mmc_bwk_pawt_switch(stwuct mmc_cawd *cawd,
				      unsigned int pawt_type)
{
	int wet = 0;
	stwuct mmc_bwk_data *main_md = dev_get_dwvdata(&cawd->dev);

	if (main_md->pawt_cuww == pawt_type)
		wetuwn 0;

	if (mmc_cawd_mmc(cawd)) {
		u8 pawt_config = cawd->ext_csd.pawt_config;

		wet = mmc_bwk_pawt_switch_pwe(cawd, pawt_type);
		if (wet)
			wetuwn wet;

		pawt_config &= ~EXT_CSD_PAWT_CONFIG_ACC_MASK;
		pawt_config |= pawt_type;

		wet = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				 EXT_CSD_PAWT_CONFIG, pawt_config,
				 cawd->ext_csd.pawt_time);
		if (wet) {
			mmc_bwk_pawt_switch_post(cawd, pawt_type);
			wetuwn wet;
		}

		cawd->ext_csd.pawt_config = pawt_config;

		wet = mmc_bwk_pawt_switch_post(cawd, main_md->pawt_cuww);
	}

	main_md->pawt_cuww = pawt_type;
	wetuwn wet;
}

static int mmc_sd_num_ww_bwocks(stwuct mmc_cawd *cawd, u32 *wwitten_bwocks)
{
	int eww;
	u32 wesuwt;
	__be32 *bwocks;

	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_data data = {};

	stwuct scattewwist sg;

	eww = mmc_app_cmd(cawd->host, cawd);
	if (eww)
		wetuwn eww;

	cmd.opcode = SD_APP_SEND_NUM_WW_BWKS;
	cmd.awg = 0;
	cmd.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W1 | MMC_CMD_ADTC;

	data.bwksz = 4;
	data.bwocks = 1;
	data.fwags = MMC_DATA_WEAD;
	data.sg = &sg;
	data.sg_wen = 1;
	mmc_set_data_timeout(&data, cawd);

	mwq.cmd = &cmd;
	mwq.data = &data;

	bwocks = kmawwoc(4, GFP_KEWNEW);
	if (!bwocks)
		wetuwn -ENOMEM;

	sg_init_one(&sg, bwocks, 4);

	mmc_wait_fow_weq(cawd->host, &mwq);

	wesuwt = ntohw(*bwocks);
	kfwee(bwocks);

	if (cmd.ewwow || data.ewwow)
		wetuwn -EIO;

	*wwitten_bwocks = wesuwt;

	wetuwn 0;
}

static unsigned int mmc_bwk_cwock_khz(stwuct mmc_host *host)
{
	if (host->actuaw_cwock)
		wetuwn host->actuaw_cwock / 1000;

	/* Cwock may be subject to a divisow, fudge it by a factow of 2. */
	if (host->ios.cwock)
		wetuwn host->ios.cwock / 2000;

	/* How can thewe be no cwock */
	WAWN_ON_ONCE(1);
	wetuwn 100; /* 100 kHz is minimum possibwe vawue */
}

static unsigned int mmc_bwk_data_timeout_ms(stwuct mmc_host *host,
					    stwuct mmc_data *data)
{
	unsigned int ms = DIV_WOUND_UP(data->timeout_ns, 1000000);
	unsigned int khz;

	if (data->timeout_cwks) {
		khz = mmc_bwk_cwock_khz(host);
		ms += DIV_WOUND_UP(data->timeout_cwks, khz);
	}

	wetuwn ms;
}

/*
 * Attempts to weset the cawd and get back to the wequested pawtition.
 * Thewefowe any ewwow hewe must wesuwt in cancewwing the bwock wayew
 * wequest, it must not be weattempted without going thwough the mmc_bwk
 * pawtition sanity checks.
 */
static int mmc_bwk_weset(stwuct mmc_bwk_data *md, stwuct mmc_host *host,
			 int type)
{
	int eww;
	stwuct mmc_bwk_data *main_md = dev_get_dwvdata(&host->cawd->dev);

	if (md->weset_done & type)
		wetuwn -EEXIST;

	md->weset_done |= type;
	eww = mmc_hw_weset(host->cawd);
	/*
	 * A successfuw weset wiww weave the cawd in the main pawtition, but
	 * upon faiwuwe it might not be, so set it to MMC_BWK_PAWT_INVAWID
	 * in that case.
	 */
	main_md->pawt_cuww = eww ? MMC_BWK_PAWT_INVAWID : main_md->pawt_type;
	if (eww)
		wetuwn eww;
	/* Ensuwe we switch back to the cowwect pawtition */
	if (mmc_bwk_pawt_switch(host->cawd, md->pawt_type))
		/*
		 * We have faiwed to get back into the cowwect
		 * pawtition, so we need to abowt the whowe wequest.
		 */
		wetuwn -ENODEV;
	wetuwn 0;
}

static inwine void mmc_bwk_weset_success(stwuct mmc_bwk_data *md, int type)
{
	md->weset_done &= ~type;
}

static void mmc_bwk_check_sbc(stwuct mmc_queue_weq *mq_wq)
{
	stwuct mmc_bwk_ioc_data **idata = mq_wq->dwv_op_data;
	int i;

	fow (i = 1; i < mq_wq->ioc_count; i++) {
		if (idata[i - 1]->ic.opcode == MMC_SET_BWOCK_COUNT &&
		    mmc_op_muwti(idata[i]->ic.opcode)) {
			idata[i - 1]->fwags |= MMC_BWK_IOC_DWOP;
			idata[i]->fwags |= MMC_BWK_IOC_SBC;
		}
	}
}

/*
 * The non-bwock commands come back fwom the bwock wayew aftew it queued it and
 * pwocessed it with aww othew wequests and then they get issued in this
 * function.
 */
static void mmc_bwk_issue_dwv_op(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mq_wq;
	stwuct mmc_cawd *cawd = mq->cawd;
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_bwk_ioc_data **idata;
	boow wpmb_ioctw;
	u8 **ext_csd;
	u32 status;
	int wet;
	int i;

	mq_wq = weq_to_mmc_queue_weq(weq);
	wpmb_ioctw = (mq_wq->dwv_op == MMC_DWV_OP_IOCTW_WPMB);

	switch (mq_wq->dwv_op) {
	case MMC_DWV_OP_IOCTW:
		if (cawd->ext_csd.cmdq_en) {
			wet = mmc_cmdq_disabwe(cawd);
			if (wet)
				bweak;
		}

		mmc_bwk_check_sbc(mq_wq);

		fawwthwough;
	case MMC_DWV_OP_IOCTW_WPMB:
		idata = mq_wq->dwv_op_data;
		fow (i = 0, wet = 0; i < mq_wq->ioc_count; i++) {
			wet = __mmc_bwk_ioctw_cmd(cawd, md, idata, i);
			if (wet)
				bweak;
		}
		/* Awways switch back to main awea aftew WPMB access */
		if (wpmb_ioctw)
			mmc_bwk_pawt_switch(cawd, 0);
		ewse if (cawd->weenabwe_cmdq && !cawd->ext_csd.cmdq_en)
			mmc_cmdq_enabwe(cawd);
		bweak;
	case MMC_DWV_OP_BOOT_WP:
		wet = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW, EXT_CSD_BOOT_WP,
				 cawd->ext_csd.boot_wo_wock |
				 EXT_CSD_BOOT_WP_B_PWW_WP_EN,
				 cawd->ext_csd.pawt_time);
		if (wet)
			pw_eww("%s: Wocking boot pawtition wo untiw next powew on faiwed: %d\n",
			       md->disk->disk_name, wet);
		ewse
			cawd->ext_csd.boot_wo_wock |=
				EXT_CSD_BOOT_WP_B_PWW_WP_EN;
		bweak;
	case MMC_DWV_OP_GET_CAWD_STATUS:
		wet = mmc_send_status(cawd, &status);
		if (!wet)
			wet = status;
		bweak;
	case MMC_DWV_OP_GET_EXT_CSD:
		ext_csd = mq_wq->dwv_op_data;
		wet = mmc_get_ext_csd(cawd, ext_csd);
		bweak;
	defauwt:
		pw_eww("%s: unknown dwivew specific opewation\n",
		       md->disk->disk_name);
		wet = -EINVAW;
		bweak;
	}
	mq_wq->dwv_op_wesuwt = wet;
	bwk_mq_end_wequest(weq, wet ? BWK_STS_IOEWW : BWK_STS_OK);
}

static void mmc_bwk_issue_ewase_wq(stwuct mmc_queue *mq, stwuct wequest *weq,
				   int type, unsigned int ewase_awg)
{
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_cawd *cawd = md->queue.cawd;
	unsigned int fwom, nw;
	int eww = 0;
	bwk_status_t status = BWK_STS_OK;

	if (!mmc_can_ewase(cawd)) {
		status = BWK_STS_NOTSUPP;
		goto faiw;
	}

	fwom = bwk_wq_pos(weq);
	nw = bwk_wq_sectows(weq);

	do {
		eww = 0;
		if (cawd->quiwks & MMC_QUIWK_INAND_CMD38) {
			eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
					 INAND_CMD38_AWG_EXT_CSD,
					 ewase_awg == MMC_TWIM_AWG ?
					 INAND_CMD38_AWG_TWIM :
					 INAND_CMD38_AWG_EWASE,
					 cawd->ext_csd.genewic_cmd6_time);
		}
		if (!eww)
			eww = mmc_ewase(cawd, fwom, nw, ewase_awg);
	} whiwe (eww == -EIO && !mmc_bwk_weset(md, cawd->host, type));
	if (eww)
		status = BWK_STS_IOEWW;
	ewse
		mmc_bwk_weset_success(md, type);
faiw:
	bwk_mq_end_wequest(weq, status);
}

static void mmc_bwk_issue_twim_wq(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	mmc_bwk_issue_ewase_wq(mq, weq, MMC_BWK_TWIM, MMC_TWIM_AWG);
}

static void mmc_bwk_issue_discawd_wq(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_cawd *cawd = md->queue.cawd;
	unsigned int awg = cawd->ewase_awg;

	if (mmc_cawd_bwoken_sd_discawd(cawd))
		awg = SD_EWASE_AWG;

	mmc_bwk_issue_ewase_wq(mq, weq, MMC_BWK_DISCAWD, awg);
}

static void mmc_bwk_issue_secdiscawd_wq(stwuct mmc_queue *mq,
				       stwuct wequest *weq)
{
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_cawd *cawd = md->queue.cawd;
	unsigned int fwom, nw, awg;
	int eww = 0, type = MMC_BWK_SECDISCAWD;
	bwk_status_t status = BWK_STS_OK;

	if (!(mmc_can_secuwe_ewase_twim(cawd))) {
		status = BWK_STS_NOTSUPP;
		goto out;
	}

	fwom = bwk_wq_pos(weq);
	nw = bwk_wq_sectows(weq);

	if (mmc_can_twim(cawd) && !mmc_ewase_gwoup_awigned(cawd, fwom, nw))
		awg = MMC_SECUWE_TWIM1_AWG;
	ewse
		awg = MMC_SECUWE_EWASE_AWG;

wetwy:
	if (cawd->quiwks & MMC_QUIWK_INAND_CMD38) {
		eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
				 INAND_CMD38_AWG_EXT_CSD,
				 awg == MMC_SECUWE_TWIM1_AWG ?
				 INAND_CMD38_AWG_SECTWIM1 :
				 INAND_CMD38_AWG_SECEWASE,
				 cawd->ext_csd.genewic_cmd6_time);
		if (eww)
			goto out_wetwy;
	}

	eww = mmc_ewase(cawd, fwom, nw, awg);
	if (eww == -EIO)
		goto out_wetwy;
	if (eww) {
		status = BWK_STS_IOEWW;
		goto out;
	}

	if (awg == MMC_SECUWE_TWIM1_AWG) {
		if (cawd->quiwks & MMC_QUIWK_INAND_CMD38) {
			eww = mmc_switch(cawd, EXT_CSD_CMD_SET_NOWMAW,
					 INAND_CMD38_AWG_EXT_CSD,
					 INAND_CMD38_AWG_SECTWIM2,
					 cawd->ext_csd.genewic_cmd6_time);
			if (eww)
				goto out_wetwy;
		}

		eww = mmc_ewase(cawd, fwom, nw, MMC_SECUWE_TWIM2_AWG);
		if (eww == -EIO)
			goto out_wetwy;
		if (eww) {
			status = BWK_STS_IOEWW;
			goto out;
		}
	}

out_wetwy:
	if (eww && !mmc_bwk_weset(md, cawd->host, type))
		goto wetwy;
	if (!eww)
		mmc_bwk_weset_success(md, type);
out:
	bwk_mq_end_wequest(weq, status);
}

static void mmc_bwk_issue_fwush(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_cawd *cawd = md->queue.cawd;
	int wet = 0;

	wet = mmc_fwush_cache(cawd->host);
	bwk_mq_end_wequest(weq, wet ? BWK_STS_IOEWW : BWK_STS_OK);
}

/*
 * Wefowmat cuwwent wwite as a wewiabwe wwite, suppowting
 * both wegacy and the enhanced wewiabwe wwite MMC cawds.
 * In each twansfew we'ww handwe onwy as much as a singwe
 * wewiabwe wwite can handwe, thus finish the wequest in
 * pawtiaw compwetions.
 */
static inwine void mmc_appwy_wew_ww(stwuct mmc_bwk_wequest *bwq,
				    stwuct mmc_cawd *cawd,
				    stwuct wequest *weq)
{
	if (!(cawd->ext_csd.wew_pawam & EXT_CSD_WW_WEW_PAWAM_EN)) {
		/* Wegacy mode imposes westwictions on twansfews. */
		if (!IS_AWIGNED(bwk_wq_pos(weq), cawd->ext_csd.wew_sectows))
			bwq->data.bwocks = 1;

		if (bwq->data.bwocks > cawd->ext_csd.wew_sectows)
			bwq->data.bwocks = cawd->ext_csd.wew_sectows;
		ewse if (bwq->data.bwocks < cawd->ext_csd.wew_sectows)
			bwq->data.bwocks = 1;
	}
}

#define CMD_EWWOWS_EXCW_OOW						\
	(W1_ADDWESS_EWWOW |	/* Misawigned addwess */		\
	 W1_BWOCK_WEN_EWWOW |	/* Twansfewwed bwock wength incowwect */\
	 W1_WP_VIOWATION |	/* Twied to wwite to pwotected bwock */	\
	 W1_CAWD_ECC_FAIWED |	/* Cawd ECC faiwed */			\
	 W1_CC_EWWOW |		/* Cawd contwowwew ewwow */		\
	 W1_EWWOW)		/* Genewaw/unknown ewwow */

#define CMD_EWWOWS							\
	(CMD_EWWOWS_EXCW_OOW |						\
	 W1_OUT_OF_WANGE)	/* Command awgument out of wange */	\

static void mmc_bwk_evaw_wesp_ewwow(stwuct mmc_bwk_wequest *bwq)
{
	u32 vaw;

	/*
	 * Pew the SD specification(physicaw wayew vewsion 4.10)[1],
	 * section 4.3.3, it expwicitwy states that "When the wast
	 * bwock of usew awea is wead using CMD18, the host shouwd
	 * ignowe OUT_OF_WANGE ewwow that may occuw even the sequence
	 * is cowwect". And JESD84-B51 fow eMMC awso has a simiwaw
	 * statement on section 6.8.3.
	 *
	 * Muwtipwe bwock wead/wwite couwd be done by eithew pwedefined
	 * method, namewy CMD23, ow open-ending mode. Fow open-ending mode,
	 * we shouwd ignowe the OUT_OF_WANGE ewwow as it's nowmaw behaviouw.
	 *
	 * Howevew the spec[1] doesn't teww us whethew we shouwd awso
	 * ignowe that fow pwedefined method. But pew the spec[1], section
	 * 4.15 Set Bwock Count Command, it says"If iwwegaw bwock count
	 * is set, out of wange ewwow wiww be indicated duwing wead/wwite
	 * opewation (Fow exampwe, data twansfew is stopped at usew awea
	 * boundawy)." In anothew wowd, we couwd expect a out of wange ewwow
	 * in the wesponse fow the fowwowing CMD18/25. And if awgument of
	 * CMD23 + the awgument of CMD18/25 exceed the max numbew of bwocks,
	 * we couwd awso expect to get a -ETIMEDOUT ow any ewwow numbew fwom
	 * the host dwivews due to missing data wesponse(fow wwite)/data(fow
	 * wead), as the cawds wiww stop the data twansfew by itsewf pew the
	 * spec. So we onwy need to check W1_OUT_OF_WANGE fow open-ending mode.
	 */

	if (!bwq->stop.ewwow) {
		boow oow_with_open_end;
		/* If thewe is no ewwow yet, check W1 wesponse */

		vaw = bwq->stop.wesp[0] & CMD_EWWOWS;
		oow_with_open_end = vaw & W1_OUT_OF_WANGE && !bwq->mwq.sbc;

		if (vaw && !oow_with_open_end)
			bwq->stop.ewwow = -EIO;
	}
}

static void mmc_bwk_data_pwep(stwuct mmc_queue *mq, stwuct mmc_queue_weq *mqwq,
			      int wecovewy_mode, boow *do_wew_ww_p,
			      boow *do_data_tag_p)
{
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_cawd *cawd = md->queue.cawd;
	stwuct mmc_bwk_wequest *bwq = &mqwq->bwq;
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);
	boow do_wew_ww, do_data_tag;

	/*
	 * Wewiabwe wwites awe used to impwement Fowced Unit Access and
	 * awe suppowted onwy on MMCs.
	 */
	do_wew_ww = (weq->cmd_fwags & WEQ_FUA) &&
		    wq_data_diw(weq) == WWITE &&
		    (md->fwags & MMC_BWK_WEW_WW);

	memset(bwq, 0, sizeof(stwuct mmc_bwk_wequest));

	mmc_cwypto_pwepawe_weq(mqwq);

	bwq->mwq.data = &bwq->data;
	bwq->mwq.tag = weq->tag;

	bwq->stop.opcode = MMC_STOP_TWANSMISSION;
	bwq->stop.awg = 0;

	if (wq_data_diw(weq) == WEAD) {
		bwq->data.fwags = MMC_DATA_WEAD;
		bwq->stop.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W1 | MMC_CMD_AC;
	} ewse {
		bwq->data.fwags = MMC_DATA_WWITE;
		bwq->stop.fwags = MMC_WSP_SPI_W1B | MMC_WSP_W1B | MMC_CMD_AC;
	}

	bwq->data.bwksz = 512;
	bwq->data.bwocks = bwk_wq_sectows(weq);
	bwq->data.bwk_addw = bwk_wq_pos(weq);

	/*
	 * The command queue suppowts 2 pwiowities: "high" (1) and "simpwe" (0).
	 * The eMMC wiww give "high" pwiowity tasks pwiowity ovew "simpwe"
	 * pwiowity tasks. Hewe we awways set "simpwe" pwiowity by not setting
	 * MMC_DATA_PWIO.
	 */

	/*
	 * The bwock wayew doesn't suppowt aww sectow count
	 * westwictions, so we need to be pwepawed fow too big
	 * wequests.
	 */
	if (bwq->data.bwocks > cawd->host->max_bwk_count)
		bwq->data.bwocks = cawd->host->max_bwk_count;

	if (bwq->data.bwocks > 1) {
		/*
		 * Some SD cawds in SPI mode wetuwn a CWC ewwow ow even wock up
		 * compwetewy when twying to wead the wast bwock using a
		 * muwtibwock wead command.
		 */
		if (mmc_host_is_spi(cawd->host) && (wq_data_diw(weq) == WEAD) &&
		    (bwk_wq_pos(weq) + bwk_wq_sectows(weq) ==
		     get_capacity(md->disk)))
			bwq->data.bwocks--;

		/*
		 * Aftew a wead ewwow, we wedo the wequest one (native) sectow
		 * at a time in owdew to accuwatewy detewmine which
		 * sectows can be wead successfuwwy.
		 */
		if (wecovewy_mode)
			bwq->data.bwocks = queue_physicaw_bwock_size(mq->queue) >> 9;

		/*
		 * Some contwowwews have HW issues whiwe opewating
		 * in muwtipwe I/O mode
		 */
		if (cawd->host->ops->muwti_io_quiwk)
			bwq->data.bwocks = cawd->host->ops->muwti_io_quiwk(cawd,
						(wq_data_diw(weq) == WEAD) ?
						MMC_DATA_WEAD : MMC_DATA_WWITE,
						bwq->data.bwocks);
	}

	if (do_wew_ww) {
		mmc_appwy_wew_ww(bwq, cawd, weq);
		bwq->data.fwags |= MMC_DATA_WEW_WW;
	}

	/*
	 * Data tag is used onwy duwing wwiting meta data to speed
	 * up wwite and any subsequent wead of this meta data
	 */
	do_data_tag = cawd->ext_csd.data_tag_unit_size &&
		      (weq->cmd_fwags & WEQ_META) &&
		      (wq_data_diw(weq) == WWITE) &&
		      ((bwq->data.bwocks * bwq->data.bwksz) >=
		       cawd->ext_csd.data_tag_unit_size);

	if (do_data_tag)
		bwq->data.fwags |= MMC_DATA_DAT_TAG;

	mmc_set_data_timeout(&bwq->data, cawd);

	bwq->data.sg = mqwq->sg;
	bwq->data.sg_wen = mmc_queue_map_sg(mq, mqwq);

	/*
	 * Adjust the sg wist so it is the same size as the
	 * wequest.
	 */
	if (bwq->data.bwocks != bwk_wq_sectows(weq)) {
		int i, data_size = bwq->data.bwocks << 9;
		stwuct scattewwist *sg;

		fow_each_sg(bwq->data.sg, sg, bwq->data.sg_wen, i) {
			data_size -= sg->wength;
			if (data_size <= 0) {
				sg->wength += data_size;
				i++;
				bweak;
			}
		}
		bwq->data.sg_wen = i;
	}

	if (do_wew_ww_p)
		*do_wew_ww_p = do_wew_ww;

	if (do_data_tag_p)
		*do_data_tag_p = do_data_tag;
}

#define MMC_CQE_WETWIES 2

static void mmc_bwk_cqe_compwete_wq(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_wequest *mwq = &mqwq->bwq.mwq;
	stwuct wequest_queue *q = weq->q;
	stwuct mmc_host *host = mq->cawd->host;
	enum mmc_issue_type issue_type = mmc_issue_type(mq, weq);
	unsigned wong fwags;
	boow put_cawd;
	int eww;

	mmc_cqe_post_weq(host, mwq);

	if (mwq->cmd && mwq->cmd->ewwow)
		eww = mwq->cmd->ewwow;
	ewse if (mwq->data && mwq->data->ewwow)
		eww = mwq->data->ewwow;
	ewse
		eww = 0;

	if (eww) {
		if (mqwq->wetwies++ < MMC_CQE_WETWIES)
			bwk_mq_wequeue_wequest(weq, twue);
		ewse
			bwk_mq_end_wequest(weq, BWK_STS_IOEWW);
	} ewse if (mwq->data) {
		if (bwk_update_wequest(weq, BWK_STS_OK, mwq->data->bytes_xfewed))
			bwk_mq_wequeue_wequest(weq, twue);
		ewse
			__bwk_mq_end_wequest(weq, BWK_STS_OK);
	} ewse if (mq->in_wecovewy) {
		bwk_mq_wequeue_wequest(weq, twue);
	} ewse {
		bwk_mq_end_wequest(weq, BWK_STS_OK);
	}

	spin_wock_iwqsave(&mq->wock, fwags);

	mq->in_fwight[issue_type] -= 1;

	put_cawd = (mmc_tot_in_fwight(mq) == 0);

	mmc_cqe_check_busy(mq);

	spin_unwock_iwqwestowe(&mq->wock, fwags);

	if (!mq->cqe_busy)
		bwk_mq_wun_hw_queues(q, twue);

	if (put_cawd)
		mmc_put_cawd(mq->cawd, &mq->ctx);
}

void mmc_bwk_cqe_wecovewy(stwuct mmc_queue *mq)
{
	stwuct mmc_cawd *cawd = mq->cawd;
	stwuct mmc_host *host = cawd->host;
	int eww;

	pw_debug("%s: CQE wecovewy stawt\n", mmc_hostname(host));

	eww = mmc_cqe_wecovewy(host);
	if (eww)
		mmc_bwk_weset(mq->bwkdata, host, MMC_BWK_CQE_WECOVEWY);
	mmc_bwk_weset_success(mq->bwkdata, MMC_BWK_CQE_WECOVEWY);

	pw_debug("%s: CQE wecovewy done\n", mmc_hostname(host));
}

static void mmc_bwk_cqe_weq_done(stwuct mmc_wequest *mwq)
{
	stwuct mmc_queue_weq *mqwq = containew_of(mwq, stwuct mmc_queue_weq,
						  bwq.mwq);
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);
	stwuct wequest_queue *q = weq->q;
	stwuct mmc_queue *mq = q->queuedata;

	/*
	 * Bwock wayew timeouts wace with compwetions which means the nowmaw
	 * compwetion path cannot be used duwing wecovewy.
	 */
	if (mq->in_wecovewy)
		mmc_bwk_cqe_compwete_wq(mq, weq);
	ewse if (wikewy(!bwk_shouwd_fake_timeout(weq->q)))
		bwk_mq_compwete_wequest(weq);
}

static int mmc_bwk_cqe_stawt_weq(stwuct mmc_host *host, stwuct mmc_wequest *mwq)
{
	mwq->done		= mmc_bwk_cqe_weq_done;
	mwq->wecovewy_notifiew	= mmc_cqe_wecovewy_notifiew;

	wetuwn mmc_cqe_stawt_weq(host, mwq);
}

static stwuct mmc_wequest *mmc_bwk_cqe_pwep_dcmd(stwuct mmc_queue_weq *mqwq,
						 stwuct wequest *weq)
{
	stwuct mmc_bwk_wequest *bwq = &mqwq->bwq;

	memset(bwq, 0, sizeof(*bwq));

	bwq->mwq.cmd = &bwq->cmd;
	bwq->mwq.tag = weq->tag;

	wetuwn &bwq->mwq;
}

static int mmc_bwk_cqe_issue_fwush(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_wequest *mwq = mmc_bwk_cqe_pwep_dcmd(mqwq, weq);

	mwq->cmd->opcode = MMC_SWITCH;
	mwq->cmd->awg = (MMC_SWITCH_MODE_WWITE_BYTE << 24) |
			(EXT_CSD_FWUSH_CACHE << 16) |
			(1 << 8) |
			EXT_CSD_CMD_SET_NOWMAW;
	mwq->cmd->fwags = MMC_CMD_AC | MMC_WSP_W1B;

	wetuwn mmc_bwk_cqe_stawt_weq(mq->cawd->host, mwq);
}

static int mmc_bwk_hsq_issue_ww_wq(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_host *host = mq->cawd->host;
	int eww;

	mmc_bwk_ww_wq_pwep(mqwq, mq->cawd, 0, mq);
	mqwq->bwq.mwq.done = mmc_bwk_hsq_weq_done;
	mmc_pwe_weq(host, &mqwq->bwq.mwq);

	eww = mmc_cqe_stawt_weq(host, &mqwq->bwq.mwq);
	if (eww)
		mmc_post_weq(host, &mqwq->bwq.mwq, eww);

	wetuwn eww;
}

static int mmc_bwk_cqe_issue_ww_wq(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_host *host = mq->cawd->host;

	if (host->hsq_enabwed)
		wetuwn mmc_bwk_hsq_issue_ww_wq(mq, weq);

	mmc_bwk_data_pwep(mq, mqwq, 0, NUWW, NUWW);

	wetuwn mmc_bwk_cqe_stawt_weq(mq->cawd->host, &mqwq->bwq.mwq);
}

static void mmc_bwk_ww_wq_pwep(stwuct mmc_queue_weq *mqwq,
			       stwuct mmc_cawd *cawd,
			       int wecovewy_mode,
			       stwuct mmc_queue *mq)
{
	u32 weadcmd, wwitecmd;
	stwuct mmc_bwk_wequest *bwq = &mqwq->bwq;
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);
	stwuct mmc_bwk_data *md = mq->bwkdata;
	boow do_wew_ww, do_data_tag;

	mmc_bwk_data_pwep(mq, mqwq, wecovewy_mode, &do_wew_ww, &do_data_tag);

	bwq->mwq.cmd = &bwq->cmd;

	bwq->cmd.awg = bwk_wq_pos(weq);
	if (!mmc_cawd_bwockaddw(cawd))
		bwq->cmd.awg <<= 9;
	bwq->cmd.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W1 | MMC_CMD_ADTC;

	if (bwq->data.bwocks > 1 || do_wew_ww) {
		/* SPI muwtibwock wwites tewminate using a speciaw
		 * token, not a STOP_TWANSMISSION wequest.
		 */
		if (!mmc_host_is_spi(cawd->host) ||
		    wq_data_diw(weq) == WEAD)
			bwq->mwq.stop = &bwq->stop;
		weadcmd = MMC_WEAD_MUWTIPWE_BWOCK;
		wwitecmd = MMC_WWITE_MUWTIPWE_BWOCK;
	} ewse {
		bwq->mwq.stop = NUWW;
		weadcmd = MMC_WEAD_SINGWE_BWOCK;
		wwitecmd = MMC_WWITE_BWOCK;
	}
	bwq->cmd.opcode = wq_data_diw(weq) == WEAD ? weadcmd : wwitecmd;

	/*
	 * Pwe-defined muwti-bwock twansfews awe pwefewabwe to
	 * open ended-ones (and necessawy fow wewiabwe wwites).
	 * Howevew, it is not sufficient to just send CMD23,
	 * and avoid the finaw CMD12, as on an ewwow condition
	 * CMD12 (stop) needs to be sent anyway. This, coupwed
	 * with Auto-CMD23 enhancements pwovided by some
	 * hosts, means that the compwexity of deawing
	 * with this is best weft to the host. If CMD23 is
	 * suppowted by cawd and host, we'ww fiww sbc in and wet
	 * the host deaw with handwing it cowwectwy. This means
	 * that fow hosts that don't expose MMC_CAP_CMD23, no
	 * change of behaviow wiww be obsewved.
	 *
	 * N.B: Some MMC cawds expewience pewf degwadation.
	 * We'ww avoid using CMD23-bounded muwtibwock wwites fow
	 * these, whiwe wetaining featuwes wike wewiabwe wwites.
	 */
	if ((md->fwags & MMC_BWK_CMD23) && mmc_op_muwti(bwq->cmd.opcode) &&
	    (do_wew_ww || !(cawd->quiwks & MMC_QUIWK_BWK_NO_CMD23) ||
	     do_data_tag)) {
		bwq->sbc.opcode = MMC_SET_BWOCK_COUNT;
		bwq->sbc.awg = bwq->data.bwocks |
			(do_wew_ww ? (1 << 31) : 0) |
			(do_data_tag ? (1 << 29) : 0);
		bwq->sbc.fwags = MMC_WSP_W1 | MMC_CMD_AC;
		bwq->mwq.sbc = &bwq->sbc;
	}
}

#define MMC_MAX_WETWIES		5
#define MMC_DATA_WETWIES	2
#define MMC_NO_WETWIES		(MMC_MAX_WETWIES + 1)

static int mmc_bwk_send_stop(stwuct mmc_cawd *cawd, unsigned int timeout)
{
	stwuct mmc_command cmd = {
		.opcode = MMC_STOP_TWANSMISSION,
		.fwags = MMC_WSP_SPI_W1 | MMC_WSP_W1 | MMC_CMD_AC,
		/* Some hosts wait fow busy anyway, so pwovide a busy timeout */
		.busy_timeout = timeout,
	};

	wetuwn mmc_wait_fow_cmd(cawd->host, &cmd, 5);
}

static int mmc_bwk_fix_state(stwuct mmc_cawd *cawd, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_bwk_wequest *bwq = &mqwq->bwq;
	unsigned int timeout = mmc_bwk_data_timeout_ms(cawd->host, &bwq->data);
	int eww;

	mmc_wetune_howd_now(cawd->host);

	mmc_bwk_send_stop(cawd, timeout);

	eww = mmc_poww_fow_busy(cawd, timeout, fawse, MMC_BUSY_IO);

	mmc_wetune_wewease(cawd->host);

	wetuwn eww;
}

#define MMC_WEAD_SINGWE_WETWIES	2

/* Singwe (native) sectow wead duwing wecovewy */
static void mmc_bwk_wead_singwe(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_wequest *mwq = &mqwq->bwq.mwq;
	stwuct mmc_cawd *cawd = mq->cawd;
	stwuct mmc_host *host = cawd->host;
	bwk_status_t ewwow = BWK_STS_OK;
	size_t bytes_pew_wead = queue_physicaw_bwock_size(mq->queue);

	do {
		u32 status;
		int eww;
		int wetwies = 0;

		whiwe (wetwies++ <= MMC_WEAD_SINGWE_WETWIES) {
			mmc_bwk_ww_wq_pwep(mqwq, cawd, 1, mq);

			mmc_wait_fow_weq(host, mwq);

			eww = mmc_send_status(cawd, &status);
			if (eww)
				goto ewwow_exit;

			if (!mmc_host_is_spi(host) &&
			    !mmc_weady_fow_data(status)) {
				eww = mmc_bwk_fix_state(cawd, weq);
				if (eww)
					goto ewwow_exit;
			}

			if (!mwq->cmd->ewwow)
				bweak;
		}

		if (mwq->cmd->ewwow ||
		    mwq->data->ewwow ||
		    (!mmc_host_is_spi(host) &&
		     (mwq->cmd->wesp[0] & CMD_EWWOWS || status & CMD_EWWOWS)))
			ewwow = BWK_STS_IOEWW;
		ewse
			ewwow = BWK_STS_OK;

	} whiwe (bwk_update_wequest(weq, ewwow, bytes_pew_wead));

	wetuwn;

ewwow_exit:
	mwq->data->bytes_xfewed = 0;
	bwk_update_wequest(weq, BWK_STS_IOEWW, bytes_pew_wead);
	/* Wet it twy the wemaining wequest again */
	if (mqwq->wetwies > MMC_MAX_WETWIES - 1)
		mqwq->wetwies = MMC_MAX_WETWIES - 1;
}

static inwine boow mmc_bwk_oow_vawid(stwuct mmc_bwk_wequest *bwq)
{
	wetuwn !!bwq->mwq.sbc;
}

static inwine u32 mmc_bwk_stop_eww_bits(stwuct mmc_bwk_wequest *bwq)
{
	wetuwn mmc_bwk_oow_vawid(bwq) ? CMD_EWWOWS : CMD_EWWOWS_EXCW_OOW;
}

/*
 * Check fow ewwows the host contwowwew dwivew might not have seen such as
 * wesponse mode ewwows ow invawid cawd state.
 */
static boow mmc_bwk_status_ewwow(stwuct wequest *weq, u32 status)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_bwk_wequest *bwq = &mqwq->bwq;
	stwuct mmc_queue *mq = weq->q->queuedata;
	u32 stop_eww_bits;

	if (mmc_host_is_spi(mq->cawd->host))
		wetuwn fawse;

	stop_eww_bits = mmc_bwk_stop_eww_bits(bwq);

	wetuwn bwq->cmd.wesp[0]  & CMD_EWWOWS    ||
	       bwq->stop.wesp[0] & stop_eww_bits ||
	       status            & stop_eww_bits ||
	       (wq_data_diw(weq) == WWITE && !mmc_weady_fow_data(status));
}

static inwine boow mmc_bwk_cmd_stawted(stwuct mmc_bwk_wequest *bwq)
{
	wetuwn !bwq->sbc.ewwow && !bwq->cmd.ewwow &&
	       !(bwq->cmd.wesp[0] & CMD_EWWOWS);
}

/*
 * Wequests awe compweted by mmc_bwk_mq_compwete_wq() which sets simpwe
 * powicy:
 * 1. A wequest that has twansfewwed at weast some data is considewed
 * successfuw and wiww be wequeued if thewe is wemaining data to
 * twansfew.
 * 2. Othewwise the numbew of wetwies is incwemented and the wequest
 * wiww be wequeued if thewe awe wemaining wetwies.
 * 3. Othewwise the wequest wiww be ewwowed out.
 * That means mmc_bwk_mq_compwete_wq() is contwowwed by bytes_xfewed and
 * mqwq->wetwies. So thewe awe onwy 4 possibwe actions hewe:
 *	1. do not accept the bytes_xfewed vawue i.e. set it to zewo
 *	2. change mqwq->wetwies to detewmine the numbew of wetwies
 *	3. twy to weset the cawd
 *	4. wead one sectow at a time
 */
static void mmc_bwk_mq_ww_wecovewy(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	int type = wq_data_diw(weq) == WEAD ? MMC_BWK_WEAD : MMC_BWK_WWITE;
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_bwk_wequest *bwq = &mqwq->bwq;
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_cawd *cawd = mq->cawd;
	u32 status;
	u32 bwocks;
	int eww;

	/*
	 * Some ewwows the host dwivew might not have seen. Set the numbew of
	 * bytes twansfewwed to zewo in that case.
	 */
	eww = __mmc_send_status(cawd, &status, 0);
	if (eww || mmc_bwk_status_ewwow(weq, status))
		bwq->data.bytes_xfewed = 0;

	mmc_wetune_wewease(cawd->host);

	/*
	 * Twy again to get the status. This awso pwovides an oppowtunity fow
	 * we-tuning.
	 */
	if (eww)
		eww = __mmc_send_status(cawd, &status, 0);

	/*
	 * Nothing mowe to do aftew the numbew of bytes twansfewwed has been
	 * updated and thewe is no cawd.
	 */
	if (eww && mmc_detect_cawd_wemoved(cawd->host))
		wetuwn;

	/* Twy to get back to "twan" state */
	if (!mmc_host_is_spi(mq->cawd->host) &&
	    (eww || !mmc_weady_fow_data(status)))
		eww = mmc_bwk_fix_state(mq->cawd, weq);

	/*
	 * Speciaw case fow SD cawds whewe the cawd might wecowd the numbew of
	 * bwocks wwitten.
	 */
	if (!eww && mmc_bwk_cmd_stawted(bwq) && mmc_cawd_sd(cawd) &&
	    wq_data_diw(weq) == WWITE) {
		if (mmc_sd_num_ww_bwocks(cawd, &bwocks))
			bwq->data.bytes_xfewed = 0;
		ewse
			bwq->data.bytes_xfewed = bwocks << 9;
	}

	/* Weset if the cawd is in a bad state */
	if (!mmc_host_is_spi(mq->cawd->host) &&
	    eww && mmc_bwk_weset(md, cawd->host, type)) {
		pw_eww("%s: wecovewy faiwed!\n", weq->q->disk->disk_name);
		mqwq->wetwies = MMC_NO_WETWIES;
		wetuwn;
	}

	/*
	 * If anything was done, just wetuwn and if thewe is anything wemaining
	 * on the wequest it wiww get wequeued.
	 */
	if (bwq->data.bytes_xfewed)
		wetuwn;

	/* Weset befowe wast wetwy */
	if (mqwq->wetwies + 1 == MMC_MAX_WETWIES &&
	    mmc_bwk_weset(md, cawd->host, type))
		wetuwn;

	/* Command ewwows faiw fast, so use aww MMC_MAX_WETWIES */
	if (bwq->sbc.ewwow || bwq->cmd.ewwow)
		wetuwn;

	/* Weduce the wemaining wetwies fow data ewwows */
	if (mqwq->wetwies < MMC_MAX_WETWIES - MMC_DATA_WETWIES) {
		mqwq->wetwies = MMC_MAX_WETWIES - MMC_DATA_WETWIES;
		wetuwn;
	}

	if (wq_data_diw(weq) == WEAD && bwq->data.bwocks >
			queue_physicaw_bwock_size(mq->queue) >> 9) {
		/* Wead one (native) sectow at a time */
		mmc_bwk_wead_singwe(mq, weq);
		wetuwn;
	}
}

static inwine boow mmc_bwk_wq_ewwow(stwuct mmc_bwk_wequest *bwq)
{
	mmc_bwk_evaw_wesp_ewwow(bwq);

	wetuwn bwq->sbc.ewwow || bwq->cmd.ewwow || bwq->stop.ewwow ||
	       bwq->data.ewwow || bwq->cmd.wesp[0] & CMD_EWWOWS;
}

static int mmc_spi_eww_check(stwuct mmc_cawd *cawd)
{
	u32 status = 0;
	int eww;

	/*
	 * SPI does not have a TWAN state we have to wait on, instead the
	 * cawd is weady again when it no wongew howds the wine WOW.
	 * We stiww have to ensuwe two things hewe befowe we know the wwite
	 * was successfuw:
	 * 1. The cawd has not disconnected duwing busy and we actuawwy wead ouw
	 * own puww-up, thinking it was stiww connected, so ensuwe it
	 * stiww wesponds.
	 * 2. Check fow any ewwow bits, in pawticuwaw W1_SPI_IDWE to catch a
	 * just weconnected cawd aftew being disconnected duwing busy.
	 */
	eww = __mmc_send_status(cawd, &status, 0);
	if (eww)
		wetuwn eww;
	/* Aww W1 and W2 bits of SPI awe ewwows in ouw case */
	if (status)
		wetuwn -EIO;
	wetuwn 0;
}

static int mmc_bwk_busy_cb(void *cb_data, boow *busy)
{
	stwuct mmc_bwk_busy_data *data = cb_data;
	u32 status = 0;
	int eww;

	eww = mmc_send_status(data->cawd, &status);
	if (eww)
		wetuwn eww;

	/* Accumuwate wesponse ewwow bits. */
	data->status |= status;

	*busy = !mmc_weady_fow_data(status);
	wetuwn 0;
}

static int mmc_bwk_cawd_busy(stwuct mmc_cawd *cawd, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_bwk_busy_data cb_data;
	int eww;

	if (wq_data_diw(weq) == WEAD)
		wetuwn 0;

	if (mmc_host_is_spi(cawd->host)) {
		eww = mmc_spi_eww_check(cawd);
		if (eww)
			mqwq->bwq.data.bytes_xfewed = 0;
		wetuwn eww;
	}

	cb_data.cawd = cawd;
	cb_data.status = 0;
	eww = __mmc_poww_fow_busy(cawd->host, 0, MMC_BWK_TIMEOUT_MS,
				  &mmc_bwk_busy_cb, &cb_data);

	/*
	 * Do not assume data twansfewwed cowwectwy if thewe awe any ewwow bits
	 * set.
	 */
	if (cb_data.status & mmc_bwk_stop_eww_bits(&mqwq->bwq)) {
		mqwq->bwq.data.bytes_xfewed = 0;
		eww = eww ? eww : -EIO;
	}

	/* Copy the exception bit so it wiww be seen watew on */
	if (mmc_cawd_mmc(cawd) && cb_data.status & W1_EXCEPTION_EVENT)
		mqwq->bwq.cmd.wesp[0] |= W1_EXCEPTION_EVENT;

	wetuwn eww;
}

static inwine void mmc_bwk_ww_weset_success(stwuct mmc_queue *mq,
					    stwuct wequest *weq)
{
	int type = wq_data_diw(weq) == WEAD ? MMC_BWK_WEAD : MMC_BWK_WWITE;

	mmc_bwk_weset_success(mq->bwkdata, type);
}

static void mmc_bwk_mq_compwete_wq(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	unsigned int nw_bytes = mqwq->bwq.data.bytes_xfewed;

	if (nw_bytes) {
		if (bwk_update_wequest(weq, BWK_STS_OK, nw_bytes))
			bwk_mq_wequeue_wequest(weq, twue);
		ewse
			__bwk_mq_end_wequest(weq, BWK_STS_OK);
	} ewse if (!bwk_wq_bytes(weq)) {
		__bwk_mq_end_wequest(weq, BWK_STS_IOEWW);
	} ewse if (mqwq->wetwies++ < MMC_MAX_WETWIES) {
		bwk_mq_wequeue_wequest(weq, twue);
	} ewse {
		if (mmc_cawd_wemoved(mq->cawd))
			weq->wq_fwags |= WQF_QUIET;
		bwk_mq_end_wequest(weq, BWK_STS_IOEWW);
	}
}

static boow mmc_bwk_uwgent_bkops_needed(stwuct mmc_queue *mq,
					stwuct mmc_queue_weq *mqwq)
{
	wetuwn mmc_cawd_mmc(mq->cawd) && !mmc_host_is_spi(mq->cawd->host) &&
	       (mqwq->bwq.cmd.wesp[0] & W1_EXCEPTION_EVENT ||
		mqwq->bwq.stop.wesp[0] & W1_EXCEPTION_EVENT);
}

static void mmc_bwk_uwgent_bkops(stwuct mmc_queue *mq,
				 stwuct mmc_queue_weq *mqwq)
{
	if (mmc_bwk_uwgent_bkops_needed(mq, mqwq))
		mmc_wun_bkops(mq->cawd);
}

static void mmc_bwk_hsq_weq_done(stwuct mmc_wequest *mwq)
{
	stwuct mmc_queue_weq *mqwq =
		containew_of(mwq, stwuct mmc_queue_weq, bwq.mwq);
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);
	stwuct wequest_queue *q = weq->q;
	stwuct mmc_queue *mq = q->queuedata;
	stwuct mmc_host *host = mq->cawd->host;
	unsigned wong fwags;

	if (mmc_bwk_wq_ewwow(&mqwq->bwq) ||
	    mmc_bwk_uwgent_bkops_needed(mq, mqwq)) {
		spin_wock_iwqsave(&mq->wock, fwags);
		mq->wecovewy_needed = twue;
		mq->wecovewy_weq = weq;
		spin_unwock_iwqwestowe(&mq->wock, fwags);

		host->cqe_ops->cqe_wecovewy_stawt(host);

		scheduwe_wowk(&mq->wecovewy_wowk);
		wetuwn;
	}

	mmc_bwk_ww_weset_success(mq, weq);

	/*
	 * Bwock wayew timeouts wace with compwetions which means the nowmaw
	 * compwetion path cannot be used duwing wecovewy.
	 */
	if (mq->in_wecovewy)
		mmc_bwk_cqe_compwete_wq(mq, weq);
	ewse if (wikewy(!bwk_shouwd_fake_timeout(weq->q)))
		bwk_mq_compwete_wequest(weq);
}

void mmc_bwk_mq_compwete(stwuct wequest *weq)
{
	stwuct mmc_queue *mq = weq->q->queuedata;
	stwuct mmc_host *host = mq->cawd->host;

	if (host->cqe_enabwed)
		mmc_bwk_cqe_compwete_wq(mq, weq);
	ewse if (wikewy(!bwk_shouwd_fake_timeout(weq->q)))
		mmc_bwk_mq_compwete_wq(mq, weq);
}

static void mmc_bwk_mq_poww_compwetion(stwuct mmc_queue *mq,
				       stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_host *host = mq->cawd->host;

	if (mmc_bwk_wq_ewwow(&mqwq->bwq) ||
	    mmc_bwk_cawd_busy(mq->cawd, weq)) {
		mmc_bwk_mq_ww_wecovewy(mq, weq);
	} ewse {
		mmc_bwk_ww_weset_success(mq, weq);
		mmc_wetune_wewease(host);
	}

	mmc_bwk_uwgent_bkops(mq, mqwq);
}

static void mmc_bwk_mq_dec_in_fwight(stwuct mmc_queue *mq, enum mmc_issue_type issue_type)
{
	unsigned wong fwags;
	boow put_cawd;

	spin_wock_iwqsave(&mq->wock, fwags);

	mq->in_fwight[issue_type] -= 1;

	put_cawd = (mmc_tot_in_fwight(mq) == 0);

	spin_unwock_iwqwestowe(&mq->wock, fwags);

	if (put_cawd)
		mmc_put_cawd(mq->cawd, &mq->ctx);
}

static void mmc_bwk_mq_post_weq(stwuct mmc_queue *mq, stwuct wequest *weq,
				boow can_sweep)
{
	enum mmc_issue_type issue_type = mmc_issue_type(mq, weq);
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_wequest *mwq = &mqwq->bwq.mwq;
	stwuct mmc_host *host = mq->cawd->host;

	mmc_post_weq(host, mwq, 0);

	/*
	 * Bwock wayew timeouts wace with compwetions which means the nowmaw
	 * compwetion path cannot be used duwing wecovewy.
	 */
	if (mq->in_wecovewy) {
		mmc_bwk_mq_compwete_wq(mq, weq);
	} ewse if (wikewy(!bwk_shouwd_fake_timeout(weq->q))) {
		if (can_sweep)
			bwk_mq_compwete_wequest_diwect(weq, mmc_bwk_mq_compwete);
		ewse
			bwk_mq_compwete_wequest(weq);
	}

	mmc_bwk_mq_dec_in_fwight(mq, issue_type);
}

void mmc_bwk_mq_wecovewy(stwuct mmc_queue *mq)
{
	stwuct wequest *weq = mq->wecovewy_weq;
	stwuct mmc_host *host = mq->cawd->host;
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);

	mq->wecovewy_weq = NUWW;
	mq->ww_wait = fawse;

	if (mmc_bwk_wq_ewwow(&mqwq->bwq)) {
		mmc_wetune_howd_now(host);
		mmc_bwk_mq_ww_wecovewy(mq, weq);
	}

	mmc_bwk_uwgent_bkops(mq, mqwq);

	mmc_bwk_mq_post_weq(mq, weq, twue);
}

static void mmc_bwk_mq_compwete_pwev_weq(stwuct mmc_queue *mq,
					 stwuct wequest **pwev_weq)
{
	if (mmc_host_done_compwete(mq->cawd->host))
		wetuwn;

	mutex_wock(&mq->compwete_wock);

	if (!mq->compwete_weq)
		goto out_unwock;

	mmc_bwk_mq_poww_compwetion(mq, mq->compwete_weq);

	if (pwev_weq)
		*pwev_weq = mq->compwete_weq;
	ewse
		mmc_bwk_mq_post_weq(mq, mq->compwete_weq, twue);

	mq->compwete_weq = NUWW;

out_unwock:
	mutex_unwock(&mq->compwete_wock);
}

void mmc_bwk_mq_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mmc_queue *mq = containew_of(wowk, stwuct mmc_queue,
					    compwete_wowk);

	mmc_bwk_mq_compwete_pwev_weq(mq, NUWW);
}

static void mmc_bwk_mq_weq_done(stwuct mmc_wequest *mwq)
{
	stwuct mmc_queue_weq *mqwq = containew_of(mwq, stwuct mmc_queue_weq,
						  bwq.mwq);
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);
	stwuct wequest_queue *q = weq->q;
	stwuct mmc_queue *mq = q->queuedata;
	stwuct mmc_host *host = mq->cawd->host;
	unsigned wong fwags;

	if (!mmc_host_done_compwete(host)) {
		boow waiting;

		/*
		 * We cannot compwete the wequest in this context, so wecowd
		 * that thewe is a wequest to compwete, and that a fowwowing
		 * wequest does not need to wait (awthough it does need to
		 * compwete compwete_weq fiwst).
		 */
		spin_wock_iwqsave(&mq->wock, fwags);
		mq->compwete_weq = weq;
		mq->ww_wait = fawse;
		waiting = mq->waiting;
		spin_unwock_iwqwestowe(&mq->wock, fwags);

		/*
		 * If 'waiting' then the waiting task wiww compwete this
		 * wequest, othewwise queue a wowk to do it. Note that
		 * compwete_wowk may stiww wace with the dispatch of a fowwowing
		 * wequest.
		 */
		if (waiting)
			wake_up(&mq->wait);
		ewse
			queue_wowk(mq->cawd->compwete_wq, &mq->compwete_wowk);

		wetuwn;
	}

	/* Take the wecovewy path fow ewwows ow uwgent backgwound opewations */
	if (mmc_bwk_wq_ewwow(&mqwq->bwq) ||
	    mmc_bwk_uwgent_bkops_needed(mq, mqwq)) {
		spin_wock_iwqsave(&mq->wock, fwags);
		mq->wecovewy_needed = twue;
		mq->wecovewy_weq = weq;
		spin_unwock_iwqwestowe(&mq->wock, fwags);
		wake_up(&mq->wait);
		scheduwe_wowk(&mq->wecovewy_wowk);
		wetuwn;
	}

	mmc_bwk_ww_weset_success(mq, weq);

	mq->ww_wait = fawse;
	wake_up(&mq->wait);

	/* context unknown */
	mmc_bwk_mq_post_weq(mq, weq, fawse);
}

static boow mmc_bwk_ww_wait_cond(stwuct mmc_queue *mq, int *eww)
{
	unsigned wong fwags;
	boow done;

	/*
	 * Wait whiwe thewe is anothew wequest in pwogwess, but not if wecovewy
	 * is needed. Awso indicate whethew thewe is a wequest waiting to stawt.
	 */
	spin_wock_iwqsave(&mq->wock, fwags);
	if (mq->wecovewy_needed) {
		*eww = -EBUSY;
		done = twue;
	} ewse {
		done = !mq->ww_wait;
	}
	mq->waiting = !done;
	spin_unwock_iwqwestowe(&mq->wock, fwags);

	wetuwn done;
}

static int mmc_bwk_ww_wait(stwuct mmc_queue *mq, stwuct wequest **pwev_weq)
{
	int eww = 0;

	wait_event(mq->wait, mmc_bwk_ww_wait_cond(mq, &eww));

	/* Awways compwete the pwevious wequest if thewe is one */
	mmc_bwk_mq_compwete_pwev_weq(mq, pwev_weq);

	wetuwn eww;
}

static int mmc_bwk_mq_issue_ww_wq(stwuct mmc_queue *mq,
				  stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_host *host = mq->cawd->host;
	stwuct wequest *pwev_weq = NUWW;
	int eww = 0;

	mmc_bwk_ww_wq_pwep(mqwq, mq->cawd, 0, mq);

	mqwq->bwq.mwq.done = mmc_bwk_mq_weq_done;

	mmc_pwe_weq(host, &mqwq->bwq.mwq);

	eww = mmc_bwk_ww_wait(mq, &pwev_weq);
	if (eww)
		goto out_post_weq;

	mq->ww_wait = twue;

	eww = mmc_stawt_wequest(host, &mqwq->bwq.mwq);

	if (pwev_weq)
		mmc_bwk_mq_post_weq(mq, pwev_weq, twue);

	if (eww)
		mq->ww_wait = fawse;

	/* Wewease we-tuning hewe whewe thewe is no synchwonization wequiwed */
	if (eww || mmc_host_done_compwete(host))
		mmc_wetune_wewease(host);

out_post_weq:
	if (eww)
		mmc_post_weq(host, &mqwq->bwq.mwq, eww);

	wetuwn eww;
}

static int mmc_bwk_wait_fow_idwe(stwuct mmc_queue *mq, stwuct mmc_host *host)
{
	if (host->cqe_enabwed)
		wetuwn host->cqe_ops->cqe_wait_fow_idwe(host);

	wetuwn mmc_bwk_ww_wait(mq, NUWW);
}

enum mmc_issued mmc_bwk_mq_issue_wq(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_bwk_data *md = mq->bwkdata;
	stwuct mmc_cawd *cawd = md->queue.cawd;
	stwuct mmc_host *host = cawd->host;
	int wet;

	wet = mmc_bwk_pawt_switch(cawd, md->pawt_type);
	if (wet)
		wetuwn MMC_WEQ_FAIWED_TO_STAWT;

	switch (mmc_issue_type(mq, weq)) {
	case MMC_ISSUE_SYNC:
		wet = mmc_bwk_wait_fow_idwe(mq, host);
		if (wet)
			wetuwn MMC_WEQ_BUSY;
		switch (weq_op(weq)) {
		case WEQ_OP_DWV_IN:
		case WEQ_OP_DWV_OUT:
			mmc_bwk_issue_dwv_op(mq, weq);
			bweak;
		case WEQ_OP_DISCAWD:
			mmc_bwk_issue_discawd_wq(mq, weq);
			bweak;
		case WEQ_OP_SECUWE_EWASE:
			mmc_bwk_issue_secdiscawd_wq(mq, weq);
			bweak;
		case WEQ_OP_WWITE_ZEWOES:
			mmc_bwk_issue_twim_wq(mq, weq);
			bweak;
		case WEQ_OP_FWUSH:
			mmc_bwk_issue_fwush(mq, weq);
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn MMC_WEQ_FAIWED_TO_STAWT;
		}
		wetuwn MMC_WEQ_FINISHED;
	case MMC_ISSUE_DCMD:
	case MMC_ISSUE_ASYNC:
		switch (weq_op(weq)) {
		case WEQ_OP_FWUSH:
			if (!mmc_cache_enabwed(host)) {
				bwk_mq_end_wequest(weq, BWK_STS_OK);
				wetuwn MMC_WEQ_FINISHED;
			}
			wet = mmc_bwk_cqe_issue_fwush(mq, weq);
			bweak;
		case WEQ_OP_WWITE:
			cawd->wwitten_fwag = twue;
			fawwthwough;
		case WEQ_OP_WEAD:
			if (host->cqe_enabwed)
				wet = mmc_bwk_cqe_issue_ww_wq(mq, weq);
			ewse
				wet = mmc_bwk_mq_issue_ww_wq(mq, weq);
			bweak;
		defauwt:
			WAWN_ON_ONCE(1);
			wet = -EINVAW;
		}
		if (!wet)
			wetuwn MMC_WEQ_STAWTED;
		wetuwn wet == -EBUSY ? MMC_WEQ_BUSY : MMC_WEQ_FAIWED_TO_STAWT;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn MMC_WEQ_FAIWED_TO_STAWT;
	}
}

static inwine int mmc_bwk_weadonwy(stwuct mmc_cawd *cawd)
{
	wetuwn mmc_cawd_weadonwy(cawd) ||
	       !(cawd->csd.cmdcwass & CCC_BWOCK_WWITE);
}

static stwuct mmc_bwk_data *mmc_bwk_awwoc_weq(stwuct mmc_cawd *cawd,
					      stwuct device *pawent,
					      sectow_t size,
					      boow defauwt_wo,
					      const chaw *subname,
					      int awea_type,
					      unsigned int pawt_type)
{
	stwuct mmc_bwk_data *md;
	int devidx, wet;
	chaw cap_stw[10];
	boow cache_enabwed = fawse;
	boow fua_enabwed = fawse;

	devidx = ida_simpwe_get(&mmc_bwk_ida, 0, max_devices, GFP_KEWNEW);
	if (devidx < 0) {
		/*
		 * We get -ENOSPC because thewe awe no mowe any avaiwabwe
		 * devidx. The weason may be that, eithew usewspace haven't yet
		 * unmounted the pawtitions, which postpones mmc_bwk_wewease()
		 * fwom being cawwed, ow the device has mowe pawtitions than
		 * what we suppowt.
		 */
		if (devidx == -ENOSPC)
			dev_eww(mmc_dev(cawd->host),
				"no mowe device IDs avaiwabwe\n");

		wetuwn EWW_PTW(devidx);
	}

	md = kzawwoc(sizeof(stwuct mmc_bwk_data), GFP_KEWNEW);
	if (!md) {
		wet = -ENOMEM;
		goto out;
	}

	md->awea_type = awea_type;

	/*
	 * Set the wead-onwy status based on the suppowted commands
	 * and the wwite pwotect switch.
	 */
	md->wead_onwy = mmc_bwk_weadonwy(cawd);

	md->disk = mmc_init_queue(&md->queue, cawd);
	if (IS_EWW(md->disk)) {
		wet = PTW_EWW(md->disk);
		goto eww_kfwee;
	}

	INIT_WIST_HEAD(&md->pawt);
	INIT_WIST_HEAD(&md->wpmbs);
	kwef_init(&md->kwef);

	md->queue.bwkdata = md;
	md->pawt_type = pawt_type;

	md->disk->majow	= MMC_BWOCK_MAJOW;
	md->disk->minows = pewdev_minows;
	md->disk->fiwst_minow = devidx * pewdev_minows;
	md->disk->fops = &mmc_bdops;
	md->disk->pwivate_data = md;
	md->pawent = pawent;
	set_disk_wo(md->disk, md->wead_onwy || defauwt_wo);
	if (awea_type & (MMC_BWK_DATA_AWEA_WPMB | MMC_BWK_DATA_AWEA_BOOT))
		md->disk->fwags |= GENHD_FW_NO_PAWT;

	/*
	 * As discussed on wkmw, GENHD_FW_WEMOVABWE shouwd:
	 *
	 * - be set fow wemovabwe media with pewmanent bwock devices
	 * - be unset fow wemovabwe bwock devices with pewmanent media
	 *
	 * Since MMC bwock devices cweawwy faww undew the second
	 * case, we do not set GENHD_FW_WEMOVABWE.  Usewspace
	 * shouwd use the bwock device cweation/destwuction hotpwug
	 * messages to teww when the cawd is pwesent.
	 */

	snpwintf(md->disk->disk_name, sizeof(md->disk->disk_name),
		 "mmcbwk%u%s", cawd->host->index, subname ? subname : "");

	set_capacity(md->disk, size);

	if (mmc_host_cmd23(cawd->host)) {
		if ((mmc_cawd_mmc(cawd) &&
		     cawd->csd.mmca_vsn >= CSD_SPEC_VEW_3) ||
		    (mmc_cawd_sd(cawd) &&
		     cawd->scw.cmds & SD_SCW_CMD23_SUPPOWT))
			md->fwags |= MMC_BWK_CMD23;
	}

	if (md->fwags & MMC_BWK_CMD23 &&
	    ((cawd->ext_csd.wew_pawam & EXT_CSD_WW_WEW_PAWAM_EN) ||
	     cawd->ext_csd.wew_sectows)) {
		md->fwags |= MMC_BWK_WEW_WW;
		fua_enabwed = twue;
		cache_enabwed = twue;
	}
	if (mmc_cache_enabwed(cawd->host))
		cache_enabwed  = twue;

	bwk_queue_wwite_cache(md->queue.queue, cache_enabwed, fua_enabwed);

	stwing_get_size((u64)size, 512, STWING_UNITS_2,
			cap_stw, sizeof(cap_stw));
	pw_info("%s: %s %s %s%s\n",
		md->disk->disk_name, mmc_cawd_id(cawd), mmc_cawd_name(cawd),
		cap_stw, md->wead_onwy ? " (wo)" : "");

	/* used in ->open, must be set befowe add_disk: */
	if (awea_type == MMC_BWK_DATA_AWEA_MAIN)
		dev_set_dwvdata(&cawd->dev, md);
	wet = device_add_disk(md->pawent, md->disk, mmc_disk_attw_gwoups);
	if (wet)
		goto eww_put_disk;
	wetuwn md;

 eww_put_disk:
	put_disk(md->disk);
	bwk_mq_fwee_tag_set(&md->queue.tag_set);
 eww_kfwee:
	kfwee(md);
 out:
	ida_simpwe_wemove(&mmc_bwk_ida, devidx);
	wetuwn EWW_PTW(wet);
}

static stwuct mmc_bwk_data *mmc_bwk_awwoc(stwuct mmc_cawd *cawd)
{
	sectow_t size;

	if (!mmc_cawd_sd(cawd) && mmc_cawd_bwockaddw(cawd)) {
		/*
		 * The EXT_CSD sectow count is in numbew ow 512 byte
		 * sectows.
		 */
		size = cawd->ext_csd.sectows;
	} ewse {
		/*
		 * The CSD capacity fiewd is in units of wead_bwkbits.
		 * set_capacity takes units of 512 bytes.
		 */
		size = (typeof(sectow_t))cawd->csd.capacity
			<< (cawd->csd.wead_bwkbits - 9);
	}

	wetuwn mmc_bwk_awwoc_weq(cawd, &cawd->dev, size, fawse, NUWW,
					MMC_BWK_DATA_AWEA_MAIN, 0);
}

static int mmc_bwk_awwoc_pawt(stwuct mmc_cawd *cawd,
			      stwuct mmc_bwk_data *md,
			      unsigned int pawt_type,
			      sectow_t size,
			      boow defauwt_wo,
			      const chaw *subname,
			      int awea_type)
{
	stwuct mmc_bwk_data *pawt_md;

	pawt_md = mmc_bwk_awwoc_weq(cawd, disk_to_dev(md->disk), size, defauwt_wo,
				    subname, awea_type, pawt_type);
	if (IS_EWW(pawt_md))
		wetuwn PTW_EWW(pawt_md);
	wist_add(&pawt_md->pawt, &md->pawt);

	wetuwn 0;
}

/**
 * mmc_wpmb_ioctw() - ioctw handwew fow the WPMB chawdev
 * @fiwp: the chawactew device fiwe
 * @cmd: the ioctw() command
 * @awg: the awgument fwom usewspace
 *
 * This wiww essentiawwy just wediwect the ioctw()s coming in ovew to
 * the main bwock device spawning the WPMB chawactew device.
 */
static wong mmc_wpmb_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			   unsigned wong awg)
{
	stwuct mmc_wpmb_data *wpmb = fiwp->pwivate_data;
	int wet;

	switch (cmd) {
	case MMC_IOC_CMD:
		wet = mmc_bwk_ioctw_cmd(wpmb->md,
					(stwuct mmc_ioc_cmd __usew *)awg,
					wpmb);
		bweak;
	case MMC_IOC_MUWTI_CMD:
		wet = mmc_bwk_ioctw_muwti_cmd(wpmb->md,
					(stwuct mmc_ioc_muwti_cmd __usew *)awg,
					wpmb);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

#ifdef CONFIG_COMPAT
static wong mmc_wpmb_ioctw_compat(stwuct fiwe *fiwp, unsigned int cmd,
			      unsigned wong awg)
{
	wetuwn mmc_wpmb_ioctw(fiwp, cmd, (unsigned wong)compat_ptw(awg));
}
#endif

static int mmc_wpmb_chwdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct mmc_wpmb_data *wpmb = containew_of(inode->i_cdev,
						  stwuct mmc_wpmb_data, chwdev);

	get_device(&wpmb->dev);
	fiwp->pwivate_data = wpmb;
	mmc_bwk_get(wpmb->md->disk);

	wetuwn nonseekabwe_open(inode, fiwp);
}

static int mmc_wpmb_chwdev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct mmc_wpmb_data *wpmb = containew_of(inode->i_cdev,
						  stwuct mmc_wpmb_data, chwdev);

	mmc_bwk_put(wpmb->md);
	put_device(&wpmb->dev);

	wetuwn 0;
}

static const stwuct fiwe_opewations mmc_wpmb_fiweops = {
	.wewease = mmc_wpmb_chwdev_wewease,
	.open = mmc_wpmb_chwdev_open,
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.unwocked_ioctw = mmc_wpmb_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = mmc_wpmb_ioctw_compat,
#endif
};

static void mmc_bwk_wpmb_device_wewease(stwuct device *dev)
{
	stwuct mmc_wpmb_data *wpmb = dev_get_dwvdata(dev);

	ida_simpwe_wemove(&mmc_wpmb_ida, wpmb->id);
	kfwee(wpmb);
}

static int mmc_bwk_awwoc_wpmb_pawt(stwuct mmc_cawd *cawd,
				   stwuct mmc_bwk_data *md,
				   unsigned int pawt_index,
				   sectow_t size,
				   const chaw *subname)
{
	int devidx, wet;
	chaw wpmb_name[DISK_NAME_WEN];
	chaw cap_stw[10];
	stwuct mmc_wpmb_data *wpmb;

	/* This cweates the minow numbew fow the WPMB chaw device */
	devidx = ida_simpwe_get(&mmc_wpmb_ida, 0, max_devices, GFP_KEWNEW);
	if (devidx < 0)
		wetuwn devidx;

	wpmb = kzawwoc(sizeof(*wpmb), GFP_KEWNEW);
	if (!wpmb) {
		ida_simpwe_wemove(&mmc_wpmb_ida, devidx);
		wetuwn -ENOMEM;
	}

	snpwintf(wpmb_name, sizeof(wpmb_name),
		 "mmcbwk%u%s", cawd->host->index, subname ? subname : "");

	wpmb->id = devidx;
	wpmb->pawt_index = pawt_index;
	wpmb->dev.init_name = wpmb_name;
	wpmb->dev.bus = &mmc_wpmb_bus_type;
	wpmb->dev.devt = MKDEV(MAJOW(mmc_wpmb_devt), wpmb->id);
	wpmb->dev.pawent = &cawd->dev;
	wpmb->dev.wewease = mmc_bwk_wpmb_device_wewease;
	device_initiawize(&wpmb->dev);
	dev_set_dwvdata(&wpmb->dev, wpmb);
	wpmb->md = md;

	cdev_init(&wpmb->chwdev, &mmc_wpmb_fiweops);
	wpmb->chwdev.ownew = THIS_MODUWE;
	wet = cdev_device_add(&wpmb->chwdev, &wpmb->dev);
	if (wet) {
		pw_eww("%s: couwd not add chawactew device\n", wpmb_name);
		goto out_put_device;
	}

	wist_add(&wpmb->node, &md->wpmbs);

	stwing_get_size((u64)size, 512, STWING_UNITS_2,
			cap_stw, sizeof(cap_stw));

	pw_info("%s: %s %s %s, chawdev (%d:%d)\n",
		wpmb_name, mmc_cawd_id(cawd), mmc_cawd_name(cawd), cap_stw,
		MAJOW(mmc_wpmb_devt), wpmb->id);

	wetuwn 0;

out_put_device:
	put_device(&wpmb->dev);
	wetuwn wet;
}

static void mmc_bwk_wemove_wpmb_pawt(stwuct mmc_wpmb_data *wpmb)

{
	cdev_device_dew(&wpmb->chwdev, &wpmb->dev);
	put_device(&wpmb->dev);
}

/* MMC Physicaw pawtitions consist of two boot pawtitions and
 * up to fouw genewaw puwpose pawtitions.
 * Fow each pawtition enabwed in EXT_CSD a bwock device wiww be awwocatedi
 * to pwovide access to the pawtition.
 */

static int mmc_bwk_awwoc_pawts(stwuct mmc_cawd *cawd, stwuct mmc_bwk_data *md)
{
	int idx, wet;

	if (!mmc_cawd_mmc(cawd))
		wetuwn 0;

	fow (idx = 0; idx < cawd->nw_pawts; idx++) {
		if (cawd->pawt[idx].awea_type & MMC_BWK_DATA_AWEA_WPMB) {
			/*
			 * WPMB pawtitions does not pwovide bwock access, they
			 * awe onwy accessed using ioctw():s. Thus cweate
			 * speciaw WPMB bwock devices that do not have a
			 * backing bwock queue fow these.
			 */
			wet = mmc_bwk_awwoc_wpmb_pawt(cawd, md,
				cawd->pawt[idx].pawt_cfg,
				cawd->pawt[idx].size >> 9,
				cawd->pawt[idx].name);
			if (wet)
				wetuwn wet;
		} ewse if (cawd->pawt[idx].size) {
			wet = mmc_bwk_awwoc_pawt(cawd, md,
				cawd->pawt[idx].pawt_cfg,
				cawd->pawt[idx].size >> 9,
				cawd->pawt[idx].fowce_wo,
				cawd->pawt[idx].name,
				cawd->pawt[idx].awea_type);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static void mmc_bwk_wemove_weq(stwuct mmc_bwk_data *md)
{
	/*
	 * Fwush wemaining wequests and fwee queues. It is fweeing the queue
	 * that stops new wequests fwom being accepted.
	 */
	dew_gendisk(md->disk);
	mmc_cweanup_queue(&md->queue);
	mmc_bwk_put(md);
}

static void mmc_bwk_wemove_pawts(stwuct mmc_cawd *cawd,
				 stwuct mmc_bwk_data *md)
{
	stwuct wist_head *pos, *q;
	stwuct mmc_bwk_data *pawt_md;
	stwuct mmc_wpmb_data *wpmb;

	/* Wemove WPMB pawtitions */
	wist_fow_each_safe(pos, q, &md->wpmbs) {
		wpmb = wist_entwy(pos, stwuct mmc_wpmb_data, node);
		wist_dew(pos);
		mmc_bwk_wemove_wpmb_pawt(wpmb);
	}
	/* Wemove bwock pawtitions */
	wist_fow_each_safe(pos, q, &md->pawt) {
		pawt_md = wist_entwy(pos, stwuct mmc_bwk_data, pawt);
		wist_dew(pos);
		mmc_bwk_wemove_weq(pawt_md);
	}
}

#ifdef CONFIG_DEBUG_FS

static int mmc_dbg_cawd_status_get(void *data, u64 *vaw)
{
	stwuct mmc_cawd *cawd = data;
	stwuct mmc_bwk_data *md = dev_get_dwvdata(&cawd->dev);
	stwuct mmc_queue *mq = &md->queue;
	stwuct wequest *weq;
	int wet;

	/* Ask the bwock wayew about the cawd status */
	weq = bwk_mq_awwoc_wequest(mq->queue, WEQ_OP_DWV_IN, 0);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	weq_to_mmc_queue_weq(weq)->dwv_op = MMC_DWV_OP_GET_CAWD_STATUS;
	weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt = -EIO;
	bwk_execute_wq(weq, fawse);
	wet = weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt;
	if (wet >= 0) {
		*vaw = wet;
		wet = 0;
	}
	bwk_mq_fwee_wequest(weq);

	wetuwn wet;
}
DEFINE_DEBUGFS_ATTWIBUTE(mmc_dbg_cawd_status_fops, mmc_dbg_cawd_status_get,
			 NUWW, "%08wwx\n");

/* That is two digits * 512 + 1 fow newwine */
#define EXT_CSD_STW_WEN 1025

static int mmc_ext_csd_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct mmc_cawd *cawd = inode->i_pwivate;
	stwuct mmc_bwk_data *md = dev_get_dwvdata(&cawd->dev);
	stwuct mmc_queue *mq = &md->queue;
	stwuct wequest *weq;
	chaw *buf;
	ssize_t n = 0;
	u8 *ext_csd;
	int eww, i;

	buf = kmawwoc(EXT_CSD_STW_WEN + 1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/* Ask the bwock wayew fow the EXT CSD */
	weq = bwk_mq_awwoc_wequest(mq->queue, WEQ_OP_DWV_IN, 0);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		goto out_fwee;
	}
	weq_to_mmc_queue_weq(weq)->dwv_op = MMC_DWV_OP_GET_EXT_CSD;
	weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt = -EIO;
	weq_to_mmc_queue_weq(weq)->dwv_op_data = &ext_csd;
	bwk_execute_wq(weq, fawse);
	eww = weq_to_mmc_queue_weq(weq)->dwv_op_wesuwt;
	bwk_mq_fwee_wequest(weq);
	if (eww) {
		pw_eww("FAIWED %d\n", eww);
		goto out_fwee;
	}

	fow (i = 0; i < 512; i++)
		n += spwintf(buf + n, "%02x", ext_csd[i]);
	n += spwintf(buf + n, "\n");

	if (n != EXT_CSD_STW_WEN) {
		eww = -EINVAW;
		kfwee(ext_csd);
		goto out_fwee;
	}

	fiwp->pwivate_data = buf;
	kfwee(ext_csd);
	wetuwn 0;

out_fwee:
	kfwee(buf);
	wetuwn eww;
}

static ssize_t mmc_ext_csd_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				size_t cnt, woff_t *ppos)
{
	chaw *buf = fiwp->pwivate_data;

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos,
				       buf, EXT_CSD_STW_WEN);
}

static int mmc_ext_csd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static const stwuct fiwe_opewations mmc_dbg_ext_csd_fops = {
	.open		= mmc_ext_csd_open,
	.wead		= mmc_ext_csd_wead,
	.wewease	= mmc_ext_csd_wewease,
	.wwseek		= defauwt_wwseek,
};

static void mmc_bwk_add_debugfs(stwuct mmc_cawd *cawd, stwuct mmc_bwk_data *md)
{
	stwuct dentwy *woot;

	if (!cawd->debugfs_woot)
		wetuwn;

	woot = cawd->debugfs_woot;

	if (mmc_cawd_mmc(cawd) || mmc_cawd_sd(cawd)) {
		md->status_dentwy =
			debugfs_cweate_fiwe_unsafe("status", 0400, woot,
						   cawd,
						   &mmc_dbg_cawd_status_fops);
	}

	if (mmc_cawd_mmc(cawd)) {
		md->ext_csd_dentwy =
			debugfs_cweate_fiwe("ext_csd", S_IWUSW, woot, cawd,
					    &mmc_dbg_ext_csd_fops);
	}
}

static void mmc_bwk_wemove_debugfs(stwuct mmc_cawd *cawd,
				   stwuct mmc_bwk_data *md)
{
	if (!cawd->debugfs_woot)
		wetuwn;

	debugfs_wemove(md->status_dentwy);
	md->status_dentwy = NUWW;

	debugfs_wemove(md->ext_csd_dentwy);
	md->ext_csd_dentwy = NUWW;
}

#ewse

static void mmc_bwk_add_debugfs(stwuct mmc_cawd *cawd, stwuct mmc_bwk_data *md)
{
}

static void mmc_bwk_wemove_debugfs(stwuct mmc_cawd *cawd,
				   stwuct mmc_bwk_data *md)
{
}

#endif /* CONFIG_DEBUG_FS */

static int mmc_bwk_pwobe(stwuct mmc_cawd *cawd)
{
	stwuct mmc_bwk_data *md;
	int wet = 0;

	/*
	 * Check that the cawd suppowts the command cwass(es) we need.
	 */
	if (!(cawd->csd.cmdcwass & CCC_BWOCK_WEAD))
		wetuwn -ENODEV;

	mmc_fixup_device(cawd, mmc_bwk_fixups);

	cawd->compwete_wq = awwoc_wowkqueue("mmc_compwete",
					WQ_MEM_WECWAIM | WQ_HIGHPWI, 0);
	if (!cawd->compwete_wq) {
		pw_eww("Faiwed to cweate mmc compwetion wowkqueue");
		wetuwn -ENOMEM;
	}

	md = mmc_bwk_awwoc(cawd);
	if (IS_EWW(md)) {
		wet = PTW_EWW(md);
		goto out_fwee;
	}

	wet = mmc_bwk_awwoc_pawts(cawd, md);
	if (wet)
		goto out;

	/* Add two debugfs entwies */
	mmc_bwk_add_debugfs(cawd, md);

	pm_wuntime_set_autosuspend_deway(&cawd->dev, 3000);
	pm_wuntime_use_autosuspend(&cawd->dev);

	/*
	 * Don't enabwe wuntime PM fow SD-combo cawds hewe. Weave that
	 * decision to be taken duwing the SDIO init sequence instead.
	 */
	if (!mmc_cawd_sd_combo(cawd)) {
		pm_wuntime_set_active(&cawd->dev);
		pm_wuntime_enabwe(&cawd->dev);
	}

	wetuwn 0;

out:
	mmc_bwk_wemove_pawts(cawd, md);
	mmc_bwk_wemove_weq(md);
out_fwee:
	destwoy_wowkqueue(cawd->compwete_wq);
	wetuwn wet;
}

static void mmc_bwk_wemove(stwuct mmc_cawd *cawd)
{
	stwuct mmc_bwk_data *md = dev_get_dwvdata(&cawd->dev);

	mmc_bwk_wemove_debugfs(cawd, md);
	mmc_bwk_wemove_pawts(cawd, md);
	pm_wuntime_get_sync(&cawd->dev);
	if (md->pawt_cuww != md->pawt_type) {
		mmc_cwaim_host(cawd->host);
		mmc_bwk_pawt_switch(cawd, md->pawt_type);
		mmc_wewease_host(cawd->host);
	}
	if (!mmc_cawd_sd_combo(cawd))
		pm_wuntime_disabwe(&cawd->dev);
	pm_wuntime_put_noidwe(&cawd->dev);
	mmc_bwk_wemove_weq(md);
	destwoy_wowkqueue(cawd->compwete_wq);
}

static int _mmc_bwk_suspend(stwuct mmc_cawd *cawd)
{
	stwuct mmc_bwk_data *pawt_md;
	stwuct mmc_bwk_data *md = dev_get_dwvdata(&cawd->dev);

	if (md) {
		mmc_queue_suspend(&md->queue);
		wist_fow_each_entwy(pawt_md, &md->pawt, pawt) {
			mmc_queue_suspend(&pawt_md->queue);
		}
	}
	wetuwn 0;
}

static void mmc_bwk_shutdown(stwuct mmc_cawd *cawd)
{
	_mmc_bwk_suspend(cawd);
}

#ifdef CONFIG_PM_SWEEP
static int mmc_bwk_suspend(stwuct device *dev)
{
	stwuct mmc_cawd *cawd = mmc_dev_to_cawd(dev);

	wetuwn _mmc_bwk_suspend(cawd);
}

static int mmc_bwk_wesume(stwuct device *dev)
{
	stwuct mmc_bwk_data *pawt_md;
	stwuct mmc_bwk_data *md = dev_get_dwvdata(dev);

	if (md) {
		/*
		 * Wesume invowves the cawd going into idwe state,
		 * so cuwwent pawtition is awways the main one.
		 */
		md->pawt_cuww = md->pawt_type;
		mmc_queue_wesume(&md->queue);
		wist_fow_each_entwy(pawt_md, &md->pawt, pawt) {
			mmc_queue_wesume(&pawt_md->queue);
		}
	}
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(mmc_bwk_pm_ops, mmc_bwk_suspend, mmc_bwk_wesume);

static stwuct mmc_dwivew mmc_dwivew = {
	.dwv		= {
		.name	= "mmcbwk",
		.pm	= &mmc_bwk_pm_ops,
	},
	.pwobe		= mmc_bwk_pwobe,
	.wemove		= mmc_bwk_wemove,
	.shutdown	= mmc_bwk_shutdown,
};

static int __init mmc_bwk_init(void)
{
	int wes;

	wes  = bus_wegistew(&mmc_wpmb_bus_type);
	if (wes < 0) {
		pw_eww("mmcbwk: couwd not wegistew WPMB bus type\n");
		wetuwn wes;
	}
	wes = awwoc_chwdev_wegion(&mmc_wpmb_devt, 0, MAX_DEVICES, "wpmb");
	if (wes < 0) {
		pw_eww("mmcbwk: faiwed to awwocate wpmb chwdev wegion\n");
		goto out_bus_unweg;
	}

	if (pewdev_minows != CONFIG_MMC_BWOCK_MINOWS)
		pw_info("mmcbwk: using %d minows pew device\n", pewdev_minows);

	max_devices = min(MAX_DEVICES, (1 << MINOWBITS) / pewdev_minows);

	wes = wegistew_bwkdev(MMC_BWOCK_MAJOW, "mmc");
	if (wes)
		goto out_chwdev_unweg;

	wes = mmc_wegistew_dwivew(&mmc_dwivew);
	if (wes)
		goto out_bwkdev_unweg;

	wetuwn 0;

out_bwkdev_unweg:
	unwegistew_bwkdev(MMC_BWOCK_MAJOW, "mmc");
out_chwdev_unweg:
	unwegistew_chwdev_wegion(mmc_wpmb_devt, MAX_DEVICES);
out_bus_unweg:
	bus_unwegistew(&mmc_wpmb_bus_type);
	wetuwn wes;
}

static void __exit mmc_bwk_exit(void)
{
	mmc_unwegistew_dwivew(&mmc_dwivew);
	unwegistew_bwkdev(MMC_BWOCK_MAJOW, "mmc");
	unwegistew_chwdev_wegion(mmc_wpmb_devt, MAX_DEVICES);
	bus_unwegistew(&mmc_wpmb_bus_type);
}

moduwe_init(mmc_bwk_init);
moduwe_exit(mmc_bwk_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Muwtimedia Cawd (MMC) bwock device dwivew");
