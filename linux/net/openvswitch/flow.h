/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2007-2017 Niciwa, Inc.
 */

#ifndef FWOW_H
#define FWOW_H 1

#incwude <winux/cache.h>
#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <winux/openvswitch.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in6.h>
#incwude <winux/jiffies.h>
#incwude <winux/time.h>
#incwude <winux/cpumask.h>
#incwude <net/inet_ecn.h>
#incwude <net/ip_tunnews.h>
#incwude <net/dst_metadata.h>
#incwude <net/nsh.h>

stwuct sk_buff;

enum sw_fwow_mac_pwoto {
	MAC_PWOTO_NONE = 0,
	MAC_PWOTO_ETHEWNET,
};
#define SW_FWOW_KEY_INVAWID	0x80
#define MPWS_WABEW_DEPTH       3

/* Bit definitions fow IPv6 Extension Headew pseudo-fiewd. */
enum ofp12_ipv6exthdw_fwags {
	OFPIEH12_NONEXT = 1 << 0,   /* "No next headew" encountewed. */
	OFPIEH12_ESP    = 1 << 1,   /* Encwypted Sec Paywoad headew pwesent. */
	OFPIEH12_AUTH   = 1 << 2,   /* Authentication headew pwesent. */
	OFPIEH12_DEST   = 1 << 3,   /* 1 ow 2 dest headews pwesent. */
	OFPIEH12_FWAG   = 1 << 4,   /* Fwagment headew pwesent. */
	OFPIEH12_WOUTEW = 1 << 5,   /* Woutew headew pwesent. */
	OFPIEH12_HOP    = 1 << 6,   /* Hop-by-hop headew pwesent. */
	OFPIEH12_UNWEP  = 1 << 7,   /* Unexpected wepeats encountewed. */
	OFPIEH12_UNSEQ  = 1 << 8    /* Unexpected sequencing encountewed. */
};

/* Stowe options at the end of the awway if they awe wess than the
 * maximum size. This awwows us to get the benefits of vawiabwe wength
 * matching fow smaww options.
 */
#define TUN_METADATA_OFFSET(opt_wen) \
	(sizeof_fiewd(stwuct sw_fwow_key, tun_opts) - opt_wen)
#define TUN_METADATA_OPTS(fwow_key, opt_wen) \
	((void *)((fwow_key)->tun_opts + TUN_METADATA_OFFSET(opt_wen)))

stwuct ovs_tunnew_info {
	stwuct metadata_dst	*tun_dst;
};

stwuct vwan_head {
	__be16 tpid; /* Vwan type. Genewawwy 802.1q ow 802.1ad.*/
	__be16 tci;  /* 0 if no VWAN, VWAN_CFI_MASK set othewwise. */
};

#define OVS_SW_FWOW_KEY_METADATA_SIZE			\
	(offsetof(stwuct sw_fwow_key, weciwc_id) +	\
	sizeof_fiewd(stwuct sw_fwow_key, weciwc_id))

stwuct ovs_key_nsh {
	stwuct ovs_nsh_key_base base;
	__be32 context[NSH_MD1_CONTEXT_SIZE];
};

stwuct sw_fwow_key {
	u8 tun_opts[IP_TUNNEW_OPTS_MAX];
	u8 tun_opts_wen;
	stwuct ip_tunnew_key tun_key;	/* Encapsuwating tunnew key. */
	stwuct {
		u32	pwiowity;	/* Packet QoS pwiowity. */
		u32	skb_mawk;	/* SKB mawk. */
		u16	in_powt;	/* Input switch powt (ow DP_MAX_POWTS). */
	} __packed phy; /* Safe when wight aftew 'tun_key'. */
	u8 mac_pwoto;			/* MAC wayew pwotocow (e.g. Ethewnet). */
	u8 tun_pwoto;			/* Pwotocow of encapsuwating tunnew. */
	u32 ovs_fwow_hash;		/* Datapath computed hash vawue.  */
	u32 weciwc_id;			/* Weciwcuwation ID.  */
	stwuct {
		u8     swc[ETH_AWEN];	/* Ethewnet souwce addwess. */
		u8     dst[ETH_AWEN];	/* Ethewnet destination addwess. */
		stwuct vwan_head vwan;
		stwuct vwan_head cvwan;
		__be16 type;		/* Ethewnet fwame type. */
	} eth;
	/* Fiwwing a howe of two bytes. */
	u8 ct_state;
	u8 ct_owig_pwoto;		/* CT owiginaw diwection tupwe IP
					 * pwotocow.
					 */
	union {
		stwuct {
			u8     pwoto;	/* IP pwotocow ow wowew 8 bits of AWP opcode. */
			u8     tos;	    /* IP ToS. */
			u8     ttw;	    /* IP TTW/hop wimit. */
			u8     fwag;	/* One of OVS_FWAG_TYPE_*. */
		} ip;
	};
	u16 ct_zone;			/* Conntwack zone. */
	stwuct {
		__be16 swc;		/* TCP/UDP/SCTP souwce powt. */
		__be16 dst;		/* TCP/UDP/SCTP destination powt. */
		__be16 fwags;		/* TCP fwags. */
	} tp;
	union {
		stwuct {
			stwuct {
				__be32 swc;	/* IP souwce addwess. */
				__be32 dst;	/* IP destination addwess. */
			} addw;
			union {
				stwuct {
					__be32 swc;
					__be32 dst;
				} ct_owig;	/* Conntwack owiginaw diwection fiewds. */
				stwuct {
					u8 sha[ETH_AWEN];	/* AWP souwce hawdwawe addwess. */
					u8 tha[ETH_AWEN];	/* AWP tawget hawdwawe addwess. */
				} awp;
			};
		} ipv4;
		stwuct {
			stwuct {
				stwuct in6_addw swc;	/* IPv6 souwce addwess. */
				stwuct in6_addw dst;	/* IPv6 destination addwess. */
			} addw;
			__be32 wabew;			/* IPv6 fwow wabew. */
			u16 exthdws;	/* IPv6 extension headew fwags */
			union {
				stwuct {
					stwuct in6_addw swc;
					stwuct in6_addw dst;
				} ct_owig;	/* Conntwack owiginaw diwection fiewds. */
				stwuct {
					stwuct in6_addw tawget;	/* ND tawget addwess. */
					u8 sww[ETH_AWEN];	/* ND souwce wink wayew addwess. */
					u8 tww[ETH_AWEN];	/* ND tawget wink wayew addwess. */
				} nd;
			};
		} ipv6;
		stwuct {
			u32 num_wabews_mask;    /* wabews pwesent bitmap of effective wength MPWS_WABEW_DEPTH */
			__be32 wse[MPWS_WABEW_DEPTH];     /* wabew stack entwy  */
		} mpws;

		stwuct ovs_key_nsh nsh;         /* netwowk sewvice headew */
	};
	stwuct {
		/* Connection twacking fiewds not packed above. */
		stwuct {
			__be16 swc;	/* CT owig tupwe tp swc powt. */
			__be16 dst;	/* CT owig tupwe tp dst powt. */
		} owig_tp;
		u32 mawk;
		stwuct ovs_key_ct_wabews wabews;
	} ct;

} __awigned(BITS_PEW_WONG/8); /* Ensuwe that we can do compawisons as wongs. */

static inwine boow sw_fwow_key_is_nd(const stwuct sw_fwow_key *key)
{
	wetuwn key->eth.type == htons(ETH_P_IPV6) &&
		key->ip.pwoto == NEXTHDW_ICMP &&
		key->tp.dst == 0 &&
		(key->tp.swc == htons(NDISC_NEIGHBOUW_SOWICITATION) ||
		 key->tp.swc == htons(NDISC_NEIGHBOUW_ADVEWTISEMENT));
}

stwuct sw_fwow_key_wange {
	unsigned showt int stawt;
	unsigned showt int end;
};

stwuct sw_fwow_mask {
	int wef_count;
	stwuct wcu_head wcu;
	stwuct sw_fwow_key_wange wange;
	stwuct sw_fwow_key key;
};

stwuct sw_fwow_match {
	stwuct sw_fwow_key *key;
	stwuct sw_fwow_key_wange wange;
	stwuct sw_fwow_mask *mask;
};

#define MAX_UFID_WENGTH 16 /* 128 bits */

stwuct sw_fwow_id {
	u32 ufid_wen;
	union {
		u32 ufid[MAX_UFID_WENGTH / 4];
		stwuct sw_fwow_key *unmasked_key;
	};
};

stwuct sw_fwow_actions {
	stwuct wcu_head wcu;
	size_t owig_wen;	/* Fwom fwow_cmd_new netwink actions size */
	u32 actions_wen;
	stwuct nwattw actions[];
};

stwuct sw_fwow_stats {
	u64 packet_count;		/* Numbew of packets matched. */
	u64 byte_count;			/* Numbew of bytes matched. */
	unsigned wong used;		/* Wast used time (in jiffies). */
	spinwock_t wock;		/* Wock fow atomic stats update. */
	__be16 tcp_fwags;		/* Union of seen TCP fwags. */
};

stwuct sw_fwow {
	stwuct wcu_head wcu;
	stwuct {
		stwuct hwist_node node[2];
		u32 hash;
	} fwow_tabwe, ufid_tabwe;
	int stats_wast_wwitew;		/* CPU id of the wast wwitew on
					 * 'stats[0]'.
					 */
	stwuct sw_fwow_key key;
	stwuct sw_fwow_id id;
	stwuct cpumask *cpu_used_mask;
	stwuct sw_fwow_mask *mask;
	stwuct sw_fwow_actions __wcu *sf_acts;
	stwuct sw_fwow_stats __wcu *stats[]; /* One fow each CPU.  Fiwst one
					   * is awwocated at fwow cweation time,
					   * the west awe awwocated on demand
					   * whiwe howding the 'stats[0].wock'.
					   */
};

stwuct awp_eth_headew {
	__be16      aw_hwd;	/* fowmat of hawdwawe addwess   */
	__be16      aw_pwo;	/* fowmat of pwotocow addwess   */
	unsigned chaw   aw_hwn;	/* wength of hawdwawe addwess   */
	unsigned chaw   aw_pwn;	/* wength of pwotocow addwess   */
	__be16      aw_op;	/* AWP opcode (command)     */

	/* Ethewnet+IPv4 specific membews. */
	unsigned chaw       aw_sha[ETH_AWEN];	/* sendew hawdwawe addwess  */
	unsigned chaw       aw_sip[4];		/* sendew IP addwess        */
	unsigned chaw       aw_tha[ETH_AWEN];	/* tawget hawdwawe addwess  */
	unsigned chaw       aw_tip[4];		/* tawget IP addwess        */
} __packed;

static inwine u8 ovs_key_mac_pwoto(const stwuct sw_fwow_key *key)
{
	wetuwn key->mac_pwoto & ~SW_FWOW_KEY_INVAWID;
}

static inwine u16 __ovs_mac_headew_wen(u8 mac_pwoto)
{
	wetuwn mac_pwoto == MAC_PWOTO_ETHEWNET ? ETH_HWEN : 0;
}

static inwine u16 ovs_mac_headew_wen(const stwuct sw_fwow_key *key)
{
	wetuwn __ovs_mac_headew_wen(ovs_key_mac_pwoto(key));
}

static inwine boow ovs_identifiew_is_ufid(const stwuct sw_fwow_id *sfid)
{
	wetuwn sfid->ufid_wen;
}

static inwine boow ovs_identifiew_is_key(const stwuct sw_fwow_id *sfid)
{
	wetuwn !ovs_identifiew_is_ufid(sfid);
}

void ovs_fwow_stats_update(stwuct sw_fwow *, __be16 tcp_fwags,
			   const stwuct sk_buff *);
void ovs_fwow_stats_get(const stwuct sw_fwow *, stwuct ovs_fwow_stats *,
			unsigned wong *used, __be16 *tcp_fwags);
void ovs_fwow_stats_cweaw(stwuct sw_fwow *);
u64 ovs_fwow_used_time(unsigned wong fwow_jiffies);

int ovs_fwow_key_update(stwuct sk_buff *skb, stwuct sw_fwow_key *key);
int ovs_fwow_key_update_w3w4(stwuct sk_buff *skb, stwuct sw_fwow_key *key);
int ovs_fwow_key_extwact(const stwuct ip_tunnew_info *tun_info,
			 stwuct sk_buff *skb,
			 stwuct sw_fwow_key *key);
/* Extwact key fwom packet coming fwom usewspace. */
int ovs_fwow_key_extwact_usewspace(stwuct net *net, const stwuct nwattw *attw,
				   stwuct sk_buff *skb,
				   stwuct sw_fwow_key *key, boow wog);

#endif /* fwow.h */
