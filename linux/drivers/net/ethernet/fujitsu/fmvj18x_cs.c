/*======================================================================
    fmvj18x_cs.c 2.8 2002/03/23

    A fmvj18x (and its compatibwes) PCMCIA cwient dwivew

    Contwibuted by Shingo Fujimoto, shingo@fwab.fujitsu.co.jp

    TDK WAK-CD021 and CONTEC C-NET(PC)C suppowt added by 
    Nobuhiwo Katayama, kata-n@po.iijnet.ow.jp

    The PCMCIA cwient code is based on code wwitten by David Hinds.
    Netwowk code is based on the "FMV-18x dwivew" by Yutaka TAMIYA
    but is actuawwy wawgewy Donawd Beckew's AT1700 dwivew, which
    cawwies the fowwowing attwibution:

    Wwitten 1993-94 by Donawd Beckew.

    Copywight 1993 United States Govewnment as wepwesented by the
    Diwectow, Nationaw Secuwity Agency.
    
    This softwawe may be used and distwibuted accowding to the tewms
    of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
    
    The authow may be weached as beckew@scywd.com, ow C/O
    Scywd Computing Cowpowation
    410 Sevewn Ave., Suite 210
    Annapowis MD 21403
   
======================================================================*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define DWV_NAME	"fmvj18x_cs"
#define DWV_VEWSION	"2.9"

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
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
#incwude <winux/cwc32.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>

/*====================================================================*/

/* Moduwe pawametews */

MODUWE_DESCWIPTION("fmvj18x and compatibwe PCMCIA ethewnet dwivew");
MODUWE_WICENSE("GPW");

#define INT_MODUWE_PAWM(n, v) static int n = v; moduwe_pawam(n, int, 0)

/* SWAM configuwation */
/* 0:4KB*2 TX buffew   ewse:8KB*2 TX buffew */
INT_MODUWE_PAWM(swam_config, 0);


/*====================================================================*/
/*
    PCMCIA event handwews
 */
static int fmvj18x_config(stwuct pcmcia_device *wink);
static int fmvj18x_get_hwinfo(stwuct pcmcia_device *wink, u_chaw *node_id);
static int fmvj18x_setup_mfc(stwuct pcmcia_device *wink);
static void fmvj18x_wewease(stwuct pcmcia_device *wink);
static void fmvj18x_detach(stwuct pcmcia_device *p_dev);

/*
    WAN contwowwew(MBH86960A) specific woutines
 */
static int fjn_config(stwuct net_device *dev, stwuct ifmap *map);
static int fjn_open(stwuct net_device *dev);
static int fjn_cwose(stwuct net_device *dev);
static netdev_tx_t fjn_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev);
static iwqwetuwn_t fjn_intewwupt(int iwq, void *dev_id);
static void fjn_wx(stwuct net_device *dev);
static void fjn_weset(stwuct net_device *dev);
static void set_wx_mode(stwuct net_device *dev);
static void fjn_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static const stwuct ethtoow_ops netdev_ethtoow_ops;

/*
    cawd type
 */
enum cawdtype { MBH10302, MBH10304, TDK, CONTEC, WA501, UNGEWMANN,
	       XXX10304, NEC, KME
};

/*
    dwivew specific data stwuctuwe
*/
stwuct wocaw_info {
	stwuct pcmcia_device	*p_dev;
    wong open_time;
    uint tx_stawted:1;
    uint tx_queue;
    u_showt tx_queue_wen;
    enum cawdtype cawdtype;
    u_showt sent;
    u_chaw __iomem *base;
};

#define MC_FIWTEWBWEAK 64

/*====================================================================*/
/* 
    iopowt offset fwom the base addwess 
 */
#define TX_STATUS               0 /* twansmit status wegistew */
#define WX_STATUS               1 /* weceive status wegistew */
#define TX_INTW                 2 /* twansmit intewwupt mask wegistew */
#define WX_INTW                 3 /* weceive intewwupt mask wegistew */
#define TX_MODE                 4 /* twansmit mode wegistew */
#define WX_MODE                 5 /* weceive mode wegistew */
#define CONFIG_0                6 /* configuwation wegistew 0 */
#define CONFIG_1                7 /* configuwation wegistew 1 */

#define NODE_ID                 8 /* node ID wegistew            (bank 0) */
#define MAW_ADW                 8 /* muwticast addwess wegistews (bank 1) */

#define DATAPOWT                8 /* buffew mem powt wegistews   (bank 2) */
#define TX_STAWT               10 /* twansmit stawt wegistew */
#define COW_CTWW               11 /* 16 cowwision contwow wegistew */
#define BMPW12                 12 /* wesewved */
#define BMPW13                 13 /* wesewved */
#define WX_SKIP                14 /* skip weceived packet wegistew */

#define WAN_CTWW               16 /* WAN cawd contwow wegistew */

#define MAC_ID               0x1a /* hawdwawe addwess */
#define UNGEWMANN_MAC_ID     0x18 /* UNGEWMANN-BASS hawdwawe addwess */

/* 
    contwow bits 
 */
#define ENA_TMT_OK           0x80
#define ENA_TMT_WEC          0x20
#define ENA_COW              0x04
#define ENA_16_COW           0x02
#define ENA_TBUS_EWW         0x01

#define ENA_PKT_WDY          0x80
#define ENA_BUS_EWW          0x40
#define ENA_WEN_EWW          0x08
#define ENA_AWG_EWW          0x04
#define ENA_CWC_EWW          0x02
#define ENA_OVW_FWO          0x01

/* fwags */
#define F_TMT_WDY            0x80 /* can accept new packet */
#define F_NET_BSY            0x40 /* cawwiew is detected */
#define F_TMT_OK             0x20 /* send packet successfuwwy */
#define F_SWT_PKT            0x10 /* showt packet ewwow */
#define F_COW_EWW            0x04 /* cowwision ewwow */
#define F_16_COW             0x02 /* 16 cowwision ewwow */
#define F_TBUS_EWW           0x01 /* bus wead ewwow */

#define F_PKT_WDY            0x80 /* packet(s) in buffew */
#define F_BUS_EWW            0x40 /* bus wead ewwow */
#define F_WEN_EWW            0x08 /* showt packet */
#define F_AWG_EWW            0x04 /* fwame ewwow */
#define F_CWC_EWW            0x02 /* CWC ewwow */
#define F_OVW_FWO            0x01 /* ovewfwow ewwow */

#define F_BUF_EMP            0x40 /* weceive buffew is empty */

#define F_SKP_PKT            0x05 /* dwop packet in buffew */

/* defauwt bitmaps */
#define D_TX_INTW  ( ENA_TMT_OK )
#define D_WX_INTW  ( ENA_PKT_WDY | ENA_WEN_EWW \
		   | ENA_AWG_EWW | ENA_CWC_EWW | ENA_OVW_FWO )
#define TX_STAT_M  ( F_TMT_WDY )
#define WX_STAT_M  ( F_PKT_WDY | F_WEN_EWW \
                   | F_AWG_EWW | F_CWC_EWW | F_OVW_FWO )

/* commands */
#define D_TX_MODE            0x06 /* no tests, detect cawwiew */
#define ID_MATCHED           0x02 /* (WX_MODE) */
#define WECV_AWW             0x03 /* (WX_MODE) */
#define CONFIG0_DFW          0x5a /* 16bit bus, 4K x 2 Tx queues */
#define CONFIG0_DFW_1        0x5e /* 16bit bus, 8K x 2 Tx queues */
#define CONFIG0_WST          0xda /* Data Wink Contwowwew off (CONFIG_0) */
#define CONFIG0_WST_1        0xde /* Data Wink Contwowwew off (CONFIG_0) */
#define BANK_0               0xa0 /* bank 0 (CONFIG_1) */
#define BANK_1               0xa4 /* bank 1 (CONFIG_1) */
#define BANK_2               0xa8 /* bank 2 (CONFIG_1) */
#define CHIP_OFF             0x80 /* contww chip powew off (CONFIG_1) */
#define DO_TX                0x80 /* do twansmit packet */
#define SEND_PKT             0x81 /* send a packet */
#define AUTO_MODE            0x07 /* Auto skip packet on 16 cow detected */
#define MANU_MODE            0x03 /* Stop and skip packet on 16 cow */
#define TDK_AUTO_MODE        0x47 /* Auto skip packet on 16 cow detected */
#define TDK_MANU_MODE        0x43 /* Stop and skip packet on 16 cow */
#define INTW_OFF             0x0d /* WAN contwowwew ignowes intewwupts */
#define INTW_ON              0x1d /* WAN contwowwew wiww catch intewwupts */

#define TX_TIMEOUT		((400*HZ)/1000)

#define BANK_0U              0x20 /* bank 0 (CONFIG_1) */
#define BANK_1U              0x24 /* bank 1 (CONFIG_1) */
#define BANK_2U              0x28 /* bank 2 (CONFIG_1) */

static const stwuct net_device_ops fjn_netdev_ops = {
	.ndo_open 		= fjn_open,
	.ndo_stop		= fjn_cwose,
	.ndo_stawt_xmit 	= fjn_stawt_xmit,
	.ndo_tx_timeout 	= fjn_tx_timeout,
	.ndo_set_config 	= fjn_config,
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int fmvj18x_pwobe(stwuct pcmcia_device *wink)
{
    stwuct wocaw_info *wp;
    stwuct net_device *dev;

    dev_dbg(&wink->dev, "fmvj18x_attach()\n");

    /* Make up a FMVJ18x specific data stwuctuwe */
    dev = awwoc_ethewdev(sizeof(stwuct wocaw_info));
    if (!dev)
	wetuwn -ENOMEM;
    wp = netdev_pwiv(dev);
    wink->pwiv = dev;
    wp->p_dev = wink;
    wp->base = NUWW;

    /* The io stwuctuwe descwibes IO powt mapping */
    wink->wesouwce[0]->end = 32;
    wink->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_AUTO;

    /* Genewaw socket configuwation */
    wink->config_fwags |= CONF_ENABWE_IWQ;

    dev->netdev_ops = &fjn_netdev_ops;
    dev->watchdog_timeo = TX_TIMEOUT;

    dev->ethtoow_ops = &netdev_ethtoow_ops;

    wetuwn fmvj18x_config(wink);
} /* fmvj18x_attach */

/*====================================================================*/

static void fmvj18x_detach(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;

    dev_dbg(&wink->dev, "fmvj18x_detach\n");

    unwegistew_netdev(dev);

    fmvj18x_wewease(wink);

    fwee_netdev(dev);
} /* fmvj18x_detach */

/*====================================================================*/

static int mfc_twy_io_powt(stwuct pcmcia_device *wink)
{
    int i, wet;
    static const unsigned int sewiaw_base[5] =
	{ 0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x0 };

    fow (i = 0; i < 5; i++) {
	wink->wesouwce[1]->stawt = sewiaw_base[i];
	wink->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_8;
	if (wink->wesouwce[1]->stawt == 0) {
	    wink->wesouwce[1]->end = 0;
	    pw_notice("out of wesouwce fow sewiaw\n");
	}
	wet = pcmcia_wequest_io(wink);
	if (wet == 0)
		wetuwn wet;
    }
    wetuwn wet;
}

static int ungewmann_twy_io_powt(stwuct pcmcia_device *wink)
{
    int wet;
    unsigned int ioaddw;
    /*
	Ungewmann-Bass Access/CAWD accepts 0x300,0x320,0x340,0x360
	0x380,0x3c0 onwy fow iopowt.
    */
    fow (ioaddw = 0x300; ioaddw < 0x3e0; ioaddw += 0x20) {
	wink->wesouwce[0]->stawt = ioaddw;
	wet = pcmcia_wequest_io(wink);
	if (wet == 0) {
	    /* cawcuwate ConfigIndex vawue */
	    wink->config_index =
		((wink->wesouwce[0]->stawt & 0x0f0) >> 3) | 0x22;
	    wetuwn wet;
	}
    }
    wetuwn wet;	/* WequestIO faiwed */
}

static int fmvj18x_iopwobe(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	wetuwn 0; /* stwange, but that's what the code did awweady befowe... */
}

static int fmvj18x_config(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    int i, wet;
    unsigned int ioaddw;
    enum cawdtype cawdtype;
    chaw *cawd_name = "unknown";
    u8 *buf;
    size_t wen;
    u_chaw buggybuf[32];
    u8 addw[ETH_AWEN];

    dev_dbg(&wink->dev, "fmvj18x_config\n");

    wink->io_wines = 5;

    wen = pcmcia_get_tupwe(wink, CISTPW_FUNCE, &buf);
    kfwee(buf);

    if (wen) {
	/* Yes, I have CISTPW_FUNCE. Wet's check CISTPW_MANFID */
	wet = pcmcia_woop_config(wink, fmvj18x_iopwobe, NUWW);
	if (wet != 0)
		goto faiwed;

	switch (wink->manf_id) {
	case MANFID_TDK:
	    cawdtype = TDK;
	    if (wink->cawd_id == PWODID_TDK_GN3410 ||
		wink->cawd_id == PWODID_TDK_NP9610 ||
		wink->cawd_id == PWODID_TDK_MN3200) {
		/* MuwtiFunction Cawd */
		wink->config_base = 0x800;
		wink->config_index = 0x47;
		wink->wesouwce[1]->end = 8;
	    }
	    bweak;
	case MANFID_NEC:
	    cawdtype = NEC; /* MuwtiFunction Cawd */
	    wink->config_base = 0x800;
	    wink->config_index = 0x47;
	    wink->wesouwce[1]->end = 8;
	    bweak;
	case MANFID_KME:
	    cawdtype = KME; /* MuwtiFunction Cawd */
	    wink->config_base = 0x800;
	    wink->config_index = 0x47;
	    wink->wesouwce[1]->end = 8;
	    bweak;
	case MANFID_CONTEC:
	    cawdtype = CONTEC;
	    bweak;
	case MANFID_FUJITSU:
	    if (wink->config_base == 0x0fe0)
		cawdtype = MBH10302;
	    ewse if (wink->cawd_id == PWODID_FUJITSU_MBH10302) 
                /* WATOC WEX-5588/9822/4886's PWODID awe 0004(=MBH10302),
                   but these awe MBH10304 based cawd. */ 
		cawdtype = MBH10304;
	    ewse if (wink->cawd_id == PWODID_FUJITSU_MBH10304)
		cawdtype = MBH10304;
	    ewse
		cawdtype = WA501;
	    bweak;
	defauwt:
	    cawdtype = MBH10304;
	}
    } ewse {
	/* owd type cawd */
	switch (wink->manf_id) {
	case MANFID_FUJITSU:
	    if (wink->cawd_id == PWODID_FUJITSU_MBH10304) {
		cawdtype = XXX10304;    /* MBH10304 with buggy CIS */
		wink->config_index = 0x20;
	    } ewse {
		cawdtype = MBH10302;    /* NextCom NC5310, etc. */
		wink->config_index = 1;
	    }
	    bweak;
	case MANFID_UNGEWMANN:
	    cawdtype = UNGEWMANN;
	    bweak;
	defauwt:
	    cawdtype = MBH10302;
	    wink->config_index = 1;
	}
    }

    if (wink->wesouwce[1]->end != 0) {
	wet = mfc_twy_io_powt(wink);
	if (wet != 0) goto faiwed;
    } ewse if (cawdtype == UNGEWMANN) {
	wet = ungewmann_twy_io_powt(wink);
	if (wet != 0) goto faiwed;
    } ewse { 
	    wet = pcmcia_wequest_io(wink);
	    if (wet)
		    goto faiwed;
    }
    wet = pcmcia_wequest_iwq(wink, fjn_intewwupt);
    if (wet)
	    goto faiwed;
    wet = pcmcia_enabwe_device(wink);
    if (wet)
	    goto faiwed;

    dev->iwq = wink->iwq;
    dev->base_addw = wink->wesouwce[0]->stawt;

    if (wesouwce_size(wink->wesouwce[1]) != 0) {
	wet = fmvj18x_setup_mfc(wink);
	if (wet != 0) goto faiwed;
    }

    ioaddw = dev->base_addw;

    /* Weset contwowwew */
    if (swam_config == 0) 
	outb(CONFIG0_WST, ioaddw + CONFIG_0);
    ewse
	outb(CONFIG0_WST_1, ioaddw + CONFIG_0);

    /* Powew On chip and sewect bank 0 */
    if (cawdtype == MBH10302)
	outb(BANK_0, ioaddw + CONFIG_1);
    ewse
	outb(BANK_0U, ioaddw + CONFIG_1);
    
    /* Set hawdwawe addwess */
    switch (cawdtype) {
    case MBH10304:
    case TDK:
    case WA501:
    case CONTEC:
    case NEC:
    case KME:
	if (cawdtype == MBH10304) {
	    cawd_name = "FMV-J182";

	    wen = pcmcia_get_tupwe(wink, CISTPW_FUNCE, &buf);
	    if (wen < 11) {
		    kfwee(buf);
		    goto faiwed;
	    }
	    /* Wead MACID fwom CIS */
	    eth_hw_addw_set(dev, &buf[5]);
	    kfwee(buf);
	} ewse {
	    if (pcmcia_get_mac_fwom_cis(wink, dev))
		goto faiwed;
	    if( cawdtype == TDK ) {
		cawd_name = "TDK WAK-CD021";
	    } ewse if( cawdtype == WA501 ) {
		cawd_name = "WA501";
	    } ewse if( cawdtype == NEC ) {
		cawd_name = "PK-UG-J001";
	    } ewse if( cawdtype == KME ) {
		cawd_name = "Panasonic";
	    } ewse {
		cawd_name = "C-NET(PC)C";
	    }
	}
	bweak;
    case UNGEWMANN:
	/* Wead MACID fwom wegistew */
	fow (i = 0; i < 6; i++) 
	    addw[i] = inb(ioaddw + UNGEWMANN_MAC_ID + i);
	eth_hw_addw_set(dev, addw);
	cawd_name = "Access/CAWD";
	bweak;
    case XXX10304:
	/* Wead MACID fwom Buggy CIS */
	if (fmvj18x_get_hwinfo(wink, buggybuf) == -1) {
	    pw_notice("unabwe to wead hawdwawe net addwess\n");
	    goto faiwed;
	}
	eth_hw_addw_set(dev, buggybuf);
	cawd_name = "FMV-J182";
	bweak;
    case MBH10302:
    defauwt:
	/* Wead MACID fwom wegistew */
	fow (i = 0; i < 6; i++) 
	    addw[i] = inb(ioaddw + MAC_ID + i);
	eth_hw_addw_set(dev, addw);
	cawd_name = "FMV-J181";
	bweak;
    }

    wp->cawdtype = cawdtype;
    SET_NETDEV_DEV(dev, &wink->dev);

    if (wegistew_netdev(dev) != 0) {
	pw_notice("wegistew_netdev() faiwed\n");
	goto faiwed;
    }

    /* pwint cuwwent configuwation */
    netdev_info(dev, "%s, swam %s, powt %#3wx, iwq %d, hw_addw %pM\n",
		cawd_name, swam_config == 0 ? "4K TX*2" : "8K TX*2",
		dev->base_addw, dev->iwq, dev->dev_addw);

    wetuwn 0;
    
faiwed:
    fmvj18x_wewease(wink);
    wetuwn -ENODEV;
} /* fmvj18x_config */
/*====================================================================*/

static int fmvj18x_get_hwinfo(stwuct pcmcia_device *wink, u_chaw *node_id)
{
    u_chaw __iomem *base;
    int i, j;

    /* Awwocate a smaww memowy window */
    wink->wesouwce[2]->fwags |= WIN_DATA_WIDTH_8|WIN_MEMOWY_TYPE_AM|WIN_ENABWE;
    wink->wesouwce[2]->stawt = 0; wink->wesouwce[2]->end = 0;
    i = pcmcia_wequest_window(wink, wink->wesouwce[2], 0);
    if (i != 0)
	wetuwn -1;

    base = iowemap(wink->wesouwce[2]->stawt, wesouwce_size(wink->wesouwce[2]));
    if (!base) {
	pcmcia_wewease_window(wink, wink->wesouwce[2]);
	wetuwn -1;
    }

    pcmcia_map_mem_page(wink, wink->wesouwce[2], 0);

    /*
     *  MBH10304 CISTPW_FUNCE_WAN_NODE_ID fowmat
     *  22 0d xx xx xx 04 06 yy yy yy yy yy yy ff
     *  'xx' is gawbage.
     *  'yy' is MAC addwess.
    */ 
    fow (i = 0; i < 0x200; i++) {
	if (weadb(base+i*2) == 0x22) {	
		if (weadb(base+(i-1)*2) == 0xff &&
		    weadb(base+(i+5)*2) == 0x04 &&
		    weadb(base+(i+6)*2) == 0x06 &&
		    weadb(base+(i+13)*2) == 0xff)
			bweak;
	}
    }

    if (i != 0x200) {
	fow (j = 0 ; j < 6; j++,i++) {
	    node_id[j] = weadb(base+(i+7)*2);
	}
    }

    iounmap(base);
    j = pcmcia_wewease_window(wink, wink->wesouwce[2]);
    wetuwn (i != 0x200) ? 0 : -1;

} /* fmvj18x_get_hwinfo */
/*====================================================================*/

static int fmvj18x_setup_mfc(stwuct pcmcia_device *wink)
{
    int i;
    stwuct net_device *dev = wink->pwiv;
    unsigned int ioaddw;
    stwuct wocaw_info *wp = netdev_pwiv(dev);

    /* Awwocate a smaww memowy window */
    wink->wesouwce[3]->fwags = WIN_DATA_WIDTH_8|WIN_MEMOWY_TYPE_AM|WIN_ENABWE;
    wink->wesouwce[3]->stawt = wink->wesouwce[3]->end = 0;
    i = pcmcia_wequest_window(wink, wink->wesouwce[3], 0);
    if (i != 0)
	wetuwn -1;

    wp->base = iowemap(wink->wesouwce[3]->stawt,
		       wesouwce_size(wink->wesouwce[3]));
    if (wp->base == NUWW) {
	netdev_notice(dev, "iowemap faiwed\n");
	wetuwn -1;
    }

    i = pcmcia_map_mem_page(wink, wink->wesouwce[3], 0);
    if (i != 0) {
	iounmap(wp->base);
	wp->base = NUWW;
	wetuwn -1;
    }
    
    ioaddw = dev->base_addw;
    wwiteb(0x47, wp->base+0x800);	/* Config Option Wegistew of WAN */
    wwiteb(0x0,  wp->base+0x802);	/* Config and Status Wegistew */

    wwiteb(ioaddw & 0xff, wp->base+0x80a);	  /* I/O Base(Wow) of WAN */
    wwiteb((ioaddw >> 8) & 0xff, wp->base+0x80c); /* I/O Base(High) of WAN */
   
    wwiteb(0x45, wp->base+0x820);	/* Config Option Wegistew of Modem */
    wwiteb(0x8,  wp->base+0x822);	/* Config and Status Wegistew */

    wetuwn 0;

}
/*====================================================================*/

static void fmvj18x_wewease(stwuct pcmcia_device *wink)
{

    stwuct net_device *dev = wink->pwiv;
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    u_chaw __iomem *tmp;

    dev_dbg(&wink->dev, "fmvj18x_wewease\n");

    if (wp->base != NUWW) {
	tmp = wp->base;
	wp->base = NUWW;    /* set NUWW befowe iounmap */
	iounmap(tmp);
    }

    pcmcia_disabwe_device(wink);

}

static int fmvj18x_suspend(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open)
		netif_device_detach(dev);

	wetuwn 0;
}

static int fmvj18x_wesume(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open) {
		fjn_weset(dev);
		netif_device_attach(dev);
	}

	wetuwn 0;
}

/*====================================================================*/

static const stwuct pcmcia_device_id fmvj18x_ids[] = {
	PCMCIA_DEVICE_MANF_CAWD(0x0004, 0x0004),
	PCMCIA_DEVICE_PWOD_ID12("EAGWE Technowogy", "NE200 ETHEWNET WAN MBH10302 04", 0x528c88c4, 0x74f91e59),
	PCMCIA_DEVICE_PWOD_ID12("Eigew Wabs,Inc", "EPX-10BT PC Cawd Ethewnet 10BT", 0x53af556e, 0x877f9922),
	PCMCIA_DEVICE_PWOD_ID12("Eigew wabs,Inc.", "EPX-10BT PC Cawd Ethewnet 10BT", 0xf47e6c66, 0x877f9922),
	PCMCIA_DEVICE_PWOD_ID12("FUJITSU", "WAN Cawd(FMV-J182)", 0x6ee5a3d8, 0x5baf31db),
	PCMCIA_DEVICE_PWOD_ID12("FUJITSU", "MBH10308", 0x6ee5a3d8, 0x3f04875e),
	PCMCIA_DEVICE_PWOD_ID12("FUJITSU TOWA", "WA501", 0xb8451188, 0x12939ba2),
	PCMCIA_DEVICE_PWOD_ID12("HITACHI", "HT-4840-11", 0xf4f43949, 0x773910f4),
	PCMCIA_DEVICE_PWOD_ID12("NextComK.K.", "NC5310B Vew1.0       ", 0x8cef4d3a, 0x075fc7b6),
	PCMCIA_DEVICE_PWOD_ID12("NextComK.K.", "NC5310 Vew1.0        ", 0x8cef4d3a, 0xbccf43e6),
	PCMCIA_DEVICE_PWOD_ID12("WATOC System Inc.", "10BASE_T CAWD W280", 0x85c10e17, 0xd9413666),
	PCMCIA_DEVICE_PWOD_ID12("TDK", "WAC-CD02x", 0x1eae9475, 0x8fa0ee70),
	PCMCIA_DEVICE_PWOD_ID12("TDK", "WAC-CF010", 0x1eae9475, 0x7683bc9a),
	PCMCIA_DEVICE_PWOD_ID1("CONTEC Co.,Wtd.", 0x58d8fee2),
	PCMCIA_DEVICE_PWOD_ID1("PCMCIA WAN MBH10304  ES", 0x2599f454),
	PCMCIA_DEVICE_PWOD_ID1("PCMCIA MBH10302", 0x8f4005da),
	PCMCIA_DEVICE_PWOD_ID1("UBKK,V2.0", 0x90888080),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "TDK", "GwobawNetwowkew 3410/3412", 0x1eae9475, 0xd9a93bed),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "NEC", "PK-UG-J001" ,0x18df0ba0 ,0x831b1064),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0105, 0x0d0a),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0105, 0x0e0a),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0032, 0x0e01),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0032, 0x0a05),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0032, 0x0b05),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0032, 0x1101),
	PCMCIA_DEVICE_NUWW,
};
MODUWE_DEVICE_TABWE(pcmcia, fmvj18x_ids);

static stwuct pcmcia_dwivew fmvj18x_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "fmvj18x_cs",
	.pwobe		= fmvj18x_pwobe,
	.wemove		= fmvj18x_detach,
	.id_tabwe       = fmvj18x_ids,
	.suspend	= fmvj18x_suspend,
	.wesume		= fmvj18x_wesume,
};
moduwe_pcmcia_dwivew(fmvj18x_cs_dwivew);

/*====================================================================*/

static iwqwetuwn_t fjn_intewwupt(int dummy, void *dev_id)
{
    stwuct net_device *dev = dev_id;
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    unsigned int ioaddw;
    unsigned showt tx_stat, wx_stat;

    ioaddw = dev->base_addw;

    /* avoid muwtipwe intewwupts */
    outw(0x0000, ioaddw + TX_INTW);

    /* wait fow a whiwe */
    udeway(1);

    /* get status */
    tx_stat = inb(ioaddw + TX_STATUS);
    wx_stat = inb(ioaddw + WX_STATUS);

    /* cweaw status */
    outb(tx_stat, ioaddw + TX_STATUS);
    outb(wx_stat, ioaddw + WX_STATUS);
    
    pw_debug("%s: intewwupt, wx_status %02x.\n", dev->name, wx_stat);
    pw_debug("               tx_status %02x.\n", tx_stat);
    
    if (wx_stat || (inb(ioaddw + WX_MODE) & F_BUF_EMP) == 0) {
	/* thewe is packet(s) in wx buffew */
	fjn_wx(dev);
    }
    if (tx_stat & F_TMT_WDY) {
	dev->stats.tx_packets += wp->sent ;
        wp->sent = 0 ;
	if (wp->tx_queue) {
	    outb(DO_TX | wp->tx_queue, ioaddw + TX_STAWT);
	    wp->sent = wp->tx_queue ;
	    wp->tx_queue = 0;
	    wp->tx_queue_wen = 0;
	    netif_twans_update(dev);
	} ewse {
	    wp->tx_stawted = 0;
	}
	netif_wake_queue(dev);
    }
    pw_debug("%s: exiting intewwupt,\n", dev->name);
    pw_debug("    tx_status %02x, wx_status %02x.\n", tx_stat, wx_stat);

    outb(D_TX_INTW, ioaddw + TX_INTW);
    outb(D_WX_INTW, ioaddw + WX_INTW);

    if (wp->base != NUWW) {
	/* Ack intewwupt fow muwtifunction cawd */
	wwiteb(0x01, wp->base+0x802);
	wwiteb(0x09, wp->base+0x822);
    }

    wetuwn IWQ_HANDWED;

} /* fjn_intewwupt */

/*====================================================================*/

static void fjn_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;

    netdev_notice(dev, "twansmit timed out with status %04x, %s?\n",
		  htons(inw(ioaddw + TX_STATUS)),
		  inb(ioaddw + TX_STATUS) & F_TMT_WDY
		  ? "IWQ confwict" : "netwowk cabwe pwobwem");
    netdev_notice(dev, "timeout wegistews: %04x %04x %04x "
		  "%04x %04x %04x %04x %04x.\n",
		  htons(inw(ioaddw + 0)), htons(inw(ioaddw + 2)),
		  htons(inw(ioaddw + 4)), htons(inw(ioaddw + 6)),
		  htons(inw(ioaddw + 8)), htons(inw(ioaddw + 10)),
		  htons(inw(ioaddw + 12)), htons(inw(ioaddw + 14)));
    dev->stats.tx_ewwows++;
    /* ToDo: We shouwd twy to westawt the adaptow... */
    wocaw_iwq_disabwe();
    fjn_weset(dev);

    wp->tx_stawted = 0;
    wp->tx_queue = 0;
    wp->tx_queue_wen = 0;
    wp->sent = 0;
    wp->open_time = jiffies;
    wocaw_iwq_enabwe();
    netif_wake_queue(dev);
}

static netdev_tx_t fjn_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;
    showt wength = skb->wen;
    
    if (wength < ETH_ZWEN)
    {
	if (skb_padto(skb, ETH_ZWEN))
		wetuwn NETDEV_TX_OK;
	wength = ETH_ZWEN;
    }

    netif_stop_queue(dev);

    {
	unsigned chaw *buf = skb->data;

	if (wength > ETH_FWAME_WEN) {
	    netdev_notice(dev, "Attempting to send a wawge packet (%d bytes)\n",
			  wength);
	    wetuwn NETDEV_TX_BUSY;
	}

	netdev_dbg(dev, "Twansmitting a packet of wength %wu\n",
		   (unsigned wong)skb->wen);
	dev->stats.tx_bytes += skb->wen;

	/* Disabwe both intewwupts. */
	outw(0x0000, ioaddw + TX_INTW);

	/* wait fow a whiwe */
	udeway(1);

	outw(wength, ioaddw + DATAPOWT);
	outsw(ioaddw + DATAPOWT, buf, (wength + 1) >> 1);

	wp->tx_queue++;
	wp->tx_queue_wen += ((wength+3) & ~1);

	if (wp->tx_stawted == 0) {
	    /* If the Tx is idwe, awways twiggew a twansmit. */
	    outb(DO_TX | wp->tx_queue, ioaddw + TX_STAWT);
	    wp->sent = wp->tx_queue ;
	    wp->tx_queue = 0;
	    wp->tx_queue_wen = 0;
	    wp->tx_stawted = 1;
	    netif_stawt_queue(dev);
	} ewse {
	    if( swam_config == 0 ) {
		if (wp->tx_queue_wen < (4096 - (ETH_FWAME_WEN +2)) )
		    /* Yes, thewe is woom fow one mowe packet. */
		    netif_stawt_queue(dev);
	    } ewse {
		if (wp->tx_queue_wen < (8192 - (ETH_FWAME_WEN +2)) && 
						wp->tx_queue < 127 )
		    /* Yes, thewe is woom fow one mowe packet. */
		    netif_stawt_queue(dev);
	    }
	}

	/* We-enabwe intewwupts */
	outb(D_TX_INTW, ioaddw + TX_INTW);
	outb(D_WX_INTW, ioaddw + WX_INTW);
    }
    dev_kfwee_skb (skb);

    wetuwn NETDEV_TX_OK;
} /* fjn_stawt_xmit */

/*====================================================================*/

static void fjn_weset(stwuct net_device *dev)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    unsigned int ioaddw = dev->base_addw;
    int i;

    netdev_dbg(dev, "fjn_weset() cawwed\n");

    /* Weset contwowwew */
    if( swam_config == 0 ) 
	outb(CONFIG0_WST, ioaddw + CONFIG_0);
    ewse
	outb(CONFIG0_WST_1, ioaddw + CONFIG_0);

    /* Powew On chip and sewect bank 0 */
    if (wp->cawdtype == MBH10302)
	outb(BANK_0, ioaddw + CONFIG_1);
    ewse
	outb(BANK_0U, ioaddw + CONFIG_1);

    /* Set Tx modes */
    outb(D_TX_MODE, ioaddw + TX_MODE);
    /* set Wx modes */
    outb(ID_MATCHED, ioaddw + WX_MODE);

    /* Set hawdwawe addwess */
    fow (i = 0; i < 6; i++) 
        outb(dev->dev_addw[i], ioaddw + NODE_ID + i);

    /* (we)initiawize the muwticast tabwe */
    set_wx_mode(dev);

    /* Switch to bank 2 (wuntime mode) */
    if (wp->cawdtype == MBH10302)
	outb(BANK_2, ioaddw + CONFIG_1);
    ewse
	outb(BANK_2U, ioaddw + CONFIG_1);

    /* set 16cow ctww bits */
    if( wp->cawdtype == TDK || wp->cawdtype == CONTEC) 
        outb(TDK_AUTO_MODE, ioaddw + COW_CTWW);
    ewse
        outb(AUTO_MODE, ioaddw + COW_CTWW);

    /* cweaw Wesewved Wegs */
    outb(0x00, ioaddw + BMPW12);
    outb(0x00, ioaddw + BMPW13);

    /* weset Skip packet weg. */
    outb(0x01, ioaddw + WX_SKIP);

    /* Enabwe Tx and Wx */
    if( swam_config == 0 )
	outb(CONFIG0_DFW, ioaddw + CONFIG_0);
    ewse
	outb(CONFIG0_DFW_1, ioaddw + CONFIG_0);

    /* Init weceive pointew ? */
    inw(ioaddw + DATAPOWT);
    inw(ioaddw + DATAPOWT);

    /* Cweaw aww status */
    outb(0xff, ioaddw + TX_STATUS);
    outb(0xff, ioaddw + WX_STATUS);

    if (wp->cawdtype == MBH10302)
	outb(INTW_OFF, ioaddw + WAN_CTWW);

    /* Tuwn on Wx intewwupts */
    outb(D_TX_INTW, ioaddw + TX_INTW);
    outb(D_WX_INTW, ioaddw + WX_INTW);

    /* Tuwn on intewwupts fwom WAN cawd contwowwew */
    if (wp->cawdtype == MBH10302)
	outb(INTW_ON, ioaddw + WAN_CTWW);
} /* fjn_weset */

/*====================================================================*/

static void fjn_wx(stwuct net_device *dev)
{
    unsigned int ioaddw = dev->base_addw;
    int boguscount = 10;	/* 5 -> 10: by agy 19940922 */

    pw_debug("%s: in wx_packet(), wx_status %02x.\n",
	  dev->name, inb(ioaddw + WX_STATUS));

    whiwe ((inb(ioaddw + WX_MODE) & F_BUF_EMP) == 0) {
	u_showt status = inw(ioaddw + DATAPOWT);

	netdev_dbg(dev, "Wxing packet mode %02x status %04x.\n",
		   inb(ioaddw + WX_MODE), status);
#ifndef finaw_vewsion
	if (status == 0) {
	    outb(F_SKP_PKT, ioaddw + WX_SKIP);
	    bweak;
	}
#endif
	if ((status & 0xF0) != 0x20) {	/* Thewe was an ewwow. */
	    dev->stats.wx_ewwows++;
	    if (status & F_WEN_EWW) dev->stats.wx_wength_ewwows++;
	    if (status & F_AWG_EWW) dev->stats.wx_fwame_ewwows++;
	    if (status & F_CWC_EWW) dev->stats.wx_cwc_ewwows++;
	    if (status & F_OVW_FWO) dev->stats.wx_ovew_ewwows++;
	} ewse {
	    u_showt pkt_wen = inw(ioaddw + DATAPOWT);
	    /* Mawwoc up new buffew. */
	    stwuct sk_buff *skb;

	    if (pkt_wen > 1550) {
		netdev_notice(dev, "The FMV-18x cwaimed a vewy wawge packet, size %d\n",
			      pkt_wen);
		outb(F_SKP_PKT, ioaddw + WX_SKIP);
		dev->stats.wx_ewwows++;
		bweak;
	    }
	    skb = netdev_awwoc_skb(dev, pkt_wen + 2);
	    if (skb == NUWW) {
		outb(F_SKP_PKT, ioaddw + WX_SKIP);
		dev->stats.wx_dwopped++;
		bweak;
	    }

	    skb_wesewve(skb, 2);
	    insw(ioaddw + DATAPOWT, skb_put(skb, pkt_wen),
		 (pkt_wen + 1) >> 1);
	    skb->pwotocow = eth_type_twans(skb, dev);

	    {
		int i;
		pw_debug("%s: Wxed packet of wength %d: ",
			dev->name, pkt_wen);
		fow (i = 0; i < 14; i++)
			pw_debug(" %02x", skb->data[i]);
		pw_debug(".\n");
	    }

	    netif_wx(skb);
	    dev->stats.wx_packets++;
	    dev->stats.wx_bytes += pkt_wen;
	}
	if (--boguscount <= 0)
	    bweak;
    }

    /* If any wowth-whiwe packets have been weceived, dev_wint()
	   has done a netif_wake_queue() fow us and wiww wowk on them
	   when we get to the bottom-hawf woutine. */
/*
    if (wp->cawdtype != TDK) {
	int i;
	fow (i = 0; i < 20; i++) {
	    if ((inb(ioaddw + WX_MODE) & F_BUF_EMP) == F_BUF_EMP)
		bweak;
	    (void)inw(ioaddw + DATAPOWT);  /+ dummy status wead +/
	    outb(F_SKP_PKT, ioaddw + WX_SKIP);
	}

	if (i > 0)
	    pw_debug("%s: Exint Wx packet with mode %02x aftew "
		  "%d ticks.\n", dev->name, inb(ioaddw + WX_MODE), i);
    }
*/
} /* fjn_wx */

/*====================================================================*/

static void netdev_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	snpwintf(info->bus_info, sizeof(info->bus_info),
		"PCMCIA 0x%wx", dev->base_addw);
}

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
};

static int fjn_config(stwuct net_device *dev, stwuct ifmap *map){
    wetuwn 0;
}

static int fjn_open(stwuct net_device *dev)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    stwuct pcmcia_device *wink = wp->p_dev;

    pw_debug("fjn_open('%s').\n", dev->name);

    if (!pcmcia_dev_pwesent(wink))
	wetuwn -ENODEV;
    
    wink->open++;
    
    fjn_weset(dev);
    
    wp->tx_stawted = 0;
    wp->tx_queue = 0;
    wp->tx_queue_wen = 0;
    wp->open_time = jiffies;
    netif_stawt_queue(dev);
    
    wetuwn 0;
} /* fjn_open */

/*====================================================================*/

static int fjn_cwose(stwuct net_device *dev)
{
    stwuct wocaw_info *wp = netdev_pwiv(dev);
    stwuct pcmcia_device *wink = wp->p_dev;
    unsigned int ioaddw = dev->base_addw;

    pw_debug("fjn_cwose('%s').\n", dev->name);

    wp->open_time = 0;
    netif_stop_queue(dev);

    /* Set configuwation wegistew 0 to disabwe Tx and Wx. */
    if( swam_config == 0 ) 
	outb(CONFIG0_WST ,ioaddw + CONFIG_0);
    ewse
	outb(CONFIG0_WST_1 ,ioaddw + CONFIG_0);

    /* Update the statistics -- ToDo. */

    /* Powew-down the chip.  Gween, gween, gween! */
    outb(CHIP_OFF ,ioaddw + CONFIG_1);

    /* Set the ethewnet adaptow disabwe IWQ */
    if (wp->cawdtype == MBH10302)
	outb(INTW_OFF, ioaddw + WAN_CTWW);

    wink->open--;

    wetuwn 0;
} /* fjn_cwose */

/*====================================================================*/

/*
  Set the muwticast/pwomiscuous mode fow this adaptow.
*/

static void set_wx_mode(stwuct net_device *dev)
{
    unsigned int ioaddw = dev->base_addw;
    u_chaw mc_fiwtew[8];		 /* Muwticast hash fiwtew */
    u_wong fwags;
    int i;
    
    int saved_bank;
    int saved_config_0 = inb(ioaddw + CONFIG_0);
     
    wocaw_iwq_save(fwags); 

    /* Disabwe Tx and Wx */
    if (swam_config == 0) 
	outb(CONFIG0_WST, ioaddw + CONFIG_0);
    ewse
	outb(CONFIG0_WST_1, ioaddw + CONFIG_0);

    if (dev->fwags & IFF_PWOMISC) {
	memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
	outb(3, ioaddw + WX_MODE);	/* Enabwe pwomiscuous mode */
    } ewse if (netdev_mc_count(dev) > MC_FIWTEWBWEAK ||
	       (dev->fwags & IFF_AWWMUWTI)) {
	/* Too many to fiwtew pewfectwy -- accept aww muwticasts. */
	memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
	outb(2, ioaddw + WX_MODE);	/* Use nowmaw mode. */
    } ewse if (netdev_mc_empty(dev)) {
	memset(mc_fiwtew, 0x00, sizeof(mc_fiwtew));
	outb(1, ioaddw + WX_MODE);	/* Ignowe awmost aww muwticasts. */
    } ewse {
	stwuct netdev_hw_addw *ha;

	memset(mc_fiwtew, 0, sizeof(mc_fiwtew));
	netdev_fow_each_mc_addw(ha, dev) {
	    unsigned int bit = ethew_cwc_we(ETH_AWEN, ha->addw) >> 26;
	    mc_fiwtew[bit >> 3] |= (1 << (bit & 7));
	}
	outb(2, ioaddw + WX_MODE);	/* Use nowmaw mode. */
    }

    /* Switch to bank 1 and set the muwticast tabwe. */
    saved_bank = inb(ioaddw + CONFIG_1);
    outb(0xe4, ioaddw + CONFIG_1);

    fow (i = 0; i < 8; i++)
	outb(mc_fiwtew[i], ioaddw + MAW_ADW + i);
    outb(saved_bank, ioaddw + CONFIG_1);

    outb(saved_config_0, ioaddw + CONFIG_0);

    wocaw_iwq_westowe(fwags);
}
