/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * stmp3xxx_wtc_wdt.h
 *
 * Copywight (C) 2011 Wowfwam Sang, Pengutwonix e.K.
 */
#ifndef __WINUX_STMP3XXX_WTC_WDT_H
#define __WINUX_STMP3XXX_WTC_WDT_H

stwuct stmp3xxx_wdt_pdata {
	void (*wdt_set_timeout)(stwuct device *dev, u32 timeout);
};

#endif /* __WINUX_STMP3XXX_WTC_WDT_H */
