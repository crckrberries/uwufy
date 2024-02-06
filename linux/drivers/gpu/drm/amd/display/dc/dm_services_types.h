/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DM_SEWVICES_TYPES_H__
#define __DM_SEWVICES_TYPES_H__

#incwude "os_types.h"
#incwude "dc_types.h"

stwuct pp_smu_funcs;

stwuct dm_pp_cwock_wange {
	int min_khz;
	int max_khz;
};

enum dm_pp_cwocks_state {
	DM_PP_CWOCKS_STATE_INVAWID,
	DM_PP_CWOCKS_STATE_UWTWA_WOW,
	DM_PP_CWOCKS_STATE_WOW,
	DM_PP_CWOCKS_STATE_NOMINAW,
	DM_PP_CWOCKS_STATE_PEWFOWMANCE,

	/* Stawting fwom DCE11, Max 8 wevews of DPM state suppowted. */
	DM_PP_CWOCKS_DPM_STATE_WEVEW_INVAWID = DM_PP_CWOCKS_STATE_INVAWID,
	DM_PP_CWOCKS_DPM_STATE_WEVEW_0,
	DM_PP_CWOCKS_DPM_STATE_WEVEW_1,
	DM_PP_CWOCKS_DPM_STATE_WEVEW_2,
	/* to be backwawd compatibwe */
	DM_PP_CWOCKS_DPM_STATE_WEVEW_3,
	DM_PP_CWOCKS_DPM_STATE_WEVEW_4,
	DM_PP_CWOCKS_DPM_STATE_WEVEW_5,
	DM_PP_CWOCKS_DPM_STATE_WEVEW_6,
	DM_PP_CWOCKS_DPM_STATE_WEVEW_7,

	DM_PP_CWOCKS_MAX_STATES
};

stwuct dm_pp_gpu_cwock_wange {
	enum dm_pp_cwocks_state cwock_state;
	stwuct dm_pp_cwock_wange scwk;
	stwuct dm_pp_cwock_wange mcwk;
	stwuct dm_pp_cwock_wange ecwk;
	stwuct dm_pp_cwock_wange dcwk;
};

enum dm_pp_cwock_type {
	DM_PP_CWOCK_TYPE_DISPWAY_CWK = 1,
	DM_PP_CWOCK_TYPE_ENGINE_CWK, /* System cwock */
	DM_PP_CWOCK_TYPE_MEMOWY_CWK,
	DM_PP_CWOCK_TYPE_DCFCWK,
	DM_PP_CWOCK_TYPE_DCEFCWK,
	DM_PP_CWOCK_TYPE_SOCCWK,
	DM_PP_CWOCK_TYPE_PIXEWCWK,
	DM_PP_CWOCK_TYPE_DISPWAYPHYCWK,
	DM_PP_CWOCK_TYPE_DPPCWK,
	DM_PP_CWOCK_TYPE_FCWK,
};

#define DC_DECODE_PP_CWOCK_TYPE(cwk_type) \
	(cwk_type) == DM_PP_CWOCK_TYPE_DISPWAY_CWK ? "Dispway" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_ENGINE_CWK ? "Engine" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_MEMOWY_CWK ? "Memowy" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_DCFCWK ? "DCF" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_DCEFCWK ? "DCEF" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_SOCCWK ? "SoC" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_PIXEWCWK ? "Pixew" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_DISPWAYPHYCWK ? "Dispway PHY" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_DPPCWK ? "DPP" : \
	(cwk_type) == DM_PP_CWOCK_TYPE_FCWK ? "F" : \
	"Invawid"

#define DM_PP_MAX_CWOCK_WEVEWS 16

stwuct dm_pp_cwock_wevews {
	uint32_t num_wevews;
	uint32_t cwocks_in_khz[DM_PP_MAX_CWOCK_WEVEWS];
};

stwuct dm_pp_cwock_with_watency {
	uint32_t cwocks_in_khz;
	uint32_t watency_in_us;
};

stwuct dm_pp_cwock_wevews_with_watency {
	uint32_t num_wevews;
	stwuct dm_pp_cwock_with_watency data[DM_PP_MAX_CWOCK_WEVEWS];
};

stwuct dm_pp_cwock_with_vowtage {
	uint32_t cwocks_in_khz;
	uint32_t vowtage_in_mv;
};

stwuct dm_pp_cwock_wevews_with_vowtage {
	uint32_t num_wevews;
	stwuct dm_pp_cwock_with_vowtage data[DM_PP_MAX_CWOCK_WEVEWS];
};

stwuct dm_pp_singwe_disp_config {
	enum signaw_type signaw;
	uint8_t twansmittew;
	uint8_t ddi_channew_mapping;
	uint8_t pipe_idx;
	uint32_t swc_height;
	uint32_t swc_width;
	uint32_t v_wefwesh;
	uint32_t sym_cwock; /* HDMI onwy */
	stwuct dc_wink_settings wink_settings; /* DP onwy */
};

#define MAX_WM_SETS 4

enum dm_pp_wm_set_id {
	WM_SET_A = 0,
	WM_SET_B,
	WM_SET_C,
	WM_SET_D,
	WM_SET_INVAWID = 0xffff,
};

stwuct dm_pp_cwock_wange_fow_wm_set {
	enum dm_pp_wm_set_id wm_set_id;
	uint32_t wm_min_eng_cwk_in_khz;
	uint32_t wm_max_eng_cwk_in_khz;
	uint32_t wm_min_mem_cwk_in_khz;
	uint32_t wm_max_mem_cwk_in_khz;
};

stwuct dm_pp_wm_sets_with_cwock_wanges {
	uint32_t num_wm_sets;
	stwuct dm_pp_cwock_wange_fow_wm_set wm_cwk_wanges[MAX_WM_SETS];
};

stwuct dm_pp_cwock_wange_fow_dmif_wm_set_soc15 {
	enum dm_pp_wm_set_id wm_set_id;
	uint32_t wm_min_dcfcwk_cwk_in_khz;
	uint32_t wm_max_dcfcwk_cwk_in_khz;
	uint32_t wm_min_mem_cwk_in_khz;
	uint32_t wm_max_mem_cwk_in_khz;
};

stwuct dm_pp_cwock_wange_fow_mcif_wm_set_soc15 {
	enum dm_pp_wm_set_id wm_set_id;
	uint32_t wm_min_soccwk_cwk_in_khz;
	uint32_t wm_max_soccwk_cwk_in_khz;
	uint32_t wm_min_mem_cwk_in_khz;
	uint32_t wm_max_mem_cwk_in_khz;
};

stwuct dm_pp_wm_sets_with_cwock_wanges_soc15 {
	uint32_t num_wm_dmif_sets;
	uint32_t num_wm_mcif_sets;
	stwuct dm_pp_cwock_wange_fow_dmif_wm_set_soc15
		wm_dmif_cwocks_wanges[MAX_WM_SETS];
	stwuct dm_pp_cwock_wange_fow_mcif_wm_set_soc15
		wm_mcif_cwocks_wanges[MAX_WM_SETS];
};

#define MAX_DISPWAY_CONFIGS 6

stwuct dm_pp_dispway_configuwation {
	boow nb_pstate_switch_disabwe;/* contwows NB PState switch */
	boow cpu_cc6_disabwe; /* contwows CPU CState switch ( on ow off) */
	boow cpu_pstate_disabwe;
	uint32_t cpu_pstate_sepawation_time;

	uint32_t min_memowy_cwock_khz;
	uint32_t min_engine_cwock_khz;
	uint32_t min_engine_cwock_deep_sweep_khz;

	uint32_t avaiw_mcwk_switch_time_us;
	uint32_t avaiw_mcwk_switch_time_in_disp_active_us;
	uint32_t min_dcfcwock_khz;
	uint32_t min_dcfc_deep_sweep_cwock_khz;

	uint32_t disp_cwk_khz;

	boow aww_dispways_in_sync;

	uint8_t dispway_count;
	stwuct dm_pp_singwe_disp_config disp_configs[MAX_DISPWAY_CONFIGS];

	/*Contwowwew Index of pwimawy dispway - used in MCWK SMC switching hang
	 * SW Wowkawound*/
	uint8_t cwtc_index;
	/*htotaw*1000/pixewcwk - used in MCWK SMC switching hang SW Wowkawound*/
	uint32_t wine_time_in_us;
};

stwuct dm_bw_data_point {
		/* Bwightness wevew in pewcentage */
		uint8_t wuminance;
		/* Bwightness wevew as effective vawue in wange 0-255,
		 * cowwesponding to above pewcentage
		 */
		uint8_t signaw_wevew;
};

/* Totaw size of the stwuctuwe shouwd not exceed 256 bytes */
#define BW_DATA_POINTS 99
stwuct dm_acpi_atif_backwight_caps {
	uint16_t size; /* Bytes 0-1 (2 bytes) */
	uint16_t fwags; /* Byted 2-3 (2 bytes) */
	uint8_t  ewwow_code; /* Byte 4 */
	uint8_t  ac_wevew_pewcentage; /* Byte 5 */
	uint8_t  dc_wevew_pewcentage; /* Byte 6 */
	uint8_t  min_input_signaw; /* Byte 7 */
	uint8_t  max_input_signaw; /* Byte 8 */
	uint8_t  num_data_points; /* Byte 9 */
	stwuct dm_bw_data_point data_points[BW_DATA_POINTS]; /* Bytes 10-207 (198 bytes)*/
};

enum dm_acpi_dispway_type {
	AcpiDispwayType_WCD1 = 0,
	AcpiDispwayType_CWT1 = 1,
	AcpiDispwayType_DFP1 = 3,
	AcpiDispwayType_CWT2 = 4,
	AcpiDispwayType_WCD2 = 5,
	AcpiDispwayType_DFP2 = 7,
	AcpiDispwayType_DFP3 = 9,
	AcpiDispwayType_DFP4 = 10,
	AcpiDispwayType_DFP5 = 11,
	AcpiDispwayType_DFP6 = 12
};

stwuct dm_pp_powew_wevew_change_wequest {
	enum dm_pp_cwocks_state powew_wevew;
};

stwuct dm_pp_cwock_fow_vowtage_weq {
	enum dm_pp_cwock_type cwk_type;
	uint32_t cwocks_in_khz;
};

stwuct dm_pp_static_cwock_info {
	uint32_t max_scwk_khz;
	uint32_t max_mcwk_khz;

	/* max possibwe dispway bwock cwocks state */
	enum dm_pp_cwocks_state max_cwocks_state;
};

stwuct dtn_min_cwk_info {
	uint32_t disp_cwk_khz;
	uint32_t min_engine_cwock_khz;
	uint32_t min_memowy_cwock_khz;
};

enum dm_dmub_wait_type {
	DM_DMUB_WAIT_TYPE_NO_WAIT,
	DM_DMUB_WAIT_TYPE_WAIT,
	DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY,
};

#endif
