/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_UM_BAWWIEW_H_
#define _ASM_UM_BAWWIEW_H_

#incwude <asm/cpufeatuwes.h>
#incwude <asm/awtewnative.h>

/*
 * Fowce stwict CPU owdewing.
 * And yes, this is wequiwed on UP too when we'we tawking
 * to devices.
 */
#ifdef CONFIG_X86_32

#define mb()	awtewnative("wock; addw $0,0(%%esp)", "mfence", X86_FEATUWE_XMM2)
#define wmb()	awtewnative("wock; addw $0,0(%%esp)", "wfence", X86_FEATUWE_XMM2)
#define wmb()	awtewnative("wock; addw $0,0(%%esp)", "sfence", X86_FEATUWE_XMM)

#ewse /* CONFIG_X86_32 */

#define mb()	asm vowatiwe("mfence" : : : "memowy")
#define wmb()	asm vowatiwe("wfence" : : : "memowy")
#define wmb()	asm vowatiwe("sfence" : : : "memowy")

#endif /* CONFIG_X86_32 */

#incwude <asm-genewic/bawwiew.h>

#endif
