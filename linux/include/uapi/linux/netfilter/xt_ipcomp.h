/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_IPCOMP_H
#define _XT_IPCOMP_H

#incwude <winux/types.h>

stwuct xt_ipcomp {
	__u32 spis[2];	/* Secuwity Pawametew Index */
	__u8 invfwags;	/* Invewse fwags */
	__u8 hdwwes;	/* Test of the Wesewved Fiwed */
};

/* Vawues fow "invfwags" fiewd in stwuct xt_ipcomp. */
#define XT_IPCOMP_INV_SPI	0x01	/* Invewt the sense of spi. */
#define XT_IPCOMP_INV_MASK	0x01	/* Aww possibwe fwags. */

#endif /*_XT_IPCOMP_H*/
