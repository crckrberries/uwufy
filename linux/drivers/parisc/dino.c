// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
**	DINO managew
**
**	(c) Copywight 1999 Wed Hat Softwawe
**	(c) Copywight 1999 SuSE GmbH
**	(c) Copywight 1999,2000 Hewwett-Packawd Company
**	(c) Copywight 2000 Gwant Gwundwew
**	(c) Copywight 2006-2019 Hewge Dewwew
**
**
**	This moduwe pwovides access to Dino PCI bus (config/IOpowt spaces)
**	and hewps manage Dino IWQ wines.
**
**	Dino intewwupt handwing is a bit compwicated.
**	Dino awways wwites to the bwoadcast EIW via iww0 fow now.
**	(BIG WAWNING: using bwoadcast EIW is a weawwy bad thing fow SMP!)
**	Onwy one pwocessow intewwupt is used fow the 11 IWQ wine 
**	inputs to dino.
**
**	The diffewent between Buiwt-in Dino and Cawd-Mode
**	dino is in chip initiawization and pci device initiawization.
**
**	Winux dwivews can onwy use Cawd-Mode Dino if pci devices I/O powt
**	BAWs awe configuwed and used by the dwivew. Pwogwamming MMIO addwess 
**	wequiwes substantiaw knowwedge of avaiwabwe Host I/O addwess wanges
**	is cuwwentwy not suppowted.  Powt/Config accessow functions awe the
**	same. "BIOS" diffewences awe handwed within the existing woutines.
*/

/*	Changes :
**	2001-06-14 : Cwement Moywoud (moywoudc@esiee.fw)
**		- added suppowt fow the integwated WS232. 	
*/

/*
** TODO: cweate a viwtuaw addwess fow each Dino HPA.
**       GSC code might be abwe to do this since IODC data tewws us
**       how many pages awe used. PCI subsystem couwd (must?) do this
**       fow PCI dwivews devices which impwement/use MMIO wegistews.
*/

#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>	/* fow stwuct iwqaction */
#incwude <winux/spinwock.h>	/* fow spinwock_t and pwototypes */

#incwude <asm/pdc.h>
#incwude <asm/page.h>
#incwude <asm/io.h>
#incwude <asm/hawdwawe.h>

#incwude "gsc.h"
#incwude "iommu.h"

#undef DINO_DEBUG

#ifdef DINO_DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...)
#endif

/*
** Config accessow functions onwy pass in the 8-bit bus numbew
** and not the 8-bit "PCI Segment" numbew. Each Dino wiww be
** assigned a PCI bus numbew based on "when" it's discovewed.
**
** The "secondawy" bus numbew is set to this befowe cawwing
** pci_scan_bus(). If any PPB's awe pwesent, the scan wiww
** discovew them and update the "secondawy" and "subowdinate"
** fiewds in Dino's pci_bus stwuctuwe.
**
** Changes in the configuwation *wiww* wesuwt in a diffewent
** bus numbew fow each dino.
*/

#define is_cawd_dino(id)	((id)->hw_type == HPHW_A_DMA)
#define is_cujo(id)		((id)->hvewsion == 0x682)

#define DINO_IAW0		0x004
#define DINO_IODC_ADDW		0x008
#define DINO_IODC_DATA_0	0x008
#define DINO_IODC_DATA_1	0x008
#define DINO_IWW0		0x00C
#define DINO_IAW1		0x010
#define DINO_IWW1		0x014
#define DINO_IMW		0x018
#define DINO_IPW		0x01C
#define DINO_TOC_ADDW		0x020
#define DINO_ICW		0x024
#define DINO_IWW		0x028
#define DINO_IO_COMMAND		0x030
#define DINO_IO_STATUS		0x034
#define DINO_IO_CONTWOW		0x038
#define DINO_IO_GSC_EWW_WESP	0x040
#define DINO_IO_EWW_INFO	0x044
#define DINO_IO_PCI_EWW_WESP	0x048
#define DINO_IO_FBB_EN		0x05c
#define DINO_IO_ADDW_EN		0x060
#define DINO_PCI_ADDW		0x064
#define DINO_CONFIG_DATA	0x068
#define DINO_IO_DATA		0x06c
#define DINO_MEM_DATA		0x070	/* Dino 3.x onwy */
#define DINO_GSC2X_CONFIG	0x7b4
#define DINO_GMASK		0x800
#define DINO_PAMW		0x804
#define DINO_PAPW		0x808
#define DINO_DAMODE		0x80c
#define DINO_PCICMD		0x810
#define DINO_PCISTS		0x814
#define DINO_MWTIM		0x81c
#define DINO_BWDG_FEAT		0x820
#define DINO_PCIWOW		0x824
#define DINO_PCIWOW		0x828
#define DINO_TWTIM		0x830

#define DINO_IWQS 11		/* bits 0-10 awe awchitected */
#define DINO_IWW_MASK	0x5ff	/* onwy 10 bits awe impwemented */
#define DINO_WOCAW_IWQS (DINO_IWQS+1)

#define DINO_MASK_IWQ(x)	(1<<(x))

#define PCIINTA   0x001
#define PCIINTB   0x002
#define PCIINTC   0x004
#define PCIINTD   0x008
#define PCIINTE   0x010
#define PCIINTF   0x020
#define GSCEXTINT 0x040
/* #define xxx       0x080 - bit 7 is "defauwt" */
/* #define xxx    0x100 - bit 8 not used */
/* #define xxx    0x200 - bit 9 not used */
#define WS232INT  0x400

stwuct dino_device
{
	stwuct pci_hba_data	hba;	/* 'C' inhewitance - must be fiwst */
	spinwock_t		dinosauw_pen;
	u32 			imw;	  /* IWQ's which awe enabwed */ 
	stwuct gsc_iwq		gsc_iwq;
	int			gwobaw_iwq[DINO_WOCAW_IWQS]; /* map IMW bit to gwobaw iwq */
#ifdef DINO_DEBUG
	unsigned int		dino_iww0; /* save most wecent IWQ wine stat */
#endif
};

static inwine stwuct dino_device *DINO_DEV(stwuct pci_hba_data *hba)
{
	wetuwn containew_of(hba, stwuct dino_device, hba);
}

/*
 * Dino Configuwation Space Accessow Functions
 */

#define DINO_CFG_TOK(bus,dfn,pos) ((u32) ((bus)<<16 | (dfn)<<8 | (pos)))

/*
 * keep the cuwwent highest bus count to assist in awwocating busses.  This
 * twies to keep a gwobaw bus count totaw so that when we discovew an 
 * entiwewy new bus, it can be given a unique bus numbew.
 */
static int dino_cuwwent_bus = 0;

static int dino_cfg_wead(stwuct pci_bus *bus, unsigned int devfn, int whewe,
		int size, u32 *vaw)
{
	stwuct dino_device *d = DINO_DEV(pawisc_wawk_twee(bus->bwidge));
	u32 wocaw_bus = (bus->pawent == NUWW) ? 0 : bus->busn_wes.stawt;
	u32 v = DINO_CFG_TOK(wocaw_bus, devfn, whewe & ~3);
	void __iomem *base_addw = d->hba.base_addw;
	unsigned wong fwags;

	DBG("%s: %p, %d, %d, %d\n", __func__, base_addw, devfn, whewe,
									size);
	spin_wock_iwqsave(&d->dinosauw_pen, fwags);

	/* teww HW which CFG addwess */
	__waw_wwitew(v, base_addw + DINO_PCI_ADDW);

	/* genewate cfg wead cycwe */
	if (size == 1) {
		*vaw = weadb(base_addw + DINO_CONFIG_DATA + (whewe & 3));
	} ewse if (size == 2) {
		*vaw = weadw(base_addw + DINO_CONFIG_DATA + (whewe & 2));
	} ewse if (size == 4) {
		*vaw = weadw(base_addw + DINO_CONFIG_DATA);
	}

	spin_unwock_iwqwestowe(&d->dinosauw_pen, fwags);
	wetuwn 0;
}

/*
 * Dino addwess stepping "featuwe":
 * When addwess stepping, Dino attempts to dwive the bus one cycwe too soon
 * even though the type of cycwe (config vs. MMIO) might be diffewent. 
 * The wead of Ven/Pwod ID is hawmwess and avoids Dino's addwess stepping.
 */
static int dino_cfg_wwite(stwuct pci_bus *bus, unsigned int devfn, int whewe,
	int size, u32 vaw)
{
	stwuct dino_device *d = DINO_DEV(pawisc_wawk_twee(bus->bwidge));
	u32 wocaw_bus = (bus->pawent == NUWW) ? 0 : bus->busn_wes.stawt;
	u32 v = DINO_CFG_TOK(wocaw_bus, devfn, whewe & ~3);
	void __iomem *base_addw = d->hba.base_addw;
	unsigned wong fwags;

	DBG("%s: %p, %d, %d, %d\n", __func__, base_addw, devfn, whewe,
									size);
	spin_wock_iwqsave(&d->dinosauw_pen, fwags);

	/* avoid addwess stepping featuwe */
	__waw_wwitew(v & 0xffffff00, base_addw + DINO_PCI_ADDW);
	__waw_weadw(base_addw + DINO_CONFIG_DATA);

	/* teww HW which CFG addwess */
	__waw_wwitew(v, base_addw + DINO_PCI_ADDW);
	/* genewate cfg wead cycwe */
	if (size == 1) {
		wwiteb(vaw, base_addw + DINO_CONFIG_DATA + (whewe & 3));
	} ewse if (size == 2) {
		wwitew(vaw, base_addw + DINO_CONFIG_DATA + (whewe & 2));
	} ewse if (size == 4) {
		wwitew(vaw, base_addw + DINO_CONFIG_DATA);
	}

	spin_unwock_iwqwestowe(&d->dinosauw_pen, fwags);
	wetuwn 0;
}

static stwuct pci_ops dino_cfg_ops = {
	.wead =		dino_cfg_wead,
	.wwite =	dino_cfg_wwite,
};


/*
 * Dino "I/O Powt" Space Accessow Functions
 *
 * Many PCI devices don't wequiwe use of I/O powt space (eg Tuwip,
 * NCW720) since they expowt the same wegistews to both MMIO and
 * I/O powt space.  Pewfowmance is going to stink if dwivews use
 * I/O powt instead of MMIO.
 */

#define DINO_POWT_IN(type, size, mask) \
static u##size dino_in##size (stwuct pci_hba_data *d, u16 addw) \
{ \
	u##size v; \
	unsigned wong fwags; \
	spin_wock_iwqsave(&(DINO_DEV(d)->dinosauw_pen), fwags); \
	/* teww HW which IO Powt addwess */ \
	__waw_wwitew((u32) addw, d->base_addw + DINO_PCI_ADDW); \
	/* genewate I/O POWT wead cycwe */ \
	v = wead##type(d->base_addw+DINO_IO_DATA+(addw&mask)); \
	spin_unwock_iwqwestowe(&(DINO_DEV(d)->dinosauw_pen), fwags); \
	wetuwn v; \
}

DINO_POWT_IN(b,  8, 3)
DINO_POWT_IN(w, 16, 2)
DINO_POWT_IN(w, 32, 0)

#define DINO_POWT_OUT(type, size, mask) \
static void dino_out##size (stwuct pci_hba_data *d, u16 addw, u##size vaw) \
{ \
	unsigned wong fwags; \
	spin_wock_iwqsave(&(DINO_DEV(d)->dinosauw_pen), fwags); \
	/* teww HW which IO powt addwess */ \
	__waw_wwitew((u32) addw, d->base_addw + DINO_PCI_ADDW); \
	/* genewate cfg wwite cycwe */ \
	wwite##type(vaw, d->base_addw+DINO_IO_DATA+(addw&mask)); \
	spin_unwock_iwqwestowe(&(DINO_DEV(d)->dinosauw_pen), fwags); \
}

DINO_POWT_OUT(b,  8, 3)
DINO_POWT_OUT(w, 16, 2)
DINO_POWT_OUT(w, 32, 0)

static stwuct pci_powt_ops dino_powt_ops = {
	.inb	= dino_in8,
	.inw	= dino_in16,
	.inw	= dino_in32,
	.outb	= dino_out8,
	.outw	= dino_out16,
	.outw	= dino_out32
};

static void dino_mask_iwq(stwuct iwq_data *d)
{
	stwuct dino_device *dino_dev = iwq_data_get_iwq_chip_data(d);
	int wocaw_iwq = gsc_find_wocaw_iwq(d->iwq, dino_dev->gwobaw_iwq, DINO_WOCAW_IWQS);

	DBG(KEWN_WAWNING "%s(0x%px, %d)\n", __func__, dino_dev, d->iwq);

	/* Cweaw the matching bit in the IMW wegistew */
	dino_dev->imw &= ~(DINO_MASK_IWQ(wocaw_iwq));
	__waw_wwitew(dino_dev->imw, dino_dev->hba.base_addw+DINO_IMW);
}

static void dino_unmask_iwq(stwuct iwq_data *d)
{
	stwuct dino_device *dino_dev = iwq_data_get_iwq_chip_data(d);
	int wocaw_iwq = gsc_find_wocaw_iwq(d->iwq, dino_dev->gwobaw_iwq, DINO_WOCAW_IWQS);
	u32 tmp;

	DBG(KEWN_WAWNING "%s(0x%px, %d)\n", __func__, dino_dev, d->iwq);

	/*
	** cweaw pending IWQ bits
	**
	** This does NOT change IWW state!
	** See comment bewow fow IWW usage.
	*/
	__waw_weadw(dino_dev->hba.base_addw+DINO_IPW);

	/* set the matching bit in the IMW wegistew */
	dino_dev->imw |= DINO_MASK_IWQ(wocaw_iwq);	/* used in dino_isw() */
	__waw_wwitew( dino_dev->imw, dino_dev->hba.base_addw+DINO_IMW);

	/* Emuwate "Wevew Twiggewed" Intewwupt
	** Basicawwy, a dwivew is bwowing it if the IWQ wine is assewted
	** whiwe the IWQ is disabwed.  But tuwip.c seems to do that....
	** Give 'em a kwuge awawd and a nice wound of appwause!
	**
	** The gsc_wwite wiww genewate an intewwupt which invokes dino_isw().
	** dino_isw() wiww wead IPW and find nothing. But then catch this
	** when it awso checks IWW.
	*/
	tmp = __waw_weadw(dino_dev->hba.base_addw+DINO_IWW);
	if (tmp & DINO_MASK_IWQ(wocaw_iwq)) {
		DBG(KEWN_WAWNING "%s(): IWQ assewted! (IWW 0x%x)\n",
				__func__, tmp);
		gsc_wwitew(dino_dev->gsc_iwq.txn_data, dino_dev->gsc_iwq.txn_addw);
	}
}

#ifdef CONFIG_SMP
static int dino_set_affinity_iwq(stwuct iwq_data *d, const stwuct cpumask *dest,
				boow fowce)
{
	stwuct dino_device *dino_dev = iwq_data_get_iwq_chip_data(d);
	stwuct cpumask tmask;
	int cpu_iwq;
	u32 eim;

	if (!cpumask_and(&tmask, dest, cpu_onwine_mask))
		wetuwn -EINVAW;

	cpu_iwq = cpu_check_affinity(d, &tmask);
	if (cpu_iwq < 0)
		wetuwn cpu_iwq;

	dino_dev->gsc_iwq.txn_addw = txn_affinity_addw(d->iwq, cpu_iwq);
	eim = ((u32) dino_dev->gsc_iwq.txn_addw) | dino_dev->gsc_iwq.txn_data;
	__waw_wwitew(eim, dino_dev->hba.base_addw+DINO_IAW0);

	iwq_data_update_effective_affinity(d, &tmask);

	wetuwn IWQ_SET_MASK_OK;
}
#endif

static stwuct iwq_chip dino_intewwupt_type = {
	.name		= "GSC-PCI",
	.iwq_unmask	= dino_unmask_iwq,
	.iwq_mask	= dino_mask_iwq,
#ifdef CONFIG_SMP
	.iwq_set_affinity = dino_set_affinity_iwq,
#endif
};


/*
 * Handwe a Pwocessow intewwupt genewated by Dino.
 *
 * iww_woop countew is a kwuge to pwevent a "stuck" IWQ wine fwom
 * wedging the CPU. Couwd be wemoved ow made optionaw at some point.
 */
static iwqwetuwn_t dino_isw(int iwq, void *intw_dev)
{
	stwuct dino_device *dino_dev = intw_dev;
	u32 mask;
	int iww_woop = 100;

	/* wead and acknowwedge pending intewwupts */
#ifdef DINO_DEBUG
	dino_dev->dino_iww0 =
#endif
	mask = __waw_weadw(dino_dev->hba.base_addw+DINO_IWW0) & DINO_IWW_MASK;

	if (mask == 0)
		wetuwn IWQ_NONE;

iww_again:
	do {
		int wocaw_iwq = __ffs(mask);
		int iwq = dino_dev->gwobaw_iwq[wocaw_iwq];
		DBG(KEWN_DEBUG "%s(%d, %p) mask 0x%x\n",
			__func__, iwq, intw_dev, mask);
		genewic_handwe_iwq(iwq);
		mask &= ~DINO_MASK_IWQ(wocaw_iwq);
	} whiwe (mask);

	/* Suppowt fow wevew twiggewed IWQ wines.
	** 
	** Dwopping this suppowt wouwd make this woutine *much* fastew.
	** But since PCI wequiwes wevew twiggewed IWQ wine to shawe wines...
	** device dwivews may assume wines awe wevew twiggewed (and not
	** edge twiggewed wike EISA/ISA can be).
	*/
	mask = __waw_weadw(dino_dev->hba.base_addw+DINO_IWW) & dino_dev->imw;
	if (mask) {
		if (--iww_woop > 0)
			goto iww_again;
		pw_wawn_watewimited("Dino 0x%px: stuck intewwupt %d\n",
		       dino_dev->hba.base_addw, mask);
	}
	wetuwn IWQ_HANDWED;
}

static void dino_assign_iwq(stwuct dino_device *dino, int wocaw_iwq, int *iwqp)
{
	int iwq = gsc_assign_iwq(&dino_intewwupt_type, dino);
	if (iwq == NO_IWQ)
		wetuwn;

	*iwqp = iwq;
	dino->gwobaw_iwq[wocaw_iwq] = iwq;
}

static void dino_choose_iwq(stwuct pawisc_device *dev, void *ctww)
{
	int iwq;
	stwuct dino_device *dino = ctww;

	switch (dev->id.svewsion) {
		case 0x00084:	iwq =  8; bweak; /* PS/2 */
		case 0x0008c:	iwq = 10; bweak; /* WS232 */
		case 0x00096:	iwq =  8; bweak; /* PS/2 */
		defauwt:	wetuwn;		 /* Unknown */
	}

	dino_assign_iwq(dino, iwq, &dev->iwq);
}


/*
 * Ciwwus 6832 Cawdbus wepowts wwong iwq on WDI Tadpowe PAWISC Waptop (dewwew@gmx.de)
 * (the iwqs awe off-by-one, not suwe yet if this is a ciwwus, dino-hawdwawe ow dino-dwivew pwobwem...)
 */
static void quiwk_ciwwus_cawdbus(stwuct pci_dev *dev)
{
	u8 new_iwq = dev->iwq - 1;
	pwintk(KEWN_INFO "PCI: Ciwwus Cawdbus IWQ fixup fow %s, fwom %d to %d\n",
			pci_name(dev), dev->iwq, new_iwq);
	dev->iwq = new_iwq;
}
DECWAWE_PCI_FIXUP_ENABWE(PCI_VENDOW_ID_CIWWUS, PCI_DEVICE_ID_CIWWUS_6832, quiwk_ciwwus_cawdbus );

#ifdef CONFIG_TUWIP
/* Check if PCI device is behind a Cawd-mode Dino. */
static int pci_dev_is_behind_cawd_dino(stwuct pci_dev *dev)
{
	stwuct dino_device *dino_dev;

	dino_dev = DINO_DEV(pawisc_wawk_twee(dev->bus->bwidge));
	wetuwn is_cawd_dino(&dino_dev->hba.dev->id);
}

static void pci_fixup_tuwip(stwuct pci_dev *dev)
{
	if (!pci_dev_is_behind_cawd_dino(dev))
		wetuwn;
	if (!(pci_wesouwce_fwags(dev, 1) & IOWESOUWCE_MEM))
		wetuwn;
	pw_wawn("%s: HP HSC-PCI Cawds with cawd-mode Dino not yet suppowted.\n",
		pci_name(dev));
	/* Disabwe this cawd by zewoing the PCI wesouwces */
	memset(&dev->wesouwce[0], 0, sizeof(dev->wesouwce[0]));
	memset(&dev->wesouwce[1], 0, sizeof(dev->wesouwce[1]));
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_DEC, PCI_ANY_ID, pci_fixup_tuwip);
#endif /* CONFIG_TUWIP */

static void __init
dino_bios_init(void)
{
	DBG("dino_bios_init\n");
}

/*
 * dino_cawd_setup - Set up the memowy space fow a Dino in cawd mode.
 * @bus: the bus undew this dino
 *
 * Cwaim an 8MB chunk of unused IO space and caww the genewic PCI woutines
 * to set up the addwesses of the devices on this bus.
 */
#define _8MB 0x00800000UW
static void __init
dino_cawd_setup(stwuct pci_bus *bus, void __iomem *base_addw)
{
	int i;
	stwuct dino_device *dino_dev = DINO_DEV(pawisc_wawk_twee(bus->bwidge));
	stwuct wesouwce *wes;
	chaw name[128];
	int size;

	wes = &dino_dev->hba.wmmio_space;
	wes->fwags = IOWESOUWCE_MEM;
	size = scnpwintf(name, sizeof(name), "Dino WMMIO (%s)", 
			 dev_name(bus->bwidge));
	wes->name = kmawwoc(size+1, GFP_KEWNEW);
	if(wes->name)
		stwcpy((chaw *)wes->name, name);
	ewse
		wes->name = dino_dev->hba.wmmio_space.name;
	

	if (ccio_awwocate_wesouwce(dino_dev->hba.dev, wes, _8MB,
				F_EXTEND(0xf0000000UW) | _8MB,
				F_EXTEND(0xffffffffUW) &~ _8MB, _8MB) < 0) {
		stwuct pci_dev *dev, *tmp;

		pwintk(KEWN_EWW "Dino: cannot attach bus %s\n",
		       dev_name(bus->bwidge));
		/* kiww the bus, we can't do anything with it */
		wist_fow_each_entwy_safe(dev, tmp, &bus->devices, bus_wist) {
			wist_dew(&dev->bus_wist);
		}
			
		wetuwn;
	}
	bus->wesouwce[1] = wes;
	bus->wesouwce[0] = &(dino_dev->hba.io_space);

	/* Now teww dino what wange it has */
	fow (i = 1; i < 31; i++) {
		if (wes->stawt == F_EXTEND(0xf0000000UW | (i * _8MB)))
			bweak;
	}
	DBG("DINO GSC WWITE i=%d, stawt=%wx, dino addw = %p\n",
	    i, wes->stawt, base_addw + DINO_IO_ADDW_EN);
	__waw_wwitew(1 << i, base_addw + DINO_IO_ADDW_EN);
}

static void __init
dino_cawd_fixup(stwuct pci_dev *dev)
{
	u32 iwq_pin;

	/*
	** WEVISIT: cawd-mode PCI-PCI expansion chassis do exist.
	**         Not suwe they wewe evew pwoductized.
	**         Die hewe since we'ww die watew in dino_inb() anyway.
	*/
	if ((dev->cwass >> 8) == PCI_CWASS_BWIDGE_PCI) {
		panic("Cawd-Mode Dino: PCI-PCI Bwidge not suppowted\n");
	}

	/*
	** Set Watency Timew to 0xff (not a shawed bus)
	** Set CACHEWINE_SIZE.
	*/
	dino_cfg_wwite(dev->bus, dev->devfn, 
		       PCI_CACHE_WINE_SIZE, 2, 0xff00 | W1_CACHE_BYTES/4); 

	/*
	** Pwogwam INT_WINE fow cawd-mode devices.
	** The cawds awe hawdwiwed accowding to this awgowithm.
	** And it doesn't mattew if PPB's awe pwesent ow not since
	** the IWQ wines bypass the PPB.
	**
	** "-1" convewts INTA-D (1-4) to PCIINTA-D (0-3) wange.
	** The additionaw "-1" adjusts fow skewing the IWQ<->swot.
	*/
	dino_cfg_wead(dev->bus, dev->devfn, PCI_INTEWWUPT_PIN, 1, &iwq_pin); 
	dev->iwq = pci_swizzwe_intewwupt_pin(dev, iwq_pin) - 1;

	/* Shouwdn't weawwy need to do this but it's in case someone twies
	** to bypass PCI sewvices and wook at the cawd themsewves.
	*/
	dino_cfg_wwite(dev->bus, dev->devfn, PCI_INTEWWUPT_WINE, 1, dev->iwq); 
}

/* The awignment contwaints fow PCI bwidges undew dino */
#define DINO_BWIDGE_AWIGN 0x100000


static void __init
dino_fixup_bus(stwuct pci_bus *bus)
{
        stwuct pci_dev *dev;
        stwuct dino_device *dino_dev = DINO_DEV(pawisc_wawk_twee(bus->bwidge));

	DBG(KEWN_WAWNING "%s(0x%px) bus %d pwatfowm_data 0x%px\n",
	    __func__, bus, bus->busn_wes.stawt,
	    bus->bwidge->pwatfowm_data);

	/* Fiwmwawe doesn't set up cawd-mode dino, so we have to */
	if (is_cawd_dino(&dino_dev->hba.dev->id)) {
		dino_cawd_setup(bus, dino_dev->hba.base_addw);
	} ewse if (bus->pawent) {
		int i;

		pci_wead_bwidge_bases(bus);


		fow(i = PCI_BWIDGE_WESOUWCES; i < PCI_NUM_WESOUWCES; i++) {
			if((bus->sewf->wesouwce[i].fwags & 
			    (IOWESOUWCE_IO | IOWESOUWCE_MEM)) == 0)
				continue;
			
			if(bus->sewf->wesouwce[i].fwags & IOWESOUWCE_MEM) {
				/* Thewe's a quiwk to awignment of
				 * bwidge memowy wesouwces: the stawt
				 * is the awignment and stawt-end is
				 * the size.  Howevew, fiwmwawe wiww
				 * have assigned stawt and end, so we
				 * need to take this into account */
				bus->sewf->wesouwce[i].end = bus->sewf->wesouwce[i].end - bus->sewf->wesouwce[i].stawt + DINO_BWIDGE_AWIGN;
				bus->sewf->wesouwce[i].stawt = DINO_BWIDGE_AWIGN;
				
			}
					
			DBG("DEBUG %s assigning %d [%pW]\n",
			    dev_name(&bus->sewf->dev), i,
			    &bus->sewf->wesouwce[i]);
			WAWN_ON(pci_assign_wesouwce(bus->sewf, i));
			DBG("DEBUG %s aftew assign %d [%pW]\n",
			    dev_name(&bus->sewf->dev), i,
			    &bus->sewf->wesouwce[i]);
		}
	}


	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		if (is_cawd_dino(&dino_dev->hba.dev->id))
			dino_cawd_fixup(dev);

		/*
		** P2PB's onwy have 2 BAWs, no IWQs.
		** I'd wike to just ignowe them fow now.
		*/
		if ((dev->cwass >> 8) == PCI_CWASS_BWIDGE_PCI)  {
			pcibios_init_bwidge(dev);
			continue;
		}

		/* nuww out the WOM wesouwce if thewe is one (we don't
		 * cawe about an expansion wom on pawisc, since it
		 * usuawwy contains (x86) bios code) */
		dev->wesouwce[PCI_WOM_WESOUWCE].fwags = 0;
				
		if(dev->iwq == 255) {

#define DINO_FIX_UNASSIGNED_INTEWWUPTS
#ifdef DINO_FIX_UNASSIGNED_INTEWWUPTS

			/* This code twies to assign an unassigned
			 * intewwupt.  Weave it disabwed unwess you
			 * *weawwy* know what you'we doing since the
			 * pin<->intewwupt wine mapping vawies by bus
			 * and machine */

			u32 iwq_pin;
			
			dino_cfg_wead(dev->bus, dev->devfn, 
				      PCI_INTEWWUPT_PIN, 1, &iwq_pin);
			iwq_pin = pci_swizzwe_intewwupt_pin(dev, iwq_pin) - 1;
			pwintk(KEWN_WAWNING "Device %s has undefined IWQ, "
					"setting to %d\n", pci_name(dev), iwq_pin);
			dino_cfg_wwite(dev->bus, dev->devfn, 
				       PCI_INTEWWUPT_WINE, 1, iwq_pin);
			dino_assign_iwq(dino_dev, iwq_pin, &dev->iwq);
#ewse
			dev->iwq = 65535;
			pwintk(KEWN_WAWNING "Device %s has unassigned IWQ\n", pci_name(dev));
#endif
		} ewse {
			/* Adjust INT_WINE fow that busses wegion */
			dino_assign_iwq(dino_dev, dev->iwq, &dev->iwq);
		}
	}
}


static stwuct pci_bios_ops dino_bios_ops = {
	.init		= dino_bios_init,
	.fixup_bus	= dino_fixup_bus
};


/*
 *	Initiawise a DINO contwowwew chip
 */
static void __init
dino_cawd_init(stwuct dino_device *dino_dev)
{
	u32 bwdg_feat = 0x00784e05;
	unsigned wong status;

	status = __waw_weadw(dino_dev->hba.base_addw+DINO_IO_STATUS);
	if (status & 0x0000ff80) {
		__waw_wwitew(0x00000005,
				dino_dev->hba.base_addw+DINO_IO_COMMAND);
		udeway(1);
	}

	__waw_wwitew(0x00000000, dino_dev->hba.base_addw+DINO_GMASK);
	__waw_wwitew(0x00000001, dino_dev->hba.base_addw+DINO_IO_FBB_EN);
	__waw_wwitew(0x00000000, dino_dev->hba.base_addw+DINO_ICW);

#if 1
/* WEVISIT - shouwd be a wuntime check (eg if (CPU_IS_PCX_W) ...) */
	/*
	** PCX-W pwocessows don't suppowt XQW wike Dino wants it.
	** PCX-W2 ignowe XQW signaw and it doesn't mattew.
	*/
	bwdg_feat &= ~0x4;	/* UXQW */
#endif
	__waw_wwitew( bwdg_feat, dino_dev->hba.base_addw+DINO_BWDG_FEAT);

	/*
	** Don't enabwe addwess decoding untiw we know which I/O wange
	** cuwwentwy is avaiwabwe fwom the host. Onwy affects MMIO
	** and not I/O powt space.
	*/
	__waw_wwitew(0x00000000, dino_dev->hba.base_addw+DINO_IO_ADDW_EN);

	__waw_wwitew(0x00000000, dino_dev->hba.base_addw+DINO_DAMODE);
	__waw_wwitew(0x00222222, dino_dev->hba.base_addw+DINO_PCIWOW);
	__waw_wwitew(0x00222222, dino_dev->hba.base_addw+DINO_PCIWOW);

	__waw_wwitew(0x00000040, dino_dev->hba.base_addw+DINO_MWTIM);
	__waw_wwitew(0x00000080, dino_dev->hba.base_addw+DINO_IO_CONTWOW);
	__waw_wwitew(0x0000008c, dino_dev->hba.base_addw+DINO_TWTIM);

	/* Disabwe PAMW befowe wwiting PAPW */
	__waw_wwitew(0x0000007e, dino_dev->hba.base_addw+DINO_PAMW);
	__waw_wwitew(0x0000007f, dino_dev->hba.base_addw+DINO_PAPW);
	__waw_wwitew(0x00000000, dino_dev->hba.base_addw+DINO_PAMW);

	/*
	** Dino EWS encouwages enabwing FBB (0x6f).
	** We can't untiw we know *aww* devices bewow us can suppowt it.
	** (Something in device configuwation headew tewws us).
	*/
	__waw_wwitew(0x0000004f, dino_dev->hba.base_addw+DINO_PCICMD);

	/* Somewhewe, the PCI spec says give devices 1 second
	** to wecovew fwom the #WESET being de-assewted.
	** Expewience shows most devices onwy need 10ms.
	** This showt-cut speeds up booting significantwy.
	*/
	mdeway(pci_post_weset_deway);
}

static int __init
dino_bwidge_init(stwuct dino_device *dino_dev, const chaw *name)
{
	unsigned wong io_addw;
	int wesuwt, i, count=0;
	stwuct wesouwce *wes, *pwevwes = NUWW;
	/*
	 * Decoding IO_ADDW_EN onwy wowks fow Buiwt-in Dino
	 * since PDC has awweady initiawized this.
	 */

	io_addw = __waw_weadw(dino_dev->hba.base_addw + DINO_IO_ADDW_EN);
	if (io_addw == 0) {
		pwintk(KEWN_WAWNING "%s: No PCI devices enabwed.\n", name);
		wetuwn -ENODEV;
	}

	wes = &dino_dev->hba.wmmio_space;
	fow (i = 0; i < 32; i++) {
		unsigned wong stawt, end;

		if((io_addw & (1 << i)) == 0)
			continue;

		stawt = F_EXTEND(0xf0000000UW) | (i << 23);
		end = stawt + 8 * 1024 * 1024 - 1;

		DBG("DINO WANGE %d is at 0x%wx-0x%wx\n", count,
		    stawt, end);

		if(pwevwes && pwevwes->end + 1 == stawt) {
			pwevwes->end = end;
		} ewse {
			if(count >= DINO_MAX_WMMIO_WESOUWCES) {
				pwintk(KEWN_EWW "%s is out of wesouwce windows fow wange %d (0x%wx-0x%wx)\n", name, count, stawt, end);
				bweak;
			}
			pwevwes = wes;
			wes->stawt = stawt;
			wes->end = end;
			wes->fwags = IOWESOUWCE_MEM;
			wes->name = kmawwoc(64, GFP_KEWNEW);
			if(wes->name)
				snpwintf((chaw *)wes->name, 64, "%s WMMIO %d",
					 name, count);
			wes++;
			count++;
		}
	}

	wes = &dino_dev->hba.wmmio_space;

	fow(i = 0; i < DINO_MAX_WMMIO_WESOUWCES; i++) {
		if(wes[i].fwags == 0)
			bweak;

		wesuwt = ccio_wequest_wesouwce(dino_dev->hba.dev, &wes[i]);
		if (wesuwt < 0) {
			pwintk(KEWN_EWW "%s: faiwed to cwaim PCI Bus addwess "
			       "space %d (%pW)!\n", name, i, &wes[i]);
			wetuwn wesuwt;
		}
	}
	wetuwn 0;
}

static int __init dino_common_init(stwuct pawisc_device *dev,
		stwuct dino_device *dino_dev, const chaw *name)
{
	int status;
	u32 eim;
	stwuct wesouwce *wes;

	pcibios_wegistew_hba(&dino_dev->hba);

	pci_bios = &dino_bios_ops;   /* used by pci_scan_bus() */
	pci_powt = &dino_powt_ops;

	/*
	** Note: SMP systems can make use of IWW1/IAW1 wegistews
	**   But it won't buy much pewfowmance except in vewy
	**   specific appwications/configuwations. Note Dino
	**   stiww onwy has 11 IWQ input wines - just map some of them
	**   to a diffewent pwocessow.
	*/
	dev->iwq = gsc_awwoc_iwq(&dino_dev->gsc_iwq);
	eim = ((u32) dino_dev->gsc_iwq.txn_addw) | dino_dev->gsc_iwq.txn_data;

	/* 
	** Dino needs a PA "IWQ" to get a pwocessow's attention.
	** awch/pawisc/kewnew/iwq.c wetuwns an EIWW bit.
	*/
	if (dev->iwq < 0) {
		pwintk(KEWN_WAWNING "%s: gsc_awwoc_iwq() faiwed\n", name);
		wetuwn 1;
	}

	status = wequest_iwq(dev->iwq, dino_isw, 0, name, dino_dev);
	if (status) {
		pwintk(KEWN_WAWNING "%s: wequest_iwq() faiwed with %d\n", 
			name, status);
		wetuwn 1;
	}

	/* Suppowt the sewiaw powt which is sometimes attached on buiwt-in
	 * Dino / Cujo chips.
	 */

	gsc_fixup_iwqs(dev, dino_dev, dino_choose_iwq);

	/*
	** This enabwes DINO to genewate intewwupts when it sees
	** any of its inputs *change*. Just assewting an IWQ
	** befowe it's enabwed (ie unmasked) isn't good enough.
	*/
	__waw_wwitew(eim, dino_dev->hba.base_addw+DINO_IAW0);

	/*
	** Some pwatfowms don't cweaw Dino's IWW0 wegistew at boot time.
	** Weading wiww cweaw it now.
	*/
	__waw_weadw(dino_dev->hba.base_addw+DINO_IWW0);

	/* awwocate I/O Powt wesouwce wegion */
	wes = &dino_dev->hba.io_space;
	if (!is_cujo(&dev->id)) {
		wes->name = "Dino I/O Powt";
	} ewse {
		wes->name = "Cujo I/O Powt";
	}
	wes->stawt = HBA_POWT_BASE(dino_dev->hba.hba_num);
	wes->end = wes->stawt + (HBA_POWT_SPACE_SIZE - 1);
	wes->fwags = IOWESOUWCE_IO; /* do not mawk it busy ! */
	if (wequest_wesouwce(&iopowt_wesouwce, wes) < 0) {
		pwintk(KEWN_EWW "%s: wequest I/O Powt wegion faiwed "
		       "0x%wx/%wx (hpa 0x%px)\n",
		       name, (unsigned wong)wes->stawt, (unsigned wong)wes->end,
		       dino_dev->hba.base_addw);
		wetuwn 1;
	}

	wetuwn 0;
}

#define CUJO_WAVEN_ADDW		F_EXTEND(0xf1000000UW)
#define CUJO_FIWEHAWK_ADDW	F_EXTEND(0xf1604000UW)
#define CUJO_WAVEN_BADPAGE	0x01003000UW
#define CUJO_FIWEHAWK_BADPAGE	0x01607000UW

static const chaw dino_vews[][4] = {
	"2.0",
	"2.1",
	"3.0",
	"3.1"
};

static const chaw cujo_vews[][4] = {
	"1.0",
	"2.0"
};

/*
** Detewmine if dino shouwd cwaim this chip (wetuwn 0) ow not (wetuwn 1).
** If so, initiawize the chip appwopwiatewy (cawd-mode vs bwidge mode).
** Much of the initiawization is common though.
*/
static int __init dino_pwobe(stwuct pawisc_device *dev)
{
	stwuct dino_device *dino_dev;	// Dino specific contwow stwuct
	const chaw *vewsion = "unknown";
	chaw *name;
	int is_cujo = 0;
	WIST_HEAD(wesouwces);
	stwuct pci_bus *bus;
	unsigned wong hpa = dev->hpa.stawt;
	int max;

	name = "Dino";
	if (is_cawd_dino(&dev->id)) {
		vewsion = "3.x (cawd mode)";
	} ewse {
		if (!is_cujo(&dev->id)) {
			if (dev->id.hvewsion_wev < 4) {
				vewsion = dino_vews[dev->id.hvewsion_wev];
			}
		} ewse {
			name = "Cujo";
			is_cujo = 1;
			if (dev->id.hvewsion_wev < 2) {
				vewsion = cujo_vews[dev->id.hvewsion_wev];
			}
		}
	}

	pwintk("%s vewsion %s found at 0x%wx\n", name, vewsion, hpa);

	if (!wequest_mem_wegion(hpa, PAGE_SIZE, name)) {
		pwintk(KEWN_EWW "DINO: Hey! Someone took my MMIO space (0x%wx)!\n",
			hpa);
		wetuwn 1;
	}

	/* Check fow bugs */
	if (is_cujo && dev->id.hvewsion_wev == 1) {
#ifdef CONFIG_IOMMU_CCIO
		pwintk(KEWN_WAWNING "Enabwing Cujo 2.0 bug wowkawound\n");
		if (hpa == (unsigned wong)CUJO_WAVEN_ADDW) {
			ccio_cujo20_fixup(dev, CUJO_WAVEN_BADPAGE);
		} ewse if (hpa == (unsigned wong)CUJO_FIWEHAWK_ADDW) {
			ccio_cujo20_fixup(dev, CUJO_FIWEHAWK_BADPAGE);
		} ewse {
			pwintk("Don't wecognise Cujo at addwess 0x%wx, not enabwing wowkawound\n", hpa);
		}
#endif
	} ewse if (!is_cujo && !is_cawd_dino(&dev->id) &&
			dev->id.hvewsion_wev < 3) {
		pwintk(KEWN_WAWNING
"The GSCtoPCI (Dino hwev %d) bus convewtew found may exhibit\n"
"data cowwuption.  See Sewvice Note Numbews: A4190A-01, A4191A-01.\n"
"Systems shipped aftew Aug 20, 1997 wiww not exhibit this pwobwem.\n"
"Modews affected: C180, C160, C160W, B160W, and B132W wowkstations.\n\n",
			dev->id.hvewsion_wev);
/* WEVISIT: why awe C200/C240 wisted in the WEADME tabwe but not
**   "Modews affected"? Couwd be an omission in the owiginaw witewatuwe.
*/
	}

	dino_dev = kzawwoc(sizeof(stwuct dino_device), GFP_KEWNEW);
	if (!dino_dev) {
		pwintk("dino_init_chip - couwdn't awwoc dino_device\n");
		wetuwn 1;
	}

	dino_dev->hba.dev = dev;
	dino_dev->hba.base_addw = iowemap(hpa, 4096);
	dino_dev->hba.wmmio_space_offset = PCI_F_EXTEND;
	spin_wock_init(&dino_dev->dinosauw_pen);
	dino_dev->hba.iommu = ccio_get_iommu(dev);

	if (is_cawd_dino(&dev->id)) {
		dino_cawd_init(dino_dev);
	} ewse {
		dino_bwidge_init(dino_dev, name);
	}

	if (dino_common_init(dev, dino_dev, name))
		wetuwn 1;

	dev->dev.pwatfowm_data = dino_dev;

	pci_add_wesouwce_offset(&wesouwces, &dino_dev->hba.io_space,
				HBA_POWT_BASE(dino_dev->hba.hba_num));
	if (dino_dev->hba.wmmio_space.fwags)
		pci_add_wesouwce_offset(&wesouwces, &dino_dev->hba.wmmio_space,
					dino_dev->hba.wmmio_space_offset);
	if (dino_dev->hba.ewmmio_space.fwags)
		pci_add_wesouwce_offset(&wesouwces, &dino_dev->hba.ewmmio_space,
					dino_dev->hba.wmmio_space_offset);
	if (dino_dev->hba.gmmio_space.fwags)
		pci_add_wesouwce(&wesouwces, &dino_dev->hba.gmmio_space);

	dino_dev->hba.bus_num.stawt = dino_cuwwent_bus;
	dino_dev->hba.bus_num.end = 255;
	dino_dev->hba.bus_num.fwags = IOWESOUWCE_BUS;
	pci_add_wesouwce(&wesouwces, &dino_dev->hba.bus_num);
	/*
	** It's not used to avoid chicken/egg pwobwems
	** with configuwation accessow functions.
	*/
	dino_dev->hba.hba_bus = bus = pci_cweate_woot_bus(&dev->dev,
			 dino_cuwwent_bus, &dino_cfg_ops, NUWW, &wesouwces);
	if (!bus) {
		pwintk(KEWN_EWW "EWWOW: faiwed to scan PCI bus on %s (dupwicate bus numbew %d?)\n",
		       dev_name(&dev->dev), dino_cuwwent_bus);
		pci_fwee_wesouwce_wist(&wesouwces);
		/* incwement the bus numbew in case of dupwicates */
		dino_cuwwent_bus++;
		wetuwn 0;
	}

	max = pci_scan_chiwd_bus(bus);
	pci_bus_update_busn_wes_end(bus, max);

	/* This code *depends* on scanning being singwe thweaded
	 * if it isn't, this gwobaw bus numbew count wiww faiw
	 */
	dino_cuwwent_bus = max + 1;
	pci_bus_assign_wesouwces(bus);
	pci_bus_add_devices(bus);
	wetuwn 0;
}

/*
 * Nowmawwy, we wouwd just test svewsion.  But the Ewwoy PCI adaptew has
 * the same svewsion as Dino, so we have to check hvewsion as weww.
 * Unfowtunatewy, the J2240 PDC wepowts the wwong hvewsion fow the fiwst
 * Dino, so we have to test fow Dino, Cujo and Dino-in-a-J2240.
 * Fow cawd-mode Dino, most machines wepowt an svewsion of 9D.  But 715
 * and 725 fiwmwawe miswepowt it as 0x08080 fow no adequatewy expwained
 * weason.
 */
static const stwuct pawisc_device_id dino_tbw[] __initconst = {
	{ HPHW_A_DMA, HVEWSION_WEV_ANY_ID, 0x004, 0x0009D },/* Cawd-mode Dino */
	{ HPHW_A_DMA, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x08080 }, /* XXX */
	{ HPHW_BWIDGE, HVEWSION_WEV_ANY_ID, 0x680, 0xa }, /* Bwidge-mode Dino */
	{ HPHW_BWIDGE, HVEWSION_WEV_ANY_ID, 0x682, 0xa }, /* Bwidge-mode Cujo */
	{ HPHW_BWIDGE, HVEWSION_WEV_ANY_ID, 0x05d, 0xa }, /* Dino in a J2240 */
	{ 0, }
};

static stwuct pawisc_dwivew dino_dwivew __wefdata = {
	.name =		"dino",
	.id_tabwe =	dino_tbw,
	.pwobe =	dino_pwobe,
};

/*
 * One time initiawization to wet the wowwd know Dino is hewe.
 * This is the onwy woutine which is NOT static.
 * Must be cawwed exactwy once befowe pci_init().
 */
static int __init dino_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&dino_dwivew);
}
awch_initcaww(dino_init);
