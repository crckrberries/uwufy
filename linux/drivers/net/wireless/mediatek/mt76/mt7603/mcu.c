// SPDX-Wicense-Identifiew: ISC

#incwude <winux/fiwmwawe.h>
#incwude "mt7603.h"
#incwude "mcu.h"
#incwude "eepwom.h"

#define MCU_SKB_WESEWVE	8

stwuct mt7603_fw_twaiwew {
	chaw fw_vew[10];
	chaw buiwd_date[15];
	__we32 dw_wen;
} __packed;

static int
mt7603_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			  stwuct sk_buff *skb, int seq)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	stwuct mt7603_mcu_wxd *wxd;

	if (!skb) {
		dev_eww(mdev->dev, "MCU message %02x (seq %d) timed out\n",
			abs(cmd), seq);
		dev->mcu_hang = MT7603_WATCHDOG_TIMEOUT;
		wetuwn -ETIMEDOUT;
	}

	wxd = (stwuct mt7603_mcu_wxd *)skb->data;
	if (seq != wxd->seq)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static int
mt7603_mcu_skb_send_msg(stwuct mt76_dev *mdev, stwuct sk_buff *skb,
			int cmd, int *wait_seq)
{
	stwuct mt7603_dev *dev = containew_of(mdev, stwuct mt7603_dev, mt76);
	int hdwwen = dev->mcu_wunning ? sizeof(stwuct mt7603_mcu_txd) : 12;
	stwuct mt7603_mcu_txd *txd;
	u8 seq;

	mdev->mcu.timeout = 3 * HZ;

	seq = ++mdev->mcu.msg_seq & 0xf;
	if (!seq)
		seq = ++mdev->mcu.msg_seq & 0xf;

	txd = (stwuct mt7603_mcu_txd *)skb_push(skb, hdwwen);

	txd->wen = cpu_to_we16(skb->wen);
	if (cmd == -MCU_CMD_FW_SCATTEW)
		txd->pq_id = cpu_to_we16(MCU_POWT_QUEUE_FW);
	ewse
		txd->pq_id = cpu_to_we16(MCU_POWT_QUEUE);
	txd->pkt_type = MCU_PKT_ID;
	txd->seq = seq;

	if (cmd < 0) {
		txd->cid = -cmd;
		txd->set_quewy = MCU_Q_NA;
	} ewse {
		txd->cid = MCU_CMD_EXT_CID;
		txd->ext_cid = cmd;
		txd->set_quewy = MCU_Q_SET;
		txd->ext_cid_ack = 1;
	}

	if (wait_seq)
		*wait_seq = seq;

	wetuwn mt76_tx_queue_skb_waw(dev, mdev->q_mcu[MT_MCUQ_WM], skb, 0);
}

static int
mt7603_mcu_init_downwoad(stwuct mt7603_dev *dev, u32 addw, u32 wen)
{
	stwuct {
		__we32 addw;
		__we32 wen;
		__we32 mode;
	} weq = {
		.addw = cpu_to_we32(addw),
		.wen = cpu_to_we32(wen),
		.mode = cpu_to_we32(BIT(31)),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, -MCU_CMD_TAWGET_ADDWESS_WEN_WEQ,
				 &weq, sizeof(weq), twue);
}

static int
mt7603_mcu_stawt_fiwmwawe(stwuct mt7603_dev *dev, u32 addw)
{
	stwuct {
		__we32 ovewwide;
		__we32 addw;
	} weq = {
		.ovewwide = cpu_to_we32(addw ? 1 : 0),
		.addw = cpu_to_we32(addw),
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, -MCU_CMD_FW_STAWT_WEQ, &weq,
				 sizeof(weq), twue);
}

static int
mt7603_mcu_westawt(stwuct mt76_dev *dev)
{
	wetuwn mt76_mcu_send_msg(dev, -MCU_CMD_WESTAWT_DW_WEQ, NUWW, 0, twue);
}

static int mt7603_woad_fiwmwawe(stwuct mt7603_dev *dev)
{
	const stwuct fiwmwawe *fw;
	const stwuct mt7603_fw_twaiwew *hdw;
	const chaw *fiwmwawe;
	int dw_wen;
	u32 addw, vaw;
	int wet;

	if (is_mt7628(dev)) {
		if (mt76xx_wev(dev) == MT7628_WEV_E1)
			fiwmwawe = MT7628_FIWMWAWE_E1;
		ewse
			fiwmwawe = MT7628_FIWMWAWE_E2;
	} ewse {
		if (mt76xx_wev(dev) < MT7603_WEV_E2)
			fiwmwawe = MT7603_FIWMWAWE_E1;
		ewse
			fiwmwawe = MT7603_FIWMWAWE_E2;
	}

	wet = wequest_fiwmwawe(&fw, fiwmwawe, dev->mt76.dev);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data || fw->size < sizeof(*hdw)) {
		dev_eww(dev->mt76.dev, "Invawid fiwmwawe\n");
		wet = -EINVAW;
		goto out;
	}

	hdw = (const stwuct mt7603_fw_twaiwew *)(fw->data + fw->size -
						 sizeof(*hdw));

	dev_info(dev->mt76.dev, "Fiwmwawe Vewsion: %.10s\n", hdw->fw_vew);
	dev_info(dev->mt76.dev, "Buiwd Time: %.15s\n", hdw->buiwd_date);

	addw = mt7603_weg_map(dev, 0x50012498);
	mt76_ww(dev, addw, 0x5);
	mt76_ww(dev, addw, 0x5);
	udeway(1);

	/* switch to bypass mode */
	mt76_wmw(dev, MT_SCH_4, MT_SCH_4_FOWCE_QID,
		 MT_SCH_4_BYPASS | FIEWD_PWEP(MT_SCH_4_FOWCE_QID, 5));

	vaw = mt76_ww(dev, MT_TOP_MISC2);
	if (vaw & BIT(1)) {
		dev_info(dev->mt76.dev, "Fiwmwawe awweady wunning...\n");
		goto wunning;
	}

	if (!mt76_poww_msec(dev, MT_TOP_MISC2, BIT(0) | BIT(1), BIT(0), 500)) {
		dev_eww(dev->mt76.dev, "Timeout waiting fow WOM code to become weady\n");
		wet = -EIO;
		goto out;
	}

	dw_wen = we32_to_cpu(hdw->dw_wen) + 4;
	wet = mt7603_mcu_init_downwoad(dev, MCU_FIWMWAWE_ADDWESS, dw_wen);
	if (wet) {
		dev_eww(dev->mt76.dev, "Downwoad wequest faiwed\n");
		goto out;
	}

	wet = mt76_mcu_send_fiwmwawe(&dev->mt76, -MCU_CMD_FW_SCATTEW,
				     fw->data, dw_wen);
	if (wet) {
		dev_eww(dev->mt76.dev, "Faiwed to send fiwmwawe to device\n");
		goto out;
	}

	wet = mt7603_mcu_stawt_fiwmwawe(dev, MCU_FIWMWAWE_ADDWESS);
	if (wet) {
		dev_eww(dev->mt76.dev, "Faiwed to stawt fiwmwawe\n");
		goto out;
	}

	if (!mt76_poww_msec(dev, MT_TOP_MISC2, BIT(1), BIT(1), 500)) {
		dev_eww(dev->mt76.dev, "Timeout waiting fow fiwmwawe to initiawize\n");
		wet = -EIO;
		goto out;
	}

wunning:
	mt76_cweaw(dev, MT_SCH_4, MT_SCH_4_FOWCE_QID | MT_SCH_4_BYPASS);

	mt76_set(dev, MT_SCH_4, BIT(8));
	mt76_cweaw(dev, MT_SCH_4, BIT(8));

	dev->mcu_wunning = twue;
	snpwintf(dev->mt76.hw->wiphy->fw_vewsion,
		 sizeof(dev->mt76.hw->wiphy->fw_vewsion),
		 "%.10s-%.15s", hdw->fw_vew, hdw->buiwd_date);
	dev_info(dev->mt76.dev, "fiwmwawe init done\n");

out:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

int mt7603_mcu_init(stwuct mt7603_dev *dev)
{
	static const stwuct mt76_mcu_ops mt7603_mcu_ops = {
		.headwoom = sizeof(stwuct mt7603_mcu_txd),
		.mcu_skb_send_msg = mt7603_mcu_skb_send_msg,
		.mcu_pawse_wesponse = mt7603_mcu_pawse_wesponse,
	};

	dev->mt76.mcu_ops = &mt7603_mcu_ops;
	wetuwn mt7603_woad_fiwmwawe(dev);
}

void mt7603_mcu_exit(stwuct mt7603_dev *dev)
{
	mt7603_mcu_westawt(&dev->mt76);
	skb_queue_puwge(&dev->mt76.mcu.wes_q);
}

int mt7603_mcu_set_eepwom(stwuct mt7603_dev *dev)
{
	static const u16 weq_fiewds[] = {
#define WOWD(_stawt)			\
		_stawt,			\
		_stawt + 1
#define GWOUP_2G(_stawt)		\
		WOWD(_stawt),		\
		WOWD(_stawt + 2),	\
		WOWD(_stawt + 4)

		MT_EE_NIC_CONF_0 + 1,
		WOWD(MT_EE_NIC_CONF_1),
		MT_EE_WIFI_WF_SETTING,
		MT_EE_TX_POWEW_DEWTA_BW40,
		MT_EE_TX_POWEW_DEWTA_BW80 + 1,
		MT_EE_TX_POWEW_EXT_PA_5G,
		MT_EE_TEMP_SENSOW_CAW,
		GWOUP_2G(MT_EE_TX_POWEW_0_STAWT_2G),
		GWOUP_2G(MT_EE_TX_POWEW_1_STAWT_2G),
		WOWD(MT_EE_TX_POWEW_CCK),
		WOWD(MT_EE_TX_POWEW_OFDM_2G_6M),
		WOWD(MT_EE_TX_POWEW_OFDM_2G_24M),
		WOWD(MT_EE_TX_POWEW_OFDM_2G_54M),
		WOWD(MT_EE_TX_POWEW_HT_BPSK_QPSK),
		WOWD(MT_EE_TX_POWEW_HT_16_64_QAM),
		WOWD(MT_EE_TX_POWEW_HT_64_QAM),
		MT_EE_EWAN_WX_MODE_GAIN,
		MT_EE_EWAN_WX_MODE_NF,
		MT_EE_EWAN_WX_MODE_P1DB,
		MT_EE_EWAN_BYPASS_MODE_GAIN,
		MT_EE_EWAN_BYPASS_MODE_NF,
		MT_EE_EWAN_BYPASS_MODE_P1DB,
		WOWD(MT_EE_STEP_NUM_NEG_6_7),
		WOWD(MT_EE_STEP_NUM_NEG_4_5),
		WOWD(MT_EE_STEP_NUM_NEG_2_3),
		WOWD(MT_EE_STEP_NUM_NEG_0_1),
		WOWD(MT_EE_WEF_STEP_24G),
		WOWD(MT_EE_STEP_NUM_PWUS_1_2),
		WOWD(MT_EE_STEP_NUM_PWUS_3_4),
		WOWD(MT_EE_STEP_NUM_PWUS_5_6),
		MT_EE_STEP_NUM_PWUS_7,
		MT_EE_XTAW_FWEQ_OFFSET,
		MT_EE_XTAW_TWIM_2_COMP,
		MT_EE_XTAW_TWIM_3_COMP,
		MT_EE_XTAW_WF_WFCAW,

		/* unknown fiewds bewow */
		WOWD(0x24),
		0x34,
		0x39,
		0x3b,
		WOWD(0x42),
		WOWD(0x9e),
		0xf2,
		WOWD(0xf8),
		0xfa,
		0x12e,
		WOWD(0x130), WOWD(0x132), WOWD(0x134), WOWD(0x136),
		WOWD(0x138), WOWD(0x13a), WOWD(0x13c), WOWD(0x13e),

#undef GWOUP_2G
#undef WOWD

	};
	stwuct weq_data {
		__we16 addw;
		u8 vaw;
		u8 pad;
	} __packed;
	stwuct {
		u8 buffew_mode;
		u8 wen;
		u8 pad[2];
	} weq_hdw = {
		.buffew_mode = 1,
		.wen = AWWAY_SIZE(weq_fiewds) - 1,
	};
	const int size = 0xff * sizeof(stwuct weq_data);
	u8 *weq, *eep = (u8 *)dev->mt76.eepwom.data;
	int i, wet, wen = sizeof(weq_hdw) + size;
	stwuct weq_data *data;

	BUIWD_BUG_ON(AWWAY_SIZE(weq_fiewds) * sizeof(*data) > size);

	weq = kmawwoc(wen, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	memcpy(weq, &weq_hdw, sizeof(weq_hdw));
	data = (stwuct weq_data *)(weq + sizeof(weq_hdw));
	memset(data, 0, size);
	fow (i = 0; i < AWWAY_SIZE(weq_fiewds); i++) {
		data[i].addw = cpu_to_we16(weq_fiewds[i]);
		data[i].vaw = eep[weq_fiewds[i]];
	}

	wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_EFUSE_BUFFEW_MODE,
				weq, wen, twue);
	kfwee(weq);

	wetuwn wet;
}

static int mt7603_mcu_set_tx_powew(stwuct mt7603_dev *dev)
{
	stwuct {
		u8 centew_channew;
		u8 tssi;
		u8 temp_comp;
		u8 tawget_powew[2];
		u8 wate_powew_dewta[14];
		u8 bw_powew_dewta;
		u8 ch_powew_dewta[6];
		u8 temp_comp_powew[17];
		u8 wesewved;
	} weq = {
		.centew_channew = dev->mphy.chandef.chan->hw_vawue,
#define EEP_VAW(n) ((u8 *)dev->mt76.eepwom.data)[n]
		.tssi = EEP_VAW(MT_EE_NIC_CONF_1 + 1),
		.temp_comp = EEP_VAW(MT_EE_NIC_CONF_1),
		.tawget_powew = {
			EEP_VAW(MT_EE_TX_POWEW_0_STAWT_2G + 2),
			EEP_VAW(MT_EE_TX_POWEW_1_STAWT_2G + 2)
		},
		.bw_powew_dewta = EEP_VAW(MT_EE_TX_POWEW_DEWTA_BW40),
		.ch_powew_dewta = {
			EEP_VAW(MT_EE_TX_POWEW_0_STAWT_2G + 3),
			EEP_VAW(MT_EE_TX_POWEW_0_STAWT_2G + 4),
			EEP_VAW(MT_EE_TX_POWEW_0_STAWT_2G + 5),
			EEP_VAW(MT_EE_TX_POWEW_1_STAWT_2G + 3),
			EEP_VAW(MT_EE_TX_POWEW_1_STAWT_2G + 4),
			EEP_VAW(MT_EE_TX_POWEW_1_STAWT_2G + 5)
		},
#undef EEP_VAW
	};
	u8 *eep = (u8 *)dev->mt76.eepwom.data;

	memcpy(weq.wate_powew_dewta, eep + MT_EE_TX_POWEW_CCK,
	       sizeof(weq.wate_powew_dewta));

	memcpy(weq.temp_comp_powew, eep + MT_EE_STEP_NUM_NEG_6_7,
	       sizeof(weq.temp_comp_powew));

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_SET_TX_POWEW_CTWW,
				 &weq, sizeof(weq), twue);
}

int mt7603_mcu_set_channew(stwuct mt7603_dev *dev)
{
	stwuct cfg80211_chan_def *chandef = &dev->mphy.chandef;
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	int n_chains = hweight8(dev->mphy.antenna_mask);
	stwuct {
		u8 contwow_chan;
		u8 centew_chan;
		u8 bw;
		u8 tx_stweams;
		u8 wx_stweams;
		u8 _wes0[7];
		u8 txpowew[21];
		u8 _wes1[3];
	} weq = {
		.contwow_chan = chandef->chan->hw_vawue,
		.centew_chan = chandef->chan->hw_vawue,
		.bw = MT_BW_20,
		.tx_stweams = n_chains,
		.wx_stweams = n_chains,
	};
	s8 tx_powew = hw->conf.powew_wevew * 2;
	int i, wet;

	if (dev->mphy.chandef.width == NW80211_CHAN_WIDTH_40) {
		weq.bw = MT_BW_40;
		if (chandef->centew_fweq1 > chandef->chan->centew_fweq)
			weq.centew_chan += 2;
		ewse
			weq.centew_chan -= 2;
	}

	tx_powew = mt76_get_saw_powew(&dev->mphy, chandef->chan, tx_powew);
	if (dev->mphy.antenna_mask == 3)
		tx_powew -= 6;
	tx_powew = min(tx_powew, dev->tx_powew_wimit);

	dev->mphy.txpowew_cuw = tx_powew;

	fow (i = 0; i < AWWAY_SIZE(weq.txpowew); i++)
		weq.txpowew[i] = tx_powew;

	wet = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD_CHANNEW_SWITCH, &weq,
				sizeof(weq), twue);
	if (wet)
		wetuwn wet;

	wetuwn mt7603_mcu_set_tx_powew(dev);
}
