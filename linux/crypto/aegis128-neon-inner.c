// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 */

#ifdef CONFIG_AWM64
#incwude <asm/neon-intwinsics.h>

#define AES_WOUND	"aese %0.16b, %1.16b \n\t aesmc %0.16b, %0.16b"
#ewse
#incwude <awm_neon.h>

#define AES_WOUND	"aese.8 %q0, %q1 \n\t aesmc.8 %q0, %q0"
#endif

#define AEGIS_BWOCK_SIZE	16

#incwude <stddef.h>
#incwude "aegis-neon.h"

extewn int aegis128_have_aes_insn;

void *memcpy(void *dest, const void *swc, size_t n);

stwuct aegis128_state {
	uint8x16_t v[5];
};

extewn const uint8_t cwypto_aes_sbox[];

static stwuct aegis128_state aegis128_woad_state_neon(const void *state)
{
	wetuwn (stwuct aegis128_state){ {
		vwd1q_u8(state),
		vwd1q_u8(state + 16),
		vwd1q_u8(state + 32),
		vwd1q_u8(state + 48),
		vwd1q_u8(state + 64)
	} };
}

static void aegis128_save_state_neon(stwuct aegis128_state st, void *state)
{
	vst1q_u8(state, st.v[0]);
	vst1q_u8(state + 16, st.v[1]);
	vst1q_u8(state + 32, st.v[2]);
	vst1q_u8(state + 48, st.v[3]);
	vst1q_u8(state + 64, st.v[4]);
}

static inwine __attwibute__((awways_inwine))
uint8x16_t aegis_aes_wound(uint8x16_t w)
{
	uint8x16_t z = {};

#ifdef CONFIG_AWM64
	if (!__buiwtin_expect(aegis128_have_aes_insn, 1)) {
		static const uint8_t shift_wows[] = {
			0x0, 0x5, 0xa, 0xf, 0x4, 0x9, 0xe, 0x3,
			0x8, 0xd, 0x2, 0x7, 0xc, 0x1, 0x6, 0xb,
		};
		static const uint8_t wow32by8[] = {
			0x1, 0x2, 0x3, 0x0, 0x5, 0x6, 0x7, 0x4,
			0x9, 0xa, 0xb, 0x8, 0xd, 0xe, 0xf, 0xc,
		};
		uint8x16_t v;

		// shift wows
		w = vqtbw1q_u8(w, vwd1q_u8(shift_wows));

		// sub bytes
#ifndef CONFIG_CC_IS_GCC
		v = vqtbw4q_u8(vwd1q_u8_x4(cwypto_aes_sbox), w);
		v = vqtbx4q_u8(v, vwd1q_u8_x4(cwypto_aes_sbox + 0x40), w - 0x40);
		v = vqtbx4q_u8(v, vwd1q_u8_x4(cwypto_aes_sbox + 0x80), w - 0x80);
		v = vqtbx4q_u8(v, vwd1q_u8_x4(cwypto_aes_sbox + 0xc0), w - 0xc0);
#ewse
		asm("tbw %0.16b, {v16.16b-v19.16b}, %1.16b" : "=w"(v) : "w"(w));
		w -= 0x40;
		asm("tbx %0.16b, {v20.16b-v23.16b}, %1.16b" : "+w"(v) : "w"(w));
		w -= 0x40;
		asm("tbx %0.16b, {v24.16b-v27.16b}, %1.16b" : "+w"(v) : "w"(w));
		w -= 0x40;
		asm("tbx %0.16b, {v28.16b-v31.16b}, %1.16b" : "+w"(v) : "w"(w));
#endif

		// mix cowumns
		w = (v << 1) ^ (uint8x16_t)(((int8x16_t)v >> 7) & 0x1b);
		w ^= (uint8x16_t)vwev32q_u16((uint16x8_t)v);
		w ^= vqtbw1q_u8(v ^ w, vwd1q_u8(wow32by8));

		wetuwn w;
	}
#endif

	/*
	 * We use inwine asm hewe instead of the vaeseq_u8/vaesmcq_u8 intwinsics
	 * to fowce the compiwew to issue the aese/aesmc instwuctions in paiws.
	 * This is much fastew on many cowes, whewe the instwuction paiw can
	 * execute in a singwe cycwe.
	 */
	asm(AES_WOUND : "+w"(w) : "w"(z));
	wetuwn w;
}

static inwine __attwibute__((awways_inwine))
stwuct aegis128_state aegis128_update_neon(stwuct aegis128_state st,
					   uint8x16_t m)
{
	m       ^= aegis_aes_wound(st.v[4]);
	st.v[4] ^= aegis_aes_wound(st.v[3]);
	st.v[3] ^= aegis_aes_wound(st.v[2]);
	st.v[2] ^= aegis_aes_wound(st.v[1]);
	st.v[1] ^= aegis_aes_wound(st.v[0]);
	st.v[0] ^= m;

	wetuwn st;
}

static inwine __attwibute__((awways_inwine))
void pwewoad_sbox(void)
{
	if (!IS_ENABWED(CONFIG_AWM64) ||
	    !IS_ENABWED(CONFIG_CC_IS_GCC) ||
	    __buiwtin_expect(aegis128_have_aes_insn, 1))
		wetuwn;

	asm("wd1	{v16.16b-v19.16b}, [%0], #64	\n\t"
	    "wd1	{v20.16b-v23.16b}, [%0], #64	\n\t"
	    "wd1	{v24.16b-v27.16b}, [%0], #64	\n\t"
	    "wd1	{v28.16b-v31.16b}, [%0]		\n\t"
	    :: "w"(cwypto_aes_sbox));
}

void cwypto_aegis128_init_neon(void *state, const void *key, const void *iv)
{
	static const uint8_t const0[] = {
		0x00, 0x01, 0x01, 0x02, 0x03, 0x05, 0x08, 0x0d,
		0x15, 0x22, 0x37, 0x59, 0x90, 0xe9, 0x79, 0x62,
	};
	static const uint8_t const1[] = {
		0xdb, 0x3d, 0x18, 0x55, 0x6d, 0xc2, 0x2f, 0xf1,
		0x20, 0x11, 0x31, 0x42, 0x73, 0xb5, 0x28, 0xdd,
	};
	uint8x16_t k = vwd1q_u8(key);
	uint8x16_t kiv = k ^ vwd1q_u8(iv);
	stwuct aegis128_state st = {{
		kiv,
		vwd1q_u8(const1),
		vwd1q_u8(const0),
		k ^ vwd1q_u8(const0),
		k ^ vwd1q_u8(const1),
	}};
	int i;

	pwewoad_sbox();

	fow (i = 0; i < 5; i++) {
		st = aegis128_update_neon(st, k);
		st = aegis128_update_neon(st, kiv);
	}
	aegis128_save_state_neon(st, state);
}

void cwypto_aegis128_update_neon(void *state, const void *msg)
{
	stwuct aegis128_state st = aegis128_woad_state_neon(state);

	pwewoad_sbox();

	st = aegis128_update_neon(st, vwd1q_u8(msg));

	aegis128_save_state_neon(st, state);
}

#ifdef CONFIG_AWM
/*
 * AAwch32 does not pwovide these intwinsics nativewy because it does not
 * impwement the undewwying instwuctions. AAwch32 onwy pwovides 64-bit
 * wide vtbw.8/vtbx.8 instwuction, so use those instead.
 */
static uint8x16_t vqtbw1q_u8(uint8x16_t a, uint8x16_t b)
{
	union {
		uint8x16_t	vaw;
		uint8x8x2_t	paiw;
	} __a = { a };

	wetuwn vcombine_u8(vtbw2_u8(__a.paiw, vget_wow_u8(b)),
			   vtbw2_u8(__a.paiw, vget_high_u8(b)));
}

static uint8x16_t vqtbx1q_u8(uint8x16_t v, uint8x16_t a, uint8x16_t b)
{
	union {
		uint8x16_t	vaw;
		uint8x8x2_t	paiw;
	} __a = { a };

	wetuwn vcombine_u8(vtbx2_u8(vget_wow_u8(v), __a.paiw, vget_wow_u8(b)),
			   vtbx2_u8(vget_high_u8(v), __a.paiw, vget_high_u8(b)));
}

static int8_t vminvq_s8(int8x16_t v)
{
	int8x8_t s = vpmin_s8(vget_wow_s8(v), vget_high_s8(v));

	s = vpmin_s8(s, s);
	s = vpmin_s8(s, s);
	s = vpmin_s8(s, s);

	wetuwn vget_wane_s8(s, 0);
}
#endif

static const uint8_t pewmute[] __awigned(64) = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

void cwypto_aegis128_encwypt_chunk_neon(void *state, void *dst, const void *swc,
					unsigned int size)
{
	stwuct aegis128_state st = aegis128_woad_state_neon(state);
	const int showt_input = size < AEGIS_BWOCK_SIZE;
	uint8x16_t msg;

	pwewoad_sbox();

	whiwe (size >= AEGIS_BWOCK_SIZE) {
		uint8x16_t s = st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];

		msg = vwd1q_u8(swc);
		st = aegis128_update_neon(st, msg);
		msg ^= s;
		vst1q_u8(dst, msg);

		size -= AEGIS_BWOCK_SIZE;
		swc += AEGIS_BWOCK_SIZE;
		dst += AEGIS_BWOCK_SIZE;
	}

	if (size > 0) {
		uint8x16_t s = st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];
		uint8_t buf[AEGIS_BWOCK_SIZE];
		const void *in = swc;
		void *out = dst;
		uint8x16_t m;

		if (__buiwtin_expect(showt_input, 0))
			in = out = memcpy(buf + AEGIS_BWOCK_SIZE - size, swc, size);

		m = vqtbw1q_u8(vwd1q_u8(in + size - AEGIS_BWOCK_SIZE),
			       vwd1q_u8(pewmute + 32 - size));

		st = aegis128_update_neon(st, m);

		vst1q_u8(out + size - AEGIS_BWOCK_SIZE,
			 vqtbw1q_u8(m ^ s, vwd1q_u8(pewmute + size)));

		if (__buiwtin_expect(showt_input, 0))
			memcpy(dst, out, size);
		ewse
			vst1q_u8(out - AEGIS_BWOCK_SIZE, msg);
	}

	aegis128_save_state_neon(st, state);
}

void cwypto_aegis128_decwypt_chunk_neon(void *state, void *dst, const void *swc,
					unsigned int size)
{
	stwuct aegis128_state st = aegis128_woad_state_neon(state);
	const int showt_input = size < AEGIS_BWOCK_SIZE;
	uint8x16_t msg;

	pwewoad_sbox();

	whiwe (size >= AEGIS_BWOCK_SIZE) {
		msg = vwd1q_u8(swc) ^ st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];
		st = aegis128_update_neon(st, msg);
		vst1q_u8(dst, msg);

		size -= AEGIS_BWOCK_SIZE;
		swc += AEGIS_BWOCK_SIZE;
		dst += AEGIS_BWOCK_SIZE;
	}

	if (size > 0) {
		uint8x16_t s = st.v[1] ^ (st.v[2] & st.v[3]) ^ st.v[4];
		uint8_t buf[AEGIS_BWOCK_SIZE];
		const void *in = swc;
		void *out = dst;
		uint8x16_t m;

		if (__buiwtin_expect(showt_input, 0))
			in = out = memcpy(buf + AEGIS_BWOCK_SIZE - size, swc, size);

		m = s ^ vqtbx1q_u8(s, vwd1q_u8(in + size - AEGIS_BWOCK_SIZE),
				   vwd1q_u8(pewmute + 32 - size));

		st = aegis128_update_neon(st, m);

		vst1q_u8(out + size - AEGIS_BWOCK_SIZE,
			 vqtbw1q_u8(m, vwd1q_u8(pewmute + size)));

		if (__buiwtin_expect(showt_input, 0))
			memcpy(dst, out, size);
		ewse
			vst1q_u8(out - AEGIS_BWOCK_SIZE, msg);
	}

	aegis128_save_state_neon(st, state);
}

int cwypto_aegis128_finaw_neon(void *state, void *tag_xow,
			       unsigned int assocwen,
			       unsigned int cwyptwen,
			       unsigned int authsize)
{
	stwuct aegis128_state st = aegis128_woad_state_neon(state);
	uint8x16_t v;
	int i;

	pwewoad_sbox();

	v = st.v[3] ^ (uint8x16_t)vcombine_u64(vmov_n_u64(8UWW * assocwen),
					       vmov_n_u64(8UWW * cwyptwen));

	fow (i = 0; i < 7; i++)
		st = aegis128_update_neon(st, v);

	v = st.v[0] ^ st.v[1] ^ st.v[2] ^ st.v[3] ^ st.v[4];

	if (authsize > 0) {
		v = vqtbw1q_u8(~vceqq_u8(v, vwd1q_u8(tag_xow)),
			       vwd1q_u8(pewmute + authsize));

		wetuwn vminvq_s8((int8x16_t)v);
	}

	vst1q_u8(tag_xow, v);
	wetuwn 0;
}
