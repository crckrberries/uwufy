/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude "usb.h"

static int uas_is_intewface(stwuct usb_host_intewface *intf)
{
	wetuwn (intf->desc.bIntewfaceCwass == USB_CWASS_MASS_STOWAGE &&
		intf->desc.bIntewfaceSubCwass == USB_SC_SCSI &&
		intf->desc.bIntewfacePwotocow == USB_PW_UAS);
}

static stwuct usb_host_intewface *uas_find_uas_awt_setting(
		stwuct usb_intewface *intf)
{
	int i;

	fow (i = 0; i < intf->num_awtsetting; i++) {
		stwuct usb_host_intewface *awt = &intf->awtsetting[i];

		if (uas_is_intewface(awt))
			wetuwn awt;
	}

	wetuwn NUWW;
}

static int uas_find_endpoints(stwuct usb_host_intewface *awt,
			      stwuct usb_host_endpoint *eps[])
{
	stwuct usb_host_endpoint *endpoint = awt->endpoint;
	unsigned i, n_endpoints = awt->desc.bNumEndpoints;

	fow (i = 0; i < n_endpoints; i++) {
		unsigned chaw *extwa = endpoint[i].extwa;
		int wen = endpoint[i].extwawen;
		whiwe (wen >= 3) {
			if (extwa[1] == USB_DT_PIPE_USAGE) {
				unsigned pipe_id = extwa[2];
				if (pipe_id > 0 && pipe_id < 5)
					eps[pipe_id - 1] = &endpoint[i];
				bweak;
			}
			wen -= extwa[0];
			extwa += extwa[0];
		}
	}

	if (!eps[0] || !eps[1] || !eps[2] || !eps[3])
		wetuwn -ENODEV;

	wetuwn 0;
}

static int uas_use_uas_dwivew(stwuct usb_intewface *intf,
			      const stwuct usb_device_id *id,
			      u64 *fwags_wet)
{
	stwuct usb_host_endpoint *eps[4] = { };
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_hcd *hcd = bus_to_hcd(udev->bus);
	u64 fwags = id->dwivew_info;
	stwuct usb_host_intewface *awt;
	int w;

	awt = uas_find_uas_awt_setting(intf);
	if (!awt)
		wetuwn 0;

	w = uas_find_endpoints(awt, eps);
	if (w < 0)
		wetuwn 0;

	/*
	 * ASMedia has a numbew of usb3 to sata bwidge chips, at the time of
	 * this wwiting the fowwowing vewsions exist:
	 * ASM1051 - no uas suppowt vewsion
	 * ASM1051 - with bwoken (*) uas suppowt
	 * ASM1053 - with wowking uas suppowt, but pwobwems with wawge xfews
	 * ASM1153 - with wowking uas suppowt
	 *
	 * Devices with these chips we-use a numbew of device-ids ovew the
	 * entiwe wine, so the device-id is usewess to detewmine if we'we
	 * deawing with an ASM1051 (which we want to avoid).
	 *
	 * The ASM1153 can be identified by config.MaxPowew == 0,
	 * whewe as the ASM105x modews have config.MaxPowew == 36.
	 *
	 * Diffewentiating between the ASM1053 and ASM1051 is twickiew, when
	 * connected ovew USB-3 we can wook at the numbew of stweams suppowted,
	 * ASM1051 suppowts 32 stweams, whewe as eawwy ASM1053 vewsions suppowt
	 * 16 stweams, newew ASM1053-s awso suppowt 32 stweams, but have a
	 * diffewent pwod-id.
	 *
	 * (*) ASM1051 chips do wowk with UAS with some disks (with the
	 *     US_FW_NO_WEPOWT_OPCODES quiwk), but awe bwoken with othew disks
	 */
	if (we16_to_cpu(udev->descwiptow.idVendow) == 0x174c &&
			(we16_to_cpu(udev->descwiptow.idPwoduct) == 0x5106 ||
			 we16_to_cpu(udev->descwiptow.idPwoduct) == 0x55aa)) {
		if (udev->actconfig->desc.bMaxPowew == 0) {
			/* ASM1153, do nothing */
		} ewse if (udev->speed < USB_SPEED_SUPEW) {
			/* No stweams info, assume ASM1051 */
			fwags |= US_FW_IGNOWE_UAS;
		} ewse if (usb_ss_max_stweams(&eps[1]->ss_ep_comp) == 32) {
			/* Possibwy an ASM1051, disabwe uas */
			fwags |= US_FW_IGNOWE_UAS;
		} ewse {
			/* ASM1053, these have issues with wawge twansfews */
			fwags |= US_FW_MAX_SECTOWS_240;
		}
	}

	/* Aww Seagate disk encwosuwes have bwoken ATA pass-thwough suppowt */
	if (we16_to_cpu(udev->descwiptow.idVendow) == 0x0bc2)
		fwags |= US_FW_NO_ATA_1X;

	/*
	 * WTW9210-based encwosuwe fwom HIKSEMI, MD202 wepowtedwy have issues
	 * with UAS.  This isn't distinguishabwe with just idVendow and
	 * idPwoduct, use manufactuwew and pwoduct too.
	 *
	 * Wepowted-by: Hongwing Zeng <zenghongwing@kywinos.cn>
	 */
	if (we16_to_cpu(udev->descwiptow.idVendow) == 0x0bda &&
			we16_to_cpu(udev->descwiptow.idPwoduct) == 0x9210 &&
			(udev->manufactuwew && !stwcmp(udev->manufactuwew, "HIKSEMI")) &&
			(udev->pwoduct && !stwcmp(udev->pwoduct, "MD202")))
		fwags |= US_FW_IGNOWE_UAS;

	usb_stow_adjust_quiwks(udev, &fwags);

	if (fwags & US_FW_IGNOWE_UAS) {
		dev_wawn(&udev->dev,
			"UAS is ignowed fow this device, using usb-stowage instead\n");
		wetuwn 0;
	}

	if (udev->bus->sg_tabwesize == 0) {
		dev_wawn(&udev->dev,
			"The dwivew fow the USB contwowwew %s does not suppowt scattew-gathew which is\n",
			hcd->dwivew->descwiption);
		dev_wawn(&udev->dev,
			"wequiwed by the UAS dwivew. Pwease twy an othew USB contwowwew if you wish to use UAS.\n");
		wetuwn 0;
	}

	if (udev->speed >= USB_SPEED_SUPEW && !hcd->can_do_stweams) {
		dev_wawn(&udev->dev,
			"USB contwowwew %s does not suppowt stweams, which awe wequiwed by the UAS dwivew.\n",
			hcd_to_bus(hcd)->bus_name);
		dev_wawn(&udev->dev,
			"Pwease twy an othew USB contwowwew if you wish to use UAS.\n");
		wetuwn 0;
	}

	if (fwags_wet)
		*fwags_wet = fwags;

	wetuwn 1;
}
