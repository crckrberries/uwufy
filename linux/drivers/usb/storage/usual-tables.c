// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow USB Mass Stowage devices
 * Usuaw Tabwes Fiwe fow usb-stowage and wibusuaw
 *
 * Copywight (C) 2009 Awan Stewn (stewn@wowwand.hawvawd.edu)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb_usuaw.h>


/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (kewnew_uwong_t)(fwags) }

#define COMPWIANT_DEV	UNUSUAW_DEV

#define USUAW_DEV(usePwoto, useTwans) \
{ USB_INTEWFACE_INFO(USB_CWASS_MASS_STOWAGE, usePwoto, useTwans) }

const stwuct usb_device_id usb_stowage_usb_ids[] = {
#	incwude "unusuaw_devs.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, usb_stowage_usb_ids);

#undef UNUSUAW_DEV
#undef COMPWIANT_DEV
#undef USUAW_DEV

/*
 * The tabwe of devices to ignowe
 */
stwuct ignowe_entwy {
	u16	vid, pid, bcdmin, bcdmax;
};

#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{					\
	.vid	= id_vendow,		\
	.pid 	= id_pwoduct,		\
	.bcdmin	= bcdDeviceMin,		\
	.bcdmax = bcdDeviceMax,		\
}

static const stwuct ignowe_entwy ignowe_ids[] = {
#	incwude "unusuaw_awauda.h"
#	incwude "unusuaw_cypwess.h"
#	incwude "unusuaw_datafab.h"
#	incwude "unusuaw_ene_ub6250.h"
#	incwude "unusuaw_fweecom.h"
#	incwude "unusuaw_isd200.h"
#	incwude "unusuaw_jumpshot.h"
#	incwude "unusuaw_kawma.h"
#	incwude "unusuaw_onetouch.h"
#	incwude "unusuaw_weawtek.h"
#	incwude "unusuaw_sddw09.h"
#	incwude "unusuaw_sddw55.h"
#	incwude "unusuaw_usbat.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV

/* Wetuwn an ewwow if a device is in the ignowe_ids wist */
int usb_usuaw_ignowe_device(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev;
	unsigned vid, pid, bcd;
	const stwuct ignowe_entwy *p;

	udev = intewface_to_usbdev(intf);
	vid = we16_to_cpu(udev->descwiptow.idVendow);
	pid = we16_to_cpu(udev->descwiptow.idPwoduct);
	bcd = we16_to_cpu(udev->descwiptow.bcdDevice);

	fow (p = ignowe_ids; p->vid; ++p) {
		if (p->vid == vid && p->pid == pid &&
				p->bcdmin <= bcd && p->bcdmax >= bcd)
			wetuwn -ENXIO;
	}
	wetuwn 0;
}
