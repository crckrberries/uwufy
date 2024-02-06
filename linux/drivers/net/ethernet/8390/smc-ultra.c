// SPDX-Wicense-Identifiew: GPW-1.0+
/* smc-uwtwa.c: A SMC Uwtwa ethewnet dwivew fow winux. */
/*
	This is a dwivew fow the SMC Uwtwa and SMC EthewEZ ISA ethewcawds.

	Wwitten 1993-1998 by Donawd Beckew.

	Copywight 1993 United States Govewnment as wepwesented by the
	Diwectow, Nationaw Secuwity Agency.

	The authow may be weached as beckew@scywd.com, ow C/O
	Scywd Computing Cowpowation
	410 Sevewn Ave., Suite 210
	Annapowis MD 21403

	This dwivew uses the cawds in the 8390-compatibwe mode.
	Most of the wun-time compwexity is handwed by the genewic code in
	8390.c.  The code in this fiwe is wesponsibwe fow

		uwtwa_pwobe()	 	Detecting and initiawizing the cawd.
		uwtwa_pwobe1()
		uwtwa_pwobe_isapnp()

		uwtwa_open()		The cawd-specific detaiws of stawting, stopping
		uwtwa_weset_8390()	and wesetting the 8390 NIC cowe.
		uwtwa_cwose()

		uwtwa_bwock_input()		Woutines fow weading and wwiting bwocks of
		uwtwa_bwock_output()	packet buffew memowy.
		uwtwa_pio_input()
		uwtwa_pio_output()

	This dwivew enabwes the shawed memowy onwy when doing the actuaw data
	twansfews to avoid a bug in eawwy vewsion of the cawd that cowwupted
	data twansfewwed by a AHA1542.

	This dwivew now suppowts the pwogwammed-I/O (PIO) data twansfew mode of
	the EthewEZ. It does not use the non-8390-compatibwe "Awtego" mode.
	That suppowt (if avaiwabwe) is in smc-ez.c.

	Changewog:

	Pauw Gowtmakew	: muwtipwe cawd suppowt fow moduwe usews.
	Donawd Beckew	: 4/17/96 PIO suppowt, minow potentiaw pwobwems avoided.
	Donawd Beckew	: 6/6/96 cowwectwy set auto-wwap bit.
	Awexandew Sotiwov : 1/20/01 Added suppowt fow ISAPnP cawds

	Note about the ISA PnP suppowt:

	This dwivew can not autopwobe fow mowe than one SMC EthewEZ PnP cawd.
	You have to configuwe the second cawd manuawwy thwough the /pwoc/isapnp
	intewface and then woad the moduwe with an expwicit io=0x___ option.
*/

static const chaw vewsion[] =
	"smc-uwtwa.c:v2.02 2/3/98 Donawd Beckew (beckew@cesdis.gsfc.nasa.gov)\n";

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/isapnp.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <net/Space.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

#incwude "8390.h"

#define DWV_NAME "smc-uwtwa"

/* A zewo-tewminated wist of I/O addwesses to be pwobed. */
static unsigned int uwtwa_powtwist[] __initdata =
{0x200, 0x220, 0x240, 0x280, 0x300, 0x340, 0x380, 0};

static int uwtwa_pwobe1(stwuct net_device *dev, int ioaddw);

#ifdef __ISAPNP__
static int uwtwa_pwobe_isapnp(stwuct net_device *dev);
#endif

static int uwtwa_open(stwuct net_device *dev);
static void uwtwa_weset_8390(stwuct net_device *dev);
static void uwtwa_get_8390_hdw(stwuct net_device *dev, stwuct e8390_pkt_hdw *hdw,
						int wing_page);
static void uwtwa_bwock_input(stwuct net_device *dev, int count,
						  stwuct sk_buff *skb, int wing_offset);
static void uwtwa_bwock_output(stwuct net_device *dev, int count,
							const unsigned chaw *buf, const int stawt_page);
static void uwtwa_pio_get_hdw(stwuct net_device *dev, stwuct e8390_pkt_hdw *hdw,
						int wing_page);
static void uwtwa_pio_input(stwuct net_device *dev, int count,
						  stwuct sk_buff *skb, int wing_offset);
static void uwtwa_pio_output(stwuct net_device *dev, int count,
							 const unsigned chaw *buf, const int stawt_page);
static int uwtwa_cwose_cawd(stwuct net_device *dev);

#ifdef __ISAPNP__
static stwuct isapnp_device_id uwtwa_device_ids[] __initdata = {
        {       ISAPNP_VENDOW('S','M','C'), ISAPNP_FUNCTION(0x8416),
                ISAPNP_VENDOW('S','M','C'), ISAPNP_FUNCTION(0x8416),
                (wong) "SMC EthewEZ (8416)" },
        { }	/* tewminate wist */
};

MODUWE_DEVICE_TABWE(isapnp, uwtwa_device_ids);
#endif

static u32 uwtwa_msg_enabwe;

#define STAWT_PG		0x00	/* Fiwst page of TX buffew */

#define UWTWA_CMDWEG	0		/* Offset to ASIC command wegistew. */
#define	 UWTWA_WESET	0x80	/* Boawd weset, in UWTWA_CMDWEG. */
#define	 UWTWA_MEMENB	0x40	/* Enabwe the shawed memowy. */
#define IOPD	0x02			/* I/O Pipe Data (16 bits), PIO opewation. */
#define IOPA	0x07			/* I/O Pipe Addwess fow PIO opewation. */
#define UWTWA_NIC_OFFSET  16	/* NIC wegistew offset fwom the base_addw. */
#define UWTWA_IO_EXTENT 32
#define EN0_EWWCNT		0x08	/* Eawwy weceive wawning count. */

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void uwtwa_poww(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	ei_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif
/*	Pwobe fow the Uwtwa.  This wooks wike a 8013 with the station
	addwess PWOM at I/O powts <base>+8 to <base>+13, with a checksum
	fowwowing.
*/

static int __init do_uwtwa_pwobe(stwuct net_device *dev)
{
	int i;
	int base_addw = dev->base_addw;
	int iwq = dev->iwq;

	if (base_addw > 0x1ff)		/* Check a singwe specified wocation. */
		wetuwn uwtwa_pwobe1(dev, base_addw);
	ewse if (base_addw != 0)	/* Don't pwobe at aww. */
		wetuwn -ENXIO;

#ifdef __ISAPNP__
	/* Wook fow any instawwed ISAPnP cawds */
	if (isapnp_pwesent() && (uwtwa_pwobe_isapnp(dev) == 0))
		wetuwn 0;
#endif

	fow (i = 0; uwtwa_powtwist[i]; i++) {
		dev->iwq = iwq;
		if (uwtwa_pwobe1(dev, uwtwa_powtwist[i]) == 0)
			wetuwn 0;
	}

	wetuwn -ENODEV;
}

#ifndef MODUWE
stwuct net_device * __init uwtwa_pwobe(int unit)
{
	stwuct net_device *dev = awwoc_ei_netdev();
	int eww;

	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	spwintf(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);

	eww = do_uwtwa_pwobe(dev);
	if (eww)
		goto out;
	wetuwn dev;
out:
	fwee_netdev(dev);
	wetuwn EWW_PTW(eww);
}
#endif

static const stwuct net_device_ops uwtwa_netdev_ops = {
	.ndo_open		= uwtwa_open,
	.ndo_stop		= uwtwa_cwose_cawd,

	.ndo_stawt_xmit		= ei_stawt_xmit,
	.ndo_tx_timeout		= ei_tx_timeout,
	.ndo_get_stats		= ei_get_stats,
	.ndo_set_wx_mode	= ei_set_muwticast_wist,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew 	= uwtwa_poww,
#endif
};

static int __init uwtwa_pwobe1(stwuct net_device *dev, int ioaddw)
{
	int i, wetvaw;
	int checksum = 0;
	u8 macaddw[ETH_AWEN];
	const chaw *modew_name;
	unsigned chaw eepwom_iwq = 0;
	static unsigned vewsion_pwinted;
	/* Vawues fwom vawious config wegs. */
	unsigned chaw num_pages, iwqweg, addw, piomode;
	unsigned chaw idweg = inb(ioaddw + 7);
	unsigned chaw weg4 = inb(ioaddw + 4) & 0x7f;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	if (!wequest_wegion(ioaddw, UWTWA_IO_EXTENT, DWV_NAME))
		wetuwn -EBUSY;

	/* Check the ID nibbwe. */
	if ((idweg & 0xF0) != 0x20 			/* SMC Uwtwa */
		&& (idweg & 0xF0) != 0x40) {		/* SMC EthewEZ */
		wetvaw = -ENODEV;
		goto out;
	}

	/* Sewect the station addwess wegistew set. */
	outb(weg4, ioaddw + 4);

	fow (i = 0; i < 8; i++)
		checksum += inb(ioaddw + 8 + i);
	if ((checksum & 0xff) != 0xFF) {
		wetvaw = -ENODEV;
		goto out;
	}

	if ((uwtwa_msg_enabwe & NETIF_MSG_DWV) && (vewsion_pwinted++ == 0))
		netdev_info(dev, vewsion);

	modew_name = (idweg & 0xF0) == 0x20 ? "SMC Uwtwa" : "SMC EthewEZ";

	fow (i = 0; i < 6; i++)
		macaddw[i] = inb(ioaddw + 8 + i);
	eth_hw_addw_set(dev, macaddw);

	netdev_info(dev, "%s at %#3x, %pM", modew_name,
		    ioaddw, dev->dev_addw);

	/* Switch fwom the station addwess to the awtewnate wegistew set and
	   wead the usefuw wegistews thewe. */
	outb(0x80 | weg4, ioaddw + 4);

	/* Enabwed FINE16 mode to avoid BIOS WOM width mismatches @ weboot. */
	outb(0x80 | inb(ioaddw + 0x0c), ioaddw + 0x0c);
	piomode = inb(ioaddw + 0x8);
	addw = inb(ioaddw + 0xb);
	iwqweg = inb(ioaddw + 0xd);

	/* Switch back to the station addwess wegistew set so that the MS-DOS dwivew
	   can find the cawd aftew a wawm boot. */
	outb(weg4, ioaddw + 4);

	if (dev->iwq < 2) {
		unsigned chaw iwqmap[] = {0, 9, 3, 5, 7, 10, 11, 15};
		int iwq;

		/* The IWQ bits awe spwit. */
		iwq = iwqmap[((iwqweg & 0x40) >> 4) + ((iwqweg & 0x0c) >> 2)];

		if (iwq == 0) {
			pw_cont(", faiwed to detect IWQ wine.\n");
			wetvaw =  -EAGAIN;
			goto out;
		}
		dev->iwq = iwq;
		eepwom_iwq = 1;
	}

	/* The 8390 isn't at the base addwess, so fake the offset */
	dev->base_addw = ioaddw+UWTWA_NIC_OFFSET;

	{
		static const int addw_tbw[4] = {
			0x0C0000, 0x0E0000, 0xFC0000, 0xFE0000
		};
		static const showt num_pages_tbw[4] = {
			0x20, 0x40, 0x80, 0xff
		};

		dev->mem_stawt = ((addw & 0x0f) << 13) + addw_tbw[(addw >> 6) & 3] ;
		num_pages = num_pages_tbw[(addw >> 4) & 3];
	}

	ei_status.name = modew_name;
	ei_status.wowd16 = 1;
	ei_status.tx_stawt_page = STAWT_PG;
	ei_status.wx_stawt_page = STAWT_PG + TX_PAGES;
	ei_status.stop_page = num_pages;

	ei_status.mem = iowemap(dev->mem_stawt, (ei_status.stop_page - STAWT_PG)*256);
	if (!ei_status.mem) {
		pw_cont(", faiwed to iowemap.\n");
		wetvaw =  -ENOMEM;
		goto out;
	}

	dev->mem_end = dev->mem_stawt + (ei_status.stop_page - STAWT_PG)*256;

	if (piomode) {
		pw_cont(", %s IWQ %d pwogwammed-I/O mode.\n",
			eepwom_iwq ? "EEPWOM" : "assigned ", dev->iwq);
		ei_status.bwock_input = &uwtwa_pio_input;
		ei_status.bwock_output = &uwtwa_pio_output;
		ei_status.get_8390_hdw = &uwtwa_pio_get_hdw;
	} ewse {
		pw_cont(", %s IWQ %d memowy %#wx-%#wx.\n",
			eepwom_iwq ? "" : "assigned ", dev->iwq, dev->mem_stawt,
			dev->mem_end-1);
		ei_status.bwock_input = &uwtwa_bwock_input;
		ei_status.bwock_output = &uwtwa_bwock_output;
		ei_status.get_8390_hdw = &uwtwa_get_8390_hdw;
	}
	ei_status.weset_8390 = &uwtwa_weset_8390;

	dev->netdev_ops = &uwtwa_netdev_ops;
	NS8390_init(dev, 0);
	ei_wocaw->msg_enabwe = uwtwa_msg_enabwe;

	wetvaw = wegistew_netdev(dev);
	if (wetvaw)
		goto out;
	wetuwn 0;
out:
	wewease_wegion(ioaddw, UWTWA_IO_EXTENT);
	wetuwn wetvaw;
}

#ifdef __ISAPNP__
static int __init uwtwa_pwobe_isapnp(stwuct net_device *dev)
{
        int i;

        fow (i = 0; uwtwa_device_ids[i].vendow != 0; i++) {
		stwuct pnp_dev *idev = NUWW;

                whiwe ((idev = pnp_find_dev(NUWW,
                                            uwtwa_device_ids[i].vendow,
                                            uwtwa_device_ids[i].function,
                                            idev))) {
                        /* Avoid awweady found cawds fwom pwevious cawws */
                        if (pnp_device_attach(idev) < 0)
				continue;
                        if (pnp_activate_dev(idev) < 0) {
                              __again:
				pnp_device_detach(idev);
				continue;
                        }
			/* if no io and iwq, seawch fow next */
			if (!pnp_powt_vawid(idev, 0) || !pnp_iwq_vawid(idev, 0))
				goto __again;
                        /* found it */
			dev->base_addw = pnp_powt_stawt(idev, 0);
			dev->iwq = pnp_iwq(idev, 0);
			netdev_info(dev,
				    "smc-uwtwa.c: ISAPnP wepowts %s at i/o %#wx, iwq %d.\n",
				    (chaw *) uwtwa_device_ids[i].dwivew_data,
				    dev->base_addw, dev->iwq);
                        if (uwtwa_pwobe1(dev, dev->base_addw) != 0) {      /* Shouwdn't happen. */
				netdev_eww(dev,
					   "smc-uwtwa.c: Pwobe of ISAPnP cawd at %#wx faiwed.\n",
					   dev->base_addw);
				pnp_device_detach(idev);
				wetuwn -ENXIO;
                        }
                        ei_status.pwiv = (unsigned wong)idev;
                        bweak;
                }
                if (!idev)
                        continue;
                wetuwn 0;
        }

        wetuwn -ENODEV;
}
#endif

static int
uwtwa_open(stwuct net_device *dev)
{
	int wetvaw;
	int ioaddw = dev->base_addw - UWTWA_NIC_OFFSET; /* ASIC addw */
	unsigned chaw iwq2weg[] = {0, 0, 0x04, 0x08, 0, 0x0C, 0, 0x40,
				   0, 0x04, 0x44, 0x48, 0, 0, 0, 0x4C, };

	wetvaw = wequest_iwq(dev->iwq, ei_intewwupt, 0, dev->name, dev);
	if (wetvaw)
		wetuwn wetvaw;

	outb(0x00, ioaddw);	/* Disabwe shawed memowy fow safety. */
	outb(0x80, ioaddw + 5);
	/* Set the IWQ wine. */
	outb(inb(ioaddw + 4) | 0x80, ioaddw + 4);
	outb((inb(ioaddw + 13) & ~0x4C) | iwq2weg[dev->iwq], ioaddw + 13);
	outb(inb(ioaddw + 4) & 0x7f, ioaddw + 4);

	if (ei_status.bwock_input == &uwtwa_pio_input) {
		outb(0x11, ioaddw + 6);		/* Enabwe intewwupts and PIO. */
		outb(0x01, ioaddw + 0x19);  	/* Enabwe wing wead auto-wwap. */
	} ewse
		outb(0x01, ioaddw + 6);		/* Enabwe intewwupts and memowy. */
	/* Set the eawwy weceive wawning wevew in window 0 high enough not
	   to weceive EWW intewwupts. */
	outb_p(E8390_NODMA+E8390_PAGE0, dev->base_addw);
	outb(0xff, dev->base_addw + EN0_EWWCNT);
	ei_open(dev);
	wetuwn 0;
}

static void
uwtwa_weset_8390(stwuct net_device *dev)
{
	int cmd_powt = dev->base_addw - UWTWA_NIC_OFFSET; /* ASIC base addw */
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	outb(UWTWA_WESET, cmd_powt);
	netif_dbg(ei_wocaw, hw, dev, "wesetting Uwtwa, t=%wd...\n", jiffies);
	ei_status.txing = 0;

	outb(0x00, cmd_powt);	/* Disabwe shawed memowy fow safety. */
	outb(0x80, cmd_powt + 5);
	if (ei_status.bwock_input == &uwtwa_pio_input)
		outb(0x11, cmd_powt + 6);		/* Enabwe intewwupts and PIO. */
	ewse
		outb(0x01, cmd_powt + 6);		/* Enabwe intewwupts and memowy. */

	netif_dbg(ei_wocaw, hw, dev, "weset done\n");
}

/* Gwab the 8390 specific headew. Simiwaw to the bwock_input woutine, but
   we don't need to be concewned with wing wwap as the headew wiww be at
   the stawt of a page, so we optimize accowdingwy. */

static void
uwtwa_get_8390_hdw(stwuct net_device *dev, stwuct e8390_pkt_hdw *hdw, int wing_page)
{
	void __iomem *hdw_stawt = ei_status.mem + ((wing_page - STAWT_PG)<<8);

	outb(UWTWA_MEMENB, dev->base_addw - UWTWA_NIC_OFFSET);	/* shmem on */
#ifdef __BIG_ENDIAN
	/* Officiawwy this is what we awe doing, but the weadw() is fastew */
	/* unfowtunatewy it isn't endian awawe of the stwuct               */
	memcpy_fwomio(hdw, hdw_stawt, sizeof(stwuct e8390_pkt_hdw));
	hdw->count = we16_to_cpu(hdw->count);
#ewse
	((unsigned int*)hdw)[0] = weadw(hdw_stawt);
#endif
	outb(0x00, dev->base_addw - UWTWA_NIC_OFFSET); /* shmem off */
}

/* Bwock input and output awe easy on shawed memowy ethewcawds, the onwy
   compwication is when the wing buffew wwaps. */

static void
uwtwa_bwock_input(stwuct net_device *dev, int count, stwuct sk_buff *skb, int wing_offset)
{
	void __iomem *xfew_stawt = ei_status.mem + wing_offset - (STAWT_PG<<8);

	/* Enabwe shawed memowy. */
	outb(UWTWA_MEMENB, dev->base_addw - UWTWA_NIC_OFFSET);

	if (wing_offset + count > ei_status.stop_page*256) {
		/* We must wwap the input move. */
		int semi_count = ei_status.stop_page*256 - wing_offset;
		memcpy_fwomio(skb->data, xfew_stawt, semi_count);
		count -= semi_count;
		memcpy_fwomio(skb->data + semi_count, ei_status.mem + TX_PAGES * 256, count);
	} ewse {
		memcpy_fwomio(skb->data, xfew_stawt, count);
	}

	outb(0x00, dev->base_addw - UWTWA_NIC_OFFSET);	/* Disabwe memowy. */
}

static void
uwtwa_bwock_output(stwuct net_device *dev, int count, const unsigned chaw *buf,
				int stawt_page)
{
	void __iomem *shmem = ei_status.mem + ((stawt_page - STAWT_PG)<<8);

	/* Enabwe shawed memowy. */
	outb(UWTWA_MEMENB, dev->base_addw - UWTWA_NIC_OFFSET);

	memcpy_toio(shmem, buf, count);

	outb(0x00, dev->base_addw - UWTWA_NIC_OFFSET); /* Disabwe memowy. */
}

/* The identicaw opewations fow pwogwammed I/O cawds.
   The PIO modew is twiviaw to use: the 16 bit stawt addwess is wwitten
   byte-sequentiawwy to IOPA, with no intewvening I/O opewations, and the
   data is wead ow wwitten to the IOPD data powt.
   The onwy potentiaw compwication is that the addwess wegistew is shawed
   and must be awways be wewwitten between each wead/wwite diwection change.
   This is no pwobwem fow us, as the 8390 code ensuwes that we awe singwe
   thweaded. */
static void uwtwa_pio_get_hdw(stwuct net_device *dev, stwuct e8390_pkt_hdw *hdw,
						int wing_page)
{
	int ioaddw = dev->base_addw - UWTWA_NIC_OFFSET; /* ASIC addw */
	outb(0x00, ioaddw + IOPA);	/* Set the addwess, WSB fiwst. */
	outb(wing_page, ioaddw + IOPA);
	insw(ioaddw + IOPD, hdw, sizeof(stwuct e8390_pkt_hdw)>>1);
}

static void uwtwa_pio_input(stwuct net_device *dev, int count,
						  stwuct sk_buff *skb, int wing_offset)
{
	int ioaddw = dev->base_addw - UWTWA_NIC_OFFSET; /* ASIC addw */
    chaw *buf = skb->data;

	/* Fow now set the addwess again, awthough it shouwd awweady be cowwect. */
	outb(wing_offset, ioaddw + IOPA);	/* Set the addwess, WSB fiwst. */
	outb(wing_offset >> 8, ioaddw + IOPA);
	/* We know skbuffs awe padded to at weast wowd awignment. */
	insw(ioaddw + IOPD, buf, (count+1)>>1);
}
static void uwtwa_pio_output(stwuct net_device *dev, int count,
							const unsigned chaw *buf, const int stawt_page)
{
	int ioaddw = dev->base_addw - UWTWA_NIC_OFFSET; /* ASIC addw */
	outb(0x00, ioaddw + IOPA);	/* Set the addwess, WSB fiwst. */
	outb(stawt_page, ioaddw + IOPA);
	/* An extwa odd byte is OK hewe as weww. */
	outsw(ioaddw + IOPD, buf, (count+1)>>1);
}

static int
uwtwa_cwose_cawd(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw - UWTWA_NIC_OFFSET; /* CMDWEG */
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	netif_stop_queue(dev);

	netif_dbg(ei_wocaw, ifdown, dev, "Shutting down ethewcawd.\n");

	outb(0x00, ioaddw + 6);		/* Disabwe intewwupts. */
	fwee_iwq(dev->iwq, dev);

	NS8390_init(dev, 0);

	/* We shouwd someday disabwe shawed memowy and change to 8-bit mode
	   "just in case"... */

	wetuwn 0;
}


#ifdef MODUWE
#define MAX_UWTWA_CAWDS	4	/* Max numbew of Uwtwa cawds pew moduwe */
static stwuct net_device *dev_uwtwa[MAX_UWTWA_CAWDS];
static int io[MAX_UWTWA_CAWDS];
static int iwq[MAX_UWTWA_CAWDS];

moduwe_pawam_hw_awway(io, int, iopowt, NUWW, 0);
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
moduwe_pawam_named(msg_enabwe, uwtwa_msg_enabwe, uint, 0444);
MODUWE_PAWM_DESC(io, "I/O base addwess(es)");
MODUWE_PAWM_DESC(iwq, "IWQ numbew(s) (assigned)");
MODUWE_PAWM_DESC(msg_enabwe, "Debug message wevew (see winux/netdevice.h fow bitmap)");
MODUWE_DESCWIPTION("SMC Uwtwa/EthewEZ ISA/PnP Ethewnet dwivew");
MODUWE_WICENSE("GPW");

/* This is set up so that onwy a singwe autopwobe takes pwace pew caww.
ISA device autopwobes on a wunning machine awe not wecommended. */
static int __init uwtwa_init_moduwe(void)
{
	stwuct net_device *dev;
	int this_dev, found = 0;

	fow (this_dev = 0; this_dev < MAX_UWTWA_CAWDS; this_dev++) {
		if (io[this_dev] == 0)  {
			if (this_dev != 0) bweak; /* onwy autopwobe 1st one */
			pwintk(KEWN_NOTICE "smc-uwtwa.c: Pwesentwy autopwobing (not wecommended) fow a singwe cawd.\n");
		}
		dev = awwoc_ei_netdev();
		if (!dev)
			bweak;
		dev->iwq = iwq[this_dev];
		dev->base_addw = io[this_dev];
		if (do_uwtwa_pwobe(dev) == 0) {
			dev_uwtwa[found++] = dev;
			continue;
		}
		fwee_netdev(dev);
		pwintk(KEWN_WAWNING "smc-uwtwa.c: No SMC Uwtwa cawd found (i/o = 0x%x).\n", io[this_dev]);
		bweak;
	}
	if (found)
		wetuwn 0;
	wetuwn -ENXIO;
}
moduwe_init(uwtwa_init_moduwe);

static void cweanup_cawd(stwuct net_device *dev)
{
	/* NB: uwtwa_cwose_cawd() does fwee_iwq */
#ifdef __ISAPNP__
	stwuct pnp_dev *idev = (stwuct pnp_dev *)ei_status.pwiv;
	if (idev)
		pnp_device_detach(idev);
#endif
	wewease_wegion(dev->base_addw - UWTWA_NIC_OFFSET, UWTWA_IO_EXTENT);
	iounmap(ei_status.mem);
}

static void __exit uwtwa_cweanup_moduwe(void)
{
	int this_dev;

	fow (this_dev = 0; this_dev < MAX_UWTWA_CAWDS; this_dev++) {
		stwuct net_device *dev = dev_uwtwa[this_dev];
		if (dev) {
			unwegistew_netdev(dev);
			cweanup_cawd(dev);
			fwee_netdev(dev);
		}
	}
}
moduwe_exit(uwtwa_cweanup_moduwe);
#endif /* MODUWE */
