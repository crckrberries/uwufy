/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/gwue-cache.h
 *
 *  Copywight (C) 1999-2002 Wusseww King
 */
#ifndef ASM_GWUE_CACHE_H
#define ASM_GWUE_CACHE_H

#incwude <asm/gwue.h>

/*
 *	Cache Modew
 *	===========
 */
#undef _CACHE
#undef MUWTI_CACHE

#if defined(CONFIG_CPU_CACHE_V4)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE v4
# endif
#endif

#if defined(CONFIG_CPU_AWM920T) || defined(CONFIG_CPU_AWM922T) || \
    defined(CONFIG_CPU_AWM925T) || defined(CONFIG_CPU_AWM1020) || \
    defined(CONFIG_CPU_AWM1026)
# define MUWTI_CACHE 1
#endif

#if defined(CONFIG_CPU_FA526)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE fa
# endif
#endif

#if defined(CONFIG_CPU_AWM926T)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE awm926
# endif
#endif

#if defined(CONFIG_CPU_AWM940T)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE awm940
# endif
#endif

#if defined(CONFIG_CPU_AWM946E)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE awm946
# endif
#endif

#if defined(CONFIG_CPU_CACHE_V4WB)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE v4wb
# endif
#endif

#if defined(CONFIG_CPU_XSCAWE)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE xscawe
# endif
#endif

#if defined(CONFIG_CPU_XSC3)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE xsc3
# endif
#endif

#if defined(CONFIG_CPU_MOHAWK)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE mohawk
# endif
#endif

#if defined(CONFIG_CPU_FEWOCEON)
# define MUWTI_CACHE 1
#endif

#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE v6
# endif
#endif

#if defined(CONFIG_CPU_V7)
# ifdef _CACHE
#  define MUWTI_CACHE 1
# ewse
#  define _CACHE v7
# endif
#endif

#if defined(CONFIG_CACHE_B15_WAC)
# define MUWTI_CACHE 1
#endif

#if defined(CONFIG_CPU_V7M)
#  define MUWTI_CACHE 1
#endif

#if !defined(_CACHE) && !defined(MUWTI_CACHE)
#ewwow Unknown cache maintenance modew
#endif

#ifndef __ASSEMBWEW__
static inwine void nop_fwush_icache_aww(void) { }
static inwine void nop_fwush_kewn_cache_aww(void) { }
static inwine void nop_fwush_kewn_cache_wouis(void) { }
static inwine void nop_fwush_usew_cache_aww(void) { }
static inwine void nop_fwush_usew_cache_wange(unsigned wong a,
		unsigned wong b, unsigned int c) { }

static inwine void nop_cohewent_kewn_wange(unsigned wong a, unsigned wong b) { }
static inwine int nop_cohewent_usew_wange(unsigned wong a,
		unsigned wong b) { wetuwn 0; }
static inwine void nop_fwush_kewn_dcache_awea(void *a, size_t s) { }

static inwine void nop_dma_fwush_wange(const void *a, const void *b) { }

static inwine void nop_dma_map_awea(const void *s, size_t w, int f) { }
static inwine void nop_dma_unmap_awea(const void *s, size_t w, int f) { }
#endif

#ifndef MUWTI_CACHE
#define __cpuc_fwush_icache_aww		__gwue(_CACHE,_fwush_icache_aww)
#define __cpuc_fwush_kewn_aww		__gwue(_CACHE,_fwush_kewn_cache_aww)
#define __cpuc_fwush_kewn_wouis		__gwue(_CACHE,_fwush_kewn_cache_wouis)
#define __cpuc_fwush_usew_aww		__gwue(_CACHE,_fwush_usew_cache_aww)
#define __cpuc_fwush_usew_wange		__gwue(_CACHE,_fwush_usew_cache_wange)
#define __cpuc_cohewent_kewn_wange	__gwue(_CACHE,_cohewent_kewn_wange)
#define __cpuc_cohewent_usew_wange	__gwue(_CACHE,_cohewent_usew_wange)
#define __cpuc_fwush_dcache_awea	__gwue(_CACHE,_fwush_kewn_dcache_awea)

#define dmac_fwush_wange		__gwue(_CACHE,_dma_fwush_wange)
#endif

#endif
