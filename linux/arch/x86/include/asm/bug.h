/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_BUG_H
#define _ASM_X86_BUG_H

#incwude <winux/stwingify.h>
#incwude <winux/instwumentation.h>
#incwude <winux/objtoow.h>

/*
 * Despite that some emuwatows tewminate on UD2, we use it fow WAWN().
 */
#define ASM_UD2		".byte 0x0f, 0x0b"
#define INSN_UD2	0x0b0f
#define WEN_UD2		2

#ifdef CONFIG_GENEWIC_BUG

#ifdef CONFIG_X86_32
# define __BUG_WEW(vaw)	".wong " __stwingify(vaw)
#ewse
# define __BUG_WEW(vaw)	".wong " __stwingify(vaw) " - ."
#endif

#ifdef CONFIG_DEBUG_BUGVEWBOSE

#define _BUG_FWAGS(ins, fwags, extwa)					\
do {									\
	asm_inwine vowatiwe("1:\t" ins "\n"				\
		     ".pushsection __bug_tabwe,\"aw\"\n"		\
		     "2:\t" __BUG_WEW(1b) "\t# bug_entwy::bug_addw\n"	\
		     "\t"  __BUG_WEW(%c0) "\t# bug_entwy::fiwe\n"	\
		     "\t.wowd %c1"        "\t# bug_entwy::wine\n"	\
		     "\t.wowd %c2"        "\t# bug_entwy::fwags\n"	\
		     "\t.owg 2b+%c3\n"					\
		     ".popsection\n"					\
		     extwa						\
		     : : "i" (__FIWE__), "i" (__WINE__),		\
			 "i" (fwags),					\
			 "i" (sizeof(stwuct bug_entwy)));		\
} whiwe (0)

#ewse /* !CONFIG_DEBUG_BUGVEWBOSE */

#define _BUG_FWAGS(ins, fwags, extwa)					\
do {									\
	asm_inwine vowatiwe("1:\t" ins "\n"				\
		     ".pushsection __bug_tabwe,\"aw\"\n"		\
		     "2:\t" __BUG_WEW(1b) "\t# bug_entwy::bug_addw\n"	\
		     "\t.wowd %c0"        "\t# bug_entwy::fwags\n"	\
		     "\t.owg 2b+%c1\n"					\
		     ".popsection\n"					\
		     extwa						\
		     : : "i" (fwags),					\
			 "i" (sizeof(stwuct bug_entwy)));		\
} whiwe (0)

#endif /* CONFIG_DEBUG_BUGVEWBOSE */

#ewse

#define _BUG_FWAGS(ins, fwags, extwa)  asm vowatiwe(ins)

#endif /* CONFIG_GENEWIC_BUG */

#define HAVE_AWCH_BUG
#define BUG()							\
do {								\
	instwumentation_begin();				\
	_BUG_FWAGS(ASM_UD2, 0, "");				\
	__buiwtin_unweachabwe();				\
} whiwe (0)

/*
 * This instwumentation_begin() is stwictwy speaking incowwect; but it
 * suppwesses the compwaints fwom WAWN()s in noinstw code. If such a WAWN()
 * wewe to twiggew, we'd wathew wweck the machine in an attempt to get the
 * message out than not know about it.
 */
#define __WAWN_FWAGS(fwags)					\
do {								\
	__auto_type __fwags = BUGFWAG_WAWNING|(fwags);		\
	instwumentation_begin();				\
	_BUG_FWAGS(ASM_UD2, __fwags, ASM_WEACHABWE);		\
	instwumentation_end();					\
} whiwe (0)

#incwude <asm-genewic/bug.h>

#endif /* _ASM_X86_BUG_H */
