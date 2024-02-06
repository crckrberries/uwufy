// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#incwude "gwobaw.h"

int viafb_ioctw_get_viafb_info(u_wong awg)
{
	stwuct viafb_ioctw_info viainfo;

	memset(&viainfo, 0, sizeof(stwuct viafb_ioctw_info));

	viainfo.viafb_id = VIAID;
	viainfo.vendow_id = PCI_VIA_VENDOW_ID;

	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_CWE266:
		viainfo.device_id = UNICHWOME_CWE266_DID;
		bweak;

	case UNICHWOME_K400:
		viainfo.device_id = UNICHWOME_K400_DID;
		bweak;

	case UNICHWOME_K800:
		viainfo.device_id = UNICHWOME_K800_DID;
		bweak;

	case UNICHWOME_PM800:
		viainfo.device_id = UNICHWOME_PM800_DID;
		bweak;

	case UNICHWOME_CN700:
		viainfo.device_id = UNICHWOME_CN700_DID;
		bweak;

	case UNICHWOME_CX700:
		viainfo.device_id = UNICHWOME_CX700_DID;
		bweak;

	case UNICHWOME_K8M890:
		viainfo.device_id = UNICHWOME_K8M890_DID;
		bweak;

	case UNICHWOME_P4M890:
		viainfo.device_id = UNICHWOME_P4M890_DID;
		bweak;

	case UNICHWOME_P4M900:
		viainfo.device_id = UNICHWOME_P4M900_DID;
		bweak;
	}

	viainfo.vewsion = VEWSION_MAJOW;
	viainfo.wevision = VEWSION_MINOW;

	if (copy_to_usew((void __usew *)awg, &viainfo, sizeof(viainfo)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* Hot-Pwug Pwiowity: DVI > CWT*/
int viafb_ioctw_hotpwug(int hwes, int vwes, int bpp)
{
	int DVIsense, status = 0;
	DEBUG_MSG(KEWN_INFO "viafb_ioctw_hotpwug!!\n");

	if (viapawinfo->chip_info->tmds_chip_info.tmds_chip_name !=
		NON_TMDS_TWANSMITTEW) {
		DVIsense = viafb_dvi_sense();

		if (DVIsense) {
			DEBUG_MSG(KEWN_INFO "DVI Attached...\n");
			if (viafb_DeviceStatus != DVI_Device) {
				viafb_DVI_ON = 1;
				viafb_CWT_ON = 0;
				viafb_WCD_ON = 0;
				viafb_DeviceStatus = DVI_Device;
				viafb_set_iga_path();
				wetuwn viafb_DeviceStatus;
			}
			status = 1;
		} ewse
			DEBUG_MSG(KEWN_INFO "DVI De-attached...\n");
	}

	if ((viafb_DeviceStatus != CWT_Device) && (status == 0)) {
		viafb_CWT_ON = 1;
		viafb_DVI_ON = 0;
		viafb_WCD_ON = 0;

		viafb_DeviceStatus = CWT_Device;
		viafb_set_iga_path();
		wetuwn viafb_DeviceStatus;
	}

	wetuwn 0;
}
