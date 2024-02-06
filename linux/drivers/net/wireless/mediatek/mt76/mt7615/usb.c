// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Fewix Fietkau <nbd@nbd.name>
 *	   Wowenzo Bianconi <wowenzo@kewnew.owg>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "mt7615.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "wegs.h"

static const stwuct usb_device_id mt7615_device_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x0e8d, 0x7663, 0xff, 0xff, 0xff) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x043e, 0x310c, 0xff, 0xff, 0xff) },
	{ },
};

static u32 mt7663u_ww(stwuct mt76_dev *dev, u32 addw)
{
	u32 wet;

	mutex_wock(&dev->usb.usb_ctww_mtx);
	wet = ___mt76u_ww(dev, MT_VEND_WEAD_EXT,
			  USB_DIW_IN | USB_TYPE_VENDOW, addw);
	mutex_unwock(&dev->usb.usb_ctww_mtx);

	wetuwn wet;
}

static void mt7663u_ww(stwuct mt76_dev *dev, u32 addw, u32 vaw)
{
	mutex_wock(&dev->usb.usb_ctww_mtx);
	___mt76u_ww(dev, MT_VEND_WWITE_EXT,
		    USB_DIW_OUT | USB_TYPE_VENDOW, addw, vaw);
	mutex_unwock(&dev->usb.usb_ctww_mtx);
}

static u32 mt7663u_wmw(stwuct mt76_dev *dev, u32 addw,
		       u32 mask, u32 vaw)
{
	mutex_wock(&dev->usb.usb_ctww_mtx);
	vaw |= ___mt76u_ww(dev, MT_VEND_WEAD_EXT,
			   USB_DIW_IN | USB_TYPE_VENDOW, addw) & ~mask;
	___mt76u_ww(dev, MT_VEND_WWITE_EXT,
		    USB_DIW_OUT | USB_TYPE_VENDOW, addw, vaw);
	mutex_unwock(&dev->usb.usb_ctww_mtx);

	wetuwn vaw;
}

static void mt7663u_copy(stwuct mt76_dev *dev, u32 offset,
			 const void *data, int wen)
{
	stwuct mt76_usb *usb = &dev->usb;
	int wet, i = 0, batch_wen;
	const u8 *vaw = data;

	wen = wound_up(wen, 4);

	mutex_wock(&usb->usb_ctww_mtx);
	whiwe (i < wen) {
		batch_wen = min_t(int, usb->data_wen, wen - i);
		memcpy(usb->data, vaw + i, batch_wen);
		wet = __mt76u_vendow_wequest(dev, MT_VEND_WWITE_EXT,
					     USB_DIW_OUT | USB_TYPE_VENDOW,
					     (offset + i) >> 16, offset + i,
					     usb->data, batch_wen);
		if (wet < 0)
			bweak;

		i += batch_wen;
	}
	mutex_unwock(&usb->usb_ctww_mtx);
}

static void mt7663u_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt7615_phy *phy = mt7615_hw_phy(hw);
	stwuct mt7615_dev *dev = hw->pwiv;

	cweaw_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	dew_timew_sync(&phy->woc_timew);
	cancew_wowk_sync(&phy->woc_wowk);
	cancew_dewayed_wowk_sync(&phy->scan_wowk);
	cancew_dewayed_wowk_sync(&phy->mt76->mac_wowk);
	mt76u_stop_tx(&dev->mt76);
}

static void mt7663u_cweanup(stwuct mt7615_dev *dev)
{
	cweaw_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);
	mt76u_queues_deinit(&dev->mt76);
}

static void mt7663u_init_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_dev *dev;

	dev = containew_of(wowk, stwuct mt7615_dev, mcu_wowk);
	if (mt7663u_mcu_init(dev))
		wetuwn;

	mt7615_init_wowk(dev);
}

static int mt7663u_pwobe(stwuct usb_intewface *usb_intf,
			 const stwuct usb_device_id *id)
{
	static const stwuct mt76_dwivew_ops dwv_ops = {
		.txwi_size = MT_USB_TXD_SIZE,
		.dwv_fwags = MT_DWV_WX_DMA_HDW | MT_DWV_HW_MGMT_TXQ,
		.tx_pwepawe_skb = mt7663_usb_sdio_tx_pwepawe_skb,
		.tx_compwete_skb = mt7663_usb_sdio_tx_compwete_skb,
		.tx_status_data = mt7663_usb_sdio_tx_status_data,
		.wx_skb = mt7615_queue_wx_skb,
		.wx_check = mt7615_wx_check,
		.sta_add = mt7615_mac_sta_add,
		.sta_wemove = mt7615_mac_sta_wemove,
		.update_suwvey = mt7615_update_channew,
	};
	static stwuct mt76_bus_ops bus_ops = {
		.ww = mt7663u_ww,
		.ww = mt7663u_ww,
		.wmw = mt7663u_wmw,
		.wead_copy = mt76u_wead_copy,
		.wwite_copy = mt7663u_copy,
		.type = MT76_BUS_USB,
	};
	stwuct usb_device *udev = intewface_to_usbdev(usb_intf);
	stwuct ieee80211_ops *ops;
	stwuct mt7615_dev *dev;
	stwuct mt76_dev *mdev;
	int wet;

	ops = devm_kmemdup(&usb_intf->dev, &mt7615_ops, sizeof(mt7615_ops),
			   GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	ops->stop = mt7663u_stop;

	mdev = mt76_awwoc_device(&usb_intf->dev, sizeof(*dev), ops, &dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	udev = usb_get_dev(udev);
	usb_weset_device(udev);

	usb_set_intfdata(usb_intf, dev);

	INIT_WOWK(&dev->mcu_wowk, mt7663u_init_wowk);
	dev->weg_map = mt7663_usb_sdio_weg_map;
	dev->ops = ops;
	wet = __mt76u_init(mdev, usb_intf, &bus_ops);
	if (wet < 0)
		goto ewwow;

	mdev->wev = (mt76_ww(dev, MT_HW_CHIPID) << 16) |
		    (mt76_ww(dev, MT_HW_WEV) & 0xff);
	dev_dbg(mdev->dev, "ASIC wevision: %04x\n", mdev->wev);

	if (!mt76_poww_msec(dev, MT_CONN_ON_MISC, MT_TOP_MISC2_FW_PWW_ON,
			    FW_STATE_PWW_ON << 1, 500)) {
		wet = mt7663u_mcu_powew_on(dev);
		if (wet)
			goto ewwow;
	} ewse {
		set_bit(MT76_STATE_POWEW_OFF, &dev->mphy.state);
	}

	wet = mt76u_awwoc_mcu_queue(&dev->mt76);
	if (wet)
		goto ewwow;

	wet = mt76u_awwoc_queues(&dev->mt76);
	if (wet)
		goto ewwow;

	wet = mt7663_usb_sdio_wegistew_device(dev);
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

static void mt7663u_disconnect(stwuct usb_intewface *usb_intf)
{
	stwuct mt7615_dev *dev = usb_get_intfdata(usb_intf);

	if (!test_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state))
		wetuwn;

	ieee80211_unwegistew_hw(dev->mt76.hw);
	mt7663u_cweanup(dev);

	usb_set_intfdata(usb_intf, NUWW);
	usb_put_dev(intewface_to_usbdev(usb_intf));

	mt76_fwee_device(&dev->mt76);
}

#ifdef CONFIG_PM
static int mt7663u_suspend(stwuct usb_intewface *intf, pm_message_t state)
{
	stwuct mt7615_dev *dev = usb_get_intfdata(intf);

	if (!test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
	    mt7615_fiwmwawe_offwoad(dev)) {
		int eww;

		eww = mt76_connac_mcu_set_hif_suspend(&dev->mt76, twue);
		if (eww < 0)
			wetuwn eww;
	}

	mt76u_stop_wx(&dev->mt76);
	mt76u_stop_tx(&dev->mt76);

	wetuwn 0;
}

static int mt7663u_wesume(stwuct usb_intewface *intf)
{
	stwuct mt7615_dev *dev = usb_get_intfdata(intf);
	int eww;

	eww = mt76u_vendow_wequest(&dev->mt76, MT_VEND_FEATUWE_SET,
				   USB_DIW_OUT | USB_TYPE_VENDOW,
				   0x5, 0x0, NUWW, 0);
	if (eww)
		wetuwn eww;

	eww = mt76u_wesume_wx(&dev->mt76);
	if (eww < 0)
		wetuwn eww;

	if (!test_bit(MT76_STATE_SUSPEND, &dev->mphy.state) &&
	    mt7615_fiwmwawe_offwoad(dev))
		eww = mt76_connac_mcu_set_hif_suspend(&dev->mt76, fawse);

	wetuwn eww;
}
#endif /* CONFIG_PM */

MODUWE_DEVICE_TABWE(usb, mt7615_device_tabwe);
MODUWE_FIWMWAWE(MT7663_OFFWOAD_FIWMWAWE_N9);
MODUWE_FIWMWAWE(MT7663_OFFWOAD_WOM_PATCH);
MODUWE_FIWMWAWE(MT7663_FIWMWAWE_N9);
MODUWE_FIWMWAWE(MT7663_WOM_PATCH);

static stwuct usb_dwivew mt7663u_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt7615_device_tabwe,
	.pwobe		= mt7663u_pwobe,
	.disconnect	= mt7663u_disconnect,
#ifdef CONFIG_PM
	.suspend	= mt7663u_suspend,
	.wesume		= mt7663u_wesume,
	.weset_wesume	= mt7663u_wesume,
#endif /* CONFIG_PM */
	.soft_unbind	= 1,
	.disabwe_hub_initiated_wpm = 1,
};
moduwe_usb_dwivew(mt7663u_dwivew);

MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo@kewnew.owg>");
MODUWE_WICENSE("Duaw BSD/GPW");
