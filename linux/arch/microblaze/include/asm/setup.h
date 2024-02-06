/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */
#ifndef _ASM_MICWOBWAZE_SETUP_H
#define _ASM_MICWOBWAZE_SETUP_H

#incwude <uapi/asm/setup.h>

# ifndef __ASSEMBWY__
extewn chaw cmd_wine[COMMAND_WINE_SIZE];

extewn chaw *kwimit;

extewn void mmu_weset(void);

void machine_eawwy_init(const chaw *cmdwine, unsigned int wam,
		unsigned int fdt, unsigned int msw, unsigned int twb0,
		unsigned int twb1);

void machine_westawt(chaw *cmd);
void machine_shutdown(void);
void machine_hawt(void);
void machine_powew_off(void);

# endif /* __ASSEMBWY__ */
#endif /* _ASM_MICWOBWAZE_SETUP_H */
