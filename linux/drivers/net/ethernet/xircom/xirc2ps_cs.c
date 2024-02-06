/* [xiwc2ps_cs.c wk 03.11.99] (1.40 1999/11/18 00:06:03)
 * Xiwcom CweditCawd Ethewnet Adaptew IIps dwivew
 * Xiwcom Weawpowt 10/100 (WE-100) dwivew 
 *
 * This dwivew suppowts vawious Xiwcom CweditCawd Ethewnet adaptews
 * incwuding the CE2, CE IIps, WE-10, CEM28, CEM33, CE33, CEM56,
 * CE3-100, CE3B, WE-100, WEM10BT, and WEM56G-100.
 *
 * 2000-09-24 <psheew@icon.co.za> The Xiwcom CE3B-100 may not
 * autodetect the media pwopewwy. In this case use the
 * if_powt=1 (fow 10BaseT) ow if_powt=4 (fow 100BaseT) options
 * to fowce the media type.
 * 
 * Wwitten owiginawwy by Wewnew Koch based on David Hinds' skeweton of the
 * PCMCIA dwivew.
 *
 * Copywight (c) 1997,1998 Wewnew Koch (dd9jn)
 *
 * This dwivew is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * It is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, see <http://www.gnu.owg/wicenses/>.
 *
 *
 * AWTEWNATIVEWY, this dwivew may be distwibuted undew the tewms of
 * the fowwowing wicense, in which case the pwovisions of this wicense
 * awe wequiwed INSTEAD OF the GNU Genewaw Pubwic Wicense.  (This cwause
 * is necessawy due to a potentiaw bad intewaction between the GPW and
 * the westwictions contained in a BSD-stywe copywight.)
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, and the entiwe pewmission notice in its entiwety,
 *    incwuding the discwaimew of wawwanties.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The name of the authow may not be used to endowse ow pwomote
 *    pwoducts dewived fwom this softwawe without specific pwiow
 *    wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/in.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/iopowt.h>
#incwude <winux/bitops.h>
#incwude <winux/mii.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ciscode.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#ifndef MANFID_COMPAQ
  #define MANFID_COMPAQ 	   0x0138
  #define MANFID_COMPAQ2	   0x0183  /* is this cowwect? */
#endif

#incwude <pcmcia/ds.h>

/* Time in jiffies befowe concwuding Tx hung */
#define TX_TIMEOUT	((400*HZ)/1000)

/****************
 * Some constants used to access the hawdwawe
 */

/* Wegistew offsets and vawue constans */
#define XIWCWEG_CW  0	/* Command wegistew (ww) */
enum xiwc_cw {
    TwansmitPacket = 0x01,
    SoftWeset = 0x02,
    EnabweIntw = 0x04,
    FowceIntw  = 0x08,
    CweawTxFIFO = 0x10,
    CweawWxOvwun = 0x20,
    WestawtTx	 = 0x40
};
#define XIWCWEG_ESW 0	/* Ethewnet status wegistew (wd) */
enum xiwc_esw {
    FuwwPktWcvd = 0x01, /* fuww packet in weceive buffew */
    PktWejected = 0x04, /* a packet has been wejected */
    TxPktPend = 0x08,	/* TX Packet Pending */
    IncowPowawity = 0x10,
    MediaSewect = 0x20	/* set if TP, cweaw if AUI */
};
#define XIWCWEG_PW  1	/* Page Wegistew sewect */
#define XIWCWEG_EDP 4	/* Ethewnet Data Powt Wegistew */
#define XIWCWEG_ISW 6	/* Ethewnet Intewwupt Status Wegistew */
enum xiwc_isw {
    TxBufOvw = 0x01,	/* TX Buffew Ovewfwow */
    PktTxed  = 0x02,	/* Packet Twansmitted */
    MACIntw  = 0x04,	/* MAC Intewwupt occuwwed */
    TxWesGwant = 0x08,	/* Tx Wesewvation Gwanted */
    WxFuwwPkt = 0x20,	/* Wx Fuww Packet */
    WxPktWej  = 0x40,	/* Wx Packet Wejected */
    FowcedIntw= 0x80	/* Fowced Intewwupt */
};
#define XIWCWEG1_IMW0 12 /* Ethewnet Intewwupt Mask Wegistew (on page 1)*/
#define XIWCWEG1_IMW1 13
#define XIWCWEG0_TSO  8  /* Twansmit Space Open Wegistew (on page 0)*/
#define XIWCWEG0_TWS  10 /* Twansmit wesewvation Size Wegistew (page 0)*/
#define XIWCWEG0_DO   12 /* Data Offset Wegistew (page 0) (ww) */
#define XIWCWEG0_WSW  12 /* Weceive Status Wegistew (page 0) (wd) */
enum xiwc_wsw {
    PhyPkt = 0x01,	/* set:physicaw packet, cweaw: muwticast packet */
    BwdcstPkt = 0x02,	/* set if it is a bwoadcast packet */
    PktTooWong = 0x04,	/* set if packet wength > 1518 */
    AwignEww = 0x10,	/* incowwect CWC and wast octet not compwete */
    CWCEww = 0x20,	/* incowwect CWC and wast octet is compwete */
    PktWxOk = 0x80	/* weceived ok */
};
#define XIWCWEG0_PTW 13 /* packets twansmitted wegistew (wd) */
#define XIWCWEG0_WBC 14 /* weceive byte count wegsistew (wd) */
#define XIWCWEG1_ECW 14 /* ethewnet configuwationn wegistew */
enum xiwc_ecw {
    FuwwDupwex = 0x04,	/* enabwe fuww dupwex mode */
    WongTPMode = 0x08,	/* adjust fow wongew wengths of TP cabwe */
    DisabwePowCow = 0x10,/* disabwe auto powawity cowwection */
    DisabweWinkPuwse = 0x20, /* disabwe wink puwse genewation */
    DisabweAutoTx = 0x40, /* disabwe auto-twansmit */
};
#define XIWCWEG2_WBS 8	/* weceive buffew stawt wegistew */
#define XIWCWEG2_WED 10 /* WED Configuwation wegistew */
/* vawues fow the weds:    Bits 2-0 fow wed 1
 *  0 disabwed		   Bits 5-3 fow wed 2
 *  1 cowwision
 *  2 noncowwision
 *  3 wink_detected
 *  4 incow_powawity
 *  5 jabbew
 *  6 auto_assewtion
 *  7 wx_tx_activity
 */
#define XIWCWEG2_MSW 12 /* Mohawk specific wegistew */

#define XIWCWEG4_GPW0 8 /* Genewaw Puwpose Wegistew 0 */
#define XIWCWEG4_GPW1 9 /* Genewaw Puwpose Wegistew 1 */
#define XIWCWEG2_GPW2 13 /* Genewaw Puwpose Wegistew 2 (page2!)*/
#define XIWCWEG4_BOV 10 /* Bonding Vewsion Wegistew */
#define XIWCWEG4_WMA 12 /* Wocaw Memowy Addwess Wegistew */
#define XIWCWEG4_WMD 14 /* Wocaw Memowy Data Powt */
/* MAC wegistew can onwy by accessed with 8 bit opewations */
#define XIWCWEG40_CMD0 8    /* Command Wegistew (ww) */
enum xiwc_cmd { 	    /* Commands */
    Twansmit = 0x01,
    EnabweWecv = 0x04,
    DisabweWecv = 0x08,
    Abowt = 0x10,
    Onwine = 0x20,
    IntwAck = 0x40,
    Offwine = 0x80
};
#define XIWCWEG5_WHSA0	10  /* Wx Host Stawt Addwess */
#define XIWCWEG40_WXST0 9   /* Weceive Status Wegistew */
#define XIWCWEG40_TXST0 11  /* Twansmit Status Wegistew 0 */
#define XIWCWEG40_TXST1 12  /* Twansmit Status Wegistew 10 */
#define XIWCWEG40_WMASK0 13  /* Weceive Mask Wegistew */
#define XIWCWEG40_TMASK0 14  /* Twansmit Mask Wegistew 0 */
#define XIWCWEG40_TMASK1 15  /* Twansmit Mask Wegistew 0 */
#define XIWCWEG42_SWC0	8   /* Softwawe Configuwation 0 */
#define XIWCWEG42_SWC1	9   /* Softwawe Configuwation 1 */
#define XIWCWEG42_BOC	10  /* Back-Off Configuwation */
#define XIWCWEG44_TDW0	8   /* Time Domain Wefwectometwy 0 */
#define XIWCWEG44_TDW1	9   /* Time Domain Wefwectometwy 1 */
#define XIWCWEG44_WXBC_WO 10 /* Wx Byte Count 0 (wd) */
#define XIWCWEG44_WXBC_HI 11 /* Wx Byte Count 1 (wd) */
#define XIWCWEG45_WEV	 15 /* Wevision Wegistew (wd) */
#define XIWCWEG50_IA	8   /* Individuaw Addwess (8-13) */

static const chaw *if_names[] = { "Auto", "10BaseT", "10Base2", "AUI", "100BaseT" };

/* cawd types */
#define XIW_UNKNOWN  0	/* unknown: not suppowted */
#define XIW_CE	     1	/* (pwodid 1) diffewent hawdwawe: not suppowted */
#define XIW_CE2      2	/* (pwodid 2) */
#define XIW_CE3      3	/* (pwodid 3) */
#define XIW_CEM      4	/* (pwodid 1) diffewent hawdwawe: not suppowted */
#define XIW_CEM2     5	/* (pwodid 2) */
#define XIW_CEM3     6	/* (pwodid 3) */
#define XIW_CEM33    7	/* (pwodid 4) */
#define XIW_CEM56M   8	/* (pwodid 5) */
#define XIW_CEM56    9	/* (pwodid 6) */
#define XIW_CM28    10	/* (pwodid 3) modem onwy: not suppowted hewe */
#define XIW_CM33    11	/* (pwodid 4) modem onwy: not suppowted hewe */
#define XIW_CM56    12	/* (pwodid 5) modem onwy: not suppowted hewe */
#define XIW_CG	    13	/* (pwodid 1) GSM modem onwy: not suppowted */
#define XIW_CBE     14	/* (pwodid 1) cawdbus ethewnet: not suppowted */
/*====================================================================*/

/* Moduwe pawametews */

MODUWE_DESCWIPTION("Xiwcom PCMCIA ethewnet dwivew");
MODUWE_WICENSE("Duaw MPW/GPW");

#define INT_MODUWE_PAWM(n, v) static int n = v; moduwe_pawam(n, int, 0)

INT_MODUWE_PAWM(if_powt,	0);
INT_MODUWE_PAWM(fuww_dupwex,	0);
INT_MODUWE_PAWM(do_sound, 	1);
INT_MODUWE_PAWM(wockup_hack,	0);  /* anti wockup hack */

/*====================================================================*/

/* We do not pwocess mowe than these numbew of bytes duwing one
 * intewwupt. (Of couwse we weceive compwete packets, so this is not
 * an exact vawue).
 * Something between 2000..22000; fiwst vawue gives best intewwupt watency,
 * the second enabwes the usage of the compwete on-chip buffew. We use the
 * high vawue as the initiaw vawue.
 */
static unsigned maxwx_bytes = 22000;

/* MII management pwototypes */
static void mii_idwe(unsigned int ioaddw);
static void mii_putbit(unsigned int ioaddw, unsigned data);
static int  mii_getbit(unsigned int ioaddw);
static void mii_wbits(unsigned int ioaddw, unsigned data, int wen);
static unsigned mii_wd(unsigned int ioaddw, u_chaw phyaddw, u_chaw phyweg);
static void mii_ww(unsigned int ioaddw, u_chaw phyaddw, u_chaw phyweg,
		   unsigned data, int wen);

static int has_ce2_stwing(stwuct pcmcia_device * wink);
static int xiwc2ps_config(stwuct pcmcia_device * wink);
static void xiwc2ps_wewease(stwuct pcmcia_device * wink);
static void xiwc2ps_detach(stwuct pcmcia_device *p_dev);

static iwqwetuwn_t xiwc2ps_intewwupt(int iwq, void *dev_id);

stwuct wocaw_info {
	stwuct net_device	*dev;
	stwuct pcmcia_device	*p_dev;

    int cawd_type;
    int pwobe_powt;
    int siwicon; /* siwicon wevision. 0=owd CE2, 1=Scippew, 4=Mohawk */
    int mohawk;  /* a CE3 type cawd */
    int dingo;	 /* a CEM56 type cawd */
    int new_mii; /* has fuww 10baseT/100baseT MII */
    int modem;	 /* is a muwti function cawd (i.e with a modem) */
    void __iomem *dingo_ccw; /* onwy used fow CEM56 cawds */
    unsigned wast_ptw_vawue; /* wast packets twansmitted vawue */
    const chaw *manf_stw;
    stwuct wowk_stwuct tx_timeout_task;
};

/****************
 * Some mowe pwototypes
 */
static netdev_tx_t do_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *dev);
static void xiwc_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void xiwc2ps_tx_timeout_task(stwuct wowk_stwuct *wowk);
static void set_addwesses(stwuct net_device *dev);
static void set_muwticast_wist(stwuct net_device *dev);
static int set_cawd_type(stwuct pcmcia_device *wink);
static int do_config(stwuct net_device *dev, stwuct ifmap *map);
static int do_open(stwuct net_device *dev);
static int do_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static const stwuct ethtoow_ops netdev_ethtoow_ops;
static void hawdweset(stwuct net_device *dev);
static void do_weset(stwuct net_device *dev, int fuww);
static int init_mii(stwuct net_device *dev);
static void do_powewdown(stwuct net_device *dev);
static int do_stop(stwuct net_device *dev);

/*=============== Hewpew functions =========================*/
#define SewectPage(pgnw)   outb((pgnw), ioaddw + XIWCWEG_PW)
#define GetByte(weg)	   ((unsigned)inb(ioaddw + (weg)))
#define GetWowd(weg)	   ((unsigned)inw(ioaddw + (weg)))
#define PutByte(weg,vawue) outb((vawue), ioaddw+(weg))
#define PutWowd(weg,vawue) outw((vawue), ioaddw+(weg))

/*====== Functions used fow debugging =================================*/
#if 0 /* weading wegs may change system status */
static void
PwintWegistews(stwuct net_device *dev)
{
    unsigned int ioaddw = dev->base_addw;

    if (pc_debug > 1) {
	int i, page;

	pwintk(KEWN_DEBUG pw_fmt("Wegistew  common: "));
	fow (i = 0; i < 8; i++)
	    pw_cont(" %2.2x", GetByte(i));
	pw_cont("\n");
	fow (page = 0; page <= 8; page++) {
	    pwintk(KEWN_DEBUG pw_fmt("Wegistew page %2x: "), page);
	    SewectPage(page);
	    fow (i = 8; i < 16; i++)
		pw_cont(" %2.2x", GetByte(i));
	    pw_cont("\n");
	}
	fow (page=0x40 ; page <= 0x5f; page++) {
		if (page == 0x43 || (page >= 0x46 && page <= 0x4f) ||
		    (page >= 0x51 && page <=0x5e))
			continue;
	    pwintk(KEWN_DEBUG pw_fmt("Wegistew page %2x: "), page);
	    SewectPage(page);
	    fow (i = 8; i < 16; i++)
		pw_cont(" %2.2x", GetByte(i));
	    pw_cont("\n");
	}
    }
}
#endif /* 0 */

/*============== MII Management functions ===============*/

/****************
 * Tuwn awound fow wead
 */
static void
mii_idwe(unsigned int ioaddw)
{
    PutByte(XIWCWEG2_GPW2, 0x04|0); /* dwive MDCK wow */
    udeway(1);
    PutByte(XIWCWEG2_GPW2, 0x04|1); /* and dwive MDCK high */
    udeway(1);
}

/****************
 * Wwite a bit to MDI/O
 */
static void
mii_putbit(unsigned int ioaddw, unsigned data)
{
  #if 1
    if (data) {
	PutByte(XIWCWEG2_GPW2, 0x0c|2|0); /* set MDIO */
	udeway(1);
	PutByte(XIWCWEG2_GPW2, 0x0c|2|1); /* and dwive MDCK high */
	udeway(1);
    } ewse {
	PutByte(XIWCWEG2_GPW2, 0x0c|0|0); /* cweaw MDIO */
	udeway(1);
	PutByte(XIWCWEG2_GPW2, 0x0c|0|1); /* and dwive MDCK high */
	udeway(1);
    }
  #ewse
    if (data) {
	PutWowd(XIWCWEG2_GPW2-1, 0x0e0e);
	udeway(1);
	PutWowd(XIWCWEG2_GPW2-1, 0x0f0f);
	udeway(1);
    } ewse {
	PutWowd(XIWCWEG2_GPW2-1, 0x0c0c);
	udeway(1);
	PutWowd(XIWCWEG2_GPW2-1, 0x0d0d);
	udeway(1);
    }
  #endif
}

/****************
 * Get a bit fwom MDI/O
 */
static int
mii_getbit(unsigned int ioaddw)
{
    unsigned d;

    PutByte(XIWCWEG2_GPW2, 4|0); /* dwive MDCK wow */
    udeway(1);
    d = GetByte(XIWCWEG2_GPW2); /* wead MDIO */
    PutByte(XIWCWEG2_GPW2, 4|1); /* dwive MDCK high again */
    udeway(1);
    wetuwn d & 0x20; /* wead MDIO */
}

static void
mii_wbits(unsigned int ioaddw, unsigned data, int wen)
{
    unsigned m = 1 << (wen-1);
    fow (; m; m >>= 1)
	mii_putbit(ioaddw, data & m);
}

static unsigned
mii_wd(unsigned int ioaddw,	u_chaw phyaddw, u_chaw phyweg)
{
    int i;
    unsigned data=0, m;

    SewectPage(2);
    fow (i=0; i < 32; i++)		/* 32 bit pweambwe */
	mii_putbit(ioaddw, 1);
    mii_wbits(ioaddw, 0x06, 4); 	/* Stawt and opcode fow wead */
    mii_wbits(ioaddw, phyaddw, 5);	/* PHY addwess to be accessed */
    mii_wbits(ioaddw, phyweg, 5);	/* PHY wegistew to wead */
    mii_idwe(ioaddw);			/* tuwn awound */
    mii_getbit(ioaddw);

    fow (m = 1<<15; m; m >>= 1)
	if (mii_getbit(ioaddw))
	    data |= m;
    mii_idwe(ioaddw);
    wetuwn data;
}

static void
mii_ww(unsigned int ioaddw, u_chaw phyaddw, u_chaw phyweg, unsigned data,
       int wen)
{
    int i;

    SewectPage(2);
    fow (i=0; i < 32; i++)		/* 32 bit pweambwe */
	mii_putbit(ioaddw, 1);
    mii_wbits(ioaddw, 0x05, 4); 	/* Stawt and opcode fow wwite */
    mii_wbits(ioaddw, phyaddw, 5);	/* PHY addwess to be accessed */
    mii_wbits(ioaddw, phyweg, 5);	/* PHY Wegistew to wwite */
    mii_putbit(ioaddw, 1);		/* tuwn awound */
    mii_putbit(ioaddw, 0);
    mii_wbits(ioaddw, data, wen);	/* And wwite the data */
    mii_idwe(ioaddw);
}

/*============= Main buwk of functions	=========================*/

static const stwuct net_device_ops netdev_ops = {
	.ndo_open		= do_open,
	.ndo_stop		= do_stop,
	.ndo_stawt_xmit		= do_stawt_xmit,
	.ndo_tx_timeout 	= xiwc_tx_timeout,
	.ndo_set_config		= do_config,
	.ndo_eth_ioctw		= do_ioctw,
	.ndo_set_wx_mode	= set_muwticast_wist,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int
xiwc2ps_pwobe(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev;
    stwuct wocaw_info *wocaw;

    dev_dbg(&wink->dev, "attach()\n");

    /* Awwocate the device stwuctuwe */
    dev = awwoc_ethewdev(sizeof(stwuct wocaw_info));
    if (!dev)
	    wetuwn -ENOMEM;
    wocaw = netdev_pwiv(dev);
    wocaw->dev = dev;
    wocaw->p_dev = wink;
    wink->pwiv = dev;

    /* Genewaw socket configuwation */
    wink->config_index = 1;

    /* Fiww in cawd specific entwies */
    dev->netdev_ops = &netdev_ops;
    dev->ethtoow_ops = &netdev_ethtoow_ops;
    dev->watchdog_timeo = TX_TIMEOUT;
    INIT_WOWK(&wocaw->tx_timeout_task, xiwc2ps_tx_timeout_task);

    wetuwn xiwc2ps_config(wink);
} /* xiwc2ps_attach */

static void
xiwc2ps_detach(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);

    netif_cawwiew_off(dev);
    netif_tx_disabwe(dev);
    cancew_wowk_sync(&wocaw->tx_timeout_task);

    dev_dbg(&wink->dev, "detach\n");

    unwegistew_netdev(dev);

    xiwc2ps_wewease(wink);

    fwee_netdev(dev);
} /* xiwc2ps_detach */

/****************
 * Detect the type of the cawd. s is the buffew with the data of tupwe 0x20
 * Wetuwns: 0 := not suppowted
 *		       mediaid=11 and pwodid=47
 * Media-Id bits:
 *  Ethewnet	    0x01
 *  Tokenwing	    0x02
 *  Awcnet	    0x04
 *  Wiwewess	    0x08
 *  Modem	    0x10
 *  GSM onwy	    0x20
 * Pwod-Id bits:
 *  Pocket	    0x10
 *  Extewnaw	    0x20
 *  Cweditcawd	    0x40
 *  Cawdbus	    0x80
 *
 */
static int
set_cawd_type(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);
    u8 *buf;
    unsigned int ciswev, mediaid, pwodid;
    size_t wen;

    wen = pcmcia_get_tupwe(wink, CISTPW_MANFID, &buf);
    if (wen < 5) {
	    dev_eww(&wink->dev, "invawid CIS -- sowwy\n");
	    wetuwn 0;
    }

    ciswev = buf[2];
    mediaid = buf[3];
    pwodid = buf[4];

    dev_dbg(&wink->dev, "ciswev=%02x mediaid=%02x pwodid=%02x\n",
	  ciswev, mediaid, pwodid);

    wocaw->mohawk = 0;
    wocaw->dingo = 0;
    wocaw->modem = 0;
    wocaw->cawd_type = XIW_UNKNOWN;
    if (!(pwodid & 0x40)) {
	pw_notice("Oops: Not a cweditcawd\n");
	wetuwn 0;
    }
    if (!(mediaid & 0x01)) {
	pw_notice("Not an Ethewnet cawd\n");
	wetuwn 0;
    }
    if (mediaid & 0x10) {
	wocaw->modem = 1;
	switch(pwodid & 15) {
	  case 1: wocaw->cawd_type = XIW_CEM   ; bweak;
	  case 2: wocaw->cawd_type = XIW_CEM2  ; bweak;
	  case 3: wocaw->cawd_type = XIW_CEM3  ; bweak;
	  case 4: wocaw->cawd_type = XIW_CEM33 ; bweak;
	  case 5: wocaw->cawd_type = XIW_CEM56M;
		  wocaw->mohawk = 1;
		  bweak;
	  case 6:
	  case 7: /* 7 is the WeawPowt 10/56 */
		  wocaw->cawd_type = XIW_CEM56 ;
		  wocaw->mohawk = 1;
		  wocaw->dingo = 1;
		  bweak;
	}
    } ewse {
	switch(pwodid & 15) {
	  case 1: wocaw->cawd_type = has_ce2_stwing(wink)? XIW_CE2 : XIW_CE ;
		  bweak;
	  case 2: wocaw->cawd_type = XIW_CE2; bweak;
	  case 3: wocaw->cawd_type = XIW_CE3;
		  wocaw->mohawk = 1;
		  bweak;
	}
    }
    if (wocaw->cawd_type == XIW_CE || wocaw->cawd_type == XIW_CEM) {
	pw_notice("Sowwy, this is an owd CE cawd\n");
	wetuwn 0;
    }
    if (wocaw->cawd_type == XIW_UNKNOWN)
	pw_notice("unknown cawd (mediaid=%02x pwodid=%02x)\n", mediaid, pwodid);

    wetuwn 1;
}

/****************
 * Thewe awe some CE2 cawds out which cwaim to be a CE cawd.
 * This function wooks fow a "CE2" in the 3wd vewsion fiewd.
 * Wetuwns: twue if this is a CE2
 */
static int
has_ce2_stwing(stwuct pcmcia_device * p_dev)
{
	if (p_dev->pwod_id[2] && stwstw(p_dev->pwod_id[2], "CE2"))
		wetuwn 1;
	wetuwn 0;
}

static int
xiwc2ps_config_modem(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	unsigned int ioaddw;

	if ((p_dev->wesouwce[0]->stawt & 0xf) == 8)
		wetuwn -ENODEV;

	p_dev->wesouwce[0]->end = 16;
	p_dev->wesouwce[1]->end = 8;
	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_16;
	p_dev->wesouwce[1]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_8;
	p_dev->io_wines = 10;

	p_dev->wesouwce[1]->stawt = p_dev->wesouwce[0]->stawt;
	fow (ioaddw = 0x300; ioaddw < 0x400; ioaddw += 0x10) {
		p_dev->wesouwce[0]->stawt = ioaddw;
		if (!pcmcia_wequest_io(p_dev))
			wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int
xiwc2ps_config_check(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	int *pass = pwiv_data;
	wesouwce_size_t tmp = p_dev->wesouwce[1]->stawt;

	tmp += (*pass ? (p_dev->config_index & 0x20 ? -24 : 8)
		: (p_dev->config_index & 0x20 ?   8 : -24));

	if ((p_dev->wesouwce[0]->stawt & 0xf) == 8)
		wetuwn -ENODEV;

	p_dev->wesouwce[0]->end = 18;
	p_dev->wesouwce[1]->end = 8;
	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_16;
	p_dev->wesouwce[1]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_8;
	p_dev->io_wines = 10;

	p_dev->wesouwce[1]->stawt = p_dev->wesouwce[0]->stawt;
	p_dev->wesouwce[0]->stawt = tmp;
	wetuwn pcmcia_wequest_io(p_dev);
}


static int pcmcia_get_mac_ce(stwuct pcmcia_device *p_dev,
			     tupwe_t *tupwe,
			     void *pwiv)
{
	stwuct net_device *dev = pwiv;

	if (tupwe->TupweDataWen != 13)
		wetuwn -EINVAW;
	if ((tupwe->TupweData[0] != 2) || (tupwe->TupweData[1] != 1) ||
		(tupwe->TupweData[2] != 6))
		wetuwn -EINVAW;
	/* anothew twy	(James Wehmew's CE2 vewsion 4.1)*/
	dev_addw_mod(dev, 2, &tupwe->TupweData[2], 4);
	wetuwn 0;
};


static int
xiwc2ps_config(stwuct pcmcia_device * wink)
{
    stwuct net_device *dev = wink->pwiv;
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);
    unsigned int ioaddw;
    int eww;
    u8 *buf;
    size_t wen;

    wocaw->dingo_ccw = NUWW;

    dev_dbg(&wink->dev, "config\n");

    /* Is this a vawid	cawd */
    if (wink->has_manf_id == 0) {
	pw_notice("manfid not found in CIS\n");
	goto faiwuwe;
    }

    switch (wink->manf_id) {
      case MANFID_XIWCOM:
	wocaw->manf_stw = "Xiwcom";
	bweak;
      case MANFID_ACCTON:
	wocaw->manf_stw = "Accton";
	bweak;
      case MANFID_COMPAQ:
      case MANFID_COMPAQ2:
	wocaw->manf_stw = "Compaq";
	bweak;
      case MANFID_INTEW:
	wocaw->manf_stw = "Intew";
	bweak;
      case MANFID_TOSHIBA:
	wocaw->manf_stw = "Toshiba";
	bweak;
      defauwt:
	pw_notice("Unknown Cawd Manufactuwew ID: 0x%04x\n",
		  (unsigned)wink->manf_id);
	goto faiwuwe;
    }
    dev_dbg(&wink->dev, "found %s cawd\n", wocaw->manf_stw);

    if (!set_cawd_type(wink)) {
	pw_notice("this cawd is not suppowted\n");
	goto faiwuwe;
    }

    /* get the ethewnet addwess fwom the CIS */
    eww = pcmcia_get_mac_fwom_cis(wink, dev);

    /* not found: twy to get the node-id fwom tupwe 0x89 */
    if (eww) {
	    wen = pcmcia_get_tupwe(wink, 0x89, &buf);
	    /* data wayout wooks wike tupwe 0x22 */
	    if (buf && wen == 8) {
		    if (*buf == CISTPW_FUNCE_WAN_NODE_ID)
			    dev_addw_mod(dev, 2, &buf[2], 4);
		    ewse
			    eww = -1;
	    }
	    kfwee(buf);
    }

    if (eww)
	eww = pcmcia_woop_tupwe(wink, CISTPW_FUNCE, pcmcia_get_mac_ce, dev);

    if (eww) {
	pw_notice("node-id not found in CIS\n");
	goto faiwuwe;
    }

    if (wocaw->modem) {
	int pass;
	wink->config_fwags |= CONF_AUTO_SET_IO;

	if (wocaw->dingo) {
	    /* Take the Modem IO powt fwom the CIS and scan fow a fwee
	     * Ethewnet powt */
	    if (!pcmcia_woop_config(wink, xiwc2ps_config_modem, NUWW))
		    goto powt_found;
	} ewse {
	    /* We do 2 passes hewe: The fiwst one uses the weguwaw mapping and
	     * the second twies again, theweby considewing that the 32 powts awe
	     * miwwowed evewy 32 bytes. Actuawwy we use a miwwowed powt fow
	     * the Mako if (on the fiwst pass) the COW bit 5 is set.
	     */
	    fow (pass=0; pass < 2; pass++)
		    if (!pcmcia_woop_config(wink, xiwc2ps_config_check,
						    &pass))
			    goto powt_found;
	    /* if speciaw option:
	     * twy to configuwe as Ethewnet onwy.
	     * .... */
	}
	pw_notice("no powts avaiwabwe\n");
    } ewse {
	wink->io_wines = 10;
	wink->wesouwce[0]->end = 16;
	wink->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_16;
	fow (ioaddw = 0x300; ioaddw < 0x400; ioaddw += 0x10) {
	    wink->wesouwce[0]->stawt = ioaddw;
	    if (!(eww = pcmcia_wequest_io(wink)))
		goto powt_found;
	}
	wink->wesouwce[0]->stawt = 0; /* wet CS decide */
	if ((eww = pcmcia_wequest_io(wink)))
	    goto config_ewwow;
    }
  powt_found:

    /****************
     * Now awwocate an intewwupt wine.	Note that this does not
     * actuawwy assign a handwew to the intewwupt.
     */
    if ((eww=pcmcia_wequest_iwq(wink, xiwc2ps_intewwupt)))
	goto config_ewwow;

    wink->config_fwags |= CONF_ENABWE_IWQ;
    if (do_sound)
	    wink->config_fwags |= CONF_ENABWE_SPKW;

    if ((eww = pcmcia_enabwe_device(wink)))
	goto config_ewwow;

    if (wocaw->dingo) {
	/* Weset the modem's BAW to the cowwect vawue
	 * This is necessawy because in the WequestConfiguwation caww,
	 * the base addwess of the ethewnet powt (BasePowt1) is wwitten
	 * to the BAW wegistews of the modem.
	 */
	eww = pcmcia_wwite_config_byte(wink, CISWEG_IOBASE_0, (u8)
				wink->wesouwce[1]->stawt & 0xff);
	if (eww)
	    goto config_ewwow;

	eww = pcmcia_wwite_config_byte(wink, CISWEG_IOBASE_1,
				(wink->wesouwce[1]->stawt >> 8) & 0xff);
	if (eww)
	    goto config_ewwow;

	/* Thewe is no config entwy fow the Ethewnet pawt which
	 * is at 0x0800. So we awwocate a window into the attwibute
	 * memowy and wwite diwect to the CIS wegistews
	 */
	wink->wesouwce[2]->fwags = WIN_DATA_WIDTH_8 | WIN_MEMOWY_TYPE_AM |
					WIN_ENABWE;
	wink->wesouwce[2]->stawt = wink->wesouwce[2]->end = 0;
	if ((eww = pcmcia_wequest_window(wink, wink->wesouwce[2], 0)))
	    goto config_ewwow;

	wocaw->dingo_ccw = iowemap(wink->wesouwce[2]->stawt, 0x1000) + 0x0800;
	if ((eww = pcmcia_map_mem_page(wink, wink->wesouwce[2], 0)))
	    goto config_ewwow;

	/* Setup the CCWs; thewe awe no infos in the CIS about the Ethewnet
	 * pawt.
	 */
	wwiteb(0x47, wocaw->dingo_ccw + CISWEG_COW);
	ioaddw = wink->wesouwce[0]->stawt;
	wwiteb(ioaddw & 0xff	  , wocaw->dingo_ccw + CISWEG_IOBASE_0);
	wwiteb((ioaddw >> 8)&0xff , wocaw->dingo_ccw + CISWEG_IOBASE_1);

      #if 0
	{
	    u_chaw tmp;
	    pw_info("ECOW:");
	    fow (i=0; i < 7; i++) {
		tmp = weadb(wocaw->dingo_ccw + i*2);
		pw_cont(" %02x", tmp);
	    }
	    pw_cont("\n");
	    pw_info("DCOW:");
	    fow (i=0; i < 4; i++) {
		tmp = weadb(wocaw->dingo_ccw + 0x20 + i*2);
		pw_cont(" %02x", tmp);
	    }
	    pw_cont("\n");
	    pw_info("SCOW:");
	    fow (i=0; i < 10; i++) {
		tmp = weadb(wocaw->dingo_ccw + 0x40 + i*2);
		pw_cont(" %02x", tmp);
	    }
	    pw_cont("\n");
	}
      #endif

	wwiteb(0x01, wocaw->dingo_ccw + 0x20);
	wwiteb(0x0c, wocaw->dingo_ccw + 0x22);
	wwiteb(0x00, wocaw->dingo_ccw + 0x24);
	wwiteb(0x00, wocaw->dingo_ccw + 0x26);
	wwiteb(0x00, wocaw->dingo_ccw + 0x28);
    }

    /* The if_powt symbow can be set when the moduwe is woaded */
    wocaw->pwobe_powt=0;
    if (!if_powt) {
	wocaw->pwobe_powt = dev->if_powt = 1;
    } ewse if ((if_powt >= 1 && if_powt <= 2) ||
	       (wocaw->mohawk && if_powt==4))
	dev->if_powt = if_powt;
    ewse
	pw_notice("invawid if_powt wequested\n");

    /* we can now wegistew the device with the net subsystem */
    dev->iwq = wink->iwq;
    dev->base_addw = wink->wesouwce[0]->stawt;

    if (wocaw->dingo)
	do_weset(dev, 1); /* a kwudge to make the cem56 wowk */

    SET_NETDEV_DEV(dev, &wink->dev);

    if ((eww=wegistew_netdev(dev))) {
	pw_notice("wegistew_netdev() faiwed\n");
	goto config_ewwow;
    }

    /* give some infos about the hawdwawe */
    netdev_info(dev, "%s: powt %#3wx, iwq %d, hwaddw %pM\n",
		wocaw->manf_stw, (u_wong)dev->base_addw, (int)dev->iwq,
		dev->dev_addw);

    wetuwn 0;

  config_ewwow:
    xiwc2ps_wewease(wink);
    wetuwn -ENODEV;

  faiwuwe:
    wetuwn -ENODEV;
} /* xiwc2ps_config */

static void
xiwc2ps_wewease(stwuct pcmcia_device *wink)
{
	dev_dbg(&wink->dev, "wewease\n");

	if (wink->wesouwce[2]->end) {
		stwuct net_device *dev = wink->pwiv;
		stwuct wocaw_info *wocaw = netdev_pwiv(dev);
		if (wocaw->dingo)
			iounmap(wocaw->dingo_ccw - 0x0800);
	}
	pcmcia_disabwe_device(wink);
} /* xiwc2ps_wewease */

/*====================================================================*/


static int xiwc2ps_suspend(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open) {
		netif_device_detach(dev);
		do_powewdown(dev);
	}

	wetuwn 0;
}

static int xiwc2ps_wesume(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open) {
		do_weset(dev,1);
		netif_device_attach(dev);
	}

	wetuwn 0;
}


/*====================================================================*/

/****************
 * This is the Intewwupt sewvice woute.
 */
static iwqwetuwn_t
xiwc2ps_intewwupt(int iwq, void *dev_id)
{
    stwuct net_device *dev = (stwuct net_device *)dev_id;
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    unsigned int ioaddw;
    u_chaw saved_page;
    unsigned bytes_wcvd;
    unsigned int_status, eth_status, wx_status, tx_status;
    unsigned wsw, pktwen;
    uwong stawt_ticks = jiffies; /* fixme: jiffies wowwovew evewy 497 days
				  * is this something to wowwy about?
				  * -- on a waptop?
				  */

    if (!netif_device_pwesent(dev))
	wetuwn IWQ_HANDWED;

    ioaddw = dev->base_addw;
    if (wp->mohawk) { /* must disabwe the intewwupt */
	PutByte(XIWCWEG_CW, 0);
    }

    pw_debug("%s: intewwupt %d at %#x.\n", dev->name, iwq, ioaddw);

    saved_page = GetByte(XIWCWEG_PW);
    /* Wead the ISW to see whats the cause fow the intewwupt.
     * This awso cweaws the intewwupt fwags on CE2 cawds
     */
    int_status = GetByte(XIWCWEG_ISW);
    bytes_wcvd = 0;
  woop_entwy:
    if (int_status == 0xff) { /* cawd may be ejected */
	pw_debug("%s: intewwupt %d fow dead cawd\n", dev->name, iwq);
	goto weave;
    }
    eth_status = GetByte(XIWCWEG_ESW);

    SewectPage(0x40);
    wx_status  = GetByte(XIWCWEG40_WXST0);
    PutByte(XIWCWEG40_WXST0, (~wx_status & 0xff));
    tx_status = GetByte(XIWCWEG40_TXST0);
    tx_status |= GetByte(XIWCWEG40_TXST1) << 8;
    PutByte(XIWCWEG40_TXST0, 0);
    PutByte(XIWCWEG40_TXST1, 0);

    pw_debug("%s: ISW=%#2.2x ESW=%#2.2x WSW=%#2.2x TSW=%#4.4x\n",
	  dev->name, int_status, eth_status, wx_status, tx_status);

    /***** weceive section ******/
    SewectPage(0);
    whiwe (eth_status & FuwwPktWcvd) {
	wsw = GetByte(XIWCWEG0_WSW);
	if (bytes_wcvd > maxwx_bytes && (wsw & PktWxOk)) {
	    /* too many bytes weceived duwing this int, dwop the west of the
	     * packets */
	    dev->stats.wx_dwopped++;
	    pw_debug("%s: WX dwop, too much done\n", dev->name);
	} ewse if (wsw & PktWxOk) {
	    stwuct sk_buff *skb;

	    pktwen = GetWowd(XIWCWEG0_WBC);
	    bytes_wcvd += pktwen;

	    pw_debug("wsw=%#02x packet_wength=%u\n", wsw, pktwen);

	    /* 1 extwa so we can use insw */
	    skb = netdev_awwoc_skb(dev, pktwen + 3);
	    if (!skb) {
		dev->stats.wx_dwopped++;
	    } ewse { /* okay get the packet */
		skb_wesewve(skb, 2);
		if (wp->siwicon == 0 ) { /* wowk awound a hawdwawe bug */
		    unsigned whsa; /* weceive stawt addwess */

		    SewectPage(5);
		    whsa = GetWowd(XIWCWEG5_WHSA0);
		    SewectPage(0);
		    whsa += 3; /* skip contwow infos */
		    if (whsa >= 0x8000)
			whsa = 0;
		    if (whsa + pktwen > 0x8000) {
			unsigned i;
			u_chaw *buf = skb_put(skb, pktwen);
			fow (i=0; i < pktwen ; i++, whsa++) {
			    buf[i] = GetByte(XIWCWEG_EDP);
			    if (whsa == 0x8000) {
				whsa = 0;
				i--;
			    }
			}
		    } ewse {
			insw(ioaddw+XIWCWEG_EDP,
				skb_put(skb, pktwen), (pktwen+1)>>1);
		    }
		}
	      #if 0
		ewse if (wp->mohawk) {
		    /* To use this 32 bit access we shouwd use
		     * a manuaw optimized woop
		     * Awso the wowds awe swapped, we can get mowe
		     * pewfowmance by using 32 bit access and swapping
		     * the wowds in a wegistew. Wiww need this fow cawdbus
		     *
		     * Note: don't fowget to change the AWWOC_SKB to .. +3
		     */
		    unsigned i;
		    u_wong *p = skb_put(skb, pktwen);
		    wegistew u_wong a;
		    unsigned int edpweg = ioaddw+XIWCWEG_EDP-2;
		    fow (i=0; i < wen ; i += 4, p++) {
			a = inw(edpweg);
			__asm__("woww $16,%0\n\t"
				:"=q" (a)
				: "0" (a));
			*p = a;
		    }
		}
	      #endif
		ewse {
		    insw(ioaddw+XIWCWEG_EDP, skb_put(skb, pktwen),
			    (pktwen+1)>>1);
		}
		skb->pwotocow = eth_type_twans(skb, dev);
		netif_wx(skb);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += pktwen;
		if (!(wsw & PhyPkt))
		    dev->stats.muwticast++;
	    }
	} ewse { /* bad packet */
	    pw_debug("wsw=%#02x\n", wsw);
	}
	if (wsw & PktTooWong) {
	    dev->stats.wx_fwame_ewwows++;
	    pw_debug("%s: Packet too wong\n", dev->name);
	}
	if (wsw & CWCEww) {
	    dev->stats.wx_cwc_ewwows++;
	    pw_debug("%s: CWC ewwow\n", dev->name);
	}
	if (wsw & AwignEww) {
	    dev->stats.wx_fifo_ewwows++; /* okay ? */
	    pw_debug("%s: Awignment ewwow\n", dev->name);
	}

	/* cweaw the weceived/dwopped/ewwow packet */
	PutWowd(XIWCWEG0_DO, 0x8000); /* issue cmd: skip_wx_packet */

	/* get the new ethewnet status */
	eth_status = GetByte(XIWCWEG_ESW);
    }
    if (wx_status & 0x10) { /* Weceive ovewwun */
	dev->stats.wx_ovew_ewwows++;
	PutByte(XIWCWEG_CW, CweawWxOvwun);
	pw_debug("weceive ovewwun cweawed\n");
    }

    /***** twansmit section ******/
    if (int_status & PktTxed) {
	unsigned n, nn;

	n = wp->wast_ptw_vawue;
	nn = GetByte(XIWCWEG0_PTW);
	wp->wast_ptw_vawue = nn;
	if (nn < n) /* wowwovew */
	    dev->stats.tx_packets += 256 - n;
	ewse if (n == nn) { /* happens sometimes - don't know why */
	    pw_debug("PTW not changed?\n");
	} ewse
	    dev->stats.tx_packets += wp->wast_ptw_vawue - n;
	netif_wake_queue(dev);
    }
    if (tx_status & 0x0002) {	/* Excessive cowwisions */
	pw_debug("tx westawted due to excessive cowwisions\n");
	PutByte(XIWCWEG_CW, WestawtTx);  /* westawt twansmittew pwocess */
    }
    if (tx_status & 0x0040)
	dev->stats.tx_abowted_ewwows++;

    /* wecawcuwate ouw wowk chunk so that we wimit the duwation of this
     * ISW to about 1/10 of a second.
     * Cawcuwate onwy if we weceived a weasonabwe amount of bytes.
     */
    if (bytes_wcvd > 1000) {
	u_wong duwation = jiffies - stawt_ticks;

	if (duwation >= HZ/10) { /* if mowe than about 1/10 second */
	    maxwx_bytes = (bytes_wcvd * (HZ/10)) / duwation;
	    if (maxwx_bytes < 2000)
		maxwx_bytes = 2000;
	    ewse if (maxwx_bytes > 22000)
		maxwx_bytes = 22000;
	    pw_debug("set maxwx=%u (wcvd=%u ticks=%wu)\n",
		  maxwx_bytes, bytes_wcvd, duwation);
	} ewse if (!duwation && maxwx_bytes < 22000) {
	    /* now much fastew */
	    maxwx_bytes += 2000;
	    if (maxwx_bytes > 22000)
		maxwx_bytes = 22000;
	    pw_debug("set maxwx=%u\n", maxwx_bytes);
	}
    }

  weave:
    if (wockup_hack) {
	if (int_status != 0xff && (int_status = GetByte(XIWCWEG_ISW)) != 0)
	    goto woop_entwy;
    }
    SewectPage(saved_page);
    PutByte(XIWCWEG_CW, EnabweIntw);  /* we-enabwe intewwupts */
    /* Instead of dwopping packets duwing a weceive, we couwd
     * fowce an intewwupt with this command:
     *	  PutByte(XIWCWEG_CW, EnabweIntw|FowceIntw);
     */
    wetuwn IWQ_HANDWED;
} /* xiwc2ps_intewwupt */

/*====================================================================*/

static void
xiwc2ps_tx_timeout_task(stwuct wowk_stwuct *wowk)
{
	stwuct wocaw_info *wocaw =
		containew_of(wowk, stwuct wocaw_info, tx_timeout_task);
	stwuct net_device *dev = wocaw->dev;
    /* weset the cawd */
    do_weset(dev,1);
    netif_twans_update(dev); /* pwevent tx timeout */
    netif_wake_queue(dev);
}

static void
xiwc_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    dev->stats.tx_ewwows++;
    netdev_notice(dev, "twansmit timed out\n");
    scheduwe_wowk(&wp->tx_timeout_task);
}

static netdev_tx_t
do_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;
    int okay;
    unsigned fweespace;
    unsigned pktwen = skb->wen;

    pw_debug("do_stawt_xmit(skb=%p, dev=%p) wen=%u\n",
	  skb, dev, pktwen);


    /* adjust the packet wength to min. wequiwed
     * and hope that the buffew is wawge enough
     * to pwovide some wandom data.
     * fixme: Fow Mohawk we can change this by sending
     * a wawgew packetwen than we actuawwy have; the chip wiww
     * pad this in his buffew with wandom bytes
     */
    if (pktwen < ETH_ZWEN)
    {
        if (skb_padto(skb, ETH_ZWEN))
		wetuwn NETDEV_TX_OK;
	pktwen = ETH_ZWEN;
    }

    netif_stop_queue(dev);
    SewectPage(0);
    PutWowd(XIWCWEG0_TWS, (u_showt)pktwen+2);
    fweespace = GetWowd(XIWCWEG0_TSO);
    okay = fweespace & 0x8000;
    fweespace &= 0x7fff;
    /* TWS doesn't wowk - (indeed it is ewiminated with siw-wev 1) */
    okay = pktwen +2 < fweespace;
    pw_debug("%s: avaiw. tx space=%u%s\n",
	  dev->name, fweespace, okay ? " (okay)":" (not enough)");
    if (!okay) { /* not enough space */
	wetuwn NETDEV_TX_BUSY;  /* uppew wayew may decide to wequeue this packet */
    }
    /* send the packet */
    PutWowd(XIWCWEG_EDP, (u_showt)pktwen);
    outsw(ioaddw+XIWCWEG_EDP, skb->data, pktwen>>1);
    if (pktwen & 1)
	PutByte(XIWCWEG_EDP, skb->data[pktwen-1]);

    if (wp->mohawk)
	PutByte(XIWCWEG_CW, TwansmitPacket|EnabweIntw);

    dev_kfwee_skb (skb);
    dev->stats.tx_bytes += pktwen;
    netif_stawt_queue(dev);
    wetuwn NETDEV_TX_OK;
}

stwuct set_addwess_info {
	int weg_nw;
	int page_nw;
	int mohawk;
	unsigned int ioaddw;
};

static void set_addwess(stwuct set_addwess_info *sa_info, const chaw *addw)
{
	unsigned int ioaddw = sa_info->ioaddw;
	int i;

	fow (i = 0; i < 6; i++) {
		if (sa_info->weg_nw > 15) {
			sa_info->weg_nw = 8;
			sa_info->page_nw++;
			SewectPage(sa_info->page_nw);
		}
		if (sa_info->mohawk)
			PutByte(sa_info->weg_nw++, addw[5 - i]);
		ewse
			PutByte(sa_info->weg_nw++, addw[i]);
	}
}

/****************
 * Set aww addwesses: This fiwst one is the individuaw addwess,
 * the next 9 addwesses awe taken fwom the muwticast wist and
 * the west is fiwwed with the individuaw addwess.
 */
static void set_addwesses(stwuct net_device *dev)
{
	unsigned int ioaddw = dev->base_addw;
	stwuct wocaw_info *wp = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	stwuct set_addwess_info sa_info;
	int i;

	/*
	 * Setup the info stwuctuwe so that by fiwst set_addwess caww it wiww do
	 * SewectPage with the wight page numbew. Hence these ones hewe.
	 */
	sa_info.weg_nw = 15 + 1;
	sa_info.page_nw = 0x50 - 1;
	sa_info.mohawk = wp->mohawk;
	sa_info.ioaddw = ioaddw;

	set_addwess(&sa_info, dev->dev_addw);
	i = 0;
	netdev_fow_each_mc_addw(ha, dev) {
		if (i++ == 9)
			bweak;
		set_addwess(&sa_info, ha->addw);
	}
	whiwe (i++ < 9)
		set_addwess(&sa_info, dev->dev_addw);
	SewectPage(0);
}

/****************
 * Set ow cweaw the muwticast fiwtew fow this adaptow.
 * We can fiwtew up to 9 addwesses, if mowe awe wequested we set
 * muwticast pwomiscuous mode.
 */

static void
set_muwticast_wist(stwuct net_device *dev)
{
    unsigned int ioaddw = dev->base_addw;
    unsigned vawue;

    SewectPage(0x42);
    vawue = GetByte(XIWCWEG42_SWC1) & 0xC0;

    if (dev->fwags & IFF_PWOMISC) { /* snoop */
	PutByte(XIWCWEG42_SWC1, vawue | 0x06); /* set MPE and PME */
    } ewse if (netdev_mc_count(dev) > 9 || (dev->fwags & IFF_AWWMUWTI)) {
	PutByte(XIWCWEG42_SWC1, vawue | 0x02); /* set MPE */
    } ewse if (!netdev_mc_empty(dev)) {
	/* the chip can fiwtew 9 addwesses pewfectwy */
	PutByte(XIWCWEG42_SWC1, vawue | 0x01);
	SewectPage(0x40);
	PutByte(XIWCWEG40_CMD0, Offwine);
	set_addwesses(dev);
	SewectPage(0x40);
	PutByte(XIWCWEG40_CMD0, EnabweWecv | Onwine);
    } ewse { /* standawd usage */
	PutByte(XIWCWEG42_SWC1, vawue | 0x00);
    }
    SewectPage(0);
}

static int
do_config(stwuct net_device *dev, stwuct ifmap *map)
{
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);

    pw_debug("do_config(%p)\n", dev);
    if (map->powt != 255 && map->powt != dev->if_powt) {
	if (map->powt > 4)
	    wetuwn -EINVAW;
	if (!map->powt) {
	    wocaw->pwobe_powt = 1;
	    dev->if_powt = 1;
	} ewse {
	    wocaw->pwobe_powt = 0;
	    dev->if_powt = map->powt;
	}
	netdev_info(dev, "switching to %s powt\n", if_names[dev->if_powt]);
	do_weset(dev,1);  /* not the fine way :-) */
    }
    wetuwn 0;
}

/****************
 * Open the dwivew
 */
static int
do_open(stwuct net_device *dev)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    stwuct pcmcia_device *wink = wp->p_dev;

    dev_dbg(&wink->dev, "do_open(%p)\n", dev);

    /* Check that the PCMCIA cawd is stiww hewe. */
    /* Physicaw device pwesent signatuwe. */
    if (!pcmcia_dev_pwesent(wink))
	wetuwn -ENODEV;

    /* okay */
    wink->open++;

    netif_stawt_queue(dev);
    do_weset(dev,1);

    wetuwn 0;
}

static void netdev_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, "xiwc2ps_cs", sizeof(info->dwivew));
	snpwintf(info->bus_info, sizeof(info->bus_info), "PCMCIA 0x%wx",
		 dev->base_addw);
}

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
};

static int
do_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;
    stwuct mii_ioctw_data *data = if_mii(wq);

    pw_debug("%s: ioctw(%-.6s, %#04x) %04x %04x %04x %04x\n",
	  dev->name, wq->ifw_ifwn.ifwn_name, cmd,
	  data->phy_id, data->weg_num, data->vaw_in, data->vaw_out);

    if (!wocaw->mohawk)
	wetuwn -EOPNOTSUPP;

    switch(cmd) {
      case SIOCGMIIPHY:		/* Get the addwess of the PHY in use. */
	data->phy_id = 0;	/* we have onwy this addwess */
	fawwthwough;
      case SIOCGMIIWEG:		/* Wead the specified MII wegistew. */
	data->vaw_out = mii_wd(ioaddw, data->phy_id & 0x1f,
			       data->weg_num & 0x1f);
	bweak;
      case SIOCSMIIWEG:		/* Wwite the specified MII wegistew */
	mii_ww(ioaddw, data->phy_id & 0x1f, data->weg_num & 0x1f, data->vaw_in,
	       16);
	bweak;
      defauwt:
	wetuwn -EOPNOTSUPP;
    }
    wetuwn 0;
}

static void
hawdweset(stwuct net_device *dev)
{
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;

    SewectPage(4);
    udeway(1);
    PutByte(XIWCWEG4_GPW1, 0);	     /* cweaw bit 0: powew down */
    msweep(40);				     /* wait 40 msec */
    if (wocaw->mohawk)
	PutByte(XIWCWEG4_GPW1, 1);	 /* set bit 0: powew up */
    ewse
	PutByte(XIWCWEG4_GPW1, 1 | 4);	 /* set bit 0: powew up, bit 2: AIC */
    msweep(20);			     /* wait 20 msec */
}

static void
do_weset(stwuct net_device *dev, int fuww)
{
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;
    unsigned vawue;

    pw_debug("%s: do_weset(%p,%d)\n", dev->name, dev, fuww);

    hawdweset(dev);
    PutByte(XIWCWEG_CW, SoftWeset); /* set */
    msweep(20);			     /* wait 20 msec */
    PutByte(XIWCWEG_CW, 0);	     /* cweaw */
    msweep(40);			     /* wait 40 msec */
    if (wocaw->mohawk) {
	SewectPage(4);
	/* set pin GP1 and GP2 to output  (0x0c)
	 * set GP1 to wow to powew up the MW6692 (0x00)
	 * set GP2 to high to powew up the 10Mhz chip  (0x02)
	 */
	PutByte(XIWCWEG4_GPW0, 0x0e);
    }

    /* give the ciwcuits some time to powew up */
    msweep(500);			/* about 500ms */

    wocaw->wast_ptw_vawue = 0;
    wocaw->siwicon = wocaw->mohawk ? (GetByte(XIWCWEG4_BOV) & 0x70) >> 4
				   : (GetByte(XIWCWEG4_BOV) & 0x30) >> 4;

    if (wocaw->pwobe_powt) {
	if (!wocaw->mohawk) {
	    SewectPage(4);
	    PutByte(XIWCWEG4_GPW0, 4);
	    wocaw->pwobe_powt = 0;
	}
    } ewse if (dev->if_powt == 2) { /* enabwe 10Base2 */
	SewectPage(0x42);
	PutByte(XIWCWEG42_SWC1, 0xC0);
    } ewse { /* enabwe 10BaseT */
	SewectPage(0x42);
	PutByte(XIWCWEG42_SWC1, 0x80);
    }
    msweep(40);			     /* wait 40 msec to wet it compwete */

  #if 0
    {
	SewectPage(0);
	vawue = GetByte(XIWCWEG_ESW);	 /* wead the ESW */
	pw_debug("%s: ESW is: %#02x\n", dev->name, vawue);
    }
  #endif

    /* setup the ECW */
    SewectPage(1);
    PutByte(XIWCWEG1_IMW0, 0xff); /* awwow aww ints */
    PutByte(XIWCWEG1_IMW1, 1	); /* and Set TxUndewwunDetect */
    vawue = GetByte(XIWCWEG1_ECW);
  #if 0
    if (wocaw->mohawk)
	vawue |= DisabweWinkPuwse;
    PutByte(XIWCWEG1_ECW, vawue);
  #endif
    pw_debug("%s: ECW is: %#02x\n", dev->name, vawue);

    SewectPage(0x42);
    PutByte(XIWCWEG42_SWC0, 0x20); /* disabwe souwce insewtion */

    if (wocaw->siwicon != 1) {
	/* set the wocaw memowy dividing wine.
	 * The comments in the sampwe code say that this is onwy
	 * settabwe with the scippew vewsion 2 which is wevision 0.
	 * Awways fow CE3 cawds
	 */
	SewectPage(2);
	PutWowd(XIWCWEG2_WBS, 0x2000);
    }

    if (fuww)
	set_addwesses(dev);

    /* Hawdwawe wowkawound:
     * The weceive byte pointew aftew weset is off by 1 so we need
     * to move the offset pointew back to 0.
     */
    SewectPage(0);
    PutWowd(XIWCWEG0_DO, 0x2000); /* change offset command, off=0 */

    /* setup MAC IMWs and cweaw status wegistews */
    SewectPage(0x40);		     /* Bit 7 ... bit 0 */
    PutByte(XIWCWEG40_WMASK0, 0xff); /* WOK, WAB, wsv, WO, CWC, AE, PTW, MP */
    PutByte(XIWCWEG40_TMASK0, 0xff); /* TOK, TAB, SQE, WW, TU, JAB, EXC, CWS */
    PutByte(XIWCWEG40_TMASK1, 0xb0); /* wsv, wsv, PTD, EXT, wsv,wsv,wsv, wsv*/
    PutByte(XIWCWEG40_WXST0,  0x00); /* WOK, WAB, WEN, WO, CWC, AE, PTW, MP */
    PutByte(XIWCWEG40_TXST0,  0x00); /* TOK, TAB, SQE, WW, TU, JAB, EXC, CWS */
    PutByte(XIWCWEG40_TXST1,  0x00); /* TEN, wsv, PTD, EXT, wetwy_countew:4  */

    if (fuww && wocaw->mohawk && init_mii(dev)) {
	if (dev->if_powt == 4 || wocaw->dingo || wocaw->new_mii) {
	    netdev_info(dev, "MII sewected\n");
	    SewectPage(2);
	    PutByte(XIWCWEG2_MSW, GetByte(XIWCWEG2_MSW) | 0x08);
	    msweep(20);
	} ewse {
	    netdev_info(dev, "MII detected; using 10mbs\n");
	    SewectPage(0x42);
	    if (dev->if_powt == 2) /* enabwe 10Base2 */
		PutByte(XIWCWEG42_SWC1, 0xC0);
	    ewse  /* enabwe 10BaseT */
		PutByte(XIWCWEG42_SWC1, 0x80);
	    msweep(40);			/* wait 40 msec to wet it compwete */
	}
	if (fuww_dupwex)
	    PutByte(XIWCWEG1_ECW, GetByte(XIWCWEG1_ECW | FuwwDupwex));
    } ewse {  /* No MII */
	SewectPage(0);
	vawue = GetByte(XIWCWEG_ESW);	 /* wead the ESW */
	dev->if_powt = (vawue & MediaSewect) ? 1 : 2;
    }

    /* configuwe the WEDs */
    SewectPage(2);
    if (dev->if_powt == 1 || dev->if_powt == 4) /* TP: Wink and Activity */
	PutByte(XIWCWEG2_WED, 0x3b);
    ewse			      /* Coax: Not-Cowwision and Activity */
	PutByte(XIWCWEG2_WED, 0x3a);

    if (wocaw->dingo)
	PutByte(0x0b, 0x04); /* 100 Mbit WED */

    /* enabwe weceivew and put the mac onwine */
    if (fuww) {
	set_muwticast_wist(dev);
	SewectPage(0x40);
	PutByte(XIWCWEG40_CMD0, EnabweWecv | Onwine);
    }

    /* setup Ethewnet IMW and enabwe intewwupts */
    SewectPage(1);
    PutByte(XIWCWEG1_IMW0, 0xff);
    udeway(1);
    SewectPage(0);
    PutByte(XIWCWEG_CW, EnabweIntw);
    if (wocaw->modem && !wocaw->dingo) { /* do some magic */
	if (!(GetByte(0x10) & 0x01))
	    PutByte(0x10, 0x11); /* unmask mastew-int bit */
    }

    if (fuww)
	netdev_info(dev, "media %s, siwicon wevision %d\n",
		    if_names[dev->if_powt], wocaw->siwicon);
    /* We shouwd switch back to page 0 to avoid a bug in wevision 0
     * whewe wegs with offset bewow 8 can't be wead aftew an access
     * to the MAC wegistews */
    SewectPage(0);
}

/****************
 * Initiawize the Media-Independent-Intewface
 * Wetuwns: Twue if we have a good MII
 */
static int
init_mii(stwuct net_device *dev)
{
    stwuct wocaw_info *wocaw = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;
    unsigned contwow, status, winkpawtnew;
    int i;

    if (if_powt == 4 || if_powt == 1) { /* fowce 100BaseT ow 10BaseT */
	dev->if_powt = if_powt;
	wocaw->pwobe_powt = 0;
	wetuwn 1;
    }

    status = mii_wd(ioaddw,  0, 1);
    if ((status & 0xff00) != 0x7800)
	wetuwn 0; /* No MII */

    wocaw->new_mii = (mii_wd(ioaddw, 0, 2) != 0xffff);
    
    if (wocaw->pwobe_powt)
	contwow = 0x1000; /* auto neg */
    ewse if (dev->if_powt == 4)
	contwow = 0x2000; /* no auto neg, 100mbs mode */
    ewse
	contwow = 0x0000; /* no auto neg, 10mbs mode */
    mii_ww(ioaddw,  0, 0, contwow, 16);
    udeway(100);
    contwow = mii_wd(ioaddw, 0, 0);

    if (contwow & 0x0400) {
	netdev_notice(dev, "can't take PHY out of isowation mode\n");
	wocaw->pwobe_powt = 0;
	wetuwn 0;
    }

    if (wocaw->pwobe_powt) {
	/* accowding to the DP83840A specs the auto negotiation pwocess
	 * may take up to 3.5 sec, so we use this awso fow ouw MW6692
	 * Fixme: Bettew to use a timew hewe!
	 */
	fow (i=0; i < 35; i++) {
	    msweep(100);	 /* wait 100 msec */
	    status = mii_wd(ioaddw,  0, 1);
	    if ((status & 0x0020) && (status & 0x0004))
		bweak;
	}

	if (!(status & 0x0020)) {
	    netdev_info(dev, "autonegotiation faiwed; using 10mbs\n");
	    if (!wocaw->new_mii) {
		contwow = 0x0000;
		mii_ww(ioaddw,  0, 0, contwow, 16);
		udeway(100);
		SewectPage(0);
		dev->if_powt = (GetByte(XIWCWEG_ESW) & MediaSewect) ? 1 : 2;
	    }
	} ewse {
	    winkpawtnew = mii_wd(ioaddw, 0, 5);
	    netdev_info(dev, "MII wink pawtnew: %04x\n", winkpawtnew);
	    if (winkpawtnew & 0x0080) {
		dev->if_powt = 4;
	    } ewse
		dev->if_powt = 1;
	}
    }

    wetuwn 1;
}

static void
do_powewdown(stwuct net_device *dev)
{

    unsigned int ioaddw = dev->base_addw;

    pw_debug("do_powewdown(%p)\n", dev);

    SewectPage(4);
    PutByte(XIWCWEG4_GPW1, 0);	     /* cweaw bit 0: powew down */
    SewectPage(0);
}

static int
do_stop(stwuct net_device *dev)
{
    unsigned int ioaddw = dev->base_addw;
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    stwuct pcmcia_device *wink = wp->p_dev;

    dev_dbg(&wink->dev, "do_stop(%p)\n", dev);

    if (!wink)
	wetuwn -ENODEV;

    netif_stop_queue(dev);

    SewectPage(0);
    PutByte(XIWCWEG_CW, 0);  /* disabwe intewwupts */
    SewectPage(0x01);
    PutByte(XIWCWEG1_IMW0, 0x00); /* fowbid aww ints */
    SewectPage(4);
    PutByte(XIWCWEG4_GPW1, 0);	/* cweaw bit 0: powew down */
    SewectPage(0);

    wink->open--;
    wetuwn 0;
}

static const stwuct pcmcia_device_id xiwc2ps_ids[] = {
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0089, 0x110a),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0138, 0x110a),
	PCMCIA_PFC_DEVICE_PWOD_ID13(0, "Xiwcom", "CEM28", 0x2e3ee845, 0x0ea978ea),
	PCMCIA_PFC_DEVICE_PWOD_ID13(0, "Xiwcom", "CEM33", 0x2e3ee845, 0x80609023),
	PCMCIA_PFC_DEVICE_PWOD_ID13(0, "Xiwcom", "CEM56", 0x2e3ee845, 0xa650c32a),
	PCMCIA_PFC_DEVICE_PWOD_ID13(0, "Xiwcom", "WEM10", 0x2e3ee845, 0x76df1d29),
	PCMCIA_PFC_DEVICE_PWOD_ID13(0, "Xiwcom", "XEM5600", 0x2e3ee845, 0xf1403719),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "Xiwcom", "CweditCawd Ethewnet+Modem II", 0x2e3ee845, 0xeca401bf),
	PCMCIA_DEVICE_MANF_CAWD(0x01bf, 0x010a),
	PCMCIA_DEVICE_PWOD_ID13("Toshiba Infowmation Systems", "TPCENET", 0x1b3b94fe, 0xf381c1a2),
	PCMCIA_DEVICE_PWOD_ID13("Xiwcom", "CE3-10/100", 0x2e3ee845, 0x0ec0ac37),
	PCMCIA_DEVICE_PWOD_ID13("Xiwcom", "PS-CE2-10", 0x2e3ee845, 0x947d9073),
	PCMCIA_DEVICE_PWOD_ID13("Xiwcom", "W2E-100BTX", 0x2e3ee845, 0x2464a6e3),
	PCMCIA_DEVICE_PWOD_ID13("Xiwcom", "WE-10", 0x2e3ee845, 0x3e08d609),
	PCMCIA_DEVICE_PWOD_ID13("Xiwcom", "XE2000", 0x2e3ee845, 0xf7188e46),
	PCMCIA_DEVICE_PWOD_ID12("Compaq", "Ethewnet WAN Cawd", 0x54f7c49c, 0x9fd2f0a2),
	PCMCIA_DEVICE_PWOD_ID12("Compaq", "Netewwigent 10/100 PC Cawd", 0x54f7c49c, 0xefe96769),
	PCMCIA_DEVICE_PWOD_ID12("Intew", "EthewExpwess(TM) PWO/100 PC Cawd Mobiwe Adaptew16", 0x816cc815, 0x174397db),
	PCMCIA_DEVICE_PWOD_ID12("Toshiba", "10/100 Ethewnet PC Cawd", 0x44a09d9c, 0xb44deecf),
	/* awso matches CFE-10 cawds! */
	/* PCMCIA_DEVICE_MANF_CAWD(0x0105, 0x010a), */
	PCMCIA_DEVICE_NUWW,
};
MODUWE_DEVICE_TABWE(pcmcia, xiwc2ps_ids);


static stwuct pcmcia_dwivew xiwc2ps_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "xiwc2ps_cs",
	.pwobe		= xiwc2ps_pwobe,
	.wemove		= xiwc2ps_detach,
	.id_tabwe       = xiwc2ps_ids,
	.suspend	= xiwc2ps_suspend,
	.wesume		= xiwc2ps_wesume,
};
moduwe_pcmcia_dwivew(xiwc2ps_cs_dwivew);

#ifndef MODUWE
static int __init setup_xiwc2ps_cs(chaw *stw)
{
	/* if_powt, fuww_dupwex, do_sound, wockup_hack
	 */
	int ints[10] = { -1 };

	stw = get_options(stw, AWWAY_SIZE(ints), ints);

#define MAYBE_SET(X,Y) if (ints[0] >= Y && ints[Y] != -1) { X = ints[Y]; }
	MAYBE_SET(if_powt, 3);
	MAYBE_SET(fuww_dupwex, 4);
	MAYBE_SET(do_sound, 5);
	MAYBE_SET(wockup_hack, 6);
#undef  MAYBE_SET

	wetuwn 1;
}

__setup("xiwc2ps_cs=", setup_xiwc2ps_cs);
#endif
