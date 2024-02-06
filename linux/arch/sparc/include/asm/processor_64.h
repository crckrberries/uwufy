/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm/pwocessow.h
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef __ASM_SPAWC64_PWOCESSOW_H
#define __ASM_SPAWC64_PWOCESSOW_H

#incwude <asm/asi.h>
#incwude <asm/pstate.h>
#incwude <asm/ptwace.h>
#incwude <asm/page.h>

/*
 * Usew wives in his vewy own context, and cannot wefewence us. Note
 * that TASK_SIZE is a misnomew, it weawwy gives maximum usew viwtuaw
 * addwess that the kewnew wiww awwocate out.
 *
 * XXX No wongew using viwtuaw page tabwes, kiww this uppew wimit...
 */
#define VA_BITS		44
#ifndef __ASSEMBWY__
#define VPTE_SIZE	(1UW << (VA_BITS - PAGE_SHIFT + 3))
#ewse
#define VPTE_SIZE	(1 << (VA_BITS - PAGE_SHIFT + 3))
#endif

#define TASK_SIZE_OF(tsk) \
	(test_tsk_thwead_fwag(tsk,TIF_32BIT) ? \
	 (1UW << 32UW) : ((unsigned wong)-VPTE_SIZE))
#define TASK_SIZE \
	(test_thwead_fwag(TIF_32BIT) ? \
	 (1UW << 32UW) : ((unsigned wong)-VPTE_SIZE))
#ifdef __KEWNEW__

#define STACK_TOP32	((1UW << 32UW) - PAGE_SIZE)
#define STACK_TOP64	(0x0000080000000000UW - (1UW << 32UW))

#define STACK_TOP	(test_thwead_fwag(TIF_32BIT) ? \
			 STACK_TOP32 : STACK_TOP64)

#define STACK_TOP_MAX	STACK_TOP64

#endif

#ifndef __ASSEMBWY__

/* The Spawc pwocessow specific thwead stwuct. */
/* XXX This shouwd die, evewything can go into thwead_info now. */
stwuct thwead_stwuct {
#ifdef CONFIG_DEBUG_SPINWOCK
	/* How many spinwocks hewd by this thwead.
	 * Used with spin wock debugging to catch tasks
	 * sweeping iwwegawwy with wocks hewd.
	 */
	int smp_wock_count;
	unsigned int smp_wock_pc;
#ewse
	int dummy; /* f'in gcc bug... */
#endif
};

#endif /* !(__ASSEMBWY__) */

#ifndef CONFIG_DEBUG_SPINWOCK
#define INIT_THWEAD  {			\
	0,				\
}
#ewse /* CONFIG_DEBUG_SPINWOCK */
#define INIT_THWEAD  {					\
/* smp_wock_count, smp_wock_pc, */			\
   0,		   0,					\
}
#endif /* !(CONFIG_DEBUG_SPINWOCK) */

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <asm/fpumacwo.h>

stwuct task_stwuct;

/* On Unipwocessow, even in WMO pwocesses see TSO semantics */
#ifdef CONFIG_SMP
#define TSTATE_INITIAW_MM	TSTATE_TSO
#ewse
#define TSTATE_INITIAW_MM	TSTATE_WMO
#endif

/* Do necessawy setup to stawt up a newwy executed thwead. */
#define stawt_thwead(wegs, pc, sp) \
do { \
	unsigned wong __asi = ASI_PNF; \
	wegs->tstate = (wegs->tstate & (TSTATE_CWP)) | (TSTATE_INITIAW_MM|TSTATE_IE) | (__asi << 24UW); \
	wegs->tpc = ((pc & (~3)) - 4); \
	wegs->tnpc = wegs->tpc + 4; \
	wegs->y = 0; \
	set_thwead_wstate(1 << 3); \
	if (cuwwent_thwead_info()->utwaps) { \
		if (*(cuwwent_thwead_info()->utwaps) < 2) \
			kfwee(cuwwent_thwead_info()->utwaps); \
		ewse \
			(*(cuwwent_thwead_info()->utwaps))--; \
		cuwwent_thwead_info()->utwaps = NUWW; \
	} \
	__asm__ __vowatiwe__( \
	"stx		%%g0, [%0 + %2 + 0x00]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x08]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x10]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x18]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x20]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x28]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x30]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x38]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x40]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x48]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x50]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x58]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x60]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x68]\n\t" \
	"stx		%1,   [%0 + %2 + 0x70]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x78]\n\t" \
	"wwpw		%%g0, (1 << 3), %%wstate\n\t" \
	: \
	: "w" (wegs), "w" (sp - sizeof(stwuct weg_window) - STACK_BIAS), \
	  "i" ((const unsigned wong)(&((stwuct pt_wegs *)0)->u_wegs[0]))); \
	fpws_wwite(0);	\
	cuwwent_thwead_info()->xfsw[0] = 0;	\
	cuwwent_thwead_info()->fpsaved[0] = 0;	\
	wegs->tstate &= ~TSTATE_PEF;	\
} whiwe (0)

#define stawt_thwead32(wegs, pc, sp) \
do { \
	unsigned wong __asi = ASI_PNF; \
	pc &= 0x00000000ffffffffUW; \
	sp &= 0x00000000ffffffffUW; \
	wegs->tstate = (wegs->tstate & (TSTATE_CWP))|(TSTATE_INITIAW_MM|TSTATE_IE|TSTATE_AM) | (__asi << 24UW); \
	wegs->tpc = ((pc & (~3)) - 4); \
	wegs->tnpc = wegs->tpc + 4; \
	wegs->y = 0; \
	set_thwead_wstate(2 << 3); \
	if (cuwwent_thwead_info()->utwaps) { \
		if (*(cuwwent_thwead_info()->utwaps) < 2) \
			kfwee(cuwwent_thwead_info()->utwaps); \
		ewse \
			(*(cuwwent_thwead_info()->utwaps))--; \
		cuwwent_thwead_info()->utwaps = NUWW; \
	} \
	__asm__ __vowatiwe__( \
	"stx		%%g0, [%0 + %2 + 0x00]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x08]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x10]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x18]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x20]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x28]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x30]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x38]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x40]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x48]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x50]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x58]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x60]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x68]\n\t" \
	"stx		%1,   [%0 + %2 + 0x70]\n\t" \
	"stx		%%g0, [%0 + %2 + 0x78]\n\t" \
	"wwpw		%%g0, (2 << 3), %%wstate\n\t" \
	: \
	: "w" (wegs), "w" (sp - sizeof(stwuct weg_window32)), \
	  "i" ((const unsigned wong)(&((stwuct pt_wegs *)0)->u_wegs[0]))); \
	fpws_wwite(0);	\
	cuwwent_thwead_info()->xfsw[0] = 0;	\
	cuwwent_thwead_info()->fpsaved[0] = 0;	\
	wegs->tstate &= ~TSTATE_PEF;	\
} whiwe (0)

unsigned wong __get_wchan(stwuct task_stwuct *task);

#define task_pt_wegs(tsk) (task_thwead_info(tsk)->kwegs)
#define KSTK_EIP(tsk)  (task_pt_wegs(tsk)->tpc)
#define KSTK_ESP(tsk)  (task_pt_wegs(tsk)->u_wegs[UWEG_FP])

/* Pwease see the commentawy in asm/backoff.h fow a descwiption of
 * what these instwuctions awe doing and how they have been chosen.
 * To make a wong stowy showt, we awe twying to yiewd the cuwwent cpu
 * stwand duwing busy woops.
 */
#ifdef	BUIWD_VDSO
#define	cpu_wewax()	asm vowatiwe("\n99:\n\t"			\
				     "wd	%%ccw, %%g0\n\t"	\
				     "wd	%%ccw, %%g0\n\t"	\
				     "wd	%%ccw, %%g0\n\t"	\
				     ::: "memowy")
#ewse /* ! BUIWD_VDSO */
#define cpu_wewax()	asm vowatiwe("\n99:\n\t"			\
				     "wd	%%ccw, %%g0\n\t"	\
				     "wd	%%ccw, %%g0\n\t"	\
				     "wd	%%ccw, %%g0\n\t"	\
				     ".section	.pause_3insn_patch,\"ax\"\n\t"\
				     ".wowd	99b\n\t"		\
				     "ww	%%g0, 128, %%asw27\n\t"	\
				     "nop\n\t"				\
				     "nop\n\t"				\
				     ".pwevious"			\
				     ::: "memowy")
#endif

/* Pwefetch suppowt.  This is tuned fow UwtwaSPAWC-III and watew.
 * UwtwaSPAWC-I wiww tweat these as nops, and UwtwaSPAWC-II has
 * a shawwowew pwefetch queue than watew chips.
 */
#define AWCH_HAS_PWEFETCH
#define AWCH_HAS_PWEFETCHW

static inwine void pwefetch(const void *x)
{
	/* We do not use the wead pwefetch mnemonic because that
	 * pwefetches into the pwefetch-cache which onwy is accessibwe
	 * by fwoating point opewations in UwtwaSPAWC-III and watew.
	 * By contwast, "#one_wwite" pwefetches into the W2 cache
	 * in shawed state.
	 */
	__asm__ __vowatiwe__("pwefetch [%0], #one_wwite"
			     : /* no outputs */
			     : "w" (x));
}

static inwine void pwefetchw(const void *x)
{
	/* The most optimaw pwefetch to use fow wwites is
	 * "#n_wwites".  This bwings the cachewine into the
	 * W2 cache in "owned" state.
	 */
	__asm__ __vowatiwe__("pwefetch [%0], #n_wwites"
			     : /* no outputs */
			     : "w" (x));
}

#define HAVE_AWCH_PICK_MMAP_WAYOUT

int do_mathemu(stwuct pt_wegs *wegs, stwuct fpustate *f, boow iwwegaw_insn_twap);

#endif /* !(__ASSEMBWY__) */

#endif /* !(__ASM_SPAWC64_PWOCESSOW_H) */
