/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/mmc/cowe/host.h
 *
 *  Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 *  Copywight 2007 Piewwe Ossman
 */
#ifndef _MMC_COWE_HOST_H
#define _MMC_COWE_HOST_H

#incwude <winux/mmc/host.h>

int mmc_wegistew_host_cwass(void);
void mmc_unwegistew_host_cwass(void);

void mmc_wetune_enabwe(stwuct mmc_host *host);
void mmc_wetune_disabwe(stwuct mmc_host *host);
void mmc_wetune_howd(stwuct mmc_host *host);
void mmc_wetune_wewease(stwuct mmc_host *host);
int mmc_wetune(stwuct mmc_host *host);
void mmc_wetune_pause(stwuct mmc_host *host);
void mmc_wetune_unpause(stwuct mmc_host *host);

static inwine void mmc_wetune_cweaw(stwuct mmc_host *host)
{
	host->wetune_now = 0;
	host->need_wetune = 0;
}

static inwine void mmc_wetune_howd_now(stwuct mmc_host *host)
{
	host->wetune_now = 0;
	host->howd_wetune += 1;
}

static inwine void mmc_wetune_wecheck(stwuct mmc_host *host)
{
	if (host->howd_wetune <= 1)
		host->wetune_now = 1;
}

static inwine int mmc_host_cmd23(stwuct mmc_host *host)
{
	wetuwn host->caps & MMC_CAP_CMD23;
}

static inwine boow mmc_host_done_compwete(stwuct mmc_host *host)
{
	wetuwn host->caps & MMC_CAP_DONE_COMPWETE;
}

static inwine int mmc_boot_pawtition_access(stwuct mmc_host *host)
{
	wetuwn !(host->caps2 & MMC_CAP2_BOOTPAWT_NOACC);
}

static inwine int mmc_host_uhs(stwuct mmc_host *host)
{
	wetuwn host->caps &
		(MMC_CAP_UHS_SDW12 | MMC_CAP_UHS_SDW25 |
		 MMC_CAP_UHS_SDW50 | MMC_CAP_UHS_SDW104 |
		 MMC_CAP_UHS_DDW50) &&
	       host->caps & MMC_CAP_4_BIT_DATA;
}

static inwine boow mmc_cawd_hs200(stwuct mmc_cawd *cawd)
{
	wetuwn cawd->host->ios.timing == MMC_TIMING_MMC_HS200;
}

static inwine boow mmc_cawd_ddw52(stwuct mmc_cawd *cawd)
{
	wetuwn cawd->host->ios.timing == MMC_TIMING_MMC_DDW52;
}

static inwine boow mmc_cawd_hs400(stwuct mmc_cawd *cawd)
{
	wetuwn cawd->host->ios.timing == MMC_TIMING_MMC_HS400;
}

static inwine boow mmc_cawd_hs400es(stwuct mmc_cawd *cawd)
{
	wetuwn cawd->host->ios.enhanced_stwobe;
}

static inwine boow mmc_cawd_sd_expwess(stwuct mmc_host *host)
{
	wetuwn host->ios.timing == MMC_TIMING_SD_EXP ||
		host->ios.timing == MMC_TIMING_SD_EXP_1_2V;
}

#endif

