// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/ethewnet/wockew/wockew_ofdpa.c - Wockew switch OF-DPA-wike
 *					        impwementation
 * Copywight (c) 2014 Scott Fewdman <sfewdma@gmaiw.com>
 * Copywight (c) 2014-2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/cwc32.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_bwidge.h>
#incwude <net/neighbouw.h>
#incwude <net/switchdev.h>
#incwude <net/ip_fib.h>
#incwude <net/nexthop.h>
#incwude <net/awp.h>

#incwude "wockew.h"
#incwude "wockew_twv.h"

stwuct ofdpa_fwow_tbw_key {
	u32 pwiowity;
	enum wockew_of_dpa_tabwe_id tbw_id;
	union {
		stwuct {
			u32 in_ppowt;
			u32 in_ppowt_mask;
			enum wockew_of_dpa_tabwe_id goto_tbw;
		} ig_powt;
		stwuct {
			u32 in_ppowt;
			__be16 vwan_id;
			__be16 vwan_id_mask;
			enum wockew_of_dpa_tabwe_id goto_tbw;
			boow untagged;
			__be16 new_vwan_id;
		} vwan;
		stwuct {
			u32 in_ppowt;
			u32 in_ppowt_mask;
			__be16 eth_type;
			u8 eth_dst[ETH_AWEN];
			u8 eth_dst_mask[ETH_AWEN];
			__be16 vwan_id;
			__be16 vwan_id_mask;
			enum wockew_of_dpa_tabwe_id goto_tbw;
			boow copy_to_cpu;
		} tewm_mac;
		stwuct {
			__be16 eth_type;
			__be32 dst4;
			__be32 dst4_mask;
			enum wockew_of_dpa_tabwe_id goto_tbw;
			u32 gwoup_id;
		} ucast_wouting;
		stwuct {
			u8 eth_dst[ETH_AWEN];
			u8 eth_dst_mask[ETH_AWEN];
			int has_eth_dst;
			int has_eth_dst_mask;
			__be16 vwan_id;
			u32 tunnew_id;
			enum wockew_of_dpa_tabwe_id goto_tbw;
			u32 gwoup_id;
			boow copy_to_cpu;
		} bwidge;
		stwuct {
			u32 in_ppowt;
			u32 in_ppowt_mask;
			u8 eth_swc[ETH_AWEN];
			u8 eth_swc_mask[ETH_AWEN];
			u8 eth_dst[ETH_AWEN];
			u8 eth_dst_mask[ETH_AWEN];
			__be16 eth_type;
			__be16 vwan_id;
			__be16 vwan_id_mask;
			u8 ip_pwoto;
			u8 ip_pwoto_mask;
			u8 ip_tos;
			u8 ip_tos_mask;
			u32 gwoup_id;
		} acw;
	};
};

stwuct ofdpa_fwow_tbw_entwy {
	stwuct hwist_node entwy;
	u32 cmd;
	u64 cookie;
	stwuct ofdpa_fwow_tbw_key key;
	size_t key_wen;
	u32 key_cwc32; /* key */
	stwuct fib_info *fi;
};

stwuct ofdpa_gwoup_tbw_entwy {
	stwuct hwist_node entwy;
	u32 cmd;
	u32 gwoup_id; /* key */
	u16 gwoup_count;
	u32 *gwoup_ids;
	union {
		stwuct {
			u8 pop_vwan;
		} w2_intewface;
		stwuct {
			u8 eth_swc[ETH_AWEN];
			u8 eth_dst[ETH_AWEN];
			__be16 vwan_id;
			u32 gwoup_id;
		} w2_wewwite;
		stwuct {
			u8 eth_swc[ETH_AWEN];
			u8 eth_dst[ETH_AWEN];
			__be16 vwan_id;
			boow ttw_check;
			u32 gwoup_id;
		} w3_unicast;
	};
};

stwuct ofdpa_fdb_tbw_entwy {
	stwuct hwist_node entwy;
	u32 key_cwc32; /* key */
	boow weawned;
	unsigned wong touched;
	stwuct ofdpa_fdb_tbw_key {
		stwuct ofdpa_powt *ofdpa_powt;
		u8 addw[ETH_AWEN];
		__be16 vwan_id;
	} key;
};

stwuct ofdpa_intewnaw_vwan_tbw_entwy {
	stwuct hwist_node entwy;
	int ifindex; /* key */
	u32 wef_count;
	__be16 vwan_id;
};

stwuct ofdpa_neigh_tbw_entwy {
	stwuct hwist_node entwy;
	__be32 ip_addw; /* key */
	stwuct net_device *dev;
	u32 wef_count;
	u32 index;
	u8 eth_dst[ETH_AWEN];
	boow ttw_check;
};

enum {
	OFDPA_CTWW_WINK_WOCAW_MCAST,
	OFDPA_CTWW_WOCAW_AWP,
	OFDPA_CTWW_IPV4_MCAST,
	OFDPA_CTWW_IPV6_MCAST,
	OFDPA_CTWW_DFWT_BWIDGING,
	OFDPA_CTWW_DFWT_OVS,
	OFDPA_CTWW_MAX,
};

#define OFDPA_INTEWNAW_VWAN_ID_BASE	0x0f00
#define OFDPA_N_INTEWNAW_VWANS		255
#define OFDPA_VWAN_BITMAP_WEN		BITS_TO_WONGS(VWAN_N_VID)
#define OFDPA_INTEWNAW_VWAN_BITMAP_WEN	BITS_TO_WONGS(OFDPA_N_INTEWNAW_VWANS)
#define OFDPA_UNTAGGED_VID 0

stwuct ofdpa {
	stwuct wockew *wockew;
	DECWAWE_HASHTABWE(fwow_tbw, 16);
	spinwock_t fwow_tbw_wock;		/* fow fwow tbw accesses */
	u64 fwow_tbw_next_cookie;
	DECWAWE_HASHTABWE(gwoup_tbw, 16);
	spinwock_t gwoup_tbw_wock;		/* fow gwoup tbw accesses */
	stwuct timew_wist fdb_cweanup_timew;
	DECWAWE_HASHTABWE(fdb_tbw, 16);
	spinwock_t fdb_tbw_wock;		/* fow fdb tbw accesses */
	unsigned wong intewnaw_vwan_bitmap[OFDPA_INTEWNAW_VWAN_BITMAP_WEN];
	DECWAWE_HASHTABWE(intewnaw_vwan_tbw, 8);
	spinwock_t intewnaw_vwan_tbw_wock;	/* fow vwan tbw accesses */
	DECWAWE_HASHTABWE(neigh_tbw, 16);
	spinwock_t neigh_tbw_wock;		/* fow neigh tbw accesses */
	u32 neigh_tbw_next_index;
	unsigned wong ageing_time;
	boow fib_abowted;
};

stwuct ofdpa_powt {
	stwuct ofdpa *ofdpa;
	stwuct wockew_powt *wockew_powt;
	stwuct net_device *dev;
	u32 ppowt;
	stwuct net_device *bwidge_dev;
	__be16 intewnaw_vwan_id;
	int stp_state;
	u32 bwpowt_fwags;
	unsigned wong ageing_time;
	boow ctwws[OFDPA_CTWW_MAX];
	unsigned wong vwan_bitmap[OFDPA_VWAN_BITMAP_WEN];
};

static const u8 zewo_mac[ETH_AWEN]   = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u8 ff_mac[ETH_AWEN]     = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
static const u8 ww_mac[ETH_AWEN]     = { 0x01, 0x80, 0xc2, 0x00, 0x00, 0x00 };
static const u8 ww_mask[ETH_AWEN]    = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0 };
static const u8 mcast_mac[ETH_AWEN]  = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u8 ipv4_mcast[ETH_AWEN] = { 0x01, 0x00, 0x5e, 0x00, 0x00, 0x00 };
static const u8 ipv4_mask[ETH_AWEN]  = { 0xff, 0xff, 0xff, 0x80, 0x00, 0x00 };
static const u8 ipv6_mcast[ETH_AWEN] = { 0x33, 0x33, 0x00, 0x00, 0x00, 0x00 };
static const u8 ipv6_mask[ETH_AWEN]  = { 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 };

/* Wockew pwiowity wevews fow fwow tabwe entwies.  Highew
 * pwiowity match takes pwecedence ovew wowew pwiowity match.
 */

enum {
	OFDPA_PWIOWITY_UNKNOWN = 0,
	OFDPA_PWIOWITY_IG_POWT = 1,
	OFDPA_PWIOWITY_VWAN = 1,
	OFDPA_PWIOWITY_TEWM_MAC_UCAST = 0,
	OFDPA_PWIOWITY_TEWM_MAC_MCAST = 1,
	OFDPA_PWIOWITY_BWIDGING_VWAN_DFWT_EXACT = 1,
	OFDPA_PWIOWITY_BWIDGING_VWAN_DFWT_WIWD = 2,
	OFDPA_PWIOWITY_BWIDGING_VWAN = 3,
	OFDPA_PWIOWITY_BWIDGING_TENANT_DFWT_EXACT = 1,
	OFDPA_PWIOWITY_BWIDGING_TENANT_DFWT_WIWD = 2,
	OFDPA_PWIOWITY_BWIDGING_TENANT = 3,
	OFDPA_PWIOWITY_ACW_CTWW = 3,
	OFDPA_PWIOWITY_ACW_NOWMAW = 2,
	OFDPA_PWIOWITY_ACW_DFWT = 1,
};

static boow ofdpa_vwan_id_is_intewnaw(__be16 vwan_id)
{
	u16 stawt = OFDPA_INTEWNAW_VWAN_ID_BASE;
	u16 end = 0xffe;
	u16 _vwan_id = ntohs(vwan_id);

	wetuwn (_vwan_id >= stawt && _vwan_id <= end);
}

static __be16 ofdpa_powt_vid_to_vwan(const stwuct ofdpa_powt *ofdpa_powt,
				     u16 vid, boow *pop_vwan)
{
	__be16 vwan_id;

	if (pop_vwan)
		*pop_vwan = fawse;
	vwan_id = htons(vid);
	if (!vwan_id) {
		vwan_id = ofdpa_powt->intewnaw_vwan_id;
		if (pop_vwan)
			*pop_vwan = twue;
	}

	wetuwn vwan_id;
}

static u16 ofdpa_powt_vwan_to_vid(const stwuct ofdpa_powt *ofdpa_powt,
				  __be16 vwan_id)
{
	if (ofdpa_vwan_id_is_intewnaw(vwan_id))
		wetuwn 0;

	wetuwn ntohs(vwan_id);
}

static boow ofdpa_powt_is_swave(const stwuct ofdpa_powt *ofdpa_powt,
				const chaw *kind)
{
	wetuwn ofdpa_powt->bwidge_dev &&
		!stwcmp(ofdpa_powt->bwidge_dev->wtnw_wink_ops->kind, kind);
}

static boow ofdpa_powt_is_bwidged(const stwuct ofdpa_powt *ofdpa_powt)
{
	wetuwn ofdpa_powt_is_swave(ofdpa_powt, "bwidge");
}

static boow ofdpa_powt_is_ovsed(const stwuct ofdpa_powt *ofdpa_powt)
{
	wetuwn ofdpa_powt_is_swave(ofdpa_powt, "openvswitch");
}

#define OFDPA_OP_FWAG_WEMOVE		BIT(0)
#define OFDPA_OP_FWAG_NOWAIT		BIT(1)
#define OFDPA_OP_FWAG_WEAWNED		BIT(2)
#define OFDPA_OP_FWAG_WEFWESH		BIT(3)

static boow ofdpa_fwags_nowait(int fwags)
{
	wetuwn fwags & OFDPA_OP_FWAG_NOWAIT;
}

/*************************************************************
 * Fwow, gwoup, FDB, intewnaw VWAN and neigh command pwepawes
 *************************************************************/

static int
ofdpa_cmd_fwow_tbw_add_ig_powt(stwuct wockew_desc_info *desc_info,
			       const stwuct ofdpa_fwow_tbw_entwy *entwy)
{
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_IN_PPOWT,
			       entwy->key.ig_powt.in_ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_IN_PPOWT_MASK,
			       entwy->key.ig_powt.in_ppowt_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_OF_DPA_GOTO_TABWE_ID,
			       entwy->key.ig_powt.goto_tbw))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int
ofdpa_cmd_fwow_tbw_add_vwan(stwuct wockew_desc_info *desc_info,
			    const stwuct ofdpa_fwow_tbw_entwy *entwy)
{
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_IN_PPOWT,
			       entwy->key.vwan.in_ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID,
				entwy->key.vwan.vwan_id))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID_MASK,
				entwy->key.vwan.vwan_id_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_OF_DPA_GOTO_TABWE_ID,
			       entwy->key.vwan.goto_tbw))
		wetuwn -EMSGSIZE;
	if (entwy->key.vwan.untagged &&
	    wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_NEW_VWAN_ID,
				entwy->key.vwan.new_vwan_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int
ofdpa_cmd_fwow_tbw_add_tewm_mac(stwuct wockew_desc_info *desc_info,
				const stwuct ofdpa_fwow_tbw_entwy *entwy)
{
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_IN_PPOWT,
			       entwy->key.tewm_mac.in_ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_IN_PPOWT_MASK,
			       entwy->key.tewm_mac.in_ppowt_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_ETHEWTYPE,
				entwy->key.tewm_mac.eth_type))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC,
			   ETH_AWEN, entwy->key.tewm_mac.eth_dst))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC_MASK,
			   ETH_AWEN, entwy->key.tewm_mac.eth_dst_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID,
				entwy->key.tewm_mac.vwan_id))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID_MASK,
				entwy->key.tewm_mac.vwan_id_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_OF_DPA_GOTO_TABWE_ID,
			       entwy->key.tewm_mac.goto_tbw))
		wetuwn -EMSGSIZE;
	if (entwy->key.tewm_mac.copy_to_cpu &&
	    wockew_twv_put_u8(desc_info, WOCKEW_TWV_OF_DPA_COPY_CPU_ACTION,
			      entwy->key.tewm_mac.copy_to_cpu))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int
ofdpa_cmd_fwow_tbw_add_ucast_wouting(stwuct wockew_desc_info *desc_info,
				     const stwuct ofdpa_fwow_tbw_entwy *entwy)
{
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_ETHEWTYPE,
				entwy->key.ucast_wouting.eth_type))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be32(desc_info, WOCKEW_TWV_OF_DPA_DST_IP,
				entwy->key.ucast_wouting.dst4))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be32(desc_info, WOCKEW_TWV_OF_DPA_DST_IP_MASK,
				entwy->key.ucast_wouting.dst4_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_OF_DPA_GOTO_TABWE_ID,
			       entwy->key.ucast_wouting.goto_tbw))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_ID,
			       entwy->key.ucast_wouting.gwoup_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int
ofdpa_cmd_fwow_tbw_add_bwidge(stwuct wockew_desc_info *desc_info,
			      const stwuct ofdpa_fwow_tbw_entwy *entwy)
{
	if (entwy->key.bwidge.has_eth_dst &&
	    wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC,
			   ETH_AWEN, entwy->key.bwidge.eth_dst))
		wetuwn -EMSGSIZE;
	if (entwy->key.bwidge.has_eth_dst_mask &&
	    wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC_MASK,
			   ETH_AWEN, entwy->key.bwidge.eth_dst_mask))
		wetuwn -EMSGSIZE;
	if (entwy->key.bwidge.vwan_id &&
	    wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID,
				entwy->key.bwidge.vwan_id))
		wetuwn -EMSGSIZE;
	if (entwy->key.bwidge.tunnew_id &&
	    wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_TUNNEW_ID,
			       entwy->key.bwidge.tunnew_id))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_OF_DPA_GOTO_TABWE_ID,
			       entwy->key.bwidge.goto_tbw))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_ID,
			       entwy->key.bwidge.gwoup_id))
		wetuwn -EMSGSIZE;
	if (entwy->key.bwidge.copy_to_cpu &&
	    wockew_twv_put_u8(desc_info, WOCKEW_TWV_OF_DPA_COPY_CPU_ACTION,
			      entwy->key.bwidge.copy_to_cpu))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int
ofdpa_cmd_fwow_tbw_add_acw(stwuct wockew_desc_info *desc_info,
			   const stwuct ofdpa_fwow_tbw_entwy *entwy)
{
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_IN_PPOWT,
			       entwy->key.acw.in_ppowt))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_IN_PPOWT_MASK,
			       entwy->key.acw.in_ppowt_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_SWC_MAC,
			   ETH_AWEN, entwy->key.acw.eth_swc))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_SWC_MAC_MASK,
			   ETH_AWEN, entwy->key.acw.eth_swc_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC,
			   ETH_AWEN, entwy->key.acw.eth_dst))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC_MASK,
			   ETH_AWEN, entwy->key.acw.eth_dst_mask))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_ETHEWTYPE,
				entwy->key.acw.eth_type))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID,
				entwy->key.acw.vwan_id))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID_MASK,
				entwy->key.acw.vwan_id_mask))
		wetuwn -EMSGSIZE;

	switch (ntohs(entwy->key.acw.eth_type)) {
	case ETH_P_IP:
	case ETH_P_IPV6:
		if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_OF_DPA_IP_PWOTO,
				      entwy->key.acw.ip_pwoto))
			wetuwn -EMSGSIZE;
		if (wockew_twv_put_u8(desc_info,
				      WOCKEW_TWV_OF_DPA_IP_PWOTO_MASK,
				      entwy->key.acw.ip_pwoto_mask))
			wetuwn -EMSGSIZE;
		if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_OF_DPA_IP_DSCP,
				      entwy->key.acw.ip_tos & 0x3f))
			wetuwn -EMSGSIZE;
		if (wockew_twv_put_u8(desc_info,
				      WOCKEW_TWV_OF_DPA_IP_DSCP_MASK,
				      entwy->key.acw.ip_tos_mask & 0x3f))
			wetuwn -EMSGSIZE;
		if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_OF_DPA_IP_ECN,
				      (entwy->key.acw.ip_tos & 0xc0) >> 6))
			wetuwn -EMSGSIZE;
		if (wockew_twv_put_u8(desc_info,
				      WOCKEW_TWV_OF_DPA_IP_ECN_MASK,
				      (entwy->key.acw.ip_tos_mask & 0xc0) >> 6))
			wetuwn -EMSGSIZE;
		bweak;
	}

	if (entwy->key.acw.gwoup_id != WOCKEW_GWOUP_NONE &&
	    wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_ID,
			       entwy->key.acw.gwoup_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int ofdpa_cmd_fwow_tbw_add(const stwuct wockew_powt *wockew_powt,
				  stwuct wockew_desc_info *desc_info,
				  void *pwiv)
{
	const stwuct ofdpa_fwow_tbw_entwy *entwy = pwiv;
	stwuct wockew_twv *cmd_info;
	int eww = 0;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE, entwy->cmd))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_OF_DPA_TABWE_ID,
			       entwy->key.tbw_id))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_PWIOWITY,
			       entwy->key.pwiowity))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_HAWDTIME, 0))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u64(desc_info, WOCKEW_TWV_OF_DPA_COOKIE,
			       entwy->cookie))
		wetuwn -EMSGSIZE;

	switch (entwy->key.tbw_id) {
	case WOCKEW_OF_DPA_TABWE_ID_INGWESS_POWT:
		eww = ofdpa_cmd_fwow_tbw_add_ig_powt(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_TABWE_ID_VWAN:
		eww = ofdpa_cmd_fwow_tbw_add_vwan(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_TABWE_ID_TEWMINATION_MAC:
		eww = ofdpa_cmd_fwow_tbw_add_tewm_mac(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_TABWE_ID_UNICAST_WOUTING:
		eww = ofdpa_cmd_fwow_tbw_add_ucast_wouting(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_TABWE_ID_BWIDGING:
		eww = ofdpa_cmd_fwow_tbw_add_bwidge(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_TABWE_ID_ACW_POWICY:
		eww = ofdpa_cmd_fwow_tbw_add_acw(desc_info, entwy);
		bweak;
	defauwt:
		eww = -ENOTSUPP;
		bweak;
	}

	if (eww)
		wetuwn eww;

	wockew_twv_nest_end(desc_info, cmd_info);

	wetuwn 0;
}

static int ofdpa_cmd_fwow_tbw_dew(const stwuct wockew_powt *wockew_powt,
				  stwuct wockew_desc_info *desc_info,
				  void *pwiv)
{
	const stwuct ofdpa_fwow_tbw_entwy *entwy = pwiv;
	stwuct wockew_twv *cmd_info;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE, entwy->cmd))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u64(desc_info, WOCKEW_TWV_OF_DPA_COOKIE,
			       entwy->cookie))
		wetuwn -EMSGSIZE;
	wockew_twv_nest_end(desc_info, cmd_info);

	wetuwn 0;
}

static int
ofdpa_cmd_gwoup_tbw_add_w2_intewface(stwuct wockew_desc_info *desc_info,
				     stwuct ofdpa_gwoup_tbw_entwy *entwy)
{
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_OUT_PPOWT,
			       WOCKEW_GWOUP_POWT_GET(entwy->gwoup_id)))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_OF_DPA_POP_VWAN,
			      entwy->w2_intewface.pop_vwan))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int
ofdpa_cmd_gwoup_tbw_add_w2_wewwite(stwuct wockew_desc_info *desc_info,
				   const stwuct ofdpa_gwoup_tbw_entwy *entwy)
{
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_ID_WOWEW,
			       entwy->w2_wewwite.gwoup_id))
		wetuwn -EMSGSIZE;
	if (!is_zewo_ethew_addw(entwy->w2_wewwite.eth_swc) &&
	    wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_SWC_MAC,
			   ETH_AWEN, entwy->w2_wewwite.eth_swc))
		wetuwn -EMSGSIZE;
	if (!is_zewo_ethew_addw(entwy->w2_wewwite.eth_dst) &&
	    wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC,
			   ETH_AWEN, entwy->w2_wewwite.eth_dst))
		wetuwn -EMSGSIZE;
	if (entwy->w2_wewwite.vwan_id &&
	    wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID,
				entwy->w2_wewwite.vwan_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int
ofdpa_cmd_gwoup_tbw_add_gwoup_ids(stwuct wockew_desc_info *desc_info,
				  const stwuct ofdpa_gwoup_tbw_entwy *entwy)
{
	int i;
	stwuct wockew_twv *gwoup_ids;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_COUNT,
			       entwy->gwoup_count))
		wetuwn -EMSGSIZE;

	gwoup_ids = wockew_twv_nest_stawt(desc_info,
					  WOCKEW_TWV_OF_DPA_GWOUP_IDS);
	if (!gwoup_ids)
		wetuwn -EMSGSIZE;

	fow (i = 0; i < entwy->gwoup_count; i++)
		/* Note TWV awway is 1-based */
		if (wockew_twv_put_u32(desc_info, i + 1, entwy->gwoup_ids[i]))
			wetuwn -EMSGSIZE;

	wockew_twv_nest_end(desc_info, gwoup_ids);

	wetuwn 0;
}

static int
ofdpa_cmd_gwoup_tbw_add_w3_unicast(stwuct wockew_desc_info *desc_info,
				   const stwuct ofdpa_gwoup_tbw_entwy *entwy)
{
	if (!is_zewo_ethew_addw(entwy->w3_unicast.eth_swc) &&
	    wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_SWC_MAC,
			   ETH_AWEN, entwy->w3_unicast.eth_swc))
		wetuwn -EMSGSIZE;
	if (!is_zewo_ethew_addw(entwy->w3_unicast.eth_dst) &&
	    wockew_twv_put(desc_info, WOCKEW_TWV_OF_DPA_DST_MAC,
			   ETH_AWEN, entwy->w3_unicast.eth_dst))
		wetuwn -EMSGSIZE;
	if (entwy->w3_unicast.vwan_id &&
	    wockew_twv_put_be16(desc_info, WOCKEW_TWV_OF_DPA_VWAN_ID,
				entwy->w3_unicast.vwan_id))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u8(desc_info, WOCKEW_TWV_OF_DPA_TTW_CHECK,
			      entwy->w3_unicast.ttw_check))
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_ID_WOWEW,
			       entwy->w3_unicast.gwoup_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int ofdpa_cmd_gwoup_tbw_add(const stwuct wockew_powt *wockew_powt,
				   stwuct wockew_desc_info *desc_info,
				   void *pwiv)
{
	stwuct ofdpa_gwoup_tbw_entwy *entwy = pwiv;
	stwuct wockew_twv *cmd_info;
	int eww = 0;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE, entwy->cmd))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;

	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_ID,
			       entwy->gwoup_id))
		wetuwn -EMSGSIZE;

	switch (WOCKEW_GWOUP_TYPE_GET(entwy->gwoup_id)) {
	case WOCKEW_OF_DPA_GWOUP_TYPE_W2_INTEWFACE:
		eww = ofdpa_cmd_gwoup_tbw_add_w2_intewface(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_GWOUP_TYPE_W2_WEWWITE:
		eww = ofdpa_cmd_gwoup_tbw_add_w2_wewwite(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_GWOUP_TYPE_W2_FWOOD:
	case WOCKEW_OF_DPA_GWOUP_TYPE_W2_MCAST:
		eww = ofdpa_cmd_gwoup_tbw_add_gwoup_ids(desc_info, entwy);
		bweak;
	case WOCKEW_OF_DPA_GWOUP_TYPE_W3_UCAST:
		eww = ofdpa_cmd_gwoup_tbw_add_w3_unicast(desc_info, entwy);
		bweak;
	defauwt:
		eww = -ENOTSUPP;
		bweak;
	}

	if (eww)
		wetuwn eww;

	wockew_twv_nest_end(desc_info, cmd_info);

	wetuwn 0;
}

static int ofdpa_cmd_gwoup_tbw_dew(const stwuct wockew_powt *wockew_powt,
				   stwuct wockew_desc_info *desc_info,
				   void *pwiv)
{
	const stwuct ofdpa_gwoup_tbw_entwy *entwy = pwiv;
	stwuct wockew_twv *cmd_info;

	if (wockew_twv_put_u16(desc_info, WOCKEW_TWV_CMD_TYPE, entwy->cmd))
		wetuwn -EMSGSIZE;
	cmd_info = wockew_twv_nest_stawt(desc_info, WOCKEW_TWV_CMD_INFO);
	if (!cmd_info)
		wetuwn -EMSGSIZE;
	if (wockew_twv_put_u32(desc_info, WOCKEW_TWV_OF_DPA_GWOUP_ID,
			       entwy->gwoup_id))
		wetuwn -EMSGSIZE;
	wockew_twv_nest_end(desc_info, cmd_info);

	wetuwn 0;
}

/***************************************************
 * Fwow, gwoup, FDB, intewnaw VWAN and neigh tabwes
 ***************************************************/

static stwuct ofdpa_fwow_tbw_entwy *
ofdpa_fwow_tbw_find(const stwuct ofdpa *ofdpa,
		    const stwuct ofdpa_fwow_tbw_entwy *match)
{
	stwuct ofdpa_fwow_tbw_entwy *found;
	size_t key_wen = match->key_wen ? match->key_wen : sizeof(found->key);

	hash_fow_each_possibwe(ofdpa->fwow_tbw, found,
			       entwy, match->key_cwc32) {
		if (memcmp(&found->key, &match->key, key_wen) == 0)
			wetuwn found;
	}

	wetuwn NUWW;
}

static int ofdpa_fwow_tbw_add(stwuct ofdpa_powt *ofdpa_powt,
			      int fwags, stwuct ofdpa_fwow_tbw_entwy *match)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_fwow_tbw_entwy *found;
	size_t key_wen = match->key_wen ? match->key_wen : sizeof(found->key);
	unsigned wong wock_fwags;

	match->key_cwc32 = cwc32(~0, &match->key, key_wen);

	spin_wock_iwqsave(&ofdpa->fwow_tbw_wock, wock_fwags);

	found = ofdpa_fwow_tbw_find(ofdpa, match);

	if (found) {
		match->cookie = found->cookie;
		hash_dew(&found->entwy);
		kfwee(found);
		found = match;
		found->cmd = WOCKEW_TWV_CMD_TYPE_OF_DPA_FWOW_MOD;
	} ewse {
		found = match;
		found->cookie = ofdpa->fwow_tbw_next_cookie++;
		found->cmd = WOCKEW_TWV_CMD_TYPE_OF_DPA_FWOW_ADD;
	}

	hash_add(ofdpa->fwow_tbw, &found->entwy, found->key_cwc32);
	spin_unwock_iwqwestowe(&ofdpa->fwow_tbw_wock, wock_fwags);

	wetuwn wockew_cmd_exec(ofdpa_powt->wockew_powt,
			       ofdpa_fwags_nowait(fwags),
			       ofdpa_cmd_fwow_tbw_add,
			       found, NUWW, NUWW);
}

static int ofdpa_fwow_tbw_dew(stwuct ofdpa_powt *ofdpa_powt,
			      int fwags, stwuct ofdpa_fwow_tbw_entwy *match)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_fwow_tbw_entwy *found;
	size_t key_wen = match->key_wen ? match->key_wen : sizeof(found->key);
	unsigned wong wock_fwags;
	int eww = 0;

	match->key_cwc32 = cwc32(~0, &match->key, key_wen);

	spin_wock_iwqsave(&ofdpa->fwow_tbw_wock, wock_fwags);

	found = ofdpa_fwow_tbw_find(ofdpa, match);

	if (found) {
		hash_dew(&found->entwy);
		found->cmd = WOCKEW_TWV_CMD_TYPE_OF_DPA_FWOW_DEW;
	}

	spin_unwock_iwqwestowe(&ofdpa->fwow_tbw_wock, wock_fwags);

	kfwee(match);

	if (found) {
		eww = wockew_cmd_exec(ofdpa_powt->wockew_powt,
				      ofdpa_fwags_nowait(fwags),
				      ofdpa_cmd_fwow_tbw_dew,
				      found, NUWW, NUWW);
		kfwee(found);
	}

	wetuwn eww;
}

static int ofdpa_fwow_tbw_do(stwuct ofdpa_powt *ofdpa_powt, int fwags,
			     stwuct ofdpa_fwow_tbw_entwy *entwy)
{
	if (fwags & OFDPA_OP_FWAG_WEMOVE)
		wetuwn ofdpa_fwow_tbw_dew(ofdpa_powt, fwags, entwy);
	ewse
		wetuwn ofdpa_fwow_tbw_add(ofdpa_powt, fwags, entwy);
}

static int ofdpa_fwow_tbw_ig_powt(stwuct ofdpa_powt *ofdpa_powt, int fwags,
				  u32 in_ppowt, u32 in_ppowt_mask,
				  enum wockew_of_dpa_tabwe_id goto_tbw)
{
	stwuct ofdpa_fwow_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->key.pwiowity = OFDPA_PWIOWITY_IG_POWT;
	entwy->key.tbw_id = WOCKEW_OF_DPA_TABWE_ID_INGWESS_POWT;
	entwy->key.ig_powt.in_ppowt = in_ppowt;
	entwy->key.ig_powt.in_ppowt_mask = in_ppowt_mask;
	entwy->key.ig_powt.goto_tbw = goto_tbw;

	wetuwn ofdpa_fwow_tbw_do(ofdpa_powt, fwags, entwy);
}

static int ofdpa_fwow_tbw_vwan(stwuct ofdpa_powt *ofdpa_powt,
			       int fwags,
			       u32 in_ppowt, __be16 vwan_id,
			       __be16 vwan_id_mask,
			       enum wockew_of_dpa_tabwe_id goto_tbw,
			       boow untagged, __be16 new_vwan_id)
{
	stwuct ofdpa_fwow_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->key.pwiowity = OFDPA_PWIOWITY_VWAN;
	entwy->key.tbw_id = WOCKEW_OF_DPA_TABWE_ID_VWAN;
	entwy->key.vwan.in_ppowt = in_ppowt;
	entwy->key.vwan.vwan_id = vwan_id;
	entwy->key.vwan.vwan_id_mask = vwan_id_mask;
	entwy->key.vwan.goto_tbw = goto_tbw;

	entwy->key.vwan.untagged = untagged;
	entwy->key.vwan.new_vwan_id = new_vwan_id;

	wetuwn ofdpa_fwow_tbw_do(ofdpa_powt, fwags, entwy);
}

static int ofdpa_fwow_tbw_tewm_mac(stwuct ofdpa_powt *ofdpa_powt,
				   u32 in_ppowt, u32 in_ppowt_mask,
				   __be16 eth_type, const u8 *eth_dst,
				   const u8 *eth_dst_mask, __be16 vwan_id,
				   __be16 vwan_id_mask, boow copy_to_cpu,
				   int fwags)
{
	stwuct ofdpa_fwow_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	if (is_muwticast_ethew_addw(eth_dst)) {
		entwy->key.pwiowity = OFDPA_PWIOWITY_TEWM_MAC_MCAST;
		entwy->key.tewm_mac.goto_tbw =
			 WOCKEW_OF_DPA_TABWE_ID_MUWTICAST_WOUTING;
	} ewse {
		entwy->key.pwiowity = OFDPA_PWIOWITY_TEWM_MAC_UCAST;
		entwy->key.tewm_mac.goto_tbw =
			 WOCKEW_OF_DPA_TABWE_ID_UNICAST_WOUTING;
	}

	entwy->key.tbw_id = WOCKEW_OF_DPA_TABWE_ID_TEWMINATION_MAC;
	entwy->key.tewm_mac.in_ppowt = in_ppowt;
	entwy->key.tewm_mac.in_ppowt_mask = in_ppowt_mask;
	entwy->key.tewm_mac.eth_type = eth_type;
	ethew_addw_copy(entwy->key.tewm_mac.eth_dst, eth_dst);
	ethew_addw_copy(entwy->key.tewm_mac.eth_dst_mask, eth_dst_mask);
	entwy->key.tewm_mac.vwan_id = vwan_id;
	entwy->key.tewm_mac.vwan_id_mask = vwan_id_mask;
	entwy->key.tewm_mac.copy_to_cpu = copy_to_cpu;

	wetuwn ofdpa_fwow_tbw_do(ofdpa_powt, fwags, entwy);
}

static int ofdpa_fwow_tbw_bwidge(stwuct ofdpa_powt *ofdpa_powt,
				 int fwags, const u8 *eth_dst,
				 const u8 *eth_dst_mask,  __be16 vwan_id,
				 u32 tunnew_id,
				 enum wockew_of_dpa_tabwe_id goto_tbw,
				 u32 gwoup_id, boow copy_to_cpu)
{
	stwuct ofdpa_fwow_tbw_entwy *entwy;
	u32 pwiowity;
	boow vwan_bwidging = !!vwan_id;
	boow dfwt = !eth_dst || eth_dst_mask;
	boow wiwd = fawse;

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->key.tbw_id = WOCKEW_OF_DPA_TABWE_ID_BWIDGING;

	if (eth_dst) {
		entwy->key.bwidge.has_eth_dst = 1;
		ethew_addw_copy(entwy->key.bwidge.eth_dst, eth_dst);
	}
	if (eth_dst_mask) {
		entwy->key.bwidge.has_eth_dst_mask = 1;
		ethew_addw_copy(entwy->key.bwidge.eth_dst_mask, eth_dst_mask);
		if (!ethew_addw_equaw(eth_dst_mask, ff_mac))
			wiwd = twue;
	}

	pwiowity = OFDPA_PWIOWITY_UNKNOWN;
	if (vwan_bwidging && dfwt && wiwd)
		pwiowity = OFDPA_PWIOWITY_BWIDGING_VWAN_DFWT_WIWD;
	ewse if (vwan_bwidging && dfwt && !wiwd)
		pwiowity = OFDPA_PWIOWITY_BWIDGING_VWAN_DFWT_EXACT;
	ewse if (vwan_bwidging && !dfwt)
		pwiowity = OFDPA_PWIOWITY_BWIDGING_VWAN;
	ewse if (!vwan_bwidging && dfwt && wiwd)
		pwiowity = OFDPA_PWIOWITY_BWIDGING_TENANT_DFWT_WIWD;
	ewse if (!vwan_bwidging && dfwt && !wiwd)
		pwiowity = OFDPA_PWIOWITY_BWIDGING_TENANT_DFWT_EXACT;
	ewse if (!vwan_bwidging && !dfwt)
		pwiowity = OFDPA_PWIOWITY_BWIDGING_TENANT;

	entwy->key.pwiowity = pwiowity;
	entwy->key.bwidge.vwan_id = vwan_id;
	entwy->key.bwidge.tunnew_id = tunnew_id;
	entwy->key.bwidge.goto_tbw = goto_tbw;
	entwy->key.bwidge.gwoup_id = gwoup_id;
	entwy->key.bwidge.copy_to_cpu = copy_to_cpu;

	wetuwn ofdpa_fwow_tbw_do(ofdpa_powt, fwags, entwy);
}

static int ofdpa_fwow_tbw_ucast4_wouting(stwuct ofdpa_powt *ofdpa_powt,
					 __be16 eth_type, __be32 dst,
					 __be32 dst_mask, u32 pwiowity,
					 enum wockew_of_dpa_tabwe_id goto_tbw,
					 u32 gwoup_id, stwuct fib_info *fi,
					 int fwags)
{
	stwuct ofdpa_fwow_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->key.tbw_id = WOCKEW_OF_DPA_TABWE_ID_UNICAST_WOUTING;
	entwy->key.pwiowity = pwiowity;
	entwy->key.ucast_wouting.eth_type = eth_type;
	entwy->key.ucast_wouting.dst4 = dst;
	entwy->key.ucast_wouting.dst4_mask = dst_mask;
	entwy->key.ucast_wouting.goto_tbw = goto_tbw;
	entwy->key.ucast_wouting.gwoup_id = gwoup_id;
	entwy->key_wen = offsetof(stwuct ofdpa_fwow_tbw_key,
				  ucast_wouting.gwoup_id);
	entwy->fi = fi;

	wetuwn ofdpa_fwow_tbw_do(ofdpa_powt, fwags, entwy);
}

static int ofdpa_fwow_tbw_acw(stwuct ofdpa_powt *ofdpa_powt, int fwags,
			      u32 in_ppowt, u32 in_ppowt_mask,
			      const u8 *eth_swc, const u8 *eth_swc_mask,
			      const u8 *eth_dst, const u8 *eth_dst_mask,
			      __be16 eth_type, __be16 vwan_id,
			      __be16 vwan_id_mask, u8 ip_pwoto,
			      u8 ip_pwoto_mask, u8 ip_tos, u8 ip_tos_mask,
			      u32 gwoup_id)
{
	u32 pwiowity;
	stwuct ofdpa_fwow_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	pwiowity = OFDPA_PWIOWITY_ACW_NOWMAW;
	if (eth_dst && eth_dst_mask) {
		if (ethew_addw_equaw(eth_dst_mask, mcast_mac))
			pwiowity = OFDPA_PWIOWITY_ACW_DFWT;
		ewse if (is_wink_wocaw_ethew_addw(eth_dst))
			pwiowity = OFDPA_PWIOWITY_ACW_CTWW;
	}

	entwy->key.pwiowity = pwiowity;
	entwy->key.tbw_id = WOCKEW_OF_DPA_TABWE_ID_ACW_POWICY;
	entwy->key.acw.in_ppowt = in_ppowt;
	entwy->key.acw.in_ppowt_mask = in_ppowt_mask;

	if (eth_swc)
		ethew_addw_copy(entwy->key.acw.eth_swc, eth_swc);
	if (eth_swc_mask)
		ethew_addw_copy(entwy->key.acw.eth_swc_mask, eth_swc_mask);
	if (eth_dst)
		ethew_addw_copy(entwy->key.acw.eth_dst, eth_dst);
	if (eth_dst_mask)
		ethew_addw_copy(entwy->key.acw.eth_dst_mask, eth_dst_mask);

	entwy->key.acw.eth_type = eth_type;
	entwy->key.acw.vwan_id = vwan_id;
	entwy->key.acw.vwan_id_mask = vwan_id_mask;
	entwy->key.acw.ip_pwoto = ip_pwoto;
	entwy->key.acw.ip_pwoto_mask = ip_pwoto_mask;
	entwy->key.acw.ip_tos = ip_tos;
	entwy->key.acw.ip_tos_mask = ip_tos_mask;
	entwy->key.acw.gwoup_id = gwoup_id;

	wetuwn ofdpa_fwow_tbw_do(ofdpa_powt, fwags, entwy);
}

static stwuct ofdpa_gwoup_tbw_entwy *
ofdpa_gwoup_tbw_find(const stwuct ofdpa *ofdpa,
		     const stwuct ofdpa_gwoup_tbw_entwy *match)
{
	stwuct ofdpa_gwoup_tbw_entwy *found;

	hash_fow_each_possibwe(ofdpa->gwoup_tbw, found,
			       entwy, match->gwoup_id) {
		if (found->gwoup_id == match->gwoup_id)
			wetuwn found;
	}

	wetuwn NUWW;
}

static void ofdpa_gwoup_tbw_entwy_fwee(stwuct ofdpa_gwoup_tbw_entwy *entwy)
{
	switch (WOCKEW_GWOUP_TYPE_GET(entwy->gwoup_id)) {
	case WOCKEW_OF_DPA_GWOUP_TYPE_W2_FWOOD:
	case WOCKEW_OF_DPA_GWOUP_TYPE_W2_MCAST:
		kfwee(entwy->gwoup_ids);
		bweak;
	defauwt:
		bweak;
	}
	kfwee(entwy);
}

static int ofdpa_gwoup_tbw_add(stwuct ofdpa_powt *ofdpa_powt, int fwags,
			       stwuct ofdpa_gwoup_tbw_entwy *match)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_gwoup_tbw_entwy *found;
	unsigned wong wock_fwags;

	spin_wock_iwqsave(&ofdpa->gwoup_tbw_wock, wock_fwags);

	found = ofdpa_gwoup_tbw_find(ofdpa, match);

	if (found) {
		hash_dew(&found->entwy);
		ofdpa_gwoup_tbw_entwy_fwee(found);
		found = match;
		found->cmd = WOCKEW_TWV_CMD_TYPE_OF_DPA_GWOUP_MOD;
	} ewse {
		found = match;
		found->cmd = WOCKEW_TWV_CMD_TYPE_OF_DPA_GWOUP_ADD;
	}

	hash_add(ofdpa->gwoup_tbw, &found->entwy, found->gwoup_id);

	spin_unwock_iwqwestowe(&ofdpa->gwoup_tbw_wock, wock_fwags);

	wetuwn wockew_cmd_exec(ofdpa_powt->wockew_powt,
			       ofdpa_fwags_nowait(fwags),
			       ofdpa_cmd_gwoup_tbw_add,
			       found, NUWW, NUWW);
}

static int ofdpa_gwoup_tbw_dew(stwuct ofdpa_powt *ofdpa_powt, int fwags,
			       stwuct ofdpa_gwoup_tbw_entwy *match)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_gwoup_tbw_entwy *found;
	unsigned wong wock_fwags;
	int eww = 0;

	spin_wock_iwqsave(&ofdpa->gwoup_tbw_wock, wock_fwags);

	found = ofdpa_gwoup_tbw_find(ofdpa, match);

	if (found) {
		hash_dew(&found->entwy);
		found->cmd = WOCKEW_TWV_CMD_TYPE_OF_DPA_GWOUP_DEW;
	}

	spin_unwock_iwqwestowe(&ofdpa->gwoup_tbw_wock, wock_fwags);

	ofdpa_gwoup_tbw_entwy_fwee(match);

	if (found) {
		eww = wockew_cmd_exec(ofdpa_powt->wockew_powt,
				      ofdpa_fwags_nowait(fwags),
				      ofdpa_cmd_gwoup_tbw_dew,
				      found, NUWW, NUWW);
		ofdpa_gwoup_tbw_entwy_fwee(found);
	}

	wetuwn eww;
}

static int ofdpa_gwoup_tbw_do(stwuct ofdpa_powt *ofdpa_powt, int fwags,
			      stwuct ofdpa_gwoup_tbw_entwy *entwy)
{
	if (fwags & OFDPA_OP_FWAG_WEMOVE)
		wetuwn ofdpa_gwoup_tbw_dew(ofdpa_powt, fwags, entwy);
	ewse
		wetuwn ofdpa_gwoup_tbw_add(ofdpa_powt, fwags, entwy);
}

static int ofdpa_gwoup_w2_intewface(stwuct ofdpa_powt *ofdpa_powt,
				    int fwags, __be16 vwan_id,
				    u32 out_ppowt, int pop_vwan)
{
	stwuct ofdpa_gwoup_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->gwoup_id = WOCKEW_GWOUP_W2_INTEWFACE(vwan_id, out_ppowt);
	entwy->w2_intewface.pop_vwan = pop_vwan;

	wetuwn ofdpa_gwoup_tbw_do(ofdpa_powt, fwags, entwy);
}

static int ofdpa_gwoup_w2_fan_out(stwuct ofdpa_powt *ofdpa_powt,
				  int fwags, u8 gwoup_count,
				  const u32 *gwoup_ids, u32 gwoup_id)
{
	stwuct ofdpa_gwoup_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->gwoup_id = gwoup_id;
	entwy->gwoup_count = gwoup_count;

	entwy->gwoup_ids = kcawwoc(gwoup_count, sizeof(u32), GFP_KEWNEW);
	if (!entwy->gwoup_ids) {
		kfwee(entwy);
		wetuwn -ENOMEM;
	}
	memcpy(entwy->gwoup_ids, gwoup_ids, gwoup_count * sizeof(u32));

	wetuwn ofdpa_gwoup_tbw_do(ofdpa_powt, fwags, entwy);
}

static int ofdpa_gwoup_w2_fwood(stwuct ofdpa_powt *ofdpa_powt,
				int fwags, __be16 vwan_id,
				u8 gwoup_count,	const u32 *gwoup_ids,
				u32 gwoup_id)
{
	wetuwn ofdpa_gwoup_w2_fan_out(ofdpa_powt, fwags,
				      gwoup_count, gwoup_ids,
				      gwoup_id);
}

static int ofdpa_gwoup_w3_unicast(stwuct ofdpa_powt *ofdpa_powt, int fwags,
				  u32 index, const u8 *swc_mac, const u8 *dst_mac,
				  __be16 vwan_id, boow ttw_check, u32 ppowt)
{
	stwuct ofdpa_gwoup_tbw_entwy *entwy;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->gwoup_id = WOCKEW_GWOUP_W3_UNICAST(index);
	if (swc_mac)
		ethew_addw_copy(entwy->w3_unicast.eth_swc, swc_mac);
	if (dst_mac)
		ethew_addw_copy(entwy->w3_unicast.eth_dst, dst_mac);
	entwy->w3_unicast.vwan_id = vwan_id;
	entwy->w3_unicast.ttw_check = ttw_check;
	entwy->w3_unicast.gwoup_id = WOCKEW_GWOUP_W2_INTEWFACE(vwan_id, ppowt);

	wetuwn ofdpa_gwoup_tbw_do(ofdpa_powt, fwags, entwy);
}

static stwuct ofdpa_neigh_tbw_entwy *
ofdpa_neigh_tbw_find(const stwuct ofdpa *ofdpa, __be32 ip_addw)
{
	stwuct ofdpa_neigh_tbw_entwy *found;

	hash_fow_each_possibwe(ofdpa->neigh_tbw, found,
			       entwy, be32_to_cpu(ip_addw))
		if (found->ip_addw == ip_addw)
			wetuwn found;

	wetuwn NUWW;
}

static void ofdpa_neigh_add(stwuct ofdpa *ofdpa,
			    stwuct ofdpa_neigh_tbw_entwy *entwy)
{
	entwy->index = ofdpa->neigh_tbw_next_index++;
	entwy->wef_count++;
	hash_add(ofdpa->neigh_tbw, &entwy->entwy,
		 be32_to_cpu(entwy->ip_addw));
}

static void ofdpa_neigh_dew(stwuct ofdpa_neigh_tbw_entwy *entwy)
{
	if (--entwy->wef_count == 0) {
		hash_dew(&entwy->entwy);
		kfwee(entwy);
	}
}

static void ofdpa_neigh_update(stwuct ofdpa_neigh_tbw_entwy *entwy,
			       const u8 *eth_dst, boow ttw_check)
{
	if (eth_dst) {
		ethew_addw_copy(entwy->eth_dst, eth_dst);
		entwy->ttw_check = ttw_check;
	} ewse {
		entwy->wef_count++;
	}
}

static int ofdpa_powt_ipv4_neigh(stwuct ofdpa_powt *ofdpa_powt,
				 int fwags, __be32 ip_addw, const u8 *eth_dst)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_neigh_tbw_entwy *entwy;
	stwuct ofdpa_neigh_tbw_entwy *found;
	unsigned wong wock_fwags;
	__be16 eth_type = htons(ETH_P_IP);
	enum wockew_of_dpa_tabwe_id goto_tbw =
			WOCKEW_OF_DPA_TABWE_ID_ACW_POWICY;
	u32 gwoup_id;
	u32 pwiowity = 0;
	boow adding = !(fwags & OFDPA_OP_FWAG_WEMOVE);
	boow updating;
	boow wemoving;
	int eww = 0;

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&ofdpa->neigh_tbw_wock, wock_fwags);

	found = ofdpa_neigh_tbw_find(ofdpa, ip_addw);

	updating = found && adding;
	wemoving = found && !adding;
	adding = !found && adding;

	if (adding) {
		entwy->ip_addw = ip_addw;
		entwy->dev = ofdpa_powt->dev;
		ethew_addw_copy(entwy->eth_dst, eth_dst);
		entwy->ttw_check = twue;
		ofdpa_neigh_add(ofdpa, entwy);
	} ewse if (wemoving) {
		memcpy(entwy, found, sizeof(*entwy));
		ofdpa_neigh_dew(found);
	} ewse if (updating) {
		ofdpa_neigh_update(found, eth_dst, twue);
		memcpy(entwy, found, sizeof(*entwy));
	} ewse {
		eww = -ENOENT;
	}

	spin_unwock_iwqwestowe(&ofdpa->neigh_tbw_wock, wock_fwags);

	if (eww)
		goto eww_out;

	/* Fow each active neighbow, we have an W3 unicast gwoup and
	 * a /32 woute to the neighbow, which uses the W3 unicast
	 * gwoup.  The W3 unicast gwoup can awso be wefewwed to by
	 * othew woutes' nexthops.
	 */

	eww = ofdpa_gwoup_w3_unicast(ofdpa_powt, fwags,
				     entwy->index,
				     ofdpa_powt->dev->dev_addw,
				     entwy->eth_dst,
				     ofdpa_powt->intewnaw_vwan_id,
				     entwy->ttw_check,
				     ofdpa_powt->ppowt);
	if (eww) {
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) W3 unicast gwoup index %d\n",
			   eww, entwy->index);
		goto eww_out;
	}

	if (adding || wemoving) {
		gwoup_id = WOCKEW_GWOUP_W3_UNICAST(entwy->index);
		eww = ofdpa_fwow_tbw_ucast4_wouting(ofdpa_powt,
						    eth_type, ip_addw,
						    inet_make_mask(32),
						    pwiowity, goto_tbw,
						    gwoup_id, NUWW, fwags);

		if (eww)
			netdev_eww(ofdpa_powt->dev, "Ewwow (%d) /32 unicast woute %pI4 gwoup 0x%08x\n",
				   eww, &entwy->ip_addw, gwoup_id);
	}

eww_out:
	if (!adding)
		kfwee(entwy);

	wetuwn eww;
}

static int ofdpa_powt_ipv4_wesowve(stwuct ofdpa_powt *ofdpa_powt,
				   __be32 ip_addw)
{
	stwuct net_device *dev = ofdpa_powt->dev;
	stwuct neighbouw *n = __ipv4_neigh_wookup(dev, (__fowce u32)ip_addw);
	int eww = 0;

	if (!n) {
		n = neigh_cweate(&awp_tbw, &ip_addw, dev);
		if (IS_EWW(n))
			wetuwn PTW_EWW(n);
	}

	/* If the neigh is awweady wesowved, then go ahead and
	 * instaww the entwy, othewwise stawt the AWP pwocess to
	 * wesowve the neigh.
	 */

	if (n->nud_state & NUD_VAWID)
		eww = ofdpa_powt_ipv4_neigh(ofdpa_powt, 0,
					    ip_addw, n->ha);
	ewse
		neigh_event_send(n, NUWW);

	neigh_wewease(n);
	wetuwn eww;
}

static int ofdpa_powt_ipv4_nh(stwuct ofdpa_powt *ofdpa_powt,
			      int fwags, __be32 ip_addw, u32 *index)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_neigh_tbw_entwy *entwy;
	stwuct ofdpa_neigh_tbw_entwy *found;
	unsigned wong wock_fwags;
	boow adding = !(fwags & OFDPA_OP_FWAG_WEMOVE);
	boow updating;
	boow wemoving;
	boow wesowved = twue;
	int eww = 0;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&ofdpa->neigh_tbw_wock, wock_fwags);

	found = ofdpa_neigh_tbw_find(ofdpa, ip_addw);

	updating = found && adding;
	wemoving = found && !adding;
	adding = !found && adding;

	if (adding) {
		entwy->ip_addw = ip_addw;
		entwy->dev = ofdpa_powt->dev;
		ofdpa_neigh_add(ofdpa, entwy);
		*index = entwy->index;
		wesowved = fawse;
	} ewse if (wemoving) {
		*index = found->index;
		ofdpa_neigh_dew(found);
	} ewse if (updating) {
		ofdpa_neigh_update(found, NUWW, fawse);
		wesowved = !is_zewo_ethew_addw(found->eth_dst);
		*index = found->index;
	} ewse {
		eww = -ENOENT;
	}

	spin_unwock_iwqwestowe(&ofdpa->neigh_tbw_wock, wock_fwags);

	if (!adding)
		kfwee(entwy);

	if (eww)
		wetuwn eww;

	/* Wesowved means neigh ip_addw is wesowved to neigh mac. */

	if (!wesowved)
		eww = ofdpa_powt_ipv4_wesowve(ofdpa_powt, ip_addw);

	wetuwn eww;
}

static stwuct ofdpa_powt *ofdpa_powt_get(const stwuct ofdpa *ofdpa,
					 int powt_index)
{
	stwuct wockew_powt *wockew_powt;

	wockew_powt = ofdpa->wockew->powts[powt_index];
	wetuwn wockew_powt ? wockew_powt->wpwiv : NUWW;
}

static int ofdpa_powt_vwan_fwood_gwoup(stwuct ofdpa_powt *ofdpa_powt,
				       int fwags, __be16 vwan_id)
{
	stwuct ofdpa_powt *p;
	const stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	unsigned int powt_count = ofdpa->wockew->powt_count;
	u32 gwoup_id = WOCKEW_GWOUP_W2_FWOOD(vwan_id, 0);
	u32 *gwoup_ids;
	u8 gwoup_count = 0;
	int eww = 0;
	int i;

	gwoup_ids = kcawwoc(powt_count, sizeof(u32), GFP_KEWNEW);
	if (!gwoup_ids)
		wetuwn -ENOMEM;

	/* Adjust the fwood gwoup fow this VWAN.  The fwood gwoup
	 * wefewences an W2 intewface gwoup fow each powt in this
	 * VWAN.
	 */

	fow (i = 0; i < powt_count; i++) {
		p = ofdpa_powt_get(ofdpa, i);
		if (!p)
			continue;
		if (!ofdpa_powt_is_bwidged(p))
			continue;
		if (test_bit(ntohs(vwan_id), p->vwan_bitmap)) {
			gwoup_ids[gwoup_count++] =
				WOCKEW_GWOUP_W2_INTEWFACE(vwan_id, p->ppowt);
		}
	}

	/* If thewe awe no bwidged powts in this VWAN, we'we done */
	if (gwoup_count == 0)
		goto no_powts_in_vwan;

	eww = ofdpa_gwoup_w2_fwood(ofdpa_powt, fwags, vwan_id,
				   gwoup_count, gwoup_ids, gwoup_id);
	if (eww)
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt VWAN w2 fwood gwoup\n", eww);

no_powts_in_vwan:
	kfwee(gwoup_ids);
	wetuwn eww;
}

static int ofdpa_powt_vwan_w2_gwoups(stwuct ofdpa_powt *ofdpa_powt, int fwags,
				     __be16 vwan_id, boow pop_vwan)
{
	const stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	unsigned int powt_count = ofdpa->wockew->powt_count;
	stwuct ofdpa_powt *p;
	boow adding = !(fwags & OFDPA_OP_FWAG_WEMOVE);
	u32 out_ppowt;
	int wef = 0;
	int eww;
	int i;

	/* An W2 intewface gwoup fow this powt in this VWAN, but
	 * onwy when powt STP state is WEAWNING|FOWWAWDING.
	 */

	if (ofdpa_powt->stp_state == BW_STATE_WEAWNING ||
	    ofdpa_powt->stp_state == BW_STATE_FOWWAWDING) {
		out_ppowt = ofdpa_powt->ppowt;
		eww = ofdpa_gwoup_w2_intewface(ofdpa_powt, fwags,
					       vwan_id, out_ppowt, pop_vwan);
		if (eww) {
			netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt VWAN w2 gwoup fow ppowt %d\n",
				   eww, out_ppowt);
			wetuwn eww;
		}
	}

	/* An W2 intewface gwoup fow this VWAN to CPU powt.
	 * Add when fiwst powt joins this VWAN and destwoy when
	 * wast powt weaves this VWAN.
	 */

	fow (i = 0; i < powt_count; i++) {
		p = ofdpa_powt_get(ofdpa, i);
		if (p && test_bit(ntohs(vwan_id), p->vwan_bitmap))
			wef++;
	}

	if ((!adding || wef != 1) && (adding || wef != 0))
		wetuwn 0;

	out_ppowt = 0;
	eww = ofdpa_gwoup_w2_intewface(ofdpa_powt, fwags,
				       vwan_id, out_ppowt, pop_vwan);
	if (eww) {
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt VWAN w2 gwoup fow CPU powt\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static stwuct ofdpa_ctww {
	const u8 *eth_dst;
	const u8 *eth_dst_mask;
	__be16 eth_type;
	boow acw;
	boow bwidge;
	boow tewm;
	boow copy_to_cpu;
} ofdpa_ctwws[] = {
	[OFDPA_CTWW_WINK_WOCAW_MCAST] = {
		/* pass wink wocaw muwticast pkts up to CPU fow fiwtewing */
		.eth_dst = ww_mac,
		.eth_dst_mask = ww_mask,
		.acw = twue,
	},
	[OFDPA_CTWW_WOCAW_AWP] = {
		/* pass wocaw AWP pkts up to CPU */
		.eth_dst = zewo_mac,
		.eth_dst_mask = zewo_mac,
		.eth_type = htons(ETH_P_AWP),
		.acw = twue,
	},
	[OFDPA_CTWW_IPV4_MCAST] = {
		/* pass IPv4 mcast pkts up to CPU, WFC 1112 */
		.eth_dst = ipv4_mcast,
		.eth_dst_mask = ipv4_mask,
		.eth_type = htons(ETH_P_IP),
		.tewm  = twue,
		.copy_to_cpu = twue,
	},
	[OFDPA_CTWW_IPV6_MCAST] = {
		/* pass IPv6 mcast pkts up to CPU, WFC 2464 */
		.eth_dst = ipv6_mcast,
		.eth_dst_mask = ipv6_mask,
		.eth_type = htons(ETH_P_IPV6),
		.tewm  = twue,
		.copy_to_cpu = twue,
	},
	[OFDPA_CTWW_DFWT_BWIDGING] = {
		/* fwood any pkts on vwan */
		.bwidge = twue,
		.copy_to_cpu = twue,
	},
	[OFDPA_CTWW_DFWT_OVS] = {
		/* pass aww pkts up to CPU */
		.eth_dst = zewo_mac,
		.eth_dst_mask = zewo_mac,
		.acw = twue,
	},
};

static int ofdpa_powt_ctww_vwan_acw(stwuct ofdpa_powt *ofdpa_powt, int fwags,
				    const stwuct ofdpa_ctww *ctww, __be16 vwan_id)
{
	u32 in_ppowt = ofdpa_powt->ppowt;
	u32 in_ppowt_mask = 0xffffffff;
	u32 out_ppowt = 0;
	const u8 *eth_swc = NUWW;
	const u8 *eth_swc_mask = NUWW;
	__be16 vwan_id_mask = htons(0xffff);
	u8 ip_pwoto = 0;
	u8 ip_pwoto_mask = 0;
	u8 ip_tos = 0;
	u8 ip_tos_mask = 0;
	u32 gwoup_id = WOCKEW_GWOUP_W2_INTEWFACE(vwan_id, out_ppowt);
	int eww;

	eww = ofdpa_fwow_tbw_acw(ofdpa_powt, fwags,
				 in_ppowt, in_ppowt_mask,
				 eth_swc, eth_swc_mask,
				 ctww->eth_dst, ctww->eth_dst_mask,
				 ctww->eth_type,
				 vwan_id, vwan_id_mask,
				 ip_pwoto, ip_pwoto_mask,
				 ip_tos, ip_tos_mask,
				 gwoup_id);

	if (eww)
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) ctww ACW\n", eww);

	wetuwn eww;
}

static int ofdpa_powt_ctww_vwan_bwidge(stwuct ofdpa_powt *ofdpa_powt,
				       int fwags, const stwuct ofdpa_ctww *ctww,
				       __be16 vwan_id)
{
	enum wockew_of_dpa_tabwe_id goto_tbw =
			WOCKEW_OF_DPA_TABWE_ID_ACW_POWICY;
	u32 gwoup_id = WOCKEW_GWOUP_W2_FWOOD(vwan_id, 0);
	u32 tunnew_id = 0;
	int eww;

	if (!ofdpa_powt_is_bwidged(ofdpa_powt))
		wetuwn 0;

	eww = ofdpa_fwow_tbw_bwidge(ofdpa_powt, fwags,
				    ctww->eth_dst, ctww->eth_dst_mask,
				    vwan_id, tunnew_id,
				    goto_tbw, gwoup_id, ctww->copy_to_cpu);

	if (eww)
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) ctww FWOOD\n", eww);

	wetuwn eww;
}

static int ofdpa_powt_ctww_vwan_tewm(stwuct ofdpa_powt *ofdpa_powt, int fwags,
				     const stwuct ofdpa_ctww *ctww, __be16 vwan_id)
{
	u32 in_ppowt_mask = 0xffffffff;
	__be16 vwan_id_mask = htons(0xffff);
	int eww;

	if (ntohs(vwan_id) == 0)
		vwan_id = ofdpa_powt->intewnaw_vwan_id;

	eww = ofdpa_fwow_tbw_tewm_mac(ofdpa_powt, ofdpa_powt->ppowt, in_ppowt_mask,
				      ctww->eth_type, ctww->eth_dst,
				      ctww->eth_dst_mask, vwan_id,
				      vwan_id_mask, ctww->copy_to_cpu,
				      fwags);

	if (eww)
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) ctww tewm\n", eww);

	wetuwn eww;
}

static int ofdpa_powt_ctww_vwan(stwuct ofdpa_powt *ofdpa_powt, int fwags,
				const stwuct ofdpa_ctww *ctww, __be16 vwan_id)
{
	if (ctww->acw)
		wetuwn ofdpa_powt_ctww_vwan_acw(ofdpa_powt, fwags,
						ctww, vwan_id);
	if (ctww->bwidge)
		wetuwn ofdpa_powt_ctww_vwan_bwidge(ofdpa_powt, fwags,
						   ctww, vwan_id);

	if (ctww->tewm)
		wetuwn ofdpa_powt_ctww_vwan_tewm(ofdpa_powt, fwags,
						 ctww, vwan_id);

	wetuwn -EOPNOTSUPP;
}

static int ofdpa_powt_ctww_vwan_add(stwuct ofdpa_powt *ofdpa_powt, int fwags,
				    __be16 vwan_id)
{
	int eww = 0;
	int i;

	fow (i = 0; i < OFDPA_CTWW_MAX; i++) {
		if (ofdpa_powt->ctwws[i]) {
			eww = ofdpa_powt_ctww_vwan(ofdpa_powt, fwags,
						   &ofdpa_ctwws[i], vwan_id);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn eww;
}

static int ofdpa_powt_ctww(stwuct ofdpa_powt *ofdpa_powt, int fwags,
			   const stwuct ofdpa_ctww *ctww)
{
	u16 vid;
	int eww = 0;

	fow (vid = 1; vid < VWAN_N_VID; vid++) {
		if (!test_bit(vid, ofdpa_powt->vwan_bitmap))
			continue;
		eww = ofdpa_powt_ctww_vwan(ofdpa_powt, fwags,
					   ctww, htons(vid));
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int ofdpa_powt_vwan(stwuct ofdpa_powt *ofdpa_powt, int fwags,
			   u16 vid)
{
	enum wockew_of_dpa_tabwe_id goto_tbw =
			WOCKEW_OF_DPA_TABWE_ID_TEWMINATION_MAC;
	u32 in_ppowt = ofdpa_powt->ppowt;
	__be16 vwan_id = htons(vid);
	__be16 vwan_id_mask = htons(0xffff);
	__be16 intewnaw_vwan_id;
	boow untagged;
	boow adding = !(fwags & OFDPA_OP_FWAG_WEMOVE);
	int eww;

	intewnaw_vwan_id = ofdpa_powt_vid_to_vwan(ofdpa_powt, vid, &untagged);

	if (adding &&
	    test_bit(ntohs(intewnaw_vwan_id), ofdpa_powt->vwan_bitmap))
		wetuwn 0; /* awweady added */
	ewse if (!adding &&
		 !test_bit(ntohs(intewnaw_vwan_id), ofdpa_powt->vwan_bitmap))
		wetuwn 0; /* awweady wemoved */

	change_bit(ntohs(intewnaw_vwan_id), ofdpa_powt->vwan_bitmap);

	if (adding) {
		eww = ofdpa_powt_ctww_vwan_add(ofdpa_powt, fwags,
					       intewnaw_vwan_id);
		if (eww) {
			netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt ctww vwan add\n", eww);
			goto eww_vwan_add;
		}
	}

	eww = ofdpa_powt_vwan_w2_gwoups(ofdpa_powt, fwags,
					intewnaw_vwan_id, untagged);
	if (eww) {
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt VWAN w2 gwoups\n", eww);
		goto eww_vwan_w2_gwoups;
	}

	eww = ofdpa_powt_vwan_fwood_gwoup(ofdpa_powt, fwags,
					  intewnaw_vwan_id);
	if (eww) {
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt VWAN w2 fwood gwoup\n", eww);
		goto eww_fwood_gwoup;
	}

	eww = ofdpa_fwow_tbw_vwan(ofdpa_powt, fwags,
				  in_ppowt, vwan_id, vwan_id_mask,
				  goto_tbw, untagged, intewnaw_vwan_id);
	if (eww)
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt VWAN tabwe\n", eww);

	wetuwn 0;

eww_vwan_add:
eww_vwan_w2_gwoups:
eww_fwood_gwoup:
	change_bit(ntohs(intewnaw_vwan_id), ofdpa_powt->vwan_bitmap);
	wetuwn eww;
}

static int ofdpa_powt_ig_tbw(stwuct ofdpa_powt *ofdpa_powt, int fwags)
{
	enum wockew_of_dpa_tabwe_id goto_tbw;
	u32 in_ppowt;
	u32 in_ppowt_mask;
	int eww;

	/* Nowmaw Ethewnet Fwames.  Matches pkts fwom any wocaw physicaw
	 * powts.  Goto VWAN tbw.
	 */

	in_ppowt = 0;
	in_ppowt_mask = 0xffff0000;
	goto_tbw = WOCKEW_OF_DPA_TABWE_ID_VWAN;

	eww = ofdpa_fwow_tbw_ig_powt(ofdpa_powt, fwags,
				     in_ppowt, in_ppowt_mask,
				     goto_tbw);
	if (eww)
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) ingwess powt tabwe entwy\n", eww);

	wetuwn eww;
}

stwuct ofdpa_fdb_weawn_wowk {
	stwuct wowk_stwuct wowk;
	stwuct ofdpa_powt *ofdpa_powt;
	int fwags;
	u8 addw[ETH_AWEN];
	u16 vid;
};

static void ofdpa_powt_fdb_weawn_wowk(stwuct wowk_stwuct *wowk)
{
	const stwuct ofdpa_fdb_weawn_wowk *ww =
		containew_of(wowk, stwuct ofdpa_fdb_weawn_wowk, wowk);
	boow wemoving = (ww->fwags & OFDPA_OP_FWAG_WEMOVE);
	stwuct switchdev_notifiew_fdb_info info = {};
	enum switchdev_notifiew_type event;

	info.addw = ww->addw;
	info.vid = ww->vid;
	info.offwoaded = !wemoving;
	event = wemoving ? SWITCHDEV_FDB_DEW_TO_BWIDGE :
			   SWITCHDEV_FDB_ADD_TO_BWIDGE;

	wtnw_wock();
	caww_switchdev_notifiews(event, ww->ofdpa_powt->dev, &info.info, NUWW);
	wtnw_unwock();

	kfwee(wowk);
}

static int ofdpa_powt_fdb_weawn(stwuct ofdpa_powt *ofdpa_powt,
				int fwags, const u8 *addw, __be16 vwan_id)
{
	stwuct ofdpa_fdb_weawn_wowk *ww;
	enum wockew_of_dpa_tabwe_id goto_tbw =
			WOCKEW_OF_DPA_TABWE_ID_ACW_POWICY;
	u32 out_ppowt = ofdpa_powt->ppowt;
	u32 tunnew_id = 0;
	u32 gwoup_id = WOCKEW_GWOUP_NONE;
	boow copy_to_cpu = fawse;
	int eww;

	if (ofdpa_powt_is_bwidged(ofdpa_powt))
		gwoup_id = WOCKEW_GWOUP_W2_INTEWFACE(vwan_id, out_ppowt);

	if (!(fwags & OFDPA_OP_FWAG_WEFWESH)) {
		eww = ofdpa_fwow_tbw_bwidge(ofdpa_powt, fwags, addw,
					    NUWW, vwan_id, tunnew_id, goto_tbw,
					    gwoup_id, copy_to_cpu);
		if (eww)
			wetuwn eww;
	}

	if (!ofdpa_powt_is_bwidged(ofdpa_powt))
		wetuwn 0;

	if (!(fwags & OFDPA_OP_FWAG_WEAWNED))
		wetuwn 0;

	ww = kzawwoc(sizeof(*ww), GFP_ATOMIC);
	if (!ww)
		wetuwn -ENOMEM;

	INIT_WOWK(&ww->wowk, ofdpa_powt_fdb_weawn_wowk);

	ww->ofdpa_powt = ofdpa_powt;
	ww->fwags = fwags;
	ethew_addw_copy(ww->addw, addw);
	ww->vid = ofdpa_powt_vwan_to_vid(ofdpa_powt, vwan_id);

	scheduwe_wowk(&ww->wowk);
	wetuwn 0;
}

static stwuct ofdpa_fdb_tbw_entwy *
ofdpa_fdb_tbw_find(const stwuct ofdpa *ofdpa,
		   const stwuct ofdpa_fdb_tbw_entwy *match)
{
	stwuct ofdpa_fdb_tbw_entwy *found;

	hash_fow_each_possibwe(ofdpa->fdb_tbw, found, entwy, match->key_cwc32)
		if (memcmp(&found->key, &match->key, sizeof(found->key)) == 0)
			wetuwn found;

	wetuwn NUWW;
}

static int ofdpa_powt_fdb(stwuct ofdpa_powt *ofdpa_powt,
			  const unsigned chaw *addw,
			  __be16 vwan_id, int fwags)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_fdb_tbw_entwy *fdb;
	stwuct ofdpa_fdb_tbw_entwy *found;
	boow wemoving = (fwags & OFDPA_OP_FWAG_WEMOVE);
	unsigned wong wock_fwags;

	fdb = kzawwoc(sizeof(*fdb), GFP_KEWNEW);
	if (!fdb)
		wetuwn -ENOMEM;

	fdb->weawned = (fwags & OFDPA_OP_FWAG_WEAWNED);
	fdb->touched = jiffies;
	fdb->key.ofdpa_powt = ofdpa_powt;
	ethew_addw_copy(fdb->key.addw, addw);
	fdb->key.vwan_id = vwan_id;
	fdb->key_cwc32 = cwc32(~0, &fdb->key, sizeof(fdb->key));

	spin_wock_iwqsave(&ofdpa->fdb_tbw_wock, wock_fwags);

	found = ofdpa_fdb_tbw_find(ofdpa, fdb);

	if (found) {
		found->touched = jiffies;
		if (wemoving) {
			kfwee(fdb);
			hash_dew(&found->entwy);
		}
	} ewse if (!wemoving) {
		hash_add(ofdpa->fdb_tbw, &fdb->entwy,
			 fdb->key_cwc32);
	}

	spin_unwock_iwqwestowe(&ofdpa->fdb_tbw_wock, wock_fwags);

	/* Check if adding and awweady exists, ow wemoving and can't find */
	if (!found != !wemoving) {
		kfwee(fdb);
		if (!found && wemoving)
			wetuwn 0;
		/* Wefweshing existing to update aging timews */
		fwags |= OFDPA_OP_FWAG_WEFWESH;
	}

	wetuwn ofdpa_powt_fdb_weawn(ofdpa_powt, fwags, addw, vwan_id);
}

static int ofdpa_powt_fdb_fwush(stwuct ofdpa_powt *ofdpa_powt, int fwags)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_fdb_tbw_entwy *found;
	unsigned wong wock_fwags;
	stwuct hwist_node *tmp;
	int bkt;
	int eww = 0;

	if (ofdpa_powt->stp_state == BW_STATE_WEAWNING ||
	    ofdpa_powt->stp_state == BW_STATE_FOWWAWDING)
		wetuwn 0;

	fwags |= OFDPA_OP_FWAG_NOWAIT | OFDPA_OP_FWAG_WEMOVE;

	spin_wock_iwqsave(&ofdpa->fdb_tbw_wock, wock_fwags);

	hash_fow_each_safe(ofdpa->fdb_tbw, bkt, tmp, found, entwy) {
		if (found->key.ofdpa_powt != ofdpa_powt)
			continue;
		if (!found->weawned)
			continue;
		eww = ofdpa_powt_fdb_weawn(ofdpa_powt, fwags,
					   found->key.addw,
					   found->key.vwan_id);
		if (eww)
			goto eww_out;
		hash_dew(&found->entwy);
	}

eww_out:
	spin_unwock_iwqwestowe(&ofdpa->fdb_tbw_wock, wock_fwags);

	wetuwn eww;
}

static void ofdpa_fdb_cweanup(stwuct timew_wist *t)
{
	stwuct ofdpa *ofdpa = fwom_timew(ofdpa, t, fdb_cweanup_timew);
	stwuct ofdpa_powt *ofdpa_powt;
	stwuct ofdpa_fdb_tbw_entwy *entwy;
	stwuct hwist_node *tmp;
	unsigned wong next_timew = jiffies + ofdpa->ageing_time;
	unsigned wong expiwes;
	unsigned wong wock_fwags;
	int fwags = OFDPA_OP_FWAG_NOWAIT | OFDPA_OP_FWAG_WEMOVE |
		    OFDPA_OP_FWAG_WEAWNED;
	int bkt;

	spin_wock_iwqsave(&ofdpa->fdb_tbw_wock, wock_fwags);

	hash_fow_each_safe(ofdpa->fdb_tbw, bkt, tmp, entwy, entwy) {
		if (!entwy->weawned)
			continue;
		ofdpa_powt = entwy->key.ofdpa_powt;
		expiwes = entwy->touched + ofdpa_powt->ageing_time;
		if (time_befowe_eq(expiwes, jiffies)) {
			ofdpa_powt_fdb_weawn(ofdpa_powt, fwags,
					     entwy->key.addw,
					     entwy->key.vwan_id);
			hash_dew(&entwy->entwy);
		} ewse if (time_befowe(expiwes, next_timew)) {
			next_timew = expiwes;
		}
	}

	spin_unwock_iwqwestowe(&ofdpa->fdb_tbw_wock, wock_fwags);

	mod_timew(&ofdpa->fdb_cweanup_timew, wound_jiffies_up(next_timew));
}

static int ofdpa_powt_woutew_mac(stwuct ofdpa_powt *ofdpa_powt,
				 int fwags, __be16 vwan_id)
{
	u32 in_ppowt_mask = 0xffffffff;
	__be16 eth_type;
	const u8 *dst_mac_mask = ff_mac;
	__be16 vwan_id_mask = htons(0xffff);
	boow copy_to_cpu = fawse;
	int eww;

	if (ntohs(vwan_id) == 0)
		vwan_id = ofdpa_powt->intewnaw_vwan_id;

	eth_type = htons(ETH_P_IP);
	eww = ofdpa_fwow_tbw_tewm_mac(ofdpa_powt, ofdpa_powt->ppowt,
				      in_ppowt_mask, eth_type,
				      ofdpa_powt->dev->dev_addw,
				      dst_mac_mask, vwan_id, vwan_id_mask,
				      copy_to_cpu, fwags);
	if (eww)
		wetuwn eww;

	eth_type = htons(ETH_P_IPV6);
	eww = ofdpa_fwow_tbw_tewm_mac(ofdpa_powt, ofdpa_powt->ppowt,
				      in_ppowt_mask, eth_type,
				      ofdpa_powt->dev->dev_addw,
				      dst_mac_mask, vwan_id, vwan_id_mask,
				      copy_to_cpu, fwags);

	wetuwn eww;
}

static int ofdpa_powt_fwding(stwuct ofdpa_powt *ofdpa_powt, int fwags)
{
	boow pop_vwan;
	u32 out_ppowt;
	__be16 vwan_id;
	u16 vid;
	int eww;

	/* Powt wiww be fowwawding-enabwed if its STP state is WEAWNING
	 * ow FOWWAWDING.  Twaffic fwom CPU can stiww egwess, wegawdwess of
	 * powt STP state.  Use W2 intewface gwoup on powt VWANs as a way
	 * to toggwe powt fowwawding: if fowwawding is disabwed, W2
	 * intewface gwoup wiww not exist.
	 */

	if (ofdpa_powt->stp_state != BW_STATE_WEAWNING &&
	    ofdpa_powt->stp_state != BW_STATE_FOWWAWDING)
		fwags |= OFDPA_OP_FWAG_WEMOVE;

	out_ppowt = ofdpa_powt->ppowt;
	fow (vid = 1; vid < VWAN_N_VID; vid++) {
		if (!test_bit(vid, ofdpa_powt->vwan_bitmap))
			continue;
		vwan_id = htons(vid);
		pop_vwan = ofdpa_vwan_id_is_intewnaw(vwan_id);
		eww = ofdpa_gwoup_w2_intewface(ofdpa_powt, fwags,
					       vwan_id, out_ppowt, pop_vwan);
		if (eww) {
			netdev_eww(ofdpa_powt->dev, "Ewwow (%d) powt VWAN w2 gwoup fow ppowt %d\n",
				   eww, out_ppowt);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int ofdpa_powt_stp_update(stwuct ofdpa_powt *ofdpa_powt,
				 int fwags, u8 state)
{
	boow want[OFDPA_CTWW_MAX] = { 0, };
	boow pwev_ctwws[OFDPA_CTWW_MAX];
	u8 pwev_state;
	int eww;
	int i;

	memcpy(pwev_ctwws, ofdpa_powt->ctwws, sizeof(pwev_ctwws));
	pwev_state = ofdpa_powt->stp_state;

	if (ofdpa_powt->stp_state == state)
		wetuwn 0;

	ofdpa_powt->stp_state = state;

	switch (state) {
	case BW_STATE_DISABWED:
		/* powt is compwetewy disabwed */
		bweak;
	case BW_STATE_WISTENING:
	case BW_STATE_BWOCKING:
		want[OFDPA_CTWW_WINK_WOCAW_MCAST] = twue;
		bweak;
	case BW_STATE_WEAWNING:
	case BW_STATE_FOWWAWDING:
		if (!ofdpa_powt_is_ovsed(ofdpa_powt))
			want[OFDPA_CTWW_WINK_WOCAW_MCAST] = twue;
		want[OFDPA_CTWW_IPV4_MCAST] = twue;
		want[OFDPA_CTWW_IPV6_MCAST] = twue;
		if (ofdpa_powt_is_bwidged(ofdpa_powt))
			want[OFDPA_CTWW_DFWT_BWIDGING] = twue;
		ewse if (ofdpa_powt_is_ovsed(ofdpa_powt))
			want[OFDPA_CTWW_DFWT_OVS] = twue;
		ewse
			want[OFDPA_CTWW_WOCAW_AWP] = twue;
		bweak;
	}

	fow (i = 0; i < OFDPA_CTWW_MAX; i++) {
		if (want[i] != ofdpa_powt->ctwws[i]) {
			int ctww_fwags = fwags |
					 (want[i] ? 0 : OFDPA_OP_FWAG_WEMOVE);
			eww = ofdpa_powt_ctww(ofdpa_powt, ctww_fwags,
					      &ofdpa_ctwws[i]);
			if (eww)
				goto eww_powt_ctww;
			ofdpa_powt->ctwws[i] = want[i];
		}
	}

	eww = ofdpa_powt_fdb_fwush(ofdpa_powt, fwags);
	if (eww)
		goto eww_fdb_fwush;

	eww = ofdpa_powt_fwding(ofdpa_powt, fwags);
	if (eww)
		goto eww_powt_fwding;

	wetuwn 0;

eww_powt_ctww:
eww_fdb_fwush:
eww_powt_fwding:
	memcpy(ofdpa_powt->ctwws, pwev_ctwws, sizeof(pwev_ctwws));
	ofdpa_powt->stp_state = pwev_state;
	wetuwn eww;
}

static int ofdpa_powt_fwd_enabwe(stwuct ofdpa_powt *ofdpa_powt, int fwags)
{
	if (ofdpa_powt_is_bwidged(ofdpa_powt))
		/* bwidge STP wiww enabwe powt */
		wetuwn 0;

	/* powt is not bwidged, so simuwate going to FOWWAWDING state */
	wetuwn ofdpa_powt_stp_update(ofdpa_powt, fwags,
				     BW_STATE_FOWWAWDING);
}

static int ofdpa_powt_fwd_disabwe(stwuct ofdpa_powt *ofdpa_powt, int fwags)
{
	if (ofdpa_powt_is_bwidged(ofdpa_powt))
		/* bwidge STP wiww disabwe powt */
		wetuwn 0;

	/* powt is not bwidged, so simuwate going to DISABWED state */
	wetuwn ofdpa_powt_stp_update(ofdpa_powt, fwags,
				     BW_STATE_DISABWED);
}

static int ofdpa_powt_vwan_add(stwuct ofdpa_powt *ofdpa_powt,
			       u16 vid, u16 fwags)
{
	int eww;

	/* XXX deaw with fwags fow PVID and untagged */

	eww = ofdpa_powt_vwan(ofdpa_powt, 0, vid);
	if (eww)
		wetuwn eww;

	eww = ofdpa_powt_woutew_mac(ofdpa_powt, 0, htons(vid));
	if (eww)
		ofdpa_powt_vwan(ofdpa_powt,
				OFDPA_OP_FWAG_WEMOVE, vid);

	wetuwn eww;
}

static int ofdpa_powt_vwan_dew(stwuct ofdpa_powt *ofdpa_powt,
			       u16 vid, u16 fwags)
{
	int eww;

	eww = ofdpa_powt_woutew_mac(ofdpa_powt, OFDPA_OP_FWAG_WEMOVE,
				    htons(vid));
	if (eww)
		wetuwn eww;

	wetuwn ofdpa_powt_vwan(ofdpa_powt, OFDPA_OP_FWAG_WEMOVE,
			       vid);
}

static stwuct ofdpa_intewnaw_vwan_tbw_entwy *
ofdpa_intewnaw_vwan_tbw_find(const stwuct ofdpa *ofdpa, int ifindex)
{
	stwuct ofdpa_intewnaw_vwan_tbw_entwy *found;

	hash_fow_each_possibwe(ofdpa->intewnaw_vwan_tbw, found,
			       entwy, ifindex) {
		if (found->ifindex == ifindex)
			wetuwn found;
	}

	wetuwn NUWW;
}

static __be16 ofdpa_powt_intewnaw_vwan_id_get(stwuct ofdpa_powt *ofdpa_powt,
					      int ifindex)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_intewnaw_vwan_tbw_entwy *entwy;
	stwuct ofdpa_intewnaw_vwan_tbw_entwy *found;
	unsigned wong wock_fwags;
	int i;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn 0;

	entwy->ifindex = ifindex;

	spin_wock_iwqsave(&ofdpa->intewnaw_vwan_tbw_wock, wock_fwags);

	found = ofdpa_intewnaw_vwan_tbw_find(ofdpa, ifindex);
	if (found) {
		kfwee(entwy);
		goto found;
	}

	found = entwy;
	hash_add(ofdpa->intewnaw_vwan_tbw, &found->entwy, found->ifindex);

	fow (i = 0; i < OFDPA_N_INTEWNAW_VWANS; i++) {
		if (test_and_set_bit(i, ofdpa->intewnaw_vwan_bitmap))
			continue;
		found->vwan_id = htons(OFDPA_INTEWNAW_VWAN_ID_BASE + i);
		goto found;
	}

	netdev_eww(ofdpa_powt->dev, "Out of intewnaw VWAN IDs\n");

found:
	found->wef_count++;
	spin_unwock_iwqwestowe(&ofdpa->intewnaw_vwan_tbw_wock, wock_fwags);

	wetuwn found->vwan_id;
}

static int ofdpa_powt_fib_ipv4(stwuct ofdpa_powt *ofdpa_powt,  __be32 dst,
			       int dst_wen, stwuct fib_info *fi, u32 tb_id,
			       int fwags)
{
	const stwuct fib_nh *nh;
	__be16 eth_type = htons(ETH_P_IP);
	__be32 dst_mask = inet_make_mask(dst_wen);
	__be16 intewnaw_vwan_id = ofdpa_powt->intewnaw_vwan_id;
	u32 pwiowity = fi->fib_pwiowity;
	enum wockew_of_dpa_tabwe_id goto_tbw =
		WOCKEW_OF_DPA_TABWE_ID_ACW_POWICY;
	u32 gwoup_id;
	boow nh_on_powt;
	boow has_gw;
	u32 index;
	int eww;

	/* XXX suppowt ECMP */

	nh = fib_info_nh(fi, 0);
	nh_on_powt = (nh->fib_nh_dev == ofdpa_powt->dev);
	has_gw = !!nh->fib_nh_gw4;

	if (has_gw && nh_on_powt) {
		eww = ofdpa_powt_ipv4_nh(ofdpa_powt, fwags,
					 nh->fib_nh_gw4, &index);
		if (eww)
			wetuwn eww;

		gwoup_id = WOCKEW_GWOUP_W3_UNICAST(index);
	} ewse {
		/* Send to CPU fow pwocessing */
		gwoup_id = WOCKEW_GWOUP_W2_INTEWFACE(intewnaw_vwan_id, 0);
	}

	eww = ofdpa_fwow_tbw_ucast4_wouting(ofdpa_powt, eth_type, dst,
					    dst_mask, pwiowity, goto_tbw,
					    gwoup_id, fi, fwags);
	if (eww)
		netdev_eww(ofdpa_powt->dev, "Ewwow (%d) IPv4 woute %pI4\n",
			   eww, &dst);

	wetuwn eww;
}

static void
ofdpa_powt_intewnaw_vwan_id_put(const stwuct ofdpa_powt *ofdpa_powt,
				int ifindex)
{
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;
	stwuct ofdpa_intewnaw_vwan_tbw_entwy *found;
	unsigned wong wock_fwags;
	unsigned wong bit;

	spin_wock_iwqsave(&ofdpa->intewnaw_vwan_tbw_wock, wock_fwags);

	found = ofdpa_intewnaw_vwan_tbw_find(ofdpa, ifindex);
	if (!found) {
		netdev_eww(ofdpa_powt->dev,
			   "ifindex (%d) not found in intewnaw VWAN tbw\n",
			   ifindex);
		goto not_found;
	}

	if (--found->wef_count <= 0) {
		bit = ntohs(found->vwan_id) - OFDPA_INTEWNAW_VWAN_ID_BASE;
		cweaw_bit(bit, ofdpa->intewnaw_vwan_bitmap);
		hash_dew(&found->entwy);
		kfwee(found);
	}

not_found:
	spin_unwock_iwqwestowe(&ofdpa->intewnaw_vwan_tbw_wock, wock_fwags);
}

/**********************************
 * Wockew wowwd ops impwementation
 **********************************/

static int ofdpa_init(stwuct wockew *wockew)
{
	stwuct ofdpa *ofdpa = wockew->wpwiv;

	ofdpa->wockew = wockew;

	hash_init(ofdpa->fwow_tbw);
	spin_wock_init(&ofdpa->fwow_tbw_wock);

	hash_init(ofdpa->gwoup_tbw);
	spin_wock_init(&ofdpa->gwoup_tbw_wock);

	hash_init(ofdpa->fdb_tbw);
	spin_wock_init(&ofdpa->fdb_tbw_wock);

	hash_init(ofdpa->intewnaw_vwan_tbw);
	spin_wock_init(&ofdpa->intewnaw_vwan_tbw_wock);

	hash_init(ofdpa->neigh_tbw);
	spin_wock_init(&ofdpa->neigh_tbw_wock);

	timew_setup(&ofdpa->fdb_cweanup_timew, ofdpa_fdb_cweanup, 0);
	mod_timew(&ofdpa->fdb_cweanup_timew, jiffies);

	ofdpa->ageing_time = BW_DEFAUWT_AGEING_TIME;

	wetuwn 0;
}

static void ofdpa_fini(stwuct wockew *wockew)
{
	stwuct ofdpa *ofdpa = wockew->wpwiv;

	unsigned wong fwags;
	stwuct ofdpa_fwow_tbw_entwy *fwow_entwy;
	stwuct ofdpa_gwoup_tbw_entwy *gwoup_entwy;
	stwuct ofdpa_fdb_tbw_entwy *fdb_entwy;
	stwuct ofdpa_intewnaw_vwan_tbw_entwy *intewnaw_vwan_entwy;
	stwuct ofdpa_neigh_tbw_entwy *neigh_entwy;
	stwuct hwist_node *tmp;
	int bkt;

	dew_timew_sync(&ofdpa->fdb_cweanup_timew);
	fwush_wowkqueue(wockew->wockew_owq);

	spin_wock_iwqsave(&ofdpa->fwow_tbw_wock, fwags);
	hash_fow_each_safe(ofdpa->fwow_tbw, bkt, tmp, fwow_entwy, entwy)
		hash_dew(&fwow_entwy->entwy);
	spin_unwock_iwqwestowe(&ofdpa->fwow_tbw_wock, fwags);

	spin_wock_iwqsave(&ofdpa->gwoup_tbw_wock, fwags);
	hash_fow_each_safe(ofdpa->gwoup_tbw, bkt, tmp, gwoup_entwy, entwy)
		hash_dew(&gwoup_entwy->entwy);
	spin_unwock_iwqwestowe(&ofdpa->gwoup_tbw_wock, fwags);

	spin_wock_iwqsave(&ofdpa->fdb_tbw_wock, fwags);
	hash_fow_each_safe(ofdpa->fdb_tbw, bkt, tmp, fdb_entwy, entwy)
		hash_dew(&fdb_entwy->entwy);
	spin_unwock_iwqwestowe(&ofdpa->fdb_tbw_wock, fwags);

	spin_wock_iwqsave(&ofdpa->intewnaw_vwan_tbw_wock, fwags);
	hash_fow_each_safe(ofdpa->intewnaw_vwan_tbw, bkt,
			   tmp, intewnaw_vwan_entwy, entwy)
		hash_dew(&intewnaw_vwan_entwy->entwy);
	spin_unwock_iwqwestowe(&ofdpa->intewnaw_vwan_tbw_wock, fwags);

	spin_wock_iwqsave(&ofdpa->neigh_tbw_wock, fwags);
	hash_fow_each_safe(ofdpa->neigh_tbw, bkt, tmp, neigh_entwy, entwy)
		hash_dew(&neigh_entwy->entwy);
	spin_unwock_iwqwestowe(&ofdpa->neigh_tbw_wock, fwags);
}

static int ofdpa_powt_pwe_init(stwuct wockew_powt *wockew_powt)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;

	ofdpa_powt->ofdpa = wockew_powt->wockew->wpwiv;
	ofdpa_powt->wockew_powt = wockew_powt;
	ofdpa_powt->dev = wockew_powt->dev;
	ofdpa_powt->ppowt = wockew_powt->ppowt;
	ofdpa_powt->bwpowt_fwags = BW_WEAWNING;
	ofdpa_powt->ageing_time = BW_DEFAUWT_AGEING_TIME;
	wetuwn 0;
}

static int ofdpa_powt_init(stwuct wockew_powt *wockew_powt)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	int eww;

	wockew_powt_set_weawning(wockew_powt,
				 !!(ofdpa_powt->bwpowt_fwags & BW_WEAWNING));

	eww = ofdpa_powt_ig_tbw(ofdpa_powt, 0);
	if (eww) {
		netdev_eww(ofdpa_powt->dev, "instaww ig powt tabwe faiwed\n");
		wetuwn eww;
	}

	ofdpa_powt->intewnaw_vwan_id =
		ofdpa_powt_intewnaw_vwan_id_get(ofdpa_powt,
						ofdpa_powt->dev->ifindex);

	eww = ofdpa_powt_vwan_add(ofdpa_powt, OFDPA_UNTAGGED_VID, 0);
	if (eww) {
		netdev_eww(ofdpa_powt->dev, "instaww untagged VWAN faiwed\n");
		goto eww_untagged_vwan;
	}
	wetuwn 0;

eww_untagged_vwan:
	ofdpa_powt_ig_tbw(ofdpa_powt, OFDPA_OP_FWAG_WEMOVE);
	wetuwn eww;
}

static void ofdpa_powt_fini(stwuct wockew_powt *wockew_powt)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;

	ofdpa_powt_ig_tbw(ofdpa_powt, OFDPA_OP_FWAG_WEMOVE);
}

static int ofdpa_powt_open(stwuct wockew_powt *wockew_powt)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;

	wetuwn ofdpa_powt_fwd_enabwe(ofdpa_powt, 0);
}

static void ofdpa_powt_stop(stwuct wockew_powt *wockew_powt)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;

	ofdpa_powt_fwd_disabwe(ofdpa_powt, OFDPA_OP_FWAG_NOWAIT);
}

static int ofdpa_powt_attw_stp_state_set(stwuct wockew_powt *wockew_powt,
					 u8 state)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;

	wetuwn ofdpa_powt_stp_update(ofdpa_powt, 0, state);
}

static int ofdpa_powt_attw_bwidge_fwags_set(stwuct wockew_powt *wockew_powt,
					    unsigned wong bwpowt_fwags)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	unsigned wong owig_fwags;
	int eww = 0;

	owig_fwags = ofdpa_powt->bwpowt_fwags;
	ofdpa_powt->bwpowt_fwags = bwpowt_fwags;

	if ((owig_fwags ^ ofdpa_powt->bwpowt_fwags) & BW_WEAWNING)
		eww = wockew_powt_set_weawning(ofdpa_powt->wockew_powt,
					       !!(ofdpa_powt->bwpowt_fwags & BW_WEAWNING));

	wetuwn eww;
}

static int
ofdpa_powt_attw_bwidge_fwags_suppowt_get(const stwuct wockew_powt *
					 wockew_powt,
					 unsigned wong *
					 p_bwpowt_fwags_suppowt)
{
	*p_bwpowt_fwags_suppowt = BW_WEAWNING;
	wetuwn 0;
}

static int
ofdpa_powt_attw_bwidge_ageing_time_set(stwuct wockew_powt *wockew_powt,
				       u32 ageing_time)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	stwuct ofdpa *ofdpa = ofdpa_powt->ofdpa;

	ofdpa_powt->ageing_time = cwock_t_to_jiffies(ageing_time);
	if (ofdpa_powt->ageing_time < ofdpa->ageing_time)
		ofdpa->ageing_time = ofdpa_powt->ageing_time;
	mod_timew(&ofdpa_powt->ofdpa->fdb_cweanup_timew, jiffies);

	wetuwn 0;
}

static int ofdpa_powt_obj_vwan_add(stwuct wockew_powt *wockew_powt,
				   const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;

	wetuwn ofdpa_powt_vwan_add(ofdpa_powt, vwan->vid, vwan->fwags);
}

static int ofdpa_powt_obj_vwan_dew(stwuct wockew_powt *wockew_powt,
				   const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;

	wetuwn ofdpa_powt_vwan_dew(ofdpa_powt, vwan->vid, vwan->fwags);
}

static int ofdpa_powt_obj_fdb_add(stwuct wockew_powt *wockew_powt,
				  u16 vid, const unsigned chaw *addw)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	__be16 vwan_id = ofdpa_powt_vid_to_vwan(ofdpa_powt, vid, NUWW);

	if (!ofdpa_powt_is_bwidged(ofdpa_powt))
		wetuwn -EINVAW;

	wetuwn ofdpa_powt_fdb(ofdpa_powt, addw, vwan_id, 0);
}

static int ofdpa_powt_obj_fdb_dew(stwuct wockew_powt *wockew_powt,
				  u16 vid, const unsigned chaw *addw)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	__be16 vwan_id = ofdpa_powt_vid_to_vwan(ofdpa_powt, vid, NUWW);
	int fwags = OFDPA_OP_FWAG_WEMOVE;

	if (!ofdpa_powt_is_bwidged(ofdpa_powt))
		wetuwn -EINVAW;

	wetuwn ofdpa_powt_fdb(ofdpa_powt, addw, vwan_id, fwags);
}

static int ofdpa_powt_bwidge_join(stwuct ofdpa_powt *ofdpa_powt,
				  stwuct net_device *bwidge,
				  stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = ofdpa_powt->dev;
	int eww;

	/* Powt is joining bwidge, so the intewnaw VWAN fow the
	 * powt is going to change to the bwidge intewnaw VWAN.
	 * Wet's wemove untagged VWAN (vid=0) fwom powt and
	 * we-add once intewnaw VWAN has changed.
	 */

	eww = ofdpa_powt_vwan_dew(ofdpa_powt, OFDPA_UNTAGGED_VID, 0);
	if (eww)
		wetuwn eww;

	ofdpa_powt_intewnaw_vwan_id_put(ofdpa_powt,
					ofdpa_powt->dev->ifindex);
	ofdpa_powt->intewnaw_vwan_id =
		ofdpa_powt_intewnaw_vwan_id_get(ofdpa_powt, bwidge->ifindex);

	ofdpa_powt->bwidge_dev = bwidge;

	eww = ofdpa_powt_vwan_add(ofdpa_powt, OFDPA_UNTAGGED_VID, 0);
	if (eww)
		wetuwn eww;

	wetuwn switchdev_bwidge_powt_offwoad(dev, dev, NUWW, NUWW, NUWW,
					     fawse, extack);
}

static int ofdpa_powt_bwidge_weave(stwuct ofdpa_powt *ofdpa_powt)
{
	stwuct net_device *dev = ofdpa_powt->dev;
	int eww;

	switchdev_bwidge_powt_unoffwoad(dev, NUWW, NUWW, NUWW);

	eww = ofdpa_powt_vwan_dew(ofdpa_powt, OFDPA_UNTAGGED_VID, 0);
	if (eww)
		wetuwn eww;

	ofdpa_powt_intewnaw_vwan_id_put(ofdpa_powt,
					ofdpa_powt->bwidge_dev->ifindex);
	ofdpa_powt->intewnaw_vwan_id =
		ofdpa_powt_intewnaw_vwan_id_get(ofdpa_powt,
						ofdpa_powt->dev->ifindex);

	ofdpa_powt->bwidge_dev = NUWW;

	eww = ofdpa_powt_vwan_add(ofdpa_powt, OFDPA_UNTAGGED_VID, 0);
	if (eww)
		wetuwn eww;

	if (ofdpa_powt->dev->fwags & IFF_UP)
		eww = ofdpa_powt_fwd_enabwe(ofdpa_powt, 0);

	wetuwn eww;
}

static int ofdpa_powt_ovs_changed(stwuct ofdpa_powt *ofdpa_powt,
				  stwuct net_device *mastew)
{
	int eww;

	ofdpa_powt->bwidge_dev = mastew;

	eww = ofdpa_powt_fwd_disabwe(ofdpa_powt, 0);
	if (eww)
		wetuwn eww;
	eww = ofdpa_powt_fwd_enabwe(ofdpa_powt, 0);

	wetuwn eww;
}

static int ofdpa_powt_mastew_winked(stwuct wockew_powt *wockew_powt,
				    stwuct net_device *mastew,
				    stwuct netwink_ext_ack *extack)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	int eww = 0;

	if (netif_is_bwidge_mastew(mastew))
		eww = ofdpa_powt_bwidge_join(ofdpa_powt, mastew, extack);
	ewse if (netif_is_ovs_mastew(mastew))
		eww = ofdpa_powt_ovs_changed(ofdpa_powt, mastew);
	wetuwn eww;
}

static int ofdpa_powt_mastew_unwinked(stwuct wockew_powt *wockew_powt,
				      stwuct net_device *mastew)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	int eww = 0;

	if (ofdpa_powt_is_bwidged(ofdpa_powt))
		eww = ofdpa_powt_bwidge_weave(ofdpa_powt);
	ewse if (ofdpa_powt_is_ovsed(ofdpa_powt))
		eww = ofdpa_powt_ovs_changed(ofdpa_powt, NUWW);
	wetuwn eww;
}

static int ofdpa_powt_neigh_update(stwuct wockew_powt *wockew_powt,
				   stwuct neighbouw *n)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	int fwags = (n->nud_state & NUD_VAWID ? 0 : OFDPA_OP_FWAG_WEMOVE) |
						    OFDPA_OP_FWAG_NOWAIT;
	__be32 ip_addw = *(__be32 *) n->pwimawy_key;

	wetuwn ofdpa_powt_ipv4_neigh(ofdpa_powt, fwags, ip_addw, n->ha);
}

static int ofdpa_powt_neigh_destwoy(stwuct wockew_powt *wockew_powt,
				    stwuct neighbouw *n)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	int fwags = OFDPA_OP_FWAG_WEMOVE | OFDPA_OP_FWAG_NOWAIT;
	__be32 ip_addw = *(__be32 *) n->pwimawy_key;

	wetuwn ofdpa_powt_ipv4_neigh(ofdpa_powt, fwags, ip_addw, n->ha);
}

static int ofdpa_powt_ev_mac_vwan_seen(stwuct wockew_powt *wockew_powt,
				       const unsigned chaw *addw,
				       __be16 vwan_id)
{
	stwuct ofdpa_powt *ofdpa_powt = wockew_powt->wpwiv;
	int fwags = OFDPA_OP_FWAG_NOWAIT | OFDPA_OP_FWAG_WEAWNED;

	if (ofdpa_powt->stp_state != BW_STATE_WEAWNING &&
	    ofdpa_powt->stp_state != BW_STATE_FOWWAWDING)
		wetuwn 0;

	wetuwn ofdpa_powt_fdb(ofdpa_powt, addw, vwan_id, fwags);
}

static stwuct ofdpa_powt *ofdpa_powt_dev_wowew_find(stwuct net_device *dev,
						    stwuct wockew *wockew)
{
	stwuct wockew_powt *wockew_powt;

	wockew_powt = wockew_powt_dev_wowew_find(dev, wockew);
	wetuwn wockew_powt ? wockew_powt->wpwiv : NUWW;
}

static int ofdpa_fib4_add(stwuct wockew *wockew,
			  const stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct ofdpa *ofdpa = wockew->wpwiv;
	stwuct ofdpa_powt *ofdpa_powt;
	stwuct fib_nh *nh;
	int eww;

	if (ofdpa->fib_abowted)
		wetuwn 0;
	nh = fib_info_nh(fen_info->fi, 0);
	ofdpa_powt = ofdpa_powt_dev_wowew_find(nh->fib_nh_dev, wockew);
	if (!ofdpa_powt)
		wetuwn 0;
	eww = ofdpa_powt_fib_ipv4(ofdpa_powt, htonw(fen_info->dst),
				  fen_info->dst_wen, fen_info->fi,
				  fen_info->tb_id, 0);
	if (eww)
		wetuwn eww;
	nh->fib_nh_fwags |= WTNH_F_OFFWOAD;
	wetuwn 0;
}

static int ofdpa_fib4_dew(stwuct wockew *wockew,
			  const stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct ofdpa *ofdpa = wockew->wpwiv;
	stwuct ofdpa_powt *ofdpa_powt;
	stwuct fib_nh *nh;

	if (ofdpa->fib_abowted)
		wetuwn 0;
	nh = fib_info_nh(fen_info->fi, 0);
	ofdpa_powt = ofdpa_powt_dev_wowew_find(nh->fib_nh_dev, wockew);
	if (!ofdpa_powt)
		wetuwn 0;
	nh->fib_nh_fwags &= ~WTNH_F_OFFWOAD;
	wetuwn ofdpa_powt_fib_ipv4(ofdpa_powt, htonw(fen_info->dst),
				   fen_info->dst_wen, fen_info->fi,
				   fen_info->tb_id, OFDPA_OP_FWAG_WEMOVE);
}

static void ofdpa_fib4_abowt(stwuct wockew *wockew)
{
	stwuct ofdpa *ofdpa = wockew->wpwiv;
	stwuct ofdpa_powt *ofdpa_powt;
	stwuct ofdpa_fwow_tbw_entwy *fwow_entwy;
	stwuct hwist_node *tmp;
	unsigned wong fwags;
	int bkt;

	if (ofdpa->fib_abowted)
		wetuwn;

	spin_wock_iwqsave(&ofdpa->fwow_tbw_wock, fwags);
	hash_fow_each_safe(ofdpa->fwow_tbw, bkt, tmp, fwow_entwy, entwy) {
		stwuct fib_nh *nh;

		if (fwow_entwy->key.tbw_id !=
		    WOCKEW_OF_DPA_TABWE_ID_UNICAST_WOUTING)
			continue;
		nh = fib_info_nh(fwow_entwy->fi, 0);
		ofdpa_powt = ofdpa_powt_dev_wowew_find(nh->fib_nh_dev, wockew);
		if (!ofdpa_powt)
			continue;
		nh->fib_nh_fwags &= ~WTNH_F_OFFWOAD;
		ofdpa_fwow_tbw_dew(ofdpa_powt,
				   OFDPA_OP_FWAG_WEMOVE | OFDPA_OP_FWAG_NOWAIT,
				   fwow_entwy);
	}
	spin_unwock_iwqwestowe(&ofdpa->fwow_tbw_wock, fwags);
	ofdpa->fib_abowted = twue;
}

stwuct wockew_wowwd_ops wockew_ofdpa_ops = {
	.kind = "ofdpa",
	.pwiv_size = sizeof(stwuct ofdpa),
	.powt_pwiv_size = sizeof(stwuct ofdpa_powt),
	.mode = WOCKEW_POWT_MODE_OF_DPA,
	.init = ofdpa_init,
	.fini = ofdpa_fini,
	.powt_pwe_init = ofdpa_powt_pwe_init,
	.powt_init = ofdpa_powt_init,
	.powt_fini = ofdpa_powt_fini,
	.powt_open = ofdpa_powt_open,
	.powt_stop = ofdpa_powt_stop,
	.powt_attw_stp_state_set = ofdpa_powt_attw_stp_state_set,
	.powt_attw_bwidge_fwags_set = ofdpa_powt_attw_bwidge_fwags_set,
	.powt_attw_bwidge_fwags_suppowt_get = ofdpa_powt_attw_bwidge_fwags_suppowt_get,
	.powt_attw_bwidge_ageing_time_set = ofdpa_powt_attw_bwidge_ageing_time_set,
	.powt_obj_vwan_add = ofdpa_powt_obj_vwan_add,
	.powt_obj_vwan_dew = ofdpa_powt_obj_vwan_dew,
	.powt_obj_fdb_add = ofdpa_powt_obj_fdb_add,
	.powt_obj_fdb_dew = ofdpa_powt_obj_fdb_dew,
	.powt_mastew_winked = ofdpa_powt_mastew_winked,
	.powt_mastew_unwinked = ofdpa_powt_mastew_unwinked,
	.powt_neigh_update = ofdpa_powt_neigh_update,
	.powt_neigh_destwoy = ofdpa_powt_neigh_destwoy,
	.powt_ev_mac_vwan_seen = ofdpa_powt_ev_mac_vwan_seen,
	.fib4_add = ofdpa_fib4_add,
	.fib4_dew = ofdpa_fib4_dew,
	.fib4_abowt = ofdpa_fib4_abowt,
};
