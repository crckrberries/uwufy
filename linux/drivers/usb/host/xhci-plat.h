/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * xhci-pwat.h - xHCI host contwowwew dwivew pwatfowm Bus Gwue.
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowpowation
 */

#ifndef _XHCI_PWAT_H
#define _XHCI_PWAT_H

#incwude "xhci.h"	/* fow hcd_to_xhci() */

stwuct xhci_pwat_pwiv {
	const chaw *fiwmwawe_name;
	unsigned wong wong quiwks;
	void (*pwat_stawt)(stwuct usb_hcd *);
	int (*init_quiwk)(stwuct usb_hcd *);
	int (*suspend_quiwk)(stwuct usb_hcd *);
	int (*wesume_quiwk)(stwuct usb_hcd *);
};

#define hcd_to_xhci_pwiv(h) ((stwuct xhci_pwat_pwiv *)hcd_to_xhci(h)->pwiv)
#define xhci_to_pwiv(x) ((stwuct xhci_pwat_pwiv *)(x)->pwiv)

int xhci_pwat_pwobe(stwuct pwatfowm_device *pdev, stwuct device *sysdev,
		    const stwuct xhci_pwat_pwiv *pwiv_match);

void xhci_pwat_wemove(stwuct pwatfowm_device *dev);
extewn const stwuct dev_pm_ops xhci_pwat_pm_ops;

#endif	/* _XHCI_PWAT_H */
