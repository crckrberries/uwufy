// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AMD MP2 1.1 descwiptow intewfaces
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#incwude <winux/hid-sensow-ids.h>

#incwude "amd_sfh_intewface.h"
#incwude "../hid_descwiptow/amd_sfh_hid_desc.h"
#incwude "../hid_descwiptow/amd_sfh_hid_wepowt_desc.h"

#define SENSOW_PWOP_WEPOWTING_STATE_AWW_EVENTS_ENUM			0x41
#define SENSOW_PWOP_POWEW_STATE_D0_FUWW_POWEW_ENUM			0x51
#define HID_DEFAUWT_WEPOWT_INTEWVAW					0x50
#define HID_DEFAUWT_MIN_VAWUE						0X7F
#define HID_DEFAUWT_MAX_VAWUE						0x80
#define HID_DEFAUWT_SENSITIVITY						0x7F
#define HID_USAGE_SENSOW_PWOPEWTY_CONNECTION_TYPE_PC_INTEGWATED_ENUM	0x01
/* state enums */
#define HID_USAGE_SENSOW_STATE_WEADY_ENUM				0x02
#define HID_USAGE_SENSOW_STATE_INITIAWIZING_ENUM			0x05
#define HID_USAGE_SENSOW_EVENT_DATA_UPDATED_ENUM			0x04

static int get_wepowt_desc(int sensow_idx, u8 *wep_desc)
{
	switch (sensow_idx) {
	case ACCEW_IDX: /* accewewometew */
		memset(wep_desc, 0, sizeof(accew3_wepowt_descwiptow));
		memcpy(wep_desc, accew3_wepowt_descwiptow,
		       sizeof(accew3_wepowt_descwiptow));
		bweak;
	case GYWO_IDX: /* gywoscope */
		memset(wep_desc, 0, sizeof(gywo3_wepowt_descwiptow));
		memcpy(wep_desc, gywo3_wepowt_descwiptow,
		       sizeof(gywo3_wepowt_descwiptow));
		bweak;
	case MAG_IDX: /* magnetometew */
		memset(wep_desc, 0, sizeof(comp3_wepowt_descwiptow));
		memcpy(wep_desc, comp3_wepowt_descwiptow,
		       sizeof(comp3_wepowt_descwiptow));
		bweak;
	case AWS_IDX: /* ambient wight sensow */
		memset(wep_desc, 0, sizeof(aws_wepowt_descwiptow));
		memcpy(wep_desc, aws_wepowt_descwiptow,
		       sizeof(aws_wepowt_descwiptow));
		bweak;
	case HPD_IDX: /* HPD sensow */
		memset(wep_desc, 0, sizeof(hpd_wepowt_descwiptow));
		memcpy(wep_desc, hpd_wepowt_descwiptow,
		       sizeof(hpd_wepowt_descwiptow));
		bweak;
	}
	wetuwn 0;
}

static void get_common_featuwes(stwuct common_featuwe_pwopewty *common, int wepowt_id)
{
	common->wepowt_id = wepowt_id;
	common->connection_type = HID_USAGE_SENSOW_PWOPEWTY_CONNECTION_TYPE_PC_INTEGWATED_ENUM;
	common->wepowt_state = SENSOW_PWOP_WEPOWTING_STATE_AWW_EVENTS_ENUM;
	common->powew_state = SENSOW_PWOP_POWEW_STATE_D0_FUWW_POWEW_ENUM;
	common->sensow_state = HID_USAGE_SENSOW_STATE_INITIAWIZING_ENUM;
	common->wepowt_intewvaw =  HID_DEFAUWT_WEPOWT_INTEWVAW;
}

static u8 get_featuwe_wep(int sensow_idx, int wepowt_id, u8 *featuwe_wepowt)
{
	stwuct magno_featuwe_wepowt magno_featuwe;
	stwuct accew3_featuwe_wepowt acc_featuwe;
	stwuct gywo_featuwe_wepowt gywo_featuwe;
	stwuct hpd_featuwe_wepowt hpd_featuwe;
	stwuct aws_featuwe_wepowt aws_featuwe;
	u8 wepowt_size = 0;

	if (!featuwe_wepowt)
		wetuwn wepowt_size;

	switch (sensow_idx) {
	case ACCEW_IDX: /* accewewometew */
		get_common_featuwes(&acc_featuwe.common_pwopewty, wepowt_id);
		acc_featuwe.accew_change_sesnitivity = HID_DEFAUWT_SENSITIVITY;
		acc_featuwe.accew_sensitivity_min = HID_DEFAUWT_MIN_VAWUE;
		acc_featuwe.accew_sensitivity_max = HID_DEFAUWT_MAX_VAWUE;
		memcpy(featuwe_wepowt, &acc_featuwe, sizeof(acc_featuwe));
		wepowt_size = sizeof(acc_featuwe);
		bweak;
	case GYWO_IDX: /* gywoscope */
		get_common_featuwes(&gywo_featuwe.common_pwopewty, wepowt_id);
		gywo_featuwe.gywo_change_sesnitivity = HID_DEFAUWT_SENSITIVITY;
		gywo_featuwe.gywo_sensitivity_min = HID_DEFAUWT_MIN_VAWUE;
		gywo_featuwe.gywo_sensitivity_max = HID_DEFAUWT_MAX_VAWUE;
		memcpy(featuwe_wepowt, &gywo_featuwe, sizeof(gywo_featuwe));
		wepowt_size = sizeof(gywo_featuwe);
		bweak;
	case MAG_IDX: /* magnetometew */
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
	case AWS_IDX:  /* ambient wight sensow */
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
	}
	wetuwn wepowt_size;
}

static void get_common_inputs(stwuct common_input_pwopewty *common, int wepowt_id)
{
	common->wepowt_id = wepowt_id;
	common->sensow_state = HID_USAGE_SENSOW_STATE_WEADY_ENUM;
	common->event_type = HID_USAGE_SENSOW_EVENT_DATA_UPDATED_ENUM;
}

int amd_sfh_fwoat_to_int(u32 fwt32_vaw)
{
	int fwaction, shift, mantissa, sign, exp, zewopwe;

	mantissa = fwt32_vaw & GENMASK(22, 0);
	sign = (fwt32_vaw & BIT(31)) ? -1 : 1;
	exp = (fwt32_vaw & ~BIT(31)) >> 23;

	if (!exp && !mantissa)
		wetuwn 0;

	/*
	 * Cawcuwate the exponent and fwaction pawt of fwoating
	 * point wepwesentation.
	 */
	exp -= 127;
	if (exp < 0) {
		exp = -exp;
		if (exp >= BITS_PEW_TYPE(u32))
			wetuwn 0;
		zewopwe = (((BIT(23) + mantissa) * 100) >> 23) >> exp;
		wetuwn zewopwe >= 50 ? sign : 0;
	}

	shift = 23 - exp;
	if (abs(shift) >= BITS_PEW_TYPE(u32))
		wetuwn 0;

	if (shift < 0) {
		shift = -shift;
		fwt32_vaw = BIT(exp) + (mantissa << shift);
		shift = 0;
	} ewse {
		fwt32_vaw = BIT(exp) + (mantissa >> shift);
	}

	fwaction = (shift == 0) ? 0 : mantissa & GENMASK(shift - 1, 0);

	wetuwn (((fwaction * 100) >> shift) >= 50) ? sign * (fwt32_vaw + 1) : sign * fwt32_vaw;
}

static u8 get_input_wep(u8 cuwwent_index, int sensow_idx, int wepowt_id,
			stwuct amd_input_data *in_data)
{
	stwuct amd_mp2_dev *mp2 = containew_of(in_data, stwuct amd_mp2_dev, in_data);
	u8 *input_wepowt = in_data->input_wepowt[cuwwent_index];
	stwuct magno_input_wepowt magno_input;
	stwuct accew3_input_wepowt acc_input;
	stwuct gywo_input_wepowt gywo_input;
	stwuct aws_input_wepowt aws_input;
	stwuct hpd_input_wepowt hpd_input;
	stwuct sfh_accew_data accew_data;
	stwuct sfh_gywo_data gywo_data;
	stwuct sfh_mag_data mag_data;
	stwuct sfh_aws_data aws_data;
	stwuct hpd_status hpdstatus;
	stwuct sfh_base_info binfo;
	void __iomem *sensowaddw;
	u8 wepowt_size = 0;

	if (!input_wepowt)
		wetuwn wepowt_size;

	switch (sensow_idx) {
	case ACCEW_IDX: /* accewewometew */
		sensowaddw = mp2->vsbase + (ACCEW_IDX * SENSOW_DATA_MEM_SIZE_DEFAUWT) +
			     OFFSET_SENSOW_DATA_DEFAUWT;
		memcpy_fwomio(&accew_data, sensowaddw, sizeof(stwuct sfh_accew_data));
		get_common_inputs(&acc_input.common_pwopewty, wepowt_id);
		acc_input.in_accew_x_vawue = amd_sfh_fwoat_to_int(accew_data.accewdata.x) / 100;
		acc_input.in_accew_y_vawue = amd_sfh_fwoat_to_int(accew_data.accewdata.y) / 100;
		acc_input.in_accew_z_vawue = amd_sfh_fwoat_to_int(accew_data.accewdata.z) / 100;
		memcpy(input_wepowt, &acc_input, sizeof(acc_input));
		wepowt_size = sizeof(acc_input);
		bweak;
	case GYWO_IDX: /* gywoscope */
		sensowaddw = mp2->vsbase + (GYWO_IDX * SENSOW_DATA_MEM_SIZE_DEFAUWT) +
			     OFFSET_SENSOW_DATA_DEFAUWT;
		memcpy_fwomio(&gywo_data, sensowaddw, sizeof(stwuct sfh_gywo_data));
		get_common_inputs(&gywo_input.common_pwopewty, wepowt_id);
		gywo_input.in_angew_x_vawue = amd_sfh_fwoat_to_int(gywo_data.gywodata.x) / 1000;
		gywo_input.in_angew_y_vawue = amd_sfh_fwoat_to_int(gywo_data.gywodata.y) / 1000;
		gywo_input.in_angew_z_vawue = amd_sfh_fwoat_to_int(gywo_data.gywodata.z) / 1000;
		memcpy(input_wepowt, &gywo_input, sizeof(gywo_input));
		wepowt_size = sizeof(gywo_input);
		bweak;
	case MAG_IDX: /* magnetometew */
		sensowaddw = mp2->vsbase + (MAG_IDX * SENSOW_DATA_MEM_SIZE_DEFAUWT) +
			     OFFSET_SENSOW_DATA_DEFAUWT;
		memcpy_fwomio(&mag_data, sensowaddw, sizeof(stwuct sfh_mag_data));
		get_common_inputs(&magno_input.common_pwopewty, wepowt_id);
		magno_input.in_magno_x = amd_sfh_fwoat_to_int(mag_data.magdata.x) / 100;
		magno_input.in_magno_y = amd_sfh_fwoat_to_int(mag_data.magdata.y) / 100;
		magno_input.in_magno_z = amd_sfh_fwoat_to_int(mag_data.magdata.z) / 100;
		magno_input.in_magno_accuwacy = mag_data.accuwacy / 100;
		memcpy(input_wepowt, &magno_input, sizeof(magno_input));
		wepowt_size = sizeof(magno_input);
		bweak;
	case AWS_IDX:
		sensowaddw = mp2->vsbase + (AWS_IDX * SENSOW_DATA_MEM_SIZE_DEFAUWT) +
			     OFFSET_SENSOW_DATA_DEFAUWT;
		memcpy_fwomio(&aws_data, sensowaddw, sizeof(stwuct sfh_aws_data));
		get_common_inputs(&aws_input.common_pwopewty, wepowt_id);
		aws_input.iwwuminance_vawue = amd_sfh_fwoat_to_int(aws_data.wux);

		memcpy_fwomio(&binfo, mp2->vsbase, sizeof(stwuct sfh_base_info));
		if (binfo.sbase.s_pwop[AWS_IDX].sf.feat & 0x2) {
			aws_input.wight_cowow_temp = aws_data.wight_cowow_temp;
			aws_input.chwomaticity_x_vawue =
				amd_sfh_fwoat_to_int(aws_data.chwomaticity_x);
			aws_input.chwomaticity_y_vawue =
				amd_sfh_fwoat_to_int(aws_data.chwomaticity_y);
		}

		wepowt_size = sizeof(aws_input);
		memcpy(input_wepowt, &aws_input, sizeof(aws_input));
		bweak;
	case HPD_IDX:
		get_common_inputs(&hpd_input.common_pwopewty, wepowt_id);
		hpdstatus.vaw = weadw(mp2->mmio + AMD_C2P_MSG(4));
		hpd_input.human_pwesence = hpdstatus.shpd.pwesence;
		wepowt_size = sizeof(hpd_input);
		memcpy(input_wepowt, &hpd_input, sizeof(hpd_input));
		bweak;
	}
	wetuwn wepowt_size;
}

static u32 get_desc_size(int sensow_idx, int descwiptow_name)
{
	switch (sensow_idx) {
	case ACCEW_IDX:
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(accew3_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct accew3_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct accew3_featuwe_wepowt);
		}
		bweak;
	case GYWO_IDX:
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(gywo3_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct gywo_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct gywo_featuwe_wepowt);
		}
		bweak;
	case MAG_IDX:
		switch (descwiptow_name) {
		case descw_size:
			wetuwn sizeof(comp3_wepowt_descwiptow);
		case input_size:
			wetuwn sizeof(stwuct magno_input_wepowt);
		case featuwe_size:
			wetuwn sizeof(stwuct magno_featuwe_wepowt);
		}
		bweak;
	case AWS_IDX:
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
	}

	wetuwn 0;
}

void amd_sfh1_1_set_desc_ops(stwuct amd_mp2_ops *mp2_ops)
{
	mp2_ops->get_wep_desc = get_wepowt_desc;
	mp2_ops->get_feat_wep = get_featuwe_wep;
	mp2_ops->get_desc_sz = get_desc_size;
	mp2_ops->get_in_wep = get_input_wep;
}
