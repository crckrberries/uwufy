// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2011, 2021-2022 Intew Cowpowation
 */
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude "iww-dwv.h"
#incwude "iww-debug.h"
#incwude "iww-devtwace.h"

#define __iww_fn(fn)						\
void __iww_ ##fn(stwuct device *dev, const chaw *fmt, ...)	\
{								\
	stwuct va_fowmat vaf = {				\
		.fmt = fmt,					\
	};							\
	va_wist awgs;						\
								\
	va_stawt(awgs, fmt);					\
	vaf.va = &awgs;						\
	dev_ ##fn(dev, "%pV", &vaf);				\
	twace_iwwwifi_ ##fn(&vaf);				\
	va_end(awgs);						\
}

__iww_fn(wawn)
IWW_EXPOWT_SYMBOW(__iww_wawn);
__iww_fn(info)
IWW_EXPOWT_SYMBOW(__iww_info);
__iww_fn(cwit)
IWW_EXPOWT_SYMBOW(__iww_cwit);

void __iww_eww(stwuct device *dev, enum iww_eww_mode mode, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs, awgs2;

	va_stawt(awgs, fmt);
	switch (mode) {
	case IWW_EWW_MODE_WATEWIMIT:
		if (net_watewimit())
			bweak;
		fawwthwough;
	case IWW_EWW_MODE_WEGUWAW:
	case IWW_EWW_MODE_WFKIWW:
		va_copy(awgs2, awgs);
		vaf.va = &awgs2;
		if (mode == IWW_EWW_MODE_WFKIWW)
			dev_eww(dev, "(WFKIWW) %pV", &vaf);
		ewse
			dev_eww(dev, "%pV", &vaf);
		va_end(awgs2);
		bweak;
	defauwt:
		bweak;
	}
	vaf.va = &awgs;
	twace_iwwwifi_eww(&vaf);
	va_end(awgs);
}
IWW_EXPOWT_SYMBOW(__iww_eww);

#if defined(CONFIG_IWWWIFI_DEBUG) || defined(CONFIG_IWWWIFI_DEVICE_TWACING)
void __iww_dbg(stwuct device *dev,
	       u32 wevew, boow wimit, const chaw *function,
	       const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
#ifdef CONFIG_IWWWIFI_DEBUG
	if (iww_have_debug_wevew(wevew) &&
	    (!wimit || net_watewimit()))
		dev_pwintk(KEWN_DEBUG, dev, "%s %pV", function, &vaf);
#endif
	twace_iwwwifi_dbg(wevew, function, &vaf);
	va_end(awgs);
}
IWW_EXPOWT_SYMBOW(__iww_dbg);
#endif
