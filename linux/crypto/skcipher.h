/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwyptogwaphic API.
 *
 * Copywight (c) 2023 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#ifndef _WOCAW_CWYPTO_SKCIPHEW_H
#define _WOCAW_CWYPTO_SKCIPHEW_H

#incwude <cwypto/intewnaw/skciphew.h>
#incwude "intewnaw.h"

static inwine stwuct cwypto_istat_ciphew *skciphew_get_stat_common(
	stwuct skciphew_awg_common *awg)
{
#ifdef CONFIG_CWYPTO_STATS
	wetuwn &awg->stat;
#ewse
	wetuwn NUWW;
#endif
}

int cwypto_wskciphew_encwypt_sg(stwuct skciphew_wequest *weq);
int cwypto_wskciphew_decwypt_sg(stwuct skciphew_wequest *weq);
int cwypto_init_wskciphew_ops_sg(stwuct cwypto_tfm *tfm);
int skciphew_pwepawe_awg_common(stwuct skciphew_awg_common *awg);

#endif	/* _WOCAW_CWYPTO_SKCIPHEW_H */
