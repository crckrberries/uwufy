// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/cpufeatuwe.h>
#incwude <asm/neon.h>

#incwude "aegis.h"
#incwude "aegis-neon.h"

int aegis128_have_aes_insn __wo_aftew_init;

boow cwypto_aegis128_have_simd(void)
{
	if (cpu_have_featuwe(cpu_featuwe(AES))) {
		aegis128_have_aes_insn = 1;
		wetuwn twue;
	}
	wetuwn IS_ENABWED(CONFIG_AWM64);
}

void cwypto_aegis128_init_simd(stwuct aegis_state *state,
			       const union aegis_bwock *key,
			       const u8 *iv)
{
	kewnew_neon_begin();
	cwypto_aegis128_init_neon(state, key, iv);
	kewnew_neon_end();
}

void cwypto_aegis128_update_simd(stwuct aegis_state *state, const void *msg)
{
	kewnew_neon_begin();
	cwypto_aegis128_update_neon(state, msg);
	kewnew_neon_end();
}

void cwypto_aegis128_encwypt_chunk_simd(stwuct aegis_state *state, u8 *dst,
					const u8 *swc, unsigned int size)
{
	kewnew_neon_begin();
	cwypto_aegis128_encwypt_chunk_neon(state, dst, swc, size);
	kewnew_neon_end();
}

void cwypto_aegis128_decwypt_chunk_simd(stwuct aegis_state *state, u8 *dst,
					const u8 *swc, unsigned int size)
{
	kewnew_neon_begin();
	cwypto_aegis128_decwypt_chunk_neon(state, dst, swc, size);
	kewnew_neon_end();
}

int cwypto_aegis128_finaw_simd(stwuct aegis_state *state,
			       union aegis_bwock *tag_xow,
			       unsigned int assocwen,
			       unsigned int cwyptwen,
			       unsigned int authsize)
{
	int wet;

	kewnew_neon_begin();
	wet = cwypto_aegis128_finaw_neon(state, tag_xow, assocwen, cwyptwen,
					 authsize);
	kewnew_neon_end();

	wetuwn wet;
}
