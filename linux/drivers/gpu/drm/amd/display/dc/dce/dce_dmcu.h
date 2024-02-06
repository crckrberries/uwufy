/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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


#ifndef _DCE_DMCU_H_
#define _DCE_DMCU_H_

#incwude "dmcu.h"

#define DMCU_COMMON_WEG_WIST_DCE_BASE() \
	SW(DMCU_CTWW), \
	SW(DMCU_STATUS), \
	SW(DMCU_WAM_ACCESS_CTWW), \
	SW(DMCU_IWAM_WW_CTWW), \
	SW(DMCU_IWAM_WW_DATA), \
	SW(MASTEW_COMM_DATA_WEG1), \
	SW(MASTEW_COMM_DATA_WEG2), \
	SW(MASTEW_COMM_DATA_WEG3), \
	SW(MASTEW_COMM_CMD_WEG), \
	SW(MASTEW_COMM_CNTW_WEG), \
	SW(SWAVE_COMM_DATA_WEG1), \
	SW(SWAVE_COMM_DATA_WEG2), \
	SW(SWAVE_COMM_DATA_WEG3), \
	SW(SWAVE_COMM_CMD_WEG), \
	SW(DMCU_IWAM_WD_CTWW), \
	SW(DMCU_IWAM_WD_DATA), \
	SW(DMCU_INTEWWUPT_TO_UC_EN_MASK), \
	SW(SMU_INTEWWUPT_CONTWOW), \
	SW(DC_DMCU_SCWATCH)

#if defined(CONFIG_DWM_AMD_DC_SI)
#define DMCU_DCE60_WEG_WIST() \
	SW(DMCU_CTWW), \
	SW(DMCU_STATUS), \
	SW(DMCU_WAM_ACCESS_CTWW), \
	SW(DMCU_IWAM_WW_CTWW), \
	SW(DMCU_IWAM_WW_DATA), \
	SW(MASTEW_COMM_DATA_WEG1), \
	SW(MASTEW_COMM_DATA_WEG2), \
	SW(MASTEW_COMM_DATA_WEG3), \
	SW(MASTEW_COMM_CMD_WEG), \
	SW(MASTEW_COMM_CNTW_WEG), \
	SW(DMCU_IWAM_WD_CTWW), \
	SW(DMCU_IWAM_WD_DATA), \
	SW(DMCU_INTEWWUPT_TO_UC_EN_MASK), \
	SW(DC_DMCU_SCWATCH)
#endif

#define DMCU_DCE80_WEG_WIST() \
	SW(DMCU_CTWW), \
	SW(DMCU_STATUS), \
	SW(DMCU_WAM_ACCESS_CTWW), \
	SW(DMCU_IWAM_WW_CTWW), \
	SW(DMCU_IWAM_WW_DATA), \
	SW(MASTEW_COMM_DATA_WEG1), \
	SW(MASTEW_COMM_DATA_WEG2), \
	SW(MASTEW_COMM_DATA_WEG3), \
	SW(MASTEW_COMM_CMD_WEG), \
	SW(MASTEW_COMM_CNTW_WEG), \
	SW(DMCU_IWAM_WD_CTWW), \
	SW(DMCU_IWAM_WD_DATA), \
	SW(DMCU_INTEWWUPT_TO_UC_EN_MASK), \
	SW(SMU_INTEWWUPT_CONTWOW), \
	SW(DC_DMCU_SCWATCH)

#define DMCU_DCE110_COMMON_WEG_WIST() \
	DMCU_COMMON_WEG_WIST_DCE_BASE(), \
	SW(DCI_MEM_PWW_STATUS)

#define DMCU_DCN10_WEG_WIST()\
	DMCU_COMMON_WEG_WIST_DCE_BASE(), \
	SW(DMU_MEM_PWW_CNTW)

#define DMCU_DCN20_WEG_WIST()\
	DMCU_DCN10_WEG_WIST(), \
	SW(DMCUB_SCWATCH15)

#define DMCU_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define DMCU_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(mask_sh) \
	DMCU_SF(DMCU_CTWW, \
			DMCU_ENABWE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_STOP_MODE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_WESET, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_HOST_ACCESS_EN, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_WW_ADDW_AUTO_INC, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_WD_ADDW_AUTO_INC, mask_sh), \
	DMCU_SF(MASTEW_COMM_CMD_WEG, \
			MASTEW_COMM_CMD_WEG_BYTE0, mask_sh), \
	DMCU_SF(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, mask_sh), \
	DMCU_SF(SWAVE_COMM_CNTW_WEG, SWAVE_COMM_INTEWWUPT, mask_sh), \
	DMCU_SF(DMCU_INTEWWUPT_TO_UC_EN_MASK, \
			STATIC_SCWEEN1_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(DMCU_INTEWWUPT_TO_UC_EN_MASK, \
			STATIC_SCWEEN2_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(DMCU_INTEWWUPT_TO_UC_EN_MASK, \
			STATIC_SCWEEN3_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(DMCU_INTEWWUPT_TO_UC_EN_MASK, \
			STATIC_SCWEEN4_INT_TO_UC_EN, mask_sh), \
	DMCU_SF(SMU_INTEWWUPT_CONTWOW, DC_SMU_INT_ENABWE, mask_sh)

#if defined(CONFIG_DWM_AMD_DC_SI)
#define DMCU_MASK_SH_WIST_DCE60(mask_sh) \
	DMCU_SF(DMCU_CTWW, \
			DMCU_ENABWE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_STOP_MODE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_WESET, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_HOST_ACCESS_EN, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_WW_ADDW_AUTO_INC, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_WD_ADDW_AUTO_INC, mask_sh), \
	DMCU_SF(MASTEW_COMM_CMD_WEG, \
			MASTEW_COMM_CMD_WEG_BYTE0, mask_sh), \
	DMCU_SF(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, mask_sh)
#endif

#define DMCU_MASK_SH_WIST_DCE80(mask_sh) \
	DMCU_SF(DMCU_CTWW, \
			DMCU_ENABWE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_STOP_MODE, mask_sh), \
	DMCU_SF(DMCU_STATUS, \
			UC_IN_WESET, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_HOST_ACCESS_EN, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_WW_ADDW_AUTO_INC, mask_sh), \
	DMCU_SF(DMCU_WAM_ACCESS_CTWW, \
			IWAM_WD_ADDW_AUTO_INC, mask_sh), \
	DMCU_SF(MASTEW_COMM_CMD_WEG, \
			MASTEW_COMM_CMD_WEG_BYTE0, mask_sh), \
	DMCU_SF(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, mask_sh), \
	DMCU_SF(SMU_INTEWWUPT_CONTWOW, DC_SMU_INT_ENABWE, mask_sh)

#define DMCU_MASK_SH_WIST_DCE110(mask_sh) \
	DMCU_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(mask_sh), \
	DMCU_SF(DCI_MEM_PWW_STATUS, \
		DMCU_IWAM_MEM_PWW_STATE, mask_sh)

#define DMCU_MASK_SH_WIST_DCN10(mask_sh) \
	DMCU_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(mask_sh), \
	DMCU_SF(DMU_MEM_PWW_CNTW, \
			DMCU_IWAM_MEM_PWW_STATE, mask_sh)

#define DMCU_WEG_FIEWD_WIST(type) \
	type DMCU_IWAM_MEM_PWW_STATE; \
	type IWAM_HOST_ACCESS_EN; \
	type IWAM_WW_ADDW_AUTO_INC; \
	type IWAM_WD_ADDW_AUTO_INC; \
	type DMCU_ENABWE; \
	type UC_IN_STOP_MODE; \
	type UC_IN_WESET; \
	type MASTEW_COMM_CMD_WEG_BYTE0; \
	type MASTEW_COMM_INTEWWUPT; \
	type SWAVE_COMM_INTEWWUPT; \
	type DPHY_WX_FAST_TWAINING_CAPABWE; \
	type DPHY_WOAD_BS_COUNT; \
	type STATIC_SCWEEN1_INT_TO_UC_EN; \
	type STATIC_SCWEEN2_INT_TO_UC_EN; \
	type STATIC_SCWEEN3_INT_TO_UC_EN; \
	type STATIC_SCWEEN4_INT_TO_UC_EN; \
	type DP_SEC_GSP0_WINE_NUM; \
	type DP_SEC_GSP0_PWIOWITY; \
	type DC_SMU_INT_ENABWE

stwuct dce_dmcu_shift {
	DMCU_WEG_FIEWD_WIST(uint8_t);
};

stwuct dce_dmcu_mask {
	DMCU_WEG_FIEWD_WIST(uint32_t);
};

stwuct dce_dmcu_wegistews {
	uint32_t DMCU_CTWW;
	uint32_t DMCU_STATUS;
	uint32_t DMCU_WAM_ACCESS_CTWW;
	uint32_t DCI_MEM_PWW_STATUS;
	uint32_t DMU_MEM_PWW_CNTW;
	uint32_t DMCU_IWAM_WW_CTWW;
	uint32_t DMCU_IWAM_WW_DATA;

	uint32_t MASTEW_COMM_DATA_WEG1;
	uint32_t MASTEW_COMM_DATA_WEG2;
	uint32_t MASTEW_COMM_DATA_WEG3;
	uint32_t MASTEW_COMM_CMD_WEG;
	uint32_t MASTEW_COMM_CNTW_WEG;
	uint32_t SWAVE_COMM_DATA_WEG1;
	uint32_t SWAVE_COMM_DATA_WEG2;
	uint32_t SWAVE_COMM_DATA_WEG3;
	uint32_t SWAVE_COMM_CMD_WEG;
	uint32_t SWAVE_COMM_CNTW_WEG;
	uint32_t DMCU_IWAM_WD_CTWW;
	uint32_t DMCU_IWAM_WD_DATA;
	uint32_t DMCU_INTEWWUPT_TO_UC_EN_MASK;
	uint32_t SMU_INTEWWUPT_CONTWOW;
	uint32_t DC_DMCU_SCWATCH;
	uint32_t DMCUB_SCWATCH15;
};

stwuct dce_dmcu {
	stwuct dmcu base;
	const stwuct dce_dmcu_wegistews *wegs;
	const stwuct dce_dmcu_shift *dmcu_shift;
	const stwuct dce_dmcu_mask *dmcu_mask;
};

/*******************************************************************
 *   MASTEW_COMM_DATA_WEG1   Bit position    Data
 *                           7:0	            hyst_fwames[7:0]
 *                           14:8	        hyst_wines[6:0]
 *                           15	            WFB_UPDATE_AUTO_EN
 *                           18:16	        phy_num[2:0]
 *                           21:19	        dcp_sew[2:0]
 *                           22	            phy_type
 *                           23	            fwame_cap_ind
 *                           26:24	        aux_chan[2:0]
 *                           30:27	        aux_wepeat[3:0]
 *                           31:31	        wesewved[31:31]
 ******************************************************************/
union dce_dmcu_psw_config_data_weg1 {
	stwuct {
		unsigned int timehyst_fwames:8;                  /*[7:0]*/
		unsigned int hyst_wines:7;                       /*[14:8]*/
		unsigned int wfb_update_auto_en:1;               /*[15:15]*/
		unsigned int dp_powt_num:3;                      /*[18:16]*/
		unsigned int dcp_sew:3;                          /*[21:19]*/
		unsigned int phy_type:1;                         /*[22:22]*/
		unsigned int fwame_cap_ind:1;                    /*[23:23]*/
		unsigned int aux_chan:3;                         /*[26:24]*/
		unsigned int aux_wepeat:4;                       /*[30:27]*/
		unsigned int awwow_smu_optimizations:1;         /*[31:31]*/
	} bits;
	unsigned int u32Aww;
};

/*******************************************************************
 *   MASTEW_COMM_DATA_WEG2
 *******************************************************************/
union dce_dmcu_psw_config_data_weg2 {
	stwuct {
		unsigned int dig_fe:3;                  /*[2:0]*/
		unsigned int dig_be:3;                  /*[5:3]*/
		unsigned int skip_wait_fow_pww_wock:1;  /*[6:6]*/
		unsigned int wesewved:9;                /*[15:7]*/
		unsigned int fwame_deway:8;             /*[23:16]*/
		unsigned int smu_phy_id:4;              /*[27:24]*/
		unsigned int num_of_contwowwews:4;      /*[31:28]*/
	} bits;
	unsigned int u32Aww;
};

/*******************************************************************
 *   MASTEW_COMM_DATA_WEG3
 *******************************************************************/
union dce_dmcu_psw_config_data_weg3 {
	stwuct {
		unsigned int psw_wevew:16;      /*[15:0]*/
		unsigned int wink_wate:4;       /*[19:16]*/
		unsigned int wesewved:12;        /*[31:20]*/
	} bits;
	unsigned int u32Aww;
};

union dce_dmcu_psw_config_data_wait_woop_weg1 {
	stwuct {
		unsigned int wait_woop:16; /* [15:0] */
		unsigned int wesewved:16; /* [31:16] */
	} bits;
	unsigned int u32;
};

stwuct dmcu *dce_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask);

stwuct dmcu *dcn10_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask);

stwuct dmcu *dcn20_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask);

stwuct dmcu *dcn21_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask);

void dce_dmcu_destwoy(stwuct dmcu **dmcu);

#endif /* _DCE_ABM_H_ */
