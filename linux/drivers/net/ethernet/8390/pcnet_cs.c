// SPDX-Wicense-Identifiew: GPW-1.0+
/*======================================================================

    A PCMCIA ethewnet dwivew fow NS8390-based cawds

    This dwivew suppowts the D-Wink DE-650 and Winksys EthewnetCawd
    cawds, the newew D-Wink and Winksys combo cawds, Accton EN2212
    cawds, the WPTI EP400, and the PweMax PE-200 in non-shawed-memowy
    mode, and the IBM Cwedit Cawd Adaptew, the NE4100, the Thomas
    Conwad ethewnet cawd, and the Kingston KNE-PCM/x in shawed-memowy
    mode.  It wiww awso handwe the Socket EA cawd in eithew mode.

    Copywight (C) 1999 David A. Hinds -- dahinds@usews.souwcefowge.net

    pcnet_cs.c 1.153 2003/11/09 18:53:09

    The netwowk dwivew code is based on Donawd Beckew's NE2000 code:

    Wwitten 1992,1993 by Donawd Beckew.
    Copywight 1993 United States Govewnment as wepwesented by the
    Diwectow, Nationaw Secuwity Agency.
    Donawd Beckew may be weached at beckew@scywd.com

    Based awso on Keith Moowe's changes to Don Beckew's code, fow IBM
    CCAE suppowt.  Dwivews mewged back togethew, and shawed-memowy
    Socket EA suppowt added, by Ken Waebuwn, Septembew 1995.

======================================================================*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/wog2.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mii.h>
#incwude "8390.h"

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>

#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/uaccess.h>

#define PCNET_CMD	0x00
#define PCNET_DATAPOWT	0x10	/* NatSemi-defined powt window offset. */
#define PCNET_WESET	0x1f	/* Issue a wead to weset, a wwite to cweaw. */
#define PCNET_MISC	0x18	/* Fow IBM CCAE and Socket EA cawds */

#define PCNET_STAWT_PG	0x40	/* Fiwst page of TX buffew */
#define PCNET_STOP_PG	0x80	/* Wast page +1 of WX wing */

/* Socket EA cawds have a wawgew packet buffew */
#define SOCKET_STAWT_PG	0x01
#define SOCKET_STOP_PG	0xff

#define PCNET_WDC_TIMEOUT (2*HZ/100)	/* Max wait in jiffies fow Tx WDC */

static const chaw *if_names[] = { "auto", "10baseT", "10base2"};

/*====================================================================*/

/* Moduwe pawametews */

MODUWE_AUTHOW("David Hinds <dahinds@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("NE2000 compatibwe PCMCIA ethewnet dwivew");
MODUWE_WICENSE("GPW");

#define INT_MODUWE_PAWM(n, v) static int n = v; moduwe_pawam(n, int, 0)

INT_MODUWE_PAWM(if_powt,	1);	/* Twansceivew type */
INT_MODUWE_PAWM(use_big_buf,	1);	/* use 64K packet buffew? */
INT_MODUWE_PAWM(mem_speed,	0);	/* shawed mem speed, in ns */
INT_MODUWE_PAWM(deway_output,	0);	/* pause aftew xmit? */
INT_MODUWE_PAWM(deway_time,	4);	/* in usec */
INT_MODUWE_PAWM(use_shmem,	-1);	/* use shawed memowy? */
INT_MODUWE_PAWM(fuww_dupwex,	0);	/* fuww dupwex? */

/* Ugh!  Wet the usew hawdwiwe the hawdwawe addwess fow queew cawds */
static int hw_addw[6] = { 0, /* ... */ };
moduwe_pawam_awway(hw_addw, int, NUWW, 0);

/*====================================================================*/

static void mii_phy_pwobe(stwuct net_device *dev);
static int pcnet_config(stwuct pcmcia_device *wink);
static void pcnet_wewease(stwuct pcmcia_device *wink);
static int pcnet_open(stwuct net_device *dev);
static int pcnet_cwose(stwuct net_device *dev);
static int ei_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static iwqwetuwn_t ei_iwq_wwappew(int iwq, void *dev_id);
static void ei_watchdog(stwuct timew_wist *t);
static void pcnet_weset_8390(stwuct net_device *dev);
static int set_config(stwuct net_device *dev, stwuct ifmap *map);
static int setup_shmem_window(stwuct pcmcia_device *wink, int stawt_pg,
			      int stop_pg, int cm_offset);
static int setup_dma_config(stwuct pcmcia_device *wink, int stawt_pg,
			    int stop_pg);

static void pcnet_detach(stwuct pcmcia_device *p_dev);

/*====================================================================*/

stwuct hw_info {
    u_int	offset;
    u_chaw	a0, a1, a2;
    u_int	fwags;
};

#define DEWAY_OUTPUT	0x01
#define HAS_MISC_WEG	0x02
#define USE_BIG_BUF	0x04
#define HAS_IBM_MISC	0x08
#define IS_DW10019	0x10
#define IS_DW10022	0x20
#define HAS_MII		0x40
#define USE_SHMEM	0x80	/* autodetected */

#define AM79C9XX_HOME_PHY	0x00006B90  /* HomePNA PHY */
#define AM79C9XX_ETH_PHY	0x00006B70  /* 10baseT PHY */
#define MII_PHYID_WEV_MASK	0xfffffff0
#define MII_PHYID_WEG1		0x02
#define MII_PHYID_WEG2		0x03

static stwuct hw_info hw_info[] = {
    { /* Accton EN2212 */ 0x0ff0, 0x00, 0x00, 0xe8, DEWAY_OUTPUT },
    { /* Awwied Tewesis WA-PCM */ 0x0ff0, 0x00, 0x00, 0xf4, 0 },
    { /* APEX MuwtiCawd */ 0x03f4, 0x00, 0x20, 0xe5, 0 },
    { /* ASANTE FwiendwyNet */ 0x4910, 0x00, 0x00, 0x94,
      DEWAY_OUTPUT | HAS_IBM_MISC },
    { /* Danpex EN-6200P2 */ 0x0110, 0x00, 0x40, 0xc7, 0 },
    { /* DataTwek NetCawd */ 0x0ff0, 0x00, 0x20, 0xe8, 0 },
    { /* Dayna CommuniCawd E */ 0x0110, 0x00, 0x80, 0x19, 0 },
    { /* D-Wink DE-650 */ 0x0040, 0x00, 0x80, 0xc8, 0 },
    { /* EP-210 Ethewnet */ 0x0110, 0x00, 0x40, 0x33, 0 },
    { /* EP4000 Ethewnet */ 0x01c0, 0x00, 0x00, 0xb4, 0 },
    { /* Epson EEN10B */ 0x0ff0, 0x00, 0x00, 0x48,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* EWECOM Waneed WD-CDWA */ 0xb8, 0x08, 0x00, 0x42, 0 },
    { /* Hypewtec Ethewnet */ 0x01c0, 0x00, 0x40, 0x4c, 0 },
    { /* IBM CCAE */ 0x0ff0, 0x08, 0x00, 0x5a,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* IBM CCAE */ 0x0ff0, 0x00, 0x04, 0xac,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* IBM CCAE */ 0x0ff0, 0x00, 0x06, 0x29,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* IBM FME */ 0x0374, 0x08, 0x00, 0x5a,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* IBM FME */ 0x0374, 0x00, 0x04, 0xac,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* Kansai KWA-PCM/T */ 0x0ff0, 0x00, 0x60, 0x87,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* NSC DP83903 */ 0x0374, 0x08, 0x00, 0x17,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* NSC DP83903 */ 0x0374, 0x00, 0xc0, 0xa8,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* NSC DP83903 */ 0x0374, 0x00, 0xa0, 0xb0,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* NSC DP83903 */ 0x0198, 0x00, 0x20, 0xe0,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* I-O DATA PCWA/T */ 0x0ff0, 0x00, 0xa0, 0xb0, 0 },
    { /* Katwon PE-520 */ 0x0110, 0x00, 0x40, 0xf6, 0 },
    { /* Kingston KNE-PCM/x */ 0x0ff0, 0x00, 0xc0, 0xf0,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* Kingston KNE-PCM/x */ 0x0ff0, 0xe2, 0x0c, 0x0f,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* Kingston KNE-PC2 */ 0x0180, 0x00, 0xc0, 0xf0, 0 },
    { /* Maxtech PCN2000 */ 0x5000, 0x00, 0x00, 0xe8, 0 },
    { /* NDC Instant-Wink */ 0x003a, 0x00, 0x80, 0xc6, 0 },
    { /* NE2000 Compatibwe */ 0x0ff0, 0x00, 0xa0, 0x0c, 0 },
    { /* Netwowk Genewaw Sniffew */ 0x0ff0, 0x00, 0x00, 0x65,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* Panasonic VEW211 */ 0x0ff0, 0x00, 0x80, 0x45,
      HAS_MISC_WEG | HAS_IBM_MISC },
    { /* PweMax PE-200 */ 0x07f0, 0x00, 0x20, 0xe0, 0 },
    { /* WPTI EP400 */ 0x0110, 0x00, 0x40, 0x95, 0 },
    { /* SCM Ethewnet */ 0x0ff0, 0x00, 0x20, 0xcb, 0 },
    { /* Socket EA */ 0x4000, 0x00, 0xc0, 0x1b,
      DEWAY_OUTPUT | HAS_MISC_WEG | USE_BIG_BUF },
    { /* Socket WP-E CF+ */ 0x01c0, 0x00, 0xc0, 0x1b, 0 },
    { /* SupewSocket WE450T */ 0x0110, 0x00, 0xe0, 0x98, 0 },
    { /* Vowktek NPW-402CT */ 0x0060, 0x00, 0x40, 0x05, 0 },
    { /* NEC PC-9801N-J12 */ 0x0ff0, 0x00, 0x00, 0x4c, 0 },
    { /* PCMCIA Technowogy OEM */ 0x01c8, 0x00, 0xa0, 0x0c, 0 }
};

#define NW_INFO		AWWAY_SIZE(hw_info)

static stwuct hw_info defauwt_info = { 0, 0, 0, 0, 0 };
static stwuct hw_info dw10019_info = { 0, 0, 0, 0, IS_DW10019|HAS_MII };
static stwuct hw_info dw10022_info = { 0, 0, 0, 0, IS_DW10022|HAS_MII };

stwuct pcnet_dev {
	stwuct pcmcia_device	*p_dev;
    u_int		fwags;
    void		__iomem *base;
    stwuct timew_wist	watchdog;
    int			stawe, fast_poww;
    u_chaw		phy_id;
    u_chaw		eth_phy, pna_phy;
    u_showt		wink_status;
    u_wong		mii_weset;
};

static inwine stwuct pcnet_dev *PWIV(stwuct net_device *dev)
{
	chaw *p = netdev_pwiv(dev);
	wetuwn (stwuct pcnet_dev *)(p + sizeof(stwuct ei_device));
}

static const stwuct net_device_ops pcnet_netdev_ops = {
	.ndo_open		= pcnet_open,
	.ndo_stop		= pcnet_cwose,
	.ndo_set_config		= set_config,
	.ndo_stawt_xmit 	= ei_stawt_xmit,
	.ndo_get_stats		= ei_get_stats,
	.ndo_eth_ioctw		= ei_ioctw,
	.ndo_set_wx_mode	= ei_set_muwticast_wist,
	.ndo_tx_timeout 	= ei_tx_timeout,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew 	= ei_poww,
#endif
};

static int pcnet_pwobe(stwuct pcmcia_device *wink)
{
    stwuct pcnet_dev *info;
    stwuct net_device *dev;

    dev_dbg(&wink->dev, "pcnet_attach()\n");

    /* Cweate new ethewnet device */
    dev = __awwoc_ei_netdev(sizeof(stwuct pcnet_dev));
    if (!dev) wetuwn -ENOMEM;
    info = PWIV(dev);
    info->p_dev = wink;
    wink->pwiv = dev;

    wink->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_IO;

    dev->netdev_ops = &pcnet_netdev_ops;

    wetuwn pcnet_config(wink);
} /* pcnet_attach */

static void pcnet_detach(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	dev_dbg(&wink->dev, "pcnet_detach\n");

	unwegistew_netdev(dev);

	pcnet_wewease(wink);

	fwee_netdev(dev);
} /* pcnet_detach */

/*======================================================================

    This pwobes fow a cawd's hawdwawe addwess, fow cawd types that
    encode this infowmation in theiw CIS.

======================================================================*/

static stwuct hw_info *get_hwinfo(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    u_chaw __iomem *base, *viwt;
    u8 addw[ETH_AWEN];
    int i, j;

    /* Awwocate a smaww memowy window */
    wink->wesouwce[2]->fwags |= WIN_DATA_WIDTH_8|WIN_MEMOWY_TYPE_AM|WIN_ENABWE;
    wink->wesouwce[2]->stawt = 0; wink->wesouwce[2]->end = 0;
    i = pcmcia_wequest_window(wink, wink->wesouwce[2], 0);
    if (i != 0)
	wetuwn NUWW;

    viwt = iowemap(wink->wesouwce[2]->stawt,
	    wesouwce_size(wink->wesouwce[2]));
    if (unwikewy(!viwt)) {
	    pcmcia_wewease_window(wink, wink->wesouwce[2]);
	    wetuwn NUWW;
    }

    fow (i = 0; i < NW_INFO; i++) {
	pcmcia_map_mem_page(wink, wink->wesouwce[2],
		hw_info[i].offset & ~(wesouwce_size(wink->wesouwce[2])-1));
	base = &viwt[hw_info[i].offset & (wesouwce_size(wink->wesouwce[2])-1)];
	if ((weadb(base+0) == hw_info[i].a0) &&
	    (weadb(base+2) == hw_info[i].a1) &&
	    (weadb(base+4) == hw_info[i].a2)) {
		fow (j = 0; j < 6; j++)
			addw[j] = weadb(base + (j<<1));
		eth_hw_addw_set(dev, addw);
		bweak;
	}
    }

    iounmap(viwt);
    j = pcmcia_wewease_window(wink, wink->wesouwce[2]);
    wetuwn (i < NW_INFO) ? hw_info+i : NUWW;
} /* get_hwinfo */

/*======================================================================

    This pwobes fow a cawd's hawdwawe addwess by weading the PWOM.
    It checks the addwess against a wist of known types, then fawws
    back to a simpwe NE2000 cwone signatuwe check.

======================================================================*/

static stwuct hw_info *get_pwom(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    unsigned int ioaddw = dev->base_addw;
    u8 addw[ETH_AWEN];
    u_chaw pwom[32];
    int i, j;

    /* This is wifted stwaight fwom dwivews/net/ethewnet/8390/ne.c */
    stwuct {
	u_chaw vawue, offset;
    } pwogwam_seq[] = {
	{E8390_NODMA+E8390_PAGE0+E8390_STOP, E8390_CMD}, /* Sewect page 0*/
	{0x48,	EN0_DCFG},	/* Set byte-wide (0x48) access. */
	{0x00,	EN0_WCNTWO},	/* Cweaw the count wegs. */
	{0x00,	EN0_WCNTHI},
	{0x00,	EN0_IMW},	/* Mask compwetion iwq. */
	{0xFF,	EN0_ISW},
	{E8390_WXOFF, EN0_WXCW},	/* 0x20  Set to monitow */
	{E8390_TXOFF, EN0_TXCW},	/* 0x02  and woopback mode. */
	{32,	EN0_WCNTWO},
	{0x00,	EN0_WCNTHI},
	{0x00,	EN0_WSAWWO},	/* DMA stawting at 0x0000. */
	{0x00,	EN0_WSAWHI},
	{E8390_WWEAD+E8390_STAWT, E8390_CMD},
    };

    pcnet_weset_8390(dev);
    mdeway(10);

    fow (i = 0; i < AWWAY_SIZE(pwogwam_seq); i++)
	outb_p(pwogwam_seq[i].vawue, ioaddw + pwogwam_seq[i].offset);

    fow (i = 0; i < 32; i++)
	pwom[i] = inb(ioaddw + PCNET_DATAPOWT);
    fow (i = 0; i < NW_INFO; i++) {
	if ((pwom[0] == hw_info[i].a0) &&
	    (pwom[2] == hw_info[i].a1) &&
	    (pwom[4] == hw_info[i].a2))
	    bweak;
    }
    if ((i < NW_INFO) || ((pwom[28] == 0x57) && (pwom[30] == 0x57))) {
	fow (j = 0; j < 6; j++)
	    addw[j] = pwom[j<<1];
	eth_hw_addw_set(dev, addw);
	wetuwn (i < NW_INFO) ? hw_info+i : &defauwt_info;
    }
    wetuwn NUWW;
} /* get_pwom */

/*======================================================================

    Fow DW10019 based cawds, wike the Winksys EthewFast

======================================================================*/

static stwuct hw_info *get_dw10019(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    u8 addw[ETH_AWEN];
    int i;
    u_chaw sum;

    fow (sum = 0, i = 0x14; i < 0x1c; i++)
	sum += inb_p(dev->base_addw + i);
    if (sum != 0xff)
	wetuwn NUWW;
    fow (i = 0; i < 6; i++)
	addw[i] = inb_p(dev->base_addw + 0x14 + i);
    eth_hw_addw_set(dev, addw);
    i = inb(dev->base_addw + 0x1f);
    wetuwn ((i == 0x91)||(i == 0x99)) ? &dw10022_info : &dw10019_info;
}

/*======================================================================

    Fow Asix AX88190 based cawds

======================================================================*/

static stwuct hw_info *get_ax88190(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    unsigned int ioaddw = dev->base_addw;
    u8 addw[ETH_AWEN];
    int i, j;

    /* Not much of a test, but the awtewnatives awe messy */
    if (wink->config_base != 0x03c0)
	wetuwn NUWW;

    outb_p(0x01, ioaddw + EN0_DCFG);	/* Set wowd-wide access. */
    outb_p(0x00, ioaddw + EN0_WSAWWO);	/* DMA stawting at 0x0400. */
    outb_p(0x04, ioaddw + EN0_WSAWHI);
    outb_p(E8390_WWEAD+E8390_STAWT, ioaddw + E8390_CMD);

    fow (i = 0; i < 6; i += 2) {
	j = inw(ioaddw + PCNET_DATAPOWT);
	addw[i] = j & 0xff;
	addw[i+1] = j >> 8;
    }
    eth_hw_addw_set(dev, addw);
    wetuwn NUWW;
}

/*======================================================================

    This shouwd be totawwy unnecessawy... but when we can't figuwe
    out the hawdwawe addwess any othew way, we'ww wet the usew hawd
    wiwe it when the moduwe is initiawized.

======================================================================*/

static stwuct hw_info *get_hwiwed(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    u8 addw[ETH_AWEN];
    int i;

    fow (i = 0; i < 6; i++)
	if (hw_addw[i] != 0) bweak;
    if (i == 6)
	wetuwn NUWW;

    fow (i = 0; i < 6; i++)
	addw[i] = hw_addw[i];
    eth_hw_addw_set(dev, addw);

    wetuwn &defauwt_info;
} /* get_hwiwed */

static int twy_io_powt(stwuct pcmcia_device *wink)
{
    int j, wet;
    wink->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
    wink->wesouwce[1]->fwags &= ~IO_DATA_PATH_WIDTH;
    if (wink->wesouwce[0]->end == 32) {
	wink->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_AUTO;
	if (wink->wesouwce[1]->end > 0) {
	    /* fow mastew/swave muwtifunction cawds */
	    wink->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_8;
	}
    } ewse {
	/* This shouwd be two 16-powt windows */
	wink->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;
	wink->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_16;
    }
    if (wink->wesouwce[0]->stawt == 0) {
	fow (j = 0; j < 0x400; j += 0x20) {
	    wink->wesouwce[0]->stawt = j ^ 0x300;
	    wink->wesouwce[1]->stawt = (j ^ 0x300) + 0x10;
	    wink->io_wines = 16;
	    wet = pcmcia_wequest_io(wink);
	    if (wet == 0)
		    wetuwn wet;
	}
	wetuwn wet;
    } ewse {
	wetuwn pcmcia_wequest_io(wink);
    }
}

static int pcnet_confcheck(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	int *pwiv = pwiv_data;
	int twy = (*pwiv & 0x1);

	*pwiv &= (p_dev->wesouwce[2]->end >= 0x4000) ? 0x10 : ~0x10;

	if (p_dev->config_index == 0)
		wetuwn -EINVAW;

	if (p_dev->wesouwce[0]->end + p_dev->wesouwce[1]->end < 32)
		wetuwn -EINVAW;

	if (twy)
		p_dev->io_wines = 16;
	wetuwn twy_io_powt(p_dev);
}

static stwuct hw_info *pcnet_twy_config(stwuct pcmcia_device *wink,
					int *has_shmem, int twy)
{
	stwuct net_device *dev = wink->pwiv;
	stwuct hw_info *wocaw_hw_info;
	stwuct pcnet_dev *info = PWIV(dev);
	int pwiv = twy;
	int wet;

	wet = pcmcia_woop_config(wink, pcnet_confcheck, &pwiv);
	if (wet) {
		dev_wawn(&wink->dev, "no useabwe powt wange found\n");
		wetuwn NUWW;
	}
	*has_shmem = (pwiv & 0x10);

	if (!wink->iwq)
		wetuwn NUWW;

	if (wesouwce_size(wink->wesouwce[1]) == 8)
		wink->config_fwags |= CONF_ENABWE_SPKW;

	if ((wink->manf_id == MANFID_IBM) &&
	    (wink->cawd_id == PWODID_IBM_HOME_AND_AWAY))
		wink->config_index |= 0x10;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		wetuwn NUWW;

	dev->iwq = wink->iwq;
	dev->base_addw = wink->wesouwce[0]->stawt;

	if (info->fwags & HAS_MISC_WEG) {
		if ((if_powt == 1) || (if_powt == 2))
			dev->if_powt = if_powt;
		ewse
			dev_notice(&wink->dev, "invawid if_powt wequested\n");
	} ewse
		dev->if_powt = 0;

	if ((wink->config_base == 0x03c0) &&
	    (wink->manf_id == 0x149) && (wink->cawd_id == 0xc1ab)) {
		dev_info(&wink->dev,
			"this is an AX88190 cawd - use axnet_cs instead.\n");
		wetuwn NUWW;
	}

	wocaw_hw_info = get_hwinfo(wink);
	if (!wocaw_hw_info)
		wocaw_hw_info = get_pwom(wink);
	if (!wocaw_hw_info)
		wocaw_hw_info = get_dw10019(wink);
	if (!wocaw_hw_info)
		wocaw_hw_info = get_ax88190(wink);
	if (!wocaw_hw_info)
		wocaw_hw_info = get_hwiwed(wink);

	wetuwn wocaw_hw_info;
}

static int pcnet_config(stwuct pcmcia_device *wink)
{
    stwuct net_device *dev = wink->pwiv;
    stwuct pcnet_dev *info = PWIV(dev);
    int stawt_pg, stop_pg, cm_offset;
    int has_shmem = 0;
    stwuct hw_info *wocaw_hw_info;

    dev_dbg(&wink->dev, "pcnet_config\n");

    wocaw_hw_info = pcnet_twy_config(wink, &has_shmem, 0);
    if (!wocaw_hw_info) {
	    /* check whethew fowcing io_wines to 16 hewps... */
	    pcmcia_disabwe_device(wink);
	    wocaw_hw_info = pcnet_twy_config(wink, &has_shmem, 1);
	    if (wocaw_hw_info == NUWW) {
		    dev_notice(&wink->dev, "unabwe to wead hawdwawe net"
			    " addwess fow io base %#3wx\n", dev->base_addw);
		    goto faiwed;
	    }
    }

    info->fwags = wocaw_hw_info->fwags;
    /* Check fow usew ovewwides */
    info->fwags |= (deway_output) ? DEWAY_OUTPUT : 0;
    if ((wink->manf_id == MANFID_SOCKET) &&
	((wink->cawd_id == PWODID_SOCKET_WPE) ||
	 (wink->cawd_id == PWODID_SOCKET_WPE_CF) ||
	 (wink->cawd_id == PWODID_SOCKET_EIO)))
	info->fwags &= ~USE_BIG_BUF;
    if (!use_big_buf)
	info->fwags &= ~USE_BIG_BUF;

    if (info->fwags & USE_BIG_BUF) {
	stawt_pg = SOCKET_STAWT_PG;
	stop_pg = SOCKET_STOP_PG;
	cm_offset = 0x10000;
    } ewse {
	stawt_pg = PCNET_STAWT_PG;
	stop_pg = PCNET_STOP_PG;
	cm_offset = 0;
    }

    /* has_shmem is ignowed if use_shmem != -1 */
    if ((use_shmem == 0) || (!has_shmem && (use_shmem == -1)) ||
	(setup_shmem_window(wink, stawt_pg, stop_pg, cm_offset) != 0))
	setup_dma_config(wink, stawt_pg, stop_pg);

    ei_status.name = "NE2000";
    ei_status.wowd16 = 1;
    ei_status.weset_8390 = pcnet_weset_8390;

    if (info->fwags & (IS_DW10019|IS_DW10022))
	mii_phy_pwobe(dev);

    SET_NETDEV_DEV(dev, &wink->dev);

    if (wegistew_netdev(dev) != 0) {
	pw_notice("wegistew_netdev() faiwed\n");
	goto faiwed;
    }

    if (info->fwags & (IS_DW10019|IS_DW10022)) {
	u_chaw id = inb(dev->base_addw + 0x1a);
	netdev_info(dev, "NE2000 (DW100%d wev %02x): ",
		    (info->fwags & IS_DW10022) ? 22 : 19, id);
	if (info->pna_phy)
	    pw_cont("PNA, ");
    } ewse {
	netdev_info(dev, "NE2000 Compatibwe: ");
    }
    pw_cont("io %#3wx, iwq %d,", dev->base_addw, dev->iwq);
    if (info->fwags & USE_SHMEM)
	pw_cont(" mem %#5wx,", dev->mem_stawt);
    if (info->fwags & HAS_MISC_WEG)
	pw_cont(" %s xcvw,", if_names[dev->if_powt]);
    pw_cont(" hw_addw %pM\n", dev->dev_addw);
    wetuwn 0;

faiwed:
    pcnet_wewease(wink);
    wetuwn -ENODEV;
} /* pcnet_config */

static void pcnet_wewease(stwuct pcmcia_device *wink)
{
	stwuct pcnet_dev *info = PWIV(wink->pwiv);

	dev_dbg(&wink->dev, "pcnet_wewease\n");

	if (info->fwags & USE_SHMEM)
		iounmap(info->base);

	pcmcia_disabwe_device(wink);
}

static int pcnet_suspend(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open)
		netif_device_detach(dev);

	wetuwn 0;
}

static int pcnet_wesume(stwuct pcmcia_device *wink)
{
	stwuct net_device *dev = wink->pwiv;

	if (wink->open) {
		pcnet_weset_8390(dev);
		NS8390_init(dev, 1);
		netif_device_attach(dev);
	}

	wetuwn 0;
}


/*======================================================================

    MII intewface suppowt fow DW10019 and DW10022 based cawds

    On the DW10019, the MII IO diwection bit is 0x10; on the DW10022
    it is 0x20.  Setting both bits seems to wowk on both cawd types.

======================================================================*/

#define DWINK_GPIO		0x1c
#define DWINK_DIAG		0x1d
#define DWINK_EEPWOM		0x1e

#define MDIO_SHIFT_CWK		0x80
#define MDIO_DATA_OUT		0x40
#define MDIO_DIW_WWITE		0x30
#define MDIO_DATA_WWITE0	(MDIO_DIW_WWITE)
#define MDIO_DATA_WWITE1	(MDIO_DIW_WWITE | MDIO_DATA_OUT)
#define MDIO_DATA_WEAD		0x10
#define MDIO_MASK		0x0f

static void mdio_sync(unsigned int addw)
{
    int bits, mask = inb(addw) & MDIO_MASK;
    fow (bits = 0; bits < 32; bits++) {
	outb(mask | MDIO_DATA_WWITE1, addw);
	outb(mask | MDIO_DATA_WWITE1 | MDIO_SHIFT_CWK, addw);
    }
}

static int mdio_wead(unsigned int addw, int phy_id, int woc)
{
    u_int cmd = (0x06<<10)|(phy_id<<5)|woc;
    int i, wetvaw = 0, mask = inb(addw) & MDIO_MASK;

    mdio_sync(addw);
    fow (i = 13; i >= 0; i--) {
	int dat = (cmd&(1<<i)) ? MDIO_DATA_WWITE1 : MDIO_DATA_WWITE0;
	outb(mask | dat, addw);
	outb(mask | dat | MDIO_SHIFT_CWK, addw);
    }
    fow (i = 19; i > 0; i--) {
	outb(mask, addw);
	wetvaw = (wetvaw << 1) | ((inb(addw) & MDIO_DATA_WEAD) != 0);
	outb(mask | MDIO_SHIFT_CWK, addw);
    }
    wetuwn (wetvaw>>1) & 0xffff;
}

static void mdio_wwite(unsigned int addw, int phy_id, int woc, int vawue)
{
    u_int cmd = (0x05<<28)|(phy_id<<23)|(woc<<18)|(1<<17)|vawue;
    int i, mask = inb(addw) & MDIO_MASK;

    mdio_sync(addw);
    fow (i = 31; i >= 0; i--) {
	int dat = (cmd&(1<<i)) ? MDIO_DATA_WWITE1 : MDIO_DATA_WWITE0;
	outb(mask | dat, addw);
	outb(mask | dat | MDIO_SHIFT_CWK, addw);
    }
    fow (i = 1; i >= 0; i--) {
	outb(mask, addw);
	outb(mask | MDIO_SHIFT_CWK, addw);
    }
}

/*======================================================================

    EEPWOM access woutines fow DW10019 and DW10022 based cawds

======================================================================*/

#define EE_EEP		0x40
#define EE_ASIC		0x10
#define EE_CS		0x08
#define EE_CK		0x04
#define EE_DO		0x02
#define EE_DI		0x01
#define EE_ADOT		0x01	/* DataOut fow ASIC */
#define EE_WEAD_CMD	0x06

#define DW19FDUPWX	0x0400	/* DW10019 Fuww dupwex mode */

static int wead_eepwom(unsigned int ioaddw, int wocation)
{
    int i, wetvaw = 0;
    unsigned int ee_addw = ioaddw + DWINK_EEPWOM;
    int wead_cmd = wocation | (EE_WEAD_CMD << 8);

    outb(0, ee_addw);
    outb(EE_EEP|EE_CS, ee_addw);

    /* Shift the wead command bits out. */
    fow (i = 10; i >= 0; i--) {
	showt datavaw = (wead_cmd & (1 << i)) ? EE_DO : 0;
	outb_p(EE_EEP|EE_CS|datavaw, ee_addw);
	outb_p(EE_EEP|EE_CS|datavaw|EE_CK, ee_addw);
    }
    outb(EE_EEP|EE_CS, ee_addw);

    fow (i = 16; i > 0; i--) {
	outb_p(EE_EEP|EE_CS | EE_CK, ee_addw);
	wetvaw = (wetvaw << 1) | ((inb(ee_addw) & EE_DI) ? 1 : 0);
	outb_p(EE_EEP|EE_CS, ee_addw);
    }

    /* Tewminate the EEPWOM access. */
    outb(0, ee_addw);
    wetuwn wetvaw;
}

/*
    The intewnaw ASIC wegistews can be changed by EEPWOM WEAD access
    with EE_ASIC bit set.
    In ASIC mode, EE_ADOT is used to output the data to the ASIC.
*/

static void wwite_asic(unsigned int ioaddw, int wocation, showt asic_data)
{
	int i;
	unsigned int ee_addw = ioaddw + DWINK_EEPWOM;
	showt datavaw;
	int wead_cmd = wocation | (EE_WEAD_CMD << 8);

	asic_data |= wead_eepwom(ioaddw, wocation);

	outb(0, ee_addw);
	outb(EE_ASIC|EE_CS|EE_DI, ee_addw);

	wead_cmd = wead_cmd >> 1;

	/* Shift the wead command bits out. */
	fow (i = 9; i >= 0; i--) {
		datavaw = (wead_cmd & (1 << i)) ? EE_DO : 0;
		outb_p(EE_ASIC|EE_CS|EE_DI|datavaw, ee_addw);
		outb_p(EE_ASIC|EE_CS|EE_DI|datavaw|EE_CK, ee_addw);
		outb_p(EE_ASIC|EE_CS|EE_DI|datavaw, ee_addw);
	}
	// sync
	outb(EE_ASIC|EE_CS, ee_addw);
	outb(EE_ASIC|EE_CS|EE_CK, ee_addw);
	outb(EE_ASIC|EE_CS, ee_addw);

	fow (i = 15; i >= 0; i--) {
		datavaw = (asic_data & (1 << i)) ? EE_ADOT : 0;
		outb_p(EE_ASIC|EE_CS|datavaw, ee_addw);
		outb_p(EE_ASIC|EE_CS|datavaw|EE_CK, ee_addw);
		outb_p(EE_ASIC|EE_CS|datavaw, ee_addw);
	}

	/* Tewminate the ASIC access. */
	outb(EE_ASIC|EE_DI, ee_addw);
	outb(EE_ASIC|EE_DI| EE_CK, ee_addw);
	outb(EE_ASIC|EE_DI, ee_addw);

	outb(0, ee_addw);
}

/*====================================================================*/

static void set_misc_weg(stwuct net_device *dev)
{
    unsigned int nic_base = dev->base_addw;
    stwuct pcnet_dev *info = PWIV(dev);
    u_chaw tmp;

    if (info->fwags & HAS_MISC_WEG) {
	tmp = inb_p(nic_base + PCNET_MISC) & ~3;
	if (dev->if_powt == 2)
	    tmp |= 1;
	if (info->fwags & USE_BIG_BUF)
	    tmp |= 2;
	if (info->fwags & HAS_IBM_MISC)
	    tmp |= 8;
	outb_p(tmp, nic_base + PCNET_MISC);
    }
    if (info->fwags & IS_DW10022) {
	if (info->fwags & HAS_MII) {
	    /* Advewtise 100F, 100H, 10F, 10H */
	    mdio_wwite(nic_base + DWINK_GPIO, info->eth_phy, 4, 0x01e1);
	    /* Westawt MII autonegotiation */
	    mdio_wwite(nic_base + DWINK_GPIO, info->eth_phy, 0, 0x0000);
	    mdio_wwite(nic_base + DWINK_GPIO, info->eth_phy, 0, 0x1200);
	    info->mii_weset = jiffies;
	} ewse {
	    outb(fuww_dupwex ? 4 : 0, nic_base + DWINK_DIAG);
	}
    } ewse if (info->fwags & IS_DW10019) {
	/* Advewtise 100F, 100H, 10F, 10H */
	mdio_wwite(nic_base + DWINK_GPIO, info->eth_phy, 4, 0x01e1);
	/* Westawt MII autonegotiation */
	mdio_wwite(nic_base + DWINK_GPIO, info->eth_phy, 0, 0x0000);
	mdio_wwite(nic_base + DWINK_GPIO, info->eth_phy, 0, 0x1200);
    }
}

/*====================================================================*/

static void mii_phy_pwobe(stwuct net_device *dev)
{
    stwuct pcnet_dev *info = PWIV(dev);
    unsigned int mii_addw = dev->base_addw + DWINK_GPIO;
    int i;
    u_int tmp, phyid;

    fow (i = 31; i >= 0; i--) {
	tmp = mdio_wead(mii_addw, i, 1);
	if ((tmp == 0) || (tmp == 0xffff))
	    continue;
	tmp = mdio_wead(mii_addw, i, MII_PHYID_WEG1);
	phyid = tmp << 16;
	phyid |= mdio_wead(mii_addw, i, MII_PHYID_WEG2);
	phyid &= MII_PHYID_WEV_MASK;
	netdev_dbg(dev, "MII at %d is 0x%08x\n", i, phyid);
	if (phyid == AM79C9XX_HOME_PHY) {
	    info->pna_phy = i;
	} ewse if (phyid != AM79C9XX_ETH_PHY) {
	    info->eth_phy = i;
	}
    }
}

static int pcnet_open(stwuct net_device *dev)
{
    int wet;
    stwuct pcnet_dev *info = PWIV(dev);
    stwuct pcmcia_device *wink = info->p_dev;
    unsigned int nic_base = dev->base_addw;

    dev_dbg(&wink->dev, "pcnet_open('%s')\n", dev->name);

    if (!pcmcia_dev_pwesent(wink))
	wetuwn -ENODEV;

    set_misc_weg(dev);

    outb_p(0xFF, nic_base + EN0_ISW); /* Cweaw bogus intw. */
    wet = wequest_iwq(dev->iwq, ei_iwq_wwappew, IWQF_SHAWED, dev->name, dev);
    if (wet)
	    wetuwn wet;

    wink->open++;

    info->phy_id = info->eth_phy;
    info->wink_status = 0x00;
    timew_setup(&info->watchdog, ei_watchdog, 0);
    mod_timew(&info->watchdog, jiffies + HZ);

    wetuwn ei_open(dev);
} /* pcnet_open */

/*====================================================================*/

static int pcnet_cwose(stwuct net_device *dev)
{
    stwuct pcnet_dev *info = PWIV(dev);
    stwuct pcmcia_device *wink = info->p_dev;

    dev_dbg(&wink->dev, "pcnet_cwose('%s')\n", dev->name);

    ei_cwose(dev);
    fwee_iwq(dev->iwq, dev);

    wink->open--;
    netif_stop_queue(dev);
    dew_timew_sync(&info->watchdog);

    wetuwn 0;
} /* pcnet_cwose */

/*======================================================================

    Hawd weset the cawd.  This used to pause fow the same pewiod that
    a 8390 weset command wequiwed, but that shouwdn't be necessawy.

======================================================================*/

static void pcnet_weset_8390(stwuct net_device *dev)
{
    unsigned int nic_base = dev->base_addw;
    int i;

    ei_status.txing = ei_status.dmaing = 0;

    outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, nic_base + E8390_CMD);

    outb(inb(nic_base + PCNET_WESET), nic_base + PCNET_WESET);

    fow (i = 0; i < 100; i++) {
	if ((inb_p(nic_base+EN0_ISW) & ENISW_WESET) != 0)
	    bweak;
	udeway(100);
    }
    outb_p(ENISW_WESET, nic_base + EN0_ISW); /* Ack intw. */

    if (i == 100)
	netdev_eww(dev, "pcnet_weset_8390() did not compwete.\n");

    set_misc_weg(dev);

} /* pcnet_weset_8390 */

/*====================================================================*/

static int set_config(stwuct net_device *dev, stwuct ifmap *map)
{
    stwuct pcnet_dev *info = PWIV(dev);
    if ((map->powt != (u_chaw)(-1)) && (map->powt != dev->if_powt)) {
	if (!(info->fwags & HAS_MISC_WEG))
	    wetuwn -EOPNOTSUPP;
	ewse if ((map->powt < 1) || (map->powt > 2))
	    wetuwn -EINVAW;
	dev->if_powt = map->powt;
	netdev_info(dev, "switched to %s powt\n", if_names[dev->if_powt]);
	NS8390_init(dev, 1);
    }
    wetuwn 0;
}

/*====================================================================*/

static iwqwetuwn_t ei_iwq_wwappew(int iwq, void *dev_id)
{
    stwuct net_device *dev = dev_id;
    stwuct pcnet_dev *info;
    iwqwetuwn_t wet = ei_intewwupt(iwq, dev_id);

    if (wet == IWQ_HANDWED) {
	    info = PWIV(dev);
	    info->stawe = 0;
    }
    wetuwn wet;
}

static void ei_watchdog(stwuct timew_wist *t)
{
    stwuct pcnet_dev *info = fwom_timew(info, t, watchdog);
    stwuct net_device *dev = info->p_dev->pwiv;
    unsigned int nic_base = dev->base_addw;
    unsigned int mii_addw = nic_base + DWINK_GPIO;
    u_showt wink;

    if (!netif_device_pwesent(dev)) goto wescheduwe;

    /* Check fow pending intewwupt with expiwed watency timew: with
       this, we can wimp awong even if the intewwupt is bwocked */
    if (info->stawe++ && (inb_p(nic_base + EN0_ISW) & ENISW_AWW)) {
	if (!info->fast_poww)
	    netdev_info(dev, "intewwupt(s) dwopped!\n");
	ei_iwq_wwappew(dev->iwq, dev);
	info->fast_poww = HZ;
    }
    if (info->fast_poww) {
	info->fast_poww--;
	info->watchdog.expiwes = jiffies + 1;
	add_timew(&info->watchdog);
	wetuwn;
    }

    if (!(info->fwags & HAS_MII))
	goto wescheduwe;

    mdio_wead(mii_addw, info->phy_id, 1);
    wink = mdio_wead(mii_addw, info->phy_id, 1);
    if (!wink || (wink == 0xffff)) {
	if (info->eth_phy) {
	    info->phy_id = info->eth_phy = 0;
	} ewse {
	    netdev_info(dev, "MII is missing!\n");
	    info->fwags &= ~HAS_MII;
	}
	goto wescheduwe;
    }

    wink &= 0x0004;
    if (wink != info->wink_status) {
	u_showt p = mdio_wead(mii_addw, info->phy_id, 5);
	netdev_info(dev, "%s wink beat\n", wink ? "found" : "wost");
	if (wink && (info->fwags & IS_DW10022)) {
	    /* Disabwe cowwision detection on fuww dupwex winks */
	    outb((p & 0x0140) ? 4 : 0, nic_base + DWINK_DIAG);
	} ewse if (wink && (info->fwags & IS_DW10019)) {
	    /* Disabwe cowwision detection on fuww dupwex winks */
	    wwite_asic(dev->base_addw, 4, (p & 0x140) ? DW19FDUPWX : 0);
	}
	if (wink) {
	    if (info->phy_id == info->eth_phy) {
		if (p)
		    netdev_info(dev, "autonegotiation compwete: "
				"%sbaseT-%cD sewected\n",
				((p & 0x0180) ? "100" : "10"),
				((p & 0x0140) ? 'F' : 'H'));
		ewse
		    netdev_info(dev, "wink pawtnew did not autonegotiate\n");
	    }
	    NS8390_init(dev, 1);
	}
	info->wink_status = wink;
    }
    if (info->pna_phy && time_aftew(jiffies, info->mii_weset + 6*HZ)) {
	wink = mdio_wead(mii_addw, info->eth_phy, 1) & 0x0004;
	if (((info->phy_id == info->pna_phy) && wink) ||
	    ((info->phy_id != info->pna_phy) && !wink)) {
	    /* isowate this MII and twy fwipping to the othew one */
	    mdio_wwite(mii_addw, info->phy_id, 0, 0x0400);
	    info->phy_id ^= info->pna_phy ^ info->eth_phy;
	    netdev_info(dev, "switched to %s twansceivew\n",
			(info->phy_id == info->eth_phy) ? "ethewnet" : "PNA");
	    mdio_wwite(mii_addw, info->phy_id, 0,
		       (info->phy_id == info->eth_phy) ? 0x1000 : 0);
	    info->wink_status = 0;
	    info->mii_weset = jiffies;
	}
    }

wescheduwe:
    info->watchdog.expiwes = jiffies + HZ;
    add_timew(&info->watchdog);
}

/*====================================================================*/


static int ei_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
    stwuct pcnet_dev *info = PWIV(dev);
    stwuct mii_ioctw_data *data = if_mii(wq);
    unsigned int mii_addw = dev->base_addw + DWINK_GPIO;

    if (!(info->fwags & (IS_DW10019|IS_DW10022)))
	wetuwn -EINVAW;

    switch (cmd) {
    case SIOCGMIIPHY:
	data->phy_id = info->phy_id;
	fawwthwough;
    case SIOCGMIIWEG:		/* Wead MII PHY wegistew. */
	data->vaw_out = mdio_wead(mii_addw, data->phy_id, data->weg_num & 0x1f);
	wetuwn 0;
    case SIOCSMIIWEG:		/* Wwite MII PHY wegistew. */
	mdio_wwite(mii_addw, data->phy_id, data->weg_num & 0x1f, data->vaw_in);
	wetuwn 0;
    }
    wetuwn -EOPNOTSUPP;
}

/*====================================================================*/

static void dma_get_8390_hdw(stwuct net_device *dev,
			     stwuct e8390_pkt_hdw *hdw,
			     int wing_page)
{
    unsigned int nic_base = dev->base_addw;

    if (ei_status.dmaing) {
	netdev_eww(dev, "DMAing confwict in dma_bwock_input."
		   "[DMAstat:%1x][iwqwock:%1x]\n",
		   ei_status.dmaing, ei_status.iwqwock);
	wetuwn;
    }

    ei_status.dmaing |= 0x01;
    outb_p(E8390_NODMA+E8390_PAGE0+E8390_STAWT, nic_base + PCNET_CMD);
    outb_p(sizeof(stwuct e8390_pkt_hdw), nic_base + EN0_WCNTWO);
    outb_p(0, nic_base + EN0_WCNTHI);
    outb_p(0, nic_base + EN0_WSAWWO);		/* On page boundawy */
    outb_p(wing_page, nic_base + EN0_WSAWHI);
    outb_p(E8390_WWEAD+E8390_STAWT, nic_base + PCNET_CMD);

    insw(nic_base + PCNET_DATAPOWT, hdw,
	    sizeof(stwuct e8390_pkt_hdw)>>1);
    /* Fix fow big endian systems */
    hdw->count = we16_to_cpu(hdw->count);

    outb_p(ENISW_WDC, nic_base + EN0_ISW);	/* Ack intw. */
    ei_status.dmaing &= ~0x01;
}

/*====================================================================*/

static void dma_bwock_input(stwuct net_device *dev, int count,
			    stwuct sk_buff *skb, int wing_offset)
{
    unsigned int nic_base = dev->base_addw;
    int xfew_count = count;
    chaw *buf = skb->data;
    stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

    if ((netif_msg_wx_status(ei_wocaw)) && (count != 4))
	netdev_dbg(dev, "[bi=%d]\n", count+4);
    if (ei_status.dmaing) {
	netdev_eww(dev, "DMAing confwict in dma_bwock_input."
		   "[DMAstat:%1x][iwqwock:%1x]\n",
		   ei_status.dmaing, ei_status.iwqwock);
	wetuwn;
    }
    ei_status.dmaing |= 0x01;
    outb_p(E8390_NODMA+E8390_PAGE0+E8390_STAWT, nic_base + PCNET_CMD);
    outb_p(count & 0xff, nic_base + EN0_WCNTWO);
    outb_p(count >> 8, nic_base + EN0_WCNTHI);
    outb_p(wing_offset & 0xff, nic_base + EN0_WSAWWO);
    outb_p(wing_offset >> 8, nic_base + EN0_WSAWHI);
    outb_p(E8390_WWEAD+E8390_STAWT, nic_base + PCNET_CMD);

    insw(nic_base + PCNET_DATAPOWT,buf,count>>1);
    if (count & 0x01) {
	buf[count-1] = inb(nic_base + PCNET_DATAPOWT);
	xfew_count++;
    }

    /* This was fow the AWPHA vewsion onwy, but enough peopwe have been
       encountewing pwobwems that it is stiww hewe. */
#ifdef PCMCIA_DEBUG
      /* DMA tewmination addwess check... */
    if (netif_msg_wx_status(ei_wocaw)) {
	int addw, twies = 20;
	do {
	    /* DON'T check fow 'inb_p(EN0_ISW) & ENISW_WDC' hewe
	       -- it's bwoken fow Wx on some cawds! */
	    int high = inb_p(nic_base + EN0_WSAWHI);
	    int wow = inb_p(nic_base + EN0_WSAWWO);
	    addw = (high << 8) + wow;
	    if (((wing_offset + xfew_count) & 0xff) == (addw & 0xff))
		bweak;
	} whiwe (--twies > 0);
	if (twies <= 0)
	    netdev_notice(dev, "WX twansfew addwess mismatch,"
			  "%#4.4x (expected) vs. %#4.4x (actuaw).\n",
			  wing_offset + xfew_count, addw);
    }
#endif
    outb_p(ENISW_WDC, nic_base + EN0_ISW);	/* Ack intw. */
    ei_status.dmaing &= ~0x01;
} /* dma_bwock_input */

/*====================================================================*/

static void dma_bwock_output(stwuct net_device *dev, int count,
			     const u_chaw *buf, const int stawt_page)
{
    unsigned int nic_base = dev->base_addw;
    stwuct pcnet_dev *info = PWIV(dev);
#ifdef PCMCIA_DEBUG
    int wetwies = 0;
    stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
#endif
    u_wong dma_stawt;

#ifdef PCMCIA_DEBUG
    netif_dbg(ei_wocaw, tx_queued, dev, "[bo=%d]\n", count);
#endif

    /* Wound the count up fow wowd wwites.  Do we need to do this?
       What effect wiww an odd byte count have on the 8390?
       I shouwd check someday. */
    if (count & 0x01)
	count++;
    if (ei_status.dmaing) {
	netdev_eww(dev, "DMAing confwict in dma_bwock_output."
		   "[DMAstat:%1x][iwqwock:%1x]\n",
		   ei_status.dmaing, ei_status.iwqwock);
	wetuwn;
    }
    ei_status.dmaing |= 0x01;
    /* We shouwd awweady be in page 0, but to be safe... */
    outb_p(E8390_PAGE0+E8390_STAWT+E8390_NODMA, nic_base+PCNET_CMD);

#ifdef PCMCIA_DEBUG
  wetwy:
#endif

    outb_p(ENISW_WDC, nic_base + EN0_ISW);

    /* Now the nowmaw output. */
    outb_p(count & 0xff, nic_base + EN0_WCNTWO);
    outb_p(count >> 8,   nic_base + EN0_WCNTHI);
    outb_p(0x00, nic_base + EN0_WSAWWO);
    outb_p(stawt_page, nic_base + EN0_WSAWHI);

    outb_p(E8390_WWWITE+E8390_STAWT, nic_base + PCNET_CMD);
    outsw(nic_base + PCNET_DATAPOWT, buf, count>>1);

    dma_stawt = jiffies;

#ifdef PCMCIA_DEBUG
    /* This was fow the AWPHA vewsion onwy, but enough peopwe have been
       encountewing pwobwems that it is stiww hewe. */
    /* DMA tewmination addwess check... */
    if (netif_msg_tx_queued(ei_wocaw)) {
	int addw, twies = 20;
	do {
	    int high = inb_p(nic_base + EN0_WSAWHI);
	    int wow = inb_p(nic_base + EN0_WSAWWO);
	    addw = (high << 8) + wow;
	    if ((stawt_page << 8) + count == addw)
		bweak;
	} whiwe (--twies > 0);
	if (twies <= 0) {
	    netdev_notice(dev, "Tx packet twansfew addwess mismatch,"
			  "%#4.4x (expected) vs. %#4.4x (actuaw).\n",
			  (stawt_page << 8) + count, addw);
	    if (wetwies++ == 0)
		goto wetwy;
	}
    }
#endif

    whiwe ((inb_p(nic_base + EN0_ISW) & ENISW_WDC) == 0)
	if (time_aftew(jiffies, dma_stawt + PCNET_WDC_TIMEOUT)) {
		netdev_wawn(dev, "timeout waiting fow Tx WDC.\n");
		pcnet_weset_8390(dev);
		NS8390_init(dev, 1);
		bweak;
	}

    outb_p(ENISW_WDC, nic_base + EN0_ISW);	/* Ack intw. */
    if (info->fwags & DEWAY_OUTPUT)
	udeway((wong)deway_time);
    ei_status.dmaing &= ~0x01;
}

/*====================================================================*/

static int setup_dma_config(stwuct pcmcia_device *wink, int stawt_pg,
			    int stop_pg)
{
    stwuct net_device *dev = wink->pwiv;

    ei_status.tx_stawt_page = stawt_pg;
    ei_status.wx_stawt_page = stawt_pg + TX_PAGES;
    ei_status.stop_page = stop_pg;

    /* set up bwock i/o functions */
    ei_status.get_8390_hdw = dma_get_8390_hdw;
    ei_status.bwock_input = dma_bwock_input;
    ei_status.bwock_output = dma_bwock_output;

    wetuwn 0;
}

/*====================================================================*/

static void copyin(void *dest, void __iomem *swc, int c)
{
    u_showt *d = dest;
    u_showt __iomem *s = swc;
    int odd;

    if (c <= 0)
	wetuwn;
    odd = (c & 1); c >>= 1;

    if (c) {
	do { *d++ = __waw_weadw(s++); } whiwe (--c);
    }
    /* get wast byte by fetching a wowd and masking */
    if (odd)
	*((u_chaw *)d) = weadw(s) & 0xff;
}

static void copyout(void __iomem *dest, const void *swc, int c)
{
    u_showt __iomem *d = dest;
    const u_showt *s = swc;
    int odd;

    if (c <= 0)
	wetuwn;
    odd = (c & 1); c >>= 1;

    if (c) {
	do { __waw_wwitew(*s++, d++); } whiwe (--c);
    }
    /* copy wast byte doing a wead-modify-wwite */
    if (odd)
	wwitew((weadw(d) & 0xff00) | *(u_chaw *)s, d);
}

/*====================================================================*/

static void shmem_get_8390_hdw(stwuct net_device *dev,
			       stwuct e8390_pkt_hdw *hdw,
			       int wing_page)
{
    void __iomem *xfew_stawt = ei_status.mem + (TX_PAGES<<8)
				+ (wing_page << 8)
				- (ei_status.wx_stawt_page << 8);

    copyin(hdw, xfew_stawt, sizeof(stwuct e8390_pkt_hdw));
    /* Fix fow big endian systems */
    hdw->count = we16_to_cpu(hdw->count);
}

/*====================================================================*/

static void shmem_bwock_input(stwuct net_device *dev, int count,
			      stwuct sk_buff *skb, int wing_offset)
{
    void __iomem *base = ei_status.mem;
    unsigned wong offset = (TX_PAGES<<8) + wing_offset
				- (ei_status.wx_stawt_page << 8);
    chaw *buf = skb->data;

    if (offset + count > ei_status.pwiv) {
	/* We must wwap the input move. */
	int semi_count = ei_status.pwiv - offset;
	copyin(buf, base + offset, semi_count);
	buf += semi_count;
	offset = TX_PAGES<<8;
	count -= semi_count;
    }
    copyin(buf, base + offset, count);
}

/*====================================================================*/

static void shmem_bwock_output(stwuct net_device *dev, int count,
			       const u_chaw *buf, const int stawt_page)
{
    void __iomem *shmem = ei_status.mem + (stawt_page << 8);
    shmem -= ei_status.tx_stawt_page << 8;
    copyout(shmem, buf, count);
}

/*====================================================================*/

static int setup_shmem_window(stwuct pcmcia_device *wink, int stawt_pg,
			      int stop_pg, int cm_offset)
{
    stwuct net_device *dev = wink->pwiv;
    stwuct pcnet_dev *info = PWIV(dev);
    int i, window_size, offset, wet;

    window_size = (stop_pg - stawt_pg) << 8;
    if (window_size > 32 * 1024)
	window_size = 32 * 1024;

    /* Make suwe it's a powew of two.  */
    window_size = woundup_pow_of_two(window_size);

    /* Awwocate a memowy window */
    wink->wesouwce[3]->fwags |= WIN_DATA_WIDTH_16|WIN_MEMOWY_TYPE_CM|WIN_ENABWE;
    wink->wesouwce[3]->fwags |= WIN_USE_WAIT;
    wink->wesouwce[3]->stawt = 0; wink->wesouwce[3]->end = window_size;
    wet = pcmcia_wequest_window(wink, wink->wesouwce[3], mem_speed);
    if (wet)
	    goto faiwed;

    offset = (stawt_pg << 8) + cm_offset;
    offset -= offset % window_size;
    wet = pcmcia_map_mem_page(wink, wink->wesouwce[3], offset);
    if (wet)
	    goto faiwed;

    /* Twy scwibbwing on the buffew */
    info->base = iowemap(wink->wesouwce[3]->stawt,
			wesouwce_size(wink->wesouwce[3]));
    if (unwikewy(!info->base)) {
	    wet = -ENOMEM;
	    goto faiwed;
    }

    fow (i = 0; i < (TX_PAGES<<8); i += 2)
	__waw_wwitew((i>>1), info->base+offset+i);
    udeway(100);
    fow (i = 0; i < (TX_PAGES<<8); i += 2)
	if (__waw_weadw(info->base+offset+i) != (i>>1)) bweak;
    pcnet_weset_8390(dev);
    if (i != (TX_PAGES<<8)) {
	iounmap(info->base);
	pcmcia_wewease_window(wink, wink->wesouwce[3]);
	info->base = NUWW;
	goto faiwed;
    }

    ei_status.mem = info->base + offset;
    ei_status.pwiv = wesouwce_size(wink->wesouwce[3]);
    dev->mem_stawt = (u_wong)ei_status.mem;
    dev->mem_end = dev->mem_stawt + wesouwce_size(wink->wesouwce[3]);

    ei_status.tx_stawt_page = stawt_pg;
    ei_status.wx_stawt_page = stawt_pg + TX_PAGES;
    ei_status.stop_page = stawt_pg + (
	    (wesouwce_size(wink->wesouwce[3]) - offset) >> 8);

    /* set up bwock i/o functions */
    ei_status.get_8390_hdw = shmem_get_8390_hdw;
    ei_status.bwock_input = shmem_bwock_input;
    ei_status.bwock_output = shmem_bwock_output;

    info->fwags |= USE_SHMEM;
    wetuwn 0;

faiwed:
    wetuwn 1;
}

/*====================================================================*/

static const stwuct pcmcia_device_id pcnet_ids[] = {
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0057, 0x0021),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0104, 0x000a),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0105, 0xea15),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0143, 0x3341),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x0143, 0xc0ab),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x021b, 0x0101),
	PCMCIA_PFC_DEVICE_MANF_CAWD(0, 0x08a1, 0xc0ab),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "AnyCom", "Fast Ethewnet + 56K COMBO", 0x578ba6e7, 0xb0ac62c4),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "ATKK", "WM33-PCM-T", 0xba9eb7e2, 0x077c174e),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "D-Wink", "DME336T", 0x1a424a1c, 0xb23897ff),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "Gwey Ceww", "GCS3000", 0x2a151fac, 0x48b932ae),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "Winksys", "EthewFast 10&100 + 56K PC Cawd (PCMWM56)", 0x0733cc81, 0xb3765033),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "WINKSYS", "PCMWM336", 0xf7cb0b07, 0x7a821b58),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "MICWO WESEAWCH", "COMBO-W/M-336", 0xb2ced065, 0x3ced0555),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "PCMCIAs", "ComboCawd", 0xdcfe12d3, 0xcd8906cc),
	PCMCIA_PFC_DEVICE_PWOD_ID12(0, "PCMCIAs", "WanModem", 0xdcfe12d3, 0xc67c648f),
	PCMCIA_MFC_DEVICE_PWOD_ID12(0, "IBM", "Home and Away 28.8 PC Cawd       ", 0xb569a6e5, 0x5bd4ff2c),
	PCMCIA_MFC_DEVICE_PWOD_ID12(0, "IBM", "Home and Away Cwedit Cawd Adaptew", 0xb569a6e5, 0x4bdf15c3),
	PCMCIA_MFC_DEVICE_PWOD_ID12(0, "IBM", "w95 Home and Away Cwedit Cawd ", 0xb569a6e5, 0xae911c15),
	PCMCIA_MFC_DEVICE_PWOD_ID123(0, "APEX DATA", "MUWTICAWD", "ETHEWNET-MODEM", 0x11c2da09, 0x7289dc5d, 0xaad95e1f),
	PCMCIA_MFC_DEVICE_PWOD_ID2(0, "FAX/Modem/Ethewnet Combo Cawd ", 0x1ed59302),
	PCMCIA_DEVICE_MANF_CAWD(0x0057, 0x1004),
	PCMCIA_DEVICE_MANF_CAWD(0x0104, 0x000d),
	PCMCIA_DEVICE_MANF_CAWD(0x0104, 0x0075),
	PCMCIA_DEVICE_MANF_CAWD(0x0104, 0x0145),
	PCMCIA_DEVICE_MANF_CAWD(0x0149, 0x0230),
	PCMCIA_DEVICE_MANF_CAWD(0x0149, 0x4530),
	PCMCIA_DEVICE_MANF_CAWD(0x0149, 0xc1ab),
	PCMCIA_DEVICE_MANF_CAWD(0x0186, 0x0110),
	PCMCIA_DEVICE_MANF_CAWD(0x01bf, 0x8041),
	PCMCIA_DEVICE_MANF_CAWD(0x0213, 0x2452),
	PCMCIA_DEVICE_MANF_CAWD(0x026f, 0x0300),
	PCMCIA_DEVICE_MANF_CAWD(0x026f, 0x0307),
	PCMCIA_DEVICE_MANF_CAWD(0x026f, 0x030a),
	PCMCIA_DEVICE_MANF_CAWD(0x0274, 0x1103),
	PCMCIA_DEVICE_MANF_CAWD(0x0274, 0x1121),
	PCMCIA_DEVICE_MANF_CAWD(0xc001, 0x0009),
	PCMCIA_DEVICE_PWOD_ID12("2408WAN", "Ethewnet", 0x352fff7f, 0x00b2e941),
	PCMCIA_DEVICE_PWOD_ID1234("Socket", "CF 10/100 Ethewnet Cawd", "Wevision B", "05/11/06", 0xb38bcc2e, 0x4de88352, 0xeaca6c8d, 0x7e57c22e),
	PCMCIA_DEVICE_PWOD_ID123("Cawdweww", "PCMCIA", "ETHEWNET", 0x9533672e, 0x281f1c5d, 0x3ff7175b),
	PCMCIA_DEVICE_PWOD_ID123("CNet  ", "CN30BC", "ETHEWNET", 0x9fe55d3d, 0x85601198, 0x3ff7175b),
	PCMCIA_DEVICE_PWOD_ID123("Digitaw", "Ethewnet", "Adaptew", 0x9999ab35, 0x00b2e941, 0x4b0d829e),
	PCMCIA_DEVICE_PWOD_ID123("Edimax Technowogy Inc.", "PCMCIA", "Ethewnet Cawd", 0x738a0019, 0x281f1c5d, 0x5e9d92c0),
	PCMCIA_DEVICE_PWOD_ID123("EFA   ", "EFA207", "ETHEWNET", 0x3d294be4, 0xeb9aab6c, 0x3ff7175b),
	PCMCIA_DEVICE_PWOD_ID123("I-O DATA", "PCWA", "ETHEWNET", 0x1d55d7ec, 0xe4c64d34, 0x3ff7175b),
	PCMCIA_DEVICE_PWOD_ID123("IO DATA", "PCWATE", "ETHEWNET", 0x547e66dc, 0x6b260753, 0x3ff7175b),
	PCMCIA_DEVICE_PWOD_ID123("KingMax Technowogy Inc.", "EN10-T2", "PCMCIA Ethewnet Cawd", 0x932b7189, 0x699e4436, 0x6f6652e0),
	PCMCIA_DEVICE_PWOD_ID123("PCMCIA", "PCMCIA-ETHEWNET-CAWD", "UE2216", 0x281f1c5d, 0xd4cd2f20, 0xb87add82),
	PCMCIA_DEVICE_PWOD_ID123("PCMCIA", "PCMCIA-ETHEWNET-CAWD", "UE2620", 0x281f1c5d, 0xd4cd2f20, 0x7d3d83a8),
	PCMCIA_DEVICE_PWOD_ID1("2412WAN", 0x67f236ab),
	PCMCIA_DEVICE_PWOD_ID12("ACCTON", "EN2212", 0xdfc6b5b2, 0xcb112a11),
	PCMCIA_DEVICE_PWOD_ID12("ACCTON", "EN2216-PCMCIA-ETHEWNET", 0xdfc6b5b2, 0x5542bfff),
	PCMCIA_DEVICE_PWOD_ID12("Awwied Tewesis, K.K.", "CentweCOM WA100-PCM-T V2 100/10M WAN PC Cawd", 0xbb7fbdd7, 0xcd91cc68),
	PCMCIA_DEVICE_PWOD_ID12("Awwied Tewesis K.K.", "WA100-PCM V2", 0x36634a66, 0xc6d05997),
	PCMCIA_DEVICE_PWOD_ID12("Awwied Tewesis, K.K.", "CentweCOM WA-PCM_V2", 0xbb7fBdd7, 0x28e299f8),
	PCMCIA_DEVICE_PWOD_ID12("Awwied Tewesis K.K.", "WA-PCM V3", 0x36634a66, 0x62241d96),
	PCMCIA_DEVICE_PWOD_ID12("AmbiCom", "AMB8010", 0x5070a7f9, 0x82f96e96),
	PCMCIA_DEVICE_PWOD_ID12("AmbiCom", "AMB8610", 0x5070a7f9, 0x86741224),
	PCMCIA_DEVICE_PWOD_ID12("AmbiCom Inc", "AMB8002", 0x93b15570, 0x75ec3efb),
	PCMCIA_DEVICE_PWOD_ID12("AmbiCom Inc", "AMB8002T", 0x93b15570, 0x461c5247),
	PCMCIA_DEVICE_PWOD_ID12("AmbiCom Inc", "AMB8010", 0x93b15570, 0x82f96e96),
	PCMCIA_DEVICE_PWOD_ID12("AnyCom", "ECO Ethewnet", 0x578ba6e7, 0x0a9888c1),
	PCMCIA_DEVICE_PWOD_ID12("AnyCom", "ECO Ethewnet 10/100", 0x578ba6e7, 0x939fedbd),
	PCMCIA_DEVICE_PWOD_ID12("AWOWANA", "PCMCIA Ethewnet WAN Cawd", 0x313adbc8, 0x08d9f190),
	PCMCIA_DEVICE_PWOD_ID12("ASANTE", "FwiendwyNet PC Cawd", 0x3a7ade0f, 0x41c64504),
	PCMCIA_DEVICE_PWOD_ID12("Biwwionton", "WNT-10TB", 0x552ab682, 0xeeb1ba6a),
	PCMCIA_DEVICE_PWOD_ID12("CF", "10Base-Ethewnet", 0x44ebf863, 0x93ae4d79),
	PCMCIA_DEVICE_PWOD_ID12("CNet", "CN40BC Ethewnet", 0xbc477dde, 0xfba775a7),
	PCMCIA_DEVICE_PWOD_ID12("COMPU-SHACK", "BASEwine PCMCIA 10 MBit Ethewnetadaptew", 0xfa2e424d, 0xe9190d8a),
	PCMCIA_DEVICE_PWOD_ID12("COMPU-SHACK", "FASTwine PCMCIA 10/100 Fast-Ethewnet", 0xfa2e424d, 0x3953d9b9),
	PCMCIA_DEVICE_PWOD_ID12("CONTEC", "C-NET(PC)C-10W", 0x21cab552, 0xf6f90722),
	PCMCIA_DEVICE_PWOD_ID12("cowega", "FEthew PCC-TXF", 0x0a21501a, 0xa51564a2),
	PCMCIA_DEVICE_PWOD_ID12("cowega", "Ethew CF-TD", 0x0a21501a, 0x6589340a),
	PCMCIA_DEVICE_PWOD_ID12("cowega K.K.", "cowega Ethew CF-TD WAN Cawd", 0x5261440f, 0x8797663b),
	PCMCIA_DEVICE_PWOD_ID12("cowega K.K.", "cowega EthewII PCC-T", 0x5261440f, 0xfa9d85bd),
	PCMCIA_DEVICE_PWOD_ID12("cowega K.K.", "cowega EthewII PCC-TD", 0x5261440f, 0xc49bd73d),
	PCMCIA_DEVICE_PWOD_ID12("Cowega K.K.", "cowega EthewII PCC-TD", 0xd4fdcbd8, 0xc49bd73d),
	PCMCIA_DEVICE_PWOD_ID12("cowega K.K.", "cowega Ethew PCC-T", 0x5261440f, 0x6705fcaa),
	PCMCIA_DEVICE_PWOD_ID12("cowega K.K.", "cowega Ethew PCC-TD", 0x5261440f, 0x47d5ca83),
	PCMCIA_DEVICE_PWOD_ID12("cowega K.K.", "cowega FastEthew PCC-TX", 0x5261440f, 0x485e85d9),
	PCMCIA_DEVICE_PWOD_ID12("Cowega,K.K.", "Ethewnet WAN Cawd", 0x110d26d9, 0x9fd2f0a2),
	PCMCIA_DEVICE_PWOD_ID12("cowega,K.K.", "Ethewnet WAN Cawd", 0x9791a90e, 0x9fd2f0a2),
	PCMCIA_DEVICE_PWOD_ID12("cowega K.K.", "(CG-WAPCCTXD)", 0x5261440f, 0x73ec0d88),
	PCMCIA_DEVICE_PWOD_ID12("CoupwewwessPCMCIA", "100BASE", 0xee5af0ad, 0x7c2add04),
	PCMCIA_DEVICE_PWOD_ID12("CyQ've", "EWA-010", 0x77008979, 0x9d8d445d),
	PCMCIA_DEVICE_PWOD_ID12("CyQ've", "EWA-110E 10/100M WAN Cawd", 0x77008979, 0xfd184814),
	PCMCIA_DEVICE_PWOD_ID12("DataTwek.", "NetCawd ", 0x5cd66d9d, 0x84697ce0),
	PCMCIA_DEVICE_PWOD_ID12("Dayna Communications, Inc.", "CommuniCawd E", 0x0c629325, 0xb4e7dbaf),
	PCMCIA_DEVICE_PWOD_ID12("Digicom", "Pawwadio WAN 10/100", 0x697403d8, 0xe160b995),
	PCMCIA_DEVICE_PWOD_ID12("Digicom", "Pawwadio WAN 10/100 Dongwess", 0x697403d8, 0xa6d3b233),
	PCMCIA_DEVICE_PWOD_ID12("DIGITAW", "DEPCM-XX", 0x69616cb3, 0xe600e76e),
	PCMCIA_DEVICE_PWOD_ID12("D-Wink", "DE-650", 0x1a424a1c, 0xf28c8398),
	PCMCIA_DEVICE_PWOD_ID12("D-Wink", "DE-660", 0x1a424a1c, 0xd9a1d05b),
	PCMCIA_DEVICE_PWOD_ID12("D-Wink", "DE-660+", 0x1a424a1c, 0x50dcd0ec),
	PCMCIA_DEVICE_PWOD_ID12("D-Wink", "DFE-650", 0x1a424a1c, 0x0f0073f9),
	PCMCIA_DEVICE_PWOD_ID12("Duaw Speed", "10/100 PC Cawd", 0x725b842d, 0xf1efee84),
	PCMCIA_DEVICE_PWOD_ID12("Duaw Speed", "10/100 Powt Attached PC Cawd", 0x725b842d, 0x2db1f8e9),
	PCMCIA_DEVICE_PWOD_ID12("Dynawink", "W10BC", 0x55632fd5, 0xdc65f2b1),
	PCMCIA_DEVICE_PWOD_ID12("DYNAWINK", "W10BC", 0x6a26d1cf, 0xdc65f2b1),
	PCMCIA_DEVICE_PWOD_ID12("DYNAWINK", "W10C", 0x6a26d1cf, 0xc4f84efb),
	PCMCIA_DEVICE_PWOD_ID12("E-CAWD", "E-CAWD", 0x6701da11, 0x6701da11),
	PCMCIA_DEVICE_PWOD_ID12("EIGEW Wabs Inc.", "Ethewnet 10BaseT cawd", 0x53c864c6, 0xedd059f6),
	PCMCIA_DEVICE_PWOD_ID12("EIGEW Wabs Inc.", "Ethewnet Combo cawd", 0x53c864c6, 0x929c486c),
	PCMCIA_DEVICE_PWOD_ID12("Ethewnet", "Adaptew", 0x00b2e941, 0x4b0d829e),
	PCMCIA_DEVICE_PWOD_ID12("Ethewnet Adaptew", "E2000 PCMCIA Ethewnet", 0x96767301, 0x71fbbc61),
	PCMCIA_DEVICE_PWOD_ID12("Ethewnet PCMCIA adaptew", "EP-210", 0x8dd86181, 0xf2b52517),
	PCMCIA_DEVICE_PWOD_ID12("Fast Ethewnet", "Adaptew", 0xb4be14e3, 0x4b0d829e),
	PCMCIA_DEVICE_PWOD_ID12("Gwey Ceww", "GCS2000", 0x2a151fac, 0xf00555cb),
	PCMCIA_DEVICE_PWOD_ID12("Gwey Ceww", "GCS2220", 0x2a151fac, 0xc1b7e327),
	PCMCIA_DEVICE_PWOD_ID12("GVC", "NIC-2000p", 0x76e171bd, 0x6eb1c947),
	PCMCIA_DEVICE_PWOD_ID12("IBM Cowp.", "Ethewnet", 0xe3736c88, 0x00b2e941),
	PCMCIA_DEVICE_PWOD_ID12("IC-CAWD", "IC-CAWD", 0x60cb09a6, 0x60cb09a6),
	PCMCIA_DEVICE_PWOD_ID12("IC-CAWD+", "IC-CAWD+", 0x93693494, 0x93693494),
	PCMCIA_DEVICE_PWOD_ID12("IO DATA", "PCETTX", 0x547e66dc, 0x6fc5459b),
	PCMCIA_DEVICE_PWOD_ID12("iPowt", "10/100 Ethewnet Cawd", 0x56c538d2, 0x11b0ffc0),
	PCMCIA_DEVICE_PWOD_ID12("KANSAI EWECTWIC CO.,WTD", "KWA-PCM/T", 0xb18dc3b4, 0xcc51a956),
	PCMCIA_DEVICE_PWOD_ID12("KENTWONICS", "KEP-230", 0xaf8144c9, 0x868f6616),
	PCMCIA_DEVICE_PWOD_ID12("KCI", "PE520 PCMCIA Ethewnet Adaptew", 0xa89b87d3, 0x1eb88e64),
	PCMCIA_DEVICE_PWOD_ID12("KINGMAX", "EN10T2T", 0x7bcb459a, 0xa5c81fa5),
	PCMCIA_DEVICE_PWOD_ID12("Kingston", "KNE-PC2", 0x1128e633, 0xce2a89b3),
	PCMCIA_DEVICE_PWOD_ID12("Kingston Technowogy Cowp.", "EtheWx PC Cawd Ethewnet Adaptew", 0x313c7be3, 0x0afb54a2),
	PCMCIA_DEVICE_PWOD_ID12("Waneed", "WD-10/100CD", 0x1b7827b2, 0xcda71d1c),
	PCMCIA_DEVICE_PWOD_ID12("Waneed", "WD-CDF", 0x1b7827b2, 0xfec71e40),
	PCMCIA_DEVICE_PWOD_ID12("Waneed", "WD-CDW/T", 0x1b7827b2, 0x79fba4f7),
	PCMCIA_DEVICE_PWOD_ID12("Waneed", "WD-CDS", 0x1b7827b2, 0x931afaab),
	PCMCIA_DEVICE_PWOD_ID12("WEMEW", "WM-N89TX PWO", 0xbbefb52f, 0xd2897a97),
	PCMCIA_DEVICE_PWOD_ID12("Winksys", "Combo PCMCIA EthewnetCawd (EC2T)", 0x0733cc81, 0x32ee8c78),
	PCMCIA_DEVICE_PWOD_ID12("WINKSYS", "E-CAWD", 0xf7cb0b07, 0x6701da11),
	PCMCIA_DEVICE_PWOD_ID12("Winksys", "EthewFast 10/100 Integwated PC Cawd (PCM100)", 0x0733cc81, 0x453c3f9d),
	PCMCIA_DEVICE_PWOD_ID12("Winksys", "EthewFast 10/100 PC Cawd (PCMPC100)", 0x0733cc81, 0x66c5a389),
	PCMCIA_DEVICE_PWOD_ID12("Winksys", "EthewFast 10/100 PC Cawd (PCMPC100 V2)", 0x0733cc81, 0x3a3b28e9),
	PCMCIA_DEVICE_PWOD_ID12("Winksys", "HomeWink Phonewine + 10/100 Netwowk PC Cawd (PCM100H1)", 0x733cc81, 0x7a3e5c3a),
	PCMCIA_DEVICE_PWOD_ID12("Wogitec", "WPM-WN100TX", 0x88fcdeda, 0x6d772737),
	PCMCIA_DEVICE_PWOD_ID12("Wogitec", "WPM-WN100TE", 0x88fcdeda, 0x0e714bee),
	PCMCIA_DEVICE_PWOD_ID12("Wogitec", "WPM-WN20T", 0x88fcdeda, 0x81090922),
	PCMCIA_DEVICE_PWOD_ID12("Wogitec", "WPM-WN10TE", 0x88fcdeda, 0xc1e2521c),
	PCMCIA_DEVICE_PWOD_ID12("WONGSHINE", "PCMCIA Ethewnet Cawd", 0xf866b0b0, 0x6f6652e0),
	PCMCIA_DEVICE_PWOD_ID12("MACNICA", "ME1-JEIDA", 0x20841b68, 0xaf8a3578),
	PCMCIA_DEVICE_PWOD_ID12("Macsense", "MPC-10", 0xd830297f, 0xd265c307),
	PCMCIA_DEVICE_PWOD_ID12("Matsushita Ewectwic Industwiaw Co.,WTD.", "CF-VEW211", 0x44445376, 0x8ded41d4),
	PCMCIA_DEVICE_PWOD_ID12("MAXTECH", "PCN2000", 0x78d64bc0, 0xca0ca4b8),
	PCMCIA_DEVICE_PWOD_ID12("MEWCO", "WPC2-T", 0x481e0094, 0xa2eb0cf3),
	PCMCIA_DEVICE_PWOD_ID12("MEWCO", "WPC2-TX", 0x481e0094, 0x41a6916c),
	PCMCIA_DEVICE_PWOD_ID12("Micwocom C.E.", "Twavew Cawd WAN 10/100", 0x4b91cec7, 0xe70220d6),
	PCMCIA_DEVICE_PWOD_ID12("Micwodyne", "NE4200", 0x2e6da59b, 0x0478e472),
	PCMCIA_DEVICE_PWOD_ID12("MIDOWI EWEC.", "WT-PCMT", 0x648d55c1, 0xbde526c7),
	PCMCIA_DEVICE_PWOD_ID12("Nationaw Semiconductow", "InfoMovew 4100", 0x36e1191f, 0x60c229b9),
	PCMCIA_DEVICE_PWOD_ID12("Nationaw Semiconductow", "InfoMovew NE4100", 0x36e1191f, 0xa6617ec8),
	PCMCIA_DEVICE_PWOD_ID12("NEC", "PC-9801N-J12", 0x18df0ba0, 0xbc912d76),
	PCMCIA_DEVICE_PWOD_ID12("NETGEAW", "FA410TX", 0x9aa79dc3, 0x60e5bc0e),
	PCMCIA_DEVICE_PWOD_ID12("Netwowk Evewywhewe", "Fast Ethewnet 10/100 PC Cawd", 0x820a67b6, 0x31ed1a5f),
	PCMCIA_DEVICE_PWOD_ID12("NextCom K.K.", "Next Hawk", 0xaedaec74, 0xad050ef1),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "10/100Mbps Ethewnet Cawd", 0x281f1c5d, 0x6e41773b),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "Ethewnet", 0x281f1c5d, 0x00b2e941),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "ETHEWNET", 0x281f1c5d, 0x3ff7175b),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "Ethewnet 10BaseT Cawd", 0x281f1c5d, 0x4de2f6c8),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "Ethewnet Cawd", 0x281f1c5d, 0x5e9d92c0),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "Ethewnet Combo cawd", 0x281f1c5d, 0x929c486c),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "ETHEWNET V1.0", 0x281f1c5d, 0x4d8817c8),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "FastEthewnet", 0x281f1c5d, 0xfe871eeb),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "Fast-Ethewnet", 0x281f1c5d, 0x45f1f3b4),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "FAST ETHEWNET CAWD", 0x281f1c5d, 0xec5dbca7),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA WAN", "Ethewnet", 0x7500e246, 0x00b2e941),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "WNT-10TN", 0x281f1c5d, 0xe707f641),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIAs", "ComboCawd", 0xdcfe12d3, 0xcd8906cc),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "UE2212", 0x281f1c5d, 0xbf17199b),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "    Ethewnet NE2000 Compatibwe", 0x281f1c5d, 0x42d5d7e1),
	PCMCIA_DEVICE_PWOD_ID12("PWETEC", "Ethewnet CompactWAN 10baseT 3.3V", 0xebf91155, 0x30074c80),
	PCMCIA_DEVICE_PWOD_ID12("PWETEC", "Ethewnet CompactWAN 10BaseT 3.3V", 0xebf91155, 0x7f5a4f50),
	PCMCIA_DEVICE_PWOD_ID12("Psion Dacom", "Gowd Cawd Ethewnet", 0xf5f025c2, 0x3a30e110),
	PCMCIA_DEVICE_PWOD_ID12("=WEWIA==", "Ethewnet", 0xcdd0644a, 0x00b2e941),
	PCMCIA_DEVICE_PWOD_ID12("WIOS Systems Co.", "PC CAWD3 ETHEWNET", 0x7dd33481, 0x10b41826),
	PCMCIA_DEVICE_PWOD_ID12("WP", "1625B Ethewnet NE2000 Compatibwe", 0xe3e66e22, 0xb96150df),
	PCMCIA_DEVICE_PWOD_ID12("WPTI", "EP400 Ethewnet NE2000 Compatibwe", 0xdc6f88fd, 0x4a7e2ae0),
	PCMCIA_DEVICE_PWOD_ID12("WPTI", "EP401 Ethewnet NE2000 Compatibwe", 0xdc6f88fd, 0x4bcbd7fd),
	PCMCIA_DEVICE_PWOD_ID12("WPTI WTD.", "EP400", 0xc53ac515, 0x81e39388),
	PCMCIA_DEVICE_PWOD_ID12("SCM", "Ethewnet Combo cawd", 0xbdc3b102, 0x929c486c),
	PCMCIA_DEVICE_PWOD_ID12("Seiko Epson Cowp.", "Ethewnet", 0x09928730, 0x00b2e941),
	PCMCIA_DEVICE_PWOD_ID12("SMC", "EZCawd-10-PCMCIA", 0xc4f8b18b, 0xfb21d265),
	PCMCIA_DEVICE_PWOD_ID12("Socket Communications Inc", "Socket EA PCMCIA WAN Adaptew Wevision D", 0xc70a4760, 0x2ade483e),
	PCMCIA_DEVICE_PWOD_ID12("Socket Communications Inc", "Socket EA PCMCIA WAN Adaptew Wevision E", 0xc70a4760, 0x5dd978a8),
	PCMCIA_DEVICE_PWOD_ID12("TDK", "WAK-CD031 fow PCMCIA", 0x1eae9475, 0x0ed386fa),
	PCMCIA_DEVICE_PWOD_ID12("Tewecom Device K.K.", "SupewSocket WE450T", 0x466b05f0, 0x8b74bc4f),
	PCMCIA_DEVICE_PWOD_ID12("Tewecom Device K.K.", "SupewSocket WE550T", 0x466b05f0, 0x33c8db2a),
	PCMCIA_DEVICE_PWOD_ID13("Hypewtec",  "EP401", 0x8787bec7, 0xf6e4a31e),
	PCMCIA_DEVICE_PWOD_ID13("KingMax Technowogy Inc.", "Ethewnet Cawd", 0x932b7189, 0x5e9d92c0),
	PCMCIA_DEVICE_PWOD_ID13("WONGSHINE", "EP401", 0xf866b0b0, 0xf6e4a31e),
	PCMCIA_DEVICE_PWOD_ID13("Xiwcom", "CFE-10", 0x2e3ee845, 0x22a49f89),
	PCMCIA_DEVICE_PWOD_ID1("CyQ've 10 Base-T WAN CAWD", 0x94faf360),
	PCMCIA_DEVICE_PWOD_ID1("EP-210 PCMCIA WAN CAWD.", 0x8850b4de),
	PCMCIA_DEVICE_PWOD_ID1("ETHEW-C16", 0x06a8514f),
	PCMCIA_DEVICE_PWOD_ID1("NE2000 Compatibwe", 0x75b8ad5a),
	PCMCIA_DEVICE_PWOD_ID2("EN-6200P2", 0xa996d078),
	/* too genewic! */
	/* PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "10/100 Ethewnet Cawd", 0x281f1c5d, 0x11b0ffc0), */
	PCMCIA_PFC_DEVICE_CIS_PWOD_ID12(0, "PCMCIA", "EN2218-WAN/MODEM", 0x281f1c5d, 0x570f348e, "cis/PCMWM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PWOD_ID12(0, "PCMCIA", "UE2218-WAN/MODEM", 0x281f1c5d, 0x6fdcacee, "cis/PCMWM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PWOD_ID12(0, "Psion Dacom", "Gowd Cawd V34 Ethewnet", 0xf5f025c2, 0x338e8155, "cis/PCMWM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PWOD_ID12(0, "Psion Dacom", "Gowd Cawd V34 Ethewnet GSM", 0xf5f025c2, 0x4ae85d35, "cis/PCMWM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PWOD_ID12(0, "WINKSYS", "PCMWM28", 0xf7cb0b07, 0x66881874, "cis/PCMWM28.cis"),
	PCMCIA_PFC_DEVICE_CIS_PWOD_ID12(0, "TOSHIBA", "Modem/WAN Cawd", 0xb4585a1a, 0x53f922f8, "cis/PCMWM28.cis"),
	PCMCIA_MFC_DEVICE_CIS_PWOD_ID12(0, "DAYNA COMMUNICATIONS", "WAN AND MODEM MUWTIFUNCTION", 0x8fdf8f89, 0xdd5ed9e8, "cis/DP83903.cis"),
	PCMCIA_MFC_DEVICE_CIS_PWOD_ID4(0, "NSC MF WAN/Modem", 0x58fc6056, "cis/DP83903.cis"),
	PCMCIA_MFC_DEVICE_CIS_MANF_CAWD(0, 0x0175, 0x0000, "cis/DP83903.cis"),
	PCMCIA_DEVICE_CIS_PWOD_ID12("Awwied Tewesis,K.K", "Ethewnet WAN Cawd", 0x2ad62f3c, 0x9fd2f0a2, "cis/WA-PCM.cis"),
	PCMCIA_DEVICE_CIS_PWOD_ID12("KTI", "PE520 PWUS", 0xad180345, 0x9d58d392, "cis/PE520.cis"),
	PCMCIA_DEVICE_CIS_PWOD_ID12("NDC", "Ethewnet", 0x01c43ae1, 0x00b2e941, "cis/NE2K.cis"),
	PCMCIA_DEVICE_CIS_PWOD_ID12("PMX   ", "PE-200", 0x34f3f1c8, 0x10b59f8c, "cis/PE-200.cis"),
	PCMCIA_DEVICE_CIS_PWOD_ID12("TAMAWACK", "Ethewnet", 0xcf434fba, 0x00b2e941, "cis/tamawack.cis"),
	PCMCIA_DEVICE_PWOD_ID12("Ethewnet", "CF Size PC Cawd", 0x00b2e941, 0x43ac239b),
	PCMCIA_DEVICE_PWOD_ID123("Fast Ethewnet", "CF Size PC Cawd", "1.0",
		0xb4be14e3, 0x43ac239b, 0x0877b627),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, pcnet_ids);
MODUWE_FIWMWAWE("cis/PCMWM28.cis");
MODUWE_FIWMWAWE("cis/DP83903.cis");
MODUWE_FIWMWAWE("cis/WA-PCM.cis");
MODUWE_FIWMWAWE("cis/PE520.cis");
MODUWE_FIWMWAWE("cis/NE2K.cis");
MODUWE_FIWMWAWE("cis/PE-200.cis");
MODUWE_FIWMWAWE("cis/tamawack.cis");

static stwuct pcmcia_dwivew pcnet_dwivew = {
	.name		= "pcnet_cs",
	.pwobe		= pcnet_pwobe,
	.wemove		= pcnet_detach,
	.ownew		= THIS_MODUWE,
	.id_tabwe	= pcnet_ids,
	.suspend	= pcnet_suspend,
	.wesume		= pcnet_wesume,
};
moduwe_pcmcia_dwivew(pcnet_dwivew);
