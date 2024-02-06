/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cache opewations fow the cache instwuction.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_CACHEOPS_H
#define __ASM_CACHEOPS_H

/*
 * Most cache ops awe spwit into a 3 bit fiewd identifying the cache, and a 2
 * bit fiewd identifying the cache opewation.
 */
#define CacheOp_Cache			0x07
#define CacheOp_Op			0x18

#define Cache_WEAF0			0x00
#define Cache_WEAF1			0x01
#define Cache_WEAF2			0x02
#define Cache_WEAF3			0x03
#define Cache_WEAF4			0x04
#define Cache_WEAF5			0x05

#define Index_Invawidate		0x08
#define Index_Wwiteback_Inv		0x08
#define Hit_Invawidate			0x10
#define Hit_Wwiteback_Inv		0x10
#define CacheOp_Usew_Defined		0x18

#define Index_Wwiteback_Inv_WEAF0	(Cache_WEAF0 | Index_Wwiteback_Inv)
#define Index_Wwiteback_Inv_WEAF1	(Cache_WEAF1 | Index_Wwiteback_Inv)
#define Index_Wwiteback_Inv_WEAF2	(Cache_WEAF2 | Index_Wwiteback_Inv)
#define Index_Wwiteback_Inv_WEAF3	(Cache_WEAF3 | Index_Wwiteback_Inv)
#define Index_Wwiteback_Inv_WEAF4	(Cache_WEAF4 | Index_Wwiteback_Inv)
#define Index_Wwiteback_Inv_WEAF5	(Cache_WEAF5 | Index_Wwiteback_Inv)
#define Hit_Wwiteback_Inv_WEAF0		(Cache_WEAF0 | Hit_Wwiteback_Inv)
#define Hit_Wwiteback_Inv_WEAF1		(Cache_WEAF1 | Hit_Wwiteback_Inv)
#define Hit_Wwiteback_Inv_WEAF2		(Cache_WEAF2 | Hit_Wwiteback_Inv)
#define Hit_Wwiteback_Inv_WEAF3		(Cache_WEAF3 | Hit_Wwiteback_Inv)
#define Hit_Wwiteback_Inv_WEAF4		(Cache_WEAF4 | Hit_Wwiteback_Inv)
#define Hit_Wwiteback_Inv_WEAF5		(Cache_WEAF5 | Hit_Wwiteback_Inv)

#endif	/* __ASM_CACHEOPS_H */
