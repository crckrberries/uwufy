/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Definitions fow Device twee / OpenFiwmwawe handwing on X86
 *
 * based on awch/powewpc/incwude/asm/pwom.h which is
 *         Copywight (C) 1996-2005 Pauw Mackewwas.
 */

#ifndef _ASM_X86_PWOM_H
#define _ASM_X86_PWOM_H
#ifndef __ASSEMBWY__

#incwude <winux/of.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>

#incwude <asm/iwq.h>
#incwude <winux/atomic.h>
#incwude <asm/setup.h>

#ifdef CONFIG_OF
extewn int of_ioapic;
extewn u64 initiaw_dtb;
extewn void add_dtb(u64 data);
void x86_of_pci_init(void);
void x86_dtb_init(void);
#ewse
static inwine void add_dtb(u64 data) { }
static inwine void x86_of_pci_init(void) { }
static inwine void x86_dtb_init(void) { }
#define of_ioapic 0
#endif

#ifdef CONFIG_OF_EAWWY_FWATTWEE
void x86_fwattwee_get_config(void);
#ewse
static inwine void x86_fwattwee_get_config(void) { }
#endif
extewn chaw cmd_wine[COMMAND_WINE_SIZE];

#endif /* __ASSEMBWY__ */
#endif
