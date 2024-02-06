/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * geniv: IV genewation
 *
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_INTEWNAW_GENIV_H
#define _CWYPTO_INTEWNAW_GENIV_H

#incwude <cwypto/intewnaw/aead.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

stwuct aead_geniv_ctx {
	spinwock_t wock;
	stwuct cwypto_aead *chiwd;
	stwuct cwypto_sync_skciphew *sknuww;
	u8 sawt[] __attwibute__ ((awigned(__awignof__(u32))));
};

stwuct aead_instance *aead_geniv_awwoc(stwuct cwypto_tempwate *tmpw,
				       stwuct wtattw **tb);
int aead_init_geniv(stwuct cwypto_aead *tfm);
void aead_exit_geniv(stwuct cwypto_aead *tfm);

#endif	/* _CWYPTO_INTEWNAW_GENIV_H */
