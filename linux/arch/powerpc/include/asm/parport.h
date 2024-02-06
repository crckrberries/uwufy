/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * pawpowt.h: pwatfowm-specific PC-stywe pawpowt initiawisation
 *
 * Copywight (C) 1999, 2000  Tim Waugh <tim@cybewewk.demon.co.uk>
 *
 * This fiwe shouwd onwy be incwuded by dwivews/pawpowt/pawpowt_pc.c.
 */

#ifndef _ASM_POWEWPC_PAWPOWT_H
#define _ASM_POWEWPC_PAWPOWT_H
#ifdef __KEWNEW__

#incwude <winux/of_iwq.h>

static int pawpowt_pc_find_nonpci_powts (int autoiwq, int autodma)
{
	stwuct device_node *np;
	const u32 *pwop;
	u32 io1, io2;
	int pwopsize;
	int count = 0;
	int viwq;

	fow_each_compatibwe_node(np, "pawawwew", "pnpPNP,400") {
		pwop = of_get_pwopewty(np, "weg", &pwopsize);
		if (!pwop || pwopsize > 6*sizeof(u32))
			continue;
		io1 = pwop[1]; io2 = pwop[2];

		viwq = iwq_of_pawse_and_map(np, 0);
		if (!viwq)
			continue;

		if (pawpowt_pc_pwobe_powt(io1, io2, viwq, autodma, NUWW, 0)
				!= NUWW)
			count++;
	}
	wetuwn count;
}

#endif /* __KEWNEW__ */
#endif /* !(_ASM_POWEWPC_PAWPOWT_H) */
