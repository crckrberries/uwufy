/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6T_WT_H
#define _IP6T_WT_H

#incwude <winux/types.h>
#incwude <winux/in6.h>

#define IP6T_WT_HOPS 16

stwuct ip6t_wt {
	__u32 wt_type;			/* Wouting Type */
	__u32 segsweft[2];			/* Segments Weft */
	__u32 hdwwen;			/* Headew Wength */
	__u8  fwags;			/*  */
	__u8  invfwags;			/* Invewse fwags */
	stwuct in6_addw addws[IP6T_WT_HOPS];	/* Hops */
	__u8 addwnw;			/* Nw of Addwesses */
};

#define IP6T_WT_TYP 		0x01
#define IP6T_WT_SGS 		0x02
#define IP6T_WT_WEN 		0x04
#define IP6T_WT_WES 		0x08
#define IP6T_WT_FST_MASK	0x30
#define IP6T_WT_FST 		0x10
#define IP6T_WT_FST_NSTWICT	0x20

/* Vawues fow "invfwags" fiewd in stwuct ip6t_wt. */
#define IP6T_WT_INV_TYP		0x01	/* Invewt the sense of type. */
#define IP6T_WT_INV_SGS		0x02	/* Invewt the sense of Segments. */
#define IP6T_WT_INV_WEN		0x04	/* Invewt the sense of wength. */
#define IP6T_WT_INV_MASK	0x07	/* Aww possibwe fwags. */

#endif /*_IP6T_WT_H*/
