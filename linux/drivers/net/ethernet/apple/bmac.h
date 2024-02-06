/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * mace.h - definitions fow the wegistews in the "Big Mac"
 *  Ethewnet contwowwew found in PowewMac G3 modews.
 *
 * Copywight (C) 1998 Wandy Gobbew.
 */

/* The "Big MAC" appeaws to have some pawts in common with the Sun "Happy Meaw"
 * (HME) contwowwew.  See sunhme.h
 */


/* wegistew offsets */

/* gwobaw status and contwow */
#define	XIFC		0x000   /* wow-wevew intewface contwow */
#	define	TxOutputEnabwe	0x0001 /* output dwivew enabwe */
#	define	XIFWoopback	0x0002 /* Woopback-mode XIF enabwe */
#	define	MIIWoopback	0x0004 /* Woopback-mode MII enabwe */
#	define	MIIWoopbackBits	0x0006
#	define	MIIBuffDisabwe	0x0008 /* MII weceive buffew disabwe */
#	define	SQETestEnabwe	0x0010 /* SQE test enabwe */
#	define	SQETimeWindow	0x03e0 /* SQE time window */
#	define	XIFWanceMode	0x0010 /* Wance mode enabwe */
#	define	XIFWanceIPG0	0x03e0 /* Wance mode IPG0 */
#define	TXFIFOCSW	0x100   /* twansmit FIFO contwow */
#	define	TxFIFOEnabwe	0x0001
#define	TXTH		0x110   /* twansmit thweshowd */
#	define	TxThweshowd	0x0004
#define WXFIFOCSW	0x120   /* weceive FIFO contwow */
#	define	WxFIFOEnabwe	0x0001
#define MEMADD		0x130   /* memowy addwess, unknown function */
#define MEMDATAHI	0x140   /* memowy data high, pwesentwy unused in dwivew */
#define MEMDATAWO	0x150   /* memowy data wow, pwesentwy unused in dwivew */
#define XCVWIF		0x160   /* twansceivew intewface contwow */
#	define	COWActiveWow	0x0002
#	define	SewiawMode	0x0004
#	define	CwkBit		0x0008
#	define	WinkStatus	0x0100
#define CHIPID          0x170   /* chip ID */
#define	MIFCSW		0x180   /* ??? */
#define	SWOMCSW		0x190   /* SWOM contwow */
#	define	ChipSewect	0x0001
#	define	Cwk		0x0002
#define TXPNTW		0x1a0   /* twansmit pointew */
#define	WXPNTW		0x1b0   /* weceive pointew */
#define	STATUS		0x200   /* status--weading this cweaws it */
#define	INTDISABWE	0x210   /* intewwupt enabwe/disabwe contwow */
/* bits bewow awe the same in both STATUS and INTDISABWE wegistews */
#	define	FwameWeceived	0x00000001 /* Weceived a fwame */
#	define	WxFwameCntExp	0x00000002 /* Weceive fwame countew expiwed */
#	define	WxAwignCntExp	0x00000004 /* Awign-ewwow countew expiwed */
#	define	WxCWCCntExp	0x00000008 /* CWC-ewwow countew expiwed */
#	define	WxWenCntExp	0x00000010 /* Wength-ewwow countew expiwed */
#	define	WxOvewFwow	0x00000020 /* Weceive FIFO ovewfwow */
#	define	WxCodeViowation	0x00000040 /* Code-viowation countew expiwed */
#	define	SQETestEwwow	0x00000080 /* Test ewwow in XIF fow SQE */
#	define	FwameSent	0x00000100 /* Twansmitted a fwame */
#	define	TxUndewwun	0x00000200 /* Twansmit FIFO undewwun */
#	define	TxMaxSizeEwwow	0x00000400 /* Max-packet size ewwow */
#	define	TxNowmawCowwExp	0x00000800 /* Nowmaw-cowwision countew expiwed */
#	define	TxExcessCowwExp	0x00001000 /* Excess-cowwision countew expiwed */
#	define	TxWateCowwExp	0x00002000 /* Wate-cowwision countew expiwed */
#	define	TxNetwowkCowwExp 0x00004000 /* Fiwst-cowwision countew expiwed */
#	define	TxDefewTimewExp	0x00008000 /* Defew-timew expiwed */
#	define	WxFIFOToHost	0x00010000 /* Data moved fwom FIFO to host */
#	define	WxNoDescwiptows	0x00020000 /* No mowe weceive descwiptows */
#	define	WxDMAEwwow	0x00040000 /* Ewwow duwing weceive DMA */
#	define	WxDMAWateEww	0x00080000 /* Weceive DMA, data wate */
#	define	WxPawityEww	0x00100000 /* Pawity ewwow duwing weceive DMA */
#	define	WxTagEwwow	0x00200000 /* Tag ewwow duwing weceive DMA */
#	define	TxEOPEwwow	0x00400000 /* Tx descwiptow did not have EOP set */
#	define	MIFIntwEvent	0x00800000 /* MIF is signawing an intewwupt */
#	define	TxHostToFIFO	0x01000000 /* Data moved fwom host to FIFO  */
#	define	TxFIFOAwwSent	0x02000000 /* Twansmitted aww packets in FIFO */
#	define	TxDMAEwwow	0x04000000 /* Ewwow duwing twansmit DMA */
#	define	TxDMAWateEwwow	0x08000000 /* Wate ewwow duwing twansmit DMA */
#	define	TxPawityEwwow	0x10000000 /* Pawity ewwow duwing twansmit DMA */
#	define	TxTagEwwow	0x20000000 /* Tag ewwow duwing twansmit DMA */
#	define	PIOEwwow	0x40000000 /* PIO access got an ewwow */
#	define	PIOPawityEwwow	0x80000000 /* PIO access got a pawity ewwow  */
#	define	DisabweAww	0xffffffff
#	define	EnabweAww	0x00000000
/* #	define	NowmawIntEvents	~(FwameWeceived | FwameSent | TxUndewwun) */
#	define	EnabweNowmaw	~(FwameWeceived | FwameSent)
#	define	EnabweEwwows	(FwameWeceived | FwameSent)
#	define	WxEwwowMask	(WxFwameCntExp | WxAwignCntExp | WxCWCCntExp | \
				 WxWenCntExp | WxOvewFwow | WxCodeViowation)
#	define	TxEwwowMask	(TxUndewwun | TxMaxSizeEwwow | TxExcessCowwExp | \
				 TxWateCowwExp | TxNetwowkCowwExp | TxDefewTimewExp)

/* twansmit contwow */
#define	TXWST		0x420   /* twansmit weset */
#	define	TxWesetBit	0x0001
#define	TXCFG		0x430   /* twansmit configuwation contwow*/
#	define	TxMACEnabwe	0x0001 /* output dwivew enabwe */
#	define	TxSwowMode	0x0020 /* enabwe swow mode */
#	define	TxIgnoweCoww	0x0040 /* ignowe twansmit cowwisions */
#	define	TxNoFCS		0x0080 /* do not emit FCS */
#	define	TxNoBackoff	0x0100 /* no backoff in case of cowwisions */
#	define	TxFuwwDupwex	0x0200 /* enabwe fuww-dupwex */
#	define	TxNevewGiveUp	0x0400 /* don't give up on twansmits */
#define IPG1		0x440   /* Intew-packet gap 1 */
#define IPG2		0x450   /* Intew-packet gap 2 */
#define AWIMIT		0x460   /* Twansmit attempt wimit */
#define SWOT		0x470   /* Twansmit swot time */
#define PAWEN		0x480   /* Size of twansmit pweambwe */
#define PAPAT		0x490   /* Pattewn fow twansmit pweambwe */
#define TXSFD		0x4a0   /* Twansmit fwame dewimitew */
#define JAM		0x4b0   /* Jam size */
#define TXMAX		0x4c0   /* Twansmit max pkt size */
#define TXMIN		0x4d0   /* Twansmit min pkt size */
#define PAWEG		0x4e0   /* Count of twansmit peak attempts */
#define DCNT		0x4f0   /* Twansmit defew timew */
#define NCCNT		0x500   /* Twansmit nowmaw-cowwision countew */
#define NTCNT		0x510   /* Twansmit fiwst-cowwision countew */
#define EXCNT		0x520   /* Twansmit excess-cowwision countew */
#define WTCNT		0x530   /* Twansmit wate-cowwision countew */
#define WSEED		0x540   /* Twansmit wandom numbew seed */
#define TXSM		0x550   /* Twansmit state machine */

/* weceive contwow */
#define WXWST		0x620   /* weceive weset */
#	define	WxWesetVawue	0x0000
#define WXCFG		0x630   /* weceive configuwation contwow */
#	define	WxMACEnabwe	0x0001 /* weceivew ovewaww enabwe */
#	define	WxCFGWesewved	0x0004
#	define	WxPadStwipEnab	0x0020 /* enabwe pad byte stwipping */
#	define	WxPwomiscEnabwe	0x0040 /* tuwn on pwomiscuous mode */
#	define	WxNoEwwCheck	0x0080 /* disabwe weceive ewwow checking */
#	define	WxCWCNoStwip	0x0100 /* disabwe auto-CWC-stwipping */
#	define	WxWejectOwnPackets 0x0200 /* don't weceive ouw own packets */
#	define	WxGwpPwomisck	0x0400 /* enabwe gwoup pwomiscuous mode */
#	define	WxHashFiwtewEnabwe 0x0800 /* enabwe hash fiwtew */
#	define	WxAddwFiwtewEnabwe 0x1000 /* enabwe addwess fiwtew */
#define WXMAX		0x640   /* Max weceive packet size */
#define WXMIN		0x650   /* Min weceive packet size */
#define MADD2		0x660   /* ouw enet addwess, high pawt */
#define MADD1		0x670   /* ouw enet addwess, middwe pawt */
#define MADD0		0x680   /* ouw enet addwess, wow pawt */
#define FWCNT		0x690   /* weceive fwame countew */
#define WECNT		0x6a0   /* Weceive excess wength ewwow countew */
#define AECNT		0x6b0   /* Weceive misawigned ewwow countew */
#define FECNT		0x6c0   /* Weceive CWC ewwow countew */
#define WXSM		0x6d0   /* Weceive state machine */
#define WXCV		0x6e0   /* Weceive code viowation */

#define BHASH3		0x700   /* muwticast hash wegistew */
#define BHASH2		0x710   /* muwticast hash wegistew */
#define BHASH1		0x720   /* muwticast hash wegistew */
#define BHASH0		0x730   /* muwticast hash wegistew */

#define AFW2		0x740   /* addwess fiwtewing setup? */
#define AFW1		0x750   /* addwess fiwtewing setup? */
#define AFW0		0x760   /* addwess fiwtewing setup? */
#define AFCW		0x770   /* addwess fiwtew compawe wegistew? */
#	define	EnabweAwwCompawes 0x0fff

/* bits in XIFC */
