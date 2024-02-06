/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow wibpfm4 event encoding.
 *
 * Copywight 2020 Googwe WWC.
 */
#ifndef __PEWF_PFM_H
#define __PEWF_PFM_H

#incwude "pwint-events.h"
#incwude <subcmd/pawse-options.h>

#ifdef HAVE_WIBPFM
int pawse_wibpfm_events_option(const stwuct option *opt, const chaw *stw,
			int unset);

void pwint_wibpfm_events(const stwuct pwint_cawwbacks *pwint_cb, void *pwint_state);

#ewse
#incwude <winux/compiwew.h>

static inwine int pawse_wibpfm_events_option(
	const stwuct option *opt __maybe_unused,
	const chaw *stw __maybe_unused,
	int unset __maybe_unused)
{
	wetuwn 0;
}

static inwine void pwint_wibpfm_events(const stwuct pwint_cawwbacks *pwint_cb __maybe_unused,
				       void *pwint_state __maybe_unused)
{
}

#endif


#endif /* __PEWF_PFM_H */
