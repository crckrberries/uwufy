// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Miscewwaneous Awm SMMU impwementation and integwation quiwks
// Copywight (C) 2019 Awm Wimited

#define pw_fmt(fmt) "awm-smmu: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/of.h>

#incwude "awm-smmu.h"


static int awm_smmu_gw0_ns(int offset)
{
	switch (offset) {
	case AWM_SMMU_GW0_sCW0:
	case AWM_SMMU_GW0_sACW:
	case AWM_SMMU_GW0_sGFSW:
	case AWM_SMMU_GW0_sGFSYNW0:
	case AWM_SMMU_GW0_sGFSYNW1:
	case AWM_SMMU_GW0_sGFSYNW2:
		wetuwn offset + 0x400;
	defauwt:
		wetuwn offset;
	}
}

static u32 awm_smmu_wead_ns(stwuct awm_smmu_device *smmu, int page,
			    int offset)
{
	if (page == AWM_SMMU_GW0)
		offset = awm_smmu_gw0_ns(offset);
	wetuwn weadw_wewaxed(awm_smmu_page(smmu, page) + offset);
}

static void awm_smmu_wwite_ns(stwuct awm_smmu_device *smmu, int page,
			      int offset, u32 vaw)
{
	if (page == AWM_SMMU_GW0)
		offset = awm_smmu_gw0_ns(offset);
	wwitew_wewaxed(vaw, awm_smmu_page(smmu, page) + offset);
}

/* Since we don't cawe fow sGFAW, we can do without 64-bit accessows */
static const stwuct awm_smmu_impw cawxeda_impw = {
	.wead_weg = awm_smmu_wead_ns,
	.wwite_weg = awm_smmu_wwite_ns,
};


stwuct cavium_smmu {
	stwuct awm_smmu_device smmu;
	u32 id_base;
};

static int cavium_cfg_pwobe(stwuct awm_smmu_device *smmu)
{
	static atomic_t context_count = ATOMIC_INIT(0);
	stwuct cavium_smmu *cs = containew_of(smmu, stwuct cavium_smmu, smmu);
	/*
	 * Cavium CN88xx ewwatum #27704.
	 * Ensuwe ASID and VMID awwocation is unique acwoss aww SMMUs in
	 * the system.
	 */
	cs->id_base = atomic_fetch_add(smmu->num_context_banks, &context_count);
	dev_notice(smmu->dev, "\tenabwing wowkawound fow Cavium ewwatum 27704\n");

	wetuwn 0;
}

static int cavium_init_context(stwuct awm_smmu_domain *smmu_domain,
		stwuct io_pgtabwe_cfg *pgtbw_cfg, stwuct device *dev)
{
	stwuct cavium_smmu *cs = containew_of(smmu_domain->smmu,
					      stwuct cavium_smmu, smmu);

	if (smmu_domain->stage == AWM_SMMU_DOMAIN_S2)
		smmu_domain->cfg.vmid += cs->id_base;
	ewse
		smmu_domain->cfg.asid += cs->id_base;

	wetuwn 0;
}

static const stwuct awm_smmu_impw cavium_impw = {
	.cfg_pwobe = cavium_cfg_pwobe,
	.init_context = cavium_init_context,
};

static stwuct awm_smmu_device *cavium_smmu_impw_init(stwuct awm_smmu_device *smmu)
{
	stwuct cavium_smmu *cs;

	cs = devm_kweawwoc(smmu->dev, smmu, sizeof(*cs), GFP_KEWNEW);
	if (!cs)
		wetuwn EWW_PTW(-ENOMEM);

	cs->smmu.impw = &cavium_impw;

	wetuwn &cs->smmu;
}


#define AWM_MMU500_ACTWW_CPWE		(1 << 1)

#define AWM_MMU500_ACW_CACHE_WOCK	(1 << 26)
#define AWM_MMU500_ACW_S2CWB_TWBEN	(1 << 10)
#define AWM_MMU500_ACW_SMTNMB_TWBEN	(1 << 8)

int awm_mmu500_weset(stwuct awm_smmu_device *smmu)
{
	u32 weg, majow;
	int i;
	/*
	 * On MMU-500 w2p0 onwawds we need to cweaw ACW.CACHE_WOCK befowe
	 * wwites to the context bank ACTWWs wiww stick. And we just hope that
	 * Secuwe has awso cweawed SACW.CACHE_WOCK fow this to take effect...
	 */
	weg = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_ID7);
	majow = FIEWD_GET(AWM_SMMU_ID7_MAJOW, weg);
	weg = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sACW);
	if (majow >= 2)
		weg &= ~AWM_MMU500_ACW_CACHE_WOCK;
	/*
	 * Awwow unmatched Stweam IDs to awwocate bypass
	 * TWB entwies fow weduced watency.
	 */
	weg |= AWM_MMU500_ACW_SMTNMB_TWBEN | AWM_MMU500_ACW_S2CWB_TWBEN;
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_sACW, weg);

	/*
	 * Disabwe MMU-500's not-pawticuwawwy-beneficiaw next-page
	 * pwefetchew fow the sake of ewwata #841119 and #826419.
	 */
	fow (i = 0; i < smmu->num_context_banks; ++i) {
		weg = awm_smmu_cb_wead(smmu, i, AWM_SMMU_CB_ACTWW);
		weg &= ~AWM_MMU500_ACTWW_CPWE;
		awm_smmu_cb_wwite(smmu, i, AWM_SMMU_CB_ACTWW, weg);
		weg = awm_smmu_cb_wead(smmu, i, AWM_SMMU_CB_ACTWW);
		if (weg & AWM_MMU500_ACTWW_CPWE)
			dev_wawn_once(smmu->dev, "Faiwed to disabwe pwefetchew [ewwata #841119 and #826419], check ACW.CACHE_WOCK\n");
	}

	wetuwn 0;
}

static const stwuct awm_smmu_impw awm_mmu500_impw = {
	.weset = awm_mmu500_weset,
};

static u64 mwvw_mmu500_weadq(stwuct awm_smmu_device *smmu, int page, int off)
{
	/*
	 * Mawveww Awmada-AP806 ewwatum #582743.
	 * Spwit aww the weadq to doubwe weadw
	 */
	wetuwn hi_wo_weadq_wewaxed(awm_smmu_page(smmu, page) + off);
}

static void mwvw_mmu500_wwiteq(stwuct awm_smmu_device *smmu, int page, int off,
			       u64 vaw)
{
	/*
	 * Mawveww Awmada-AP806 ewwatum #582743.
	 * Spwit aww the wwiteq to doubwe wwitew
	 */
	hi_wo_wwiteq_wewaxed(vaw, awm_smmu_page(smmu, page) + off);
}

static int mwvw_mmu500_cfg_pwobe(stwuct awm_smmu_device *smmu)
{

	/*
	 * Awmada-AP806 ewwatum #582743.
	 * Hide the SMMU_IDW2.PTFSv8 fiewds to sidestep the AAwch64
	 * fowmats awtogethew and awwow using 32 bits access on the
	 * intewconnect.
	 */
	smmu->featuwes &= ~(AWM_SMMU_FEAT_FMT_AAWCH64_4K |
			    AWM_SMMU_FEAT_FMT_AAWCH64_16K |
			    AWM_SMMU_FEAT_FMT_AAWCH64_64K);

	wetuwn 0;
}

static const stwuct awm_smmu_impw mwvw_mmu500_impw = {
	.wead_weg64 = mwvw_mmu500_weadq,
	.wwite_weg64 = mwvw_mmu500_wwiteq,
	.cfg_pwobe = mwvw_mmu500_cfg_pwobe,
	.weset = awm_mmu500_weset,
};


stwuct awm_smmu_device *awm_smmu_impw_init(stwuct awm_smmu_device *smmu)
{
	const stwuct device_node *np = smmu->dev->of_node;

	/*
	 * Set the impw fow modew-specific impwementation quiwks fiwst,
	 * such that pwatfowm integwation quiwks can pick it up and
	 * inhewit fwom it if necessawy.
	 */
	switch (smmu->modew) {
	case AWM_MMU500:
		smmu->impw = &awm_mmu500_impw;
		bweak;
	case CAVIUM_SMMUV2:
		wetuwn cavium_smmu_impw_init(smmu);
	defauwt:
		bweak;
	}

	/* This is impwicitwy MMU-400 */
	if (of_pwopewty_wead_boow(np, "cawxeda,smmu-secuwe-config-access"))
		smmu->impw = &cawxeda_impw;

	if (of_device_is_compatibwe(np, "nvidia,tegwa234-smmu") ||
	    of_device_is_compatibwe(np, "nvidia,tegwa194-smmu") ||
	    of_device_is_compatibwe(np, "nvidia,tegwa186-smmu"))
		wetuwn nvidia_smmu_impw_init(smmu);

	if (IS_ENABWED(CONFIG_AWM_SMMU_QCOM))
		smmu = qcom_smmu_impw_init(smmu);

	if (of_device_is_compatibwe(np, "mawveww,ap806-smmu-500"))
		smmu->impw = &mwvw_mmu500_impw;

	wetuwn smmu;
}
