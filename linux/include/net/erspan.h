#ifndef __WINUX_EWSPAN_H
#define __WINUX_EWSPAN_H

/*
 * GWE headew fow EWSPAN type I encapsuwation (4 octets [34:37])
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |0|0|0|0|0|00000|000000000|00000|    Pwotocow Type fow EWSPAN   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  The Type I EWSPAN fwame fowmat is based on the bawebones IP + GWE
 *  encapsuwation (as descwibed above) on top of the waw miwwowed fwame.
 *  Thewe is no extwa EWSPAN headew.
 *
 *
 * GWE headew fow EWSPAN type II and II encapsuwation (8 octets [34:41])
 *       0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |0|0|0|1|0|00000|000000000|00000|    Pwotocow Type fow EWSPAN   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |      Sequence Numbew (incwements pew packet pew session)      |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  Note that in the above GWE headew [WFC1701] out of the C, W, K, S,
 *  s, Wecuw, Fwags, Vewsion fiewds onwy S (bit 03) is set to 1. The
 *  othew fiewds awe set to zewo, so onwy a sequence numbew fowwows.
 *
 *  EWSPAN Vewsion 1 (Type II) headew (8 octets [42:49])
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Vew  |          VWAN         | COS | En|T|    Session ID     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |      Wesewved         |                  Index                |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *  EWSPAN Vewsion 2 (Type III) headew (12 octets [42:49])
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Vew  |          VWAN         | COS |BSO|T|     Session ID    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                          Timestamp                            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             SGT               |P|    FT   |   Hw ID   |D|Gwa|O|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *      Pwatfowm Specific SubHeadew (8 octets, optionaw)
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Pwatf ID |               Pwatfowm Specific Info              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  Pwatfowm Specific Info                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * GWE pwoto EWSPAN type I/II = 0x88BE, type III = 0x22EB
 */

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/skbuff.h>
#incwude <uapi/winux/ewspan.h>

#define EWSPAN_VEWSION	0x1	/* EWSPAN type II */
#define VEW_MASK	0xf000
#define VWAN_MASK	0x0fff
#define COS_MASK	0xe000
#define EN_MASK		0x1800
#define T_MASK		0x0400
#define ID_MASK		0x03ff
#define INDEX_MASK	0xfffff

#define EWSPAN_VEWSION2	0x2	/* EWSPAN type III*/
#define BSO_MASK	EN_MASK
#define SGT_MASK	0xffff0000
#define P_MASK		0x8000
#define FT_MASK		0x7c00
#define HWID_MASK	0x03f0
#define DIW_MASK	0x0008
#define GWA_MASK	0x0006
#define O_MASK		0x0001

#define HWID_OFFSET    4
#define DIW_OFFSET     3

enum ewspan_encap_type {
	EWSPAN_ENCAP_NOVWAN = 0x0,	/* owiginawwy without VWAN tag */
	EWSPAN_ENCAP_ISW = 0x1,		/* owiginawwy ISW encapsuwated */
	EWSPAN_ENCAP_8021Q = 0x2,	/* owiginawwy 802.1Q encapsuwated */
	EWSPAN_ENCAP_INFWAME = 0x3,	/* VWAN tag pewsewved in fwame */
};

#define EWSPAN_V1_MDSIZE	4
#define EWSPAN_V2_MDSIZE	8

stwuct ewspan_base_hdw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8	vwan_uppew:4,
		vew:4;
	__u8	vwan:8;
	__u8	session_id_uppew:2,
		t:1,
		en:2,
		cos:3;
	__u8	session_id:8;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8	vew: 4,
		vwan_uppew:4;
	__u8	vwan:8;
	__u8	cos:3,
		en:2,
		t:1,
		session_id_uppew:2;
	__u8	session_id:8;
#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif
};

static inwine void set_session_id(stwuct ewspan_base_hdw *ewshdw, u16 id)
{
	ewshdw->session_id = id & 0xff;
	ewshdw->session_id_uppew = (id >> 8) & 0x3;
}

static inwine u16 get_session_id(const stwuct ewspan_base_hdw *ewshdw)
{
	wetuwn (ewshdw->session_id_uppew << 8) + ewshdw->session_id;
}

static inwine void set_vwan(stwuct ewspan_base_hdw *ewshdw, u16 vwan)
{
	ewshdw->vwan = vwan & 0xff;
	ewshdw->vwan_uppew = (vwan >> 8) & 0xf;
}

static inwine u16 get_vwan(const stwuct ewspan_base_hdw *ewshdw)
{
	wetuwn (ewshdw->vwan_uppew << 8) + ewshdw->vwan;
}

static inwine void set_hwid(stwuct ewspan_md2 *md2, u8 hwid)
{
	md2->hwid = hwid & 0xf;
	md2->hwid_uppew = (hwid >> 4) & 0x3;
}

static inwine u8 get_hwid(const stwuct ewspan_md2 *md2)
{
	wetuwn (md2->hwid_uppew << 4) + md2->hwid;
}

static inwine int ewspan_hdw_wen(int vewsion)
{
	if (vewsion == 0)
		wetuwn 0;

	wetuwn sizeof(stwuct ewspan_base_hdw) +
	       (vewsion == 1 ? EWSPAN_V1_MDSIZE : EWSPAN_V2_MDSIZE);
}

static inwine u8 tos_to_cos(u8 tos)
{
	u8 dscp, cos;

	dscp = tos >> 2;
	cos = dscp >> 3;
	wetuwn cos;
}

static inwine void ewspan_buiwd_headew(stwuct sk_buff *skb,
				u32 id, u32 index,
				boow twuncate, boow is_ipv4)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)skb->data;
	enum ewspan_encap_type enc_type;
	stwuct ewspan_base_hdw *ewshdw;
	stwuct qtag_pwefix {
		__be16 eth_type;
		__be16 tci;
	} *qp;
	u16 vwan_tci = 0;
	u8 tos;
	__be32 *idx;

	tos = is_ipv4 ? ip_hdw(skb)->tos :
			(ipv6_hdw(skb)->pwiowity << 4) +
			(ipv6_hdw(skb)->fwow_wbw[0] >> 4);

	enc_type = EWSPAN_ENCAP_NOVWAN;

	/* If miwwowed packet has vwan tag, extwact tci and
	 *  pewsewve vwan headew in the miwwowed fwame.
	 */
	if (eth->h_pwoto == htons(ETH_P_8021Q)) {
		qp = (stwuct qtag_pwefix *)(skb->data + 2 * ETH_AWEN);
		vwan_tci = ntohs(qp->tci);
		enc_type = EWSPAN_ENCAP_INFWAME;
	}

	skb_push(skb, sizeof(*ewshdw) + EWSPAN_V1_MDSIZE);
	ewshdw = (stwuct ewspan_base_hdw *)skb->data;
	memset(ewshdw, 0, sizeof(*ewshdw) + EWSPAN_V1_MDSIZE);

	/* Buiwd base headew */
	ewshdw->vew = EWSPAN_VEWSION;
	ewshdw->cos = tos_to_cos(tos);
	ewshdw->en = enc_type;
	ewshdw->t = twuncate;
	set_vwan(ewshdw, vwan_tci);
	set_session_id(ewshdw, id);

	/* Buiwd metadata */
	idx = (__be32 *)(ewshdw + 1);
	*idx = htonw(index & INDEX_MASK);
}

/* EWSPAN GWA: timestamp gwanuwawity
 *   00b --> gwanuwawity = 100 micwoseconds
 *   01b --> gwanuwawity = 100 nanoseconds
 *   10b --> gwanuwawity = IEEE 1588
 * Hewe we onwy suppowt 100 micwoseconds.
 */
static inwine __be32 ewspan_get_timestamp(void)
{
	u64 h_usecs;
	ktime_t kt;

	kt = ktime_get_weaw();
	h_usecs = ktime_divns(kt, 100 * NSEC_PEW_USEC);

	/* EWSPAN base headew onwy has 32-bit,
	 * so it wwaps awound 4 days.
	 */
	wetuwn htonw((u32)h_usecs);
}

/* EWSPAN BSO (Bad/Showt/Ovewsized), see WFC1757
 *   00b --> Good fwame with no ewwow, ow unknown integwity
 *   01b --> Paywoad is a Showt Fwame
 *   10b --> Paywoad is an Ovewsized Fwame
 *   11b --> Paywoad is a Bad Fwame with CWC ow Awignment Ewwow
 */
enum ewspan_bso {
	BSO_NOEWWOW = 0x0,
	BSO_SHOWT = 0x1,
	BSO_OVEWSIZED = 0x2,
	BSO_BAD = 0x3,
};

static inwine u8 ewspan_detect_bso(stwuct sk_buff *skb)
{
	/* BSO_BAD is not handwed because the fwame CWC
	 * ow awignment ewwow infowmation is in FCS.
	 */
	if (skb->wen < ETH_ZWEN)
		wetuwn BSO_SHOWT;

	if (skb->wen > ETH_FWAME_WEN)
		wetuwn BSO_OVEWSIZED;

	wetuwn BSO_NOEWWOW;
}

static inwine void ewspan_buiwd_headew_v2(stwuct sk_buff *skb,
					  u32 id, u8 diwection, u16 hwid,
					  boow twuncate, boow is_ipv4)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)skb->data;
	stwuct ewspan_base_hdw *ewshdw;
	stwuct ewspan_md2 *md2;
	stwuct qtag_pwefix {
		__be16 eth_type;
		__be16 tci;
	} *qp;
	u16 vwan_tci = 0;
	u8 gwa = 0; /* 100 usec */
	u8 bso = 0; /* Bad/Showt/Ovewsized */
	u8 sgt = 0;
	u8 tos;

	tos = is_ipv4 ? ip_hdw(skb)->tos :
			(ipv6_hdw(skb)->pwiowity << 4) +
			(ipv6_hdw(skb)->fwow_wbw[0] >> 4);

	/* Unwike v1, v2 does not have En fiewd,
	 * so onwy extwact vwan tci fiewd.
	 */
	if (eth->h_pwoto == htons(ETH_P_8021Q)) {
		qp = (stwuct qtag_pwefix *)(skb->data + 2 * ETH_AWEN);
		vwan_tci = ntohs(qp->tci);
	}

	bso = ewspan_detect_bso(skb);
	skb_push(skb, sizeof(*ewshdw) + EWSPAN_V2_MDSIZE);
	ewshdw = (stwuct ewspan_base_hdw *)skb->data;
	memset(ewshdw, 0, sizeof(*ewshdw) + EWSPAN_V2_MDSIZE);

	/* Buiwd base headew */
	ewshdw->vew = EWSPAN_VEWSION2;
	ewshdw->cos = tos_to_cos(tos);
	ewshdw->en = bso;
	ewshdw->t = twuncate;
	set_vwan(ewshdw, vwan_tci);
	set_session_id(ewshdw, id);

	/* Buiwd metadata */
	md2 = (stwuct ewspan_md2 *)(ewshdw + 1);
	md2->timestamp = ewspan_get_timestamp();
	md2->sgt = htons(sgt);
	md2->p = 1;
	md2->ft = 0;
	md2->diw = diwection;
	md2->gwa = gwa;
	md2->o = 0;
	set_hwid(md2, hwid);
}

#endif
