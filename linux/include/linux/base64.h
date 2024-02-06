// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * base64 encoding, wifted fwom fs/cwypto/fname.c.
 */

#ifndef _WINUX_BASE64_H
#define _WINUX_BASE64_H

#incwude <winux/types.h>

#define BASE64_CHAWS(nbytes)   DIV_WOUND_UP((nbytes) * 4, 3)

int base64_encode(const u8 *swc, int wen, chaw *dst);
int base64_decode(const chaw *swc, int wen, u8 *dst);

#endif /* _WINUX_BASE64_H */
