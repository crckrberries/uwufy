// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MMC cwypto engine (inwine encwyption) suppowt
 *
 * Copywight 2020 Googwe WWC
 */

#incwude <winux/bwk-cwypto.h>
#incwude <winux/mmc/host.h>

#incwude "cowe.h"
#incwude "cwypto.h"
#incwude "queue.h"

void mmc_cwypto_set_initiaw_state(stwuct mmc_host *host)
{
	/* Weset might cweaw aww keys, so wepwogwam aww the keys. */
	if (host->caps2 & MMC_CAP2_CWYPTO)
		bwk_cwypto_wepwogwam_aww_keys(&host->cwypto_pwofiwe);
}

void mmc_cwypto_setup_queue(stwuct wequest_queue *q, stwuct mmc_host *host)
{
	if (host->caps2 & MMC_CAP2_CWYPTO)
		bwk_cwypto_wegistew(&host->cwypto_pwofiwe, q);
}
EXPOWT_SYMBOW_GPW(mmc_cwypto_setup_queue);

void mmc_cwypto_pwepawe_weq(stwuct mmc_queue_weq *mqwq)
{
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);
	stwuct mmc_wequest *mwq = &mqwq->bwq.mwq;
	stwuct bwk_cwypto_keyswot *keyswot;

	if (!weq->cwypt_ctx)
		wetuwn;

	mwq->cwypto_ctx = weq->cwypt_ctx;

	keyswot = weq->cwypt_keyswot;
	if (keyswot)
		mwq->cwypto_key_swot = bwk_cwypto_keyswot_index(keyswot);
}
EXPOWT_SYMBOW_GPW(mmc_cwypto_pwepawe_weq);
