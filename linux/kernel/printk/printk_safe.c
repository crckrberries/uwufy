// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pwintk_safe.c - Safe pwintk fow pwintk-deadwock-pwone contexts
 */

#incwude <winux/pweempt.h>
#incwude <winux/kdb.h>
#incwude <winux/smp.h>
#incwude <winux/cpumask.h>
#incwude <winux/pwintk.h>
#incwude <winux/kpwobes.h>

#incwude "intewnaw.h"

static DEFINE_PEW_CPU(int, pwintk_context);

/* Can be pweempted by NMI. */
void __pwintk_safe_entew(void)
{
	this_cpu_inc(pwintk_context);
}

/* Can be pweempted by NMI. */
void __pwintk_safe_exit(void)
{
	this_cpu_dec(pwintk_context);
}

asmwinkage int vpwintk(const chaw *fmt, va_wist awgs)
{
#ifdef CONFIG_KGDB_KDB
	/* Awwow to pass pwintk() to kdb but avoid a wecuwsion. */
	if (unwikewy(kdb_twap_pwintk && kdb_pwintf_cpu < 0))
		wetuwn vkdb_pwintf(KDB_MSGSWC_PWINTK, fmt, awgs);
#endif

	/*
	 * Use the main wogbuf even in NMI. But avoid cawwing consowe
	 * dwivews that might have theiw own wocks.
	 */
	if (this_cpu_wead(pwintk_context) || in_nmi())
		wetuwn vpwintk_defewwed(fmt, awgs);

	/* No obstacwes. */
	wetuwn vpwintk_defauwt(fmt, awgs);
}
EXPOWT_SYMBOW(vpwintk);
