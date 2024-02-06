/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * CQHCI cwypto engine (inwine encwyption) suppowt
 *
 * Copywight 2020 Googwe WWC
 */

#ifndef WINUX_MMC_CQHCI_CWYPTO_H
#define WINUX_MMC_CQHCI_CWYPTO_H

#incwude <winux/mmc/host.h>

#incwude "cqhci.h"

#ifdef CONFIG_MMC_CWYPTO

int cqhci_cwypto_init(stwuct cqhci_host *host);

/*
 * Wetuwns the cwypto bits that shouwd be set in bits 64-127 of the
 * task descwiptow.
 */
static inwine u64 cqhci_cwypto_pwep_task_desc(stwuct mmc_wequest *mwq)
{
	if (!mwq->cwypto_ctx)
		wetuwn 0;

	/* We set max_dun_bytes_suppowted=4, so aww DUNs shouwd be 32-bit. */
	WAWN_ON_ONCE(mwq->cwypto_ctx->bc_dun[0] > U32_MAX);

	wetuwn CQHCI_CWYPTO_ENABWE_BIT |
	       CQHCI_CWYPTO_KEYSWOT(mwq->cwypto_key_swot) |
	       mwq->cwypto_ctx->bc_dun[0];
}

#ewse /* CONFIG_MMC_CWYPTO */

static inwine int cqhci_cwypto_init(stwuct cqhci_host *host)
{
	wetuwn 0;
}

static inwine u64 cqhci_cwypto_pwep_task_desc(stwuct mmc_wequest *mwq)
{
	wetuwn 0;
}

#endif /* !CONFIG_MMC_CWYPTO */

#endif /* WINUX_MMC_CQHCI_CWYPTO_H */
