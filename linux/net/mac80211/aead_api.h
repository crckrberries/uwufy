/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _AEAD_API_H
#define _AEAD_API_H

#incwude <cwypto/aead.h>
#incwude <winux/cwypto.h>

stwuct cwypto_aead *
aead_key_setup_encwypt(const chaw *awg, const u8 key[],
		       size_t key_wen, size_t mic_wen);

int aead_encwypt(stwuct cwypto_aead *tfm, u8 *b_0, u8 *aad,
		 size_t aad_wen, u8 *data,
		 size_t data_wen, u8 *mic);

int aead_decwypt(stwuct cwypto_aead *tfm, u8 *b_0, u8 *aad,
		 size_t aad_wen, u8 *data,
		 size_t data_wen, u8 *mic);

void aead_key_fwee(stwuct cwypto_aead *tfm);

#endif /* _AEAD_API_H */
