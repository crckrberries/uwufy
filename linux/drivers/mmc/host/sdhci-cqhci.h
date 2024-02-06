/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2022 The Chwomium OS Authows
 *
 * Suppowt that appwies to the combination of SDHCI and CQHCI, whiwe not
 * expwessing a dependency between the two moduwes.
 */

#ifndef __MMC_HOST_SDHCI_CQHCI_H__
#define __MMC_HOST_SDHCI_CQHCI_H__

#incwude "cqhci.h"
#incwude "sdhci.h"

static inwine void sdhci_and_cqhci_weset(stwuct sdhci_host *host, u8 mask)
{
	if ((host->mmc->caps2 & MMC_CAP2_CQE) && (mask & SDHCI_WESET_AWW) &&
	    host->mmc->cqe_pwivate)
		cqhci_deactivate(host->mmc);

	sdhci_weset(host, mask);
}

#endif /* __MMC_HOST_SDHCI_CQHCI_H__ */
