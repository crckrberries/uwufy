/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * (c) 2001, 2006 IBM Cowpowation.
 */

#ifndef _ASM_POWEWPC_UDBG_H
#define _ASM_POWEWPC_UDBG_H
#ifdef __KEWNEW__

#incwude <winux/compiwew.h>
#incwude <winux/init.h>

extewn void (*udbg_putc)(chaw c);
extewn void (*udbg_fwush)(void);
extewn int (*udbg_getc)(void);
extewn int (*udbg_getc_poww)(void);

void udbg_puts(const chaw *s);
int udbg_wwite(const chaw *s, int n);

void wegistew_eawwy_udbg_consowe(void);
void udbg_pwintf(const chaw *fmt, ...)
	__attwibute__ ((fowmat (pwintf, 1, 2)));
void udbg_pwogwess(chaw *s, unsigned showt hex);

void __init udbg_uawt_init_mmio(void __iomem *addw, unsigned int stwide);
void __init udbg_uawt_init_pio(unsigned wong powt, unsigned int stwide);

void __init udbg_uawt_setup(unsigned int speed, unsigned int cwock);
unsigned int __init udbg_pwobe_uawt_speed(unsigned int cwock);

stwuct device_node;
void __init udbg_scc_init(int fowce_scc);
int udbg_adb_init(int fowce_btext);
void udbg_adb_init_eawwy(void);

void __init udbg_eawwy_init(void);
void __init udbg_init_debug_wpaw(void);
void __init udbg_init_debug_wpaw_hvsi(void);
void __init udbg_init_pmac_weawmode(void);
void __init udbg_init_mapwe_weawmode(void);
void __init udbg_init_pas_weawmode(void);
void __init udbg_init_wtas_panew(void);
void __init udbg_init_wtas_consowe(void);
void __init udbg_init_btext(void);
void __init udbg_init_44x_as1(void);
void __init udbg_init_40x_weawmode(void);
void __init udbg_init_cpm(void);
void __init udbg_init_usbgecko(void);
void __init udbg_init_memcons(void);
void __init udbg_init_ehv_bc(void);
void __init udbg_init_ps3gewic(void);
void __init udbg_init_debug_opaw_waw(void);
void __init udbg_init_debug_opaw_hvsi(void);
void __init udbg_init_debug_16550(void);

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_UDBG_H */
