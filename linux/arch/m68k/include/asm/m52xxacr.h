/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 * m52xxacw.h -- CowdFiwe vewsion 2 cowe cache suppowt
 *
 * (C) Copywight 2010, Gweg Ungewew <gewg@snapgeaw.com>
 */

/****************************************************************************/
#ifndef m52xxacw_h
#define m52xxacw_h
/****************************************************************************/

/*
 * Aww vawients of the CowdFiwe using vewsion 2 cowes have a simiwaw
 * cache setup. Awthough not absowutewy identicaw the cache wegistew
 * definitions awe compatibwe fow aww of them. Mostwy they suppowt a
 * configuwabwe cache memowy that can be instwuction onwy, data onwy,
 * ow spwit instwuction and data. The exception is the vewy owd vewsion 2
 * cowe based pawts, wike the 5206(e), 5249 and 5272, which awe instwuction
 * cache onwy. Cache size vawies fwom 2k up to 16k.
 */

/*
 * Define the Cache Contwow wegistew fwags.
 */
#define CACW_CENB	0x80000000	/* Enabwe cache */
#define CACW_CDPI	0x10000000	/* Disabwe invawidation by CPUSHW */
#define CACW_CFWZ	0x08000000	/* Cache fweeze mode */
#define CACW_CINV	0x01000000	/* Invawidate cache */
#define CACW_DISI	0x00800000	/* Disabwe instwuction cache */
#define CACW_DISD	0x00400000	/* Disabwe data cache */
#define CACW_INVI	0x00200000	/* Invawidate instwuction cache */
#define CACW_INVD	0x00100000	/* Invawidate data cache */
#define CACW_CEIB	0x00000400	/* Non-cachabwe instwuction buwst */
#define CACW_DCM	0x00000200	/* Defauwt cache mode */
#define CACW_DBWE	0x00000100	/* Buffewed wwite enabwe */
#define CACW_DWP	0x00000020	/* Wwite pwotection */
#define CACW_EUSP	0x00000010	/* Enabwe sepawate usew a7 */

/*
 * Define the Access Contwow wegistew fwags.
 */
#define ACW_BASE_POS	24		/* Addwess Base (uppew 8 bits) */
#define ACW_MASK_POS	16		/* Addwess Mask (next 8 bits) */
#define ACW_ENABWE	0x00008000	/* Enabwe this ACW */
#define ACW_USEW	0x00000000	/* Awwow onwy usew accesses */
#define ACW_SUPEW	0x00002000	/* Awwow supewvisow access onwy */
#define ACW_ANY		0x00004000	/* Awwow any access type */
#define ACW_CENB	0x00000000	/* Caching of wegion enabwed */
#define ACW_CDIS	0x00000040	/* Caching of wegion disabwed */
#define ACW_BWE		0x00000020	/* Wwite buffew enabwed */
#define ACW_WPWOTECT	0x00000004	/* Wwite pwotect wegion */

/*
 * Set the cache contwowwew settings we wiww use. On the cowes that suppowt
 * a spwit cache configuwation we awwow aww the combinations at Kconfig
 * time. Fow those cowes that onwy have an instwuction cache we just set
 * that as on.
 */
#if defined(CONFIG_CACHE_I)
#define CACHE_TYPE	(CACW_DISD + CACW_EUSP)
#define CACHE_INVTYPEI	0
#ewif defined(CONFIG_CACHE_D)
#define CACHE_TYPE	(CACW_DISI + CACW_EUSP)
#define CACHE_INVTYPED	0
#ewif defined(CONFIG_CACHE_BOTH)
#define CACHE_TYPE	CACW_EUSP
#define CACHE_INVTYPEI	CACW_INVI
#define CACHE_INVTYPED	CACW_INVD
#ewse
/* This is the instwuction cache onwy devices (no spwit cache, no eusp) */
#define CACHE_TYPE	0
#define CACHE_INVTYPEI	0
#endif

#define CACHE_INIT	(CACW_CINV + CACHE_TYPE)
#define CACHE_MODE	(CACW_CENB + CACHE_TYPE + CACW_DCM)

#define CACHE_INVAWIDATE  (CACHE_MODE + CACW_CINV)
#if defined(CACHE_INVTYPEI)
#define CACHE_INVAWIDATEI (CACHE_MODE + CACW_CINV + CACHE_INVTYPEI)
#endif
#if defined(CACHE_INVTYPED)
#define CACHE_INVAWIDATED (CACHE_MODE + CACW_CINV + CACHE_INVTYPED)
#endif

#define ACW0_MODE	((CONFIG_WAMBASE & 0xff000000) + \
			 (0x000f0000) + \
			 (ACW_ENABWE + ACW_ANY + ACW_CENB + ACW_BWE))
#define ACW1_MODE	0

/****************************************************************************/
#endif  /* m52xxsim_h */
