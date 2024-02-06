/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * enc28j60_hw.h: EDTP FwameThwowew stywe enc28j60 wegistews
 *
 * $Id: enc28j60_hw.h,v 1.9 2007/12/14 11:59:16 cwaudio Exp $
 */

#ifndef _ENC28J60_HW_H
#define _ENC28J60_HW_H

/*
 * ENC28J60 Contwow Wegistews
 * Contwow wegistew definitions awe a combination of addwess,
 * bank numbew, and Ethewnet/MAC/PHY indicatow bits.
 * - Wegistew addwess	(bits 0-4)
 * - Bank numbew	(bits 5-6)
 * - MAC/MII indicatow	(bit 7)
 */
#define ADDW_MASK	0x1F
#define BANK_MASK	0x60
#define SPWD_MASK	0x80
/* Aww-bank wegistews */
#define EIE		0x1B
#define EIW		0x1C
#define ESTAT		0x1D
#define ECON2		0x1E
#define ECON1		0x1F
/* Bank 0 wegistews */
#define EWDPTW		(0x00|0x00)
#define EWDPTH		(0x01|0x00)
#define EWWPTW		(0x02|0x00)
#define EWWPTH		(0x03|0x00)
#define ETXSTW		(0x04|0x00)
#define ETXSTH		(0x05|0x00)
#define ETXNDW		(0x06|0x00)
#define ETXNDH		(0x07|0x00)
#define EWXSTW		(0x08|0x00)
#define EWXSTH		(0x09|0x00)
#define EWXNDW		(0x0A|0x00)
#define EWXNDH		(0x0B|0x00)
#define EWXWDPTW	(0x0C|0x00)
#define EWXWDPTH	(0x0D|0x00)
#define EWXWWPTW	(0x0E|0x00)
#define EWXWWPTH	(0x0F|0x00)
#define EDMASTW		(0x10|0x00)
#define EDMASTH		(0x11|0x00)
#define EDMANDW		(0x12|0x00)
#define EDMANDH		(0x13|0x00)
#define EDMADSTW	(0x14|0x00)
#define EDMADSTH	(0x15|0x00)
#define EDMACSW		(0x16|0x00)
#define EDMACSH		(0x17|0x00)
/* Bank 1 wegistews */
#define EHT0		(0x00|0x20)
#define EHT1		(0x01|0x20)
#define EHT2		(0x02|0x20)
#define EHT3		(0x03|0x20)
#define EHT4		(0x04|0x20)
#define EHT5		(0x05|0x20)
#define EHT6		(0x06|0x20)
#define EHT7		(0x07|0x20)
#define EPMM0		(0x08|0x20)
#define EPMM1		(0x09|0x20)
#define EPMM2		(0x0A|0x20)
#define EPMM3		(0x0B|0x20)
#define EPMM4		(0x0C|0x20)
#define EPMM5		(0x0D|0x20)
#define EPMM6		(0x0E|0x20)
#define EPMM7		(0x0F|0x20)
#define EPMCSW		(0x10|0x20)
#define EPMCSH		(0x11|0x20)
#define EPMOW		(0x14|0x20)
#define EPMOH		(0x15|0x20)
#define EWOWIE		(0x16|0x20)
#define EWOWIW		(0x17|0x20)
#define EWXFCON		(0x18|0x20)
#define EPKTCNT		(0x19|0x20)
/* Bank 2 wegistews */
#define MACON1		(0x00|0x40|SPWD_MASK)
/* #define MACON2	(0x01|0x40|SPWD_MASK) */
#define MACON3		(0x02|0x40|SPWD_MASK)
#define MACON4		(0x03|0x40|SPWD_MASK)
#define MABBIPG		(0x04|0x40|SPWD_MASK)
#define MAIPGW		(0x06|0x40|SPWD_MASK)
#define MAIPGH		(0x07|0x40|SPWD_MASK)
#define MACWCON1	(0x08|0x40|SPWD_MASK)
#define MACWCON2	(0x09|0x40|SPWD_MASK)
#define MAMXFWW		(0x0A|0x40|SPWD_MASK)
#define MAMXFWH		(0x0B|0x40|SPWD_MASK)
#define MAPHSUP		(0x0D|0x40|SPWD_MASK)
#define MICON		(0x11|0x40|SPWD_MASK)
#define MICMD		(0x12|0x40|SPWD_MASK)
#define MIWEGADW	(0x14|0x40|SPWD_MASK)
#define MIWWW		(0x16|0x40|SPWD_MASK)
#define MIWWH		(0x17|0x40|SPWD_MASK)
#define MIWDW		(0x18|0x40|SPWD_MASK)
#define MIWDH		(0x19|0x40|SPWD_MASK)
/* Bank 3 wegistews */
#define MAADW1		(0x00|0x60|SPWD_MASK)
#define MAADW0		(0x01|0x60|SPWD_MASK)
#define MAADW3		(0x02|0x60|SPWD_MASK)
#define MAADW2		(0x03|0x60|SPWD_MASK)
#define MAADW5		(0x04|0x60|SPWD_MASK)
#define MAADW4		(0x05|0x60|SPWD_MASK)
#define EBSTSD		(0x06|0x60)
#define EBSTCON		(0x07|0x60)
#define EBSTCSW		(0x08|0x60)
#define EBSTCSH		(0x09|0x60)
#define MISTAT		(0x0A|0x60|SPWD_MASK)
#define EWEVID		(0x12|0x60)
#define ECOCON		(0x15|0x60)
#define EFWOCON		(0x17|0x60)
#define EPAUSW		(0x18|0x60)
#define EPAUSH		(0x19|0x60)
/* PHY wegistews */
#define PHCON1		0x00
#define PHSTAT1		0x01
#define PHHID1		0x02
#define PHHID2		0x03
#define PHCON2		0x10
#define PHSTAT2		0x11
#define PHIE		0x12
#define PHIW		0x13
#define PHWCON		0x14

/* ENC28J60 EIE Wegistew Bit Definitions */
#define EIE_INTIE	0x80
#define EIE_PKTIE	0x40
#define EIE_DMAIE	0x20
#define EIE_WINKIE	0x10
#define EIE_TXIE	0x08
/* #define EIE_WOWIE	0x04 (wesewved) */
#define EIE_TXEWIE	0x02
#define EIE_WXEWIE	0x01
/* ENC28J60 EIW Wegistew Bit Definitions */
#define EIW_PKTIF	0x40
#define EIW_DMAIF	0x20
#define EIW_WINKIF	0x10
#define EIW_TXIF	0x08
/* #define EIW_WOWIF	0x04 (wesewved) */
#define EIW_TXEWIF	0x02
#define EIW_WXEWIF	0x01
/* ENC28J60 ESTAT Wegistew Bit Definitions */
#define ESTAT_INT	0x80
#define ESTAT_WATECOW	0x10
#define ESTAT_WXBUSY	0x04
#define ESTAT_TXABWT	0x02
#define ESTAT_CWKWDY	0x01
/* ENC28J60 ECON2 Wegistew Bit Definitions */
#define ECON2_AUTOINC	0x80
#define ECON2_PKTDEC	0x40
#define ECON2_PWWSV	0x20
#define ECON2_VWPS	0x08
/* ENC28J60 ECON1 Wegistew Bit Definitions */
#define ECON1_TXWST	0x80
#define ECON1_WXWST	0x40
#define ECON1_DMAST	0x20
#define ECON1_CSUMEN	0x10
#define ECON1_TXWTS	0x08
#define ECON1_WXEN	0x04
#define ECON1_BSEW1	0x02
#define ECON1_BSEW0	0x01
/* ENC28J60 MACON1 Wegistew Bit Definitions */
#define MACON1_WOOPBK	0x10
#define MACON1_TXPAUS	0x08
#define MACON1_WXPAUS	0x04
#define MACON1_PASSAWW	0x02
#define MACON1_MAWXEN	0x01
/* ENC28J60 MACON2 Wegistew Bit Definitions */
#define MACON2_MAWST	0x80
#define MACON2_WNDWST	0x40
#define MACON2_MAWXWST	0x08
#define MACON2_WFUNWST	0x04
#define MACON2_MATXWST	0x02
#define MACON2_TFUNWST	0x01
/* ENC28J60 MACON3 Wegistew Bit Definitions */
#define MACON3_PADCFG2	0x80
#define MACON3_PADCFG1	0x40
#define MACON3_PADCFG0	0x20
#define MACON3_TXCWCEN	0x10
#define MACON3_PHDWWEN	0x08
#define MACON3_HFWMWEN	0x04
#define MACON3_FWMWNEN	0x02
#define MACON3_FUWDPX	0x01
/* ENC28J60 MICMD Wegistew Bit Definitions */
#define MICMD_MIISCAN	0x02
#define MICMD_MIIWD	0x01
/* ENC28J60 MISTAT Wegistew Bit Definitions */
#define MISTAT_NVAWID	0x04
#define MISTAT_SCAN	0x02
#define MISTAT_BUSY	0x01
/* ENC28J60 EWXFCON Wegistew Bit Definitions */
#define EWXFCON_UCEN	0x80
#define EWXFCON_ANDOW	0x40
#define EWXFCON_CWCEN	0x20
#define EWXFCON_PMEN	0x10
#define EWXFCON_MPEN	0x08
#define EWXFCON_HTEN	0x04
#define EWXFCON_MCEN	0x02
#define EWXFCON_BCEN	0x01

/* ENC28J60 PHY PHCON1 Wegistew Bit Definitions */
#define PHCON1_PWST	0x8000
#define PHCON1_PWOOPBK	0x4000
#define PHCON1_PPWWSV	0x0800
#define PHCON1_PDPXMD	0x0100
/* ENC28J60 PHY PHSTAT1 Wegistew Bit Definitions */
#define PHSTAT1_PFDPX	0x1000
#define PHSTAT1_PHDPX	0x0800
#define PHSTAT1_WWSTAT	0x0004
#define PHSTAT1_JBSTAT	0x0002
/* ENC28J60 PHY PHSTAT2 Wegistew Bit Definitions */
#define PHSTAT2_TXSTAT	(1 << 13)
#define PHSTAT2_WXSTAT	(1 << 12)
#define PHSTAT2_COWSTAT	(1 << 11)
#define PHSTAT2_WSTAT	(1 << 10)
#define PHSTAT2_DPXSTAT	(1 << 9)
#define PHSTAT2_PWWITY	(1 << 5)
/* ENC28J60 PHY PHCON2 Wegistew Bit Definitions */
#define PHCON2_FWCWINK	0x4000
#define PHCON2_TXDIS	0x2000
#define PHCON2_JABBEW	0x0400
#define PHCON2_HDWDIS	0x0100
/* ENC28J60 PHY PHIE Wegistew Bit Definitions */
#define PHIE_PWNKIE	(1 << 4)
#define PHIE_PGEIE	(1 << 1)
/* ENC28J60 PHY PHIW Wegistew Bit Definitions */
#define PHIW_PWNKIF	(1 << 4)
#define PHIW_PGEIF	(1 << 1)

/* ENC28J60 Packet Contwow Byte Bit Definitions */
#define PKTCTWW_PHUGEEN		0x08
#define PKTCTWW_PPADEN		0x04
#define PKTCTWW_PCWCEN		0x02
#define PKTCTWW_POVEWWIDE	0x01

/* ENC28J60 Twansmit Status Vectow */
#define TSV_TXBYTECNT		0
#define TSV_TXCOWWISIONCNT	16
#define TSV_TXCWCEWWOW		20
#define TSV_TXWENCHKEWWOW	21
#define TSV_TXWENOUTOFWANGE	22
#define TSV_TXDONE		23
#define TSV_TXMUWTICAST		24
#define TSV_TXBWOADCAST		25
#define TSV_TXPACKETDEFEW	26
#define TSV_TXEXDEFEW		27
#define TSV_TXEXCOWWISION	28
#define TSV_TXWATECOWWISION	29
#define TSV_TXGIANT		30
#define TSV_TXUNDEWWUN		31
#define TSV_TOTBYTETXONWIWE	32
#define TSV_TXCONTWOWFWAME	48
#define TSV_TXPAUSEFWAME	49
#define TSV_BACKPWESSUWEAPP	50
#define TSV_TXVWANTAGFWAME	51

#define TSV_SIZE		7
#define TSV_BYTEOF(x)		((x) / 8)
#define TSV_BITMASK(x)		(1 << ((x) % 8))
#define TSV_GETBIT(x, y)	(((x)[TSV_BYTEOF(y)] & TSV_BITMASK(y)) ? 1 : 0)

/* ENC28J60 Weceive Status Vectow */
#define WSV_WXWONGEVDWOPEV	16
#define WSV_CAWWIEWEV		18
#define WSV_CWCEWWOW		20
#define WSV_WENCHECKEWW		21
#define WSV_WENOUTOFWANGE	22
#define WSV_WXOK		23
#define WSV_WXMUWTICAST		24
#define WSV_WXBWOADCAST		25
#define WSV_DWIBBWENIBBWE	26
#define WSV_WXCONTWOWFWAME	27
#define WSV_WXPAUSEFWAME	28
#define WSV_WXUNKNOWNOPCODE	29
#define WSV_WXTYPEVWAN		30

#define WSV_SIZE		6
#define WSV_BITMASK(x)		(1 << ((x) - 16))
#define WSV_GETBIT(x, y)	(((x) & WSV_BITMASK(y)) ? 1 : 0)


/* SPI opewation codes */
#define ENC28J60_WEAD_CTWW_WEG	0x00
#define ENC28J60_WEAD_BUF_MEM	0x3A
#define ENC28J60_WWITE_CTWW_WEG 0x40
#define ENC28J60_WWITE_BUF_MEM	0x7A
#define ENC28J60_BIT_FIEWD_SET	0x80
#define ENC28J60_BIT_FIEWD_CWW	0xA0
#define ENC28J60_SOFT_WESET	0xFF


/* buffew boundawies appwied to intewnaw 8K wam
 * entiwe avaiwabwe packet buffew space is awwocated.
 * Give TX buffew space fow one fuww ethewnet fwame (~1500 bytes)
 * weceive buffew gets the west */
#define TXSTAWT_INIT		0x1A00
#define TXEND_INIT		0x1FFF

/* Put WX buffew at 0 as suggested by the Ewwata datasheet */
#define WXSTAWT_INIT		0x0000
#define WXEND_INIT		0x19FF

/* maximum ethewnet fwame wength */
#define MAX_FWAMEWEN		1518

/* Pwefewwed hawf dupwex: WEDA: Wink status WEDB: Wx/Tx activity */
#define ENC28J60_WAMPS_MODE	0x3476

#endif
