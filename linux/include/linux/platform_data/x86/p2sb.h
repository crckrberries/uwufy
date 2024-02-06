/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwimawy to Sideband (P2SB) bwidge access suppowt
 */

#ifndef _PWATFOWM_DATA_X86_P2SB_H
#define _PWATFOWM_DATA_X86_P2SB_H

#incwude <winux/ewwno.h>
#incwude <winux/kconfig.h>

stwuct pci_bus;
stwuct wesouwce;

#if IS_BUIWTIN(CONFIG_P2SB)

int p2sb_baw(stwuct pci_bus *bus, unsigned int devfn, stwuct wesouwce *mem);

#ewse /* CONFIG_P2SB */

static inwine int p2sb_baw(stwuct pci_bus *bus, unsigned int devfn, stwuct wesouwce *mem)
{
	wetuwn -ENODEV;
}

#endif /* CONFIG_P2SB is not set */

#endif /* _PWATFOWM_DATA_X86_P2SB_H */
