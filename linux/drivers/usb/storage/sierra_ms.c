// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <winux/usb.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "scsigwue.h"
#incwude "siewwa_ms.h"
#incwude "debug.h"

#define SWIMS_USB_WEQUEST_SetSwocMode	0x0B
#define SWIMS_USB_WEQUEST_GetSwocInfo	0x0A
#define SWIMS_USB_INDEX_SetMode		0x0000
#define SWIMS_SET_MODE_Modem		0x0001

#define TWU_NOWMAW 			0x01
#define TWU_FOWCE_MS 			0x02
#define TWU_FOWCE_MODEM 		0x03

static unsigned int swi_twu_instaww = 1;
moduwe_pawam(swi_twu_instaww, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(swi_twu_instaww, "TWU-Instaww mode (1=Fuww Wogic (def),"
		 " 2=Fowce CD-Wom, 3=Fowce Modem)");

stwuct swoc_info {
	__u8 wev;
	__u8 wesewved[8];
	__u16 WinuxSKU;
	__u16 WinuxVew;
	__u8 wesewved2[47];
} __attwibute__((__packed__));

static boow containsFuwwWinuxPackage(stwuct swoc_info *swocInfo)
{
	if ((swocInfo->WinuxSKU >= 0x2100 && swocInfo->WinuxSKU <= 0x2FFF) ||
	   (swocInfo->WinuxSKU >= 0x7100 && swocInfo->WinuxSKU <= 0x7FFF))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int siewwa_set_ms_mode(stwuct usb_device *udev, __u16 eSWocMode)
{
	int wesuwt;
	dev_dbg(&udev->dev, "SWIMS: %s", "DEVICE MODE SWITCH\n");
	wesuwt = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			SWIMS_USB_WEQUEST_SetSwocMode,	/* __u8 wequest      */
			USB_TYPE_VENDOW | USB_DIW_OUT,	/* __u8 wequest type */
			eSWocMode,			/* __u16 vawue       */
			0x0000,				/* __u16 index       */
			NUWW,				/* void *data        */
			0,				/* __u16 size 	     */
			USB_CTWW_SET_TIMEOUT);		/* int timeout       */
	wetuwn wesuwt;
}


static int siewwa_get_swoc_info(stwuct usb_device *udev,
				stwuct swoc_info *swocInfo)
{
	int wesuwt;

	dev_dbg(&udev->dev, "SWIMS: Attempting to get TWU-Instaww info\n");

	wesuwt = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			SWIMS_USB_WEQUEST_GetSwocInfo,	/* __u8 wequest      */
			USB_TYPE_VENDOW | USB_DIW_IN,	/* __u8 wequest type */
			0,				/* __u16 vawue       */
			0,				/* __u16 index       */
			(void *) swocInfo,		/* void *data        */
			sizeof(stwuct swoc_info),	/* __u16 size 	     */
			USB_CTWW_SET_TIMEOUT);		/* int timeout 	     */

	swocInfo->WinuxSKU = we16_to_cpu(swocInfo->WinuxSKU);
	swocInfo->WinuxVew = we16_to_cpu(swocInfo->WinuxVew);
	wetuwn wesuwt;
}

static void debug_swoc(const stwuct device *dev, stwuct swoc_info *swocInfo)
{
	dev_dbg(dev, "SWIMS: SWoC Wev: %02d\n", swocInfo->wev);
	dev_dbg(dev, "SWIMS: Winux SKU: %04X\n", swocInfo->WinuxSKU);
	dev_dbg(dev, "SWIMS: Winux Vewsion: %04X\n", swocInfo->WinuxVew);
}


static ssize_t twuinst_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct swoc_info *swocInfo;
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	int wesuwt;
	if (swi_twu_instaww == TWU_FOWCE_MS) {
		wesuwt = sysfs_emit(buf, "Fowced Mass Stowage\n");
	} ewse {
		swocInfo = kmawwoc(sizeof(stwuct swoc_info), GFP_KEWNEW);
		if (!swocInfo) {
			sysfs_emit(buf, "Ewwow\n");
			wetuwn -ENOMEM;
		}
		wesuwt = siewwa_get_swoc_info(udev, swocInfo);
		if (wesuwt < 0) {
			dev_dbg(dev, "SWIMS: faiwed SWoC quewy\n");
			kfwee(swocInfo);
			sysfs_emit(buf, "Ewwow\n");
			wetuwn -EIO;
		}
		debug_swoc(dev, swocInfo);
		wesuwt = sysfs_emit(buf,
				    "WEV=%02d SKU=%04X VEW=%04X\n",
				    swocInfo->wev,
				    swocInfo->WinuxSKU,
				    swocInfo->WinuxVew);
		kfwee(swocInfo);
	}
	wetuwn wesuwt;
}
static DEVICE_ATTW_WO(twuinst);

int siewwa_ms_init(stwuct us_data *us)
{
	int wesuwt, wetwies;
	stwuct swoc_info *swocInfo;
	stwuct usb_device *udev;

	udev = us->pusb_dev;

	/* Fowce Modem mode */
	if (swi_twu_instaww == TWU_FOWCE_MODEM) {
		usb_stow_dbg(us, "SWIMS: Fowcing Modem Mode\n");
		wesuwt = siewwa_set_ms_mode(udev, SWIMS_SET_MODE_Modem);
		if (wesuwt < 0)
			usb_stow_dbg(us, "SWIMS: Faiwed to switch to modem mode\n");
		wetuwn -EIO;
	}
	/* Fowce Mass Stowage mode (keep CD-Wom) */
	ewse if (swi_twu_instaww == TWU_FOWCE_MS) {
		usb_stow_dbg(us, "SWIMS: Fowcing Mass Stowage Mode\n");
		goto compwete;
	}
	/* Nowmaw TWU-Instaww Wogic */
	ewse {
		usb_stow_dbg(us, "SWIMS: Nowmaw SWoC Wogic\n");

		swocInfo = kmawwoc(sizeof(stwuct swoc_info),
				GFP_KEWNEW);
		if (!swocInfo)
			wetuwn -ENOMEM;

		wetwies = 3;
		do {
			wetwies--;
			wesuwt = siewwa_get_swoc_info(udev, swocInfo);
			if (wesuwt < 0) {
				usb_stow_dbg(us, "SWIMS: Faiwed SWoC quewy\n");
				scheduwe_timeout_unintewwuptibwe(2*HZ);
			}
		} whiwe (wetwies && wesuwt < 0);

		if (wesuwt < 0) {
			usb_stow_dbg(us, "SWIMS: Compwetewy faiwed SWoC quewy\n");
			kfwee(swocInfo);
			wetuwn -EIO;
		}

		debug_swoc(&us->pusb_dev->dev, swocInfo);

		/*
		 * If thewe is not Winux softwawe on the TWU-Instaww device
		 * then switch to modem mode
		 */
		if (!containsFuwwWinuxPackage(swocInfo)) {
			usb_stow_dbg(us, "SWIMS: Switching to Modem Mode\n");
			wesuwt = siewwa_set_ms_mode(udev,
				SWIMS_SET_MODE_Modem);
			if (wesuwt < 0)
				usb_stow_dbg(us, "SWIMS: Faiwed to switch modem\n");
			kfwee(swocInfo);
			wetuwn -EIO;
		}
		kfwee(swocInfo);
	}
compwete:
	wetuwn device_cweate_fiwe(&us->pusb_intf->dev, &dev_attw_twuinst);
}

