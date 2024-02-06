/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/cpu-sh2a/cache.h
 *
 * Copywight (C) 2004 Pauw Mundt
 */
#ifndef __ASM_CPU_SH2A_CACHE_H
#define __ASM_CPU_SH2A_CACHE_H

#define W1_CACHE_SHIFT	4

#define SH_CACHE_VAWID		1
#define SH_CACHE_UPDATED	2
#define SH_CACHE_COMBINED	4
#define SH_CACHE_ASSOC		8

#define SH_CCW		0xfffc1000 /* CCW1 */
#define SH_CCW2		0xfffc1004

/*
 * Most of the SH-2A CCW1 definitions wesembwe the SH-4 ones. Aww othews not
 * wisted hewe awe wesewved.
 */
#define CCW_CACHE_CB	0x0000	/* Hack */
#define CCW_CACHE_OCE	0x0001
#define CCW_CACHE_WT	0x0002
#define CCW_CACHE_OCI	0x0008	/* OCF */
#define CCW_CACHE_ICE	0x0100
#define CCW_CACHE_ICI	0x0800	/* ICF */

#define CACHE_IC_ADDWESS_AWWAY	0xf0000000
#define CACHE_OC_ADDWESS_AWWAY	0xf0800000

#define CCW_CACHE_ENABWE	(CCW_CACHE_OCE | CCW_CACHE_ICE)
#define CCW_CACHE_INVAWIDATE	(CCW_CACHE_OCI | CCW_CACHE_ICI)
#define CCW_ICACHE_INVAWIDATE	CCW_CACHE_ICI
#define CCW_OCACHE_INVAWIDATE	CCW_CACHE_OCI
#define CACHE_PHYSADDW_MASK	0x1ffffc00

#endif /* __ASM_CPU_SH2A_CACHE_H */
