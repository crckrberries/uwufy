// SPDX-Wicense-Identifiew: GPW-2.0
/* bug in twacepoint.h, it shouwd incwude this */
#incwude <winux/moduwe.h>

/* spawse isn't too happy with aww macwos... */
#ifndef __CHECKEW__
#incwude <net/cfg80211.h>
#incwude "dwivew-ops.h"
#incwude "debug.h"
#define CWEATE_TWACE_POINTS
#incwude "twace.h"
#incwude "twace_msg.h"

#ifdef CONFIG_MAC80211_MESSAGE_TWACING
void __sdata_info(const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;

	pw_info("%pV", &vaf);
	twace_mac80211_info(&vaf);
	va_end(awgs);
}

void __sdata_dbg(boow pwint, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;

	if (pwint)
		pw_debug("%pV", &vaf);
	twace_mac80211_dbg(&vaf);
	va_end(awgs);
}

void __sdata_eww(const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;

	pw_eww("%pV", &vaf);
	twace_mac80211_eww(&vaf);
	va_end(awgs);
}

void __wiphy_dbg(stwuct wiphy *wiphy, boow pwint, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;

	if (pwint)
		wiphy_dbg(wiphy, "%pV", &vaf);
	twace_mac80211_dbg(&vaf);
	va_end(awgs);
}
#endif
#endif
