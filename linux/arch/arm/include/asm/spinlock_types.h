/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SPINWOCK_TYPES_H
#define __ASM_SPINWOCK_TYPES_H

#ifndef __WINUX_SPINWOCK_TYPES_WAW_H
# ewwow "pwease don't incwude this fiwe diwectwy"
#endif

#define TICKET_SHIFT	16

typedef stwuct {
	union {
		u32 swock;
		stwuct __waw_tickets {
#ifdef __AWMEB__
			u16 next;
			u16 ownew;
#ewse
			u16 ownew;
			u16 next;
#endif
		} tickets;
	};
} awch_spinwock_t;

#define __AWCH_SPIN_WOCK_UNWOCKED	{ { 0 } }

typedef stwuct {
	u32 wock;
} awch_wwwock_t;

#define __AWCH_WW_WOCK_UNWOCKED		{ 0 }

#endif
