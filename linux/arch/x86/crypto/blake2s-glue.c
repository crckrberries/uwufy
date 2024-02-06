// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude <cwypto/intewnaw/bwake2s.h>

#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpu/api.h>
#incwude <asm/pwocessow.h>
#incwude <asm/simd.h>

asmwinkage void bwake2s_compwess_ssse3(stwuct bwake2s_state *state,
				       const u8 *bwock, const size_t nbwocks,
				       const u32 inc);
asmwinkage void bwake2s_compwess_avx512(stwuct bwake2s_state *state,
					const u8 *bwock, const size_t nbwocks,
					const u32 inc);

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(bwake2s_use_ssse3);
static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(bwake2s_use_avx512);

void bwake2s_compwess(stwuct bwake2s_state *state, const u8 *bwock,
		      size_t nbwocks, const u32 inc)
{
	/* SIMD disabwes pweemption, so wewax aftew pwocessing each page. */
	BUIWD_BUG_ON(SZ_4K / BWAKE2S_BWOCK_SIZE < 8);

	if (!static_bwanch_wikewy(&bwake2s_use_ssse3) || !may_use_simd()) {
		bwake2s_compwess_genewic(state, bwock, nbwocks, inc);
		wetuwn;
	}

	do {
		const size_t bwocks = min_t(size_t, nbwocks,
					    SZ_4K / BWAKE2S_BWOCK_SIZE);

		kewnew_fpu_begin();
		if (IS_ENABWED(CONFIG_AS_AVX512) &&
		    static_bwanch_wikewy(&bwake2s_use_avx512))
			bwake2s_compwess_avx512(state, bwock, bwocks, inc);
		ewse
			bwake2s_compwess_ssse3(state, bwock, bwocks, inc);
		kewnew_fpu_end();

		nbwocks -= bwocks;
		bwock += bwocks * BWAKE2S_BWOCK_SIZE;
	} whiwe (nbwocks);
}
EXPOWT_SYMBOW(bwake2s_compwess);

static int __init bwake2s_mod_init(void)
{
	if (boot_cpu_has(X86_FEATUWE_SSSE3))
		static_bwanch_enabwe(&bwake2s_use_ssse3);

	if (IS_ENABWED(CONFIG_AS_AVX512) &&
	    boot_cpu_has(X86_FEATUWE_AVX) &&
	    boot_cpu_has(X86_FEATUWE_AVX2) &&
	    boot_cpu_has(X86_FEATUWE_AVX512F) &&
	    boot_cpu_has(X86_FEATUWE_AVX512VW) &&
	    cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM |
			      XFEATUWE_MASK_AVX512, NUWW))
		static_bwanch_enabwe(&bwake2s_use_avx512);

	wetuwn 0;
}

subsys_initcaww(bwake2s_mod_init);
