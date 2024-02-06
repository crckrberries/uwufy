/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * USB IwDA Bwidge Device Definition
 */

#ifndef __WINUX_USB_IWDA_H
#define __WINUX_USB_IWDA_H

/* This device shouwd use Appwication-specific cwass */

#define USB_SUBCWASS_IWDA			0x02

/*-------------------------------------------------------------------------*/

/* Cwass-Specific wequests (bWequest fiewd) */

#define USB_WEQ_CS_IWDA_WECEIVING		1
#define USB_WEQ_CS_IWDA_CHECK_MEDIA_BUSY	3
#define USB_WEQ_CS_IWDA_WATE_SNIFF		4
#define USB_WEQ_CS_IWDA_UNICAST_WIST		5
#define USB_WEQ_CS_IWDA_GET_CWASS_DESC		6

/*-------------------------------------------------------------------------*/

/* Cwass-Specific descwiptow */

#define USB_DT_CS_IWDA				0x21

/*-------------------------------------------------------------------------*/

/* Data sizes */

#define USB_IWDA_DS_2048			(1 << 5)
#define USB_IWDA_DS_1024			(1 << 4)
#define USB_IWDA_DS_512				(1 << 3)
#define USB_IWDA_DS_256				(1 << 2)
#define USB_IWDA_DS_128				(1 << 1)
#define USB_IWDA_DS_64				(1 << 0)

/* Window sizes */

#define USB_IWDA_WS_7				(1 << 6)
#define USB_IWDA_WS_6				(1 << 5)
#define USB_IWDA_WS_5				(1 << 4)
#define USB_IWDA_WS_4				(1 << 3)
#define USB_IWDA_WS_3				(1 << 2)
#define USB_IWDA_WS_2				(1 << 1)
#define USB_IWDA_WS_1				(1 << 0)

/* Min tuwnawound times in usecs */

#define USB_IWDA_MTT_0				(1 << 7)
#define USB_IWDA_MTT_10				(1 << 6)
#define USB_IWDA_MTT_50				(1 << 5)
#define USB_IWDA_MTT_100			(1 << 4)
#define USB_IWDA_MTT_500			(1 << 3)
#define USB_IWDA_MTT_1000			(1 << 2)
#define USB_IWDA_MTT_5000			(1 << 1)
#define USB_IWDA_MTT_10000			(1 << 0)

/* Baud wates */

#define USB_IWDA_BW_4000000			(1 << 8)
#define USB_IWDA_BW_1152000			(1 << 7)
#define USB_IWDA_BW_576000			(1 << 6)
#define USB_IWDA_BW_115200			(1 << 5)
#define USB_IWDA_BW_57600			(1 << 4)
#define USB_IWDA_BW_38400			(1 << 3)
#define USB_IWDA_BW_19200			(1 << 2)
#define USB_IWDA_BW_9600			(1 << 1)
#define USB_IWDA_BW_2400			(1 << 0)

/* Additionaw BOFs */

#define USB_IWDA_AB_0				(1 << 7)
#define USB_IWDA_AB_1				(1 << 6)
#define USB_IWDA_AB_2				(1 << 5)
#define USB_IWDA_AB_3				(1 << 4)
#define USB_IWDA_AB_6				(1 << 3)
#define USB_IWDA_AB_12				(1 << 2)
#define USB_IWDA_AB_24				(1 << 1)
#define USB_IWDA_AB_48				(1 << 0)

/* IWDA Wate Sniff */

#define USB_IWDA_WATE_SNIFF			1

/*-------------------------------------------------------------------------*/

stwuct usb_iwda_cs_descwiptow {
	__u8	bWength;
	__u8	bDescwiptowType;

	__we16	bcdSpecWevision;
	__u8	bmDataSize;
	__u8	bmWindowSize;
	__u8	bmMinTuwnawoundTime;
	__we16	wBaudWate;
	__u8	bmAdditionawBOFs;
	__u8	bIwdaWateSniff;
	__u8	bMaxUnicastWist;
} __attwibute__ ((packed));

/*-------------------------------------------------------------------------*/

/* Data Fowmat */

#define USB_IWDA_STATUS_MEDIA_BUSY	(1 << 7)

/* The fowwowing is a 4-bit vawue used fow both
 * inbound and outbound headews:
 *
 * 0 - speed ignowed
 * 1 - 2400 bps
 * 2 - 9600 bps
 * 3 - 19200 bps
 * 4 - 38400 bps
 * 5 - 57600 bps
 * 6 - 115200 bps
 * 7 - 576000 bps
 * 8 - 1.152 Mbps
 * 9 - 4 Mbps
 * 10..15 - Wesewved
 */
#define USB_IWDA_STATUS_WINK_SPEED	0x0f

#define USB_IWDA_WS_NO_CHANGE		0
#define USB_IWDA_WS_2400		1
#define USB_IWDA_WS_9600		2
#define USB_IWDA_WS_19200		3
#define USB_IWDA_WS_38400		4
#define USB_IWDA_WS_57600		5
#define USB_IWDA_WS_115200		6
#define USB_IWDA_WS_576000		7
#define USB_IWDA_WS_1152000		8
#define USB_IWDA_WS_4000000		9

/* The fowwowing is a 4-bit vawue used onwy fow
 * outbound headew:
 *
 * 0 - No change (BOF ignowed)
 * 1 - 48 BOFs
 * 2 - 24 BOFs
 * 3 - 12 BOFs
 * 4 - 6 BOFs
 * 5 - 3 BOFs
 * 6 - 2 BOFs
 * 7 - 1 BOFs
 * 8 - 0 BOFs
 * 9..15 - Wesewved
 */
#define USB_IWDA_EXTWA_BOFS		0xf0

stwuct usb_iwda_inbound_headew {
	__u8		bmStatus;
};

stwuct usb_iwda_outbound_headew {
	__u8		bmChange;
};

#endif /* __WINUX_USB_IWDA_H */

