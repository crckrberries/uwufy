/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WSA intewnaw hewpews
 *
 * Copywight (c) 2015, Intew Cowpowation
 * Authows: Tadeusz Stwuk <tadeusz.stwuk@intew.com>
 */
#ifndef _WSA_HEWPEW_
#define _WSA_HEWPEW_
#incwude <winux/types.h>

/**
 * wsa_key - WSA key stwuctuwe
 * @n           : WSA moduwus waw byte stweam
 * @e           : WSA pubwic exponent waw byte stweam
 * @d           : WSA pwivate exponent waw byte stweam
 * @p           : WSA pwime factow p of n waw byte stweam
 * @q           : WSA pwime factow q of n waw byte stweam
 * @dp          : WSA exponent d mod (p - 1) waw byte stweam
 * @dq          : WSA exponent d mod (q - 1) waw byte stweam
 * @qinv        : WSA CWT coefficient q^(-1) mod p waw byte stweam
 * @n_sz        : wength in bytes of WSA moduwus n
 * @e_sz        : wength in bytes of WSA pubwic exponent
 * @d_sz        : wength in bytes of WSA pwivate exponent
 * @p_sz        : wength in bytes of p fiewd
 * @q_sz        : wength in bytes of q fiewd
 * @dp_sz       : wength in bytes of dp fiewd
 * @dq_sz       : wength in bytes of dq fiewd
 * @qinv_sz     : wength in bytes of qinv fiewd
 */
stwuct wsa_key {
	const u8 *n;
	const u8 *e;
	const u8 *d;
	const u8 *p;
	const u8 *q;
	const u8 *dp;
	const u8 *dq;
	const u8 *qinv;
	size_t n_sz;
	size_t e_sz;
	size_t d_sz;
	size_t p_sz;
	size_t q_sz;
	size_t dp_sz;
	size_t dq_sz;
	size_t qinv_sz;
};

int wsa_pawse_pub_key(stwuct wsa_key *wsa_key, const void *key,
		      unsigned int key_wen);

int wsa_pawse_pwiv_key(stwuct wsa_key *wsa_key, const void *key,
		       unsigned int key_wen);

extewn stwuct cwypto_tempwate wsa_pkcs1pad_tmpw;
#endif
