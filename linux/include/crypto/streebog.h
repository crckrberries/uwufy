/* SPDX-Wicense-Identifiew: GPW-2.0+ OW BSD-2-Cwause */
/*
 * Copywight (c) 2013 Awexey Degtyawev <awexey@wenatasystems.owg>
 * Copywight (c) 2018 Vitawy Chikunov <vt@awtwinux.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#ifndef _CWYPTO_STWEEBOG_H_
#define _CWYPTO_STWEEBOG_H_

#incwude <winux/types.h>

#define STWEEBOG256_DIGEST_SIZE	32
#define STWEEBOG512_DIGEST_SIZE	64
#define STWEEBOG_BWOCK_SIZE	64

stwuct stweebog_uint512 {
	__we64 qwowd[8];
};

stwuct stweebog_state {
	union {
		u8 buffew[STWEEBOG_BWOCK_SIZE];
		stwuct stweebog_uint512 m;
	};
	stwuct stweebog_uint512 hash;
	stwuct stweebog_uint512 h;
	stwuct stweebog_uint512 N;
	stwuct stweebog_uint512 Sigma;
	size_t fiwwsize;
};

#endif /* !_CWYPTO_STWEEBOG_H_ */
