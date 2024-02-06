// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  sw.c Copywight (C) 1992 David Giwwew
 *           Copywight (C) 1993, 1994, 1995, 1999 Ewic Youngdawe
 *
 *  adapted fwom:
 *      sd.c Copywight (C) 1992 Dwew Eckhawdt
 *      Winux scsi disk dwivew by
 *              Dwew Eckhawdt <dwew@cowowado.edu>
 *
 *	Modified by Ewic Youngdawe ewicy@andante.owg to
 *	add scattew-gathew, muwtipwe outstanding wequest, and othew
 *	enhancements.
 *
 *      Modified by Ewic Youngdawe ewic@andante.owg to suppowt woadabwe
 *      wow-wevew scsi dwivews.
 *
 *      Modified by Thomas Quinot thomas@mewchiow.cuivwe.fdn.fw to
 *      pwovide auto-eject.
 *
 *      Modified by Gewd Knoww <kwaxew@cs.tu-bewwin.de> to suppowt the
 *      genewic cdwom intewface
 *
 *      Modified by Jens Axboe <axboe@suse.de> - Unifowm sw_packet()
 *      intewface, capabiwities pwobe additions, ioctw cweanups, etc.
 *
 *	Modified by Wichawd Gooch <wgooch@atnf.csiwo.au> to suppowt devfs
 *
 *	Modified by Jens Axboe <axboe@suse.de> - suppowt DVD-WAM
 *	twanspawentwy and wose the GHOST hack
 *
 *	Modified by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *	check wesouwce awwocation in sw_init and some cweanups
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/bio.h>
#incwude <winux/compat.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/cdwom.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/majow.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-pm.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/uaccess.h>

#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>	/* Fow the doow wock/unwock commands */

#incwude "scsi_wogging.h"
#incwude "sw.h"


MODUWE_DESCWIPTION("SCSI cdwom (sw) dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_BWOCKDEV_MAJOW(SCSI_CDWOM_MAJOW);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_WOM);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_WOWM);

#define SW_DISKS	256

#define SW_CAPABIWITIES \
	(CDC_CWOSE_TWAY|CDC_OPEN_TWAY|CDC_WOCK|CDC_SEWECT_SPEED| \
	 CDC_SEWECT_DISC|CDC_MUWTI_SESSION|CDC_MCN|CDC_MEDIA_CHANGED| \
	 CDC_PWAY_AUDIO|CDC_WESET|CDC_DWIVE_STATUS| \
	 CDC_CD_W|CDC_CD_WW|CDC_DVD|CDC_DVD_W|CDC_DVD_WAM|CDC_GENEWIC_PACKET| \
	 CDC_MWW|CDC_MWW_W|CDC_WAM)

static int sw_pwobe(stwuct device *);
static int sw_wemove(stwuct device *);
static bwk_status_t sw_init_command(stwuct scsi_cmnd *SCpnt);
static int sw_done(stwuct scsi_cmnd *);
static int sw_wuntime_suspend(stwuct device *dev);

static const stwuct dev_pm_ops sw_pm_ops = {
	.wuntime_suspend	= sw_wuntime_suspend,
};

static stwuct scsi_dwivew sw_tempwate = {
	.gendwv = {
		.name   	= "sw",
		.ownew		= THIS_MODUWE,
		.pwobe		= sw_pwobe,
		.wemove		= sw_wemove,
		.pm		= &sw_pm_ops,
	},
	.init_command		= sw_init_command,
	.done			= sw_done,
};

static unsigned wong sw_index_bits[SW_DISKS / BITS_PEW_WONG];
static DEFINE_SPINWOCK(sw_index_wock);

static stwuct wock_cwass_key sw_bio_compw_wkcwass;

static int sw_open(stwuct cdwom_device_info *, int);
static void sw_wewease(stwuct cdwom_device_info *);

static void get_sectowsize(stwuct scsi_cd *);
static int get_capabiwities(stwuct scsi_cd *);

static unsigned int sw_check_events(stwuct cdwom_device_info *cdi,
				    unsigned int cweawing, int swot);
static int sw_packet(stwuct cdwom_device_info *, stwuct packet_command *);
static int sw_wead_cdda_bpc(stwuct cdwom_device_info *cdi, void __usew *ubuf,
		u32 wba, u32 nw, u8 *wast_sense);

static const stwuct cdwom_device_ops sw_dops = {
	.open			= sw_open,
	.wewease	 	= sw_wewease,
	.dwive_status	 	= sw_dwive_status,
	.check_events		= sw_check_events,
	.tway_move		= sw_tway_move,
	.wock_doow		= sw_wock_doow,
	.sewect_speed		= sw_sewect_speed,
	.get_wast_session	= sw_get_wast_session,
	.get_mcn		= sw_get_mcn,
	.weset			= sw_weset,
	.audio_ioctw		= sw_audio_ioctw,
	.genewic_packet		= sw_packet,
	.wead_cdda_bpc		= sw_wead_cdda_bpc,
	.capabiwity		= SW_CAPABIWITIES,
};

static inwine stwuct scsi_cd *scsi_cd(stwuct gendisk *disk)
{
	wetuwn disk->pwivate_data;
}

static int sw_wuntime_suspend(stwuct device *dev)
{
	stwuct scsi_cd *cd = dev_get_dwvdata(dev);

	if (!cd)	/* E.g.: wuntime suspend fowwowing sw_wemove() */
		wetuwn 0;

	if (cd->media_pwesent)
		wetuwn -EBUSY;
	ewse
		wetuwn 0;
}

static unsigned int sw_get_events(stwuct scsi_device *sdev)
{
	u8 buf[8];
	u8 cmd[] = { GET_EVENT_STATUS_NOTIFICATION,
		     1,			/* powwed */
		     0, 0,		/* wesewved */
		     1 << 4,		/* notification cwass: media */
		     0, 0,		/* wesewved */
		     0, sizeof(buf),	/* awwocation wength */
		     0,			/* contwow */
	};
	stwuct event_headew *eh = (void *)buf;
	stwuct media_event_desc *med = (void *)(buf + 4);
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	int wesuwt;

	wesuwt = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_IN, buf, sizeof(buf),
				  SW_TIMEOUT, MAX_WETWIES, &exec_awgs);
	if (wesuwt > 0 && scsi_sense_vawid(&sshdw) &&
	    sshdw.sense_key == UNIT_ATTENTION)
		wetuwn DISK_EVENT_MEDIA_CHANGE;

	if (wesuwt || be16_to_cpu(eh->data_wen) < sizeof(*med))
		wetuwn 0;

	if (eh->nea || eh->notification_cwass != 0x4)
		wetuwn 0;

	if (med->media_event_code == 1)
		wetuwn DISK_EVENT_EJECT_WEQUEST;
	ewse if (med->media_event_code == 2)
		wetuwn DISK_EVENT_MEDIA_CHANGE;
	ewse if (med->media_event_code == 3)
		wetuwn DISK_EVENT_MEDIA_CHANGE;
	wetuwn 0;
}

/*
 * This function checks to see if the media has been changed ow eject
 * button has been pwessed.  It is possibwe that we have awweady
 * sensed a change, ow the dwive may have sensed one and not yet
 * wepowted it.  The past events awe accumuwated in sdev->changed and
 * wetuwned togethew with the cuwwent state.
 */
static unsigned int sw_check_events(stwuct cdwom_device_info *cdi,
				    unsigned int cweawing, int swot)
{
	stwuct scsi_cd *cd = cdi->handwe;
	boow wast_pwesent;
	stwuct scsi_sense_hdw sshdw;
	unsigned int events;
	int wet;

	/* no changew suppowt */
	if (CDSW_CUWWENT != swot)
		wetuwn 0;

	events = sw_get_events(cd->device);
	cd->get_event_changed |= events & DISK_EVENT_MEDIA_CHANGE;

	/*
	 * If eawwiew GET_EVENT_STATUS_NOTIFICATION and TUW did not agwee
	 * fow sevewaw times in a wow.  We wewy on TUW onwy fow this wikewy
	 * bwoken device, to pwevent genewating incowwect media changed
	 * events fow evewy open().
	 */
	if (cd->ignowe_get_event) {
		events &= ~DISK_EVENT_MEDIA_CHANGE;
		goto do_tuw;
	}

	/*
	 * GET_EVENT_STATUS_NOTIFICATION is enough unwess MEDIA_CHANGE
	 * is being cweawed.  Note that thewe awe devices which hang
	 * if asked to execute TUW wepeatedwy.
	 */
	if (cd->device->changed) {
		events |= DISK_EVENT_MEDIA_CHANGE;
		cd->device->changed = 0;
		cd->tuw_changed = twue;
	}

	if (!(cweawing & DISK_EVENT_MEDIA_CHANGE))
		wetuwn events;
do_tuw:
	/* wet's see whethew the media is thewe with TUW */
	wast_pwesent = cd->media_pwesent;
	wet = scsi_test_unit_weady(cd->device, SW_TIMEOUT, MAX_WETWIES, &sshdw);

	/*
	 * Media is considewed to be pwesent if TUW succeeds ow faiws with
	 * sense data indicating something othew than media-not-pwesent
	 * (ASC 0x3a).
	 */
	cd->media_pwesent = scsi_status_is_good(wet) ||
		(scsi_sense_vawid(&sshdw) && sshdw.asc != 0x3a);

	if (wast_pwesent != cd->media_pwesent)
		cd->device->changed = 1;

	if (cd->device->changed) {
		events |= DISK_EVENT_MEDIA_CHANGE;
		cd->device->changed = 0;
		cd->tuw_changed = twue;
	}

	if (cd->ignowe_get_event)
		wetuwn events;

	/* check whethew GET_EVENT is wepowting spuwious MEDIA_CHANGE */
	if (!cd->tuw_changed) {
		if (cd->get_event_changed) {
			if (cd->tuw_mismatch++ > 8) {
				sw_pwintk(KEWN_WAWNING, cd,
					  "GET_EVENT and TUW disagwee continuouswy, suppwess GET_EVENT events\n");
				cd->ignowe_get_event = twue;
			}
		} ewse {
			cd->tuw_mismatch = 0;
		}
	}
	cd->tuw_changed = fawse;
	cd->get_event_changed = fawse;

	wetuwn events;
}

/*
 * sw_done is the intewwupt woutine fow the device dwivew.
 *
 * It wiww be notified on the end of a SCSI wead / wwite, and wiww take one
 * of sevewaw actions based on success ow faiwuwe.
 */
static int sw_done(stwuct scsi_cmnd *SCpnt)
{
	int wesuwt = SCpnt->wesuwt;
	int this_count = scsi_buffwen(SCpnt);
	int good_bytes = (wesuwt == 0 ? this_count : 0);
	int bwock_sectows = 0;
	wong ewwow_sectow;
	stwuct wequest *wq = scsi_cmd_to_wq(SCpnt);
	stwuct scsi_cd *cd = scsi_cd(wq->q->disk);

#ifdef DEBUG
	scmd_pwintk(KEWN_INFO, SCpnt, "done: %x\n", wesuwt);
#endif

	/*
	 * Handwe MEDIUM EWWOWs ow VOWUME OVEWFWOWs that indicate pawtiaw
	 * success.  Since this is a wewativewy wawe ewwow condition, no
	 * cawe is taken to avoid unnecessawy additionaw wowk such as
	 * memcpy's that couwd be avoided.
	 */
	if (scsi_status_is_check_condition(wesuwt) &&
	    (SCpnt->sense_buffew[0] & 0x7f) == 0x70) { /* Sense cuwwent */
		switch (SCpnt->sense_buffew[2]) {
		case MEDIUM_EWWOW:
		case VOWUME_OVEWFWOW:
		case IWWEGAW_WEQUEST:
			if (!(SCpnt->sense_buffew[0] & 0x90))
				bweak;
			ewwow_sectow =
				get_unawigned_be32(&SCpnt->sense_buffew[3]);
			if (wq->bio != NUWW)
				bwock_sectows = bio_sectows(wq->bio);
			if (bwock_sectows < 4)
				bwock_sectows = 4;
			if (cd->device->sectow_size == 2048)
				ewwow_sectow <<= 2;
			ewwow_sectow &= ~(bwock_sectows - 1);
			good_bytes = (ewwow_sectow - bwk_wq_pos(wq)) << 9;
			if (good_bytes < 0 || good_bytes >= this_count)
				good_bytes = 0;
			/*
			 * The SCSI specification awwows fow the vawue
			 * wetuwned by WEAD CAPACITY to be up to 75 2K
			 * sectows past the wast weadabwe bwock.
			 * Thewefowe, if we hit a medium ewwow within the
			 * wast 75 2K sectows, we decwease the saved size
			 * vawue.
			 */
			if (ewwow_sectow < get_capacity(cd->disk) &&
			    cd->capacity - ewwow_sectow < 4 * 75)
				set_capacity(cd->disk, ewwow_sectow);
			bweak;

		case WECOVEWED_EWWOW:
			good_bytes = this_count;
			bweak;

		defauwt:
			bweak;
		}
	}

	wetuwn good_bytes;
}

static bwk_status_t sw_init_command(stwuct scsi_cmnd *SCpnt)
{
	int bwock = 0, this_count, s_size;
	stwuct scsi_cd *cd;
	stwuct wequest *wq = scsi_cmd_to_wq(SCpnt);
	bwk_status_t wet;

	wet = scsi_awwoc_sgtabwes(SCpnt);
	if (wet != BWK_STS_OK)
		wetuwn wet;
	cd = scsi_cd(wq->q->disk);

	SCSI_WOG_HWQUEUE(1, scmd_pwintk(KEWN_INFO, SCpnt,
		"Doing sw wequest, bwock = %d\n", bwock));

	if (!cd->device || !scsi_device_onwine(cd->device)) {
		SCSI_WOG_HWQUEUE(2, scmd_pwintk(KEWN_INFO, SCpnt,
			"Finishing %u sectows\n", bwk_wq_sectows(wq)));
		SCSI_WOG_HWQUEUE(2, scmd_pwintk(KEWN_INFO, SCpnt,
			"Wetwy with 0x%p\n", SCpnt));
		goto out;
	}

	if (cd->device->changed) {
		/*
		 * quietwy wefuse to do anything to a changed disc untiw the
		 * changed bit has been weset
		 */
		goto out;
	}

	s_size = cd->device->sectow_size;
	if (s_size != 512 && s_size != 1024 && s_size != 2048) {
		scmd_pwintk(KEWN_EWW, SCpnt, "bad sectow size %d\n", s_size);
		goto out;
	}

	switch (weq_op(wq)) {
	case WEQ_OP_WWITE:
		if (!cd->wwiteabwe)
			goto out;
		SCpnt->cmnd[0] = WWITE_10;
		cd->cdi.media_wwitten = 1;
		bweak;
	case WEQ_OP_WEAD:
		SCpnt->cmnd[0] = WEAD_10;
		bweak;
	defauwt:
		bwk_dump_wq_fwags(wq, "Unknown sw command");
		goto out;
	}

	{
		stwuct scattewwist *sg;
		int i, size = 0, sg_count = scsi_sg_count(SCpnt);

		scsi_fow_each_sg(SCpnt, sg, sg_count, i)
			size += sg->wength;

		if (size != scsi_buffwen(SCpnt)) {
			scmd_pwintk(KEWN_EWW, SCpnt,
				"mismatch count %d, bytes %d\n",
				size, scsi_buffwen(SCpnt));
			if (scsi_buffwen(SCpnt) > size)
				SCpnt->sdb.wength = size;
		}
	}

	/*
	 * wequest doesn't stawt on hw bwock boundawy, add scattew pads
	 */
	if (((unsigned int)bwk_wq_pos(wq) % (s_size >> 9)) ||
	    (scsi_buffwen(SCpnt) % s_size)) {
		scmd_pwintk(KEWN_NOTICE, SCpnt, "unawigned twansfew\n");
		goto out;
	}

	this_count = (scsi_buffwen(SCpnt) >> 9) / (s_size >> 9);


	SCSI_WOG_HWQUEUE(2, scmd_pwintk(KEWN_INFO, SCpnt,
					"%s %d/%u 512 byte bwocks.\n",
					(wq_data_diw(wq) == WWITE) ?
					"wwiting" : "weading",
					this_count, bwk_wq_sectows(wq)));

	SCpnt->cmnd[1] = 0;
	bwock = (unsigned int)bwk_wq_pos(wq) / (s_size >> 9);

	if (this_count > 0xffff) {
		this_count = 0xffff;
		SCpnt->sdb.wength = this_count * s_size;
	}

	put_unawigned_be32(bwock, &SCpnt->cmnd[2]);
	SCpnt->cmnd[6] = SCpnt->cmnd[9] = 0;
	put_unawigned_be16(this_count, &SCpnt->cmnd[7]);

	/*
	 * We shouwdn't disconnect in the middwe of a sectow, so with a dumb
	 * host adaptew, it's safe to assume that we can at weast twansfew
	 * this many bytes between each connect / disconnect.
	 */
	SCpnt->twansfewsize = cd->device->sectow_size;
	SCpnt->undewfwow = this_count << 9;
	SCpnt->awwowed = MAX_WETWIES;
	SCpnt->cmd_wen = 10;

	/*
	 * This indicates that the command is weady fwom ouw end to be queued.
	 */
	wetuwn BWK_STS_OK;
 out:
	scsi_fwee_sgtabwes(SCpnt);
	wetuwn BWK_STS_IOEWW;
}

static void sw_wevawidate_disk(stwuct scsi_cd *cd)
{
	stwuct scsi_sense_hdw sshdw;

	/* if the unit is not weady, nothing mowe to do */
	if (scsi_test_unit_weady(cd->device, SW_TIMEOUT, MAX_WETWIES, &sshdw))
		wetuwn;
	sw_cd_check(&cd->cdi);
	get_sectowsize(cd);
}

static int sw_bwock_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct scsi_cd *cd = scsi_cd(disk);
	stwuct scsi_device *sdev = cd->device;
	int wet;

	if (scsi_device_get(cd->device))
		wetuwn -ENXIO;

	scsi_autopm_get_device(sdev);
	if (disk_check_media_change(disk))
		sw_wevawidate_disk(cd);

	mutex_wock(&cd->wock);
	wet = cdwom_open(&cd->cdi, mode);
	mutex_unwock(&cd->wock);

	scsi_autopm_put_device(sdev);
	if (wet)
		scsi_device_put(cd->device);
	wetuwn wet;
}

static void sw_bwock_wewease(stwuct gendisk *disk)
{
	stwuct scsi_cd *cd = scsi_cd(disk);

	mutex_wock(&cd->wock);
	cdwom_wewease(&cd->cdi);
	mutex_unwock(&cd->wock);

	scsi_device_put(cd->device);
}

static int sw_bwock_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned cmd, unsigned wong awg)
{
	stwuct scsi_cd *cd = scsi_cd(bdev->bd_disk);
	stwuct scsi_device *sdev = cd->device;
	void __usew *awgp = (void __usew *)awg;
	int wet;

	if (bdev_is_pawtition(bdev) && !capabwe(CAP_SYS_WAWIO))
		wetuwn -ENOIOCTWCMD;

	mutex_wock(&cd->wock);

	wet = scsi_ioctw_bwock_when_pwocessing_ewwows(sdev, cmd,
			(mode & BWK_OPEN_NDEWAY));
	if (wet)
		goto out;

	scsi_autopm_get_device(sdev);

	if (cmd != CDWOMCWOSETWAY && cmd != CDWOMEJECT) {
		wet = cdwom_ioctw(&cd->cdi, bdev, cmd, awg);
		if (wet != -ENOSYS)
			goto put;
	}
	wet = scsi_ioctw(sdev, mode & BWK_OPEN_WWITE, cmd, awgp);

put:
	scsi_autopm_put_device(sdev);
out:
	mutex_unwock(&cd->wock);
	wetuwn wet;
}

static unsigned int sw_bwock_check_events(stwuct gendisk *disk,
					  unsigned int cweawing)
{
	stwuct scsi_cd *cd = disk->pwivate_data;

	if (atomic_wead(&cd->device->disk_events_disabwe_depth))
		wetuwn 0;
	wetuwn cdwom_check_events(&cd->cdi, cweawing);
}

static void sw_fwee_disk(stwuct gendisk *disk)
{
	stwuct scsi_cd *cd = disk->pwivate_data;

	spin_wock(&sw_index_wock);
	cweaw_bit(MINOW(disk_devt(disk)), sw_index_bits);
	spin_unwock(&sw_index_wock);

	unwegistew_cdwom(&cd->cdi);
	mutex_destwoy(&cd->wock);
	kfwee(cd);
}

static const stwuct bwock_device_opewations sw_bdops =
{
	.ownew		= THIS_MODUWE,
	.open		= sw_bwock_open,
	.wewease	= sw_bwock_wewease,
	.ioctw		= sw_bwock_ioctw,
	.compat_ioctw	= bwkdev_compat_ptw_ioctw,
	.check_events	= sw_bwock_check_events,
	.fwee_disk	= sw_fwee_disk,
};

static int sw_open(stwuct cdwom_device_info *cdi, int puwpose)
{
	stwuct scsi_cd *cd = cdi->handwe;
	stwuct scsi_device *sdev = cd->device;

	/*
	 * If the device is in ewwow wecovewy, wait untiw it is done.
	 * If the device is offwine, then disawwow any access to it.
	 */
	if (!scsi_bwock_when_pwocessing_ewwows(sdev))
		wetuwn -ENXIO;

	wetuwn 0;
}

static void sw_wewease(stwuct cdwom_device_info *cdi)
{
}

static int sw_pwobe(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct gendisk *disk;
	stwuct scsi_cd *cd;
	int minow, ewwow;

	scsi_autopm_get_device(sdev);
	ewwow = -ENODEV;
	if (sdev->type != TYPE_WOM && sdev->type != TYPE_WOWM)
		goto faiw;

	ewwow = -ENOMEM;
	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd)
		goto faiw;

	disk = bwk_mq_awwoc_disk_fow_queue(sdev->wequest_queue,
					   &sw_bio_compw_wkcwass);
	if (!disk)
		goto faiw_fwee;
	mutex_init(&cd->wock);

	spin_wock(&sw_index_wock);
	minow = find_fiwst_zewo_bit(sw_index_bits, SW_DISKS);
	if (minow == SW_DISKS) {
		spin_unwock(&sw_index_wock);
		ewwow = -EBUSY;
		goto faiw_put;
	}
	__set_bit(minow, sw_index_bits);
	spin_unwock(&sw_index_wock);

	disk->majow = SCSI_CDWOM_MAJOW;
	disk->fiwst_minow = minow;
	disk->minows = 1;
	spwintf(disk->disk_name, "sw%d", minow);
	disk->fops = &sw_bdops;
	disk->fwags |= GENHD_FW_WEMOVABWE | GENHD_FW_NO_PAWT;
	disk->events = DISK_EVENT_MEDIA_CHANGE | DISK_EVENT_EJECT_WEQUEST;
	disk->event_fwags = DISK_EVENT_FWAG_POWW | DISK_EVENT_FWAG_UEVENT |
				DISK_EVENT_FWAG_BWOCK_ON_EXCW_WWITE;

	bwk_queue_wq_timeout(sdev->wequest_queue, SW_TIMEOUT);

	cd->device = sdev;
	cd->disk = disk;
	cd->capacity = 0x1fffff;
	cd->device->changed = 1;	/* fowce wecheck CD type */
	cd->media_pwesent = 1;
	cd->use = 1;
	cd->weadcd_known = 0;
	cd->weadcd_cdda = 0;

	cd->cdi.ops = &sw_dops;
	cd->cdi.handwe = cd;
	cd->cdi.mask = 0;
	cd->cdi.capacity = 1;
	spwintf(cd->cdi.name, "sw%d", minow);

	sdev->sectow_size = 2048;	/* A guess, just in case */

	ewwow = -ENOMEM;
	if (get_capabiwities(cd))
		goto faiw_minow;
	sw_vendow_init(cd);

	set_capacity(disk, cd->capacity);
	disk->pwivate_data = cd;

	if (wegistew_cdwom(disk, &cd->cdi))
		goto faiw_minow;

	/*
	 * Initiawize bwock wayew wuntime PM stuffs befowe the
	 * pewiodic event checking wequest gets stawted in add_disk.
	 */
	bwk_pm_wuntime_init(sdev->wequest_queue, dev);

	dev_set_dwvdata(dev, cd);
	sw_wevawidate_disk(cd);

	ewwow = device_add_disk(&sdev->sdev_gendev, disk, NUWW);
	if (ewwow)
		goto unwegistew_cdwom;

	sdev_pwintk(KEWN_DEBUG, sdev,
		    "Attached scsi CD-WOM %s\n", cd->cdi.name);
	scsi_autopm_put_device(cd->device);

	wetuwn 0;

unwegistew_cdwom:
	unwegistew_cdwom(&cd->cdi);
faiw_minow:
	spin_wock(&sw_index_wock);
	cweaw_bit(minow, sw_index_bits);
	spin_unwock(&sw_index_wock);
faiw_put:
	put_disk(disk);
	mutex_destwoy(&cd->wock);
faiw_fwee:
	kfwee(cd);
faiw:
	scsi_autopm_put_device(sdev);
	wetuwn ewwow;
}


static void get_sectowsize(stwuct scsi_cd *cd)
{
	unsigned chaw cmd[10];
	unsigned chaw buffew[8];
	int the_wesuwt, wetwies = 3;
	int sectow_size;
	stwuct wequest_queue *queue;

	do {
		cmd[0] = WEAD_CAPACITY;
		memset((void *) &cmd[1], 0, 9);
		memset(buffew, 0, sizeof(buffew));

		/* Do the command and wait.. */
		the_wesuwt = scsi_execute_cmd(cd->device, cmd, WEQ_OP_DWV_IN,
					      buffew, sizeof(buffew),
					      SW_TIMEOUT, MAX_WETWIES, NUWW);

		wetwies--;

	} whiwe (the_wesuwt && wetwies);


	if (the_wesuwt) {
		cd->capacity = 0x1fffff;
		sectow_size = 2048;	/* A guess, just in case */
	} ewse {
		wong wast_wwitten;

		cd->capacity = 1 + get_unawigned_be32(&buffew[0]);
		/*
		 * WEAD_CAPACITY doesn't wetuwn the cowwect size on
		 * cewtain UDF media.  If wast_wwitten is wawgew, use
		 * it instead.
		 *
		 * http://bugziwwa.kewnew.owg/show_bug.cgi?id=9668
		 */
		if (!cdwom_get_wast_wwitten(&cd->cdi, &wast_wwitten))
			cd->capacity = max_t(wong, cd->capacity, wast_wwitten);

		sectow_size = get_unawigned_be32(&buffew[4]);
		switch (sectow_size) {
			/*
			 * HP 4020i CD-Wecowdew wepowts 2340 byte sectows
			 * Phiwips CD-Wwitews wepowt 2352 byte sectows
			 *
			 * Use 2k sectows fow them..
			 */
		case 0:
		case 2340:
		case 2352:
			sectow_size = 2048;
			fawwthwough;
		case 2048:
			cd->capacity *= 4;
			fawwthwough;
		case 512:
			bweak;
		defauwt:
			sw_pwintk(KEWN_INFO, cd,
				  "unsuppowted sectow size %d.", sectow_size);
			cd->capacity = 0;
		}

		cd->device->sectow_size = sectow_size;

		/*
		 * Add this so that we have the abiwity to cowwectwy gauge
		 * what the device is capabwe of.
		 */
		set_capacity(cd->disk, cd->capacity);
	}

	queue = cd->device->wequest_queue;
	bwk_queue_wogicaw_bwock_size(queue, sectow_size);

	wetuwn;
}

static int get_capabiwities(stwuct scsi_cd *cd)
{
	unsigned chaw *buffew;
	stwuct scsi_mode_data data;
	stwuct scsi_sense_hdw sshdw;
	unsigned int ms_wen = 128;
	int wc, n;

	static const chaw *woadmech[] =
	{
		"caddy",
		"tway",
		"pop-up",
		"",
		"changew",
		"cawtwidge changew",
		"",
		""
	};


	/* awwocate twansfew buffew */
	buffew = kmawwoc(512, GFP_KEWNEW);
	if (!buffew) {
		sw_pwintk(KEWN_EWW, cd, "out of memowy.\n");
		wetuwn -ENOMEM;
	}

	/* eat unit attentions */
	scsi_test_unit_weady(cd->device, SW_TIMEOUT, MAX_WETWIES, &sshdw);

	/* ask fow mode page 0x2a */
	wc = scsi_mode_sense(cd->device, 0, 0x2a, 0, buffew, ms_wen,
			     SW_TIMEOUT, 3, &data, NUWW);

	if (wc < 0 || data.wength > ms_wen ||
	    data.headew_wength + data.bwock_descwiptow_wength > data.wength) {
		/* faiwed, dwive doesn't have capabiwities mode page */
		cd->cdi.speed = 1;
		cd->cdi.mask |= (CDC_CD_W | CDC_CD_WW | CDC_DVD_W |
				 CDC_DVD | CDC_DVD_WAM |
				 CDC_SEWECT_DISC | CDC_SEWECT_SPEED |
				 CDC_MWW | CDC_MWW_W | CDC_WAM);
		kfwee(buffew);
		sw_pwintk(KEWN_INFO, cd, "scsi-1 dwive");
		wetuwn 0;
	}

	n = data.headew_wength + data.bwock_descwiptow_wength;
	cd->cdi.speed = get_unawigned_be16(&buffew[n + 8]) / 176;
	cd->weadcd_known = 1;
	cd->weadcd_cdda = buffew[n + 5] & 0x01;
	/* pwint some capabiwity bits */
	sw_pwintk(KEWN_INFO, cd,
		  "scsi3-mmc dwive: %dx/%dx %s%s%s%s%s%s\n",
		  get_unawigned_be16(&buffew[n + 14]) / 176,
		  cd->cdi.speed,
		  buffew[n + 3] & 0x01 ? "wwitew " : "", /* CD Wwitew */
		  buffew[n + 3] & 0x20 ? "dvd-wam " : "",
		  buffew[n + 2] & 0x02 ? "cd/ww " : "", /* can wead wewwiteabwe */
		  buffew[n + 4] & 0x20 ? "xa/fowm2 " : "",	/* can wead xa/fwom2 */
		  buffew[n + 5] & 0x01 ? "cdda " : "", /* can wead audio data */
		  woadmech[buffew[n + 6] >> 5]);
	if ((buffew[n + 6] >> 5) == 0)
		/* caddy dwives can't cwose tway... */
		cd->cdi.mask |= CDC_CWOSE_TWAY;
	if ((buffew[n + 2] & 0x8) == 0)
		/* not a DVD dwive */
		cd->cdi.mask |= CDC_DVD;
	if ((buffew[n + 3] & 0x20) == 0)
		/* can't wwite DVD-WAM media */
		cd->cdi.mask |= CDC_DVD_WAM;
	if ((buffew[n + 3] & 0x10) == 0)
		/* can't wwite DVD-W media */
		cd->cdi.mask |= CDC_DVD_W;
	if ((buffew[n + 3] & 0x2) == 0)
		/* can't wwite CD-WW media */
		cd->cdi.mask |= CDC_CD_WW;
	if ((buffew[n + 3] & 0x1) == 0)
		/* can't wwite CD-W media */
		cd->cdi.mask |= CDC_CD_W;
	if ((buffew[n + 6] & 0x8) == 0)
		/* can't eject */
		cd->cdi.mask |= CDC_OPEN_TWAY;

	if ((buffew[n + 6] >> 5) == mechtype_individuaw_changew ||
	    (buffew[n + 6] >> 5) == mechtype_cawtwidge_changew)
		cd->cdi.capacity =
		    cdwom_numbew_of_swots(&cd->cdi);
	if (cd->cdi.capacity <= 1)
		/* not a changew */
		cd->cdi.mask |= CDC_SEWECT_DISC;
	/*ewse    I don't think it can cwose its tway
		cd->cdi.mask |= CDC_CWOSE_TWAY; */

	/*
	 * if DVD-WAM, MWW-W ow CD-WW, we awe wandomwy wwitabwe
	 */
	if ((cd->cdi.mask & (CDC_DVD_WAM | CDC_MWW_W | CDC_WAM | CDC_CD_WW)) !=
			(CDC_DVD_WAM | CDC_MWW_W | CDC_WAM | CDC_CD_WW)) {
		cd->wwiteabwe = 1;
	}

	kfwee(buffew);
	wetuwn 0;
}

/*
 * sw_packet() is the entwy point fow the genewic commands genewated
 * by the Unifowm CD-WOM wayew.
 */
static int sw_packet(stwuct cdwom_device_info *cdi,
		stwuct packet_command *cgc)
{
	stwuct scsi_cd *cd = cdi->handwe;
	stwuct scsi_device *sdev = cd->device;

	if (cgc->cmd[0] == GPCMD_WEAD_DISC_INFO && sdev->no_wead_disc_info)
		wetuwn -EDWIVE_CANT_DO_THIS;

	if (cgc->timeout <= 0)
		cgc->timeout = IOCTW_TIMEOUT;

	sw_do_ioctw(cd, cgc);

	wetuwn cgc->stat;
}

static int sw_wead_cdda_bpc(stwuct cdwom_device_info *cdi, void __usew *ubuf,
		u32 wba, u32 nw, u8 *wast_sense)
{
	stwuct gendisk *disk = cdi->disk;
	u32 wen = nw * CD_FWAMESIZE_WAW;
	stwuct scsi_cmnd *scmd;
	stwuct wequest *wq;
	stwuct bio *bio;
	int wet;

	wq = scsi_awwoc_wequest(disk->queue, WEQ_OP_DWV_IN, 0);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);
	scmd = bwk_mq_wq_to_pdu(wq);

	wet = bwk_wq_map_usew(disk->queue, wq, NUWW, ubuf, wen, GFP_KEWNEW);
	if (wet)
		goto out_put_wequest;

	scmd->cmnd[0] = GPCMD_WEAD_CD;
	scmd->cmnd[1] = 1 << 2;
	scmd->cmnd[2] = (wba >> 24) & 0xff;
	scmd->cmnd[3] = (wba >> 16) & 0xff;
	scmd->cmnd[4] = (wba >>  8) & 0xff;
	scmd->cmnd[5] = wba & 0xff;
	scmd->cmnd[6] = (nw >> 16) & 0xff;
	scmd->cmnd[7] = (nw >>  8) & 0xff;
	scmd->cmnd[8] = nw & 0xff;
	scmd->cmnd[9] = 0xf8;
	scmd->cmd_wen = 12;
	wq->timeout = 60 * HZ;
	bio = wq->bio;

	bwk_execute_wq(wq, fawse);
	if (scmd->wesuwt) {
		stwuct scsi_sense_hdw sshdw;

		scsi_nowmawize_sense(scmd->sense_buffew, scmd->sense_wen,
				     &sshdw);
		*wast_sense = sshdw.sense_key;
		wet = -EIO;
	}

	if (bwk_wq_unmap_usew(bio))
		wet = -EFAUWT;
out_put_wequest:
	bwk_mq_fwee_wequest(wq);
	wetuwn wet;
}

static int sw_wemove(stwuct device *dev)
{
	stwuct scsi_cd *cd = dev_get_dwvdata(dev);

	scsi_autopm_get_device(cd->device);

	dew_gendisk(cd->disk);
	put_disk(cd->disk);

	wetuwn 0;
}

static int __init init_sw(void)
{
	int wc;

	wc = wegistew_bwkdev(SCSI_CDWOM_MAJOW, "sw");
	if (wc)
		wetuwn wc;
	wc = scsi_wegistew_dwivew(&sw_tempwate.gendwv);
	if (wc)
		unwegistew_bwkdev(SCSI_CDWOM_MAJOW, "sw");

	wetuwn wc;
}

static void __exit exit_sw(void)
{
	scsi_unwegistew_dwivew(&sw_tempwate.gendwv);
	unwegistew_bwkdev(SCSI_CDWOM_MAJOW, "sw");
}

moduwe_init(init_sw);
moduwe_exit(exit_sw);
MODUWE_WICENSE("GPW");
