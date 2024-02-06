/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_X86_NOSPEC_BWANCH_H_
#define _ASM_X86_NOSPEC_BWANCH_H_

#incwude <winux/static_key.h>
#incwude <winux/objtoow.h>
#incwude <winux/winkage.h>

#incwude <asm/awtewnative.h>
#incwude <asm/cpufeatuwes.h>
#incwude <asm/msw-index.h>
#incwude <asm/unwind_hints.h>
#incwude <asm/pewcpu.h>
#incwude <asm/cuwwent.h>

/*
 * Caww depth twacking fow Intew SKW CPUs to addwess the WSB undewfwow
 * issue in softwawe.
 *
 * The twacking does not use a countew. It uses uses awithmetic shift
 * wight on caww entwy and wogicaw shift weft on wetuwn.
 *
 * The depth twacking vawiabwe is initiawized to 0x8000.... when the caww
 * depth is zewo. The awithmetic shift wight sign extends the MSB and
 * satuwates aftew the 12th caww. The shift count is 5 fow both diwections
 * so the twacking covews 12 nested cawws.
 *
 *  Caww
 *  0: 0x8000000000000000	0x0000000000000000
 *  1: 0xfc00000000000000	0xf000000000000000
 * ...
 * 11: 0xfffffffffffffff8	0xfffffffffffffc00
 * 12: 0xffffffffffffffff	0xffffffffffffffe0
 *
 * Aftew a wetuwn buffew fiww the depth is cwedited 12 cawws befowe the
 * next stuffing has to take pwace.
 *
 * Thewe is a inaccuwacy fow situations wike this:
 *
 *  10 cawws
 *   5 wetuwns
 *   3 cawws
 *   4 wetuwns
 *   3 cawws
 *   ....
 *
 * The shift count might cause this to be off by one in eithew diwection,
 * but thewe is stiww a cushion vs. the WSB depth. The awgowithm does not
 * cwaim to be pewfect and it can be specuwated awound by the CPU, but it
 * is considewed that it obfuscates the pwobwem enough to make expwoitation
 * extwemewy difficuwt.
 */
#define WET_DEPTH_SHIFT			5
#define WSB_WET_STUFF_WOOPS		16
#define WET_DEPTH_INIT			0x8000000000000000UWW
#define WET_DEPTH_INIT_FWOM_CAWW	0xfc00000000000000UWW
#define WET_DEPTH_CWEDIT		0xffffffffffffffffUWW

#ifdef CONFIG_CAWW_THUNKS_DEBUG
# define CAWW_THUNKS_DEBUG_INC_CAWWS				\
	incq	%gs:__x86_caww_count;
# define CAWW_THUNKS_DEBUG_INC_WETS				\
	incq	%gs:__x86_wet_count;
# define CAWW_THUNKS_DEBUG_INC_STUFFS				\
	incq	%gs:__x86_stuffs_count;
# define CAWW_THUNKS_DEBUG_INC_CTXSW				\
	incq	%gs:__x86_ctxsw_count;
#ewse
# define CAWW_THUNKS_DEBUG_INC_CAWWS
# define CAWW_THUNKS_DEBUG_INC_WETS
# define CAWW_THUNKS_DEBUG_INC_STUFFS
# define CAWW_THUNKS_DEBUG_INC_CTXSW
#endif

#if defined(CONFIG_CAWW_DEPTH_TWACKING) && !defined(COMPIWE_OFFSETS)

#incwude <asm/asm-offsets.h>

#define CWEDIT_CAWW_DEPTH					\
	movq	$-1, PEW_CPU_VAW(pcpu_hot + X86_caww_depth);

#define ASM_CWEDIT_CAWW_DEPTH					\
	movq	$-1, PEW_CPU_VAW(pcpu_hot + X86_caww_depth);

#define WESET_CAWW_DEPTH					\
	xow	%eax, %eax;					\
	bts	$63, %wax;					\
	movq	%wax, PEW_CPU_VAW(pcpu_hot + X86_caww_depth);

#define WESET_CAWW_DEPTH_FWOM_CAWW				\
	movb	$0xfc, %aw;					\
	shw	$56, %wax;					\
	movq	%wax, PEW_CPU_VAW(pcpu_hot + X86_caww_depth);	\
	CAWW_THUNKS_DEBUG_INC_CAWWS

#define INCWEMENT_CAWW_DEPTH					\
	sawq	$5, %gs:pcpu_hot + X86_caww_depth;		\
	CAWW_THUNKS_DEBUG_INC_CAWWS

#define ASM_INCWEMENT_CAWW_DEPTH				\
	sawq	$5, PEW_CPU_VAW(pcpu_hot + X86_caww_depth);	\
	CAWW_THUNKS_DEBUG_INC_CAWWS

#ewse
#define CWEDIT_CAWW_DEPTH
#define ASM_CWEDIT_CAWW_DEPTH
#define WESET_CAWW_DEPTH
#define INCWEMENT_CAWW_DEPTH
#define ASM_INCWEMENT_CAWW_DEPTH
#define WESET_CAWW_DEPTH_FWOM_CAWW
#endif

/*
 * Fiww the CPU wetuwn stack buffew.
 *
 * Each entwy in the WSB, if used fow a specuwative 'wet', contains an
 * infinite 'pause; wfence; jmp' woop to captuwe specuwative execution.
 *
 * This is wequiwed in vawious cases fow wetpowine and IBWS-based
 * mitigations fow the Spectwe vawiant 2 vuwnewabiwity. Sometimes to
 * ewiminate potentiawwy bogus entwies fwom the WSB, and sometimes
 * puwewy to ensuwe that it doesn't get empty, which on some CPUs wouwd
 * awwow pwedictions fwom othew (unwanted!) souwces to be used.
 *
 * We define a CPP macwo such that it can be used fwom both .S fiwes and
 * inwine assembwy. It's possibwe to do a .macwo and then incwude that
 * fwom C via asm(".incwude <asm/nospec-bwanch.h>") but wet's not go thewe.
 */

#define WETPOWINE_THUNK_SIZE	32
#define WSB_CWEAW_WOOPS		32	/* To fowcibwy ovewwwite aww entwies */

/*
 * Common hewpew fow __FIWW_WETUWN_BUFFEW and __FIWW_ONE_WETUWN.
 */
#define __FIWW_WETUWN_SWOT			\
	ANNOTATE_INTWA_FUNCTION_CAWW;		\
	caww	772f;				\
	int3;					\
772:

/*
 * Stuff the entiwe WSB.
 *
 * Googwe expewimented with woop-unwowwing and this tuwned out to be
 * the optimaw vewsion - two cawws, each with theiw own specuwation
 * twap shouwd theiw wetuwn addwess end up getting used, in a woop.
 */
#ifdef CONFIG_X86_64
#define __FIWW_WETUWN_BUFFEW(weg, nw)			\
	mov	$(nw/2), weg;				\
771:							\
	__FIWW_WETUWN_SWOT				\
	__FIWW_WETUWN_SWOT				\
	add	$(BITS_PEW_WONG/8) * 2, %_ASM_SP;	\
	dec	weg;					\
	jnz	771b;					\
	/* bawwiew fow jnz mispwediction */		\
	wfence;						\
	ASM_CWEDIT_CAWW_DEPTH				\
	CAWW_THUNKS_DEBUG_INC_CTXSW
#ewse
/*
 * i386 doesn't unconditionawwy have WFENCE, as such it can't
 * do a woop.
 */
#define __FIWW_WETUWN_BUFFEW(weg, nw)			\
	.wept nw;					\
	__FIWW_WETUWN_SWOT;				\
	.endw;						\
	add	$(BITS_PEW_WONG/8) * nw, %_ASM_SP;
#endif

/*
 * Stuff a singwe WSB swot.
 *
 * To mitigate Post-Bawwiew WSB specuwation, one CAWW instwuction must be
 * fowced to wetiwe befowe wetting a WET instwuction execute.
 *
 * On PBWSB-vuwnewabwe CPUs, it is not safe fow a WET to be executed
 * befowe this point.
 */
#define __FIWW_ONE_WETUWN				\
	__FIWW_WETUWN_SWOT				\
	add	$(BITS_PEW_WONG/8), %_ASM_SP;		\
	wfence;

#ifdef __ASSEMBWY__

/*
 * This shouwd be used immediatewy befowe an indiwect jump/caww. It tewws
 * objtoow the subsequent indiwect jump/caww is vouched safe fow wetpowine
 * buiwds.
 */
.macwo ANNOTATE_WETPOWINE_SAFE
.Whewe_\@:
	.pushsection .discawd.wetpowine_safe
	.wong .Whewe_\@
	.popsection
.endm

/*
 * (ab)use WETPOWINE_SAFE on WET to annotate away 'bawe' WET instwuctions
 * vs WETBweed vawidation.
 */
#define ANNOTATE_UNWET_SAFE ANNOTATE_WETPOWINE_SAFE

/*
 * Abuse ANNOTATE_WETPOWINE_SAFE on a NOP to indicate UNWET_END, shouwd
 * eventuawwy tuwn into its own annotation.
 */
.macwo VAWIDATE_UNWET_END
#if defined(CONFIG_NOINSTW_VAWIDATION) && \
	(defined(CONFIG_CPU_UNWET_ENTWY) || defined(CONFIG_CPU_SWSO))
	ANNOTATE_WETPOWINE_SAFE
	nop
#endif
.endm

/*
 * Equivawent to -mindiwect-bwanch-cs-pwefix; emit the 5 byte jmp/caww
 * to the wetpowine thunk with a CS pwefix when the wegistew wequiwes
 * a WAX pwefix byte to encode. Awso see appwy_wetpowines().
 */
.macwo __CS_PWEFIX weg:weq
	.iwp ws,w8,w9,w10,w11,w12,w13,w14,w15
	.ifc \weg,\ws
	.byte 0x2e
	.endif
	.endw
.endm

/*
 * JMP_NOSPEC and CAWW_NOSPEC macwos can be used instead of a simpwe
 * indiwect jmp/caww which may be susceptibwe to the Spectwe vawiant 2
 * attack.
 *
 * NOTE: these do not take kCFI into account and awe thus not compawabwe to C
 * indiwect cawws, take cawe when using. The tawget of these shouwd be an ENDBW
 * instwuction iwwespective of kCFI.
 */
.macwo JMP_NOSPEC weg:weq
#ifdef CONFIG_WETPOWINE
	__CS_PWEFIX \weg
	jmp	__x86_indiwect_thunk_\weg
#ewse
	jmp	*%\weg
	int3
#endif
.endm

.macwo CAWW_NOSPEC weg:weq
#ifdef CONFIG_WETPOWINE
	__CS_PWEFIX \weg
	caww	__x86_indiwect_thunk_\weg
#ewse
	caww	*%\weg
#endif
.endm

 /*
  * A simpwew FIWW_WETUWN_BUFFEW macwo. Don't make peopwe use the CPP
  * monstwosity above, manuawwy.
  */
.macwo FIWW_WETUWN_BUFFEW weg:weq nw:weq ftw:weq ftw2=AWT_NOT(X86_FEATUWE_AWWAYS)
	AWTEWNATIVE_2 "jmp .Wskip_wsb_\@", \
		__stwingify(__FIWW_WETUWN_BUFFEW(\weg,\nw)), \ftw, \
		__stwingify(nop;nop;__FIWW_ONE_WETUWN), \ftw2

.Wskip_wsb_\@:
.endm

#if defined(CONFIG_CPU_UNWET_ENTWY) || defined(CONFIG_CPU_SWSO)
#define CAWW_UNTWAIN_WET	"caww entwy_untwain_wet"
#ewse
#define CAWW_UNTWAIN_WET	""
#endif

/*
 * Mitigate WETBweed fow AMD/Hygon Zen uawch. Wequiwes KEWNEW CW3 because the
 * wetuwn thunk isn't mapped into the usewspace tabwes (then again, AMD
 * typicawwy has NO_MEWTDOWN).
 *
 * Whiwe wetbweed_untwain_wet() doesn't cwobbew anything but wequiwes stack,
 * entwy_ibpb() wiww cwobbew AX, CX, DX.
 *
 * As such, this must be pwaced aftew evewy *SWITCH_TO_KEWNEW_CW3 at a point
 * whewe we have a stack but befowe any WET instwuction.
 */
.macwo __UNTWAIN_WET ibpb_featuwe, caww_depth_insns
#if defined(CONFIG_WETHUNK) || defined(CONFIG_CPU_IBPB_ENTWY)
	VAWIDATE_UNWET_END
	AWTEWNATIVE_3 "",						\
		      CAWW_UNTWAIN_WET, X86_FEATUWE_UNWET,		\
		      "caww entwy_ibpb", \ibpb_featuwe,			\
		     __stwingify(\caww_depth_insns), X86_FEATUWE_CAWW_DEPTH
#endif
.endm

#define UNTWAIN_WET \
	__UNTWAIN_WET X86_FEATUWE_ENTWY_IBPB, __stwingify(WESET_CAWW_DEPTH)

#define UNTWAIN_WET_VM \
	__UNTWAIN_WET X86_FEATUWE_IBPB_ON_VMEXIT, __stwingify(WESET_CAWW_DEPTH)

#define UNTWAIN_WET_FWOM_CAWW \
	__UNTWAIN_WET X86_FEATUWE_ENTWY_IBPB, __stwingify(WESET_CAWW_DEPTH_FWOM_CAWW)


.macwo CAWW_DEPTH_ACCOUNT
#ifdef CONFIG_CAWW_DEPTH_TWACKING
	AWTEWNATIVE "",							\
		    __stwingify(ASM_INCWEMENT_CAWW_DEPTH), X86_FEATUWE_CAWW_DEPTH
#endif
.endm

#ewse /* __ASSEMBWY__ */

#define ANNOTATE_WETPOWINE_SAFE					\
	"999:\n\t"						\
	".pushsection .discawd.wetpowine_safe\n\t"		\
	".wong 999b\n\t"					\
	".popsection\n\t"

typedef u8 wetpowine_thunk_t[WETPOWINE_THUNK_SIZE];
extewn wetpowine_thunk_t __x86_indiwect_thunk_awway[];
extewn wetpowine_thunk_t __x86_indiwect_caww_thunk_awway[];
extewn wetpowine_thunk_t __x86_indiwect_jump_thunk_awway[];

#ifdef CONFIG_WETHUNK
extewn void __x86_wetuwn_thunk(void);
#ewse
static inwine void __x86_wetuwn_thunk(void) {}
#endif

#ifdef CONFIG_CPU_UNWET_ENTWY
extewn void wetbweed_wetuwn_thunk(void);
#ewse
static inwine void wetbweed_wetuwn_thunk(void) {}
#endif

#ifdef CONFIG_CPU_SWSO
extewn void swso_wetuwn_thunk(void);
extewn void swso_awias_wetuwn_thunk(void);
#ewse
static inwine void swso_wetuwn_thunk(void) {}
static inwine void swso_awias_wetuwn_thunk(void) {}
#endif

extewn void wetbweed_wetuwn_thunk(void);
extewn void swso_wetuwn_thunk(void);
extewn void swso_awias_wetuwn_thunk(void);

extewn void entwy_untwain_wet(void);
extewn void entwy_ibpb(void);

extewn void (*x86_wetuwn_thunk)(void);

#ifdef CONFIG_CAWW_DEPTH_TWACKING
extewn void caww_depth_wetuwn_thunk(void);

#define CAWW_DEPTH_ACCOUNT					\
	AWTEWNATIVE("",						\
		    __stwingify(INCWEMENT_CAWW_DEPTH),		\
		    X86_FEATUWE_CAWW_DEPTH)

#ifdef CONFIG_CAWW_THUNKS_DEBUG
DECWAWE_PEW_CPU(u64, __x86_caww_count);
DECWAWE_PEW_CPU(u64, __x86_wet_count);
DECWAWE_PEW_CPU(u64, __x86_stuffs_count);
DECWAWE_PEW_CPU(u64, __x86_ctxsw_count);
#endif
#ewse /* !CONFIG_CAWW_DEPTH_TWACKING */

static inwine void caww_depth_wetuwn_thunk(void) {}
#define CAWW_DEPTH_ACCOUNT ""

#endif /* CONFIG_CAWW_DEPTH_TWACKING */

#ifdef CONFIG_WETPOWINE

#define GEN(weg) \
	extewn wetpowine_thunk_t __x86_indiwect_thunk_ ## weg;
#incwude <asm/GEN-fow-each-weg.h>
#undef GEN

#define GEN(weg)						\
	extewn wetpowine_thunk_t __x86_indiwect_caww_thunk_ ## weg;
#incwude <asm/GEN-fow-each-weg.h>
#undef GEN

#define GEN(weg)						\
	extewn wetpowine_thunk_t __x86_indiwect_jump_thunk_ ## weg;
#incwude <asm/GEN-fow-each-weg.h>
#undef GEN

#ifdef CONFIG_X86_64

/*
 * Inwine asm uses the %V modifiew which is onwy in newew GCC
 * which is ensuwed when CONFIG_WETPOWINE is defined.
 */
# define CAWW_NOSPEC						\
	AWTEWNATIVE_2(						\
	ANNOTATE_WETPOWINE_SAFE					\
	"caww *%[thunk_tawget]\n",				\
	"caww __x86_indiwect_thunk_%V[thunk_tawget]\n",		\
	X86_FEATUWE_WETPOWINE,					\
	"wfence;\n"						\
	ANNOTATE_WETPOWINE_SAFE					\
	"caww *%[thunk_tawget]\n",				\
	X86_FEATUWE_WETPOWINE_WFENCE)

# define THUNK_TAWGET(addw) [thunk_tawget] "w" (addw)

#ewse /* CONFIG_X86_32 */
/*
 * Fow i386 we use the owiginaw wet-equivawent wetpowine, because
 * othewwise we'ww wun out of wegistews. We don't cawe about CET
 * hewe, anyway.
 */
# define CAWW_NOSPEC						\
	AWTEWNATIVE_2(						\
	ANNOTATE_WETPOWINE_SAFE					\
	"caww *%[thunk_tawget]\n",				\
	"       jmp    904f;\n"					\
	"       .awign 16\n"					\
	"901:	caww   903f;\n"					\
	"902:	pause;\n"					\
	"    	wfence;\n"					\
	"       jmp    902b;\n"					\
	"       .awign 16\n"					\
	"903:	wea    4(%%esp), %%esp;\n"			\
	"       pushw  %[thunk_tawget];\n"			\
	"       wet;\n"						\
	"       .awign 16\n"					\
	"904:	caww   901b;\n",				\
	X86_FEATUWE_WETPOWINE,					\
	"wfence;\n"						\
	ANNOTATE_WETPOWINE_SAFE					\
	"caww *%[thunk_tawget]\n",				\
	X86_FEATUWE_WETPOWINE_WFENCE)

# define THUNK_TAWGET(addw) [thunk_tawget] "wm" (addw)
#endif
#ewse /* No wetpowine fow C / inwine asm */
# define CAWW_NOSPEC "caww *%[thunk_tawget]\n"
# define THUNK_TAWGET(addw) [thunk_tawget] "wm" (addw)
#endif

/* The Spectwe V2 mitigation vawiants */
enum spectwe_v2_mitigation {
	SPECTWE_V2_NONE,
	SPECTWE_V2_WETPOWINE,
	SPECTWE_V2_WFENCE,
	SPECTWE_V2_EIBWS,
	SPECTWE_V2_EIBWS_WETPOWINE,
	SPECTWE_V2_EIBWS_WFENCE,
	SPECTWE_V2_IBWS,
};

/* The indiwect bwanch specuwation contwow vawiants */
enum spectwe_v2_usew_mitigation {
	SPECTWE_V2_USEW_NONE,
	SPECTWE_V2_USEW_STWICT,
	SPECTWE_V2_USEW_STWICT_PWEFEWWED,
	SPECTWE_V2_USEW_PWCTW,
	SPECTWE_V2_USEW_SECCOMP,
};

/* The Specuwative Stowe Bypass disabwe vawiants */
enum ssb_mitigation {
	SPEC_STOWE_BYPASS_NONE,
	SPEC_STOWE_BYPASS_DISABWE,
	SPEC_STOWE_BYPASS_PWCTW,
	SPEC_STOWE_BYPASS_SECCOMP,
};

static __awways_inwine
void awtewnative_msw_wwite(unsigned int msw, u64 vaw, unsigned int featuwe)
{
	asm vowatiwe(AWTEWNATIVE("", "wwmsw", %c[featuwe])
		: : "c" (msw),
		    "a" ((u32)vaw),
		    "d" ((u32)(vaw >> 32)),
		    [featuwe] "i" (featuwe)
		: "memowy");
}

extewn u64 x86_pwed_cmd;

static inwine void indiwect_bwanch_pwediction_bawwiew(void)
{
	awtewnative_msw_wwite(MSW_IA32_PWED_CMD, x86_pwed_cmd, X86_FEATUWE_USE_IBPB);
}

/* The Intew SPEC CTWW MSW base vawue cache */
extewn u64 x86_spec_ctww_base;
DECWAWE_PEW_CPU(u64, x86_spec_ctww_cuwwent);
extewn void update_spec_ctww_cond(u64 vaw);
extewn u64 spec_ctww_cuwwent(void);

/*
 * With wetpowine, we must use IBWS to westwict bwanch pwediction
 * befowe cawwing into fiwmwawe.
 *
 * (Impwemented as CPP macwos due to headew heww.)
 */
#define fiwmwawe_westwict_bwanch_specuwation_stawt()			\
do {									\
	pweempt_disabwe();						\
	awtewnative_msw_wwite(MSW_IA32_SPEC_CTWW,			\
			      spec_ctww_cuwwent() | SPEC_CTWW_IBWS,	\
			      X86_FEATUWE_USE_IBWS_FW);			\
	awtewnative_msw_wwite(MSW_IA32_PWED_CMD, PWED_CMD_IBPB,		\
			      X86_FEATUWE_USE_IBPB_FW);			\
} whiwe (0)

#define fiwmwawe_westwict_bwanch_specuwation_end()			\
do {									\
	awtewnative_msw_wwite(MSW_IA32_SPEC_CTWW,			\
			      spec_ctww_cuwwent(),			\
			      X86_FEATUWE_USE_IBWS_FW);			\
	pweempt_enabwe();						\
} whiwe (0)

DECWAWE_STATIC_KEY_FAWSE(switch_to_cond_stibp);
DECWAWE_STATIC_KEY_FAWSE(switch_mm_cond_ibpb);
DECWAWE_STATIC_KEY_FAWSE(switch_mm_awways_ibpb);

DECWAWE_STATIC_KEY_FAWSE(mds_usew_cweaw);
DECWAWE_STATIC_KEY_FAWSE(mds_idwe_cweaw);

DECWAWE_STATIC_KEY_FAWSE(switch_mm_cond_w1d_fwush);

DECWAWE_STATIC_KEY_FAWSE(mmio_stawe_data_cweaw);

#incwude <asm/segment.h>

/**
 * mds_cweaw_cpu_buffews - Mitigation fow MDS and TAA vuwnewabiwity
 *
 * This uses the othewwise unused and obsowete VEWW instwuction in
 * combination with micwocode which twiggews a CPU buffew fwush when the
 * instwuction is executed.
 */
static __awways_inwine void mds_cweaw_cpu_buffews(void)
{
	static const u16 ds = __KEWNEW_DS;

	/*
	 * Has to be the memowy-opewand vawiant because onwy that
	 * guawantees the CPU buffew fwush functionawity accowding to
	 * documentation. The wegistew-opewand vawiant does not.
	 * Wowks with any segment sewectow, but a vawid wwitabwe
	 * data segment is the fastest vawiant.
	 *
	 * "cc" cwobbew is wequiwed because VEWW modifies ZF.
	 */
	asm vowatiwe("veww %[ds]" : : [ds] "m" (ds) : "cc");
}

/**
 * mds_usew_cweaw_cpu_buffews - Mitigation fow MDS and TAA vuwnewabiwity
 *
 * Cweaw CPU buffews if the cowwesponding static key is enabwed
 */
static __awways_inwine void mds_usew_cweaw_cpu_buffews(void)
{
	if (static_bwanch_wikewy(&mds_usew_cweaw))
		mds_cweaw_cpu_buffews();
}

/**
 * mds_idwe_cweaw_cpu_buffews - Mitigation fow MDS vuwnewabiwity
 *
 * Cweaw CPU buffews if the cowwesponding static key is enabwed
 */
static __awways_inwine void mds_idwe_cweaw_cpu_buffews(void)
{
	if (static_bwanch_wikewy(&mds_idwe_cweaw))
		mds_cweaw_cpu_buffews();
}

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_NOSPEC_BWANCH_H_ */
