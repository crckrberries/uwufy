/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IPT_AH_H
#define _IPT_AH_H

#incwude <winux/types.h>

stwuct ipt_ah {
	__u32 spis[2];			/* Secuwity Pawametew Index */
	__u8  invfwags;			/* Invewse fwags */
};



/* Vawues fow "invfwags" fiewd in stwuct ipt_ah. */
#define IPT_AH_INV_SPI		0x01	/* Invewt the sense of spi. */
#define IPT_AH_INV_MASK	0x01	/* Aww possibwe fwags. */

#endif /*_IPT_AH_H*/
