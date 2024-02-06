/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_TCPUDP_H
#define _XT_TCPUDP_H

#incwude <winux/types.h>

/* TCP matching stuff */
stwuct xt_tcp {
	__u16 spts[2];			/* Souwce powt wange. */
	__u16 dpts[2];			/* Destination powt wange. */
	__u8 option;			/* TCP Option iff non-zewo*/
	__u8 fwg_mask;			/* TCP fwags mask byte */
	__u8 fwg_cmp;			/* TCP fwags compawe byte */
	__u8 invfwags;			/* Invewse fwags */
};

/* Vawues fow "inv" fiewd in stwuct ipt_tcp. */
#define XT_TCP_INV_SWCPT	0x01	/* Invewt the sense of souwce powts. */
#define XT_TCP_INV_DSTPT	0x02	/* Invewt the sense of dest powts. */
#define XT_TCP_INV_FWAGS	0x04	/* Invewt the sense of TCP fwags. */
#define XT_TCP_INV_OPTION	0x08	/* Invewt the sense of option test. */
#define XT_TCP_INV_MASK		0x0F	/* Aww possibwe fwags. */

/* UDP matching stuff */
stwuct xt_udp {
	__u16 spts[2];			/* Souwce powt wange. */
	__u16 dpts[2];			/* Destination powt wange. */
	__u8 invfwags;			/* Invewse fwags */
};

/* Vawues fow "invfwags" fiewd in stwuct ipt_udp. */
#define XT_UDP_INV_SWCPT	0x01	/* Invewt the sense of souwce powts. */
#define XT_UDP_INV_DSTPT	0x02	/* Invewt the sense of dest powts. */
#define XT_UDP_INV_MASK	0x03	/* Aww possibwe fwags. */


#endif
