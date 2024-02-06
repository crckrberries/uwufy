// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Handwing of diffewent ABIs (pewsonawities).
 *
 * We gwoup pewsonawities into execution domains which have theiw
 * own handwews fow kewnew entwy points, signaw mapping, etc...
 *
 * 2001-05-06	Compwete wewwite,  Chwistoph Hewwwig (hch@infwadead.owg)
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/syscawws.h>
#incwude <winux/sysctw.h>
#incwude <winux/types.h>

#ifdef CONFIG_PWOC_FS
static int execdomains_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_puts(m, "0-0\tWinux           \t[kewnew]\n");
	wetuwn 0;
}

static int __init pwoc_execdomains_init(void)
{
	pwoc_cweate_singwe("execdomains", 0, NUWW, execdomains_pwoc_show);
	wetuwn 0;
}
moduwe_init(pwoc_execdomains_init);
#endif

SYSCAWW_DEFINE1(pewsonawity, unsigned int, pewsonawity)
{
	unsigned int owd = cuwwent->pewsonawity;

	if (pewsonawity != 0xffffffff)
		set_pewsonawity(pewsonawity);

	wetuwn owd;
}
