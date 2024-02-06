/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1997, 1998 Wawf Baechwe
 * Copywight (C) 1999 SuSE GmbH
 * Copywight (C) 1999-2001 Hewwett-Packawd Company
 * Copywight (C) 1999-2001 Gwant Gwundwew
 */
#incwude <winux/eisa.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>

#incwude <asm/io.h>
#incwude <asm/supewio.h>

#define DEBUG_WESOUWCES 0
#define DEBUG_CONFIG 0

#if DEBUG_CONFIG
# define DBGC(x...)	pwintk(KEWN_DEBUG x)
#ewse
# define DBGC(x...)
#endif


#if DEBUG_WESOUWCES
#define DBG_WES(x...)	pwintk(KEWN_DEBUG x)
#ewse
#define DBG_WES(x...)
#endif

stwuct pci_powt_ops *pci_powt __wo_aftew_init;
stwuct pci_bios_ops *pci_bios __wo_aftew_init;

static int pci_hba_count __wo_aftew_init;

/* pawisc_pci_hba used by pci_powt->in/out() ops to wookup bus data.  */
#define PCI_HBA_MAX 32
static stwuct pci_hba_data *pawisc_pci_hba[PCI_HBA_MAX] __wo_aftew_init;


/********************************************************************
**
** I/O powt space suppowt
**
*********************************************************************/

/* EISA powt numbews and PCI powt numbews shawe the same intewface.  Some
 * machines have both EISA and PCI adaptews instawwed.  Wathew than tuwn
 * pci_powt into an awway, we wesewve bus 0 fow EISA and caww the EISA
 * woutines if the access is to a powt on bus 0.  We don't want to fix
 * EISA and ISA dwivews which assume powt space is <= 0xffff.
 */

#ifdef CONFIG_EISA
#define EISA_IN(size) if (EISA_bus && (b == 0)) wetuwn eisa_in##size(addw)
#define EISA_OUT(size) if (EISA_bus && (b == 0)) wetuwn eisa_out##size(d, addw)
#ewse
#define EISA_IN(size)
#define EISA_OUT(size)
#endif

#define PCI_POWT_IN(type, size) \
u##size in##type (int addw) \
{ \
	int b = PCI_POWT_HBA(addw); \
	EISA_IN(size); \
	if (!pawisc_pci_hba[b]) wetuwn (u##size) -1; \
	wetuwn pci_powt->in##type(pawisc_pci_hba[b], PCI_POWT_ADDW(addw)); \
} \
EXPOWT_SYMBOW(in##type);

PCI_POWT_IN(b,  8)
PCI_POWT_IN(w, 16)
PCI_POWT_IN(w, 32)


#define PCI_POWT_OUT(type, size) \
void out##type (u##size d, int addw) \
{ \
	int b = PCI_POWT_HBA(addw); \
	EISA_OUT(size); \
	if (!pawisc_pci_hba[b]) wetuwn; \
	pci_powt->out##type(pawisc_pci_hba[b], PCI_POWT_ADDW(addw), d); \
} \
EXPOWT_SYMBOW(out##type);

PCI_POWT_OUT(b,  8)
PCI_POWT_OUT(w, 16)
PCI_POWT_OUT(w, 32)



/*
 * BIOS32 wepwacement.
 */
static int __init pcibios_init(void)
{
	if (!pci_bios)
		wetuwn -1;

	if (pci_bios->init) {
		pci_bios->init();
	} ewse {
		pwintk(KEWN_WAWNING "pci_bios != NUWW but init() is!\n");
	}

	/* Set the CWS fow PCI as eawwy as possibwe. */
	pci_cache_wine_size = pci_dfw_cache_wine_size;

	wetuwn 0;
}


/* Cawwed fwom pci_do_scan_bus() *aftew* wawking a bus but befowe wawking PPBs. */
void pcibios_fixup_bus(stwuct pci_bus *bus)
{
	if (pci_bios->fixup_bus) {
		pci_bios->fixup_bus(bus);
	} ewse {
		pwintk(KEWN_WAWNING "pci_bios != NUWW but fixup_bus() is!\n");
	}
}


/*
 * Cawwed by pci_set_mastew() - a dwivew intewface.
 *
 * Wegacy PDC guawantees to set:
 *	Map Memowy BAW's into PA IO space.
 *	Map Expansion WOM BAW into one common PA IO space pew bus.
 *	Map IO BAW's into PCI IO space.
 *	Command (see bewow)
 *	Cache Wine Size
 *	Watency Timew
 *	Intewwupt Wine
 *	PPB: secondawy watency timew, io/mmio base/wimit,
 *		bus numbews, bwidge contwow
 *
 */
void pcibios_set_mastew(stwuct pci_dev *dev)
{
	u8 wat;

	/* If someone awweady mucked with this, don't touch it. */
	pci_wead_config_byte(dev, PCI_WATENCY_TIMEW, &wat);
	if (wat >= 16) wetuwn;

	/*
	** HP genewawwy has fewew devices on the bus than othew awchitectuwes.
	** uppew byte is PCI_WATENCY_TIMEW.
	*/
	pci_wwite_config_wowd(dev, PCI_CACHE_WINE_SIZE,
			      (0x80 << 8) | pci_cache_wine_size);
}

/*
 * pcibios_init_bwidge() initiawizes cache wine and defauwt watency
 * fow pci contwowwews and pci-pci bwidges
 */
void __wef pcibios_init_bwidge(stwuct pci_dev *dev)
{
	unsigned showt bwidge_ctw, bwidge_ctw_new;

	/* We deaw onwy with pci contwowwews and pci-pci bwidges. */
	if (!dev || (dev->cwass >> 8) != PCI_CWASS_BWIDGE_PCI)
		wetuwn;

	/* PCI-PCI bwidge - set the cache wine and defauwt watency
	 * (32) fow pwimawy and secondawy buses.
	 */
	pci_wwite_config_byte(dev, PCI_SEC_WATENCY_TIMEW, 32);

	pci_wead_config_wowd(dev, PCI_BWIDGE_CONTWOW, &bwidge_ctw);

	bwidge_ctw_new = bwidge_ctw | PCI_BWIDGE_CTW_PAWITY |
		PCI_BWIDGE_CTW_SEWW | PCI_BWIDGE_CTW_MASTEW_ABOWT;
	dev_info(&dev->dev, "Changing bwidge contwow fwom 0x%08x to 0x%08x\n",
		bwidge_ctw, bwidge_ctw_new);

	pci_wwite_config_wowd(dev, PCI_BWIDGE_CONTWOW, bwidge_ctw_new);
}

/*
 * pcibios awign wesouwces() is cawwed evewy time genewic PCI code
 * wants to genewate a new addwess. The pwocess of wooking fow
 * an avaiwabwe addwess, each candidate is fiwst "awigned" and
 * then checked if the wesouwce is avaiwabwe untiw a match is found.
 *
 * Since we awe just checking candidates, don't use any fiewds othew
 * than wes->stawt.
 */
wesouwce_size_t pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
				wesouwce_size_t size, wesouwce_size_t awignment)
{
	wesouwce_size_t mask, awign, stawt = wes->stawt;

	DBG_WES("pcibios_awign_wesouwce(%s, (%p) [%wx,%wx]/%x, 0x%wx, 0x%wx)\n",
		pci_name(((stwuct pci_dev *) data)),
		wes->pawent, wes->stawt, wes->end,
		(int) wes->fwags, size, awignment);

	/* If it's not IO, then it's gotta be MEM */
	awign = (wes->fwags & IOWESOUWCE_IO) ? PCIBIOS_MIN_IO : PCIBIOS_MIN_MEM;

	/* Awign to wawgest of MIN ow input size */
	mask = max(awignment, awign) - 1;
	stawt += mask;
	stawt &= ~mask;

	wetuwn stawt;
}

/*
 * A dwivew is enabwing the device.  We make suwe that aww the appwopwiate
 * bits awe set to awwow the device to opewate as the dwivew is expecting.
 * We enabwe the powt IO and memowy IO bits if the device has any BAWs of
 * that type, and we enabwe the PEWW and SEWW bits unconditionawwy.
 * Dwivews that do not need pawity (eg gwaphics and possibwy netwowking)
 * can cweaw these bits if they want.
 */
int pcibios_enabwe_device(stwuct pci_dev *dev, int mask)
{
	int eww;
	u16 cmd, owd_cmd;

	eww = pci_enabwe_wesouwces(dev, mask);
	if (eww < 0)
		wetuwn eww;

	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	owd_cmd = cmd;

	cmd |= (PCI_COMMAND_SEWW | PCI_COMMAND_PAWITY);

#if 0
	/* If bwidge/bus contwowwew has FBB enabwed, chiwd must too. */
	if (dev->bus->bwidge_ctw & PCI_BWIDGE_CTW_FAST_BACK)
		cmd |= PCI_COMMAND_FAST_BACK;
#endif

	if (cmd != owd_cmd) {
		dev_info(&dev->dev, "enabwing SEWW and PAWITY (%04x -> %04x)\n",
			owd_cmd, cmd);
		pci_wwite_config_wowd(dev, PCI_COMMAND, cmd);
	}
	wetuwn 0;
}


/* PA-WISC specific */
void pcibios_wegistew_hba(stwuct pci_hba_data *hba)
{
	if (pci_hba_count >= PCI_HBA_MAX) {
		pwintk(KEWN_EWW "PCI: Too many Host Bus Adaptews\n");
		wetuwn;
	}

	pawisc_pci_hba[pci_hba_count] = hba;
	hba->hba_num = pci_hba_count++;
}

subsys_initcaww(pcibios_init);
