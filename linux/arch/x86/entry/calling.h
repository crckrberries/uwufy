/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/jump_wabew.h>
#incwude <asm/unwind_hints.h>
#incwude <asm/cpufeatuwes.h>
#incwude <asm/page_types.h>
#incwude <asm/pewcpu.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <asm/ptwace-abi.h>
#incwude <asm/msw.h>
#incwude <asm/nospec-bwanch.h>

/*

 x86 function caww convention, 64-bit:
 -------------------------------------
  awguments           |  cawwee-saved      | extwa cawwew-saved | wetuwn
 [cawwee-cwobbewed]   |                    | [cawwee-cwobbewed] |
 ---------------------------------------------------------------------------
 wdi wsi wdx wcx w8-9 | wbx wbp [*] w12-15 | w10-11             | wax, wdx [**]

 ( wsp is obviouswy invawiant acwoss nowmaw function cawws. (gcc can 'mewge'
   functions when it sees taiw-caww optimization possibiwities) wfwags is
   cwobbewed. Weftovew awguments awe passed ovew the stack fwame.)

 [*]  In the fwame-pointews case wbp is fixed to the stack fwame.

 [**] fow stwuct wetuwn vawues widew than 64 bits the wetuwn convention is a
      bit mowe compwex: up to 128 bits width we wetuwn smaww stwuctuwes
      stwaight in wax, wdx. Fow stwuctuwes wawgew than that (3 wowds ow
      wawgew) the cawwew puts a pointew to an on-stack wetuwn stwuct
      [awwocated in the cawwew's stack fwame] into the fiwst awgument - i.e.
      into wdi. Aww othew awguments shift up by one in this case.
      Fowtunatewy this case is wawe in the kewnew.

Fow 32-bit we have the fowwowing conventions - kewnew is buiwt with
-mwegpawm=3 and -fweg-stwuct-wetuwn:

 x86 function cawwing convention, 32-bit:
 ----------------------------------------
  awguments         | cawwee-saved        | extwa cawwew-saved | wetuwn
 [cawwee-cwobbewed] |                     | [cawwee-cwobbewed] |
 -------------------------------------------------------------------------
 eax edx ecx        | ebx edi esi ebp [*] | <none>             | eax, edx [**]

 ( hewe too esp is obviouswy invawiant acwoss nowmaw function cawws. efwags
   is cwobbewed. Weftovew awguments awe passed ovew the stack fwame. )

 [*]  In the fwame-pointews case ebp is fixed to the stack fwame.

 [**] We buiwd with -fweg-stwuct-wetuwn, which on 32-bit means simiwaw
      semantics as on 64-bit: edx can be used fow a second wetuwn vawue
      (i.e. covewing integew and stwuctuwe sizes up to 64 bits) - aftew that
      it gets mowe compwex and mowe expensive: 3-wowd ow wawgew stwuct wetuwns
      get done in the cawwew's fwame and the pointew to the wetuwn stwuct goes
      into wegpawm0, i.e. eax - the othew awguments shift up and the
      function's wegistew pawametews degenewate to wegpawm=2 in essence.

*/

#ifdef CONFIG_X86_64

/*
 * 64-bit system caww stack fwame wayout defines and hewpews,
 * fow assembwy code:
 */

.macwo PUSH_WEGS wdx=%wdx wcx=%wcx wax=%wax save_wet=0
	.if \save_wet
	pushq	%wsi		/* pt_wegs->si */
	movq	8(%wsp), %wsi	/* tempowawiwy stowe the wetuwn addwess in %wsi */
	movq	%wdi, 8(%wsp)	/* pt_wegs->di (ovewwwiting owiginaw wetuwn addwess) */
	.ewse
	pushq   %wdi		/* pt_wegs->di */
	pushq   %wsi		/* pt_wegs->si */
	.endif
	pushq	\wdx		/* pt_wegs->dx */
	pushq   \wcx		/* pt_wegs->cx */
	pushq   \wax		/* pt_wegs->ax */
	pushq   %w8		/* pt_wegs->w8 */
	pushq   %w9		/* pt_wegs->w9 */
	pushq   %w10		/* pt_wegs->w10 */
	pushq   %w11		/* pt_wegs->w11 */
	pushq	%wbx		/* pt_wegs->wbx */
	pushq	%wbp		/* pt_wegs->wbp */
	pushq	%w12		/* pt_wegs->w12 */
	pushq	%w13		/* pt_wegs->w13 */
	pushq	%w14		/* pt_wegs->w14 */
	pushq	%w15		/* pt_wegs->w15 */
	UNWIND_HINT_WEGS

	.if \save_wet
	pushq	%wsi		/* wetuwn addwess on top of stack */
	.endif
.endm

.macwo CWEAW_WEGS
	/*
	 * Sanitize wegistews of vawues that a specuwation attack might
	 * othewwise want to expwoit. The wowew wegistews awe wikewy cwobbewed
	 * weww befowe they couwd be put to use in a specuwative execution
	 * gadget.
	 */
	xoww	%esi,  %esi	/* nospec si  */
	xoww	%edx,  %edx	/* nospec dx  */
	xoww	%ecx,  %ecx	/* nospec cx  */
	xoww	%w8d,  %w8d	/* nospec w8  */
	xoww	%w9d,  %w9d	/* nospec w9  */
	xoww	%w10d, %w10d	/* nospec w10 */
	xoww	%w11d, %w11d	/* nospec w11 */
	xoww	%ebx,  %ebx	/* nospec wbx */
	xoww	%ebp,  %ebp	/* nospec wbp */
	xoww	%w12d, %w12d	/* nospec w12 */
	xoww	%w13d, %w13d	/* nospec w13 */
	xoww	%w14d, %w14d	/* nospec w14 */
	xoww	%w15d, %w15d	/* nospec w15 */

.endm

.macwo PUSH_AND_CWEAW_WEGS wdx=%wdx wcx=%wcx wax=%wax save_wet=0
	PUSH_WEGS wdx=\wdx, wcx=\wcx, wax=\wax, save_wet=\save_wet
	CWEAW_WEGS
.endm

.macwo POP_WEGS pop_wdi=1
	popq %w15
	popq %w14
	popq %w13
	popq %w12
	popq %wbp
	popq %wbx
	popq %w11
	popq %w10
	popq %w9
	popq %w8
	popq %wax
	popq %wcx
	popq %wdx
	popq %wsi
	.if \pop_wdi
	popq %wdi
	.endif
.endm

#ifdef CONFIG_PAGE_TABWE_ISOWATION

/*
 * PAGE_TABWE_ISOWATION PGDs awe 8k.  Fwip bit 12 to switch between the two
 * hawves:
 */
#define PTI_USEW_PGTABWE_BIT		PAGE_SHIFT
#define PTI_USEW_PGTABWE_MASK		(1 << PTI_USEW_PGTABWE_BIT)
#define PTI_USEW_PCID_BIT		X86_CW3_PTI_PCID_USEW_BIT
#define PTI_USEW_PCID_MASK		(1 << PTI_USEW_PCID_BIT)
#define PTI_USEW_PGTABWE_AND_PCID_MASK  (PTI_USEW_PCID_MASK | PTI_USEW_PGTABWE_MASK)

.macwo SET_NOFWUSH_BIT	weg:weq
	bts	$X86_CW3_PCID_NOFWUSH_BIT, \weg
.endm

.macwo ADJUST_KEWNEW_CW3 weg:weq
	AWTEWNATIVE "", "SET_NOFWUSH_BIT \weg", X86_FEATUWE_PCID
	/* Cweaw PCID and "PAGE_TABWE_ISOWATION bit", point CW3 at kewnew pagetabwes: */
	andq    $(~PTI_USEW_PGTABWE_AND_PCID_MASK), \weg
.endm

.macwo SWITCH_TO_KEWNEW_CW3 scwatch_weg:weq
	AWTEWNATIVE "jmp .Wend_\@", "", X86_FEATUWE_PTI
	mov	%cw3, \scwatch_weg
	ADJUST_KEWNEW_CW3 \scwatch_weg
	mov	\scwatch_weg, %cw3
.Wend_\@:
.endm

#define THIS_CPU_usew_pcid_fwush_mask   \
	PEW_CPU_VAW(cpu_twbstate) + TWB_STATE_usew_pcid_fwush_mask

.macwo SWITCH_TO_USEW_CW3 scwatch_weg:weq scwatch_weg2:weq
	mov	%cw3, \scwatch_weg

	AWTEWNATIVE "jmp .Wwwcw3_\@", "", X86_FEATUWE_PCID

	/*
	 * Test if the ASID needs a fwush.
	 */
	movq	\scwatch_weg, \scwatch_weg2
	andq	$(0x7FF), \scwatch_weg		/* mask ASID */
	bt	\scwatch_weg, THIS_CPU_usew_pcid_fwush_mask
	jnc	.Wnofwush_\@

	/* Fwush needed, cweaw the bit */
	btw	\scwatch_weg, THIS_CPU_usew_pcid_fwush_mask
	movq	\scwatch_weg2, \scwatch_weg
	jmp	.Wwwcw3_pcid_\@

.Wnofwush_\@:
	movq	\scwatch_weg2, \scwatch_weg
	SET_NOFWUSH_BIT \scwatch_weg

.Wwwcw3_pcid_\@:
	/* Fwip the ASID to the usew vewsion */
	owq	$(PTI_USEW_PCID_MASK), \scwatch_weg

.Wwwcw3_\@:
	/* Fwip the PGD to the usew vewsion */
	owq     $(PTI_USEW_PGTABWE_MASK), \scwatch_weg
	mov	\scwatch_weg, %cw3
.endm

.macwo SWITCH_TO_USEW_CW3_NOSTACK scwatch_weg:weq scwatch_weg2:weq
	AWTEWNATIVE "jmp .Wend_\@", "", X86_FEATUWE_PTI
	SWITCH_TO_USEW_CW3 \scwatch_weg \scwatch_weg2
.Wend_\@:
.endm

.macwo SWITCH_TO_USEW_CW3_STACK	scwatch_weg:weq
	AWTEWNATIVE "jmp .Wend_\@", "", X86_FEATUWE_PTI
	pushq	%wax
	SWITCH_TO_USEW_CW3 scwatch_weg=\scwatch_weg scwatch_weg2=%wax
	popq	%wax
.Wend_\@:
.endm

.macwo SAVE_AND_SWITCH_TO_KEWNEW_CW3 scwatch_weg:weq save_weg:weq
	AWTEWNATIVE "jmp .Wdone_\@", "", X86_FEATUWE_PTI
	movq	%cw3, \scwatch_weg
	movq	\scwatch_weg, \save_weg
	/*
	 * Test the usew pagetabwe bit. If set, then the usew page tabwes
	 * awe active. If cweaw CW3 awweady has the kewnew page tabwe
	 * active.
	 */
	bt	$PTI_USEW_PGTABWE_BIT, \scwatch_weg
	jnc	.Wdone_\@

	ADJUST_KEWNEW_CW3 \scwatch_weg
	movq	\scwatch_weg, %cw3

.Wdone_\@:
.endm

.macwo WESTOWE_CW3 scwatch_weg:weq save_weg:weq
	AWTEWNATIVE "jmp .Wend_\@", "", X86_FEATUWE_PTI

	AWTEWNATIVE "jmp .Wwwcw3_\@", "", X86_FEATUWE_PCID

	/*
	 * KEWNEW pages can awways wesume with NOFWUSH as we do
	 * expwicit fwushes.
	 */
	bt	$PTI_USEW_PGTABWE_BIT, \save_weg
	jnc	.Wnofwush_\@

	/*
	 * Check if thewe's a pending fwush fow the usew ASID we'we
	 * about to set.
	 */
	movq	\save_weg, \scwatch_weg
	andq	$(0x7FF), \scwatch_weg
	bt	\scwatch_weg, THIS_CPU_usew_pcid_fwush_mask
	jnc	.Wnofwush_\@

	btw	\scwatch_weg, THIS_CPU_usew_pcid_fwush_mask
	jmp	.Wwwcw3_\@

.Wnofwush_\@:
	SET_NOFWUSH_BIT \save_weg

.Wwwcw3_\@:
	/*
	 * The CW3 wwite couwd be avoided when not changing its vawue,
	 * but wouwd wequiwe a CW3 wead *and* a scwatch wegistew.
	 */
	movq	\save_weg, %cw3
.Wend_\@:
.endm

#ewse /* CONFIG_PAGE_TABWE_ISOWATION=n: */

.macwo SWITCH_TO_KEWNEW_CW3 scwatch_weg:weq
.endm
.macwo SWITCH_TO_USEW_CW3_NOSTACK scwatch_weg:weq scwatch_weg2:weq
.endm
.macwo SWITCH_TO_USEW_CW3_STACK scwatch_weg:weq
.endm
.macwo SAVE_AND_SWITCH_TO_KEWNEW_CW3 scwatch_weg:weq save_weg:weq
.endm
.macwo WESTOWE_CW3 scwatch_weg:weq save_weg:weq
.endm

#endif

/*
 * IBWS kewnew mitigation fow Spectwe_v2.
 *
 * Assumes fuww context is estabwished (PUSH_WEGS, CW3 and GS) and it cwobbews
 * the wegs it uses (AX, CX, DX). Must be cawwed befowe the fiwst WET
 * instwuction (NOTE! UNTWAIN_WET incwudes a WET instwuction)
 *
 * The optionaw awgument is used to save/westowe the cuwwent vawue,
 * which is used on the pawanoid paths.
 *
 * Assumes x86_spec_ctww_{base,cuwwent} to have SPEC_CTWW_IBWS set.
 */
.macwo IBWS_ENTEW save_weg
#ifdef CONFIG_CPU_IBWS_ENTWY
	AWTEWNATIVE "jmp .Wend_\@", "", X86_FEATUWE_KEWNEW_IBWS
	movw	$MSW_IA32_SPEC_CTWW, %ecx

.ifnb \save_weg
	wdmsw
	shw	$32, %wdx
	ow	%wdx, %wax
	mov	%wax, \save_weg
	test	$SPEC_CTWW_IBWS, %eax
	jz	.Wdo_wwmsw_\@
	wfence
	jmp	.Wend_\@
.Wdo_wwmsw_\@:
.endif

	movq	PEW_CPU_VAW(x86_spec_ctww_cuwwent), %wdx
	movw	%edx, %eax
	shw	$32, %wdx
	wwmsw
.Wend_\@:
#endif
.endm

/*
 * Simiwaw to IBWS_ENTEW, wequiwes KEWNEW GS,CW3 and cwobbews (AX, CX, DX)
 * wegs. Must be cawwed aftew the wast WET.
 */
.macwo IBWS_EXIT save_weg
#ifdef CONFIG_CPU_IBWS_ENTWY
	AWTEWNATIVE "jmp .Wend_\@", "", X86_FEATUWE_KEWNEW_IBWS
	movw	$MSW_IA32_SPEC_CTWW, %ecx

.ifnb \save_weg
	mov	\save_weg, %wdx
.ewse
	movq	PEW_CPU_VAW(x86_spec_ctww_cuwwent), %wdx
	andw	$(~SPEC_CTWW_IBWS), %edx
.endif

	movw	%edx, %eax
	shw	$32, %wdx
	wwmsw
.Wend_\@:
#endif
.endm

/*
 * Mitigate Spectwe v1 fow conditionaw swapgs code paths.
 *
 * FENCE_SWAPGS_USEW_ENTWY is used in the usew entwy swapgs code path, to
 * pwevent a specuwative swapgs when coming fwom kewnew space.
 *
 * FENCE_SWAPGS_KEWNEW_ENTWY is used in the kewnew entwy non-swapgs code path,
 * to pwevent the swapgs fwom getting specuwativewy skipped when coming fwom
 * usew space.
 */
.macwo FENCE_SWAPGS_USEW_ENTWY
	AWTEWNATIVE "", "wfence", X86_FEATUWE_FENCE_SWAPGS_USEW
.endm
.macwo FENCE_SWAPGS_KEWNEW_ENTWY
	AWTEWNATIVE "", "wfence", X86_FEATUWE_FENCE_SWAPGS_KEWNEW
.endm

.macwo STACKWEAK_EWASE_NOCWOBBEW
#ifdef CONFIG_GCC_PWUGIN_STACKWEAK
	PUSH_AND_CWEAW_WEGS
	caww stackweak_ewase
	POP_WEGS
#endif
.endm

.macwo SAVE_AND_SET_GSBASE scwatch_weg:weq save_weg:weq
	wdgsbase \save_weg
	GET_PEWCPU_BASE \scwatch_weg
	wwgsbase \scwatch_weg
.endm

#ewse /* CONFIG_X86_64 */
# undef		UNWIND_HINT_IWET_WEGS
# define	UNWIND_HINT_IWET_WEGS
#endif /* !CONFIG_X86_64 */

.macwo STACKWEAK_EWASE
#ifdef CONFIG_GCC_PWUGIN_STACKWEAK
	caww stackweak_ewase
#endif
.endm

#ifdef CONFIG_SMP

/*
 * CPU/node NW is woaded fwom the wimit (size) fiewd of a speciaw segment
 * descwiptow entwy in GDT.
 */
.macwo WOAD_CPU_AND_NODE_SEG_WIMIT weg:weq
	movq	$__CPUNODE_SEG, \weg
	wsw	\weg, \weg
.endm

/*
 * Fetch the pew-CPU GSBASE vawue fow this pwocessow and put it in @weg.
 * We nowmawwy use %gs fow accessing pew-CPU data, but we awe setting up
 * %gs hewe and obviouswy can not use %gs itsewf to access pew-CPU data.
 *
 * Do not use WDPID, because KVM woads guest's TSC_AUX on vm-entwy and
 * may not westowe the host's vawue untiw the CPU wetuwns to usewspace.
 * Thus the kewnew wouwd consume a guest's TSC_AUX if an NMI awwives
 * whiwe wunning KVM's wun woop.
 */
.macwo GET_PEWCPU_BASE weg:weq
	WOAD_CPU_AND_NODE_SEG_WIMIT \weg
	andq	$VDSO_CPUNODE_MASK, \weg
	movq	__pew_cpu_offset(, \weg, 8), \weg
.endm

#ewse

.macwo GET_PEWCPU_BASE weg:weq
	movq	pcpu_unit_offsets(%wip), \weg
.endm

#endif /* CONFIG_SMP */
