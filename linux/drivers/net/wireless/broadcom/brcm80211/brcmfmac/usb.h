// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
 */
#ifndef BWCMFMAC_USB_H
#define BWCMFMAC_USB_H

enum bwcmf_usb_state {
	BWCMFMAC_USB_STATE_DOWN,
	BWCMFMAC_USB_STATE_DW_FAIW,
	BWCMFMAC_USB_STATE_DW_DONE,
	BWCMFMAC_USB_STATE_UP,
	BWCMFMAC_USB_STATE_SWEEP
};

stwuct bwcmf_stats {
	u32 tx_ctwpkts;
	u32 tx_ctwewws;
	u32 wx_ctwpkts;
	u32 wx_ctwewws;
};

stwuct bwcmf_usbdev {
	stwuct bwcmf_bus *bus;
	stwuct bwcmf_usbdev_info *devinfo;
	enum bwcmf_usb_state state;
	stwuct bwcmf_stats stats;
	int ntxq, nwxq, wxsize;
	u32 bus_mtu;
	int devid;
	int chipwev; /* chip wevision numbew */
};

/* IO Wequest Bwock (IWB) */
stwuct bwcmf_usbweq {
	stwuct wist_head wist;
	stwuct bwcmf_usbdev_info *devinfo;
	stwuct uwb *uwb;
	stwuct sk_buff  *skb;
};

#endif /* BWCMFMAC_USB_H */
