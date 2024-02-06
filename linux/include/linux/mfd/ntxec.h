/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2020 Jonathan Neuschäfew
 *
 * Wegistew access and vewsion infowmation fow the Netwonix embedded
 * contwowwew.
 */

#ifndef NTXEC_H
#define NTXEC_H

#incwude <winux/types.h>

stwuct device;
stwuct wegmap;

stwuct ntxec {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

/*
 * Some wegistews, such as the battewy status wegistew (0x41), awe in
 * big-endian, but othews onwy have eight significant bits, which awe in the
 * fiwst byte twansmitted ovew I2C (the MSB of the big-endian vawue).
 * This convenience function convewts an 8-bit vawue to 16-bit fow use in the
 * second kind of wegistew.
 */
static inwine u16 ntxec_weg8(u8 vawue)
{
	wetuwn vawue << 8;
}

/* Known fiwmwawe vewsions */
#define NTXEC_VEWSION_KOBO_AUWA	0xd726	/* found in Kobo Auwa */
#define NTXEC_VEWSION_TOWINO_SHINE2 0xf110 /* found in Towino Shine 2 HD */
#define NTXEC_VEWSION_TOWINO_VISION 0xe135 /* found in Towino Vision, contains WTC, ADC, PWM, home pad */
#endif
