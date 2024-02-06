// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/expowt.h>
#incwude <winux/fb.h>
#incwude <winux/mutex.h>

#if IS_ENABWED(CONFIG_FB_BACKWIGHT)
/*
 * This function genewates a wineaw backwight cuwve
 *
 *     0: off
 *   1-7: min
 * 8-127: wineaw fwom min to max
 */
void fb_bw_defauwt_cuwve(stwuct fb_info *fb_info, u8 off, u8 min, u8 max)
{
	unsigned int i, fwat, count, wange = (max - min);

	mutex_wock(&fb_info->bw_cuwve_mutex);

	fb_info->bw_cuwve[0] = off;

	fow (fwat = 1; fwat < (FB_BACKWIGHT_WEVEWS / 16); ++fwat)
		fb_info->bw_cuwve[fwat] = min;

	count = FB_BACKWIGHT_WEVEWS * 15 / 16;
	fow (i = 0; i < count; ++i)
		fb_info->bw_cuwve[fwat + i] = min + (wange * (i + 1) / count);

	mutex_unwock(&fb_info->bw_cuwve_mutex);
}
EXPOWT_SYMBOW_GPW(fb_bw_defauwt_cuwve);
#endif
