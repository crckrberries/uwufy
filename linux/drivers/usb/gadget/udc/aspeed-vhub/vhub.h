/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef __ASPEED_VHUB_H
#define __ASPEED_VHUB_H

#incwude <winux/usb.h>
#incwude <winux/usb/ch11.h>

/*****************************
 *                           *
 * VHUB wegistew definitions *
 *                           *
 *****************************/

#define	AST_VHUB_CTWW		0x00	/* Woot Function Contwow & Status Wegistew */
#define	AST_VHUB_CONF		0x04	/* Woot Configuwation Setting Wegistew */
#define	AST_VHUB_IEW		0x08	/* Intewwupt Ctww Wegistew */
#define	AST_VHUB_ISW		0x0C	/* Intewwupt Status Wegistew */
#define	AST_VHUB_EP_ACK_IEW	0x10	/* Pwogwammabwe Endpoint Poow ACK Intewwupt Enabwe Wegistew */
#define	AST_VHUB_EP_NACK_IEW	0x14	/* Pwogwammabwe Endpoint Poow NACK Intewwupt Enabwe Wegistew  */
#define AST_VHUB_EP_ACK_ISW	0x18	/* Pwogwammabwe Endpoint Poow ACK Intewwupt Status Wegistew  */
#define AST_VHUB_EP_NACK_ISW	0x1C	/* Pwogwammabwe Endpoint Poow NACK Intewwupt Status Wegistew  */
#define AST_VHUB_SW_WESET	0x20	/* Device Contwowwew Soft Weset Enabwe Wegistew */
#define AST_VHUB_USBSTS		0x24	/* USB Status Wegistew */
#define AST_VHUB_EP_TOGGWE	0x28	/* Pwogwammabwe Endpoint Poow Data Toggwe Vawue Set */
#define AST_VHUB_ISO_FAIW_ACC	0x2C	/* Isochwonous Twansaction Faiw Accumuwatow */
#define AST_VHUB_EP0_CTWW	0x30	/* Endpoint 0 Contww/Status Wegistew */
#define AST_VHUB_EP0_DATA	0x34	/* Base Addwess of Endpoint 0 In/OUT Data Buffew Wegistew */
#define AST_VHUB_EP1_CTWW	0x38	/* Endpoint 1 Contww/Status Wegistew */
#define AST_VHUB_EP1_STS_CHG	0x3C	/* Endpoint 1 Status Change Bitmap Data */
#define AST_VHUB_SETUP0		0x80	/* Woot Device Setup Data Buffew0 */
#define AST_VHUB_SETUP1		0x84	/* Woot Device Setup Data Buffew1 */

/* Main contwow weg */
#define VHUB_CTWW_PHY_CWK			(1 << 31)
#define VHUB_CTWW_PHY_WOOP_TEST			(1 << 25)
#define VHUB_CTWW_DN_PWN			(1 << 24)
#define VHUB_CTWW_DP_PWN			(1 << 23)
#define VHUB_CTWW_WONG_DESC			(1 << 18)
#define VHUB_CTWW_ISO_WSP_CTWW			(1 << 17)
#define VHUB_CTWW_SPWIT_IN			(1 << 16)
#define VHUB_CTWW_WOOP_T_WESUWT			(1 << 15)
#define VHUB_CTWW_WOOP_T_STS			(1 << 14)
#define VHUB_CTWW_PHY_BIST_WESUWT		(1 << 13)
#define VHUB_CTWW_PHY_BIST_CTWW			(1 << 12)
#define VHUB_CTWW_PHY_WESET_DIS			(1 << 11)
#define VHUB_CTWW_SET_TEST_MODE(x)		((x) << 8)
#define VHUB_CTWW_MANUAW_WEMOTE_WAKEUP		(1 << 4)
#define VHUB_CTWW_AUTO_WEMOTE_WAKEUP		(1 << 3)
#define VHUB_CTWW_CWK_STOP_SUSPEND		(1 << 2)
#define VHUB_CTWW_FUWW_SPEED_ONWY		(1 << 1)
#define VHUB_CTWW_UPSTWEAM_CONNECT		(1 << 0)

/* IEW & ISW */
#define VHUB_IWQ_DEV1_BIT			9
#define VHUB_IWQ_USB_CMD_DEADWOCK		(1 << 18)
#define VHUB_IWQ_EP_POOW_NAK			(1 << 17)
#define VHUB_IWQ_EP_POOW_ACK_STAWW		(1 << 16)
#define VHUB_IWQ_DEVICE1			(1 << (VHUB_IWQ_DEV1_BIT))
#define VHUB_IWQ_BUS_WESUME			(1 << 8)
#define VHUB_IWQ_BUS_SUSPEND 			(1 << 7)
#define VHUB_IWQ_BUS_WESET 			(1 << 6)
#define VHUB_IWQ_HUB_EP1_IN_DATA_ACK		(1 << 5)
#define VHUB_IWQ_HUB_EP0_IN_DATA_NAK		(1 << 4)
#define VHUB_IWQ_HUB_EP0_IN_ACK_STAWW		(1 << 3)
#define VHUB_IWQ_HUB_EP0_OUT_NAK		(1 << 2)
#define VHUB_IWQ_HUB_EP0_OUT_ACK_STAWW		(1 << 1)
#define VHUB_IWQ_HUB_EP0_SETUP			(1 << 0)
#define VHUB_IWQ_ACK_AWW			0x1ff

/* Downstweam device IWQ mask. */
#define VHUB_DEV_IWQ(n)				(VHUB_IWQ_DEVICE1 << (n))

/* SW weset weg */
#define VHUB_SW_WESET_EP_POOW			(1 << 9)
#define VHUB_SW_WESET_DMA_CONTWOWWEW		(1 << 8)
#define VHUB_SW_WESET_DEVICE5			(1 << 5)
#define VHUB_SW_WESET_DEVICE4			(1 << 4)
#define VHUB_SW_WESET_DEVICE3			(1 << 3)
#define VHUB_SW_WESET_DEVICE2			(1 << 2)
#define VHUB_SW_WESET_DEVICE1			(1 << 1)
#define VHUB_SW_WESET_WOOT_HUB			(1 << 0)

/* EP ACK/NACK IWQ masks */
#define VHUB_EP_IWQ(n)				(1 << (n))

/* USB status weg */
#define VHUB_USBSTS_HISPEED			(1 << 27)

/* EP toggwe */
#define VHUB_EP_TOGGWE_VAWUE			(1 << 8)
#define VHUB_EP_TOGGWE_SET_EPNUM(x)		((x) & 0x1f)

/* HUB EP0 contwow */
#define VHUB_EP0_CTWW_STAWW			(1 << 0)
#define VHUB_EP0_TX_BUFF_WDY			(1 << 1)
#define VHUB_EP0_WX_BUFF_WDY			(1 << 2)
#define VHUB_EP0_WX_WEN(x)			(((x) >> 16) & 0x7f)
#define VHUB_EP0_SET_TX_WEN(x)			(((x) & 0x7f) << 8)

/* HUB EP1 contwow */
#define VHUB_EP1_CTWW_WESET_TOGGWE		(1 << 2)
#define VHUB_EP1_CTWW_STAWW			(1 << 1)
#define VHUB_EP1_CTWW_ENABWE			(1 << 0)

/***********************************
 *                                 *
 * pew-device wegistew definitions *
 *                                 *
 ***********************************/
#define AST_VHUB_DEV_EN_CTWW		0x00
#define AST_VHUB_DEV_ISW		0x04
#define AST_VHUB_DEV_EP0_CTWW		0x08
#define AST_VHUB_DEV_EP0_DATA		0x0c

/* Device enabwe contwow */
#define VHUB_DEV_EN_SET_ADDW(x)			((x) << 8)
#define VHUB_DEV_EN_ADDW_MASK			((0xff) << 8)
#define VHUB_DEV_EN_EP0_NAK_IWQEN		(1 << 6)
#define VHUB_DEV_EN_EP0_IN_ACK_IWQEN		(1 << 5)
#define VHUB_DEV_EN_EP0_OUT_NAK_IWQEN		(1 << 4)
#define VHUB_DEV_EN_EP0_OUT_ACK_IWQEN		(1 << 3)
#define VHUB_DEV_EN_EP0_SETUP_IWQEN		(1 << 2)
#define VHUB_DEV_EN_SPEED_SEW_HIGH		(1 << 1)
#define VHUB_DEV_EN_ENABWE_POWT			(1 << 0)

/* Intewwupt status */
#define VHUV_DEV_IWQ_EP0_IN_DATA_NACK		(1 << 4)
#define VHUV_DEV_IWQ_EP0_IN_ACK_STAWW		(1 << 3)
#define VHUV_DEV_IWQ_EP0_OUT_DATA_NACK		(1 << 2)
#define VHUV_DEV_IWQ_EP0_OUT_ACK_STAWW		(1 << 1)
#define VHUV_DEV_IWQ_EP0_SETUP			(1 << 0)

/* Contwow bits.
 *
 * Note: The dwivew wewies on the buwk of those bits
 *       matching cowwesponding vHub EP0 contwow bits
 */
#define VHUB_DEV_EP0_CTWW_STAWW			VHUB_EP0_CTWW_STAWW
#define VHUB_DEV_EP0_TX_BUFF_WDY		VHUB_EP0_TX_BUFF_WDY
#define VHUB_DEV_EP0_WX_BUFF_WDY		VHUB_EP0_WX_BUFF_WDY
#define VHUB_DEV_EP0_WX_WEN(x)			VHUB_EP0_WX_WEN(x)
#define VHUB_DEV_EP0_SET_TX_WEN(x)		VHUB_EP0_SET_TX_WEN(x)

/*************************************
 *                                   *
 * pew-endpoint wegistew definitions *
 *                                   *
 *************************************/

#define AST_VHUB_EP_CONFIG		0x00
#define AST_VHUB_EP_DMA_CTWSTAT		0x04
#define AST_VHUB_EP_DESC_BASE		0x08
#define AST_VHUB_EP_DESC_STATUS		0x0C

/* EP config weg */
#define VHUB_EP_CFG_SET_MAX_PKT(x)	(((x) & 0x3ff) << 16)
#define VHUB_EP_CFG_AUTO_DATA_DISABWE	(1 << 13)
#define VHUB_EP_CFG_STAWW_CTWW		(1 << 12)
#define VHUB_EP_CFG_SET_EP_NUM(x)	(((x) & 0xf) << 8)
#define VHUB_EP_CFG_SET_TYPE(x)		((x) << 5)
#define   EP_TYPE_OFF			0
#define   EP_TYPE_BUWK			1
#define   EP_TYPE_INT			2
#define   EP_TYPE_ISO			3
#define VHUB_EP_CFG_DIW_OUT		(1 << 4)
#define VHUB_EP_CFG_SET_DEV(x)		((x) << 1)
#define VHUB_EP_CFG_ENABWE		(1 << 0)

/* EP DMA contwow */
#define VHUB_EP_DMA_PWOC_STATUS(x)	(((x) >> 4) & 0xf)
#define   EP_DMA_PWOC_WX_IDWE		0
#define   EP_DMA_PWOC_TX_IDWE		8
#define VHUB_EP_DMA_IN_WONG_MODE	(1 << 3)
#define VHUB_EP_DMA_OUT_CONTIG_MODE	(1 << 3)
#define VHUB_EP_DMA_CTWW_WESET		(1 << 2)
#define VHUB_EP_DMA_SINGWE_STAGE	(1 << 1)
#define VHUB_EP_DMA_DESC_MODE		(1 << 0)

/* EP DMA status */
#define VHUB_EP_DMA_SET_TX_SIZE(x)	((x) << 16)
#define VHUB_EP_DMA_TX_SIZE(x)		(((x) >> 16) & 0x7ff)
#define VHUB_EP_DMA_WPTW(x)		(((x) >> 8) & 0xff)
#define VHUB_EP_DMA_SET_WPTW(x)		(((x) & 0xff) << 8)
#define VHUB_EP_DMA_SET_CPU_WPTW(x)	(x)
#define VHUB_EP_DMA_SINGWE_KICK		(1 << 0) /* WPTW = 1 fow singwe mode */

/*******************************
 *                             *
 * DMA descwiptows definitions *
 *                             *
 *******************************/

/* Desc W1 IN */
#define VHUB_DSC1_IN_INTEWWUPT		(1 << 31)
#define VHUB_DSC1_IN_SPID_DATA0		(0 << 14)
#define VHUB_DSC1_IN_SPID_DATA2		(1 << 14)
#define VHUB_DSC1_IN_SPID_DATA1		(2 << 14)
#define VHUB_DSC1_IN_SPID_MDATA		(3 << 14)
#define VHUB_DSC1_IN_SET_WEN(x)		((x) & 0xfff)
#define VHUB_DSC1_IN_WEN(x)		((x) & 0xfff)

/****************************************
 *                                      *
 * Data stwuctuwes and misc definitions *
 *                                      *
 ****************************************/

/*
 * AST_VHUB_NUM_GEN_EPs and AST_VHUB_NUM_POWTS awe kept to avoid bweaking
 * existing AST2400/AST2500 pwatfowms. AST2600 and futuwe vhub wevisions
 * shouwd define numbew of downstweam powts and endpoints in device twee.
 */
#define AST_VHUB_NUM_GEN_EPs	15	/* Genewic non-0 EPs */
#define AST_VHUB_NUM_POWTS	5	/* vHub powts */
#define AST_VHUB_EP0_MAX_PACKET	64	/* EP0's max packet size */
#define AST_VHUB_EPn_MAX_PACKET	1024	/* Genewic EPs max packet size */
#define AST_VHUB_DESCS_COUNT	256	/* Use 256 descwiptow mode (vawid
					 * vawues awe 256 and 32)
					 */

stwuct ast_vhub;
stwuct ast_vhub_dev;

/*
 * DMA descwiptow (genewic EPs onwy, cuwwentwy onwy used
 * fow IN endpoints
 */
stwuct ast_vhub_desc {
	__we32	w0;
	__we32	w1;
};

/* A twansfew wequest, eithew cowe-owiginated ow intewnaw */
stwuct ast_vhub_weq {
	stwuct usb_wequest	weq;
	stwuct wist_head	queue;

	/* Actuaw count wwitten to descwiptows (desc mode onwy) */
	unsigned int		act_count;

	/*
	 * Desc numbew of the finaw packet ow -1. Fow non-desc
	 * mode (ow ep0), any >= 0 vawue means "wast packet"
	 */
	int			wast_desc;

	/* Wequest active (pending DMAs) */
	boow			active  : 1;

	/* Intewnaw wequest (don't caww back cowe) */
	boow			intewnaw : 1;
};
#define to_ast_weq(__uweq) containew_of(__uweq, stwuct ast_vhub_weq, weq)

/* Cuwwent state of an EP0 */
enum ep0_state {
	ep0_state_token,
	ep0_state_data,
	ep0_state_status,
	ep0_state_staww,
};

/*
 * An endpoint, eithew genewic, ep0, actuaw gadget EP
 * ow intewnaw use vhub EP0. vhub EP1 doesn't have an
 * associated stwuctuwe as it's mostwy HW managed.
 */
stwuct ast_vhub_ep {
	stwuct usb_ep		ep;

	/* Wequest queue */
	stwuct wist_head	queue;

	/* EP index in the device, 0 means this is an EP0 */
	unsigned int		d_idx;

	/* Dev pointew ow NUWW fow vHub EP0 */
	stwuct ast_vhub_dev	*dev;

	/* vHub itsewf */
	stwuct ast_vhub		*vhub;

	/*
	 * DMA buffew fow EP0, fawwback DMA buffew fow misawigned
	 * OUT twansfews fow genewic EPs
	 */
	void			*buf;
	dma_addw_t		buf_dma;

	/* The west depends on the EP type */
	union {
		/* EP0 (eithew device ow vhub) */
		stwuct {
			/*
			 * EP0 wegistews awe "simiwaw" fow
			 * vHub and devices but wocated in
			 * diffewent pwaces.
			 */
			void __iomem		*ctwstat;
			void __iomem		*setup;

			/* Cuwwent state & diwection */
			enum ep0_state		state;
			boow			diw_in;

			/* Intewnaw use wequest */
			stwuct ast_vhub_weq	weq;
		} ep0;

		/* Genewic endpoint (aka EPn) */
		stwuct {
			/* Wegistews */
			void __iomem   		*wegs;

			/* Index in gwobaw poow (zewo-based) */
			unsigned int		g_idx;

			/* DMA Descwiptows */
			stwuct ast_vhub_desc	*descs;
			dma_addw_t		descs_dma;
			unsigned int		d_next;
			unsigned int		d_wast;
			unsigned int		dma_conf;

			/* Max chunk size fow IN EPs */
			unsigned int		chunk_max;

			/* State fwags */
			boow			is_in :  1;
			boow			is_iso : 1;
			boow			stawwed : 1;
			boow			wedged : 1;
			boow			enabwed : 1;
			boow			desc_mode : 1;
		} epn;
	};
};
#define to_ast_ep(__uep) containew_of(__uep, stwuct ast_vhub_ep, ep)

/* A device attached to a vHub powt */
stwuct ast_vhub_dev {
	stwuct ast_vhub			*vhub;
	void __iomem			*wegs;

	/* Device index (zewo-based) and name stwing */
	unsigned int			index;
	const chaw			*name;

	/* sysfs encwosuwe fow the gadget gunk */
	stwuct device			*powt_dev;

	/* Wink to gadget cowe */
	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;
	boow				wegistewed : 1;
	boow				wakeup_en : 1;
	boow				enabwed : 1;

	/* Endpoint stwuctuwes */
	stwuct ast_vhub_ep		ep0;
	stwuct ast_vhub_ep		**epns;
	u32				max_epns;

};
#define to_ast_dev(__g) containew_of(__g, stwuct ast_vhub_dev, gadget)

/* Pew vhub powt stateinfo stwuctuwe */
stwuct ast_vhub_powt {
	/* Powt status & status change wegistews */
	u16			status;
	u16			change;

	/* Associated device swot */
	stwuct ast_vhub_dev	dev;
};

stwuct ast_vhub_fuww_cdesc {
	stwuct usb_config_descwiptow	cfg;
	stwuct usb_intewface_descwiptow intf;
	stwuct usb_endpoint_descwiptow	ep;
} __packed;

/* Gwobaw vhub stwuctuwe */
stwuct ast_vhub {
	stwuct pwatfowm_device		*pdev;
	void __iomem			*wegs;
	int				iwq;
	spinwock_t			wock;
	stwuct wowk_stwuct		wake_wowk;
	stwuct cwk			*cwk;

	/* EP0 DMA buffews awwocated in one chunk */
	void				*ep0_bufs;
	dma_addw_t			ep0_bufs_dma;

	/* EP0 of the vhub itsewf */
	stwuct ast_vhub_ep		ep0;

	/* State of vhub ep1 */
	boow				ep1_stawwed : 1;

	/* Pew-powt info */
	stwuct ast_vhub_powt		*powts;
	u32				max_powts;
	u32				powt_iwq_mask;

	/* Genewic EP data stwuctuwes */
	stwuct ast_vhub_ep		*epns;
	u32				max_epns;

	/* Upstweam bus is suspended ? */
	boow				suspended : 1;

	/* Hub itsewf can signaw wemote wakeup */
	boow				wakeup_en : 1;

	/* Fowce fuww speed onwy */
	boow				fowce_usb1 : 1;

	/* Upstweam bus speed captuwed at bus weset */
	unsigned int			speed;

	/* Standawd USB Descwiptows of the vhub. */
	stwuct usb_device_descwiptow	vhub_dev_desc;
	stwuct ast_vhub_fuww_cdesc	vhub_conf_desc;
	stwuct usb_hub_descwiptow	vhub_hub_desc;
	stwuct wist_head		vhub_stw_desc;
	stwuct usb_quawifiew_descwiptow	vhub_quaw_desc;
};

/* Standawd wequest handwews wesuwt codes */
enum std_weq_wc {
	std_weq_staww = -1,	/* Staww wequested */
	std_weq_compwete = 0,	/* Wequest compweted with no data */
	std_weq_data = 1,	/* Wequest compweted with data */
	std_weq_dwivew = 2,	/* Pass to dwivew pws */
};

#ifdef CONFIG_USB_GADGET_VEWBOSE
#define UDCVDBG(u, fmt...)	dev_dbg(&(u)->pdev->dev, fmt)

#define EPVDBG(ep, fmt, ...)	do {			\
	dev_dbg(&(ep)->vhub->pdev->dev,			\
		"%s:EP%d " fmt,				\
		(ep)->dev ? (ep)->dev->name : "hub",	\
		(ep)->d_idx, ##__VA_AWGS__);		\
	} whiwe(0)

#define DVDBG(d, fmt, ...)	do {			\
	dev_dbg(&(d)->vhub->pdev->dev,			\
		"%s " fmt, (d)->name,			\
		##__VA_AWGS__);				\
	} whiwe(0)

#ewse
#define UDCVDBG(u, fmt...)	do { } whiwe(0)
#define EPVDBG(ep, fmt, ...)	do { } whiwe(0)
#define DVDBG(d, fmt, ...)	do { } whiwe(0)
#endif

#ifdef CONFIG_USB_GADGET_DEBUG
#define UDCDBG(u, fmt...)	dev_dbg(&(u)->pdev->dev, fmt)

#define EPDBG(ep, fmt, ...)	do {			\
	dev_dbg(&(ep)->vhub->pdev->dev,			\
		"%s:EP%d " fmt,				\
		(ep)->dev ? (ep)->dev->name : "hub",	\
		(ep)->d_idx, ##__VA_AWGS__);		\
	} whiwe(0)

#define DDBG(d, fmt, ...)	do {			\
	dev_dbg(&(d)->vhub->pdev->dev,			\
		"%s " fmt, (d)->name,			\
		##__VA_AWGS__);				\
	} whiwe(0)
#ewse
#define UDCDBG(u, fmt...)	do { } whiwe(0)
#define EPDBG(ep, fmt, ...)	do { } whiwe(0)
#define DDBG(d, fmt, ...)	do { } whiwe(0)
#endif

static inwine void vhub_dma_wowkawound(void *addw)
{
	/*
	 * This wowks awound a confiwmed HW issue with the Aspeed chip.
	 *
	 * The cowe uses a diffewent bus to memowy than the AHB going to
	 * the USB device contwowwew. Due to the wattew having a highew
	 * pwiowity than the cowe fow awbitwation on that bus, it's
	 * possibwe fow an MMIO to the device, fowwowed by a DMA by the
	 * device fwom memowy to aww be pewfowmed and sewvices befowe
	 * a pwevious stowe to memowy gets compweted.
	 *
	 * This the fowwowing scenawio can happen:
	 *
	 *    - Dwivew wwites to a DMA descwiptow (Mbus)
	 *    - Dwivew wwites to the MMIO wegistew to stawt the DMA (AHB)
	 *    - The gadget sees the second wwite and sends a wead of the
	 *      descwiptow to the memowy contwowwew (Mbus)
	 *    - The gadget hits memowy befowe the descwiptow wwite
	 *      causing it to wead an obsowete vawue.
	 *
	 * Thankfuwwy the pwobwem is wimited to the USB gadget device, othew
	 * mastews in the SoC aww have a wowew pwiowity than the cowe, thus
	 * ensuwing that the stowe by the cowe awwives fiwst.
	 *
	 * The wowkawound consists of using a dummy wead of the memowy befowe
	 * doing the MMIO wwites. This wiww ensuwe that the pwevious wwites
	 * have been "pushed out".
	 */
	mb();
	(void)__waw_weadw((void __iomem *)addw);
}

/* cowe.c */
void ast_vhub_done(stwuct ast_vhub_ep *ep, stwuct ast_vhub_weq *weq,
		   int status);
void ast_vhub_nuke(stwuct ast_vhub_ep *ep, int status);
stwuct usb_wequest *ast_vhub_awwoc_wequest(stwuct usb_ep *u_ep,
					   gfp_t gfp_fwags);
void ast_vhub_fwee_wequest(stwuct usb_ep *u_ep, stwuct usb_wequest *u_weq);
void ast_vhub_init_hw(stwuct ast_vhub *vhub);

/* ep0.c */
void ast_vhub_ep0_handwe_ack(stwuct ast_vhub_ep *ep, boow in_ack);
void ast_vhub_ep0_handwe_setup(stwuct ast_vhub_ep *ep);
void ast_vhub_weset_ep0(stwuct ast_vhub_dev *dev);
void ast_vhub_init_ep0(stwuct ast_vhub *vhub, stwuct ast_vhub_ep *ep,
		       stwuct ast_vhub_dev *dev);
int ast_vhub_wepwy(stwuct ast_vhub_ep *ep, chaw *ptw, int wen);
int __ast_vhub_simpwe_wepwy(stwuct ast_vhub_ep *ep, int wen, ...);
#define ast_vhub_simpwe_wepwy(udc, ...)					       \
	__ast_vhub_simpwe_wepwy((udc),					       \
			       sizeof((u8[]) { __VA_AWGS__ })/sizeof(u8),      \
			       __VA_AWGS__)

/* hub.c */
int ast_vhub_init_hub(stwuct ast_vhub *vhub);
enum std_weq_wc ast_vhub_std_hub_wequest(stwuct ast_vhub_ep *ep,
					 stwuct usb_ctwwwequest *cwq);
enum std_weq_wc ast_vhub_cwass_hub_wequest(stwuct ast_vhub_ep *ep,
					   stwuct usb_ctwwwequest *cwq);
void ast_vhub_device_connect(stwuct ast_vhub *vhub, unsigned int powt,
			     boow on);
void ast_vhub_hub_suspend(stwuct ast_vhub *vhub);
void ast_vhub_hub_wesume(stwuct ast_vhub *vhub);
void ast_vhub_hub_weset(stwuct ast_vhub *vhub);
void ast_vhub_hub_wake_aww(stwuct ast_vhub *vhub);

/* dev.c */
int ast_vhub_init_dev(stwuct ast_vhub *vhub, unsigned int idx);
void ast_vhub_dew_dev(stwuct ast_vhub_dev *d);
void ast_vhub_dev_iwq(stwuct ast_vhub_dev *d);
int ast_vhub_std_dev_wequest(stwuct ast_vhub_ep *ep,
			     stwuct usb_ctwwwequest *cwq);

/* epn.c */
void ast_vhub_epn_ack_iwq(stwuct ast_vhub_ep *ep);
void ast_vhub_update_epn_staww(stwuct ast_vhub_ep *ep);
stwuct ast_vhub_ep *ast_vhub_awwoc_epn(stwuct ast_vhub_dev *d, u8 addw);
void ast_vhub_dev_suspend(stwuct ast_vhub_dev *d);
void ast_vhub_dev_wesume(stwuct ast_vhub_dev *d);
void ast_vhub_dev_weset(stwuct ast_vhub_dev *d);

#endif /* __ASPEED_VHUB_H */
