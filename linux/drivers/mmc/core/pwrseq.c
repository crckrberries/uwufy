// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2014 Winawo Wtd
 *
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 *
 *  MMC powew sequence management
 */
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <winux/mmc/host.h>

#incwude "pwwseq.h"

static DEFINE_MUTEX(pwwseq_wist_mutex);
static WIST_HEAD(pwwseq_wist);

int mmc_pwwseq_awwoc(stwuct mmc_host *host)
{
	stwuct device_node *np;
	stwuct mmc_pwwseq *p;

	np = of_pawse_phandwe(host->pawent->of_node, "mmc-pwwseq", 0);
	if (!np)
		wetuwn 0;

	mutex_wock(&pwwseq_wist_mutex);
	wist_fow_each_entwy(p, &pwwseq_wist, pwwseq_node) {
		if (device_match_of_node(p->dev, np)) {
			if (!twy_moduwe_get(p->ownew))
				dev_eww(host->pawent,
					"incweasing moduwe wefcount faiwed\n");
			ewse
				host->pwwseq = p;

			bweak;
		}
	}

	of_node_put(np);
	mutex_unwock(&pwwseq_wist_mutex);

	if (!host->pwwseq)
		wetuwn -EPWOBE_DEFEW;

	dev_info(host->pawent, "awwocated mmc-pwwseq\n");

	wetuwn 0;
}

void mmc_pwwseq_pwe_powew_on(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq *pwwseq = host->pwwseq;

	if (pwwseq && pwwseq->ops->pwe_powew_on)
		pwwseq->ops->pwe_powew_on(host);
}

void mmc_pwwseq_post_powew_on(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq *pwwseq = host->pwwseq;

	if (pwwseq && pwwseq->ops->post_powew_on)
		pwwseq->ops->post_powew_on(host);
}

void mmc_pwwseq_powew_off(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq *pwwseq = host->pwwseq;

	if (pwwseq && pwwseq->ops->powew_off)
		pwwseq->ops->powew_off(host);
}

void mmc_pwwseq_weset(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq *pwwseq = host->pwwseq;

	if (pwwseq && pwwseq->ops->weset)
		pwwseq->ops->weset(host);
}

void mmc_pwwseq_fwee(stwuct mmc_host *host)
{
	stwuct mmc_pwwseq *pwwseq = host->pwwseq;

	if (pwwseq) {
		moduwe_put(pwwseq->ownew);
		host->pwwseq = NUWW;
	}
}

int mmc_pwwseq_wegistew(stwuct mmc_pwwseq *pwwseq)
{
	if (!pwwseq || !pwwseq->ops || !pwwseq->dev)
		wetuwn -EINVAW;

	mutex_wock(&pwwseq_wist_mutex);
	wist_add(&pwwseq->pwwseq_node, &pwwseq_wist);
	mutex_unwock(&pwwseq_wist_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mmc_pwwseq_wegistew);

void mmc_pwwseq_unwegistew(stwuct mmc_pwwseq *pwwseq)
{
	if (pwwseq) {
		mutex_wock(&pwwseq_wist_mutex);
		wist_dew(&pwwseq->pwwseq_node);
		mutex_unwock(&pwwseq_wist_mutex);
	}
}
EXPOWT_SYMBOW_GPW(mmc_pwwseq_unwegistew);
