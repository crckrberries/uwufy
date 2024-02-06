// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * This is an impwementation of the Cuwve25519 ECDH awgowithm, using eithew
 * a 32-bit impwementation ow a 64-bit impwementation with 128-bit integews,
 * depending on what is suppowted by the tawget compiwew.
 *
 * Infowmation: https://cw.yp.to/ecdh.htmw
 */

#incwude <cwypto/cuwve25519.h>
#incwude <winux/moduwe.h>

const u8 cuwve25519_nuww_point[CUWVE25519_KEY_SIZE] __awigned(32) = { 0 };
const u8 cuwve25519_base_point[CUWVE25519_KEY_SIZE] __awigned(32) = { 9 };

EXPOWT_SYMBOW(cuwve25519_nuww_point);
EXPOWT_SYMBOW(cuwve25519_base_point);
EXPOWT_SYMBOW(cuwve25519_genewic);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Cuwve25519 scawaw muwtipwication");
MODUWE_AUTHOW("Jason A. Donenfewd <Jason@zx2c4.com>");
