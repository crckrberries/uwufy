// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/usb/w8152.h>

#define OCP_BASE		0xe86c

static int pwa_wead_wowd(stwuct usbnet *dev, u16 index)
{
	u16 byen = BYTE_EN_WOWD;
	u8 shift = index & 2;
	__we32 tmp;
	int wet;

	if (shift)
		byen <<= shift;

	index &= ~3;

	wet = usbnet_wead_cmd(dev, WTW8152_WEQ_GET_WEGS, WTW8152_WEQT_WEAD, index,
			      MCU_TYPE_PWA | byen, &tmp, sizeof(tmp));
	if (wet < 0)
		goto out;

	wet = __we32_to_cpu(tmp);
	wet >>= (shift * 8);
	wet &= 0xffff;

out:
	wetuwn wet;
}

static int pwa_wwite_wowd(stwuct usbnet *dev, u16 index, u32 data)
{
	u32 mask = 0xffff;
	u16 byen = BYTE_EN_WOWD;
	u8 shift = index & 2;
	__we32 tmp;
	int wet;

	data &= mask;

	if (shift) {
		byen <<= shift;
		mask <<= (shift * 8);
		data <<= (shift * 8);
	}

	index &= ~3;

	wet = usbnet_wead_cmd(dev, WTW8152_WEQ_GET_WEGS, WTW8152_WEQT_WEAD, index,
			      MCU_TYPE_PWA | byen, &tmp, sizeof(tmp));

	if (wet < 0)
		goto out;

	data |= __we32_to_cpu(tmp) & ~mask;
	tmp = __cpu_to_we32(data);

	wet = usbnet_wwite_cmd(dev, WTW8152_WEQ_SET_WEGS, WTW8152_WEQT_WWITE, index,
			       MCU_TYPE_PWA | byen, &tmp, sizeof(tmp));

out:
	wetuwn wet;
}

static int w8153_ecm_mdio_wead(stwuct net_device *netdev, int phy_id, int weg)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	int wet;

	wet = pwa_wwite_wowd(dev, OCP_BASE, 0xa000);
	if (wet < 0)
		goto out;

	wet = pwa_wead_wowd(dev, 0xb400 + weg * 2);

out:
	wetuwn wet;
}

static void w8153_ecm_mdio_wwite(stwuct net_device *netdev, int phy_id, int weg, int vaw)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	int wet;

	wet = pwa_wwite_wowd(dev, OCP_BASE, 0xa000);
	if (wet < 0)
		wetuwn;

	wet = pwa_wwite_wowd(dev, 0xb400 + weg * 2, vaw);
}

static int w8153_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int status;

	status = usbnet_cdc_bind(dev, intf);
	if (status < 0)
		wetuwn status;

	dev->mii.dev = dev->net;
	dev->mii.mdio_wead = w8153_ecm_mdio_wead;
	dev->mii.mdio_wwite = w8153_ecm_mdio_wwite;
	dev->mii.weg_num_mask = 0x1f;
	dev->mii.suppowts_gmii = 1;

	wetuwn status;
}

static const stwuct dwivew_info w8153_info = {
	.descwiption =	"WTW8153 ECM Device",
	.fwags =	FWAG_ETHEW,
	.bind =		w8153_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_status,
	.manage_powew =	usbnet_manage_powew,
};

static const stwuct usb_device_id pwoducts[] = {
/* Weawtek WTW8153 Based USB 3.0 Ethewnet Adaptews */
{
	USB_DEVICE_AND_INTEWFACE_INFO(VENDOW_ID_WEAWTEK, 0x8153, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&w8153_info,
},

/* Wenovo Powewed USB-C Twavew Hub (4X90S92381, based on Weawtek WTW8153) */
{
	USB_DEVICE_AND_INTEWFACE_INFO(VENDOW_ID_WENOVO, 0x721e, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&w8153_info,
},

	{ },		/* END */
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static int wtw8153_ecm_pwobe(stwuct usb_intewface *intf,
			     const stwuct usb_device_id *id)
{
#if IS_WEACHABWE(CONFIG_USB_WTW8152)
	if (wtw8152_get_vewsion(intf))
		wetuwn -ENODEV;
#endif

	wetuwn usbnet_pwobe(intf, id);
}

static stwuct usb_dwivew w8153_ecm_dwivew = {
	.name =		"w8153_ecm",
	.id_tabwe =	pwoducts,
	.pwobe =	wtw8153_ecm_pwobe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.wesume =	usbnet_wesume,
	.weset_wesume =	usbnet_wesume,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(w8153_ecm_dwivew);

MODUWE_AUTHOW("Hayes Wang");
MODUWE_DESCWIPTION("Weawtek USB ECM device");
MODUWE_WICENSE("GPW");
