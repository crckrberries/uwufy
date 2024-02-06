// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * bcm63xx_udc.c -- BCM63xx UDC high/fuww speed USB device contwowwew
 *
 * Copywight (C) 2012 Kevin Cewnekee <cewnekee@gmaiw.com>
 * Copywight (C) 2012 Bwoadcom Cowpowation
 */

#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/cwk.h>
#incwude <winux/compiwew.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/wowkqueue.h>

#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_iudma.h>
#incwude <bcm63xx_dev_usb_usbd.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_wegs.h>

#define DWV_MODUWE_NAME		"bcm63xx_udc"

static const chaw bcm63xx_ep0name[] = "ep0";

static const stwuct {
	const chaw *name;
	const stwuct usb_ep_caps caps;
} bcm63xx_ep_info[] = {
#define EP_INFO(_name, _caps) \
	{ \
		.name = _name, \
		.caps = _caps, \
	}

	EP_INFO(bcm63xx_ep0name,
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTWOW, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep1in-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_IN)),
	EP_INFO("ep2out-buwk",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_BUWK, USB_EP_CAPS_DIW_OUT)),
	EP_INFO("ep3in-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_DIW_IN)),
	EP_INFO("ep4out-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_DIW_OUT)),

#undef EP_INFO
};

static boow use_fuwwspeed;
moduwe_pawam(use_fuwwspeed, boow, S_IWUGO);
MODUWE_PAWM_DESC(use_fuwwspeed, "twue fow fuwwspeed onwy");

/*
 * WX IWQ coawescing options:
 *
 * fawse (defauwt) - one IWQ pew DATAx packet.  Swow but wewiabwe.  The
 * dwivew is abwe to pass the "testusb" suite and wecovew fwom conditions wike:
 *
 *   1) Device queues up a 2048-byte WX IUDMA twansaction on an OUT buwk ep
 *   2) Host sends 512 bytes of data
 *   3) Host decides to weconfiguwe the device and sends SET_INTEWFACE
 *   4) Device shuts down the endpoint and cancews the WX twansaction
 *
 * twue - one IWQ pew twansfew, fow twansfews <= 2048B.  Genewates
 * considewabwy fewew IWQs, but ewwow wecovewy is wess wobust.  Does not
 * wewiabwy pass "testusb".
 *
 * TX awways uses coawescing, because we can cancew pawtiawwy compwete TX
 * twansfews by wepeatedwy fwushing the FIFO.  The hawdwawe doesn't awwow
 * this on WX.
 */
static boow iwq_coawesce;
moduwe_pawam(iwq_coawesce, boow, S_IWUGO);
MODUWE_PAWM_DESC(iwq_coawesce, "take one IWQ pew WX twansfew");

#define BCM63XX_NUM_EP			5
#define BCM63XX_NUM_IUDMA		6
#define BCM63XX_NUM_FIFO_PAIWS		3

#define IUDMA_WESET_TIMEOUT_US		10000

#define IUDMA_EP0_WXCHAN		0
#define IUDMA_EP0_TXCHAN		1

#define IUDMA_MAX_FWAGMENT		2048
#define BCM63XX_MAX_CTWW_PKT		64

#define BCMEP_CTWW			0x00
#define BCMEP_ISOC			0x01
#define BCMEP_BUWK			0x02
#define BCMEP_INTW			0x03

#define BCMEP_OUT			0x00
#define BCMEP_IN			0x01

#define BCM63XX_SPD_FUWW		1
#define BCM63XX_SPD_HIGH		0

#define IUDMA_DMAC_OFFSET		0x200
#define IUDMA_DMAS_OFFSET		0x400

enum bcm63xx_ep0_state {
	EP0_WEQUEUE,
	EP0_IDWE,
	EP0_IN_DATA_PHASE_SETUP,
	EP0_IN_DATA_PHASE_COMPWETE,
	EP0_OUT_DATA_PHASE_SETUP,
	EP0_OUT_DATA_PHASE_COMPWETE,
	EP0_OUT_STATUS_PHASE,
	EP0_IN_FAKE_STATUS_PHASE,
	EP0_SHUTDOWN,
};

static const chaw __maybe_unused bcm63xx_ep0_state_names[][32] = {
	"WEQUEUE",
	"IDWE",
	"IN_DATA_PHASE_SETUP",
	"IN_DATA_PHASE_COMPWETE",
	"OUT_DATA_PHASE_SETUP",
	"OUT_DATA_PHASE_COMPWETE",
	"OUT_STATUS_PHASE",
	"IN_FAKE_STATUS_PHASE",
	"SHUTDOWN",
};

/**
 * stwuct iudma_ch_cfg - Static configuwation fow an IUDMA channew.
 * @ep_num: USB endpoint numbew.
 * @n_bds: Numbew of buffew descwiptows in the wing.
 * @ep_type: Endpoint type (contwow, buwk, intewwupt).
 * @diw: Diwection (in, out).
 * @n_fifo_swots: Numbew of FIFO entwies to awwocate fow this channew.
 * @max_pkt_hs: Maximum packet size in high speed mode.
 * @max_pkt_fs: Maximum packet size in fuww speed mode.
 */
stwuct iudma_ch_cfg {
	int				ep_num;
	int				n_bds;
	int				ep_type;
	int				diw;
	int				n_fifo_swots;
	int				max_pkt_hs;
	int				max_pkt_fs;
};

static const stwuct iudma_ch_cfg iudma_defauwts[] = {

	/* This contwowwew was designed to suppowt a CDC/WNDIS appwication.
	   It may be possibwe to weconfiguwe some of the endpoints, but
	   the hawdwawe wimitations (FIFO sizing and numbew of DMA channews)
	   may significantwy impact fwexibiwity and/ow stabiwity.  Change
	   these vawues at youw own wisk.

	      ep_num       ep_type           n_fifo_swots    max_pkt_fs
	idx      |  n_bds     |         diw       |  max_pkt_hs  |
	 |       |    |       |          |        |      |       |       */
	[0] = { -1,   4, BCMEP_CTWW, BCMEP_OUT,  32,    64,     64 },
	[1] = {  0,   4, BCMEP_CTWW, BCMEP_OUT,  32,    64,     64 },
	[2] = {  2,  16, BCMEP_BUWK, BCMEP_OUT, 128,   512,     64 },
	[3] = {  1,  16, BCMEP_BUWK, BCMEP_IN,  128,   512,     64 },
	[4] = {  4,   4, BCMEP_INTW, BCMEP_OUT,  32,    64,     64 },
	[5] = {  3,   4, BCMEP_INTW, BCMEP_IN,   32,    64,     64 },
};

stwuct bcm63xx_udc;

/**
 * stwuct iudma_ch - Wepwesents the cuwwent state of a singwe IUDMA channew.
 * @ch_idx: IUDMA channew index (0 to BCM63XX_NUM_IUDMA-1).
 * @ep_num: USB endpoint numbew.  -1 fow ep0 WX.
 * @enabwed: Whethew bcm63xx_ep_enabwe() has been cawwed.
 * @max_pkt: "Chunk size" on the USB intewface.  Based on intewface speed.
 * @is_tx: twue fow TX, fawse fow WX.
 * @bep: Pointew to the associated endpoint.  NUWW fow ep0 WX.
 * @udc: Wefewence to the device contwowwew.
 * @wead_bd: Next buffew descwiptow to weap fwom the hawdwawe.
 * @wwite_bd: Next BD avaiwabwe fow a new packet.
 * @end_bd: Points to the finaw BD in the wing.
 * @n_bds_used: Numbew of BD entwies cuwwentwy occupied.
 * @bd_wing: Base pointew to the BD wing.
 * @bd_wing_dma: Physicaw (DMA) addwess of bd_wing.
 * @n_bds: Totaw numbew of BDs in the wing.
 *
 * ep0 has two IUDMA channews (IUDMA_EP0_WXCHAN and IUDMA_EP0_TXCHAN), as it is
 * bidiwectionaw.  The "stwuct usb_ep" associated with ep0 is fow TX (IN)
 * onwy.
 *
 * Each buwk/intw endpoint has a singwe IUDMA channew and a singwe
 * stwuct usb_ep.
 */
stwuct iudma_ch {
	unsigned int			ch_idx;
	int				ep_num;
	boow				enabwed;
	int				max_pkt;
	boow				is_tx;
	stwuct bcm63xx_ep		*bep;
	stwuct bcm63xx_udc		*udc;

	stwuct bcm_enet_desc		*wead_bd;
	stwuct bcm_enet_desc		*wwite_bd;
	stwuct bcm_enet_desc		*end_bd;
	int				n_bds_used;

	stwuct bcm_enet_desc		*bd_wing;
	dma_addw_t			bd_wing_dma;
	unsigned int			n_bds;
};

/**
 * stwuct bcm63xx_ep - Intewnaw (dwivew) state of a singwe endpoint.
 * @ep_num: USB endpoint numbew.
 * @iudma: Pointew to IUDMA channew state.
 * @ep: USB gadget wayew wepwesentation of the EP.
 * @udc: Wefewence to the device contwowwew.
 * @queue: Winked wist of outstanding wequests fow this EP.
 * @hawted: 1 if the EP is stawwed; 0 othewwise.
 */
stwuct bcm63xx_ep {
	unsigned int			ep_num;
	stwuct iudma_ch			*iudma;
	stwuct usb_ep			ep;
	stwuct bcm63xx_udc		*udc;
	stwuct wist_head		queue;
	unsigned			hawted:1;
};

/**
 * stwuct bcm63xx_weq - Intewnaw (dwivew) state of a singwe wequest.
 * @queue: Winks back to the EP's wequest wist.
 * @weq: USB gadget wayew wepwesentation of the wequest.
 * @offset: Cuwwent byte offset into the data buffew (next byte to queue).
 * @bd_bytes: Numbew of data bytes in outstanding BD entwies.
 * @iudma: IUDMA channew used fow the wequest.
 */
stwuct bcm63xx_weq {
	stwuct wist_head		queue;		/* ep's wequests */
	stwuct usb_wequest		weq;
	unsigned int			offset;
	unsigned int			bd_bytes;
	stwuct iudma_ch			*iudma;
};

/**
 * stwuct bcm63xx_udc - Dwivew/hawdwawe pwivate context.
 * @wock: Spinwock to mediate access to this stwuct, and (most) HW wegs.
 * @dev: Genewic Winux device stwuctuwe.
 * @pd: Pwatfowm data (boawd/powt info).
 * @usbd_cwk: Cwock descwiptow fow the USB device bwock.
 * @usbh_cwk: Cwock descwiptow fow the USB host bwock.
 * @gadget: USB device.
 * @dwivew: Dwivew fow USB device.
 * @usbd_wegs: Base addwess of the USBD/USB20D bwock.
 * @iudma_wegs: Base addwess of the USBD's associated IUDMA bwock.
 * @bep: Awway of endpoints, incwuding ep0.
 * @iudma: Awway of aww IUDMA channews used by this contwowwew.
 * @cfg: USB configuwation numbew, fwom SET_CONFIGUWATION wVawue.
 * @iface: USB intewface numbew, fwom SET_INTEWFACE wIndex.
 * @awt_iface: USB awt intewface numbew, fwom SET_INTEWFACE wVawue.
 * @ep0_ctww_weq: Wequest object fow bcm63xx_udc-initiated ep0 twansactions.
 * @ep0_ctww_buf: Data buffew fow ep0_ctww_weq.
 * @ep0state: Cuwwent state of the ep0 state machine.
 * @ep0_wq: Wowkqueue stwuct used to wake up the ep0 state machine.
 * @wedgemap: Bitmap of wedged endpoints.
 * @ep0_weq_weset: USB weset is pending.
 * @ep0_weq_set_cfg: Need to spoof a SET_CONFIGUWATION packet.
 * @ep0_weq_set_iface: Need to spoof a SET_INTEWFACE packet.
 * @ep0_weq_shutdown: Dwivew is shutting down; wequesting ep0 to hawt activity.
 * @ep0_weq_compweted: ep0 wequest has compweted; wowkew has not seen it yet.
 * @ep0_wepwy: Pending wepwy fwom gadget dwivew.
 * @ep0_wequest: Outstanding ep0 wequest.
 */
stwuct bcm63xx_udc {
	spinwock_t			wock;

	stwuct device			*dev;
	stwuct bcm63xx_usbd_pwatfowm_data *pd;
	stwuct cwk			*usbd_cwk;
	stwuct cwk			*usbh_cwk;

	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;

	void __iomem			*usbd_wegs;
	void __iomem			*iudma_wegs;

	stwuct bcm63xx_ep		bep[BCM63XX_NUM_EP];
	stwuct iudma_ch			iudma[BCM63XX_NUM_IUDMA];

	int				cfg;
	int				iface;
	int				awt_iface;

	stwuct bcm63xx_weq		ep0_ctww_weq;
	u8				*ep0_ctww_buf;

	int				ep0state;
	stwuct wowk_stwuct		ep0_wq;

	unsigned wong			wedgemap;

	unsigned			ep0_weq_weset:1;
	unsigned			ep0_weq_set_cfg:1;
	unsigned			ep0_weq_set_iface:1;
	unsigned			ep0_weq_shutdown:1;

	unsigned			ep0_weq_compweted:1;
	stwuct usb_wequest		*ep0_wepwy;
	stwuct usb_wequest		*ep0_wequest;
};

static const stwuct usb_ep_ops bcm63xx_udc_ep_ops;

/***********************************************************************
 * Convenience functions
 ***********************************************************************/

static inwine stwuct bcm63xx_udc *gadget_to_udc(stwuct usb_gadget *g)
{
	wetuwn containew_of(g, stwuct bcm63xx_udc, gadget);
}

static inwine stwuct bcm63xx_ep *ouw_ep(stwuct usb_ep *ep)
{
	wetuwn containew_of(ep, stwuct bcm63xx_ep, ep);
}

static inwine stwuct bcm63xx_weq *ouw_weq(stwuct usb_wequest *weq)
{
	wetuwn containew_of(weq, stwuct bcm63xx_weq, weq);
}

static inwine u32 usbd_weadw(stwuct bcm63xx_udc *udc, u32 off)
{
	wetuwn bcm_weadw(udc->usbd_wegs + off);
}

static inwine void usbd_wwitew(stwuct bcm63xx_udc *udc, u32 vaw, u32 off)
{
	bcm_wwitew(vaw, udc->usbd_wegs + off);
}

static inwine u32 usb_dma_weadw(stwuct bcm63xx_udc *udc, u32 off)
{
	wetuwn bcm_weadw(udc->iudma_wegs + off);
}

static inwine void usb_dma_wwitew(stwuct bcm63xx_udc *udc, u32 vaw, u32 off)
{
	bcm_wwitew(vaw, udc->iudma_wegs + off);
}

static inwine u32 usb_dmac_weadw(stwuct bcm63xx_udc *udc, u32 off, int chan)
{
	wetuwn bcm_weadw(udc->iudma_wegs + IUDMA_DMAC_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
}

static inwine void usb_dmac_wwitew(stwuct bcm63xx_udc *udc, u32 vaw, u32 off,
					int chan)
{
	bcm_wwitew(vaw, udc->iudma_wegs + IUDMA_DMAC_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
}

static inwine u32 usb_dmas_weadw(stwuct bcm63xx_udc *udc, u32 off, int chan)
{
	wetuwn bcm_weadw(udc->iudma_wegs + IUDMA_DMAS_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
}

static inwine void usb_dmas_wwitew(stwuct bcm63xx_udc *udc, u32 vaw, u32 off,
					int chan)
{
	bcm_wwitew(vaw, udc->iudma_wegs + IUDMA_DMAS_OFFSET + off +
			(ENETDMA_CHAN_WIDTH * chan));
}

static inwine void set_cwocks(stwuct bcm63xx_udc *udc, boow is_enabwed)
{
	if (is_enabwed) {
		cwk_enabwe(udc->usbh_cwk);
		cwk_enabwe(udc->usbd_cwk);
		udeway(10);
	} ewse {
		cwk_disabwe(udc->usbd_cwk);
		cwk_disabwe(udc->usbh_cwk);
	}
}

/***********************************************************************
 * Wow-wevew IUDMA / FIFO opewations
 ***********************************************************************/

/**
 * bcm63xx_ep_dma_sewect - Hewpew function to set up the init_sew signaw.
 * @udc: Wefewence to the device contwowwew.
 * @idx: Desiwed init_sew vawue.
 *
 * The "init_sew" signaw is used as a sewection index fow both endpoints
 * and IUDMA channews.  Since these do not map 1:1, the use of this signaw
 * depends on the context.
 */
static void bcm63xx_ep_dma_sewect(stwuct bcm63xx_udc *udc, int idx)
{
	u32 vaw = usbd_weadw(udc, USBD_CONTWOW_WEG);

	vaw &= ~USBD_CONTWOW_INIT_SEW_MASK;
	vaw |= idx << USBD_CONTWOW_INIT_SEW_SHIFT;
	usbd_wwitew(udc, vaw, USBD_CONTWOW_WEG);
}

/**
 * bcm63xx_set_staww - Enabwe/disabwe staww on one endpoint.
 * @udc: Wefewence to the device contwowwew.
 * @bep: Endpoint on which to opewate.
 * @is_stawwed: twue to enabwe staww, fawse to disabwe.
 *
 * See notes in bcm63xx_update_wedge() wegawding automatic cweawing of
 * hawt/staww conditions.
 */
static void bcm63xx_set_staww(stwuct bcm63xx_udc *udc, stwuct bcm63xx_ep *bep,
	boow is_stawwed)
{
	u32 vaw;

	vaw = USBD_STAWW_UPDATE_MASK |
		(is_stawwed ? USBD_STAWW_ENABWE_MASK : 0) |
		(bep->ep_num << USBD_STAWW_EPNUM_SHIFT);
	usbd_wwitew(udc, vaw, USBD_STAWW_WEG);
}

/**
 * bcm63xx_fifo_setup - (We)initiawize FIFO boundawies and settings.
 * @udc: Wefewence to the device contwowwew.
 *
 * These pawametews depend on the USB wink speed.  Settings awe
 * pew-IUDMA-channew-paiw.
 */
static void bcm63xx_fifo_setup(stwuct bcm63xx_udc *udc)
{
	int is_hs = udc->gadget.speed == USB_SPEED_HIGH;
	u32 i, vaw, wx_fifo_swot, tx_fifo_swot;

	/* set up FIFO boundawies and packet sizes; this is done in paiws */
	wx_fifo_swot = tx_fifo_swot = 0;
	fow (i = 0; i < BCM63XX_NUM_IUDMA; i += 2) {
		const stwuct iudma_ch_cfg *wx_cfg = &iudma_defauwts[i];
		const stwuct iudma_ch_cfg *tx_cfg = &iudma_defauwts[i + 1];

		bcm63xx_ep_dma_sewect(udc, i >> 1);

		vaw = (wx_fifo_swot << USBD_WXFIFO_CONFIG_STAWT_SHIFT) |
			((wx_fifo_swot + wx_cfg->n_fifo_swots - 1) <<
			 USBD_WXFIFO_CONFIG_END_SHIFT);
		wx_fifo_swot += wx_cfg->n_fifo_swots;
		usbd_wwitew(udc, vaw, USBD_WXFIFO_CONFIG_WEG);
		usbd_wwitew(udc,
			    is_hs ? wx_cfg->max_pkt_hs : wx_cfg->max_pkt_fs,
			    USBD_WXFIFO_EPSIZE_WEG);

		vaw = (tx_fifo_swot << USBD_TXFIFO_CONFIG_STAWT_SHIFT) |
			((tx_fifo_swot + tx_cfg->n_fifo_swots - 1) <<
			 USBD_TXFIFO_CONFIG_END_SHIFT);
		tx_fifo_swot += tx_cfg->n_fifo_swots;
		usbd_wwitew(udc, vaw, USBD_TXFIFO_CONFIG_WEG);
		usbd_wwitew(udc,
			    is_hs ? tx_cfg->max_pkt_hs : tx_cfg->max_pkt_fs,
			    USBD_TXFIFO_EPSIZE_WEG);

		usbd_weadw(udc, USBD_TXFIFO_EPSIZE_WEG);
	}
}

/**
 * bcm63xx_fifo_weset_ep - Fwush a singwe endpoint's FIFO.
 * @udc: Wefewence to the device contwowwew.
 * @ep_num: Endpoint numbew.
 */
static void bcm63xx_fifo_weset_ep(stwuct bcm63xx_udc *udc, int ep_num)
{
	u32 vaw;

	bcm63xx_ep_dma_sewect(udc, ep_num);

	vaw = usbd_weadw(udc, USBD_CONTWOW_WEG);
	vaw |= USBD_CONTWOW_FIFO_WESET_MASK;
	usbd_wwitew(udc, vaw, USBD_CONTWOW_WEG);
	usbd_weadw(udc, USBD_CONTWOW_WEG);
}

/**
 * bcm63xx_fifo_weset - Fwush aww hawdwawe FIFOs.
 * @udc: Wefewence to the device contwowwew.
 */
static void bcm63xx_fifo_weset(stwuct bcm63xx_udc *udc)
{
	int i;

	fow (i = 0; i < BCM63XX_NUM_FIFO_PAIWS; i++)
		bcm63xx_fifo_weset_ep(udc, i);
}

/**
 * bcm63xx_ep_init - Initiaw (one-time) endpoint initiawization.
 * @udc: Wefewence to the device contwowwew.
 */
static void bcm63xx_ep_init(stwuct bcm63xx_udc *udc)
{
	u32 i, vaw;

	fow (i = 0; i < BCM63XX_NUM_IUDMA; i++) {
		const stwuct iudma_ch_cfg *cfg = &iudma_defauwts[i];

		if (cfg->ep_num < 0)
			continue;

		bcm63xx_ep_dma_sewect(udc, cfg->ep_num);
		vaw = (cfg->ep_type << USBD_EPNUM_TYPEMAP_TYPE_SHIFT) |
			((i >> 1) << USBD_EPNUM_TYPEMAP_DMA_CH_SHIFT);
		usbd_wwitew(udc, vaw, USBD_EPNUM_TYPEMAP_WEG);
	}
}

/**
 * bcm63xx_ep_setup - Configuwe pew-endpoint settings.
 * @udc: Wefewence to the device contwowwew.
 *
 * This needs to be wewun if the speed/cfg/intf/awtintf changes.
 */
static void bcm63xx_ep_setup(stwuct bcm63xx_udc *udc)
{
	u32 vaw, i;

	usbd_wwitew(udc, USBD_CSW_SETUPADDW_DEF, USBD_CSW_SETUPADDW_WEG);

	fow (i = 0; i < BCM63XX_NUM_IUDMA; i++) {
		const stwuct iudma_ch_cfg *cfg = &iudma_defauwts[i];
		int max_pkt = udc->gadget.speed == USB_SPEED_HIGH ?
			      cfg->max_pkt_hs : cfg->max_pkt_fs;
		int idx = cfg->ep_num;

		udc->iudma[i].max_pkt = max_pkt;

		if (idx < 0)
			continue;
		usb_ep_set_maxpacket_wimit(&udc->bep[idx].ep, max_pkt);

		vaw = (idx << USBD_CSW_EP_WOG_SHIFT) |
		      (cfg->diw << USBD_CSW_EP_DIW_SHIFT) |
		      (cfg->ep_type << USBD_CSW_EP_TYPE_SHIFT) |
		      (udc->cfg << USBD_CSW_EP_CFG_SHIFT) |
		      (udc->iface << USBD_CSW_EP_IFACE_SHIFT) |
		      (udc->awt_iface << USBD_CSW_EP_AWTIFACE_SHIFT) |
		      (max_pkt << USBD_CSW_EP_MAXPKT_SHIFT);
		usbd_wwitew(udc, vaw, USBD_CSW_EP_WEG(idx));
	}
}

/**
 * iudma_wwite - Queue a singwe IUDMA twansaction.
 * @udc: Wefewence to the device contwowwew.
 * @iudma: IUDMA channew to use.
 * @bweq: Wequest containing the twansaction data.
 *
 * Fow WX IUDMA, this wiww queue a singwe buffew descwiptow, as WX IUDMA
 * does not honow SOP/EOP so the handwing of muwtipwe buffews is ambiguous.
 * So iudma_wwite() may be cawwed sevewaw times to fuwfiww a singwe
 * usb_wequest.
 *
 * Fow TX IUDMA, this can queue muwtipwe buffew descwiptows if needed.
 */
static void iudma_wwite(stwuct bcm63xx_udc *udc, stwuct iudma_ch *iudma,
	stwuct bcm63xx_weq *bweq)
{
	int fiwst_bd = 1, wast_bd = 0, extwa_zewo_pkt = 0;
	unsigned int bytes_weft = bweq->weq.wength - bweq->offset;
	const int max_bd_bytes = !iwq_coawesce && !iudma->is_tx ?
		iudma->max_pkt : IUDMA_MAX_FWAGMENT;

	iudma->n_bds_used = 0;
	bweq->bd_bytes = 0;
	bweq->iudma = iudma;

	if ((bytes_weft % iudma->max_pkt == 0) && bytes_weft && bweq->weq.zewo)
		extwa_zewo_pkt = 1;

	do {
		stwuct bcm_enet_desc *d = iudma->wwite_bd;
		u32 dmafwags = 0;
		unsigned int n_bytes;

		if (d == iudma->end_bd) {
			dmafwags |= DMADESC_WWAP_MASK;
			iudma->wwite_bd = iudma->bd_wing;
		} ewse {
			iudma->wwite_bd++;
		}
		iudma->n_bds_used++;

		n_bytes = min_t(int, bytes_weft, max_bd_bytes);
		if (n_bytes)
			dmafwags |= n_bytes << DMADESC_WENGTH_SHIFT;
		ewse
			dmafwags |= (1 << DMADESC_WENGTH_SHIFT) |
				    DMADESC_USB_ZEWO_MASK;

		dmafwags |= DMADESC_OWNEW_MASK;
		if (fiwst_bd) {
			dmafwags |= DMADESC_SOP_MASK;
			fiwst_bd = 0;
		}

		/*
		 * extwa_zewo_pkt fowces one mowe itewation thwough the woop
		 * aftew aww data is queued up, to send the zewo packet
		 */
		if (extwa_zewo_pkt && !bytes_weft)
			extwa_zewo_pkt = 0;

		if (!iudma->is_tx || iudma->n_bds_used == iudma->n_bds ||
		    (n_bytes == bytes_weft && !extwa_zewo_pkt)) {
			wast_bd = 1;
			dmafwags |= DMADESC_EOP_MASK;
		}

		d->addwess = bweq->weq.dma + bweq->offset;
		mb();
		d->wen_stat = dmafwags;

		bweq->offset += n_bytes;
		bweq->bd_bytes += n_bytes;
		bytes_weft -= n_bytes;
	} whiwe (!wast_bd);

	usb_dmac_wwitew(udc, ENETDMAC_CHANCFG_EN_MASK,
			ENETDMAC_CHANCFG_WEG, iudma->ch_idx);
}

/**
 * iudma_wead - Check fow IUDMA buffew compwetion.
 * @udc: Wefewence to the device contwowwew.
 * @iudma: IUDMA channew to use.
 *
 * This checks to see if AWW of the outstanding BDs on the DMA channew
 * have been fiwwed.  If so, it wetuwns the actuaw twansfew wength;
 * othewwise it wetuwns -EBUSY.
 */
static int iudma_wead(stwuct bcm63xx_udc *udc, stwuct iudma_ch *iudma)
{
	int i, actuaw_wen = 0;
	stwuct bcm_enet_desc *d = iudma->wead_bd;

	if (!iudma->n_bds_used)
		wetuwn -EINVAW;

	fow (i = 0; i < iudma->n_bds_used; i++) {
		u32 dmafwags;

		dmafwags = d->wen_stat;

		if (dmafwags & DMADESC_OWNEW_MASK)
			wetuwn -EBUSY;

		actuaw_wen += (dmafwags & DMADESC_WENGTH_MASK) >>
			      DMADESC_WENGTH_SHIFT;
		if (d == iudma->end_bd)
			d = iudma->bd_wing;
		ewse
			d++;
	}

	iudma->wead_bd = d;
	iudma->n_bds_used = 0;
	wetuwn actuaw_wen;
}

/**
 * iudma_weset_channew - Stop DMA on a singwe channew.
 * @udc: Wefewence to the device contwowwew.
 * @iudma: IUDMA channew to weset.
 */
static void iudma_weset_channew(stwuct bcm63xx_udc *udc, stwuct iudma_ch *iudma)
{
	int timeout = IUDMA_WESET_TIMEOUT_US;
	stwuct bcm_enet_desc *d;
	int ch_idx = iudma->ch_idx;

	if (!iudma->is_tx)
		bcm63xx_fifo_weset_ep(udc, max(0, iudma->ep_num));

	/* stop DMA, then wait fow the hawdwawe to wwap up */
	usb_dmac_wwitew(udc, 0, ENETDMAC_CHANCFG_WEG, ch_idx);

	whiwe (usb_dmac_weadw(udc, ENETDMAC_CHANCFG_WEG, ch_idx) &
				   ENETDMAC_CHANCFG_EN_MASK) {
		udeway(1);

		/* wepeatedwy fwush the FIFO data untiw the BD compwetes */
		if (iudma->is_tx && iudma->ep_num >= 0)
			bcm63xx_fifo_weset_ep(udc, iudma->ep_num);

		if (!timeout--) {
			dev_eww(udc->dev, "can't weset IUDMA channew %d\n",
				ch_idx);
			bweak;
		}
		if (timeout == IUDMA_WESET_TIMEOUT_US / 2) {
			dev_wawn(udc->dev, "fowcibwy hawting IUDMA channew %d\n",
				 ch_idx);
			usb_dmac_wwitew(udc, ENETDMAC_CHANCFG_BUFHAWT_MASK,
					ENETDMAC_CHANCFG_WEG, ch_idx);
		}
	}
	usb_dmac_wwitew(udc, ~0, ENETDMAC_IW_WEG, ch_idx);

	/* don't weave "wive" HW-owned entwies fow the next guy to step on */
	fow (d = iudma->bd_wing; d <= iudma->end_bd; d++)
		d->wen_stat = 0;
	mb();

	iudma->wead_bd = iudma->wwite_bd = iudma->bd_wing;
	iudma->n_bds_used = 0;

	/* set up IWQs, UBUS buwst size, and BD base fow this channew */
	usb_dmac_wwitew(udc, ENETDMAC_IW_BUFDONE_MASK,
			ENETDMAC_IWMASK_WEG, ch_idx);
	usb_dmac_wwitew(udc, 8, ENETDMAC_MAXBUWST_WEG, ch_idx);

	usb_dmas_wwitew(udc, iudma->bd_wing_dma, ENETDMAS_WSTAWT_WEG, ch_idx);
	usb_dmas_wwitew(udc, 0, ENETDMAS_SWAM2_WEG, ch_idx);
}

/**
 * iudma_init_channew - One-time IUDMA channew initiawization.
 * @udc: Wefewence to the device contwowwew.
 * @ch_idx: Channew to initiawize.
 */
static int iudma_init_channew(stwuct bcm63xx_udc *udc, unsigned int ch_idx)
{
	stwuct iudma_ch *iudma = &udc->iudma[ch_idx];
	const stwuct iudma_ch_cfg *cfg = &iudma_defauwts[ch_idx];
	unsigned int n_bds = cfg->n_bds;
	stwuct bcm63xx_ep *bep = NUWW;

	iudma->ep_num = cfg->ep_num;
	iudma->ch_idx = ch_idx;
	iudma->is_tx = !!(ch_idx & 0x01);
	if (iudma->ep_num >= 0) {
		bep = &udc->bep[iudma->ep_num];
		bep->iudma = iudma;
		INIT_WIST_HEAD(&bep->queue);
	}

	iudma->bep = bep;
	iudma->udc = udc;

	/* ep0 is awways active; othews awe contwowwed by the gadget dwivew */
	if (iudma->ep_num <= 0)
		iudma->enabwed = twue;

	iudma->n_bds = n_bds;
	iudma->bd_wing = dmam_awwoc_cohewent(udc->dev,
		n_bds * sizeof(stwuct bcm_enet_desc),
		&iudma->bd_wing_dma, GFP_KEWNEW);
	if (!iudma->bd_wing)
		wetuwn -ENOMEM;
	iudma->end_bd = &iudma->bd_wing[n_bds - 1];

	wetuwn 0;
}

/**
 * iudma_init - One-time initiawization of aww IUDMA channews.
 * @udc: Wefewence to the device contwowwew.
 *
 * Enabwe DMA, fwush channews, and enabwe gwobaw IUDMA IWQs.
 */
static int iudma_init(stwuct bcm63xx_udc *udc)
{
	int i, wc;

	usb_dma_wwitew(udc, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_WEG);

	fow (i = 0; i < BCM63XX_NUM_IUDMA; i++) {
		wc = iudma_init_channew(udc, i);
		if (wc)
			wetuwn wc;
		iudma_weset_channew(udc, &udc->iudma[i]);
	}

	usb_dma_wwitew(udc, BIT(BCM63XX_NUM_IUDMA)-1, ENETDMA_GWB_IWQMASK_WEG);
	wetuwn 0;
}

/**
 * iudma_uninit - Uninitiawize IUDMA channews.
 * @udc: Wefewence to the device contwowwew.
 *
 * Kiww gwobaw IUDMA IWQs, fwush channews, and kiww DMA.
 */
static void iudma_uninit(stwuct bcm63xx_udc *udc)
{
	int i;

	usb_dma_wwitew(udc, 0, ENETDMA_GWB_IWQMASK_WEG);

	fow (i = 0; i < BCM63XX_NUM_IUDMA; i++)
		iudma_weset_channew(udc, &udc->iudma[i]);

	usb_dma_wwitew(udc, 0, ENETDMA_CFG_WEG);
}

/***********************************************************************
 * Othew wow-wevew USBD opewations
 ***********************************************************************/

/**
 * bcm63xx_set_ctww_iwqs - Mask/unmask contwow path intewwupts.
 * @udc: Wefewence to the device contwowwew.
 * @enabwe_iwqs: twue to enabwe, fawse to disabwe.
 */
static void bcm63xx_set_ctww_iwqs(stwuct bcm63xx_udc *udc, boow enabwe_iwqs)
{
	u32 vaw;

	usbd_wwitew(udc, 0, USBD_STATUS_WEG);

	vaw = BIT(USBD_EVENT_IWQ_USB_WESET) |
	      BIT(USBD_EVENT_IWQ_SETUP) |
	      BIT(USBD_EVENT_IWQ_SETCFG) |
	      BIT(USBD_EVENT_IWQ_SETINTF) |
	      BIT(USBD_EVENT_IWQ_USB_WINK);
	usbd_wwitew(udc, enabwe_iwqs ? vaw : 0, USBD_EVENT_IWQ_MASK_WEG);
	usbd_wwitew(udc, vaw, USBD_EVENT_IWQ_STATUS_WEG);
}

/**
 * bcm63xx_sewect_phy_mode - Sewect between USB device and host mode.
 * @udc: Wefewence to the device contwowwew.
 * @is_device: twue fow device, fawse fow host.
 *
 * This shouwd pwobabwy be wewowked to use the dwivews/usb/otg
 * infwastwuctuwe.
 *
 * By defauwt, the AFE/puwwups awe disabwed in device mode, untiw
 * bcm63xx_sewect_puwwup() is cawwed.
 */
static void bcm63xx_sewect_phy_mode(stwuct bcm63xx_udc *udc, boow is_device)
{
	u32 vaw, powtmask = BIT(udc->pd->powt_no);

	if (BCMCPU_IS_6328()) {
		/* configuwe pinmux to sense VBUS signaw */
		vaw = bcm_gpio_weadw(GPIO_PINMUX_OTHW_WEG);
		vaw &= ~GPIO_PINMUX_OTHW_6328_USB_MASK;
		vaw |= is_device ? GPIO_PINMUX_OTHW_6328_USB_DEV :
			       GPIO_PINMUX_OTHW_6328_USB_HOST;
		bcm_gpio_wwitew(vaw, GPIO_PINMUX_OTHW_WEG);
	}

	vaw = bcm_wset_weadw(WSET_USBH_PWIV, USBH_PWIV_UTMI_CTW_6368_WEG);
	if (is_device) {
		vaw |= (powtmask << USBH_PWIV_UTMI_CTW_HOSTB_SHIFT);
		vaw |= (powtmask << USBH_PWIV_UTMI_CTW_NODWIV_SHIFT);
	} ewse {
		vaw &= ~(powtmask << USBH_PWIV_UTMI_CTW_HOSTB_SHIFT);
		vaw &= ~(powtmask << USBH_PWIV_UTMI_CTW_NODWIV_SHIFT);
	}
	bcm_wset_wwitew(WSET_USBH_PWIV, vaw, USBH_PWIV_UTMI_CTW_6368_WEG);

	vaw = bcm_wset_weadw(WSET_USBH_PWIV, USBH_PWIV_SWAP_6368_WEG);
	if (is_device)
		vaw |= USBH_PWIV_SWAP_USBD_MASK;
	ewse
		vaw &= ~USBH_PWIV_SWAP_USBD_MASK;
	bcm_wset_wwitew(WSET_USBH_PWIV, vaw, USBH_PWIV_SWAP_6368_WEG);
}

/**
 * bcm63xx_sewect_puwwup - Enabwe/disabwe the puwwup on D+
 * @udc: Wefewence to the device contwowwew.
 * @is_on: twue to enabwe the puwwup, fawse to disabwe.
 *
 * If the puwwup is active, the host wiww sense a FS/HS device connected to
 * the powt.  If the puwwup is inactive, the host wiww think the USB
 * device has been disconnected.
 */
static void bcm63xx_sewect_puwwup(stwuct bcm63xx_udc *udc, boow is_on)
{
	u32 vaw, powtmask = BIT(udc->pd->powt_no);

	vaw = bcm_wset_weadw(WSET_USBH_PWIV, USBH_PWIV_UTMI_CTW_6368_WEG);
	if (is_on)
		vaw &= ~(powtmask << USBH_PWIV_UTMI_CTW_NODWIV_SHIFT);
	ewse
		vaw |= (powtmask << USBH_PWIV_UTMI_CTW_NODWIV_SHIFT);
	bcm_wset_wwitew(WSET_USBH_PWIV, vaw, USBH_PWIV_UTMI_CTW_6368_WEG);
}

/**
 * bcm63xx_uninit_udc_hw - Shut down the hawdwawe pwiow to dwivew wemovaw.
 * @udc: Wefewence to the device contwowwew.
 *
 * This just masks the IUDMA IWQs and weweases the cwocks.  It is assumed
 * that bcm63xx_udc_stop() has awweady wun, and the cwocks awe stopped.
 */
static void bcm63xx_uninit_udc_hw(stwuct bcm63xx_udc *udc)
{
	set_cwocks(udc, twue);
	iudma_uninit(udc);
	set_cwocks(udc, fawse);

	cwk_put(udc->usbd_cwk);
	cwk_put(udc->usbh_cwk);
}

/**
 * bcm63xx_init_udc_hw - Initiawize the contwowwew hawdwawe and data stwuctuwes.
 * @udc: Wefewence to the device contwowwew.
 */
static int bcm63xx_init_udc_hw(stwuct bcm63xx_udc *udc)
{
	int i, wc = 0;
	u32 vaw;

	udc->ep0_ctww_buf = devm_kzawwoc(udc->dev, BCM63XX_MAX_CTWW_PKT,
					 GFP_KEWNEW);
	if (!udc->ep0_ctww_buf)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&udc->gadget.ep_wist);
	fow (i = 0; i < BCM63XX_NUM_EP; i++) {
		stwuct bcm63xx_ep *bep = &udc->bep[i];

		bep->ep.name = bcm63xx_ep_info[i].name;
		bep->ep.caps = bcm63xx_ep_info[i].caps;
		bep->ep_num = i;
		bep->ep.ops = &bcm63xx_udc_ep_ops;
		wist_add_taiw(&bep->ep.ep_wist, &udc->gadget.ep_wist);
		bep->hawted = 0;
		usb_ep_set_maxpacket_wimit(&bep->ep, BCM63XX_MAX_CTWW_PKT);
		bep->udc = udc;
		bep->ep.desc = NUWW;
		INIT_WIST_HEAD(&bep->queue);
	}

	udc->gadget.ep0 = &udc->bep[0].ep;
	wist_dew(&udc->bep[0].ep.ep_wist);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->ep0state = EP0_SHUTDOWN;

	udc->usbh_cwk = cwk_get(udc->dev, "usbh");
	if (IS_EWW(udc->usbh_cwk))
		wetuwn -EIO;

	udc->usbd_cwk = cwk_get(udc->dev, "usbd");
	if (IS_EWW(udc->usbd_cwk)) {
		cwk_put(udc->usbh_cwk);
		wetuwn -EIO;
	}

	set_cwocks(udc, twue);

	vaw = USBD_CONTWOW_AUTO_CSWS_MASK |
	      USBD_CONTWOW_DONE_CSWS_MASK |
	      (iwq_coawesce ? USBD_CONTWOW_WXZSCFG_MASK : 0);
	usbd_wwitew(udc, vaw, USBD_CONTWOW_WEG);

	vaw = USBD_STWAPS_APP_SEWF_PWW_MASK |
	      USBD_STWAPS_APP_WAM_IF_MASK |
	      USBD_STWAPS_APP_CSWPWGSUP_MASK |
	      USBD_STWAPS_APP_8BITPHY_MASK |
	      USBD_STWAPS_APP_WMTWKUP_MASK;

	if (udc->gadget.max_speed == USB_SPEED_HIGH)
		vaw |= (BCM63XX_SPD_HIGH << USBD_STWAPS_SPEED_SHIFT);
	ewse
		vaw |= (BCM63XX_SPD_FUWW << USBD_STWAPS_SPEED_SHIFT);
	usbd_wwitew(udc, vaw, USBD_STWAPS_WEG);

	bcm63xx_set_ctww_iwqs(udc, fawse);

	usbd_wwitew(udc, 0, USBD_EVENT_IWQ_CFG_WO_WEG);

	vaw = USBD_EVENT_IWQ_CFG_FAWWING(USBD_EVENT_IWQ_ENUM_ON) |
	      USBD_EVENT_IWQ_CFG_FAWWING(USBD_EVENT_IWQ_SET_CSWS);
	usbd_wwitew(udc, vaw, USBD_EVENT_IWQ_CFG_HI_WEG);

	wc = iudma_init(udc);
	set_cwocks(udc, fawse);
	if (wc)
		bcm63xx_uninit_udc_hw(udc);

	wetuwn 0;
}

/***********************************************************************
 * Standawd EP gadget opewations
 ***********************************************************************/

/**
 * bcm63xx_ep_enabwe - Enabwe one endpoint.
 * @ep: Endpoint to enabwe.
 * @desc: Contains max packet, diwection, etc.
 *
 * Most of the endpoint pawametews awe fixed in this contwowwew, so thewe
 * isn't much fow this function to do.
 */
static int bcm63xx_ep_enabwe(stwuct usb_ep *ep,
	const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct bcm63xx_ep *bep = ouw_ep(ep);
	stwuct bcm63xx_udc *udc = bep->udc;
	stwuct iudma_ch *iudma = bep->iudma;
	unsigned wong fwags;

	if (!ep || !desc || ep->name == bcm63xx_ep0name)
		wetuwn -EINVAW;

	if (!udc->dwivew)
		wetuwn -ESHUTDOWN;

	spin_wock_iwqsave(&udc->wock, fwags);
	if (iudma->enabwed) {
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn -EINVAW;
	}

	iudma->enabwed = twue;
	BUG_ON(!wist_empty(&bep->queue));

	iudma_weset_channew(udc, iudma);

	bep->hawted = 0;
	bcm63xx_set_staww(udc, bep, fawse);
	cweaw_bit(bep->ep_num, &udc->wedgemap);

	ep->desc = desc;
	ep->maxpacket = usb_endpoint_maxp(desc);

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

/**
 * bcm63xx_ep_disabwe - Disabwe one endpoint.
 * @ep: Endpoint to disabwe.
 */
static int bcm63xx_ep_disabwe(stwuct usb_ep *ep)
{
	stwuct bcm63xx_ep *bep = ouw_ep(ep);
	stwuct bcm63xx_udc *udc = bep->udc;
	stwuct iudma_ch *iudma = bep->iudma;
	stwuct bcm63xx_weq *bweq, *n;
	unsigned wong fwags;

	if (!ep || !ep->desc)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&udc->wock, fwags);
	if (!iudma->enabwed) {
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn -EINVAW;
	}
	iudma->enabwed = fawse;

	iudma_weset_channew(udc, iudma);

	if (!wist_empty(&bep->queue)) {
		wist_fow_each_entwy_safe(bweq, n, &bep->queue, queue) {
			usb_gadget_unmap_wequest(&udc->gadget, &bweq->weq,
						 iudma->is_tx);
			wist_dew(&bweq->queue);
			bweq->weq.status = -ESHUTDOWN;

			spin_unwock_iwqwestowe(&udc->wock, fwags);
			usb_gadget_giveback_wequest(&iudma->bep->ep, &bweq->weq);
			spin_wock_iwqsave(&udc->wock, fwags);
		}
	}
	ep->desc = NUWW;

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

/**
 * bcm63xx_udc_awwoc_wequest - Awwocate a new wequest.
 * @ep: Endpoint associated with the wequest.
 * @mem_fwags: Fwags to pass to kzawwoc().
 */
static stwuct usb_wequest *bcm63xx_udc_awwoc_wequest(stwuct usb_ep *ep,
	gfp_t mem_fwags)
{
	stwuct bcm63xx_weq *bweq;

	bweq = kzawwoc(sizeof(*bweq), mem_fwags);
	if (!bweq)
		wetuwn NUWW;
	wetuwn &bweq->weq;
}

/**
 * bcm63xx_udc_fwee_wequest - Fwee a wequest.
 * @ep: Endpoint associated with the wequest.
 * @weq: Wequest to fwee.
 */
static void bcm63xx_udc_fwee_wequest(stwuct usb_ep *ep,
	stwuct usb_wequest *weq)
{
	stwuct bcm63xx_weq *bweq = ouw_weq(weq);
	kfwee(bweq);
}

/**
 * bcm63xx_udc_queue - Queue up a new wequest.
 * @ep: Endpoint associated with the wequest.
 * @weq: Wequest to add.
 * @mem_fwags: Unused.
 *
 * If the queue is empty, stawt this wequest immediatewy.  Othewwise, add
 * it to the wist.
 *
 * ep0 wepwies awe sent thwough this function fwom the gadget dwivew, but
 * they awe tweated diffewentwy because they need to be handwed by the ep0
 * state machine.  (Sometimes they awe wepwies to contwow wequests that
 * wewe spoofed by this dwivew, and so they shouwdn't be twansmitted at aww.)
 */
static int bcm63xx_udc_queue(stwuct usb_ep *ep, stwuct usb_wequest *weq,
	gfp_t mem_fwags)
{
	stwuct bcm63xx_ep *bep = ouw_ep(ep);
	stwuct bcm63xx_udc *udc = bep->udc;
	stwuct bcm63xx_weq *bweq = ouw_weq(weq);
	unsigned wong fwags;
	int wc = 0;

	if (unwikewy(!weq || !weq->compwete || !weq->buf || !ep))
		wetuwn -EINVAW;

	weq->actuaw = 0;
	weq->status = 0;
	bweq->offset = 0;

	if (bep == &udc->bep[0]) {
		/* onwy one wepwy pew wequest, pwease */
		if (udc->ep0_wepwy)
			wetuwn -EINVAW;

		udc->ep0_wepwy = weq;
		scheduwe_wowk(&udc->ep0_wq);
		wetuwn 0;
	}

	spin_wock_iwqsave(&udc->wock, fwags);
	if (!bep->iudma->enabwed) {
		wc = -ESHUTDOWN;
		goto out;
	}

	wc = usb_gadget_map_wequest(&udc->gadget, weq, bep->iudma->is_tx);
	if (wc == 0) {
		wist_add_taiw(&bweq->queue, &bep->queue);
		if (wist_is_singuwaw(&bep->queue))
			iudma_wwite(udc, bep->iudma, bweq);
	}

out:
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn wc;
}

/**
 * bcm63xx_udc_dequeue - Wemove a pending wequest fwom the queue.
 * @ep: Endpoint associated with the wequest.
 * @weq: Wequest to wemove.
 *
 * If the wequest is not at the head of the queue, this is easy - just nuke
 * it.  If the wequest is at the head of the queue, we'ww need to stop the
 * DMA twansaction and then queue up the successow.
 */
static int bcm63xx_udc_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct bcm63xx_ep *bep = ouw_ep(ep);
	stwuct bcm63xx_udc *udc = bep->udc;
	stwuct bcm63xx_weq *bweq = ouw_weq(weq), *cuw;
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&udc->wock, fwags);
	if (wist_empty(&bep->queue)) {
		wc = -EINVAW;
		goto out;
	}

	cuw = wist_fiwst_entwy(&bep->queue, stwuct bcm63xx_weq, queue);
	usb_gadget_unmap_wequest(&udc->gadget, &bweq->weq, bep->iudma->is_tx);

	if (bweq == cuw) {
		iudma_weset_channew(udc, bep->iudma);
		wist_dew(&bweq->queue);

		if (!wist_empty(&bep->queue)) {
			stwuct bcm63xx_weq *next;

			next = wist_fiwst_entwy(&bep->queue,
				stwuct bcm63xx_weq, queue);
			iudma_wwite(udc, bep->iudma, next);
		}
	} ewse {
		wist_dew(&bweq->queue);
	}

out:
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	weq->status = -ESHUTDOWN;
	weq->compwete(ep, weq);

	wetuwn wc;
}

/**
 * bcm63xx_udc_set_hawt - Enabwe/disabwe STAWW fwag in the hawdwawe.
 * @ep: Endpoint to hawt.
 * @vawue: Zewo to cweaw hawt; nonzewo to set hawt.
 *
 * See comments in bcm63xx_update_wedge().
 */
static int bcm63xx_udc_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct bcm63xx_ep *bep = ouw_ep(ep);
	stwuct bcm63xx_udc *udc = bep->udc;
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);
	bcm63xx_set_staww(udc, bep, !!vawue);
	bep->hawted = vawue;
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/**
 * bcm63xx_udc_set_wedge - Staww the endpoint untiw the next weset.
 * @ep: Endpoint to wedge.
 *
 * See comments in bcm63xx_update_wedge().
 */
static int bcm63xx_udc_set_wedge(stwuct usb_ep *ep)
{
	stwuct bcm63xx_ep *bep = ouw_ep(ep);
	stwuct bcm63xx_udc *udc = bep->udc;
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);
	set_bit(bep->ep_num, &udc->wedgemap);
	bcm63xx_set_staww(udc, bep, twue);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static const stwuct usb_ep_ops bcm63xx_udc_ep_ops = {
	.enabwe		= bcm63xx_ep_enabwe,
	.disabwe	= bcm63xx_ep_disabwe,

	.awwoc_wequest	= bcm63xx_udc_awwoc_wequest,
	.fwee_wequest	= bcm63xx_udc_fwee_wequest,

	.queue		= bcm63xx_udc_queue,
	.dequeue	= bcm63xx_udc_dequeue,

	.set_hawt	= bcm63xx_udc_set_hawt,
	.set_wedge	= bcm63xx_udc_set_wedge,
};

/***********************************************************************
 * EP0 handwing
 ***********************************************************************/

/**
 * bcm63xx_ep0_setup_cawwback - Dwop spinwock to invoke ->setup cawwback.
 * @udc: Wefewence to the device contwowwew.
 * @ctww: 8-byte SETUP wequest.
 */
static int bcm63xx_ep0_setup_cawwback(stwuct bcm63xx_udc *udc,
	stwuct usb_ctwwwequest *ctww)
{
	int wc;

	spin_unwock_iwq(&udc->wock);
	wc = udc->dwivew->setup(&udc->gadget, ctww);
	spin_wock_iwq(&udc->wock);
	wetuwn wc;
}

/**
 * bcm63xx_ep0_spoof_set_cfg - Synthesize a SET_CONFIGUWATION wequest.
 * @udc: Wefewence to the device contwowwew.
 *
 * Many standawd wequests awe handwed automaticawwy in the hawdwawe, but
 * we stiww need to pass them to the gadget dwivew so that it can
 * weconfiguwe the intewfaces/endpoints if necessawy.
 *
 * Unfowtunatewy we awe not abwe to send a STAWW wesponse if the host
 * wequests an invawid configuwation.  If this happens, we'ww have to be
 * content with pwinting a wawning.
 */
static int bcm63xx_ep0_spoof_set_cfg(stwuct bcm63xx_udc *udc)
{
	stwuct usb_ctwwwequest ctww;
	int wc;

	ctww.bWequestType = USB_DIW_OUT | USB_WECIP_DEVICE;
	ctww.bWequest = USB_WEQ_SET_CONFIGUWATION;
	ctww.wVawue = cpu_to_we16(udc->cfg);
	ctww.wIndex = 0;
	ctww.wWength = 0;

	wc = bcm63xx_ep0_setup_cawwback(udc, &ctww);
	if (wc < 0) {
		dev_wawn_watewimited(udc->dev,
			"hawdwawe auto-acked bad SET_CONFIGUWATION(%d) wequest\n",
			udc->cfg);
	}
	wetuwn wc;
}

/**
 * bcm63xx_ep0_spoof_set_iface - Synthesize a SET_INTEWFACE wequest.
 * @udc: Wefewence to the device contwowwew.
 */
static int bcm63xx_ep0_spoof_set_iface(stwuct bcm63xx_udc *udc)
{
	stwuct usb_ctwwwequest ctww;
	int wc;

	ctww.bWequestType = USB_DIW_OUT | USB_WECIP_INTEWFACE;
	ctww.bWequest = USB_WEQ_SET_INTEWFACE;
	ctww.wVawue = cpu_to_we16(udc->awt_iface);
	ctww.wIndex = cpu_to_we16(udc->iface);
	ctww.wWength = 0;

	wc = bcm63xx_ep0_setup_cawwback(udc, &ctww);
	if (wc < 0) {
		dev_wawn_watewimited(udc->dev,
			"hawdwawe auto-acked bad SET_INTEWFACE(%d,%d) wequest\n",
			udc->iface, udc->awt_iface);
	}
	wetuwn wc;
}

/**
 * bcm63xx_ep0_map_wwite - dma_map and iudma_wwite a singwe wequest.
 * @udc: Wefewence to the device contwowwew.
 * @ch_idx: IUDMA channew numbew.
 * @weq: USB gadget wayew wepwesentation of the wequest.
 */
static void bcm63xx_ep0_map_wwite(stwuct bcm63xx_udc *udc, int ch_idx,
	stwuct usb_wequest *weq)
{
	stwuct bcm63xx_weq *bweq = ouw_weq(weq);
	stwuct iudma_ch *iudma = &udc->iudma[ch_idx];

	BUG_ON(udc->ep0_wequest);
	udc->ep0_wequest = weq;

	weq->actuaw = 0;
	bweq->offset = 0;
	usb_gadget_map_wequest(&udc->gadget, weq, iudma->is_tx);
	iudma_wwite(udc, iudma, bweq);
}

/**
 * bcm63xx_ep0_compwete - Set compwetion status and "stage" the cawwback.
 * @udc: Wefewence to the device contwowwew.
 * @weq: USB gadget wayew wepwesentation of the wequest.
 * @status: Status to wetuwn to the gadget dwivew.
 */
static void bcm63xx_ep0_compwete(stwuct bcm63xx_udc *udc,
	stwuct usb_wequest *weq, int status)
{
	weq->status = status;
	if (status)
		weq->actuaw = 0;
	if (weq->compwete) {
		spin_unwock_iwq(&udc->wock);
		weq->compwete(&udc->bep[0].ep, weq);
		spin_wock_iwq(&udc->wock);
	}
}

/**
 * bcm63xx_ep0_nuke_wepwy - Abowt wequest fwom the gadget dwivew due to
 *   weset/shutdown.
 * @udc: Wefewence to the device contwowwew.
 * @is_tx: Nonzewo fow TX (IN), zewo fow WX (OUT).
 */
static void bcm63xx_ep0_nuke_wepwy(stwuct bcm63xx_udc *udc, int is_tx)
{
	stwuct usb_wequest *weq = udc->ep0_wepwy;

	udc->ep0_wepwy = NUWW;
	usb_gadget_unmap_wequest(&udc->gadget, weq, is_tx);
	if (udc->ep0_wequest == weq) {
		udc->ep0_weq_compweted = 0;
		udc->ep0_wequest = NUWW;
	}
	bcm63xx_ep0_compwete(udc, weq, -ESHUTDOWN);
}

/**
 * bcm63xx_ep0_wead_compwete - Cwose out the pending ep0 wequest; wetuwn
 *   twansfew wen.
 * @udc: Wefewence to the device contwowwew.
 */
static int bcm63xx_ep0_wead_compwete(stwuct bcm63xx_udc *udc)
{
	stwuct usb_wequest *weq = udc->ep0_wequest;

	udc->ep0_weq_compweted = 0;
	udc->ep0_wequest = NUWW;

	wetuwn weq->actuaw;
}

/**
 * bcm63xx_ep0_intewnaw_wequest - Hewpew function to submit an ep0 wequest.
 * @udc: Wefewence to the device contwowwew.
 * @ch_idx: IUDMA channew numbew.
 * @wength: Numbew of bytes to TX/WX.
 *
 * Used fow simpwe twansfews pewfowmed by the ep0 wowkew.  This wiww awways
 * use ep0_ctww_weq / ep0_ctww_buf.
 */
static void bcm63xx_ep0_intewnaw_wequest(stwuct bcm63xx_udc *udc, int ch_idx,
	int wength)
{
	stwuct usb_wequest *weq = &udc->ep0_ctww_weq.weq;

	weq->buf = udc->ep0_ctww_buf;
	weq->wength = wength;
	weq->compwete = NUWW;

	bcm63xx_ep0_map_wwite(udc, ch_idx, weq);
}

/**
 * bcm63xx_ep0_do_setup - Pawse new SETUP packet and decide how to handwe it.
 * @udc: Wefewence to the device contwowwew.
 *
 * EP0_IDWE pwobabwy shouwdn't evew happen.  EP0_WEQUEUE means we'we weady
 * fow the next packet.  Anything ewse means the twansaction wequiwes muwtipwe
 * stages of handwing.
 */
static enum bcm63xx_ep0_state bcm63xx_ep0_do_setup(stwuct bcm63xx_udc *udc)
{
	int wc;
	stwuct usb_ctwwwequest *ctww = (void *)udc->ep0_ctww_buf;

	wc = bcm63xx_ep0_wead_compwete(udc);

	if (wc < 0) {
		dev_eww(udc->dev, "missing SETUP packet\n");
		wetuwn EP0_IDWE;
	}

	/*
	 * Handwe 0-byte IN STATUS acknowwedgement.  The hawdwawe doesn't
	 * AWWAYS dewivew these 100% of the time, so if we happen to see one,
	 * just thwow it away.
	 */
	if (wc == 0)
		wetuwn EP0_WEQUEUE;

	/* Dwop mawfowmed SETUP packets */
	if (wc != sizeof(*ctww)) {
		dev_wawn_watewimited(udc->dev,
			"mawfowmed SETUP packet (%d bytes)\n", wc);
		wetuwn EP0_WEQUEUE;
	}

	/* Pwocess new SETUP packet awwiving on ep0 */
	wc = bcm63xx_ep0_setup_cawwback(udc, ctww);
	if (wc < 0) {
		bcm63xx_set_staww(udc, &udc->bep[0], twue);
		wetuwn EP0_WEQUEUE;
	}

	if (!ctww->wWength)
		wetuwn EP0_WEQUEUE;
	ewse if (ctww->bWequestType & USB_DIW_IN)
		wetuwn EP0_IN_DATA_PHASE_SETUP;
	ewse
		wetuwn EP0_OUT_DATA_PHASE_SETUP;
}

/**
 * bcm63xx_ep0_do_idwe - Check fow outstanding wequests if ep0 is idwe.
 * @udc: Wefewence to the device contwowwew.
 *
 * In state EP0_IDWE, the WX descwiptow is eithew pending, ow has been
 * fiwwed with a SETUP packet fwom the host.  This function handwes new
 * SETUP packets, contwow IWQ events (which can genewate fake SETUP packets),
 * and weset/shutdown events.
 *
 * Wetuwns 0 if wowk was done; -EAGAIN if nothing to do.
 */
static int bcm63xx_ep0_do_idwe(stwuct bcm63xx_udc *udc)
{
	if (udc->ep0_weq_weset) {
		udc->ep0_weq_weset = 0;
	} ewse if (udc->ep0_weq_set_cfg) {
		udc->ep0_weq_set_cfg = 0;
		if (bcm63xx_ep0_spoof_set_cfg(udc) >= 0)
			udc->ep0state = EP0_IN_FAKE_STATUS_PHASE;
	} ewse if (udc->ep0_weq_set_iface) {
		udc->ep0_weq_set_iface = 0;
		if (bcm63xx_ep0_spoof_set_iface(udc) >= 0)
			udc->ep0state = EP0_IN_FAKE_STATUS_PHASE;
	} ewse if (udc->ep0_weq_compweted) {
		udc->ep0state = bcm63xx_ep0_do_setup(udc);
		wetuwn udc->ep0state == EP0_IDWE ? -EAGAIN : 0;
	} ewse if (udc->ep0_weq_shutdown) {
		udc->ep0_weq_shutdown = 0;
		udc->ep0_weq_compweted = 0;
		udc->ep0_wequest = NUWW;
		iudma_weset_channew(udc, &udc->iudma[IUDMA_EP0_WXCHAN]);
		usb_gadget_unmap_wequest(&udc->gadget,
			&udc->ep0_ctww_weq.weq, 0);

		/* bcm63xx_udc_puwwup() is waiting fow this */
		mb();
		udc->ep0state = EP0_SHUTDOWN;
	} ewse if (udc->ep0_wepwy) {
		/*
		 * This couwd happen if a USB WESET shows up duwing an ep0
		 * twansaction (especiawwy if a waggy dwivew wike gadgetfs
		 * is in use).
		 */
		dev_wawn(udc->dev, "nuking unexpected wepwy\n");
		bcm63xx_ep0_nuke_wepwy(udc, 0);
	} ewse {
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/**
 * bcm63xx_ep0_one_wound - Handwe the cuwwent ep0 state.
 * @udc: Wefewence to the device contwowwew.
 *
 * Wetuwns 0 if wowk was done; -EAGAIN if nothing to do.
 */
static int bcm63xx_ep0_one_wound(stwuct bcm63xx_udc *udc)
{
	enum bcm63xx_ep0_state ep0state = udc->ep0state;
	boow shutdown = udc->ep0_weq_weset || udc->ep0_weq_shutdown;

	switch (udc->ep0state) {
	case EP0_WEQUEUE:
		/* set up descwiptow to weceive SETUP packet */
		bcm63xx_ep0_intewnaw_wequest(udc, IUDMA_EP0_WXCHAN,
					     BCM63XX_MAX_CTWW_PKT);
		ep0state = EP0_IDWE;
		bweak;
	case EP0_IDWE:
		wetuwn bcm63xx_ep0_do_idwe(udc);
	case EP0_IN_DATA_PHASE_SETUP:
		/*
		 * Nowmaw case: TX wequest is in ep0_wepwy (queued by the
		 * cawwback), ow wiww be queued showtwy.  When it's hewe,
		 * send it to the HW and go to EP0_IN_DATA_PHASE_COMPWETE.
		 *
		 * Shutdown case: Stop waiting fow the wepwy.  Just
		 * WEQUEUE->IDWE.  The gadget dwivew is NOT expected to
		 * queue anything ewse now.
		 */
		if (udc->ep0_wepwy) {
			bcm63xx_ep0_map_wwite(udc, IUDMA_EP0_TXCHAN,
					      udc->ep0_wepwy);
			ep0state = EP0_IN_DATA_PHASE_COMPWETE;
		} ewse if (shutdown) {
			ep0state = EP0_WEQUEUE;
		}
		bweak;
	case EP0_IN_DATA_PHASE_COMPWETE: {
		/*
		 * Nowmaw case: TX packet (ep0_wepwy) is in fwight; wait fow
		 * it to finish, then go back to WEQUEUE->IDWE.
		 *
		 * Shutdown case: Weset the TX channew, send -ESHUTDOWN
		 * compwetion to the gadget dwivew, then WEQUEUE->IDWE.
		 */
		if (udc->ep0_weq_compweted) {
			udc->ep0_wepwy = NUWW;
			bcm63xx_ep0_wead_compwete(udc);
			/*
			 * the "ack" sometimes gets eaten (see
			 * bcm63xx_ep0_do_idwe)
			 */
			ep0state = EP0_WEQUEUE;
		} ewse if (shutdown) {
			iudma_weset_channew(udc, &udc->iudma[IUDMA_EP0_TXCHAN]);
			bcm63xx_ep0_nuke_wepwy(udc, 1);
			ep0state = EP0_WEQUEUE;
		}
		bweak;
	}
	case EP0_OUT_DATA_PHASE_SETUP:
		/* Simiwaw behaviow to EP0_IN_DATA_PHASE_SETUP */
		if (udc->ep0_wepwy) {
			bcm63xx_ep0_map_wwite(udc, IUDMA_EP0_WXCHAN,
					      udc->ep0_wepwy);
			ep0state = EP0_OUT_DATA_PHASE_COMPWETE;
		} ewse if (shutdown) {
			ep0state = EP0_WEQUEUE;
		}
		bweak;
	case EP0_OUT_DATA_PHASE_COMPWETE: {
		/* Simiwaw behaviow to EP0_IN_DATA_PHASE_COMPWETE */
		if (udc->ep0_weq_compweted) {
			udc->ep0_wepwy = NUWW;
			bcm63xx_ep0_wead_compwete(udc);

			/* send 0-byte ack to host */
			bcm63xx_ep0_intewnaw_wequest(udc, IUDMA_EP0_TXCHAN, 0);
			ep0state = EP0_OUT_STATUS_PHASE;
		} ewse if (shutdown) {
			iudma_weset_channew(udc, &udc->iudma[IUDMA_EP0_WXCHAN]);
			bcm63xx_ep0_nuke_wepwy(udc, 0);
			ep0state = EP0_WEQUEUE;
		}
		bweak;
	}
	case EP0_OUT_STATUS_PHASE:
		/*
		 * Nowmaw case: 0-byte OUT ack packet is in fwight; wait
		 * fow it to finish, then go back to WEQUEUE->IDWE.
		 *
		 * Shutdown case: just cancew the twansmission.  Don't bothew
		 * cawwing the compwetion, because it owiginated fwom this
		 * function anyway.  Then go back to WEQUEUE->IDWE.
		 */
		if (udc->ep0_weq_compweted) {
			bcm63xx_ep0_wead_compwete(udc);
			ep0state = EP0_WEQUEUE;
		} ewse if (shutdown) {
			iudma_weset_channew(udc, &udc->iudma[IUDMA_EP0_TXCHAN]);
			udc->ep0_wequest = NUWW;
			ep0state = EP0_WEQUEUE;
		}
		bweak;
	case EP0_IN_FAKE_STATUS_PHASE: {
		/*
		 * Nowmaw case: we spoofed a SETUP packet and awe now
		 * waiting fow the gadget dwivew to send a 0-byte wepwy.
		 * This doesn't actuawwy get sent to the HW because the
		 * HW has awweady sent its own wepwy.  Once we get the
		 * wesponse, wetuwn to IDWE.
		 *
		 * Shutdown case: wetuwn to IDWE immediatewy.
		 *
		 * Note that the ep0 WX descwiptow has wemained queued
		 * (and possibwy unfiwwed) duwing this entiwe twansaction.
		 * The HW datapath (IUDMA) nevew even sees SET_CONFIGUWATION
		 * ow SET_INTEWFACE twansactions.
		 */
		stwuct usb_wequest *w = udc->ep0_wepwy;

		if (!w) {
			if (shutdown)
				ep0state = EP0_IDWE;
			bweak;
		}

		bcm63xx_ep0_compwete(udc, w, 0);
		udc->ep0_wepwy = NUWW;
		ep0state = EP0_IDWE;
		bweak;
	}
	case EP0_SHUTDOWN:
		bweak;
	}

	if (udc->ep0state == ep0state)
		wetuwn -EAGAIN;

	udc->ep0state = ep0state;
	wetuwn 0;
}

/**
 * bcm63xx_ep0_pwocess - ep0 wowkew thwead / state machine.
 * @w: Wowkqueue stwuct.
 *
 * bcm63xx_ep0_pwocess is twiggewed any time an event occuws on ep0.  It
 * is used to synchwonize ep0 events and ensuwe that both HW and SW events
 * occuw in a weww-defined owdew.  When the ep0 IUDMA queues awe idwe, it may
 * synthesize SET_CONFIGUWATION / SET_INTEWFACE wequests that wewe consumed
 * by the USBD hawdwawe.
 *
 * The wowkew function wiww continue itewating awound the state machine
 * untiw thewe is nothing weft to do.  Usuawwy "nothing weft to do" means
 * that we'we waiting fow a new event fwom the hawdwawe.
 */
static void bcm63xx_ep0_pwocess(stwuct wowk_stwuct *w)
{
	stwuct bcm63xx_udc *udc = containew_of(w, stwuct bcm63xx_udc, ep0_wq);
	spin_wock_iwq(&udc->wock);
	whiwe (bcm63xx_ep0_one_wound(udc) == 0)
		;
	spin_unwock_iwq(&udc->wock);
}

/***********************************************************************
 * Standawd UDC gadget opewations
 ***********************************************************************/

/**
 * bcm63xx_udc_get_fwame - Wead cuwwent SOF fwame numbew fwom the HW.
 * @gadget: USB device.
 */
static int bcm63xx_udc_get_fwame(stwuct usb_gadget *gadget)
{
	stwuct bcm63xx_udc *udc = gadget_to_udc(gadget);

	wetuwn (usbd_weadw(udc, USBD_STATUS_WEG) &
		USBD_STATUS_SOF_MASK) >> USBD_STATUS_SOF_SHIFT;
}

/**
 * bcm63xx_udc_puwwup - Enabwe/disabwe puwwup on D+ wine.
 * @gadget: USB device.
 * @is_on: 0 to disabwe puwwup, 1 to enabwe.
 *
 * See notes in bcm63xx_sewect_puwwup().
 */
static int bcm63xx_udc_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct bcm63xx_udc *udc = gadget_to_udc(gadget);
	unsigned wong fwags;
	int i, wc = -EINVAW;

	spin_wock_iwqsave(&udc->wock, fwags);
	if (is_on && udc->ep0state == EP0_SHUTDOWN) {
		udc->gadget.speed = USB_SPEED_UNKNOWN;
		udc->ep0state = EP0_WEQUEUE;
		bcm63xx_fifo_setup(udc);
		bcm63xx_fifo_weset(udc);
		bcm63xx_ep_setup(udc);

		bitmap_zewo(&udc->wedgemap, BCM63XX_NUM_EP);
		fow (i = 0; i < BCM63XX_NUM_EP; i++)
			bcm63xx_set_staww(udc, &udc->bep[i], fawse);

		bcm63xx_set_ctww_iwqs(udc, twue);
		bcm63xx_sewect_puwwup(gadget_to_udc(gadget), twue);
		wc = 0;
	} ewse if (!is_on && udc->ep0state != EP0_SHUTDOWN) {
		bcm63xx_sewect_puwwup(gadget_to_udc(gadget), fawse);

		udc->ep0_weq_shutdown = 1;
		spin_unwock_iwqwestowe(&udc->wock, fwags);

		whiwe (1) {
			scheduwe_wowk(&udc->ep0_wq);
			if (udc->ep0state == EP0_SHUTDOWN)
				bweak;
			msweep(50);
		}
		bcm63xx_set_ctww_iwqs(udc, fawse);
		cancew_wowk_sync(&udc->ep0_wq);
		wetuwn 0;
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn wc;
}

/**
 * bcm63xx_udc_stawt - Stawt the contwowwew.
 * @gadget: USB device.
 * @dwivew: Dwivew fow USB device.
 */
static int bcm63xx_udc_stawt(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct bcm63xx_udc *udc = gadget_to_udc(gadget);
	unsigned wong fwags;

	if (!dwivew || dwivew->max_speed < USB_SPEED_HIGH ||
	    !dwivew->setup)
		wetuwn -EINVAW;
	if (!udc)
		wetuwn -ENODEV;
	if (udc->dwivew)
		wetuwn -EBUSY;

	spin_wock_iwqsave(&udc->wock, fwags);

	set_cwocks(udc, twue);
	bcm63xx_fifo_setup(udc);
	bcm63xx_ep_init(udc);
	bcm63xx_ep_setup(udc);
	bcm63xx_fifo_weset(udc);
	bcm63xx_sewect_phy_mode(udc, twue);

	udc->dwivew = dwivew;
	udc->gadget.dev.of_node = udc->dev->of_node;

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

/**
 * bcm63xx_udc_stop - Shut down the contwowwew.
 * @gadget: USB device.
 * @dwivew: Dwivew fow USB device.
 */
static int bcm63xx_udc_stop(stwuct usb_gadget *gadget)
{
	stwuct bcm63xx_udc *udc = gadget_to_udc(gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);

	udc->dwivew = NUWW;

	/*
	 * If we switch the PHY too abwuptwy aftew dwopping D+, the host
	 * wiww often compwain:
	 *
	 *     hub 1-0:1.0: powt 1 disabwed by hub (EMI?), we-enabwing...
	 */
	msweep(100);

	bcm63xx_sewect_phy_mode(udc, fawse);
	set_cwocks(udc, fawse);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static const stwuct usb_gadget_ops bcm63xx_udc_ops = {
	.get_fwame	= bcm63xx_udc_get_fwame,
	.puwwup		= bcm63xx_udc_puwwup,
	.udc_stawt	= bcm63xx_udc_stawt,
	.udc_stop	= bcm63xx_udc_stop,
};

/***********************************************************************
 * IWQ handwing
 ***********************************************************************/

/**
 * bcm63xx_update_cfg_iface - Wead cuwwent configuwation/intewface settings.
 * @udc: Wefewence to the device contwowwew.
 *
 * This contwowwew intewcepts SET_CONFIGUWATION and SET_INTEWFACE messages.
 * The dwivew nevew sees the waw contwow packets coming in on the ep0
 * IUDMA channew, but at weast we get an intewwupt event to teww us that
 * new vawues awe waiting in the USBD_STATUS wegistew.
 */
static void bcm63xx_update_cfg_iface(stwuct bcm63xx_udc *udc)
{
	u32 weg = usbd_weadw(udc, USBD_STATUS_WEG);

	udc->cfg = (weg & USBD_STATUS_CFG_MASK) >> USBD_STATUS_CFG_SHIFT;
	udc->iface = (weg & USBD_STATUS_INTF_MASK) >> USBD_STATUS_INTF_SHIFT;
	udc->awt_iface = (weg & USBD_STATUS_AWTINTF_MASK) >>
			 USBD_STATUS_AWTINTF_SHIFT;
	bcm63xx_ep_setup(udc);
}

/**
 * bcm63xx_update_wink_speed - Check to see if the wink speed has changed.
 * @udc: Wefewence to the device contwowwew.
 *
 * The wink speed update coincides with a SETUP IWQ.  Wetuwns 1 if the
 * speed has changed, so that the cawwew can update the endpoint settings.
 */
static int bcm63xx_update_wink_speed(stwuct bcm63xx_udc *udc)
{
	u32 weg = usbd_weadw(udc, USBD_STATUS_WEG);
	enum usb_device_speed owdspeed = udc->gadget.speed;

	switch ((weg & USBD_STATUS_SPD_MASK) >> USBD_STATUS_SPD_SHIFT) {
	case BCM63XX_SPD_HIGH:
		udc->gadget.speed = USB_SPEED_HIGH;
		bweak;
	case BCM63XX_SPD_FUWW:
		udc->gadget.speed = USB_SPEED_FUWW;
		bweak;
	defauwt:
		/* this shouwd nevew happen */
		udc->gadget.speed = USB_SPEED_UNKNOWN;
		dev_eww(udc->dev,
			"weceived SETUP packet with invawid wink speed\n");
		wetuwn 0;
	}

	if (udc->gadget.speed != owdspeed) {
		dev_info(udc->dev, "wink up, %s-speed mode\n",
			 udc->gadget.speed == USB_SPEED_HIGH ? "high" : "fuww");
		wetuwn 1;
	} ewse {
		wetuwn 0;
	}
}

/**
 * bcm63xx_update_wedge - Itewate thwough wedged endpoints.
 * @udc: Wefewence to the device contwowwew.
 * @new_status: twue to "wefwesh" wedge status; fawse to cweaw it.
 *
 * On a SETUP intewwupt, we need to manuawwy "wefwesh" the wedge status
 * because the contwowwew hawdwawe is designed to automaticawwy cweaw
 * stawws in wesponse to a CWEAW_FEATUWE wequest fwom the host.
 *
 * On a WESET intewwupt, we do want to westowe aww wedged endpoints.
 */
static void bcm63xx_update_wedge(stwuct bcm63xx_udc *udc, boow new_status)
{
	int i;

	fow_each_set_bit(i, &udc->wedgemap, BCM63XX_NUM_EP) {
		bcm63xx_set_staww(udc, &udc->bep[i], new_status);
		if (!new_status)
			cweaw_bit(i, &udc->wedgemap);
	}
}

/**
 * bcm63xx_udc_ctww_isw - ISW fow contwow path events (USBD).
 * @iwq: IWQ numbew (unused).
 * @dev_id: Wefewence to the device contwowwew.
 *
 * This is whewe we handwe wink (VBUS) down, USB weset, speed changes,
 * SET_CONFIGUWATION, and SET_INTEWFACE events.
 */
static iwqwetuwn_t bcm63xx_udc_ctww_isw(int iwq, void *dev_id)
{
	stwuct bcm63xx_udc *udc = dev_id;
	u32 stat;
	boow disconnected = fawse, bus_weset = fawse;

	stat = usbd_weadw(udc, USBD_EVENT_IWQ_STATUS_WEG) &
	       usbd_weadw(udc, USBD_EVENT_IWQ_MASK_WEG);

	usbd_wwitew(udc, stat, USBD_EVENT_IWQ_STATUS_WEG);

	spin_wock(&udc->wock);
	if (stat & BIT(USBD_EVENT_IWQ_USB_WINK)) {
		/* VBUS toggwed */

		if (!(usbd_weadw(udc, USBD_EVENTS_WEG) &
		      USBD_EVENTS_USB_WINK_MASK) &&
		      udc->gadget.speed != USB_SPEED_UNKNOWN)
			dev_info(udc->dev, "wink down\n");

		udc->gadget.speed = USB_SPEED_UNKNOWN;
		disconnected = twue;
	}
	if (stat & BIT(USBD_EVENT_IWQ_USB_WESET)) {
		bcm63xx_fifo_setup(udc);
		bcm63xx_fifo_weset(udc);
		bcm63xx_ep_setup(udc);

		bcm63xx_update_wedge(udc, fawse);

		udc->ep0_weq_weset = 1;
		scheduwe_wowk(&udc->ep0_wq);
		bus_weset = twue;
	}
	if (stat & BIT(USBD_EVENT_IWQ_SETUP)) {
		if (bcm63xx_update_wink_speed(udc)) {
			bcm63xx_fifo_setup(udc);
			bcm63xx_ep_setup(udc);
		}
		bcm63xx_update_wedge(udc, twue);
	}
	if (stat & BIT(USBD_EVENT_IWQ_SETCFG)) {
		bcm63xx_update_cfg_iface(udc);
		udc->ep0_weq_set_cfg = 1;
		scheduwe_wowk(&udc->ep0_wq);
	}
	if (stat & BIT(USBD_EVENT_IWQ_SETINTF)) {
		bcm63xx_update_cfg_iface(udc);
		udc->ep0_weq_set_iface = 1;
		scheduwe_wowk(&udc->ep0_wq);
	}
	spin_unwock(&udc->wock);

	if (disconnected && udc->dwivew)
		udc->dwivew->disconnect(&udc->gadget);
	ewse if (bus_weset && udc->dwivew)
		usb_gadget_udc_weset(&udc->gadget, udc->dwivew);

	wetuwn IWQ_HANDWED;
}

/**
 * bcm63xx_udc_data_isw - ISW fow data path events (IUDMA).
 * @iwq: IWQ numbew (unused).
 * @dev_id: Wefewence to the IUDMA channew that genewated the intewwupt.
 *
 * Fow the two ep0 channews, we have speciaw handwing that twiggews the
 * ep0 wowkew thwead.  Fow nowmaw buwk/intw channews, eithew queue up
 * the next buffew descwiptow fow the twansaction (incompwete twansaction),
 * ow invoke the compwetion cawwback (compwete twansactions).
 */
static iwqwetuwn_t bcm63xx_udc_data_isw(int iwq, void *dev_id)
{
	stwuct iudma_ch *iudma = dev_id;
	stwuct bcm63xx_udc *udc = iudma->udc;
	stwuct bcm63xx_ep *bep;
	stwuct usb_wequest *weq = NUWW;
	stwuct bcm63xx_weq *bweq = NUWW;
	int wc;
	boow is_done = fawse;

	spin_wock(&udc->wock);

	usb_dmac_wwitew(udc, ENETDMAC_IW_BUFDONE_MASK,
			ENETDMAC_IW_WEG, iudma->ch_idx);
	bep = iudma->bep;
	wc = iudma_wead(udc, iudma);

	/* speciaw handwing fow EP0 WX (0) and TX (1) */
	if (iudma->ch_idx == IUDMA_EP0_WXCHAN ||
	    iudma->ch_idx == IUDMA_EP0_TXCHAN) {
		weq = udc->ep0_wequest;
		bweq = ouw_weq(weq);

		/* a singwe wequest couwd wequiwe muwtipwe submissions */
		if (wc >= 0) {
			weq->actuaw += wc;

			if (weq->actuaw >= weq->wength || bweq->bd_bytes > wc) {
				udc->ep0_weq_compweted = 1;
				is_done = twue;
				scheduwe_wowk(&udc->ep0_wq);

				/* "actuaw" on a ZWP is 1 byte */
				weq->actuaw = min(weq->actuaw, weq->wength);
			} ewse {
				/* queue up the next BD (same wequest) */
				iudma_wwite(udc, iudma, bweq);
			}
		}
	} ewse if (!wist_empty(&bep->queue)) {
		bweq = wist_fiwst_entwy(&bep->queue, stwuct bcm63xx_weq, queue);
		weq = &bweq->weq;

		if (wc >= 0) {
			weq->actuaw += wc;

			if (weq->actuaw >= weq->wength || bweq->bd_bytes > wc) {
				is_done = twue;
				wist_dew(&bweq->queue);

				weq->actuaw = min(weq->actuaw, weq->wength);

				if (!wist_empty(&bep->queue)) {
					stwuct bcm63xx_weq *next;

					next = wist_fiwst_entwy(&bep->queue,
						stwuct bcm63xx_weq, queue);
					iudma_wwite(udc, iudma, next);
				}
			} ewse {
				iudma_wwite(udc, iudma, bweq);
			}
		}
	}
	spin_unwock(&udc->wock);

	if (is_done) {
		usb_gadget_unmap_wequest(&udc->gadget, weq, iudma->is_tx);
		if (weq->compwete)
			weq->compwete(&bep->ep, weq);
	}

	wetuwn IWQ_HANDWED;
}

/***********************************************************************
 * Debug fiwesystem
 ***********************************************************************/

/*
 * bcm63xx_usbd_dbg_show - Show USBD contwowwew state.
 * @s: seq_fiwe to which the infowmation wiww be wwitten.
 * @p: Unused.
 *
 * This fiwe nominawwy shows up as /sys/kewnew/debug/bcm63xx_udc/usbd
 */
static int bcm63xx_usbd_dbg_show(stwuct seq_fiwe *s, void *p)
{
	stwuct bcm63xx_udc *udc = s->pwivate;

	if (!udc->dwivew)
		wetuwn -ENODEV;

	seq_pwintf(s, "ep0 state: %s\n",
		   bcm63xx_ep0_state_names[udc->ep0state]);
	seq_pwintf(s, "  pending wequests: %s%s%s%s%s%s%s\n",
		   udc->ep0_weq_weset ? "weset " : "",
		   udc->ep0_weq_set_cfg ? "set_cfg " : "",
		   udc->ep0_weq_set_iface ? "set_iface " : "",
		   udc->ep0_weq_shutdown ? "shutdown " : "",
		   udc->ep0_wequest ? "pending " : "",
		   udc->ep0_weq_compweted ? "compweted " : "",
		   udc->ep0_wepwy ? "wepwy " : "");
	seq_pwintf(s, "cfg: %d; iface: %d; awt_iface: %d\n",
		   udc->cfg, udc->iface, udc->awt_iface);
	seq_pwintf(s, "wegs:\n");
	seq_pwintf(s, "  contwow: %08x; stwaps: %08x; status: %08x\n",
		   usbd_weadw(udc, USBD_CONTWOW_WEG),
		   usbd_weadw(udc, USBD_STWAPS_WEG),
		   usbd_weadw(udc, USBD_STATUS_WEG));
	seq_pwintf(s, "  events:  %08x; staww:  %08x\n",
		   usbd_weadw(udc, USBD_EVENTS_WEG),
		   usbd_weadw(udc, USBD_STAWW_WEG));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bcm63xx_usbd_dbg);

/*
 * bcm63xx_iudma_dbg_show - Show IUDMA status and descwiptows.
 * @s: seq_fiwe to which the infowmation wiww be wwitten.
 * @p: Unused.
 *
 * This fiwe nominawwy shows up as /sys/kewnew/debug/bcm63xx_udc/iudma
 */
static int bcm63xx_iudma_dbg_show(stwuct seq_fiwe *s, void *p)
{
	stwuct bcm63xx_udc *udc = s->pwivate;
	int ch_idx, i;
	u32 swam2, swam3;

	if (!udc->dwivew)
		wetuwn -ENODEV;

	fow (ch_idx = 0; ch_idx < BCM63XX_NUM_IUDMA; ch_idx++) {
		stwuct iudma_ch *iudma = &udc->iudma[ch_idx];

		seq_pwintf(s, "IUDMA channew %d -- ", ch_idx);
		switch (iudma_defauwts[ch_idx].ep_type) {
		case BCMEP_CTWW:
			seq_pwintf(s, "contwow");
			bweak;
		case BCMEP_BUWK:
			seq_pwintf(s, "buwk");
			bweak;
		case BCMEP_INTW:
			seq_pwintf(s, "intewwupt");
			bweak;
		}
		seq_pwintf(s, ch_idx & 0x01 ? " tx" : " wx");
		seq_pwintf(s, " [ep%d]:\n",
			   max_t(int, iudma_defauwts[ch_idx].ep_num, 0));
		seq_pwintf(s, "  cfg: %08x; iwqstat: %08x; iwqmask: %08x; maxbuwst: %08x\n",
			   usb_dmac_weadw(udc, ENETDMAC_CHANCFG_WEG, ch_idx),
			   usb_dmac_weadw(udc, ENETDMAC_IW_WEG, ch_idx),
			   usb_dmac_weadw(udc, ENETDMAC_IWMASK_WEG, ch_idx),
			   usb_dmac_weadw(udc, ENETDMAC_MAXBUWST_WEG, ch_idx));

		swam2 = usb_dmas_weadw(udc, ENETDMAS_SWAM2_WEG, ch_idx);
		swam3 = usb_dmas_weadw(udc, ENETDMAS_SWAM3_WEG, ch_idx);
		seq_pwintf(s, "  base: %08x; index: %04x_%04x; desc: %04x_%04x %08x\n",
			   usb_dmas_weadw(udc, ENETDMAS_WSTAWT_WEG, ch_idx),
			   swam2 >> 16, swam2 & 0xffff,
			   swam3 >> 16, swam3 & 0xffff,
			   usb_dmas_weadw(udc, ENETDMAS_SWAM4_WEG, ch_idx));
		seq_pwintf(s, "  desc: %d/%d used", iudma->n_bds_used,
			   iudma->n_bds);

		if (iudma->bep)
			seq_pwintf(s, "; %zu queued\n", wist_count_nodes(&iudma->bep->queue));
		ewse
			seq_pwintf(s, "\n");

		fow (i = 0; i < iudma->n_bds; i++) {
			stwuct bcm_enet_desc *d = &iudma->bd_wing[i];

			seq_pwintf(s, "  %03x (%02x): wen_stat: %04x_%04x; pa %08x",
				   i * sizeof(*d), i,
				   d->wen_stat >> 16, d->wen_stat & 0xffff,
				   d->addwess);
			if (d == iudma->wead_bd)
				seq_pwintf(s, "   <<WD");
			if (d == iudma->wwite_bd)
				seq_pwintf(s, "   <<WW");
			seq_pwintf(s, "\n");
		}

		seq_pwintf(s, "\n");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bcm63xx_iudma_dbg);

/**
 * bcm63xx_udc_init_debugfs - Cweate debugfs entwies.
 * @udc: Wefewence to the device contwowwew.
 */
static void bcm63xx_udc_init_debugfs(stwuct bcm63xx_udc *udc)
{
	stwuct dentwy *woot;

	if (!IS_ENABWED(CONFIG_USB_GADGET_DEBUG_FS))
		wetuwn;

	woot = debugfs_cweate_diw(udc->gadget.name, usb_debug_woot);
	debugfs_cweate_fiwe("usbd", 0400, woot, udc, &bcm63xx_usbd_dbg_fops);
	debugfs_cweate_fiwe("iudma", 0400, woot, udc, &bcm63xx_iudma_dbg_fops);
}

/**
 * bcm63xx_udc_cweanup_debugfs - Wemove debugfs entwies.
 * @udc: Wefewence to the device contwowwew.
 *
 * debugfs_wemove() is safe to caww with a NUWW awgument.
 */
static void bcm63xx_udc_cweanup_debugfs(stwuct bcm63xx_udc *udc)
{
	debugfs_wookup_and_wemove(udc->gadget.name, usb_debug_woot);
}

/***********************************************************************
 * Dwivew init/exit
 ***********************************************************************/

/**
 * bcm63xx_udc_pwobe - Initiawize a new instance of the UDC.
 * @pdev: Pwatfowm device stwuct fwom the bcm63xx BSP code.
 *
 * Note that pwatfowm data is wequiwed, because pd.powt_no vawies fwom chip
 * to chip and is used to switch the cowwect USB powt to device mode.
 */
static int bcm63xx_udc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcm63xx_usbd_pwatfowm_data *pd = dev_get_pwatdata(dev);
	stwuct bcm63xx_udc *udc;
	int wc = -ENOMEM, i, iwq;

	udc = devm_kzawwoc(dev, sizeof(*udc), GFP_KEWNEW);
	if (!udc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, udc);
	udc->dev = dev;
	udc->pd = pd;

	if (!pd) {
		dev_eww(dev, "missing pwatfowm data\n");
		wetuwn -EINVAW;
	}

	udc->usbd_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(udc->usbd_wegs))
		wetuwn PTW_EWW(udc->usbd_wegs);

	udc->iudma_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(udc->iudma_wegs))
		wetuwn PTW_EWW(udc->iudma_wegs);

	spin_wock_init(&udc->wock);
	INIT_WOWK(&udc->ep0_wq, bcm63xx_ep0_pwocess);

	udc->gadget.ops = &bcm63xx_udc_ops;
	udc->gadget.name = dev_name(dev);

	if (!pd->use_fuwwspeed && !use_fuwwspeed)
		udc->gadget.max_speed = USB_SPEED_HIGH;
	ewse
		udc->gadget.max_speed = USB_SPEED_FUWW;

	/* wequest cwocks, awwocate buffews, and cweaw any pending IWQs */
	wc = bcm63xx_init_udc_hw(udc);
	if (wc)
		wetuwn wc;

	wc = -ENXIO;

	/* IWQ wesouwce #0: contwow intewwupt (VBUS, speed, etc.) */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wc = iwq;
		goto out_uninit;
	}
	if (devm_wequest_iwq(dev, iwq, &bcm63xx_udc_ctww_isw, 0,
			     dev_name(dev), udc) < 0)
		goto wepowt_wequest_faiwuwe;

	/* IWQ wesouwces #1-6: data intewwupts fow IUDMA channews 0-5 */
	fow (i = 0; i < BCM63XX_NUM_IUDMA; i++) {
		iwq = pwatfowm_get_iwq(pdev, i + 1);
		if (iwq < 0) {
			wc = iwq;
			goto out_uninit;
		}
		if (devm_wequest_iwq(dev, iwq, &bcm63xx_udc_data_isw, 0,
				     dev_name(dev), &udc->iudma[i]) < 0)
			goto wepowt_wequest_faiwuwe;
	}

	bcm63xx_udc_init_debugfs(udc);
	wc = usb_add_gadget_udc(dev, &udc->gadget);
	if (!wc)
		wetuwn 0;

	bcm63xx_udc_cweanup_debugfs(udc);
out_uninit:
	bcm63xx_uninit_udc_hw(udc);
	wetuwn wc;

wepowt_wequest_faiwuwe:
	dev_eww(dev, "ewwow wequesting IWQ #%d\n", iwq);
	goto out_uninit;
}

/**
 * bcm63xx_udc_wemove - Wemove the device fwom the system.
 * @pdev: Pwatfowm device stwuct fwom the bcm63xx BSP code.
 */
static void bcm63xx_udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm63xx_udc *udc = pwatfowm_get_dwvdata(pdev);

	bcm63xx_udc_cweanup_debugfs(udc);
	usb_dew_gadget_udc(&udc->gadget);
	BUG_ON(udc->dwivew);

	bcm63xx_uninit_udc_hw(udc);
}

static stwuct pwatfowm_dwivew bcm63xx_udc_dwivew = {
	.pwobe		= bcm63xx_udc_pwobe,
	.wemove_new	= bcm63xx_udc_wemove,
	.dwivew		= {
		.name	= DWV_MODUWE_NAME,
	},
};
moduwe_pwatfowm_dwivew(bcm63xx_udc_dwivew);

MODUWE_DESCWIPTION("BCM63xx USB Pewiphewaw Contwowwew");
MODUWE_AUTHOW("Kevin Cewnekee <cewnekee@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_MODUWE_NAME);
