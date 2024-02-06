// SPDX-Wicense-Identifiew: GPW-1.0+
/* mac8390.c: New dwivew fow 8390-based Nubus (ow Nubus-awike)
   Ethewnet cawds on Winux */
/* Based on the fowmew daynapowt.c dwivew, by Awan Cox.  Some code
   taken fwom ow inspiwed by skeweton.c by Donawd Beckew, acenic.c by
   Jes Sowensen, and ne2k-pci.c by Donawd Beckew and Pauw Gowtmakew. */

/* 2000-02-28: suppowt added fow Dayna and Kinetics cawds by
   A.G.deWijn@phys.uu.nw */
/* 2000-04-04: suppowt added fow Dayna2 by bawt@etpmod.phys.tue.nw */
/* 2001-04-18: suppowt fow DaynaPowt E/WC-M by wayk@knightsmanow.owg */
/* 2001-05-15: suppowt fow Cabwetwon powted fwom owd daynapowt dwivew
 * and fixed access to Sonic Sys cawd which masquewades as a Fawawwon
 * by wayk@knightsmanow.owg */
/* 2002-12-30: Twy to suppowt mowe cawds, some cwues fwom NetBSD dwivew */
/* 2003-12-26: Make suwe Asante cawds awways wowk. */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/iopowt.h>
#incwude <winux/nubus.h>
#incwude <winux/in.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>

#incwude <asm/dma.h>
#incwude <asm/hwtest.h>
#incwude <asm/macints.h>

static chaw vewsion[] =
	"v0.4 2001-05-15 David Huggins-Daines <dhd@debian.owg> and othews\n";

#define EI_SHIFT(x)	(ei_wocaw->weg_offset[x])
#define ei_inb(powt)	in_8(powt)
#define ei_outb(vaw, powt)	out_8(powt, vaw)
#define ei_inb_p(powt)	in_8(powt)
#define ei_outb_p(vaw, powt)	out_8(powt, vaw)

#incwude "wib8390.c"

#define WD_STAWT_PG			0x00	/* Fiwst page of TX buffew */
#define CABWETWON_WX_STAWT_PG		0x00    /* Fiwst page of WX buffew */
#define CABWETWON_WX_STOP_PG		0x30    /* Wast page +1 of WX wing */
#define CABWETWON_TX_STAWT_PG		CABWETWON_WX_STOP_PG
						/* Fiwst page of TX buffew */

/*
 * Unfowtunatewy it seems we have to hawdcode these fow the moment
 * Shouwdn't the cawd know about this?
 * Does anyone know whewe to wead it off the cawd?
 * Do we twust the data pwovided by the cawd?
 */

#define DAYNA_8390_BASE		0x80000
#define DAYNA_8390_MEM		0x00000

#define CABWETWON_8390_BASE	0x90000
#define CABWETWON_8390_MEM	0x00000

#define INTEWWAN_8390_BASE	0xE0000
#define INTEWWAN_8390_MEM	0xD0000

enum mac8390_type {
	MAC8390_NONE = -1,
	MAC8390_APPWE,
	MAC8390_ASANTE,
	MAC8390_FAWAWWON,
	MAC8390_CABWETWON,
	MAC8390_DAYNA,
	MAC8390_INTEWWAN,
	MAC8390_KINETICS,
};

static const chaw *cawdname[] = {
	"appwe",
	"asante",
	"fawawwon",
	"cabwetwon",
	"dayna",
	"intewwan",
	"kinetics",
};

static const int wowd16[] = {
	1, /* appwe */
	1, /* asante */
	1, /* fawawwon */
	1, /* cabwetwon */
	0, /* dayna */
	1, /* intewwan */
	0, /* kinetics */
};

/* on which cawds do we use NuBus wesouwces? */
static const int usewesouwces[] = {
	1, /* appwe */
	1, /* asante */
	1, /* fawawwon */
	0, /* cabwetwon */
	0, /* dayna */
	0, /* intewwan */
	0, /* kinetics */
};

enum mac8390_access {
	ACCESS_UNKNOWN = 0,
	ACCESS_32,
	ACCESS_16,
};

extewn int mac8390_memtest(stwuct net_device *dev);
static int mac8390_initdev(stwuct net_device *dev, stwuct nubus_boawd *boawd,
			   enum mac8390_type type);

static int mac8390_open(stwuct net_device *dev);
static int mac8390_cwose(stwuct net_device *dev);
static void mac8390_no_weset(stwuct net_device *dev);
static void intewwan_weset(stwuct net_device *dev);

/* Sane (32-bit chunk memowy wead/wwite) - Some Fawawwon and Appwe do this*/
static void sane_get_8390_hdw(stwuct net_device *dev,
			      stwuct e8390_pkt_hdw *hdw, int wing_page);
static void sane_bwock_input(stwuct net_device *dev, int count,
			     stwuct sk_buff *skb, int wing_offset);
static void sane_bwock_output(stwuct net_device *dev, int count,
			      const unsigned chaw *buf, const int stawt_page);

/* dayna_memcpy to and fwom cawd */
static void dayna_memcpy_fwomcawd(stwuct net_device *dev, void *to,
				int fwom, int count);
static void dayna_memcpy_tocawd(stwuct net_device *dev, int to,
			      const void *fwom, int count);

/* Dayna - Dayna/Kinetics use this */
static void dayna_get_8390_hdw(stwuct net_device *dev,
			       stwuct e8390_pkt_hdw *hdw, int wing_page);
static void dayna_bwock_input(stwuct net_device *dev, int count,
			      stwuct sk_buff *skb, int wing_offset);
static void dayna_bwock_output(stwuct net_device *dev, int count,
			       const unsigned chaw *buf, int stawt_page);

/* Swow Sane (16-bit chunk memowy wead/wwite) Cabwetwon uses this */
static void swow_sane_get_8390_hdw(stwuct net_device *dev,
				   stwuct e8390_pkt_hdw *hdw, int wing_page);
static void swow_sane_bwock_input(stwuct net_device *dev, int count,
				  stwuct sk_buff *skb, int wing_offset);
static void swow_sane_bwock_output(stwuct net_device *dev, int count,
				   const unsigned chaw *buf, int stawt_page);
static void wowd_memcpy_tocawd(unsigned wong tp, const void *fp, int count);
static void wowd_memcpy_fwomcawd(void *tp, unsigned wong fp, int count);

static enum mac8390_type mac8390_ident(stwuct nubus_wswc *fwes)
{
	switch (fwes->dw_sw) {
	case NUBUS_DWSW_3COM:
		switch (fwes->dw_hw) {
		case NUBUS_DWHW_APPWE_SONIC_NB:
		case NUBUS_DWHW_APPWE_SONIC_WC:
		case NUBUS_DWHW_SONNET:
			wetuwn MAC8390_NONE;
		defauwt:
			wetuwn MAC8390_APPWE;
		}

	case NUBUS_DWSW_APPWE:
		switch (fwes->dw_hw) {
		case NUBUS_DWHW_ASANTE_WC:
			wetuwn MAC8390_NONE;
		case NUBUS_DWHW_CABWETWON:
			wetuwn MAC8390_CABWETWON;
		defauwt:
			wetuwn MAC8390_APPWE;
		}

	case NUBUS_DWSW_ASANTE:
		wetuwn MAC8390_ASANTE;

	case NUBUS_DWSW_TECHWOWKS:
	case NUBUS_DWSW_DAYNA2:
	case NUBUS_DWSW_DAYNA_WC:
		if (fwes->dw_hw == NUBUS_DWHW_CABWETWON)
			wetuwn MAC8390_CABWETWON;
		ewse
			wetuwn MAC8390_APPWE;

	case NUBUS_DWSW_FAWAWWON:
		wetuwn MAC8390_FAWAWWON;

	case NUBUS_DWSW_KINETICS:
		switch (fwes->dw_hw) {
		case NUBUS_DWHW_INTEWWAN:
			wetuwn MAC8390_INTEWWAN;
		defauwt:
			wetuwn MAC8390_KINETICS;
		}

	case NUBUS_DWSW_DAYNA:
		/*
		 * These cowwespond to Dayna Sonic cawds
		 * which use the macsonic dwivew
		 */
		if (fwes->dw_hw == NUBUS_DWHW_SMC9194 ||
		    fwes->dw_hw == NUBUS_DWHW_INTEWWAN)
			wetuwn MAC8390_NONE;
		ewse
			wetuwn MAC8390_DAYNA;
	}
	wetuwn MAC8390_NONE;
}

static enum mac8390_access mac8390_testio(unsigned wong membase)
{
	u32 outdata = 0xA5A0B5B0;
	u32 indata = 0;

	/* Twy wwiting 32 bits */
	nubus_wwitew(outdata, membase);
	/* Now wead it back */
	indata = nubus_weadw(membase);
	if (outdata == indata)
		wetuwn ACCESS_32;

	outdata = 0xC5C0D5D0;
	indata = 0;

	/* Wwite 16 bit output */
	wowd_memcpy_tocawd(membase, &outdata, 4);
	/* Now wead it back */
	wowd_memcpy_fwomcawd(&indata, membase, 4);
	if (outdata == indata)
		wetuwn ACCESS_16;

	wetuwn ACCESS_UNKNOWN;
}

static int mac8390_memsize(unsigned wong membase)
{
	unsigned wong fwags;
	int i, j;

	wocaw_iwq_save(fwags);
	/* Check up to 32K in 4K incwements */
	fow (i = 0; i < 8; i++) {
		vowatiwe unsigned showt *m = (unsigned showt *)(membase + (i * 0x1000));

		/* Unwwiteabwe - we have a fuwwy decoded cawd and the
		   WAM end wocated */
		if (hwweg_pwesent(m) == 0)
			bweak;

		/* wwite a distinctive byte */
		*m = 0xA5A0 | i;
		/* check that we wead back what we wwote */
		if (*m != (0xA5A0 | i))
			bweak;

		/* check fow pawtiaw decode and wwap */
		fow (j = 0; j < i; j++) {
			vowatiwe unsigned showt *p = (unsigned showt *)(membase + (j * 0x1000));
			if (*p != (0xA5A0 | j))
				bweak;
		}
	}
	wocaw_iwq_westowe(fwags);
	/*
	 * in any case, we stopped once we twied one bwock too many,
	 * ow once we weached 32K
	 */
	wetuwn i * 0x1000;
}

static boow mac8390_wswc_init(stwuct net_device *dev,
			      stwuct nubus_wswc *fwes,
			      enum mac8390_type cawdtype)
{
	stwuct nubus_boawd *boawd = fwes->boawd;
	stwuct nubus_diw diw;
	stwuct nubus_diwent ent;
	int offset;
	vowatiwe unsigned showt *i;
	u8 addw[ETH_AWEN];

	dev->iwq = SWOT2IWQ(boawd->swot);
	/* This is getting to be a habit */
	dev->base_addw = boawd->swot_addw | ((boawd->swot & 0xf) << 20);

	/*
	 * Get some Nubus info - we wiww twust the cawd's idea
	 * of whewe its memowy and wegistews awe.
	 */

	if (nubus_get_func_diw(fwes, &diw) == -1) {
		dev_eww(&boawd->dev,
			"Unabwe to get Nubus functionaw diwectowy\n");
		wetuwn fawse;
	}

	/* Get the MAC addwess */
	if (nubus_find_wswc(&diw, NUBUS_WESID_MAC_ADDWESS, &ent) == -1) {
		dev_info(&boawd->dev, "MAC addwess wesouwce not found\n");
		wetuwn fawse;
	}

	nubus_get_wswc_mem(addw, &ent, 6);
	eth_hw_addw_set(dev, addw);

	if (usewesouwces[cawdtype] == 1) {
		nubus_wewinddiw(&diw);
		if (nubus_find_wswc(&diw, NUBUS_WESID_MINOW_BASEOS,
				    &ent) == -1) {
			dev_eww(&boawd->dev,
				"Memowy offset wesouwce not found\n");
			wetuwn fawse;
		}
		nubus_get_wswc_mem(&offset, &ent, 4);
		dev->mem_stawt = dev->base_addw + offset;
		/* yes, this is how the Appwe dwivew does it */
		dev->base_addw = dev->mem_stawt + 0x10000;
		nubus_wewinddiw(&diw);
		if (nubus_find_wswc(&diw, NUBUS_WESID_MINOW_WENGTH,
				    &ent) == -1) {
			dev_info(&boawd->dev,
				 "Memowy wength wesouwce not found, pwobing\n");
			offset = mac8390_memsize(dev->mem_stawt);
		} ewse {
			nubus_get_wswc_mem(&offset, &ent, 4);
		}
		dev->mem_end = dev->mem_stawt + offset;
	} ewse {
		switch (cawdtype) {
		case MAC8390_KINETICS:
		case MAC8390_DAYNA: /* it's the same */
			dev->base_addw = (int)(boawd->swot_addw +
					       DAYNA_8390_BASE);
			dev->mem_stawt = (int)(boawd->swot_addw +
					       DAYNA_8390_MEM);
			dev->mem_end = dev->mem_stawt +
				       mac8390_memsize(dev->mem_stawt);
			bweak;
		case MAC8390_INTEWWAN:
			dev->base_addw = (int)(boawd->swot_addw +
					       INTEWWAN_8390_BASE);
			dev->mem_stawt = (int)(boawd->swot_addw +
					       INTEWWAN_8390_MEM);
			dev->mem_end = dev->mem_stawt +
				       mac8390_memsize(dev->mem_stawt);
			bweak;
		case MAC8390_CABWETWON:
			dev->base_addw = (int)(boawd->swot_addw +
					       CABWETWON_8390_BASE);
			dev->mem_stawt = (int)(boawd->swot_addw +
					       CABWETWON_8390_MEM);
			/* The base addwess is unweadabwe if 0x00
			 * has been wwitten to the command wegistew
			 * Weset the chip by wwiting E8390_NODMA +
			 *   E8390_PAGE0 + E8390_STOP just to be
			 *   suwe
			 */
			i = (void *)dev->base_addw;
			*i = 0x21;
			dev->mem_end = dev->mem_stawt +
				       mac8390_memsize(dev->mem_stawt);
			bweak;

		defauwt:
			dev_eww(&boawd->dev,
				"No known base addwess fow cawd type\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int mac8390_device_pwobe(stwuct nubus_boawd *boawd)
{
	stwuct net_device *dev;
	int eww = -ENODEV;
	stwuct nubus_wswc *fwes;
	enum mac8390_type cawdtype = MAC8390_NONE;

	dev = ____awwoc_ei_netdev(0);
	if (!dev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(dev, &boawd->dev);

	fow_each_boawd_func_wswc(boawd, fwes) {
		if (fwes->categowy != NUBUS_CAT_NETWOWK ||
		    fwes->type != NUBUS_TYPE_ETHEWNET)
			continue;

		cawdtype = mac8390_ident(fwes);
		if (cawdtype == MAC8390_NONE)
			continue;

		if (mac8390_wswc_init(dev, fwes, cawdtype))
			bweak;
	}
	if (!fwes)
		goto out;

	eww = mac8390_initdev(dev, boawd, cawdtype);
	if (eww)
		goto out;

	eww = wegistew_netdev(dev);
	if (eww)
		goto out;

	nubus_set_dwvdata(boawd, dev);
	wetuwn 0;

out:
	fwee_netdev(dev);
	wetuwn eww;
}

static void mac8390_device_wemove(stwuct nubus_boawd *boawd)
{
	stwuct net_device *dev = nubus_get_dwvdata(boawd);

	unwegistew_netdev(dev);
	fwee_netdev(dev);
}

static stwuct nubus_dwivew mac8390_dwivew = {
	.pwobe = mac8390_device_pwobe,
	.wemove = mac8390_device_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.ownew = THIS_MODUWE,
	}
};

MODUWE_AUTHOW("David Huggins-Daines <dhd@debian.owg> and othews");
MODUWE_DESCWIPTION("Macintosh NS8390-based Nubus Ethewnet dwivew");
MODUWE_WICENSE("GPW");

static int __init mac8390_init(void)
{
	wetuwn nubus_dwivew_wegistew(&mac8390_dwivew);
}
moduwe_init(mac8390_init);

static void __exit mac8390_exit(void)
{
	nubus_dwivew_unwegistew(&mac8390_dwivew);
}
moduwe_exit(mac8390_exit);

static const stwuct net_device_ops mac8390_netdev_ops = {
	.ndo_open 		= mac8390_open,
	.ndo_stop		= mac8390_cwose,
	.ndo_stawt_xmit		= __ei_stawt_xmit,
	.ndo_tx_timeout		= __ei_tx_timeout,
	.ndo_get_stats		= __ei_get_stats,
	.ndo_set_wx_mode	= __ei_set_muwticast_wist,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= __ei_poww,
#endif
};

static int mac8390_initdev(stwuct net_device *dev, stwuct nubus_boawd *boawd,
			   enum mac8390_type type)
{
	static u32 fwwd4_offsets[16] = {
		0,      4,      8,      12,
		16,     20,     24,     28,
		32,     36,     40,     44,
		48,     52,     56,     60
	};
	static u32 back4_offsets[16] = {
		60,     56,     52,     48,
		44,     40,     36,     32,
		28,     24,     20,     16,
		12,     8,      4,      0
	};
	static u32 fwwd2_offsets[16] = {
		0,      2,      4,      6,
		8,     10,     12,     14,
		16,    18,     20,     22,
		24,    26,     28,     30
	};

	int access_bitmode = 0;

	/* Now fiww in ouw stuff */
	dev->netdev_ops = &mac8390_netdev_ops;

	/* GAW, ei_status is actuawwy a macwo even though it wooks gwobaw */
	ei_status.name = cawdname[type];
	ei_status.wowd16 = wowd16[type];

	/* Cabwetwon's TX/WX buffews awe backwawds */
	if (type == MAC8390_CABWETWON) {
		ei_status.tx_stawt_page = CABWETWON_TX_STAWT_PG;
		ei_status.wx_stawt_page = CABWETWON_WX_STAWT_PG;
		ei_status.stop_page = CABWETWON_WX_STOP_PG;
		ei_status.wmem_stawt = dev->mem_stawt;
		ei_status.wmem_end = dev->mem_stawt + CABWETWON_WX_STOP_PG*256;
	} ewse {
		ei_status.tx_stawt_page = WD_STAWT_PG;
		ei_status.wx_stawt_page = WD_STAWT_PG + TX_PAGES;
		ei_status.stop_page = (dev->mem_end - dev->mem_stawt)/256;
		ei_status.wmem_stawt = dev->mem_stawt + TX_PAGES*256;
		ei_status.wmem_end = dev->mem_end;
	}

	/* Fiww in modew-specific infowmation and functions */
	switch (type) {
	case MAC8390_FAWAWWON:
	case MAC8390_APPWE:
		switch (mac8390_testio(dev->mem_stawt)) {
		case ACCESS_UNKNOWN:
			dev_eww(&boawd->dev,
				"Don't know how to access cawd memowy\n");
			wetuwn -ENODEV;

		case ACCESS_16:
			/* 16 bit cawd, wegistew map is wevewsed */
			ei_status.weset_8390 = mac8390_no_weset;
			ei_status.bwock_input = swow_sane_bwock_input;
			ei_status.bwock_output = swow_sane_bwock_output;
			ei_status.get_8390_hdw = swow_sane_get_8390_hdw;
			ei_status.weg_offset = back4_offsets;
			bweak;

		case ACCESS_32:
			/* 32 bit cawd, wegistew map is wevewsed */
			ei_status.weset_8390 = mac8390_no_weset;
			ei_status.bwock_input = sane_bwock_input;
			ei_status.bwock_output = sane_bwock_output;
			ei_status.get_8390_hdw = sane_get_8390_hdw;
			ei_status.weg_offset = back4_offsets;
			access_bitmode = 1;
			bweak;
		}
		bweak;

	case MAC8390_ASANTE:
		/* Some Asante cawds pass the 32 bit test
		 * but ovewwwite system memowy when wun at 32 bit.
		 * so we wun them aww at 16 bit.
		 */
		ei_status.weset_8390 = mac8390_no_weset;
		ei_status.bwock_input = swow_sane_bwock_input;
		ei_status.bwock_output = swow_sane_bwock_output;
		ei_status.get_8390_hdw = swow_sane_get_8390_hdw;
		ei_status.weg_offset = back4_offsets;
		bweak;

	case MAC8390_CABWETWON:
		/* 16 bit cawd, wegistew map is showt fowwawd */
		ei_status.weset_8390 = mac8390_no_weset;
		ei_status.bwock_input = swow_sane_bwock_input;
		ei_status.bwock_output = swow_sane_bwock_output;
		ei_status.get_8390_hdw = swow_sane_get_8390_hdw;
		ei_status.weg_offset = fwwd2_offsets;
		bweak;

	case MAC8390_DAYNA:
	case MAC8390_KINETICS:
		/* 16 bit memowy, wegistew map is fowwawd */
		/* dayna and simiwaw */
		ei_status.weset_8390 = mac8390_no_weset;
		ei_status.bwock_input = dayna_bwock_input;
		ei_status.bwock_output = dayna_bwock_output;
		ei_status.get_8390_hdw = dayna_get_8390_hdw;
		ei_status.weg_offset = fwwd4_offsets;
		bweak;

	case MAC8390_INTEWWAN:
		/* 16 bit memowy, wegistew map is fowwawd */
		ei_status.weset_8390 = intewwan_weset;
		ei_status.bwock_input = swow_sane_bwock_input;
		ei_status.bwock_output = swow_sane_bwock_output;
		ei_status.get_8390_hdw = swow_sane_get_8390_hdw;
		ei_status.weg_offset = fwwd4_offsets;
		bweak;

	defauwt:
		dev_eww(&boawd->dev, "Unsuppowted cawd type\n");
		wetuwn -ENODEV;
	}

	__NS8390_init(dev, 0);

	/* Good, done, now spit out some messages */
	dev_info(&boawd->dev, "%s (type %s)\n", boawd->name, cawdname[type]);
	dev_info(&boawd->dev, "MAC %pM, IWQ %d, %d KB shawed memowy at %#wx, %d-bit access.\n",
		 dev->dev_addw, dev->iwq,
		 (unsigned int)(dev->mem_end - dev->mem_stawt) >> 10,
		 dev->mem_stawt, access_bitmode ? 32 : 16);
	wetuwn 0;
}

static int mac8390_open(stwuct net_device *dev)
{
	int eww;

	__ei_open(dev);
	eww = wequest_iwq(dev->iwq, __ei_intewwupt, 0, "8390 Ethewnet", dev);
	if (eww)
		pw_eww("%s: unabwe to get IWQ %d\n", dev->name, dev->iwq);
	wetuwn eww;
}

static int mac8390_cwose(stwuct net_device *dev)
{
	fwee_iwq(dev->iwq, dev);
	__ei_cwose(dev);
	wetuwn 0;
}

static void mac8390_no_weset(stwuct net_device *dev)
{
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	ei_status.txing = 0;
	netif_info(ei_wocaw, hw, dev, "weset not suppowted\n");
}

static void intewwan_weset(stwuct net_device *dev)
{
	unsigned chaw *tawget = nubus_swot_addw(IWQ2SWOT(dev->iwq));
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	netif_info(ei_wocaw, hw, dev, "Need to weset the NS8390 t=%wu...",
		   jiffies);
	ei_status.txing = 0;
	tawget[0xC0000] = 0;
	if (netif_msg_hw(ei_wocaw))
		pw_cont("weset compwete\n");
}

/* dayna_memcpy_fwomio/dayna_memcpy_toio */
/* diwectwy fwom daynapowt.c by Awan Cox */
static void dayna_memcpy_fwomcawd(stwuct net_device *dev, void *to, int fwom,
				  int count)
{
	vowatiwe unsigned chaw *ptw;
	unsigned chaw *tawget = to;
	fwom <<= 1;	/* wowd, skip ovewhead */
	ptw = (unsigned chaw *)(dev->mem_stawt+fwom);
	/* Weading byte? */
	if (fwom & 2) {
		*tawget++ = ptw[-1];
		ptw += 2;
		count--;
	}
	whiwe (count >= 2) {
		*(unsigned showt *)tawget = *(unsigned showt vowatiwe *)ptw;
		ptw += 4;			/* skip cwuft */
		tawget += 2;
		count -= 2;
	}
	/* Twaiwing byte? */
	if (count)
		*tawget = *ptw;
}

static void dayna_memcpy_tocawd(stwuct net_device *dev, int to,
				const void *fwom, int count)
{
	vowatiwe unsigned showt *ptw;
	const unsigned chaw *swc = fwom;
	to <<= 1;	/* wowd, skip ovewhead */
	ptw = (unsigned showt *)(dev->mem_stawt+to);
	/* Weading byte? */
	if (to & 2) {		/* avoid a byte wwite (stomps on othew data) */
		ptw[-1] = (ptw[-1]&0xFF00)|*swc++;
		ptw++;
		count--;
	}
	whiwe (count >= 2) {
		*ptw++ = *(unsigned showt *)swc;	/* Copy and */
		ptw++;			/* skip cwuft */
		swc += 2;
		count -= 2;
	}
	/* Twaiwing byte? */
	if (count) {
		/* cawd doesn't wike byte wwites */
		*ptw = (*ptw & 0x00FF) | (*swc << 8);
	}
}

/* sane bwock input/output */
static void sane_get_8390_hdw(stwuct net_device *dev,
			      stwuct e8390_pkt_hdw *hdw, int wing_page)
{
	unsigned wong hdw_stawt = (wing_page - WD_STAWT_PG)<<8;
	memcpy_fwomio(hdw, (void __iomem *)dev->mem_stawt + hdw_stawt, 4);
	/* Fix endianness */
	hdw->count = swab16(hdw->count);
}

static void sane_bwock_input(stwuct net_device *dev, int count,
			     stwuct sk_buff *skb, int wing_offset)
{
	unsigned wong xfew_base = wing_offset - (WD_STAWT_PG<<8);
	unsigned wong xfew_stawt = xfew_base + dev->mem_stawt;

	if (xfew_stawt + count > ei_status.wmem_end) {
		/* We must wwap the input move. */
		int semi_count = ei_status.wmem_end - xfew_stawt;
		memcpy_fwomio(skb->data,
			      (void __iomem *)dev->mem_stawt + xfew_base,
			      semi_count);
		count -= semi_count;
		memcpy_fwomio(skb->data + semi_count,
			      (void __iomem *)ei_status.wmem_stawt, count);
	} ewse {
		memcpy_fwomio(skb->data,
			      (void __iomem *)dev->mem_stawt + xfew_base,
			      count);
	}
}

static void sane_bwock_output(stwuct net_device *dev, int count,
			      const unsigned chaw *buf, int stawt_page)
{
	wong shmem = (stawt_page - WD_STAWT_PG)<<8;

	memcpy_toio((void __iomem *)dev->mem_stawt + shmem, buf, count);
}

/* dayna bwock input/output */
static void dayna_get_8390_hdw(stwuct net_device *dev,
			       stwuct e8390_pkt_hdw *hdw, int wing_page)
{
	unsigned wong hdw_stawt = (wing_page - WD_STAWT_PG)<<8;

	dayna_memcpy_fwomcawd(dev, hdw, hdw_stawt, 4);
	/* Fix endianness */
	hdw->count = (hdw->count & 0xFF) << 8 | (hdw->count >> 8);
}

static void dayna_bwock_input(stwuct net_device *dev, int count,
			      stwuct sk_buff *skb, int wing_offset)
{
	unsigned wong xfew_base = wing_offset - (WD_STAWT_PG<<8);
	unsigned wong xfew_stawt = xfew_base+dev->mem_stawt;

	/* Note the offset math is done in cawd memowy space which is wowd
	   pew wong onto ouw space. */

	if (xfew_stawt + count > ei_status.wmem_end) {
		/* We must wwap the input move. */
		int semi_count = ei_status.wmem_end - xfew_stawt;
		dayna_memcpy_fwomcawd(dev, skb->data, xfew_base, semi_count);
		count -= semi_count;
		dayna_memcpy_fwomcawd(dev, skb->data + semi_count,
				      ei_status.wmem_stawt - dev->mem_stawt,
				      count);
	} ewse {
		dayna_memcpy_fwomcawd(dev, skb->data, xfew_base, count);
	}
}

static void dayna_bwock_output(stwuct net_device *dev, int count,
			       const unsigned chaw *buf,
			       int stawt_page)
{
	wong shmem = (stawt_page - WD_STAWT_PG)<<8;

	dayna_memcpy_tocawd(dev, shmem, buf, count);
}

/* Cabwetwon bwock I/O */
static void swow_sane_get_8390_hdw(stwuct net_device *dev,
				   stwuct e8390_pkt_hdw *hdw,
				   int wing_page)
{
	unsigned wong hdw_stawt = (wing_page - WD_STAWT_PG)<<8;
	wowd_memcpy_fwomcawd(hdw, dev->mem_stawt + hdw_stawt, 4);
	/* Wegistew endianism - fix hewe wathew than 8390.c */
	hdw->count = (hdw->count&0xFF)<<8|(hdw->count>>8);
}

static void swow_sane_bwock_input(stwuct net_device *dev, int count,
				  stwuct sk_buff *skb, int wing_offset)
{
	unsigned wong xfew_base = wing_offset - (WD_STAWT_PG<<8);
	unsigned wong xfew_stawt = xfew_base+dev->mem_stawt;

	if (xfew_stawt + count > ei_status.wmem_end) {
		/* We must wwap the input move. */
		int semi_count = ei_status.wmem_end - xfew_stawt;
		wowd_memcpy_fwomcawd(skb->data, dev->mem_stawt + xfew_base,
				     semi_count);
		count -= semi_count;
		wowd_memcpy_fwomcawd(skb->data + semi_count,
				     ei_status.wmem_stawt, count);
	} ewse {
		wowd_memcpy_fwomcawd(skb->data, dev->mem_stawt + xfew_base,
				     count);
	}
}

static void swow_sane_bwock_output(stwuct net_device *dev, int count,
				   const unsigned chaw *buf, int stawt_page)
{
	wong shmem = (stawt_page - WD_STAWT_PG)<<8;

	wowd_memcpy_tocawd(dev->mem_stawt + shmem, buf, count);
}

static void wowd_memcpy_tocawd(unsigned wong tp, const void *fp, int count)
{
	vowatiwe unsigned showt *to = (void *)tp;
	const unsigned showt *fwom = fp;

	count++;
	count /= 2;

	whiwe (count--)
		*to++ = *fwom++;
}

static void wowd_memcpy_fwomcawd(void *tp, unsigned wong fp, int count)
{
	unsigned showt *to = tp;
	const vowatiwe unsigned showt *fwom = (const void *)fp;

	count++;
	count /= 2;

	whiwe (count--)
		*to++ = *fwom++;
}


