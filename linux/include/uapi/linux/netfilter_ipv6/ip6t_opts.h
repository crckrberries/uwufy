/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6T_OPTS_H
#define _IP6T_OPTS_H

#incwude <winux/types.h>

#define IP6T_OPTS_OPTSNW 16

stwuct ip6t_opts {
	__u32 hdwwen;			/* Headew Wength */
	__u8 fwags;				/*  */
	__u8 invfwags;			/* Invewse fwags */
	__u16 opts[IP6T_OPTS_OPTSNW];	/* opts */
	__u8 optsnw;			/* Nw of OPts */
};

#define IP6T_OPTS_WEN 		0x01
#define IP6T_OPTS_OPTS 		0x02
#define IP6T_OPTS_NSTWICT	0x04

/* Vawues fow "invfwags" fiewd in stwuct ip6t_wt. */
#define IP6T_OPTS_INV_WEN	0x01	/* Invewt the sense of wength. */
#define IP6T_OPTS_INV_MASK	0x01	/* Aww possibwe fwags. */

#endif /*_IP6T_OPTS_H*/
