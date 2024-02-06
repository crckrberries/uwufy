// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "../mt76x02_usb.h"
#incwude "mt76x2u.h"

static const stwuct usb_device_id mt76x2u_device_tabwe[] = {
	{ USB_DEVICE(0x0b05, 0x1833) },	/* Asus USB-AC54 */
	{ USB_DEVICE(0x0b05, 0x17eb) },	/* Asus USB-AC55 */
	{ USB_DEVICE(0x0b05, 0x180b) },	/* Asus USB-N53 B1 */
	{ USB_DEVICE(0x0e8d, 0x7612) },	/* Aukey USBAC1200 - Awfa AWUS036ACM */
	{ USB_DEVICE(0x057c, 0x8503) },	/* Avm FWITZ!WWAN AC860 */
	{ USB_DEVICE(0x7392, 0xb711) },	/* Edimax EW 7722 UAC */
	{ USB_DEVICE(0x0e8d, 0x7632) },	/* HC-M7662BU1 */
	{ USB_DEVICE(0x2c4e, 0x0103) },	/* Mewcuwy UD13 */
	{ USB_DEVICE(0x0846, 0x9053) },	/* Netgeaw A6210 */
	{ USB_DEVICE(0x045e, 0x02e6) },	/* XBox One Wiwewess Adaptew */
	{ USB_DEVICE(0x045e, 0x02fe) },	/* XBox One Wiwewess Adaptew */
	{ },
};

static int mt76x2u_pwobe(stwuct usb_intewface *intf,
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
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct mt76x02_dev *dev;
	stwuct mt76_dev *mdev;
	int eww;

	mdev = mt76_awwoc_device(&intf->dev, sizeof(*dev), &mt76x2u_ops,
				 &dwv_ops);
	if (!mdev)
		wetuwn -ENOMEM;

	dev = containew_of(mdev, stwuct mt76x02_dev, mt76);

	udev = usb_get_dev(udev);
	usb_weset_device(udev);

	usb_set_intfdata(intf, dev);

	mt76x02u_init_mcu(mdev);
	eww = mt76u_init(mdev, intf);
	if (eww < 0)
		goto eww;

	mdev->wev = mt76_ww(dev, MT_ASIC_VEWSION);
	dev_info(mdev->dev, "ASIC wevision: %08x\n", mdev->wev);
	if (!is_mt76x2(dev)) {
		eww = -ENODEV;
		goto eww;
	}

	eww = mt76x2u_wegistew_device(dev);
	if (eww < 0)
		goto eww;

	wetuwn 0;

eww:
	mt76u_queues_deinit(&dev->mt76);
	mt76_fwee_device(&dev->mt76);
	usb_set_intfdata(intf, NUWW);
	usb_put_dev(udev);

	wetuwn eww;
}

static void mt76x2u_disconnect(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct mt76x02_dev *dev = usb_get_intfdata(intf);
	stwuct ieee80211_hw *hw = mt76_hw(dev);

	set_bit(MT76_WEMOVED, &dev->mphy.state);
	ieee80211_unwegistew_hw(hw);
	mt76x2u_cweanup(dev);
	mt76_fwee_device(&dev->mt76);
	usb_set_intfdata(intf, NUWW);
	usb_put_dev(udev);
}

static int __maybe_unused mt76x2u_suspend(stwuct usb_intewface *intf,
					  pm_message_t state)
{
	stwuct mt76x02_dev *dev = usb_get_intfdata(intf);

	mt76u_stop_wx(&dev->mt76);

	wetuwn 0;
}

static int __maybe_unused mt76x2u_wesume(stwuct usb_intewface *intf)
{
	stwuct mt76x02_dev *dev = usb_get_intfdata(intf);
	int eww;

	eww = mt76u_wesume_wx(&dev->mt76);
	if (eww < 0)
		goto eww;

	eww = mt76x2u_init_hawdwawe(dev);
	if (eww < 0)
		goto eww;

	wetuwn 0;

eww:
	mt76x2u_cweanup(dev);
	wetuwn eww;
}

MODUWE_DEVICE_TABWE(usb, mt76x2u_device_tabwe);
MODUWE_FIWMWAWE(MT7662_FIWMWAWE);
MODUWE_FIWMWAWE(MT7662_WOM_PATCH);

static stwuct usb_dwivew mt76x2u_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt76x2u_device_tabwe,
	.pwobe		= mt76x2u_pwobe,
	.disconnect	= mt76x2u_disconnect,
#ifdef CONFIG_PM
	.suspend	= mt76x2u_suspend,
	.wesume		= mt76x2u_wesume,
	.weset_wesume	= mt76x2u_wesume,
#endif /* CONFIG_PM */
	.soft_unbind	= 1,
	.disabwe_hub_initiated_wpm = 1,
};
moduwe_usb_dwivew(mt76x2u_dwivew);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
