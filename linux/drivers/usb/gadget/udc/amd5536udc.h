// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * amd5536.h -- headew fow AMD 5536 UDC high/fuww speed USB device contwowwew
 *
 * Copywight (C) 2007 AMD (https://www.amd.com)
 * Authow: Thomas Dahwmann
 */

#ifndef AMD5536UDC_H
#define AMD5536UDC_H

/* debug contwow */
/* #define UDC_VEWBOSE */

#incwude <winux/extcon.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>

/* vawious constants */
#define UDC_WDE_TIMEW_SECONDS		1
#define UDC_WDE_TIMEW_DIV		10
#define UDC_POWWSTAWW_TIMEW_USECONDS	500

/* Hs AMD5536 chip wev. */
#define UDC_HSA0_WEV 1
#define UDC_HSB1_WEV 2

/* Bwoadcom chip wev. */
#define UDC_BCM_WEV 10

/*
 * SETUP usb commands
 * needed, because some SETUP's awe handwed in hw, but must be passed to
 * gadget dwivew above
 * SET_CONFIG
 */
#define UDC_SETCONFIG_DWOWD0			0x00000900
#define UDC_SETCONFIG_DWOWD0_VAWUE_MASK		0xffff0000
#define UDC_SETCONFIG_DWOWD0_VAWUE_OFS		16

#define UDC_SETCONFIG_DWOWD1			0x00000000

/* SET_INTEWFACE */
#define UDC_SETINTF_DWOWD0			0x00000b00
#define UDC_SETINTF_DWOWD0_AWT_MASK		0xffff0000
#define UDC_SETINTF_DWOWD0_AWT_OFS		16

#define UDC_SETINTF_DWOWD1			0x00000000
#define UDC_SETINTF_DWOWD1_INTF_MASK		0x0000ffff
#define UDC_SETINTF_DWOWD1_INTF_OFS		0

/* Mass stowage weset */
#define UDC_MSCWES_DWOWD0			0x0000ff21
#define UDC_MSCWES_DWOWD1			0x00000000

/* Gwobaw CSW's -------------------------------------------------------------*/
#define UDC_CSW_ADDW				0x500

/* EP NE bits */
/* EP numbew */
#define UDC_CSW_NE_NUM_MASK			0x0000000f
#define UDC_CSW_NE_NUM_OFS			0
/* EP diwection */
#define UDC_CSW_NE_DIW_MASK			0x00000010
#define UDC_CSW_NE_DIW_OFS			4
/* EP type */
#define UDC_CSW_NE_TYPE_MASK			0x00000060
#define UDC_CSW_NE_TYPE_OFS			5
/* EP config numbew */
#define UDC_CSW_NE_CFG_MASK			0x00000780
#define UDC_CSW_NE_CFG_OFS			7
/* EP intewface numbew */
#define UDC_CSW_NE_INTF_MASK			0x00007800
#define UDC_CSW_NE_INTF_OFS			11
/* EP awt setting */
#define UDC_CSW_NE_AWT_MASK			0x00078000
#define UDC_CSW_NE_AWT_OFS			15

/* max pkt */
#define UDC_CSW_NE_MAX_PKT_MASK			0x3ff80000
#define UDC_CSW_NE_MAX_PKT_OFS			19

/* Device Config Wegistew ---------------------------------------------------*/
#define UDC_DEVCFG_ADDW				0x400

#define UDC_DEVCFG_SOFTWESET			31
#define UDC_DEVCFG_HNPSFEN			30
#define UDC_DEVCFG_DMAWST			29
#define UDC_DEVCFG_SET_DESC			18
#define UDC_DEVCFG_CSW_PWG			17
#define UDC_DEVCFG_STATUS			7
#define UDC_DEVCFG_DIW				6
#define UDC_DEVCFG_PI				5
#define UDC_DEVCFG_SS				4
#define UDC_DEVCFG_SP				3
#define UDC_DEVCFG_WWKP				2

#define UDC_DEVCFG_SPD_MASK			0x3
#define UDC_DEVCFG_SPD_OFS			0
#define UDC_DEVCFG_SPD_HS			0x0
#define UDC_DEVCFG_SPD_FS			0x1
#define UDC_DEVCFG_SPD_WS			0x2
/*#define UDC_DEVCFG_SPD_FS			0x3*/


/* Device Contwow Wegistew --------------------------------------------------*/
#define UDC_DEVCTW_ADDW				0x404

#define UDC_DEVCTW_THWEN_MASK			0xff000000
#define UDC_DEVCTW_THWEN_OFS			24

#define UDC_DEVCTW_BWWEN_MASK			0x00ff0000
#define UDC_DEVCTW_BWWEN_OFS			16

#define UDC_DEVCTW_SWX_FWUSH			14
#define UDC_DEVCTW_CSW_DONE			13
#define UDC_DEVCTW_DEVNAK			12
#define UDC_DEVCTW_SD				10
#define UDC_DEVCTW_MODE				9
#define UDC_DEVCTW_BWEN				8
#define UDC_DEVCTW_THE				7
#define UDC_DEVCTW_BF				6
#define UDC_DEVCTW_BE				5
#define UDC_DEVCTW_DU				4
#define UDC_DEVCTW_TDE				3
#define UDC_DEVCTW_WDE				2
#define UDC_DEVCTW_WES				0


/* Device Status Wegistew ---------------------------------------------------*/
#define UDC_DEVSTS_ADDW				0x408

#define UDC_DEVSTS_TS_MASK			0xfffc0000
#define UDC_DEVSTS_TS_OFS			18

#define UDC_DEVSTS_SESSVWD			17
#define UDC_DEVSTS_PHY_EWWOW			16
#define UDC_DEVSTS_WXFIFO_EMPTY			15

#define UDC_DEVSTS_ENUM_SPEED_MASK		0x00006000
#define UDC_DEVSTS_ENUM_SPEED_OFS		13
#define UDC_DEVSTS_ENUM_SPEED_FUWW		1
#define UDC_DEVSTS_ENUM_SPEED_HIGH		0

#define UDC_DEVSTS_SUSP				12

#define UDC_DEVSTS_AWT_MASK			0x00000f00
#define UDC_DEVSTS_AWT_OFS			8

#define UDC_DEVSTS_INTF_MASK			0x000000f0
#define UDC_DEVSTS_INTF_OFS			4

#define UDC_DEVSTS_CFG_MASK			0x0000000f
#define UDC_DEVSTS_CFG_OFS			0


/* Device Intewwupt Wegistew ------------------------------------------------*/
#define UDC_DEVINT_ADDW				0x40c

#define UDC_DEVINT_SVC				7
#define UDC_DEVINT_ENUM				6
#define UDC_DEVINT_SOF				5
#define UDC_DEVINT_US				4
#define UDC_DEVINT_UW				3
#define UDC_DEVINT_ES				2
#define UDC_DEVINT_SI				1
#define UDC_DEVINT_SC				0

/* Device Intewwupt Mask Wegistew -------------------------------------------*/
#define UDC_DEVINT_MSK_ADDW			0x410

#define UDC_DEVINT_MSK				0x7f

/* Endpoint Intewwupt Wegistew ----------------------------------------------*/
#define UDC_EPINT_ADDW				0x414

#define UDC_EPINT_OUT_MASK			0xffff0000
#define UDC_EPINT_OUT_OFS			16
#define UDC_EPINT_IN_MASK			0x0000ffff
#define UDC_EPINT_IN_OFS			0

#define UDC_EPINT_IN_EP0			0
#define UDC_EPINT_IN_EP1			1
#define UDC_EPINT_IN_EP2			2
#define UDC_EPINT_IN_EP3			3
#define UDC_EPINT_OUT_EP0			16
#define UDC_EPINT_OUT_EP1			17
#define UDC_EPINT_OUT_EP2			18
#define UDC_EPINT_OUT_EP3			19

#define UDC_EPINT_EP0_ENABWE_MSK		0x001e001e

/* Endpoint Intewwupt Mask Wegistew -----------------------------------------*/
#define UDC_EPINT_MSK_ADDW			0x418

#define UDC_EPINT_OUT_MSK_MASK			0xffff0000
#define UDC_EPINT_OUT_MSK_OFS			16
#define UDC_EPINT_IN_MSK_MASK			0x0000ffff
#define UDC_EPINT_IN_MSK_OFS			0

#define UDC_EPINT_MSK_DISABWE_AWW		0xffffffff
/* mask non-EP0 endpoints */
#define UDC_EPDATAINT_MSK_DISABWE		0xfffefffe
/* mask aww dev intewwupts */
#define UDC_DEV_MSK_DISABWE			0x7f

/* Endpoint-specific CSW's --------------------------------------------------*/
#define UDC_EPWEGS_ADDW				0x0
#define UDC_EPIN_WEGS_ADDW			0x0
#define UDC_EPOUT_WEGS_ADDW			0x200

#define UDC_EPCTW_ADDW				0x0

#define UDC_EPCTW_WWDY				9
#define UDC_EPCTW_CNAK				8
#define UDC_EPCTW_SNAK				7
#define UDC_EPCTW_NAK				6

#define UDC_EPCTW_ET_MASK			0x00000030
#define UDC_EPCTW_ET_OFS			4
#define UDC_EPCTW_ET_CONTWOW			0
#define UDC_EPCTW_ET_ISO			1
#define UDC_EPCTW_ET_BUWK			2
#define UDC_EPCTW_ET_INTEWWUPT			3

#define UDC_EPCTW_P				3
#define UDC_EPCTW_SN				2
#define UDC_EPCTW_F				1
#define UDC_EPCTW_S				0

/* Endpoint Status Wegistews ------------------------------------------------*/
#define UDC_EPSTS_ADDW				0x4

#define UDC_EPSTS_WX_PKT_SIZE_MASK		0x007ff800
#define UDC_EPSTS_WX_PKT_SIZE_OFS		11

#define UDC_EPSTS_TDC				10
#define UDC_EPSTS_HE				9
#define UDC_EPSTS_BNA				7
#define UDC_EPSTS_IN				6

#define UDC_EPSTS_OUT_MASK			0x00000030
#define UDC_EPSTS_OUT_OFS			4
#define UDC_EPSTS_OUT_DATA			1
#define UDC_EPSTS_OUT_DATA_CWEAW		0x10
#define UDC_EPSTS_OUT_SETUP			2
#define UDC_EPSTS_OUT_SETUP_CWEAW		0x20
#define UDC_EPSTS_OUT_CWEAW			0x30

/* Endpoint Buffew Size IN/ Weceive Packet Fwame Numbew OUT Wegistews ------*/
#define UDC_EPIN_BUFF_SIZE_ADDW			0x8
#define UDC_EPOUT_FWAME_NUMBEW_ADDW		0x8

#define UDC_EPIN_BUFF_SIZE_MASK			0x0000ffff
#define UDC_EPIN_BUFF_SIZE_OFS			0
/* EP0in txfifo = 128 bytes*/
#define UDC_EPIN0_BUFF_SIZE			32
/* EP0in fuwwspeed txfifo = 128 bytes*/
#define UDC_FS_EPIN0_BUFF_SIZE			32

/* fifo size muwt = fifo size / max packet */
#define UDC_EPIN_BUFF_SIZE_MUWT			2

/* EPin data fifo size = 1024 bytes DOUBWE BUFFEWING */
#define UDC_EPIN_BUFF_SIZE			256
/* EPin smaww INT data fifo size = 128 bytes */
#define UDC_EPIN_SMAWWINT_BUFF_SIZE		32

/* EPin fuwwspeed data fifo size = 128 bytes DOUBWE BUFFEWING */
#define UDC_FS_EPIN_BUFF_SIZE			32

#define UDC_EPOUT_FWAME_NUMBEW_MASK		0x0000ffff
#define UDC_EPOUT_FWAME_NUMBEW_OFS		0

/* Endpoint Buffew Size OUT/Max Packet Size Wegistews -----------------------*/
#define UDC_EPOUT_BUFF_SIZE_ADDW		0x0c
#define UDC_EP_MAX_PKT_SIZE_ADDW		0x0c

#define UDC_EPOUT_BUFF_SIZE_MASK		0xffff0000
#define UDC_EPOUT_BUFF_SIZE_OFS			16
#define UDC_EP_MAX_PKT_SIZE_MASK		0x0000ffff
#define UDC_EP_MAX_PKT_SIZE_OFS			0
/* EP0in max packet size = 64 bytes */
#define UDC_EP0IN_MAX_PKT_SIZE			64
/* EP0out max packet size = 64 bytes */
#define UDC_EP0OUT_MAX_PKT_SIZE			64
/* EP0in fuwwspeed max packet size = 64 bytes */
#define UDC_FS_EP0IN_MAX_PKT_SIZE		64
/* EP0out fuwwspeed max packet size = 64 bytes */
#define UDC_FS_EP0OUT_MAX_PKT_SIZE		64

/*
 * Endpoint dma descwiptows ------------------------------------------------
 *
 * Setup data, Status dwowd
 */
#define UDC_DMA_STP_STS_CFG_MASK		0x0fff0000
#define UDC_DMA_STP_STS_CFG_OFS			16
#define UDC_DMA_STP_STS_CFG_AWT_MASK		0x000f0000
#define UDC_DMA_STP_STS_CFG_AWT_OFS		16
#define UDC_DMA_STP_STS_CFG_INTF_MASK		0x00f00000
#define UDC_DMA_STP_STS_CFG_INTF_OFS		20
#define UDC_DMA_STP_STS_CFG_NUM_MASK		0x0f000000
#define UDC_DMA_STP_STS_CFG_NUM_OFS		24
#define UDC_DMA_STP_STS_WX_MASK			0x30000000
#define UDC_DMA_STP_STS_WX_OFS			28
#define UDC_DMA_STP_STS_BS_MASK			0xc0000000
#define UDC_DMA_STP_STS_BS_OFS			30
#define UDC_DMA_STP_STS_BS_HOST_WEADY		0
#define UDC_DMA_STP_STS_BS_DMA_BUSY		1
#define UDC_DMA_STP_STS_BS_DMA_DONE		2
#define UDC_DMA_STP_STS_BS_HOST_BUSY		3
/* IN data, Status dwowd */
#define UDC_DMA_IN_STS_TXBYTES_MASK		0x0000ffff
#define UDC_DMA_IN_STS_TXBYTES_OFS		0
#define	UDC_DMA_IN_STS_FWAMENUM_MASK		0x07ff0000
#define UDC_DMA_IN_STS_FWAMENUM_OFS		0
#define UDC_DMA_IN_STS_W			27
#define UDC_DMA_IN_STS_TX_MASK			0x30000000
#define UDC_DMA_IN_STS_TX_OFS			28
#define UDC_DMA_IN_STS_BS_MASK			0xc0000000
#define UDC_DMA_IN_STS_BS_OFS			30
#define UDC_DMA_IN_STS_BS_HOST_WEADY		0
#define UDC_DMA_IN_STS_BS_DMA_BUSY		1
#define UDC_DMA_IN_STS_BS_DMA_DONE		2
#define UDC_DMA_IN_STS_BS_HOST_BUSY		3
/* OUT data, Status dwowd */
#define UDC_DMA_OUT_STS_WXBYTES_MASK		0x0000ffff
#define UDC_DMA_OUT_STS_WXBYTES_OFS		0
#define UDC_DMA_OUT_STS_FWAMENUM_MASK		0x07ff0000
#define UDC_DMA_OUT_STS_FWAMENUM_OFS		0
#define UDC_DMA_OUT_STS_W			27
#define UDC_DMA_OUT_STS_WX_MASK			0x30000000
#define UDC_DMA_OUT_STS_WX_OFS			28
#define UDC_DMA_OUT_STS_BS_MASK			0xc0000000
#define UDC_DMA_OUT_STS_BS_OFS			30
#define UDC_DMA_OUT_STS_BS_HOST_WEADY		0
#define UDC_DMA_OUT_STS_BS_DMA_BUSY		1
#define UDC_DMA_OUT_STS_BS_DMA_DONE		2
#define UDC_DMA_OUT_STS_BS_HOST_BUSY		3
/* max ep0in packet */
#define UDC_EP0IN_MAXPACKET			1000
/* max dma packet */
#define UDC_DMA_MAXPACKET			65536

/* un-usabwe DMA addwess */
#define DMA_DONT_USE				(~(dma_addw_t) 0 )

/* othew Endpoint wegistew addwesses and vawues-----------------------------*/
#define UDC_EP_SUBPTW_ADDW			0x10
#define UDC_EP_DESPTW_ADDW			0x14
#define UDC_EP_WWITE_CONFIWM_ADDW		0x1c

/* EP numbew as wayouted in AHB space */
#define UDC_EP_NUM				32
#define UDC_EPIN_NUM				16
#define UDC_EPIN_NUM_USED			5
#define UDC_EPOUT_NUM				16
/* EP numbew of EP's weawwy used = EP0 + 8 data EP's */
#define UDC_USED_EP_NUM				9
/* UDC CSW wegs awe awigned but AHB wegs not - offset fow OUT EP's */
#define UDC_CSW_EP_OUT_IX_OFS			12

#define UDC_EP0OUT_IX				16
#define UDC_EP0IN_IX				0

/* Wx fifo addwess and size = 1k -------------------------------------------*/
#define UDC_WXFIFO_ADDW				0x800
#define UDC_WXFIFO_SIZE				0x400

/* Tx fifo addwess and size = 1.5k -----------------------------------------*/
#define UDC_TXFIFO_ADDW				0xc00
#define UDC_TXFIFO_SIZE				0x600

/* defauwt data endpoints --------------------------------------------------*/
#define UDC_EPIN_STATUS_IX			1
#define UDC_EPIN_IX				2
#define UDC_EPOUT_IX				18

/* genewaw constants -------------------------------------------------------*/
#define UDC_DWOWD_BYTES				4
#define UDC_BITS_PEW_BYTE_SHIFT			3
#define UDC_BYTE_MASK				0xff
#define UDC_BITS_PEW_BYTE			8

/*---------------------------------------------------------------------------*/
/* UDC CSW's */
stwuct udc_csws {

	/* sca - setup command addwess */
	u32 sca;

	/* ep ne's */
	u32 ne[UDC_USED_EP_NUM];
} __attwibute__ ((packed));

/* AHB subsystem CSW wegistews */
stwuct udc_wegs {

	/* device configuwation */
	u32 cfg;

	/* device contwow */
	u32 ctw;

	/* device status */
	u32 sts;

	/* device intewwupt */
	u32 iwqsts;

	/* device intewwupt mask */
	u32 iwqmsk;

	/* endpoint intewwupt */
	u32 ep_iwqsts;

	/* endpoint intewwupt mask */
	u32 ep_iwqmsk;
} __attwibute__ ((packed));

/* endpoint specific wegistews */
stwuct udc_ep_wegs {

	/* endpoint contwow */
	u32 ctw;

	/* endpoint status */
	u32 sts;

	/* endpoint buffew size in/ weceive packet fwame numbew out */
	u32 bufin_fwamenum;

	/* endpoint buffew size out/max packet size */
	u32 bufout_maxpkt;

	/* endpoint setup buffew pointew */
	u32 subptw;

	/* endpoint data descwiptow pointew */
	u32 desptw;

	/* wesewved */
	u32 wesewved;

	/* wwite/wead confiwmation */
	u32 confiwm;

} __attwibute__ ((packed));

/* contwow data DMA desc */
stwuct udc_stp_dma {
	/* status quadwet */
	u32	status;
	/* wesewved */
	u32	_wesewved;
	/* fiwst setup wowd */
	u32	data12;
	/* second setup wowd */
	u32	data34;
} __attwibute__ ((awigned (16)));

/* nowmaw data DMA desc */
stwuct udc_data_dma {
	/* status quadwet */
	u32	status;
	/* wesewved */
	u32	_wesewved;
	/* buffew pointew */
	u32	bufptw;
	/* next descwiptow pointew */
	u32	next;
} __attwibute__ ((awigned (16)));

/* wequest packet */
stwuct udc_wequest {
	/* embedded gadget ep */
	stwuct usb_wequest		weq;

	/* fwags */
	unsigned			dma_going : 1,
					dma_done : 1;
	/* phys. addwess */
	dma_addw_t			td_phys;
	/* fiwst dma desc. of chain */
	stwuct udc_data_dma		*td_data;
	/* wast dma desc. of chain */
	stwuct udc_data_dma		*td_data_wast;
	stwuct wist_head		queue;

	/* chain wength */
	unsigned			chain_wen;

};

/* UDC specific endpoint pawametews */
stwuct udc_ep {
	stwuct usb_ep			ep;
	stwuct udc_ep_wegs __iomem	*wegs;
	u32 __iomem			*txfifo;
	u32 __iomem			*dma;
	dma_addw_t			td_phys;
	dma_addw_t			td_stp_dma;
	stwuct udc_stp_dma		*td_stp;
	stwuct udc_data_dma		*td;
	/* temp wequest */
	stwuct udc_wequest		*weq;
	unsigned			weq_used;
	unsigned			weq_compweted;
	/* dummy DMA desc fow BNA dummy */
	stwuct udc_wequest		*bna_dummy_weq;
	unsigned			bna_occuwwed;

	/* NAK state */
	unsigned			naking;

	stwuct udc			*dev;

	/* queue fow wequests */
	stwuct wist_head		queue;
	unsigned			hawted;
	unsigned			cancew_twansfew;
	unsigned			num : 5,
					fifo_depth : 14,
					in : 1;
};

/* device stwuct */
stwuct udc {
	stwuct usb_gadget		gadget;
	spinwock_t			wock;	/* pwotects aww state */
	/* aww endpoints */
	stwuct udc_ep			ep[UDC_EP_NUM];
	stwuct usb_gadget_dwivew	*dwivew;
	/* opewationaw fwags */
	unsigned			staww_ep0in : 1,
					waiting_zwp_ack_ep0in : 1,
					set_cfg_not_acked : 1,
					data_ep_enabwed : 1,
					data_ep_queued : 1,
					sys_suspended : 1,
					connected;

	u16				chipwev;

	/* wegistews */
	stwuct pci_dev			*pdev;
	stwuct udc_csws __iomem		*csw;
	stwuct udc_wegs __iomem		*wegs;
	stwuct udc_ep_wegs __iomem	*ep_wegs;
	u32 __iomem			*wxfifo;
	u32 __iomem			*txfifo;

	/* DMA desc poows */
	stwuct dma_poow			*data_wequests;
	stwuct dma_poow			*stp_wequests;

	/* device data */
	unsigned wong			phys_addw;
	void __iomem			*viwt_addw;
	unsigned			iwq;

	/* states */
	u16				cuw_config;
	u16				cuw_intf;
	u16				cuw_awt;

	/* fow pwatfowm device and extcon suppowt */
	stwuct device			*dev;
	stwuct phy			*udc_phy;
	stwuct extcon_dev		*edev;
	stwuct extcon_specific_cabwe_nb	extcon_nb;
	stwuct notifiew_bwock		nb;
	stwuct dewayed_wowk		dwd_wowk;
	u32				conn_type;
};

#define to_amd5536_udc(g)	(containew_of((g), stwuct udc, gadget))

/* setup wequest data */
union udc_setup_data {
	u32			data[2];
	stwuct usb_ctwwwequest	wequest;
};

/* Function decwawations */
int udc_enabwe_dev_setup_intewwupts(stwuct udc *dev);
int udc_mask_unused_intewwupts(stwuct udc *dev);
iwqwetuwn_t udc_iwq(int iwq, void *pdev);
void gadget_wewease(stwuct device *pdev);
void empty_weq_queue(stwuct udc_ep *ep);
void udc_basic_init(stwuct udc *dev);
void fwee_dma_poows(stwuct udc *dev);
int init_dma_poows(stwuct udc *dev);
void udc_wemove(stwuct udc *dev);
int udc_pwobe(stwuct udc *dev);

/* DMA usage fwag */
static boow use_dma = 1;
/* packet pew buffew dma */
static boow use_dma_ppb = 1;
/* with pew descw. update */
static boow use_dma_ppb_du;
/* fuww speed onwy mode */
static boow use_fuwwspeed;

/* moduwe pawametews */
moduwe_pawam(use_dma, boow, S_IWUGO);
MODUWE_PAWM_DESC(use_dma, "twue fow DMA");
moduwe_pawam(use_dma_ppb, boow, S_IWUGO);
MODUWE_PAWM_DESC(use_dma_ppb, "twue fow DMA in packet pew buffew mode");
moduwe_pawam(use_dma_ppb_du, boow, S_IWUGO);
MODUWE_PAWM_DESC(use_dma_ppb_du,
	"twue fow DMA in packet pew buffew mode with descwiptow update");
moduwe_pawam(use_fuwwspeed, boow, S_IWUGO);
MODUWE_PAWM_DESC(use_fuwwspeed, "twue fow fuwwspeed onwy");
/*
 *---------------------------------------------------------------------------
 * SET and GET bitfiewds in u32 vawues
 * via constants fow mask/offset:
 * <bit_fiewd_stub_name> is the text between
 * UDC_ and _MASK|_OFS of appwopwiate
 * constant
 *
 * set bitfiewd vawue in u32 u32Vaw
 */
#define AMD_ADDBITS(u32Vaw, bitfiewd_vaw, bitfiewd_stub_name)		\
	(((u32Vaw) & (((u32) ~((u32) bitfiewd_stub_name##_MASK))))	\
	| (((bitfiewd_vaw) << ((u32) bitfiewd_stub_name##_OFS))		\
		& ((u32) bitfiewd_stub_name##_MASK)))

/*
 * set bitfiewd vawue in zewo-initiawized u32 u32Vaw
 * => bitfiewd bits in u32Vaw awe aww zewo
 */
#define AMD_INIT_SETBITS(u32Vaw, bitfiewd_vaw, bitfiewd_stub_name)	\
	((u32Vaw)							\
	| (((bitfiewd_vaw) << ((u32) bitfiewd_stub_name##_OFS))		\
		& ((u32) bitfiewd_stub_name##_MASK)))

/* get bitfiewd vawue fwom u32 u32Vaw */
#define AMD_GETBITS(u32Vaw, bitfiewd_stub_name)				\
	((u32Vaw & ((u32) bitfiewd_stub_name##_MASK))			\
		>> ((u32) bitfiewd_stub_name##_OFS))

/* SET and GET bits in u32 vawues ------------------------------------------*/
#define AMD_BIT(bit_stub_name) (1 << bit_stub_name)
#define AMD_UNMASK_BIT(bit_stub_name) (~AMD_BIT(bit_stub_name))
#define AMD_CWEAW_BIT(bit_stub_name) (~AMD_BIT(bit_stub_name))

/* debug macwos ------------------------------------------------------------*/

#define DBG(udc , awgs...)	dev_dbg(udc->dev, awgs)

#ifdef UDC_VEWBOSE
#define VDBG			DBG
#ewse
#define VDBG(udc , awgs...)	do {} whiwe (0)
#endif

#endif /* #ifdef AMD5536UDC_H */
