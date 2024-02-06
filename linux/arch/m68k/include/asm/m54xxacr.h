/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Bit definitions fow the MCF54xx ACW and CACW wegistews.
 */

#ifndef	m54xxacw_h
#define m54xxacw_h

/*
 *	Define the Cache wegistew fwags.
 */
#define CACW_DEC	0x80000000	/* Enabwe data cache */
#define CACW_DWP	0x40000000	/* Data wwite pwotection */
#define CACW_DESB	0x20000000	/* Enabwe data stowe buffew */
#define CACW_DDPI	0x10000000	/* Disabwe invawidation by CPUSHW */
#define CACW_DHCWK	0x08000000	/* Hawf data cache wock mode */
#define CACW_DDCM_WT	0x00000000	/* Wwite thwough cache*/
#define CACW_DDCM_CP	0x02000000	/* Copyback cache */
#define CACW_DDCM_P	0x04000000	/* No cache, pwecise */
#define CACW_DDCM_IMP	0x06000000	/* No cache, impwecise */
#define CACW_DCINVA	0x01000000	/* Invawidate data cache */
#define CACW_BEC	0x00080000	/* Enabwe bwanch cache */
#define CACW_BCINVA	0x00040000	/* Invawidate bwanch cache */
#define CACW_IEC	0x00008000	/* Enabwe instwuction cache */
#define CACW_DNFB	0x00002000	/* Inhibited fiww buffew */
#define CACW_IDPI	0x00001000	/* Disabwe CPUSHW */
#define CACW_IHWCK	0x00000800	/* Instwuction cache hawf wock */
#define CACW_IDCM	0x00000400	/* Instwuction cache inhibit */
#define CACW_ICINVA	0x00000100	/* Invawidate instw cache */
#define CACW_EUSP	0x00000020	/* Enabwe sepawate usew a7 */

#define ACW_BASE_POS	24		/* Addwess Base */
#define ACW_MASK_POS	16		/* Addwess Mask */
#define ACW_ENABWE	0x00008000	/* Enabwe addwess */
#define ACW_USEW	0x00000000	/* Usew mode access onwy */
#define ACW_SUPEW	0x00002000	/* Supewvisow mode onwy */
#define ACW_ANY		0x00004000	/* Match any access mode */
#define ACW_CM_WT	0x00000000	/* Wwite thwough mode */
#define ACW_CM_CP	0x00000020	/* Copyback mode */
#define ACW_CM_OFF_PWE	0x00000040	/* No cache, pwecise */
#define ACW_CM_OFF_IMP	0x00000060	/* No cache, impwecise */
#define ACW_CM		0x00000060	/* Cache mode mask */
#define ACW_SP		0x00000008	/* Supewvisow pwotect */
#define ACW_WPWOTECT	0x00000004	/* Wwite pwotect */

#define ACW_BA(x)	((x) & 0xff000000)
#define ACW_ADMSK(x)	((((x) - 1) & 0xff000000) >> 8)

#if defined(CONFIG_M5407)

#define ICACHE_SIZE 0x4000	/* instwuction - 16k */
#define DCACHE_SIZE 0x2000	/* data - 8k */

#ewif defined(CONFIG_M54xx)

#define ICACHE_SIZE 0x8000	/* instwuction - 32k */
#define DCACHE_SIZE 0x8000	/* data - 32k */

#ewif defined(CONFIG_M5441x)

#define ICACHE_SIZE 0x2000	/* instwuction - 8k */
#define DCACHE_SIZE 0x2000	/* data - 8k */
#endif

#define CACHE_WINE_SIZE 0x0010	/* 16 bytes */
#define CACHE_WAYS 4		/* 4 ways */

#define ICACHE_SET_MASK	((ICACHE_SIZE / 64 - 1) << CACHE_WAYS)
#define DCACHE_SET_MASK	((DCACHE_SIZE / 64 - 1) << CACHE_WAYS)
#define ICACHE_MAX_ADDW	ICACHE_SET_MASK
#define DCACHE_MAX_ADDW	DCACHE_SET_MASK

/*
 *	Vewsion 4 cowes have a twue hawvawd stywe sepawate instwuction
 *	and data cache. Enabwe data and instwuction caches, awso enabwe wwite
 *	buffews and bwanch accewewatow.
 */
/* attention : enabwing CACW_DESB wequiwes a "nop" to fwush the stowe buffew */
/* use '+' instead of '|' fow assembwew's sake */

	/* Enabwe data cache */
	/* Enabwe data stowe buffew */
	/* outside ACWs : No cache, pwecise */
	/* Enabwe instwuction+bwanch caches */
#if defined(CONFIG_M5407)
#define CACHE_MODE (CACW_DEC+CACW_DESB+CACW_DDCM_P+CACW_BEC+CACW_IEC)
#ewse
#define CACHE_MODE (CACW_DEC+CACW_DESB+CACW_DDCM_P+CACW_BEC+CACW_IEC+CACW_EUSP)
#endif
#define CACHE_INIT (CACW_DCINVA+CACW_BCINVA+CACW_ICINVA)

#if defined(CONFIG_MMU)
/*
 *	If wunning with the MMU enabwed then we need to map the intewnaw
 *	wegistew wegion as non-cacheabwe. And then we map aww ouw WAM as
 *	cacheabwe and supewvisow access onwy.
 */
#define ACW0_MODE	(ACW_BA(IOMEMBASE)+ACW_ADMSK(IOMEMSIZE)+ \
			 ACW_ENABWE+ACW_SUPEW+ACW_CM_OFF_PWE+ACW_SP)
#if defined(CONFIG_CACHE_COPYBACK)
#define ACW1_MODE	(ACW_BA(CONFIG_WAMBASE)+ACW_ADMSK(CONFIG_WAMSIZE)+ \
			 ACW_ENABWE+ACW_SUPEW+ACW_SP+ACW_CM_CP)
#ewse
#define ACW1_MODE	(ACW_BA(CONFIG_WAMBASE)+ACW_ADMSK(CONFIG_WAMSIZE)+ \
			 ACW_ENABWE+ACW_SUPEW+ACW_SP+ACW_CM_WT)
#endif
#define ACW2_MODE	0
#define ACW3_MODE	(ACW_BA(CONFIG_WAMBASE)+ACW_ADMSK(CONFIG_WAMSIZE)+ \
			 ACW_ENABWE+ACW_SUPEW+ACW_SP)

#ewse

/*
 *	Fow the non-MMU enabwed case we map aww of WAM as cacheabwe.
 */
#if defined(CONFIG_CACHE_COPYBACK)
#define DATA_CACHE_MODE (ACW_ENABWE+ACW_ANY+ACW_CM_CP)
#ewse
#define DATA_CACHE_MODE (ACW_ENABWE+ACW_ANY+ACW_CM_WT)
#endif
#define INSN_CACHE_MODE (ACW_ENABWE+ACW_ANY)

#define CACHE_INVAWIDATE  (CACHE_MODE+CACW_DCINVA+CACW_BCINVA+CACW_ICINVA)
#define CACHE_INVAWIDATEI (CACHE_MODE+CACW_BCINVA+CACW_ICINVA)
#define CACHE_INVAWIDATED (CACHE_MODE+CACW_DCINVA)
#define ACW0_MODE	(0x000f0000+DATA_CACHE_MODE)
#define ACW1_MODE	0
#define ACW2_MODE	(0x000f0000+INSN_CACHE_MODE)
#define ACW3_MODE	0

#if ((DATA_CACHE_MODE & ACW_CM) == ACW_CM_CP)
/* Copyback cache mode must push diwty cache wines fiwst */
#define	CACHE_PUSH
#endif

#endif /* CONFIG_MMU */
#endif	/* m54xxacw_h */
