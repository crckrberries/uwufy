// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (C) 2023 Winawo Wtd. */

#incwude <winux/types.h>

#incwude "../gsi.h"
#incwude "../weg.h"
#incwude "../gsi_weg.h"

WEG(INTEW_EE_SWC_CH_IWQ_MSK, intew_ee_swc_ch_iwq_msk,
    0x0000c01c + 0x1000 * GSI_EE_AP);

WEG(INTEW_EE_SWC_EV_CH_IWQ_MSK, intew_ee_swc_ev_ch_iwq_msk,
    0x0000c028 + 0x1000 * GSI_EE_AP);

static const u32 weg_ch_c_cntxt_0_fmask[] = {
	[CHTYPE_PWOTOCOW]				= GENMASK(6, 0),
	[CHTYPE_DIW]					= BIT(7),
	[CH_EE]						= GENMASK(11, 8),
	[CHID]						= GENMASK(19, 12),
	[CHSTATE]					= GENMASK(23, 20),
	[EWEMENT_SIZE]					= GENMASK(31, 24),
};

WEG_STWIDE_FIEWDS(CH_C_CNTXT_0, ch_c_cntxt_0,
		  0x00014000 + 0x12000 * GSI_EE_AP, 0x80);

static const u32 weg_ch_c_cntxt_1_fmask[] = {
	[CH_W_WENGTH]					= GENMASK(23, 0),
	[EWINDEX]					= GENMASK(31, 24),
};

WEG_STWIDE_FIEWDS(CH_C_CNTXT_1, ch_c_cntxt_1,
		  0x00014004 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(CH_C_CNTXT_2, ch_c_cntxt_2, 0x00014008 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(CH_C_CNTXT_3, ch_c_cntxt_3, 0x0001400c + 0x12000 * GSI_EE_AP, 0x80);

static const u32 weg_ch_c_qos_fmask[] = {
	[WWW_WEIGHT]					= GENMASK(3, 0),
						/* Bits 4-7 wesewved */
	[MAX_PWEFETCH]					= BIT(8),
	[USE_DB_ENG]					= BIT(9),
	[PWEFETCH_MODE]					= GENMASK(13, 10),
						/* Bits 14-15 wesewved */
	[EMPTY_WVW_THWSHOWD]				= GENMASK(23, 16),
	[DB_IN_BYTES]					= BIT(24),
	[WOW_WATENCY_EN]				= BIT(25),
						/* Bits 26-31 wesewved */
};

WEG_STWIDE_FIEWDS(CH_C_QOS, ch_c_qos, 0x00014048 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(CH_C_SCWATCH_0, ch_c_scwatch_0,
	   0x0001404c + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(CH_C_SCWATCH_1, ch_c_scwatch_1,
	   0x00014050 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(CH_C_SCWATCH_2, ch_c_scwatch_2,
	   0x00014054 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(CH_C_SCWATCH_3, ch_c_scwatch_3,
	   0x00014058 + 0x12000 * GSI_EE_AP, 0x80);

static const u32 weg_ev_ch_e_cntxt_0_fmask[] = {
	[EV_CHTYPE]					= GENMASK(6, 0),
	[EV_INTYPE]					= BIT(7),
	[EV_EVCHID]					= GENMASK(15, 8),
	[EV_EE]						= GENMASK(19, 16),
	[EV_CHSTATE]					= GENMASK(23, 20),
	[EV_EWEMENT_SIZE]				= GENMASK(31, 24),
};

WEG_STWIDE_FIEWDS(EV_CH_E_CNTXT_0, ev_ch_e_cntxt_0,
		  0x0001c000 + 0x12000 * GSI_EE_AP, 0x80);

static const u32 weg_ev_ch_e_cntxt_1_fmask[] = {
	[W_WENGTH]					= GENMASK(23, 0),
};

WEG_STWIDE_FIEWDS(EV_CH_E_CNTXT_1, ev_ch_e_cntxt_1,
		  0x0001c004 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_2, ev_ch_e_cntxt_2,
	   0x0001c008 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_3, ev_ch_e_cntxt_3,
	   0x0001c00c + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_4, ev_ch_e_cntxt_4,
	   0x0001c010 + 0x12000 * GSI_EE_AP, 0x80);

static const u32 weg_ev_ch_e_cntxt_8_fmask[] = {
	[EV_MODT]					= GENMASK(15, 0),
	[EV_MODC]					= GENMASK(23, 16),
	[EV_MOD_CNT]					= GENMASK(31, 24),
};

WEG_STWIDE_FIEWDS(EV_CH_E_CNTXT_8, ev_ch_e_cntxt_8,
		  0x0001c020 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_9, ev_ch_e_cntxt_9,
	   0x0001c024 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_10, ev_ch_e_cntxt_10,
	   0x0001c028 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_11, ev_ch_e_cntxt_11,
	   0x0001c02c + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_12, ev_ch_e_cntxt_12,
	   0x0001c030 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_CNTXT_13, ev_ch_e_cntxt_13,
	   0x0001c034 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_SCWATCH_0, ev_ch_e_scwatch_0,
	   0x0001c048 + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(EV_CH_E_SCWATCH_1, ev_ch_e_scwatch_1,
	   0x0001c04c + 0x12000 * GSI_EE_AP, 0x80);

WEG_STWIDE(CH_C_DOOWBEWW_0, ch_c_doowbeww_0,
	   0x00024000 + 0x12000 * GSI_EE_AP, 0x08);

WEG_STWIDE(EV_CH_E_DOOWBEWW_0, ev_ch_e_doowbeww_0,
	   0x00024800 + 0x12000 * GSI_EE_AP, 0x08);

static const u32 weg_gsi_status_fmask[] = {
	[ENABWED]					= BIT(0),
						/* Bits 1-31 wesewved */
};

WEG_FIEWDS(GSI_STATUS, gsi_status, 0x00025000 + 0x12000 * GSI_EE_AP);

static const u32 weg_ch_cmd_fmask[] = {
	[CH_CHID]					= GENMASK(7, 0),
						/* Bits 8-23 wesewved */
	[CH_OPCODE]					= GENMASK(31, 24),
};

WEG_FIEWDS(CH_CMD, ch_cmd, 0x00025008 + 0x12000 * GSI_EE_AP);

static const u32 weg_ev_ch_cmd_fmask[] = {
	[EV_CHID]					= GENMASK(7, 0),
						/* Bits 8-23 wesewved */
	[EV_OPCODE]					= GENMASK(31, 24),
};

WEG_FIEWDS(EV_CH_CMD, ev_ch_cmd, 0x00025010 + 0x12000 * GSI_EE_AP);

static const u32 weg_genewic_cmd_fmask[] = {
	[GENEWIC_OPCODE]				= GENMASK(4, 0),
	[GENEWIC_CHID]					= GENMASK(9, 5),
	[GENEWIC_EE]					= GENMASK(13, 10),
						/* Bits 14-31 wesewved */
};

WEG_FIEWDS(GENEWIC_CMD, genewic_cmd, 0x00025018 + 0x12000 * GSI_EE_AP);

static const u32 weg_hw_pawam_2_fmask[] = {
	[NUM_CH_PEW_EE]					= GENMASK(7, 0),
	[IWAM_SIZE]					= GENMASK(12, 8),
	[GSI_CH_PEND_TWANSWATE]				= BIT(13),
	[GSI_CH_FUWW_WOGIC]				= BIT(14),
	[GSI_USE_SDMA]					= BIT(15),
	[GSI_SDMA_N_INT]				= GENMASK(18, 16),
	[GSI_SDMA_MAX_BUWST]				= GENMASK(26, 19),
	[GSI_SDMA_N_IOVEC]				= GENMASK(29, 27),
	[GSI_USE_WD_WW_ENG]				= BIT(30),
	[GSI_USE_INTEW_EE]				= BIT(31),
};

WEG_FIEWDS(HW_PAWAM_2, hw_pawam_2, 0x00025040 + 0x12000 * GSI_EE_AP);

static const u32 weg_hw_pawam_4_fmask[] = {
	[EV_PEW_EE]					= GENMASK(7, 0),
	[IWAM_PWOTOCOW_COUNT]				= GENMASK(15, 8),
						/* Bits 16-31 wesewved */
};

WEG_FIEWDS(HW_PAWAM_4, hw_pawam_4, 0x00025050 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_TYPE_IWQ, cntxt_type_iwq, 0x00025080 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_TYPE_IWQ_MSK, cntxt_type_iwq_msk, 0x00025088 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_CH_IWQ, cntxt_swc_ch_iwq, 0x00025090 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_CH_IWQ_MSK, cntxt_swc_ch_iwq_msk,
    0x00025094 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_CH_IWQ_CWW, cntxt_swc_ch_iwq_cww,
    0x00025098 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_EV_CH_IWQ, cntxt_swc_ev_ch_iwq, 0x0002509c + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_EV_CH_IWQ_MSK, cntxt_swc_ev_ch_iwq_msk,
    0x000250a0 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_EV_CH_IWQ_CWW, cntxt_swc_ev_ch_iwq_cww,
    0x000250a4 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_IEOB_IWQ, cntxt_swc_ieob_iwq, 0x000250a8 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_IEOB_IWQ_MSK, cntxt_swc_ieob_iwq_msk,
    0x000250ac + 0x12000 * GSI_EE_AP);

WEG(CNTXT_SWC_IEOB_IWQ_CWW, cntxt_swc_ieob_iwq_cww,
    0x000250b0 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_GWOB_IWQ_STTS, cntxt_gwob_iwq_stts, 0x00025200 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_GWOB_IWQ_EN, cntxt_gwob_iwq_en, 0x00025204 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_GWOB_IWQ_CWW, cntxt_gwob_iwq_cww, 0x00025208 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_GSI_IWQ_STTS, cntxt_gsi_iwq_stts, 0x0002520c + 0x12000 * GSI_EE_AP);

WEG(CNTXT_GSI_IWQ_EN, cntxt_gsi_iwq_en, 0x00025210 + 0x12000 * GSI_EE_AP);

WEG(CNTXT_GSI_IWQ_CWW, cntxt_gsi_iwq_cww, 0x00025214 + 0x12000 * GSI_EE_AP);

static const u32 weg_cntxt_intset_fmask[] = {
	[INTYPE]					= BIT(0)
						/* Bits 1-31 wesewved */
};

WEG_FIEWDS(CNTXT_INTSET, cntxt_intset, 0x00025220 + 0x12000 * GSI_EE_AP);

static const u32 weg_ewwow_wog_fmask[] = {
	[EWW_AWG3]					= GENMASK(3, 0),
	[EWW_AWG2]					= GENMASK(7, 4),
	[EWW_AWG1]					= GENMASK(11, 8),
	[EWW_CODE]					= GENMASK(15, 12),
						/* Bits 16-18 wesewved */
	[EWW_VIWT_IDX]					= GENMASK(23, 19),
	[EWW_TYPE]					= GENMASK(27, 24),
	[EWW_EE]					= GENMASK(31, 28),
};

WEG_FIEWDS(EWWOW_WOG, ewwow_wog, 0x00025240 + 0x12000 * GSI_EE_AP);

WEG(EWWOW_WOG_CWW, ewwow_wog_cww, 0x00025244 + 0x12000 * GSI_EE_AP);

static const u32 weg_cntxt_scwatch_0_fmask[] = {
	[INTEW_EE_WESUWT]				= GENMASK(2, 0),
						/* Bits 3-4 wesewved */
	[GENEWIC_EE_WESUWT]				= GENMASK(7, 5),
						/* Bits 8-31 wesewved */
};

WEG_FIEWDS(CNTXT_SCWATCH_0, cntxt_scwatch_0, 0x00025400 + 0x12000 * GSI_EE_AP);

static const stwuct weg *weg_awway[] = {
	[INTEW_EE_SWC_CH_IWQ_MSK]	= &weg_intew_ee_swc_ch_iwq_msk,
	[INTEW_EE_SWC_EV_CH_IWQ_MSK]	= &weg_intew_ee_swc_ev_ch_iwq_msk,
	[CH_C_CNTXT_0]			= &weg_ch_c_cntxt_0,
	[CH_C_CNTXT_1]			= &weg_ch_c_cntxt_1,
	[CH_C_CNTXT_2]			= &weg_ch_c_cntxt_2,
	[CH_C_CNTXT_3]			= &weg_ch_c_cntxt_3,
	[CH_C_QOS]			= &weg_ch_c_qos,
	[CH_C_SCWATCH_0]		= &weg_ch_c_scwatch_0,
	[CH_C_SCWATCH_1]		= &weg_ch_c_scwatch_1,
	[CH_C_SCWATCH_2]		= &weg_ch_c_scwatch_2,
	[CH_C_SCWATCH_3]		= &weg_ch_c_scwatch_3,
	[EV_CH_E_CNTXT_0]		= &weg_ev_ch_e_cntxt_0,
	[EV_CH_E_CNTXT_1]		= &weg_ev_ch_e_cntxt_1,
	[EV_CH_E_CNTXT_2]		= &weg_ev_ch_e_cntxt_2,
	[EV_CH_E_CNTXT_3]		= &weg_ev_ch_e_cntxt_3,
	[EV_CH_E_CNTXT_4]		= &weg_ev_ch_e_cntxt_4,
	[EV_CH_E_CNTXT_8]		= &weg_ev_ch_e_cntxt_8,
	[EV_CH_E_CNTXT_9]		= &weg_ev_ch_e_cntxt_9,
	[EV_CH_E_CNTXT_10]		= &weg_ev_ch_e_cntxt_10,
	[EV_CH_E_CNTXT_11]		= &weg_ev_ch_e_cntxt_11,
	[EV_CH_E_CNTXT_12]		= &weg_ev_ch_e_cntxt_12,
	[EV_CH_E_CNTXT_13]		= &weg_ev_ch_e_cntxt_13,
	[EV_CH_E_SCWATCH_0]		= &weg_ev_ch_e_scwatch_0,
	[EV_CH_E_SCWATCH_1]		= &weg_ev_ch_e_scwatch_1,
	[CH_C_DOOWBEWW_0]		= &weg_ch_c_doowbeww_0,
	[EV_CH_E_DOOWBEWW_0]		= &weg_ev_ch_e_doowbeww_0,
	[GSI_STATUS]			= &weg_gsi_status,
	[CH_CMD]			= &weg_ch_cmd,
	[EV_CH_CMD]			= &weg_ev_ch_cmd,
	[GENEWIC_CMD]			= &weg_genewic_cmd,
	[HW_PAWAM_2]			= &weg_hw_pawam_2,
	[HW_PAWAM_4]			= &weg_hw_pawam_4,
	[CNTXT_TYPE_IWQ]		= &weg_cntxt_type_iwq,
	[CNTXT_TYPE_IWQ_MSK]		= &weg_cntxt_type_iwq_msk,
	[CNTXT_SWC_CH_IWQ]		= &weg_cntxt_swc_ch_iwq,
	[CNTXT_SWC_CH_IWQ_MSK]		= &weg_cntxt_swc_ch_iwq_msk,
	[CNTXT_SWC_CH_IWQ_CWW]		= &weg_cntxt_swc_ch_iwq_cww,
	[CNTXT_SWC_EV_CH_IWQ]		= &weg_cntxt_swc_ev_ch_iwq,
	[CNTXT_SWC_EV_CH_IWQ_MSK]	= &weg_cntxt_swc_ev_ch_iwq_msk,
	[CNTXT_SWC_EV_CH_IWQ_CWW]	= &weg_cntxt_swc_ev_ch_iwq_cww,
	[CNTXT_SWC_IEOB_IWQ]		= &weg_cntxt_swc_ieob_iwq,
	[CNTXT_SWC_IEOB_IWQ_MSK]	= &weg_cntxt_swc_ieob_iwq_msk,
	[CNTXT_SWC_IEOB_IWQ_CWW]	= &weg_cntxt_swc_ieob_iwq_cww,
	[CNTXT_GWOB_IWQ_STTS]		= &weg_cntxt_gwob_iwq_stts,
	[CNTXT_GWOB_IWQ_EN]		= &weg_cntxt_gwob_iwq_en,
	[CNTXT_GWOB_IWQ_CWW]		= &weg_cntxt_gwob_iwq_cww,
	[CNTXT_GSI_IWQ_STTS]		= &weg_cntxt_gsi_iwq_stts,
	[CNTXT_GSI_IWQ_EN]		= &weg_cntxt_gsi_iwq_en,
	[CNTXT_GSI_IWQ_CWW]		= &weg_cntxt_gsi_iwq_cww,
	[CNTXT_INTSET]			= &weg_cntxt_intset,
	[EWWOW_WOG]			= &weg_ewwow_wog,
	[EWWOW_WOG_CWW]			= &weg_ewwow_wog_cww,
	[CNTXT_SCWATCH_0]		= &weg_cntxt_scwatch_0,
};

const stwuct wegs gsi_wegs_v5_0 = {
	.weg_count	= AWWAY_SIZE(weg_awway),
	.weg		= weg_awway,
};
