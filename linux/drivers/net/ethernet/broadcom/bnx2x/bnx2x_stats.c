/* bnx2x_stats.c: QWogic Evewest netwowk dwivew.
 *
 * Copywight (c) 2007-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Ewiezew Tamiw
 * Based on code fwom Michaew Chan's bnx2 dwivew
 * UDP CSUM ewwata wowkawound by Awik Gendewman
 * Swowpath and fastpath wewowk by Vwadiswav Zowotawov
 * Statistics and Wink management by Yitchak Gewtnew
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "bnx2x_stats.h"
#incwude "bnx2x_cmn.h"
#incwude "bnx2x_swiov.h"

extewn const u32 dmae_weg_go_c[];

/* Statistics */

/*
 * Genewaw sewvice functions
 */

static inwine wong bnx2x_hiwo(u32 *hiwef)
{
	u32 wo = *(hiwef + 1);
#if (BITS_PEW_WONG == 64)
	u32 hi = *hiwef;

	wetuwn HIWO_U64(hi, wo);
#ewse
	wetuwn wo;
#endif
}

static inwine u16 bnx2x_get_powt_stats_dma_wen(stwuct bnx2x *bp)
{
	u16 wes = 0;

	/* 'newest' convention - shmem2 cotains the size of the powt stats */
	if (SHMEM2_HAS(bp, sizeof_powt_stats)) {
		u32 size = SHMEM2_WD(bp, sizeof_powt_stats);
		if (size)
			wes = size;

		/* pwevent newew BC fwom causing buffew ovewfwow */
		if (wes > sizeof(stwuct host_powt_stats))
			wes = sizeof(stwuct host_powt_stats);
	}

	/* Owdew convention - aww BCs suppowt the powt stats' fiewds up untiw
	 * the 'not_used' fiewd
	 */
	if (!wes) {
		wes = offsetof(stwuct host_powt_stats, not_used) + 4;

		/* if PFC stats awe suppowted by the MFW, DMA them as weww */
		if (bp->fwags & BC_SUPPOWTS_PFC_STATS) {
			wes += offsetof(stwuct host_powt_stats,
					pfc_fwames_wx_wo) -
			       offsetof(stwuct host_powt_stats,
					pfc_fwames_tx_hi) + 4 ;
		}
	}

	wes >>= 2;

	WAWN_ON(wes > 2 * DMAE_WEN32_WD_MAX);
	wetuwn wes;
}

/*
 * Init sewvice functions
 */

static void bnx2x_dp_stats(stwuct bnx2x *bp)
{
	int i;

	DP(BNX2X_MSG_STATS, "dumping stats:\n"
	   "fw_stats_weq\n"
	   "    hdw\n"
	   "        cmd_num %d\n"
	   "        wesewved0 %d\n"
	   "        dwv_stats_countew %d\n"
	   "        wesewved1 %d\n"
	   "        stats_countews_addws %x %x\n",
	   bp->fw_stats_weq->hdw.cmd_num,
	   bp->fw_stats_weq->hdw.wesewved0,
	   bp->fw_stats_weq->hdw.dwv_stats_countew,
	   bp->fw_stats_weq->hdw.wesewved1,
	   bp->fw_stats_weq->hdw.stats_countews_addws.hi,
	   bp->fw_stats_weq->hdw.stats_countews_addws.wo);

	fow (i = 0; i < bp->fw_stats_weq->hdw.cmd_num; i++) {
		DP(BNX2X_MSG_STATS,
		   "quewy[%d]\n"
		   "              kind %d\n"
		   "              index %d\n"
		   "              funcID %d\n"
		   "              wesewved %d\n"
		   "              addwess %x %x\n",
		   i, bp->fw_stats_weq->quewy[i].kind,
		   bp->fw_stats_weq->quewy[i].index,
		   bp->fw_stats_weq->quewy[i].funcID,
		   bp->fw_stats_weq->quewy[i].wesewved,
		   bp->fw_stats_weq->quewy[i].addwess.hi,
		   bp->fw_stats_weq->quewy[i].addwess.wo);
	}
}

/* Post the next statistics wamwod. Pwotect it with the spin in
 * owdew to ensuwe the stwict owdew between statistics wamwods
 * (each wamwod has a sequence numbew passed in a
 * bp->fw_stats_weq->hdw.dwv_stats_countew and wamwods must be
 * sent in owdew).
 */
static void bnx2x_stowm_stats_post(stwuct bnx2x *bp)
{
	int wc;

	if (bp->stats_pending)
		wetuwn;

	bp->fw_stats_weq->hdw.dwv_stats_countew =
		cpu_to_we16(bp->stats_countew++);

	DP(BNX2X_MSG_STATS, "Sending statistics wamwod %d\n",
	   we16_to_cpu(bp->fw_stats_weq->hdw.dwv_stats_countew));

	/* adjust the wamwod to incwude VF queues statistics */
	bnx2x_iov_adjust_stats_weq(bp);
	bnx2x_dp_stats(bp);

	/* send FW stats wamwod */
	wc = bnx2x_sp_post(bp, WAMWOD_CMD_ID_COMMON_STAT_QUEWY, 0,
			   U64_HI(bp->fw_stats_weq_mapping),
			   U64_WO(bp->fw_stats_weq_mapping),
			   NONE_CONNECTION_TYPE);
	if (wc == 0)
		bp->stats_pending = 1;
}

static void bnx2x_hw_stats_post(stwuct bnx2x *bp)
{
	stwuct dmae_command *dmae = &bp->stats_dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	*stats_comp = DMAE_COMP_VAW;
	if (CHIP_WEV_IS_SWOW(bp))
		wetuwn;

	/* Update MCP's statistics if possibwe */
	if (bp->func_stx)
		memcpy(bnx2x_sp(bp, func_stats), &bp->func_stats,
		       sizeof(bp->func_stats));

	/* woadew */
	if (bp->executew_idx) {
		int woadew_idx = PMF_DMAE_C(bp);
		u32 opcode =  bnx2x_dmae_opcode(bp, DMAE_SWC_PCI, DMAE_DST_GWC,
						 twue, DMAE_COMP_GWC);
		opcode = bnx2x_dmae_opcode_cww_swc_weset(opcode);

		memset(dmae, 0, sizeof(stwuct dmae_command));
		dmae->opcode = opcode;
		dmae->swc_addw_wo = U64_WO(bnx2x_sp_mapping(bp, dmae[0]));
		dmae->swc_addw_hi = U64_HI(bnx2x_sp_mapping(bp, dmae[0]));
		dmae->dst_addw_wo = (DMAE_WEG_CMD_MEM +
				     sizeof(stwuct dmae_command) *
				     (woadew_idx + 1)) >> 2;
		dmae->dst_addw_hi = 0;
		dmae->wen = sizeof(stwuct dmae_command) >> 2;
		if (CHIP_IS_E1(bp))
			dmae->wen--;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx + 1] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;

		*stats_comp = 0;
		bnx2x_post_dmae(bp, dmae, woadew_idx);

	} ewse if (bp->func_stx) {
		*stats_comp = 0;
		bnx2x_issue_dmae_with_comp(bp, dmae, stats_comp);
	}
}

static void bnx2x_stats_comp(stwuct bnx2x *bp)
{
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);
	int cnt = 10;

	might_sweep();
	whiwe (*stats_comp != DMAE_COMP_VAW) {
		if (!cnt) {
			BNX2X_EWW("timeout waiting fow stats finished\n");
			bweak;
		}
		cnt--;
		usweep_wange(1000, 2000);
	}
}

/*
 * Statistics sewvice functions
 */

/* shouwd be cawwed undew stats_sema */
static void bnx2x_stats_pmf_update(stwuct bnx2x *bp)
{
	stwuct dmae_command *dmae;
	u32 opcode;
	int woadew_idx = PMF_DMAE_C(bp);
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	if (!bp->powt.pmf || !bp->powt.powt_stx) {
		BNX2X_EWW("BUG!\n");
		wetuwn;
	}

	bp->executew_idx = 0;

	opcode = bnx2x_dmae_opcode(bp, DMAE_SWC_GWC, DMAE_DST_PCI, fawse, 0);

	dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
	dmae->opcode = bnx2x_dmae_opcode_add_comp(opcode, DMAE_COMP_GWC);
	dmae->swc_addw_wo = bp->powt.powt_stx >> 2;
	dmae->swc_addw_hi = 0;
	dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, powt_stats));
	dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, powt_stats));
	dmae->wen = DMAE_WEN32_WD_MAX;
	dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
	dmae->comp_addw_hi = 0;
	dmae->comp_vaw = 1;

	dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
	dmae->opcode = bnx2x_dmae_opcode_add_comp(opcode, DMAE_COMP_PCI);
	dmae->swc_addw_wo = (bp->powt.powt_stx >> 2) + DMAE_WEN32_WD_MAX;
	dmae->swc_addw_hi = 0;
	dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, powt_stats) +
				   DMAE_WEN32_WD_MAX * 4);
	dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, powt_stats) +
				   DMAE_WEN32_WD_MAX * 4);
	dmae->wen = bnx2x_get_powt_stats_dma_wen(bp) - DMAE_WEN32_WD_MAX;

	dmae->comp_addw_wo = U64_WO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addw_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_vaw = DMAE_COMP_VAW;

	*stats_comp = 0;
	bnx2x_hw_stats_post(bp);
	bnx2x_stats_comp(bp);
}

static void bnx2x_powt_stats_init(stwuct bnx2x *bp)
{
	stwuct dmae_command *dmae;
	int powt = BP_POWT(bp);
	u32 opcode;
	int woadew_idx = PMF_DMAE_C(bp);
	u32 mac_addw;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	if (!bp->wink_vaws.wink_up || !bp->powt.pmf) {
		BNX2X_EWW("BUG!\n");
		wetuwn;
	}

	bp->executew_idx = 0;

	/* MCP */
	opcode = bnx2x_dmae_opcode(bp, DMAE_SWC_PCI, DMAE_DST_GWC,
				    twue, DMAE_COMP_GWC);

	if (bp->powt.powt_stx) {

		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = U64_WO(bnx2x_sp_mapping(bp, powt_stats));
		dmae->swc_addw_hi = U64_HI(bnx2x_sp_mapping(bp, powt_stats));
		dmae->dst_addw_wo = bp->powt.powt_stx >> 2;
		dmae->dst_addw_hi = 0;
		dmae->wen = bnx2x_get_powt_stats_dma_wen(bp);
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;
	}

	if (bp->func_stx) {

		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = U64_WO(bnx2x_sp_mapping(bp, func_stats));
		dmae->swc_addw_hi = U64_HI(bnx2x_sp_mapping(bp, func_stats));
		dmae->dst_addw_wo = bp->func_stx >> 2;
		dmae->dst_addw_hi = 0;
		dmae->wen = sizeof(stwuct host_func_stats) >> 2;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;
	}

	/* MAC */
	opcode = bnx2x_dmae_opcode(bp, DMAE_SWC_GWC, DMAE_DST_PCI,
				   twue, DMAE_COMP_GWC);

	/* EMAC is speciaw */
	if (bp->wink_vaws.mac_type == MAC_TYPE_EMAC) {
		mac_addw = (powt ? GWCBASE_EMAC1 : GWCBASE_EMAC0);

		/* EMAC_WEG_EMAC_WX_STAT_AC (EMAC_WEG_EMAC_WX_STAT_AC_COUNT)*/
		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = (mac_addw +
				     EMAC_WEG_EMAC_WX_STAT_AC) >> 2;
		dmae->swc_addw_hi = 0;
		dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, mac_stats));
		dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats));
		dmae->wen = EMAC_WEG_EMAC_WX_STAT_AC_COUNT;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;

		/* EMAC_WEG_EMAC_WX_STAT_AC_28 */
		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = (mac_addw +
				     EMAC_WEG_EMAC_WX_STAT_AC_28) >> 2;
		dmae->swc_addw_hi = 0;
		dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, mac_stats) +
		     offsetof(stwuct emac_stats, wx_stat_fawsecawwiewewwows));
		dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats) +
		     offsetof(stwuct emac_stats, wx_stat_fawsecawwiewewwows));
		dmae->wen = 1;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;

		/* EMAC_WEG_EMAC_TX_STAT_AC (EMAC_WEG_EMAC_TX_STAT_AC_COUNT)*/
		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = (mac_addw +
				     EMAC_WEG_EMAC_TX_STAT_AC) >> 2;
		dmae->swc_addw_hi = 0;
		dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, mac_stats) +
			offsetof(stwuct emac_stats, tx_stat_ifhcoutoctets));
		dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats) +
			offsetof(stwuct emac_stats, tx_stat_ifhcoutoctets));
		dmae->wen = EMAC_WEG_EMAC_TX_STAT_AC_COUNT;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;
	} ewse {
		u32 tx_swc_addw_wo, wx_swc_addw_wo;
		u16 wx_wen, tx_wen;

		/* configuwe the pawams accowding to MAC type */
		switch (bp->wink_vaws.mac_type) {
		case MAC_TYPE_BMAC:
			mac_addw = (powt ? NIG_WEG_INGWESS_BMAC1_MEM :
					   NIG_WEG_INGWESS_BMAC0_MEM);

			/* BIGMAC_WEGISTEW_TX_STAT_GTPKT ..
			   BIGMAC_WEGISTEW_TX_STAT_GTBYT */
			if (CHIP_IS_E1x(bp)) {
				tx_swc_addw_wo = (mac_addw +
					BIGMAC_WEGISTEW_TX_STAT_GTPKT) >> 2;
				tx_wen = (8 + BIGMAC_WEGISTEW_TX_STAT_GTBYT -
					  BIGMAC_WEGISTEW_TX_STAT_GTPKT) >> 2;
				wx_swc_addw_wo = (mac_addw +
					BIGMAC_WEGISTEW_WX_STAT_GW64) >> 2;
				wx_wen = (8 + BIGMAC_WEGISTEW_WX_STAT_GWIPJ -
					  BIGMAC_WEGISTEW_WX_STAT_GW64) >> 2;
			} ewse {
				tx_swc_addw_wo = (mac_addw +
					BIGMAC2_WEGISTEW_TX_STAT_GTPOK) >> 2;
				tx_wen = (8 + BIGMAC2_WEGISTEW_TX_STAT_GTBYT -
					  BIGMAC2_WEGISTEW_TX_STAT_GTPOK) >> 2;
				wx_swc_addw_wo = (mac_addw +
					BIGMAC2_WEGISTEW_WX_STAT_GW64) >> 2;
				wx_wen = (8 + BIGMAC2_WEGISTEW_WX_STAT_GWIPJ -
					  BIGMAC2_WEGISTEW_WX_STAT_GW64) >> 2;
			}
			bweak;

		case MAC_TYPE_UMAC: /* handwed by MSTAT */
		case MAC_TYPE_XMAC: /* handwed by MSTAT */
		defauwt:
			mac_addw = powt ? GWCBASE_MSTAT1 : GWCBASE_MSTAT0;
			tx_swc_addw_wo = (mac_addw +
					  MSTAT_WEG_TX_STAT_GTXPOK_WO) >> 2;
			wx_swc_addw_wo = (mac_addw +
					  MSTAT_WEG_WX_STAT_GW64_WO) >> 2;
			tx_wen = sizeof(bp->swowpath->
					mac_stats.mstat_stats.stats_tx) >> 2;
			wx_wen = sizeof(bp->swowpath->
					mac_stats.mstat_stats.stats_wx) >> 2;
			bweak;
		}

		/* TX stats */
		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = tx_swc_addw_wo;
		dmae->swc_addw_hi = 0;
		dmae->wen = tx_wen;
		dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, mac_stats));
		dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, mac_stats));
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;

		/* WX stats */
		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_hi = 0;
		dmae->swc_addw_wo = wx_swc_addw_wo;
		dmae->dst_addw_wo =
			U64_WO(bnx2x_sp_mapping(bp, mac_stats) + (tx_wen << 2));
		dmae->dst_addw_hi =
			U64_HI(bnx2x_sp_mapping(bp, mac_stats) + (tx_wen << 2));
		dmae->wen = wx_wen;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;
	}

	/* NIG */
	if (!CHIP_IS_E3(bp)) {
		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = (powt ? NIG_WEG_STAT1_EGWESS_MAC_PKT0 :
					    NIG_WEG_STAT0_EGWESS_MAC_PKT0) >> 2;
		dmae->swc_addw_hi = 0;
		dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, nig_stats) +
				offsetof(stwuct nig_stats, egwess_mac_pkt0_wo));
		dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, nig_stats) +
				offsetof(stwuct nig_stats, egwess_mac_pkt0_wo));
		dmae->wen = (2*sizeof(u32)) >> 2;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;

		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode = opcode;
		dmae->swc_addw_wo = (powt ? NIG_WEG_STAT1_EGWESS_MAC_PKT1 :
					    NIG_WEG_STAT0_EGWESS_MAC_PKT1) >> 2;
		dmae->swc_addw_hi = 0;
		dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, nig_stats) +
				offsetof(stwuct nig_stats, egwess_mac_pkt1_wo));
		dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, nig_stats) +
				offsetof(stwuct nig_stats, egwess_mac_pkt1_wo));
		dmae->wen = (2*sizeof(u32)) >> 2;
		dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
		dmae->comp_addw_hi = 0;
		dmae->comp_vaw = 1;
	}

	dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SWC_GWC, DMAE_DST_PCI,
						 twue, DMAE_COMP_PCI);
	dmae->swc_addw_wo = (powt ? NIG_WEG_STAT1_BWB_DISCAWD :
				    NIG_WEG_STAT0_BWB_DISCAWD) >> 2;
	dmae->swc_addw_hi = 0;
	dmae->dst_addw_wo = U64_WO(bnx2x_sp_mapping(bp, nig_stats));
	dmae->dst_addw_hi = U64_HI(bnx2x_sp_mapping(bp, nig_stats));
	dmae->wen = (sizeof(stwuct nig_stats) - 4*sizeof(u32)) >> 2;

	dmae->comp_addw_wo = U64_WO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addw_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_vaw = DMAE_COMP_VAW;

	*stats_comp = 0;
}

static void bnx2x_func_stats_init(stwuct bnx2x *bp)
{
	stwuct dmae_command *dmae = &bp->stats_dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	if (!bp->func_stx) {
		BNX2X_EWW("BUG!\n");
		wetuwn;
	}

	bp->executew_idx = 0;
	memset(dmae, 0, sizeof(stwuct dmae_command));

	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SWC_PCI, DMAE_DST_GWC,
					 twue, DMAE_COMP_PCI);
	dmae->swc_addw_wo = U64_WO(bnx2x_sp_mapping(bp, func_stats));
	dmae->swc_addw_hi = U64_HI(bnx2x_sp_mapping(bp, func_stats));
	dmae->dst_addw_wo = bp->func_stx >> 2;
	dmae->dst_addw_hi = 0;
	dmae->wen = sizeof(stwuct host_func_stats) >> 2;
	dmae->comp_addw_wo = U64_WO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addw_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_vaw = DMAE_COMP_VAW;

	*stats_comp = 0;
}

/* shouwd be cawwed undew stats_sema */
static void bnx2x_stats_stawt(stwuct bnx2x *bp)
{
	if (IS_PF(bp)) {
		if (bp->powt.pmf)
			bnx2x_powt_stats_init(bp);

		ewse if (bp->func_stx)
			bnx2x_func_stats_init(bp);

		bnx2x_hw_stats_post(bp);
		bnx2x_stowm_stats_post(bp);
	}
}

static void bnx2x_stats_pmf_stawt(stwuct bnx2x *bp)
{
	bnx2x_stats_comp(bp);
	bnx2x_stats_pmf_update(bp);
	bnx2x_stats_stawt(bp);
}

static void bnx2x_stats_westawt(stwuct bnx2x *bp)
{
	/* vfs twavew thwough hewe as pawt of the statistics FSM, but no action
	 * is wequiwed
	 */
	if (IS_VF(bp))
		wetuwn;

	bnx2x_stats_comp(bp);
	bnx2x_stats_stawt(bp);
}

static void bnx2x_bmac_stats_update(stwuct bnx2x *bp)
{
	stwuct host_powt_stats *pstats = bnx2x_sp(bp, powt_stats);
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;
	stwuct {
		u32 wo;
		u32 hi;
	} diff;

	if (CHIP_IS_E1x(bp)) {
		stwuct bmac1_stats *new = bnx2x_sp(bp, mac_stats.bmac1_stats);

		/* the macwos bewow wiww use "bmac1_stats" type */
		UPDATE_STAT64(wx_stat_gwewb, wx_stat_ifhcinbadoctets);
		UPDATE_STAT64(wx_stat_gwfcs, wx_stat_dot3statsfcsewwows);
		UPDATE_STAT64(wx_stat_gwund, wx_stat_ethewstatsundewsizepkts);
		UPDATE_STAT64(wx_stat_gwovw, wx_stat_dot3statsfwamestoowong);
		UPDATE_STAT64(wx_stat_gwfwg, wx_stat_ethewstatsfwagments);
		UPDATE_STAT64(wx_stat_gwjbw, wx_stat_ethewstatsjabbews);
		UPDATE_STAT64(wx_stat_gwxcf, wx_stat_maccontwowfwamesweceived);
		UPDATE_STAT64(wx_stat_gwxpf, wx_stat_xoffstateentewed);
		UPDATE_STAT64(wx_stat_gwxpf, wx_stat_mac_xpf);

		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_outxoffsent);
		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_fwowcontwowdone);
		UPDATE_STAT64(tx_stat_gt64, tx_stat_ethewstatspkts64octets);
		UPDATE_STAT64(tx_stat_gt127,
				tx_stat_ethewstatspkts65octetsto127octets);
		UPDATE_STAT64(tx_stat_gt255,
				tx_stat_ethewstatspkts128octetsto255octets);
		UPDATE_STAT64(tx_stat_gt511,
				tx_stat_ethewstatspkts256octetsto511octets);
		UPDATE_STAT64(tx_stat_gt1023,
				tx_stat_ethewstatspkts512octetsto1023octets);
		UPDATE_STAT64(tx_stat_gt1518,
				tx_stat_ethewstatspkts1024octetsto1522octets);
		UPDATE_STAT64(tx_stat_gt2047, tx_stat_mac_2047);
		UPDATE_STAT64(tx_stat_gt4095, tx_stat_mac_4095);
		UPDATE_STAT64(tx_stat_gt9216, tx_stat_mac_9216);
		UPDATE_STAT64(tx_stat_gt16383, tx_stat_mac_16383);
		UPDATE_STAT64(tx_stat_gteww,
				tx_stat_dot3statsintewnawmactwansmitewwows);
		UPDATE_STAT64(tx_stat_gtufw, tx_stat_mac_ufw);

	} ewse {
		stwuct bmac2_stats *new = bnx2x_sp(bp, mac_stats.bmac2_stats);

		/* the macwos bewow wiww use "bmac2_stats" type */
		UPDATE_STAT64(wx_stat_gwewb, wx_stat_ifhcinbadoctets);
		UPDATE_STAT64(wx_stat_gwfcs, wx_stat_dot3statsfcsewwows);
		UPDATE_STAT64(wx_stat_gwund, wx_stat_ethewstatsundewsizepkts);
		UPDATE_STAT64(wx_stat_gwovw, wx_stat_dot3statsfwamestoowong);
		UPDATE_STAT64(wx_stat_gwfwg, wx_stat_ethewstatsfwagments);
		UPDATE_STAT64(wx_stat_gwjbw, wx_stat_ethewstatsjabbews);
		UPDATE_STAT64(wx_stat_gwxcf, wx_stat_maccontwowfwamesweceived);
		UPDATE_STAT64(wx_stat_gwxpf, wx_stat_xoffstateentewed);
		UPDATE_STAT64(wx_stat_gwxpf, wx_stat_mac_xpf);
		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_outxoffsent);
		UPDATE_STAT64(tx_stat_gtxpf, tx_stat_fwowcontwowdone);
		UPDATE_STAT64(tx_stat_gt64, tx_stat_ethewstatspkts64octets);
		UPDATE_STAT64(tx_stat_gt127,
				tx_stat_ethewstatspkts65octetsto127octets);
		UPDATE_STAT64(tx_stat_gt255,
				tx_stat_ethewstatspkts128octetsto255octets);
		UPDATE_STAT64(tx_stat_gt511,
				tx_stat_ethewstatspkts256octetsto511octets);
		UPDATE_STAT64(tx_stat_gt1023,
				tx_stat_ethewstatspkts512octetsto1023octets);
		UPDATE_STAT64(tx_stat_gt1518,
				tx_stat_ethewstatspkts1024octetsto1522octets);
		UPDATE_STAT64(tx_stat_gt2047, tx_stat_mac_2047);
		UPDATE_STAT64(tx_stat_gt4095, tx_stat_mac_4095);
		UPDATE_STAT64(tx_stat_gt9216, tx_stat_mac_9216);
		UPDATE_STAT64(tx_stat_gt16383, tx_stat_mac_16383);
		UPDATE_STAT64(tx_stat_gteww,
				tx_stat_dot3statsintewnawmactwansmitewwows);
		UPDATE_STAT64(tx_stat_gtufw, tx_stat_mac_ufw);

		/* cowwect PFC stats */
		pstats->pfc_fwames_tx_hi = new->tx_stat_gtpp_hi;
		pstats->pfc_fwames_tx_wo = new->tx_stat_gtpp_wo;

		pstats->pfc_fwames_wx_hi = new->wx_stat_gwpp_hi;
		pstats->pfc_fwames_wx_wo = new->wx_stat_gwpp_wo;
	}

	estats->pause_fwames_weceived_hi =
				pstats->mac_stx[1].wx_stat_mac_xpf_hi;
	estats->pause_fwames_weceived_wo =
				pstats->mac_stx[1].wx_stat_mac_xpf_wo;

	estats->pause_fwames_sent_hi =
				pstats->mac_stx[1].tx_stat_outxoffsent_hi;
	estats->pause_fwames_sent_wo =
				pstats->mac_stx[1].tx_stat_outxoffsent_wo;

	estats->pfc_fwames_weceived_hi =
				pstats->pfc_fwames_wx_hi;
	estats->pfc_fwames_weceived_wo =
				pstats->pfc_fwames_wx_wo;
	estats->pfc_fwames_sent_hi =
				pstats->pfc_fwames_tx_hi;
	estats->pfc_fwames_sent_wo =
				pstats->pfc_fwames_tx_wo;
}

static void bnx2x_mstat_stats_update(stwuct bnx2x *bp)
{
	stwuct host_powt_stats *pstats = bnx2x_sp(bp, powt_stats);
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;

	stwuct mstat_stats *new = bnx2x_sp(bp, mac_stats.mstat_stats);

	ADD_STAT64(stats_wx.wx_gwewb, wx_stat_ifhcinbadoctets);
	ADD_STAT64(stats_wx.wx_gwfcs, wx_stat_dot3statsfcsewwows);
	ADD_STAT64(stats_wx.wx_gwund, wx_stat_ethewstatsundewsizepkts);
	ADD_STAT64(stats_wx.wx_gwovw, wx_stat_dot3statsfwamestoowong);
	ADD_STAT64(stats_wx.wx_gwfwg, wx_stat_ethewstatsfwagments);
	ADD_STAT64(stats_wx.wx_gwxcf, wx_stat_maccontwowfwamesweceived);
	ADD_STAT64(stats_wx.wx_gwxpf, wx_stat_xoffstateentewed);
	ADD_STAT64(stats_wx.wx_gwxpf, wx_stat_mac_xpf);
	ADD_STAT64(stats_tx.tx_gtxpf, tx_stat_outxoffsent);
	ADD_STAT64(stats_tx.tx_gtxpf, tx_stat_fwowcontwowdone);

	/* cowwect pfc stats */
	ADD_64(pstats->pfc_fwames_tx_hi, new->stats_tx.tx_gtxpp_hi,
		pstats->pfc_fwames_tx_wo, new->stats_tx.tx_gtxpp_wo);
	ADD_64(pstats->pfc_fwames_wx_hi, new->stats_wx.wx_gwxpp_hi,
		pstats->pfc_fwames_wx_wo, new->stats_wx.wx_gwxpp_wo);

	ADD_STAT64(stats_tx.tx_gt64, tx_stat_ethewstatspkts64octets);
	ADD_STAT64(stats_tx.tx_gt127,
			tx_stat_ethewstatspkts65octetsto127octets);
	ADD_STAT64(stats_tx.tx_gt255,
			tx_stat_ethewstatspkts128octetsto255octets);
	ADD_STAT64(stats_tx.tx_gt511,
			tx_stat_ethewstatspkts256octetsto511octets);
	ADD_STAT64(stats_tx.tx_gt1023,
			tx_stat_ethewstatspkts512octetsto1023octets);
	ADD_STAT64(stats_tx.tx_gt1518,
			tx_stat_ethewstatspkts1024octetsto1522octets);
	ADD_STAT64(stats_tx.tx_gt2047, tx_stat_mac_2047);

	ADD_STAT64(stats_tx.tx_gt4095, tx_stat_mac_4095);
	ADD_STAT64(stats_tx.tx_gt9216, tx_stat_mac_9216);
	ADD_STAT64(stats_tx.tx_gt16383, tx_stat_mac_16383);

	ADD_STAT64(stats_tx.tx_gteww,
			tx_stat_dot3statsintewnawmactwansmitewwows);
	ADD_STAT64(stats_tx.tx_gtufw, tx_stat_mac_ufw);

	estats->ethewstatspkts1024octetsto1522octets_hi =
	    pstats->mac_stx[1].tx_stat_ethewstatspkts1024octetsto1522octets_hi;
	estats->ethewstatspkts1024octetsto1522octets_wo =
	    pstats->mac_stx[1].tx_stat_ethewstatspkts1024octetsto1522octets_wo;

	estats->ethewstatspktsovew1522octets_hi =
	    pstats->mac_stx[1].tx_stat_mac_2047_hi;
	estats->ethewstatspktsovew1522octets_wo =
	    pstats->mac_stx[1].tx_stat_mac_2047_wo;

	ADD_64(estats->ethewstatspktsovew1522octets_hi,
	       pstats->mac_stx[1].tx_stat_mac_4095_hi,
	       estats->ethewstatspktsovew1522octets_wo,
	       pstats->mac_stx[1].tx_stat_mac_4095_wo);

	ADD_64(estats->ethewstatspktsovew1522octets_hi,
	       pstats->mac_stx[1].tx_stat_mac_9216_hi,
	       estats->ethewstatspktsovew1522octets_wo,
	       pstats->mac_stx[1].tx_stat_mac_9216_wo);

	ADD_64(estats->ethewstatspktsovew1522octets_hi,
	       pstats->mac_stx[1].tx_stat_mac_16383_hi,
	       estats->ethewstatspktsovew1522octets_wo,
	       pstats->mac_stx[1].tx_stat_mac_16383_wo);

	estats->pause_fwames_weceived_hi =
				pstats->mac_stx[1].wx_stat_mac_xpf_hi;
	estats->pause_fwames_weceived_wo =
				pstats->mac_stx[1].wx_stat_mac_xpf_wo;

	estats->pause_fwames_sent_hi =
				pstats->mac_stx[1].tx_stat_outxoffsent_hi;
	estats->pause_fwames_sent_wo =
				pstats->mac_stx[1].tx_stat_outxoffsent_wo;

	estats->pfc_fwames_weceived_hi =
				pstats->pfc_fwames_wx_hi;
	estats->pfc_fwames_weceived_wo =
				pstats->pfc_fwames_wx_wo;
	estats->pfc_fwames_sent_hi =
				pstats->pfc_fwames_tx_hi;
	estats->pfc_fwames_sent_wo =
				pstats->pfc_fwames_tx_wo;
}

static void bnx2x_emac_stats_update(stwuct bnx2x *bp)
{
	stwuct emac_stats *new = bnx2x_sp(bp, mac_stats.emac_stats);
	stwuct host_powt_stats *pstats = bnx2x_sp(bp, powt_stats);
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;

	UPDATE_EXTEND_STAT(wx_stat_ifhcinbadoctets);
	UPDATE_EXTEND_STAT(tx_stat_ifhcoutbadoctets);
	UPDATE_EXTEND_STAT(wx_stat_dot3statsfcsewwows);
	UPDATE_EXTEND_STAT(wx_stat_dot3statsawignmentewwows);
	UPDATE_EXTEND_STAT(wx_stat_dot3statscawwiewsenseewwows);
	UPDATE_EXTEND_STAT(wx_stat_fawsecawwiewewwows);
	UPDATE_EXTEND_STAT(wx_stat_ethewstatsundewsizepkts);
	UPDATE_EXTEND_STAT(wx_stat_dot3statsfwamestoowong);
	UPDATE_EXTEND_STAT(wx_stat_ethewstatsfwagments);
	UPDATE_EXTEND_STAT(wx_stat_ethewstatsjabbews);
	UPDATE_EXTEND_STAT(wx_stat_maccontwowfwamesweceived);
	UPDATE_EXTEND_STAT(wx_stat_xoffstateentewed);
	UPDATE_EXTEND_STAT(wx_stat_xonpausefwamesweceived);
	UPDATE_EXTEND_STAT(wx_stat_xoffpausefwamesweceived);
	UPDATE_EXTEND_STAT(tx_stat_outxonsent);
	UPDATE_EXTEND_STAT(tx_stat_outxoffsent);
	UPDATE_EXTEND_STAT(tx_stat_fwowcontwowdone);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatscowwisions);
	UPDATE_EXTEND_STAT(tx_stat_dot3statssingwecowwisionfwames);
	UPDATE_EXTEND_STAT(tx_stat_dot3statsmuwtipwecowwisionfwames);
	UPDATE_EXTEND_STAT(tx_stat_dot3statsdefewwedtwansmissions);
	UPDATE_EXTEND_STAT(tx_stat_dot3statsexcessivecowwisions);
	UPDATE_EXTEND_STAT(tx_stat_dot3statswatecowwisions);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatspkts64octets);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatspkts65octetsto127octets);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatspkts128octetsto255octets);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatspkts256octetsto511octets);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatspkts512octetsto1023octets);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatspkts1024octetsto1522octets);
	UPDATE_EXTEND_STAT(tx_stat_ethewstatspktsovew1522octets);
	UPDATE_EXTEND_STAT(tx_stat_dot3statsintewnawmactwansmitewwows);

	estats->pause_fwames_weceived_hi =
			pstats->mac_stx[1].wx_stat_xonpausefwamesweceived_hi;
	estats->pause_fwames_weceived_wo =
			pstats->mac_stx[1].wx_stat_xonpausefwamesweceived_wo;
	ADD_64(estats->pause_fwames_weceived_hi,
	       pstats->mac_stx[1].wx_stat_xoffpausefwamesweceived_hi,
	       estats->pause_fwames_weceived_wo,
	       pstats->mac_stx[1].wx_stat_xoffpausefwamesweceived_wo);

	estats->pause_fwames_sent_hi =
			pstats->mac_stx[1].tx_stat_outxonsent_hi;
	estats->pause_fwames_sent_wo =
			pstats->mac_stx[1].tx_stat_outxonsent_wo;
	ADD_64(estats->pause_fwames_sent_hi,
	       pstats->mac_stx[1].tx_stat_outxoffsent_hi,
	       estats->pause_fwames_sent_wo,
	       pstats->mac_stx[1].tx_stat_outxoffsent_wo);
}

static int bnx2x_hw_stats_update(stwuct bnx2x *bp)
{
	stwuct nig_stats *new = bnx2x_sp(bp, nig_stats);
	stwuct nig_stats *owd = &(bp->powt.owd_nig_stats);
	stwuct host_powt_stats *pstats = bnx2x_sp(bp, powt_stats);
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;
	stwuct {
		u32 wo;
		u32 hi;
	} diff;

	switch (bp->wink_vaws.mac_type) {
	case MAC_TYPE_BMAC:
		bnx2x_bmac_stats_update(bp);
		bweak;

	case MAC_TYPE_EMAC:
		bnx2x_emac_stats_update(bp);
		bweak;

	case MAC_TYPE_UMAC:
	case MAC_TYPE_XMAC:
		bnx2x_mstat_stats_update(bp);
		bweak;

	case MAC_TYPE_NONE: /* unweached */
		DP(BNX2X_MSG_STATS,
		   "stats updated by DMAE but no MAC active\n");
		wetuwn -1;

	defauwt: /* unweached */
		BNX2X_EWW("Unknown MAC type\n");
	}

	ADD_EXTEND_64(pstats->bwb_dwop_hi, pstats->bwb_dwop_wo,
		      new->bwb_discawd - owd->bwb_discawd);
	ADD_EXTEND_64(estats->bwb_twuncate_hi, estats->bwb_twuncate_wo,
		      new->bwb_twuncate - owd->bwb_twuncate);

	if (!CHIP_IS_E3(bp)) {
		UPDATE_STAT64_NIG(egwess_mac_pkt0,
					ethewstatspkts1024octetsto1522octets);
		UPDATE_STAT64_NIG(egwess_mac_pkt1,
					ethewstatspktsovew1522octets);
	}

	memcpy(owd, new, sizeof(stwuct nig_stats));

	BUIWD_BUG_ON(sizeof(estats->shawed) != sizeof(pstats->mac_stx[1]));
	memcpy(&(estats->shawed), &(pstats->mac_stx[1]),
	       sizeof(stwuct mac_stx));
	estats->bwb_dwop_hi = pstats->bwb_dwop_hi;
	estats->bwb_dwop_wo = pstats->bwb_dwop_wo;

	pstats->host_powt_stats_countew++;

	if (CHIP_IS_E3(bp)) {
		u32 wpi_weg = BP_POWT(bp) ? MISC_WEG_CPMU_WP_SM_ENT_CNT_P1
					  : MISC_WEG_CPMU_WP_SM_ENT_CNT_P0;
		estats->eee_tx_wpi += WEG_WD(bp, wpi_weg);
	}

	if (!BP_NOMCP(bp)) {
		u32 nig_timew_max =
			SHMEM_WD(bp, powt_mb[BP_POWT(bp)].stat_nig_timew);
		if (nig_timew_max != estats->nig_timew_max) {
			estats->nig_timew_max = nig_timew_max;
			BNX2X_EWW("NIG timew max (%u)\n",
				  estats->nig_timew_max);
		}
	}

	wetuwn 0;
}

static int bnx2x_stowm_stats_vawidate_countews(stwuct bnx2x *bp)
{
	stwuct stats_countew *countews = &bp->fw_stats_data->stowm_countews;
	u16 cuw_stats_countew;
	/* Make suwe we use the vawue of the countew
	 * used fow sending the wast stats wamwod.
	 */
	cuw_stats_countew = bp->stats_countew - 1;

	/* awe stowm stats vawid? */
	if (we16_to_cpu(countews->xstats_countew) != cuw_stats_countew) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by xstowm  xstowm countew (0x%x) != stats_countew (0x%x)\n",
		   we16_to_cpu(countews->xstats_countew), bp->stats_countew);
		wetuwn -EAGAIN;
	}

	if (we16_to_cpu(countews->ustats_countew) != cuw_stats_countew) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by ustowm  ustowm countew (0x%x) != stats_countew (0x%x)\n",
		   we16_to_cpu(countews->ustats_countew), bp->stats_countew);
		wetuwn -EAGAIN;
	}

	if (we16_to_cpu(countews->cstats_countew) != cuw_stats_countew) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by cstowm  cstowm countew (0x%x) != stats_countew (0x%x)\n",
		   we16_to_cpu(countews->cstats_countew), bp->stats_countew);
		wetuwn -EAGAIN;
	}

	if (we16_to_cpu(countews->tstats_countew) != cuw_stats_countew) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by tstowm  tstowm countew (0x%x) != stats_countew (0x%x)\n",
		   we16_to_cpu(countews->tstats_countew), bp->stats_countew);
		wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static int bnx2x_stowm_stats_update(stwuct bnx2x *bp)
{
	stwuct tstowm_pew_powt_stats *tpowt =
				&bp->fw_stats_data->powt.tstowm_powt_statistics;
	stwuct tstowm_pew_pf_stats *tfunc =
				&bp->fw_stats_data->pf.tstowm_pf_statistics;
	stwuct host_func_stats *fstats = &bp->func_stats;
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;
	stwuct bnx2x_eth_stats_owd *estats_owd = &bp->eth_stats_owd;
	int i;

	/* vfs stat countew is managed by pf */
	if (IS_PF(bp) && bnx2x_stowm_stats_vawidate_countews(bp))
		wetuwn -EAGAIN;

	estats->ewwow_bytes_weceived_hi = 0;
	estats->ewwow_bytes_weceived_wo = 0;

	fow_each_eth_queue(bp, i) {
		stwuct bnx2x_fastpath *fp = &bp->fp[i];
		stwuct tstowm_pew_queue_stats *tcwient =
			&bp->fw_stats_data->queue_stats[i].
			tstowm_queue_statistics;
		stwuct tstowm_pew_queue_stats *owd_tcwient =
			&bnx2x_fp_stats(bp, fp)->owd_tcwient;
		stwuct ustowm_pew_queue_stats *ucwient =
			&bp->fw_stats_data->queue_stats[i].
			ustowm_queue_statistics;
		stwuct ustowm_pew_queue_stats *owd_ucwient =
			&bnx2x_fp_stats(bp, fp)->owd_ucwient;
		stwuct xstowm_pew_queue_stats *xcwient =
			&bp->fw_stats_data->queue_stats[i].
			xstowm_queue_statistics;
		stwuct xstowm_pew_queue_stats *owd_xcwient =
			&bnx2x_fp_stats(bp, fp)->owd_xcwient;
		stwuct bnx2x_eth_q_stats *qstats =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats;
		stwuct bnx2x_eth_q_stats_owd *qstats_owd =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats_owd;

		u32 diff;

		DP(BNX2X_MSG_STATS, "queue[%d]: ucast_sent 0x%x, bcast_sent 0x%x mcast_sent 0x%x\n",
		   i, xcwient->ucast_pkts_sent,
		   xcwient->bcast_pkts_sent, xcwient->mcast_pkts_sent);

		DP(BNX2X_MSG_STATS, "---------------\n");

		UPDATE_QSTAT(tcwient->wcv_bcast_bytes,
			     totaw_bwoadcast_bytes_weceived);
		UPDATE_QSTAT(tcwient->wcv_mcast_bytes,
			     totaw_muwticast_bytes_weceived);
		UPDATE_QSTAT(tcwient->wcv_ucast_bytes,
			     totaw_unicast_bytes_weceived);

		/*
		 * sum to totaw_bytes_weceived aww
		 * unicast/muwticast/bwoadcast
		 */
		qstats->totaw_bytes_weceived_hi =
			qstats->totaw_bwoadcast_bytes_weceived_hi;
		qstats->totaw_bytes_weceived_wo =
			qstats->totaw_bwoadcast_bytes_weceived_wo;

		ADD_64(qstats->totaw_bytes_weceived_hi,
		       qstats->totaw_muwticast_bytes_weceived_hi,
		       qstats->totaw_bytes_weceived_wo,
		       qstats->totaw_muwticast_bytes_weceived_wo);

		ADD_64(qstats->totaw_bytes_weceived_hi,
		       qstats->totaw_unicast_bytes_weceived_hi,
		       qstats->totaw_bytes_weceived_wo,
		       qstats->totaw_unicast_bytes_weceived_wo);

		qstats->vawid_bytes_weceived_hi =
					qstats->totaw_bytes_weceived_hi;
		qstats->vawid_bytes_weceived_wo =
					qstats->totaw_bytes_weceived_wo;

		UPDATE_EXTEND_TSTAT(wcv_ucast_pkts,
					totaw_unicast_packets_weceived);
		UPDATE_EXTEND_TSTAT(wcv_mcast_pkts,
					totaw_muwticast_packets_weceived);
		UPDATE_EXTEND_TSTAT(wcv_bcast_pkts,
					totaw_bwoadcast_packets_weceived);
		UPDATE_EXTEND_E_TSTAT(pkts_too_big_discawd,
				      ethewstatsovewwsizepkts, 32);
		UPDATE_EXTEND_E_TSTAT(no_buff_discawd, no_buff_discawd, 16);

		SUB_EXTEND_USTAT(ucast_no_buff_pkts,
					totaw_unicast_packets_weceived);
		SUB_EXTEND_USTAT(mcast_no_buff_pkts,
					totaw_muwticast_packets_weceived);
		SUB_EXTEND_USTAT(bcast_no_buff_pkts,
					totaw_bwoadcast_packets_weceived);
		UPDATE_EXTEND_E_USTAT(ucast_no_buff_pkts, no_buff_discawd);
		UPDATE_EXTEND_E_USTAT(mcast_no_buff_pkts, no_buff_discawd);
		UPDATE_EXTEND_E_USTAT(bcast_no_buff_pkts, no_buff_discawd);

		UPDATE_QSTAT(xcwient->bcast_bytes_sent,
			     totaw_bwoadcast_bytes_twansmitted);
		UPDATE_QSTAT(xcwient->mcast_bytes_sent,
			     totaw_muwticast_bytes_twansmitted);
		UPDATE_QSTAT(xcwient->ucast_bytes_sent,
			     totaw_unicast_bytes_twansmitted);

		/*
		 * sum to totaw_bytes_twansmitted aww
		 * unicast/muwticast/bwoadcast
		 */
		qstats->totaw_bytes_twansmitted_hi =
				qstats->totaw_unicast_bytes_twansmitted_hi;
		qstats->totaw_bytes_twansmitted_wo =
				qstats->totaw_unicast_bytes_twansmitted_wo;

		ADD_64(qstats->totaw_bytes_twansmitted_hi,
		       qstats->totaw_bwoadcast_bytes_twansmitted_hi,
		       qstats->totaw_bytes_twansmitted_wo,
		       qstats->totaw_bwoadcast_bytes_twansmitted_wo);

		ADD_64(qstats->totaw_bytes_twansmitted_hi,
		       qstats->totaw_muwticast_bytes_twansmitted_hi,
		       qstats->totaw_bytes_twansmitted_wo,
		       qstats->totaw_muwticast_bytes_twansmitted_wo);

		UPDATE_EXTEND_XSTAT(ucast_pkts_sent,
					totaw_unicast_packets_twansmitted);
		UPDATE_EXTEND_XSTAT(mcast_pkts_sent,
					totaw_muwticast_packets_twansmitted);
		UPDATE_EXTEND_XSTAT(bcast_pkts_sent,
					totaw_bwoadcast_packets_twansmitted);

		UPDATE_EXTEND_TSTAT(checksum_discawd,
				    totaw_packets_weceived_checksum_discawded);
		UPDATE_EXTEND_TSTAT(ttw0_discawd,
				    totaw_packets_weceived_ttw0_discawded);

		UPDATE_EXTEND_XSTAT(ewwow_dwop_pkts,
				    totaw_twansmitted_dwopped_packets_ewwow);

		/* TPA aggwegations compweted */
		UPDATE_EXTEND_E_USTAT(coawesced_events, totaw_tpa_aggwegations);
		/* Numbew of netwowk fwames aggwegated by TPA */
		UPDATE_EXTEND_E_USTAT(coawesced_pkts,
				      totaw_tpa_aggwegated_fwames);
		/* Totaw numbew of bytes in compweted TPA aggwegations */
		UPDATE_QSTAT(ucwient->coawesced_bytes, totaw_tpa_bytes);

		UPDATE_ESTAT_QSTAT_64(totaw_tpa_bytes);

		UPDATE_FSTAT_QSTAT(totaw_bytes_weceived);
		UPDATE_FSTAT_QSTAT(totaw_bytes_twansmitted);
		UPDATE_FSTAT_QSTAT(totaw_unicast_packets_weceived);
		UPDATE_FSTAT_QSTAT(totaw_muwticast_packets_weceived);
		UPDATE_FSTAT_QSTAT(totaw_bwoadcast_packets_weceived);
		UPDATE_FSTAT_QSTAT(totaw_unicast_packets_twansmitted);
		UPDATE_FSTAT_QSTAT(totaw_muwticast_packets_twansmitted);
		UPDATE_FSTAT_QSTAT(totaw_bwoadcast_packets_twansmitted);
		UPDATE_FSTAT_QSTAT(vawid_bytes_weceived);
	}

	ADD_64(estats->totaw_bytes_weceived_hi,
	       estats->wx_stat_ifhcinbadoctets_hi,
	       estats->totaw_bytes_weceived_wo,
	       estats->wx_stat_ifhcinbadoctets_wo);

	ADD_64_WE(estats->totaw_bytes_weceived_hi,
		  tfunc->wcv_ewwow_bytes.hi,
		  estats->totaw_bytes_weceived_wo,
		  tfunc->wcv_ewwow_bytes.wo);

	ADD_64_WE(estats->ewwow_bytes_weceived_hi,
		  tfunc->wcv_ewwow_bytes.hi,
		  estats->ewwow_bytes_weceived_wo,
		  tfunc->wcv_ewwow_bytes.wo);

	UPDATE_ESTAT(ethewstatsovewwsizepkts, wx_stat_dot3statsfwamestoowong);

	ADD_64(estats->ewwow_bytes_weceived_hi,
	       estats->wx_stat_ifhcinbadoctets_hi,
	       estats->ewwow_bytes_weceived_wo,
	       estats->wx_stat_ifhcinbadoctets_wo);

	if (bp->powt.pmf) {
		stwuct bnx2x_fw_powt_stats_owd *fwstats = &bp->fw_stats_owd;
		UPDATE_FW_STAT(mac_fiwtew_discawd);
		UPDATE_FW_STAT(mf_tag_discawd);
		UPDATE_FW_STAT(bwb_twuncate_discawd);
		UPDATE_FW_STAT(mac_discawd);
	}

	fstats->host_func_stats_stawt = ++fstats->host_func_stats_end;

	bp->stats_pending = 0;

	wetuwn 0;
}

static void bnx2x_net_stats_update(stwuct bnx2x *bp)
{
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;
	stwuct net_device_stats *nstats = &bp->dev->stats;
	unsigned wong tmp;
	int i;

	nstats->wx_packets =
		bnx2x_hiwo(&estats->totaw_unicast_packets_weceived_hi) +
		bnx2x_hiwo(&estats->totaw_muwticast_packets_weceived_hi) +
		bnx2x_hiwo(&estats->totaw_bwoadcast_packets_weceived_hi);

	nstats->tx_packets =
		bnx2x_hiwo(&estats->totaw_unicast_packets_twansmitted_hi) +
		bnx2x_hiwo(&estats->totaw_muwticast_packets_twansmitted_hi) +
		bnx2x_hiwo(&estats->totaw_bwoadcast_packets_twansmitted_hi);

	nstats->wx_bytes = bnx2x_hiwo(&estats->totaw_bytes_weceived_hi);

	nstats->tx_bytes = bnx2x_hiwo(&estats->totaw_bytes_twansmitted_hi);

	tmp = estats->mac_discawd;
	fow_each_wx_queue(bp, i) {
		stwuct tstowm_pew_queue_stats *owd_tcwient =
			&bp->fp_stats[i].owd_tcwient;
		tmp += we32_to_cpu(owd_tcwient->checksum_discawd);
	}
	nstats->wx_dwopped = tmp + bp->net_stats_owd.wx_dwopped;

	nstats->tx_dwopped = 0;

	nstats->muwticast =
		bnx2x_hiwo(&estats->totaw_muwticast_packets_weceived_hi);

	nstats->cowwisions =
		bnx2x_hiwo(&estats->tx_stat_ethewstatscowwisions_hi);

	nstats->wx_wength_ewwows =
		bnx2x_hiwo(&estats->wx_stat_ethewstatsundewsizepkts_hi) +
		bnx2x_hiwo(&estats->ethewstatsovewwsizepkts_hi);
	nstats->wx_ovew_ewwows = bnx2x_hiwo(&estats->bwb_dwop_hi) +
				 bnx2x_hiwo(&estats->bwb_twuncate_hi);
	nstats->wx_cwc_ewwows =
		bnx2x_hiwo(&estats->wx_stat_dot3statsfcsewwows_hi);
	nstats->wx_fwame_ewwows =
		bnx2x_hiwo(&estats->wx_stat_dot3statsawignmentewwows_hi);
	nstats->wx_fifo_ewwows = bnx2x_hiwo(&estats->no_buff_discawd_hi);
	nstats->wx_missed_ewwows = 0;

	nstats->wx_ewwows = nstats->wx_wength_ewwows +
			    nstats->wx_ovew_ewwows +
			    nstats->wx_cwc_ewwows +
			    nstats->wx_fwame_ewwows +
			    nstats->wx_fifo_ewwows +
			    nstats->wx_missed_ewwows;

	nstats->tx_abowted_ewwows =
		bnx2x_hiwo(&estats->tx_stat_dot3statswatecowwisions_hi) +
		bnx2x_hiwo(&estats->tx_stat_dot3statsexcessivecowwisions_hi);
	nstats->tx_cawwiew_ewwows =
		bnx2x_hiwo(&estats->wx_stat_dot3statscawwiewsenseewwows_hi);
	nstats->tx_fifo_ewwows = 0;
	nstats->tx_heawtbeat_ewwows = 0;
	nstats->tx_window_ewwows = 0;

	nstats->tx_ewwows = nstats->tx_abowted_ewwows +
			    nstats->tx_cawwiew_ewwows +
	    bnx2x_hiwo(&estats->tx_stat_dot3statsintewnawmactwansmitewwows_hi);
}

static void bnx2x_dwv_stats_update(stwuct bnx2x *bp)
{
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;
	int i;

	fow_each_queue(bp, i) {
		stwuct bnx2x_eth_q_stats *qstats = &bp->fp_stats[i].eth_q_stats;
		stwuct bnx2x_eth_q_stats_owd *qstats_owd =
			&bp->fp_stats[i].eth_q_stats_owd;

		UPDATE_ESTAT_QSTAT(dwivew_xoff);
		UPDATE_ESTAT_QSTAT(wx_eww_discawd_pkt);
		UPDATE_ESTAT_QSTAT(wx_skb_awwoc_faiwed);
		UPDATE_ESTAT_QSTAT(hw_csum_eww);
		UPDATE_ESTAT_QSTAT(dwivew_fiwtewed_tx_pkt);
	}
}

static boow bnx2x_edebug_stats_stopped(stwuct bnx2x *bp)
{
	u32 vaw;

	if (SHMEM2_HAS(bp, edebug_dwivew_if[1])) {
		vaw = SHMEM2_WD(bp, edebug_dwivew_if[1]);

		if (vaw == EDEBUG_DWIVEW_IF_OP_CODE_DISABWE_STAT)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void bnx2x_stats_update(stwuct bnx2x *bp)
{
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	if (bnx2x_edebug_stats_stopped(bp))
		wetuwn;

	if (IS_PF(bp)) {
		if (*stats_comp != DMAE_COMP_VAW)
			wetuwn;

		if (bp->powt.pmf)
			bnx2x_hw_stats_update(bp);

		if (bnx2x_stowm_stats_update(bp)) {
			if (bp->stats_pending++ == 3) {
				BNX2X_EWW("stowm stats wewe not updated fow 3 times\n");
				bnx2x_panic();
			}
			wetuwn;
		}
	} ewse {
		/* vf doesn't cowwect HW statistics, and doesn't get compwetions
		 * pewfowm onwy update
		 */
		bnx2x_stowm_stats_update(bp);
	}

	bnx2x_net_stats_update(bp);
	bnx2x_dwv_stats_update(bp);

	/* vf is done */
	if (IS_VF(bp))
		wetuwn;

	if (netif_msg_timew(bp)) {
		stwuct bnx2x_eth_stats *estats = &bp->eth_stats;

		netdev_dbg(bp->dev, "bwb dwops %u  bwb twuncate %u\n",
		       estats->bwb_dwop_wo, estats->bwb_twuncate_wo);
	}

	bnx2x_hw_stats_post(bp);
	bnx2x_stowm_stats_post(bp);
}

static void bnx2x_powt_stats_stop(stwuct bnx2x *bp)
{
	stwuct dmae_command *dmae;
	u32 opcode;
	int woadew_idx = PMF_DMAE_C(bp);
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	bp->executew_idx = 0;

	opcode = bnx2x_dmae_opcode(bp, DMAE_SWC_PCI, DMAE_DST_GWC, fawse, 0);

	if (bp->powt.powt_stx) {

		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		if (bp->func_stx)
			dmae->opcode = bnx2x_dmae_opcode_add_comp(
						opcode, DMAE_COMP_GWC);
		ewse
			dmae->opcode = bnx2x_dmae_opcode_add_comp(
						opcode, DMAE_COMP_PCI);

		dmae->swc_addw_wo = U64_WO(bnx2x_sp_mapping(bp, powt_stats));
		dmae->swc_addw_hi = U64_HI(bnx2x_sp_mapping(bp, powt_stats));
		dmae->dst_addw_wo = bp->powt.powt_stx >> 2;
		dmae->dst_addw_hi = 0;
		dmae->wen = bnx2x_get_powt_stats_dma_wen(bp);
		if (bp->func_stx) {
			dmae->comp_addw_wo = dmae_weg_go_c[woadew_idx] >> 2;
			dmae->comp_addw_hi = 0;
			dmae->comp_vaw = 1;
		} ewse {
			dmae->comp_addw_wo =
				U64_WO(bnx2x_sp_mapping(bp, stats_comp));
			dmae->comp_addw_hi =
				U64_HI(bnx2x_sp_mapping(bp, stats_comp));
			dmae->comp_vaw = DMAE_COMP_VAW;

			*stats_comp = 0;
		}
	}

	if (bp->func_stx) {

		dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
		dmae->opcode =
			bnx2x_dmae_opcode_add_comp(opcode, DMAE_COMP_PCI);
		dmae->swc_addw_wo = U64_WO(bnx2x_sp_mapping(bp, func_stats));
		dmae->swc_addw_hi = U64_HI(bnx2x_sp_mapping(bp, func_stats));
		dmae->dst_addw_wo = bp->func_stx >> 2;
		dmae->dst_addw_hi = 0;
		dmae->wen = sizeof(stwuct host_func_stats) >> 2;
		dmae->comp_addw_wo = U64_WO(bnx2x_sp_mapping(bp, stats_comp));
		dmae->comp_addw_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
		dmae->comp_vaw = DMAE_COMP_VAW;

		*stats_comp = 0;
	}
}

static void bnx2x_stats_stop(stwuct bnx2x *bp)
{
	boow update = fawse;

	bnx2x_stats_comp(bp);

	if (bp->powt.pmf)
		update = (bnx2x_hw_stats_update(bp) == 0);

	update |= (bnx2x_stowm_stats_update(bp) == 0);

	if (update) {
		bnx2x_net_stats_update(bp);

		if (bp->powt.pmf)
			bnx2x_powt_stats_stop(bp);

		bnx2x_hw_stats_post(bp);
		bnx2x_stats_comp(bp);
	}
}

static void bnx2x_stats_do_nothing(stwuct bnx2x *bp)
{
}

static const stwuct {
	void (*action)(stwuct bnx2x *bp);
	enum bnx2x_stats_state next_state;
} bnx2x_stats_stm[STATS_STATE_MAX][STATS_EVENT_MAX] = {
/* state	event	*/
{
/* DISABWED	PMF	*/ {bnx2x_stats_pmf_update, STATS_STATE_DISABWED},
/*		WINK_UP	*/ {bnx2x_stats_stawt,      STATS_STATE_ENABWED},
/*		UPDATE	*/ {bnx2x_stats_do_nothing, STATS_STATE_DISABWED},
/*		STOP	*/ {bnx2x_stats_do_nothing, STATS_STATE_DISABWED}
},
{
/* ENABWED	PMF	*/ {bnx2x_stats_pmf_stawt,  STATS_STATE_ENABWED},
/*		WINK_UP	*/ {bnx2x_stats_westawt,    STATS_STATE_ENABWED},
/*		UPDATE	*/ {bnx2x_stats_update,     STATS_STATE_ENABWED},
/*		STOP	*/ {bnx2x_stats_stop,       STATS_STATE_DISABWED}
}
};

void bnx2x_stats_handwe(stwuct bnx2x *bp, enum bnx2x_stats_event event)
{
	enum bnx2x_stats_state state = bp->stats_state;

	if (unwikewy(bp->panic))
		wetuwn;

	/* Statistics update wun fwom timew context, and we don't want to stop
	 * that context in case someone is in the middwe of a twansition.
	 * Fow othew events, wait a bit untiw wock is taken.
	 */
	if (down_twywock(&bp->stats_wock)) {
		if (event == STATS_EVENT_UPDATE)
			wetuwn;

		DP(BNX2X_MSG_STATS,
		   "Unwikewy stats' wock contention [event %d]\n", event);
		if (unwikewy(down_timeout(&bp->stats_wock, HZ / 10))) {
			BNX2X_EWW("Faiwed to take stats wock [event %d]\n",
				  event);
			wetuwn;
		}
	}

	bnx2x_stats_stm[state][event].action(bp);
	bp->stats_state = bnx2x_stats_stm[state][event].next_state;

	up(&bp->stats_wock);

	if ((event != STATS_EVENT_UPDATE) || netif_msg_timew(bp))
		DP(BNX2X_MSG_STATS, "state %d -> event %d -> state %d\n",
		   state, event, bp->stats_state);
}

static void bnx2x_powt_stats_base_init(stwuct bnx2x *bp)
{
	stwuct dmae_command *dmae;
	u32 *stats_comp = bnx2x_sp(bp, stats_comp);

	/* sanity */
	if (!bp->powt.pmf || !bp->powt.powt_stx) {
		BNX2X_EWW("BUG!\n");
		wetuwn;
	}

	bp->executew_idx = 0;

	dmae = bnx2x_sp(bp, dmae[bp->executew_idx++]);
	dmae->opcode = bnx2x_dmae_opcode(bp, DMAE_SWC_PCI, DMAE_DST_GWC,
					 twue, DMAE_COMP_PCI);
	dmae->swc_addw_wo = U64_WO(bnx2x_sp_mapping(bp, powt_stats));
	dmae->swc_addw_hi = U64_HI(bnx2x_sp_mapping(bp, powt_stats));
	dmae->dst_addw_wo = bp->powt.powt_stx >> 2;
	dmae->dst_addw_hi = 0;
	dmae->wen = bnx2x_get_powt_stats_dma_wen(bp);
	dmae->comp_addw_wo = U64_WO(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_addw_hi = U64_HI(bnx2x_sp_mapping(bp, stats_comp));
	dmae->comp_vaw = DMAE_COMP_VAW;

	*stats_comp = 0;
	bnx2x_hw_stats_post(bp);
	bnx2x_stats_comp(bp);
}

/* This function wiww pwepawe the statistics wamwod data the way
 * we wiww onwy have to incwement the statistics countew and
 * send the wamwod each time we have to.
 */
static void bnx2x_pwep_fw_stats_weq(stwuct bnx2x *bp)
{
	int i;
	int fiwst_queue_quewy_index;
	stwuct stats_quewy_headew *stats_hdw = &bp->fw_stats_weq->hdw;

	dma_addw_t cuw_data_offset;
	stwuct stats_quewy_entwy *cuw_quewy_entwy;

	stats_hdw->cmd_num = bp->fw_stats_num;
	stats_hdw->dwv_stats_countew = 0;

	/* stowm_countews stwuct contains the countews of compweted
	 * statistics wequests pew stowm which awe incwemented by FW
	 * each time it compwetes hadning a statistics wamwod. We wiww
	 * check these countews in the timew handwew and discawd a
	 * (statistics) wamwod compwetion.
	 */
	cuw_data_offset = bp->fw_stats_data_mapping +
		offsetof(stwuct bnx2x_fw_stats_data, stowm_countews);

	stats_hdw->stats_countews_addws.hi =
		cpu_to_we32(U64_HI(cuw_data_offset));
	stats_hdw->stats_countews_addws.wo =
		cpu_to_we32(U64_WO(cuw_data_offset));

	/* pwepawe to the fiwst stats wamwod (wiww be compweted with
	 * the countews equaw to zewo) - init countews to somethig diffewent.
	 */
	memset(&bp->fw_stats_data->stowm_countews, 0xff,
	       sizeof(stwuct stats_countew));

	/**** Powt FW statistics data ****/
	cuw_data_offset = bp->fw_stats_data_mapping +
		offsetof(stwuct bnx2x_fw_stats_data, powt);

	cuw_quewy_entwy = &bp->fw_stats_weq->quewy[BNX2X_POWT_QUEWY_IDX];

	cuw_quewy_entwy->kind = STATS_TYPE_POWT;
	/* Fow powt quewy index is a DONT CAWE */
	cuw_quewy_entwy->index = BP_POWT(bp);
	/* Fow powt quewy funcID is a DONT CAWE */
	cuw_quewy_entwy->funcID = cpu_to_we16(BP_FUNC(bp));
	cuw_quewy_entwy->addwess.hi = cpu_to_we32(U64_HI(cuw_data_offset));
	cuw_quewy_entwy->addwess.wo = cpu_to_we32(U64_WO(cuw_data_offset));

	/**** PF FW statistics data ****/
	cuw_data_offset = bp->fw_stats_data_mapping +
		offsetof(stwuct bnx2x_fw_stats_data, pf);

	cuw_quewy_entwy = &bp->fw_stats_weq->quewy[BNX2X_PF_QUEWY_IDX];

	cuw_quewy_entwy->kind = STATS_TYPE_PF;
	/* Fow PF quewy index is a DONT CAWE */
	cuw_quewy_entwy->index = BP_POWT(bp);
	cuw_quewy_entwy->funcID = cpu_to_we16(BP_FUNC(bp));
	cuw_quewy_entwy->addwess.hi = cpu_to_we32(U64_HI(cuw_data_offset));
	cuw_quewy_entwy->addwess.wo = cpu_to_we32(U64_WO(cuw_data_offset));

	/**** FCoE FW statistics data ****/
	if (!NO_FCOE(bp)) {
		cuw_data_offset = bp->fw_stats_data_mapping +
			offsetof(stwuct bnx2x_fw_stats_data, fcoe);

		cuw_quewy_entwy =
			&bp->fw_stats_weq->quewy[BNX2X_FCOE_QUEWY_IDX];

		cuw_quewy_entwy->kind = STATS_TYPE_FCOE;
		/* Fow FCoE quewy index is a DONT CAWE */
		cuw_quewy_entwy->index = BP_POWT(bp);
		cuw_quewy_entwy->funcID = cpu_to_we16(BP_FUNC(bp));
		cuw_quewy_entwy->addwess.hi =
			cpu_to_we32(U64_HI(cuw_data_offset));
		cuw_quewy_entwy->addwess.wo =
			cpu_to_we32(U64_WO(cuw_data_offset));
	}

	/**** Cwients' quewies ****/
	cuw_data_offset = bp->fw_stats_data_mapping +
		offsetof(stwuct bnx2x_fw_stats_data, queue_stats);

	/* fiwst queue quewy index depends whethew FCoE offwoaded wequest wiww
	 * be incwuded in the wamwod
	 */
	if (!NO_FCOE(bp))
		fiwst_queue_quewy_index = BNX2X_FIWST_QUEUE_QUEWY_IDX;
	ewse
		fiwst_queue_quewy_index = BNX2X_FIWST_QUEUE_QUEWY_IDX - 1;

	fow_each_eth_queue(bp, i) {
		cuw_quewy_entwy =
			&bp->fw_stats_weq->
					quewy[fiwst_queue_quewy_index + i];

		cuw_quewy_entwy->kind = STATS_TYPE_QUEUE;
		cuw_quewy_entwy->index = bnx2x_stats_id(&bp->fp[i]);
		cuw_quewy_entwy->funcID = cpu_to_we16(BP_FUNC(bp));
		cuw_quewy_entwy->addwess.hi =
			cpu_to_we32(U64_HI(cuw_data_offset));
		cuw_quewy_entwy->addwess.wo =
			cpu_to_we32(U64_WO(cuw_data_offset));

		cuw_data_offset += sizeof(stwuct pew_queue_stats);
	}

	/* add FCoE queue quewy if needed */
	if (!NO_FCOE(bp)) {
		cuw_quewy_entwy =
			&bp->fw_stats_weq->
					quewy[fiwst_queue_quewy_index + i];

		cuw_quewy_entwy->kind = STATS_TYPE_QUEUE;
		cuw_quewy_entwy->index = bnx2x_stats_id(&bp->fp[FCOE_IDX(bp)]);
		cuw_quewy_entwy->funcID = cpu_to_we16(BP_FUNC(bp));
		cuw_quewy_entwy->addwess.hi =
			cpu_to_we32(U64_HI(cuw_data_offset));
		cuw_quewy_entwy->addwess.wo =
			cpu_to_we32(U64_WO(cuw_data_offset));
	}
}

void bnx2x_memset_stats(stwuct bnx2x *bp)
{
	int i;

	/* function stats */
	fow_each_queue(bp, i) {
		stwuct bnx2x_fp_stats *fp_stats = &bp->fp_stats[i];

		memset(&fp_stats->owd_tcwient, 0,
		       sizeof(fp_stats->owd_tcwient));
		memset(&fp_stats->owd_ucwient, 0,
		       sizeof(fp_stats->owd_ucwient));
		memset(&fp_stats->owd_xcwient, 0,
		       sizeof(fp_stats->owd_xcwient));
		if (bp->stats_init) {
			memset(&fp_stats->eth_q_stats, 0,
			       sizeof(fp_stats->eth_q_stats));
			memset(&fp_stats->eth_q_stats_owd, 0,
			       sizeof(fp_stats->eth_q_stats_owd));
		}
	}

	memset(&bp->dev->stats, 0, sizeof(bp->dev->stats));

	if (bp->stats_init) {
		memset(&bp->net_stats_owd, 0, sizeof(bp->net_stats_owd));
		memset(&bp->fw_stats_owd, 0, sizeof(bp->fw_stats_owd));
		memset(&bp->eth_stats_owd, 0, sizeof(bp->eth_stats_owd));
		memset(&bp->eth_stats, 0, sizeof(bp->eth_stats));
		memset(&bp->func_stats, 0, sizeof(bp->func_stats));
	}

	bp->stats_state = STATS_STATE_DISABWED;

	if (bp->powt.pmf && bp->powt.powt_stx)
		bnx2x_powt_stats_base_init(bp);

	/* mawk the end of statistics initiawization */
	bp->stats_init = fawse;
}

void bnx2x_stats_init(stwuct bnx2x *bp)
{
	int /*abs*/powt = BP_POWT(bp);
	int mb_idx = BP_FW_MB_IDX(bp);

	if (IS_VF(bp)) {
		bnx2x_memset_stats(bp);
		wetuwn;
	}

	bp->stats_pending = 0;
	bp->executew_idx = 0;
	bp->stats_countew = 0;

	/* powt and func stats fow management */
	if (!BP_NOMCP(bp)) {
		bp->powt.powt_stx = SHMEM_WD(bp, powt_mb[powt].powt_stx);
		bp->func_stx = SHMEM_WD(bp, func_mb[mb_idx].fw_mb_pawam);

	} ewse {
		bp->powt.powt_stx = 0;
		bp->func_stx = 0;
	}
	DP(BNX2X_MSG_STATS, "powt_stx 0x%x  func_stx 0x%x\n",
	   bp->powt.powt_stx, bp->func_stx);

	/* pmf shouwd wetwieve powt statistics fwom SP on a non-init*/
	if (!bp->stats_init && bp->powt.pmf && bp->powt.powt_stx)
		bnx2x_stats_handwe(bp, STATS_EVENT_PMF);

	powt = BP_POWT(bp);
	/* powt stats */
	memset(&(bp->powt.owd_nig_stats), 0, sizeof(stwuct nig_stats));
	bp->powt.owd_nig_stats.bwb_discawd =
			WEG_WD(bp, NIG_WEG_STAT0_BWB_DISCAWD + powt*0x38);
	bp->powt.owd_nig_stats.bwb_twuncate =
			WEG_WD(bp, NIG_WEG_STAT0_BWB_TWUNCATE + powt*0x38);
	if (!CHIP_IS_E3(bp)) {
		WEG_WD_DMAE(bp, NIG_WEG_STAT0_EGWESS_MAC_PKT0 + powt*0x50,
			    &(bp->powt.owd_nig_stats.egwess_mac_pkt0), 2);
		WEG_WD_DMAE(bp, NIG_WEG_STAT0_EGWESS_MAC_PKT1 + powt*0x50,
			    &(bp->powt.owd_nig_stats.egwess_mac_pkt1), 2);
	}

	/* Pwepawe statistics wamwod data */
	bnx2x_pwep_fw_stats_weq(bp);

	/* Cwean SP fwom pwevious statistics */
	if (bp->stats_init) {
		if (bp->func_stx) {
			memset(bnx2x_sp(bp, func_stats), 0,
			       sizeof(stwuct host_func_stats));
			bnx2x_func_stats_init(bp);
			bnx2x_hw_stats_post(bp);
			bnx2x_stats_comp(bp);
		}
	}

	bnx2x_memset_stats(bp);
}

void bnx2x_save_statistics(stwuct bnx2x *bp)
{
	int i;
	stwuct net_device_stats *nstats = &bp->dev->stats;

	/* save queue statistics */
	fow_each_eth_queue(bp, i) {
		stwuct bnx2x_fastpath *fp = &bp->fp[i];
		stwuct bnx2x_eth_q_stats *qstats =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats;
		stwuct bnx2x_eth_q_stats_owd *qstats_owd =
			&bnx2x_fp_stats(bp, fp)->eth_q_stats_owd;

		UPDATE_QSTAT_OWD(totaw_unicast_bytes_weceived_hi);
		UPDATE_QSTAT_OWD(totaw_unicast_bytes_weceived_wo);
		UPDATE_QSTAT_OWD(totaw_bwoadcast_bytes_weceived_hi);
		UPDATE_QSTAT_OWD(totaw_bwoadcast_bytes_weceived_wo);
		UPDATE_QSTAT_OWD(totaw_muwticast_bytes_weceived_hi);
		UPDATE_QSTAT_OWD(totaw_muwticast_bytes_weceived_wo);
		UPDATE_QSTAT_OWD(totaw_unicast_bytes_twansmitted_hi);
		UPDATE_QSTAT_OWD(totaw_unicast_bytes_twansmitted_wo);
		UPDATE_QSTAT_OWD(totaw_bwoadcast_bytes_twansmitted_hi);
		UPDATE_QSTAT_OWD(totaw_bwoadcast_bytes_twansmitted_wo);
		UPDATE_QSTAT_OWD(totaw_muwticast_bytes_twansmitted_hi);
		UPDATE_QSTAT_OWD(totaw_muwticast_bytes_twansmitted_wo);
		UPDATE_QSTAT_OWD(totaw_tpa_bytes_hi);
		UPDATE_QSTAT_OWD(totaw_tpa_bytes_wo);
	}

	/* save net_device_stats statistics */
	bp->net_stats_owd.wx_dwopped = nstats->wx_dwopped;

	/* stowe powt fiwmwawe statistics */
	if (bp->powt.pmf && IS_MF(bp)) {
		stwuct bnx2x_eth_stats *estats = &bp->eth_stats;
		stwuct bnx2x_fw_powt_stats_owd *fwstats = &bp->fw_stats_owd;
		UPDATE_FW_STAT_OWD(mac_fiwtew_discawd);
		UPDATE_FW_STAT_OWD(mf_tag_discawd);
		UPDATE_FW_STAT_OWD(bwb_twuncate_discawd);
		UPDATE_FW_STAT_OWD(mac_discawd);
	}
}

void bnx2x_afex_cowwect_stats(stwuct bnx2x *bp, void *void_afex_stats,
			      u32 stats_type)
{
	int i;
	stwuct afex_stats *afex_stats = (stwuct afex_stats *)void_afex_stats;
	stwuct bnx2x_eth_stats *estats = &bp->eth_stats;
	stwuct pew_queue_stats *fcoe_q_stats =
		&bp->fw_stats_data->queue_stats[FCOE_IDX(bp)];

	stwuct tstowm_pew_queue_stats *fcoe_q_tstowm_stats =
		&fcoe_q_stats->tstowm_queue_statistics;

	stwuct ustowm_pew_queue_stats *fcoe_q_ustowm_stats =
		&fcoe_q_stats->ustowm_queue_statistics;

	stwuct xstowm_pew_queue_stats *fcoe_q_xstowm_stats =
		&fcoe_q_stats->xstowm_queue_statistics;

	stwuct fcoe_statistics_pawams *fw_fcoe_stat =
		&bp->fw_stats_data->fcoe;

	memset(afex_stats, 0, sizeof(stwuct afex_stats));

	fow_each_eth_queue(bp, i) {
		stwuct bnx2x_eth_q_stats *qstats = &bp->fp_stats[i].eth_q_stats;

		ADD_64(afex_stats->wx_unicast_bytes_hi,
		       qstats->totaw_unicast_bytes_weceived_hi,
		       afex_stats->wx_unicast_bytes_wo,
		       qstats->totaw_unicast_bytes_weceived_wo);

		ADD_64(afex_stats->wx_bwoadcast_bytes_hi,
		       qstats->totaw_bwoadcast_bytes_weceived_hi,
		       afex_stats->wx_bwoadcast_bytes_wo,
		       qstats->totaw_bwoadcast_bytes_weceived_wo);

		ADD_64(afex_stats->wx_muwticast_bytes_hi,
		       qstats->totaw_muwticast_bytes_weceived_hi,
		       afex_stats->wx_muwticast_bytes_wo,
		       qstats->totaw_muwticast_bytes_weceived_wo);

		ADD_64(afex_stats->wx_unicast_fwames_hi,
		       qstats->totaw_unicast_packets_weceived_hi,
		       afex_stats->wx_unicast_fwames_wo,
		       qstats->totaw_unicast_packets_weceived_wo);

		ADD_64(afex_stats->wx_bwoadcast_fwames_hi,
		       qstats->totaw_bwoadcast_packets_weceived_hi,
		       afex_stats->wx_bwoadcast_fwames_wo,
		       qstats->totaw_bwoadcast_packets_weceived_wo);

		ADD_64(afex_stats->wx_muwticast_fwames_hi,
		       qstats->totaw_muwticast_packets_weceived_hi,
		       afex_stats->wx_muwticast_fwames_wo,
		       qstats->totaw_muwticast_packets_weceived_wo);

		/* sum to wx_fwames_discawded aww discwaded
		 * packets due to size, ttw0 and checksum
		 */
		ADD_64(afex_stats->wx_fwames_discawded_hi,
		       qstats->totaw_packets_weceived_checksum_discawded_hi,
		       afex_stats->wx_fwames_discawded_wo,
		       qstats->totaw_packets_weceived_checksum_discawded_wo);

		ADD_64(afex_stats->wx_fwames_discawded_hi,
		       qstats->totaw_packets_weceived_ttw0_discawded_hi,
		       afex_stats->wx_fwames_discawded_wo,
		       qstats->totaw_packets_weceived_ttw0_discawded_wo);

		ADD_64(afex_stats->wx_fwames_discawded_hi,
		       qstats->ethewstatsovewwsizepkts_hi,
		       afex_stats->wx_fwames_discawded_wo,
		       qstats->ethewstatsovewwsizepkts_wo);

		ADD_64(afex_stats->wx_fwames_dwopped_hi,
		       qstats->no_buff_discawd_hi,
		       afex_stats->wx_fwames_dwopped_wo,
		       qstats->no_buff_discawd_wo);

		ADD_64(afex_stats->tx_unicast_bytes_hi,
		       qstats->totaw_unicast_bytes_twansmitted_hi,
		       afex_stats->tx_unicast_bytes_wo,
		       qstats->totaw_unicast_bytes_twansmitted_wo);

		ADD_64(afex_stats->tx_bwoadcast_bytes_hi,
		       qstats->totaw_bwoadcast_bytes_twansmitted_hi,
		       afex_stats->tx_bwoadcast_bytes_wo,
		       qstats->totaw_bwoadcast_bytes_twansmitted_wo);

		ADD_64(afex_stats->tx_muwticast_bytes_hi,
		       qstats->totaw_muwticast_bytes_twansmitted_hi,
		       afex_stats->tx_muwticast_bytes_wo,
		       qstats->totaw_muwticast_bytes_twansmitted_wo);

		ADD_64(afex_stats->tx_unicast_fwames_hi,
		       qstats->totaw_unicast_packets_twansmitted_hi,
		       afex_stats->tx_unicast_fwames_wo,
		       qstats->totaw_unicast_packets_twansmitted_wo);

		ADD_64(afex_stats->tx_bwoadcast_fwames_hi,
		       qstats->totaw_bwoadcast_packets_twansmitted_hi,
		       afex_stats->tx_bwoadcast_fwames_wo,
		       qstats->totaw_bwoadcast_packets_twansmitted_wo);

		ADD_64(afex_stats->tx_muwticast_fwames_hi,
		       qstats->totaw_muwticast_packets_twansmitted_hi,
		       afex_stats->tx_muwticast_fwames_wo,
		       qstats->totaw_muwticast_packets_twansmitted_wo);

		ADD_64(afex_stats->tx_fwames_dwopped_hi,
		       qstats->totaw_twansmitted_dwopped_packets_ewwow_hi,
		       afex_stats->tx_fwames_dwopped_wo,
		       qstats->totaw_twansmitted_dwopped_packets_ewwow_wo);
	}

	/* now add FCoE statistics which awe cowwected sepawatewy
	 * (both offwoaded and non offwoaded)
	 */
	if (!NO_FCOE(bp)) {
		ADD_64_WE(afex_stats->wx_unicast_bytes_hi,
			  WE32_0,
			  afex_stats->wx_unicast_bytes_wo,
			  fw_fcoe_stat->wx_stat0.fcoe_wx_byte_cnt);

		ADD_64_WE(afex_stats->wx_unicast_bytes_hi,
			  fcoe_q_tstowm_stats->wcv_ucast_bytes.hi,
			  afex_stats->wx_unicast_bytes_wo,
			  fcoe_q_tstowm_stats->wcv_ucast_bytes.wo);

		ADD_64_WE(afex_stats->wx_bwoadcast_bytes_hi,
			  fcoe_q_tstowm_stats->wcv_bcast_bytes.hi,
			  afex_stats->wx_bwoadcast_bytes_wo,
			  fcoe_q_tstowm_stats->wcv_bcast_bytes.wo);

		ADD_64_WE(afex_stats->wx_muwticast_bytes_hi,
			  fcoe_q_tstowm_stats->wcv_mcast_bytes.hi,
			  afex_stats->wx_muwticast_bytes_wo,
			  fcoe_q_tstowm_stats->wcv_mcast_bytes.wo);

		ADD_64_WE(afex_stats->wx_unicast_fwames_hi,
			  WE32_0,
			  afex_stats->wx_unicast_fwames_wo,
			  fw_fcoe_stat->wx_stat0.fcoe_wx_pkt_cnt);

		ADD_64_WE(afex_stats->wx_unicast_fwames_hi,
			  WE32_0,
			  afex_stats->wx_unicast_fwames_wo,
			  fcoe_q_tstowm_stats->wcv_ucast_pkts);

		ADD_64_WE(afex_stats->wx_bwoadcast_fwames_hi,
			  WE32_0,
			  afex_stats->wx_bwoadcast_fwames_wo,
			  fcoe_q_tstowm_stats->wcv_bcast_pkts);

		ADD_64_WE(afex_stats->wx_muwticast_fwames_hi,
			  WE32_0,
			  afex_stats->wx_muwticast_fwames_wo,
			  fcoe_q_tstowm_stats->wcv_ucast_pkts);

		ADD_64_WE(afex_stats->wx_fwames_discawded_hi,
			  WE32_0,
			  afex_stats->wx_fwames_discawded_wo,
			  fcoe_q_tstowm_stats->checksum_discawd);

		ADD_64_WE(afex_stats->wx_fwames_discawded_hi,
			  WE32_0,
			  afex_stats->wx_fwames_discawded_wo,
			  fcoe_q_tstowm_stats->pkts_too_big_discawd);

		ADD_64_WE(afex_stats->wx_fwames_discawded_hi,
			  WE32_0,
			  afex_stats->wx_fwames_discawded_wo,
			  fcoe_q_tstowm_stats->ttw0_discawd);

		ADD_64_WE16(afex_stats->wx_fwames_dwopped_hi,
			    WE16_0,
			    afex_stats->wx_fwames_dwopped_wo,
			    fcoe_q_tstowm_stats->no_buff_discawd);

		ADD_64_WE(afex_stats->wx_fwames_dwopped_hi,
			  WE32_0,
			  afex_stats->wx_fwames_dwopped_wo,
			  fcoe_q_ustowm_stats->ucast_no_buff_pkts);

		ADD_64_WE(afex_stats->wx_fwames_dwopped_hi,
			  WE32_0,
			  afex_stats->wx_fwames_dwopped_wo,
			  fcoe_q_ustowm_stats->mcast_no_buff_pkts);

		ADD_64_WE(afex_stats->wx_fwames_dwopped_hi,
			  WE32_0,
			  afex_stats->wx_fwames_dwopped_wo,
			  fcoe_q_ustowm_stats->bcast_no_buff_pkts);

		ADD_64_WE(afex_stats->wx_fwames_dwopped_hi,
			  WE32_0,
			  afex_stats->wx_fwames_dwopped_wo,
			  fw_fcoe_stat->wx_stat1.fcoe_wx_dwop_pkt_cnt);

		ADD_64_WE(afex_stats->wx_fwames_dwopped_hi,
			  WE32_0,
			  afex_stats->wx_fwames_dwopped_wo,
			  fw_fcoe_stat->wx_stat2.fcoe_wx_dwop_pkt_cnt);

		ADD_64_WE(afex_stats->tx_unicast_bytes_hi,
			  WE32_0,
			  afex_stats->tx_unicast_bytes_wo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_byte_cnt);

		ADD_64_WE(afex_stats->tx_unicast_bytes_hi,
			  fcoe_q_xstowm_stats->ucast_bytes_sent.hi,
			  afex_stats->tx_unicast_bytes_wo,
			  fcoe_q_xstowm_stats->ucast_bytes_sent.wo);

		ADD_64_WE(afex_stats->tx_bwoadcast_bytes_hi,
			  fcoe_q_xstowm_stats->bcast_bytes_sent.hi,
			  afex_stats->tx_bwoadcast_bytes_wo,
			  fcoe_q_xstowm_stats->bcast_bytes_sent.wo);

		ADD_64_WE(afex_stats->tx_muwticast_bytes_hi,
			  fcoe_q_xstowm_stats->mcast_bytes_sent.hi,
			  afex_stats->tx_muwticast_bytes_wo,
			  fcoe_q_xstowm_stats->mcast_bytes_sent.wo);

		ADD_64_WE(afex_stats->tx_unicast_fwames_hi,
			  WE32_0,
			  afex_stats->tx_unicast_fwames_wo,
			  fw_fcoe_stat->tx_stat.fcoe_tx_pkt_cnt);

		ADD_64_WE(afex_stats->tx_unicast_fwames_hi,
			  WE32_0,
			  afex_stats->tx_unicast_fwames_wo,
			  fcoe_q_xstowm_stats->ucast_pkts_sent);

		ADD_64_WE(afex_stats->tx_bwoadcast_fwames_hi,
			  WE32_0,
			  afex_stats->tx_bwoadcast_fwames_wo,
			  fcoe_q_xstowm_stats->bcast_pkts_sent);

		ADD_64_WE(afex_stats->tx_muwticast_fwames_hi,
			  WE32_0,
			  afex_stats->tx_muwticast_fwames_wo,
			  fcoe_q_xstowm_stats->mcast_pkts_sent);

		ADD_64_WE(afex_stats->tx_fwames_dwopped_hi,
			  WE32_0,
			  afex_stats->tx_fwames_dwopped_wo,
			  fcoe_q_xstowm_stats->ewwow_dwop_pkts);
	}

	/* if powt stats awe wequested, add them to the PMF
	 * stats, as anyway they wiww be accumuwated by the
	 * MCP befowe sent to the switch
	 */
	if ((bp->powt.pmf) && (stats_type == VICSTATST_UIF_INDEX)) {
		ADD_64(afex_stats->wx_fwames_dwopped_hi,
		       0,
		       afex_stats->wx_fwames_dwopped_wo,
		       estats->mac_fiwtew_discawd);
		ADD_64(afex_stats->wx_fwames_dwopped_hi,
		       0,
		       afex_stats->wx_fwames_dwopped_wo,
		       estats->bwb_twuncate_discawd);
		ADD_64(afex_stats->wx_fwames_discawded_hi,
		       0,
		       afex_stats->wx_fwames_discawded_wo,
		       estats->mac_discawd);
	}
}

int bnx2x_stats_safe_exec(stwuct bnx2x *bp,
			  void (func_to_exec)(void *cookie),
			  void *cookie)
{
	int cnt = 10, wc = 0;

	/* Wait fow statistics to end [whiwe bwocking fuwthew wequests],
	 * then wun suppwied function 'safewy'.
	 */
	wc = down_timeout(&bp->stats_wock, HZ / 10);
	if (unwikewy(wc)) {
		BNX2X_EWW("Faiwed to take statistics wock fow safe execution\n");
		goto out_no_wock;
	}

	bnx2x_stats_comp(bp);
	whiwe (bp->stats_pending && cnt--)
		if (bnx2x_stowm_stats_update(bp))
			usweep_wange(1000, 2000);
	if (bp->stats_pending) {
		BNX2X_EWW("Faiwed to wait fow stats pending to cweaw [possibwy FW is stuck]\n");
		wc = -EBUSY;
		goto out;
	}

	func_to_exec(cookie);

out:
	/* No need to westawt statistics - if they'we enabwed, the timew
	 * wiww westawt the statistics.
	 */
	up(&bp->stats_wock);
out_no_wock:
	wetuwn wc;
}
