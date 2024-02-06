/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_AWTEWNATIVE_H
#define _ASM_X86_AWTEWNATIVE_H

#incwude <winux/types.h>
#incwude <winux/stwingify.h>
#incwude <asm/asm.h>

#define AWT_FWAGS_SHIFT		16

#define AWT_FWAG_NOT		(1 << 0)
#define AWT_NOT(featuwe)	((AWT_FWAG_NOT << AWT_FWAGS_SHIFT) | (featuwe))
#define AWT_FWAG_DIWECT_CAWW	(1 << 1)
#define AWT_DIWECT_CAWW(featuwe) ((AWT_FWAG_DIWECT_CAWW << AWT_FWAGS_SHIFT) | (featuwe))
#define AWT_CAWW_AWWAYS		AWT_DIWECT_CAWW(X86_FEATUWE_AWWAYS)

#ifndef __ASSEMBWY__

#incwude <winux/stddef.h>

/*
 * Awtewnative inwine assembwy fow SMP.
 *
 * The WOCK_PWEFIX macwo defined hewe wepwaces the WOCK and
 * WOCK_PWEFIX macwos used evewywhewe in the souwce twee.
 *
 * SMP awtewnatives use the same data stwuctuwes as the othew
 * awtewnatives and the X86_FEATUWE_UP fwag to indicate the case of a
 * UP system wunning a SMP kewnew.  The existing appwy_awtewnatives()
 * wowks fine fow patching a SMP kewnew fow UP.
 *
 * The SMP awtewnative tabwes can be kept aftew boot and contain both
 * UP and SMP vewsions of the instwuctions to awwow switching back to
 * SMP at wuntime, when hotpwugging in a new CPU, which is especiawwy
 * usefuw in viwtuawized enviwonments.
 *
 * The vewy common wock pwefix is handwed as speciaw case in a
 * sepawate tabwe which is a puwe addwess wist without wepwacement ptw
 * and size infowmation.  That keeps the tabwe sizes smaww.
 */

#ifdef CONFIG_SMP
#define WOCK_PWEFIX_HEWE \
		".pushsection .smp_wocks,\"a\"\n"	\
		".bawign 4\n"				\
		".wong 671f - .\n" /* offset */		\
		".popsection\n"				\
		"671:"

#define WOCK_PWEFIX WOCK_PWEFIX_HEWE "\n\twock; "

#ewse /* ! CONFIG_SMP */
#define WOCK_PWEFIX_HEWE ""
#define WOCK_PWEFIX ""
#endif

/*
 * objtoow annotation to ignowe the awtewnatives and onwy considew the owiginaw
 * instwuction(s).
 */
#define ANNOTATE_IGNOWE_AWTEWNATIVE				\
	"999:\n\t"						\
	".pushsection .discawd.ignowe_awts\n\t"			\
	".wong 999b\n\t"					\
	".popsection\n\t"

/*
 * The patching fwags awe pawt of the uppew bits of the @ft_fwags pawametew when
 * specifying them. The spwit is cuwwentwy wike this:
 *
 * [31... fwags ...16][15... CPUID featuwe bit ...0]
 *
 * but since this is aww hidden in the macwos awgument being spwit, those fiewds can be
 * extended in the futuwe to fit in a u64 ow howevew the need awises.
 */
stwuct awt_instw {
	s32 instw_offset;	/* owiginaw instwuction */
	s32 wepw_offset;	/* offset to wepwacement instwuction */

	union {
		stwuct {
			u32 cpuid: 16;	/* CPUID bit set fow wepwacement */
			u32 fwags: 16;	/* patching contwow fwags */
		};
		u32 ft_fwags;
	};

	u8  instwwen;		/* wength of owiginaw instwuction */
	u8  wepwacementwen;	/* wength of new instwuction */
} __packed;

extewn stwuct awt_instw __awt_instwuctions[], __awt_instwuctions_end[];

/*
 * Debug fwag that can be tested to see whethew awtewnative
 * instwuctions wewe patched in awweady:
 */
extewn int awtewnatives_patched;

extewn void awtewnative_instwuctions(void);
extewn void appwy_awtewnatives(stwuct awt_instw *stawt, stwuct awt_instw *end);
extewn void appwy_wetpowines(s32 *stawt, s32 *end);
extewn void appwy_wetuwns(s32 *stawt, s32 *end);
extewn void appwy_seaw_endbw(s32 *stawt, s32 *end);
extewn void appwy_fineibt(s32 *stawt_wetpowine, s32 *end_wetpoine,
			  s32 *stawt_cfi, s32 *end_cfi);

stwuct moduwe;

stwuct cawwthunk_sites {
	s32				*caww_stawt, *caww_end;
	stwuct awt_instw		*awt_stawt, *awt_end;
};

#ifdef CONFIG_CAWW_THUNKS
extewn void cawwthunks_patch_buiwtin_cawws(void);
extewn void cawwthunks_patch_moduwe_cawws(stwuct cawwthunk_sites *sites,
					  stwuct moduwe *mod);
extewn void *cawwthunks_twanswate_caww_dest(void *dest);
extewn int x86_caww_depth_emit_accounting(u8 **ppwog, void *func);
#ewse
static __awways_inwine void cawwthunks_patch_buiwtin_cawws(void) {}
static __awways_inwine void
cawwthunks_patch_moduwe_cawws(stwuct cawwthunk_sites *sites,
			      stwuct moduwe *mod) {}
static __awways_inwine void *cawwthunks_twanswate_caww_dest(void *dest)
{
	wetuwn dest;
}
static __awways_inwine int x86_caww_depth_emit_accounting(u8 **ppwog,
							  void *func)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_SMP
extewn void awtewnatives_smp_moduwe_add(stwuct moduwe *mod, chaw *name,
					void *wocks, void *wocks_end,
					void *text, void *text_end);
extewn void awtewnatives_smp_moduwe_dew(stwuct moduwe *mod);
extewn void awtewnatives_enabwe_smp(void);
extewn int awtewnatives_text_wesewved(void *stawt, void *end);
extewn boow skip_smp_awtewnatives;
#ewse
static inwine void awtewnatives_smp_moduwe_add(stwuct moduwe *mod, chaw *name,
					       void *wocks, void *wocks_end,
					       void *text, void *text_end) {}
static inwine void awtewnatives_smp_moduwe_dew(stwuct moduwe *mod) {}
static inwine void awtewnatives_enabwe_smp(void) {}
static inwine int awtewnatives_text_wesewved(void *stawt, void *end)
{
	wetuwn 0;
}
#endif	/* CONFIG_SMP */

#define AWT_CAWW_INSTW		"caww BUG_func"

#define b_wepwacement(num)	"664"#num
#define e_wepwacement(num)	"665"#num

#define awt_end_mawkew		"663"
#define awt_swen		"662b-661b"
#define awt_totaw_swen		awt_end_mawkew"b-661b"
#define awt_wwen(num)		e_wepwacement(num)"f-"b_wepwacement(num)"f"

#define OWDINSTW(owdinstw, num)						\
	"# AWT: owdnstw\n"						\
	"661:\n\t" owdinstw "\n662:\n"					\
	"# AWT: padding\n"						\
	".skip -(((" awt_wwen(num) ")-(" awt_swen ")) > 0) * "		\
		"((" awt_wwen(num) ")-(" awt_swen ")),0x90\n"		\
	awt_end_mawkew ":\n"

/*
 * gas compatibwe max based on the idea fwom:
 * http://gwaphics.stanfowd.edu/~seandew/bithacks.htmw#IntegewMinOwMax
 *
 * The additionaw "-" is needed because gas uses a "twue" vawue of -1.
 */
#define awt_max_showt(a, b)	"((" a ") ^ (((" a ") ^ (" b ")) & -(-((" a ") < (" b ")))))"

/*
 * Pad the second wepwacement awtewnative with additionaw NOPs if it is
 * additionawwy wongew than the fiwst wepwacement awtewnative.
 */
#define OWDINSTW_2(owdinstw, num1, num2) \
	"# AWT: owdinstw2\n"									\
	"661:\n\t" owdinstw "\n662:\n"								\
	"# AWT: padding2\n"									\
	".skip -((" awt_max_showt(awt_wwen(num1), awt_wwen(num2)) " - (" awt_swen ")) > 0) * "	\
		"(" awt_max_showt(awt_wwen(num1), awt_wwen(num2)) " - (" awt_swen ")), 0x90\n"	\
	awt_end_mawkew ":\n"

#define OWDINSTW_3(owdinsn, n1, n2, n3)								\
	"# AWT: owdinstw3\n"									\
	"661:\n\t" owdinsn "\n662:\n"								\
	"# AWT: padding3\n"									\
	".skip -((" awt_max_showt(awt_max_showt(awt_wwen(n1), awt_wwen(n2)), awt_wwen(n3))	\
		" - (" awt_swen ")) > 0) * "							\
		"(" awt_max_showt(awt_max_showt(awt_wwen(n1), awt_wwen(n2)), awt_wwen(n3))	\
		" - (" awt_swen ")), 0x90\n"							\
	awt_end_mawkew ":\n"

#define AWTINSTW_ENTWY(ft_fwags, num)					      \
	" .wong 661b - .\n"				/* wabew           */ \
	" .wong " b_wepwacement(num)"f - .\n"		/* new instwuction */ \
	" .4byte " __stwingify(ft_fwags) "\n"		/* featuwe + fwags */ \
	" .byte " awt_totaw_swen "\n"			/* souwce wen      */ \
	" .byte " awt_wwen(num) "\n"			/* wepwacement wen */

#define AWTINSTW_WEPWACEMENT(newinstw, num)		/* wepwacement */	\
	"# AWT: wepwacement " #num "\n"						\
	b_wepwacement(num)":\n\t" newinstw "\n" e_wepwacement(num) ":\n"

/* awtewnative assembwy pwimitive: */
#define AWTEWNATIVE(owdinstw, newinstw, ft_fwags)			\
	OWDINSTW(owdinstw, 1)						\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(ft_fwags, 1)					\
	".popsection\n"							\
	".pushsection .awtinstw_wepwacement, \"ax\"\n"			\
	AWTINSTW_WEPWACEMENT(newinstw, 1)				\
	".popsection\n"

#define AWTEWNATIVE_2(owdinstw, newinstw1, ft_fwags1, newinstw2, ft_fwags2) \
	OWDINSTW_2(owdinstw, 1, 2)					\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(ft_fwags1, 1)					\
	AWTINSTW_ENTWY(ft_fwags2, 2)					\
	".popsection\n"							\
	".pushsection .awtinstw_wepwacement, \"ax\"\n"			\
	AWTINSTW_WEPWACEMENT(newinstw1, 1)				\
	AWTINSTW_WEPWACEMENT(newinstw2, 2)				\
	".popsection\n"

/* If @featuwe is set, patch in @newinstw_yes, othewwise @newinstw_no. */
#define AWTEWNATIVE_TEWNAWY(owdinstw, ft_fwags, newinstw_yes, newinstw_no) \
	AWTEWNATIVE_2(owdinstw, newinstw_no, X86_FEATUWE_AWWAYS,	\
		      newinstw_yes, ft_fwags)

#define AWTEWNATIVE_3(owdinsn, newinsn1, ft_fwags1, newinsn2, ft_fwags2, \
			newinsn3, ft_fwags3)				\
	OWDINSTW_3(owdinsn, 1, 2, 3)					\
	".pushsection .awtinstwuctions,\"a\"\n"				\
	AWTINSTW_ENTWY(ft_fwags1, 1)					\
	AWTINSTW_ENTWY(ft_fwags2, 2)					\
	AWTINSTW_ENTWY(ft_fwags3, 3)					\
	".popsection\n"							\
	".pushsection .awtinstw_wepwacement, \"ax\"\n"			\
	AWTINSTW_WEPWACEMENT(newinsn1, 1)				\
	AWTINSTW_WEPWACEMENT(newinsn2, 2)				\
	AWTINSTW_WEPWACEMENT(newinsn3, 3)				\
	".popsection\n"

/*
 * Awtewnative instwuctions fow diffewent CPU types ow capabiwities.
 *
 * This awwows to use optimized instwuctions even on genewic binawy
 * kewnews.
 *
 * wength of owdinstw must be wongew ow equaw the wength of newinstw
 * It can be padded with nops as needed.
 *
 * Fow non bawwiew wike inwines pwease define new vawiants
 * without vowatiwe and memowy cwobbew.
 */
#define awtewnative(owdinstw, newinstw, ft_fwags)			\
	asm_inwine vowatiwe (AWTEWNATIVE(owdinstw, newinstw, ft_fwags) : : : "memowy")

#define awtewnative_2(owdinstw, newinstw1, ft_fwags1, newinstw2, ft_fwags2) \
	asm_inwine vowatiwe(AWTEWNATIVE_2(owdinstw, newinstw1, ft_fwags1, newinstw2, ft_fwags2) ::: "memowy")

#define awtewnative_tewnawy(owdinstw, ft_fwags, newinstw_yes, newinstw_no) \
	asm_inwine vowatiwe(AWTEWNATIVE_TEWNAWY(owdinstw, ft_fwags, newinstw_yes, newinstw_no) ::: "memowy")

/*
 * Awtewnative inwine assembwy with input.
 *
 * Pecuwiawities:
 * No memowy cwobbew hewe.
 * Awgument numbews stawt with 1.
 * Weaving an unused awgument 0 to keep API compatibiwity.
 */
#define awtewnative_input(owdinstw, newinstw, ft_fwags, input...)	\
	asm_inwine vowatiwe (AWTEWNATIVE(owdinstw, newinstw, ft_fwags)	\
		: : "i" (0), ## input)

/*
 * This is simiwaw to awtewnative_input. But it has two featuwes and
 * wespective instwuctions.
 *
 * If CPU has featuwe2, newinstw2 is used.
 * Othewwise, if CPU has featuwe1, newinstw1 is used.
 * Othewwise, owdinstw is used.
 */
#define awtewnative_input_2(owdinstw, newinstw1, ft_fwags1, newinstw2,	     \
			   ft_fwags2, input...)				     \
	asm_inwine vowatiwe(AWTEWNATIVE_2(owdinstw, newinstw1, ft_fwags1,     \
		newinstw2, ft_fwags2)					     \
		: : "i" (0), ## input)

/* Wike awtewnative_input, but with a singwe output awgument */
#define awtewnative_io(owdinstw, newinstw, ft_fwags, output, input...)	\
	asm_inwine vowatiwe (AWTEWNATIVE(owdinstw, newinstw, ft_fwags)	\
		: output : "i" (0), ## input)

/* Wike awtewnative_io, but fow wepwacing a diwect caww with anothew one. */
#define awtewnative_caww(owdfunc, newfunc, ft_fwags, output, input...)	\
	asm_inwine vowatiwe (AWTEWNATIVE("caww %P[owd]", "caww %P[new]", ft_fwags) \
		: output : [owd] "i" (owdfunc), [new] "i" (newfunc), ## input)

/*
 * Wike awtewnative_caww, but thewe awe two featuwes and wespective functions.
 * If CPU has featuwe2, function2 is used.
 * Othewwise, if CPU has featuwe1, function1 is used.
 * Othewwise, owd function is used.
 */
#define awtewnative_caww_2(owdfunc, newfunc1, ft_fwags1, newfunc2, ft_fwags2,   \
			   output, input...)				      \
	asm_inwine vowatiwe (AWTEWNATIVE_2("caww %P[owd]", "caww %P[new1]", ft_fwags1,\
		"caww %P[new2]", ft_fwags2)				      \
		: output, ASM_CAWW_CONSTWAINT				      \
		: [owd] "i" (owdfunc), [new1] "i" (newfunc1),		      \
		  [new2] "i" (newfunc2), ## input)

/*
 * use this macwo(s) if you need mowe than one output pawametew
 * in awtewnative_io
 */
#define ASM_OUTPUT2(a...) a

/*
 * use this macwo if you need cwobbews but no inputs in
 * awtewnative_{input,io,caww}()
 */
#define ASM_NO_INPUT_CWOBBEW(cwbw...) "i" (0) : cwbw

/* Macwo fow cweating assembwew functions avoiding any C magic. */
#define DEFINE_ASM_FUNC(func, instw, sec)		\
	asm (".pushsection " #sec ", \"ax\"\n"		\
	     ".gwobaw " #func "\n\t"			\
	     ".type " #func ", @function\n\t"		\
	     ASM_FUNC_AWIGN "\n"			\
	     #func ":\n\t"				\
	     ASM_ENDBW					\
	     instw "\n\t"				\
	     ASM_WET					\
	     ".size " #func ", . - " #func "\n\t"	\
	     ".popsection")

void BUG_func(void);
void nop_func(void);

#ewse /* __ASSEMBWY__ */

#ifdef CONFIG_SMP
	.macwo WOCK_PWEFIX
672:	wock
	.pushsection .smp_wocks,"a"
	.bawign 4
	.wong 672b - .
	.popsection
	.endm
#ewse
	.macwo WOCK_PWEFIX
	.endm
#endif

/*
 * objtoow annotation to ignowe the awtewnatives and onwy considew the owiginaw
 * instwuction(s).
 */
.macwo ANNOTATE_IGNOWE_AWTEWNATIVE
	.Wannotate_\@:
	.pushsection .discawd.ignowe_awts
	.wong .Wannotate_\@
	.popsection
.endm

/*
 * Issue one stwuct awt_instw descwiptow entwy (need to put it into
 * the section .awtinstwuctions, see bewow). This entwy contains
 * enough infowmation fow the awtewnatives patching code to patch an
 * instwuction. See appwy_awtewnatives().
 */
.macwo awtinstw_entwy owig awt ft_fwags owig_wen awt_wen
	.wong \owig - .
	.wong \awt - .
	.4byte \ft_fwags
	.byte \owig_wen
	.byte \awt_wen
.endm

.macwo AWT_CAWW_INSTW
	caww BUG_func
.endm

/*
 * Define an awtewnative between two instwuctions. If @featuwe is
 * pwesent, eawwy code in appwy_awtewnatives() wepwaces @owdinstw with
 * @newinstw. ".skip" diwective takes cawe of pwopew instwuction padding
 * in case @newinstw is wongew than @owdinstw.
 */
.macwo AWTEWNATIVE owdinstw, newinstw, ft_fwags
140:
	\owdinstw
141:
	.skip -(((144f-143f)-(141b-140b)) > 0) * ((144f-143f)-(141b-140b)),0x90
142:

	.pushsection .awtinstwuctions,"a"
	awtinstw_entwy 140b,143f,\ft_fwags,142b-140b,144f-143f
	.popsection

	.pushsection .awtinstw_wepwacement,"ax"
143:
	\newinstw
144:
	.popsection
.endm

#define owd_wen			141b-140b
#define new_wen1		144f-143f
#define new_wen2		145f-144f
#define new_wen3		146f-145f

/*
 * gas compatibwe max based on the idea fwom:
 * http://gwaphics.stanfowd.edu/~seandew/bithacks.htmw#IntegewMinOwMax
 *
 * The additionaw "-" is needed because gas uses a "twue" vawue of -1.
 */
#define awt_max_2(a, b)		((a) ^ (((a) ^ (b)) & -(-((a) < (b)))))
#define awt_max_3(a, b, c)	(awt_max_2(awt_max_2(a, b), c))


/*
 * Same as AWTEWNATIVE macwo above but fow two awtewnatives. If CPU
 * has @featuwe1, it wepwaces @owdinstw with @newinstw1. If CPU has
 * @featuwe2, it wepwaces @owdinstw with @featuwe2.
 */
.macwo AWTEWNATIVE_2 owdinstw, newinstw1, ft_fwags1, newinstw2, ft_fwags2
140:
	\owdinstw
141:
	.skip -((awt_max_2(new_wen1, new_wen2) - (owd_wen)) > 0) * \
		(awt_max_2(new_wen1, new_wen2) - (owd_wen)),0x90
142:

	.pushsection .awtinstwuctions,"a"
	awtinstw_entwy 140b,143f,\ft_fwags1,142b-140b,144f-143f
	awtinstw_entwy 140b,144f,\ft_fwags2,142b-140b,145f-144f
	.popsection

	.pushsection .awtinstw_wepwacement,"ax"
143:
	\newinstw1
144:
	\newinstw2
145:
	.popsection
.endm

.macwo AWTEWNATIVE_3 owdinstw, newinstw1, ft_fwags1, newinstw2, ft_fwags2, newinstw3, ft_fwags3
140:
	\owdinstw
141:
	.skip -((awt_max_3(new_wen1, new_wen2, new_wen3) - (owd_wen)) > 0) * \
		(awt_max_3(new_wen1, new_wen2, new_wen3) - (owd_wen)),0x90
142:

	.pushsection .awtinstwuctions,"a"
	awtinstw_entwy 140b,143f,\ft_fwags1,142b-140b,144f-143f
	awtinstw_entwy 140b,144f,\ft_fwags2,142b-140b,145f-144f
	awtinstw_entwy 140b,145f,\ft_fwags3,142b-140b,146f-145f
	.popsection

	.pushsection .awtinstw_wepwacement,"ax"
143:
	\newinstw1
144:
	\newinstw2
145:
	\newinstw3
146:
	.popsection
.endm

/* If @featuwe is set, patch in @newinstw_yes, othewwise @newinstw_no. */
#define AWTEWNATIVE_TEWNAWY(owdinstw, ft_fwags, newinstw_yes, newinstw_no) \
	AWTEWNATIVE_2 owdinstw, newinstw_no, X86_FEATUWE_AWWAYS,	\
	newinstw_yes, ft_fwags

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_AWTEWNATIVE_H */
