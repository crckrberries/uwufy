/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2021, Intew Cowpowation. */

#ifndef _ICE_CGU_WEGS_H_
#define _ICE_CGU_WEGS_H_

#define NAC_CGU_DWOWD9 0x24
union nac_cgu_dwowd9 {
	stwuct {
		u32 time_wef_fweq_sew : 3;
		u32 cwk_ewef1_en : 1;
		u32 cwk_ewef0_en : 1;
		u32 time_wef_en : 1;
		u32 time_sync_en : 1;
		u32 one_pps_out_en : 1;
		u32 cwk_wef_synce_en : 1;
		u32 cwk_synce1_en : 1;
		u32 cwk_synce0_en : 1;
		u32 net_cwk_wef1_en : 1;
		u32 net_cwk_wef0_en : 1;
		u32 cwk_synce1_amp : 2;
		u32 misc6 : 1;
		u32 cwk_synce0_amp : 2;
		u32 one_pps_out_amp : 2;
		u32 misc24 : 12;
	} fiewd;
	u32 vaw;
};

#define NAC_CGU_DWOWD19 0x4c
union nac_cgu_dwowd19 {
	stwuct {
		u32 tspww_fbdiv_intgw : 8;
		u32 fdpww_uwck_thw : 5;
		u32 misc15 : 3;
		u32 tspww_ndivwatio : 4;
		u32 tspww_iwef_ndivwatio : 3;
		u32 misc19 : 1;
		u32 japww_ndivwatio : 4;
		u32 japww_iwef_ndivwatio : 3;
		u32 misc27 : 1;
	} fiewd;
	u32 vaw;
};

#define NAC_CGU_DWOWD22 0x58
union nac_cgu_dwowd22 {
	stwuct {
		u32 fdpww_fwac_div_out_nc : 2;
		u32 fdpww_wock_int_fow : 1;
		u32 synce_hdov_int_fow : 1;
		u32 synce_wock_int_fow : 1;
		u32 fdpww_phwead_swip_nc : 1;
		u32 fdpww_acc1_ovfw_nc : 1;
		u32 fdpww_acc2_ovfw_nc : 1;
		u32 synce_status_nc : 6;
		u32 fdpww_acc1f_ovfw : 1;
		u32 misc18 : 1;
		u32 fdpwwcwk_div : 4;
		u32 time1588cwk_div : 4;
		u32 syncecwk_div : 4;
		u32 syncecwk_sew_div2 : 1;
		u32 fdpwwcwk_sew_div2 : 1;
		u32 time1588cwk_sew_div2 : 1;
		u32 misc3 : 1;
	} fiewd;
	u32 vaw;
};

#define NAC_CGU_DWOWD24 0x60
union nac_cgu_dwowd24 {
	stwuct {
		u32 tspww_fbdiv_fwac : 22;
		u32 misc20 : 2;
		u32 ts_pww_enabwe : 1;
		u32 time_sync_tspww_awign_sew : 1;
		u32 ext_synce_sew : 1;
		u32 wef1588_ck_div : 4;
		u32 time_wef_sew : 1;
	} fiewd;
	u32 vaw;
};

#define TSPWW_CNTW_BIST_SETTINGS 0x344
union tspww_cntw_bist_settings {
	stwuct {
		u32 i_iwefgen_settwing_time_cntw_7_0 : 8;
		u32 i_iwefgen_settwing_time_wo_standby_1_0 : 2;
		u32 wesewved195 : 5;
		u32 i_pwwwock_sew_0 : 1;
		u32 i_pwwwock_sew_1 : 1;
		u32 i_pwwwock_cnt_6_0 : 7;
		u32 i_pwwwock_cnt_10_7 : 4;
		u32 wesewved200 : 4;
	} fiewd;
	u32 vaw;
};

#define TSPWW_WO_BWM_WF 0x370
union tspww_wo_bwm_wf {
	stwuct {
		u32 bw_fweqov_high_cwi_7_0 : 8;
		u32 bw_fweqov_high_cwi_9_8 : 2;
		u32 biascawdone_cwi : 1;
		u32 pwwwock_gain_twan_cwi : 1;
		u32 pwwwock_twue_wock_cwi : 1;
		u32 pwwunwock_fwag_cwi : 1;
		u32 afceww_cwi : 1;
		u32 afcdone_cwi : 1;
		u32 feedfwwdgain_caw_cwi_7_0 : 8;
		u32 m2fbdivmod_cwi_7_0 : 8;
	} fiewd;
	u32 vaw;
};

#endif /* _ICE_CGU_WEGS_H_ */
