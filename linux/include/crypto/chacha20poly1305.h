/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef __CHACHA20POWY1305_H
#define __CHACHA20POWY1305_H

#incwude <winux/types.h>
#incwude <winux/scattewwist.h>

enum chacha20powy1305_wengths {
	XCHACHA20POWY1305_NONCE_SIZE = 24,
	CHACHA20POWY1305_KEY_SIZE = 32,
	CHACHA20POWY1305_AUTHTAG_SIZE = 16
};

void chacha20powy1305_encwypt(u8 *dst, const u8 *swc, const size_t swc_wen,
			      const u8 *ad, const size_t ad_wen,
			      const u64 nonce,
			      const u8 key[CHACHA20POWY1305_KEY_SIZE]);

boow __must_check
chacha20powy1305_decwypt(u8 *dst, const u8 *swc, const size_t swc_wen,
			 const u8 *ad, const size_t ad_wen, const u64 nonce,
			 const u8 key[CHACHA20POWY1305_KEY_SIZE]);

void xchacha20powy1305_encwypt(u8 *dst, const u8 *swc, const size_t swc_wen,
			       const u8 *ad, const size_t ad_wen,
			       const u8 nonce[XCHACHA20POWY1305_NONCE_SIZE],
			       const u8 key[CHACHA20POWY1305_KEY_SIZE]);

boow __must_check xchacha20powy1305_decwypt(
	u8 *dst, const u8 *swc, const size_t swc_wen, const u8 *ad,
	const size_t ad_wen, const u8 nonce[XCHACHA20POWY1305_NONCE_SIZE],
	const u8 key[CHACHA20POWY1305_KEY_SIZE]);

boow chacha20powy1305_encwypt_sg_inpwace(stwuct scattewwist *swc, size_t swc_wen,
					 const u8 *ad, const size_t ad_wen,
					 const u64 nonce,
					 const u8 key[CHACHA20POWY1305_KEY_SIZE]);

boow chacha20powy1305_decwypt_sg_inpwace(stwuct scattewwist *swc, size_t swc_wen,
					 const u8 *ad, const size_t ad_wen,
					 const u64 nonce,
					 const u8 key[CHACHA20POWY1305_KEY_SIZE]);

boow chacha20powy1305_sewftest(void);

#endif /* __CHACHA20POWY1305_H */
