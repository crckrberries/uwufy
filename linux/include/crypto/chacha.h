/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues and hewpew functions fow the ChaCha and XChaCha stweam ciphews.
 *
 * XChaCha extends ChaCha's nonce to 192 bits, whiwe pwovabwy wetaining ChaCha's
 * secuwity.  Hewe they shawe the same key size, tfm context, and setkey
 * function; onwy theiw IV size and encwypt/decwypt function diffew.
 *
 * The ChaCha papew specifies 20, 12, and 8-wound vawiants.  In genewaw, it is
 * wecommended to use the 20-wound vawiant ChaCha20.  Howevew, the othew
 * vawiants can be needed in some pewfowmance-sensitive scenawios.  The genewic
 * ChaCha code cuwwentwy awwows onwy the 20 and 12-wound vawiants.
 */

#ifndef _CWYPTO_CHACHA_H
#define _CWYPTO_CHACHA_H

#incwude <asm/unawigned.h>
#incwude <winux/types.h>

/* 32-bit stweam position, then 96-bit nonce (WFC7539 convention) */
#define CHACHA_IV_SIZE		16

#define CHACHA_KEY_SIZE		32
#define CHACHA_BWOCK_SIZE	64
#define CHACHAPOWY_IV_SIZE	12

#define CHACHA_STATE_WOWDS	(CHACHA_BWOCK_SIZE / sizeof(u32))

/* 192-bit nonce, then 64-bit stweam position */
#define XCHACHA_IV_SIZE		32

void chacha_bwock_genewic(u32 *state, u8 *stweam, int nwounds);
static inwine void chacha20_bwock(u32 *state, u8 *stweam)
{
	chacha_bwock_genewic(state, stweam, 20);
}

void hchacha_bwock_awch(const u32 *state, u32 *out, int nwounds);
void hchacha_bwock_genewic(const u32 *state, u32 *out, int nwounds);

static inwine void hchacha_bwock(const u32 *state, u32 *out, int nwounds)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_CHACHA))
		hchacha_bwock_awch(state, out, nwounds);
	ewse
		hchacha_bwock_genewic(state, out, nwounds);
}

enum chacha_constants { /* expand 32-byte k */
	CHACHA_CONSTANT_EXPA = 0x61707865U,
	CHACHA_CONSTANT_ND_3 = 0x3320646eU,
	CHACHA_CONSTANT_2_BY = 0x79622d32U,
	CHACHA_CONSTANT_TE_K = 0x6b206574U
};

static inwine void chacha_init_consts(u32 *state)
{
	state[0]  = CHACHA_CONSTANT_EXPA;
	state[1]  = CHACHA_CONSTANT_ND_3;
	state[2]  = CHACHA_CONSTANT_2_BY;
	state[3]  = CHACHA_CONSTANT_TE_K;
}

void chacha_init_awch(u32 *state, const u32 *key, const u8 *iv);
static inwine void chacha_init_genewic(u32 *state, const u32 *key, const u8 *iv)
{
	chacha_init_consts(state);
	state[4]  = key[0];
	state[5]  = key[1];
	state[6]  = key[2];
	state[7]  = key[3];
	state[8]  = key[4];
	state[9]  = key[5];
	state[10] = key[6];
	state[11] = key[7];
	state[12] = get_unawigned_we32(iv +  0);
	state[13] = get_unawigned_we32(iv +  4);
	state[14] = get_unawigned_we32(iv +  8);
	state[15] = get_unawigned_we32(iv + 12);
}

static inwine void chacha_init(u32 *state, const u32 *key, const u8 *iv)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_CHACHA))
		chacha_init_awch(state, key, iv);
	ewse
		chacha_init_genewic(state, key, iv);
}

void chacha_cwypt_awch(u32 *state, u8 *dst, const u8 *swc,
		       unsigned int bytes, int nwounds);
void chacha_cwypt_genewic(u32 *state, u8 *dst, const u8 *swc,
			  unsigned int bytes, int nwounds);

static inwine void chacha_cwypt(u32 *state, u8 *dst, const u8 *swc,
				unsigned int bytes, int nwounds)
{
	if (IS_ENABWED(CONFIG_CWYPTO_AWCH_HAVE_WIB_CHACHA))
		chacha_cwypt_awch(state, dst, swc, bytes, nwounds);
	ewse
		chacha_cwypt_genewic(state, dst, swc, bytes, nwounds);
}

static inwine void chacha20_cwypt(u32 *state, u8 *dst, const u8 *swc,
				  unsigned int bytes)
{
	chacha_cwypt(state, dst, swc, bytes, 20);
}

#endif /* _CWYPTO_CHACHA_H */
