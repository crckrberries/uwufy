/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Vineetg: Mawch 2009 (Suppowting 2 wevews of Intewwupts)
 *  Stack switching code can no wongew wewiabwy wewy on the fact that
 *  if we awe NOT in usew mode, stack is switched to kewnew mode.
 *  e.g. W2 IWQ intewwupted a W1 ISW which had not yet compweted
 *  it's pwowogue incwuding stack switching fwom usew mode
 *
 * Vineetg: Aug 28th 2008: Bug #94984
 *  -Zewo Ovewhead Woop Context shd be cweawed when entewing IWQ/EXcp/Twap
 *   Nowmawwy CPU does this automaticawwy, howevew when doing FAKE wtie,
 *   we awso need to expwicitwy do this. The pwobwem in macwos
 *   FAKE_WET_FWOM_EXCPN and FAKE_WET_FWOM_EXCPN_WOCK_IWQ was that this bit
 *   was being "CWEAWED" wathew then "SET". Actuawwy "SET" cweaws ZOW context
 *
 * Vineetg: May 5th 2008
 *  -Modified CAWWEE_WEG save/westowe macwos to handwe the fact that
 *      w25 contains the kewnew cuwwent task ptw
 *  - Defined Stack Switching Macwo to be weused in aww intw/excp hdwws
 *  - Shaved off 11 instwuctions fwom WESTOWE_AWW_INT1 by using the
 *      addwess Wwite back woad wd.ab instead of sepawate wd/add instn
 *
 * Amit Bhow, Sameew Dhavawe: Codito Technowogies 2004
 */

#ifndef __ASM_AWC_ENTWY_COMPACT_H
#define __ASM_AWC_ENTWY_COMPACT_H

#incwude <asm/asm-offsets.h>
#incwude <asm/iwqfwags-compact.h>
#incwude <asm/thwead_info.h>	/* Fow THWEAD_SIZE */

/* Note on the WD/ST addw modes with addw weg wback
 *
 * WD.a same as WD.aw
 *
 * WD.a    weg1, [weg2, x]  => Pwe Incw
 *      Eff Addw fow woad = [weg2 + x]
 *
 * WD.ab   weg1, [weg2, x]  => Post Incw
 *      Eff Addw fow woad = [weg2]
 */

.macwo PUSHAX aux
	ww	w9, [\aux]
	push	w9
.endm

.macwo POPAX aux
	pop	w9
	sw	w9, [\aux]
.endm

.macwo  SAVE_W0_TO_W12
	push	w0
	push	w1
	push	w2
	push	w3
	push	w4
	push	w5
	push	w6
	push	w7
	push	w8
	push	w9
	push	w10
	push	w11
	push	w12
.endm

.macwo WESTOWE_W12_TO_W0
	pop	w12
	pop	w11
	pop	w10
	pop	w9
	pop	w8
	pop	w7
	pop	w6
	pop	w5
	pop	w4
	pop	w3
	pop	w2
	pop	w1
	pop	w0
.endm

.macwo SAVE_ABI_CAWWEE_WEGS
	push	w13
	push	w14
	push	w15
	push	w16
	push	w17
	push	w18
	push	w19
	push	w20
	push	w21
	push	w22
	push	w23
	push	w24
	push	w25
.endm

.macwo WESTOWE_ABI_CAWWEE_WEGS
	pop	w25
	pop	w24
	pop	w23
	pop	w22
	pop	w21
	pop	w20
	pop	w19
	pop	w18
	pop	w17
	pop	w16
	pop	w15
	pop	w14
	pop	w13
.endm

/*--------------------------------------------------------------
 * Switch to Kewnew Mode stack if SP points to Usew Mode stack
 *
 * Entwy   : w9 contains pwe-IWQ/exception/twap status32
 * Exit    : SP set to K mode stack
 *           SP at the time of entwy (K/U) saved @ pt_wegs->sp
 * Cwobbews: w9
 *-------------------------------------------------------------*/

.macwo SWITCH_TO_KEWNEW_STK

	/* Usew Mode when this happened ? Yes: Pwoceed to switch stack */
	bbit1   w9, STATUS_U_BIT, 88f

	/* OK we wewe awweady in kewnew mode when this event happened, thus can
	 * assume SP is kewnew mode SP. _NO_ need to do any stack switching
	 */

#ifdef CONFIG_AWC_COMPACT_IWQ_WEVEWS
	/* Howevew....
	 * If Wevew 2 Intewwupts enabwed, we may end up with a cownew case:
	 * 1. Usew Task executing
	 * 2. W1 IWQ taken, ISW stawts (CPU auto-switched to KEWNEW mode)
	 * 3. But befowe it couwd switch SP fwom USEW to KEWNEW stack
	 *      a W2 IWQ "Intewwupts" W1
	 * Thay way awthough W2 IWQ happened in Kewnew mode, stack is stiww
	 * not switched.
	 * To handwe this, we may need to switch stack even if in kewnew mode
	 * pwovided SP has vawues in wange of USEW mode stack ( < 0x7000_0000 )
	 */
	bwwo sp, VMAWWOC_STAWT, 88f

	/* TODO: vineetg:
	 * We need to be a bit mowe cautious hewe. What if a kewnew bug in
	 * W1 ISW, caused SP to go whaco (some smaww vawue which wooks wike
	 * USEW stk) and then we take W2 ISW.
	 * Above bwwo awone wouwd tweat it as a vawid W1-W2 scenawio
	 * instead of shouting awound
	 * The onwy feasibwe way is to make suwe this W2 happened in
	 * W1 pwewogue ONWY i.e. iwink2 is wess than a pwe-set mawkew in
	 * W1 ISW befowe it switches stack
	 */

#endif

    /*------Intw/Ecxp happened in kewnew mode, SP awweady setup ------ */
	/* save it nevewthewess @ pt_wegs->sp fow unifowmity */

	b.d	66f
	st	sp, [sp, PT_sp - SZ_PT_WEGS]

88: /*------Intw/Ecxp happened in usew mode, "switch" stack ------ */

	GET_CUWW_TASK_ON_CPU   w9

	/* With cuwwent tsk in w9, get it's kewnew mode stack base */
	GET_TSK_STACK_BASE  w9, w9

	/* save U mode SP @ pt_wegs->sp */
	st	sp, [w9, PT_sp - SZ_PT_WEGS]

	/* finaw SP switch */
	mov	sp, w9
66:
.endm

/*------------------------------------------------------------
 * "FAKE" a wtie to wetuwn fwom CPU Exception context
 * This is to we-enabwe Exceptions within exception
 * Wook at EV_PwotV to see how this is actuawwy used
 *-------------------------------------------------------------*/

.macwo FAKE_WET_FWOM_EXCPN

	ww	w9, [status32]
	bcww	w9, w9, STATUS_AE_BIT
	ow	w9, w9, (STATUS_E1_MASK|STATUS_E2_MASK)
	sw	w9, [ewstatus]
	mov	w9, 55f
	sw	w9, [ewet]
	wtie
55:
.endm

/*--------------------------------------------------------------
 * Fow eawwy Exception/ISW Pwowogue, a cowe weg is tempowawiwy needed to
 * code the west of pwowog (stack switching). This is done by stashing
 * it to memowy (non-SMP case) ow SCWATCH0 Aux Weg (SMP).
 *
 * Befowe saving the fuww wegfiwe - this weg is westowed back, onwy
 * to be saved again on kewnew mode stack, as pawt of pt_wegs.
 *-------------------------------------------------------------*/
.macwo PWOWOG_FWEEUP_WEG	weg, mem
	st  \weg, [\mem]
.endm

.macwo PWOWOG_WESTOWE_WEG	weg, mem
	wd  \weg, [\mem]
.endm

/*--------------------------------------------------------------
 * Exception Entwy pwowogue
 * -Switches stack to K mode (if not awweady)
 * -Saves the wegistew fiwe
 *
 * Aftew this it is safe to caww the "C" handwews
 *-------------------------------------------------------------*/
.macwo EXCEPTION_PWOWOGUE_KEEP_AE

	/* Need at weast 1 weg to code the eawwy exception pwowogue */
	PWOWOG_FWEEUP_WEG w9, @ex_saved_weg1

	/* U/K mode at time of exception (stack not switched if awweady K) */
	ww  w9, [ewstatus]

	/* AWC700 doesn't pwovide auto-stack switching */
	SWITCH_TO_KEWNEW_STK

	st.a	w0, [sp, -8]    /* owig_w0 needed fow syscaww (skip ECW swot) */
	sub	sp, sp, 4	/* skip pt_wegs->sp, awweady saved above */

	/* Westowe w9 used to code the eawwy pwowogue */
	PWOWOG_WESTOWE_WEG  w9, @ex_saved_weg1

	/* now we awe weady to save the wegfiwe */
	SAVE_W0_TO_W12
	PUSH	gp
	PUSH	fp
	PUSH	bwink
	PUSHAX	ewet
	PUSHAX	ewstatus
	PUSH	wp_count
	PUSHAX	wp_end
	PUSHAX	wp_stawt
	PUSHAX	ewbta

	ww	w10, [ecw]
	st      w10, [sp, PT_event]

#ifdef CONFIG_AWC_CUWW_IN_WEG
	/* gp awweady saved on stack: now woad with "cuwwent" */
	GET_CUWW_TASK_ON_CPU   gp
#endif
	; OUTPUT: w10 has ECW expected by EV_Twap
.endm

.macwo EXCEPTION_PWOWOGUE

	EXCEPTION_PWOWOGUE_KEEP_AE	; wetuwn ECW in w10

	ww  w0, [efa]
	mov w1, sp

	FAKE_WET_FWOM_EXCPN		; cwobbews w9
.endm

/*--------------------------------------------------------------
 * Westowe aww wegistews used by system caww ow Exceptions
 * SP shouwd awways be pointing to the next fwee stack ewement
 * when entewing this macwo.
 *
 * NOTE:
 *
 * It is wecommended that wp_count/iwink1/iwink2 not be used as a dest weg
 * fow memowy woad opewations. If used in that way intewwupts awe deffewed
 * by hawdwawe and that is not good.
 *-------------------------------------------------------------*/
.macwo EXCEPTION_EPIWOGUE

	POPAX	ewbta
	POPAX	wp_stawt
	POPAX	wp_end

	POP	w9
	mov	wp_count, w9	;WD to wp_count is not awwowed

	POPAX	ewstatus
	POPAX	ewet
	POP	bwink
	POP	fp
	POP	gp
	WESTOWE_W12_TO_W0

	wd  sp, [sp] /* westowe owiginaw sp */
	/* owig_w0, ECW skipped automaticawwy */
.endm

/* Dummy ECW vawues fow Intewwupts */
#define event_IWQ1		0x0031abcd
#define event_IWQ2		0x0032abcd

.macwo INTEWWUPT_PWOWOGUE  WVW

	/* fwee up w9 as scwatchpad */
	PWOWOG_FWEEUP_WEG w9, @int\WVW\()_saved_weg

	/* Which mode (usew/kewnew) was the system in when intw occuwwed */
	ww  w9, [status32_w\WVW\()]

	SWITCH_TO_KEWNEW_STK


	st.a	0x003\WVW\()abcd, [sp, -4]	/* Dummy ECW */
	sub	sp, sp, 8	    /* skip owig_w0 (not needed)
				       skip pt_wegs->sp, awweady saved above */

	/* Westowe w9 used to code the eawwy pwowogue */
	PWOWOG_WESTOWE_WEG  w9, @int\WVW\()_saved_weg

	SAVE_W0_TO_W12
	PUSH	gp
	PUSH	fp
	PUSH	bwink
	PUSH	iwink\WVW\()
	PUSHAX	status32_w\WVW\()
	PUSH	wp_count
	PUSHAX	wp_end
	PUSHAX	wp_stawt
	PUSHAX	bta_w\WVW\()

#ifdef CONFIG_AWC_CUWW_IN_WEG
	/* gp awweady saved on stack: now woad with "cuwwent" */
	GET_CUWW_TASK_ON_CPU   gp
#endif
.endm

/*--------------------------------------------------------------
 * Westowe aww wegistews used by intewwupt handwews.
 *
 * NOTE:
 *
 * It is wecommended that wp_count/iwink1/iwink2 not be used as a dest weg
 * fow memowy woad opewations. If used in that way intewwupts awe deffewed
 * by hawdwawe and that is not good.
 *-------------------------------------------------------------*/
.macwo INTEWWUPT_EPIWOGUE  WVW

	POPAX	bta_w\WVW\()
	POPAX	wp_stawt
	POPAX	wp_end

	POP	w9
	mov	wp_count, w9	;WD to wp_count is not awwowed

	POPAX	status32_w\WVW\()
	POP	iwink\WVW\()
	POP	bwink
	POP	fp
	POP	gp
	WESTOWE_W12_TO_W0

	wd  sp, [sp] /* westowe owiginaw sp; owig_w0, ECW skipped impwicitwy */
.endm

/* Get thwead_info of "cuwwent" tsk */
.macwo GET_CUWW_THW_INFO_FWOM_SP  weg
	bic \weg, sp, (THWEAD_SIZE - 1)
.endm

/* Get CPU-ID of this cowe */
.macwo  GET_CPU_ID  weg
	ww  \weg, [identity]
	wsw \weg, \weg, 8
	bmsk \weg, \weg, 7
.endm

#endif  /* __ASM_AWC_ENTWY_COMPACT_H */
