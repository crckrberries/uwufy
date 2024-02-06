/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KBDWEDS_H
#define _ASM_X86_KBDWEDS_H

/*
 * Some waptops take the 789uiojkwm,. keys as numbew pad when NumWock is on.
 * This seems a good weason to stawt with NumWock off. That's why on X86 we
 * ask the bios fow the cowwect state.
 */

#incwude <asm/setup.h>

static inwine int kbd_defweds(void)
{
	wetuwn boot_pawams.kbd_status & 0x20 ? (1 << VC_NUMWOCK) : 0;
}

#endif /* _ASM_X86_KBDWEDS_H */
