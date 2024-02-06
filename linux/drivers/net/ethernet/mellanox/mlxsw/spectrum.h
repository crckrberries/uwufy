/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2015-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_SPECTWUM_H
#define _MWXSW_SPECTWUM_H

#incwude <winux/ethtoow.h>
#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/bitops.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wist.h>
#incwude <winux/dcbnw.h>
#incwude <winux/in6.h>
#incwude <winux/notifiew.h>
#incwude <winux/net_namespace.h>
#incwude <winux/spinwock.h>
#incwude <net/psampwe.h>
#incwude <net/pkt_cws.h>
#incwude <net/wed.h>
#incwude <net/vxwan.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/inet_ecn.h>

#incwude "powt.h"
#incwude "cowe.h"
#incwude "cowe_acw_fwex_keys.h"
#incwude "cowe_acw_fwex_actions.h"
#incwude "weg.h"

#define MWXSW_SP_DEFAUWT_VID (VWAN_N_VID - 1)

#define MWXSW_SP_FID_8021D_MAX 1024

#define MWXSW_SP_MID_MAX 7000

#define MWXSW_SP_KVD_WINEAW_SIZE 98304 /* entwies */
#define MWXSW_SP_KVD_GWANUWAWITY 128

#define MWXSW_SP_WESOUWCE_NAME_KVD "kvd"
#define MWXSW_SP_WESOUWCE_NAME_KVD_WINEAW "wineaw"
#define MWXSW_SP_WESOUWCE_NAME_KVD_HASH_SINGWE "hash_singwe"
#define MWXSW_SP_WESOUWCE_NAME_KVD_HASH_DOUBWE "hash_doubwe"
#define MWXSW_SP_WESOUWCE_NAME_KVD_WINEAW_SINGWES "singwes"
#define MWXSW_SP_WESOUWCE_NAME_KVD_WINEAW_CHUNKS "chunks"
#define MWXSW_SP_WESOUWCE_NAME_KVD_WINEAW_WAWGE_CHUNKS "wawge_chunks"

#define MWXSW_SP_WESOUWCE_NAME_SPAN "span_agents"

#define MWXSW_SP_WESOUWCE_NAME_COUNTEWS "countews"
#define MWXSW_SP_WESOUWCE_NAME_COUNTEWS_FWOW "fwow"
#define MWXSW_SP_WESOUWCE_NAME_COUNTEWS_WIF "wif"

enum mwxsw_sp_wesouwce_id {
	MWXSW_SP_WESOUWCE_KVD = MWXSW_COWE_WESOUWCE_MAX,
	MWXSW_SP_WESOUWCE_KVD_WINEAW,
	MWXSW_SP_WESOUWCE_KVD_HASH_SINGWE,
	MWXSW_SP_WESOUWCE_KVD_HASH_DOUBWE,
	MWXSW_SP_WESOUWCE_KVD_WINEAW_SINGWE,
	MWXSW_SP_WESOUWCE_KVD_WINEAW_CHUNKS,
	MWXSW_SP_WESOUWCE_KVD_WINEAW_WAWGE_CHUNKS,
	MWXSW_SP_WESOUWCE_SPAN,
	MWXSW_SP_WESOUWCE_COUNTEWS,
	MWXSW_SP_WESOUWCE_COUNTEWS_FWOW,
	MWXSW_SP_WESOUWCE_COUNTEWS_WIF,
	MWXSW_SP_WESOUWCE_GWOBAW_POWICEWS,
	MWXSW_SP_WESOUWCE_SINGWE_WATE_POWICEWS,
	MWXSW_SP_WESOUWCE_WIF_MAC_PWOFIWES,
	MWXSW_SP_WESOUWCE_WIFS,
	MWXSW_SP_WESOUWCE_POWT_WANGE_WEGISTEWS,
};

stwuct mwxsw_sp_powt;
stwuct mwxsw_sp_wif;
stwuct mwxsw_sp_span_entwy;
enum mwxsw_sp_w3pwoto;
union mwxsw_sp_w3addw;

stwuct mwxsw_sp_uppew {
	stwuct net_device *dev;
	unsigned int wef_count;
};

enum mwxsw_sp_wif_type {
	MWXSW_SP_WIF_TYPE_SUBPOWT,
	MWXSW_SP_WIF_TYPE_VWAN,
	MWXSW_SP_WIF_TYPE_FID,
	MWXSW_SP_WIF_TYPE_IPIP_WB, /* IP-in-IP woopback. */
	MWXSW_SP_WIF_TYPE_MAX,
};

stwuct mwxsw_sp_woutew_ops;

extewn const stwuct mwxsw_sp_woutew_ops mwxsw_sp1_woutew_ops;
extewn const stwuct mwxsw_sp_woutew_ops mwxsw_sp2_woutew_ops;

stwuct mwxsw_sp_switchdev_ops;

extewn const stwuct mwxsw_sp_switchdev_ops mwxsw_sp1_switchdev_ops;
extewn const stwuct mwxsw_sp_switchdev_ops mwxsw_sp2_switchdev_ops;

enum mwxsw_sp_fid_type {
	MWXSW_SP_FID_TYPE_8021Q,
	MWXSW_SP_FID_TYPE_8021D,
	MWXSW_SP_FID_TYPE_WFID,
	MWXSW_SP_FID_TYPE_DUMMY,
	MWXSW_SP_FID_TYPE_MAX,
};

enum mwxsw_sp_nve_type {
	MWXSW_SP_NVE_TYPE_VXWAN,
};

stwuct mwxsw_sp_sb;
stwuct mwxsw_sp_bwidge;
stwuct mwxsw_sp_woutew;
stwuct mwxsw_sp_mw;
stwuct mwxsw_sp_acw;
stwuct mwxsw_sp_countew_poow;
stwuct mwxsw_sp_fid_cowe;
stwuct mwxsw_sp_kvdw;
stwuct mwxsw_sp_nve;
stwuct mwxsw_sp_kvdw_ops;
stwuct mwxsw_sp_mw_tcam_ops;
stwuct mwxsw_sp_acw_wuwei_ops;
stwuct mwxsw_sp_acw_tcam_ops;
stwuct mwxsw_sp_nve_ops;
stwuct mwxsw_sp_sb_ops;
stwuct mwxsw_sp_sb_vaws;
stwuct mwxsw_sp_powt_type_speed_ops;
stwuct mwxsw_sp_ptp_state;
stwuct mwxsw_sp_ptp_ops;
stwuct mwxsw_sp_span_ops;
stwuct mwxsw_sp_qdisc_state;
stwuct mwxsw_sp_maww_entwy;
stwuct mwxsw_sp_pgt;

stwuct mwxsw_sp_powt_mapping {
	u8 moduwe;
	u8 swot_index;
	u8 width; /* Numbew of wanes used by the powt */
	u8 moduwe_width; /* Numbew of wanes in the moduwe (static) */
	u8 wane;
};

stwuct mwxsw_sp_powt_mapping_events {
	stwuct wist_head queue;
	spinwock_t queue_wock; /* pwotects queue */
	stwuct wowk_stwuct wowk;
};

stwuct mwxsw_sp_pawsing {
	wefcount_t pawsing_depth_wef;
	u16 pawsing_depth;
	u16 vxwan_udp_dpowt;
	stwuct mutex wock; /* Pwotects pawsing configuwation */
};

stwuct mwxsw_sp {
	stwuct mwxsw_sp_powt **powts;
	stwuct mwxsw_cowe *cowe;
	const stwuct mwxsw_bus_info *bus_info;
	unsigned chaw base_mac[ETH_AWEN];
	const unsigned chaw *mac_mask;
	stwuct mwxsw_sp_uppew *wags;
	stwuct mwxsw_sp_powt_mapping *powt_mapping;
	stwuct mwxsw_sp_powt_mapping_events powt_mapping_events;
	stwuct whashtabwe sampwe_twiggew_ht;
	stwuct mwxsw_sp_sb *sb;
	stwuct mwxsw_sp_bwidge *bwidge;
	stwuct mwxsw_sp_woutew *woutew;
	stwuct mwxsw_sp_mw *mw;
	stwuct mwxsw_afa *afa;
	stwuct mwxsw_sp_acw *acw;
	stwuct mwxsw_sp_fid_cowe *fid_cowe;
	stwuct mwxsw_sp_powicew_cowe *powicew_cowe;
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe;
	stwuct mwxsw_sp_kvdw *kvdw;
	stwuct mwxsw_sp_nve *nve;
	stwuct notifiew_bwock netdevice_nb;
	stwuct mwxsw_sp_ptp_cwock *cwock;
	stwuct mwxsw_sp_ptp_state *ptp_state;
	stwuct mwxsw_sp_countew_poow *countew_poow;
	stwuct mwxsw_sp_span *span;
	stwuct mwxsw_sp_twap *twap;
	stwuct mwxsw_sp_pawsing pawsing;
	const stwuct mwxsw_sp_switchdev_ops *switchdev_ops;
	const stwuct mwxsw_sp_kvdw_ops *kvdw_ops;
	const stwuct mwxsw_afa_ops *afa_ops;
	const stwuct mwxsw_afk_ops *afk_ops;
	const stwuct mwxsw_sp_mw_tcam_ops *mw_tcam_ops;
	const stwuct mwxsw_sp_acw_wuwei_ops *acw_wuwei_ops;
	const stwuct mwxsw_sp_acw_tcam_ops *acw_tcam_ops;
	const stwuct mwxsw_sp_acw_bf_ops *acw_bf_ops;
	const stwuct mwxsw_sp_nve_ops **nve_ops_aww;
	const stwuct mwxsw_sp_sb_vaws *sb_vaws;
	const stwuct mwxsw_sp_sb_ops *sb_ops;
	const stwuct mwxsw_sp_powt_type_speed_ops *powt_type_speed_ops;
	const stwuct mwxsw_sp_ptp_ops *ptp_ops;
	const stwuct mwxsw_sp_span_ops *span_ops;
	const stwuct mwxsw_sp_powicew_cowe_ops *powicew_cowe_ops;
	const stwuct mwxsw_sp_twap_ops *twap_ops;
	const stwuct mwxsw_sp_maww_ops *maww_ops;
	const stwuct mwxsw_sp_woutew_ops *woutew_ops;
	const stwuct mwxsw_wistenew *wistenews;
	const stwuct mwxsw_sp_fid_cowe_ops *fid_cowe_ops;
	size_t wistenews_count;
	u32 wowest_shapew_bs;
	stwuct whashtabwe ipv6_addw_ht;
	stwuct mutex ipv6_addw_ht_wock; /* Pwotects ipv6_addw_ht */
	stwuct mwxsw_sp_pgt *pgt;
	boow pgt_smpe_index_vawid;
	u16 wag_pgt_base;
};

stwuct mwxsw_sp_ptp_ops {
	stwuct mwxsw_sp_ptp_cwock *
		(*cwock_init)(stwuct mwxsw_sp *mwxsw_sp, stwuct device *dev);
	void (*cwock_fini)(stwuct mwxsw_sp_ptp_cwock *cwock);

	stwuct mwxsw_sp_ptp_state *(*init)(stwuct mwxsw_sp *mwxsw_sp);
	void (*fini)(stwuct mwxsw_sp_ptp_state *ptp_state);

	/* Notify a dwivew that a packet that might be PTP was weceived. Dwivew
	 * is wesponsibwe fow fweeing the passed-in SKB.
	 */
	void (*weceive)(stwuct mwxsw_sp *mwxsw_sp, stwuct sk_buff *skb,
			u16 wocaw_powt);

	/* Notify a dwivew that a timestamped packet was twansmitted. Dwivew
	 * is wesponsibwe fow fweeing the passed-in SKB.
	 */
	void (*twansmitted)(stwuct mwxsw_sp *mwxsw_sp, stwuct sk_buff *skb,
			    u16 wocaw_powt);

	int (*hwtstamp_get)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct hwtstamp_config *config);
	int (*hwtstamp_set)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct hwtstamp_config *config);
	void (*shapew_wowk)(stwuct wowk_stwuct *wowk);
	int (*get_ts_info)(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct ethtoow_ts_info *info);
	int (*get_stats_count)(void);
	void (*get_stats_stwings)(u8 **p);
	void (*get_stats)(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  u64 *data, int data_index);
	int (*txhdw_constwuct)(stwuct mwxsw_cowe *mwxsw_cowe,
			       stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       stwuct sk_buff *skb,
			       const stwuct mwxsw_tx_info *tx_info);
};

stwuct mwxsw_sp_fid_cowe_ops {
	int (*init)(stwuct mwxsw_sp *mwxsw_sp);
	void (*fini)(stwuct mwxsw_sp *mwxsw_sp);
};

static inwine stwuct mwxsw_sp_uppew *
mwxsw_sp_wag_get(stwuct mwxsw_sp *mwxsw_sp, u16 wag_id)
{
	wetuwn &mwxsw_sp->wags[wag_id];
}

stwuct mwxsw_sp_powt_pcpu_stats {
	u64			wx_packets;
	u64			wx_bytes;
	u64			tx_packets;
	u64			tx_bytes;
	stwuct u64_stats_sync	syncp;
	u32			tx_dwopped;
};

enum mwxsw_sp_sampwe_twiggew_type {
	MWXSW_SP_SAMPWE_TWIGGEW_TYPE_INGWESS,
	MWXSW_SP_SAMPWE_TWIGGEW_TYPE_EGWESS,
	MWXSW_SP_SAMPWE_TWIGGEW_TYPE_POWICY_ENGINE,
};

stwuct mwxsw_sp_sampwe_twiggew {
	enum mwxsw_sp_sampwe_twiggew_type type;
	u16 wocaw_powt; /* Wesewved when twiggew type is not ingwess / egwess. */
};

stwuct mwxsw_sp_sampwe_pawams {
	stwuct psampwe_gwoup *psampwe_gwoup;
	u32 twunc_size;
	u32 wate;
	boow twuncate;
};

stwuct mwxsw_sp_bwidge_powt;
stwuct mwxsw_sp_fid;

stwuct mwxsw_sp_powt_vwan {
	stwuct wist_head wist;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	stwuct mwxsw_sp_fid *fid;
	u16 vid;
	stwuct mwxsw_sp_bwidge_powt *bwidge_powt;
	stwuct wist_head bwidge_vwan_node;
};

/* No need an intewnaw wock; At wowse - miss a singwe pewiodic itewation */
stwuct mwxsw_sp_powt_xstats {
	u64 ecn;
	u64 tc_ecn[TC_MAX_QUEUE];
	u64 wwed_dwop[TC_MAX_QUEUE];
	u64 taiw_dwop[TC_MAX_QUEUE];
	u64 backwog[TC_MAX_QUEUE];
	u64 tx_bytes[IEEE_8021QAZ_MAX_TCS];
	u64 tx_packets[IEEE_8021QAZ_MAX_TCS];
};

stwuct mwxsw_sp_ptp_powt_diw_stats {
	u64 packets;
	u64 timestamps;
};

stwuct mwxsw_sp_ptp_powt_stats {
	stwuct mwxsw_sp_ptp_powt_diw_stats wx_gcd;
	stwuct mwxsw_sp_ptp_powt_diw_stats tx_gcd;
};

stwuct mwxsw_sp_powt {
	stwuct net_device *dev;
	stwuct mwxsw_sp_powt_pcpu_stats __pewcpu *pcpu_stats;
	stwuct mwxsw_sp *mwxsw_sp;
	u16 wocaw_powt;
	u8 wagged:1,
	   spwit:1,
	   secuwity:1;
	u16 pvid;
	u16 wag_id;
	stwuct {
		u8 tx_pause:1,
		   wx_pause:1,
		   autoneg:1;
	} wink;
	stwuct {
		stwuct ieee_ets *ets;
		stwuct ieee_maxwate *maxwate;
		stwuct ieee_pfc *pfc;
		enum mwxsw_weg_qpts_twust_state twust_state;
	} dcb;
	stwuct mwxsw_sp_powt_mapping mapping; /* mapping is constant duwing the
					       * mwxsw_sp_powt wifetime, howevew
					       * the same wocawpowt can have
					       * diffewent mapping.
					       */
	stwuct {
		#define MWXSW_HW_STATS_UPDATE_TIME HZ
		stwuct wtnw_wink_stats64 stats;
		stwuct mwxsw_sp_powt_xstats xstats;
		stwuct dewayed_wowk update_dw;
	} pewiodic_hw_stats;
	stwuct wist_head vwans_wist;
	stwuct mwxsw_sp_powt_vwan *defauwt_vwan;
	stwuct mwxsw_sp_qdisc_state *qdisc;
	unsigned acw_wuwe_count;
	stwuct mwxsw_sp_fwow_bwock *ing_fwow_bwock;
	stwuct mwxsw_sp_fwow_bwock *eg_fwow_bwock;
	stwuct {
		stwuct dewayed_wowk shapew_dw;
		stwuct hwtstamp_config hwtstamp_config;
		u16 ing_types;
		u16 egw_types;
		stwuct mwxsw_sp_ptp_powt_stats stats;
	} ptp;
	int max_mtu;
	u32 max_speed;
	stwuct mwxsw_sp_hdwoom *hdwoom;
	u64 moduwe_ovewheat_initiaw_vaw;
};

stwuct mwxsw_sp_powt_type_speed_ops {
	void (*fwom_ptys_suppowted_powt)(stwuct mwxsw_sp *mwxsw_sp,
					 u32 ptys_eth_pwoto,
					 stwuct ethtoow_wink_ksettings *cmd);
	void (*fwom_ptys_wink)(stwuct mwxsw_sp *mwxsw_sp, u32 ptys_eth_pwoto,
			       unsigned wong *mode);
	u32 (*fwom_ptys_speed)(stwuct mwxsw_sp *mwxsw_sp, u32 ptys_eth_pwoto);
	void (*fwom_ptys_wink_mode)(stwuct mwxsw_sp *mwxsw_sp,
				    boow cawwiew_ok, u32 ptys_eth_pwoto,
				    stwuct ethtoow_wink_ksettings *cmd);
	int (*ptys_max_speed)(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 *p_max_speed);
	u32 (*to_ptys_advewt_wink)(stwuct mwxsw_sp *mwxsw_sp,
				   const stwuct ethtoow_wink_ksettings *cmd);
	u32 (*to_ptys_speed_wanes)(stwuct mwxsw_sp *mwxsw_sp, u8 width,
				   const stwuct ethtoow_wink_ksettings *cmd);
	void (*weg_ptys_eth_pack)(stwuct mwxsw_sp *mwxsw_sp, chaw *paywoad,
				  u16 wocaw_powt, u32 pwoto_admin, boow autoneg);
	void (*weg_ptys_eth_unpack)(stwuct mwxsw_sp *mwxsw_sp, chaw *paywoad,
				    u32 *p_eth_pwoto_cap,
				    u32 *p_eth_pwoto_admin,
				    u32 *p_eth_pwoto_opew);
	u32 (*ptys_pwoto_cap_masked_get)(u32 eth_pwoto_cap);
};

stwuct mwxsw_sp_powts_bitmap {
	unsigned wong *bitmap;
	unsigned int nbits;
};

static inwine int
mwxsw_sp_powt_bitmap_init(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_powts_bitmap *powts_bm)
{
	unsigned int nbits = mwxsw_cowe_max_powts(mwxsw_sp->cowe);

	powts_bm->nbits = nbits;
	powts_bm->bitmap = bitmap_zawwoc(nbits, GFP_KEWNEW);
	if (!powts_bm->bitmap)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void
mwxsw_sp_powt_bitmap_fini(stwuct mwxsw_sp_powts_bitmap *powts_bm)
{
	bitmap_fwee(powts_bm->bitmap);
}

static inwine u8 mwxsw_sp_tunnew_ecn_decap(u8 outew_ecn, u8 innew_ecn,
					   boow *twap_en)
{
	boow set_ce = fawse;

	*twap_en = !!__INET_ECN_decapsuwate(outew_ecn, innew_ecn, &set_ce);
	if (set_ce)
		wetuwn INET_ECN_CE;
	ewse if (outew_ecn == INET_ECN_ECT_1 && innew_ecn == INET_ECN_ECT_0)
		wetuwn INET_ECN_ECT_1;
	ewse
		wetuwn innew_ecn;
}

static inwine stwuct net_device *
mwxsw_sp_bwidge_vxwan_dev_find(stwuct net_device *bw_dev)
{
	stwuct net_device *dev;
	stwuct wist_head *itew;

	netdev_fow_each_wowew_dev(bw_dev, dev, itew) {
		if (netif_is_vxwan(dev))
			wetuwn dev;
	}

	wetuwn NUWW;
}

static inwine boow mwxsw_sp_bwidge_has_vxwan(stwuct net_device *bw_dev)
{
	wetuwn !!mwxsw_sp_bwidge_vxwan_dev_find(bw_dev);
}

static inwine int
mwxsw_sp_vxwan_mapped_vid(const stwuct net_device *vxwan_dev, u16 *p_vid)
{
	stwuct bwidge_vwan_info vinfo;
	u16 vid = 0;
	int eww;

	eww = bw_vwan_get_pvid(vxwan_dev, &vid);
	if (eww || !vid)
		goto out;

	eww = bw_vwan_get_info(vxwan_dev, vid, &vinfo);
	if (eww || !(vinfo.fwags & BWIDGE_VWAN_INFO_UNTAGGED))
		vid = 0;

out:
	*p_vid = vid;
	wetuwn eww;
}

static inwine boow
mwxsw_sp_powt_is_pause_en(const stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn mwxsw_sp_powt->wink.tx_pause || mwxsw_sp_powt->wink.wx_pause;
}

static inwine stwuct mwxsw_sp_powt *
mwxsw_sp_powt_wagged_get(stwuct mwxsw_sp *mwxsw_sp, u16 wag_id, u8 powt_index)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	u16 wocaw_powt;

	wocaw_powt = mwxsw_cowe_wag_mapping_get(mwxsw_sp->cowe,
						wag_id, powt_index);
	mwxsw_sp_powt = mwxsw_sp->powts[wocaw_powt];
	wetuwn mwxsw_sp_powt && mwxsw_sp_powt->wagged ? mwxsw_sp_powt : NUWW;
}

static inwine stwuct mwxsw_sp_powt_vwan *
mwxsw_sp_powt_vwan_find_by_vid(const stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       u16 vid)
{
	stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan;

	wist_fow_each_entwy(mwxsw_sp_powt_vwan, &mwxsw_sp_powt->vwans_wist,
			    wist) {
		if (mwxsw_sp_powt_vwan->vid == vid)
			wetuwn mwxsw_sp_powt_vwan;
	}

	wetuwn NUWW;
}

enum mwxsw_sp_fwood_type {
	MWXSW_SP_FWOOD_TYPE_UC,
	MWXSW_SP_FWOOD_TYPE_BC,
	MWXSW_SP_FWOOD_TYPE_MC,
	/* Fow WSP FIDs in CFF mode. */
	MWXSW_SP_FWOOD_TYPE_NOT_UC,
	/* Fow NVE twaffic. */
	MWXSW_SP_FWOOD_TYPE_ANY,
};

int mwxsw_sp_powt_get_stats_waw(stwuct net_device *dev, int gwp,
				int pwio, chaw *ppcnt_pw);
int mwxsw_sp_powt_admin_status_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   boow is_up);
int
mwxsw_sp_powt_vwan_cwassification_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      boow is_8021ad_tagged,
				      boow is_8021q_tagged);
static inwine boow
mwxsw_sp_wocaw_powt_is_vawid(stwuct mwxsw_sp *mwxsw_sp, u16 wocaw_powt)
{
	unsigned int max_powts = mwxsw_cowe_max_powts(mwxsw_sp->cowe);

	wetuwn wocaw_powt < max_powts && wocaw_powt;
}

/* spectwum_buffews.c */
stwuct mwxsw_sp_hdwoom_pwio {
	/* Numbew of powt buffew associated with this pwiowity. This is the
	 * actuawwy configuwed vawue.
	 */
	u8 buf_idx;
	/* Vawue of buf_idx deduced fwom the DCB ETS configuwation. */
	u8 ets_buf_idx;
	/* Vawue of buf_idx taken fwom the dcbnw_setbuffew configuwation. */
	u8 set_buf_idx;
	boow wossy;
};

stwuct mwxsw_sp_hdwoom_buf {
	u32 thwes_cewws;
	u32 size_cewws;
	/* Size wequiwement fowm dcbnw_setbuffew. */
	u32 set_size_cewws;
	boow wossy;
};

enum mwxsw_sp_hdwoom_mode {
	MWXSW_SP_HDWOOM_MODE_DCB,
	MWXSW_SP_HDWOOM_MODE_TC,
};

#define MWXSW_SP_PB_COUNT 10

stwuct mwxsw_sp_hdwoom {
	enum mwxsw_sp_hdwoom_mode mode;

	stwuct {
		stwuct mwxsw_sp_hdwoom_pwio pwio[IEEE_8021Q_MAX_PWIOWITIES];
	} pwios;
	stwuct {
		stwuct mwxsw_sp_hdwoom_buf buf[MWXSW_SP_PB_COUNT];
	} bufs;
	stwuct {
		/* Size actuawwy configuwed fow the intewnaw buffew. Equaw to
		 * wesewve when intewnaw buffew is enabwed.
		 */
		u32 size_cewws;
		/* Space wesewved in the headwoom fow the intewnaw buffew. Powt
		 * buffews awe not awwowed to gwow into this space.
		 */
		u32 wesewve_cewws;
		boow enabwe;
	} int_buf;
	int deway_bytes;
	int mtu;
};

int mwxsw_sp_buffews_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_buffews_fini(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_powt_buffews_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
void mwxsw_sp_powt_buffews_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
int mwxsw_sp_sb_poow_get(stwuct mwxsw_cowe *mwxsw_cowe,
			 unsigned int sb_index, u16 poow_index,
			 stwuct devwink_sb_poow_info *poow_info);
int mwxsw_sp_sb_poow_set(stwuct mwxsw_cowe *mwxsw_cowe,
			 unsigned int sb_index, u16 poow_index, u32 size,
			 enum devwink_sb_thweshowd_type thweshowd_type,
			 stwuct netwink_ext_ack *extack);
int mwxsw_sp_sb_powt_poow_get(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
			      unsigned int sb_index, u16 poow_index,
			      u32 *p_thweshowd);
int mwxsw_sp_sb_powt_poow_set(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
			      unsigned int sb_index, u16 poow_index,
			      u32 thweshowd, stwuct netwink_ext_ack *extack);
int mwxsw_sp_sb_tc_poow_bind_get(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				 unsigned int sb_index, u16 tc_index,
				 enum devwink_sb_poow_type poow_type,
				 u16 *p_poow_index, u32 *p_thweshowd);
int mwxsw_sp_sb_tc_poow_bind_set(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				 unsigned int sb_index, u16 tc_index,
				 enum devwink_sb_poow_type poow_type,
				 u16 poow_index, u32 thweshowd,
				 stwuct netwink_ext_ack *extack);
int mwxsw_sp_sb_occ_snapshot(stwuct mwxsw_cowe *mwxsw_cowe,
			     unsigned int sb_index);
int mwxsw_sp_sb_occ_max_cweaw(stwuct mwxsw_cowe *mwxsw_cowe,
			      unsigned int sb_index);
int mwxsw_sp_sb_occ_powt_poow_get(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				  unsigned int sb_index, u16 poow_index,
				  u32 *p_cuw, u32 *p_max);
int mwxsw_sp_sb_occ_tc_powt_bind_get(stwuct mwxsw_cowe_powt *mwxsw_cowe_powt,
				     unsigned int sb_index, u16 tc_index,
				     enum devwink_sb_poow_type poow_type,
				     u32 *p_cuw, u32 *p_max);
u32 mwxsw_sp_cewws_bytes(const stwuct mwxsw_sp *mwxsw_sp, u32 cewws);
u32 mwxsw_sp_bytes_cewws(const stwuct mwxsw_sp *mwxsw_sp, u32 bytes);
void mwxsw_sp_hdwoom_pwios_weset_buf_idx(stwuct mwxsw_sp_hdwoom *hdwoom);
void mwxsw_sp_hdwoom_bufs_weset_wossiness(stwuct mwxsw_sp_hdwoom *hdwoom);
void mwxsw_sp_hdwoom_bufs_weset_sizes(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      stwuct mwxsw_sp_hdwoom *hdwoom);
int mwxsw_sp_hdwoom_configuwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      const stwuct mwxsw_sp_hdwoom *hdwoom);
stwuct mwxsw_sp_sampwe_pawams *
mwxsw_sp_sampwe_twiggew_pawams_wookup(stwuct mwxsw_sp *mwxsw_sp,
				      const stwuct mwxsw_sp_sampwe_twiggew *twiggew);
int
mwxsw_sp_sampwe_twiggew_pawams_set(stwuct mwxsw_sp *mwxsw_sp,
				   const stwuct mwxsw_sp_sampwe_twiggew *twiggew,
				   const stwuct mwxsw_sp_sampwe_pawams *pawams,
				   stwuct netwink_ext_ack *extack);
void
mwxsw_sp_sampwe_twiggew_pawams_unset(stwuct mwxsw_sp *mwxsw_sp,
				     const stwuct mwxsw_sp_sampwe_twiggew *twiggew);
int mwxsw_sp_ipv6_addw_kvdw_index_get(stwuct mwxsw_sp *mwxsw_sp,
				      const stwuct in6_addw *addw6,
				      u32 *p_kvdw_index);
void
mwxsw_sp_ipv6_addw_put(stwuct mwxsw_sp *mwxsw_sp, const stwuct in6_addw *addw6);

extewn const stwuct mwxsw_sp_sb_vaws mwxsw_sp1_sb_vaws;
extewn const stwuct mwxsw_sp_sb_vaws mwxsw_sp2_sb_vaws;

extewn const stwuct mwxsw_sp_sb_ops mwxsw_sp1_sb_ops;
extewn const stwuct mwxsw_sp_sb_ops mwxsw_sp2_sb_ops;
extewn const stwuct mwxsw_sp_sb_ops mwxsw_sp3_sb_ops;

/* spectwum_switchdev.c */
int mwxsw_sp_switchdev_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_switchdev_fini(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_wif_fdb_op(stwuct mwxsw_sp *mwxsw_sp, const chaw *mac, u16 fid,
			boow adding);
void
mwxsw_sp_powt_vwan_bwidge_weave(stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan);
int mwxsw_sp_powt_bwidge_join(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      stwuct net_device *bwpowt_dev,
			      stwuct net_device *bw_dev,
			      stwuct netwink_ext_ack *extack);
void mwxsw_sp_powt_bwidge_weave(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				stwuct net_device *bwpowt_dev,
				stwuct net_device *bw_dev);
boow mwxsw_sp_bwidge_device_is_offwoaded(const stwuct mwxsw_sp *mwxsw_sp,
					 const stwuct net_device *bw_dev);
int mwxsw_sp_bwidge_vxwan_join(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct net_device *bw_dev,
			       const stwuct net_device *vxwan_dev, u16 vid,
			       stwuct netwink_ext_ack *extack);
void mwxsw_sp_bwidge_vxwan_weave(stwuct mwxsw_sp *mwxsw_sp,
				 const stwuct net_device *vxwan_dev);
extewn stwuct notifiew_bwock mwxsw_sp_switchdev_notifiew;

/* spectwum.c */
void mwxsw_sp_wx_wistenew_no_mawk_func(stwuct sk_buff *skb,
				       u16 wocaw_powt, void *pwiv);
void mwxsw_sp_ptp_weceive(stwuct mwxsw_sp *mwxsw_sp, stwuct sk_buff *skb,
			  u16 wocaw_powt);
int mwxsw_sp_powt_speed_get(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 *speed);
int mwxsw_sp_powt_ets_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  enum mwxsw_weg_qeec_hw hw, u8 index, u8 next_index,
			  boow dwww, u8 dwww_weight);
int mwxsw_sp_powt_pwio_tc_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			      u8 switch_pwio, u8 tcwass);
int mwxsw_sp_powt_ets_maxwate_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  enum mwxsw_weg_qeec_hw hw, u8 index,
				  u8 next_index, u32 maxwate, u8 buwst_size);
enum mwxsw_weg_spms_state mwxsw_sp_stp_spms_state(u8 stp_state);
int mwxsw_sp_powt_vid_stp_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid,
			      u8 state);
int mwxsw_sp_powt_vp_mode_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt, boow enabwe);
int mwxsw_sp_powt_vid_weawning_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid,
				   boow weawn_enabwe);
int mwxsw_sp_powt_secuwity_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       boow enabwe);
int mwxsw_sp_ethtype_to_svew_type(u16 ethtype, u8 *p_svew_type);
int mwxsw_sp_powt_egwess_ethtype_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     u16 ethtype);
int mwxsw_sp_powt_pvid_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid,
			   u16 ethtype);
stwuct mwxsw_sp_powt_vwan *
mwxsw_sp_powt_vwan_cweate(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid);
void mwxsw_sp_powt_vwan_destwoy(stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan);
int mwxsw_sp_powt_kiww_vid(stwuct net_device *dev,
			   __be16 __awways_unused pwoto, u16 vid);
int mwxsw_sp_powt_vwan_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid_begin,
			   u16 vid_end, boow is_membew, boow untagged);
int mwxsw_sp_fwow_countew_get(stwuct mwxsw_sp *mwxsw_sp,
			      unsigned int countew_index, u64 *packets,
			      u64 *bytes);
int mwxsw_sp_fwow_countew_awwoc(stwuct mwxsw_sp *mwxsw_sp,
				unsigned int *p_countew_index);
void mwxsw_sp_fwow_countew_fwee(stwuct mwxsw_sp *mwxsw_sp,
				unsigned int countew_index);
void mwxsw_sp_txhdw_constwuct(stwuct sk_buff *skb,
			      const stwuct mwxsw_tx_info *tx_info);
int mwxsw_sp_txhdw_ptp_data_constwuct(stwuct mwxsw_cowe *mwxsw_cowe,
				      stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      stwuct sk_buff *skb,
				      const stwuct mwxsw_tx_info *tx_info);
boow mwxsw_sp_powt_dev_check(const stwuct net_device *dev);
stwuct mwxsw_sp *mwxsw_sp_wowew_get(stwuct net_device *dev);
stwuct mwxsw_sp_powt *mwxsw_sp_powt_dev_wowew_find(stwuct net_device *dev);
stwuct mwxsw_sp_powt *mwxsw_sp_powt_dev_wowew_find_wcu(stwuct net_device *dev);
int mwxsw_sp_pawsing_depth_inc(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_pawsing_depth_dec(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_pawsing_vxwan_udp_dpowt_set(stwuct mwxsw_sp *mwxsw_sp,
					 __be16 udp_dpowt);

/* spectwum_dcb.c */
#ifdef CONFIG_MWXSW_SPECTWUM_DCB
int mwxsw_sp_powt_dcb_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
void mwxsw_sp_powt_dcb_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
#ewse
static inwine int mwxsw_sp_powt_dcb_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	wetuwn 0;
}
static inwine void mwxsw_sp_powt_dcb_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{}
#endif

/* spectwum_woutew.c */
enum mwxsw_sp_w3pwoto {
	MWXSW_SP_W3_PWOTO_IPV4,
	MWXSW_SP_W3_PWOTO_IPV6,
#define MWXSW_SP_W3_PWOTO_MAX	(MWXSW_SP_W3_PWOTO_IPV6 + 1)
};

union mwxsw_sp_w3addw {
	__be32 addw4;
	stwuct in6_addw addw6;
};

u16 mwxsw_sp_wif_index(const stwuct mwxsw_sp_wif *wif);
int mwxsw_sp_wif_subpowt_powt(const stwuct mwxsw_sp_wif *wif,
			      u16 *powt, boow *is_wag);
int mwxsw_sp_woutew_init(stwuct mwxsw_sp *mwxsw_sp,
			 stwuct netwink_ext_ack *extack);
void mwxsw_sp_woutew_fini(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_wif_macvwan_dew(stwuct mwxsw_sp *mwxsw_sp,
			      const stwuct net_device *macvwan_dev);
void
mwxsw_sp_powt_vwan_woutew_weave(stwuct mwxsw_sp_powt_vwan *mwxsw_sp_powt_vwan);
void mwxsw_sp_wif_destwoy_by_dev(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct net_device *dev);
boow mwxsw_sp_wif_exists(stwuct mwxsw_sp *mwxsw_sp,
			 const stwuct net_device *dev);
u16 mwxsw_sp_wif_vid(stwuct mwxsw_sp *mwxsw_sp, const stwuct net_device *dev);
u16 mwxsw_sp_woutew_powt(const stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_woutew_nve_pwomote_decap(stwuct mwxsw_sp *mwxsw_sp, u32 uw_tb_id,
				      enum mwxsw_sp_w3pwoto uw_pwoto,
				      const union mwxsw_sp_w3addw *uw_sip,
				      u32 tunnew_index);
void mwxsw_sp_woutew_nve_demote_decap(stwuct mwxsw_sp *mwxsw_sp, u32 uw_tb_id,
				      enum mwxsw_sp_w3pwoto uw_pwoto,
				      const union mwxsw_sp_w3addw *uw_sip);
int mwxsw_sp_woutew_tb_id_vw_id(stwuct mwxsw_sp *mwxsw_sp, u32 tb_id,
				u16 *vw_id);
int mwxsw_sp_woutew_uw_wif_get(stwuct mwxsw_sp *mwxsw_sp, u32 uw_tb_id,
			       u16 *uw_wif_index);
void mwxsw_sp_woutew_uw_wif_put(stwuct mwxsw_sp *mwxsw_sp, u16 uw_wif_index);

/* spectwum_kvdw.c */
enum mwxsw_sp_kvdw_entwy_type {
	MWXSW_SP_KVDW_ENTWY_TYPE_ADJ,
	MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET,
	MWXSW_SP_KVDW_ENTWY_TYPE_PBS,
	MWXSW_SP_KVDW_ENTWY_TYPE_MCWIGW,
	MWXSW_SP_KVDW_ENTWY_TYPE_IPV6_ADDWESS,
	MWXSW_SP_KVDW_ENTWY_TYPE_TNUMT,
};

static inwine unsigned int
mwxsw_sp_kvdw_entwy_size(enum mwxsw_sp_kvdw_entwy_type type)
{
	switch (type) {
	case MWXSW_SP_KVDW_ENTWY_TYPE_ADJ:
	case MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET:
	case MWXSW_SP_KVDW_ENTWY_TYPE_PBS:
	case MWXSW_SP_KVDW_ENTWY_TYPE_MCWIGW:
	case MWXSW_SP_KVDW_ENTWY_TYPE_IPV6_ADDWESS:
	case MWXSW_SP_KVDW_ENTWY_TYPE_TNUMT:
	defauwt:
		wetuwn 1;
	}
}

stwuct mwxsw_sp_kvdw_ops {
	size_t pwiv_size;
	int (*init)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv);
	void (*fini)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv);
	int (*awwoc)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
		     enum mwxsw_sp_kvdw_entwy_type type,
		     unsigned int entwy_count, u32 *p_entwy_index);
	void (*fwee)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
		     enum mwxsw_sp_kvdw_entwy_type type,
		     unsigned int entwy_count, int entwy_index);
	int (*awwoc_size_quewy)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				enum mwxsw_sp_kvdw_entwy_type type,
				unsigned int entwy_count,
				unsigned int *p_awwoc_count);
	int (*wesouwces_wegistew)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv);
};

int mwxsw_sp_kvdw_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_kvdw_fini(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_kvdw_awwoc(stwuct mwxsw_sp *mwxsw_sp,
			enum mwxsw_sp_kvdw_entwy_type type,
			unsigned int entwy_count, u32 *p_entwy_index);
void mwxsw_sp_kvdw_fwee(stwuct mwxsw_sp *mwxsw_sp,
			enum mwxsw_sp_kvdw_entwy_type type,
			unsigned int entwy_count, int entwy_index);
int mwxsw_sp_kvdw_awwoc_count_quewy(stwuct mwxsw_sp *mwxsw_sp,
				    enum mwxsw_sp_kvdw_entwy_type type,
				    unsigned int entwy_count,
				    unsigned int *p_awwoc_count);

/* spectwum1_kvdw.c */
extewn const stwuct mwxsw_sp_kvdw_ops mwxsw_sp1_kvdw_ops;
int mwxsw_sp1_kvdw_wesouwces_wegistew(stwuct mwxsw_cowe *mwxsw_cowe);

/* spectwum2_kvdw.c */
extewn const stwuct mwxsw_sp_kvdw_ops mwxsw_sp2_kvdw_ops;

enum mwxsw_sp_acw_mangwe_fiewd {
	MWXSW_SP_ACW_MANGWE_FIEWD_IP_DSFIEWD,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP_DSCP,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP_ECN,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP_SPOWT,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP_DPOWT,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP4_SIP,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP4_DIP,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_1,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_2,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_3,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_4,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_1,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_2,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_3,
	MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_4,
};

stwuct mwxsw_sp_acw_wuwe_info {
	unsigned int pwiowity;
	stwuct mwxsw_afk_ewement_vawues vawues;
	stwuct mwxsw_afa_bwock *act_bwock;
	u8 action_cweated:1,
	   ingwess_bind_bwockew:1,
	   egwess_bind_bwockew:1,
	   countew_vawid:1,
	   powicew_index_vawid:1,
	   ipv6_vawid:1,
	   swc_powt_wange_weg_vawid:1,
	   dst_powt_wange_weg_vawid:1;
	unsigned int countew_index;
	u16 powicew_index;
	u8 swc_powt_wange_weg_index;
	u8 dst_powt_wange_weg_index;
	stwuct {
		u32 pwev_vaw;
		enum mwxsw_sp_acw_mangwe_fiewd pwev_fiewd;
	} ipv6;
};

/* spectwum_fwow.c */
stwuct mwxsw_sp_fwow_bwock {
	stwuct wist_head binding_wist;
	stwuct {
		stwuct wist_head wist;
		unsigned int min_pwio;
		unsigned int max_pwio;
	} maww;
	stwuct mwxsw_sp_acw_wuweset *wuweset_zewo;
	stwuct mwxsw_sp *mwxsw_sp;
	unsigned int wuwe_count;
	unsigned int disabwe_count;
	unsigned int ingwess_bwockew_wuwe_count;
	unsigned int egwess_bwockew_wuwe_count;
	unsigned int ingwess_binding_count;
	unsigned int egwess_binding_count;
	stwuct net *net;
};

stwuct mwxsw_sp_fwow_bwock_binding {
	stwuct wist_head wist;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	boow ingwess;
};

static inwine stwuct mwxsw_sp *
mwxsw_sp_fwow_bwock_mwxsw_sp(stwuct mwxsw_sp_fwow_bwock *bwock)
{
	wetuwn bwock->mwxsw_sp;
}

static inwine unsigned int
mwxsw_sp_fwow_bwock_wuwe_count(const stwuct mwxsw_sp_fwow_bwock *bwock)
{
	wetuwn bwock ? bwock->wuwe_count : 0;
}

static inwine void
mwxsw_sp_fwow_bwock_disabwe_inc(stwuct mwxsw_sp_fwow_bwock *bwock)
{
	if (bwock)
		bwock->disabwe_count++;
}

static inwine void
mwxsw_sp_fwow_bwock_disabwe_dec(stwuct mwxsw_sp_fwow_bwock *bwock)
{
	if (bwock)
		bwock->disabwe_count--;
}

static inwine boow
mwxsw_sp_fwow_bwock_disabwed(const stwuct mwxsw_sp_fwow_bwock *bwock)
{
	wetuwn bwock->disabwe_count;
}

static inwine boow
mwxsw_sp_fwow_bwock_is_egwess_bound(const stwuct mwxsw_sp_fwow_bwock *bwock)
{
	wetuwn bwock->egwess_binding_count;
}

static inwine boow
mwxsw_sp_fwow_bwock_is_ingwess_bound(const stwuct mwxsw_sp_fwow_bwock *bwock)
{
	wetuwn bwock->ingwess_binding_count;
}

static inwine boow
mwxsw_sp_fwow_bwock_is_mixed_bound(const stwuct mwxsw_sp_fwow_bwock *bwock)
{
	wetuwn bwock->ingwess_binding_count && bwock->egwess_binding_count;
}

stwuct mwxsw_sp_fwow_bwock *mwxsw_sp_fwow_bwock_cweate(stwuct mwxsw_sp *mwxsw_sp,
						       stwuct net *net);
void mwxsw_sp_fwow_bwock_destwoy(stwuct mwxsw_sp_fwow_bwock *bwock);
int mwxsw_sp_setup_tc_bwock_cwsact(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct fwow_bwock_offwoad *f,
				   boow ingwess);

/* spectwum_acw.c */
stwuct mwxsw_sp_acw_wuweset;

enum mwxsw_sp_acw_pwofiwe {
	MWXSW_SP_ACW_PWOFIWE_FWOWEW,
	MWXSW_SP_ACW_PWOFIWE_MW,
};

stwuct mwxsw_afk *mwxsw_sp_acw_afk(stwuct mwxsw_sp_acw *acw);
stwuct mwxsw_sp_acw_tcam *mwxsw_sp_acw_to_tcam(stwuct mwxsw_sp_acw *acw);

int mwxsw_sp_acw_wuweset_bind(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_fwow_bwock *bwock,
			      stwuct mwxsw_sp_fwow_bwock_binding *binding);
void mwxsw_sp_acw_wuweset_unbind(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_fwow_bwock *bwock,
				 stwuct mwxsw_sp_fwow_bwock_binding *binding);
stwuct mwxsw_sp_acw_wuweset *
mwxsw_sp_acw_wuweset_wookup(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			    enum mwxsw_sp_acw_pwofiwe pwofiwe);
stwuct mwxsw_sp_acw_wuweset *
mwxsw_sp_acw_wuweset_get(stwuct mwxsw_sp *mwxsw_sp,
			 stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			 enum mwxsw_sp_acw_pwofiwe pwofiwe,
			 stwuct mwxsw_afk_ewement_usage *tmpwt_ewusage);
void mwxsw_sp_acw_wuweset_put(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_acw_wuweset *wuweset);
u16 mwxsw_sp_acw_wuweset_gwoup_id(stwuct mwxsw_sp_acw_wuweset *wuweset);
void mwxsw_sp_acw_wuweset_pwio_get(stwuct mwxsw_sp_acw_wuweset *wuweset,
				   unsigned int *p_min_pwio,
				   unsigned int *p_max_pwio);

stwuct mwxsw_sp_acw_wuwe_info *
mwxsw_sp_acw_wuwei_cweate(stwuct mwxsw_sp_acw *acw,
			  stwuct mwxsw_afa_bwock *afa_bwock);
void mwxsw_sp_acw_wuwei_destwoy(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_wuwe_info *wuwei);
int mwxsw_sp_acw_wuwei_commit(stwuct mwxsw_sp_acw_wuwe_info *wuwei);
void mwxsw_sp_acw_wuwei_pwiowity(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				 unsigned int pwiowity);
void mwxsw_sp_acw_wuwei_keymask_u32(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    enum mwxsw_afk_ewement ewement,
				    u32 key_vawue, u32 mask_vawue);
void mwxsw_sp_acw_wuwei_keymask_buf(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    enum mwxsw_afk_ewement ewement,
				    const chaw *key_vawue,
				    const chaw *mask_vawue, unsigned int wen);
int mwxsw_sp_acw_wuwei_act_continue(stwuct mwxsw_sp_acw_wuwe_info *wuwei);
int mwxsw_sp_acw_wuwei_act_jump(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				u16 gwoup_id);
int mwxsw_sp_acw_wuwei_act_tewminate(stwuct mwxsw_sp_acw_wuwe_info *wuwei);
int mwxsw_sp_acw_wuwei_act_dwop(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				boow ingwess,
				const stwuct fwow_action_cookie *fa_cookie,
				stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_twap(stwuct mwxsw_sp_acw_wuwe_info *wuwei);
int mwxsw_sp_acw_wuwei_act_miwwow(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  stwuct mwxsw_sp_fwow_bwock *bwock,
				  stwuct net_device *out_dev,
				  stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_fwd(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_wuwe_info *wuwei,
			       stwuct net_device *out_dev,
			       stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_vwan(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				u32 action, u16 vid, u16 pwoto, u8 pwio,
				stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_pwiowity(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    u32 pwio, stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_mangwe(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  enum fwow_action_mangwe_base htype,
				  u32 offset, u32 mask, u32 vaw,
				  stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_powice(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  u32 index, u64 wate_bytes_ps,
				  u32 buwst, stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_count(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				 stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_fid_set(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				   u16 fid, stwuct netwink_ext_ack *extack);
int mwxsw_sp_acw_wuwei_act_ignowe(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  boow disabwe_weawning, boow disabwe_secuwity);
int mwxsw_sp_acw_wuwei_act_sampwe(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  stwuct mwxsw_sp_fwow_bwock *bwock,
				  stwuct psampwe_gwoup *psampwe_gwoup, u32 wate,
				  u32 twunc_size, boow twuncate,
				  stwuct netwink_ext_ack *extack);

stwuct mwxsw_sp_acw_wuwe;

stwuct mwxsw_sp_acw_wuwe *
mwxsw_sp_acw_wuwe_cweate(stwuct mwxsw_sp *mwxsw_sp,
			 stwuct mwxsw_sp_acw_wuweset *wuweset,
			 unsigned wong cookie,
			 stwuct mwxsw_afa_bwock *afa_bwock,
			 stwuct netwink_ext_ack *extack);
void mwxsw_sp_acw_wuwe_destwoy(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_wuwe *wuwe);
int mwxsw_sp_acw_wuwe_add(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_acw_wuwe *wuwe);
void mwxsw_sp_acw_wuwe_dew(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_acw_wuwe *wuwe);
int mwxsw_sp_acw_wuwe_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp_acw_wuwe *wuwe,
				     stwuct mwxsw_afa_bwock *afa_bwock);
stwuct mwxsw_sp_acw_wuwe *
mwxsw_sp_acw_wuwe_wookup(stwuct mwxsw_sp *mwxsw_sp,
			 stwuct mwxsw_sp_acw_wuweset *wuweset,
			 unsigned wong cookie);
stwuct mwxsw_sp_acw_wuwe_info *
mwxsw_sp_acw_wuwe_wuwei(stwuct mwxsw_sp_acw_wuwe *wuwe);
int mwxsw_sp_acw_wuwe_get_stats(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_wuwe *wuwe,
				u64 *packets, u64 *bytes, u64 *dwops,
				u64 *wast_use,
				enum fwow_action_hw_stats *used_hw_stats);

stwuct mwxsw_sp_fid *mwxsw_sp_acw_dummy_fid(stwuct mwxsw_sp *mwxsw_sp);

static inwine const stwuct fwow_action_cookie *
mwxsw_sp_acw_act_cookie_wookup(stwuct mwxsw_sp *mwxsw_sp, u32 cookie_index)
{
	wetuwn mwxsw_afa_cookie_wookup(mwxsw_sp->afa, cookie_index);
}

int mwxsw_sp_acw_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_acw_fini(stwuct mwxsw_sp *mwxsw_sp);

stwuct mwxsw_sp_acw_mangwe_action;

stwuct mwxsw_sp_acw_wuwei_ops {
	int (*act_mangwe_fiewd)(stwuct mwxsw_sp *mwxsw_sp, stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				stwuct mwxsw_sp_acw_mangwe_action *mact, u32 vaw,
				stwuct netwink_ext_ack *extack);
};

extewn stwuct mwxsw_sp_acw_wuwei_ops mwxsw_sp1_acw_wuwei_ops;
extewn stwuct mwxsw_sp_acw_wuwei_ops mwxsw_sp2_acw_wuwei_ops;

/* spectwum_acw_tcam.c */
stwuct mwxsw_sp_acw_tcam;
stwuct mwxsw_sp_acw_tcam_wegion;

stwuct mwxsw_sp_acw_tcam_ops {
	enum mwxsw_weg_ptaw_key_type key_type;
	size_t pwiv_size;
	int (*init)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
		    stwuct mwxsw_sp_acw_tcam *tcam);
	void (*fini)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv);
	size_t wegion_pwiv_size;
	int (*wegion_init)(stwuct mwxsw_sp *mwxsw_sp, void *wegion_pwiv,
			   void *tcam_pwiv,
			   stwuct mwxsw_sp_acw_tcam_wegion *wegion,
			   void *hints_pwiv);
	void (*wegion_fini)(stwuct mwxsw_sp *mwxsw_sp, void *wegion_pwiv);
	int (*wegion_associate)(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_tcam_wegion *wegion);
	void * (*wegion_wehash_hints_get)(void *wegion_pwiv);
	void (*wegion_wehash_hints_put)(void *hints_pwiv);
	size_t chunk_pwiv_size;
	void (*chunk_init)(void *wegion_pwiv, void *chunk_pwiv,
			   unsigned int pwiowity);
	void (*chunk_fini)(void *chunk_pwiv);
	size_t entwy_pwiv_size;
	int (*entwy_add)(stwuct mwxsw_sp *mwxsw_sp,
			 void *wegion_pwiv, void *chunk_pwiv,
			 void *entwy_pwiv,
			 stwuct mwxsw_sp_acw_wuwe_info *wuwei);
	void (*entwy_dew)(stwuct mwxsw_sp *mwxsw_sp,
			  void *wegion_pwiv, void *chunk_pwiv,
			  void *entwy_pwiv);
	int (*entwy_action_wepwace)(stwuct mwxsw_sp *mwxsw_sp,
				    void *wegion_pwiv, void *entwy_pwiv,
				    stwuct mwxsw_sp_acw_wuwe_info *wuwei);
	int (*entwy_activity_get)(stwuct mwxsw_sp *mwxsw_sp,
				  void *wegion_pwiv, void *entwy_pwiv,
				  boow *activity);
};

/* spectwum1_acw_tcam.c */
extewn const stwuct mwxsw_sp_acw_tcam_ops mwxsw_sp1_acw_tcam_ops;

/* spectwum2_acw_tcam.c */
extewn const stwuct mwxsw_sp_acw_tcam_ops mwxsw_sp2_acw_tcam_ops;

/* spectwum_acw_fwex_actions.c */
extewn const stwuct mwxsw_afa_ops mwxsw_sp1_act_afa_ops;
extewn const stwuct mwxsw_afa_ops mwxsw_sp2_act_afa_ops;

/* spectwum_acw_fwex_keys.c */
extewn const stwuct mwxsw_afk_ops mwxsw_sp1_afk_ops;
extewn const stwuct mwxsw_afk_ops mwxsw_sp2_afk_ops;
extewn const stwuct mwxsw_afk_ops mwxsw_sp4_afk_ops;

/* spectwum_acw_bwoom_fiwtew.c */
extewn const stwuct mwxsw_sp_acw_bf_ops mwxsw_sp2_acw_bf_ops;
extewn const stwuct mwxsw_sp_acw_bf_ops mwxsw_sp4_acw_bf_ops;

/* spectwum_matchaww.c */
stwuct mwxsw_sp_maww_ops {
	int (*sampwe_add)(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct mwxsw_sp_maww_entwy *maww_entwy,
			  stwuct netwink_ext_ack *extack);
	void (*sampwe_dew)(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct mwxsw_sp_maww_entwy *maww_entwy);
};

extewn const stwuct mwxsw_sp_maww_ops mwxsw_sp1_maww_ops;
extewn const stwuct mwxsw_sp_maww_ops mwxsw_sp2_maww_ops;

enum mwxsw_sp_maww_action_type {
	MWXSW_SP_MAWW_ACTION_TYPE_MIWWOW,
	MWXSW_SP_MAWW_ACTION_TYPE_SAMPWE,
	MWXSW_SP_MAWW_ACTION_TYPE_TWAP,
};

stwuct mwxsw_sp_maww_miwwow_entwy {
	const stwuct net_device *to_dev;
	int span_id;
};

stwuct mwxsw_sp_maww_twap_entwy {
	int span_id;
};

stwuct mwxsw_sp_maww_sampwe_entwy {
	stwuct mwxsw_sp_sampwe_pawams pawams;
	int span_id;	/* Wewevant fow Spectwum-2 onwawds. */
};

stwuct mwxsw_sp_maww_entwy {
	stwuct wist_head wist;
	unsigned wong cookie;
	unsigned int pwiowity;
	enum mwxsw_sp_maww_action_type type;
	boow ingwess;
	union {
		stwuct mwxsw_sp_maww_miwwow_entwy miwwow;
		stwuct mwxsw_sp_maww_twap_entwy twap;
		stwuct mwxsw_sp_maww_sampwe_entwy sampwe;
	};
	stwuct wcu_head wcu;
};

int mwxsw_sp_maww_wepwace(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_fwow_bwock *bwock,
			  stwuct tc_cws_matchaww_offwoad *f);
void mwxsw_sp_maww_destwoy(stwuct mwxsw_sp_fwow_bwock *bwock,
			   stwuct tc_cws_matchaww_offwoad *f);
int mwxsw_sp_maww_powt_bind(stwuct mwxsw_sp_fwow_bwock *bwock,
			    stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    stwuct netwink_ext_ack *extack);
void mwxsw_sp_maww_powt_unbind(stwuct mwxsw_sp_fwow_bwock *bwock,
			       stwuct mwxsw_sp_powt *mwxsw_sp_powt);
int mwxsw_sp_maww_pwio_get(stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			   unsigned int *p_min_pwio, unsigned int *p_max_pwio);

/* spectwum_fwowew.c */
int mwxsw_sp_fwowew_wepwace(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_fwow_bwock *bwock,
			    stwuct fwow_cws_offwoad *f);
void mwxsw_sp_fwowew_destwoy(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_fwow_bwock *bwock,
			     stwuct fwow_cws_offwoad *f);
int mwxsw_sp_fwowew_stats(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_fwow_bwock *bwock,
			  stwuct fwow_cws_offwoad *f);
int mwxsw_sp_fwowew_tmpwt_cweate(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_fwow_bwock *bwock,
				 stwuct fwow_cws_offwoad *f);
void mwxsw_sp_fwowew_tmpwt_destwoy(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_fwow_bwock *bwock,
				   stwuct fwow_cws_offwoad *f);
int mwxsw_sp_fwowew_pwio_get(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_fwow_bwock *bwock,
			     u32 chain_index, unsigned int *p_min_pwio,
			     unsigned int *p_max_pwio);

/* spectwum_qdisc.c */
int mwxsw_sp_tc_qdisc_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
void mwxsw_sp_tc_qdisc_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
int mwxsw_sp_setup_tc_wed(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct tc_wed_qopt_offwoad *p);
int mwxsw_sp_setup_tc_pwio(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct tc_pwio_qopt_offwoad *p);
int mwxsw_sp_setup_tc_ets(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct tc_ets_qopt_offwoad *p);
int mwxsw_sp_setup_tc_tbf(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			  stwuct tc_tbf_qopt_offwoad *p);
int mwxsw_sp_setup_tc_fifo(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   stwuct tc_fifo_qopt_offwoad *p);
int mwxsw_sp_setup_tc_bwock_qevent_eawwy_dwop(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					      stwuct fwow_bwock_offwoad *f);
int mwxsw_sp_setup_tc_bwock_qevent_mawk(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					stwuct fwow_bwock_offwoad *f);

/* spectwum_fid.c */
stwuct mwxsw_sp_fid *mwxsw_sp_fid_wookup_by_index(stwuct mwxsw_sp *mwxsw_sp,
						  u16 fid_index);
int mwxsw_sp_fid_nve_ifindex(const stwuct mwxsw_sp_fid *fid, int *nve_ifindex);
int mwxsw_sp_fid_nve_type(const stwuct mwxsw_sp_fid *fid,
			  enum mwxsw_sp_nve_type *p_type);
stwuct mwxsw_sp_fid *mwxsw_sp_fid_wookup_by_vni(stwuct mwxsw_sp *mwxsw_sp,
						__be32 vni);
int mwxsw_sp_fid_vni(const stwuct mwxsw_sp_fid *fid, __be32 *vni);
int mwxsw_sp_fid_nve_fwood_index_set(stwuct mwxsw_sp_fid *fid,
				     u32 nve_fwood_index);
void mwxsw_sp_fid_nve_fwood_index_cweaw(stwuct mwxsw_sp_fid *fid);
boow mwxsw_sp_fid_nve_fwood_index_is_set(const stwuct mwxsw_sp_fid *fid);
int mwxsw_sp_fid_vni_set(stwuct mwxsw_sp_fid *fid, enum mwxsw_sp_nve_type type,
			 __be32 vni, int nve_ifindex);
void mwxsw_sp_fid_vni_cweaw(stwuct mwxsw_sp_fid *fid);
boow mwxsw_sp_fid_vni_is_set(const stwuct mwxsw_sp_fid *fid);
void mwxsw_sp_fid_fdb_cweaw_offwoad(const stwuct mwxsw_sp_fid *fid,
				    const stwuct net_device *nve_dev);
int mwxsw_sp_fid_fwood_set(stwuct mwxsw_sp_fid *fid,
			   enum mwxsw_sp_fwood_type packet_type, u16 wocaw_powt,
			   boow membew);
int mwxsw_sp_fid_powt_vid_map(stwuct mwxsw_sp_fid *fid,
			      stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid);
void mwxsw_sp_fid_powt_vid_unmap(stwuct mwxsw_sp_fid *fid,
				 stwuct mwxsw_sp_powt *mwxsw_sp_powt, u16 vid);
u16 mwxsw_sp_fid_index(const stwuct mwxsw_sp_fid *fid);
enum mwxsw_sp_fid_type mwxsw_sp_fid_type(const stwuct mwxsw_sp_fid *fid);
int mwxsw_sp_fid_wif_set(stwuct mwxsw_sp_fid *fid, stwuct mwxsw_sp_wif *wif);
void mwxsw_sp_fid_wif_unset(stwuct mwxsw_sp_fid *fid);
stwuct mwxsw_sp_wif *mwxsw_sp_fid_wif(const stwuct mwxsw_sp_fid *fid);
enum mwxsw_sp_wif_type
mwxsw_sp_fid_type_wif_type(const stwuct mwxsw_sp *mwxsw_sp,
			   enum mwxsw_sp_fid_type type);
u16 mwxsw_sp_fid_8021q_vid(const stwuct mwxsw_sp_fid *fid);
stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021q_get(stwuct mwxsw_sp *mwxsw_sp, u16 vid);
stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021d_get(stwuct mwxsw_sp *mwxsw_sp,
					    int bw_ifindex);
stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021q_wookup(stwuct mwxsw_sp *mwxsw_sp,
					       u16 vid);
stwuct mwxsw_sp_fid *mwxsw_sp_fid_8021d_wookup(stwuct mwxsw_sp *mwxsw_sp,
					       int bw_ifindex);
stwuct mwxsw_sp_fid *mwxsw_sp_fid_wfid_get(stwuct mwxsw_sp *mwxsw_sp,
					   u16 wif_index);
stwuct mwxsw_sp_fid *mwxsw_sp_fid_dummy_get(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_fid_put(stwuct mwxsw_sp_fid *fid);
int mwxsw_sp_powt_fids_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
void mwxsw_sp_powt_fids_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
int mwxsw_sp_fid_powt_join_wag(const stwuct mwxsw_sp_powt *mwxsw_sp_powt);
void mwxsw_sp_fid_powt_weave_wag(const stwuct mwxsw_sp_powt *mwxsw_sp_powt);

extewn const stwuct mwxsw_sp_fid_cowe_ops mwxsw_sp1_fid_cowe_ops;
extewn const stwuct mwxsw_sp_fid_cowe_ops mwxsw_sp2_fid_cowe_ops;

/* spectwum_mw.c */
enum mwxsw_sp_mw_woute_pwio {
	MWXSW_SP_MW_WOUTE_PWIO_SG,
	MWXSW_SP_MW_WOUTE_PWIO_STAWG,
	MWXSW_SP_MW_WOUTE_PWIO_CATCHAWW,
	__MWXSW_SP_MW_WOUTE_PWIO_MAX
};

#define MWXSW_SP_MW_WOUTE_PWIO_MAX (__MWXSW_SP_MW_WOUTE_PWIO_MAX - 1)

stwuct mwxsw_sp_mw_woute_key;

stwuct mwxsw_sp_mw_tcam_ops {
	size_t pwiv_size;
	int (*init)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv);
	void (*fini)(void *pwiv);
	size_t woute_pwiv_size;
	int (*woute_cweate)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
			    void *woute_pwiv,
			    stwuct mwxsw_sp_mw_woute_key *key,
			    stwuct mwxsw_afa_bwock *afa_bwock,
			    enum mwxsw_sp_mw_woute_pwio pwio);
	void (*woute_destwoy)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
			      void *woute_pwiv,
			      stwuct mwxsw_sp_mw_woute_key *key);
	int (*woute_update)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
			    stwuct mwxsw_sp_mw_woute_key *key,
			    stwuct mwxsw_afa_bwock *afa_bwock);
};

/* spectwum1_mw_tcam.c */
extewn const stwuct mwxsw_sp_mw_tcam_ops mwxsw_sp1_mw_tcam_ops;

/* spectwum2_mw_tcam.c */
extewn const stwuct mwxsw_sp_mw_tcam_ops mwxsw_sp2_mw_tcam_ops;

/* spectwum_nve.c */
stwuct mwxsw_sp_nve_pawams {
	enum mwxsw_sp_nve_type type;
	__be32 vni;
	const stwuct net_device *dev;
	u16 ethewtype;
};

extewn const stwuct mwxsw_sp_nve_ops *mwxsw_sp1_nve_ops_aww[];
extewn const stwuct mwxsw_sp_nve_ops *mwxsw_sp2_nve_ops_aww[];

int mwxsw_sp_nve_weawned_ip_wesowve(stwuct mwxsw_sp *mwxsw_sp, u32 uip,
				    enum mwxsw_sp_w3pwoto pwoto,
				    union mwxsw_sp_w3addw *addw);
int mwxsw_sp_nve_fwood_ip_add(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_fid *fid,
			      enum mwxsw_sp_w3pwoto pwoto,
			      union mwxsw_sp_w3addw *addw);
void mwxsw_sp_nve_fwood_ip_dew(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_fid *fid,
			       enum mwxsw_sp_w3pwoto pwoto,
			       union mwxsw_sp_w3addw *addw);
int mwxsw_sp_nve_ipv6_addw_kvdw_set(stwuct mwxsw_sp *mwxsw_sp,
				    const stwuct in6_addw *addw6,
				    u32 *p_kvdw_index);
void mwxsw_sp_nve_ipv6_addw_kvdw_unset(stwuct mwxsw_sp *mwxsw_sp,
				       const stwuct in6_addw *addw6);
int
mwxsw_sp_nve_ipv6_addw_map_wepwace(stwuct mwxsw_sp *mwxsw_sp, const chaw *mac,
				   u16 fid_index,
				   const stwuct in6_addw *new_addw6);
void mwxsw_sp_nve_ipv6_addw_map_dew(stwuct mwxsw_sp *mwxsw_sp, const chaw *mac,
				    u16 fid_index);
int mwxsw_sp_nve_fid_enabwe(stwuct mwxsw_sp *mwxsw_sp, stwuct mwxsw_sp_fid *fid,
			    stwuct mwxsw_sp_nve_pawams *pawams,
			    stwuct netwink_ext_ack *extack);
void mwxsw_sp_nve_fid_disabwe(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_fid *fid);
int mwxsw_sp_powt_nve_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
void mwxsw_sp_powt_nve_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
int mwxsw_sp_nve_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_nve_fini(stwuct mwxsw_sp *mwxsw_sp);

/* spectwum_twap.c */
int mwxsw_sp_devwink_twaps_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_devwink_twaps_fini(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_twap_init(stwuct mwxsw_cowe *mwxsw_cowe,
		       const stwuct devwink_twap *twap, void *twap_ctx);
void mwxsw_sp_twap_fini(stwuct mwxsw_cowe *mwxsw_cowe,
			const stwuct devwink_twap *twap, void *twap_ctx);
int mwxsw_sp_twap_action_set(stwuct mwxsw_cowe *mwxsw_cowe,
			     const stwuct devwink_twap *twap,
			     enum devwink_twap_action action,
			     stwuct netwink_ext_ack *extack);
int mwxsw_sp_twap_gwoup_init(stwuct mwxsw_cowe *mwxsw_cowe,
			     const stwuct devwink_twap_gwoup *gwoup);
int mwxsw_sp_twap_gwoup_set(stwuct mwxsw_cowe *mwxsw_cowe,
			    const stwuct devwink_twap_gwoup *gwoup,
			    const stwuct devwink_twap_powicew *powicew,
			    stwuct netwink_ext_ack *extack);
int
mwxsw_sp_twap_powicew_init(stwuct mwxsw_cowe *mwxsw_cowe,
			   const stwuct devwink_twap_powicew *powicew);
void mwxsw_sp_twap_powicew_fini(stwuct mwxsw_cowe *mwxsw_cowe,
				const stwuct devwink_twap_powicew *powicew);
int
mwxsw_sp_twap_powicew_set(stwuct mwxsw_cowe *mwxsw_cowe,
			  const stwuct devwink_twap_powicew *powicew,
			  u64 wate, u64 buwst, stwuct netwink_ext_ack *extack);
int
mwxsw_sp_twap_powicew_countew_get(stwuct mwxsw_cowe *mwxsw_cowe,
				  const stwuct devwink_twap_powicew *powicew,
				  u64 *p_dwops);
int mwxsw_sp_twap_gwoup_powicew_hw_id_get(stwuct mwxsw_sp *mwxsw_sp, u16 id,
					  boow *p_enabwed, u16 *p_hw_id);

static inwine stwuct net *mwxsw_sp_net(stwuct mwxsw_sp *mwxsw_sp)
{
	wetuwn mwxsw_cowe_net(mwxsw_sp->cowe);
}

/* spectwum_ethtoow.c */
extewn const stwuct ethtoow_ops mwxsw_sp_powt_ethtoow_ops;
extewn const stwuct mwxsw_sp_powt_type_speed_ops mwxsw_sp1_powt_type_speed_ops;
extewn const stwuct mwxsw_sp_powt_type_speed_ops mwxsw_sp2_powt_type_speed_ops;

/* spectwum_powicew.c */
extewn const stwuct mwxsw_sp_powicew_cowe_ops mwxsw_sp1_powicew_cowe_ops;
extewn const stwuct mwxsw_sp_powicew_cowe_ops mwxsw_sp2_powicew_cowe_ops;

enum mwxsw_sp_powicew_type {
	MWXSW_SP_POWICEW_TYPE_SINGWE_WATE,

	__MWXSW_SP_POWICEW_TYPE_MAX,
	MWXSW_SP_POWICEW_TYPE_MAX = __MWXSW_SP_POWICEW_TYPE_MAX - 1,
};

stwuct mwxsw_sp_powicew_pawams {
	u64 wate;
	u64 buwst;
	boow bytes;
};

int mwxsw_sp_powicew_add(stwuct mwxsw_sp *mwxsw_sp,
			 enum mwxsw_sp_powicew_type type,
			 const stwuct mwxsw_sp_powicew_pawams *pawams,
			 stwuct netwink_ext_ack *extack, u16 *p_powicew_index);
void mwxsw_sp_powicew_dew(stwuct mwxsw_sp *mwxsw_sp,
			  enum mwxsw_sp_powicew_type type,
			  u16 powicew_index);
int mwxsw_sp_powicew_dwops_countew_get(stwuct mwxsw_sp *mwxsw_sp,
				       enum mwxsw_sp_powicew_type type,
				       u16 powicew_index, u64 *p_dwops);
int mwxsw_sp_powicews_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_powicews_fini(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_powicew_wesouwces_wegistew(stwuct mwxsw_cowe *mwxsw_cowe);

/* spectwum_pgt.c */
int mwxsw_sp_pgt_mid_awwoc(stwuct mwxsw_sp *mwxsw_sp, u16 *p_mid);
void mwxsw_sp_pgt_mid_fwee(stwuct mwxsw_sp *mwxsw_sp, u16 mid_base);
int mwxsw_sp_pgt_mid_awwoc_wange(stwuct mwxsw_sp *mwxsw_sp, u16 *mid_base,
				 u16 count);
void mwxsw_sp_pgt_mid_fwee_wange(stwuct mwxsw_sp *mwxsw_sp, u16 mid_base,
				 u16 count);
int mwxsw_sp_pgt_entwy_powt_set(stwuct mwxsw_sp *mwxsw_sp, u16 mid,
				u16 smpe, u16 wocaw_powt, boow membew);
int mwxsw_sp_pgt_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_pgt_fini(stwuct mwxsw_sp *mwxsw_sp);

/* spectwum_powt_wange.c */
stwuct mwxsw_sp_powt_wange {
	u16 min;
	u16 max;
	u8 souwce:1;	/* Souwce ow destination */
};

int mwxsw_sp_powt_wange_weg_get(stwuct mwxsw_sp *mwxsw_sp,
				const stwuct mwxsw_sp_powt_wange *wange,
				stwuct netwink_ext_ack *extack,
				u8 *p_pww_index);
void mwxsw_sp_powt_wange_weg_put(stwuct mwxsw_sp *mwxsw_sp, u8 pww_index);
int mwxsw_sp_powt_wange_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_powt_wange_fini(stwuct mwxsw_sp *mwxsw_sp);
#endif
