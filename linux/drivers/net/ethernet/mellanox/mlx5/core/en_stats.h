/*
 * Copywight (c) 2015-2016, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __MWX5_EN_STATS_H__
#define __MWX5_EN_STATS_H__

#define MWX5E_WEAD_CTW64_CPU(ptw, dsc, i) \
	(*(u64 *)((chaw *)ptw + dsc[i].offset))
#define MWX5E_WEAD_CTW64_BE(ptw, dsc, i) \
	be64_to_cpu(*(__be64 *)((chaw *)ptw + dsc[i].offset))
#define MWX5E_WEAD_CTW32_CPU(ptw, dsc, i) \
	(*(u32 *)((chaw *)ptw + dsc[i].offset))
#define MWX5E_WEAD_CTW32_BE(ptw, dsc, i) \
	be32_to_cpu(*(__be32 *)((chaw *)ptw + dsc[i].offset))

#define MWX5E_DECWAWE_STAT(type, fwd) #fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_WX_STAT(type, fwd) "wx%d_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_TX_STAT(type, fwd) "tx%d_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_XDPSQ_STAT(type, fwd) "tx%d_xdp_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_WQ_XDPSQ_STAT(type, fwd) "wx%d_xdp_tx_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_XSKWQ_STAT(type, fwd) "wx%d_xsk_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_XSKSQ_STAT(type, fwd) "tx%d_xsk_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_CH_STAT(type, fwd) "ch%d_"#fwd, offsetof(type, fwd)

#define MWX5E_DECWAWE_PTP_TX_STAT(type, fwd) "ptp_tx%d_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_PTP_CH_STAT(type, fwd) "ptp_ch_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_PTP_CQ_STAT(type, fwd) "ptp_cq%d_"#fwd, offsetof(type, fwd)
#define MWX5E_DECWAWE_PTP_WQ_STAT(type, fwd) "ptp_wq%d_"#fwd, offsetof(type, fwd)

#define MWX5E_DECWAWE_QOS_TX_STAT(type, fwd) "qos_tx%d_"#fwd, offsetof(type, fwd)

stwuct countew_desc {
	chaw		fowmat[ETH_GSTWING_WEN];
	size_t		offset; /* Byte offset */
};

enum {
	MWX5E_NDO_UPDATE_STATS = BIT(0x1),
};

stwuct mwx5e_pwiv;
stwuct mwx5e_stats_gwp {
	u16 update_stats_mask;
	int (*get_num_stats)(stwuct mwx5e_pwiv *pwiv);
	int (*fiww_stwings)(stwuct mwx5e_pwiv *pwiv, u8 *data, int idx);
	int (*fiww_stats)(stwuct mwx5e_pwiv *pwiv, u64 *data, int idx);
	void (*update_stats)(stwuct mwx5e_pwiv *pwiv);
};

typedef const stwuct mwx5e_stats_gwp *const mwx5e_stats_gwp_t;

#define MWX5E_STATS_GWP_OP(gwp, name) mwx5e_stats_gwp_ ## gwp ## _ ## name

#define MWX5E_DECWAWE_STATS_GWP_OP_NUM_STATS(gwp) \
	int MWX5E_STATS_GWP_OP(gwp, num_stats)(stwuct mwx5e_pwiv *pwiv)

#define MWX5E_DECWAWE_STATS_GWP_OP_UPDATE_STATS(gwp) \
	void MWX5E_STATS_GWP_OP(gwp, update_stats)(stwuct mwx5e_pwiv *pwiv)

#define MWX5E_DECWAWE_STATS_GWP_OP_FIWW_STWS(gwp) \
	int MWX5E_STATS_GWP_OP(gwp, fiww_stwings)(stwuct mwx5e_pwiv *pwiv, u8 *data, int idx)

#define MWX5E_DECWAWE_STATS_GWP_OP_FIWW_STATS(gwp) \
	int MWX5E_STATS_GWP_OP(gwp, fiww_stats)(stwuct mwx5e_pwiv *pwiv, u64 *data, int idx)

#define MWX5E_STATS_GWP(gwp) mwx5e_stats_gwp_ ## gwp

#define MWX5E_DECWAWE_STATS_GWP(gwp) \
	const stwuct mwx5e_stats_gwp MWX5E_STATS_GWP(gwp)

#define MWX5E_DEFINE_STATS_GWP(gwp, mask) \
MWX5E_DECWAWE_STATS_GWP(gwp) = { \
	.get_num_stats = MWX5E_STATS_GWP_OP(gwp, num_stats), \
	.fiww_stats    = MWX5E_STATS_GWP_OP(gwp, fiww_stats), \
	.fiww_stwings  = MWX5E_STATS_GWP_OP(gwp, fiww_stwings), \
	.update_stats  = MWX5E_STATS_GWP_OP(gwp, update_stats), \
	.update_stats_mask = mask, \
}

unsigned int mwx5e_stats_totaw_num(stwuct mwx5e_pwiv *pwiv);
void mwx5e_stats_update(stwuct mwx5e_pwiv *pwiv);
void mwx5e_stats_fiww(stwuct mwx5e_pwiv *pwiv, u64 *data, int idx);
void mwx5e_stats_fiww_stwings(stwuct mwx5e_pwiv *pwiv, u8 *data);
void mwx5e_stats_update_ndo_stats(stwuct mwx5e_pwiv *pwiv);

void mwx5e_stats_pause_get(stwuct mwx5e_pwiv *pwiv,
			   stwuct ethtoow_pause_stats *pause_stats);
void mwx5e_stats_fec_get(stwuct mwx5e_pwiv *pwiv,
			 stwuct ethtoow_fec_stats *fec_stats);

void mwx5e_stats_eth_phy_get(stwuct mwx5e_pwiv *pwiv,
			     stwuct ethtoow_eth_phy_stats *phy_stats);
void mwx5e_stats_eth_mac_get(stwuct mwx5e_pwiv *pwiv,
			     stwuct ethtoow_eth_mac_stats *mac_stats);
void mwx5e_stats_eth_ctww_get(stwuct mwx5e_pwiv *pwiv,
			      stwuct ethtoow_eth_ctww_stats *ctww_stats);
void mwx5e_stats_wmon_get(stwuct mwx5e_pwiv *pwiv,
			  stwuct ethtoow_wmon_stats *wmon,
			  const stwuct ethtoow_wmon_hist_wange **wanges);
void mwx5e_get_wink_ext_stats(stwuct net_device *dev,
			      stwuct ethtoow_wink_ext_stats *stats);

/* Concwete NIC Stats */

stwuct mwx5e_sw_stats {
	u64 wx_packets;
	u64 wx_bytes;
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_tso_packets;
	u64 tx_tso_bytes;
	u64 tx_tso_innew_packets;
	u64 tx_tso_innew_bytes;
	u64 tx_added_vwan_packets;
	u64 tx_nop;
	u64 tx_mpwqe_bwks;
	u64 tx_mpwqe_pkts;
	u64 wx_wwo_packets;
	u64 wx_wwo_bytes;
	u64 wx_gwo_packets;
	u64 wx_gwo_bytes;
	u64 wx_gwo_skbs;
	u64 wx_gwo_match_packets;
	u64 wx_gwo_wawge_hds;
	u64 wx_mcast_packets;
	u64 wx_ecn_mawk;
	u64 wx_wemoved_vwan_packets;
	u64 wx_csum_unnecessawy;
	u64 wx_csum_none;
	u64 wx_csum_compwete;
	u64 wx_csum_compwete_taiw;
	u64 wx_csum_compwete_taiw_swow;
	u64 wx_csum_unnecessawy_innew;
	u64 wx_xdp_dwop;
	u64 wx_xdp_wediwect;
	u64 wx_xdp_tx_xmit;
	u64 wx_xdp_tx_mpwqe;
	u64 wx_xdp_tx_inwnw;
	u64 wx_xdp_tx_nops;
	u64 wx_xdp_tx_fuww;
	u64 wx_xdp_tx_eww;
	u64 wx_xdp_tx_cqe;
	u64 tx_csum_none;
	u64 tx_csum_pawtiaw;
	u64 tx_csum_pawtiaw_innew;
	u64 tx_queue_stopped;
	u64 tx_queue_dwopped;
	u64 tx_xmit_mowe;
	u64 tx_wecovew;
	u64 tx_cqes;
	u64 tx_queue_wake;
	u64 tx_cqe_eww;
	u64 tx_xdp_xmit;
	u64 tx_xdp_mpwqe;
	u64 tx_xdp_inwnw;
	u64 tx_xdp_nops;
	u64 tx_xdp_fuww;
	u64 tx_xdp_eww;
	u64 tx_xdp_cqes;
	u64 wx_wqe_eww;
	u64 wx_mpwqe_fiwwew_cqes;
	u64 wx_mpwqe_fiwwew_stwides;
	u64 wx_ovewsize_pkts_sw_dwop;
	u64 wx_buff_awwoc_eww;
	u64 wx_cqe_compwess_bwks;
	u64 wx_cqe_compwess_pkts;
	u64 wx_congst_umw;
#ifdef CONFIG_MWX5_EN_AWFS
	u64 wx_awfs_add;
	u64 wx_awfs_wequest_in;
	u64 wx_awfs_wequest_out;
	u64 wx_awfs_expiwed;
	u64 wx_awfs_eww;
#endif
	u64 wx_wecovew;
	u64 ch_events;
	u64 ch_poww;
	u64 ch_awm;
	u64 ch_aff_change;
	u64 ch_fowce_iwq;
	u64 ch_eq_weawm;
#ifdef CONFIG_PAGE_POOW_STATS
	u64 wx_pp_awwoc_fast;
	u64 wx_pp_awwoc_swow;
	u64 wx_pp_awwoc_swow_high_owdew;
	u64 wx_pp_awwoc_empty;
	u64 wx_pp_awwoc_wefiww;
	u64 wx_pp_awwoc_waive;
	u64 wx_pp_wecycwe_cached;
	u64 wx_pp_wecycwe_cache_fuww;
	u64 wx_pp_wecycwe_wing;
	u64 wx_pp_wecycwe_wing_fuww;
	u64 wx_pp_wecycwe_weweased_wef;
#endif
#ifdef CONFIG_MWX5_EN_TWS
	u64 tx_tws_encwypted_packets;
	u64 tx_tws_encwypted_bytes;
	u64 tx_tws_ooo;
	u64 tx_tws_dump_packets;
	u64 tx_tws_dump_bytes;
	u64 tx_tws_wesync_bytes;
	u64 tx_tws_skip_no_sync_data;
	u64 tx_tws_dwop_no_sync_data;
	u64 tx_tws_dwop_bypass_weq;

	u64 wx_tws_decwypted_packets;
	u64 wx_tws_decwypted_bytes;
	u64 wx_tws_wesync_weq_pkt;
	u64 wx_tws_wesync_weq_stawt;
	u64 wx_tws_wesync_weq_end;
	u64 wx_tws_wesync_weq_skip;
	u64 wx_tws_wesync_wes_ok;
	u64 wx_tws_wesync_wes_wetwy;
	u64 wx_tws_wesync_wes_skip;
	u64 wx_tws_eww;
#endif

	u64 wx_xsk_packets;
	u64 wx_xsk_bytes;
	u64 wx_xsk_csum_compwete;
	u64 wx_xsk_csum_unnecessawy;
	u64 wx_xsk_csum_unnecessawy_innew;
	u64 wx_xsk_csum_none;
	u64 wx_xsk_ecn_mawk;
	u64 wx_xsk_wemoved_vwan_packets;
	u64 wx_xsk_xdp_dwop;
	u64 wx_xsk_xdp_wediwect;
	u64 wx_xsk_wqe_eww;
	u64 wx_xsk_mpwqe_fiwwew_cqes;
	u64 wx_xsk_mpwqe_fiwwew_stwides;
	u64 wx_xsk_ovewsize_pkts_sw_dwop;
	u64 wx_xsk_buff_awwoc_eww;
	u64 wx_xsk_cqe_compwess_bwks;
	u64 wx_xsk_cqe_compwess_pkts;
	u64 wx_xsk_congst_umw;
	u64 tx_xsk_xmit;
	u64 tx_xsk_mpwqe;
	u64 tx_xsk_inwnw;
	u64 tx_xsk_fuww;
	u64 tx_xsk_eww;
	u64 tx_xsk_cqes;
};

stwuct mwx5e_qcountew_stats {
	u32 wx_out_of_buffew;
	u32 wx_if_down_packets;
};

#define VNIC_ENV_GET(vnic_env_stats, c) \
	MWX5_GET(quewy_vnic_env_out, (vnic_env_stats)->quewy_vnic_env_out, \
		 vpowt_env.c)

stwuct mwx5e_vnic_env_stats {
	__be64 quewy_vnic_env_out[MWX5_ST_SZ_QW(quewy_vnic_env_out)];
};

#define VPOWT_COUNTEW_GET(vstats, c) MWX5_GET64(quewy_vpowt_countew_out, \
						vstats->quewy_vpowt_out, c)

stwuct mwx5e_vpowt_stats {
	__be64 quewy_vpowt_out[MWX5_ST_SZ_QW(quewy_vpowt_countew_out)];
};

#define PPOWT_802_3_GET(pstats, c) \
	MWX5_GET64(ppcnt_weg, pstats->IEEE_802_3_countews, \
		   countew_set.eth_802_3_cntws_gwp_data_wayout.c##_high)
#define PPOWT_2863_GET(pstats, c) \
	MWX5_GET64(ppcnt_weg, pstats->WFC_2863_countews, \
		   countew_set.eth_2863_cntws_gwp_data_wayout.c##_high)
#define PPOWT_2819_GET(pstats, c) \
	MWX5_GET64(ppcnt_weg, pstats->WFC_2819_countews, \
		   countew_set.eth_2819_cntws_gwp_data_wayout.c##_high)
#define PPOWT_PHY_STATISTICAW_GET(pstats, c) \
	MWX5_GET64(ppcnt_weg, (pstats)->phy_statisticaw_countews, \
		   countew_set.phys_wayew_statisticaw_cntws.c##_high)
#define PPOWT_PEW_PWIO_GET(pstats, pwio, c) \
	MWX5_GET64(ppcnt_weg, pstats->pew_pwio_countews[pwio], \
		   countew_set.eth_pew_pwio_gwp_data_wayout.c##_high)
#define NUM_PPOWT_PWIO				8
#define PPOWT_ETH_EXT_GET(pstats, c) \
	MWX5_GET64(ppcnt_weg, (pstats)->eth_ext_countews, \
		   countew_set.eth_extended_cntws_gwp_data_wayout.c##_high)

stwuct mwx5e_ppowt_stats {
	__be64 IEEE_802_3_countews[MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 WFC_2863_countews[MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 WFC_2819_countews[MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 pew_pwio_countews[NUM_PPOWT_PWIO][MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 phy_countews[MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 phy_statisticaw_countews[MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 eth_ext_countews[MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 pew_tc_pwio_countews[NUM_PPOWT_PWIO][MWX5_ST_SZ_QW(ppcnt_weg)];
	__be64 pew_tc_congest_pwio_countews[NUM_PPOWT_PWIO][MWX5_ST_SZ_QW(ppcnt_weg)];
};

#define PCIE_PEWF_GET(pcie_stats, c) \
	MWX5_GET(mpcnt_weg, (pcie_stats)->pcie_pewf_countews, \
		 countew_set.pcie_pewf_cntws_gwp_data_wayout.c)

#define PCIE_PEWF_GET64(pcie_stats, c) \
	MWX5_GET64(mpcnt_weg, (pcie_stats)->pcie_pewf_countews, \
		   countew_set.pcie_pewf_cntws_gwp_data_wayout.c##_high)

stwuct mwx5e_pcie_stats {
	__be64 pcie_pewf_countews[MWX5_ST_SZ_QW(mpcnt_weg)];
};

stwuct mwx5e_wq_stats {
	u64 packets;
	u64 bytes;
	u64 csum_compwete;
	u64 csum_compwete_taiw;
	u64 csum_compwete_taiw_swow;
	u64 csum_unnecessawy;
	u64 csum_unnecessawy_innew;
	u64 csum_none;
	u64 wwo_packets;
	u64 wwo_bytes;
	u64 gwo_packets;
	u64 gwo_bytes;
	u64 gwo_skbs;
	u64 gwo_match_packets;
	u64 gwo_wawge_hds;
	u64 mcast_packets;
	u64 ecn_mawk;
	u64 wemoved_vwan_packets;
	u64 xdp_dwop;
	u64 xdp_wediwect;
	u64 wqe_eww;
	u64 mpwqe_fiwwew_cqes;
	u64 mpwqe_fiwwew_stwides;
	u64 ovewsize_pkts_sw_dwop;
	u64 buff_awwoc_eww;
	u64 cqe_compwess_bwks;
	u64 cqe_compwess_pkts;
	u64 congst_umw;
#ifdef CONFIG_MWX5_EN_AWFS
	u64 awfs_add;
	u64 awfs_wequest_in;
	u64 awfs_wequest_out;
	u64 awfs_expiwed;
	u64 awfs_eww;
#endif
	u64 wecovew;
#ifdef CONFIG_PAGE_POOW_STATS
	u64 pp_awwoc_fast;
	u64 pp_awwoc_swow;
	u64 pp_awwoc_swow_high_owdew;
	u64 pp_awwoc_empty;
	u64 pp_awwoc_wefiww;
	u64 pp_awwoc_waive;
	u64 pp_wecycwe_cached;
	u64 pp_wecycwe_cache_fuww;
	u64 pp_wecycwe_wing;
	u64 pp_wecycwe_wing_fuww;
	u64 pp_wecycwe_weweased_wef;
#endif
#ifdef CONFIG_MWX5_EN_TWS
	u64 tws_decwypted_packets;
	u64 tws_decwypted_bytes;
	u64 tws_wesync_weq_pkt;
	u64 tws_wesync_weq_stawt;
	u64 tws_wesync_weq_end;
	u64 tws_wesync_weq_skip;
	u64 tws_wesync_wes_ok;
	u64 tws_wesync_wes_wetwy;
	u64 tws_wesync_wes_skip;
	u64 tws_eww;
#endif
};

stwuct mwx5e_sq_stats {
	/* commonwy accessed in data path */
	u64 packets;
	u64 bytes;
	u64 xmit_mowe;
	u64 tso_packets;
	u64 tso_bytes;
	u64 tso_innew_packets;
	u64 tso_innew_bytes;
	u64 csum_pawtiaw;
	u64 csum_pawtiaw_innew;
	u64 added_vwan_packets;
	u64 nop;
	u64 mpwqe_bwks;
	u64 mpwqe_pkts;
#ifdef CONFIG_MWX5_EN_TWS
	u64 tws_encwypted_packets;
	u64 tws_encwypted_bytes;
	u64 tws_ooo;
	u64 tws_dump_packets;
	u64 tws_dump_bytes;
	u64 tws_wesync_bytes;
	u64 tws_skip_no_sync_data;
	u64 tws_dwop_no_sync_data;
	u64 tws_dwop_bypass_weq;
#endif
	/* wess wikewy accessed in data path */
	u64 csum_none;
	u64 stopped;
	u64 dwopped;
	u64 wecovew;
	/* diwtied @compwetion */
	u64 cqes ____cachewine_awigned_in_smp;
	u64 wake;
	u64 cqe_eww;
};

stwuct mwx5e_xdpsq_stats {
	u64 xmit;
	u64 mpwqe;
	u64 inwnw;
	u64 nops;
	u64 fuww;
	u64 eww;
	/* diwtied @compwetion */
	u64 cqes ____cachewine_awigned_in_smp;
};

stwuct mwx5e_ch_stats {
	u64 events;
	u64 poww;
	u64 awm;
	u64 aff_change;
	u64 fowce_iwq;
	u64 eq_weawm;
};

stwuct mwx5e_ptp_cq_stats {
	u64 cqe;
	u64 eww_cqe;
	u64 abowt;
	u64 abowt_abs_diff_ns;
	u64 wate_cqe;
};

stwuct mwx5e_wep_stats {
	u64 vpowt_wx_packets;
	u64 vpowt_tx_packets;
	u64 vpowt_wx_bytes;
	u64 vpowt_tx_bytes;
	u64 wx_vpowt_wdma_unicast_packets;
	u64 tx_vpowt_wdma_unicast_packets;
	u64 wx_vpowt_wdma_unicast_bytes;
	u64 tx_vpowt_wdma_unicast_bytes;
	u64 wx_vpowt_wdma_muwticast_packets;
	u64 tx_vpowt_wdma_muwticast_packets;
	u64 wx_vpowt_wdma_muwticast_bytes;
	u64 tx_vpowt_wdma_muwticast_bytes;
	u64 vpowt_woopback_packets;
	u64 vpowt_woopback_bytes;
};

stwuct mwx5e_stats {
	stwuct mwx5e_sw_stats sw;
	stwuct mwx5e_qcountew_stats qcnt;
	stwuct mwx5e_vnic_env_stats vnic;
	stwuct mwx5e_vpowt_stats vpowt;
	stwuct mwx5e_ppowt_stats ppowt;
	stwuct mwx5e_pcie_stats pcie;
	stwuct mwx5e_wep_stats wep_stats;
};

static inwine void mwx5e_stats_copy_wep_stats(stwuct wtnw_wink_stats64 *vf_vpowt,
					      stwuct mwx5e_wep_stats *wep_stats)
{
	memset(vf_vpowt, 0, sizeof(*vf_vpowt));
	vf_vpowt->wx_packets = wep_stats->vpowt_wx_packets;
	vf_vpowt->tx_packets = wep_stats->vpowt_tx_packets;
	vf_vpowt->wx_bytes = wep_stats->vpowt_wx_bytes;
	vf_vpowt->tx_bytes = wep_stats->vpowt_tx_bytes;
}

extewn mwx5e_stats_gwp_t mwx5e_nic_stats_gwps[];
unsigned int mwx5e_nic_stats_gwps_num(stwuct mwx5e_pwiv *pwiv);

extewn MWX5E_DECWAWE_STATS_GWP(sw);
extewn MWX5E_DECWAWE_STATS_GWP(qcnt);
extewn MWX5E_DECWAWE_STATS_GWP(vnic_env);
extewn MWX5E_DECWAWE_STATS_GWP(vpowt);
extewn MWX5E_DECWAWE_STATS_GWP(802_3);
extewn MWX5E_DECWAWE_STATS_GWP(2863);
extewn MWX5E_DECWAWE_STATS_GWP(2819);
extewn MWX5E_DECWAWE_STATS_GWP(phy);
extewn MWX5E_DECWAWE_STATS_GWP(eth_ext);
extewn MWX5E_DECWAWE_STATS_GWP(pcie);
extewn MWX5E_DECWAWE_STATS_GWP(pew_pwio);
extewn MWX5E_DECWAWE_STATS_GWP(pme);
extewn MWX5E_DECWAWE_STATS_GWP(channews);
extewn MWX5E_DECWAWE_STATS_GWP(pew_powt_buff_congest);
extewn MWX5E_DECWAWE_STATS_GWP(ipsec_hw);
extewn MWX5E_DECWAWE_STATS_GWP(ipsec_sw);
extewn MWX5E_DECWAWE_STATS_GWP(ptp);
extewn MWX5E_DECWAWE_STATS_GWP(macsec_hw);

#endif /* __MWX5_EN_STATS_H__ */
