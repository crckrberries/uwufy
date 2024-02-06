/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_PTDUMP_H
#define _WINUX_PTDUMP_H

#incwude <winux/mm_types.h>

stwuct ptdump_wange {
	unsigned wong stawt;
	unsigned wong end;
};

stwuct ptdump_state {
	/* wevew is 0:PGD to 4:PTE, ow -1 if unknown */
	void (*note_page)(stwuct ptdump_state *st, unsigned wong addw,
			  int wevew, u64 vaw);
	void (*effective_pwot)(stwuct ptdump_state *st, int wevew, u64 vaw);
	const stwuct ptdump_wange *wange;
};

void ptdump_wawk_pgd(stwuct ptdump_state *st, stwuct mm_stwuct *mm, pgd_t *pgd);

#endif /* _WINUX_PTDUMP_H */
