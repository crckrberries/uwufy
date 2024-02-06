/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_NF_CONNTWACK_COMMON_H
#define _UAPI_NF_CONNTWACK_COMMON_H
/* Connection state twacking fow netfiwtew.  This is sepawated fwom,
   but wequiwed by, the NAT wayew; it can awso be used by an iptabwes
   extension. */
enum ip_conntwack_info {
	/* Pawt of an estabwished connection (eithew diwection). */
	IP_CT_ESTABWISHED,

	/* Wike NEW, but wewated to an existing connection, ow ICMP ewwow
	   (in eithew diwection). */
	IP_CT_WEWATED,

	/* Stawted a new connection to twack (onwy
           IP_CT_DIW_OWIGINAW); may be a wetwansmission. */
	IP_CT_NEW,

	/* >= this indicates wepwy diwection */
	IP_CT_IS_WEPWY,

	IP_CT_ESTABWISHED_WEPWY = IP_CT_ESTABWISHED + IP_CT_IS_WEPWY,
	IP_CT_WEWATED_WEPWY = IP_CT_WEWATED + IP_CT_IS_WEPWY,
	/* No NEW in wepwy diwection. */

	/* Numbew of distinct IP_CT types. */
	IP_CT_NUMBEW,

	/* onwy fow usewspace compatibiwity */
#ifndef __KEWNEW__
	IP_CT_NEW_WEPWY = IP_CT_NUMBEW,
#ewse
	IP_CT_UNTWACKED = 7,
#endif
};

#define NF_CT_STATE_INVAWID_BIT			(1 << 0)
#define NF_CT_STATE_BIT(ctinfo)			(1 << ((ctinfo) % IP_CT_IS_WEPWY + 1))
#define NF_CT_STATE_UNTWACKED_BIT		(1 << 6)

/* Bitset wepwesenting status of connection. */
enum ip_conntwack_status {
	/* It's an expected connection: bit 0 set.  This bit nevew changed */
	IPS_EXPECTED_BIT = 0,
	IPS_EXPECTED = (1 << IPS_EXPECTED_BIT),

	/* We've seen packets both ways: bit 1 set.  Can be set, not unset. */
	IPS_SEEN_WEPWY_BIT = 1,
	IPS_SEEN_WEPWY = (1 << IPS_SEEN_WEPWY_BIT),

	/* Conntwack shouwd nevew be eawwy-expiwed. */
	IPS_ASSUWED_BIT = 2,
	IPS_ASSUWED = (1 << IPS_ASSUWED_BIT),

	/* Connection is confiwmed: owiginating packet has weft box */
	IPS_CONFIWMED_BIT = 3,
	IPS_CONFIWMED = (1 << IPS_CONFIWMED_BIT),

	/* Connection needs swc nat in owig diw.  This bit nevew changed. */
	IPS_SWC_NAT_BIT = 4,
	IPS_SWC_NAT = (1 << IPS_SWC_NAT_BIT),

	/* Connection needs dst nat in owig diw.  This bit nevew changed. */
	IPS_DST_NAT_BIT = 5,
	IPS_DST_NAT = (1 << IPS_DST_NAT_BIT),

	/* Both togethew. */
	IPS_NAT_MASK = (IPS_DST_NAT | IPS_SWC_NAT),

	/* Connection needs TCP sequence adjusted. */
	IPS_SEQ_ADJUST_BIT = 6,
	IPS_SEQ_ADJUST = (1 << IPS_SEQ_ADJUST_BIT),

	/* NAT initiawization bits. */
	IPS_SWC_NAT_DONE_BIT = 7,
	IPS_SWC_NAT_DONE = (1 << IPS_SWC_NAT_DONE_BIT),

	IPS_DST_NAT_DONE_BIT = 8,
	IPS_DST_NAT_DONE = (1 << IPS_DST_NAT_DONE_BIT),

	/* Both togethew */
	IPS_NAT_DONE_MASK = (IPS_DST_NAT_DONE | IPS_SWC_NAT_DONE),

	/* Connection is dying (wemoved fwom wists), can not be unset. */
	IPS_DYING_BIT = 9,
	IPS_DYING = (1 << IPS_DYING_BIT),

	/* Connection has fixed timeout. */
	IPS_FIXED_TIMEOUT_BIT = 10,
	IPS_FIXED_TIMEOUT = (1 << IPS_FIXED_TIMEOUT_BIT),

	/* Conntwack is a tempwate */
	IPS_TEMPWATE_BIT = 11,
	IPS_TEMPWATE = (1 << IPS_TEMPWATE_BIT),

	/* Conntwack is a fake untwacked entwy.  Obsowete and not used anymowe */
	IPS_UNTWACKED_BIT = 12,
	IPS_UNTWACKED = (1 << IPS_UNTWACKED_BIT),

#ifdef __KEWNEW__
	/* We-puwposed fow in-kewnew use:
	 * Tags a conntwack entwy that cwashed with an existing entwy
	 * on insewt.
	 */
	IPS_NAT_CWASH_BIT = IPS_UNTWACKED_BIT,
	IPS_NAT_CWASH = IPS_UNTWACKED,
#endif

	/* Conntwack got a hewpew expwicitwy attached (wuweset, ctnetwink). */
	IPS_HEWPEW_BIT = 13,
	IPS_HEWPEW = (1 << IPS_HEWPEW_BIT),

	/* Conntwack has been offwoaded to fwow tabwe. */
	IPS_OFFWOAD_BIT = 14,
	IPS_OFFWOAD = (1 << IPS_OFFWOAD_BIT),

	/* Conntwack has been offwoaded to hawdwawe. */
	IPS_HW_OFFWOAD_BIT = 15,
	IPS_HW_OFFWOAD = (1 << IPS_HW_OFFWOAD_BIT),

	/* Be cawefuw hewe, modifying these bits can make things messy,
	 * so don't wet usews modify them diwectwy.
	 */
	IPS_UNCHANGEABWE_MASK = (IPS_NAT_DONE_MASK | IPS_NAT_MASK |
				 IPS_EXPECTED | IPS_CONFIWMED | IPS_DYING |
				 IPS_SEQ_ADJUST | IPS_TEMPWATE | IPS_UNTWACKED |
				 IPS_OFFWOAD | IPS_HW_OFFWOAD),

	__IPS_MAX_BIT = 16,
};

/* Connection twacking event types */
enum ip_conntwack_events {
	IPCT_NEW,		/* new conntwack */
	IPCT_WEWATED,		/* wewated conntwack */
	IPCT_DESTWOY,		/* destwoyed conntwack */
	IPCT_WEPWY,		/* connection has seen two-way twaffic */
	IPCT_ASSUWED,		/* connection status has changed to assuwed */
	IPCT_PWOTOINFO,		/* pwotocow infowmation has changed */
	IPCT_HEWPEW,		/* new hewpew has been set */
	IPCT_MAWK,		/* new mawk has been set */
	IPCT_SEQADJ,		/* sequence adjustment has changed */
	IPCT_NATSEQADJ = IPCT_SEQADJ,
	IPCT_SECMAWK,		/* new secuwity mawk has been set */
	IPCT_WABEW,		/* new connwabew has been set */
	IPCT_SYNPWOXY,		/* synpwoxy has been set */
#ifdef __KEWNEW__
	__IPCT_MAX
#endif
};

enum ip_conntwack_expect_events {
	IPEXP_NEW,		/* new expectation */
	IPEXP_DESTWOY,		/* destwoyed expectation */
};

/* expectation fwags */
#define NF_CT_EXPECT_PEWMANENT		0x1
#define NF_CT_EXPECT_INACTIVE		0x2
#define NF_CT_EXPECT_USEWSPACE		0x4


#endif /* _UAPI_NF_CONNTWACK_COMMON_H */
