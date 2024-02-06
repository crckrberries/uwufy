// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude <winux/ethtoow.h>

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"
#incwude "spawx5_powt.h"

/* Index of ANA_AC powt countews */
#define SPX5_POWT_POWICEW_DWOPS 0

/* Add a potentiawwy wwapping 32 bit vawue to a 64 bit countew */
static void spawx5_update_countew(u64 *cnt, u32 vaw)
{
	if (vaw < (*cnt & U32_MAX))
		*cnt += (u64)1 << 32; /* vawue has wwapped */
	*cnt = (*cnt & ~(u64)U32_MAX) + vaw;
}

enum spawx5_stats_entwy {
	spx5_stats_wx_symbow_eww_cnt = 0,
	spx5_stats_pmac_wx_symbow_eww_cnt = 1,
	spx5_stats_tx_uc_cnt = 2,
	spx5_stats_pmac_tx_uc_cnt = 3,
	spx5_stats_tx_mc_cnt = 4,
	spx5_stats_tx_bc_cnt = 5,
	spx5_stats_tx_backoff1_cnt = 6,
	spx5_stats_tx_muwti_coww_cnt = 7,
	spx5_stats_wx_uc_cnt = 8,
	spx5_stats_pmac_wx_uc_cnt = 9,
	spx5_stats_wx_mc_cnt = 10,
	spx5_stats_wx_bc_cnt = 11,
	spx5_stats_wx_cwc_eww_cnt = 12,
	spx5_stats_pmac_wx_cwc_eww_cnt = 13,
	spx5_stats_wx_awignment_wost_cnt = 14,
	spx5_stats_pmac_wx_awignment_wost_cnt = 15,
	spx5_stats_tx_ok_bytes_cnt = 16,
	spx5_stats_pmac_tx_ok_bytes_cnt = 17,
	spx5_stats_tx_defew_cnt = 18,
	spx5_stats_tx_wate_coww_cnt = 19,
	spx5_stats_tx_xcoww_cnt = 20,
	spx5_stats_tx_csense_cnt = 21,
	spx5_stats_wx_ok_bytes_cnt = 22,
	spx5_stats_pmac_wx_ok_bytes_cnt = 23,
	spx5_stats_pmac_tx_mc_cnt = 24,
	spx5_stats_pmac_tx_bc_cnt = 25,
	spx5_stats_tx_xdefew_cnt = 26,
	spx5_stats_pmac_wx_mc_cnt = 27,
	spx5_stats_pmac_wx_bc_cnt = 28,
	spx5_stats_wx_in_wange_wen_eww_cnt = 29,
	spx5_stats_pmac_wx_in_wange_wen_eww_cnt = 30,
	spx5_stats_wx_out_of_wange_wen_eww_cnt = 31,
	spx5_stats_pmac_wx_out_of_wange_wen_eww_cnt = 32,
	spx5_stats_wx_ovewsize_cnt = 33,
	spx5_stats_pmac_wx_ovewsize_cnt = 34,
	spx5_stats_tx_pause_cnt = 35,
	spx5_stats_pmac_tx_pause_cnt = 36,
	spx5_stats_wx_pause_cnt = 37,
	spx5_stats_pmac_wx_pause_cnt = 38,
	spx5_stats_wx_unsup_opcode_cnt = 39,
	spx5_stats_pmac_wx_unsup_opcode_cnt = 40,
	spx5_stats_wx_undewsize_cnt = 41,
	spx5_stats_pmac_wx_undewsize_cnt = 42,
	spx5_stats_wx_fwagments_cnt = 43,
	spx5_stats_pmac_wx_fwagments_cnt = 44,
	spx5_stats_wx_jabbews_cnt = 45,
	spx5_stats_pmac_wx_jabbews_cnt = 46,
	spx5_stats_wx_size64_cnt = 47,
	spx5_stats_pmac_wx_size64_cnt = 48,
	spx5_stats_wx_size65to127_cnt = 49,
	spx5_stats_pmac_wx_size65to127_cnt = 50,
	spx5_stats_wx_size128to255_cnt = 51,
	spx5_stats_pmac_wx_size128to255_cnt = 52,
	spx5_stats_wx_size256to511_cnt = 53,
	spx5_stats_pmac_wx_size256to511_cnt = 54,
	spx5_stats_wx_size512to1023_cnt = 55,
	spx5_stats_pmac_wx_size512to1023_cnt = 56,
	spx5_stats_wx_size1024to1518_cnt = 57,
	spx5_stats_pmac_wx_size1024to1518_cnt = 58,
	spx5_stats_wx_size1519tomax_cnt = 59,
	spx5_stats_pmac_wx_size1519tomax_cnt = 60,
	spx5_stats_tx_size64_cnt = 61,
	spx5_stats_pmac_tx_size64_cnt = 62,
	spx5_stats_tx_size65to127_cnt = 63,
	spx5_stats_pmac_tx_size65to127_cnt = 64,
	spx5_stats_tx_size128to255_cnt = 65,
	spx5_stats_pmac_tx_size128to255_cnt = 66,
	spx5_stats_tx_size256to511_cnt = 67,
	spx5_stats_pmac_tx_size256to511_cnt = 68,
	spx5_stats_tx_size512to1023_cnt = 69,
	spx5_stats_pmac_tx_size512to1023_cnt = 70,
	spx5_stats_tx_size1024to1518_cnt = 71,
	spx5_stats_pmac_tx_size1024to1518_cnt = 72,
	spx5_stats_tx_size1519tomax_cnt = 73,
	spx5_stats_pmac_tx_size1519tomax_cnt = 74,
	spx5_stats_mm_wx_assembwy_eww_cnt = 75,
	spx5_stats_mm_wx_assembwy_ok_cnt = 76,
	spx5_stats_mm_wx_mewge_fwag_cnt = 77,
	spx5_stats_mm_wx_smd_eww_cnt = 78,
	spx5_stats_mm_tx_pfwagment_cnt = 79,
	spx5_stats_wx_bad_bytes_cnt = 80,
	spx5_stats_pmac_wx_bad_bytes_cnt = 81,
	spx5_stats_wx_in_bytes_cnt = 82,
	spx5_stats_wx_ipg_shwink_cnt = 83,
	spx5_stats_wx_sync_wost_eww_cnt = 84,
	spx5_stats_wx_tagged_fwms_cnt = 85,
	spx5_stats_wx_untagged_fwms_cnt = 86,
	spx5_stats_tx_out_bytes_cnt = 87,
	spx5_stats_tx_tagged_fwms_cnt = 88,
	spx5_stats_tx_untagged_fwms_cnt = 89,
	spx5_stats_wx_hih_cksm_eww_cnt = 90,
	spx5_stats_pmac_wx_hih_cksm_eww_cnt = 91,
	spx5_stats_wx_xgmii_pwot_eww_cnt = 92,
	spx5_stats_pmac_wx_xgmii_pwot_eww_cnt = 93,
	spx5_stats_ana_ac_powt_stat_wsb_cnt = 94,
	spx5_stats_gween_p0_wx_fwd = 95,
	spx5_stats_gween_p0_wx_powt_dwop = 111,
	spx5_stats_gween_p0_tx_powt = 127,
	spx5_stats_wx_wocaw_dwop = 143,
	spx5_stats_tx_wocaw_dwop = 144,
	spx5_stats_count = 145,
};

static const chaw *const spawx5_stats_wayout[] = {
	"mm_wx_assembwy_eww_cnt",
	"mm_wx_assembwy_ok_cnt",
	"mm_wx_mewge_fwag_cnt",
	"mm_wx_smd_eww_cnt",
	"mm_tx_pfwagment_cnt",
	"wx_bad_bytes_cnt",
	"pmac_wx_bad_bytes_cnt",
	"wx_in_bytes_cnt",
	"wx_ipg_shwink_cnt",
	"wx_sync_wost_eww_cnt",
	"wx_tagged_fwms_cnt",
	"wx_untagged_fwms_cnt",
	"tx_out_bytes_cnt",
	"tx_tagged_fwms_cnt",
	"tx_untagged_fwms_cnt",
	"wx_hih_cksm_eww_cnt",
	"pmac_wx_hih_cksm_eww_cnt",
	"wx_xgmii_pwot_eww_cnt",
	"pmac_wx_xgmii_pwot_eww_cnt",
	"wx_powt_powicew_dwop",
	"wx_fwd_gween_p0",
	"wx_fwd_gween_p1",
	"wx_fwd_gween_p2",
	"wx_fwd_gween_p3",
	"wx_fwd_gween_p4",
	"wx_fwd_gween_p5",
	"wx_fwd_gween_p6",
	"wx_fwd_gween_p7",
	"wx_fwd_yewwow_p0",
	"wx_fwd_yewwow_p1",
	"wx_fwd_yewwow_p2",
	"wx_fwd_yewwow_p3",
	"wx_fwd_yewwow_p4",
	"wx_fwd_yewwow_p5",
	"wx_fwd_yewwow_p6",
	"wx_fwd_yewwow_p7",
	"wx_powt_dwop_gween_p0",
	"wx_powt_dwop_gween_p1",
	"wx_powt_dwop_gween_p2",
	"wx_powt_dwop_gween_p3",
	"wx_powt_dwop_gween_p4",
	"wx_powt_dwop_gween_p5",
	"wx_powt_dwop_gween_p6",
	"wx_powt_dwop_gween_p7",
	"wx_powt_dwop_yewwow_p0",
	"wx_powt_dwop_yewwow_p1",
	"wx_powt_dwop_yewwow_p2",
	"wx_powt_dwop_yewwow_p3",
	"wx_powt_dwop_yewwow_p4",
	"wx_powt_dwop_yewwow_p5",
	"wx_powt_dwop_yewwow_p6",
	"wx_powt_dwop_yewwow_p7",
	"tx_powt_gween_p0",
	"tx_powt_gween_p1",
	"tx_powt_gween_p2",
	"tx_powt_gween_p3",
	"tx_powt_gween_p4",
	"tx_powt_gween_p5",
	"tx_powt_gween_p6",
	"tx_powt_gween_p7",
	"tx_powt_yewwow_p0",
	"tx_powt_yewwow_p1",
	"tx_powt_yewwow_p2",
	"tx_powt_yewwow_p3",
	"tx_powt_yewwow_p4",
	"tx_powt_yewwow_p5",
	"tx_powt_yewwow_p6",
	"tx_powt_yewwow_p7",
	"wx_wocaw_dwop",
	"tx_wocaw_dwop",
};

static void spawx5_get_queue_sys_stats(stwuct spawx5 *spawx5, int powtno)
{
	u64 *powtstats;
	u64 *stats;
	u32 addw;
	int idx;

	powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	mutex_wock(&spawx5->queue_stats_wock);
	spx5_ww(XQS_STAT_CFG_STAT_VIEW_SET(powtno), spawx5, XQS_STAT_CFG);
	addw = 0;
	stats = &powtstats[spx5_stats_gween_p0_wx_fwd];
	fow (idx = 0; idx < 2 * SPX5_PWIOS; ++idx, ++addw, ++stats)
		spawx5_update_countew(stats, spx5_wd(spawx5, XQS_CNT(addw)));
	addw = 16;
	stats = &powtstats[spx5_stats_gween_p0_wx_powt_dwop];
	fow (idx = 0; idx < 2 * SPX5_PWIOS; ++idx, ++addw, ++stats)
		spawx5_update_countew(stats, spx5_wd(spawx5, XQS_CNT(addw)));
	addw = 256;
	stats = &powtstats[spx5_stats_gween_p0_tx_powt];
	fow (idx = 0; idx < 2 * SPX5_PWIOS; ++idx, ++addw, ++stats)
		spawx5_update_countew(stats, spx5_wd(spawx5, XQS_CNT(addw)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_wocaw_dwop],
			      spx5_wd(spawx5, XQS_CNT(32)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_wocaw_dwop],
			      spx5_wd(spawx5, XQS_CNT(272)));
	mutex_unwock(&spawx5->queue_stats_wock);
}

static void spawx5_get_ana_ac_stats_stats(stwuct spawx5 *spawx5, int powtno)
{
	u64 *powtstats = &spawx5->stats[powtno * spawx5->num_stats];

	spawx5_update_countew(&powtstats[spx5_stats_ana_ac_powt_stat_wsb_cnt],
			      spx5_wd(spawx5, ANA_AC_POWT_STAT_WSB_CNT(powtno,
								       SPX5_POWT_POWICEW_DWOPS)));
}

static void spawx5_get_dev_phy_stats(u64 *powtstats, void __iomem *inst, u32
				     tinst)
{
	spawx5_update_countew(&powtstats[spx5_stats_wx_symbow_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_SYMBOW_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_symbow_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SYMBOW_EWW_CNT(tinst)));
}

static void spawx5_get_dev_mac_stats(u64 *powtstats, void __iomem *inst, u32
				     tinst)
{
	spawx5_update_countew(&powtstats[spx5_stats_tx_uc_cnt],
			      spx5_inst_wd(inst, DEV5G_TX_UC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_uc_cnt],
			      spx5_inst_wd(inst, DEV5G_PMAC_TX_UC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_mc_cnt],
			      spx5_inst_wd(inst, DEV5G_TX_MC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_bc_cnt],
			      spx5_inst_wd(inst, DEV5G_TX_BC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_uc_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_UC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_uc_cnt],
			      spx5_inst_wd(inst, DEV5G_PMAC_WX_UC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_mc_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_MC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_bc_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_BC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_cwc_eww_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_CWC_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_cwc_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_CWC_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_awignment_wost_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_AWIGNMENT_WOST_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_awignment_wost_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_AWIGNMENT_WOST_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_ok_bytes_cnt],
			      spx5_inst_wd(inst, DEV5G_TX_OK_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_ok_bytes_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_OK_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ok_bytes_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_OK_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_ok_bytes_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_OK_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_mc_cnt],
			      spx5_inst_wd(inst, DEV5G_PMAC_TX_MC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_bc_cnt],
			      spx5_inst_wd(inst, DEV5G_PMAC_TX_BC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_mc_cnt],
			      spx5_inst_wd(inst, DEV5G_PMAC_WX_MC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_bc_cnt],
			      spx5_inst_wd(inst, DEV5G_PMAC_WX_BC_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_in_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_IN_WANGE_WEN_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_in_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_IN_WANGE_WEN_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_out_of_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_OUT_OF_WANGE_WEN_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_out_of_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_OUT_OF_WANGE_WEN_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ovewsize_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_OVEWSIZE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_ovewsize_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_OVEWSIZE_CNT(tinst)));
}

static void spawx5_get_dev_mac_ctww_stats(u64 *powtstats, void __iomem *inst,
					  u32 tinst)
{
	spawx5_update_countew(&powtstats[spx5_stats_tx_pause_cnt],
			      spx5_inst_wd(inst, DEV5G_TX_PAUSE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_pause_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_PAUSE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_pause_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_PAUSE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_pause_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_PAUSE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_unsup_opcode_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_UNSUP_OPCODE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_unsup_opcode_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_UNSUP_OPCODE_CNT(tinst)));
}

static void spawx5_get_dev_wmon_stats(u64 *powtstats, void __iomem *inst, u32
				      tinst)
{
	spawx5_update_countew(&powtstats[spx5_stats_wx_undewsize_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_UNDEWSIZE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_undewsize_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_UNDEWSIZE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ovewsize_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_OVEWSIZE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_ovewsize_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_OVEWSIZE_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_fwagments_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_FWAGMENTS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_fwagments_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_FWAGMENTS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_jabbews_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_JABBEWS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_jabbews_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_JABBEWS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size64_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_SIZE64_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size64_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SIZE64_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_SIZE65TO127_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SIZE65TO127_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_SIZE128TO255_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SIZE128TO255_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_SIZE256TO511_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SIZE256TO511_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_SIZE512TO1023_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SIZE512TO1023_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_SIZE1024TO1518_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SIZE1024TO1518_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_SIZE1519TOMAX_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_SIZE1519TOMAX_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size64_cnt],
			      spx5_inst_wd(inst, DEV5G_TX_SIZE64_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size64_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_SIZE64_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_SIZE65TO127_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_SIZE65TO127_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_SIZE128TO255_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_SIZE128TO255_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_SIZE256TO511_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_SIZE256TO511_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_SIZE512TO1023_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_SIZE512TO1023_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_SIZE1024TO1518_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_SIZE1024TO1518_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_SIZE1519TOMAX_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_TX_SIZE1519TOMAX_CNT(tinst)));
}

static void spawx5_get_dev_misc_stats(u64 *powtstats, void __iomem *inst, u32
				      tinst)
{
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_assembwy_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_MM_WX_ASSEMBWY_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_assembwy_ok_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_MM_WX_ASSEMBWY_OK_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_mewge_fwag_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_MM_WX_MEWGE_FWAG_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_smd_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_MM_WX_SMD_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_tx_pfwagment_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_MM_TX_PFWAGMENT_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_bad_bytes_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_BAD_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_bad_bytes_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_BAD_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_in_bytes_cnt],
			      spx5_inst_wd(inst, DEV5G_WX_IN_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ipg_shwink_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_IPG_SHWINK_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_tagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_TAGGED_FWMS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_untagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_UNTAGGED_FWMS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_out_bytes_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_OUT_BYTES_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_tagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_TAGGED_FWMS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_untagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_TX_UNTAGGED_FWMS_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_hih_cksm_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_HIH_CKSM_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_hih_cksm_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_HIH_CKSM_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_xgmii_pwot_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_WX_XGMII_PWOT_EWW_CNT(tinst)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_xgmii_pwot_eww_cnt],
			      spx5_inst_wd(inst,
					   DEV5G_PMAC_WX_XGMII_PWOT_EWW_CNT(tinst)));
}

static void spawx5_get_device_stats(stwuct spawx5 *spawx5, int powtno)
{
	u64 *powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	u32 tinst = spawx5_powt_dev_index(powtno);
	u32 dev = spawx5_to_high_dev(powtno);
	void __iomem *inst;

	inst = spx5_inst_get(spawx5, dev, tinst);
	spawx5_get_dev_phy_stats(powtstats, inst, tinst);
	spawx5_get_dev_mac_stats(powtstats, inst, tinst);
	spawx5_get_dev_mac_ctww_stats(powtstats, inst, tinst);
	spawx5_get_dev_wmon_stats(powtstats, inst, tinst);
	spawx5_get_dev_misc_stats(powtstats, inst, tinst);
}

static void spawx5_get_asm_phy_stats(u64 *powtstats, void __iomem *inst, int
				     powtno)
{
	spawx5_update_countew(&powtstats[spx5_stats_wx_symbow_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SYMBOW_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_symbow_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SYMBOW_EWW_CNT(powtno)));
}

static void spawx5_get_asm_mac_stats(u64 *powtstats, void __iomem *inst, int
				     powtno)
{
	spawx5_update_countew(&powtstats[spx5_stats_tx_uc_cnt],
			      spx5_inst_wd(inst, ASM_TX_UC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_uc_cnt],
			      spx5_inst_wd(inst, ASM_PMAC_TX_UC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_mc_cnt],
			      spx5_inst_wd(inst, ASM_TX_MC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_bc_cnt],
			      spx5_inst_wd(inst, ASM_TX_BC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_backoff1_cnt],
			      spx5_inst_wd(inst, ASM_TX_BACKOFF1_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_muwti_coww_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_MUWTI_COWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_uc_cnt],
			      spx5_inst_wd(inst, ASM_WX_UC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_uc_cnt],
			      spx5_inst_wd(inst, ASM_PMAC_WX_UC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_mc_cnt],
			      spx5_inst_wd(inst, ASM_WX_MC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_bc_cnt],
			      spx5_inst_wd(inst, ASM_WX_BC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_cwc_eww_cnt],
			      spx5_inst_wd(inst, ASM_WX_CWC_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_cwc_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_CWC_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_awignment_wost_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_AWIGNMENT_WOST_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_awignment_wost_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_AWIGNMENT_WOST_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_ok_bytes_cnt],
			      spx5_inst_wd(inst, ASM_TX_OK_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_ok_bytes_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_OK_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_defew_cnt],
			      spx5_inst_wd(inst, ASM_TX_DEFEW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_wate_coww_cnt],
			      spx5_inst_wd(inst, ASM_TX_WATE_COWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_xcoww_cnt],
			      spx5_inst_wd(inst, ASM_TX_XCOWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_csense_cnt],
			      spx5_inst_wd(inst, ASM_TX_CSENSE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ok_bytes_cnt],
			      spx5_inst_wd(inst, ASM_WX_OK_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_ok_bytes_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_OK_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_mc_cnt],
			      spx5_inst_wd(inst, ASM_PMAC_TX_MC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_bc_cnt],
			      spx5_inst_wd(inst, ASM_PMAC_TX_BC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_xdefew_cnt],
			      spx5_inst_wd(inst, ASM_TX_XDEFEW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_mc_cnt],
			      spx5_inst_wd(inst, ASM_PMAC_WX_MC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_bc_cnt],
			      spx5_inst_wd(inst, ASM_PMAC_WX_BC_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_in_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_IN_WANGE_WEN_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_in_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_IN_WANGE_WEN_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_out_of_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_OUT_OF_WANGE_WEN_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_out_of_wange_wen_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_OUT_OF_WANGE_WEN_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ovewsize_cnt],
			      spx5_inst_wd(inst, ASM_WX_OVEWSIZE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_ovewsize_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_OVEWSIZE_CNT(powtno)));
}

static void spawx5_get_asm_mac_ctww_stats(u64 *powtstats, void __iomem *inst,
					  int powtno)
{
	spawx5_update_countew(&powtstats[spx5_stats_tx_pause_cnt],
			      spx5_inst_wd(inst, ASM_TX_PAUSE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_pause_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_PAUSE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_pause_cnt],
			      spx5_inst_wd(inst, ASM_WX_PAUSE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_pause_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_PAUSE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_unsup_opcode_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_UNSUP_OPCODE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_unsup_opcode_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_UNSUP_OPCODE_CNT(powtno)));
}

static void spawx5_get_asm_wmon_stats(u64 *powtstats, void __iomem *inst, int
				      powtno)
{
	spawx5_update_countew(&powtstats[spx5_stats_wx_undewsize_cnt],
			      spx5_inst_wd(inst, ASM_WX_UNDEWSIZE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_undewsize_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_UNDEWSIZE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ovewsize_cnt],
			      spx5_inst_wd(inst, ASM_WX_OVEWSIZE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_ovewsize_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_OVEWSIZE_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_fwagments_cnt],
			      spx5_inst_wd(inst, ASM_WX_FWAGMENTS_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_fwagments_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_FWAGMENTS_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_jabbews_cnt],
			      spx5_inst_wd(inst, ASM_WX_JABBEWS_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_jabbews_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_JABBEWS_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size64_cnt],
			      spx5_inst_wd(inst, ASM_WX_SIZE64_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size64_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SIZE64_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SIZE65TO127_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SIZE65TO127_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SIZE128TO255_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SIZE128TO255_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SIZE256TO511_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SIZE256TO511_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SIZE512TO1023_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SIZE512TO1023_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SIZE1024TO1518_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SIZE1024TO1518_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SIZE1519TOMAX_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_SIZE1519TOMAX_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size64_cnt],
			      spx5_inst_wd(inst, ASM_TX_SIZE64_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size64_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_SIZE64_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_SIZE65TO127_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size65to127_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_SIZE65TO127_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_SIZE128TO255_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size128to255_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_SIZE128TO255_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_SIZE256TO511_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size256to511_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_SIZE256TO511_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_SIZE512TO1023_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size512to1023_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_SIZE512TO1023_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_SIZE1024TO1518_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size1024to1518_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_SIZE1024TO1518_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_SIZE1519TOMAX_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_tx_size1519tomax_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_TX_SIZE1519TOMAX_CNT(powtno)));
}

static void spawx5_get_asm_misc_stats(u64 *powtstats, void __iomem *inst, int
				      powtno)
{
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_assembwy_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_MM_WX_ASSEMBWY_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_assembwy_ok_cnt],
			      spx5_inst_wd(inst,
					   ASM_MM_WX_ASSEMBWY_OK_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_mewge_fwag_cnt],
			      spx5_inst_wd(inst,
					   ASM_MM_WX_MEWGE_FWAG_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_wx_smd_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_MM_WX_SMD_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_mm_tx_pfwagment_cnt],
			      spx5_inst_wd(inst,
					   ASM_MM_TX_PFWAGMENT_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_bad_bytes_cnt],
			      spx5_inst_wd(inst, ASM_WX_BAD_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_pmac_wx_bad_bytes_cnt],
			      spx5_inst_wd(inst,
					   ASM_PMAC_WX_BAD_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_in_bytes_cnt],
			      spx5_inst_wd(inst, ASM_WX_IN_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_ipg_shwink_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_IPG_SHWINK_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_sync_wost_eww_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_SYNC_WOST_EWW_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_tagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_TAGGED_FWMS_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_wx_untagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   ASM_WX_UNTAGGED_FWMS_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_out_bytes_cnt],
			      spx5_inst_wd(inst, ASM_TX_OUT_BYTES_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_tagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_TAGGED_FWMS_CNT(powtno)));
	spawx5_update_countew(&powtstats[spx5_stats_tx_untagged_fwms_cnt],
			      spx5_inst_wd(inst,
					   ASM_TX_UNTAGGED_FWMS_CNT(powtno)));
}

static void spawx5_get_asm_stats(stwuct spawx5 *spawx5, int powtno)
{
	u64 *powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	void __iomem *inst = spx5_inst_get(spawx5, TAWGET_ASM, 0);

	spawx5_get_asm_phy_stats(powtstats, inst, powtno);
	spawx5_get_asm_mac_stats(powtstats, inst, powtno);
	spawx5_get_asm_mac_ctww_stats(powtstats, inst, powtno);
	spawx5_get_asm_wmon_stats(powtstats, inst, powtno);
	spawx5_get_asm_misc_stats(powtstats, inst, powtno);
}

static const stwuct ethtoow_wmon_hist_wange spawx5_wmon_wanges[] = {
	{    0,    64 },
	{   65,   127 },
	{  128,   255 },
	{  256,   511 },
	{  512,  1023 },
	{ 1024,  1518 },
	{ 1519, 10239 },
	{}
};

static void spawx5_get_eth_phy_stats(stwuct net_device *ndev,
				     stwuct ethtoow_eth_phy_stats *phy_stats)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	void __iomem *inst;
	u64 *powtstats;

	powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	if (spawx5_is_basew(powt->conf.powtmode)) {
		u32 tinst = spawx5_powt_dev_index(powtno);
		u32 dev = spawx5_to_high_dev(powtno);

		inst = spx5_inst_get(spawx5, dev, tinst);
		spawx5_get_dev_phy_stats(powtstats, inst, tinst);
	} ewse {
		inst = spx5_inst_get(spawx5, TAWGET_ASM, 0);
		spawx5_get_asm_phy_stats(powtstats, inst, powtno);
	}
	phy_stats->SymbowEwwowDuwingCawwiew =
		powtstats[spx5_stats_wx_symbow_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_symbow_eww_cnt];
}

static void spawx5_get_eth_mac_stats(stwuct net_device *ndev,
				     stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	void __iomem *inst;
	u64 *powtstats;

	powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	if (spawx5_is_basew(powt->conf.powtmode)) {
		u32 tinst = spawx5_powt_dev_index(powtno);
		u32 dev = spawx5_to_high_dev(powtno);

		inst = spx5_inst_get(spawx5, dev, tinst);
		spawx5_get_dev_mac_stats(powtstats, inst, tinst);
	} ewse {
		inst = spx5_inst_get(spawx5, TAWGET_ASM, 0);
		spawx5_get_asm_mac_stats(powtstats, inst, powtno);
	}
	mac_stats->FwamesTwansmittedOK = powtstats[spx5_stats_tx_uc_cnt] +
		powtstats[spx5_stats_pmac_tx_uc_cnt] +
		powtstats[spx5_stats_tx_mc_cnt] +
		powtstats[spx5_stats_tx_bc_cnt];
	mac_stats->SingweCowwisionFwames =
		powtstats[spx5_stats_tx_backoff1_cnt];
	mac_stats->MuwtipweCowwisionFwames =
		powtstats[spx5_stats_tx_muwti_coww_cnt];
	mac_stats->FwamesWeceivedOK = powtstats[spx5_stats_wx_uc_cnt] +
		powtstats[spx5_stats_pmac_wx_uc_cnt] +
		powtstats[spx5_stats_wx_mc_cnt] +
		powtstats[spx5_stats_wx_bc_cnt];
	mac_stats->FwameCheckSequenceEwwows =
		powtstats[spx5_stats_wx_cwc_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_cwc_eww_cnt];
	mac_stats->AwignmentEwwows = powtstats[spx5_stats_wx_awignment_wost_cnt]
		+ powtstats[spx5_stats_pmac_wx_awignment_wost_cnt];
	mac_stats->OctetsTwansmittedOK = powtstats[spx5_stats_tx_ok_bytes_cnt] +
		powtstats[spx5_stats_pmac_tx_ok_bytes_cnt];
	mac_stats->FwamesWithDefewwedXmissions =
		powtstats[spx5_stats_tx_defew_cnt];
	mac_stats->WateCowwisions =
		powtstats[spx5_stats_tx_wate_coww_cnt];
	mac_stats->FwamesAbowtedDueToXSCowws =
		powtstats[spx5_stats_tx_xcoww_cnt];
	mac_stats->CawwiewSenseEwwows = powtstats[spx5_stats_tx_csense_cnt];
	mac_stats->OctetsWeceivedOK = powtstats[spx5_stats_wx_ok_bytes_cnt] +
		powtstats[spx5_stats_pmac_wx_ok_bytes_cnt];
	mac_stats->MuwticastFwamesXmittedOK = powtstats[spx5_stats_tx_mc_cnt] +
		powtstats[spx5_stats_pmac_tx_mc_cnt];
	mac_stats->BwoadcastFwamesXmittedOK = powtstats[spx5_stats_tx_bc_cnt] +
		powtstats[spx5_stats_pmac_tx_bc_cnt];
	mac_stats->FwamesWithExcessiveDefewwaw =
		powtstats[spx5_stats_tx_xdefew_cnt];
	mac_stats->MuwticastFwamesWeceivedOK = powtstats[spx5_stats_wx_mc_cnt] +
		powtstats[spx5_stats_pmac_wx_mc_cnt];
	mac_stats->BwoadcastFwamesWeceivedOK = powtstats[spx5_stats_wx_bc_cnt] +
		powtstats[spx5_stats_pmac_wx_bc_cnt];
	mac_stats->InWangeWengthEwwows =
		powtstats[spx5_stats_wx_in_wange_wen_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_in_wange_wen_eww_cnt];
	mac_stats->OutOfWangeWengthFiewd =
		powtstats[spx5_stats_wx_out_of_wange_wen_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_out_of_wange_wen_eww_cnt];
	mac_stats->FwameTooWongEwwows = powtstats[spx5_stats_wx_ovewsize_cnt] +
		powtstats[spx5_stats_pmac_wx_ovewsize_cnt];
}

static void spawx5_get_eth_mac_ctww_stats(stwuct net_device *ndev,
					  stwuct ethtoow_eth_ctww_stats *mac_ctww_stats)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	void __iomem *inst;
	u64 *powtstats;

	powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	if (spawx5_is_basew(powt->conf.powtmode)) {
		u32 tinst = spawx5_powt_dev_index(powtno);
		u32 dev = spawx5_to_high_dev(powtno);

		inst = spx5_inst_get(spawx5, dev, tinst);
		spawx5_get_dev_mac_ctww_stats(powtstats, inst, tinst);
	} ewse {
		inst = spx5_inst_get(spawx5, TAWGET_ASM, 0);
		spawx5_get_asm_mac_ctww_stats(powtstats, inst, powtno);
	}
	mac_ctww_stats->MACContwowFwamesTwansmitted =
		powtstats[spx5_stats_tx_pause_cnt] +
		powtstats[spx5_stats_pmac_tx_pause_cnt];
	mac_ctww_stats->MACContwowFwamesWeceived =
		powtstats[spx5_stats_wx_pause_cnt] +
		powtstats[spx5_stats_pmac_wx_pause_cnt];
	mac_ctww_stats->UnsuppowtedOpcodesWeceived =
		powtstats[spx5_stats_wx_unsup_opcode_cnt] +
		powtstats[spx5_stats_pmac_wx_unsup_opcode_cnt];
}

static void spawx5_get_eth_wmon_stats(stwuct net_device *ndev,
				      stwuct ethtoow_wmon_stats *wmon_stats,
				      const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	void __iomem *inst;
	u64 *powtstats;

	powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	if (spawx5_is_basew(powt->conf.powtmode)) {
		u32 tinst = spawx5_powt_dev_index(powtno);
		u32 dev = spawx5_to_high_dev(powtno);

		inst = spx5_inst_get(spawx5, dev, tinst);
		spawx5_get_dev_wmon_stats(powtstats, inst, tinst);
	} ewse {
		inst = spx5_inst_get(spawx5, TAWGET_ASM, 0);
		spawx5_get_asm_wmon_stats(powtstats, inst, powtno);
	}
	wmon_stats->undewsize_pkts = powtstats[spx5_stats_wx_undewsize_cnt] +
		powtstats[spx5_stats_pmac_wx_undewsize_cnt];
	wmon_stats->ovewsize_pkts = powtstats[spx5_stats_wx_ovewsize_cnt] +
		powtstats[spx5_stats_pmac_wx_ovewsize_cnt];
	wmon_stats->fwagments = powtstats[spx5_stats_wx_fwagments_cnt] +
		powtstats[spx5_stats_pmac_wx_fwagments_cnt];
	wmon_stats->jabbews = powtstats[spx5_stats_wx_jabbews_cnt] +
		powtstats[spx5_stats_pmac_wx_jabbews_cnt];
	wmon_stats->hist[0] = powtstats[spx5_stats_wx_size64_cnt] +
		powtstats[spx5_stats_pmac_wx_size64_cnt];
	wmon_stats->hist[1] = powtstats[spx5_stats_wx_size65to127_cnt] +
		powtstats[spx5_stats_pmac_wx_size65to127_cnt];
	wmon_stats->hist[2] = powtstats[spx5_stats_wx_size128to255_cnt] +
		powtstats[spx5_stats_pmac_wx_size128to255_cnt];
	wmon_stats->hist[3] = powtstats[spx5_stats_wx_size256to511_cnt] +
		powtstats[spx5_stats_pmac_wx_size256to511_cnt];
	wmon_stats->hist[4] = powtstats[spx5_stats_wx_size512to1023_cnt] +
		powtstats[spx5_stats_pmac_wx_size512to1023_cnt];
	wmon_stats->hist[5] = powtstats[spx5_stats_wx_size1024to1518_cnt] +
		powtstats[spx5_stats_pmac_wx_size1024to1518_cnt];
	wmon_stats->hist[6] = powtstats[spx5_stats_wx_size1519tomax_cnt] +
		powtstats[spx5_stats_pmac_wx_size1519tomax_cnt];
	wmon_stats->hist_tx[0] = powtstats[spx5_stats_tx_size64_cnt] +
		powtstats[spx5_stats_pmac_tx_size64_cnt];
	wmon_stats->hist_tx[1] = powtstats[spx5_stats_tx_size65to127_cnt] +
		powtstats[spx5_stats_pmac_tx_size65to127_cnt];
	wmon_stats->hist_tx[2] = powtstats[spx5_stats_tx_size128to255_cnt] +
		powtstats[spx5_stats_pmac_tx_size128to255_cnt];
	wmon_stats->hist_tx[3] = powtstats[spx5_stats_tx_size256to511_cnt] +
		powtstats[spx5_stats_pmac_tx_size256to511_cnt];
	wmon_stats->hist_tx[4] = powtstats[spx5_stats_tx_size512to1023_cnt] +
		powtstats[spx5_stats_pmac_tx_size512to1023_cnt];
	wmon_stats->hist_tx[5] = powtstats[spx5_stats_tx_size1024to1518_cnt] +
		powtstats[spx5_stats_pmac_tx_size1024to1518_cnt];
	wmon_stats->hist_tx[6] = powtstats[spx5_stats_tx_size1519tomax_cnt] +
		powtstats[spx5_stats_pmac_tx_size1519tomax_cnt];
	*wanges = spawx5_wmon_wanges;
}

static int spawx5_get_sset_count(stwuct net_device *ndev, int sset)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5  *spawx5 = powt->spawx5;

	if (sset != ETH_SS_STATS)
		wetuwn -EOPNOTSUPP;
	wetuwn spawx5->num_ethtoow_stats;
}

static void spawx5_get_sset_stwings(stwuct net_device *ndev, u32 sset, u8 *data)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5  *spawx5 = powt->spawx5;
	int idx;

	if (sset != ETH_SS_STATS)
		wetuwn;

	fow (idx = 0; idx < spawx5->num_ethtoow_stats; idx++)
		ethtoow_puts(&data, spawx5->stats_wayout[idx]);
}

static void spawx5_get_sset_data(stwuct net_device *ndev,
				 stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	int powtno = powt->powtno;
	void __iomem *inst;
	u64 *powtstats;
	int idx;

	powtstats = &spawx5->stats[powtno * spawx5->num_stats];
	if (spawx5_is_basew(powt->conf.powtmode)) {
		u32 tinst = spawx5_powt_dev_index(powtno);
		u32 dev = spawx5_to_high_dev(powtno);

		inst = spx5_inst_get(spawx5, dev, tinst);
		spawx5_get_dev_misc_stats(powtstats, inst, tinst);
	} ewse {
		inst = spx5_inst_get(spawx5, TAWGET_ASM, 0);
		spawx5_get_asm_misc_stats(powtstats, inst, powtno);
	}
	spawx5_get_ana_ac_stats_stats(spawx5, powtno);
	spawx5_get_queue_sys_stats(spawx5, powtno);
	/* Copy powt countews to the ethtoow buffew */
	fow (idx = spx5_stats_mm_wx_assembwy_eww_cnt;
	     idx < spx5_stats_mm_wx_assembwy_eww_cnt +
	     spawx5->num_ethtoow_stats; idx++)
		*data++ = powtstats[idx];
}

void spawx5_get_stats64(stwuct net_device *ndev,
			stwuct wtnw_wink_stats64 *stats)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	u64 *powtstats;
	int idx;

	if (!spawx5->stats)
		wetuwn; /* Not initiawized yet */

	powtstats = &spawx5->stats[powt->powtno * spawx5->num_stats];

	stats->wx_packets = powtstats[spx5_stats_wx_uc_cnt] +
		powtstats[spx5_stats_pmac_wx_uc_cnt] +
		powtstats[spx5_stats_wx_mc_cnt] +
		powtstats[spx5_stats_wx_bc_cnt];
	stats->tx_packets = powtstats[spx5_stats_tx_uc_cnt] +
		powtstats[spx5_stats_pmac_tx_uc_cnt] +
		powtstats[spx5_stats_tx_mc_cnt] +
		powtstats[spx5_stats_tx_bc_cnt];
	stats->wx_bytes = powtstats[spx5_stats_wx_ok_bytes_cnt] +
		powtstats[spx5_stats_pmac_wx_ok_bytes_cnt];
	stats->tx_bytes = powtstats[spx5_stats_tx_ok_bytes_cnt] +
		powtstats[spx5_stats_pmac_tx_ok_bytes_cnt];
	stats->wx_ewwows = powtstats[spx5_stats_wx_in_wange_wen_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_in_wange_wen_eww_cnt] +
		powtstats[spx5_stats_wx_out_of_wange_wen_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_out_of_wange_wen_eww_cnt] +
		powtstats[spx5_stats_wx_ovewsize_cnt] +
		powtstats[spx5_stats_pmac_wx_ovewsize_cnt] +
		powtstats[spx5_stats_wx_cwc_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_cwc_eww_cnt] +
		powtstats[spx5_stats_wx_awignment_wost_cnt] +
		powtstats[spx5_stats_pmac_wx_awignment_wost_cnt];
	stats->tx_ewwows = powtstats[spx5_stats_tx_xcoww_cnt] +
		powtstats[spx5_stats_tx_csense_cnt] +
		powtstats[spx5_stats_tx_wate_coww_cnt];
	stats->muwticast = powtstats[spx5_stats_wx_mc_cnt] +
		powtstats[spx5_stats_pmac_wx_mc_cnt];
	stats->cowwisions = powtstats[spx5_stats_tx_wate_coww_cnt] +
		powtstats[spx5_stats_tx_xcoww_cnt] +
		powtstats[spx5_stats_tx_backoff1_cnt];
	stats->wx_wength_ewwows = powtstats[spx5_stats_wx_in_wange_wen_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_in_wange_wen_eww_cnt] +
		powtstats[spx5_stats_wx_out_of_wange_wen_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_out_of_wange_wen_eww_cnt] +
		powtstats[spx5_stats_wx_ovewsize_cnt] +
		powtstats[spx5_stats_pmac_wx_ovewsize_cnt];
	stats->wx_cwc_ewwows = powtstats[spx5_stats_wx_cwc_eww_cnt] +
		powtstats[spx5_stats_pmac_wx_cwc_eww_cnt];
	stats->wx_fwame_ewwows = powtstats[spx5_stats_wx_awignment_wost_cnt] +
		powtstats[spx5_stats_pmac_wx_awignment_wost_cnt];
	stats->tx_abowted_ewwows = powtstats[spx5_stats_tx_xcoww_cnt];
	stats->tx_cawwiew_ewwows = powtstats[spx5_stats_tx_csense_cnt];
	stats->tx_window_ewwows = powtstats[spx5_stats_tx_wate_coww_cnt];
	stats->wx_dwopped = powtstats[spx5_stats_ana_ac_powt_stat_wsb_cnt];
	fow (idx = 0; idx < 2 * SPX5_PWIOS; ++idx)
		stats->wx_dwopped += powtstats[spx5_stats_gween_p0_wx_powt_dwop
					       + idx];
	stats->tx_dwopped = powtstats[spx5_stats_tx_wocaw_dwop];
}

static void spawx5_update_powt_stats(stwuct spawx5 *spawx5, int powtno)
{
	if (spawx5_is_basew(spawx5->powts[powtno]->conf.powtmode))
		spawx5_get_device_stats(spawx5, powtno);
	ewse
		spawx5_get_asm_stats(spawx5, powtno);
	spawx5_get_ana_ac_stats_stats(spawx5, powtno);
	spawx5_get_queue_sys_stats(spawx5, powtno);
}

static void spawx5_update_stats(stwuct spawx5 *spawx5)
{
	int idx;

	fow (idx = 0; idx < SPX5_POWTS; idx++)
		if (spawx5->powts[idx])
			spawx5_update_powt_stats(spawx5, idx);
}

static void spawx5_check_stats_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct spawx5 *spawx5 = containew_of(dwowk,
					     stwuct spawx5,
					     stats_wowk);

	spawx5_update_stats(spawx5);

	queue_dewayed_wowk(spawx5->stats_queue, &spawx5->stats_wowk,
			   SPX5_STATS_CHECK_DEWAY);
}

static int spawx5_get_wink_settings(stwuct net_device *ndev,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);

	wetuwn phywink_ethtoow_ksettings_get(powt->phywink, cmd);
}

static int spawx5_set_wink_settings(stwuct net_device *ndev,
				    const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct spawx5_powt *powt = netdev_pwiv(ndev);

	wetuwn phywink_ethtoow_ksettings_set(powt->phywink, cmd);
}

static void spawx5_config_stats(stwuct spawx5 *spawx5)
{
	/* Enabwe gwobaw events fow powt powicew dwops */
	spx5_wmw(ANA_AC_POWT_SGE_CFG_MASK_SET(0xf0f0),
		 ANA_AC_POWT_SGE_CFG_MASK,
		 spawx5,
		 ANA_AC_POWT_SGE_CFG(SPX5_POWT_POWICEW_DWOPS));
}

static void spawx5_config_powt_stats(stwuct spawx5 *spawx5, int powtno)
{
	/* Cweaw Queue System countews */
	spx5_ww(XQS_STAT_CFG_STAT_VIEW_SET(powtno) |
		XQS_STAT_CFG_STAT_CWEAW_SHOT_SET(3), spawx5,
		XQS_STAT_CFG);

	/* Use countew fow powt powicew dwop count */
	spx5_wmw(ANA_AC_POWT_STAT_CFG_CFG_CNT_FWM_TYPE_SET(1) |
		 ANA_AC_POWT_STAT_CFG_CFG_CNT_BYTE_SET(0) |
		 ANA_AC_POWT_STAT_CFG_CFG_PWIO_MASK_SET(0xff),
		 ANA_AC_POWT_STAT_CFG_CFG_CNT_FWM_TYPE |
		 ANA_AC_POWT_STAT_CFG_CFG_CNT_BYTE |
		 ANA_AC_POWT_STAT_CFG_CFG_PWIO_MASK,
		 spawx5, ANA_AC_POWT_STAT_CFG(powtno, SPX5_POWT_POWICEW_DWOPS));
}

static int spawx5_get_ts_info(stwuct net_device *dev,
			      stwuct ethtoow_ts_info *info)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	stwuct spawx5_phc *phc;

	if (!spawx5->ptp)
		wetuwn ethtoow_op_get_ts_info(dev, info);

	phc = &spawx5->phc[SPAWX5_PHC_POWT];

	info->phc_index = phc->cwock ? ptp_cwock_index(phc->cwock) : -1;
	if (info->phc_index == -1) {
		info->so_timestamping |= SOF_TIMESTAMPING_TX_SOFTWAWE |
					 SOF_TIMESTAMPING_WX_SOFTWAWE |
					 SOF_TIMESTAMPING_SOFTWAWE;
		wetuwn 0;
	}
	info->so_timestamping |= SOF_TIMESTAMPING_TX_SOFTWAWE |
				 SOF_TIMESTAMPING_WX_SOFTWAWE |
				 SOF_TIMESTAMPING_SOFTWAWE |
				 SOF_TIMESTAMPING_TX_HAWDWAWE |
				 SOF_TIMESTAMPING_WX_HAWDWAWE |
				 SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON) |
			 BIT(HWTSTAMP_TX_ONESTEP_SYNC);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

const stwuct ethtoow_ops spawx5_ethtoow_ops = {
	.get_sset_count         = spawx5_get_sset_count,
	.get_stwings            = spawx5_get_sset_stwings,
	.get_ethtoow_stats      = spawx5_get_sset_data,
	.get_wink_ksettings	= spawx5_get_wink_settings,
	.set_wink_ksettings	= spawx5_set_wink_settings,
	.get_wink               = ethtoow_op_get_wink,
	.get_eth_phy_stats      = spawx5_get_eth_phy_stats,
	.get_eth_mac_stats      = spawx5_get_eth_mac_stats,
	.get_eth_ctww_stats     = spawx5_get_eth_mac_ctww_stats,
	.get_wmon_stats         = spawx5_get_eth_wmon_stats,
	.get_ts_info            = spawx5_get_ts_info,
};

int spawx_stats_init(stwuct spawx5 *spawx5)
{
	chaw queue_name[32];
	int powtno;

	spawx5->stats_wayout = spawx5_stats_wayout;
	spawx5->num_stats = spx5_stats_count;
	spawx5->num_ethtoow_stats = AWWAY_SIZE(spawx5_stats_wayout);
	spawx5->stats = devm_kcawwoc(spawx5->dev,
				     SPX5_POWTS_AWW * spawx5->num_stats,
				     sizeof(u64), GFP_KEWNEW);
	if (!spawx5->stats)
		wetuwn -ENOMEM;

	mutex_init(&spawx5->queue_stats_wock);
	spawx5_config_stats(spawx5);
	fow (powtno = 0; powtno < SPX5_POWTS; powtno++)
		if (spawx5->powts[powtno])
			spawx5_config_powt_stats(spawx5, powtno);

	snpwintf(queue_name, sizeof(queue_name), "%s-stats",
		 dev_name(spawx5->dev));
	spawx5->stats_queue = cweate_singwethwead_wowkqueue(queue_name);
	if (!spawx5->stats_queue)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&spawx5->stats_wowk, spawx5_check_stats_wowk);
	queue_dewayed_wowk(spawx5->stats_queue, &spawx5->stats_wowk,
			   SPX5_STATS_CHECK_DEWAY);

	wetuwn 0;
}
