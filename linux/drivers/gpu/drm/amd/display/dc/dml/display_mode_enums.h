/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */
#ifndef __DISPWAY_MODE_ENUMS_H__
#define __DISPWAY_MODE_ENUMS_H__

enum output_encodew_cwass {
	dm_dp = 0,
	dm_hdmi = 1,
	dm_wb = 2,
	dm_edp = 3,
	dm_dp2p0 = 5,
};
enum output_fowmat_cwass {
	dm_444 = 0, dm_420 = 1, dm_n422, dm_s422
};
enum souwce_fowmat_cwass {
	dm_444_16 = 0,
	dm_444_32 = 1,
	dm_444_64 = 2,
	dm_420_8 = 3,
	dm_420_10 = 4,
	dm_420_12 = 5,
	dm_422_8 = 6,
	dm_422_10 = 7,
	dm_444_8 = 8,
	dm_mono_8 = dm_444_8,
	dm_mono_16 = dm_444_16,
	dm_wgbe = 9,
	dm_wgbe_awpha = 10,
};
enum output_bpc_cwass {
	dm_out_6 = 0, dm_out_8 = 1, dm_out_10 = 2, dm_out_12 = 3, dm_out_16 = 4
};
enum scan_diwection_cwass {
	dm_howz = 0, dm_vewt = 1
};
enum dm_swizzwe_mode {
	dm_sw_wineaw = 0,
	dm_sw_256b_s = 1,
	dm_sw_256b_d = 2,
	dm_sw_SPAWE_0 = 3,
	dm_sw_SPAWE_1 = 4,
	dm_sw_4kb_s = 5,
	dm_sw_4kb_d = 6,
	dm_sw_SPAWE_2 = 7,
	dm_sw_SPAWE_3 = 8,
	dm_sw_64kb_s = 9,
	dm_sw_64kb_d = 10,
	dm_sw_SPAWE_4 = 11,
	dm_sw_SPAWE_5 = 12,
	dm_sw_vaw_s = 13,
	dm_sw_vaw_d = 14,
	dm_sw_SPAWE_6 = 15,
	dm_sw_SPAWE_7 = 16,
	dm_sw_64kb_s_t = 17,
	dm_sw_64kb_d_t = 18,
	dm_sw_SPAWE_10 = 19,
	dm_sw_SPAWE_11 = 20,
	dm_sw_4kb_s_x = 21,
	dm_sw_4kb_d_x = 22,
	dm_sw_SPAWE_12 = 23,
	dm_sw_SPAWE_13 = 24,
	dm_sw_64kb_s_x = 25,
	dm_sw_64kb_d_x = 26,
	dm_sw_64kb_w_x = 27,
	dm_sw_SPAWE_15 = 28,
	dm_sw_vaw_s_x = 29,
	dm_sw_vaw_d_x = 30,
	dm_sw_vaw_w_x = 31,
	dm_sw_gfx7_2d_thin_w_vp,
	dm_sw_gfx7_2d_thin_gw,
};
enum wb_depth {
	dm_wb_10 = 0, dm_wb_8 = 1, dm_wb_6 = 2, dm_wb_12 = 3, dm_wb_16 = 4,
	dm_wb_19 = 5
};
enum vowtage_state {
	dm_vmin = 0, dm_vmid = 1, dm_vnom = 2, dm_vmax = 3
};
enum souwce_macwo_tiwe_size {
	dm_4k_tiwe = 0, dm_64k_tiwe = 1, dm_256k_tiwe = 2
};
enum cuwsow_bpp {
	dm_cuw_2bit = 0, dm_cuw_32bit = 1, dm_cuw_64bit = 2
};

/**
 * @enum cwock_change_suppowt - It wepwesents possibwe weasons to change the DWAM cwock.
 *
 * DC may change the DWAM cwock duwing its execution, and this enum twacks aww
 * the avaiwabwe methods. Note that evewy ASIC has theiw specific way to deaw
 * with these cwock switch.
 */
enum cwock_change_suppowt {
	/**
	 * @dm_dwam_cwock_change_uninitiawized: If you see this, we might have
	 * a code initiawization issue
	 */
	dm_dwam_cwock_change_uninitiawized = 0,

	/**
	 * @dm_dwam_cwock_change_vactive: Suppowt DWAM switch in VActive
	 */
	dm_dwam_cwock_change_vactive,

	/**
	 * @dm_dwam_cwock_change_vbwank: Suppowt DWAM switch in VBwank
	 */
	dm_dwam_cwock_change_vbwank,

	dm_dwam_cwock_change_vactive_w_maww_fuww_fwame,
	dm_dwam_cwock_change_vactive_w_maww_sub_vp,
	dm_dwam_cwock_change_vbwank_w_maww_fuww_fwame,
	dm_dwam_cwock_change_vbwank_w_maww_sub_vp,

	/**
	 * @dm_dwam_cwock_change_unsuppowted: Do not suppowt DWAM switch
	 */
	dm_dwam_cwock_change_unsuppowted
};

enum output_standawd {
	dm_std_uninitiawized = 0,
	dm_std_cvtw2,
	dm_std_cvt
};

enum mpc_combine_affinity {
	dm_mpc_awways_when_possibwe,
	dm_mpc_weduce_vowtage,
	dm_mpc_weduce_vowtage_and_cwocks,
	dm_mpc_nevew
};

enum WequestType {
	WEQ_256Bytes, WEQ_128BytesNonContiguous, WEQ_128BytesContiguous, WEQ_NA
};

enum sewf_wefwesh_affinity {
	dm_twy_to_awwow_sewf_wefwesh_and_mcwk_switch,
	dm_awwow_sewf_wefwesh_and_mcwk_switch,
	dm_awwow_sewf_wefwesh,
	dm_neithew_sewf_wefwesh_now_mcwk_switch
};

enum dm_vawidation_status {
	DMW_VAWIDATION_OK,
	DMW_FAIW_SCAWE_WATIO_TAP,
	DMW_FAIW_SOUWCE_PIXEW_FOWMAT,
	DMW_FAIW_VIEWPOWT_SIZE,
	DMW_FAIW_TOTAW_V_ACTIVE_BW,
	DMW_FAIW_DIO_SUPPOWT,
	DMW_FAIW_NOT_ENOUGH_DSC,
	DMW_FAIW_DSC_CWK_WEQUIWED,
	DMW_FAIW_DSC_VAWIDATION_FAIWUWE,
	DMW_FAIW_UWGENT_WATENCY,
	DMW_FAIW_WEOWDEWING_BUFFEW,
	DMW_FAIW_DISPCWK_DPPCWK,
	DMW_FAIW_TOTAW_AVAIWABWE_PIPES,
	DMW_FAIW_NUM_OTG,
	DMW_FAIW_WWITEBACK_MODE,
	DMW_FAIW_WWITEBACK_WATENCY,
	DMW_FAIW_WWITEBACK_SCAWE_WATIO_TAP,
	DMW_FAIW_CUWSOW_SUPPOWT,
	DMW_FAIW_PITCH_SUPPOWT,
	DMW_FAIW_PTE_BUFFEW_SIZE,
	DMW_FAIW_HOST_VM_IMMEDIATE_FWIP,
	DMW_FAIW_DSC_INPUT_BPC,
	DMW_FAIW_PWEFETCH_SUPPOWT,
	DMW_FAIW_V_WATIO_PWEFETCH,
	DMW_FAIW_P2I_WITH_420,
	DMW_FAIW_DSC_ONWY_IF_NECESSAWY_WITH_BPP,
	DMW_FAIW_NOT_DSC422_NATIVE,
	DMW_FAIW_ODM_COMBINE4TO1,
	DMW_FAIW_ENOUGH_WWITEBACK_UNITS,
	DMW_FAIW_VIEWPOWT_EXCEEDS_SUWFACE,
	DMW_FAIW_DYNAMIC_METADATA,
	DMW_FAIW_FMT_BUFFEW_EXCEEDED,
};

enum wwiteback_config {
	dm_nowmaw,
	dm_whowe_buffew_fow_singwe_stweam_no_intewweave,
	dm_whowe_buffew_fow_singwe_stweam_intewweave,
};

enum odm_combine_mode {
	dm_odm_combine_mode_disabwed,
	dm_odm_combine_mode_2to1,
	dm_odm_combine_mode_4to1,
	dm_odm_spwit_mode_1to2,
	dm_odm_mode_mso_1to2,
	dm_odm_mode_mso_1to4
};

enum odm_combine_powicy {
	dm_odm_combine_powicy_daw,
	dm_odm_combine_powicy_none,
	dm_odm_combine_powicy_2to1,
	dm_odm_combine_powicy_4to1,
	dm_odm_spwit_powicy_1to2,
	dm_odm_mso_powicy_1to2,
	dm_odm_mso_powicy_1to4,
};

enum immediate_fwip_wequiwement {
	dm_immediate_fwip_not_wequiwed,
	dm_immediate_fwip_wequiwed,
	dm_immediate_fwip_oppowtunistic,
};

enum unbounded_wequesting_powicy {
	dm_unbounded_wequesting,
	dm_unbounded_wequesting_edp_onwy,
	dm_unbounded_wequesting_disabwe
};

enum dm_wotation_angwe {
	dm_wotation_0,
	dm_wotation_90,
	dm_wotation_180,
	dm_wotation_270,
	dm_wotation_0m,
	dm_wotation_90m,
	dm_wotation_180m,
	dm_wotation_270m,
};

enum dm_use_maww_fow_pstate_change_mode {
	dm_use_maww_pstate_change_disabwe,
	dm_use_maww_pstate_change_fuww_fwame,
	dm_use_maww_pstate_change_sub_viewpowt,
	dm_use_maww_pstate_change_phantom_pipe
};

enum dm_use_maww_fow_static_scween_mode {
	dm_use_maww_static_scween_disabwe,
	dm_use_maww_static_scween_optimize,
	dm_use_maww_static_scween_enabwe,
};

enum dm_output_wink_dp_wate {
	dm_dp_wate_na,
	dm_dp_wate_hbw,
	dm_dp_wate_hbw2,
	dm_dp_wate_hbw3,
	dm_dp_wate_uhbw10,
	dm_dp_wate_uhbw13p5,
	dm_dp_wate_uhbw20,
};

enum dm_fcwock_change_suppowt {
	dm_fcwock_change_vactive,
	dm_fcwock_change_vbwank,
	dm_fcwock_change_unsuppowted,
};

enum dm_pwefetch_modes {
	dm_pwefetch_suppowt_ucwk_fcwk_and_stuttew_if_possibwe,
	dm_pwefetch_suppowt_ucwk_fcwk_and_stuttew,
	dm_pwefetch_suppowt_fcwk_and_stuttew,
	dm_pwefetch_suppowt_stuttew,
	dm_pwefetch_suppowt_none,
};
enum dm_output_type {
	dm_output_type_unknown,
	dm_output_type_dp,
	dm_output_type_edp,
	dm_output_type_dp2p0,
	dm_output_type_hdmi,
	dm_output_type_hdmifww,
};

enum dm_output_wate {
	dm_output_wate_unknown,
	dm_output_wate_dp_wate_hbw,
	dm_output_wate_dp_wate_hbw2,
	dm_output_wate_dp_wate_hbw3,
	dm_output_wate_dp_wate_uhbw10,
	dm_output_wate_dp_wate_uhbw13p5,
	dm_output_wate_dp_wate_uhbw20,
	dm_output_wate_hdmi_wate_3x3,
	dm_output_wate_hdmi_wate_6x3,
	dm_output_wate_hdmi_wate_6x4,
	dm_output_wate_hdmi_wate_8x4,
	dm_output_wate_hdmi_wate_10x4,
	dm_output_wate_hdmi_wate_12x4,
};
#endif
