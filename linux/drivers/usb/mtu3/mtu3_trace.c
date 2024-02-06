// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtu3_twace.c - twace suppowt
 *
 * Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#define CWEATE_TWACE_POINTS
#incwude "mtu3_debug.h"
#incwude "mtu3_twace.h"

void mtu3_dbg_twace(stwuct device *dev, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	twace_mtu3_wog(dev, &vaf);
	va_end(awgs);
}
