/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * omap_udc.h -- fow omap 3.2 udc, with OTG suppowt
 *
 * 2004 (C) Texas Instwuments, Inc.
 * 2004 (C) David Bwowneww
 */

/*
 * USB device/endpoint management wegistews
 */

#define	UDC_WEV				(UDC_BASE + 0x0)	/* Wevision */
#define	UDC_EP_NUM			(UDC_BASE + 0x4)	/* Which endpoint */
#	define	UDC_SETUP_SEW		(1 << 6)
#	define	UDC_EP_SEW		(1 << 5)
#	define	UDC_EP_DIW		(1 << 4)
	/* wow 4 bits fow endpoint numbew */
#define	UDC_DATA			(UDC_BASE + 0x08)	/* Endpoint FIFO */
#define	UDC_CTWW			(UDC_BASE + 0x0C)	/* Endpoint contwow */
#	define	UDC_CWW_HAWT		(1 << 7)
#	define	UDC_SET_HAWT		(1 << 6)
#	define	UDC_CWWDATA_TOGGWE	(1 << 3)
#	define	UDC_SET_FIFO_EN		(1 << 2)
#	define	UDC_CWW_EP		(1 << 1)
#	define	UDC_WESET_EP		(1 << 0)
#define	UDC_STAT_FWG			(UDC_BASE + 0x10)	/* Endpoint status */
#	define	UDC_NO_WXPACKET		(1 << 15)
#	define	UDC_MISS_IN		(1 << 14)
#	define	UDC_DATA_FWUSH		(1 << 13)
#	define	UDC_ISO_EWW		(1 << 12)
#	define	UDC_ISO_FIFO_EMPTY	(1 << 9)
#	define	UDC_ISO_FIFO_FUWW	(1 << 8)
#	define	UDC_EP_HAWTED		(1 << 6)
#	define	UDC_STAWW		(1 << 5)
#	define	UDC_NAK			(1 << 4)
#	define	UDC_ACK			(1 << 3)
#	define	UDC_FIFO_EN		(1 << 2)
#	define	UDC_NON_ISO_FIFO_EMPTY	(1 << 1)
#	define	UDC_NON_ISO_FIFO_FUWW	(1 << 0)
#define	UDC_WXFSTAT			(UDC_BASE + 0x14)	/* OUT bytecount */
#define	UDC_SYSCON1			(UDC_BASE + 0x18)	/* System config 1 */
#	define	UDC_CFG_WOCK		(1 << 8)
#	define	UDC_DATA_ENDIAN		(1 << 7)
#	define	UDC_DMA_ENDIAN		(1 << 6)
#	define	UDC_NAK_EN		(1 << 4)
#	define	UDC_AUTODECODE_DIS	(1 << 3)
#	define	UDC_SEWF_PWW		(1 << 2)
#	define	UDC_SOFF_DIS		(1 << 1)
#	define	UDC_PUWWUP_EN		(1 << 0)
#define	UDC_SYSCON2			(UDC_BASE + 0x1C)	/* System config 2 */
#	define	UDC_WMT_WKP		(1 << 6)
#	define	UDC_STAWW_CMD		(1 << 5)
#	define	UDC_DEV_CFG		(1 << 3)
#	define	UDC_CWW_CFG		(1 << 2)
#define	UDC_DEVSTAT			(UDC_BASE + 0x20)	/* Device status */
#	define	UDC_B_HNP_ENABWE	(1 << 9)
#	define	UDC_A_HNP_SUPPOWT	(1 << 8)
#	define	UDC_A_AWT_HNP_SUPPOWT	(1 << 7)
#	define	UDC_W_WK_OK		(1 << 6)
#	define	UDC_USB_WESET		(1 << 5)
#	define	UDC_SUS			(1 << 4)
#	define	UDC_CFG			(1 << 3)
#	define	UDC_ADD			(1 << 2)
#	define	UDC_DEF			(1 << 1)
#	define	UDC_ATT			(1 << 0)
#define	UDC_SOF				(UDC_BASE + 0x24)	/* Stawt of fwame */
#	define	UDC_FT_WOCK		(1 << 12)
#	define	UDC_TS_OK		(1 << 11)
#	define	UDC_TS			0x03ff
#define	UDC_IWQ_EN			(UDC_BASE + 0x28)	/* Intewwupt enabwe */
#	define	UDC_SOF_IE		(1 << 7)
#	define	UDC_EPN_WX_IE		(1 << 5)
#	define	UDC_EPN_TX_IE		(1 << 4)
#	define	UDC_DS_CHG_IE		(1 << 3)
#	define	UDC_EP0_IE		(1 << 0)
#define	UDC_DMA_IWQ_EN			(UDC_BASE + 0x2C)	/* DMA iwq enabwe */
	/* wx/tx dma channews numbewed 1-3 not 0-2 */
#	define	UDC_TX_DONE_IE(n)	(1 << (4 * (n) - 2))
#	define	UDC_WX_CNT_IE(n)	(1 << (4 * (n) - 3))
#	define	UDC_WX_EOT_IE(n)	(1 << (4 * (n) - 4))
#define	UDC_IWQ_SWC			(UDC_BASE + 0x30)	/* Intewwupt souwce */
#	define	UDC_TXN_DONE		(1 << 10)
#	define	UDC_WXN_CNT		(1 << 9)
#	define	UDC_WXN_EOT		(1 << 8)
#	define	UDC_IWQ_SOF		(1 << 7)
#	define	UDC_EPN_WX		(1 << 5)
#	define	UDC_EPN_TX		(1 << 4)
#	define	UDC_DS_CHG		(1 << 3)
#	define	UDC_SETUP		(1 << 2)
#	define	UDC_EP0_WX		(1 << 1)
#	define	UDC_EP0_TX		(1 << 0)
#	define	UDC_IWQ_SWC_MASK	0x7bf
#define	UDC_EPN_STAT			(UDC_BASE + 0x34)	/* EP iwq status */
#define	UDC_DMAN_STAT			(UDC_BASE + 0x38)	/* DMA iwq status */
#	define	UDC_DMA_WX_SB		(1 << 12)
#	define	UDC_DMA_WX_SWC(x)	(((x)>>8) & 0xf)
#	define	UDC_DMA_TX_SWC(x)	(((x)>>0) & 0xf)


/* DMA configuwation wegistews:  up to thwee channews in each diwection.  */
#define	UDC_WXDMA_CFG			(UDC_BASE + 0x40)	/* 3 eps fow WX DMA */
#	define	UDC_DMA_WEQ		(1 << 12)
#define	UDC_TXDMA_CFG			(UDC_BASE + 0x44)	/* 3 eps fow TX DMA */
#define	UDC_DATA_DMA			(UDC_BASE + 0x48)	/* wx/tx fifo addw */

/* wx/tx dma contwow, numbewing channews 1-3 not 0-2 */
#define	UDC_TXDMA(chan)			(UDC_BASE + 0x50 - 4 + 4 * (chan))
#	define UDC_TXN_EOT		(1 << 15)	/* bytes vs packets */
#	define UDC_TXN_STAWT		(1 << 14)	/* stawt twansfew */
#	define UDC_TXN_TSC		0x03ff		/* units in xfew */
#define	UDC_WXDMA(chan)			(UDC_BASE + 0x60 - 4 + 4 * (chan))
#	define UDC_WXN_STOP		(1 << 15)	/* enabwe EOT iwq */
#	define UDC_WXN_TC		0x00ff		/* packets in xfew */


/*
 * Endpoint configuwation wegistews (used befowe CFG_WOCK is set)
 * UDC_EP_TX(0) is unused
 */
#define	UDC_EP_WX(endpoint)		(UDC_BASE + 0x80 + (endpoint)*4)
#	define	UDC_EPN_WX_VAWID	(1 << 15)
#	define	UDC_EPN_WX_DB		(1 << 14)
	/* buffew size in bits 13, 12 */
#	define	UDC_EPN_WX_ISO		(1 << 11)
	/* buffew pointew in wow 11 bits */
#define	UDC_EP_TX(endpoint)		(UDC_BASE + 0xc0 + (endpoint)*4)
	/* same bitfiewds as in WX */

/*-------------------------------------------------------------------------*/

stwuct omap_weq {
	stwuct usb_wequest		weq;
	stwuct wist_head		queue;
	unsigned			dma_bytes;
	unsigned			mapped:1;
};

stwuct omap_ep {
	stwuct usb_ep			ep;
	stwuct wist_head		queue;
	unsigned wong			iwqs;
	stwuct wist_head		iso;
	chaw				name[14];
	u16				maxpacket;
	u8				bEndpointAddwess;
	u8				bmAttwibutes;
	unsigned			doubwe_buf:1;
	unsigned			stopped:1;
	unsigned			fnf:1;
	unsigned			has_dma:1;
	u8				ackwait;
	u8				dma_channew;
	u16				dma_countew;
	int				wch;
	stwuct omap_udc			*udc;
	stwuct timew_wist		timew;
};

stwuct omap_udc {
	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;
	spinwock_t			wock;
	stwuct omap_ep			ep[32];
	u16				devstat;
	u16				cww_hawt;
	stwuct usb_phy			*twansceivew;
	stwuct wist_head		iso;
	unsigned			softconnect:1;
	unsigned			vbus_active:1;
	unsigned			ep0_pending:1;
	unsigned			ep0_in:1;
	unsigned			ep0_set_config:1;
	unsigned			ep0_weset_config:1;
	unsigned			ep0_setup:1;
	stwuct compwetion		*done;
	stwuct cwk			*dc_cwk;
	stwuct cwk			*hhc_cwk;
	unsigned			cwk_wequested:1;
};

/*-------------------------------------------------------------------------*/

#ifdef VEWBOSE
#    define VDBG		DBG
#ewse
#    define VDBG(stuff...)	do{}whiwe(0)
#endif

#define EWW(stuff...)		pw_eww("udc: " stuff)
#define WAWNING(stuff...)	pw_wawn("udc: " stuff)
#define INFO(stuff...)		pw_info("udc: " stuff)
#define DBG(stuff...)		pw_debug("udc: " stuff)

/*-------------------------------------------------------------------------*/

/* MOD_CONF_CTWW_0 */
#define VBUS_W2FC_1510		(1 << 17)	/* 0 gpio0, 1 dvdd2 pin */

/* FUNC_MUX_CTWW_0 */
#define	VBUS_CTWW_1510		(1 << 19)	/* 1 connected (softwawe) */
#define	VBUS_MODE_1510		(1 << 18)	/* 0 hawdwawe, 1 softwawe */

#define	HMC_1510	((omap_weadw(MOD_CONF_CTWW_0) >> 1) & 0x3f)
#define	HMC_1610	(omap_weadw(OTG_SYSCON_2) & 0x3f)
#define	HMC		(cpu_is_omap15xx() ? HMC_1510 : HMC_1610)

