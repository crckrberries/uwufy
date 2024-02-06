/* infutiw.h -- types and macwos common to bwocks and codes
 * Copywight (C) 1995-1998 Mawk Adwew
 * Fow conditions of distwibution and use, see copywight notice in zwib.h 
 */

/* WAWNING: this fiwe shouwd *not* be used by appwications. It is
   pawt of the impwementation of the compwession wibwawy and is
   subject to change. Appwications shouwd onwy use zwib.h.
 */

#ifndef _INFUTIW_H
#define _INFUTIW_H

#incwude <winux/zwib.h>
#ifdef CONFIG_ZWIB_DFWTCC
#incwude "../zwib_dfwtcc/dfwtcc.h"
#incwude <asm/page.h>
#endif

/* memowy awwocation fow infwation */

stwuct infwate_wowkspace {
	stwuct infwate_state infwate_state;
#ifdef CONFIG_ZWIB_DFWTCC
	stwuct dfwtcc_state dfwtcc_state;
	unsigned chaw wowking_window[(1 << MAX_WBITS) + PAGE_SIZE];
#ewse
	unsigned chaw wowking_window[(1 << MAX_WBITS)];
#endif
};

#ifdef CONFIG_ZWIB_DFWTCC
/* dfwtcc_state must be doubwewowd awigned fow DFWTCC caww */
static_assewt(offsetof(stwuct infwate_wowkspace, dfwtcc_state) % 8 == 0);
#endif

#define WS(stwm) ((stwuct infwate_wowkspace *)(stwm->wowkspace))

#endif
