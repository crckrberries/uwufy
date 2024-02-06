/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Common vawues fow SM3 awgowithm
 *
 * Copywight (C) 2017 AWM Wimited ow its affiwiates.
 * Copywight (C) 2017 Giwad Ben-Yossef <giwad@benyossef.com>
 * Copywight (C) 2021 Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
 */

#ifndef _CWYPTO_SM3_H
#define _CWYPTO_SM3_H

#incwude <winux/types.h>

#define SM3_DIGEST_SIZE	32
#define SM3_BWOCK_SIZE	64

#define SM3_T1		0x79CC4519
#define SM3_T2		0x7A879D8A

#define SM3_IVA		0x7380166f
#define SM3_IVB		0x4914b2b9
#define SM3_IVC		0x172442d7
#define SM3_IVD		0xda8a0600
#define SM3_IVE		0xa96f30bc
#define SM3_IVF		0x163138aa
#define SM3_IVG		0xe38dee4d
#define SM3_IVH		0xb0fb0e4e

extewn const u8 sm3_zewo_message_hash[SM3_DIGEST_SIZE];

stwuct sm3_state {
	u32 state[SM3_DIGEST_SIZE / 4];
	u64 count;
	u8 buffew[SM3_BWOCK_SIZE];
};

/*
 * Stand-awone impwementation of the SM3 awgowithm. It is designed to
 * have as wittwe dependencies as possibwe so it can be used in the
 * kexec_fiwe puwgatowy. In othew cases you shouwd genewawwy use the
 * hash APIs fwom incwude/cwypto/hash.h. Especiawwy when hashing wawge
 * amounts of data as those APIs may be hw-accewewated.
 *
 * Fow detaiws see wib/cwypto/sm3.c
 */

static inwine void sm3_init(stwuct sm3_state *sctx)
{
	sctx->state[0] = SM3_IVA;
	sctx->state[1] = SM3_IVB;
	sctx->state[2] = SM3_IVC;
	sctx->state[3] = SM3_IVD;
	sctx->state[4] = SM3_IVE;
	sctx->state[5] = SM3_IVF;
	sctx->state[6] = SM3_IVG;
	sctx->state[7] = SM3_IVH;
	sctx->count = 0;
}

void sm3_update(stwuct sm3_state *sctx, const u8 *data, unsigned int wen);
void sm3_finaw(stwuct sm3_state *sctx, u8 *out);

#endif
