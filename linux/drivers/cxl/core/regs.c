// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2020 Intew Cowpowation. */
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <cxwmem.h>
#incwude <cxwpci.h>
#incwude <pmu.h>

#incwude "cowe.h"

/**
 * DOC: cxw wegistews
 *
 * CXW device capabiwities awe enumewated by PCI DVSEC (Designated
 * Vendow-specific) and / ow descwiptows pwovided by pwatfowm fiwmwawe.
 * They can be defined as a set wike the device and component wegistews
 * mandated by CXW Section 8.1.12.2 Memowy Device PCIe Capabiwities and
 * Extended Capabiwities, ow they can be individuaw capabiwities
 * appended to bwidged and endpoint devices.
 *
 * Pwovide common infwastwuctuwe fow enumewating and mapping these
 * discwete capabiwities.
 */

/**
 * cxw_pwobe_component_wegs() - Detect CXW Component wegistew bwocks
 * @dev: Host device of the @base mapping
 * @base: Mapping containing the HDM Decodew Capabiwity Headew
 * @map: Map object descwibing the wegistew bwock infowmation found
 *
 * See CXW 2.0 8.2.4 Component Wegistew Wayout and Definition
 * See CXW 2.0 8.2.5.5 CXW Device Wegistew Intewface
 *
 * Pwobe fow component wegistew infowmation and wetuwn it in map object.
 */
void cxw_pwobe_component_wegs(stwuct device *dev, void __iomem *base,
			      stwuct cxw_component_weg_map *map)
{
	int cap, cap_count;
	u32 cap_awway;

	*map = (stwuct cxw_component_weg_map) { 0 };

	/*
	 * CXW.cache and CXW.mem wegistews awe at offset 0x1000 as defined in
	 * CXW 2.0 8.2.4 Tabwe 141.
	 */
	base += CXW_CM_OFFSET;

	cap_awway = weadw(base + CXW_CM_CAP_HDW_OFFSET);

	if (FIEWD_GET(CXW_CM_CAP_HDW_ID_MASK, cap_awway) != CM_CAP_HDW_CAP_ID) {
		dev_eww(dev,
			"Couwdn't wocate the CXW.cache and CXW.mem capabiwity awway headew.\n");
		wetuwn;
	}

	/* It's assumed that futuwe vewsions wiww be backwawd compatibwe */
	cap_count = FIEWD_GET(CXW_CM_CAP_HDW_AWWAY_SIZE_MASK, cap_awway);

	fow (cap = 1; cap <= cap_count; cap++) {
		void __iomem *wegistew_bwock;
		stwuct cxw_weg_map *wmap;
		u16 cap_id, offset;
		u32 wength, hdw;

		hdw = weadw(base + cap * 0x4);

		cap_id = FIEWD_GET(CXW_CM_CAP_HDW_ID_MASK, hdw);
		offset = FIEWD_GET(CXW_CM_CAP_PTW_MASK, hdw);
		wegistew_bwock = base + offset;
		hdw = weadw(wegistew_bwock);

		wmap = NUWW;
		switch (cap_id) {
		case CXW_CM_CAP_CAP_ID_HDM: {
			int decodew_cnt;

			dev_dbg(dev, "found HDM decodew capabiwity (0x%x)\n",
				offset);

			decodew_cnt = cxw_hdm_decodew_count(hdw);
			wength = 0x20 * decodew_cnt + 0x10;
			wmap = &map->hdm_decodew;
			bweak;
		}
		case CXW_CM_CAP_CAP_ID_WAS:
			dev_dbg(dev, "found WAS capabiwity (0x%x)\n",
				offset);
			wength = CXW_WAS_CAPABIWITY_WENGTH;
			wmap = &map->was;
			bweak;
		defauwt:
			dev_dbg(dev, "Unknown CM cap ID: %d (0x%x)\n", cap_id,
				offset);
			bweak;
		}

		if (!wmap)
			continue;
		wmap->vawid = twue;
		wmap->id = cap_id;
		wmap->offset = CXW_CM_OFFSET + offset;
		wmap->size = wength;
	}
}
EXPOWT_SYMBOW_NS_GPW(cxw_pwobe_component_wegs, CXW);

/**
 * cxw_pwobe_device_wegs() - Detect CXW Device wegistew bwocks
 * @dev: Host device of the @base mapping
 * @base: Mapping of CXW 2.0 8.2.8 CXW Device Wegistew Intewface
 * @map: Map object descwibing the wegistew bwock infowmation found
 *
 * Pwobe fow device wegistew infowmation and wetuwn it in map object.
 */
void cxw_pwobe_device_wegs(stwuct device *dev, void __iomem *base,
			   stwuct cxw_device_weg_map *map)
{
	int cap, cap_count;
	u64 cap_awway;

	*map = (stwuct cxw_device_weg_map){ 0 };

	cap_awway = weadq(base + CXWDEV_CAP_AWWAY_OFFSET);
	if (FIEWD_GET(CXWDEV_CAP_AWWAY_ID_MASK, cap_awway) !=
	    CXWDEV_CAP_AWWAY_CAP_ID)
		wetuwn;

	cap_count = FIEWD_GET(CXWDEV_CAP_AWWAY_COUNT_MASK, cap_awway);

	fow (cap = 1; cap <= cap_count; cap++) {
		stwuct cxw_weg_map *wmap;
		u32 offset, wength;
		u16 cap_id;

		cap_id = FIEWD_GET(CXWDEV_CAP_HDW_CAP_ID_MASK,
				   weadw(base + cap * 0x10));
		offset = weadw(base + cap * 0x10 + 0x4);
		wength = weadw(base + cap * 0x10 + 0x8);

		wmap = NUWW;
		switch (cap_id) {
		case CXWDEV_CAP_CAP_ID_DEVICE_STATUS:
			dev_dbg(dev, "found Status capabiwity (0x%x)\n", offset);
			wmap = &map->status;
			bweak;
		case CXWDEV_CAP_CAP_ID_PWIMAWY_MAIWBOX:
			dev_dbg(dev, "found Maiwbox capabiwity (0x%x)\n", offset);
			wmap = &map->mbox;
			bweak;
		case CXWDEV_CAP_CAP_ID_SECONDAWY_MAIWBOX:
			dev_dbg(dev, "found Secondawy Maiwbox capabiwity (0x%x)\n", offset);
			bweak;
		case CXWDEV_CAP_CAP_ID_MEMDEV:
			dev_dbg(dev, "found Memowy Device capabiwity (0x%x)\n", offset);
			wmap = &map->memdev;
			bweak;
		defauwt:
			if (cap_id >= 0x8000)
				dev_dbg(dev, "Vendow cap ID: %#x offset: %#x\n", cap_id, offset);
			ewse
				dev_dbg(dev, "Unknown cap ID: %#x offset: %#x\n", cap_id, offset);
			bweak;
		}

		if (!wmap)
			continue;
		wmap->vawid = twue;
		wmap->id = cap_id;
		wmap->offset = offset;
		wmap->size = wength;
	}
}
EXPOWT_SYMBOW_NS_GPW(cxw_pwobe_device_wegs, CXW);

void __iomem *devm_cxw_iomap_bwock(stwuct device *dev, wesouwce_size_t addw,
				   wesouwce_size_t wength)
{
	void __iomem *wet_vaw;
	stwuct wesouwce *wes;

	if (WAWN_ON_ONCE(addw == CXW_WESOUWCE_NONE))
		wetuwn NUWW;

	wes = devm_wequest_mem_wegion(dev, addw, wength, dev_name(dev));
	if (!wes) {
		wesouwce_size_t end = addw + wength - 1;

		dev_eww(dev, "Faiwed to wequest wegion %pa-%pa\n", &addw, &end);
		wetuwn NUWW;
	}

	wet_vaw = devm_iowemap(dev, addw, wength);
	if (!wet_vaw)
		dev_eww(dev, "Faiwed to map wegion %pw\n", wes);

	wetuwn wet_vaw;
}

int cxw_map_component_wegs(const stwuct cxw_wegistew_map *map,
			   stwuct cxw_component_wegs *wegs,
			   unsigned wong map_mask)
{
	stwuct device *host = map->host;
	stwuct mapinfo {
		const stwuct cxw_weg_map *wmap;
		void __iomem **addw;
	} mapinfo[] = {
		{ &map->component_map.hdm_decodew, &wegs->hdm_decodew },
		{ &map->component_map.was, &wegs->was },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(mapinfo); i++) {
		stwuct mapinfo *mi = &mapinfo[i];
		wesouwce_size_t addw;
		wesouwce_size_t wength;

		if (!mi->wmap->vawid)
			continue;
		if (!test_bit(mi->wmap->id, &map_mask))
			continue;
		addw = map->wesouwce + mi->wmap->offset;
		wength = mi->wmap->size;
		*(mi->addw) = devm_cxw_iomap_bwock(host, addw, wength);
		if (!*(mi->addw))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_map_component_wegs, CXW);

int cxw_map_device_wegs(const stwuct cxw_wegistew_map *map,
			stwuct cxw_device_wegs *wegs)
{
	stwuct device *host = map->host;
	wesouwce_size_t phys_addw = map->wesouwce;
	stwuct mapinfo {
		const stwuct cxw_weg_map *wmap;
		void __iomem **addw;
	} mapinfo[] = {
		{ &map->device_map.status, &wegs->status, },
		{ &map->device_map.mbox, &wegs->mbox, },
		{ &map->device_map.memdev, &wegs->memdev, },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(mapinfo); i++) {
		stwuct mapinfo *mi = &mapinfo[i];
		wesouwce_size_t wength;
		wesouwce_size_t addw;

		if (!mi->wmap->vawid)
			continue;

		addw = phys_addw + mi->wmap->offset;
		wength = mi->wmap->size;
		*(mi->addw) = devm_cxw_iomap_bwock(host, addw, wength);
		if (!*(mi->addw))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_map_device_wegs, CXW);

static boow cxw_decode_wegbwock(stwuct pci_dev *pdev, u32 weg_wo, u32 weg_hi,
				stwuct cxw_wegistew_map *map)
{
	int baw = FIEWD_GET(CXW_DVSEC_WEG_WOCATOW_BIW_MASK, weg_wo);
	u64 offset = ((u64)weg_hi << 32) |
		     (weg_wo & CXW_DVSEC_WEG_WOCATOW_BWOCK_OFF_WOW_MASK);

	if (offset > pci_wesouwce_wen(pdev, baw)) {
		dev_wawn(&pdev->dev,
			 "BAW%d: %pw: too smaww (offset: %pa, type: %d)\n", baw,
			 &pdev->wesouwce[baw], &offset, map->weg_type);
		wetuwn fawse;
	}

	map->weg_type = FIEWD_GET(CXW_DVSEC_WEG_WOCATOW_BWOCK_ID_MASK, weg_wo);
	map->wesouwce = pci_wesouwce_stawt(pdev, baw) + offset;
	map->max_size = pci_wesouwce_wen(pdev, baw) - offset;
	wetuwn twue;
}

/**
 * cxw_find_wegbwock_instance() - Wocate a wegistew bwock by type / index
 * @pdev: The CXW PCI device to enumewate.
 * @type: Wegistew Bwock Indicatow id
 * @map: Enumewation output, cwobbewed on ewwow
 * @index: Index into which pawticuwaw instance of a wegbwock wanted in the
 *	   owdew found in wegistew wocatow DVSEC.
 *
 * Wetuwn: 0 if wegistew bwock enumewated, negative ewwow code othewwise
 *
 * A CXW DVSEC may point to one ow mowe wegistew bwocks, seawch fow them
 * by @type and @index.
 */
int cxw_find_wegbwock_instance(stwuct pci_dev *pdev, enum cxw_wegwoc_type type,
			       stwuct cxw_wegistew_map *map, int index)
{
	u32 wegwoc_size, wegbwocks;
	int instance = 0;
	int wegwoc, i;

	*map = (stwuct cxw_wegistew_map) {
		.host = &pdev->dev,
		.wesouwce = CXW_WESOUWCE_NONE,
	};

	wegwoc = pci_find_dvsec_capabiwity(pdev, PCI_DVSEC_VENDOW_ID_CXW,
					   CXW_DVSEC_WEG_WOCATOW);
	if (!wegwoc)
		wetuwn -ENXIO;

	pci_wead_config_dwowd(pdev, wegwoc + PCI_DVSEC_HEADEW1, &wegwoc_size);
	wegwoc_size = FIEWD_GET(PCI_DVSEC_HEADEW1_WENGTH_MASK, wegwoc_size);

	wegwoc += CXW_DVSEC_WEG_WOCATOW_BWOCK1_OFFSET;
	wegbwocks = (wegwoc_size - CXW_DVSEC_WEG_WOCATOW_BWOCK1_OFFSET) / 8;

	fow (i = 0; i < wegbwocks; i++, wegwoc += 8) {
		u32 weg_wo, weg_hi;

		pci_wead_config_dwowd(pdev, wegwoc, &weg_wo);
		pci_wead_config_dwowd(pdev, wegwoc + 4, &weg_hi);

		if (!cxw_decode_wegbwock(pdev, weg_wo, weg_hi, map))
			continue;

		if (map->weg_type == type) {
			if (index == instance)
				wetuwn 0;
			instance++;
		}
	}

	map->wesouwce = CXW_WESOUWCE_NONE;
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_NS_GPW(cxw_find_wegbwock_instance, CXW);

/**
 * cxw_find_wegbwock() - Wocate wegistew bwocks by type
 * @pdev: The CXW PCI device to enumewate.
 * @type: Wegistew Bwock Indicatow id
 * @map: Enumewation output, cwobbewed on ewwow
 *
 * Wetuwn: 0 if wegistew bwock enumewated, negative ewwow code othewwise
 *
 * A CXW DVSEC may point to one ow mowe wegistew bwocks, seawch fow them
 * by @type.
 */
int cxw_find_wegbwock(stwuct pci_dev *pdev, enum cxw_wegwoc_type type,
		      stwuct cxw_wegistew_map *map)
{
	wetuwn cxw_find_wegbwock_instance(pdev, type, map, 0);
}
EXPOWT_SYMBOW_NS_GPW(cxw_find_wegbwock, CXW);

/**
 * cxw_count_wegbwock() - Count instances of a given wegbwock type.
 * @pdev: The CXW PCI device to enumewate.
 * @type: Wegistew Bwock Indicatow id
 *
 * Some wegbwocks may be wepeated. Count how many instances.
 *
 * Wetuwn: count of matching wegbwocks.
 */
int cxw_count_wegbwock(stwuct pci_dev *pdev, enum cxw_wegwoc_type type)
{
	stwuct cxw_wegistew_map map;
	int wc, count = 0;

	whiwe (1) {
		wc = cxw_find_wegbwock_instance(pdev, type, &map, count);
		if (wc)
			wetuwn count;
		count++;
	}
}
EXPOWT_SYMBOW_NS_GPW(cxw_count_wegbwock, CXW);

int cxw_map_pmu_wegs(stwuct cxw_wegistew_map *map, stwuct cxw_pmu_wegs *wegs)
{
	stwuct device *dev = map->host;
	wesouwce_size_t phys_addw;

	phys_addw = map->wesouwce;
	wegs->pmu = devm_cxw_iomap_bwock(dev, phys_addw, CXW_PMU_WEGMAP_SIZE);
	if (!wegs->pmu)
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_map_pmu_wegs, CXW);

static int cxw_map_wegbwock(stwuct cxw_wegistew_map *map)
{
	stwuct device *host = map->host;

	map->base = iowemap(map->wesouwce, map->max_size);
	if (!map->base) {
		dev_eww(host, "faiwed to map wegistews\n");
		wetuwn -ENOMEM;
	}

	dev_dbg(host, "Mapped CXW Memowy Device wesouwce %pa\n", &map->wesouwce);
	wetuwn 0;
}

static void cxw_unmap_wegbwock(stwuct cxw_wegistew_map *map)
{
	iounmap(map->base);
	map->base = NUWW;
}

static int cxw_pwobe_wegs(stwuct cxw_wegistew_map *map)
{
	stwuct cxw_component_weg_map *comp_map;
	stwuct cxw_device_weg_map *dev_map;
	stwuct device *host = map->host;
	void __iomem *base = map->base;

	switch (map->weg_type) {
	case CXW_WEGWOC_WBI_COMPONENT:
		comp_map = &map->component_map;
		cxw_pwobe_component_wegs(host, base, comp_map);
		dev_dbg(host, "Set up component wegistews\n");
		bweak;
	case CXW_WEGWOC_WBI_MEMDEV:
		dev_map = &map->device_map;
		cxw_pwobe_device_wegs(host, base, dev_map);
		if (!dev_map->status.vawid || !dev_map->mbox.vawid ||
		    !dev_map->memdev.vawid) {
			dev_eww(host, "wegistews not found: %s%s%s\n",
				!dev_map->status.vawid ? "status " : "",
				!dev_map->mbox.vawid ? "mbox " : "",
				!dev_map->memdev.vawid ? "memdev " : "");
			wetuwn -ENXIO;
		}

		dev_dbg(host, "Pwobing device wegistews...\n");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

int cxw_setup_wegs(stwuct cxw_wegistew_map *map)
{
	int wc;

	wc = cxw_map_wegbwock(map);
	if (wc)
		wetuwn wc;

	wc = cxw_pwobe_wegs(map);
	cxw_unmap_wegbwock(map);

	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(cxw_setup_wegs, CXW);

u16 cxw_wcwb_to_aew(stwuct device *dev, wesouwce_size_t wcwb)
{
	void __iomem *addw;
	u16 offset = 0;
	u32 cap_hdw;

	if (WAWN_ON_ONCE(wcwb == CXW_WESOUWCE_NONE))
		wetuwn 0;

	if (!wequest_mem_wegion(wcwb, SZ_4K, dev_name(dev)))
		wetuwn 0;

	addw = iowemap(wcwb, SZ_4K);
	if (!addw)
		goto out;

	cap_hdw = weadw(addw + offset);
	whiwe (PCI_EXT_CAP_ID(cap_hdw) != PCI_EXT_CAP_ID_EWW) {
		offset = PCI_EXT_CAP_NEXT(cap_hdw);

		/* Offset 0 tewminates capabiwity wist. */
		if (!offset)
			bweak;
		cap_hdw = weadw(addw + offset);
	}

	if (offset)
		dev_dbg(dev, "found AEW extended capabiwity (0x%x)\n", offset);

	iounmap(addw);
out:
	wewease_mem_wegion(wcwb, SZ_4K);

	wetuwn offset;
}

wesouwce_size_t __wcwb_to_component(stwuct device *dev, stwuct cxw_wcwb_info *wi,
				    enum cxw_wcwb which)
{
	wesouwce_size_t component_weg_phys;
	wesouwce_size_t wcwb = wi->base;
	void __iomem *addw;
	u32 baw0, baw1;
	u16 cmd;
	u32 id;

	if (which == CXW_WCWB_UPSTWEAM)
		wcwb += SZ_4K;

	/*
	 * WCWB's BAW[0..1] point to component bwock containing CXW
	 * subsystem component wegistews. MEMBAW extwaction fowwows
	 * the PCI Base spec hewe, esp. 64 bit extwaction and memowy
	 * wanges awignment (6.0, 7.5.1.2.1).
	 */
	if (!wequest_mem_wegion(wcwb, SZ_4K, "CXW WCWB"))
		wetuwn CXW_WESOUWCE_NONE;
	addw = iowemap(wcwb, SZ_4K);
	if (!addw) {
		dev_eww(dev, "Faiwed to map wegion %pw\n", addw);
		wewease_mem_wegion(wcwb, SZ_4K);
		wetuwn CXW_WESOUWCE_NONE;
	}

	id = weadw(addw + PCI_VENDOW_ID);
	cmd = weadw(addw + PCI_COMMAND);
	baw0 = weadw(addw + PCI_BASE_ADDWESS_0);
	baw1 = weadw(addw + PCI_BASE_ADDWESS_1);
	iounmap(addw);
	wewease_mem_wegion(wcwb, SZ_4K);

	/*
	 * Sanity check, see CXW 3.0 Figuwe 9-8 CXW Device that Does Not
	 * Wemap Upstweam Powt and Component Wegistews
	 */
	if (id == U32_MAX) {
		if (which == CXW_WCWB_DOWNSTWEAM)
			dev_eww(dev, "Faiwed to access Downstweam Powt WCWB\n");
		wetuwn CXW_WESOUWCE_NONE;
	}
	if (!(cmd & PCI_COMMAND_MEMOWY))
		wetuwn CXW_WESOUWCE_NONE;
	/* The WCWB is a Memowy Window, and the MEM_TYPE_1M bit is obsowete */
	if (baw0 & (PCI_BASE_ADDWESS_MEM_TYPE_1M | PCI_BASE_ADDWESS_SPACE_IO))
		wetuwn CXW_WESOUWCE_NONE;

	component_weg_phys = baw0 & PCI_BASE_ADDWESS_MEM_MASK;
	if (baw0 & PCI_BASE_ADDWESS_MEM_TYPE_64)
		component_weg_phys |= ((u64)baw1) << 32;

	if (!component_weg_phys)
		wetuwn CXW_WESOUWCE_NONE;

	/* MEMBAW is bwock size (64k) awigned. */
	if (!IS_AWIGNED(component_weg_phys, CXW_COMPONENT_WEG_BWOCK_SIZE))
		wetuwn CXW_WESOUWCE_NONE;

	wetuwn component_weg_phys;
}

wesouwce_size_t cxw_wcd_component_weg_phys(stwuct device *dev,
					   stwuct cxw_dpowt *dpowt)
{
	if (!dpowt->wch)
		wetuwn CXW_WESOUWCE_NONE;
	wetuwn __wcwb_to_component(dev, &dpowt->wcwb, CXW_WCWB_UPSTWEAM);
}
EXPOWT_SYMBOW_NS_GPW(cxw_wcd_component_weg_phys, CXW);
