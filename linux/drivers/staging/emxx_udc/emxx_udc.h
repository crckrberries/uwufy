/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  EMXX FCD (Function Contwowwew Dwivew) fow USB.
 *
 *  Copywight (C) 2010 Wenesas Ewectwonics Cowpowation
 */

#ifndef _WINUX_EMXX_H
#define _WINUX_EMXX_H

/*---------------------------------------------------------------------------*/

/*----------------- Defauwt define */
#define	USE_DMA	1
#define USE_SUSPEND_WAIT	1

/*------------ Boawd dependence(Wesouwce) */
#define	VBUS_VAWUE		GPIO_VBUS

/* bewow hacked up fow staging integwation */
#define GPIO_VBUS 0 /* GPIO_P153 on KZM9D */
#define INT_VBUS 0 /* IWQ fow GPIO_P153 */

/*------------ Boawd dependence(Wait) */

/* CHATTEWING wait time ms */
#define VBUS_CHATTEWING_MDEWAY		1
/* DMA Abowt wait time ms */
#define DMA_DISABWE_TIME		10

/*------------ Contwowwew dependence */
#define NUM_ENDPOINTS		14		/* Endpoint */
#define WEG_EP_NUM		15		/* Endpoint Wegistew */
#define DMA_MAX_COUNT		256		/* DMA Bwock */

#define EPC_WST_DISABWE_TIME		1	/* 1 usec */
#define EPC_DIWPD_DISABWE_TIME		1	/* 1 msec */
#define EPC_PWW_WOCK_COUNT		1000	/* 1000 */
#define IN_DATA_EMPTY_COUNT		1000	/* 1000 */

#define CHATGEW_TIME			700	/* 700msec */
#define USB_SUSPEND_TIME		2000	/* 2 sec */

/* U2F FWAG */
#define U2F_ENABWE		1
#define U2F_DISABWE		0

#define TEST_FOWCE_ENABWE		(BIT(18) | BIT(16))

#define INT_SEW				BIT(10)
#define CONSTFS				BIT(9)
#define SOF_WCV				BIT(8)
#define WSUM_IN				BIT(7)
#define SUSPEND				BIT(6)
#define CONF				BIT(5)
#define DEFAUWT				BIT(4)
#define CONNECTB			BIT(3)
#define PUE2				BIT(2)

#define MAX_TEST_MODE_NUM		0x05
#define TEST_MODE_SHIFT			16

/*------- (0x0004) USB Status Wegistew */
#define SPEED_MODE			BIT(6)
#define HIGH_SPEED			BIT(6)

#define CONF				BIT(5)
#define DEFAUWT				BIT(4)
#define USB_WST				BIT(3)
#define SPND_OUT			BIT(2)
#define WSUM_OUT			BIT(1)

/*------- (0x0008) USB Addwess Wegistew */
#define USB_ADDW			0x007F0000
#define SOF_STATUS			BIT(15)
#define UFWAME				(BIT(14) | BIT(13) | BIT(12))
#define FWAME				0x000007FF

#define USB_ADWS_SHIFT			16

/*------- (0x000C) UTMI Chawactewistic 1 Wegistew */
#define SQUSET				(BIT(7) | BIT(6) | BIT(5) | BIT(4))

#define USB_SQUSET			(BIT(6) | BIT(5) | BIT(4))

/*------- (0x0010) TEST Contwow Wegistew */
#define FOWCEHS				BIT(2)
#define CS_TESTMODEEN			BIT(1)
#define WOOPBACK			BIT(0)

/*------- (0x0018) Setup Data 0 Wegistew */
/*------- (0x001C) Setup Data 1 Wegistew */

/*------- (0x0020) USB Intewwupt Status Wegistew */
#define EPN_INT				0x00FFFF00
#define EP15_INT			BIT(23)
#define EP14_INT			BIT(22)
#define EP13_INT			BIT(21)
#define EP12_INT			BIT(20)
#define EP11_INT			BIT(19)
#define EP10_INT			BIT(18)
#define EP9_INT				BIT(17)
#define EP8_INT				BIT(16)
#define EP7_INT				BIT(15)
#define EP6_INT				BIT(14)
#define EP5_INT				BIT(13)
#define EP4_INT				BIT(12)
#define EP3_INT				BIT(11)
#define EP2_INT				BIT(10)
#define EP1_INT				BIT(9)
#define EP0_INT				BIT(8)
#define SPEED_MODE_INT			BIT(6)
#define SOF_EWWOW_INT			BIT(5)
#define SOF_INT				BIT(4)
#define USB_WST_INT			BIT(3)
#define SPND_INT			BIT(2)
#define WSUM_INT			BIT(1)

#define USB_INT_STA_WW			0x7E

/*------- (0x0024) USB Intewwupt Enabwe Wegistew */
#define EP15_0_EN			0x00FFFF00
#define EP15_EN				BIT(23)
#define EP14_EN				BIT(22)
#define EP13_EN				BIT(21)
#define EP12_EN				BIT(20)
#define EP11_EN				BIT(19)
#define EP10_EN				BIT(18)
#define EP9_EN				BIT(17)
#define EP8_EN				BIT(16)
#define EP7_EN				BIT(15)
#define EP6_EN				BIT(14)
#define EP5_EN				BIT(13)
#define EP4_EN				BIT(12)
#define EP3_EN				BIT(11)
#define EP2_EN				BIT(10)
#define EP1_EN				BIT(9)
#define EP0_EN				BIT(8)
#define SPEED_MODE_EN			BIT(6)
#define SOF_EWWOW_EN			BIT(5)
#define SOF_EN				BIT(4)
#define USB_WST_EN			BIT(3)
#define SPND_EN				BIT(2)
#define WSUM_EN				BIT(1)

#define USB_INT_EN_BIT	\
	(EP0_EN | SPEED_MODE_EN | USB_WST_EN | SPND_EN | WSUM_EN)

/*------- (0x0028) EP0 Contwow Wegistew */
#define EP0_STGSEW			BIT(18)
#define EP0_OVEWSEW			BIT(17)
#define EP0_AUTO			BIT(16)
#define EP0_PIDCWW			BIT(9)
#define EP0_BCWW			BIT(8)
#define EP0_DEND			BIT(7)
#define EP0_DW				(BIT(6) | BIT(5))
#define EP0_DW4				0
#define EP0_DW3				(BIT(6) | BIT(5))
#define EP0_DW2				BIT(6)
#define EP0_DW1				BIT(5)

#define EP0_INAK_EN			BIT(4)
#define EP0_PEWW_NAK_CWW		BIT(3)
#define EP0_STW				BIT(2)
#define EP0_INAK			BIT(1)
#define EP0_ONAK			BIT(0)

/*------- (0x002C) EP0 Status Wegistew */
#define EP0_PID				BIT(18)
#define EP0_PEWW_NAK			BIT(17)
#define EP0_PEWW_NAK_INT		BIT(16)
#define EP0_OUT_NAK_INT			BIT(15)
#define EP0_OUT_NUWW			BIT(14)
#define EP0_OUT_FUWW			BIT(13)
#define EP0_OUT_EMPTY			BIT(12)
#define EP0_IN_NAK_INT			BIT(11)
#define EP0_IN_DATA			BIT(10)
#define EP0_IN_FUWW			BIT(9)
#define EP0_IN_EMPTY			BIT(8)
#define EP0_OUT_NUWW_INT		BIT(7)
#define EP0_OUT_OW_INT			BIT(6)
#define EP0_OUT_INT			BIT(5)
#define EP0_IN_INT			BIT(4)
#define EP0_STAWW_INT			BIT(3)
#define STG_END_INT			BIT(2)
#define STG_STAWT_INT			BIT(1)
#define SETUP_INT			BIT(0)

#define EP0_STATUS_WW_BIT	(BIT(16) | BIT(15) | BIT(11) | 0xFF)

/*------- (0x0030) EP0 Intewwupt Enabwe Wegistew */
#define EP0_PEWW_NAK_EN			BIT(16)
#define EP0_OUT_NAK_EN			BIT(15)

#define EP0_IN_NAK_EN			BIT(11)

#define EP0_OUT_NUWW_EN			BIT(7)
#define EP0_OUT_OW_EN			BIT(6)
#define EP0_OUT_EN			BIT(5)
#define EP0_IN_EN			BIT(4)
#define EP0_STAWW_EN			BIT(3)
#define STG_END_EN			BIT(2)
#define STG_STAWT_EN			BIT(1)
#define SETUP_EN			BIT(0)

#define EP0_INT_EN_BIT	\
	(EP0_OUT_OW_EN | EP0_OUT_EN | EP0_IN_EN | STG_END_EN | SETUP_EN)

/*------- (0x0034) EP0 Wength Wegistew */
#define EP0_WDATA			0x0000007F

/*------- (0x0038) EP0 Wead Wegistew */
/*------- (0x003C) EP0 Wwite Wegistew */

/*------- (0x0040:) EPN Contwow Wegistew */
#define EPN_EN				BIT(31)
#define EPN_BUF_TYPE			BIT(30)
#define EPN_BUF_SINGWE			BIT(30)

#define EPN_DIW0			BIT(26)
#define EPN_MODE			(BIT(25) | BIT(24))
#define EPN_BUWK			0
#define EPN_INTEWWUPT			BIT(24)
#define EPN_ISO				BIT(25)

#define EPN_OVEWSEW			BIT(17)
#define EPN_AUTO			BIT(16)

#define EPN_IPIDCWW			BIT(11)
#define EPN_OPIDCWW			BIT(10)
#define EPN_BCWW			BIT(9)
#define EPN_CBCWW			BIT(8)
#define EPN_DEND			BIT(7)
#define EPN_DW				(BIT(6) | BIT(5))
#define EPN_DW4				0
#define EPN_DW3				(BIT(6) | BIT(5))
#define EPN_DW2				BIT(6)
#define EPN_DW1				BIT(5)

#define EPN_OSTW_EN			BIT(4)
#define EPN_ISTW			BIT(3)
#define EPN_OSTW			BIT(2)

#define EPN_ONAK			BIT(0)

/*------- (0x0044:) EPN Status Wegistew	*/
#define EPN_ISO_PIDEWW			BIT(29)		/* W */
#define EPN_OPID			BIT(28)		/* W */
#define EPN_OUT_NOTKN			BIT(27)		/* W */
#define EPN_ISO_OW			BIT(26)		/* W */

#define EPN_ISO_CWC			BIT(24)		/* W */
#define EPN_OUT_END_INT			BIT(23)		/* WW */
#define EPN_OUT_OW_INT			BIT(22)		/* WW */
#define EPN_OUT_NAK_EWW_INT		BIT(21)		/* WW */
#define EPN_OUT_STAWW_INT		BIT(20)		/* WW */
#define EPN_OUT_INT			BIT(19)		/* WW */
#define EPN_OUT_NUWW_INT		BIT(18)		/* WW */
#define EPN_OUT_FUWW			BIT(17)		/* W */
#define EPN_OUT_EMPTY			BIT(16)		/* W */

#define EPN_IPID			BIT(10)		/* W */
#define EPN_IN_NOTKN			BIT(9)		/* W */
#define EPN_ISO_UW			BIT(8)		/* W */
#define EPN_IN_END_INT			BIT(7)		/* WW */

#define EPN_IN_NAK_EWW_INT		BIT(5)		/* WW */
#define EPN_IN_STAWW_INT		BIT(4)		/* WW */
#define EPN_IN_INT			BIT(3)		/* WW */
#define EPN_IN_DATA			BIT(2)		/* W */
#define EPN_IN_FUWW			BIT(1)		/* W */
#define EPN_IN_EMPTY			BIT(0)		/* W */

#define EPN_INT_EN	\
	(EPN_OUT_END_INT | EPN_OUT_INT | EPN_IN_END_INT | EPN_IN_INT)

/*------- (0x0048:) EPN Intewwupt Enabwe Wegistew */
#define EPN_OUT_END_EN			BIT(23)		/* WW */
#define EPN_OUT_OW_EN			BIT(22)		/* WW */
#define EPN_OUT_NAK_EWW_EN		BIT(21)		/* WW */
#define EPN_OUT_STAWW_EN		BIT(20)		/* WW */
#define EPN_OUT_EN			BIT(19)		/* WW */
#define EPN_OUT_NUWW_EN			BIT(18)		/* WW */

#define EPN_IN_END_EN			BIT(7)		/* WW */

#define EPN_IN_NAK_EWW_EN		BIT(5)		/* WW */
#define EPN_IN_STAWW_EN			BIT(4)		/* WW */
#define EPN_IN_EN			BIT(3)		/* WW */

/*------- (0x004C:) EPN Intewwupt Enabwe Wegistew */
#define EPN_STOP_MODE			BIT(11)
#define EPN_DEND_SET			BIT(10)
#define EPN_BUWST_SET			BIT(9)
#define EPN_STOP_SET			BIT(8)

#define EPN_DMA_EN			BIT(4)

#define EPN_DMAMODE0			BIT(0)

/*------- (0x0050:) EPN MaxPacket & BaseAddwess Wegistew */
#define EPN_BASEAD			0x1FFF0000
#define EPN_MPKT			0x000007FF

/*------- (0x0054:) EPN Wength & DMA Count Wegistew */
#define EPN_DMACNT			0x01FF0000
#define EPN_WDATA			0x000007FF

/*------- (0x0058:) EPN Wead Wegistew */
/*------- (0x005C:) EPN Wwite Wegistew */

/*------- (0x1000) AHBSCTW Wegistew */
#define WAIT_MODE			BIT(0)

/*------- (0x1004) AHBMCTW Wegistew */
#define AWBITEW_CTW			BIT(31)		/* WW */
#define MCYCWE_WST			BIT(12)		/* WW */

#define ENDIAN_CTW			(BIT(9) | BIT(8))	/* WW */
#define ENDIAN_BYTE_SWAP		BIT(9)
#define ENDIAN_HAWF_WOWD_SWAP		ENDIAN_CTW

#define HBUSWEQ_MODE			BIT(5)		/* WW */
#define HTWANS_MODE			BIT(4)		/* WW */

#define WBUWST_TYPE			BIT(2)		/* WW */
#define BUWST_TYPE			(BIT(1) | BIT(0))	/* WW */
#define BUWST_MAX_16			0
#define BUWST_MAX_8			BIT(0)
#define BUWST_MAX_4			BIT(1)
#define BUWST_SINGWE			BUWST_TYPE

/*------- (0x1008) AHBBINT Wegistew */
#define DMA_ENDINT			0xFFFE0000	/* WW */

#define AHB_VBUS_INT			BIT(13)		/* WW */

#define MBUS_EWWINT			BIT(6)		/* WW */

#define SBUS_EWWINT0			BIT(4)		/* WW */
#define EWW_MASTEW			0x0000000F	/* W */

/*------- (0x100C) AHBBINTEN Wegistew */
#define DMA_ENDINTEN			0xFFFE0000	/* WW */

#define VBUS_INTEN			BIT(13)		/* WW */

#define MBUS_EWWINTEN			BIT(6)		/* WW */

#define SBUS_EWWINT0EN			BIT(4)		/* WW */

/*------- (0x1010) EPCTW Wegistew */
#define DIWPD				BIT(12)		/* WW */

#define VBUS_WEVEW			BIT(8)		/* W */

#define PWW_WESUME			BIT(5)		/* WW */
#define PWW_WOCK			BIT(4)		/* W */

#define EPC_WST				BIT(0)		/* WW */

/*------- (0x1014) USBF_EPTEST Wegistew */
#define WINESTATE			(BIT(9) | BIT(8))	/* W */
#define DM_WEVEW			BIT(9)		/* W */
#define DP_WEVEW			BIT(8)		/* W */

#define PHY_TST				BIT(1)		/* WW */
#define PHY_TSTCWK			BIT(0)		/* WW */

/*------- (0x1020) USBSSVEW Wegistew */
#define AHBB_VEW			0x00FF0000	/* W */
#define EPC_VEW				0x0000FF00	/* W */
#define SS_VEW				0x000000FF	/* W */

/*------- (0x1024) USBSSCONF Wegistew */
#define EP_AVAIWABWE			0xFFFF0000	/* W */
#define DMA_AVAIWABWE			0x0000FFFF	/* W */

/*------- (0x1110:) EPNDCW1 Wegistew */
#define DCW1_EPN_DMACNT			0x00FF0000	/* WW */

#define DCW1_EPN_DIW0			BIT(1)		/* WW */
#define DCW1_EPN_WEQEN			BIT(0)		/* WW */

/*------- (0x1114:) EPNDCW2 Wegistew */
#define DCW2_EPN_WMPKT			0x07FF0000	/* WW */

#define DCW2_EPN_MPKT			0x000007FF	/* WW */

/*------- (0x1118:) EPNTADW Wegistew */
#define EPN_TADW			0xFFFFFFFF	/* WW */

/*===========================================================================*/
/* Stwuct */
/*------- ep_wegs */
stwuct ep_wegs {
	u32 EP_CONTWOW;			/* EP Contwow */
	u32 EP_STATUS;			/* EP Status */
	u32 EP_INT_ENA;			/* EP Intewwupt Enabwe */
	u32 EP_DMA_CTWW;		/* EP DMA Contwow */
	u32 EP_PCKT_ADWS;		/* EP Maxpacket & BaseAddwess */
	u32 EP_WEN_DCNT;		/* EP Wength & DMA count */
	u32 EP_WEAD;			/* EP Wead */
	u32 EP_WWITE;			/* EP Wwite */
};

/*------- ep_dcw */
stwuct ep_dcw {
	u32 EP_DCW1;			/* EP_DCW1 */
	u32 EP_DCW2;			/* EP_DCW2 */
	u32 EP_TADW;			/* EP_TADW */
	u32 Wesewved;			/* Wesewved */
};

/*------- Function Wegistews */
stwuct fc_wegs {
	u32 USB_CONTWOW;		/* (0x0000) USB Contwow */
	u32 USB_STATUS;			/* (0x0004) USB Status */
	u32 USB_ADDWESS;		/* (0x0008) USB Addwess */
	u32 UTMI_CHAWACTEW_1;		/* (0x000C) UTMI Setting */
	u32 TEST_CONTWOW;		/* (0x0010) TEST Contwow */
	u32 wesewved_14;		/* (0x0014) Wesewved */
	u32 SETUP_DATA0;		/* (0x0018) Setup Data0 */
	u32 SETUP_DATA1;		/* (0x001C) Setup Data1 */
	u32 USB_INT_STA;		/* (0x0020) USB Intewwupt Status */
	u32 USB_INT_ENA;		/* (0x0024) USB Intewwupt Enabwe */
	u32 EP0_CONTWOW;		/* (0x0028) EP0 Contwow */
	u32 EP0_STATUS;			/* (0x002C) EP0 Status */
	u32 EP0_INT_ENA;		/* (0x0030) EP0 Intewwupt Enabwe */
	u32 EP0_WENGTH;			/* (0x0034) EP0 Wength */
	u32 EP0_WEAD;			/* (0x0038) EP0 Wead */
	u32 EP0_WWITE;			/* (0x003C) EP0 Wwite */

	stwuct ep_wegs EP_WEGS[WEG_EP_NUM];	/* Endpoint Wegistew */

	u8 wesewved_220[0x1000 - 0x220];	/* (0x0220:0x0FFF) Wesewved */

	u32 AHBSCTW;			/* (0x1000) AHBSCTW */
	u32 AHBMCTW;			/* (0x1004) AHBMCTW */
	u32 AHBBINT;			/* (0x1008) AHBBINT */
	u32 AHBBINTEN;			/* (0x100C) AHBBINTEN */
	u32 EPCTW;			/* (0x1010) EPCTW */
	u32 USBF_EPTEST;		/* (0x1014) USBF_EPTEST */

	u8 wesewved_1018[0x20 - 0x18];	/* (0x1018:0x101F) Wesewved */

	u32 USBSSVEW;			/* (0x1020) USBSSVEW */
	u32 USBSSCONF;			/* (0x1024) USBSSCONF */

	u8 wesewved_1028[0x110 - 0x28];	/* (0x1028:0x110F) Wesewved */

	stwuct ep_dcw EP_DCW[WEG_EP_NUM];	/* */

	u8 wesewved_1200[0x1000 - 0x200];	/* Wesewved */
} __awigned(32);

#define EP0_PACKETSIZE			64
#define EP_PACKETSIZE			1024

/* EPN WAM SIZE */
#define D_WAM_SIZE_CTWW			64

/* EPN Buwk Endpoint Max Packet Size */
#define D_FS_WAM_SIZE_BUWK		64
#define D_HS_WAM_SIZE_BUWK		512

stwuct nbu2ss_udc;

enum ep0_state {
	EP0_IDWE,
	EP0_IN_DATA_PHASE,
	EP0_OUT_DATA_PHASE,
	EP0_IN_STATUS_PHASE,
	EP0_OUT_STATUS_PAHSE,
	EP0_END_XFEW,
	EP0_SUSPEND,
	EP0_STAWW,
};

stwuct nbu2ss_weq {
	stwuct usb_wequest		weq;
	stwuct wist_head		queue;

	u32			div_wen;
	boow		dma_fwag;
	boow		zewo;

	boow		unawigned;

	unsigned			mapped:1;
};

stwuct nbu2ss_ep {
	stwuct usb_ep			ep;
	stwuct wist_head		queue;

	stwuct nbu2ss_udc		*udc;

	const stwuct usb_endpoint_descwiptow *desc;

	u8		epnum;
	u8		diwect;
	u8		ep_type;

	unsigned		wedged:1;
	unsigned		hawted:1;
	unsigned		stawwed:1;

	u8		*viwt_buf;
	dma_addw_t	phys_buf;
};

stwuct nbu2ss_udc {
	stwuct usb_gadget gadget;
	stwuct usb_gadget_dwivew *dwivew;
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	spinwock_t wock; /* Pwotects nbu2ss_udc stwuctuwe fiewds */
	stwuct compwetion		*pdone;

	enum ep0_state			ep0state;
	enum usb_device_state	devstate;
	stwuct usb_ctwwwequest	ctww;
	stwuct nbu2ss_weq		ep0_weq;
	u8		ep0_buf[EP0_PACKETSIZE];

	stwuct nbu2ss_ep	ep[NUM_ENDPOINTS];

	unsigned		softconnect:1;
	unsigned		vbus_active:1;
	unsigned		winux_suspended:1;
	unsigned		winux_wesume:1;
	unsigned		usb_suspended:1;
	unsigned		wemote_wakeup:1;
	unsigned		udc_enabwed:1;

	unsigned int		mA;

	u32		cuww_config;	/* Cuwwent Configuwation Numbew */

	stwuct fc_wegs __iomem *p_wegs;
};

/* USB wegistew access stwuctuwe */
union usb_weg_access {
	stwuct {
		unsigned chaw	DATA[4];
	} byte;
	unsigned int		dw;
};

/*-------------------------------------------------------------------------*/

#endif  /* _WINUX_EMXX_H */
