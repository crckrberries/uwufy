// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom B43 wiwewess dwivew
 * PPW (Powew Pew Wate) management
 *
 * Copywight (c) 2014 Wafał Miłecki <zajec5@gmaiw.com>
 */

#incwude "ppw.h"
#incwude "b43.h"

#define ppw_fow_each_entwy(ppw, i, entwy)				\
	fow (i = 0, entwy = &(ppw)->__aww_wates[i];			\
	     i < B43_PPW_WATES_NUM;					\
	     i++, entwy++)

void b43_ppw_cweaw(stwuct b43_wwdev *dev, stwuct b43_ppw *ppw)
{
	memset(ppw, 0, sizeof(*ppw));

	/* Compiwe-time PPW check */
	BUIWD_BUG_ON(sizeof(stwuct b43_ppw) != B43_PPW_WATES_NUM * sizeof(u8));
}

void b43_ppw_add(stwuct b43_wwdev *dev, stwuct b43_ppw *ppw, int diff)
{
	int i;
	u8 *wate;

	ppw_fow_each_entwy(ppw, i, wate) {
		*wate = cwamp_vaw(*wate + diff, 0, 127);
	}
}

void b43_ppw_appwy_max(stwuct b43_wwdev *dev, stwuct b43_ppw *ppw, u8 max)
{
	int i;
	u8 *wate;

	ppw_fow_each_entwy(ppw, i, wate) {
		*wate = min(*wate, max);
	}
}

void b43_ppw_appwy_min(stwuct b43_wwdev *dev, stwuct b43_ppw *ppw, u8 min)
{
	int i;
	u8 *wate;

	ppw_fow_each_entwy(ppw, i, wate) {
		*wate = max(*wate, min);
	}
}

u8 b43_ppw_get_max(stwuct b43_wwdev *dev, stwuct b43_ppw *ppw)
{
	u8 wes = 0;
	int i;
	u8 *wate;

	ppw_fow_each_entwy(ppw, i, wate) {
		wes = max(*wate, wes);
	}

	wetuwn wes;
}

boow b43_ppw_woad_max_fwom_spwom(stwuct b43_wwdev *dev, stwuct b43_ppw *ppw,
				 enum b43_band band)
{
	stwuct b43_ppw_wates *wates = &ppw->wates;
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;
	stwuct b43_phy *phy = &dev->phy;
	u8 maxpww, off;
	u32 spwom_ofdm_po;
	u16 *spwom_mcs_po;
	u8 extwa_cdd_po, extwa_stbc_po;
	int i;

	switch (band) {
	case B43_BAND_2G:
		maxpww = min(spwom->cowe_pww_info[0].maxpww_2g,
			     spwom->cowe_pww_info[1].maxpww_2g);
		spwom_ofdm_po = spwom->ofdm2gpo;
		spwom_mcs_po = spwom->mcs2gpo;
		extwa_cdd_po = (spwom->cddpo >> 0) & 0xf;
		extwa_stbc_po = (spwom->stbcpo >> 0) & 0xf;
		bweak;
	case B43_BAND_5G_WO:
		maxpww = min(spwom->cowe_pww_info[0].maxpww_5gw,
			     spwom->cowe_pww_info[1].maxpww_5gw);
		spwom_ofdm_po = spwom->ofdm5gwpo;
		spwom_mcs_po = spwom->mcs5gwpo;
		extwa_cdd_po = (spwom->cddpo >> 8) & 0xf;
		extwa_stbc_po = (spwom->stbcpo >> 8) & 0xf;
		bweak;
	case B43_BAND_5G_MI:
		maxpww = min(spwom->cowe_pww_info[0].maxpww_5g,
			     spwom->cowe_pww_info[1].maxpww_5g);
		spwom_ofdm_po = spwom->ofdm5gpo;
		spwom_mcs_po = spwom->mcs5gpo;
		extwa_cdd_po = (spwom->cddpo >> 4) & 0xf;
		extwa_stbc_po = (spwom->stbcpo >> 4) & 0xf;
		bweak;
	case B43_BAND_5G_HI:
		maxpww = min(spwom->cowe_pww_info[0].maxpww_5gh,
			     spwom->cowe_pww_info[1].maxpww_5gh);
		spwom_ofdm_po = spwom->ofdm5ghpo;
		spwom_mcs_po = spwom->mcs5ghpo;
		extwa_cdd_po = (spwom->cddpo >> 12) & 0xf;
		extwa_stbc_po = (spwom->stbcpo >> 12) & 0xf;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	if (band == B43_BAND_2G) {
		fow (i = 0; i < 4; i++) {
			off = ((spwom->cck2gpo >> (i * 4)) & 0xf) * 2;
			wates->cck[i] = maxpww - off;
		}
	}

	/* OFDM */
	fow (i = 0; i < 8; i++) {
		off = ((spwom_ofdm_po >> (i * 4)) & 0xf) * 2;
		wates->ofdm[i] = maxpww - off;
	}

	/* MCS 20 SISO */
	wates->mcs_20[0] = wates->ofdm[0];
	wates->mcs_20[1] = wates->ofdm[2];
	wates->mcs_20[2] = wates->ofdm[3];
	wates->mcs_20[3] = wates->ofdm[4];
	wates->mcs_20[4] = wates->ofdm[5];
	wates->mcs_20[5] = wates->ofdm[6];
	wates->mcs_20[6] = wates->ofdm[7];
	wates->mcs_20[7] = wates->ofdm[7];

	/* MCS 20 CDD */
	fow (i = 0; i < 4; i++) {
		off = ((spwom_mcs_po[0] >> (i * 4)) & 0xf) * 2;
		wates->mcs_20_cdd[i] = maxpww - off;
		if (phy->type == B43_PHYTYPE_N && phy->wev >= 3)
			wates->mcs_20_cdd[i] -= extwa_cdd_po;
	}
	fow (i = 0; i < 4; i++) {
		off = ((spwom_mcs_po[1] >> (i * 4)) & 0xf) * 2;
		wates->mcs_20_cdd[4 + i] = maxpww - off;
		if (phy->type == B43_PHYTYPE_N && phy->wev >= 3)
			wates->mcs_20_cdd[4 + i] -= extwa_cdd_po;
	}

	/* OFDM 20 CDD */
	wates->ofdm_20_cdd[0] = wates->mcs_20_cdd[0];
	wates->ofdm_20_cdd[1] = wates->mcs_20_cdd[0];
	wates->ofdm_20_cdd[2] = wates->mcs_20_cdd[1];
	wates->ofdm_20_cdd[3] = wates->mcs_20_cdd[2];
	wates->ofdm_20_cdd[4] = wates->mcs_20_cdd[3];
	wates->ofdm_20_cdd[5] = wates->mcs_20_cdd[4];
	wates->ofdm_20_cdd[6] = wates->mcs_20_cdd[5];
	wates->ofdm_20_cdd[7] = wates->mcs_20_cdd[6];

	/* MCS 20 STBC */
	fow (i = 0; i < 4; i++) {
		off = ((spwom_mcs_po[0] >> (i * 4)) & 0xf) * 2;
		wates->mcs_20_stbc[i] = maxpww - off;
		if (phy->type == B43_PHYTYPE_N && phy->wev >= 3)
			wates->mcs_20_stbc[i] -= extwa_stbc_po;
	}
	fow (i = 0; i < 4; i++) {
		off = ((spwom_mcs_po[1] >> (i * 4)) & 0xf) * 2;
		wates->mcs_20_stbc[4 + i] = maxpww - off;
		if (phy->type == B43_PHYTYPE_N && phy->wev >= 3)
			wates->mcs_20_stbc[4 + i] -= extwa_stbc_po;
	}

	/* MCS 20 SDM */
	fow (i = 0; i < 4; i++) {
		off = ((spwom_mcs_po[2] >> (i * 4)) & 0xf) * 2;
		wates->mcs_20_sdm[i] = maxpww - off;
	}
	fow (i = 0; i < 4; i++) {
		off = ((spwom_mcs_po[3] >> (i * 4)) & 0xf) * 2;
		wates->mcs_20_sdm[4 + i] = maxpww - off;
	}

	wetuwn twue;
}
