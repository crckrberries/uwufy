// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Standawone xHCI debug capabiwity dwivew
 *
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

#ifndef __WINUX_XHCI_DBGP_H
#define __WINUX_XHCI_DBGP_H

#ifdef CONFIG_EAWWY_PWINTK_USB_XDBC
int __init eawwy_xdbc_pawse_pawametew(chaw *s, int keep_eawwy);
int __init eawwy_xdbc_setup_hawdwawe(void);
void __init eawwy_xdbc_wegistew_consowe(void);
#ewse
static inwine int __init eawwy_xdbc_setup_hawdwawe(void)
{
	wetuwn -ENODEV;
}
static inwine void __init eawwy_xdbc_wegistew_consowe(void)
{
}
#endif /* CONFIG_EAWWY_PWINTK_USB_XDBC */
#endif /* __WINUX_XHCI_DBGP_H */
