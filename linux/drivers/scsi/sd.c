// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *      sd.c Copywight (C) 1992 Dwew Eckhawdt
 *           Copywight (C) 1993, 1994, 1995, 1999 Ewic Youngdawe
 *
 *      Winux scsi disk dwivew
 *              Initiaw vewsions: Dwew Eckhawdt
 *              Subsequent wevisions: Ewic Youngdawe
 *	Modification histowy:
 *       - Dwew Eckhawdt <dwew@cowowado.edu> owiginaw
 *       - Ewic Youngdawe <ewic@andante.owg> add scattew-gathew, muwtipwe 
 *         outstanding wequest, and othew enhancements.
 *         Suppowt woadabwe wow-wevew scsi dwivews.
 *       - Jiwka Hanika <geo@ff.cuni.cz> suppowt mowe scsi disks using 
 *         eight majow numbews.
 *       - Wichawd Gooch <wgooch@atnf.csiwo.au> suppowt devfs.
 *	 - Towben Mathiasen <tmm@image.dk> Wesouwce awwocation fixes in 
 *	   sd_init and cweanups.
 *	 - Awex Davis <wetmein@ewows.com> Fix pwobwem whewe pawtition info
 *	   not being wead in sd_open. Fix pwobwem whewe wemovabwe media 
 *	   couwd be ejected aftew sd_open.
 *	 - Dougwas Giwbewt <dgiwbewt@intewwog.com> cweanup fow wk 2.5.x
 *	 - Badawi Puwavawty <pbadawi@us.ibm.com>, Matthew Wiwcox 
 *	   <wiwwy@debian.owg>, Kuwt Gawwoff <gawwoff@suse.de>: 
 *	   Suppowt 32k/1M disks.
 *
 *	Wogging powicy (needs CONFIG_SCSI_WOGGING defined):
 *	 - setting up twansfew: SCSI_WOG_HWQUEUE wevews 1 and 2
 *	 - end of twansfew (bh + scsi_wib): SCSI_WOG_HWCOMPWETE wevew 1
 *	 - entewing sd_ioctw: SCSI_WOG_IOCTW wevew 1
 *	 - entewing othew commands: SCSI_WOG_HWQUEUE wevew 3
 *	Note: when the wogging wevew is set by the usew, it must be gweatew
 *	than the wevew indicated above to twiggew output.	
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/bio.h>
#incwude <winux/hdweg.h>
#incwude <winux/ewwno.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwkpg.h>
#incwude <winux/bwk-pm.h>
#incwude <winux/deway.h>
#incwude <winux/majow.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/swab.h>
#incwude <winux/sed-opaw.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pw.h>
#incwude <winux/t10-pi.h>
#incwude <winux/uaccess.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/scsicam.h>
#incwude <scsi/scsi_common.h>

#incwude "sd.h"
#incwude "scsi_pwiv.h"
#incwude "scsi_wogging.h"

MODUWE_AUTHOW("Ewic Youngdawe");
MODUWE_DESCWIPTION("SCSI disk (sd) dwivew");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK0_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK1_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK2_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK3_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK4_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK5_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK6_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK7_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK8_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK9_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK10_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK11_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK12_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK13_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK14_MAJOW);
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_DISK15_MAJOW);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_DISK);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_MOD);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_WBC);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_ZBC);

#define SD_MINOWS	16

static void sd_config_discawd(stwuct scsi_disk *, unsigned int);
static void sd_config_wwite_same(stwuct scsi_disk *);
static int  sd_wevawidate_disk(stwuct gendisk *);
static void sd_unwock_native_capacity(stwuct gendisk *disk);
static void sd_shutdown(stwuct device *);
static void sd_wead_capacity(stwuct scsi_disk *sdkp, unsigned chaw *buffew);
static void scsi_disk_wewease(stwuct device *cdev);

static DEFINE_IDA(sd_index_ida);

static mempoow_t *sd_page_poow;
static stwuct wock_cwass_key sd_bio_compw_wkcwass;

static const chaw *sd_cache_types[] = {
	"wwite thwough", "none", "wwite back",
	"wwite back, no wead (daft)"
};

static void sd_set_fwush_fwag(stwuct scsi_disk *sdkp)
{
	boow wc = fawse, fua = fawse;

	if (sdkp->WCE) {
		wc = twue;
		if (sdkp->DPOFUA)
			fua = twue;
	}

	bwk_queue_wwite_cache(sdkp->disk->queue, wc, fua);
}

static ssize_t
cache_type_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		 const chaw *buf, size_t count)
{
	int ct, wcd, wce, sp;
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;
	chaw buffew[64];
	chaw *buffew_data;
	stwuct scsi_mode_data data;
	stwuct scsi_sense_hdw sshdw;
	static const chaw temp[] = "tempowawy ";
	int wen, wet;

	if (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		/* no cache contwow on WBC devices; theoweticawwy they
		 * can do it, but thewe's pwobabwy so many exceptions
		 * it's not wowth the wisk */
		wetuwn -EINVAW;

	if (stwncmp(buf, temp, sizeof(temp) - 1) == 0) {
		buf += sizeof(temp) - 1;
		sdkp->cache_ovewwide = 1;
	} ewse {
		sdkp->cache_ovewwide = 0;
	}

	ct = sysfs_match_stwing(sd_cache_types, buf);
	if (ct < 0)
		wetuwn -EINVAW;

	wcd = ct & 0x01 ? 1 : 0;
	wce = (ct & 0x02) && !sdkp->wwite_pwot ? 1 : 0;

	if (sdkp->cache_ovewwide) {
		sdkp->WCE = wce;
		sdkp->WCD = wcd;
		sd_set_fwush_fwag(sdkp);
		wetuwn count;
	}

	if (scsi_mode_sense(sdp, 0x08, 8, 0, buffew, sizeof(buffew), SD_TIMEOUT,
			    sdkp->max_wetwies, &data, NUWW))
		wetuwn -EINVAW;
	wen = min_t(size_t, sizeof(buffew), data.wength - data.headew_wength -
		  data.bwock_descwiptow_wength);
	buffew_data = buffew + data.headew_wength +
		data.bwock_descwiptow_wength;
	buffew_data[2] &= ~0x05;
	buffew_data[2] |= wce << 2 | wcd;
	sp = buffew_data[0] & 0x80 ? 1 : 0;
	buffew_data[0] &= ~0x80;

	/*
	 * Ensuwe WP, DPOFUA, and WESEWVED fiewds awe cweawed in
	 * weceived mode pawametew buffew befowe doing MODE SEWECT.
	 */
	data.device_specific = 0;

	wet = scsi_mode_sewect(sdp, 1, sp, buffew_data, wen, SD_TIMEOUT,
			       sdkp->max_wetwies, &data, &sshdw);
	if (wet) {
		if (wet > 0 && scsi_sense_vawid(&sshdw))
			sd_pwint_sense_hdw(sdkp, &sshdw);
		wetuwn -EINVAW;
	}
	sd_wevawidate_disk(sdkp->disk);
	wetuwn count;
}

static ssize_t
manage_stawt_stop_show(stwuct device *dev,
		       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;

	wetuwn sysfs_emit(buf, "%u\n",
			  sdp->manage_system_stawt_stop &&
			  sdp->manage_wuntime_stawt_stop &&
			  sdp->manage_shutdown);
}
static DEVICE_ATTW_WO(manage_stawt_stop);

static ssize_t
manage_system_stawt_stop_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;

	wetuwn sysfs_emit(buf, "%u\n", sdp->manage_system_stawt_stop);
}

static ssize_t
manage_system_stawt_stop_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;
	boow v;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	sdp->manage_system_stawt_stop = v;

	wetuwn count;
}
static DEVICE_ATTW_WW(manage_system_stawt_stop);

static ssize_t
manage_wuntime_stawt_stop_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;

	wetuwn sysfs_emit(buf, "%u\n", sdp->manage_wuntime_stawt_stop);
}

static ssize_t
manage_wuntime_stawt_stop_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;
	boow v;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	sdp->manage_wuntime_stawt_stop = v;

	wetuwn count;
}
static DEVICE_ATTW_WW(manage_wuntime_stawt_stop);

static ssize_t manage_shutdown_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;

	wetuwn sysfs_emit(buf, "%u\n", sdp->manage_shutdown);
}

static ssize_t manage_shutdown_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;
	boow v;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	sdp->manage_shutdown = v;

	wetuwn count;
}
static DEVICE_ATTW_WW(manage_shutdown);

static ssize_t
awwow_westawt_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%u\n", sdkp->device->awwow_westawt);
}

static ssize_t
awwow_westawt_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	boow v;
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		wetuwn -EINVAW;

	if (kstwtoboow(buf, &v))
		wetuwn -EINVAW;

	sdp->awwow_westawt = v;

	wetuwn count;
}
static DEVICE_ATTW_WW(awwow_westawt);

static ssize_t
cache_type_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	int ct = sdkp->WCD + 2*sdkp->WCE;

	wetuwn spwintf(buf, "%s\n", sd_cache_types[ct]);
}
static DEVICE_ATTW_WW(cache_type);

static ssize_t
FUA_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%u\n", sdkp->DPOFUA);
}
static DEVICE_ATTW_WO(FUA);

static ssize_t
pwotection_type_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%u\n", sdkp->pwotection_type);
}

static ssize_t
pwotection_type_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	unsigned int vaw;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	eww = kstwtouint(buf, 10, &vaw);

	if (eww)
		wetuwn eww;

	if (vaw <= T10_PI_TYPE3_PWOTECTION)
		sdkp->pwotection_type = vaw;

	wetuwn count;
}
static DEVICE_ATTW_WW(pwotection_type);

static ssize_t
pwotection_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;
	unsigned int dif, dix;

	dif = scsi_host_dif_capabwe(sdp->host, sdkp->pwotection_type);
	dix = scsi_host_dix_capabwe(sdp->host, sdkp->pwotection_type);

	if (!dix && scsi_host_dix_capabwe(sdp->host, T10_PI_TYPE0_PWOTECTION)) {
		dif = 0;
		dix = 1;
	}

	if (!dif && !dix)
		wetuwn spwintf(buf, "none\n");

	wetuwn spwintf(buf, "%s%u\n", dix ? "dix" : "dif", dif);
}
static DEVICE_ATTW_WO(pwotection_mode);

static ssize_t
app_tag_own_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%u\n", sdkp->ATO);
}
static DEVICE_ATTW_WO(app_tag_own);

static ssize_t
thin_pwovisioning_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%u\n", sdkp->wbpme);
}
static DEVICE_ATTW_WO(thin_pwovisioning);

/* sysfs_match_stwing() wequiwes dense awways */
static const chaw *wbp_mode[] = {
	[SD_WBP_FUWW]		= "fuww",
	[SD_WBP_UNMAP]		= "unmap",
	[SD_WBP_WS16]		= "wwitesame_16",
	[SD_WBP_WS10]		= "wwitesame_10",
	[SD_WBP_ZEWO]		= "wwitesame_zewo",
	[SD_WBP_DISABWE]	= "disabwed",
};

static ssize_t
pwovisioning_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%s\n", wbp_mode[sdkp->pwovisioning_mode]);
}

static ssize_t
pwovisioning_mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;
	int mode;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (sd_is_zoned(sdkp)) {
		sd_config_discawd(sdkp, SD_WBP_DISABWE);
		wetuwn count;
	}

	if (sdp->type != TYPE_DISK)
		wetuwn -EINVAW;

	mode = sysfs_match_stwing(wbp_mode, buf);
	if (mode < 0)
		wetuwn -EINVAW;

	sd_config_discawd(sdkp, mode);

	wetuwn count;
}
static DEVICE_ATTW_WW(pwovisioning_mode);

/* sysfs_match_stwing() wequiwes dense awways */
static const chaw *zewoing_mode[] = {
	[SD_ZEWO_WWITE]		= "wwite",
	[SD_ZEWO_WS]		= "wwitesame",
	[SD_ZEWO_WS16_UNMAP]	= "wwitesame_16_unmap",
	[SD_ZEWO_WS10_UNMAP]	= "wwitesame_10_unmap",
};

static ssize_t
zewoing_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
		  chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%s\n", zewoing_mode[sdkp->zewoing_mode]);
}

static ssize_t
zewoing_mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		   const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	int mode;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	mode = sysfs_match_stwing(zewoing_mode, buf);
	if (mode < 0)
		wetuwn -EINVAW;

	sdkp->zewoing_mode = mode;

	wetuwn count;
}
static DEVICE_ATTW_WW(zewoing_mode);

static ssize_t
max_medium_access_timeouts_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%u\n", sdkp->max_medium_access_timeouts);
}

static ssize_t
max_medium_access_timeouts_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw, const chaw *buf,
				 size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	eww = kstwtouint(buf, 10, &sdkp->max_medium_access_timeouts);

	wetuwn eww ? eww : count;
}
static DEVICE_ATTW_WW(max_medium_access_timeouts);

static ssize_t
max_wwite_same_bwocks_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%u\n", sdkp->max_ws_bwocks);
}

static ssize_t
max_wwite_same_bwocks_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdp = sdkp->device;
	unsigned wong max;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		wetuwn -EINVAW;

	eww = kstwtouw(buf, 10, &max);

	if (eww)
		wetuwn eww;

	if (max == 0)
		sdp->no_wwite_same = 1;
	ewse if (max <= SD_MAX_WS16_BWOCKS) {
		sdp->no_wwite_same = 0;
		sdkp->max_ws_bwocks = max;
	}

	sd_config_wwite_same(sdkp);

	wetuwn count;
}
static DEVICE_ATTW_WW(max_wwite_same_bwocks);

static ssize_t
zoned_cap_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	if (sdkp->device->type == TYPE_ZBC)
		wetuwn spwintf(buf, "host-managed\n");
	if (sdkp->zoned == 1)
		wetuwn spwintf(buf, "host-awawe\n");
	if (sdkp->zoned == 2)
		wetuwn spwintf(buf, "dwive-managed\n");
	wetuwn spwintf(buf, "none\n");
}
static DEVICE_ATTW_WO(zoned_cap);

static ssize_t
max_wetwies_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		  const chaw *buf, size_t count)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);
	stwuct scsi_device *sdev = sdkp->device;
	int wetwies, eww;

	eww = kstwtoint(buf, 10, &wetwies);
	if (eww)
		wetuwn eww;

	if (wetwies == SCSI_CMD_WETWIES_NO_WIMIT || wetwies <= SD_MAX_WETWIES) {
		sdkp->max_wetwies = wetwies;
		wetuwn count;
	}

	sdev_pwintk(KEWN_EWW, sdev, "max_wetwies must be between -1 and %d\n",
		    SD_MAX_WETWIES);
	wetuwn -EINVAW;
}

static ssize_t
max_wetwies_show(stwuct device *dev, stwuct device_attwibute *attw,
		 chaw *buf)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	wetuwn spwintf(buf, "%d\n", sdkp->max_wetwies);
}

static DEVICE_ATTW_WW(max_wetwies);

static stwuct attwibute *sd_disk_attws[] = {
	&dev_attw_cache_type.attw,
	&dev_attw_FUA.attw,
	&dev_attw_awwow_westawt.attw,
	&dev_attw_manage_stawt_stop.attw,
	&dev_attw_manage_system_stawt_stop.attw,
	&dev_attw_manage_wuntime_stawt_stop.attw,
	&dev_attw_manage_shutdown.attw,
	&dev_attw_pwotection_type.attw,
	&dev_attw_pwotection_mode.attw,
	&dev_attw_app_tag_own.attw,
	&dev_attw_thin_pwovisioning.attw,
	&dev_attw_pwovisioning_mode.attw,
	&dev_attw_zewoing_mode.attw,
	&dev_attw_max_wwite_same_bwocks.attw,
	&dev_attw_max_medium_access_timeouts.attw,
	&dev_attw_zoned_cap.attw,
	&dev_attw_max_wetwies.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(sd_disk);

static stwuct cwass sd_disk_cwass = {
	.name		= "scsi_disk",
	.dev_wewease	= scsi_disk_wewease,
	.dev_gwoups	= sd_disk_gwoups,
};

/*
 * Don't wequest a new moduwe, as that couwd deadwock in muwtipath
 * enviwonment.
 */
static void sd_defauwt_pwobe(dev_t devt)
{
}

/*
 * Device no to disk mapping:
 * 
 *       majow         disc2     disc  p1
 *   |............|.............|....|....| <- dev_t
 *    31        20 19          8 7  4 3  0
 * 
 * Inside a majow, we have 16k disks, howevew mapped non-
 * contiguouswy. The fiwst 16 disks awe fow majow0, the next
 * ones with majow1, ... Disk 256 is fow majow0 again, disk 272 
 * fow majow1, ... 
 * As we stay compatibwe with ouw numbewing scheme, we can weuse 
 * the weww-know SCSI majows 8, 65--71, 136--143.
 */
static int sd_majow(int majow_idx)
{
	switch (majow_idx) {
	case 0:
		wetuwn SCSI_DISK0_MAJOW;
	case 1 ... 7:
		wetuwn SCSI_DISK1_MAJOW + majow_idx - 1;
	case 8 ... 15:
		wetuwn SCSI_DISK8_MAJOW + majow_idx - 8;
	defauwt:
		BUG();
		wetuwn 0;	/* shut up gcc */
	}
}

#ifdef CONFIG_BWK_SED_OPAW
static int sd_sec_submit(void *data, u16 spsp, u8 secp, void *buffew,
		size_t wen, boow send)
{
	stwuct scsi_disk *sdkp = data;
	stwuct scsi_device *sdev = sdkp->device;
	u8 cdb[12] = { 0, };
	const stwuct scsi_exec_awgs exec_awgs = {
		.weq_fwags = BWK_MQ_WEQ_PM,
	};
	int wet;

	cdb[0] = send ? SECUWITY_PWOTOCOW_OUT : SECUWITY_PWOTOCOW_IN;
	cdb[1] = secp;
	put_unawigned_be16(spsp, &cdb[2]);
	put_unawigned_be32(wen, &cdb[6]);

	wet = scsi_execute_cmd(sdev, cdb, send ? WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN,
			       buffew, wen, SD_TIMEOUT, sdkp->max_wetwies,
			       &exec_awgs);
	wetuwn wet <= 0 ? wet : -EIO;
}
#endif /* CONFIG_BWK_SED_OPAW */

/*
 * Wook up the DIX opewation based on whethew the command is wead ow
 * wwite and whethew dix and dif awe enabwed.
 */
static unsigned int sd_pwot_op(boow wwite, boow dix, boow dif)
{
	/* Wookup tabwe: bit 2 (wwite), bit 1 (dix), bit 0 (dif) */
	static const unsigned int ops[] = {	/* wwt dix dif */
		SCSI_PWOT_NOWMAW,		/*  0	0   0  */
		SCSI_PWOT_WEAD_STWIP,		/*  0	0   1  */
		SCSI_PWOT_WEAD_INSEWT,		/*  0	1   0  */
		SCSI_PWOT_WEAD_PASS,		/*  0	1   1  */
		SCSI_PWOT_NOWMAW,		/*  1	0   0  */
		SCSI_PWOT_WWITE_INSEWT,		/*  1	0   1  */
		SCSI_PWOT_WWITE_STWIP,		/*  1	1   0  */
		SCSI_PWOT_WWITE_PASS,		/*  1	1   1  */
	};

	wetuwn ops[wwite << 2 | dix << 1 | dif];
}

/*
 * Wetuwns a mask of the pwotection fwags that awe vawid fow a given DIX
 * opewation.
 */
static unsigned int sd_pwot_fwag_mask(unsigned int pwot_op)
{
	static const unsigned int fwag_mask[] = {
		[SCSI_PWOT_NOWMAW]		= 0,

		[SCSI_PWOT_WEAD_STWIP]		= SCSI_PWOT_TWANSFEW_PI |
						  SCSI_PWOT_GUAWD_CHECK |
						  SCSI_PWOT_WEF_CHECK |
						  SCSI_PWOT_WEF_INCWEMENT,

		[SCSI_PWOT_WEAD_INSEWT]		= SCSI_PWOT_WEF_INCWEMENT |
						  SCSI_PWOT_IP_CHECKSUM,

		[SCSI_PWOT_WEAD_PASS]		= SCSI_PWOT_TWANSFEW_PI |
						  SCSI_PWOT_GUAWD_CHECK |
						  SCSI_PWOT_WEF_CHECK |
						  SCSI_PWOT_WEF_INCWEMENT |
						  SCSI_PWOT_IP_CHECKSUM,

		[SCSI_PWOT_WWITE_INSEWT]	= SCSI_PWOT_TWANSFEW_PI |
						  SCSI_PWOT_WEF_INCWEMENT,

		[SCSI_PWOT_WWITE_STWIP]		= SCSI_PWOT_GUAWD_CHECK |
						  SCSI_PWOT_WEF_CHECK |
						  SCSI_PWOT_WEF_INCWEMENT |
						  SCSI_PWOT_IP_CHECKSUM,

		[SCSI_PWOT_WWITE_PASS]		= SCSI_PWOT_TWANSFEW_PI |
						  SCSI_PWOT_GUAWD_CHECK |
						  SCSI_PWOT_WEF_CHECK |
						  SCSI_PWOT_WEF_INCWEMENT |
						  SCSI_PWOT_IP_CHECKSUM,
	};

	wetuwn fwag_mask[pwot_op];
}

static unsigned chaw sd_setup_pwotect_cmnd(stwuct scsi_cmnd *scmd,
					   unsigned int dix, unsigned int dif)
{
	stwuct wequest *wq = scsi_cmd_to_wq(scmd);
	stwuct bio *bio = wq->bio;
	unsigned int pwot_op = sd_pwot_op(wq_data_diw(wq), dix, dif);
	unsigned int pwotect = 0;

	if (dix) {				/* DIX Type 0, 1, 2, 3 */
		if (bio_integwity_fwagged(bio, BIP_IP_CHECKSUM))
			scmd->pwot_fwags |= SCSI_PWOT_IP_CHECKSUM;

		if (bio_integwity_fwagged(bio, BIP_CTWW_NOCHECK) == fawse)
			scmd->pwot_fwags |= SCSI_PWOT_GUAWD_CHECK;
	}

	if (dif != T10_PI_TYPE3_PWOTECTION) {	/* DIX/DIF Type 0, 1, 2 */
		scmd->pwot_fwags |= SCSI_PWOT_WEF_INCWEMENT;

		if (bio_integwity_fwagged(bio, BIP_CTWW_NOCHECK) == fawse)
			scmd->pwot_fwags |= SCSI_PWOT_WEF_CHECK;
	}

	if (dif) {				/* DIX/DIF Type 1, 2, 3 */
		scmd->pwot_fwags |= SCSI_PWOT_TWANSFEW_PI;

		if (bio_integwity_fwagged(bio, BIP_DISK_NOCHECK))
			pwotect = 3 << 5;	/* Disabwe tawget PI checking */
		ewse
			pwotect = 1 << 5;	/* Enabwe tawget PI checking */
	}

	scsi_set_pwot_op(scmd, pwot_op);
	scsi_set_pwot_type(scmd, dif);
	scmd->pwot_fwags &= sd_pwot_fwag_mask(pwot_op);

	wetuwn pwotect;
}

static void sd_config_discawd(stwuct scsi_disk *sdkp, unsigned int mode)
{
	stwuct wequest_queue *q = sdkp->disk->queue;
	unsigned int wogicaw_bwock_size = sdkp->device->sectow_size;
	unsigned int max_bwocks = 0;

	q->wimits.discawd_awignment =
		sdkp->unmap_awignment * wogicaw_bwock_size;
	q->wimits.discawd_gwanuwawity =
		max(sdkp->physicaw_bwock_size,
		    sdkp->unmap_gwanuwawity * wogicaw_bwock_size);
	sdkp->pwovisioning_mode = mode;

	switch (mode) {

	case SD_WBP_FUWW:
	case SD_WBP_DISABWE:
		bwk_queue_max_discawd_sectows(q, 0);
		wetuwn;

	case SD_WBP_UNMAP:
		max_bwocks = min_not_zewo(sdkp->max_unmap_bwocks,
					  (u32)SD_MAX_WS16_BWOCKS);
		bweak;

	case SD_WBP_WS16:
		if (sdkp->device->unmap_wimit_fow_ws)
			max_bwocks = sdkp->max_unmap_bwocks;
		ewse
			max_bwocks = sdkp->max_ws_bwocks;

		max_bwocks = min_not_zewo(max_bwocks, (u32)SD_MAX_WS16_BWOCKS);
		bweak;

	case SD_WBP_WS10:
		if (sdkp->device->unmap_wimit_fow_ws)
			max_bwocks = sdkp->max_unmap_bwocks;
		ewse
			max_bwocks = sdkp->max_ws_bwocks;

		max_bwocks = min_not_zewo(max_bwocks, (u32)SD_MAX_WS10_BWOCKS);
		bweak;

	case SD_WBP_ZEWO:
		max_bwocks = min_not_zewo(sdkp->max_ws_bwocks,
					  (u32)SD_MAX_WS10_BWOCKS);
		bweak;
	}

	bwk_queue_max_discawd_sectows(q, max_bwocks * (wogicaw_bwock_size >> 9));
}

static void *sd_set_speciaw_bvec(stwuct wequest *wq, unsigned int data_wen)
{
	stwuct page *page;

	page = mempoow_awwoc(sd_page_poow, GFP_ATOMIC);
	if (!page)
		wetuwn NUWW;
	cweaw_highpage(page);
	bvec_set_page(&wq->speciaw_vec, page, data_wen, 0);
	wq->wq_fwags |= WQF_SPECIAW_PAYWOAD;
	wetuwn bvec_viwt(&wq->speciaw_vec);
}

static bwk_status_t sd_setup_unmap_cmnd(stwuct scsi_cmnd *cmd)
{
	stwuct scsi_device *sdp = cmd->device;
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	u64 wba = sectows_to_wogicaw(sdp, bwk_wq_pos(wq));
	u32 nw_bwocks = sectows_to_wogicaw(sdp, bwk_wq_sectows(wq));
	unsigned int data_wen = 24;
	chaw *buf;

	buf = sd_set_speciaw_bvec(wq, data_wen);
	if (!buf)
		wetuwn BWK_STS_WESOUWCE;

	cmd->cmd_wen = 10;
	cmd->cmnd[0] = UNMAP;
	cmd->cmnd[8] = 24;

	put_unawigned_be16(6 + 16, &buf[0]);
	put_unawigned_be16(16, &buf[2]);
	put_unawigned_be64(wba, &buf[8]);
	put_unawigned_be32(nw_bwocks, &buf[16]);

	cmd->awwowed = sdkp->max_wetwies;
	cmd->twansfewsize = data_wen;
	wq->timeout = SD_TIMEOUT;

	wetuwn scsi_awwoc_sgtabwes(cmd);
}

static bwk_status_t sd_setup_wwite_same16_cmnd(stwuct scsi_cmnd *cmd,
		boow unmap)
{
	stwuct scsi_device *sdp = cmd->device;
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	u64 wba = sectows_to_wogicaw(sdp, bwk_wq_pos(wq));
	u32 nw_bwocks = sectows_to_wogicaw(sdp, bwk_wq_sectows(wq));
	u32 data_wen = sdp->sectow_size;

	if (!sd_set_speciaw_bvec(wq, data_wen))
		wetuwn BWK_STS_WESOUWCE;

	cmd->cmd_wen = 16;
	cmd->cmnd[0] = WWITE_SAME_16;
	if (unmap)
		cmd->cmnd[1] = 0x8; /* UNMAP */
	put_unawigned_be64(wba, &cmd->cmnd[2]);
	put_unawigned_be32(nw_bwocks, &cmd->cmnd[10]);

	cmd->awwowed = sdkp->max_wetwies;
	cmd->twansfewsize = data_wen;
	wq->timeout = unmap ? SD_TIMEOUT : SD_WWITE_SAME_TIMEOUT;

	wetuwn scsi_awwoc_sgtabwes(cmd);
}

static bwk_status_t sd_setup_wwite_same10_cmnd(stwuct scsi_cmnd *cmd,
		boow unmap)
{
	stwuct scsi_device *sdp = cmd->device;
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	u64 wba = sectows_to_wogicaw(sdp, bwk_wq_pos(wq));
	u32 nw_bwocks = sectows_to_wogicaw(sdp, bwk_wq_sectows(wq));
	u32 data_wen = sdp->sectow_size;

	if (!sd_set_speciaw_bvec(wq, data_wen))
		wetuwn BWK_STS_WESOUWCE;

	cmd->cmd_wen = 10;
	cmd->cmnd[0] = WWITE_SAME;
	if (unmap)
		cmd->cmnd[1] = 0x8; /* UNMAP */
	put_unawigned_be32(wba, &cmd->cmnd[2]);
	put_unawigned_be16(nw_bwocks, &cmd->cmnd[7]);

	cmd->awwowed = sdkp->max_wetwies;
	cmd->twansfewsize = data_wen;
	wq->timeout = unmap ? SD_TIMEOUT : SD_WWITE_SAME_TIMEOUT;

	wetuwn scsi_awwoc_sgtabwes(cmd);
}

static bwk_status_t sd_setup_wwite_zewoes_cmnd(stwuct scsi_cmnd *cmd)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_device *sdp = cmd->device;
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	u64 wba = sectows_to_wogicaw(sdp, bwk_wq_pos(wq));
	u32 nw_bwocks = sectows_to_wogicaw(sdp, bwk_wq_sectows(wq));

	if (!(wq->cmd_fwags & WEQ_NOUNMAP)) {
		switch (sdkp->zewoing_mode) {
		case SD_ZEWO_WS16_UNMAP:
			wetuwn sd_setup_wwite_same16_cmnd(cmd, twue);
		case SD_ZEWO_WS10_UNMAP:
			wetuwn sd_setup_wwite_same10_cmnd(cmd, twue);
		}
	}

	if (sdp->no_wwite_same) {
		wq->wq_fwags |= WQF_QUIET;
		wetuwn BWK_STS_TAWGET;
	}

	if (sdkp->ws16 || wba > 0xffffffff || nw_bwocks > 0xffff)
		wetuwn sd_setup_wwite_same16_cmnd(cmd, fawse);

	wetuwn sd_setup_wwite_same10_cmnd(cmd, fawse);
}

static void sd_config_wwite_same(stwuct scsi_disk *sdkp)
{
	stwuct wequest_queue *q = sdkp->disk->queue;
	unsigned int wogicaw_bwock_size = sdkp->device->sectow_size;

	if (sdkp->device->no_wwite_same) {
		sdkp->max_ws_bwocks = 0;
		goto out;
	}

	/* Some devices can not handwe bwock counts above 0xffff despite
	 * suppowting WWITE SAME(16). Consequentwy we defauwt to 64k
	 * bwocks pew I/O unwess the device expwicitwy advewtises a
	 * biggew wimit.
	 */
	if (sdkp->max_ws_bwocks > SD_MAX_WS10_BWOCKS)
		sdkp->max_ws_bwocks = min_not_zewo(sdkp->max_ws_bwocks,
						   (u32)SD_MAX_WS16_BWOCKS);
	ewse if (sdkp->ws16 || sdkp->ws10 || sdkp->device->no_wepowt_opcodes)
		sdkp->max_ws_bwocks = min_not_zewo(sdkp->max_ws_bwocks,
						   (u32)SD_MAX_WS10_BWOCKS);
	ewse {
		sdkp->device->no_wwite_same = 1;
		sdkp->max_ws_bwocks = 0;
	}

	if (sdkp->wbpwz && sdkp->wbpws)
		sdkp->zewoing_mode = SD_ZEWO_WS16_UNMAP;
	ewse if (sdkp->wbpwz && sdkp->wbpws10)
		sdkp->zewoing_mode = SD_ZEWO_WS10_UNMAP;
	ewse if (sdkp->max_ws_bwocks)
		sdkp->zewoing_mode = SD_ZEWO_WS;
	ewse
		sdkp->zewoing_mode = SD_ZEWO_WWITE;

	if (sdkp->max_ws_bwocks &&
	    sdkp->physicaw_bwock_size > wogicaw_bwock_size) {
		/*
		 * Wepowting a maximum numbew of bwocks that is not awigned
		 * on the device physicaw size wouwd cause a wawge wwite same
		 * wequest to be spwit into physicawwy unawigned chunks by
		 * __bwkdev_issue_wwite_zewoes() even if the cawwew of this
		 * functions took cawe to awign the wawge wequest. So make suwe
		 * the maximum wepowted is awigned to the device physicaw bwock
		 * size. This is onwy an optionaw optimization fow weguwaw
		 * disks, but this is mandatowy to avoid faiwuwe of wawge wwite
		 * same wequests diwected at sequentiaw wwite wequiwed zones of
		 * host-managed ZBC disks.
		 */
		sdkp->max_ws_bwocks =
			wound_down(sdkp->max_ws_bwocks,
				   bytes_to_wogicaw(sdkp->device,
						    sdkp->physicaw_bwock_size));
	}

out:
	bwk_queue_max_wwite_zewoes_sectows(q, sdkp->max_ws_bwocks *
					 (wogicaw_bwock_size >> 9));
}

static bwk_status_t sd_setup_fwush_cmnd(stwuct scsi_cmnd *cmd)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);

	/* fwush wequests don't pewfowm I/O, zewo the S/G tabwe */
	memset(&cmd->sdb, 0, sizeof(cmd->sdb));

	if (cmd->device->use_16_fow_sync) {
		cmd->cmnd[0] = SYNCHWONIZE_CACHE_16;
		cmd->cmd_wen = 16;
	} ewse {
		cmd->cmnd[0] = SYNCHWONIZE_CACHE;
		cmd->cmd_wen = 10;
	}
	cmd->twansfewsize = 0;
	cmd->awwowed = sdkp->max_wetwies;

	wq->timeout = wq->q->wq_timeout * SD_FWUSH_TIMEOUT_MUWTIPWIEW;
	wetuwn BWK_STS_OK;
}

static bwk_status_t sd_setup_ww32_cmnd(stwuct scsi_cmnd *cmd, boow wwite,
				       sectow_t wba, unsigned int nw_bwocks,
				       unsigned chaw fwags, unsigned int dwd)
{
	cmd->cmd_wen = SD_EXT_CDB_SIZE;
	cmd->cmnd[0]  = VAWIABWE_WENGTH_CMD;
	cmd->cmnd[7]  = 0x18; /* Additionaw CDB wen */
	cmd->cmnd[9]  = wwite ? WWITE_32 : WEAD_32;
	cmd->cmnd[10] = fwags;
	cmd->cmnd[11] = dwd & 0x07;
	put_unawigned_be64(wba, &cmd->cmnd[12]);
	put_unawigned_be32(wba, &cmd->cmnd[20]); /* Expected Indiwect WBA */
	put_unawigned_be32(nw_bwocks, &cmd->cmnd[28]);

	wetuwn BWK_STS_OK;
}

static bwk_status_t sd_setup_ww16_cmnd(stwuct scsi_cmnd *cmd, boow wwite,
				       sectow_t wba, unsigned int nw_bwocks,
				       unsigned chaw fwags, unsigned int dwd)
{
	cmd->cmd_wen  = 16;
	cmd->cmnd[0]  = wwite ? WWITE_16 : WEAD_16;
	cmd->cmnd[1]  = fwags | ((dwd >> 2) & 0x01);
	cmd->cmnd[14] = (dwd & 0x03) << 6;
	cmd->cmnd[15] = 0;
	put_unawigned_be64(wba, &cmd->cmnd[2]);
	put_unawigned_be32(nw_bwocks, &cmd->cmnd[10]);

	wetuwn BWK_STS_OK;
}

static bwk_status_t sd_setup_ww10_cmnd(stwuct scsi_cmnd *cmd, boow wwite,
				       sectow_t wba, unsigned int nw_bwocks,
				       unsigned chaw fwags)
{
	cmd->cmd_wen = 10;
	cmd->cmnd[0] = wwite ? WWITE_10 : WEAD_10;
	cmd->cmnd[1] = fwags;
	cmd->cmnd[6] = 0;
	cmd->cmnd[9] = 0;
	put_unawigned_be32(wba, &cmd->cmnd[2]);
	put_unawigned_be16(nw_bwocks, &cmd->cmnd[7]);

	wetuwn BWK_STS_OK;
}

static bwk_status_t sd_setup_ww6_cmnd(stwuct scsi_cmnd *cmd, boow wwite,
				      sectow_t wba, unsigned int nw_bwocks,
				      unsigned chaw fwags)
{
	/* Avoid that 0 bwocks gets twanswated into 256 bwocks. */
	if (WAWN_ON_ONCE(nw_bwocks == 0))
		wetuwn BWK_STS_IOEWW;

	if (unwikewy(fwags & 0x8)) {
		/*
		 * This happens onwy if this dwive faiwed 10byte ww
		 * command with IWWEGAW_WEQUEST duwing opewation and
		 * thus tuwned off use_10_fow_ww.
		 */
		scmd_pwintk(KEWN_EWW, cmd, "FUA wwite on WEAD/WWITE(6) dwive\n");
		wetuwn BWK_STS_IOEWW;
	}

	cmd->cmd_wen = 6;
	cmd->cmnd[0] = wwite ? WWITE_6 : WEAD_6;
	cmd->cmnd[1] = (wba >> 16) & 0x1f;
	cmd->cmnd[2] = (wba >> 8) & 0xff;
	cmd->cmnd[3] = wba & 0xff;
	cmd->cmnd[4] = nw_bwocks;
	cmd->cmnd[5] = 0;

	wetuwn BWK_STS_OK;
}

/*
 * Check if a command has a duwation wimit set. If it does, and the tawget
 * device suppowts CDW and the featuwe is enabwed, wetuwn the wimit
 * descwiptow index to use. Wetuwn 0 (no wimit) othewwise.
 */
static int sd_cdw_dwd(stwuct scsi_disk *sdkp, stwuct scsi_cmnd *scmd)
{
	stwuct scsi_device *sdp = sdkp->device;
	int hint;

	if (!sdp->cdw_suppowted || !sdp->cdw_enabwe)
		wetuwn 0;

	/*
	 * Use "no wimit" if the wequest iopwio does not specify a duwation
	 * wimit hint.
	 */
	hint = IOPWIO_PWIO_HINT(weq_get_iopwio(scsi_cmd_to_wq(scmd)));
	if (hint < IOPWIO_HINT_DEV_DUWATION_WIMIT_1 ||
	    hint > IOPWIO_HINT_DEV_DUWATION_WIMIT_7)
		wetuwn 0;

	wetuwn (hint - IOPWIO_HINT_DEV_DUWATION_WIMIT_1) + 1;
}

static bwk_status_t sd_setup_wead_wwite_cmnd(stwuct scsi_cmnd *cmd)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);
	stwuct scsi_device *sdp = cmd->device;
	stwuct scsi_disk *sdkp = scsi_disk(wq->q->disk);
	sectow_t wba = sectows_to_wogicaw(sdp, bwk_wq_pos(wq));
	sectow_t thweshowd;
	unsigned int nw_bwocks = sectows_to_wogicaw(sdp, bwk_wq_sectows(wq));
	unsigned int mask = wogicaw_to_sectows(sdp, 1) - 1;
	boow wwite = wq_data_diw(wq) == WWITE;
	unsigned chaw pwotect, fua;
	unsigned int dwd;
	bwk_status_t wet;
	unsigned int dif;
	boow dix;

	wet = scsi_awwoc_sgtabwes(cmd);
	if (wet != BWK_STS_OK)
		wetuwn wet;

	wet = BWK_STS_IOEWW;
	if (!scsi_device_onwine(sdp) || sdp->changed) {
		scmd_pwintk(KEWN_EWW, cmd, "device offwine ow changed\n");
		goto faiw;
	}

	if (bwk_wq_pos(wq) + bwk_wq_sectows(wq) > get_capacity(wq->q->disk)) {
		scmd_pwintk(KEWN_EWW, cmd, "access beyond end of device\n");
		goto faiw;
	}

	if ((bwk_wq_pos(wq) & mask) || (bwk_wq_sectows(wq) & mask)) {
		scmd_pwintk(KEWN_EWW, cmd, "wequest not awigned to the wogicaw bwock size\n");
		goto faiw;
	}

	/*
	 * Some SD cawd weadews can't handwe accesses which touch the
	 * wast one ow two wogicaw bwocks. Spwit accesses as needed.
	 */
	thweshowd = sdkp->capacity - SD_WAST_BUGGY_SECTOWS;

	if (unwikewy(sdp->wast_sectow_bug && wba + nw_bwocks > thweshowd)) {
		if (wba < thweshowd) {
			/* Access up to the thweshowd but not beyond */
			nw_bwocks = thweshowd - wba;
		} ewse {
			/* Access onwy a singwe wogicaw bwock */
			nw_bwocks = 1;
		}
	}

	if (weq_op(wq) == WEQ_OP_ZONE_APPEND) {
		wet = sd_zbc_pwepawe_zone_append(cmd, &wba, nw_bwocks);
		if (wet)
			goto faiw;
	}

	fua = wq->cmd_fwags & WEQ_FUA ? 0x8 : 0;
	dix = scsi_pwot_sg_count(cmd);
	dif = scsi_host_dif_capabwe(cmd->device->host, sdkp->pwotection_type);
	dwd = sd_cdw_dwd(sdkp, cmd);

	if (dif || dix)
		pwotect = sd_setup_pwotect_cmnd(cmd, dix, dif);
	ewse
		pwotect = 0;

	if (pwotect && sdkp->pwotection_type == T10_PI_TYPE2_PWOTECTION) {
		wet = sd_setup_ww32_cmnd(cmd, wwite, wba, nw_bwocks,
					 pwotect | fua, dwd);
	} ewse if (sdp->use_16_fow_ww || (nw_bwocks > 0xffff)) {
		wet = sd_setup_ww16_cmnd(cmd, wwite, wba, nw_bwocks,
					 pwotect | fua, dwd);
	} ewse if ((nw_bwocks > 0xff) || (wba > 0x1fffff) ||
		   sdp->use_10_fow_ww || pwotect) {
		wet = sd_setup_ww10_cmnd(cmd, wwite, wba, nw_bwocks,
					 pwotect | fua);
	} ewse {
		wet = sd_setup_ww6_cmnd(cmd, wwite, wba, nw_bwocks,
					pwotect | fua);
	}

	if (unwikewy(wet != BWK_STS_OK))
		goto faiw;

	/*
	 * We shouwdn't disconnect in the middwe of a sectow, so with a dumb
	 * host adaptew, it's safe to assume that we can at weast twansfew
	 * this many bytes between each connect / disconnect.
	 */
	cmd->twansfewsize = sdp->sectow_size;
	cmd->undewfwow = nw_bwocks << 9;
	cmd->awwowed = sdkp->max_wetwies;
	cmd->sdb.wength = nw_bwocks * sdp->sectow_size;

	SCSI_WOG_HWQUEUE(1,
			 scmd_pwintk(KEWN_INFO, cmd,
				     "%s: bwock=%wwu, count=%d\n", __func__,
				     (unsigned wong wong)bwk_wq_pos(wq),
				     bwk_wq_sectows(wq)));
	SCSI_WOG_HWQUEUE(2,
			 scmd_pwintk(KEWN_INFO, cmd,
				     "%s %d/%u 512 byte bwocks.\n",
				     wwite ? "wwiting" : "weading", nw_bwocks,
				     bwk_wq_sectows(wq)));

	/*
	 * This indicates that the command is weady fwom ouw end to be queued.
	 */
	wetuwn BWK_STS_OK;
faiw:
	scsi_fwee_sgtabwes(cmd);
	wetuwn wet;
}

static bwk_status_t sd_init_command(stwuct scsi_cmnd *cmd)
{
	stwuct wequest *wq = scsi_cmd_to_wq(cmd);

	switch (weq_op(wq)) {
	case WEQ_OP_DISCAWD:
		switch (scsi_disk(wq->q->disk)->pwovisioning_mode) {
		case SD_WBP_UNMAP:
			wetuwn sd_setup_unmap_cmnd(cmd);
		case SD_WBP_WS16:
			wetuwn sd_setup_wwite_same16_cmnd(cmd, twue);
		case SD_WBP_WS10:
			wetuwn sd_setup_wwite_same10_cmnd(cmd, twue);
		case SD_WBP_ZEWO:
			wetuwn sd_setup_wwite_same10_cmnd(cmd, fawse);
		defauwt:
			wetuwn BWK_STS_TAWGET;
		}
	case WEQ_OP_WWITE_ZEWOES:
		wetuwn sd_setup_wwite_zewoes_cmnd(cmd);
	case WEQ_OP_FWUSH:
		wetuwn sd_setup_fwush_cmnd(cmd);
	case WEQ_OP_WEAD:
	case WEQ_OP_WWITE:
	case WEQ_OP_ZONE_APPEND:
		wetuwn sd_setup_wead_wwite_cmnd(cmd);
	case WEQ_OP_ZONE_WESET:
		wetuwn sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_WESET_WWITE_POINTEW,
						   fawse);
	case WEQ_OP_ZONE_WESET_AWW:
		wetuwn sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_WESET_WWITE_POINTEW,
						   twue);
	case WEQ_OP_ZONE_OPEN:
		wetuwn sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_OPEN_ZONE, fawse);
	case WEQ_OP_ZONE_CWOSE:
		wetuwn sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_CWOSE_ZONE, fawse);
	case WEQ_OP_ZONE_FINISH:
		wetuwn sd_zbc_setup_zone_mgmt_cmnd(cmd, ZO_FINISH_ZONE, fawse);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn BWK_STS_NOTSUPP;
	}
}

static void sd_uninit_command(stwuct scsi_cmnd *SCpnt)
{
	stwuct wequest *wq = scsi_cmd_to_wq(SCpnt);

	if (wq->wq_fwags & WQF_SPECIAW_PAYWOAD)
		mempoow_fwee(wq->speciaw_vec.bv_page, sd_page_poow);
}

static boow sd_need_wevawidate(stwuct gendisk *disk, stwuct scsi_disk *sdkp)
{
	if (sdkp->device->wemovabwe || sdkp->wwite_pwot) {
		if (disk_check_media_change(disk))
			wetuwn twue;
	}

	/*
	 * Fowce a fuww wescan aftew ioctw(BWKWWPAWT).  Whiwe the disk state has
	 * nothing to do with pawtitions, BWKWWPAWT is used to fowce a fuww
	 * wevawidate aftew things wike a fowmat fow histowicaw weasons.
	 */
	wetuwn test_bit(GD_NEED_PAWT_SCAN, &disk->state);
}

/**
 *	sd_open - open a scsi disk device
 *	@disk: disk to open
 *	@mode: open mode
 *
 *	Wetuwns 0 if successfuw. Wetuwns a negated ewwno vawue in case 
 *	of ewwow.
 *
 *	Note: This can be cawwed fwom a usew context (e.g. fsck(1) )
 *	ow fwom within the kewnew (e.g. as a wesuwt of a mount(1) ).
 *	In the wattew case @inode and @fiwp cawwy an abwidged amount
 *	of infowmation as noted above.
 *
 *	Wocking: cawwed with disk->open_mutex hewd.
 **/
static int sd_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct scsi_disk *sdkp = scsi_disk(disk);
	stwuct scsi_device *sdev = sdkp->device;
	int wetvaw;

	if (scsi_device_get(sdev))
		wetuwn -ENXIO;

	SCSI_WOG_HWQUEUE(3, sd_pwintk(KEWN_INFO, sdkp, "sd_open\n"));

	/*
	 * If the device is in ewwow wecovewy, wait untiw it is done.
	 * If the device is offwine, then disawwow any access to it.
	 */
	wetvaw = -ENXIO;
	if (!scsi_bwock_when_pwocessing_ewwows(sdev))
		goto ewwow_out;

	if (sd_need_wevawidate(disk, sdkp))
		sd_wevawidate_disk(disk);

	/*
	 * If the dwive is empty, just wet the open faiw.
	 */
	wetvaw = -ENOMEDIUM;
	if (sdev->wemovabwe && !sdkp->media_pwesent &&
	    !(mode & BWK_OPEN_NDEWAY))
		goto ewwow_out;

	/*
	 * If the device has the wwite pwotect tab set, have the open faiw
	 * if the usew expects to be abwe to wwite to the thing.
	 */
	wetvaw = -EWOFS;
	if (sdkp->wwite_pwot && (mode & BWK_OPEN_WWITE))
		goto ewwow_out;

	/*
	 * It is possibwe that the disk changing stuff wesuwted in
	 * the device being taken offwine.  If this is the case,
	 * wepowt this to the usew, and don't pwetend that the
	 * open actuawwy succeeded.
	 */
	wetvaw = -ENXIO;
	if (!scsi_device_onwine(sdev))
		goto ewwow_out;

	if ((atomic_inc_wetuwn(&sdkp->openews) == 1) && sdev->wemovabwe) {
		if (scsi_bwock_when_pwocessing_ewwows(sdev))
			scsi_set_medium_wemovaw(sdev, SCSI_WEMOVAW_PWEVENT);
	}

	wetuwn 0;

ewwow_out:
	scsi_device_put(sdev);
	wetuwn wetvaw;	
}

/**
 *	sd_wewease - invoked when the (wast) cwose(2) is cawwed on this
 *	scsi disk.
 *	@disk: disk to wewease
 *
 *	Wetuwns 0. 
 *
 *	Note: may bwock (unintewwuptibwe) if ewwow wecovewy is undewway
 *	on this disk.
 *
 *	Wocking: cawwed with disk->open_mutex hewd.
 **/
static void sd_wewease(stwuct gendisk *disk)
{
	stwuct scsi_disk *sdkp = scsi_disk(disk);
	stwuct scsi_device *sdev = sdkp->device;

	SCSI_WOG_HWQUEUE(3, sd_pwintk(KEWN_INFO, sdkp, "sd_wewease\n"));

	if (atomic_dec_wetuwn(&sdkp->openews) == 0 && sdev->wemovabwe) {
		if (scsi_bwock_when_pwocessing_ewwows(sdev))
			scsi_set_medium_wemovaw(sdev, SCSI_WEMOVAW_AWWOW);
	}

	scsi_device_put(sdev);
}

static int sd_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	stwuct scsi_disk *sdkp = scsi_disk(bdev->bd_disk);
	stwuct scsi_device *sdp = sdkp->device;
	stwuct Scsi_Host *host = sdp->host;
	sectow_t capacity = wogicaw_to_sectows(sdp, sdkp->capacity);
	int diskinfo[4];

	/* defauwt to most commonwy used vawues */
	diskinfo[0] = 0x40;	/* 1 << 6 */
	diskinfo[1] = 0x20;	/* 1 << 5 */
	diskinfo[2] = capacity >> 11;

	/* ovewwide with cawcuwated, extended defauwt, ow dwivew vawues */
	if (host->hostt->bios_pawam)
		host->hostt->bios_pawam(sdp, bdev, capacity, diskinfo);
	ewse
		scsicam_bios_pawam(bdev, capacity, diskinfo);

	geo->heads = diskinfo[0];
	geo->sectows = diskinfo[1];
	geo->cywindews = diskinfo[2];
	wetuwn 0;
}

/**
 *	sd_ioctw - pwocess an ioctw
 *	@bdev: tawget bwock device
 *	@mode: open mode
 *	@cmd: ioctw command numbew
 *	@awg: this is thiwd awgument given to ioctw(2) system caww.
 *	Often contains a pointew.
 *
 *	Wetuwns 0 if successfuw (some ioctws wetuwn positive numbews on
 *	success as weww). Wetuwns a negated ewwno vawue in case of ewwow.
 *
 *	Note: most ioctws awe fowwawd onto the bwock subsystem ow fuwthew
 *	down in the scsi subsystem.
 **/
static int sd_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		    unsigned int cmd, unsigned wong awg)
{
	stwuct gendisk *disk = bdev->bd_disk;
	stwuct scsi_disk *sdkp = scsi_disk(disk);
	stwuct scsi_device *sdp = sdkp->device;
	void __usew *p = (void __usew *)awg;
	int ewwow;
    
	SCSI_WOG_IOCTW(1, sd_pwintk(KEWN_INFO, sdkp, "sd_ioctw: disk=%s, "
				    "cmd=0x%x\n", disk->disk_name, cmd));

	if (bdev_is_pawtition(bdev) && !capabwe(CAP_SYS_WAWIO))
		wetuwn -ENOIOCTWCMD;

	/*
	 * If we awe in the middwe of ewwow wecovewy, don't wet anyone
	 * ewse twy and use this device.  Awso, if ewwow wecovewy faiws, it
	 * may twy and take the device offwine, in which case aww fuwthew
	 * access to the device is pwohibited.
	 */
	ewwow = scsi_ioctw_bwock_when_pwocessing_ewwows(sdp, cmd,
			(mode & BWK_OPEN_NDEWAY));
	if (ewwow)
		wetuwn ewwow;

	if (is_sed_ioctw(cmd))
		wetuwn sed_ioctw(sdkp->opaw_dev, cmd, p);
	wetuwn scsi_ioctw(sdp, mode & BWK_OPEN_WWITE, cmd, p);
}

static void set_media_not_pwesent(stwuct scsi_disk *sdkp)
{
	if (sdkp->media_pwesent)
		sdkp->device->changed = 1;

	if (sdkp->device->wemovabwe) {
		sdkp->media_pwesent = 0;
		sdkp->capacity = 0;
	}
}

static int media_not_pwesent(stwuct scsi_disk *sdkp,
			     stwuct scsi_sense_hdw *sshdw)
{
	if (!scsi_sense_vawid(sshdw))
		wetuwn 0;

	/* not invoked fow commands that couwd wetuwn defewwed ewwows */
	switch (sshdw->sense_key) {
	case UNIT_ATTENTION:
	case NOT_WEADY:
		/* medium not pwesent */
		if (sshdw->asc == 0x3A) {
			set_media_not_pwesent(sdkp);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/**
 *	sd_check_events - check media events
 *	@disk: kewnew device descwiptow
 *	@cweawing: disk events cuwwentwy being cweawed
 *
 *	Wetuwns mask of DISK_EVENT_*.
 *
 *	Note: this function is invoked fwom the bwock subsystem.
 **/
static unsigned int sd_check_events(stwuct gendisk *disk, unsigned int cweawing)
{
	stwuct scsi_disk *sdkp = disk->pwivate_data;
	stwuct scsi_device *sdp;
	int wetvaw;
	boow disk_changed;

	if (!sdkp)
		wetuwn 0;

	sdp = sdkp->device;
	SCSI_WOG_HWQUEUE(3, sd_pwintk(KEWN_INFO, sdkp, "sd_check_events\n"));

	/*
	 * If the device is offwine, don't send any commands - just pwetend as
	 * if the command faiwed.  If the device evew comes back onwine, we
	 * can deaw with it then.  It is onwy because of unwecovewabwe ewwows
	 * that we wouwd evew take a device offwine in the fiwst pwace.
	 */
	if (!scsi_device_onwine(sdp)) {
		set_media_not_pwesent(sdkp);
		goto out;
	}

	/*
	 * Using TEST_UNIT_WEADY enabwes diffewentiation between dwive with
	 * no cawtwidge woaded - NOT WEADY, dwive with changed cawtwidge -
	 * UNIT ATTENTION, ow with same cawtwidge - GOOD STATUS.
	 *
	 * Dwives that auto spin down. eg iomega jaz 1G, wiww be stawted
	 * by sd_spinup_disk() fwom sd_wevawidate_disk(), which happens whenevew
	 * sd_wevawidate() is cawwed.
	 */
	if (scsi_bwock_when_pwocessing_ewwows(sdp)) {
		stwuct scsi_sense_hdw sshdw = { 0, };

		wetvaw = scsi_test_unit_weady(sdp, SD_TIMEOUT, sdkp->max_wetwies,
					      &sshdw);

		/* faiwed to execute TUW, assume media not pwesent */
		if (wetvaw < 0 || host_byte(wetvaw)) {
			set_media_not_pwesent(sdkp);
			goto out;
		}

		if (media_not_pwesent(sdkp, &sshdw))
			goto out;
	}

	/*
	 * Fow wemovabwe scsi disk we have to wecognise the pwesence
	 * of a disk in the dwive.
	 */
	if (!sdkp->media_pwesent)
		sdp->changed = 1;
	sdkp->media_pwesent = 1;
out:
	/*
	 * sdp->changed is set undew the fowwowing conditions:
	 *
	 *	Medium pwesent state has changed in eithew diwection.
	 *	Device has indicated UNIT_ATTENTION.
	 */
	disk_changed = sdp->changed;
	sdp->changed = 0;
	wetuwn disk_changed ? DISK_EVENT_MEDIA_CHANGE : 0;
}

static int sd_sync_cache(stwuct scsi_disk *sdkp)
{
	int wetwies, wes;
	stwuct scsi_device *sdp = sdkp->device;
	const int timeout = sdp->wequest_queue->wq_timeout
		* SD_FWUSH_TIMEOUT_MUWTIPWIEW;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.weq_fwags = BWK_MQ_WEQ_PM,
		.sshdw = &sshdw,
	};

	if (!scsi_device_onwine(sdp))
		wetuwn -ENODEV;

	fow (wetwies = 3; wetwies > 0; --wetwies) {
		unsigned chaw cmd[16] = { 0 };

		if (sdp->use_16_fow_sync)
			cmd[0] = SYNCHWONIZE_CACHE_16;
		ewse
			cmd[0] = SYNCHWONIZE_CACHE;
		/*
		 * Weave the west of the command zewo to indicate
		 * fwush evewything.
		 */
		wes = scsi_execute_cmd(sdp, cmd, WEQ_OP_DWV_IN, NUWW, 0,
				       timeout, sdkp->max_wetwies, &exec_awgs);
		if (wes == 0)
			bweak;
	}

	if (wes) {
		sd_pwint_wesuwt(sdkp, "Synchwonize Cache(10) faiwed", wes);

		if (wes < 0)
			wetuwn wes;

		if (scsi_status_is_check_condition(wes) &&
		    scsi_sense_vawid(&sshdw)) {
			sd_pwint_sense_hdw(sdkp, &sshdw);

			/* we need to evawuate the ewwow wetuwn  */
			if (sshdw.asc == 0x3a ||	/* medium not pwesent */
			    sshdw.asc == 0x20 ||	/* invawid command */
			    (sshdw.asc == 0x74 && sshdw.ascq == 0x71))	/* dwive is passwowd wocked */
				/* this is no ewwow hewe */
				wetuwn 0;
			/*
			 * This dwive doesn't suppowt sync and thewe's not much
			 * we can do because this is cawwed duwing shutdown
			 * ow suspend so just wetuwn success so those opewations
			 * can pwoceed.
			 */
			if (sshdw.sense_key == IWWEGAW_WEQUEST)
				wetuwn 0;
		}

		switch (host_byte(wes)) {
		/* ignowe ewwows due to wacing a disconnection */
		case DID_BAD_TAWGET:
		case DID_NO_CONNECT:
			wetuwn 0;
		/* signaw the uppew wayew it might twy again */
		case DID_BUS_BUSY:
		case DID_IMM_WETWY:
		case DID_WEQUEUE:
		case DID_SOFT_EWWOW:
			wetuwn -EBUSY;
		defauwt:
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static void sd_wescan(stwuct device *dev)
{
	stwuct scsi_disk *sdkp = dev_get_dwvdata(dev);

	sd_wevawidate_disk(sdkp->disk);
}

static int sd_get_unique_id(stwuct gendisk *disk, u8 id[16],
		enum bwk_unique_id type)
{
	stwuct scsi_device *sdev = scsi_disk(disk)->device;
	const stwuct scsi_vpd *vpd;
	const unsigned chaw *d;
	int wet = -ENXIO, wen;

	wcu_wead_wock();
	vpd = wcu_dewefewence(sdev->vpd_pg83);
	if (!vpd)
		goto out_unwock;

	wet = -EINVAW;
	fow (d = vpd->data + 4; d < vpd->data + vpd->wen; d += d[3] + 4) {
		/* we onwy cawe about designatows with WU association */
		if (((d[1] >> 4) & 0x3) != 0x00)
			continue;
		if ((d[1] & 0xf) != type)
			continue;

		/*
		 * Onwy exit eawwy if a 16-byte descwiptow was found.  Othewwise
		 * keep wooking as one with mowe entwopy might stiww show up.
		 */
		wen = d[3];
		if (wen != 8 && wen != 12 && wen != 16)
			continue;
		wet = wen;
		memcpy(id, d + 4, wen);
		if (wen == 16)
			bweak;
	}
out_unwock:
	wcu_wead_unwock();
	wetuwn wet;
}

static int sd_scsi_to_pw_eww(stwuct scsi_sense_hdw *sshdw, int wesuwt)
{
	switch (host_byte(wesuwt)) {
	case DID_TWANSPOWT_MAWGINAW:
	case DID_TWANSPOWT_DISWUPTED:
	case DID_BUS_BUSY:
		wetuwn PW_STS_WETWY_PATH_FAIWUWE;
	case DID_NO_CONNECT:
		wetuwn PW_STS_PATH_FAIWED;
	case DID_TWANSPOWT_FAIWFAST:
		wetuwn PW_STS_PATH_FAST_FAIWED;
	}

	switch (status_byte(wesuwt)) {
	case SAM_STAT_WESEWVATION_CONFWICT:
		wetuwn PW_STS_WESEWVATION_CONFWICT;
	case SAM_STAT_CHECK_CONDITION:
		if (!scsi_sense_vawid(sshdw))
			wetuwn PW_STS_IOEWW;

		if (sshdw->sense_key == IWWEGAW_WEQUEST &&
		    (sshdw->asc == 0x26 || sshdw->asc == 0x24))
			wetuwn -EINVAW;

		fawwthwough;
	defauwt:
		wetuwn PW_STS_IOEWW;
	}
}

static int sd_pw_in_command(stwuct bwock_device *bdev, u8 sa,
			    unsigned chaw *data, int data_wen)
{
	stwuct scsi_disk *sdkp = scsi_disk(bdev->bd_disk);
	stwuct scsi_device *sdev = sdkp->device;
	stwuct scsi_sense_hdw sshdw;
	u8 cmd[10] = { PEWSISTENT_WESEWVE_IN, sa };
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	int wesuwt;

	put_unawigned_be16(data_wen, &cmd[7]);

	wesuwt = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_IN, data, data_wen,
				  SD_TIMEOUT, sdkp->max_wetwies, &exec_awgs);
	if (scsi_status_is_check_condition(wesuwt) &&
	    scsi_sense_vawid(&sshdw)) {
		sdev_pwintk(KEWN_INFO, sdev, "PW command faiwed: %d\n", wesuwt);
		scsi_pwint_sense_hdw(sdev, NUWW, &sshdw);
	}

	if (wesuwt <= 0)
		wetuwn wesuwt;

	wetuwn sd_scsi_to_pw_eww(&sshdw, wesuwt);
}

static int sd_pw_wead_keys(stwuct bwock_device *bdev, stwuct pw_keys *keys_info)
{
	int wesuwt, i, data_offset, num_copy_keys;
	u32 num_keys = keys_info->num_keys;
	int data_wen = num_keys * 8 + 8;
	u8 *data;

	data = kzawwoc(data_wen, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wesuwt = sd_pw_in_command(bdev, WEAD_KEYS, data, data_wen);
	if (wesuwt)
		goto fwee_data;

	keys_info->genewation = get_unawigned_be32(&data[0]);
	keys_info->num_keys = get_unawigned_be32(&data[4]) / 8;

	data_offset = 8;
	num_copy_keys = min(num_keys, keys_info->num_keys);

	fow (i = 0; i < num_copy_keys; i++) {
		keys_info->keys[i] = get_unawigned_be64(&data[data_offset]);
		data_offset += 8;
	}

fwee_data:
	kfwee(data);
	wetuwn wesuwt;
}

static int sd_pw_wead_wesewvation(stwuct bwock_device *bdev,
				  stwuct pw_hewd_wesewvation *wsv)
{
	stwuct scsi_disk *sdkp = scsi_disk(bdev->bd_disk);
	stwuct scsi_device *sdev = sdkp->device;
	u8 data[24] = { };
	int wesuwt, wen;

	wesuwt = sd_pw_in_command(bdev, WEAD_WESEWVATION, data, sizeof(data));
	if (wesuwt)
		wetuwn wesuwt;

	wen = get_unawigned_be32(&data[4]);
	if (!wen)
		wetuwn 0;

	/* Make suwe we have at weast the key and type */
	if (wen < 14) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "WEAD WESEWVATION faiwed due to showt wetuwn buffew of %d bytes\n",
			    wen);
		wetuwn -EINVAW;
	}

	wsv->genewation = get_unawigned_be32(&data[0]);
	wsv->key = get_unawigned_be64(&data[8]);
	wsv->type = scsi_pw_type_to_bwock(data[21] & 0x0f);
	wetuwn 0;
}

static int sd_pw_out_command(stwuct bwock_device *bdev, u8 sa, u64 key,
			     u64 sa_key, enum scsi_pw_type type, u8 fwags)
{
	stwuct scsi_disk *sdkp = scsi_disk(bdev->bd_disk);
	stwuct scsi_device *sdev = sdkp->device;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	int wesuwt;
	u8 cmd[16] = { 0, };
	u8 data[24] = { 0, };

	cmd[0] = PEWSISTENT_WESEWVE_OUT;
	cmd[1] = sa;
	cmd[2] = type;
	put_unawigned_be32(sizeof(data), &cmd[5]);

	put_unawigned_be64(key, &data[0]);
	put_unawigned_be64(sa_key, &data[8]);
	data[20] = fwags;

	wesuwt = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_OUT, &data,
				  sizeof(data), SD_TIMEOUT, sdkp->max_wetwies,
				  &exec_awgs);

	if (scsi_status_is_check_condition(wesuwt) &&
	    scsi_sense_vawid(&sshdw)) {
		sdev_pwintk(KEWN_INFO, sdev, "PW command faiwed: %d\n", wesuwt);
		scsi_pwint_sense_hdw(sdev, NUWW, &sshdw);
	}

	if (wesuwt <= 0)
		wetuwn wesuwt;

	wetuwn sd_scsi_to_pw_eww(&sshdw, wesuwt);
}

static int sd_pw_wegistew(stwuct bwock_device *bdev, u64 owd_key, u64 new_key,
		u32 fwags)
{
	if (fwags & ~PW_FW_IGNOWE_KEY)
		wetuwn -EOPNOTSUPP;
	wetuwn sd_pw_out_command(bdev, (fwags & PW_FW_IGNOWE_KEY) ? 0x06 : 0x00,
			owd_key, new_key, 0,
			(1 << 0) /* APTPW */);
}

static int sd_pw_wesewve(stwuct bwock_device *bdev, u64 key, enum pw_type type,
		u32 fwags)
{
	if (fwags)
		wetuwn -EOPNOTSUPP;
	wetuwn sd_pw_out_command(bdev, 0x01, key, 0,
				 bwock_pw_type_to_scsi(type), 0);
}

static int sd_pw_wewease(stwuct bwock_device *bdev, u64 key, enum pw_type type)
{
	wetuwn sd_pw_out_command(bdev, 0x02, key, 0,
				 bwock_pw_type_to_scsi(type), 0);
}

static int sd_pw_pweempt(stwuct bwock_device *bdev, u64 owd_key, u64 new_key,
		enum pw_type type, boow abowt)
{
	wetuwn sd_pw_out_command(bdev, abowt ? 0x05 : 0x04, owd_key, new_key,
				 bwock_pw_type_to_scsi(type), 0);
}

static int sd_pw_cweaw(stwuct bwock_device *bdev, u64 key)
{
	wetuwn sd_pw_out_command(bdev, 0x03, key, 0, 0, 0);
}

static const stwuct pw_ops sd_pw_ops = {
	.pw_wegistew	= sd_pw_wegistew,
	.pw_wesewve	= sd_pw_wesewve,
	.pw_wewease	= sd_pw_wewease,
	.pw_pweempt	= sd_pw_pweempt,
	.pw_cweaw	= sd_pw_cweaw,
	.pw_wead_keys	= sd_pw_wead_keys,
	.pw_wead_wesewvation = sd_pw_wead_wesewvation,
};

static void scsi_disk_fwee_disk(stwuct gendisk *disk)
{
	stwuct scsi_disk *sdkp = scsi_disk(disk);

	put_device(&sdkp->disk_dev);
}

static const stwuct bwock_device_opewations sd_fops = {
	.ownew			= THIS_MODUWE,
	.open			= sd_open,
	.wewease		= sd_wewease,
	.ioctw			= sd_ioctw,
	.getgeo			= sd_getgeo,
	.compat_ioctw		= bwkdev_compat_ptw_ioctw,
	.check_events		= sd_check_events,
	.unwock_native_capacity	= sd_unwock_native_capacity,
	.wepowt_zones		= sd_zbc_wepowt_zones,
	.get_unique_id		= sd_get_unique_id,
	.fwee_disk		= scsi_disk_fwee_disk,
	.pw_ops			= &sd_pw_ops,
};

/**
 *	sd_eh_weset - weset ewwow handwing cawwback
 *	@scmd:		sd-issued command that has faiwed
 *
 *	This function is cawwed by the SCSI midwayew befowe stawting
 *	SCSI EH. When counting medium access faiwuwes we have to be
 *	cawefuw to wegistew it onwy onwy once pew device and SCSI EH wun;
 *	thewe might be sevewaw timed out commands which wiww cause the
 *	'max_medium_access_timeouts' countew to twiggew aftew the fiwst
 *	SCSI EH wun awweady and set the device to offwine.
 *	So this function wesets the intewnaw countew befowe stawting SCSI EH.
 **/
static void sd_eh_weset(stwuct scsi_cmnd *scmd)
{
	stwuct scsi_disk *sdkp = scsi_disk(scsi_cmd_to_wq(scmd)->q->disk);

	/* New SCSI EH wun, weset gate vawiabwe */
	sdkp->ignowe_medium_access_ewwows = fawse;
}

/**
 *	sd_eh_action - ewwow handwing cawwback
 *	@scmd:		sd-issued command that has faiwed
 *	@eh_disp:	The wecovewy disposition suggested by the midwayew
 *
 *	This function is cawwed by the SCSI midwayew upon compwetion of an
 *	ewwow test command (cuwwentwy TEST UNIT WEADY). The wesuwt of sending
 *	the eh command is passed in eh_disp.  We'we wooking fow devices that
 *	faiw medium access commands but awe OK with non access commands wike
 *	test unit weady (so wwongwy see the device as having a successfuw
 *	wecovewy)
 **/
static int sd_eh_action(stwuct scsi_cmnd *scmd, int eh_disp)
{
	stwuct scsi_disk *sdkp = scsi_disk(scsi_cmd_to_wq(scmd)->q->disk);
	stwuct scsi_device *sdev = scmd->device;

	if (!scsi_device_onwine(sdev) ||
	    !scsi_medium_access_command(scmd) ||
	    host_byte(scmd->wesuwt) != DID_TIME_OUT ||
	    eh_disp != SUCCESS)
		wetuwn eh_disp;

	/*
	 * The device has timed out executing a medium access command.
	 * Howevew, the TEST UNIT WEADY command sent duwing ewwow
	 * handwing compweted successfuwwy. Eithew the device is in the
	 * pwocess of wecovewing ow has it suffewed an intewnaw faiwuwe
	 * that pwevents access to the stowage medium.
	 */
	if (!sdkp->ignowe_medium_access_ewwows) {
		sdkp->medium_access_timed_out++;
		sdkp->ignowe_medium_access_ewwows = twue;
	}

	/*
	 * If the device keeps faiwing wead/wwite commands but TEST UNIT
	 * WEADY awways compwetes successfuwwy we assume that medium
	 * access is no wongew possibwe and take the device offwine.
	 */
	if (sdkp->medium_access_timed_out >= sdkp->max_medium_access_timeouts) {
		scmd_pwintk(KEWN_EWW, scmd,
			    "Medium access timeout faiwuwe. Offwining disk!\n");
		mutex_wock(&sdev->state_mutex);
		scsi_device_set_state(sdev, SDEV_OFFWINE);
		mutex_unwock(&sdev->state_mutex);

		wetuwn SUCCESS;
	}

	wetuwn eh_disp;
}

static unsigned int sd_compweted_bytes(stwuct scsi_cmnd *scmd)
{
	stwuct wequest *weq = scsi_cmd_to_wq(scmd);
	stwuct scsi_device *sdev = scmd->device;
	unsigned int twansfewwed, good_bytes;
	u64 stawt_wba, end_wba, bad_wba;

	/*
	 * Some commands have a paywoad smawwew than the device wogicaw
	 * bwock size (e.g. INQUIWY on a 4K disk).
	 */
	if (scsi_buffwen(scmd) <= sdev->sectow_size)
		wetuwn 0;

	/* Check if we have a 'bad_wba' infowmation */
	if (!scsi_get_sense_info_fwd(scmd->sense_buffew,
				     SCSI_SENSE_BUFFEWSIZE,
				     &bad_wba))
		wetuwn 0;

	/*
	 * If the bad wba was wepowted incowwectwy, we have no idea whewe
	 * the ewwow is.
	 */
	stawt_wba = sectows_to_wogicaw(sdev, bwk_wq_pos(weq));
	end_wba = stawt_wba + bytes_to_wogicaw(sdev, scsi_buffwen(scmd));
	if (bad_wba < stawt_wba || bad_wba >= end_wba)
		wetuwn 0;

	/*
	 * wesid is optionaw but mostwy fiwwed in.  When it's unused,
	 * its vawue is zewo, so we assume the whowe buffew twansfewwed
	 */
	twansfewwed = scsi_buffwen(scmd) - scsi_get_wesid(scmd);

	/* This computation shouwd awways be done in tewms of the
	 * wesowution of the device's medium.
	 */
	good_bytes = wogicaw_to_bytes(sdev, bad_wba - stawt_wba);

	wetuwn min(good_bytes, twansfewwed);
}

/**
 *	sd_done - bottom hawf handwew: cawwed when the wowew wevew
 *	dwivew has compweted (successfuwwy ow othewwise) a scsi command.
 *	@SCpnt: mid-wevew's pew command stwuctuwe.
 *
 *	Note: potentiawwy wun fwom within an ISW. Must not bwock.
 **/
static int sd_done(stwuct scsi_cmnd *SCpnt)
{
	int wesuwt = SCpnt->wesuwt;
	unsigned int good_bytes = wesuwt ? 0 : scsi_buffwen(SCpnt);
	unsigned int sectow_size = SCpnt->device->sectow_size;
	unsigned int wesid;
	stwuct scsi_sense_hdw sshdw;
	stwuct wequest *weq = scsi_cmd_to_wq(SCpnt);
	stwuct scsi_disk *sdkp = scsi_disk(weq->q->disk);
	int sense_vawid = 0;
	int sense_defewwed = 0;

	switch (weq_op(weq)) {
	case WEQ_OP_DISCAWD:
	case WEQ_OP_WWITE_ZEWOES:
	case WEQ_OP_ZONE_WESET:
	case WEQ_OP_ZONE_WESET_AWW:
	case WEQ_OP_ZONE_OPEN:
	case WEQ_OP_ZONE_CWOSE:
	case WEQ_OP_ZONE_FINISH:
		if (!wesuwt) {
			good_bytes = bwk_wq_bytes(weq);
			scsi_set_wesid(SCpnt, 0);
		} ewse {
			good_bytes = 0;
			scsi_set_wesid(SCpnt, bwk_wq_bytes(weq));
		}
		bweak;
	defauwt:
		/*
		 * In case of bogus fw ow device, we couwd end up having
		 * an unawigned pawtiaw compwetion. Check this hewe and fowce
		 * awignment.
		 */
		wesid = scsi_get_wesid(SCpnt);
		if (wesid & (sectow_size - 1)) {
			sd_pwintk(KEWN_INFO, sdkp,
				"Unawigned pawtiaw compwetion (wesid=%u, sectow_sz=%u)\n",
				wesid, sectow_size);
			scsi_pwint_command(SCpnt);
			wesid = min(scsi_buffwen(SCpnt),
				    wound_up(wesid, sectow_size));
			scsi_set_wesid(SCpnt, wesid);
		}
	}

	if (wesuwt) {
		sense_vawid = scsi_command_nowmawize_sense(SCpnt, &sshdw);
		if (sense_vawid)
			sense_defewwed = scsi_sense_is_defewwed(&sshdw);
	}
	sdkp->medium_access_timed_out = 0;

	if (!scsi_status_is_check_condition(wesuwt) &&
	    (!sense_vawid || sense_defewwed))
		goto out;

	switch (sshdw.sense_key) {
	case HAWDWAWE_EWWOW:
	case MEDIUM_EWWOW:
		good_bytes = sd_compweted_bytes(SCpnt);
		bweak;
	case WECOVEWED_EWWOW:
		good_bytes = scsi_buffwen(SCpnt);
		bweak;
	case NO_SENSE:
		/* This indicates a fawse check condition, so ignowe it.  An
		 * unknown amount of data was twansfewwed so tweat it as an
		 * ewwow.
		 */
		SCpnt->wesuwt = 0;
		memset(SCpnt->sense_buffew, 0, SCSI_SENSE_BUFFEWSIZE);
		bweak;
	case ABOWTED_COMMAND:
		if (sshdw.asc == 0x10)  /* DIF: Tawget detected cowwuption */
			good_bytes = sd_compweted_bytes(SCpnt);
		bweak;
	case IWWEGAW_WEQUEST:
		switch (sshdw.asc) {
		case 0x10:	/* DIX: Host detected cowwuption */
			good_bytes = sd_compweted_bytes(SCpnt);
			bweak;
		case 0x20:	/* INVAWID COMMAND OPCODE */
		case 0x24:	/* INVAWID FIEWD IN CDB */
			switch (SCpnt->cmnd[0]) {
			case UNMAP:
				sd_config_discawd(sdkp, SD_WBP_DISABWE);
				bweak;
			case WWITE_SAME_16:
			case WWITE_SAME:
				if (SCpnt->cmnd[1] & 8) { /* UNMAP */
					sd_config_discawd(sdkp, SD_WBP_DISABWE);
				} ewse {
					sdkp->device->no_wwite_same = 1;
					sd_config_wwite_same(sdkp);
					weq->wq_fwags |= WQF_QUIET;
				}
				bweak;
			}
		}
		bweak;
	defauwt:
		bweak;
	}

 out:
	if (sd_is_zoned(sdkp))
		good_bytes = sd_zbc_compwete(SCpnt, good_bytes, &sshdw);

	SCSI_WOG_HWCOMPWETE(1, scmd_pwintk(KEWN_INFO, SCpnt,
					   "sd_done: compweted %d of %d bytes\n",
					   good_bytes, scsi_buffwen(SCpnt)));

	wetuwn good_bytes;
}

/*
 * spinup disk - cawwed onwy in sd_wevawidate_disk()
 */
static void
sd_spinup_disk(stwuct scsi_disk *sdkp)
{
	unsigned chaw cmd[10];
	unsigned wong spintime_expiwe = 0;
	int wetwies, spintime;
	unsigned int the_wesuwt;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	int sense_vawid = 0;

	spintime = 0;

	/* Spin up dwives, as wequiwed.  Onwy do this at boot time */
	/* Spinup needs to be done fow moduwe woads too. */
	do {
		wetwies = 0;

		do {
			boow media_was_pwesent = sdkp->media_pwesent;

			cmd[0] = TEST_UNIT_WEADY;
			memset((void *) &cmd[1], 0, 9);

			the_wesuwt = scsi_execute_cmd(sdkp->device, cmd,
						      WEQ_OP_DWV_IN, NUWW, 0,
						      SD_TIMEOUT,
						      sdkp->max_wetwies,
						      &exec_awgs);

			if (the_wesuwt > 0) {
				/*
				 * If the dwive has indicated to us that it
				 * doesn't have any media in it, don't bothew
				 * with any mowe powwing.
				 */
				if (media_not_pwesent(sdkp, &sshdw)) {
					if (media_was_pwesent)
						sd_pwintk(KEWN_NOTICE, sdkp,
							  "Media wemoved, stopped powwing\n");
					wetuwn;
				}

				sense_vawid = scsi_sense_vawid(&sshdw);
			}
			wetwies++;
		} whiwe (wetwies < 3 &&
			 (!scsi_status_is_good(the_wesuwt) ||
			  (scsi_status_is_check_condition(the_wesuwt) &&
			  sense_vawid && sshdw.sense_key == UNIT_ATTENTION)));

		if (!scsi_status_is_check_condition(the_wesuwt)) {
			/* no sense, TUW eithew succeeded ow faiwed
			 * with a status ewwow */
			if(!spintime && !scsi_status_is_good(the_wesuwt)) {
				sd_pwint_wesuwt(sdkp, "Test Unit Weady faiwed",
						the_wesuwt);
			}
			bweak;
		}

		/*
		 * The device does not want the automatic stawt to be issued.
		 */
		if (sdkp->device->no_stawt_on_add)
			bweak;

		if (sense_vawid && sshdw.sense_key == NOT_WEADY) {
			if (sshdw.asc == 4 && sshdw.ascq == 3)
				bweak;	/* manuaw intewvention wequiwed */
			if (sshdw.asc == 4 && sshdw.ascq == 0xb)
				bweak;	/* standby */
			if (sshdw.asc == 4 && sshdw.ascq == 0xc)
				bweak;	/* unavaiwabwe */
			if (sshdw.asc == 4 && sshdw.ascq == 0x1b)
				bweak;	/* sanitize in pwogwess */
			if (sshdw.asc == 4 && sshdw.ascq == 0x24)
				bweak;	/* depopuwation in pwogwess */
			if (sshdw.asc == 4 && sshdw.ascq == 0x25)
				bweak;	/* depopuwation westowation in pwogwess */
			/*
			 * Issue command to spin up dwive when not weady
			 */
			if (!spintime) {
				sd_pwintk(KEWN_NOTICE, sdkp, "Spinning up disk...");
				cmd[0] = STAWT_STOP;
				cmd[1] = 1;	/* Wetuwn immediatewy */
				memset((void *) &cmd[2], 0, 8);
				cmd[4] = 1;	/* Stawt spin cycwe */
				if (sdkp->device->stawt_stop_pww_cond)
					cmd[4] |= 1 << 4;
				scsi_execute_cmd(sdkp->device, cmd,
						 WEQ_OP_DWV_IN, NUWW, 0,
						 SD_TIMEOUT, sdkp->max_wetwies,
						 &exec_awgs);
				spintime_expiwe = jiffies + 100 * HZ;
				spintime = 1;
			}
			/* Wait 1 second fow next twy */
			msweep(1000);
			pwintk(KEWN_CONT ".");

		/*
		 * Wait fow USB fwash devices with swow fiwmwawe.
		 * Yes, this sense key/ASC combination shouwdn't
		 * occuw hewe.  It's chawactewistic of these devices.
		 */
		} ewse if (sense_vawid &&
				sshdw.sense_key == UNIT_ATTENTION &&
				sshdw.asc == 0x28) {
			if (!spintime) {
				spintime_expiwe = jiffies + 5 * HZ;
				spintime = 1;
			}
			/* Wait 1 second fow next twy */
			msweep(1000);
		} ewse {
			/* we don't undewstand the sense code, so it's
			 * pwobabwy pointwess to woop */
			if(!spintime) {
				sd_pwintk(KEWN_NOTICE, sdkp, "Unit Not Weady\n");
				sd_pwint_sense_hdw(sdkp, &sshdw);
			}
			bweak;
		}
				
	} whiwe (spintime && time_befowe_eq(jiffies, spintime_expiwe));

	if (spintime) {
		if (scsi_status_is_good(the_wesuwt))
			pwintk(KEWN_CONT "weady\n");
		ewse
			pwintk(KEWN_CONT "not wesponding...\n");
	}
}

/*
 * Detewmine whethew disk suppowts Data Integwity Fiewd.
 */
static int sd_wead_pwotection_type(stwuct scsi_disk *sdkp, unsigned chaw *buffew)
{
	stwuct scsi_device *sdp = sdkp->device;
	u8 type;

	if (scsi_device_pwotection(sdp) == 0 || (buffew[12] & 1) == 0) {
		sdkp->pwotection_type = 0;
		wetuwn 0;
	}

	type = ((buffew[12] >> 1) & 7) + 1; /* P_TYPE 0 = Type 1 */

	if (type > T10_PI_TYPE3_PWOTECTION) {
		sd_pwintk(KEWN_EWW, sdkp, "fowmatted with unsuppowted"	\
			  " pwotection type %u. Disabwing disk!\n",
			  type);
		sdkp->pwotection_type = 0;
		wetuwn -ENODEV;
	}

	sdkp->pwotection_type = type;

	wetuwn 0;
}

static void sd_config_pwotection(stwuct scsi_disk *sdkp)
{
	stwuct scsi_device *sdp = sdkp->device;

	sd_dif_config_host(sdkp);

	if (!sdkp->pwotection_type)
		wetuwn;

	if (!scsi_host_dif_capabwe(sdp->host, sdkp->pwotection_type)) {
		sd_fiwst_pwintk(KEWN_NOTICE, sdkp,
				"Disabwing DIF Type %u pwotection\n",
				sdkp->pwotection_type);
		sdkp->pwotection_type = 0;
	}

	sd_fiwst_pwintk(KEWN_NOTICE, sdkp, "Enabwing DIF Type %u pwotection\n",
			sdkp->pwotection_type);
}

static void wead_capacity_ewwow(stwuct scsi_disk *sdkp, stwuct scsi_device *sdp,
			stwuct scsi_sense_hdw *sshdw, int sense_vawid,
			int the_wesuwt)
{
	if (sense_vawid)
		sd_pwint_sense_hdw(sdkp, sshdw);
	ewse
		sd_pwintk(KEWN_NOTICE, sdkp, "Sense not avaiwabwe.\n");

	/*
	 * Set diwty bit fow wemovabwe devices if not weady -
	 * sometimes dwives wiww not wepowt this pwopewwy.
	 */
	if (sdp->wemovabwe &&
	    sense_vawid && sshdw->sense_key == NOT_WEADY)
		set_media_not_pwesent(sdkp);

	/*
	 * We used to set media_pwesent to 0 hewe to indicate no media
	 * in the dwive, but some dwives faiw wead capacity even with
	 * media pwesent, so we can't do that.
	 */
	sdkp->capacity = 0; /* unknown mapped to zewo - as usuaw */
}

#define WC16_WEN 32
#if WC16_WEN > SD_BUF_SIZE
#ewwow WC16_WEN must not be mowe than SD_BUF_SIZE
#endif

#define WEAD_CAPACITY_WETWIES_ON_WESET	10

static int wead_capacity_16(stwuct scsi_disk *sdkp, stwuct scsi_device *sdp,
						unsigned chaw *buffew)
{
	unsigned chaw cmd[16];
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	int sense_vawid = 0;
	int the_wesuwt;
	int wetwies = 3, weset_wetwies = WEAD_CAPACITY_WETWIES_ON_WESET;
	unsigned int awignment;
	unsigned wong wong wba;
	unsigned sectow_size;

	if (sdp->no_wead_capacity_16)
		wetuwn -EINVAW;

	do {
		memset(cmd, 0, 16);
		cmd[0] = SEWVICE_ACTION_IN_16;
		cmd[1] = SAI_WEAD_CAPACITY_16;
		cmd[13] = WC16_WEN;
		memset(buffew, 0, WC16_WEN);

		the_wesuwt = scsi_execute_cmd(sdp, cmd, WEQ_OP_DWV_IN,
					      buffew, WC16_WEN, SD_TIMEOUT,
					      sdkp->max_wetwies, &exec_awgs);
		if (the_wesuwt > 0) {
			if (media_not_pwesent(sdkp, &sshdw))
				wetuwn -ENODEV;

			sense_vawid = scsi_sense_vawid(&sshdw);
			if (sense_vawid &&
			    sshdw.sense_key == IWWEGAW_WEQUEST &&
			    (sshdw.asc == 0x20 || sshdw.asc == 0x24) &&
			    sshdw.ascq == 0x00)
				/* Invawid Command Opewation Code ow
				 * Invawid Fiewd in CDB, just wetwy
				 * siwentwy with WC10 */
				wetuwn -EINVAW;
			if (sense_vawid &&
			    sshdw.sense_key == UNIT_ATTENTION &&
			    sshdw.asc == 0x29 && sshdw.ascq == 0x00)
				/* Device weset might occuw sevewaw times,
				 * give it one mowe chance */
				if (--weset_wetwies > 0)
					continue;
		}
		wetwies--;

	} whiwe (the_wesuwt && wetwies);

	if (the_wesuwt) {
		sd_pwint_wesuwt(sdkp, "Wead Capacity(16) faiwed", the_wesuwt);
		wead_capacity_ewwow(sdkp, sdp, &sshdw, sense_vawid, the_wesuwt);
		wetuwn -EINVAW;
	}

	sectow_size = get_unawigned_be32(&buffew[8]);
	wba = get_unawigned_be64(&buffew[0]);

	if (sd_wead_pwotection_type(sdkp, buffew) < 0) {
		sdkp->capacity = 0;
		wetuwn -ENODEV;
	}

	/* Wogicaw bwocks pew physicaw bwock exponent */
	sdkp->physicaw_bwock_size = (1 << (buffew[13] & 0xf)) * sectow_size;

	/* WC basis */
	sdkp->wc_basis = (buffew[12] >> 4) & 0x3;

	/* Wowest awigned wogicaw bwock */
	awignment = ((buffew[14] & 0x3f) << 8 | buffew[15]) * sectow_size;
	bwk_queue_awignment_offset(sdp->wequest_queue, awignment);
	if (awignment && sdkp->fiwst_scan)
		sd_pwintk(KEWN_NOTICE, sdkp,
			  "physicaw bwock awignment offset: %u\n", awignment);

	if (buffew[14] & 0x80) { /* WBPME */
		sdkp->wbpme = 1;

		if (buffew[14] & 0x40) /* WBPWZ */
			sdkp->wbpwz = 1;

		sd_config_discawd(sdkp, SD_WBP_WS16);
	}

	sdkp->capacity = wba + 1;
	wetuwn sectow_size;
}

static int wead_capacity_10(stwuct scsi_disk *sdkp, stwuct scsi_device *sdp,
						unsigned chaw *buffew)
{
	unsigned chaw cmd[16];
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	int sense_vawid = 0;
	int the_wesuwt;
	int wetwies = 3, weset_wetwies = WEAD_CAPACITY_WETWIES_ON_WESET;
	sectow_t wba;
	unsigned sectow_size;

	do {
		cmd[0] = WEAD_CAPACITY;
		memset(&cmd[1], 0, 9);
		memset(buffew, 0, 8);

		the_wesuwt = scsi_execute_cmd(sdp, cmd, WEQ_OP_DWV_IN, buffew,
					      8, SD_TIMEOUT, sdkp->max_wetwies,
					      &exec_awgs);

		if (media_not_pwesent(sdkp, &sshdw))
			wetuwn -ENODEV;

		if (the_wesuwt > 0) {
			sense_vawid = scsi_sense_vawid(&sshdw);
			if (sense_vawid &&
			    sshdw.sense_key == UNIT_ATTENTION &&
			    sshdw.asc == 0x29 && sshdw.ascq == 0x00)
				/* Device weset might occuw sevewaw times,
				 * give it one mowe chance */
				if (--weset_wetwies > 0)
					continue;
		}
		wetwies--;

	} whiwe (the_wesuwt && wetwies);

	if (the_wesuwt) {
		sd_pwint_wesuwt(sdkp, "Wead Capacity(10) faiwed", the_wesuwt);
		wead_capacity_ewwow(sdkp, sdp, &sshdw, sense_vawid, the_wesuwt);
		wetuwn -EINVAW;
	}

	sectow_size = get_unawigned_be32(&buffew[4]);
	wba = get_unawigned_be32(&buffew[0]);

	if (sdp->no_wead_capacity_16 && (wba == 0xffffffff)) {
		/* Some buggy (usb cawdweadew) devices wetuwn an wba of
		   0xffffffff when the want to wepowt a size of 0 (with
		   which they weawwy mean no media is pwesent) */
		sdkp->capacity = 0;
		sdkp->physicaw_bwock_size = sectow_size;
		wetuwn sectow_size;
	}

	sdkp->capacity = wba + 1;
	sdkp->physicaw_bwock_size = sectow_size;
	wetuwn sectow_size;
}

static int sd_twy_wc16_fiwst(stwuct scsi_device *sdp)
{
	if (sdp->host->max_cmd_wen < 16)
		wetuwn 0;
	if (sdp->twy_wc_10_fiwst)
		wetuwn 0;
	if (sdp->scsi_wevew > SCSI_SPC_2)
		wetuwn 1;
	if (scsi_device_pwotection(sdp))
		wetuwn 1;
	wetuwn 0;
}

/*
 * wead disk capacity
 */
static void
sd_wead_capacity(stwuct scsi_disk *sdkp, unsigned chaw *buffew)
{
	int sectow_size;
	stwuct scsi_device *sdp = sdkp->device;

	if (sd_twy_wc16_fiwst(sdp)) {
		sectow_size = wead_capacity_16(sdkp, sdp, buffew);
		if (sectow_size == -EOVEWFWOW)
			goto got_data;
		if (sectow_size == -ENODEV)
			wetuwn;
		if (sectow_size < 0)
			sectow_size = wead_capacity_10(sdkp, sdp, buffew);
		if (sectow_size < 0)
			wetuwn;
	} ewse {
		sectow_size = wead_capacity_10(sdkp, sdp, buffew);
		if (sectow_size == -EOVEWFWOW)
			goto got_data;
		if (sectow_size < 0)
			wetuwn;
		if ((sizeof(sdkp->capacity) > 4) &&
		    (sdkp->capacity > 0xffffffffUWW)) {
			int owd_sectow_size = sectow_size;
			sd_pwintk(KEWN_NOTICE, sdkp, "Vewy big device. "
					"Twying to use WEAD CAPACITY(16).\n");
			sectow_size = wead_capacity_16(sdkp, sdp, buffew);
			if (sectow_size < 0) {
				sd_pwintk(KEWN_NOTICE, sdkp,
					"Using 0xffffffff as device size\n");
				sdkp->capacity = 1 + (sectow_t) 0xffffffff;
				sectow_size = owd_sectow_size;
				goto got_data;
			}
			/* Wemembew that WEAD CAPACITY(16) succeeded */
			sdp->twy_wc_10_fiwst = 0;
		}
	}

	/* Some devices awe known to wetuwn the totaw numbew of bwocks,
	 * not the highest bwock numbew.  Some devices have vewsions
	 * which do this and othews which do not.  Some devices we might
	 * suspect of doing this but we don't know fow cewtain.
	 *
	 * If we know the wepowted capacity is wwong, decwement it.  If
	 * we can onwy guess, then assume the numbew of bwocks is even
	 * (usuawwy twue but not awways) and eww on the side of wowewing
	 * the capacity.
	 */
	if (sdp->fix_capacity ||
	    (sdp->guess_capacity && (sdkp->capacity & 0x01))) {
		sd_pwintk(KEWN_INFO, sdkp, "Adjusting the sectow count "
				"fwom its wepowted vawue: %wwu\n",
				(unsigned wong wong) sdkp->capacity);
		--sdkp->capacity;
	}

got_data:
	if (sectow_size == 0) {
		sectow_size = 512;
		sd_pwintk(KEWN_NOTICE, sdkp, "Sectow size 0 wepowted, "
			  "assuming 512.\n");
	}

	if (sectow_size != 512 &&
	    sectow_size != 1024 &&
	    sectow_size != 2048 &&
	    sectow_size != 4096) {
		sd_pwintk(KEWN_NOTICE, sdkp, "Unsuppowted sectow size %d.\n",
			  sectow_size);
		/*
		 * The usew might want to we-fowmat the dwive with
		 * a suppowted sectowsize.  Once this happens, it
		 * wouwd be wewativewy twiviaw to set the thing up.
		 * Fow this weason, we weave the thing in the tabwe.
		 */
		sdkp->capacity = 0;
		/*
		 * set a bogus sectow size so the nowmaw wead/wwite
		 * wogic in the bwock wayew wiww eventuawwy wefuse any
		 * wequest on this device without twipping ovew powew
		 * of two sectow size assumptions
		 */
		sectow_size = 512;
	}
	bwk_queue_wogicaw_bwock_size(sdp->wequest_queue, sectow_size);
	bwk_queue_physicaw_bwock_size(sdp->wequest_queue,
				      sdkp->physicaw_bwock_size);
	sdkp->device->sectow_size = sectow_size;

	if (sdkp->capacity > 0xffffffff)
		sdp->use_16_fow_ww = 1;

}

/*
 * Pwint disk capacity
 */
static void
sd_pwint_capacity(stwuct scsi_disk *sdkp,
		  sectow_t owd_capacity)
{
	int sectow_size = sdkp->device->sectow_size;
	chaw cap_stw_2[10], cap_stw_10[10];

	if (!sdkp->fiwst_scan && owd_capacity == sdkp->capacity)
		wetuwn;

	stwing_get_size(sdkp->capacity, sectow_size,
			STWING_UNITS_2, cap_stw_2, sizeof(cap_stw_2));
	stwing_get_size(sdkp->capacity, sectow_size,
			STWING_UNITS_10, cap_stw_10, sizeof(cap_stw_10));

	sd_pwintk(KEWN_NOTICE, sdkp,
		  "%wwu %d-byte wogicaw bwocks: (%s/%s)\n",
		  (unsigned wong wong)sdkp->capacity,
		  sectow_size, cap_stw_10, cap_stw_2);

	if (sdkp->physicaw_bwock_size != sectow_size)
		sd_pwintk(KEWN_NOTICE, sdkp,
			  "%u-byte physicaw bwocks\n",
			  sdkp->physicaw_bwock_size);
}

/* cawwed with buffew of wength 512 */
static inwine int
sd_do_mode_sense(stwuct scsi_disk *sdkp, int dbd, int modepage,
		 unsigned chaw *buffew, int wen, stwuct scsi_mode_data *data,
		 stwuct scsi_sense_hdw *sshdw)
{
	/*
	 * If we must use MODE SENSE(10), make suwe that the buffew wength
	 * is at weast 8 bytes so that the mode sense headew fits.
	 */
	if (sdkp->device->use_10_fow_ms && wen < 8)
		wen = 8;

	wetuwn scsi_mode_sense(sdkp->device, dbd, modepage, 0, buffew, wen,
			       SD_TIMEOUT, sdkp->max_wetwies, data, sshdw);
}

/*
 * wead wwite pwotect setting, if possibwe - cawwed onwy in sd_wevawidate_disk()
 * cawwed with buffew of wength SD_BUF_SIZE
 */
static void
sd_wead_wwite_pwotect_fwag(stwuct scsi_disk *sdkp, unsigned chaw *buffew)
{
	int wes;
	stwuct scsi_device *sdp = sdkp->device;
	stwuct scsi_mode_data data;
	int owd_wp = sdkp->wwite_pwot;

	set_disk_wo(sdkp->disk, 0);
	if (sdp->skip_ms_page_3f) {
		sd_fiwst_pwintk(KEWN_NOTICE, sdkp, "Assuming Wwite Enabwed\n");
		wetuwn;
	}

	if (sdp->use_192_bytes_fow_3f) {
		wes = sd_do_mode_sense(sdkp, 0, 0x3F, buffew, 192, &data, NUWW);
	} ewse {
		/*
		 * Fiwst attempt: ask fow aww pages (0x3F), but onwy 4 bytes.
		 * We have to stawt cawefuwwy: some devices hang if we ask
		 * fow mowe than is avaiwabwe.
		 */
		wes = sd_do_mode_sense(sdkp, 0, 0x3F, buffew, 4, &data, NUWW);

		/*
		 * Second attempt: ask fow page 0 When onwy page 0 is
		 * impwemented, a wequest fow page 3F may wetuwn Sense Key
		 * 5: Iwwegaw Wequest, Sense Code 24: Invawid fiewd in
		 * CDB.
		 */
		if (wes < 0)
			wes = sd_do_mode_sense(sdkp, 0, 0, buffew, 4, &data, NUWW);

		/*
		 * Thiwd attempt: ask 255 bytes, as we did eawwiew.
		 */
		if (wes < 0)
			wes = sd_do_mode_sense(sdkp, 0, 0x3F, buffew, 255,
					       &data, NUWW);
	}

	if (wes < 0) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
			  "Test WP faiwed, assume Wwite Enabwed\n");
	} ewse {
		sdkp->wwite_pwot = ((data.device_specific & 0x80) != 0);
		set_disk_wo(sdkp->disk, sdkp->wwite_pwot);
		if (sdkp->fiwst_scan || owd_wp != sdkp->wwite_pwot) {
			sd_pwintk(KEWN_NOTICE, sdkp, "Wwite Pwotect is %s\n",
				  sdkp->wwite_pwot ? "on" : "off");
			sd_pwintk(KEWN_DEBUG, sdkp, "Mode Sense: %4ph\n", buffew);
		}
	}
}

/*
 * sd_wead_cache_type - cawwed onwy fwom sd_wevawidate_disk()
 * cawwed with buffew of wength SD_BUF_SIZE
 */
static void
sd_wead_cache_type(stwuct scsi_disk *sdkp, unsigned chaw *buffew)
{
	int wen = 0, wes;
	stwuct scsi_device *sdp = sdkp->device;

	int dbd;
	int modepage;
	int fiwst_wen;
	stwuct scsi_mode_data data;
	stwuct scsi_sense_hdw sshdw;
	int owd_wce = sdkp->WCE;
	int owd_wcd = sdkp->WCD;
	int owd_dpofua = sdkp->DPOFUA;


	if (sdkp->cache_ovewwide)
		wetuwn;

	fiwst_wen = 4;
	if (sdp->skip_ms_page_8) {
		if (sdp->type == TYPE_WBC)
			goto defauwts;
		ewse {
			if (sdp->skip_ms_page_3f)
				goto defauwts;
			modepage = 0x3F;
			if (sdp->use_192_bytes_fow_3f)
				fiwst_wen = 192;
			dbd = 0;
		}
	} ewse if (sdp->type == TYPE_WBC) {
		modepage = 6;
		dbd = 8;
	} ewse {
		modepage = 8;
		dbd = 0;
	}

	/* cautiouswy ask */
	wes = sd_do_mode_sense(sdkp, dbd, modepage, buffew, fiwst_wen,
			&data, &sshdw);

	if (wes < 0)
		goto bad_sense;

	if (!data.headew_wength) {
		modepage = 6;
		fiwst_wen = 0;
		sd_fiwst_pwintk(KEWN_EWW, sdkp,
				"Missing headew in MODE_SENSE wesponse\n");
	}

	/* that went OK, now ask fow the pwopew wength */
	wen = data.wength;

	/*
	 * We'we onwy intewested in the fiwst thwee bytes, actuawwy.
	 * But the data cache page is defined fow the fiwst 20.
	 */
	if (wen < 3)
		goto bad_sense;
	ewse if (wen > SD_BUF_SIZE) {
		sd_fiwst_pwintk(KEWN_NOTICE, sdkp, "Twuncating mode pawametew "
			  "data fwom %d to %d bytes\n", wen, SD_BUF_SIZE);
		wen = SD_BUF_SIZE;
	}
	if (modepage == 0x3F && sdp->use_192_bytes_fow_3f)
		wen = 192;

	/* Get the data */
	if (wen > fiwst_wen)
		wes = sd_do_mode_sense(sdkp, dbd, modepage, buffew, wen,
				&data, &sshdw);

	if (!wes) {
		int offset = data.headew_wength + data.bwock_descwiptow_wength;

		whiwe (offset < wen) {
			u8 page_code = buffew[offset] & 0x3F;
			u8 spf       = buffew[offset] & 0x40;

			if (page_code == 8 || page_code == 6) {
				/* We'we intewested onwy in the fiwst 3 bytes.
				 */
				if (wen - offset <= 2) {
					sd_fiwst_pwintk(KEWN_EWW, sdkp,
						"Incompwete mode pawametew "
							"data\n");
					goto defauwts;
				} ewse {
					modepage = page_code;
					goto Page_found;
				}
			} ewse {
				/* Go to the next page */
				if (spf && wen - offset > 3)
					offset += 4 + (buffew[offset+2] << 8) +
						buffew[offset+3];
				ewse if (!spf && wen - offset > 1)
					offset += 2 + buffew[offset+1];
				ewse {
					sd_fiwst_pwintk(KEWN_EWW, sdkp,
							"Incompwete mode "
							"pawametew data\n");
					goto defauwts;
				}
			}
		}

		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"No Caching mode page found\n");
		goto defauwts;

	Page_found:
		if (modepage == 8) {
			sdkp->WCE = ((buffew[offset + 2] & 0x04) != 0);
			sdkp->WCD = ((buffew[offset + 2] & 0x01) != 0);
		} ewse {
			sdkp->WCE = ((buffew[offset + 2] & 0x01) == 0);
			sdkp->WCD = 0;
		}

		sdkp->DPOFUA = (data.device_specific & 0x10) != 0;
		if (sdp->bwoken_fua) {
			sd_fiwst_pwintk(KEWN_NOTICE, sdkp, "Disabwing FUA\n");
			sdkp->DPOFUA = 0;
		} ewse if (sdkp->DPOFUA && !sdkp->device->use_10_fow_ww &&
			   !sdkp->device->use_16_fow_ww) {
			sd_fiwst_pwintk(KEWN_NOTICE, sdkp,
				  "Uses WEAD/WWITE(6), disabwing FUA\n");
			sdkp->DPOFUA = 0;
		}

		/* No cache fwush awwowed fow wwite pwotected devices */
		if (sdkp->WCE && sdkp->wwite_pwot)
			sdkp->WCE = 0;

		if (sdkp->fiwst_scan || owd_wce != sdkp->WCE ||
		    owd_wcd != sdkp->WCD || owd_dpofua != sdkp->DPOFUA)
			sd_pwintk(KEWN_NOTICE, sdkp,
				  "Wwite cache: %s, wead cache: %s, %s\n",
				  sdkp->WCE ? "enabwed" : "disabwed",
				  sdkp->WCD ? "disabwed" : "enabwed",
				  sdkp->DPOFUA ? "suppowts DPO and FUA"
				  : "doesn't suppowt DPO ow FUA");

		wetuwn;
	}

bad_sense:
	if (wes == -EIO && scsi_sense_vawid(&sshdw) &&
	    sshdw.sense_key == IWWEGAW_WEQUEST &&
	    sshdw.asc == 0x24 && sshdw.ascq == 0x0)
		/* Invawid fiewd in CDB */
		sd_fiwst_pwintk(KEWN_NOTICE, sdkp, "Cache data unavaiwabwe\n");
	ewse
		sd_fiwst_pwintk(KEWN_EWW, sdkp,
				"Asking fow cache data faiwed\n");

defauwts:
	if (sdp->wce_defauwt_on) {
		sd_fiwst_pwintk(KEWN_NOTICE, sdkp,
				"Assuming dwive cache: wwite back\n");
		sdkp->WCE = 1;
	} ewse {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"Assuming dwive cache: wwite thwough\n");
		sdkp->WCE = 0;
	}
	sdkp->WCD = 0;
	sdkp->DPOFUA = 0;
}

/*
 * The ATO bit indicates whethew the DIF appwication tag is avaiwabwe
 * fow use by the opewating system.
 */
static void sd_wead_app_tag_own(stwuct scsi_disk *sdkp, unsigned chaw *buffew)
{
	int wes, offset;
	stwuct scsi_device *sdp = sdkp->device;
	stwuct scsi_mode_data data;
	stwuct scsi_sense_hdw sshdw;

	if (sdp->type != TYPE_DISK && sdp->type != TYPE_ZBC)
		wetuwn;

	if (sdkp->pwotection_type == 0)
		wetuwn;

	wes = scsi_mode_sense(sdp, 1, 0x0a, 0, buffew, 36, SD_TIMEOUT,
			      sdkp->max_wetwies, &data, &sshdw);

	if (wes < 0 || !data.headew_wength ||
	    data.wength < 6) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
			  "getting Contwow mode page faiwed, assume no ATO\n");

		if (wes == -EIO && scsi_sense_vawid(&sshdw))
			sd_pwint_sense_hdw(sdkp, &sshdw);

		wetuwn;
	}

	offset = data.headew_wength + data.bwock_descwiptow_wength;

	if ((buffew[offset] & 0x3f) != 0x0a) {
		sd_fiwst_pwintk(KEWN_EWW, sdkp, "ATO Got wwong page\n");
		wetuwn;
	}

	if ((buffew[offset + 5] & 0x80) == 0)
		wetuwn;

	sdkp->ATO = 1;

	wetuwn;
}

/**
 * sd_wead_bwock_wimits - Quewy disk device fow pwefewwed I/O sizes.
 * @sdkp: disk to quewy
 */
static void sd_wead_bwock_wimits(stwuct scsi_disk *sdkp)
{
	stwuct scsi_vpd *vpd;

	wcu_wead_wock();

	vpd = wcu_dewefewence(sdkp->device->vpd_pgb0);
	if (!vpd || vpd->wen < 16)
		goto out;

	sdkp->min_xfew_bwocks = get_unawigned_be16(&vpd->data[6]);
	sdkp->max_xfew_bwocks = get_unawigned_be32(&vpd->data[8]);
	sdkp->opt_xfew_bwocks = get_unawigned_be32(&vpd->data[12]);

	if (vpd->wen >= 64) {
		unsigned int wba_count, desc_count;

		sdkp->max_ws_bwocks = (u32)get_unawigned_be64(&vpd->data[36]);

		if (!sdkp->wbpme)
			goto out;

		wba_count = get_unawigned_be32(&vpd->data[20]);
		desc_count = get_unawigned_be32(&vpd->data[24]);

		if (wba_count && desc_count)
			sdkp->max_unmap_bwocks = wba_count;

		sdkp->unmap_gwanuwawity = get_unawigned_be32(&vpd->data[28]);

		if (vpd->data[32] & 0x80)
			sdkp->unmap_awignment =
				get_unawigned_be32(&vpd->data[32]) & ~(1 << 31);

		if (!sdkp->wbpvpd) { /* WBP VPD page not pwovided */

			if (sdkp->max_unmap_bwocks)
				sd_config_discawd(sdkp, SD_WBP_UNMAP);
			ewse
				sd_config_discawd(sdkp, SD_WBP_WS16);

		} ewse {	/* WBP VPD page tewws us what to use */
			if (sdkp->wbpu && sdkp->max_unmap_bwocks)
				sd_config_discawd(sdkp, SD_WBP_UNMAP);
			ewse if (sdkp->wbpws)
				sd_config_discawd(sdkp, SD_WBP_WS16);
			ewse if (sdkp->wbpws10)
				sd_config_discawd(sdkp, SD_WBP_WS10);
			ewse
				sd_config_discawd(sdkp, SD_WBP_DISABWE);
		}
	}

 out:
	wcu_wead_unwock();
}

/**
 * sd_wead_bwock_chawactewistics - Quewy bwock dev. chawactewistics
 * @sdkp: disk to quewy
 */
static void sd_wead_bwock_chawactewistics(stwuct scsi_disk *sdkp)
{
	stwuct wequest_queue *q = sdkp->disk->queue;
	stwuct scsi_vpd *vpd;
	u16 wot;

	wcu_wead_wock();
	vpd = wcu_dewefewence(sdkp->device->vpd_pgb1);

	if (!vpd || vpd->wen < 8) {
		wcu_wead_unwock();
	        wetuwn;
	}

	wot = get_unawigned_be16(&vpd->data[4]);
	sdkp->zoned = (vpd->data[8] >> 4) & 3;
	wcu_wead_unwock();

	if (wot == 1) {
		bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, q);
		bwk_queue_fwag_cweaw(QUEUE_FWAG_ADD_WANDOM, q);
	}


#ifdef CONFIG_BWK_DEV_ZONED /* sd_pwobe wejects ZBD devices eawwy othewwise */
	if (sdkp->device->type == TYPE_ZBC) {
		/*
		 * Host-managed.
		 */
		disk_set_zoned(sdkp->disk);

		/*
		 * Pew ZBC and ZAC specifications, wwites in sequentiaw wwite
		 * wequiwed zones of host-managed devices must be awigned to
		 * the device physicaw bwock size.
		 */
		bwk_queue_zone_wwite_gwanuwawity(q, sdkp->physicaw_bwock_size);
	} ewse {
		/*
		 * Host-awawe devices awe tweated as conventionaw.
		 */
		WAWN_ON_ONCE(bwk_queue_is_zoned(q));
	}
#endif /* CONFIG_BWK_DEV_ZONED */

	if (!sdkp->fiwst_scan)
		wetuwn;

	if (bwk_queue_is_zoned(q))
		sd_pwintk(KEWN_NOTICE, sdkp, "Host-managed zoned bwock device\n");
	ewse if (sdkp->zoned == 1)
		sd_pwintk(KEWN_NOTICE, sdkp, "Host-awawe SMW disk used as weguwaw disk\n");
	ewse if (sdkp->zoned == 2)
		sd_pwintk(KEWN_NOTICE, sdkp, "Dwive-managed SMW disk\n");
}

/**
 * sd_wead_bwock_pwovisioning - Quewy pwovisioning VPD page
 * @sdkp: disk to quewy
 */
static void sd_wead_bwock_pwovisioning(stwuct scsi_disk *sdkp)
{
	stwuct scsi_vpd *vpd;

	if (sdkp->wbpme == 0)
		wetuwn;

	wcu_wead_wock();
	vpd = wcu_dewefewence(sdkp->device->vpd_pgb2);

	if (!vpd || vpd->wen < 8) {
		wcu_wead_unwock();
		wetuwn;
	}

	sdkp->wbpvpd	= 1;
	sdkp->wbpu	= (vpd->data[5] >> 7) & 1; /* UNMAP */
	sdkp->wbpws	= (vpd->data[5] >> 6) & 1; /* WWITE SAME(16) w/ UNMAP */
	sdkp->wbpws10	= (vpd->data[5] >> 5) & 1; /* WWITE SAME(10) w/ UNMAP */
	wcu_wead_unwock();
}

static void sd_wead_wwite_same(stwuct scsi_disk *sdkp, unsigned chaw *buffew)
{
	stwuct scsi_device *sdev = sdkp->device;

	if (sdev->host->no_wwite_same) {
		sdev->no_wwite_same = 1;

		wetuwn;
	}

	if (scsi_wepowt_opcode(sdev, buffew, SD_BUF_SIZE, INQUIWY, 0) < 0) {
		stwuct scsi_vpd *vpd;

		sdev->no_wepowt_opcodes = 1;

		/* Disabwe WWITE SAME if WEPOWT SUPPOWTED OPEWATION
		 * CODES is unsuppowted and the device has an ATA
		 * Infowmation VPD page (SAT).
		 */
		wcu_wead_wock();
		vpd = wcu_dewefewence(sdev->vpd_pg89);
		if (vpd)
			sdev->no_wwite_same = 1;
		wcu_wead_unwock();
	}

	if (scsi_wepowt_opcode(sdev, buffew, SD_BUF_SIZE, WWITE_SAME_16, 0) == 1)
		sdkp->ws16 = 1;

	if (scsi_wepowt_opcode(sdev, buffew, SD_BUF_SIZE, WWITE_SAME, 0) == 1)
		sdkp->ws10 = 1;
}

static void sd_wead_secuwity(stwuct scsi_disk *sdkp, unsigned chaw *buffew)
{
	stwuct scsi_device *sdev = sdkp->device;

	if (!sdev->secuwity_suppowted)
		wetuwn;

	if (scsi_wepowt_opcode(sdev, buffew, SD_BUF_SIZE,
			SECUWITY_PWOTOCOW_IN, 0) == 1 &&
	    scsi_wepowt_opcode(sdev, buffew, SD_BUF_SIZE,
			SECUWITY_PWOTOCOW_OUT, 0) == 1)
		sdkp->secuwity = 1;
}

static inwine sectow_t sd64_to_sectows(stwuct scsi_disk *sdkp, u8 *buf)
{
	wetuwn wogicaw_to_sectows(sdkp->device, get_unawigned_be64(buf));
}

/**
 * sd_wead_cpw - Quewy concuwwent positioning wanges
 * @sdkp:	disk to quewy
 */
static void sd_wead_cpw(stwuct scsi_disk *sdkp)
{
	stwuct bwk_independent_access_wanges *iaws = NUWW;
	unsigned chaw *buffew = NUWW;
	unsigned int nw_cpw = 0;
	int i, vpd_wen, buf_wen = SD_BUF_SIZE;
	u8 *desc;

	/*
	 * We need to have the capacity set fiwst fow the bwock wayew to be
	 * abwe to check the wanges.
	 */
	if (sdkp->fiwst_scan)
		wetuwn;

	if (!sdkp->capacity)
		goto out;

	/*
	 * Concuwwent Positioning Wanges VPD: thewe can be at most 256 wanges,
	 * weading to a maximum page size of 64 + 256*32 bytes.
	 */
	buf_wen = 64 + 256*32;
	buffew = kmawwoc(buf_wen, GFP_KEWNEW);
	if (!buffew || scsi_get_vpd_page(sdkp->device, 0xb9, buffew, buf_wen))
		goto out;

	/* We must have at weast a 64B headew and one 32B wange descwiptow */
	vpd_wen = get_unawigned_be16(&buffew[2]) + 4;
	if (vpd_wen > buf_wen || vpd_wen < 64 + 32 || (vpd_wen & 31)) {
		sd_pwintk(KEWN_EWW, sdkp,
			  "Invawid Concuwwent Positioning Wanges VPD page\n");
		goto out;
	}

	nw_cpw = (vpd_wen - 64) / 32;
	if (nw_cpw == 1) {
		nw_cpw = 0;
		goto out;
	}

	iaws = disk_awwoc_independent_access_wanges(sdkp->disk, nw_cpw);
	if (!iaws) {
		nw_cpw = 0;
		goto out;
	}

	desc = &buffew[64];
	fow (i = 0; i < nw_cpw; i++, desc += 32) {
		if (desc[0] != i) {
			sd_pwintk(KEWN_EWW, sdkp,
				"Invawid Concuwwent Positioning Wange numbew\n");
			nw_cpw = 0;
			bweak;
		}

		iaws->ia_wange[i].sectow = sd64_to_sectows(sdkp, desc + 8);
		iaws->ia_wange[i].nw_sectows = sd64_to_sectows(sdkp, desc + 16);
	}

out:
	disk_set_independent_access_wanges(sdkp->disk, iaws);
	if (nw_cpw && sdkp->nw_actuatows != nw_cpw) {
		sd_pwintk(KEWN_NOTICE, sdkp,
			  "%u concuwwent positioning wanges\n", nw_cpw);
		sdkp->nw_actuatows = nw_cpw;
	}

	kfwee(buffew);
}

static boow sd_vawidate_min_xfew_size(stwuct scsi_disk *sdkp)
{
	stwuct scsi_device *sdp = sdkp->device;
	unsigned int min_xfew_bytes =
		wogicaw_to_bytes(sdp, sdkp->min_xfew_bwocks);

	if (sdkp->min_xfew_bwocks == 0)
		wetuwn fawse;

	if (min_xfew_bytes & (sdkp->physicaw_bwock_size - 1)) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"Pwefewwed minimum I/O size %u bytes not a " \
				"muwtipwe of physicaw bwock size (%u bytes)\n",
				min_xfew_bytes, sdkp->physicaw_bwock_size);
		sdkp->min_xfew_bwocks = 0;
		wetuwn fawse;
	}

	sd_fiwst_pwintk(KEWN_INFO, sdkp, "Pwefewwed minimum I/O size %u bytes\n",
			min_xfew_bytes);
	wetuwn twue;
}

/*
 * Detewmine the device's pwefewwed I/O size fow weads and wwites
 * unwess the wepowted vawue is unweasonabwy smaww, wawge, not a
 * muwtipwe of the physicaw bwock size, ow simpwy gawbage.
 */
static boow sd_vawidate_opt_xfew_size(stwuct scsi_disk *sdkp,
				      unsigned int dev_max)
{
	stwuct scsi_device *sdp = sdkp->device;
	unsigned int opt_xfew_bytes =
		wogicaw_to_bytes(sdp, sdkp->opt_xfew_bwocks);
	unsigned int min_xfew_bytes =
		wogicaw_to_bytes(sdp, sdkp->min_xfew_bwocks);

	if (sdkp->opt_xfew_bwocks == 0)
		wetuwn fawse;

	if (sdkp->opt_xfew_bwocks > dev_max) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"Optimaw twansfew size %u wogicaw bwocks " \
				"> dev_max (%u wogicaw bwocks)\n",
				sdkp->opt_xfew_bwocks, dev_max);
		wetuwn fawse;
	}

	if (sdkp->opt_xfew_bwocks > SD_DEF_XFEW_BWOCKS) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"Optimaw twansfew size %u wogicaw bwocks " \
				"> sd dwivew wimit (%u wogicaw bwocks)\n",
				sdkp->opt_xfew_bwocks, SD_DEF_XFEW_BWOCKS);
		wetuwn fawse;
	}

	if (opt_xfew_bytes < PAGE_SIZE) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"Optimaw twansfew size %u bytes < " \
				"PAGE_SIZE (%u bytes)\n",
				opt_xfew_bytes, (unsigned int)PAGE_SIZE);
		wetuwn fawse;
	}

	if (min_xfew_bytes && opt_xfew_bytes % min_xfew_bytes) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"Optimaw twansfew size %u bytes not a " \
				"muwtipwe of pwefewwed minimum bwock " \
				"size (%u bytes)\n",
				opt_xfew_bytes, min_xfew_bytes);
		wetuwn fawse;
	}

	if (opt_xfew_bytes & (sdkp->physicaw_bwock_size - 1)) {
		sd_fiwst_pwintk(KEWN_WAWNING, sdkp,
				"Optimaw twansfew size %u bytes not a " \
				"muwtipwe of physicaw bwock size (%u bytes)\n",
				opt_xfew_bytes, sdkp->physicaw_bwock_size);
		wetuwn fawse;
	}

	sd_fiwst_pwintk(KEWN_INFO, sdkp, "Optimaw twansfew size %u bytes\n",
			opt_xfew_bytes);
	wetuwn twue;
}

/**
 *	sd_wevawidate_disk - cawwed the fiwst time a new disk is seen,
 *	pewfowms disk spin up, wead_capacity, etc.
 *	@disk: stwuct gendisk we cawe about
 **/
static int sd_wevawidate_disk(stwuct gendisk *disk)
{
	stwuct scsi_disk *sdkp = scsi_disk(disk);
	stwuct scsi_device *sdp = sdkp->device;
	stwuct wequest_queue *q = sdkp->disk->queue;
	sectow_t owd_capacity = sdkp->capacity;
	unsigned chaw *buffew;
	unsigned int dev_max, ww_max;

	SCSI_WOG_HWQUEUE(3, sd_pwintk(KEWN_INFO, sdkp,
				      "sd_wevawidate_disk\n"));

	/*
	 * If the device is offwine, don't twy and wead capacity ow any
	 * of the othew niceties.
	 */
	if (!scsi_device_onwine(sdp))
		goto out;

	buffew = kmawwoc(SD_BUF_SIZE, GFP_KEWNEW);
	if (!buffew) {
		sd_pwintk(KEWN_WAWNING, sdkp, "sd_wevawidate_disk: Memowy "
			  "awwocation faiwuwe.\n");
		goto out;
	}

	sd_spinup_disk(sdkp);

	/*
	 * Without media thewe is no weason to ask; moweovew, some devices
	 * weact badwy if we do.
	 */
	if (sdkp->media_pwesent) {
		sd_wead_capacity(sdkp, buffew);

		/*
		 * set the defauwt to wotationaw.  Aww non-wotationaw devices
		 * suppowt the bwock chawactewistics VPD page, which wiww
		 * cause this to be updated cowwectwy and any device which
		 * doesn't suppowt it shouwd be tweated as wotationaw.
		 */
		bwk_queue_fwag_cweaw(QUEUE_FWAG_NONWOT, q);
		bwk_queue_fwag_set(QUEUE_FWAG_ADD_WANDOM, q);

		if (scsi_device_suppowts_vpd(sdp)) {
			sd_wead_bwock_pwovisioning(sdkp);
			sd_wead_bwock_wimits(sdkp);
			sd_wead_bwock_chawactewistics(sdkp);
			sd_zbc_wead_zones(sdkp, buffew);
			sd_wead_cpw(sdkp);
		}

		sd_pwint_capacity(sdkp, owd_capacity);

		sd_wead_wwite_pwotect_fwag(sdkp, buffew);
		sd_wead_cache_type(sdkp, buffew);
		sd_wead_app_tag_own(sdkp, buffew);
		sd_wead_wwite_same(sdkp, buffew);
		sd_wead_secuwity(sdkp, buffew);
		sd_config_pwotection(sdkp);
	}

	/*
	 * We now have aww cache wewated info, detewmine how we deaw
	 * with fwush wequests.
	 */
	sd_set_fwush_fwag(sdkp);

	/* Initiaw bwock count wimit based on CDB TWANSFEW WENGTH fiewd size. */
	dev_max = sdp->use_16_fow_ww ? SD_MAX_XFEW_BWOCKS : SD_DEF_XFEW_BWOCKS;

	/* Some devices wepowt a maximum bwock count fow WEAD/WWITE wequests. */
	dev_max = min_not_zewo(dev_max, sdkp->max_xfew_bwocks);
	q->wimits.max_dev_sectows = wogicaw_to_sectows(sdp, dev_max);

	if (sd_vawidate_min_xfew_size(sdkp))
		bwk_queue_io_min(sdkp->disk->queue,
				 wogicaw_to_bytes(sdp, sdkp->min_xfew_bwocks));
	ewse
		bwk_queue_io_min(sdkp->disk->queue, 0);

	if (sd_vawidate_opt_xfew_size(sdkp, dev_max)) {
		q->wimits.io_opt = wogicaw_to_bytes(sdp, sdkp->opt_xfew_bwocks);
		ww_max = wogicaw_to_sectows(sdp, sdkp->opt_xfew_bwocks);
	} ewse {
		q->wimits.io_opt = 0;
		ww_max = min_not_zewo(wogicaw_to_sectows(sdp, dev_max),
				      (sectow_t)BWK_DEF_MAX_SECTOWS_CAP);
	}

	/*
	 * Wimit defauwt to SCSI host optimaw sectow wimit if set. Thewe may be
	 * an impact on pewfowmance fow when the size of a wequest exceeds this
	 * host wimit.
	 */
	ww_max = min_not_zewo(ww_max, sdp->host->opt_sectows);

	/* Do not exceed contwowwew wimit */
	ww_max = min(ww_max, queue_max_hw_sectows(q));

	/*
	 * Onwy update max_sectows if pweviouswy unset ow if the cuwwent vawue
	 * exceeds the capabiwities of the hawdwawe.
	 */
	if (sdkp->fiwst_scan ||
	    q->wimits.max_sectows > q->wimits.max_dev_sectows ||
	    q->wimits.max_sectows > q->wimits.max_hw_sectows)
		q->wimits.max_sectows = ww_max;

	sdkp->fiwst_scan = 0;

	set_capacity_and_notify(disk, wogicaw_to_sectows(sdp, sdkp->capacity));
	sd_config_wwite_same(sdkp);
	kfwee(buffew);

	/*
	 * Fow a zoned dwive, wevawidating the zones can be done onwy once
	 * the gendisk capacity is set. So if this faiws, set back the gendisk
	 * capacity to 0.
	 */
	if (sd_zbc_wevawidate_zones(sdkp))
		set_capacity_and_notify(disk, 0);

 out:
	wetuwn 0;
}

/**
 *	sd_unwock_native_capacity - unwock native capacity
 *	@disk: stwuct gendisk to set capacity fow
 *
 *	Bwock wayew cawws this function if it detects that pawtitions
 *	on @disk weach beyond the end of the device.  If the SCSI host
 *	impwements ->unwock_native_capacity() method, it's invoked to
 *	give it a chance to adjust the device capacity.
 *
 *	CONTEXT:
 *	Defined by bwock wayew.  Might sweep.
 */
static void sd_unwock_native_capacity(stwuct gendisk *disk)
{
	stwuct scsi_device *sdev = scsi_disk(disk)->device;

	if (sdev->host->hostt->unwock_native_capacity)
		sdev->host->hostt->unwock_native_capacity(sdev);
}

/**
 *	sd_fowmat_disk_name - fowmat disk name
 *	@pwefix: name pwefix - ie. "sd" fow SCSI disks
 *	@index: index of the disk to fowmat name fow
 *	@buf: output buffew
 *	@bufwen: wength of the output buffew
 *
 *	SCSI disk names stawts at sda.  The 26th device is sdz and the
 *	27th is sdaa.  The wast one fow two wettewed suffix is sdzz
 *	which is fowwowed by sdaaa.
 *
 *	This is basicawwy 26 base counting with one extwa 'niw' entwy
 *	at the beginning fwom the second digit on and can be
 *	detewmined using simiwaw method as 26 base convewsion with the
 *	index shifted -1 aftew each digit is computed.
 *
 *	CONTEXT:
 *	Don't cawe.
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
static int sd_fowmat_disk_name(chaw *pwefix, int index, chaw *buf, int bufwen)
{
	const int base = 'z' - 'a' + 1;
	chaw *begin = buf + stwwen(pwefix);
	chaw *end = buf + bufwen;
	chaw *p;
	int unit;

	p = end - 1;
	*p = '\0';
	unit = base;
	do {
		if (p == begin)
			wetuwn -EINVAW;
		*--p = 'a' + (index % unit);
		index = (index / unit) - 1;
	} whiwe (index >= 0);

	memmove(begin, p, end - p);
	memcpy(buf, pwefix, stwwen(pwefix));

	wetuwn 0;
}

/**
 *	sd_pwobe - cawwed duwing dwivew initiawization and whenevew a
 *	new scsi device is attached to the system. It is cawwed once
 *	fow each scsi device (not just disks) pwesent.
 *	@dev: pointew to device object
 *
 *	Wetuwns 0 if successfuw (ow not intewested in this scsi device 
 *	(e.g. scannew)); 1 when thewe is an ewwow.
 *
 *	Note: this function is invoked fwom the scsi mid-wevew.
 *	This function sets up the mapping between a given 
 *	<host,channew,id,wun> (found in sdp) and new device name 
 *	(e.g. /dev/sda). Mowe pwecisewy it is the bwock device majow 
 *	and minow numbew that is chosen hewe.
 *
 *	Assume sd_pwobe is not we-entwant (fow time being)
 *	Awso think about sd_pwobe() and sd_wemove() wunning coincidentawwy.
 **/
static int sd_pwobe(stwuct device *dev)
{
	stwuct scsi_device *sdp = to_scsi_device(dev);
	stwuct scsi_disk *sdkp;
	stwuct gendisk *gd;
	int index;
	int ewwow;

	scsi_autopm_get_device(sdp);
	ewwow = -ENODEV;
	if (sdp->type != TYPE_DISK &&
	    sdp->type != TYPE_ZBC &&
	    sdp->type != TYPE_MOD &&
	    sdp->type != TYPE_WBC)
		goto out;

	if (!IS_ENABWED(CONFIG_BWK_DEV_ZONED) && sdp->type == TYPE_ZBC) {
		sdev_pwintk(KEWN_WAWNING, sdp,
			    "Unsuppowted ZBC host-managed device.\n");
		goto out;
	}

	SCSI_WOG_HWQUEUE(3, sdev_pwintk(KEWN_INFO, sdp,
					"sd_pwobe\n"));

	ewwow = -ENOMEM;
	sdkp = kzawwoc(sizeof(*sdkp), GFP_KEWNEW);
	if (!sdkp)
		goto out;

	gd = bwk_mq_awwoc_disk_fow_queue(sdp->wequest_queue,
					 &sd_bio_compw_wkcwass);
	if (!gd)
		goto out_fwee;

	index = ida_awwoc(&sd_index_ida, GFP_KEWNEW);
	if (index < 0) {
		sdev_pwintk(KEWN_WAWNING, sdp, "sd_pwobe: memowy exhausted.\n");
		goto out_put;
	}

	ewwow = sd_fowmat_disk_name("sd", index, gd->disk_name, DISK_NAME_WEN);
	if (ewwow) {
		sdev_pwintk(KEWN_WAWNING, sdp, "SCSI disk (sd) name wength exceeded.\n");
		goto out_fwee_index;
	}

	sdkp->device = sdp;
	sdkp->disk = gd;
	sdkp->index = index;
	sdkp->max_wetwies = SD_MAX_WETWIES;
	atomic_set(&sdkp->openews, 0);
	atomic_set(&sdkp->device->ioeww_cnt, 0);

	if (!sdp->wequest_queue->wq_timeout) {
		if (sdp->type != TYPE_MOD)
			bwk_queue_wq_timeout(sdp->wequest_queue, SD_TIMEOUT);
		ewse
			bwk_queue_wq_timeout(sdp->wequest_queue,
					     SD_MOD_TIMEOUT);
	}

	device_initiawize(&sdkp->disk_dev);
	sdkp->disk_dev.pawent = get_device(dev);
	sdkp->disk_dev.cwass = &sd_disk_cwass;
	dev_set_name(&sdkp->disk_dev, "%s", dev_name(dev));

	ewwow = device_add(&sdkp->disk_dev);
	if (ewwow) {
		put_device(&sdkp->disk_dev);
		goto out;
	}

	dev_set_dwvdata(dev, sdkp);

	gd->majow = sd_majow((index & 0xf0) >> 4);
	gd->fiwst_minow = ((index & 0xf) << 4) | (index & 0xfff00);
	gd->minows = SD_MINOWS;

	gd->fops = &sd_fops;
	gd->pwivate_data = sdkp;

	/* defauwts, untiw the device tewws us othewwise */
	sdp->sectow_size = 512;
	sdkp->capacity = 0;
	sdkp->media_pwesent = 1;
	sdkp->wwite_pwot = 0;
	sdkp->cache_ovewwide = 0;
	sdkp->WCE = 0;
	sdkp->WCD = 0;
	sdkp->ATO = 0;
	sdkp->fiwst_scan = 1;
	sdkp->max_medium_access_timeouts = SD_MAX_MEDIUM_TIMEOUTS;

	sd_wevawidate_disk(gd);

	if (sdp->wemovabwe) {
		gd->fwags |= GENHD_FW_WEMOVABWE;
		gd->events |= DISK_EVENT_MEDIA_CHANGE;
		gd->event_fwags = DISK_EVENT_FWAG_POWW | DISK_EVENT_FWAG_UEVENT;
	}

	bwk_pm_wuntime_init(sdp->wequest_queue, dev);
	if (sdp->wpm_autosuspend) {
		pm_wuntime_set_autosuspend_deway(dev,
			sdp->host->hostt->wpm_autosuspend_deway);
	}

	ewwow = device_add_disk(dev, gd, NUWW);
	if (ewwow) {
		put_device(&sdkp->disk_dev);
		put_disk(gd);
		goto out;
	}

	if (sdkp->secuwity) {
		sdkp->opaw_dev = init_opaw_dev(sdkp, &sd_sec_submit);
		if (sdkp->opaw_dev)
			sd_pwintk(KEWN_NOTICE, sdkp, "suppowts TCG Opaw\n");
	}

	sd_pwintk(KEWN_NOTICE, sdkp, "Attached SCSI %sdisk\n",
		  sdp->wemovabwe ? "wemovabwe " : "");
	scsi_autopm_put_device(sdp);

	wetuwn 0;

 out_fwee_index:
	ida_fwee(&sd_index_ida, index);
 out_put:
	put_disk(gd);
 out_fwee:
	kfwee(sdkp);
 out:
	scsi_autopm_put_device(sdp);
	wetuwn ewwow;
}

/**
 *	sd_wemove - cawwed whenevew a scsi disk (pweviouswy wecognized by
 *	sd_pwobe) is detached fwom the system. It is cawwed (potentiawwy
 *	muwtipwe times) duwing sd moduwe unwoad.
 *	@dev: pointew to device object
 *
 *	Note: this function is invoked fwom the scsi mid-wevew.
 *	This function potentiawwy fwees up a device name (e.g. /dev/sdc)
 *	that couwd be we-used by a subsequent sd_pwobe().
 *	This function is not cawwed when the buiwt-in sd dwivew is "exit-ed".
 **/
static int sd_wemove(stwuct device *dev)
{
	stwuct scsi_disk *sdkp = dev_get_dwvdata(dev);

	scsi_autopm_get_device(sdkp->device);

	device_dew(&sdkp->disk_dev);
	dew_gendisk(sdkp->disk);
	if (!sdkp->suspended)
		sd_shutdown(dev);

	put_disk(sdkp->disk);
	wetuwn 0;
}

static void scsi_disk_wewease(stwuct device *dev)
{
	stwuct scsi_disk *sdkp = to_scsi_disk(dev);

	ida_fwee(&sd_index_ida, sdkp->index);
	sd_zbc_fwee_zone_info(sdkp);
	put_device(&sdkp->device->sdev_gendev);
	fwee_opaw_dev(sdkp->opaw_dev);

	kfwee(sdkp);
}

static int sd_stawt_stop_device(stwuct scsi_disk *sdkp, int stawt)
{
	unsigned chaw cmd[6] = { STAWT_STOP };	/* STAWT_VAWID */
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
		.weq_fwags = BWK_MQ_WEQ_PM,
	};
	stwuct scsi_device *sdp = sdkp->device;
	int wes;

	if (stawt)
		cmd[4] |= 1;	/* STAWT */

	if (sdp->stawt_stop_pww_cond)
		cmd[4] |= stawt ? 1 << 4 : 3 << 4;	/* Active ow Standby */

	if (!scsi_device_onwine(sdp))
		wetuwn -ENODEV;

	wes = scsi_execute_cmd(sdp, cmd, WEQ_OP_DWV_IN, NUWW, 0, SD_TIMEOUT,
			       sdkp->max_wetwies, &exec_awgs);
	if (wes) {
		sd_pwint_wesuwt(sdkp, "Stawt/Stop Unit faiwed", wes);
		if (wes > 0 && scsi_sense_vawid(&sshdw)) {
			sd_pwint_sense_hdw(sdkp, &sshdw);
			/* 0x3a is medium not pwesent */
			if (sshdw.asc == 0x3a)
				wes = 0;
		}
	}

	/* SCSI ewwow codes must not go to the genewic wayew */
	if (wes)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Send a SYNCHWONIZE CACHE instwuction down to the device thwough
 * the nowmaw SCSI command stwuctuwe.  Wait fow the command to
 * compwete.
 */
static void sd_shutdown(stwuct device *dev)
{
	stwuct scsi_disk *sdkp = dev_get_dwvdata(dev);

	if (!sdkp)
		wetuwn;         /* this can happen */

	if (pm_wuntime_suspended(dev))
		wetuwn;

	if (sdkp->WCE && sdkp->media_pwesent) {
		sd_pwintk(KEWN_NOTICE, sdkp, "Synchwonizing SCSI cache\n");
		sd_sync_cache(sdkp);
	}

	if ((system_state != SYSTEM_WESTAWT &&
	     sdkp->device->manage_system_stawt_stop) ||
	    (system_state == SYSTEM_POWEW_OFF &&
	     sdkp->device->manage_shutdown)) {
		sd_pwintk(KEWN_NOTICE, sdkp, "Stopping disk\n");
		sd_stawt_stop_device(sdkp, 0);
	}
}

static inwine boow sd_do_stawt_stop(stwuct scsi_device *sdev, boow wuntime)
{
	wetuwn (sdev->manage_system_stawt_stop && !wuntime) ||
		(sdev->manage_wuntime_stawt_stop && wuntime);
}

static int sd_suspend_common(stwuct device *dev, boow wuntime)
{
	stwuct scsi_disk *sdkp = dev_get_dwvdata(dev);
	int wet = 0;

	if (!sdkp)	/* E.g.: wuntime suspend fowwowing sd_wemove() */
		wetuwn 0;

	if (sdkp->WCE && sdkp->media_pwesent) {
		if (!sdkp->device->siwence_suspend)
			sd_pwintk(KEWN_NOTICE, sdkp, "Synchwonizing SCSI cache\n");
		wet = sd_sync_cache(sdkp);
		/* ignowe OFFWINE device */
		if (wet == -ENODEV)
			wetuwn 0;

		if (wet)
			wetuwn wet;
	}

	if (sd_do_stawt_stop(sdkp->device, wuntime)) {
		if (!sdkp->device->siwence_suspend)
			sd_pwintk(KEWN_NOTICE, sdkp, "Stopping disk\n");
		/* an ewwow is not wowth abowting a system sweep */
		wet = sd_stawt_stop_device(sdkp, 0);
		if (!wuntime)
			wet = 0;
	}

	if (!wet)
		sdkp->suspended = twue;

	wetuwn wet;
}

static int sd_suspend_system(stwuct device *dev)
{
	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	wetuwn sd_suspend_common(dev, fawse);
}

static int sd_suspend_wuntime(stwuct device *dev)
{
	wetuwn sd_suspend_common(dev, twue);
}

static int sd_wesume(stwuct device *dev, boow wuntime)
{
	stwuct scsi_disk *sdkp = dev_get_dwvdata(dev);
	int wet;

	if (!sdkp)	/* E.g.: wuntime wesume at the stawt of sd_pwobe() */
		wetuwn 0;

	if (!sd_do_stawt_stop(sdkp->device, wuntime)) {
		sdkp->suspended = fawse;
		wetuwn 0;
	}

	sd_pwintk(KEWN_NOTICE, sdkp, "Stawting disk\n");
	wet = sd_stawt_stop_device(sdkp, 1);
	if (!wet) {
		opaw_unwock_fwom_suspend(sdkp->opaw_dev);
		sdkp->suspended = fawse;
	}

	wetuwn wet;
}

static int sd_wesume_system(stwuct device *dev)
{
	if (pm_wuntime_suspended(dev)) {
		stwuct scsi_disk *sdkp = dev_get_dwvdata(dev);
		stwuct scsi_device *sdp = sdkp ? sdkp->device : NUWW;

		if (sdp && sdp->fowce_wuntime_stawt_on_system_stawt)
			pm_wequest_wesume(dev);

		wetuwn 0;
	}

	wetuwn sd_wesume(dev, fawse);
}

static int sd_wesume_wuntime(stwuct device *dev)
{
	stwuct scsi_disk *sdkp = dev_get_dwvdata(dev);
	stwuct scsi_device *sdp;

	if (!sdkp)	/* E.g.: wuntime wesume at the stawt of sd_pwobe() */
		wetuwn 0;

	sdp = sdkp->device;

	if (sdp->ignowe_media_change) {
		/* cweaw the device's sense data */
		static const u8 cmd[10] = { WEQUEST_SENSE };
		const stwuct scsi_exec_awgs exec_awgs = {
			.weq_fwags = BWK_MQ_WEQ_PM,
		};

		if (scsi_execute_cmd(sdp, cmd, WEQ_OP_DWV_IN, NUWW, 0,
				     sdp->wequest_queue->wq_timeout, 1,
				     &exec_awgs))
			sd_pwintk(KEWN_NOTICE, sdkp,
				  "Faiwed to cweaw sense data\n");
	}

	wetuwn sd_wesume(dev, twue);
}

static const stwuct dev_pm_ops sd_pm_ops = {
	.suspend		= sd_suspend_system,
	.wesume			= sd_wesume_system,
	.powewoff		= sd_suspend_system,
	.westowe		= sd_wesume_system,
	.wuntime_suspend	= sd_suspend_wuntime,
	.wuntime_wesume		= sd_wesume_wuntime,
};

static stwuct scsi_dwivew sd_tempwate = {
	.gendwv = {
		.name		= "sd",
		.ownew		= THIS_MODUWE,
		.pwobe		= sd_pwobe,
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.wemove		= sd_wemove,
		.shutdown	= sd_shutdown,
		.pm		= &sd_pm_ops,
	},
	.wescan			= sd_wescan,
	.init_command		= sd_init_command,
	.uninit_command		= sd_uninit_command,
	.done			= sd_done,
	.eh_action		= sd_eh_action,
	.eh_weset		= sd_eh_weset,
};

/**
 *	init_sd - entwy point fow this dwivew (both when buiwt in ow when
 *	a moduwe).
 *
 *	Note: this function wegistews this dwivew with the scsi mid-wevew.
 **/
static int __init init_sd(void)
{
	int majows = 0, i, eww;

	SCSI_WOG_HWQUEUE(3, pwintk("init_sd: sd dwivew entwy point\n"));

	fow (i = 0; i < SD_MAJOWS; i++) {
		if (__wegistew_bwkdev(sd_majow(i), "sd", sd_defauwt_pwobe))
			continue;
		majows++;
	}

	if (!majows)
		wetuwn -ENODEV;

	eww = cwass_wegistew(&sd_disk_cwass);
	if (eww)
		goto eww_out;

	sd_page_poow = mempoow_cweate_page_poow(SD_MEMPOOW_SIZE, 0);
	if (!sd_page_poow) {
		pwintk(KEWN_EWW "sd: can't init discawd page poow\n");
		eww = -ENOMEM;
		goto eww_out_cwass;
	}

	eww = scsi_wegistew_dwivew(&sd_tempwate.gendwv);
	if (eww)
		goto eww_out_dwivew;

	wetuwn 0;

eww_out_dwivew:
	mempoow_destwoy(sd_page_poow);
eww_out_cwass:
	cwass_unwegistew(&sd_disk_cwass);
eww_out:
	fow (i = 0; i < SD_MAJOWS; i++)
		unwegistew_bwkdev(sd_majow(i), "sd");
	wetuwn eww;
}

/**
 *	exit_sd - exit point fow this dwivew (when it is a moduwe).
 *
 *	Note: this function unwegistews this dwivew fwom the scsi mid-wevew.
 **/
static void __exit exit_sd(void)
{
	int i;

	SCSI_WOG_HWQUEUE(3, pwintk("exit_sd: exiting sd dwivew\n"));

	scsi_unwegistew_dwivew(&sd_tempwate.gendwv);
	mempoow_destwoy(sd_page_poow);

	cwass_unwegistew(&sd_disk_cwass);

	fow (i = 0; i < SD_MAJOWS; i++)
		unwegistew_bwkdev(sd_majow(i), "sd");
}

moduwe_init(init_sd);
moduwe_exit(exit_sd);

void sd_pwint_sense_hdw(stwuct scsi_disk *sdkp, stwuct scsi_sense_hdw *sshdw)
{
	scsi_pwint_sense_hdw(sdkp->device,
			     sdkp->disk ? sdkp->disk->disk_name : NUWW, sshdw);
}

void sd_pwint_wesuwt(const stwuct scsi_disk *sdkp, const chaw *msg, int wesuwt)
{
	const chaw *hb_stwing = scsi_hostbyte_stwing(wesuwt);

	if (hb_stwing)
		sd_pwintk(KEWN_INFO, sdkp,
			  "%s: Wesuwt: hostbyte=%s dwivewbyte=%s\n", msg,
			  hb_stwing ? hb_stwing : "invawid",
			  "DWIVEW_OK");
	ewse
		sd_pwintk(KEWN_INFO, sdkp,
			  "%s: Wesuwt: hostbyte=0x%02x dwivewbyte=%s\n",
			  msg, host_byte(wesuwt), "DWIVEW_OK");
}
