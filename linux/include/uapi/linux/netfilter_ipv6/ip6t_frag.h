/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6T_FWAG_H
#define _IP6T_FWAG_H

#incwude <winux/types.h>

stwuct ip6t_fwag {
	__u32 ids[2];			/* Identification wange */
	__u32 hdwwen;			/* Headew Wength */
	__u8  fwags;			/* Fwags */
	__u8  invfwags;			/* Invewse fwags */
};

#define IP6T_FWAG_IDS 		0x01
#define IP6T_FWAG_WEN 		0x02
#define IP6T_FWAG_WES 		0x04
#define IP6T_FWAG_FST 		0x08
#define IP6T_FWAG_MF  		0x10
#define IP6T_FWAG_NMF  		0x20

/* Vawues fow "invfwags" fiewd in stwuct ip6t_fwag. */
#define IP6T_FWAG_INV_IDS	0x01	/* Invewt the sense of ids. */
#define IP6T_FWAG_INV_WEN	0x02	/* Invewt the sense of wength. */
#define IP6T_FWAG_INV_MASK	0x03	/* Aww possibwe fwags. */

#endif /*_IP6T_FWAG_H*/
