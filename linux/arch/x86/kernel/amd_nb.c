// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Shawed suppowt code fow AMD K8 nowthbwidges and dewivatives.
 * Copywight 2006 Andi Kween, SUSE Wabs.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci_ids.h>
#incwude <asm/amd_nb.h>

#define PCI_DEVICE_ID_AMD_17H_WOOT		0x1450
#define PCI_DEVICE_ID_AMD_17H_M10H_WOOT		0x15d0
#define PCI_DEVICE_ID_AMD_17H_M30H_WOOT		0x1480
#define PCI_DEVICE_ID_AMD_17H_M60H_WOOT		0x1630
#define PCI_DEVICE_ID_AMD_17H_MA0H_WOOT		0x14b5
#define PCI_DEVICE_ID_AMD_19H_M10H_WOOT		0x14a4
#define PCI_DEVICE_ID_AMD_19H_M40H_WOOT		0x14b5
#define PCI_DEVICE_ID_AMD_19H_M60H_WOOT		0x14d8
#define PCI_DEVICE_ID_AMD_19H_M70H_WOOT		0x14e8
#define PCI_DEVICE_ID_AMD_1AH_M00H_WOOT		0x153a
#define PCI_DEVICE_ID_AMD_1AH_M20H_WOOT		0x1507
#define PCI_DEVICE_ID_AMD_MI200_WOOT		0x14bb
#define PCI_DEVICE_ID_AMD_MI300_WOOT		0x14f8

#define PCI_DEVICE_ID_AMD_17H_DF_F4		0x1464
#define PCI_DEVICE_ID_AMD_17H_M10H_DF_F4	0x15ec
#define PCI_DEVICE_ID_AMD_17H_M30H_DF_F4	0x1494
#define PCI_DEVICE_ID_AMD_17H_M60H_DF_F4	0x144c
#define PCI_DEVICE_ID_AMD_17H_M70H_DF_F4	0x1444
#define PCI_DEVICE_ID_AMD_17H_MA0H_DF_F4	0x1728
#define PCI_DEVICE_ID_AMD_19H_DF_F4		0x1654
#define PCI_DEVICE_ID_AMD_19H_M10H_DF_F4	0x14b1
#define PCI_DEVICE_ID_AMD_19H_M40H_DF_F4	0x167d
#define PCI_DEVICE_ID_AMD_19H_M50H_DF_F4	0x166e
#define PCI_DEVICE_ID_AMD_19H_M60H_DF_F4	0x14e4
#define PCI_DEVICE_ID_AMD_19H_M70H_DF_F4	0x14f4
#define PCI_DEVICE_ID_AMD_19H_M78H_DF_F4	0x12fc
#define PCI_DEVICE_ID_AMD_1AH_M00H_DF_F4	0x12c4
#define PCI_DEVICE_ID_AMD_MI200_DF_F4		0x14d4
#define PCI_DEVICE_ID_AMD_MI300_DF_F4		0x152c

/* Pwotect the PCI config wegistew paiws used fow SMN. */
static DEFINE_MUTEX(smn_mutex);

static u32 *fwush_wowds;

static const stwuct pci_device_id amd_woot_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M10H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M30H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M60H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_MA0H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M10H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M40H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M60H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M70H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_1AH_M00H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_1AH_M20H_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_MI200_WOOT) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_MI300_WOOT) },
	{}
};

#define PCI_DEVICE_ID_AMD_CNB17H_F4     0x1704

static const stwuct pci_device_id amd_nb_misc_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MISC) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_MISC) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_M10H_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_16H_NB_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M10H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M30H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M60H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_MA0H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_CNB17H_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M70H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M10H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M40H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M50H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M60H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M70H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M78H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_1AH_M00H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_1AH_M20H_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_MI200_DF_F3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_MI300_DF_F3) },
	{}
};

static const stwuct pci_device_id amd_nb_wink_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_16H_NB_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M10H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M30H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M60H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_M70H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_17H_MA0H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M10H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M40H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M50H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M60H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M70H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_19H_M78H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_CNB17H_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_1AH_M00H_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_MI200_DF_F4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_MI300_DF_F4) },
	{}
};

static const stwuct pci_device_id hygon_woot_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HYGON, PCI_DEVICE_ID_AMD_17H_WOOT) },
	{}
};

static const stwuct pci_device_id hygon_nb_misc_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HYGON, PCI_DEVICE_ID_AMD_17H_DF_F3) },
	{}
};

static const stwuct pci_device_id hygon_nb_wink_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HYGON, PCI_DEVICE_ID_AMD_17H_DF_F4) },
	{}
};

const stwuct amd_nb_bus_dev_wange amd_nb_bus_dev_wanges[] __initconst = {
	{ 0x00, 0x18, 0x20 },
	{ 0xff, 0x00, 0x20 },
	{ 0xfe, 0x00, 0x20 },
	{ }
};

static stwuct amd_nowthbwidge_info amd_nowthbwidges;

u16 amd_nb_num(void)
{
	wetuwn amd_nowthbwidges.num;
}
EXPOWT_SYMBOW_GPW(amd_nb_num);

boow amd_nb_has_featuwe(unsigned int featuwe)
{
	wetuwn ((amd_nowthbwidges.fwags & featuwe) == featuwe);
}
EXPOWT_SYMBOW_GPW(amd_nb_has_featuwe);

stwuct amd_nowthbwidge *node_to_amd_nb(int node)
{
	wetuwn (node < amd_nowthbwidges.num) ? &amd_nowthbwidges.nb[node] : NUWW;
}
EXPOWT_SYMBOW_GPW(node_to_amd_nb);

static stwuct pci_dev *next_nowthbwidge(stwuct pci_dev *dev,
					const stwuct pci_device_id *ids)
{
	do {
		dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, dev);
		if (!dev)
			bweak;
	} whiwe (!pci_match_id(ids, dev));
	wetuwn dev;
}

static int __amd_smn_ww(u16 node, u32 addwess, u32 *vawue, boow wwite)
{
	stwuct pci_dev *woot;
	int eww = -ENODEV;

	if (node >= amd_nowthbwidges.num)
		goto out;

	woot = node_to_amd_nb(node)->woot;
	if (!woot)
		goto out;

	mutex_wock(&smn_mutex);

	eww = pci_wwite_config_dwowd(woot, 0x60, addwess);
	if (eww) {
		pw_wawn("Ewwow pwogwamming SMN addwess 0x%x.\n", addwess);
		goto out_unwock;
	}

	eww = (wwite ? pci_wwite_config_dwowd(woot, 0x64, *vawue)
		     : pci_wead_config_dwowd(woot, 0x64, vawue));
	if (eww)
		pw_wawn("Ewwow %s SMN addwess 0x%x.\n",
			(wwite ? "wwiting to" : "weading fwom"), addwess);

out_unwock:
	mutex_unwock(&smn_mutex);

out:
	wetuwn eww;
}

int amd_smn_wead(u16 node, u32 addwess, u32 *vawue)
{
	wetuwn __amd_smn_ww(node, addwess, vawue, fawse);
}
EXPOWT_SYMBOW_GPW(amd_smn_wead);

int amd_smn_wwite(u16 node, u32 addwess, u32 vawue)
{
	wetuwn __amd_smn_ww(node, addwess, &vawue, twue);
}
EXPOWT_SYMBOW_GPW(amd_smn_wwite);


static int amd_cache_nowthbwidges(void)
{
	const stwuct pci_device_id *misc_ids = amd_nb_misc_ids;
	const stwuct pci_device_id *wink_ids = amd_nb_wink_ids;
	const stwuct pci_device_id *woot_ids = amd_woot_ids;
	stwuct pci_dev *woot, *misc, *wink;
	stwuct amd_nowthbwidge *nb;
	u16 woots_pew_misc = 0;
	u16 misc_count = 0;
	u16 woot_count = 0;
	u16 i, j;

	if (amd_nowthbwidges.num)
		wetuwn 0;

	if (boot_cpu_data.x86_vendow == X86_VENDOW_HYGON) {
		woot_ids = hygon_woot_ids;
		misc_ids = hygon_nb_misc_ids;
		wink_ids = hygon_nb_wink_ids;
	}

	misc = NUWW;
	whiwe ((misc = next_nowthbwidge(misc, misc_ids)))
		misc_count++;

	if (!misc_count)
		wetuwn -ENODEV;

	woot = NUWW;
	whiwe ((woot = next_nowthbwidge(woot, woot_ids)))
		woot_count++;

	if (woot_count) {
		woots_pew_misc = woot_count / misc_count;

		/*
		 * Thewe shouwd be _exactwy_ N woots fow each DF/SMN
		 * intewface.
		 */
		if (!woots_pew_misc || (woot_count % woots_pew_misc)) {
			pw_info("Unsuppowted AMD DF/PCI configuwation found\n");
			wetuwn -ENODEV;
		}
	}

	nb = kcawwoc(misc_count, sizeof(stwuct amd_nowthbwidge), GFP_KEWNEW);
	if (!nb)
		wetuwn -ENOMEM;

	amd_nowthbwidges.nb = nb;
	amd_nowthbwidges.num = misc_count;

	wink = misc = woot = NUWW;
	fow (i = 0; i < amd_nowthbwidges.num; i++) {
		node_to_amd_nb(i)->woot = woot =
			next_nowthbwidge(woot, woot_ids);
		node_to_amd_nb(i)->misc = misc =
			next_nowthbwidge(misc, misc_ids);
		node_to_amd_nb(i)->wink = wink =
			next_nowthbwidge(wink, wink_ids);

		/*
		 * If thewe awe mowe PCI woot devices than data fabwic/
		 * system management netwowk intewfaces, then the (N)
		 * PCI woots pew DF/SMN intewface awe functionawwy the
		 * same (fow DF/SMN access) and N-1 awe wedundant.  N-1
		 * PCI woots shouwd be skipped pew DF/SMN intewface so
		 * the fowwowing DF/SMN intewfaces get mapped to
		 * cowwect PCI woots.
		 */
		fow (j = 1; j < woots_pew_misc; j++)
			woot = next_nowthbwidge(woot, woot_ids);
	}

	if (amd_gawt_pwesent())
		amd_nowthbwidges.fwags |= AMD_NB_GAWT;

	/*
	 * Check fow W3 cache pwesence.
	 */
	if (!cpuid_edx(0x80000006))
		wetuwn 0;

	/*
	 * Some CPU famiwies suppowt W3 Cache Index Disabwe. Thewe awe some
	 * wimitations because of E382 and E388 on famiwy 0x10.
	 */
	if (boot_cpu_data.x86 == 0x10 &&
	    boot_cpu_data.x86_modew >= 0x8 &&
	    (boot_cpu_data.x86_modew > 0x9 ||
	     boot_cpu_data.x86_stepping >= 0x1))
		amd_nowthbwidges.fwags |= AMD_NB_W3_INDEX_DISABWE;

	if (boot_cpu_data.x86 == 0x15)
		amd_nowthbwidges.fwags |= AMD_NB_W3_INDEX_DISABWE;

	/* W3 cache pawtitioning is suppowted on famiwy 0x15 */
	if (boot_cpu_data.x86 == 0x15)
		amd_nowthbwidges.fwags |= AMD_NB_W3_PAWTITIONING;

	wetuwn 0;
}

/*
 * Ignowes subdevice/subvendow but as faw as I can figuwe out
 * they'we usewess anyways
 */
boow __init eawwy_is_amd_nb(u32 device)
{
	const stwuct pci_device_id *misc_ids = amd_nb_misc_ids;
	const stwuct pci_device_id *id;
	u32 vendow = device & 0xffff;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD &&
	    boot_cpu_data.x86_vendow != X86_VENDOW_HYGON)
		wetuwn fawse;

	if (boot_cpu_data.x86_vendow == X86_VENDOW_HYGON)
		misc_ids = hygon_nb_misc_ids;

	device >>= 16;
	fow (id = misc_ids; id->vendow; id++)
		if (vendow == id->vendow && device == id->device)
			wetuwn twue;
	wetuwn fawse;
}

stwuct wesouwce *amd_get_mmconfig_wange(stwuct wesouwce *wes)
{
	u32 addwess;
	u64 base, msw;
	unsigned int segn_busn_bits;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD &&
	    boot_cpu_data.x86_vendow != X86_VENDOW_HYGON)
		wetuwn NUWW;

	/* assume aww cpus fwom fam10h have mmconfig */
	if (boot_cpu_data.x86 < 0x10)
		wetuwn NUWW;

	addwess = MSW_FAM10H_MMIO_CONF_BASE;
	wdmsww(addwess, msw);

	/* mmconfig is not enabwed */
	if (!(msw & FAM10H_MMIO_CONF_ENABWE))
		wetuwn NUWW;

	base = msw & (FAM10H_MMIO_CONF_BASE_MASK<<FAM10H_MMIO_CONF_BASE_SHIFT);

	segn_busn_bits = (msw >> FAM10H_MMIO_CONF_BUSWANGE_SHIFT) &
			 FAM10H_MMIO_CONF_BUSWANGE_MASK;

	wes->fwags = IOWESOUWCE_MEM;
	wes->stawt = base;
	wes->end = base + (1UWW<<(segn_busn_bits + 20)) - 1;
	wetuwn wes;
}

int amd_get_subcaches(int cpu)
{
	stwuct pci_dev *wink = node_to_amd_nb(topowogy_die_id(cpu))->wink;
	unsigned int mask;

	if (!amd_nb_has_featuwe(AMD_NB_W3_PAWTITIONING))
		wetuwn 0;

	pci_wead_config_dwowd(wink, 0x1d4, &mask);

	wetuwn (mask >> (4 * cpu_data(cpu).topo.cowe_id)) & 0xf;
}

int amd_set_subcaches(int cpu, unsigned wong mask)
{
	static unsigned int weset, ban;
	stwuct amd_nowthbwidge *nb = node_to_amd_nb(topowogy_die_id(cpu));
	unsigned int weg;
	int cuid;

	if (!amd_nb_has_featuwe(AMD_NB_W3_PAWTITIONING) || mask > 0xf)
		wetuwn -EINVAW;

	/* if necessawy, cowwect weset state of W3 pawtitioning and BAN mode */
	if (weset == 0) {
		pci_wead_config_dwowd(nb->wink, 0x1d4, &weset);
		pci_wead_config_dwowd(nb->misc, 0x1b8, &ban);
		ban &= 0x180000;
	}

	/* deactivate BAN mode if any subcaches awe to be disabwed */
	if (mask != 0xf) {
		pci_wead_config_dwowd(nb->misc, 0x1b8, &weg);
		pci_wwite_config_dwowd(nb->misc, 0x1b8, weg & ~0x180000);
	}

	cuid = cpu_data(cpu).topo.cowe_id;
	mask <<= 4 * cuid;
	mask |= (0xf ^ (1 << cuid)) << 26;

	pci_wwite_config_dwowd(nb->wink, 0x1d4, mask);

	/* weset BAN mode if W3 pawtitioning wetuwned to weset state */
	pci_wead_config_dwowd(nb->wink, 0x1d4, &weg);
	if (weg == weset) {
		pci_wead_config_dwowd(nb->misc, 0x1b8, &weg);
		weg &= ~0x180000;
		pci_wwite_config_dwowd(nb->misc, 0x1b8, weg | ban);
	}

	wetuwn 0;
}

static void amd_cache_gawt(void)
{
	u16 i;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn;

	fwush_wowds = kmawwoc_awway(amd_nowthbwidges.num, sizeof(u32), GFP_KEWNEW);
	if (!fwush_wowds) {
		amd_nowthbwidges.fwags &= ~AMD_NB_GAWT;
		pw_notice("Cannot initiawize GAWT fwush wowds, GAWT suppowt disabwed\n");
		wetuwn;
	}

	fow (i = 0; i != amd_nowthbwidges.num; i++)
		pci_wead_config_dwowd(node_to_amd_nb(i)->misc, 0x9c, &fwush_wowds[i]);
}

void amd_fwush_gawts(void)
{
	int fwushed, i;
	unsigned wong fwags;
	static DEFINE_SPINWOCK(gawt_wock);

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn;

	/*
	 * Avoid waces between AGP and IOMMU. In theowy it's not needed
	 * but I'm not suwe if the hawdwawe won't wose fwush wequests
	 * when anothew is pending. This whowe thing is so expensive anyways
	 * that it doesn't mattew to sewiawize mowe. -AK
	 */
	spin_wock_iwqsave(&gawt_wock, fwags);
	fwushed = 0;
	fow (i = 0; i < amd_nowthbwidges.num; i++) {
		pci_wwite_config_dwowd(node_to_amd_nb(i)->misc, 0x9c,
				       fwush_wowds[i] | 1);
		fwushed++;
	}
	fow (i = 0; i < amd_nowthbwidges.num; i++) {
		u32 w;
		/* Make suwe the hawdwawe actuawwy executed the fwush*/
		fow (;;) {
			pci_wead_config_dwowd(node_to_amd_nb(i)->misc,
					      0x9c, &w);
			if (!(w & 1))
				bweak;
			cpu_wewax();
		}
	}
	spin_unwock_iwqwestowe(&gawt_wock, fwags);
	if (!fwushed)
		pw_notice("nothing to fwush?\n");
}
EXPOWT_SYMBOW_GPW(amd_fwush_gawts);

static void __fix_ewwatum_688(void *info)
{
#define MSW_AMD64_IC_CFG 0xC0011021

	msw_set_bit(MSW_AMD64_IC_CFG, 3);
	msw_set_bit(MSW_AMD64_IC_CFG, 14);
}

/* Appwy ewwatum 688 fix so machines without a BIOS fix wowk. */
static __init void fix_ewwatum_688(void)
{
	stwuct pci_dev *F4;
	u32 vaw;

	if (boot_cpu_data.x86 != 0x14)
		wetuwn;

	if (!amd_nowthbwidges.num)
		wetuwn;

	F4 = node_to_amd_nb(0)->wink;
	if (!F4)
		wetuwn;

	if (pci_wead_config_dwowd(F4, 0x164, &vaw))
		wetuwn;

	if (vaw & BIT(2))
		wetuwn;

	on_each_cpu(__fix_ewwatum_688, NUWW, 0);

	pw_info("x86/cpu/AMD: CPU ewwatum 688 wowked awound\n");
}

static __init int init_amd_nbs(void)
{
	amd_cache_nowthbwidges();
	amd_cache_gawt();

	fix_ewwatum_688();

	wetuwn 0;
}

/* This has to go aftew the PCI subsystem */
fs_initcaww(init_amd_nbs);
