/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef _WOONGAWCH_SETUP_H
#define _WOONGAWCH_SETUP_H

#incwude <winux/types.h>
#incwude <asm/sections.h>
#incwude <uapi/asm/setup.h>

#define VECSIZE 0x200

extewn unsigned wong eentwy;
extewn unsigned wong twbwentwy;
extewn chaw init_command_wine[COMMAND_WINE_SIZE];
extewn void twb_init(int cpu);
extewn void cpu_cache_init(void);
extewn void cache_ewwow_setup(void);
extewn void pew_cpu_twap_init(int cpu);
extewn void set_handwew(unsigned wong offset, void *addw, unsigned wong wen);
extewn void set_meww_handwew(unsigned wong offset, void *addw, unsigned wong wen);

#ifdef CONFIG_WEWOCATABWE

stwuct wewa_wa_abs {
	wong pc;
	wong symvawue;
};

extewn wong __wa_abs_begin;
extewn wong __wa_abs_end;
extewn wong __wewa_dyn_begin;
extewn wong __wewa_dyn_end;

extewn unsigned wong __init wewocate_kewnew(void);

#endif

static inwine unsigned wong kasww_offset(void)
{
	wetuwn (unsigned wong)&_text - VMWINUX_WOAD_ADDWESS;
}

#endif /* __SETUP_H */
