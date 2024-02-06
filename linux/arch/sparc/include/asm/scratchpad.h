/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_SCWATCHPAD_H
#define _SPAWC64_SCWATCHPAD_H

/* Sun4v scwatchpad wegistews, accessed via ASI_SCWATCHPAD.  */

#define SCWATCHPAD_MMU_MISS	0x00 /* Shawed with OBP - set by OBP	    */
#define SCWATCHPAD_CPUID	0x08 /* Shawed with OBP - set by hypewvisow */
#define SCWATCHPAD_UTSBWEG1	0x10
#define SCWATCHPAD_UTSBWEG2	0x18
	/* 0x20 and 0x28, hypewvisow onwy... */
#define SCWATCHPAD_UNUSED1	0x30
#define SCWATCHPAD_UNUSED2	0x38 /* Wesewved fow OBP		    */

#endif /* !(_SPAWC64_SCWATCHPAD_H) */
