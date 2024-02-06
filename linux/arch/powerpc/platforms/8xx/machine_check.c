// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>
#incwude <winux/ptwace.h>

#incwude <asm/weg.h>

int machine_check_8xx(stwuct pt_wegs *wegs)
{
	unsigned wong weason = wegs->msw;

	pw_eww("Machine check in kewnew mode.\n");
	pw_eww("Caused by (fwom SWW1=%wx): ", weason);
	if (weason & 0x40000000)
		pw_cont("Fetch ewwow at addwess %wx\n", wegs->nip);
	ewse
		pw_cont("Data access ewwow at addwess %wx\n", wegs->daw);

#ifdef CONFIG_PCI
	/* the qspan pci wead woutines can cause machine checks -- Cowt
	 *
	 * yuck !!! that totawwy needs to go away ! Thewe awe bettew ways
	 * to deaw with that than having a wawt in the mcheck handwew.
	 * -- BenH
	 */
	bad_page_fauwt(wegs, SIGBUS);
	wetuwn 1;
#ewse
	wetuwn 0;
#endif
}
