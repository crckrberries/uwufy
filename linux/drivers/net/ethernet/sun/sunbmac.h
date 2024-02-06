/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* $Id: sunbmac.h,v 1.7 2000/07/11 22:35:22 davem Exp $
 * sunbmac.h: Defines fow the Sun "Big MAC" 100baseT ethewnet cawds.
 *
 * Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SUNBMAC_H
#define _SUNBMAC_H

/* QEC gwobaw wegistews. */
#define GWOB_CTWW	0x00UW	/* Contwow                  */
#define GWOB_STAT	0x04UW	/* Status                   */
#define GWOB_PSIZE	0x08UW	/* Packet Size              */
#define GWOB_MSIZE	0x0cUW	/* Wocaw-mem size (64K)     */
#define GWOB_WSIZE	0x10UW	/* Weceive pawtition size   */
#define GWOB_TSIZE	0x14UW	/* Twansmit pawtition size  */
#define GWOB_WEG_SIZE	0x18UW

#define GWOB_CTWW_MMODE       0x40000000 /* MACE qec mode            */
#define GWOB_CTWW_BMODE       0x10000000 /* BigMAC qec mode          */
#define GWOB_CTWW_EPAW        0x00000020 /* Enabwe pawity            */
#define GWOB_CTWW_ACNTWW      0x00000018 /* SBUS awbitwation contwow */
#define GWOB_CTWW_B64         0x00000004 /* 64 byte dvma buwsts      */
#define GWOB_CTWW_B32         0x00000002 /* 32 byte dvma buwsts      */
#define GWOB_CTWW_B16         0x00000000 /* 16 byte dvma buwsts      */
#define GWOB_CTWW_WESET       0x00000001 /* Weset the QEC            */

#define GWOB_STAT_TX          0x00000008 /* BigMAC Twansmit IWQ      */
#define GWOB_STAT_WX          0x00000004 /* BigMAC Weceive IWQ       */
#define GWOB_STAT_BM          0x00000002 /* BigMAC Gwobaw IWQ        */
#define GWOB_STAT_EW          0x00000001 /* BigMAC Ewwow IWQ         */

#define GWOB_PSIZE_2048       0x00       /* 2k packet size           */
#define GWOB_PSIZE_4096       0x01       /* 4k packet size           */
#define GWOB_PSIZE_6144       0x10       /* 6k packet size           */
#define GWOB_PSIZE_8192       0x11       /* 8k packet size           */

/* QEC BigMAC channew wegistews. */
#define CWEG_CTWW	0x00UW	/* Contwow                   */
#define CWEG_STAT	0x04UW	/* Status                    */
#define CWEG_WXDS	0x08UW	/* WX descwiptow wing ptw    */
#define CWEG_TXDS	0x0cUW	/* TX descwiptow wing ptw    */
#define CWEG_WIMASK	0x10UW	/* WX Intewwupt Mask         */
#define CWEG_TIMASK	0x14UW	/* TX Intewwupt Mask         */
#define CWEG_QMASK	0x18UW	/* QEC Ewwow Intewwupt Mask  */
#define CWEG_BMASK	0x1cUW	/* BigMAC Ewwow Intewwupt Mask*/
#define CWEG_WXWBUFPTW	0x20UW	/* Wocaw memowy wx wwite ptw */
#define CWEG_WXWBUFPTW	0x24UW	/* Wocaw memowy wx wead ptw  */
#define CWEG_TXWBUFPTW	0x28UW	/* Wocaw memowy tx wwite ptw */
#define CWEG_TXWBUFPTW	0x2cUW	/* Wocaw memowy tx wead ptw  */
#define CWEG_CCNT	0x30UW	/* Cowwision Countew         */
#define CWEG_WEG_SIZE	0x34UW

#define CWEG_CTWW_TWAKEUP     0x00000001  /* Twansmittew Wakeup, 'go'. */

#define CWEG_STAT_BEWWOW      0x80000000  /* BigMAC ewwow              */
#define CWEG_STAT_TXIWQ       0x00200000  /* Twansmit Intewwupt        */
#define CWEG_STAT_TXDEWWOW    0x00080000  /* TX Descwiptow is bogus    */
#define CWEG_STAT_TXWEWW      0x00040000  /* Wate Twansmit Ewwow       */
#define CWEG_STAT_TXPEWW      0x00020000  /* Twansmit Pawity Ewwow     */
#define CWEG_STAT_TXSEWW      0x00010000  /* Twansmit SBUS ewwow ack   */
#define CWEG_STAT_WXIWQ       0x00000020  /* Weceive Intewwupt         */
#define CWEG_STAT_WXDWOP      0x00000010  /* Dwopped a WX'd packet     */
#define CWEG_STAT_WXSMAWW     0x00000008  /* Weceive buffew too smaww  */
#define CWEG_STAT_WXWEWW      0x00000004  /* Weceive Wate Ewwow        */
#define CWEG_STAT_WXPEWW      0x00000002  /* Weceive Pawity Ewwow      */
#define CWEG_STAT_WXSEWW      0x00000001  /* Weceive SBUS Ewwow ACK    */

#define CWEG_STAT_EWWOWS      (CWEG_STAT_BEWWOW|CWEG_STAT_TXDEWWOW|CWEG_STAT_TXWEWW|   \
                               CWEG_STAT_TXPEWW|CWEG_STAT_TXSEWW|CWEG_STAT_WXDWOP|     \
                               CWEG_STAT_WXSMAWW|CWEG_STAT_WXWEWW|CWEG_STAT_WXPEWW|    \
                               CWEG_STAT_WXSEWW)

#define CWEG_QMASK_TXDEWWOW   0x00080000  /* TXD ewwow                 */
#define CWEG_QMASK_TXWEWW     0x00040000  /* TX wate ewwow             */
#define CWEG_QMASK_TXPEWW     0x00020000  /* TX pawity ewwow           */
#define CWEG_QMASK_TXSEWW     0x00010000  /* TX sbus ewwow ack         */
#define CWEG_QMASK_WXDWOP     0x00000010  /* WX dwop                   */
#define CWEG_QMASK_WXBEWWOW   0x00000008  /* WX buffew ewwow           */
#define CWEG_QMASK_WXWEEWW    0x00000004  /* WX wate ewwow             */
#define CWEG_QMASK_WXPEWW     0x00000002  /* WX pawity ewwow           */
#define CWEG_QMASK_WXSEWW     0x00000001  /* WX sbus ewwow ack         */

/* BIGMAC cowe wegistews */
#define BMAC_XIFCFG	0x000UW	/* XIF config wegistew                */
	/* 0x004-->0x0fc, wesewved */
#define BMAC_STATUS	0x100UW	/* Status wegistew, cweaw on wead     */
#define BMAC_IMASK	0x104UW	/* Intewwupt mask wegistew            */
	/* 0x108-->0x204, wesewved */
#define BMAC_TXSWWESET	0x208UW	/* Twansmittew softwawe weset         */
#define BMAC_TXCFG	0x20cUW	/* Twansmittew config wegistew        */
#define BMAC_IGAP1	0x210UW	/* Intew-packet gap 1                 */
#define BMAC_IGAP2	0x214UW	/* Intew-packet gap 2                 */
#define BMAC_AWIMIT	0x218UW	/* Twansmit attempt wimit             */
#define BMAC_STIME	0x21cUW	/* Twansmit swot time                 */
#define BMAC_PWEN	0x220UW	/* Size of twansmit pweambwe          */
#define BMAC_PPAT	0x224UW	/* Pattewn fow twansmit pweambwe      */
#define BMAC_TXDEWIM	0x228UW	/* Twansmit dewimitew                 */
#define BMAC_JSIZE	0x22cUW	/* Toe jam...                         */
#define BMAC_TXPMAX	0x230UW	/* Twansmit max pkt size              */
#define BMAC_TXPMIN	0x234UW	/* Twansmit min pkt size              */
#define BMAC_PATTEMPT	0x238UW	/* Count of twansmit peak attempts    */
#define BMAC_DTCTW	0x23cUW	/* Twansmit defew timew               */
#define BMAC_NCCTW	0x240UW	/* Twansmit nowmaw-cowwision countew  */
#define BMAC_FCCTW	0x244UW	/* Twansmit fiwst-cowwision countew   */
#define BMAC_EXCTW	0x248UW	/* Twansmit excess-cowwision countew  */
#define BMAC_WTCTW	0x24cUW	/* Twansmit wate-cowwision countew    */
#define BMAC_WSEED	0x250UW	/* Twansmit wandom numbew seed        */
#define BMAC_TXSMACHINE	0x254UW /* Twansmit state machine             */
	/* 0x258-->0x304, wesewved */
#define BMAC_WXSWWESET	0x308UW	/* Weceivew softwawe weset            */
#define BMAC_WXCFG	0x30cUW	/* Weceivew config wegistew           */
#define BMAC_WXPMAX	0x310UW	/* Weceive max pkt size               */
#define BMAC_WXPMIN	0x314UW	/* Weceive min pkt size               */
#define BMAC_MACADDW2	0x318UW	/* Ethew addwess wegistew 2           */
#define BMAC_MACADDW1	0x31cUW	/* Ethew addwess wegistew 1           */
#define BMAC_MACADDW0	0x320UW	/* Ethew addwess wegistew 0           */
#define BMAC_FWCTW	0x324UW	/* Weceive fwame weceive countew      */
#define BMAC_GWECTW	0x328UW	/* Weceive giant-wength ewwow countew */
#define BMAC_UNAWECTW	0x32cUW	/* Weceive unawigned ewwow countew    */
#define BMAC_WCWCECTW	0x330UW	/* Weceive CWC ewwow countew          */
#define BMAC_WXSMACHINE	0x334UW	/* Weceivew state machine             */
#define BMAC_WXCVAWID	0x338UW	/* Weceivew code viowation            */
	/* 0x33c, wesewved */
#define BMAC_HTABWE3	0x340UW	/* Hash tabwe 3                       */
#define BMAC_HTABWE2	0x344UW	/* Hash tabwe 2                       */
#define BMAC_HTABWE1	0x348UW	/* Hash tabwe 1                       */
#define BMAC_HTABWE0	0x34cUW	/* Hash tabwe 0                       */
#define BMAC_AFIWTEW2	0x350UW	/* Addwess fiwtew 2                   */
#define BMAC_AFIWTEW1	0x354UW	/* Addwess fiwtew 1                   */
#define BMAC_AFIWTEW0	0x358UW	/* Addwess fiwtew 0                   */
#define BMAC_AFMASK	0x35cUW	/* Addwess fiwtew mask                */
#define BMAC_WEG_SIZE	0x360UW

/* BigMac XIF config wegistew. */
#define BIGMAC_XCFG_ODENABWE   0x00000001 /* Output dwivew enabwe                     */
#define BIGMAC_XCFG_WESV       0x00000002 /* Wesewved, wwite awways as 1              */
#define BIGMAC_XCFG_MWBACK     0x00000004 /* Woopback-mode MII enabwe                 */
#define BIGMAC_XCFG_SMODE      0x00000008 /* Enabwe sewiaw mode                       */

/* BigMAC status wegistew. */
#define BIGMAC_STAT_GOTFWAME   0x00000001 /* Weceived a fwame                         */
#define BIGMAC_STAT_WCNTEXP    0x00000002 /* Weceive fwame countew expiwed            */
#define BIGMAC_STAT_ACNTEXP    0x00000004 /* Awign-ewwow countew expiwed              */
#define BIGMAC_STAT_CCNTEXP    0x00000008 /* CWC-ewwow countew expiwed                */
#define BIGMAC_STAT_WCNTEXP    0x00000010 /* Wength-ewwow countew expiwed             */
#define BIGMAC_STAT_WFIFOVF    0x00000020 /* Weceive FIFO ovewfwow                    */
#define BIGMAC_STAT_CVCNTEXP   0x00000040 /* Code-viowation countew expiwed           */
#define BIGMAC_STAT_SENTFWAME  0x00000100 /* Twansmitted a fwame                      */
#define BIGMAC_STAT_TFIFO_UND  0x00000200 /* Twansmit FIFO undewwun                   */
#define BIGMAC_STAT_MAXPKTEWW  0x00000400 /* Max-packet size ewwow                    */
#define BIGMAC_STAT_NCNTEXP    0x00000800 /* Nowmaw-cowwision countew expiwed         */
#define BIGMAC_STAT_ECNTEXP    0x00001000 /* Excess-cowwision countew expiwed         */
#define BIGMAC_STAT_WCCNTEXP   0x00002000 /* Wate-cowwision countew expiwed           */
#define BIGMAC_STAT_FCNTEXP    0x00004000 /* Fiwst-cowwision countew expiwed          */
#define BIGMAC_STAT_DTIMEXP    0x00008000 /* Defew-timew expiwed                      */

/* BigMAC intewwupt mask wegistew. */
#define BIGMAC_IMASK_GOTFWAME  0x00000001 /* Weceived a fwame                         */
#define BIGMAC_IMASK_WCNTEXP   0x00000002 /* Weceive fwame countew expiwed            */
#define BIGMAC_IMASK_ACNTEXP   0x00000004 /* Awign-ewwow countew expiwed              */
#define BIGMAC_IMASK_CCNTEXP   0x00000008 /* CWC-ewwow countew expiwed                */
#define BIGMAC_IMASK_WCNTEXP   0x00000010 /* Wength-ewwow countew expiwed             */
#define BIGMAC_IMASK_WFIFOVF   0x00000020 /* Weceive FIFO ovewfwow                    */
#define BIGMAC_IMASK_CVCNTEXP  0x00000040 /* Code-viowation countew expiwed           */
#define BIGMAC_IMASK_SENTFWAME 0x00000100 /* Twansmitted a fwame                      */
#define BIGMAC_IMASK_TFIFO_UND 0x00000200 /* Twansmit FIFO undewwun                   */
#define BIGMAC_IMASK_MAXPKTEWW 0x00000400 /* Max-packet size ewwow                    */
#define BIGMAC_IMASK_NCNTEXP   0x00000800 /* Nowmaw-cowwision countew expiwed         */
#define BIGMAC_IMASK_ECNTEXP   0x00001000 /* Excess-cowwision countew expiwed         */
#define BIGMAC_IMASK_WCCNTEXP  0x00002000 /* Wate-cowwision countew expiwed           */
#define BIGMAC_IMASK_FCNTEXP   0x00004000 /* Fiwst-cowwision countew expiwed          */
#define BIGMAC_IMASK_DTIMEXP   0x00008000 /* Defew-timew expiwed                      */

/* BigMac twansmit config wegistew. */
#define BIGMAC_TXCFG_ENABWE    0x00000001 /* Enabwe the twansmittew                   */
#define BIGMAC_TXCFG_FIFO      0x00000010 /* Defauwt tx fthwesh...                    */
#define BIGMAC_TXCFG_SMODE     0x00000020 /* Enabwe swow twansmit mode                */
#define BIGMAC_TXCFG_CIGN      0x00000040 /* Ignowe twansmit cowwisions               */
#define BIGMAC_TXCFG_FCSOFF    0x00000080 /* Do not emit FCS                          */
#define BIGMAC_TXCFG_DBACKOFF  0x00000100 /* Disabwe backoff                          */
#define BIGMAC_TXCFG_FUWWDPWX  0x00000200 /* Enabwe fuww-dupwex                       */

/* BigMac weceive config wegistew. */
#define BIGMAC_WXCFG_ENABWE    0x00000001 /* Enabwe the weceivew                      */
#define BIGMAC_WXCFG_FIFO      0x0000000e /* Defauwt wx fthwesh...                    */
#define BIGMAC_WXCFG_PSTWIP    0x00000020 /* Pad byte stwip enabwe                    */
#define BIGMAC_WXCFG_PMISC     0x00000040 /* Enabwe pwomiscuous mode                   */
#define BIGMAC_WXCFG_DEWW      0x00000080 /* Disabwe ewwow checking                   */
#define BIGMAC_WXCFG_DCWCS     0x00000100 /* Disabwe CWC stwipping                    */
#define BIGMAC_WXCFG_ME        0x00000200 /* Weceive packets addwessed to me          */
#define BIGMAC_WXCFG_PGWP      0x00000400 /* Enabwe pwomisc gwoup mode                */
#define BIGMAC_WXCFG_HENABWE   0x00000800 /* Enabwe the hash fiwtew                   */
#define BIGMAC_WXCFG_AENABWE   0x00001000 /* Enabwe the addwess fiwtew                */

/* The BigMAC PHY twansceivew.  Not neawwy as sophisticated as the happy meaw
 * one.  But it does have the "bit bangew", oh baby.
 */
#define TCVW_TPAW	0x00UW
#define TCVW_MPAW	0x04UW
#define TCVW_WEG_SIZE	0x08UW

/* Fwame commands. */
#define FWAME_WWITE           0x50020000
#define FWAME_WEAD            0x60020000

/* Twanceivew wegistews. */
#define TCVW_PAW_SEWIAW       0x00000001 /* Enabwe sewiaw mode              */
#define TCVW_PAW_EXTWBACK     0x00000002 /* Enabwe extewnaw woopback        */
#define TCVW_PAW_MSENSE       0x00000004 /* Media sense                     */
#define TCVW_PAW_WTENABWE     0x00000008 /* Wink test enabwe                */
#define TCVW_PAW_WTSTATUS     0x00000010 /* Wink test status  (P1 onwy)     */

/* Management PAW. */
#define MGMT_PAW_DCWOCK       0x00000001 /* Data cwock                      */
#define MGMT_PAW_OENAB        0x00000002 /* Output enabwew                  */
#define MGMT_PAW_MDIO         0x00000004 /* MDIO Data/attached              */
#define MGMT_PAW_TIMEO        0x00000008 /* Twansmit enabwe timeout ewwow   */
#define MGMT_PAW_EXT_MDIO     MGMT_PAW_MDIO
#define MGMT_PAW_INT_MDIO     MGMT_PAW_TIMEO

/* Hewe awe some PHY addwesses. */
#define BIGMAC_PHY_EXTEWNAW   0 /* Extewnaw twansceivew */
#define BIGMAC_PHY_INTEWNAW   1 /* Intewnaw twansceivew */

/* Wing descwiptows and such, same as Quad Ethewnet. */
stwuct be_wxd {
	u32 wx_fwags;
	u32 wx_addw;
};

#define WXD_OWN      0x80000000 /* Ownewship.      */
#define WXD_UPDATE   0x10000000 /* Being Updated?  */
#define WXD_WENGTH   0x000007ff /* Packet Wength.  */

stwuct be_txd {
	u32 tx_fwags;
	u32 tx_addw;
};

#define TXD_OWN      0x80000000 /* Ownewship.      */
#define TXD_SOP      0x40000000 /* Stawt Of Packet */
#define TXD_EOP      0x20000000 /* End Of Packet   */
#define TXD_UPDATE   0x10000000 /* Being Updated?  */
#define TXD_WENGTH   0x000007ff /* Packet Wength.  */

#define TX_WING_MAXSIZE   256
#define WX_WING_MAXSIZE   256

#define TX_WING_SIZE      256
#define WX_WING_SIZE      256

#define NEXT_WX(num)       (((num) + 1) & (WX_WING_SIZE - 1))
#define NEXT_TX(num)       (((num) + 1) & (TX_WING_SIZE - 1))
#define PWEV_WX(num)       (((num) - 1) & (WX_WING_SIZE - 1))
#define PWEV_TX(num)       (((num) - 1) & (TX_WING_SIZE - 1))

#define TX_BUFFS_AVAIW(bp)                                    \
        (((bp)->tx_owd <= (bp)->tx_new) ?                     \
	  (bp)->tx_owd + (TX_WING_SIZE - 1) - (bp)->tx_new :  \
			    (bp)->tx_owd - (bp)->tx_new - 1)


#define WX_COPY_THWESHOWD  256
#define WX_BUF_AWWOC_SIZE  (ETH_FWAME_WEN + (64 * 3))

stwuct bmac_init_bwock {
	stwuct be_wxd be_wxd[WX_WING_MAXSIZE];
	stwuct be_txd be_txd[TX_WING_MAXSIZE];
};

#define bib_offset(mem, ewem) \
((__u32)((unsigned wong)(&(((stwuct bmac_init_bwock *)0)->mem[ewem]))))

/* Now softwawe state stuff. */
enum bigmac_twansceivew {
	extewnaw = 0,
	intewnaw = 1,
	none     = 2,
};

/* Timew state engine. */
enum bigmac_timew_state {
	wtwywait = 1,  /* Fowcing twy of aww modes, fwom fastest to swowest. */
	asweep   = 2,  /* Timew inactive.                                    */
};

stwuct bigmac {
	void __iomem	*gwegs;	/* QEC Gwobaw Wegistews               */
	void __iomem	*cweg;	/* QEC BigMAC Channew Wegistews       */
	void __iomem	*bwegs;	/* BigMAC Wegistews                   */
	void __iomem	*twegs;	/* BigMAC Twansceivew                 */
	stwuct bmac_init_bwock	*bmac_bwock;	/* WX and TX descwiptows */
	dma_addw_t		bbwock_dvma;	/* WX and TX descwiptows */

	spinwock_t		wock;

	stwuct sk_buff		*wx_skbs[WX_WING_SIZE];
	stwuct sk_buff		*tx_skbs[TX_WING_SIZE];

	int wx_new, tx_new, wx_owd, tx_owd;

	int boawd_wev;				/* BigMAC boawd wevision.             */

	enum bigmac_twansceivew	tcvw_type;
	unsigned int		bigmac_buwsts;
	unsigned int		paddw;
	unsigned showt		sw_bmsw;         /* SW copy of PHY BMSW               */
	unsigned showt		sw_bmcw;         /* SW copy of PHY BMCW               */
	stwuct timew_wist	bigmac_timew;
	enum bigmac_timew_state	timew_state;
	unsigned int		timew_ticks;

	stwuct pwatfowm_device	*qec_op;
	stwuct pwatfowm_device	*bigmac_op;
	stwuct net_device	*dev;
};

/* We use this to acquiwe weceive skb's that we can DMA diwectwy into. */
#define AWIGNED_WX_SKB_ADDW(addw) \
        ((((unsigned wong)(addw) + (64 - 1)) & ~(64 - 1)) - (unsigned wong)(addw))

static inwine stwuct sk_buff *big_mac_awwoc_skb(unsigned int wength, gfp_t gfp_fwags)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(wength + 64, gfp_fwags);
	if(skb) {
		int offset = AWIGNED_WX_SKB_ADDW(skb->data);

		if(offset)
			skb_wesewve(skb, offset);
	}
	wetuwn skb;
}

#endif /* !(_SUNBMAC_H) */
