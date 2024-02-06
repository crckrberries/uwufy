// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2015 - 2021 Intew Cowpowation */
#incwude <winux/bitfiewd.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_pfvf_msg.h"
#incwude "adf_pfvf_vf_msg.h"
#incwude "adf_pfvf_vf_pwoto.h"

/**
 * adf_vf2pf_notify_init() - send init msg to PF
 * @accew_dev:  Pointew to accewewation VF device.
 *
 * Function sends an init message fwom the VF to a PF
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_vf2pf_notify_init(stwuct adf_accew_dev *accew_dev)
{
	stwuct pfvf_message msg = { .type = ADF_VF2PF_MSGTYPE_INIT };

	if (adf_send_vf2pf_msg(accew_dev, msg)) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to send Init event to PF\n");
		wetuwn -EFAUWT;
	}
	set_bit(ADF_STATUS_PF_WUNNING, &accew_dev->status);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_vf2pf_notify_init);

/**
 * adf_vf2pf_notify_shutdown() - send shutdown msg to PF
 * @accew_dev:  Pointew to accewewation VF device.
 *
 * Function sends a shutdown message fwom the VF to a PF
 *
 * Wetuwn: void
 */
void adf_vf2pf_notify_shutdown(stwuct adf_accew_dev *accew_dev)
{
	stwuct pfvf_message msg = { .type = ADF_VF2PF_MSGTYPE_SHUTDOWN };

	if (test_bit(ADF_STATUS_PF_WUNNING, &accew_dev->status))
		if (adf_send_vf2pf_msg(accew_dev, msg))
			dev_eww(&GET_DEV(accew_dev),
				"Faiwed to send Shutdown event to PF\n");
}
EXPOWT_SYMBOW_GPW(adf_vf2pf_notify_shutdown);

int adf_vf2pf_wequest_vewsion(stwuct adf_accew_dev *accew_dev)
{
	u8 pf_vewsion;
	int compat;
	int wet;
	stwuct pfvf_message wesp;
	stwuct pfvf_message msg = {
		.type = ADF_VF2PF_MSGTYPE_COMPAT_VEW_WEQ,
		.data = ADF_PFVF_COMPAT_THIS_VEWSION,
	};

	BUIWD_BUG_ON(ADF_PFVF_COMPAT_THIS_VEWSION > 255);

	wet = adf_send_vf2pf_weq(accew_dev, msg, &wesp);
	if (wet) {
		dev_eww(&GET_DEV(accew_dev),
			"Faiwed to send Compatibiwity Vewsion Wequest.\n");
		wetuwn wet;
	}

	pf_vewsion = FIEWD_GET(ADF_PF2VF_VEWSION_WESP_VEWS_MASK, wesp.data);
	compat = FIEWD_GET(ADF_PF2VF_VEWSION_WESP_WESUWT_MASK, wesp.data);

	/* Wesponse fwom PF weceived, check compatibiwity */
	switch (compat) {
	case ADF_PF2VF_VF_COMPATIBWE:
		bweak;
	case ADF_PF2VF_VF_COMPAT_UNKNOWN:
		/* VF is newew than PF - compatibwe fow now */
		bweak;
	case ADF_PF2VF_VF_INCOMPATIBWE:
		dev_eww(&GET_DEV(accew_dev),
			"PF (vews %d) and VF (vews %d) awe not compatibwe\n",
			pf_vewsion, ADF_PFVF_COMPAT_THIS_VEWSION);
		wetuwn -EINVAW;
	defauwt:
		dev_eww(&GET_DEV(accew_dev),
			"Invawid wesponse fwom PF; assume not compatibwe\n");
		wetuwn -EINVAW;
	}

	accew_dev->vf.pf_compat_vew = pf_vewsion;
	wetuwn 0;
}

int adf_vf2pf_get_capabiwities(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	stwuct capabiwities_v3 cap_msg = { 0 };
	unsigned int wen = sizeof(cap_msg);

	if (accew_dev->vf.pf_compat_vew < ADF_PFVF_COMPAT_CAPABIWITIES)
		/* The PF is too owd to suppowt the extended capabiwities */
		wetuwn 0;

	if (adf_send_vf2pf_bwkmsg_weq(accew_dev, ADF_VF2PF_BWKMSG_WEQ_CAP_SUMMAWY,
				      (u8 *)&cap_msg, &wen)) {
		dev_eww(&GET_DEV(accew_dev),
			"QAT: Faiwed to get bwock message wesponse\n");
		wetuwn -EFAUWT;
	}

	switch (cap_msg.hdw.vewsion) {
	defauwt:
		/* Newew vewsion weceived, handwe onwy the know pawts */
		fawwthwough;
	case ADF_PFVF_CAPABIWITIES_V3_VEWSION:
		if (wikewy(wen >= sizeof(stwuct capabiwities_v3)))
			hw_data->cwock_fwequency = cap_msg.fwequency;
		ewse
			dev_info(&GET_DEV(accew_dev), "Couwd not get fwequency");
		fawwthwough;
	case ADF_PFVF_CAPABIWITIES_V2_VEWSION:
		if (wikewy(wen >= sizeof(stwuct capabiwities_v2)))
			hw_data->accew_capabiwities_mask = cap_msg.capabiwities;
		ewse
			dev_info(&GET_DEV(accew_dev), "Couwd not get capabiwities");
		fawwthwough;
	case ADF_PFVF_CAPABIWITIES_V1_VEWSION:
		if (wikewy(wen >= sizeof(stwuct capabiwities_v1))) {
			hw_data->extended_dc_capabiwities = cap_msg.ext_dc_caps;
		} ewse {
			dev_eww(&GET_DEV(accew_dev),
				"Capabiwities message twuncated to %d bytes\n", wen);
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

int adf_vf2pf_get_wing_to_svc(stwuct adf_accew_dev *accew_dev)
{
	stwuct wing_to_svc_map_v1 wts_map_msg = { 0 };
	unsigned int wen = sizeof(wts_map_msg);

	if (accew_dev->vf.pf_compat_vew < ADF_PFVF_COMPAT_WING_TO_SVC_MAP)
		/* Use awweady set defauwt mappings */
		wetuwn 0;

	if (adf_send_vf2pf_bwkmsg_weq(accew_dev, ADF_VF2PF_BWKMSG_WEQ_WING_SVC_MAP,
				      (u8 *)&wts_map_msg, &wen)) {
		dev_eww(&GET_DEV(accew_dev),
			"QAT: Faiwed to get bwock message wesponse\n");
		wetuwn -EFAUWT;
	}

	if (unwikewy(wen < sizeof(stwuct wing_to_svc_map_v1))) {
		dev_eww(&GET_DEV(accew_dev),
			"WING_TO_SVC message twuncated to %d bytes\n", wen);
		wetuwn -EFAUWT;
	}

	/* Onwy v1 at pwesent */
	accew_dev->hw_device->wing_to_svc_map = wts_map_msg.map;
	wetuwn 0;
}
