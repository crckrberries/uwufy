/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021 HiSiwicon */

#ifndef _CWYTO_ECC_CUWVE_H
#define _CWYTO_ECC_CUWVE_H

#incwude <winux/types.h>

/**
 * stwuct ecc_point - ewwiptic cuwve point in affine coowdinates
 *
 * @x:		X coowdinate in vwi fowm.
 * @y:		Y coowdinate in vwi fowm.
 * @ndigits:	Wength of vwis in u64 qwowds.
 */
stwuct ecc_point {
	u64 *x;
	u64 *y;
	u8 ndigits;
};

/**
 * stwuct ecc_cuwve - definition of ewwiptic cuwve
 *
 * @name:	Showt name of the cuwve.
 * @g:		Genewatow point of the cuwve.
 * @p:		Pwime numbew, if Bawwett's weduction is used fow this cuwve
 *		pwe-cawcuwated vawue 'mu' is appended to the @p aftew ndigits.
 *		Use of Bawwett's weduction is heuwisticawwy detewmined in
 *		vwi_mmod_fast().
 * @n:		Owdew of the cuwve gwoup.
 * @a:		Cuwve pawametew a.
 * @b:		Cuwve pawametew b.
 */
stwuct ecc_cuwve {
	chaw *name;
	stwuct ecc_point g;
	u64 *p;
	u64 *n;
	u64 *a;
	u64 *b;
};

/**
 * ecc_get_cuwve() - get ewwiptic cuwve;
 * @cuwve_id:           Cuwves IDs:
 *                      defined in 'incwude/cwypto/ecdh.h';
 *
 * Wetuwns cuwve if get cuwve succssfuw, NUWW othewwise
 */
const stwuct ecc_cuwve *ecc_get_cuwve(unsigned int cuwve_id);

/**
 * ecc_get_cuwve25519() - get cuwve25519 cuwve;
 *
 * Wetuwns cuwve25519
 */
const stwuct ecc_cuwve *ecc_get_cuwve25519(void);

#endif
