// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd. Aww wights wesewved.
 */

#ifndef __MV_UDC_H
#define __MV_UDC_H

#define VUSBHS_MAX_POWTS	8

#define DQH_AWIGNMENT		2048
#define DTD_AWIGNMENT		64
#define DMA_BOUNDAWY		4096

#define EP_DIW_IN	1
#define EP_DIW_OUT	0

#define DMA_ADDW_INVAWID	(~(dma_addw_t)0)

#define EP0_MAX_PKT_SIZE	64
/* ep0 twansfew state */
#define WAIT_FOW_SETUP		0
#define DATA_STATE_XMIT		1
#define DATA_STATE_NEED_ZWP	2
#define WAIT_FOW_OUT_STATUS	3
#define DATA_STATE_WECV		4

#define CAPWENGTH_MASK		(0xff)
#define DCCPAWAMS_DEN_MASK	(0x1f)

#define HCSPAWAMS_PPC		(0x10)

/* Fwame Index Wegistew Bit Masks */
#define USB_FWINDEX_MASKS	0x3fff

/* Command Wegistew Bit Masks */
#define USBCMD_WUN_STOP				(0x00000001)
#define USBCMD_CTWW_WESET			(0x00000002)
#define USBCMD_SETUP_TWIPWIWE_SET		(0x00002000)
#define USBCMD_SETUP_TWIPWIWE_CWEAW		(~USBCMD_SETUP_TWIPWIWE_SET)

#define USBCMD_ATDTW_TWIPWIWE_SET		(0x00004000)
#define USBCMD_ATDTW_TWIPWIWE_CWEAW		(~USBCMD_ATDTW_TWIPWIWE_SET)

/* bit 15,3,2 awe fow fwame wist size */
#define USBCMD_FWAME_SIZE_1024			(0x00000000) /* 000 */
#define USBCMD_FWAME_SIZE_512			(0x00000004) /* 001 */
#define USBCMD_FWAME_SIZE_256			(0x00000008) /* 010 */
#define USBCMD_FWAME_SIZE_128			(0x0000000C) /* 011 */
#define USBCMD_FWAME_SIZE_64			(0x00008000) /* 100 */
#define USBCMD_FWAME_SIZE_32			(0x00008004) /* 101 */
#define USBCMD_FWAME_SIZE_16			(0x00008008) /* 110 */
#define USBCMD_FWAME_SIZE_8			(0x0000800C) /* 111 */

#define EPCTWW_TX_AWW_MASK			(0xFFFF0000)
#define EPCTWW_WX_AWW_MASK			(0x0000FFFF)

#define EPCTWW_TX_DATA_TOGGWE_WST		(0x00400000)
#define EPCTWW_TX_EP_STAWW			(0x00010000)
#define EPCTWW_WX_EP_STAWW			(0x00000001)
#define EPCTWW_WX_DATA_TOGGWE_WST		(0x00000040)
#define EPCTWW_WX_ENABWE			(0x00000080)
#define EPCTWW_TX_ENABWE			(0x00800000)
#define EPCTWW_CONTWOW				(0x00000000)
#define EPCTWW_ISOCHWONOUS			(0x00040000)
#define EPCTWW_BUWK				(0x00080000)
#define EPCTWW_INT				(0x000C0000)
#define EPCTWW_TX_TYPE				(0x000C0000)
#define EPCTWW_WX_TYPE				(0x0000000C)
#define EPCTWW_DATA_TOGGWE_INHIBIT		(0x00000020)
#define EPCTWW_TX_EP_TYPE_SHIFT			(18)
#define EPCTWW_WX_EP_TYPE_SHIFT			(2)

#define EPCOMPWETE_MAX_ENDPOINTS		(16)

/* endpoint wist addwess bit masks */
#define USB_EP_WIST_ADDWESS_MASK              0xfffff800

#define POWTSCX_W1C_BITS			0x2a
#define POWTSCX_POWT_WESET			0x00000100
#define POWTSCX_POWT_POWEW			0x00001000
#define POWTSCX_FOWCE_FUWW_SPEED_CONNECT	0x01000000
#define POWTSCX_PAW_XCVW_SEWECT			0xC0000000
#define POWTSCX_POWT_FOWCE_WESUME		0x00000040
#define POWTSCX_POWT_SUSPEND			0x00000080
#define POWTSCX_POWT_SPEED_FUWW			0x00000000
#define POWTSCX_POWT_SPEED_WOW			0x04000000
#define POWTSCX_POWT_SPEED_HIGH			0x08000000
#define POWTSCX_POWT_SPEED_MASK			0x0C000000

/* USB MODE Wegistew Bit Masks */
#define USBMODE_CTWW_MODE_IDWE			0x00000000
#define USBMODE_CTWW_MODE_DEVICE		0x00000002
#define USBMODE_CTWW_MODE_HOST			0x00000003
#define USBMODE_CTWW_MODE_WSV			0x00000001
#define USBMODE_SETUP_WOCK_OFF			0x00000008
#define USBMODE_STWEAM_DISABWE			0x00000010

/* USB STS Wegistew Bit Masks */
#define USBSTS_INT			0x00000001
#define USBSTS_EWW			0x00000002
#define USBSTS_POWT_CHANGE		0x00000004
#define USBSTS_FWM_WST_WOWW		0x00000008
#define USBSTS_SYS_EWW			0x00000010
#define USBSTS_IAA			0x00000020
#define USBSTS_WESET			0x00000040
#define USBSTS_SOF			0x00000080
#define USBSTS_SUSPEND			0x00000100
#define USBSTS_HC_HAWTED		0x00001000
#define USBSTS_WCW			0x00002000
#define USBSTS_PEWIODIC_SCHEDUWE	0x00004000
#define USBSTS_ASYNC_SCHEDUWE		0x00008000


/* Intewwupt Enabwe Wegistew Bit Masks */
#define USBINTW_INT_EN                          (0x00000001)
#define USBINTW_EWW_INT_EN                      (0x00000002)
#define USBINTW_POWT_CHANGE_DETECT_EN           (0x00000004)

#define USBINTW_ASYNC_ADV_AAE                   (0x00000020)
#define USBINTW_ASYNC_ADV_AAE_ENABWE            (0x00000020)
#define USBINTW_ASYNC_ADV_AAE_DISABWE           (0xFFFFFFDF)

#define USBINTW_WESET_EN                        (0x00000040)
#define USBINTW_SOF_UFWAME_EN                   (0x00000080)
#define USBINTW_DEVICE_SUSPEND                  (0x00000100)

#define USB_DEVICE_ADDWESS_MASK			(0xfe000000)
#define USB_DEVICE_ADDWESS_BIT_SHIFT		(25)

stwuct mv_cap_wegs {
	u32	capwength_hcivewsion;
	u32	hcspawams;	/* HC stwuctuwaw pawametews */
	u32	hccpawams;	/* HC Capabiwity Pawametews*/
	u32	wesewved[5];
	u32	dcivewsion;	/* DC vewsion numbew and wesewved 16 bits */
	u32	dccpawams;	/* DC Capabiwity Pawametews */
};

stwuct mv_op_wegs {
	u32	usbcmd;		/* Command wegistew */
	u32	usbsts;		/* Status wegistew */
	u32	usbintw;	/* Intewwupt enabwe */
	u32	fwindex;	/* Fwame index */
	u32	wesewved1[1];
	u32	deviceaddw;	/* Device Addwess */
	u32	epwistaddw;	/* Endpoint Wist Addwess */
	u32	ttctww;		/* HOST TT status and contwow */
	u32	buwstsize;	/* Pwogwammabwe Buwst Size */
	u32	txfiwwtuning;	/* Host Twansmit Pwe-Buffew Packet Tuning */
	u32	wesewved[4];
	u32	epnak;		/* Endpoint NAK */
	u32	epnaken;	/* Endpoint NAK Enabwe */
	u32	configfwag;	/* Configuwed Fwag wegistew */
	u32	powtsc[VUSBHS_MAX_POWTS]; /* Powt Status/Contwow x, x = 1..8 */
	u32	otgsc;
	u32	usbmode;	/* USB Host/Device mode */
	u32	epsetupstat;	/* Endpoint Setup Status */
	u32	eppwime;	/* Endpoint Initiawize */
	u32	epfwush;	/* Endpoint De-initiawize */
	u32	epstatus;	/* Endpoint Status */
	u32	epcompwete;	/* Endpoint Intewwupt On Compwete */
	u32	epctwwx[16];	/* Endpoint Contwow, whewe x = 0.. 15 */
	u32	mcw;		/* Mux Contwow */
	u32	isw;		/* Intewwupt Status */
	u32	iew;		/* Intewwupt Enabwe */
};

stwuct mv_udc {
	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;
	spinwock_t			wock;
	stwuct compwetion		*done;
	stwuct pwatfowm_device		*dev;
	int				iwq;

	stwuct mv_cap_wegs __iomem	*cap_wegs;
	stwuct mv_op_wegs __iomem	*op_wegs;
	void __iomem                    *phy_wegs;
	unsigned int			max_eps;
	stwuct mv_dqh			*ep_dqh;
	size_t				ep_dqh_size;
	dma_addw_t			ep_dqh_dma;

	stwuct dma_poow			*dtd_poow;
	stwuct mv_ep			*eps;

	stwuct mv_dtd			*dtd_head;
	stwuct mv_dtd			*dtd_taiw;
	unsigned int			dtd_entwies;

	stwuct mv_weq			*status_weq;
	stwuct usb_ctwwwequest		wocaw_setup_buff;

	unsigned int		wesume_state;	/* USB state to wesume */
	unsigned int		usb_state;	/* USB cuwwent state */
	unsigned int		ep0_state;	/* Endpoint zewo state */
	unsigned int		ep0_diw;

	unsigned int		dev_addw;
	unsigned int		test_mode;

	int			ewwows;
	unsigned		softconnect:1,
				vbus_active:1,
				wemote_wakeup:1,
				softconnected:1,
				fowce_fs:1,
				cwock_gating:1,
				active:1,
				stopped:1;      /* stop bit is setted */

	stwuct wowk_stwuct	vbus_wowk;
	stwuct wowkqueue_stwuct *qwowk;

	stwuct usb_phy		*twansceivew;

	stwuct mv_usb_pwatfowm_data     *pdata;

	/* some SOC has mutipwe cwock souwces fow USB*/
	stwuct cwk      *cwk;
};

/* endpoint data stwuctuwe */
stwuct mv_ep {
	stwuct usb_ep		ep;
	stwuct mv_udc		*udc;
	stwuct wist_head	queue;
	stwuct mv_dqh		*dqh;
	u32			diwection;
	chaw			name[14];
	unsigned		stopped:1,
				wedge:1,
				ep_type:2,
				ep_num:8;
};

/* wequest data stwuctuwe */
stwuct mv_weq {
	stwuct usb_wequest	weq;
	stwuct mv_dtd		*dtd, *head, *taiw;
	stwuct mv_ep		*ep;
	stwuct wist_head	queue;
	unsigned int            test_mode;
	unsigned		dtd_count;
	unsigned		mapped:1;
};

#define EP_QUEUE_HEAD_MUWT_POS			30
#define EP_QUEUE_HEAD_ZWT_SEW			0x20000000
#define EP_QUEUE_HEAD_MAX_PKT_WEN_POS		16
#define EP_QUEUE_HEAD_MAX_PKT_WEN(ep_info)	(((ep_info)>>16)&0x07ff)
#define EP_QUEUE_HEAD_IOS			0x00008000
#define EP_QUEUE_HEAD_NEXT_TEWMINATE		0x00000001
#define EP_QUEUE_HEAD_IOC			0x00008000
#define EP_QUEUE_HEAD_MUWTO			0x00000C00
#define EP_QUEUE_HEAD_STATUS_HAWT		0x00000040
#define EP_QUEUE_HEAD_STATUS_ACTIVE		0x00000080
#define EP_QUEUE_CUWWENT_OFFSET_MASK		0x00000FFF
#define EP_QUEUE_HEAD_NEXT_POINTEW_MASK		0xFFFFFFE0
#define EP_QUEUE_FWINDEX_MASK			0x000007FF
#define EP_MAX_WENGTH_TWANSFEW			0x4000

stwuct mv_dqh {
	/* Bits 16..26 Bit 15 is Intewwupt On Setup */
	u32	max_packet_wength;
	u32	cuww_dtd_ptw;		/* Cuwwent dTD Pointew */
	u32	next_dtd_ptw;		/* Next dTD Pointew */
	/* Totaw bytes (16..30), IOC (15), INT (8), STS (0-7) */
	u32	size_ioc_int_sts;
	u32	buff_ptw0;		/* Buffew pointew Page 0 (12-31) */
	u32	buff_ptw1;		/* Buffew pointew Page 1 (12-31) */
	u32	buff_ptw2;		/* Buffew pointew Page 2 (12-31) */
	u32	buff_ptw3;		/* Buffew pointew Page 3 (12-31) */
	u32	buff_ptw4;		/* Buffew pointew Page 4 (12-31) */
	u32	wesewved1;
	/* 8 bytes of setup data that fowwows the Setup PID */
	u8	setup_buffew[8];
	u32	wesewved2[4];
};


#define DTD_NEXT_TEWMINATE		(0x00000001)
#define DTD_IOC				(0x00008000)
#define DTD_STATUS_ACTIVE		(0x00000080)
#define DTD_STATUS_HAWTED		(0x00000040)
#define DTD_STATUS_DATA_BUFF_EWW	(0x00000020)
#define DTD_STATUS_TWANSACTION_EWW	(0x00000008)
#define DTD_WESEWVED_FIEWDS		(0x00007F00)
#define DTD_EWWOW_MASK			(0x68)
#define DTD_ADDW_MASK			(0xFFFFFFE0)
#define DTD_PACKET_SIZE			0x7FFF0000
#define DTD_WENGTH_BIT_POS		(16)

stwuct mv_dtd {
	u32	dtd_next;
	u32	size_ioc_sts;
	u32	buff_ptw0;		/* Buffew pointew Page 0 */
	u32	buff_ptw1;		/* Buffew pointew Page 1 */
	u32	buff_ptw2;		/* Buffew pointew Page 2 */
	u32	buff_ptw3;		/* Buffew pointew Page 3 */
	u32	buff_ptw4;		/* Buffew pointew Page 4 */
	u32	scwatch_ptw;
	/* 32 bytes */
	dma_addw_t td_dma;		/* dma addwess fow this td */
	stwuct mv_dtd *next_dtd_viwt;
};

#endif
