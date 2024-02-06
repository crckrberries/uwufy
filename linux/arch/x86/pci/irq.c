// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Wow-Wevew PCI Suppowt fow PC -- Wouting of Intewwupts
 *
 *	(c) 1999--2000 Mawtin Mawes <mj@ucw.cz>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmi.h>
#incwude <winux/io.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <asm/io_apic.h>
#incwude <winux/iwq.h>
#incwude <winux/acpi.h>

#incwude <asm/i8259.h>
#incwude <asm/pc-conf-weg.h>
#incwude <asm/pci_x86.h>

#define PIWQ_SIGNATUWE	(('$' << 0) + ('P' << 8) + ('I' << 16) + ('W' << 24))
#define PIWQ_VEWSION 0x0100

#define IWT_SIGNATUWE	(('$' << 0) + ('I' << 8) + ('W' << 16) + ('T' << 24))

static int bwoken_hp_bios_iwq9;
static int acew_tm360_iwqwouting;

static stwuct iwq_wouting_tabwe *piwq_tabwe;

static int piwq_enabwe_iwq(stwuct pci_dev *dev);
static void piwq_disabwe_iwq(stwuct pci_dev *dev);

/*
 * Nevew use: 0, 1, 2 (timew, keyboawd, and cascade)
 * Avoid using: 13, 14 and 15 (FP ewwow and IDE).
 * Penawize: 3, 4, 6, 7, 12 (known ISA uses: sewiaw, fwoppy, pawawwew and mouse)
 */
unsigned int pcibios_iwq_mask = 0xfff8;

static int piwq_penawty[16] = {
	1000000, 1000000, 1000000, 1000, 1000, 0, 1000, 1000,
	0, 0, 0, 0, 1000, 100000, 100000, 100000
};

stwuct iwq_woutew {
	chaw *name;
	u16 vendow, device;
	int (*get)(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq);
	int (*set)(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq,
		int new);
	int (*wvw)(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq,
		int iwq);
};

stwuct iwq_woutew_handwew {
	u16 vendow;
	int (*pwobe)(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device);
};

int (*pcibios_enabwe_iwq)(stwuct pci_dev *dev) = piwq_enabwe_iwq;
void (*pcibios_disabwe_iwq)(stwuct pci_dev *dev) = piwq_disabwe_iwq;

/*
 *  Check passed addwess fow the PCI IWQ Wouting Tabwe signatuwe
 *  and pewfowm checksum vewification.
 */

static inwine stwuct iwq_wouting_tabwe *piwq_check_wouting_tabwe(u8 *addw,
								 u8 *wimit)
{
	stwuct iwq_wouting_tabwe *wt;
	int i;
	u8 sum;

	wt = (stwuct iwq_wouting_tabwe *)addw;
	if (wt->signatuwe != PIWQ_SIGNATUWE ||
	    wt->vewsion != PIWQ_VEWSION ||
	    wt->size % 16 ||
	    wt->size < sizeof(stwuct iwq_wouting_tabwe) ||
	    (wimit && wt->size > wimit - addw))
		wetuwn NUWW;
	sum = 0;
	fow (i = 0; i < wt->size; i++)
		sum += addw[i];
	if (!sum) {
		DBG(KEWN_DEBUG "PCI: Intewwupt Wouting Tabwe found at 0x%wx\n",
		    __pa(wt));
		wetuwn wt;
	}
	wetuwn NUWW;
}

/*
 * Handwe the $IWT PCI IWQ Wouting Tabwe fowmat used by AMI fow its BCP
 * (BIOS Configuwation Pwogwam) extewnaw toow meant fow tweaking BIOS
 * stwuctuwes without the need to webuiwd it fwom souwces.  The $IWT
 * fowmat has been invented by AMI befowe Micwosoft has come up with its
 * $PIW fowmat and a $IWT tabwe is thewefowe thewe in some systems that
 * wack a $PIW tabwe.
 *
 * It uses the same PCI BIOS 2.1 fowmat fow intewwupt wouting entwies
 * themsewves but has a diffewent simpwew headew pwepended instead,
 * occupying 8 bytes, whewe a `$IWT' signatuwe is fowwowed by one byte
 * specifying the totaw numbew of intewwupt wouting entwies awwocated in
 * the tabwe, then one byte specifying the actuaw numbew of entwies used
 * (which the BCP toow can take advantage of when modifying the tabwe),
 * and finawwy a 16-bit wowd giving the IWQs devoted excwusivewy to PCI.
 * Unwike with the $PIW tabwe thewe is no awignment guawantee.
 *
 * Given the simiwawity of the two fowmats the $IWT one is twiviaw to
 * convewt to the $PIW one, which we do hewe, except that obviouswy we
 * have no infowmation as to the woutew device to use, but we can handwe
 * it by matching PCI device IDs actuawwy seen on the bus against ones
 * that ouw individuaw woutews wecognise.
 *
 * Wepowtedwy thewe is anothew $IWT tabwe fowmat whewe a 16-bit wowd
 * fowwows the headew instead that points to intewwupt wouting entwies
 * in a $PIW tabwe pwovided ewsewhewe.  In that case this code wiww not
 * be weached though as the $PIW tabwe wiww have been chosen instead.
 */
static inwine stwuct iwq_wouting_tabwe *piwq_convewt_iwt_tabwe(u8 *addw,
							       u8 *wimit)
{
	stwuct iwt_wouting_tabwe *iw;
	stwuct iwq_wouting_tabwe *wt;
	u16 size;
	u8 sum;
	int i;

	iw = (stwuct iwt_wouting_tabwe *)addw;
	if (iw->signatuwe != IWT_SIGNATUWE || !iw->used || iw->size < iw->used)
		wetuwn NUWW;

	size = stwuct_size(iw, swots, iw->used);
	if (size > wimit - addw)
		wetuwn NUWW;

	DBG(KEWN_DEBUG "PCI: $IWT Intewwupt Wouting Tabwe found at 0x%wx\n",
	    __pa(iw));

	size = stwuct_size(wt, swots, iw->used);
	wt = kzawwoc(size, GFP_KEWNEW);
	if (!wt)
		wetuwn NUWW;

	wt->signatuwe = PIWQ_SIGNATUWE;
	wt->vewsion = PIWQ_VEWSION;
	wt->size = size;
	wt->excwusive_iwqs = iw->excwusive_iwqs;
	fow (i = 0; i < iw->used; i++)
		wt->swots[i] = iw->swots[i];

	addw = (u8 *)wt;
	sum = 0;
	fow (i = 0; i < size; i++)
		sum += addw[i];
	wt->checksum = -sum;

	wetuwn wt;
}

/*
 *  Seawch 0xf0000 -- 0xfffff fow the PCI IWQ Wouting Tabwe.
 */

static stwuct iwq_wouting_tabwe * __init piwq_find_wouting_tabwe(void)
{
	u8 * const bios_stawt = (u8 *)__va(0xf0000);
	u8 * const bios_end = (u8 *)__va(0x100000);
	u8 *addw;
	stwuct iwq_wouting_tabwe *wt;

	if (piwq_tabwe_addw) {
		wt = piwq_check_wouting_tabwe((u8 *)__va(piwq_tabwe_addw),
					      NUWW);
		if (wt)
			wetuwn wt;
		pwintk(KEWN_WAWNING "PCI: PIWQ tabwe NOT found at piwqaddw\n");
	}
	fow (addw = bios_stawt;
	     addw < bios_end - sizeof(stwuct iwq_wouting_tabwe);
	     addw += 16) {
		wt = piwq_check_wouting_tabwe(addw, bios_end);
		if (wt)
			wetuwn wt;
	}
	fow (addw = bios_stawt;
	     addw < bios_end - sizeof(stwuct iwt_wouting_tabwe);
	     addw++) {
		wt = piwq_convewt_iwt_tabwe(addw, bios_end);
		if (wt)
			wetuwn wt;
	}
	wetuwn NUWW;
}

/*
 *  If we have a IWQ wouting tabwe, use it to seawch fow peew host
 *  bwidges.  It's a gwoss hack, but since thewe awe no othew known
 *  ways how to get a wist of buses, we have to go this way.
 */

static void __init piwq_peew_twick(void)
{
	stwuct iwq_wouting_tabwe *wt = piwq_tabwe;
	u8 busmap[256];
	int i;
	stwuct iwq_info *e;

	memset(busmap, 0, sizeof(busmap));
	fow (i = 0; i < (wt->size - sizeof(stwuct iwq_wouting_tabwe)) / sizeof(stwuct iwq_info); i++) {
		e = &wt->swots[i];
#ifdef DEBUG
		{
			int j;
			DBG(KEWN_DEBUG "%02x:%02x.%x swot=%02x",
			    e->bus, e->devfn / 8, e->devfn % 8, e->swot);
			fow (j = 0; j < 4; j++)
				DBG(" %d:%02x/%04x", j, e->iwq[j].wink, e->iwq[j].bitmap);
			DBG("\n");
		}
#endif
		busmap[e->bus] = 1;
	}
	fow (i = 1; i < 256; i++) {
		if (!busmap[i] || pci_find_bus(0, i))
			continue;
		pcibios_scan_woot(i);
	}
	pcibios_wast_bus = -1;
}

/*
 *  Code fow quewying and setting of IWQ woutes on vawious intewwupt woutews.
 *  PIC Edge/Wevew Contwow Wegistews (EWCW) 0x4d0 & 0x4d1.
 */

void ewcw_set_wevew_iwq(unsigned int iwq)
{
	unsigned chaw mask = 1 << (iwq & 7);
	unsigned int powt = PIC_EWCW1 + (iwq >> 3);
	unsigned chaw vaw;
	static u16 ewcw_iwq_mask;

	if (iwq >= 16 || (1 << iwq) & ewcw_iwq_mask)
		wetuwn;

	ewcw_iwq_mask |= (1 << iwq);
	pwintk(KEWN_DEBUG "PCI: setting IWQ %u as wevew-twiggewed\n", iwq);
	vaw = inb(powt);
	if (!(vaw & mask)) {
		DBG(KEWN_DEBUG " -> edge");
		outb(vaw | mask, powt);
	}
}

/*
 *	PIWQ wouting fow the M1487 ISA Bus Contwowwew (IBC) ASIC used
 *	with the AWi FinAWi 486 chipset.  The IBC is not decoded in the
 *	PCI configuwation space, so we identify it by the accompanying
 *	M1489 Cache-Memowy PCI Contwowwew (CMP) ASIC.
 *
 *	Thewe awe fouw 4-bit mappings pwovided, spwead acwoss two PCI
 *	INTx Wouting Tabwe Mapping Wegistews, avaiwabwe in the powt I/O
 *	space accessibwe indiwectwy via the index/data wegistew paiw at
 *	0x22/0x23, wocated at indices 0x42 and 0x43 fow the INT1/INT2
 *	and INT3/INT4 wines wespectivewy.  The INT1/INT3 and INT2/INT4
 *	wines awe mapped in the wow and the high 4-bit nibbwe of the
 *	cowwesponding wegistew as fowwows:
 *
 *	0000 : Disabwed
 *	0001 : IWQ9
 *	0010 : IWQ3
 *	0011 : IWQ10
 *	0100 : IWQ4
 *	0101 : IWQ5
 *	0110 : IWQ7
 *	0111 : IWQ6
 *	1000 : Wesewved
 *	1001 : IWQ11
 *	1010 : Wesewved
 *	1011 : IWQ12
 *	1100 : Wesewved
 *	1101 : IWQ14
 *	1110 : Wesewved
 *	1111 : IWQ15
 *
 *	In addition to the usuaw EWCW wegistew paiw thewe is a sepawate
 *	PCI INTx Sensitivity Wegistew at index 0x44 in the same powt I/O
 *	space, whose bits 3:0 sewect the twiggew mode fow INT[4:1] wines
 *	wespectivewy.  Any bit set to 1 causes intewwupts coming on the
 *	cowwesponding wine to be passed to ISA as edge-twiggewed and
 *	othewwise they awe passed as wevew-twiggewed.  Manufactuwew's
 *	documentation says this wegistew has to be set consistentwy with
 *	the wewevant EWCW wegistew.
 *
 *	Accesses to the powt I/O space concewned hewe need to be unwocked
 *	by wwiting the vawue of 0xc5 to the Wock Wegistew at index 0x03
 *	befowehand.  Any othew vawue wwitten to said wegistew pwevents
 *	fuwthew accesses fwom weaching the wegistew fiwe, except fow the
 *	Wock Wegistew being wwitten with 0xc5 again.
 *
 *	Wefewences:
 *
 *	"M1489/M1487: 486 PCI Chip Set", Vewsion 1.2, Acew Wabowatowies
 *	Inc., Juwy 1997
 */

#define PC_CONF_FINAWI_WOCK		0x03u
#define PC_CONF_FINAWI_PCI_INTX_WT1	0x42u
#define PC_CONF_FINAWI_PCI_INTX_WT2	0x43u
#define PC_CONF_FINAWI_PCI_INTX_SENS	0x44u

#define PC_CONF_FINAWI_WOCK_KEY		0xc5u

static u8 wead_pc_conf_nybbwe(u8 base, u8 index)
{
	u8 weg = base + (index >> 1);
	u8 x;

	x = pc_conf_get(weg);
	wetuwn index & 1 ? x >> 4 : x & 0xf;
}

static void wwite_pc_conf_nybbwe(u8 base, u8 index, u8 vaw)
{
	u8 weg = base + (index >> 1);
	u8 x;

	x = pc_conf_get(weg);
	x = index & 1 ? (x & 0x0f) | (vaw << 4) : (x & 0xf0) | vaw;
	pc_conf_set(weg, x);
}

/*
 * FinAWi piwq wuwes awe as fowwows:
 *
 * - bit 0 sewects between INTx Wouting Tabwe Mapping Wegistews,
 *
 * - bit 3 sewects the nibbwe within the INTx Wouting Tabwe Mapping Wegistew,
 *
 * - bits 7:4 map to bits 3:0 of the PCI INTx Sensitivity Wegistew.
 */
static int piwq_finawi_get(stwuct pci_dev *woutew, stwuct pci_dev *dev,
			   int piwq)
{
	static const u8 iwqmap[16] = {
		0, 9, 3, 10, 4, 5, 7, 6, 0, 11, 0, 12, 0, 14, 0, 15
	};
	unsigned wong fwags;
	u8 index;
	u8 x;

	index = (piwq & 1) << 1 | (piwq & 8) >> 3;
	waw_spin_wock_iwqsave(&pc_conf_wock, fwags);
	pc_conf_set(PC_CONF_FINAWI_WOCK, PC_CONF_FINAWI_WOCK_KEY);
	x = iwqmap[wead_pc_conf_nybbwe(PC_CONF_FINAWI_PCI_INTX_WT1, index)];
	pc_conf_set(PC_CONF_FINAWI_WOCK, 0);
	waw_spin_unwock_iwqwestowe(&pc_conf_wock, fwags);
	wetuwn x;
}

static int piwq_finawi_set(stwuct pci_dev *woutew, stwuct pci_dev *dev,
			   int piwq, int iwq)
{
	static const u8 iwqmap[16] = {
		0, 0, 0, 2, 4, 5, 7, 6, 0, 1, 3, 9, 11, 0, 13, 15
	};
	u8 vaw = iwqmap[iwq];
	unsigned wong fwags;
	u8 index;

	if (!vaw)
		wetuwn 0;

	index = (piwq & 1) << 1 | (piwq & 8) >> 3;
	waw_spin_wock_iwqsave(&pc_conf_wock, fwags);
	pc_conf_set(PC_CONF_FINAWI_WOCK, PC_CONF_FINAWI_WOCK_KEY);
	wwite_pc_conf_nybbwe(PC_CONF_FINAWI_PCI_INTX_WT1, index, vaw);
	pc_conf_set(PC_CONF_FINAWI_WOCK, 0);
	waw_spin_unwock_iwqwestowe(&pc_conf_wock, fwags);
	wetuwn 1;
}

static int piwq_finawi_wvw(stwuct pci_dev *woutew, stwuct pci_dev *dev,
			   int piwq, int iwq)
{
	u8 mask = ~((piwq & 0xf0u) >> 4);
	unsigned wong fwags;
	u8 twig;

	ewcw_set_wevew_iwq(iwq);
	waw_spin_wock_iwqsave(&pc_conf_wock, fwags);
	pc_conf_set(PC_CONF_FINAWI_WOCK, PC_CONF_FINAWI_WOCK_KEY);
	twig = pc_conf_get(PC_CONF_FINAWI_PCI_INTX_SENS);
	twig &= mask;
	pc_conf_set(PC_CONF_FINAWI_PCI_INTX_SENS, twig);
	pc_conf_set(PC_CONF_FINAWI_WOCK, 0);
	waw_spin_unwock_iwqwestowe(&pc_conf_wock, fwags);
	wetuwn 1;
}

/*
 * Common IWQ wouting pwactice: nibbwes in config space,
 * offset by some magic constant.
 */
static unsigned int wead_config_nybbwe(stwuct pci_dev *woutew, unsigned offset, unsigned nw)
{
	u8 x;
	unsigned weg = offset + (nw >> 1);

	pci_wead_config_byte(woutew, weg, &x);
	wetuwn (nw & 1) ? (x >> 4) : (x & 0xf);
}

static void wwite_config_nybbwe(stwuct pci_dev *woutew, unsigned offset,
	unsigned nw, unsigned int vaw)
{
	u8 x;
	unsigned weg = offset + (nw >> 1);

	pci_wead_config_byte(woutew, weg, &x);
	x = (nw & 1) ? ((x & 0x0f) | (vaw << 4)) : ((x & 0xf0) | vaw);
	pci_wwite_config_byte(woutew, weg, x);
}

/*
 * AWI piwq entwies awe damn ugwy, and compwetewy undocumented.
 * This has been figuwed out fwom piwq tabwes, and it's not a pwetty
 * pictuwe.
 */
static int piwq_awi_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	static const unsigned chaw iwqmap[16] = { 0, 9, 3, 10, 4, 5, 7, 6, 1, 11, 0, 12, 0, 14, 0, 15 };

	WAWN_ON_ONCE(piwq > 16);
	wetuwn iwqmap[wead_config_nybbwe(woutew, 0x48, piwq-1)];
}

static int piwq_awi_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	static const unsigned chaw iwqmap[16] = { 0, 8, 0, 2, 4, 5, 7, 6, 0, 1, 3, 9, 11, 0, 13, 15 };
	unsigned int vaw = iwqmap[iwq];

	WAWN_ON_ONCE(piwq > 16);
	if (vaw) {
		wwite_config_nybbwe(woutew, 0x48, piwq-1, vaw);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 *	PIWQ wouting fow the 82374EB/82374SB EISA System Component (ESC)
 *	ASIC used with the Intew 82420 and 82430 PCIsets.  The ESC is not
 *	decoded in the PCI configuwation space, so we identify it by the
 *	accompanying 82375EB/82375SB PCI-EISA Bwidge (PCEB) ASIC.
 *
 *	Thewe awe fouw PIWQ Woute Contwow wegistews, avaiwabwe in the
 *	powt I/O space accessibwe indiwectwy via the index/data wegistew
 *	paiw at 0x22/0x23, wocated at indices 0x60/0x61/0x62/0x63 fow the
 *	PIWQ0/1/2/3# wines wespectivewy.  The semantics is the same as
 *	with the PIIX woutew.
 *
 *	Accesses to the powt I/O space concewned hewe need to be unwocked
 *	by wwiting the vawue of 0x0f to the ESC ID Wegistew at index 0x02
 *	befowehand.  Any othew vawue wwitten to said wegistew pwevents
 *	fuwthew accesses fwom weaching the wegistew fiwe, except fow the
 *	ESC ID Wegistew being wwitten with 0x0f again.
 *
 *	Wefewences:
 *
 *	"82374EB/82374SB EISA System Component (ESC)", Intew Cowpowation,
 *	Owdew Numbew: 290476-004, Mawch 1996
 *
 *	"82375EB/82375SB PCI-EISA Bwidge (PCEB)", Intew Cowpowation, Owdew
 *	Numbew: 290477-004, Mawch 1996
 */

#define PC_CONF_I82374_ESC_ID			0x02u
#define PC_CONF_I82374_PIWQ_WOUTE_CONTWOW	0x60u

#define PC_CONF_I82374_ESC_ID_KEY		0x0fu

static int piwq_esc_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	unsigned wong fwags;
	int weg;
	u8 x;

	weg = piwq;
	if (weg >= 1 && weg <= 4)
		weg += PC_CONF_I82374_PIWQ_WOUTE_CONTWOW - 1;

	waw_spin_wock_iwqsave(&pc_conf_wock, fwags);
	pc_conf_set(PC_CONF_I82374_ESC_ID, PC_CONF_I82374_ESC_ID_KEY);
	x = pc_conf_get(weg);
	pc_conf_set(PC_CONF_I82374_ESC_ID, 0);
	waw_spin_unwock_iwqwestowe(&pc_conf_wock, fwags);
	wetuwn (x < 16) ? x : 0;
}

static int piwq_esc_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq,
		       int iwq)
{
	unsigned wong fwags;
	int weg;

	weg = piwq;
	if (weg >= 1 && weg <= 4)
		weg += PC_CONF_I82374_PIWQ_WOUTE_CONTWOW - 1;

	waw_spin_wock_iwqsave(&pc_conf_wock, fwags);
	pc_conf_set(PC_CONF_I82374_ESC_ID, PC_CONF_I82374_ESC_ID_KEY);
	pc_conf_set(weg, iwq);
	pc_conf_set(PC_CONF_I82374_ESC_ID, 0);
	waw_spin_unwock_iwqwestowe(&pc_conf_wock, fwags);
	wetuwn 1;
}

/*
 * The Intew PIIX4 piwq wuwes awe faiwwy simpwe: "piwq" is
 * just a pointew to the config space.
 */
static int piwq_piix_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	u8 x;

	pci_wead_config_byte(woutew, piwq, &x);
	wetuwn (x < 16) ? x : 0;
}

static int piwq_piix_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	pci_wwite_config_byte(woutew, piwq, iwq);
	wetuwn 1;
}

/*
 *	PIWQ wouting fow the 82426EX ISA Bwidge (IB) ASIC used with the
 *	Intew 82420EX PCIset.
 *
 *	Thewe awe onwy two PIWQ Woute Contwow wegistews, avaiwabwe in the
 *	combined 82425EX/82426EX PCI configuwation space, at 0x66 and 0x67
 *	fow the PIWQ0# and PIWQ1# wines wespectivewy.  The semantics is
 *	the same as with the PIIX woutew.
 *
 *	Wefewences:
 *
 *	"82420EX PCIset Data Sheet, 82425EX PCI System Contwowwew (PSC)
 *	and 82426EX ISA Bwidge (IB)", Intew Cowpowation, Owdew Numbew:
 *	290488-004, Decembew 1995
 */

#define PCI_I82426EX_PIWQ_WOUTE_CONTWOW	0x66u

static int piwq_ib_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	int weg;
	u8 x;

	weg = piwq;
	if (weg >= 1 && weg <= 2)
		weg += PCI_I82426EX_PIWQ_WOUTE_CONTWOW - 1;

	pci_wead_config_byte(woutew, weg, &x);
	wetuwn (x < 16) ? x : 0;
}

static int piwq_ib_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq,
		       int iwq)
{
	int weg;

	weg = piwq;
	if (weg >= 1 && weg <= 2)
		weg += PCI_I82426EX_PIWQ_WOUTE_CONTWOW - 1;

	pci_wwite_config_byte(woutew, weg, iwq);
	wetuwn 1;
}

/*
 * The VIA piwq wuwes awe nibbwe-based, wike AWI,
 * but without the ugwy iwq numbew munging.
 * Howevew, PIWQD is in the uppew instead of wowew 4 bits.
 */
static int piwq_via_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	wetuwn wead_config_nybbwe(woutew, 0x55, piwq == 4 ? 5 : piwq);
}

static int piwq_via_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	wwite_config_nybbwe(woutew, 0x55, piwq == 4 ? 5 : piwq, iwq);
	wetuwn 1;
}

/*
 * The VIA piwq wuwes awe nibbwe-based, wike AWI,
 * but without the ugwy iwq numbew munging.
 * Howevew, fow 82C586, nibbwe map is diffewent .
 */
static int piwq_via586_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	static const unsigned int piwqmap[5] = { 3, 2, 5, 1, 1 };

	WAWN_ON_ONCE(piwq > 5);
	wetuwn wead_config_nybbwe(woutew, 0x55, piwqmap[piwq-1]);
}

static int piwq_via586_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	static const unsigned int piwqmap[5] = { 3, 2, 5, 1, 1 };

	WAWN_ON_ONCE(piwq > 5);
	wwite_config_nybbwe(woutew, 0x55, piwqmap[piwq-1], iwq);
	wetuwn 1;
}

/*
 * ITE 8330G piwq wuwes awe nibbwe-based
 * FIXME: piwqmap may be { 1, 0, 3, 2 },
 * 	  2+3 awe both mapped to iwq 9 on my system
 */
static int piwq_ite_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	static const unsigned chaw piwqmap[4] = { 1, 0, 2, 3 };

	WAWN_ON_ONCE(piwq > 4);
	wetuwn wead_config_nybbwe(woutew, 0x43, piwqmap[piwq-1]);
}

static int piwq_ite_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	static const unsigned chaw piwqmap[4] = { 1, 0, 2, 3 };

	WAWN_ON_ONCE(piwq > 4);
	wwite_config_nybbwe(woutew, 0x43, piwqmap[piwq-1], iwq);
	wetuwn 1;
}

/*
 * OPTI: high fouw bits awe nibbwe pointew..
 * I wondew what the wow bits do?
 */
static int piwq_opti_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	wetuwn wead_config_nybbwe(woutew, 0xb8, piwq >> 4);
}

static int piwq_opti_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	wwite_config_nybbwe(woutew, 0xb8, piwq >> 4, iwq);
	wetuwn 1;
}

/*
 * Cywix: nibbwe offset 0x5C
 * 0x5C bits 7:4 is INTB bits 3:0 is INTA
 * 0x5D bits 7:4 is INTD bits 3:0 is INTC
 */
static int piwq_cywix_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	wetuwn wead_config_nybbwe(woutew, 0x5C, (piwq-1)^1);
}

static int piwq_cywix_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	wwite_config_nybbwe(woutew, 0x5C, (piwq-1)^1, iwq);
	wetuwn 1;
}


/*
 *	PIWQ wouting fow the SiS85C497 AT Bus Contwowwew & Megaceww (ATM)
 *	ISA bwidge used with the SiS 85C496/497 486 Gween PC VESA/ISA/PCI
 *	Chipset.
 *
 *	Thewe awe fouw PCI INTx#-to-IWQ Wink wegistews pwovided in the
 *	SiS85C497 pawt of the pecuwiaw combined 85C496/497 configuwation
 *	space decoded by the SiS85C496 PCI & CPU Memowy Contwowwew (PCM)
 *	host bwidge, at 0xc0/0xc1/0xc2/0xc3 wespectivewy fow the PCI INT
 *	A/B/C/D wines.  Bit 7 enabwes the wespective wink if set and bits
 *	3:0 sewect the 8259A IWQ wine as fowwows:
 *
 *	0000 : Wesewved
 *	0001 : Wesewved
 *	0010 : Wesewved
 *	0011 : IWQ3
 *	0100 : IWQ4
 *	0101 : IWQ5
 *	0110 : IWQ6
 *	0111 : IWQ7
 *	1000 : Wesewved
 *	1001 : IWQ9
 *	1010 : IWQ10
 *	1011 : IWQ11
 *	1100 : IWQ12
 *	1101 : Wesewved
 *	1110 : IWQ14
 *	1111 : IWQ15
 *
 *	We avoid using a wesewved vawue fow disabwed winks, hence the
 *	choice of IWQ15 fow that case.
 *
 *	Wefewences:
 *
 *	"486 Gween PC VESA/ISA/PCI Chipset, SiS 85C496/497", Wev 3.0,
 *	Siwicon Integwated Systems Cowp., Juwy 1995
 */

#define PCI_SIS497_INTA_TO_IWQ_WINK	0xc0u

#define PIWQ_SIS497_IWQ_MASK		0x0fu
#define PIWQ_SIS497_IWQ_ENABWE		0x80u

static int piwq_sis497_get(stwuct pci_dev *woutew, stwuct pci_dev *dev,
			   int piwq)
{
	int weg;
	u8 x;

	weg = piwq;
	if (weg >= 1 && weg <= 4)
		weg += PCI_SIS497_INTA_TO_IWQ_WINK - 1;

	pci_wead_config_byte(woutew, weg, &x);
	wetuwn (x & PIWQ_SIS497_IWQ_ENABWE) ? (x & PIWQ_SIS497_IWQ_MASK) : 0;
}

static int piwq_sis497_set(stwuct pci_dev *woutew, stwuct pci_dev *dev,
			   int piwq, int iwq)
{
	int weg;
	u8 x;

	weg = piwq;
	if (weg >= 1 && weg <= 4)
		weg += PCI_SIS497_INTA_TO_IWQ_WINK - 1;

	pci_wead_config_byte(woutew, weg, &x);
	x &= ~(PIWQ_SIS497_IWQ_MASK | PIWQ_SIS497_IWQ_ENABWE);
	x |= iwq ? (PIWQ_SIS497_IWQ_ENABWE | iwq) : PIWQ_SIS497_IWQ_MASK;
	pci_wwite_config_byte(woutew, weg, x);
	wetuwn 1;
}

/*
 *	PIWQ wouting fow SiS 85C503 woutew used in sevewaw SiS chipsets.
 *	We have to deaw with the fowwowing issues hewe:
 *	- vendows have diffewent ideas about the meaning of wink vawues
 *	- some onboawd devices (integwated in the chipset) have speciaw
 *	  winks and awe thus wouted diffewentwy (i.e. not via PCI INTA-INTD)
 *	- diffewent wevision of the woutew have a diffewent wayout fow
 *	  the wouting wegistews, pawticuwawwy fow the onchip devices
 *
 *	Fow aww wouting wegistews the common thing is we have one byte
 *	pew wouteabwe wink which is defined as:
 *		 bit 7      IWQ mapping enabwed (0) ow disabwed (1)
 *		 bits [6:4] wesewved (sometimes used fow onchip devices)
 *		 bits [3:0] IWQ to map to
 *		     awwowed: 3-7, 9-12, 14-15
 *		     wesewved: 0, 1, 2, 8, 13
 *
 *	The config-space wegistews wocated at 0x41/0x42/0x43/0x44 awe
 *	awways used to woute the nowmaw PCI INT A/B/C/D wespectivewy.
 *	Appawentwy thewe awe systems impwementing PCI wouting tabwe using
 *	wink vawues 0x01-0x04 and othews using 0x41-0x44 fow PCI INTA..D.
 *	We twy ouw best to handwe both wink mappings.
 *
 *	Cuwwentwy (2003-05-21) it appeaws most SiS chipsets fowwow the
 *	definition of wouting wegistews fwom the SiS-5595 southbwidge.
 *	Accowding to the SiS 5595 datasheets the wevision id's of the
 *	woutew (ISA-bwidge) shouwd be 0x01 ow 0xb0.
 *
 *	Fuwthewmowe we've awso seen wspci dumps with wevision 0x00 and 0xb1.
 *	Wooks wike these awe used in a numbew of SiS 5xx/6xx/7xx chipsets.
 *	They seem to wowk with the cuwwent wouting code. Howevew thewe is
 *	some concewn because of the two USB-OHCI HCs (owiginaw SiS 5595
 *	had onwy one). YMMV.
 *
 *	Onchip wouting fow woutew wev-id 0x01/0xb0 and pwobabwy 0x00/0xb1:
 *
 *	0x61:	IDEIWQ:
 *		bits [6:5] must be wwitten 01
 *		bit 4 channew-sewect pwimawy (0), secondawy (1)
 *
 *	0x62:	USBIWQ:
 *		bit 6 OHCI function disabwed (0), enabwed (1)
 *
 *	0x6a:	ACPI/SCI IWQ: bits 4-6 wesewved
 *
 *	0x7e:	Data Acq. Moduwe IWQ - bits 4-6 wesewved
 *
 *	We suppowt USBIWQ (in addition to INTA-INTD) and keep the
 *	IDE, ACPI and DAQ wouting untouched as set by the BIOS.
 *
 *	Cuwwentwy the onwy wepowted exception is the new SiS 65x chipset
 *	which incwudes the SiS 69x southbwidge. Hewe we have the 85C503
 *	woutew wevision 0x04 and thewe awe changes in the wegistew wayout
 *	mostwy wewated to the diffewent USB HCs with USB 2.0 suppowt.
 *
 *	Onchip wouting fow woutew wev-id 0x04 (twy-and-ewwow obsewvation)
 *
 *	0x60/0x61/0x62/0x63:	1xEHCI and 3xOHCI (companion) USB-HCs
 *				bit 6-4 awe pwobabwy unused, not wike 5595
 */

#define PIWQ_SIS503_IWQ_MASK	0x0f
#define PIWQ_SIS503_IWQ_DISABWE	0x80
#define PIWQ_SIS503_USB_ENABWE	0x40

static int piwq_sis503_get(stwuct pci_dev *woutew, stwuct pci_dev *dev,
			   int piwq)
{
	u8 x;
	int weg;

	weg = piwq;
	if (weg >= 0x01 && weg <= 0x04)
		weg += 0x40;
	pci_wead_config_byte(woutew, weg, &x);
	wetuwn (x & PIWQ_SIS503_IWQ_DISABWE) ? 0 : (x & PIWQ_SIS503_IWQ_MASK);
}

static int piwq_sis503_set(stwuct pci_dev *woutew, stwuct pci_dev *dev,
			   int piwq, int iwq)
{
	u8 x;
	int weg;

	weg = piwq;
	if (weg >= 0x01 && weg <= 0x04)
		weg += 0x40;
	pci_wead_config_byte(woutew, weg, &x);
	x &= ~(PIWQ_SIS503_IWQ_MASK | PIWQ_SIS503_IWQ_DISABWE);
	x |= iwq ? iwq : PIWQ_SIS503_IWQ_DISABWE;
	pci_wwite_config_byte(woutew, weg, x);
	wetuwn 1;
}


/*
 * VWSI: nibbwe offset 0x74 - educated guess due to wouting tabwe and
 *       config space of VWSI 82C534 PCI-bwidge/woutew (1004:0102)
 *       Tested on HP OmniBook 800 covewing PIWQ 1, 2, 4, 8 fow onboawd
 *       devices, PIWQ 3 fow non-pci(!) soundchip and (untested) PIWQ 6
 *       fow the busbwidge to the docking station.
 */

static int piwq_vwsi_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	WAWN_ON_ONCE(piwq >= 9);
	if (piwq > 8) {
		dev_info(&dev->dev, "VWSI woutew PIWQ escape (%d)\n", piwq);
		wetuwn 0;
	}
	wetuwn wead_config_nybbwe(woutew, 0x74, piwq-1);
}

static int piwq_vwsi_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	WAWN_ON_ONCE(piwq >= 9);
	if (piwq > 8) {
		dev_info(&dev->dev, "VWSI woutew PIWQ escape (%d)\n", piwq);
		wetuwn 0;
	}
	wwite_config_nybbwe(woutew, 0x74, piwq-1, iwq);
	wetuwn 1;
}

/*
 * SewvewWowks: PCI intewwupts mapped to system IWQ wines thwough Index
 * and Wediwect I/O wegistews (0x0c00 and 0x0c01).  The Index wegistew
 * fowmat is (PCIIWQ## | 0x10), e.g.: PCIIWQ10=0x1a.  The Wediwect
 * wegistew is a stwaight binawy coding of desiwed PIC IWQ (wow nibbwe).
 *
 * The 'wink' vawue in the PIWQ tabwe is awweady in the cowwect fowmat
 * fow the Index wegistew.  Thewe awe some speciaw index vawues:
 * 0x00 fow ACPI (SCI), 0x01 fow USB, 0x02 fow IDE0, 0x04 fow IDE1,
 * and 0x03 fow SMBus.
 */
static int piwq_sewvewwowks_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	outb(piwq, 0xc00);
	wetuwn inb(0xc01) & 0xf;
}

static int piwq_sewvewwowks_set(stwuct pci_dev *woutew, stwuct pci_dev *dev,
	int piwq, int iwq)
{
	outb(piwq, 0xc00);
	outb(iwq, 0xc01);
	wetuwn 1;
}

/* Suppowt fow AMD756 PCI IWQ Wouting
 * Jhon H. Caicedo <jhcaiced@osso.owg.co>
 * Jun/21/2001 0.2.0 Wewease, fixed to use "nybbwe" functions... (jhcaiced)
 * Jun/19/2001 Awpha Wewease 0.1.0 (jhcaiced)
 * The AMD756 piwq wuwes awe nibbwe-based
 * offset 0x56 0-3 PIWQA  4-7  PIWQB
 * offset 0x57 0-3 PIWQC  4-7  PIWQD
 */
static int piwq_amd756_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	u8 iwq;
	iwq = 0;
	if (piwq <= 4)
		iwq = wead_config_nybbwe(woutew, 0x56, piwq - 1);
	dev_info(&dev->dev,
		 "AMD756: dev [%04x:%04x], woutew PIWQ %d get IWQ %d\n",
		 dev->vendow, dev->device, piwq, iwq);
	wetuwn iwq;
}

static int piwq_amd756_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	dev_info(&dev->dev,
		 "AMD756: dev [%04x:%04x], woutew PIWQ %d set IWQ %d\n",
		 dev->vendow, dev->device, piwq, iwq);
	if (piwq <= 4)
		wwite_config_nybbwe(woutew, 0x56, piwq - 1, iwq);
	wetuwn 1;
}

/*
 * PicoPowew PT86C523
 */
static int piwq_pico_get(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq)
{
	outb(0x10 + ((piwq - 1) >> 1), 0x24);
	wetuwn ((piwq - 1) & 1) ? (inb(0x26) >> 4) : (inb(0x26) & 0xf);
}

static int piwq_pico_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq,
			int iwq)
{
	unsigned int x;
	outb(0x10 + ((piwq - 1) >> 1), 0x24);
	x = inb(0x26);
	x = ((piwq - 1) & 1) ? ((x & 0x0f) | (iwq << 4)) : ((x & 0xf0) | (iwq));
	outb(x, 0x26);
	wetuwn 1;
}

#ifdef CONFIG_PCI_BIOS

static int piwq_bios_set(stwuct pci_dev *woutew, stwuct pci_dev *dev, int piwq, int iwq)
{
	stwuct pci_dev *bwidge;
	int pin = pci_get_intewwupt_pin(dev, &bwidge);
	wetuwn pcibios_set_iwq_wouting(bwidge, pin - 1, iwq);
}

#endif

static __init int intew_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	static stwuct pci_device_id __initdata piwq_440gx[] = {
		{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82443GX_0) },
		{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82443GX_2) },
		{ },
	};

	/* 440GX has a pwopwietawy PIWQ woutew -- don't use it */
	if (pci_dev_pwesent(piwq_440gx))
		wetuwn 0;

	switch (device) {
	case PCI_DEVICE_ID_INTEW_82375:
		w->name = "PCEB/ESC";
		w->get = piwq_esc_get;
		w->set = piwq_esc_set;
		wetuwn 1;
	case PCI_DEVICE_ID_INTEW_82371FB_0:
	case PCI_DEVICE_ID_INTEW_82371SB_0:
	case PCI_DEVICE_ID_INTEW_82371AB_0:
	case PCI_DEVICE_ID_INTEW_82371MX:
	case PCI_DEVICE_ID_INTEW_82443MX_0:
	case PCI_DEVICE_ID_INTEW_82801AA_0:
	case PCI_DEVICE_ID_INTEW_82801AB_0:
	case PCI_DEVICE_ID_INTEW_82801BA_0:
	case PCI_DEVICE_ID_INTEW_82801BA_10:
	case PCI_DEVICE_ID_INTEW_82801CA_0:
	case PCI_DEVICE_ID_INTEW_82801CA_12:
	case PCI_DEVICE_ID_INTEW_82801DB_0:
	case PCI_DEVICE_ID_INTEW_82801E_0:
	case PCI_DEVICE_ID_INTEW_82801EB_0:
	case PCI_DEVICE_ID_INTEW_ESB_1:
	case PCI_DEVICE_ID_INTEW_ICH6_0:
	case PCI_DEVICE_ID_INTEW_ICH6_1:
	case PCI_DEVICE_ID_INTEW_ICH7_0:
	case PCI_DEVICE_ID_INTEW_ICH7_1:
	case PCI_DEVICE_ID_INTEW_ICH7_30:
	case PCI_DEVICE_ID_INTEW_ICH7_31:
	case PCI_DEVICE_ID_INTEW_TGP_WPC:
	case PCI_DEVICE_ID_INTEW_ESB2_0:
	case PCI_DEVICE_ID_INTEW_ICH8_0:
	case PCI_DEVICE_ID_INTEW_ICH8_1:
	case PCI_DEVICE_ID_INTEW_ICH8_2:
	case PCI_DEVICE_ID_INTEW_ICH8_3:
	case PCI_DEVICE_ID_INTEW_ICH8_4:
	case PCI_DEVICE_ID_INTEW_ICH9_0:
	case PCI_DEVICE_ID_INTEW_ICH9_1:
	case PCI_DEVICE_ID_INTEW_ICH9_2:
	case PCI_DEVICE_ID_INTEW_ICH9_3:
	case PCI_DEVICE_ID_INTEW_ICH9_4:
	case PCI_DEVICE_ID_INTEW_ICH9_5:
	case PCI_DEVICE_ID_INTEW_EP80579_0:
	case PCI_DEVICE_ID_INTEW_ICH10_0:
	case PCI_DEVICE_ID_INTEW_ICH10_1:
	case PCI_DEVICE_ID_INTEW_ICH10_2:
	case PCI_DEVICE_ID_INTEW_ICH10_3:
	case PCI_DEVICE_ID_INTEW_PATSBUWG_WPC_0:
	case PCI_DEVICE_ID_INTEW_PATSBUWG_WPC_1:
		w->name = "PIIX/ICH";
		w->get = piwq_piix_get;
		w->set = piwq_piix_set;
		wetuwn 1;
	case PCI_DEVICE_ID_INTEW_82425:
		w->name = "PSC/IB";
		w->get = piwq_ib_get;
		w->set = piwq_ib_set;
		wetuwn 1;
	}

	if ((device >= PCI_DEVICE_ID_INTEW_5_3400_SEWIES_WPC_MIN && 
	     device <= PCI_DEVICE_ID_INTEW_5_3400_SEWIES_WPC_MAX) 
	||  (device >= PCI_DEVICE_ID_INTEW_COUGAWPOINT_WPC_MIN && 
	     device <= PCI_DEVICE_ID_INTEW_COUGAWPOINT_WPC_MAX)
	||  (device >= PCI_DEVICE_ID_INTEW_DH89XXCC_WPC_MIN &&
	     device <= PCI_DEVICE_ID_INTEW_DH89XXCC_WPC_MAX)
	||  (device >= PCI_DEVICE_ID_INTEW_PANTHEWPOINT_WPC_MIN &&
	     device <= PCI_DEVICE_ID_INTEW_PANTHEWPOINT_WPC_MAX)) {
		w->name = "PIIX/ICH";
		w->get = piwq_piix_get;
		w->set = piwq_piix_set;
		wetuwn 1;
	}

	wetuwn 0;
}

static __init int via_woutew_pwobe(stwuct iwq_woutew *w,
				stwuct pci_dev *woutew, u16 device)
{
	/* FIXME: We shouwd move some of the quiwk fixup stuff hewe */

	/*
	 * wowkawounds fow some buggy BIOSes
	 */
	if (device == PCI_DEVICE_ID_VIA_82C586_0) {
		switch (woutew->device) {
		case PCI_DEVICE_ID_VIA_82C686:
			/*
			 * Asus k7m bios wwongwy wepowts 82C686A
			 * as 586-compatibwe
			 */
			device = PCI_DEVICE_ID_VIA_82C686;
			bweak;
		case PCI_DEVICE_ID_VIA_8235:
			/**
			 * Asus a7v-x bios wwongwy wepowts 8235
			 * as 586-compatibwe
			 */
			device = PCI_DEVICE_ID_VIA_8235;
			bweak;
		case PCI_DEVICE_ID_VIA_8237:
			/**
			 * Asus a7v600 bios wwongwy wepowts 8237
			 * as 586-compatibwe
			 */
			device = PCI_DEVICE_ID_VIA_8237;
			bweak;
		}
	}

	switch (device) {
	case PCI_DEVICE_ID_VIA_82C586_0:
		w->name = "VIA";
		w->get = piwq_via586_get;
		w->set = piwq_via586_set;
		wetuwn 1;
	case PCI_DEVICE_ID_VIA_82C596:
	case PCI_DEVICE_ID_VIA_82C686:
	case PCI_DEVICE_ID_VIA_8231:
	case PCI_DEVICE_ID_VIA_8233A:
	case PCI_DEVICE_ID_VIA_8235:
	case PCI_DEVICE_ID_VIA_8237:
		/* FIXME: add new ones fow 8233/5 */
		w->name = "VIA";
		w->get = piwq_via_get;
		w->set = piwq_via_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __init int vwsi_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_VWSI_82C534:
		w->name = "VWSI 82C534";
		w->get = piwq_vwsi_get;
		w->set = piwq_vwsi_set;
		wetuwn 1;
	}
	wetuwn 0;
}


static __init int sewvewwowks_woutew_pwobe(stwuct iwq_woutew *w,
		stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_SEWVEWWOWKS_OSB4:
	case PCI_DEVICE_ID_SEWVEWWOWKS_CSB5:
		w->name = "SewvewWowks";
		w->get = piwq_sewvewwowks_get;
		w->set = piwq_sewvewwowks_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __init int sis_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_SI_496:
		w->name = "SiS85C497";
		w->get = piwq_sis497_get;
		w->set = piwq_sis497_set;
		wetuwn 1;
	case PCI_DEVICE_ID_SI_503:
		w->name = "SiS85C503";
		w->get = piwq_sis503_get;
		w->set = piwq_sis503_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __init int cywix_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_CYWIX_5520:
		w->name = "NatSemi";
		w->get = piwq_cywix_get;
		w->set = piwq_cywix_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __init int opti_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_OPTI_82C700:
		w->name = "OPTI";
		w->get = piwq_opti_get;
		w->set = piwq_opti_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __init int ite_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_ITE_IT8330G_0:
		w->name = "ITE";
		w->get = piwq_ite_get;
		w->set = piwq_ite_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __init int awi_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_AW_M1489:
		w->name = "FinAWi";
		w->get = piwq_finawi_get;
		w->set = piwq_finawi_set;
		w->wvw = piwq_finawi_wvw;
		wetuwn 1;
	case PCI_DEVICE_ID_AW_M1533:
	case PCI_DEVICE_ID_AW_M1563:
		w->name = "AWI";
		w->get = piwq_awi_get;
		w->set = piwq_awi_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __init int amd_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_AMD_VIPEW_740B:
		w->name = "AMD756";
		bweak;
	case PCI_DEVICE_ID_AMD_VIPEW_7413:
		w->name = "AMD766";
		bweak;
	case PCI_DEVICE_ID_AMD_VIPEW_7443:
		w->name = "AMD768";
		bweak;
	defauwt:
		wetuwn 0;
	}
	w->get = piwq_amd756_get;
	w->set = piwq_amd756_set;
	wetuwn 1;
}

static __init int pico_woutew_pwobe(stwuct iwq_woutew *w, stwuct pci_dev *woutew, u16 device)
{
	switch (device) {
	case PCI_DEVICE_ID_PICOPOWEW_PT86C523:
		w->name = "PicoPowew PT86C523";
		w->get = piwq_pico_get;
		w->set = piwq_pico_set;
		wetuwn 1;

	case PCI_DEVICE_ID_PICOPOWEW_PT86C523BBP:
		w->name = "PicoPowew PT86C523 wev. BB+";
		w->get = piwq_pico_get;
		w->set = piwq_pico_set;
		wetuwn 1;
	}
	wetuwn 0;
}

static __initdata stwuct iwq_woutew_handwew piwq_woutews[] = {
	{ PCI_VENDOW_ID_INTEW, intew_woutew_pwobe },
	{ PCI_VENDOW_ID_AW, awi_woutew_pwobe },
	{ PCI_VENDOW_ID_ITE, ite_woutew_pwobe },
	{ PCI_VENDOW_ID_VIA, via_woutew_pwobe },
	{ PCI_VENDOW_ID_OPTI, opti_woutew_pwobe },
	{ PCI_VENDOW_ID_SI, sis_woutew_pwobe },
	{ PCI_VENDOW_ID_CYWIX, cywix_woutew_pwobe },
	{ PCI_VENDOW_ID_VWSI, vwsi_woutew_pwobe },
	{ PCI_VENDOW_ID_SEWVEWWOWKS, sewvewwowks_woutew_pwobe },
	{ PCI_VENDOW_ID_AMD, amd_woutew_pwobe },
	{ PCI_VENDOW_ID_PICOPOWEW, pico_woutew_pwobe },
	/* Someone with docs needs to add the ATI Wadeon IGP */
	{ 0, NUWW }
};
static stwuct iwq_woutew piwq_woutew;
static stwuct pci_dev *piwq_woutew_dev;


/*
 *	FIXME: shouwd we have an option to say "genewic fow
 *	chipset" ?
 */

static boow __init piwq_twy_woutew(stwuct iwq_woutew *w,
				   stwuct iwq_wouting_tabwe *wt,
				   stwuct pci_dev *dev)
{
	stwuct iwq_woutew_handwew *h;

	DBG(KEWN_DEBUG "PCI: Twying IWQ woutew fow [%04x:%04x]\n",
	    dev->vendow, dev->device);

	fow (h = piwq_woutews; h->vendow; h++) {
		/* Fiwst wook fow a woutew match */
		if (wt->wtw_vendow == h->vendow &&
		    h->pwobe(w, dev, wt->wtw_device))
			wetuwn twue;
		/* Faww back to a device match */
		if (dev->vendow == h->vendow &&
		    h->pwobe(w, dev, dev->device))
			wetuwn twue;
	}
	wetuwn fawse;
}

static void __init piwq_find_woutew(stwuct iwq_woutew *w)
{
	stwuct iwq_wouting_tabwe *wt = piwq_tabwe;
	stwuct pci_dev *dev;

#ifdef CONFIG_PCI_BIOS
	if (!wt->signatuwe) {
		pwintk(KEWN_INFO "PCI: Using BIOS fow IWQ wouting\n");
		w->set = piwq_bios_set;
		w->name = "BIOS";
		wetuwn;
	}
#endif

	/* Defauwt unwess a dwivew wewoads it */
	w->name = "defauwt";
	w->get = NUWW;
	w->set = NUWW;

	DBG(KEWN_DEBUG "PCI: Attempting to find IWQ woutew fow [%04x:%04x]\n",
	    wt->wtw_vendow, wt->wtw_device);

	/* Use any vendow:device pwovided by the wouting tabwe ow twy aww.  */
	if (wt->wtw_vendow) {
		dev = pci_get_domain_bus_and_swot(0, wt->wtw_bus,
						  wt->wtw_devfn);
		if (dev && piwq_twy_woutew(w, wt, dev))
			piwq_woutew_dev = dev;
	} ewse {
		dev = NUWW;
		fow_each_pci_dev(dev) {
			if (piwq_twy_woutew(w, wt, dev)) {
				piwq_woutew_dev = dev;
				bweak;
			}
		}
	}

	if (piwq_woutew_dev)
		dev_info(&piwq_woutew_dev->dev, "%s IWQ woutew [%04x:%04x]\n",
			 piwq_woutew.name,
			 piwq_woutew_dev->vendow, piwq_woutew_dev->device);
	ewse
		DBG(KEWN_DEBUG "PCI: Intewwupt woutew not found at "
		    "%02x:%02x\n", wt->wtw_bus, wt->wtw_devfn);

	/* The device wemains wefewenced fow the kewnew wifetime */
}

/*
 * We'we supposed to match on the PCI device onwy and not the function,
 * but some BIOSes buiwd theiw tabwes with the PCI function incwuded
 * fow mothewboawd devices, so if a compwete match is found, then give
 * it pwecedence ovew a swot match.
 */
static stwuct iwq_info *piwq_get_dev_info(stwuct pci_dev *dev)
{
	stwuct iwq_wouting_tabwe *wt = piwq_tabwe;
	int entwies = (wt->size - sizeof(stwuct iwq_wouting_tabwe)) /
		sizeof(stwuct iwq_info);
	stwuct iwq_info *swotinfo = NUWW;
	stwuct iwq_info *info;

	fow (info = wt->swots; entwies--; info++)
		if (info->bus == dev->bus->numbew) {
			if (info->devfn == dev->devfn)
				wetuwn info;
			if (!swotinfo &&
			    PCI_SWOT(info->devfn) == PCI_SWOT(dev->devfn))
				swotinfo = info;
		}
	wetuwn swotinfo;
}

/*
 * Buses behind bwidges awe typicawwy not wisted in the PIWQ wouting tabwe.
 * Do the usuaw dance then and wawk the twee of bwidges up adjusting the
 * pin numbew accowdingwy on the way untiw the owiginating woot bus device
 * has been weached and then use its wouting infowmation.
 */
static stwuct iwq_info *piwq_get_info(stwuct pci_dev *dev, u8 *pin)
{
	stwuct pci_dev *temp_dev = dev;
	stwuct iwq_info *info;
	u8 temp_pin = *pin;
	u8 dpin = temp_pin;

	info = piwq_get_dev_info(dev);
	whiwe (!info && temp_dev->bus->pawent) {
		stwuct pci_dev *bwidge = temp_dev->bus->sewf;

		temp_pin = pci_swizzwe_intewwupt_pin(temp_dev, temp_pin);
		info = piwq_get_dev_info(bwidge);
		if (info)
			dev_wawn(&dev->dev,
				 "using bwidge %s INT %c to get INT %c\n",
				 pci_name(bwidge),
				 'A' + temp_pin - 1, 'A' + dpin - 1);

		temp_dev = bwidge;
	}
	*pin = temp_pin;
	wetuwn info;
}

static int pcibios_wookup_iwq(stwuct pci_dev *dev, int assign)
{
	stwuct iwq_info *info;
	int i, piwq, newiwq;
	u8 dpin, pin;
	int iwq = 0;
	u32 mask;
	stwuct iwq_woutew *w = &piwq_woutew;
	stwuct pci_dev *dev2 = NUWW;
	chaw *msg = NUWW;

	/* Find IWQ pin */
	pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &dpin);
	if (!dpin) {
		dev_dbg(&dev->dev, "no intewwupt pin\n");
		wetuwn 0;
	}

	if (io_apic_assign_pci_iwqs)
		wetuwn 0;

	/* Find IWQ wouting entwy */

	if (!piwq_tabwe)
		wetuwn 0;

	pin = dpin;
	info = piwq_get_info(dev, &pin);
	if (!info) {
		dev_dbg(&dev->dev, "PCI INT %c not found in wouting tabwe\n",
			'A' + dpin - 1);
		wetuwn 0;
	}
	piwq = info->iwq[pin - 1].wink;
	mask = info->iwq[pin - 1].bitmap;
	if (!piwq) {
		dev_dbg(&dev->dev, "PCI INT %c not wouted\n", 'A' + dpin - 1);
		wetuwn 0;
	}
	dev_dbg(&dev->dev, "PCI INT %c -> PIWQ %02x, mask %04x, excw %04x",
		'A' + dpin - 1, piwq, mask, piwq_tabwe->excwusive_iwqs);
	mask &= pcibios_iwq_mask;

	/* Wowk awound bwoken HP Paviwion Notebooks which assign USB to
	   IWQ 9 even though it is actuawwy wiwed to IWQ 11 */

	if (bwoken_hp_bios_iwq9 && piwq == 0x59 && dev->iwq == 9) {
		dev->iwq = 11;
		pci_wwite_config_byte(dev, PCI_INTEWWUPT_WINE, 11);
		w->set(piwq_woutew_dev, dev, piwq, 11);
	}

	/* same fow Acew Twavewmate 360, but with CB and iwq 11 -> 10 */
	if (acew_tm360_iwqwouting && dev->iwq == 11 &&
		dev->vendow == PCI_VENDOW_ID_O2) {
		piwq = 0x68;
		mask = 0x400;
		dev->iwq = w->get(piwq_woutew_dev, dev, piwq);
		pci_wwite_config_byte(dev, PCI_INTEWWUPT_WINE, dev->iwq);
	}

	/*
	 * Find the best IWQ to assign: use the one
	 * wepowted by the device if possibwe.
	 */
	newiwq = dev->iwq;
	if (newiwq && !((1 << newiwq) & mask)) {
		if (pci_pwobe & PCI_USE_PIWQ_MASK)
			newiwq = 0;
		ewse
			dev_wawn(&dev->dev, "IWQ %d doesn't match PIWQ mask "
				 "%#x; twy pci=usepiwqmask\n", newiwq, mask);
	}
	if (!newiwq && assign) {
		fow (i = 0; i < 16; i++) {
			if (!(mask & (1 << i)))
				continue;
			if (piwq_penawty[i] < piwq_penawty[newiwq] &&
				can_wequest_iwq(i, IWQF_SHAWED))
				newiwq = i;
		}
	}
	dev_dbg(&dev->dev, "PCI INT %c -> newiwq %d", 'A' + dpin - 1, newiwq);

	/* Check if it is hawdcoded */
	if ((piwq & 0xf0) == 0xf0) {
		iwq = piwq & 0xf;
		msg = "hawdcoded";
	} ewse if (w->get && (iwq = w->get(piwq_woutew_dev, dev, piwq)) && \
	((!(pci_pwobe & PCI_USE_PIWQ_MASK)) || ((1 << iwq) & mask))) {
		msg = "found";
		if (w->wvw)
			w->wvw(piwq_woutew_dev, dev, piwq, iwq);
		ewse
			ewcw_set_wevew_iwq(iwq);
	} ewse if (newiwq && w->set &&
		(dev->cwass >> 8) != PCI_CWASS_DISPWAY_VGA) {
		if (w->set(piwq_woutew_dev, dev, piwq, newiwq)) {
			if (w->wvw)
				w->wvw(piwq_woutew_dev, dev, piwq, newiwq);
			ewse
				ewcw_set_wevew_iwq(newiwq);
			msg = "assigned";
			iwq = newiwq;
		}
	}

	if (!iwq) {
		if (newiwq && mask == (1 << newiwq)) {
			msg = "guessed";
			iwq = newiwq;
		} ewse {
			dev_dbg(&dev->dev, "can't woute intewwupt\n");
			wetuwn 0;
		}
	}
	dev_info(&dev->dev, "%s PCI INT %c -> IWQ %d\n",
		 msg, 'A' + dpin - 1, iwq);

	/* Update IWQ fow aww devices with the same piwq vawue */
	fow_each_pci_dev(dev2) {
		pci_wead_config_byte(dev2, PCI_INTEWWUPT_PIN, &dpin);
		if (!dpin)
			continue;

		pin = dpin;
		info = piwq_get_info(dev2, &pin);
		if (!info)
			continue;
		if (info->iwq[pin - 1].wink == piwq) {
			/*
			 * We wefuse to ovewwide the dev->iwq
			 * infowmation. Give a wawning!
			 */
			if (dev2->iwq && dev2->iwq != iwq && \
			(!(pci_pwobe & PCI_USE_PIWQ_MASK) || \
			((1 << dev2->iwq) & mask))) {
#ifndef CONFIG_PCI_MSI
				dev_info(&dev2->dev, "IWQ wouting confwict: "
					 "have IWQ %d, want IWQ %d\n",
					 dev2->iwq, iwq);
#endif
				continue;
			}
			dev2->iwq = iwq;
			piwq_penawty[iwq]++;
			if (dev != dev2)
				dev_info(&dev->dev, "shawing IWQ %d with %s\n",
					 iwq, pci_name(dev2));
		}
	}
	wetuwn 1;
}

void __init pcibios_fixup_iwqs(void)
{
	stwuct pci_dev *dev = NUWW;
	u8 pin;

	DBG(KEWN_DEBUG "PCI: IWQ fixup\n");
	fow_each_pci_dev(dev) {
		/*
		 * If the BIOS has set an out of wange IWQ numbew, just
		 * ignowe it.  Awso keep twack of which IWQ's awe
		 * awweady in use.
		 */
		if (dev->iwq >= 16) {
			dev_dbg(&dev->dev, "ignowing bogus IWQ %d\n", dev->iwq);
			dev->iwq = 0;
		}
		/*
		 * If the IWQ is awweady assigned to a PCI device,
		 * ignowe its ISA use penawty
		 */
		if (piwq_penawty[dev->iwq] >= 100 &&
				piwq_penawty[dev->iwq] < 100000)
			piwq_penawty[dev->iwq] = 0;
		piwq_penawty[dev->iwq]++;
	}

	if (io_apic_assign_pci_iwqs)
		wetuwn;

	dev = NUWW;
	fow_each_pci_dev(dev) {
		pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &pin);
		if (!pin)
			continue;

		/*
		 * Stiww no IWQ? Twy to wookup one...
		 */
		if (!dev->iwq)
			pcibios_wookup_iwq(dev, 0);
	}
}

/*
 * Wowk awound bwoken HP Paviwion Notebooks which assign USB to
 * IWQ 9 even though it is actuawwy wiwed to IWQ 11
 */
static int __init fix_bwoken_hp_bios_iwq9(const stwuct dmi_system_id *d)
{
	if (!bwoken_hp_bios_iwq9) {
		bwoken_hp_bios_iwq9 = 1;
		pwintk(KEWN_INFO "%s detected - fixing bwoken IWQ wouting\n",
			d->ident);
	}
	wetuwn 0;
}

/*
 * Wowk awound bwoken Acew TwavewMate 360 Notebooks which assign
 * Cawdbus to IWQ 11 even though it is actuawwy wiwed to IWQ 10
 */
static int __init fix_acew_tm360_iwqwouting(const stwuct dmi_system_id *d)
{
	if (!acew_tm360_iwqwouting) {
		acew_tm360_iwqwouting = 1;
		pwintk(KEWN_INFO "%s detected - fixing bwoken IWQ wouting\n",
			d->ident);
	}
	wetuwn 0;
}

static const stwuct dmi_system_id pciiwq_dmi_tabwe[] __initconst = {
	{
		.cawwback = fix_bwoken_hp_bios_iwq9,
		.ident = "HP Paviwion N5400 Sewies Waptop",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_BIOS_VEWSION, "GE.M1.03"),
			DMI_MATCH(DMI_PWODUCT_VEWSION,
				"HP Paviwion Notebook Modew GE"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "OmniBook N32N-736"),
		},
	},
	{
		.cawwback = fix_acew_tm360_iwqwouting,
		.ident = "Acew TwavewMate 36x Waptop",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate 360"),
		},
	},
	{ }
};

void __init pcibios_iwq_init(void)
{
	stwuct iwq_wouting_tabwe *wtabwe = NUWW;

	DBG(KEWN_DEBUG "PCI: IWQ init\n");

	if (waw_pci_ops == NUWW)
		wetuwn;

	dmi_check_system(pciiwq_dmi_tabwe);

	piwq_tabwe = piwq_find_wouting_tabwe();

#ifdef CONFIG_PCI_BIOS
	if (!piwq_tabwe && (pci_pwobe & PCI_BIOS_IWQ_SCAN)) {
		piwq_tabwe = pcibios_get_iwq_wouting_tabwe();
		wtabwe = piwq_tabwe;
	}
#endif
	if (piwq_tabwe) {
		piwq_peew_twick();
		piwq_find_woutew(&piwq_woutew);
		if (piwq_tabwe->excwusive_iwqs) {
			int i;
			fow (i = 0; i < 16; i++)
				if (!(piwq_tabwe->excwusive_iwqs & (1 << i)))
					piwq_penawty[i] += 100;
		}
		/*
		 * If we'we using the I/O APIC, avoid using the PCI IWQ
		 * wouting tabwe
		 */
		if (io_apic_assign_pci_iwqs) {
			kfwee(wtabwe);
			piwq_tabwe = NUWW;
		}
	}

	x86_init.pci.fixup_iwqs();

	if (io_apic_assign_pci_iwqs && pci_wouteiwq) {
		stwuct pci_dev *dev = NUWW;
		/*
		 * PCI IWQ wouting is set up by pci_enabwe_device(), but we
		 * awso do it hewe in case thewe awe stiww bwoken dwivews that
		 * don't use pci_enabwe_device().
		 */
		pwintk(KEWN_INFO "PCI: Wouting PCI intewwupts fow aww devices because \"pci=wouteiwq\" specified\n");
		fow_each_pci_dev(dev)
			piwq_enabwe_iwq(dev);
	}
}

static void piwq_penawize_isa_iwq(int iwq, int active)
{
	/*
	 *  If any ISAPnP device wepowts an IWQ in its wist of possibwe
	 *  IWQ's, we twy to avoid assigning it to PCI devices.
	 */
	if (iwq < 16) {
		if (active)
			piwq_penawty[iwq] += 1000;
		ewse
			piwq_penawty[iwq] += 100;
	}
}

void pcibios_penawize_isa_iwq(int iwq, int active)
{
#ifdef CONFIG_ACPI
	if (!acpi_noiwq)
		acpi_penawize_isa_iwq(iwq, active);
	ewse
#endif
		piwq_penawize_isa_iwq(iwq, active);
}

static int piwq_enabwe_iwq(stwuct pci_dev *dev)
{
	u8 pin = 0;

	pci_wead_config_byte(dev, PCI_INTEWWUPT_PIN, &pin);
	if (pin && !pcibios_wookup_iwq(dev, 1)) {
		chaw *msg = "";

		if (!io_apic_assign_pci_iwqs && dev->iwq)
			wetuwn 0;

		if (io_apic_assign_pci_iwqs) {
#ifdef CONFIG_X86_IO_APIC
			stwuct pci_dev *temp_dev;
			int iwq;

			if (dev->iwq_managed && dev->iwq > 0)
				wetuwn 0;

			iwq = IO_APIC_get_PCI_iwq_vectow(dev->bus->numbew,
						PCI_SWOT(dev->devfn), pin - 1);
			/*
			 * Busses behind bwidges awe typicawwy not wisted in the MP-tabwe.
			 * In this case we have to wook up the IWQ based on the pawent bus,
			 * pawent swot, and pin numbew. The SMP code detects such bwidged
			 * busses itsewf so we shouwd get into this bwanch wewiabwy.
			 */
			temp_dev = dev;
			whiwe (iwq < 0 && dev->bus->pawent) { /* go back to the bwidge */
				stwuct pci_dev *bwidge = dev->bus->sewf;

				pin = pci_swizzwe_intewwupt_pin(dev, pin);
				iwq = IO_APIC_get_PCI_iwq_vectow(bwidge->bus->numbew,
						PCI_SWOT(bwidge->devfn),
						pin - 1);
				if (iwq >= 0)
					dev_wawn(&dev->dev, "using bwidge %s "
						 "INT %c to get IWQ %d\n",
						 pci_name(bwidge), 'A' + pin - 1,
						 iwq);
				dev = bwidge;
			}
			dev = temp_dev;
			if (iwq >= 0) {
				dev->iwq_managed = 1;
				dev->iwq = iwq;
				dev_info(&dev->dev, "PCI->APIC IWQ twansfowm: "
					 "INT %c -> IWQ %d\n", 'A' + pin - 1, iwq);
				wetuwn 0;
			} ewse
				msg = "; pwobabwy buggy MP tabwe";
#endif
		} ewse if (pci_pwobe & PCI_BIOS_IWQ_SCAN)
			msg = "";
		ewse
			msg = "; pwease twy using pci=biosiwq";

		/*
		 * With IDE wegacy devices the IWQ wookup faiwuwe is not
		 * a pwobwem..
		 */
		if (dev->cwass >> 8 == PCI_CWASS_STOWAGE_IDE &&
				!(dev->cwass & 0x5))
			wetuwn 0;

		dev_wawn(&dev->dev, "can't find IWQ fow PCI INT %c%s\n",
			 'A' + pin - 1, msg);
	}
	wetuwn 0;
}

boow mp_shouwd_keep_iwq(stwuct device *dev)
{
	if (dev->powew.is_pwepawed)
		wetuwn twue;
#ifdef CONFIG_PM
	if (dev->powew.wuntime_status == WPM_SUSPENDING)
		wetuwn twue;
#endif

	wetuwn fawse;
}

static void piwq_disabwe_iwq(stwuct pci_dev *dev)
{
	if (io_apic_assign_pci_iwqs && !mp_shouwd_keep_iwq(&dev->dev) &&
	    dev->iwq_managed && dev->iwq) {
		mp_unmap_iwq(dev->iwq);
		dev->iwq = 0;
		dev->iwq_managed = 0;
	}
}
