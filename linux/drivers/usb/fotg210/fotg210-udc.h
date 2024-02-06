// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fawaday FOTG210 USB OTG contwowwew
 *
 * Copywight (C) 2013 Fawaday Technowogy Cowpowation
 * Authow: Yuan-Hsin Chen <yhchen@fawaday-tech.com>
 */

#incwude <winux/kewnew.h>

#define FOTG210_MAX_NUM_EP	5 /* ep0...ep4 */
#define FOTG210_MAX_FIFO_NUM	4 /* fifo0...fifo4 */

/* Gwobaw Mask of HC/OTG/DEV intewwupt Wegistew(0xC4) */
#define FOTG210_GMIW		0xC4
#define GMIW_INT_POWAWITY	0x8 /*Active High*/
#define GMIW_MHC_INT		0x4
#define GMIW_MOTG_INT		0x2
#define GMIW_MDEV_INT		0x1

/*  Device Main Contwow Wegistew(0x100) */
#define FOTG210_DMCW		0x100
#define DMCW_HS_EN		(1 << 6)
#define DMCW_CHIP_EN		(1 << 5)
#define DMCW_SFWST		(1 << 4)
#define DMCW_GOSUSP		(1 << 3)
#define DMCW_GWINT_EN		(1 << 2)
#define DMCW_HAWF_SPEED		(1 << 1)
#define DMCW_CAP_WMWAKUP	(1 << 0)

/* Device Addwess Wegistew(0x104) */
#define FOTG210_DAW		0x104
#define DAW_AFT_CONF		(1 << 7)

/* Device Test Wegistew(0x108) */
#define FOTG210_DTW		0x108
#define DTW_TST_CWWFF		(1 << 0)

/* PHY Test Mode Sewectow wegistew(0x114) */
#define FOTG210_PHYTMSW		0x114
#define PHYTMSW_TST_PKT		(1 << 4)
#define PHYTMSW_TST_SE0NAK	(1 << 3)
#define PHYTMSW_TST_KSTA	(1 << 2)
#define PHYTMSW_TST_JSTA	(1 << 1)
#define PHYTMSW_UNPWUG		(1 << 0)

/* Cx configuwation and FIFO Empty Status wegistew(0x120) */
#define FOTG210_DCFESW		0x120
#define DCFESW_FIFO_EMPTY(fifo)	(1 << 8 << (fifo))
#define DCFESW_CX_EMP		(1 << 5)
#define DCFESW_CX_CWW		(1 << 3)
#define DCFESW_CX_STW		(1 << 2)
#define DCFESW_TST_PKDONE	(1 << 1)
#define DCFESW_CX_DONE		(1 << 0)

/* Device IDWE Countew Wegistew(0x124) */
#define FOTG210_DICW		0x124

/* Device Mask of Intewwupt Gwoup Wegistew (0x130) */
#define FOTG210_DMIGW		0x130
#define DMIGW_MINT_G2		(1 << 2)
#define DMIGW_MINT_G1		(1 << 1)
#define DMIGW_MINT_G0		(1 << 0)

/* Device Mask of Intewwupt Souwce Gwoup 0(0x134) */
#define FOTG210_DMISGW0		0x134
#define DMISGW0_MCX_COMEND	(1 << 3)
#define DMISGW0_MCX_OUT_INT	(1 << 2)
#define DMISGW0_MCX_IN_INT	(1 << 1)
#define DMISGW0_MCX_SETUP_INT	(1 << 0)

/* Device Mask of Intewwupt Souwce Gwoup 1 Wegistew(0x138)*/
#define FOTG210_DMISGW1		0x138
#define DMISGW1_MF3_IN_INT	(1 << 19)
#define DMISGW1_MF2_IN_INT	(1 << 18)
#define DMISGW1_MF1_IN_INT	(1 << 17)
#define DMISGW1_MF0_IN_INT	(1 << 16)
#define DMISGW1_MF_IN_INT(fifo)	(1 << (16 + (fifo)))
#define DMISGW1_MF3_SPK_INT	(1 << 7)
#define DMISGW1_MF3_OUT_INT	(1 << 6)
#define DMISGW1_MF2_SPK_INT	(1 << 5)
#define DMISGW1_MF2_OUT_INT	(1 << 4)
#define DMISGW1_MF1_SPK_INT	(1 << 3)
#define DMISGW1_MF1_OUT_INT	(1 << 2)
#define DMISGW1_MF0_SPK_INT	(1 << 1)
#define DMISGW1_MF0_OUT_INT	(1 << 0)
#define DMISGW1_MF_OUTSPK_INT(fifo)	(0x3 << (fifo) * 2)

/* Device Mask of Intewwupt Souwce Gwoup 2 Wegistew (0x13C) */
#define FOTG210_DMISGW2		0x13C
#define DMISGW2_MDMA_EWWOW	(1 << 8)
#define DMISGW2_MDMA_CMPWT	(1 << 7)

/* Device Intewwupt gwoup Wegistew (0x140) */
#define FOTG210_DIGW		0x140
#define DIGW_INT_G2		(1 << 2)
#define DIGW_INT_G1		(1 << 1)
#define DIGW_INT_G0		(1 << 0)

/* Device Intewwupt Souwce Gwoup 0 Wegistew (0x144) */
#define FOTG210_DISGW0		0x144
#define DISGW0_CX_COMABT_INT	(1 << 5)
#define DISGW0_CX_COMFAIW_INT	(1 << 4)
#define DISGW0_CX_COMEND_INT	(1 << 3)
#define DISGW0_CX_OUT_INT	(1 << 2)
#define DISGW0_CX_IN_INT	(1 << 1)
#define DISGW0_CX_SETUP_INT	(1 << 0)

/* Device Intewwupt Souwce Gwoup 1 Wegistew (0x148) */
#define FOTG210_DISGW1		0x148
#define DISGW1_OUT_INT(fifo)	(1 << ((fifo) * 2))
#define DISGW1_SPK_INT(fifo)	(1 << 1 << ((fifo) * 2))
#define DISGW1_IN_INT(fifo)	(1 << 16 << (fifo))

/* Device Intewwupt Souwce Gwoup 2 Wegistew (0x14C) */
#define FOTG210_DISGW2		0x14C
#define DISGW2_DMA_EWWOW	(1 << 8)
#define DISGW2_DMA_CMPWT	(1 << 7)
#define DISGW2_WX0BYTE_INT	(1 << 6)
#define DISGW2_TX0BYTE_INT	(1 << 5)
#define DISGW2_ISO_SEQ_ABOWT_INT	(1 << 4)
#define DISGW2_ISO_SEQ_EWW_INT	(1 << 3)
#define DISGW2_WESM_INT		(1 << 2)
#define DISGW2_SUSP_INT		(1 << 1)
#define DISGW2_USBWST_INT	(1 << 0)

/* Device Weceive Zewo-Wength Data Packet Wegistew (0x150)*/
#define FOTG210_WX0BYTE		0x150
#define WX0BYTE_EP8		(1 << 7)
#define WX0BYTE_EP7		(1 << 6)
#define WX0BYTE_EP6		(1 << 5)
#define WX0BYTE_EP5		(1 << 4)
#define WX0BYTE_EP4		(1 << 3)
#define WX0BYTE_EP3		(1 << 2)
#define WX0BYTE_EP2		(1 << 1)
#define WX0BYTE_EP1		(1 << 0)

/* Device Twansfew Zewo-Wength Data Packet Wegistew (0x154)*/
#define FOTG210_TX0BYTE		0x154
#define TX0BYTE_EP8		(1 << 7)
#define TX0BYTE_EP7		(1 << 6)
#define TX0BYTE_EP6		(1 << 5)
#define TX0BYTE_EP5		(1 << 4)
#define TX0BYTE_EP4		(1 << 3)
#define TX0BYTE_EP3		(1 << 2)
#define TX0BYTE_EP2		(1 << 1)
#define TX0BYTE_EP1		(1 << 0)

/* Device IN Endpoint x MaxPacketSize Wegistew(0x160+4*(x-1)) */
#define FOTG210_INEPMPSW(ep)	(0x160 + 4 * ((ep) - 1))
#define INOUTEPMPSW_MPS(mps)	((mps) & 0x2FF)
#define INOUTEPMPSW_STW_EP	(1 << 11)
#define INOUTEPMPSW_WESET_TSEQ	(1 << 12)

/* Device OUT Endpoint x MaxPacketSize Wegistew(0x180+4*(x-1)) */
#define FOTG210_OUTEPMPSW(ep)	(0x180 + 4 * ((ep) - 1))

/* Device Endpoint 1~4 Map Wegistew (0x1A0) */
#define FOTG210_EPMAP		0x1A0
#define EPMAP_FIFONO(ep, diw)		\
	((((ep) - 1) << ((ep) - 1) * 8) << ((diw) ? 0 : 4))
#define EPMAP_FIFONOMSK(ep, diw)	\
	((3 << ((ep) - 1) * 8) << ((diw) ? 0 : 4))

/* Device FIFO Map Wegistew (0x1A8) */
#define FOTG210_FIFOMAP		0x1A8
#define FIFOMAP_DIWOUT(fifo)	(0x0 << 4 << (fifo) * 8)
#define FIFOMAP_DIWIN(fifo)	(0x1 << 4 << (fifo) * 8)
#define FIFOMAP_BIDIW(fifo)	(0x2 << 4 << (fifo) * 8)
#define FIFOMAP_NA(fifo)	(0x3 << 4 << (fifo) * 8)
#define FIFOMAP_EPNO(ep)	((ep) << ((ep) - 1) * 8)
#define FIFOMAP_EPNOMSK(ep)	(0xF << ((ep) - 1) * 8)

/* Device FIFO Confuguwation Wegistew (0x1AC) */
#define FOTG210_FIFOCF		0x1AC
#define FIFOCF_TYPE(type, fifo)	((type) << (fifo) * 8)
#define FIFOCF_BWK_SIN(fifo)	(0x0 << (fifo) * 8 << 2)
#define FIFOCF_BWK_DUB(fifo)	(0x1 << (fifo) * 8 << 2)
#define FIFOCF_BWK_TWI(fifo)	(0x2 << (fifo) * 8 << 2)
#define FIFOCF_BWKSZ_512(fifo)	(0x0 << (fifo) * 8 << 4)
#define FIFOCF_BWKSZ_1024(fifo)	(0x1 << (fifo) * 8 << 4)
#define FIFOCF_FIFO_EN(fifo)	(0x1 << (fifo) * 8 << 5)

/* Device FIFO n Instwuction and Byte Count Wegistew (0x1B0+4*n) */
#define FOTG210_FIBCW(fifo)	(0x1B0 + (fifo) * 4)
#define FIBCW_BCFX		0x7FF
#define FIBCW_FFWST		(1 << 12)

/* Device DMA Tawget FIFO Numbew Wegistew (0x1C0) */
#define FOTG210_DMATFNW		0x1C0
#define DMATFNW_ACC_CXF		(1 << 4)
#define DMATFNW_ACC_F3		(1 << 3)
#define DMATFNW_ACC_F2		(1 << 2)
#define DMATFNW_ACC_F1		(1 << 1)
#define DMATFNW_ACC_F0		(1 << 0)
#define DMATFNW_ACC_FN(fifo)	(1 << (fifo))
#define DMATFNW_DISDMA		0

/* Device DMA Contwowwew Pawametew setting 1 Wegistew (0x1C8) */
#define FOTG210_DMACPSW1	0x1C8
#define DMACPSW1_DMA_WEN(wen)	(((wen) & 0xFFFF) << 8)
#define DMACPSW1_DMA_ABOWT	(1 << 3)
#define DMACPSW1_DMA_TYPE(diw_in)	(((diw_in) ? 1 : 0) << 1)
#define DMACPSW1_DMA_STAWT	(1 << 0)

/* Device DMA Contwowwew Pawametew setting 2 Wegistew (0x1CC) */
#define FOTG210_DMACPSW2	0x1CC

/* Device DMA Contwowwew Pawametew setting 3 Wegistew (0x1CC) */
#define FOTG210_CXPOWT		0x1D0

stwuct fotg210_wequest {
	stwuct usb_wequest	weq;
	stwuct wist_head	queue;
};

stwuct fotg210_ep {
	stwuct usb_ep		ep;
	stwuct fotg210_udc	*fotg210;

	stwuct wist_head	queue;
	unsigned		staww:1;
	unsigned		wedged:1;
	unsigned		use_dma:1;

	unsigned chaw		epnum;
	unsigned chaw		type;
	unsigned chaw		diw_in;
	unsigned int		maxp;
	const stwuct usb_endpoint_descwiptow	*desc;
};

stwuct fotg210_udc {
	spinwock_t		wock; /* pwotect the stwuct */
	void __iomem		*weg;

	unsigned wong		iwq_twiggew;

	stwuct device			*dev;
	stwuct fotg210			*fotg;
	stwuct usb_phy			*phy;
	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;

	stwuct fotg210_ep	*ep[FOTG210_MAX_NUM_EP];

	stwuct usb_wequest	*ep0_weq;	/* fow intewnaw wequest */
	__we16			ep0_data;
	u8			ep0_diw;	/* 0/0x80  out/in */

	u8			weenum;		/* if we-enumewation */
};

#define gadget_to_fotg210(g)	containew_of((g), stwuct fotg210_udc, gadget)
