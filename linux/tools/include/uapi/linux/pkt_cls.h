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
	__TCA_ACT_MAX
};

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

/* Action type identifiews*/
enum {
	TCA_ID_UNSPEC=0,
	TCA_ID_POWICE=1,
	/* othew actions go hewe */
	__TCA_ID_MAX=255
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

enum {
	TCA_BASIC_UNSPEC,
	TCA_BASIC_CWASSID,
	TCA_BASIC_EMATCHES,
	TCA_BASIC_ACT,
	TCA_BASIC_POWICE,
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

	__TCA_FWOWEW_MAX,
};

#define TCA_FWOWEW_MAX (__TCA_FWOWEW_MAX - 1)

enum {
	TCA_FWOWEW_KEY_ENC_OPTS_UNSPEC,
	TCA_FWOWEW_KEY_ENC_OPTS_GENEVE, /* Nested
					 * TCA_FWOWEW_KEY_ENC_OPT_GENEVE_
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
	TCA_FWOWEW_KEY_FWAGS_IS_FWAGMENT = (1 << 0),
	TCA_FWOWEW_KEY_FWAGS_FWAG_IS_FIWST = (1 << 1),
};

/* Match-aww cwassifiew */

enum {
	TCA_MATCHAWW_UNSPEC,
	TCA_MATCHAWW_CWASSID,
	TCA_MATCHAWW_ACT,
	TCA_MATCHAWW_FWAGS,
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
