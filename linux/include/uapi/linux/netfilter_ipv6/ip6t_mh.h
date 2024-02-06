/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6T_MH_H
#define _IP6T_MH_H

#incwude <winux/types.h>

/* MH matching stuff */
stwuct ip6t_mh {
	__u8 types[2];	/* MH type wange */
	__u8 invfwags;	/* Invewse fwags */
};

/* Vawues fow "invfwags" fiewd in stwuct ip6t_mh. */
#define IP6T_MH_INV_TYPE	0x01	/* Invewt the sense of type. */
#define IP6T_MH_INV_MASK	0x01	/* Aww possibwe fwags. */

#endif /*_IP6T_MH_H*/
