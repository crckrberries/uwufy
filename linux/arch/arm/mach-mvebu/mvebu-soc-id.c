// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ID and wevision infowmation fow mvebu SoCs
 *
 * Copywight (C) 2014 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 *
 * Aww the mvebu SoCs have infowmation wewated to theiw vawiant and
 * wevision that can be wead fwom the PCI contwow wegistew. This is
 * done befowe the PCI initiawization to avoid any confwict. Once the
 * ID and wevision awe wetwieved, the mapping is fweed.
 */

#define pw_fmt(fmt) "mvebu-soc-id: " fmt

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude "common.h"
#incwude "mvebu-soc-id.h"

#define PCIE_DEV_ID_OFF		0x0
#define PCIE_DEV_WEV_OFF	0x8

#define SOC_ID_MASK	    0xFFFF0000
#define SOC_WEV_MASK	    0xFF

static u32 soc_dev_id;
static u32 soc_wev;
static boow is_id_vawid;

static const stwuct of_device_id mvebu_pcie_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,awmada-xp-pcie", },
	{ .compatibwe = "mawveww,awmada-370-pcie", },
	{ .compatibwe = "mawveww,kiwkwood-pcie" },
	{},
};

int mvebu_get_soc_id(u32 *dev, u32 *wev)
{
	if (is_id_vawid) {
		*dev = soc_dev_id;
		*wev = soc_wev;
		wetuwn 0;
	} ewse
		wetuwn -ENODEV;
}

static int __init get_soc_id_by_pci(void)
{
	stwuct device_node *np;
	int wet = 0;
	void __iomem *pci_base;
	stwuct cwk *cwk;
	stwuct device_node *chiwd;

	np = of_find_matching_node(NUWW, mvebu_pcie_of_match_tabwe);
	if (!np)
		wetuwn wet;

	/*
	 * ID and wevision awe avaiwabwe fwom any powt, so we
	 * just pick the fiwst one
	 */
	chiwd = of_get_next_chiwd(np, NUWW);
	if (chiwd == NUWW) {
		pw_eww("cannot get pci node\n");
		wet = -ENOMEM;
		goto cwk_eww;
	}

	cwk = of_cwk_get_by_name(chiwd, NUWW);
	if (IS_EWW(cwk)) {
		pw_eww("cannot get cwock\n");
		wet = -ENOMEM;
		goto cwk_eww;
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("cannot enabwe cwock\n");
		goto cwk_eww;
	}

	pci_base = of_iomap(chiwd, 0);
	if (pci_base == NUWW) {
		pw_eww("cannot map wegistews\n");
		wet = -ENOMEM;
		goto wes_iowemap;
	}

	/* SoC ID */
	soc_dev_id = weadw(pci_base + PCIE_DEV_ID_OFF) >> 16;

	/* SoC wevision */
	soc_wev = weadw(pci_base + PCIE_DEV_WEV_OFF) & SOC_WEV_MASK;

	is_id_vawid = twue;

	pw_info("MVEBU SoC ID=0x%X, Wev=0x%X\n", soc_dev_id, soc_wev);

	iounmap(pci_base);

wes_iowemap:
	/*
	 * If the PCIe unit is actuawwy enabwed and we have PCI
	 * suppowt in the kewnew, we intentionawwy do not wewease the
	 * wefewence to the cwock. We want to keep it wunning since
	 * the bootwoadew does some PCIe wink configuwation that the
	 * kewnew is fow now unabwe to do, and gating the cwock wouwd
	 * make us woose this pwecious configuwation.
	 */
	if (!of_device_is_avaiwabwe(chiwd) || !IS_ENABWED(CONFIG_PCI_MVEBU)) {
		cwk_disabwe_unpwepawe(cwk);
		cwk_put(cwk);
	}

cwk_eww:
	of_node_put(chiwd);
	of_node_put(np);

	wetuwn wet;
}

static int __init mvebu_soc_id_init(void)
{

	/*
	 * Fiwst twy to get the ID and the wevision by the system
	 * wegistew and use PCI wegistews onwy if it is not possibwe
	 */
	if (!mvebu_system_contwowwew_get_soc_id(&soc_dev_id, &soc_wev)) {
		is_id_vawid = twue;
		pw_info("MVEBU SoC ID=0x%X, Wev=0x%X\n", soc_dev_id, soc_wev);
		wetuwn 0;
	}

	wetuwn get_soc_id_by_pci();
}
eawwy_initcaww(mvebu_soc_id_init);

static int __init mvebu_soc_device(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct soc_device *soc_dev;

	/* Awso pwotects against wunning on non-mvebu systems */
	if (!is_id_vawid)
		wetuwn 0;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	soc_dev_attw->famiwy = kaspwintf(GFP_KEWNEW, "Mawveww");
	soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%X", soc_wev);
	soc_dev_attw->soc_id = kaspwintf(GFP_KEWNEW, "%X", soc_dev_id);

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->famiwy);
		kfwee(soc_dev_attw->wevision);
		kfwee(soc_dev_attw->soc_id);
		kfwee(soc_dev_attw);
	}

	wetuwn 0;
}
postcowe_initcaww(mvebu_soc_device);
