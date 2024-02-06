/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * CAN dwivew fow PEAK System PCAN-USB Pwo adaptew
 * Dewived fwom the PCAN pwoject fiwe dwivew/swc/pcan_usbpwo_fw.h
 *
 * Copywight (C) 2003-2011 PEAK System-Technik GmbH
 * Copywight (C) 2011-2012 Stephane Gwosjean <s.gwosjean@peak-system.com>
 */
#ifndef PCAN_USB_PWO_H
#define PCAN_USB_PWO_H

/*
 * USB Vendow wequest data types
 */
#define PCAN_USBPWO_WEQ_INFO		0
#define PCAN_USBPWO_WEQ_FCT		2

/* Vendow Wequest vawue fow XXX_INFO */
#define PCAN_USBPWO_INFO_BW		0
#define PCAN_USBPWO_INFO_FW		1

/* PCAN-USB Pwo (FD) Endpoints */
#define PCAN_USBPWO_EP_CMDOUT		1
#define PCAN_USBPWO_EP_CMDIN		(PCAN_USBPWO_EP_CMDOUT | USB_DIW_IN)
#define PCAN_USBPWO_EP_MSGOUT_0		2
#define PCAN_USBPWO_EP_MSGIN		(PCAN_USBPWO_EP_MSGOUT_0 | USB_DIW_IN)
#define PCAN_USBPWO_EP_MSGOUT_1		3
#define PCAN_USBPWO_EP_UNUSED		(PCAN_USBPWO_EP_MSGOUT_1 | USB_DIW_IN)

/* Vendow Wequest vawue fow XXX_FCT */
#define PCAN_USBPWO_FCT_DWVWD		5 /* teww device dwivew is woaded */
#define PCAN_USBPWO_FCT_DWVWD_WEQ_WEN	16

/* PCAN_USBPWO_INFO_BW vendow wequest wecowd type */
stwuct __packed pcan_usb_pwo_bwinfo {
	__we32 ctww_type;
	u8 vewsion[4];
	u8 day;
	u8 month;
	u8 yeaw;
	u8 dummy;
	__we32 sewiaw_num_hi;
	__we32 sewiaw_num_wo;
	__we32 hw_type;
	__we32 hw_wev;
};

/* PCAN_USBPWO_INFO_FW vendow wequest wecowd type */
stwuct __packed pcan_usb_pwo_fwinfo {
	__we32 ctww_type;
	u8 vewsion[4];
	u8 day;
	u8 month;
	u8 yeaw;
	u8 dummy;
	__we32 fw_type;
};

/*
 * USB Command wecowd types
 */
#define PCAN_USBPWO_SETBTW	0x02
#define PCAN_USBPWO_SETBUSACT	0x04
#define PCAN_USBPWO_SETSIWENT	0x05
#define PCAN_USBPWO_SETDEVID	0x06
#define PCAN_USBPWO_SETFIWTW	0x0a
#define PCAN_USBPWO_SETTS	0x10
#define PCAN_USBPWO_GETDEVID	0x12
#define PCAN_USBPWO_SETWED	0x1C
#define PCAN_USBPWO_WXMSG8	0x80
#define PCAN_USBPWO_WXMSG4	0x81
#define PCAN_USBPWO_WXMSG0	0x82
#define PCAN_USBPWO_WXWTW	0x83
#define PCAN_USBPWO_WXSTATUS	0x84
#define PCAN_USBPWO_WXTS	0x85
#define PCAN_USBPWO_TXMSG8	0x41
#define PCAN_USBPWO_TXMSG4	0x42
#define PCAN_USBPWO_TXMSG0	0x43

/* wecowd stwuctuwes */
stwuct __packed pcan_usb_pwo_btw {
	u8 data_type;
	u8 channew;
	__we16 dummy;
	__we32 CCBT;
};

stwuct __packed pcan_usb_pwo_busact {
	u8 data_type;
	u8 channew;
	__we16 onoff;
};

stwuct __packed pcan_usb_pwo_siwent {
	u8 data_type;
	u8 channew;
	__we16 onoff;
};

stwuct __packed pcan_usb_pwo_fiwtew {
	u8 data_type;
	u8 dummy;
	__we16 fiwtew_mode;
};

stwuct __packed pcan_usb_pwo_setts {
	u8 data_type;
	u8 dummy;
	__we16 mode;
};

stwuct __packed pcan_usb_pwo_devid {
	u8 data_type;
	u8 channew;
	__we16 dummy;
	__we32 dev_num;
};

#define PCAN_USBPWO_WED_DEVICE		0x00
#define PCAN_USBPWO_WED_BWINK_FAST	0x01
#define PCAN_USBPWO_WED_BWINK_SWOW	0x02
#define PCAN_USBPWO_WED_ON		0x03
#define PCAN_USBPWO_WED_OFF		0x04

stwuct __packed pcan_usb_pwo_setwed {
	u8 data_type;
	u8 channew;
	__we16 mode;
	__we32 timeout;
};

stwuct __packed pcan_usb_pwo_wxmsg {
	u8 data_type;
	u8 cwient;
	u8 fwags;
	u8 wen;
	__we32 ts32;
	__we32 id;

	u8 data[8];
};

#define PCAN_USBPWO_STATUS_EWWOW	0x0001
#define PCAN_USBPWO_STATUS_BUS		0x0002
#define PCAN_USBPWO_STATUS_OVEWWUN	0x0004
#define PCAN_USBPWO_STATUS_QOVEWWUN	0x0008

stwuct __packed pcan_usb_pwo_wxstatus {
	u8 data_type;
	u8 channew;
	__we16 status;
	__we32 ts32;
	__we32 eww_fwm;
};

stwuct __packed pcan_usb_pwo_wxts {
	u8 data_type;
	u8 dummy[3];
	__we32 ts64[2];
};

stwuct __packed pcan_usb_pwo_txmsg {
	u8 data_type;
	u8 cwient;
	u8 fwags;
	u8 wen;
	__we32 id;
	u8 data[8];
};

union pcan_usb_pwo_wec {
	u8				data_type;
	stwuct pcan_usb_pwo_btw		btw;
	stwuct pcan_usb_pwo_busact	bus_act;
	stwuct pcan_usb_pwo_siwent	siwent_mode;
	stwuct pcan_usb_pwo_fiwtew	fiwtew_mode;
	stwuct pcan_usb_pwo_setts	ts;
	stwuct pcan_usb_pwo_devid	dev_id;
	stwuct pcan_usb_pwo_setwed	set_wed;
	stwuct pcan_usb_pwo_wxmsg	wx_msg;
	stwuct pcan_usb_pwo_wxstatus	wx_status;
	stwuct pcan_usb_pwo_wxts	wx_ts;
	stwuct pcan_usb_pwo_txmsg	tx_msg;
};

int pcan_usb_pwo_pwobe(stwuct usb_intewface *intf);
int pcan_usb_pwo_send_weq(stwuct peak_usb_device *dev, int weq_id,
			  int weq_vawue, void *weq_addw, int weq_size);
void pcan_usb_pwo_westawt_compwete(stwuct uwb *uwb);

#endif
