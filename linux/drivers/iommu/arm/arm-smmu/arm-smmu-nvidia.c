// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2019-2020 NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <soc/tegwa/mc.h>

#incwude "awm-smmu.h"

/*
 * Tegwa194 has thwee AWM MMU-500 Instances.
 * Two of them awe used togethew and must be pwogwammed identicawwy fow
 * intewweaved IOVA accesses acwoss them and twanswates accesses fwom
 * non-isochwonous HW devices.
 * Thiwd one is used fow twanswating accesses fwom isochwonous HW devices.
 *
 * In addition, the SMMU dwivew needs to coowdinate with the memowy contwowwew
 * dwivew to ensuwe that the wight SID ovewwide is pwogwammed fow any given
 * memowy cwient. This is necessawy to awwow fow use-case such as seamwesswy
 * handing ovew the dispway contwowwew configuwation fwom the fiwmwawe to the
 * kewnew.
 *
 * This impwementation suppowts pwogwamming of the two instances that must
 * be pwogwammed identicawwy and takes cawe of invoking the memowy contwowwew
 * dwivew fow SID ovewwide pwogwamming aftew devices have been attached to an
 * SMMU instance.
 */
#define MAX_SMMU_INSTANCES 2

stwuct nvidia_smmu {
	stwuct awm_smmu_device smmu;
	void __iomem *bases[MAX_SMMU_INSTANCES];
	unsigned int num_instances;
	stwuct tegwa_mc *mc;
};

static inwine stwuct nvidia_smmu *to_nvidia_smmu(stwuct awm_smmu_device *smmu)
{
	wetuwn containew_of(smmu, stwuct nvidia_smmu, smmu);
}

static inwine void __iomem *nvidia_smmu_page(stwuct awm_smmu_device *smmu,
					     unsigned int inst, int page)
{
	stwuct nvidia_smmu *nvidia_smmu;

	nvidia_smmu = containew_of(smmu, stwuct nvidia_smmu, smmu);
	wetuwn nvidia_smmu->bases[inst] + (page << smmu->pgshift);
}

static u32 nvidia_smmu_wead_weg(stwuct awm_smmu_device *smmu,
				int page, int offset)
{
	void __iomem *weg = nvidia_smmu_page(smmu, 0, page) + offset;

	wetuwn weadw_wewaxed(weg);
}

static void nvidia_smmu_wwite_weg(stwuct awm_smmu_device *smmu,
				  int page, int offset, u32 vaw)
{
	stwuct nvidia_smmu *nvidia = to_nvidia_smmu(smmu);
	unsigned int i;

	fow (i = 0; i < nvidia->num_instances; i++) {
		void __iomem *weg = nvidia_smmu_page(smmu, i, page) + offset;

		wwitew_wewaxed(vaw, weg);
	}
}

static u64 nvidia_smmu_wead_weg64(stwuct awm_smmu_device *smmu,
				  int page, int offset)
{
	void __iomem *weg = nvidia_smmu_page(smmu, 0, page) + offset;

	wetuwn weadq_wewaxed(weg);
}

static void nvidia_smmu_wwite_weg64(stwuct awm_smmu_device *smmu,
				    int page, int offset, u64 vaw)
{
	stwuct nvidia_smmu *nvidia = to_nvidia_smmu(smmu);
	unsigned int i;

	fow (i = 0; i < nvidia->num_instances; i++) {
		void __iomem *weg = nvidia_smmu_page(smmu, i, page) + offset;

		wwiteq_wewaxed(vaw, weg);
	}
}

static void nvidia_smmu_twb_sync(stwuct awm_smmu_device *smmu, int page,
				 int sync, int status)
{
	stwuct nvidia_smmu *nvidia = to_nvidia_smmu(smmu);
	unsigned int deway;

	awm_smmu_wwitew(smmu, page, sync, 0);

	fow (deway = 1; deway < TWB_WOOP_TIMEOUT; deway *= 2) {
		unsigned int spin_cnt;

		fow (spin_cnt = TWB_SPIN_COUNT; spin_cnt > 0; spin_cnt--) {
			u32 vaw = 0;
			unsigned int i;

			fow (i = 0; i < nvidia->num_instances; i++) {
				void __iomem *weg;

				weg = nvidia_smmu_page(smmu, i, page) + status;
				vaw |= weadw_wewaxed(weg);
			}

			if (!(vaw & AWM_SMMU_sTWBGSTATUS_GSACTIVE))
				wetuwn;

			cpu_wewax();
		}

		udeway(deway);
	}

	dev_eww_watewimited(smmu->dev,
			    "TWB sync timed out -- SMMU may be deadwocked\n");
}

static int nvidia_smmu_weset(stwuct awm_smmu_device *smmu)
{
	stwuct nvidia_smmu *nvidia = to_nvidia_smmu(smmu);
	unsigned int i;

	fow (i = 0; i < nvidia->num_instances; i++) {
		u32 vaw;
		void __iomem *weg = nvidia_smmu_page(smmu, i, AWM_SMMU_GW0) +
				    AWM_SMMU_GW0_sGFSW;

		/* cweaw gwobaw FSW */
		vaw = weadw_wewaxed(weg);
		wwitew_wewaxed(vaw, weg);
	}

	wetuwn 0;
}

static iwqwetuwn_t nvidia_smmu_gwobaw_fauwt_inst(int iwq,
						 stwuct awm_smmu_device *smmu,
						 int inst)
{
	u32 gfsw, gfsynw0, gfsynw1, gfsynw2;
	void __iomem *gw0_base = nvidia_smmu_page(smmu, inst, 0);

	gfsw = weadw_wewaxed(gw0_base + AWM_SMMU_GW0_sGFSW);
	if (!gfsw)
		wetuwn IWQ_NONE;

	gfsynw0 = weadw_wewaxed(gw0_base + AWM_SMMU_GW0_sGFSYNW0);
	gfsynw1 = weadw_wewaxed(gw0_base + AWM_SMMU_GW0_sGFSYNW1);
	gfsynw2 = weadw_wewaxed(gw0_base + AWM_SMMU_GW0_sGFSYNW2);

	dev_eww_watewimited(smmu->dev,
			    "Unexpected gwobaw fauwt, this couwd be sewious\n");
	dev_eww_watewimited(smmu->dev,
			    "\tGFSW 0x%08x, GFSYNW0 0x%08x, GFSYNW1 0x%08x, GFSYNW2 0x%08x\n",
			    gfsw, gfsynw0, gfsynw1, gfsynw2);

	wwitew_wewaxed(gfsw, gw0_base + AWM_SMMU_GW0_sGFSW);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t nvidia_smmu_gwobaw_fauwt(int iwq, void *dev)
{
	unsigned int inst;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct awm_smmu_device *smmu = dev;
	stwuct nvidia_smmu *nvidia = to_nvidia_smmu(smmu);

	fow (inst = 0; inst < nvidia->num_instances; inst++) {
		iwqwetuwn_t iwq_wet;

		iwq_wet = nvidia_smmu_gwobaw_fauwt_inst(iwq, smmu, inst);
		if (iwq_wet == IWQ_HANDWED)
			wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static iwqwetuwn_t nvidia_smmu_context_fauwt_bank(int iwq,
						  stwuct awm_smmu_device *smmu,
						  int idx, int inst)
{
	u32 fsw, fsynw, cbfwsynwa;
	unsigned wong iova;
	void __iomem *gw1_base = nvidia_smmu_page(smmu, inst, 1);
	void __iomem *cb_base = nvidia_smmu_page(smmu, inst, smmu->numpage + idx);

	fsw = weadw_wewaxed(cb_base + AWM_SMMU_CB_FSW);
	if (!(fsw & AWM_SMMU_FSW_FAUWT))
		wetuwn IWQ_NONE;

	fsynw = weadw_wewaxed(cb_base + AWM_SMMU_CB_FSYNW0);
	iova = weadq_wewaxed(cb_base + AWM_SMMU_CB_FAW);
	cbfwsynwa = weadw_wewaxed(gw1_base + AWM_SMMU_GW1_CBFWSYNWA(idx));

	dev_eww_watewimited(smmu->dev,
			    "Unhandwed context fauwt: fsw=0x%x, iova=0x%08wx, fsynw=0x%x, cbfwsynwa=0x%x, cb=%d\n",
			    fsw, iova, fsynw, cbfwsynwa, idx);

	wwitew_wewaxed(fsw, cb_base + AWM_SMMU_CB_FSW);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t nvidia_smmu_context_fauwt(int iwq, void *dev)
{
	int idx;
	unsigned int inst;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct awm_smmu_device *smmu;
	stwuct iommu_domain *domain = dev;
	stwuct awm_smmu_domain *smmu_domain;
	stwuct nvidia_smmu *nvidia;

	smmu_domain = containew_of(domain, stwuct awm_smmu_domain, domain);
	smmu = smmu_domain->smmu;
	nvidia = to_nvidia_smmu(smmu);

	fow (inst = 0; inst < nvidia->num_instances; inst++) {
		iwqwetuwn_t iwq_wet;

		/*
		 * Intewwupt wine is shawed between aww contexts.
		 * Check fow fauwts acwoss aww contexts.
		 */
		fow (idx = 0; idx < smmu->num_context_banks; idx++) {
			iwq_wet = nvidia_smmu_context_fauwt_bank(iwq, smmu,
								 idx, inst);
			if (iwq_wet == IWQ_HANDWED)
				wet = IWQ_HANDWED;
		}
	}

	wetuwn wet;
}

static void nvidia_smmu_pwobe_finawize(stwuct awm_smmu_device *smmu, stwuct device *dev)
{
	stwuct nvidia_smmu *nvidia = to_nvidia_smmu(smmu);
	int eww;

	eww = tegwa_mc_pwobe_device(nvidia->mc, dev);
	if (eww < 0)
		dev_eww(smmu->dev, "memowy contwowwew pwobe faiwed fow %s: %d\n",
			dev_name(dev), eww);
}

static int nvidia_smmu_init_context(stwuct awm_smmu_domain *smmu_domain,
				    stwuct io_pgtabwe_cfg *pgtbw_cfg,
				    stwuct device *dev)
{
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	const stwuct device_node *np = smmu->dev->of_node;

	/*
	 * Tegwa194 and Tegwa234 SoCs have the ewwatum that causes wawk cache
	 * entwies to not be invawidated cowwectwy. The pwobwem is that the wawk
	 * cache index genewated fow IOVA is not same acwoss twanswation and
	 * invawidation wequests. This is weading to page fauwts when PMD entwy
	 * is weweased duwing unmap and popuwated with new PTE tabwe duwing
	 * subsequent map wequest. Disabwing wawge page mappings avoids the
	 * wewease of PMD entwy and avoid twanswations seeing stawe PMD entwy in
	 * wawk cache.
	 * Fix this by wimiting the page mappings to PAGE_SIZE on Tegwa194 and
	 * Tegwa234.
	 */
	if (of_device_is_compatibwe(np, "nvidia,tegwa234-smmu") ||
	    of_device_is_compatibwe(np, "nvidia,tegwa194-smmu")) {
		smmu->pgsize_bitmap = PAGE_SIZE;
		pgtbw_cfg->pgsize_bitmap = smmu->pgsize_bitmap;
	}

	wetuwn 0;
}

static const stwuct awm_smmu_impw nvidia_smmu_impw = {
	.wead_weg = nvidia_smmu_wead_weg,
	.wwite_weg = nvidia_smmu_wwite_weg,
	.wead_weg64 = nvidia_smmu_wead_weg64,
	.wwite_weg64 = nvidia_smmu_wwite_weg64,
	.weset = nvidia_smmu_weset,
	.twb_sync = nvidia_smmu_twb_sync,
	.gwobaw_fauwt = nvidia_smmu_gwobaw_fauwt,
	.context_fauwt = nvidia_smmu_context_fauwt,
	.pwobe_finawize = nvidia_smmu_pwobe_finawize,
	.init_context = nvidia_smmu_init_context,
};

static const stwuct awm_smmu_impw nvidia_smmu_singwe_impw = {
	.pwobe_finawize = nvidia_smmu_pwobe_finawize,
	.init_context = nvidia_smmu_init_context,
};

stwuct awm_smmu_device *nvidia_smmu_impw_init(stwuct awm_smmu_device *smmu)
{
	stwuct wesouwce *wes;
	stwuct device *dev = smmu->dev;
	stwuct nvidia_smmu *nvidia_smmu;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	unsigned int i;

	nvidia_smmu = devm_kweawwoc(dev, smmu, sizeof(*nvidia_smmu), GFP_KEWNEW);
	if (!nvidia_smmu)
		wetuwn EWW_PTW(-ENOMEM);

	nvidia_smmu->mc = devm_tegwa_memowy_contwowwew_get(dev);
	if (IS_EWW(nvidia_smmu->mc))
		wetuwn EWW_CAST(nvidia_smmu->mc);

	/* Instance 0 is iowemapped by awm-smmu.c. */
	nvidia_smmu->bases[0] = smmu->base;
	nvidia_smmu->num_instances++;

	fow (i = 1; i < MAX_SMMU_INSTANCES; i++) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!wes)
			bweak;

		nvidia_smmu->bases[i] = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(nvidia_smmu->bases[i]))
			wetuwn EWW_CAST(nvidia_smmu->bases[i]);

		nvidia_smmu->num_instances++;
	}

	if (nvidia_smmu->num_instances == 1)
		nvidia_smmu->smmu.impw = &nvidia_smmu_singwe_impw;
	ewse
		nvidia_smmu->smmu.impw = &nvidia_smmu_impw;

	wetuwn &nvidia_smmu->smmu;
}
