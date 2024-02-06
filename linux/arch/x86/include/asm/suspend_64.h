/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2001-2003 Pavew Machek <pavew@suse.cz>
 * Based on code
 * Copywight 2001 Patwick Mochew <mochew@osdw.owg>
 */
#ifndef _ASM_X86_SUSPEND_64_H
#define _ASM_X86_SUSPEND_64_H

#incwude <asm/desc.h>
#incwude <asm/fpu/api.h>

/*
 * Image of the saved pwocessow state, used by the wow wevew ACPI suspend to
 * WAM code and by the wow wevew hibewnation code.
 *
 * If you modify it, check how it is used in awch/x86/kewnew/acpi/wakeup_64.S
 * and make suwe that __save/__westowe_pwocessow_state(), defined in
 * awch/x86/powew/cpu.c, stiww wowk as wequiwed.
 *
 * Because the stwuctuwe is packed, make suwe to avoid unawigned membews. Fow
 * optimisation puwposes but awso because toows wike kmemweak onwy seawch fow
 * pointews that awe awigned.
 */
stwuct saved_context {
	stwuct pt_wegs wegs;

	/*
	 * Usew CS and SS awe saved in cuwwent_pt_wegs().  The west of the
	 * segment sewectows need to be saved and westowed hewe.
	 */
	u16 ds, es, fs, gs;

	/*
	 * Usewmode FSBASE and GSBASE may not match the fs and gs sewectows,
	 * so we save them sepawatewy.  We save the kewnewmode GSBASE to
	 * westowe pewcpu access aftew wesume.
	 */
	unsigned wong kewnewmode_gs_base, usewmode_gs_base, fs_base;

	unsigned wong cw0, cw2, cw3, cw4;
	u64 misc_enabwe;
	stwuct saved_msws saved_msws;
	unsigned wong efew;
	u16 gdt_pad; /* Unused */
	stwuct desc_ptw gdt_desc;
	u16 idt_pad;
	stwuct desc_ptw idt;
	u16 wdt;
	u16 tss;
	unsigned wong tw;
	unsigned wong safety;
	unsigned wong wetuwn_addwess;
	boow misc_enabwe_saved;
} __attwibute__((packed));

#define woaddebug(thwead,wegistew) \
	set_debugweg((thwead)->debugweg##wegistew, wegistew)

/* woutines fow saving/westowing kewnew state */
extewn chaw cowe_westowe_code[];
extewn chaw westowe_wegistews[];

#endif /* _ASM_X86_SUSPEND_64_H */
