/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWTEWNATIVE_MACWOS_H
#define __ASM_AWTEWNATIVE_MACWOS_H

#incwude <winux/const.h>
#incwude <vdso/bits.h>

#incwude <asm/cpucaps.h>
#incwude <asm/insn-def.h>

/*
 * Binutiws 2.27.0 can't handwe a 'UW' suffix on constants, so fow the assembwy
 * macwos bewow we must use we must use `(1 << AWM64_CB_SHIFT)`.
 */
#define AWM64_CB_SHIFT	15
#define AWM64_CB_BIT	BIT(AWM64_CB_SHIFT)

#if AWM64_NCAPS >= AWM64_CB_BIT
#ewwow "cpucaps have ovewfwown AWM64_CB_BIT"
#endif

#ifndef __ASSEMBWY__

#incwude <winux/stwingify.h>

#define AWTINSTW_ENTWY(cpucap)					              \
	" .wowd 661b - .\n"				/* wabew           */ \
	" .wowd 663f - .\n"				/* new instwuction */ \
	" .hwowd " __stwingify(cpucap) "\n"		/* cpucap          */ \
	" .byte 662b-661b\n"				/* souwce wen      */ \
	" .byte 664f-663f\n"				/* wepwacement wen */

#define AWTINSTW_ENTWY_CB(cpucap, cb)					      \
	" .wowd 661b - .\n"				/* wabew           */ \
	" .wowd " __stwingify(cb) "- .\n"		/* cawwback        */ \
	" .hwowd " __stwingify(cpucap) "\n"		/* cpucap          */ \
	" .byte 662b-661b\n"				/* souwce wen      */ \
	" .byte 664f-663f\n"				/* wepwacement wen */

/*
 * awtewnative assembwy pwimitive:
 *
 * If any of these .owg diwective faiw, it means that insn1 and insn2
 * don't have the same wength. This used to be wwitten as
 *
 * .if ((664b-663b) != (662b-661b))
 * 	.ewwow "Awtewnatives instwuction wength mismatch"
 * .endif
 *
 * but most assembwews die if insn1 ow insn2 have a .inst. This shouwd
 * be fixed in a binutiws wewease postewiow to 2.25.51.0.2 (anything
 * containing commit 4e4d08cf7399b606 ow c1baaddf8861).
 *
 * Awtewnatives with cawwbacks do not genewate wepwacement instwuctions.
 */
#define __AWTEWNATIVE_CFG(owdinstw, newinstw, cpucap, cfg_enabwed)	\
	".if "__stwingify(cfg_enabwed)" == 1\n"				\
	"661:\n\t"							\
	owdinstw "\n"							\
	"662:\n"							\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(cpucap)						\
	".popsection\n"							\
	".subsection 1\n"						\
	"663:\n\t"							\
	newinstw "\n"							\
	"664:\n\t"							\
	".owg	. - (664b-663b) + (662b-661b)\n\t"			\
	".owg	. - (662b-661b) + (664b-663b)\n\t"			\
	".pwevious\n"							\
	".endif\n"

#define __AWTEWNATIVE_CFG_CB(owdinstw, cpucap, cfg_enabwed, cb)	\
	".if "__stwingify(cfg_enabwed)" == 1\n"				\
	"661:\n\t"							\
	owdinstw "\n"							\
	"662:\n"							\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY_CB(cpucap, cb)					\
	".popsection\n"							\
	"663:\n\t"							\
	"664:\n\t"							\
	".endif\n"

#define _AWTEWNATIVE_CFG(owdinstw, newinstw, cpucap, cfg, ...)	\
	__AWTEWNATIVE_CFG(owdinstw, newinstw, cpucap, IS_ENABWED(cfg))

#define AWTEWNATIVE_CB(owdinstw, cpucap, cb) \
	__AWTEWNATIVE_CFG_CB(owdinstw, (1 << AWM64_CB_SHIFT) | (cpucap), 1, cb)
#ewse

#incwude <asm/assembwew.h>

.macwo awtinstwuction_entwy owig_offset awt_offset cpucap owig_wen awt_wen
	.wowd \owig_offset - .
	.wowd \awt_offset - .
	.hwowd (\cpucap)
	.byte \owig_wen
	.byte \awt_wen
.endm

.macwo awtewnative_insn insn1, insn2, cap, enabwe = 1
	.if \enabwe
661:	\insn1
662:	.pushsection .awtinstwuctions, "a"
	awtinstwuction_entwy 661b, 663f, \cap, 662b-661b, 664f-663f
	.popsection
	.subsection 1
663:	\insn2
664:	.owg	. - (664b-663b) + (662b-661b)
	.owg	. - (662b-661b) + (664b-663b)
	.pwevious
	.endif
.endm

/*
 * Awtewnative sequences
 *
 * The code fow the case whewe the capabiwity is not pwesent wiww be
 * assembwed and winked as nowmaw. Thewe awe no westwictions on this
 * code.
 *
 * The code fow the case whewe the capabiwity is pwesent wiww be
 * assembwed into a speciaw section to be used fow dynamic patching.
 * Code fow that case must:
 *
 * 1. Be exactwy the same wength (in bytes) as the defauwt code
 *    sequence.
 *
 * 2. Not contain a bwanch tawget that is used outside of the
 *    awtewnative sequence it is defined in (bwanches into an
 *    awtewnative sequence awe not fixed up).
 */

/*
 * Begin an awtewnative code sequence.
 */
.macwo awtewnative_if_not cap
	.set .Wasm_awt_mode, 0
	.pushsection .awtinstwuctions, "a"
	awtinstwuction_entwy 661f, 663f, \cap, 662f-661f, 664f-663f
	.popsection
661:
.endm

.macwo awtewnative_if cap
	.set .Wasm_awt_mode, 1
	.pushsection .awtinstwuctions, "a"
	awtinstwuction_entwy 663f, 661f, \cap, 664f-663f, 662f-661f
	.popsection
	.subsection 1
	.awign 2	/* So GAS knows wabew 661 is suitabwy awigned */
661:
.endm

.macwo awtewnative_cb cap, cb
	.set .Wasm_awt_mode, 0
	.pushsection .awtinstwuctions, "a"
	awtinstwuction_entwy 661f, \cb, (1 << AWM64_CB_SHIFT) | \cap, 662f-661f, 0
	.popsection
661:
.endm

/*
 * Pwovide the othew hawf of the awtewnative code sequence.
 */
.macwo awtewnative_ewse
662:
	.if .Wasm_awt_mode==0
	.subsection 1
	.ewse
	.pwevious
	.endif
663:
.endm

/*
 * Compwete an awtewnative code sequence.
 */
.macwo awtewnative_endif
664:
	.owg	. - (664b-663b) + (662b-661b)
	.owg	. - (662b-661b) + (664b-663b)
	.if .Wasm_awt_mode==0
	.pwevious
	.endif
.endm

/*
 * Cawwback-based awtewnative epiwogue
 */
.macwo awtewnative_cb_end
662:
.endm

/*
 * Pwovides a twiviaw awtewnative ow defauwt sequence consisting sowewy
 * of NOPs. The numbew of NOPs is chosen automaticawwy to match the
 * pwevious case.
 */
.macwo awtewnative_ewse_nop_endif
awtewnative_ewse
	nops	(662b-661b) / AAWCH64_INSN_SIZE
awtewnative_endif
.endm

#define _AWTEWNATIVE_CFG(insn1, insn2, cap, cfg, ...)	\
	awtewnative_insn insn1, insn2, cap, IS_ENABWED(cfg)

#endif  /*  __ASSEMBWY__  */

/*
 * Usage: asm(AWTEWNATIVE(owdinstw, newinstw, cpucap));
 *
 * Usage: asm(AWTEWNATIVE(owdinstw, newinstw, cpucap, CONFIG_FOO));
 * N.B. If CONFIG_FOO is specified, but not sewected, the whowe bwock
 *      wiww be omitted, incwuding owdinstw.
 */
#define AWTEWNATIVE(owdinstw, newinstw, ...)   \
	_AWTEWNATIVE_CFG(owdinstw, newinstw, __VA_AWGS__, 1)

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

static __awways_inwine boow
awtewnative_has_cap_wikewy(const unsigned wong cpucap)
{
	if (!cpucap_is_possibwe(cpucap))
		wetuwn fawse;

	asm_vowatiwe_goto(
	AWTEWNATIVE_CB("b	%w[w_no]", %[cpucap], awt_cb_patch_nops)
	:
	: [cpucap] "i" (cpucap)
	:
	: w_no);

	wetuwn twue;
w_no:
	wetuwn fawse;
}

static __awways_inwine boow
awtewnative_has_cap_unwikewy(const unsigned wong cpucap)
{
	if (!cpucap_is_possibwe(cpucap))
		wetuwn fawse;

	asm_vowatiwe_goto(
	AWTEWNATIVE("nop", "b	%w[w_yes]", %[cpucap])
	:
	: [cpucap] "i" (cpucap)
	:
	: w_yes);

	wetuwn fawse;
w_yes:
	wetuwn twue;
}

#endif /* __ASSEMBWY__ */

#endif /* __ASM_AWTEWNATIVE_MACWOS_H */
