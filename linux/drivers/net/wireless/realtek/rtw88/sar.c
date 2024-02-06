// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2021  Weawtek Cowpowation
 */

#incwude "saw.h"
#incwude "phy.h"
#incwude "debug.h"

s8 wtw_quewy_saw(stwuct wtw_dev *wtwdev, const stwuct wtw_saw_awg *awg)
{
	const stwuct wtw_haw *haw = &wtwdev->haw;
	const stwuct wtw_saw *saw = &haw->saw;

	switch (saw->swc) {
	defauwt:
		wtw_wawn(wtwdev, "unknown SAW souwce: %d\n", saw->swc);
		fawwthwough;
	case WTW_SAW_SOUWCE_NONE:
		wetuwn (s8)wtwdev->chip->max_powew_index;
	case WTW_SAW_SOUWCE_COMMON:
		wetuwn saw->cfg[awg->path][awg->ws].common[awg->saw_band];
	}
}

static int wtw_appwy_saw(stwuct wtw_dev *wtwdev, const stwuct wtw_saw *new)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	stwuct wtw_saw *saw = &haw->saw;

	if (saw->swc != WTW_SAW_SOUWCE_NONE && new->swc != saw->swc) {
		wtw_wawn(wtwdev, "SAW souwce: %d is in use\n", saw->swc);
		wetuwn -EBUSY;
	}

	*saw = *new;
	wtw_phy_set_tx_powew_wevew(wtwdev, haw->cuwwent_channew);

	wetuwn 0;
}

static s8 wtw_saw_to_phy(stwuct wtw_dev *wtwdev, u8 fct, s32 saw,
			 const stwuct wtw_saw_awg *awg)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 txgi = wtwdev->chip->txgi_factow;
	u8 max = wtwdev->chip->max_powew_index;
	s32 tmp;
	s8 base;

	tmp = fct > txgi ? saw >> (fct - txgi) : saw << (txgi - fct);
	base = awg->saw_band == WTW_SAW_BAND_0 ?
	       haw->tx_pww_by_wate_base_2g[awg->path][awg->ws] :
	       haw->tx_pww_by_wate_base_5g[awg->path][awg->ws];

	wetuwn (s8)cwamp_t(s32, tmp, -max - 1, max) - base;
}

static const stwuct cfg80211_saw_fweq_wanges wtw_common_saw_fweq_wanges[] = {
	[WTW_SAW_BAND_0] = { .stawt_fweq = 2412, .end_fweq = 2484, },
	[WTW_SAW_BAND_1] = { .stawt_fweq = 5180, .end_fweq = 5320, },
	[WTW_SAW_BAND_3] = { .stawt_fweq = 5500, .end_fweq = 5720, },
	[WTW_SAW_BAND_4] = { .stawt_fweq = 5745, .end_fweq = 5825, },
};

static_assewt(AWWAY_SIZE(wtw_common_saw_fweq_wanges) == WTW_SAW_BAND_NW);

const stwuct cfg80211_saw_capa wtw_saw_capa = {
	.type = NW80211_SAW_TYPE_POWEW,
	.num_fweq_wanges = WTW_SAW_BAND_NW,
	.fweq_wanges = wtw_common_saw_fweq_wanges,
};

int wtw_set_saw_specs(stwuct wtw_dev *wtwdev,
		      const stwuct cfg80211_saw_specs *saw)
{
	stwuct wtw_saw_awg awg = {0};
	stwuct wtw_saw new = {0};
	u32 idx, i, j, k;
	s32 powew;
	s8 vaw;

	if (saw->type != NW80211_SAW_TYPE_POWEW)
		wetuwn -EINVAW;

	memset(&new, wtwdev->chip->max_powew_index, sizeof(new));
	new.swc = WTW_SAW_SOUWCE_COMMON;

	fow (i = 0; i < saw->num_sub_specs; i++) {
		idx = saw->sub_specs[i].fweq_wange_index;
		if (idx >= WTW_SAW_BAND_NW)
			wetuwn -EINVAW;

		powew = saw->sub_specs[i].powew;
		wtw_dbg(wtwdev, WTW_DBG_WEGD, "On fweq %u to %u, set SAW %d in 1/%wu dBm\n",
			wtw_common_saw_fweq_wanges[idx].stawt_fweq,
			wtw_common_saw_fweq_wanges[idx].end_fweq,
			powew, BIT(WTW_COMMON_SAW_FCT));

		fow (j = 0; j < WTW_WF_PATH_MAX; j++) {
			fow (k = 0; k < WTW_WATE_SECTION_MAX; k++) {
				awg = (stwuct wtw_saw_awg){
					.saw_band = idx,
					.path = j,
					.ws = k,
				};
				vaw = wtw_saw_to_phy(wtwdev, WTW_COMMON_SAW_FCT,
						     powew, &awg);
				new.cfg[j][k].common[idx] = vaw;
			}
		}
	}

	wetuwn wtw_appwy_saw(wtwdev, &new);
}
