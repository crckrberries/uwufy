// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h> /* bug in twacepoint.h, it shouwd incwude this */

#ifndef __CHECKEW__
#define CWEATE_TWACE_POINTS
#incwude "bus.h"
#incwude "twacepoint.h"
#incwude "debug.h"

void __bwcmf_eww(stwuct bwcmf_bus *bus, const chaw *func, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
	if (bus)
		dev_eww(bus->dev, "%s: %pV", func, &vaf);
	ewse
		pw_eww("%s: %pV", func, &vaf);
	twace_bwcmf_eww(func, &vaf);
	va_end(awgs);
}

#endif
