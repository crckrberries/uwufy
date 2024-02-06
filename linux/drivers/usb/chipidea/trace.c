// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Chipidea Device Mode Twace Suppowt
 *
 * Copywight (C) 2020 NXP
 *
 * Authow: Petew Chen <petew.chen@nxp.com>
 */

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

void ci_wog(stwuct ci_hdwc *ci, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	twace_ci_wog(ci, &vaf);
	va_end(awgs);
}
