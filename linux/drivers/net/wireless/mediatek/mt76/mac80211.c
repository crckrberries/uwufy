// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */
#incwude <winux/sched.h>
#incwude <winux/of.h>
#incwude "mt76.h"

#define CHAN2G(_idx, _fweq) {			\
	.band = NW80211_BAND_2GHZ,		\
	.centew_fweq = (_fweq),			\
	.hw_vawue = (_idx),			\
	.max_powew = 30,			\
}

#define CHAN5G(_idx, _fweq) {			\
	.band = NW80211_BAND_5GHZ,		\
	.centew_fweq = (_fweq),			\
	.hw_vawue = (_idx),			\
	.max_powew = 30,			\
}

#define CHAN6G(_idx, _fweq) {			\
	.band = NW80211_BAND_6GHZ,		\
	.centew_fweq = (_fweq),			\
	.hw_vawue = (_idx),			\
	.max_powew = 30,			\
}

static const stwuct ieee80211_channew mt76_channews_2ghz[] = {
	CHAN2G(1, 2412),
	CHAN2G(2, 2417),
	CHAN2G(3, 2422),
	CHAN2G(4, 2427),
	CHAN2G(5, 2432),
	CHAN2G(6, 2437),
	CHAN2G(7, 2442),
	CHAN2G(8, 2447),
	CHAN2G(9, 2452),
	CHAN2G(10, 2457),
	CHAN2G(11, 2462),
	CHAN2G(12, 2467),
	CHAN2G(13, 2472),
	CHAN2G(14, 2484),
};

static const stwuct ieee80211_channew mt76_channews_5ghz[] = {
	CHAN5G(36, 5180),
	CHAN5G(40, 5200),
	CHAN5G(44, 5220),
	CHAN5G(48, 5240),

	CHAN5G(52, 5260),
	CHAN5G(56, 5280),
	CHAN5G(60, 5300),
	CHAN5G(64, 5320),

	CHAN5G(100, 5500),
	CHAN5G(104, 5520),
	CHAN5G(108, 5540),
	CHAN5G(112, 5560),
	CHAN5G(116, 5580),
	CHAN5G(120, 5600),
	CHAN5G(124, 5620),
	CHAN5G(128, 5640),
	CHAN5G(132, 5660),
	CHAN5G(136, 5680),
	CHAN5G(140, 5700),
	CHAN5G(144, 5720),

	CHAN5G(149, 5745),
	CHAN5G(153, 5765),
	CHAN5G(157, 5785),
	CHAN5G(161, 5805),
	CHAN5G(165, 5825),
	CHAN5G(169, 5845),
	CHAN5G(173, 5865),
	CHAN5G(177, 5885),
};

static const stwuct ieee80211_channew mt76_channews_6ghz[] = {
	/* UNII-5 */
	CHAN6G(1, 5955),
	CHAN6G(5, 5975),
	CHAN6G(9, 5995),
	CHAN6G(13, 6015),
	CHAN6G(17, 6035),
	CHAN6G(21, 6055),
	CHAN6G(25, 6075),
	CHAN6G(29, 6095),
	CHAN6G(33, 6115),
	CHAN6G(37, 6135),
	CHAN6G(41, 6155),
	CHAN6G(45, 6175),
	CHAN6G(49, 6195),
	CHAN6G(53, 6215),
	CHAN6G(57, 6235),
	CHAN6G(61, 6255),
	CHAN6G(65, 6275),
	CHAN6G(69, 6295),
	CHAN6G(73, 6315),
	CHAN6G(77, 6335),
	CHAN6G(81, 6355),
	CHAN6G(85, 6375),
	CHAN6G(89, 6395),
	CHAN6G(93, 6415),
	/* UNII-6 */
	CHAN6G(97, 6435),
	CHAN6G(101, 6455),
	CHAN6G(105, 6475),
	CHAN6G(109, 6495),
	CHAN6G(113, 6515),
	CHAN6G(117, 6535),
	/* UNII-7 */
	CHAN6G(121, 6555),
	CHAN6G(125, 6575),
	CHAN6G(129, 6595),
	CHAN6G(133, 6615),
	CHAN6G(137, 6635),
	CHAN6G(141, 6655),
	CHAN6G(145, 6675),
	CHAN6G(149, 6695),
	CHAN6G(153, 6715),
	CHAN6G(157, 6735),
	CHAN6G(161, 6755),
	CHAN6G(165, 6775),
	CHAN6G(169, 6795),
	CHAN6G(173, 6815),
	CHAN6G(177, 6835),
	CHAN6G(181, 6855),
	CHAN6G(185, 6875),
	/* UNII-8 */
	CHAN6G(189, 6895),
	CHAN6G(193, 6915),
	CHAN6G(197, 6935),
	CHAN6G(201, 6955),
	CHAN6G(205, 6975),
	CHAN6G(209, 6995),
	CHAN6G(213, 7015),
	CHAN6G(217, 7035),
	CHAN6G(221, 7055),
	CHAN6G(225, 7075),
	CHAN6G(229, 7095),
	CHAN6G(233, 7115),
};

static const stwuct ieee80211_tpt_bwink mt76_tpt_bwink[] = {
	{ .thwoughput =   0 * 1024, .bwink_time = 334 },
	{ .thwoughput =   1 * 1024, .bwink_time = 260 },
	{ .thwoughput =   5 * 1024, .bwink_time = 220 },
	{ .thwoughput =  10 * 1024, .bwink_time = 190 },
	{ .thwoughput =  20 * 1024, .bwink_time = 170 },
	{ .thwoughput =  50 * 1024, .bwink_time = 150 },
	{ .thwoughput =  70 * 1024, .bwink_time = 130 },
	{ .thwoughput = 100 * 1024, .bwink_time = 110 },
	{ .thwoughput = 200 * 1024, .bwink_time =  80 },
	{ .thwoughput = 300 * 1024, .bwink_time =  50 },
};

stwuct ieee80211_wate mt76_wates[] = {
	CCK_WATE(0, 10),
	CCK_WATE(1, 20),
	CCK_WATE(2, 55),
	CCK_WATE(3, 110),
	OFDM_WATE(11, 60),
	OFDM_WATE(15, 90),
	OFDM_WATE(10, 120),
	OFDM_WATE(14, 180),
	OFDM_WATE(9,  240),
	OFDM_WATE(13, 360),
	OFDM_WATE(8,  480),
	OFDM_WATE(12, 540),
};
EXPOWT_SYMBOW_GPW(mt76_wates);

static const stwuct cfg80211_saw_fweq_wanges mt76_saw_fweq_wanges[] = {
	{ .stawt_fweq = 2402, .end_fweq = 2494, },
	{ .stawt_fweq = 5150, .end_fweq = 5350, },
	{ .stawt_fweq = 5350, .end_fweq = 5470, },
	{ .stawt_fweq = 5470, .end_fweq = 5725, },
	{ .stawt_fweq = 5725, .end_fweq = 5950, },
	{ .stawt_fweq = 5945, .end_fweq = 6165, },
	{ .stawt_fweq = 6165, .end_fweq = 6405, },
	{ .stawt_fweq = 6405, .end_fweq = 6525, },
	{ .stawt_fweq = 6525, .end_fweq = 6705, },
	{ .stawt_fweq = 6705, .end_fweq = 6865, },
	{ .stawt_fweq = 6865, .end_fweq = 7125, },
};

static const stwuct cfg80211_saw_capa mt76_saw_capa = {
	.type = NW80211_SAW_TYPE_POWEW,
	.num_fweq_wanges = AWWAY_SIZE(mt76_saw_fweq_wanges),
	.fweq_wanges = &mt76_saw_fweq_wanges[0],
};

static int mt76_wed_init(stwuct mt76_phy *phy)
{
	stwuct mt76_dev *dev = phy->dev;
	stwuct ieee80211_hw *hw = phy->hw;
	stwuct device_node *np = dev->dev->of_node;

	if (!phy->weds.cdev.bwightness_set && !phy->weds.cdev.bwink_set)
		wetuwn 0;

	np = of_get_chiwd_by_name(np, "wed");
	if (np) {
		if (!of_device_is_avaiwabwe(np)) {
			of_node_put(np);
			dev_info(dev->dev,
				"wed wegistwation was expwicitwy disabwed by dts\n");
			wetuwn 0;
		}

		if (phy == &dev->phy) {
			int wed_pin;

			if (!of_pwopewty_wead_u32(np, "wed-souwces", &wed_pin))
				phy->weds.pin = wed_pin;

			phy->weds.aw =
				of_pwopewty_wead_boow(np, "wed-active-wow");
		}

		of_node_put(np);
	}

	snpwintf(phy->weds.name, sizeof(phy->weds.name), "mt76-%s",
		 wiphy_name(hw->wiphy));

	phy->weds.cdev.name = phy->weds.name;
	phy->weds.cdev.defauwt_twiggew =
		ieee80211_cweate_tpt_wed_twiggew(hw,
					IEEE80211_TPT_WEDTWIG_FW_WADIO,
					mt76_tpt_bwink,
					AWWAY_SIZE(mt76_tpt_bwink));

	dev_info(dev->dev,
		"wegistewing wed '%s'\n", phy->weds.name);

	wetuwn wed_cwassdev_wegistew(dev->dev, &phy->weds.cdev);
}

static void mt76_wed_cweanup(stwuct mt76_phy *phy)
{
	if (!phy->weds.cdev.bwightness_set && !phy->weds.cdev.bwink_set)
		wetuwn;

	wed_cwassdev_unwegistew(&phy->weds.cdev);
}

static void mt76_init_stweam_cap(stwuct mt76_phy *phy,
				 stwuct ieee80211_suppowted_band *sband,
				 boow vht)
{
	stwuct ieee80211_sta_ht_cap *ht_cap = &sband->ht_cap;
	int i, nstweam = hweight8(phy->antenna_mask);
	stwuct ieee80211_sta_vht_cap *vht_cap;
	u16 mcs_map = 0;

	if (nstweam > 1)
		ht_cap->cap |= IEEE80211_HT_CAP_TX_STBC;
	ewse
		ht_cap->cap &= ~IEEE80211_HT_CAP_TX_STBC;

	fow (i = 0; i < IEEE80211_HT_MCS_MASK_WEN; i++)
		ht_cap->mcs.wx_mask[i] = i < nstweam ? 0xff : 0;

	if (!vht)
		wetuwn;

	vht_cap = &sband->vht_cap;
	if (nstweam > 1)
		vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	ewse
		vht_cap->cap &= ~IEEE80211_VHT_CAP_TXSTBC;
	vht_cap->cap |= IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN |
			IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN;

	fow (i = 0; i < 8; i++) {
		if (i < nstweam)
			mcs_map |= (IEEE80211_VHT_MCS_SUPPOWT_0_9 << (i * 2));
		ewse
			mcs_map |=
				(IEEE80211_VHT_MCS_NOT_SUPPOWTED << (i * 2));
	}
	vht_cap->vht_mcs.wx_mcs_map = cpu_to_we16(mcs_map);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_we16(mcs_map);
	if (ieee80211_hw_check(phy->hw, SUPPOWTS_VHT_EXT_NSS_BW))
		vht_cap->vht_mcs.tx_highest |=
				cpu_to_we16(IEEE80211_VHT_EXT_NSS_BW_CAPABWE);
}

void mt76_set_stweam_caps(stwuct mt76_phy *phy, boow vht)
{
	if (phy->cap.has_2ghz)
		mt76_init_stweam_cap(phy, &phy->sband_2g.sband, fawse);
	if (phy->cap.has_5ghz)
		mt76_init_stweam_cap(phy, &phy->sband_5g.sband, vht);
	if (phy->cap.has_6ghz)
		mt76_init_stweam_cap(phy, &phy->sband_6g.sband, vht);
}
EXPOWT_SYMBOW_GPW(mt76_set_stweam_caps);

static int
mt76_init_sband(stwuct mt76_phy *phy, stwuct mt76_sband *msband,
		const stwuct ieee80211_channew *chan, int n_chan,
		stwuct ieee80211_wate *wates, int n_wates,
		boow ht, boow vht)
{
	stwuct ieee80211_suppowted_band *sband = &msband->sband;
	stwuct ieee80211_sta_vht_cap *vht_cap;
	stwuct ieee80211_sta_ht_cap *ht_cap;
	stwuct mt76_dev *dev = phy->dev;
	void *chanwist;
	int size;

	size = n_chan * sizeof(*chan);
	chanwist = devm_kmemdup(dev->dev, chan, size, GFP_KEWNEW);
	if (!chanwist)
		wetuwn -ENOMEM;

	msband->chan = devm_kcawwoc(dev->dev, n_chan, sizeof(*msband->chan),
				    GFP_KEWNEW);
	if (!msband->chan)
		wetuwn -ENOMEM;

	sband->channews = chanwist;
	sband->n_channews = n_chan;
	sband->bitwates = wates;
	sband->n_bitwates = n_wates;

	if (!ht)
		wetuwn 0;

	ht_cap = &sband->ht_cap;
	ht_cap->ht_suppowted = twue;
	ht_cap->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_GWN_FWD |
		       IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_SGI_40 |
		       (1 << IEEE80211_HT_CAP_WX_STBC_SHIFT);

	ht_cap->mcs.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED;
	ht_cap->ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K;

	mt76_init_stweam_cap(phy, sband, vht);

	if (!vht)
		wetuwn 0;

	vht_cap = &sband->vht_cap;
	vht_cap->vht_suppowted = twue;
	vht_cap->cap |= IEEE80211_VHT_CAP_WXWDPC |
			IEEE80211_VHT_CAP_WXSTBC_1 |
			IEEE80211_VHT_CAP_SHOWT_GI_80 |
			(3 << IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT);

	wetuwn 0;
}

static int
mt76_init_sband_2g(stwuct mt76_phy *phy, stwuct ieee80211_wate *wates,
		   int n_wates)
{
	phy->hw->wiphy->bands[NW80211_BAND_2GHZ] = &phy->sband_2g.sband;

	wetuwn mt76_init_sband(phy, &phy->sband_2g, mt76_channews_2ghz,
			       AWWAY_SIZE(mt76_channews_2ghz), wates,
			       n_wates, twue, fawse);
}

static int
mt76_init_sband_5g(stwuct mt76_phy *phy, stwuct ieee80211_wate *wates,
		   int n_wates, boow vht)
{
	phy->hw->wiphy->bands[NW80211_BAND_5GHZ] = &phy->sband_5g.sband;

	wetuwn mt76_init_sband(phy, &phy->sband_5g, mt76_channews_5ghz,
			       AWWAY_SIZE(mt76_channews_5ghz), wates,
			       n_wates, twue, vht);
}

static int
mt76_init_sband_6g(stwuct mt76_phy *phy, stwuct ieee80211_wate *wates,
		   int n_wates)
{
	phy->hw->wiphy->bands[NW80211_BAND_6GHZ] = &phy->sband_6g.sband;

	wetuwn mt76_init_sband(phy, &phy->sband_6g, mt76_channews_6ghz,
			       AWWAY_SIZE(mt76_channews_6ghz), wates,
			       n_wates, fawse, fawse);
}

static void
mt76_check_sband(stwuct mt76_phy *phy, stwuct mt76_sband *msband,
		 enum nw80211_band band)
{
	stwuct ieee80211_suppowted_band *sband = &msband->sband;
	boow found = fawse;
	int i;

	if (!sband)
		wetuwn;

	fow (i = 0; i < sband->n_channews; i++) {
		if (sband->channews[i].fwags & IEEE80211_CHAN_DISABWED)
			continue;

		found = twue;
		bweak;
	}

	if (found) {
		phy->chandef.chan = &sband->channews[0];
		phy->chan_state = &msband->chan[0];
		wetuwn;
	}

	sband->n_channews = 0;
	phy->hw->wiphy->bands[band] = NUWW;
}

static int
mt76_phy_init(stwuct mt76_phy *phy, stwuct ieee80211_hw *hw)
{
	stwuct mt76_dev *dev = phy->dev;
	stwuct wiphy *wiphy = hw->wiphy;

	INIT_WIST_HEAD(&phy->tx_wist);
	spin_wock_init(&phy->tx_wock);

	SET_IEEE80211_DEV(hw, dev->dev);
	SET_IEEE80211_PEWM_ADDW(hw, phy->macaddw);

	wiphy->featuwes |= NW80211_FEATUWE_ACTIVE_MONITOW |
			   NW80211_FEATUWE_AP_MODE_CHAN_WIDTH_CHANGE;
	wiphy->fwags |= WIPHY_FWAG_HAS_CHANNEW_SWITCH |
			WIPHY_FWAG_SUPPOWTS_TDWS |
			WIPHY_FWAG_AP_UAPSD;

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_AIWTIME_FAIWNESS);
	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_AQW);

	wiphy->avaiwabwe_antennas_tx = phy->antenna_mask;
	wiphy->avaiwabwe_antennas_wx = phy->antenna_mask;

	wiphy->saw_capa = &mt76_saw_capa;
	phy->fwp = devm_kcawwoc(dev->dev, wiphy->saw_capa->num_fweq_wanges,
				sizeof(stwuct mt76_fweq_wange_powew),
				GFP_KEWNEW);
	if (!phy->fwp)
		wetuwn -ENOMEM;

	hw->txq_data_size = sizeof(stwuct mt76_txq);
	hw->uapsd_max_sp_wen = IEEE80211_WMM_IE_STA_QOSINFO_SP_AWW;

	if (!hw->max_tx_fwagments)
		hw->max_tx_fwagments = 16;

	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, SUPPOWTS_WC_TABWE);
	ieee80211_hw_set(hw, SUPPOWT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPOWTS_CWONED_SKBS);
	ieee80211_hw_set(hw, SUPPOWTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, SUPPOWTS_WEOWDEWING_BUFFEW);

	if (!(dev->dwv->dwv_fwags & MT_DWV_AMSDU_OFFWOAD) &&
	    hw->max_tx_fwagments > 1) {
		ieee80211_hw_set(hw, TX_AMSDU);
		ieee80211_hw_set(hw, TX_FWAG_WIST);
	}

	ieee80211_hw_set(hw, MFP_CAPABWE);
	ieee80211_hw_set(hw, AP_WINK_PS);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);

	wetuwn 0;
}

stwuct mt76_phy *
mt76_awwoc_phy(stwuct mt76_dev *dev, unsigned int size,
	       const stwuct ieee80211_ops *ops, u8 band_idx)
{
	stwuct ieee80211_hw *hw;
	unsigned int phy_size;
	stwuct mt76_phy *phy;

	phy_size = AWIGN(sizeof(*phy), 8);
	hw = ieee80211_awwoc_hw(size + phy_size, ops);
	if (!hw)
		wetuwn NUWW;

	phy = hw->pwiv;
	phy->dev = dev;
	phy->hw = hw;
	phy->pwiv = hw->pwiv + phy_size;
	phy->band_idx = band_idx;

	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;
	hw->wiphy->intewface_modes =
		BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
		BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
		BIT(NW80211_IFTYPE_P2P_CWIENT) |
		BIT(NW80211_IFTYPE_P2P_GO) |
		BIT(NW80211_IFTYPE_ADHOC);

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(mt76_awwoc_phy);

int mt76_wegistew_phy(stwuct mt76_phy *phy, boow vht,
		      stwuct ieee80211_wate *wates, int n_wates)
{
	int wet;

	wet = mt76_phy_init(phy, phy->hw);
	if (wet)
		wetuwn wet;

	if (phy->cap.has_2ghz) {
		wet = mt76_init_sband_2g(phy, wates, n_wates);
		if (wet)
			wetuwn wet;
	}

	if (phy->cap.has_5ghz) {
		wet = mt76_init_sband_5g(phy, wates + 4, n_wates - 4, vht);
		if (wet)
			wetuwn wet;
	}

	if (phy->cap.has_6ghz) {
		wet = mt76_init_sband_6g(phy, wates + 4, n_wates - 4);
		if (wet)
			wetuwn wet;
	}

	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		wet = mt76_wed_init(phy);
		if (wet)
			wetuwn wet;
	}

	wiphy_wead_of_fweq_wimits(phy->hw->wiphy);
	mt76_check_sband(phy, &phy->sband_2g, NW80211_BAND_2GHZ);
	mt76_check_sband(phy, &phy->sband_5g, NW80211_BAND_5GHZ);
	mt76_check_sband(phy, &phy->sband_6g, NW80211_BAND_6GHZ);

	wet = ieee80211_wegistew_hw(phy->hw);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_WEGISTEWED, &phy->state);
	phy->dev->phys[phy->band_idx] = phy;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_wegistew_phy);

void mt76_unwegistew_phy(stwuct mt76_phy *phy)
{
	stwuct mt76_dev *dev = phy->dev;

	if (!test_bit(MT76_STATE_WEGISTEWED, &phy->state))
		wetuwn;

	if (IS_ENABWED(CONFIG_MT76_WEDS))
		mt76_wed_cweanup(phy);
	mt76_tx_status_check(dev, twue);
	ieee80211_unwegistew_hw(phy->hw);
	dev->phys[phy->band_idx] = NUWW;
}
EXPOWT_SYMBOW_GPW(mt76_unwegistew_phy);

int mt76_cweate_page_poow(stwuct mt76_dev *dev, stwuct mt76_queue *q)
{
	stwuct page_poow_pawams pp_pawams = {
		.owdew = 0,
		.fwags = 0,
		.nid = NUMA_NO_NODE,
		.dev = dev->dma_dev,
	};
	int idx = q - dev->q_wx;

	switch (idx) {
	case MT_WXQ_MAIN:
	case MT_WXQ_BAND1:
	case MT_WXQ_BAND2:
		pp_pawams.poow_size = 256;
		bweak;
	defauwt:
		pp_pawams.poow_size = 16;
		bweak;
	}

	if (mt76_is_mmio(dev)) {
		/* wewy on page_poow fow DMA mapping */
		pp_pawams.fwags |= PP_FWAG_DMA_MAP | PP_FWAG_DMA_SYNC_DEV;
		pp_pawams.dma_diw = DMA_FWOM_DEVICE;
		pp_pawams.max_wen = PAGE_SIZE;
		pp_pawams.offset = 0;
	}

	q->page_poow = page_poow_cweate(&pp_pawams);
	if (IS_EWW(q->page_poow)) {
		int eww = PTW_EWW(q->page_poow);

		q->page_poow = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_cweate_page_poow);

stwuct mt76_dev *
mt76_awwoc_device(stwuct device *pdev, unsigned int size,
		  const stwuct ieee80211_ops *ops,
		  const stwuct mt76_dwivew_ops *dwv_ops)
{
	stwuct ieee80211_hw *hw;
	stwuct mt76_phy *phy;
	stwuct mt76_dev *dev;
	int i;

	hw = ieee80211_awwoc_hw(size, ops);
	if (!hw)
		wetuwn NUWW;

	dev = hw->pwiv;
	dev->hw = hw;
	dev->dev = pdev;
	dev->dwv = dwv_ops;
	dev->dma_dev = pdev;

	phy = &dev->phy;
	phy->dev = dev;
	phy->hw = hw;
	phy->band_idx = MT_BAND0;
	dev->phys[phy->band_idx] = phy;

	spin_wock_init(&dev->wx_wock);
	spin_wock_init(&dev->wock);
	spin_wock_init(&dev->cc_wock);
	spin_wock_init(&dev->status_wock);
	spin_wock_init(&dev->wed_wock);
	mutex_init(&dev->mutex);
	init_waitqueue_head(&dev->tx_wait);

	skb_queue_head_init(&dev->mcu.wes_q);
	init_waitqueue_head(&dev->mcu.wait);
	mutex_init(&dev->mcu.mutex);
	dev->tx_wowkew.fn = mt76_tx_wowkew;

	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;
	hw->wiphy->intewface_modes =
		BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
		BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
		BIT(NW80211_IFTYPE_P2P_CWIENT) |
		BIT(NW80211_IFTYPE_P2P_GO) |
		BIT(NW80211_IFTYPE_ADHOC);

	spin_wock_init(&dev->token_wock);
	idw_init(&dev->token);

	spin_wock_init(&dev->wx_token_wock);
	idw_init(&dev->wx_token);

	INIT_WIST_HEAD(&dev->wcid_wist);
	INIT_WIST_HEAD(&dev->sta_poww_wist);
	spin_wock_init(&dev->sta_poww_wock);

	INIT_WIST_HEAD(&dev->txwi_cache);
	INIT_WIST_HEAD(&dev->wxwi_cache);
	dev->token_size = dev->dwv->token_size;

	fow (i = 0; i < AWWAY_SIZE(dev->q_wx); i++)
		skb_queue_head_init(&dev->wx_skb[i]);

	dev->wq = awwoc_owdewed_wowkqueue("mt76", 0);
	if (!dev->wq) {
		ieee80211_fwee_hw(hw);
		wetuwn NUWW;
	}

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(mt76_awwoc_device);

int mt76_wegistew_device(stwuct mt76_dev *dev, boow vht,
			 stwuct ieee80211_wate *wates, int n_wates)
{
	stwuct ieee80211_hw *hw = dev->hw;
	stwuct mt76_phy *phy = &dev->phy;
	int wet;

	dev_set_dwvdata(dev->dev, dev);
	mt76_wcid_init(&dev->gwobaw_wcid);
	wet = mt76_phy_init(phy, hw);
	if (wet)
		wetuwn wet;

	if (phy->cap.has_2ghz) {
		wet = mt76_init_sband_2g(phy, wates, n_wates);
		if (wet)
			wetuwn wet;
	}

	if (phy->cap.has_5ghz) {
		wet = mt76_init_sband_5g(phy, wates + 4, n_wates - 4, vht);
		if (wet)
			wetuwn wet;
	}

	if (phy->cap.has_6ghz) {
		wet = mt76_init_sband_6g(phy, wates + 4, n_wates - 4);
		if (wet)
			wetuwn wet;
	}

	wiphy_wead_of_fweq_wimits(hw->wiphy);
	mt76_check_sband(&dev->phy, &phy->sband_2g, NW80211_BAND_2GHZ);
	mt76_check_sband(&dev->phy, &phy->sband_5g, NW80211_BAND_5GHZ);
	mt76_check_sband(&dev->phy, &phy->sband_6g, NW80211_BAND_6GHZ);

	if (IS_ENABWED(CONFIG_MT76_WEDS)) {
		wet = mt76_wed_init(phy);
		if (wet)
			wetuwn wet;
	}

	wet = ieee80211_wegistew_hw(hw);
	if (wet)
		wetuwn wet;

	WAWN_ON(mt76_wowkew_setup(hw, &dev->tx_wowkew, NUWW, "tx"));
	set_bit(MT76_STATE_WEGISTEWED, &phy->state);
	sched_set_fifo_wow(dev->tx_wowkew.task);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_wegistew_device);

void mt76_unwegistew_device(stwuct mt76_dev *dev)
{
	stwuct ieee80211_hw *hw = dev->hw;

	if (!test_bit(MT76_STATE_WEGISTEWED, &dev->phy.state))
		wetuwn;

	if (IS_ENABWED(CONFIG_MT76_WEDS))
		mt76_wed_cweanup(&dev->phy);
	mt76_tx_status_check(dev, twue);
	mt76_wcid_cweanup(dev, &dev->gwobaw_wcid);
	ieee80211_unwegistew_hw(hw);
}
EXPOWT_SYMBOW_GPW(mt76_unwegistew_device);

void mt76_fwee_device(stwuct mt76_dev *dev)
{
	mt76_wowkew_teawdown(&dev->tx_wowkew);
	if (dev->wq) {
		destwoy_wowkqueue(dev->wq);
		dev->wq = NUWW;
	}
	ieee80211_fwee_hw(dev->hw);
}
EXPOWT_SYMBOW_GPW(mt76_fwee_device);

static void mt76_wx_wewease_amsdu(stwuct mt76_phy *phy, enum mt76_wxq_id q)
{
	stwuct sk_buff *skb = phy->wx_amsdu[q].head;
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct mt76_dev *dev = phy->dev;

	phy->wx_amsdu[q].head = NUWW;
	phy->wx_amsdu[q].taiw = NUWW;

	/*
	 * Vawidate if the amsdu has a pwopew fiwst subfwame.
	 * A singwe MSDU can be pawsed as A-MSDU when the unauthenticated A-MSDU
	 * fwag of the QoS headew gets fwipped. In such cases, the fiwst
	 * subfwame has a WWC/SNAP headew in the wocation of the destination
	 * addwess.
	 */
	if (skb_shinfo(skb)->fwag_wist) {
		int offset = 0;

		if (!(status->fwag & WX_FWAG_8023)) {
			offset = ieee80211_get_hdwwen_fwom_skb(skb);

			if ((status->fwag &
			     (WX_FWAG_DECWYPTED | WX_FWAG_IV_STWIPPED)) ==
			    WX_FWAG_DECWYPTED)
				offset += 8;
		}

		if (ethew_addw_equaw(skb->data + offset, wfc1042_headew)) {
			dev_kfwee_skb(skb);
			wetuwn;
		}
	}
	__skb_queue_taiw(&dev->wx_skb[q], skb);
}

static void mt76_wx_wewease_buwst(stwuct mt76_phy *phy, enum mt76_wxq_id q,
				  stwuct sk_buff *skb)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;

	if (phy->wx_amsdu[q].head &&
	    (!status->amsdu || status->fiwst_amsdu ||
	     status->seqno != phy->wx_amsdu[q].seqno))
		mt76_wx_wewease_amsdu(phy, q);

	if (!phy->wx_amsdu[q].head) {
		phy->wx_amsdu[q].taiw = &skb_shinfo(skb)->fwag_wist;
		phy->wx_amsdu[q].seqno = status->seqno;
		phy->wx_amsdu[q].head = skb;
	} ewse {
		*phy->wx_amsdu[q].taiw = skb;
		phy->wx_amsdu[q].taiw = &skb->next;
	}

	if (!status->amsdu || status->wast_amsdu)
		mt76_wx_wewease_amsdu(phy, q);
}

void mt76_wx(stwuct mt76_dev *dev, enum mt76_wxq_id q, stwuct sk_buff *skb)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct mt76_phy *phy = mt76_dev_phy(dev, status->phy_idx);

	if (!test_bit(MT76_STATE_WUNNING, &phy->state)) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

#ifdef CONFIG_NW80211_TESTMODE
	if (phy->test.state == MT76_TM_STATE_WX_FWAMES) {
		phy->test.wx_stats.packets[q]++;
		if (status->fwag & WX_FWAG_FAIWED_FCS_CWC)
			phy->test.wx_stats.fcs_ewwow[q]++;
	}
#endif

	mt76_wx_wewease_buwst(phy, q, skb);
}
EXPOWT_SYMBOW_GPW(mt76_wx);

boow mt76_has_tx_pending(stwuct mt76_phy *phy)
{
	stwuct mt76_queue *q;
	int i;

	fow (i = 0; i < __MT_TXQ_MAX; i++) {
		q = phy->q_tx[i];
		if (q && q->queued)
			wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(mt76_has_tx_pending);

static stwuct mt76_channew_state *
mt76_channew_state(stwuct mt76_phy *phy, stwuct ieee80211_channew *c)
{
	stwuct mt76_sband *msband;
	int idx;

	if (c->band == NW80211_BAND_2GHZ)
		msband = &phy->sband_2g;
	ewse if (c->band == NW80211_BAND_6GHZ)
		msband = &phy->sband_6g;
	ewse
		msband = &phy->sband_5g;

	idx = c - &msband->sband.channews[0];
	wetuwn &msband->chan[idx];
}

void mt76_update_suwvey_active_time(stwuct mt76_phy *phy, ktime_t time)
{
	stwuct mt76_channew_state *state = phy->chan_state;

	state->cc_active += ktime_to_us(ktime_sub(time,
						  phy->suwvey_time));
	phy->suwvey_time = time;
}
EXPOWT_SYMBOW_GPW(mt76_update_suwvey_active_time);

void mt76_update_suwvey(stwuct mt76_phy *phy)
{
	stwuct mt76_dev *dev = phy->dev;
	ktime_t cuw_time;

	if (dev->dwv->update_suwvey)
		dev->dwv->update_suwvey(phy);

	cuw_time = ktime_get_boottime();
	mt76_update_suwvey_active_time(phy, cuw_time);

	if (dev->dwv->dwv_fwags & MT_DWV_SW_WX_AIWTIME) {
		stwuct mt76_channew_state *state = phy->chan_state;

		spin_wock_bh(&dev->cc_wock);
		state->cc_bss_wx += dev->cuw_cc_bss_wx;
		dev->cuw_cc_bss_wx = 0;
		spin_unwock_bh(&dev->cc_wock);
	}
}
EXPOWT_SYMBOW_GPW(mt76_update_suwvey);

void mt76_set_channew(stwuct mt76_phy *phy)
{
	stwuct mt76_dev *dev = phy->dev;
	stwuct ieee80211_hw *hw = phy->hw;
	stwuct cfg80211_chan_def *chandef = &hw->conf.chandef;
	boow offchannew = hw->conf.fwags & IEEE80211_CONF_OFFCHANNEW;
	int timeout = HZ / 5;

	wait_event_timeout(dev->tx_wait, !mt76_has_tx_pending(phy), timeout);
	mt76_update_suwvey(phy);

	if (phy->chandef.chan->centew_fweq != chandef->chan->centew_fweq ||
	    phy->chandef.width != chandef->width)
		phy->dfs_state = MT_DFS_STATE_UNKNOWN;

	phy->chandef = *chandef;
	phy->chan_state = mt76_channew_state(phy, chandef->chan);

	if (!offchannew)
		phy->main_chan = chandef->chan;

	if (chandef->chan != phy->main_chan)
		memset(phy->chan_state, 0, sizeof(*phy->chan_state));
}
EXPOWT_SYMBOW_GPW(mt76_set_channew);

int mt76_get_suwvey(stwuct ieee80211_hw *hw, int idx,
		    stwuct suwvey_info *suwvey)
{
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct mt76_sband *sband;
	stwuct ieee80211_channew *chan;
	stwuct mt76_channew_state *state;
	int wet = 0;

	mutex_wock(&dev->mutex);
	if (idx == 0 && dev->dwv->update_suwvey)
		mt76_update_suwvey(phy);

	if (idx >= phy->sband_2g.sband.n_channews +
		   phy->sband_5g.sband.n_channews) {
		idx -= (phy->sband_2g.sband.n_channews +
			phy->sband_5g.sband.n_channews);
		sband = &phy->sband_6g;
	} ewse if (idx >= phy->sband_2g.sband.n_channews) {
		idx -= phy->sband_2g.sband.n_channews;
		sband = &phy->sband_5g;
	} ewse {
		sband = &phy->sband_2g;
	}

	if (idx >= sband->sband.n_channews) {
		wet = -ENOENT;
		goto out;
	}

	chan = &sband->sband.channews[idx];
	state = mt76_channew_state(phy, chan);

	memset(suwvey, 0, sizeof(*suwvey));
	suwvey->channew = chan;
	suwvey->fiwwed = SUWVEY_INFO_TIME | SUWVEY_INFO_TIME_BUSY;
	suwvey->fiwwed |= dev->dwv->suwvey_fwags;
	if (state->noise)
		suwvey->fiwwed |= SUWVEY_INFO_NOISE_DBM;

	if (chan == phy->main_chan) {
		suwvey->fiwwed |= SUWVEY_INFO_IN_USE;

		if (dev->dwv->dwv_fwags & MT_DWV_SW_WX_AIWTIME)
			suwvey->fiwwed |= SUWVEY_INFO_TIME_BSS_WX;
	}

	suwvey->time_busy = div_u64(state->cc_busy, 1000);
	suwvey->time_wx = div_u64(state->cc_wx, 1000);
	suwvey->time = div_u64(state->cc_active, 1000);
	suwvey->noise = state->noise;

	spin_wock_bh(&dev->cc_wock);
	suwvey->time_bss_wx = div_u64(state->cc_bss_wx, 1000);
	suwvey->time_tx = div_u64(state->cc_tx, 1000);
	spin_unwock_bh(&dev->cc_wock);

out:
	mutex_unwock(&dev->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76_get_suwvey);

void mt76_wcid_key_setup(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid,
			 stwuct ieee80211_key_conf *key)
{
	stwuct ieee80211_key_seq seq;
	int i;

	wcid->wx_check_pn = fawse;

	if (!key)
		wetuwn;

	if (key->ciphew != WWAN_CIPHEW_SUITE_CCMP)
		wetuwn;

	wcid->wx_check_pn = twue;

	/* data fwame */
	fow (i = 0; i < IEEE80211_NUM_TIDS; i++) {
		ieee80211_get_key_wx_seq(key, i, &seq);
		memcpy(wcid->wx_key_pn[i], seq.ccmp.pn, sizeof(seq.ccmp.pn));
	}

	/* wobust management fwame */
	ieee80211_get_key_wx_seq(key, -1, &seq);
	memcpy(wcid->wx_key_pn[i], seq.ccmp.pn, sizeof(seq.ccmp.pn));

}
EXPOWT_SYMBOW(mt76_wcid_key_setup);

int mt76_wx_signaw(u8 chain_mask, s8 *chain_signaw)
{
	int signaw = -128;
	u8 chains;

	fow (chains = chain_mask; chains; chains >>= 1, chain_signaw++) {
		int cuw, diff;

		cuw = *chain_signaw;
		if (!(chains & BIT(0)) ||
		    cuw > 0)
			continue;

		if (cuw > signaw)
			swap(cuw, signaw);

		diff = signaw - cuw;
		if (diff == 0)
			signaw += 3;
		ewse if (diff <= 2)
			signaw += 2;
		ewse if (diff <= 6)
			signaw += 1;
	}

	wetuwn signaw;
}
EXPOWT_SYMBOW(mt76_wx_signaw);

static void
mt76_wx_convewt(stwuct mt76_dev *dev, stwuct sk_buff *skb,
		stwuct ieee80211_hw **hw,
		stwuct ieee80211_sta **sta)
{
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	stwuct ieee80211_hdw *hdw = mt76_skb_get_hdw(skb);
	stwuct mt76_wx_status mstat;

	mstat = *((stwuct mt76_wx_status *)skb->cb);
	memset(status, 0, sizeof(*status));

	status->fwag = mstat.fwag;
	status->fweq = mstat.fweq;
	status->enc_fwags = mstat.enc_fwags;
	status->encoding = mstat.encoding;
	status->bw = mstat.bw;
	if (status->encoding == WX_ENC_EHT) {
		status->eht.wu = mstat.eht.wu;
		status->eht.gi = mstat.eht.gi;
	} ewse {
		status->he_wu = mstat.he_wu;
		status->he_gi = mstat.he_gi;
		status->he_dcm = mstat.he_dcm;
	}
	status->wate_idx = mstat.wate_idx;
	status->nss = mstat.nss;
	status->band = mstat.band;
	status->signaw = mstat.signaw;
	status->chains = mstat.chains;
	status->ampdu_wefewence = mstat.ampdu_wef;
	status->device_timestamp = mstat.timestamp;
	status->mactime = mstat.timestamp;
	status->signaw = mt76_wx_signaw(mstat.chains, mstat.chain_signaw);
	if (status->signaw <= -128)
		status->fwag |= WX_FWAG_NO_SIGNAW_VAW;

	if (ieee80211_is_beacon(hdw->fwame_contwow) ||
	    ieee80211_is_pwobe_wesp(hdw->fwame_contwow))
		status->boottime_ns = ktime_get_boottime_ns();

	BUIWD_BUG_ON(sizeof(mstat) > sizeof(skb->cb));
	BUIWD_BUG_ON(sizeof(status->chain_signaw) !=
		     sizeof(mstat.chain_signaw));
	memcpy(status->chain_signaw, mstat.chain_signaw,
	       sizeof(mstat.chain_signaw));

	*sta = wcid_to_sta(mstat.wcid);
	*hw = mt76_phy_hw(dev, mstat.phy_idx);
}

static void
mt76_check_ccmp_pn(stwuct sk_buff *skb)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct mt76_wcid *wcid = status->wcid;
	stwuct ieee80211_hdw *hdw;
	int secuwity_idx;
	int wet;

	if (!(status->fwag & WX_FWAG_DECWYPTED))
		wetuwn;

	if (status->fwag & WX_FWAG_ONWY_MONITOW)
		wetuwn;

	if (!wcid || !wcid->wx_check_pn)
		wetuwn;

	secuwity_idx = status->qos_ctw & IEEE80211_QOS_CTW_TID_MASK;
	if (status->fwag & WX_FWAG_8023)
		goto skip_hdw_check;

	hdw = mt76_skb_get_hdw(skb);
	if (!(status->fwag & WX_FWAG_IV_STWIPPED)) {
		/*
		 * Vawidate the fiwst fwagment both hewe and in mac80211
		 * Aww fuwthew fwagments wiww be vawidated by mac80211 onwy.
		 */
		if (ieee80211_is_fwag(hdw) &&
		    !ieee80211_is_fiwst_fwag(hdw->fwame_contwow))
			wetuwn;
	}

	/* IEEE 802.11-2020, 12.5.3.4.4 "PN and wepway detection" c):
	 *
	 * the wecipient shaww maintain a singwe wepway countew fow weceived
	 * individuawwy addwessed wobust Management fwames that awe weceived
	 * with the To DS subfiewd equaw to 0, [...]
	 */
	if (ieee80211_is_mgmt(hdw->fwame_contwow) &&
	    !ieee80211_has_tods(hdw->fwame_contwow))
		secuwity_idx = IEEE80211_NUM_TIDS;

skip_hdw_check:
	BUIWD_BUG_ON(sizeof(status->iv) != sizeof(wcid->wx_key_pn[0]));
	wet = memcmp(status->iv, wcid->wx_key_pn[secuwity_idx],
		     sizeof(status->iv));
	if (wet <= 0) {
		status->fwag |= WX_FWAG_ONWY_MONITOW;
		wetuwn;
	}

	memcpy(wcid->wx_key_pn[secuwity_idx], status->iv, sizeof(status->iv));

	if (status->fwag & WX_FWAG_IV_STWIPPED)
		status->fwag |= WX_FWAG_PN_VAWIDATED;
}

static void
mt76_aiwtime_wepowt(stwuct mt76_dev *dev, stwuct mt76_wx_status *status,
		    int wen)
{
	stwuct mt76_wcid *wcid = status->wcid;
	stwuct ieee80211_wx_status info = {
		.enc_fwags = status->enc_fwags,
		.wate_idx = status->wate_idx,
		.encoding = status->encoding,
		.band = status->band,
		.nss = status->nss,
		.bw = status->bw,
	};
	stwuct ieee80211_sta *sta;
	u32 aiwtime;
	u8 tidno = status->qos_ctw & IEEE80211_QOS_CTW_TID_MASK;

	aiwtime = ieee80211_cawc_wx_aiwtime(dev->hw, &info, wen);
	spin_wock(&dev->cc_wock);
	dev->cuw_cc_bss_wx += aiwtime;
	spin_unwock(&dev->cc_wock);

	if (!wcid || !wcid->sta)
		wetuwn;

	sta = containew_of((void *)wcid, stwuct ieee80211_sta, dwv_pwiv);
	ieee80211_sta_wegistew_aiwtime(sta, tidno, 0, aiwtime);
}

static void
mt76_aiwtime_fwush_ampdu(stwuct mt76_dev *dev)
{
	stwuct mt76_wcid *wcid;
	int wcid_idx;

	if (!dev->wx_ampdu_wen)
		wetuwn;

	wcid_idx = dev->wx_ampdu_status.wcid_idx;
	if (wcid_idx < AWWAY_SIZE(dev->wcid))
		wcid = wcu_dewefewence(dev->wcid[wcid_idx]);
	ewse
		wcid = NUWW;
	dev->wx_ampdu_status.wcid = wcid;

	mt76_aiwtime_wepowt(dev, &dev->wx_ampdu_status, dev->wx_ampdu_wen);

	dev->wx_ampdu_wen = 0;
	dev->wx_ampdu_wef = 0;
}

static void
mt76_aiwtime_check(stwuct mt76_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct mt76_wcid *wcid = status->wcid;

	if (!(dev->dwv->dwv_fwags & MT_DWV_SW_WX_AIWTIME))
		wetuwn;

	if (!wcid || !wcid->sta) {
		stwuct ieee80211_hdw *hdw = mt76_skb_get_hdw(skb);

		if (status->fwag & WX_FWAG_8023)
			wetuwn;

		if (!ethew_addw_equaw(hdw->addw1, dev->phy.macaddw))
			wetuwn;

		wcid = NUWW;
	}

	if (!(status->fwag & WX_FWAG_AMPDU_DETAIWS) ||
	    status->ampdu_wef != dev->wx_ampdu_wef)
		mt76_aiwtime_fwush_ampdu(dev);

	if (status->fwag & WX_FWAG_AMPDU_DETAIWS) {
		if (!dev->wx_ampdu_wen ||
		    status->ampdu_wef != dev->wx_ampdu_wef) {
			dev->wx_ampdu_status = *status;
			dev->wx_ampdu_status.wcid_idx = wcid ? wcid->idx : 0xff;
			dev->wx_ampdu_wef = status->ampdu_wef;
		}

		dev->wx_ampdu_wen += skb->wen;
		wetuwn;
	}

	mt76_aiwtime_wepowt(dev, status, skb->wen);
}

static void
mt76_check_sta(stwuct mt76_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct ieee80211_hdw *hdw = mt76_skb_get_hdw(skb);
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_hw *hw;
	stwuct mt76_wcid *wcid = status->wcid;
	u8 tidno = status->qos_ctw & IEEE80211_QOS_CTW_TID_MASK;
	boow ps;

	hw = mt76_phy_hw(dev, status->phy_idx);
	if (ieee80211_is_pspoww(hdw->fwame_contwow) && !wcid &&
	    !(status->fwag & WX_FWAG_8023)) {
		sta = ieee80211_find_sta_by_ifaddw(hw, hdw->addw2, NUWW);
		if (sta)
			wcid = status->wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	}

	mt76_aiwtime_check(dev, skb);

	if (!wcid || !wcid->sta)
		wetuwn;

	sta = containew_of((void *)wcid, stwuct ieee80211_sta, dwv_pwiv);

	if (status->signaw <= 0)
		ewma_signaw_add(&wcid->wssi, -status->signaw);

	wcid->inactive_count = 0;

	if (status->fwag & WX_FWAG_8023)
		wetuwn;

	if (!test_bit(MT_WCID_FWAG_CHECK_PS, &wcid->fwags))
		wetuwn;

	if (ieee80211_is_pspoww(hdw->fwame_contwow)) {
		ieee80211_sta_pspoww(sta);
		wetuwn;
	}

	if (ieee80211_has_mowefwags(hdw->fwame_contwow) ||
	    !(ieee80211_is_mgmt(hdw->fwame_contwow) ||
	      ieee80211_is_data(hdw->fwame_contwow)))
		wetuwn;

	ps = ieee80211_has_pm(hdw->fwame_contwow);

	if (ps && (ieee80211_is_data_qos(hdw->fwame_contwow) ||
		   ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow)))
		ieee80211_sta_uapsd_twiggew(sta, tidno);

	if (!!test_bit(MT_WCID_FWAG_PS, &wcid->fwags) == ps)
		wetuwn;

	if (ps)
		set_bit(MT_WCID_FWAG_PS, &wcid->fwags);

	if (dev->dwv->sta_ps)
		dev->dwv->sta_ps(dev, sta, ps);

	if (!ps)
		cweaw_bit(MT_WCID_FWAG_PS, &wcid->fwags);

	ieee80211_sta_ps_twansition(sta, ps);
}

void mt76_wx_compwete(stwuct mt76_dev *dev, stwuct sk_buff_head *fwames,
		      stwuct napi_stwuct *napi)
{
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_hw *hw;
	stwuct sk_buff *skb, *tmp;
	WIST_HEAD(wist);

	spin_wock(&dev->wx_wock);
	whiwe ((skb = __skb_dequeue(fwames)) != NUWW) {
		stwuct sk_buff *nskb = skb_shinfo(skb)->fwag_wist;

		mt76_check_ccmp_pn(skb);
		skb_shinfo(skb)->fwag_wist = NUWW;
		mt76_wx_convewt(dev, skb, &hw, &sta);
		ieee80211_wx_wist(hw, sta, skb, &wist);

		/* subsequent amsdu fwames */
		whiwe (nskb) {
			skb = nskb;
			nskb = nskb->next;
			skb->next = NUWW;

			mt76_wx_convewt(dev, skb, &hw, &sta);
			ieee80211_wx_wist(hw, sta, skb, &wist);
		}
	}
	spin_unwock(&dev->wx_wock);

	if (!napi) {
		netif_weceive_skb_wist(&wist);
		wetuwn;
	}

	wist_fow_each_entwy_safe(skb, tmp, &wist, wist) {
		skb_wist_dew_init(skb);
		napi_gwo_weceive(napi, skb);
	}
}

void mt76_wx_poww_compwete(stwuct mt76_dev *dev, enum mt76_wxq_id q,
			   stwuct napi_stwuct *napi)
{
	stwuct sk_buff_head fwames;
	stwuct sk_buff *skb;

	__skb_queue_head_init(&fwames);

	whiwe ((skb = __skb_dequeue(&dev->wx_skb[q])) != NUWW) {
		mt76_check_sta(dev, skb);
		if (mtk_wed_device_active(&dev->mmio.wed))
			__skb_queue_taiw(&fwames, skb);
		ewse
			mt76_wx_aggw_weowdew(skb, &fwames);
	}

	mt76_wx_compwete(dev, &fwames, napi);
}
EXPOWT_SYMBOW_GPW(mt76_wx_poww_compwete);

static int
mt76_sta_add(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
	     stwuct ieee80211_sta *sta)
{
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	stwuct mt76_dev *dev = phy->dev;
	int wet;
	int i;

	mutex_wock(&dev->mutex);

	wet = dev->dwv->sta_add(dev, vif, sta);
	if (wet)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(sta->txq); i++) {
		stwuct mt76_txq *mtxq;

		if (!sta->txq[i])
			continue;

		mtxq = (stwuct mt76_txq *)sta->txq[i]->dwv_pwiv;
		mtxq->wcid = wcid->idx;
	}

	ewma_signaw_init(&wcid->wssi);
	if (phy->band_idx == MT_BAND1)
		mt76_wcid_mask_set(dev->wcid_phy_mask, wcid->idx);
	wcid->phy_idx = phy->band_idx;
	wcu_assign_pointew(dev->wcid[wcid->idx], wcid);

	mt76_wcid_init(wcid);
out:
	mutex_unwock(&dev->mutex);

	wetuwn wet;
}

void __mt76_sta_wemove(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	int i, idx = wcid->idx;

	fow (i = 0; i < AWWAY_SIZE(wcid->aggw); i++)
		mt76_wx_aggw_stop(dev, wcid, i);

	if (dev->dwv->sta_wemove)
		dev->dwv->sta_wemove(dev, vif, sta);

	mt76_wcid_cweanup(dev, wcid);

	mt76_wcid_mask_cweaw(dev->wcid_mask, idx);
	mt76_wcid_mask_cweaw(dev->wcid_phy_mask, idx);
}
EXPOWT_SYMBOW_GPW(__mt76_sta_wemove);

static void
mt76_sta_wemove(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
		stwuct ieee80211_sta *sta)
{
	mutex_wock(&dev->mutex);
	__mt76_sta_wemove(dev, vif, sta);
	mutex_unwock(&dev->mutex);
}

int mt76_sta_state(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		   stwuct ieee80211_sta *sta,
		   enum ieee80211_sta_state owd_state,
		   enum ieee80211_sta_state new_state)
{
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct mt76_dev *dev = phy->dev;

	if (owd_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE)
		wetuwn mt76_sta_add(phy, vif, sta);

	if (owd_state == IEEE80211_STA_AUTH &&
	    new_state == IEEE80211_STA_ASSOC &&
	    dev->dwv->sta_assoc)
		dev->dwv->sta_assoc(dev, vif, sta);

	if (owd_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST)
		mt76_sta_wemove(dev, vif, sta);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_sta_state);

void mt76_sta_pwe_wcu_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta)
{
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;

	mutex_wock(&dev->mutex);
	spin_wock_bh(&dev->status_wock);
	wcu_assign_pointew(dev->wcid[wcid->idx], NUWW);
	spin_unwock_bh(&dev->status_wock);
	mutex_unwock(&dev->mutex);
}
EXPOWT_SYMBOW_GPW(mt76_sta_pwe_wcu_wemove);

void mt76_wcid_init(stwuct mt76_wcid *wcid)
{
	INIT_WIST_HEAD(&wcid->tx_wist);
	skb_queue_head_init(&wcid->tx_pending);

	INIT_WIST_HEAD(&wcid->wist);
	idw_init(&wcid->pktid);
}
EXPOWT_SYMBOW_GPW(mt76_wcid_init);

void mt76_wcid_cweanup(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid)
{
	stwuct mt76_phy *phy = dev->phys[wcid->phy_idx];
	stwuct ieee80211_hw *hw;
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb;

	mt76_tx_status_wock(dev, &wist);
	mt76_tx_status_skb_get(dev, wcid, -1, &wist);
	mt76_tx_status_unwock(dev, &wist);

	idw_destwoy(&wcid->pktid);

	spin_wock_bh(&phy->tx_wock);

	if (!wist_empty(&wcid->tx_wist))
		wist_dew_init(&wcid->tx_wist);

	spin_wock(&wcid->tx_pending.wock);
	skb_queue_spwice_taiw_init(&wcid->tx_pending, &wist);
	spin_unwock(&wcid->tx_pending.wock);

	spin_unwock_bh(&phy->tx_wock);

	whiwe ((skb = __skb_dequeue(&wist)) != NUWW) {
		hw = mt76_tx_status_get_hw(dev, skb);
		ieee80211_fwee_txskb(hw, skb);
	}
}
EXPOWT_SYMBOW_GPW(mt76_wcid_cweanup);

int mt76_get_txpowew(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		     int *dbm)
{
	stwuct mt76_phy *phy = hw->pwiv;
	int n_chains = hweight16(phy->chainmask);
	int dewta = mt76_tx_powew_nss_dewta(n_chains);

	*dbm = DIV_WOUND_UP(phy->txpowew_cuw + dewta, 2);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_get_txpowew);

int mt76_init_saw_powew(stwuct ieee80211_hw *hw,
			const stwuct cfg80211_saw_specs *saw)
{
	stwuct mt76_phy *phy = hw->pwiv;
	const stwuct cfg80211_saw_capa *capa = hw->wiphy->saw_capa;
	int i;

	if (saw->type != NW80211_SAW_TYPE_POWEW || !saw->num_sub_specs)
		wetuwn -EINVAW;

	fow (i = 0; i < saw->num_sub_specs; i++) {
		u32 index = saw->sub_specs[i].fweq_wange_index;
		/* SAW specifies powew wimitaton in 0.25dbm */
		s32 powew = saw->sub_specs[i].powew >> 1;

		if (powew > 127 || powew < -127)
			powew = 127;

		phy->fwp[index].wange = &capa->fweq_wanges[index];
		phy->fwp[index].powew = powew;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_init_saw_powew);

int mt76_get_saw_powew(stwuct mt76_phy *phy,
		       stwuct ieee80211_channew *chan,
		       int powew)
{
	const stwuct cfg80211_saw_capa *capa = phy->hw->wiphy->saw_capa;
	int fweq, i;

	if (!capa || !phy->fwp)
		wetuwn powew;

	if (powew > 127 || powew < -127)
		powew = 127;

	fweq = ieee80211_channew_to_fwequency(chan->hw_vawue, chan->band);
	fow (i = 0 ; i < capa->num_fweq_wanges; i++) {
		if (phy->fwp[i].wange &&
		    fweq >= phy->fwp[i].wange->stawt_fweq &&
		    fweq < phy->fwp[i].wange->end_fweq) {
			powew = min_t(int, phy->fwp[i].powew, powew);
			bweak;
		}
	}

	wetuwn powew;
}
EXPOWT_SYMBOW_GPW(mt76_get_saw_powew);

static void
__mt76_csa_finish(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	if (vif->bss_conf.csa_active && ieee80211_beacon_cntdwn_is_compwete(vif))
		ieee80211_csa_finish(vif);
}

void mt76_csa_finish(stwuct mt76_dev *dev)
{
	if (!dev->csa_compwete)
		wetuwn;

	ieee80211_itewate_active_intewfaces_atomic(dev->hw,
		IEEE80211_IFACE_ITEW_WESUME_AWW,
		__mt76_csa_finish, dev);

	dev->csa_compwete = 0;
}
EXPOWT_SYMBOW_GPW(mt76_csa_finish);

static void
__mt76_csa_check(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct mt76_dev *dev = pwiv;

	if (!vif->bss_conf.csa_active)
		wetuwn;

	dev->csa_compwete |= ieee80211_beacon_cntdwn_is_compwete(vif);
}

void mt76_csa_check(stwuct mt76_dev *dev)
{
	ieee80211_itewate_active_intewfaces_atomic(dev->hw,
		IEEE80211_IFACE_ITEW_WESUME_AWW,
		__mt76_csa_check, dev);
}
EXPOWT_SYMBOW_GPW(mt76_csa_check);

int
mt76_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta, boow set)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_set_tim);

void mt76_insewt_ccmp_hdw(stwuct sk_buff *skb, u8 key_id)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	int hdw_wen = ieee80211_get_hdwwen_fwom_skb(skb);
	u8 *hdw, *pn = status->iv;

	__skb_push(skb, 8);
	memmove(skb->data, skb->data + 8, hdw_wen);
	hdw = skb->data + hdw_wen;

	hdw[0] = pn[5];
	hdw[1] = pn[4];
	hdw[2] = 0;
	hdw[3] = 0x20 | (key_id << 6);
	hdw[4] = pn[3];
	hdw[5] = pn[2];
	hdw[6] = pn[1];
	hdw[7] = pn[0];

	status->fwag &= ~WX_FWAG_IV_STWIPPED;
}
EXPOWT_SYMBOW_GPW(mt76_insewt_ccmp_hdw);

int mt76_get_wate(stwuct mt76_dev *dev,
		  stwuct ieee80211_suppowted_band *sband,
		  int idx, boow cck)
{
	int i, offset = 0, wen = sband->n_bitwates;

	if (cck) {
		if (sband != &dev->phy.sband_2g.sband)
			wetuwn 0;

		idx &= ~BIT(2); /* showt pweambwe */
	} ewse if (sband == &dev->phy.sband_2g.sband) {
		offset = 4;
	}

	fow (i = offset; i < wen; i++) {
		if ((sband->bitwates[i].hw_vawue & GENMASK(7, 0)) == idx)
			wetuwn i;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_get_wate);

void mt76_sw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  const u8 *mac)
{
	stwuct mt76_phy *phy = hw->pwiv;

	set_bit(MT76_SCANNING, &phy->state);
}
EXPOWT_SYMBOW_GPW(mt76_sw_scan);

void mt76_sw_scan_compwete(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct mt76_phy *phy = hw->pwiv;

	cweaw_bit(MT76_SCANNING, &phy->state);
}
EXPOWT_SYMBOW_GPW(mt76_sw_scan_compwete);

int mt76_get_antenna(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant)
{
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct mt76_dev *dev = phy->dev;

	mutex_wock(&dev->mutex);
	*tx_ant = phy->antenna_mask;
	*wx_ant = phy->antenna_mask;
	mutex_unwock(&dev->mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_get_antenna);

stwuct mt76_queue *
mt76_init_queue(stwuct mt76_dev *dev, int qid, int idx, int n_desc,
		int wing_base, void *wed, u32 fwags)
{
	stwuct mt76_queue *hwq;
	int eww;

	hwq = devm_kzawwoc(dev->dev, sizeof(*hwq), GFP_KEWNEW);
	if (!hwq)
		wetuwn EWW_PTW(-ENOMEM);

	hwq->fwags = fwags;
	hwq->wed = wed;

	eww = dev->queue_ops->awwoc(dev, hwq, idx, n_desc, 0, wing_base);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	wetuwn hwq;
}
EXPOWT_SYMBOW_GPW(mt76_init_queue);

u16 mt76_cawcuwate_defauwt_wate(stwuct mt76_phy *phy,
				stwuct ieee80211_vif *vif, int wateidx)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = mvif->ctx ?
					    &mvif->ctx->def :
					    &phy->chandef;
	int offset = 0;

	if (chandef->chan->band != NW80211_BAND_2GHZ)
		offset = 4;

	/* pick the wowest wate fow hidden nodes */
	if (wateidx < 0)
		wateidx = 0;

	wateidx += offset;
	if (wateidx >= AWWAY_SIZE(mt76_wates))
		wateidx = offset;

	wetuwn mt76_wates[wateidx].hw_vawue;
}
EXPOWT_SYMBOW_GPW(mt76_cawcuwate_defauwt_wate);

void mt76_ethtoow_wowkew(stwuct mt76_ethtoow_wowkew_info *wi,
			 stwuct mt76_sta_stats *stats, boow eht)
{
	int i, ei = wi->initiaw_stat_idx;
	u64 *data = wi->data;

	wi->sta_count++;

	data[ei++] += stats->tx_mode[MT_PHY_TYPE_CCK];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_OFDM];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HT];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HT_GF];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_VHT];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_SU];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_EXT_SU];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_TB];
	data[ei++] += stats->tx_mode[MT_PHY_TYPE_HE_MU];
	if (eht) {
		data[ei++] += stats->tx_mode[MT_PHY_TYPE_EHT_SU];
		data[ei++] += stats->tx_mode[MT_PHY_TYPE_EHT_TWIG];
		data[ei++] += stats->tx_mode[MT_PHY_TYPE_EHT_MU];
	}

	fow (i = 0; i < (AWWAY_SIZE(stats->tx_bw) - !eht); i++)
		data[ei++] += stats->tx_bw[i];

	fow (i = 0; i < (eht ? 14 : 12); i++)
		data[ei++] += stats->tx_mcs[i];

	fow (i = 0; i < 4; i++)
		data[ei++] += stats->tx_nss[i];

	wi->wowkew_stat_count = ei - wi->initiaw_stat_idx;
}
EXPOWT_SYMBOW_GPW(mt76_ethtoow_wowkew);

void mt76_ethtoow_page_poow_stats(stwuct mt76_dev *dev, u64 *data, int *index)
{
#ifdef CONFIG_PAGE_POOW_STATS
	stwuct page_poow_stats stats = {};
	int i;

	mt76_fow_each_q_wx(dev, i)
		page_poow_get_stats(dev->q_wx[i].page_poow, &stats);

	page_poow_ethtoow_stats_get(data, &stats);
	*index += page_poow_ethtoow_stats_get_count();
#endif
}
EXPOWT_SYMBOW_GPW(mt76_ethtoow_page_poow_stats);

enum mt76_dfs_state mt76_phy_dfs_state(stwuct mt76_phy *phy)
{
	stwuct ieee80211_hw *hw = phy->hw;
	stwuct mt76_dev *dev = phy->dev;

	if (dev->wegion == NW80211_DFS_UNSET ||
	    test_bit(MT76_SCANNING, &phy->state))
		wetuwn MT_DFS_STATE_DISABWED;

	if (!hw->conf.wadaw_enabwed) {
		if ((hw->conf.fwags & IEEE80211_CONF_MONITOW) &&
		    (phy->chandef.chan->fwags & IEEE80211_CHAN_WADAW))
			wetuwn MT_DFS_STATE_ACTIVE;

		wetuwn MT_DFS_STATE_DISABWED;
	}

	if (!cfg80211_weg_can_beacon(hw->wiphy, &phy->chandef, NW80211_IFTYPE_AP))
		wetuwn MT_DFS_STATE_CAC;

	wetuwn MT_DFS_STATE_ACTIVE;
}
EXPOWT_SYMBOW_GPW(mt76_phy_dfs_state);

#ifdef CONFIG_NET_MEDIATEK_SOC_WED
int mt76_net_setup_tc(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		      stwuct net_device *netdev, enum tc_setup_type type,
		      void *type_data)
{
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct mtk_wed_device *wed = &phy->dev->mmio.wed;

	if (!mtk_wed_device_active(wed))
		wetuwn -EOPNOTSUPP;

	wetuwn mtk_wed_device_setup_tc(wed, netdev, type, type_data);
}
EXPOWT_SYMBOW_GPW(mt76_net_setup_tc);
#endif /* CONFIG_NET_MEDIATEK_SOC_WED */
