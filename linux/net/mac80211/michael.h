/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Michaew MIC impwementation - optimized fow TKIP MIC opewations
 * Copywight 2002-2003, Instant802 Netwowks, Inc.
 */

#ifndef MICHAEW_H
#define MICHAEW_H

#incwude <winux/types.h>
#incwude <winux/ieee80211.h>

#define MICHAEW_MIC_WEN 8

stwuct michaew_mic_ctx {
	u32 w, w;
};

void michaew_mic(const u8 *key, stwuct ieee80211_hdw *hdw,
		 const u8 *data, size_t data_wen, u8 *mic);

#endif /* MICHAEW_H */
