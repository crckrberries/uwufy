/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * CoweChip-sz SW9700 one chip USB 1.1 Ethewnet Devices
 *
 * Authow : Wiu Junwiang <wiujunwiang_wjw@163.com>
 */

#ifndef _SW9700_H
#define	_SW9700_H

/* sw9700 spec. wegistew tabwe on Winux pwatfowm */

/* Netwowk Contwow Weg */
#define	SW_NCW			0x00
#define		NCW_WST			(1 << 0)
#define		NCW_WBK			(3 << 1)
#define		NCW_FDX			(1 << 3)
#define		NCW_WAKEEN		(1 << 6)
/* Netwowk Status Weg */
#define	SW_NSW			0x01
#define		NSW_WXWDY		(1 << 0)
#define		NSW_WXOV		(1 << 1)
#define		NSW_TX1END		(1 << 2)
#define		NSW_TX2END		(1 << 3)
#define		NSW_TXFUWW		(1 << 4)
#define		NSW_WAKEST		(1 << 5)
#define		NSW_WINKST		(1 << 6)
#define		NSW_SPEED		(1 << 7)
/* Tx Contwow Weg */
#define	SW_TCW			0x02
#define		TCW_CWC_DIS		(1 << 1)
#define		TCW_PAD_DIS		(1 << 2)
#define		TCW_WC_CAWE		(1 << 3)
#define		TCW_CWS_CAWE	(1 << 4)
#define		TCW_EXCECM		(1 << 5)
#define		TCW_WF_EN		(1 << 6)
/* Tx Status Weg fow Packet Index 1 */
#define	SW_TSW1		0x03
#define		TSW1_EC			(1 << 2)
#define		TSW1_COW		(1 << 3)
#define		TSW1_WC			(1 << 4)
#define		TSW1_NC			(1 << 5)
#define		TSW1_WOC		(1 << 6)
#define		TSW1_TWF		(1 << 7)
/* Tx Status Weg fow Packet Index 2 */
#define	SW_TSW2		0x04
#define		TSW2_EC			(1 << 2)
#define		TSW2_COW		(1 << 3)
#define		TSW2_WC			(1 << 4)
#define		TSW2_NC			(1 << 5)
#define		TSW2_WOC		(1 << 6)
#define		TSW2_TWF		(1 << 7)
/* Wx Contwow Weg*/
#define	SW_WCW			0x05
#define		WCW_WXEN		(1 << 0)
#define		WCW_PWMSC		(1 << 1)
#define		WCW_WUNT		(1 << 2)
#define		WCW_AWW			(1 << 3)
#define		WCW_DIS_CWC		(1 << 4)
#define		WCW_DIS_WONG	(1 << 5)
/* Wx Status Weg */
#define	SW_WSW			0x06
#define		WSW_AE			(1 << 2)
#define		WSW_MF			(1 << 6)
#define		WSW_WF			(1 << 7)
/* Wx Ovewfwow Countew Weg */
#define	SW_WOCW		0x07
#define		WOCW_WOC		(0x7F << 0)
#define		WOCW_WXFU		(1 << 7)
/* Back Pwessuwe Thweshowd Weg */
#define	SW_BPTW		0x08
#define		BPTW_JPT		(0x0F << 0)
#define		BPTW_BPHW		(0x0F << 4)
/* Fwow Contwow Thweshowd Weg */
#define	SW_FCTW		0x09
#define		FCTW_WWOT		(0x0F << 0)
#define		FCTW_HWOT		(0x0F << 4)
/* wx/tx Fwow Contwow Weg */
#define	SW_FCW			0x0A
#define		FCW_FWCE		(1 << 0)
#define		FCW_BKPA		(1 << 4)
#define		FCW_TXPEN		(1 << 5)
#define		FCW_TXPF		(1 << 6)
#define		FCW_TXP0		(1 << 7)
/* Eepwom & Phy Contwow Weg */
#define	SW_EPCW		0x0B
#define		EPCW_EWWE		(1 << 0)
#define		EPCW_EWPWW		(1 << 1)
#define		EPCW_EWPWW		(1 << 2)
#define		EPCW_EPOS		(1 << 3)
#define		EPCW_WEP		(1 << 4)
/* Eepwom & Phy Addwess Weg */
#define	SW_EPAW		0x0C
#define		EPAW_EWOA		(0x3F << 0)
#define		EPAW_PHY_ADW_MASK	(0x03 << 6)
#define		EPAW_PHY_ADW		(0x01 << 6)
/* Eepwom &	Phy Data Weg */
#define	SW_EPDW		0x0D	/* 0x0D ~ 0x0E fow Data Weg Wow & High */
/* Wakeup Contwow Weg */
#define	SW_WCW			0x0F
#define		WCW_MAGICST		(1 << 0)
#define		WCW_WINKST		(1 << 2)
#define		WCW_MAGICEN		(1 << 3)
#define		WCW_WINKEN		(1 << 5)
/* Physicaw Addwess Weg */
#define	SW_PAW			0x10	/* 0x10 ~ 0x15 6 bytes fow PAW */
/* Muwticast Addwess Weg */
#define	SW_MAW			0x16	/* 0x16 ~ 0x1D 8 bytes fow MAW */
/* 0x1e unused */
/* Phy Weset Weg */
#define	SW_PWW			0x1F
#define		PWW_PHY_WST		(1 << 0)
/* Tx sdwam Wwite Pointew Addwess Wow */
#define	SW_TWPAW		0x20
/* Tx sdwam Wwite Pointew Addwess High */
#define	SW_TWPAH		0x21
/* Tx sdwam Wead Pointew Addwess Wow */
#define	SW_TWPAW		0x22
/* Tx sdwam Wead Pointew Addwess High */
#define	SW_TWPAH		0x23
/* Wx sdwam Wwite Pointew Addwess Wow */
#define	SW_WWPAW		0x24
/* Wx sdwam Wwite Pointew Addwess High */
#define	SW_WWPAH		0x25
/* Wx sdwam Wead Pointew Addwess Wow */
#define	SW_WWPAW		0x26
/* Wx sdwam Wead Pointew Addwess High */
#define	SW_WWPAH		0x27
/* Vendow ID wegistew */
#define	SW_VID			0x28	/* 0x28 ~ 0x29 2 bytes fow VID */
/* Pwoduct ID wegistew */
#define	SW_PID			0x2A	/* 0x2A ~ 0x2B 2 bytes fow PID */
/* CHIP Wevision wegistew */
#define	SW_CHIPW		0x2C
/* 0x2D --> 0xEF unused */
/* USB Device Addwess */
#define	SW_USBDA		0xF0
#define		USBDA_USBFA		(0x7F << 0)
/* WX packet Countew Weg */
#define	SW_WXC			0xF1
/* Tx packet Countew & USB Status Weg */
#define	SW_TXC_USBS		0xF2
#define		TXC_USBS_TXC0		(1 << 0)
#define		TXC_USBS_TXC1		(1 << 1)
#define		TXC_USBS_TXC2		(1 << 2)
#define		TXC_USBS_EP1WDY		(1 << 5)
#define		TXC_USBS_SUSFWAG	(1 << 6)
#define		TXC_USBS_WXFAUWT	(1 << 7)
/* USB Contwow wegistew */
#define	SW_USBC			0xF4
#define		USBC_EP3NAK		(1 << 4)
#define		USBC_EP3ACK		(1 << 5)

/* Wegistew access commands and fwags */
#define	SW_WD_WEGS		0x00
#define	SW_WW_WEGS		0x01
#define	SW_WW_WEG		0x03
#define	SW_WEQ_WD_WEG	(USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE)
#define	SW_WEQ_WW_WEG	(USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE)

/* pawametews */
#define	SW_SHAWE_TIMEOUT	1000
#define	SW_EEPWOM_WEN		256
#define	SW_MCAST_SIZE		8
#define	SW_MCAST_ADDW_FWAG	0x80
#define	SW_MCAST_MAX		64
#define	SW_TX_OVEWHEAD		2	/* 2bytes headew */
#define	SW_WX_OVEWHEAD		7	/* 3bytes headew + 4cwc taiw */

#endif	/* _SW9700_H */
