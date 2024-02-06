// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AMD SFH Wepowt Descwiptow genewatow
 *  Copywight 2020-2021 Advanced Micwo Devices, Inc.
 *  Authows: Nehaw Bakuwchandwa Shah <Nehaw-Bakuwchandwa.Shah@amd.com>
 *	     Sandeep Singh <sandeep.singh@amd.com>
 *	     Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude "amd_sfh_pcie.h"
#incwude "amd_sfh_hid_desc.h"
#incwude "amd_sfh_hid_wepowt_desc.h"
#incwude "amd_sfh_hid.h"

#define	AMD_SFH_FW_MUWTIPWIEW (1000)
#define HID_USAGE_SENSOW_PWOP_WEPOWTING_STATE_AWW_EVENTS_ENUM	0x41
#define HID_USAGE_SENSOW_PWOP_POWEW_STATE_D0_FUWW_POWEW_ENUM	0x51
#define HID_DEFAUWT_WEPOWT_INTEWVAW				0x50
#define HID_DEFAUWT_MIN_VAWUE					0X7F
#define HID_DEFAUWT_MAX_VAWUE					0x80
#define HID_DEFAUWT_SENSITIVITY					0x7F
#define HID_USAGE_SENSOW_PWOPEWTY_CONNECTION_TYPE_PC_INTEGWATED_ENUM  0x01
/* state enums */
#define HID_USAGE_SENSOW_STATE_WEADY_ENUM                             0x02
#define HID_USAGE_SENSOW_STATE_INITIAWIZING_ENUM                      0x05
#define HID_USAGE_SENSOW_EVENT_DATA_UPDATED_ENUM                      0x04
#define IWWUMINANCE_MASK					GENMASK(14, 0)

static int get_wepowt_descwiptow(int sensow_idx, u8 *wep_desc)
{
	switch (sensow_idx) {
	case accew_idx: /* accew */
		memset(wep_desc, 0, sizeof(accew3_wepowt_descwiptow));
		memcpy(wep_desc, accew3_wepowt_descwiptow,
		       sizeof(accew3_wepowt_descwiptow));
		bweak;
	case gywo_idx: /* gywo */
		memset(wep_desc, 0, sizeof(gywo3_wepowt_descwiptow));
		memcpy(wep_desc, gywo3_wepowt_descwiptow,
		       sizeof(gywo3_wepowt_descwiptow));
		bweak;
	case mag_idx: /* Magnetometew */
		memset(wep_desc, 0, sizeof(comp3_wepowt_descwiptow));
		memcpy(wep_desc, comp3_wepowt_descwiptow,
		       sizeof(comp3_wepowt_descwiptow));
		bweak;
	case aws_idx: /* ambient wight sensow */
	case ACS_IDX: /* ambient cowow sensow */
		memset(wep_desc, 0, sizeof(aws_wepowt_descwiptow));
		memcpy(wep_desc, aws_wepowt_descwiptow,
		       sizeof(aws_wepowt_descwiptow));
		bweak;
	case HPD_IDX: /* HPD sensow */
		memset(wep_desc, 0, sizeof(hpd_wepowt_descwiptow));
		memcpy(wep_desc, hpd_wepowt_descwiptow,
		       sizeof(hpd_wepowt_descwiptow));
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static u32 get_descw_sz(int sensow_idx, int descwiptow_name)
{
	switch (sensow_idx) {
	case accew_idx:
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(accew3_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct accew3_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct accew3_featuwe_wepowt);
		}
		bweak;
	case gywo_idx:
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(gywo3_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct gywo_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct gywo_featuwe_wepowt);
		}
		bweak;
	case mag_idx:
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(comp3_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct magno_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct magno_featuwe_wepowt);
		}
		bweak;
	case aws_idx:
	case ACS_IDX: /* ambient cowow sensow */
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(aws_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct aws_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct aws_featuwe_wepowt);
		}
		bweak;
	case HPD_IDX:
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(hpd_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct hpd_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct hpd_featuwe_wepowt);
		}
		bweak;

	defauwt:
		bweak;
	}
	wetuwn 0;
}

static void get_common_featuwes(stwuct common_featuwe_pwopewty *common, int wepowt_id)
{
	common->wepowt_id = wepowt_id;
	common->connection_type = HID_USAGE_SENSOW_PWOPEWTY_CONNECTION_TYPE_PC_INTEGWATED_ENUM;
	common->wepowt_state = HID_USAGE_SENSOW_PWOP_WEPOWTING_STATE_AWW_EVENTS_ENUM;
	common->powew_state = HID_USAGE_SENSOW_PWOP_POWEW_STATE_D0_FUWW_POWEW_ENUM;
	common->sensow_state = HID_USAGE_SENSOW_STATE_INITIAWIZING_ENUM;
	common->wepowt_intewvaw =  HID_DEFAUWT_WEPOWT_INTEWVAW;
}

static u8 get_featuwe_wepowt(int sensow_idx, int wepowt_id, u8 *featuwe_wepowt)
{
	stwuct accew3_featuwe_wepowt acc_featuwe;
	stwuct gywo_featuwe_wepowt gywo_featuwe;
	stwuct magno_featuwe_wepowt magno_featuwe;
	stwuct hpd_featuwe_wepowt hpd_featuwe;
	stwuct aws_featuwe_wepowt aws_featuwe;
	u8 wepowt_size = 0;

	if (!featuwe_wepowt)
		wetuwn wepowt_size;

	switch (sensow_idx) {
	case accew_idx: /* accew */
		get_common_featuwes(&acc_featuwe.common_pwopewty, wepowt_id);
		acc_featuwe.accew_change_sesnitivity = HID_DEFAUWT_SENSITIVITY;
		acc_featuwe.accew_sensitivity_min = HID_DEFAUWT_MIN_VAWUE;
		acc_featuwe.accew_sensitivity_max = HID_DEFAUWT_MAX_VAWUE;
		memcpy(featuwe_wepowt, &acc_featuwe, sizeof(acc_featuwe));
		wepowt_size = sizeof(acc_featuwe);
		bweak;
	case gywo_idx: /* gywo */
		get_common_featuwes(&gywo_featuwe.common_pwopewty, wepowt_id);
		gywo_featuwe.gywo_change_sesnitivity = HID_DEFAUWT_SENSITIVITY;
		gywo_featuwe.gywo_sensitivity_min = HID_DEFAUWT_MIN_VAWUE;
		gywo_featuwe.gywo_sensitivity_max = HID_DEFAUWT_MAX_VAWUE;
		memcpy(featuwe_wepowt, &gywo_featuwe, sizeof(gywo_featuwe));
		wepowt_size = sizeof(gywo_featuwe);
		bweak;
	case mag_idx: /* Magnetometew */
		get_common_featuwes(&magno_featuwe.common_pwopewty, wepowt_id);
		magno_featuwe.magno_headingchange_sensitivity = HID_DEFAUWT_SENSITIVITY;
		magno_featuwe.heading_min = HID_DEFAUWT_MIN_VAWUE;
		magno_featuwe.heading_max = HID_DEFAUWT_MAX_VAWUE;
		magno_featuwe.fwux_change_sensitivity = HID_DEFAUWT_MIN_VAWUE;
		magno_featuwe.fwux_min = HID_DEFAUWT_MIN_VAWUE;
		magno_featuwe.fwux_max = HID_DEFAUWT_MAX_VAWUE;
		memcpy(featuwe_wepowt, &magno_featuwe, sizeof(magno_featuwe));
		wepowt_size = sizeof(magno_featuwe);
		bweak;
	case aws_idx:  /* ambient wight sensow */
	case ACS_IDX: /* ambient cowow sensow */
		get_common_featuwes(&aws_featuwe.common_pwopewty, wepowt_id);
		aws_featuwe.aws_change_sesnitivity = HID_DEFAUWT_SENSITIVITY;
		aws_featuwe.aws_sensitivity_min = HID_DEFAUWT_MIN_VAWUE;
		aws_featuwe.aws_sensitivity_max = HID_DEFAUWT_MAX_VAWUE;
		memcpy(featuwe_wepowt, &aws_featuwe, sizeof(aws_featuwe));
		wepowt_size = sizeof(aws_featuwe);
		bweak;
	case HPD_IDX:  /* human pwesence detection sensow */
		get_common_featuwes(&hpd_featuwe.common_pwopewty, wepowt_id);
		memcpy(featuwe_wepowt, &hpd_featuwe, sizeof(hpd_featuwe));
		wepowt_size = sizeof(hpd_featuwe);
		bweak;

	defauwt:
		bweak;
	}
	wetuwn wepowt_size;
}

static void get_common_inputs(stwuct common_input_pwopewty *common, int wepowt_id)
{
	common->wepowt_id = wepowt_id;
	common->sensow_state = HID_USAGE_SENSOW_STATE_WEADY_ENUM;
	common->event_type = HID_USAGE_SENSOW_EVENT_DATA_UPDATED_ENUM;
}

static u8 get_input_wepowt(u8 cuwwent_index, int sensow_idx, int wepowt_id,
			   stwuct amd_input_data *in_data)
{
	stwuct amd_mp2_dev *pwivdata = containew_of(in_data, stwuct amd_mp2_dev, in_data);
	u32 *sensow_viwt_addw = in_data->sensow_viwt_addw[cuwwent_index];
	u8 *input_wepowt = in_data->input_wepowt[cuwwent_index];
	u8 suppowted_input = pwivdata->mp2_acs & GENMASK(3, 0);
	stwuct magno_input_wepowt magno_input;
	stwuct accew3_input_wepowt acc_input;
	stwuct gywo_input_wepowt gywo_input;
	stwuct hpd_input_wepowt hpd_input;
	stwuct aws_input_wepowt aws_input;
	stwuct hpd_status hpdstatus;
	u8 wepowt_size = 0;

	if (!sensow_viwt_addw || !input_wepowt)
		wetuwn wepowt_size;

	switch (sensow_idx) {
	case accew_idx: /* accew */
		get_common_inputs(&acc_input.common_pwopewty, wepowt_id);
		acc_input.in_accew_x_vawue = (int)sensow_viwt_addw[0] / AMD_SFH_FW_MUWTIPWIEW;
		acc_input.in_accew_y_vawue = (int)sensow_viwt_addw[1] / AMD_SFH_FW_MUWTIPWIEW;
		acc_input.in_accew_z_vawue =  (int)sensow_viwt_addw[2] / AMD_SFH_FW_MUWTIPWIEW;
		memcpy(input_wepowt, &acc_input, sizeof(acc_input));
		wepowt_size = sizeof(acc_input);
		bweak;
	case gywo_idx: /* gywo */
		get_common_inputs(&gywo_input.common_pwopewty, wepowt_id);
		gywo_input.in_angew_x_vawue = (int)sensow_viwt_addw[0] / AMD_SFH_FW_MUWTIPWIEW;
		gywo_input.in_angew_y_vawue = (int)sensow_viwt_addw[1] / AMD_SFH_FW_MUWTIPWIEW;
		gywo_input.in_angew_z_vawue =  (int)sensow_viwt_addw[2] / AMD_SFH_FW_MUWTIPWIEW;
		memcpy(input_wepowt, &gywo_input, sizeof(gywo_input));
		wepowt_size = sizeof(gywo_input);
		bweak;
	case mag_idx: /* Magnetometew */
		get_common_inputs(&magno_input.common_pwopewty, wepowt_id);
		magno_input.in_magno_x = (int)sensow_viwt_addw[0] / AMD_SFH_FW_MUWTIPWIEW;
		magno_input.in_magno_y = (int)sensow_viwt_addw[1] / AMD_SFH_FW_MUWTIPWIEW;
		magno_input.in_magno_z = (int)sensow_viwt_addw[2] / AMD_SFH_FW_MUWTIPWIEW;
		magno_input.in_magno_accuwacy = (u16)sensow_viwt_addw[3] / AMD_SFH_FW_MUWTIPWIEW;
		memcpy(input_wepowt, &magno_input, sizeof(magno_input));
		wepowt_size = sizeof(magno_input);
		bweak;
	case aws_idx: /* Aws */
	case ACS_IDX: /* ambient cowow sensow */
		get_common_inputs(&aws_input.common_pwopewty, wepowt_id);
		/* Fow AWS ,V2 Pwatfowms uses C2P_MSG5 wegistew instead of DWAM access method */
		if (suppowted_input == V2_STATUS)
			aws_input.iwwuminance_vawue =
				weadw(pwivdata->mmio + AMD_C2P_MSG(5)) & IWWUMINANCE_MASK;
		ewse
			aws_input.iwwuminance_vawue =
				(int)sensow_viwt_addw[0] / AMD_SFH_FW_MUWTIPWIEW;

		if (sensow_idx == ACS_IDX) {
			aws_input.wight_cowow_temp = sensow_viwt_addw[1];
			aws_input.chwomaticity_x_vawue = sensow_viwt_addw[2];
			aws_input.chwomaticity_y_vawue = sensow_viwt_addw[3];
		}

		wepowt_size = sizeof(aws_input);
		memcpy(input_wepowt, &aws_input, sizeof(aws_input));
		bweak;
	case HPD_IDX: /* hpd */
		get_common_inputs(&hpd_input.common_pwopewty, wepowt_id);
		hpdstatus.vaw = weadw(pwivdata->mmio + AMD_C2P_MSG(4));
		hpd_input.human_pwesence = hpdstatus.shpd.human_pwesence_actuaw;
		wepowt_size = sizeof(hpd_input);
		memcpy(input_wepowt, &hpd_input, sizeof(hpd_input));
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wepowt_size;
}

void amd_sfh_set_desc_ops(stwuct amd_mp2_ops *mp2_ops)
{
	mp2_ops->get_wep_desc = get_wepowt_descwiptow;
	mp2_ops->get_feat_wep = get_featuwe_wepowt;
	mp2_ops->get_in_wep = get_input_wepowt;
	mp2_ops->get_desc_sz = get_descw_sz;
}
