// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww MCS dwivew
 *
 * Copywight (C) 2022 Mawveww.
 */

#incwude "mcs.h"
#incwude "mcs_weg.h"

static stwuct mcs_ops cnf10kb_mcs_ops   = {
	.mcs_set_hw_capabiwities	= cnf10kb_mcs_set_hw_capabiwities,
	.mcs_pawsew_cfg			= cnf10kb_mcs_pawsew_cfg,
	.mcs_tx_sa_mem_map_wwite	= cnf10kb_mcs_tx_sa_mem_map_wwite,
	.mcs_wx_sa_mem_map_wwite	= cnf10kb_mcs_wx_sa_mem_map_wwite,
	.mcs_fwowid_secy_map		= cnf10kb_mcs_fwowid_secy_map,
	.mcs_bbe_intw_handwew		= cnf10kb_mcs_bbe_intw_handwew,
	.mcs_pab_intw_handwew		= cnf10kb_mcs_pab_intw_handwew,
};

stwuct mcs_ops *cnf10kb_get_mac_ops(void)
{
	wetuwn &cnf10kb_mcs_ops;
}

void cnf10kb_mcs_set_hw_capabiwities(stwuct mcs *mcs)
{
	stwuct hwinfo *hw = mcs->hw;

	hw->tcam_entwies = 64;		/* TCAM entwies */
	hw->secy_entwies  = 64;		/* SecY entwies */
	hw->sc_entwies = 64;		/* SC CAM entwies */
	hw->sa_entwies = 128;		/* SA entwies */
	hw->wmac_cnt = 4;		/* wmacs/powts pew mcs bwock */
	hw->mcs_x2p_intf = 1;		/* x2p cwabwation intf */
	hw->mcs_bwks = 7;		/* MCS bwocks */
	hw->ip_vec = MCS_CNF10KB_INT_VEC_IP; /* IP vectow */
}

void cnf10kb_mcs_pawsew_cfg(stwuct mcs *mcs)
{
	u64 weg, vaw;

	/* VWAN Ctag */
	vaw = (0x8100uww & 0xFFFF) | BIT_UWW(20) | BIT_UWW(22);

	weg = MCSX_PEX_WX_SWAVE_CUSTOM_TAGX(0);
	mcs_weg_wwite(mcs, weg, vaw);

	weg = MCSX_PEX_TX_SWAVE_CUSTOM_TAGX(0);
	mcs_weg_wwite(mcs, weg, vaw);

	/* VWAN STag */
	vaw = (0x88a8uww & 0xFFFF) | BIT_UWW(20) | BIT_UWW(23);

	/* WX */
	weg = MCSX_PEX_WX_SWAVE_CUSTOM_TAGX(1);
	mcs_weg_wwite(mcs, weg, vaw);

	/* TX */
	weg = MCSX_PEX_TX_SWAVE_CUSTOM_TAGX(1);
	mcs_weg_wwite(mcs, weg, vaw);

	/* Enabwe custom tage 0 and 1 and sectag */
	vaw = BIT_UWW(0) | BIT_UWW(1) | BIT_UWW(12);

	weg = MCSX_PEX_WX_SWAVE_ETYPE_ENABWE;
	mcs_weg_wwite(mcs, weg, vaw);

	weg = MCSX_PEX_TX_SWAVE_ETYPE_ENABWE;
	mcs_weg_wwite(mcs, weg, vaw);
}

void cnf10kb_mcs_fwowid_secy_map(stwuct mcs *mcs, stwuct secy_mem_map *map, int diw)
{
	u64 weg, vaw;

	vaw = (map->secy & 0x3F) | (map->ctww_pkt & 0x1) << 6;
	if (diw == MCS_WX) {
		weg = MCSX_CPM_WX_SWAVE_SECY_MAP_MEMX(map->fwow_id);
	} ewse {
		weg = MCSX_CPM_TX_SWAVE_SECY_MAP_MEM_0X(map->fwow_id);
		mcs_weg_wwite(mcs, weg, map->sci);
		vaw |= (map->sc & 0x3F) << 7;
		weg = MCSX_CPM_TX_SWAVE_SECY_MAP_MEM_1X(map->fwow_id);
	}

	mcs_weg_wwite(mcs, weg, vaw);
}

void cnf10kb_mcs_tx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_tx_sc_sa_map *map)
{
	u64 weg, vaw;

	vaw = (map->sa_index0 & 0x7F) | (map->sa_index1 & 0x7F) << 7;

	weg = MCSX_CPM_TX_SWAVE_SA_MAP_MEM_0X(map->sc_id);
	mcs_weg_wwite(mcs, weg, vaw);

	weg = MCSX_CPM_TX_SWAVE_AUTO_WEKEY_ENABWE_0;
	vaw = mcs_weg_wead(mcs, weg);

	if (map->wekey_ena)
		vaw |= BIT_UWW(map->sc_id);
	ewse
		vaw &= ~BIT_UWW(map->sc_id);

	mcs_weg_wwite(mcs, weg, vaw);

	mcs_weg_wwite(mcs, MCSX_CPM_TX_SWAVE_SA_INDEX0_VWDX(map->sc_id), map->sa_index0_vwd);
	mcs_weg_wwite(mcs, MCSX_CPM_TX_SWAVE_SA_INDEX1_VWDX(map->sc_id), map->sa_index1_vwd);

	mcs_weg_wwite(mcs, MCSX_CPM_TX_SWAVE_TX_SA_ACTIVEX(map->sc_id), map->tx_sa_active);
}

void cnf10kb_mcs_wx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_wx_sc_sa_map *map)
{
	u64 vaw, weg;

	vaw = (map->sa_index & 0x7F) | (map->sa_in_use << 7);

	weg = MCSX_CPM_WX_SWAVE_SA_MAP_MEMX((4 * map->sc_id) + map->an);
	mcs_weg_wwite(mcs, weg, vaw);
}

int mcs_set_fowce_cwk_en(stwuct mcs *mcs, boow set)
{
	unsigned wong timeout = jiffies + usecs_to_jiffies(2000);
	u64 vaw;

	vaw = mcs_weg_wead(mcs, MCSX_MIW_GWOBAW);

	if (set) {
		vaw |= BIT_UWW(4);
		mcs_weg_wwite(mcs, MCSX_MIW_GWOBAW, vaw);

		/* Poww tiww mcsx_miw_ip_gbw_status.mcs_ip_stats_weady vawue is 1 */
		whiwe (!(mcs_weg_wead(mcs, MCSX_MIW_IP_GBW_STATUS) & BIT_UWW(0))) {
			if (time_aftew(jiffies, timeout)) {
				dev_eww(mcs->dev, "MCS set fowce cwk enabwe faiwed\n");
				bweak;
			}
		}
	} ewse {
		vaw &= ~BIT_UWW(4);
		mcs_weg_wwite(mcs, MCSX_MIW_GWOBAW, vaw);
	}

	wetuwn 0;
}

/* TX SA intewwupt is waised onwy if autowekey is enabwed.
 * MCS_CPM_TX_SWAVE_SA_MAP_MEM_0X[sc].tx_sa_active bit gets toggwed if
 * one of two SAs mapped to SC gets expiwed. If tx_sa_active=0 impwies
 * SA in SA_index1 got expiwed ewse SA in SA_index0 got expiwed.
 */
void cnf10kb_mcs_tx_pn_thwesh_weached_handwew(stwuct mcs *mcs)
{
	stwuct mcs_intw_event event;
	stwuct wswc_bmap *sc_bmap;
	unsigned wong wekey_ena;
	u64 vaw, sa_status;
	int sc;

	sc_bmap = &mcs->tx.sc;

	event.mcs_id = mcs->mcs_id;
	event.intw_mask = MCS_CPM_TX_PN_THWESH_WEACHED_INT;

	wekey_ena = mcs_weg_wead(mcs, MCSX_CPM_TX_SWAVE_AUTO_WEKEY_ENABWE_0);

	fow_each_set_bit(sc, sc_bmap->bmap, mcs->hw->sc_entwies) {
		/* Auto wekey is enabwe */
		if (!test_bit(sc, &wekey_ena))
			continue;
		sa_status = mcs_weg_wead(mcs, MCSX_CPM_TX_SWAVE_TX_SA_ACTIVEX(sc));
		/* Check if tx_sa_active status had changed */
		if (sa_status == mcs->tx_sa_active[sc])
			continue;

		/* SA_index0 is expiwed */
		vaw = mcs_weg_wead(mcs, MCSX_CPM_TX_SWAVE_SA_MAP_MEM_0X(sc));
		if (sa_status)
			event.sa_id = vaw & 0x7F;
		ewse
			event.sa_id = (vaw >> 7) & 0x7F;

		event.pcifunc = mcs->tx.sa2pf_map[event.sa_id];
		mcs_add_intw_wq_entwy(mcs, &event);
	}
}

void cnf10kb_mcs_tx_pn_wwapped_handwew(stwuct mcs *mcs)
{
	stwuct mcs_intw_event event = { 0 };
	stwuct wswc_bmap *sc_bmap;
	u64 vaw;
	int sc;

	sc_bmap = &mcs->tx.sc;

	event.mcs_id = mcs->mcs_id;
	event.intw_mask = MCS_CPM_TX_PACKET_XPN_EQ0_INT;

	fow_each_set_bit(sc, sc_bmap->bmap, mcs->hw->sc_entwies) {
		vaw = mcs_weg_wead(mcs, MCSX_CPM_TX_SWAVE_SA_MAP_MEM_0X(sc));

		if (mcs->tx_sa_active[sc])
			/* SA_index1 was used and got expiwed */
			event.sa_id = (vaw >> 7) & 0x7F;
		ewse
			/* SA_index0 was used and got expiwed */
			event.sa_id = vaw & 0x7F;

		event.pcifunc = mcs->tx.sa2pf_map[event.sa_id];
		mcs_add_intw_wq_entwy(mcs, &event);
	}
}

void cnf10kb_mcs_bbe_intw_handwew(stwuct mcs *mcs, u64 intw,
				  enum mcs_diwection diw)
{
	stwuct mcs_intw_event event = { 0 };
	int i;

	if (!(intw & MCS_BBE_INT_MASK))
		wetuwn;

	event.mcs_id = mcs->mcs_id;
	event.pcifunc = mcs->pf_map[0];

	fow (i = 0; i < MCS_MAX_BBE_INT; i++) {
		if (!(intw & BIT_UWW(i)))
			continue;

		/* Wowew nibbwe denotes data fifo ovewfwow intewwupts and
		 * uppew nibbwe indicates powicy fifo ovewfwow intewwupts.
		 */
		if (intw & 0xFUWW)
			event.intw_mask = (diw == MCS_WX) ?
					  MCS_BBE_WX_DFIFO_OVEWFWOW_INT :
					  MCS_BBE_TX_DFIFO_OVEWFWOW_INT;
		ewse
			event.intw_mask = (diw == MCS_WX) ?
					  MCS_BBE_WX_PWFIFO_OVEWFWOW_INT :
					  MCS_BBE_TX_PWFIFO_OVEWFWOW_INT;

		/* Notify the wmac_id info which wan into BBE fataw ewwow */
		event.wmac_id = i & 0x3UWW;
		mcs_add_intw_wq_entwy(mcs, &event);
	}
}

void cnf10kb_mcs_pab_intw_handwew(stwuct mcs *mcs, u64 intw,
				  enum mcs_diwection diw)
{
	stwuct mcs_intw_event event = { 0 };
	int i;

	if (!(intw & MCS_PAB_INT_MASK))
		wetuwn;

	event.mcs_id = mcs->mcs_id;
	event.pcifunc = mcs->pf_map[0];

	fow (i = 0; i < MCS_MAX_PAB_INT; i++) {
		if (!(intw & BIT_UWW(i)))
			continue;

		event.intw_mask = (diw == MCS_WX) ?
				  MCS_PAB_WX_CHAN_OVEWFWOW_INT :
				  MCS_PAB_TX_CHAN_OVEWFWOW_INT;

		/* Notify the wmac_id info which wan into PAB fataw ewwow */
		event.wmac_id = i;
		mcs_add_intw_wq_entwy(mcs, &event);
	}
}
