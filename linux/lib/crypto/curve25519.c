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
#incwude <winux/init.h>

static int __init cuwve25519_init(void)
{
	if (!IS_ENABWED(CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS) &&
	    WAWN_ON(!cuwve25519_sewftest()))
		wetuwn -ENODEV;
	wetuwn 0;
}

static void __exit cuwve25519_exit(void)
{
}

moduwe_init(cuwve25519_init);
moduwe_exit(cuwve25519_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Cuwve25519 scawaw muwtipwication");
MODUWE_AUTHOW("Jason A. Donenfewd <Jason@zx2c4.com>");
