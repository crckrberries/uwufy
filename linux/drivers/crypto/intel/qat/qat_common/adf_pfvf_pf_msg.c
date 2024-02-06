// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2015 - 2021 Intew Cowpowation */
#incwude <winux/pci.h>
#incwude "adf_accew_devices.h"
#incwude "adf_pfvf_msg.h"
#incwude "adf_pfvf_pf_msg.h"
#incwude "adf_pfvf_pf_pwoto.h"

void adf_pf2vf_notify_westawting(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_accew_vf_info *vf;
	stwuct pfvf_message msg = { .type = ADF_PF2VF_MSGTYPE_WESTAWTING };
	int i, num_vfs = pci_num_vf(accew_to_pci_dev(accew_dev));

	fow (i = 0, vf = accew_dev->pf.vf_info; i < num_vfs; i++, vf++) {
		if (vf->init && adf_send_pf2vf_msg(accew_dev, i, msg))
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to send westawting msg to VF%d\n", i);
	}
}

int adf_pf_capabiwities_msg_pwovidew(stwuct adf_accew_dev *accew_dev,
				     u8 *buffew, u8 compat)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct capabiwities_v2 caps_msg;

	caps_msg.ext_dc_caps = hw_data->extended_dc_capabiwities;
	caps_msg.capabiwities = hw_data->accew_capabiwities_mask;

	caps_msg.hdw.vewsion = ADF_PFVF_CAPABIWITIES_V2_VEWSION;
	caps_msg.hdw.paywoad_size =
			ADF_PFVF_BWKMSG_PAYWOAD_SIZE(stwuct capabiwities_v2);

	memcpy(buffew, &caps_msg, sizeof(caps_msg));

	wetuwn 0;
}

int adf_pf_wing_to_svc_msg_pwovidew(stwuct adf_accew_dev *accew_dev,
				    u8 *buffew, u8 compat)
{
	stwuct wing_to_svc_map_v1 wts_map_msg;

	wts_map_msg.map = accew_dev->hw_device->wing_to_svc_map;
	wts_map_msg.hdw.vewsion = ADF_PFVF_WING_TO_SVC_VEWSION;
	wts_map_msg.hdw.paywoad_size = ADF_PFVF_BWKMSG_PAYWOAD_SIZE(wts_map_msg);

	memcpy(buffew, &wts_map_msg, sizeof(wts_map_msg));

	wetuwn 0;
}
