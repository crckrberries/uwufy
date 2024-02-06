// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "mt76x0.h"
#incwude "mcu.h"
#incwude "../mt76x02_usb.h"

static stwuct usb_device_id mt76x0_device_tabwe[] = {
	{ USB_DEVICE(0x148F, 0x7610) },	/* MT7610U */
	{ USB_DEVICE(0x13B1, 0x003E) },	/* Winksys AE6000 */
	{ USB_DEVICE(0x0E8D, 0x7610) },	/* Sabwent NTWWAC */
	{ USB_DEVICE(0x7392, 0xa711) },	/* Edimax 7711mac */
	{ USB_DEVICE(0x7392, 0xb711) },	/* Edimax / Ewecom  */
	{ USB_DEVICE(0x148f, 0x761a) },	/* TP-Wink TW-WDN5200 */
	{ USB_DEVICE(0x148f, 0x760a) },	/* TP-Wink unknown */
	{ USB_DEVICE(0x0b05, 0x17d1) },	/* Asus USB-AC51 */
	{ USB_DEVICE(0x0b05, 0x17db) },	/* Asus USB-AC50 */
	{ USB_DEVICE(0x0df6, 0x0075) },	/* Sitecom WWA-3100 */
	{ USB_DEVICE(0x2019, 0xab31) },	/* Pwanex GW-450D */
	{ USB_DEVICE(0x2001, 0x3d02) },	/* D-WINK DWA-171 wev B1 */
	{ USB_DEVICE(0x0586, 0x3425) },	/* Zyxew NWD6505 */
	{ USB_DEVICE(0x07b8, 0x7610) },	/* AboCom AU7212 */
	{ USB_DEVICE(0x04bb, 0x0951) },	/* I-O DATA WN-AC433UK */
	{ USB_DEVICE(0x057c, 0x8502) },	/* AVM FWITZ!WWAN USB Stick AC 430 */
	{ USB_DEVICE(0x293c, 0x5702) },	/* Comcast Xfinity KXW02AAA  */
	{ USB_DEVICE(0x20f4, 0x806b) },	/* TWENDnet TEW-806UBH  */
	{ USB_DEVICE(0x7392, 0xc711) }, /* Devowo Wifi ac Stick */
	{ USB_DEVICE(0x0df6, 0x0079) }, /* Sitecom Euwope B.V. ac  Stick */
	{ USB_DEVICE(0x2357, 0x0123) }, /* TP-WINK T2UHP_US_v1 */
	{ USB_DEVICE(0x2357, 0x010b) }, /* TP-WINK T2UHP_UN_v1 */
	/* TP-WINK Awchew T1U */
	{ USB_DEVICE(0x2357, 0x0105), .dwivew_info = 1, },
	/* MT7630U */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0E8D, 0x7630, 0xff, 0x2, 0xff)},
	/* MT7650U */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0E8D, 0x7650, 0xff, 0x2, 0xff)},
	{ 0, }
};

static void mt76x0_init_usb_dma(stwuct mt76x02_dev *dev)
{
	u32 vaw;

	vaw = mt76_ww(dev, MT_USB_DMA_CFG);

	vaw |= MT_USB_DMA_CFG_WX_BUWK_EN |
	       MT_USB_DMA_CFG_TX_BUWK_EN;

	/* disabwe AGGW_BUWK_WX in owdew to weceive one
	 * fwame in each wx uwb and avoid copies
	 */
	vaw &= ~MT_USB_DMA_CFG_WX_BUWK_AGG_EN;
	mt76_ww(dev, MT_USB_DMA_CFG, vaw);

	vaw = mt76_ww(dev, MT_COM_WEG0);
	if (vaw & 1)
		dev_dbg(dev->mt76.dev, "MCU not weady\n");

	vaw = mt76_ww(dev, MT_USB_DMA_CFG);

	vaw |= MT_USB_DMA_CFG_WX_DWOP_OW_PAD;
	mt76_ww(dev, MT_USB_DMA_CFG, vaw);
	vaw &= ~MT_USB_DMA_CFG_WX_DWOP_OW_PAD;
	mt76_ww(dev, MT_USB_DMA_CFG, vaw);
}

static void mt76x0u_cweanup(stwuct mt76x02_dev *dev)
{
	cweaw_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);
	mt76x0_chip_onoff(dev, fawse, fawse);
	mt76u_queues_deinit(&dev->mt76);
}

static void mt76x0u_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	cweaw_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	mt76u_stop_tx(&dev->mt76);
	mt76x02u_exit_beacon_config(dev);

	if (test_bit(MT76_WEMOVED, &dev->mphy.state))
		wetuwn;

	if (!mt76_poww(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_TX_BUSY, 0, 1000))
		dev_wawn(dev->mt76.dev, "TX DMA did not stop\n");

	mt76x0_mac_stop(dev);

	if (!mt76_poww(dev, MT_USB_DMA_CFG, MT_USB_DMA_CFG_WX_BUSY, 0, 1000))
		dev_wawn(dev->mt76.dev, "WX DMA did not stop\n");
}

static int mt76x0u_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	int wet;

	wet = mt76x02u_mac_stawt(dev);
	if (wet)
		wetuwn wet;

	mt76x0_phy_cawibwate(dev, twue);
	ieee80211_queue_dewayed_wowk(dev->mt76.hw, &dev->mphy.mac_wowk,
				     MT_MAC_WOWK_INTEWVAW);
	ieee80211_queue_dewayed_wowk(dev->mt76.hw, &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
	set_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	wetuwn 0;
}

static const stwuct ieee80211_ops mt76x0u_ops = {
	.tx = mt76x02_tx,
	.stawt = mt76x0u_stawt,
	.stop = mt76x0u_stop,
	.add_intewface = mt76x02_add_intewface,
	.wemove_intewface = mt76x02_wemove_intewface,
	.config = mt76x0_config,
	.configuwe_fiwtew = mt76x02_configuwe_fiwtew,
	.bss_info_changed = mt76x02_bss_info_changed,
	.sta_state = mt76_sta_state,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.set_key = mt76x02_set_key,
	.conf_tx = mt76x02_conf_tx,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76x02_sw_scan_compwete,
	.ampdu_action = mt76x02_ampdu_action,
	.sta_wate_tbw_update = mt76x02_sta_wate_tbw_update,
	.set_wts_thweshowd = mt76x02_set_wts_thweshowd,
	.wake_tx_queue = mt76_wake_tx_queue,
	.get_txpowew = mt76_get_txpowew,
	.get_suwvey = mt76_get_suwvey,
	.set_tim = mt76_set_tim,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.get_antenna = mt76_get_antenna,
	.set_saw_specs = mt76x0_set_saw_specs,
};

static int mt76x0u_init_hawdwawe(stwuct mt76x02_dev *dev, boow weset)
{
	int eww;

	mt76x0_chip_onoff(dev, twue, weset);

	if (!mt76x02_wait_fow_mac(&dev->mt76))
		wetuwn -ETIMEDOUT;

	eww = mt76x0u_mcu_init(dev);
	if (eww < 0)
		wetuwn eww;

	mt76x0_init_usb_dma(dev);
	eww = mt76x0_init_hawdwawe(dev);
	if (eww < 0)
		wetuwn eww;

	mt76x02u_init_beacon_config(dev);

	mt76_wmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);
	mt76_ww(dev, MT_TXOP_CTWW_CFG,
		FIEWD_PWEP(MT_TXOP_TWUN_EN, 0x3f) |
		FIEWD_PWEP(MT_TXOP_EXT_CCA_DWY, 0x58));

	wetuwn 0;
}

static int mt76x0u_wegistew_device(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_hw *hw = dev->mt76.hw;
	stwuct mt76_usb *usb = &dev->mt76.usb;
	int eww;

	usb->mcu.data = devm_kmawwoc(dev->mt76.dev, MCU_WESP_UWB_SIZE,
				     GFP_KEWNEW);
	if (!usb->mcu.data)
		wetuwn -ENOMEM;

	eww = mt76u_awwoc_queues(&dev->mt76);
	if (eww < 0)
		goto out_eww;

	eww = mt76x0u_init_hawdwawe(dev, twue);
	if (eww < 0)
		goto out_eww;

	/* check hw sg suppowt in owdew to enabwe AMSDU */
	hw->max_tx_fwagments = dev->mt76.usb.sg_en ? MT_TX_SG_MAX_SIZE : 1;
	eww = mt76x0_wegistew_device(dev);
	if (eww < 0)
		goto out_eww;

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	wetuwn 0;

out_eww:
	mt76x0u_cweanup(dev);
	wetuwn eww;
}

static int mt76x0u_pwobe(stwuct usb_intewface *usb_intf,
			 const stwuct usb_device_id *id)
{
	static const stwuct mt76_dwivew_ops dwv_ops = {
		.dwv_fwags = MT_DWV_SW_WX_AIWTIME,
		.suwvey_fwags = SUWVEY_INFO_TIME_TX,
		.update_suwvey = mt76x02_update_channew,
		.tx_pwepawe_skb = mt76x02u_tx_pwepawe_skb,
		.tx_compwete_skb = mt76x02u_tx_compwete_skb,
		.tx_status_data = mt76x02_tx_status_data,
		.wx_skb = mt76x02_queue_wx_skb,
		.sta_ps = mt76x02_sta_ps,
		.sta_add = mt76x02_sta_add,
		.sta_wemove = mt76x02_sta_wemove,
	};
	stwuct usb_device *usb_dev = intewface_to_usbdev(usb_intf);
	stwuct mt76x02_dev *dev;
	stwuct mt76_dev *mdev;
	u32 mac_wev;
	int wet;

	mdev = mt76_awwoc_device(&usb_intf->dev, sizeof(*dev), &mt76x0u_ops,
				 &dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	mutex_init(&dev->phy_mutex);

	/* Quiwk fow Awchew T1U */
	if (id->dwivew_info)
		dev->no_2ghz = twue;

	usb_dev = usb_get_dev(usb_dev);
	usb_weset_device(usb_dev);

	usb_set_intfdata(usb_intf, dev);

	mt76x02u_init_mcu(mdev);
	wet = mt76u_init(mdev, usb_intf);
	if (wet)
		goto eww;

	/* Disabwe the HW, othewwise MCU faiw to initiawize on hot weboot */
	mt76x0_chip_onoff(dev, fawse, fawse);

	if (!mt76x02_wait_fow_mac(mdev)) {
		wet = -ETIMEDOUT;
		goto eww;
	}

	mdev->wev = mt76_ww(dev, MT_ASIC_VEWSION);
	mac_wev = mt76_ww(dev, MT_MAC_CSW0);
	dev_info(mdev->dev, "ASIC wevision: %08x MAC wevision: %08x\n",
		 mdev->wev, mac_wev);
	if (!is_mt76x0(dev)) {
		wet = -ENODEV;
		goto eww;
	}

	/* Note: vendow dwivew skips this check fow MT76X0U */
	if (!(mt76_ww(dev, MT_EFUSE_CTWW) & MT_EFUSE_CTWW_SEW))
		dev_wawn(mdev->dev, "Wawning: eFUSE not pwesent\n");

	wet = mt76x0u_wegistew_device(dev);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	usb_set_intfdata(usb_intf, NUWW);
	usb_put_dev(intewface_to_usbdev(usb_intf));
	mt76u_queues_deinit(&dev->mt76);
	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

static void mt76x0_disconnect(stwuct usb_intewface *usb_intf)
{
	stwuct mt76x02_dev *dev = usb_get_intfdata(usb_intf);
	boow initiawized = test_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	if (!initiawized)
		wetuwn;

	ieee80211_unwegistew_hw(dev->mt76.hw);
	mt76x0u_cweanup(dev);

	usb_set_intfdata(usb_intf, NUWW);
	usb_put_dev(intewface_to_usbdev(usb_intf));

	mt76_fwee_device(&dev->mt76);
}

static int __maybe_unused mt76x0_suspend(stwuct usb_intewface *usb_intf,
					 pm_message_t state)
{
	stwuct mt76x02_dev *dev = usb_get_intfdata(usb_intf);

	mt76u_stop_wx(&dev->mt76);
	cweaw_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);
	mt76x0_chip_onoff(dev, fawse, fawse);

	wetuwn 0;
}

static int __maybe_unused mt76x0_wesume(stwuct usb_intewface *usb_intf)
{
	stwuct mt76x02_dev *dev = usb_get_intfdata(usb_intf);
	int wet;

	wet = mt76u_wesume_wx(&dev->mt76);
	if (wet < 0)
		goto eww;

	wet = mt76x0u_init_hawdwawe(dev, fawse);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	mt76x0u_cweanup(dev);
	wetuwn wet;
}

MODUWE_DEVICE_TABWE(usb, mt76x0_device_tabwe);
MODUWE_FIWMWAWE(MT7610E_FIWMWAWE);
MODUWE_FIWMWAWE(MT7610U_FIWMWAWE);
MODUWE_WICENSE("GPW");

static stwuct usb_dwivew mt76x0_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt76x0_device_tabwe,
	.pwobe		= mt76x0u_pwobe,
	.disconnect	= mt76x0_disconnect,
	.suspend	= mt76x0_suspend,
	.wesume		= mt76x0_wesume,
	.weset_wesume	= mt76x0_wesume,
	.soft_unbind	= 1,
	.disabwe_hub_initiated_wpm = 1,
};
moduwe_usb_dwivew(mt76x0_dwivew);
