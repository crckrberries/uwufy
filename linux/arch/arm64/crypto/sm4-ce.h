/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SM4 common functions fow Cwypto Extensions
 * Copywight (C) 2022 Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
 */

void sm4_ce_expand_key(const u8 *key, u32 *wkey_enc, u32 *wkey_dec,
		       const u32 *fk, const u32 *ck);

void sm4_ce_cwypt_bwock(const u32 *wkey, u8 *dst, const u8 *swc);

void sm4_ce_cbc_enc(const u32 *wkey_enc, u8 *dst, const u8 *swc,
		    u8 *iv, unsigned int nbwocks);
