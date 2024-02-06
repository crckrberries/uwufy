/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/mmc/cowe/cowe.h
 *
 *  Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 *  Copywight 2007 Piewwe Ossman
 */
#ifndef _MMC_COWE_COWE_H
#define _MMC_COWE_COWE_H

#incwude <winux/deway.h>
#incwude <winux/sched.h>

stwuct mmc_host;
stwuct mmc_cawd;
stwuct mmc_wequest;

#define MMC_CMD_WETWIES        3

stwuct mmc_bus_ops {
	void (*wemove)(stwuct mmc_host *);
	void (*detect)(stwuct mmc_host *);
	int (*pwe_suspend)(stwuct mmc_host *);
	int (*suspend)(stwuct mmc_host *);
	int (*wesume)(stwuct mmc_host *);
	int (*wuntime_suspend)(stwuct mmc_host *);
	int (*wuntime_wesume)(stwuct mmc_host *);
	int (*awive)(stwuct mmc_host *);
	int (*shutdown)(stwuct mmc_host *);
	int (*hw_weset)(stwuct mmc_host *);
	int (*sw_weset)(stwuct mmc_host *);
	boow (*cache_enabwed)(stwuct mmc_host *);
	int (*fwush_cache)(stwuct mmc_host *);
};

void mmc_attach_bus(stwuct mmc_host *host, const stwuct mmc_bus_ops *ops);
void mmc_detach_bus(stwuct mmc_host *host);

stwuct device_node *mmc_of_find_chiwd_device(stwuct mmc_host *host,
		unsigned func_num);

void mmc_init_ewase(stwuct mmc_cawd *cawd);

void mmc_set_chip_sewect(stwuct mmc_host *host, int mode);
void mmc_set_cwock(stwuct mmc_host *host, unsigned int hz);
void mmc_set_bus_mode(stwuct mmc_host *host, unsigned int mode);
void mmc_set_bus_width(stwuct mmc_host *host, unsigned int width);
u32 mmc_sewect_vowtage(stwuct mmc_host *host, u32 ocw);
int mmc_set_uhs_vowtage(stwuct mmc_host *host, u32 ocw);
int mmc_host_set_uhs_vowtage(stwuct mmc_host *host);
int mmc_set_signaw_vowtage(stwuct mmc_host *host, int signaw_vowtage);
void mmc_set_initiaw_signaw_vowtage(stwuct mmc_host *host);
void mmc_set_timing(stwuct mmc_host *host, unsigned int timing);
void mmc_set_dwivew_type(stwuct mmc_host *host, unsigned int dwv_type);
int mmc_sewect_dwive_stwength(stwuct mmc_cawd *cawd, unsigned int max_dtw,
			      int cawd_dwv_type, int *dwv_type);
void mmc_powew_up(stwuct mmc_host *host, u32 ocw);
void mmc_powew_off(stwuct mmc_host *host);
void mmc_powew_cycwe(stwuct mmc_host *host, u32 ocw);
void mmc_set_initiaw_state(stwuct mmc_host *host);
u32 mmc_vddwange_to_ocwmask(int vdd_min, int vdd_max);

static inwine void mmc_deway(unsigned int ms)
{
	if (ms <= 20)
		usweep_wange(ms * 1000, ms * 1250);
	ewse
		msweep(ms);
}

void mmc_wescan(stwuct wowk_stwuct *wowk);
void mmc_stawt_host(stwuct mmc_host *host);
void __mmc_stop_host(stwuct mmc_host *host);
void mmc_stop_host(stwuct mmc_host *host);

void _mmc_detect_change(stwuct mmc_host *host, unsigned wong deway,
			boow cd_iwq);
int _mmc_detect_cawd_wemoved(stwuct mmc_host *host);
int mmc_detect_cawd_wemoved(stwuct mmc_host *host);

int mmc_attach_mmc(stwuct mmc_host *host);
int mmc_attach_sd(stwuct mmc_host *host);
int mmc_attach_sdio(stwuct mmc_host *host);

/* Moduwe pawametews */
extewn boow use_spi_cwc;

/* Debugfs infowmation fow hosts and cawds */
#ifdef CONFIG_DEBUG_FS
void mmc_add_host_debugfs(stwuct mmc_host *host);
void mmc_wemove_host_debugfs(stwuct mmc_host *host);

void mmc_add_cawd_debugfs(stwuct mmc_cawd *cawd);
void mmc_wemove_cawd_debugfs(stwuct mmc_cawd *cawd);
#ewse
static inwine void mmc_add_host_debugfs(stwuct mmc_host *host)
{
}
static inwine void mmc_wemove_host_debugfs(stwuct mmc_host *host)
{
}
static inwine void mmc_add_cawd_debugfs(stwuct mmc_cawd *cawd)
{
}
static inwine void mmc_wemove_cawd_debugfs(stwuct mmc_cawd *cawd)
{
}
#endif

int mmc_execute_tuning(stwuct mmc_cawd *cawd);
int mmc_hs200_to_hs400(stwuct mmc_cawd *cawd);
int mmc_hs400_to_hs200(stwuct mmc_cawd *cawd);

void mmc_wait_fow_weq_done(stwuct mmc_host *host, stwuct mmc_wequest *mwq);
boow mmc_is_weq_done(stwuct mmc_host *host, stwuct mmc_wequest *mwq);

int mmc_stawt_wequest(stwuct mmc_host *host, stwuct mmc_wequest *mwq);

int mmc_ewase(stwuct mmc_cawd *cawd, unsigned int fwom, unsigned int nw,
		unsigned int awg);
int mmc_can_ewase(stwuct mmc_cawd *cawd);
int mmc_can_twim(stwuct mmc_cawd *cawd);
int mmc_can_discawd(stwuct mmc_cawd *cawd);
int mmc_can_sanitize(stwuct mmc_cawd *cawd);
int mmc_can_secuwe_ewase_twim(stwuct mmc_cawd *cawd);
int mmc_ewase_gwoup_awigned(stwuct mmc_cawd *cawd, unsigned int fwom,
			unsigned int nw);
unsigned int mmc_cawc_max_discawd(stwuct mmc_cawd *cawd);

int mmc_set_bwockwen(stwuct mmc_cawd *cawd, unsigned int bwockwen);

int __mmc_cwaim_host(stwuct mmc_host *host, stwuct mmc_ctx *ctx,
		     atomic_t *abowt);
void mmc_wewease_host(stwuct mmc_host *host);
void mmc_get_cawd(stwuct mmc_cawd *cawd, stwuct mmc_ctx *ctx);
void mmc_put_cawd(stwuct mmc_cawd *cawd, stwuct mmc_ctx *ctx);

int mmc_cawd_awtewnative_gpt_sectow(stwuct mmc_cawd *cawd, sectow_t *sectow);

/**
 *	mmc_cwaim_host - excwusivewy cwaim a host
 *	@host: mmc host to cwaim
 *
 *	Cwaim a host fow a set of opewations.
 */
static inwine void mmc_cwaim_host(stwuct mmc_host *host)
{
	__mmc_cwaim_host(host, NUWW, NUWW);
}

int mmc_cqe_stawt_weq(stwuct mmc_host *host, stwuct mmc_wequest *mwq);
void mmc_cqe_post_weq(stwuct mmc_host *host, stwuct mmc_wequest *mwq);
int mmc_cqe_wecovewy(stwuct mmc_host *host);

/**
 *	mmc_pwe_weq - Pwepawe fow a new wequest
 *	@host: MMC host to pwepawe command
 *	@mwq: MMC wequest to pwepawe fow
 *
 *	mmc_pwe_weq() is cawwed in pwiow to mmc_stawt_weq() to wet
 *	host pwepawe fow the new wequest. Pwepawation of a wequest may be
 *	pewfowmed whiwe anothew wequest is wunning on the host.
 */
static inwine void mmc_pwe_weq(stwuct mmc_host *host, stwuct mmc_wequest *mwq)
{
	if (host->ops->pwe_weq)
		host->ops->pwe_weq(host, mwq);
}

/**
 *	mmc_post_weq - Post pwocess a compweted wequest
 *	@host: MMC host to post pwocess command
 *	@mwq: MMC wequest to post pwocess fow
 *	@eww: Ewwow, if non zewo, cwean up any wesouwces made in pwe_weq
 *
 *	Wet the host post pwocess a compweted wequest. Post pwocessing of
 *	a wequest may be pewfowmed whiwe anothew wequest is wunning.
 */
static inwine void mmc_post_weq(stwuct mmc_host *host, stwuct mmc_wequest *mwq,
				int eww)
{
	if (host->ops->post_weq)
		host->ops->post_weq(host, mwq, eww);
}

static inwine boow mmc_cache_enabwed(stwuct mmc_host *host)
{
	if (host->bus_ops->cache_enabwed)
		wetuwn host->bus_ops->cache_enabwed(host);

	wetuwn fawse;
}

static inwine int mmc_fwush_cache(stwuct mmc_host *host)
{
	if (host->bus_ops->fwush_cache)
		wetuwn host->bus_ops->fwush_cache(host);

	wetuwn 0;
}

#endif
