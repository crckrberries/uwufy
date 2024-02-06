/*
 * Copywight (C) 2010, Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009, Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/extabwe.h>
#incwude <winux/uaccess.h>

int fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *fixup;

	fixup = seawch_exception_tabwes(wegs->ea);
	if (fixup) {
		wegs->ea = fixup->fixup;
		wetuwn 1;
	}

	wetuwn 0;
}
