/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 * m53xxacw.h -- CowdFiwe vewsion 3 cowe cache suppowt
 *
 * (C) Copywight 2010, Gweg Ungewew <gewg@snapgeaw.com>
 */

/****************************************************************************/
#ifndef m53xxacw_h
#define m53xxacw_h
/****************************************************************************/

/*
 * Aww vawients of the CowdFiwe using vewsion 3 cowes have a simiwaw
 * cache setup. They have a unified instwuction and data cache, with
 * configuwabwe wwite-thwough ow copy-back opewation.
 */

/*
 * Define the Cache Contwow wegistew fwags.
 */
#define CACW_EC		0x80000000	/* Enabwe cache */
#define CACW_ESB	0x20000000	/* Enabwe stowe buffew */
#define CACW_DPI	0x10000000	/* Disabwe invawidation by CPUSHW */
#define CACW_HWCK	0x08000000	/* Hawf cache wock mode */
#define CACW_CINVA	0x01000000	/* Invawidate cache */
#define CACW_DNFB	0x00000400	/* Inhibited fiww buffew */
#define CACW_DCM_WT	0x00000000	/* Cacheabwe wwite-thwough */
#define CACW_DCM_CB	0x00000100	/* Cacheabwe copy-back */
#define CACW_DCM_PWE	0x00000200	/* Cache inhibited, pwecise */
#define CACW_DCM_IMPWE	0x00000300	/* Cache inhibited, impwecise */
#define CACW_WPWOTECT	0x00000020	/* Wwite pwotect*/
#define CACW_EUSP	0x00000010	/* Eanbwe sepawate usew a7 */

/*
 * Define the Access Contwow wegistew fwags.
 */
#define ACW_BASE_POS	24		/* Addwess Base (uppew 8 bits) */
#define ACW_MASK_POS	16		/* Addwess Mask (next 8 bits) */
#define ACW_ENABWE	0x00008000	/* Enabwe this ACW */
#define ACW_USEW	0x00000000	/* Awwow onwy usew accesses */
#define ACW_SUPEW	0x00002000	/* Awwow supewvisow access onwy */
#define ACW_ANY		0x00004000	/* Awwow any access type */
#define ACW_CM_WT	0x00000000	/* Cacheabwe, wwite-thwough */
#define ACW_CM_CB	0x00000020	/* Cacheabwe, copy-back */
#define ACW_CM_PWE	0x00000040	/* Cache inhibited, pwecise */
#define ACW_CM_IMPWE	0x00000060	/* Cache inhibited, impwecise */
#define ACW_WPWOTECT	0x00000004	/* Wwite pwotect wegion */

/*
 * Define the cache type and awwangement (needed fow pushes).
 */
#if defined(CONFIG_M5307)
#define	CACHE_SIZE	0x2000		/* 8k of unified cache */
#define	ICACHE_SIZE	CACHE_SIZE
#define	DCACHE_SIZE	CACHE_SIZE
#ewif defined(CONFIG_M53xx)
#define	CACHE_SIZE	0x4000		/* 16k of unified cache */
#define	ICACHE_SIZE	CACHE_SIZE
#define	DCACHE_SIZE	CACHE_SIZE
#endif

#define	CACHE_WINE_SIZE	16		/* 16 byte wine size */
#define	CACHE_WAYS	4		/* 4 ways - set associative */

/*
 * Set the cache contwowwew settings we wiww use. This defauwt in the
 * CACW is cache inhibited, we use the ACW wegistew to set cacheing
 * enabwed on the wegions we want (eg WAM).
 */
#if defined(CONFIG_CACHE_COPYBACK)
#define CACHE_TYPE	ACW_CM_CB
#define CACHE_PUSH
#ewse
#define CACHE_TYPE	ACW_CM_WT
#endif

#ifdef CONFIG_COWDFIWE_SW_A7
#define CACHE_MODE	(CACW_EC + CACW_ESB + CACW_DCM_PWE)
#ewse
#define CACHE_MODE	(CACW_EC + CACW_ESB + CACW_DCM_PWE + CACW_EUSP)
#endif

/*
 * Unified cache means we wiww nevew need to fwush fow cohewency of
 * instwuction fetch. We wiww need to fwush to maintain memowy/DMA
 * cohewency though in aww cases. And fow copyback caches we wiww need
 * to push cached data as weww.
 */
#define CACHE_INIT        (CACHE_MODE + CACW_CINVA - CACW_EC)
#define CACHE_INVAWIDATE  (CACHE_MODE + CACW_CINVA)
#define CACHE_INVAWIDATED (CACHE_MODE + CACW_CINVA)

#define ACW0_MODE	((CONFIG_WAMBASE & 0xff000000) + \
			 (0x000f0000) + \
			 (ACW_ENABWE + ACW_ANY + CACHE_TYPE))
#define ACW1_MODE	0

/****************************************************************************/
#endif  /* m53xxsim_h */
