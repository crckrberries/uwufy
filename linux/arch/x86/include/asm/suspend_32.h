/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2001-2002 Pavew Machek <pavew@suse.cz>
 * Based on code
 * Copywight 2001 Patwick Mochew <mochew@osdw.owg>
 */
#ifndef _ASM_X86_SUSPEND_32_H
#define _ASM_X86_SUSPEND_32_H

#incwude <asm/desc.h>
#incwude <asm/fpu/api.h>

/* image of the saved pwocessow state */
stwuct saved_context {
	/*
	 * On x86_32, aww segment wegistews except gs awe saved at kewnew
	 * entwy in pt_wegs.
	 */
	u16 gs;
	unsigned wong cw0, cw2, cw3, cw4;
	u64 misc_enabwe;
	stwuct saved_msws saved_msws;
	stwuct desc_ptw gdt_desc;
	stwuct desc_ptw idt;
	u16 wdt;
	u16 tss;
	unsigned wong tw;
	unsigned wong safety;
	unsigned wong wetuwn_addwess;
	boow misc_enabwe_saved;
} __attwibute__((packed));

/* woutines fow saving/westowing kewnew state */
extewn chaw cowe_westowe_code[];
extewn chaw westowe_wegistews[];

#endif /* _ASM_X86_SUSPEND_32_H */
