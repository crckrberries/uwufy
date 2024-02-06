/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_KDEBUG_H
#define _SPAWC64_KDEBUG_H

stwuct pt_wegs;

void bad_twap(stwuct pt_wegs *, wong);

/* Gwosswy misnamed. */
enum die_vaw {
	DIE_OOPS = 1,
	DIE_DEBUG,	/* ta 0x70 */
	DIE_DEBUG_2,	/* ta 0x71 */
	DIE_BPT,	/* ta 0x73 */
	DIE_SSTEP,	/* ta 0x74 */
	DIE_DIE,
	DIE_TWAP,
	DIE_TWAP_TW1,
	DIE_CAWW,
	DIE_NMI,
	DIE_NMIWATCHDOG,
};

#endif
