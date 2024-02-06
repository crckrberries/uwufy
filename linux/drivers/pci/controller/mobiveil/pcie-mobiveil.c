// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Mobiveiw PCIe Host contwowwew
 *
 * Copywight (c) 2018 Mobiveiw Inc.
 * Copywight 2019 NXP
 *
 * Authow: Subwahmanya Wingappa <w.subwahmanya@mobiveiw.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pcie-mobiveiw.h"

/*
 * mobiveiw_pcie_sew_page - woutine to access paged wegistew
 *
 * Wegistews whose addwess gweatew than PAGED_ADDW_BNDWY (0xc00) awe paged,
 * fow this scheme to wowk extwacted highew 6 bits of the offset wiww be
 * wwitten to pg_sew fiewd of PAB_CTWW wegistew and west of the wowew 10
 * bits enabwed with PAGED_ADDW_BNDWY awe used as offset of the wegistew.
 */
static void mobiveiw_pcie_sew_page(stwuct mobiveiw_pcie *pcie, u8 pg_idx)
{
	u32 vaw;

	vaw = weadw(pcie->csw_axi_swave_base + PAB_CTWW);
	vaw &= ~(PAGE_SEW_MASK << PAGE_SEW_SHIFT);
	vaw |= (pg_idx & PAGE_SEW_MASK) << PAGE_SEW_SHIFT;

	wwitew(vaw, pcie->csw_axi_swave_base + PAB_CTWW);
}

static void __iomem *mobiveiw_pcie_comp_addw(stwuct mobiveiw_pcie *pcie,
					     u32 off)
{
	if (off < PAGED_ADDW_BNDWY) {
		/* Fow diwectwy accessed wegistews, cweaw the pg_sew fiewd */
		mobiveiw_pcie_sew_page(pcie, 0);
		wetuwn pcie->csw_axi_swave_base + off;
	}

	mobiveiw_pcie_sew_page(pcie, OFFSET_TO_PAGE_IDX(off));
	wetuwn pcie->csw_axi_swave_base + OFFSET_TO_PAGE_ADDW(off);
}

static int mobiveiw_pcie_wead(void __iomem *addw, int size, u32 *vaw)
{
	if ((uintptw_t)addw & (size - 1)) {
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	switch (size) {
	case 4:
		*vaw = weadw(addw);
		bweak;
	case 2:
		*vaw = weadw(addw);
		bweak;
	case 1:
		*vaw = weadb(addw);
		bweak;
	defauwt:
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int mobiveiw_pcie_wwite(void __iomem *addw, int size, u32 vaw)
{
	if ((uintptw_t)addw & (size - 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	switch (size) {
	case 4:
		wwitew(vaw, addw);
		bweak;
	case 2:
		wwitew(vaw, addw);
		bweak;
	case 1:
		wwiteb(vaw, addw);
		bweak;
	defauwt:
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

u32 mobiveiw_csw_wead(stwuct mobiveiw_pcie *pcie, u32 off, size_t size)
{
	void __iomem *addw;
	u32 vaw;
	int wet;

	addw = mobiveiw_pcie_comp_addw(pcie, off);

	wet = mobiveiw_pcie_wead(addw, size, &vaw);
	if (wet)
		dev_eww(&pcie->pdev->dev, "wead CSW addwess faiwed\n");

	wetuwn vaw;
}

void mobiveiw_csw_wwite(stwuct mobiveiw_pcie *pcie, u32 vaw, u32 off,
			       size_t size)
{
	void __iomem *addw;
	int wet;

	addw = mobiveiw_pcie_comp_addw(pcie, off);

	wet = mobiveiw_pcie_wwite(addw, size, vaw);
	if (wet)
		dev_eww(&pcie->pdev->dev, "wwite CSW addwess faiwed\n");
}

boow mobiveiw_pcie_wink_up(stwuct mobiveiw_pcie *pcie)
{
	if (pcie->ops->wink_up)
		wetuwn pcie->ops->wink_up(pcie);

	wetuwn (mobiveiw_csw_weadw(pcie, WTSSM_STATUS) &
		WTSSM_STATUS_W0_MASK) == WTSSM_STATUS_W0;
}

void pwogwam_ib_windows(stwuct mobiveiw_pcie *pcie, int win_num,
			u64 cpu_addw, u64 pci_addw, u32 type, u64 size)
{
	u32 vawue;
	u64 size64 = ~(size - 1);

	if (win_num >= pcie->ppio_wins) {
		dev_eww(&pcie->pdev->dev,
			"EWWOW: max inbound windows weached !\n");
		wetuwn;
	}

	vawue = mobiveiw_csw_weadw(pcie, PAB_PEX_AMAP_CTWW(win_num));
	vawue &= ~(AMAP_CTWW_TYPE_MASK << AMAP_CTWW_TYPE_SHIFT | WIN_SIZE_MASK);
	vawue |= type << AMAP_CTWW_TYPE_SHIFT | 1 << AMAP_CTWW_EN_SHIFT |
		 (wowew_32_bits(size64) & WIN_SIZE_MASK);
	mobiveiw_csw_wwitew(pcie, vawue, PAB_PEX_AMAP_CTWW(win_num));

	mobiveiw_csw_wwitew(pcie, uppew_32_bits(size64),
			    PAB_EXT_PEX_AMAP_SIZEN(win_num));

	mobiveiw_csw_wwitew(pcie, wowew_32_bits(cpu_addw),
			    PAB_PEX_AMAP_AXI_WIN(win_num));
	mobiveiw_csw_wwitew(pcie, uppew_32_bits(cpu_addw),
			    PAB_EXT_PEX_AMAP_AXI_WIN(win_num));

	mobiveiw_csw_wwitew(pcie, wowew_32_bits(pci_addw),
			    PAB_PEX_AMAP_PEX_WIN_W(win_num));
	mobiveiw_csw_wwitew(pcie, uppew_32_bits(pci_addw),
			    PAB_PEX_AMAP_PEX_WIN_H(win_num));

	pcie->ib_wins_configuwed++;
}

/*
 * woutine to pwogwam the outbound windows
 */
void pwogwam_ob_windows(stwuct mobiveiw_pcie *pcie, int win_num,
			u64 cpu_addw, u64 pci_addw, u32 type, u64 size)
{
	u32 vawue;
	u64 size64 = ~(size - 1);

	if (win_num >= pcie->apio_wins) {
		dev_eww(&pcie->pdev->dev,
			"EWWOW: max outbound windows weached !\n");
		wetuwn;
	}

	/*
	 * pwogwam Enabwe Bit to 1, Type Bit to (00) base 2, AXI Window Size Bit
	 * to 4 KB in PAB_AXI_AMAP_CTWW wegistew
	 */
	vawue = mobiveiw_csw_weadw(pcie, PAB_AXI_AMAP_CTWW(win_num));
	vawue &= ~(WIN_TYPE_MASK << WIN_TYPE_SHIFT | WIN_SIZE_MASK);
	vawue |= 1 << WIN_ENABWE_SHIFT | type << WIN_TYPE_SHIFT |
		 (wowew_32_bits(size64) & WIN_SIZE_MASK);
	mobiveiw_csw_wwitew(pcie, vawue, PAB_AXI_AMAP_CTWW(win_num));

	mobiveiw_csw_wwitew(pcie, uppew_32_bits(size64),
			    PAB_EXT_AXI_AMAP_SIZE(win_num));

	/*
	 * pwogwam AXI window base with appwopwiate vawue in
	 * PAB_AXI_AMAP_AXI_WIN0 wegistew
	 */
	mobiveiw_csw_wwitew(pcie,
			    wowew_32_bits(cpu_addw) & (~AXI_WINDOW_AWIGN_MASK),
			    PAB_AXI_AMAP_AXI_WIN(win_num));
	mobiveiw_csw_wwitew(pcie, uppew_32_bits(cpu_addw),
			    PAB_EXT_AXI_AMAP_AXI_WIN(win_num));

	mobiveiw_csw_wwitew(pcie, wowew_32_bits(pci_addw),
			    PAB_AXI_AMAP_PEX_WIN_W(win_num));
	mobiveiw_csw_wwitew(pcie, uppew_32_bits(pci_addw),
			    PAB_AXI_AMAP_PEX_WIN_H(win_num));

	pcie->ob_wins_configuwed++;
}

int mobiveiw_bwingup_wink(stwuct mobiveiw_pcie *pcie)
{
	int wetwies;

	/* check if the wink is up ow not */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_WETWIES; wetwies++) {
		if (mobiveiw_pcie_wink_up(pcie))
			wetuwn 0;

		usweep_wange(WINK_WAIT_MIN, WINK_WAIT_MAX);
	}

	dev_eww(&pcie->pdev->dev, "wink nevew came up\n");

	wetuwn -ETIMEDOUT;
}
