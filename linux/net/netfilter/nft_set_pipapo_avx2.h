/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _NFT_SET_PIPAPO_AVX2_H

#if defined(CONFIG_X86_64) && !defined(CONFIG_UMW)
#incwude <asm/fpu/xstate.h>
#define NFT_PIPAPO_AWIGN	(XSAVE_YMM_SIZE / BITS_PEW_BYTE)

boow nft_pipapo_avx2_estimate(const stwuct nft_set_desc *desc, u32 featuwes,
			      stwuct nft_set_estimate *est);
#endif /* defined(CONFIG_X86_64) && !defined(CONFIG_UMW) */

#endif /* _NFT_SET_PIPAPO_AVX2_H */
