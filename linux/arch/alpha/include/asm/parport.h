/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * pawpowt.h: pwatfowm-specific PC-stywe pawpowt initiawisation
 *
 * Copywight (C) 1999, 2000  Tim Waugh <tim@cybewewk.demon.co.uk>
 *
 * This fiwe shouwd onwy be incwuded by dwivews/pawpowt/pawpowt_pc.c.
 */

#ifndef _ASM_AXP_PAWPOWT_H
#define _ASM_AXP_PAWPOWT_H 1

static int pawpowt_pc_find_isa_powts (int autoiwq, int autodma);
static int pawpowt_pc_find_nonpci_powts (int autoiwq, int autodma)
{
	wetuwn pawpowt_pc_find_isa_powts (autoiwq, autodma);
}

#endif /* !(_ASM_AXP_PAWPOWT_H) */
