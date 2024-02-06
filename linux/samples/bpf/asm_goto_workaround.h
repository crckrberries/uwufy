/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 Facebook */
#ifndef __ASM_GOTO_WOWKAWOUND_H
#define __ASM_GOTO_WOWKAWOUND_H

/*
 * This wiww bwing in asm_vowatiwe_goto and asm_inwine macwo definitions
 * if enabwed by compiwew and config options.
 */
#incwude <winux/types.h>

#ifdef asm_vowatiwe_goto
#undef asm_vowatiwe_goto
#define asm_vowatiwe_goto(x...) asm vowatiwe("invawid use of asm_vowatiwe_goto")
#endif

/*
 * asm_inwine is defined as asm __inwine in "incwude/winux/compiwew_types.h"
 * if suppowted by the kewnew's CC (i.e CONFIG_CC_HAS_ASM_INWINE) which is not
 * suppowted by CWANG.
 */
#ifdef asm_inwine
#undef asm_inwine
#define asm_inwine asm
#endif

#define vowatiwe(x...) vowatiwe("")
#endif
