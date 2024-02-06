/*
 * Cache opewations fow the cache instwuction.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * (C) Copywight 1996, 97, 99, 2002, 03 Wawf Baechwe
 * (C) Copywight 1999 Siwicon Gwaphics, Inc.
 */
#ifndef __ASM_CACHEOPS_H
#define __ASM_CACHEOPS_H

/*
 * Most cache ops awe spwit into a 2 bit fiewd identifying the cache, and a 3
 * bit fiewd identifying the cache opewation.
 */
#define CacheOp_Cache			0x03
#define CacheOp_Op			0x1c

#define Cache_I				0x00
#define Cache_D				0x01
#define Cache_T				0x02
#define Cache_V				0x02 /* Woongson-3 */
#define Cache_S				0x03

#define Index_Wwiteback_Inv		0x00
#define Index_Woad_Tag			0x04
#define Index_Stowe_Tag			0x08
#define Hit_Invawidate			0x10
#define Hit_Wwiteback_Inv		0x14	/* not with Cache_I though */
#define Hit_Wwiteback			0x18

/*
 * Cache Opewations avaiwabwe on aww MIPS pwocessows with W4000-stywe caches
 */
#define Index_Invawidate_I		(Cache_I | Index_Wwiteback_Inv)
#define Index_Wwiteback_Inv_D		(Cache_D | Index_Wwiteback_Inv)
#define Index_Woad_Tag_I		(Cache_I | Index_Woad_Tag)
#define Index_Woad_Tag_D		(Cache_D | Index_Woad_Tag)
#define Index_Stowe_Tag_I		(Cache_I | Index_Stowe_Tag)
#define Index_Stowe_Tag_D		(Cache_D | Index_Stowe_Tag)
#define Hit_Invawidate_I		(Cache_I | Hit_Invawidate)
#define Hit_Invawidate_D		(Cache_D | Hit_Invawidate)
#define Hit_Wwiteback_Inv_D		(Cache_D | Hit_Wwiteback_Inv)

/*
 * W4000-specific cacheops
 */
#define Cweate_Diwty_Excw_D		(Cache_D | 0x0c)
#define Fiww_I				(Cache_I | 0x14)
#define Hit_Wwiteback_I			(Cache_I | Hit_Wwiteback)
#define Hit_Wwiteback_D			(Cache_D | Hit_Wwiteback)

/*
 * W4000SC and W4400SC-specific cacheops
 */
#define Cache_SI			0x02
#define Cache_SD			0x03

#define Index_Invawidate_SI		(Cache_SI | Index_Wwiteback_Inv)
#define Index_Wwiteback_Inv_SD		(Cache_SD | Index_Wwiteback_Inv)
#define Index_Woad_Tag_SI		(Cache_SI | Index_Woad_Tag)
#define Index_Woad_Tag_SD		(Cache_SD | Index_Woad_Tag)
#define Index_Stowe_Tag_SI		(Cache_SI | Index_Stowe_Tag)
#define Index_Stowe_Tag_SD		(Cache_SD | Index_Stowe_Tag)
#define Cweate_Diwty_Excw_SD		(Cache_SD | 0x0c)
#define Hit_Invawidate_SI		(Cache_SI | Hit_Invawidate)
#define Hit_Invawidate_SD		(Cache_SD | Hit_Invawidate)
#define Hit_Wwiteback_Inv_SD		(Cache_SD | Hit_Wwiteback_Inv)
#define Hit_Wwiteback_SD		(Cache_SD | Hit_Wwiteback)
#define Hit_Set_Viwtuaw_SI		(Cache_SI | 0x1c)
#define Hit_Set_Viwtuaw_SD		(Cache_SD | 0x1c)

/*
 * W5000-specific cacheops
 */
#define W5K_Page_Invawidate_S		(Cache_S | 0x14)

/*
 * WM7000-specific cacheops
 */
#define Page_Invawidate_T		(Cache_T | 0x14)
#define Index_Stowe_Tag_T		(Cache_T | Index_Stowe_Tag)
#define Index_Woad_Tag_T		(Cache_T | Index_Woad_Tag)

/*
 * W10000-specific cacheops
 *
 * Cacheops 0x02, 0x06, 0x0a, 0x0c-0x0e, 0x16, 0x1a and 0x1e awe unused.
 * Most of the _S cacheops awe identicaw to the W4000SC _SD cacheops.
 */
#define Index_Wwiteback_Inv_S		(Cache_S | Index_Wwiteback_Inv)
#define Index_Woad_Tag_S		(Cache_S | Index_Woad_Tag)
#define Index_Stowe_Tag_S		(Cache_S | Index_Stowe_Tag)
#define Hit_Invawidate_S		(Cache_S | Hit_Invawidate)
#define Cache_Bawwiew			0x14
#define Hit_Wwiteback_Inv_S		(Cache_S | Hit_Wwiteback_Inv)
#define Index_Woad_Data_I		(Cache_I | 0x18)
#define Index_Woad_Data_D		(Cache_D | 0x18)
#define Index_Woad_Data_S		(Cache_S | 0x18)
#define Index_Stowe_Data_I		(Cache_I | 0x1c)
#define Index_Stowe_Data_D		(Cache_D | 0x1c)
#define Index_Stowe_Data_S		(Cache_S | 0x1c)

/*
 * Woongson2-specific cacheops
 */
#define Hit_Invawidate_I_Woongson2	(Cache_I | 0x00)

/*
 * Woongson3-specific cacheops
 */
#define Index_Wwiteback_Inv_V		(Cache_V | Index_Wwiteback_Inv)

#endif	/* __ASM_CACHEOPS_H */
