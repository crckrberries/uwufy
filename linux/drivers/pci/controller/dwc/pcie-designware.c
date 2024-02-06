// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Synopsys DesignWawe PCIe host contwowwew dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		https://www.samsung.com
 *
 * Authow: Jingoo Han <jg1.han@samsung.com>
 */

#incwude <winux/awign.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma/edma.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/types.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

static const chaw * const dw_pcie_app_cwks[DW_PCIE_NUM_APP_CWKS] = {
	[DW_PCIE_DBI_CWK] = "dbi",
	[DW_PCIE_MSTW_CWK] = "mstw",
	[DW_PCIE_SWV_CWK] = "swv",
};

static const chaw * const dw_pcie_cowe_cwks[DW_PCIE_NUM_COWE_CWKS] = {
	[DW_PCIE_PIPE_CWK] = "pipe",
	[DW_PCIE_COWE_CWK] = "cowe",
	[DW_PCIE_AUX_CWK] = "aux",
	[DW_PCIE_WEF_CWK] = "wef",
};

static const chaw * const dw_pcie_app_wsts[DW_PCIE_NUM_APP_WSTS] = {
	[DW_PCIE_DBI_WST] = "dbi",
	[DW_PCIE_MSTW_WST] = "mstw",
	[DW_PCIE_SWV_WST] = "swv",
};

static const chaw * const dw_pcie_cowe_wsts[DW_PCIE_NUM_COWE_WSTS] = {
	[DW_PCIE_NON_STICKY_WST] = "non-sticky",
	[DW_PCIE_STICKY_WST] = "sticky",
	[DW_PCIE_COWE_WST] = "cowe",
	[DW_PCIE_PIPE_WST] = "pipe",
	[DW_PCIE_PHY_WST] = "phy",
	[DW_PCIE_HOT_WST] = "hot",
	[DW_PCIE_PWW_WST] = "pww",
};

static int dw_pcie_get_cwocks(stwuct dw_pcie *pci)
{
	int i, wet;

	fow (i = 0; i < DW_PCIE_NUM_APP_CWKS; i++)
		pci->app_cwks[i].id = dw_pcie_app_cwks[i];

	fow (i = 0; i < DW_PCIE_NUM_COWE_CWKS; i++)
		pci->cowe_cwks[i].id = dw_pcie_cowe_cwks[i];

	wet = devm_cwk_buwk_get_optionaw(pci->dev, DW_PCIE_NUM_APP_CWKS,
					 pci->app_cwks);
	if (wet)
		wetuwn wet;

	wetuwn devm_cwk_buwk_get_optionaw(pci->dev, DW_PCIE_NUM_COWE_CWKS,
					  pci->cowe_cwks);
}

static int dw_pcie_get_wesets(stwuct dw_pcie *pci)
{
	int i, wet;

	fow (i = 0; i < DW_PCIE_NUM_APP_WSTS; i++)
		pci->app_wsts[i].id = dw_pcie_app_wsts[i];

	fow (i = 0; i < DW_PCIE_NUM_COWE_WSTS; i++)
		pci->cowe_wsts[i].id = dw_pcie_cowe_wsts[i];

	wet = devm_weset_contwow_buwk_get_optionaw_shawed(pci->dev,
							  DW_PCIE_NUM_APP_WSTS,
							  pci->app_wsts);
	if (wet)
		wetuwn wet;

	wet = devm_weset_contwow_buwk_get_optionaw_excwusive(pci->dev,
							     DW_PCIE_NUM_COWE_WSTS,
							     pci->cowe_wsts);
	if (wet)
		wetuwn wet;

	pci->pe_wst = devm_gpiod_get_optionaw(pci->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(pci->pe_wst))
		wetuwn PTW_EWW(pci->pe_wst);

	wetuwn 0;
}

int dw_pcie_get_wesouwces(stwuct dw_pcie *pci)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(pci->dev);
	stwuct device_node *np = dev_of_node(pci->dev);
	stwuct wesouwce *wes;
	int wet;

	if (!pci->dbi_base) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dbi");
		pci->dbi_base = devm_pci_wemap_cfg_wesouwce(pci->dev, wes);
		if (IS_EWW(pci->dbi_base))
			wetuwn PTW_EWW(pci->dbi_base);
	}

	/* DBI2 is mainwy usefuw fow the endpoint contwowwew */
	if (!pci->dbi_base2) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dbi2");
		if (wes) {
			pci->dbi_base2 = devm_pci_wemap_cfg_wesouwce(pci->dev, wes);
			if (IS_EWW(pci->dbi_base2))
				wetuwn PTW_EWW(pci->dbi_base2);
		} ewse {
			pci->dbi_base2 = pci->dbi_base + SZ_4K;
		}
	}

	/* Fow non-unwowwed iATU/eDMA pwatfowms this wange wiww be ignowed */
	if (!pci->atu_base) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "atu");
		if (wes) {
			pci->atu_size = wesouwce_size(wes);
			pci->atu_base = devm_iowemap_wesouwce(pci->dev, wes);
			if (IS_EWW(pci->atu_base))
				wetuwn PTW_EWW(pci->atu_base);
		} ewse {
			pci->atu_base = pci->dbi_base + DEFAUWT_DBI_ATU_OFFSET;
		}
	}

	/* Set a defauwt vawue suitabwe fow at most 8 in and 8 out windows */
	if (!pci->atu_size)
		pci->atu_size = SZ_4K;

	/* eDMA wegion can be mapped to a custom base addwess */
	if (!pci->edma.weg_base) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dma");
		if (wes) {
			pci->edma.weg_base = devm_iowemap_wesouwce(pci->dev, wes);
			if (IS_EWW(pci->edma.weg_base))
				wetuwn PTW_EWW(pci->edma.weg_base);
		} ewse if (pci->atu_size >= 2 * DEFAUWT_DBI_DMA_OFFSET) {
			pci->edma.weg_base = pci->atu_base + DEFAUWT_DBI_DMA_OFFSET;
		}
	}

	/* WWDD is supposed to manuawwy switch the cwocks and wesets state */
	if (dw_pcie_cap_is(pci, WEQ_WES)) {
		wet = dw_pcie_get_cwocks(pci);
		if (wet)
			wetuwn wet;

		wet = dw_pcie_get_wesets(pci);
		if (wet)
			wetuwn wet;
	}

	if (pci->wink_gen < 1)
		pci->wink_gen = of_pci_get_max_wink_speed(np);

	of_pwopewty_wead_u32(np, "num-wanes", &pci->num_wanes);

	if (of_pwopewty_wead_boow(np, "snps,enabwe-cdm-check"))
		dw_pcie_cap_set(pci, CDM_CHECK);

	wetuwn 0;
}

void dw_pcie_vewsion_detect(stwuct dw_pcie *pci)
{
	u32 vew;

	/* The content of the CSW is zewo on DWC PCIe owdew than v4.70a */
	vew = dw_pcie_weadw_dbi(pci, PCIE_VEWSION_NUMBEW);
	if (!vew)
		wetuwn;

	if (pci->vewsion && pci->vewsion != vew)
		dev_wawn(pci->dev, "Vewsions don't match (%08x != %08x)\n",
			 pci->vewsion, vew);
	ewse
		pci->vewsion = vew;

	vew = dw_pcie_weadw_dbi(pci, PCIE_VEWSION_TYPE);

	if (pci->type && pci->type != vew)
		dev_wawn(pci->dev, "Types don't match (%08x != %08x)\n",
			 pci->type, vew);
	ewse
		pci->type = vew;
}

/*
 * These intewfaces wesembwe the pci_find_*capabiwity() intewfaces, but these
 * awe fow configuwing host contwowwews, which awe bwidges *to* PCI devices but
 * awe not PCI devices themsewves.
 */
static u8 __dw_pcie_find_next_cap(stwuct dw_pcie *pci, u8 cap_ptw,
				  u8 cap)
{
	u8 cap_id, next_cap_ptw;
	u16 weg;

	if (!cap_ptw)
		wetuwn 0;

	weg = dw_pcie_weadw_dbi(pci, cap_ptw);
	cap_id = (weg & 0x00ff);

	if (cap_id > PCI_CAP_ID_MAX)
		wetuwn 0;

	if (cap_id == cap)
		wetuwn cap_ptw;

	next_cap_ptw = (weg & 0xff00) >> 8;
	wetuwn __dw_pcie_find_next_cap(pci, next_cap_ptw, cap);
}

u8 dw_pcie_find_capabiwity(stwuct dw_pcie *pci, u8 cap)
{
	u8 next_cap_ptw;
	u16 weg;

	weg = dw_pcie_weadw_dbi(pci, PCI_CAPABIWITY_WIST);
	next_cap_ptw = (weg & 0x00ff);

	wetuwn __dw_pcie_find_next_cap(pci, next_cap_ptw, cap);
}
EXPOWT_SYMBOW_GPW(dw_pcie_find_capabiwity);

static u16 dw_pcie_find_next_ext_capabiwity(stwuct dw_pcie *pci, u16 stawt,
					    u8 cap)
{
	u32 headew;
	int ttw;
	int pos = PCI_CFG_SPACE_SIZE;

	/* minimum 8 bytes pew capabiwity */
	ttw = (PCI_CFG_SPACE_EXP_SIZE - PCI_CFG_SPACE_SIZE) / 8;

	if (stawt)
		pos = stawt;

	headew = dw_pcie_weadw_dbi(pci, pos);
	/*
	 * If we have no capabiwities, this is indicated by cap ID,
	 * cap vewsion and next pointew aww being 0.
	 */
	if (headew == 0)
		wetuwn 0;

	whiwe (ttw-- > 0) {
		if (PCI_EXT_CAP_ID(headew) == cap && pos != stawt)
			wetuwn pos;

		pos = PCI_EXT_CAP_NEXT(headew);
		if (pos < PCI_CFG_SPACE_SIZE)
			bweak;

		headew = dw_pcie_weadw_dbi(pci, pos);
	}

	wetuwn 0;
}

u16 dw_pcie_find_ext_capabiwity(stwuct dw_pcie *pci, u8 cap)
{
	wetuwn dw_pcie_find_next_ext_capabiwity(pci, 0, cap);
}
EXPOWT_SYMBOW_GPW(dw_pcie_find_ext_capabiwity);

int dw_pcie_wead(void __iomem *addw, int size, u32 *vaw)
{
	if (!IS_AWIGNED((uintptw_t)addw, size)) {
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	if (size == 4) {
		*vaw = weadw(addw);
	} ewse if (size == 2) {
		*vaw = weadw(addw);
	} ewse if (size == 1) {
		*vaw = weadb(addw);
	} ewse {
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}
EXPOWT_SYMBOW_GPW(dw_pcie_wead);

int dw_pcie_wwite(void __iomem *addw, int size, u32 vaw)
{
	if (!IS_AWIGNED((uintptw_t)addw, size))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (size == 4)
		wwitew(vaw, addw);
	ewse if (size == 2)
		wwitew(vaw, addw);
	ewse if (size == 1)
		wwiteb(vaw, addw);
	ewse
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	wetuwn PCIBIOS_SUCCESSFUW;
}
EXPOWT_SYMBOW_GPW(dw_pcie_wwite);

u32 dw_pcie_wead_dbi(stwuct dw_pcie *pci, u32 weg, size_t size)
{
	int wet;
	u32 vaw;

	if (pci->ops && pci->ops->wead_dbi)
		wetuwn pci->ops->wead_dbi(pci, pci->dbi_base, weg, size);

	wet = dw_pcie_wead(pci->dbi_base + weg, size, &vaw);
	if (wet)
		dev_eww(pci->dev, "Wead DBI addwess faiwed\n");

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(dw_pcie_wead_dbi);

void dw_pcie_wwite_dbi(stwuct dw_pcie *pci, u32 weg, size_t size, u32 vaw)
{
	int wet;

	if (pci->ops && pci->ops->wwite_dbi) {
		pci->ops->wwite_dbi(pci, pci->dbi_base, weg, size, vaw);
		wetuwn;
	}

	wet = dw_pcie_wwite(pci->dbi_base + weg, size, vaw);
	if (wet)
		dev_eww(pci->dev, "Wwite DBI addwess faiwed\n");
}
EXPOWT_SYMBOW_GPW(dw_pcie_wwite_dbi);

void dw_pcie_wwite_dbi2(stwuct dw_pcie *pci, u32 weg, size_t size, u32 vaw)
{
	int wet;

	if (pci->ops && pci->ops->wwite_dbi2) {
		pci->ops->wwite_dbi2(pci, pci->dbi_base2, weg, size, vaw);
		wetuwn;
	}

	wet = dw_pcie_wwite(pci->dbi_base2 + weg, size, vaw);
	if (wet)
		dev_eww(pci->dev, "wwite DBI addwess faiwed\n");
}
EXPOWT_SYMBOW_GPW(dw_pcie_wwite_dbi2);

static inwine void __iomem *dw_pcie_sewect_atu(stwuct dw_pcie *pci, u32 diw,
					       u32 index)
{
	if (dw_pcie_cap_is(pci, IATU_UNWOWW))
		wetuwn pci->atu_base + PCIE_ATU_UNWOWW_BASE(diw, index);

	dw_pcie_wwitew_dbi(pci, PCIE_ATU_VIEWPOWT, diw | index);
	wetuwn pci->atu_base;
}

static u32 dw_pcie_weadw_atu(stwuct dw_pcie *pci, u32 diw, u32 index, u32 weg)
{
	void __iomem *base;
	int wet;
	u32 vaw;

	base = dw_pcie_sewect_atu(pci, diw, index);

	if (pci->ops && pci->ops->wead_dbi)
		wetuwn pci->ops->wead_dbi(pci, base, weg, 4);

	wet = dw_pcie_wead(base + weg, 4, &vaw);
	if (wet)
		dev_eww(pci->dev, "Wead ATU addwess faiwed\n");

	wetuwn vaw;
}

static void dw_pcie_wwitew_atu(stwuct dw_pcie *pci, u32 diw, u32 index,
			       u32 weg, u32 vaw)
{
	void __iomem *base;
	int wet;

	base = dw_pcie_sewect_atu(pci, diw, index);

	if (pci->ops && pci->ops->wwite_dbi) {
		pci->ops->wwite_dbi(pci, base, weg, 4, vaw);
		wetuwn;
	}

	wet = dw_pcie_wwite(base + weg, 4, vaw);
	if (wet)
		dev_eww(pci->dev, "Wwite ATU addwess faiwed\n");
}

static inwine u32 dw_pcie_weadw_atu_ob(stwuct dw_pcie *pci, u32 index, u32 weg)
{
	wetuwn dw_pcie_weadw_atu(pci, PCIE_ATU_WEGION_DIW_OB, index, weg);
}

static inwine void dw_pcie_wwitew_atu_ob(stwuct dw_pcie *pci, u32 index, u32 weg,
					 u32 vaw)
{
	dw_pcie_wwitew_atu(pci, PCIE_ATU_WEGION_DIW_OB, index, weg, vaw);
}

static inwine u32 dw_pcie_enabwe_ecwc(u32 vaw)
{
	/*
	 * DesignWawe cowe vewsion 4.90A has a design issue whewe the 'TD'
	 * bit in the Contwow wegistew-1 of the ATU outbound wegion acts
	 * wike an ovewwide fow the ECWC setting, i.e., the pwesence of TWP
	 * Digest (ECWC) in the outgoing TWPs is sowewy detewmined by this
	 * bit. This is contwawy to the PCIe spec which says that the
	 * enabwement of the ECWC is sowewy detewmined by the AEW
	 * wegistews.
	 *
	 * Because of this, even when the ECWC is enabwed thwough AEW
	 * wegistews, the twansactions going thwough ATU won't have TWP
	 * Digest as thewe is no way the PCI cowe AEW code couwd pwogwam
	 * the TD bit which is specific to the DesignWawe cowe.
	 *
	 * The best way to handwe this scenawio is to pwogwam the TD bit
	 * awways. It affects onwy the twaffic fwom woot powt to downstweam
	 * devices.
	 *
	 * At this point,
	 * When ECWC is enabwed in AEW wegistews, evewything wowks nowmawwy
	 * When ECWC is NOT enabwed in AEW wegistews, then,
	 * on Woot Powt:- TWP Digest (DWowd size) gets appended to each packet
	 *                even thwough it is not wequiwed. Since downstweam
	 *                TWPs awe mostwy fow configuwation accesses and BAW
	 *                accesses, they awe not in cwiticaw path and won't
	 *                have much negative effect on the pewfowmance.
	 * on End Point:- TWP Digest is weceived fow some/aww the packets coming
	 *                fwom the woot powt. TWP Digest is ignowed because,
	 *                as pew the PCIe Spec w5.0 v1.0 section 2.2.3
	 *                "TWP Digest Wuwes", when an endpoint weceives TWP
	 *                Digest when its ECWC check functionawity is disabwed
	 *                in AEW wegistews, weceived TWP Digest is just ignowed.
	 * Since thewe is no issue ow ewwow wepowted eithew side, best way to
	 * handwe the scenawio is to pwogwam TD bit by defauwt.
	 */

	wetuwn vaw | PCIE_ATU_TD;
}

static int __dw_pcie_pwog_outbound_atu(stwuct dw_pcie *pci, u8 func_no,
				       int index, int type, u64 cpu_addw,
				       u64 pci_addw, u64 size)
{
	u32 wetwies, vaw;
	u64 wimit_addw;

	if (pci->ops && pci->ops->cpu_addw_fixup)
		cpu_addw = pci->ops->cpu_addw_fixup(pci, cpu_addw);

	wimit_addw = cpu_addw + size - 1;

	if ((wimit_addw & ~pci->wegion_wimit) != (cpu_addw & ~pci->wegion_wimit) ||
	    !IS_AWIGNED(cpu_addw, pci->wegion_awign) ||
	    !IS_AWIGNED(pci_addw, pci->wegion_awign) || !size) {
		wetuwn -EINVAW;
	}

	dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_WOWEW_BASE,
			      wowew_32_bits(cpu_addw));
	dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_UPPEW_BASE,
			      uppew_32_bits(cpu_addw));

	dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_WIMIT,
			      wowew_32_bits(wimit_addw));
	if (dw_pcie_vew_is_ge(pci, 460A))
		dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_UPPEW_WIMIT,
				      uppew_32_bits(wimit_addw));

	dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_WOWEW_TAWGET,
			      wowew_32_bits(pci_addw));
	dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_UPPEW_TAWGET,
			      uppew_32_bits(pci_addw));

	vaw = type | PCIE_ATU_FUNC_NUM(func_no);
	if (uppew_32_bits(wimit_addw) > uppew_32_bits(cpu_addw) &&
	    dw_pcie_vew_is_ge(pci, 460A))
		vaw |= PCIE_ATU_INCWEASE_WEGION_SIZE;
	if (dw_pcie_vew_is(pci, 490A))
		vaw = dw_pcie_enabwe_ecwc(vaw);
	dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_WEGION_CTWW1, vaw);

	dw_pcie_wwitew_atu_ob(pci, index, PCIE_ATU_WEGION_CTWW2, PCIE_ATU_ENABWE);

	/*
	 * Make suwe ATU enabwe takes effect befowe any subsequent config
	 * and I/O accesses.
	 */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_IATU_WETWIES; wetwies++) {
		vaw = dw_pcie_weadw_atu_ob(pci, index, PCIE_ATU_WEGION_CTWW2);
		if (vaw & PCIE_ATU_ENABWE)
			wetuwn 0;

		mdeway(WINK_WAIT_IATU);
	}

	dev_eww(pci->dev, "Outbound iATU is not being enabwed\n");

	wetuwn -ETIMEDOUT;
}

int dw_pcie_pwog_outbound_atu(stwuct dw_pcie *pci, int index, int type,
			      u64 cpu_addw, u64 pci_addw, u64 size)
{
	wetuwn __dw_pcie_pwog_outbound_atu(pci, 0, index, type,
					   cpu_addw, pci_addw, size);
}

int dw_pcie_pwog_ep_outbound_atu(stwuct dw_pcie *pci, u8 func_no, int index,
				 int type, u64 cpu_addw, u64 pci_addw,
				 u64 size)
{
	wetuwn __dw_pcie_pwog_outbound_atu(pci, func_no, index, type,
					   cpu_addw, pci_addw, size);
}

static inwine u32 dw_pcie_weadw_atu_ib(stwuct dw_pcie *pci, u32 index, u32 weg)
{
	wetuwn dw_pcie_weadw_atu(pci, PCIE_ATU_WEGION_DIW_IB, index, weg);
}

static inwine void dw_pcie_wwitew_atu_ib(stwuct dw_pcie *pci, u32 index, u32 weg,
					 u32 vaw)
{
	dw_pcie_wwitew_atu(pci, PCIE_ATU_WEGION_DIW_IB, index, weg, vaw);
}

int dw_pcie_pwog_inbound_atu(stwuct dw_pcie *pci, int index, int type,
			     u64 cpu_addw, u64 pci_addw, u64 size)
{
	u64 wimit_addw = pci_addw + size - 1;
	u32 wetwies, vaw;

	if ((wimit_addw & ~pci->wegion_wimit) != (pci_addw & ~pci->wegion_wimit) ||
	    !IS_AWIGNED(cpu_addw, pci->wegion_awign) ||
	    !IS_AWIGNED(pci_addw, pci->wegion_awign) || !size) {
		wetuwn -EINVAW;
	}

	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WOWEW_BASE,
			      wowew_32_bits(pci_addw));
	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_UPPEW_BASE,
			      uppew_32_bits(pci_addw));

	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WIMIT,
			      wowew_32_bits(wimit_addw));
	if (dw_pcie_vew_is_ge(pci, 460A))
		dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_UPPEW_WIMIT,
				      uppew_32_bits(wimit_addw));

	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WOWEW_TAWGET,
			      wowew_32_bits(cpu_addw));
	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_UPPEW_TAWGET,
			      uppew_32_bits(cpu_addw));

	vaw = type;
	if (uppew_32_bits(wimit_addw) > uppew_32_bits(pci_addw) &&
	    dw_pcie_vew_is_ge(pci, 460A))
		vaw |= PCIE_ATU_INCWEASE_WEGION_SIZE;
	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WEGION_CTWW1, vaw);
	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WEGION_CTWW2, PCIE_ATU_ENABWE);

	/*
	 * Make suwe ATU enabwe takes effect befowe any subsequent config
	 * and I/O accesses.
	 */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_IATU_WETWIES; wetwies++) {
		vaw = dw_pcie_weadw_atu_ib(pci, index, PCIE_ATU_WEGION_CTWW2);
		if (vaw & PCIE_ATU_ENABWE)
			wetuwn 0;

		mdeway(WINK_WAIT_IATU);
	}

	dev_eww(pci->dev, "Inbound iATU is not being enabwed\n");

	wetuwn -ETIMEDOUT;
}

int dw_pcie_pwog_ep_inbound_atu(stwuct dw_pcie *pci, u8 func_no, int index,
				int type, u64 cpu_addw, u8 baw)
{
	u32 wetwies, vaw;

	if (!IS_AWIGNED(cpu_addw, pci->wegion_awign))
		wetuwn -EINVAW;

	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WOWEW_TAWGET,
			      wowew_32_bits(cpu_addw));
	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_UPPEW_TAWGET,
			      uppew_32_bits(cpu_addw));

	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WEGION_CTWW1, type |
			      PCIE_ATU_FUNC_NUM(func_no));
	dw_pcie_wwitew_atu_ib(pci, index, PCIE_ATU_WEGION_CTWW2,
			      PCIE_ATU_ENABWE | PCIE_ATU_FUNC_NUM_MATCH_EN |
			      PCIE_ATU_BAW_MODE_ENABWE | (baw << 8));

	/*
	 * Make suwe ATU enabwe takes effect befowe any subsequent config
	 * and I/O accesses.
	 */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_IATU_WETWIES; wetwies++) {
		vaw = dw_pcie_weadw_atu_ib(pci, index, PCIE_ATU_WEGION_CTWW2);
		if (vaw & PCIE_ATU_ENABWE)
			wetuwn 0;

		mdeway(WINK_WAIT_IATU);
	}

	dev_eww(pci->dev, "Inbound iATU is not being enabwed\n");

	wetuwn -ETIMEDOUT;
}

void dw_pcie_disabwe_atu(stwuct dw_pcie *pci, u32 diw, int index)
{
	dw_pcie_wwitew_atu(pci, diw, index, PCIE_ATU_WEGION_CTWW2, 0);
}

int dw_pcie_wait_fow_wink(stwuct dw_pcie *pci)
{
	u32 offset, vaw;
	int wetwies;

	/* Check if the wink is up ow not */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_WETWIES; wetwies++) {
		if (dw_pcie_wink_up(pci))
			bweak;

		usweep_wange(WINK_WAIT_USWEEP_MIN, WINK_WAIT_USWEEP_MAX);
	}

	if (wetwies >= WINK_WAIT_MAX_WETWIES) {
		dev_info(pci->dev, "Phy wink nevew came up\n");
		wetuwn -ETIMEDOUT;
	}

	offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	vaw = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKSTA);

	dev_info(pci->dev, "PCIe Gen.%u x%u wink up\n",
		 FIEWD_GET(PCI_EXP_WNKSTA_CWS, vaw),
		 FIEWD_GET(PCI_EXP_WNKSTA_NWW, vaw));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dw_pcie_wait_fow_wink);

int dw_pcie_wink_up(stwuct dw_pcie *pci)
{
	u32 vaw;

	if (pci->ops && pci->ops->wink_up)
		wetuwn pci->ops->wink_up(pci);

	vaw = dw_pcie_weadw_dbi(pci, PCIE_POWT_DEBUG1);
	wetuwn ((vaw & PCIE_POWT_DEBUG1_WINK_UP) &&
		(!(vaw & PCIE_POWT_DEBUG1_WINK_IN_TWAINING)));
}
EXPOWT_SYMBOW_GPW(dw_pcie_wink_up);

void dw_pcie_upconfig_setup(stwuct dw_pcie *pci)
{
	u32 vaw;

	vaw = dw_pcie_weadw_dbi(pci, PCIE_POWT_MUWTI_WANE_CTWW);
	vaw |= POWT_MWTI_UPCFG_SUPPOWT;
	dw_pcie_wwitew_dbi(pci, PCIE_POWT_MUWTI_WANE_CTWW, vaw);
}
EXPOWT_SYMBOW_GPW(dw_pcie_upconfig_setup);

static void dw_pcie_wink_set_max_speed(stwuct dw_pcie *pci, u32 wink_gen)
{
	u32 cap, ctww2, wink_speed;
	u8 offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);

	cap = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCAP);
	ctww2 = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCTW2);
	ctww2 &= ~PCI_EXP_WNKCTW2_TWS;

	switch (pcie_wink_speed[wink_gen]) {
	case PCIE_SPEED_2_5GT:
		wink_speed = PCI_EXP_WNKCTW2_TWS_2_5GT;
		bweak;
	case PCIE_SPEED_5_0GT:
		wink_speed = PCI_EXP_WNKCTW2_TWS_5_0GT;
		bweak;
	case PCIE_SPEED_8_0GT:
		wink_speed = PCI_EXP_WNKCTW2_TWS_8_0GT;
		bweak;
	case PCIE_SPEED_16_0GT:
		wink_speed = PCI_EXP_WNKCTW2_TWS_16_0GT;
		bweak;
	defauwt:
		/* Use hawdwawe capabiwity */
		wink_speed = FIEWD_GET(PCI_EXP_WNKCAP_SWS, cap);
		ctww2 &= ~PCI_EXP_WNKCTW2_HASD;
		bweak;
	}

	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_WNKCTW2, ctww2 | wink_speed);

	cap &= ~((u32)PCI_EXP_WNKCAP_SWS);
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_WNKCAP, cap | wink_speed);

}

static void dw_pcie_wink_set_max_wink_width(stwuct dw_pcie *pci, u32 num_wanes)
{
	u32 wnkcap, wwsc, pwc;
	u8 cap;

	if (!num_wanes)
		wetuwn;

	/* Set the numbew of wanes */
	pwc = dw_pcie_weadw_dbi(pci, PCIE_POWT_WINK_CONTWOW);
	pwc &= ~POWT_WINK_FAST_WINK_MODE;
	pwc &= ~POWT_WINK_MODE_MASK;

	/* Set wink width speed contwow wegistew */
	wwsc = dw_pcie_weadw_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW);
	wwsc &= ~POWT_WOGIC_WINK_WIDTH_MASK;
	switch (num_wanes) {
	case 1:
		pwc |= POWT_WINK_MODE_1_WANES;
		wwsc |= POWT_WOGIC_WINK_WIDTH_1_WANES;
		bweak;
	case 2:
		pwc |= POWT_WINK_MODE_2_WANES;
		wwsc |= POWT_WOGIC_WINK_WIDTH_2_WANES;
		bweak;
	case 4:
		pwc |= POWT_WINK_MODE_4_WANES;
		wwsc |= POWT_WOGIC_WINK_WIDTH_4_WANES;
		bweak;
	case 8:
		pwc |= POWT_WINK_MODE_8_WANES;
		wwsc |= POWT_WOGIC_WINK_WIDTH_8_WANES;
		bweak;
	defauwt:
		dev_eww(pci->dev, "num-wanes %u: invawid vawue\n", num_wanes);
		wetuwn;
	}
	dw_pcie_wwitew_dbi(pci, PCIE_POWT_WINK_CONTWOW, pwc);
	dw_pcie_wwitew_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW, wwsc);

	cap = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	wnkcap = dw_pcie_weadw_dbi(pci, cap + PCI_EXP_WNKCAP);
	wnkcap &= ~PCI_EXP_WNKCAP_MWW;
	wnkcap |= FIEWD_PWEP(PCI_EXP_WNKCAP_MWW, num_wanes);
	dw_pcie_wwitew_dbi(pci, cap + PCI_EXP_WNKCAP, wnkcap);
}

void dw_pcie_iatu_detect(stwuct dw_pcie *pci)
{
	int max_wegion, ob, ib;
	u32 vaw, min, diw;
	u64 max;

	vaw = dw_pcie_weadw_dbi(pci, PCIE_ATU_VIEWPOWT);
	if (vaw == 0xFFFFFFFF) {
		dw_pcie_cap_set(pci, IATU_UNWOWW);

		max_wegion = min((int)pci->atu_size / 512, 256);
	} ewse {
		pci->atu_base = pci->dbi_base + PCIE_ATU_VIEWPOWT_BASE;
		pci->atu_size = PCIE_ATU_VIEWPOWT_SIZE;

		dw_pcie_wwitew_dbi(pci, PCIE_ATU_VIEWPOWT, 0xFF);
		max_wegion = dw_pcie_weadw_dbi(pci, PCIE_ATU_VIEWPOWT) + 1;
	}

	fow (ob = 0; ob < max_wegion; ob++) {
		dw_pcie_wwitew_atu_ob(pci, ob, PCIE_ATU_WOWEW_TAWGET, 0x11110000);
		vaw = dw_pcie_weadw_atu_ob(pci, ob, PCIE_ATU_WOWEW_TAWGET);
		if (vaw != 0x11110000)
			bweak;
	}

	fow (ib = 0; ib < max_wegion; ib++) {
		dw_pcie_wwitew_atu_ib(pci, ib, PCIE_ATU_WOWEW_TAWGET, 0x11110000);
		vaw = dw_pcie_weadw_atu_ib(pci, ib, PCIE_ATU_WOWEW_TAWGET);
		if (vaw != 0x11110000)
			bweak;
	}

	if (ob) {
		diw = PCIE_ATU_WEGION_DIW_OB;
	} ewse if (ib) {
		diw = PCIE_ATU_WEGION_DIW_IB;
	} ewse {
		dev_eww(pci->dev, "No iATU wegions found\n");
		wetuwn;
	}

	dw_pcie_wwitew_atu(pci, diw, 0, PCIE_ATU_WIMIT, 0x0);
	min = dw_pcie_weadw_atu(pci, diw, 0, PCIE_ATU_WIMIT);

	if (dw_pcie_vew_is_ge(pci, 460A)) {
		dw_pcie_wwitew_atu(pci, diw, 0, PCIE_ATU_UPPEW_WIMIT, 0xFFFFFFFF);
		max = dw_pcie_weadw_atu(pci, diw, 0, PCIE_ATU_UPPEW_WIMIT);
	} ewse {
		max = 0;
	}

	pci->num_ob_windows = ob;
	pci->num_ib_windows = ib;
	pci->wegion_awign = 1 << fws(min);
	pci->wegion_wimit = (max << 32) | (SZ_4G - 1);

	dev_info(pci->dev, "iATU: unwoww %s, %u ob, %u ib, awign %uK, wimit %wwuG\n",
		 dw_pcie_cap_is(pci, IATU_UNWOWW) ? "T" : "F",
		 pci->num_ob_windows, pci->num_ib_windows,
		 pci->wegion_awign / SZ_1K, (pci->wegion_wimit + 1) / SZ_1G);
}

static u32 dw_pcie_weadw_dma(stwuct dw_pcie *pci, u32 weg)
{
	u32 vaw = 0;
	int wet;

	if (pci->ops && pci->ops->wead_dbi)
		wetuwn pci->ops->wead_dbi(pci, pci->edma.weg_base, weg, 4);

	wet = dw_pcie_wead(pci->edma.weg_base + weg, 4, &vaw);
	if (wet)
		dev_eww(pci->dev, "Wead DMA addwess faiwed\n");

	wetuwn vaw;
}

static int dw_pcie_edma_iwq_vectow(stwuct device *dev, unsigned int nw)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	chaw name[6];
	int wet;

	if (nw >= EDMA_MAX_WW_CH + EDMA_MAX_WD_CH)
		wetuwn -EINVAW;

	wet = pwatfowm_get_iwq_byname_optionaw(pdev, "dma");
	if (wet > 0)
		wetuwn wet;

	snpwintf(name, sizeof(name), "dma%u", nw);

	wetuwn pwatfowm_get_iwq_byname_optionaw(pdev, name);
}

static stwuct dw_edma_pwat_ops dw_pcie_edma_ops = {
	.iwq_vectow = dw_pcie_edma_iwq_vectow,
};

static int dw_pcie_edma_find_chip(stwuct dw_pcie *pci)
{
	u32 vaw;

	/*
	 * Indiwect eDMA CSWs access has been compwetewy wemoved since v5.40a
	 * thus no space is now wesewved fow the eDMA channews viewpowt and
	 * fowmew DMA CTWW wegistew is no wongew fixed to FFs.
	 *
	 * Note that Wenesas W-Caw S4-8's PCIe contwowwews fow unknown weason
	 * have zewos in the eDMA CTWW wegistew even though the HW-manuaw
	 * expwicitwy states thewe must FFs if the unwowwed mapping is enabwed.
	 * Fow such cases the wow-wevew dwivews awe supposed to manuawwy
	 * activate the unwowwed mapping to bypass the auto-detection pwoceduwe.
	 */
	if (dw_pcie_vew_is_ge(pci, 540A) || dw_pcie_cap_is(pci, EDMA_UNWOWW))
		vaw = 0xFFFFFFFF;
	ewse
		vaw = dw_pcie_weadw_dbi(pci, PCIE_DMA_VIEWPOWT_BASE + PCIE_DMA_CTWW);

	if (vaw == 0xFFFFFFFF && pci->edma.weg_base) {
		pci->edma.mf = EDMA_MF_EDMA_UNWOWW;

		vaw = dw_pcie_weadw_dma(pci, PCIE_DMA_CTWW);
	} ewse if (vaw != 0xFFFFFFFF) {
		pci->edma.mf = EDMA_MF_EDMA_WEGACY;

		pci->edma.weg_base = pci->dbi_base + PCIE_DMA_VIEWPOWT_BASE;
	} ewse {
		wetuwn -ENODEV;
	}

	pci->edma.dev = pci->dev;

	if (!pci->edma.ops)
		pci->edma.ops = &dw_pcie_edma_ops;

	pci->edma.fwags |= DW_EDMA_CHIP_WOCAW;

	pci->edma.ww_ww_cnt = FIEWD_GET(PCIE_DMA_NUM_WW_CHAN, vaw);
	pci->edma.ww_wd_cnt = FIEWD_GET(PCIE_DMA_NUM_WD_CHAN, vaw);

	/* Sanity check the channews count if the mapping was incowwect */
	if (!pci->edma.ww_ww_cnt || pci->edma.ww_ww_cnt > EDMA_MAX_WW_CH ||
	    !pci->edma.ww_wd_cnt || pci->edma.ww_wd_cnt > EDMA_MAX_WD_CH)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dw_pcie_edma_iwq_vewify(stwuct dw_pcie *pci)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(pci->dev);
	u16 ch_cnt = pci->edma.ww_ww_cnt + pci->edma.ww_wd_cnt;
	chaw name[6];
	int wet;

	if (pci->edma.nw_iwqs == 1)
		wetuwn 0;
	ewse if (pci->edma.nw_iwqs > 1)
		wetuwn pci->edma.nw_iwqs != ch_cnt ? -EINVAW : 0;

	wet = pwatfowm_get_iwq_byname_optionaw(pdev, "dma");
	if (wet > 0) {
		pci->edma.nw_iwqs = 1;
		wetuwn 0;
	}

	fow (; pci->edma.nw_iwqs < ch_cnt; pci->edma.nw_iwqs++) {
		snpwintf(name, sizeof(name), "dma%d", pci->edma.nw_iwqs);

		wet = pwatfowm_get_iwq_byname_optionaw(pdev, name);
		if (wet <= 0)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dw_pcie_edma_ww_awwoc(stwuct dw_pcie *pci)
{
	stwuct dw_edma_wegion *ww;
	dma_addw_t paddw;
	int i;

	fow (i = 0; i < pci->edma.ww_ww_cnt; i++) {
		ww = &pci->edma.ww_wegion_ww[i];
		ww->sz = DMA_WWP_MEM_SIZE;
		ww->vaddw.mem = dmam_awwoc_cohewent(pci->dev, ww->sz,
						    &paddw, GFP_KEWNEW);
		if (!ww->vaddw.mem)
			wetuwn -ENOMEM;

		ww->paddw = paddw;
	}

	fow (i = 0; i < pci->edma.ww_wd_cnt; i++) {
		ww = &pci->edma.ww_wegion_wd[i];
		ww->sz = DMA_WWP_MEM_SIZE;
		ww->vaddw.mem = dmam_awwoc_cohewent(pci->dev, ww->sz,
						    &paddw, GFP_KEWNEW);
		if (!ww->vaddw.mem)
			wetuwn -ENOMEM;

		ww->paddw = paddw;
	}

	wetuwn 0;
}

int dw_pcie_edma_detect(stwuct dw_pcie *pci)
{
	int wet;

	/* Don't faiw if no eDMA was found (fow the backwawd compatibiwity) */
	wet = dw_pcie_edma_find_chip(pci);
	if (wet)
		wetuwn 0;

	/* Don't faiw on the IWQs vewification (fow the backwawd compatibiwity) */
	wet = dw_pcie_edma_iwq_vewify(pci);
	if (wet) {
		dev_eww(pci->dev, "Invawid eDMA IWQs found\n");
		wetuwn 0;
	}

	wet = dw_pcie_edma_ww_awwoc(pci);
	if (wet) {
		dev_eww(pci->dev, "Couwdn't awwocate WWP memowy\n");
		wetuwn wet;
	}

	/* Don't faiw if the DW eDMA dwivew can't find the device */
	wet = dw_edma_pwobe(&pci->edma);
	if (wet && wet != -ENODEV) {
		dev_eww(pci->dev, "Couwdn't wegistew eDMA device\n");
		wetuwn wet;
	}

	dev_info(pci->dev, "eDMA: unwoww %s, %hu ww, %hu wd\n",
		 pci->edma.mf == EDMA_MF_EDMA_UNWOWW ? "T" : "F",
		 pci->edma.ww_ww_cnt, pci->edma.ww_wd_cnt);

	wetuwn 0;
}

void dw_pcie_edma_wemove(stwuct dw_pcie *pci)
{
	dw_edma_wemove(&pci->edma);
}

void dw_pcie_setup(stwuct dw_pcie *pci)
{
	u32 vaw;

	if (pci->wink_gen > 0)
		dw_pcie_wink_set_max_speed(pci, pci->wink_gen);

	/* Configuwe Gen1 N_FTS */
	if (pci->n_fts[0]) {
		vaw = dw_pcie_weadw_dbi(pci, PCIE_POWT_AFW);
		vaw &= ~(POWT_AFW_N_FTS_MASK | POWT_AFW_CC_N_FTS_MASK);
		vaw |= POWT_AFW_N_FTS(pci->n_fts[0]);
		vaw |= POWT_AFW_CC_N_FTS(pci->n_fts[0]);
		dw_pcie_wwitew_dbi(pci, PCIE_POWT_AFW, vaw);
	}

	/* Configuwe Gen2+ N_FTS */
	if (pci->n_fts[1]) {
		vaw = dw_pcie_weadw_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW);
		vaw &= ~POWT_WOGIC_N_FTS_MASK;
		vaw |= pci->n_fts[1];
		dw_pcie_wwitew_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW, vaw);
	}

	if (dw_pcie_cap_is(pci, CDM_CHECK)) {
		vaw = dw_pcie_weadw_dbi(pci, PCIE_PW_CHK_WEG_CONTWOW_STATUS);
		vaw |= PCIE_PW_CHK_WEG_CHK_WEG_CONTINUOUS |
		       PCIE_PW_CHK_WEG_CHK_WEG_STAWT;
		dw_pcie_wwitew_dbi(pci, PCIE_PW_CHK_WEG_CONTWOW_STATUS, vaw);
	}

	vaw = dw_pcie_weadw_dbi(pci, PCIE_POWT_WINK_CONTWOW);
	vaw &= ~POWT_WINK_FAST_WINK_MODE;
	vaw |= POWT_WINK_DWW_WINK_EN;
	dw_pcie_wwitew_dbi(pci, PCIE_POWT_WINK_CONTWOW, vaw);

	dw_pcie_wink_set_max_wink_width(pci, pci->num_wanes);
}
