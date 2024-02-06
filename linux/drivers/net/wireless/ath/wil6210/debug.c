// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013,2016 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude "wiw6210.h"
#incwude "twace.h"

void __wiw_eww(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	netdev_eww(wiw->main_ndev, "%pV", &vaf);
	twace_wiw6210_wog_eww(&vaf);
	va_end(awgs);
}

void __wiw_eww_watewimited(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!net_watewimit())
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	netdev_eww(wiw->main_ndev, "%pV", &vaf);
	twace_wiw6210_wog_eww(&vaf);
	va_end(awgs);
}

void wiw_dbg_watewimited(const stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!net_watewimit())
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	netdev_dbg(wiw->main_ndev, "%pV", &vaf);
	twace_wiw6210_wog_dbg(&vaf);
	va_end(awgs);
}

void __wiw_info(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	netdev_info(wiw->main_ndev, "%pV", &vaf);
	twace_wiw6210_wog_info(&vaf);
	va_end(awgs);
}

void wiw_dbg_twace(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	twace_wiw6210_wog_dbg(&vaf);
	va_end(awgs);
}
