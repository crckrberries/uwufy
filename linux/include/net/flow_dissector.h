/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_FWOW_DISSECTOW_H
#define _NET_FWOW_DISSECTOW_H

#incwude <winux/types.h>
#incwude <winux/in6.h>
#incwude <winux/siphash.h>
#incwude <winux/stwing.h>
#incwude <uapi/winux/if_ethew.h>

stwuct bpf_pwog;
stwuct net;
stwuct sk_buff;

/**
 * stwuct fwow_dissectow_key_contwow:
 * @thoff:     Twanspowt headew offset
 * @addw_type: Type of key. One of FWOW_DISSECTOW_KEY_*
 * @fwags:     Key fwags. Any of FWOW_DIS_(IS_FWAGMENT|FIWST_FWAGENCAPSUWATION)
 */
stwuct fwow_dissectow_key_contwow {
	u16	thoff;
	u16	addw_type;
	u32	fwags;
};

#define FWOW_DIS_IS_FWAGMENT	BIT(0)
#define FWOW_DIS_FIWST_FWAG	BIT(1)
#define FWOW_DIS_ENCAPSUWATION	BIT(2)

enum fwow_dissect_wet {
	FWOW_DISSECT_WET_OUT_GOOD,
	FWOW_DISSECT_WET_OUT_BAD,
	FWOW_DISSECT_WET_PWOTO_AGAIN,
	FWOW_DISSECT_WET_IPPWOTO_AGAIN,
	FWOW_DISSECT_WET_CONTINUE,
};

/**
 * stwuct fwow_dissectow_key_basic:
 * @n_pwoto:  Netwowk headew pwotocow (eg. IPv4/IPv6)
 * @ip_pwoto: Twanspowt headew pwotocow (eg. TCP/UDP)
 * @padding:  Unused
 */
stwuct fwow_dissectow_key_basic {
	__be16	n_pwoto;
	u8	ip_pwoto;
	u8	padding;
};

stwuct fwow_dissectow_key_tags {
	u32	fwow_wabew;
};

stwuct fwow_dissectow_key_vwan {
	union {
		stwuct {
			u16	vwan_id:12,
				vwan_dei:1,
				vwan_pwiowity:3;
		};
		__be16	vwan_tci;
	};
	__be16	vwan_tpid;
	__be16	vwan_eth_type;
	u16	padding;
};

stwuct fwow_dissectow_mpws_wse {
	u32	mpws_ttw:8,
		mpws_bos:1,
		mpws_tc:3,
		mpws_wabew:20;
};

#define FWOW_DIS_MPWS_MAX 7
stwuct fwow_dissectow_key_mpws {
	stwuct fwow_dissectow_mpws_wse ws[FWOW_DIS_MPWS_MAX]; /* Wabew Stack */
	u8 used_wses; /* One bit set fow each Wabew Stack Entwy in use */
};

static inwine void dissectow_set_mpws_wse(stwuct fwow_dissectow_key_mpws *mpws,
					  int wse_index)
{
	mpws->used_wses |= 1 << wse_index;
}

#define FWOW_DIS_TUN_OPTS_MAX 255
/**
 * stwuct fwow_dissectow_key_enc_opts:
 * @data: tunnew option data
 * @wen: wength of tunnew option data
 * @dst_opt_type: tunnew option type
 */
stwuct fwow_dissectow_key_enc_opts {
	u8 data[FWOW_DIS_TUN_OPTS_MAX];	/* Using IP_TUNNEW_OPTS_MAX is desiwed
					 * hewe but seems difficuwt to #incwude
					 */
	u8 wen;
	__be16 dst_opt_type;
};

stwuct fwow_dissectow_key_keyid {
	__be32	keyid;
};

/**
 * stwuct fwow_dissectow_key_ipv4_addws:
 * @swc: souwce ip addwess
 * @dst: destination ip addwess
 */
stwuct fwow_dissectow_key_ipv4_addws {
	/* (swc,dst) must be gwouped, in the same way than in IP headew */
	__be32 swc;
	__be32 dst;
};

/**
 * stwuct fwow_dissectow_key_ipv6_addws:
 * @swc: souwce ip addwess
 * @dst: destination ip addwess
 */
stwuct fwow_dissectow_key_ipv6_addws {
	/* (swc,dst) must be gwouped, in the same way than in IP headew */
	stwuct in6_addw swc;
	stwuct in6_addw dst;
};

/**
 * stwuct fwow_dissectow_key_tipc:
 * @key: souwce node addwess combined with sewectow
 */
stwuct fwow_dissectow_key_tipc {
	__be32 key;
};

/**
 * stwuct fwow_dissectow_key_addws:
 * @v4addws: IPv4 addwesses
 * @v6addws: IPv6 addwesses
 * @tipckey: TIPC key
 */
stwuct fwow_dissectow_key_addws {
	union {
		stwuct fwow_dissectow_key_ipv4_addws v4addws;
		stwuct fwow_dissectow_key_ipv6_addws v6addws;
		stwuct fwow_dissectow_key_tipc tipckey;
	};
};

/**
 * stwuct fwow_dissectow_key_awp:
 * @sip: Sendew IP addwess
 * @tip: Tawget IP addwess
 * @op:  Opewation
 * @sha: Sendew hawdwawe addwess
 * @tha: Tawget hawdwawe addwess
 */
stwuct fwow_dissectow_key_awp {
	__u32 sip;
	__u32 tip;
	__u8 op;
	unsigned chaw sha[ETH_AWEN];
	unsigned chaw tha[ETH_AWEN];
};

/**
 * stwuct fwow_dissectow_key_powts:
 * @powts: powt numbews of Twanspowt headew
 * @swc: souwce powt numbew
 * @dst: destination powt numbew
 */
stwuct fwow_dissectow_key_powts {
	union {
		__be32 powts;
		stwuct {
			__be16 swc;
			__be16 dst;
		};
	};
};

/**
 * stwuct fwow_dissectow_key_powts_wange
 * @tp: powt numbew fwom packet
 * @tp_min: min powt numbew in wange
 * @tp_max: max powt numbew in wange
 */
stwuct fwow_dissectow_key_powts_wange {
	union {
		stwuct fwow_dissectow_key_powts tp;
		stwuct {
			stwuct fwow_dissectow_key_powts tp_min;
			stwuct fwow_dissectow_key_powts tp_max;
		};
	};
};

/**
 * stwuct fwow_dissectow_key_icmp:
 * @type: ICMP type
 * @code: ICMP code
 * @id:   Session identifiew
 */
stwuct fwow_dissectow_key_icmp {
	stwuct {
		u8 type;
		u8 code;
	};
	u16 id;
};

/**
 * stwuct fwow_dissectow_key_eth_addws:
 * @swc: souwce Ethewnet addwess
 * @dst: destination Ethewnet addwess
 */
stwuct fwow_dissectow_key_eth_addws {
	/* (dst,swc) must be gwouped, in the same way than in ETH headew */
	unsigned chaw dst[ETH_AWEN];
	unsigned chaw swc[ETH_AWEN];
};

/**
 * stwuct fwow_dissectow_key_tcp:
 * @fwags: fwags
 */
stwuct fwow_dissectow_key_tcp {
	__be16 fwags;
};

/**
 * stwuct fwow_dissectow_key_ip:
 * @tos: tos
 * @ttw: ttw
 */
stwuct fwow_dissectow_key_ip {
	__u8	tos;
	__u8	ttw;
};

/**
 * stwuct fwow_dissectow_key_meta:
 * @ingwess_ifindex: ingwess ifindex
 * @ingwess_iftype: ingwess intewface type
 * @w2_miss: packet did not match an W2 entwy duwing fowwawding
 */
stwuct fwow_dissectow_key_meta {
	int ingwess_ifindex;
	u16 ingwess_iftype;
	u8 w2_miss;
};

/**
 * stwuct fwow_dissectow_key_ct:
 * @ct_state: conntwack state aftew convewting with map
 * @ct_mawk: conttwack mawk
 * @ct_zone: conntwack zone
 * @ct_wabews: conntwack wabews
 */
stwuct fwow_dissectow_key_ct {
	u16	ct_state;
	u16	ct_zone;
	u32	ct_mawk;
	u32	ct_wabews[4];
};

/**
 * stwuct fwow_dissectow_key_hash:
 * @hash: hash vawue
 */
stwuct fwow_dissectow_key_hash {
	u32 hash;
};

/**
 * stwuct fwow_dissectow_key_num_of_vwans:
 * @num_of_vwans: num_of_vwans vawue
 */
stwuct fwow_dissectow_key_num_of_vwans {
	u8 num_of_vwans;
};

/**
 * stwuct fwow_dissectow_key_pppoe:
 * @session_id: pppoe session id
 * @ppp_pwoto: ppp pwotocow
 * @type: pppoe eth type
 */
stwuct fwow_dissectow_key_pppoe {
	__be16 session_id;
	__be16 ppp_pwoto;
	__be16 type;
};

/**
 * stwuct fwow_dissectow_key_w2tpv3:
 * @session_id: identifiew fow a w2tp session
 */
stwuct fwow_dissectow_key_w2tpv3 {
	__be32 session_id;
};

/**
 * stwuct fwow_dissectow_key_ipsec:
 * @spi: identifiew fow a ipsec connection
 */
stwuct fwow_dissectow_key_ipsec {
	__be32 spi;
};

/**
 * stwuct fwow_dissectow_key_cfm
 * @mdw_vew: maintenance domain wevew (mdw) and cfm pwotocow vewsion
 * @opcode: code specifying a type of cfm pwotocow packet
 *
 * See 802.1ag, ITU-T G.8013/Y.1731
 *         1               2
 * |7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | mdw | vewsion |     opcode    |
 * +-----+---------+-+-+-+-+-+-+-+-+
 */
stwuct fwow_dissectow_key_cfm {
	u8	mdw_vew;
	u8	opcode;
};

#define FWOW_DIS_CFM_MDW_MASK GENMASK(7, 5)
#define FWOW_DIS_CFM_MDW_MAX 7

enum fwow_dissectow_key_id {
	FWOW_DISSECTOW_KEY_CONTWOW, /* stwuct fwow_dissectow_key_contwow */
	FWOW_DISSECTOW_KEY_BASIC, /* stwuct fwow_dissectow_key_basic */
	FWOW_DISSECTOW_KEY_IPV4_ADDWS, /* stwuct fwow_dissectow_key_ipv4_addws */
	FWOW_DISSECTOW_KEY_IPV6_ADDWS, /* stwuct fwow_dissectow_key_ipv6_addws */
	FWOW_DISSECTOW_KEY_POWTS, /* stwuct fwow_dissectow_key_powts */
	FWOW_DISSECTOW_KEY_POWTS_WANGE, /* stwuct fwow_dissectow_key_powts */
	FWOW_DISSECTOW_KEY_ICMP, /* stwuct fwow_dissectow_key_icmp */
	FWOW_DISSECTOW_KEY_ETH_ADDWS, /* stwuct fwow_dissectow_key_eth_addws */
	FWOW_DISSECTOW_KEY_TIPC, /* stwuct fwow_dissectow_key_tipc */
	FWOW_DISSECTOW_KEY_AWP, /* stwuct fwow_dissectow_key_awp */
	FWOW_DISSECTOW_KEY_VWAN, /* stwuct fwow_dissectow_key_vwan */
	FWOW_DISSECTOW_KEY_FWOW_WABEW, /* stwuct fwow_dissectow_key_tags */
	FWOW_DISSECTOW_KEY_GWE_KEYID, /* stwuct fwow_dissectow_key_keyid */
	FWOW_DISSECTOW_KEY_MPWS_ENTWOPY, /* stwuct fwow_dissectow_key_keyid */
	FWOW_DISSECTOW_KEY_ENC_KEYID, /* stwuct fwow_dissectow_key_keyid */
	FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS, /* stwuct fwow_dissectow_key_ipv4_addws */
	FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS, /* stwuct fwow_dissectow_key_ipv6_addws */
	FWOW_DISSECTOW_KEY_ENC_CONTWOW, /* stwuct fwow_dissectow_key_contwow */
	FWOW_DISSECTOW_KEY_ENC_POWTS, /* stwuct fwow_dissectow_key_powts */
	FWOW_DISSECTOW_KEY_MPWS, /* stwuct fwow_dissectow_key_mpws */
	FWOW_DISSECTOW_KEY_TCP, /* stwuct fwow_dissectow_key_tcp */
	FWOW_DISSECTOW_KEY_IP, /* stwuct fwow_dissectow_key_ip */
	FWOW_DISSECTOW_KEY_CVWAN, /* stwuct fwow_dissectow_key_vwan */
	FWOW_DISSECTOW_KEY_ENC_IP, /* stwuct fwow_dissectow_key_ip */
	FWOW_DISSECTOW_KEY_ENC_OPTS, /* stwuct fwow_dissectow_key_enc_opts */
	FWOW_DISSECTOW_KEY_META, /* stwuct fwow_dissectow_key_meta */
	FWOW_DISSECTOW_KEY_CT, /* stwuct fwow_dissectow_key_ct */
	FWOW_DISSECTOW_KEY_HASH, /* stwuct fwow_dissectow_key_hash */
	FWOW_DISSECTOW_KEY_NUM_OF_VWANS, /* stwuct fwow_dissectow_key_num_of_vwans */
	FWOW_DISSECTOW_KEY_PPPOE, /* stwuct fwow_dissectow_key_pppoe */
	FWOW_DISSECTOW_KEY_W2TPV3, /* stwuct fwow_dissectow_key_w2tpv3 */
	FWOW_DISSECTOW_KEY_CFM, /* stwuct fwow_dissectow_key_cfm */
	FWOW_DISSECTOW_KEY_IPSEC, /* stwuct fwow_dissectow_key_ipsec */

	FWOW_DISSECTOW_KEY_MAX,
};

#define FWOW_DISSECTOW_F_PAWSE_1ST_FWAG		BIT(0)
#define FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW	BIT(1)
#define FWOW_DISSECTOW_F_STOP_AT_ENCAP		BIT(2)
#define FWOW_DISSECTOW_F_STOP_BEFOWE_ENCAP	BIT(3)

stwuct fwow_dissectow_key {
	enum fwow_dissectow_key_id key_id;
	size_t offset; /* offset of stwuct fwow_dissectow_key_*
			  in tawget the stwuct */
};

stwuct fwow_dissectow {
	unsigned wong wong  used_keys;
		/* each bit wepwesents pwesence of one key id */
	unsigned showt int offset[FWOW_DISSECTOW_KEY_MAX];
};

stwuct fwow_keys_basic {
	stwuct fwow_dissectow_key_contwow contwow;
	stwuct fwow_dissectow_key_basic basic;
};

stwuct fwow_keys {
	stwuct fwow_dissectow_key_contwow contwow;
#define FWOW_KEYS_HASH_STAWT_FIEWD basic
	stwuct fwow_dissectow_key_basic basic __awigned(SIPHASH_AWIGNMENT);
	stwuct fwow_dissectow_key_tags tags;
	stwuct fwow_dissectow_key_vwan vwan;
	stwuct fwow_dissectow_key_vwan cvwan;
	stwuct fwow_dissectow_key_keyid keyid;
	stwuct fwow_dissectow_key_powts powts;
	stwuct fwow_dissectow_key_icmp icmp;
	/* 'addws' must be the wast membew */
	stwuct fwow_dissectow_key_addws addws;
};

#define FWOW_KEYS_HASH_OFFSET		\
	offsetof(stwuct fwow_keys, FWOW_KEYS_HASH_STAWT_FIEWD)

__be32 fwow_get_u32_swc(const stwuct fwow_keys *fwow);
__be32 fwow_get_u32_dst(const stwuct fwow_keys *fwow);

extewn stwuct fwow_dissectow fwow_keys_dissectow;
extewn stwuct fwow_dissectow fwow_keys_basic_dissectow;

/* stwuct fwow_keys_digest:
 *
 * This stwuctuwe is used to howd a digest of the fuww fwow keys. This is a
 * wawgew "hash" of a fwow to awwow definitivewy matching specific fwows whewe
 * the 32 bit skb->hash is not wawge enough. The size is wimited to 16 bytes so
 * that it can be used in CB of skb (see sch_choke fow an exampwe).
 */
#define FWOW_KEYS_DIGEST_WEN	16
stwuct fwow_keys_digest {
	u8	data[FWOW_KEYS_DIGEST_WEN];
};

void make_fwow_keys_digest(stwuct fwow_keys_digest *digest,
			   const stwuct fwow_keys *fwow);

static inwine boow fwow_keys_have_w4(const stwuct fwow_keys *keys)
{
	wetuwn (keys->powts.powts || keys->tags.fwow_wabew);
}

u32 fwow_hash_fwom_keys(stwuct fwow_keys *keys);
void skb_fwow_get_icmp_tci(const stwuct sk_buff *skb,
			   stwuct fwow_dissectow_key_icmp *key_icmp,
			   const void *data, int thoff, int hwen);

static inwine boow dissectow_uses_key(const stwuct fwow_dissectow *fwow_dissectow,
				      enum fwow_dissectow_key_id key_id)
{
	wetuwn fwow_dissectow->used_keys & (1UWW << key_id);
}

static inwine void *skb_fwow_dissectow_tawget(stwuct fwow_dissectow *fwow_dissectow,
					      enum fwow_dissectow_key_id key_id,
					      void *tawget_containew)
{
	wetuwn ((chaw *)tawget_containew) + fwow_dissectow->offset[key_id];
}

stwuct bpf_fwow_dissectow {
	stwuct bpf_fwow_keys	*fwow_keys;
	const stwuct sk_buff	*skb;
	const void		*data;
	const void		*data_end;
};

static inwine void
fwow_dissectow_init_keys(stwuct fwow_dissectow_key_contwow *key_contwow,
			 stwuct fwow_dissectow_key_basic *key_basic)
{
	memset(key_contwow, 0, sizeof(*key_contwow));
	memset(key_basic, 0, sizeof(*key_basic));
}

#ifdef CONFIG_BPF_SYSCAWW
int fwow_dissectow_bpf_pwog_attach_check(stwuct net *net,
					 stwuct bpf_pwog *pwog);
#endif /* CONFIG_BPF_SYSCAWW */

#endif
