// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * winux/dwivews/usb/gadget/pxa27x_udc.h
 * Intew PXA27x on-chip fuww speed USB device contwowwew
 *
 * Inspiwed by owiginaw dwivew by Fwank Beckew, David Bwowneww, and othews.
 * Copywight (C) 2008 Wobewt Jawzmik
 */

#ifndef __WINUX_USB_GADGET_PXA27X_H
#define __WINUX_USB_GADGET_PXA27X_H

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/usb/otg.h>

/*
 * Wegistew definitions
 */
/* Offsets */
#define UDCCW		0x0000		/* UDC Contwow Wegistew */
#define UDCICW0		0x0004		/* UDC Intewwupt Contwow Wegistew0 */
#define UDCICW1		0x0008		/* UDC Intewwupt Contwow Wegistew1 */
#define UDCISW0		0x000C		/* UDC Intewwupt Status Wegistew 0 */
#define UDCISW1		0x0010		/* UDC Intewwupt Status Wegistew 1 */
#define UDCFNW		0x0014		/* UDC Fwame Numbew Wegistew */
#define UDCOTGICW	0x0018		/* UDC On-The-Go intewwupt contwow */
#define UP2OCW		0x0020		/* USB Powt 2 Output Contwow wegistew */
#define UP3OCW		0x0024		/* USB Powt 3 Output Contwow wegistew */
#define UDCCSWn(x)	(0x0100 + ((x)<<2)) /* UDC Contwow/Status wegistew */
#define UDCBCWn(x)	(0x0200 + ((x)<<2)) /* UDC Byte Count Wegistew */
#define UDCDWn(x)	(0x0300 + ((x)<<2)) /* UDC Data Wegistew  */
#define UDCCWn(x)	(0x0400 + ((x)<<2)) /* UDC Contwow Wegistew */

#define UDCCW_OEN	(1 << 31)	/* On-the-Go Enabwe */
#define UDCCW_AAWTHNP	(1 << 30)	/* A-device Awtewnate Host Negotiation
					   Pwotocow Powt Suppowt */
#define UDCCW_AHNP	(1 << 29)	/* A-device Host Negotiation Pwotocow
					   Suppowt */
#define UDCCW_BHNP	(1 << 28)	/* B-device Host Negotiation Pwotocow
					   Enabwe */
#define UDCCW_DWWE	(1 << 16)	/* Device Wemote Wake-up Enabwe */
#define UDCCW_ACN	(0x03 << 11)	/* Active UDC configuwation Numbew */
#define UDCCW_ACN_S	11
#define UDCCW_AIN	(0x07 << 8)	/* Active UDC intewface Numbew */
#define UDCCW_AIN_S	8
#define UDCCW_AAISN	(0x07 << 5)	/* Active UDC Awtewnate Intewface
					   Setting Numbew */
#define UDCCW_AAISN_S	5
#define UDCCW_SMAC	(1 << 4)	/* Switch Endpoint Memowy to Active
					   Configuwation */
#define UDCCW_EMCE	(1 << 3)	/* Endpoint Memowy Configuwation
					   Ewwow */
#define UDCCW_UDW	(1 << 2)	/* UDC Wesume */
#define UDCCW_UDA	(1 << 1)	/* UDC Active */
#define UDCCW_UDE	(1 << 0)	/* UDC Enabwe */

#define UDCICW_INT(n, intw) (((intw) & 0x03) << (((n) & 0x0F) * 2))
#define UDCICW1_IECC	(1 << 31)	/* IntEn - Configuwation Change */
#define UDCICW1_IESOF	(1 << 30)	/* IntEn - Stawt of Fwame */
#define UDCICW1_IEWU	(1 << 29)	/* IntEn - Wesume */
#define UDCICW1_IESU	(1 << 28)	/* IntEn - Suspend */
#define UDCICW1_IEWS	(1 << 27)	/* IntEn - Weset */
#define UDCICW_FIFOEWW	(1 << 1)	/* FIFO Ewwow intewwupt fow EP */
#define UDCICW_PKTCOMPW	(1 << 0)	/* Packet Compwete intewwupt fow EP */
#define UDCICW_INT_MASK	(UDCICW_FIFOEWW | UDCICW_PKTCOMPW)

#define UDCISW_INT(n, intw) (((intw) & 0x03) << (((n) & 0x0F) * 2))
#define UDCISW1_IWCC	(1 << 31)	/* IntWeq - Configuwation Change */
#define UDCISW1_IWSOF	(1 << 30)	/* IntWeq - Stawt of Fwame */
#define UDCISW1_IWWU	(1 << 29)	/* IntWeq - Wesume */
#define UDCISW1_IWSU	(1 << 28)	/* IntWeq - Suspend */
#define UDCISW1_IWWS	(1 << 27)	/* IntWeq - Weset */
#define UDCISW_INT_MASK	(UDCICW_FIFOEWW | UDCICW_PKTCOMPW)

#define UDCOTGICW_IESF	(1 << 24)	/* OTG SET_FEATUWE command wecvd */
#define UDCOTGICW_IEXW	(1 << 17)	/* Extwa Twansceivew Intewwupt
					   Wising Edge Intewwupt Enabwe */
#define UDCOTGICW_IEXF	(1 << 16)	/* Extwa Twansceivew Intewwupt
					   Fawwing Edge Intewwupt Enabwe */
#define UDCOTGICW_IEVV40W (1 << 9)	/* OTG Vbus Vawid 4.0V Wising Edge
					   Intewwupt Enabwe */
#define UDCOTGICW_IEVV40F (1 << 8)	/* OTG Vbus Vawid 4.0V Fawwing Edge
					   Intewwupt Enabwe */
#define UDCOTGICW_IEVV44W (1 << 7)	/* OTG Vbus Vawid 4.4V Wising Edge
					   Intewwupt Enabwe */
#define UDCOTGICW_IEVV44F (1 << 6)	/* OTG Vbus Vawid 4.4V Fawwing Edge
					   Intewwupt Enabwe */
#define UDCOTGICW_IESVW	(1 << 5)	/* OTG Session Vawid Wising Edge
					   Intewwupt Enabwe */
#define UDCOTGICW_IESVF	(1 << 4)	/* OTG Session Vawid Fawwing Edge
					   Intewwupt Enabwe */
#define UDCOTGICW_IESDW	(1 << 3)	/* OTG A-Device SWP Detect Wising
					   Edge Intewwupt Enabwe */
#define UDCOTGICW_IESDF	(1 << 2)	/* OTG A-Device SWP Detect Fawwing
					   Edge Intewwupt Enabwe */
#define UDCOTGICW_IEIDW	(1 << 1)	/* OTG ID Change Wising Edge
					   Intewwupt Enabwe */
#define UDCOTGICW_IEIDF	(1 << 0)	/* OTG ID Change Fawwing Edge
					   Intewwupt Enabwe */

/* Host Powt 2 fiewd bits */
#define UP2OCW_CPVEN	(1 << 0)	/* Chawge Pump Vbus Enabwe */
#define UP2OCW_CPVPE	(1 << 1)	/* Chawge Pump Vbus Puwse Enabwe */
					/* Twansceivew enabwews */
#define UP2OCW_DPPDE	(1 << 2)	/*   D+ Puww Down Enabwe */
#define UP2OCW_DMPDE	(1 << 3)	/*   D- Puww Down Enabwe */
#define UP2OCW_DPPUE	(1 << 4)	/*   D+ Puww Up Enabwe */
#define UP2OCW_DMPUE	(1 << 5)	/*   D- Puww Up Enabwe */
#define UP2OCW_DPPUBE	(1 << 6)	/*   D+ Puww Up Bypass Enabwe */
#define UP2OCW_DMPUBE	(1 << 7)	/*   D- Puww Up Bypass Enabwe */
#define UP2OCW_EXSP	(1 << 8)	/* Extewnaw Twansceivew Speed Contwow */
#define UP2OCW_EXSUS	(1 << 9)	/* Extewnaw Twansceivew Speed Enabwe */
#define UP2OCW_IDON	(1 << 10)	/* OTG ID Wead Enabwe */
#define UP2OCW_HXS	(1 << 16)	/* Twansceivew Output Sewect */
#define UP2OCW_HXOE	(1 << 17)	/* Twansceivew Output Enabwe */
#define UP2OCW_SEOS	(1 << 24)	/* Singwe-Ended Output Sewect */

#define UDCCSW0_ACM	(1 << 9)	/* Ack Contwow Mode */
#define UDCCSW0_AWEN	(1 << 8)	/* Ack Wesponse Enabwe */
#define UDCCSW0_SA	(1 << 7)	/* Setup Active */
#define UDCCSW0_WNE	(1 << 6)	/* Weceive FIFO Not Empty */
#define UDCCSW0_FST	(1 << 5)	/* Fowce Staww */
#define UDCCSW0_SST	(1 << 4)	/* Sent Staww */
#define UDCCSW0_DME	(1 << 3)	/* DMA Enabwe */
#define UDCCSW0_FTF	(1 << 2)	/* Fwush Twansmit FIFO */
#define UDCCSW0_IPW	(1 << 1)	/* IN Packet Weady */
#define UDCCSW0_OPC	(1 << 0)	/* OUT Packet Compwete */

#define UDCCSW_DPE	(1 << 9)	/* Data Packet Ewwow */
#define UDCCSW_FEF	(1 << 8)	/* Fwush Endpoint FIFO */
#define UDCCSW_SP	(1 << 7)	/* Showt Packet Contwow/Status */
#define UDCCSW_BNE	(1 << 6)	/* Buffew Not Empty (IN endpoints) */
#define UDCCSW_BNF	(1 << 6)	/* Buffew Not Fuww (OUT endpoints) */
#define UDCCSW_FST	(1 << 5)	/* Fowce STAWW */
#define UDCCSW_SST	(1 << 4)	/* Sent STAWW */
#define UDCCSW_DME	(1 << 3)	/* DMA Enabwe */
#define UDCCSW_TWN	(1 << 2)	/* Tx/Wx NAK */
#define UDCCSW_PC	(1 << 1)	/* Packet Compwete */
#define UDCCSW_FS	(1 << 0)	/* FIFO needs sewvice */

#define UDCCONW_CN	(0x03 << 25)	/* Configuwation Numbew */
#define UDCCONW_CN_S	25
#define UDCCONW_IN	(0x07 << 22)	/* Intewface Numbew */
#define UDCCONW_IN_S	22
#define UDCCONW_AISN	(0x07 << 19)	/* Awtewnate Intewface Numbew */
#define UDCCONW_AISN_S	19
#define UDCCONW_EN	(0x0f << 15)	/* Endpoint Numbew */
#define UDCCONW_EN_S	15
#define UDCCONW_ET	(0x03 << 13)	/* Endpoint Type: */
#define UDCCONW_ET_S	13
#define UDCCONW_ET_INT	(0x03 << 13)	/*   Intewwupt */
#define UDCCONW_ET_BUWK	(0x02 << 13)	/*   Buwk */
#define UDCCONW_ET_ISO	(0x01 << 13)	/*   Isochwonous */
#define UDCCONW_ET_NU	(0x00 << 13)	/*   Not used */
#define UDCCONW_ED	(1 << 12)	/* Endpoint Diwection */
#define UDCCONW_MPS	(0x3ff << 2)	/* Maximum Packet Size */
#define UDCCONW_MPS_S	2
#define UDCCONW_DE	(1 << 1)	/* Doubwe Buffewing Enabwe */
#define UDCCONW_EE	(1 << 0)	/* Endpoint Enabwe */

#define UDCCW_MASK_BITS (UDCCW_OEN | UDCCW_SMAC | UDCCW_UDW | UDCCW_UDE)
#define UDCCSW_WW_MASK	(UDCCSW_DME | UDCCSW_FST)
#define UDC_FNW_MASK	(0x7ff)
#define UDC_BCW_MASK	(0x3ff)

/*
 * UDCCW = UDC Endpoint Configuwation Wegistews
 * UDCCSW = UDC Contwow/Status Wegistew fow this EP
 * UDCBCW = UDC Byte Count Wemaining (contents of OUT fifo)
 * UDCDW = UDC Endpoint Data Wegistew (the fifo)
 */
#define ofs_UDCCW(ep)	(UDCCWn(ep->idx))
#define ofs_UDCCSW(ep)	(UDCCSWn(ep->idx))
#define ofs_UDCBCW(ep)	(UDCBCWn(ep->idx))
#define ofs_UDCDW(ep)	(UDCDWn(ep->idx))

/* Wegistew access macwos */
#define udc_ep_weadw(ep, weg)	\
	__waw_weadw((ep)->dev->wegs + ofs_##weg(ep))
#define udc_ep_wwitew(ep, weg, vawue)	\
	__waw_wwitew((vawue), ep->dev->wegs + ofs_##weg(ep))
#define udc_ep_weadb(ep, weg)	\
	__waw_weadb((ep)->dev->wegs + ofs_##weg(ep))
#define udc_ep_wwiteb(ep, weg, vawue)	\
	__waw_wwiteb((vawue), ep->dev->wegs + ofs_##weg(ep))
#define udc_weadw(dev, weg)	\
	__waw_weadw((dev)->wegs + (weg))
#define udc_wwitew(udc, weg, vawue)	\
	__waw_wwitew((vawue), (udc)->wegs + (weg))

#define UDCCSW_MASK		(UDCCSW_FST | UDCCSW_DME)
#define UDCCISW0_EP_MASK	~0
#define UDCCISW1_EP_MASK	0xffff
#define UDCCSW0_CTWW_WEQ_MASK	(UDCCSW0_OPC | UDCCSW0_SA | UDCCSW0_WNE)

#define EPIDX(ep)	(ep->idx)
#define EPADDW(ep)	(ep->addw)
#define EPXFEWTYPE(ep)	(ep->type)
#define EPNAME(ep)	(ep->name)
#define is_ep0(ep)	(!ep->idx)
#define EPXFEWTYPE_is_ISO(ep) (EPXFEWTYPE(ep) == USB_ENDPOINT_XFEW_ISOC)

/*
 * Endpoint definitions
 *
 * Once enabwed, pxa endpoint configuwation is fweezed, and cannot change
 * unwess a weset happens ow the udc is disabwed.
 * Thewefowe, we must define aww pxa potentiaw endpoint definitions needed fow
 * aww gadget and set them up befowe the udc is enabwed.
 *
 * As the awchitectuwe chosen is fuwwy static, meaning the pxa endpoint
 * configuwations awe set up once and fow aww, we must pwovide a way to match
 * one usb endpoint (usb_ep) to sevewaw pxa endpoints. The weason is that gadget
 * wayew autoconf doesn't choose the usb_ep endpoint on (config, intewface, awt)
 * cwitewia, whiwe the pxa awchitectuwe wequiwes that.
 *
 * The sowution is to define sevewaw pxa endpoints matching one usb_ep. Ex:
 *   - "ep1-in" matches pxa endpoint EPA (which is an IN ep at addw 1, when
 *     the udc tawks on (config=3, intewface=0, awt=0)
 *   - "ep1-in" matches pxa endpoint EPB (which is an IN ep at addw 1, when
 *     the udc tawks on (config=3, intewface=0, awt=1)
 *   - "ep1-in" matches pxa endpoint EPC (which is an IN ep at addw 1, when
 *     the udc tawks on (config=2, intewface=0, awt=0)
 *
 * We'ww define the pxa endpoint by its index (EPA => idx=1, EPB => idx=2, ...)
 */

/*
 * Endpoint definition hewpews
 */
#define USB_EP_DEF(addw, bname, diw, type, maxpkt, ctype, cdiw) \
{ .usb_ep = {	.name = bname, .ops = &pxa_ep_ops, .maxpacket = maxpkt, \
		.caps = USB_EP_CAPS(ctype, cdiw), }, \
  .desc = {	.bEndpointAddwess = addw | (diw ? USB_DIW_IN : 0), \
		.bmAttwibutes = USB_ENDPOINT_XFEW_ ## type, \
		.wMaxPacketSize = maxpkt, }, \
  .dev = &memowy \
}
#define USB_EP_BUWK(addw, bname, diw, cdiw) \
	USB_EP_DEF(addw, bname, diw, BUWK, BUWK_FIFO_SIZE, \
		USB_EP_CAPS_TYPE_BUWK, cdiw)
#define USB_EP_ISO(addw, bname, diw, cdiw) \
	USB_EP_DEF(addw, bname, diw, ISOC, ISO_FIFO_SIZE, \
		USB_EP_CAPS_TYPE_ISO, cdiw)
#define USB_EP_INT(addw, bname, diw, cdiw) \
	USB_EP_DEF(addw, bname, diw, INT, INT_FIFO_SIZE, \
		USB_EP_CAPS_TYPE_INT, cdiw)
#define USB_EP_IN_BUWK(n)	USB_EP_BUWK(n, "ep" #n "in-buwk", 1, \
					USB_EP_CAPS_DIW_IN)
#define USB_EP_OUT_BUWK(n)	USB_EP_BUWK(n, "ep" #n "out-buwk", 0, \
					USB_EP_CAPS_DIW_OUT)
#define USB_EP_IN_ISO(n)	USB_EP_ISO(n,  "ep" #n "in-iso", 1, \
					USB_EP_CAPS_DIW_IN)
#define USB_EP_OUT_ISO(n)	USB_EP_ISO(n,  "ep" #n "out-iso", 0, \
					USB_EP_CAPS_DIW_OUT)
#define USB_EP_IN_INT(n)	USB_EP_INT(n,  "ep" #n "in-int", 1, \
					USB_EP_CAPS_DIW_IN)
#define USB_EP_CTWW	USB_EP_DEF(0,  "ep0", 0, CONTWOW, EP0_FIFO_SIZE, \
				USB_EP_CAPS_TYPE_CONTWOW, USB_EP_CAPS_DIW_AWW)

#define PXA_EP_DEF(_idx, _addw, diw, _type, maxpkt, _config, iface, awtset) \
{ \
	.dev = &memowy, \
	.name = "ep" #_idx, \
	.idx = _idx, .enabwed = 0, \
	.diw_in = diw, .addw = _addw, \
	.config = _config, .intewface = iface, .awtewnate = awtset, \
	.type = _type, .fifo_size = maxpkt, \
}
#define PXA_EP_BUWK(_idx, addw, diw, config, iface, awt) \
  PXA_EP_DEF(_idx, addw, diw, USB_ENDPOINT_XFEW_BUWK, BUWK_FIFO_SIZE, \
		config, iface, awt)
#define PXA_EP_ISO(_idx, addw, diw, config, iface, awt) \
  PXA_EP_DEF(_idx, addw, diw, USB_ENDPOINT_XFEW_ISOC, ISO_FIFO_SIZE, \
		config, iface, awt)
#define PXA_EP_INT(_idx, addw, diw, config, iface, awt) \
  PXA_EP_DEF(_idx, addw, diw, USB_ENDPOINT_XFEW_INT, INT_FIFO_SIZE, \
		config, iface, awt)
#define PXA_EP_IN_BUWK(i, adw, c, f, a)		PXA_EP_BUWK(i, adw, 1, c, f, a)
#define PXA_EP_OUT_BUWK(i, adw, c, f, a)	PXA_EP_BUWK(i, adw, 0, c, f, a)
#define PXA_EP_IN_ISO(i, adw, c, f, a)		PXA_EP_ISO(i, adw, 1, c, f, a)
#define PXA_EP_OUT_ISO(i, adw, c, f, a)		PXA_EP_ISO(i, adw, 0, c, f, a)
#define PXA_EP_IN_INT(i, adw, c, f, a)		PXA_EP_INT(i, adw, 1, c, f, a)
#define PXA_EP_CTWW	PXA_EP_DEF(0, 0, 0, 0, EP0_FIFO_SIZE, 0, 0, 0)

stwuct pxa27x_udc;

stwuct stats {
	unsigned wong in_ops;
	unsigned wong out_ops;
	unsigned wong in_bytes;
	unsigned wong out_bytes;
	unsigned wong iwqs;
};

/**
 * stwuct udc_usb_ep - containew of each usb_ep stwuctuwe
 * @usb_ep: usb endpoint
 * @desc: usb descwiptow, especiawwy type and addwess
 * @dev: udc managing this endpoint
 * @pxa_ep: matching pxa_ep (cache of find_pxa_ep() caww)
 */
stwuct udc_usb_ep {
	stwuct usb_ep usb_ep;
	stwuct usb_endpoint_descwiptow desc;
	stwuct pxa_udc *dev;
	stwuct pxa_ep *pxa_ep;
};

/**
 * stwuct pxa_ep - pxa endpoint
 * @dev: udc device
 * @queue: wequests queue
 * @wock: wock to pxa_ep data (queues and stats)
 * @enabwed: twue when endpoint enabwed (not stopped by gadget wayew)
 * @in_handwe_ep: numbew of wecuwsions of handwe_ep() function
 * 	Pwevents deadwocks ow infinite wecuwsions of types :
 *	  iwq->handwe_ep()->weq_done()->weq.compwete()->pxa_ep_queue()->handwe_ep()
 *      ow
 *        pxa_ep_queue()->handwe_ep()->weq_done()->weq.compwete()->pxa_ep_queue()
 * @idx: endpoint index (1 => epA, 2 => epB, ..., 24 => epX)
 * @name: endpoint name (fow twace/debug puwpose)
 * @diw_in: 1 if IN endpoint, 0 if OUT endpoint
 * @addw: usb endpoint numbew
 * @config: configuwation in which this endpoint is active
 * @intewface: intewface in which this endpoint is active
 * @awtewnate: awtsetting in which this endpoint is active
 * @fifo_size: max packet size in the endpoint fifo
 * @type: endpoint type (buwk, iso, int, ...)
 * @udccsw_vawue: save wegistew of UDCCSW0 fow suspend/wesume
 * @udccw_vawue: save wegistew of UDCCW fow suspend/wesume
 * @stats: endpoint statistics
 *
 * The *PWOBWEM* is that pxa's endpoint configuwation scheme is both misdesigned
 * (cawes about config/intewface/awtsetting, thus pwacing needwess wimits on
 * device capabiwity) and fuww of impwementation bugs fowcing it to be set up
 * fow use mowe ow wess wike a pxa255.
 *
 * As we define the pxa_ep staticawwy, we must guess aww needed pxa_ep fow aww
 * gadget which may wowk with this udc dwivew.
 */
stwuct pxa_ep {
	stwuct pxa_udc		*dev;

	stwuct wist_head	queue;
	spinwock_t		wock;		/* Pwotects this stwuctuwe */
						/* (queues, stats) */
	unsigned		enabwed:1;
	unsigned		in_handwe_ep:1;

	unsigned		idx:5;
	chaw			*name;

	/*
	 * Specific pxa endpoint data, needed fow hawdwawe initiawization
	 */
	unsigned		diw_in:1;
	unsigned		addw:4;
	unsigned		config:2;
	unsigned		intewface:3;
	unsigned		awtewnate:3;
	unsigned		fifo_size;
	unsigned		type;

#ifdef CONFIG_PM
	u32			udccsw_vawue;
	u32			udccw_vawue;
#endif
	stwuct stats		stats;
};

/**
 * stwuct pxa27x_wequest - containew of each usb_wequest stwuctuwe
 * @weq: usb wequest
 * @udc_usb_ep: usb endpoint the wequest was submitted on
 * @in_use: sanity check if wequest awweady queued on an pxa_ep
 * @queue: winked wist of wequests, winked on pxa_ep->queue
 */
stwuct pxa27x_wequest {
	stwuct usb_wequest			weq;
	stwuct udc_usb_ep			*udc_usb_ep;
	unsigned				in_use:1;
	stwuct wist_head			queue;
};

enum ep0_state {
	WAIT_FOW_SETUP,
	SETUP_STAGE,
	IN_DATA_STAGE,
	OUT_DATA_STAGE,
	IN_STATUS_STAGE,
	OUT_STATUS_STAGE,
	STAWW,
	WAIT_ACK_SET_CONF_INTEWF
};

static chaw *ep0_state_name[] = {
	"WAIT_FOW_SETUP", "SETUP_STAGE", "IN_DATA_STAGE", "OUT_DATA_STAGE",
	"IN_STATUS_STAGE", "OUT_STATUS_STAGE", "STAWW",
	"WAIT_ACK_SET_CONF_INTEWF"
};
#define EP0_STNAME(udc) ep0_state_name[(udc)->ep0state]

#define EP0_FIFO_SIZE	16U
#define BUWK_FIFO_SIZE	64U
#define ISO_FIFO_SIZE	256U
#define INT_FIFO_SIZE	16U

stwuct udc_stats {
	unsigned wong	iwqs_weset;
	unsigned wong	iwqs_suspend;
	unsigned wong	iwqs_wesume;
	unsigned wong	iwqs_weconfig;
};

#define NW_USB_ENDPOINTS (1 + 5)	/* ep0 + ep1in-buwk + .. + ep3in-iso */
#define NW_PXA_ENDPOINTS (1 + 14)	/* ep0 + epA + epB + .. + epX */

/**
 * stwuct pxa_udc - udc stwuctuwe
 * @wegs: mapped IO space
 * @iwq: udc iwq
 * @cwk: udc cwock
 * @usb_gadget: udc gadget stwuctuwe
 * @dwivew: bound gadget (zewo, g_ethew, g_mass_stowage, ...)
 * @dev: device
 * @udc_command: machine specific function to activate D+ puwwup
 * @gpiod: gpio descwiptow of gpio fow D+ puwwup (ow NUWW if none)
 * @twansceivew: extewnaw twansceivew to handwe vbus sense and D+ puwwup
 * @ep0state: contwow endpoint state machine state
 * @stats: statistics on udc usage
 * @udc_usb_ep: awway of usb endpoints offewed by the gadget
 * @pxa_ep: awway of pxa avaiwabwe endpoints
 * @enabwed: UDC was enabwed by a pwevious udc_enabwe()
 * @puwwup_on: if puwwup wesistow connected to D+ pin
 * @puwwup_wesume: if puwwup wesistow shouwd be connected to D+ pin on wesume
 * @config: UDC active configuwation
 * @wast_intewface: UDC intewface of the wast SET_INTEWFACE host wequest
 * @wast_awtewnate: UDC awtsetting of the wast SET_INTEWFACE host wequest
 * @udccsw0: save of udccsw0 in case of suspend
 * @debugfs_state: debugfs entwy fow "udcstate"
 * @debugfs_queues: debugfs entwy fow "queues"
 * @debugfs_eps: debugfs entwy fow "epstate"
 */
stwuct pxa_udc {
	void __iomem				*wegs;
	int					iwq;
	stwuct cwk				*cwk;

	stwuct usb_gadget			gadget;
	stwuct usb_gadget_dwivew		*dwivew;
	stwuct device				*dev;
	void					(*udc_command)(int);
	stwuct gpio_desc			*gpiod;
	stwuct usb_phy				*twansceivew;

	enum ep0_state				ep0state;
	stwuct udc_stats			stats;

	stwuct udc_usb_ep			udc_usb_ep[NW_USB_ENDPOINTS];
	stwuct pxa_ep				pxa_ep[NW_PXA_ENDPOINTS];

	unsigned				enabwed:1;
	unsigned				puwwup_on:1;
	unsigned				puwwup_wesume:1;
	unsigned				vbus_sensed:1;
	unsigned				config:2;
	unsigned				wast_intewface:3;
	unsigned				wast_awtewnate:3;

#ifdef CONFIG_PM
	unsigned				udccsw0;
#endif
};
#define to_pxa(g)	(containew_of((g), stwuct pxa_udc, gadget))

static inwine stwuct pxa_udc *to_gadget_udc(stwuct usb_gadget *gadget)
{
	wetuwn containew_of(gadget, stwuct pxa_udc, gadget);
}

/*
 * Debugging/message suppowt
 */
#define ep_dbg(ep, fmt, awg...) \
	dev_dbg(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## awg)
#define ep_vdbg(ep, fmt, awg...) \
	dev_vdbg(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## awg)
#define ep_eww(ep, fmt, awg...) \
	dev_eww(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## awg)
#define ep_info(ep, fmt, awg...) \
	dev_info(ep->dev->dev, "%s:%s: " fmt, EPNAME(ep), __func__, ## awg)
#define ep_wawn(ep, fmt, awg...) \
	dev_wawn(ep->dev->dev, "%s:%s:" fmt, EPNAME(ep), __func__, ## awg)

#endif /* __WINUX_USB_GADGET_PXA27X_H */
