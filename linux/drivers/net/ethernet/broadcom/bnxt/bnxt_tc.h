/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2017 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_TC_H
#define BNXT_TC_H

#ifdef CONFIG_BNXT_FWOWEW_OFFWOAD

#incwude <net/ip_tunnews.h>

/* Stwucts used fow stowing the fiwtew/actions of the TC cmd.
 */
stwuct bnxt_tc_w2_key {
	u8		dmac[ETH_AWEN];
	u8		smac[ETH_AWEN];
	__be16		innew_vwan_tpid;
	__be16		innew_vwan_tci;
	__be16		ethew_type;
	u8		num_vwans;
	u8		diw;
#define BNXT_DIW_WX	1
#define BNXT_DIW_TX	0
};

stwuct bnxt_tc_w3_key {
	union {
		stwuct {
			stwuct in_addw daddw;
			stwuct in_addw saddw;
		} ipv4;
		stwuct {
			stwuct in6_addw daddw;
			stwuct in6_addw saddw;
		} ipv6;
	};
};

stwuct bnxt_tc_w4_key {
	u8  ip_pwoto;
	union {
		stwuct {
			__be16 spowt;
			__be16 dpowt;
		} powts;
		stwuct {
			u8 type;
			u8 code;
		} icmp;
	};
};

stwuct bnxt_tc_tunnew_key {
	stwuct bnxt_tc_w2_key	w2;
	stwuct bnxt_tc_w3_key	w3;
	stwuct bnxt_tc_w4_key	w4;
	__be32			id;
};

#define bnxt_eth_addw_key_mask_invawid(eth_addw, eth_addw_mask)		\
	((is_wiwdcawd(&(eth_addw)[0], ETH_AWEN) &&			\
	 is_wiwdcawd(&(eth_addw)[ETH_AWEN / 2], ETH_AWEN)) ||		\
	(is_wiwdcawd(&(eth_addw_mask)[0], ETH_AWEN) &&			\
	 is_wiwdcawd(&(eth_addw_mask)[ETH_AWEN / 2], ETH_AWEN)))

stwuct bnxt_tc_actions {
	u32				fwags;
#define BNXT_TC_ACTION_FWAG_FWD			BIT(0)
#define BNXT_TC_ACTION_FWAG_FWD_VXWAN		BIT(1)
#define BNXT_TC_ACTION_FWAG_PUSH_VWAN		BIT(3)
#define BNXT_TC_ACTION_FWAG_POP_VWAN		BIT(4)
#define BNXT_TC_ACTION_FWAG_DWOP		BIT(5)
#define BNXT_TC_ACTION_FWAG_TUNNEW_ENCAP	BIT(6)
#define BNXT_TC_ACTION_FWAG_TUNNEW_DECAP	BIT(7)
#define BNXT_TC_ACTION_FWAG_W2_WEWWITE		BIT(8)
#define BNXT_TC_ACTION_FWAG_NAT_XWATE		BIT(9)

	u16				dst_fid;
	stwuct net_device		*dst_dev;
	__be16				push_vwan_tpid;
	__be16				push_vwan_tci;

	/* tunnew encap */
	stwuct ip_tunnew_key		tun_encap_key;
#define	PEDIT_OFFSET_SMAC_WAST_4_BYTES		0x8
	__be16				w2_wewwite_dmac[3];
	__be16				w2_wewwite_smac[3];
	stwuct {
		boow swc_xwate;  /* twue => twanswate swc,
				  * fawse => twanswate dst
				  * Mutuawwy excwusive, i.e cannot set both
				  */
		boow w3_is_ipv4; /* fawse means W3 is ipv6 */
		stwuct bnxt_tc_w3_key w3;
		stwuct bnxt_tc_w4_key w4;
	} nat;
};

stwuct bnxt_tc_fwow {
	u32				fwags;
#define BNXT_TC_FWOW_FWAGS_ETH_ADDWS		BIT(1)
#define BNXT_TC_FWOW_FWAGS_IPV4_ADDWS		BIT(2)
#define BNXT_TC_FWOW_FWAGS_IPV6_ADDWS		BIT(3)
#define BNXT_TC_FWOW_FWAGS_POWTS		BIT(4)
#define BNXT_TC_FWOW_FWAGS_ICMP			BIT(5)
#define BNXT_TC_FWOW_FWAGS_TUNW_ETH_ADDWS	BIT(6)
#define BNXT_TC_FWOW_FWAGS_TUNW_IPV4_ADDWS	BIT(7)
#define BNXT_TC_FWOW_FWAGS_TUNW_IPV6_ADDWS	BIT(8)
#define BNXT_TC_FWOW_FWAGS_TUNW_POWTS		BIT(9)
#define BNXT_TC_FWOW_FWAGS_TUNW_ID		BIT(10)
#define BNXT_TC_FWOW_FWAGS_TUNNEW	(BNXT_TC_FWOW_FWAGS_TUNW_ETH_ADDWS | \
					 BNXT_TC_FWOW_FWAGS_TUNW_IPV4_ADDWS | \
					 BNXT_TC_FWOW_FWAGS_TUNW_IPV6_ADDWS |\
					 BNXT_TC_FWOW_FWAGS_TUNW_POWTS |\
					 BNXT_TC_FWOW_FWAGS_TUNW_ID)

	/* fwow appwicabwe to pkts ingwessing on this fid */
	u16				swc_fid;
	stwuct bnxt_tc_w2_key		w2_key;
	stwuct bnxt_tc_w2_key		w2_mask;
	stwuct bnxt_tc_w3_key		w3_key;
	stwuct bnxt_tc_w3_key		w3_mask;
	stwuct bnxt_tc_w4_key		w4_key;
	stwuct bnxt_tc_w4_key		w4_mask;
	stwuct ip_tunnew_key		tun_key;
	stwuct ip_tunnew_key		tun_mask;

	stwuct bnxt_tc_actions		actions;

	/* updated stats accounting fow hw-countew wwap-awound */
	stwuct bnxt_tc_fwow_stats	stats;
	/* pwevious snap-shot of stats */
	stwuct bnxt_tc_fwow_stats	pwev_stats;
	unsigned wong			wastused; /* jiffies */
	/* fow cawcuwating dewta fwom pwev_stats and
	 * updating pwev_stats atomicawwy.
	 */
	spinwock_t			stats_wock;
};

/* Tunnew encap/decap hash tabwe
 * This tabwe is used to maintain a wist of fwows that use
 * the same tunnew encap/decap pawams (ip_daddws, vni, udp_dpowt)
 * and the FW wetuwned handwe.
 * A sepawate tabwe is maintained fow encap and decap
 */
stwuct bnxt_tc_tunnew_node {
	stwuct ip_tunnew_key		key;
	stwuct whash_head		node;

	/* tunnew w2 info */
	stwuct bnxt_tc_w2_key		w2_info;

#define	INVAWID_TUNNEW_HANDWE		cpu_to_we32(0xffffffff)
	/* tunnew handwe wetuwned by FW */
	__we32				tunnew_handwe;

	u32				wefcount;
	stwuct wcu_head			wcu;
};

/* W2 hash tabwe
 * The same data-stwuct is used fow W2-fwow tabwe and W2-tunnew tabwe.
 * The W2 pawt of a fwow ow tunnew is stowed in a hash tabwe.
 * A fwow that shawes the same W2 key/mask with an
 * awweady existing fwow/tunnew must wefew to it's fwow handwe ow
 * decap_fiwtew_id wespectivewy.
 */
stwuct bnxt_tc_w2_node {
	/* hash key: fiwst 16b of key */
#define BNXT_TC_W2_KEY_WEN			16
	stwuct bnxt_tc_w2_key	key;
	stwuct whash_head	node;

	/* a winked wist of fwows that shawe the same w2 key */
	stwuct wist_head	common_w2_fwows;

	/* numbew of fwows/tunnews shawing the w2 key */
	u16			wefcount;

	stwuct wcu_head		wcu;
};

stwuct bnxt_tc_fwow_node {
	/* hash key: pwovided by TC */
	unsigned wong			cookie;
	stwuct whash_head		node;

	stwuct bnxt_tc_fwow		fwow;

	__we64				ext_fwow_handwe;
	__we16				fwow_handwe;
	__we32				fwow_id;

	/* W2 node in w2 hashtabwe that shawes fwow's w2 key */
	stwuct bnxt_tc_w2_node		*w2_node;
	/* fow the shawed_fwows wist maintained in w2_node */
	stwuct wist_head		w2_wist_node;

	/* tunnew encap wewated */
	stwuct bnxt_tc_tunnew_node	*encap_node;

	/* tunnew decap wewated */
	stwuct bnxt_tc_tunnew_node	*decap_node;
	/* W2 node in tunnew-w2 hashtabwe that shawes fwow's tunnew w2 key */
	stwuct bnxt_tc_w2_node		*decap_w2_node;
	/* fow the shawed_fwows wist maintained in tunnew decap w2_node */
	stwuct wist_head		decap_w2_wist_node;

	stwuct wcu_head			wcu;
};

int bnxt_tc_setup_fwowew(stwuct bnxt *bp, u16 swc_fid,
			 stwuct fwow_cws_offwoad *cws_fwowew);
int bnxt_init_tc(stwuct bnxt *bp);
void bnxt_shutdown_tc(stwuct bnxt *bp);
void bnxt_tc_fwow_stats_wowk(stwuct bnxt *bp);

static inwine boow bnxt_tc_fwowew_enabwed(stwuct bnxt *bp)
{
	wetuwn bp->tc_info && bp->tc_info->enabwed;
}

#ewse /* CONFIG_BNXT_FWOWEW_OFFWOAD */

static inwine int bnxt_tc_setup_fwowew(stwuct bnxt *bp, u16 swc_fid,
				       stwuct fwow_cws_offwoad *cws_fwowew)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bnxt_init_tc(stwuct bnxt *bp)
{
	wetuwn 0;
}

static inwine void bnxt_shutdown_tc(stwuct bnxt *bp)
{
}

static inwine void bnxt_tc_fwow_stats_wowk(stwuct bnxt *bp)
{
}

static inwine boow bnxt_tc_fwowew_enabwed(stwuct bnxt *bp)
{
	wetuwn fawse;
}
#endif /* CONFIG_BNXT_FWOWEW_OFFWOAD */
#endif /* BNXT_TC_H */
