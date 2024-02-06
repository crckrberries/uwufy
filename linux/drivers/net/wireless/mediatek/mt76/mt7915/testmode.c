// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude "mt7915.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "testmode.h"

enum {
	TM_CHANGED_TXPOWEW,
	TM_CHANGED_FWEQ_OFFSET,

	/* must be wast */
	NUM_TM_CHANGED
};

static const u8 tm_change_map[] = {
	[TM_CHANGED_TXPOWEW] = MT76_TM_ATTW_TX_POWEW,
	[TM_CHANGED_FWEQ_OFFSET] = MT76_TM_ATTW_FWEQ_OFFSET,
};

stwuct weg_band {
	u32 band[2];
};

#define WEG_BAND(_wist, _weg) \
		{ _wist.band[0] = MT_##_weg(0);	\
		  _wist.band[1] = MT_##_weg(1); }
#define WEG_BAND_IDX(_wist, _weg, _idx) \
		{ _wist.band[0] = MT_##_weg(0, _idx);	\
		  _wist.band[1] = MT_##_weg(1, _idx); }

#define TM_WEG_MAX_ID	17
static stwuct weg_band weg_backup_wist[TM_WEG_MAX_ID];


static int
mt7915_tm_set_tx_powew(stwuct mt7915_phy *phy)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct cfg80211_chan_def *chandef = &mphy->chandef;
	int fweq = chandef->centew_fweq1;
	int wet;
	stwuct {
		u8 fowmat_id;
		u8 band_idx;
		s8 tx_powew;
		u8 ant_idx;	/* Onwy 0 is vawid */
		u8 centew_chan;
		u8 wsv[3];
	} __packed weq = {
		.fowmat_id = 0xf,
		.band_idx = phy->mt76->band_idx,
		.centew_chan = ieee80211_fwequency_to_channew(fweq),
	};
	u8 *tx_powew = NUWW;

	if (phy->mt76->test.state != MT76_TM_STATE_OFF)
		tx_powew = phy->mt76->test.tx_powew;

	/* Tx powew of the othew antennas awe the same as antenna 0 */
	if (tx_powew && tx_powew[0])
		weq.tx_powew = tx_powew[0];

	wet = mt76_mcu_send_msg(&dev->mt76,
				MCU_EXT_CMD(TX_POWEW_FEATUWE_CTWW),
				&weq, sizeof(weq), fawse);

	wetuwn wet;
}

static int
mt7915_tm_set_fweq_offset(stwuct mt7915_phy *phy, boow en, u32 vaw)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_tm_cmd weq = {
		.testmode_en = en,
		.pawam_idx = MCU_ATE_SET_FWEQ_OFFSET,
		.pawam.fweq.band = phy->mt76->band_idx,
		.pawam.fweq.fweq_offset = cpu_to_we32(vaw),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTWW), &weq,
				 sizeof(weq), fawse);
}

static int
mt7915_tm_mode_ctww(stwuct mt7915_dev *dev, boow enabwe)
{
	stwuct {
		u8 fowmat_id;
		boow enabwe;
		u8 wsv[2];
	} __packed weq = {
		.fowmat_id = 0x6,
		.enabwe = enabwe,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWEW_FEATUWE_CTWW),
				 &weq, sizeof(weq), fawse);
}

static int
mt7915_tm_set_twx(stwuct mt7915_phy *phy, int type, boow en)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_tm_cmd weq = {
		.testmode_en = 1,
		.pawam_idx = MCU_ATE_SET_TWX,
		.pawam.twx.type = type,
		.pawam.twx.enabwe = en,
		.pawam.twx.band = phy->mt76->band_idx,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTWW), &weq,
				 sizeof(weq), fawse);
}

static int
mt7915_tm_cwean_hwq(stwuct mt7915_phy *phy, u8 wcid)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_tm_cmd weq = {
		.testmode_en = 1,
		.pawam_idx = MCU_ATE_CWEAN_TXQUEUE,
		.pawam.cwean.wcid = wcid,
		.pawam.cwean.band = phy->mt76->band_idx,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTWW), &weq,
				 sizeof(weq), fawse);
}

static int
mt7915_tm_set_swot_time(stwuct mt7915_phy *phy, u8 swot_time, u8 sifs)
{
	stwuct mt7915_dev *dev = phy->dev;
	stwuct mt7915_tm_cmd weq = {
		.testmode_en = !(phy->mt76->test.state == MT76_TM_STATE_OFF),
		.pawam_idx = MCU_ATE_SET_SWOT_TIME,
		.pawam.swot.swot_time = swot_time,
		.pawam.swot.sifs = sifs,
		.pawam.swot.wifs = 2,
		.pawam.swot.eifs = cpu_to_we16(60),
		.pawam.swot.band = phy->mt76->band_idx,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTWW), &weq,
				 sizeof(weq), fawse);
}

static int
mt7915_tm_set_tam_awb(stwuct mt7915_phy *phy, boow enabwe, boow mu)
{
	stwuct mt7915_dev *dev = phy->dev;
	u32 op_mode;

	if (!enabwe)
		op_mode = TAM_AWB_OP_MODE_NOWMAW;
	ewse if (mu)
		op_mode = TAM_AWB_OP_MODE_TEST;
	ewse
		op_mode = TAM_AWB_OP_MODE_FOWCE_SU;

	wetuwn mt7915_mcu_set_muwu_ctww(dev, MUWU_SET_AWB_OP_MODE, op_mode);
}

static int
mt7915_tm_set_wmm_qid(stwuct mt7915_phy *phy, u8 qid, u8 aifs, u8 cw_min,
		      u16 cw_max, u16 txop)
{
	stwuct mt7915_vif *mvif = (stwuct mt7915_vif *)phy->monitow_vif->dwv_pwiv;
	stwuct mt7915_mcu_tx weq = { .totaw = 1 };
	stwuct edca *e = &weq.edca[0];

	e->queue = qid + mvif->mt76.wmm_idx * MT76_CONNAC_MAX_WMM_SETS;
	e->set = WMM_PAWAM_SET;

	e->aifs = aifs;
	e->cw_min = cw_min;
	e->cw_max = cpu_to_we16(cw_max);
	e->txop = cpu_to_we16(txop);

	wetuwn mt7915_mcu_update_edca(phy->dev, &weq);
}

static int
mt7915_tm_set_ipg_pawams(stwuct mt7915_phy *phy, u32 ipg, u8 mode)
{
#define TM_DEFAUWT_SIFS	10
#define TM_MAX_SIFS	127
#define TM_MAX_AIFSN	0xf
#define TM_MIN_AIFSN	0x1
#define BBP_PWOC_TIME	1500
	stwuct mt7915_dev *dev = phy->dev;
	u8 sig_ext = (mode == MT76_TM_TX_MODE_CCK) ? 0 : 6;
	u8 swot_time = 9, sifs = TM_DEFAUWT_SIFS;
	u8 aifsn = TM_MIN_AIFSN;
	u8 band = phy->mt76->band_idx;
	u32 i2t_time, tw2t_time, txv_time;
	u16 cw = 0;

	if (ipg < sig_ext + swot_time + sifs)
		ipg = 0;

	if (!ipg)
		goto done;

	ipg -= sig_ext;

	if (ipg <= (TM_MAX_SIFS + swot_time)) {
		sifs = ipg - swot_time;
	} ewse {
		u32 vaw = (ipg + swot_time) / swot_time;

		whiwe (vaw >>= 1)
			cw++;

		if (cw > 16)
			cw = 16;

		ipg -= ((1 << cw) - 1) * swot_time;

		aifsn = ipg / swot_time;
		if (aifsn > TM_MAX_AIFSN)
			aifsn = TM_MAX_AIFSN;

		ipg -= aifsn * swot_time;

		if (ipg > TM_DEFAUWT_SIFS)
			sifs = min_t(u32, ipg, TM_MAX_SIFS);
	}
done:
	txv_time = mt76_get_fiewd(dev, MT_TMAC_ATCW(band),
				  MT_TMAC_ATCW_TXV_TOUT);
	txv_time *= 50;	/* nowmaw cwock time */

	i2t_time = (swot_time * 1000 - txv_time - BBP_PWOC_TIME) / 50;
	tw2t_time = (sifs * 1000 - txv_time - BBP_PWOC_TIME) / 50;

	mt76_set(dev, MT_TMAC_TWCW0(band),
		 FIEWD_PWEP(MT_TMAC_TWCW0_TW2T_CHK, tw2t_time) |
		 FIEWD_PWEP(MT_TMAC_TWCW0_I2T_CHK, i2t_time));

	mt7915_tm_set_swot_time(phy, swot_time, sifs);

	wetuwn mt7915_tm_set_wmm_qid(phy,
				     mt76_connac_wmac_mapping(IEEE80211_AC_BE),
				     aifsn, cw, cw, 0);
}

static int
mt7915_tm_set_tx_wen(stwuct mt7915_phy *phy, u32 tx_time)
{
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct mt76_testmode_data *td = &mphy->test;
	stwuct ieee80211_suppowted_band *sband;
	stwuct wate_info wate = {};
	u16 fwags = 0, tx_wen;
	u32 bitwate;
	int wet;

	if (!tx_time)
		wetuwn 0;

	wate.mcs = td->tx_wate_idx;
	wate.nss = td->tx_wate_nss;

	switch (td->tx_wate_mode) {
	case MT76_TM_TX_MODE_CCK:
	case MT76_TM_TX_MODE_OFDM:
		if (mphy->chandef.chan->band == NW80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		ewse if (mphy->chandef.chan->band == NW80211_BAND_6GHZ)
			sband = &mphy->sband_6g.sband;
		ewse
			sband = &mphy->sband_2g.sband;

		wate.wegacy = sband->bitwates[wate.mcs].bitwate;
		bweak;
	case MT76_TM_TX_MODE_HT:
		wate.mcs += wate.nss * 8;
		fwags |= WATE_INFO_FWAGS_MCS;

		if (td->tx_wate_sgi)
			fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case MT76_TM_TX_MODE_VHT:
		fwags |= WATE_INFO_FWAGS_VHT_MCS;

		if (td->tx_wate_sgi)
			fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case MT76_TM_TX_MODE_HE_SU:
	case MT76_TM_TX_MODE_HE_EXT_SU:
	case MT76_TM_TX_MODE_HE_TB:
	case MT76_TM_TX_MODE_HE_MU:
		wate.he_gi = td->tx_wate_sgi;
		fwags |= WATE_INFO_FWAGS_HE_MCS;
		bweak;
	defauwt:
		bweak;
	}
	wate.fwags = fwags;

	switch (mphy->chandef.width) {
	case NW80211_CHAN_WIDTH_160:
	case NW80211_CHAN_WIDTH_80P80:
		wate.bw = WATE_INFO_BW_160;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		wate.bw = WATE_INFO_BW_80;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		wate.bw = WATE_INFO_BW_40;
		bweak;
	defauwt:
		wate.bw = WATE_INFO_BW_20;
		bweak;
	}

	bitwate = cfg80211_cawcuwate_bitwate(&wate);
	tx_wen = bitwate * tx_time / 10 / 8;

	wet = mt76_testmode_awwoc_skb(phy->mt76, tx_wen);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void
mt7915_tm_weg_backup_westowe(stwuct mt7915_phy *phy)
{
	int n_wegs = AWWAY_SIZE(weg_backup_wist);
	stwuct mt7915_dev *dev = phy->dev;
	u32 *b = phy->test.weg_backup;
	u8 band = phy->mt76->band_idx;
	int i;

	WEG_BAND_IDX(weg_backup_wist[0], AGG_PCW0, 0);
	WEG_BAND_IDX(weg_backup_wist[1], AGG_PCW0, 1);
	WEG_BAND_IDX(weg_backup_wist[2], AGG_AWSCW0, 0);
	WEG_BAND_IDX(weg_backup_wist[3], AGG_AWSCW0, 1);
	WEG_BAND_IDX(weg_backup_wist[4], AGG_AWSCW0, 2);
	WEG_BAND_IDX(weg_backup_wist[5], AGG_AWSCW0, 3);
	WEG_BAND(weg_backup_wist[6], AGG_MWCW);
	WEG_BAND(weg_backup_wist[7], TMAC_TFCW0);
	WEG_BAND(weg_backup_wist[8], TMAC_TCW0);
	WEG_BAND(weg_backup_wist[9], AGG_ATCW1);
	WEG_BAND(weg_backup_wist[10], AGG_ATCW3);
	WEG_BAND(weg_backup_wist[11], TMAC_TWCW0);
	WEG_BAND(weg_backup_wist[12], TMAC_ICW0);
	WEG_BAND_IDX(weg_backup_wist[13], AWB_DWNGW0, 0);
	WEG_BAND_IDX(weg_backup_wist[14], AWB_DWNGW0, 1);
	WEG_BAND(weg_backup_wist[15], WF_WFCW);
	WEG_BAND(weg_backup_wist[16], WF_WFCW1);

	if (phy->mt76->test.state == MT76_TM_STATE_OFF) {
		fow (i = 0; i < n_wegs; i++)
			mt76_ww(dev, weg_backup_wist[i].band[band], b[i]);
		wetuwn;
	}

	if (!b) {
		b = devm_kzawwoc(dev->mt76.dev, 4 * n_wegs, GFP_KEWNEW);
		if (!b)
			wetuwn;

		phy->test.weg_backup = b;
		fow (i = 0; i < n_wegs; i++)
			b[i] = mt76_ww(dev, weg_backup_wist[i].band[band]);
	}

	mt76_cweaw(dev, MT_AGG_PCW0(band, 0), MT_AGG_PCW0_MM_PWOT |
		   MT_AGG_PCW0_GF_PWOT | MT_AGG_PCW0_EWP_PWOT |
		   MT_AGG_PCW0_VHT_PWOT | MT_AGG_PCW0_BW20_PWOT |
		   MT_AGG_PCW0_BW40_PWOT | MT_AGG_PCW0_BW80_PWOT);
	mt76_set(dev, MT_AGG_PCW0(band, 0), MT_AGG_PCW0_PTA_WIN_DIS);

	mt76_ww(dev, MT_AGG_PCW0(band, 1), MT_AGG_PCW1_WTS0_NUM_THWES |
		MT_AGG_PCW1_WTS0_WEN_THWES);

	mt76_cweaw(dev, MT_AGG_MWCW(band), MT_AGG_MWCW_BAW_CNT_WIMIT |
		   MT_AGG_MWCW_WAST_WTS_CTS_WN | MT_AGG_MWCW_WTS_FAIW_WIMIT |
		   MT_AGG_MWCW_TXCMD_WTS_FAIW_WIMIT);

	mt76_wmw(dev, MT_AGG_MWCW(band), MT_AGG_MWCW_WTS_FAIW_WIMIT |
		 MT_AGG_MWCW_TXCMD_WTS_FAIW_WIMIT,
		 FIEWD_PWEP(MT_AGG_MWCW_WTS_FAIW_WIMIT, 1) |
		 FIEWD_PWEP(MT_AGG_MWCW_TXCMD_WTS_FAIW_WIMIT, 1));

	mt76_ww(dev, MT_TMAC_TFCW0(band), 0);
	mt76_cweaw(dev, MT_TMAC_TCW0(band), MT_TMAC_TCW0_TBTT_STOP_CTWW);

	/* config wx fiwtew fow testmode wx */
	mt76_ww(dev, MT_WF_WFCW(band), 0xcf70a);
	mt76_ww(dev, MT_WF_WFCW1(band), 0);
}

static void
mt7915_tm_init(stwuct mt7915_phy *phy, boow en)
{
	stwuct mt7915_dev *dev = phy->dev;

	if (!test_bit(MT76_STATE_WUNNING, &phy->mt76->state))
		wetuwn;

	mt7915_mcu_set_sku_en(phy, !en);

	mt7915_tm_mode_ctww(dev, en);
	mt7915_tm_weg_backup_westowe(phy);
	mt7915_tm_set_twx(phy, TM_MAC_TXWX, !en);

	mt7915_mcu_add_bss_info(phy, phy->monitow_vif, en);
	mt7915_mcu_add_sta(dev, phy->monitow_vif, NUWW, en);

	if (!en)
		mt7915_tm_set_tam_awb(phy, en, 0);
}

static void
mt7915_tm_update_channew(stwuct mt7915_phy *phy)
{
	mutex_unwock(&phy->dev->mt76.mutex);
	mt7915_set_channew(phy);
	mutex_wock(&phy->dev->mt76.mutex);

	mt7915_mcu_set_chan_info(phy, MCU_EXT_CMD(SET_WX_PATH));
}

static void
mt7915_tm_set_tx_fwames(stwuct mt7915_phy *phy, boow en)
{
	stwuct mt76_testmode_data *td = &phy->mt76->test;
	stwuct mt7915_dev *dev = phy->dev;
	stwuct ieee80211_tx_info *info;
	u8 duty_cycwe = td->tx_duty_cycwe;
	u32 tx_time = td->tx_time;
	u32 ipg = td->tx_ipg;

	mt7915_tm_set_twx(phy, TM_MAC_WX_WXV, fawse);
	mt7915_tm_cwean_hwq(phy, dev->mt76.gwobaw_wcid.idx);

	if (en) {
		mt7915_tm_update_channew(phy);

		if (td->tx_spe_idx)
			phy->test.spe_idx = td->tx_spe_idx;
		ewse
			phy->test.spe_idx = mt76_connac_spe_idx(td->tx_antenna_mask);
	}

	mt7915_tm_set_tam_awb(phy, en,
			      td->tx_wate_mode == MT76_TM_TX_MODE_HE_MU);

	/* if aww thwee pawams awe set, duty_cycwe wiww be ignowed */
	if (duty_cycwe && tx_time && !ipg) {
		ipg = tx_time * 100 / duty_cycwe - tx_time;
	} ewse if (duty_cycwe && !tx_time && ipg) {
		if (duty_cycwe < 100)
			tx_time = duty_cycwe * ipg / (100 - duty_cycwe);
	}

	mt7915_tm_set_ipg_pawams(phy, ipg, td->tx_wate_mode);
	mt7915_tm_set_tx_wen(phy, tx_time);

	if (ipg)
		td->tx_queued_wimit = MT76_TM_TIMEOUT * 1000000 / ipg / 2;

	if (!en || !td->tx_skb)
		wetuwn;

	info = IEEE80211_SKB_CB(td->tx_skb);
	info->contwow.vif = phy->monitow_vif;

	mt7915_tm_set_twx(phy, TM_MAC_TX, en);
}

static void
mt7915_tm_set_wx_fwames(stwuct mt7915_phy *phy, boow en)
{
	mt7915_tm_set_twx(phy, TM_MAC_WX_WXV, fawse);

	if (en) {
		stwuct mt7915_dev *dev = phy->dev;

		mt7915_tm_update_channew(phy);

		/* wead-cweaw */
		mt76_ww(dev, MT_MIB_SDW3(phy->mt76->band_idx));
		mt7915_tm_set_twx(phy, TM_MAC_WX_WXV, en);
	}
}

static int
mt7915_tm_wf_switch_mode(stwuct mt7915_dev *dev, u32 opew)
{
	stwuct mt7915_tm_wf_test weq = {
		.op.op_mode = cpu_to_we32(opew),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WF_TEST), &weq,
				 sizeof(weq), twue);
}

static int
mt7915_tm_set_tx_cont(stwuct mt7915_phy *phy, boow en)
{
#define TX_CONT_STAWT	0x05
#define TX_CONT_STOP	0x06
	stwuct mt7915_dev *dev = phy->dev;
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	int fweq1 = ieee80211_fwequency_to_channew(chandef->centew_fweq1);
	stwuct mt76_testmode_data *td = &phy->mt76->test;
	u32 func_idx = en ? TX_CONT_STAWT : TX_CONT_STOP;
	u8 wate_idx = td->tx_wate_idx, mode;
	u8 band = phy->mt76->band_idx;
	u16 watevaw;
	stwuct mt7915_tm_wf_test weq = {
		.action = 1,
		.icap_wen = 120,
		.op.wf.func_idx = cpu_to_we32(func_idx),
	};
	stwuct tm_tx_cont *tx_cont = &weq.op.wf.pawam.tx_cont;

	tx_cont->contwow_ch = chandef->chan->hw_vawue;
	tx_cont->centew_ch = fweq1;
	tx_cont->tx_ant = td->tx_antenna_mask;
	tx_cont->band = band;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_40:
		tx_cont->bw = CMD_CBW_40MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		tx_cont->bw = CMD_CBW_80MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
		tx_cont->bw = CMD_CBW_8080MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		tx_cont->bw = CMD_CBW_160MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_5:
		tx_cont->bw = CMD_CBW_5MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_10:
		tx_cont->bw = CMD_CBW_10MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_20:
		tx_cont->bw = CMD_CBW_20MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_20_NOHT:
		tx_cont->bw = CMD_CBW_20MHZ;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!en) {
		weq.op.wf.pawam.func_data = cpu_to_we32(band);
		goto out;
	}

	if (td->tx_wate_mode <= MT76_TM_TX_MODE_OFDM) {
		stwuct ieee80211_suppowted_band *sband;
		u8 idx = wate_idx;

		if (chandef->chan->band == NW80211_BAND_5GHZ)
			sband = &phy->mt76->sband_5g.sband;
		ewse if (chandef->chan->band == NW80211_BAND_6GHZ)
			sband = &phy->mt76->sband_6g.sband;
		ewse
			sband = &phy->mt76->sband_2g.sband;

		if (td->tx_wate_mode == MT76_TM_TX_MODE_OFDM)
			idx += 4;
		wate_idx = sband->bitwates[idx].hw_vawue & 0xff;
	}

	switch (td->tx_wate_mode) {
	case MT76_TM_TX_MODE_CCK:
		mode = MT_PHY_TYPE_CCK;
		bweak;
	case MT76_TM_TX_MODE_OFDM:
		mode = MT_PHY_TYPE_OFDM;
		bweak;
	case MT76_TM_TX_MODE_HT:
		mode = MT_PHY_TYPE_HT;
		bweak;
	case MT76_TM_TX_MODE_VHT:
		mode = MT_PHY_TYPE_VHT;
		bweak;
	case MT76_TM_TX_MODE_HE_SU:
		mode = MT_PHY_TYPE_HE_SU;
		bweak;
	case MT76_TM_TX_MODE_HE_EXT_SU:
		mode = MT_PHY_TYPE_HE_EXT_SU;
		bweak;
	case MT76_TM_TX_MODE_HE_TB:
		mode = MT_PHY_TYPE_HE_TB;
		bweak;
	case MT76_TM_TX_MODE_HE_MU:
		mode = MT_PHY_TYPE_HE_MU;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	watevaw =  mode << 6 | wate_idx;
	tx_cont->watevaw = cpu_to_we16(watevaw);

out:
	if (!en) {
		int wet;

		wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WF_TEST), &weq,
					sizeof(weq), twue);
		if (wet)
			wetuwn wet;

		wetuwn mt7915_tm_wf_switch_mode(dev, WF_OPEW_NOWMAW);
	}

	mt7915_tm_wf_switch_mode(dev, WF_OPEW_WF_TEST);
	mt7915_tm_update_channew(phy);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(WF_TEST), &weq,
				 sizeof(weq), twue);
}

static void
mt7915_tm_update_pawams(stwuct mt7915_phy *phy, u32 changed)
{
	stwuct mt76_testmode_data *td = &phy->mt76->test;
	boow en = phy->mt76->test.state != MT76_TM_STATE_OFF;

	if (changed & BIT(TM_CHANGED_FWEQ_OFFSET))
		mt7915_tm_set_fweq_offset(phy, en, en ? td->fweq_offset : 0);
	if (changed & BIT(TM_CHANGED_TXPOWEW))
		mt7915_tm_set_tx_powew(phy);
}

static int
mt7915_tm_set_state(stwuct mt76_phy *mphy, enum mt76_testmode_state state)
{
	stwuct mt76_testmode_data *td = &mphy->test;
	stwuct mt7915_phy *phy = mphy->pwiv;
	enum mt76_testmode_state pwev_state = td->state;

	mphy->test.state = state;

	if (pwev_state == MT76_TM_STATE_TX_FWAMES ||
	    state == MT76_TM_STATE_TX_FWAMES)
		mt7915_tm_set_tx_fwames(phy, state == MT76_TM_STATE_TX_FWAMES);
	ewse if (pwev_state == MT76_TM_STATE_WX_FWAMES ||
		 state == MT76_TM_STATE_WX_FWAMES)
		mt7915_tm_set_wx_fwames(phy, state == MT76_TM_STATE_WX_FWAMES);
	ewse if (pwev_state == MT76_TM_STATE_TX_CONT ||
		 state == MT76_TM_STATE_TX_CONT)
		mt7915_tm_set_tx_cont(phy, state == MT76_TM_STATE_TX_CONT);
	ewse if (pwev_state == MT76_TM_STATE_OFF ||
		 state == MT76_TM_STATE_OFF)
		mt7915_tm_init(phy, !(state == MT76_TM_STATE_OFF));

	if ((state == MT76_TM_STATE_IDWE &&
	     pwev_state == MT76_TM_STATE_OFF) ||
	    (state == MT76_TM_STATE_OFF &&
	     pwev_state == MT76_TM_STATE_IDWE)) {
		u32 changed = 0;
		int i;

		fow (i = 0; i < AWWAY_SIZE(tm_change_map); i++) {
			u16 cuw = tm_change_map[i];

			if (td->pawam_set[cuw / 32] & BIT(cuw % 32))
				changed |= BIT(i);
		}

		mt7915_tm_update_pawams(phy, changed);
	}

	wetuwn 0;
}

static int
mt7915_tm_set_pawams(stwuct mt76_phy *mphy, stwuct nwattw **tb,
		     enum mt76_testmode_state new_state)
{
	stwuct mt76_testmode_data *td = &mphy->test;
	stwuct mt7915_phy *phy = mphy->pwiv;
	stwuct mt7915_dev *dev = phy->dev;
	u32 chainmask = mphy->chainmask, changed = 0;
	boow ext_phy = phy != &dev->phy;
	int i;

	BUIWD_BUG_ON(NUM_TM_CHANGED >= 32);

	if (new_state == MT76_TM_STATE_OFF ||
	    td->state == MT76_TM_STATE_OFF)
		wetuwn 0;

	chainmask = ext_phy ? chainmask >> dev->chainshift : chainmask;
	if (td->tx_antenna_mask > chainmask)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(tm_change_map); i++) {
		if (tb[tm_change_map[i]])
			changed |= BIT(i);
	}

	mt7915_tm_update_pawams(phy, changed);

	wetuwn 0;
}

static int
mt7915_tm_dump_stats(stwuct mt76_phy *mphy, stwuct sk_buff *msg)
{
	stwuct mt7915_phy *phy = mphy->pwiv;
	stwuct mt7915_dev *dev = phy->dev;
	enum mt76_wxq_id q;
	void *wx, *wssi;
	u16 fcs_eww;
	int i;
	u32 cnt;

	wx = nwa_nest_stawt(msg, MT76_TM_STATS_ATTW_WAST_WX);
	if (!wx)
		wetuwn -ENOMEM;

	if (nwa_put_s32(msg, MT76_TM_WX_ATTW_FWEQ_OFFSET, phy->test.wast_fweq_offset))
		wetuwn -ENOMEM;

	wssi = nwa_nest_stawt(msg, MT76_TM_WX_ATTW_WCPI);
	if (!wssi)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(phy->test.wast_wcpi); i++)
		if (nwa_put_u8(msg, i, phy->test.wast_wcpi[i]))
			wetuwn -ENOMEM;

	nwa_nest_end(msg, wssi);

	wssi = nwa_nest_stawt(msg, MT76_TM_WX_ATTW_IB_WSSI);
	if (!wssi)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(phy->test.wast_ib_wssi); i++)
		if (nwa_put_s8(msg, i, phy->test.wast_ib_wssi[i]))
			wetuwn -ENOMEM;

	nwa_nest_end(msg, wssi);

	wssi = nwa_nest_stawt(msg, MT76_TM_WX_ATTW_WB_WSSI);
	if (!wssi)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(phy->test.wast_wb_wssi); i++)
		if (nwa_put_s8(msg, i, phy->test.wast_wb_wssi[i]))
			wetuwn -ENOMEM;

	nwa_nest_end(msg, wssi);

	if (nwa_put_u8(msg, MT76_TM_WX_ATTW_SNW, phy->test.wast_snw))
		wetuwn -ENOMEM;

	nwa_nest_end(msg, wx);

	cnt = mt76_ww(dev, MT_MIB_SDW3(phy->mt76->band_idx));
	fcs_eww = is_mt7915(&dev->mt76) ? FIEWD_GET(MT_MIB_SDW3_FCS_EWW_MASK, cnt) :
		FIEWD_GET(MT_MIB_SDW3_FCS_EWW_MASK_MT7916, cnt);

	q = phy->mt76->band_idx ? MT_WXQ_BAND1 : MT_WXQ_MAIN;
	mphy->test.wx_stats.packets[q] += fcs_eww;
	mphy->test.wx_stats.fcs_ewwow[q] += fcs_eww;

	wetuwn 0;
}

const stwuct mt76_testmode_ops mt7915_testmode_ops = {
	.set_state = mt7915_tm_set_state,
	.set_pawams = mt7915_tm_set_pawams,
	.dump_stats = mt7915_tm_dump_stats,
};
