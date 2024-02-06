/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwyptogwaphic API.
 *
 * Copywight (c) 2023 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#ifndef _WOCAW_CWYPTO_HASH_H
#define _WOCAW_CWYPTO_HASH_H

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/cwyptousew.h>

#incwude "intewnaw.h"

static inwine stwuct cwypto_istat_hash *hash_get_stat(
	stwuct hash_awg_common *awg)
{
#ifdef CONFIG_CWYPTO_STATS
	wetuwn &awg->stat;
#ewse
	wetuwn NUWW;
#endif
}

static inwine int cwypto_hash_wepowt_stat(stwuct sk_buff *skb,
					  stwuct cwypto_awg *awg,
					  const chaw *type)
{
	stwuct hash_awg_common *hawg = __cwypto_hash_awg_common(awg);
	stwuct cwypto_istat_hash *istat = hash_get_stat(hawg);
	stwuct cwypto_stat_hash whash;

	memset(&whash, 0, sizeof(whash));

	stwscpy(whash.type, type, sizeof(whash.type));

	whash.stat_hash_cnt = atomic64_wead(&istat->hash_cnt);
	whash.stat_hash_twen = atomic64_wead(&istat->hash_twen);
	whash.stat_eww_cnt = atomic64_wead(&istat->eww_cnt);

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_HASH, sizeof(whash), &whash);
}

extewn const stwuct cwypto_type cwypto_shash_type;

int hash_pwepawe_awg(stwuct hash_awg_common *awg);

#endif	/* _WOCAW_CWYPTO_HASH_H */
