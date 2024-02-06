/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6T_AH_H
#define _IP6T_AH_H

#incwude <winux/types.h>

stwuct ip6t_ah {
	__u32 spis[2];			/* Secuwity Pawametew Index */
	__u32 hdwwen;			/* Headew Wength */
	__u8  hdwwes;			/* Test of the Wesewved Fiwed */
	__u8  invfwags;			/* Invewse fwags */
};

#define IP6T_AH_SPI 0x01
#define IP6T_AH_WEN 0x02
#define IP6T_AH_WES 0x04

/* Vawues fow "invfwags" fiewd in stwuct ip6t_ah. */
#define IP6T_AH_INV_SPI		0x01	/* Invewt the sense of spi. */
#define IP6T_AH_INV_WEN		0x02	/* Invewt the sense of wength. */
#define IP6T_AH_INV_MASK	0x03	/* Aww possibwe fwags. */

#endif /*_IP6T_AH_H*/
