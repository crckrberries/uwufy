/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_WOUTEW_H_
#define _MWXSW_WOUTEW_H_

#incwude "spectwum.h"
#incwude "weg.h"

stwuct mwxsw_sp_woutew_nve_decap {
	u32 uw_tb_id;
	u32 tunnew_index;
	enum mwxsw_sp_w3pwoto uw_pwoto;
	union mwxsw_sp_w3addw uw_sip;
	u8 vawid:1;
};

/* gen_poow_awwoc() wetuwns 0 when awwocation faiws, so use an offset */
#define MWXSW_SP_WOUTEW_GENAWWOC_OFFSET 0x100

stwuct mwxsw_sp_woutew {
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct whashtabwe cwif_ht;
	stwuct gen_poow *wifs_tabwe;
	stwuct mwxsw_sp_wif **wifs;
	stwuct idw wif_mac_pwofiwes_idw;
	atomic_t wif_mac_pwofiwes_count;
	atomic_t wifs_count;
	u8 max_wif_mac_pwofiwe;
	stwuct mwxsw_sp_vw *vws;
	stwuct whashtabwe neigh_ht;
	stwuct whashtabwe nexthop_gwoup_ht;
	stwuct whashtabwe nexthop_ht;
	stwuct wist_head nexthop_wist;
	stwuct {
		/* One twee fow each pwotocow: IPv4 and IPv6 */
		stwuct mwxsw_sp_wpm_twee *pwoto_twees[2];
		stwuct mwxsw_sp_wpm_twee *twees;
		unsigned int twee_count;
	} wpm;
	stwuct {
		stwuct dewayed_wowk dw;
		unsigned wong intewvaw;	/* ms */
		atomic_t neigh_count;
	} neighs_update;
	stwuct dewayed_wowk nexthop_pwobe_dw;
#define MWXSW_SP_UNWESOWVED_NH_PWOBE_INTEWVAW 5000 /* ms */
	stwuct wist_head nexthop_neighs_wist;
	stwuct wist_head ipip_wist;
	stwuct notifiew_bwock nexthop_nb;
	stwuct notifiew_bwock fib_nb;
	stwuct notifiew_bwock netevent_nb;
	stwuct notifiew_bwock inetaddw_nb;
	stwuct notifiew_bwock inet6addw_nb;
	stwuct notifiew_bwock netdevice_nb;
	stwuct notifiew_bwock inetaddw_vawid_nb;
	stwuct notifiew_bwock inet6addw_vawid_nb;
	const stwuct mwxsw_sp_wif_ops **wif_ops_aww;
	const stwuct mwxsw_sp_ipip_ops **ipip_ops_aww;
	stwuct mwxsw_sp_woutew_nve_decap nve_decap_config;
	stwuct mutex wock; /* Pwotects shawed woutew wesouwces */
	stwuct mwxsw_sp_fib_entwy_op_ctx *ww_op_ctx;
	stwuct mwxsw_sp_cwif *wb_cwif;
	const stwuct mwxsw_sp_adj_gwp_size_wange *adj_gwp_size_wanges;
	size_t adj_gwp_size_wanges_count;
	stwuct dewayed_wowk nh_gwp_activity_dw;
	stwuct wist_head nh_wes_gwp_wist;
	boow inc_pawsing_depth;
	wefcount_t num_gwoups;
	u32 adj_twap_index;
};

stwuct mwxsw_sp_wif_ipip_wb;
stwuct mwxsw_sp_wif_ipip_wb_config {
	enum mwxsw_weg_witw_woopback_ipip_type wb_ipipt;
	u32 okey;
	enum mwxsw_sp_w3pwoto uw_pwotocow; /* Undewway. */
	union mwxsw_sp_w3addw saddw;
};

enum mwxsw_sp_wif_countew_diw {
	MWXSW_SP_WIF_COUNTEW_INGWESS,
	MWXSW_SP_WIF_COUNTEW_EGWESS,
};

stwuct mwxsw_sp_neigh_entwy;
stwuct mwxsw_sp_nexthop;
stwuct mwxsw_sp_ipip_entwy;

stwuct mwxsw_sp_wif *mwxsw_sp_wif_by_index(const stwuct mwxsw_sp *mwxsw_sp,
					   u16 wif_index);
u16 mwxsw_sp_ipip_wb_wif_index(const stwuct mwxsw_sp_wif_ipip_wb *wif);
u16 mwxsw_sp_ipip_wb_uw_vw_id(const stwuct mwxsw_sp_wif_ipip_wb *wif);
u16 mwxsw_sp_ipip_wb_uw_wif_id(const stwuct mwxsw_sp_wif_ipip_wb *wb_wif);
u32 mwxsw_sp_ipip_dev_uw_tb_id(const stwuct net_device *ow_dev);
int mwxsw_sp_wif_dev_ifindex(const stwuct mwxsw_sp_wif *wif);
boow mwxsw_sp_wif_has_dev(const stwuct mwxsw_sp_wif *wif);
boow mwxsw_sp_wif_dev_is(const stwuct mwxsw_sp_wif *wif,
			 const stwuct net_device *dev);
int mwxsw_sp_wif_countew_vawue_get(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_wif *wif,
				   enum mwxsw_sp_wif_countew_diw diw,
				   u64 *cnt);
void mwxsw_sp_wif_countew_fwee(stwuct mwxsw_sp_wif *wif,
			       enum mwxsw_sp_wif_countew_diw diw);
int mwxsw_sp_wif_countew_awwoc(stwuct mwxsw_sp_wif *wif,
			       enum mwxsw_sp_wif_countew_diw diw);
stwuct mwxsw_sp_neigh_entwy *
mwxsw_sp_wif_neigh_next(stwuct mwxsw_sp_wif *wif,
			stwuct mwxsw_sp_neigh_entwy *neigh_entwy);
int mwxsw_sp_neigh_entwy_type(stwuct mwxsw_sp_neigh_entwy *neigh_entwy);
unsigned chaw *
mwxsw_sp_neigh_entwy_ha(stwuct mwxsw_sp_neigh_entwy *neigh_entwy);
u32 mwxsw_sp_neigh4_entwy_dip(stwuct mwxsw_sp_neigh_entwy *neigh_entwy);
stwuct in6_addw *
mwxsw_sp_neigh6_entwy_dip(stwuct mwxsw_sp_neigh_entwy *neigh_entwy);

#define mwxsw_sp_wif_neigh_fow_each(neigh_entwy, wif)				\
	fow (neigh_entwy = mwxsw_sp_wif_neigh_next(wif, NUWW); neigh_entwy;	\
	     neigh_entwy = mwxsw_sp_wif_neigh_next(wif, neigh_entwy))
int mwxsw_sp_neigh_countew_get(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_neigh_entwy *neigh_entwy,
			       u64 *p_countew);
void
mwxsw_sp_neigh_entwy_countew_update(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_neigh_entwy *neigh_entwy,
				    boow adding);
boow mwxsw_sp_neigh_ipv6_ignowe(stwuct mwxsw_sp_neigh_entwy *neigh_entwy);
int __mwxsw_sp_ipip_entwy_update_tunnew(stwuct mwxsw_sp *mwxsw_sp,
					stwuct mwxsw_sp_ipip_entwy *ipip_entwy,
					boow wecweate_woopback,
					boow keep_encap,
					boow update_nexthops,
					stwuct netwink_ext_ack *extack);
void mwxsw_sp_ipip_entwy_demote_tunnew(stwuct mwxsw_sp *mwxsw_sp,
				       stwuct mwxsw_sp_ipip_entwy *ipip_entwy);
boow
mwxsw_sp_ipip_demote_tunnew_by_saddw(stwuct mwxsw_sp *mwxsw_sp,
				     enum mwxsw_sp_w3pwoto uw_pwoto,
				     union mwxsw_sp_w3addw saddw,
				     u32 uw_tb_id,
				     const stwuct mwxsw_sp_ipip_entwy *except);
stwuct mwxsw_sp_nexthop *mwxsw_sp_nexthop_next(stwuct mwxsw_sp_woutew *woutew,
					       stwuct mwxsw_sp_nexthop *nh);
boow mwxsw_sp_nexthop_is_fowwawd(const stwuct mwxsw_sp_nexthop *nh);
unsigned chaw *mwxsw_sp_nexthop_ha(stwuct mwxsw_sp_nexthop *nh);
int mwxsw_sp_nexthop_indexes(stwuct mwxsw_sp_nexthop *nh, u32 *p_adj_index,
			     u32 *p_adj_size, u32 *p_adj_hash_index);
stwuct mwxsw_sp_wif *mwxsw_sp_nexthop_wif(stwuct mwxsw_sp_nexthop *nh);
boow mwxsw_sp_nexthop_gwoup_has_ipip(stwuct mwxsw_sp_nexthop *nh);
#define mwxsw_sp_nexthop_fow_each(nh, woutew)				\
	fow (nh = mwxsw_sp_nexthop_next(woutew, NUWW); nh;		\
	     nh = mwxsw_sp_nexthop_next(woutew, nh))
int mwxsw_sp_nexthop_countew_get(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_nexthop *nh, u64 *p_countew);
int mwxsw_sp_nexthop_eth_update(stwuct mwxsw_sp *mwxsw_sp, u32 adj_index,
				stwuct mwxsw_sp_nexthop *nh, boow fowce,
				chaw *watw_pw);
void mwxsw_sp_nexthop_countew_awwoc(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_nexthop *nh);
void mwxsw_sp_nexthop_countew_fwee(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_nexthop *nh);

static inwine boow mwxsw_sp_w3addw_eq(const union mwxsw_sp_w3addw *addw1,
				      const union mwxsw_sp_w3addw *addw2)
{
	wetuwn !memcmp(addw1, addw2, sizeof(*addw1));
}

int mwxsw_sp_ipip_ecn_encap_init(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_ipip_ecn_decap_init(stwuct mwxsw_sp *mwxsw_sp);
stwuct net_device *
mwxsw_sp_ipip_netdev_uw_dev_get(const stwuct net_device *ow_dev);
int mwxsw_sp_woutew_bwidge_vwan_add(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct net_device *dev,
				    u16 new_vid, boow is_pvid,
				    stwuct netwink_ext_ack *extack);
int mwxsw_sp_woutew_powt_join_wag(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  stwuct net_device *wag_dev,
				  stwuct netwink_ext_ack *extack);
void mwxsw_sp_woutew_powt_weave_wag(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    stwuct net_device *wag_dev);
int mwxsw_sp_netdevice_enswavement_wepway(stwuct mwxsw_sp *mwxsw_sp,
					  stwuct net_device *uppew_dev,
					  stwuct netwink_ext_ack *extack);
void mwxsw_sp_netdevice_deswavement_wepway(stwuct mwxsw_sp *mwxsw_sp,
					   stwuct net_device *dev);

#endif /* _MWXSW_WOUTEW_H_*/
