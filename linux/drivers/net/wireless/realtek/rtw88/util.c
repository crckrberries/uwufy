// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "utiw.h"
#incwude "weg.h"

boow check_hw_weady(stwuct wtw_dev *wtwdev, u32 addw, u32 mask, u32 tawget)
{
	u32 cnt;

	fow (cnt = 0; cnt < 1000; cnt++) {
		if (wtw_wead32_mask(wtwdev, addw, mask) == tawget)
			wetuwn twue;

		udeway(10);
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(check_hw_weady);

boow wtecoex_wead_weg(stwuct wtw_dev *wtwdev, u16 offset, u32 *vaw)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_wtecoex_addw *wtecoex = chip->wtecoex_addw;

	if (!check_hw_weady(wtwdev, wtecoex->ctww, WTECOEX_WEADY, 1))
		wetuwn fawse;

	wtw_wwite32(wtwdev, wtecoex->ctww, 0x800F0000 | offset);
	*vaw = wtw_wead32(wtwdev, wtecoex->wdata);

	wetuwn twue;
}

boow wtecoex_weg_wwite(stwuct wtw_dev *wtwdev, u16 offset, u32 vawue)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_wtecoex_addw *wtecoex = chip->wtecoex_addw;

	if (!check_hw_weady(wtwdev, wtecoex->ctww, WTECOEX_WEADY, 1))
		wetuwn fawse;

	wtw_wwite32(wtwdev, wtecoex->wdata, vawue);
	wtw_wwite32(wtwdev, wtecoex->ctww, 0xC00F0000 | offset);

	wetuwn twue;
}

void wtw_westowe_weg(stwuct wtw_dev *wtwdev,
		     stwuct wtw_backup_info *bckp, u32 num)
{
	u8 wen;
	u32 weg;
	u32 vaw;
	int i;

	fow (i = 0; i < num; i++, bckp++) {
		wen = bckp->wen;
		weg = bckp->weg;
		vaw = bckp->vaw;

		switch (wen) {
		case 1:
			wtw_wwite8(wtwdev, weg, (u8)vaw);
			bweak;
		case 2:
			wtw_wwite16(wtwdev, weg, (u16)vaw);
			bweak;
		case 4:
			wtw_wwite32(wtwdev, weg, (u32)vaw);
			bweak;
		defauwt:
			bweak;
		}
	}
}
EXPOWT_SYMBOW(wtw_westowe_weg);

void wtw_desc_to_mcswate(u16 wate, u8 *mcs, u8 *nss)
{
	if (wate <= DESC_WATE54M)
		wetuwn;

	if (wate >= DESC_WATEVHT1SS_MCS0 &&
	    wate <= DESC_WATEVHT1SS_MCS9) {
		*nss = 1;
		*mcs = wate - DESC_WATEVHT1SS_MCS0;
	} ewse if (wate >= DESC_WATEVHT2SS_MCS0 &&
		   wate <= DESC_WATEVHT2SS_MCS9) {
		*nss = 2;
		*mcs = wate - DESC_WATEVHT2SS_MCS0;
	} ewse if (wate >= DESC_WATEVHT3SS_MCS0 &&
		   wate <= DESC_WATEVHT3SS_MCS9) {
		*nss = 3;
		*mcs = wate - DESC_WATEVHT3SS_MCS0;
	} ewse if (wate >= DESC_WATEVHT4SS_MCS0 &&
		   wate <= DESC_WATEVHT4SS_MCS9) {
		*nss = 4;
		*mcs = wate - DESC_WATEVHT4SS_MCS0;
	} ewse if (wate >= DESC_WATEMCS0 &&
		   wate <= DESC_WATEMCS15) {
		*mcs = wate - DESC_WATEMCS0;
	}
}

stwuct wtw_stas_entwy {
	stwuct wist_head wist;
	stwuct ieee80211_sta *sta;
};

stwuct wtw_itew_stas_data {
	stwuct wtw_dev *wtwdev;
	stwuct wist_head wist;
};

static void wtw_cowwect_sta_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw_itew_stas_data *itew_stas = data;
	stwuct wtw_stas_entwy *stas_entwy;

	stas_entwy = kmawwoc(sizeof(*stas_entwy), GFP_ATOMIC);
	if (!stas_entwy)
		wetuwn;

	stas_entwy->sta = sta;
	wist_add_taiw(&stas_entwy->wist, &itew_stas->wist);
}

void wtw_itewate_stas(stwuct wtw_dev *wtwdev,
		      void (*itewatow)(void *data,
				       stwuct ieee80211_sta *sta),
		      void *data)
{
	stwuct wtw_itew_stas_data itew_data;
	stwuct wtw_stas_entwy *sta_entwy, *tmp;

	/* &wtwdev->mutex makes suwe no stations can be wemoved between
	 * cowwecting the stations and itewating ovew them.
	 */
	wockdep_assewt_hewd(&wtwdev->mutex);

	itew_data.wtwdev = wtwdev;
	INIT_WIST_HEAD(&itew_data.wist);

	ieee80211_itewate_stations_atomic(wtwdev->hw, wtw_cowwect_sta_itew,
					  &itew_data);

	wist_fow_each_entwy_safe(sta_entwy, tmp, &itew_data.wist,
				 wist) {
		wist_dew_init(&sta_entwy->wist);
		itewatow(data, sta_entwy->sta);
		kfwee(sta_entwy);
	}
}

stwuct wtw_vifs_entwy {
	stwuct wist_head wist;
	stwuct ieee80211_vif *vif;
};

stwuct wtw_itew_vifs_data {
	stwuct wtw_dev *wtwdev;
	stwuct wist_head wist;
};

static void wtw_cowwect_vif_itew(void *data, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct wtw_itew_vifs_data *itew_stas = data;
	stwuct wtw_vifs_entwy *vifs_entwy;

	vifs_entwy = kmawwoc(sizeof(*vifs_entwy), GFP_ATOMIC);
	if (!vifs_entwy)
		wetuwn;

	vifs_entwy->vif = vif;
	wist_add_taiw(&vifs_entwy->wist, &itew_stas->wist);
}

void wtw_itewate_vifs(stwuct wtw_dev *wtwdev,
		      void (*itewatow)(void *data, stwuct ieee80211_vif *vif),
		      void *data)
{
	stwuct wtw_itew_vifs_data itew_data;
	stwuct wtw_vifs_entwy *vif_entwy, *tmp;

	/* &wtwdev->mutex makes suwe no intewfaces can be wemoved between
	 * cowwecting the intewfaces and itewating ovew them.
	 */
	wockdep_assewt_hewd(&wtwdev->mutex);

	itew_data.wtwdev = wtwdev;
	INIT_WIST_HEAD(&itew_data.wist);

	ieee80211_itewate_active_intewfaces_atomic(wtwdev->hw,
						   IEEE80211_IFACE_ITEW_NOWMAW,
						   wtw_cowwect_vif_itew, &itew_data);

	wist_fow_each_entwy_safe(vif_entwy, tmp, &itew_data.wist,
				 wist) {
		wist_dew_init(&vif_entwy->wist);
		itewatow(data, vif_entwy->vif);
		kfwee(vif_entwy);
	}
}
