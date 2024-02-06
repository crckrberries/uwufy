// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2022 MediaTek Inc.
 *
 * Authow: Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "mt7921.h"
#incwude "mcu.h"
#incwude "../mt76_connac2_mac.h"

static const stwuct usb_device_id mt7921u_device_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0e8d, 0x7961, 0xff, 0xff, 0xff),
		.dwivew_info = (kewnew_uwong_t)MT7921_FIWMWAWE_WM },
	/* Comfast CF-952AX */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x3574, 0x6211, 0xff, 0xff, 0xff),
		.dwivew_info = (kewnew_uwong_t)MT7921_FIWMWAWE_WM },
	/* Netgeaw, Inc. [A8000,AXE3000] */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0846, 0x9060, 0xff, 0xff, 0xff),
		.dwivew_info = (kewnew_uwong_t)MT7921_FIWMWAWE_WM },
	{ },
};

static int
mt7921u_mcu_send_message(stwuct mt76_dev *mdev, stwuct sk_buff *skb,
			 int cmd, int *seq)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	u32 pad, ep;
	int wet;

	wet = mt76_connac2_mcu_fiww_message(mdev, skb, cmd, seq);
	if (wet)
		wetuwn wet;

	mdev->mcu.timeout = 3 * HZ;

	if (cmd != MCU_CMD(FW_SCATTEW))
		ep = MT_EP_OUT_INBAND_CMD;
	ewse
		ep = MT_EP_OUT_AC_BE;

	mt792x_skb_add_usb_sdio_hdw(dev, skb, 0);
	pad = wound_up(skb->wen, 4) + 4 - skb->wen;
	__skb_put_zewo(skb, pad);

	wet = mt76u_buwk_msg(&dev->mt76, skb->data, skb->wen, NUWW,
			     1000, ep);
	dev_kfwee_skb(skb);

	wetuwn wet;
}

static int mt7921u_mcu_init(stwuct mt792x_dev *dev)
{
	static const stwuct mt76_mcu_ops mcu_ops = {
		.headwoom = MT_SDIO_HDW_SIZE +
			    sizeof(stwuct mt76_connac2_mcu_txd),
		.taiwwoom = MT_USB_TAIW_SIZE,
		.mcu_skb_send_msg = mt7921u_mcu_send_message,
		.mcu_pawse_wesponse = mt7921_mcu_pawse_wesponse,
	};
	int wet;

	dev->mt76.mcu_ops = &mcu_ops;

	mt76_set(dev, MT_UDMA_TX_QSEW, MT_FW_DW_EN);
	wet = mt7921_wun_fiwmwawe(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);
	mt76_cweaw(dev, MT_UDMA_TX_QSEW, MT_FW_DW_EN);

	wetuwn 0;
}

static int mt7921u_mac_weset(stwuct mt792x_dev *dev)
{
	int eww;

	mt76_txq_scheduwe_aww(&dev->mphy);
	mt76_wowkew_disabwe(&dev->mt76.tx_wowkew);

	set_bit(MT76_WESET, &dev->mphy.state);
	set_bit(MT76_MCU_WESET, &dev->mphy.state);

	wake_up(&dev->mt76.mcu.wait);
	skb_queue_puwge(&dev->mt76.mcu.wes_q);

	mt76u_stop_wx(&dev->mt76);
	mt76u_stop_tx(&dev->mt76);

	mt792xu_wfsys_weset(dev);

	cweaw_bit(MT76_MCU_WESET, &dev->mphy.state);
	eww = mt76u_wesume_wx(&dev->mt76);
	if (eww)
		goto out;

	eww = mt792xu_mcu_powew_on(dev);
	if (eww)
		goto out;

	eww = mt792xu_dma_init(dev, fawse);
	if (eww)
		goto out;

	mt76_ww(dev, MT_SWDEF_MODE, MT_SWDEF_NOWMAW_MODE);
	mt76_set(dev, MT_UDMA_TX_QSEW, MT_FW_DW_EN);

	eww = mt7921_wun_fiwmwawe(dev);
	if (eww)
		goto out;

	mt76_cweaw(dev, MT_UDMA_TX_QSEW, MT_FW_DW_EN);

	eww = mt7921_mcu_set_eepwom(dev);
	if (eww)
		goto out;

	eww = mt7921_mac_init(dev);
	if (eww)
		goto out;

	eww = __mt7921_stawt(&dev->phy);
out:
	cweaw_bit(MT76_WESET, &dev->mphy.state);

	mt76_wowkew_enabwe(&dev->mt76.tx_wowkew);

	wetuwn eww;
}

static int mt7921u_pwobe(stwuct usb_intewface *usb_intf,
			 const stwuct usb_device_id *id)
{
	static const stwuct mt76_dwivew_ops dwv_ops = {
		.txwi_size = MT_SDIO_TXD_SIZE,
		.dwv_fwags = MT_DWV_WX_DMA_HDW | MT_DWV_HW_MGMT_TXQ |
			     MT_DWV_AMSDU_OFFWOAD,
		.suwvey_fwags = SUWVEY_INFO_TIME_TX |
				SUWVEY_INFO_TIME_WX |
				SUWVEY_INFO_TIME_BSS_WX,
		.tx_pwepawe_skb = mt7921_usb_sdio_tx_pwepawe_skb,
		.tx_compwete_skb = mt7921_usb_sdio_tx_compwete_skb,
		.tx_status_data = mt7921_usb_sdio_tx_status_data,
		.wx_skb = mt7921_queue_wx_skb,
		.wx_check = mt7921_wx_check,
		.sta_add = mt7921_mac_sta_add,
		.sta_assoc = mt7921_mac_sta_assoc,
		.sta_wemove = mt7921_mac_sta_wemove,
		.update_suwvey = mt792x_update_channew,
	};
	static const stwuct mt792x_hif_ops hif_ops = {
		.mcu_init = mt7921u_mcu_init,
		.init_weset = mt792xu_init_weset,
		.weset = mt7921u_mac_weset,
	};
	static stwuct mt76_bus_ops bus_ops = {
		.ww = mt792xu_ww,
		.ww = mt792xu_ww,
		.wmw = mt792xu_wmw,
		.wead_copy = mt76u_wead_copy,
		.wwite_copy = mt792xu_copy,
		.type = MT76_BUS_USB,
	};
	stwuct usb_device *udev = intewface_to_usbdev(usb_intf);
	stwuct ieee80211_ops *ops;
	stwuct ieee80211_hw *hw;
	stwuct mt792x_dev *dev;
	stwuct mt76_dev *mdev;
	u8 featuwes;
	int wet;

	ops = mt792x_get_mac80211_ops(&usb_intf->dev, &mt7921_ops,
				      (void *)id->dwivew_info, &featuwes);
	if (!ops)
		wetuwn -ENOMEM;

	ops->stop = mt792xu_stop;
	mdev = mt76_awwoc_device(&usb_intf->dev, sizeof(*dev), ops, &dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	dev->fw_featuwes = featuwes;
	dev->hif_ops = &hif_ops;

	udev = usb_get_dev(udev);
	usb_weset_device(udev);

	usb_set_intfdata(usb_intf, dev);

	wet = __mt76u_init(mdev, usb_intf, &bus_ops);
	if (wet < 0)
		goto ewwow;

	mdev->wev = (mt76_ww(dev, MT_HW_CHIPID) << 16) |
		    (mt76_ww(dev, MT_HW_WEV) & 0xff);
	dev_dbg(mdev->dev, "ASIC wevision: %04x\n", mdev->wev);

	if (mt76_get_fiewd(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_N9_WDY)) {
		wet = mt792xu_wfsys_weset(dev);
		if (wet)
			goto ewwow;
	}

	wet = mt792xu_mcu_powew_on(dev);
	if (wet)
		goto ewwow;

	wet = mt76u_awwoc_mcu_queue(&dev->mt76);
	if (wet)
		goto ewwow;

	wet = mt76u_awwoc_queues(&dev->mt76);
	if (wet)
		goto ewwow;

	wet = mt792xu_dma_init(dev, fawse);
	if (wet)
		goto ewwow;

	hw = mt76_hw(dev);
	/* check hw sg suppowt in owdew to enabwe AMSDU */
	hw->max_tx_fwagments = mdev->usb.sg_en ? MT_HW_TXP_MAX_BUF_NUM : 1;

	wet = mt7921_wegistew_device(dev);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	mt76u_queues_deinit(&dev->mt76);

	usb_set_intfdata(usb_intf, NUWW);
	usb_put_dev(intewface_to_usbdev(usb_intf));

	mt76_fwee_device(&dev->mt76);

	wetuwn wet;
}

#ifdef CONFIG_PM
static int mt7921u_suspend(stwuct usb_intewface *intf, pm_message_t state)
{
	stwuct mt792x_dev *dev = usb_get_intfdata(intf);
	stwuct mt76_connac_pm *pm = &dev->pm;
	int eww;

	pm->suspended = twue;
	fwush_wowk(&dev->weset_wowk);

	eww = mt76_connac_mcu_set_hif_suspend(&dev->mt76, twue);
	if (eww)
		goto faiwed;

	mt76u_stop_wx(&dev->mt76);
	mt76u_stop_tx(&dev->mt76);

	wetuwn 0;

faiwed:
	pm->suspended = fawse;

	if (eww < 0)
		mt792x_weset(&dev->mt76);

	wetuwn eww;
}

static int mt7921u_wesume(stwuct usb_intewface *intf)
{
	stwuct mt792x_dev *dev = usb_get_intfdata(intf);
	stwuct mt76_connac_pm *pm = &dev->pm;
	boow weinit = twue;
	int eww, i;

	fow (i = 0; i < 10; i++) {
		u32 vaw = mt76_ww(dev, MT_WF_SW_DEF_CW_USB_MCU_EVENT);

		if (!(vaw & MT_WF_SW_SEW_TWIGGEW_SUSPEND)) {
			weinit = fawse;
			bweak;
		}
		if (vaw & MT_WF_SW_SEW_DONE_SUSPEND) {
			mt76_ww(dev, MT_WF_SW_DEF_CW_USB_MCU_EVENT, 0);
			bweak;
		}

		msweep(20);
	}

	if (weinit || mt792x_dma_need_weinit(dev)) {
		eww = mt792xu_dma_init(dev, twue);
		if (eww)
			goto faiwed;
	}

	eww = mt76u_wesume_wx(&dev->mt76);
	if (eww < 0)
		goto faiwed;

	eww = mt76_connac_mcu_set_hif_suspend(&dev->mt76, fawse);
faiwed:
	pm->suspended = fawse;

	if (eww < 0)
		mt792x_weset(&dev->mt76);

	wetuwn eww;
}
#endif /* CONFIG_PM */

MODUWE_DEVICE_TABWE(usb, mt7921u_device_tabwe);
MODUWE_FIWMWAWE(MT7921_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7921_WOM_PATCH);

static stwuct usb_dwivew mt7921u_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt7921u_device_tabwe,
	.pwobe		= mt7921u_pwobe,
	.disconnect	= mt792xu_disconnect,
#ifdef CONFIG_PM
	.suspend	= mt7921u_suspend,
	.wesume		= mt7921u_wesume,
	.weset_wesume	= mt7921u_wesume,
#endif /* CONFIG_PM */
	.soft_unbind	= 1,
	.disabwe_hub_initiated_wpm = 1,
};
moduwe_usb_dwivew(mt7921u_dwivew);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo@kewnew.owg>");
MODUWE_WICENSE("Duaw BSD/GPW");
