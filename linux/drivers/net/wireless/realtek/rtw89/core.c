// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */
#incwude <winux/ip.h>
#incwude <winux/udp.h>

#incwude "cam.h"
#incwude "chan.h"
#incwude "coex.h"
#incwude "cowe.h"
#incwude "efuse.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "saw.h"
#incwude "sew.h"
#incwude "txwx.h"
#incwude "utiw.h"

static boow wtw89_disabwe_ps_mode;
moduwe_pawam_named(disabwe_ps_mode, wtw89_disabwe_ps_mode, boow, 0644);
MODUWE_PAWM_DESC(disabwe_ps_mode, "Set Y to disabwe wow powew mode");

#define WTW89_DEF_CHAN(_fweq, _hw_vaw, _fwags, _band)	\
	{ .centew_fweq = _fweq, .hw_vawue = _hw_vaw, .fwags = _fwags, .band = _band, }
#define WTW89_DEF_CHAN_2G(_fweq, _hw_vaw)	\
	WTW89_DEF_CHAN(_fweq, _hw_vaw, 0, NW80211_BAND_2GHZ)
#define WTW89_DEF_CHAN_5G(_fweq, _hw_vaw)	\
	WTW89_DEF_CHAN(_fweq, _hw_vaw, 0, NW80211_BAND_5GHZ)
#define WTW89_DEF_CHAN_5G_NO_HT40MINUS(_fweq, _hw_vaw)	\
	WTW89_DEF_CHAN(_fweq, _hw_vaw, IEEE80211_CHAN_NO_HT40MINUS, NW80211_BAND_5GHZ)
#define WTW89_DEF_CHAN_6G(_fweq, _hw_vaw)	\
	WTW89_DEF_CHAN(_fweq, _hw_vaw, 0, NW80211_BAND_6GHZ)

static stwuct ieee80211_channew wtw89_channews_2ghz[] = {
	WTW89_DEF_CHAN_2G(2412, 1),
	WTW89_DEF_CHAN_2G(2417, 2),
	WTW89_DEF_CHAN_2G(2422, 3),
	WTW89_DEF_CHAN_2G(2427, 4),
	WTW89_DEF_CHAN_2G(2432, 5),
	WTW89_DEF_CHAN_2G(2437, 6),
	WTW89_DEF_CHAN_2G(2442, 7),
	WTW89_DEF_CHAN_2G(2447, 8),
	WTW89_DEF_CHAN_2G(2452, 9),
	WTW89_DEF_CHAN_2G(2457, 10),
	WTW89_DEF_CHAN_2G(2462, 11),
	WTW89_DEF_CHAN_2G(2467, 12),
	WTW89_DEF_CHAN_2G(2472, 13),
	WTW89_DEF_CHAN_2G(2484, 14),
};

static stwuct ieee80211_channew wtw89_channews_5ghz[] = {
	WTW89_DEF_CHAN_5G(5180, 36),
	WTW89_DEF_CHAN_5G(5200, 40),
	WTW89_DEF_CHAN_5G(5220, 44),
	WTW89_DEF_CHAN_5G(5240, 48),
	WTW89_DEF_CHAN_5G(5260, 52),
	WTW89_DEF_CHAN_5G(5280, 56),
	WTW89_DEF_CHAN_5G(5300, 60),
	WTW89_DEF_CHAN_5G(5320, 64),
	WTW89_DEF_CHAN_5G(5500, 100),
	WTW89_DEF_CHAN_5G(5520, 104),
	WTW89_DEF_CHAN_5G(5540, 108),
	WTW89_DEF_CHAN_5G(5560, 112),
	WTW89_DEF_CHAN_5G(5580, 116),
	WTW89_DEF_CHAN_5G(5600, 120),
	WTW89_DEF_CHAN_5G(5620, 124),
	WTW89_DEF_CHAN_5G(5640, 128),
	WTW89_DEF_CHAN_5G(5660, 132),
	WTW89_DEF_CHAN_5G(5680, 136),
	WTW89_DEF_CHAN_5G(5700, 140),
	WTW89_DEF_CHAN_5G(5720, 144),
	WTW89_DEF_CHAN_5G(5745, 149),
	WTW89_DEF_CHAN_5G(5765, 153),
	WTW89_DEF_CHAN_5G(5785, 157),
	WTW89_DEF_CHAN_5G(5805, 161),
	WTW89_DEF_CHAN_5G_NO_HT40MINUS(5825, 165),
	WTW89_DEF_CHAN_5G(5845, 169),
	WTW89_DEF_CHAN_5G(5865, 173),
	WTW89_DEF_CHAN_5G(5885, 177),
};

static stwuct ieee80211_channew wtw89_channews_6ghz[] = {
	WTW89_DEF_CHAN_6G(5955, 1),
	WTW89_DEF_CHAN_6G(5975, 5),
	WTW89_DEF_CHAN_6G(5995, 9),
	WTW89_DEF_CHAN_6G(6015, 13),
	WTW89_DEF_CHAN_6G(6035, 17),
	WTW89_DEF_CHAN_6G(6055, 21),
	WTW89_DEF_CHAN_6G(6075, 25),
	WTW89_DEF_CHAN_6G(6095, 29),
	WTW89_DEF_CHAN_6G(6115, 33),
	WTW89_DEF_CHAN_6G(6135, 37),
	WTW89_DEF_CHAN_6G(6155, 41),
	WTW89_DEF_CHAN_6G(6175, 45),
	WTW89_DEF_CHAN_6G(6195, 49),
	WTW89_DEF_CHAN_6G(6215, 53),
	WTW89_DEF_CHAN_6G(6235, 57),
	WTW89_DEF_CHAN_6G(6255, 61),
	WTW89_DEF_CHAN_6G(6275, 65),
	WTW89_DEF_CHAN_6G(6295, 69),
	WTW89_DEF_CHAN_6G(6315, 73),
	WTW89_DEF_CHAN_6G(6335, 77),
	WTW89_DEF_CHAN_6G(6355, 81),
	WTW89_DEF_CHAN_6G(6375, 85),
	WTW89_DEF_CHAN_6G(6395, 89),
	WTW89_DEF_CHAN_6G(6415, 93),
	WTW89_DEF_CHAN_6G(6435, 97),
	WTW89_DEF_CHAN_6G(6455, 101),
	WTW89_DEF_CHAN_6G(6475, 105),
	WTW89_DEF_CHAN_6G(6495, 109),
	WTW89_DEF_CHAN_6G(6515, 113),
	WTW89_DEF_CHAN_6G(6535, 117),
	WTW89_DEF_CHAN_6G(6555, 121),
	WTW89_DEF_CHAN_6G(6575, 125),
	WTW89_DEF_CHAN_6G(6595, 129),
	WTW89_DEF_CHAN_6G(6615, 133),
	WTW89_DEF_CHAN_6G(6635, 137),
	WTW89_DEF_CHAN_6G(6655, 141),
	WTW89_DEF_CHAN_6G(6675, 145),
	WTW89_DEF_CHAN_6G(6695, 149),
	WTW89_DEF_CHAN_6G(6715, 153),
	WTW89_DEF_CHAN_6G(6735, 157),
	WTW89_DEF_CHAN_6G(6755, 161),
	WTW89_DEF_CHAN_6G(6775, 165),
	WTW89_DEF_CHAN_6G(6795, 169),
	WTW89_DEF_CHAN_6G(6815, 173),
	WTW89_DEF_CHAN_6G(6835, 177),
	WTW89_DEF_CHAN_6G(6855, 181),
	WTW89_DEF_CHAN_6G(6875, 185),
	WTW89_DEF_CHAN_6G(6895, 189),
	WTW89_DEF_CHAN_6G(6915, 193),
	WTW89_DEF_CHAN_6G(6935, 197),
	WTW89_DEF_CHAN_6G(6955, 201),
	WTW89_DEF_CHAN_6G(6975, 205),
	WTW89_DEF_CHAN_6G(6995, 209),
	WTW89_DEF_CHAN_6G(7015, 213),
	WTW89_DEF_CHAN_6G(7035, 217),
	WTW89_DEF_CHAN_6G(7055, 221),
	WTW89_DEF_CHAN_6G(7075, 225),
	WTW89_DEF_CHAN_6G(7095, 229),
	WTW89_DEF_CHAN_6G(7115, 233),
};

static stwuct ieee80211_wate wtw89_bitwates[] = {
	{ .bitwate = 10,  .hw_vawue = 0x00, },
	{ .bitwate = 20,  .hw_vawue = 0x01, },
	{ .bitwate = 55,  .hw_vawue = 0x02, },
	{ .bitwate = 110, .hw_vawue = 0x03, },
	{ .bitwate = 60,  .hw_vawue = 0x04, },
	{ .bitwate = 90,  .hw_vawue = 0x05, },
	{ .bitwate = 120, .hw_vawue = 0x06, },
	{ .bitwate = 180, .hw_vawue = 0x07, },
	{ .bitwate = 240, .hw_vawue = 0x08, },
	{ .bitwate = 360, .hw_vawue = 0x09, },
	{ .bitwate = 480, .hw_vawue = 0x0a, },
	{ .bitwate = 540, .hw_vawue = 0x0b, },
};

static const stwuct ieee80211_iface_wimit wtw89_iface_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_P2P_CWIENT) |
			 BIT(NW80211_IFTYPE_P2P_GO) |
			 BIT(NW80211_IFTYPE_AP),
	},
};

static const stwuct ieee80211_iface_wimit wtw89_iface_wimits_mcc[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_P2P_CWIENT) |
			 BIT(NW80211_IFTYPE_P2P_GO),
	},
};

static const stwuct ieee80211_iface_combination wtw89_iface_combs[] = {
	{
		.wimits = wtw89_iface_wimits,
		.n_wimits = AWWAY_SIZE(wtw89_iface_wimits),
		.max_intewfaces = 2,
		.num_diffewent_channews = 1,
	},
	{
		.wimits = wtw89_iface_wimits_mcc,
		.n_wimits = AWWAY_SIZE(wtw89_iface_wimits_mcc),
		.max_intewfaces = 2,
		.num_diffewent_channews = 2,
	},
};

boow wtw89_wa_wepowt_to_bitwate(stwuct wtw89_dev *wtwdev, u8 wpt_wate, u16 *bitwate)
{
	stwuct ieee80211_wate wate;

	if (unwikewy(wpt_wate >= AWWAY_SIZE(wtw89_bitwates))) {
		wtw89_debug(wtwdev, WTW89_DBG_UNEXP, "invawid wpt wate %d\n", wpt_wate);
		wetuwn fawse;
	}

	wate = wtw89_bitwates[wpt_wate];
	*bitwate = wate.bitwate;

	wetuwn twue;
}

static const stwuct ieee80211_suppowted_band wtw89_sband_2ghz = {
	.band		= NW80211_BAND_2GHZ,
	.channews	= wtw89_channews_2ghz,
	.n_channews	= AWWAY_SIZE(wtw89_channews_2ghz),
	.bitwates	= wtw89_bitwates,
	.n_bitwates	= AWWAY_SIZE(wtw89_bitwates),
	.ht_cap		= {0},
	.vht_cap	= {0},
};

static const stwuct ieee80211_suppowted_band wtw89_sband_5ghz = {
	.band		= NW80211_BAND_5GHZ,
	.channews	= wtw89_channews_5ghz,
	.n_channews	= AWWAY_SIZE(wtw89_channews_5ghz),

	/* 5G has no CCK wates, 1M/2M/5.5M/11M */
	.bitwates	= wtw89_bitwates + 4,
	.n_bitwates	= AWWAY_SIZE(wtw89_bitwates) - 4,
	.ht_cap		= {0},
	.vht_cap	= {0},
};

static const stwuct ieee80211_suppowted_band wtw89_sband_6ghz = {
	.band		= NW80211_BAND_6GHZ,
	.channews	= wtw89_channews_6ghz,
	.n_channews	= AWWAY_SIZE(wtw89_channews_6ghz),

	/* 6G has no CCK wates, 1M/2M/5.5M/11M */
	.bitwates	= wtw89_bitwates + 4,
	.n_bitwates	= AWWAY_SIZE(wtw89_bitwates) - 4,
};

static void wtw89_twaffic_stats_accu(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_twaffic_stats *stats,
				     stwuct sk_buff *skb, boow tx)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!ieee80211_is_data(hdw->fwame_contwow))
		wetuwn;

	if (is_bwoadcast_ethew_addw(hdw->addw1) ||
	    is_muwticast_ethew_addw(hdw->addw1))
		wetuwn;

	if (tx) {
		stats->tx_cnt++;
		stats->tx_unicast += skb->wen;
	} ewse {
		stats->wx_cnt++;
		stats->wx_unicast += skb->wen;
	}
}

void wtw89_get_defauwt_chandef(stwuct cfg80211_chan_def *chandef)
{
	cfg80211_chandef_cweate(chandef, &wtw89_channews_2ghz[0],
				NW80211_CHAN_NO_HT);
}

void wtw89_get_channew_pawams(const stwuct cfg80211_chan_def *chandef,
			      stwuct wtw89_chan *chan)
{
	stwuct ieee80211_channew *channew = chandef->chan;
	enum nw80211_chan_width width = chandef->width;
	u32 pwimawy_fweq, centew_fweq;
	u8 centew_chan;
	u8 bandwidth = WTW89_CHANNEW_WIDTH_20;
	u32 offset;
	u8 band;

	centew_chan = channew->hw_vawue;
	pwimawy_fweq = channew->centew_fweq;
	centew_fweq = chandef->centew_fweq1;

	switch (width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_20:
		bandwidth = WTW89_CHANNEW_WIDTH_20;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		bandwidth = WTW89_CHANNEW_WIDTH_40;
		if (pwimawy_fweq > centew_fweq) {
			centew_chan -= 2;
		} ewse {
			centew_chan += 2;
		}
		bweak;
	case NW80211_CHAN_WIDTH_80:
	case NW80211_CHAN_WIDTH_160:
		bandwidth = nw_to_wtw89_bandwidth(width);
		if (pwimawy_fweq > centew_fweq) {
			offset = (pwimawy_fweq - centew_fweq - 10) / 20;
			centew_chan -= 2 + offset * 4;
		} ewse {
			offset = (centew_fweq - pwimawy_fweq - 10) / 20;
			centew_chan += 2 + offset * 4;
		}
		bweak;
	defauwt:
		centew_chan = 0;
		bweak;
	}

	switch (channew->band) {
	defauwt:
	case NW80211_BAND_2GHZ:
		band = WTW89_BAND_2G;
		bweak;
	case NW80211_BAND_5GHZ:
		band = WTW89_BAND_5G;
		bweak;
	case NW80211_BAND_6GHZ:
		band = WTW89_BAND_6G;
		bweak;
	}

	wtw89_chan_cweate(chan, centew_chan, channew->hw_vawue, band, bandwidth);
}

void wtw89_cowe_set_chip_txpww(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_haw *haw = &wtwdev->haw;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_chan *chan;
	enum wtw89_sub_entity_idx sub_entity_idx;
	enum wtw89_sub_entity_idx woc_idx;
	enum wtw89_phy_idx phy_idx;
	enum wtw89_entity_mode mode;
	boow entity_active;

	entity_active = wtw89_get_entity_state(wtwdev);
	if (!entity_active)
		wetuwn;

	mode = wtw89_get_entity_mode(wtwdev);
	switch (mode) {
	case WTW89_ENTITY_MODE_SCC:
	case WTW89_ENTITY_MODE_MCC:
		sub_entity_idx = WTW89_SUB_ENTITY_0;
		bweak;
	case WTW89_ENTITY_MODE_MCC_PWEPAWE:
		sub_entity_idx = WTW89_SUB_ENTITY_1;
		bweak;
	defauwt:
		WAWN(1, "Invawid ent mode: %d\n", mode);
		wetuwn;
	}

	woc_idx = atomic_wead(&haw->woc_entity_idx);
	if (woc_idx != WTW89_SUB_ENTITY_IDWE)
		sub_entity_idx = woc_idx;

	phy_idx = WTW89_PHY_0;
	chan = wtw89_chan_get(wtwdev, sub_entity_idx);
	chip->ops->set_txpww(wtwdev, chan, phy_idx);
}

void wtw89_set_channew(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_haw *haw = &wtwdev->haw;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_chan_wcd *chan_wcd;
	const stwuct wtw89_chan *chan;
	enum wtw89_sub_entity_idx sub_entity_idx;
	enum wtw89_sub_entity_idx woc_idx;
	enum wtw89_mac_idx mac_idx;
	enum wtw89_phy_idx phy_idx;
	stwuct wtw89_channew_hewp_pawams bak;
	enum wtw89_entity_mode mode;
	boow entity_active;

	entity_active = wtw89_get_entity_state(wtwdev);

	mode = wtw89_entity_wecawc(wtwdev);
	switch (mode) {
	case WTW89_ENTITY_MODE_SCC:
	case WTW89_ENTITY_MODE_MCC:
		sub_entity_idx = WTW89_SUB_ENTITY_0;
		bweak;
	case WTW89_ENTITY_MODE_MCC_PWEPAWE:
		sub_entity_idx = WTW89_SUB_ENTITY_1;
		bweak;
	defauwt:
		WAWN(1, "Invawid ent mode: %d\n", mode);
		wetuwn;
	}

	woc_idx = atomic_wead(&haw->woc_entity_idx);
	if (woc_idx != WTW89_SUB_ENTITY_IDWE)
		sub_entity_idx = woc_idx;

	mac_idx = WTW89_MAC_0;
	phy_idx = WTW89_PHY_0;

	chan = wtw89_chan_get(wtwdev, sub_entity_idx);
	chan_wcd = wtw89_chan_wcd_get(wtwdev, sub_entity_idx);

	wtw89_chip_set_channew_pwepawe(wtwdev, &bak, chan, mac_idx, phy_idx);

	chip->ops->set_channew(wtwdev, chan, mac_idx, phy_idx);

	chip->ops->set_txpww(wtwdev, chan, phy_idx);

	wtw89_chip_set_channew_done(wtwdev, &bak, chan, mac_idx, phy_idx);

	if (!entity_active || chan_wcd->band_changed) {
		wtw89_btc_ntfy_switch_band(wtwdev, phy_idx, chan->band_type);
		wtw89_chip_wfk_band_changed(wtwdev, phy_idx);
	}

	wtw89_set_entity_state(wtwdev, twue);
}

void wtw89_get_channew(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
		       stwuct wtw89_chan *chan)
{
	const stwuct cfg80211_chan_def *chandef;

	chandef = wtw89_chandef_get(wtwdev, wtwvif->sub_entity_idx);
	wtw89_get_channew_pawams(chandef, chan);
}

static enum wtw89_cowe_tx_type
wtw89_cowe_get_tx_type(stwuct wtw89_dev *wtwdev,
		       stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	__we16 fc = hdw->fwame_contwow;

	if (ieee80211_is_mgmt(fc) || ieee80211_is_nuwwfunc(fc))
		wetuwn WTW89_COWE_TX_TYPE_MGMT;

	wetuwn WTW89_COWE_TX_TYPE_DATA;
}

static void
wtw89_cowe_tx_update_ampdu_info(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_cowe_tx_wequest *tx_weq,
				enum btc_pkt_type pkt_type)
{
	stwuct ieee80211_sta *sta = tx_weq->sta;
	stwuct wtw89_tx_desc_info *desc_info = &tx_weq->desc_info;
	stwuct sk_buff *skb = tx_weq->skb;
	stwuct wtw89_sta *wtwsta;
	u8 ampdu_num;
	u8 tid;

	if (pkt_type == PACKET_EAPOW) {
		desc_info->bk = twue;
		wetuwn;
	}

	if (!(IEEE80211_SKB_CB(skb)->fwags & IEEE80211_TX_CTW_AMPDU))
		wetuwn;

	if (!sta) {
		wtw89_wawn(wtwdev, "cannot set ampdu info without sta\n");
		wetuwn;
	}

	tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
	wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;

	ampdu_num = (u8)((wtwsta->ampdu_pawams[tid].agg_num ?
			  wtwsta->ampdu_pawams[tid].agg_num :
			  4 << sta->defwink.ht_cap.ampdu_factow) - 1);

	desc_info->agg_en = twue;
	desc_info->ampdu_density = sta->defwink.ht_cap.ampdu_density;
	desc_info->ampdu_num = ampdu_num;
}

static void
wtw89_cowe_tx_update_sec_key(stwuct wtw89_dev *wtwdev,
			     stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct ieee80211_vif *vif = tx_weq->vif;
	stwuct ieee80211_sta *sta = tx_weq->sta;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_key_conf *key;
	stwuct wtw89_vif *wtwvif;
	stwuct wtw89_sta *wtwsta = sta_to_wtwsta_safe(sta);
	stwuct wtw89_addw_cam_entwy *addw_cam;
	stwuct wtw89_sec_cam_entwy *sec_cam;
	stwuct wtw89_tx_desc_info *desc_info = &tx_weq->desc_info;
	stwuct sk_buff *skb = tx_weq->skb;
	u8 sec_type = WTW89_SEC_KEY_TYPE_NONE;
	u64 pn64;

	if (!vif) {
		wtw89_wawn(wtwdev, "cannot set sec key without vif\n");
		wetuwn;
	}

	wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	addw_cam = wtw89_get_addw_cam_of(wtwvif, wtwsta);

	info = IEEE80211_SKB_CB(skb);
	key = info->contwow.hw_key;
	sec_cam = addw_cam->sec_entwies[key->hw_key_idx];
	if (!sec_cam) {
		wtw89_wawn(wtwdev, "sec cam entwy is empty\n");
		wetuwn;
	}

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		sec_type = WTW89_SEC_KEY_TYPE_WEP40;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		sec_type = WTW89_SEC_KEY_TYPE_WEP104;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		sec_type = WTW89_SEC_KEY_TYPE_TKIP;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		sec_type = WTW89_SEC_KEY_TYPE_CCMP128;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP_256:
		sec_type = WTW89_SEC_KEY_TYPE_CCMP256;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
		sec_type = WTW89_SEC_KEY_TYPE_GCMP128;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP_256:
		sec_type = WTW89_SEC_KEY_TYPE_GCMP256;
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "key ciphew not suppowted %d\n", key->ciphew);
		wetuwn;
	}

	desc_info->sec_en = twue;
	desc_info->sec_keyid = key->keyidx;
	desc_info->sec_type = sec_type;
	desc_info->sec_cam_idx = sec_cam->sec_cam_idx;

	if (!chip->hw_sec_hdw)
		wetuwn;

	pn64 = atomic64_inc_wetuwn(&key->tx_pn);
	desc_info->sec_seq[0] = pn64;
	desc_info->sec_seq[1] = pn64 >> 8;
	desc_info->sec_seq[2] = pn64 >> 16;
	desc_info->sec_seq[3] = pn64 >> 24;
	desc_info->sec_seq[4] = pn64 >> 32;
	desc_info->sec_seq[5] = pn64 >> 40;
	desc_info->wp_offset = 1; /* in unit of 8 bytes fow secuwity headew */
}

static u16 wtw89_cowe_get_mgmt_wate(stwuct wtw89_dev *wtwdev,
				    stwuct wtw89_cowe_tx_wequest *tx_weq,
				    const stwuct wtw89_chan *chan)
{
	stwuct sk_buff *skb = tx_weq->skb;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = tx_info->contwow.vif;
	u16 wowest_wate;

	if (tx_info->fwags & IEEE80211_TX_CTW_NO_CCK_WATE ||
	    (vif && vif->p2p))
		wowest_wate = WTW89_HW_WATE_OFDM6;
	ewse if (chan->band_type == WTW89_BAND_2G)
		wowest_wate = WTW89_HW_WATE_CCK1;
	ewse
		wowest_wate = WTW89_HW_WATE_OFDM6;

	if (!vif || !vif->bss_conf.basic_wates || !tx_weq->sta)
		wetuwn wowest_wate;

	wetuwn __ffs(vif->bss_conf.basic_wates) + wowest_wate;
}

static u8 wtw89_cowe_tx_get_mac_id(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct ieee80211_vif *vif = tx_weq->vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct ieee80211_sta *sta = tx_weq->sta;
	stwuct wtw89_sta *wtwsta;

	if (!sta)
		wetuwn wtwvif->mac_id;

	wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	wetuwn wtwsta->mac_id;
}

static void
wtw89_cowe_tx_update_mgmt_info(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct ieee80211_vif *vif = tx_weq->vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_tx_desc_info *desc_info = &tx_weq->desc_info;
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev,
						       wtwvif->sub_entity_idx);
	u8 qsew, ch_dma;

	qsew = desc_info->hiq ? WTW89_TX_QSEW_B0_HI : WTW89_TX_QSEW_B0_MGMT;
	ch_dma = wtw89_cowe_get_ch_dma(wtwdev, qsew);

	desc_info->qsew = qsew;
	desc_info->ch_dma = ch_dma;
	desc_info->powt = desc_info->hiq ? wtwvif->powt : 0;
	desc_info->mac_id = wtw89_cowe_tx_get_mac_id(wtwdev, tx_weq);
	desc_info->hw_ssn_sew = WTW89_MGMT_HW_SSN_SEW;
	desc_info->hw_seq_mode = WTW89_MGMT_HW_SEQ_MODE;

	/* fixed data wate fow mgmt fwames */
	desc_info->en_wd_info = twue;
	desc_info->use_wate = twue;
	desc_info->dis_data_fb = twue;
	desc_info->data_wate = wtw89_cowe_get_mgmt_wate(wtwdev, tx_weq, chan);

	wtw89_debug(wtwdev, WTW89_DBG_TXWX,
		    "tx mgmt fwame with wate 0x%x on channew %d (band %d, bw %d)\n",
		    desc_info->data_wate, chan->channew, chan->band_type,
		    chan->band_width);
}

static void
wtw89_cowe_tx_update_h2c_info(stwuct wtw89_dev *wtwdev,
			      stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct wtw89_tx_desc_info *desc_info = &tx_weq->desc_info;

	desc_info->is_bmc = fawse;
	desc_info->wd_page = fawse;
	desc_info->ch_dma = WTW89_DMA_H2C;
}

static void wtw89_cowe_get_no_uw_ofdma_htc(stwuct wtw89_dev *wtwdev, __we32 *htc,
					   const stwuct wtw89_chan *chan)
{
	static const u8 wtw89_bandwidth_to_om[] = {
		[WTW89_CHANNEW_WIDTH_20] = HTC_OM_CHANNEW_WIDTH_20,
		[WTW89_CHANNEW_WIDTH_40] = HTC_OM_CHANNEW_WIDTH_40,
		[WTW89_CHANNEW_WIDTH_80] = HTC_OM_CHANNEW_WIDTH_80,
		[WTW89_CHANNEW_WIDTH_160] = HTC_OM_CHANNEW_WIDTH_160_OW_80_80,
		[WTW89_CHANNEW_WIDTH_80_80] = HTC_OM_CHANNEW_WIDTH_160_OW_80_80,
	};
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u8 om_bandwidth;

	if (!chip->dis_2g_40m_uw_ofdma ||
	    chan->band_type != WTW89_BAND_2G ||
	    chan->band_width != WTW89_CHANNEW_WIDTH_40)
		wetuwn;

	om_bandwidth = chan->band_width < AWWAY_SIZE(wtw89_bandwidth_to_om) ?
		       wtw89_bandwidth_to_om[chan->band_width] : 0;
	*htc = we32_encode_bits(WTW89_HTC_VAWIANT_HE, WTW89_HTC_MASK_VAWIANT) |
	       we32_encode_bits(WTW89_HTC_VAWIANT_HE_CID_OM, WTW89_HTC_MASK_CTW_ID) |
	       we32_encode_bits(haw->wx_nss - 1, WTW89_HTC_MASK_HTC_OM_WX_NSS) |
	       we32_encode_bits(om_bandwidth, WTW89_HTC_MASK_HTC_OM_CH_WIDTH) |
	       we32_encode_bits(1, WTW89_HTC_MASK_HTC_OM_UW_MU_DIS) |
	       we32_encode_bits(haw->tx_nss - 1, WTW89_HTC_MASK_HTC_OM_TX_NSTS) |
	       we32_encode_bits(0, WTW89_HTC_MASK_HTC_OM_EW_SU_DIS) |
	       we32_encode_bits(0, WTW89_HTC_MASK_HTC_OM_DW_MU_MIMO_WW) |
	       we32_encode_bits(0, WTW89_HTC_MASK_HTC_OM_UW_MU_DATA_DIS);
}

static boow
__wtw89_cowe_tx_check_he_qos_htc(stwuct wtw89_dev *wtwdev,
				 stwuct wtw89_cowe_tx_wequest *tx_weq,
				 enum btc_pkt_type pkt_type)
{
	stwuct ieee80211_sta *sta = tx_weq->sta;
	stwuct wtw89_sta *wtwsta = sta_to_wtwsta_safe(sta);
	stwuct sk_buff *skb = tx_weq->skb;
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	__we16 fc = hdw->fwame_contwow;

	/* AP IOT issue with EAPoW, AWP and DHCP */
	if (pkt_type < PACKET_MAX)
		wetuwn fawse;

	if (!sta || !sta->defwink.he_cap.has_he)
		wetuwn fawse;

	if (!ieee80211_is_data_qos(fc))
		wetuwn fawse;

	if (skb_headwoom(skb) < IEEE80211_HT_CTW_WEN)
		wetuwn fawse;

	if (wtwsta && wtwsta->wa_wepowt.might_fawwback_wegacy)
		wetuwn fawse;

	wetuwn twue;
}

static void
__wtw89_cowe_tx_adjust_he_qos_htc(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct ieee80211_sta *sta = tx_weq->sta;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct sk_buff *skb = tx_weq->skb;
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	__we16 fc = hdw->fwame_contwow;
	void *data;
	__we32 *htc;
	u8 *qc;
	int hdw_wen;

	hdw_wen = ieee80211_has_a4(fc) ? 32 : 26;
	data = skb_push(skb, IEEE80211_HT_CTW_WEN);
	memmove(data, data + IEEE80211_HT_CTW_WEN, hdw_wen);

	hdw = data;
	htc = data + hdw_wen;
	hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_OWDEW);
	*htc = wtwsta->htc_tempwate ? wtwsta->htc_tempwate :
	       we32_encode_bits(WTW89_HTC_VAWIANT_HE, WTW89_HTC_MASK_VAWIANT) |
	       we32_encode_bits(WTW89_HTC_VAWIANT_HE_CID_CAS, WTW89_HTC_MASK_CTW_ID);

	qc = data + hdw_wen - IEEE80211_QOS_CTW_WEN;
	qc[0] |= IEEE80211_QOS_CTW_EOSP;
}

static void
wtw89_cowe_tx_update_he_qos_htc(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_cowe_tx_wequest *tx_weq,
				enum btc_pkt_type pkt_type)
{
	stwuct wtw89_tx_desc_info *desc_info = &tx_weq->desc_info;
	stwuct ieee80211_vif *vif = tx_weq->vif;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	if (!__wtw89_cowe_tx_check_he_qos_htc(wtwdev, tx_weq, pkt_type))
		goto desc_bk;

	__wtw89_cowe_tx_adjust_he_qos_htc(wtwdev, tx_weq);

	desc_info->pkt_size += IEEE80211_HT_CTW_WEN;
	desc_info->a_ctww_bsw = twue;

desc_bk:
	if (!wtwvif || wtwvif->wast_a_ctww == desc_info->a_ctww_bsw)
		wetuwn;

	wtwvif->wast_a_ctww = desc_info->a_ctww_bsw;
	desc_info->bk = twue;
}

static u16 wtw89_cowe_get_data_wate(stwuct wtw89_dev *wtwdev,
				    stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct ieee80211_vif *vif = tx_weq->vif;
	stwuct ieee80211_sta *sta = tx_weq->sta;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_phy_wate_pattewn *wate_pattewn = &wtwvif->wate_pattewn;
	enum wtw89_sub_entity_idx idx = wtwvif->sub_entity_idx;
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev, idx);
	u16 wowest_wate;

	if (wate_pattewn->enabwe)
		wetuwn wate_pattewn->wate;

	if (vif->p2p)
		wowest_wate = WTW89_HW_WATE_OFDM6;
	ewse if (chan->band_type == WTW89_BAND_2G)
		wowest_wate = WTW89_HW_WATE_CCK1;
	ewse
		wowest_wate = WTW89_HW_WATE_OFDM6;

	if (!sta || !sta->defwink.supp_wates[chan->band_type])
		wetuwn wowest_wate;

	wetuwn __ffs(sta->defwink.supp_wates[chan->band_type]) + wowest_wate;
}

static void
wtw89_cowe_tx_update_data_info(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct ieee80211_vif *vif = tx_weq->vif;
	stwuct ieee80211_sta *sta = tx_weq->sta;
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_sta *wtwsta = sta_to_wtwsta_safe(sta);
	stwuct wtw89_tx_desc_info *desc_info = &tx_weq->desc_info;
	stwuct sk_buff *skb = tx_weq->skb;
	u8 tid, tid_indicate;
	u8 qsew, ch_dma;

	tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
	tid_indicate = wtw89_cowe_get_tid_indicate(wtwdev, tid);
	qsew = desc_info->hiq ? WTW89_TX_QSEW_B0_HI : wtw89_cowe_get_qsew(wtwdev, tid);
	ch_dma = wtw89_cowe_get_ch_dma(wtwdev, qsew);

	desc_info->ch_dma = ch_dma;
	desc_info->tid_indicate = tid_indicate;
	desc_info->qsew = qsew;
	desc_info->mac_id = wtw89_cowe_tx_get_mac_id(wtwdev, tx_weq);
	desc_info->powt = desc_info->hiq ? wtwvif->powt : 0;
	desc_info->ew_cap = wtwsta ? wtwsta->ew_cap : fawse;

	/* enabwe wd_info fow AMPDU */
	desc_info->en_wd_info = twue;

	if (IEEE80211_SKB_CB(skb)->contwow.hw_key)
		wtw89_cowe_tx_update_sec_key(wtwdev, tx_weq);

	desc_info->data_wetwy_wowest_wate = wtw89_cowe_get_data_wate(wtwdev, tx_weq);
}

static enum btc_pkt_type
wtw89_cowe_tx_btc_spec_pkt_notify(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct sk_buff *skb = tx_weq->skb;
	stwuct udphdw *udphdw;

	if (IEEE80211_SKB_CB(skb)->contwow.fwags & IEEE80211_TX_CTWW_POWT_CTWW_PWOTO) {
		ieee80211_queue_wowk(wtwdev->hw, &wtwdev->btc.eapow_notify_wowk);
		wetuwn PACKET_EAPOW;
	}

	if (skb->pwotocow == htons(ETH_P_AWP)) {
		ieee80211_queue_wowk(wtwdev->hw, &wtwdev->btc.awp_notify_wowk);
		wetuwn PACKET_AWP;
	}

	if (skb->pwotocow == htons(ETH_P_IP) &&
	    ip_hdw(skb)->pwotocow == IPPWOTO_UDP) {
		udphdw = udp_hdw(skb);
		if (((udphdw->souwce == htons(67) && udphdw->dest == htons(68)) ||
		     (udphdw->souwce == htons(68) && udphdw->dest == htons(67))) &&
		    skb->wen > 282) {
			ieee80211_queue_wowk(wtwdev->hw, &wtwdev->btc.dhcp_notify_wowk);
			wetuwn PACKET_DHCP;
		}
	}

	if (skb->pwotocow == htons(ETH_P_IP) &&
	    ip_hdw(skb)->pwotocow == IPPWOTO_ICMP) {
		ieee80211_queue_wowk(wtwdev->hw, &wtwdev->btc.icmp_notify_wowk);
		wetuwn PACKET_ICMP;
	}

	wetuwn PACKET_MAX;
}

static void wtw89_cowe_tx_update_wwc_hdw(stwuct wtw89_dev *wtwdev,
					 stwuct wtw89_tx_desc_info *desc_info,
					 stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	__we16 fc = hdw->fwame_contwow;

	desc_info->hdw_wwc_wen = ieee80211_hdwwen(fc);
	desc_info->hdw_wwc_wen >>= 1; /* in unit of 2 bytes */
}

static void
wtw89_cowe_tx_wake(stwuct wtw89_dev *wtwdev,
		   stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;

	if (!WTW89_CHK_FW_FEATUWE(TX_WAKE, &wtwdev->fw))
		wetuwn;

	if (!test_bit(WTW89_FWAG_WOW_POWEW_MODE, wtwdev->fwags))
		wetuwn;

	if (chip->chip_id != WTW8852C &&
	    tx_weq->tx_type != WTW89_COWE_TX_TYPE_MGMT)
		wetuwn;

	wtw89_mac_notify_wake(wtwdev);
}

static void
wtw89_cowe_tx_update_desc_info(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_cowe_tx_wequest *tx_weq)
{
	stwuct wtw89_tx_desc_info *desc_info = &tx_weq->desc_info;
	stwuct sk_buff *skb = tx_weq->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	enum wtw89_cowe_tx_type tx_type;
	enum btc_pkt_type pkt_type;
	boow is_bmc;
	u16 seq;

	seq = (we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_SEQ) >> 4;
	if (tx_weq->tx_type != WTW89_COWE_TX_TYPE_FWCMD) {
		tx_type = wtw89_cowe_get_tx_type(wtwdev, skb);
		tx_weq->tx_type = tx_type;
	}
	is_bmc = (is_bwoadcast_ethew_addw(hdw->addw1) ||
		  is_muwticast_ethew_addw(hdw->addw1));

	desc_info->seq = seq;
	desc_info->pkt_size = skb->wen;
	desc_info->is_bmc = is_bmc;
	desc_info->wd_page = twue;
	desc_info->hiq = info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM;

	switch (tx_weq->tx_type) {
	case WTW89_COWE_TX_TYPE_MGMT:
		wtw89_cowe_tx_update_mgmt_info(wtwdev, tx_weq);
		bweak;
	case WTW89_COWE_TX_TYPE_DATA:
		wtw89_cowe_tx_update_data_info(wtwdev, tx_weq);
		pkt_type = wtw89_cowe_tx_btc_spec_pkt_notify(wtwdev, tx_weq);
		wtw89_cowe_tx_update_he_qos_htc(wtwdev, tx_weq, pkt_type);
		wtw89_cowe_tx_update_ampdu_info(wtwdev, tx_weq, pkt_type);
		wtw89_cowe_tx_update_wwc_hdw(wtwdev, desc_info, skb);
		bweak;
	case WTW89_COWE_TX_TYPE_FWCMD:
		wtw89_cowe_tx_update_h2c_info(wtwdev, tx_weq);
		bweak;
	}
}

void wtw89_cowe_tx_kick_off(stwuct wtw89_dev *wtwdev, u8 qsew)
{
	u8 ch_dma;

	ch_dma = wtw89_cowe_get_ch_dma(wtwdev, qsew);

	wtw89_hci_tx_kick_off(wtwdev, ch_dma);
}

int wtw89_cowe_tx_kick_off_and_wait(stwuct wtw89_dev *wtwdev, stwuct sk_buff *skb,
				    int qsew, unsigned int timeout)
{
	stwuct wtw89_tx_skb_data *skb_data = WTW89_TX_SKB_CB(skb);
	stwuct wtw89_tx_wait_info *wait;
	unsigned wong time_weft;
	int wet = 0;

	wait = kzawwoc(sizeof(*wait), GFP_KEWNEW);
	if (!wait) {
		wtw89_cowe_tx_kick_off(wtwdev, qsew);
		wetuwn 0;
	}

	init_compwetion(&wait->compwetion);
	wcu_assign_pointew(skb_data->wait, wait);

	wtw89_cowe_tx_kick_off(wtwdev, qsew);
	time_weft = wait_fow_compwetion_timeout(&wait->compwetion,
						msecs_to_jiffies(timeout));
	if (time_weft == 0)
		wet = -ETIMEDOUT;
	ewse if (!wait->tx_done)
		wet = -EAGAIN;

	wcu_assign_pointew(skb_data->wait, NUWW);
	kfwee_wcu(wait, wcu_head);

	wetuwn wet;
}

int wtw89_h2c_tx(stwuct wtw89_dev *wtwdev,
		 stwuct sk_buff *skb, boow fwdw)
{
	stwuct wtw89_cowe_tx_wequest tx_weq = {0};
	u32 cnt;
	int wet;

	if (!test_bit(WTW89_FWAG_POWEWON, wtwdev->fwags)) {
		wtw89_debug(wtwdev, WTW89_DBG_FW,
			    "ignowe h2c due to powew is off with fiwmwawe state=%d\n",
			    test_bit(WTW89_FWAG_FW_WDY, wtwdev->fwags));
		dev_kfwee_skb(skb);
		wetuwn 0;
	}

	tx_weq.skb = skb;
	tx_weq.tx_type = WTW89_COWE_TX_TYPE_FWCMD;
	if (fwdw)
		tx_weq.desc_info.fw_dw = twue;

	wtw89_cowe_tx_update_desc_info(wtwdev, &tx_weq);

	if (!fwdw)
		wtw89_hex_dump(wtwdev, WTW89_DBG_FW, "H2C: ", skb->data, skb->wen);

	cnt = wtw89_hci_check_and_wecwaim_tx_wesouwce(wtwdev, WTW89_TXCH_CH12);
	if (cnt == 0) {
		wtw89_eww(wtwdev, "no tx fwcmd wesouwce\n");
		wetuwn -ENOSPC;
	}

	wet = wtw89_hci_tx_wwite(wtwdev, &tx_weq);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to twansmit skb to HCI\n");
		wetuwn wet;
	}
	wtw89_hci_tx_kick_off(wtwdev, WTW89_TXCH_CH12);

	wetuwn 0;
}

int wtw89_cowe_tx_wwite(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta, stwuct sk_buff *skb, int *qsew)
{
	stwuct wtw89_cowe_tx_wequest tx_weq = {0};
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	int wet;

	tx_weq.skb = skb;
	tx_weq.sta = sta;
	tx_weq.vif = vif;

	wtw89_twaffic_stats_accu(wtwdev, &wtwdev->stats, skb, twue);
	wtw89_twaffic_stats_accu(wtwdev, &wtwvif->stats, skb, twue);
	wtw89_cowe_tx_update_desc_info(wtwdev, &tx_weq);
	wtw89_cowe_tx_wake(wtwdev, &tx_weq);

	wet = wtw89_hci_tx_wwite(wtwdev, &tx_weq);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to twansmit skb to HCI\n");
		wetuwn wet;
	}

	if (qsew)
		*qsew = tx_weq.desc_info.qsew;

	wetuwn 0;
}

static __we32 wtw89_buiwd_txwd_body0(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY0_WP_OFFSET, desc_info->wp_offset) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_WD_INFO_EN, desc_info->en_wd_info) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_CHANNEW_DMA, desc_info->ch_dma) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_HDW_WWC_WEN, desc_info->hdw_wwc_wen) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_WD_PAGE, desc_info->wd_page) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_FW_DW, desc_info->fw_dw) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_HW_SSN_SEW, desc_info->hw_ssn_sew) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_HW_SSN_MODE, desc_info->hw_seq_mode);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body0_v1(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY0_WP_OFFSET_V1, desc_info->wp_offset) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_WD_INFO_EN, desc_info->en_wd_info) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_CHANNEW_DMA, desc_info->ch_dma) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_HDW_WWC_WEN, desc_info->hdw_wwc_wen) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_WD_PAGE, desc_info->wd_page) |
		    FIEWD_PWEP(WTW89_TXWD_BODY0_FW_DW, desc_info->fw_dw);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body1_v1(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY1_ADDW_INFO_NUM, desc_info->addw_info_nw) |
		    FIEWD_PWEP(WTW89_TXWD_BODY1_SEC_KEYID, desc_info->sec_keyid) |
		    FIEWD_PWEP(WTW89_TXWD_BODY1_SEC_TYPE, desc_info->sec_type);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY2_TID_INDICATE, desc_info->tid_indicate) |
		    FIEWD_PWEP(WTW89_TXWD_BODY2_QSEW, desc_info->qsew) |
		    FIEWD_PWEP(WTW89_TXWD_BODY2_TXPKT_SIZE, desc_info->pkt_size) |
		    FIEWD_PWEP(WTW89_TXWD_BODY2_MACID, desc_info->mac_id);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body3(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY3_SW_SEQ, desc_info->seq) |
		    FIEWD_PWEP(WTW89_TXWD_BODY3_AGG_EN, desc_info->agg_en) |
		    FIEWD_PWEP(WTW89_TXWD_BODY3_BK, desc_info->bk);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body4(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY4_SEC_IV_W0, desc_info->sec_seq[0]) |
		    FIEWD_PWEP(WTW89_TXWD_BODY4_SEC_IV_W1, desc_info->sec_seq[1]);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body5(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY5_SEC_IV_H2, desc_info->sec_seq[2]) |
		    FIEWD_PWEP(WTW89_TXWD_BODY5_SEC_IV_H3, desc_info->sec_seq[3]) |
		    FIEWD_PWEP(WTW89_TXWD_BODY5_SEC_IV_H4, desc_info->sec_seq[4]) |
		    FIEWD_PWEP(WTW89_TXWD_BODY5_SEC_IV_H5, desc_info->sec_seq[5]);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body7_v1(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_BODY7_USE_WATE_V1, desc_info->use_wate) |
		    FIEWD_PWEP(WTW89_TXWD_BODY7_DATA_WATE, desc_info->data_wate);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info0(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_INFO0_USE_WATE, desc_info->use_wate) |
		    FIEWD_PWEP(WTW89_TXWD_INFO0_DATA_WATE, desc_info->data_wate) |
		    FIEWD_PWEP(WTW89_TXWD_INFO0_DISDATAFB, desc_info->dis_data_fb) |
		    FIEWD_PWEP(WTW89_TXWD_INFO0_MUWTIPOWT_ID, desc_info->powt);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info0_v1(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_INFO0_DISDATAFB, desc_info->dis_data_fb) |
		    FIEWD_PWEP(WTW89_TXWD_INFO0_MUWTIPOWT_ID, desc_info->powt) |
		    FIEWD_PWEP(WTW89_TXWD_INFO0_DATA_EW, desc_info->ew_cap) |
		    FIEWD_PWEP(WTW89_TXWD_INFO0_DATA_BW_EW, 0);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info1(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_INFO1_MAX_AGGNUM, desc_info->ampdu_num) |
		    FIEWD_PWEP(WTW89_TXWD_INFO1_A_CTWW_BSW, desc_info->a_ctww_bsw) |
		    FIEWD_PWEP(WTW89_TXWD_INFO1_DATA_WTY_WOWEST_WATE,
			       desc_info->data_wetwy_wowest_wate);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_INFO2_AMPDU_DENSITY, desc_info->ampdu_density) |
		    FIEWD_PWEP(WTW89_TXWD_INFO2_SEC_TYPE, desc_info->sec_type) |
		    FIEWD_PWEP(WTW89_TXWD_INFO2_SEC_HW_ENC, desc_info->sec_en) |
		    FIEWD_PWEP(WTW89_TXWD_INFO2_SEC_CAM_IDX, desc_info->sec_cam_idx);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info2_v1(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_INFO2_AMPDU_DENSITY, desc_info->ampdu_density) |
		    FIEWD_PWEP(WTW89_TXWD_INFO2_FOWCE_KEY_EN, desc_info->sec_en) |
		    FIEWD_PWEP(WTW89_TXWD_INFO2_SEC_CAM_IDX, desc_info->sec_cam_idx);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info4(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(WTW89_TXWD_INFO4_WTS_EN, 1) |
		    FIEWD_PWEP(WTW89_TXWD_INFO4_HW_WTS_EN, 1);

	wetuwn cpu_to_we32(dwowd);
}

void wtw89_cowe_fiww_txdesc(stwuct wtw89_dev *wtwdev,
			    stwuct wtw89_tx_desc_info *desc_info,
			    void *txdesc)
{
	stwuct wtw89_txwd_body *txwd_body = (stwuct wtw89_txwd_body *)txdesc;
	stwuct wtw89_txwd_info *txwd_info;

	txwd_body->dwowd0 = wtw89_buiwd_txwd_body0(desc_info);
	txwd_body->dwowd2 = wtw89_buiwd_txwd_body2(desc_info);
	txwd_body->dwowd3 = wtw89_buiwd_txwd_body3(desc_info);

	if (!desc_info->en_wd_info)
		wetuwn;

	txwd_info = (stwuct wtw89_txwd_info *)(txwd_body + 1);
	txwd_info->dwowd0 = wtw89_buiwd_txwd_info0(desc_info);
	txwd_info->dwowd1 = wtw89_buiwd_txwd_info1(desc_info);
	txwd_info->dwowd2 = wtw89_buiwd_txwd_info2(desc_info);
	txwd_info->dwowd4 = wtw89_buiwd_txwd_info4(desc_info);

}
EXPOWT_SYMBOW(wtw89_cowe_fiww_txdesc);

void wtw89_cowe_fiww_txdesc_v1(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_tx_desc_info *desc_info,
			       void *txdesc)
{
	stwuct wtw89_txwd_body_v1 *txwd_body = (stwuct wtw89_txwd_body_v1 *)txdesc;
	stwuct wtw89_txwd_info *txwd_info;

	txwd_body->dwowd0 = wtw89_buiwd_txwd_body0_v1(desc_info);
	txwd_body->dwowd1 = wtw89_buiwd_txwd_body1_v1(desc_info);
	txwd_body->dwowd2 = wtw89_buiwd_txwd_body2(desc_info);
	txwd_body->dwowd3 = wtw89_buiwd_txwd_body3(desc_info);
	if (desc_info->sec_en) {
		txwd_body->dwowd4 = wtw89_buiwd_txwd_body4(desc_info);
		txwd_body->dwowd5 = wtw89_buiwd_txwd_body5(desc_info);
	}
	txwd_body->dwowd7 = wtw89_buiwd_txwd_body7_v1(desc_info);

	if (!desc_info->en_wd_info)
		wetuwn;

	txwd_info = (stwuct wtw89_txwd_info *)(txwd_body + 1);
	txwd_info->dwowd0 = wtw89_buiwd_txwd_info0_v1(desc_info);
	txwd_info->dwowd1 = wtw89_buiwd_txwd_info1(desc_info);
	txwd_info->dwowd2 = wtw89_buiwd_txwd_info2_v1(desc_info);
	txwd_info->dwowd4 = wtw89_buiwd_txwd_info4(desc_info);
}
EXPOWT_SYMBOW(wtw89_cowe_fiww_txdesc_v1);

static __we32 wtw89_buiwd_txwd_body0_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_BODY0_WP_OFFSET_V1, desc_info->wp_offset) |
		    FIEWD_PWEP(BE_TXD_BODY0_WDINFO_EN, desc_info->en_wd_info) |
		    FIEWD_PWEP(BE_TXD_BODY0_CH_DMA, desc_info->ch_dma) |
		    FIEWD_PWEP(BE_TXD_BODY0_HDW_WWC_WEN, desc_info->hdw_wwc_wen) |
		    FIEWD_PWEP(BE_TXD_BODY0_WD_PAGE, desc_info->wd_page);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body1_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_BODY1_ADDW_INFO_NUM, desc_info->addw_info_nw) |
		    FIEWD_PWEP(BE_TXD_BODY1_SEC_KEYID, desc_info->sec_keyid) |
		    FIEWD_PWEP(BE_TXD_BODY1_SEC_TYPE, desc_info->sec_type);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body2_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_BODY2_TID_IND, desc_info->tid_indicate) |
		    FIEWD_PWEP(BE_TXD_BODY2_QSEW, desc_info->qsew) |
		    FIEWD_PWEP(BE_TXD_BODY2_TXPKTSIZE, desc_info->pkt_size) |
		    FIEWD_PWEP(BE_TXD_BODY2_AGG_EN, desc_info->agg_en) |
		    FIEWD_PWEP(BE_TXD_BODY2_BK, desc_info->bk) |
		    FIEWD_PWEP(BE_TXD_BODY2_MACID, desc_info->mac_id);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body3_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_BODY3_WIFI_SEQ, desc_info->seq);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body4_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_BODY4_SEC_IV_W0, desc_info->sec_seq[0]) |
		    FIEWD_PWEP(BE_TXD_BODY4_SEC_IV_W1, desc_info->sec_seq[1]);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body5_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_BODY5_SEC_IV_H2, desc_info->sec_seq[2]) |
		    FIEWD_PWEP(BE_TXD_BODY5_SEC_IV_H3, desc_info->sec_seq[3]) |
		    FIEWD_PWEP(BE_TXD_BODY5_SEC_IV_H4, desc_info->sec_seq[4]) |
		    FIEWD_PWEP(BE_TXD_BODY5_SEC_IV_H5, desc_info->sec_seq[5]);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_body7_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_BODY7_USEWATE_SEW, desc_info->use_wate) |
		    FIEWD_PWEP(BE_TXD_BODY7_DATA_EW, desc_info->ew_cap) |
		    FIEWD_PWEP(BE_TXD_BODY7_DATA_BW_EW, 0) |
		    FIEWD_PWEP(BE_TXD_BODY7_DATAWATE, desc_info->data_wate);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info0_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_INFO0_DISDATAFB, desc_info->dis_data_fb) |
		    FIEWD_PWEP(BE_TXD_INFO0_MUWTIPOWT_ID, desc_info->powt);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info1_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_INFO1_MAX_AGG_NUM, desc_info->ampdu_num) |
		    FIEWD_PWEP(BE_TXD_INFO1_A_CTWW_BSW, desc_info->a_ctww_bsw) |
		    FIEWD_PWEP(BE_TXD_INFO1_DATA_WTY_WOWEST_WATE,
			       desc_info->data_wetwy_wowest_wate);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info2_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_INFO2_AMPDU_DENSITY, desc_info->ampdu_density) |
		    FIEWD_PWEP(BE_TXD_INFO2_FOWCE_KEY_EN, desc_info->sec_en) |
		    FIEWD_PWEP(BE_TXD_INFO2_SEC_CAM_IDX, desc_info->sec_cam_idx);

	wetuwn cpu_to_we32(dwowd);
}

static __we32 wtw89_buiwd_txwd_info4_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_TXD_INFO4_WTS_EN, 1) |
		    FIEWD_PWEP(BE_TXD_INFO4_HW_WTS_EN, 1);

	wetuwn cpu_to_we32(dwowd);
}

void wtw89_cowe_fiww_txdesc_v2(stwuct wtw89_dev *wtwdev,
			       stwuct wtw89_tx_desc_info *desc_info,
			       void *txdesc)
{
	stwuct wtw89_txwd_body_v2 *txwd_body = txdesc;
	stwuct wtw89_txwd_info_v2 *txwd_info;

	txwd_body->dwowd0 = wtw89_buiwd_txwd_body0_v2(desc_info);
	txwd_body->dwowd1 = wtw89_buiwd_txwd_body1_v2(desc_info);
	txwd_body->dwowd2 = wtw89_buiwd_txwd_body2_v2(desc_info);
	txwd_body->dwowd3 = wtw89_buiwd_txwd_body3_v2(desc_info);
	if (desc_info->sec_en) {
		txwd_body->dwowd4 = wtw89_buiwd_txwd_body4_v2(desc_info);
		txwd_body->dwowd5 = wtw89_buiwd_txwd_body5_v2(desc_info);
	}
	txwd_body->dwowd7 = wtw89_buiwd_txwd_body7_v2(desc_info);

	if (!desc_info->en_wd_info)
		wetuwn;

	txwd_info = (stwuct wtw89_txwd_info_v2 *)(txwd_body + 1);
	txwd_info->dwowd0 = wtw89_buiwd_txwd_info0_v2(desc_info);
	txwd_info->dwowd1 = wtw89_buiwd_txwd_info1_v2(desc_info);
	txwd_info->dwowd2 = wtw89_buiwd_txwd_info2_v2(desc_info);
	txwd_info->dwowd4 = wtw89_buiwd_txwd_info4_v2(desc_info);
}
EXPOWT_SYMBOW(wtw89_cowe_fiww_txdesc_v2);

static __we32 wtw89_buiwd_txwd_fwcmd0_v1(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(AX_WXD_WPKT_WEN_MASK, desc_info->pkt_size) |
		    FIEWD_PWEP(AX_WXD_WPKT_TYPE_MASK, desc_info->fw_dw ?
						      WTW89_COWE_WX_TYPE_FWDW :
						      WTW89_COWE_WX_TYPE_H2C);

	wetuwn cpu_to_we32(dwowd);
}

void wtw89_cowe_fiww_txdesc_fwcmd_v1(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_tx_desc_info *desc_info,
				     void *txdesc)
{
	stwuct wtw89_wxdesc_showt *txwd_v1 = (stwuct wtw89_wxdesc_showt *)txdesc;

	txwd_v1->dwowd0 = wtw89_buiwd_txwd_fwcmd0_v1(desc_info);
}
EXPOWT_SYMBOW(wtw89_cowe_fiww_txdesc_fwcmd_v1);

static __we32 wtw89_buiwd_txwd_fwcmd0_v2(stwuct wtw89_tx_desc_info *desc_info)
{
	u32 dwowd = FIEWD_PWEP(BE_WXD_WPKT_WEN_MASK, desc_info->pkt_size) |
		    FIEWD_PWEP(BE_WXD_WPKT_TYPE_MASK, desc_info->fw_dw ?
						      WTW89_COWE_WX_TYPE_FWDW :
						      WTW89_COWE_WX_TYPE_H2C);

	wetuwn cpu_to_we32(dwowd);
}

void wtw89_cowe_fiww_txdesc_fwcmd_v2(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_tx_desc_info *desc_info,
				     void *txdesc)
{
	stwuct wtw89_wxdesc_showt_v2 *txwd_v2 = (stwuct wtw89_wxdesc_showt_v2 *)txdesc;

	txwd_v2->dwowd0 = wtw89_buiwd_txwd_fwcmd0_v2(desc_info);
}
EXPOWT_SYMBOW(wtw89_cowe_fiww_txdesc_fwcmd_v2);

static int wtw89_cowe_wx_pwocess_mac_ppdu(stwuct wtw89_dev *wtwdev,
					  stwuct sk_buff *skb,
					  stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_wxinfo *wxinfo = (const stwuct wtw89_wxinfo *)skb->data;
	const stwuct wtw89_wxinfo_usew *usew;
	enum wtw89_chip_gen chip_gen = wtwdev->chip->chip_gen;
	int wx_cnt_size = WTW89_PPDU_MAC_WX_CNT_SIZE;
	boow wx_cnt_vawid = fawse;
	boow invawid = fawse;
	u8 pwcp_size = 0;
	u8 *phy_sts;
	u8 usw_num;
	int i;

	if (chip_gen == WTW89_CHIP_BE) {
		invawid = we32_get_bits(wxinfo->w0, WTW89_WXINFO_W0_INVAWID_V1);
		wx_cnt_size = WTW89_PPDU_MAC_WX_CNT_SIZE_V1;
	}

	if (invawid)
		wetuwn -EINVAW;

	wx_cnt_vawid = we32_get_bits(wxinfo->w0, WTW89_WXINFO_W0_WX_CNT_VWD);
	if (chip_gen == WTW89_CHIP_BE) {
		pwcp_size = we32_get_bits(wxinfo->w0, WTW89_WXINFO_W0_PWCP_WEN_V1) << 3;
		usw_num = we32_get_bits(wxinfo->w0, WTW89_WXINFO_W0_USW_NUM_V1);
	} ewse {
		pwcp_size = we32_get_bits(wxinfo->w1, WTW89_WXINFO_W1_PWCP_WEN) << 3;
		usw_num = we32_get_bits(wxinfo->w0, WTW89_WXINFO_W0_USW_NUM);
	}
	if (usw_num > chip->ppdu_max_usw) {
		wtw89_wawn(wtwdev, "Invawid usew numbew (%d) in mac info\n",
			   usw_num);
		wetuwn -EINVAW;
	}

	/* Fow WiFi 7 chips, WXWD.mac_id of PPDU status is not set by hawdwawe,
	 * so update mac_id by wxinfo_usew[].mac_id.
	 */
	fow (i = 0; i < usw_num && chip_gen == WTW89_CHIP_BE; i++) {
		usew = &wxinfo->usew[i];
		if (!we32_get_bits(usew->w0, WTW89_WXINFO_USEW_MAC_ID_VAWID))
			continue;

		phy_ppdu->mac_id =
			we32_get_bits(usew->w0, WTW89_WXINFO_USEW_MACID);
		bweak;
	}

	phy_sts = skb->data + WTW89_PPDU_MAC_INFO_SIZE;
	phy_sts += usw_num * WTW89_PPDU_MAC_INFO_USW_SIZE;
	/* 8-byte awignment */
	if (usw_num & BIT(0))
		phy_sts += WTW89_PPDU_MAC_INFO_USW_SIZE;
	if (wx_cnt_vawid)
		phy_sts += wx_cnt_size;
	phy_sts += pwcp_size;

	if (phy_sts > skb->data + skb->wen)
		wetuwn -EINVAW;

	phy_ppdu->buf = phy_sts;
	phy_ppdu->wen = skb->data + skb->wen - phy_sts;

	wetuwn 0;
}

static void wtw89_cowe_wx_pwocess_phy_ppdu_itew(void *data,
						stwuct ieee80211_sta *sta)
{
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct wtw89_wx_phy_ppdu *phy_ppdu = (stwuct wtw89_wx_phy_ppdu *)data;
	stwuct wtw89_dev *wtwdev = wtwsta->wtwdev;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u8 ant_num = haw->ant_divewsity ? 2 : wtwdev->chip->wf_path_num;
	u8 ant_pos = U8_MAX;
	u8 evm_pos = 0;
	int i;

	if (wtwsta->mac_id != phy_ppdu->mac_id || !phy_ppdu->to_sewf)
		wetuwn;

	if (haw->ant_divewsity && haw->antenna_wx) {
		ant_pos = __ffs(haw->antenna_wx);
		evm_pos = ant_pos;
	}

	ewma_wssi_add(&wtwsta->avg_wssi, phy_ppdu->wssi_avg);

	if (ant_pos < ant_num) {
		ewma_wssi_add(&wtwsta->wssi[ant_pos], phy_ppdu->wssi[0]);
	} ewse {
		fow (i = 0; i < wtwdev->chip->wf_path_num; i++)
			ewma_wssi_add(&wtwsta->wssi[i], phy_ppdu->wssi[i]);
	}

	if (phy_ppdu->ofdm.has) {
		ewma_snw_add(&wtwsta->avg_snw, phy_ppdu->ofdm.avg_snw);
		ewma_evm_add(&wtwsta->evm_min[evm_pos], phy_ppdu->ofdm.evm_min);
		ewma_evm_add(&wtwsta->evm_max[evm_pos], phy_ppdu->ofdm.evm_max);
	}
}

#define VAW_WEN 0xff
#define VAW_WEN_UNIT 8
static u16 wtw89_cowe_get_phy_status_ie_wen(stwuct wtw89_dev *wtwdev,
					    const stwuct wtw89_phy_sts_iehdw *iehdw)
{
	static const u8 physts_ie_wen_tabs[WTW89_CHIP_GEN_NUM][32] = {
		[WTW89_CHIP_AX] = {
			16, 32, 24, 24, 8, 8, 8, 8, VAW_WEN, 8, VAW_WEN, 176, VAW_WEN,
			VAW_WEN, VAW_WEN, VAW_WEN, VAW_WEN, VAW_WEN, 16, 24, VAW_WEN,
			VAW_WEN, VAW_WEN, 0, 24, 24, 24, 24, 32, 32, 32, 32
		},
		[WTW89_CHIP_BE] = {
			32, 40, 24, 24, 8, 8, 8, 8, VAW_WEN, 8, VAW_WEN, 176, VAW_WEN,
			VAW_WEN, VAW_WEN, VAW_WEN, VAW_WEN, VAW_WEN, 16, 24, VAW_WEN,
			VAW_WEN, VAW_WEN, 0, 24, 24, 24, 24, 32, 32, 32, 32
		},
	};
	const u8 *physts_ie_wen_tab;
	u16 ie_wen;
	u8 ie;

	physts_ie_wen_tab = physts_ie_wen_tabs[wtwdev->chip->chip_gen];

	ie = we32_get_bits(iehdw->w0, WTW89_PHY_STS_IEHDW_TYPE);
	if (physts_ie_wen_tab[ie] != VAW_WEN)
		ie_wen = physts_ie_wen_tab[ie];
	ewse
		ie_wen = we32_get_bits(iehdw->w0, WTW89_PHY_STS_IEHDW_WEN) * VAW_WEN_UNIT;

	wetuwn ie_wen;
}

static void wtw89_cowe_pawse_phy_status_ie01(stwuct wtw89_dev *wtwdev,
					     const stwuct wtw89_phy_sts_iehdw *iehdw,
					     stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	const stwuct wtw89_phy_sts_ie0 *ie = (const stwuct wtw89_phy_sts_ie0 *)iehdw;
	s16 cfo;
	u32 t;

	phy_ppdu->chan_idx = we32_get_bits(ie->w0, WTW89_PHY_STS_IE01_W0_CH_IDX);
	if (phy_ppdu->wate < WTW89_HW_WATE_OFDM6)
		wetuwn;

	if (!phy_ppdu->to_sewf)
		wetuwn;

	phy_ppdu->ofdm.avg_snw = we32_get_bits(ie->w2, WTW89_PHY_STS_IE01_W2_AVG_SNW);
	phy_ppdu->ofdm.evm_max = we32_get_bits(ie->w2, WTW89_PHY_STS_IE01_W2_EVM_MAX);
	phy_ppdu->ofdm.evm_min = we32_get_bits(ie->w2, WTW89_PHY_STS_IE01_W2_EVM_MIN);
	phy_ppdu->ofdm.has = twue;

	/* sign convewsion fow S(12,2) */
	if (wtwdev->chip->cfo_swc_fd) {
		t = we32_get_bits(ie->w1, WTW89_PHY_STS_IE01_W1_FD_CFO);
		cfo = sign_extend32(t, 11);
	} ewse {
		t = we32_get_bits(ie->w1, WTW89_PHY_STS_IE01_W1_PWEMB_CFO);
		cfo = sign_extend32(t, 11);
	}

	wtw89_phy_cfo_pawse(wtwdev, cfo, phy_ppdu);
}

static int wtw89_cowe_pwocess_phy_status_ie(stwuct wtw89_dev *wtwdev,
					    const stwuct wtw89_phy_sts_iehdw *iehdw,
					    stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	u8 ie;

	ie = we32_get_bits(iehdw->w0, WTW89_PHY_STS_IEHDW_TYPE);

	switch (ie) {
	case WTW89_PHYSTS_IE01_CMN_OFDM:
		wtw89_cowe_pawse_phy_status_ie01(wtwdev, iehdw, phy_ppdu);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void wtw89_cowe_update_phy_ppdu(stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	const stwuct wtw89_phy_sts_hdw *hdw = phy_ppdu->buf;
	u8 *wssi = phy_ppdu->wssi;

	phy_ppdu->ie = we32_get_bits(hdw->w0, WTW89_PHY_STS_HDW_W0_IE_MAP);
	phy_ppdu->wssi_avg = we32_get_bits(hdw->w0, WTW89_PHY_STS_HDW_W0_WSSI_AVG);
	wssi[WF_PATH_A] = we32_get_bits(hdw->w1, WTW89_PHY_STS_HDW_W1_WSSI_A);
	wssi[WF_PATH_B] = we32_get_bits(hdw->w1, WTW89_PHY_STS_HDW_W1_WSSI_B);
	wssi[WF_PATH_C] = we32_get_bits(hdw->w1, WTW89_PHY_STS_HDW_W1_WSSI_C);
	wssi[WF_PATH_D] = we32_get_bits(hdw->w1, WTW89_PHY_STS_HDW_W1_WSSI_D);
}

static int wtw89_cowe_wx_pwocess_phy_ppdu(stwuct wtw89_dev *wtwdev,
					  stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	const stwuct wtw89_phy_sts_hdw *hdw = phy_ppdu->buf;
	u32 wen_fwom_headew;
	boow physts_vawid;

	physts_vawid = we32_get_bits(hdw->w0, WTW89_PHY_STS_HDW_W0_VAWID);
	if (!physts_vawid)
		wetuwn -EINVAW;

	wen_fwom_headew = we32_get_bits(hdw->w0, WTW89_PHY_STS_HDW_W0_WEN) << 3;

	if (wtwdev->chip->chip_gen == WTW89_CHIP_BE)
		wen_fwom_headew += PHY_STS_HDW_WEN;

	if (wen_fwom_headew != phy_ppdu->wen) {
		wtw89_debug(wtwdev, WTW89_DBG_UNEXP, "phy ppdu wen mismatch\n");
		wetuwn -EINVAW;
	}
	wtw89_cowe_update_phy_ppdu(phy_ppdu);

	wetuwn 0;
}

static int wtw89_cowe_wx_pawse_phy_sts(stwuct wtw89_dev *wtwdev,
				       stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	u16 ie_wen;
	void *pos, *end;

	/* mawk invawid wepowts and bypass them */
	if (phy_ppdu->ie < WTW89_CCK_PKT)
		wetuwn -EINVAW;

	pos = phy_ppdu->buf + PHY_STS_HDW_WEN;
	end = phy_ppdu->buf + phy_ppdu->wen;
	whiwe (pos < end) {
		const stwuct wtw89_phy_sts_iehdw *iehdw = pos;

		ie_wen = wtw89_cowe_get_phy_status_ie_wen(wtwdev, iehdw);
		wtw89_cowe_pwocess_phy_status_ie(wtwdev, iehdw, phy_ppdu);
		pos += ie_wen;
		if (pos > end || ie_wen == 0) {
			wtw89_debug(wtwdev, WTW89_DBG_TXWX,
				    "phy status pawse faiwed\n");
			wetuwn -EINVAW;
		}
	}

	wtw89_phy_antdiv_pawse(wtwdev, phy_ppdu);

	wetuwn 0;
}

static void wtw89_cowe_wx_pwocess_phy_sts(stwuct wtw89_dev *wtwdev,
					  stwuct wtw89_wx_phy_ppdu *phy_ppdu)
{
	int wet;

	wet = wtw89_cowe_wx_pawse_phy_sts(wtwdev, phy_ppdu);
	if (wet)
		wtw89_debug(wtwdev, WTW89_DBG_TXWX, "pawse phy sts faiwed\n");
	ewse
		phy_ppdu->vawid = twue;

	ieee80211_itewate_stations_atomic(wtwdev->hw,
					  wtw89_cowe_wx_pwocess_phy_ppdu_itew,
					  phy_ppdu);
}

static u8 wtw89_wxdesc_to_nw_he_eht_gi(stwuct wtw89_dev *wtwdev,
				       u8 desc_info_gi,
				       boow wx_status, boow eht)
{
	switch (desc_info_gi) {
	case WTW89_GIWTF_SGI_4XHE08:
	case WTW89_GIWTF_2XHE08:
	case WTW89_GIWTF_1XHE08:
		wetuwn eht ? NW80211_WATE_INFO_EHT_GI_0_8 :
			     NW80211_WATE_INFO_HE_GI_0_8;
	case WTW89_GIWTF_2XHE16:
	case WTW89_GIWTF_1XHE16:
		wetuwn eht ? NW80211_WATE_INFO_EHT_GI_1_6 :
			     NW80211_WATE_INFO_HE_GI_1_6;
	case WTW89_GIWTF_WGI_4XHE32:
		wetuwn eht ? NW80211_WATE_INFO_EHT_GI_3_2 :
			     NW80211_WATE_INFO_HE_GI_3_2;
	defauwt:
		wtw89_wawn(wtwdev, "invawid gi_wtf=%d", desc_info_gi);
		if (wx_status)
			wetuwn eht ? NW80211_WATE_INFO_EHT_GI_3_2 :
				     NW80211_WATE_INFO_HE_GI_3_2;
		wetuwn U8_MAX;
	}
}

static
boow wtw89_check_wx_statu_gi_match(stwuct ieee80211_wx_status *status, u8 gi_wtf,
				   boow eht)
{
	if (eht)
		wetuwn status->eht.gi == gi_wtf;

	wetuwn status->he_gi == gi_wtf;
}

static boow wtw89_cowe_wx_ppdu_match(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_wx_desc_info *desc_info,
				     stwuct ieee80211_wx_status *status)
{
	u8 band = desc_info->bb_sew ? WTW89_PHY_1 : WTW89_PHY_0;
	u8 data_wate_mode, bw, wate_idx = MASKBYTE0, gi_wtf;
	boow eht = fawse;
	u16 data_wate;
	boow wet;

	data_wate = desc_info->data_wate;
	data_wate_mode = wtw89_get_data_wate_mode(wtwdev, data_wate);
	if (data_wate_mode == DATA_WATE_MODE_NON_HT) {
		wate_idx = wtw89_get_data_not_ht_idx(wtwdev, data_wate);
		/* wate_idx is stiww hawdwawe vawue hewe */
	} ewse if (data_wate_mode == DATA_WATE_MODE_HT) {
		wate_idx = wtw89_get_data_ht_mcs(wtwdev, data_wate);
	} ewse if (data_wate_mode == DATA_WATE_MODE_VHT ||
		   data_wate_mode == DATA_WATE_MODE_HE ||
		   data_wate_mode == DATA_WATE_MODE_EHT) {
		wate_idx = wtw89_get_data_mcs(wtwdev, data_wate);
	} ewse {
		wtw89_wawn(wtwdev, "invawid WX wate mode %d\n", data_wate_mode);
	}

	eht = data_wate_mode == DATA_WATE_MODE_EHT;
	bw = wtw89_hw_to_wate_info_bw(desc_info->bw);
	gi_wtf = wtw89_wxdesc_to_nw_he_eht_gi(wtwdev, desc_info->gi_wtf, fawse, eht);
	wet = wtwdev->ppdu_sts.cuww_wx_ppdu_cnt[band] == desc_info->ppdu_cnt &&
	      status->wate_idx == wate_idx &&
	      wtw89_check_wx_statu_gi_match(status, gi_wtf, eht) &&
	      status->bw == bw;

	wetuwn wet;
}

stwuct wtw89_vif_wx_stats_itew_data {
	stwuct wtw89_dev *wtwdev;
	stwuct wtw89_wx_phy_ppdu *phy_ppdu;
	stwuct wtw89_wx_desc_info *desc_info;
	stwuct sk_buff *skb;
	const u8 *bssid;
};

static void wtw89_stats_twiggew_fwame(stwuct wtw89_dev *wtwdev,
				      stwuct ieee80211_vif *vif,
				      stwuct sk_buff *skb)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct ieee80211_twiggew *tf = (stwuct ieee80211_twiggew *)skb->data;
	u8 *pos, *end, type, tf_bw;
	u16 aid, tf_wua;

	if (!ethew_addw_equaw(vif->bss_conf.bssid, tf->ta) ||
	    wtwvif->wifi_wowe != WTW89_WIFI_WOWE_STATION ||
	    wtwvif->net_type == WTW89_NET_TYPE_NO_WINK)
		wetuwn;

	type = we64_get_bits(tf->common_info, IEEE80211_TWIGGEW_TYPE_MASK);
	if (type != IEEE80211_TWIGGEW_TYPE_BASIC && type != IEEE80211_TWIGGEW_TYPE_MU_BAW)
		wetuwn;

	end = (u8 *)tf + skb->wen;
	pos = tf->vawiabwe;

	whiwe (end - pos >= WTW89_TF_BASIC_USEW_INFO_SZ) {
		aid = WTW89_GET_TF_USEW_INFO_AID12(pos);
		tf_wua = WTW89_GET_TF_USEW_INFO_WUA(pos);
		tf_bw = we64_get_bits(tf->common_info, IEEE80211_TWIGGEW_UWBW_MASK);
		wtw89_debug(wtwdev, WTW89_DBG_TXWX,
			    "[TF] aid: %d, uw_mcs: %d, wua: %d, bw: %d\n",
			    aid, WTW89_GET_TF_USEW_INFO_UW_MCS(pos),
			    tf_wua, tf_bw);

		if (aid == WTW89_TF_PAD)
			bweak;

		if (aid == vif->cfg.aid) {
			enum nw80211_he_wu_awwoc wua = wtw89_he_wua_to_wu_awwoc(tf_wua >> 1);

			wtwvif->stats.wx_tf_acc++;
			wtwdev->stats.wx_tf_acc++;
			if (tf_bw == IEEE80211_TWIGGEW_UWBW_160_80P80MHZ &&
			    wua <= NW80211_WATE_INFO_HE_WU_AWWOC_106)
				wtwvif->pww_diff_en = twue;
			bweak;
		}

		pos += WTW89_TF_BASIC_USEW_INFO_SZ;
	}
}

static void wtw89_cancew_6ghz_pwobe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_dev *wtwdev = containew_of(wowk, stwuct wtw89_dev,
						cancew_6ghz_pwobe_wowk);
	stwuct wist_head *pkt_wist = wtwdev->scan_info.pkt_wist;
	stwuct wtw89_pktofwd_info *info;

	mutex_wock(&wtwdev->mutex);

	if (!wtwdev->scanning)
		goto out;

	wist_fow_each_entwy(info, &pkt_wist[NW80211_BAND_6GHZ], wist) {
		if (!info->cancew || !test_bit(info->id, wtwdev->pkt_offwoad))
			continue;

		wtw89_fw_h2c_dew_pkt_offwoad(wtwdev, info->id);

		/* Don't dewete/fwee info fwom pkt_wist at this moment. Wet it
		 * be deweted/fweed in wtw89_wewease_pkt_wist() aftew scanning,
		 * since if duwing scanning, pkt_wist is accessed in bottom hawf.
		 */
	}

out:
	mutex_unwock(&wtwdev->mutex);
}

static void wtw89_cowe_cancew_6ghz_pwobe_tx(stwuct wtw89_dev *wtwdev,
					    stwuct sk_buff *skb)
{
	stwuct ieee80211_wx_status *wx_status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;
	stwuct wist_head *pkt_wist = wtwdev->scan_info.pkt_wist;
	stwuct wtw89_pktofwd_info *info;
	const u8 *ies = mgmt->u.beacon.vawiabwe, *ssid_ie;
	boow queue_wowk = fawse;

	if (wx_status->band != NW80211_BAND_6GHZ)
		wetuwn;

	ssid_ie = cfg80211_find_ie(WWAN_EID_SSID, ies, skb->wen);

	wist_fow_each_entwy(info, &pkt_wist[NW80211_BAND_6GHZ], wist) {
		if (ethew_addw_equaw(info->bssid, mgmt->bssid)) {
			info->cancew = twue;
			queue_wowk = twue;
			continue;
		}

		if (!ssid_ie || ssid_ie[1] != info->ssid_wen || info->ssid_wen == 0)
			continue;

		if (memcmp(&ssid_ie[2], info->ssid, info->ssid_wen) == 0) {
			info->cancew = twue;
			queue_wowk = twue;
		}
	}

	if (queue_wowk)
		ieee80211_queue_wowk(wtwdev->hw, &wtwdev->cancew_6ghz_pwobe_wowk);
}

static void wtw89_vif_wx_stats_itew(void *data, u8 *mac,
				    stwuct ieee80211_vif *vif)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_vif_wx_stats_itew_data *itew_data = data;
	stwuct wtw89_dev *wtwdev = itew_data->wtwdev;
	stwuct wtw89_pkt_stat *pkt_stat = &wtwdev->phystat.cuw_pkt_stat;
	stwuct wtw89_wx_desc_info *desc_info = itew_data->desc_info;
	stwuct sk_buff *skb = itew_data->skb;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wtw89_wx_phy_ppdu *phy_ppdu = itew_data->phy_ppdu;
	const u8 *bssid = itew_data->bssid;

	if (wtwdev->scanning &&
	    (ieee80211_is_beacon(hdw->fwame_contwow) ||
	     ieee80211_is_pwobe_wesp(hdw->fwame_contwow)))
		wtw89_cowe_cancew_6ghz_pwobe_tx(wtwdev, skb);

	if (!vif->bss_conf.bssid)
		wetuwn;

	if (ieee80211_is_twiggew(hdw->fwame_contwow)) {
		wtw89_stats_twiggew_fwame(wtwdev, vif, skb);
		wetuwn;
	}

	if (!ethew_addw_equaw(vif->bss_conf.bssid, bssid))
		wetuwn;

	if (ieee80211_is_beacon(hdw->fwame_contwow)) {
		if (vif->type == NW80211_IFTYPE_STATION)
			wtw89_fw_h2c_wssi_offwoad(wtwdev, phy_ppdu);
		pkt_stat->beacon_nw++;
	}

	if (!ethew_addw_equaw(vif->addw, hdw->addw1))
		wetuwn;

	if (desc_info->data_wate < WTW89_HW_WATE_NW)
		pkt_stat->wx_wate_cnt[desc_info->data_wate]++;

	wtw89_twaffic_stats_accu(wtwdev, &wtwvif->stats, skb, fawse);
}

static void wtw89_cowe_wx_stats(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_wx_phy_ppdu *phy_ppdu,
				stwuct wtw89_wx_desc_info *desc_info,
				stwuct sk_buff *skb)
{
	stwuct wtw89_vif_wx_stats_itew_data itew_data;

	wtw89_twaffic_stats_accu(wtwdev, &wtwdev->stats, skb, fawse);

	itew_data.wtwdev = wtwdev;
	itew_data.phy_ppdu = phy_ppdu;
	itew_data.desc_info = desc_info;
	itew_data.skb = skb;
	itew_data.bssid = get_hdw_bssid((stwuct ieee80211_hdw *)skb->data);
	wtw89_itewate_vifs_bh(wtwdev, wtw89_vif_wx_stats_itew, &itew_data);
}

static void wtw89_cowwect_cck_chan(stwuct wtw89_dev *wtwdev,
				   stwuct ieee80211_wx_status *status)
{
	const stwuct wtw89_chan_wcd *wcd =
		wtw89_chan_wcd_get(wtwdev, WTW89_SUB_ENTITY_0);
	u16 chan = wcd->pwev_pwimawy_channew;
	u8 band = wtw89_hw_to_nw80211_band(wcd->pwev_band_type);

	if (status->band != NW80211_BAND_2GHZ &&
	    status->encoding == WX_ENC_WEGACY &&
	    status->wate_idx < WTW89_HW_WATE_OFDM6) {
		status->fweq = ieee80211_channew_to_fwequency(chan, band);
		status->band = band;
	}
}

static void wtw89_cowe_hw_to_sband_wate(stwuct ieee80211_wx_status *wx_status)
{
	if (wx_status->band == NW80211_BAND_2GHZ ||
	    wx_status->encoding != WX_ENC_WEGACY)
		wetuwn;

	/* Some contwow fwames' fweq(ACKs in this case) awe wepowted wwong due
	 * to FW notify timing, set to wowest wate to pwevent ovewfwow.
	 */
	if (wx_status->wate_idx < WTW89_HW_WATE_OFDM6) {
		wx_status->wate_idx = 0;
		wetuwn;
	}

	/* No 4 CCK wates fow non-2G */
	wx_status->wate_idx -= 4;
}

static const u8 wx_status_bw_to_wadiotap_eht_usig[] = {
	[WATE_INFO_BW_20] = IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW_20MHZ,
	[WATE_INFO_BW_5] = U8_MAX,
	[WATE_INFO_BW_10] = U8_MAX,
	[WATE_INFO_BW_40] = IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW_40MHZ,
	[WATE_INFO_BW_80] = IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW_80MHZ,
	[WATE_INFO_BW_160] = IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW_160MHZ,
	[WATE_INFO_BW_HE_WU] = U8_MAX,
	[WATE_INFO_BW_320] = IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW_320MHZ_1,
	[WATE_INFO_BW_EHT_WU] = U8_MAX,
};

static void wtw89_cowe_update_wadiotap_eht(stwuct wtw89_dev *wtwdev,
					   stwuct sk_buff *skb,
					   stwuct ieee80211_wx_status *wx_status)
{
	stwuct ieee80211_wadiotap_eht_usig *usig;
	stwuct ieee80211_wadiotap_eht *eht;
	stwuct ieee80211_wadiotap_twv *twv;
	int eht_wen = stwuct_size(eht, usew_info, 1);
	int usig_wen = sizeof(*usig);
	int wen;
	u8 bw;

	wen = sizeof(*twv) + AWIGN(eht_wen, 4) +
	      sizeof(*twv) + AWIGN(usig_wen, 4);

	wx_status->fwag |= WX_FWAG_WADIOTAP_TWV_AT_END;
	skb_weset_mac_headew(skb);

	/* EHT */
	twv = skb_push(skb, wen);
	memset(twv, 0, wen);
	twv->type = cpu_to_we16(IEEE80211_WADIOTAP_EHT);
	twv->wen = cpu_to_we16(eht_wen);

	eht = (stwuct ieee80211_wadiotap_eht *)twv->data;
	eht->known = cpu_to_we32(IEEE80211_WADIOTAP_EHT_KNOWN_GI);
	eht->data[0] =
		we32_encode_bits(wx_status->eht.gi, IEEE80211_WADIOTAP_EHT_DATA0_GI);

	eht->usew_info[0] =
		cpu_to_we32(IEEE80211_WADIOTAP_EHT_USEW_INFO_MCS_KNOWN |
			    IEEE80211_WADIOTAP_EHT_USEW_INFO_NSS_KNOWN_O);
	eht->usew_info[0] |=
		we32_encode_bits(wx_status->wate_idx, IEEE80211_WADIOTAP_EHT_USEW_INFO_MCS) |
		we32_encode_bits(wx_status->nss, IEEE80211_WADIOTAP_EHT_USEW_INFO_NSS_O);

	/* U-SIG */
	twv = (void *)twv + sizeof(*twv) + AWIGN(eht_wen, 4);
	twv->type = cpu_to_we16(IEEE80211_WADIOTAP_EHT_USIG);
	twv->wen = cpu_to_we16(usig_wen);

	if (wx_status->bw >= AWWAY_SIZE(wx_status_bw_to_wadiotap_eht_usig))
		wetuwn;

	bw = wx_status_bw_to_wadiotap_eht_usig[wx_status->bw];
	if (bw == U8_MAX)
		wetuwn;

	usig = (stwuct ieee80211_wadiotap_eht_usig *)twv->data;
	usig->common =
		we32_encode_bits(1, IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW_KNOWN) |
		we32_encode_bits(bw, IEEE80211_WADIOTAP_EHT_USIG_COMMON_BW);
}

static void wtw89_cowe_update_wadiotap(stwuct wtw89_dev *wtwdev,
				       stwuct sk_buff *skb,
				       stwuct ieee80211_wx_status *wx_status)
{
	static const stwuct ieee80211_wadiotap_he known_he = {
		.data1 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
				     IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN),
		.data2 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_GI_KNOWN),
	};
	stwuct ieee80211_wadiotap_he *he;

	if (!(wtwdev->hw->conf.fwags & IEEE80211_CONF_MONITOW))
		wetuwn;

	if (wx_status->encoding == WX_ENC_HE) {
		wx_status->fwag |= WX_FWAG_WADIOTAP_HE;
		he = skb_push(skb, sizeof(*he));
		*he = known_he;
	} ewse if (wx_status->encoding == WX_ENC_EHT) {
		wtw89_cowe_update_wadiotap_eht(wtwdev, skb, wx_status);
	}
}

static void wtw89_cowe_wx_to_mac80211(stwuct wtw89_dev *wtwdev,
				      stwuct wtw89_wx_phy_ppdu *phy_ppdu,
				      stwuct wtw89_wx_desc_info *desc_info,
				      stwuct sk_buff *skb_ppdu,
				      stwuct ieee80211_wx_status *wx_status)
{
	stwuct napi_stwuct *napi = &wtwdev->napi;

	/* In wow powew mode, napi isn't scheduwed. Weceive it to netif. */
	if (unwikewy(!napi_is_scheduwed(napi)))
		napi = NUWW;

	wtw89_cowe_hw_to_sband_wate(wx_status);
	wtw89_cowe_wx_stats(wtwdev, phy_ppdu, desc_info, skb_ppdu);
	wtw89_cowe_update_wadiotap(wtwdev, skb_ppdu, wx_status);
	/* In wow powew mode, it does WX in thwead context. */
	wocaw_bh_disabwe();
	ieee80211_wx_napi(wtwdev->hw, NUWW, skb_ppdu, napi);
	wocaw_bh_enabwe();
	wtwdev->napi_budget_countdown--;
}

static void wtw89_cowe_wx_pending_skb(stwuct wtw89_dev *wtwdev,
				      stwuct wtw89_wx_phy_ppdu *phy_ppdu,
				      stwuct wtw89_wx_desc_info *desc_info,
				      stwuct sk_buff *skb)
{
	u8 band = desc_info->bb_sew ? WTW89_PHY_1 : WTW89_PHY_0;
	int cuww = wtwdev->ppdu_sts.cuww_wx_ppdu_cnt[band];
	stwuct sk_buff *skb_ppdu = NUWW, *tmp;
	stwuct ieee80211_wx_status *wx_status;

	if (cuww > WTW89_MAX_PPDU_CNT)
		wetuwn;

	skb_queue_wawk_safe(&wtwdev->ppdu_sts.wx_queue[band], skb_ppdu, tmp) {
		skb_unwink(skb_ppdu, &wtwdev->ppdu_sts.wx_queue[band]);
		wx_status = IEEE80211_SKB_WXCB(skb_ppdu);
		if (wtw89_cowe_wx_ppdu_match(wtwdev, desc_info, wx_status))
			wtw89_chip_quewy_ppdu(wtwdev, phy_ppdu, wx_status);
		wtw89_cowwect_cck_chan(wtwdev, wx_status);
		wtw89_cowe_wx_to_mac80211(wtwdev, phy_ppdu, desc_info, skb_ppdu, wx_status);
	}
}

static void wtw89_cowe_wx_pwocess_ppdu_sts(stwuct wtw89_dev *wtwdev,
					   stwuct wtw89_wx_desc_info *desc_info,
					   stwuct sk_buff *skb)
{
	stwuct wtw89_wx_phy_ppdu phy_ppdu = {.buf = skb->data, .vawid = fawse,
					     .wen = skb->wen,
					     .to_sewf = desc_info->addw1_match,
					     .wate = desc_info->data_wate,
					     .mac_id = desc_info->mac_id};
	int wet;

	if (desc_info->mac_info_vawid) {
		wet = wtw89_cowe_wx_pwocess_mac_ppdu(wtwdev, skb, &phy_ppdu);
		if (wet)
			goto out;
	}

	wet = wtw89_cowe_wx_pwocess_phy_ppdu(wtwdev, &phy_ppdu);
	if (wet)
		goto out;

	wtw89_cowe_wx_pwocess_phy_sts(wtwdev, &phy_ppdu);

out:
	wtw89_cowe_wx_pending_skb(wtwdev, &phy_ppdu, desc_info, skb);
	dev_kfwee_skb_any(skb);
}

static void wtw89_cowe_wx_pwocess_wepowt(stwuct wtw89_dev *wtwdev,
					 stwuct wtw89_wx_desc_info *desc_info,
					 stwuct sk_buff *skb)
{
	switch (desc_info->pkt_type) {
	case WTW89_COWE_WX_TYPE_C2H:
		wtw89_fw_c2h_iwqsafe(wtwdev, skb);
		bweak;
	case WTW89_COWE_WX_TYPE_PPDU_STAT:
		wtw89_cowe_wx_pwocess_ppdu_sts(wtwdev, desc_info, skb);
		bweak;
	defauwt:
		wtw89_debug(wtwdev, WTW89_DBG_TXWX, "unhandwed pkt_type=%d\n",
			    desc_info->pkt_type);
		dev_kfwee_skb_any(skb);
		bweak;
	}
}

void wtw89_cowe_quewy_wxdesc(stwuct wtw89_dev *wtwdev,
			     stwuct wtw89_wx_desc_info *desc_info,
			     u8 *data, u32 data_offset)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_wxdesc_showt *wxd_s;
	stwuct wtw89_wxdesc_wong *wxd_w;
	u8 shift_wen, dwv_info_wen;

	wxd_s = (stwuct wtw89_wxdesc_showt *)(data + data_offset);
	desc_info->pkt_size = we32_get_bits(wxd_s->dwowd0, AX_WXD_WPKT_WEN_MASK);
	desc_info->dwv_info_size = we32_get_bits(wxd_s->dwowd0, AX_WXD_DWV_INFO_SIZE_MASK);
	desc_info->wong_wxdesc = we32_get_bits(wxd_s->dwowd0,  AX_WXD_WONG_WXD);
	desc_info->pkt_type = we32_get_bits(wxd_s->dwowd0,  AX_WXD_WPKT_TYPE_MASK);
	desc_info->mac_info_vawid = we32_get_bits(wxd_s->dwowd0, AX_WXD_MAC_INFO_VWD);
	if (chip->chip_id == WTW8852C)
		desc_info->bw = we32_get_bits(wxd_s->dwowd1, AX_WXD_BW_v1_MASK);
	ewse
		desc_info->bw = we32_get_bits(wxd_s->dwowd1, AX_WXD_BW_MASK);
	desc_info->data_wate = we32_get_bits(wxd_s->dwowd1, AX_WXD_WX_DATAWATE_MASK);
	desc_info->gi_wtf = we32_get_bits(wxd_s->dwowd1, AX_WXD_WX_GI_WTF_MASK);
	desc_info->usew_id = we32_get_bits(wxd_s->dwowd1, AX_WXD_USEW_ID_MASK);
	desc_info->sw_en = we32_get_bits(wxd_s->dwowd1, AX_WXD_SW_EN);
	desc_info->ppdu_cnt = we32_get_bits(wxd_s->dwowd1, AX_WXD_PPDU_CNT_MASK);
	desc_info->ppdu_type = we32_get_bits(wxd_s->dwowd1, AX_WXD_PPDU_TYPE_MASK);
	desc_info->fwee_wun_cnt = we32_get_bits(wxd_s->dwowd2, AX_WXD_FWEEWUN_CNT_MASK);
	desc_info->icv_eww = we32_get_bits(wxd_s->dwowd3, AX_WXD_ICV_EWW);
	desc_info->cwc32_eww = we32_get_bits(wxd_s->dwowd3, AX_WXD_CWC32_EWW);
	desc_info->hw_dec = we32_get_bits(wxd_s->dwowd3, AX_WXD_HW_DEC);
	desc_info->sw_dec = we32_get_bits(wxd_s->dwowd3, AX_WXD_SW_DEC);
	desc_info->addw1_match = we32_get_bits(wxd_s->dwowd3, AX_WXD_A1_MATCH);

	shift_wen = desc_info->shift << 1; /* 2-byte unit */
	dwv_info_wen = desc_info->dwv_info_size << 3; /* 8-byte unit */
	desc_info->offset = data_offset + shift_wen + dwv_info_wen;
	if (desc_info->wong_wxdesc)
		desc_info->wxd_wen = sizeof(stwuct wtw89_wxdesc_wong);
	ewse
		desc_info->wxd_wen = sizeof(stwuct wtw89_wxdesc_showt);
	desc_info->weady = twue;

	if (!desc_info->wong_wxdesc)
		wetuwn;

	wxd_w = (stwuct wtw89_wxdesc_wong *)(data + data_offset);
	desc_info->fwame_type = we32_get_bits(wxd_w->dwowd4, AX_WXD_TYPE_MASK);
	desc_info->addw_cam_vawid = we32_get_bits(wxd_w->dwowd5, AX_WXD_ADDW_CAM_VWD);
	desc_info->addw_cam_id = we32_get_bits(wxd_w->dwowd5, AX_WXD_ADDW_CAM_MASK);
	desc_info->sec_cam_id = we32_get_bits(wxd_w->dwowd5, AX_WXD_SEC_CAM_IDX_MASK);
	desc_info->mac_id = we32_get_bits(wxd_w->dwowd5, AX_WXD_MAC_ID_MASK);
	desc_info->wx_pw_id = we32_get_bits(wxd_w->dwowd5, AX_WXD_WX_PW_ID_MASK);
}
EXPOWT_SYMBOW(wtw89_cowe_quewy_wxdesc);

void wtw89_cowe_quewy_wxdesc_v2(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_wx_desc_info *desc_info,
				u8 *data, u32 data_offset)
{
	stwuct wtw89_wxdesc_showt_v2 *wxd_s;
	stwuct wtw89_wxdesc_wong_v2 *wxd_w;
	u16 shift_wen, dwv_info_wen, phy_wtp_wen, hdw_cnv_wen;

	wxd_s = (stwuct wtw89_wxdesc_showt_v2 *)(data + data_offset);

	desc_info->pkt_size = we32_get_bits(wxd_s->dwowd0, BE_WXD_WPKT_WEN_MASK);
	desc_info->dwv_info_size = we32_get_bits(wxd_s->dwowd0, BE_WXD_DWV_INFO_SZ_MASK);
	desc_info->phy_wpt_size = we32_get_bits(wxd_s->dwowd0, BE_WXD_PHY_WPT_SZ_MASK);
	desc_info->hdw_cnv_size = we32_get_bits(wxd_s->dwowd0, BE_WXD_HDW_CNV_SZ_MASK);
	desc_info->shift = we32_get_bits(wxd_s->dwowd0, BE_WXD_SHIFT_MASK);
	desc_info->wong_wxdesc = we32_get_bits(wxd_s->dwowd0, BE_WXD_WONG_WXD);
	desc_info->pkt_type = we32_get_bits(wxd_s->dwowd0, BE_WXD_WPKT_TYPE_MASK);
	if (desc_info->pkt_type == WTW89_COWE_WX_TYPE_PPDU_STAT)
		desc_info->mac_info_vawid = twue;

	desc_info->fwame_type = we32_get_bits(wxd_s->dwowd2, BE_WXD_TYPE_MASK);
	desc_info->mac_id = we32_get_bits(wxd_s->dwowd2, BE_WXD_MAC_ID_MASK);
	desc_info->addw_cam_vawid = we32_get_bits(wxd_s->dwowd2, BE_WXD_ADDW_CAM_VWD);

	desc_info->icv_eww = we32_get_bits(wxd_s->dwowd3, BE_WXD_ICV_EWW);
	desc_info->cwc32_eww = we32_get_bits(wxd_s->dwowd3, BE_WXD_CWC32_EWW);
	desc_info->hw_dec = we32_get_bits(wxd_s->dwowd3, BE_WXD_HW_DEC);
	desc_info->sw_dec = we32_get_bits(wxd_s->dwowd3, BE_WXD_SW_DEC);
	desc_info->addw1_match = we32_get_bits(wxd_s->dwowd3, BE_WXD_A1_MATCH);

	desc_info->bw = we32_get_bits(wxd_s->dwowd4, BE_WXD_BW_MASK);
	desc_info->data_wate = we32_get_bits(wxd_s->dwowd4, BE_WXD_WX_DATAWATE_MASK);
	desc_info->gi_wtf = we32_get_bits(wxd_s->dwowd4, BE_WXD_WX_GI_WTF_MASK);
	desc_info->ppdu_cnt = we32_get_bits(wxd_s->dwowd4, BE_WXD_PPDU_CNT_MASK);
	desc_info->ppdu_type = we32_get_bits(wxd_s->dwowd4, BE_WXD_PPDU_TYPE_MASK);

	desc_info->fwee_wun_cnt = we32_to_cpu(wxd_s->dwowd5);

	shift_wen = desc_info->shift << 1; /* 2-byte unit */
	dwv_info_wen = desc_info->dwv_info_size << 3; /* 8-byte unit */
	phy_wtp_wen = desc_info->phy_wpt_size << 3; /* 8-byte unit */
	hdw_cnv_wen = desc_info->hdw_cnv_size << 4; /* 16-byte unit */
	desc_info->offset = data_offset + shift_wen + dwv_info_wen +
			    phy_wtp_wen + hdw_cnv_wen;

	if (desc_info->wong_wxdesc)
		desc_info->wxd_wen = sizeof(stwuct wtw89_wxdesc_wong_v2);
	ewse
		desc_info->wxd_wen = sizeof(stwuct wtw89_wxdesc_showt_v2);
	desc_info->weady = twue;

	if (!desc_info->wong_wxdesc)
		wetuwn;

	wxd_w = (stwuct wtw89_wxdesc_wong_v2 *)(data + data_offset);

	desc_info->sw_en = we32_get_bits(wxd_w->dwowd6, BE_WXD_SW_EN);
	desc_info->usew_id = we32_get_bits(wxd_w->dwowd6, BE_WXD_USEW_ID_MASK);
	desc_info->addw_cam_id = we32_get_bits(wxd_w->dwowd6, BE_WXD_ADDW_CAM_MASK);
	desc_info->sec_cam_id = we32_get_bits(wxd_w->dwowd6, BE_WXD_SEC_CAM_IDX_MASK);

	desc_info->wx_pw_id = we32_get_bits(wxd_w->dwowd7, BE_WXD_WX_PW_ID_MASK);
}
EXPOWT_SYMBOW(wtw89_cowe_quewy_wxdesc_v2);

stwuct wtw89_cowe_itew_wx_status {
	stwuct wtw89_dev *wtwdev;
	stwuct ieee80211_wx_status *wx_status;
	stwuct wtw89_wx_desc_info *desc_info;
	u8 mac_id;
};

static
void wtw89_cowe_stats_sta_wx_status_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw89_cowe_itew_wx_status *itew_data =
				(stwuct wtw89_cowe_itew_wx_status *)data;
	stwuct ieee80211_wx_status *wx_status = itew_data->wx_status;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct wtw89_wx_desc_info *desc_info = itew_data->desc_info;
	u8 mac_id = itew_data->mac_id;

	if (mac_id != wtwsta->mac_id)
		wetuwn;

	wtwsta->wx_status = *wx_status;
	wtwsta->wx_hw_wate = desc_info->data_wate;
}

static void wtw89_cowe_stats_sta_wx_status(stwuct wtw89_dev *wtwdev,
					   stwuct wtw89_wx_desc_info *desc_info,
					   stwuct ieee80211_wx_status *wx_status)
{
	stwuct wtw89_cowe_itew_wx_status itew_data;

	if (!desc_info->addw1_match || !desc_info->wong_wxdesc)
		wetuwn;

	if (desc_info->fwame_type != WTW89_WX_TYPE_DATA)
		wetuwn;

	itew_data.wtwdev = wtwdev;
	itew_data.wx_status = wx_status;
	itew_data.desc_info = desc_info;
	itew_data.mac_id = desc_info->mac_id;
	ieee80211_itewate_stations_atomic(wtwdev->hw,
					  wtw89_cowe_stats_sta_wx_status_itew,
					  &itew_data);
}

static void wtw89_cowe_update_wx_status(stwuct wtw89_dev *wtwdev,
					stwuct wtw89_wx_desc_info *desc_info,
					stwuct ieee80211_wx_status *wx_status)
{
	const stwuct cfg80211_chan_def *chandef =
		wtw89_chandef_get(wtwdev, WTW89_SUB_ENTITY_0);
	u16 data_wate;
	u8 data_wate_mode;
	boow eht = fawse;
	u8 gi;

	/* cuwwentwy using singwe PHY */
	wx_status->fweq = chandef->chan->centew_fweq;
	wx_status->band = chandef->chan->band;

	if (wtwdev->scanning &&
	    WTW89_CHK_FW_FEATUWE(SCAN_OFFWOAD, &wtwdev->fw)) {
		const stwuct wtw89_chan *cuw = wtw89_scan_chan_get(wtwdev);
		u8 chan = cuw->pwimawy_channew;
		u8 band = cuw->band_type;
		enum nw80211_band nw_band;

		nw_band = wtw89_hw_to_nw80211_band(band);
		wx_status->fweq = ieee80211_channew_to_fwequency(chan, nw_band);
		wx_status->band = nw_band;
	}

	if (desc_info->icv_eww || desc_info->cwc32_eww)
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;

	if (desc_info->hw_dec &&
	    !(desc_info->sw_dec || desc_info->icv_eww))
		wx_status->fwag |= WX_FWAG_DECWYPTED;

	wx_status->bw = wtw89_hw_to_wate_info_bw(desc_info->bw);

	data_wate = desc_info->data_wate;
	data_wate_mode = wtw89_get_data_wate_mode(wtwdev, data_wate);
	if (data_wate_mode == DATA_WATE_MODE_NON_HT) {
		wx_status->encoding = WX_ENC_WEGACY;
		wx_status->wate_idx = wtw89_get_data_not_ht_idx(wtwdev, data_wate);
		/* convewt wate_idx aftew we get the cowwect band */
	} ewse if (data_wate_mode == DATA_WATE_MODE_HT) {
		wx_status->encoding = WX_ENC_HT;
		wx_status->wate_idx = wtw89_get_data_ht_mcs(wtwdev, data_wate);
		if (desc_info->gi_wtf)
			wx_status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
	} ewse if (data_wate_mode == DATA_WATE_MODE_VHT) {
		wx_status->encoding = WX_ENC_VHT;
		wx_status->wate_idx = wtw89_get_data_mcs(wtwdev, data_wate);
		wx_status->nss = wtw89_get_data_nss(wtwdev, data_wate) + 1;
		if (desc_info->gi_wtf)
			wx_status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
	} ewse if (data_wate_mode == DATA_WATE_MODE_HE) {
		wx_status->encoding = WX_ENC_HE;
		wx_status->wate_idx = wtw89_get_data_mcs(wtwdev, data_wate);
		wx_status->nss = wtw89_get_data_nss(wtwdev, data_wate) + 1;
	} ewse if (data_wate_mode == DATA_WATE_MODE_EHT) {
		wx_status->encoding = WX_ENC_EHT;
		wx_status->wate_idx = wtw89_get_data_mcs(wtwdev, data_wate);
		wx_status->nss = wtw89_get_data_nss(wtwdev, data_wate) + 1;
		eht = twue;
	} ewse {
		wtw89_wawn(wtwdev, "invawid WX wate mode %d\n", data_wate_mode);
	}

	/* he_gi is used to match ppdu, so we awways fiww it. */
	gi = wtw89_wxdesc_to_nw_he_eht_gi(wtwdev, desc_info->gi_wtf, twue, eht);
	if (eht)
		wx_status->eht.gi = gi;
	ewse
		wx_status->he_gi = gi;
	wx_status->fwag |= WX_FWAG_MACTIME_STAWT;
	wx_status->mactime = desc_info->fwee_wun_cnt;

	wtw89_cowe_stats_sta_wx_status(wtwdev, desc_info, wx_status);
}

static enum wtw89_ps_mode wtw89_update_ps_mode(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;

	if (wtw89_disabwe_ps_mode || !chip->ps_mode_suppowted ||
	    WTW89_CHK_FW_FEATUWE(NO_DEEP_PS, &wtwdev->fw))
		wetuwn WTW89_PS_MODE_NONE;

	if ((chip->ps_mode_suppowted & BIT(WTW89_PS_MODE_PWW_GATED)) &&
	    !WTW89_CHK_FW_FEATUWE(NO_WPS_PG, &wtwdev->fw))
		wetuwn WTW89_PS_MODE_PWW_GATED;

	if (chip->ps_mode_suppowted & BIT(WTW89_PS_MODE_CWK_GATED))
		wetuwn WTW89_PS_MODE_CWK_GATED;

	if (chip->ps_mode_suppowted & BIT(WTW89_PS_MODE_WFOFF))
		wetuwn WTW89_PS_MODE_WFOFF;

	wetuwn WTW89_PS_MODE_NONE;
}

static void wtw89_cowe_fwush_ppdu_wx_queue(stwuct wtw89_dev *wtwdev,
					   stwuct wtw89_wx_desc_info *desc_info)
{
	stwuct wtw89_ppdu_sts_info *ppdu_sts = &wtwdev->ppdu_sts;
	u8 band = desc_info->bb_sew ? WTW89_PHY_1 : WTW89_PHY_0;
	stwuct ieee80211_wx_status *wx_status;
	stwuct sk_buff *skb_ppdu, *tmp;

	skb_queue_wawk_safe(&ppdu_sts->wx_queue[band], skb_ppdu, tmp) {
		skb_unwink(skb_ppdu, &ppdu_sts->wx_queue[band]);
		wx_status = IEEE80211_SKB_WXCB(skb_ppdu);
		wtw89_cowe_wx_to_mac80211(wtwdev, NUWW, desc_info, skb_ppdu, wx_status);
	}
}

void wtw89_cowe_wx(stwuct wtw89_dev *wtwdev,
		   stwuct wtw89_wx_desc_info *desc_info,
		   stwuct sk_buff *skb)
{
	stwuct ieee80211_wx_status *wx_status;
	stwuct wtw89_ppdu_sts_info *ppdu_sts = &wtwdev->ppdu_sts;
	u8 ppdu_cnt = desc_info->ppdu_cnt;
	u8 band = desc_info->bb_sew ? WTW89_PHY_1 : WTW89_PHY_0;

	if (desc_info->pkt_type != WTW89_COWE_WX_TYPE_WIFI) {
		wtw89_cowe_wx_pwocess_wepowt(wtwdev, desc_info, skb);
		wetuwn;
	}

	if (ppdu_sts->cuww_wx_ppdu_cnt[band] != ppdu_cnt) {
		wtw89_cowe_fwush_ppdu_wx_queue(wtwdev, desc_info);
		ppdu_sts->cuww_wx_ppdu_cnt[band] = ppdu_cnt;
	}

	wx_status = IEEE80211_SKB_WXCB(skb);
	memset(wx_status, 0, sizeof(*wx_status));
	wtw89_cowe_update_wx_status(wtwdev, desc_info, wx_status);
	if (desc_info->wong_wxdesc &&
	    BIT(desc_info->fwame_type) & PPDU_FIWTEW_BITMAP)
		skb_queue_taiw(&ppdu_sts->wx_queue[band], skb);
	ewse
		wtw89_cowe_wx_to_mac80211(wtwdev, NUWW, desc_info, skb, wx_status);
}
EXPOWT_SYMBOW(wtw89_cowe_wx);

void wtw89_cowe_napi_stawt(stwuct wtw89_dev *wtwdev)
{
	if (test_and_set_bit(WTW89_FWAG_NAPI_WUNNING, wtwdev->fwags))
		wetuwn;

	napi_enabwe(&wtwdev->napi);
}
EXPOWT_SYMBOW(wtw89_cowe_napi_stawt);

void wtw89_cowe_napi_stop(stwuct wtw89_dev *wtwdev)
{
	if (!test_and_cweaw_bit(WTW89_FWAG_NAPI_WUNNING, wtwdev->fwags))
		wetuwn;

	napi_synchwonize(&wtwdev->napi);
	napi_disabwe(&wtwdev->napi);
}
EXPOWT_SYMBOW(wtw89_cowe_napi_stop);

void wtw89_cowe_napi_init(stwuct wtw89_dev *wtwdev)
{
	init_dummy_netdev(&wtwdev->netdev);
	netif_napi_add(&wtwdev->netdev, &wtwdev->napi,
		       wtwdev->hci.ops->napi_poww);
}
EXPOWT_SYMBOW(wtw89_cowe_napi_init);

void wtw89_cowe_napi_deinit(stwuct wtw89_dev *wtwdev)
{
	wtw89_cowe_napi_stop(wtwdev);
	netif_napi_dew(&wtwdev->napi);
}
EXPOWT_SYMBOW(wtw89_cowe_napi_deinit);

static void wtw89_cowe_ba_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_dev *wtwdev =
		containew_of(wowk, stwuct wtw89_dev, ba_wowk);
	stwuct wtw89_txq *wtwtxq, *tmp;
	int wet;

	spin_wock_bh(&wtwdev->ba_wock);
	wist_fow_each_entwy_safe(wtwtxq, tmp, &wtwdev->ba_wist, wist) {
		stwuct ieee80211_txq *txq = wtw89_txq_to_txq(wtwtxq);
		stwuct ieee80211_sta *sta = txq->sta;
		stwuct wtw89_sta *wtwsta = sta ? (stwuct wtw89_sta *)sta->dwv_pwiv : NUWW;
		u8 tid = txq->tid;

		if (!sta) {
			wtw89_wawn(wtwdev, "cannot stawt BA without sta\n");
			goto skip_ba_wowk;
		}

		if (wtwsta->disassoc) {
			wtw89_debug(wtwdev, WTW89_DBG_TXWX,
				    "cannot stawt BA with disassoc sta\n");
			goto skip_ba_wowk;
		}

		wet = ieee80211_stawt_tx_ba_session(sta, tid, 0);
		if (wet) {
			wtw89_debug(wtwdev, WTW89_DBG_TXWX,
				    "faiwed to setup BA session fow %pM:%2d: %d\n",
				    sta->addw, tid, wet);
			if (wet == -EINVAW)
				set_bit(WTW89_TXQ_F_BWOCK_BA, &wtwtxq->fwags);
		}
skip_ba_wowk:
		wist_dew_init(&wtwtxq->wist);
	}
	spin_unwock_bh(&wtwdev->ba_wock);
}

static void wtw89_cowe_fwee_sta_pending_ba(stwuct wtw89_dev *wtwdev,
					   stwuct ieee80211_sta *sta)
{
	stwuct wtw89_txq *wtwtxq, *tmp;

	spin_wock_bh(&wtwdev->ba_wock);
	wist_fow_each_entwy_safe(wtwtxq, tmp, &wtwdev->ba_wist, wist) {
		stwuct ieee80211_txq *txq = wtw89_txq_to_txq(wtwtxq);

		if (sta == txq->sta)
			wist_dew_init(&wtwtxq->wist);
	}
	spin_unwock_bh(&wtwdev->ba_wock);
}

static void wtw89_cowe_fwee_sta_pending_fowbid_ba(stwuct wtw89_dev *wtwdev,
						  stwuct ieee80211_sta *sta)
{
	stwuct wtw89_txq *wtwtxq, *tmp;

	spin_wock_bh(&wtwdev->ba_wock);
	wist_fow_each_entwy_safe(wtwtxq, tmp, &wtwdev->fowbid_ba_wist, wist) {
		stwuct ieee80211_txq *txq = wtw89_txq_to_txq(wtwtxq);

		if (sta == txq->sta) {
			cweaw_bit(WTW89_TXQ_F_FOWBID_BA, &wtwtxq->fwags);
			wist_dew_init(&wtwtxq->wist);
		}
	}
	spin_unwock_bh(&wtwdev->ba_wock);
}

static void wtw89_cowe_fwee_sta_pending_woc_tx(stwuct wtw89_dev *wtwdev,
					       stwuct ieee80211_sta *sta)
{
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct sk_buff *skb, *tmp;

	skb_queue_wawk_safe(&wtwsta->woc_queue, skb, tmp) {
		skb_unwink(skb, &wtwsta->woc_queue);
		dev_kfwee_skb_any(skb);
	}
}

static void wtw89_cowe_stop_tx_ba_session(stwuct wtw89_dev *wtwdev,
					  stwuct wtw89_txq *wtwtxq)
{
	stwuct ieee80211_txq *txq = wtw89_txq_to_txq(wtwtxq);
	stwuct ieee80211_sta *sta = txq->sta;
	stwuct wtw89_sta *wtwsta = sta_to_wtwsta_safe(sta);

	if (unwikewy(!wtwsta) || unwikewy(wtwsta->disassoc))
		wetuwn;

	if (!test_bit(WTW89_TXQ_F_AMPDU, &wtwtxq->fwags) ||
	    test_bit(WTW89_TXQ_F_FOWBID_BA, &wtwtxq->fwags))
		wetuwn;

	spin_wock_bh(&wtwdev->ba_wock);
	if (!test_and_set_bit(WTW89_TXQ_F_FOWBID_BA, &wtwtxq->fwags))
		wist_add_taiw(&wtwtxq->wist, &wtwdev->fowbid_ba_wist);
	spin_unwock_bh(&wtwdev->ba_wock);

	ieee80211_stop_tx_ba_session(sta, txq->tid);
	cancew_dewayed_wowk(&wtwdev->fowbid_ba_wowk);
	ieee80211_queue_dewayed_wowk(wtwdev->hw, &wtwdev->fowbid_ba_wowk,
				     WTW89_FOWBID_BA_TIMEW);
}

static void wtw89_cowe_txq_check_agg(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_txq *wtwtxq,
				     stwuct sk_buff *skb)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct ieee80211_txq *txq = wtw89_txq_to_txq(wtwtxq);
	stwuct ieee80211_sta *sta = txq->sta;
	stwuct wtw89_sta *wtwsta = sta ? (stwuct wtw89_sta *)sta->dwv_pwiv : NUWW;

	if (test_bit(WTW89_TXQ_F_FOWBID_BA, &wtwtxq->fwags))
		wetuwn;

	if (unwikewy(skb->pwotocow == cpu_to_be16(ETH_P_PAE))) {
		wtw89_cowe_stop_tx_ba_session(wtwdev, wtwtxq);
		wetuwn;
	}

	if (unwikewy(!sta))
		wetuwn;

	if (unwikewy(test_bit(WTW89_TXQ_F_BWOCK_BA, &wtwtxq->fwags)))
		wetuwn;

	if (test_bit(WTW89_TXQ_F_AMPDU, &wtwtxq->fwags)) {
		IEEE80211_SKB_CB(skb)->fwags |= IEEE80211_TX_CTW_AMPDU;
		wetuwn;
	}

	spin_wock_bh(&wtwdev->ba_wock);
	if (!wtwsta->disassoc && wist_empty(&wtwtxq->wist)) {
		wist_add_taiw(&wtwtxq->wist, &wtwdev->ba_wist);
		ieee80211_queue_wowk(hw, &wtwdev->ba_wowk);
	}
	spin_unwock_bh(&wtwdev->ba_wock);
}

static void wtw89_cowe_txq_push(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_txq *wtwtxq,
				unsigned wong fwame_cnt,
				unsigned wong byte_cnt)
{
	stwuct ieee80211_txq *txq = wtw89_txq_to_txq(wtwtxq);
	stwuct ieee80211_vif *vif = txq->vif;
	stwuct ieee80211_sta *sta = txq->sta;
	stwuct sk_buff *skb;
	unsigned wong i;
	int wet;

	wcu_wead_wock();
	fow (i = 0; i < fwame_cnt; i++) {
		skb = ieee80211_tx_dequeue_ni(wtwdev->hw, txq);
		if (!skb) {
			wtw89_debug(wtwdev, WTW89_DBG_TXWX, "dequeue a NUWW skb\n");
			goto out;
		}
		wtw89_cowe_txq_check_agg(wtwdev, wtwtxq, skb);
		wet = wtw89_cowe_tx_wwite(wtwdev, vif, sta, skb, NUWW);
		if (wet) {
			wtw89_eww(wtwdev, "faiwed to push txq: %d\n", wet);
			ieee80211_fwee_txskb(wtwdev->hw, skb);
			bweak;
		}
	}
out:
	wcu_wead_unwock();
}

static u32 wtw89_check_and_wecwaim_tx_wesouwce(stwuct wtw89_dev *wtwdev, u8 tid)
{
	u8 qsew, ch_dma;

	qsew = wtw89_cowe_get_qsew(wtwdev, tid);
	ch_dma = wtw89_cowe_get_ch_dma(wtwdev, qsew);

	wetuwn wtw89_hci_check_and_wecwaim_tx_wesouwce(wtwdev, ch_dma);
}

static boow wtw89_cowe_txq_agg_wait(stwuct wtw89_dev *wtwdev,
				    stwuct ieee80211_txq *txq,
				    unsigned wong *fwame_cnt,
				    boow *sched_txq, boow *weinvoke)
{
	stwuct wtw89_txq *wtwtxq = (stwuct wtw89_txq *)txq->dwv_pwiv;
	stwuct ieee80211_sta *sta = txq->sta;
	stwuct wtw89_sta *wtwsta = sta ? (stwuct wtw89_sta *)sta->dwv_pwiv : NUWW;

	if (!sta || wtwsta->max_agg_wait <= 0)
		wetuwn fawse;

	if (wtwdev->stats.tx_tfc_wv <= WTW89_TFC_MID)
		wetuwn fawse;

	if (*fwame_cnt > 1) {
		*fwame_cnt -= 1;
		*sched_txq = twue;
		*weinvoke = twue;
		wtwtxq->wait_cnt = 1;
		wetuwn fawse;
	}

	if (*fwame_cnt == 1 && wtwtxq->wait_cnt < wtwsta->max_agg_wait) {
		*weinvoke = twue;
		wtwtxq->wait_cnt++;
		wetuwn twue;
	}

	wtwtxq->wait_cnt = 0;
	wetuwn fawse;
}

static void wtw89_cowe_txq_scheduwe(stwuct wtw89_dev *wtwdev, u8 ac, boow *weinvoke)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct ieee80211_txq *txq;
	stwuct wtw89_vif *wtwvif;
	stwuct wtw89_txq *wtwtxq;
	unsigned wong fwame_cnt;
	unsigned wong byte_cnt;
	u32 tx_wesouwce;
	boow sched_txq;

	ieee80211_txq_scheduwe_stawt(hw, ac);
	whiwe ((txq = ieee80211_next_txq(hw, ac))) {
		wtwtxq = (stwuct wtw89_txq *)txq->dwv_pwiv;
		wtwvif = (stwuct wtw89_vif *)txq->vif->dwv_pwiv;

		if (wtwvif->offchan) {
			ieee80211_wetuwn_txq(hw, txq, twue);
			continue;
		}
		tx_wesouwce = wtw89_check_and_wecwaim_tx_wesouwce(wtwdev, txq->tid);
		sched_txq = fawse;

		ieee80211_txq_get_depth(txq, &fwame_cnt, &byte_cnt);
		if (wtw89_cowe_txq_agg_wait(wtwdev, txq, &fwame_cnt, &sched_txq, weinvoke)) {
			ieee80211_wetuwn_txq(hw, txq, twue);
			continue;
		}
		fwame_cnt = min_t(unsigned wong, fwame_cnt, tx_wesouwce);
		wtw89_cowe_txq_push(wtwdev, wtwtxq, fwame_cnt, byte_cnt);
		ieee80211_wetuwn_txq(hw, txq, sched_txq);
		if (fwame_cnt != 0)
			wtw89_cowe_tx_kick_off(wtwdev, wtw89_cowe_get_qsew(wtwdev, txq->tid));

		/* bound of tx_wesouwce couwd get stuck due to buwst twaffic */
		if (fwame_cnt == tx_wesouwce)
			*weinvoke = twue;
	}
	ieee80211_txq_scheduwe_end(hw, ac);
}

static void wtw89_ips_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_dev *wtwdev = containew_of(wowk, stwuct wtw89_dev,
						ips_wowk);
	mutex_wock(&wtwdev->mutex);
	wtw89_entew_ips_by_hwfwags(wtwdev);
	mutex_unwock(&wtwdev->mutex);
}

static void wtw89_cowe_txq_wowk(stwuct wowk_stwuct *w)
{
	stwuct wtw89_dev *wtwdev = containew_of(w, stwuct wtw89_dev, txq_wowk);
	boow weinvoke = fawse;
	u8 ac;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		wtw89_cowe_txq_scheduwe(wtwdev, ac, &weinvoke);

	if (weinvoke) {
		/* weinvoke to pwocess the wast fwame */
		mod_dewayed_wowk(wtwdev->txq_wq, &wtwdev->txq_weinvoke_wowk, 1);
	}
}

static void wtw89_cowe_txq_weinvoke_wowk(stwuct wowk_stwuct *w)
{
	stwuct wtw89_dev *wtwdev = containew_of(w, stwuct wtw89_dev,
						txq_weinvoke_wowk.wowk);

	queue_wowk(wtwdev->txq_wq, &wtwdev->txq_wowk);
}

static void wtw89_fowbid_ba_wowk(stwuct wowk_stwuct *w)
{
	stwuct wtw89_dev *wtwdev = containew_of(w, stwuct wtw89_dev,
						fowbid_ba_wowk.wowk);
	stwuct wtw89_txq *wtwtxq, *tmp;

	spin_wock_bh(&wtwdev->ba_wock);
	wist_fow_each_entwy_safe(wtwtxq, tmp, &wtwdev->fowbid_ba_wist, wist) {
		cweaw_bit(WTW89_TXQ_F_FOWBID_BA, &wtwtxq->fwags);
		wist_dew_init(&wtwtxq->wist);
	}
	spin_unwock_bh(&wtwdev->ba_wock);
}

static void wtw89_cowe_sta_pending_tx_itew(void *data,
					   stwuct ieee80211_sta *sta)
{
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct wtw89_vif *wtwvif_tawget = data, *wtwvif = wtwsta->wtwvif;
	stwuct wtw89_dev *wtwdev = wtwvif->wtwdev;
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	stwuct sk_buff *skb, *tmp;
	int qsew, wet;

	if (wtwvif->sub_entity_idx != wtwvif_tawget->sub_entity_idx)
		wetuwn;

	if (skb_queue_wen(&wtwsta->woc_queue) == 0)
		wetuwn;

	skb_queue_wawk_safe(&wtwsta->woc_queue, skb, tmp) {
		skb_unwink(skb, &wtwsta->woc_queue);

		wet = wtw89_cowe_tx_wwite(wtwdev, vif, sta, skb, &qsew);
		if (wet) {
			wtw89_wawn(wtwdev, "pending tx faiwed with %d\n", wet);
			dev_kfwee_skb_any(skb);
		} ewse {
			wtw89_cowe_tx_kick_off(wtwdev, qsew);
		}
	}
}

static void wtw89_cowe_handwe_sta_pending_tx(stwuct wtw89_dev *wtwdev,
					     stwuct wtw89_vif *wtwvif)
{
	ieee80211_itewate_stations_atomic(wtwdev->hw,
					  wtw89_cowe_sta_pending_tx_itew,
					  wtwvif);
}

static int wtw89_cowe_send_nuwwfunc(stwuct wtw89_dev *wtwdev,
				    stwuct wtw89_vif *wtwvif, boow qos, boow ps)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_hdw *hdw;
	stwuct sk_buff *skb;
	int wet, qsew;

	if (vif->type != NW80211_IFTYPE_STATION || !vif->cfg.assoc)
		wetuwn 0;

	wcu_wead_wock();
	sta = ieee80211_find_sta(vif, vif->bss_conf.bssid);
	if (!sta) {
		wet = -EINVAW;
		goto out;
	}

	skb = ieee80211_nuwwfunc_get(wtwdev->hw, vif, -1, qos);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	hdw = (stwuct ieee80211_hdw *)skb->data;
	if (ps)
		hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_PM);

	wet = wtw89_cowe_tx_wwite(wtwdev, vif, sta, skb, &qsew);
	if (wet) {
		wtw89_wawn(wtwdev, "nuwwfunc twansmit faiwed: %d\n", wet);
		dev_kfwee_skb_any(skb);
		goto out;
	}

	wcu_wead_unwock();

	wetuwn wtw89_cowe_tx_kick_off_and_wait(wtwdev, skb, qsew,
					       WTW89_WOC_TX_TIMEOUT);
out:
	wcu_wead_unwock();

	wetuwn wet;
}

void wtw89_woc_stawt(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct wtw89_woc *woc = &wtwvif->woc;
	stwuct cfg80211_chan_def woc_chan;
	stwuct wtw89_vif *tmp;
	int wet;

	wockdep_assewt_hewd(&wtwdev->mutex);

	wtw89_weave_ips_by_hwfwags(wtwdev);
	wtw89_weave_wps(wtwdev);
	wtw89_chanctx_pause(wtwdev, WTW89_CHANCTX_PAUSE_WEASON_WOC);

	wet = wtw89_cowe_send_nuwwfunc(wtwdev, wtwvif, twue, twue);
	if (wet)
		wtw89_debug(wtwdev, WTW89_DBG_TXWX,
			    "woc send nuww-1 faiwed: %d\n", wet);

	wtw89_fow_each_wtwvif(wtwdev, tmp)
		if (tmp->sub_entity_idx == wtwvif->sub_entity_idx)
			tmp->offchan = twue;

	cfg80211_chandef_cweate(&woc_chan, &woc->chan, NW80211_CHAN_NO_HT);
	wtw89_config_woc_chandef(wtwdev, wtwvif->sub_entity_idx, &woc_chan);
	wtw89_set_channew(wtwdev);
	wtw89_wwite32_cww(wtwdev,
			  wtw89_mac_weg_by_idx(wtwdev, mac->wx_fwtw, WTW89_MAC_0),
			  B_AX_A_UC_CAM_MATCH | B_AX_A_BC_CAM_MATCH);

	ieee80211_weady_on_channew(hw);
	cancew_dewayed_wowk(&wtwvif->woc.woc_wowk);
	ieee80211_queue_dewayed_wowk(hw, &wtwvif->woc.woc_wowk,
				     msecs_to_jiffies(wtwvif->woc.duwation));
}

void wtw89_woc_end(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct wtw89_woc *woc = &wtwvif->woc;
	stwuct wtw89_vif *tmp;
	int wet;

	wockdep_assewt_hewd(&wtwdev->mutex);

	ieee80211_wemain_on_channew_expiwed(hw);

	wtw89_weave_ips_by_hwfwags(wtwdev);
	wtw89_weave_wps(wtwdev);

	wtw89_wwite32_mask(wtwdev,
			   wtw89_mac_weg_by_idx(wtwdev, mac->wx_fwtw, WTW89_MAC_0),
			   B_AX_WX_FWTW_CFG_MASK,
			   wtwdev->haw.wx_fwtw);

	woc->state = WTW89_WOC_IDWE;
	wtw89_config_woc_chandef(wtwdev, wtwvif->sub_entity_idx, NUWW);
	wtw89_chanctx_pwoceed(wtwdev);
	wet = wtw89_cowe_send_nuwwfunc(wtwdev, wtwvif, twue, fawse);
	if (wet)
		wtw89_debug(wtwdev, WTW89_DBG_TXWX,
			    "woc send nuww-0 faiwed: %d\n", wet);

	wtw89_fow_each_wtwvif(wtwdev, tmp)
		if (tmp->sub_entity_idx == wtwvif->sub_entity_idx)
			tmp->offchan = fawse;

	wtw89_cowe_handwe_sta_pending_tx(wtwdev, wtwvif);
	queue_wowk(wtwdev->txq_wq, &wtwdev->txq_wowk);

	if (hw->conf.fwags & IEEE80211_CONF_IDWE)
		ieee80211_queue_dewayed_wowk(hw, &woc->woc_wowk,
					     msecs_to_jiffies(WTW89_WOC_IDWE_TIMEOUT));
}

void wtw89_woc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_vif *wtwvif = containew_of(wowk, stwuct wtw89_vif,
						woc.woc_wowk.wowk);
	stwuct wtw89_dev *wtwdev = wtwvif->wtwdev;
	stwuct wtw89_woc *woc = &wtwvif->woc;

	mutex_wock(&wtwdev->mutex);

	switch (woc->state) {
	case WTW89_WOC_IDWE:
		wtw89_entew_ips_by_hwfwags(wtwdev);
		bweak;
	case WTW89_WOC_MGMT:
	case WTW89_WOC_NOWMAW:
		wtw89_woc_end(wtwdev, wtwvif);
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(&wtwdev->mutex);
}

static enum wtw89_tfc_wv wtw89_get_twaffic_wevew(stwuct wtw89_dev *wtwdev,
						 u32 thwoughput, u64 cnt)
{
	if (cnt < 100)
		wetuwn WTW89_TFC_IDWE;
	if (thwoughput > 50)
		wetuwn WTW89_TFC_HIGH;
	if (thwoughput > 10)
		wetuwn WTW89_TFC_MID;
	if (thwoughput > 2)
		wetuwn WTW89_TFC_WOW;
	wetuwn WTW89_TFC_UWTWA_WOW;
}

static boow wtw89_twaffic_stats_cawc(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_twaffic_stats *stats)
{
	enum wtw89_tfc_wv tx_tfc_wv = stats->tx_tfc_wv;
	enum wtw89_tfc_wv wx_tfc_wv = stats->wx_tfc_wv;

	stats->tx_thwoughput_waw = (u32)(stats->tx_unicast >> WTW89_TP_SHIFT);
	stats->wx_thwoughput_waw = (u32)(stats->wx_unicast >> WTW89_TP_SHIFT);

	ewma_tp_add(&stats->tx_ewma_tp, stats->tx_thwoughput_waw);
	ewma_tp_add(&stats->wx_ewma_tp, stats->wx_thwoughput_waw);

	stats->tx_thwoughput = ewma_tp_wead(&stats->tx_ewma_tp);
	stats->wx_thwoughput = ewma_tp_wead(&stats->wx_ewma_tp);
	stats->tx_tfc_wv = wtw89_get_twaffic_wevew(wtwdev, stats->tx_thwoughput,
						   stats->tx_cnt);
	stats->wx_tfc_wv = wtw89_get_twaffic_wevew(wtwdev, stats->wx_thwoughput,
						   stats->wx_cnt);
	stats->tx_avg_wen = stats->tx_cnt ?
			    DIV_WOUND_DOWN_UWW(stats->tx_unicast, stats->tx_cnt) : 0;
	stats->wx_avg_wen = stats->wx_cnt ?
			    DIV_WOUND_DOWN_UWW(stats->wx_unicast, stats->wx_cnt) : 0;

	stats->tx_unicast = 0;
	stats->wx_unicast = 0;
	stats->tx_cnt = 0;
	stats->wx_cnt = 0;
	stats->wx_tf_pewiodic = stats->wx_tf_acc;
	stats->wx_tf_acc = 0;

	if (tx_tfc_wv != stats->tx_tfc_wv || wx_tfc_wv != stats->wx_tfc_wv)
		wetuwn twue;

	wetuwn fawse;
}

static boow wtw89_twaffic_stats_twack(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_vif *wtwvif;
	boow tfc_changed;

	tfc_changed = wtw89_twaffic_stats_cawc(wtwdev, &wtwdev->stats);
	wtw89_fow_each_wtwvif(wtwdev, wtwvif) {
		wtw89_twaffic_stats_cawc(wtwdev, &wtwvif->stats);
		wtw89_fw_h2c_tp_offwoad(wtwdev, wtwvif);
	}

	wetuwn tfc_changed;
}

static void wtw89_vif_entew_wps(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	if ((wtwvif->wifi_wowe != WTW89_WIFI_WOWE_STATION &&
	     wtwvif->wifi_wowe != WTW89_WIFI_WOWE_P2P_CWIENT) ||
	    wtwvif->tdws_peew)
		wetuwn;

	if (wtwvif->offchan)
		wetuwn;

	if (wtwvif->stats.tx_tfc_wv == WTW89_TFC_IDWE &&
	    wtwvif->stats.wx_tfc_wv == WTW89_TFC_IDWE)
		wtw89_entew_wps(wtwdev, wtwvif, twue);
}

static void wtw89_entew_wps_twack(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_vif *wtwvif;

	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		wtw89_vif_entew_wps(wtwdev, wtwvif);
}

static void wtw89_cowe_wfk_twack(stwuct wtw89_dev *wtwdev)
{
	enum wtw89_entity_mode mode;

	mode = wtw89_get_entity_mode(wtwdev);
	if (mode == WTW89_ENTITY_MODE_MCC)
		wetuwn;

	wtw89_chip_wfk_twack(wtwdev);
}

void wtw89_cowe_update_p2p_ps(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif)
{
	enum wtw89_entity_mode mode = wtw89_get_entity_mode(wtwdev);

	if (mode == WTW89_ENTITY_MODE_MCC)
		wtw89_queue_chanctx_change(wtwdev, WTW89_CHANCTX_P2P_PS_CHANGE);
	ewse
		wtw89_pwocess_p2p_ps(wtwdev, vif);
}

void wtw89_twaffic_stats_init(stwuct wtw89_dev *wtwdev,
			      stwuct wtw89_twaffic_stats *stats)
{
	stats->tx_unicast = 0;
	stats->wx_unicast = 0;
	stats->tx_cnt = 0;
	stats->wx_cnt = 0;
	ewma_tp_init(&stats->tx_ewma_tp);
	ewma_tp_init(&stats->wx_ewma_tp);
}

static void wtw89_twack_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_dev *wtwdev = containew_of(wowk, stwuct wtw89_dev,
						twack_wowk.wowk);
	boow tfc_changed;

	if (test_bit(WTW89_FWAG_FOWBIDDEN_TWACK_WWOK, wtwdev->fwags))
		wetuwn;

	mutex_wock(&wtwdev->mutex);

	if (!test_bit(WTW89_FWAG_WUNNING, wtwdev->fwags))
		goto out;

	ieee80211_queue_dewayed_wowk(wtwdev->hw, &wtwdev->twack_wowk,
				     WTW89_TWACK_WOWK_PEWIOD);

	tfc_changed = wtw89_twaffic_stats_twack(wtwdev);
	if (wtwdev->scanning)
		goto out;

	wtw89_weave_wps(wtwdev);

	if (tfc_changed) {
		wtw89_hci_wecawc_int_mit(wtwdev);
		wtw89_btc_ntfy_ww_sta(wtwdev);
	}
	wtw89_mac_bf_monitow_twack(wtwdev);
	wtw89_phy_stat_twack(wtwdev);
	wtw89_phy_env_monitow_twack(wtwdev);
	wtw89_phy_dig(wtwdev);
	wtw89_cowe_wfk_twack(wtwdev);
	wtw89_phy_wa_update(wtwdev);
	wtw89_phy_cfo_twack(wtwdev);
	wtw89_phy_tx_path_div_twack(wtwdev);
	wtw89_phy_antdiv_twack(wtwdev);
	wtw89_phy_uw_tb_ctww_twack(wtwdev);
	wtw89_phy_edcca_twack(wtwdev);
	wtw89_tas_twack(wtwdev);
	wtw89_chanctx_twack(wtwdev);

	if (wtwdev->wps_enabwed && !wtwdev->btc.wps)
		wtw89_entew_wps_twack(wtwdev);

out:
	mutex_unwock(&wtwdev->mutex);
}

u8 wtw89_cowe_acquiwe_bit_map(unsigned wong *addw, unsigned wong size)
{
	unsigned wong bit;

	bit = find_fiwst_zewo_bit(addw, size);
	if (bit < size)
		set_bit(bit, addw);

	wetuwn bit;
}

void wtw89_cowe_wewease_bit_map(unsigned wong *addw, u8 bit)
{
	cweaw_bit(bit, addw);
}

void wtw89_cowe_wewease_aww_bits_map(unsigned wong *addw, unsigned int nbits)
{
	bitmap_zewo(addw, nbits);
}

int wtw89_cowe_acquiwe_sta_ba_entwy(stwuct wtw89_dev *wtwdev,
				    stwuct wtw89_sta *wtwsta, u8 tid, u8 *cam_idx)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;
	stwuct wtw89_ba_cam_entwy *entwy = NUWW, *tmp;
	u8 idx;
	int i;

	wockdep_assewt_hewd(&wtwdev->mutex);

	idx = wtw89_cowe_acquiwe_bit_map(cam_info->ba_cam_map, chip->bacam_num);
	if (idx == chip->bacam_num) {
		/* awwocate a static BA CAM to tid=0/5, so wepwace the existing
		 * one if BA CAM is fuww. Hawdwawe wiww pwocess the owiginaw tid
		 * automaticawwy.
		 */
		if (tid != 0 && tid != 5)
			wetuwn -ENOSPC;

		fow_each_set_bit(i, cam_info->ba_cam_map, chip->bacam_num) {
			tmp = &cam_info->ba_cam_entwy[i];
			if (tmp->tid == 0 || tmp->tid == 5)
				continue;

			idx = i;
			entwy = tmp;
			wist_dew(&entwy->wist);
			bweak;
		}

		if (!entwy)
			wetuwn -ENOSPC;
	} ewse {
		entwy = &cam_info->ba_cam_entwy[idx];
	}

	entwy->tid = tid;
	wist_add_taiw(&entwy->wist, &wtwsta->ba_cam_wist);

	*cam_idx = idx;

	wetuwn 0;
}

int wtw89_cowe_wewease_sta_ba_entwy(stwuct wtw89_dev *wtwdev,
				    stwuct wtw89_sta *wtwsta, u8 tid, u8 *cam_idx)
{
	stwuct wtw89_cam_info *cam_info = &wtwdev->cam_info;
	stwuct wtw89_ba_cam_entwy *entwy = NUWW, *tmp;
	u8 idx;

	wockdep_assewt_hewd(&wtwdev->mutex);

	wist_fow_each_entwy_safe(entwy, tmp, &wtwsta->ba_cam_wist, wist) {
		if (entwy->tid != tid)
			continue;

		idx = entwy - cam_info->ba_cam_entwy;
		wist_dew(&entwy->wist);

		wtw89_cowe_wewease_bit_map(cam_info->ba_cam_map, idx);
		*cam_idx = idx;
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

#define WTW89_TYPE_MAPPING(_type)	\
	case NW80211_IFTYPE_ ## _type:	\
		wtwvif->wifi_wowe = WTW89_WIFI_WOWE_ ## _type;	\
		bweak
void wtw89_vif_type_mapping(stwuct ieee80211_vif *vif, boow assoc)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		if (vif->p2p)
			wtwvif->wifi_wowe = WTW89_WIFI_WOWE_P2P_CWIENT;
		ewse
			wtwvif->wifi_wowe = WTW89_WIFI_WOWE_STATION;
		bweak;
	case NW80211_IFTYPE_AP:
		if (vif->p2p)
			wtwvif->wifi_wowe = WTW89_WIFI_WOWE_P2P_GO;
		ewse
			wtwvif->wifi_wowe = WTW89_WIFI_WOWE_AP;
		bweak;
	WTW89_TYPE_MAPPING(ADHOC);
	WTW89_TYPE_MAPPING(MONITOW);
	WTW89_TYPE_MAPPING(MESH_POINT);
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	switch (vif->type) {
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_MESH_POINT:
		wtwvif->net_type = WTW89_NET_TYPE_AP_MODE;
		wtwvif->sewf_wowe = WTW89_SEWF_WOWE_AP;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		wtwvif->net_type = WTW89_NET_TYPE_AD_HOC;
		wtwvif->sewf_wowe = WTW89_SEWF_WOWE_CWIENT;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (assoc) {
			wtwvif->net_type = WTW89_NET_TYPE_INFWA;
			wtwvif->twiggew = vif->bss_conf.he_suppowt;
		} ewse {
			wtwvif->net_type = WTW89_NET_TYPE_NO_WINK;
			wtwvif->twiggew = fawse;
		}
		wtwvif->sewf_wowe = WTW89_SEWF_WOWE_CWIENT;
		wtwvif->addw_cam.sec_ent_mode = WTW89_ADDW_CAM_SEC_NOWMAW;
		bweak;
	case NW80211_IFTYPE_MONITOW:
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

int wtw89_cowe_sta_add(stwuct wtw89_dev *wtwdev,
		       stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u8 ant_num = haw->ant_divewsity ? 2 : wtwdev->chip->wf_path_num;
	int i;
	int wet;

	wtwsta->wtwdev = wtwdev;
	wtwsta->wtwvif = wtwvif;
	wtwsta->pwev_wssi = 0;
	INIT_WIST_HEAD(&wtwsta->ba_cam_wist);
	skb_queue_head_init(&wtwsta->woc_queue);

	fow (i = 0; i < AWWAY_SIZE(sta->txq); i++)
		wtw89_cowe_txq_init(wtwdev, sta->txq[i]);

	ewma_wssi_init(&wtwsta->avg_wssi);
	ewma_snw_init(&wtwsta->avg_snw);
	fow (i = 0; i < ant_num; i++) {
		ewma_wssi_init(&wtwsta->wssi[i]);
		ewma_evm_init(&wtwsta->evm_min[i]);
		ewma_evm_init(&wtwsta->evm_max[i]);
	}

	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws) {
		/* fow station mode, assign the mac_id fwom itsewf */
		wtwsta->mac_id = wtwvif->mac_id;
		/* must do wtw89_weg_6ghz_powew_wecawc() befowe wfk channew */
		wtw89_weg_6ghz_powew_wecawc(wtwdev, wtwvif, twue);
		wtw89_btc_ntfy_wowe_info(wtwdev, wtwvif, wtwsta,
					 BTC_WOWE_MSTS_STA_CONN_STAWT);
		wtw89_chip_wfk_channew(wtwdev);
	} ewse if (vif->type == NW80211_IFTYPE_AP || sta->tdws) {
		wtwsta->mac_id = wtw89_cowe_acquiwe_bit_map(wtwdev->mac_id_map,
							    WTW89_MAX_MAC_ID_NUM);
		if (wtwsta->mac_id == WTW89_MAX_MAC_ID_NUM)
			wetuwn -ENOSPC;

		wet = wtw89_mac_set_macid_pause(wtwdev, wtwsta->mac_id, fawse);
		if (wet) {
			wtw89_cowe_wewease_bit_map(wtwdev->mac_id_map, wtwsta->mac_id);
			wtw89_wawn(wtwdev, "faiwed to send h2c macid pause\n");
			wetuwn wet;
		}

		wet = wtw89_fw_h2c_wowe_maintain(wtwdev, wtwvif, wtwsta,
						 WTW89_WOWE_CWEATE);
		if (wet) {
			wtw89_cowe_wewease_bit_map(wtwdev->mac_id_map, wtwsta->mac_id);
			wtw89_wawn(wtwdev, "faiwed to send h2c wowe info\n");
			wetuwn wet;
		}

		wtw89_queue_chanctx_change(wtwdev, WTW89_CHANCTX_WEMOTE_STA_CHANGE);
	}

	wetuwn 0;
}

int wtw89_cowe_sta_disassoc(stwuct wtw89_dev *wtwdev,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;

	if (vif->type == NW80211_IFTYPE_STATION)
		wtw89_fw_h2c_set_bcn_fwtw_cfg(wtwdev, vif, fawse);

	wtwdev->totaw_sta_assoc--;
	if (sta->tdws)
		wtwvif->tdws_peew--;
	wtwsta->disassoc = twue;

	wetuwn 0;
}

int wtw89_cowe_sta_disconnect(stwuct wtw89_dev *wtwdev,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	int wet;

	wtw89_mac_bf_monitow_cawc(wtwdev, sta, twue);
	wtw89_mac_bf_disassoc(wtwdev, vif, sta);
	wtw89_cowe_fwee_sta_pending_ba(wtwdev, sta);
	wtw89_cowe_fwee_sta_pending_fowbid_ba(wtwdev, sta);
	wtw89_cowe_fwee_sta_pending_woc_tx(wtwdev, sta);

	if (vif->type == NW80211_IFTYPE_AP || sta->tdws)
		wtw89_cam_deinit_addw_cam(wtwdev, &wtwsta->addw_cam);
	if (sta->tdws)
		wtw89_cam_deinit_bssid_cam(wtwdev, &wtwsta->bssid_cam);

	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws) {
		wtw89_vif_type_mapping(vif, fawse);
		wtw89_fw_wewease_genewaw_pkt_wist_vif(wtwdev, wtwvif, twue);
	}

	wet = wtw89_fw_h2c_assoc_cmac_tbw(wtwdev, vif, sta);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c cmac tabwe\n");
		wetuwn wet;
	}

	wet = wtw89_fw_h2c_join_info(wtwdev, wtwvif, wtwsta, twue);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c join info\n");
		wetuwn wet;
	}

	/* update cam aid mac_id net_type */
	wet = wtw89_fw_h2c_cam(wtwdev, wtwvif, wtwsta, NUWW);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c cam\n");
		wetuwn wet;
	}

	wetuwn wet;
}

int wtw89_cowe_sta_assoc(stwuct wtw89_dev *wtwdev,
			 stwuct ieee80211_vif *vif,
			 stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	stwuct wtw89_bssid_cam_entwy *bssid_cam = wtw89_get_bssid_cam_of(wtwvif, wtwsta);
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev,
						       wtwvif->sub_entity_idx);
	int wet;

	if (vif->type == NW80211_IFTYPE_AP || sta->tdws) {
		if (sta->tdws) {
			wet = wtw89_cam_init_bssid_cam(wtwdev, wtwvif, bssid_cam, sta->addw);
			if (wet) {
				wtw89_wawn(wtwdev, "faiwed to send h2c init bssid cam fow TDWS\n");
				wetuwn wet;
			}
		}

		wet = wtw89_cam_init_addw_cam(wtwdev, &wtwsta->addw_cam, bssid_cam);
		if (wet) {
			wtw89_wawn(wtwdev, "faiwed to send h2c init addw cam\n");
			wetuwn wet;
		}
	}

	wet = wtw89_fw_h2c_assoc_cmac_tbw(wtwdev, vif, sta);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c cmac tabwe\n");
		wetuwn wet;
	}

	wet = wtw89_fw_h2c_join_info(wtwdev, wtwvif, wtwsta, fawse);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c join info\n");
		wetuwn wet;
	}

	/* update cam aid mac_id net_type */
	wet = wtw89_fw_h2c_cam(wtwdev, wtwvif, wtwsta, NUWW);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to send h2c cam\n");
		wetuwn wet;
	}

	wtwdev->totaw_sta_assoc++;
	if (sta->tdws)
		wtwvif->tdws_peew++;
	wtw89_phy_wa_assoc(wtwdev, sta);
	wtw89_mac_bf_assoc(wtwdev, vif, sta);
	wtw89_mac_bf_monitow_cawc(wtwdev, sta, fawse);

	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws) {
		stwuct ieee80211_bss_conf *bss_conf = &vif->bss_conf;

		if (bss_conf->he_suppowt &&
		    !(bss_conf->he_opew.pawams & IEEE80211_HE_OPEWATION_EW_SU_DISABWE))
			wtwsta->ew_cap = twue;

		wtw89_btc_ntfy_wowe_info(wtwdev, wtwvif, wtwsta,
					 BTC_WOWE_MSTS_STA_CONN_END);
		wtw89_cowe_get_no_uw_ofdma_htc(wtwdev, &wtwsta->htc_tempwate, chan);
		wtw89_phy_uw_tb_assoc(wtwdev, wtwvif);

		wet = wtw89_fw_h2c_genewaw_pkt(wtwdev, wtwvif, wtwsta->mac_id);
		if (wet) {
			wtw89_wawn(wtwdev, "faiwed to send h2c genewaw packet\n");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

int wtw89_cowe_sta_wemove(stwuct wtw89_dev *wtwdev,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;
	int wet;

	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws) {
		wtw89_weg_6ghz_powew_wecawc(wtwdev, wtwvif, fawse);
		wtw89_btc_ntfy_wowe_info(wtwdev, wtwvif, wtwsta,
					 BTC_WOWE_MSTS_STA_DIS_CONN);
	} ewse if (vif->type == NW80211_IFTYPE_AP || sta->tdws) {
		wtw89_cowe_wewease_bit_map(wtwdev->mac_id_map, wtwsta->mac_id);

		wet = wtw89_fw_h2c_wowe_maintain(wtwdev, wtwvif, wtwsta,
						 WTW89_WOWE_WEMOVE);
		if (wet) {
			wtw89_wawn(wtwdev, "faiwed to send h2c wowe info\n");
			wetuwn wet;
		}

		wtw89_queue_chanctx_change(wtwdev, WTW89_CHANCTX_WEMOTE_STA_CHANGE);
	}

	wetuwn 0;
}

static void _wtw89_cowe_set_tid_config(stwuct wtw89_dev *wtwdev,
				       stwuct ieee80211_sta *sta,
				       stwuct cfg80211_tid_cfg *tid_conf)
{
	stwuct ieee80211_txq *txq;
	stwuct wtw89_txq *wtwtxq;
	u32 mask = tid_conf->mask;
	u8 tids = tid_conf->tids;
	int tids_nbit = BITS_PEW_BYTE;
	int i;

	fow (i = 0; i < tids_nbit; i++, tids >>= 1) {
		if (!tids)
			bweak;

		if (!(tids & BIT(0)))
			continue;

		txq = sta->txq[i];
		wtwtxq = (stwuct wtw89_txq *)txq->dwv_pwiv;

		if (mask & BIT(NW80211_TID_CONFIG_ATTW_AMPDU_CTWW)) {
			if (tid_conf->ampdu == NW80211_TID_CONFIG_ENABWE) {
				cweaw_bit(WTW89_TXQ_F_FOWBID_BA, &wtwtxq->fwags);
			} ewse {
				if (test_bit(WTW89_TXQ_F_AMPDU, &wtwtxq->fwags))
					ieee80211_stop_tx_ba_session(sta, txq->tid);
				spin_wock_bh(&wtwdev->ba_wock);
				wist_dew_init(&wtwtxq->wist);
				set_bit(WTW89_TXQ_F_FOWBID_BA, &wtwtxq->fwags);
				spin_unwock_bh(&wtwdev->ba_wock);
			}
		}

		if (mask & BIT(NW80211_TID_CONFIG_ATTW_AMSDU_CTWW) && tids == 0xff) {
			if (tid_conf->amsdu == NW80211_TID_CONFIG_ENABWE)
				sta->max_amsdu_subfwames = 0;
			ewse
				sta->max_amsdu_subfwames = 1;
		}
	}
}

void wtw89_cowe_set_tid_config(stwuct wtw89_dev *wtwdev,
			       stwuct ieee80211_sta *sta,
			       stwuct cfg80211_tid_config *tid_config)
{
	int i;

	fow (i = 0; i < tid_config->n_tid_conf; i++)
		_wtw89_cowe_set_tid_config(wtwdev, sta,
					   &tid_config->tid_conf[i]);
}

static void wtw89_init_ht_cap(stwuct wtw89_dev *wtwdev,
			      stwuct ieee80211_sta_ht_cap *ht_cap)
{
	static const __we16 highest[WF_PATH_MAX] = {
		cpu_to_we16(150), cpu_to_we16(300), cpu_to_we16(450), cpu_to_we16(600),
	};
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u8 nss = haw->wx_nss;
	int i;

	ht_cap->ht_suppowted = twue;
	ht_cap->cap = 0;
	ht_cap->cap |= IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_MAX_AMSDU |
		       IEEE80211_HT_CAP_TX_STBC |
		       (1 << IEEE80211_HT_CAP_WX_STBC_SHIFT);
	ht_cap->cap |= IEEE80211_HT_CAP_WDPC_CODING;
	ht_cap->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_DSSSCCK40 |
		       IEEE80211_HT_CAP_SGI_40;
	ht_cap->ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap->ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;
	ht_cap->mcs.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED;
	fow (i = 0; i < nss; i++)
		ht_cap->mcs.wx_mask[i] = 0xFF;
	ht_cap->mcs.wx_mask[4] = 0x01;
	ht_cap->mcs.wx_highest = highest[nss - 1];
}

static void wtw89_init_vht_cap(stwuct wtw89_dev *wtwdev,
			       stwuct ieee80211_sta_vht_cap *vht_cap)
{
	static const __we16 highest_bw80[WF_PATH_MAX] = {
		cpu_to_we16(433), cpu_to_we16(867), cpu_to_we16(1300), cpu_to_we16(1733),
	};
	static const __we16 highest_bw160[WF_PATH_MAX] = {
		cpu_to_we16(867), cpu_to_we16(1733), cpu_to_we16(2600), cpu_to_we16(3467),
	};
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const __we16 *highest = chip->suppowt_bw160 ? highest_bw160 : highest_bw80;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u16 tx_mcs_map = 0, wx_mcs_map = 0;
	u8 sts_cap = 3;
	int i;

	fow (i = 0; i < 8; i++) {
		if (i < haw->tx_nss)
			tx_mcs_map |= IEEE80211_VHT_MCS_SUPPOWT_0_9 << (i * 2);
		ewse
			tx_mcs_map |= IEEE80211_VHT_MCS_NOT_SUPPOWTED << (i * 2);
		if (i < haw->wx_nss)
			wx_mcs_map |= IEEE80211_VHT_MCS_SUPPOWT_0_9 << (i * 2);
		ewse
			wx_mcs_map |= IEEE80211_VHT_MCS_NOT_SUPPOWTED << (i * 2);
	}

	vht_cap->vht_suppowted = twue;
	vht_cap->cap = IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454 |
		       IEEE80211_VHT_CAP_SHOWT_GI_80 |
		       IEEE80211_VHT_CAP_WXSTBC_1 |
		       IEEE80211_VHT_CAP_HTC_VHT |
		       IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK |
		       0;
	vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	vht_cap->cap |= IEEE80211_VHT_CAP_WXWDPC;
	vht_cap->cap |= IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE |
			IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE;
	vht_cap->cap |= sts_cap << IEEE80211_VHT_CAP_BEAMFOWMEE_STS_SHIFT;
	if (chip->suppowt_bw160)
		vht_cap->cap |= IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ |
				IEEE80211_VHT_CAP_SHOWT_GI_160;
	vht_cap->vht_mcs.wx_mcs_map = cpu_to_we16(wx_mcs_map);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_we16(tx_mcs_map);
	vht_cap->vht_mcs.wx_highest = highest[haw->wx_nss - 1];
	vht_cap->vht_mcs.tx_highest = highest[haw->tx_nss - 1];
}

#define WTW89_SBAND_IFTYPES_NW 2

static void wtw89_init_he_cap(stwuct wtw89_dev *wtwdev,
			      enum nw80211_band band,
			      stwuct ieee80211_suppowted_band *sband)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	stwuct ieee80211_sband_iftype_data *iftype_data;
	boow no_ng16 = (chip->chip_id == WTW8852A && haw->cv == CHIP_CBV) ||
		       (chip->chip_id == WTW8852B && haw->cv == CHIP_CAV);
	u16 mcs_map = 0;
	int i;
	int nss = haw->wx_nss;
	int idx = 0;

	iftype_data = kcawwoc(WTW89_SBAND_IFTYPES_NW, sizeof(*iftype_data), GFP_KEWNEW);
	if (!iftype_data)
		wetuwn;

	fow (i = 0; i < 8; i++) {
		if (i < nss)
			mcs_map |= IEEE80211_HE_MCS_SUPPOWT_0_11 << (i * 2);
		ewse
			mcs_map |= IEEE80211_HE_MCS_NOT_SUPPOWTED << (i * 2);
	}

	fow (i = 0; i < NUM_NW80211_IFTYPES; i++) {
		stwuct ieee80211_sta_he_cap *he_cap;
		u8 *mac_cap_info;
		u8 *phy_cap_info;

		switch (i) {
		case NW80211_IFTYPE_STATION:
		case NW80211_IFTYPE_AP:
			bweak;
		defauwt:
			continue;
		}

		if (idx >= WTW89_SBAND_IFTYPES_NW) {
			wtw89_wawn(wtwdev, "wun out of iftype_data\n");
			bweak;
		}

		iftype_data[idx].types_mask = BIT(i);
		he_cap = &iftype_data[idx].he_cap;
		mac_cap_info = he_cap->he_cap_ewem.mac_cap_info;
		phy_cap_info = he_cap->he_cap_ewem.phy_cap_info;

		he_cap->has_he = twue;
		mac_cap_info[0] = IEEE80211_HE_MAC_CAP0_HTC_HE;
		if (i == NW80211_IFTYPE_STATION)
			mac_cap_info[1] = IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_16US;
		mac_cap_info[2] = IEEE80211_HE_MAC_CAP2_AWW_ACK |
				  IEEE80211_HE_MAC_CAP2_BSW;
		mac_cap_info[3] = IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_2;
		if (i == NW80211_IFTYPE_AP)
			mac_cap_info[3] |= IEEE80211_HE_MAC_CAP3_OMI_CONTWOW;
		mac_cap_info[4] = IEEE80211_HE_MAC_CAP4_OPS |
				  IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU;
		if (i == NW80211_IFTYPE_STATION)
			mac_cap_info[5] = IEEE80211_HE_MAC_CAP5_HT_VHT_TWIG_FWAME_WX;
		if (band == NW80211_BAND_2GHZ) {
			phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G;
		} ewse {
			phy_cap_info[0] =
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G;
			if (chip->suppowt_bw160)
				phy_cap_info[0] |= IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;
		}
		phy_cap_info[1] = IEEE80211_HE_PHY_CAP1_DEVICE_CWASS_A |
				  IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD |
				  IEEE80211_HE_PHY_CAP1_HE_WTF_AND_GI_FOW_HE_PPDUS_0_8US;
		phy_cap_info[2] = IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US |
				  IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ |
				  IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ |
				  IEEE80211_HE_PHY_CAP2_DOPPWEW_TX;
		phy_cap_info[3] = IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_16_QAM;
		if (i == NW80211_IFTYPE_STATION)
			phy_cap_info[3] |= IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_16_QAM |
					   IEEE80211_HE_PHY_CAP3_DCM_MAX_TX_NSS_2;
		if (i == NW80211_IFTYPE_AP)
			phy_cap_info[3] |= IEEE80211_HE_PHY_CAP3_WX_PAWTIAW_BW_SU_IN_20MHZ_MU;
		phy_cap_info[4] = IEEE80211_HE_PHY_CAP4_SU_BEAMFOWMEE |
				  IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_4;
		if (chip->suppowt_bw160)
			phy_cap_info[4] |= IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_4;
		phy_cap_info[5] = no_ng16 ? 0 :
				  IEEE80211_HE_PHY_CAP5_NG16_SU_FEEDBACK |
				  IEEE80211_HE_PHY_CAP5_NG16_MU_FEEDBACK;
		phy_cap_info[6] = IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_42_SU |
				  IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_75_MU |
				  IEEE80211_HE_PHY_CAP6_TWIG_SU_BEAMFOWMING_FB |
				  IEEE80211_HE_PHY_CAP6_PAWTIAW_BW_EXT_WANGE;
		phy_cap_info[7] = IEEE80211_HE_PHY_CAP7_POWEW_BOOST_FACTOW_SUPP |
				  IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI |
				  IEEE80211_HE_PHY_CAP7_MAX_NC_1;
		phy_cap_info[8] = IEEE80211_HE_PHY_CAP8_HE_EW_SU_PPDU_4XWTF_AND_08_US_GI |
				  IEEE80211_HE_PHY_CAP8_HE_EW_SU_1XWTF_AND_08_US_GI |
				  IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_996;
		if (chip->suppowt_bw160)
			phy_cap_info[8] |= IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
					   IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU;
		phy_cap_info[9] = IEEE80211_HE_PHY_CAP9_WONGEW_THAN_16_SIGB_OFDM_SYM |
				  IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU |
				  IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_COMP_SIGB |
				  IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_NON_COMP_SIGB |
				  u8_encode_bits(IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_16US,
						 IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_MASK);
		if (i == NW80211_IFTYPE_STATION)
			phy_cap_info[9] |= IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU;
		he_cap->he_mcs_nss_supp.wx_mcs_80 = cpu_to_we16(mcs_map);
		he_cap->he_mcs_nss_supp.tx_mcs_80 = cpu_to_we16(mcs_map);
		if (chip->suppowt_bw160) {
			he_cap->he_mcs_nss_supp.wx_mcs_160 = cpu_to_we16(mcs_map);
			he_cap->he_mcs_nss_supp.tx_mcs_160 = cpu_to_we16(mcs_map);
		}

		if (band == NW80211_BAND_6GHZ) {
			__we16 capa;

			capa = we16_encode_bits(IEEE80211_HT_MPDU_DENSITY_NONE,
						IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT) |
			       we16_encode_bits(IEEE80211_VHT_MAX_AMPDU_1024K,
						IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP) |
			       we16_encode_bits(IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454,
						IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN);
			iftype_data[idx].he_6ghz_capa.capa = capa;
		}

		idx++;
	}

	_ieee80211_set_sband_iftype_data(sband, iftype_data, idx);
}

static int wtw89_cowe_set_suppowted_band(stwuct wtw89_dev *wtwdev)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct ieee80211_suppowted_band *sband_2ghz = NUWW, *sband_5ghz = NUWW;
	stwuct ieee80211_suppowted_band *sband_6ghz = NUWW;
	u32 size = sizeof(stwuct ieee80211_suppowted_band);
	u8 suppowt_bands = wtwdev->chip->suppowt_bands;

	if (suppowt_bands & BIT(NW80211_BAND_2GHZ)) {
		sband_2ghz = kmemdup(&wtw89_sband_2ghz, size, GFP_KEWNEW);
		if (!sband_2ghz)
			goto eww;
		wtw89_init_ht_cap(wtwdev, &sband_2ghz->ht_cap);
		wtw89_init_he_cap(wtwdev, NW80211_BAND_2GHZ, sband_2ghz);
		hw->wiphy->bands[NW80211_BAND_2GHZ] = sband_2ghz;
	}

	if (suppowt_bands & BIT(NW80211_BAND_5GHZ)) {
		sband_5ghz = kmemdup(&wtw89_sband_5ghz, size, GFP_KEWNEW);
		if (!sband_5ghz)
			goto eww;
		wtw89_init_ht_cap(wtwdev, &sband_5ghz->ht_cap);
		wtw89_init_vht_cap(wtwdev, &sband_5ghz->vht_cap);
		wtw89_init_he_cap(wtwdev, NW80211_BAND_5GHZ, sband_5ghz);
		hw->wiphy->bands[NW80211_BAND_5GHZ] = sband_5ghz;
	}

	if (suppowt_bands & BIT(NW80211_BAND_6GHZ)) {
		sband_6ghz = kmemdup(&wtw89_sband_6ghz, size, GFP_KEWNEW);
		if (!sband_6ghz)
			goto eww;
		wtw89_init_he_cap(wtwdev, NW80211_BAND_6GHZ, sband_6ghz);
		hw->wiphy->bands[NW80211_BAND_6GHZ] = sband_6ghz;
	}

	wetuwn 0;

eww:
	hw->wiphy->bands[NW80211_BAND_2GHZ] = NUWW;
	hw->wiphy->bands[NW80211_BAND_5GHZ] = NUWW;
	hw->wiphy->bands[NW80211_BAND_6GHZ] = NUWW;
	if (sband_2ghz)
		kfwee((__fowce void *)sband_2ghz->iftype_data);
	if (sband_5ghz)
		kfwee((__fowce void *)sband_5ghz->iftype_data);
	if (sband_6ghz)
		kfwee((__fowce void *)sband_6ghz->iftype_data);
	kfwee(sband_2ghz);
	kfwee(sband_5ghz);
	kfwee(sband_6ghz);
	wetuwn -ENOMEM;
}

static void wtw89_cowe_cww_suppowted_band(stwuct wtw89_dev *wtwdev)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;

	if (hw->wiphy->bands[NW80211_BAND_2GHZ])
		kfwee((__fowce void *)hw->wiphy->bands[NW80211_BAND_2GHZ]->iftype_data);
	if (hw->wiphy->bands[NW80211_BAND_5GHZ])
		kfwee((__fowce void *)hw->wiphy->bands[NW80211_BAND_5GHZ]->iftype_data);
	if (hw->wiphy->bands[NW80211_BAND_6GHZ])
		kfwee((__fowce void *)hw->wiphy->bands[NW80211_BAND_6GHZ]->iftype_data);
	kfwee(hw->wiphy->bands[NW80211_BAND_2GHZ]);
	kfwee(hw->wiphy->bands[NW80211_BAND_5GHZ]);
	kfwee(hw->wiphy->bands[NW80211_BAND_6GHZ]);
	hw->wiphy->bands[NW80211_BAND_2GHZ] = NUWW;
	hw->wiphy->bands[NW80211_BAND_5GHZ] = NUWW;
	hw->wiphy->bands[NW80211_BAND_6GHZ] = NUWW;
}

static void wtw89_cowe_ppdu_sts_init(stwuct wtw89_dev *wtwdev)
{
	int i;

	fow (i = 0; i < WTW89_PHY_MAX; i++)
		skb_queue_head_init(&wtwdev->ppdu_sts.wx_queue[i]);
	fow (i = 0; i < WTW89_PHY_MAX; i++)
		wtwdev->ppdu_sts.cuww_wx_ppdu_cnt[i] = U8_MAX;
}

void wtw89_cowe_update_beacon_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_dev *wtwdev;
	stwuct wtw89_vif *wtwvif = containew_of(wowk, stwuct wtw89_vif,
						update_beacon_wowk);

	if (wtwvif->net_type != WTW89_NET_TYPE_AP_MODE)
		wetuwn;

	wtwdev = wtwvif->wtwdev;
	mutex_wock(&wtwdev->mutex);
	wtw89_fw_h2c_update_beacon(wtwdev, wtwvif);
	mutex_unwock(&wtwdev->mutex);
}

int wtw89_wait_fow_cond(stwuct wtw89_wait_info *wait, unsigned int cond)
{
	stwuct compwetion *cmpw = &wait->compwetion;
	unsigned wong timeout;
	unsigned int cuw;

	cuw = atomic_cmpxchg(&wait->cond, WTW89_WAIT_COND_IDWE, cond);
	if (cuw != WTW89_WAIT_COND_IDWE)
		wetuwn -EBUSY;

	timeout = wait_fow_compwetion_timeout(cmpw, WTW89_WAIT_FOW_COND_TIMEOUT);
	if (timeout == 0) {
		atomic_set(&wait->cond, WTW89_WAIT_COND_IDWE);
		wetuwn -ETIMEDOUT;
	}

	if (wait->data.eww)
		wetuwn -EFAUWT;

	wetuwn 0;
}

void wtw89_compwete_cond(stwuct wtw89_wait_info *wait, unsigned int cond,
			 const stwuct wtw89_compwetion_data *data)
{
	unsigned int cuw;

	cuw = atomic_cmpxchg(&wait->cond, cond, WTW89_WAIT_COND_IDWE);
	if (cuw != cond)
		wetuwn;

	wait->data = *data;
	compwete(&wait->compwetion);
}

void wtw89_cowe_ntfy_btc_event(stwuct wtw89_dev *wtwdev, enum wtw89_btc_hmsg event)
{
	u16 bt_weq_wen;

	switch (event) {
	case WTW89_BTC_HMSG_SET_BT_WEQ_SWOT:
		bt_weq_wen = wtw89_coex_quewy_bt_weq_wen(wtwdev, WTW89_PHY_0);
		wtw89_debug(wtwdev, WTW89_DBG_BTC,
			    "coex updates BT weq wen to %d TU\n", bt_weq_wen);
		wtw89_queue_chanctx_change(wtwdev, WTW89_CHANCTX_BT_SWOT_CHANGE);
		bweak;
	defauwt:
		if (event < NUM_OF_WTW89_BTC_HMSG)
			wtw89_debug(wtwdev, WTW89_DBG_BTC,
				    "unhandwed BTC HMSG event: %d\n", event);
		ewse
			wtw89_wawn(wtwdev,
				   "unwecognized BTC HMSG event: %d\n", event);
		bweak;
	}
}

int wtw89_cowe_stawt(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtwdev->mac.qta_mode = WTW89_QTA_SCC;
	wet = wtw89_mac_init(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "mac init faiw, wet:%d\n", wet);
		wetuwn wet;
	}

	wtw89_btc_ntfy_powewon(wtwdev);

	/* efuse pwocess */

	/* pwe-config BB/WF, BB weset/WFC weset */
	wet = wtw89_chip_weset_bb_wf(wtwdev);
	if (wet)
		wetuwn wet;

	wtw89_phy_init_bb_weg(wtwdev);
	wtw89_phy_init_wf_weg(wtwdev, fawse);

	wtw89_btc_ntfy_init(wtwdev, BTC_MODE_NOWMAW);

	wtw89_phy_dm_init(wtwdev);

	wtw89_mac_cfg_ppdu_status(wtwdev, WTW89_MAC_0, twue);
	wtw89_mac_update_wts_thweshowd(wtwdev, WTW89_MAC_0);

	wtw89_tas_weset(wtwdev);

	wet = wtw89_hci_stawt(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to stawt hci\n");
		wetuwn wet;
	}

	ieee80211_queue_dewayed_wowk(wtwdev->hw, &wtwdev->twack_wowk,
				     WTW89_TWACK_WOWK_PEWIOD);

	set_bit(WTW89_FWAG_WUNNING, wtwdev->fwags);

	wtw89_btc_ntfy_wadio_state(wtwdev, BTC_WFCTWW_WW_ON);
	wtw89_fw_h2c_fw_wog(wtwdev, wtwdev->fw.wog.enabwe);
	wtw89_fw_h2c_init_ba_cam(wtwdev);

	wetuwn 0;
}

void wtw89_cowe_stop(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;

	/* Pwvent to stop twice; entew_ips and ops_stop */
	if (!test_bit(WTW89_FWAG_WUNNING, wtwdev->fwags))
		wetuwn;

	wtw89_btc_ntfy_wadio_state(wtwdev, BTC_WFCTWW_WW_OFF);

	cweaw_bit(WTW89_FWAG_WUNNING, wtwdev->fwags);

	mutex_unwock(&wtwdev->mutex);

	cancew_wowk_sync(&wtwdev->c2h_wowk);
	cancew_wowk_sync(&wtwdev->cancew_6ghz_pwobe_wowk);
	cancew_wowk_sync(&btc->eapow_notify_wowk);
	cancew_wowk_sync(&btc->awp_notify_wowk);
	cancew_wowk_sync(&btc->dhcp_notify_wowk);
	cancew_wowk_sync(&btc->icmp_notify_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->txq_weinvoke_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->twack_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->chanctx_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->coex_act1_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->coex_bt_devinfo_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->coex_wfk_chk_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->cfo_twack_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->fowbid_ba_wowk);
	cancew_dewayed_wowk_sync(&wtwdev->antdiv_wowk);

	mutex_wock(&wtwdev->mutex);

	wtw89_btc_ntfy_powewoff(wtwdev);
	wtw89_hci_fwush_queues(wtwdev, BIT(wtwdev->hw->queues) - 1, twue);
	wtw89_mac_fwush_txq(wtwdev, BIT(wtwdev->hw->queues) - 1, twue);
	wtw89_hci_stop(wtwdev);
	wtw89_hci_deinit(wtwdev);
	wtw89_mac_pww_off(wtwdev);
	wtw89_hci_weset(wtwdev);
}

int wtw89_cowe_init(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	u8 band;

	INIT_WIST_HEAD(&wtwdev->ba_wist);
	INIT_WIST_HEAD(&wtwdev->fowbid_ba_wist);
	INIT_WIST_HEAD(&wtwdev->wtwvifs_wist);
	INIT_WIST_HEAD(&wtwdev->eawwy_h2c_wist);
	fow (band = NW80211_BAND_2GHZ; band < NUM_NW80211_BANDS; band++) {
		if (!(wtwdev->chip->suppowt_bands & BIT(band)))
			continue;
		INIT_WIST_HEAD(&wtwdev->scan_info.pkt_wist[band]);
	}
	INIT_WOWK(&wtwdev->ba_wowk, wtw89_cowe_ba_wowk);
	INIT_WOWK(&wtwdev->txq_wowk, wtw89_cowe_txq_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->txq_weinvoke_wowk, wtw89_cowe_txq_weinvoke_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->twack_wowk, wtw89_twack_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->chanctx_wowk, wtw89_chanctx_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->coex_act1_wowk, wtw89_coex_act1_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->coex_bt_devinfo_wowk, wtw89_coex_bt_devinfo_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->coex_wfk_chk_wowk, wtw89_coex_wfk_chk_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->cfo_twack_wowk, wtw89_phy_cfo_twack_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->fowbid_ba_wowk, wtw89_fowbid_ba_wowk);
	INIT_DEWAYED_WOWK(&wtwdev->antdiv_wowk, wtw89_phy_antdiv_wowk);
	wtwdev->txq_wq = awwoc_wowkqueue("wtw89_tx_wq", WQ_UNBOUND | WQ_HIGHPWI, 0);
	if (!wtwdev->txq_wq)
		wetuwn -ENOMEM;
	spin_wock_init(&wtwdev->ba_wock);
	spin_wock_init(&wtwdev->wpwm_wock);
	mutex_init(&wtwdev->mutex);
	mutex_init(&wtwdev->wf_mutex);
	wtwdev->totaw_sta_assoc = 0;

	wtw89_init_wait(&wtwdev->mcc.wait);
	wtw89_init_wait(&wtwdev->mac.fw_ofwd_wait);

	INIT_WOWK(&wtwdev->c2h_wowk, wtw89_fw_c2h_wowk);
	INIT_WOWK(&wtwdev->ips_wowk, wtw89_ips_wowk);
	INIT_WOWK(&wtwdev->woad_fiwmwawe_wowk, wtw89_woad_fiwmwawe_wowk);
	INIT_WOWK(&wtwdev->cancew_6ghz_pwobe_wowk, wtw89_cancew_6ghz_pwobe_wowk);

	skb_queue_head_init(&wtwdev->c2h_queue);
	wtw89_cowe_ppdu_sts_init(wtwdev);
	wtw89_twaffic_stats_init(wtwdev, &wtwdev->stats);

	wtwdev->haw.wx_fwtw = DEFAUWT_AX_WX_FWTW;

	INIT_WOWK(&btc->eapow_notify_wowk, wtw89_btc_ntfy_eapow_packet_wowk);
	INIT_WOWK(&btc->awp_notify_wowk, wtw89_btc_ntfy_awp_packet_wowk);
	INIT_WOWK(&btc->dhcp_notify_wowk, wtw89_btc_ntfy_dhcp_packet_wowk);
	INIT_WOWK(&btc->icmp_notify_wowk, wtw89_btc_ntfy_icmp_packet_wowk);

	init_compwetion(&wtwdev->fw.weq.compwetion);

	scheduwe_wowk(&wtwdev->woad_fiwmwawe_wowk);

	wtw89_sew_init(wtwdev);
	wtw89_entity_init(wtwdev);
	wtw89_tas_init(wtwdev);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtw89_cowe_init);

void wtw89_cowe_deinit(stwuct wtw89_dev *wtwdev)
{
	wtw89_sew_deinit(wtwdev);
	wtw89_unwoad_fiwmwawe(wtwdev);
	wtw89_fw_fwee_aww_eawwy_h2c(wtwdev);

	destwoy_wowkqueue(wtwdev->txq_wq);
	mutex_destwoy(&wtwdev->wf_mutex);
	mutex_destwoy(&wtwdev->mutex);
}
EXPOWT_SYMBOW(wtw89_cowe_deinit);

void wtw89_cowe_scan_stawt(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
			   const u8 *mac_addw, boow hw_scan)
{
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev,
						       wtwvif->sub_entity_idx);

	wtwdev->scanning = twue;
	wtw89_weave_wps(wtwdev);
	if (hw_scan)
		wtw89_weave_ips_by_hwfwags(wtwdev);

	ethew_addw_copy(wtwvif->mac_addw, mac_addw);
	wtw89_btc_ntfy_scan_stawt(wtwdev, WTW89_PHY_0, chan->band_type);
	wtw89_chip_wfk_scan(wtwdev, twue);
	wtw89_hci_wecawc_int_mit(wtwdev);
	wtw89_phy_config_edcca(wtwdev, twue);

	wtw89_fw_h2c_cam(wtwdev, wtwvif, NUWW, mac_addw);
}

void wtw89_cowe_scan_compwete(stwuct wtw89_dev *wtwdev,
			      stwuct ieee80211_vif *vif, boow hw_scan)
{
	stwuct wtw89_vif *wtwvif = vif ? (stwuct wtw89_vif *)vif->dwv_pwiv : NUWW;

	if (!wtwvif)
		wetuwn;

	ethew_addw_copy(wtwvif->mac_addw, vif->addw);
	wtw89_fw_h2c_cam(wtwdev, wtwvif, NUWW, NUWW);

	wtw89_chip_wfk_scan(wtwdev, fawse);
	wtw89_btc_ntfy_scan_finish(wtwdev, WTW89_PHY_0);
	wtw89_phy_config_edcca(wtwdev, fawse);

	wtwdev->scanning = fawse;
	wtwdev->dig.bypass_dig = twue;
	if (hw_scan && (wtwdev->hw->conf.fwags & IEEE80211_CONF_IDWE))
		ieee80211_queue_wowk(wtwdev->hw, &wtwdev->ips_wowk);
}

static void wtw89_wead_chip_vew(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	int wet;
	u8 vaw;
	u8 cv;

	cv = wtw89_wead32_mask(wtwdev, W_AX_SYS_CFG1, B_AX_CHIP_VEW_MASK);
	if (chip->chip_id == WTW8852A && cv <= CHIP_CBV) {
		if (wtw89_wead32(wtwdev, W_AX_GPIO0_7_FUNC_SEW) == WTW89_W32_DEAD)
			cv = CHIP_CAV;
		ewse
			cv = CHIP_CBV;
	}

	wtwdev->haw.cv = cv;

	if (chip->chip_id == WTW8852B || chip->chip_id == WTW8851B) {
		wet = wtw89_mac_wead_xtaw_si(wtwdev, XTAW_SI_CV, &vaw);
		if (wet)
			wetuwn;

		wtwdev->haw.acv = u8_get_bits(vaw, XTAW_SI_ACV_MASK);
	}
}

static void wtw89_cowe_setup_phycap(stwuct wtw89_dev *wtwdev)
{
	wtwdev->haw.suppowt_cckpd =
		!(wtwdev->chip->chip_id == WTW8852A && wtwdev->haw.cv <= CHIP_CBV) &&
		!(wtwdev->chip->chip_id == WTW8852B && wtwdev->haw.cv <= CHIP_CAV);
	wtwdev->haw.suppowt_igi =
		wtwdev->chip->chip_id == WTW8852A && wtwdev->haw.cv <= CHIP_CBV;
}

static void wtw89_cowe_setup_wfe_pawms(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_wfe_pawms_conf *conf = chip->wfe_pawms_conf;
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;
	const stwuct wtw89_wfe_pawms *sew;
	u8 wfe_type = efuse->wfe_type;

	if (!conf) {
		sew = chip->dfwt_pawms;
		goto out;
	}

	whiwe (conf->wfe_pawms) {
		if (wfe_type == conf->wfe_type) {
			sew = conf->wfe_pawms;
			goto out;
		}
		conf++;
	}

	sew = chip->dfwt_pawms;

out:
	wtwdev->wfe_pawms = wtw89_woad_wfe_data_fwom_fw(wtwdev, sew);
	wtw89_woad_txpww_tabwe(wtwdev, wtwdev->wfe_pawms->byw_tbw);
}

static int wtw89_chip_efuse_info_setup(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	int wet;

	wet = wtw89_mac_pawtiaw_init(wtwdev, fawse);
	if (wet)
		wetuwn wet;

	wet = mac->pawse_efuse_map(wtwdev);
	if (wet)
		wetuwn wet;

	wet = mac->pawse_phycap_map(wtwdev);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_setup_phycap(wtwdev);
	if (wet)
		wetuwn wet;

	wtw89_cowe_setup_phycap(wtwdev);

	wtw89_hci_mac_pwe_deinit(wtwdev);

	wtw89_mac_pww_off(wtwdev);

	wetuwn 0;
}

static int wtw89_chip_boawd_info_setup(stwuct wtw89_dev *wtwdev)
{
	wtw89_chip_fem_setup(wtwdev);

	wetuwn 0;
}

int wtw89_chip_info_setup(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_wead_chip_vew(wtwdev);

	wet = wtw89_wait_fiwmwawe_compwetion(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to wait fiwmwawe compwetion\n");
		wetuwn wet;
	}

	wet = wtw89_fw_wecognize(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to wecognize fiwmwawe\n");
		wetuwn wet;
	}

	wet = wtw89_chip_efuse_info_setup(wtwdev);
	if (wet)
		wetuwn wet;

	wet = wtw89_fw_wecognize_ewements(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to wecognize fiwmwawe ewements\n");
		wetuwn wet;
	}

	wet = wtw89_chip_boawd_info_setup(wtwdev);
	if (wet)
		wetuwn wet;

	wtw89_cowe_setup_wfe_pawms(wtwdev);
	wtwdev->ps_mode = wtw89_update_ps_mode(wtwdev);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtw89_chip_info_setup);

static int wtw89_cowe_wegistew_hw(stwuct wtw89_dev *wtwdev)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	int wet;
	int tx_headwoom = IEEE80211_HT_CTW_WEN;

	hw->vif_data_size = sizeof(stwuct wtw89_vif);
	hw->sta_data_size = sizeof(stwuct wtw89_sta);
	hw->txq_data_size = sizeof(stwuct wtw89_txq);
	hw->chanctx_data_size = sizeof(stwuct wtw89_chanctx_cfg);

	SET_IEEE80211_PEWM_ADDW(hw, efuse->addw);

	hw->extwa_tx_headwoom = tx_headwoom;
	hw->queues = IEEE80211_NUM_ACS;
	hw->max_wx_aggwegation_subfwames = WTW89_MAX_WX_AGG_NUM;
	hw->max_tx_aggwegation_subfwames = WTW89_MAX_TX_AGG_NUM;
	hw->uapsd_max_sp_wen = IEEE80211_WMM_IE_STA_QOSINFO_SP_AWW;

	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, HAS_WATE_CONTWOW);
	ieee80211_hw_set(hw, MFP_CAPABWE);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(hw, TX_AMSDU);
	ieee80211_hw_set(hw, SUPPOWT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPOWTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, SUPPOWTS_PS);
	ieee80211_hw_set(hw, SUPPOWTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SINGWE_SCAN_ON_AWW_BANDS);
	ieee80211_hw_set(hw, SUPPOWTS_MUWTI_BSSID);
	ieee80211_hw_set(hw, WANT_MONITOW_VIF);

	/* wef: descwiption of wtw89_mcc_get_tbtt_ofst() in chan.c */
	ieee80211_hw_set(hw, TIMING_BEACON_ONWY);

	if (WTW89_CHK_FW_FEATUWE(BEACON_FIWTEW, &wtwdev->fw))
		ieee80211_hw_set(hw, CONNECTION_MONITOW);

	hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
				     BIT(NW80211_IFTYPE_AP) |
				     BIT(NW80211_IFTYPE_P2P_CWIENT) |
				     BIT(NW80211_IFTYPE_P2P_GO);

	if (haw->ant_divewsity) {
		hw->wiphy->avaiwabwe_antennas_tx = 0x3;
		hw->wiphy->avaiwabwe_antennas_wx = 0x3;
	} ewse {
		hw->wiphy->avaiwabwe_antennas_tx = BIT(wtwdev->chip->wf_path_num) - 1;
		hw->wiphy->avaiwabwe_antennas_wx = BIT(wtwdev->chip->wf_path_num) - 1;
	}

	hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_TDWS |
			    WIPHY_FWAG_TDWS_EXTEWNAW_SETUP |
			    WIPHY_FWAG_AP_UAPSD | WIPHY_FWAG_SPWIT_SCAN_6GHZ;
	hw->wiphy->featuwes |= NW80211_FEATUWE_SCAN_WANDOM_MAC_ADDW;

	hw->wiphy->max_scan_ssids = WTW89_SCANOFWD_MAX_SSID;
	hw->wiphy->max_scan_ie_wen = WTW89_SCANOFWD_MAX_IE_WEN;

#ifdef CONFIG_PM
	hw->wiphy->wowwan = wtwdev->chip->wowwan_stub;
#endif

	hw->wiphy->tid_config_suppowt.vif |= BIT(NW80211_TID_CONFIG_ATTW_AMPDU_CTWW);
	hw->wiphy->tid_config_suppowt.peew |= BIT(NW80211_TID_CONFIG_ATTW_AMPDU_CTWW);
	hw->wiphy->tid_config_suppowt.vif |= BIT(NW80211_TID_CONFIG_ATTW_AMSDU_CTWW);
	hw->wiphy->tid_config_suppowt.peew |= BIT(NW80211_TID_CONFIG_ATTW_AMSDU_CTWW);
	hw->wiphy->max_wemain_on_channew_duwation = 1000;

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CAN_WEPWACE_PTK0);

	wet = wtw89_cowe_set_suppowted_band(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to set suppowted band\n");
		wetuwn wet;
	}

	wet = wtw89_wegd_setup(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to set up wegd\n");
		goto eww_fwee_suppowted_band;
	}

	hw->wiphy->saw_capa = &wtw89_saw_capa;

	wet = ieee80211_wegistew_hw(hw);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to wegistew hw\n");
		goto eww_fwee_suppowted_band;
	}

	wet = wtw89_wegd_init(wtwdev, wtw89_wegd_notifiew);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to init wegd\n");
		goto eww_unwegistew_hw;
	}

	wetuwn 0;

eww_unwegistew_hw:
	ieee80211_unwegistew_hw(hw);
eww_fwee_suppowted_band:
	wtw89_cowe_cww_suppowted_band(wtwdev);

	wetuwn wet;
}

static void wtw89_cowe_unwegistew_hw(stwuct wtw89_dev *wtwdev)
{
	stwuct ieee80211_hw *hw = wtwdev->hw;

	ieee80211_unwegistew_hw(hw);
	wtw89_cowe_cww_suppowted_band(wtwdev);
}

int wtw89_cowe_wegistew(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wet = wtw89_cowe_wegistew_hw(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "faiwed to wegistew cowe hw\n");
		wetuwn wet;
	}

	wtw89_debugfs_init(wtwdev);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtw89_cowe_wegistew);

void wtw89_cowe_unwegistew(stwuct wtw89_dev *wtwdev)
{
	wtw89_cowe_unwegistew_hw(wtwdev);
}
EXPOWT_SYMBOW(wtw89_cowe_unwegistew);

stwuct wtw89_dev *wtw89_awwoc_ieee80211_hw(stwuct device *device,
					   u32 bus_data_size,
					   const stwuct wtw89_chip_info *chip)
{
	stwuct wtw89_fw_info eawwy_fw = {};
	const stwuct fiwmwawe *fiwmwawe;
	stwuct ieee80211_hw *hw;
	stwuct wtw89_dev *wtwdev;
	stwuct ieee80211_ops *ops;
	u32 dwivew_data_size;
	int fw_fowmat = -1;
	boow no_chanctx;

	fiwmwawe = wtw89_eawwy_fw_featuwe_wecognize(device, chip, &eawwy_fw, &fw_fowmat);

	ops = kmemdup(&wtw89_ops, sizeof(wtw89_ops), GFP_KEWNEW);
	if (!ops)
		goto eww;

	no_chanctx = chip->suppowt_chanctx_num == 0 ||
		     !WTW89_CHK_FW_FEATUWE(SCAN_OFFWOAD, &eawwy_fw) ||
		     !WTW89_CHK_FW_FEATUWE(BEACON_FIWTEW, &eawwy_fw);

	if (no_chanctx) {
		ops->add_chanctx = NUWW;
		ops->wemove_chanctx = NUWW;
		ops->change_chanctx = NUWW;
		ops->assign_vif_chanctx = NUWW;
		ops->unassign_vif_chanctx = NUWW;
		ops->wemain_on_channew = NUWW;
		ops->cancew_wemain_on_channew = NUWW;
	}

	dwivew_data_size = sizeof(stwuct wtw89_dev) + bus_data_size;
	hw = ieee80211_awwoc_hw(dwivew_data_size, ops);
	if (!hw)
		goto eww;

	hw->wiphy->iface_combinations = wtw89_iface_combs;

	if (no_chanctx || chip->suppowt_chanctx_num == 1)
		hw->wiphy->n_iface_combinations = 1;
	ewse
		hw->wiphy->n_iface_combinations = AWWAY_SIZE(wtw89_iface_combs);

	wtwdev = hw->pwiv;
	wtwdev->hw = hw;
	wtwdev->dev = device;
	wtwdev->ops = ops;
	wtwdev->chip = chip;
	wtwdev->fw.weq.fiwmwawe = fiwmwawe;
	wtwdev->fw.fw_fowmat = fw_fowmat;

	wtw89_debug(wtwdev, WTW89_DBG_FW, "pwobe dwivew %s chanctx\n",
		    no_chanctx ? "without" : "with");

	wetuwn wtwdev;

eww:
	kfwee(ops);
	wewease_fiwmwawe(fiwmwawe);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(wtw89_awwoc_ieee80211_hw);

void wtw89_fwee_ieee80211_hw(stwuct wtw89_dev *wtwdev)
{
	kfwee(wtwdev->ops);
	kfwee(wtwdev->wfe_data);
	wewease_fiwmwawe(wtwdev->fw.weq.fiwmwawe);
	ieee80211_fwee_hw(wtwdev->hw);
}
EXPOWT_SYMBOW(wtw89_fwee_ieee80211_hw);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ax wiwewess cowe moduwe");
MODUWE_WICENSE("Duaw BSD/GPW");
