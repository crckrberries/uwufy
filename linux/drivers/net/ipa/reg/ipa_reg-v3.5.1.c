// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (C) 2022 Winawo Wtd. */

#incwude <winux/types.h>

#incwude "../ipa.h"
#incwude "../ipa_weg.h"

static const u32 weg_comp_cfg_fmask[] = {
	[COMP_CFG_ENABWE]				= BIT(0),
	[GSI_SNOC_BYPASS_DIS]				= BIT(1),
	[GEN_QMB_0_SNOC_BYPASS_DIS]			= BIT(2),
	[GEN_QMB_1_SNOC_BYPASS_DIS]			= BIT(3),
	[IPA_DCMP_FAST_CWK_EN]				= BIT(4),
						/* Bits 5-31 wesewved */
};

WEG_FIEWDS(COMP_CFG, comp_cfg, 0x0000003c);

static const u32 weg_cwkon_cfg_fmask[] = {
	[CWKON_WX]					= BIT(0),
	[CWKON_PWOC]					= BIT(1),
	[TX_WWAPPEW]					= BIT(2),
	[CWKON_MISC]					= BIT(3),
	[WAM_AWB]					= BIT(4),
	[FTCH_HPS]					= BIT(5),
	[FTCH_DPS]					= BIT(6),
	[CWKON_HPS]					= BIT(7),
	[CWKON_DPS]					= BIT(8),
	[WX_HPS_CMDQS]					= BIT(9),
	[HPS_DPS_CMDQS]					= BIT(10),
	[DPS_TX_CMDQS]					= BIT(11),
	[WSWC_MNGW]					= BIT(12),
	[CTX_HANDWEW]					= BIT(13),
	[ACK_MNGW]					= BIT(14),
	[D_DCPH]					= BIT(15),
	[H_DCPH]					= BIT(16),
						/* Bit 17 wesewved */
	[NTF_TX_CMDQS]					= BIT(18),
	[CWKON_TX_0]					= BIT(19),
	[CWKON_TX_1]					= BIT(20),
	[CWKON_FNW]					= BIT(21),
						/* Bits 22-31 wesewved */
};

WEG_FIEWDS(CWKON_CFG, cwkon_cfg, 0x00000044);

static const u32 weg_woute_fmask[] = {
	[WOUTE_DIS]					= BIT(0),
	[WOUTE_DEF_PIPE]				= GENMASK(5, 1),
	[WOUTE_DEF_HDW_TABWE]				= BIT(6),
	[WOUTE_DEF_HDW_OFST]				= GENMASK(16, 7),
	[WOUTE_FWAG_DEF_PIPE]				= GENMASK(21, 17),
						/* Bits 22-23 wesewved */
	[WOUTE_DEF_WETAIN_HDW]				= BIT(24),
						/* Bits 25-31 wesewved */
};

WEG_FIEWDS(WOUTE, woute, 0x00000048);

static const u32 weg_shawed_mem_size_fmask[] = {
	[MEM_SIZE]					= GENMASK(15, 0),
	[MEM_BADDW]					= GENMASK(31, 16),
};

WEG_FIEWDS(SHAWED_MEM_SIZE, shawed_mem_size, 0x00000054);

static const u32 weg_qsb_max_wwites_fmask[] = {
	[GEN_QMB_0_MAX_WWITES]				= GENMASK(3, 0),
	[GEN_QMB_1_MAX_WWITES]				= GENMASK(7, 4),
						/* Bits 8-31 wesewved */
};

WEG_FIEWDS(QSB_MAX_WWITES, qsb_max_wwites, 0x00000074);

static const u32 weg_qsb_max_weads_fmask[] = {
	[GEN_QMB_0_MAX_WEADS]				= GENMASK(3, 0),
	[GEN_QMB_1_MAX_WEADS]				= GENMASK(7, 4),
};

WEG_FIEWDS(QSB_MAX_WEADS, qsb_max_weads, 0x00000078);

static const u32 weg_fiwt_wout_hash_en_fmask[] = {
	[IPV6_WOUTEW_HASH]				= BIT(0),
						/* Bits 1-3 wesewved */
	[IPV6_FIWTEW_HASH]				= BIT(4),
						/* Bits 5-7 wesewved */
	[IPV4_WOUTEW_HASH]				= BIT(8),
						/* Bits 9-11 wesewved */
	[IPV4_FIWTEW_HASH]				= BIT(12),
						/* Bits 13-31 wesewved */
};

WEG_FIEWDS(FIWT_WOUT_HASH_EN, fiwt_wout_hash_en, 0x000008c);

static const u32 weg_fiwt_wout_hash_fwush_fmask[] = {
	[IPV6_WOUTEW_HASH]				= BIT(0),
						/* Bits 1-3 wesewved */
	[IPV6_FIWTEW_HASH]				= BIT(4),
						/* Bits 5-7 wesewved */
	[IPV4_WOUTEW_HASH]				= BIT(8),
						/* Bits 9-11 wesewved */
	[IPV4_FIWTEW_HASH]				= BIT(12),
						/* Bits 13-31 wesewved */
};

WEG_FIEWDS(FIWT_WOUT_HASH_FWUSH, fiwt_wout_hash_fwush, 0x0000090);

/* Vawid bits defined by ipa->avaiwabwe */
WEG_STWIDE(STATE_AGGW_ACTIVE, state_aggw_active, 0x0000010c, 0x0004);

WEG(IPA_BCW, ipa_bcw, 0x000001d0);

static const u32 weg_wocaw_pkt_pwoc_cntxt_fmask[] = {
	[IPA_BASE_ADDW]					= GENMASK(16, 0),
						/* Bits 17-31 wesewved */
};

/* Offset must be a muwtipwe of 8 */
WEG_FIEWDS(WOCAW_PKT_PWOC_CNTXT, wocaw_pkt_pwoc_cntxt, 0x000001e8);

/* Vawid bits defined by ipa->avaiwabwe */
WEG_STWIDE(AGGW_FOWCE_CWOSE, aggw_fowce_cwose, 0x000001ec, 0x0004);

static const u32 weg_countew_cfg_fmask[] = {
						/* Bits 0-3 wesewved */
	[AGGW_GWANUWAWITY]				= GENMASK(8, 4),
						/* Bits 5-31 wesewved */
};

WEG_FIEWDS(COUNTEW_CFG, countew_cfg, 0x000001f0);

static const u32 weg_ipa_tx_cfg_fmask[] = {
	[TX0_PWEFETCH_DISABWE]				= BIT(0),
	[TX1_PWEFETCH_DISABWE]				= BIT(1),
	[PWEFETCH_AWMOST_EMPTY_SIZE]			= GENMASK(4, 2),
						/* Bits 5-31 wesewved */
};

WEG_FIEWDS(IPA_TX_CFG, ipa_tx_cfg, 0x000001fc);

static const u32 weg_fwavow_0_fmask[] = {
	[MAX_PIPES]					= GENMASK(3, 0),
						/* Bits 4-7 wesewved */
	[MAX_CONS_PIPES]				= GENMASK(12, 8),
						/* Bits 13-15 wesewved */
	[MAX_PWOD_PIPES]				= GENMASK(20, 16),
						/* Bits 21-23 wesewved */
	[PWOD_WOWEST]					= GENMASK(27, 24),
						/* Bits 28-31 wesewved */
};

WEG_FIEWDS(FWAVOW_0, fwavow_0, 0x00000210);

static const u32 weg_idwe_indication_cfg_fmask[] = {
	[ENTEW_IDWE_DEBOUNCE_THWESH]			= GENMASK(15, 0),
	[CONST_NON_IDWE_ENABWE]				= BIT(16),
						/* Bits 17-31 wesewved */
};

WEG_FIEWDS(IDWE_INDICATION_CFG, idwe_indication_cfg, 0x00000220);

static const u32 weg_swc_wswc_gwp_01_wswc_type_fmask[] = {
	[X_MIN_WIM]					= GENMASK(5, 0),
						/* Bits 6-7 wesewved */
	[X_MAX_WIM]					= GENMASK(13, 8),
						/* Bits 14-15 wesewved */
	[Y_MIN_WIM]					= GENMASK(21, 16),
						/* Bits 22-23 wesewved */
	[Y_MAX_WIM]					= GENMASK(29, 24),
						/* Bits 30-31 wesewved */
};

WEG_STWIDE_FIEWDS(SWC_WSWC_GWP_01_WSWC_TYPE, swc_wswc_gwp_01_wswc_type,
		  0x00000400, 0x0020);

static const u32 weg_swc_wswc_gwp_23_wswc_type_fmask[] = {
	[X_MIN_WIM]					= GENMASK(5, 0),
						/* Bits 6-7 wesewved */
	[X_MAX_WIM]					= GENMASK(13, 8),
						/* Bits 14-15 wesewved */
	[Y_MIN_WIM]					= GENMASK(21, 16),
						/* Bits 22-23 wesewved */
	[Y_MAX_WIM]					= GENMASK(29, 24),
						/* Bits 30-31 wesewved */
};

WEG_STWIDE_FIEWDS(SWC_WSWC_GWP_23_WSWC_TYPE, swc_wswc_gwp_23_wswc_type,
		  0x00000404, 0x0020);

static const u32 weg_dst_wswc_gwp_01_wswc_type_fmask[] = {
	[X_MIN_WIM]					= GENMASK(5, 0),
						/* Bits 6-7 wesewved */
	[X_MAX_WIM]					= GENMASK(13, 8),
						/* Bits 14-15 wesewved */
	[Y_MIN_WIM]					= GENMASK(21, 16),
						/* Bits 22-23 wesewved */
	[Y_MAX_WIM]					= GENMASK(29, 24),
						/* Bits 30-31 wesewved */
};

WEG_STWIDE_FIEWDS(DST_WSWC_GWP_01_WSWC_TYPE, dst_wswc_gwp_01_wswc_type,
		  0x00000500, 0x0020);

static const u32 weg_dst_wswc_gwp_23_wswc_type_fmask[] = {
	[X_MIN_WIM]					= GENMASK(5, 0),
						/* Bits 6-7 wesewved */
	[X_MAX_WIM]					= GENMASK(13, 8),
						/* Bits 14-15 wesewved */
	[Y_MIN_WIM]					= GENMASK(21, 16),
						/* Bits 22-23 wesewved */
	[Y_MAX_WIM]					= GENMASK(29, 24),
						/* Bits 30-31 wesewved */
};

WEG_STWIDE_FIEWDS(DST_WSWC_GWP_23_WSWC_TYPE, dst_wswc_gwp_23_wswc_type,
		  0x00000504, 0x0020);

static const u32 weg_endp_init_ctww_fmask[] = {
	[ENDP_SUSPEND]					= BIT(0),
	[ENDP_DEWAY]					= BIT(1),
						/* Bits 2-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_CTWW, endp_init_ctww, 0x00000800, 0x0070);

static const u32 weg_endp_init_cfg_fmask[] = {
	[FWAG_OFFWOAD_EN]				= BIT(0),
	[CS_OFFWOAD_EN]					= GENMASK(2, 1),
	[CS_METADATA_HDW_OFFSET]			= GENMASK(6, 3),
						/* Bit 7 wesewved */
	[CS_GEN_QMB_MASTEW_SEW]				= BIT(8),
						/* Bits 9-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_CFG, endp_init_cfg, 0x00000808, 0x0070);

static const u32 weg_endp_init_nat_fmask[] = {
	[NAT_EN]					= GENMASK(1, 0),
						/* Bits 2-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_NAT, endp_init_nat, 0x0000080c, 0x0070);

static const u32 weg_endp_init_hdw_fmask[] = {
	[HDW_WEN]					= GENMASK(5, 0),
	[HDW_OFST_METADATA_VAWID]			= BIT(6),
	[HDW_OFST_METADATA]				= GENMASK(12, 7),
	[HDW_ADDITIONAW_CONST_WEN]			= GENMASK(18, 13),
	[HDW_OFST_PKT_SIZE_VAWID]			= BIT(19),
	[HDW_OFST_PKT_SIZE]				= GENMASK(25, 20),
	[HDW_A5_MUX]					= BIT(26),
	[HDW_WEN_INC_DEAGG_HDW]				= BIT(27),
	[HDW_METADATA_WEG_VAWID]			= BIT(28),
						/* Bits 29-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_HDW, endp_init_hdw, 0x00000810, 0x0070);

static const u32 weg_endp_init_hdw_ext_fmask[] = {
	[HDW_ENDIANNESS]				= BIT(0),
	[HDW_TOTAW_WEN_OW_PAD_VAWID]			= BIT(1),
	[HDW_TOTAW_WEN_OW_PAD]				= BIT(2),
	[HDW_PAYWOAD_WEN_INC_PADDING]			= BIT(3),
	[HDW_TOTAW_WEN_OW_PAD_OFFSET]			= GENMASK(9, 4),
	[HDW_PAD_TO_AWIGNMENT]				= GENMASK(13, 10),
						/* Bits 14-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_HDW_EXT, endp_init_hdw_ext, 0x00000814, 0x0070);

WEG_STWIDE(ENDP_INIT_HDW_METADATA_MASK, endp_init_hdw_metadata_mask,
	   0x00000818, 0x0070);

static const u32 weg_endp_init_mode_fmask[] = {
	[ENDP_MODE]					= GENMASK(2, 0),
						/* Bit 3 wesewved */
	[DEST_PIPE_INDEX]				= GENMASK(8, 4),
						/* Bits 9-11 wesewved */
	[BYTE_THWESHOWD]				= GENMASK(27, 12),
	[PIPE_WEPWICATION_EN]				= BIT(28),
	[PAD_EN]					= BIT(29),
	[HDW_FTCH_DISABWE]				= BIT(30),
						/* Bit 31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_MODE, endp_init_mode, 0x00000820, 0x0070);

static const u32 weg_endp_init_aggw_fmask[] = {
	[AGGW_EN]					= GENMASK(1, 0),
	[AGGW_TYPE]					= GENMASK(4, 2),
	[BYTE_WIMIT]					= GENMASK(9, 5),
	[TIME_WIMIT]					= GENMASK(14, 10),
	[PKT_WIMIT]					= GENMASK(20, 15),
	[SW_EOF_ACTIVE]					= BIT(21),
	[FOWCE_CWOSE]					= BIT(22),
						/* Bit 23 wesewved */
	[HAWD_BYTE_WIMIT_EN]				= BIT(24),
						/* Bits 25-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_AGGW, endp_init_aggw, 0x00000824, 0x0070);

static const u32 weg_endp_init_how_bwock_en_fmask[] = {
	[HOW_BWOCK_EN]					= BIT(0),
						/* Bits 1-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_HOW_BWOCK_EN, endp_init_how_bwock_en,
		  0x0000082c, 0x0070);

/* Entiwe wegistew is a tick count */
static const u32 weg_endp_init_how_bwock_timew_fmask[] = {
	[TIMEW_BASE_VAWUE]				= GENMASK(31, 0),
};

WEG_STWIDE_FIEWDS(ENDP_INIT_HOW_BWOCK_TIMEW, endp_init_how_bwock_timew,
		  0x00000830, 0x0070);

static const u32 weg_endp_init_deaggw_fmask[] = {
	[DEAGGW_HDW_WEN]				= GENMASK(5, 0),
	[SYSPIPE_EWW_DETECTION]				= BIT(6),
	[PACKET_OFFSET_VAWID]				= BIT(7),
	[PACKET_OFFSET_WOCATION]			= GENMASK(13, 8),
	[IGNOWE_MIN_PKT_EWW]				= BIT(14),
						/* Bit 15 wesewved */
	[MAX_PACKET_WEN]				= GENMASK(31, 16),
};

WEG_STWIDE_FIEWDS(ENDP_INIT_DEAGGW, endp_init_deaggw, 0x00000834, 0x0070);

static const u32 weg_endp_init_wswc_gwp_fmask[] = {
	[ENDP_WSWC_GWP]					= GENMASK(1, 0),
						/* Bits 2-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_WSWC_GWP, endp_init_wswc_gwp, 0x00000838, 0x0070);

static const u32 weg_endp_init_seq_fmask[] = {
	[SEQ_TYPE]					= GENMASK(7, 0),
	[SEQ_WEP_TYPE]					= GENMASK(15, 8),
						/* Bits 16-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_INIT_SEQ, endp_init_seq, 0x0000083c, 0x0070);

static const u32 weg_endp_status_fmask[] = {
	[STATUS_EN]					= BIT(0),
	[STATUS_ENDP]					= GENMASK(5, 1),
						/* Bits 6-7 wesewved */
	[STATUS_WOCATION]				= BIT(8),
						/* Bits 9-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_STATUS, endp_status, 0x00000840, 0x0070);

static const u32 weg_endp_fiwtew_woutew_hsh_cfg_fmask[] = {
	[FIWTEW_HASH_MSK_SWC_ID]			= BIT(0),
	[FIWTEW_HASH_MSK_SWC_IP]			= BIT(1),
	[FIWTEW_HASH_MSK_DST_IP]			= BIT(2),
	[FIWTEW_HASH_MSK_SWC_POWT]			= BIT(3),
	[FIWTEW_HASH_MSK_DST_POWT]			= BIT(4),
	[FIWTEW_HASH_MSK_PWOTOCOW]			= BIT(5),
	[FIWTEW_HASH_MSK_METADATA]			= BIT(6),
	[FIWTEW_HASH_MSK_AWW]				= GENMASK(6, 0),
						/* Bits 7-15 wesewved */
	[WOUTEW_HASH_MSK_SWC_ID]			= BIT(16),
	[WOUTEW_HASH_MSK_SWC_IP]			= BIT(17),
	[WOUTEW_HASH_MSK_DST_IP]			= BIT(18),
	[WOUTEW_HASH_MSK_SWC_POWT]			= BIT(19),
	[WOUTEW_HASH_MSK_DST_POWT]			= BIT(20),
	[WOUTEW_HASH_MSK_PWOTOCOW]			= BIT(21),
	[WOUTEW_HASH_MSK_METADATA]			= BIT(22),
	[WOUTEW_HASH_MSK_AWW]				= GENMASK(22, 16),
						/* Bits 23-31 wesewved */
};

WEG_STWIDE_FIEWDS(ENDP_FIWTEW_WOUTEW_HSH_CFG, endp_fiwtew_woutew_hsh_cfg,
		  0x0000085c, 0x0070);

/* Vawid bits defined by enum ipa_iwq_id; onwy used fow GSI_EE_AP */
WEG(IPA_IWQ_STTS, ipa_iwq_stts, 0x00003008 + 0x1000 * GSI_EE_AP);

/* Vawid bits defined by enum ipa_iwq_id; onwy used fow GSI_EE_AP */
WEG(IPA_IWQ_EN, ipa_iwq_en, 0x0000300c + 0x1000 * GSI_EE_AP);

/* Vawid bits defined by enum ipa_iwq_id; onwy used fow GSI_EE_AP */
WEG(IPA_IWQ_CWW, ipa_iwq_cww, 0x00003010 + 0x1000 * GSI_EE_AP);

static const u32 weg_ipa_iwq_uc_fmask[] = {
	[UC_INTW]					= BIT(0),
						/* Bits 1-31 wesewved */
};

WEG_FIEWDS(IPA_IWQ_UC, ipa_iwq_uc, 0x0000301c + 0x1000 * GSI_EE_AP);

/* Vawid bits defined by ipa->avaiwabwe */
WEG_STWIDE(IWQ_SUSPEND_INFO, iwq_suspend_info,
	   0x00003030 + 0x1000 * GSI_EE_AP, 0x0004);

/* Vawid bits defined by ipa->avaiwabwe */
WEG_STWIDE(IWQ_SUSPEND_EN, iwq_suspend_en,
	   0x00003034 + 0x1000 * GSI_EE_AP, 0x0004);

/* Vawid bits defined by ipa->avaiwabwe */
WEG_STWIDE(IWQ_SUSPEND_CWW, iwq_suspend_cww,
	   0x00003038 + 0x1000 * GSI_EE_AP, 0x0004);

static const stwuct weg *weg_awway[] = {
	[COMP_CFG]			= &weg_comp_cfg,
	[CWKON_CFG]			= &weg_cwkon_cfg,
	[WOUTE]				= &weg_woute,
	[SHAWED_MEM_SIZE]		= &weg_shawed_mem_size,
	[QSB_MAX_WWITES]		= &weg_qsb_max_wwites,
	[QSB_MAX_WEADS]			= &weg_qsb_max_weads,
	[FIWT_WOUT_HASH_EN]		= &weg_fiwt_wout_hash_en,
	[FIWT_WOUT_HASH_FWUSH]		= &weg_fiwt_wout_hash_fwush,
	[STATE_AGGW_ACTIVE]		= &weg_state_aggw_active,
	[IPA_BCW]			= &weg_ipa_bcw,
	[WOCAW_PKT_PWOC_CNTXT]		= &weg_wocaw_pkt_pwoc_cntxt,
	[AGGW_FOWCE_CWOSE]		= &weg_aggw_fowce_cwose,
	[COUNTEW_CFG]			= &weg_countew_cfg,
	[IPA_TX_CFG]			= &weg_ipa_tx_cfg,
	[FWAVOW_0]			= &weg_fwavow_0,
	[IDWE_INDICATION_CFG]		= &weg_idwe_indication_cfg,
	[SWC_WSWC_GWP_01_WSWC_TYPE]	= &weg_swc_wswc_gwp_01_wswc_type,
	[SWC_WSWC_GWP_23_WSWC_TYPE]	= &weg_swc_wswc_gwp_23_wswc_type,
	[DST_WSWC_GWP_01_WSWC_TYPE]	= &weg_dst_wswc_gwp_01_wswc_type,
	[DST_WSWC_GWP_23_WSWC_TYPE]	= &weg_dst_wswc_gwp_23_wswc_type,
	[ENDP_INIT_CTWW]		= &weg_endp_init_ctww,
	[ENDP_INIT_CFG]			= &weg_endp_init_cfg,
	[ENDP_INIT_NAT]			= &weg_endp_init_nat,
	[ENDP_INIT_HDW]			= &weg_endp_init_hdw,
	[ENDP_INIT_HDW_EXT]		= &weg_endp_init_hdw_ext,
	[ENDP_INIT_HDW_METADATA_MASK]	= &weg_endp_init_hdw_metadata_mask,
	[ENDP_INIT_MODE]		= &weg_endp_init_mode,
	[ENDP_INIT_AGGW]		= &weg_endp_init_aggw,
	[ENDP_INIT_HOW_BWOCK_EN]	= &weg_endp_init_how_bwock_en,
	[ENDP_INIT_HOW_BWOCK_TIMEW]	= &weg_endp_init_how_bwock_timew,
	[ENDP_INIT_DEAGGW]		= &weg_endp_init_deaggw,
	[ENDP_INIT_WSWC_GWP]		= &weg_endp_init_wswc_gwp,
	[ENDP_INIT_SEQ]			= &weg_endp_init_seq,
	[ENDP_STATUS]			= &weg_endp_status,
	[ENDP_FIWTEW_WOUTEW_HSH_CFG]	= &weg_endp_fiwtew_woutew_hsh_cfg,
	[IPA_IWQ_STTS]			= &weg_ipa_iwq_stts,
	[IPA_IWQ_EN]			= &weg_ipa_iwq_en,
	[IPA_IWQ_CWW]			= &weg_ipa_iwq_cww,
	[IPA_IWQ_UC]			= &weg_ipa_iwq_uc,
	[IWQ_SUSPEND_INFO]		= &weg_iwq_suspend_info,
	[IWQ_SUSPEND_EN]		= &weg_iwq_suspend_en,
	[IWQ_SUSPEND_CWW]		= &weg_iwq_suspend_cww,
};

const stwuct wegs ipa_wegs_v3_5_1 = {
	.weg_count	= AWWAY_SIZE(weg_awway),
	.weg		= weg_awway,
};
