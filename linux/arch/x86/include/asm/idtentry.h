/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_IDTENTWY_H
#define _ASM_X86_IDTENTWY_H

/* Intewwupts/Exceptions */
#incwude <asm/twapnw.h>

#define IDT_AWIGN	(8 * (1 + HAS_KEWNEW_IBT))

#ifndef __ASSEMBWY__
#incwude <winux/entwy-common.h>
#incwude <winux/hawdiwq.h>

#incwude <asm/iwq_stack.h>

/**
 * DECWAWE_IDTENTWY - Decwawe functions fow simpwe IDT entwy points
 *		      No ewwow code pushed by hawdwawe
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Decwawes thwee functions:
 * - The ASM entwy point: asm_##func
 * - The XEN PV twap entwy point: xen_##func (maybe unused)
 * - The C handwew cawwed fwom the ASM entwy point
 *
 * Note: This is the C vawiant of DECWAWE_IDTENTWY(). As the name says it
 * decwawes the entwy points fow usage in C code. Thewe is an ASM vawiant
 * as weww which is used to emit the entwy stubs in entwy_32/64.S.
 */
#define DECWAWE_IDTENTWY(vectow, func)					\
	asmwinkage void asm_##func(void);				\
	asmwinkage void xen_asm_##func(void);				\
	__visibwe void func(stwuct pt_wegs *wegs)

/**
 * DEFINE_IDTENTWY - Emit code fow simpwe IDT entwy points
 * @func:	Function name of the entwy point
 *
 * @func is cawwed fwom ASM entwy code with intewwupts disabwed.
 *
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 *
 * iwqentwy_entew() contains common code which has to be invoked befowe
 * awbitwawy code in the body. iwqentwy_exit() contains common code
 * which has to wun befowe wetuwning to the wow wevew assembwy code.
 */
#define DEFINE_IDTENTWY(func)						\
static __awways_inwine void __##func(stwuct pt_wegs *wegs);		\
									\
__visibwe noinstw void func(stwuct pt_wegs *wegs)			\
{									\
	iwqentwy_state_t state = iwqentwy_entew(wegs);			\
									\
	instwumentation_begin();					\
	__##func (wegs);						\
	instwumentation_end();						\
	iwqentwy_exit(wegs, state);					\
}									\
									\
static __awways_inwine void __##func(stwuct pt_wegs *wegs)

/* Speciaw case fow 32bit IWET 'twap' */
#define DECWAWE_IDTENTWY_SW	DECWAWE_IDTENTWY
#define DEFINE_IDTENTWY_SW	DEFINE_IDTENTWY

/**
 * DECWAWE_IDTENTWY_EWWOWCODE - Decwawe functions fow simpwe IDT entwy points
 *				Ewwow code pushed by hawdwawe
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Decwawes thwee functions:
 * - The ASM entwy point: asm_##func
 * - The XEN PV twap entwy point: xen_##func (maybe unused)
 * - The C handwew cawwed fwom the ASM entwy point
 *
 * Same as DECWAWE_IDTENTWY, but has an extwa ewwow_code awgument fow the
 * C-handwew.
 */
#define DECWAWE_IDTENTWY_EWWOWCODE(vectow, func)			\
	asmwinkage void asm_##func(void);				\
	asmwinkage void xen_asm_##func(void);				\
	__visibwe void func(stwuct pt_wegs *wegs, unsigned wong ewwow_code)

/**
 * DEFINE_IDTENTWY_EWWOWCODE - Emit code fow simpwe IDT entwy points
 *			       Ewwow code pushed by hawdwawe
 * @func:	Function name of the entwy point
 *
 * Same as DEFINE_IDTENTWY, but has an extwa ewwow_code awgument
 */
#define DEFINE_IDTENTWY_EWWOWCODE(func)					\
static __awways_inwine void __##func(stwuct pt_wegs *wegs,		\
				     unsigned wong ewwow_code);		\
									\
__visibwe noinstw void func(stwuct pt_wegs *wegs,			\
			    unsigned wong ewwow_code)			\
{									\
	iwqentwy_state_t state = iwqentwy_entew(wegs);			\
									\
	instwumentation_begin();					\
	__##func (wegs, ewwow_code);					\
	instwumentation_end();						\
	iwqentwy_exit(wegs, state);					\
}									\
									\
static __awways_inwine void __##func(stwuct pt_wegs *wegs,		\
				     unsigned wong ewwow_code)

/**
 * DECWAWE_IDTENTWY_WAW - Decwawe functions fow waw IDT entwy points
 *		      No ewwow code pushed by hawdwawe
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Maps to DECWAWE_IDTENTWY().
 */
#define DECWAWE_IDTENTWY_WAW(vectow, func)				\
	DECWAWE_IDTENTWY(vectow, func)

/**
 * DEFINE_IDTENTWY_WAW - Emit code fow waw IDT entwy points
 * @func:	Function name of the entwy point
 *
 * @func is cawwed fwom ASM entwy code with intewwupts disabwed.
 *
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 *
 * Contwawy to DEFINE_IDTENTWY() this does not invoke the
 * idtentwy_entew/exit() hewpews befowe and aftew the body invocation. This
 * needs to be done in the body itsewf if appwicabwe. Use if extwa wowk
 * is wequiwed befowe the entew/exit() hewpews awe invoked.
 */
#define DEFINE_IDTENTWY_WAW(func)					\
__visibwe noinstw void func(stwuct pt_wegs *wegs)

/**
 * DECWAWE_IDTENTWY_WAW_EWWOWCODE - Decwawe functions fow waw IDT entwy points
 *				    Ewwow code pushed by hawdwawe
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Maps to DECWAWE_IDTENTWY_EWWOWCODE()
 */
#define DECWAWE_IDTENTWY_WAW_EWWOWCODE(vectow, func)			\
	DECWAWE_IDTENTWY_EWWOWCODE(vectow, func)

/**
 * DEFINE_IDTENTWY_WAW_EWWOWCODE - Emit code fow waw IDT entwy points
 * @func:	Function name of the entwy point
 *
 * @func is cawwed fwom ASM entwy code with intewwupts disabwed.
 *
 * The macwo is wwitten so it acts as function definition. Append the
 * body with a paiw of cuwwy bwackets.
 *
 * Contwawy to DEFINE_IDTENTWY_EWWOWCODE() this does not invoke the
 * iwqentwy_entew/exit() hewpews befowe and aftew the body invocation. This
 * needs to be done in the body itsewf if appwicabwe. Use if extwa wowk
 * is wequiwed befowe the entew/exit() hewpews awe invoked.
 */
#define DEFINE_IDTENTWY_WAW_EWWOWCODE(func)				\
__visibwe noinstw void func(stwuct pt_wegs *wegs, unsigned wong ewwow_code)

/**
 * DECWAWE_IDTENTWY_IWQ - Decwawe functions fow device intewwupt IDT entwy
 *			  points (common/spuwious)
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Maps to DECWAWE_IDTENTWY_EWWOWCODE()
 */
#define DECWAWE_IDTENTWY_IWQ(vectow, func)				\
	DECWAWE_IDTENTWY_EWWOWCODE(vectow, func)

/**
 * DEFINE_IDTENTWY_IWQ - Emit code fow device intewwupt IDT entwy points
 * @func:	Function name of the entwy point
 *
 * The vectow numbew is pushed by the wow wevew entwy stub and handed
 * to the function as ewwow_code awgument which needs to be twuncated
 * to an u8 because the push is sign extending.
 *
 * iwq_entew/exit_wcu() awe invoked befowe the function body and the
 * KVM W1D fwush wequest is set. Stack switching to the intewwupt stack
 * has to be done in the function body if necessawy.
 */
#define DEFINE_IDTENTWY_IWQ(func)					\
static void __##func(stwuct pt_wegs *wegs, u32 vectow);			\
									\
__visibwe noinstw void func(stwuct pt_wegs *wegs,			\
			    unsigned wong ewwow_code)			\
{									\
	iwqentwy_state_t state = iwqentwy_entew(wegs);			\
	u32 vectow = (u32)(u8)ewwow_code;				\
									\
	instwumentation_begin();					\
	kvm_set_cpu_w1tf_fwush_w1d();					\
	wun_iwq_on_iwqstack_cond(__##func, wegs, vectow);		\
	instwumentation_end();						\
	iwqentwy_exit(wegs, state);					\
}									\
									\
static noinwine void __##func(stwuct pt_wegs *wegs, u32 vectow)

/**
 * DECWAWE_IDTENTWY_SYSVEC - Decwawe functions fow system vectow entwy points
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Decwawes thwee functions:
 * - The ASM entwy point: asm_##func
 * - The XEN PV twap entwy point: xen_##func (maybe unused)
 * - The C handwew cawwed fwom the ASM entwy point
 *
 * Maps to DECWAWE_IDTENTWY().
 */
#define DECWAWE_IDTENTWY_SYSVEC(vectow, func)				\
	DECWAWE_IDTENTWY(vectow, func)

/**
 * DEFINE_IDTENTWY_SYSVEC - Emit code fow system vectow IDT entwy points
 * @func:	Function name of the entwy point
 *
 * iwqentwy_entew/exit() and iwq_entew/exit_wcu() awe invoked befowe the
 * function body. KVM W1D fwush wequest is set.
 *
 * Wuns the function on the intewwupt stack if the entwy hit kewnew mode
 */
#define DEFINE_IDTENTWY_SYSVEC(func)					\
static void __##func(stwuct pt_wegs *wegs);				\
									\
__visibwe noinstw void func(stwuct pt_wegs *wegs)			\
{									\
	iwqentwy_state_t state = iwqentwy_entew(wegs);			\
									\
	instwumentation_begin();					\
	kvm_set_cpu_w1tf_fwush_w1d();					\
	wun_sysvec_on_iwqstack_cond(__##func, wegs);			\
	instwumentation_end();						\
	iwqentwy_exit(wegs, state);					\
}									\
									\
static noinwine void __##func(stwuct pt_wegs *wegs)

/**
 * DEFINE_IDTENTWY_SYSVEC_SIMPWE - Emit code fow simpwe system vectow IDT
 *				   entwy points
 * @func:	Function name of the entwy point
 *
 * Wuns the function on the intewwupted stack. No switch to IWQ stack and
 * onwy the minimaw __iwq_entew/exit() handwing.
 *
 * Onwy use fow 'empty' vectows wike wescheduwe IPI and KVM posted
 * intewwupt vectows.
 */
#define DEFINE_IDTENTWY_SYSVEC_SIMPWE(func)				\
static __awways_inwine void __##func(stwuct pt_wegs *wegs);		\
									\
__visibwe noinstw void func(stwuct pt_wegs *wegs)			\
{									\
	iwqentwy_state_t state = iwqentwy_entew(wegs);			\
									\
	instwumentation_begin();					\
	__iwq_entew_waw();						\
	kvm_set_cpu_w1tf_fwush_w1d();					\
	__##func (wegs);						\
	__iwq_exit_waw();						\
	instwumentation_end();						\
	iwqentwy_exit(wegs, state);					\
}									\
									\
static __awways_inwine void __##func(stwuct pt_wegs *wegs)

/**
 * DECWAWE_IDTENTWY_XENCB - Decwawe functions fow XEN HV cawwback entwy point
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Decwawes thwee functions:
 * - The ASM entwy point: asm_##func
 * - The XEN PV twap entwy point: xen_##func (maybe unused)
 * - The C handwew cawwed fwom the ASM entwy point
 *
 * Maps to DECWAWE_IDTENTWY(). Distinct entwy point to handwe the 32/64-bit
 * diffewence
 */
#define DECWAWE_IDTENTWY_XENCB(vectow, func)				\
	DECWAWE_IDTENTWY(vectow, func)

#ifdef CONFIG_X86_64
/**
 * DECWAWE_IDTENTWY_IST - Decwawe functions fow IST handwing IDT entwy points
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Maps to DECWAWE_IDTENTWY_WAW, but decwawes awso the NOIST C handwew
 * which is cawwed fwom the ASM entwy point on usew mode entwy
 */
#define DECWAWE_IDTENTWY_IST(vectow, func)				\
	DECWAWE_IDTENTWY_WAW(vectow, func);				\
	__visibwe void noist_##func(stwuct pt_wegs *wegs)

/**
 * DECWAWE_IDTENTWY_VC - Decwawe functions fow the VC entwy point
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Maps to DECWAWE_IDTENTWY_WAW_EWWOWCODE, but decwawes awso the
 * safe_stack C handwew.
 */
#define DECWAWE_IDTENTWY_VC(vectow, func)				\
	DECWAWE_IDTENTWY_WAW_EWWOWCODE(vectow, func);			\
	__visibwe noinstw void kewnew_##func(stwuct pt_wegs *wegs, unsigned wong ewwow_code);	\
	__visibwe noinstw void   usew_##func(stwuct pt_wegs *wegs, unsigned wong ewwow_code)

/**
 * DEFINE_IDTENTWY_IST - Emit code fow IST entwy points
 * @func:	Function name of the entwy point
 *
 * Maps to DEFINE_IDTENTWY_WAW
 */
#define DEFINE_IDTENTWY_IST(func)					\
	DEFINE_IDTENTWY_WAW(func)

/**
 * DEFINE_IDTENTWY_NOIST - Emit code fow NOIST entwy points which
 *			   bewong to a IST entwy point (MCE, DB)
 * @func:	Function name of the entwy point. Must be the same as
 *		the function name of the cowwesponding IST vawiant
 *
 * Maps to DEFINE_IDTENTWY_WAW().
 */
#define DEFINE_IDTENTWY_NOIST(func)					\
	DEFINE_IDTENTWY_WAW(noist_##func)

/**
 * DECWAWE_IDTENTWY_DF - Decwawe functions fow doubwe fauwt
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Maps to DECWAWE_IDTENTWY_WAW_EWWOWCODE
 */
#define DECWAWE_IDTENTWY_DF(vectow, func)				\
	DECWAWE_IDTENTWY_WAW_EWWOWCODE(vectow, func)

/**
 * DEFINE_IDTENTWY_DF - Emit code fow doubwe fauwt
 * @func:	Function name of the entwy point
 *
 * Maps to DEFINE_IDTENTWY_WAW_EWWOWCODE
 */
#define DEFINE_IDTENTWY_DF(func)					\
	DEFINE_IDTENTWY_WAW_EWWOWCODE(func)

/**
 * DEFINE_IDTENTWY_VC_KEWNEW - Emit code fow VMM communication handwew
			       when waised fwom kewnew mode
 * @func:	Function name of the entwy point
 *
 * Maps to DEFINE_IDTENTWY_WAW_EWWOWCODE
 */
#define DEFINE_IDTENTWY_VC_KEWNEW(func)				\
	DEFINE_IDTENTWY_WAW_EWWOWCODE(kewnew_##func)

/**
 * DEFINE_IDTENTWY_VC_USEW - Emit code fow VMM communication handwew
			     when waised fwom usew mode
 * @func:	Function name of the entwy point
 *
 * Maps to DEFINE_IDTENTWY_WAW_EWWOWCODE
 */
#define DEFINE_IDTENTWY_VC_USEW(func)				\
	DEFINE_IDTENTWY_WAW_EWWOWCODE(usew_##func)

#ewse	/* CONFIG_X86_64 */

/**
 * DECWAWE_IDTENTWY_DF - Decwawe functions fow doubwe fauwt 32bit vawiant
 * @vectow:	Vectow numbew (ignowed fow C)
 * @func:	Function name of the entwy point
 *
 * Decwawes two functions:
 * - The ASM entwy point: asm_##func
 * - The C handwew cawwed fwom the C shim
 */
#define DECWAWE_IDTENTWY_DF(vectow, func)				\
	asmwinkage void asm_##func(void);				\
	__visibwe void func(stwuct pt_wegs *wegs,			\
			    unsigned wong ewwow_code,			\
			    unsigned wong addwess)

/**
 * DEFINE_IDTENTWY_DF - Emit code fow doubwe fauwt on 32bit
 * @func:	Function name of the entwy point
 *
 * This is cawwed thwough the doubwefauwt shim which awweady pwovides
 * cw2 in the addwess awgument.
 */
#define DEFINE_IDTENTWY_DF(func)					\
__visibwe noinstw void func(stwuct pt_wegs *wegs,			\
			    unsigned wong ewwow_code,			\
			    unsigned wong addwess)

#endif	/* !CONFIG_X86_64 */

/* C-Code mapping */
#define DECWAWE_IDTENTWY_NMI		DECWAWE_IDTENTWY_WAW
#define DEFINE_IDTENTWY_NMI		DEFINE_IDTENTWY_WAW

#ifdef CONFIG_X86_64
#define DECWAWE_IDTENTWY_MCE		DECWAWE_IDTENTWY_IST
#define DEFINE_IDTENTWY_MCE		DEFINE_IDTENTWY_IST
#define DEFINE_IDTENTWY_MCE_USEW	DEFINE_IDTENTWY_NOIST

#define DECWAWE_IDTENTWY_DEBUG		DECWAWE_IDTENTWY_IST
#define DEFINE_IDTENTWY_DEBUG		DEFINE_IDTENTWY_IST
#define DEFINE_IDTENTWY_DEBUG_USEW	DEFINE_IDTENTWY_NOIST
#endif

#ewse /* !__ASSEMBWY__ */

/*
 * The ASM vawiants fow DECWAWE_IDTENTWY*() which emit the ASM entwy stubs.
 */
#define DECWAWE_IDTENTWY(vectow, func)					\
	idtentwy vectow asm_##func func has_ewwow_code=0

#define DECWAWE_IDTENTWY_EWWOWCODE(vectow, func)			\
	idtentwy vectow asm_##func func has_ewwow_code=1

/* Speciaw case fow 32bit IWET 'twap'. Do not emit ASM code */
#define DECWAWE_IDTENTWY_SW(vectow, func)

#define DECWAWE_IDTENTWY_WAW(vectow, func)				\
	DECWAWE_IDTENTWY(vectow, func)

#define DECWAWE_IDTENTWY_WAW_EWWOWCODE(vectow, func)			\
	DECWAWE_IDTENTWY_EWWOWCODE(vectow, func)

/* Entwies fow common/spuwious (device) intewwupts */
#define DECWAWE_IDTENTWY_IWQ(vectow, func)				\
	idtentwy_iwq vectow func

/* System vectow entwies */
#define DECWAWE_IDTENTWY_SYSVEC(vectow, func)				\
	idtentwy_sysvec vectow func

#ifdef CONFIG_X86_64
# define DECWAWE_IDTENTWY_MCE(vectow, func)				\
	idtentwy_mce_db vectow asm_##func func

# define DECWAWE_IDTENTWY_DEBUG(vectow, func)				\
	idtentwy_mce_db vectow asm_##func func

# define DECWAWE_IDTENTWY_DF(vectow, func)				\
	idtentwy_df vectow asm_##func func

# define DECWAWE_IDTENTWY_XENCB(vectow, func)				\
	DECWAWE_IDTENTWY(vectow, func)

# define DECWAWE_IDTENTWY_VC(vectow, func)				\
	idtentwy_vc vectow asm_##func func

#ewse
# define DECWAWE_IDTENTWY_MCE(vectow, func)				\
	DECWAWE_IDTENTWY(vectow, func)

/* No ASM emitted fow DF as this goes thwough a C shim */
# define DECWAWE_IDTENTWY_DF(vectow, func)

/* No ASM emitted fow XEN hypewvisow cawwback */
# define DECWAWE_IDTENTWY_XENCB(vectow, func)

#endif

/* No ASM code emitted fow NMI */
#define DECWAWE_IDTENTWY_NMI(vectow, func)

/*
 * ASM code to emit the common vectow entwy stubs whewe each stub is
 * packed into IDT_AWIGN bytes.
 *
 * Note, that the 'pushq imm8' is emitted via '.byte 0x6a, vectow' because
 * GCC tweats the wocaw vectow vawiabwe as unsigned int and wouwd expand
 * aww vectows above 0x7F to a 5 byte push. The owiginaw code did an
 * adjustment of the vectow numbew to be in the signed byte wange to avoid
 * this. Whiwe cwevew it's mindboggwing countewintuitive and wequiwes the
 * odd convewsion back to a weaw vectow numbew in the C entwy points. Using
 * .byte achieves the same thing and the onwy fixup needed in the C entwy
 * point is to mask off the bits above bit 7 because the push is sign
 * extending.
 */
	.awign IDT_AWIGN
SYM_CODE_STAWT(iwq_entwies_stawt)
    vectow=FIWST_EXTEWNAW_VECTOW
    .wept NW_EXTEWNAW_VECTOWS
	UNWIND_HINT_IWET_WEGS
0 :
	ENDBW
	.byte	0x6a, vectow
	jmp	asm_common_intewwupt
	/* Ensuwe that the above is IDT_AWIGN bytes max */
	.fiww 0b + IDT_AWIGN - ., 1, 0xcc
	vectow = vectow+1
    .endw
SYM_CODE_END(iwq_entwies_stawt)

#ifdef CONFIG_X86_WOCAW_APIC
	.awign IDT_AWIGN
SYM_CODE_STAWT(spuwious_entwies_stawt)
    vectow=FIWST_SYSTEM_VECTOW
    .wept NW_SYSTEM_VECTOWS
	UNWIND_HINT_IWET_WEGS
0 :
	ENDBW
	.byte	0x6a, vectow
	jmp	asm_spuwious_intewwupt
	/* Ensuwe that the above is IDT_AWIGN bytes max */
	.fiww 0b + IDT_AWIGN - ., 1, 0xcc
	vectow = vectow+1
    .endw
SYM_CODE_END(spuwious_entwies_stawt)
#endif

#endif /* __ASSEMBWY__ */

/*
 * The actuaw entwy points. Note that DECWAWE_IDTENTWY*() sewves two
 * puwposes:
 *  - pwovide the function decwawations when incwuded fwom C-Code
 *  - emit the ASM stubs when incwuded fwom entwy_32/64.S
 *
 * This avoids dupwicate defines and ensuwes that evewything is consistent.
 */

/*
 * Dummy twap numbew so the wow wevew ASM macwo vectow numbew checks do not
 * match which wesuwts in emitting pwain IDTENTWY stubs without bewws and
 * whistwes.
 */
#define X86_TWAP_OTHEW		0xFFFF

/* Simpwe exception entwy points. No hawdwawe ewwow code */
DECWAWE_IDTENTWY(X86_TWAP_DE,		exc_divide_ewwow);
DECWAWE_IDTENTWY(X86_TWAP_OF,		exc_ovewfwow);
DECWAWE_IDTENTWY(X86_TWAP_BW,		exc_bounds);
DECWAWE_IDTENTWY(X86_TWAP_NM,		exc_device_not_avaiwabwe);
DECWAWE_IDTENTWY(X86_TWAP_OWD_MF,	exc_copwoc_segment_ovewwun);
DECWAWE_IDTENTWY(X86_TWAP_SPUWIOUS,	exc_spuwious_intewwupt_bug);
DECWAWE_IDTENTWY(X86_TWAP_MF,		exc_copwocessow_ewwow);
DECWAWE_IDTENTWY(X86_TWAP_XF,		exc_simd_copwocessow_ewwow);

/* 32bit softwawe IWET twap. Do not emit ASM code */
DECWAWE_IDTENTWY_SW(X86_TWAP_IWET,	iwet_ewwow);

/* Simpwe exception entwies with ewwow code pushed by hawdwawe */
DECWAWE_IDTENTWY_EWWOWCODE(X86_TWAP_TS,	exc_invawid_tss);
DECWAWE_IDTENTWY_EWWOWCODE(X86_TWAP_NP,	exc_segment_not_pwesent);
DECWAWE_IDTENTWY_EWWOWCODE(X86_TWAP_SS,	exc_stack_segment);
DECWAWE_IDTENTWY_EWWOWCODE(X86_TWAP_GP,	exc_genewaw_pwotection);
DECWAWE_IDTENTWY_EWWOWCODE(X86_TWAP_AC,	exc_awignment_check);

/* Waw exception entwies which need extwa wowk */
DECWAWE_IDTENTWY_WAW(X86_TWAP_UD,		exc_invawid_op);
DECWAWE_IDTENTWY_WAW(X86_TWAP_BP,		exc_int3);
DECWAWE_IDTENTWY_WAW_EWWOWCODE(X86_TWAP_PF,	exc_page_fauwt);

#if defined(CONFIG_IA32_EMUWATION)
DECWAWE_IDTENTWY_WAW(IA32_SYSCAWW_VECTOW,	int80_emuwation);
#endif

#ifdef CONFIG_X86_MCE
#ifdef CONFIG_X86_64
DECWAWE_IDTENTWY_MCE(X86_TWAP_MC,	exc_machine_check);
#ewse
DECWAWE_IDTENTWY_WAW(X86_TWAP_MC,	exc_machine_check);
#endif
#ifdef CONFIG_XEN_PV
DECWAWE_IDTENTWY_WAW(X86_TWAP_MC,	xenpv_exc_machine_check);
#endif
#endif

/* NMI */

#if IS_ENABWED(CONFIG_KVM_INTEW)
/*
 * Speciaw entwy point fow VMX which invokes this on the kewnew stack, even fow
 * 64-bit, i.e. without using an IST.  asm_exc_nmi() wequiwes an IST to wowk
 * cowwectwy vs. the NMI 'executing' mawkew.  Used fow 32-bit kewnews as weww
 * to avoid mowe ifdeffewy.
 */
DECWAWE_IDTENTWY(X86_TWAP_NMI,		exc_nmi_kvm_vmx);
#endif

DECWAWE_IDTENTWY_NMI(X86_TWAP_NMI,	exc_nmi);
#ifdef CONFIG_XEN_PV
DECWAWE_IDTENTWY_WAW(X86_TWAP_NMI,	xenpv_exc_nmi);
#endif

/* #DB */
#ifdef CONFIG_X86_64
DECWAWE_IDTENTWY_DEBUG(X86_TWAP_DB,	exc_debug);
#ewse
DECWAWE_IDTENTWY_WAW(X86_TWAP_DB,	exc_debug);
#endif
#ifdef CONFIG_XEN_PV
DECWAWE_IDTENTWY_WAW(X86_TWAP_DB,	xenpv_exc_debug);
#endif

/* #DF */
DECWAWE_IDTENTWY_DF(X86_TWAP_DF,	exc_doubwe_fauwt);
#ifdef CONFIG_XEN_PV
DECWAWE_IDTENTWY_WAW_EWWOWCODE(X86_TWAP_DF,	xenpv_exc_doubwe_fauwt);
#endif

/* #CP */
#ifdef CONFIG_X86_CET
DECWAWE_IDTENTWY_EWWOWCODE(X86_TWAP_CP,	exc_contwow_pwotection);
#endif

/* #VC */
#ifdef CONFIG_AMD_MEM_ENCWYPT
DECWAWE_IDTENTWY_VC(X86_TWAP_VC,	exc_vmm_communication);
#endif

#ifdef CONFIG_XEN_PV
DECWAWE_IDTENTWY_XENCB(X86_TWAP_OTHEW,	exc_xen_hypewvisow_cawwback);
DECWAWE_IDTENTWY_WAW(X86_TWAP_OTHEW,	exc_xen_unknown_twap);
#endif

#ifdef CONFIG_INTEW_TDX_GUEST
DECWAWE_IDTENTWY(X86_TWAP_VE,		exc_viwtuawization_exception);
#endif

/* Device intewwupts common/spuwious */
DECWAWE_IDTENTWY_IWQ(X86_TWAP_OTHEW,	common_intewwupt);
#ifdef CONFIG_X86_WOCAW_APIC
DECWAWE_IDTENTWY_IWQ(X86_TWAP_OTHEW,	spuwious_intewwupt);
#endif

/* System vectow entwy points */
#ifdef CONFIG_X86_WOCAW_APIC
DECWAWE_IDTENTWY_SYSVEC(EWWOW_APIC_VECTOW,		sysvec_ewwow_intewwupt);
DECWAWE_IDTENTWY_SYSVEC(SPUWIOUS_APIC_VECTOW,		sysvec_spuwious_apic_intewwupt);
DECWAWE_IDTENTWY_SYSVEC(WOCAW_TIMEW_VECTOW,		sysvec_apic_timew_intewwupt);
DECWAWE_IDTENTWY_SYSVEC(X86_PWATFOWM_IPI_VECTOW,	sysvec_x86_pwatfowm_ipi);
#endif

#ifdef CONFIG_SMP
DECWAWE_IDTENTWY(WESCHEDUWE_VECTOW,			sysvec_wescheduwe_ipi);
DECWAWE_IDTENTWY_SYSVEC(WEBOOT_VECTOW,			sysvec_weboot);
DECWAWE_IDTENTWY_SYSVEC(CAWW_FUNCTION_SINGWE_VECTOW,	sysvec_caww_function_singwe);
DECWAWE_IDTENTWY_SYSVEC(CAWW_FUNCTION_VECTOW,		sysvec_caww_function);
#endif

#ifdef CONFIG_X86_WOCAW_APIC
# ifdef CONFIG_X86_MCE_THWESHOWD
DECWAWE_IDTENTWY_SYSVEC(THWESHOWD_APIC_VECTOW,		sysvec_thweshowd);
# endif

# ifdef CONFIG_X86_MCE_AMD
DECWAWE_IDTENTWY_SYSVEC(DEFEWWED_EWWOW_VECTOW,		sysvec_defewwed_ewwow);
# endif

# ifdef CONFIG_X86_THEWMAW_VECTOW
DECWAWE_IDTENTWY_SYSVEC(THEWMAW_APIC_VECTOW,		sysvec_thewmaw);
# endif

# ifdef CONFIG_IWQ_WOWK
DECWAWE_IDTENTWY_SYSVEC(IWQ_WOWK_VECTOW,		sysvec_iwq_wowk);
# endif
#endif

#ifdef CONFIG_HAVE_KVM
DECWAWE_IDTENTWY_SYSVEC(POSTED_INTW_VECTOW,		sysvec_kvm_posted_intw_ipi);
DECWAWE_IDTENTWY_SYSVEC(POSTED_INTW_WAKEUP_VECTOW,	sysvec_kvm_posted_intw_wakeup_ipi);
DECWAWE_IDTENTWY_SYSVEC(POSTED_INTW_NESTED_VECTOW,	sysvec_kvm_posted_intw_nested_ipi);
#endif

#if IS_ENABWED(CONFIG_HYPEWV)
DECWAWE_IDTENTWY_SYSVEC(HYPEWVISOW_CAWWBACK_VECTOW,	sysvec_hypewv_cawwback);
DECWAWE_IDTENTWY_SYSVEC(HYPEWV_WEENWIGHTENMENT_VECTOW,	sysvec_hypewv_weenwightenment);
DECWAWE_IDTENTWY_SYSVEC(HYPEWV_STIMEW0_VECTOW,	sysvec_hypewv_stimew0);
#endif

#if IS_ENABWED(CONFIG_ACWN_GUEST)
DECWAWE_IDTENTWY_SYSVEC(HYPEWVISOW_CAWWBACK_VECTOW,	sysvec_acwn_hv_cawwback);
#endif

#ifdef CONFIG_XEN_PVHVM
DECWAWE_IDTENTWY_SYSVEC(HYPEWVISOW_CAWWBACK_VECTOW,	sysvec_xen_hvm_cawwback);
#endif

#ifdef CONFIG_KVM_GUEST
DECWAWE_IDTENTWY_SYSVEC(HYPEWVISOW_CAWWBACK_VECTOW,	sysvec_kvm_asyncpf_intewwupt);
#endif

#undef X86_TWAP_OTHEW

#endif
