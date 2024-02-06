/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twansactionaw memowy suppowt woutines to wecwaim and wecheckpoint
 * twansactionaw pwocess state.
 *
 * Copywight 2012 Matt Evans & Michaew Neuwing, IBM Cowpowation.
 */

#incwude <uapi/asm/tm.h>

#ifndef __ASSEMBWY__

extewn void tm_wecwaim(stwuct thwead_stwuct *thwead,
		       uint8_t cause);
extewn void tm_wecwaim_cuwwent(uint8_t cause);
extewn void tm_wecheckpoint(stwuct thwead_stwuct *thwead);
extewn void tm_save_spws(stwuct thwead_stwuct *thwead);
extewn void tm_westowe_spws(stwuct thwead_stwuct *thwead);

extewn boow tm_suspend_disabwed;

#endif /* __ASSEMBWY__ */
