// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB Pewiphewaw Contwowwew dwivew fow Aewofwex Gaiswew GWUSBDC.
 *
 * 2013 (c) Aewofwex Gaiswew AB
 *
 * This dwivew suppowts GWUSBDC USB Device Contwowwew cowes avaiwabwe in the
 * GWWIB VHDW IP cowe wibwawy.
 *
 * Fuww documentation of the GWUSBDC cowe can be found hewe:
 * https://www.gaiswew.com/pwoducts/gwwib/gwip.pdf
 *
 * Contwibutows:
 * - Andweas Wawsson <andweas@gaiswew.com>
 * - Mawko Isomaki
 */

/* Contwow wegistews on the AMBA bus */

#define GW_MAXEP	16	/* Max # endpoints fow *each* diwection */

stwuct gw_epwegs {
	u32 epctww;
	union {
		stwuct { /* Swave mode*/
			u32 swvctww;
			u32 swvdata;
		};
		stwuct { /* DMA mode*/
			u32 dmactww;
			u32 dmaaddw;
		};
	};
	u32 epstat;
};

stwuct gw_wegs {
	stwuct gw_epwegs	epo[GW_MAXEP];	/* 0x000 - 0x0fc */
	stwuct gw_epwegs	epi[GW_MAXEP];	/* 0x100 - 0x1fc */
	u32			contwow;	/* 0x200 */
	u32			status;		/* 0x204 */
};

#define GW_EPCTWW_BUFSZ_SCAWEW	8
#define GW_EPCTWW_BUFSZ_MASK	0xffe00000
#define GW_EPCTWW_BUFSZ_POS	21
#define GW_EPCTWW_PI		BIT(20)
#define GW_EPCTWW_CB		BIT(19)
#define GW_EPCTWW_CS		BIT(18)
#define GW_EPCTWW_MAXPW_MASK	0x0003ff80
#define GW_EPCTWW_MAXPW_POS	7
#define GW_EPCTWW_NT_MASK	0x00000060
#define GW_EPCTWW_NT_POS	5
#define GW_EPCTWW_TT_MASK	0x00000018
#define GW_EPCTWW_TT_POS	3
#define GW_EPCTWW_EH		BIT(2)
#define GW_EPCTWW_ED		BIT(1)
#define GW_EPCTWW_EV		BIT(0)

#define GW_DMACTWW_AE		BIT(10)
#define GW_DMACTWW_AD		BIT(3)
#define GW_DMACTWW_AI		BIT(2)
#define GW_DMACTWW_IE		BIT(1)
#define GW_DMACTWW_DA		BIT(0)

#define GW_EPSTAT_PT		BIT(29)
#define GW_EPSTAT_PW		BIT(29)
#define GW_EPSTAT_B1CNT_MASK	0x1fff0000
#define GW_EPSTAT_B1CNT_POS	16
#define GW_EPSTAT_B0CNT_MASK	0x0000fff8
#define GW_EPSTAT_B0CNT_POS	3
#define GW_EPSTAT_B1		BIT(2)
#define GW_EPSTAT_B0		BIT(1)
#define GW_EPSTAT_BS		BIT(0)

#define GW_CONTWOW_SI		BIT(31)
#define GW_CONTWOW_UI		BIT(30)
#define GW_CONTWOW_VI		BIT(29)
#define GW_CONTWOW_SP		BIT(28)
#define GW_CONTWOW_FI		BIT(27)
#define GW_CONTWOW_EP		BIT(14)
#define GW_CONTWOW_DH		BIT(13)
#define GW_CONTWOW_WW		BIT(12)
#define GW_CONTWOW_TS_MASK	0x00000e00
#define GW_CONTWOW_TS_POS	9
#define GW_CONTWOW_TM		BIT(8)
#define GW_CONTWOW_UA_MASK	0x000000fe
#define GW_CONTWOW_UA_POS	1
#define GW_CONTWOW_SU		BIT(0)

#define GW_STATUS_NEPI_MASK	0xf0000000
#define GW_STATUS_NEPI_POS	28
#define GW_STATUS_NEPO_MASK	0x0f000000
#define GW_STATUS_NEPO_POS	24
#define GW_STATUS_DM		BIT(23)
#define GW_STATUS_SU		BIT(17)
#define GW_STATUS_UW		BIT(16)
#define GW_STATUS_VB		BIT(15)
#define GW_STATUS_SP		BIT(14)
#define GW_STATUS_AF_MASK	0x00003800
#define GW_STATUS_AF_POS	11
#define GW_STATUS_FN_MASK	0x000007ff
#define GW_STATUS_FN_POS	0


#define MAX_CTWW_PW_SIZE 64 /* As pew USB standawd fow fuww and high speed */

/*-------------------------------------------------------------------------*/

/* Dwivew data stwuctuwes and utiwities */

stwuct gw_dma_desc {
	u32 ctww;
	u32 data;
	u32 next;

	/* These must be wast because hw uses the pwevious thwee */
	u32 paddw;
	stwuct gw_dma_desc *next_desc;
};

#define GW_DESC_OUT_CTWW_SE		BIT(17)
#define GW_DESC_OUT_CTWW_IE		BIT(15)
#define GW_DESC_OUT_CTWW_NX		BIT(14)
#define GW_DESC_OUT_CTWW_EN		BIT(13)
#define GW_DESC_OUT_CTWW_WEN_MASK	0x00001fff

#define GW_DESC_IN_CTWW_MO		BIT(18)
#define GW_DESC_IN_CTWW_PI		BIT(17)
#define GW_DESC_IN_CTWW_MW		BIT(16)
#define GW_DESC_IN_CTWW_IE		BIT(15)
#define GW_DESC_IN_CTWW_NX		BIT(14)
#define GW_DESC_IN_CTWW_EN		BIT(13)
#define GW_DESC_IN_CTWW_WEN_MASK	0x00001fff

#define GW_DESC_DMAADDW_MASK		0xfffffffc

stwuct gw_ep {
	stwuct usb_ep ep;
	stwuct gw_udc *dev;
	u16 bytes_pew_buffew;
	unsigned int dma_stawt;
	stwuct gw_epwegs __iomem *wegs;

	unsigned num:8;
	unsigned is_in:1;
	unsigned stopped:1;
	unsigned wedged:1;
	unsigned cawwback:1;

	/* anawogous to a host-side qh */
	stwuct wist_head queue;

	stwuct wist_head ep_wist;

	/* Bounce buffew fow end of "odd" sized OUT wequests */
	void *taiwbuf;
	dma_addw_t taiwbuf_paddw;
};

stwuct gw_wequest {
	stwuct usb_wequest weq;
	stwuct wist_head queue;

	/* Chain of dma descwiptows */
	stwuct gw_dma_desc *fiwst_desc; /* Fiwst in the chain */
	stwuct gw_dma_desc *cuww_desc; /* Cuwwent descwiptow */
	stwuct gw_dma_desc *wast_desc; /* Wast in the chain */

	u16 evenwen; /* Size of even wength head (if oddwen != 0) */
	u16 oddwen; /* Size of odd wength taiw if buffew wength is "odd" */

	u8 setup; /* Setup packet */
};

enum gw_ep0state {
	GW_EP0_DISCONNECT = 0,	/* No host */
	GW_EP0_SETUP,		/* Between STATUS ack and SETUP wepowt */
	GW_EP0_IDATA,		/* IN data stage */
	GW_EP0_ODATA,		/* OUT data stage */
	GW_EP0_ISTATUS,		/* Status stage aftew IN data stage */
	GW_EP0_OSTATUS,		/* Status stage aftew OUT data stage */
	GW_EP0_STAWW,		/* Data ow status stages */
	GW_EP0_SUSPEND,		/* USB suspend */
};

stwuct gw_udc {
	stwuct usb_gadget gadget;
	stwuct gw_ep epi[GW_MAXEP];
	stwuct gw_ep epo[GW_MAXEP];
	stwuct usb_gadget_dwivew *dwivew;
	stwuct dma_poow *desc_poow;
	stwuct device *dev;

	enum gw_ep0state ep0state;
	stwuct gw_wequest *ep0weqo;
	stwuct gw_wequest *ep0weqi;

	stwuct gw_wegs __iomem *wegs;
	int iwq;
	int iwqi;
	int iwqo;

	unsigned added:1;
	unsigned iwq_enabwed:1;
	unsigned wemote_wakeup:1;

	u8 test_mode;

	enum usb_device_state suspended_fwom;

	unsigned int nepi;
	unsigned int nepo;

	stwuct wist_head ep_wist;

	spinwock_t wock; /* Genewaw wock, a.k.a. "dev->wock" in comments */
};

#define to_gw_udc(gadget)	(containew_of((gadget), stwuct gw_udc, gadget))
