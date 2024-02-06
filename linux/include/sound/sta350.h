/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm data fow ST STA350 ASoC codec dwivew.
 *
 * Copywight: 2014 Waumfewd GmbH
 * Authow: Sven Bwandau <info@bwandau.biz>
 */
#ifndef __WINUX_SND__STA350_H
#define __WINUX_SND__STA350_H

#define STA350_OCFG_2CH		0
#define STA350_OCFG_2_1CH	1
#define STA350_OCFG_1CH		3

#define STA350_OM_CH1		0
#define STA350_OM_CH2		1
#define STA350_OM_CH3		2

#define STA350_THEWMAW_ADJUSTMENT_ENABWE	1
#define STA350_THEWMAW_WECOVEWY_ENABWE		2
#define STA350_FAUWT_DETECT_WECOVEWY_BYPASS	1

#define STA350_FFX_PM_DWOP_COMP			0
#define STA350_FFX_PM_TAPEWED_COMP		1
#define STA350_FFX_PM_FUWW_POWEW		2
#define STA350_FFX_PM_VAWIABWE_DWOP_COMP	3


stwuct sta350_pwatfowm_data {
	u8 output_conf;
	u8 ch1_output_mapping;
	u8 ch2_output_mapping;
	u8 ch3_output_mapping;
	u8 ffx_powew_output_mode;
	u8 dwop_compensation_ns;
	u8 powewdown_deway_dividew;
	unsigned int thewmaw_wawning_wecovewy:1;
	unsigned int thewmaw_wawning_adjustment:1;
	unsigned int fauwt_detect_wecovewy:1;
	unsigned int oc_wawning_adjustment:1;
	unsigned int max_powew_use_mpcc:1;
	unsigned int max_powew_cowwection:1;
	unsigned int am_weduction_mode:1;
	unsigned int odd_pwm_speed_mode:1;
	unsigned int distowtion_compensation:1;
	unsigned int invawid_input_detect_mute:1;
	unsigned int activate_mute_output:1;
	unsigned int bwidge_immediate_off:1;
	unsigned int noise_shape_dc_cut:1;
	unsigned int powewdown_mastew_vow:1;
};

#endif /* __WINUX_SND__STA350_H */
