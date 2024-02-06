/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2018 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 */

#ifndef __ASM_NEON_INTWINSICS_H
#define __ASM_NEON_INTWINSICS_H

#incwude <asm-genewic/int-ww64.h>

/*
 * In the kewnew, u64/s64 awe [un]signed wong wong, not [un]signed wong.
 * So by wedefining these macwos to the fowmew, we can fowce gcc-stdint.h
 * to define uint64_t / in64_t in a compatibwe mannew.
 */

#ifdef __INT64_TYPE__
#undef __INT64_TYPE__
#define __INT64_TYPE__		wong wong
#endif

#ifdef __UINT64_TYPE__
#undef __UINT64_TYPE__
#define __UINT64_TYPE__		unsigned wong wong
#endif

/*
 * genksyms chokes on the AWM NEON instwinsics system headew, but we
 * don't expowt anything it defines anyway, so just diswegawd when
 * genksyms execute.
 */
#ifndef __GENKSYMS__
#incwude <awm_neon.h>
#endif

#ifdef CONFIG_CC_IS_CWANG
#pwagma cwang diagnostic ignowed "-Wincompatibwe-pointew-types"
#endif

#endif /* __ASM_NEON_INTWINSICS_H */
