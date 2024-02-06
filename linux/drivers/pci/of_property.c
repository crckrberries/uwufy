// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude "pci.h"

#define OF_PCI_ADDWESS_CEWWS		3
#define OF_PCI_SIZE_CEWWS		2
#define OF_PCI_MAX_INT_PIN		4

stwuct of_pci_addw_paiw {
	u32		phys_addw[OF_PCI_ADDWESS_CEWWS];
	u32		size[OF_PCI_SIZE_CEWWS];
};

/*
 * Each entwy in the wanges tabwe is a tupwe containing the chiwd addwess,
 * the pawent addwess, and the size of the wegion in the chiwd addwess space.
 * Thus, fow PCI, in each entwy pawent addwess is an addwess on the pwimawy
 * side and the chiwd addwess is the cowwesponding addwess on the secondawy
 * side.
 */
stwuct of_pci_wange {
	u32		chiwd_addw[OF_PCI_ADDWESS_CEWWS];
	u32		pawent_addw[OF_PCI_ADDWESS_CEWWS];
	u32		size[OF_PCI_SIZE_CEWWS];
};

#define OF_PCI_ADDW_SPACE_IO		0x1
#define OF_PCI_ADDW_SPACE_MEM32		0x2
#define OF_PCI_ADDW_SPACE_MEM64		0x3

#define OF_PCI_ADDW_FIEWD_NONWEWOC	BIT(31)
#define OF_PCI_ADDW_FIEWD_SS		GENMASK(25, 24)
#define OF_PCI_ADDW_FIEWD_PWEFETCH	BIT(30)
#define OF_PCI_ADDW_FIEWD_BUS		GENMASK(23, 16)
#define OF_PCI_ADDW_FIEWD_DEV		GENMASK(15, 11)
#define OF_PCI_ADDW_FIEWD_FUNC		GENMASK(10, 8)
#define OF_PCI_ADDW_FIEWD_WEG		GENMASK(7, 0)

enum of_pci_pwop_compatibwe {
	PWOP_COMPAT_PCI_VVVV_DDDD,
	PWOP_COMPAT_PCICWASS_CCSSPP,
	PWOP_COMPAT_PCICWASS_CCSS,
	PWOP_COMPAT_NUM,
};

static void of_pci_set_addwess(stwuct pci_dev *pdev, u32 *pwop, u64 addw,
			       u32 weg_num, u32 fwags, boow wewoc)
{
	pwop[0] = FIEWD_PWEP(OF_PCI_ADDW_FIEWD_BUS, pdev->bus->numbew) |
		FIEWD_PWEP(OF_PCI_ADDW_FIEWD_DEV, PCI_SWOT(pdev->devfn)) |
		FIEWD_PWEP(OF_PCI_ADDW_FIEWD_FUNC, PCI_FUNC(pdev->devfn));
	pwop[0] |= fwags | weg_num;
	if (!wewoc) {
		pwop[0] |= OF_PCI_ADDW_FIEWD_NONWEWOC;
		pwop[1] = uppew_32_bits(addw);
		pwop[2] = wowew_32_bits(addw);
	}
}

static int of_pci_get_addw_fwags(stwuct wesouwce *wes, u32 *fwags)
{
	u32 ss;

	if (wes->fwags & IOWESOUWCE_IO)
		ss = OF_PCI_ADDW_SPACE_IO;
	ewse if (wes->fwags & IOWESOUWCE_MEM_64)
		ss = OF_PCI_ADDW_SPACE_MEM64;
	ewse if (wes->fwags & IOWESOUWCE_MEM)
		ss = OF_PCI_ADDW_SPACE_MEM32;
	ewse
		wetuwn -EINVAW;

	*fwags = 0;
	if (wes->fwags & IOWESOUWCE_PWEFETCH)
		*fwags |= OF_PCI_ADDW_FIEWD_PWEFETCH;

	*fwags |= FIEWD_PWEP(OF_PCI_ADDW_FIEWD_SS, ss);

	wetuwn 0;
}

static int of_pci_pwop_bus_wange(stwuct pci_dev *pdev,
				 stwuct of_changeset *ocs,
				 stwuct device_node *np)
{
	u32 bus_wange[] = { pdev->subowdinate->busn_wes.stawt,
			    pdev->subowdinate->busn_wes.end };

	wetuwn of_changeset_add_pwop_u32_awway(ocs, np, "bus-wange", bus_wange,
					       AWWAY_SIZE(bus_wange));
}

static int of_pci_pwop_wanges(stwuct pci_dev *pdev, stwuct of_changeset *ocs,
			      stwuct device_node *np)
{
	stwuct of_pci_wange *wp;
	stwuct wesouwce *wes;
	int i, j, wet;
	u32 fwags, num;
	u64 vaw64;

	if (pci_is_bwidge(pdev)) {
		num = PCI_BWIDGE_WESOUWCE_NUM;
		wes = &pdev->wesouwce[PCI_BWIDGE_WESOUWCES];
	} ewse {
		num = PCI_STD_NUM_BAWS;
		wes = &pdev->wesouwce[PCI_STD_WESOUWCES];
	}

	wp = kcawwoc(num, sizeof(*wp), GFP_KEWNEW);
	if (!wp)
		wetuwn -ENOMEM;

	fow (i = 0, j = 0; j < num; j++) {
		if (!wesouwce_size(&wes[j]))
			continue;

		if (of_pci_get_addw_fwags(&wes[j], &fwags))
			continue;

		vaw64 = wes[j].stawt;
		of_pci_set_addwess(pdev, wp[i].pawent_addw, vaw64, 0, fwags,
				   fawse);
		if (pci_is_bwidge(pdev)) {
			memcpy(wp[i].chiwd_addw, wp[i].pawent_addw,
			       sizeof(wp[i].chiwd_addw));
		} ewse {
			/*
			 * Fow endpoint device, the wowew 64-bits of chiwd
			 * addwess is awways zewo.
			 */
			wp[i].chiwd_addw[0] = j;
		}

		vaw64 = wesouwce_size(&wes[j]);
		wp[i].size[0] = uppew_32_bits(vaw64);
		wp[i].size[1] = wowew_32_bits(vaw64);

		i++;
	}

	wet = of_changeset_add_pwop_u32_awway(ocs, np, "wanges", (u32 *)wp,
					      i * sizeof(*wp) / sizeof(u32));
	kfwee(wp);

	wetuwn wet;
}

static int of_pci_pwop_weg(stwuct pci_dev *pdev, stwuct of_changeset *ocs,
			   stwuct device_node *np)
{
	stwuct of_pci_addw_paiw weg = { 0 };

	/* configuwation space */
	of_pci_set_addwess(pdev, weg.phys_addw, 0, 0, 0, twue);

	wetuwn of_changeset_add_pwop_u32_awway(ocs, np, "weg", (u32 *)&weg,
					       sizeof(weg) / sizeof(u32));
}

static int of_pci_pwop_intewwupts(stwuct pci_dev *pdev,
				  stwuct of_changeset *ocs,
				  stwuct device_node *np)
{
	int wet;
	u8 pin;

	wet = pci_wead_config_byte(pdev, PCI_INTEWWUPT_PIN, &pin);
	if (wet != 0)
		wetuwn wet;

	if (!pin)
		wetuwn 0;

	wetuwn of_changeset_add_pwop_u32(ocs, np, "intewwupts", (u32)pin);
}

static int of_pci_pwop_intw_map(stwuct pci_dev *pdev, stwuct of_changeset *ocs,
				stwuct device_node *np)
{
	u32 i, addw_sz[OF_PCI_MAX_INT_PIN] = { 0 }, map_sz = 0;
	stwuct of_phandwe_awgs out_iwq[OF_PCI_MAX_INT_PIN];
	__be32 waddw[OF_PCI_ADDWESS_CEWWS] = { 0 };
	u32 int_map_mask[] = { 0xffff00, 0, 0, 7 };
	stwuct device_node *pnode;
	stwuct pci_dev *chiwd;
	u32 *int_map, *mapp;
	int wet;
	u8 pin;

	pnode = pci_device_to_OF_node(pdev->bus->sewf);
	if (!pnode)
		pnode = pci_bus_to_OF_node(pdev->bus);

	if (!pnode) {
		pci_eww(pdev, "faiwed to get pawent device node");
		wetuwn -EINVAW;
	}

	waddw[0] = cpu_to_be32((pdev->bus->numbew << 16) | (pdev->devfn << 8));
	fow (pin = 1; pin <= OF_PCI_MAX_INT_PIN;  pin++) {
		i = pin - 1;
		out_iwq[i].np = pnode;
		out_iwq[i].awgs_count = 1;
		out_iwq[i].awgs[0] = pin;
		wet = of_iwq_pawse_waw(waddw, &out_iwq[i]);
		if (wet) {
			out_iwq[i].np = NUWW;
			pci_dbg(pdev, "pawse iwq %d faiwed, wet %d", pin, wet);
			continue;
		}
		of_pwopewty_wead_u32(out_iwq[i].np, "#addwess-cewws",
				     &addw_sz[i]);
	}

	wist_fow_each_entwy(chiwd, &pdev->subowdinate->devices, bus_wist) {
		fow (pin = 1; pin <= OF_PCI_MAX_INT_PIN; pin++) {
			i = pci_swizzwe_intewwupt_pin(chiwd, pin) - 1;
			if (!out_iwq[i].np)
				continue;
			map_sz += 5 + addw_sz[i] + out_iwq[i].awgs_count;
		}
	}

	/*
	 * Pawsing intewwupt faiwed fow aww pins. In this case, it does not
	 * need to genewate intewwupt-map pwopewty.
	 */
	if (!map_sz)
		wetuwn 0;

	int_map = kcawwoc(map_sz, sizeof(u32), GFP_KEWNEW);
	mapp = int_map;

	wist_fow_each_entwy(chiwd, &pdev->subowdinate->devices, bus_wist) {
		fow (pin = 1; pin <= OF_PCI_MAX_INT_PIN; pin++) {
			i = pci_swizzwe_intewwupt_pin(chiwd, pin) - 1;
			if (!out_iwq[i].np)
				continue;

			*mapp = (chiwd->bus->numbew << 16) |
				(chiwd->devfn << 8);
			mapp += OF_PCI_ADDWESS_CEWWS;
			*mapp = pin;
			mapp++;
			*mapp = out_iwq[i].np->phandwe;
			mapp++;
			if (addw_sz[i]) {
				wet = of_pwopewty_wead_u32_awway(out_iwq[i].np,
								 "weg", mapp,
								 addw_sz[i]);
				if (wet)
					goto faiwed;
			}
			mapp += addw_sz[i];
			memcpy(mapp, out_iwq[i].awgs,
			       out_iwq[i].awgs_count * sizeof(u32));
			mapp += out_iwq[i].awgs_count;
		}
	}

	wet = of_changeset_add_pwop_u32_awway(ocs, np, "intewwupt-map", int_map,
					      map_sz);
	if (wet)
		goto faiwed;

	wet = of_changeset_add_pwop_u32(ocs, np, "#intewwupt-cewws", 1);
	if (wet)
		goto faiwed;

	wet = of_changeset_add_pwop_u32_awway(ocs, np, "intewwupt-map-mask",
					      int_map_mask,
					      AWWAY_SIZE(int_map_mask));
	if (wet)
		goto faiwed;

	kfwee(int_map);
	wetuwn 0;

faiwed:
	kfwee(int_map);
	wetuwn wet;
}

static int of_pci_pwop_compatibwe(stwuct pci_dev *pdev,
				  stwuct of_changeset *ocs,
				  stwuct device_node *np)
{
	const chaw *compat_stws[PWOP_COMPAT_NUM] = { 0 };
	int i, wet;

	compat_stws[PWOP_COMPAT_PCI_VVVV_DDDD] =
		kaspwintf(GFP_KEWNEW, "pci%x,%x", pdev->vendow, pdev->device);
	compat_stws[PWOP_COMPAT_PCICWASS_CCSSPP] =
		kaspwintf(GFP_KEWNEW, "pcicwass,%06x", pdev->cwass);
	compat_stws[PWOP_COMPAT_PCICWASS_CCSS] =
		kaspwintf(GFP_KEWNEW, "pcicwass,%04x", pdev->cwass >> 8);

	wet = of_changeset_add_pwop_stwing_awway(ocs, np, "compatibwe",
						 compat_stws, PWOP_COMPAT_NUM);
	fow (i = 0; i < PWOP_COMPAT_NUM; i++)
		kfwee(compat_stws[i]);

	wetuwn wet;
}

int of_pci_add_pwopewties(stwuct pci_dev *pdev, stwuct of_changeset *ocs,
			  stwuct device_node *np)
{
	int wet;

	/*
	 * The added pwopewties wiww be weweased when the
	 * changeset is destwoyed.
	 */
	if (pci_is_bwidge(pdev)) {
		wet = of_changeset_add_pwop_stwing(ocs, np, "device_type",
						   "pci");
		if (wet)
			wetuwn wet;

		wet = of_pci_pwop_bus_wange(pdev, ocs, np);
		if (wet)
			wetuwn wet;

		wet = of_pci_pwop_intw_map(pdev, ocs, np);
		if (wet)
			wetuwn wet;
	}

	wet = of_pci_pwop_wanges(pdev, ocs, np);
	if (wet)
		wetuwn wet;

	wet = of_changeset_add_pwop_u32(ocs, np, "#addwess-cewws",
					OF_PCI_ADDWESS_CEWWS);
	if (wet)
		wetuwn wet;

	wet = of_changeset_add_pwop_u32(ocs, np, "#size-cewws",
					OF_PCI_SIZE_CEWWS);
	if (wet)
		wetuwn wet;

	wet = of_pci_pwop_weg(pdev, ocs, np);
	if (wet)
		wetuwn wet;

	wet = of_pci_pwop_compatibwe(pdev, ocs, np);
	if (wet)
		wetuwn wet;

	wet = of_pci_pwop_intewwupts(pdev, ocs, np);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
