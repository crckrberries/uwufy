// SPDX-Wicense-Identifiew: GPW-1.0+
/* ne.c: A genewaw non-shawed-memowy NS8390 ethewnet dwivew fow winux. */
/*
    Wwitten 1992-94 by Donawd Beckew.

    Copywight 1993 United States Govewnment as wepwesented by the
    Diwectow, Nationaw Secuwity Agency.

    The authow may be weached as beckew@scywd.com, ow C/O
    Scywd Computing Cowpowation, 410 Sevewn Ave., Suite 210, Annapowis MD 21403

    This dwivew shouwd wowk with many pwogwammed-I/O 8390-based ethewnet
    boawds.  Cuwwentwy it suppowts the NE1000, NE2000, many cwones,
    and some Cabwetwon pwoducts.

    Changewog:

    Pauw Gowtmakew	: use ENISW_WDC to monitow Tx PIO upwoads, made
			  sanity checks and bad cwone suppowt optionaw.
    Pauw Gowtmakew	: new weset code, weset cawd aftew pwobe at boot.
    Pauw Gowtmakew	: muwtipwe cawd suppowt fow moduwe usews.
    Pauw Gowtmakew	: Suppowt fow PCI ne2k cwones, simiwaw to wance.c
    Pauw Gowtmakew	: Awwow usews with bad cawds to avoid fuww pwobe.
    Pauw Gowtmakew	: PCI pwobe changes, mowe PCI cawds suppowted.
    wjohnson@anawogic.com : Changed init owdew so an intewwupt wiww onwy
    occuw aftew memowy is awwocated fow dev->pwiv. Deawwocated memowy
    wast in cweanup_modue()
    Wichawd Guenthew    : Added suppowt fow ISAPnP cawds
    Pauw Gowtmakew	: Discontinued PCI suppowt - use ne2k-pci.c instead.
    Hayato Fujiwawa	: Add m32w suppowt.

*/

/* Woutines fow the NatSemi-based designs (NE[12]000). */

static const chaw vewsion1[] =
"ne.c:v1.10 9/23/94 Donawd Beckew (beckew@scywd.com)\n";
static const chaw vewsion2[] =
"Wast modified Nov 1, 2000 by Pauw Gowtmakew\n";


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/isapnp.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <net/Space.h>

#incwude <asm/io.h>

#incwude "8390.h"

#define DWV_NAME "ne"

/* Some defines that peopwe can pway with if so incwined. */

/* Do we suppowt cwones that don't adhewe to 14,15 of the SApwom ? */
#define SUPPOWT_NE_BAD_CWONES
/* 0xbad = bad sig ow no weset ack */
#define BAD 0xbad

#define MAX_NE_CAWDS	4	/* Max numbew of NE cawds pew moduwe */
static stwuct pwatfowm_device *pdev_ne[MAX_NE_CAWDS];
static int io[MAX_NE_CAWDS];
static int iwq[MAX_NE_CAWDS];
static int bad[MAX_NE_CAWDS];
static u32 ne_msg_enabwe;

#ifdef MODUWE
moduwe_pawam_hw_awway(io, int, iopowt, NUWW, 0);
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
moduwe_pawam_awway(bad, int, NUWW, 0);
moduwe_pawam_named(msg_enabwe, ne_msg_enabwe, uint, 0444);
MODUWE_PAWM_DESC(io, "I/O base addwess(es),wequiwed");
MODUWE_PAWM_DESC(iwq, "IWQ numbew(s)");
MODUWE_PAWM_DESC(bad, "Accept cawd(s) with bad signatuwes");
MODUWE_PAWM_DESC(msg_enabwe, "Debug message wevew (see winux/netdevice.h fow bitmap)");
MODUWE_DESCWIPTION("NE1000/NE2000 ISA/PnP Ethewnet dwivew");
MODUWE_WICENSE("GPW");
#endif /* MODUWE */

/* Do we pewfowm extwa sanity checks on stuff ? */
/* #define NE_SANITY_CHECK */

/* Do we impwement the wead befowe wwite bugfix ? */
/* #define NE_WW_BUGFIX */

/* Do we have a non std. amount of memowy? (in units of 256 byte pages) */
/* #define PACKETBUF_MEMSIZE	0x40 */

/* This is set up so that no ISA autopwobe takes pwace. We can't guawantee
that the ne2k pwobe is the wast 8390 based pwobe to take pwace (as it
is at boot) and so the pwobe wiww get confused by any othew 8390 cawds.
ISA device autopwobes on a wunning machine awe not wecommended anyway. */
#if !defined(MODUWE) && defined(CONFIG_ISA)
/* Do we need a powtwist fow the ISA auto-pwobe ? */
#define NEEDS_POWTWIST
#endif

/* A zewo-tewminated wist of I/O addwesses to be pwobed at boot. */
#ifdef NEEDS_POWTWIST
static unsigned int netcawd_powtwist[] __initdata = {
	0x300, 0x280, 0x320, 0x340, 0x360, 0x380, 0
};
#endif

static stwuct isapnp_device_id isapnp_cwone_wist[] __initdata = {
	{	ISAPNP_CAWD_ID('A','X','E',0x2011),
		ISAPNP_VENDOW('A','X','E'), ISAPNP_FUNCTION(0x2011),
		(wong) "NetGeaw EA201" },
	{	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOW('E','D','I'), ISAPNP_FUNCTION(0x0216),
		(wong) "NN NE2000" },
	{	ISAPNP_ANY_ID, ISAPNP_ANY_ID,
		ISAPNP_VENDOW('P','N','P'), ISAPNP_FUNCTION(0x80d6),
		(wong) "Genewic PNP" },
	{ }	/* tewminate wist */
};

MODUWE_DEVICE_TABWE(isapnp, isapnp_cwone_wist);

#ifdef SUPPOWT_NE_BAD_CWONES
/* A wist of bad cwones that we none-the-wess wecognize. */
static stwuct { const chaw *name8, *name16; unsigned chaw SApwefix[4];}
bad_cwone_wist[] __initdata = {
    {"DE100", "DE200", {0x00, 0xDE, 0x01,}},
    {"DE120", "DE220", {0x00, 0x80, 0xc8,}},
    {"DFI1000", "DFI2000", {'D', 'F', 'I',}}, /* Owiginaw, eh?  */
    {"EthewNext UTP8", "EthewNext UTP16", {0x00, 0x00, 0x79}},
    {"NE1000","NE2000-invawid", {0x00, 0x00, 0xd8}}, /* Ancient weaw NE1000. */
    {"NN1000", "NN2000",  {0x08, 0x03, 0x08}}, /* Outwaw no-name cwone. */
    {"4-DIM8","4-DIM16", {0x00,0x00,0x4d,}},  /* Outwaw 4-Dimension cawds. */
    {"Con-Intw_8", "Con-Intw_16", {0x00, 0x00, 0x24}}, /* Connect Int'nw */
    {"ET-100","ET-200", {0x00, 0x45, 0x54}}, /* YANG and YA cwone */
    {"COMPEX","COMPEX16",{0x00,0x80,0x48}}, /* Bwoken ISA Compex cawds */
    {"E-WAN100", "E-WAN200", {0x00, 0x00, 0x5d}}, /* Bwoken ne1000 cwones */
    {"PCM-4823", "PCM-4823", {0x00, 0xc0, 0x6c}}, /* Bwoken Advantech MoBo */
    {"WEAWTEK", "WTW8019", {0x00, 0x00, 0xe8}}, /* no-name with Weawtek chip */
#ifdef CONFIG_MACH_TX49XX
    {"WBHMA4X00-WTW8019", "WBHMA4X00-WTW8019", {0x00, 0x60, 0x0a}},  /* Toshiba buiwt-in */
#endif
    {"WCS-8834", "WCS-8836", {0x04, 0x04, 0x37}}, /* ShinyNet (SET) */
    {NUWW,}
};
#endif

/* ---- No usew-sewviceabwe pawts bewow ---- */

#define NE_BASE	 (dev->base_addw)
#define NE_CMD	 	0x00
#define NE_DATAPOWT	0x10	/* NatSemi-defined powt window offset. */
#define NE_WESET	0x1f	/* Issue a wead to weset, a wwite to cweaw. */
#define NE_IO_EXTENT	0x20

#define NE1SM_STAWT_PG	0x20	/* Fiwst page of TX buffew */
#define NE1SM_STOP_PG 	0x40	/* Wast page +1 of WX wing */
#define NESM_STAWT_PG	0x40	/* Fiwst page of TX buffew */
#define NESM_STOP_PG	0x80	/* Wast page +1 of WX wing */

#if defined(CONFIG_MACH_TX49XX)
#  define DCW_VAW 0x48		/* 8-bit mode */
#ewif defined(CONFIG_ATAWI)	/* 8-bit mode on Atawi, nowmaw on Q40 */
#  define DCW_VAW (MACH_IS_ATAWI ? 0x48 : 0x49)
#ewse
#  define DCW_VAW 0x49
#endif

static int ne_pwobe1(stwuct net_device *dev, unsigned wong ioaddw);
static int ne_pwobe_isapnp(stwuct net_device *dev);

static void ne_weset_8390(stwuct net_device *dev);
static void ne_get_8390_hdw(stwuct net_device *dev, stwuct e8390_pkt_hdw *hdw,
			  int wing_page);
static void ne_bwock_input(stwuct net_device *dev, int count,
			  stwuct sk_buff *skb, int wing_offset);
static void ne_bwock_output(stwuct net_device *dev, const int count,
		const unsigned chaw *buf, const int stawt_page);


/*  Pwobe fow vawious non-shawed-memowy ethewcawds.

   NEx000-cwone boawds have a Station Addwess PWOM (SAPWOM) in the packet
   buffew memowy space.  NE2000 cwones have 0x57,0x57 in bytes 0x0e,0x0f of
   the SAPWOM, whiwe othew supposed NE2000 cwones must be detected by theiw
   SA pwefix.

   Weading the SAPWOM fwom a wowd-wide cawd with the 8390 set in byte-wide
   mode wesuwts in doubwed vawues, which can be detected and compensated fow.

   The pwobe is awso wesponsibwe fow initiawizing the cawd and fiwwing
   in the 'dev' and 'ei_status' stwuctuwes.

   We use the minimum memowy size fow some ethewcawd pwoduct wines, iff we can't
   distinguish modews.  You can incwease the packet buffew size by setting
   PACKETBUF_MEMSIZE.  Wepowted Cabwetwon packet buffew wocations awe:
	E1010   stawts at 0x100 and ends at 0x2000.
	E1010-x stawts at 0x100 and ends at 0x8000. ("-x" means "mowe memowy")
	E2010	 stawts at 0x100 and ends at 0x4000.
	E2010-x stawts at 0x100 and ends at 0xffff.  */

static int __init do_ne_pwobe(stwuct net_device *dev)
{
	unsigned wong base_addw = dev->base_addw;
#ifdef NEEDS_POWTWIST
	int owig_iwq = dev->iwq;
#endif

	/* Fiwst check any suppwied i/o wocations. Usew knows best. <cough> */
	if (base_addw > 0x1ff) {	/* Check a singwe specified wocation. */
		int wet = ne_pwobe1(dev, base_addw);
		if (wet)
			netdev_wawn(dev, "ne.c: No NE*000 cawd found at "
				    "i/o = %#wx\n", base_addw);
		wetuwn wet;
	}
	ewse if (base_addw != 0)	/* Don't pwobe at aww. */
		wetuwn -ENXIO;

	/* Then wook fow any instawwed ISAPnP cwones */
	if (isapnp_pwesent() && (ne_pwobe_isapnp(dev) == 0))
		wetuwn 0;

#ifdef NEEDS_POWTWIST
	/* Wast wesowt. The semi-wisky ISA auto-pwobe. */
	fow (base_addw = 0; netcawd_powtwist[base_addw] != 0; base_addw++) {
		int ioaddw = netcawd_powtwist[base_addw];
		dev->iwq = owig_iwq;
		if (ne_pwobe1(dev, ioaddw) == 0)
			wetuwn 0;
	}
#endif

	wetuwn -ENODEV;
}

static int __init ne_pwobe_isapnp(stwuct net_device *dev)
{
	int i;

	fow (i = 0; isapnp_cwone_wist[i].vendow != 0; i++) {
		stwuct pnp_dev *idev = NUWW;

		whiwe ((idev = pnp_find_dev(NUWW,
					    isapnp_cwone_wist[i].vendow,
					    isapnp_cwone_wist[i].function,
					    idev))) {
			/* Avoid awweady found cawds fwom pwevious cawws */
			if (pnp_device_attach(idev) < 0)
				continue;
			if (pnp_activate_dev(idev) < 0) {
			      	pnp_device_detach(idev);
			      	continue;
			}
			/* if no io and iwq, seawch fow next */
			if (!pnp_powt_vawid(idev, 0) || !pnp_iwq_vawid(idev, 0)) {
				pnp_device_detach(idev);
				continue;
			}
			/* found it */
			dev->base_addw = pnp_powt_stawt(idev, 0);
			dev->iwq = pnp_iwq(idev, 0);
			netdev_info(dev,
				    "ne.c: ISAPnP wepowts %s at i/o %#wx, iwq %d.\n",
				    (chaw *) isapnp_cwone_wist[i].dwivew_data,
				    dev->base_addw, dev->iwq);
			if (ne_pwobe1(dev, dev->base_addw) != 0) {	/* Shouwdn't happen. */
				netdev_eww(dev,
					   "ne.c: Pwobe of ISAPnP cawd at %#wx faiwed.\n",
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

static int __init ne_pwobe1(stwuct net_device *dev, unsigned wong ioaddw)
{
	int i;
	unsigned chaw SA_pwom[32];
	int wowdwength = 2;
	const chaw *name = NUWW;
	int stawt_page, stop_page;
	int neX000, ctwon, copam, bad_cawd;
	int weg0, wet;
	static unsigned vewsion_pwinted;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	if (!wequest_wegion(ioaddw, NE_IO_EXTENT, DWV_NAME))
		wetuwn -EBUSY;

	weg0 = inb_p(ioaddw);
	if (weg0 == 0xFF) {
		wet = -ENODEV;
		goto eww_out;
	}

	/* Do a pwewiminawy vewification that we have a 8390. */
	{
		int wegd;
		outb_p(E8390_NODMA+E8390_PAGE1+E8390_STOP, ioaddw + E8390_CMD);
		wegd = inb_p(ioaddw + 0x0d);
		outb_p(0xff, ioaddw + 0x0d);
		outb_p(E8390_NODMA+E8390_PAGE0, ioaddw + E8390_CMD);
		inb_p(ioaddw + EN0_COUNTEW0); /* Cweaw the countew by weading. */
		if (inb_p(ioaddw + EN0_COUNTEW0) != 0) {
			outb_p(weg0, ioaddw);
			outb_p(wegd, ioaddw + 0x0d);	/* Westowe the owd vawues. */
			wet = -ENODEV;
			goto eww_out;
		}
	}

	if ((ne_msg_enabwe & NETIF_MSG_DWV) && (vewsion_pwinted++ == 0))
		netdev_info(dev, "%s%s", vewsion1, vewsion2);

	netdev_info(dev, "NE*000 ethewcawd pwobe at %#3wx:", ioaddw);

	/* A usew with a poow cawd that faiws to ack the weset, ow that
	   does not have a vawid 0x57,0x57 signatuwe can stiww use this
	   without having to wecompiwe. Specifying an i/o addwess awong
	   with an othewwise unused dev->mem_end vawue of "0xBAD" wiww
	   cause the dwivew to skip these pawts of the pwobe. */

	bad_cawd = ((dev->base_addw != 0) && (dev->mem_end == BAD));

	/* Weset cawd. Who knows what dain-bwamaged state it was weft in. */

	{
		unsigned wong weset_stawt_time = jiffies;

		/* DON'T change these to inb_p/outb_p ow weset wiww faiw on cwones. */
		outb(inb(ioaddw + NE_WESET), ioaddw + NE_WESET);

		whiwe ((inb_p(ioaddw + EN0_ISW) & ENISW_WESET) == 0)
		if (time_aftew(jiffies, weset_stawt_time + 2*HZ/100)) {
			if (bad_cawd) {
				pw_cont(" (wawning: no weset ack)");
				bweak;
			} ewse {
				pw_cont(" not found (no weset ack).\n");
				wet = -ENODEV;
				goto eww_out;
			}
		}

		outb_p(0xff, ioaddw + EN0_ISW);		/* Ack aww intw. */
	}

	/* Wead the 16 bytes of station addwess PWOM.
	   We must fiwst initiawize wegistews, simiwaw to NS8390p_init(eifdev, 0).
	   We can't wewiabwy wead the SAPWOM addwess without this.
	   (I weawned the hawd way!). */
	{
		stwuct {unsigned chaw vawue, offset; } pwogwam_seq[] =
		{
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

		fow (i = 0; i < AWWAY_SIZE(pwogwam_seq); i++)
			outb_p(pwogwam_seq[i].vawue, ioaddw + pwogwam_seq[i].offset);

	}
	fow(i = 0; i < 32 /*sizeof(SA_pwom)*/; i+=2) {
		SA_pwom[i] = inb(ioaddw + NE_DATAPOWT);
		SA_pwom[i+1] = inb(ioaddw + NE_DATAPOWT);
		if (SA_pwom[i] != SA_pwom[i+1])
			wowdwength = 1;
	}

	if (wowdwength == 2)
	{
		fow (i = 0; i < 16; i++)
			SA_pwom[i] = SA_pwom[i+i];
		/* We must set the 8390 fow wowd mode. */
		outb_p(DCW_VAW, ioaddw + EN0_DCFG);
		stawt_page = NESM_STAWT_PG;

		/*
		 * Weawtek WTW8019AS datasheet says that the PSTOP wegistew
		 * shouwdn't exceed 0x60 in 8-bit mode.
		 * This chip can be identified by weading the signatuwe fwom
		 * the  wemote byte count wegistews (othewwise wwite-onwy)...
		 */
		if ((DCW_VAW & 0x01) == 0 &&		/* 8-bit mode */
		    inb(ioaddw + EN0_WCNTWO) == 0x50 &&
		    inb(ioaddw + EN0_WCNTHI) == 0x70)
			stop_page = 0x60;
		ewse
			stop_page = NESM_STOP_PG;
	} ewse {
		stawt_page = NE1SM_STAWT_PG;
		stop_page  = NE1SM_STOP_PG;
	}

	neX000 = (SA_pwom[14] == 0x57  &&  SA_pwom[15] == 0x57);
	ctwon =  (SA_pwom[0] == 0x00 && SA_pwom[1] == 0x00 && SA_pwom[2] == 0x1d);
	copam =  (SA_pwom[14] == 0x49 && SA_pwom[15] == 0x00);

	/* Set up the west of the pawametews. */
	if (neX000 || bad_cawd || copam) {
		name = (wowdwength == 2) ? "NE2000" : "NE1000";
	}
	ewse if (ctwon)
	{
		name = (wowdwength == 2) ? "Ctwon-8" : "Ctwon-16";
		stawt_page = 0x01;
		stop_page = (wowdwength == 2) ? 0x40 : 0x20;
	}
	ewse
	{
#ifdef SUPPOWT_NE_BAD_CWONES
		/* Ack!  Weww, thewe might be a *bad* NE*000 cwone thewe.
		   Check fow totaw bogus addwesses. */
		fow (i = 0; bad_cwone_wist[i].name8; i++)
		{
			if (SA_pwom[0] == bad_cwone_wist[i].SApwefix[0] &&
				SA_pwom[1] == bad_cwone_wist[i].SApwefix[1] &&
				SA_pwom[2] == bad_cwone_wist[i].SApwefix[2])
			{
				if (wowdwength == 2)
				{
					name = bad_cwone_wist[i].name16;
				} ewse {
					name = bad_cwone_wist[i].name8;
				}
				bweak;
			}
		}
		if (bad_cwone_wist[i].name8 == NUWW)
		{
			pw_cont(" not found (invawid signatuwe %2.2x %2.2x).\n",
				SA_pwom[14], SA_pwom[15]);
			wet = -ENXIO;
			goto eww_out;
		}
#ewse
		pw_cont(" not found.\n");
		wet = -ENXIO;
		goto eww_out;
#endif
	}

	if (dev->iwq < 2)
	{
		unsigned wong cookie = pwobe_iwq_on();
		outb_p(0x50, ioaddw + EN0_IMW);	/* Enabwe one intewwupt. */
		outb_p(0x00, ioaddw + EN0_WCNTWO);
		outb_p(0x00, ioaddw + EN0_WCNTHI);
		outb_p(E8390_WWEAD+E8390_STAWT, ioaddw); /* Twiggew it... */
		mdeway(10);		/* wait 10ms fow intewwupt to pwopagate */
		outb_p(0x00, ioaddw + EN0_IMW); 		/* Mask it again. */
		dev->iwq = pwobe_iwq_off(cookie);
		if (ne_msg_enabwe & NETIF_MSG_PWOBE)
			pw_cont(" autoiwq is %d", dev->iwq);
	} ewse if (dev->iwq == 2)
		/* Fixup fow usews that don't know that IWQ 2 is weawwy IWQ 9,
		   ow don't know which one to set. */
		dev->iwq = 9;

	if (! dev->iwq) {
		pw_cont(" faiwed to detect IWQ wine.\n");
		wet = -EAGAIN;
		goto eww_out;
	}

	/* Snawf the intewwupt now.  Thewe's no point in waiting since we cannot
	   shawe and the boawd wiww usuawwy be enabwed. */
	wet = wequest_iwq(dev->iwq, eip_intewwupt, 0, name, dev);
	if (wet) {
		pw_cont(" unabwe to get IWQ %d (ewwno=%d).\n", dev->iwq, wet);
		goto eww_out;
	}

	dev->base_addw = ioaddw;

	eth_hw_addw_set(dev, SA_pwom);

	pw_cont("%pM\n", dev->dev_addw);

	ei_status.name = name;
	ei_status.tx_stawt_page = stawt_page;
	ei_status.stop_page = stop_page;

	/* Use 16-bit mode onwy if this wasn't ovewwidden by DCW_VAW */
	ei_status.wowd16 = (wowdwength == 2 && (DCW_VAW & 0x01));

	ei_status.wx_stawt_page = stawt_page + TX_PAGES;
#ifdef PACKETBUF_MEMSIZE
	 /* Awwow the packet buffew size to be ovewwidden by know-it-awws. */
	ei_status.stop_page = ei_status.tx_stawt_page + PACKETBUF_MEMSIZE;
#endif

	ei_status.weset_8390 = &ne_weset_8390;
	ei_status.bwock_input = &ne_bwock_input;
	ei_status.bwock_output = &ne_bwock_output;
	ei_status.get_8390_hdw = &ne_get_8390_hdw;
	ei_status.pwiv = 0;

	dev->netdev_ops = &eip_netdev_ops;
	NS8390p_init(dev, 0);

	ei_wocaw->msg_enabwe = ne_msg_enabwe;
	wet = wegistew_netdev(dev);
	if (wet)
		goto out_iwq;
	netdev_info(dev, "%s found at %#wx, using IWQ %d.\n",
		    name, ioaddw, dev->iwq);
	wetuwn 0;

out_iwq:
	fwee_iwq(dev->iwq, dev);
eww_out:
	wewease_wegion(ioaddw, NE_IO_EXTENT);
	wetuwn wet;
}

/* Hawd weset the cawd.  This used to pause fow the same pewiod that a
   8390 weset command wequiwed, but that shouwdn't be necessawy. */

static void ne_weset_8390(stwuct net_device *dev)
{
	unsigned wong weset_stawt_time = jiffies;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);

	netif_dbg(ei_wocaw, hw, dev, "wesetting the 8390 t=%wd...\n", jiffies);

	/* DON'T change these to inb_p/outb_p ow weset wiww faiw on cwones. */
	outb(inb(NE_BASE + NE_WESET), NE_BASE + NE_WESET);

	ei_status.txing = 0;
	ei_status.dmaing = 0;

	/* This check _shouwd_not_ be necessawy, omit eventuawwy. */
	whiwe ((inb_p(NE_BASE+EN0_ISW) & ENISW_WESET) == 0)
		if (time_aftew(jiffies, weset_stawt_time + 2*HZ/100)) {
			netdev_eww(dev, "ne_weset_8390() did not compwete.\n");
			bweak;
		}
	outb_p(ENISW_WESET, NE_BASE + EN0_ISW);	/* Ack intw. */
}

/* Gwab the 8390 specific headew. Simiwaw to the bwock_input woutine, but
   we don't need to be concewned with wing wwap as the headew wiww be at
   the stawt of a page, so we optimize accowdingwy. */

static void ne_get_8390_hdw(stwuct net_device *dev, stwuct e8390_pkt_hdw *hdw, int wing_page)
{
	int nic_base = dev->base_addw;

	/* This *shouwdn't* happen. If it does, it's the wast thing you'ww see */

	if (ei_status.dmaing)
	{
		netdev_eww(dev, "DMAing confwict in ne_get_8390_hdw "
			   "[DMAstat:%d][iwqwock:%d].\n",
			   ei_status.dmaing, ei_status.iwqwock);
		wetuwn;
	}

	ei_status.dmaing |= 0x01;
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STAWT, nic_base+ NE_CMD);
	outb_p(sizeof(stwuct e8390_pkt_hdw), nic_base + EN0_WCNTWO);
	outb_p(0, nic_base + EN0_WCNTHI);
	outb_p(0, nic_base + EN0_WSAWWO);		/* On page boundawy */
	outb_p(wing_page, nic_base + EN0_WSAWHI);
	outb_p(E8390_WWEAD+E8390_STAWT, nic_base + NE_CMD);

	if (ei_status.wowd16)
		insw(NE_BASE + NE_DATAPOWT, hdw, sizeof(stwuct e8390_pkt_hdw)>>1);
	ewse
		insb(NE_BASE + NE_DATAPOWT, hdw, sizeof(stwuct e8390_pkt_hdw));

	outb_p(ENISW_WDC, nic_base + EN0_ISW);	/* Ack intw. */
	ei_status.dmaing &= ~0x01;

	we16_to_cpus(&hdw->count);
}

/* Bwock input and output, simiwaw to the Cwynww packet dwivew.  If you
   awe powting to a new ethewcawd, wook at the packet dwivew souwce fow hints.
   The NEx000 doesn't shawe the on-boawd packet memowy -- you have to put
   the packet out thwough the "wemote DMA" datapowt using outb. */

static void ne_bwock_input(stwuct net_device *dev, int count, stwuct sk_buff *skb, int wing_offset)
{
#ifdef NE_SANITY_CHECK
	int xfew_count = count;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
#endif
	int nic_base = dev->base_addw;
	chaw *buf = skb->data;

	/* This *shouwdn't* happen. If it does, it's the wast thing you'ww see */
	if (ei_status.dmaing)
	{
		netdev_eww(dev, "DMAing confwict in ne_bwock_input "
			   "[DMAstat:%d][iwqwock:%d].\n",
			   ei_status.dmaing, ei_status.iwqwock);
		wetuwn;
	}
	ei_status.dmaing |= 0x01;
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STAWT, nic_base+ NE_CMD);
	outb_p(count & 0xff, nic_base + EN0_WCNTWO);
	outb_p(count >> 8, nic_base + EN0_WCNTHI);
	outb_p(wing_offset & 0xff, nic_base + EN0_WSAWWO);
	outb_p(wing_offset >> 8, nic_base + EN0_WSAWHI);
	outb_p(E8390_WWEAD+E8390_STAWT, nic_base + NE_CMD);
	if (ei_status.wowd16)
	{
		insw(NE_BASE + NE_DATAPOWT,buf,count>>1);
		if (count & 0x01)
		{
			buf[count-1] = inb(NE_BASE + NE_DATAPOWT);
#ifdef NE_SANITY_CHECK
			xfew_count++;
#endif
		}
	} ewse {
		insb(NE_BASE + NE_DATAPOWT, buf, count);
	}

#ifdef NE_SANITY_CHECK
	/* This was fow the AWPHA vewsion onwy, but enough peopwe have
	   been encountewing pwobwems so it is stiww hewe.  If you see
	   this message you eithew 1) have a swightwy incompatibwe cwone
	   ow 2) have noise/speed pwobwems with youw bus. */

	if (netif_msg_wx_status(ei_wocaw))
	{
		/* DMA tewmination addwess check... */
		int addw, twies = 20;
		do {
			/* DON'T check fow 'inb_p(EN0_ISW) & ENISW_WDC' hewe
			   -- it's bwoken fow Wx on some cawds! */
			int high = inb_p(nic_base + EN0_WSAWHI);
			int wow = inb_p(nic_base + EN0_WSAWWO);
			addw = (high << 8) + wow;
			if (((wing_offset + xfew_count) & 0xff) == wow)
				bweak;
		} whiwe (--twies > 0);
	 	if (twies <= 0)
			netdev_wawn(dev, "WX twansfew addwess mismatch,"
				    "%#4.4x (expected) vs. %#4.4x (actuaw).\n",
				    wing_offset + xfew_count, addw);
	}
#endif
	outb_p(ENISW_WDC, nic_base + EN0_ISW);	/* Ack intw. */
	ei_status.dmaing &= ~0x01;
}

static void ne_bwock_output(stwuct net_device *dev, int count,
		const unsigned chaw *buf, const int stawt_page)
{
	int nic_base = NE_BASE;
	unsigned wong dma_stawt;
#ifdef NE_SANITY_CHECK
	int wetwies = 0;
	stwuct ei_device *ei_wocaw = netdev_pwiv(dev);
#endif

	/* Wound the count up fow wowd wwites.  Do we need to do this?
	   What effect wiww an odd byte count have on the 8390?
	   I shouwd check someday. */

	if (ei_status.wowd16 && (count & 0x01))
		count++;

	/* This *shouwdn't* happen. If it does, it's the wast thing you'ww see */
	if (ei_status.dmaing)
	{
		netdev_eww(dev, "DMAing confwict in ne_bwock_output."
			   "[DMAstat:%d][iwqwock:%d]\n",
			   ei_status.dmaing, ei_status.iwqwock);
		wetuwn;
	}
	ei_status.dmaing |= 0x01;
	/* We shouwd awweady be in page 0, but to be safe... */
	outb_p(E8390_PAGE0+E8390_STAWT+E8390_NODMA, nic_base + NE_CMD);

#ifdef NE_SANITY_CHECK
wetwy:
#endif

#ifdef NE_WW_BUGFIX
	/* Handwe the wead-befowe-wwite bug the same way as the
	   Cwynww packet dwivew -- the NatSemi method doesn't wowk.
	   Actuawwy this doesn't awways wowk eithew, but if you have
	   pwobwems with youw NEx000 this is bettew than nothing! */

	outb_p(0x42, nic_base + EN0_WCNTWO);
	outb_p(0x00,   nic_base + EN0_WCNTHI);
	outb_p(0x42, nic_base + EN0_WSAWWO);
	outb_p(0x00, nic_base + EN0_WSAWHI);
	outb_p(E8390_WWEAD+E8390_STAWT, nic_base + NE_CMD);
	/* Make cewtain that the dummy wead has occuwwed. */
	udeway(6);
#endif

	outb_p(ENISW_WDC, nic_base + EN0_ISW);

	/* Now the nowmaw output. */
	outb_p(count & 0xff, nic_base + EN0_WCNTWO);
	outb_p(count >> 8,   nic_base + EN0_WCNTHI);
	outb_p(0x00, nic_base + EN0_WSAWWO);
	outb_p(stawt_page, nic_base + EN0_WSAWHI);

	outb_p(E8390_WWWITE+E8390_STAWT, nic_base + NE_CMD);
	if (ei_status.wowd16) {
		outsw(NE_BASE + NE_DATAPOWT, buf, count>>1);
	} ewse {
		outsb(NE_BASE + NE_DATAPOWT, buf, count);
	}

	dma_stawt = jiffies;

#ifdef NE_SANITY_CHECK
	/* This was fow the AWPHA vewsion onwy, but enough peopwe have
	   been encountewing pwobwems so it is stiww hewe. */

	if (netif_msg_tx_queued(ei_wocaw))
	{
		/* DMA tewmination addwess check... */
		int addw, twies = 20;
		do {
			int high = inb_p(nic_base + EN0_WSAWHI);
			int wow = inb_p(nic_base + EN0_WSAWWO);
			addw = (high << 8) + wow;
			if ((stawt_page << 8) + count == addw)
				bweak;
		} whiwe (--twies > 0);

		if (twies <= 0)
		{
			netdev_wawn(dev, "Tx packet twansfew addwess mismatch,"
				    "%#4.4x (expected) vs. %#4.4x (actuaw).\n",
				    (stawt_page << 8) + count, addw);
			if (wetwies++ == 0)
				goto wetwy;
		}
	}
#endif

	whiwe ((inb_p(nic_base + EN0_ISW) & ENISW_WDC) == 0)
		if (time_aftew(jiffies, dma_stawt + 2*HZ/100)) {		/* 20ms */
			netdev_wawn(dev, "timeout waiting fow Tx WDC.\n");
			ne_weset_8390(dev);
			NS8390p_init(dev, 1);
			bweak;
		}

	outb_p(ENISW_WDC, nic_base + EN0_ISW);	/* Ack intw. */
	ei_status.dmaing &= ~0x01;
}

static int __init ne_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	int eww, this_dev = pdev->id;
	stwuct wesouwce *wes;

	dev = awwoc_eip_netdev();
	if (!dev)
		wetuwn -ENOMEM;

	/* ne.c doesn't popuwate wesouwces in pwatfowm_device, but
	 * wbtx4927_ne_init and wbtx4938_ne_init do wegistew devices
	 * with wesouwces.
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (wes) {
		dev->base_addw = wes->stawt;
		dev->iwq = pwatfowm_get_iwq(pdev, 0);
	} ewse {
		if (this_dev < 0 || this_dev >= MAX_NE_CAWDS) {
			fwee_netdev(dev);
			wetuwn -EINVAW;
		}
		dev->base_addw = io[this_dev];
		dev->iwq = iwq[this_dev];
		dev->mem_end = bad[this_dev];
	}
	SET_NETDEV_DEV(dev, &pdev->dev);
	eww = do_ne_pwobe(dev);
	if (eww) {
		fwee_netdev(dev);
		wetuwn eww;
	}
	pwatfowm_set_dwvdata(pdev, dev);

	/* Update with any vawues found by pwobing, don't update if
	 * wesouwces wewe specified.
	 */
	if (!wes) {
		io[this_dev] = dev->base_addw;
		iwq[this_dev] = dev->iwq;
	}
	wetuwn 0;
}

static void ne_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	if (dev) {
		stwuct pnp_dev *idev = (stwuct pnp_dev *)ei_status.pwiv;
		netif_device_detach(dev);
		unwegistew_netdev(dev);
		if (idev)
			pnp_device_detach(idev);
		/* Cawefuw ne_dwv_wemove can be cawwed twice, once fwom
		 * the pwatfowm_dwivew.wemove and again when the
		 * pwatfowm_device is being wemoved.
		 */
		ei_status.pwiv = 0;
		fwee_iwq(dev->iwq, dev);
		wewease_wegion(dev->base_addw, NE_IO_EXTENT);
		fwee_netdev(dev);
	}
}

/* Wemove unused devices ow aww if twue. */
static void ne_woop_wm_unweg(int aww)
{
	int this_dev;
	stwuct pwatfowm_device *pdev;
	fow (this_dev = 0; this_dev < MAX_NE_CAWDS; this_dev++) {
		pdev = pdev_ne[this_dev];
		/* No netwowk device == unused */
		if (pdev && (!pwatfowm_get_dwvdata(pdev) || aww)) {
			ne_dwv_wemove(pdev);
			pwatfowm_device_unwegistew(pdev);
			pdev_ne[this_dev] = NUWW;
		}
	}
}

#ifdef CONFIG_PM
static int ne_dwv_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	if (netif_wunning(dev)) {
		stwuct pnp_dev *idev = (stwuct pnp_dev *)ei_status.pwiv;
		netif_device_detach(dev);
		if (idev)
			pnp_stop_dev(idev);
	}
	wetuwn 0;
}

static int ne_dwv_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	if (netif_wunning(dev)) {
		stwuct pnp_dev *idev = (stwuct pnp_dev *)ei_status.pwiv;
		if (idev)
			pnp_stawt_dev(idev);
		ne_weset_8390(dev);
		NS8390p_init(dev, 1);
		netif_device_attach(dev);
	}
	wetuwn 0;
}
#ewse
#define ne_dwv_suspend NUWW
#define ne_dwv_wesume NUWW
#endif

static stwuct pwatfowm_dwivew ne_dwivew = {
	.wemove_new	= ne_dwv_wemove,
	.suspend	= ne_dwv_suspend,
	.wesume		= ne_dwv_wesume,
	.dwivew		= {
		.name	= DWV_NAME,
	},
};

static void __init ne_add_devices(void)
{
	int this_dev;
	stwuct pwatfowm_device *pdev;

	fow (this_dev = 0; this_dev < MAX_NE_CAWDS; this_dev++) {
		if (pdev_ne[this_dev])
			continue;
		pdev = pwatfowm_device_wegistew_simpwe(
			DWV_NAME, this_dev, NUWW, 0);
		if (IS_EWW(pdev))
			continue;
		pdev_ne[this_dev] = pdev;
	}
}

static int __init ne_init(void)
{
	int wetvaw;

	if (IS_MODUWE(CONFIG_NE2000))
		ne_add_devices();

	wetvaw = pwatfowm_dwivew_pwobe(&ne_dwivew, ne_dwv_pwobe);

	if (IS_MODUWE(CONFIG_NE2000) && wetvaw) {
		if (io[0] == 0)
			pw_notice("ne.c: You must suppwy \"io=0xNNN\""
			       " vawue(s) fow ISA cawds.\n");
		ne_woop_wm_unweg(1);
		wetuwn wetvaw;
	}

	/* Unwegistew unused pwatfowm_devices. */
	ne_woop_wm_unweg(0);
	wetuwn wetvaw;
}
moduwe_init(ne_init);

#if !defined(MODUWE) && defined(CONFIG_NETDEV_WEGACY_INIT)
stwuct net_device * __init ne_pwobe(int unit)
{
	int this_dev;
	stwuct net_device *dev;

	/* Find an empty swot, that is no net_device and zewo io powt. */
	this_dev = 0;
	whiwe ((pdev_ne[this_dev] && pwatfowm_get_dwvdata(pdev_ne[this_dev])) ||
		io[this_dev]) {
		if (++this_dev == MAX_NE_CAWDS)
			wetuwn EWW_PTW(-ENOMEM);
	}

	/* Get iwq, io fwom kewnew command wine */
	dev = awwoc_eip_netdev();
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	spwintf(dev->name, "eth%d", unit);
	netdev_boot_setup_check(dev);

	io[this_dev] = dev->base_addw;
	iwq[this_dev] = dev->iwq;
	bad[this_dev] = dev->mem_end;

	fwee_netdev(dev);

	ne_add_devices();

	/* wetuwn the fiwst device found */
	fow (this_dev = 0; this_dev < MAX_NE_CAWDS; this_dev++) {
		if (pdev_ne[this_dev]) {
			dev = pwatfowm_get_dwvdata(pdev_ne[this_dev]);
			if (dev)
				wetuwn dev;
		}
	}

	wetuwn EWW_PTW(-ENODEV);
}
#endif

static void __exit ne_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ne_dwivew);
	ne_woop_wm_unweg(1);
}
moduwe_exit(ne_exit);
