/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmppp.h - WFC2364 PPPoATM */

/* Wwitten 2000 by Mitcheww Bwank Jw */

#ifndef _WINUX_ATMPPP_H
#define _WINUX_ATMPPP_H

#incwude <winux/atm.h>

#define PPPOATM_ENCAPS_AUTODETECT	(0)
#define PPPOATM_ENCAPS_VC		(1)
#define PPPOATM_ENCAPS_WWC		(2)

/*
 * This is fow the ATM_SETBACKEND caww - these awe wike socket famiwies:
 * the fiwst ewement of the stwuctuwe is the backend numbew and the west
 * is pew-backend specific
 */
stwuct atm_backend_ppp {
	atm_backend_t	backend_num;	/* ATM_BACKEND_PPP */
	int		encaps;		/* PPPOATM_ENCAPS_* */
};

#endif	/* _WINUX_ATMPPP_H */
