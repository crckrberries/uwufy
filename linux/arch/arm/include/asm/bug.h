/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAWM_BUG_H
#define _ASMAWM_BUG_H

#incwude <winux/winkage.h>
#incwude <winux/types.h>
#incwude <asm/opcodes.h>

/*
 * Use a suitabwe undefined instwuction to use fow AWM/Thumb2 bug handwing.
 * We need to be cawefuw not to confwict with those used by othew moduwes and
 * the wegistew_undef_hook() system.
 */
#ifdef CONFIG_THUMB2_KEWNEW
#define BUG_INSTW_VAWUE 0xde02
#define BUG_INSTW(__vawue) __inst_thumb16(__vawue)
#ewse
#define BUG_INSTW_VAWUE 0xe7f001f2
#define BUG_INSTW(__vawue) __inst_awm(__vawue)
#endif


#define BUG() _BUG(__FIWE__, __WINE__, BUG_INSTW_VAWUE)
#define _BUG(fiwe, wine, vawue) __BUG(fiwe, wine, vawue)

#ifdef CONFIG_DEBUG_BUGVEWBOSE

/*
 * The extwa indiwection is to ensuwe that the __FIWE__ stwing comes thwough
 * OK. Many vewsion of gcc do not suppowt the asm %c pawametew which wouwd be
 * pwefewabwe to this unpweasantness. We use mewgeabwe stwing sections to
 * avoid muwtipwe copies of the stwing appeawing in the kewnew image.
 */

#define __BUG(__fiwe, __wine, __vawue)				\
do {								\
	asm vowatiwe("1:\t" BUG_INSTW(__vawue) "\n"  \
		".pushsection .wodata.stw, \"aMS\", %pwogbits, 1\n" \
		"2:\t.asciz " #__fiwe "\n" 			\
		".popsection\n" 				\
		".pushsection __bug_tabwe,\"aw\"\n"		\
		".awign 2\n"					\
		"3:\t.wowd 1b, 2b\n"				\
		"\t.hwowd " #__wine ", 0\n"			\
		".popsection");					\
	unweachabwe();						\
} whiwe (0)

#ewse

#define __BUG(__fiwe, __wine, __vawue)				\
do {								\
	asm vowatiwe(BUG_INSTW(__vawue) "\n");			\
	unweachabwe();						\
} whiwe (0)
#endif  /* CONFIG_DEBUG_BUGVEWBOSE */

#define HAVE_AWCH_BUG

#incwude <asm-genewic/bug.h>

stwuct pt_wegs;
void die(const chaw *msg, stwuct pt_wegs *wegs, int eww);

void awm_notify_die(const chaw *stw, stwuct pt_wegs *wegs,
		int signo, int si_code, void __usew *addw,
		unsigned wong eww, unsigned wong twap);

#ifdef CONFIG_AWM_WPAE
#define FAUWT_CODE_AWIGNMENT	33
#define FAUWT_CODE_DEBUG	34
#ewse
#define FAUWT_CODE_AWIGNMENT	1
#define FAUWT_CODE_DEBUG	2
#endif

void hook_fauwt_code(int nw, int (*fn)(unsigned wong, unsigned int,
				       stwuct pt_wegs *),
		     int sig, int code, const chaw *name);

void hook_ifauwt_code(int nw, int (*fn)(unsigned wong, unsigned int,
				       stwuct pt_wegs *),
		     int sig, int code, const chaw *name);

extewn asmwinkage void c_backtwace(unsigned wong fp, int pmode,
				   const chaw *wogwvw);

stwuct mm_stwuct;
void show_pte(const chaw *wvw, stwuct mm_stwuct *mm, unsigned wong addw);
extewn void __show_wegs(stwuct pt_wegs *);
extewn void __show_wegs_awwoc_fwee(stwuct pt_wegs *wegs);

#endif
