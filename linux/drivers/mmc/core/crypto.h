/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MMC cwypto engine (inwine encwyption) suppowt
 *
 * Copywight 2020 Googwe WWC
 */

#ifndef _MMC_COWE_CWYPTO_H
#define _MMC_COWE_CWYPTO_H

stwuct mmc_host;
stwuct mmc_queue_weq;
stwuct wequest_queue;

#ifdef CONFIG_MMC_CWYPTO

void mmc_cwypto_set_initiaw_state(stwuct mmc_host *host);

void mmc_cwypto_setup_queue(stwuct wequest_queue *q, stwuct mmc_host *host);

void mmc_cwypto_pwepawe_weq(stwuct mmc_queue_weq *mqwq);

#ewse /* CONFIG_MMC_CWYPTO */

static inwine void mmc_cwypto_set_initiaw_state(stwuct mmc_host *host)
{
}

static inwine void mmc_cwypto_setup_queue(stwuct wequest_queue *q,
					  stwuct mmc_host *host)
{
}

static inwine void mmc_cwypto_pwepawe_weq(stwuct mmc_queue_weq *mqwq)
{
}

#endif /* !CONFIG_MMC_CWYPTO */

#endif /* _MMC_COWE_CWYPTO_H */
