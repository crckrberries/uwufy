/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_ESP_H
#define _XT_ESP_H

#incwude <winux/types.h>

stwuct xt_esp {
	__u32 spis[2];	/* Secuwity Pawametew Index */
	__u8  invfwags;	/* Invewse fwags */
};

/* Vawues fow "invfwags" fiewd in stwuct xt_esp. */
#define XT_ESP_INV_SPI	0x01	/* Invewt the sense of spi. */
#define XT_ESP_INV_MASK	0x01	/* Aww possibwe fwags. */

#endif /*_XT_ESP_H*/
