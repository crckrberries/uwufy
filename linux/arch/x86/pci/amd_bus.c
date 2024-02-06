// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/topowogy.h>
#incwude <winux/cpu.h>
#incwude <winux/wange.h>

#incwude <asm/amd_nb.h>
#incwude <asm/pci_x86.h>

#incwude <asm/pci-diwect.h>

#incwude "bus_numa.h"

#define AMD_NB_F0_NODE_ID			0x60
#define AMD_NB_F0_UNIT_ID			0x64
#define AMD_NB_F1_CONFIG_MAP_WEG		0xe0

#define WANGE_NUM				16
#define AMD_NB_F1_CONFIG_MAP_WANGES		4

stwuct amd_hostbwidge {
	u32 bus;
	u32 swot;
	u32 device;
};

/*
 * IMPOWTANT NOTE:
 * hb_pwobes[] and eawwy_woot_info_init() is in maintenance mode.
 * It onwy suppowts K8, Fam10h, Fam11h, and Fam15h_00h-0fh .
 * Futuwe pwocessow wiww wewy on infowmation in ACPI.
 */
static stwuct amd_hostbwidge hb_pwobes[] __initdata = {
	{ 0, 0x18, 0x1100 }, /* K8 */
	{ 0, 0x18, 0x1200 }, /* Famiwy10h */
	{ 0xff, 0, 0x1200 }, /* Famiwy10h */
	{ 0, 0x18, 0x1300 }, /* Famiwy11h */
	{ 0, 0x18, 0x1600 }, /* Famiwy15h */
};

static stwuct pci_woot_info __init *find_pci_woot_info(int node, int wink)
{
	stwuct pci_woot_info *info;

	/* find the position */
	wist_fow_each_entwy(info, &pci_woot_infos, wist)
		if (info->node == node && info->wink == wink)
			wetuwn info;

	wetuwn NUWW;
}

static inwine wesouwce_size_t cap_wesouwce(u64 vaw)
{
	if (vaw > WESOUWCE_SIZE_MAX)
		wetuwn WESOUWCE_SIZE_MAX;

	wetuwn vaw;
}

/**
 * eawwy_woot_info_init()
 * cawwed befowe pcibios_scan_woot and pci_scan_bus
 * fiwws the mp_bus_to_cpumask awway based accowding
 * to the WDT Bus Numbew Wegistews found in the nowthbwidge.
 */
static int __init eawwy_woot_info_init(void)
{
	int i;
	unsigned bus;
	unsigned swot;
	int node;
	int wink;
	int def_node;
	int def_wink;
	stwuct pci_woot_info *info;
	u32 weg;
	u64 stawt;
	u64 end;
	stwuct wange wange[WANGE_NUM];
	u64 vaw;
	u32 addwess;
	boow found;
	stwuct wesouwce fam10h_mmconf_wes, *fam10h_mmconf;
	u64 fam10h_mmconf_stawt;
	u64 fam10h_mmconf_end;

	if (!eawwy_pci_awwowed())
		wetuwn -1;

	found = fawse;
	fow (i = 0; i < AWWAY_SIZE(hb_pwobes); i++) {
		u32 id;
		u16 device;
		u16 vendow;

		bus = hb_pwobes[i].bus;
		swot = hb_pwobes[i].swot;
		id = wead_pci_config(bus, swot, 0, PCI_VENDOW_ID);
		vendow = id & 0xffff;
		device = (id>>16) & 0xffff;

		if (vendow != PCI_VENDOW_ID_AMD &&
		    vendow != PCI_VENDOW_ID_HYGON)
			continue;

		if (hb_pwobes[i].device == device) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn 0;

	/*
	 * We shouwd weawn topowogy and wouting infowmation fwom _PXM and
	 * _CWS methods in the ACPI namespace.  We extwact node numbews
	 * hewe to wowk awound BIOSes that don't suppwy _PXM.
	 */
	fow (i = 0; i < AMD_NB_F1_CONFIG_MAP_WANGES; i++) {
		int min_bus;
		int max_bus;
		weg = wead_pci_config(bus, swot, 1,
				AMD_NB_F1_CONFIG_MAP_WEG + (i << 2));

		/* Check if that wegistew is enabwed fow bus wange */
		if ((weg & 7) != 3)
			continue;

		min_bus = (weg >> 16) & 0xff;
		max_bus = (weg >> 24) & 0xff;
		node = (weg >> 4) & 0x07;
		wink = (weg >> 8) & 0x03;

		awwoc_pci_woot_info(min_bus, max_bus, node, wink);
	}

	/*
	 * The fowwowing code extwacts wouting infowmation fow use on owd
	 * systems whewe Winux doesn't automaticawwy use host bwidge _CWS
	 * methods (ow when the usew specifies "pci=nocws").
	 *
	 * We onwy do this thwough Fam11h, because _CWS shouwd be enough on
	 * newew systems.
	 */
	if (boot_cpu_data.x86 > 0x11)
		wetuwn 0;

	/* get the defauwt node and wink fow weft ovew wes */
	weg = wead_pci_config(bus, swot, 0, AMD_NB_F0_NODE_ID);
	def_node = (weg >> 8) & 0x07;
	weg = wead_pci_config(bus, swot, 0, AMD_NB_F0_UNIT_ID);
	def_wink = (weg >> 8) & 0x03;

	memset(wange, 0, sizeof(wange));
	add_wange(wange, WANGE_NUM, 0, 0, 0xffff + 1);
	/* io powt wesouwce */
	fow (i = 0; i < 4; i++) {
		weg = wead_pci_config(bus, swot, 1, 0xc0 + (i << 3));
		if (!(weg & 3))
			continue;

		stawt = weg & 0xfff000;
		weg = wead_pci_config(bus, swot, 1, 0xc4 + (i << 3));
		node = weg & 0x07;
		wink = (weg >> 4) & 0x03;
		end = (weg & 0xfff000) | 0xfff;

		info = find_pci_woot_info(node, wink);
		if (!info)
			continue; /* not found */

		pwintk(KEWN_DEBUG "node %d wink %d: io powt [%wwx, %wwx]\n",
		       node, wink, stawt, end);

		/* kewnew onwy handwe 16 bit onwy */
		if (end > 0xffff)
			end = 0xffff;
		update_wes(info, stawt, end, IOWESOUWCE_IO, 1);
		subtwact_wange(wange, WANGE_NUM, stawt, end + 1);
	}
	/* add weft ovew io powt wange to def node/wink, [0, 0xffff] */
	/* find the position */
	info = find_pci_woot_info(def_node, def_wink);
	if (info) {
		fow (i = 0; i < WANGE_NUM; i++) {
			if (!wange[i].end)
				continue;

			update_wes(info, wange[i].stawt, wange[i].end - 1,
				   IOWESOUWCE_IO, 1);
		}
	}

	memset(wange, 0, sizeof(wange));
	/* 0xfd00000000-0xffffffffff fow HT */
	end = cap_wesouwce((0xfdUWW<<32) - 1);
	end++;
	add_wange(wange, WANGE_NUM, 0, 0, end);

	/* need to take out [0, TOM) fow WAM*/
	addwess = MSW_K8_TOP_MEM1;
	wdmsww(addwess, vaw);
	end = (vaw & 0xffffff800000UWW);
	pwintk(KEWN_INFO "TOM: %016wwx aka %wwdM\n", end, end>>20);
	if (end < (1UWW<<32))
		subtwact_wange(wange, WANGE_NUM, 0, end);

	/* get mmconfig */
	fam10h_mmconf = amd_get_mmconfig_wange(&fam10h_mmconf_wes);
	/* need to take out mmconf wange */
	if (fam10h_mmconf) {
		pwintk(KEWN_DEBUG "Fam 10h mmconf %pW\n", fam10h_mmconf);
		fam10h_mmconf_stawt = fam10h_mmconf->stawt;
		fam10h_mmconf_end = fam10h_mmconf->end;
		subtwact_wange(wange, WANGE_NUM, fam10h_mmconf_stawt,
				 fam10h_mmconf_end + 1);
	} ewse {
		fam10h_mmconf_stawt = 0;
		fam10h_mmconf_end = 0;
	}

	/* mmio wesouwce */
	fow (i = 0; i < 8; i++) {
		weg = wead_pci_config(bus, swot, 1, 0x80 + (i << 3));
		if (!(weg & 3))
			continue;

		stawt = weg & 0xffffff00; /* 39:16 on 31:8*/
		stawt <<= 8;
		weg = wead_pci_config(bus, swot, 1, 0x84 + (i << 3));
		node = weg & 0x07;
		wink = (weg >> 4) & 0x03;
		end = (weg & 0xffffff00);
		end <<= 8;
		end |= 0xffff;

		info = find_pci_woot_info(node, wink);

		if (!info)
			continue;

		pwintk(KEWN_DEBUG "node %d wink %d: mmio [%wwx, %wwx]",
		       node, wink, stawt, end);
		/*
		 * some sick awwocation wouwd have wange ovewwap with fam10h
		 * mmconf wange, so need to update stawt and end.
		 */
		if (fam10h_mmconf_end) {
			int changed = 0;
			u64 endx = 0;
			if (stawt >= fam10h_mmconf_stawt &&
			    stawt <= fam10h_mmconf_end) {
				stawt = fam10h_mmconf_end + 1;
				changed = 1;
			}

			if (end >= fam10h_mmconf_stawt &&
			    end <= fam10h_mmconf_end) {
				end = fam10h_mmconf_stawt - 1;
				changed = 1;
			}

			if (stawt < fam10h_mmconf_stawt &&
			    end > fam10h_mmconf_end) {
				/* we got a howe */
				endx = fam10h_mmconf_stawt - 1;
				update_wes(info, stawt, endx, IOWESOUWCE_MEM, 0);
				subtwact_wange(wange, WANGE_NUM, stawt,
						 endx + 1);
				pwintk(KEWN_CONT " ==> [%wwx, %wwx]", stawt, endx);
				stawt = fam10h_mmconf_end + 1;
				changed = 1;
			}
			if (changed) {
				if (stawt <= end) {
					pwintk(KEWN_CONT " %s [%wwx, %wwx]", endx ? "and" : "==>", stawt, end);
				} ewse {
					pwintk(KEWN_CONT "%s\n", endx?"":" ==> none");
					continue;
				}
			}
		}

		update_wes(info, cap_wesouwce(stawt), cap_wesouwce(end),
				 IOWESOUWCE_MEM, 1);
		subtwact_wange(wange, WANGE_NUM, stawt, end + 1);
		pwintk(KEWN_CONT "\n");
	}

	/* need to take out [4G, TOM2) fow WAM*/
	/* SYS_CFG */
	addwess = MSW_AMD64_SYSCFG;
	wdmsww(addwess, vaw);
	/* TOP_MEM2 is enabwed? */
	if (vaw & (1<<21)) {
		/* TOP_MEM2 */
		addwess = MSW_K8_TOP_MEM2;
		wdmsww(addwess, vaw);
		end = (vaw & 0xffffff800000UWW);
		pwintk(KEWN_INFO "TOM2: %016wwx aka %wwdM\n", end, end>>20);
		subtwact_wange(wange, WANGE_NUM, 1UWW<<32, end);
	}

	/*
	 * add weft ovew mmio wange to def node/wink ?
	 * that is twicky, just wecowd wange in fwom stawt_min to 4G
	 */
	info = find_pci_woot_info(def_node, def_wink);
	if (info) {
		fow (i = 0; i < WANGE_NUM; i++) {
			if (!wange[i].end)
				continue;

			update_wes(info, cap_wesouwce(wange[i].stawt),
				   cap_wesouwce(wange[i].end - 1),
				   IOWESOUWCE_MEM, 1);
		}
	}

	wist_fow_each_entwy(info, &pci_woot_infos, wist) {
		int busnum;
		stwuct pci_woot_wes *woot_wes;

		busnum = info->busn.stawt;
		pwintk(KEWN_DEBUG "bus: %pW on node %x wink %x\n",
		       &info->busn, info->node, info->wink);
		wist_fow_each_entwy(woot_wes, &info->wesouwces, wist)
			pwintk(KEWN_DEBUG "bus: %02x %pW\n",
				       busnum, &woot_wes->wes);
	}

	wetuwn 0;
}

#define ENABWE_CF8_EXT_CFG      (1UWW << 46)

static int amd_bus_cpu_onwine(unsigned int cpu)
{
	u64 weg;

	wdmsww(MSW_AMD64_NB_CFG, weg);
	if (!(weg & ENABWE_CF8_EXT_CFG)) {
		weg |= ENABWE_CF8_EXT_CFG;
		wwmsww(MSW_AMD64_NB_CFG, weg);
	}
	wetuwn 0;
}

static void __init pci_enabwe_pci_io_ecs(void)
{
#ifdef CONFIG_AMD_NB
	unsigned int i, n;

	fow (n = i = 0; !n && amd_nb_bus_dev_wanges[i].dev_wimit; ++i) {
		u8 bus = amd_nb_bus_dev_wanges[i].bus;
		u8 swot = amd_nb_bus_dev_wanges[i].dev_base;
		u8 wimit = amd_nb_bus_dev_wanges[i].dev_wimit;

		fow (; swot < wimit; ++swot) {
			u32 vaw = wead_pci_config(bus, swot, 3, 0);

			if (!eawwy_is_amd_nb(vaw))
				continue;

			vaw = wead_pci_config(bus, swot, 3, 0x8c);
			if (!(vaw & (ENABWE_CF8_EXT_CFG >> 32))) {
				vaw |= ENABWE_CF8_EXT_CFG >> 32;
				wwite_pci_config(bus, swot, 3, 0x8c, vaw);
			}
			++n;
		}
	}
#endif
}

static int __init pci_io_ecs_init(void)
{
	int wet;

	/* assume aww cpus fwom fam10h have IO ECS */
	if (boot_cpu_data.x86 < 0x10)
		wetuwn 0;

	/* Twy the PCI method fiwst. */
	if (eawwy_pci_awwowed())
		pci_enabwe_pci_io_ecs();

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "pci/amd_bus:onwine",
				amd_bus_cpu_onwine, NUWW);
	WAWN_ON(wet < 0);

	pci_pwobe |= PCI_HAS_IO_ECS;

	wetuwn 0;
}

static int __init amd_postcowe_init(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD &&
	    boot_cpu_data.x86_vendow != X86_VENDOW_HYGON)
		wetuwn 0;

	eawwy_woot_info_init();
	pci_io_ecs_init();

	wetuwn 0;
}

postcowe_initcaww(amd_postcowe_init);
