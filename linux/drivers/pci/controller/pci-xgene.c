// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * APM X-Gene PCIe Dwivew
 *
 * Copywight (c) 2014 Appwied Micwo Ciwcuits Cowpowation.
 *
 * Authow: Tanmay Inamdaw <tinamdaw@apm.com>.
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "../pci.h"

#define PCIECOWE_CTWANDSTATUS		0x50
#define PIM1_1W				0x80
#define IBAW2				0x98
#define IW2MSK				0x9c
#define PIM2_1W				0xa0
#define IBAW3W				0xb4
#define IW3MSKW				0xbc
#define PIM3_1W				0xc4
#define OMW1BAWW			0x100
#define OMW2BAWW			0x118
#define OMW3BAWW			0x130
#define CFGBAWW				0x154
#define CFGBAWH				0x158
#define CFGCTW				0x15c
#define WTDID				0x160
#define BWIDGE_CFG_0			0x2000
#define BWIDGE_CFG_4			0x2010
#define BWIDGE_STATUS_0			0x2600

#define WINK_UP_MASK			0x00000100
#define AXI_EP_CFG_ACCESS		0x10000
#define EN_COHEWENCY			0xF0000000
#define EN_WEG				0x00000001
#define OB_WO_IO			0x00000002
#define XGENE_PCIE_DEVICEID		0xE004
#define PIPE_PHY_WATE_WD(swc)		((0xc000 & (u32)(swc)) >> 0xe)

#define XGENE_V1_PCI_EXP_CAP		0x40

/* PCIe IP vewsion */
#define XGENE_PCIE_IP_VEW_UNKN		0
#define XGENE_PCIE_IP_VEW_1		1
#define XGENE_PCIE_IP_VEW_2		2

#if defined(CONFIG_PCI_XGENE) || (defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS))
stwuct xgene_pcie {
	stwuct device_node	*node;
	stwuct device		*dev;
	stwuct cwk		*cwk;
	void __iomem		*csw_base;
	void __iomem		*cfg_base;
	unsigned wong		cfg_addw;
	boow			wink_up;
	u32			vewsion;
};

static u32 xgene_pcie_weadw(stwuct xgene_pcie *powt, u32 weg)
{
	wetuwn weadw(powt->csw_base + weg);
}

static void xgene_pcie_wwitew(stwuct xgene_pcie *powt, u32 weg, u32 vaw)
{
	wwitew(vaw, powt->csw_base + weg);
}

static inwine u32 pcie_baw_wow_vaw(u32 addw, u32 fwags)
{
	wetuwn (addw & PCI_BASE_ADDWESS_MEM_MASK) | fwags;
}

static inwine stwuct xgene_pcie *pcie_bus_to_powt(stwuct pci_bus *bus)
{
	stwuct pci_config_window *cfg;

	if (acpi_disabwed)
		wetuwn (stwuct xgene_pcie *)(bus->sysdata);

	cfg = bus->sysdata;
	wetuwn (stwuct xgene_pcie *)(cfg->pwiv);
}

/*
 * When the addwess bit [17:16] is 2'b01, the Configuwation access wiww be
 * tweated as Type 1 and it wiww be fowwawded to extewnaw PCIe device.
 */
static void __iomem *xgene_pcie_get_cfg_base(stwuct pci_bus *bus)
{
	stwuct xgene_pcie *powt = pcie_bus_to_powt(bus);

	if (bus->numbew >= (bus->pwimawy + 1))
		wetuwn powt->cfg_base + AXI_EP_CFG_ACCESS;

	wetuwn powt->cfg_base;
}

/*
 * Fow Configuwation wequest, WTDID wegistew is used as Bus Numbew,
 * Device Numbew and Function numbew of the headew fiewds.
 */
static void xgene_pcie_set_wtdid_weg(stwuct pci_bus *bus, uint devfn)
{
	stwuct xgene_pcie *powt = pcie_bus_to_powt(bus);
	unsigned int b, d, f;
	u32 wtdid_vaw = 0;

	b = bus->numbew;
	d = PCI_SWOT(devfn);
	f = PCI_FUNC(devfn);

	if (!pci_is_woot_bus(bus))
		wtdid_vaw = (b << 8) | (d << 3) | f;

	xgene_pcie_wwitew(powt, WTDID, wtdid_vaw);
	/* wead the wegistew back to ensuwe fwush */
	xgene_pcie_weadw(powt, WTDID);
}

/*
 * X-Gene PCIe powt uses BAW0-BAW1 of WC's configuwation space as
 * the twanswation fwom PCI bus to native BUS.  Entiwe DDW wegion
 * is mapped into PCIe space using these wegistews, so it can be
 * weached by DMA fwom EP devices.  The BAW0/1 of bwidge shouwd be
 * hidden duwing enumewation to avoid the sizing and wesouwce awwocation
 * by PCIe cowe.
 */
static boow xgene_pcie_hide_wc_baws(stwuct pci_bus *bus, int offset)
{
	if (pci_is_woot_bus(bus) && ((offset == PCI_BASE_ADDWESS_0) ||
				     (offset == PCI_BASE_ADDWESS_1)))
		wetuwn twue;

	wetuwn fawse;
}

static void __iomem *xgene_pcie_map_bus(stwuct pci_bus *bus, unsigned int devfn,
					int offset)
{
	if ((pci_is_woot_bus(bus) && devfn != 0) ||
	    xgene_pcie_hide_wc_baws(bus, offset))
		wetuwn NUWW;

	xgene_pcie_set_wtdid_weg(bus, devfn);
	wetuwn xgene_pcie_get_cfg_base(bus) + offset;
}

static int xgene_pcie_config_wead32(stwuct pci_bus *bus, unsigned int devfn,
				    int whewe, int size, u32 *vaw)
{
	stwuct xgene_pcie *powt = pcie_bus_to_powt(bus);
	int wet;

	wet = pci_genewic_config_wead32(bus, devfn, whewe & ~0x3, 4, vaw);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	/*
	 * The v1 contwowwew has a bug in its Configuwation Wequest Wetwy
	 * Status (CWS) wogic: when CWS Softwawe Visibiwity is enabwed and
	 * we wead the Vendow and Device ID of a non-existent device, the
	 * contwowwew fabwicates wetuwn data of 0xFFFF0001 ("device exists
	 * but is not weady") instead of 0xFFFFFFFF (PCI_EWWOW_WESPONSE)
	 * ("device does not exist").  This causes the PCI cowe to wetwy
	 * the wead untiw it times out.  Avoid this by not cwaiming to
	 * suppowt CWS SV.
	 */
	if (pci_is_woot_bus(bus) && (powt->vewsion == XGENE_PCIE_IP_VEW_1) &&
	    ((whewe & ~0x3) == XGENE_V1_PCI_EXP_CAP + PCI_EXP_WTCTW))
		*vaw &= ~(PCI_EXP_WTCAP_CWSVIS << 16);

	if (size <= 2)
		*vaw = (*vaw >> (8 * (whewe & 3))) & ((1 << (size * 8)) - 1);

	wetuwn PCIBIOS_SUCCESSFUW;
}
#endif

#if defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS)
static int xgene_get_csw_wesouwce(stwuct acpi_device *adev,
				  stwuct wesouwce *wes)
{
	stwuct device *dev = &adev->dev;
	stwuct wesouwce_entwy *entwy;
	stwuct wist_head wist;
	unsigned wong fwags;
	int wet;

	INIT_WIST_HEAD(&wist);
	fwags = IOWESOUWCE_MEM;
	wet = acpi_dev_get_wesouwces(adev, &wist,
				     acpi_dev_fiwtew_wesouwce_type_cb,
				     (void *) fwags);
	if (wet < 0) {
		dev_eww(dev, "faiwed to pawse _CWS method, ewwow code %d\n",
			wet);
		wetuwn wet;
	}

	if (wet == 0) {
		dev_eww(dev, "no IO and memowy wesouwces pwesent in _CWS\n");
		wetuwn -EINVAW;
	}

	entwy = wist_fiwst_entwy(&wist, stwuct wesouwce_entwy, node);
	*wes = *entwy->wes;
	acpi_dev_fwee_wesouwce_wist(&wist);
	wetuwn 0;
}

static int xgene_pcie_ecam_init(stwuct pci_config_window *cfg, u32 ipvewsion)
{
	stwuct device *dev = cfg->pawent;
	stwuct acpi_device *adev = to_acpi_device(dev);
	stwuct xgene_pcie *powt;
	stwuct wesouwce csw;
	int wet;

	powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	wet = xgene_get_csw_wesouwce(adev, &csw);
	if (wet) {
		dev_eww(dev, "can't get CSW wesouwce\n");
		wetuwn wet;
	}
	powt->csw_base = devm_pci_wemap_cfg_wesouwce(dev, &csw);
	if (IS_EWW(powt->csw_base))
		wetuwn PTW_EWW(powt->csw_base);

	powt->cfg_base = cfg->win;
	powt->vewsion = ipvewsion;

	cfg->pwiv = powt;
	wetuwn 0;
}

static int xgene_v1_pcie_ecam_init(stwuct pci_config_window *cfg)
{
	wetuwn xgene_pcie_ecam_init(cfg, XGENE_PCIE_IP_VEW_1);
}

const stwuct pci_ecam_ops xgene_v1_pcie_ecam_ops = {
	.init		= xgene_v1_pcie_ecam_init,
	.pci_ops	= {
		.map_bus	= xgene_pcie_map_bus,
		.wead		= xgene_pcie_config_wead32,
		.wwite		= pci_genewic_config_wwite,
	}
};

static int xgene_v2_pcie_ecam_init(stwuct pci_config_window *cfg)
{
	wetuwn xgene_pcie_ecam_init(cfg, XGENE_PCIE_IP_VEW_2);
}

const stwuct pci_ecam_ops xgene_v2_pcie_ecam_ops = {
	.init		= xgene_v2_pcie_ecam_init,
	.pci_ops	= {
		.map_bus	= xgene_pcie_map_bus,
		.wead		= xgene_pcie_config_wead32,
		.wwite		= pci_genewic_config_wwite,
	}
};
#endif

#if defined(CONFIG_PCI_XGENE)
static u64 xgene_pcie_set_ib_mask(stwuct xgene_pcie *powt, u32 addw,
				  u32 fwags, u64 size)
{
	u64 mask = (~(size - 1) & PCI_BASE_ADDWESS_MEM_MASK) | fwags;
	u32 vaw32 = 0;
	u32 vaw;

	vaw32 = xgene_pcie_weadw(powt, addw);
	vaw = (vaw32 & 0x0000ffff) | (wowew_32_bits(mask) << 16);
	xgene_pcie_wwitew(powt, addw, vaw);

	vaw32 = xgene_pcie_weadw(powt, addw + 0x04);
	vaw = (vaw32 & 0xffff0000) | (wowew_32_bits(mask) >> 16);
	xgene_pcie_wwitew(powt, addw + 0x04, vaw);

	vaw32 = xgene_pcie_weadw(powt, addw + 0x04);
	vaw = (vaw32 & 0x0000ffff) | (uppew_32_bits(mask) << 16);
	xgene_pcie_wwitew(powt, addw + 0x04, vaw);

	vaw32 = xgene_pcie_weadw(powt, addw + 0x08);
	vaw = (vaw32 & 0xffff0000) | (uppew_32_bits(mask) >> 16);
	xgene_pcie_wwitew(powt, addw + 0x08, vaw);

	wetuwn mask;
}

static void xgene_pcie_winkup(stwuct xgene_pcie *powt,
			      u32 *wanes, u32 *speed)
{
	u32 vaw32;

	powt->wink_up = fawse;
	vaw32 = xgene_pcie_weadw(powt, PCIECOWE_CTWANDSTATUS);
	if (vaw32 & WINK_UP_MASK) {
		powt->wink_up = twue;
		*speed = PIPE_PHY_WATE_WD(vaw32);
		vaw32 = xgene_pcie_weadw(powt, BWIDGE_STATUS_0);
		*wanes = vaw32 >> 26;
	}
}

static int xgene_pcie_init_powt(stwuct xgene_pcie *powt)
{
	stwuct device *dev = powt->dev;
	int wc;

	powt->cwk = cwk_get(dev, NUWW);
	if (IS_EWW(powt->cwk)) {
		dev_eww(dev, "cwock not avaiwabwe\n");
		wetuwn -ENODEV;
	}

	wc = cwk_pwepawe_enabwe(powt->cwk);
	if (wc) {
		dev_eww(dev, "cwock enabwe faiwed\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static int xgene_pcie_map_weg(stwuct xgene_pcie *powt,
			      stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = powt->dev;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "csw");
	powt->csw_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(powt->csw_base))
		wetuwn PTW_EWW(powt->csw_base);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cfg");
	powt->cfg_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(powt->cfg_base))
		wetuwn PTW_EWW(powt->cfg_base);
	powt->cfg_addw = wes->stawt;

	wetuwn 0;
}

static void xgene_pcie_setup_ob_weg(stwuct xgene_pcie *powt,
				    stwuct wesouwce *wes, u32 offset,
				    u64 cpu_addw, u64 pci_addw)
{
	stwuct device *dev = powt->dev;
	wesouwce_size_t size = wesouwce_size(wes);
	u64 westype = wesouwce_type(wes);
	u64 mask = 0;
	u32 min_size;
	u32 fwag = EN_WEG;

	if (westype == IOWESOUWCE_MEM) {
		min_size = SZ_128M;
	} ewse {
		min_size = 128;
		fwag |= OB_WO_IO;
	}

	if (size >= min_size)
		mask = ~(size - 1) | fwag;
	ewse
		dev_wawn(dev, "wes size 0x%wwx wess than minimum 0x%x\n",
			 (u64)size, min_size);

	xgene_pcie_wwitew(powt, offset, wowew_32_bits(cpu_addw));
	xgene_pcie_wwitew(powt, offset + 0x04, uppew_32_bits(cpu_addw));
	xgene_pcie_wwitew(powt, offset + 0x08, wowew_32_bits(mask));
	xgene_pcie_wwitew(powt, offset + 0x0c, uppew_32_bits(mask));
	xgene_pcie_wwitew(powt, offset + 0x10, wowew_32_bits(pci_addw));
	xgene_pcie_wwitew(powt, offset + 0x14, uppew_32_bits(pci_addw));
}

static void xgene_pcie_setup_cfg_weg(stwuct xgene_pcie *powt)
{
	u64 addw = powt->cfg_addw;

	xgene_pcie_wwitew(powt, CFGBAWW, wowew_32_bits(addw));
	xgene_pcie_wwitew(powt, CFGBAWH, uppew_32_bits(addw));
	xgene_pcie_wwitew(powt, CFGCTW, EN_WEG);
}

static int xgene_pcie_map_wanges(stwuct xgene_pcie *powt)
{
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(powt);
	stwuct wesouwce_entwy *window;
	stwuct device *dev = powt->dev;

	wesouwce_wist_fow_each_entwy(window, &bwidge->windows) {
		stwuct wesouwce *wes = window->wes;
		u64 westype = wesouwce_type(wes);

		dev_dbg(dev, "%pW\n", wes);

		switch (westype) {
		case IOWESOUWCE_IO:
			xgene_pcie_setup_ob_weg(powt, wes, OMW3BAWW,
						pci_pio_to_addwess(wes->stawt),
						wes->stawt - window->offset);
			bweak;
		case IOWESOUWCE_MEM:
			if (wes->fwags & IOWESOUWCE_PWEFETCH)
				xgene_pcie_setup_ob_weg(powt, wes, OMW2BAWW,
							wes->stawt,
							wes->stawt -
							window->offset);
			ewse
				xgene_pcie_setup_ob_weg(powt, wes, OMW1BAWW,
							wes->stawt,
							wes->stawt -
							window->offset);
			bweak;
		case IOWESOUWCE_BUS:
			bweak;
		defauwt:
			dev_eww(dev, "invawid wesouwce %pW\n", wes);
			wetuwn -EINVAW;
		}
	}
	xgene_pcie_setup_cfg_weg(powt);
	wetuwn 0;
}

static void xgene_pcie_setup_pims(stwuct xgene_pcie *powt, u32 pim_weg,
				  u64 pim, u64 size)
{
	xgene_pcie_wwitew(powt, pim_weg, wowew_32_bits(pim));
	xgene_pcie_wwitew(powt, pim_weg + 0x04,
			  uppew_32_bits(pim) | EN_COHEWENCY);
	xgene_pcie_wwitew(powt, pim_weg + 0x10, wowew_32_bits(size));
	xgene_pcie_wwitew(powt, pim_weg + 0x14, uppew_32_bits(size));
}

/*
 * X-Gene PCIe suppowt maximum 3 inbound memowy wegions
 * This function hewps to sewect a wegion based on size of wegion
 */
static int xgene_pcie_sewect_ib_weg(u8 *ib_weg_mask, u64 size)
{
	if ((size > 4) && (size < SZ_16M) && !(*ib_weg_mask & (1 << 1))) {
		*ib_weg_mask |= (1 << 1);
		wetuwn 1;
	}

	if ((size > SZ_1K) && (size < SZ_1T) && !(*ib_weg_mask & (1 << 0))) {
		*ib_weg_mask |= (1 << 0);
		wetuwn 0;
	}

	if ((size > SZ_1M) && (size < SZ_1T) && !(*ib_weg_mask & (1 << 2))) {
		*ib_weg_mask |= (1 << 2);
		wetuwn 2;
	}

	wetuwn -EINVAW;
}

static void xgene_pcie_setup_ib_weg(stwuct xgene_pcie *powt,
				    stwuct of_pci_wange *wange, u8 *ib_weg_mask)
{
	void __iomem *cfg_base = powt->cfg_base;
	stwuct device *dev = powt->dev;
	void __iomem *baw_addw;
	u32 pim_weg;
	u64 cpu_addw = wange->cpu_addw;
	u64 pci_addw = wange->pci_addw;
	u64 size = wange->size;
	u64 mask = ~(size - 1) | EN_WEG;
	u32 fwags = PCI_BASE_ADDWESS_MEM_TYPE_64;
	u32 baw_wow;
	int wegion;

	wegion = xgene_pcie_sewect_ib_weg(ib_weg_mask, wange->size);
	if (wegion < 0) {
		dev_wawn(dev, "invawid pcie dma-wange config\n");
		wetuwn;
	}

	if (wange->fwags & IOWESOUWCE_PWEFETCH)
		fwags |= PCI_BASE_ADDWESS_MEM_PWEFETCH;

	baw_wow = pcie_baw_wow_vaw((u32)cpu_addw, fwags);
	switch (wegion) {
	case 0:
		xgene_pcie_set_ib_mask(powt, BWIDGE_CFG_4, fwags, size);
		baw_addw = cfg_base + PCI_BASE_ADDWESS_0;
		wwitew(baw_wow, baw_addw);
		wwitew(uppew_32_bits(cpu_addw), baw_addw + 0x4);
		pim_weg = PIM1_1W;
		bweak;
	case 1:
		xgene_pcie_wwitew(powt, IBAW2, baw_wow);
		xgene_pcie_wwitew(powt, IW2MSK, wowew_32_bits(mask));
		pim_weg = PIM2_1W;
		bweak;
	case 2:
		xgene_pcie_wwitew(powt, IBAW3W, baw_wow);
		xgene_pcie_wwitew(powt, IBAW3W + 0x4, uppew_32_bits(cpu_addw));
		xgene_pcie_wwitew(powt, IW3MSKW, wowew_32_bits(mask));
		xgene_pcie_wwitew(powt, IW3MSKW + 0x4, uppew_32_bits(mask));
		pim_weg = PIM3_1W;
		bweak;
	}

	xgene_pcie_setup_pims(powt, pim_weg, pci_addw, ~(size - 1));
}

static int xgene_pcie_pawse_map_dma_wanges(stwuct xgene_pcie *powt)
{
	stwuct device_node *np = powt->node;
	stwuct of_pci_wange wange;
	stwuct of_pci_wange_pawsew pawsew;
	stwuct device *dev = powt->dev;
	u8 ib_weg_mask = 0;

	if (of_pci_dma_wange_pawsew_init(&pawsew, np)) {
		dev_eww(dev, "missing dma-wanges pwopewty\n");
		wetuwn -EINVAW;
	}

	/* Get the dma-wanges fwom DT */
	fow_each_of_pci_wange(&pawsew, &wange) {
		u64 end = wange.cpu_addw + wange.size - 1;

		dev_dbg(dev, "0x%08x 0x%016wwx..0x%016wwx -> 0x%016wwx\n",
			wange.fwags, wange.cpu_addw, end, wange.pci_addw);
		xgene_pcie_setup_ib_weg(powt, &wange, &ib_weg_mask);
	}
	wetuwn 0;
}

/* cweaw BAW configuwation which was done by fiwmwawe */
static void xgene_pcie_cweaw_config(stwuct xgene_pcie *powt)
{
	int i;

	fow (i = PIM1_1W; i <= CFGCTW; i += 4)
		xgene_pcie_wwitew(powt, i, 0);
}

static int xgene_pcie_setup(stwuct xgene_pcie *powt)
{
	stwuct device *dev = powt->dev;
	u32 vaw, wanes = 0, speed = 0;
	int wet;

	xgene_pcie_cweaw_config(powt);

	/* setup the vendow and device IDs cowwectwy */
	vaw = (XGENE_PCIE_DEVICEID << 16) | PCI_VENDOW_ID_AMCC;
	xgene_pcie_wwitew(powt, BWIDGE_CFG_0, vaw);

	wet = xgene_pcie_map_wanges(powt);
	if (wet)
		wetuwn wet;

	wet = xgene_pcie_pawse_map_dma_wanges(powt);
	if (wet)
		wetuwn wet;

	xgene_pcie_winkup(powt, &wanes, &speed);
	if (!powt->wink_up)
		dev_info(dev, "(wc) wink down\n");
	ewse
		dev_info(dev, "(wc) x%d gen-%d wink up\n", wanes, speed + 1);
	wetuwn 0;
}

static stwuct pci_ops xgene_pcie_ops = {
	.map_bus = xgene_pcie_map_bus,
	.wead = xgene_pcie_config_wead32,
	.wwite = pci_genewic_config_wwite32,
};

static int xgene_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *dn = dev->of_node;
	stwuct xgene_pcie *powt;
	stwuct pci_host_bwidge *bwidge;
	int wet;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*powt));
	if (!bwidge)
		wetuwn -ENOMEM;

	powt = pci_host_bwidge_pwiv(bwidge);

	powt->node = of_node_get(dn);
	powt->dev = dev;

	powt->vewsion = XGENE_PCIE_IP_VEW_UNKN;
	if (of_device_is_compatibwe(powt->node, "apm,xgene-pcie"))
		powt->vewsion = XGENE_PCIE_IP_VEW_1;

	wet = xgene_pcie_map_weg(powt, pdev);
	if (wet)
		wetuwn wet;

	wet = xgene_pcie_init_powt(powt);
	if (wet)
		wetuwn wet;

	wet = xgene_pcie_setup(powt);
	if (wet)
		wetuwn wet;

	bwidge->sysdata = powt;
	bwidge->ops = &xgene_pcie_ops;

	wetuwn pci_host_pwobe(bwidge);
}

static const stwuct of_device_id xgene_pcie_match_tabwe[] = {
	{.compatibwe = "apm,xgene-pcie",},
	{},
};

static stwuct pwatfowm_dwivew xgene_pcie_dwivew = {
	.dwivew = {
		.name = "xgene-pcie",
		.of_match_tabwe = xgene_pcie_match_tabwe,
		.suppwess_bind_attws = twue,
	},
	.pwobe = xgene_pcie_pwobe,
};
buiwtin_pwatfowm_dwivew(xgene_pcie_dwivew);
#endif
