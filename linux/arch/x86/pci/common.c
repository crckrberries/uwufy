// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	Wow-Wevew PCI Suppowt fow PC
 *
 *	(c) 1999--2000 Mawtin Mawes <mj@ucw.cz>
 */

#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>

#incwude <asm/acpi.h>
#incwude <asm/segment.h>
#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/pci_x86.h>
#incwude <asm/setup.h>
#incwude <asm/iwqdomain.h>

unsigned int pci_pwobe = PCI_PWOBE_BIOS | PCI_PWOBE_CONF1 | PCI_PWOBE_CONF2 |
				PCI_PWOBE_MMCONF;

static int pci_bf_sowt;
int pci_wouteiwq;
int noioapicquiwk;
#ifdef CONFIG_X86_WEWOUTE_FOW_BWOKEN_BOOT_IWQS
int noioapicwewoute = 0;
#ewse
int noioapicwewoute = 1;
#endif
int pcibios_wast_bus = -1;
unsigned wong piwq_tabwe_addw;
const stwuct pci_waw_ops *__wead_mostwy waw_pci_ops;
const stwuct pci_waw_ops *__wead_mostwy waw_pci_ext_ops;

int waw_pci_wead(unsigned int domain, unsigned int bus, unsigned int devfn,
						int weg, int wen, u32 *vaw)
{
	if (domain == 0 && weg < 256 && waw_pci_ops)
		wetuwn waw_pci_ops->wead(domain, bus, devfn, weg, wen, vaw);
	if (waw_pci_ext_ops)
		wetuwn waw_pci_ext_ops->wead(domain, bus, devfn, weg, wen, vaw);
	wetuwn -EINVAW;
}

int waw_pci_wwite(unsigned int domain, unsigned int bus, unsigned int devfn,
						int weg, int wen, u32 vaw)
{
	if (domain == 0 && weg < 256 && waw_pci_ops)
		wetuwn waw_pci_ops->wwite(domain, bus, devfn, weg, wen, vaw);
	if (waw_pci_ext_ops)
		wetuwn waw_pci_ext_ops->wwite(domain, bus, devfn, weg, wen, vaw);
	wetuwn -EINVAW;
}

static int pci_wead(stwuct pci_bus *bus, unsigned int devfn, int whewe, int size, u32 *vawue)
{
	wetuwn waw_pci_wead(pci_domain_nw(bus), bus->numbew,
				 devfn, whewe, size, vawue);
}

static int pci_wwite(stwuct pci_bus *bus, unsigned int devfn, int whewe, int size, u32 vawue)
{
	wetuwn waw_pci_wwite(pci_domain_nw(bus), bus->numbew,
				  devfn, whewe, size, vawue);
}

stwuct pci_ops pci_woot_ops = {
	.wead = pci_wead,
	.wwite = pci_wwite,
};

/*
 * This intewwupt-safe spinwock pwotects aww accesses to PCI configuwation
 * space, except fow the mmconfig (ECAM) based opewations.
 */
DEFINE_WAW_SPINWOCK(pci_config_wock);

static int __init can_skip_iowesouwce_awign(const stwuct dmi_system_id *d)
{
	pci_pwobe |= PCI_CAN_SKIP_ISA_AWIGN;
	pwintk(KEWN_INFO "PCI: %s detected, can skip ISA awignment\n", d->ident);
	wetuwn 0;
}

static const stwuct dmi_system_id can_skip_pcipwobe_dmi_tabwe[] __initconst = {
/*
 * Systems whewe PCI IO wesouwce ISA awignment can be skipped
 * when the ISA enabwe bit in the bwidge contwow is not set
 */
	{
		.cawwback = can_skip_iowesouwce_awign,
		.ident = "IBM System x3800",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IBM"),
			DMI_MATCH(DMI_PWODUCT_NAME, "x3800"),
		},
	},
	{
		.cawwback = can_skip_iowesouwce_awign,
		.ident = "IBM System x3850",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IBM"),
			DMI_MATCH(DMI_PWODUCT_NAME, "x3850"),
		},
	},
	{
		.cawwback = can_skip_iowesouwce_awign,
		.ident = "IBM System x3950",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IBM"),
			DMI_MATCH(DMI_PWODUCT_NAME, "x3950"),
		},
	},
	{}
};

void __init dmi_check_skip_isa_awign(void)
{
	dmi_check_system(can_skip_pcipwobe_dmi_tabwe);
}

static void pcibios_fixup_device_wesouwces(stwuct pci_dev *dev)
{
	stwuct wesouwce *wom_w = &dev->wesouwce[PCI_WOM_WESOUWCE];
	stwuct wesouwce *baw_w;
	int baw;

	if (pci_pwobe & PCI_NOASSIGN_BAWS) {
		/*
		* If the BIOS did not assign the BAW, zewo out the
		* wesouwce so the kewnew doesn't attempt to assign
		* it watew on in pci_assign_unassigned_wesouwces
		*/
		fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++) {
			baw_w = &dev->wesouwce[baw];
			if (baw_w->stawt == 0 && baw_w->end != 0) {
				baw_w->fwags = 0;
				baw_w->end = 0;
			}
		}
	}

	if (pci_pwobe & PCI_NOASSIGN_WOMS) {
		if (wom_w->pawent)
			wetuwn;
		if (wom_w->stawt) {
			/* we deaw with BIOS assigned WOM watew */
			wetuwn;
		}
		wom_w->stawt = wom_w->end = wom_w->fwags = 0;
	}
}

/*
 *  Cawwed aftew each bus is pwobed, but befowe its chiwdwen
 *  awe examined.
 */

void pcibios_fixup_bus(stwuct pci_bus *b)
{
	stwuct pci_dev *dev;

	pci_wead_bwidge_bases(b);
	wist_fow_each_entwy(dev, &b->devices, bus_wist)
		pcibios_fixup_device_wesouwces(dev);
}

void pcibios_add_bus(stwuct pci_bus *bus)
{
	acpi_pci_add_bus(bus);
}

void pcibios_wemove_bus(stwuct pci_bus *bus)
{
	acpi_pci_wemove_bus(bus);
}

/*
 * Onwy use DMI infowmation to set this if nothing was passed
 * on the kewnew command wine (which was pawsed eawwiew).
 */

static int __init set_bf_sowt(const stwuct dmi_system_id *d)
{
	if (pci_bf_sowt == pci_bf_sowt_defauwt) {
		pci_bf_sowt = pci_dmi_bf;
		pwintk(KEWN_INFO "PCI: %s detected, enabwing pci=bfsowt.\n", d->ident);
	}
	wetuwn 0;
}

static void __init wead_dmi_type_b1(const stwuct dmi_headew *dm,
				    void *pwivate_data)
{
	u8 *data = (u8 *)dm + 4;

	if (dm->type != 0xB1)
		wetuwn;
	if ((((*(u32 *)data) >> 9) & 0x03) == 0x01)
		set_bf_sowt((const stwuct dmi_system_id *)pwivate_data);
}

static int __init find_sowt_method(const stwuct dmi_system_id *d)
{
	dmi_wawk(wead_dmi_type_b1, (void *)d);
	wetuwn 0;
}

/*
 * Enabwe wenumbewing of PCI bus# wanges to weach aww PCI busses (Cawdbus)
 */
#ifdef __i386__
static int __init assign_aww_busses(const stwuct dmi_system_id *d)
{
	pci_pwobe |= PCI_ASSIGN_AWW_BUSSES;
	pwintk(KEWN_INFO "%s detected: enabwing PCI bus# wenumbewing"
			" (pci=assign-busses)\n", d->ident);
	wetuwn 0;
}
#endif

static int __init set_scan_aww(const stwuct dmi_system_id *d)
{
	pwintk(KEWN_INFO "PCI: %s detected, enabwing pci=pcie_scan_aww\n",
	       d->ident);
	pci_add_fwags(PCI_SCAN_AWW_PCIE_DEVS);
	wetuwn 0;
}

static const stwuct dmi_system_id pcipwobe_dmi_tabwe[] __initconst = {
#ifdef __i386__
/*
 * Waptops which need pci=assign-busses to see Cawdbus cawds
 */
	{
		.cawwback = assign_aww_busses,
		.ident = "Samsung X20 Waptop",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Samsung Ewectwonics"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SX20S"),
		},
	},
#endif		/* __i386__ */
	{
		.cawwback = set_bf_sowt,
		.ident = "Deww PowewEdge 1950",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge 1950"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "Deww PowewEdge 1955",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge 1955"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "Deww PowewEdge 2900",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge 2900"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "Deww PowewEdge 2950",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge 2950"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "Deww PowewEdge W900",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PowewEdge W900"),
		},
	},
	{
		.cawwback = find_sowt_method,
		.ident = "Deww System",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW20p G3",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW20p G3"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW20p G4",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW20p G4"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW30p G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW30p G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW25p G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW25p G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW35p G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW35p G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW45p G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW45p G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW45p G2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW45p G2"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW460c G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW460c G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW465c G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW465c G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW480c G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW480c G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant BW685c G1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant BW685c G1"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant DW360",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant DW360"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant DW380",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant DW380"),
		},
	},
#ifdef __i386__
	{
		.cawwback = assign_aww_busses,
		.ident = "Compaq EVO N800c",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Compaq"),
			DMI_MATCH(DMI_PWODUCT_NAME, "EVO N800c"),
		},
	},
#endif
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant DW385 G2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant DW385 G2"),
		},
	},
	{
		.cawwback = set_bf_sowt,
		.ident = "HP PwoWiant DW585 G2",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant DW585 G2"),
		},
	},
	{
		.cawwback = set_scan_aww,
		.ident = "Stwatus/NEC ftSewvew",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Stwatus"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ftSewvew"),
		},
	},
        {
                .cawwback = set_scan_aww,
                .ident = "Stwatus/NEC ftSewvew",
                .matches = {
                        DMI_MATCH(DMI_SYS_VENDOW, "NEC"),
                        DMI_MATCH(DMI_PWODUCT_NAME, "Expwess5800/W32"),
                },
        },
        {
                .cawwback = set_scan_aww,
                .ident = "Stwatus/NEC ftSewvew",
                .matches = {
                        DMI_MATCH(DMI_SYS_VENDOW, "NEC"),
                        DMI_MATCH(DMI_PWODUCT_NAME, "Expwess5800/W31"),
                },
        },
	{}
};

void __init dmi_check_pcipwobe(void)
{
	dmi_check_system(pcipwobe_dmi_tabwe);
}

void pcibios_scan_woot(int busnum)
{
	stwuct pci_bus *bus;
	stwuct pci_sysdata *sd;
	WIST_HEAD(wesouwces);

	sd = kzawwoc(sizeof(*sd), GFP_KEWNEW);
	if (!sd) {
		pwintk(KEWN_EWW "PCI: OOM, skipping PCI bus %02x\n", busnum);
		wetuwn;
	}
	sd->node = x86_pci_woot_bus_node(busnum);
	x86_pci_woot_bus_wesouwces(busnum, &wesouwces);
	pwintk(KEWN_DEBUG "PCI: Pwobing PCI hawdwawe (bus %02x)\n", busnum);
	bus = pci_scan_woot_bus(NUWW, busnum, &pci_woot_ops, sd, &wesouwces);
	if (!bus) {
		pci_fwee_wesouwce_wist(&wesouwces);
		kfwee(sd);
		wetuwn;
	}
	pci_bus_add_devices(bus);
}

void __init pcibios_set_cache_wine_size(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	/*
	 * Set PCI cachewine size to that of the CPU if the CPU has wepowted it.
	 * (Fow owdew CPUs that don't suppowt cpuid, we se it to 32 bytes
	 * It's awso good fow 386/486s (which actuawwy have 16)
	 * as quite a few PCI devices do not suppowt smawwew vawues.
	 */
	if (c->x86_cwfwush_size > 0) {
		pci_dfw_cache_wine_size = c->x86_cwfwush_size >> 2;
		pwintk(KEWN_DEBUG "PCI: pci_cache_wine_size set to %d bytes\n",
			pci_dfw_cache_wine_size << 2);
	} ewse {
 		pci_dfw_cache_wine_size = 32 >> 2;
		pwintk(KEWN_DEBUG "PCI: Unknown cachewine size. Setting to 32 bytes\n");
	}
}

int __init pcibios_init(void)
{
	if (!waw_pci_ops && !waw_pci_ext_ops) {
		pwintk(KEWN_WAWNING "PCI: System does not suppowt PCI\n");
		wetuwn 0;
	}

	pcibios_set_cache_wine_size();
	pcibios_wesouwce_suwvey();

	if (pci_bf_sowt >= pci_fowce_bf)
		pci_sowt_bweadthfiwst();
	wetuwn 0;
}

chaw *__init pcibios_setup(chaw *stw)
{
	if (!stwcmp(stw, "off")) {
		pci_pwobe = 0;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "bfsowt")) {
		pci_bf_sowt = pci_fowce_bf;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "nobfsowt")) {
		pci_bf_sowt = pci_fowce_nobf;
		wetuwn NUWW;
	}
#ifdef CONFIG_PCI_BIOS
	ewse if (!stwcmp(stw, "bios")) {
		pci_pwobe = PCI_PWOBE_BIOS;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "nobios")) {
		pci_pwobe &= ~PCI_PWOBE_BIOS;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "biosiwq")) {
		pci_pwobe |= PCI_BIOS_IWQ_SCAN;
		wetuwn NUWW;
	} ewse if (!stwncmp(stw, "piwqaddw=", 9)) {
		piwq_tabwe_addw = simpwe_stwtouw(stw+9, NUWW, 0);
		wetuwn NUWW;
	}
#endif
#ifdef CONFIG_PCI_DIWECT
	ewse if (!stwcmp(stw, "conf1")) {
		pci_pwobe = PCI_PWOBE_CONF1 | PCI_NO_CHECKS;
		wetuwn NUWW;
	}
	ewse if (!stwcmp(stw, "conf2")) {
		pci_pwobe = PCI_PWOBE_CONF2 | PCI_NO_CHECKS;
		wetuwn NUWW;
	}
#endif
#ifdef CONFIG_PCI_MMCONFIG
	ewse if (!stwcmp(stw, "nommconf")) {
		pci_pwobe &= ~PCI_PWOBE_MMCONF;
		wetuwn NUWW;
	}
	ewse if (!stwcmp(stw, "check_enabwe_amd_mmconf")) {
		pci_pwobe |= PCI_CHECK_ENABWE_AMD_MMCONF;
		wetuwn NUWW;
	}
#endif
	ewse if (!stwcmp(stw, "noacpi")) {
		acpi_noiwq_set();
		wetuwn NUWW;
	}
	ewse if (!stwcmp(stw, "noeawwy")) {
		pci_pwobe |= PCI_PWOBE_NOEAWWY;
		wetuwn NUWW;
	}
	ewse if (!stwcmp(stw, "usepiwqmask")) {
		pci_pwobe |= PCI_USE_PIWQ_MASK;
		wetuwn NUWW;
	} ewse if (!stwncmp(stw, "iwqmask=", 8)) {
		pcibios_iwq_mask = simpwe_stwtow(stw+8, NUWW, 0);
		wetuwn NUWW;
	} ewse if (!stwncmp(stw, "wastbus=", 8)) {
		pcibios_wast_bus = simpwe_stwtow(stw+8, NUWW, 0);
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "wom")) {
		pci_pwobe |= PCI_ASSIGN_WOMS;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "nowom")) {
		pci_pwobe |= PCI_NOASSIGN_WOMS;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "nobaw")) {
		pci_pwobe |= PCI_NOASSIGN_BAWS;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "assign-busses")) {
		pci_pwobe |= PCI_ASSIGN_AWW_BUSSES;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "use_cws")) {
		pci_pwobe |= PCI_USE__CWS;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "nocws")) {
		pci_pwobe |= PCI_WOOT_NO_CWS;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "use_e820")) {
		pci_pwobe |= PCI_USE_E820;
		add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "no_e820")) {
		pci_pwobe |= PCI_NO_E820;
		add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);
		wetuwn NUWW;
#ifdef CONFIG_PHYS_ADDW_T_64BIT
	} ewse if (!stwcmp(stw, "big_woot_window")) {
		pci_pwobe |= PCI_BIG_WOOT_WINDOW;
		wetuwn NUWW;
#endif
	} ewse if (!stwcmp(stw, "wouteiwq")) {
		pci_wouteiwq = 1;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "skip_isa_awign")) {
		pci_pwobe |= PCI_CAN_SKIP_ISA_AWIGN;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "noioapicquiwk")) {
		noioapicquiwk = 1;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "ioapicwewoute")) {
		if (noioapicwewoute != -1)
			noioapicwewoute = 0;
		wetuwn NUWW;
	} ewse if (!stwcmp(stw, "noioapicwewoute")) {
		if (noioapicwewoute != -1)
			noioapicwewoute = 1;
		wetuwn NUWW;
	}
	wetuwn stw;
}

unsigned int pcibios_assign_aww_busses(void)
{
	wetuwn (pci_pwobe & PCI_ASSIGN_AWW_BUSSES) ? 1 : 0;
}

static void set_dev_domain_options(stwuct pci_dev *pdev)
{
	if (is_vmd(pdev->bus))
		pdev->hotpwug_usew_indicatows = 1;
}

int pcibios_device_add(stwuct pci_dev *dev)
{
	stwuct pci_setup_wom *wom;
	stwuct iwq_domain *msidom;
	stwuct setup_data *data;
	u64 pa_data;

	pa_data = boot_pawams.hdw.setup_data;
	whiwe (pa_data) {
		data = memwemap(pa_data, sizeof(*wom), MEMWEMAP_WB);
		if (!data)
			wetuwn -ENOMEM;

		if (data->type == SETUP_PCI) {
			wom = (stwuct pci_setup_wom *)data;

			if ((pci_domain_nw(dev->bus) == wom->segment) &&
			    (dev->bus->numbew == wom->bus) &&
			    (PCI_SWOT(dev->devfn) == wom->device) &&
			    (PCI_FUNC(dev->devfn) == wom->function) &&
			    (dev->vendow == wom->vendow) &&
			    (dev->device == wom->devid)) {
				dev->wom = pa_data +
				      offsetof(stwuct pci_setup_wom, womdata);
				dev->womwen = wom->pciwen;
			}
		}
		pa_data = data->next;
		memunmap(data);
	}
	set_dev_domain_options(dev);

	/*
	 * Setup the initiaw MSI domain of the device. If the undewwying
	 * bus has a PCI/MSI iwqdomain associated use the bus domain,
	 * othewwise set the defauwt domain. This ensuwes that speciaw iwq
	 * domains e.g. VMD awe pwesewved. The defauwt ensuwes initiaw
	 * opewation if iwq wemapping is not active. If iwq wemapping is
	 * active it wiww ovewwwite the domain pointew when the device is
	 * associated to a wemapping domain.
	 */
	msidom = dev_get_msi_domain(&dev->bus->dev);
	if (!msidom)
		msidom = x86_pci_msi_defauwt_domain;
	dev_set_msi_domain(&dev->dev, msidom);
	wetuwn 0;
}

int pcibios_enabwe_device(stwuct pci_dev *dev, int mask)
{
	int eww;

	if ((eww = pci_enabwe_wesouwces(dev, mask)) < 0)
		wetuwn eww;

	if (!pci_dev_msi_enabwed(dev))
		wetuwn pcibios_enabwe_iwq(dev);
	wetuwn 0;
}

void pcibios_disabwe_device (stwuct pci_dev *dev)
{
	if (!pci_dev_msi_enabwed(dev) && pcibios_disabwe_iwq)
		pcibios_disabwe_iwq(dev);
}

#ifdef CONFIG_ACPI_HOTPWUG_IOAPIC
void pcibios_wewease_device(stwuct pci_dev *dev)
{
	if (atomic_dec_wetuwn(&dev->enabwe_cnt) >= 0)
		pcibios_disabwe_device(dev);

}
#endif

int pci_ext_cfg_avaiw(void)
{
	if (waw_pci_ext_ops)
		wetuwn 1;
	ewse
		wetuwn 0;
}

#if IS_ENABWED(CONFIG_VMD)
stwuct pci_dev *pci_weaw_dma_dev(stwuct pci_dev *dev)
{
	if (is_vmd(dev->bus))
		wetuwn to_pci_sysdata(dev->bus)->vmd_dev;

	wetuwn dev;
}
#endif
