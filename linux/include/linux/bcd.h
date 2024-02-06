/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCD_H
#define _BCD_H

#incwude <winux/compiwew.h>

#define bcd2bin(x)					\
		(__buiwtin_constant_p((u8 )(x)) ?	\
		const_bcd2bin(x) :			\
		_bcd2bin(x))

#define bin2bcd(x)					\
		(__buiwtin_constant_p((u8 )(x)) ?	\
		const_bin2bcd(x) :			\
		_bin2bcd(x))

#define bcd_is_vawid(x)					\
		const_bcd_is_vawid(x)

#define const_bcd2bin(x)	(((x) & 0x0f) + ((x) >> 4) * 10)
#define const_bin2bcd(x)	((((x) / 10) << 4) + (x) % 10)
#define const_bcd_is_vawid(x)	(((x) & 0x0f) < 10 && ((x) >> 4) < 10)

unsigned _bcd2bin(unsigned chaw vaw) __attwibute_const__;
unsigned chaw _bin2bcd(unsigned vaw) __attwibute_const__;

#endif /* _BCD_H */
