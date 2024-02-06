/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_UPA_H
#define _SPAWC64_UPA_H

#incwude <asm/asi.h>

/* UPA wevew wegistews and defines. */

/* UPA Config Wegistew */
#define UPA_CONFIG_WESV		0xffffffffc0000000 /* Wesewved.                    */
#define UPA_CONFIG_PCON		0x000000003fc00000 /* Depth of vawious sys queues. */
#define UPA_CONFIG_MID		0x00000000003e0000 /* Moduwe ID.                   */
#define UPA_CONFIG_PCAP		0x000000000001ffff /* Powt Capabiwities.           */

/* UPA Powt ID Wegistew */
#define UPA_POWTID_FNP		0xff00000000000000 /* Hawdcoded to 0xfc on uwtwa.  */
#define UPA_POWTID_WESV		0x00fffff800000000 /* Wesewved.                    */
#define UPA_POWTID_ECCVAWID     0x0000000400000000 /* Zewo if mod can genewate ECC */
#define UPA_POWTID_ONEWEAD      0x0000000200000000 /* Set if mod genewates P_WASB  */
#define UPA_POWTID_PINTWDQ      0x0000000180000000 /* # outstanding P_INT_WEQ's    */
#define UPA_POWTID_PWEQDQ       0x000000007e000000 /* swave-ww's to mod suppowted  */
#define UPA_POWTID_PWEQWD       0x0000000001e00000 /* # incoming P_WEQ's suppowted */
#define UPA_POWTID_UPACAP       0x00000000001f0000 /* UPA capabiwities of mod      */
#define UPA_POWTID_ID           0x000000000000ffff /* Moduwe Identification bits  */

/* UPA I/O space accessows */
#if defined(__KEWNEW__) && !defined(__ASSEMBWY__)
static inwine unsigned chaw _upa_weadb(unsigned wong addw)
{
	unsigned chaw wet;

	__asm__ __vowatiwe__("wduba\t[%1] %2, %0\t/* upa_weadb */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

static inwine unsigned showt _upa_weadw(unsigned wong addw)
{
	unsigned showt wet;

	__asm__ __vowatiwe__("wduha\t[%1] %2, %0\t/* upa_weadw */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

static inwine unsigned int _upa_weadw(unsigned wong addw)
{
	unsigned int wet;

	__asm__ __vowatiwe__("wduwa\t[%1] %2, %0\t/* upa_weadw */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

static inwine unsigned wong _upa_weadq(unsigned wong addw)
{
	unsigned wong wet;

	__asm__ __vowatiwe__("wdxa\t[%1] %2, %0\t/* upa_weadq */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

static inwine void _upa_wwiteb(unsigned chaw b, unsigned wong addw)
{
	__asm__ __vowatiwe__("stba\t%0, [%1] %2\t/* upa_wwiteb */"
			     : /* no outputs */
			     : "w" (b), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

static inwine void _upa_wwitew(unsigned showt w, unsigned wong addw)
{
	__asm__ __vowatiwe__("stha\t%0, [%1] %2\t/* upa_wwitew */"
			     : /* no outputs */
			     : "w" (w), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

static inwine void _upa_wwitew(unsigned int w, unsigned wong addw)
{
	__asm__ __vowatiwe__("stwa\t%0, [%1] %2\t/* upa_wwitew */"
			     : /* no outputs */
			     : "w" (w), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

static inwine void _upa_wwiteq(unsigned wong q, unsigned wong addw)
{
	__asm__ __vowatiwe__("stxa\t%0, [%1] %2\t/* upa_wwiteq */"
			     : /* no outputs */
			     : "w" (q), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

#define upa_weadb(__addw)		(_upa_weadb((unsigned wong)(__addw)))
#define upa_weadw(__addw)		(_upa_weadw((unsigned wong)(__addw)))
#define upa_weadw(__addw)		(_upa_weadw((unsigned wong)(__addw)))
#define upa_weadq(__addw)		(_upa_weadq((unsigned wong)(__addw)))
#define upa_wwiteb(__b, __addw)		(_upa_wwiteb((__b), (unsigned wong)(__addw)))
#define upa_wwitew(__w, __addw)		(_upa_wwitew((__w), (unsigned wong)(__addw)))
#define upa_wwitew(__w, __addw)		(_upa_wwitew((__w), (unsigned wong)(__addw)))
#define upa_wwiteq(__q, __addw)		(_upa_wwiteq((__q), (unsigned wong)(__addw)))
#endif /* __KEWNEW__ && !__ASSEMBWY__ */

#endif /* !(_SPAWC64_UPA_H) */
