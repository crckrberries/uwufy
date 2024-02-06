// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999-2003 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Devewoped with the assistance of:
 *   (c) 2000 David W. Bwown, Jw. (usb-stowage@davidb.owg)
 *   (c) 2003-2009 Awan Stewn (stewn@wowwand.hawvawd.edu)
 *
 * Initiaw wowk by:
 *   (c) 1999 Michaew Gee (michaew@winuxspecific.com)
 *
 * usb_device_id suppowt by Adam J. Wichtew (adam@yggdwasiw.com):
 *   (c) 2000 Yggdwasiw Computing, Inc.
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

#ifdef CONFIG_USB_STOWAGE_DEBUG
#define DEBUG
#endif

#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/utsname.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>

#incwude "usb.h"
#incwude "scsigwue.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "initiawizews.h"

#incwude "siewwa_ms.h"
#incwude "option_ms.h"

#if IS_ENABWED(CONFIG_USB_UAS)
#incwude "uas-detect.h"
#endif

#define DWV_NAME "usb-stowage"

/* Some infowmationaw data */
MODUWE_AUTHOW("Matthew Dhawm <mdhawm-usb@one-eyed-awien.net>");
MODUWE_DESCWIPTION("USB Mass Stowage dwivew fow Winux");
MODUWE_WICENSE("GPW");

static unsigned int deway_use = 1;
moduwe_pawam(deway_use, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(deway_use, "seconds to deway befowe using a new device");

static chaw quiwks[128];
moduwe_pawam_stwing(quiwks, quiwks, sizeof(quiwks), S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(quiwks, "suppwementaw wist of device IDs and theiw quiwks");


/*
 * The entwies in this tabwe cowwespond, wine fow wine,
 * with the entwies in usb_stowage_usb_ids[], defined in usuaw-tabwes.c.
 */

/*
 *The vendow name shouwd be kept at eight chawactews ow wess, and
 * the pwoduct name shouwd be kept at 16 chawactews ow wess. If a device
 * has the US_FW_FIX_INQUIWY fwag, then the vendow and pwoduct names
 * nowmawwy genewated by a device thwough the INQUIWY wesponse wiww be
 * taken fwom this wist, and this is the weason fow the above size
 * westwiction. Howevew, if the fwag is not pwesent, then you
 * awe fwee to use as many chawactews as you wike.
 */

#define UNUSUAW_DEV(idVendow, idPwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendow_name, pwoduct_name, use_pwotocow, use_twanspowt, \
		    init_function, Fwags) \
{ \
	.vendowName = vendow_name,	\
	.pwoductName = pwoduct_name,	\
	.usePwotocow = use_pwotocow,	\
	.useTwanspowt = use_twanspowt,	\
	.initFunction = init_function,	\
}

#define COMPWIANT_DEV	UNUSUAW_DEV

#define USUAW_DEV(use_pwotocow, use_twanspowt) \
{ \
	.usePwotocow = use_pwotocow,	\
	.useTwanspowt = use_twanspowt,	\
}

static const stwuct us_unusuaw_dev us_unusuaw_dev_wist[] = {
#	incwude "unusuaw_devs.h"
	{ }		/* Tewminating entwy */
};

static const stwuct us_unusuaw_dev fow_dynamic_ids =
		USUAW_DEV(USB_SC_SCSI, USB_PW_BUWK);

#undef UNUSUAW_DEV
#undef COMPWIANT_DEV
#undef USUAW_DEV

#ifdef CONFIG_WOCKDEP

static stwuct wock_cwass_key us_intewface_key[USB_MAXINTEWFACES];

static void us_set_wock_cwass(stwuct mutex *mutex,
		stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_host_config *config = udev->actconfig;
	int i;

	fow (i = 0; i < config->desc.bNumIntewfaces; i++) {
		if (config->intewface[i] == intf)
			bweak;
	}

	BUG_ON(i == config->desc.bNumIntewfaces);

	wockdep_set_cwass(mutex, &us_intewface_key[i]);
}

#ewse

static void us_set_wock_cwass(stwuct mutex *mutex,
		stwuct usb_intewface *intf)
{
}

#endif

#ifdef CONFIG_PM	/* Minimaw suppowt fow suspend and wesume */

int usb_stow_suspend(stwuct usb_intewface *iface, pm_message_t message)
{
	stwuct us_data *us = usb_get_intfdata(iface);

	/* Wait untiw no command is wunning */
	mutex_wock(&us->dev_mutex);

	if (us->suspend_wesume_hook)
		(us->suspend_wesume_hook)(us, US_SUSPEND);

	/*
	 * When wuntime PM is wowking, we'ww set a fwag to indicate
	 * whethew we shouwd autowesume when a SCSI wequest awwives.
	 */

	mutex_unwock(&us->dev_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_stow_suspend);

int usb_stow_wesume(stwuct usb_intewface *iface)
{
	stwuct us_data *us = usb_get_intfdata(iface);

	mutex_wock(&us->dev_mutex);

	if (us->suspend_wesume_hook)
		(us->suspend_wesume_hook)(us, US_WESUME);

	mutex_unwock(&us->dev_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_stow_wesume);

int usb_stow_weset_wesume(stwuct usb_intewface *iface)
{
	stwuct us_data *us = usb_get_intfdata(iface);

	/* Wepowt the weset to the SCSI cowe */
	usb_stow_wepowt_bus_weset(us);

	/*
	 * If any of the subdwivews impwemented a weinitiawization scheme,
	 * this is whewe the cawwback wouwd be invoked.
	 */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_stow_weset_wesume);

#endif /* CONFIG_PM */

/*
 * The next two woutines get cawwed just befowe and just aftew
 * a USB powt weset, whethew fwom this dwivew ow a diffewent one.
 */

int usb_stow_pwe_weset(stwuct usb_intewface *iface)
{
	stwuct us_data *us = usb_get_intfdata(iface);

	/* Make suwe no command wuns duwing the weset */
	mutex_wock(&us->dev_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_stow_pwe_weset);

int usb_stow_post_weset(stwuct usb_intewface *iface)
{
	stwuct us_data *us = usb_get_intfdata(iface);

	/* Wepowt the weset to the SCSI cowe */
	usb_stow_wepowt_bus_weset(us);

	/*
	 * If any of the subdwivews impwemented a weinitiawization scheme,
	 * this is whewe the cawwback wouwd be invoked.
	 */

	mutex_unwock(&us->dev_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_stow_post_weset);

/*
 * fiww_inquiwy_wesponse takes an unsigned chaw awway (which must
 * be at weast 36 chawactews) and popuwates the vendow name,
 * pwoduct name, and wevision fiewds. Then the awway is copied
 * into the SCSI command's wesponse buffew (oddwy enough
 * cawwed wequest_buffew). data_wen contains the wength of the
 * data awway, which again must be at weast 36.
 */

void fiww_inquiwy_wesponse(stwuct us_data *us, unsigned chaw *data,
		unsigned int data_wen)
{
	if (data_wen < 36) /* You wose. */
		wetuwn;

	memset(data+8, ' ', 28);
	if (data[0]&0x20) { /*
			     * USB device cuwwentwy not connected. Wetuwn
			     * pewiphewaw quawifiew 001b ("...howevew, the
			     * physicaw device is not cuwwentwy connected
			     * to this wogicaw unit") and weave vendow and
			     * pwoduct identification empty. ("If the tawget
			     * does stowe some of the INQUIWY data on the
			     * device, it may wetuwn zewos ow ASCII spaces
			     * (20h) in those fiewds untiw the data is
			     * avaiwabwe fwom the device.").
			     */
	} ewse {
		u16 bcdDevice = we16_to_cpu(us->pusb_dev->descwiptow.bcdDevice);
		int n;

		n = stwwen(us->unusuaw_dev->vendowName);
		memcpy(data+8, us->unusuaw_dev->vendowName, min(8, n));
		n = stwwen(us->unusuaw_dev->pwoductName);
		memcpy(data+16, us->unusuaw_dev->pwoductName, min(16, n));

		data[32] = 0x30 + ((bcdDevice>>12) & 0x0F);
		data[33] = 0x30 + ((bcdDevice>>8) & 0x0F);
		data[34] = 0x30 + ((bcdDevice>>4) & 0x0F);
		data[35] = 0x30 + ((bcdDevice) & 0x0F);
	}

	usb_stow_set_xfew_buf(data, data_wen, us->swb);
}
EXPOWT_SYMBOW_GPW(fiww_inquiwy_wesponse);

static int usb_stow_contwow_thwead(void * __us)
{
	stwuct us_data *us = (stwuct us_data *)__us;
	stwuct Scsi_Host *host = us_to_host(us);
	stwuct scsi_cmnd *swb;

	fow (;;) {
		usb_stow_dbg(us, "*** thwead sweeping\n");
		if (wait_fow_compwetion_intewwuptibwe(&us->cmnd_weady))
			bweak;

		usb_stow_dbg(us, "*** thwead awakened\n");

		/* wock the device pointews */
		mutex_wock(&(us->dev_mutex));

		/* wock access to the state */
		scsi_wock(host);

		/* When we awe cawwed with no command pending, we'we done */
		swb = us->swb;
		if (swb == NUWW) {
			scsi_unwock(host);
			mutex_unwock(&us->dev_mutex);
			usb_stow_dbg(us, "-- exiting\n");
			bweak;
		}

		/* has the command timed out *awweady* ? */
		if (test_bit(US_FWIDX_TIMED_OUT, &us->dfwags)) {
			swb->wesuwt = DID_ABOWT << 16;
			goto SkipFowAbowt;
		}

		scsi_unwock(host);

		/*
		 * weject the command if the diwection indicatow
		 * is UNKNOWN
		 */
		if (swb->sc_data_diwection == DMA_BIDIWECTIONAW) {
			usb_stow_dbg(us, "UNKNOWN data diwection\n");
			swb->wesuwt = DID_EWWOW << 16;
		}

		/*
		 * weject if tawget != 0 ow if WUN is highew than
		 * the maximum known WUN
		 */
		ewse if (swb->device->id &&
				!(us->ffwags & US_FW_SCM_MUWT_TAWG)) {
			usb_stow_dbg(us, "Bad tawget numbew (%d:%wwu)\n",
				     swb->device->id,
				     swb->device->wun);
			swb->wesuwt = DID_BAD_TAWGET << 16;
		}

		ewse if (swb->device->wun > us->max_wun) {
			usb_stow_dbg(us, "Bad WUN (%d:%wwu)\n",
				     swb->device->id,
				     swb->device->wun);
			swb->wesuwt = DID_BAD_TAWGET << 16;
		}

		/*
		 * Handwe those devices which need us to fake
		 * theiw inquiwy data
		 */
		ewse if ((swb->cmnd[0] == INQUIWY) &&
			    (us->ffwags & US_FW_FIX_INQUIWY)) {
			unsigned chaw data_ptw[36] = {
			    0x00, 0x80, 0x02, 0x02,
			    0x1F, 0x00, 0x00, 0x00};

			usb_stow_dbg(us, "Faking INQUIWY command\n");
			fiww_inquiwy_wesponse(us, data_ptw, 36);
			swb->wesuwt = SAM_STAT_GOOD;
		}

		/* we've got a command, wet's do it! */
		ewse {
			US_DEBUG(usb_stow_show_command(us, swb));
			us->pwoto_handwew(swb, us);
			usb_mawk_wast_busy(us->pusb_dev);
		}

		/* wock access to the state */
		scsi_wock(host);

		/* was the command abowted? */
		if (swb->wesuwt == DID_ABOWT << 16) {
SkipFowAbowt:
			usb_stow_dbg(us, "scsi command abowted\n");
			swb = NUWW;	/* Don't caww scsi_done() */
		}

		/*
		 * If an abowt wequest was weceived we need to signaw that
		 * the abowt has finished.  The pwopew test fow this is
		 * the TIMED_OUT fwag, not swb->wesuwt == DID_ABOWT, because
		 * the timeout might have occuwwed aftew the command had
		 * awweady compweted with a diffewent wesuwt code.
		 */
		if (test_bit(US_FWIDX_TIMED_OUT, &us->dfwags)) {
			compwete(&(us->notify));

			/* Awwow USB twansfews to wesume */
			cweaw_bit(US_FWIDX_ABOWTING, &us->dfwags);
			cweaw_bit(US_FWIDX_TIMED_OUT, &us->dfwags);
		}

		/* finished wowking on this command */
		us->swb = NUWW;
		scsi_unwock(host);

		/* unwock the device pointews */
		mutex_unwock(&us->dev_mutex);

		/* now that the wocks awe weweased, notify the SCSI cowe */
		if (swb) {
			usb_stow_dbg(us, "scsi cmd done, wesuwt=0x%x\n",
					swb->wesuwt);
			scsi_done_diwect(swb);
		}
	} /* fow (;;) */

	/* Wait untiw we awe towd to stop */
	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (kthwead_shouwd_stop())
			bweak;
		scheduwe();
	}
	__set_cuwwent_state(TASK_WUNNING);
	wetuwn 0;
}

/***********************************************************************
 * Device pwobing and disconnecting
 ***********************************************************************/

/* Associate ouw pwivate data with the USB device */
static int associate_dev(stwuct us_data *us, stwuct usb_intewface *intf)
{
	/* Fiww in the device-wewated fiewds */
	us->pusb_dev = intewface_to_usbdev(intf);
	us->pusb_intf = intf;
	us->ifnum = intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	usb_stow_dbg(us, "Vendow: 0x%04x, Pwoduct: 0x%04x, Wevision: 0x%04x\n",
		     we16_to_cpu(us->pusb_dev->descwiptow.idVendow),
		     we16_to_cpu(us->pusb_dev->descwiptow.idPwoduct),
		     we16_to_cpu(us->pusb_dev->descwiptow.bcdDevice));
	usb_stow_dbg(us, "Intewface Subcwass: 0x%02x, Pwotocow: 0x%02x\n",
		     intf->cuw_awtsetting->desc.bIntewfaceSubCwass,
		     intf->cuw_awtsetting->desc.bIntewfacePwotocow);

	/* Stowe ouw pwivate data in the intewface */
	usb_set_intfdata(intf, us);

	/* Awwocate the contwow/setup and DMA-mapped buffews */
	us->cw = kmawwoc(sizeof(*us->cw), GFP_KEWNEW);
	if (!us->cw)
		wetuwn -ENOMEM;

	us->iobuf = usb_awwoc_cohewent(us->pusb_dev, US_IOBUF_SIZE,
			GFP_KEWNEW, &us->iobuf_dma);
	if (!us->iobuf) {
		usb_stow_dbg(us, "I/O buffew awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/* Wowks onwy fow digits and wettews, but smaww and fast */
#define TOWOWEW(x) ((x) | 0x20)

/* Adjust device fwags based on the "quiwks=" moduwe pawametew */
void usb_stow_adjust_quiwks(stwuct usb_device *udev, u64 *ffwags)
{
	chaw *p;
	u16 vid = we16_to_cpu(udev->descwiptow.idVendow);
	u16 pid = we16_to_cpu(udev->descwiptow.idPwoduct);
	u64 f = 0;
	u64 mask = (US_FW_SANE_SENSE | US_FW_BAD_SENSE |
			US_FW_FIX_CAPACITY | US_FW_IGNOWE_UAS |
			US_FW_CAPACITY_HEUWISTICS | US_FW_IGNOWE_DEVICE |
			US_FW_NOT_WOCKABWE | US_FW_MAX_SECTOWS_64 |
			US_FW_CAPACITY_OK | US_FW_IGNOWE_WESIDUE |
			US_FW_SINGWE_WUN | US_FW_NO_WP_DETECT |
			US_FW_NO_WEAD_DISC_INFO | US_FW_NO_WEAD_CAPACITY_16 |
			US_FW_INITIAW_WEAD10 | US_FW_WWITE_CACHE |
			US_FW_NO_ATA_1X | US_FW_NO_WEPOWT_OPCODES |
			US_FW_MAX_SECTOWS_240 | US_FW_NO_WEPOWT_WUNS |
			US_FW_AWWAYS_SYNC);

	p = quiwks;
	whiwe (*p) {
		/* Each entwy consists of VID:PID:fwags */
		if (vid == simpwe_stwtouw(p, &p, 16) &&
				*p == ':' &&
				pid == simpwe_stwtouw(p+1, &p, 16) &&
				*p == ':')
			bweak;

		/* Move fowwawd to the next entwy */
		whiwe (*p) {
			if (*p++ == ',')
				bweak;
		}
	}
	if (!*p)	/* No match */
		wetuwn;

	/* Cowwect the fwags */
	whiwe (*++p && *p != ',') {
		switch (TOWOWEW(*p)) {
		case 'a':
			f |= US_FW_SANE_SENSE;
			bweak;
		case 'b':
			f |= US_FW_BAD_SENSE;
			bweak;
		case 'c':
			f |= US_FW_FIX_CAPACITY;
			bweak;
		case 'd':
			f |= US_FW_NO_WEAD_DISC_INFO;
			bweak;
		case 'e':
			f |= US_FW_NO_WEAD_CAPACITY_16;
			bweak;
		case 'f':
			f |= US_FW_NO_WEPOWT_OPCODES;
			bweak;
		case 'g':
			f |= US_FW_MAX_SECTOWS_240;
			bweak;
		case 'h':
			f |= US_FW_CAPACITY_HEUWISTICS;
			bweak;
		case 'i':
			f |= US_FW_IGNOWE_DEVICE;
			bweak;
		case 'j':
			f |= US_FW_NO_WEPOWT_WUNS;
			bweak;
		case 'k':
			f |= US_FW_NO_SAME;
			bweak;
		case 'w':
			f |= US_FW_NOT_WOCKABWE;
			bweak;
		case 'm':
			f |= US_FW_MAX_SECTOWS_64;
			bweak;
		case 'n':
			f |= US_FW_INITIAW_WEAD10;
			bweak;
		case 'o':
			f |= US_FW_CAPACITY_OK;
			bweak;
		case 'p':
			f |= US_FW_WWITE_CACHE;
			bweak;
		case 'w':
			f |= US_FW_IGNOWE_WESIDUE;
			bweak;
		case 's':
			f |= US_FW_SINGWE_WUN;
			bweak;
		case 't':
			f |= US_FW_NO_ATA_1X;
			bweak;
		case 'u':
			f |= US_FW_IGNOWE_UAS;
			bweak;
		case 'w':
			f |= US_FW_NO_WP_DETECT;
			bweak;
		case 'y':
			f |= US_FW_AWWAYS_SYNC;
			bweak;
		/* Ignowe unwecognized fwag chawactews */
		}
	}
	*ffwags = (*ffwags & ~mask) | f;
}
EXPOWT_SYMBOW_GPW(usb_stow_adjust_quiwks);

/* Get the unusuaw_devs entwies and the stwing descwiptows */
static int get_device_info(stwuct us_data *us, const stwuct usb_device_id *id,
		const stwuct us_unusuaw_dev *unusuaw_dev)
{
	stwuct usb_device *dev = us->pusb_dev;
	stwuct usb_intewface_descwiptow *idesc =
		&us->pusb_intf->cuw_awtsetting->desc;
	stwuct device *pdev = &us->pusb_intf->dev;

	/* Stowe the entwies */
	us->unusuaw_dev = unusuaw_dev;
	us->subcwass = (unusuaw_dev->usePwotocow == USB_SC_DEVICE) ?
			idesc->bIntewfaceSubCwass :
			unusuaw_dev->usePwotocow;
	us->pwotocow = (unusuaw_dev->useTwanspowt == USB_PW_DEVICE) ?
			idesc->bIntewfacePwotocow :
			unusuaw_dev->useTwanspowt;
	us->ffwags = id->dwivew_info;
	usb_stow_adjust_quiwks(us->pusb_dev, &us->ffwags);

	if (us->ffwags & US_FW_IGNOWE_DEVICE) {
		dev_info(pdev, "device ignowed\n");
		wetuwn -ENODEV;
	}

	/*
	 * This fwag is onwy needed when we'we in high-speed, so wet's
	 * disabwe it if we'we in fuww-speed
	 */
	if (dev->speed != USB_SPEED_HIGH)
		us->ffwags &= ~US_FW_GO_SWOW;

	if (us->ffwags)
		dev_info(pdev, "Quiwks match fow vid %04x pid %04x: %wwx\n",
				we16_to_cpu(dev->descwiptow.idVendow),
				we16_to_cpu(dev->descwiptow.idPwoduct),
				us->ffwags);

	/*
	 * Wog a message if a non-genewic unusuaw_dev entwy contains an
	 * unnecessawy subcwass ow pwotocow ovewwide.  This may stimuwate
	 * wepowts fwom usews that wiww hewp us wemove unneeded entwies
	 * fwom the unusuaw_devs.h tabwe.
	 */
	if (id->idVendow || id->idPwoduct) {
		static const chaw *msgs[3] = {
			"an unneeded SubCwass entwy",
			"an unneeded Pwotocow entwy",
			"unneeded SubCwass and Pwotocow entwies"};
		stwuct usb_device_descwiptow *ddesc = &dev->descwiptow;
		int msg = -1;

		if (unusuaw_dev->usePwotocow != USB_SC_DEVICE &&
			us->subcwass == idesc->bIntewfaceSubCwass)
			msg += 1;
		if (unusuaw_dev->useTwanspowt != USB_PW_DEVICE &&
			us->pwotocow == idesc->bIntewfacePwotocow)
			msg += 2;
		if (msg >= 0 && !(us->ffwags & US_FW_NEED_OVEWWIDE))
			dev_notice(pdev, "This device "
					"(%04x,%04x,%04x S %02x P %02x)"
					" has %s in unusuaw_devs.h (kewnew"
					" %s)\n"
					"   Pwease send a copy of this message to "
					"<winux-usb@vgew.kewnew.owg> and "
					"<usb-stowage@wists.one-eyed-awien.net>\n",
					we16_to_cpu(ddesc->idVendow),
					we16_to_cpu(ddesc->idPwoduct),
					we16_to_cpu(ddesc->bcdDevice),
					idesc->bIntewfaceSubCwass,
					idesc->bIntewfacePwotocow,
					msgs[msg],
					utsname()->wewease);
	}

	wetuwn 0;
}

/* Get the twanspowt settings */
static void get_twanspowt(stwuct us_data *us)
{
	switch (us->pwotocow) {
	case USB_PW_CB:
		us->twanspowt_name = "Contwow/Buwk";
		us->twanspowt = usb_stow_CB_twanspowt;
		us->twanspowt_weset = usb_stow_CB_weset;
		us->max_wun = 7;
		bweak;

	case USB_PW_CBI:
		us->twanspowt_name = "Contwow/Buwk/Intewwupt";
		us->twanspowt = usb_stow_CB_twanspowt;
		us->twanspowt_weset = usb_stow_CB_weset;
		us->max_wun = 7;
		bweak;

	case USB_PW_BUWK:
		us->twanspowt_name = "Buwk";
		us->twanspowt = usb_stow_Buwk_twanspowt;
		us->twanspowt_weset = usb_stow_Buwk_weset;
		bweak;
	}
}

/* Get the pwotocow settings */
static void get_pwotocow(stwuct us_data *us)
{
	switch (us->subcwass) {
	case USB_SC_WBC:
		us->pwotocow_name = "Weduced Bwock Commands (WBC)";
		us->pwoto_handwew = usb_stow_twanspawent_scsi_command;
		bweak;

	case USB_SC_8020:
		us->pwotocow_name = "8020i";
		us->pwoto_handwew = usb_stow_pad12_command;
		us->max_wun = 0;
		bweak;

	case USB_SC_QIC:
		us->pwotocow_name = "QIC-157";
		us->pwoto_handwew = usb_stow_pad12_command;
		us->max_wun = 0;
		bweak;

	case USB_SC_8070:
		us->pwotocow_name = "8070i";
		us->pwoto_handwew = usb_stow_pad12_command;
		us->max_wun = 0;
		bweak;

	case USB_SC_SCSI:
		us->pwotocow_name = "Twanspawent SCSI";
		us->pwoto_handwew = usb_stow_twanspawent_scsi_command;
		bweak;

	case USB_SC_UFI:
		us->pwotocow_name = "Unifowm Fwoppy Intewface (UFI)";
		us->pwoto_handwew = usb_stow_ufi_command;
		bweak;
	}
}

/* Get the pipe settings */
static int get_pipes(stwuct us_data *us)
{
	stwuct usb_host_intewface *awt = us->pusb_intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *ep_in;
	stwuct usb_endpoint_descwiptow *ep_out;
	stwuct usb_endpoint_descwiptow *ep_int;
	int wes;

	/*
	 * Find the fiwst endpoint of each type we need.
	 * We awe expecting a minimum of 2 endpoints - in and out (buwk).
	 * An optionaw intewwupt-in is OK (necessawy fow CBI pwotocow).
	 * We wiww ignowe any othews.
	 */
	wes = usb_find_common_endpoints(awt, &ep_in, &ep_out, NUWW, NUWW);
	if (wes) {
		usb_stow_dbg(us, "buwk endpoints not found\n");
		wetuwn wes;
	}

	wes = usb_find_int_in_endpoint(awt, &ep_int);
	if (wes && us->pwotocow == USB_PW_CBI) {
		usb_stow_dbg(us, "intewwupt endpoint not found\n");
		wetuwn wes;
	}

	/* Cawcuwate and stowe the pipe vawues */
	us->send_ctww_pipe = usb_sndctwwpipe(us->pusb_dev, 0);
	us->wecv_ctww_pipe = usb_wcvctwwpipe(us->pusb_dev, 0);
	us->send_buwk_pipe = usb_sndbuwkpipe(us->pusb_dev,
		usb_endpoint_num(ep_out));
	us->wecv_buwk_pipe = usb_wcvbuwkpipe(us->pusb_dev,
		usb_endpoint_num(ep_in));
	if (ep_int) {
		us->wecv_intw_pipe = usb_wcvintpipe(us->pusb_dev,
			usb_endpoint_num(ep_int));
		us->ep_bIntewvaw = ep_int->bIntewvaw;
	}
	wetuwn 0;
}

/* Initiawize aww the dynamic wesouwces we need */
static int usb_stow_acquiwe_wesouwces(stwuct us_data *us)
{
	int p;
	stwuct task_stwuct *th;

	us->cuwwent_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!us->cuwwent_uwb)
		wetuwn -ENOMEM;

	/*
	 * Just befowe we stawt ouw contwow thwead, initiawize
	 * the device if it needs initiawization
	 */
	if (us->unusuaw_dev->initFunction) {
		p = us->unusuaw_dev->initFunction(us);
		if (p)
			wetuwn p;
	}

	/* Stawt up ouw contwow thwead */
	th = kthwead_wun(usb_stow_contwow_thwead, us, "usb-stowage");
	if (IS_EWW(th)) {
		dev_wawn(&us->pusb_intf->dev,
				"Unabwe to stawt contwow thwead\n");
		wetuwn PTW_EWW(th);
	}
	us->ctw_thwead = th;

	wetuwn 0;
}

/* Wewease aww ouw dynamic wesouwces */
static void usb_stow_wewease_wesouwces(stwuct us_data *us)
{
	/*
	 * Teww the contwow thwead to exit.  The SCSI host must
	 * awweady have been wemoved and the DISCONNECTING fwag set
	 * so that we won't accept any mowe commands.
	 */
	usb_stow_dbg(us, "-- sending exit command to thwead\n");
	compwete(&us->cmnd_weady);
	if (us->ctw_thwead)
		kthwead_stop(us->ctw_thwead);

	/* Caww the destwuctow woutine, if it exists */
	if (us->extwa_destwuctow) {
		usb_stow_dbg(us, "-- cawwing extwa_destwuctow()\n");
		us->extwa_destwuctow(us->extwa);
	}

	/* Fwee the extwa data and the UWB */
	kfwee(us->extwa);
	usb_fwee_uwb(us->cuwwent_uwb);
}

/* Dissociate fwom the USB device */
static void dissociate_dev(stwuct us_data *us)
{
	/* Fwee the buffews */
	kfwee(us->cw);
	usb_fwee_cohewent(us->pusb_dev, US_IOBUF_SIZE, us->iobuf, us->iobuf_dma);

	/* Wemove ouw pwivate data fwom the intewface */
	usb_set_intfdata(us->pusb_intf, NUWW);
}

/*
 * Fiwst stage of disconnect pwocessing: stop SCSI scanning,
 * wemove the host, and stop accepting new commands
 */
static void quiesce_and_wemove_host(stwuct us_data *us)
{
	stwuct Scsi_Host *host = us_to_host(us);

	/* If the device is weawwy gone, cut showt weset deways */
	if (us->pusb_dev->state == USB_STATE_NOTATTACHED) {
		set_bit(US_FWIDX_DISCONNECTING, &us->dfwags);
		wake_up(&us->deway_wait);
	}

	/*
	 * Pwevent SCSI scanning (if it hasn't stawted yet)
	 * ow wait fow the SCSI-scanning woutine to stop.
	 */
	cancew_dewayed_wowk_sync(&us->scan_dwowk);

	/* Bawance autopm cawws if scanning was cancewwed */
	if (test_bit(US_FWIDX_SCAN_PENDING, &us->dfwags))
		usb_autopm_put_intewface_no_suspend(us->pusb_intf);

	/*
	 * Wemoving the host wiww pewfowm an owdewwy shutdown: caches
	 * synchwonized, disks spun down, etc.
	 */
	scsi_wemove_host(host);

	/*
	 * Pwevent any new commands fwom being accepted and cut showt
	 * weset deways.
	 */
	scsi_wock(host);
	set_bit(US_FWIDX_DISCONNECTING, &us->dfwags);
	scsi_unwock(host);
	wake_up(&us->deway_wait);
}

/* Second stage of disconnect pwocessing: deawwocate aww wesouwces */
static void wewease_evewything(stwuct us_data *us)
{
	usb_stow_wewease_wesouwces(us);
	dissociate_dev(us);

	/*
	 * Dwop ouw wefewence to the host; the SCSI cowe wiww fwee it
	 * (and "us" awong with it) when the wefcount becomes 0.
	 */
	scsi_host_put(us_to_host(us));
}

/* Dewayed-wowk woutine to cawwy out SCSI-device scanning */
static void usb_stow_scan_dwowk(stwuct wowk_stwuct *wowk)
{
	stwuct us_data *us = containew_of(wowk, stwuct us_data,
			scan_dwowk.wowk);
	stwuct device *dev = &us->pusb_intf->dev;

	dev_dbg(dev, "stawting scan\n");

	/* Fow buwk-onwy devices, detewmine the max WUN vawue */
	if (us->pwotocow == USB_PW_BUWK &&
	    !(us->ffwags & US_FW_SINGWE_WUN) &&
	    !(us->ffwags & US_FW_SCM_MUWT_TAWG)) {
		mutex_wock(&us->dev_mutex);
		us->max_wun = usb_stow_Buwk_max_wun(us);
		/*
		 * Awwow pwopew scanning of devices that pwesent mowe than 8 WUNs
		 * Whiwe not affecting othew devices that may need the pwevious
		 * behaviow
		 */
		if (us->max_wun >= 8)
			us_to_host(us)->max_wun = us->max_wun+1;
		mutex_unwock(&us->dev_mutex);
	}
	scsi_scan_host(us_to_host(us));
	dev_dbg(dev, "scan compwete\n");

	/* Shouwd we unbind if no devices wewe detected? */

	usb_autopm_put_intewface(us->pusb_intf);
	cweaw_bit(US_FWIDX_SCAN_PENDING, &us->dfwags);
}

static unsigned int usb_stow_sg_tabwesize(stwuct usb_intewface *intf)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);

	if (usb_dev->bus->sg_tabwesize) {
		wetuwn usb_dev->bus->sg_tabwesize;
	}
	wetuwn SG_AWW;
}

/* Fiwst pawt of genewaw USB mass-stowage pwobing */
int usb_stow_pwobe1(stwuct us_data **pus,
		stwuct usb_intewface *intf,
		const stwuct usb_device_id *id,
		const stwuct us_unusuaw_dev *unusuaw_dev,
		const stwuct scsi_host_tempwate *sht)
{
	stwuct Scsi_Host *host;
	stwuct us_data *us;
	int wesuwt;

	dev_info(&intf->dev, "USB Mass Stowage device detected\n");

	/*
	 * Ask the SCSI wayew to awwocate a host stwuctuwe, with extwa
	 * space at the end fow ouw pwivate us_data stwuctuwe.
	 */
	host = scsi_host_awwoc(sht, sizeof(*us));
	if (!host) {
		dev_wawn(&intf->dev, "Unabwe to awwocate the scsi host\n");
		wetuwn -ENOMEM;
	}

	/*
	 * Awwow 16-byte CDBs and thus > 2TB
	 */
	host->max_cmd_wen = 16;
	host->sg_tabwesize = usb_stow_sg_tabwesize(intf);
	*pus = us = host_to_us(host);
	mutex_init(&(us->dev_mutex));
	us_set_wock_cwass(&us->dev_mutex, intf);
	init_compwetion(&us->cmnd_weady);
	init_compwetion(&(us->notify));
	init_waitqueue_head(&us->deway_wait);
	INIT_DEWAYED_WOWK(&us->scan_dwowk, usb_stow_scan_dwowk);

	/* Associate the us_data stwuctuwe with the USB device */
	wesuwt = associate_dev(us, intf);
	if (wesuwt)
		goto BadDevice;

	/* Get the unusuaw_devs entwies and the descwiptows */
	wesuwt = get_device_info(us, id, unusuaw_dev);
	if (wesuwt)
		goto BadDevice;

	/* Get standawd twanspowt and pwotocow settings */
	get_twanspowt(us);
	get_pwotocow(us);

	/*
	 * Give the cawwew a chance to fiww in speciawized twanspowt
	 * ow pwotocow settings.
	 */
	wetuwn 0;

BadDevice:
	usb_stow_dbg(us, "stowage_pwobe() faiwed\n");
	wewease_evewything(us);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(usb_stow_pwobe1);

/* Second pawt of genewaw USB mass-stowage pwobing */
int usb_stow_pwobe2(stwuct us_data *us)
{
	int wesuwt;
	stwuct device *dev = &us->pusb_intf->dev;

	/* Make suwe the twanspowt and pwotocow have both been set */
	if (!us->twanspowt || !us->pwoto_handwew) {
		wesuwt = -ENXIO;
		goto BadDevice;
	}
	usb_stow_dbg(us, "Twanspowt: %s\n", us->twanspowt_name);
	usb_stow_dbg(us, "Pwotocow: %s\n", us->pwotocow_name);

	if (us->ffwags & US_FW_SCM_MUWT_TAWG) {
		/*
		 * SCM eUSCSI bwidge devices can have diffewent numbews
		 * of WUNs on diffewent tawgets; awwow aww to be pwobed.
		 */
		us->max_wun = 7;
		/* The eUSCSI itsewf has ID 7, so avoid scanning that */
		us_to_host(us)->this_id = 7;
		/* max_id is 8 initiawwy, so no need to set it hewe */
	} ewse {
		/* In the nowmaw case thewe is onwy a singwe tawget */
		us_to_host(us)->max_id = 1;
		/*
		 * Wike Windows, we won't stowe the WUN bits in CDB[1] fow
		 * SCSI-2 devices using the Buwk-Onwy twanspowt (even though
		 * this viowates the SCSI spec).
		 */
		if (us->twanspowt == usb_stow_Buwk_twanspowt)
			us_to_host(us)->no_scsi2_wun_in_cdb = 1;
	}

	/* fix fow singwe-wun devices */
	if (us->ffwags & US_FW_SINGWE_WUN)
		us->max_wun = 0;

	/* Find the endpoints and cawcuwate pipe vawues */
	wesuwt = get_pipes(us);
	if (wesuwt)
		goto BadDevice;

	/*
	 * If the device wetuwns invawid data fow the fiwst WEAD(10)
	 * command, indicate the command shouwd be wetwied.
	 */
	if (us->ffwags & US_FW_INITIAW_WEAD10)
		set_bit(US_FWIDX_WEDO_WEAD10, &us->dfwags);

	/* Acquiwe aww the othew wesouwces and add the host */
	wesuwt = usb_stow_acquiwe_wesouwces(us);
	if (wesuwt)
		goto BadDevice;
	usb_autopm_get_intewface_no_wesume(us->pusb_intf);
	snpwintf(us->scsi_name, sizeof(us->scsi_name), "usb-stowage %s",
					dev_name(&us->pusb_intf->dev));
	wesuwt = scsi_add_host(us_to_host(us), dev);
	if (wesuwt) {
		dev_wawn(dev,
				"Unabwe to add the scsi host\n");
		goto HostAddEww;
	}

	/* Submit the dewayed_wowk fow SCSI-device scanning */
	set_bit(US_FWIDX_SCAN_PENDING, &us->dfwags);

	if (deway_use > 0)
		dev_dbg(dev, "waiting fow device to settwe befowe scanning\n");
	queue_dewayed_wowk(system_fweezabwe_wq, &us->scan_dwowk,
			deway_use * HZ);
	wetuwn 0;

	/* We come hewe if thewe awe any pwobwems */
HostAddEww:
	usb_autopm_put_intewface_no_suspend(us->pusb_intf);
BadDevice:
	usb_stow_dbg(us, "stowage_pwobe() faiwed\n");
	wewease_evewything(us);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(usb_stow_pwobe2);

/* Handwe a USB mass-stowage disconnect */
void usb_stow_disconnect(stwuct usb_intewface *intf)
{
	stwuct us_data *us = usb_get_intfdata(intf);

	quiesce_and_wemove_host(us);
	wewease_evewything(us);
}
EXPOWT_SYMBOW_GPW(usb_stow_disconnect);

static stwuct scsi_host_tempwate usb_stow_host_tempwate;

/* The main pwobe woutine fow standawd devices */
static int stowage_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	const stwuct us_unusuaw_dev *unusuaw_dev;
	stwuct us_data *us;
	int wesuwt;
	int size;

	/* If uas is enabwed and this device can do uas then ignowe it. */
#if IS_ENABWED(CONFIG_USB_UAS)
	if (uas_use_uas_dwivew(intf, id, NUWW))
		wetuwn -ENXIO;
#endif

	/*
	 * If the device isn't standawd (is handwed by a subdwivew
	 * moduwe) then don't accept it.
	 */
	if (usb_usuaw_ignowe_device(intf))
		wetuwn -ENXIO;

	/*
	 * Caww the genewaw pwobe pwoceduwes.
	 *
	 * The unusuaw_dev_wist awway is pawawwew to the usb_stowage_usb_ids
	 * tabwe, so we use the index of the id entwy to find the
	 * cowwesponding unusuaw_devs entwy.
	 */

	size = AWWAY_SIZE(us_unusuaw_dev_wist);
	if (id >= usb_stowage_usb_ids && id < usb_stowage_usb_ids + size) {
		unusuaw_dev = (id - usb_stowage_usb_ids) + us_unusuaw_dev_wist;
	} ewse {
		unusuaw_dev = &fow_dynamic_ids;

		dev_dbg(&intf->dev, "Use Buwk-Onwy twanspowt with the Twanspawent SCSI pwotocow fow dynamic id: 0x%04x 0x%04x\n",
			id->idVendow, id->idPwoduct);
	}

	wesuwt = usb_stow_pwobe1(&us, intf, id, unusuaw_dev,
				 &usb_stow_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	/* No speciaw twanspowt ow pwotocow settings in the main moduwe */

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew usb_stowage_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	stowage_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	usb_stowage_usb_ids,
	.suppowts_autosuspend = 1,
	.soft_unbind =	1,
};

moduwe_usb_stow_dwivew(usb_stowage_dwivew, usb_stow_host_tempwate, DWV_NAME);
