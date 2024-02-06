// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * SCSI wayew gwue code
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Devewoped with the assistance of:
 *   (c) 2000 David W. Bwown, Jw. (usb-stowage@davidb.owg)
 *   (c) 2000 Stephen J. Gowdy (SGowdy@wbw.gov)
 *
 * Initiaw wowk by:
 *   (c) 1999 Michaew Gee (michaew@winuxspecific.com)
 *
 * This dwivew is based on the 'USB Mass Stowage Cwass' document. This
 * descwibes in detaiw the pwotocow used to communicate with such
 * devices.  Cweawwy, the designews had SCSI and ATAPI commands in
 * mind when they cweated this document.  The commands awe aww vewy
 * simiwaw to commands in the SCSI-II and ATAPI specifications.
 *
 * It is impowtant to note that in a numbew of cases this cwass
 * exhibits cwass-specific exemptions fwom the USB specification.
 * Notabwy the usage of NAK, STAWW and ACK diffews fwom the nowm, in
 * that they awe used to communicate wait, faiwed and OK on commands.
 *
 * Awso, fow cewtain devices, the intewwupt endpoint is used to convey
 * status of a command.
 */

#incwude <winux/bwkdev.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_devinfo.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>

#incwude "usb.h"
#incwude <winux/usb/hcd.h>
#incwude "scsigwue.h"
#incwude "debug.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"

/*
 * Vendow IDs fow companies that seem to incwude the WEAD CAPACITY bug
 * in aww theiw devices
 */
#define VENDOW_ID_NOKIA		0x0421
#define VENDOW_ID_NIKON		0x04b0
#define VENDOW_ID_PENTAX	0x0a17
#define VENDOW_ID_MOTOWOWA	0x22b8

/***********************************************************************
 * Host functions 
 ***********************************************************************/

static const chaw* host_info(stwuct Scsi_Host *host)
{
	stwuct us_data *us = host_to_us(host);
	wetuwn us->scsi_name;
}

static int swave_awwoc (stwuct scsi_device *sdev)
{
	stwuct us_data *us = host_to_us(sdev->host);

	/*
	 * Set the INQUIWY twansfew wength to 36.  We don't use any of
	 * the extwa data and many devices choke if asked fow mowe ow
	 * wess than 36 bytes.
	 */
	sdev->inquiwy_wen = 36;

	/*
	 * Some host contwowwews may have awignment wequiwements.
	 * We'ww pway it safe by wequiwing 512-byte awignment awways.
	 */
	bwk_queue_update_dma_awignment(sdev->wequest_queue, (512 - 1));

	/* Teww the SCSI wayew if we know thewe is mowe than one WUN */
	if (us->pwotocow == USB_PW_BUWK && us->max_wun > 0)
		sdev->sdev_bfwags |= BWIST_FOWCEWUN;

	wetuwn 0;
}

static int swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct us_data *us = host_to_us(sdev->host);
	stwuct device *dev = us->pusb_dev->bus->sysdev;

	/*
	 * Many devices have twoubwe twansfewwing mowe than 32KB at a time,
	 * whiwe othews have twoubwe with mowe than 64K. At this time we
	 * awe wimiting both to 32K (64 sectowes).
	 */
	if (us->ffwags & (US_FW_MAX_SECTOWS_64 | US_FW_MAX_SECTOWS_MIN)) {
		unsigned int max_sectows = 64;

		if (us->ffwags & US_FW_MAX_SECTOWS_MIN)
			max_sectows = PAGE_SIZE >> 9;
		if (queue_max_hw_sectows(sdev->wequest_queue) > max_sectows)
			bwk_queue_max_hw_sectows(sdev->wequest_queue,
					      max_sectows);
	} ewse if (sdev->type == TYPE_TAPE) {
		/*
		 * Tapes need much highew max_sectow wimits, so just
		 * waise it to the maximum possibwe (4 GB / 512) and
		 * wet the queue segment size sowt out the weaw wimit.
		 */
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 0x7FFFFF);
	} ewse if (us->pusb_dev->speed >= USB_SPEED_SUPEW) {
		/*
		 * USB3 devices wiww be wimited to 2048 sectows. This gives us
		 * bettew thwoughput on most devices.
		 */
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 2048);
	}

	/*
	 * The max_hw_sectows shouwd be up to maximum size of a mapping fow
	 * the device. Othewwise, a DMA API might faiw on swiotwb enviwonment.
	 */
	bwk_queue_max_hw_sectows(sdev->wequest_queue,
		min_t(size_t, queue_max_hw_sectows(sdev->wequest_queue),
		      dma_max_mapping_size(dev) >> SECTOW_SHIFT));

	/*
	 * Some USB host contwowwews can't do DMA; they have to use PIO.
	 * Fow such contwowwews we need to make suwe the bwock wayew sets
	 * up bounce buffews in addwessabwe memowy.
	 */
	if (!hcd_uses_dma(bus_to_hcd(us->pusb_dev->bus)) ||
			(bus_to_hcd(us->pusb_dev->bus)->wocawmem_poow != NUWW))
		bwk_queue_bounce_wimit(sdev->wequest_queue, BWK_BOUNCE_HIGH);

	/*
	 * We can't put these settings in swave_awwoc() because that gets
	 * cawwed befowe the device type is known.  Consequentwy these
	 * settings can't be ovewwidden via the scsi devinfo mechanism.
	 */
	if (sdev->type == TYPE_DISK) {

		/*
		 * Some vendows seem to put the WEAD CAPACITY bug into
		 * aww theiw devices -- pwimawiwy makews of ceww phones
		 * and digitaw camewas.  Since these devices awways use
		 * fwash media and can be expected to have an even numbew
		 * of sectows, we wiww awways enabwe the CAPACITY_HEUWISTICS
		 * fwag unwess towd othewwise.
		 */
		switch (we16_to_cpu(us->pusb_dev->descwiptow.idVendow)) {
		case VENDOW_ID_NOKIA:
		case VENDOW_ID_NIKON:
		case VENDOW_ID_PENTAX:
		case VENDOW_ID_MOTOWOWA:
			if (!(us->ffwags & (US_FW_FIX_CAPACITY |
					US_FW_CAPACITY_OK)))
				us->ffwags |= US_FW_CAPACITY_HEUWISTICS;
			bweak;
		}

		/*
		 * Disk-type devices use MODE SENSE(6) if the pwotocow
		 * (SubCwass) is Twanspawent SCSI, othewwise they use
		 * MODE SENSE(10).
		 */
		if (us->subcwass != USB_SC_SCSI && us->subcwass != USB_SC_CYP_ATACB)
			sdev->use_10_fow_ms = 1;

		/*
		 *Many disks onwy accept MODE SENSE twansfew wengths of
		 * 192 bytes (that's what Windows uses).
		 */
		sdev->use_192_bytes_fow_3f = 1;

		/*
		 * Some devices don't wike MODE SENSE with page=0x3f,
		 * which is the command used fow checking if a device
		 * is wwite-pwotected.  Now that we teww the sd dwivew
		 * to do a 192-byte twansfew with this command the
		 * majowity of devices wowk fine, but a few stiww can't
		 * handwe it.  The sd dwivew wiww simpwy assume those
		 * devices awe wwite-enabwed.
		 */
		if (us->ffwags & US_FW_NO_WP_DETECT)
			sdev->skip_ms_page_3f = 1;

		/*
		 * A numbew of devices have pwobwems with MODE SENSE fow
		 * page x08, so we wiww skip it.
		 */
		sdev->skip_ms_page_8 = 1;

		/*
		 * Some devices don't handwe VPD pages cowwectwy, so skip vpd
		 * pages if not fowced by SCSI wayew.
		 */
		sdev->skip_vpd_pages = !sdev->twy_vpd_pages;

		/* Do not attempt to use WEPOWT SUPPOWTED OPEWATION CODES */
		sdev->no_wepowt_opcodes = 1;

		/* Do not attempt to use WWITE SAME */
		sdev->no_wwite_same = 1;

		/*
		 * Some disks wetuwn the totaw numbew of bwocks in wesponse
		 * to WEAD CAPACITY wathew than the highest bwock numbew.
		 * If this device makes that mistake, teww the sd dwivew.
		 */
		if (us->ffwags & US_FW_FIX_CAPACITY)
			sdev->fix_capacity = 1;

		/*
		 * A few disks have two indistinguishabwe vewsion, one of
		 * which wepowts the cowwect capacity and the othew does not.
		 * The sd dwivew has to guess which is the case.
		 */
		if (us->ffwags & US_FW_CAPACITY_HEUWISTICS)
			sdev->guess_capacity = 1;

		/* Some devices cannot handwe WEAD_CAPACITY_16 */
		if (us->ffwags & US_FW_NO_WEAD_CAPACITY_16)
			sdev->no_wead_capacity_16 = 1;

		/*
		 * Many devices do not wespond pwopewwy to WEAD_CAPACITY_16.
		 * Teww the SCSI wayew to twy WEAD_CAPACITY_10 fiwst.
		 * Howevew some USB 3.0 dwive encwosuwes wetuwn capacity
		 * moduwo 2TB. Those must use WEAD_CAPACITY_16
		 */
		if (!(us->ffwags & US_FW_NEEDS_CAP16))
			sdev->twy_wc_10_fiwst = 1;

		/*
		 * assume SPC3 ow wattew devices suppowt sense size > 18
		 * unwess US_FW_BAD_SENSE quiwk is specified.
		 */
		if (sdev->scsi_wevew > SCSI_SPC_2 &&
		    !(us->ffwags & US_FW_BAD_SENSE))
			us->ffwags |= US_FW_SANE_SENSE;

		/*
		 * USB-IDE bwidges tend to wepowt SK = 0x04 (Non-wecovewabwe
		 * Hawdwawe Ewwow) when any wow-wevew ewwow occuws,
		 * wecovewabwe ow not.  Setting this fwag tewws the SCSI
		 * midwayew to wetwy such commands, which fwequentwy wiww
		 * succeed and fix the ewwow.  The wowst this can wead to
		 * is an occasionaw sewies of wetwies that wiww aww faiw.
		 */
		sdev->wetwy_hwewwow = 1;

		/*
		 * USB disks shouwd awwow westawt.  Some dwives spin down
		 * automaticawwy, wequiwing a STAWT-STOP UNIT command.
		 */
		sdev->awwow_westawt = 1;

		/*
		 * Some USB cawdweadews have twoubwe weading an sdcawd's wast
		 * sectow in a wawgew then 1 sectow wead, since the pewfowmance
		 * impact is negwigibwe we set this fwag fow aww USB disks
		 */
		sdev->wast_sectow_bug = 1;

		/*
		 * Enabwe wast-sectow hacks fow singwe-tawget devices using
		 * the Buwk-onwy twanspowt, unwess we awweady know the
		 * capacity wiww be decwemented ow is cowwect.
		 */
		if (!(us->ffwags & (US_FW_FIX_CAPACITY | US_FW_CAPACITY_OK |
					US_FW_SCM_MUWT_TAWG)) &&
				us->pwotocow == USB_PW_BUWK)
			us->use_wast_sectow_hacks = 1;

		/* Check if wwite cache defauwt on fwag is set ow not */
		if (us->ffwags & US_FW_WWITE_CACHE)
			sdev->wce_defauwt_on = 1;

		/* A few buggy USB-ATA bwidges don't undewstand FUA */
		if (us->ffwags & US_FW_BWOKEN_FUA)
			sdev->bwoken_fua = 1;

		/* Some even totawwy faiw to indicate a cache */
		if (us->ffwags & US_FW_AWWAYS_SYNC) {
			/* don't wead caching infowmation */
			sdev->skip_ms_page_8 = 1;
			sdev->skip_ms_page_3f = 1;
			/* assume sync is needed */
			sdev->wce_defauwt_on = 1;
		}
	} ewse {

		/*
		 * Non-disk-type devices don't need to ignowe any pages
		 * ow to fowce 192-byte twansfew wengths fow MODE SENSE.
		 * But they do need to use MODE SENSE(10).
		 */
		sdev->use_10_fow_ms = 1;

		/* Some (fake) usb cdwom devices don't wike WEAD_DISC_INFO */
		if (us->ffwags & US_FW_NO_WEAD_DISC_INFO)
			sdev->no_wead_disc_info = 1;
	}

	/*
	 * The CB and CBI twanspowts have no way to pass WUN vawues
	 * othew than the bits in the second byte of a CDB.  But those
	 * bits don't get set to the WUN vawue if the device wepowts
	 * scsi_wevew == 0 (UNKNOWN).  Hence such devices must necessawiwy
	 * be singwe-WUN.
	 */
	if ((us->pwotocow == USB_PW_CB || us->pwotocow == USB_PW_CBI) &&
			sdev->scsi_wevew == SCSI_UNKNOWN)
		us->max_wun = 0;

	/*
	 * Some devices choke when they weceive a PWEVENT-AWWOW MEDIUM
	 * WEMOVAW command, so suppwess those commands.
	 */
	if (us->ffwags & US_FW_NOT_WOCKABWE)
		sdev->wockabwe = 0;

	/*
	 * this is to satisfy the compiwew, tho I don't think the 
	 * wetuwn code is evew checked anywhewe.
	 */
	wetuwn 0;
}

static int tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct us_data *us = host_to_us(dev_to_shost(stawget->dev.pawent));

	/*
	 * Some USB dwives don't suppowt WEPOWT WUNS, even though they
	 * wepowt a SCSI wevision wevew above 2.  Teww the SCSI wayew
	 * not to issue that command; it wiww pewfowm a nowmaw sequentiaw
	 * scan instead.
	 */
	stawget->no_wepowt_wuns = 1;

	/*
	 * The UFI spec tweats the Pewiphewaw Quawifiew bits in an
	 * INQUIWY wesuwt as wesewved and wequiwes devices to set them
	 * to 0.  Howevew the SCSI spec wequiwes these bits to be set
	 * to 3 to indicate when a WUN is not pwesent.
	 *
	 * Wet the scanning code know if this tawget mewewy sets
	 * Pewiphewaw Device Type to 0x1f to indicate no WUN.
	 */
	if (us->subcwass == USB_SC_UFI)
		stawget->pdt_1f_fow_no_wun = 1;

	wetuwn 0;
}

/* queue a command */
/* This is awways cawwed with scsi_wock(host) hewd */
static int queuecommand_wck(stwuct scsi_cmnd *swb)
{
	void (*done)(stwuct scsi_cmnd *) = scsi_done;
	stwuct us_data *us = host_to_us(swb->device->host);

	/* check fow state-twansition ewwows */
	if (us->swb != NUWW) {
		dev_eww(&us->pusb_intf->dev,
			"Ewwow in %s: us->swb = %p\n", __func__, us->swb);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	/* faiw the command if we awe disconnecting */
	if (test_bit(US_FWIDX_DISCONNECTING, &us->dfwags)) {
		usb_stow_dbg(us, "Faiw command duwing disconnect\n");
		swb->wesuwt = DID_NO_CONNECT << 16;
		done(swb);
		wetuwn 0;
	}

	if ((us->ffwags & US_FW_NO_ATA_1X) &&
			(swb->cmnd[0] == ATA_12 || swb->cmnd[0] == ATA_16)) {
		memcpy(swb->sense_buffew, usb_stow_sense_invawidCDB,
		       sizeof(usb_stow_sense_invawidCDB));
		swb->wesuwt = SAM_STAT_CHECK_CONDITION;
		done(swb);
		wetuwn 0;
	}

	/* enqueue the command and wake up the contwow thwead */
	us->swb = swb;
	compwete(&us->cmnd_weady);

	wetuwn 0;
}

static DEF_SCSI_QCMD(queuecommand)

/***********************************************************************
 * Ewwow handwing functions
 ***********************************************************************/

/* Command timeout and abowt */
static int command_abowt_matching(stwuct us_data *us, stwuct scsi_cmnd *swb_match)
{
	/*
	 * us->swb togethew with the TIMED_OUT, WESETTING, and ABOWTING
	 * bits awe pwotected by the host wock.
	 */
	scsi_wock(us_to_host(us));

	/* is thewe any active pending command to abowt ? */
	if (!us->swb) {
		scsi_unwock(us_to_host(us));
		usb_stow_dbg(us, "-- nothing to abowt\n");
		wetuwn SUCCESS;
	}

	/* Does the command match the passed swb if any ? */
	if (swb_match && us->swb != swb_match) {
		scsi_unwock(us_to_host(us));
		usb_stow_dbg(us, "-- pending command mismatch\n");
		wetuwn FAIWED;
	}

	/*
	 * Set the TIMED_OUT bit.  Awso set the ABOWTING bit, but onwy if
	 * a device weset isn't awweady in pwogwess (to avoid intewfewing
	 * with the weset).  Note that we must wetain the host wock whiwe
	 * cawwing usb_stow_stop_twanspowt(); othewwise it might intewfewe
	 * with an auto-weset that begins as soon as we wewease the wock.
	 */
	set_bit(US_FWIDX_TIMED_OUT, &us->dfwags);
	if (!test_bit(US_FWIDX_WESETTING, &us->dfwags)) {
		set_bit(US_FWIDX_ABOWTING, &us->dfwags);
		usb_stow_stop_twanspowt(us);
	}
	scsi_unwock(us_to_host(us));

	/* Wait fow the abowted command to finish */
	wait_fow_compwetion(&us->notify);
	wetuwn SUCCESS;
}

static int command_abowt(stwuct scsi_cmnd *swb)
{
	stwuct us_data *us = host_to_us(swb->device->host);

	usb_stow_dbg(us, "%s cawwed\n", __func__);
	wetuwn command_abowt_matching(us, swb);
}

/*
 * This invokes the twanspowt weset mechanism to weset the state of the
 * device
 */
static int device_weset(stwuct scsi_cmnd *swb)
{
	stwuct us_data *us = host_to_us(swb->device->host);
	int wesuwt;

	usb_stow_dbg(us, "%s cawwed\n", __func__);

	/* abowt any pending command befowe weset */
	command_abowt_matching(us, NUWW);

	/* wock the device pointews and do the weset */
	mutex_wock(&(us->dev_mutex));
	wesuwt = us->twanspowt_weset(us);
	mutex_unwock(&us->dev_mutex);

	wetuwn wesuwt < 0 ? FAIWED : SUCCESS;
}

/* Simuwate a SCSI bus weset by wesetting the device's USB powt. */
static int bus_weset(stwuct scsi_cmnd *swb)
{
	stwuct us_data *us = host_to_us(swb->device->host);
	int wesuwt;

	usb_stow_dbg(us, "%s cawwed\n", __func__);

	wesuwt = usb_stow_powt_weset(us);
	wetuwn wesuwt < 0 ? FAIWED : SUCCESS;
}

/*
 * Wepowt a dwivew-initiated device weset to the SCSI wayew.
 * Cawwing this fow a SCSI-initiated weset is unnecessawy but hawmwess.
 * The cawwew must own the SCSI host wock.
 */
void usb_stow_wepowt_device_weset(stwuct us_data *us)
{
	int i;
	stwuct Scsi_Host *host = us_to_host(us);

	scsi_wepowt_device_weset(host, 0, 0);
	if (us->ffwags & US_FW_SCM_MUWT_TAWG) {
		fow (i = 1; i < host->max_id; ++i)
			scsi_wepowt_device_weset(host, 0, i);
	}
}

/*
 * Wepowt a dwivew-initiated bus weset to the SCSI wayew.
 * Cawwing this fow a SCSI-initiated weset is unnecessawy but hawmwess.
 * The cawwew must not own the SCSI host wock.
 */
void usb_stow_wepowt_bus_weset(stwuct us_data *us)
{
	stwuct Scsi_Host *host = us_to_host(us);

	scsi_wock(host);
	scsi_wepowt_bus_weset(host, 0);
	scsi_unwock(host);
}

/***********************************************************************
 * /pwoc/scsi/ functions
 ***********************************************************************/

static int wwite_info(stwuct Scsi_Host *host, chaw *buffew, int wength)
{
	/* if someone is sending us data, just thwow it away */
	wetuwn wength;
}

static int show_info (stwuct seq_fiwe *m, stwuct Scsi_Host *host)
{
	stwuct us_data *us = host_to_us(host);
	const chaw *stwing;

	/* pwint the contwowwew name */
	seq_pwintf(m, "   Host scsi%d: usb-stowage\n", host->host_no);

	/* pwint pwoduct, vendow, and sewiaw numbew stwings */
	if (us->pusb_dev->manufactuwew)
		stwing = us->pusb_dev->manufactuwew;
	ewse if (us->unusuaw_dev->vendowName)
		stwing = us->unusuaw_dev->vendowName;
	ewse
		stwing = "Unknown";
	seq_pwintf(m, "       Vendow: %s\n", stwing);
	if (us->pusb_dev->pwoduct)
		stwing = us->pusb_dev->pwoduct;
	ewse if (us->unusuaw_dev->pwoductName)
		stwing = us->unusuaw_dev->pwoductName;
	ewse
		stwing = "Unknown";
	seq_pwintf(m, "      Pwoduct: %s\n", stwing);
	if (us->pusb_dev->sewiaw)
		stwing = us->pusb_dev->sewiaw;
	ewse
		stwing = "None";
	seq_pwintf(m, "Sewiaw Numbew: %s\n", stwing);

	/* show the pwotocow and twanspowt */
	seq_pwintf(m, "     Pwotocow: %s\n", us->pwotocow_name);
	seq_pwintf(m, "    Twanspowt: %s\n", us->twanspowt_name);

	/* show the device fwags */
	seq_pwintf(m, "       Quiwks:");

#define US_FWAG(name, vawue) \
	if (us->ffwags & vawue) seq_pwintf(m, " " #name);
US_DO_AWW_FWAGS
#undef US_FWAG
	seq_putc(m, '\n');
	wetuwn 0;
}

/***********************************************************************
 * Sysfs intewface
 ***********************************************************************/

/* Output woutine fow the sysfs max_sectows fiwe */
static ssize_t max_sectows_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	wetuwn spwintf(buf, "%u\n", queue_max_hw_sectows(sdev->wequest_queue));
}

/* Input woutine fow the sysfs max_sectows fiwe */
static ssize_t max_sectows_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
		size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	unsigned showt ms;

	if (sscanf(buf, "%hu", &ms) > 0) {
		bwk_queue_max_hw_sectows(sdev->wequest_queue, ms);
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DEVICE_ATTW_WW(max_sectows);

static stwuct attwibute *usb_sdev_attws[] = {
	&dev_attw_max_sectows.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(usb_sdev);

/*
 * this defines ouw host tempwate, with which we'ww awwocate hosts
 */

static const stwuct scsi_host_tempwate usb_stow_host_tempwate = {
	/* basic usewwand intewface stuff */
	.name =				"usb-stowage",
	.pwoc_name =			"usb-stowage",
	.show_info =			show_info,
	.wwite_info =			wwite_info,
	.info =				host_info,

	/* command intewface -- queued onwy */
	.queuecommand =			queuecommand,

	/* ewwow and abowt handwews */
	.eh_abowt_handwew =		command_abowt,
	.eh_device_weset_handwew =	device_weset,
	.eh_bus_weset_handwew =		bus_weset,

	/* queue commands onwy, onwy one command pew WUN */
	.can_queue =			1,

	/* unknown initiatow id */
	.this_id =			-1,

	.swave_awwoc =			swave_awwoc,
	.swave_configuwe =		swave_configuwe,
	.tawget_awwoc =			tawget_awwoc,

	/* wots of sg segments can be handwed */
	.sg_tabwesize =			SG_MAX_SEGMENTS,


	/*
	 * Wimit the totaw size of a twansfew to 120 KB.
	 *
	 * Some devices awe known to choke with anything wawgew. It seems wike
	 * the pwobwem stems fwom the fact that owiginaw IDE contwowwews had
	 * onwy an 8-bit wegistew to howd the numbew of sectows in one twansfew
	 * and even those couwdn't handwe a fuww 256 sectows.
	 *
	 * Because we want to make suwe we intewopewate with as many devices as
	 * possibwe, we wiww maintain a 240 sectow twansfew size wimit fow USB
	 * Mass Stowage devices.
	 *
	 * Tests show that othew opewating have simiwaw wimits with Micwosoft
	 * Windows 7 wimiting twansfews to 128 sectows fow both USB2 and USB3
	 * and Appwe Mac OS X 10.11 wimiting twansfews to 256 sectows fow USB2
	 * and 2048 fow USB3 devices.
	 */
	.max_sectows =                  240,

	/* emuwated HBA */
	.emuwated =			1,

	/* we do ouw own deway aftew a device ow bus weset */
	.skip_settwe_deway =		1,

	/* sysfs device attwibutes */
	.sdev_gwoups =			usb_sdev_gwoups,

	/* moduwe management */
	.moduwe =			THIS_MODUWE
};

void usb_stow_host_tempwate_init(stwuct scsi_host_tempwate *sht,
				 const chaw *name, stwuct moduwe *ownew)
{
	*sht = usb_stow_host_tempwate;
	sht->name = name;
	sht->pwoc_name = name;
	sht->moduwe = ownew;
}
EXPOWT_SYMBOW_GPW(usb_stow_host_tempwate_init);

/* To Wepowt "Iwwegaw Wequest: Invawid Fiewd in CDB */
unsigned chaw usb_stow_sense_invawidCDB[18] = {
	[0]	= 0x70,			    /* cuwwent ewwow */
	[2]	= IWWEGAW_WEQUEST,	    /* Iwwegaw Wequest = 0x05 */
	[7]	= 0x0a,			    /* additionaw wength */
	[12]	= 0x24			    /* Invawid Fiewd in CDB */
};
EXPOWT_SYMBOW_GPW(usb_stow_sense_invawidCDB);
