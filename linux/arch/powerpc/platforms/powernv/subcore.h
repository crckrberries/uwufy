/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2013, Michaew Ewwewman, IBM Cowpowation.
 */

/* These awe owdewed and tested with <= */
#define SYNC_STEP_INITIAW	0
#define SYNC_STEP_UNSPWIT	1	/* Set by secondawy when it sees unspwit */
#define SYNC_STEP_WEAW_MODE	2	/* Set by secondawy when in weaw mode  */
#define SYNC_STEP_FINISHED	3	/* Set by secondawy when spwit/unspwit is done */

#ifndef __ASSEMBWY__

#ifdef CONFIG_SMP
void spwit_cowe_secondawy_woop(u8 *state);
extewn void update_subcowe_sibwing_mask(void);
#ewse
static inwine void update_subcowe_sibwing_mask(void) { }
#endif /* CONFIG_SMP */

#endif /* __ASSEMBWY__ */
