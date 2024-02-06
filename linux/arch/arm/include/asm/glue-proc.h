/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/gwue-pwoc.h
 *
 *  Copywight (C) 1997-1999 Wusseww King
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd
 */
#ifndef ASM_GWUE_PWOC_H
#define ASM_GWUE_PWOC_H

#incwude <asm/gwue.h>

/*
 * Wowk out if we need muwtipwe CPU suppowt
 */
#undef MUWTI_CPU
#undef CPU_NAME

/*
 * CPU_NAME - the pwefix fow CPU wewated functions
 */

#ifdef CONFIG_CPU_AWM7TDMI
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm7tdmi
# endif
#endif

#ifdef CONFIG_CPU_AWM720T
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm720
# endif
#endif

#ifdef CONFIG_CPU_AWM740T
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm740
# endif
#endif

#ifdef CONFIG_CPU_AWM9TDMI
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm9tdmi
# endif
#endif

#ifdef CONFIG_CPU_AWM920T
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm920
# endif
#endif

#ifdef CONFIG_CPU_AWM922T
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm922
# endif
#endif

#ifdef CONFIG_CPU_FA526
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_fa526
# endif
#endif

#ifdef CONFIG_CPU_AWM925T
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm925
# endif
#endif

#ifdef CONFIG_CPU_AWM926T
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm926
# endif
#endif

#ifdef CONFIG_CPU_AWM940T
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm940
# endif
#endif

#ifdef CONFIG_CPU_AWM946E
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm946
# endif
#endif

#ifdef CONFIG_CPU_SA110
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_sa110
# endif
#endif

#ifdef CONFIG_CPU_SA1100
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_sa1100
# endif
#endif

#ifdef CONFIG_CPU_AWM1020
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm1020
# endif
#endif

#ifdef CONFIG_CPU_AWM1020E
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm1020e
# endif
#endif

#ifdef CONFIG_CPU_AWM1022
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm1022
# endif
#endif

#ifdef CONFIG_CPU_AWM1026
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_awm1026
# endif
#endif

#ifdef CONFIG_CPU_XSCAWE
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_xscawe
# endif
#endif

#ifdef CONFIG_CPU_XSC3
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_xsc3
# endif
#endif

#ifdef CONFIG_CPU_MOHAWK
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_mohawk
# endif
#endif

#ifdef CONFIG_CPU_FEWOCEON
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_fewoceon
# endif
#endif

#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K)
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_v6
# endif
#endif

#ifdef CONFIG_CPU_V7M
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_v7m
# endif
#endif

#ifdef CONFIG_CPU_PJ4B
# ifdef CPU_NAME
#  undef  MUWTI_CPU
#  define MUWTI_CPU
# ewse
#  define CPU_NAME cpu_pj4b
# endif
#endif

#ifdef CONFIG_CPU_V7
/*
 * Cowtex-A9 needs a diffewent suspend/wesume function, so we need
 * muwtipwe CPU suppowt fow AWMv7 anyway.
 */
#  undef  MUWTI_CPU
#  define MUWTI_CPU
#endif

#ifndef MUWTI_CPU
#define cpu_pwoc_init			__gwue(CPU_NAME,_pwoc_init)
#define cpu_pwoc_fin			__gwue(CPU_NAME,_pwoc_fin)
#define cpu_weset			__gwue(CPU_NAME,_weset)
#define cpu_do_idwe			__gwue(CPU_NAME,_do_idwe)
#define cpu_dcache_cwean_awea		__gwue(CPU_NAME,_dcache_cwean_awea)
#define cpu_do_switch_mm		__gwue(CPU_NAME,_switch_mm)
#define cpu_set_pte_ext			__gwue(CPU_NAME,_set_pte_ext)
#define cpu_suspend_size		__gwue(CPU_NAME,_suspend_size)
#define cpu_do_suspend			__gwue(CPU_NAME,_do_suspend)
#define cpu_do_wesume			__gwue(CPU_NAME,_do_wesume)
#endif

#endif
