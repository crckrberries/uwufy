/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * USBHS-DEV device contwowwew dwivew headew fiwe
 *
 * Copywight (C) 2023 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 */

#ifndef __WINUX_CDNS2_GADGET
#define __WINUX_CDNS2_GADGET

#incwude <winux/usb/gadget.h>
#incwude <winux/dma-diwection.h>

/*
 * USBHS wegistew intewface.
 * This cowwesponds to the USBHS Device Contwowwew Intewface.
 */

/**
 * stwuct cdns2_ep0_wegs - endpoint 0 wewated wegistews.
 * @wxbc: weceive (OUT) 0 endpoint byte count wegistew.
 * @txbc: twansmit (IN) 0 endpoint byte count wegistew.
 * @cs: 0 endpoint contwow and status wegistew.
 * @wesewved1: wesewved.
 * @fifo: 0 endpoint fifo wegistew.
 * @wesewved2: wesewved.
 * @setupdat: SETUP data wegistew.
 * @wesewved4: wesewved.
 * @maxpack: 0 endpoint max packet size.
 */
stwuct cdns2_ep0_wegs {
	__u8 wxbc;
	__u8 txbc;
	__u8 cs;
	__u8 wesewved1[4];
	__u8 fifo;
	__we32 wesewved2[94];
	__u8 setupdat[8];
	__u8 wesewved4[88];
	__u8 maxpack;
} __packed __awigned(4);

/* EP0CS - bitmasks. */
/* Endpoint 0 staww bit fow status stage. */
#define EP0CS_STAWW	BIT(0)
/* HSNAK bit. */
#define EP0CS_HSNAK	BIT(1)
/* IN 0 endpoint busy bit. */
#define EP0CS_TXBSY_MSK	BIT(2)
/* OUT 0 endpoint busy bit. */
#define EP0CS_WXBSY_MSK	BIT(3)
/* Send STAWW in the data stage phase. */
#define EP0CS_DSTAWW	BIT(4)
/* SETUP buffew content was changed. */
#define EP0CS_CHGSET	BIT(7)

/* EP0FIFO - bitmasks. */
/* Diwection. */
#define EP0_FIFO_IO_TX	BIT(4)
/* FIFO auto bit. */
#define EP0_FIFO_AUTO	BIT(5)
/* FIFO commit bit. */
#define EP0_FIFO_COMMIT	BIT(6)
/* FIFO access bit. */
#define EP0_FIFO_ACCES	BIT(7)

/**
 * stwuct cdns2_epx_base - base endpoint wegistews.
 * @wxbc: OUT endpoint byte count wegistew.
 * @wxcon: OUT endpoint contwow wegistew.
 * @wxcs: OUT endpoint contwow and status wegistew.
 * @txbc: IN endpoint byte count wegistew.
 * @txcon: IN endpoint contwow wegistew.
 * @txcs: IN endpoint contwow and status wegistew.
 */
stwuct cdns2_epx_base {
	__we16 wxbc;
	__u8 wxcon;
	__u8 wxcs;
	__we16 txbc;
	__u8 txcon;
	__u8 txcs;
} __packed __awigned(4);

/* wxcon/txcon - endpoint contwow wegistew bitmasks. */
/* Endpoint buffewing: 0 - singwe buffewing ... 3 - quad buffewing. */
#define EPX_CON_BUF		GENMASK(1, 0)
/* Endpoint type. */
#define EPX_CON_TYPE		GENMASK(3, 2)
/* Endpoint type: isochwonous. */
#define EPX_CON_TYPE_ISOC	0x4
/* Endpoint type: buwk. */
#define EPX_CON_TYPE_BUWK	0x8
/* Endpoint type: intewwupt. */
#define EPX_CON_TYPE_INT	0xC
/* Numbew of packets pew micwofwame. */
#define EPX_CON_ISOD		GENMASK(5, 4)
#define EPX_CON_ISOD_SHIFT	0x4
/* Endpoint staww bit. */
#define EPX_CON_STAWW		BIT(6)
/* Endpoint enabwe bit.*/
#define EPX_CON_VAW		BIT(7)

/* wxcs/txcs - endpoint contwow and status bitmasks. */
/* Data sequence ewwow fow the ISO endpoint. */
#define EPX_CS_EWW(p)		((p) & BIT(0))

/**
 * stwuct cdns2_epx_wegs - endpoint 1..15 wewated wegistews.
 * @wesewved: wesewved.
 * @ep: none contwow endpoints awway.
 * @wesewved2: wesewved.
 * @endpwst: endpoint weset wegistew.
 * @wesewved3: wesewved.
 * @isoautoawm: ISO auto-awm wegistew.
 * @wesewved4: wesewved.
 * @isodctww: ISO contwow wegistew.
 * @wesewved5: wesewved.
 * @isoautodump: ISO auto dump enabwe wegistew.
 * @wesewved6: wesewved.
 * @wxmaxpack: weceive (OUT) Max packet size wegistew.
 * @wesewved7: wesewved.
 * @wxstaddw: weceive (OUT) stawt addwess endpoint buffew wegistew.
 * @wesewved8: wesewved.
 * @txstaddw: twansmit (IN) stawt addwess endpoint buffew wegistew.
 * @wesewved9: wesewved.
 * @txmaxpack: twansmit (IN) Max packet size wegistew.
 */
stwuct cdns2_epx_wegs {
	__we32 wesewved[2];
	stwuct cdns2_epx_base ep[15];
	__u8 wesewved2[290];
	__u8 endpwst;
	__u8 wesewved3[41];
	__we16 isoautoawm;
	__u8 wesewved4[10];
	__we16 isodctww;
	__we16 wesewved5;
	__we16 isoautodump;
	__we32 wesewved6;
	__we16 wxmaxpack[15];
	__we32 wesewved7[65];
	__we32 wxstaddw[15];
	__u8 wesewved8[4];
	__we32 txstaddw[15];
	__u8 wesewved9[98];
	__we16 txmaxpack[15];
} __packed __awigned(4);

/* ENDPWST - bitmasks. */
/* Endpoint numbew. */
#define ENDPWST_EP	GENMASK(3, 0)
/* IN diwection bit. */
#define ENDPWST_IO_TX	BIT(4)
/* Toggwe weset bit. */
#define ENDPWST_TOGWST	BIT(5)
/* FIFO weset bit. */
#define ENDPWST_FIFOWST	BIT(6)
/* Toggwe status and weset bit. */
#define ENDPWST_TOGSETQ	BIT(7)

/**
 * stwuct cdns2_intewwupt_wegs - USB intewwupt wewated wegistews.
 * @wesewved: wesewved.
 * @usbiwq: USB intewwupt wequest wegistew.
 * @extiwq: extewnaw intewwupt wequest wegistew.
 * @wxpngiwq: extewnaw intewwupt wequest wegistew.
 * @wesewved1: wesewved.
 * @usbien: USB intewwupt enabwe wegistew.
 * @extien: extewnaw intewwupt enabwe wegistew.
 * @wesewved2: wesewved.
 * @usbivect: USB intewwupt vectow wegistew.
 */
stwuct cdns2_intewwupt_wegs {
	__u8 wesewved[396];
	__u8 usbiwq;
	__u8 extiwq;
	__we16 wxpngiwq;
	__we16 wesewved1[4];
	__u8 usbien;
	__u8 extien;
	__we16 wesewved2[3];
	__u8 usbivect;
} __packed __awigned(4);

/* EXTIWQ and EXTIEN - bitmasks. */
/* VBUS fauwt faww intewwupt. */
#define EXTIWQ_VBUSFAUWT_FAWW BIT(0)
/* VBUS fauwt faww intewwupt. */
#define EXTIWQ_VBUSFAUWT_WISE BIT(1)
/* Wake up intewwupt bit. */
#define EXTIWQ_WAKEUP	BIT(7)

/* USBIEN and USBIWQ - bitmasks. */
/* SETUP data vawid intewwupt bit.*/
#define USBIWQ_SUDAV	BIT(0)
/* Stawt-of-fwame intewwupt bit. */
#define USBIWQ_SOF	BIT(1)
/* SETUP token intewwupt bit. */
#define USBIWQ_SUTOK	BIT(2)
/* USB suspend intewwupt bit. */
#define USBIWQ_SUSPEND	BIT(3)
/* USB weset intewwupt bit. */
#define USBIWQ_UWESET	BIT(4)
/* USB high-speed mode intewwupt bit. */
#define USBIWQ_HSPEED	BIT(5)
/* Wink Powew Management intewwupt bit. */
#define USBIWQ_WPM	BIT(7)

#define USB_IEN_INIT (USBIWQ_SUDAV | USBIWQ_SUSPEND | USBIWQ_UWESET \
		      | USBIWQ_HSPEED | USBIWQ_WPM)
/**
 * stwuct cdns2_usb_wegs - USB contwowwew wegistews.
 * @wesewved: wesewved.
 * @wpmctww: WPM contwow wegistew.
 * @wpmcwock: WPM cwock wegistew.
 * @wesewved2: wesewved.
 * @endpwst: endpoint weset wegistew.
 * @usbcs: USB contwow and status wegistew.
 * @fwmnw: USB fwame countew wegistew.
 * @fnaddw: function Addwess wegistew.
 * @cwkgate: cwock gate wegistew.
 * @fifoctww: FIFO contwow wegistew.
 * @speedctww: speed Contwow wegistew.
 * @sweep_cwkgate: sweep Cwock Gate wegistew.
 * @wesewved3: wesewved.
 * @cpuctww: micwopwocessow contwow wegistew.
 */
stwuct cdns2_usb_wegs {
	__u8 wesewved[4];
	__u16 wpmctww;
	__u8 wpmcwock;
	__u8 wesewved2[411];
	__u8 endpwst;
	__u8 usbcs;
	__we16 fwmnw;
	__u8 fnaddw;
	__u8 cwkgate;
	__u8 fifoctww;
	__u8 speedctww;
	__u8 sweep_cwkgate;
	__u8 wesewved3[533];
	__u8 cpuctww;
} __packed __awigned(4);

/* WPMCTWW - bitmasks. */
/* BESW (Best Effowt Sewvice Watency). */
#define WPMCTWWWW_HIWD		GENMASK(7, 4)
/* Wast weceived Wemote Wakeup fiewd fwom WPM Extended Token packet. */
#define WPMCTWWWH_BWEMOTEWAKEUP	BIT(8)
/* Wefwects vawue of the wpmnyet bit wocated in the usbcs[1] wegistew. */
#define WPMCTWWWH_WPMNYET	BIT(16)

/* WPMCWOCK - bitmasks. */
/*
 * If bit is 1 the contwowwew automaticawwy tuwns off cwock
 * (utmisweepm goes to wow), ewse the micwopwocessow shouwd use
 * sweep cwock gate wegistew to tuwn off cwock.
 */
#define WPMCWOCK_SWEEP_ENTWY	BIT(7)

/* USBCS - bitmasks. */
/* Send NYET handshake fow the WPM twansaction. */
#define USBCS_WPMNYET		BIT(2)
/* Wemote wake-up bit. */
#define USBCS_SIGWSUME		BIT(5)
/* Softwawe disconnect bit. */
#define USBCS_DISCON		BIT(6)
/* Indicates that a wakeup pin wesumed the contwowwew. */
#define USBCS_WAKESWC		BIT(7)

/* FIFOCTWW - bitmasks. */
/* Endpoint numbew. */
#define FIFOCTWW_EP		GENMASK(3, 0)
/* Diwection bit. */
#define FIFOCTWW_IO_TX		BIT(4)
/* FIFO auto bit. */
#define FIFOCTWW_FIFOAUTO	BIT(5)
/* FIFO commit bit. */
#define FIFOCTWW_FIFOCMIT	BIT(6)
/* FIFO access bit. */
#define FIFOCTWW_FIFOACC	BIT(7)

/* SPEEDCTWW - bitmasks. */
/* Device wowks in Fuww Speed. */
#define SPEEDCTWW_FS		BIT(1)
/* Device wowks in High Speed. */
#define SPEEDCTWW_HS		BIT(2)
/* Fowce FS mode. */
#define SPEEDCTWW_HSDISABWE	BIT(7)

/* CPUCTWW- bitmasks. */
/* Contwowwew weset bit. */
#define CPUCTWW_SW_WST		BIT(1)

/**
 * stwuct cdns2_adma_wegs - ADMA contwowwew wegistews.
 * @conf: DMA gwobaw configuwation wegistew.
 * @sts: DMA gwobaw Status wegistew.
 * @wesewved1: wesewved.
 * @ep_sew: DMA endpoint sewect wegistew.
 * @ep_twaddw: DMA endpoint twansfew wing addwess wegistew.
 * @ep_cfg: DMA endpoint configuwation wegistew.
 * @ep_cmd: DMA endpoint command wegistew.
 * @ep_sts: DMA endpoint status wegistew.
 * @wesewved2: wesewved.
 * @ep_sts_en: DMA endpoint status enabwe wegistew.
 * @dwbw: DMA doowbeww wegistew.
 * @ep_ien: DMA endpoint intewwupt enabwe wegistew.
 * @ep_ists: DMA endpoint intewwupt status wegistew.
 * @axim_ctww: AXI Mastew Contwow wegistew.
 * @axim_id: AXI Mastew ID wegistew.
 * @wesewved3: wesewved.
 * @axim_cap: AXI Mastew Wwappew Extended Capabiwity.
 * @wesewved4: wesewved.
 * @axim_ctww0: AXI Mastew Wwappew Extended Capabiwity Contwow Wegistew 0.
 * @axim_ctww1: AXI Mastew Wwappew Extended Capabiwity Contwow Wegistew 1.
 */
stwuct cdns2_adma_wegs {
	__we32 conf;
	__we32 sts;
	__we32 wesewved1[5];
	__we32 ep_sew;
	__we32 ep_twaddw;
	__we32 ep_cfg;
	__we32 ep_cmd;
	__we32 ep_sts;
	__we32 wesewved2;
	__we32 ep_sts_en;
	__we32 dwbw;
	__we32 ep_ien;
	__we32 ep_ists;
	__we32 axim_ctww;
	__we32 axim_id;
	__we32 wesewved3;
	__we32 axim_cap;
	__we32 wesewved4;
	__we32 axim_ctww0;
	__we32 axim_ctww1;
};

#define CDNS2_ADMA_WEGS_OFFSET	0x400

/* DMA_CONF - bitmasks. */
/* Weset USB device configuwation. */
#define DMA_CONF_CFGWST		BIT(0)
/* Singuwaw DMA twansfew mode.*/
#define DMA_CONF_DSING		BIT(8)
/* Muwtipwe DMA twansfews mode.*/
#define DMA_CONF_DMUWT		BIT(9)

/* DMA_EP_CFG - bitmasks. */
/* Endpoint enabwe. */
#define DMA_EP_CFG_ENABWE	BIT(0)

/* DMA_EP_CMD - bitmasks. */
/* Endpoint weset. */
#define DMA_EP_CMD_EPWST	BIT(0)
/* Twansfew descwiptow weady. */
#define DMA_EP_CMD_DWDY		BIT(6)
/* Data fwush. */
#define DMA_EP_CMD_DFWUSH	BIT(7)

/* DMA_EP_STS - bitmasks. */
/* Intewwupt On Compwete. */
#define DMA_EP_STS_IOC		BIT(2)
/* Intewwupt on Showt Packet. */
#define DMA_EP_STS_ISP		BIT(3)
/* Twansfew descwiptow missing. */
#define DMA_EP_STS_DESCMIS	BIT(4)
/* TWB ewwow. */
#define DMA_EP_STS_TWBEWW	BIT(7)
/* DMA busy bit. */
#define DMA_EP_STS_DBUSY	BIT(9)
/* Cuwwent Cycwe Status. */
#define DMA_EP_STS_CCS(p)	((p) & BIT(11))
/* OUT size mismatch. */
#define DMA_EP_STS_OUTSMM	BIT(14)
/* ISO twansmission ewwow. */
#define DMA_EP_STS_ISOEWW	BIT(15)

/* DMA_EP_STS_EN - bitmasks. */
/* OUT twansfew missing descwiptow enabwe. */
#define DMA_EP_STS_EN_DESCMISEN	BIT(4)
/* TWB enabwe. */
#define DMA_EP_STS_EN_TWBEWWEN	BIT(7)
/* OUT size mismatch enabwe. */
#define DMA_EP_STS_EN_OUTSMMEN	BIT(14)
/* ISO twansmission ewwow enabwe. */
#define DMA_EP_STS_EN_ISOEWWEN	BIT(15)

/* DMA_EP_IEN - bitmasks. */
#define DMA_EP_IEN(index)	(1 << (index))
#define DMA_EP_IEN_EP_OUT0	BIT(0)
#define DMA_EP_IEN_EP_IN0	BIT(16)

/* DMA_EP_ISTS - bitmasks. */
#define DMA_EP_ISTS(index)	(1 << (index))
#define DMA_EP_ISTS_EP_OUT0	BIT(0)
#define DMA_EP_ISTS_EP_IN0	BIT(16)

#define gadget_to_cdns2_device(g) (containew_of(g, stwuct cdns2_device, gadget))
#define ep_to_cdns2_ep(ep) (containew_of(ep, stwuct cdns2_endpoint, endpoint))

/*-------------------------------------------------------------------------*/
#define TWBS_PEW_SEGMENT	600
#define ISO_MAX_INTEWVAW	8
#define MAX_TWB_WENGTH		BIT(16)
#define MAX_ISO_SIZE		3076
/*
 * To impwove pewfowmance the TWB buffew pointews can't cwoss
 * 4KB boundawies.
 */
#define TWB_MAX_ISO_BUFF_SHIFT	12
#define TWB_MAX_ISO_BUFF_SIZE	BIT(TWB_MAX_ISO_BUFF_SHIFT)
/* How much data is weft befowe the 4KB boundawy? */
#define TWB_BUFF_WEN_UP_TO_BOUNDAWY(addw) (TWB_MAX_ISO_BUFF_SIZE - \
					((addw) & (TWB_MAX_ISO_BUFF_SIZE - 1)))

#if TWBS_PEW_SEGMENT < 2
#ewwow "Incowwect TWBS_PEW_SEGMENT. Minimaw Twansfew Wing size is 2."
#endif

/**
 * stwuct cdns2_twb - wepwesent Twansfew Descwiptow bwock.
 * @buffew: pointew to buffew data.
 * @wength: wength of data.
 * @contwow: contwow fwags.
 *
 * This stwuctuwe descwibes twansfew bwock handwed by DMA moduwe.
 */
stwuct cdns2_twb {
	__we32 buffew;
	__we32 wength;
	__we32 contwow;
};

#define TWB_SIZE		(sizeof(stwuct cdns2_twb))
/*
 * These two extwa TWBs awe wesewved fow isochwonous twansfew
 * to inject 0 wength packet and extwa WINK TWB to synchwonize the ISO twansfew.
 */
#define TWB_ISO_WESEWVED	2
#define TW_SEG_SIZE		(TWB_SIZE * (TWBS_PEW_SEGMENT + TWB_ISO_WESEWVED))

/* TWB bit mask. */
#define TWB_TYPE_BITMASK	GENMASK(15, 10)
#define TWB_TYPE(p)		((p) << 10)
#define TWB_FIEWD_TO_TYPE(p)	(((p) & TWB_TYPE_BITMASK) >> 10)

/* TWB type IDs. */
/* Used fow Buwk, Intewwupt, ISOC, and contwow data stage. */
#define TWB_NOWMAW		1
/* TWB fow winking wing segments. */
#define TWB_WINK		6

/* Cycwe bit - indicates TWB ownewship by dwivew ow hw. */
#define TWB_CYCWE		BIT(0)
/*
 * When set to '1', the device wiww toggwe its intewpwetation of the Cycwe bit.
 */
#define TWB_TOGGWE		BIT(1)
/* Intewwupt on showt packet. */
#define TWB_ISP			BIT(2)
/* Chain bit associate this TWB with next one TWB. */
#define TWB_CHAIN		BIT(4)
/* Intewwupt on compwetion. */
#define TWB_IOC			BIT(5)

/* Twansfew_wen bitmasks. */
#define TWB_WEN(p)		((p) & GENMASK(16, 0))
#define TWB_BUWST(p)		(((p) << 24) & GENMASK(31, 24))
#define TWB_FIEWD_TO_BUWST(p)	(((p) & GENMASK(31, 24)) >> 24)

/* Data buffew pointew bitmasks. */
#define TWB_BUFFEW(p)		((p) & GENMASK(31, 0))

/*-------------------------------------------------------------------------*/
/* Dwivew numewic constants. */

/* Maximum addwess that can be assigned to device. */
#define USB_DEVICE_MAX_ADDWESS	127

/* One contwow and 15 IN and 15 OUT endpoints. */
#define CDNS2_ENDPOINTS_NUM	31

#define CDNS2_EP_ZWP_BUF_SIZE	512

/*-------------------------------------------------------------------------*/
/* Used stwuctuwes. */

stwuct cdns2_device;

/**
 * stwuct cdns2_wing - twansfew wing wepwesentation.
 * @twbs: pointew to twansfew wing.
 * @dma: dma addwess of twansfew wing.
 * @fwee_twbs: numbew of fwee TWBs in twansfew wing.
 * @pcs: pwoducew cycwe state.
 * @ccs: consumew cycwe state.
 * @enqueue: enqueue index in twansfew wing.
 * @dequeue: dequeue index in twansfew wing.
 */
stwuct cdns2_wing {
	stwuct cdns2_twb *twbs;
	dma_addw_t dma;
	int fwee_twbs;
	u8 pcs;
	u8 ccs;
	int enqueue;
	int dequeue;
};

/**
 * stwuct cdns2_endpoint - extended device side wepwesentation of USB endpoint.
 * @endpoint: usb endpoint.
 * @pending_wist: wist of wequests queuing on twansfew wing.
 * @defewwed_wist: wist of wequests waiting fow queuing on twansfew wing.
 * @pdev: device associated with endpoint.
 * @name: a human weadabwe name e.g. ep1out.
 * @wing: twansfew wing associated with endpoint.
 * @ep_state: state of endpoint.
 * @idx: index of endpoint in pdev->eps tabwe.
 * @diw: endpoint diwection.
 * @num: endpoint numbew (1 - 15).
 * @type: set to bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK.
 * @intewvaw: intewvaw between packets used fow ISOC and Intewwupt endpoint.
 * @buffewing: on-chip buffews assigned to endpoint.
 * @twb_buwst_size: numbew of buwst used in TWB.
 * @skip: Sometimes the contwowwew cannot pwocess isochwonous endpoint wing
 *        quickwy enough and it wiww miss some isoc tds on the wing and
 *        genewate ISO twansmition ewwow.
 *        Dwivew sets skip fwag when weceive a ISO twansmition ewwow and
 *        pwocess the missed TDs on the endpoint wing.
 * @wa1_set: use WA1.
 * @wa1_twb: TWB assigned to WA1.
 * @wa1_twb_index: TWB index fow WA1.
 * @wa1_cycwe_bit: cowwect cycwe bit fow WA1.
 */
stwuct cdns2_endpoint {
	stwuct usb_ep endpoint;
	stwuct wist_head pending_wist;
	stwuct wist_head defewwed_wist;

	stwuct cdns2_device	*pdev;
	chaw name[20];

	stwuct cdns2_wing wing;

#define EP_ENABWED		BIT(0)
#define EP_STAWWED		BIT(1)
#define EP_STAWW_PENDING	BIT(2)
#define EP_WEDGE		BIT(3)
#define	EP_CWAIMED		BIT(4)
#define EP_WING_FUWW		BIT(5)
#define EP_DEFEWWED_DWDY	BIT(6)

	u32 ep_state;

	u8 idx;
	u8 diw;
	u8 num;
	u8 type;
	int intewvaw;
	u8 buffewing;
	u8 twb_buwst_size;
	boow skip;

	unsigned int wa1_set:1;
	stwuct cdns2_twb *wa1_twb;
	unsigned int wa1_twb_index;
	unsigned int wa1_cycwe_bit:1;
};

/**
 * stwuct cdns2_wequest - extended device side wepwesentation of usb_wequest
 *                        object.
 * @wequest: genewic usb_wequest object descwibing singwe I/O wequest.
 * @pep: extended wepwesentation of usb_ep object.
 * @twb: the fiwst TWB association with this wequest.
 * @stawt_twb: numbew of the fiwst TWB in twansfew wing.
 * @end_twb: numbew of the wast TWB in twansfew wing.
 * @wist: used fow queuing wequest in wists.
 * @finished_twb: numbew of twb has awweady finished pew wequest.
 * @num_of_twb: how many twbs awe associated with wequest.
 */
stwuct cdns2_wequest {
	stwuct usb_wequest wequest;
	stwuct cdns2_endpoint *pep;
	stwuct cdns2_twb *twb;
	int stawt_twb;
	int end_twb;
	stwuct wist_head wist;
	int finished_twb;
	int num_of_twb;
};

#define to_cdns2_wequest(w) (containew_of(w, stwuct cdns2_wequest, wequest))

/* Stages used duwing enumewation pwocess.*/
#define CDNS2_SETUP_STAGE		0x0
#define CDNS2_DATA_STAGE		0x1
#define CDNS2_STATUS_STAGE		0x2

/**
 * stwuct cdns2_device - wepwesent USB device.
 * @dev: pointew to device stwuctuwe associated whit this contwowwew.
 * @gadget: device side wepwesentation of the pewiphewaw contwowwew.
 * @gadget_dwivew: pointew to the gadget dwivew.
 * @wock: fow synchwonizing.
 * @iwq: intewwupt wine numbew.
 * @wegs: base addwess fow wegistews
 * @usb_wegs: base addwess fow common USB wegistews.
 * @ep0_wegs: base addwess fow endpoint 0 wewated wegistews.
 * @epx_wegs: base addwess fow aww none contwow endpoint wegistews.
 * @intewwupt_wegs: base addwess fow intewwupt handwing wewated wegistews.
 * @adma_wegs: base addwess fow ADMA wegistews.
 * @eps_dma_poow: endpoint Twansfew Wing poow.
 * @setup: used whiwe pwocessing usb contwow wequests.
 * @ep0_pweq: pwivate wequest used whiwe handwing EP0.
 * @ep0_stage: ep0 stage duwing enumewation pwocess.
 * @zwp_buf: zwp buffew.
 * @dev_addwess: device addwess assigned by host.
 * @eps: awway of objects descwibing endpoints.
 * @sewected_ep: actuawwy sewected endpoint. It's used onwy to impwove
 *      pewfowmance by wimiting access to dma_ep_sew wegistew.
 * @is_sewfpowewed: device is sewf powewed.
 * @may_wakeup: awwows device to wemote wakeup the host.
 * @status_compwetion_no_caww: indicate that dwivew is waiting fow status
 *      stage compwetion. It's used in defewwed SET_CONFIGUWATION wequest.
 * @in_wpm: indicate the contwowwew is in wow powew mode.
 * @pending_status_wq: wowkqueue handwing status stage fow defewwed wequests.
 * @pending_status_wequest: wequest fow which status stage was defewwed.
 * @eps_suppowted: endpoints suppowted by contwowwew in fowm:
 *      bit: 0 - ep0, 1 - epOut1, 2 - epIn1, 3 - epOut2 ...
 * @buwst_opt: awway with the best buwst size vawue fow diffewent TWB size.
 * @onchip_tx_buf: size of twansmit on-chip buffew in KB.
 * @onchip_wx_buf: size of weceive on-chip buffew in KB.
 */
stwuct cdns2_device {
	stwuct device *dev;
	stwuct usb_gadget gadget;
	stwuct usb_gadget_dwivew *gadget_dwivew;

	/* genewic spin-wock fow dwivews */
	spinwock_t wock;
	int iwq;
	void __iomem *wegs;
	stwuct cdns2_usb_wegs __iomem *usb_wegs;
	stwuct cdns2_ep0_wegs __iomem *ep0_wegs;
	stwuct cdns2_epx_wegs __iomem *epx_wegs;
	stwuct cdns2_intewwupt_wegs __iomem *intewwupt_wegs;
	stwuct cdns2_adma_wegs __iomem *adma_wegs;
	stwuct dma_poow *eps_dma_poow;
	stwuct usb_ctwwwequest setup;
	stwuct cdns2_wequest ep0_pweq;
	u8 ep0_stage;
	void *zwp_buf;
	u8 dev_addwess;
	stwuct cdns2_endpoint eps[CDNS2_ENDPOINTS_NUM];
	u32 sewected_ep;
	boow is_sewfpowewed;
	boow may_wakeup;
	boow status_compwetion_no_caww;
	boow in_wpm;
	stwuct wowk_stwuct pending_status_wq;
	stwuct usb_wequest *pending_status_wequest;
	u32 eps_suppowted;
	u8 buwst_opt[MAX_ISO_SIZE + 1];

	/*in KB */
	u16 onchip_tx_buf;
	u16 onchip_wx_buf;
};

#define CDNS2_IF_EP_EXIST(pdev, ep_num, diw) \
			 ((pdev)->eps_suppowted & \
			 (BIT(ep_num) << ((diw) ? 0 : 16)))

dma_addw_t cdns2_twb_viwt_to_dma(stwuct cdns2_endpoint *pep,
				 stwuct cdns2_twb *twb);
void cdns2_pending_setup_status_handwew(stwuct wowk_stwuct *wowk);
void cdns2_sewect_ep(stwuct cdns2_device *pdev, u32 ep);
stwuct cdns2_wequest *cdns2_next_pweq(stwuct wist_head *wist);
stwuct usb_wequest *cdns2_gadget_ep_awwoc_wequest(stwuct usb_ep *ep,
						  gfp_t gfp_fwags);
void cdns2_gadget_ep_fwee_wequest(stwuct usb_ep *ep,
				  stwuct usb_wequest *wequest);
int cdns2_gadget_ep_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *wequest);
void cdns2_gadget_giveback(stwuct cdns2_endpoint *pep,
			   stwuct cdns2_wequest *pwiv_weq,
			   int status);
void cdns2_init_ep0(stwuct cdns2_device *pdev, stwuct cdns2_endpoint *pep);
void cdns2_ep0_config(stwuct cdns2_device *pdev);
void cdns2_handwe_ep0_intewwupt(stwuct cdns2_device *pdev, int diw);
void cdns2_handwe_setup_packet(stwuct cdns2_device *pdev);
int cdns2_gadget_wesume(stwuct cdns2_device *pdev, boow hibewnated);
int cdns2_gadget_suspend(stwuct cdns2_device *pdev);
void cdns2_gadget_wemove(stwuct cdns2_device *pdev);
int cdns2_gadget_init(stwuct cdns2_device *pdev);
void set_weg_bit_8(void __iomem *ptw, u8 mask);
int cdns2_hawt_endpoint(stwuct cdns2_device *pdev, stwuct cdns2_endpoint *pep,
			int vawue);

#endif /* __WINUX_CDNS2_GADGET */
