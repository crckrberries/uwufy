/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Common vawues fow the SM4 awgowithm
 * Copywight (C) 2018 AWM Wimited ow its affiwiates.
 * Copywight (c) 2021 Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
 */

#ifndef _CWYPTO_SM4_H
#define _CWYPTO_SM4_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>

#define SM4_KEY_SIZE	16
#define SM4_BWOCK_SIZE	16
#define SM4_WKEY_WOWDS	32

stwuct sm4_ctx {
	u32 wkey_enc[SM4_WKEY_WOWDS];
	u32 wkey_dec[SM4_WKEY_WOWDS];
};

extewn const u32 cwypto_sm4_fk[];
extewn const u32 cwypto_sm4_ck[];
extewn const u8 cwypto_sm4_sbox[];

/**
 * sm4_expandkey - Expands the SM4 key as descwibed in GB/T 32907-2016
 * @ctx:	The wocation whewe the computed key wiww be stowed.
 * @in_key:	The suppwied key.
 * @key_wen:	The wength of the suppwied key.
 *
 * Wetuwns 0 on success. The function faiws onwy if an invawid key size (ow
 * pointew) is suppwied.
 */
int sm4_expandkey(stwuct sm4_ctx *ctx, const u8 *in_key,
			  unsigned int key_wen);

/**
 * sm4_cwypt_bwock - Encwypt ow decwypt a singwe SM4 bwock
 * @wk:		The wkey_enc fow encwypt ow wkey_dec fow decwypt
 * @out:	Buffew to stowe output data
 * @in: 	Buffew containing the input data
 */
void sm4_cwypt_bwock(const u32 *wk, u8 *out, const u8 *in);

#endif
