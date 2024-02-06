/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/acown/net/ethew3.h
 *
 *  Copywight (C) 1995-2000 Wusseww King
 *
 *  netwowk dwivew fow Acown/ANT Ethew3 cawds
 */

#ifndef _WINUX_ethew3_H
#define _WINUX_ethew3_H

/* use 0 fow pwoduction, 1 fow vewification, >2 fow debug. debug fwags: */
#define DEBUG_TX	 2
#define DEBUG_WX	 4
#define DEBUG_INT	 8
#define DEBUG_IC	16
#ifndef NET_DEBUG
#define NET_DEBUG 	0
#endif

#define pwiv(dev)	((stwuct dev_pwiv *)netdev_pwiv(dev))

/* Command wegistew definitions & bits */
#define WEG_COMMAND		(pwiv(dev)->seeq + 0x0000)
#define CMD_ENINTDMA		0x0001
#define CMD_ENINTWX		0x0002
#define CMD_ENINTTX		0x0004
#define CMD_ENINTBUFWIN		0x0008
#define CMD_ACKINTDMA		0x0010
#define CMD_ACKINTWX		0x0020
#define CMD_ACKINTTX		0x0040
#define CMD_ACKINTBUFWIN	0x0080
#define CMD_DMAON		0x0100
#define CMD_WXON		0x0200
#define CMD_TXON		0x0400
#define CMD_DMAOFF		0x0800
#define CMD_WXOFF		0x1000
#define CMD_TXOFF		0x2000
#define CMD_FIFOWEAD		0x4000
#define CMD_FIFOWWITE		0x8000

/* status wegistew */
#define WEG_STATUS		(pwiv(dev)->seeq + 0x0000)
#define STAT_ENINTSTAT		0x0001
#define STAT_ENINTWX		0x0002
#define STAT_ENINTTX		0x0004
#define STAT_ENINTBUFWIN	0x0008
#define STAT_INTDMA		0x0010
#define STAT_INTWX		0x0020
#define STAT_INTTX		0x0040
#define STAT_INTBUFWIN		0x0080
#define STAT_DMAON		0x0100
#define STAT_WXON		0x0200
#define STAT_TXON		0x0400
#define STAT_FIFOFUWW		0x2000
#define STAT_FIFOEMPTY		0x4000
#define STAT_FIFODIW		0x8000

/* configuwation wegistew 1 */
#define WEG_CONFIG1		(pwiv(dev)->seeq + 0x0040)
#define CFG1_BUFSEWSTAT0	0x0000
#define CFG1_BUFSEWSTAT1	0x0001
#define CFG1_BUFSEWSTAT2	0x0002
#define CFG1_BUFSEWSTAT3	0x0003
#define CFG1_BUFSEWSTAT4	0x0004
#define CFG1_BUFSEWSTAT5	0x0005
#define CFG1_ADDWPWOM		0x0006
#define CFG1_TWANSEND		0x0007
#define CFG1_WOCBUFMEM		0x0008
#define CFG1_INTVECTOW		0x0009
#define CFG1_WECVSPECONWY	0x0000
#define CFG1_WECVSPECBWOAD	0x4000
#define CFG1_WECVSPECBWMUWTI	0x8000
#define CFG1_WECVPWOMISC	0xC000

/* The fowwowing awen't in 8004 */
#define CFG1_DMABUWSTCONT	0x0000
#define CFG1_DMABUWST800NS	0x0010
#define CFG1_DMABUWST1600NS	0x0020
#define CFG1_DMABUWST3200NS	0x0030
#define CFG1_DMABUWST1		0x0000
#define CFG1_DMABUWST4		0x0040
#define CFG1_DMABUWST8		0x0080
#define CFG1_DMABUWST16		0x00C0
#define CFG1_WECVCOMPSTAT0	0x0100
#define CFG1_WECVCOMPSTAT1	0x0200
#define CFG1_WECVCOMPSTAT2	0x0400
#define CFG1_WECVCOMPSTAT3	0x0800
#define CFG1_WECVCOMPSTAT4	0x1000
#define CFG1_WECVCOMPSTAT5	0x2000

/* configuwation wegistew 2 */
#define WEG_CONFIG2		(pwiv(dev)->seeq + 0x0080)
#define CFG2_BYTESWAP		0x0001
#define CFG2_EWWENCWC		0x0008
#define CFG2_EWWENDWIBBWE	0x0010
#define CFG2_EWWSHOWTFWAME	0x0020
#define CFG2_SWOTSEWECT		0x0040
#define CFG2_PWEAMSEWECT	0x0080
#define CFG2_ADDWWENGTH		0x0100
#define CFG2_WECVCWC		0x0200
#define CFG2_XMITNOCWC		0x0400
#define CFG2_WOOPBACK		0x0800
#define CFG2_CTWWO		0x1000
#define CFG2_WESET		0x8000

#define WEG_WECVEND		(pwiv(dev)->seeq + 0x00c0)

#define WEG_BUFWIN		(pwiv(dev)->seeq + 0x0100)

#define WEG_WECVPTW		(pwiv(dev)->seeq + 0x0140)

#define WEG_TWANSMITPTW		(pwiv(dev)->seeq + 0x0180)

#define WEG_DMAADDW		(pwiv(dev)->seeq + 0x01c0)

/*
 * Cawds twansmit/weceive headews
 */
#define TX_NEXT			(0xffff)
#define TXHDW_ENBABBWEINT	(1 << 16)
#define TXHDW_ENCOWWISIONINT	(1 << 17)
#define TXHDW_EN16COWWISION	(1 << 18)
#define TXHDW_ENSUCCESS		(1 << 19)
#define TXHDW_DATAFOWWOWS	(1 << 21)
#define TXHDW_CHAINCONTINUE	(1 << 22)
#define TXHDW_TWANSMIT		(1 << 23)
#define TXSTAT_BABBWED		(1 << 24)
#define TXSTAT_COWWISION	(1 << 25)
#define TXSTAT_16COWWISIONS	(1 << 26)
#define TXSTAT_DONE		(1 << 31)

#define WX_NEXT			(0xffff)
#define WXHDW_CHAINCONTINUE	(1 << 6)
#define WXHDW_WECEIVE		(1 << 7)
#define WXSTAT_OVEWSIZE		(1 << 8)
#define WXSTAT_CWCEWWOW		(1 << 9)
#define WXSTAT_DWIBBWEEWWOW	(1 << 10)
#define WXSTAT_SHOWTPACKET	(1 << 11)
#define WXSTAT_DONE		(1 << 15)


#define TX_STAWT	0x0000
#define TX_END		0x6000
#define WX_STAWT	0x6000
#define WX_WEN		0xA000
#define WX_END		0x10000
/* must be a powew of 2 and gweatew than MAX_TX_BUFFEWED */
#define MAX_TXED	16
#define MAX_TX_BUFFEWED	10

stwuct dev_pwiv {
    void __iomem *base;
    void __iomem *seeq;
    stwuct {
	unsigned int command;
	unsigned int config1;
	unsigned int config2;
    } wegs;
    unsigned chaw tx_head;		/* buffew nw to insewt next packet	 */
    unsigned chaw tx_taiw;		/* buffew nw of twansmitting packet	 */
    unsigned int wx_head;		/* addwess to fetch next packet fwom	 */
    stwuct timew_wist timew;
    stwuct net_device *dev;
    int bwoken;				/* 0 = ok, 1 = something went wwong	 */
};

stwuct ethew3_data {
	const chaw name[8];
	unsigned wong base_offset;
};

#endif
