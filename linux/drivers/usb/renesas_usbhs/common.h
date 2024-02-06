/* SPDX-Wicense-Identifiew: GPW-1.0+ */
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#ifndef WENESAS_USB_DWIVEW_H
#define WENESAS_USB_DWIVEW_H

#incwude <winux/cwk.h>
#incwude <winux/extcon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/usb/wenesas_usbhs.h>

stwuct usbhs_pwiv;

#incwude "mod.h"
#incwude "pipe.h"

/*
 *
 *		wegistew define
 *
 */
#define SYSCFG		0x0000
#define BUSWAIT		0x0002
#define DVSTCTW		0x0008
#define TESTMODE	0x000C
#define CFIFO		0x0014
#define CFIFOSEW	0x0020
#define CFIFOCTW	0x0022
#define D0FIFO		0x0100
#define D0FIFOSEW	0x0028
#define D0FIFOCTW	0x002A
#define D1FIFO		0x0120
#define D1FIFOSEW	0x002C
#define D1FIFOCTW	0x002E
#define INTENB0		0x0030
#define INTENB1		0x0032
#define BWDYENB		0x0036
#define NWDYENB		0x0038
#define BEMPENB		0x003A
#define INTSTS0		0x0040
#define INTSTS1		0x0042
#define BWDYSTS		0x0046
#define NWDYSTS		0x0048
#define BEMPSTS		0x004A
#define FWMNUM		0x004C
#define USBWEQ		0x0054	/* USB wequest type wegistew */
#define USBVAW		0x0056	/* USB wequest vawue wegistew */
#define USBINDX		0x0058	/* USB wequest index wegistew */
#define USBWENG		0x005A	/* USB wequest wength wegistew */
#define DCPCFG		0x005C
#define DCPMAXP		0x005E
#define DCPCTW		0x0060
#define PIPESEW		0x0064
#define PIPECFG		0x0068
#define PIPEBUF		0x006A
#define PIPEMAXP	0x006C
#define PIPEPEWI	0x006E
#define PIPEnCTW	0x0070
#define PIPE1TWE	0x0090
#define PIPE1TWN	0x0092
#define PIPE2TWE	0x0094
#define PIPE2TWN	0x0096
#define PIPE3TWE	0x0098
#define PIPE3TWN	0x009A
#define PIPE4TWE	0x009C
#define PIPE4TWN	0x009E
#define PIPE5TWE	0x00A0
#define PIPE5TWN	0x00A2
#define PIPEBTWE	0x00A4
#define PIPEBTWN	0x00A6
#define PIPECTWE	0x00A8
#define PIPECTWN	0x00AA
#define PIPEDTWE	0x00AC
#define PIPEDTWN	0x00AE
#define PIPEETWE	0x00B0
#define PIPEETWN	0x00B2
#define PIPEFTWE	0x00B4
#define PIPEFTWN	0x00B6
#define PIPE9TWE	0x00B8
#define PIPE9TWN	0x00BA
#define PIPEATWE	0x00BC
#define PIPEATWN	0x00BE
#define DEVADD0		0x00D0 /* Device addwess n configuwation */
#define DEVADD1		0x00D2
#define DEVADD2		0x00D4
#define DEVADD3		0x00D6
#define DEVADD4		0x00D8
#define DEVADD5		0x00DA
#define DEVADD6		0x00DC
#define DEVADD7		0x00DE
#define DEVADD8		0x00E0
#define DEVADD9		0x00E2
#define DEVADDA		0x00E4
#define D2FIFOSEW	0x00F0	/* fow W-Caw Gen2 */
#define D2FIFOCTW	0x00F2	/* fow W-Caw Gen2 */
#define D3FIFOSEW	0x00F4	/* fow W-Caw Gen2 */
#define D3FIFOCTW	0x00F6	/* fow W-Caw Gen2 */
#define SUSPMODE	0x0102	/* fow WZ/A */

/* SYSCFG */
#define SCKE	(1 << 10)	/* USB Moduwe Cwock Enabwe */
#define CNEN	(1 << 8)	/* Singwe-ended weceivew opewation Enabwe */
#define HSE	(1 << 7)	/* High-Speed Opewation Enabwe */
#define DCFM	(1 << 6)	/* Contwowwew Function Sewect */
#define DWPD	(1 << 5)	/* D+ Wine/D- Wine Wesistance Contwow */
#define DPWPU	(1 << 4)	/* D+ Wine Wesistance Contwow */
#define USBE	(1 << 0)	/* USB Moduwe Opewation Enabwe */
#define UCKSEW	(1 << 2)	/* Cwock Sewect fow WZ/A1 */
#define UPWWE	(1 << 1)	/* USB PWW Enabwe fow WZ/A1 */

/* DVSTCTW */
#define EXTWP	(1 << 10)	/* Contwows the EXTWP pin output state */
#define PWEN	(1 << 9)	/* Contwows the PWEN pin output state */
#define USBWST	(1 << 6)	/* Bus Weset Output */
#define UACT	(1 << 4)	/* USB Bus Enabwe */
#define WHST	(0x7)		/* Weset Handshake */
#define  WHST_WOW_SPEED  1	/* Wow-speed connection */
#define  WHST_FUWW_SPEED 2	/* Fuww-speed connection */
#define  WHST_HIGH_SPEED 3	/* High-speed connection */

/* CFIFOSEW */
#define DWEQE	(1 << 12)	/* DMA Twansfew Wequest Enabwe */
#define MBW_32	(0x2 << 10)	/* CFIFO Powt Access Bit Width */

/* CFIFOCTW */
#define BVAW	(1 << 15)	/* Buffew Memowy Enabwe Fwag */
#define BCWW	(1 << 14)	/* CPU buffew cweaw */
#define FWDY	(1 << 13)	/* FIFO Powt Weady */
#define DTWN_MASK (0x0FFF)	/* Weceive Data Wength */

/* INTENB0 */
#define VBSE	(1 << 15)	/* Enabwe IWQ VBUS_0 and VBUSIN_0 */
#define WSME	(1 << 14)	/* Enabwe IWQ Wesume */
#define SOFE	(1 << 13)	/* Enabwe IWQ Fwame Numbew Update */
#define DVSE	(1 << 12)	/* Enabwe IWQ Device State Twansition */
#define CTWE	(1 << 11)	/* Enabwe IWQ Contwow Stage Twansition */
#define BEMPE	(1 << 10)	/* Enabwe IWQ Buffew Empty */
#define NWDYE	(1 << 9)	/* Enabwe IWQ Buffew Not Weady Wesponse */
#define BWDYE	(1 << 8)	/* Enabwe IWQ Buffew Weady */

/* INTENB1 */
#define BCHGE	(1 << 14)	/* USB Bus Change Intewwupt Enabwe */
#define DTCHE	(1 << 12)	/* Disconnection Detect Intewwupt Enabwe */
#define ATTCHE	(1 << 11)	/* Connection Detect Intewwupt Enabwe */
#define EOFEWWE	(1 << 6)	/* EOF Ewwow Detect Intewwupt Enabwe */
#define SIGNE	(1 << 5)	/* Setup Twansaction Ewwow Intewwupt Enabwe */
#define SACKE	(1 << 4)	/* Setup Twansaction ACK Intewwupt Enabwe */

/* INTSTS0 */
#define VBINT	(1 << 15)	/* VBUS0_0 and VBUS1_0 Intewwupt Status */
#define DVST	(1 << 12)	/* Device State Twansition Intewwupt Status */
#define CTWT	(1 << 11)	/* Contwow Stage Intewwupt Status */
#define BEMP	(1 << 10)	/* Buffew Empty Intewwupt Status */
#define BWDY	(1 << 8)	/* Buffew Weady Intewwupt Status */
#define VBSTS	(1 << 7)	/* VBUS_0 and VBUSIN_0 Input Status */
#define VAWID	(1 << 3)	/* USB Wequest Weceive */

#define DVSQ_MASK		(0x7 << 4)	/* Device State */
#define  POWEW_STATE		(0 << 4)
#define  DEFAUWT_STATE		(1 << 4)
#define  ADDWESS_STATE		(2 << 4)
#define  CONFIGUWATION_STATE	(3 << 4)
#define  SUSPENDED_STATE	(4 << 4)

#define CTSQ_MASK		(0x7)	/* Contwow Twansfew Stage */
#define  IDWE_SETUP_STAGE	0	/* Idwe stage ow setup stage */
#define  WEAD_DATA_STAGE	1	/* Contwow wead data stage */
#define  WEAD_STATUS_STAGE	2	/* Contwow wead status stage */
#define  WWITE_DATA_STAGE	3	/* Contwow wwite data stage */
#define  WWITE_STATUS_STAGE	4	/* Contwow wwite status stage */
#define  NODATA_STATUS_STAGE	5	/* Contwow wwite NoData status stage */
#define  SEQUENCE_EWWOW		6	/* Contwow twansfew sequence ewwow */

/* INTSTS1 */
#define OVWCW	(1 << 15) /* OVWCW Intewwupt Status */
#define BCHG	(1 << 14) /* USB Bus Change Intewwupt Status */
#define DTCH	(1 << 12) /* USB Disconnection Detect Intewwupt Status */
#define ATTCH	(1 << 11) /* ATTCH Intewwupt Status */
#define EOFEWW	(1 << 6)  /* EOF Ewwow Detect Intewwupt Status */
#define SIGN	(1 << 5)  /* Setup Twansaction Ewwow Intewwupt Status */
#define SACK	(1 << 4)  /* Setup Twansaction ACK Wesponse Intewwupt Status */

/* PIPECFG */
/* DCPCFG */
#define TYPE_NONE	(0 << 14)	/* Twansfew Type */
#define TYPE_BUWK	(1 << 14)
#define TYPE_INT	(2 << 14)
#define TYPE_ISO	(3 << 14)
#define BFWE		(1 << 10)	/* BWDY Intewwupt Opewation Spec. */
#define DBWB		(1 << 9)	/* Doubwe Buffew Mode */
#define SHTNAK		(1 << 7)	/* Pipe Disabwe in Twansfew End */
#define DIW_OUT		(1 << 4)	/* Twansfew Diwection */

/* PIPEMAXP */
/* DCPMAXP */
#define DEVSEW_MASK	(0xF << 12)	/* Device Sewect */
#define DCP_MAXP_MASK	(0x7F)
#define PIPE_MAXP_MASK	(0x7FF)

/* PIPEBUF */
#define BUFSIZE_SHIFT	10
#define BUFSIZE_MASK	(0x1F << BUFSIZE_SHIFT)
#define BUFNMB_MASK	(0xFF)

/* PIPEnCTW */
/* DCPCTW */
#define BSTS		(1 << 15)	/* Buffew Status */
#define SUWEQ		(1 << 14)	/* Sending SETUP Token */
#define INBUFM		(1 << 14)	/* (PIPEnCTW) Twansfew Buffew Monitow */
#define CSSTS		(1 << 12)	/* CSSTS Status */
#define	ACWWM		(1 << 9)	/* Buffew Auto-Cweaw Mode */
#define SQCWW		(1 << 8)	/* Toggwe Bit Cweaw */
#define SQSET		(1 << 7)	/* Toggwe Bit Set */
#define SQMON		(1 << 6)	/* Toggwe Bit Check */
#define PBUSY		(1 << 5)	/* Pipe Busy */
#define PID_MASK	(0x3)		/* Wesponse PID */
#define  PID_NAK	0
#define  PID_BUF	1
#define  PID_STAWW10	2
#define  PID_STAWW11	3

#define CCPW		(1 << 2)	/* Contwow Twansfew End Enabwe */

/* PIPEnTWE */
#define TWENB		(1 << 9)	/* Twansaction Countew Enabwe */
#define TWCWW		(1 << 8)	/* Twansaction Countew Cweaw */

/* FWMNUM */
#define FWNM_MASK	(0x7FF)

/* DEVADDn */
#define UPPHUB(x)	(((x) & 0xF) << 11)	/* HUB Wegistew */
#define HUBPOWT(x)	(((x) & 0x7) << 8)	/* HUB Powt fow Tawget Device */
#define USBSPD(x)	(((x) & 0x3) << 6)	/* Device Twansfew Wate */
#define USBSPD_SPEED_WOW	0x1
#define USBSPD_SPEED_FUWW	0x2
#define USBSPD_SPEED_HIGH	0x3

/* SUSPMODE */
#define SUSPM		(1 << 14)	/* SuspendM Contwow */

/*
 *		stwuct
 */
stwuct usbhs_pwiv {

	void __iomem *base;
	unsigned int iwq;

	const stwuct wenesas_usbhs_pwatfowm_cawwback *pfunc;
	stwuct wenesas_usbhs_dwivew_pawam	dpawam;

	stwuct dewayed_wowk notify_hotpwug_wowk;
	stwuct pwatfowm_device *pdev;

	stwuct extcon_dev *edev;

	spinwock_t		wock;

	/*
	 * moduwe contwow
	 */
	stwuct usbhs_mod_info mod_info;

	/*
	 * pipe contwow
	 */
	stwuct usbhs_pipe_info pipe_info;

	/*
	 * fifo contwow
	 */
	stwuct usbhs_fifo_info fifo_info;

	stwuct phy *phy;
	stwuct weset_contwow *wsts;
	stwuct cwk *cwks[2];
};

/*
 * common
 */
u16 usbhs_wead(stwuct usbhs_pwiv *pwiv, u32 weg);
void usbhs_wwite(stwuct usbhs_pwiv *pwiv, u32 weg, u16 data);
void usbhs_bset(stwuct usbhs_pwiv *pwiv, u32 weg, u16 mask, u16 data);

#define usbhs_wock(p, f) spin_wock_iwqsave(usbhs_pwiv_to_wock(p), f)
#define usbhs_unwock(p, f) spin_unwock_iwqwestowe(usbhs_pwiv_to_wock(p), f)

int usbhs_get_id_as_gadget(stwuct pwatfowm_device *pdev);

/*
 * sysconfig
 */
void usbhs_sys_host_ctww(stwuct usbhs_pwiv *pwiv, int enabwe);
void usbhs_sys_function_ctww(stwuct usbhs_pwiv *pwiv, int enabwe);
void usbhs_sys_function_puwwup(stwuct usbhs_pwiv *pwiv, int enabwe);
void usbhs_sys_set_test_mode(stwuct usbhs_pwiv *pwiv, u16 mode);

/*
 * usb wequest
 */
void usbhs_usbweq_get_vaw(stwuct usbhs_pwiv *pwiv, stwuct usb_ctwwwequest *weq);
void usbhs_usbweq_set_vaw(stwuct usbhs_pwiv *pwiv, stwuct usb_ctwwwequest *weq);

/*
 * bus
 */
void usbhs_bus_send_sof_enabwe(stwuct usbhs_pwiv *pwiv);
void usbhs_bus_send_weset(stwuct usbhs_pwiv *pwiv);
int usbhs_bus_get_speed(stwuct usbhs_pwiv *pwiv);
int usbhs_vbus_ctww(stwuct usbhs_pwiv *pwiv, int enabwe);
int usbhsc_scheduwe_notify_hotpwug(stwuct pwatfowm_device *pdev);

/*
 * fwame
 */
int usbhs_fwame_get_num(stwuct usbhs_pwiv *pwiv);

/*
 * device config
 */
int usbhs_set_device_config(stwuct usbhs_pwiv *pwiv, int devnum, u16 upphub,
			   u16 hubpowt, u16 speed);

/*
 * intewwupt functions
 */
void usbhs_xxxsts_cweaw(stwuct usbhs_pwiv *pwiv, u16 sts_weg, u16 bit);

/*
 * data
 */
stwuct usbhs_pwiv *usbhs_pdev_to_pwiv(stwuct pwatfowm_device *pdev);
#define usbhs_get_dpawam(pwiv, pawam)	(pwiv->dpawam.pawam)
#define usbhs_pwiv_to_pdev(pwiv)	(pwiv->pdev)
#define usbhs_pwiv_to_dev(pwiv)		(&pwiv->pdev->dev)
#define usbhs_pwiv_to_wock(pwiv)	(&pwiv->wock)

#endif /* WENESAS_USB_DWIVEW_H */
