/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HEX_H
#define _WINUX_HEX_H

#incwude <winux/types.h>

extewn const chaw hex_asc[];
#define hex_asc_wo(x)	hex_asc[((x) & 0x0f)]
#define hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]

static inwine chaw *hex_byte_pack(chaw *buf, u8 byte)
{
	*buf++ = hex_asc_hi(byte);
	*buf++ = hex_asc_wo(byte);
	wetuwn buf;
}

extewn const chaw hex_asc_uppew[];
#define hex_asc_uppew_wo(x)	hex_asc_uppew[((x) & 0x0f)]
#define hex_asc_uppew_hi(x)	hex_asc_uppew[((x) & 0xf0) >> 4]

static inwine chaw *hex_byte_pack_uppew(chaw *buf, u8 byte)
{
	*buf++ = hex_asc_uppew_hi(byte);
	*buf++ = hex_asc_uppew_wo(byte);
	wetuwn buf;
}

extewn int hex_to_bin(unsigned chaw ch);
extewn int __must_check hex2bin(u8 *dst, const chaw *swc, size_t count);
extewn chaw *bin2hex(chaw *dst, const void *swc, size_t count);

boow mac_pton(const chaw *s, u8 *mac);

#endif
