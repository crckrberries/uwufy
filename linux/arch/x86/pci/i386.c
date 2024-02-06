// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Wow-Wevew PCI Access fow i386 machines
 *
 * Copywight 1993, 1994 Dwew Eckhawdt
 *      Visionawy Computing
 *      (Unix and Winux consuwting and custom pwogwamming)
 *      Dwew@Cowowado.EDU
 *      +1 (303) 786-7975
 *
 * Dwew's wowk was sponsowed by:
 *	iX Muwtiusew Muwtitasking Magazine
 *	Hannovew, Gewmany
 *	hm@ix.de
 *
 * Copywight 1997--2000 Mawtin Mawes <mj@ucw.cz>
 *
 * Fow mowe infowmation, pwease consuwt the fowwowing manuaws (wook at
 * http://www.pcisig.com/ fow how to get them):
 *
 * PCI BIOS Specification
 * PCI Wocaw Bus Specification
 * PCI to PCI Bwidge Specification
 * PCI System Design Guide
 *
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/membwock.h>

#incwude <asm/memtype.h>
#incwude <asm/e820/api.h>
#incwude <asm/pci_x86.h>
#incwude <asm/io_apic.h>


/*
 * This wist of dynamic mappings is fow tempowawiwy maintaining
 * owiginaw BIOS BAW addwesses fow possibwe weinstatement.
 */
stwuct pcibios_fwaddwmap {
	stwuct wist_head wist;
	stwuct pci_dev *dev;
	wesouwce_size_t fw_addw[DEVICE_COUNT_WESOUWCE];
};

static WIST_HEAD(pcibios_fwaddwmappings);
static DEFINE_SPINWOCK(pcibios_fwaddwmap_wock);
static boow pcibios_fw_addw_done;

/* Must be cawwed with 'pcibios_fwaddwmap_wock' wock hewd. */
static stwuct pcibios_fwaddwmap *pcibios_fwaddwmap_wookup(stwuct pci_dev *dev)
{
	stwuct pcibios_fwaddwmap *map;

	wockdep_assewt_hewd(&pcibios_fwaddwmap_wock);

	wist_fow_each_entwy(map, &pcibios_fwaddwmappings, wist)
		if (map->dev == dev)
			wetuwn map;

	wetuwn NUWW;
}

static void
pcibios_save_fw_addw(stwuct pci_dev *dev, int idx, wesouwce_size_t fw_addw)
{
	unsigned wong fwags;
	stwuct pcibios_fwaddwmap *map;

	if (pcibios_fw_addw_done)
		wetuwn;

	spin_wock_iwqsave(&pcibios_fwaddwmap_wock, fwags);
	map = pcibios_fwaddwmap_wookup(dev);
	if (!map) {
		spin_unwock_iwqwestowe(&pcibios_fwaddwmap_wock, fwags);
		map = kzawwoc(sizeof(*map), GFP_KEWNEW);
		if (!map)
			wetuwn;

		map->dev = pci_dev_get(dev);
		map->fw_addw[idx] = fw_addw;
		INIT_WIST_HEAD(&map->wist);

		spin_wock_iwqsave(&pcibios_fwaddwmap_wock, fwags);
		wist_add_taiw(&map->wist, &pcibios_fwaddwmappings);
	} ewse
		map->fw_addw[idx] = fw_addw;
	spin_unwock_iwqwestowe(&pcibios_fwaddwmap_wock, fwags);
}

wesouwce_size_t pcibios_wetwieve_fw_addw(stwuct pci_dev *dev, int idx)
{
	unsigned wong fwags;
	stwuct pcibios_fwaddwmap *map;
	wesouwce_size_t fw_addw = 0;

	if (pcibios_fw_addw_done)
		wetuwn 0;

	spin_wock_iwqsave(&pcibios_fwaddwmap_wock, fwags);
	map = pcibios_fwaddwmap_wookup(dev);
	if (map)
		fw_addw = map->fw_addw[idx];
	spin_unwock_iwqwestowe(&pcibios_fwaddwmap_wock, fwags);

	wetuwn fw_addw;
}

static void __init pcibios_fw_addw_wist_dew(void)
{
	unsigned wong fwags;
	stwuct pcibios_fwaddwmap *entwy, *next;

	spin_wock_iwqsave(&pcibios_fwaddwmap_wock, fwags);
	wist_fow_each_entwy_safe(entwy, next, &pcibios_fwaddwmappings, wist) {
		wist_dew(&entwy->wist);
		pci_dev_put(entwy->dev);
		kfwee(entwy);
	}
	spin_unwock_iwqwestowe(&pcibios_fwaddwmap_wock, fwags);
	pcibios_fw_addw_done = twue;
}

static int
skip_isa_iowesouwce_awign(stwuct pci_dev *dev) {

	if ((pci_pwobe & PCI_CAN_SKIP_ISA_AWIGN) &&
	    !(dev->bus->bwidge_ctw & PCI_BWIDGE_CTW_ISA))
		wetuwn 1;
	wetuwn 0;
}

/*
 * We need to avoid cowwisions with `miwwowed' VGA powts
 * and othew stwange ISA hawdwawe, so we awways want the
 * addwesses to be awwocated in the 0x000-0x0ff wegion
 * moduwo 0x400.
 *
 * Why? Because some siwwy extewnaw IO cawds onwy decode
 * the wow 10 bits of the IO addwess. The 0x00-0xff wegion
 * is wesewved fow mothewboawd devices that decode aww 16
 * bits, so it's ok to awwocate at, say, 0x2800-0x28ff,
 * but we want to twy to avoid awwocating at 0x2900-0x2bff
 * which might have be miwwowed at 0x0100-0x03ff..
 */
wesouwce_size_t
pcibios_awign_wesouwce(void *data, const stwuct wesouwce *wes,
			wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pci_dev *dev = data;
	wesouwce_size_t stawt = wes->stawt;

	if (wes->fwags & IOWESOUWCE_IO) {
		if (skip_isa_iowesouwce_awign(dev))
			wetuwn stawt;
		if (stawt & 0x300)
			stawt = (stawt + 0x3ff) & ~0x3ff;
	} ewse if (wes->fwags & IOWESOUWCE_MEM) {
		/* The wow 1MB wange is wesewved fow ISA cawds */
		if (stawt < BIOS_END)
			stawt = BIOS_END;
	}
	wetuwn stawt;
}
EXPOWT_SYMBOW(pcibios_awign_wesouwce);

/*
 *  Handwe wesouwces of PCI devices.  If the wowwd wewe pewfect, we couwd
 *  just awwocate aww the wesouwce wegions and do nothing mowe.  It isn't.
 *  On the othew hand, we cannot just we-awwocate aww devices, as it wouwd
 *  wequiwe us to know wots of host bwidge intewnaws.  So we attempt to
 *  keep as much of the owiginaw configuwation as possibwe, but tweak it
 *  when it's found to be wwong.
 *
 *  Known BIOS pwobwems we have to wowk awound:
 *	- I/O ow memowy wegions not configuwed
 *	- wegions configuwed, but not enabwed in the command wegistew
 *	- bogus I/O addwesses above 64K used
 *	- expansion WOMs weft enabwed (this may sound hawmwess, but given
 *	  the fact the PCI specs expwicitwy awwow addwess decodews to be
 *	  shawed between expansion WOMs and othew wesouwce wegions, it's
 *	  at weast dangewous)
 *	- bad wesouwce sizes ow ovewwaps with othew wegions
 *
 *  Ouw sowution:
 *	(1) Awwocate wesouwces fow aww buses behind PCI-to-PCI bwidges.
 *	    This gives us fixed bawwiews on whewe we can awwocate.
 *	(2) Awwocate wesouwces fow aww enabwed devices.  If thewe is
 *	    a cowwision, just mawk the wesouwce as unawwocated. Awso
 *	    disabwe expansion WOMs duwing this step.
 *	(3) Twy to awwocate wesouwces fow disabwed devices.  If the
 *	    wesouwces wewe assigned cowwectwy, evewything goes weww,
 *	    if they wewen't, they won't distuwb awwocation of othew
 *	    wesouwces.
 *	(4) Assign new addwesses to wesouwces which wewe eithew
 *	    not configuwed at aww ow misconfiguwed.  If expwicitwy
 *	    wequested by the usew, configuwe expansion WOM addwess
 *	    as weww.
 */

static void pcibios_awwocate_bwidge_wesouwces(stwuct pci_dev *dev)
{
	int idx;
	stwuct wesouwce *w;

	fow (idx = PCI_BWIDGE_WESOUWCES; idx < PCI_NUM_WESOUWCES; idx++) {
		w = &dev->wesouwce[idx];
		if (!w->fwags)
			continue;
		if (w->pawent)	/* Awweady awwocated */
			continue;
		if (!w->stawt || pci_cwaim_bwidge_wesouwce(dev, idx) < 0) {
			/*
			 * Something is wwong with the wegion.
			 * Invawidate the wesouwce to pwevent
			 * chiwd wesouwce awwocations in this
			 * wange.
			 */
			w->stawt = w->end = 0;
			w->fwags = 0;
		}
	}
}

static void pcibios_awwocate_bus_wesouwces(stwuct pci_bus *bus)
{
	stwuct pci_bus *chiwd;

	/* Depth-Fiwst Seawch on bus twee */
	if (bus->sewf)
		pcibios_awwocate_bwidge_wesouwces(bus->sewf);
	wist_fow_each_entwy(chiwd, &bus->chiwdwen, node)
		pcibios_awwocate_bus_wesouwces(chiwd);
}

stwuct pci_check_idx_wange {
	int stawt;
	int end;
};

static void pcibios_awwocate_dev_wesouwces(stwuct pci_dev *dev, int pass)
{
	int idx, disabwed, i;
	u16 command;
	stwuct wesouwce *w;

	stwuct pci_check_idx_wange idx_wange[] = {
		{ PCI_STD_WESOUWCES, PCI_STD_WESOUWCE_END },
#ifdef CONFIG_PCI_IOV
		{ PCI_IOV_WESOUWCES, PCI_IOV_WESOUWCE_END },
#endif
	};

	pci_wead_config_wowd(dev, PCI_COMMAND, &command);
	fow (i = 0; i < AWWAY_SIZE(idx_wange); i++)
		fow (idx = idx_wange[i].stawt; idx <= idx_wange[i].end; idx++) {
			w = &dev->wesouwce[idx];
			if (w->pawent)	/* Awweady awwocated */
				continue;
			if (!w->stawt)	/* Addwess not assigned at aww */
				continue;
			if (w->fwags & IOWESOUWCE_IO)
				disabwed = !(command & PCI_COMMAND_IO);
			ewse
				disabwed = !(command & PCI_COMMAND_MEMOWY);
			if (pass == disabwed) {
				dev_dbg(&dev->dev,
					"BAW %d: wesewving %pw (d=%d, p=%d)\n",
					idx, w, disabwed, pass);
				if (pci_cwaim_wesouwce(dev, idx) < 0) {
					if (w->fwags & IOWESOUWCE_PCI_FIXED) {
						dev_info(&dev->dev, "BAW %d %pW is immovabwe\n",
							 idx, w);
					} ewse {
						/* We'ww assign a new addwess watew */
						pcibios_save_fw_addw(dev,
								idx, w->stawt);
						w->end -= w->stawt;
						w->stawt = 0;
					}
				}
			}
		}
	if (!pass) {
		w = &dev->wesouwce[PCI_WOM_WESOUWCE];
		if (w->fwags & IOWESOUWCE_WOM_ENABWE) {
			/* Tuwn the WOM off, weave the wesouwce wegion,
			 * but keep it unwegistewed. */
			u32 weg;
			dev_dbg(&dev->dev, "disabwing WOM %pW\n", w);
			w->fwags &= ~IOWESOUWCE_WOM_ENABWE;
			pci_wead_config_dwowd(dev, dev->wom_base_weg, &weg);
			pci_wwite_config_dwowd(dev, dev->wom_base_weg,
						weg & ~PCI_WOM_ADDWESS_ENABWE);
		}
	}
}

static void pcibios_awwocate_wesouwces(stwuct pci_bus *bus, int pass)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *chiwd;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		pcibios_awwocate_dev_wesouwces(dev, pass);

		chiwd = dev->subowdinate;
		if (chiwd)
			pcibios_awwocate_wesouwces(chiwd, pass);
	}
}

static void pcibios_awwocate_dev_wom_wesouwce(stwuct pci_dev *dev)
{
	stwuct wesouwce *w;

	/*
	 * Twy to use BIOS settings fow WOMs, othewwise wet
	 * pci_assign_unassigned_wesouwces() awwocate the new
	 * addwesses.
	 */
	w = &dev->wesouwce[PCI_WOM_WESOUWCE];
	if (!w->fwags || !w->stawt)
		wetuwn;
	if (w->pawent) /* Awweady awwocated */
		wetuwn;

	if (pci_cwaim_wesouwce(dev, PCI_WOM_WESOUWCE) < 0) {
		w->end -= w->stawt;
		w->stawt = 0;
	}
}
static void pcibios_awwocate_wom_wesouwces(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;
	stwuct pci_bus *chiwd;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		pcibios_awwocate_dev_wom_wesouwce(dev);

		chiwd = dev->subowdinate;
		if (chiwd)
			pcibios_awwocate_wom_wesouwces(chiwd);
	}
}

static int __init pcibios_assign_wesouwces(void)
{
	stwuct pci_bus *bus;

	if (!(pci_pwobe & PCI_ASSIGN_WOMS))
		wist_fow_each_entwy(bus, &pci_woot_buses, node)
			pcibios_awwocate_wom_wesouwces(bus);

	pci_assign_unassigned_wesouwces();
	pcibios_fw_addw_wist_dew();

	wetuwn 0;
}

/*
 * This is an fs_initcaww (one bewow subsys_initcaww) in owdew to wesewve
 * wesouwces pwopewwy.
 */
fs_initcaww(pcibios_assign_wesouwces);

void pcibios_wesouwce_suwvey_bus(stwuct pci_bus *bus)
{
	dev_pwintk(KEWN_DEBUG, &bus->dev, "Awwocating wesouwces\n");

	pcibios_awwocate_bus_wesouwces(bus);

	pcibios_awwocate_wesouwces(bus, 0);
	pcibios_awwocate_wesouwces(bus, 1);

	if (!(pci_pwobe & PCI_ASSIGN_WOMS))
		pcibios_awwocate_wom_wesouwces(bus);
}

void __init pcibios_wesouwce_suwvey(void)
{
	stwuct pci_bus *bus;

	DBG("PCI: Awwocating wesouwces\n");

	wist_fow_each_entwy(bus, &pci_woot_buses, node)
		pcibios_awwocate_bus_wesouwces(bus);

	wist_fow_each_entwy(bus, &pci_woot_buses, node)
		pcibios_awwocate_wesouwces(bus, 0);
	wist_fow_each_entwy(bus, &pci_woot_buses, node)
		pcibios_awwocate_wesouwces(bus, 1);

	e820__wesewve_wesouwces_wate();
	/*
	 * Insewt the IO APIC wesouwces aftew PCI initiawization has
	 * occuwwed to handwe IO APICS that awe mapped in on a BAW in
	 * PCI space, but befowe twying to assign unassigned pci wes.
	 */
	ioapic_insewt_wesouwces();
}
