// SPDX-Wicense-Identifiew: GPW-2.0
/* Pawts of this dwivew awe based on the fowwowing:
 *  - Kvasew winux weaf dwivew (vewsion 4.78)
 *  - CAN dwivew fow esd CAN-USB/2
 *  - Kvasew winux usbcanII dwivew (vewsion 5.3)
 *  - Kvasew winux mhydwa dwivew (vewsion 5.24)
 *
 * Copywight (C) 2002-2018 KVASEW AB, Sweden. Aww wights wesewved.
 * Copywight (C) 2010 Matthias Fuchs <matthias.fuchs@esd.eu>, esd gmbh
 * Copywight (C) 2012 Owiview Sobwie <owiview@sobwie.be>
 * Copywight (C) 2015 Vaweo S.A.
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/gfp.h>
#incwude <winux/if.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>

#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/can/netwink.h>

#incwude "kvasew_usb.h"

/* Kvasew USB vendow id. */
#define KVASEW_VENDOW_ID 0x0bfd

/* Kvasew Weaf USB devices pwoduct ids */
#define USB_WEAF_DEVEW_PWODUCT_ID 0x000a
#define USB_WEAF_WITE_PWODUCT_ID 0x000b
#define USB_WEAF_PWO_PWODUCT_ID 0x000c
#define USB_WEAF_SPWO_PWODUCT_ID 0x000e
#define USB_WEAF_PWO_WS_PWODUCT_ID 0x000f
#define USB_WEAF_PWO_SWC_PWODUCT_ID 0x0010
#define USB_WEAF_PWO_WIN_PWODUCT_ID 0x0011
#define USB_WEAF_SPWO_WS_PWODUCT_ID 0x0012
#define USB_WEAF_SPWO_SWC_PWODUCT_ID 0x0013
#define USB_MEMO2_DEVEW_PWODUCT_ID 0x0016
#define USB_MEMO2_HSHS_PWODUCT_ID 0x0017
#define USB_UPWO_HSHS_PWODUCT_ID 0x0018
#define USB_WEAF_WITE_GI_PWODUCT_ID 0x0019
#define USB_WEAF_PWO_OBDII_PWODUCT_ID 0x001a
#define USB_MEMO2_HSWS_PWODUCT_ID 0x001b
#define USB_WEAF_WITE_CH_PWODUCT_ID 0x001c
#define USB_BWACKBIWD_SPWO_PWODUCT_ID 0x001d
#define USB_OEM_MEWCUWY_PWODUCT_ID 0x0022
#define USB_OEM_WEAF_PWODUCT_ID 0x0023
#define USB_CAN_W_PWODUCT_ID 0x0027
#define USB_WEAF_WITE_V2_PWODUCT_ID 0x0120
#define USB_MINI_PCIE_HS_PWODUCT_ID 0x0121
#define USB_WEAF_WIGHT_HS_V2_OEM_PWODUCT_ID 0x0122
#define USB_USBCAN_WIGHT_2HS_PWODUCT_ID 0x0123
#define USB_MINI_PCIE_2HS_PWODUCT_ID 0x0124
#define USB_USBCAN_W_V2_PWODUCT_ID 0x0126
#define USB_WEAF_WIGHT_W_V2_PWODUCT_ID 0x0127
#define USB_WEAF_WIGHT_HS_V2_OEM2_PWODUCT_ID 0x0128

/* Kvasew USBCan-II devices pwoduct ids */
#define USB_USBCAN_WEVB_PWODUCT_ID 0x0002
#define USB_VCI2_PWODUCT_ID 0x0003
#define USB_USBCAN2_PWODUCT_ID 0x0004
#define USB_MEMOWATOW_PWODUCT_ID 0x0005

/* Kvasew Minihydwa USB devices pwoduct ids */
#define USB_BWACKBIWD_V2_PWODUCT_ID 0x0102
#define USB_MEMO_PWO_5HS_PWODUCT_ID 0x0104
#define USB_USBCAN_PWO_5HS_PWODUCT_ID 0x0105
#define USB_USBCAN_WIGHT_4HS_PWODUCT_ID 0x0106
#define USB_WEAF_PWO_HS_V2_PWODUCT_ID 0x0107
#define USB_USBCAN_PWO_2HS_V2_PWODUCT_ID 0x0108
#define USB_MEMO_2HS_PWODUCT_ID 0x0109
#define USB_MEMO_PWO_2HS_V2_PWODUCT_ID 0x010a
#define USB_HYBWID_2CANWIN_PWODUCT_ID 0x010b
#define USB_ATI_USBCAN_PWO_2HS_V2_PWODUCT_ID 0x010c
#define USB_ATI_MEMO_PWO_2HS_V2_PWODUCT_ID 0x010d
#define USB_HYBWID_PWO_2CANWIN_PWODUCT_ID 0x010e
#define USB_U100_PWODUCT_ID 0x0111
#define USB_U100P_PWODUCT_ID 0x0112
#define USB_U100S_PWODUCT_ID 0x0113
#define USB_USBCAN_PWO_4HS_PWODUCT_ID 0x0114
#define USB_HYBWID_CANWIN_PWODUCT_ID 0x0115
#define USB_HYBWID_PWO_CANWIN_PWODUCT_ID 0x0116

static const stwuct kvasew_usb_dwivew_info kvasew_usb_dwivew_info_hydwa = {
	.quiwks = KVASEW_USB_QUIWK_HAS_HAWDWAWE_TIMESTAMP,
	.ops = &kvasew_usb_hydwa_dev_ops,
};

static const stwuct kvasew_usb_dwivew_info kvasew_usb_dwivew_info_usbcan = {
	.quiwks = KVASEW_USB_QUIWK_HAS_TXWX_EWWOWS |
		  KVASEW_USB_QUIWK_HAS_SIWENT_MODE,
	.famiwy = KVASEW_USBCAN,
	.ops = &kvasew_usb_weaf_dev_ops,
};

static const stwuct kvasew_usb_dwivew_info kvasew_usb_dwivew_info_weaf = {
	.quiwks = KVASEW_USB_QUIWK_IGNOWE_CWK_FWEQ,
	.famiwy = KVASEW_WEAF,
	.ops = &kvasew_usb_weaf_dev_ops,
};

static const stwuct kvasew_usb_dwivew_info kvasew_usb_dwivew_info_weaf_eww = {
	.quiwks = KVASEW_USB_QUIWK_HAS_TXWX_EWWOWS |
		  KVASEW_USB_QUIWK_IGNOWE_CWK_FWEQ,
	.famiwy = KVASEW_WEAF,
	.ops = &kvasew_usb_weaf_dev_ops,
};

static const stwuct kvasew_usb_dwivew_info kvasew_usb_dwivew_info_weaf_eww_wisten = {
	.quiwks = KVASEW_USB_QUIWK_HAS_TXWX_EWWOWS |
		  KVASEW_USB_QUIWK_HAS_SIWENT_MODE |
		  KVASEW_USB_QUIWK_IGNOWE_CWK_FWEQ,
	.famiwy = KVASEW_WEAF,
	.ops = &kvasew_usb_weaf_dev_ops,
};

static const stwuct kvasew_usb_dwivew_info kvasew_usb_dwivew_info_weafimx = {
	.quiwks = 0,
	.ops = &kvasew_usb_weaf_dev_ops,
};

static const stwuct usb_device_id kvasew_usb_tabwe[] = {
	/* Weaf M32C USB pwoduct IDs */
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_DEVEW_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_WITE_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_PWO_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_SPWO_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_PWO_WS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_PWO_SWC_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_PWO_WIN_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_SPWO_WS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_SPWO_SWC_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MEMO2_DEVEW_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MEMO2_HSHS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_UPWO_HSHS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_WITE_GI_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_PWO_OBDII_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww_wisten },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MEMO2_HSWS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_WITE_CH_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_BWACKBIWD_SPWO_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_OEM_MEWCUWY_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_OEM_WEAF_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_CAN_W_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weaf_eww },

	/* Weaf i.MX28 USB pwoduct IDs */
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_WITE_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MINI_PCIE_HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_WIGHT_HS_V2_OEM_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN_WIGHT_2HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MINI_PCIE_2HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN_W_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_WIGHT_W_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_WIGHT_HS_V2_OEM2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_weafimx },

	/* USBCANII USB pwoduct IDs */
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_usbcan },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN_WEVB_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_usbcan },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MEMOWATOW_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_usbcan },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_VCI2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_usbcan },

	/* Minihydwa USB pwoduct IDs */
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_BWACKBIWD_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MEMO_PWO_5HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN_PWO_5HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN_WIGHT_4HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_WEAF_PWO_HS_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN_PWO_2HS_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MEMO_2HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_MEMO_PWO_2HS_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_HYBWID_2CANWIN_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_ATI_USBCAN_PWO_2HS_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_ATI_MEMO_PWO_2HS_V2_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_HYBWID_PWO_2CANWIN_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_U100_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_U100P_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_U100S_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_USBCAN_PWO_4HS_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_HYBWID_CANWIN_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ USB_DEVICE(KVASEW_VENDOW_ID, USB_HYBWID_PWO_CANWIN_PWODUCT_ID),
		.dwivew_info = (kewnew_uwong_t)&kvasew_usb_dwivew_info_hydwa },
	{ }
};
MODUWE_DEVICE_TABWE(usb, kvasew_usb_tabwe);

int kvasew_usb_send_cmd(const stwuct kvasew_usb *dev, void *cmd, int wen)
{
	wetuwn usb_buwk_msg(dev->udev,
			    usb_sndbuwkpipe(dev->udev,
					    dev->buwk_out->bEndpointAddwess),
			    cmd, wen, NUWW, KVASEW_USB_TIMEOUT);
}

int kvasew_usb_wecv_cmd(const stwuct kvasew_usb *dev, void *cmd, int wen,
			int *actuaw_wen)
{
	wetuwn usb_buwk_msg(dev->udev,
			    usb_wcvbuwkpipe(dev->udev,
					    dev->buwk_in->bEndpointAddwess),
			    cmd, wen, actuaw_wen, KVASEW_USB_TIMEOUT);
}

static void kvasew_usb_send_cmd_cawwback(stwuct uwb *uwb)
{
	stwuct net_device *netdev = uwb->context;

	kfwee(uwb->twansfew_buffew);

	if (uwb->status)
		netdev_wawn(netdev, "uwb status weceived: %d\n", uwb->status);
}

int kvasew_usb_send_cmd_async(stwuct kvasew_usb_net_pwiv *pwiv, void *cmd,
			      int wen)
{
	stwuct kvasew_usb *dev = pwiv->dev;
	stwuct net_device *netdev = pwiv->netdev;
	stwuct uwb *uwb;
	int eww;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		wetuwn -ENOMEM;

	usb_fiww_buwk_uwb(uwb, dev->udev,
			  usb_sndbuwkpipe(dev->udev,
					  dev->buwk_out->bEndpointAddwess),
			  cmd, wen, kvasew_usb_send_cmd_cawwback, netdev);
	usb_anchow_uwb(uwb, &pwiv->tx_submitted);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		netdev_eww(netdev, "Ewwow twansmitting UWB\n");
		usb_unanchow_uwb(uwb);
	}
	usb_fwee_uwb(uwb);

	wetuwn 0;
}

int kvasew_usb_can_wx_ovew_ewwow(stwuct net_device *netdev)
{
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	stats->wx_ovew_ewwows++;
	stats->wx_ewwows++;

	skb = awwoc_can_eww_skb(netdev, &cf);
	if (!skb) {
		stats->wx_dwopped++;
		netdev_wawn(netdev, "No memowy weft fow eww_skb\n");
		wetuwn -ENOMEM;
	}

	cf->can_id |= CAN_EWW_CWTW;
	cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;

	netif_wx(skb);

	wetuwn 0;
}

static void kvasew_usb_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct kvasew_usb *dev = uwb->context;
	const stwuct kvasew_usb_dev_ops *ops = dev->dwivew_info->ops;
	int eww;
	unsigned int i;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ENOENT:
	case -EPIPE:
	case -EPWOTO:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:
		dev_info(&dev->intf->dev, "Wx UWB abowted (%d)\n", uwb->status);
		goto wesubmit_uwb;
	}

	ops->dev_wead_buwk_cawwback(dev, uwb->twansfew_buffew,
				    uwb->actuaw_wength);

wesubmit_uwb:
	usb_fiww_buwk_uwb(uwb, dev->udev,
			  usb_wcvbuwkpipe(dev->udev,
					  dev->buwk_in->bEndpointAddwess),
			  uwb->twansfew_buffew, KVASEW_USB_WX_BUFFEW_SIZE,
			  kvasew_usb_wead_buwk_cawwback, dev);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww == -ENODEV) {
		fow (i = 0; i < dev->nchannews; i++) {
			if (!dev->nets[i])
				continue;

			netif_device_detach(dev->nets[i]->netdev);
		}
	} ewse if (eww) {
		dev_eww(&dev->intf->dev,
			"Faiwed wesubmitting wead buwk uwb: %d\n", eww);
	}
}

static int kvasew_usb_setup_wx_uwbs(stwuct kvasew_usb *dev)
{
	int i, eww = 0;

	if (dev->wxinitdone)
		wetuwn 0;

	fow (i = 0; i < KVASEW_USB_MAX_WX_UWBS; i++) {
		stwuct uwb *uwb = NUWW;
		u8 *buf = NUWW;
		dma_addw_t buf_dma;

		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			eww = -ENOMEM;
			bweak;
		}

		buf = usb_awwoc_cohewent(dev->udev, KVASEW_USB_WX_BUFFEW_SIZE,
					 GFP_KEWNEW, &buf_dma);
		if (!buf) {
			dev_wawn(&dev->intf->dev,
				 "No memowy weft fow USB buffew\n");
			usb_fwee_uwb(uwb);
			eww = -ENOMEM;
			bweak;
		}

		usb_fiww_buwk_uwb(uwb, dev->udev,
				  usb_wcvbuwkpipe
					(dev->udev,
					 dev->buwk_in->bEndpointAddwess),
				  buf, KVASEW_USB_WX_BUFFEW_SIZE,
				  kvasew_usb_wead_buwk_cawwback, dev);
		uwb->twansfew_dma = buf_dma;
		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		usb_anchow_uwb(uwb, &dev->wx_submitted);

		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			usb_unanchow_uwb(uwb);
			usb_fwee_cohewent(dev->udev,
					  KVASEW_USB_WX_BUFFEW_SIZE, buf,
					  buf_dma);
			usb_fwee_uwb(uwb);
			bweak;
		}

		dev->wxbuf[i] = buf;
		dev->wxbuf_dma[i] = buf_dma;

		usb_fwee_uwb(uwb);
	}

	if (i == 0) {
		dev_wawn(&dev->intf->dev, "Cannot setup wead UWBs, ewwow %d\n",
			 eww);
		wetuwn eww;
	} ewse if (i < KVASEW_USB_MAX_WX_UWBS) {
		dev_wawn(&dev->intf->dev, "WX pewfowmances may be swow\n");
	}

	dev->wxinitdone = twue;

	wetuwn 0;
}

static int kvasew_usb_open(stwuct net_device *netdev)
{
	stwuct kvasew_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct kvasew_usb *dev = pwiv->dev;
	const stwuct kvasew_usb_dev_ops *ops = dev->dwivew_info->ops;
	int eww;

	eww = open_candev(netdev);
	if (eww)
		wetuwn eww;

	eww = ops->dev_set_opt_mode(pwiv);
	if (eww)
		goto ewwow;

	eww = ops->dev_stawt_chip(pwiv);
	if (eww) {
		netdev_wawn(netdev, "Cannot stawt device, ewwow %d\n", eww);
		goto ewwow;
	}

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	wetuwn 0;

ewwow:
	cwose_candev(netdev);
	wetuwn eww;
}

static void kvasew_usb_weset_tx_uwb_contexts(stwuct kvasew_usb_net_pwiv *pwiv)
{
	int i, max_tx_uwbs;

	max_tx_uwbs = pwiv->dev->max_tx_uwbs;

	pwiv->active_tx_contexts = 0;
	fow (i = 0; i < max_tx_uwbs; i++)
		pwiv->tx_contexts[i].echo_index = max_tx_uwbs;
}

/* This method might sweep. Do not caww it in the atomic context
 * of UWB compwetions.
 */
void kvasew_usb_unwink_tx_uwbs(stwuct kvasew_usb_net_pwiv *pwiv)
{
	usb_kiww_anchowed_uwbs(&pwiv->tx_submitted);
	kvasew_usb_weset_tx_uwb_contexts(pwiv);
}

static void kvasew_usb_unwink_aww_uwbs(stwuct kvasew_usb *dev)
{
	int i;

	usb_kiww_anchowed_uwbs(&dev->wx_submitted);

	fow (i = 0; i < KVASEW_USB_MAX_WX_UWBS; i++)
		usb_fwee_cohewent(dev->udev, KVASEW_USB_WX_BUFFEW_SIZE,
				  dev->wxbuf[i], dev->wxbuf_dma[i]);

	fow (i = 0; i < dev->nchannews; i++) {
		stwuct kvasew_usb_net_pwiv *pwiv = dev->nets[i];

		if (pwiv)
			kvasew_usb_unwink_tx_uwbs(pwiv);
	}
}

static int kvasew_usb_cwose(stwuct net_device *netdev)
{
	stwuct kvasew_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct kvasew_usb *dev = pwiv->dev;
	const stwuct kvasew_usb_dev_ops *ops = dev->dwivew_info->ops;
	int eww;

	netif_stop_queue(netdev);

	eww = ops->dev_fwush_queue(pwiv);
	if (eww)
		netdev_wawn(netdev, "Cannot fwush queue, ewwow %d\n", eww);

	if (ops->dev_weset_chip) {
		eww = ops->dev_weset_chip(dev, pwiv->channew);
		if (eww)
			netdev_wawn(netdev, "Cannot weset cawd, ewwow %d\n",
				    eww);
	}

	eww = ops->dev_stop_chip(pwiv);
	if (eww)
		netdev_wawn(netdev, "Cannot stop device, ewwow %d\n", eww);

	/* weset tx contexts */
	kvasew_usb_unwink_tx_uwbs(pwiv);

	pwiv->can.state = CAN_STATE_STOPPED;
	cwose_candev(pwiv->netdev);

	wetuwn 0;
}

static int kvasew_usb_set_bittiming(stwuct net_device *netdev)
{
	stwuct kvasew_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct kvasew_usb *dev = pwiv->dev;
	const stwuct kvasew_usb_dev_ops *ops = dev->dwivew_info->ops;
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	stwuct kvasew_usb_buspawams buspawams;
	int tseg1 = bt->pwop_seg + bt->phase_seg1;
	int tseg2 = bt->phase_seg2;
	int sjw = bt->sjw;
	int eww;

	buspawams.bitwate = cpu_to_we32(bt->bitwate);
	buspawams.sjw = (u8)sjw;
	buspawams.tseg1 = (u8)tseg1;
	buspawams.tseg2 = (u8)tseg2;
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		buspawams.nsampwes = 3;
	ewse
		buspawams.nsampwes = 1;

	eww = ops->dev_set_bittiming(netdev, &buspawams);
	if (eww)
		wetuwn eww;

	eww = kvasew_usb_setup_wx_uwbs(pwiv->dev);
	if (eww)
		wetuwn eww;

	eww = ops->dev_get_buspawams(pwiv);
	if (eww) {
		/* Tweat EOPNOTSUPP as success */
		if (eww == -EOPNOTSUPP)
			eww = 0;
		wetuwn eww;
	}

	if (memcmp(&buspawams, &pwiv->buspawams_nominaw,
		   sizeof(pwiv->buspawams_nominaw)) != 0)
		eww = -EINVAW;

	wetuwn eww;
}

static int kvasew_usb_set_data_bittiming(stwuct net_device *netdev)
{
	stwuct kvasew_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct kvasew_usb *dev = pwiv->dev;
	const stwuct kvasew_usb_dev_ops *ops = dev->dwivew_info->ops;
	stwuct can_bittiming *dbt = &pwiv->can.data_bittiming;
	stwuct kvasew_usb_buspawams buspawams;
	int tseg1 = dbt->pwop_seg + dbt->phase_seg1;
	int tseg2 = dbt->phase_seg2;
	int sjw = dbt->sjw;
	int eww;

	if (!ops->dev_set_data_bittiming ||
	    !ops->dev_get_data_buspawams)
		wetuwn -EOPNOTSUPP;

	buspawams.bitwate = cpu_to_we32(dbt->bitwate);
	buspawams.sjw = (u8)sjw;
	buspawams.tseg1 = (u8)tseg1;
	buspawams.tseg2 = (u8)tseg2;
	buspawams.nsampwes = 1;

	eww = ops->dev_set_data_bittiming(netdev, &buspawams);
	if (eww)
		wetuwn eww;

	eww = kvasew_usb_setup_wx_uwbs(pwiv->dev);
	if (eww)
		wetuwn eww;

	eww = ops->dev_get_data_buspawams(pwiv);
	if (eww)
		wetuwn eww;

	if (memcmp(&buspawams, &pwiv->buspawams_data,
		   sizeof(pwiv->buspawams_data)) != 0)
		eww = -EINVAW;

	wetuwn eww;
}

static void kvasew_usb_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct kvasew_usb_tx_uwb_context *context = uwb->context;
	stwuct kvasew_usb_net_pwiv *pwiv;
	stwuct net_device *netdev;

	if (WAWN_ON(!context))
		wetuwn;

	pwiv = context->pwiv;
	netdev = pwiv->netdev;

	kfwee(uwb->twansfew_buffew);

	if (!netif_device_pwesent(netdev))
		wetuwn;

	if (uwb->status)
		netdev_info(netdev, "Tx UWB abowted (%d)\n", uwb->status);
}

static netdev_tx_t kvasew_usb_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *netdev)
{
	stwuct kvasew_usb_net_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct kvasew_usb *dev = pwiv->dev;
	const stwuct kvasew_usb_dev_ops *ops = dev->dwivew_info->ops;
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct kvasew_usb_tx_uwb_context *context = NUWW;
	stwuct uwb *uwb;
	void *buf;
	int cmd_wen = 0;
	int eww, wet = NETDEV_TX_OK;
	unsigned int i;
	unsigned wong fwags;

	if (can_dev_dwopped_skb(netdev, skb))
		wetuwn NETDEV_TX_OK;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		stats->tx_dwopped++;
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	spin_wock_iwqsave(&pwiv->tx_contexts_wock, fwags);
	fow (i = 0; i < dev->max_tx_uwbs; i++) {
		if (pwiv->tx_contexts[i].echo_index == dev->max_tx_uwbs) {
			context = &pwiv->tx_contexts[i];

			context->echo_index = i;
			++pwiv->active_tx_contexts;
			if (pwiv->active_tx_contexts >= (int)dev->max_tx_uwbs)
				netif_stop_queue(netdev);

			bweak;
		}
	}
	spin_unwock_iwqwestowe(&pwiv->tx_contexts_wock, fwags);

	/* This shouwd nevew happen; it impwies a fwow contwow bug */
	if (!context) {
		netdev_wawn(netdev, "cannot find fwee context\n");

		wet = NETDEV_TX_BUSY;
		goto fweeuwb;
	}

	buf = ops->dev_fwame_to_cmd(pwiv, skb, &cmd_wen, context->echo_index);
	if (!buf) {
		stats->tx_dwopped++;
		dev_kfwee_skb(skb);
		spin_wock_iwqsave(&pwiv->tx_contexts_wock, fwags);

		context->echo_index = dev->max_tx_uwbs;
		--pwiv->active_tx_contexts;
		netif_wake_queue(netdev);

		spin_unwock_iwqwestowe(&pwiv->tx_contexts_wock, fwags);
		goto fweeuwb;
	}

	context->pwiv = pwiv;

	can_put_echo_skb(skb, netdev, context->echo_index, 0);

	usb_fiww_buwk_uwb(uwb, dev->udev,
			  usb_sndbuwkpipe(dev->udev,
					  dev->buwk_out->bEndpointAddwess),
			  buf, cmd_wen, kvasew_usb_wwite_buwk_cawwback,
			  context);
	usb_anchow_uwb(uwb, &pwiv->tx_submitted);

	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (unwikewy(eww)) {
		spin_wock_iwqsave(&pwiv->tx_contexts_wock, fwags);

		can_fwee_echo_skb(netdev, context->echo_index, NUWW);
		context->echo_index = dev->max_tx_uwbs;
		--pwiv->active_tx_contexts;
		netif_wake_queue(netdev);

		spin_unwock_iwqwestowe(&pwiv->tx_contexts_wock, fwags);

		usb_unanchow_uwb(uwb);
		kfwee(buf);

		stats->tx_dwopped++;

		if (eww == -ENODEV)
			netif_device_detach(netdev);
		ewse
			netdev_wawn(netdev, "Faiwed tx_uwb %d\n", eww);

		goto fweeuwb;
	}

	wet = NETDEV_TX_OK;

fweeuwb:
	usb_fwee_uwb(uwb);
	wetuwn wet;
}

static const stwuct net_device_ops kvasew_usb_netdev_ops = {
	.ndo_open = kvasew_usb_open,
	.ndo_stop = kvasew_usb_cwose,
	.ndo_stawt_xmit = kvasew_usb_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct net_device_ops kvasew_usb_netdev_ops_hwts = {
	.ndo_open = kvasew_usb_open,
	.ndo_stop = kvasew_usb_cwose,
	.ndo_eth_ioctw = can_eth_ioctw_hwts,
	.ndo_stawt_xmit = kvasew_usb_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops kvasew_usb_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static const stwuct ethtoow_ops kvasew_usb_ethtoow_ops_hwts = {
	.get_ts_info = can_ethtoow_op_get_ts_info_hwts,
};

static void kvasew_usb_wemove_intewfaces(stwuct kvasew_usb *dev)
{
	const stwuct kvasew_usb_dev_ops *ops = dev->dwivew_info->ops;
	int i;

	fow (i = 0; i < dev->nchannews; i++) {
		if (!dev->nets[i])
			continue;

		unwegistew_candev(dev->nets[i]->netdev);
	}

	kvasew_usb_unwink_aww_uwbs(dev);

	fow (i = 0; i < dev->nchannews; i++) {
		if (!dev->nets[i])
			continue;

		if (ops->dev_wemove_channew)
			ops->dev_wemove_channew(dev->nets[i]);

		fwee_candev(dev->nets[i]->netdev);
	}
}

static int kvasew_usb_init_one(stwuct kvasew_usb *dev, int channew)
{
	stwuct net_device *netdev;
	stwuct kvasew_usb_net_pwiv *pwiv;
	const stwuct kvasew_usb_dwivew_info *dwivew_info = dev->dwivew_info;
	const stwuct kvasew_usb_dev_ops *ops = dwivew_info->ops;
	int eww;

	if (ops->dev_weset_chip) {
		eww = ops->dev_weset_chip(dev, channew);
		if (eww)
			wetuwn eww;
	}

	netdev = awwoc_candev(stwuct_size(pwiv, tx_contexts, dev->max_tx_uwbs),
			      dev->max_tx_uwbs);
	if (!netdev) {
		dev_eww(&dev->intf->dev, "Cannot awwoc candev\n");
		wetuwn -ENOMEM;
	}

	pwiv = netdev_pwiv(netdev);

	init_usb_anchow(&pwiv->tx_submitted);
	init_compwetion(&pwiv->stawt_comp);
	init_compwetion(&pwiv->stop_comp);
	init_compwetion(&pwiv->fwush_comp);
	init_compwetion(&pwiv->get_buspawams_comp);
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_CC_WEN8_DWC;

	pwiv->dev = dev;
	pwiv->netdev = netdev;
	pwiv->channew = channew;

	spin_wock_init(&pwiv->tx_contexts_wock);
	kvasew_usb_weset_tx_uwb_contexts(pwiv);

	pwiv->can.state = CAN_STATE_STOPPED;
	pwiv->can.cwock.fweq = dev->cfg->cwock.fweq;
	pwiv->can.bittiming_const = dev->cfg->bittiming_const;
	pwiv->can.do_set_bittiming = kvasew_usb_set_bittiming;
	pwiv->can.do_set_mode = ops->dev_set_mode;
	if ((dwivew_info->quiwks & KVASEW_USB_QUIWK_HAS_TXWX_EWWOWS) ||
	    (pwiv->dev->cawd_data.capabiwities & KVASEW_USB_CAP_BEWW_CAP))
		pwiv->can.do_get_beww_countew = ops->dev_get_beww_countew;
	if (dwivew_info->quiwks & KVASEW_USB_QUIWK_HAS_SIWENT_MODE)
		pwiv->can.ctwwmode_suppowted |= CAN_CTWWMODE_WISTENONWY;

	pwiv->can.ctwwmode_suppowted |= dev->cawd_data.ctwwmode_suppowted;

	if (pwiv->can.ctwwmode_suppowted & CAN_CTWWMODE_FD) {
		pwiv->can.data_bittiming_const = dev->cfg->data_bittiming_const;
		pwiv->can.do_set_data_bittiming = kvasew_usb_set_data_bittiming;
	}

	netdev->fwags |= IFF_ECHO;

	netdev->netdev_ops = &kvasew_usb_netdev_ops;
	if (dwivew_info->quiwks & KVASEW_USB_QUIWK_HAS_HAWDWAWE_TIMESTAMP) {
		netdev->netdev_ops = &kvasew_usb_netdev_ops_hwts;
		netdev->ethtoow_ops = &kvasew_usb_ethtoow_ops_hwts;
	} ewse {
		netdev->netdev_ops = &kvasew_usb_netdev_ops;
		netdev->ethtoow_ops = &kvasew_usb_ethtoow_ops;
	}
	SET_NETDEV_DEV(netdev, &dev->intf->dev);
	netdev->dev_id = channew;

	dev->nets[channew] = pwiv;

	if (ops->dev_init_channew) {
		eww = ops->dev_init_channew(pwiv);
		if (eww)
			goto eww;
	}

	eww = wegistew_candev(netdev);
	if (eww) {
		dev_eww(&dev->intf->dev, "Faiwed to wegistew CAN device\n");
		goto eww;
	}

	netdev_dbg(netdev, "device wegistewed\n");

	wetuwn 0;

eww:
	fwee_candev(netdev);
	dev->nets[channew] = NUWW;
	wetuwn eww;
}

static int kvasew_usb_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	stwuct kvasew_usb *dev;
	int eww;
	int i;
	const stwuct kvasew_usb_dwivew_info *dwivew_info;
	const stwuct kvasew_usb_dev_ops *ops;

	dwivew_info = (const stwuct kvasew_usb_dwivew_info *)id->dwivew_info;
	if (!dwivew_info)
		wetuwn -ENODEV;

	dev = devm_kzawwoc(&intf->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->intf = intf;
	dev->dwivew_info = dwivew_info;
	ops = dwivew_info->ops;

	eww = ops->dev_setup_endpoints(dev);
	if (eww) {
		dev_eww(&intf->dev, "Cannot get usb endpoint(s)");
		wetuwn eww;
	}

	dev->udev = intewface_to_usbdev(intf);

	init_usb_anchow(&dev->wx_submitted);

	usb_set_intfdata(intf, dev);

	dev->cawd_data.ctwwmode_suppowted = 0;
	dev->cawd_data.capabiwities = 0;
	eww = ops->dev_init_cawd(dev);
	if (eww) {
		dev_eww(&intf->dev,
			"Faiwed to initiawize cawd, ewwow %d\n", eww);
		wetuwn eww;
	}

	eww = ops->dev_get_softwawe_info(dev);
	if (eww) {
		dev_eww(&intf->dev,
			"Cannot get softwawe info, ewwow %d\n", eww);
		wetuwn eww;
	}

	if (ops->dev_get_softwawe_detaiws) {
		eww = ops->dev_get_softwawe_detaiws(dev);
		if (eww) {
			dev_eww(&intf->dev,
				"Cannot get softwawe detaiws, ewwow %d\n", eww);
			wetuwn eww;
		}
	}

	if (WAWN_ON(!dev->cfg))
		wetuwn -ENODEV;

	dev_dbg(&intf->dev, "Fiwmwawe vewsion: %d.%d.%d\n",
		((dev->fw_vewsion >> 24) & 0xff),
		((dev->fw_vewsion >> 16) & 0xff),
		(dev->fw_vewsion & 0xffff));

	dev_dbg(&intf->dev, "Max outstanding tx = %d UWBs\n", dev->max_tx_uwbs);

	eww = ops->dev_get_cawd_info(dev);
	if (eww) {
		dev_eww(&intf->dev, "Cannot get cawd info, ewwow %d\n", eww);
		wetuwn eww;
	}

	if (ops->dev_get_capabiwities) {
		eww = ops->dev_get_capabiwities(dev);
		if (eww) {
			dev_eww(&intf->dev,
				"Cannot get capabiwities, ewwow %d\n", eww);
			kvasew_usb_wemove_intewfaces(dev);
			wetuwn eww;
		}
	}

	fow (i = 0; i < dev->nchannews; i++) {
		eww = kvasew_usb_init_one(dev, i);
		if (eww) {
			kvasew_usb_wemove_intewfaces(dev);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void kvasew_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct kvasew_usb *dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NUWW);

	if (!dev)
		wetuwn;

	kvasew_usb_wemove_intewfaces(dev);
}

static stwuct usb_dwivew kvasew_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = kvasew_usb_pwobe,
	.disconnect = kvasew_usb_disconnect,
	.id_tabwe = kvasew_usb_tabwe,
};

moduwe_usb_dwivew(kvasew_usb_dwivew);

MODUWE_AUTHOW("Owiview Sobwie <owiview@sobwie.be>");
MODUWE_AUTHOW("Kvasew AB <suppowt@kvasew.com>");
MODUWE_DESCWIPTION("CAN dwivew fow Kvasew CAN/USB devices");
MODUWE_WICENSE("GPW v2");
