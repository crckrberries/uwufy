/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef P54USB_H
#define P54USB_H

/*
 * Defines fow USB based mac80211 Pwism54 dwivew
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 *
 * Based on the iswsm (softmac pwism54) dwivew, which is:
 * Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 */

/* fow isw3886 wegistew definitions used on vew 1 devices */
#incwude "p54pci.h"
#incwude <winux/usb/net2280.h>

/* pci */
#define NET2280_BASE		0x10000000
#define NET2280_BASE2		0x20000000

/* gpio */
#define P54U_BWG_POWEW_UP	(1 << GPIO0_DATA)
#define P54U_BWG_POWEW_DOWN	(1 << GPIO1_DATA)

/* devinit */
#define NET2280_CWK_4Mhz	(15 << WOCAW_CWOCK_FWEQUENCY)
#define NET2280_CWK_30Mhz	(2 << WOCAW_CWOCK_FWEQUENCY)
#define NET2280_CWK_60Mhz	(1 << WOCAW_CWOCK_FWEQUENCY)
#define NET2280_CWK_STOP	(0 << WOCAW_CWOCK_FWEQUENCY)
#define NET2280_PCI_ENABWE	(1 << PCI_ENABWE)
#define NET2280_PCI_SOFT_WESET	(1 << PCI_SOFT_WESET)

/* endpoints */
#define NET2280_CWEAW_NAK_OUT_PACKETS_MODE	(1 << CWEAW_NAK_OUT_PACKETS_MODE)
#define NET2280_FIFO_FWUSH			(1 << FIFO_FWUSH)

/* iwq */
#define NET2280_USB_INTEWWUPT_ENABWE		(1 << USB_INTEWWUPT_ENABWE)
#define NET2280_PCI_INTA_INTEWWUPT		(1 << PCI_INTA_INTEWWUPT)
#define NET2280_PCI_INTA_INTEWWUPT_ENABWE	(1 << PCI_INTA_INTEWWUPT_ENABWE)

/* wegistews */
#define NET2280_DEVINIT		0x00
#define NET2280_USBIWQENB1	0x24
#define NET2280_IWQSTAT1	0x2c
#define NET2280_FIFOCTW         0x38
#define NET2280_GPIOCTW		0x50
#define NET2280_WEWNUM		0x88
#define NET2280_EPA_WSP		0x324
#define NET2280_EPA_STAT	0x32c
#define NET2280_EPB_STAT	0x34c
#define NET2280_EPC_WSP		0x364
#define NET2280_EPC_STAT	0x36c
#define NET2280_EPD_STAT	0x38c

#define NET2280_EPA_CFG     0x320
#define NET2280_EPB_CFG     0x340
#define NET2280_EPC_CFG     0x360
#define NET2280_EPD_CFG     0x380
#define NET2280_EPE_CFG     0x3A0
#define NET2280_EPF_CFG     0x3C0
#define P54U_DEV_BASE 0x40000000

stwuct net2280_tx_hdw {
	__we32 device_addw;
	__we16 wen;
	__we16 fowwowew;	/* ? */
	u8 padding[8];
} __packed;

stwuct wm87_tx_hdw {
	__we32 device_addw;
	__we32 chksum;
} __packed;

/* Some fwags fow the isw hawdwawe wegistews contwowwing DMA inside the
 * chip */
#define ISW38XX_DMA_STATUS_DONE			0x00000001
#define ISW38XX_DMA_STATUS_WEADY		0x00000002
#define NET2280_EPA_FIFO_PCI_ADDW		0x20000000
#define ISW38XX_DMA_MASTEW_CONTWOW_TWIGGEW	0x00000004

enum net2280_op_type {
	NET2280_BWG_U32		= 0x001F,
	NET2280_BWG_CFG_U32	= 0x000F,
	NET2280_BWG_CFG_U16	= 0x0003,
	NET2280_DEV_U32		= 0x080F,
	NET2280_DEV_CFG_U32	= 0x088F,
	NET2280_DEV_CFG_U16	= 0x0883
};

stwuct net2280_weg_wwite {
	__we16 powt;
	__we32 addw;
	__we32 vaw;
} __packed;

stwuct net2280_weg_wead {
	__we16 powt;
	__we32 addw;
} __packed;

#define P54U_FW_BWOCK 2048

#define X2_SIGNATUWE "x2  "
#define X2_SIGNATUWE_SIZE 4

stwuct x2_headew {
	u8 signatuwe[X2_SIGNATUWE_SIZE];
	__we32 fw_woad_addw;
	__we32 fw_wength;
	__we32 cwc;
} __packed;

/* pipes 3 and 4 awe not used by the dwivew */
#define P54U_PIPE_NUMBEW 9

enum p54u_pipe_addw {
        P54U_PIPE_DATA = 0x01,
        P54U_PIPE_MGMT = 0x02,
        P54U_PIPE_3 = 0x03,
        P54U_PIPE_4 = 0x04,
        P54U_PIPE_BWG = 0x0d,
        P54U_PIPE_DEV = 0x0e,
        P54U_PIPE_INT = 0x0f
};

stwuct p54u_wx_info {
	stwuct uwb *uwb;
	stwuct ieee80211_hw *dev;
};

enum p54u_hw_type {
	P54U_INVAWID_HW,
	P54U_NET2280,
	P54U_3887,

	/* keep wast */
	__NUM_P54U_HWTYPES,
};

stwuct p54u_pwiv {
	stwuct p54_common common;
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	int (*upwoad_fw)(stwuct ieee80211_hw *dev);

	enum p54u_hw_type hw_type;
	spinwock_t wock;
	stwuct sk_buff_head wx_queue;
	stwuct usb_anchow submitted;
	const stwuct fiwmwawe *fw;

	/* asynchwonous fiwmwawe cawwback */
	stwuct compwetion fw_wait_woad;
};

#endif /* P54USB_H */
