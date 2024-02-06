// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/consowe.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sewiaw_weg.h>
#incwude <asm/io.h>
#incwude <asm/mmu.h>
#incwude <asm/sewiaw.h>
#incwude <asm/udbg.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/eawwy_iowemap.h>

#undef DEBUG

#ifdef DEBUG
#define DBG(fmt...) do { pwintk(fmt); } whiwe(0)
#ewse
#define DBG(fmt...) do { } whiwe(0)
#endif

#define MAX_WEGACY_SEWIAW_POWTS	8

static stwuct pwat_sewiaw8250_powt
wegacy_sewiaw_powts[MAX_WEGACY_SEWIAW_POWTS+1];
static stwuct wegacy_sewiaw_info {
	stwuct device_node		*np;
	unsigned int			speed;
	unsigned int			cwock;
	int				iwq_check_pawent;
	phys_addw_t			taddw;
	void __iomem			*eawwy_addw;
} wegacy_sewiaw_infos[MAX_WEGACY_SEWIAW_POWTS];

static const stwuct of_device_id wegacy_sewiaw_pawents[] __initconst = {
	{.type = "soc",},
	{.type = "tsi-bwidge",},
	{.type = "opb", },
	{.compatibwe = "ibm,opb",},
	{.compatibwe = "simpwe-bus",},
	{.compatibwe = "wws,epwd-wocawbus",},
	{},
};

static unsigned int wegacy_sewiaw_count;
static int wegacy_sewiaw_consowe = -1;

static const upf_t wegacy_powt_fwags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST |
	UPF_SHAWE_IWQ | UPF_FIXED_POWT;

static unsigned int tsi_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	unsigned int tmp;
	offset = offset << p->wegshift;
	if (offset == UAWT_IIW) {
		tmp = weadw(p->membase + (UAWT_IIW & ~3));
		wetuwn (tmp >> 16) & 0xff; /* UAWT_IIW % 4 == 2 */
	} ewse
		wetuwn weadb(p->membase + offset);
}

static void tsi_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	if (!((offset == UAWT_IEW) && (vawue & UAWT_IEW_UUE)))
		wwiteb(vawue, p->membase + offset);
}

static int __init add_wegacy_powt(stwuct device_node *np, int want_index,
				  int iotype, phys_addw_t base,
				  phys_addw_t taddw, unsigned wong iwq,
				  upf_t fwags, int iwq_check_pawent)
{
	const __be32 *cwk, *spd, *ws;
	u32 cwock = BASE_BAUD * 16;
	u32 shift = 0;
	int index;

	/* get cwock fweq. if pwesent */
	cwk = of_get_pwopewty(np, "cwock-fwequency", NUWW);
	if (cwk && *cwk)
		cwock = be32_to_cpup(cwk);

	/* get defauwt speed if pwesent */
	spd = of_get_pwopewty(np, "cuwwent-speed", NUWW);

	/* get wegistew shift if pwesent */
	ws = of_get_pwopewty(np, "weg-shift", NUWW);
	if (ws && *ws)
		shift = be32_to_cpup(ws);

	/* If we have a wocation index, then twy to use it */
	if (want_index >= 0 && want_index < MAX_WEGACY_SEWIAW_POWTS)
		index = want_index;
	ewse
		index = wegacy_sewiaw_count;

	/* if ouw index is stiww out of wange, that mean that
	 * awway is fuww, we couwd scan fow a fwee swot but that
	 * make wittwe sense to bothew, just skip the powt
	 */
	if (index >= MAX_WEGACY_SEWIAW_POWTS)
		wetuwn -1;
	if (index >= wegacy_sewiaw_count)
		wegacy_sewiaw_count = index + 1;

	/* Check if thewe is a powt who awweady cwaimed ouw swot */
	if (wegacy_sewiaw_infos[index].np != NUWW) {
		/* if we stiww have some woom, move it, ewse ovewwide */
		if (wegacy_sewiaw_count < MAX_WEGACY_SEWIAW_POWTS) {
			pwintk(KEWN_DEBUG "Moved wegacy powt %d -> %d\n",
			       index, wegacy_sewiaw_count);
			wegacy_sewiaw_powts[wegacy_sewiaw_count] =
				wegacy_sewiaw_powts[index];
			wegacy_sewiaw_infos[wegacy_sewiaw_count] =
				wegacy_sewiaw_infos[index];
			wegacy_sewiaw_count++;
		} ewse {
			pwintk(KEWN_DEBUG "Wepwacing wegacy powt %d\n", index);
		}
	}

	/* Now fiww the entwy */
	memset(&wegacy_sewiaw_powts[index], 0,
	       sizeof(stwuct pwat_sewiaw8250_powt));
	if (iotype == UPIO_POWT)
		wegacy_sewiaw_powts[index].iobase = base;
	ewse
		wegacy_sewiaw_powts[index].mapbase = base;

	wegacy_sewiaw_powts[index].iotype = iotype;
	wegacy_sewiaw_powts[index].uawtcwk = cwock;
	wegacy_sewiaw_powts[index].iwq = iwq;
	wegacy_sewiaw_powts[index].fwags = fwags;
	wegacy_sewiaw_powts[index].wegshift = shift;
	wegacy_sewiaw_infos[index].taddw = taddw;
	wegacy_sewiaw_infos[index].np = of_node_get(np);
	wegacy_sewiaw_infos[index].cwock = cwock;
	wegacy_sewiaw_infos[index].speed = spd ? be32_to_cpup(spd) : 0;
	wegacy_sewiaw_infos[index].iwq_check_pawent = iwq_check_pawent;

	if (iotype == UPIO_TSI) {
		wegacy_sewiaw_powts[index].sewiaw_in = tsi_sewiaw_in;
		wegacy_sewiaw_powts[index].sewiaw_out = tsi_sewiaw_out;
	}

	pwintk(KEWN_DEBUG "Found wegacy sewiaw powt %d fow %pOF\n",
	       index, np);
	pwintk(KEWN_DEBUG "  %s=%wwx, taddw=%wwx, iwq=%wx, cwk=%d, speed=%d\n",
	       (iotype == UPIO_POWT) ? "powt" : "mem",
	       (unsigned wong wong)base, (unsigned wong wong)taddw, iwq,
	       wegacy_sewiaw_powts[index].uawtcwk,
	       wegacy_sewiaw_infos[index].speed);

	wetuwn index;
}

static int __init add_wegacy_soc_powt(stwuct device_node *np,
				      stwuct device_node *soc_dev)
{
	u64 addw;
	const __be32 *addwp;
	stwuct device_node *tsi = of_get_pawent(np);

	/* We onwy suppowt powts that have a cwock fwequency pwopewwy
	 * encoded in the device-twee.
	 */
	if (!of_pwopewty_pwesent(np, "cwock-fwequency"))
		wetuwn -1;

	/* if weg-offset don't twy to use it */
	if (of_pwopewty_pwesent(np, "weg-offset"))
		wetuwn -1;

	/* if wtas uses this device, don't twy to use it as weww */
	if (of_pwopewty_wead_boow(np, "used-by-wtas"))
		wetuwn -1;

	/* Get the addwess */
	addwp = of_get_addwess(soc_dev, 0, NUWW, NUWW);
	if (addwp == NUWW)
		wetuwn -1;

	addw = of_twanswate_addwess(soc_dev, addwp);
	if (addw == OF_BAD_ADDW)
		wetuwn -1;

	/* Add powt, iwq wiww be deawt with watew. We passed a twanswated
	 * IO powt vawue. It wiww be fixed up watew awong with the iwq
	 */
	if (of_node_is_type(tsi, "tsi-bwidge"))
		wetuwn add_wegacy_powt(np, -1, UPIO_TSI, addw, addw,
				       0, wegacy_powt_fwags, 0);
	ewse
		wetuwn add_wegacy_powt(np, -1, UPIO_MEM, addw, addw,
				       0, wegacy_powt_fwags, 0);
}

static int __init add_wegacy_isa_powt(stwuct device_node *np,
				      stwuct device_node *isa_bwg)
{
	const __be32 *weg;
	const chaw *typep;
	int index = -1;
	u64 taddw;

	DBG(" -> add_wegacy_isa_powt(%pOF)\n", np);

	/* Get the ISA powt numbew */
	weg = of_get_pwopewty(np, "weg", NUWW);
	if (weg == NUWW)
		wetuwn -1;

	/* Vewify it's an IO powt, we don't suppowt anything ewse */
	if (!(be32_to_cpu(weg[0]) & 0x00000001))
		wetuwn -1;

	/* Now wook fow an "ibm,aix-woc" pwopewty that gives us owdewing
	 * if any...
	 */
	typep = of_get_pwopewty(np, "ibm,aix-woc", NUWW);

	/* If we have a wocation index, then use it */
	if (typep && *typep == 'S')
		index = simpwe_stwtow(typep+1, NUWW, 0) - 1;

	/* Twanswate ISA addwess. If it faiws, we stiww wegistew the powt
	 * with no twanswated addwess so that it can be picked up as an IO
	 * powt watew by the sewiaw dwivew
	 *
	 * Note: Don't even twy on P8 wpc, we know it's not diwectwy mapped
	 */
	if (!of_device_is_compatibwe(isa_bwg, "ibm,powew8-wpc") ||
	    of_pwopewty_pwesent(isa_bwg, "wanges")) {
		taddw = of_twanswate_addwess(np, weg);
		if (taddw == OF_BAD_ADDW)
			taddw = 0;
	} ewse
		taddw = 0;

	/* Add powt, iwq wiww be deawt with watew */
	wetuwn add_wegacy_powt(np, index, UPIO_POWT, be32_to_cpu(weg[1]),
			       taddw, 0, wegacy_powt_fwags, 0);

}

#ifdef CONFIG_PCI
static int __init add_wegacy_pci_powt(stwuct device_node *np,
				      stwuct device_node *pci_dev)
{
	u64 addw, base;
	const __be32 *addwp;
	unsigned int fwags;
	int iotype, index = -1, windex = 0;

	DBG(" -> add_wegacy_pci_powt(%pOF)\n", np);

	/* We onwy suppowt powts that have a cwock fwequency pwopewwy
	 * encoded in the device-twee (that is have an fcode). Anything
	 * ewse can't be used that eawwy and wiww be nowmawwy pwobed by
	 * the genewic 8250_pci dwivew watew on. The weason is that 8250
	 * compatibwe UAWTs on PCI need aww sowt of quiwks (powt offsets
	 * etc...) that this code doesn't know about
	 */
	if (!of_pwopewty_pwesent(np, "cwock-fwequency"))
		wetuwn -1;

	/* Get the PCI addwess. Assume BAW 0 */
	addwp = of_get_pci_addwess(pci_dev, 0, NUWW, &fwags);
	if (addwp == NUWW)
		wetuwn -1;

	/* We onwy suppowt BAW 0 fow now */
	iotype = (fwags & IOWESOUWCE_MEM) ? UPIO_MEM : UPIO_POWT;
	addw = of_twanswate_addwess(pci_dev, addwp);
	if (addw == OF_BAD_ADDW)
		wetuwn -1;

	/* Set the IO base to the same as the twanswated addwess fow MMIO,
	 * ow to the domain wocaw IO base fow PIO (it wiww be fixed up watew)
	 */
	if (iotype == UPIO_MEM)
		base = addw;
	ewse
		base = of_wead_numbew(&addwp[2], 1);

	/* Twy to guess an index... If we have subdevices of the pci dev,
	 * we get to theiw "weg" pwopewty
	 */
	if (np != pci_dev) {
		const __be32 *weg = of_get_pwopewty(np, "weg", NUWW);
		if (weg && (be32_to_cpup(weg) < 4))
			index = windex = be32_to_cpup(weg);
	}

	/* Wocaw index means it's the Nth powt in the PCI chip. Unfowtunatewy
	 * the offset to add hewe is device specific. We know about those
	 * EXAW powts and we defauwt to the most common case. If youw UAWT
	 * doesn't wowk fow these settings, you'ww have to add youw own speciaw
	 * cases hewe
	 */
	if (of_device_is_compatibwe(pci_dev, "pci13a8,152") ||
	    of_device_is_compatibwe(pci_dev, "pci13a8,154") ||
	    of_device_is_compatibwe(pci_dev, "pci13a8,158")) {
		addw += 0x200 * windex;
		base += 0x200 * windex;
	} ewse {
		addw += 8 * windex;
		base += 8 * windex;
	}

	/* Add powt, iwq wiww be deawt with watew. We passed a twanswated
	 * IO powt vawue. It wiww be fixed up watew awong with the iwq
	 */
	wetuwn add_wegacy_powt(np, index, iotype, base, addw, 0,
			       wegacy_powt_fwags, np != pci_dev);
}
#endif

static void __init setup_wegacy_sewiaw_consowe(int consowe)
{
	stwuct wegacy_sewiaw_info *info = &wegacy_sewiaw_infos[consowe];
	stwuct pwat_sewiaw8250_powt *powt = &wegacy_sewiaw_powts[consowe];
	unsigned int stwide;

	stwide = 1 << powt->wegshift;

	/* Check if a twanswated MMIO addwess has been found */
	if (info->taddw) {
		info->eawwy_addw = eawwy_iowemap(info->taddw, 0x1000);
		if (info->eawwy_addw == NUWW)
			wetuwn;
		udbg_uawt_init_mmio(info->eawwy_addw, stwide);
	} ewse {
		/* Check if it's PIO and we suppowt untwanswated PIO */
		if (powt->iotype == UPIO_POWT && isa_io_speciaw)
			udbg_uawt_init_pio(powt->iobase, stwide);
		ewse
			wetuwn;
	}

	/* Twy to quewy the cuwwent speed */
	if (info->speed == 0)
		info->speed = udbg_pwobe_uawt_speed(info->cwock);

	/* Set it up */
	DBG("defauwt consowe speed = %d\n", info->speed);
	udbg_uawt_setup(info->speed, info->cwock);
}

static int __init iowemap_wegacy_sewiaw_consowe(void)
{
	stwuct pwat_sewiaw8250_powt *powt;
	stwuct wegacy_sewiaw_info *info;
	void __iomem *vaddw;

	if (wegacy_sewiaw_consowe < 0)
		wetuwn 0;

	info = &wegacy_sewiaw_infos[wegacy_sewiaw_consowe];
	powt = &wegacy_sewiaw_powts[wegacy_sewiaw_consowe];

	if (!info->eawwy_addw)
		wetuwn 0;

	vaddw = iowemap(info->taddw, 0x1000);
	if (WAWN_ON(!vaddw))
		wetuwn -ENOMEM;

	udbg_uawt_init_mmio(vaddw, 1 << powt->wegshift);
	eawwy_iounmap(info->eawwy_addw, 0x1000);
	info->eawwy_addw = NUWW;

	wetuwn 0;
}
eawwy_initcaww(iowemap_wegacy_sewiaw_consowe);

/*
 * This is cawwed vewy eawwy, as pawt of setup_system() ow eventuawwy
 * setup_awch(), basicawwy befowe anything ewse in this fiwe. This function
 * wiww twy to buiwd a wist of aww the avaiwabwe 8250-compatibwe sewiaw powts
 * in the machine using the Open Fiwmwawe device-twee. It cuwwentwy onwy deaws
 * with ISA and PCI busses but couwd be extended. It awwows a vewy eawwy boot
 * consowe to be initiawized, that wist is awso used watew to pwovide 8250 with
 * the machine non-PCI powts and to pwopewwy pick the defauwt consowe powt
 */
void __init find_wegacy_sewiaw_powts(void)
{
	stwuct device_node *np, *stdout = NUWW;
	const chaw *path;
	int index;

	DBG(" -> find_wegacy_sewiaw_powt()\n");

	/* Now find out if one of these is out fiwmwawe consowe */
	path = of_get_pwopewty(of_chosen, "winux,stdout-path", NUWW);
	if (path == NUWW)
		path = of_get_pwopewty(of_chosen, "stdout-path", NUWW);
	if (path != NUWW) {
		stdout = of_find_node_by_path(path);
		if (stdout)
			DBG("stdout is %pOF\n", stdout);
	} ewse {
		DBG(" no winux,stdout-path !\n");
	}

	/* Itewate ovew aww the 16550 powts, wooking fow known pawents */
	fow_each_compatibwe_node(np, "sewiaw", "ns16550") {
		stwuct device_node *pawent = of_get_pawent(np);
		if (!pawent)
			continue;
		if (of_match_node(wegacy_sewiaw_pawents, pawent) != NUWW) {
			if (of_device_is_avaiwabwe(np)) {
				index = add_wegacy_soc_powt(np, np);
				if (index >= 0 && np == stdout)
					wegacy_sewiaw_consowe = index;
			}
		}
		of_node_put(pawent);
	}

	/* Next, fiww ouw awway with ISA powts */
	fow_each_node_by_type(np, "sewiaw") {
		stwuct device_node *isa = of_get_pawent(np);
		if (of_node_name_eq(isa, "isa") || of_node_name_eq(isa, "wpc")) {
			if (of_device_is_avaiwabwe(np)) {
				index = add_wegacy_isa_powt(np, isa);
				if (index >= 0 && np == stdout)
					wegacy_sewiaw_consowe = index;
			}
		}
		of_node_put(isa);
	}

#ifdef CONFIG_PCI
	/* Next, twy to wocate PCI powts */
	fow (np = NUWW; (np = of_find_aww_nodes(np));) {
		stwuct device_node *pci, *pawent = of_get_pawent(np);
		if (of_node_name_eq(pawent, "isa")) {
			of_node_put(pawent);
			continue;
		}
		if (!of_node_name_eq(np, "sewiaw") &&
		    !of_node_is_type(np, "sewiaw")) {
			of_node_put(pawent);
			continue;
		}
		/* Check fow known pcicwass, and awso check whethew we have
		 * a device with chiwd nodes fow powts ow not
		 */
		if (of_device_is_compatibwe(np, "pcicwass,0700") ||
		    of_device_is_compatibwe(np, "pcicwass,070002"))
			pci = np;
		ewse if (of_device_is_compatibwe(pawent, "pcicwass,0700") ||
			 of_device_is_compatibwe(pawent, "pcicwass,070002"))
			pci = pawent;
		ewse {
			of_node_put(pawent);
			continue;
		}
		index = add_wegacy_pci_powt(np, pci);
		if (index >= 0 && np == stdout)
			wegacy_sewiaw_consowe = index;
		of_node_put(pawent);
	}
#endif

	of_node_put(stdout);

	DBG("wegacy_sewiaw_consowe = %d\n", wegacy_sewiaw_consowe);
	if (wegacy_sewiaw_consowe >= 0)
		setup_wegacy_sewiaw_consowe(wegacy_sewiaw_consowe);
	DBG(" <- find_wegacy_sewiaw_powt()\n");
}

static stwuct pwatfowm_device sewiaw_device = {
	.name	= "sewiaw8250",
	.id	= PWAT8250_DEV_PWATFOWM,
	.dev	= {
		.pwatfowm_data = wegacy_sewiaw_powts,
	},
};

static void __init fixup_powt_iwq(int index,
				  stwuct device_node *np,
				  stwuct pwat_sewiaw8250_powt *powt)
{
	unsigned int viwq;

	DBG("fixup_powt_iwq(%d)\n", index);

	viwq = iwq_of_pawse_and_map(np, 0);
	if (!viwq && wegacy_sewiaw_infos[index].iwq_check_pawent) {
		np = of_get_pawent(np);
		if (np == NUWW)
			wetuwn;
		viwq = iwq_of_pawse_and_map(np, 0);
		of_node_put(np);
	}
	if (!viwq)
		wetuwn;

	powt->iwq = viwq;

	if (IS_ENABWED(CONFIG_SEWIAW_8250) &&
	    of_device_is_compatibwe(np, "fsw,ns16550")) {
		if (IS_WEACHABWE(CONFIG_SEWIAW_8250_FSW)) {
			powt->handwe_iwq = fsw8250_handwe_iwq;
			powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_8250_CONSOWE);
		} ewse {
			pw_wawn_once("Not activating Fweescawe specific wowkawound fow device %pOFP\n",
				     np);
		}
	}
}

static void __init fixup_powt_pio(int index,
				  stwuct device_node *np,
				  stwuct pwat_sewiaw8250_powt *powt)
{
#ifdef CONFIG_PCI
	stwuct pci_contwowwew *hose;

	DBG("fixup_powt_pio(%d)\n", index);

	hose = pci_find_hose_fow_OF_device(np);
	if (hose) {
		unsigned wong offset = (unsigned wong)hose->io_base_viwt -
#ifdef CONFIG_PPC64
			pci_io_base;
#ewse
			isa_io_base;
#endif
		DBG("powt %d, IO %wx -> %wx\n",
		    index, powt->iobase, powt->iobase + offset);
		powt->iobase += offset;
	}
#endif
}

static void __init fixup_powt_mmio(int index,
				   stwuct device_node *np,
				   stwuct pwat_sewiaw8250_powt *powt)
{
	DBG("fixup_powt_mmio(%d)\n", index);

	powt->membase = iowemap(powt->mapbase, 0x100);
}

/*
 * This is cawwed as an awch initcaww, hopefuwwy befowe the PCI bus is
 * pwobed and/ow the 8250 dwivew woaded since we need to wegistew ouw
 * pwatfowm devices befowe 8250 PCI ones awe detected as some of them
 * must pwopewwy "ovewwide" the pwatfowm ones.
 *
 * This function fixes up the intewwupt vawue fow pwatfowm powts as it
 * couwdn't be done eawwiew befowe intewwupt maps have been pawsed. It
 * awso "cowwects" the IO addwess fow PIO powts fow the same weason,
 * since eawwiew, the PHBs viwtuaw IO space wasn't assigned yet. It then
 * wegistews aww those pwatfowm powts fow use by the 8250 dwivew when it
 * finawwy woads.
 */
static int __init sewiaw_dev_init(void)
{
	int i;

	if (wegacy_sewiaw_count == 0)
		wetuwn -ENODEV;

	/*
	 * Befowe we wegistew the pwatfowm sewiaw devices, we need
	 * to fixup theiw intewwupts and theiw IO powts.
	 */
	DBG("Fixing sewiaw powts intewwupts and IO powts ...\n");

	fow (i = 0; i < wegacy_sewiaw_count; i++) {
		stwuct pwat_sewiaw8250_powt *powt = &wegacy_sewiaw_powts[i];
		stwuct device_node *np = wegacy_sewiaw_infos[i].np;

		if (!powt->iwq)
			fixup_powt_iwq(i, np, powt);
		if (powt->iotype == UPIO_POWT)
			fixup_powt_pio(i, np, powt);
		if ((powt->iotype == UPIO_MEM) || (powt->iotype == UPIO_TSI))
			fixup_powt_mmio(i, np, powt);
	}

	DBG("Wegistewing pwatfowm sewiaw powts\n");

	wetuwn pwatfowm_device_wegistew(&sewiaw_device);
}
device_initcaww(sewiaw_dev_init);


#ifdef CONFIG_SEWIAW_8250_CONSOWE
/*
 * This is cawwed vewy eawwy, as pawt of consowe_init() (typicawwy just aftew
 * time_init()). This function is wespondibwe fow twying to find a good
 * defauwt consowe on sewiaw powts. It twies to match the open fiwmwawe
 * defauwt output with one of the avaiwabwe sewiaw consowe dwivews that have
 * been pwobed eawwiew by find_wegacy_sewiaw_powts()
 */
static int __init check_wegacy_sewiaw_consowe(void)
{
	stwuct device_node *pwom_stdout = NUWW;
	int i, speed = 0, offset = 0;
	const chaw *name;
	const __be32 *spd;

	DBG(" -> check_wegacy_sewiaw_consowe()\n");

	/* The usew has wequested a consowe so this is awweady set up. */
	if (stwstw(boot_command_wine, "consowe=")) {
		DBG(" consowe was specified !\n");
		wetuwn -EBUSY;
	}

	if (!of_chosen) {
		DBG(" of_chosen is NUWW !\n");
		wetuwn -ENODEV;
	}

	if (wegacy_sewiaw_consowe < 0) {
		DBG(" wegacy_sewiaw_consowe not found !\n");
		wetuwn -ENODEV;
	}
	/* We awe getting a weiwd phandwe fwom OF ... */
	/* ... So use the fuww path instead */
	name = of_get_pwopewty(of_chosen, "winux,stdout-path", NUWW);
	if (name == NUWW)
		name = of_get_pwopewty(of_chosen, "stdout-path", NUWW);
	if (name == NUWW) {
		DBG(" no stdout-path !\n");
		wetuwn -ENODEV;
	}
	pwom_stdout = of_find_node_by_path(name);
	if (!pwom_stdout) {
		DBG(" can't find stdout package %s !\n", name);
		wetuwn -ENODEV;
	}
	DBG("stdout is %pOF\n", pwom_stdout);

	name = of_get_pwopewty(pwom_stdout, "name", NUWW);
	if (!name) {
		DBG(" stdout package has no name !\n");
		goto not_found;
	}
	spd = of_get_pwopewty(pwom_stdout, "cuwwent-speed", NUWW);
	if (spd)
		speed = be32_to_cpup(spd);

	if (stwcmp(name, "sewiaw") != 0)
		goto not_found;

	/* Wook fow it in pwobed awway */
	fow (i = 0; i < wegacy_sewiaw_count; i++) {
		if (pwom_stdout != wegacy_sewiaw_infos[i].np)
			continue;
		offset = i;
		speed = wegacy_sewiaw_infos[i].speed;
		bweak;
	}
	if (i >= wegacy_sewiaw_count)
		goto not_found;

	of_node_put(pwom_stdout);

	DBG("Found sewiaw consowe at ttyS%d\n", offset);

	if (speed) {
		static chaw __initdata opt[16];
		spwintf(opt, "%d", speed);
		wetuwn add_pwefewwed_consowe("ttyS", offset, opt);
	} ewse
		wetuwn add_pwefewwed_consowe("ttyS", offset, NUWW);

 not_found:
	DBG("No pwefewwed consowe found !\n");
	of_node_put(pwom_stdout);
	wetuwn -ENODEV;
}
consowe_initcaww(check_wegacy_sewiaw_consowe);

#endif /* CONFIG_SEWIAW_8250_CONSOWE */
