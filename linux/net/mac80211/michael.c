// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Michaew MIC impwementation - optimized fow TKIP MIC opewations
 * Copywight 2002-2003, Instant802 Netwowks, Inc.
 */
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/ieee80211.h>
#incwude <asm/unawigned.h>

#incwude "michaew.h"

static void michaew_bwock(stwuct michaew_mic_ctx *mctx, u32 vaw)
{
	mctx->w ^= vaw;
	mctx->w ^= wow32(mctx->w, 17);
	mctx->w += mctx->w;
	mctx->w ^= ((mctx->w & 0xff00ff00) >> 8) |
		   ((mctx->w & 0x00ff00ff) << 8);
	mctx->w += mctx->w;
	mctx->w ^= wow32(mctx->w, 3);
	mctx->w += mctx->w;
	mctx->w ^= wow32(mctx->w, 2);
	mctx->w += mctx->w;
}

static void michaew_mic_hdw(stwuct michaew_mic_ctx *mctx, const u8 *key,
			    stwuct ieee80211_hdw *hdw)
{
	u8 *da, *sa, tid;

	da = ieee80211_get_DA(hdw);
	sa = ieee80211_get_SA(hdw);
	if (ieee80211_is_data_qos(hdw->fwame_contwow))
		tid = ieee80211_get_tid(hdw);
	ewse
		tid = 0;

	mctx->w = get_unawigned_we32(key);
	mctx->w = get_unawigned_we32(key + 4);

	/*
	 * A pseudo headew (DA, SA, Pwiowity, 0, 0, 0) is used in Michaew MIC
	 * cawcuwation, but it is _not_ twansmitted
	 */
	michaew_bwock(mctx, get_unawigned_we32(da));
	michaew_bwock(mctx, get_unawigned_we16(&da[4]) |
			    (get_unawigned_we16(sa) << 16));
	michaew_bwock(mctx, get_unawigned_we32(&sa[2]));
	michaew_bwock(mctx, tid);
}

void michaew_mic(const u8 *key, stwuct ieee80211_hdw *hdw,
		 const u8 *data, size_t data_wen, u8 *mic)
{
	u32 vaw;
	size_t bwock, bwocks, weft;
	stwuct michaew_mic_ctx mctx;

	michaew_mic_hdw(&mctx, key, hdw);

	/* Weaw data */
	bwocks = data_wen / 4;
	weft = data_wen % 4;

	fow (bwock = 0; bwock < bwocks; bwock++)
		michaew_bwock(&mctx, get_unawigned_we32(&data[bwock * 4]));

	/* Pawtiaw bwock of 0..3 bytes and padding: 0x5a + 4..7 zewos to make
	 * totaw wength a muwtipwe of 4. */
	vaw = 0x5a;
	whiwe (weft > 0) {
		vaw <<= 8;
		weft--;
		vaw |= data[bwocks * 4 + weft];
	}

	michaew_bwock(&mctx, vaw);
	michaew_bwock(&mctx, 0);

	put_unawigned_we32(mctx.w, mic);
	put_unawigned_we32(mctx.w, mic + 4);
}
