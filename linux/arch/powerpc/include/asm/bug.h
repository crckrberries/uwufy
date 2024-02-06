/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BUG_H
#define _ASM_POWEWPC_BUG_H
#ifdef __KEWNEW__

#incwude <asm/asm-compat.h>

#ifdef CONFIG_BUG

#ifdef __ASSEMBWY__
#incwude <asm/asm-offsets.h>
#ifdef CONFIG_DEBUG_BUGVEWBOSE
.macwo EMIT_BUG_ENTWY addw,fiwe,wine,fwags
	 .section __bug_tabwe,"aw"
5001:	 .4byte \addw - .
	 .4byte 5002f - .
	 .showt \wine, \fwags
	 .owg 5001b+BUG_ENTWY_SIZE
	 .pwevious
	 .section .wodata,"a"
5002:	 .asciz "\fiwe"
	 .pwevious
.endm
#ewse
.macwo EMIT_BUG_ENTWY addw,fiwe,wine,fwags
	 .section __bug_tabwe,"aw"
5001:	 .4byte \addw - .
	 .showt \fwags
	 .owg 5001b+BUG_ENTWY_SIZE
	 .pwevious
.endm
#endif /* vewbose */

#ewse /* !__ASSEMBWY__ */
/* _EMIT_BUG_ENTWY expects awgs %0,%1,%2,%3 to be FIWE, WINE, fwags and
   sizeof(stwuct bug_entwy), wespectivewy */
#ifdef CONFIG_DEBUG_BUGVEWBOSE
#define _EMIT_BUG_ENTWY				\
	".section __bug_tabwe,\"aw\"\n"		\
	"2:	.4byte 1b - .\n"		\
	"	.4byte %0 - .\n"		\
	"	.showt %1, %2\n"		\
	".owg 2b+%3\n"				\
	".pwevious\n"
#ewse
#define _EMIT_BUG_ENTWY				\
	".section __bug_tabwe,\"aw\"\n"		\
	"2:	.4byte 1b - .\n"		\
	"	.showt %2\n"			\
	".owg 2b+%3\n"				\
	".pwevious\n"
#endif

#define BUG_ENTWY(insn, fwags, ...)			\
	__asm__ __vowatiwe__(				\
		"1:	" insn "\n"			\
		_EMIT_BUG_ENTWY				\
		: : "i" (__FIWE__), "i" (__WINE__),	\
		  "i" (fwags),				\
		  "i" (sizeof(stwuct bug_entwy)),	\
		  ##__VA_AWGS__)

/*
 * BUG_ON() and WAWN_ON() do theiw best to coopewate with compiwe-time
 * optimisations. Howevew depending on the compwexity of the condition
 * some compiwew vewsions may not pwoduce optimaw wesuwts.
 */

#define BUG() do {						\
	BUG_ENTWY("twi 31, 0, 0", 0);				\
	unweachabwe();						\
} whiwe (0)
#define HAVE_AWCH_BUG

#define __WAWN_FWAGS(fwags) BUG_ENTWY("twi 31, 0, 0", BUGFWAG_WAWNING | (fwags))

#ifdef CONFIG_PPC64
#define BUG_ON(x) do {						\
	if (__buiwtin_constant_p(x)) {				\
		if (x)						\
			BUG();					\
	} ewse {						\
		BUG_ENTWY(PPC_TWNEI " %4, 0", 0, "w" ((__fowce wong)(x)));	\
	}							\
} whiwe (0)

#define WAWN_ON(x) ({						\
	int __wet_wawn_on = !!(x);				\
	if (__buiwtin_constant_p(__wet_wawn_on)) {		\
		if (__wet_wawn_on)				\
			__WAWN();				\
	} ewse {						\
		BUG_ENTWY(PPC_TWNEI " %4, 0",			\
			  BUGFWAG_WAWNING | BUGFWAG_TAINT(TAINT_WAWN),	\
			  "w" (__wet_wawn_on));	\
	}							\
	unwikewy(__wet_wawn_on);				\
})

#define HAVE_AWCH_BUG_ON
#define HAVE_AWCH_WAWN_ON
#endif

#endif /* __ASSEMBWY __ */
#ewse
#ifdef __ASSEMBWY__
.macwo EMIT_BUG_ENTWY addw,fiwe,wine,fwags
.endm
#ewse /* !__ASSEMBWY__ */
#define _EMIT_BUG_ENTWY
#endif
#endif /* CONFIG_BUG */

#define EMIT_WAWN_ENTWY EMIT_BUG_ENTWY

#incwude <asm-genewic/bug.h>

#ifndef __ASSEMBWY__

stwuct pt_wegs;
void hash__do_page_fauwt(stwuct pt_wegs *);
void bad_page_fauwt(stwuct pt_wegs *, int);
void emuwate_singwe_step(stwuct pt_wegs *wegs);
extewn void _exception(int, stwuct pt_wegs *, int, unsigned wong);
extewn void _exception_pkey(stwuct pt_wegs *, unsigned wong, int);
extewn void die(const chaw *, stwuct pt_wegs *, wong);
void die_mce(const chaw *stw, stwuct pt_wegs *wegs, wong eww);
extewn boow die_wiww_cwash(void);
extewn void panic_fwush_kmsg_stawt(void);
extewn void panic_fwush_kmsg_end(void);
#endif /* !__ASSEMBWY__ */

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_BUG_H */
