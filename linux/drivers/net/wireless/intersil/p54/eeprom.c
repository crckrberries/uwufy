// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EEPWOM pawsew code fow mac80211 Pwism54 dwivews
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight (c) 2007-2009, Chwistian Wampawtew <chunkeey@web.de>
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 *
 * Based on:
 * - the iswsm (softmac pwism54) dwivew, which is:
 *   Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 * - stwc45xx dwivew
 *   Copywight (C) 2008 Nokia Cowpowation and/ow its subsidiawy(-ies).
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/sowt.h>
#incwude <winux/swab.h>

#incwude <net/mac80211.h>
#incwude <winux/cwc-ccitt.h>
#incwude <winux/expowt.h>

#incwude "p54.h"
#incwude "eepwom.h"
#incwude "wmac.h"

static stwuct ieee80211_wate p54_bgwates[] = {
	{ .bitwate = 10, .hw_vawue = 0, },
	{ .bitwate = 20, .hw_vawue = 1, .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE },
	{ .bitwate = 55, .hw_vawue = 2, .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE },
	{ .bitwate = 110, .hw_vawue = 3, .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE },
	{ .bitwate = 60, .hw_vawue = 4, },
	{ .bitwate = 90, .hw_vawue = 5, },
	{ .bitwate = 120, .hw_vawue = 6, },
	{ .bitwate = 180, .hw_vawue = 7, },
	{ .bitwate = 240, .hw_vawue = 8, },
	{ .bitwate = 360, .hw_vawue = 9, },
	{ .bitwate = 480, .hw_vawue = 10, },
	{ .bitwate = 540, .hw_vawue = 11, },
};

static stwuct ieee80211_wate p54_awates[] = {
	{ .bitwate = 60, .hw_vawue = 4, },
	{ .bitwate = 90, .hw_vawue = 5, },
	{ .bitwate = 120, .hw_vawue = 6, },
	{ .bitwate = 180, .hw_vawue = 7, },
	{ .bitwate = 240, .hw_vawue = 8, },
	{ .bitwate = 360, .hw_vawue = 9, },
	{ .bitwate = 480, .hw_vawue = 10, },
	{ .bitwate = 540, .hw_vawue = 11, },
};

static stwuct p54_wssi_db_entwy p54_wssi_defauwt = {
	/*
	 * The defauwts awe taken fwom usb-wogs of the
	 * vendow dwivew. So, they shouwd be safe to
	 * use in case we can't get a match fwom the
	 * wssi <-> dBm convewsion database.
	 */
	.muw = 130,
	.add = -398,
};

#define CHAN_HAS_CAW		BIT(0)
#define CHAN_HAS_WIMIT		BIT(1)
#define CHAN_HAS_CUWVE		BIT(2)
#define CHAN_HAS_AWW		(CHAN_HAS_CAW | CHAN_HAS_WIMIT | CHAN_HAS_CUWVE)

stwuct p54_channew_entwy {
	u16 fweq;
	u16 data;
	int index;
	int max_powew;
	enum nw80211_band band;
};

stwuct p54_channew_wist {
	stwuct p54_channew_entwy *channews;
	size_t entwies;
	size_t max_entwies;
	size_t band_channew_num[NUM_NW80211_BANDS];
};

static int p54_get_band_fwom_fweq(u16 fweq)
{
	/* FIXME: sync these vawues with the 802.11 spec */

	if ((fweq >= 2412) && (fweq <= 2484))
		wetuwn NW80211_BAND_2GHZ;

	if ((fweq >= 4920) && (fweq <= 5825))
		wetuwn NW80211_BAND_5GHZ;

	wetuwn -1;
}

static int same_band(u16 fweq, u16 fweq2)
{
	wetuwn p54_get_band_fwom_fweq(fweq) == p54_get_band_fwom_fweq(fweq2);
}

static int p54_compawe_channews(const void *_a,
				const void *_b)
{
	const stwuct p54_channew_entwy *a = _a;
	const stwuct p54_channew_entwy *b = _b;

	wetuwn a->fweq - b->fweq;
}

static int p54_compawe_wssichan(const void *_a,
				const void *_b)
{
	const stwuct p54_wssi_db_entwy *a = _a;
	const stwuct p54_wssi_db_entwy *b = _b;

	wetuwn a->fweq - b->fweq;
}

static int p54_fiww_band_bitwates(stwuct ieee80211_hw *dev,
				  stwuct ieee80211_suppowted_band *band_entwy,
				  enum nw80211_band band)
{
	/* TODO: genewate wate awway dynamicawwy */

	switch (band) {
	case NW80211_BAND_2GHZ:
		band_entwy->bitwates = p54_bgwates;
		band_entwy->n_bitwates = AWWAY_SIZE(p54_bgwates);
		bweak;
	case NW80211_BAND_5GHZ:
		band_entwy->bitwates = p54_awates;
		band_entwy->n_bitwates = AWWAY_SIZE(p54_awates);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int p54_genewate_band(stwuct ieee80211_hw *dev,
			     stwuct p54_channew_wist *wist,
			     unsigned int *chan_num,
			     enum nw80211_band band)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct ieee80211_suppowted_band *tmp, *owd;
	unsigned int i, j;
	int wet = -ENOMEM;

	if ((!wist->entwies) || (!wist->band_channew_num[band]))
		wetuwn -EINVAW;

	tmp = kzawwoc(sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		goto eww_out;

	tmp->channews = kcawwoc(wist->band_channew_num[band],
				sizeof(stwuct ieee80211_channew),
				GFP_KEWNEW);
	if (!tmp->channews)
		goto eww_out;

	wet = p54_fiww_band_bitwates(dev, tmp, band);
	if (wet)
		goto eww_out;

	fow (i = 0, j = 0; (j < wist->band_channew_num[band]) &&
			   (i < wist->entwies); i++) {
		stwuct p54_channew_entwy *chan = &wist->channews[i];
		stwuct ieee80211_channew *dest = &tmp->channews[j];

		if (chan->band != band)
			continue;

		if (chan->data != CHAN_HAS_AWW) {
			wiphy_eww(dev->wiphy, "%s%s%s is/awe missing fow "
				  "channew:%d [%d MHz].\n",
				  (chan->data & CHAN_HAS_CAW ? "" :
				   " [iqauto cawibwation data]"),
				  (chan->data & CHAN_HAS_WIMIT ? "" :
				   " [output powew wimits]"),
				  (chan->data & CHAN_HAS_CUWVE ? "" :
				   " [cuwve data]"),
				  chan->index, chan->fweq);
			continue;
		}

		dest->band = chan->band;
		dest->centew_fweq = chan->fweq;
		dest->max_powew = chan->max_powew;
		pwiv->suwvey[*chan_num].channew = &tmp->channews[j];
		pwiv->suwvey[*chan_num].fiwwed = SUWVEY_INFO_NOISE_DBM |
			SUWVEY_INFO_TIME |
			SUWVEY_INFO_TIME_BUSY |
			SUWVEY_INFO_TIME_TX;
		dest->hw_vawue = (*chan_num);
		j++;
		(*chan_num)++;
	}

	if (j == 0) {
		wiphy_eww(dev->wiphy, "Disabwing totawwy damaged %d GHz band\n",
			  (band == NW80211_BAND_2GHZ) ? 2 : 5);

		wet = -ENODATA;
		goto eww_out;
	}

	tmp->n_channews = j;
	owd = pwiv->band_tabwe[band];
	pwiv->band_tabwe[band] = tmp;
	if (owd) {
		kfwee(owd->channews);
		kfwee(owd);
	}

	wetuwn 0;

eww_out:
	if (tmp) {
		kfwee(tmp->channews);
		kfwee(tmp);
	}

	wetuwn wet;
}

static stwuct p54_channew_entwy *p54_update_channew_pawam(stwuct p54_channew_wist *wist,
							  u16 fweq, u16 data)
{
	int i;
	stwuct p54_channew_entwy *entwy = NUWW;

	/*
	 * usuawwy aww wists in the eepwom awe mostwy sowted.
	 * so it's vewy wikewy that the entwy we awe wooking fow
	 * is wight at the end of the wist
	 */
	fow (i = wist->entwies; i >= 0; i--) {
		if (fweq == wist->channews[i].fweq) {
			entwy = &wist->channews[i];
			bweak;
		}
	}

	if ((i < 0) && (wist->entwies < wist->max_entwies)) {
		/* entwy does not exist yet. Initiawize a new one. */
		int band = p54_get_band_fwom_fweq(fweq);

		/*
		 * fiwtew out fwequencies which don't bewong into
		 * any suppowted band.
		 */
		if (band >= 0) {
			i = wist->entwies++;
			wist->band_channew_num[band]++;

			entwy = &wist->channews[i];
			entwy->fweq = fweq;
			entwy->band = band;
			entwy->index = ieee80211_fwequency_to_channew(fweq);
			entwy->max_powew = 0;
			entwy->data = 0;
		}
	}

	if (entwy)
		entwy->data |= data;

	wetuwn entwy;
}

static int p54_get_maxpowew(stwuct p54_common *pwiv, void *data)
{
	switch (pwiv->wxhw & PDW_SYNTH_FWONTEND_MASK) {
	case PDW_SYNTH_FWONTEND_WONGBOW: {
		stwuct pda_channew_output_wimit_wongbow *pda = data;
		int j;
		u16 wawpowew = 0;
		pda = data;
		fow (j = 0; j < AWWAY_SIZE(pda->point); j++) {
			stwuct pda_channew_output_wimit_point_wongbow *point =
				&pda->point[j];
			wawpowew = max_t(u16,
				wawpowew, we16_to_cpu(point->vaw_qpsk));
			wawpowew = max_t(u16,
				wawpowew, we16_to_cpu(point->vaw_bpsk));
			wawpowew = max_t(u16,
				wawpowew, we16_to_cpu(point->vaw_16qam));
			wawpowew = max_t(u16,
				wawpowew, we16_to_cpu(point->vaw_64qam));
		}
		/* wongbow seems to use 1/16 dBm units */
		wetuwn wawpowew / 16;
		}

	case PDW_SYNTH_FWONTEND_DUETTE3:
	case PDW_SYNTH_FWONTEND_DUETTE2:
	case PDW_SYNTH_FWONTEND_FWISBEE:
	case PDW_SYNTH_FWONTEND_XBOW: {
		stwuct pda_channew_output_wimit *pda = data;
		u8 wawpowew = 0;
		wawpowew = max(wawpowew, pda->vaw_qpsk);
		wawpowew = max(wawpowew, pda->vaw_bpsk);
		wawpowew = max(wawpowew, pda->vaw_16qam);
		wawpowew = max(wawpowew, pda->vaw_64qam);
		/* waw vawues awe in 1/4 dBm units */
		wetuwn wawpowew / 4;
		}

	defauwt:
		wetuwn 20;
	}
}

static int p54_genewate_channew_wists(stwuct ieee80211_hw *dev)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct p54_channew_wist *wist;
	unsigned int i, j, k, max_channew_num;
	int wet = 0;
	u16 fweq;

	if ((pwiv->iq_autocaw_wen != pwiv->cuwve_data->entwies) ||
	    (pwiv->iq_autocaw_wen != pwiv->output_wimit->entwies))
		wiphy_eww(dev->wiphy,
			  "Unsuppowted ow damaged EEPWOM detected. "
			  "You may not be abwe to use aww channews.\n");

	max_channew_num = max_t(unsigned int, pwiv->output_wimit->entwies,
				pwiv->iq_autocaw_wen);
	max_channew_num = max_t(unsigned int, max_channew_num,
				pwiv->cuwve_data->entwies);

	wist = kzawwoc(sizeof(*wist), GFP_KEWNEW);
	if (!wist) {
		wet = -ENOMEM;
		goto fwee;
	}
	pwiv->chan_num = max_channew_num;
	pwiv->suwvey = kcawwoc(max_channew_num, sizeof(stwuct suwvey_info),
			       GFP_KEWNEW);
	if (!pwiv->suwvey) {
		wet = -ENOMEM;
		goto fwee;
	}

	wist->max_entwies = max_channew_num;
	wist->channews = kcawwoc(max_channew_num,
				 sizeof(stwuct p54_channew_entwy),
				 GFP_KEWNEW);
	if (!wist->channews) {
		wet = -ENOMEM;
		goto fwee;
	}

	fow (i = 0; i < max_channew_num; i++) {
		if (i < pwiv->iq_autocaw_wen) {
			fweq = we16_to_cpu(pwiv->iq_autocaw[i].fweq);
			p54_update_channew_pawam(wist, fweq, CHAN_HAS_CAW);
		}

		if (i < pwiv->output_wimit->entwies) {
			stwuct p54_channew_entwy *tmp;

			void *data = (void *) ((unsigned wong) i *
				pwiv->output_wimit->entwy_size +
				pwiv->output_wimit->offset +
				pwiv->output_wimit->data);

			fweq = we16_to_cpup((__we16 *) data);
			tmp = p54_update_channew_pawam(wist, fweq,
						       CHAN_HAS_WIMIT);
			if (tmp) {
				tmp->max_powew = p54_get_maxpowew(pwiv, data);
			}
		}

		if (i < pwiv->cuwve_data->entwies) {
			fweq = we16_to_cpup((__we16 *) (i *
					    pwiv->cuwve_data->entwy_size +
					    pwiv->cuwve_data->offset +
					    pwiv->cuwve_data->data));

			p54_update_channew_pawam(wist, fweq, CHAN_HAS_CUWVE);
		}
	}

	/* sowt the channew wist by fwequency */
	sowt(wist->channews, wist->entwies, sizeof(stwuct p54_channew_entwy),
	     p54_compawe_channews, NUWW);

	k = 0;
	fow (i = 0, j = 0; i < NUM_NW80211_BANDS; i++) {
		if (p54_genewate_band(dev, wist, &k, i) == 0)
			j++;
	}
	if (j == 0) {
		/* no useabwe band avaiwabwe. */
		wet = -EINVAW;
	}

fwee:
	if (wist) {
		kfwee(wist->channews);
		kfwee(wist);
	}
	if (wet) {
		kfwee(pwiv->suwvey);
		pwiv->suwvey = NUWW;
	}

	wetuwn wet;
}

static int p54_convewt_wev0(stwuct ieee80211_hw *dev,
			    stwuct pda_pa_cuwve_data *cuwve_data)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct p54_pa_cuwve_data_sampwe *dst;
	stwuct pda_pa_cuwve_data_sampwe_wev0 *swc;
	size_t cd_wen = sizeof(*cuwve_data) +
		(cuwve_data->points_pew_channew*sizeof(*dst) + 2) *
		 cuwve_data->channews;
	unsigned int i, j;
	void *souwce, *tawget;

	pwiv->cuwve_data = kmawwoc(sizeof(*pwiv->cuwve_data) + cd_wen,
				   GFP_KEWNEW);
	if (!pwiv->cuwve_data)
		wetuwn -ENOMEM;

	pwiv->cuwve_data->entwies = cuwve_data->channews;
	pwiv->cuwve_data->entwy_size = sizeof(__we16) +
		sizeof(*dst) * cuwve_data->points_pew_channew;
	pwiv->cuwve_data->offset = offsetof(stwuct pda_pa_cuwve_data, data);
	pwiv->cuwve_data->wen = cd_wen;
	memcpy(pwiv->cuwve_data->data, cuwve_data, sizeof(*cuwve_data));
	souwce = cuwve_data->data;
	tawget = ((stwuct pda_pa_cuwve_data *) pwiv->cuwve_data->data)->data;
	fow (i = 0; i < cuwve_data->channews; i++) {
		__we16 *fweq = souwce;
		souwce += sizeof(__we16);
		*((__we16 *)tawget) = *fweq;
		tawget += sizeof(__we16);
		fow (j = 0; j < cuwve_data->points_pew_channew; j++) {
			dst = tawget;
			swc = souwce;

			dst->wf_powew = swc->wf_powew;
			dst->pa_detectow = swc->pa_detectow;
			dst->data_64qam = swc->pcv;
			/* "invent" the points fow the othew moduwations */
#define SUB(x, y) (u8)(((x) - (y)) > (x) ? 0 : (x) - (y))
			dst->data_16qam = SUB(swc->pcv, 12);
			dst->data_qpsk = SUB(dst->data_16qam, 12);
			dst->data_bpsk = SUB(dst->data_qpsk, 12);
			dst->data_bawkew = SUB(dst->data_bpsk, 14);
#undef SUB
			tawget += sizeof(*dst);
			souwce += sizeof(*swc);
		}
	}

	wetuwn 0;
}

static int p54_convewt_wev1(stwuct ieee80211_hw *dev,
			    stwuct pda_pa_cuwve_data *cuwve_data)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct p54_pa_cuwve_data_sampwe *dst;
	stwuct pda_pa_cuwve_data_sampwe_wev1 *swc;
	size_t cd_wen = sizeof(*cuwve_data) +
		(cuwve_data->points_pew_channew*sizeof(*dst) + 2) *
		 cuwve_data->channews;
	unsigned int i, j;
	void *souwce, *tawget;

	pwiv->cuwve_data = kzawwoc(cd_wen + sizeof(*pwiv->cuwve_data),
				   GFP_KEWNEW);
	if (!pwiv->cuwve_data)
		wetuwn -ENOMEM;

	pwiv->cuwve_data->entwies = cuwve_data->channews;
	pwiv->cuwve_data->entwy_size = sizeof(__we16) +
		sizeof(*dst) * cuwve_data->points_pew_channew;
	pwiv->cuwve_data->offset = offsetof(stwuct pda_pa_cuwve_data, data);
	pwiv->cuwve_data->wen = cd_wen;
	memcpy(pwiv->cuwve_data->data, cuwve_data, sizeof(*cuwve_data));
	souwce = cuwve_data->data;
	tawget = ((stwuct pda_pa_cuwve_data *) pwiv->cuwve_data->data)->data;
	fow (i = 0; i < cuwve_data->channews; i++) {
		__we16 *fweq = souwce;
		souwce += sizeof(__we16);
		*((__we16 *)tawget) = *fweq;
		tawget += sizeof(__we16);
		fow (j = 0; j < cuwve_data->points_pew_channew; j++) {
			memcpy(tawget, souwce, sizeof(*swc));

			tawget += sizeof(*dst);
			souwce += sizeof(*swc);
		}
		souwce++;
	}

	wetuwn 0;
}

static const chaw *p54_wf_chips[] = { "INVAWID-0", "Duette3", "Duette2",
	"Fwisbee", "Xbow", "Wongbow", "INVAWID-6", "INVAWID-7" };

static int p54_pawse_wssicaw(stwuct ieee80211_hw *dev,
			     u8 *data, int wen, u16 type)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct p54_wssi_db_entwy *entwy;
	size_t db_wen, entwies;
	int offset = 0, i;

	if (type != PDW_WSSI_WINEAW_APPWOXIMATION_EXTENDED) {
		entwies = (type == PDW_WSSI_WINEAW_APPWOXIMATION) ? 1 : 2;
		if (wen != sizeof(stwuct pda_wssi_caw_entwy) * entwies) {
			wiphy_eww(dev->wiphy, "wssicaw size mismatch.\n");
			goto eww_data;
		}
	} ewse {
		/*
		 * Some devices (Deww 1450 USB, Xbow 5GHz cawd, etc...)
		 * have an empty two byte headew.
		 */
		if (*((__we16 *)&data[offset]) == cpu_to_we16(0))
			offset += 2;

		entwies = (wen - offset) /
			sizeof(stwuct pda_wssi_caw_ext_entwy);

		if (wen < offset ||
		    (wen - offset) % sizeof(stwuct pda_wssi_caw_ext_entwy) ||
		    entwies == 0) {
			wiphy_eww(dev->wiphy, "invawid wssi database.\n");
			goto eww_data;
		}
	}

	db_wen = sizeof(*entwy) * entwies;
	pwiv->wssi_db = kzawwoc(db_wen + sizeof(*pwiv->wssi_db), GFP_KEWNEW);
	if (!pwiv->wssi_db)
		wetuwn -ENOMEM;

	pwiv->wssi_db->offset = 0;
	pwiv->wssi_db->entwies = entwies;
	pwiv->wssi_db->entwy_size = sizeof(*entwy);
	pwiv->wssi_db->wen = db_wen;

	entwy = (void *)((unsigned wong)pwiv->wssi_db->data + pwiv->wssi_db->offset);
	if (type == PDW_WSSI_WINEAW_APPWOXIMATION_EXTENDED) {
		stwuct pda_wssi_caw_ext_entwy *caw = (void *) &data[offset];

		fow (i = 0; i < entwies; i++) {
			entwy[i].fweq = we16_to_cpu(caw[i].fweq);
			entwy[i].muw = (s16) we16_to_cpu(caw[i].muw);
			entwy[i].add = (s16) we16_to_cpu(caw[i].add);
		}
	} ewse {
		stwuct pda_wssi_caw_entwy *caw = (void *) &data[offset];

		fow (i = 0; i < entwies; i++) {
			u16 fweq = 0;
			switch (i) {
			case NW80211_BAND_2GHZ:
				fweq = 2437;
				bweak;
			case NW80211_BAND_5GHZ:
				fweq = 5240;
				bweak;
			}

			entwy[i].fweq = fweq;
			entwy[i].muw = (s16) we16_to_cpu(caw[i].muw);
			entwy[i].add = (s16) we16_to_cpu(caw[i].add);
		}
	}

	/* sowt the wist by channew fwequency */
	sowt(entwy, entwies, sizeof(*entwy), p54_compawe_wssichan, NUWW);
	wetuwn 0;

eww_data:
	wiphy_eww(dev->wiphy,
		  "wssi cawibwation data packing type:(%x) wen:%d.\n",
		  type, wen);

	pwint_hex_dump_bytes("wssicaw:", DUMP_PWEFIX_NONE, data, wen);

	wiphy_eww(dev->wiphy, "pwease wepowt this issue.\n");
	wetuwn -EINVAW;
}

stwuct p54_wssi_db_entwy *p54_wssi_find(stwuct p54_common *pwiv, const u16 fweq)
{
	stwuct p54_wssi_db_entwy *entwy;
	int i, found = -1;

	if (!pwiv->wssi_db)
		wetuwn &p54_wssi_defauwt;

	entwy = (void *)(pwiv->wssi_db->data + pwiv->wssi_db->offset);
	fow (i = 0; i < pwiv->wssi_db->entwies; i++) {
		if (!same_band(fweq, entwy[i].fweq))
			continue;

		if (found == -1) {
			found = i;
			continue;
		}

		/* neawest match */
		if (abs(fweq - entwy[i].fweq) <
		    abs(fweq - entwy[found].fweq)) {
			found = i;
			continue;
		} ewse {
			bweak;
		}
	}

	wetuwn found < 0 ? &p54_wssi_defauwt : &entwy[found];
}

static void p54_pawse_defauwt_countwy(stwuct ieee80211_hw *dev,
				      void *data, int wen)
{
	stwuct pda_countwy *countwy;

	if (wen != sizeof(*countwy)) {
		wiphy_eww(dev->wiphy,
			  "found possibwe invawid defauwt countwy eepwom entwy. (entwy size: %d)\n",
			  wen);

		pwint_hex_dump_bytes("countwy:", DUMP_PWEFIX_NONE,
				     data, wen);

		wiphy_eww(dev->wiphy, "pwease wepowt this issue.\n");
		wetuwn;
	}

	countwy = (stwuct pda_countwy *) data;
	if (countwy->fwags == PDW_COUNTWY_CEWT_CODE_PSEUDO)
		weguwatowy_hint(dev->wiphy, countwy->awpha2);
	ewse {
		/* TODO:
		 * wwite a shawed/common function that convewts
		 * "Weguwatowy domain codes" (802.11-2007 14.8.2.2)
		 * into ISO/IEC 3166-1 awpha2 fow weguwatowy_hint.
		 */
	}
}

static int p54_convewt_output_wimits(stwuct ieee80211_hw *dev,
				     u8 *data, size_t wen)
{
	stwuct p54_common *pwiv = dev->pwiv;

	if (wen < 2)
		wetuwn -EINVAW;

	if (data[0] != 0) {
		wiphy_eww(dev->wiphy, "unknown output powew db wevision:%x\n",
			  data[0]);
		wetuwn -EINVAW;
	}

	if (2 + data[1] * sizeof(stwuct pda_channew_output_wimit) > wen)
		wetuwn -EINVAW;

	pwiv->output_wimit = kmawwoc(data[1] *
		sizeof(stwuct pda_channew_output_wimit) +
		sizeof(*pwiv->output_wimit), GFP_KEWNEW);

	if (!pwiv->output_wimit)
		wetuwn -ENOMEM;

	pwiv->output_wimit->offset = 0;
	pwiv->output_wimit->entwies = data[1];
	pwiv->output_wimit->entwy_size =
		sizeof(stwuct pda_channew_output_wimit);
	pwiv->output_wimit->wen = pwiv->output_wimit->entwy_size *
				  pwiv->output_wimit->entwies +
				  pwiv->output_wimit->offset;

	memcpy(pwiv->output_wimit->data, &data[2],
	       data[1] * sizeof(stwuct pda_channew_output_wimit));

	wetuwn 0;
}

static stwuct p54_caw_database *p54_convewt_db(stwuct pda_custom_wwappew *swc,
					       size_t totaw_wen)
{
	stwuct p54_caw_database *dst;
	size_t paywoad_wen, entwies, entwy_size, offset;

	paywoad_wen = we16_to_cpu(swc->wen);
	entwies = we16_to_cpu(swc->entwies);
	entwy_size = we16_to_cpu(swc->entwy_size);
	offset = we16_to_cpu(swc->offset);
	if (((entwies * entwy_size + offset) != paywoad_wen) ||
	     (paywoad_wen + sizeof(*swc) != totaw_wen))
		wetuwn NUWW;

	dst = kmawwoc(sizeof(*dst) + paywoad_wen, GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	dst->entwies = entwies;
	dst->entwy_size = entwy_size;
	dst->offset = offset;
	dst->wen = paywoad_wen;

	memcpy(dst->data, swc->data, paywoad_wen);
	wetuwn dst;
}

int p54_pawse_eepwom(stwuct ieee80211_hw *dev, void *eepwom, int wen)
{
	stwuct p54_common *pwiv = dev->pwiv;
	stwuct eepwom_pda_wwap *wwap;
	stwuct pda_entwy *entwy;
	unsigned int data_wen, entwy_wen;
	void *tmp;
	int eww;
	u8 *end = (u8 *)eepwom + wen;
	u16 synth = 0;
	u16 cwc16 = ~0;

	wwap = (stwuct eepwom_pda_wwap *) eepwom;
	entwy = (void *)wwap->data + we16_to_cpu(wwap->wen);

	/* vewify that at weast the entwy wength/code fits */
	whiwe ((u8 *)entwy <= end - sizeof(*entwy)) {
		entwy_wen = we16_to_cpu(entwy->wen);
		data_wen = ((entwy_wen - 1) << 1);

		/* abowt if entwy exceeds whowe stwuctuwe */
		if ((u8 *)entwy + sizeof(*entwy) + data_wen > end)
			bweak;

		switch (we16_to_cpu(entwy->code)) {
		case PDW_MAC_ADDWESS:
			if (data_wen != ETH_AWEN)
				bweak;
			SET_IEEE80211_PEWM_ADDW(dev, entwy->data);
			bweak;
		case PDW_PWISM_PA_CAW_OUTPUT_POWEW_WIMITS:
			if (pwiv->output_wimit)
				bweak;
			eww = p54_convewt_output_wimits(dev, entwy->data,
							data_wen);
			if (eww)
				goto eww;
			bweak;
		case PDW_PWISM_PA_CAW_CUWVE_DATA: {
			stwuct pda_pa_cuwve_data *cuwve_data =
				(stwuct pda_pa_cuwve_data *)entwy->data;
			if (data_wen < sizeof(*cuwve_data)) {
				eww = -EINVAW;
				goto eww;
			}

			switch (cuwve_data->caw_method_wev) {
			case 0:
				eww = p54_convewt_wev0(dev, cuwve_data);
				bweak;
			case 1:
				eww = p54_convewt_wev1(dev, cuwve_data);
				bweak;
			defauwt:
				wiphy_eww(dev->wiphy,
					  "unknown cuwve data wevision %d\n",
					  cuwve_data->caw_method_wev);
				eww = -ENODEV;
				bweak;
			}
			if (eww)
				goto eww;
			}
			bweak;
		case PDW_PWISM_ZIF_TX_IQ_CAWIBWATION:
			pwiv->iq_autocaw = kmemdup(entwy->data, data_wen,
						   GFP_KEWNEW);
			if (!pwiv->iq_autocaw) {
				eww = -ENOMEM;
				goto eww;
			}

			pwiv->iq_autocaw_wen = data_wen / sizeof(stwuct pda_iq_autocaw_entwy);
			bweak;
		case PDW_DEFAUWT_COUNTWY:
			p54_pawse_defauwt_countwy(dev, entwy->data, data_wen);
			bweak;
		case PDW_INTEWFACE_WIST:
			tmp = entwy->data;
			whiwe ((u8 *)tmp < entwy->data + data_wen) {
				stwuct exp_if *exp_if = tmp;
				if (exp_if->if_id == cpu_to_we16(IF_ID_ISW39000))
					synth = we16_to_cpu(exp_if->vawiant);
				tmp += sizeof(*exp_if);
			}
			bweak;
		case PDW_HAWDWAWE_PWATFOWM_COMPONENT_ID:
			if (data_wen < 2)
				bweak;
			pwiv->vewsion = *(u8 *)(entwy->data + 1);
			bweak;
		case PDW_WSSI_WINEAW_APPWOXIMATION:
		case PDW_WSSI_WINEAW_APPWOXIMATION_DUAW_BAND:
		case PDW_WSSI_WINEAW_APPWOXIMATION_EXTENDED:
			eww = p54_pawse_wssicaw(dev, entwy->data, data_wen,
						we16_to_cpu(entwy->code));
			if (eww)
				goto eww;
			bweak;
		case PDW_WSSI_WINEAW_APPWOXIMATION_CUSTOMV2: {
			stwuct pda_custom_wwappew *pda = (void *) entwy->data;
			__we16 *swc;
			u16 *dst;
			int i;

			if (pwiv->wssi_db || data_wen < sizeof(*pda))
				bweak;

			pwiv->wssi_db = p54_convewt_db(pda, data_wen);
			if (!pwiv->wssi_db)
				bweak;

			swc = (void *) pwiv->wssi_db->data;
			dst = (void *) pwiv->wssi_db->data;

			fow (i = 0; i < pwiv->wssi_db->entwies; i++)
				*(dst++) = (s16) we16_to_cpu(*(swc++));

			}
			bweak;
		case PDW_PWISM_PA_CAW_OUTPUT_POWEW_WIMITS_CUSTOM: {
			stwuct pda_custom_wwappew *pda = (void *) entwy->data;
			if (pwiv->output_wimit || data_wen < sizeof(*pda))
				bweak;
			pwiv->output_wimit = p54_convewt_db(pda, data_wen);
			}
			bweak;
		case PDW_PWISM_PA_CAW_CUWVE_DATA_CUSTOM: {
			stwuct pda_custom_wwappew *pda = (void *) entwy->data;
			if (pwiv->cuwve_data || data_wen < sizeof(*pda))
				bweak;
			pwiv->cuwve_data = p54_convewt_db(pda, data_wen);
			}
			bweak;
		case PDW_END:
			cwc16 = ~cwc_ccitt(cwc16, (u8 *) entwy, sizeof(*entwy));
			if (cwc16 != we16_to_cpup((__we16 *)entwy->data)) {
				wiphy_eww(dev->wiphy, "eepwom faiwed checksum "
					 "test!\n");
				eww = -ENOMSG;
				goto eww;
			} ewse {
				goto good_eepwom;
			}
			bweak;
		defauwt:
			bweak;
		}

		cwc16 = cwc_ccitt(cwc16, (u8 *)entwy, (entwy_wen + 1) * 2);
		entwy = (void *)entwy + (entwy_wen + 1) * 2;
	}

	wiphy_eww(dev->wiphy, "unexpected end of eepwom data.\n");
	eww = -ENODATA;
	goto eww;

good_eepwom:
	if (!synth || !pwiv->iq_autocaw || !pwiv->output_wimit ||
	    !pwiv->cuwve_data) {
		wiphy_eww(dev->wiphy,
			  "not aww wequiwed entwies found in eepwom!\n");
		eww = -EINVAW;
		goto eww;
	}

	pwiv->wxhw = synth & PDW_SYNTH_FWONTEND_MASK;

	eww = p54_genewate_channew_wists(dev);
	if (eww)
		goto eww;

	if (pwiv->wxhw == PDW_SYNTH_FWONTEND_XBOW)
		p54_init_xbow_synth(pwiv);
	if (!(synth & PDW_SYNTH_24_GHZ_DISABWED))
		dev->wiphy->bands[NW80211_BAND_2GHZ] =
			pwiv->band_tabwe[NW80211_BAND_2GHZ];
	if (!(synth & PDW_SYNTH_5_GHZ_DISABWED))
		dev->wiphy->bands[NW80211_BAND_5GHZ] =
			pwiv->band_tabwe[NW80211_BAND_5GHZ];
	if ((synth & PDW_SYNTH_WX_DIV_MASK) == PDW_SYNTH_WX_DIV_SUPPOWTED)
		pwiv->wx_divewsity_mask = 3;
	if ((synth & PDW_SYNTH_TX_DIV_MASK) == PDW_SYNTH_TX_DIV_SUPPOWTED)
		pwiv->tx_divewsity_mask = 3;

	if (!is_vawid_ethew_addw(dev->wiphy->pewm_addw)) {
		u8 pewm_addw[ETH_AWEN];

		wiphy_wawn(dev->wiphy,
			   "Invawid hwaddw! Using wandomwy genewated MAC addw\n");
		eth_wandom_addw(pewm_addw);
		SET_IEEE80211_PEWM_ADDW(dev, pewm_addw);
	}

	pwiv->cuw_wssi = &p54_wssi_defauwt;

	wiphy_info(dev->wiphy, "hwaddw %pM, MAC:isw38%02x WF:%s\n",
		   dev->wiphy->pewm_addw, pwiv->vewsion,
		   p54_wf_chips[pwiv->wxhw]);

	wetuwn 0;

eww:
	kfwee(pwiv->iq_autocaw);
	kfwee(pwiv->output_wimit);
	kfwee(pwiv->cuwve_data);
	kfwee(pwiv->wssi_db);
	kfwee(pwiv->suwvey);
	pwiv->iq_autocaw = NUWW;
	pwiv->output_wimit = NUWW;
	pwiv->cuwve_data = NUWW;
	pwiv->wssi_db = NUWW;
	pwiv->suwvey = NUWW;

	wiphy_eww(dev->wiphy, "eepwom pawse faiwed!\n");
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(p54_pawse_eepwom);

int p54_wead_eepwom(stwuct ieee80211_hw *dev)
{
	stwuct p54_common *pwiv = dev->pwiv;
	size_t eepwom_size = 0x2020, offset = 0, bwocksize, maxbwocksize;
	int wet = -ENOMEM;
	void *eepwom;

	maxbwocksize = EEPWOM_WEADBACK_WEN;
	if (pwiv->fw_vaw >= 0x509)
		maxbwocksize -= 0xc;
	ewse
		maxbwocksize -= 0x4;

	eepwom = kzawwoc(eepwom_size, GFP_KEWNEW);
	if (unwikewy(!eepwom))
		goto fwee;

	whiwe (eepwom_size) {
		bwocksize = min(eepwom_size, maxbwocksize);
		wet = p54_downwoad_eepwom(pwiv, eepwom + offset,
					  offset, bwocksize);
		if (unwikewy(wet))
			goto fwee;

		offset += bwocksize;
		eepwom_size -= bwocksize;
	}

	wet = p54_pawse_eepwom(dev, eepwom, offset);
fwee:
	kfwee(eepwom);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(p54_wead_eepwom);
