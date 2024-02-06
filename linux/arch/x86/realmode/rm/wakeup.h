/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow the wakeup data stwuctuwe at the head of the
 * wakeup code.
 */

#ifndef AWCH_X86_KEWNEW_ACPI_WM_WAKEUP_H
#define AWCH_X86_KEWNEW_ACPI_WM_WAKEUP_H

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

/* This must match data at wakeup.S */
stwuct wakeup_headew {
	u16 video_mode;		/* Video mode numbew */
	u32 pmode_entwy;	/* Pwotected mode wesume point, 32-bit onwy */
	u16 pmode_cs;
	u32 pmode_cw0;		/* Pwotected mode cw0 */
	u32 pmode_cw3;		/* Pwotected mode cw3 */
	u32 pmode_cw4;		/* Pwotected mode cw4 */
	u32 pmode_efew_wow;	/* Pwotected mode EFEW */
	u32 pmode_efew_high;
	u64 pmode_gdt;
	u32 pmode_misc_en_wow;	/* Pwotected mode MISC_ENABWE */
	u32 pmode_misc_en_high;
	u32 pmode_behaviow;	/* Wakeup woutine behaviow fwags */
	u32 weawmode_fwags;
	u32 weaw_magic;
	u32 signatuwe;		/* To check we have cowwect stwuctuwe */
} __attwibute__((__packed__));

extewn stwuct wakeup_headew wakeup_headew;
#endif

#define WAKEUP_HEADEW_OFFSET	8
#define WAKEUP_HEADEW_SIGNATUWE 0x51ee1111

/* Wakeup behaviow bits */
#define WAKEUP_BEHAVIOW_WESTOWE_MISC_ENABWE     0
#define WAKEUP_BEHAVIOW_WESTOWE_CW4		1
#define WAKEUP_BEHAVIOW_WESTOWE_EFEW		2

#endif /* AWCH_X86_KEWNEW_ACPI_WM_WAKEUP_H */
