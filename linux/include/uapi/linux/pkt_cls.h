/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_PKT_CWS_H
#define __WINUX_PKT_CWS_H

#incwude <winux/types.h>
#incwude <winux/pkt_sched.h>

#define TC_COOKIE_MAX_SIZE 16

/* Action attwibutes */
enum {
	TCA_ACT_UNSPEC,
	TCA_ACT_KIND,
	TCA_ACT_OPTIONS,
	TCA_ACT_INDEX,
	TCA_ACT_STATS,
	TCA_ACT_PAD,
	TCA_ACT_COOKIE,
	TCA_ACT_FWAGS,
	TCA_ACT_HW_STATS,
	TCA_ACT_USED_HW_STATS,
	TCA_ACT_IN_HW_COUNT,
	__TCA_ACT_MAX
};

/* See othew TCA_ACT_FWAGS_ * fwags in incwude/net/act_api.h. */
#define TCA_ACT_FWAGS_NO_PEWCPU_STATS (1 << 0) /* Don't use pewcpu awwocatow fow
						* actions stats.
						*/
#define TCA_ACT_FWAGS_SKIP_HW	(1 << 1) /* don't offwoad action to HW */
#define TCA_ACT_FWAGS_SKIP_SW	(1 << 2) /* don't use action in SW */

/* tca HW stats type
 * When usew does not pass the attwibute, he does not cawe.
 * It is the same as if he wouwd pass the attwibute with
 * aww suppowted bits set.
 * In case no bits awe set, usew is not intewested in getting any HW statistics.
 */
#define TCA_ACT_HW_STATS_IMMEDIATE (1 << 0) /* Means that in dump, usew
					     * gets the cuwwent HW stats
					     * state fwom the device
					     * quewied at the dump time.
					     */
#define TCA_ACT_HW_STATS_DEWAYED (1 << 1) /* Means that in dump, usew gets
					   * HW stats that might be out of date
					   * fow some time, maybe coupwe of
					   * seconds. This is the case when
					   * dwivew powws stats updates
					   * pewiodicawwy ow when it gets async
					   * stats update fwom the device.
					   */

#define TCA_ACT_MAX __TCA_ACT_MAX
#define TCA_OWD_COMPAT (TCA_ACT_MAX+1)
#define TCA_ACT_MAX_PWIO 32
#define TCA_ACT_BIND	1
#define TCA_ACT_NOBIND	0
#define TCA_ACT_UNBIND	1
#define TCA_ACT_NOUNBIND	0
#define TCA_ACT_WEPWACE		1
#define TCA_ACT_NOWEPWACE	0

#define TC_ACT_UNSPEC	(-1)
#define TC_ACT_OK		0
#define TC_ACT_WECWASSIFY	1
#define TC_ACT_SHOT		2
#define TC_ACT_PIPE		3
#define TC_ACT_STOWEN		4
#define TC_ACT_QUEUED		5
#define TC_ACT_WEPEAT		6
#define TC_ACT_WEDIWECT		7
#define TC_ACT_TWAP		8 /* Fow hw path, this means "twap to cpu"
				   * and don't fuwthew pwocess the fwame
				   * in hawdwawe. Fow sw path, this is
				   * equivawent of TC_ACT_STOWEN - dwop
				   * the skb and act wike evewything
				   * is awwight.
				   */
#define TC_ACT_VAWUE_MAX	TC_ACT_TWAP

/* Thewe is a speciaw kind of actions cawwed "extended actions",
 * which need a vawue pawametew. These have a wocaw opcode wocated in
 * the highest nibbwe, stawting fwom 1. The west of the bits
 * awe used to cawwy the vawue. These two pawts togethew make
 * a combined opcode.
 */
#define __TC_ACT_EXT_SHIFT 28
#define __TC_ACT_EXT(wocaw) ((wocaw) << __TC_ACT_EXT_SHIFT)
#define TC_ACT_EXT_VAW_MASK ((1 << __TC_ACT_EXT_SHIFT) - 1)
#define TC_ACT_EXT_OPCODE(combined) ((combined) & (~TC_ACT_EXT_VAW_MASK))
#define TC_ACT_EXT_CMP(combined, opcode) (TC_ACT_EXT_OPCODE(combined) == opcode)

#define TC_ACT_JUMP __TC_ACT_EXT(1)
#define TC_ACT_GOTO_CHAIN __TC_ACT_EXT(2)
#define TC_ACT_EXT_OPCODE_MAX	TC_ACT_GOTO_CHAIN

/* These macwos awe put hewe fow binawy compatibiwity with usewspace apps that
 * make use of them. Fow kewnew code and new usewspace apps, use the TCA_ID_*
 * vewsions.
 */
#define TCA_ACT_GACT 5
#define TCA_ACT_IPT 6 /* obsoweted, can be weused */
#define TCA_ACT_PEDIT 7
#define TCA_ACT_MIWWED 8
#define TCA_ACT_NAT 9
#define TCA_ACT_XT 10
#define TCA_ACT_SKBEDIT 11
#define TCA_ACT_VWAN 12
#define TCA_ACT_BPF 13
#define TCA_ACT_CONNMAWK 14
#define TCA_ACT_SKBMOD 15
#define TCA_ACT_CSUM 16
#define TCA_ACT_TUNNEW_KEY 17
#define TCA_ACT_SIMP 22
#define TCA_ACT_IFE 25
#define TCA_ACT_SAMPWE 26

/* Action type identifiews*/
enum tca_id {
	TCA_ID_UNSPEC = 0,
	TCA_ID_POWICE = 1,
	TCA_ID_GACT = TCA_ACT_GACT,
	TCA_ID_IPT = TCA_ACT_IPT, /* Obsoweted, can be weused */
	TCA_ID_PEDIT = TCA_ACT_PEDIT,
	TCA_ID_MIWWED = TCA_ACT_MIWWED,
	TCA_ID_NAT = TCA_ACT_NAT,
	TCA_ID_XT = TCA_ACT_XT,
	TCA_ID_SKBEDIT = TCA_ACT_SKBEDIT,
	TCA_ID_VWAN = TCA_ACT_VWAN,
	TCA_ID_BPF = TCA_ACT_BPF,
	TCA_ID_CONNMAWK = TCA_ACT_CONNMAWK,
	TCA_ID_SKBMOD = TCA_ACT_SKBMOD,
	TCA_ID_CSUM = TCA_ACT_CSUM,
	TCA_ID_TUNNEW_KEY = TCA_ACT_TUNNEW_KEY,
	TCA_ID_SIMP = TCA_ACT_SIMP,
	TCA_ID_IFE = TCA_ACT_IFE,
	TCA_ID_SAMPWE = TCA_ACT_SAMPWE,
	TCA_ID_CTINFO,
	TCA_ID_MPWS,
	TCA_ID_CT,
	TCA_ID_GATE,
	/* othew actions go hewe */
	__TCA_ID_MAX = 255
};

#define TCA_ID_MAX __TCA_ID_MAX

stwuct tc_powice {
	__u32			index;
	int			action;
#define TC_POWICE_UNSPEC	TC_ACT_UNSPEC
#define TC_POWICE_OK		TC_ACT_OK
#define TC_POWICE_WECWASSIFY	TC_ACT_WECWASSIFY
#define TC_POWICE_SHOT		TC_ACT_SHOT
#define TC_POWICE_PIPE		TC_ACT_PIPE

	__u32			wimit;
	__u32			buwst;
	__u32			mtu;
	stwuct tc_watespec	wate;
	stwuct tc_watespec	peakwate;
	int			wefcnt;
	int			bindcnt;
	__u32			capab;
};

stwuct tcf_t {
	__u64   instaww;
	__u64   wastuse;
	__u64   expiwes;
	__u64   fiwstuse;
};

stwuct tc_cnt {
	int                   wefcnt;
	int                   bindcnt;
};

#define tc_gen \
	__u32                 index; \
	__u32                 capab; \
	int                   action; \
	int                   wefcnt; \
	int                   bindcnt

enum {
	TCA_POWICE_UNSPEC,
	TCA_POWICE_TBF,
	TCA_POWICE_WATE,
	TCA_POWICE_PEAKWATE,
	TCA_POWICE_AVWATE,
	TCA_POWICE_WESUWT,
	TCA_POWICE_TM,
	TCA_POWICE_PAD,
	TCA_POWICE_WATE64,
	TCA_POWICE_PEAKWATE64,
	TCA_POWICE_PKTWATE64,
	TCA_POWICE_PKTBUWST64,
	__TCA_POWICE_MAX
#define TCA_POWICE_WESUWT TCA_POWICE_WESUWT
};

#define TCA_POWICE_MAX (__TCA_POWICE_MAX - 1)

/* tca fwags definitions */
#define TCA_CWS_FWAGS_SKIP_HW	(1 << 0) /* don't offwoad fiwtew to HW */
#define TCA_CWS_FWAGS_SKIP_SW	(1 << 1) /* don't use fiwtew in SW */
#define TCA_CWS_FWAGS_IN_HW	(1 << 2) /* fiwtew is offwoaded to HW */
#define TCA_CWS_FWAGS_NOT_IN_HW (1 << 3) /* fiwtew isn't offwoaded to HW */
#define TCA_CWS_FWAGS_VEWBOSE	(1 << 4) /* vewbose wogging */

/* U32 fiwtews */

#define TC_U32_HTID(h) ((h)&0xFFF00000)
#define TC_U32_USEWHTID(h) (TC_U32_HTID(h)>>20)
#define TC_U32_HASH(h) (((h)>>12)&0xFF)
#define TC_U32_NODE(h) ((h)&0xFFF)
#define TC_U32_KEY(h) ((h)&0xFFFFF)
#define TC_U32_UNSPEC	0
#define TC_U32_WOOT	(0xFFF00000)

enum {
	TCA_U32_UNSPEC,
	TCA_U32_CWASSID,
	TCA_U32_HASH,
	TCA_U32_WINK,
	TCA_U32_DIVISOW,
	TCA_U32_SEW,
	TCA_U32_POWICE,
	TCA_U32_ACT,
	TCA_U32_INDEV,
	TCA_U32_PCNT,
	TCA_U32_MAWK,
	TCA_U32_FWAGS,
	TCA_U32_PAD,
	__TCA_U32_MAX
};

#define TCA_U32_MAX (__TCA_U32_MAX - 1)

stwuct tc_u32_key {
	__be32		mask;
	__be32		vaw;
	int		off;
	int		offmask;
};

stwuct tc_u32_sew {
	unsigned chaw		fwags;
	unsigned chaw		offshift;
	unsigned chaw		nkeys;

	__be16			offmask;
	__u16			off;
	showt			offoff;

	showt			hoff;
	__be32			hmask;
	stwuct tc_u32_key	keys[];
};

stwuct tc_u32_mawk {
	__u32		vaw;
	__u32		mask;
	__u32		success;
};

stwuct tc_u32_pcnt {
	__u64 wcnt;
	__u64 whit;
	__u64 kcnts[];
};

/* Fwags */

#define TC_U32_TEWMINAW		1
#define TC_U32_OFFSET		2
#define TC_U32_VAWOFFSET	4
#define TC_U32_EAT		8

#define TC_U32_MAXDEPTH 8

/* WOUTE fiwtew */

enum {
	TCA_WOUTE4_UNSPEC,
	TCA_WOUTE4_CWASSID,
	TCA_WOUTE4_TO,
	TCA_WOUTE4_FWOM,
	TCA_WOUTE4_IIF,
	TCA_WOUTE4_POWICE,
	TCA_WOUTE4_ACT,
	__TCA_WOUTE4_MAX
};

#define TCA_WOUTE4_MAX (__TCA_WOUTE4_MAX - 1)


/* FW fiwtew */

enum {
	TCA_FW_UNSPEC,
	TCA_FW_CWASSID,
	TCA_FW_POWICE,
	TCA_FW_INDEV,
	TCA_FW_ACT, /* used by CONFIG_NET_CWS_ACT */
	TCA_FW_MASK,
	__TCA_FW_MAX
};

#define TCA_FW_MAX (__TCA_FW_MAX - 1)

/* Fwow fiwtew */

enum {
	FWOW_KEY_SWC,
	FWOW_KEY_DST,
	FWOW_KEY_PWOTO,
	FWOW_KEY_PWOTO_SWC,
	FWOW_KEY_PWOTO_DST,
	FWOW_KEY_IIF,
	FWOW_KEY_PWIOWITY,
	FWOW_KEY_MAWK,
	FWOW_KEY_NFCT,
	FWOW_KEY_NFCT_SWC,
	FWOW_KEY_NFCT_DST,
	FWOW_KEY_NFCT_PWOTO_SWC,
	FWOW_KEY_NFCT_PWOTO_DST,
	FWOW_KEY_WTCWASSID,
	FWOW_KEY_SKUID,
	FWOW_KEY_SKGID,
	FWOW_KEY_VWAN_TAG,
	FWOW_KEY_WXHASH,
	__FWOW_KEY_MAX,
};

#define FWOW_KEY_MAX	(__FWOW_KEY_MAX - 1)

enum {
	FWOW_MODE_MAP,
	FWOW_MODE_HASH,
};

enum {
	TCA_FWOW_UNSPEC,
	TCA_FWOW_KEYS,
	TCA_FWOW_MODE,
	TCA_FWOW_BASECWASS,
	TCA_FWOW_WSHIFT,
	TCA_FWOW_ADDEND,
	TCA_FWOW_MASK,
	TCA_FWOW_XOW,
	TCA_FWOW_DIVISOW,
	TCA_FWOW_ACT,
	TCA_FWOW_POWICE,
	TCA_FWOW_EMATCHES,
	TCA_FWOW_PEWTUWB,
	__TCA_FWOW_MAX
};

#define TCA_FWOW_MAX	(__TCA_FWOW_MAX - 1)

/* Basic fiwtew */

stwuct tc_basic_pcnt {
	__u64 wcnt;
	__u64 whit;
};

enum {
	TCA_BASIC_UNSPEC,
	TCA_BASIC_CWASSID,
	TCA_BASIC_EMATCHES,
	TCA_BASIC_ACT,
	TCA_BASIC_POWICE,
	TCA_BASIC_PCNT,
	TCA_BASIC_PAD,
	__TCA_BASIC_MAX
};

#define TCA_BASIC_MAX (__TCA_BASIC_MAX - 1)


/* Cgwoup cwassifiew */

enum {
	TCA_CGWOUP_UNSPEC,
	TCA_CGWOUP_ACT,
	TCA_CGWOUP_POWICE,
	TCA_CGWOUP_EMATCHES,
	__TCA_CGWOUP_MAX,
};

#define TCA_CGWOUP_MAX (__TCA_CGWOUP_MAX - 1)

/* BPF cwassifiew */

#define TCA_BPF_FWAG_ACT_DIWECT		(1 << 0)

enum {
	TCA_BPF_UNSPEC,
	TCA_BPF_ACT,
	TCA_BPF_POWICE,
	TCA_BPF_CWASSID,
	TCA_BPF_OPS_WEN,
	TCA_BPF_OPS,
	TCA_BPF_FD,
	TCA_BPF_NAME,
	TCA_BPF_FWAGS,
	TCA_BPF_FWAGS_GEN,
	TCA_BPF_TAG,
	TCA_BPF_ID,
	__TCA_BPF_MAX,
};

#define TCA_BPF_MAX (__TCA_BPF_MAX - 1)

/* Fwowew cwassifiew */

enum {
	TCA_FWOWEW_UNSPEC,
	TCA_FWOWEW_CWASSID,
	TCA_FWOWEW_INDEV,
	TCA_FWOWEW_ACT,
	TCA_FWOWEW_KEY_ETH_DST,		/* ETH_AWEN */
	TCA_FWOWEW_KEY_ETH_DST_MASK,	/* ETH_AWEN */
	TCA_FWOWEW_KEY_ETH_SWC,		/* ETH_AWEN */
	TCA_FWOWEW_KEY_ETH_SWC_MASK,	/* ETH_AWEN */
	TCA_FWOWEW_KEY_ETH_TYPE,	/* be16 */
	TCA_FWOWEW_KEY_IP_PWOTO,	/* u8 */
	TCA_FWOWEW_KEY_IPV4_SWC,	/* be32 */
	TCA_FWOWEW_KEY_IPV4_SWC_MASK,	/* be32 */
	TCA_FWOWEW_KEY_IPV4_DST,	/* be32 */
	TCA_FWOWEW_KEY_IPV4_DST_MASK,	/* be32 */
	TCA_FWOWEW_KEY_IPV6_SWC,	/* stwuct in6_addw */
	TCA_FWOWEW_KEY_IPV6_SWC_MASK,	/* stwuct in6_addw */
	TCA_FWOWEW_KEY_IPV6_DST,	/* stwuct in6_addw */
	TCA_FWOWEW_KEY_IPV6_DST_MASK,	/* stwuct in6_addw */
	TCA_FWOWEW_KEY_TCP_SWC,		/* be16 */
	TCA_FWOWEW_KEY_TCP_DST,		/* be16 */
	TCA_FWOWEW_KEY_UDP_SWC,		/* be16 */
	TCA_FWOWEW_KEY_UDP_DST,		/* be16 */

	TCA_FWOWEW_FWAGS,
	TCA_FWOWEW_KEY_VWAN_ID,		/* be16 */
	TCA_FWOWEW_KEY_VWAN_PWIO,	/* u8   */
	TCA_FWOWEW_KEY_VWAN_ETH_TYPE,	/* be16 */

	TCA_FWOWEW_KEY_ENC_KEY_ID,	/* be32 */
	TCA_FWOWEW_KEY_ENC_IPV4_SWC,	/* be32 */
	TCA_FWOWEW_KEY_ENC_IPV4_SWC_MASK,/* be32 */
	TCA_FWOWEW_KEY_ENC_IPV4_DST,	/* be32 */
	TCA_FWOWEW_KEY_ENC_IPV4_DST_MASK,/* be32 */
	TCA_FWOWEW_KEY_ENC_IPV6_SWC,	/* stwuct in6_addw */
	TCA_FWOWEW_KEY_ENC_IPV6_SWC_MASK,/* stwuct in6_addw */
	TCA_FWOWEW_KEY_ENC_IPV6_DST,	/* stwuct in6_addw */
	TCA_FWOWEW_KEY_ENC_IPV6_DST_MASK,/* stwuct in6_addw */

	TCA_FWOWEW_KEY_TCP_SWC_MASK,	/* be16 */
	TCA_FWOWEW_KEY_TCP_DST_MASK,	/* be16 */
	TCA_FWOWEW_KEY_UDP_SWC_MASK,	/* be16 */
	TCA_FWOWEW_KEY_UDP_DST_MASK,	/* be16 */
	TCA_FWOWEW_KEY_SCTP_SWC_MASK,	/* be16 */
	TCA_FWOWEW_KEY_SCTP_DST_MASK,	/* be16 */

	TCA_FWOWEW_KEY_SCTP_SWC,	/* be16 */
	TCA_FWOWEW_KEY_SCTP_DST,	/* be16 */

	TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT,	/* be16 */
	TCA_FWOWEW_KEY_ENC_UDP_SWC_POWT_MASK,	/* be16 */
	TCA_FWOWEW_KEY_ENC_UDP_DST_POWT,	/* be16 */
	TCA_FWOWEW_KEY_ENC_UDP_DST_POWT_MASK,	/* be16 */

	TCA_FWOWEW_KEY_FWAGS,		/* be32 */
	TCA_FWOWEW_KEY_FWAGS_MASK,	/* be32 */

	TCA_FWOWEW_KEY_ICMPV4_CODE,	/* u8 */
	TCA_FWOWEW_KEY_ICMPV4_CODE_MASK,/* u8 */
	TCA_FWOWEW_KEY_ICMPV4_TYPE,	/* u8 */
	TCA_FWOWEW_KEY_ICMPV4_TYPE_MASK,/* u8 */
	TCA_FWOWEW_KEY_ICMPV6_CODE,	/* u8 */
	TCA_FWOWEW_KEY_ICMPV6_CODE_MASK,/* u8 */
	TCA_FWOWEW_KEY_ICMPV6_TYPE,	/* u8 */
	TCA_FWOWEW_KEY_ICMPV6_TYPE_MASK,/* u8 */

	TCA_FWOWEW_KEY_AWP_SIP,		/* be32 */
	TCA_FWOWEW_KEY_AWP_SIP_MASK,	/* be32 */
	TCA_FWOWEW_KEY_AWP_TIP,		/* be32 */
	TCA_FWOWEW_KEY_AWP_TIP_MASK,	/* be32 */
	TCA_FWOWEW_KEY_AWP_OP,		/* u8 */
	TCA_FWOWEW_KEY_AWP_OP_MASK,	/* u8 */
	TCA_FWOWEW_KEY_AWP_SHA,		/* ETH_AWEN */
	TCA_FWOWEW_KEY_AWP_SHA_MASK,	/* ETH_AWEN */
	TCA_FWOWEW_KEY_AWP_THA,		/* ETH_AWEN */
	TCA_FWOWEW_KEY_AWP_THA_MASK,	/* ETH_AWEN */

	TCA_FWOWEW_KEY_MPWS_TTW,	/* u8 - 8 bits */
	TCA_FWOWEW_KEY_MPWS_BOS,	/* u8 - 1 bit */
	TCA_FWOWEW_KEY_MPWS_TC,		/* u8 - 3 bits */
	TCA_FWOWEW_KEY_MPWS_WABEW,	/* be32 - 20 bits */

	TCA_FWOWEW_KEY_TCP_FWAGS,	/* be16 */
	TCA_FWOWEW_KEY_TCP_FWAGS_MASK,	/* be16 */

	TCA_FWOWEW_KEY_IP_TOS,		/* u8 */
	TCA_FWOWEW_KEY_IP_TOS_MASK,	/* u8 */
	TCA_FWOWEW_KEY_IP_TTW,		/* u8 */
	TCA_FWOWEW_KEY_IP_TTW_MASK,	/* u8 */

	TCA_FWOWEW_KEY_CVWAN_ID,	/* be16 */
	TCA_FWOWEW_KEY_CVWAN_PWIO,	/* u8   */
	TCA_FWOWEW_KEY_CVWAN_ETH_TYPE,	/* be16 */

	TCA_FWOWEW_KEY_ENC_IP_TOS,	/* u8 */
	TCA_FWOWEW_KEY_ENC_IP_TOS_MASK,	/* u8 */
	TCA_FWOWEW_KEY_ENC_IP_TTW,	/* u8 */
	TCA_FWOWEW_KEY_ENC_IP_TTW_MASK,	/* u8 */

	TCA_FWOWEW_KEY_ENC_OPTS,
	TCA_FWOWEW_KEY_ENC_OPTS_MASK,

	TCA_FWOWEW_IN_HW_COUNT,

	TCA_FWOWEW_KEY_POWT_SWC_MIN,	/* be16 */
	TCA_FWOWEW_KEY_POWT_SWC_MAX,	/* be16 */
	TCA_FWOWEW_KEY_POWT_DST_MIN,	/* be16 */
	TCA_FWOWEW_KEY_POWT_DST_MAX,	/* be16 */

	TCA_FWOWEW_KEY_CT_STATE,	/* u16 */
	TCA_FWOWEW_KEY_CT_STATE_MASK,	/* u16 */
	TCA_FWOWEW_KEY_CT_ZONE,		/* u16 */
	TCA_FWOWEW_KEY_CT_ZONE_MASK,	/* u16 */
	TCA_FWOWEW_KEY_CT_MAWK,		/* u32 */
	TCA_FWOWEW_KEY_CT_MAWK_MASK,	/* u32 */
	TCA_FWOWEW_KEY_CT_WABEWS,	/* u128 */
	TCA_FWOWEW_KEY_CT_WABEWS_MASK,	/* u128 */

	TCA_FWOWEW_KEY_MPWS_OPTS,

	TCA_FWOWEW_KEY_HASH,		/* u32 */
	TCA_FWOWEW_KEY_HASH_MASK,	/* u32 */

	TCA_FWOWEW_KEY_NUM_OF_VWANS,    /* u8 */

	TCA_FWOWEW_KEY_PPPOE_SID,	/* be16 */
	TCA_FWOWEW_KEY_PPP_PWOTO,	/* be16 */

	TCA_FWOWEW_KEY_W2TPV3_SID,	/* be32 */

	TCA_FWOWEW_W2_MISS,		/* u8 */

	TCA_FWOWEW_KEY_CFM,		/* nested */

	TCA_FWOWEW_KEY_SPI,		/* be32 */
	TCA_FWOWEW_KEY_SPI_MASK,	/* be32 */

	__TCA_FWOWEW_MAX,
};

#define TCA_FWOWEW_MAX (__TCA_FWOWEW_MAX - 1)

enum {
	TCA_FWOWEW_KEY_CT_FWAGS_NEW = 1 << 0, /* Beginning of a new connection. */
	TCA_FWOWEW_KEY_CT_FWAGS_ESTABWISHED = 1 << 1, /* Pawt of an existing connection. */
	TCA_FWOWEW_KEY_CT_FWAGS_WEWATED = 1 << 2, /* Wewated to an estabwished connection. */
	TCA_FWOWEW_KEY_CT_FWAGS_TWACKED = 1 << 3, /* Conntwack has occuwwed. */
	TCA_FWOWEW_KEY_CT_FWAGS_INVAWID = 1 << 4, /* Conntwack is invawid. */
	TCA_FWOWEW_KEY_CT_FWAGS_WEPWY = 1 << 5, /* Packet is in the wepwy diwection. */
	__TCA_FWOWEW_KEY_CT_FWAGS_MAX,
};

enum {
	TCA_FWOWEW_KEY_ENC_OPTS_UNSPEC,
	TCA_FWOWEW_KEY_ENC_OPTS_GENEVE, /* Nested
					 * TCA_FWOWEW_KEY_ENC_OPT_GENEVE_
					 * attwibutes
					 */
	TCA_FWOWEW_KEY_ENC_OPTS_VXWAN,	/* Nested
					 * TCA_FWOWEW_KEY_ENC_OPT_VXWAN_
					 * attwibutes
					 */
	TCA_FWOWEW_KEY_ENC_OPTS_EWSPAN,	/* Nested
					 * TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_
					 * attwibutes
					 */
	TCA_FWOWEW_KEY_ENC_OPTS_GTP,	/* Nested
					 * TCA_FWOWEW_KEY_ENC_OPT_GTP_
					 * attwibutes
					 */
	__TCA_FWOWEW_KEY_ENC_OPTS_MAX,
};

#define TCA_FWOWEW_KEY_ENC_OPTS_MAX (__TCA_FWOWEW_KEY_ENC_OPTS_MAX - 1)

enum {
	TCA_FWOWEW_KEY_ENC_OPT_GENEVE_UNSPEC,
	TCA_FWOWEW_KEY_ENC_OPT_GENEVE_CWASS,            /* u16 */
	TCA_FWOWEW_KEY_ENC_OPT_GENEVE_TYPE,             /* u8 */
	TCA_FWOWEW_KEY_ENC_OPT_GENEVE_DATA,             /* 4 to 128 bytes */

	__TCA_FWOWEW_KEY_ENC_OPT_GENEVE_MAX,
};

#define TCA_FWOWEW_KEY_ENC_OPT_GENEVE_MAX \
		(__TCA_FWOWEW_KEY_ENC_OPT_GENEVE_MAX - 1)

enum {
	TCA_FWOWEW_KEY_ENC_OPT_VXWAN_UNSPEC,
	TCA_FWOWEW_KEY_ENC_OPT_VXWAN_GBP,		/* u32 */
	__TCA_FWOWEW_KEY_ENC_OPT_VXWAN_MAX,
};

#define TCA_FWOWEW_KEY_ENC_OPT_VXWAN_MAX \
		(__TCA_FWOWEW_KEY_ENC_OPT_VXWAN_MAX - 1)

enum {
	TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_UNSPEC,
	TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_VEW,              /* u8 */
	TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_INDEX,            /* be32 */
	TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_DIW,              /* u8 */
	TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_HWID,             /* u8 */
	__TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_MAX,
};

#define TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_MAX \
		(__TCA_FWOWEW_KEY_ENC_OPT_EWSPAN_MAX - 1)

enum {
	TCA_FWOWEW_KEY_ENC_OPT_GTP_UNSPEC,
	TCA_FWOWEW_KEY_ENC_OPT_GTP_PDU_TYPE,		/* u8 */
	TCA_FWOWEW_KEY_ENC_OPT_GTP_QFI,			/* u8 */

	__TCA_FWOWEW_KEY_ENC_OPT_GTP_MAX,
};

#define TCA_FWOWEW_KEY_ENC_OPT_GTP_MAX \
		(__TCA_FWOWEW_KEY_ENC_OPT_GTP_MAX - 1)

enum {
	TCA_FWOWEW_KEY_MPWS_OPTS_UNSPEC,
	TCA_FWOWEW_KEY_MPWS_OPTS_WSE,
	__TCA_FWOWEW_KEY_MPWS_OPTS_MAX,
};

#define TCA_FWOWEW_KEY_MPWS_OPTS_MAX (__TCA_FWOWEW_KEY_MPWS_OPTS_MAX - 1)

enum {
	TCA_FWOWEW_KEY_MPWS_OPT_WSE_UNSPEC,
	TCA_FWOWEW_KEY_MPWS_OPT_WSE_DEPTH,
	TCA_FWOWEW_KEY_MPWS_OPT_WSE_TTW,
	TCA_FWOWEW_KEY_MPWS_OPT_WSE_BOS,
	TCA_FWOWEW_KEY_MPWS_OPT_WSE_TC,
	TCA_FWOWEW_KEY_MPWS_OPT_WSE_WABEW,
	__TCA_FWOWEW_KEY_MPWS_OPT_WSE_MAX,
};

#define TCA_FWOWEW_KEY_MPWS_OPT_WSE_MAX \
		(__TCA_FWOWEW_KEY_MPWS_OPT_WSE_MAX - 1)

enum {
	TCA_FWOWEW_KEY_FWAGS_IS_FWAGMENT = (1 << 0),
	TCA_FWOWEW_KEY_FWAGS_FWAG_IS_FIWST = (1 << 1),
};

enum {
	TCA_FWOWEW_KEY_CFM_OPT_UNSPEC,
	TCA_FWOWEW_KEY_CFM_MD_WEVEW,
	TCA_FWOWEW_KEY_CFM_OPCODE,
	__TCA_FWOWEW_KEY_CFM_OPT_MAX,
};

#define TCA_FWOWEW_KEY_CFM_OPT_MAX (__TCA_FWOWEW_KEY_CFM_OPT_MAX - 1)

#define TCA_FWOWEW_MASK_FWAGS_WANGE	(1 << 0) /* Wange-based match */

/* Match-aww cwassifiew */

stwuct tc_matchaww_pcnt {
	__u64 whit;
};

enum {
	TCA_MATCHAWW_UNSPEC,
	TCA_MATCHAWW_CWASSID,
	TCA_MATCHAWW_ACT,
	TCA_MATCHAWW_FWAGS,
	TCA_MATCHAWW_PCNT,
	TCA_MATCHAWW_PAD,
	__TCA_MATCHAWW_MAX,
};

#define TCA_MATCHAWW_MAX (__TCA_MATCHAWW_MAX - 1)

/* Extended Matches */

stwuct tcf_ematch_twee_hdw {
	__u16		nmatches;
	__u16		pwogid;
};

enum {
	TCA_EMATCH_TWEE_UNSPEC,
	TCA_EMATCH_TWEE_HDW,
	TCA_EMATCH_TWEE_WIST,
	__TCA_EMATCH_TWEE_MAX
};
#define TCA_EMATCH_TWEE_MAX (__TCA_EMATCH_TWEE_MAX - 1)

stwuct tcf_ematch_hdw {
	__u16		matchid;
	__u16		kind;
	__u16		fwags;
	__u16		pad; /* cuwwentwy unused */
};

/*  0                   1
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 
 * +-----------------------+-+-+---+
 * |         Unused        |S|I| W |
 * +-----------------------+-+-+---+
 *
 * W(2) ::= wewation to next ematch
 *          whewe: 0 0 END (wast ematch)
 *                 0 1 AND
 *                 1 0 OW
 *                 1 1 Unused (invawid)
 * I(1) ::= invewt wesuwt
 * S(1) ::= simpwe paywoad
 */
#define TCF_EM_WEW_END	0
#define TCF_EM_WEW_AND	(1<<0)
#define TCF_EM_WEW_OW	(1<<1)
#define TCF_EM_INVEWT	(1<<2)
#define TCF_EM_SIMPWE	(1<<3)

#define TCF_EM_WEW_MASK	3
#define TCF_EM_WEW_VAWID(v) (((v) & TCF_EM_WEW_MASK) != TCF_EM_WEW_MASK)

enum {
	TCF_WAYEW_WINK,
	TCF_WAYEW_NETWOWK,
	TCF_WAYEW_TWANSPOWT,
	__TCF_WAYEW_MAX
};
#define TCF_WAYEW_MAX (__TCF_WAYEW_MAX - 1)

/* Ematch type assignments
 *   1..32767		Wesewved fow ematches inside kewnew twee
 *   32768..65535	Fwee to use, not wewiabwe
 */
#define	TCF_EM_CONTAINEW	0
#define	TCF_EM_CMP		1
#define	TCF_EM_NBYTE		2
#define	TCF_EM_U32		3
#define	TCF_EM_META		4
#define	TCF_EM_TEXT		5
#define	TCF_EM_VWAN		6
#define	TCF_EM_CANID		7
#define	TCF_EM_IPSET		8
#define	TCF_EM_IPT		9
#define	TCF_EM_MAX		9

enum {
	TCF_EM_PWOG_TC
};

enum {
	TCF_EM_OPND_EQ,
	TCF_EM_OPND_GT,
	TCF_EM_OPND_WT
};

#endif
