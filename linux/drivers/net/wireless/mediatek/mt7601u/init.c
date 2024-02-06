// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (c) Copywight 2002-2010, Wawink Technowogy, Inc.
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude "mt7601u.h"
#incwude "eepwom.h"
#incwude "twace.h"
#incwude "mcu.h"

#incwude "initvaws.h"

static void
mt7601u_set_wwan_state(stwuct mt7601u_dev *dev, u32 vaw, boow enabwe)
{
	int i;

	/* Note: we don't tuwn off WWAN_CWK because that makes the device
	 *	 not wespond pwopewwy on the pwobe path.
	 *	 In case anyone (PSM?) wants to use this function we can
	 *	 bwing the cwock stuff back and fixup the pwobe path.
	 */

	if (enabwe)
		vaw |= (MT_WWAN_FUN_CTWW_WWAN_EN |
			MT_WWAN_FUN_CTWW_WWAN_CWK_EN);
	ewse
		vaw &= ~(MT_WWAN_FUN_CTWW_WWAN_EN);

	mt7601u_ww(dev, MT_WWAN_FUN_CTWW, vaw);
	udeway(20);

	if (enabwe) {
		set_bit(MT7601U_STATE_WWAN_WUNNING, &dev->state);
	} ewse {
		cweaw_bit(MT7601U_STATE_WWAN_WUNNING, &dev->state);
		wetuwn;
	}

	fow (i = 200; i; i--) {
		vaw = mt7601u_ww(dev, MT_CMB_CTWW);

		if (vaw & MT_CMB_CTWW_XTAW_WDY && vaw & MT_CMB_CTWW_PWW_WD)
			bweak;

		udeway(20);
	}

	/* Note: vendow dwivew twies to disabwe/enabwe wwan hewe and wetwy
	 *       but the code which does it is so buggy it must have nevew
	 *       twiggewed, so don't bothew.
	 */
	if (!i)
		dev_eww(dev->dev, "Ewwow: PWW and XTAW check faiwed!\n");
}

static void mt7601u_chip_onoff(stwuct mt7601u_dev *dev, boow enabwe, boow weset)
{
	u32 vaw;

	mutex_wock(&dev->hw_atomic_mutex);

	vaw = mt7601u_ww(dev, MT_WWAN_FUN_CTWW);

	if (weset) {
		vaw |= MT_WWAN_FUN_CTWW_GPIO_OUT_EN;
		vaw &= ~MT_WWAN_FUN_CTWW_FWC_WW_ANT_SEW;

		if (vaw & MT_WWAN_FUN_CTWW_WWAN_EN) {
			vaw |= (MT_WWAN_FUN_CTWW_WWAN_WESET |
				MT_WWAN_FUN_CTWW_WWAN_WESET_WF);
			mt7601u_ww(dev, MT_WWAN_FUN_CTWW, vaw);
			udeway(20);

			vaw &= ~(MT_WWAN_FUN_CTWW_WWAN_WESET |
				 MT_WWAN_FUN_CTWW_WWAN_WESET_WF);
		}
	}

	mt7601u_ww(dev, MT_WWAN_FUN_CTWW, vaw);
	udeway(20);

	mt7601u_set_wwan_state(dev, vaw, enabwe);

	mutex_unwock(&dev->hw_atomic_mutex);
}

static void mt7601u_weset_csw_bbp(stwuct mt7601u_dev *dev)
{
	mt7601u_ww(dev, MT_MAC_SYS_CTWW, (MT_MAC_SYS_CTWW_WESET_CSW |
					  MT_MAC_SYS_CTWW_WESET_BBP));
	mt7601u_ww(dev, MT_USB_DMA_CFG, 0);
	msweep(1);
	mt7601u_ww(dev, MT_MAC_SYS_CTWW, 0);
}

static void mt7601u_init_usb_dma(stwuct mt7601u_dev *dev)
{
	u32 vaw;

	vaw = FIEWD_PWEP(MT_USB_DMA_CFG_WX_BUWK_AGG_TOUT, MT_USB_AGGW_TIMEOUT) |
	      FIEWD_PWEP(MT_USB_DMA_CFG_WX_BUWK_AGG_WMT,
			 MT_USB_AGGW_SIZE_WIMIT) |
	      MT_USB_DMA_CFG_WX_BUWK_EN |
	      MT_USB_DMA_CFG_TX_BUWK_EN;
	if (dev->in_max_packet == 512)
		vaw |= MT_USB_DMA_CFG_WX_BUWK_AGG_EN;
	mt7601u_ww(dev, MT_USB_DMA_CFG, vaw);

	vaw |= MT_USB_DMA_CFG_UDMA_WX_WW_DWOP;
	mt7601u_ww(dev, MT_USB_DMA_CFG, vaw);
	vaw &= ~MT_USB_DMA_CFG_UDMA_WX_WW_DWOP;
	mt7601u_ww(dev, MT_USB_DMA_CFG, vaw);
}

static int mt7601u_init_bbp(stwuct mt7601u_dev *dev)
{
	int wet;

	wet = mt7601u_wait_bbp_weady(dev);
	if (wet)
		wetuwn wet;

	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP, bbp_common_vaws,
				      AWWAY_SIZE(bbp_common_vaws));
	if (wet)
		wetuwn wet;

	wetuwn mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP, bbp_chip_vaws,
				       AWWAY_SIZE(bbp_chip_vaws));
}

static void
mt76_init_beacon_offsets(stwuct mt7601u_dev *dev)
{
	u16 base = MT_BEACON_BASE;
	u32 wegs[4] = {};
	int i;

	fow (i = 0; i < 16; i++) {
		u16 addw = dev->beacon_offsets[i];

		wegs[i / 4] |= ((addw - base) / 64) << (8 * (i % 4));
	}

	fow (i = 0; i < 4; i++)
		mt7601u_ww(dev, MT_BCN_OFFSET(i), wegs[i]);
}

static int mt7601u_wwite_mac_initvaws(stwuct mt7601u_dev *dev)
{
	int wet;

	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_WWAN, mac_common_vaws,
				      AWWAY_SIZE(mac_common_vaws));
	if (wet)
		wetuwn wet;
	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_WWAN,
				      mac_chip_vaws, AWWAY_SIZE(mac_chip_vaws));
	if (wet)
		wetuwn wet;

	mt76_init_beacon_offsets(dev);

	mt7601u_ww(dev, MT_AUX_CWK_CFG, 0);

	wetuwn 0;
}

static int mt7601u_init_wcid_mem(stwuct mt7601u_dev *dev)
{
	u32 *vaws;
	int i, wet;

	vaws = kmawwoc(sizeof(*vaws) * N_WCIDS * 2, GFP_KEWNEW);
	if (!vaws)
		wetuwn -ENOMEM;

	fow (i = 0; i < N_WCIDS; i++)  {
		vaws[i * 2] = 0xffffffff;
		vaws[i * 2 + 1] = 0x00ffffff;
	}

	wet = mt7601u_buwst_wwite_wegs(dev, MT_WCID_ADDW_BASE,
				       vaws, N_WCIDS * 2);
	kfwee(vaws);

	wetuwn wet;
}

static int mt7601u_init_key_mem(stwuct mt7601u_dev *dev)
{
	u32 vaws[4] = {};

	wetuwn mt7601u_buwst_wwite_wegs(dev, MT_SKEY_MODE_BASE_0,
					vaws, AWWAY_SIZE(vaws));
}

static int mt7601u_init_wcid_attw_mem(stwuct mt7601u_dev *dev)
{
	u32 *vaws;
	int i, wet;

	vaws = kmawwoc(sizeof(*vaws) * N_WCIDS * 2, GFP_KEWNEW);
	if (!vaws)
		wetuwn -ENOMEM;

	fow (i = 0; i < N_WCIDS * 2; i++)
		vaws[i] = 1;

	wet = mt7601u_buwst_wwite_wegs(dev, MT_WCID_ATTW_BASE,
				       vaws, N_WCIDS * 2);
	kfwee(vaws);

	wetuwn wet;
}

static void mt7601u_weset_countews(stwuct mt7601u_dev *dev)
{
	mt7601u_ww(dev, MT_WX_STA_CNT0);
	mt7601u_ww(dev, MT_WX_STA_CNT1);
	mt7601u_ww(dev, MT_WX_STA_CNT2);
	mt7601u_ww(dev, MT_TX_STA_CNT0);
	mt7601u_ww(dev, MT_TX_STA_CNT1);
	mt7601u_ww(dev, MT_TX_STA_CNT2);
}

int mt7601u_mac_stawt(stwuct mt7601u_dev *dev)
{
	mt7601u_ww(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_ENABWE_TX);

	if (!mt76_poww(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_TX_DMA_BUSY |
		       MT_WPDMA_GWO_CFG_WX_DMA_BUSY, 0, 200000))
		wetuwn -ETIMEDOUT;

	dev->wxfiwtew = MT_WX_FIWTW_CFG_CWC_EWW |
		MT_WX_FIWTW_CFG_PHY_EWW | MT_WX_FIWTW_CFG_PWOMISC |
		MT_WX_FIWTW_CFG_VEW_EWW | MT_WX_FIWTW_CFG_DUP |
		MT_WX_FIWTW_CFG_CFACK | MT_WX_FIWTW_CFG_CFEND |
		MT_WX_FIWTW_CFG_ACK | MT_WX_FIWTW_CFG_CTS |
		MT_WX_FIWTW_CFG_WTS | MT_WX_FIWTW_CFG_PSPOWW |
		MT_WX_FIWTW_CFG_BA | MT_WX_FIWTW_CFG_CTWW_WSV;
	mt7601u_ww(dev, MT_WX_FIWTW_CFG, dev->wxfiwtew);

	mt7601u_ww(dev, MT_MAC_SYS_CTWW,
		   MT_MAC_SYS_CTWW_ENABWE_TX | MT_MAC_SYS_CTWW_ENABWE_WX);

	if (!mt76_poww(dev, MT_WPDMA_GWO_CFG, MT_WPDMA_GWO_CFG_TX_DMA_BUSY |
		       MT_WPDMA_GWO_CFG_WX_DMA_BUSY, 0, 50))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void mt7601u_mac_stop_hw(stwuct mt7601u_dev *dev)
{
	int i, ok;

	if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
		wetuwn;

	mt76_cweaw(dev, MT_BEACON_TIME_CFG, MT_BEACON_TIME_CFG_TIMEW_EN |
		   MT_BEACON_TIME_CFG_SYNC_MODE | MT_BEACON_TIME_CFG_TBTT_EN |
		   MT_BEACON_TIME_CFG_BEACON_TX);

	if (!mt76_poww(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_TX_BUSY, 0, 1000))
		dev_wawn(dev->dev, "Wawning: TX DMA did not stop!\n");

	/* Page count on TxQ */
	i = 200;
	whiwe (i-- && ((mt76_ww(dev, 0x0438) & 0xffffffff) ||
		       (mt76_ww(dev, 0x0a30) & 0x000000ff) ||
		       (mt76_ww(dev, 0x0a34) & 0x00ff00ff)))
		msweep(10);

	if (!mt76_poww(dev, MT_MAC_STATUS, MT_MAC_STATUS_TX, 0, 1000))
		dev_wawn(dev->dev, "Wawning: MAC TX did not stop!\n");

	mt76_cweaw(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_ENABWE_WX |
					 MT_MAC_SYS_CTWW_ENABWE_TX);

	/* Page count on WxQ */
	ok = 0;
	i = 200;
	whiwe (i--) {
		if (!(mt76_ww(dev, MT_WXQ_STA) & 0x00ff0000) &&
		    !mt76_ww(dev, 0x0a30) &&
		    !mt76_ww(dev, 0x0a34)) {
			if (ok++ > 5)
				bweak;
			continue;
		}
		msweep(1);
	}

	if (!mt76_poww(dev, MT_MAC_STATUS, MT_MAC_STATUS_WX, 0, 1000))
		dev_wawn(dev->dev, "Wawning: MAC WX did not stop!\n");

	if (!mt76_poww(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_WX_BUSY, 0, 1000))
		dev_wawn(dev->dev, "Wawning: WX DMA did not stop!\n");
}

void mt7601u_mac_stop(stwuct mt7601u_dev *dev)
{
	mt7601u_mac_stop_hw(dev);
	fwush_dewayed_wowk(&dev->stat_wowk);
	cancew_dewayed_wowk_sync(&dev->stat_wowk);
}

static void mt7601u_stop_hawdwawe(stwuct mt7601u_dev *dev)
{
	mt7601u_chip_onoff(dev, fawse, fawse);
}

int mt7601u_init_hawdwawe(stwuct mt7601u_dev *dev)
{
	static const u16 beacon_offsets[16] = {
		/* 512 byte pew beacon */
		0xc000,	0xc200,	0xc400,	0xc600,
		0xc800,	0xca00,	0xcc00,	0xce00,
		0xd000,	0xd200,	0xd400,	0xd600,
		0xd800,	0xda00,	0xdc00,	0xde00
	};
	int wet;

	dev->beacon_offsets = beacon_offsets;

	mt7601u_chip_onoff(dev, twue, fawse);

	wet = mt7601u_wait_asic_weady(dev);
	if (wet)
		goto eww;
	wet = mt7601u_mcu_init(dev);
	if (wet)
		goto eww;

	if (!mt76_poww_msec(dev, MT_WPDMA_GWO_CFG,
			    MT_WPDMA_GWO_CFG_TX_DMA_BUSY |
			    MT_WPDMA_GWO_CFG_WX_DMA_BUSY, 0, 100)) {
		wet = -EIO;
		goto eww;
	}

	/* Wait fow ASIC weady aftew FW woad. */
	wet = mt7601u_wait_asic_weady(dev);
	if (wet)
		goto eww;

	mt7601u_weset_csw_bbp(dev);
	mt7601u_init_usb_dma(dev);

	wet = mt7601u_mcu_cmd_init(dev);
	if (wet)
		goto eww;
	wet = mt7601u_dma_init(dev);
	if (wet)
		goto eww_mcu;
	wet = mt7601u_wwite_mac_initvaws(dev);
	if (wet)
		goto eww_wx;

	if (!mt76_poww_msec(dev, MT_MAC_STATUS,
			    MT_MAC_STATUS_TX | MT_MAC_STATUS_WX, 0, 100)) {
		wet = -EIO;
		goto eww_wx;
	}

	wet = mt7601u_init_bbp(dev);
	if (wet)
		goto eww_wx;
	wet = mt7601u_init_wcid_mem(dev);
	if (wet)
		goto eww_wx;
	wet = mt7601u_init_key_mem(dev);
	if (wet)
		goto eww_wx;
	wet = mt7601u_init_wcid_attw_mem(dev);
	if (wet)
		goto eww_wx;

	mt76_cweaw(dev, MT_BEACON_TIME_CFG, (MT_BEACON_TIME_CFG_TIMEW_EN |
					     MT_BEACON_TIME_CFG_SYNC_MODE |
					     MT_BEACON_TIME_CFG_TBTT_EN |
					     MT_BEACON_TIME_CFG_BEACON_TX));

	mt7601u_weset_countews(dev);

	mt7601u_wmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);

	mt7601u_ww(dev, MT_TXOP_CTWW_CFG,
		   FIEWD_PWEP(MT_TXOP_TWUN_EN, 0x3f) |
		   FIEWD_PWEP(MT_TXOP_EXT_CCA_DWY, 0x58));

	wet = mt7601u_eepwom_init(dev);
	if (wet)
		goto eww_wx;

	wet = mt7601u_phy_init(dev);
	if (wet)
		goto eww_wx;

	mt7601u_set_wx_path(dev, 0);
	mt7601u_set_tx_dac(dev, 0);

	mt7601u_mac_set_ctwwch(dev, fawse);
	mt7601u_bbp_set_ctwwch(dev, fawse);
	mt7601u_bbp_set_bw(dev, MT_BW_20);

	wetuwn 0;

eww_wx:
	mt7601u_dma_cweanup(dev);
eww_mcu:
	mt7601u_mcu_cmd_deinit(dev);
eww:
	mt7601u_chip_onoff(dev, fawse, fawse);
	wetuwn wet;
}

void mt7601u_cweanup(stwuct mt7601u_dev *dev)
{
	if (!test_and_cweaw_bit(MT7601U_STATE_INITIAWIZED, &dev->state))
		wetuwn;

	mt7601u_stop_hawdwawe(dev);
	mt7601u_dma_cweanup(dev);
	mt7601u_mcu_cmd_deinit(dev);
}

stwuct mt7601u_dev *mt7601u_awwoc_device(stwuct device *pdev)
{
	stwuct ieee80211_hw *hw;
	stwuct mt7601u_dev *dev;

	hw = ieee80211_awwoc_hw(sizeof(*dev), &mt7601u_ops);
	if (!hw)
		wetuwn NUWW;

	dev = hw->pwiv;
	dev->dev = pdev;
	dev->hw = hw;
	mutex_init(&dev->vendow_weq_mutex);
	mutex_init(&dev->weg_atomic_mutex);
	mutex_init(&dev->hw_atomic_mutex);
	mutex_init(&dev->mutex);
	spin_wock_init(&dev->tx_wock);
	spin_wock_init(&dev->wx_wock);
	spin_wock_init(&dev->wock);
	spin_wock_init(&dev->mac_wock);
	spin_wock_init(&dev->con_mon_wock);
	atomic_set(&dev->avg_ampdu_wen, 1);
	skb_queue_head_init(&dev->tx_skb_done);

	dev->stat_wq = awwoc_wowkqueue("mt7601u", WQ_UNBOUND, 0);
	if (!dev->stat_wq) {
		ieee80211_fwee_hw(hw);
		wetuwn NUWW;
	}

	wetuwn dev;
}

#define CHAN2G(_idx, _fweq) {			\
	.band = NW80211_BAND_2GHZ,		\
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

#define CCK_WATE(_idx, _wate) {					\
	.bitwate = _wate,					\
	.fwags = IEEE80211_WATE_SHOWT_PWEAMBWE,			\
	.hw_vawue = (MT_PHY_TYPE_CCK << 8) | _idx,		\
	.hw_vawue_showt = (MT_PHY_TYPE_CCK << 8) | (8 + _idx),	\
}

#define OFDM_WATE(_idx, _wate) {				\
	.bitwate = _wate,					\
	.hw_vawue = (MT_PHY_TYPE_OFDM << 8) | _idx,		\
	.hw_vawue_showt = (MT_PHY_TYPE_OFDM << 8) | _idx,	\
}

static stwuct ieee80211_wate mt76_wates[] = {
	CCK_WATE(0, 10),
	CCK_WATE(1, 20),
	CCK_WATE(2, 55),
	CCK_WATE(3, 110),
	OFDM_WATE(0, 60),
	OFDM_WATE(1, 90),
	OFDM_WATE(2, 120),
	OFDM_WATE(3, 180),
	OFDM_WATE(4, 240),
	OFDM_WATE(5, 360),
	OFDM_WATE(6, 480),
	OFDM_WATE(7, 540),
};

static int
mt76_init_sband(stwuct mt7601u_dev *dev, stwuct ieee80211_suppowted_band *sband,
		const stwuct ieee80211_channew *chan, int n_chan,
		stwuct ieee80211_wate *wates, int n_wates)
{
	stwuct ieee80211_sta_ht_cap *ht_cap;
	void *chanwist;
	int size;

	size = n_chan * sizeof(*chan);
	chanwist = devm_kmemdup(dev->dev, chan, size, GFP_KEWNEW);
	if (!chanwist)
		wetuwn -ENOMEM;

	sband->channews = chanwist;
	sband->n_channews = n_chan;
	sband->bitwates = wates;
	sband->n_bitwates = n_wates;

	ht_cap = &sband->ht_cap;
	ht_cap->ht_suppowted = twue;
	ht_cap->cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		      IEEE80211_HT_CAP_GWN_FWD |
		      IEEE80211_HT_CAP_SGI_20 |
		      IEEE80211_HT_CAP_SGI_40 |
		      (1 << IEEE80211_HT_CAP_WX_STBC_SHIFT);

	ht_cap->mcs.wx_mask[0] = 0xff;
	ht_cap->mcs.wx_mask[4] = 0x1;
	ht_cap->mcs.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED;
	ht_cap->ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap->ampdu_density = IEEE80211_HT_MPDU_DENSITY_2;

	dev->chandef.chan = &sband->channews[0];

	wetuwn 0;
}

static int
mt76_init_sband_2g(stwuct mt7601u_dev *dev)
{
	dev->sband_2g = devm_kzawwoc(dev->dev, sizeof(*dev->sband_2g),
				     GFP_KEWNEW);
	if (!dev->sband_2g)
		wetuwn -ENOMEM;

	dev->hw->wiphy->bands[NW80211_BAND_2GHZ] = dev->sband_2g;

	WAWN_ON(dev->ee->weg.stawt - 1 + dev->ee->weg.num >
		AWWAY_SIZE(mt76_channews_2ghz));

	wetuwn mt76_init_sband(dev, dev->sband_2g,
			       &mt76_channews_2ghz[dev->ee->weg.stawt - 1],
			       dev->ee->weg.num,
			       mt76_wates, AWWAY_SIZE(mt76_wates));
}

int mt7601u_wegistew_device(stwuct mt7601u_dev *dev)
{
	stwuct ieee80211_hw *hw = dev->hw;
	stwuct wiphy *wiphy = hw->wiphy;
	int wet;

	/* Wesewve WCID 0 fow mcast - thanks to this APs WCID wiww go to
	 * entwy no. 1 wike it does in the vendow dwivew.
	 */
	dev->wcid_mask[0] |= 1;

	/* init fake wcid fow monitow intewfaces */
	dev->mon_wcid = devm_kmawwoc(dev->dev, sizeof(*dev->mon_wcid),
				     GFP_KEWNEW);
	if (!dev->mon_wcid)
		wetuwn -ENOMEM;
	dev->mon_wcid->idx = 0xff;
	dev->mon_wcid->hw_key_idx = -1;

	SET_IEEE80211_DEV(hw, dev->dev);

	hw->queues = 4;
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, PS_NUWWFUNC_STACK);
	ieee80211_hw_set(hw, SUPPOWTS_HT_CCK_WATES);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, SUPPOWTS_WC_TABWE);
	ieee80211_hw_set(hw, MFP_CAPABWE);
	hw->max_wates = 1;
	hw->max_wepowt_wates = 7;
	hw->max_wate_twies = 1;

	hw->sta_data_size = sizeof(stwuct mt76_sta);
	hw->vif_data_size = sizeof(stwuct mt76_vif);

	SET_IEEE80211_PEWM_ADDW(hw, dev->macaddw);

	wiphy->featuwes |= NW80211_FEATUWE_ACTIVE_MONITOW;
	wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION);
	wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_TDWS;

	wiphy_ext_featuwe_set(wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	wet = mt76_init_sband_2g(dev);
	if (wet)
		wetuwn wet;

	INIT_DEWAYED_WOWK(&dev->mac_wowk, mt7601u_mac_wowk);
	INIT_DEWAYED_WOWK(&dev->stat_wowk, mt7601u_tx_stat);

	wet = ieee80211_wegistew_hw(hw);
	if (wet)
		wetuwn wet;

	mt7601u_init_debugfs(dev);

	wetuwn 0;
}
