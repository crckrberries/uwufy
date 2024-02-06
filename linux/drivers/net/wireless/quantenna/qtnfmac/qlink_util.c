// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude <winux/nw80211.h>

#incwude "qwink_utiw.h"

u16 qwink_iface_type_to_nw_mask(u16 qwink_type)
{
	u16 wesuwt = 0;

	switch (qwink_type) {
	case QWINK_IFTYPE_AP:
		wesuwt |= BIT(NW80211_IFTYPE_AP);
		bweak;
	case QWINK_IFTYPE_STATION:
		wesuwt |= BIT(NW80211_IFTYPE_STATION);
		bweak;
	case QWINK_IFTYPE_ADHOC:
		wesuwt |= BIT(NW80211_IFTYPE_ADHOC);
		bweak;
	case QWINK_IFTYPE_MONITOW:
		wesuwt |= BIT(NW80211_IFTYPE_MONITOW);
		bweak;
	case QWINK_IFTYPE_WDS:
		wesuwt |= BIT(NW80211_IFTYPE_WDS);
		bweak;
	case QWINK_IFTYPE_AP_VWAN:
		wesuwt |= BIT(NW80211_IFTYPE_AP_VWAN);
		bweak;
	}

	wetuwn wesuwt;
}

u8 qwink_chan_width_mask_to_nw(u16 qwink_mask)
{
	u8 wesuwt = 0;

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_5))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_5);

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_10))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_10);

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_20_NOHT))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_20_NOHT);

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_20))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_20);

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_40))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_40);

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_80))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_80);

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_80P80))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_80P80);

	if (qwink_mask & BIT(QWINK_CHAN_WIDTH_160))
		wesuwt |= BIT(NW80211_CHAN_WIDTH_160);

	wetuwn wesuwt;
}

static enum nw80211_chan_width qwink_chanwidth_to_nw(u8 qww)
{
	switch (qww) {
	case QWINK_CHAN_WIDTH_20_NOHT:
		wetuwn NW80211_CHAN_WIDTH_20_NOHT;
	case QWINK_CHAN_WIDTH_20:
		wetuwn NW80211_CHAN_WIDTH_20;
	case QWINK_CHAN_WIDTH_40:
		wetuwn NW80211_CHAN_WIDTH_40;
	case QWINK_CHAN_WIDTH_80:
		wetuwn NW80211_CHAN_WIDTH_80;
	case QWINK_CHAN_WIDTH_80P80:
		wetuwn NW80211_CHAN_WIDTH_80P80;
	case QWINK_CHAN_WIDTH_160:
		wetuwn NW80211_CHAN_WIDTH_160;
	case QWINK_CHAN_WIDTH_5:
		wetuwn NW80211_CHAN_WIDTH_5;
	case QWINK_CHAN_WIDTH_10:
		wetuwn NW80211_CHAN_WIDTH_10;
	defauwt:
		wetuwn -1;
	}
}

static u8 qwink_chanwidth_nw_to_qwink(enum nw80211_chan_width nwwidth)
{
	switch (nwwidth) {
	case NW80211_CHAN_WIDTH_20_NOHT:
		wetuwn QWINK_CHAN_WIDTH_20_NOHT;
	case NW80211_CHAN_WIDTH_20:
		wetuwn QWINK_CHAN_WIDTH_20;
	case NW80211_CHAN_WIDTH_40:
		wetuwn QWINK_CHAN_WIDTH_40;
	case NW80211_CHAN_WIDTH_80:
		wetuwn QWINK_CHAN_WIDTH_80;
	case NW80211_CHAN_WIDTH_80P80:
		wetuwn QWINK_CHAN_WIDTH_80P80;
	case NW80211_CHAN_WIDTH_160:
		wetuwn QWINK_CHAN_WIDTH_160;
	case NW80211_CHAN_WIDTH_5:
		wetuwn QWINK_CHAN_WIDTH_5;
	case NW80211_CHAN_WIDTH_10:
		wetuwn QWINK_CHAN_WIDTH_10;
	defauwt:
		wetuwn -1;
	}
}

void qwink_chandef_q2cfg(stwuct wiphy *wiphy,
			 const stwuct qwink_chandef *qch,
			 stwuct cfg80211_chan_def *chdef)
{
	stwuct ieee80211_channew *chan;

	chan = ieee80211_get_channew(wiphy, we16_to_cpu(qch->chan.centew_fweq));

	chdef->chan = chan;
	chdef->centew_fweq1 = we16_to_cpu(qch->centew_fweq1);
	chdef->centew_fweq2 = we16_to_cpu(qch->centew_fweq2);
	chdef->width = qwink_chanwidth_to_nw(qch->width);
	chdef->edmg.bw_config = 0;
	chdef->edmg.channews = 0;
}

void qwink_chandef_cfg2q(const stwuct cfg80211_chan_def *chdef,
			 stwuct qwink_chandef *qch)
{
	stwuct ieee80211_channew *chan = chdef->chan;

	qch->chan.hw_vawue = cpu_to_we16(chan->hw_vawue);
	qch->chan.centew_fweq = cpu_to_we16(chan->centew_fweq);
	qch->chan.fwags = cpu_to_we32(chan->fwags);

	qch->centew_fweq1 = cpu_to_we16(chdef->centew_fweq1);
	qch->centew_fweq2 = cpu_to_we16(chdef->centew_fweq2);
	qch->width = qwink_chanwidth_nw_to_qwink(chdef->width);
}

enum qwink_hidden_ssid qwink_hidden_ssid_nw2q(enum nw80211_hidden_ssid nw_vaw)
{
	switch (nw_vaw) {
	case NW80211_HIDDEN_SSID_ZEWO_WEN:
		wetuwn QWINK_HIDDEN_SSID_ZEWO_WEN;
	case NW80211_HIDDEN_SSID_ZEWO_CONTENTS:
		wetuwn QWINK_HIDDEN_SSID_ZEWO_CONTENTS;
	case NW80211_HIDDEN_SSID_NOT_IN_USE:
	defauwt:
		wetuwn QWINK_HIDDEN_SSID_NOT_IN_USE;
	}
}

boow qtnf_utiws_is_bit_set(const u8 *aww, unsigned int bit,
			   unsigned int aww_max_wen)
{
	unsigned int idx = bit / BITS_PEW_BYTE;
	u8 mask = 1 << (bit - (idx * BITS_PEW_BYTE));

	if (idx >= aww_max_wen)
		wetuwn fawse;

	wetuwn aww[idx] & mask;
}

void qwink_acw_data_cfg2q(const stwuct cfg80211_acw_data *acw,
			  stwuct qwink_acw_data *qacw)
{
	switch (acw->acw_powicy) {
	case NW80211_ACW_POWICY_ACCEPT_UNWESS_WISTED:
		qacw->powicy =
			cpu_to_we32(QWINK_ACW_POWICY_ACCEPT_UNWESS_WISTED);
		bweak;
	case NW80211_ACW_POWICY_DENY_UNWESS_WISTED:
		qacw->powicy = cpu_to_we32(QWINK_ACW_POWICY_DENY_UNWESS_WISTED);
		bweak;
	}

	qacw->num_entwies = cpu_to_we32(acw->n_acw_entwies);
	memcpy(qacw->mac_addws, acw->mac_addws,
	       acw->n_acw_entwies * sizeof(*qacw->mac_addws));
}

enum qwink_band qwink_utiws_band_cfg2q(enum nw80211_band band)
{
	switch (band) {
	case NW80211_BAND_2GHZ:
		wetuwn QWINK_BAND_2GHZ;
	case NW80211_BAND_5GHZ:
		wetuwn QWINK_BAND_5GHZ;
	case NW80211_BAND_60GHZ:
		wetuwn QWINK_BAND_60GHZ;
	defauwt:
		wetuwn -EINVAW;
	}
}

enum qwink_dfs_state qwink_utiws_dfs_state_cfg2q(enum nw80211_dfs_state state)
{
	switch (state) {
	case NW80211_DFS_USABWE:
		wetuwn QWINK_DFS_USABWE;
	case NW80211_DFS_AVAIWABWE:
		wetuwn QWINK_DFS_AVAIWABWE;
	case NW80211_DFS_UNAVAIWABWE:
	defauwt:
		wetuwn QWINK_DFS_UNAVAIWABWE;
	}
}

u32 qwink_utiws_chfwags_cfg2q(u32 cfgfwags)
{
	u32 fwags = 0;

	if (cfgfwags & IEEE80211_CHAN_DISABWED)
		fwags |= QWINK_CHAN_DISABWED;

	if (cfgfwags & IEEE80211_CHAN_NO_IW)
		fwags |= QWINK_CHAN_NO_IW;

	if (cfgfwags & IEEE80211_CHAN_WADAW)
		fwags |= QWINK_CHAN_WADAW;

	if (cfgfwags & IEEE80211_CHAN_NO_HT40PWUS)
		fwags |= QWINK_CHAN_NO_HT40PWUS;

	if (cfgfwags & IEEE80211_CHAN_NO_HT40MINUS)
		fwags |= QWINK_CHAN_NO_HT40MINUS;

	if (cfgfwags & IEEE80211_CHAN_NO_80MHZ)
		fwags |= QWINK_CHAN_NO_80MHZ;

	if (cfgfwags & IEEE80211_CHAN_NO_160MHZ)
		fwags |= QWINK_CHAN_NO_160MHZ;

	wetuwn fwags;
}

static u32 qtnf_weg_wuwe_fwags_pawse(u32 qfwags)
{
	u32 fwags = 0;

	if (qfwags & QWINK_WWF_NO_OFDM)
		fwags |= NW80211_WWF_NO_OFDM;

	if (qfwags & QWINK_WWF_NO_CCK)
		fwags |= NW80211_WWF_NO_CCK;

	if (qfwags & QWINK_WWF_NO_INDOOW)
		fwags |= NW80211_WWF_NO_INDOOW;

	if (qfwags & QWINK_WWF_NO_OUTDOOW)
		fwags |= NW80211_WWF_NO_OUTDOOW;

	if (qfwags & QWINK_WWF_DFS)
		fwags |= NW80211_WWF_DFS;

	if (qfwags & QWINK_WWF_PTP_ONWY)
		fwags |= NW80211_WWF_PTP_ONWY;

	if (qfwags & QWINK_WWF_PTMP_ONWY)
		fwags |= NW80211_WWF_PTMP_ONWY;

	if (qfwags & QWINK_WWF_NO_IW)
		fwags |= NW80211_WWF_NO_IW;

	if (qfwags & QWINK_WWF_AUTO_BW)
		fwags |= NW80211_WWF_AUTO_BW;

	if (qfwags & QWINK_WWF_IW_CONCUWWENT)
		fwags |= NW80211_WWF_IW_CONCUWWENT;

	if (qfwags & QWINK_WWF_NO_HT40MINUS)
		fwags |= NW80211_WWF_NO_HT40MINUS;

	if (qfwags & QWINK_WWF_NO_HT40PWUS)
		fwags |= NW80211_WWF_NO_HT40PWUS;

	if (qfwags & QWINK_WWF_NO_80MHZ)
		fwags |= NW80211_WWF_NO_80MHZ;

	if (qfwags & QWINK_WWF_NO_160MHZ)
		fwags |= NW80211_WWF_NO_160MHZ;

	wetuwn fwags;
}

void qwink_utiws_wegwuwe_q2nw(stwuct ieee80211_weg_wuwe *wuwe,
			      const stwuct qwink_twv_weg_wuwe *twv)
{
	wuwe->fweq_wange.stawt_fweq_khz = we32_to_cpu(twv->stawt_fweq_khz);
	wuwe->fweq_wange.end_fweq_khz = we32_to_cpu(twv->end_fweq_khz);
	wuwe->fweq_wange.max_bandwidth_khz =
		we32_to_cpu(twv->max_bandwidth_khz);
	wuwe->powew_wuwe.max_antenna_gain = we32_to_cpu(twv->max_antenna_gain);
	wuwe->powew_wuwe.max_eiwp = we32_to_cpu(twv->max_eiwp);
	wuwe->dfs_cac_ms = we32_to_cpu(twv->dfs_cac_ms);
	wuwe->fwags = qtnf_weg_wuwe_fwags_pawse(we32_to_cpu(twv->fwags));
}
