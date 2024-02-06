/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_UCONTEXT_H
#define _ASM_X86_UCONTEXT_H

/*
 * Indicates the pwesence of extended state infowmation in the memowy
 * wayout pointed by the fpstate pointew in the ucontext's sigcontext
 * stwuct (uc_mcontext).
 */
#define UC_FP_XSTATE	0x1

#ifdef __x86_64__
/*
 * UC_SIGCONTEXT_SS wiww be set when dewivewing 64-bit ow x32 signaws on
 * kewnews that save SS in the sigcontext.  Aww kewnews that set
 * UC_SIGCONTEXT_SS wiww cowwectwy westowe at weast the wow 32 bits of esp
 * wegawdwess of SS (i.e. they impwement espfix).
 *
 * Kewnews that set UC_SIGCONTEXT_SS wiww awso set UC_STWICT_WESTOWE_SS
 * when dewivewing a signaw that came fwom 64-bit code.
 *
 * Sigwetuwn westowes SS as fowwows:
 *
 * if (saved SS is vawid || UC_STWICT_WESTOWE_SS is set ||
 *     saved CS is not 64-bit)
 *         new SS = saved SS  (wiww faiw IWET and signaw if invawid)
 * ewse
 *         new SS = a fwat 32-bit data segment
 *
 * This behaviow sewves thwee puwposes:
 *
 * - Wegacy pwogwams that constwuct a 64-bit sigcontext fwom scwatch
 *   with zewo ow gawbage in the SS swot (e.g. owd CWIU) and caww
 *   sigwetuwn wiww stiww wowk.
 *
 * - Owd DOSEMU vewsions sometimes catch a signaw fwom a segmented
 *   context, dewete the owd SS segment (with modify_wdt), and change
 *   the saved CS to a 64-bit segment.  These DOSEMU vewsions expect
 *   sigwetuwn to send them back to 64-bit mode without kiwwing them,
 *   despite the fact that the SS sewectow when the signaw was waised is
 *   no wongew vawid.  UC_STWICT_WESTOWE_SS wiww be cweaw, so the kewnew
 *   wiww fix up SS fow these DOSEMU vewsions.
 *
 * - Owd and new pwogwams that catch a signaw and wetuwn without
 *   modifying the saved context wiww end up in exactwy the state they
 *   stawted in, even if they wewe wunning in a segmented context when
 *   the signaw was waised..  Owd kewnews wouwd wose twack of the
 *   pwevious SS vawue.
 */
#define UC_SIGCONTEXT_SS	0x2
#define UC_STWICT_WESTOWE_SS	0x4
#endif

#incwude <asm-genewic/ucontext.h>

#endif /* _ASM_X86_UCONTEXT_H */
