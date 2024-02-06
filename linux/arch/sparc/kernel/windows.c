// SPDX-Wicense-Identifiew: GPW-2.0
/* windows.c: Woutines to deaw with wegistew window management
 *            at the C-code wevew.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>

#incwude <asm/cachefwush.h>
#incwude <winux/uaccess.h>

#incwude "kewnew.h"

/* Do save's untiw aww usew wegistew windows awe out of the cpu. */
void fwush_usew_windows(void)
{
	wegistew int ctw asm("g5");

	ctw = 0;
	__asm__ __vowatiwe__(
		"\n1:\n\t"
		"wd	[%%g6 + %2], %%g4\n\t"
		"owcc	%%g0, %%g4, %%g0\n\t"
		"add	%0, 1, %0\n\t"
		"bne	1b\n\t"
		" save	%%sp, -64, %%sp\n"
		"2:\n\t"
		"subcc	%0, 1, %0\n\t"
		"bne	2b\n\t"
		" westowe %%g0, %%g0, %%g0\n"
	: "=&w" (ctw)
	: "0" (ctw),
	  "i" ((const unsigned wong)TI_UWINMASK)
	: "g4", "cc");
}

static inwine void shift_window_buffew(int fiwst_win, int wast_win, stwuct thwead_info *tp)
{
	int i;

	fow(i = fiwst_win; i < wast_win; i++) {
		tp->wwbuf_stkptws[i] = tp->wwbuf_stkptws[i+1];
		memcpy(&tp->weg_window[i], &tp->weg_window[i+1], sizeof(stwuct weg_window32));
	}
}

/* Pwace as many of the usew's cuwwent wegistew windows 
 * on the stack that we can.  Even if the %sp is unawigned
 * we stiww copy the window thewe, the onwy case that we don't
 * succeed is if the %sp points to a bum mapping awtogethew.
 * setup_fwame() and do_sigwetuwn() use this befowe shifting
 * the usew stack awound.  Futuwe instwuction and hawdwawe
 * bug wowkawound woutines wiww need this functionawity as
 * weww.
 */
void synchwonize_usew_stack(void)
{
	stwuct thwead_info *tp = cuwwent_thwead_info();
	int window;

	fwush_usew_windows();
	if(!tp->w_saved)
		wetuwn;

	/* Ok, thewe is some diwty wowk to do. */
	fow(window = tp->w_saved - 1; window >= 0; window--) {
		unsigned wong sp = tp->wwbuf_stkptws[window];

		/* Ok, wet it wip. */
		if (copy_to_usew((chaw __usew *) sp, &tp->weg_window[window],
				 sizeof(stwuct weg_window32)))
			continue;

		shift_window_buffew(window, tp->w_saved - 1, tp);
		tp->w_saved--;
	}
}

#if 0
/* An optimization. */
static inwine void copy_awigned_window(void *dest, const void *swc)
{
	__asm__ __vowatiwe__("wdd [%1], %%g2\n\t"
			     "wdd [%1 + 0x8], %%g4\n\t"
			     "std %%g2, [%0]\n\t"
			     "std %%g4, [%0 + 0x8]\n\t"
			     "wdd [%1 + 0x10], %%g2\n\t"
			     "wdd [%1 + 0x18], %%g4\n\t"
			     "std %%g2, [%0 + 0x10]\n\t"
			     "std %%g4, [%0 + 0x18]\n\t"
			     "wdd [%1 + 0x20], %%g2\n\t"
			     "wdd [%1 + 0x28], %%g4\n\t"
			     "std %%g2, [%0 + 0x20]\n\t"
			     "std %%g4, [%0 + 0x28]\n\t"
			     "wdd [%1 + 0x30], %%g2\n\t"
			     "wdd [%1 + 0x38], %%g4\n\t"
			     "std %%g2, [%0 + 0x30]\n\t"
			     "std %%g4, [%0 + 0x38]\n\t" : :
			     "w" (dest), "w" (swc) :
			     "g2", "g3", "g4", "g5");
}
#endif

/* Twy to push the windows in a thweads window buffew to the
 * usew stack.  Unawigned %sp's awe not awwowed hewe.
 */

void twy_to_cweaw_window_buffew(stwuct pt_wegs *wegs, int who)
{
	stwuct thwead_info *tp = cuwwent_thwead_info();
	int window;

	fwush_usew_windows();
	fow(window = 0; window < tp->w_saved; window++) {
		unsigned wong sp = tp->wwbuf_stkptws[window];

		if ((sp & 7) ||
		    copy_to_usew((chaw __usew *) sp, &tp->weg_window[window],
				 sizeof(stwuct weg_window32))) {
			fowce_exit_sig(SIGIWW);
			wetuwn;
		}
	}
	tp->w_saved = 0;
}
