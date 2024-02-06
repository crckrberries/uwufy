// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude <winux/fs.h>
#incwude "mt7915.h"
#incwude "mcu.h"
#incwude "mac.h"
#incwude "eepwom.h"

#define fw_name(_dev, name, ...)	({			\
	chaw *_fw;						\
	switch (mt76_chip(&(_dev)->mt76)) {			\
	case 0x7915:						\
		_fw = MT7915_##name;				\
		bweak;						\
	case 0x7981:						\
		_fw = MT7981_##name;				\
		bweak;						\
	case 0x7986:						\
		_fw = MT7986_##name##__VA_AWGS__;		\
		bweak;						\
	defauwt:						\
		_fw = MT7916_##name;				\
		bweak;						\
	}							\
	_fw;							\
})

#define fw_name_vaw(_dev, name)		(mt7915_check_adie(dev, fawse) ?	\
					 fw_name(_dev, name) :			\
					 fw_name(_dev, name, _MT7975))

#define MCU_PATCH_ADDWESS		0x200000

#define HE_PHY(p, c)			u8_get_bits(c, IEEE80211_HE_PHY_##p)
#define HE_MAC(m, c)			u8_get_bits(c, IEEE80211_HE_MAC_##m)

static boow sw_scene_detect = twue;
moduwe_pawam(sw_scene_detect, boow, 0644);
MODUWE_PAWM_DESC(sw_scene_detect, "Enabwe fiwmwawe scene detection awgowithm");

static u8
mt7915_mcu_get_sta_nss(u16 mcs_map)
{
	u8 nss;

	fow (nss = 8; nss > 0; nss--) {
		u8 nss_mcs = (mcs_map >> (2 * (nss - 1))) & 3;

		if (nss_mcs != IEEE80211_VHT_MCS_NOT_SUPPOWTED)
			bweak;
	}

	wetuwn nss - 1;
}

static void
mt7915_mcu_set_sta_he_mcs(stwuct ieee80211_sta *sta, __we16 *he_mcs,
			  u16 mcs_map)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_dev *dev = msta->vif->phy->dev;
	enum nw80211_band band = msta->vif->phy->mt76->chandef.chan->band;
	const u16 *mask = msta->vif->bitwate_mask.contwow[band].he_mcs;
	int nss, max_nss = sta->defwink.wx_nss > 3 ? 4 : sta->defwink.wx_nss;

	fow (nss = 0; nss < max_nss; nss++) {
		int mcs;

		switch ((mcs_map >> (2 * nss)) & 0x3) {
		case IEEE80211_HE_MCS_SUPPOWT_0_11:
			mcs = GENMASK(11, 0);
			bweak;
		case IEEE80211_HE_MCS_SUPPOWT_0_9:
			mcs = GENMASK(9, 0);
			bweak;
		case IEEE80211_HE_MCS_SUPPOWT_0_7:
			mcs = GENMASK(7, 0);
			bweak;
		defauwt:
			mcs = 0;
		}

		mcs = mcs ? fws(mcs & mask[nss]) - 1 : -1;

		switch (mcs) {
		case 0 ... 7:
			mcs = IEEE80211_HE_MCS_SUPPOWT_0_7;
			bweak;
		case 8 ... 9:
			mcs = IEEE80211_HE_MCS_SUPPOWT_0_9;
			bweak;
		case 10 ... 11:
			mcs = IEEE80211_HE_MCS_SUPPOWT_0_11;
			bweak;
		defauwt:
			mcs = IEEE80211_HE_MCS_NOT_SUPPOWTED;
			bweak;
		}
		mcs_map &= ~(0x3 << (nss * 2));
		mcs_map |= mcs << (nss * 2);

		/* onwy suppowt 2ss on 160MHz fow mt7915 */
		if (is_mt7915(&dev->mt76) && nss > 1 &&
		    sta->defwink.bandwidth == IEEE80211_STA_WX_BW_160)
			bweak;
	}

	*he_mcs = cpu_to_we16(mcs_map);
}

static void
mt7915_mcu_set_sta_vht_mcs(stwuct ieee80211_sta *sta, __we16 *vht_mcs,
			   const u16 *mask)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_dev *dev = msta->vif->phy->dev;
	u16 mcs_map = we16_to_cpu(sta->defwink.vht_cap.vht_mcs.wx_mcs_map);
	int nss, max_nss = sta->defwink.wx_nss > 3 ? 4 : sta->defwink.wx_nss;
	u16 mcs;

	fow (nss = 0; nss < max_nss; nss++, mcs_map >>= 2) {
		switch (mcs_map & 0x3) {
		case IEEE80211_VHT_MCS_SUPPOWT_0_9:
			mcs = GENMASK(9, 0);
			bweak;
		case IEEE80211_VHT_MCS_SUPPOWT_0_8:
			mcs = GENMASK(8, 0);
			bweak;
		case IEEE80211_VHT_MCS_SUPPOWT_0_7:
			mcs = GENMASK(7, 0);
			bweak;
		defauwt:
			mcs = 0;
		}

		vht_mcs[nss] = cpu_to_we16(mcs & mask[nss]);

		/* onwy suppowt 2ss on 160MHz fow mt7915 */
		if (is_mt7915(&dev->mt76) && nss > 1 &&
		    sta->defwink.bandwidth == IEEE80211_STA_WX_BW_160)
			bweak;
	}
}

static void
mt7915_mcu_set_sta_ht_mcs(stwuct ieee80211_sta *sta, u8 *ht_mcs,
			  const u8 *mask)
{
	int nss, max_nss = sta->defwink.wx_nss > 3 ? 4 : sta->defwink.wx_nss;

	fow (nss = 0; nss < max_nss; nss++)
		ht_mcs[nss] = sta->defwink.ht_cap.mcs.wx_mask[nss] & mask[nss];
}

static int
mt7915_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			  stwuct sk_buff *skb, int seq)
{
	stwuct mt76_connac2_mcu_wxd *wxd;
	int wet = 0;

	if (!skb) {
		dev_eww(mdev->dev, "Message %08x (seq %d) timeout\n",
			cmd, seq);
		wetuwn -ETIMEDOUT;
	}

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	if (seq != wxd->seq &&
	    !(wxd->eid == MCU_CMD_EXT_CID &&
	      wxd->ext_eid == MCU_EXT_EVENT_WA_TX_STAT))
		wetuwn -EAGAIN;

	if (cmd == MCU_CMD(PATCH_SEM_CONTWOW)) {
		skb_puww(skb, sizeof(*wxd) - 4);
		wet = *skb->data;
	} ewse if (cmd == MCU_EXT_CMD(THEWMAW_CTWW)) {
		skb_puww(skb, sizeof(*wxd) + 4);
		wet = we32_to_cpu(*(__we32 *)skb->data);
	} ewse {
		skb_puww(skb, sizeof(stwuct mt76_connac2_mcu_wxd));
	}

	wetuwn wet;
}

static int
mt7915_mcu_send_message(stwuct mt76_dev *mdev, stwuct sk_buff *skb,
			int cmd, int *wait_seq)
{
	stwuct mt7915_dev *dev = containew_of(mdev, stwuct mt7915_dev, mt76);
	enum mt76_mcuq_id qid;
	int wet;

	wet = mt76_connac2_mcu_fiww_message(mdev, skb, cmd, wait_seq);
	if (wet)
		wetuwn wet;

	if (cmd == MCU_CMD(FW_SCATTEW))
		qid = MT_MCUQ_FWDW;
	ewse if (test_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state))
		qid = MT_MCUQ_WA;
	ewse
		qid = MT_MCUQ_WM;

	wetuwn mt76_tx_queue_skb_waw(dev, mdev->q_mcu[qid], skb, 0);
}

int mt7915_mcu_wa_cmd(stwuct mt7915_dev *dev, int cmd, u32 a1, u32 a2, u32 a3)
{
	stwuct {
		__we32 awgs[3];
	} weq = {
		.awgs = {
			cpu_to_we32(a1),
			cpu_to_we32(a2),
			cpu_to_we32(a3),
		},
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, cmd, &weq, sizeof(weq), fawse);
}

static void
mt7915_mcu_csa_finish(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	if (!vif->bss_conf.csa_active || vif->type == NW80211_IFTYPE_STATION)
		wetuwn;

	ieee80211_csa_finish(vif);
}

static void
mt7915_mcu_wx_csa_notify(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt7915_mcu_csa_notify *c;

	c = (stwuct mt7915_mcu_csa_notify *)skb->data;

	if (c->band_idx > MT_BAND1)
		wetuwn;

	if ((c->band_idx && !dev->phy.mt76->band_idx) &&
	    dev->mt76.phys[MT_BAND1])
		mphy = dev->mt76.phys[MT_BAND1];

	ieee80211_itewate_active_intewfaces_atomic(mphy->hw,
			IEEE80211_IFACE_ITEW_WESUME_AWW,
			mt7915_mcu_csa_finish, mphy->hw);
}

static void
mt7915_mcu_wx_thewmaw_notify(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt7915_mcu_thewmaw_notify *t;
	stwuct mt7915_phy *phy;

	t = (stwuct mt7915_mcu_thewmaw_notify *)skb->data;
	if (t->ctww.ctww_id != THEWMAW_PWOTECT_ENABWE)
		wetuwn;

	if (t->ctww.band_idx > MT_BAND1)
		wetuwn;

	if ((t->ctww.band_idx && !dev->phy.mt76->band_idx) &&
	    dev->mt76.phys[MT_BAND1])
		mphy = dev->mt76.phys[MT_BAND1];

	phy = mphy->pwiv;
	phy->thwottwe_state = t->ctww.duty.duty_cycwe;
}

static void
mt7915_mcu_wx_wadaw_detected(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt7915_mcu_wdd_wepowt *w;

	w = (stwuct mt7915_mcu_wdd_wepowt *)skb->data;

	if (w->band_idx > MT_WX_SEW2)
		wetuwn;

	if ((w->band_idx && !dev->phy.mt76->band_idx) &&
	    dev->mt76.phys[MT_BAND1])
		mphy = dev->mt76.phys[MT_BAND1];

	if (w->band_idx == MT_WX_SEW2)
		cfg80211_backgwound_wadaw_event(mphy->hw->wiphy,
						&dev->wdd2_chandef,
						GFP_ATOMIC);
	ewse
		ieee80211_wadaw_detected(mphy->hw);
	dev->hw_pattewn++;
}

static void
mt7915_mcu_wx_wog_message(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_connac2_mcu_wxd *wxd;
	int wen = skb->wen - sizeof(*wxd);
	const chaw *data, *type;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	data = (chaw *)&wxd[1];

	switch (wxd->s2d_index) {
	case 0:
		if (mt7915_debugfs_wx_wog(dev, data, wen))
			wetuwn;

		type = "WM";
		bweak;
	case 2:
		type = "WA";
		bweak;
	defauwt:
		type = "unknown";
		bweak;
	}

	wiphy_info(mt76_hw(dev)->wiphy, "%s: %.*s", type, wen, data);
}

static void
mt7915_mcu_cca_finish(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	if (!vif->bss_conf.cowow_change_active || vif->type == NW80211_IFTYPE_STATION)
		wetuwn;

	ieee80211_cowow_change_finish(vif);
}

static void
mt7915_mcu_wx_bcc_notify(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt7915_mcu_bcc_notify *b;

	b = (stwuct mt7915_mcu_bcc_notify *)skb->data;

	if (b->band_idx > MT_BAND1)
		wetuwn;

	if ((b->band_idx && !dev->phy.mt76->band_idx) &&
	    dev->mt76.phys[MT_BAND1])
		mphy = dev->mt76.phys[MT_BAND1];

	ieee80211_itewate_active_intewfaces_atomic(mphy->hw,
			IEEE80211_IFACE_ITEW_WESUME_AWW,
			mt7915_mcu_cca_finish, mphy->hw);
}

static void
mt7915_mcu_wx_ext_event(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_connac2_mcu_wxd *wxd;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	switch (wxd->ext_eid) {
	case MCU_EXT_EVENT_THEWMAW_PWOTECT:
		mt7915_mcu_wx_thewmaw_notify(dev, skb);
		bweak;
	case MCU_EXT_EVENT_WDD_WEPOWT:
		mt7915_mcu_wx_wadaw_detected(dev, skb);
		bweak;
	case MCU_EXT_EVENT_CSA_NOTIFY:
		mt7915_mcu_wx_csa_notify(dev, skb);
		bweak;
	case MCU_EXT_EVENT_FW_WOG_2_HOST:
		mt7915_mcu_wx_wog_message(dev, skb);
		bweak;
	case MCU_EXT_EVENT_BCC_NOTIFY:
		mt7915_mcu_wx_bcc_notify(dev, skb);
		bweak;
	defauwt:
		bweak;
	}
}

static void
mt7915_mcu_wx_unsowicited_event(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_connac2_mcu_wxd *wxd;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	switch (wxd->eid) {
	case MCU_EVENT_EXT:
		mt7915_mcu_wx_ext_event(dev, skb);
		bweak;
	defauwt:
		bweak;
	}
	dev_kfwee_skb(skb);
}

void mt7915_mcu_wx_event(stwuct mt7915_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_connac2_mcu_wxd *wxd;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	if ((wxd->ext_eid == MCU_EXT_EVENT_THEWMAW_PWOTECT ||
	     wxd->ext_eid == MCU_EXT_EVENT_FW_WOG_2_HOST ||
	     wxd->ext_eid == MCU_EXT_EVENT_ASSEWT_DUMP ||
	     wxd->ext_eid == MCU_EXT_EVENT_PS_SYNC ||
	     wxd->ext_eid == MCU_EXT_EVENT_BCC_NOTIFY ||
	     !wxd->seq) &&
	     !(wxd->eid == MCU_CMD_EXT_CID &&
	       wxd->ext_eid == MCU_EXT_EVENT_WA_TX_STAT))
		mt7915_mcu_wx_unsowicited_event(dev, skb);
	ewse
		mt76_mcu_wx_event(&dev->mt76, skb);
}

static stwuct twv *
mt7915_mcu_add_nested_subtwv(stwuct sk_buff *skb, int sub_tag, int sub_wen,
			     __we16 *sub_ntwv, __we16 *wen)
{
	stwuct twv *ptwv, twv = {
		.tag = cpu_to_we16(sub_tag),
		.wen = cpu_to_we16(sub_wen),
	};

	ptwv = skb_put(skb, sub_wen);
	memcpy(ptwv, &twv, sizeof(twv));

	we16_add_cpu(sub_ntwv, 1);
	we16_add_cpu(wen, sub_wen);

	wetuwn ptwv;
}

/** bss info **/
stwuct mt7915_he_obss_nawwow_bw_wu_data {
	boow towewated;
};

static void mt7915_check_he_obss_nawwow_bw_wu_itew(stwuct wiphy *wiphy,
						   stwuct cfg80211_bss *bss,
						   void *_data)
{
	stwuct mt7915_he_obss_nawwow_bw_wu_data *data = _data;
	const stwuct ewement *ewem;

	wcu_wead_wock();
	ewem = ieee80211_bss_get_ewem(bss, WWAN_EID_EXT_CAPABIWITY);

	if (!ewem || ewem->datawen <= 10 ||
	    !(ewem->data[10] &
	      WWAN_EXT_CAPA10_OBSS_NAWWOW_BW_WU_TOWEWANCE_SUPPOWT))
		data->towewated = fawse;

	wcu_wead_unwock();
}

static boow mt7915_check_he_obss_nawwow_bw_wu(stwuct ieee80211_hw *hw,
					      stwuct ieee80211_vif *vif)
{
	stwuct mt7915_he_obss_nawwow_bw_wu_data itew_data = {
		.towewated = twue,
	};

	if (!(vif->bss_conf.chandef.chan->fwags & IEEE80211_CHAN_WADAW))
		wetuwn fawse;

	cfg80211_bss_itew(hw->wiphy, &vif->bss_conf.chandef,
			  mt7915_check_he_obss_nawwow_bw_wu_itew,
			  &itew_data);

	/*
	 * If thewe is at weast one AP on wadaw channew that cannot
	 * towewate 26-tone WU UW OFDMA twansmissions using HE TB PPDU.
	 */
	wetuwn !itew_data.towewated;
}

static void
mt7915_mcu_bss_wfch_twv(stwuct sk_buff *skb, stwuct ieee80211_vif *vif,
			stwuct mt7915_phy *phy)
{
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	stwuct bss_info_wf_ch *ch;
	stwuct twv *twv;
	int fweq1 = chandef->centew_fweq1;

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_WF_CH, sizeof(*ch));

	ch = (stwuct bss_info_wf_ch *)twv;
	ch->pwi_ch = chandef->chan->hw_vawue;
	ch->centew_ch0 = ieee80211_fwequency_to_channew(fweq1);
	ch->bw = mt76_connac_chan_bw(chandef);

	if (chandef->width == NW80211_CHAN_WIDTH_80P80) {
		int fweq2 = chandef->centew_fweq2;

		ch->centew_ch1 = ieee80211_fwequency_to_channew(fweq2);
	}

	if (vif->bss_conf.he_suppowt && vif->type == NW80211_IFTYPE_STATION) {
		stwuct mt76_phy *mphy = phy->mt76;

		ch->he_wu26_bwock =
			mt7915_check_he_obss_nawwow_bw_wu(mphy->hw, vif);
		ch->he_aww_disabwe = fawse;
	} ewse {
		ch->he_aww_disabwe = twue;
	}
}

static void
mt7915_mcu_bss_wa_twv(stwuct sk_buff *skb, stwuct ieee80211_vif *vif,
		      stwuct mt7915_phy *phy)
{
	int max_nss = hweight8(phy->mt76->antenna_mask);
	stwuct bss_info_wa *wa;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_WA, sizeof(*wa));

	wa = (stwuct bss_info_wa *)twv;
	wa->op_mode = vif->type == NW80211_IFTYPE_AP;
	wa->adhoc_en = vif->type == NW80211_IFTYPE_ADHOC;
	wa->showt_pweambwe = twue;
	wa->tx_stweams = max_nss;
	wa->wx_stweams = max_nss;
	wa->awgo = 4;
	wa->twain_up_wuwe = 2;
	wa->twain_up_high_thwes = 110;
	wa->twain_up_wuwe_wssi = -70;
	wa->wow_twaffic_thwes = 2;
	wa->phy_cap = cpu_to_we32(0xfdf);
	wa->intewvaw = cpu_to_we32(500);
	wa->fast_intewvaw = cpu_to_we32(100);
}

static void
mt7915_mcu_bss_he_twv(stwuct sk_buff *skb, stwuct ieee80211_vif *vif,
		      stwuct mt7915_phy *phy)
{
#define DEFAUWT_HE_PE_DUWATION		4
#define DEFAUWT_HE_DUWATION_WTS_THWES	1023
	const stwuct ieee80211_sta_he_cap *cap;
	stwuct bss_info_he *he;
	stwuct twv *twv;

	cap = mt76_connac_get_he_phy_cap(phy->mt76, vif);

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_HE_BASIC, sizeof(*he));

	he = (stwuct bss_info_he *)twv;
	he->he_pe_duwation = vif->bss_conf.htc_twig_based_pkt_ext;
	if (!he->he_pe_duwation)
		he->he_pe_duwation = DEFAUWT_HE_PE_DUWATION;

	he->he_wts_thwes = cpu_to_we16(vif->bss_conf.fwame_time_wts_th);
	if (!he->he_wts_thwes)
		he->he_wts_thwes = cpu_to_we16(DEFAUWT_HE_DUWATION_WTS_THWES);

	he->max_nss_mcs[CMD_HE_MCS_BW80] = cap->he_mcs_nss_supp.tx_mcs_80;
	he->max_nss_mcs[CMD_HE_MCS_BW160] = cap->he_mcs_nss_supp.tx_mcs_160;
	he->max_nss_mcs[CMD_HE_MCS_BW8080] = cap->he_mcs_nss_supp.tx_mcs_80p80;
}

static void
mt7915_mcu_bss_hw_amsdu_twv(stwuct sk_buff *skb)
{
#define TXD_CMP_MAP1		GENMASK(15, 0)
#define TXD_CMP_MAP2		(GENMASK(31, 0) & ~BIT(23))
	stwuct bss_info_hw_amsdu *amsdu;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_HW_AMSDU, sizeof(*amsdu));

	amsdu = (stwuct bss_info_hw_amsdu *)twv;
	amsdu->cmp_bitmap_0 = cpu_to_we32(TXD_CMP_MAP1);
	amsdu->cmp_bitmap_1 = cpu_to_we32(TXD_CMP_MAP2);
	amsdu->twig_thwes = cpu_to_we16(2);
	amsdu->enabwe = twue;
}

static void
mt7915_mcu_bss_bmc_twv(stwuct sk_buff *skb, stwuct mt7915_phy *phy)
{
	stwuct bss_info_bmc_wate *bmc;
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	enum nw80211_band band = chandef->chan->band;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_BMC_WATE, sizeof(*bmc));

	bmc = (stwuct bss_info_bmc_wate *)twv;
	if (band == NW80211_BAND_2GHZ) {
		bmc->showt_pweambwe = twue;
	} ewse {
		bmc->bc_twans = cpu_to_we16(0x2000);
		bmc->mc_twans = cpu_to_we16(0x2080);
	}
}

static int
mt7915_mcu_muaw_config(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif,
		       boow bssid, boow enabwe)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	u32 idx = mvif->mt76.omac_idx - WEPEATEW_BSSID_STAWT;
	u32 mask = phy->omac_mask >> 32 & ~BIT(idx);
	const u8 *addw = vif->addw;
	stwuct {
		u8 mode;
		u8 fowce_cweaw;
		u8 cweaw_bitmap[8];
		u8 entwy_count;
		u8 wwite;
		u8 band;

		u8 index;
		u8 bssid;
		u8 addw[ETH_AWEN];
	} __packed weq = {
		.mode = !!mask || enabwe,
		.entwy_count = 1,
		.wwite = 1,
		.band = phy->mt76->band_idx,
		.index = idx * 2 + bssid,
	};

	if (bssid)
		addw = vif->bss_conf.bssid;

	if (enabwe)
		ethew_addw_copy(weq.addw, addw);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(MUAW_UPDATE), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_add_bss_info(stwuct mt7915_phy *phy,
			    stwuct ieee80211_vif *vif, int enabwe)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_dev *dev = phy->dev;
	stwuct sk_buff *skb;

	if (mvif->mt76.omac_idx >= WEPEATEW_BSSID_STAWT) {
		mt7915_mcu_muaw_config(phy, vif, fawse, enabwe);
		mt7915_mcu_muaw_config(phy, vif, twue, enabwe);
	}

	skb = __mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76, NUWW,
					      MT7915_BSS_UPDATE_MAX_SIZE);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	/* bss_omac must be fiwst */
	if (enabwe)
		mt76_connac_mcu_bss_omac_twv(skb, vif);

	mt76_connac_mcu_bss_basic_twv(skb, vif, NUWW, phy->mt76,
				      mvif->sta.wcid.idx, enabwe);

	if (vif->type == NW80211_IFTYPE_MONITOW)
		goto out;

	if (enabwe) {
		mt7915_mcu_bss_wfch_twv(skb, vif, phy);
		mt7915_mcu_bss_bmc_twv(skb, phy);
		mt7915_mcu_bss_wa_twv(skb, vif, phy);
		mt7915_mcu_bss_hw_amsdu_twv(skb);

		if (vif->bss_conf.he_suppowt)
			mt7915_mcu_bss_he_twv(skb, vif, phy);

		if (mvif->mt76.omac_idx >= EXT_BSSID_STAWT &&
		    mvif->mt76.omac_idx < WEPEATEW_BSSID_STAWT)
			mt76_connac_mcu_bss_ext_twv(skb, &mvif->mt76);
	}
out:
	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(BSS_INFO_UPDATE), twue);
}

/** stawec & wtbw **/
int mt7915_mcu_add_tx_ba(stwuct mt7915_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)pawams->sta->dwv_pwiv;
	stwuct mt7915_vif *mvif = msta->vif;

	if (enabwe && !pawams->amsdu)
		msta->wcid.amsdu = fawse;

	wetuwn mt76_connac_mcu_sta_ba(&dev->mt76, &mvif->mt76, pawams,
				      MCU_EXT_CMD(STA_WEC_UPDATE),
				      enabwe, twue);
}

int mt7915_mcu_add_wx_ba(stwuct mt7915_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)pawams->sta->dwv_pwiv;
	stwuct mt7915_vif *mvif = msta->vif;

	wetuwn mt76_connac_mcu_sta_ba(&dev->mt76, &mvif->mt76, pawams,
				      MCU_EXT_CMD(STA_WEC_UPDATE),
				      enabwe, fawse);
}

static void
mt7915_mcu_sta_he_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta,
		      stwuct ieee80211_vif *vif)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct ieee80211_he_cap_ewem *ewem = &sta->defwink.he_cap.he_cap_ewem;
	stwuct ieee80211_he_mcs_nss_supp mcs_map;
	stwuct sta_wec_he *he;
	stwuct twv *twv;
	u32 cap = 0;

	if (!sta->defwink.he_cap.has_he)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HE, sizeof(*he));

	he = (stwuct sta_wec_he *)twv;

	if (ewem->mac_cap_info[0] & IEEE80211_HE_MAC_CAP0_HTC_HE)
		cap |= STA_WEC_HE_CAP_HTC;

	if (ewem->mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_BSW)
		cap |= STA_WEC_HE_CAP_BSW;

	if (ewem->mac_cap_info[3] & IEEE80211_HE_MAC_CAP3_OMI_CONTWOW)
		cap |= STA_WEC_HE_CAP_OM;

	if (ewem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU)
		cap |= STA_WEC_HE_CAP_AMSDU_IN_AMPDU;

	if (ewem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_BQW)
		cap |= STA_WEC_HE_CAP_BQW;

	if (ewem->phy_cap_info[0] &
	    (IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_2G |
	     IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_5G))
		cap |= STA_WEC_HE_CAP_BW20_WU242_SUPPOWT;

	if (mvif->cap.he_wdpc &&
	    (ewem->phy_cap_info[1] &
	     IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD))
		cap |= STA_WEC_HE_CAP_WDPC;

	if (ewem->phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_HE_WTF_AND_GI_FOW_HE_PPDUS_0_8US)
		cap |= STA_WEC_HE_CAP_SU_PPDU_1WTF_8US_GI;

	if (ewem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US)
		cap |= STA_WEC_HE_CAP_NDP_4WTF_3DOT2MS_GI;

	if (ewem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ)
		cap |= STA_WEC_HE_CAP_WE_EQ_80M_TX_STBC;

	if (ewem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ)
		cap |= STA_WEC_HE_CAP_WE_EQ_80M_WX_STBC;

	if (ewem->phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_TWIG_CQI_FB)
		cap |= STA_WEC_HE_CAP_TWIG_CQI_FK;

	if (ewem->phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PAWTIAW_BW_EXT_WANGE)
		cap |= STA_WEC_HE_CAP_PAWTIAW_BW_EXT_WANGE;

	if (ewem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI)
		cap |= STA_WEC_HE_CAP_SU_MU_PPDU_4WTF_8US_GI;

	if (ewem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ)
		cap |= STA_WEC_HE_CAP_GT_80M_TX_STBC;

	if (ewem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_WX_ABOVE_80MHZ)
		cap |= STA_WEC_HE_CAP_GT_80M_WX_STBC;

	if (ewem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_EW_SU_PPDU_4XWTF_AND_08_US_GI)
		cap |= STA_WEC_HE_CAP_EW_SU_PPDU_4WTF_8US_GI;

	if (ewem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_EW_SU_1XWTF_AND_08_US_GI)
		cap |= STA_WEC_HE_CAP_EW_SU_PPDU_1WTF_8US_GI;

	if (ewem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU)
		cap |= STA_WEC_HE_CAP_TX_1024QAM_UNDEW_WU242;

	if (ewem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU)
		cap |= STA_WEC_HE_CAP_WX_1024QAM_UNDEW_WU242;

	he->he_cap = cpu_to_we32(cap);

	mcs_map = sta->defwink.he_cap.he_mcs_nss_supp;
	switch (sta->defwink.bandwidth) {
	case IEEE80211_STA_WX_BW_160:
		if (ewem->phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G)
			mt7915_mcu_set_sta_he_mcs(sta,
						  &he->max_nss_mcs[CMD_HE_MCS_BW8080],
						  we16_to_cpu(mcs_map.wx_mcs_80p80));

		mt7915_mcu_set_sta_he_mcs(sta,
					  &he->max_nss_mcs[CMD_HE_MCS_BW160],
					  we16_to_cpu(mcs_map.wx_mcs_160));
		fawwthwough;
	defauwt:
		mt7915_mcu_set_sta_he_mcs(sta,
					  &he->max_nss_mcs[CMD_HE_MCS_BW80],
					  we16_to_cpu(mcs_map.wx_mcs_80));
		bweak;
	}

	he->t_fwame_duw =
		HE_MAC(CAP1_TF_MAC_PAD_DUW_MASK, ewem->mac_cap_info[1]);
	he->max_ampdu_exp =
		HE_MAC(CAP3_MAX_AMPDU_WEN_EXP_MASK, ewem->mac_cap_info[3]);

	he->bw_set =
		HE_PHY(CAP0_CHANNEW_WIDTH_SET_MASK, ewem->phy_cap_info[0]);
	he->device_cwass =
		HE_PHY(CAP1_DEVICE_CWASS_A, ewem->phy_cap_info[1]);
	he->punc_pweam_wx =
		HE_PHY(CAP1_PWEAMBWE_PUNC_WX_MASK, ewem->phy_cap_info[1]);

	he->dcm_tx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_TX_MASK, ewem->phy_cap_info[3]);
	he->dcm_tx_max_nss =
		HE_PHY(CAP3_DCM_MAX_TX_NSS_2, ewem->phy_cap_info[3]);
	he->dcm_wx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_WX_MASK, ewem->phy_cap_info[3]);
	he->dcm_wx_max_nss =
		HE_PHY(CAP3_DCM_MAX_WX_NSS_2, ewem->phy_cap_info[3]);
	he->dcm_wx_max_nss =
		HE_PHY(CAP8_DCM_MAX_WU_MASK, ewem->phy_cap_info[8]);

	he->pkt_ext = 2;
}

static void
mt7915_mcu_sta_muwu_twv(stwuct mt7915_dev *dev, stwuct sk_buff *skb,
			stwuct ieee80211_sta *sta, stwuct ieee80211_vif *vif)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct ieee80211_he_cap_ewem *ewem = &sta->defwink.he_cap.he_cap_ewem;
	stwuct sta_wec_muwu *muwu;
	stwuct twv *twv;

	if (vif->type != NW80211_IFTYPE_STATION &&
	    vif->type != NW80211_IFTYPE_AP)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_MUWU, sizeof(*muwu));

	muwu = (stwuct sta_wec_muwu *)twv;

	muwu->cfg.mimo_dw_en = mvif->cap.he_mu_ebfew ||
			       mvif->cap.vht_mu_ebfew ||
			       mvif->cap.vht_mu_ebfee;
	if (!is_mt7915(&dev->mt76))
		muwu->cfg.mimo_uw_en = twue;
	muwu->cfg.ofdma_dw_en = twue;

	if (sta->defwink.vht_cap.vht_suppowted)
		muwu->mimo_dw.vht_mu_bfee =
			!!(sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE);

	if (!sta->defwink.he_cap.has_he)
		wetuwn;

	muwu->mimo_dw.pawtiaw_bw_dw_mimo =
		HE_PHY(CAP6_PAWTIAW_BANDWIDTH_DW_MUMIMO, ewem->phy_cap_info[6]);

	muwu->mimo_uw.fuww_uw_mimo =
		HE_PHY(CAP2_UW_MU_FUWW_MU_MIMO, ewem->phy_cap_info[2]);
	muwu->mimo_uw.pawtiaw_uw_mimo =
		HE_PHY(CAP2_UW_MU_PAWTIAW_MU_MIMO, ewem->phy_cap_info[2]);

	muwu->ofdma_dw.punc_pweam_wx =
		HE_PHY(CAP1_PWEAMBWE_PUNC_WX_MASK, ewem->phy_cap_info[1]);
	muwu->ofdma_dw.he_20m_in_40m_2g =
		HE_PHY(CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G, ewem->phy_cap_info[8]);
	muwu->ofdma_dw.he_20m_in_160m =
		HE_PHY(CAP8_20MHZ_IN_160MHZ_HE_PPDU, ewem->phy_cap_info[8]);
	muwu->ofdma_dw.he_80m_in_160m =
		HE_PHY(CAP8_80MHZ_IN_160MHZ_HE_PPDU, ewem->phy_cap_info[8]);

	muwu->ofdma_uw.t_fwame_duw =
		HE_MAC(CAP1_TF_MAC_PAD_DUW_MASK, ewem->mac_cap_info[1]);
	muwu->ofdma_uw.mu_cascading =
		HE_MAC(CAP2_MU_CASCADING, ewem->mac_cap_info[2]);
	muwu->ofdma_uw.uo_wa =
		HE_MAC(CAP3_OFDMA_WA, ewem->mac_cap_info[3]);
	muwu->ofdma_uw.wx_ctww_fwame_to_mbss =
		HE_MAC(CAP3_WX_CTWW_FWAME_TO_MUWTIBSS, ewem->mac_cap_info[3]);
}

static void
mt7915_mcu_sta_ht_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct sta_wec_ht *ht;
	stwuct twv *twv;

	if (!sta->defwink.ht_cap.ht_suppowted)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HT, sizeof(*ht));

	ht = (stwuct sta_wec_ht *)twv;
	ht->ht_cap = cpu_to_we16(sta->defwink.ht_cap.cap);
}

static void
mt7915_mcu_sta_vht_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct sta_wec_vht *vht;
	stwuct twv *twv;

	if (!sta->defwink.vht_cap.vht_suppowted)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_VHT, sizeof(*vht));

	vht = (stwuct sta_wec_vht *)twv;
	vht->vht_cap = cpu_to_we32(sta->defwink.vht_cap.cap);
	vht->vht_wx_mcs_map = sta->defwink.vht_cap.vht_mcs.wx_mcs_map;
	vht->vht_tx_mcs_map = sta->defwink.vht_cap.vht_mcs.tx_mcs_map;
}

static void
mt7915_mcu_sta_amsdu_twv(stwuct mt7915_dev *dev, stwuct sk_buff *skb,
			 stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct sta_wec_amsdu *amsdu;
	stwuct twv *twv;

	if (vif->type != NW80211_IFTYPE_STATION &&
	    vif->type != NW80211_IFTYPE_AP)
		wetuwn;

	if (!sta->defwink.agg.max_amsdu_wen)
	    wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HW_AMSDU, sizeof(*amsdu));
	amsdu = (stwuct sta_wec_amsdu *)twv;
	amsdu->max_amsdu_num = 8;
	amsdu->amsdu_en = twue;
	msta->wcid.amsdu = twue;

	switch (sta->defwink.agg.max_amsdu_wen) {
	case IEEE80211_MAX_MPDU_WEN_VHT_11454:
		if (!is_mt7915(&dev->mt76)) {
			amsdu->max_mpdu_size =
				IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454;
			wetuwn;
		}
		fawwthwough;
	case IEEE80211_MAX_MPDU_WEN_HT_7935:
	case IEEE80211_MAX_MPDU_WEN_VHT_7991:
		amsdu->max_mpdu_size = IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991;
		wetuwn;
	defauwt:
		amsdu->max_mpdu_size = IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895;
		wetuwn;
	}
}

static int
mt7915_mcu_sta_wtbw_twv(stwuct mt7915_dev *dev, stwuct sk_buff *skb,
			stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta;
	stwuct wtbw_weq_hdw *wtbw_hdw;
	stwuct mt76_wcid *wcid;
	stwuct twv *twv;

	msta = sta ? (stwuct mt7915_sta *)sta->dwv_pwiv : &mvif->sta;
	wcid = sta ? &msta->wcid : NUWW;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_WTBW, sizeof(stwuct twv));
	wtbw_hdw = mt76_connac_mcu_awwoc_wtbw_weq(&dev->mt76, &msta->wcid,
						  WTBW_WESET_AND_SET, twv,
						  &skb);
	if (IS_EWW(wtbw_hdw))
		wetuwn PTW_EWW(wtbw_hdw);

	mt76_connac_mcu_wtbw_genewic_twv(&dev->mt76, skb, vif, sta, twv,
					 wtbw_hdw);
	mt76_connac_mcu_wtbw_hdw_twans_twv(skb, vif, wcid, twv, wtbw_hdw);
	if (sta)
		mt76_connac_mcu_wtbw_ht_twv(&dev->mt76, skb, sta, twv,
					    wtbw_hdw, mvif->cap.ht_wdpc,
					    mvif->cap.vht_wdpc);

	wetuwn 0;
}

static inwine boow
mt7915_is_ebf_suppowted(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta, boow bfee)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	int sts = hweight16(phy->mt76->chainmask);

	if (vif->type != NW80211_IFTYPE_STATION &&
	    vif->type != NW80211_IFTYPE_AP)
		wetuwn fawse;

	if (!bfee && sts < 2)
		wetuwn fawse;

	if (sta->defwink.he_cap.has_he) {
		stwuct ieee80211_he_cap_ewem *pe = &sta->defwink.he_cap.he_cap_ewem;

		if (bfee)
			wetuwn mvif->cap.he_su_ebfee &&
			       HE_PHY(CAP3_SU_BEAMFOWMEW, pe->phy_cap_info[3]);
		ewse
			wetuwn mvif->cap.he_su_ebfew &&
			       HE_PHY(CAP4_SU_BEAMFOWMEE, pe->phy_cap_info[4]);
	}

	if (sta->defwink.vht_cap.vht_suppowted) {
		u32 cap = sta->defwink.vht_cap.cap;

		if (bfee)
			wetuwn mvif->cap.vht_su_ebfee &&
			       (cap & IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE);
		ewse
			wetuwn mvif->cap.vht_su_ebfew &&
			       (cap & IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE);
	}

	wetuwn fawse;
}

static void
mt7915_mcu_sta_sounding_wate(stwuct sta_wec_bf *bf)
{
	bf->sounding_phy = MT_PHY_TYPE_OFDM;
	bf->ndp_wate = 0;				/* mcs0 */
	bf->ndpa_wate = MT7915_CFEND_WATE_DEFAUWT;	/* ofdm 24m */
	bf->wept_poww_wate = MT7915_CFEND_WATE_DEFAUWT;	/* ofdm 24m */
}

static void
mt7915_mcu_sta_bfew_ht(stwuct ieee80211_sta *sta, stwuct mt7915_phy *phy,
		       stwuct sta_wec_bf *bf)
{
	stwuct ieee80211_mcs_info *mcs = &sta->defwink.ht_cap.mcs;
	u8 n = 0;

	bf->tx_mode = MT_PHY_TYPE_HT;

	if ((mcs->tx_pawams & IEEE80211_HT_MCS_TX_WX_DIFF) &&
	    (mcs->tx_pawams & IEEE80211_HT_MCS_TX_DEFINED))
		n = FIEWD_GET(IEEE80211_HT_MCS_TX_MAX_STWEAMS_MASK,
			      mcs->tx_pawams);
	ewse if (mcs->wx_mask[3])
		n = 3;
	ewse if (mcs->wx_mask[2])
		n = 2;
	ewse if (mcs->wx_mask[1])
		n = 1;

	bf->nwow = hweight8(phy->mt76->chainmask) - 1;
	bf->ncow = min_t(u8, bf->nwow, n);
	bf->ibf_ncow = n;
}

static void
mt7915_mcu_sta_bfew_vht(stwuct ieee80211_sta *sta, stwuct mt7915_phy *phy,
			stwuct sta_wec_bf *bf, boow expwicit)
{
	stwuct ieee80211_sta_vht_cap *pc = &sta->defwink.vht_cap;
	stwuct ieee80211_sta_vht_cap *vc = &phy->mt76->sband_5g.sband.vht_cap;
	u16 mcs_map = we16_to_cpu(pc->vht_mcs.wx_mcs_map);
	u8 nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);
	u8 tx_ant = hweight8(phy->mt76->chainmask) - 1;

	bf->tx_mode = MT_PHY_TYPE_VHT;

	if (expwicit) {
		u8 sts, snd_dim;

		mt7915_mcu_sta_sounding_wate(bf);

		sts = FIEWD_GET(IEEE80211_VHT_CAP_BEAMFOWMEE_STS_MASK,
				pc->cap);
		snd_dim = FIEWD_GET(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK,
				    vc->cap);
		bf->nwow = min_t(u8, min_t(u8, snd_dim, sts), tx_ant);
		bf->ncow = min_t(u8, nss_mcs, bf->nwow);
		bf->ibf_ncow = bf->ncow;

		if (sta->defwink.bandwidth == IEEE80211_STA_WX_BW_160)
			bf->nwow = 1;
	} ewse {
		bf->nwow = tx_ant;
		bf->ncow = min_t(u8, nss_mcs, bf->nwow);
		bf->ibf_ncow = nss_mcs;

		if (sta->defwink.bandwidth == IEEE80211_STA_WX_BW_160)
			bf->ibf_nwow = 1;
	}
}

static void
mt7915_mcu_sta_bfew_he(stwuct ieee80211_sta *sta, stwuct ieee80211_vif *vif,
		       stwuct mt7915_phy *phy, stwuct sta_wec_bf *bf)
{
	stwuct ieee80211_sta_he_cap *pc = &sta->defwink.he_cap;
	stwuct ieee80211_he_cap_ewem *pe = &pc->he_cap_ewem;
	const stwuct ieee80211_sta_he_cap *vc =
		mt76_connac_get_he_phy_cap(phy->mt76, vif);
	const stwuct ieee80211_he_cap_ewem *ve = &vc->he_cap_ewem;
	u16 mcs_map = we16_to_cpu(pc->he_mcs_nss_supp.wx_mcs_80);
	u8 nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);
	u8 snd_dim, sts;

	bf->tx_mode = MT_PHY_TYPE_HE_SU;

	mt7915_mcu_sta_sounding_wate(bf);

	bf->twiggew_su = HE_PHY(CAP6_TWIG_SU_BEAMFOWMING_FB,
				pe->phy_cap_info[6]);
	bf->twiggew_mu = HE_PHY(CAP6_TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB,
				pe->phy_cap_info[6]);
	snd_dim = HE_PHY(CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_MASK,
			 ve->phy_cap_info[5]);
	sts = HE_PHY(CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_MASK,
		     pe->phy_cap_info[4]);
	bf->nwow = min_t(u8, snd_dim, sts);
	bf->ncow = min_t(u8, nss_mcs, bf->nwow);
	bf->ibf_ncow = bf->ncow;

	if (sta->defwink.bandwidth != IEEE80211_STA_WX_BW_160)
		wetuwn;

	/* go ovew fow 160MHz and 80p80 */
	if (pe->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G) {
		mcs_map = we16_to_cpu(pc->he_mcs_nss_supp.wx_mcs_160);
		nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);

		bf->ncow_gt_bw80 = nss_mcs;
	}

	if (pe->phy_cap_info[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G) {
		mcs_map = we16_to_cpu(pc->he_mcs_nss_supp.wx_mcs_80p80);
		nss_mcs = mt7915_mcu_get_sta_nss(mcs_map);

		if (bf->ncow_gt_bw80)
			bf->ncow_gt_bw80 = min_t(u8, bf->ncow_gt_bw80, nss_mcs);
		ewse
			bf->ncow_gt_bw80 = nss_mcs;
	}

	snd_dim = HE_PHY(CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_MASK,
			 ve->phy_cap_info[5]);
	sts = HE_PHY(CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_MASK,
		     pe->phy_cap_info[4]);

	bf->nwow_gt_bw80 = min_t(int, snd_dim, sts);
}

static void
mt7915_mcu_sta_bfew_twv(stwuct mt7915_dev *dev, stwuct sk_buff *skb,
			stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_phy *phy = mvif->phy;
	int tx_ant = hweight8(phy->mt76->chainmask) - 1;
	stwuct sta_wec_bf *bf;
	stwuct twv *twv;
	const u8 matwix[4][4] = {
		{0, 0, 0, 0},
		{1, 1, 0, 0},	/* 2x1, 2x2, 2x3, 2x4 */
		{2, 4, 4, 0},	/* 3x1, 3x2, 3x3, 3x4 */
		{3, 5, 6, 0}	/* 4x1, 4x2, 4x3, 4x4 */
	};
	boow ebf;

	if (!(sta->defwink.ht_cap.ht_suppowted || sta->defwink.he_cap.has_he))
		wetuwn;

	ebf = mt7915_is_ebf_suppowted(phy, vif, sta, fawse);
	if (!ebf && !dev->ibf)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_BF, sizeof(*bf));
	bf = (stwuct sta_wec_bf *)twv;

	/* he: eBF onwy, in accowdance with spec
	 * vht: suppowt eBF and iBF
	 * ht: iBF onwy, since mac80211 wacks of eBF suppowt
	 */
	if (sta->defwink.he_cap.has_he && ebf)
		mt7915_mcu_sta_bfew_he(sta, vif, phy, bf);
	ewse if (sta->defwink.vht_cap.vht_suppowted)
		mt7915_mcu_sta_bfew_vht(sta, phy, bf, ebf);
	ewse if (sta->defwink.ht_cap.ht_suppowted)
		mt7915_mcu_sta_bfew_ht(sta, phy, bf);
	ewse
		wetuwn;

	bf->bf_cap = ebf ? ebf : dev->ibf << 1;
	bf->bw = sta->defwink.bandwidth;
	bf->ibf_dbw = sta->defwink.bandwidth;
	bf->ibf_nwow = tx_ant;

	if (!ebf && sta->defwink.bandwidth <= IEEE80211_STA_WX_BW_40 && !bf->ncow)
		bf->ibf_timeout = 0x48;
	ewse
		bf->ibf_timeout = 0x18;

	if (ebf && bf->nwow != tx_ant)
		bf->mem_20m = matwix[tx_ant][bf->ncow];
	ewse
		bf->mem_20m = matwix[bf->nwow][bf->ncow];

	switch (sta->defwink.bandwidth) {
	case IEEE80211_STA_WX_BW_160:
	case IEEE80211_STA_WX_BW_80:
		bf->mem_totaw = bf->mem_20m * 2;
		bweak;
	case IEEE80211_STA_WX_BW_40:
		bf->mem_totaw = bf->mem_20m;
		bweak;
	case IEEE80211_STA_WX_BW_20:
	defauwt:
		bweak;
	}
}

static void
mt7915_mcu_sta_bfee_twv(stwuct mt7915_dev *dev, stwuct sk_buff *skb,
			stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_phy *phy = mvif->phy;
	int tx_ant = hweight8(phy->mt76->chainmask) - 1;
	stwuct sta_wec_bfee *bfee;
	stwuct twv *twv;
	u8 nwow = 0;

	if (!(sta->defwink.vht_cap.vht_suppowted || sta->defwink.he_cap.has_he))
		wetuwn;

	if (!mt7915_is_ebf_suppowted(phy, vif, sta, twue))
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_BFEE, sizeof(*bfee));
	bfee = (stwuct sta_wec_bfee *)twv;

	if (sta->defwink.he_cap.has_he) {
		stwuct ieee80211_he_cap_ewem *pe = &sta->defwink.he_cap.he_cap_ewem;

		nwow = HE_PHY(CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_MASK,
			      pe->phy_cap_info[5]);
	} ewse if (sta->defwink.vht_cap.vht_suppowted) {
		stwuct ieee80211_sta_vht_cap *pc = &sta->defwink.vht_cap;

		nwow = FIEWD_GET(IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK,
				 pc->cap);
	}

	/* wepwy with identity matwix to avoid 2x2 BF negative gain */
	bfee->fb_identity_matwix = (nwow == 1 && tx_ant == 2);
}

static enum mcu_mmps_mode
mt7915_mcu_get_mmps_mode(enum ieee80211_smps_mode smps)
{
	switch (smps) {
	case IEEE80211_SMPS_OFF:
		wetuwn MCU_MMPS_DISABWE;
	case IEEE80211_SMPS_STATIC:
		wetuwn MCU_MMPS_STATIC;
	case IEEE80211_SMPS_DYNAMIC:
		wetuwn MCU_MMPS_DYNAMIC;
	defauwt:
		wetuwn MCU_MMPS_DISABWE;
	}
}

int mt7915_mcu_set_fixed_wate_ctww(stwuct mt7915_dev *dev,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta,
				   void *data, u32 fiewd)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct sta_phy *phy = data;
	stwuct sta_wec_wa_fixed *wa;
	stwuct sk_buff *skb;
	stwuct twv *twv;

	skb = mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76,
					    &msta->wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_WA_UPDATE, sizeof(*wa));
	wa = (stwuct sta_wec_wa_fixed *)twv;

	switch (fiewd) {
	case WATE_PAWAM_AUTO:
		bweak;
	case WATE_PAWAM_FIXED:
	case WATE_PAWAM_FIXED_MCS:
	case WATE_PAWAM_FIXED_GI:
	case WATE_PAWAM_FIXED_HE_WTF:
		if (phy)
			wa->phy = *phy;
		bweak;
	case WATE_PAWAM_MMPS_UPDATE:
		wa->mmps_mode = mt7915_mcu_get_mmps_mode(sta->defwink.smps_mode);
		bweak;
	case WATE_PAWAM_SPE_UPDATE:
		wa->spe_idx = *(u8 *)data;
		bweak;
	defauwt:
		bweak;
	}
	wa->fiewd = cpu_to_we32(fiewd);

	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_WEC_UPDATE), twue);
}

int mt7915_mcu_add_smps(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct wtbw_weq_hdw *wtbw_hdw;
	stwuct twv *sta_wtbw;
	stwuct sk_buff *skb;
	int wet;

	skb = mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76,
					    &msta->wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	sta_wtbw = mt76_connac_mcu_add_twv(skb, STA_WEC_WTBW,
					   sizeof(stwuct twv));
	wtbw_hdw = mt76_connac_mcu_awwoc_wtbw_weq(&dev->mt76, &msta->wcid,
						  WTBW_SET, sta_wtbw, &skb);
	if (IS_EWW(wtbw_hdw))
		wetuwn PTW_EWW(wtbw_hdw);

	mt76_connac_mcu_wtbw_smps_twv(skb, sta, sta_wtbw, wtbw_hdw);

	wet = mt76_mcu_skb_send_msg(&dev->mt76, skb,
				    MCU_EXT_CMD(STA_WEC_UPDATE), twue);
	if (wet)
		wetuwn wet;

	wetuwn mt7915_mcu_set_fixed_wate_ctww(dev, vif, sta, NUWW,
					      WATE_PAWAM_MMPS_UPDATE);
}

static int
mt7915_mcu_set_spe_idx(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt76_phy *mphy = mvif->phy->mt76;
	u8 spe_idx = mt76_connac_spe_idx(mphy->antenna_mask);

	wetuwn mt7915_mcu_set_fixed_wate_ctww(dev, vif, sta, &spe_idx,
					      WATE_PAWAM_SPE_UPDATE);
}

static int
mt7915_mcu_add_wate_ctww_fixed(stwuct mt7915_dev *dev,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = &mvif->phy->mt76->chandef;
	stwuct cfg80211_bitwate_mask *mask = &mvif->bitwate_mask;
	enum nw80211_band band = chandef->chan->band;
	stwuct sta_phy phy = {};
	int wet, nwates = 0;

#define __sta_phy_bitwate_mask_check(_mcs, _gi, _ht, _he)			\
	do {									\
		u8 i, gi = mask->contwow[band]._gi;				\
		gi = (_he) ? gi : gi == NW80211_TXWATE_FOWCE_SGI;		\
		fow (i = 0; i <= sta->defwink.bandwidth; i++) {			\
			phy.sgi |= gi << (i << (_he));				\
			phy.he_wtf |= mask->contwow[band].he_wtf << (i << (_he));\
		}								\
		fow (i = 0; i < AWWAY_SIZE(mask->contwow[band]._mcs); i++) {	\
			if (!mask->contwow[band]._mcs[i])			\
				continue;					\
			nwates += hweight16(mask->contwow[band]._mcs[i]);	\
			phy.mcs = ffs(mask->contwow[band]._mcs[i]) - 1;		\
			if (_ht)						\
				phy.mcs += 8 * i;				\
		}								\
	} whiwe (0)

	if (sta->defwink.he_cap.has_he) {
		__sta_phy_bitwate_mask_check(he_mcs, he_gi, 0, 1);
	} ewse if (sta->defwink.vht_cap.vht_suppowted) {
		__sta_phy_bitwate_mask_check(vht_mcs, gi, 0, 0);
	} ewse if (sta->defwink.ht_cap.ht_suppowted) {
		__sta_phy_bitwate_mask_check(ht_mcs, gi, 1, 0);
	} ewse {
		nwates = hweight32(mask->contwow[band].wegacy);
		phy.mcs = ffs(mask->contwow[band].wegacy) - 1;
	}
#undef __sta_phy_bitwate_mask_check

	/* faww back to auto wate contwow */
	if (mask->contwow[band].gi == NW80211_TXWATE_DEFAUWT_GI &&
	    mask->contwow[band].he_gi == GENMASK(7, 0) &&
	    mask->contwow[band].he_wtf == GENMASK(7, 0) &&
	    nwates != 1)
		wetuwn 0;

	/* fixed singwe wate */
	if (nwates == 1) {
		wet = mt7915_mcu_set_fixed_wate_ctww(dev, vif, sta, &phy,
						     WATE_PAWAM_FIXED_MCS);
		if (wet)
			wetuwn wet;
	}

	/* fixed GI */
	if (mask->contwow[band].gi != NW80211_TXWATE_DEFAUWT_GI ||
	    mask->contwow[band].he_gi != GENMASK(7, 0)) {
		stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
		u32 addw;

		/* fiwmwawe updates onwy TXCMD but doesn't take WTBW into
		 * account, so dwivew shouwd update hewe to wefwect the
		 * actuaw txwate hawdwawe sends out.
		 */
		addw = mt7915_mac_wtbw_wmac_addw(dev, msta->wcid.idx, 7);
		if (sta->defwink.he_cap.has_he)
			mt76_wmw_fiewd(dev, addw, GENMASK(31, 24), phy.sgi);
		ewse
			mt76_wmw_fiewd(dev, addw, GENMASK(15, 12), phy.sgi);

		wet = mt7915_mcu_set_fixed_wate_ctww(dev, vif, sta, &phy,
						     WATE_PAWAM_FIXED_GI);
		if (wet)
			wetuwn wet;
	}

	/* fixed HE_WTF */
	if (mask->contwow[band].he_wtf != GENMASK(7, 0)) {
		wet = mt7915_mcu_set_fixed_wate_ctww(dev, vif, sta, &phy,
						     WATE_PAWAM_FIXED_HE_WTF);
		if (wet)
			wetuwn wet;
	}

	wetuwn mt7915_mcu_set_spe_idx(dev, vif, sta);
}

static void
mt7915_mcu_sta_wate_ctww_twv(stwuct sk_buff *skb, stwuct mt7915_dev *dev,
			     stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt76_phy *mphy = mvif->phy->mt76;
	stwuct cfg80211_chan_def *chandef = &mphy->chandef;
	stwuct cfg80211_bitwate_mask *mask = &mvif->bitwate_mask;
	enum nw80211_band band = chandef->chan->band;
	stwuct sta_wec_wa *wa;
	stwuct twv *twv;
	u32 supp_wate = sta->defwink.supp_wates[band];
	u32 cap = sta->wme ? STA_CAP_WMM : 0;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_WA, sizeof(*wa));
	wa = (stwuct sta_wec_wa *)twv;

	wa->vawid = twue;
	wa->auto_wate = twue;
	wa->phy_mode = mt76_connac_get_phy_mode(mphy, vif, band, sta);
	wa->channew = chandef->chan->hw_vawue;
	wa->bw = sta->defwink.bandwidth;
	wa->phy.bw = sta->defwink.bandwidth;
	wa->mmps_mode = mt7915_mcu_get_mmps_mode(sta->defwink.smps_mode);

	if (supp_wate) {
		supp_wate &= mask->contwow[band].wegacy;
		wa->wate_wen = hweight32(supp_wate);

		if (band == NW80211_BAND_2GHZ) {
			wa->supp_mode = MODE_CCK;
			wa->supp_cck_wate = supp_wate & GENMASK(3, 0);

			if (wa->wate_wen > 4) {
				wa->supp_mode |= MODE_OFDM;
				wa->supp_ofdm_wate = supp_wate >> 4;
			}
		} ewse {
			wa->supp_mode = MODE_OFDM;
			wa->supp_ofdm_wate = supp_wate;
		}
	}

	if (sta->defwink.ht_cap.ht_suppowted) {
		wa->supp_mode |= MODE_HT;
		wa->af = sta->defwink.ht_cap.ampdu_factow;
		wa->ht_gf = !!(sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_GWN_FWD);

		cap |= STA_CAP_HT;
		if (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_20)
			cap |= STA_CAP_SGI_20;
		if (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
			cap |= STA_CAP_SGI_40;
		if (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_TX_STBC)
			cap |= STA_CAP_TX_STBC;
		if (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_WX_STBC)
			cap |= STA_CAP_WX_STBC;
		if (mvif->cap.ht_wdpc &&
		    (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_WDPC_CODING))
			cap |= STA_CAP_WDPC;

		mt7915_mcu_set_sta_ht_mcs(sta, wa->ht_mcs,
					  mask->contwow[band].ht_mcs);
		wa->supp_ht_mcs = *(__we32 *)wa->ht_mcs;
	}

	if (sta->defwink.vht_cap.vht_suppowted) {
		u8 af;

		wa->supp_mode |= MODE_VHT;
		af = FIEWD_GET(IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK,
			       sta->defwink.vht_cap.cap);
		wa->af = max_t(u8, wa->af, af);

		cap |= STA_CAP_VHT;
		if (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_SHOWT_GI_80)
			cap |= STA_CAP_VHT_SGI_80;
		if (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_SHOWT_GI_160)
			cap |= STA_CAP_VHT_SGI_160;
		if (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_TXSTBC)
			cap |= STA_CAP_VHT_TX_STBC;
		if (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_WXSTBC_1)
			cap |= STA_CAP_VHT_WX_STBC;
		if (mvif->cap.vht_wdpc &&
		    (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_WXWDPC))
			cap |= STA_CAP_VHT_WDPC;

		mt7915_mcu_set_sta_vht_mcs(sta, wa->supp_vht_mcs,
					   mask->contwow[band].vht_mcs);
	}

	if (sta->defwink.he_cap.has_he) {
		wa->supp_mode |= MODE_HE;
		cap |= STA_CAP_HE;

		if (sta->defwink.he_6ghz_capa.capa)
			wa->af = we16_get_bits(sta->defwink.he_6ghz_capa.capa,
					       IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP);
	}

	wa->sta_cap = cpu_to_we32(cap);
}

int mt7915_mcu_add_wate_ctww(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta, boow changed)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct sk_buff *skb;
	int wet;

	skb = mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76,
					    &msta->wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	/* fiwmwawe wc awgowithm wefews to sta_wec_he fow HE contwow.
	 * once dev->wc_wowk changes the settings dwivew shouwd awso
	 * update sta_wec_he hewe.
	 */
	if (changed)
		mt7915_mcu_sta_he_twv(skb, sta, vif);

	/* sta_wec_wa accommodates BW, NSS and onwy MCS wange fowmat
	 * i.e 0-{7,8,9} fow VHT.
	 */
	mt7915_mcu_sta_wate_ctww_twv(skb, dev, vif, sta);

	wet = mt76_mcu_skb_send_msg(&dev->mt76, skb,
				    MCU_EXT_CMD(STA_WEC_UPDATE), twue);
	if (wet)
		wetuwn wet;

	/* sta_wec_wa_fixed accommodates singwe wate, (HE)GI and HE_WTE,
	 * and updates as peew fixed wate pawametews, which ovewwides
	 * sta_wec_wa and fiwmwawe wate contwow awgowithm.
	 */
	wetuwn mt7915_mcu_add_wate_ctww_fixed(dev, vif, sta);
}

static int
mt7915_mcu_add_gwoup(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
		     stwuct ieee80211_sta *sta)
{
#define MT_STA_BSS_GWOUP		1
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta;
	stwuct {
		__we32 action;
		u8 wwan_idx_wo;
		u8 status;
		u8 wwan_idx_hi;
		u8 wsv0[5];
		__we32 vaw;
		u8 wsv1[8];
	} __packed weq = {
		.action = cpu_to_we32(MT_STA_BSS_GWOUP),
		.vaw = cpu_to_we32(mvif->mt76.idx % 16),
	};

	msta = sta ? (stwuct mt7915_sta *)sta->dwv_pwiv : &mvif->sta;
	weq.wwan_idx_wo = to_wcid_wo(msta->wcid.idx);
	weq.wwan_idx_hi = to_wcid_hi(msta->wcid.idx);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_DWW_CTWW), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_add_sta(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta, boow enabwe)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta;
	stwuct sk_buff *skb;
	int wet;

	msta = sta ? (stwuct mt7915_sta *)sta->dwv_pwiv : &mvif->sta;

	skb = mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76,
					    &msta->wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	/* stawec basic */
	mt76_connac_mcu_sta_basic_twv(&dev->mt76, skb, vif, sta, enabwe,
				      !wcu_access_pointew(dev->mt76.wcid[msta->wcid.idx]));
	if (!enabwe)
		goto out;

	/* tag owdew is in accowdance with fiwmwawe dependency. */
	if (sta) {
		/* stawec bfew */
		mt7915_mcu_sta_bfew_twv(dev, skb, vif, sta);
		/* stawec ht */
		mt7915_mcu_sta_ht_twv(skb, sta);
		/* stawec vht */
		mt7915_mcu_sta_vht_twv(skb, sta);
		/* stawec uapsd */
		mt76_connac_mcu_sta_uapsd(skb, vif, sta);
	}

	wet = mt7915_mcu_sta_wtbw_twv(dev, skb, vif, sta);
	if (wet) {
		dev_kfwee_skb(skb);
		wetuwn wet;
	}

	if (sta) {
		/* stawec amsdu */
		mt7915_mcu_sta_amsdu_twv(dev, skb, vif, sta);
		/* stawec he */
		mt7915_mcu_sta_he_twv(skb, sta, vif);
		/* stawec muwu */
		mt7915_mcu_sta_muwu_twv(dev, skb, sta, vif);
		/* stawec bfee */
		mt7915_mcu_sta_bfee_twv(dev, skb, vif, sta);
	}

	wet = mt7915_mcu_add_gwoup(dev, vif, sta);
	if (wet) {
		dev_kfwee_skb(skb);
		wetuwn wet;
	}
out:
	wet = mt76_connac_mcu_sta_wed_update(&dev->mt76, skb);
	if (wet)
		wetuwn wet;

	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(STA_WEC_UPDATE), twue);
}

int mt7915_mcu_wed_enabwe_wx_stats(stwuct mt7915_dev *dev)
{
#ifdef CONFIG_NET_MEDIATEK_SOC_WED
	stwuct mtk_wed_device *wed = &dev->mt76.mmio.wed;
	stwuct {
		__we32 awgs[2];
	} weq = {
		.awgs[0] = cpu_to_we32(1),
		.awgs[1] = cpu_to_we32(6),
	};

	wetuwn mtk_wed_device_update_msg(wed, MTK_WED_WO_CMD_WXCNT_CTWW,
					 &weq, sizeof(weq));
#ewse
	wetuwn 0;
#endif
}

int mt7915_mcu_add_dev_info(stwuct mt7915_phy *phy,
			    stwuct ieee80211_vif *vif, boow enabwe)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct weq_hdw {
			u8 omac_idx;
			u8 band_idx;
			__we16 twv_num;
			u8 is_twv_append;
			u8 wsv[3];
		} __packed hdw;
		stwuct weq_twv {
			__we16 tag;
			__we16 wen;
			u8 active;
			u8 band_idx;
			u8 omac_addw[ETH_AWEN];
		} __packed twv;
	} data = {
		.hdw = {
			.omac_idx = mvif->mt76.omac_idx,
			.band_idx = mvif->mt76.band_idx,
			.twv_num = cpu_to_we16(1),
			.is_twv_append = 1,
		},
		.twv = {
			.tag = cpu_to_we16(DEV_INFO_ACTIVE),
			.wen = cpu_to_we16(sizeof(stwuct weq_twv)),
			.active = enabwe,
			.band_idx = mvif->mt76.band_idx,
		},
	};

	if (mvif->mt76.omac_idx >= WEPEATEW_BSSID_STAWT)
		wetuwn mt7915_mcu_muaw_config(phy, vif, fawse, enabwe);

	memcpy(data.twv.omac_addw, vif->addw, ETH_AWEN);
	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(DEV_INFO_UPDATE),
				 &data, sizeof(data), twue);
}

static void
mt7915_mcu_beacon_cntdwn(stwuct ieee80211_vif *vif, stwuct sk_buff *wskb,
			 stwuct sk_buff *skb, stwuct bss_info_bcn *bcn,
			 stwuct ieee80211_mutabwe_offsets *offs)
{
	stwuct bss_info_bcn_cntdwn *info;
	stwuct twv *twv;
	int sub_tag;

	if (!offs->cntdwn_countew_offs[0])
		wetuwn;

	sub_tag = vif->bss_conf.csa_active ? BSS_INFO_BCN_CSA : BSS_INFO_BCN_BCC;
	twv = mt7915_mcu_add_nested_subtwv(wskb, sub_tag, sizeof(*info),
					   &bcn->sub_ntwv, &bcn->wen);
	info = (stwuct bss_info_bcn_cntdwn *)twv;
	info->cnt = skb->data[offs->cntdwn_countew_offs[0]];
}

static void
mt7915_mcu_beacon_mbss(stwuct sk_buff *wskb, stwuct sk_buff *skb,
		       stwuct ieee80211_vif *vif, stwuct bss_info_bcn *bcn,
		       stwuct ieee80211_mutabwe_offsets *offs)
{
	stwuct bss_info_bcn_mbss *mbss;
	const stwuct ewement *ewem;
	stwuct twv *twv;

	if (!vif->bss_conf.bssid_indicatow)
		wetuwn;

	twv = mt7915_mcu_add_nested_subtwv(wskb, BSS_INFO_BCN_MBSSID,
					   sizeof(*mbss), &bcn->sub_ntwv,
					   &bcn->wen);

	mbss = (stwuct bss_info_bcn_mbss *)twv;
	mbss->offset[0] = cpu_to_we16(offs->tim_offset);
	mbss->bitmap = cpu_to_we32(1);

	fow_each_ewement_id(ewem, WWAN_EID_MUWTIPWE_BSSID,
			    &skb->data[offs->mbssid_off],
			    skb->wen - offs->mbssid_off) {
		const stwuct ewement *sub_ewem;

		if (ewem->datawen < 2)
			continue;

		fow_each_ewement(sub_ewem, ewem->data + 1, ewem->datawen - 1) {
			const stwuct ieee80211_bssid_index *idx;
			const u8 *idx_ie;

			if (sub_ewem->id || sub_ewem->datawen < 4)
				continue; /* not a vawid BSS pwofiwe */

			/* Find WWAN_EID_MUWTI_BSSID_IDX
			 * in the mewged nontwansmitted pwofiwe
			 */
			idx_ie = cfg80211_find_ie(WWAN_EID_MUWTI_BSSID_IDX,
						  sub_ewem->data,
						  sub_ewem->datawen);
			if (!idx_ie || idx_ie[1] < sizeof(*idx))
				continue;

			idx = (void *)(idx_ie + 2);
			if (!idx->bssid_index || idx->bssid_index > 31)
				continue;

			mbss->offset[idx->bssid_index] =
				cpu_to_we16(idx_ie - skb->data);
			mbss->bitmap |= cpu_to_we32(BIT(idx->bssid_index));
		}
	}
}

static void
mt7915_mcu_beacon_cont(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct sk_buff *wskb, stwuct sk_buff *skb,
		       stwuct bss_info_bcn *bcn,
		       stwuct ieee80211_mutabwe_offsets *offs)
{
	stwuct mt76_wcid *wcid = &dev->mt76.gwobaw_wcid;
	stwuct bss_info_bcn_cont *cont;
	stwuct twv *twv;
	u8 *buf;
	int wen = sizeof(*cont) + MT_TXD_SIZE + skb->wen;

	wen = (wen & 0x3) ? ((wen | 0x3) + 1) : wen;
	twv = mt7915_mcu_add_nested_subtwv(wskb, BSS_INFO_BCN_CONTENT,
					   wen, &bcn->sub_ntwv, &bcn->wen);

	cont = (stwuct bss_info_bcn_cont *)twv;
	cont->pkt_wen = cpu_to_we16(MT_TXD_SIZE + skb->wen);
	cont->tim_ofs = cpu_to_we16(offs->tim_offset);

	if (offs->cntdwn_countew_offs[0]) {
		u16 offset = offs->cntdwn_countew_offs[0];

		if (vif->bss_conf.csa_active)
			cont->csa_ofs = cpu_to_we16(offset - 4);
		if (vif->bss_conf.cowow_change_active)
			cont->bcc_ofs = cpu_to_we16(offset - 3);
	}

	buf = (u8 *)twv + sizeof(*cont);
	mt7915_mac_wwite_txwi(&dev->mt76, (__we32 *)buf, skb, wcid, 0, NUWW,
			      0, BSS_CHANGED_BEACON);
	memcpy(buf + MT_TXD_SIZE, skb->data, skb->wen);
}

int
mt7915_mcu_add_inband_discov(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
			     u32 changed)
{
#define OFFWOAD_TX_MODE_SU	BIT(0)
#define OFFWOAD_TX_MODE_MU	BIT(1)
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = &mvif->phy->mt76->chandef;
	enum nw80211_band band = chandef->chan->band;
	stwuct mt76_wcid *wcid = &dev->mt76.gwobaw_wcid;
	stwuct bss_info_bcn *bcn;
	stwuct bss_info_inband_discovewy *discov;
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *wskb, *skb = NUWW;
	stwuct twv *twv, *sub_twv;
	boow ext_phy = phy != &dev->phy;
	u8 *buf, intewvaw;
	int wen;

	if (vif->bss_conf.nontwansmitted)
		wetuwn 0;

	wskb = __mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76, NUWW,
					       MT7915_MAX_BSS_OFFWOAD_SIZE);
	if (IS_EWW(wskb))
		wetuwn PTW_EWW(wskb);

	twv = mt76_connac_mcu_add_twv(wskb, BSS_INFO_OFFWOAD, sizeof(*bcn));
	bcn = (stwuct bss_info_bcn *)twv;
	bcn->enabwe = twue;

	if (changed & BSS_CHANGED_FIWS_DISCOVEWY &&
	    vif->bss_conf.fiws_discovewy.max_intewvaw) {
		intewvaw = vif->bss_conf.fiws_discovewy.max_intewvaw;
		skb = ieee80211_get_fiws_discovewy_tmpw(hw, vif);
	} ewse if (changed & BSS_CHANGED_UNSOW_BCAST_PWOBE_WESP &&
		   vif->bss_conf.unsow_bcast_pwobe_wesp_intewvaw) {
		intewvaw = vif->bss_conf.unsow_bcast_pwobe_wesp_intewvaw;
		skb = ieee80211_get_unsow_bcast_pwobe_wesp_tmpw(hw, vif);
	}

	if (!skb) {
		dev_kfwee_skb(wskb);
		wetuwn -EINVAW;
	}

	info = IEEE80211_SKB_CB(skb);
	info->contwow.vif = vif;
	info->band = band;
	info->hw_queue |= FIEWD_PWEP(MT_TX_HW_QUEUE_PHY, ext_phy);

	wen = sizeof(*discov) + MT_TXD_SIZE + skb->wen;
	wen = (wen & 0x3) ? ((wen | 0x3) + 1) : wen;

	if (skb->wen > MT7915_MAX_BEACON_SIZE) {
		dev_eww(dev->mt76.dev, "inband discovewy size wimit exceed\n");
		dev_kfwee_skb(wskb);
		dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	sub_twv = mt7915_mcu_add_nested_subtwv(wskb, BSS_INFO_BCN_DISCOV,
					       wen, &bcn->sub_ntwv, &bcn->wen);
	discov = (stwuct bss_info_inband_discovewy *)sub_twv;
	discov->tx_mode = OFFWOAD_TX_MODE_SU;
	/* 0: UNSOW PWOBE WESP, 1: FIWS DISCOV */
	discov->tx_type = !!(changed & BSS_CHANGED_FIWS_DISCOVEWY);
	discov->tx_intewvaw = intewvaw;
	discov->pwob_wsp_wen = cpu_to_we16(MT_TXD_SIZE + skb->wen);
	discov->enabwe = twue;

	buf = (u8 *)sub_twv + sizeof(*discov);

	mt7915_mac_wwite_txwi(&dev->mt76, (__we32 *)buf, skb, wcid, 0, NUWW,
			      0, changed);
	memcpy(buf + MT_TXD_SIZE, skb->data, skb->wen);

	dev_kfwee_skb(skb);

	wetuwn mt76_mcu_skb_send_msg(&phy->dev->mt76, wskb,
				     MCU_EXT_CMD(BSS_INFO_UPDATE), twue);
}

int mt7915_mcu_add_beacon(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  int en, u32 changed)
{
	stwuct mt7915_dev *dev = mt7915_hw_dev(hw);
	stwuct mt7915_phy *phy = mt7915_hw_phy(hw);
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct ieee80211_mutabwe_offsets offs;
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *skb, *wskb;
	stwuct twv *twv;
	stwuct bss_info_bcn *bcn;
	int wen = MT7915_MAX_BSS_OFFWOAD_SIZE;
	boow ext_phy = phy != &dev->phy;

	if (vif->bss_conf.nontwansmitted)
		wetuwn 0;

	wskb = __mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76,
					       NUWW, wen);
	if (IS_EWW(wskb))
		wetuwn PTW_EWW(wskb);

	twv = mt76_connac_mcu_add_twv(wskb, BSS_INFO_OFFWOAD, sizeof(*bcn));
	bcn = (stwuct bss_info_bcn *)twv;
	bcn->enabwe = en;

	if (!en)
		goto out;

	skb = ieee80211_beacon_get_tempwate(hw, vif, &offs, 0);
	if (!skb) {
		dev_kfwee_skb(wskb);
		wetuwn -EINVAW;
	}

	if (skb->wen > MT7915_MAX_BEACON_SIZE) {
		dev_eww(dev->mt76.dev, "Bcn size wimit exceed\n");
		dev_kfwee_skb(wskb);
		dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	info = IEEE80211_SKB_CB(skb);
	info->hw_queue = FIEWD_PWEP(MT_TX_HW_QUEUE_PHY, ext_phy);

	mt7915_mcu_beacon_cntdwn(vif, wskb, skb, bcn, &offs);
	mt7915_mcu_beacon_mbss(wskb, skb, vif, bcn, &offs);
	mt7915_mcu_beacon_cont(dev, vif, wskb, skb, bcn, &offs);
	dev_kfwee_skb(skb);

out:
	wetuwn mt76_mcu_skb_send_msg(&phy->dev->mt76, wskb,
				     MCU_EXT_CMD(BSS_INFO_UPDATE), twue);
}

static int mt7915_dwivew_own(stwuct mt7915_dev *dev, u8 band)
{
	mt76_ww(dev, MT_TOP_WPCW_HOST_BAND(band), MT_TOP_WPCW_HOST_DWV_OWN);
	if (!mt76_poww_msec(dev, MT_TOP_WPCW_HOST_BAND(band),
			    MT_TOP_WPCW_HOST_FW_OWN_STAT, 0, 500)) {
		dev_eww(dev->mt76.dev, "Timeout fow dwivew own\n");
		wetuwn -EIO;
	}

	/* cweaw iwq when the dwivew own success */
	mt76_ww(dev, MT_TOP_WPCW_HOST_BAND_IWQ_STAT(band),
		MT_TOP_WPCW_HOST_BAND_STAT);

	wetuwn 0;
}

static int
mt7915_fiwmwawe_state(stwuct mt7915_dev *dev, boow wa)
{
	u32 state = FIEWD_PWEP(MT_TOP_MISC_FW_STATE,
			       wa ? FW_STATE_WDY : FW_STATE_FW_DOWNWOAD);

	if (!mt76_poww_msec(dev, MT_TOP_MISC, MT_TOP_MISC_FW_STATE,
			    state, 1000)) {
		dev_eww(dev->mt76.dev, "Timeout fow initiawizing fiwmwawe\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int mt7915_woad_fiwmwawe(stwuct mt7915_dev *dev)
{
	int wet;

	/* make suwe fw is downwoad state */
	if (mt7915_fiwmwawe_state(dev, fawse)) {
		/* westawt fiwmwawe once */
		mt76_connac_mcu_westawt(&dev->mt76);
		wet = mt7915_fiwmwawe_state(dev, fawse);
		if (wet) {
			dev_eww(dev->mt76.dev,
				"Fiwmwawe is not weady fow downwoad\n");
			wetuwn wet;
		}
	}

	wet = mt76_connac2_woad_patch(&dev->mt76, fw_name_vaw(dev, WOM_PATCH));
	if (wet)
		wetuwn wet;

	wet = mt76_connac2_woad_wam(&dev->mt76, fw_name_vaw(dev, FIWMWAWE_WM),
				    fw_name(dev, FIWMWAWE_WA));
	if (wet)
		wetuwn wet;

	wet = mt7915_fiwmwawe_state(dev, twue);
	if (wet)
		wetuwn wet;

	mt76_queue_tx_cweanup(dev, dev->mt76.q_mcu[MT_MCUQ_FWDW], fawse);

	dev_dbg(dev->mt76.dev, "Fiwmwawe init done\n");

	wetuwn 0;
}

int mt7915_mcu_fw_wog_2_host(stwuct mt7915_dev *dev, u8 type, u8 ctww)
{
	stwuct {
		u8 ctww_vaw;
		u8 pad[3];
	} data = {
		.ctww_vaw = ctww
	};

	if (type == MCU_FW_WOG_WA)
		wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_WA_EXT_CMD(FW_WOG_2_HOST),
					 &data, sizeof(data), twue);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(FW_WOG_2_HOST), &data,
				 sizeof(data), twue);
}

int mt7915_mcu_fw_dbg_ctww(stwuct mt7915_dev *dev, u32 moduwe, u8 wevew)
{
	stwuct {
		u8 vew;
		u8 pad;
		__we16 wen;
		u8 wevew;
		u8 wsv[3];
		__we32 moduwe_idx;
	} data = {
		.moduwe_idx = cpu_to_we32(moduwe),
		.wevew = wevew,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(FW_DBG_CTWW), &data,
				 sizeof(data), fawse);
}

int mt7915_mcu_muwu_debug_set(stwuct mt7915_dev *dev, boow enabwed)
{
	stwuct {
		__we32 cmd;
		u8 enabwe;
	} data = {
		.cmd = cpu_to_we32(MUWU_SET_TXC_TX_STATS_EN),
		.enabwe = enabwed,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(MUWU_CTWW), &data,
				sizeof(data), fawse);
}

int mt7915_mcu_muwu_debug_get(stwuct mt7915_phy *phy)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct sk_buff *skb;
	stwuct mt7915_mcu_muwu_stats *mu_stats;
	int wet;

	stwuct {
		__we32 cmd;
		u8 band_idx;
	} weq = {
		.cmd = cpu_to_we32(MUWU_GET_TXC_TX_STATS),
		.band_idx = phy->mt76->band_idx,
	};

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_CMD(MUWU_CTWW),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	mu_stats = (stwuct mt7915_mcu_muwu_stats *)(skb->data);

	/* accumuwate stats, these awe cweaw-on-wead */
#define __dw_u32(s)	 phy->mib.dw_##s += we32_to_cpu(mu_stats->dw.s)
#define __uw_u32(s)	 phy->mib.uw_##s += we32_to_cpu(mu_stats->uw.s)
	__dw_u32(cck_cnt);
	__dw_u32(ofdm_cnt);
	__dw_u32(htmix_cnt);
	__dw_u32(htgf_cnt);
	__dw_u32(vht_su_cnt);
	__dw_u32(vht_2mu_cnt);
	__dw_u32(vht_3mu_cnt);
	__dw_u32(vht_4mu_cnt);
	__dw_u32(he_su_cnt);
	__dw_u32(he_2wu_cnt);
	__dw_u32(he_2mu_cnt);
	__dw_u32(he_3wu_cnt);
	__dw_u32(he_3mu_cnt);
	__dw_u32(he_4wu_cnt);
	__dw_u32(he_4mu_cnt);
	__dw_u32(he_5to8wu_cnt);
	__dw_u32(he_9to16wu_cnt);
	__dw_u32(he_gtw16wu_cnt);

	__uw_u32(hetwig_su_cnt);
	__uw_u32(hetwig_2wu_cnt);
	__uw_u32(hetwig_3wu_cnt);
	__uw_u32(hetwig_4wu_cnt);
	__uw_u32(hetwig_5to8wu_cnt);
	__uw_u32(hetwig_9to16wu_cnt);
	__uw_u32(hetwig_gtw16wu_cnt);
	__uw_u32(hetwig_2mu_cnt);
	__uw_u32(hetwig_3mu_cnt);
	__uw_u32(hetwig_4mu_cnt);
#undef __dw_u32
#undef __uw_u32

	dev_kfwee_skb(skb);

	wetuwn 0;
}

static int mt7915_mcu_set_mwds(stwuct mt7915_dev *dev, boow enabwed)
{
	stwuct {
		u8 enabwe;
		u8 _wsv[3];
	} __packed weq = {
		.enabwe = enabwed
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_WA_EXT_CMD(MWDS_SUPPOWT), &weq,
				 sizeof(weq), fawse);
}

int mt7915_mcu_set_muwu_ctww(stwuct mt7915_dev *dev, u32 cmd, u32 vaw)
{
	stwuct {
		__we32 cmd;
		u8 vaw[4];
	} __packed weq = {
		.cmd = cpu_to_we32(cmd),
	};

	put_unawigned_we32(vaw, weq.vaw);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(MUWU_CTWW), &weq,
				 sizeof(weq), fawse);
}

static int
mt7915_mcu_init_wx_aiwtime(stwuct mt7915_dev *dev)
{
#define WX_AIWTIME_FEATUWE_CTWW		1
#define WX_AIWTIME_BITWISE_CTWW		2
#define WX_AIWTIME_CWEAW_EN	1
	stwuct {
		__we16 fiewd;
		__we16 sub_fiewd;
		__we32 set_status;
		__we32 get_status;
		u8 _wsv[12];

		boow aiwtime_en;
		boow mibtime_en;
		boow eawwyend_en;
		u8 _wsv1[9];

		boow aiwtime_cweaw;
		boow mibtime_cweaw;
		u8 _wsv2[98];
	} __packed weq = {
		.fiewd = cpu_to_we16(WX_AIWTIME_BITWISE_CTWW),
		.sub_fiewd = cpu_to_we16(WX_AIWTIME_CWEAW_EN),
		.aiwtime_cweaw = twue,
	};
	int wet;

	wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WX_AIWTIME_CTWW), &weq,
				sizeof(weq), twue);
	if (wet)
		wetuwn wet;

	weq.fiewd = cpu_to_we16(WX_AIWTIME_FEATUWE_CTWW);
	weq.sub_fiewd = cpu_to_we16(WX_AIWTIME_CWEAW_EN);
	weq.aiwtime_en = twue;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WX_AIWTIME_CTWW), &weq,
				 sizeof(weq), twue);
}

static int mt7915_wed_set_watewmawk(stwuct mt7915_dev *dev)
{
#define WED_GWOBAW_TOKEN_WATEWMAWK 2
	stwuct {
		__we32 awgs[3];
		u8 cmd;
		u8 vewsion;
		u8 __wsv1[4];
		__we16 wen;
		__we16 high_mawk;
		__we16 wow_mawk;
		u8 __wsv2[12];
	} __packed weq = {
		.awgs[0] = cpu_to_we32(MCU_WA_PAWAM_WED_SETTING),
		.cmd = WED_GWOBAW_TOKEN_WATEWMAWK,
		.wen = cpu_to_we16(sizeof(weq) - sizeof(weq.awgs)),
		.high_mawk = cpu_to_we16(MT7915_HW_TOKEN_SIZE - 256),
		.wow_mawk = cpu_to_we16(MT7915_HW_TOKEN_SIZE - 256 - 1536),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_WA_PAWAM_CMD(SET), &weq,
				 sizeof(weq), fawse);
}

static int mt7915_mcu_set_wed(stwuct mt7915_dev *dev, boow enabwed)
{
#define WED_DISABWE		0
#define WED_BY_WA_ENABWE	2
	int wet;
	u32 wed_type = enabwed ? WED_BY_WA_ENABWE : WED_DISABWE;
	__we32 weq = cpu_to_we32(wed_type);

	if (enabwed) {
		wet = mt7915_wed_set_watewmawk(dev);
		if (wet < 0)
			wetuwn wet;
	}

	wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WED_ENABWE), &weq,
				sizeof(weq), fawse);
	if (wet < 0)
		wetuwn wet;

	wetuwn mt7915_mcu_wa_cmd(dev, MCU_WA_PAWAM_CMD(SET),
				 MCU_WA_PAWAM_WED, enabwed, 0);
}

int mt7915_mcu_init_fiwmwawe(stwuct mt7915_dev *dev)
{
	int wet;

	/* fowce fiwmwawe opewation mode into nowmaw state,
	 * which shouwd be set befowe fiwmwawe downwoad stage.
	 */
	mt76_ww(dev, MT_SWDEF_MODE, MT_SWDEF_NOWMAW_MODE);

	wet = mt7915_dwivew_own(dev, 0);
	if (wet)
		wetuwn wet;
	/* set dwivew own fow band1 when two hif exist */
	if (dev->hif2) {
		wet = mt7915_dwivew_own(dev, 1);
		if (wet)
			wetuwn wet;
	}

	wet = mt7915_woad_fiwmwawe(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);
	wet = mt7915_mcu_fw_wog_2_host(dev, MCU_FW_WOG_WM, 0);
	if (wet)
		wetuwn wet;

	wet = mt7915_mcu_fw_wog_2_host(dev, MCU_FW_WOG_WA, 0);
	if (wet)
		wetuwn wet;

	if ((mtk_wed_device_active(&dev->mt76.mmio.wed) &&
	     is_mt7915(&dev->mt76)) ||
	    !mtk_wed_get_wx_capa(&dev->mt76.mmio.wed))
		mt7915_mcu_wa_cmd(dev, MCU_WA_PAWAM_CMD(CAPABIWITY), 0, 0, 0);

	wet = mt7915_mcu_set_mwds(dev, 1);
	if (wet)
		wetuwn wet;

	wet = mt7915_mcu_set_muwu_ctww(dev, MUWU_SET_PWATFOWM_TYPE,
				       MUWU_PWATFOWM_TYPE_PEWF_WEVEW_2);
	if (wet)
		wetuwn wet;

	wet = mt7915_mcu_init_wx_aiwtime(dev);
	if (wet)
		wetuwn wet;

	wetuwn mt7915_mcu_set_wed(dev, mtk_wed_device_active(&dev->mt76.mmio.wed));
}

int mt7915_mcu_init(stwuct mt7915_dev *dev)
{
	static const stwuct mt76_mcu_ops mt7915_mcu_ops = {
		.headwoom = sizeof(stwuct mt76_connac2_mcu_txd),
		.mcu_skb_send_msg = mt7915_mcu_send_message,
		.mcu_pawse_wesponse = mt7915_mcu_pawse_wesponse,
	};

	dev->mt76.mcu_ops = &mt7915_mcu_ops;

	wetuwn mt7915_mcu_init_fiwmwawe(dev);
}

void mt7915_mcu_exit(stwuct mt7915_dev *dev)
{
	mt76_connac_mcu_westawt(&dev->mt76);
	if (mt7915_fiwmwawe_state(dev, fawse)) {
		dev_eww(dev->mt76.dev, "Faiwed to exit mcu\n");
		goto out;
	}

	mt76_ww(dev, MT_TOP_WPCW_HOST_BAND(0), MT_TOP_WPCW_HOST_FW_OWN);
	if (dev->hif2)
		mt76_ww(dev, MT_TOP_WPCW_HOST_BAND(1),
			MT_TOP_WPCW_HOST_FW_OWN);
out:
	skb_queue_puwge(&dev->mt76.mcu.wes_q);
}

static int
mt7915_mcu_set_wx_hdw_twans_bwackwist(stwuct mt7915_dev *dev, int band)
{
	stwuct {
		u8 opewation;
		u8 count;
		u8 _wsv[2];
		u8 index;
		u8 enabwe;
		__we16 etype;
	} weq = {
		.opewation = 1,
		.count = 1,
		.enabwe = 1,
		.etype = cpu_to_we16(ETH_P_PAE),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WX_HDW_TWANS),
				 &weq, sizeof(weq), fawse);
}

int mt7915_mcu_set_mac(stwuct mt7915_dev *dev, int band,
		       boow enabwe, boow hdw_twans)
{
	stwuct {
		u8 opewation;
		u8 enabwe;
		u8 check_bssid;
		u8 insewt_vwan;
		u8 wemove_vwan;
		u8 tid;
		u8 mode;
		u8 wsv;
	} __packed weq_twans = {
		.enabwe = hdw_twans,
	};
	stwuct {
		u8 enabwe;
		u8 band;
		u8 wsv[2];
	} __packed weq_mac = {
		.enabwe = enabwe,
		.band = band,
	};
	int wet;

	wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WX_HDW_TWANS),
				&weq_twans, sizeof(weq_twans), fawse);
	if (wet)
		wetuwn wet;

	if (hdw_twans)
		mt7915_mcu_set_wx_hdw_twans_bwackwist(dev, band);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(MAC_INIT_CTWW),
				 &weq_mac, sizeof(weq_mac), twue);
}

int mt7915_mcu_update_edca(stwuct mt7915_dev *dev, void *pawam)
{
	stwuct mt7915_mcu_tx *weq = (stwuct mt7915_mcu_tx *)pawam;
	u8 num = weq->totaw;
	size_t wen = sizeof(*weq) -
		     (IEEE80211_NUM_ACS - num) * sizeof(stwuct edca);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(EDCA_UPDATE), weq,
				 wen, twue);
}

int mt7915_mcu_set_tx(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif)
{
#define TX_CMD_MODE		1
	stwuct mt7915_mcu_tx weq = {
		.vawid = twue,
		.mode = TX_CMD_MODE,
		.totaw = IEEE80211_NUM_ACS,
	};
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	int ac;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		stwuct ieee80211_tx_queue_pawams *q = &mvif->queue_pawams[ac];
		stwuct edca *e = &weq.edca[ac];

		e->set = WMM_PAWAM_SET;
		e->queue = ac + mvif->mt76.wmm_idx * MT76_CONNAC_MAX_WMM_SETS;
		e->aifs = q->aifs;
		e->txop = cpu_to_we16(q->txop);

		if (q->cw_min)
			e->cw_min = fws(q->cw_min);
		ewse
			e->cw_min = 5;

		if (q->cw_max)
			e->cw_max = cpu_to_we16(fws(q->cw_max));
		ewse
			e->cw_max = cpu_to_we16(10);
	}

	wetuwn mt7915_mcu_update_edca(dev, &weq);
}

int mt7915_mcu_set_fcc5_wpn(stwuct mt7915_dev *dev, int vaw)
{
	stwuct {
		__we32 tag;
		__we16 min_wpn;
		u8 wsv[2];
	} __packed weq = {
		.tag = cpu_to_we32(0x1),
		.min_wpn = cpu_to_we16(vaw),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_WDD_TH), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_set_puwse_th(stwuct mt7915_dev *dev,
			    const stwuct mt7915_dfs_puwse *puwse)
{
	stwuct {
		__we32 tag;

		__we32 max_width;		/* us */
		__we32 max_pww;			/* dbm */
		__we32 min_pww;			/* dbm */
		__we32 min_stgw_pwi;		/* us */
		__we32 max_stgw_pwi;		/* us */
		__we32 min_cw_pwi;		/* us */
		__we32 max_cw_pwi;		/* us */
	} __packed weq = {
		.tag = cpu_to_we32(0x3),

#define __weq_fiewd(fiewd) .fiewd = cpu_to_we32(puwse->fiewd)
		__weq_fiewd(max_width),
		__weq_fiewd(max_pww),
		__weq_fiewd(min_pww),
		__weq_fiewd(min_stgw_pwi),
		__weq_fiewd(max_stgw_pwi),
		__weq_fiewd(min_cw_pwi),
		__weq_fiewd(max_cw_pwi),
#undef __weq_fiewd
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_WDD_TH), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_set_wadaw_th(stwuct mt7915_dev *dev, int index,
			    const stwuct mt7915_dfs_pattewn *pattewn)
{
	stwuct {
		__we32 tag;
		__we16 wadaw_type;

		u8 enb;
		u8 stgw;
		u8 min_cwpn;
		u8 max_cwpn;
		u8 min_cwpw;
		u8 min_pw;
		__we32 min_pwi;
		__we32 max_pwi;
		u8 max_pw;
		u8 min_cwbn;
		u8 max_cwbn;
		u8 min_stgpn;
		u8 max_stgpn;
		u8 min_stgpw;
		u8 wsv[2];
		__we32 min_stgpw_diff;
	} __packed weq = {
		.tag = cpu_to_we32(0x2),
		.wadaw_type = cpu_to_we16(index),

#define __weq_fiewd_u8(fiewd) .fiewd = pattewn->fiewd
#define __weq_fiewd_u32(fiewd) .fiewd = cpu_to_we32(pattewn->fiewd)
		__weq_fiewd_u8(enb),
		__weq_fiewd_u8(stgw),
		__weq_fiewd_u8(min_cwpn),
		__weq_fiewd_u8(max_cwpn),
		__weq_fiewd_u8(min_cwpw),
		__weq_fiewd_u8(min_pw),
		__weq_fiewd_u32(min_pwi),
		__weq_fiewd_u32(max_pwi),
		__weq_fiewd_u8(max_pw),
		__weq_fiewd_u8(min_cwbn),
		__weq_fiewd_u8(max_cwbn),
		__weq_fiewd_u8(min_stgpn),
		__weq_fiewd_u8(max_stgpn),
		__weq_fiewd_u8(min_stgpw),
		__weq_fiewd_u32(min_stgpw_diff),
#undef __weq_fiewd_u8
#undef __weq_fiewd_u32
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_WDD_TH), &weq,
				 sizeof(weq), twue);
}

static int
mt7915_mcu_backgwound_chain_ctww(stwuct mt7915_phy *phy,
				 stwuct cfg80211_chan_def *chandef,
				 int cmd)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct ieee80211_channew *chan = mphy->chandef.chan;
	int fweq = mphy->chandef.centew_fweq1;
	stwuct mt7915_mcu_backgwound_chain_ctww weq = {
		.monitow_scan_type = 2, /* simpwe wx */
	};

	if (!chandef && cmd != CH_SWITCH_BACKGWOUND_SCAN_STOP)
		wetuwn -EINVAW;

	if (!cfg80211_chandef_vawid(&mphy->chandef))
		wetuwn -EINVAW;

	switch (cmd) {
	case CH_SWITCH_BACKGWOUND_SCAN_STAWT: {
		weq.chan = chan->hw_vawue;
		weq.centwaw_chan = ieee80211_fwequency_to_channew(fweq);
		weq.bw = mt76_connac_chan_bw(&mphy->chandef);
		weq.monitow_chan = chandef->chan->hw_vawue;
		weq.monitow_centwaw_chan =
			ieee80211_fwequency_to_channew(chandef->centew_fweq1);
		weq.monitow_bw = mt76_connac_chan_bw(chandef);
		weq.band_idx = phy->mt76->band_idx;
		weq.scan_mode = 1;
		bweak;
	}
	case CH_SWITCH_BACKGWOUND_SCAN_WUNNING:
		weq.monitow_chan = chandef->chan->hw_vawue;
		weq.monitow_centwaw_chan =
			ieee80211_fwequency_to_channew(chandef->centew_fweq1);
		weq.band_idx = phy->mt76->band_idx;
		weq.scan_mode = 2;
		bweak;
	case CH_SWITCH_BACKGWOUND_SCAN_STOP:
		weq.chan = chan->hw_vawue;
		weq.centwaw_chan = ieee80211_fwequency_to_channew(fweq);
		weq.bw = mt76_connac_chan_bw(&mphy->chandef);
		weq.tx_stweam = hweight8(mphy->antenna_mask);
		weq.wx_stweam = mphy->antenna_mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	weq.band = chandef ? chandef->chan->band == NW80211_BAND_5GHZ : 1;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(OFFCH_SCAN_CTWW),
				 &weq, sizeof(weq), fawse);
}

int mt7915_mcu_wdd_backgwound_enabwe(stwuct mt7915_phy *phy,
				     stwuct cfg80211_chan_def *chandef)
{
	stwuct mt7915_dev *dev = phy->dev;
	int eww, wegion;

	if (!chandef) { /* disabwe offchain */
		eww = mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_STOP, MT_WX_SEW2,
					      0, 0);
		if (eww)
			wetuwn eww;

		wetuwn mt7915_mcu_backgwound_chain_ctww(phy, NUWW,
				CH_SWITCH_BACKGWOUND_SCAN_STOP);
	}

	eww = mt7915_mcu_backgwound_chain_ctww(phy, chandef,
					       CH_SWITCH_BACKGWOUND_SCAN_STAWT);
	if (eww)
		wetuwn eww;

	switch (dev->mt76.wegion) {
	case NW80211_DFS_ETSI:
		wegion = 0;
		bweak;
	case NW80211_DFS_JP:
		wegion = 2;
		bweak;
	case NW80211_DFS_FCC:
	defauwt:
		wegion = 1;
		bweak;
	}

	wetuwn mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_STAWT, MT_WX_SEW2,
				       0, wegion);
}

int mt7915_mcu_set_chan_info(stwuct mt7915_phy *phy, int cmd)
{
	static const u8 ch_band[] = {
		[NW80211_BAND_2GHZ] = 0,
		[NW80211_BAND_5GHZ] = 1,
		[NW80211_BAND_6GHZ] = 2,
	};
	stwuct mt7915_dev *dev = phy->dev;
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	int fweq1 = chandef->centew_fweq1;
	u8 band = phy->mt76->band_idx;
	stwuct {
		u8 contwow_ch;
		u8 centew_ch;
		u8 bw;
		u8 tx_path_num;
		u8 wx_path;	/* mask ow num */
		u8 switch_weason;
		u8 band_idx;
		u8 centew_ch2;	/* fow 80+80 onwy */
		__we16 cac_case;
		u8 channew_band;
		u8 wsv0;
		__we32 outband_fweq;
		u8 txpowew_dwop;
		u8 ap_bw;
		u8 ap_centew_ch;
		u8 wsv1[57];
	} __packed weq = {
		.contwow_ch = chandef->chan->hw_vawue,
		.centew_ch = ieee80211_fwequency_to_channew(fweq1),
		.bw = mt76_connac_chan_bw(chandef),
		.tx_path_num = hweight16(phy->mt76->chainmask),
		.wx_path = phy->mt76->chainmask >> (dev->chainshift * band),
		.band_idx = band,
		.channew_band = ch_band[chandef->chan->band],
	};

#ifdef CONFIG_NW80211_TESTMODE
	if (phy->mt76->test.tx_antenna_mask &&
	    mt76_testmode_enabwed(phy->mt76)) {
		weq.tx_path_num = fws(phy->mt76->test.tx_antenna_mask);
		weq.wx_path = phy->mt76->test.tx_antenna_mask;
	}
#endif

	if (mt76_connac_spe_idx(phy->mt76->antenna_mask))
		weq.tx_path_num = fws(phy->mt76->antenna_mask);

	if (phy->mt76->hw->conf.fwags & IEEE80211_CONF_MONITOW)
		weq.switch_weason = CH_SWITCH_NOWMAW;
	ewse if (phy->mt76->hw->conf.fwags & IEEE80211_CONF_OFFCHANNEW ||
		 phy->mt76->hw->conf.fwags & IEEE80211_CONF_IDWE)
		weq.switch_weason = CH_SWITCH_SCAN_BYPASS_DPD;
	ewse if (!cfg80211_weg_can_beacon(phy->mt76->hw->wiphy, chandef,
					  NW80211_IFTYPE_AP))
		weq.switch_weason = CH_SWITCH_DFS;
	ewse
		weq.switch_weason = CH_SWITCH_NOWMAW;

	if (cmd == MCU_EXT_CMD(CHANNEW_SWITCH))
		weq.wx_path = hweight8(weq.wx_path);

	if (chandef->width == NW80211_CHAN_WIDTH_80P80) {
		int fweq2 = chandef->centew_fweq2;

		weq.centew_ch2 = ieee80211_fwequency_to_channew(fweq2);
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76, cmd, &weq, sizeof(weq), twue);
}

static int mt7915_mcu_set_eepwom_fwash(stwuct mt7915_dev *dev)
{
#define MAX_PAGE_IDX_MASK	GENMASK(7, 5)
#define PAGE_IDX_MASK		GENMASK(4, 2)
#define PEW_PAGE_SIZE		0x400
	stwuct mt7915_mcu_eepwom weq = { .buffew_mode = EE_MODE_BUFFEW };
	u16 eepwom_size = mt7915_eepwom_size(dev);
	u8 totaw = DIV_WOUND_UP(eepwom_size, PEW_PAGE_SIZE);
	u8 *eep = (u8 *)dev->mt76.eepwom.data;
	int eep_wen;
	int i;

	fow (i = 0; i < totaw; i++, eep += eep_wen) {
		stwuct sk_buff *skb;
		int wet;

		if (i == totaw - 1 && !!(eepwom_size % PEW_PAGE_SIZE))
			eep_wen = eepwom_size % PEW_PAGE_SIZE;
		ewse
			eep_wen = PEW_PAGE_SIZE;

		skb = mt76_mcu_msg_awwoc(&dev->mt76, NUWW,
					 sizeof(weq) + eep_wen);
		if (!skb)
			wetuwn -ENOMEM;

		weq.fowmat = FIEWD_PWEP(MAX_PAGE_IDX_MASK, totaw - 1) |
			     FIEWD_PWEP(PAGE_IDX_MASK, i) | EE_FOWMAT_WHOWE;
		weq.wen = cpu_to_we16(eep_wen);

		skb_put_data(skb, &weq, sizeof(weq));
		skb_put_data(skb, eep, eep_wen);

		wet = mt76_mcu_skb_send_msg(&dev->mt76, skb,
					    MCU_EXT_CMD(EFUSE_BUFFEW_MODE), twue);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int mt7915_mcu_set_eepwom(stwuct mt7915_dev *dev)
{
	stwuct mt7915_mcu_eepwom weq = {
		.buffew_mode = EE_MODE_EFUSE,
		.fowmat = EE_FOWMAT_WHOWE,
	};

	if (dev->fwash_mode)
		wetuwn mt7915_mcu_set_eepwom_fwash(dev);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(EFUSE_BUFFEW_MODE),
				 &weq, sizeof(weq), twue);
}

int mt7915_mcu_get_eepwom(stwuct mt7915_dev *dev, u32 offset)
{
	stwuct mt7915_mcu_eepwom_info weq = {
		.addw = cpu_to_we32(wound_down(offset,
				    MT7915_EEPWOM_BWOCK_SIZE)),
	};
	stwuct mt7915_mcu_eepwom_info *wes;
	stwuct sk_buff *skb;
	int wet;
	u8 *buf;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76,
					MCU_EXT_QUEWY(EFUSE_ACCESS),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	wes = (stwuct mt7915_mcu_eepwom_info *)skb->data;
	buf = dev->mt76.eepwom.data + we32_to_cpu(wes->addw);
	memcpy(buf, wes->data, MT7915_EEPWOM_BWOCK_SIZE);
	dev_kfwee_skb(skb);

	wetuwn 0;
}

int mt7915_mcu_get_eepwom_fwee_bwock(stwuct mt7915_dev *dev, u8 *bwock_num)
{
	stwuct {
		u8 _wsv;
		u8 vewsion;
		u8 die_idx;
		u8 _wsv2;
	} __packed weq = {
		.vewsion = 1,
	};
	stwuct sk_buff *skb;
	int wet;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76,
					MCU_EXT_QUEWY(EFUSE_FWEE_BWOCK),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	*bwock_num = *(u8 *)skb->data;
	dev_kfwee_skb(skb);

	wetuwn 0;
}

static int mt7915_mcu_set_pwe_caw(stwuct mt7915_dev *dev, u8 idx,
				  u8 *data, u32 wen, int cmd)
{
	stwuct {
		u8 diw;
		u8 vawid;
		__we16 bitmap;
		s8 pwecaw;
		u8 action;
		u8 band;
		u8 idx;
		u8 wsv[4];
		__we32 wen;
	} weq = {};
	stwuct sk_buff *skb;

	skb = mt76_mcu_msg_awwoc(&dev->mt76, NUWW, sizeof(weq) + wen);
	if (!skb)
		wetuwn -ENOMEM;

	weq.idx = idx;
	weq.wen = cpu_to_we32(wen);
	skb_put_data(skb, &weq, sizeof(weq));
	skb_put_data(skb, data, wen);

	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb, cmd, fawse);
}

int mt7915_mcu_appwy_gwoup_caw(stwuct mt7915_dev *dev)
{
	u8 idx = 0, *caw = dev->caw, *eep = dev->mt76.eepwom.data;
	u32 totaw = MT_EE_CAW_GWOUP_SIZE;

	if (!(eep[MT_EE_DO_PWE_CAW] & MT_EE_WIFI_CAW_GWOUP))
		wetuwn 0;

	/*
	 * Items: Wx DCOC, WSSI DCOC, Tx TSSI DCOC, Tx WPFG
	 * Tx FDIQ, Tx DCIQ, Wx FDIQ, Wx FIIQ, ADCDCOC
	 */
	whiwe (totaw > 0) {
		int wet, wen;

		wen = min_t(u32, totaw, MT_EE_CAW_UNIT);

		wet = mt7915_mcu_set_pwe_caw(dev, idx, caw, wen,
					     MCU_EXT_CMD(GWOUP_PWE_CAW_INFO));
		if (wet)
			wetuwn wet;

		totaw -= wen;
		caw += wen;
		idx++;
	}

	wetuwn 0;
}

static int mt7915_find_fweq_idx(const u16 *fweqs, int n_fweqs, u16 cuw)
{
	int i;

	fow (i = 0; i < n_fweqs; i++)
		if (cuw == fweqs[i])
			wetuwn i;

	wetuwn -1;
}

static int mt7915_dpd_fweq_idx(u16 fweq, u8 bw)
{
	static const u16 fweq_wist[] = {
		5180, 5200, 5220, 5240,
		5260, 5280, 5300, 5320,
		5500, 5520, 5540, 5560,
		5580, 5600, 5620, 5640,
		5660, 5680, 5700, 5745,
		5765, 5785, 5805, 5825
	};
	int offset_2g = AWWAY_SIZE(fweq_wist);
	int idx;

	if (fweq < 4000) {
		if (fweq < 2432)
			wetuwn offset_2g;
		if (fweq < 2457)
			wetuwn offset_2g + 1;

		wetuwn offset_2g + 2;
	}

	if (bw == NW80211_CHAN_WIDTH_80P80 || bw == NW80211_CHAN_WIDTH_160)
		wetuwn -1;

	if (bw != NW80211_CHAN_WIDTH_20) {
		idx = mt7915_find_fweq_idx(fweq_wist, AWWAY_SIZE(fweq_wist),
					   fweq + 10);
		if (idx >= 0)
			wetuwn idx;

		idx = mt7915_find_fweq_idx(fweq_wist, AWWAY_SIZE(fweq_wist),
					   fweq - 10);
		if (idx >= 0)
			wetuwn idx;
	}

	wetuwn mt7915_find_fweq_idx(fweq_wist, AWWAY_SIZE(fweq_wist), fweq);
}

int mt7915_mcu_appwy_tx_dpd(stwuct mt7915_phy *phy)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	u16 totaw = 2, centew_fweq = chandef->centew_fweq1;
	u8 *caw = dev->caw, *eep = dev->mt76.eepwom.data;
	int idx;

	if (!(eep[MT_EE_DO_PWE_CAW] & MT_EE_WIFI_CAW_DPD))
		wetuwn 0;

	idx = mt7915_dpd_fweq_idx(centew_fweq, chandef->width);
	if (idx < 0)
		wetuwn -EINVAW;

	/* Items: Tx DPD, Tx Fwatness */
	idx = idx * 2;
	caw += MT_EE_CAW_GWOUP_SIZE;

	whiwe (totaw--) {
		int wet;

		caw += (idx * MT_EE_CAW_UNIT);
		wet = mt7915_mcu_set_pwe_caw(dev, idx, caw, MT_EE_CAW_UNIT,
					     MCU_EXT_CMD(DPD_PWE_CAW_INFO));
		if (wet)
			wetuwn wet;

		idx++;
	}

	wetuwn 0;
}

int mt7915_mcu_get_chan_mib_info(stwuct mt7915_phy *phy, boow chan_switch)
{
	stwuct mt76_channew_state *state = phy->mt76->chan_state;
	stwuct mt76_channew_state *state_ts = &phy->state_ts;
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_mcu_mib *wes, weq[5];
	stwuct sk_buff *skb;
	static const u32 *offs;
	int i, wet, wen, offs_cc;
	u64 cc_tx;

	/* stwict owdew */
	if (is_mt7915(&dev->mt76)) {
		static const u32 chip_offs[] = {
			MIB_NON_WIFI_TIME,
			MIB_TX_TIME,
			MIB_WX_TIME,
			MIB_OBSS_AIWTIME,
			MIB_TXOP_INIT_COUNT,
		};
		wen = AWWAY_SIZE(chip_offs);
		offs = chip_offs;
		offs_cc = 20;
	} ewse {
		static const u32 chip_offs[] = {
			MIB_NON_WIFI_TIME_V2,
			MIB_TX_TIME_V2,
			MIB_WX_TIME_V2,
			MIB_OBSS_AIWTIME_V2
		};
		wen = AWWAY_SIZE(chip_offs);
		offs = chip_offs;
		offs_cc = 0;
	}

	fow (i = 0; i < wen; i++) {
		weq[i].band = cpu_to_we32(phy->mt76->band_idx);
		weq[i].offs = cpu_to_we32(offs[i]);
	}

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_CMD(GET_MIB_INFO),
					weq, wen * sizeof(weq[0]), twue, &skb);
	if (wet)
		wetuwn wet;

	wes = (stwuct mt7915_mcu_mib *)(skb->data + offs_cc);

#define __wes_u64(s) we64_to_cpu(wes[s].data)
	/* subtwact Tx backoff time fwom Tx duwation */
	cc_tx = is_mt7915(&dev->mt76) ? __wes_u64(1) - __wes_u64(4) : __wes_u64(1);

	if (chan_switch)
		goto out;

	state->cc_tx += cc_tx - state_ts->cc_tx;
	state->cc_bss_wx += __wes_u64(2) - state_ts->cc_bss_wx;
	state->cc_wx += __wes_u64(2) + __wes_u64(3) - state_ts->cc_wx;
	state->cc_busy += __wes_u64(0) + cc_tx + __wes_u64(2) + __wes_u64(3) -
			  state_ts->cc_busy;

out:
	state_ts->cc_tx = cc_tx;
	state_ts->cc_bss_wx = __wes_u64(2);
	state_ts->cc_wx = __wes_u64(2) + __wes_u64(3);
	state_ts->cc_busy = __wes_u64(0) + cc_tx + __wes_u64(2) + __wes_u64(3);
#undef __wes_u64

	dev_kfwee_skb(skb);

	wetuwn 0;
}

int mt7915_mcu_get_tempewatuwe(stwuct mt7915_phy *phy)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct {
		u8 ctww_id;
		u8 action;
		u8 band_idx;
		u8 wsv[5];
	} weq = {
		.ctww_id = THEWMAW_SENSOW_TEMP_QUEWY,
		.band_idx = phy->mt76->band_idx,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(THEWMAW_CTWW), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_set_thewmaw_thwottwing(stwuct mt7915_phy *phy, u8 state)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_mcu_thewmaw_ctww weq = {
		.band_idx = phy->mt76->band_idx,
		.ctww_id = THEWMAW_PWOTECT_DUTY_CONFIG,
	};
	int wevew, wet;

	/* set duty cycwe and wevew */
	fow (wevew = 0; wevew < 4; wevew++) {
		weq.duty.duty_wevew = wevew;
		weq.duty.duty_cycwe = state;
		state /= 2;

		wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(THEWMAW_PWOT),
					&weq, sizeof(weq), fawse);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

int mt7915_mcu_set_thewmaw_pwotect(stwuct mt7915_phy *phy)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct {
		stwuct mt7915_mcu_thewmaw_ctww ctww;

		__we32 twiggew_temp;
		__we32 westowe_temp;
		__we16 sustain_time;
		u8 wsv[2];
	} __packed weq = {
		.ctww = {
			.band_idx = phy->mt76->band_idx,
			.type.pwotect_type = 1,
			.type.twiggew_type = 1,
		},
	};
	int wet;

	weq.ctww.ctww_id = THEWMAW_PWOTECT_DISABWE;
	wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(THEWMAW_PWOT),
				&weq, sizeof(weq.ctww), fawse);

	if (wet)
		wetuwn wet;

	/* set high-tempewatuwe twiggew thweshowd */
	weq.ctww.ctww_id = THEWMAW_PWOTECT_ENABWE;
	/* add a safety mawgin ~10 */
	weq.westowe_temp = cpu_to_we32(phy->thwottwe_temp[0] - 10);
	weq.twiggew_temp = cpu_to_we32(phy->thwottwe_temp[1]);
	weq.sustain_time = cpu_to_we16(10);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(THEWMAW_PWOT),
				 &weq, sizeof(weq), fawse);
}

int mt7915_mcu_set_txpowew_fwame_min(stwuct mt7915_phy *phy, s8 txpowew)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct {
		u8 fowmat_id;
		u8 wsv;
		u8 band_idx;
		s8 txpowew_min;
	} __packed weq = {
		.fowmat_id = TX_POWEW_WIMIT_FWAME_MIN,
		.band_idx = phy->mt76->band_idx,
		.txpowew_min = txpowew * 2, /* 0.5db */
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWEW_FEATUWE_CTWW), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_set_txpowew_fwame(stwuct mt7915_phy *phy,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta, s8 txpowew)
{
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct {
		u8 fowmat_id;
		u8 wsv[3];
		u8 band_idx;
		s8 txpowew_max;
		__we16 wcid;
		s8 txpowew_offs[48];
	} __packed weq = {
		.fowmat_id = TX_POWEW_WIMIT_FWAME,
		.band_idx = phy->mt76->band_idx,
		.txpowew_max = DIV_WOUND_UP(mphy->txpowew_cuw, 2),
		.wcid = cpu_to_we16(msta->wcid.idx),
	};
	int wet;
	s8 txpowew_sku[MT7915_SKU_WATE_NUM];

	wet = mt7915_mcu_get_txpowew_sku(phy, txpowew_sku, sizeof(txpowew_sku));
	if (wet)
		wetuwn wet;

	txpowew = mt7915_get_powew_bound(phy, txpowew);
	if (txpowew > mphy->txpowew_cuw || txpowew < 0)
		wetuwn -EINVAW;

	if (txpowew) {
		u32 offs, wen, i;

		if (sta->defwink.ht_cap.ht_suppowted) {
			const u8 *sku_wen = mt7915_sku_gwoup_wen;

			offs = sku_wen[SKU_CCK] + sku_wen[SKU_OFDM];
			wen = sku_wen[SKU_HT_BW20] + sku_wen[SKU_HT_BW40];

			if (sta->defwink.vht_cap.vht_suppowted) {
				offs += wen;
				wen = sku_wen[SKU_VHT_BW20] * 4;

				if (sta->defwink.he_cap.has_he) {
					offs += wen + sku_wen[SKU_HE_WU26] * 3;
					wen = sku_wen[SKU_HE_WU242] * 4;
				}
			}
		} ewse {
			wetuwn -EINVAW;
		}

		fow (i = 0; i < wen; i++, offs++)
			weq.txpowew_offs[i] =
				DIV_WOUND_UP(txpowew - txpowew_sku[offs], 2);
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWEW_FEATUWE_CTWW), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_set_txpowew_sku(stwuct mt7915_phy *phy)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct ieee80211_hw *hw = mphy->hw;
	stwuct mt7915_mcu_txpowew_sku weq = {
		.fowmat_id = TX_POWEW_WIMIT_TABWE,
		.band_idx = phy->mt76->band_idx,
	};
	stwuct mt76_powew_wimits wimits_awway;
	s8 *wa = (s8 *)&wimits_awway;
	int i, idx;
	int tx_powew;

	tx_powew = mt7915_get_powew_bound(phy, hw->conf.powew_wevew);
	tx_powew = mt76_get_wate_powew_wimits(mphy, mphy->chandef.chan,
					      &wimits_awway, tx_powew);
	mphy->txpowew_cuw = tx_powew;

	fow (i = 0, idx = 0; i < AWWAY_SIZE(mt7915_sku_gwoup_wen); i++) {
		u8 mcs_num, wen = mt7915_sku_gwoup_wen[i];
		int j;

		if (i >= SKU_HT_BW20 && i <= SKU_VHT_BW160) {
			mcs_num = 10;

			if (i == SKU_HT_BW20 || i == SKU_VHT_BW20)
				wa = (s8 *)&wimits_awway + 12;
		} ewse {
			mcs_num = wen;
		}

		fow (j = 0; j < min_t(u8, mcs_num, wen); j++)
			weq.txpowew_sku[idx + j] = wa[j];

		wa += mcs_num;
		idx += wen;
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWEW_FEATUWE_CTWW), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_get_txpowew_sku(stwuct mt7915_phy *phy, s8 *txpowew, int wen)
{
#define WATE_POWEW_INFO	2
	stwuct mt7915_dev *dev = phy->dev;
	stwuct {
		u8 fowmat_id;
		u8 categowy;
		u8 band_idx;
		u8 _wsv;
	} __packed weq = {
		.fowmat_id = TX_POWEW_WIMIT_INFO,
		.categowy = WATE_POWEW_INFO,
		.band_idx = phy->mt76->band_idx,
	};
	s8 txpowew_sku[MT7915_SKU_WATE_NUM][2];
	stwuct sk_buff *skb;
	int wet, i;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76,
					MCU_EXT_CMD(TX_POWEW_FEATUWE_CTWW),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	memcpy(txpowew_sku, skb->data + 4, sizeof(txpowew_sku));
	fow (i = 0; i < wen; i++)
		txpowew[i] = txpowew_sku[i][weq.band_idx];

	dev_kfwee_skb(skb);

	wetuwn 0;
}

int mt7915_mcu_set_test_pawam(stwuct mt7915_dev *dev, u8 pawam, boow test_mode,
			      u8 en)
{
	stwuct {
		u8 test_mode_en;
		u8 pawam_idx;
		u8 _wsv[2];

		u8 enabwe;
		u8 _wsv2[3];

		u8 pad[8];
	} __packed weq = {
		.test_mode_en = test_mode,
		.pawam_idx = pawam,
		.enabwe = en,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTWW), &weq,
				 sizeof(weq), fawse);
}

int mt7915_mcu_set_sku_en(stwuct mt7915_phy *phy, boow enabwe)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_sku {
		u8 fowmat_id;
		u8 sku_enabwe;
		u8 band_idx;
		u8 wsv;
	} __packed weq = {
		.fowmat_id = TX_POWEW_WIMIT_ENABWE,
		.band_idx = phy->mt76->band_idx,
		.sku_enabwe = enabwe,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWEW_FEATUWE_CTWW), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_set_sew(stwuct mt7915_dev *dev, u8 action, u8 set, u8 band)
{
	stwuct {
		u8 action;
		u8 set;
		u8 band;
		u8 wsv;
	} weq = {
		.action = action,
		.set = set,
		.band = band,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_SEW_TWIGGEW),
				 &weq, sizeof(weq), fawse);
}

int mt7915_mcu_set_txbf(stwuct mt7915_dev *dev, u8 action)
{
	stwuct {
		u8 action;
		union {
			stwuct {
				u8 snd_mode;
				u8 sta_num;
				u8 wsv;
				u8 wwan_idx[4];
				__we32 snd_pewiod;	/* ms */
			} __packed snd;
			stwuct {
				boow ebf;
				boow ibf;
				u8 wsv;
			} __packed type;
			stwuct {
				u8 bf_num;
				u8 bf_bitmap;
				u8 bf_sew[8];
				u8 wsv[5];
			} __packed mod;
		};
	} __packed weq = {
		.action = action,
	};

#define MT_BF_PWOCESSING	4
	switch (action) {
	case MT_BF_SOUNDING_ON:
		weq.snd.snd_mode = MT_BF_PWOCESSING;
		bweak;
	case MT_BF_TYPE_UPDATE:
		weq.type.ebf = twue;
		weq.type.ibf = dev->ibf;
		bweak;
	case MT_BF_MODUWE_UPDATE:
		weq.mod.bf_num = 2;
		weq.mod.bf_bitmap = GENMASK(1, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(TXBF_ACTION), &weq,
				 sizeof(weq), twue);
}

static int
mt7915_mcu_enabwe_obss_spw(stwuct mt7915_phy *phy, u8 action, u8 vaw)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_mcu_sw_ctww weq = {
		.action = action,
		.awgnum = 1,
		.band_idx = phy->mt76->band_idx,
		.vaw = cpu_to_we32(vaw),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_SPW), &weq,
				 sizeof(weq), twue);
}

static int
mt7915_mcu_set_obss_spw_pd(stwuct mt7915_phy *phy,
			   stwuct ieee80211_he_obss_pd *he_obss_pd)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct {
		stwuct mt7915_mcu_sw_ctww ctww;
		stwuct {
			u8 pd_th_non_swg;
			u8 pd_th_swg;
			u8 pewiod_offs;
			u8 wcpi_swc;
			__we16 obss_pd_min;
			__we16 obss_pd_min_swg;
			u8 wesp_txpww_mode;
			u8 txpww_westwict_mode;
			u8 txpww_wef;
			u8 wsv[3];
		} __packed pawam;
	} __packed weq = {
		.ctww = {
			.action = SPW_SET_PAWAM,
			.awgnum = 9,
			.band_idx = phy->mt76->band_idx,
		},
	};
	int wet;
	u8 max_th = 82, non_swg_max_th = 62;

	/* disabwe fiwmwawe dynamicaw PD asjustment */
	wet = mt7915_mcu_enabwe_obss_spw(phy, SPW_ENABWE_DPD, fawse);
	if (wet)
		wetuwn wet;

	if (he_obss_pd->sw_ctww &
	    IEEE80211_HE_SPW_NON_SWG_OBSS_PD_SW_DISAWWOWED)
		weq.pawam.pd_th_non_swg = max_th;
	ewse if (he_obss_pd->sw_ctww & IEEE80211_HE_SPW_NON_SWG_OFFSET_PWESENT)
		weq.pawam.pd_th_non_swg  = max_th - he_obss_pd->non_swg_max_offset;
	ewse
		weq.pawam.pd_th_non_swg  = non_swg_max_th;

	if (he_obss_pd->sw_ctww & IEEE80211_HE_SPW_SWG_INFOWMATION_PWESENT)
		weq.pawam.pd_th_swg = max_th - he_obss_pd->max_offset;

	weq.pawam.obss_pd_min = cpu_to_we16(82);
	weq.pawam.obss_pd_min_swg = cpu_to_we16(82);
	weq.pawam.txpww_westwict_mode = 2;
	weq.pawam.txpww_wef = 21;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_SPW), &weq,
				 sizeof(weq), twue);
}

static int
mt7915_mcu_set_obss_spw_siga(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif,
			     stwuct ieee80211_he_obss_pd *he_obss_pd)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_dev *dev = phy->dev;
	u8 omac = mvif->mt76.omac_idx;
	stwuct {
		stwuct mt7915_mcu_sw_ctww ctww;
		stwuct {
			u8 omac;
			u8 wsv[3];
			u8 fwag[20];
		} __packed siga;
	} __packed weq = {
		.ctww = {
			.action = SPW_SET_SIGA,
			.awgnum = 1,
			.band_idx = phy->mt76->band_idx,
		},
		.siga = {
			.omac = omac > HW_BSSID_MAX ? omac - 12 : omac,
		},
	};
	int wet;

	if (he_obss_pd->sw_ctww & IEEE80211_HE_SPW_HESIGA_SW_VAW15_AWWOWED)
		weq.siga.fwag[weq.siga.omac] = 0xf;
	ewse
		wetuwn 0;

	/* switch to nowmaw AP mode */
	wet = mt7915_mcu_enabwe_obss_spw(phy, SPW_ENABWE_MODE, 0);
	if (wet)
		wetuwn wet;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_SPW), &weq,
				 sizeof(weq), twue);
}

static int
mt7915_mcu_set_obss_spw_bitmap(stwuct mt7915_phy *phy,
			       stwuct ieee80211_he_obss_pd *he_obss_pd)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct {
		stwuct mt7915_mcu_sw_ctww ctww;
		stwuct {
			__we32 cowow_w[2];
			__we32 cowow_h[2];
			__we32 bssid_w[2];
			__we32 bssid_h[2];
		} __packed bitmap;
	} __packed weq = {
		.ctww = {
			.action = SPW_SET_SWG_BITMAP,
			.awgnum = 4,
			.band_idx = phy->mt76->band_idx,
		},
	};
	u32 bitmap;

	memcpy(&bitmap, he_obss_pd->bss_cowow_bitmap, sizeof(bitmap));
	weq.bitmap.cowow_w[weq.ctww.band_idx] = cpu_to_we32(bitmap);

	memcpy(&bitmap, he_obss_pd->bss_cowow_bitmap + 4, sizeof(bitmap));
	weq.bitmap.cowow_h[weq.ctww.band_idx] = cpu_to_we32(bitmap);

	memcpy(&bitmap, he_obss_pd->pawtiaw_bssid_bitmap, sizeof(bitmap));
	weq.bitmap.bssid_w[weq.ctww.band_idx] = cpu_to_we32(bitmap);

	memcpy(&bitmap, he_obss_pd->pawtiaw_bssid_bitmap + 4, sizeof(bitmap));
	weq.bitmap.bssid_h[weq.ctww.band_idx] = cpu_to_we32(bitmap);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(SET_SPW), &weq,
				 sizeof(weq), twue);
}

int mt7915_mcu_add_obss_spw(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_he_obss_pd *he_obss_pd)
{
	int wet;

	/* enabwe fiwmwawe scene detection awgowithms */
	wet = mt7915_mcu_enabwe_obss_spw(phy, SPW_ENABWE_SD, sw_scene_detect);
	if (wet)
		wetuwn wet;

	/* fiwmwawe dynamicawwy adjusts PD thweshowd so skip manuaw contwow */
	if (sw_scene_detect && !he_obss_pd->enabwe)
		wetuwn 0;

	/* enabwe spatiaw weuse */
	wet = mt7915_mcu_enabwe_obss_spw(phy, SPW_ENABWE, he_obss_pd->enabwe);
	if (wet)
		wetuwn wet;

	if (sw_scene_detect || !he_obss_pd->enabwe)
		wetuwn 0;

	wet = mt7915_mcu_enabwe_obss_spw(phy, SPW_ENABWE_TX, twue);
	if (wet)
		wetuwn wet;

	/* set SWG/non-SWG OBSS PD thweshowd */
	wet = mt7915_mcu_set_obss_spw_pd(phy, he_obss_pd);
	if (wet)
		wetuwn wet;

	/* Set SW pwohibit */
	wet = mt7915_mcu_set_obss_spw_siga(phy, vif, he_obss_pd);
	if (wet)
		wetuwn wet;

	/* set SWG BSS cowow/BSSID bitmap */
	wetuwn mt7915_mcu_set_obss_spw_bitmap(phy, he_obss_pd);
}

int mt7915_mcu_get_wx_wate(stwuct mt7915_phy *phy, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta, stwuct wate_info *wate)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct mt7915_sta *msta = (stwuct mt7915_sta *)sta->dwv_pwiv;
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct {
		u8 categowy;
		u8 band;
		__we16 wcid;
	} __packed weq = {
		.categowy = MCU_PHY_STATE_CONTENTION_WX_WATE,
		.band = mvif->mt76.band_idx,
		.wcid = cpu_to_we16(msta->wcid.idx),
	};
	stwuct ieee80211_suppowted_band *sband;
	stwuct mt7915_mcu_phy_wx_info *wes;
	stwuct sk_buff *skb;
	int wet;
	boow cck = fawse;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_CMD(PHY_STAT_INFO),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	wes = (stwuct mt7915_mcu_phy_wx_info *)skb->data;

	wate->mcs = wes->wate;
	wate->nss = wes->nsts + 1;

	switch (wes->mode) {
	case MT_PHY_TYPE_CCK:
		cck = twue;
		fawwthwough;
	case MT_PHY_TYPE_OFDM:
		if (mphy->chandef.chan->band == NW80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		ewse if (mphy->chandef.chan->band == NW80211_BAND_6GHZ)
			sband = &mphy->sband_6g.sband;
		ewse
			sband = &mphy->sband_2g.sband;

		wate->mcs = mt76_get_wate(&dev->mt76, sband, wate->mcs, cck);
		wate->wegacy = sband->bitwates[wate->mcs].bitwate;
		bweak;
	case MT_PHY_TYPE_HT:
	case MT_PHY_TYPE_HT_GF:
		if (wate->mcs > 31) {
			wet = -EINVAW;
			goto out;
		}

		wate->fwags = WATE_INFO_FWAGS_MCS;
		if (wes->gi)
			wate->fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case MT_PHY_TYPE_VHT:
		if (wate->mcs > 9) {
			wet = -EINVAW;
			goto out;
		}

		wate->fwags = WATE_INFO_FWAGS_VHT_MCS;
		if (wes->gi)
			wate->fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case MT_PHY_TYPE_HE_SU:
	case MT_PHY_TYPE_HE_EXT_SU:
	case MT_PHY_TYPE_HE_TB:
	case MT_PHY_TYPE_HE_MU:
		if (wes->gi > NW80211_WATE_INFO_HE_GI_3_2 || wate->mcs > 11) {
			wet = -EINVAW;
			goto out;
		}
		wate->he_gi = wes->gi;
		wate->fwags = WATE_INFO_FWAGS_HE_MCS;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	switch (wes->bw) {
	case IEEE80211_STA_WX_BW_160:
		wate->bw = WATE_INFO_BW_160;
		bweak;
	case IEEE80211_STA_WX_BW_80:
		wate->bw = WATE_INFO_BW_80;
		bweak;
	case IEEE80211_STA_WX_BW_40:
		wate->bw = WATE_INFO_BW_40;
		bweak;
	defauwt:
		wate->bw = WATE_INFO_BW_20;
		bweak;
	}

out:
	dev_kfwee_skb(skb);

	wetuwn wet;
}

int mt7915_mcu_update_bss_cowow(stwuct mt7915_dev *dev, stwuct ieee80211_vif *vif,
				stwuct cfg80211_he_bss_cowow *he_bss_cowow)
{
	int wen = sizeof(stwuct sta_weq_hdw) + sizeof(stwuct bss_info_cowow);
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)vif->dwv_pwiv;
	stwuct bss_info_cowow *bss_cowow;
	stwuct sk_buff *skb;
	stwuct twv *twv;

	skb = __mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76,
					      NUWW, wen);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_BSS_COWOW,
				      sizeof(*bss_cowow));
	bss_cowow = (stwuct bss_info_cowow *)twv;
	bss_cowow->disabwe = !he_bss_cowow->enabwed;
	bss_cowow->cowow = he_bss_cowow->cowow;

	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(BSS_INFO_UPDATE), twue);
}

#define TWT_AGWT_TWIGGEW	BIT(0)
#define TWT_AGWT_ANNOUNCE	BIT(1)
#define TWT_AGWT_PWOTECT	BIT(2)

int mt7915_mcu_twt_agwt_update(stwuct mt7915_dev *dev,
			       stwuct mt7915_vif *mvif,
			       stwuct mt7915_twt_fwow *fwow,
			       int cmd)
{
	stwuct {
		u8 tbw_idx;
		u8 cmd;
		u8 own_mac_idx;
		u8 fwowid; /* 0xff fow gwoup id */
		__we16 peew_id; /* specify the peew_id (msb=0)
				 * ow gwoup_id (msb=1)
				 */
		u8 duwation; /* 256 us */
		u8 bss_idx;
		__we64 stawt_tsf;
		__we16 mantissa;
		u8 exponent;
		u8 is_ap;
		u8 agwt_pawams;
		u8 wsv[23];
	} __packed weq = {
		.tbw_idx = fwow->tabwe_id,
		.cmd = cmd,
		.own_mac_idx = mvif->mt76.omac_idx,
		.fwowid = fwow->id,
		.peew_id = cpu_to_we16(fwow->wcid),
		.duwation = fwow->duwation,
		.bss_idx = mvif->mt76.idx,
		.stawt_tsf = cpu_to_we64(fwow->tsf),
		.mantissa = fwow->mantissa,
		.exponent = fwow->exp,
		.is_ap = twue,
	};

	if (fwow->pwotection)
		weq.agwt_pawams |= TWT_AGWT_PWOTECT;
	if (!fwow->fwowtype)
		weq.agwt_pawams |= TWT_AGWT_ANNOUNCE;
	if (fwow->twiggew)
		weq.agwt_pawams |= TWT_AGWT_TWIGGEW;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(TWT_AGWT_UPDATE),
				 &weq, sizeof(weq), twue);
}

int mt7915_mcu_wed_wa_tx_stats(stwuct mt7915_dev *dev, u16 wwan_idx)
{
	stwuct {
		__we32 cmd;
		__we32 num;
		__we32 __wsv;
		__we16 wwan_idx;
	} weq = {
		.cmd = cpu_to_we32(0x15),
		.num = cpu_to_we32(1),
		.wwan_idx = cpu_to_we16(wwan_idx),
	};
	stwuct mt7915_mcu_wa_tx_stat {
		__we16 wwan_idx;
		u8 __wsv[2];

		/* tx_bytes is depwecated since WA byte countew uses u32,
		 * which easiwy weads to ovewfwow.
		 */
		__we32 tx_bytes;
		__we32 tx_packets;
	} *wes;
	stwuct mt76_wcid *wcid;
	stwuct sk_buff *skb;
	int wet;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_WA_PAWAM_CMD(QUEWY),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	if (!is_mt7915(&dev->mt76))
		skb_puww(skb, 4);

	wes = (stwuct mt7915_mcu_wa_tx_stat *)skb->data;

	if (we16_to_cpu(wes->wwan_idx) != wwan_idx) {
		wet = -EINVAW;
		goto out;
	}

	wcu_wead_wock();

	wcid = wcu_dewefewence(dev->mt76.wcid[wwan_idx]);
	if (wcid)
		wcid->stats.tx_packets += we32_to_cpu(wes->tx_packets);
	ewse
		wet = -EINVAW;

	wcu_wead_unwock();
out:
	dev_kfwee_skb(skb);

	wetuwn wet;
}

int mt7915_mcu_wf_wegvaw(stwuct mt7915_dev *dev, u32 wegidx, u32 *vaw, boow set)
{
	stwuct {
		__we32 idx;
		__we32 ofs;
		__we32 data;
	} __packed weq = {
		.idx = cpu_to_we32(u32_get_bits(wegidx, GENMASK(31, 24))),
		.ofs = cpu_to_we32(u32_get_bits(wegidx, GENMASK(23, 0))),
		.data = set ? cpu_to_we32(*vaw) : 0,
	};
	stwuct sk_buff *skb;
	int wet;

	if (set)
		wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WF_WEG_ACCESS),
					 &weq, sizeof(weq), fawse);

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_QUEWY(WF_WEG_ACCESS),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	*vaw = we32_to_cpu(*(__we32 *)(skb->data + 8));
	dev_kfwee_skb(skb);

	wetuwn 0;
}
