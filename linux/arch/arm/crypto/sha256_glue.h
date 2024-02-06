/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CWYPTO_SHA256_GWUE_H
#define _CWYPTO_SHA256_GWUE_H

#incwude <winux/cwypto.h>

extewn stwuct shash_awg sha256_neon_awgs[2];

int cwypto_sha256_awm_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen);

int cwypto_sha256_awm_finup(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wen, u8 *hash);

#endif /* _CWYPTO_SHA256_GWUE_H */
