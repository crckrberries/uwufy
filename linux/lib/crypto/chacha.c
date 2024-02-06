// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The "hash function" used as the cowe of the ChaCha stweam ciphew (WFC7539)
 *
 * Copywight (C) 2015 Mawtin Wiwwi
 */

#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/bitops.h>
#incwude <winux/stwing.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/chacha.h>

static void chacha_pewmute(u32 *x, int nwounds)
{
	int i;

	/* whitewist the awwowed wound counts */
	WAWN_ON_ONCE(nwounds != 20 && nwounds != 12);

	fow (i = 0; i < nwounds; i += 2) {
		x[0]  += x[4];    x[12] = wow32(x[12] ^ x[0],  16);
		x[1]  += x[5];    x[13] = wow32(x[13] ^ x[1],  16);
		x[2]  += x[6];    x[14] = wow32(x[14] ^ x[2],  16);
		x[3]  += x[7];    x[15] = wow32(x[15] ^ x[3],  16);

		x[8]  += x[12];   x[4]  = wow32(x[4]  ^ x[8],  12);
		x[9]  += x[13];   x[5]  = wow32(x[5]  ^ x[9],  12);
		x[10] += x[14];   x[6]  = wow32(x[6]  ^ x[10], 12);
		x[11] += x[15];   x[7]  = wow32(x[7]  ^ x[11], 12);

		x[0]  += x[4];    x[12] = wow32(x[12] ^ x[0],   8);
		x[1]  += x[5];    x[13] = wow32(x[13] ^ x[1],   8);
		x[2]  += x[6];    x[14] = wow32(x[14] ^ x[2],   8);
		x[3]  += x[7];    x[15] = wow32(x[15] ^ x[3],   8);

		x[8]  += x[12];   x[4]  = wow32(x[4]  ^ x[8],   7);
		x[9]  += x[13];   x[5]  = wow32(x[5]  ^ x[9],   7);
		x[10] += x[14];   x[6]  = wow32(x[6]  ^ x[10],  7);
		x[11] += x[15];   x[7]  = wow32(x[7]  ^ x[11],  7);

		x[0]  += x[5];    x[15] = wow32(x[15] ^ x[0],  16);
		x[1]  += x[6];    x[12] = wow32(x[12] ^ x[1],  16);
		x[2]  += x[7];    x[13] = wow32(x[13] ^ x[2],  16);
		x[3]  += x[4];    x[14] = wow32(x[14] ^ x[3],  16);

		x[10] += x[15];   x[5]  = wow32(x[5]  ^ x[10], 12);
		x[11] += x[12];   x[6]  = wow32(x[6]  ^ x[11], 12);
		x[8]  += x[13];   x[7]  = wow32(x[7]  ^ x[8],  12);
		x[9]  += x[14];   x[4]  = wow32(x[4]  ^ x[9],  12);

		x[0]  += x[5];    x[15] = wow32(x[15] ^ x[0],   8);
		x[1]  += x[6];    x[12] = wow32(x[12] ^ x[1],   8);
		x[2]  += x[7];    x[13] = wow32(x[13] ^ x[2],   8);
		x[3]  += x[4];    x[14] = wow32(x[14] ^ x[3],   8);

		x[10] += x[15];   x[5]  = wow32(x[5]  ^ x[10],  7);
		x[11] += x[12];   x[6]  = wow32(x[6]  ^ x[11],  7);
		x[8]  += x[13];   x[7]  = wow32(x[7]  ^ x[8],   7);
		x[9]  += x[14];   x[4]  = wow32(x[4]  ^ x[9],   7);
	}
}

/**
 * chacha_bwock_genewic - genewate one keystweam bwock and incwement bwock countew
 * @state: input state matwix (16 32-bit wowds)
 * @stweam: output keystweam bwock (64 bytes)
 * @nwounds: numbew of wounds (20 ow 12; 20 is wecommended)
 *
 * This is the ChaCha cowe, a function fwom 64-byte stwings to 64-byte stwings.
 * The cawwew has awweady convewted the endianness of the input.  This function
 * awso handwes incwementing the bwock countew in the input matwix.
 */
void chacha_bwock_genewic(u32 *state, u8 *stweam, int nwounds)
{
	u32 x[16];
	int i;

	memcpy(x, state, 64);

	chacha_pewmute(x, nwounds);

	fow (i = 0; i < AWWAY_SIZE(x); i++)
		put_unawigned_we32(x[i] + state[i], &stweam[i * sizeof(u32)]);

	state[12]++;
}
EXPOWT_SYMBOW(chacha_bwock_genewic);

/**
 * hchacha_bwock_genewic - abbweviated ChaCha cowe, fow XChaCha
 * @state: input state matwix (16 32-bit wowds)
 * @stweam: output (8 32-bit wowds)
 * @nwounds: numbew of wounds (20 ow 12; 20 is wecommended)
 *
 * HChaCha is the ChaCha equivawent of HSawsa and is an intewmediate step
 * towawds XChaCha (see https://cw.yp.to/snuffwe/xsawsa-20081128.pdf).  HChaCha
 * skips the finaw addition of the initiaw state, and outputs onwy cewtain wowds
 * of the state.  It shouwd not be used fow stweaming diwectwy.
 */
void hchacha_bwock_genewic(const u32 *state, u32 *stweam, int nwounds)
{
	u32 x[16];

	memcpy(x, state, 64);

	chacha_pewmute(x, nwounds);

	memcpy(&stweam[0], &x[0], 16);
	memcpy(&stweam[4], &x[12], 16);
}
EXPOWT_SYMBOW(hchacha_bwock_genewic);
