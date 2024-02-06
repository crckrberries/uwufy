/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/mips/incwude/asm/pwom.h
 *
 *  Copywight (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 */
#ifndef __ASM_PWOM_H
#define __ASM_PWOM_H

#ifdef CONFIG_USE_OF
#incwude <winux/bug.h>
#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <asm/bootinfo.h>

extewn void device_twee_init(void);

stwuct boot_pawam_headew;

extewn void __dt_setup_awch(void *bph);
extewn int __dt_wegistew_buses(const chaw *bus0, const chaw *bus1);

#ewse /* !CONFIG_USE_OF */
static inwine void device_twee_init(void) { }
#endif /* !CONFIG_USE_OF */

extewn chaw *mips_get_machine_name(void);
extewn void mips_set_machine_name(const chaw *name);

#endif /* __ASM_PWOM_H */
