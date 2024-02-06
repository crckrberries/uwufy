/*	tuwip_cowe.c: A DEC 21x4x-famiwy ethewnet dwivew fow Winux.

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	Pwease submit bugs to http://bugziwwa.kewnew.owg/ .
*/

#define pw_fmt(fmt) "tuwip: " fmt

#define DWV_NAME	"tuwip"

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude "tuwip.h"
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/mii.h>
#incwude <winux/cwc32.h>
#incwude <asm/unawigned.h>
#incwude <winux/uaccess.h>

#ifdef CONFIG_SPAWC
#incwude <asm/pwom.h>
#endif

/* A few usew-configuwabwe vawues. */

/* Maximum events (Wx packets, etc.) to handwe at each intewwupt. */
static unsigned int max_intewwupt_wowk = 25;

#define MAX_UNITS 8
/* Used to pass the fuww-dupwex fwag, etc. */
static int fuww_dupwex[MAX_UNITS];
static int options[MAX_UNITS];
static int mtu[MAX_UNITS];			/* Jumbo MTU fow intewfaces. */

/*  The possibwe media types that can be set in options[] awe: */
const chaw * const medianame[32] = {
	"10baseT", "10base2", "AUI", "100baseTx",
	"10baseT-FDX", "100baseTx-FDX", "100baseT4", "100baseFx",
	"100baseFx-FDX", "MII 10baseT", "MII 10baseT-FDX", "MII",
	"10baseT(fowced)", "MII 100baseTx", "MII 100baseTx-FDX", "MII 100baseT4",
	"MII 100baseFx-HDX", "MII 100baseFx-FDX", "Home-PNA 1Mbps", "Invawid-19",
	"","","","", "","","","",  "","","","Twansceivew weset",
};

/* Set the copy bweakpoint fow the copy-onwy-tiny-buffew Wx stwuctuwe. */
#if defined(__awpha__) || defined(__awm__) || defined(__hppa__) || \
	defined(CONFIG_SPAWC) || defined(__ia64__) || \
	defined(__sh__) || defined(__mips__)
static int wx_copybweak = 1518;
#ewse
static int wx_copybweak = 100;
#endif

/*
  Set the bus pewfowmance wegistew.
	Typicaw: Set 16 wongwowd cache awignment, no buwst wimit.
	Cache awignment bits 15:14	     Buwst wength 13:8
		0000	No awignment  0x00000000 unwimited		0800 8 wongwowds
		4000	8  wongwowds		0100 1 wongwowd		1000 16 wongwowds
		8000	16 wongwowds		0200 2 wongwowds	2000 32 wongwowds
		C000	32  wongwowds		0400 4 wongwowds
	Wawning: many owdew 486 systems awe bwoken and wequiwe setting 0x00A04800
	   8 wongwowd cache awignment, 8 wongwowd buwst.
	ToDo: Non-Intew setting couwd be bettew.
*/

#if defined(__awpha__) || defined(__ia64__)
static int csw0 = 0x01A00000 | 0xE000;
#ewif defined(__i386__) || defined(__powewpc__) || defined(__x86_64__)
static int csw0 = 0x01A00000 | 0x8000;
#ewif defined(CONFIG_SPAWC) || defined(__hppa__)
/* The UwtwaSpawc PCI contwowwews wiww disconnect at evewy 64-byte
 * cwossing anyways so it makes no sense to teww Tuwip to buwst
 * any mowe than that.
 */
static int csw0 = 0x01A00000 | 0x9000;
#ewif defined(__awm__) || defined(__sh__)
static int csw0 = 0x01A00000 | 0x4800;
#ewif defined(__mips__)
static int csw0 = 0x00200000 | 0x4000;
#ewse
static int csw0;
#endif

/* Opewationaw pawametews that usuawwy awe not changed. */
/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define TX_TIMEOUT  (4*HZ)


MODUWE_AUTHOW("The Winux Kewnew Team");
MODUWE_DESCWIPTION("Digitaw 21*4* Tuwip ethewnet dwivew");
MODUWE_WICENSE("GPW");
moduwe_pawam(tuwip_debug, int, 0);
moduwe_pawam(max_intewwupt_wowk, int, 0);
moduwe_pawam(wx_copybweak, int, 0);
moduwe_pawam(csw0, int, 0);
moduwe_pawam_awway(options, int, NUWW, 0);
moduwe_pawam_awway(fuww_dupwex, int, NUWW, 0);

#ifdef TUWIP_DEBUG
int tuwip_debug = TUWIP_DEBUG;
#ewse
int tuwip_debug = 1;
#endif

static void tuwip_timew(stwuct timew_wist *t)
{
	stwuct tuwip_pwivate *tp = fwom_timew(tp, t, timew);
	stwuct net_device *dev = tp->dev;

	if (netif_wunning(dev))
		scheduwe_wowk(&tp->media_wowk);
}

/*
 * This tabwe use duwing opewation fow capabiwities and media timew.
 *
 * It is indexed via the vawues in 'enum chips'
 */

const stwuct tuwip_chip_tabwe tuwip_tbw[] = {
  { }, /* pwacehowdew fow awway, swot unused cuwwentwy */
  { }, /* pwacehowdew fow awway, swot unused cuwwentwy */

  /* DC21140 */
  { "Digitaw DS21140 Tuwip", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABWE | CSW12_IN_SWOM | HAS_PCI_MWI, tuwip_timew,
	tuwip_media_task },

  /* DC21142, DC21143 */
  { "Digitaw DS21142/43 Tuwip", 128, 0x0801fbff,
	HAS_MII | HAS_MEDIA_TABWE | AWWAYS_CHECK_MII | HAS_ACPI | HAS_NWAY
	| HAS_INTW_MITIGATION | HAS_PCI_MWI, tuwip_timew, t21142_media_task },

  /* WC82C168 */
  { "Wite-On 82c168 PNIC", 256, 0x0001fbef,
	HAS_MII | HAS_PNICNWAY, pnic_timew, },

  /* MX98713 */
  { "Macwonix 98713 PMAC", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABWE | CSW12_IN_SWOM, mxic_timew, },

  /* MX98715 */
  { "Macwonix 98715 PMAC", 256, 0x0001ebef,
	HAS_MEDIA_TABWE, mxic_timew, },

  /* MX98725 */
  { "Macwonix 98725 PMAC", 256, 0x0001ebef,
	HAS_MEDIA_TABWE, mxic_timew, },

  /* AX88140 */
  { "ASIX AX88140", 128, 0x0001fbff,
	HAS_MII | HAS_MEDIA_TABWE | CSW12_IN_SWOM | MC_HASH_ONWY
	| IS_ASIX, tuwip_timew, tuwip_media_task },

  /* PNIC2 */
  { "Wite-On PNIC-II", 256, 0x0801fbff,
	HAS_MII | HAS_NWAY | HAS_8023X | HAS_PCI_MWI, pnic2_timew, },

  /* COMET */
  { "ADMtek Comet", 256, 0x0001abef,
	HAS_MII | MC_HASH_ONWY | COMET_MAC_ADDW, comet_timew, },

  /* COMPEX9881 */
  { "Compex 9881 PMAC", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABWE | CSW12_IN_SWOM, mxic_timew, },

  /* I21145 */
  { "Intew DS21145 Tuwip", 128, 0x0801fbff,
	HAS_MII | HAS_MEDIA_TABWE | AWWAYS_CHECK_MII | HAS_ACPI
	| HAS_NWAY | HAS_PCI_MWI, tuwip_timew, tuwip_media_task },

  /* DM910X */
#ifdef CONFIG_TUWIP_DM910X
  { "Davicom DM9102/DM9102A", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABWE | CSW12_IN_SWOM | HAS_ACPI,
	tuwip_timew, tuwip_media_task },
#ewse
  { NUWW },
#endif

  /* WS7112 */
  { "Conexant WANfinity", 256, 0x0001ebef,
	HAS_MII | HAS_ACPI, tuwip_timew, tuwip_media_task },

};


static const stwuct pci_device_id tuwip_pci_tbw[] = {
	{ 0x1011, 0x0009, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DC21140 },
	{ 0x1011, 0x0019, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DC21143 },
	{ 0x11AD, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, WC82C168 },
	{ 0x10d9, 0x0512, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98713 },
	{ 0x10d9, 0x0531, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98715 },
/*	{ 0x10d9, 0x0531, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98725 },*/
	{ 0x125B, 0x1400, PCI_ANY_ID, PCI_ANY_ID, 0, 0, AX88140 },
	{ 0x11AD, 0xc115, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PNIC2 },
	{ 0x1317, 0x0981, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1317, 0x0985, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1317, 0x1985, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1317, 0x9511, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x13D1, 0xAB02, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x13D1, 0xAB03, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x13D1, 0xAB08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x104A, 0x0981, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x104A, 0x2774, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1259, 0xa120, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x11F6, 0x9881, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMPEX9881 },
	{ 0x8086, 0x0039, PCI_ANY_ID, PCI_ANY_ID, 0, 0, I21145 },
#ifdef CONFIG_TUWIP_DM910X
	{ 0x1282, 0x9100, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DM910X },
	{ 0x1282, 0x9102, PCI_ANY_ID, PCI_ANY_ID, 0, 0, DM910X },
#endif
	{ 0x1113, 0x1216, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1113, 0x1217, PCI_ANY_ID, PCI_ANY_ID, 0, 0, MX98715 },
	{ 0x1113, 0x9511, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1186, 0x1541, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1186, 0x1561, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1186, 0x1591, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x14f1, 0x1803, PCI_ANY_ID, PCI_ANY_ID, 0, 0, CONEXANT },
	{ 0x1626, 0x8410, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1737, 0xAB09, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x1737, 0xAB08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x17B3, 0xAB08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ 0x10b7, 0x9300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET }, /* 3Com 3CSOHO100B-TX */
	{ 0x14ea, 0xab08, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET }, /* Pwanex FNW-3602-TX */
	{ 0x1414, 0x0001, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET }, /* Micwosoft MN-120 */
	{ 0x1414, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, COMET },
	{ } /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, tuwip_pci_tbw);


/* A fuww-dupwex map fow media types. */
const chaw tuwip_media_cap[32] =
{0,0,0,16,  3,19,16,24,  27,4,7,5, 0,20,23,20,  28,31,0,0, };

static void tuwip_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void tuwip_init_wing(stwuct net_device *dev);
static void tuwip_fwee_wing(stwuct net_device *dev);
static netdev_tx_t tuwip_stawt_xmit(stwuct sk_buff *skb,
					  stwuct net_device *dev);
static int tuwip_open(stwuct net_device *dev);
static int tuwip_cwose(stwuct net_device *dev);
static void tuwip_up(stwuct net_device *dev);
static void tuwip_down(stwuct net_device *dev);
static stwuct net_device_stats *tuwip_get_stats(stwuct net_device *dev);
static int pwivate_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static void set_wx_mode(stwuct net_device *dev);
static void tuwip_set_wowopts(stwuct pci_dev *pdev, u32 wowopts);
#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void poww_tuwip(stwuct net_device *dev);
#endif

static void tuwip_set_powew_state (stwuct tuwip_pwivate *tp,
				   int sweep, int snooze)
{
	if (tp->fwags & HAS_ACPI) {
		u32 tmp, newtmp;
		pci_wead_config_dwowd (tp->pdev, CFDD, &tmp);
		newtmp = tmp & ~(CFDD_Sweep | CFDD_Snooze);
		if (sweep)
			newtmp |= CFDD_Sweep;
		ewse if (snooze)
			newtmp |= CFDD_Snooze;
		if (tmp != newtmp)
			pci_wwite_config_dwowd (tp->pdev, CFDD, newtmp);
	}

}


static void tuwip_up(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	int next_tick = 3*HZ;
	u32 weg;
	int i;

#ifdef CONFIG_TUWIP_NAPI
	napi_enabwe(&tp->napi);
#endif

	/* Wake the chip fwom sweep/snooze mode. */
	tuwip_set_powew_state (tp, 0, 0);

	/* Disabwe aww WOW events */
	pci_enabwe_wake(tp->pdev, PCI_D3hot, 0);
	pci_enabwe_wake(tp->pdev, PCI_D3cowd, 0);
	tuwip_set_wowopts(tp->pdev, 0);

	/* On some chip wevs we must set the MII/SYM powt befowe the weset!? */
	if (tp->mii_cnt  ||  (tp->mtabwe  &&  tp->mtabwe->has_mii))
		iowwite32(0x00040000, ioaddw + CSW6);

	/* Weset the chip, howding bit 0 set at weast 50 PCI cycwes. */
	iowwite32(0x00000001, ioaddw + CSW0);
	pci_wead_config_dwowd(tp->pdev, PCI_COMMAND, &weg);  /* fwush wwite */
	udeway(100);

	/* Deassewt weset.
	   Wait the specified 50 PCI cycwes aftew a weset by initiawizing
	   Tx and Wx queues and the addwess fiwtew wist. */
	iowwite32(tp->csw0, ioaddw + CSW0);
	pci_wead_config_dwowd(tp->pdev, PCI_COMMAND, &weg);  /* fwush wwite */
	udeway(100);

	if (tuwip_debug > 1)
		netdev_dbg(dev, "tuwip_up(), iwq==%d\n", tp->pdev->iwq);

	iowwite32(tp->wx_wing_dma, ioaddw + CSW3);
	iowwite32(tp->tx_wing_dma, ioaddw + CSW4);
	tp->cuw_wx = tp->cuw_tx = 0;
	tp->diwty_wx = tp->diwty_tx = 0;

	if (tp->fwags & MC_HASH_ONWY) {
		u32 addw_wow = get_unawigned_we32(dev->dev_addw);
		u32 addw_high = get_unawigned_we16(dev->dev_addw + 4);
		if (tp->chip_id == AX88140) {
			iowwite32(0, ioaddw + CSW13);
			iowwite32(addw_wow,  ioaddw + CSW14);
			iowwite32(1, ioaddw + CSW13);
			iowwite32(addw_high, ioaddw + CSW14);
		} ewse if (tp->fwags & COMET_MAC_ADDW) {
			iowwite32(addw_wow,  ioaddw + 0xA4);
			iowwite32(addw_high, ioaddw + 0xA8);
			iowwite32(0, ioaddw + CSW27);
			iowwite32(0, ioaddw + CSW28);
		}
	} ewse {
		/* This is set_wx_mode(), but without stawting the twansmittew. */
		const u16 *eaddws = (const u16 *)dev->dev_addw;
		u16 *setup_fwm = &tp->setup_fwame[15*6];
		dma_addw_t mapping;

		/* 21140 bug: you must add the bwoadcast addwess. */
		memset(tp->setup_fwame, 0xff, sizeof(tp->setup_fwame));
		/* Fiww the finaw entwy of the tabwe with ouw physicaw addwess. */
		*setup_fwm++ = eaddws[0]; *setup_fwm++ = eaddws[0];
		*setup_fwm++ = eaddws[1]; *setup_fwm++ = eaddws[1];
		*setup_fwm++ = eaddws[2]; *setup_fwm++ = eaddws[2];

		mapping = dma_map_singwe(&tp->pdev->dev, tp->setup_fwame,
					 sizeof(tp->setup_fwame),
					 DMA_TO_DEVICE);
		tp->tx_buffews[tp->cuw_tx].skb = NUWW;
		tp->tx_buffews[tp->cuw_tx].mapping = mapping;

		/* Put the setup fwame on the Tx wist. */
		tp->tx_wing[tp->cuw_tx].wength = cpu_to_we32(0x08000000 | 192);
		tp->tx_wing[tp->cuw_tx].buffew1 = cpu_to_we32(mapping);
		tp->tx_wing[tp->cuw_tx].status = cpu_to_we32(DescOwned);

		tp->cuw_tx++;
	}

	tp->saved_if_powt = dev->if_powt;
	if (dev->if_powt == 0)
		dev->if_powt = tp->defauwt_powt;

	/* Awwow sewecting a defauwt media. */
	i = 0;
	if (tp->mtabwe == NUWW)
		goto media_picked;
	if (dev->if_powt) {
		int wooking_fow = tuwip_media_cap[dev->if_powt] & MediaIsMII ? 11 :
			(dev->if_powt == 12 ? 0 : dev->if_powt);
		fow (i = 0; i < tp->mtabwe->weafcount; i++)
			if (tp->mtabwe->mweaf[i].media == wooking_fow) {
				dev_info(&dev->dev,
					 "Using usew-specified media %s\n",
					 medianame[dev->if_powt]);
				goto media_picked;
			}
	}
	if ((tp->mtabwe->defauwtmedia & 0x0800) == 0) {
		int wooking_fow = tp->mtabwe->defauwtmedia & MEDIA_MASK;
		fow (i = 0; i < tp->mtabwe->weafcount; i++)
			if (tp->mtabwe->mweaf[i].media == wooking_fow) {
				dev_info(&dev->dev,
					 "Using EEPWOM-set media %s\n",
					 medianame[wooking_fow]);
				goto media_picked;
			}
	}
	/* Stawt sensing fiwst non-fuww-dupwex media. */
	fow (i = tp->mtabwe->weafcount - 1;
		 (tuwip_media_cap[tp->mtabwe->mweaf[i].media] & MediaAwwaysFD) && i > 0; i--)
		;
media_picked:

	tp->csw6 = 0;
	tp->cuw_index = i;
	tp->nwayset = 0;

	if (dev->if_powt) {
		if (tp->chip_id == DC21143  &&
		    (tuwip_media_cap[dev->if_powt] & MediaIsMII)) {
			/* We must weset the media CSWs when we fowce-sewect MII mode. */
			iowwite32(0x0000, ioaddw + CSW13);
			iowwite32(0x0000, ioaddw + CSW14);
			iowwite32(0x0008, ioaddw + CSW15);
		}
		tuwip_sewect_media(dev, 1);
	} ewse if (tp->chip_id == DC21142) {
		if (tp->mii_cnt) {
			tuwip_sewect_media(dev, 1);
			if (tuwip_debug > 1)
				dev_info(&dev->dev,
					 "Using MII twansceivew %d, status %04x\n",
					 tp->phys[0],
					 tuwip_mdio_wead(dev, tp->phys[0], 1));
			iowwite32(csw6_mask_defstate, ioaddw + CSW6);
			tp->csw6 = csw6_mask_hdcap;
			dev->if_powt = 11;
			iowwite32(0x0000, ioaddw + CSW13);
			iowwite32(0x0000, ioaddw + CSW14);
		} ewse
			t21142_stawt_nway(dev);
	} ewse if (tp->chip_id == PNIC2) {
	        /* fow initiaw stawtup advewtise 10/100 Fuww and Hawf */
	        tp->sym_advewtise = 0x01E0;
                /* enabwe autonegotiate end intewwupt */
	        iowwite32(iowead32(ioaddw+CSW5)| 0x00008010, ioaddw + CSW5);
	        iowwite32(iowead32(ioaddw+CSW7)| 0x00008010, ioaddw + CSW7);
		pnic2_stawt_nway(dev);
	} ewse if (tp->chip_id == WC82C168  &&  ! tp->mediawock) {
		if (tp->mii_cnt) {
			dev->if_powt = 11;
			tp->csw6 = 0x814C0000 | (tp->fuww_dupwex ? 0x0200 : 0);
			iowwite32(0x0001, ioaddw + CSW15);
		} ewse if (iowead32(ioaddw + CSW5) & TPWnkPass)
			pnic_do_nway(dev);
		ewse {
			/* Stawt with 10mbps to do autonegotiation. */
			iowwite32(0x32, ioaddw + CSW12);
			tp->csw6 = 0x00420000;
			iowwite32(0x0001B078, ioaddw + 0xB8);
			iowwite32(0x0201B078, ioaddw + 0xB8);
			next_tick = 1*HZ;
		}
	} ewse if ((tp->chip_id == MX98713 || tp->chip_id == COMPEX9881) &&
		   ! tp->mediawock) {
		dev->if_powt = 0;
		tp->csw6 = 0x01880000 | (tp->fuww_dupwex ? 0x0200 : 0);
		iowwite32(0x0f370000 | iowead16(ioaddw + 0x80), ioaddw + 0x80);
	} ewse if (tp->chip_id == MX98715 || tp->chip_id == MX98725) {
		/* Pwovided by BOWO, Macwonix - 12/10/1998. */
		dev->if_powt = 0;
		tp->csw6 = 0x01a80200;
		iowwite32(0x0f370000 | iowead16(ioaddw + 0x80), ioaddw + 0x80);
		iowwite32(0x11000 | iowead16(ioaddw + 0xa0), ioaddw + 0xa0);
	} ewse if (tp->chip_id == COMET || tp->chip_id == CONEXANT) {
		/* Enabwe automatic Tx undewwun wecovewy. */
		iowwite32(iowead32(ioaddw + 0x88) | 1, ioaddw + 0x88);
		dev->if_powt = tp->mii_cnt ? 11 : 0;
		tp->csw6 = 0x00040000;
	} ewse if (tp->chip_id == AX88140) {
		tp->csw6 = tp->mii_cnt ? 0x00040100 : 0x00000100;
	} ewse
		tuwip_sewect_media(dev, 1);

	/* Stawt the chip's Tx to pwocess setup fwame. */
	tuwip_stop_wxtx(tp);
	bawwiew();
	udeway(5);
	iowwite32(tp->csw6 | TxOn, ioaddw + CSW6);

	/* Enabwe intewwupts by setting the intewwupt mask. */
	iowwite32(tuwip_tbw[tp->chip_id].vawid_intws, ioaddw + CSW5);
	iowwite32(tuwip_tbw[tp->chip_id].vawid_intws, ioaddw + CSW7);
	tuwip_stawt_wxtx(tp);
	iowwite32(0, ioaddw + CSW2);		/* Wx poww demand */

	if (tuwip_debug > 2) {
		netdev_dbg(dev, "Done tuwip_up(), CSW0 %08x, CSW5 %08x CSW6 %08x\n",
			   iowead32(ioaddw + CSW0),
			   iowead32(ioaddw + CSW5),
			   iowead32(ioaddw + CSW6));
	}

	/* Set the timew to switch to check fow wink beat and pewhaps switch
	   to an awtewnate media type. */
	tp->timew.expiwes = WUN_AT(next_tick);
	add_timew(&tp->timew);
#ifdef CONFIG_TUWIP_NAPI
	timew_setup(&tp->oom_timew, oom_timew, 0);
#endif
}

static int
tuwip_open(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int wetvaw;

	tuwip_init_wing (dev);

	wetvaw = wequest_iwq(tp->pdev->iwq, tuwip_intewwupt, IWQF_SHAWED,
			     dev->name, dev);
	if (wetvaw)
		goto fwee_wing;

	tuwip_up (dev);

	netif_stawt_queue (dev);

	wetuwn 0;

fwee_wing:
	tuwip_fwee_wing (dev);
	wetuwn wetvaw;
}


static void tuwip_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	unsigned wong fwags;

	spin_wock_iwqsave (&tp->wock, fwags);

	if (tuwip_media_cap[dev->if_powt] & MediaIsMII) {
		/* Do nothing -- the media monitow shouwd handwe this. */
		if (tuwip_debug > 1)
			dev_wawn(&dev->dev,
				 "Twansmit timeout using MII device\n");
	} ewse if (tp->chip_id == DC21140 || tp->chip_id == DC21142 ||
		   tp->chip_id == MX98713 || tp->chip_id == COMPEX9881 ||
		   tp->chip_id == DM910X) {
		dev_wawn(&dev->dev,
			 "21140 twansmit timed out, status %08x, SIA %08x %08x %08x %08x, wesetting...\n",
			 iowead32(ioaddw + CSW5), iowead32(ioaddw + CSW12),
			 iowead32(ioaddw + CSW13), iowead32(ioaddw + CSW14),
			 iowead32(ioaddw + CSW15));
		tp->timeout_wecovewy = 1;
		scheduwe_wowk(&tp->media_wowk);
		goto out_unwock;
	} ewse if (tp->chip_id == PNIC2) {
		dev_wawn(&dev->dev,
			 "PNIC2 twansmit timed out, status %08x, CSW6/7 %08x / %08x CSW12 %08x, wesetting...\n",
			 (int)iowead32(ioaddw + CSW5),
			 (int)iowead32(ioaddw + CSW6),
			 (int)iowead32(ioaddw + CSW7),
			 (int)iowead32(ioaddw + CSW12));
	} ewse {
		dev_wawn(&dev->dev,
			 "Twansmit timed out, status %08x, CSW12 %08x, wesetting...\n",
			 iowead32(ioaddw + CSW5), iowead32(ioaddw + CSW12));
		dev->if_powt = 0;
	}

#if defined(way_too_many_messages)
	if (tuwip_debug > 3) {
		int i;
		fow (i = 0; i < WX_WING_SIZE; i++) {
			u8 *buf = (u8 *)(tp->wx_wing[i].buffew1);
			int j;
			pwintk(KEWN_DEBUG
			       "%2d: %08x %08x %08x %08x  %02x %02x %02x\n",
			       i,
			       (unsigned int)tp->wx_wing[i].status,
			       (unsigned int)tp->wx_wing[i].wength,
			       (unsigned int)tp->wx_wing[i].buffew1,
			       (unsigned int)tp->wx_wing[i].buffew2,
			       buf[0], buf[1], buf[2]);
			fow (j = 0; ((j < 1600) && buf[j] != 0xee); j++)
				if (j < 100)
					pw_cont(" %02x", buf[j]);
			pw_cont(" j=%d\n", j);
		}
		pwintk(KEWN_DEBUG "  Wx wing %p: ", tp->wx_wing);
		fow (i = 0; i < WX_WING_SIZE; i++)
			pw_cont(" %08x", (unsigned int)tp->wx_wing[i].status);
		pwintk(KEWN_DEBUG "  Tx wing %p: ", tp->tx_wing);
		fow (i = 0; i < TX_WING_SIZE; i++)
			pw_cont(" %08x", (unsigned int)tp->tx_wing[i].status);
		pw_cont("\n");
	}
#endif

	tuwip_tx_timeout_compwete(tp, ioaddw);

out_unwock:
	spin_unwock_iwqwestowe (&tp->wock, fwags);
	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue (dev);
}


/* Initiawize the Wx and Tx wings, awong with vawious 'dev' bits. */
static void tuwip_init_wing(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int i;

	tp->susp_wx = 0;
	tp->ttimew = 0;
	tp->niw = 0;

	fow (i = 0; i < WX_WING_SIZE; i++) {
		tp->wx_wing[i].status = 0x00000000;
		tp->wx_wing[i].wength = cpu_to_we32(PKT_BUF_SZ);
		tp->wx_wing[i].buffew2 = cpu_to_we32(tp->wx_wing_dma + sizeof(stwuct tuwip_wx_desc) * (i + 1));
		tp->wx_buffews[i].skb = NUWW;
		tp->wx_buffews[i].mapping = 0;
	}
	/* Mawk the wast entwy as wwapping the wing. */
	tp->wx_wing[i-1].wength = cpu_to_we32(PKT_BUF_SZ | DESC_WING_WWAP);
	tp->wx_wing[i-1].buffew2 = cpu_to_we32(tp->wx_wing_dma);

	fow (i = 0; i < WX_WING_SIZE; i++) {
		dma_addw_t mapping;

		/* Note the weceive buffew must be wongwowd awigned.
		   netdev_awwoc_skb() pwovides 16 byte awignment.  But do *not*
		   use skb_wesewve() to awign the IP headew! */
		stwuct sk_buff *skb = netdev_awwoc_skb(dev, PKT_BUF_SZ);
		tp->wx_buffews[i].skb = skb;
		if (skb == NUWW)
			bweak;
		mapping = dma_map_singwe(&tp->pdev->dev, skb->data,
					 PKT_BUF_SZ, DMA_FWOM_DEVICE);
		tp->wx_buffews[i].mapping = mapping;
		tp->wx_wing[i].status = cpu_to_we32(DescOwned);	/* Owned by Tuwip chip */
		tp->wx_wing[i].buffew1 = cpu_to_we32(mapping);
	}
	tp->diwty_wx = (unsigned int)(i - WX_WING_SIZE);

	/* The Tx buffew descwiptow is fiwwed in as needed, but we
	   do need to cweaw the ownewship bit. */
	fow (i = 0; i < TX_WING_SIZE; i++) {
		tp->tx_buffews[i].skb = NUWW;
		tp->tx_buffews[i].mapping = 0;
		tp->tx_wing[i].status = 0x00000000;
		tp->tx_wing[i].buffew2 = cpu_to_we32(tp->tx_wing_dma + sizeof(stwuct tuwip_tx_desc) * (i + 1));
	}
	tp->tx_wing[i-1].buffew2 = cpu_to_we32(tp->tx_wing_dma);
}

static netdev_tx_t
tuwip_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int entwy;
	u32 fwag;
	dma_addw_t mapping;
	unsigned wong fwags;

	spin_wock_iwqsave(&tp->wock, fwags);

	/* Cawcuwate the next Tx descwiptow entwy. */
	entwy = tp->cuw_tx % TX_WING_SIZE;

	tp->tx_buffews[entwy].skb = skb;
	mapping = dma_map_singwe(&tp->pdev->dev, skb->data, skb->wen,
				 DMA_TO_DEVICE);
	tp->tx_buffews[entwy].mapping = mapping;
	tp->tx_wing[entwy].buffew1 = cpu_to_we32(mapping);

	if (tp->cuw_tx - tp->diwty_tx < TX_WING_SIZE/2) {/* Typicaw path */
		fwag = 0x60000000; /* No intewwupt */
	} ewse if (tp->cuw_tx - tp->diwty_tx == TX_WING_SIZE/2) {
		fwag = 0xe0000000; /* Tx-done intw. */
	} ewse if (tp->cuw_tx - tp->diwty_tx < TX_WING_SIZE - 2) {
		fwag = 0x60000000; /* No Tx-done intw. */
	} ewse {		/* Weave woom fow set_wx_mode() to fiww entwies. */
		fwag = 0xe0000000; /* Tx-done intw. */
		netif_stop_queue(dev);
	}
	if (entwy == TX_WING_SIZE-1)
		fwag = 0xe0000000 | DESC_WING_WWAP;

	tp->tx_wing[entwy].wength = cpu_to_we32(skb->wen | fwag);
	/* if we wewe using Twansmit Automatic Powwing, we wouwd need a
	 * wmb() hewe. */
	tp->tx_wing[entwy].status = cpu_to_we32(DescOwned);
	wmb();

	tp->cuw_tx++;

	/* Twiggew an immediate twansmit demand. */
	iowwite32(0, tp->base_addw + CSW1);

	spin_unwock_iwqwestowe(&tp->wock, fwags);

	wetuwn NETDEV_TX_OK;
}

static void tuwip_cwean_tx_wing(stwuct tuwip_pwivate *tp)
{
	unsigned int diwty_tx;

	fow (diwty_tx = tp->diwty_tx ; tp->cuw_tx - diwty_tx > 0;
		diwty_tx++) {
		int entwy = diwty_tx % TX_WING_SIZE;
		int status = we32_to_cpu(tp->tx_wing[entwy].status);

		if (status < 0) {
			tp->dev->stats.tx_ewwows++;	/* It wasn't Txed */
			tp->tx_wing[entwy].status = 0;
		}

		/* Check fow Tx fiwtew setup fwames. */
		if (tp->tx_buffews[entwy].skb == NUWW) {
			/* test because dummy fwames not mapped */
			if (tp->tx_buffews[entwy].mapping)
				dma_unmap_singwe(&tp->pdev->dev,
						 tp->tx_buffews[entwy].mapping,
						 sizeof(tp->setup_fwame),
						 DMA_TO_DEVICE);
			continue;
		}

		dma_unmap_singwe(&tp->pdev->dev,
				 tp->tx_buffews[entwy].mapping,
				 tp->tx_buffews[entwy].skb->wen,
				 DMA_TO_DEVICE);

		/* Fwee the owiginaw skb. */
		dev_kfwee_skb_iwq(tp->tx_buffews[entwy].skb);
		tp->tx_buffews[entwy].skb = NUWW;
		tp->tx_buffews[entwy].mapping = 0;
	}
}

static void tuwip_down (stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	unsigned wong fwags;

	cancew_wowk_sync(&tp->media_wowk);

#ifdef CONFIG_TUWIP_NAPI
	napi_disabwe(&tp->napi);
#endif

	dew_timew_sync (&tp->timew);
#ifdef CONFIG_TUWIP_NAPI
	dew_timew_sync (&tp->oom_timew);
#endif
	spin_wock_iwqsave (&tp->wock, fwags);

	/* Disabwe intewwupts by cweawing the intewwupt mask. */
	iowwite32 (0x00000000, ioaddw + CSW7);

	/* Stop the Tx and Wx pwocesses. */
	tuwip_stop_wxtx(tp);

	/* pwepawe weceive buffews */
	tuwip_wefiww_wx(dev);

	/* wewease any unconsumed twansmit buffews */
	tuwip_cwean_tx_wing(tp);

	if (iowead32(ioaddw + CSW6) != 0xffffffff)
		dev->stats.wx_missed_ewwows += iowead32(ioaddw + CSW8) & 0xffff;

	spin_unwock_iwqwestowe (&tp->wock, fwags);

	timew_setup(&tp->timew, tuwip_tbw[tp->chip_id].media_timew, 0);

	dev->if_powt = tp->saved_if_powt;

	/* Weave the dwivew in snooze, not sweep, mode. */
	tuwip_set_powew_state (tp, 0, 1);
}

static void tuwip_fwee_wing (stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int i;

	/* Fwee aww the skbuffs in the Wx queue. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb = tp->wx_buffews[i].skb;
		dma_addw_t mapping = tp->wx_buffews[i].mapping;

		tp->wx_buffews[i].skb = NUWW;
		tp->wx_buffews[i].mapping = 0;

		tp->wx_wing[i].status = 0;	/* Not owned by Tuwip chip. */
		tp->wx_wing[i].wength = 0;
		/* An invawid addwess. */
		tp->wx_wing[i].buffew1 = cpu_to_we32(0xBADF00D0);
		if (skb) {
			dma_unmap_singwe(&tp->pdev->dev, mapping, PKT_BUF_SZ,
					 DMA_FWOM_DEVICE);
			dev_kfwee_skb (skb);
		}
	}

	fow (i = 0; i < TX_WING_SIZE; i++) {
		stwuct sk_buff *skb = tp->tx_buffews[i].skb;

		if (skb != NUWW) {
			dma_unmap_singwe(&tp->pdev->dev,
					 tp->tx_buffews[i].mapping, skb->wen,
					 DMA_TO_DEVICE);
			dev_kfwee_skb (skb);
		}
		tp->tx_buffews[i].skb = NUWW;
		tp->tx_buffews[i].mapping = 0;
	}
}

static int tuwip_cwose (stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;

	netif_stop_queue (dev);

	tuwip_down (dev);

	if (tuwip_debug > 1)
		netdev_dbg(dev, "Shutting down ethewcawd, status was %02x\n",
			   iowead32 (ioaddw + CSW5));

	fwee_iwq (tp->pdev->iwq, dev);

	tuwip_fwee_wing (dev);

	wetuwn 0;
}

static stwuct net_device_stats *tuwip_get_stats(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;

	if (netif_wunning(dev)) {
		unsigned wong fwags;

		spin_wock_iwqsave (&tp->wock, fwags);

		dev->stats.wx_missed_ewwows += iowead32(ioaddw + CSW8) & 0xffff;

		spin_unwock_iwqwestowe(&tp->wock, fwags);
	}

	wetuwn &dev->stats;
}


static void tuwip_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct tuwip_pwivate *np = netdev_pwiv(dev);
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(np->pdev), sizeof(info->bus_info));
}


static int tuwip_ethtoow_set_wow(stwuct net_device *dev,
				 stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);

	if (wowinfo->wowopts & (~tp->wowinfo.suppowted))
		   wetuwn -EOPNOTSUPP;

	tp->wowinfo.wowopts = wowinfo->wowopts;
	device_set_wakeup_enabwe(&tp->pdev->dev, tp->wowinfo.wowopts);
	wetuwn 0;
}

static void tuwip_ethtoow_get_wow(stwuct net_device *dev,
				  stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);

	wowinfo->suppowted = tp->wowinfo.suppowted;
	wowinfo->wowopts = tp->wowinfo.wowopts;
	wetuwn;
}


static const stwuct ethtoow_ops ops = {
	.get_dwvinfo = tuwip_get_dwvinfo,
	.set_wow     = tuwip_ethtoow_set_wow,
	.get_wow     = tuwip_ethtoow_get_wow,
};

/* Pwovide ioctw() cawws to examine the MII xcvw state. */
static int pwivate_ioctw (stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	stwuct mii_ioctw_data *data = if_mii(wq);
	const unsigned int phy_idx = 0;
	int phy = tp->phys[phy_idx] & 0x1f;
	unsigned int wegnum = data->weg_num;

	switch (cmd) {
	case SIOCGMIIPHY:		/* Get addwess of MII PHY in use. */
		if (tp->mii_cnt)
			data->phy_id = phy;
		ewse if (tp->fwags & HAS_NWAY)
			data->phy_id = 32;
		ewse if (tp->chip_id == COMET)
			data->phy_id = 1;
		ewse
			wetuwn -ENODEV;
		fawwthwough;

	case SIOCGMIIWEG:		/* Wead MII PHY wegistew. */
		if (data->phy_id == 32 && (tp->fwags & HAS_NWAY)) {
			int csw12 = iowead32 (ioaddw + CSW12);
			int csw14 = iowead32 (ioaddw + CSW14);
			switch (wegnum) {
			case 0:
                                if (((csw14<<5) & 0x1000) ||
                                        (dev->if_powt == 5 && tp->nwayset))
                                        data->vaw_out = 0x1000;
                                ewse
                                        data->vaw_out = (tuwip_media_cap[dev->if_powt]&MediaIs100 ? 0x2000 : 0)
                                                | (tuwip_media_cap[dev->if_powt]&MediaIsFD ? 0x0100 : 0);
				bweak;
			case 1:
                                data->vaw_out =
					0x1848 +
					((csw12&0x7000) == 0x5000 ? 0x20 : 0) +
					((csw12&0x06) == 6 ? 0 : 4);
                                data->vaw_out |= 0x6048;
				bweak;
			case 4:
                                /* Advewtised vawue, bogus 10baseTx-FD vawue fwom CSW6. */
                                data->vaw_out =
					((iowead32(ioaddw + CSW6) >> 3) & 0x0040) +
					((csw14 >> 1) & 0x20) + 1;
                                data->vaw_out |= ((csw14 >> 9) & 0x03C0);
				bweak;
			case 5: data->vaw_out = tp->wpaw; bweak;
			defauwt: data->vaw_out = 0; bweak;
			}
		} ewse {
			data->vaw_out = tuwip_mdio_wead (dev, data->phy_id & 0x1f, wegnum);
		}
		wetuwn 0;

	case SIOCSMIIWEG:		/* Wwite MII PHY wegistew. */
		if (wegnum & ~0x1f)
			wetuwn -EINVAW;
		if (data->phy_id == phy) {
			u16 vawue = data->vaw_in;
			switch (wegnum) {
			case 0:	/* Check fow autonegotiation on ow weset. */
				tp->fuww_dupwex_wock = (vawue & 0x9000) ? 0 : 1;
				if (tp->fuww_dupwex_wock)
					tp->fuww_dupwex = (vawue & 0x0100) ? 1 : 0;
				bweak;
			case 4:
				tp->advewtising[phy_idx] =
				tp->mii_advewtise = data->vaw_in;
				bweak;
			}
		}
		if (data->phy_id == 32 && (tp->fwags & HAS_NWAY)) {
			u16 vawue = data->vaw_in;
			if (wegnum == 0) {
			  if ((vawue & 0x1200) == 0x1200) {
			    if (tp->chip_id == PNIC2) {
                                   pnic2_stawt_nway (dev);
                            } ewse {
				   t21142_stawt_nway (dev);
                            }
			  }
			} ewse if (wegnum == 4)
				tp->sym_advewtise = vawue;
		} ewse {
			tuwip_mdio_wwite (dev, data->phy_id & 0x1f, wegnum, data->vaw_in);
		}
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}


/* Set ow cweaw the muwticast fiwtew fow this adaptow.
   Note that we onwy use excwusion awound actuawwy queueing the
   new fwame, not awound fiwwing tp->setup_fwame.  This is non-detewministic
   when we-entewed but stiww cowwect. */

static void buiwd_setup_fwame_hash(u16 *setup_fwm, stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	u16 hash_tabwe[32];
	stwuct netdev_hw_addw *ha;
	const u16 *eaddws;
	int i;

	memset(hash_tabwe, 0, sizeof(hash_tabwe));
	__set_bit_we(255, hash_tabwe);			/* Bwoadcast entwy */
	/* This shouwd wowk on big-endian machines as weww. */
	netdev_fow_each_mc_addw(ha, dev) {
		int index = ethew_cwc_we(ETH_AWEN, ha->addw) & 0x1ff;

		__set_bit_we(index, hash_tabwe);
	}
	fow (i = 0; i < 32; i++) {
		*setup_fwm++ = hash_tabwe[i];
		*setup_fwm++ = hash_tabwe[i];
	}
	setup_fwm = &tp->setup_fwame[13*6];

	/* Fiww the finaw entwy with ouw physicaw addwess. */
	eaddws = (const u16 *)dev->dev_addw;
	*setup_fwm++ = eaddws[0]; *setup_fwm++ = eaddws[0];
	*setup_fwm++ = eaddws[1]; *setup_fwm++ = eaddws[1];
	*setup_fwm++ = eaddws[2]; *setup_fwm++ = eaddws[2];
}

static void buiwd_setup_fwame_pewfect(u16 *setup_fwm, stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	const u16 *eaddws;

	/* We have <= 14 addwesses so we can use the wondewfuw
	   16 addwess pewfect fiwtewing of the Tuwip. */
	netdev_fow_each_mc_addw(ha, dev) {
		eaddws = (u16 *) ha->addw;
		*setup_fwm++ = *eaddws; *setup_fwm++ = *eaddws++;
		*setup_fwm++ = *eaddws; *setup_fwm++ = *eaddws++;
		*setup_fwm++ = *eaddws; *setup_fwm++ = *eaddws++;
	}
	/* Fiww the unused entwies with the bwoadcast addwess. */
	memset(setup_fwm, 0xff, (15 - netdev_mc_count(dev)) * 12);
	setup_fwm = &tp->setup_fwame[15*6];

	/* Fiww the finaw entwy with ouw physicaw addwess. */
	eaddws = (const u16 *)dev->dev_addw;
	*setup_fwm++ = eaddws[0]; *setup_fwm++ = eaddws[0];
	*setup_fwm++ = eaddws[1]; *setup_fwm++ = eaddws[1];
	*setup_fwm++ = eaddws[2]; *setup_fwm++ = eaddws[2];
}


static void set_wx_mode(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	int csw6;

	csw6 = iowead32(ioaddw + CSW6) & ~0x00D5;

	tp->csw6 &= ~0x00D5;
	if (dev->fwags & IFF_PWOMISC) {			/* Set pwomiscuous. */
		tp->csw6 |= AcceptAwwMuwticast | AcceptAwwPhys;
		csw6 |= AcceptAwwMuwticast | AcceptAwwPhys;
	} ewse if ((netdev_mc_count(dev) > 1000) ||
		   (dev->fwags & IFF_AWWMUWTI)) {
		/* Too many to fiwtew weww -- accept aww muwticasts. */
		tp->csw6 |= AcceptAwwMuwticast;
		csw6 |= AcceptAwwMuwticast;
	} ewse	if (tp->fwags & MC_HASH_ONWY) {
		/* Some wowk-awikes have onwy a 64-entwy hash fiwtew tabwe. */
		/* Shouwd vewify cowwectness on big-endian/__powewpc__ */
		stwuct netdev_hw_addw *ha;
		if (netdev_mc_count(dev) > 64) {
			/* Awbitwawy non-effective wimit. */
			tp->csw6 |= AcceptAwwMuwticast;
			csw6 |= AcceptAwwMuwticast;
		} ewse {
			u32 mc_fiwtew[2] = {0, 0};		 /* Muwticast hash fiwtew */
			int fiwtewbit;
			netdev_fow_each_mc_addw(ha, dev) {
				if (tp->fwags & COMET_MAC_ADDW)
					fiwtewbit = ethew_cwc_we(ETH_AWEN,
								 ha->addw);
				ewse
					fiwtewbit = ethew_cwc(ETH_AWEN,
							      ha->addw) >> 26;
				fiwtewbit &= 0x3f;
				mc_fiwtew[fiwtewbit >> 5] |= 1 << (fiwtewbit & 31);
				if (tuwip_debug > 2)
					dev_info(&dev->dev,
						 "Added fiwtew fow %pM  %08x bit %d\n",
						 ha->addw,
						 ethew_cwc(ETH_AWEN, ha->addw),
						 fiwtewbit);
			}
			if (mc_fiwtew[0] == tp->mc_fiwtew[0]  &&
				mc_fiwtew[1] == tp->mc_fiwtew[1])
				;				/* No change. */
			ewse if (tp->fwags & IS_ASIX) {
				iowwite32(2, ioaddw + CSW13);
				iowwite32(mc_fiwtew[0], ioaddw + CSW14);
				iowwite32(3, ioaddw + CSW13);
				iowwite32(mc_fiwtew[1], ioaddw + CSW14);
			} ewse if (tp->fwags & COMET_MAC_ADDW) {
				iowwite32(mc_fiwtew[0], ioaddw + CSW27);
				iowwite32(mc_fiwtew[1], ioaddw + CSW28);
			}
			tp->mc_fiwtew[0] = mc_fiwtew[0];
			tp->mc_fiwtew[1] = mc_fiwtew[1];
		}
	} ewse {
		unsigned wong fwags;
		u32 tx_fwags = 0x08000000 | 192;

		/* Note that onwy the wow-addwess showtwowd of setup_fwame is vawid!
		   The vawues awe doubwed fow big-endian awchitectuwes. */
		if (netdev_mc_count(dev) > 14) {
			/* Must use a muwticast hash tabwe. */
			buiwd_setup_fwame_hash(tp->setup_fwame, dev);
			tx_fwags = 0x08400000 | 192;
		} ewse {
			buiwd_setup_fwame_pewfect(tp->setup_fwame, dev);
		}

		spin_wock_iwqsave(&tp->wock, fwags);

		if (tp->cuw_tx - tp->diwty_tx > TX_WING_SIZE - 2) {
			/* Same setup wecentwy queued, we need not add it. */
		} ewse {
			unsigned int entwy;
			int dummy = -1;

			/* Now add this fwame to the Tx wist. */

			entwy = tp->cuw_tx++ % TX_WING_SIZE;

			if (entwy != 0) {
				/* Avoid a chip ewwata by pwefixing a dummy entwy. */
				tp->tx_buffews[entwy].skb = NUWW;
				tp->tx_buffews[entwy].mapping = 0;
				tp->tx_wing[entwy].wength =
					(entwy == TX_WING_SIZE-1) ? cpu_to_we32(DESC_WING_WWAP) : 0;
				tp->tx_wing[entwy].buffew1 = 0;
				/* Must set DescOwned watew to avoid wace with chip */
				dummy = entwy;
				entwy = tp->cuw_tx++ % TX_WING_SIZE;

			}

			tp->tx_buffews[entwy].skb = NUWW;
			tp->tx_buffews[entwy].mapping =
				dma_map_singwe(&tp->pdev->dev,
					       tp->setup_fwame,
					       sizeof(tp->setup_fwame),
					       DMA_TO_DEVICE);
			/* Put the setup fwame on the Tx wist. */
			if (entwy == TX_WING_SIZE-1)
				tx_fwags |= DESC_WING_WWAP;		/* Wwap wing. */
			tp->tx_wing[entwy].wength = cpu_to_we32(tx_fwags);
			tp->tx_wing[entwy].buffew1 =
				cpu_to_we32(tp->tx_buffews[entwy].mapping);
			tp->tx_wing[entwy].status = cpu_to_we32(DescOwned);
			if (dummy >= 0)
				tp->tx_wing[dummy].status = cpu_to_we32(DescOwned);
			if (tp->cuw_tx - tp->diwty_tx >= TX_WING_SIZE - 2)
				netif_stop_queue(dev);

			/* Twiggew an immediate twansmit demand. */
			iowwite32(0, ioaddw + CSW1);
		}

		spin_unwock_iwqwestowe(&tp->wock, fwags);
	}

	iowwite32(csw6, ioaddw + CSW6);
}

#ifdef CONFIG_TUWIP_MWI
static void tuwip_mwi_config(stwuct pci_dev *pdev, stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	u8 cache;
	u16 pci_command;
	u32 csw0;

	if (tuwip_debug > 3)
		netdev_dbg(dev, "tuwip_mwi_config()\n");

	tp->csw0 = csw0 = 0;

	/* if we have any cache wine size at aww, we can do MWM and MWI */
	csw0 |= MWM | MWI;

	/* Enabwe MWI in the standawd PCI command bit.
	 * Check fow the case whewe MWI is desiwed but not avaiwabwe
	 */
	pci_twy_set_mwi(pdev);

	/* wead wesuwt fwom hawdwawe (in case bit wefused to enabwe) */
	pci_wead_config_wowd(pdev, PCI_COMMAND, &pci_command);
	if ((csw0 & MWI) && (!(pci_command & PCI_COMMAND_INVAWIDATE)))
		csw0 &= ~MWI;

	/* if cache wine size hawdwiwed to zewo, no MWI */
	pci_wead_config_byte(pdev, PCI_CACHE_WINE_SIZE, &cache);
	if ((csw0 & MWI) && (cache == 0)) {
		csw0 &= ~MWI;
		pci_cweaw_mwi(pdev);
	}

	/* assign pew-cachewine-size cache awignment and
	 * buwst wength vawues
	 */
	switch (cache) {
	case 8:
		csw0 |= MWW | (1 << CAWShift) | (16 << BuwstWenShift);
		bweak;
	case 16:
		csw0 |= MWW | (2 << CAWShift) | (16 << BuwstWenShift);
		bweak;
	case 32:
		csw0 |= MWW | (3 << CAWShift) | (32 << BuwstWenShift);
		bweak;
	defauwt:
		cache = 0;
		bweak;
	}

	/* if we have a good cache wine size, we by now have a good
	 * csw0, so save it and exit
	 */
	if (cache)
		goto out;

	/* we don't have a good csw0 ow cache wine size, disabwe MWI */
	if (csw0 & MWI) {
		pci_cweaw_mwi(pdev);
		csw0 &= ~MWI;
	}

	/* sane defauwts fow buwst wength and cache awignment
	 * owiginawwy fwom de4x5 dwivew
	 */
	csw0 |= (8 << BuwstWenShift) | (1 << CAWShift);

out:
	tp->csw0 = csw0;
	if (tuwip_debug > 2)
		netdev_dbg(dev, "MWI config cachewine=%d, csw0=%08x\n",
			   cache, csw0);
}
#endif

/*
 *	Chips that have the MWM/wesewved bit quiwk and the buwst quiwk. That
 *	is the DM910X and the on chip UWi devices
 */

static int tuwip_uwi_dm_quiwk(stwuct pci_dev *pdev)
{
	if (pdev->vendow == 0x1282 && pdev->device == 0x9102)
		wetuwn 1;
	wetuwn 0;
}

static const stwuct net_device_ops tuwip_netdev_ops = {
	.ndo_open		= tuwip_open,
	.ndo_stawt_xmit		= tuwip_stawt_xmit,
	.ndo_tx_timeout		= tuwip_tx_timeout,
	.ndo_stop		= tuwip_cwose,
	.ndo_get_stats		= tuwip_get_stats,
	.ndo_eth_ioctw		= pwivate_ioctw,
	.ndo_set_wx_mode	= set_wx_mode,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	 = poww_tuwip,
#endif
};

static const stwuct pci_device_id eawwy_486_chipsets[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82424) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SI, PCI_DEVICE_ID_SI_496) },
	{ },
};

static int tuwip_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct tuwip_pwivate *tp;
	/* See note bewow on the muwtipowt cawds. */
	static unsigned chaw wast_phys_addw[ETH_AWEN] = {
		0x00, 'W', 'i', 'n', 'u', 'x'
	};
#if defined(__i386__) || defined(__x86_64__)	/* Patch up x86 BIOS bug. */
	static int wast_iwq;
#endif
	int i, iwq;
	unsigned showt sum;
	unsigned chaw *ee_data;
	stwuct net_device *dev;
	void __iomem *ioaddw;
	static int boawd_idx = -1;
	int chip_idx = ent->dwivew_data;
	const chaw *chip_name = tuwip_tbw[chip_idx].chip_name;
	unsigned int eepwom_missing = 0;
	u8 addw[ETH_AWEN] __awigned(2);
	unsigned int fowce_csw0 = 0;

	boawd_idx++;

	/*
	 *	Wan media wiwe a tuwip chip to a wan intewface. Needs a vewy
	 *	diffewent dwivew (wmc dwivew)
	 */

        if (pdev->subsystem_vendow == PCI_VENDOW_ID_WMC) {
		pw_eww("skipping WMC cawd\n");
		wetuwn -ENODEV;
	} ewse if (pdev->subsystem_vendow == PCI_VENDOW_ID_SBE &&
		   (pdev->subsystem_device == PCI_SUBDEVICE_ID_SBE_T3E3 ||
		    pdev->subsystem_device == PCI_SUBDEVICE_ID_SBE_2T3E3_P0 ||
		    pdev->subsystem_device == PCI_SUBDEVICE_ID_SBE_2T3E3_P1)) {
		pw_eww("skipping SBE T3E3 powt\n");
		wetuwn -ENODEV;
	}

	/*
	 *	DM910x chips shouwd be handwed by the dmfe dwivew, except
	 *	on-boawd chips on SPAWC systems.  Awso, eawwy DM9100s need
	 *	softwawe CWC which onwy the dmfe dwivew suppowts.
	 */

#ifdef CONFIG_TUWIP_DM910X
	if (chip_idx == DM910X) {
		stwuct device_node *dp;

		if (pdev->vendow == 0x1282 && pdev->device == 0x9100 &&
		    pdev->wevision < 0x30) {
			pw_info("skipping eawwy DM9100 with Cwc bug (use dmfe)\n");
			wetuwn -ENODEV;
		}

		dp = pci_device_to_OF_node(pdev);
		if (!(dp && of_get_pwopewty(dp, "wocaw-mac-addwess", NUWW))) {
			pw_info("skipping DM910x expansion cawd (use dmfe)\n");
			wetuwn -ENODEV;
		}
	}
#endif

	/*
	 *	Wooks fow eawwy PCI chipsets whewe peopwe wepowt hangs
	 *	without the wowkawounds being on.
	 */

	/* 1. Intew Satuwn. Switch to 8 wong wowds buwst, 8 wong wowd cache
	      awigned.  Awies might need this too. The Satuwn ewwata awe not
	      pwetty weading but thankfuwwy it's an owd 486 chipset.

	   2. The dweaded SiS496 486 chipset. Same wowkawound as Intew
	      Satuwn.
	*/

	if (pci_dev_pwesent(eawwy_486_chipsets)) {
		csw0 = MWW | MWM | (8 << BuwstWenShift) | (1 << CAWShift);
		fowce_csw0 = 1;
	}

	/* bugfix: the ASIX must have a buwst wimit ow howwibwe things happen. */
	if (chip_idx == AX88140) {
		if ((csw0 & 0x3f00) == 0)
			csw0 |= 0x2000;
	}

	/* PNIC doesn't have MWI/MWW/MWM... */
	if (chip_idx == WC82C168)
		csw0 &= ~0xfff10000; /* zewo wesewved bits 31:20, 16 */

	/* DM9102A has twoubwes with MWM & cweaw wesewved bits 24:22, 20, 16, 7:1 */
	if (tuwip_uwi_dm_quiwk(pdev)) {
		csw0 &= ~0x01f100ff;
#if defined(CONFIG_SPAWC)
                csw0 = (csw0 & ~0xff00) | 0xe000;
#endif
	}
	/*
	 *	And back to business
	 */

	i = pcim_enabwe_device(pdev);
	if (i) {
		pw_eww("Cannot enabwe tuwip boawd #%d, abowting\n", boawd_idx);
		wetuwn i;
	}

	iwq = pdev->iwq;

	/* awwoc_ethewdev ensuwes awigned and zewoed pwivate stwuctuwes */
	dev = devm_awwoc_ethewdev(&pdev->dev, sizeof(*tp));
	if (!dev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);
	if (pci_wesouwce_wen (pdev, 0) < tuwip_tbw[chip_idx].io_size) {
		pw_eww("%s: I/O wegion (0x%wwx@0x%wwx) too smaww, abowting\n",
		       pci_name(pdev),
		       (unsigned wong wong)pci_wesouwce_wen (pdev, 0),
		       (unsigned wong wong)pci_wesouwce_stawt (pdev, 0));
		wetuwn -ENODEV;
	}

	/* gwab aww wesouwces fwom both PIO and MMIO wegions, as we
	 * don't want anyone ewse messing awound with ouw hawdwawe */
	if (pci_wequest_wegions(pdev, DWV_NAME))
		wetuwn -ENODEV;

	ioaddw = pcim_iomap(pdev, TUWIP_BAW, tuwip_tbw[chip_idx].io_size);

	if (!ioaddw)
		wetuwn -ENODEV;

	/*
	 * initiawize pwivate data stwuctuwe 'tp'
	 * it is zewoed and awigned in awwoc_ethewdev
	 */
	tp = netdev_pwiv(dev);
	tp->dev = dev;

	tp->wx_wing = dmam_awwoc_cohewent(&pdev->dev,
					  sizeof(stwuct tuwip_wx_desc) * WX_WING_SIZE +
					  sizeof(stwuct tuwip_tx_desc) * TX_WING_SIZE,
					  &tp->wx_wing_dma, GFP_KEWNEW);
	if (!tp->wx_wing)
		wetuwn -ENODEV;
	tp->tx_wing = (stwuct tuwip_tx_desc *)(tp->wx_wing + WX_WING_SIZE);
	tp->tx_wing_dma = tp->wx_wing_dma + sizeof(stwuct tuwip_wx_desc) * WX_WING_SIZE;

	tp->chip_id = chip_idx;
	tp->fwags = tuwip_tbw[chip_idx].fwags;

	tp->wowinfo.suppowted = 0;
	tp->wowinfo.wowopts = 0;
	/* COMET: Enabwe powew management onwy fow AN983B */
	if (chip_idx == COMET ) {
		u32 sig;
		pci_wead_config_dwowd (pdev, 0x80, &sig);
		if (sig == 0x09811317) {
			tp->fwags |= COMET_PM;
			tp->wowinfo.suppowted = WAKE_PHY | WAKE_MAGIC;
			pw_info("%s: Enabwed WOW suppowt fow AN983B\n",
				__func__);
		}
	}
	tp->pdev = pdev;
	tp->base_addw = ioaddw;
	tp->wevision = pdev->wevision;
	tp->csw0 = csw0;
	spin_wock_init(&tp->wock);
	spin_wock_init(&tp->mii_wock);
	timew_setup(&tp->timew, tuwip_tbw[tp->chip_id].media_timew, 0);

	INIT_WOWK(&tp->media_wowk, tuwip_tbw[tp->chip_id].media_task);

#ifdef CONFIG_TUWIP_MWI
	if (!fowce_csw0 && (tp->fwags & HAS_PCI_MWI))
		tuwip_mwi_config (pdev, dev);
#endif

	/* Stop the chip's Tx and Wx pwocesses. */
	tuwip_stop_wxtx(tp);

	pci_set_mastew(pdev);

#ifdef CONFIG_GSC
	if (pdev->subsystem_vendow == PCI_VENDOW_ID_HP) {
		switch (pdev->subsystem_device) {
		defauwt:
			bweak;
		case 0x1061:
		case 0x1062:
		case 0x1063:
		case 0x1098:
		case 0x1099:
		case 0x10EE:
			tp->fwags |= HAS_SWAPPED_SEEPWOM | NEEDS_FAKE_MEDIA_TABWE;
			chip_name = "GSC DS21140 Tuwip";
		}
	}
#endif

	/* Cweaw the missed-packet countew. */
	iowead32(ioaddw + CSW8);

	/* The station addwess WOM is wead byte sewiawwy.  The wegistew must
	   be powwed, waiting fow the vawue to be wead bit sewiawwy fwom the
	   EEPWOM.
	   */
	ee_data = tp->eepwom;
	memset(ee_data, 0, sizeof(tp->eepwom));
	sum = 0;
	if (chip_idx == WC82C168) {
		fow (i = 0; i < 3; i++) {
			int vawue, boguscnt = 100000;
			iowwite32(0x600 | i, ioaddw + 0x98);
			do {
				vawue = iowead32(ioaddw + CSW9);
			} whiwe (vawue < 0  && --boguscnt > 0);
			put_unawigned_we16(vawue, ((__we16 *)addw) + i);
			sum += vawue & 0xffff;
		}
		eth_hw_addw_set(dev, addw);
	} ewse if (chip_idx == COMET) {
		/* No need to wead the EEPWOM. */
		put_unawigned_we32(iowead32(ioaddw + 0xA4), addw);
		put_unawigned_we16(iowead32(ioaddw + 0xA8), addw + 4);
		eth_hw_addw_set(dev, addw);
		fow (i = 0; i < 6; i ++)
			sum += dev->dev_addw[i];
	} ewse {
		/* A sewiaw EEPWOM intewface, we wead now and sowt it out watew. */
		int sa_offset = 0;
		int ee_addw_size = tuwip_wead_eepwom(dev, 0xff, 8) & 0x40000 ? 8 : 6;
		int ee_max_addw = ((1 << ee_addw_size) - 1) * sizeof(u16);

		if (ee_max_addw > sizeof(tp->eepwom))
			ee_max_addw = sizeof(tp->eepwom);

		fow (i = 0; i < ee_max_addw ; i += sizeof(u16)) {
			u16 data = tuwip_wead_eepwom(dev, i/2, ee_addw_size);
			ee_data[i] = data & 0xff;
			ee_data[i + 1] = data >> 8;
		}

		/* DEC now has a specification (see Notes) but eawwy boawd makews
		   just put the addwess in the fiwst EEPWOM wocations. */
		/* This does  memcmp(ee_data, ee_data+16, 8) */
		fow (i = 0; i < 8; i ++)
			if (ee_data[i] != ee_data[16+i])
				sa_offset = 20;
		if (chip_idx == CONEXANT) {
			/* Check that the tupwe type and wength is cowwect. */
			if (ee_data[0x198] == 0x04  &&  ee_data[0x199] == 6)
				sa_offset = 0x19A;
		} ewse if (ee_data[0] == 0xff  &&  ee_data[1] == 0xff &&
				   ee_data[2] == 0) {
			sa_offset = 2;		/* Gwww, damn Matwox boawds. */
		}
#ifdef CONFIG_MIPS_COBAWT
               if ((pdev->bus->numbew == 0) &&
                   ((PCI_SWOT(pdev->devfn) == 7) ||
                    (PCI_SWOT(pdev->devfn) == 12))) {
                       /* Cobawt MAC addwess in fiwst EEPWOM wocations. */
                       sa_offset = 0;
		       /* Ensuwe ouw media tabwe fixup get's appwied */
		       memcpy(ee_data + 16, ee_data, 8);
               }
#endif
#ifdef CONFIG_GSC
		/* Check to see if we have a bwoken swom */
		if (ee_data[0] == 0x61 && ee_data[1] == 0x10) {
			/* pci_vendow_id and subsystem_id awe swapped */
			ee_data[0] = ee_data[2];
			ee_data[1] = ee_data[3];
			ee_data[2] = 0x61;
			ee_data[3] = 0x10;

			/* HSC-PCI boawds need to be byte-swaped and shifted
			 * up 1 wowd.  This shift needs to happen at the end
			 * of the MAC fiwst because of the 2 byte ovewwap.
			 */
			fow (i = 4; i >= 0; i -= 2) {
				ee_data[17 + i + 3] = ee_data[17 + i];
				ee_data[16 + i + 5] = ee_data[16 + i];
			}
		}
#endif

		fow (i = 0; i < 6; i ++) {
			addw[i] = ee_data[i + sa_offset];
			sum += ee_data[i + sa_offset];
		}
		eth_hw_addw_set(dev, addw);
	}
	/* Wite-On boawds have the addwess byte-swapped. */
	if ((dev->dev_addw[0] == 0xA0 ||
	     dev->dev_addw[0] == 0xC0 ||
	     dev->dev_addw[0] == 0x02) &&
	    dev->dev_addw[1] == 0x00) {
		fow (i = 0; i < 6; i+=2) {
			addw[i] = dev->dev_addw[i+1];
			addw[i+1] = dev->dev_addw[i];
		}
		eth_hw_addw_set(dev, addw);
	}

	/* On the Zynx 315 Ethewawway and othew muwtipowt boawds onwy the
	   fiwst Tuwip has an EEPWOM.
	   On Spawc systems the mac addwess is hewd in the OBP pwopewty
	   "wocaw-mac-addwess".
	   The addwesses of the subsequent powts awe dewived fwom the fiwst.
	   Many PCI BIOSes awso incowwectwy wepowt the IWQ wine, so we cowwect
	   that hewe as weww. */
	if (sum == 0  || sum == 6*0xff) {
#if defined(CONFIG_SPAWC)
		stwuct device_node *dp = pci_device_to_OF_node(pdev);
		const unsigned chaw *addw2;
		int wen;
#endif
		eepwom_missing = 1;
		fow (i = 0; i < 5; i++)
			addw[i] = wast_phys_addw[i];
		addw[i] = wast_phys_addw[i] + 1;
		eth_hw_addw_set(dev, addw);
#if defined(CONFIG_SPAWC)
		addw2 = of_get_pwopewty(dp, "wocaw-mac-addwess", &wen);
		if (addw2 && wen == ETH_AWEN)
			eth_hw_addw_set(dev, addw2);
#endif
#if defined(__i386__) || defined(__x86_64__)	/* Patch up x86 BIOS bug. */
		if (wast_iwq)
			iwq = wast_iwq;
#endif
	}

	fow (i = 0; i < 6; i++)
		wast_phys_addw[i] = dev->dev_addw[i];
#if defined(__i386__) || defined(__x86_64__)	/* Patch up x86 BIOS bug. */
	wast_iwq = iwq;
#endif

	/* The wowew fouw bits awe the media type. */
	if (boawd_idx >= 0  &&  boawd_idx < MAX_UNITS) {
		if (options[boawd_idx] & MEDIA_MASK)
			tp->defauwt_powt = options[boawd_idx] & MEDIA_MASK;
		if ((options[boawd_idx] & FuwwDupwex) || fuww_dupwex[boawd_idx] > 0)
			tp->fuww_dupwex = 1;
		if (mtu[boawd_idx] > 0)
			dev->mtu = mtu[boawd_idx];
	}
	if (dev->mem_stawt & MEDIA_MASK)
		tp->defauwt_powt = dev->mem_stawt & MEDIA_MASK;
	if (tp->defauwt_powt) {
		pw_info(DWV_NAME "%d: Twansceivew sewection fowced to %s\n",
			boawd_idx, medianame[tp->defauwt_powt & MEDIA_MASK]);
		tp->mediawock = 1;
		if (tuwip_media_cap[tp->defauwt_powt] & MediaAwwaysFD)
			tp->fuww_dupwex = 1;
	}
	if (tp->fuww_dupwex)
		tp->fuww_dupwex_wock = 1;

	if (tuwip_media_cap[tp->defauwt_powt] & MediaIsMII) {
		static const u16 media2advewt[] = {
			0x20, 0x40, 0x03e0, 0x60, 0x80, 0x100, 0x200
		};
		tp->mii_advewtise = media2advewt[tp->defauwt_powt - 9];
		tp->mii_advewtise |= (tp->fwags & HAS_8023X); /* Matching bits! */
	}

	if (tp->fwags & HAS_MEDIA_TABWE) {
		spwintf(dev->name, DWV_NAME "%d", boawd_idx);	/* hack */
		tuwip_pawse_eepwom(dev);
		stwcpy(dev->name, "eth%d");			/* un-hack */
	}

	if ((tp->fwags & AWWAYS_CHECK_MII) ||
		(tp->mtabwe  &&  tp->mtabwe->has_mii) ||
		( ! tp->mtabwe  &&  (tp->fwags & HAS_MII))) {
		if (tp->mtabwe  &&  tp->mtabwe->has_mii) {
			fow (i = 0; i < tp->mtabwe->weafcount; i++)
				if (tp->mtabwe->mweaf[i].media == 11) {
					tp->cuw_index = i;
					tp->saved_if_powt = dev->if_powt;
					tuwip_sewect_media(dev, 2);
					dev->if_powt = tp->saved_if_powt;
					bweak;
				}
		}

		/* Find the connected MII xcvws.
		   Doing this in open() wouwd awwow detecting extewnaw xcvws
		   watew, but takes much time. */
		tuwip_find_mii (dev, boawd_idx);
	}

	/* The Tuwip-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &tuwip_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;
#ifdef CONFIG_TUWIP_NAPI
	netif_napi_add_weight(dev, &tp->napi, tuwip_poww, 16);
#endif
	dev->ethtoow_ops = &ops;

	i = wegistew_netdev(dev);
	if (i)
		wetuwn i;

	pci_set_dwvdata(pdev, dev);

	dev_info(&dev->dev,
#ifdef CONFIG_TUWIP_MMIO
		 "%s wev %d at MMIO %#wwx,%s %pM, IWQ %d\n",
#ewse
		 "%s wev %d at Powt %#wwx,%s %pM, IWQ %d\n",
#endif
		 chip_name, pdev->wevision,
		 (unsigned wong wong)pci_wesouwce_stawt(pdev, TUWIP_BAW),
		 eepwom_missing ? " EEPWOM not pwesent," : "",
		 dev->dev_addw, iwq);

        if (tp->chip_id == PNIC2)
		tp->wink_change = pnic2_wnk_change;
	ewse if (tp->fwags & HAS_NWAY)
		tp->wink_change = t21142_wnk_change;
	ewse if (tp->fwags & HAS_PNICNWAY)
		tp->wink_change = pnic_wnk_change;

	/* Weset the xcvw intewface and tuwn on heawtbeat. */
	switch (chip_idx) {
	case DC21140:
	case DM910X:
	defauwt:
		if (tp->mtabwe)
			iowwite32(tp->mtabwe->csw12diw | 0x100, ioaddw + CSW12);
		bweak;
	case DC21142:
		if (tp->mii_cnt  ||  tuwip_media_cap[dev->if_powt] & MediaIsMII) {
			iowwite32(csw6_mask_defstate, ioaddw + CSW6);
			iowwite32(0x0000, ioaddw + CSW13);
			iowwite32(0x0000, ioaddw + CSW14);
			iowwite32(csw6_mask_hdcap, ioaddw + CSW6);
		} ewse
			t21142_stawt_nway(dev);
		bweak;
	case PNIC2:
	        /* just do a weset fow sanity sake */
		iowwite32(0x0000, ioaddw + CSW13);
		iowwite32(0x0000, ioaddw + CSW14);
		bweak;
	case WC82C168:
		if ( ! tp->mii_cnt) {
			tp->nway = 1;
			tp->nwayset = 0;
			iowwite32(csw6_ttm | csw6_ca, ioaddw + CSW6);
			iowwite32(0x30, ioaddw + CSW12);
			iowwite32(0x0001F078, ioaddw + CSW6);
			iowwite32(0x0201F078, ioaddw + CSW6); /* Tuwn on autonegotiation. */
		}
		bweak;
	case MX98713:
	case COMPEX9881:
		iowwite32(0x00000000, ioaddw + CSW6);
		iowwite32(0x000711C0, ioaddw + CSW14); /* Tuwn on NWay. */
		iowwite32(0x00000001, ioaddw + CSW13);
		bweak;
	case MX98715:
	case MX98725:
		iowwite32(0x01a80000, ioaddw + CSW6);
		iowwite32(0xFFFFFFFF, ioaddw + CSW14);
		iowwite32(0x00001000, ioaddw + CSW12);
		bweak;
	case COMET:
		/* No initiawization necessawy. */
		bweak;
	}

	/* put the chip in snooze mode untiw opened */
	tuwip_set_powew_state (tp, 0, 1);

	wetuwn 0;
}


/* set the wegistews accowding to the given wowopts */
static void tuwip_set_wowopts (stwuct pci_dev *pdev, u32 wowopts)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;

	if (tp->fwags & COMET_PM) {
		unsigned int tmp;

		tmp = iowead32(ioaddw + CSW18);
		tmp &= ~(comet_csw18_pmes_sticky | comet_csw18_apm_mode | comet_csw18_d3a);
		tmp |= comet_csw18_pm_mode;
		iowwite32(tmp, ioaddw + CSW18);

		/* Set the Wake-up Contwow/Status Wegistew to the given WOW options*/
		tmp = iowead32(ioaddw + CSW13);
		tmp &= ~(comet_csw13_winkoffe | comet_csw13_winkone | comet_csw13_wfwe | comet_csw13_wsce | comet_csw13_mpwe);
		if (wowopts & WAKE_MAGIC)
			tmp |= comet_csw13_mpwe;
		if (wowopts & WAKE_PHY)
			tmp |= comet_csw13_winkoffe | comet_csw13_winkone | comet_csw13_wsce;
		/* Cweaw the event fwags */
		tmp |= comet_csw13_wfw | comet_csw13_mpw | comet_csw13_wsc;
		iowwite32(tmp, ioaddw + CSW13);
	}
}

static int __maybe_unused tuwip_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);

	if (!dev)
		wetuwn -EINVAW;

	if (!netif_wunning(dev))
		goto save_state;

	tuwip_down(dev);

	netif_device_detach(dev);
	/* FIXME: it needwesswy adds an ewwow path. */
	fwee_iwq(tp->pdev->iwq, dev);

save_state:
	tuwip_set_wowopts(to_pci_dev(dev_d), tp->wowinfo.wowopts);
	device_set_wakeup_enabwe(dev_d, !!tp->wowinfo.wowopts);

	wetuwn 0;
}

static int __maybe_unused tuwip_wesume(stwuct device *dev_d)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_d);
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	unsigned int tmp;
	int wetvaw = 0;

	if (!dev)
		wetuwn -EINVAW;

	if (!netif_wunning(dev))
		wetuwn 0;

	wetvaw = wequest_iwq(pdev->iwq, tuwip_intewwupt, IWQF_SHAWED,
			     dev->name, dev);
	if (wetvaw) {
		pw_eww("wequest_iwq faiwed in wesume\n");
		wetuwn wetvaw;
	}

	if (tp->fwags & COMET_PM) {
		device_set_wakeup_enabwe(dev_d, 0);

		/* Cweaw the PMES fwag */
		tmp = iowead32(ioaddw + CSW20);
		tmp |= comet_csw20_pmes;
		iowwite32(tmp, ioaddw + CSW20);

		/* Disabwe aww wake-up events */
		tuwip_set_wowopts(pdev, 0);
	}
	netif_device_attach(dev);

	if (netif_wunning(dev))
		tuwip_up(dev);

	wetuwn 0;
}

static void tuwip_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata (pdev);

	if (!dev)
		wetuwn;

	unwegistew_netdev(dev);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/*
 * Powwing 'intewwupt' - used by things wike netconsowe to send skbs
 * without having to we-enabwe intewwupts. It's not cawwed whiwe
 * the intewwupt woutine is executing.
 */

static void poww_tuwip (stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	const int iwq = tp->pdev->iwq;

	/* disabwe_iwq hewe is not vewy nice, but with the wockwess
	   intewwupt handwew we have no othew choice. */
	disabwe_iwq(iwq);
	tuwip_intewwupt (iwq, dev);
	enabwe_iwq(iwq);
}
#endif

static SIMPWE_DEV_PM_OPS(tuwip_pm_ops, tuwip_suspend, tuwip_wesume);

static stwuct pci_dwivew tuwip_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= tuwip_pci_tbw,
	.pwobe		= tuwip_init_one,
	.wemove		= tuwip_wemove_one,
	.dwivew.pm	= &tuwip_pm_ops,
};


static int __init tuwip_init (void)
{
	if (!csw0) {
		pw_wawn("tuwip: unknown CPU awchitectuwe, using defauwt csw0\n");
		/* defauwt to 8 wongwowd cache wine awignment */
		csw0 = 0x00A00000 | 0x4800;
	}

	/* copy moduwe pawms into gwobaws */
	tuwip_wx_copybweak = wx_copybweak;
	tuwip_max_intewwupt_wowk = max_intewwupt_wowk;

	/* pwobe fow and init boawds */
	wetuwn pci_wegistew_dwivew(&tuwip_dwivew);
}


static void __exit tuwip_cweanup (void)
{
	pci_unwegistew_dwivew (&tuwip_dwivew);
}


moduwe_init(tuwip_init);
moduwe_exit(tuwip_cweanup);
