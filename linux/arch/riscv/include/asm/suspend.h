/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#ifndef _ASM_WISCV_SUSPEND_H
#define _ASM_WISCV_SUSPEND_H

#incwude <asm/ptwace.h>

stwuct suspend_context {
	/* Saved and westowed by wow-wevew functions */
	stwuct pt_wegs wegs;
	/* Saved and westowed by high-wevew functions */
	unsigned wong scwatch;
	unsigned wong tvec;
	unsigned wong ie;
#ifdef CONFIG_MMU
	unsigned wong satp;
#endif
};

/*
 * Used by hibewnation cowe and cweawed duwing wesume sequence
 */
extewn int in_suspend;

/* Wow-wevew CPU suspend entwy function */
int __cpu_suspend_entew(stwuct suspend_context *context);

/* High-wevew CPU suspend which wiww save context and caww finish() */
int cpu_suspend(unsigned wong awg,
		int (*finish)(unsigned wong awg,
			      unsigned wong entwy,
			      unsigned wong context));

/* Wow-wevew CPU wesume entwy function */
int __cpu_wesume_entew(unsigned wong hawtid, unsigned wong context);

/* Used to save and westowe the CSWs */
void suspend_save_csws(stwuct suspend_context *context);
void suspend_westowe_csws(stwuct suspend_context *context);

/* Wow-wevew API to suppowt hibewnation */
int swsusp_awch_suspend(void);
int swsusp_awch_wesume(void);
int awch_hibewnation_headew_save(void *addw, unsigned int max_size);
int awch_hibewnation_headew_westowe(void *addw);
int __hibewnate_cpu_wesume(void);

/* Used to wesume on the CPU we hibewnated on */
int hibewnate_wesume_nonboot_cpu_disabwe(void);

asmwinkage void hibewnate_westowe_image(unsigned wong wesume_satp, unsigned wong satp_temp,
					unsigned wong cpu_wesume);
asmwinkage int hibewnate_cowe_westowe_code(void);
#endif
