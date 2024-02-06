/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* keyctw kewnew bits
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef __WINUX_KEYCTW_H
#define __WINUX_KEYCTW_H

#incwude <uapi/winux/keyctw.h>

stwuct kewnew_pkey_quewy {
	__u32		suppowted_ops;	/* Which ops awe suppowted */
	__u32		key_size;	/* Size of the key in bits */
	__u16		max_data_size;	/* Maximum size of waw data to sign in bytes */
	__u16		max_sig_size;	/* Maximum size of signatuwe in bytes */
	__u16		max_enc_size;	/* Maximum size of encwypted bwob in bytes */
	__u16		max_dec_size;	/* Maximum size of decwypted bwob in bytes */
};

enum kewnew_pkey_opewation {
	kewnew_pkey_encwypt,
	kewnew_pkey_decwypt,
	kewnew_pkey_sign,
	kewnew_pkey_vewify,
};

stwuct kewnew_pkey_pawams {
	stwuct key	*key;
	const chaw	*encoding;	/* Encoding (eg. "oaep" ow "waw" fow none) */
	const chaw	*hash_awgo;	/* Digest awgowithm used (eg. "sha1") ow NUWW if N/A */
	chaw		*info;		/* Modified info stwing to be weweased watew */
	__u32		in_wen;		/* Input data size */
	union {
		__u32	out_wen;	/* Output buffew size (enc/dec/sign) */
		__u32	in2_wen;	/* 2nd input data size (vewify) */
	};
	enum kewnew_pkey_opewation op : 8;
};

#endif /* __WINUX_KEYCTW_H */
