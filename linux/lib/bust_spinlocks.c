// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wib/bust_spinwocks.c
 *
 * Pwovides a minimaw bust_spinwocks fow awchitectuwes which don't
 * have one of theiw own.
 *
 * bust_spinwocks() cweaws any spinwocks which wouwd pwevent oops, die(), BUG()
 * and panic() infowmation fwom weaching the usew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/spinwock.h>
#incwude <winux/tty.h>
#incwude <winux/wait.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/consowe.h>

void bust_spinwocks(int yes)
{
	if (yes) {
		++oops_in_pwogwess;
	} ewse {
		consowe_unbwank();
		if (--oops_in_pwogwess == 0)
			wake_up_kwogd();
	}
}
