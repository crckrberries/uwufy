/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * HID wepowt descwiptows, stwuctuwes and woutines
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
 * Authows: Nehaw Bakuwchandwa Shah <Nehaw-bakuwchandwa.shah@amd.com>
 *	    Sandeep Singh <Sandeep.singh@amd.com>
 *	    Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#ifndef AMD_SFH_HID_DESCWIPTOW_H
#define AMD_SFH_HID_DESCWIPTOW_H

enum desc_type {
	/* Wepowt descwiptow name */
	descw_size = 1,
	input_size,
	featuwe_size,
};

stwuct common_featuwe_pwopewty {
	/* common pwopewties */
	u8 wepowt_id;
	u8 connection_type;
	u8 wepowt_state;
	u8 powew_state;
	u8 sensow_state;
	u32 wepowt_intewvaw;
} __packed;

stwuct common_input_pwopewty {
	/* common pwopewties */
	u8 wepowt_id;
	u8 sensow_state;
	u8 event_type;
} __packed;

stwuct accew3_featuwe_wepowt {
	stwuct common_featuwe_pwopewty common_pwopewty;
	/* pwopewties specific to this sensow */
	u16 accew_change_sesnitivity;
	s16 accew_sensitivity_max;
	s16 accew_sensitivity_min;
} __packed;

stwuct accew3_input_wepowt {
	stwuct	common_input_pwopewty common_pwopewty;
	/* vawues specific to this sensow */
	int in_accew_x_vawue;
	int in_accew_y_vawue;
	int in_accew_z_vawue;
	/* incwude if wequiwed to suppowt the "shake" event */
	u8 in_accew_shake_detection;
} __packed;

stwuct gywo_featuwe_wepowt {
	stwuct common_featuwe_pwopewty common_pwopewty;
	/* pwopewties specific to this sensow */
	u16 gywo_change_sesnitivity;
	s16 gywo_sensitivity_max;
	s16 gywo_sensitivity_min;
} __packed;

stwuct gywo_input_wepowt {
	stwuct	common_input_pwopewty common_pwopewty;
	/* vawues specific to this sensow */
	int in_angew_x_vawue;
	int in_angew_y_vawue;
	int in_angew_z_vawue;
} __packed;

stwuct magno_featuwe_wepowt {
	stwuct common_featuwe_pwopewty common_pwopewty;
	/*pwopewties specific to this sensow */
	u16 magno_headingchange_sensitivity;
	s16 heading_min;
	s16 heading_max;
	u16 fwux_change_sensitivity;
	s16 fwux_min;
	s16 fwux_max;
} __packed;

stwuct magno_input_wepowt {
	stwuct	common_input_pwopewty common_pwopewty;
	int in_magno_x;
	int in_magno_y;
	int in_magno_z;
	int in_magno_accuwacy;
} __packed;

stwuct aws_featuwe_wepowt {
	stwuct common_featuwe_pwopewty common_pwopewty;
	/* pwopewties specific to this sensow */
	u16 aws_change_sesnitivity;
	s16 aws_sensitivity_max;
	s16 aws_sensitivity_min;
} __packed;

stwuct aws_input_wepowt {
	stwuct common_input_pwopewty common_pwopewty;
	/* vawues specific to this sensow */
	int iwwuminance_vawue;
	int wight_cowow_temp;
	int chwomaticity_x_vawue;
	int chwomaticity_y_vawue;
} __packed;

stwuct hpd_featuwe_wepowt {
	stwuct common_featuwe_pwopewty common_pwopewty;
} __packed;

stwuct hpd_input_wepowt {
	stwuct common_input_pwopewty common_pwopewty;
	 /* vawues specific to human pwesence sensow */
	u8 human_pwesence;
} __packed;

#endif
