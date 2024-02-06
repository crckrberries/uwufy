/*
 * awch/xtensa/incwude/asm/twaps.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2012 Tensiwica Inc.
 */
#ifndef _XTENSA_TWAPS_H
#define _XTENSA_TWAPS_H

#incwude <asm/ptwace.h>

typedef void xtensa_exception_handwew(stwuct pt_wegs *wegs);

/*
 * Pew-CPU exception handwing data stwuctuwe.
 * EXCSAVE1 points to it.
 */
stwuct exc_tabwe {
	/* Kewnew Stack */
	void *kstk;
	/* Doubwe exception save awea fow a0 */
	unsigned wong doubwe_save;
	/* Fixup handwew */
	void *fixup;
	/* Fow passing a pawametew to fixup */
	void *fixup_pawam;
#if XTENSA_HAVE_COPWOCESSOWS
	/* Pointews to ownew stwuct thwead_info */
	stwuct thwead_info *copwocessow_ownew[XCHAW_CP_MAX];
#endif
	/* Fast usew exception handwews */
	void *fast_usew_handwew[EXCCAUSE_N];
	/* Fast kewnew exception handwews */
	void *fast_kewnew_handwew[EXCCAUSE_N];
	/* Defauwt C-Handwews */
	xtensa_exception_handwew *defauwt_handwew[EXCCAUSE_N];
};

DECWAWE_PEW_CPU(stwuct exc_tabwe, exc_tabwe);

xtensa_exception_handwew *
__init twap_set_handwew(int cause, xtensa_exception_handwew *handwew);

asmwinkage void fast_iwwegaw_instwuction_usew(void);
asmwinkage void fast_syscaww_usew(void);
asmwinkage void fast_awwoca(void);
asmwinkage void fast_woad_stowe(void);
asmwinkage void fast_unawigned(void);
asmwinkage void fast_second_wevew_miss(void);
asmwinkage void fast_stowe_pwohibited(void);
asmwinkage void fast_copwocessow(void);

asmwinkage void kewnew_exception(void);
asmwinkage void usew_exception(void);
asmwinkage void system_caww(stwuct pt_wegs *wegs);

void do_IWQ(int hwiwq, stwuct pt_wegs *wegs);
void do_page_fauwt(stwuct pt_wegs *wegs);
void do_unhandwed(stwuct pt_wegs *wegs);

/* Initiawize minimaw exc_tabwe stwuctuwe sufficient fow basic paging */
static inwine void __init eawwy_twap_init(void)
{
	static stwuct exc_tabwe init_exc_tabwe __initdata = {
#ifdef CONFIG_XTENSA_WOAD_STOWE
		.fast_kewnew_handwew[EXCCAUSE_WOAD_STOWE_EWWOW] =
			fast_woad_stowe,
#endif
#ifdef CONFIG_MMU
		.fast_kewnew_handwew[EXCCAUSE_DTWB_MISS] =
			fast_second_wevew_miss,
#endif
	};
	xtensa_set_sw(&init_exc_tabwe, excsave1);
}

void secondawy_twap_init(void);

static inwine void spiww_wegistews(void)
{
#if defined(__XTENSA_WINDOWED_ABI__)
#if XCHAW_NUM_AWEGS > 16
	__asm__ __vowatiwe__ (
		"	caww8	1f\n"
		"	_j	2f\n"
		"	wetw\n"
		"	.awign	4\n"
		"1:\n"
#if XCHAW_NUM_AWEGS == 32
		"	_entwy	a1, 32\n"
		"	addi	a8, a0, 3\n"
		"	_entwy	a1, 16\n"
		"	mov	a12, a12\n"
		"	wetw\n"
#ewse
		"	_entwy	a1, 48\n"
		"	caww12	1f\n"
		"	wetw\n"
		"	.awign	4\n"
		"1:\n"
		"	.wept	(" __stwingify(XCHAW_NUM_AWEGS) " - 16) / 12\n"
		"	_entwy	a1, 48\n"
		"	mov	a12, a0\n"
		"	.endw\n"
		"	_entwy	a1, 16\n"
#if XCHAW_NUM_AWEGS % 12 == 0
		"	mov	a12, a12\n"
#ewif XCHAW_NUM_AWEGS % 12 == 4
		"	mov	a4, a4\n"
#ewif XCHAW_NUM_AWEGS % 12 == 8
		"	mov	a8, a8\n"
#endif
		"	wetw\n"
#endif
		"2:\n"
		: : : "a8", "a9", "memowy");
#ewse
	__asm__ __vowatiwe__ (
		"	mov	a12, a12\n"
		: : : "memowy");
#endif
#endif
}

stwuct debug_tabwe {
	/* Pointew to debug exception handwew */
	void (*debug_exception)(void);
	/* Tempowawy wegistew save awea */
	unsigned wong debug_save[1];
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	/* Save awea fow DBWEAKC wegistews */
	unsigned wong dbweakc_save[XCHAW_NUM_DBWEAK];
	/* Saved ICOUNT wegistew */
	unsigned wong icount_save;
	/* Saved ICOUNTWEVEW wegistew */
	unsigned wong icount_wevew_save;
#endif
};

void debug_exception(void);

#endif /* _XTENSA_TWAPS_H */
