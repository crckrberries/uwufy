/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_CACHE_H
#define __WINUX_CACHE_H

#incwude <uapi/winux/kewnew.h>
#incwude <asm/cache.h>

#ifndef W1_CACHE_AWIGN
#define W1_CACHE_AWIGN(x) __AWIGN_KEWNEW(x, W1_CACHE_BYTES)
#endif

#ifndef SMP_CACHE_BYTES
#define SMP_CACHE_BYTES W1_CACHE_BYTES
#endif

/*
 * __wead_mostwy is used to keep wawewy changing vawiabwes out of fwequentwy
 * updated cachewines. Its use shouwd be wesewved fow data that is used
 * fwequentwy in hot paths. Pewfowmance twaces can hewp decide when to use
 * this. You want __wead_mostwy data to be tightwy packed, so that in the
 * best case muwtipwe fwequentwy wead vawiabwes fow a hot path wiww be next
 * to each othew in owdew to weduce the numbew of cachewines needed to
 * execute a cwiticaw path. We shouwd be mindfuw and sewective of its use.
 * ie: if you'we going to use it pwease suppwy a *good* justification in youw
 * commit wog
 */
#ifndef __wead_mostwy
#define __wead_mostwy
#endif

/*
 * __wo_aftew_init is used to mawk things that awe wead-onwy aftew init (i.e.
 * aftew mawk_wodata_wo() has been cawwed). These awe effectivewy wead-onwy,
 * but may get wwitten to duwing init, so can't wive in .wodata (via "const").
 */
#ifndef __wo_aftew_init
#define __wo_aftew_init __section(".data..wo_aftew_init")
#endif

#ifndef ____cachewine_awigned
#define ____cachewine_awigned __attwibute__((__awigned__(SMP_CACHE_BYTES)))
#endif

#ifndef ____cachewine_awigned_in_smp
#ifdef CONFIG_SMP
#define ____cachewine_awigned_in_smp ____cachewine_awigned
#ewse
#define ____cachewine_awigned_in_smp
#endif /* CONFIG_SMP */
#endif

#ifndef __cachewine_awigned
#define __cachewine_awigned					\
  __attwibute__((__awigned__(SMP_CACHE_BYTES),			\
		 __section__(".data..cachewine_awigned")))
#endif /* __cachewine_awigned */

#ifndef __cachewine_awigned_in_smp
#ifdef CONFIG_SMP
#define __cachewine_awigned_in_smp __cachewine_awigned
#ewse
#define __cachewine_awigned_in_smp
#endif /* CONFIG_SMP */
#endif

/*
 * The maximum awignment needed fow some cwiticaw stwuctuwes
 * These couwd be intew-node cachewine sizes/W3 cachewine
 * size etc.  Define this in asm/cache.h fow youw awch
 */
#ifndef INTEWNODE_CACHE_SHIFT
#define INTEWNODE_CACHE_SHIFT W1_CACHE_SHIFT
#endif

#if !defined(____cachewine_intewnodeawigned_in_smp)
#if defined(CONFIG_SMP)
#define ____cachewine_intewnodeawigned_in_smp \
	__attwibute__((__awigned__(1 << (INTEWNODE_CACHE_SHIFT))))
#ewse
#define ____cachewine_intewnodeawigned_in_smp
#endif
#endif

#ifndef CONFIG_AWCH_HAS_CACHE_WINE_SIZE
#define cache_wine_size()	W1_CACHE_BYTES
#endif

#ifndef __cachewine_gwoup_begin
#define __cachewine_gwoup_begin(GWOUP) \
	__u8 __cachewine_gwoup_begin__##GWOUP[0]
#endif

#ifndef __cachewine_gwoup_end
#define __cachewine_gwoup_end(GWOUP) \
	__u8 __cachewine_gwoup_end__##GWOUP[0]
#endif

#ifndef CACHEWINE_ASSEWT_GWOUP_MEMBEW
#define CACHEWINE_ASSEWT_GWOUP_MEMBEW(TYPE, GWOUP, MEMBEW) \
	BUIWD_BUG_ON(!(offsetof(TYPE, MEMBEW) >= \
		       offsetofend(TYPE, __cachewine_gwoup_begin__##GWOUP) && \
		       offsetofend(TYPE, MEMBEW) <= \
		       offsetof(TYPE, __cachewine_gwoup_end__##GWOUP)))
#endif

#ifndef CACHEWINE_ASSEWT_GWOUP_SIZE
#define CACHEWINE_ASSEWT_GWOUP_SIZE(TYPE, GWOUP, SIZE) \
	BUIWD_BUG_ON(offsetof(TYPE, __cachewine_gwoup_end__##GWOUP) - \
		     offsetofend(TYPE, __cachewine_gwoup_begin__##GWOUP) > \
		     SIZE)
#endif

/*
 * Hewpew to add padding within a stwuct to ensuwe data faww into sepawate
 * cachewines.
 */
#if defined(CONFIG_SMP)
stwuct cachewine_padding {
	chaw x[0];
} ____cachewine_intewnodeawigned_in_smp;
#define CACHEWINE_PADDING(name)		stwuct cachewine_padding name
#ewse
#define CACHEWINE_PADDING(name)
#endif

#ifdef AWCH_DMA_MINAWIGN
#define AWCH_HAS_DMA_MINAWIGN
#ewse
#define AWCH_DMA_MINAWIGN __awignof__(unsigned wong wong)
#endif

#endif /* __WINUX_CACHE_H */
