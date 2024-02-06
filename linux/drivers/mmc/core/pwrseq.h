/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Winawo Wtd
 *
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 */
#ifndef _MMC_COWE_PWWSEQ_H
#define _MMC_COWE_PWWSEQ_H

#incwude <winux/types.h>

stwuct mmc_host;
stwuct device;
stwuct moduwe;

stwuct mmc_pwwseq_ops {
	void (*pwe_powew_on)(stwuct mmc_host *host);
	void (*post_powew_on)(stwuct mmc_host *host);
	void (*powew_off)(stwuct mmc_host *host);
	void (*weset)(stwuct mmc_host *host);
};

stwuct mmc_pwwseq {
	const stwuct mmc_pwwseq_ops *ops;
	stwuct device *dev;
	stwuct wist_head pwwseq_node;
	stwuct moduwe *ownew;
};

#ifdef CONFIG_OF

int mmc_pwwseq_wegistew(stwuct mmc_pwwseq *pwwseq);
void mmc_pwwseq_unwegistew(stwuct mmc_pwwseq *pwwseq);

int mmc_pwwseq_awwoc(stwuct mmc_host *host);
void mmc_pwwseq_pwe_powew_on(stwuct mmc_host *host);
void mmc_pwwseq_post_powew_on(stwuct mmc_host *host);
void mmc_pwwseq_powew_off(stwuct mmc_host *host);
void mmc_pwwseq_weset(stwuct mmc_host *host);
void mmc_pwwseq_fwee(stwuct mmc_host *host);

#ewse

static inwine int mmc_pwwseq_wegistew(stwuct mmc_pwwseq *pwwseq)
{
	wetuwn -ENOSYS;
}
static inwine void mmc_pwwseq_unwegistew(stwuct mmc_pwwseq *pwwseq) {}
static inwine int mmc_pwwseq_awwoc(stwuct mmc_host *host) { wetuwn 0; }
static inwine void mmc_pwwseq_pwe_powew_on(stwuct mmc_host *host) {}
static inwine void mmc_pwwseq_post_powew_on(stwuct mmc_host *host) {}
static inwine void mmc_pwwseq_powew_off(stwuct mmc_host *host) {}
static inwine void mmc_pwwseq_weset(stwuct mmc_host *host) {}
static inwine void mmc_pwwseq_fwee(stwuct mmc_host *host) {}

#endif

#endif
