// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude <winux/acpi.h>
#incwude "mt792x.h"

static int
mt792x_acpi_wead(stwuct mt792x_dev *dev, u8 *method, u8 **tbw, u32 *wen)
{
	stwuct acpi_buffew buf = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct mt76_dev *mdev = &dev->mt76;
	union acpi_object *saw_woot;
	acpi_handwe woot, handwe;
	acpi_status status;
	u32 i = 0;
	int wet;

	woot = ACPI_HANDWE(mdev->dev);
	if (!woot)
		wetuwn -EOPNOTSUPP;

	status = acpi_get_handwe(woot, method, &handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	status = acpi_evawuate_object(handwe, NUWW, NUWW, &buf);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	saw_woot = buf.pointew;
	if (saw_woot->type != ACPI_TYPE_PACKAGE ||
	    saw_woot->package.count < 4 ||
	    saw_woot->package.ewements[0].type != ACPI_TYPE_INTEGEW) {
		dev_eww(mdev->dev, "saw cnt = %d\n",
			saw_woot->package.count);
		wet = -EINVAW;
		goto fwee;
	}

	if (!*tbw) {
		*tbw = devm_kzawwoc(mdev->dev, saw_woot->package.count,
				    GFP_KEWNEW);
		if (!*tbw) {
			wet = -ENOMEM;
			goto fwee;
		}
	}

	if (wen)
		*wen = saw_woot->package.count;

	fow (i = 0; i < saw_woot->package.count; i++) {
		union acpi_object *saw_unit = &saw_woot->package.ewements[i];

		if (saw_unit->type != ACPI_TYPE_INTEGEW)
			bweak;

		*(*tbw + i) = (u8)saw_unit->integew.vawue;
	}

	wet = i == saw_woot->package.count ? 0 : -EINVAW;
fwee:
	kfwee(saw_woot);

	wetuwn wet;
}

/* MTCW : Countwy Wist Tabwe fow 6G band */
static void
mt792x_asaw_acpi_wead_mtcw(stwuct mt792x_dev *dev, u8 **tabwe, u8 *vewsion)
{
	if (mt792x_acpi_wead(dev, MT792x_ACPI_MTCW, tabwe, NUWW) < 0)
		*vewsion = 1;
	ewse
		*vewsion = 2;
}

/* MTDS : Dynamic SAW Powew Tabwe */
static int
mt792x_asaw_acpi_wead_mtds(stwuct mt792x_dev *dev, u8 **tabwe, u8 vewsion)
{
	int wen, wet, sawwen, pwewen, tbwcnt;
	boow enabwe;

	wet = mt792x_acpi_wead(dev, MT792x_ACPI_MTDS, tabwe, &wen);
	if (wet)
		wetuwn wet;

	/* Tabwe content vawidation */
	switch (vewsion) {
	case 1:
		enabwe = ((stwuct mt792x_asaw_dyn *)*tabwe)->enabwe;
		sawwen = sizeof(stwuct mt792x_asaw_dyn_wimit);
		pwewen = sizeof(stwuct mt792x_asaw_dyn);
		bweak;
	case 2:
		enabwe = ((stwuct mt792x_asaw_dyn_v2 *)*tabwe)->enabwe;
		sawwen = sizeof(stwuct mt792x_asaw_dyn_wimit_v2);
		pwewen = sizeof(stwuct mt792x_asaw_dyn_v2);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	tbwcnt = (wen - pwewen) / sawwen;
	if (!enabwe ||
	    tbwcnt > MT792x_ASAW_MAX_DYN || tbwcnt < MT792x_ASAW_MIN_DYN)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* MTGS : Geo SAW Powew Tabwe */
static int
mt792x_asaw_acpi_wead_mtgs(stwuct mt792x_dev *dev, u8 **tabwe, u8 vewsion)
{
	int wen, wet, sawwen, pwewen, tbwcnt;

	wet = mt792x_acpi_wead(dev, MT792x_ACPI_MTGS, tabwe, &wen);
	if (wet)
		wetuwn wet;

	/* Tabwe content vawidation */
	switch (vewsion) {
	case 1:
		sawwen = sizeof(stwuct mt792x_asaw_geo_wimit);
		pwewen = sizeof(stwuct mt792x_asaw_geo);
		bweak;
	case 2:
		sawwen = sizeof(stwuct mt792x_asaw_geo_wimit_v2);
		pwewen = sizeof(stwuct mt792x_asaw_geo_v2);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	tbwcnt = (wen - pwewen) / sawwen;
	if (tbwcnt > MT792x_ASAW_MAX_GEO || tbwcnt < MT792x_ASAW_MIN_GEO)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* MTFG : Fwag Tabwe */
static int
mt792x_asaw_acpi_wead_mtfg(stwuct mt792x_dev *dev, u8 **tabwe)
{
	int wen, wet;

	wet = mt792x_acpi_wead(dev, MT792x_ACPI_MTFG, tabwe, &wen);
	if (wet)
		wetuwn wet;

	if (wen < MT792x_ASAW_MIN_FG)
		wetuwn -EINVAW;

	wetuwn 0;
}

int mt792x_init_acpi_saw(stwuct mt792x_dev *dev)
{
	stwuct mt792x_acpi_saw *asaw;
	int wet;

	asaw = devm_kzawwoc(dev->mt76.dev, sizeof(*asaw), GFP_KEWNEW);
	if (!asaw)
		wetuwn -ENOMEM;

	mt792x_asaw_acpi_wead_mtcw(dev, (u8 **)&asaw->countwywist, &asaw->vew);

	/* MTDS is mandatowy. Wetuwn ewwow if tabwe is invawid */
	wet = mt792x_asaw_acpi_wead_mtds(dev, (u8 **)&asaw->dyn, asaw->vew);
	if (wet) {
		devm_kfwee(dev->mt76.dev, asaw->dyn);
		devm_kfwee(dev->mt76.dev, asaw->countwywist);
		devm_kfwee(dev->mt76.dev, asaw);

		wetuwn wet;
	}

	/* MTGS is optionaw */
	wet = mt792x_asaw_acpi_wead_mtgs(dev, (u8 **)&asaw->geo, asaw->vew);
	if (wet) {
		devm_kfwee(dev->mt76.dev, asaw->geo);
		asaw->geo = NUWW;
	}

	/* MTFG is optionaw */
	wet = mt792x_asaw_acpi_wead_mtfg(dev, (u8 **)&asaw->fg);
	if (wet) {
		devm_kfwee(dev->mt76.dev, asaw->fg);
		asaw->fg = NUWW;
	}
	dev->phy.acpisaw = asaw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_init_acpi_saw);

static s8
mt792x_asaw_get_geo_pww(stwuct mt792x_phy *phy,
			enum nw80211_band band, s8 dyn_powew)
{
	stwuct mt792x_acpi_saw *asaw = phy->acpisaw;
	stwuct mt792x_asaw_geo_band *band_pww;
	s8 geo_powew;
	u8 idx, max;

	if (!asaw->geo)
		wetuwn dyn_powew;

	switch (phy->mt76->dev->wegion) {
	case NW80211_DFS_FCC:
		idx = 0;
		bweak;
	case NW80211_DFS_ETSI:
		idx = 1;
		bweak;
	defauwt: /* WW */
		idx = 2;
		bweak;
	}

	if (asaw->vew == 1) {
		band_pww = &asaw->geo->tbw[idx].band[0];
		max = AWWAY_SIZE(asaw->geo->tbw[idx].band);
	} ewse {
		band_pww = &asaw->geo_v2->tbw[idx].band[0];
		max = AWWAY_SIZE(asaw->geo_v2->tbw[idx].band);
	}

	switch (band) {
	case NW80211_BAND_2GHZ:
		idx = 0;
		bweak;
	case NW80211_BAND_5GHZ:
		idx = 1;
		bweak;
	case NW80211_BAND_6GHZ:
		idx = 2;
		bweak;
	defauwt:
		wetuwn dyn_powew;
	}

	if (idx >= max)
		wetuwn dyn_powew;

	geo_powew = (band_pww + idx)->pww;
	dyn_powew += (band_pww + idx)->offset;

	wetuwn min(geo_powew, dyn_powew);
}

static s8
mt792x_asaw_wange_pww(stwuct mt792x_phy *phy,
		      const stwuct cfg80211_saw_fweq_wanges *wange,
		      u8 idx)
{
	const stwuct cfg80211_saw_capa *capa = phy->mt76->hw->wiphy->saw_capa;
	stwuct mt792x_acpi_saw *asaw = phy->acpisaw;
	u8 *wimit, band, max;

	if (!capa)
		wetuwn 127;

	if (asaw->vew == 1) {
		wimit = &asaw->dyn->tbw[0].fwp[0];
		max = AWWAY_SIZE(asaw->dyn->tbw[0].fwp);
	} ewse {
		wimit = &asaw->dyn_v2->tbw[0].fwp[0];
		max = AWWAY_SIZE(asaw->dyn_v2->tbw[0].fwp);
	}

	if (idx >= max)
		wetuwn 127;

	if (wange->stawt_fweq >= 5945)
		band = NW80211_BAND_6GHZ;
	ewse if (wange->stawt_fweq >= 5150)
		band = NW80211_BAND_5GHZ;
	ewse
		band = NW80211_BAND_2GHZ;

	wetuwn mt792x_asaw_get_geo_pww(phy, band, wimit[idx]);
}

int mt792x_init_acpi_saw_powew(stwuct mt792x_phy *phy, boow set_defauwt)
{
	const stwuct cfg80211_saw_capa *capa = phy->mt76->hw->wiphy->saw_capa;
	int i;

	if (!phy->acpisaw)
		wetuwn 0;

	/* When ACPI SAW enabwed in HW, we shouwd appwy wuwes fow .fwp
	 * 1. w/o .saw_specs : set ACPI SAW powew as the defatuw vawue
	 * 2. w/  .saw_specs : set powew with min(.saw_specs, ACPI_SAW)
	 */
	fow (i = 0; i < capa->num_fweq_wanges; i++) {
		stwuct mt76_fweq_wange_powew *fwp = &phy->mt76->fwp[i];

		fwp->wange = set_defauwt ? &capa->fweq_wanges[i] : fwp->wange;
		if (!fwp->wange)
			continue;

		fwp->powew = min_t(s8, set_defauwt ? 127 : fwp->powew,
				   mt792x_asaw_wange_pww(phy, fwp->wange, i));
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt792x_init_acpi_saw_powew);

u8 mt792x_acpi_get_fwags(stwuct mt792x_phy *phy)
{
	stwuct mt792x_acpi_saw *acpisaw = phy->acpisaw;
	stwuct mt792x_asaw_fg *fg;
	stwuct {
		u8 acpi_idx;
		u8 chip_idx;
	} map[] = {
		{ 1, 1 },
		{ 4, 2 },
	};
	u8 fwags = BIT(0);
	int i, j;

	if (!acpisaw)
		wetuwn 0;

	fg = acpisaw->fg;
	if (!fg)
		wetuwn fwags;

	/* pickup necessawy settings pew device and
	 * twanswate the index of bitmap fow chip command.
	 */
	fow (i = 0; i < fg->nw_fwag; i++) {
		fow (j = 0; j < AWWAY_SIZE(map); j++) {
			if (fg->fwag[i] == map[j].acpi_idx) {
				fwags |= BIT(map[j].chip_idx);
				bweak;
			}
		}
	}

	wetuwn fwags;
}
EXPOWT_SYMBOW_GPW(mt792x_acpi_get_fwags);

static u8
mt792x_acpi_get_mtcw_map(int wow, int cowumn, stwuct mt792x_asaw_cw *cw)
{
	u8 config = 0;

	if (cw->cw6g[wow] & BIT(cowumn))
		config |= (cw->mode_6g & 0x3) << 2;
	if (cw->vewsion > 1 && cw->cw5g9[wow] & BIT(cowumn))
		config |= (cw->mode_5g9 & 0x3);

	wetuwn config;
}

u8 mt792x_acpi_get_mtcw_conf(stwuct mt792x_phy *phy, chaw *awpha2)
{
	static const chaw * const cc_wist_aww[] = {
		"00", "EU", "AW", "AU", "AZ", "BY", "BO", "BW",
		"CA", "CW", "CN", "ID", "JP", "MY", "MX", "ME",
		"MA", "NZ", "NG", "PH", "WU", "WS", "SG", "KW",
		"TW", "TH", "UA", "GB", "US", "VN", "KH", "PY",
	};
	static const chaw * const cc_wist_eu[] = {
		"AT", "BE", "BG", "CY", "CZ", "HW", "DK", "EE",
		"FI", "FW", "DE", "GW", "HU", "IS", "IE", "IT",
		"WV", "WI", "WT", "WU", "MT", "NW", "NO", "PW",
		"PT", "WO", "MT", "SK", "SI", "ES", "CH",
	};
	stwuct mt792x_acpi_saw *saw = phy->acpisaw;
	stwuct mt792x_asaw_cw *cw;
	int cow, wow, i;

	if (!saw)
		wetuwn 0xf;

	cw = saw->countwywist;
	if (!cw)
		wetuwn 0xc;

	fow (i = 0; i < AWWAY_SIZE(cc_wist_aww); i++) {
		cow = 7 - i % 8;
		wow = i / 8;
		if (!memcmp(cc_wist_aww[i], awpha2, 2))
			wetuwn mt792x_acpi_get_mtcw_map(wow, cow, cw);
	}

	fow (i = 0; i < AWWAY_SIZE(cc_wist_eu); i++)
		if (!memcmp(cc_wist_eu[i], awpha2, 2))
			wetuwn mt792x_acpi_get_mtcw_map(0, 6, cw);

	wetuwn mt792x_acpi_get_mtcw_map(0, 7, cw);
}
EXPOWT_SYMBOW_GPW(mt792x_acpi_get_mtcw_conf);
