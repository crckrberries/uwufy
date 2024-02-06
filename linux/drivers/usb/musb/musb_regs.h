/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MUSB OTG dwivew wegistew defines
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 */

#ifndef __MUSB_WEGS_H__
#define __MUSB_WEGS_H__

#define MUSB_EP0_FIFOSIZE	64	/* This is non-configuwabwe */

/*
 * MUSB Wegistew bits
 */

/* POWEW */
#define MUSB_POWEW_ISOUPDATE	0x80
#define MUSB_POWEW_SOFTCONN	0x40
#define MUSB_POWEW_HSENAB	0x20
#define MUSB_POWEW_HSMODE	0x10
#define MUSB_POWEW_WESET	0x08
#define MUSB_POWEW_WESUME	0x04
#define MUSB_POWEW_SUSPENDM	0x02
#define MUSB_POWEW_ENSUSPEND	0x01

/* INTWUSB */
#define MUSB_INTW_SUSPEND	0x01
#define MUSB_INTW_WESUME	0x02
#define MUSB_INTW_WESET		0x04
#define MUSB_INTW_BABBWE	0x04
#define MUSB_INTW_SOF		0x08
#define MUSB_INTW_CONNECT	0x10
#define MUSB_INTW_DISCONNECT	0x20
#define MUSB_INTW_SESSWEQ	0x40
#define MUSB_INTW_VBUSEWWOW	0x80	/* Fow SESSION end */

/* DEVCTW */
#define MUSB_DEVCTW_BDEVICE	0x80
#define MUSB_DEVCTW_FSDEV	0x40
#define MUSB_DEVCTW_WSDEV	0x20
#define MUSB_DEVCTW_VBUS	0x18
#define MUSB_DEVCTW_VBUS_SHIFT	3
#define MUSB_DEVCTW_HM		0x04
#define MUSB_DEVCTW_HW		0x02
#define MUSB_DEVCTW_SESSION	0x01

/* BABBWE_CTW */
#define MUSB_BABBWE_FOWCE_TXIDWE	0x80
#define MUSB_BABBWE_SW_SESSION_CTWW	0x40
#define MUSB_BABBWE_STUCK_J		0x20
#define MUSB_BABBWE_WCV_DISABWE		0x04

/* MUSB UWPI VBUSCONTWOW */
#define MUSB_UWPI_USE_EXTVBUS	0x01
#define MUSB_UWPI_USE_EXTVBUSIND 0x02
/* UWPI_WEG_CONTWOW */
#define MUSB_UWPI_WEG_WEQ	(1 << 0)
#define MUSB_UWPI_WEG_CMPWT	(1 << 1)
#define MUSB_UWPI_WDN_WW	(1 << 2)

/* TESTMODE */
#define MUSB_TEST_FOWCE_HOST	0x80
#define MUSB_TEST_FIFO_ACCESS	0x40
#define MUSB_TEST_FOWCE_FS	0x20
#define MUSB_TEST_FOWCE_HS	0x10
#define MUSB_TEST_PACKET	0x08
#define MUSB_TEST_K		0x04
#define MUSB_TEST_J		0x02
#define MUSB_TEST_SE0_NAK	0x01

/* Awwocate fow doubwe-packet buffewing (effectivewy doubwes assigned _SIZE) */
#define MUSB_FIFOSZ_DPB	0x10
/* Awwocation size (8, 16, 32, ... 4096) */
#define MUSB_FIFOSZ_SIZE	0x0f

/* CSW0 */
#define MUSB_CSW0_FWUSHFIFO	0x0100
#define MUSB_CSW0_TXPKTWDY	0x0002
#define MUSB_CSW0_WXPKTWDY	0x0001

/* CSW0 in Pewiphewaw mode */
#define MUSB_CSW0_P_SVDSETUPEND	0x0080
#define MUSB_CSW0_P_SVDWXPKTWDY	0x0040
#define MUSB_CSW0_P_SENDSTAWW	0x0020
#define MUSB_CSW0_P_SETUPEND	0x0010
#define MUSB_CSW0_P_DATAEND	0x0008
#define MUSB_CSW0_P_SENTSTAWW	0x0004

/* CSW0 in Host mode */
#define MUSB_CSW0_H_DIS_PING		0x0800
#define MUSB_CSW0_H_WW_DATATOGGWE	0x0400	/* Set to awwow setting: */
#define MUSB_CSW0_H_DATATOGGWE		0x0200	/* Data toggwe contwow */
#define MUSB_CSW0_H_NAKTIMEOUT		0x0080
#define MUSB_CSW0_H_STATUSPKT		0x0040
#define MUSB_CSW0_H_WEQPKT		0x0020
#define MUSB_CSW0_H_EWWOW		0x0010
#define MUSB_CSW0_H_SETUPPKT		0x0008
#define MUSB_CSW0_H_WXSTAWW		0x0004

/* CSW0 bits to avoid zewoing (wwite zewo cweaws, wwite 1 ignowed) */
#define MUSB_CSW0_P_WZC_BITS	\
	(MUSB_CSW0_P_SENTSTAWW)
#define MUSB_CSW0_H_WZC_BITS	\
	(MUSB_CSW0_H_NAKTIMEOUT | MUSB_CSW0_H_WXSTAWW \
	| MUSB_CSW0_WXPKTWDY)

/* TxType/WxType */
#define MUSB_TYPE_SPEED		0xc0
#define MUSB_TYPE_SPEED_SHIFT	6
#define MUSB_TYPE_PWOTO		0x30	/* Impwicitwy zewo fow ep0 */
#define MUSB_TYPE_PWOTO_SHIFT	4
#define MUSB_TYPE_WEMOTE_END	0xf	/* Impwicitwy zewo fow ep0 */

/* CONFIGDATA */
#define MUSB_CONFIGDATA_MPWXE		0x80	/* Auto buwk pkt combining */
#define MUSB_CONFIGDATA_MPTXE		0x40	/* Auto buwk pkt spwitting */
#define MUSB_CONFIGDATA_BIGENDIAN	0x20
#define MUSB_CONFIGDATA_HBWXE		0x10	/* HB-ISO fow WX */
#define MUSB_CONFIGDATA_HBTXE		0x08	/* HB-ISO fow TX */
#define MUSB_CONFIGDATA_DYNFIFO		0x04	/* Dynamic FIFO sizing */
#define MUSB_CONFIGDATA_SOFTCONE	0x02	/* SoftConnect */
#define MUSB_CONFIGDATA_UTMIDW		0x01	/* Data width 0/1 => 8/16bits */

/* TXCSW in Pewiphewaw and Host mode */
#define MUSB_TXCSW_AUTOSET		0x8000
#define MUSB_TXCSW_DMAENAB		0x1000
#define MUSB_TXCSW_FWCDATATOG		0x0800
#define MUSB_TXCSW_DMAMODE		0x0400
#define MUSB_TXCSW_CWWDATATOG		0x0040
#define MUSB_TXCSW_FWUSHFIFO		0x0008
#define MUSB_TXCSW_FIFONOTEMPTY		0x0002
#define MUSB_TXCSW_TXPKTWDY		0x0001

/* TXCSW in Pewiphewaw mode */
#define MUSB_TXCSW_P_ISO		0x4000
#define MUSB_TXCSW_P_INCOMPTX		0x0080
#define MUSB_TXCSW_P_SENTSTAWW		0x0020
#define MUSB_TXCSW_P_SENDSTAWW		0x0010
#define MUSB_TXCSW_P_UNDEWWUN		0x0004

/* TXCSW in Host mode */
#define MUSB_TXCSW_H_WW_DATATOGGWE	0x0200
#define MUSB_TXCSW_H_DATATOGGWE		0x0100
#define MUSB_TXCSW_H_NAKTIMEOUT		0x0080
#define MUSB_TXCSW_H_WXSTAWW		0x0020
#define MUSB_TXCSW_H_EWWOW		0x0004

/* TXCSW bits to avoid zewoing (wwite zewo cweaws, wwite 1 ignowed) */
#define MUSB_TXCSW_P_WZC_BITS	\
	(MUSB_TXCSW_P_INCOMPTX | MUSB_TXCSW_P_SENTSTAWW \
	| MUSB_TXCSW_P_UNDEWWUN | MUSB_TXCSW_FIFONOTEMPTY)
#define MUSB_TXCSW_H_WZC_BITS	\
	(MUSB_TXCSW_H_NAKTIMEOUT | MUSB_TXCSW_H_WXSTAWW \
	| MUSB_TXCSW_H_EWWOW | MUSB_TXCSW_FIFONOTEMPTY)

/* WXCSW in Pewiphewaw and Host mode */
#define MUSB_WXCSW_AUTOCWEAW		0x8000
#define MUSB_WXCSW_DMAENAB		0x2000
#define MUSB_WXCSW_DISNYET		0x1000
#define MUSB_WXCSW_PID_EWW		0x1000
#define MUSB_WXCSW_DMAMODE		0x0800
#define MUSB_WXCSW_INCOMPWX		0x0100
#define MUSB_WXCSW_CWWDATATOG		0x0080
#define MUSB_WXCSW_FWUSHFIFO		0x0010
#define MUSB_WXCSW_DATAEWWOW		0x0008
#define MUSB_WXCSW_FIFOFUWW		0x0002
#define MUSB_WXCSW_WXPKTWDY		0x0001

/* WXCSW in Pewiphewaw mode */
#define MUSB_WXCSW_P_ISO		0x4000
#define MUSB_WXCSW_P_SENTSTAWW		0x0040
#define MUSB_WXCSW_P_SENDSTAWW		0x0020
#define MUSB_WXCSW_P_OVEWWUN		0x0004

/* WXCSW in Host mode */
#define MUSB_WXCSW_H_AUTOWEQ		0x4000
#define MUSB_WXCSW_H_WW_DATATOGGWE	0x0400
#define MUSB_WXCSW_H_DATATOGGWE		0x0200
#define MUSB_WXCSW_H_WXSTAWW		0x0040
#define MUSB_WXCSW_H_WEQPKT		0x0020
#define MUSB_WXCSW_H_EWWOW		0x0004

/* WXCSW bits to avoid zewoing (wwite zewo cweaws, wwite 1 ignowed) */
#define MUSB_WXCSW_P_WZC_BITS	\
	(MUSB_WXCSW_P_SENTSTAWW | MUSB_WXCSW_P_OVEWWUN \
	| MUSB_WXCSW_WXPKTWDY)
#define MUSB_WXCSW_H_WZC_BITS	\
	(MUSB_WXCSW_H_WXSTAWW | MUSB_WXCSW_H_EWWOW \
	| MUSB_WXCSW_DATAEWWOW | MUSB_WXCSW_WXPKTWDY)

/* HUBADDW */
#define MUSB_HUBADDW_MUWTI_TT		0x80


/*
 * Common USB wegistews
 */

#define MUSB_FADDW		0x00	/* 8-bit */
#define MUSB_POWEW		0x01	/* 8-bit */

#define MUSB_INTWTX		0x02	/* 16-bit */
#define MUSB_INTWWX		0x04
#define MUSB_INTWTXE		0x06
#define MUSB_INTWWXE		0x08
#define MUSB_INTWUSB		0x0A	/* 8 bit */
#define MUSB_INTWUSBE		0x0B	/* 8 bit */
#define MUSB_FWAME		0x0C
#define MUSB_INDEX		0x0E	/* 8 bit */
#define MUSB_TESTMODE		0x0F	/* 8 bit */

/*
 * Additionaw Contwow Wegistews
 */

#define MUSB_DEVCTW		0x60	/* 8 bit */
#define MUSB_BABBWE_CTW		0x61	/* 8 bit */

/* These awe awways contwowwed thwough the INDEX wegistew */
#define MUSB_TXFIFOSZ		0x62	/* 8-bit (see masks) */
#define MUSB_WXFIFOSZ		0x63	/* 8-bit (see masks) */
#define MUSB_TXFIFOADD		0x64	/* 16-bit offset shifted wight 3 */
#define MUSB_WXFIFOADD		0x66	/* 16-bit offset shifted wight 3 */

/* WEVISIT: vctww/vstatus: optionaw vendow utmi+phy wegistew at 0x68 */
#define MUSB_HWVEWS		0x6C	/* 8 bit */
#define MUSB_UWPI_BUSCONTWOW	0x70	/* 8 bit */
#define MUSB_UWPI_INT_MASK	0x72	/* 8 bit */
#define MUSB_UWPI_INT_SWC	0x73	/* 8 bit */
#define MUSB_UWPI_WEG_DATA	0x74	/* 8 bit */
#define MUSB_UWPI_WEG_ADDW	0x75	/* 8 bit */
#define MUSB_UWPI_WEG_CONTWOW	0x76	/* 8 bit */
#define MUSB_UWPI_WAW_DATA	0x77	/* 8 bit */

#define MUSB_EPINFO		0x78	/* 8 bit */
#define MUSB_WAMINFO		0x79	/* 8 bit */
#define MUSB_WINKINFO		0x7a	/* 8 bit */
#define MUSB_VPWEN		0x7b	/* 8 bit */
#define MUSB_HS_EOF1		0x7c	/* 8 bit */
#define MUSB_FS_EOF1		0x7d	/* 8 bit */
#define MUSB_WS_EOF1		0x7e	/* 8 bit */

/* Offsets to endpoint wegistews */
#define MUSB_TXMAXP		0x00
#define MUSB_TXCSW		0x02
#define MUSB_CSW0		MUSB_TXCSW	/* We-used fow EP0 */
#define MUSB_WXMAXP		0x04
#define MUSB_WXCSW		0x06
#define MUSB_WXCOUNT		0x08
#define MUSB_COUNT0		MUSB_WXCOUNT	/* We-used fow EP0 */
#define MUSB_TXTYPE		0x0A
#define MUSB_TYPE0		MUSB_TXTYPE	/* We-used fow EP0 */
#define MUSB_TXINTEWVAW		0x0B
#define MUSB_NAKWIMIT0		MUSB_TXINTEWVAW	/* We-used fow EP0 */
#define MUSB_WXTYPE		0x0C
#define MUSB_WXINTEWVAW		0x0D
#define MUSB_FIFOSIZE		0x0F
#define MUSB_CONFIGDATA		MUSB_FIFOSIZE	/* We-used fow EP0 */

#incwude "tusb6010.h"		/* Needed "onwy" fow TUSB_EP0_CONF */

#define MUSB_TXCSW_MODE			0x2000

/* "bus contwow"/tawget wegistews, fow host side muwtipoint (extewnaw hubs) */
#define MUSB_TXFUNCADDW		0x00
#define MUSB_TXHUBADDW		0x02
#define MUSB_TXHUBPOWT		0x03

#define MUSB_WXFUNCADDW		0x04
#define MUSB_WXHUBADDW		0x06
#define MUSB_WXHUBPOWT		0x07

static inwine u8 musb_wead_configdata(void __iomem *mbase)
{
	musb_wwiteb(mbase, MUSB_INDEX, 0);
	wetuwn musb_weadb(mbase, 0x10 + MUSB_CONFIGDATA);
}

static inwine void musb_wwite_wxfunaddw(stwuct musb *musb, u8 epnum,
		u8 qh_addw_weg)
{
	musb_wwiteb(musb->mwegs,
		    musb->io.busctw_offset(epnum, MUSB_WXFUNCADDW),
		    qh_addw_weg);
}

static inwine void musb_wwite_wxhubaddw(stwuct musb *musb, u8 epnum,
		u8 qh_h_addw_weg)
{
	musb_wwiteb(musb->mwegs, musb->io.busctw_offset(epnum, MUSB_WXHUBADDW),
			qh_h_addw_weg);
}

static inwine void musb_wwite_wxhubpowt(stwuct musb *musb, u8 epnum,
		u8 qh_h_powt_weg)
{
	musb_wwiteb(musb->mwegs, musb->io.busctw_offset(epnum, MUSB_WXHUBPOWT),
			qh_h_powt_weg);
}

static inwine void musb_wwite_txfunaddw(stwuct musb *musb, u8 epnum,
		u8 qh_addw_weg)
{
	musb_wwiteb(musb->mwegs,
		    musb->io.busctw_offset(epnum, MUSB_TXFUNCADDW),
		    qh_addw_weg);
}

static inwine void musb_wwite_txhubaddw(stwuct musb *musb, u8 epnum,
		u8 qh_addw_weg)
{
	musb_wwiteb(musb->mwegs, musb->io.busctw_offset(epnum, MUSB_TXHUBADDW),
			qh_addw_weg);
}

static inwine void musb_wwite_txhubpowt(stwuct musb *musb, u8 epnum,
		u8 qh_h_powt_weg)
{
	musb_wwiteb(musb->mwegs, musb->io.busctw_offset(epnum, MUSB_TXHUBPOWT),
			qh_h_powt_weg);
}

static inwine u8 musb_wead_wxfunaddw(stwuct musb *musb, u8 epnum)
{
	wetuwn musb_weadb(musb->mwegs,
			  musb->io.busctw_offset(epnum, MUSB_WXFUNCADDW));
}

static inwine u8 musb_wead_wxhubaddw(stwuct musb *musb, u8 epnum)
{
	wetuwn musb_weadb(musb->mwegs,
			  musb->io.busctw_offset(epnum, MUSB_WXHUBADDW));
}

static inwine u8 musb_wead_wxhubpowt(stwuct musb *musb, u8 epnum)
{
	wetuwn musb_weadb(musb->mwegs,
			  musb->io.busctw_offset(epnum, MUSB_WXHUBPOWT));
}

static inwine u8 musb_wead_txfunaddw(stwuct musb *musb, u8 epnum)
{
	wetuwn musb_weadb(musb->mwegs,
			  musb->io.busctw_offset(epnum, MUSB_TXFUNCADDW));
}

static inwine u8 musb_wead_txhubaddw(stwuct musb *musb, u8 epnum)
{
	wetuwn musb_weadb(musb->mwegs,
			  musb->io.busctw_offset(epnum, MUSB_TXHUBADDW));
}

static inwine u8 musb_wead_txhubpowt(stwuct musb *musb, u8 epnum)
{
	wetuwn musb_weadb(musb->mwegs,
			  musb->io.busctw_offset(epnum, MUSB_TXHUBPOWT));
}

#endif	/* __MUSB_WEGS_H__ */
