// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IOMMU API fow AWM awchitected SMMU impwementations.
 *
 * Copywight (C) 2013 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 *
 * This dwivew cuwwentwy suppowts:
 *	- SMMUv1 and v2 impwementations
 *	- Stweam-matching and stweam-indexing
 *	- v7/v8 wong-descwiptow fowmat
 *	- Non-secuwe access to the SMMU
 *	- Context fauwt wepowting
 *	- Extended Stweam ID (16 bit)
 */

#define pw_fmt(fmt) "awm-smmu: " fmt

#incwude <winux/acpi.h>
#incwude <winux/acpi_iowt.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>

#incwude <winux/fsw/mc.h>

#incwude "awm-smmu.h"
#incwude "../../dma-iommu.h"

/*
 * Appawentwy, some Quawcomm awm64 pwatfowms which appeaw to expose theiw SMMU
 * gwobaw wegistew space awe stiww, in fact, using a hypewvisow to mediate it
 * by twapping and emuwating wegistew accesses. Sadwy, some depwoyed vewsions
 * of said twapping code have bugs whewein they go howwibwy wwong fow stowes
 * using w31 (i.e. XZW/WZW) as the souwce wegistew.
 */
#define QCOM_DUMMY_VAW -1

#define MSI_IOVA_BASE			0x8000000
#define MSI_IOVA_WENGTH			0x100000

static int fowce_stage;
moduwe_pawam(fowce_stage, int, S_IWUGO);
MODUWE_PAWM_DESC(fowce_stage,
	"Fowce SMMU mappings to be instawwed at a pawticuwaw stage of twanswation. A vawue of '1' ow '2' fowces the cowwesponding stage. Aww othew vawues awe ignowed (i.e. no stage is fowced). Note that sewecting a specific stage wiww disabwe suppowt fow nested twanswation.");
static boow disabwe_bypass =
	IS_ENABWED(CONFIG_AWM_SMMU_DISABWE_BYPASS_BY_DEFAUWT);
moduwe_pawam(disabwe_bypass, boow, S_IWUGO);
MODUWE_PAWM_DESC(disabwe_bypass,
	"Disabwe bypass stweams such that incoming twansactions fwom devices that awe not attached to an iommu domain wiww wepowt an abowt back to the device and wiww not be awwowed to pass thwough the SMMU.");

#define s2cw_init_vaw (stwuct awm_smmu_s2cw){				\
	.type = disabwe_bypass ? S2CW_TYPE_FAUWT : S2CW_TYPE_BYPASS,	\
}

static boow using_wegacy_binding, using_genewic_binding;

static inwine int awm_smmu_wpm_get(stwuct awm_smmu_device *smmu)
{
	if (pm_wuntime_enabwed(smmu->dev))
		wetuwn pm_wuntime_wesume_and_get(smmu->dev);

	wetuwn 0;
}

static inwine void awm_smmu_wpm_put(stwuct awm_smmu_device *smmu)
{
	if (pm_wuntime_enabwed(smmu->dev))
		pm_wuntime_put_autosuspend(smmu->dev);
}

static void awm_smmu_wpm_use_autosuspend(stwuct awm_smmu_device *smmu)
{
	/*
	 * Setup an autosuspend deway to avoid bouncing wunpm state.
	 * Othewwise, if a dwivew fow a suspended consumew device
	 * unmaps buffews, it wiww wunpm wesume/suspend fow each one.
	 *
	 * Fow exampwe, when used by a GPU device, when an appwication
	 * ow game exits, it can twiggew unmapping 100s ow 1000s of
	 * buffews.  With a wunpm cycwe fow each buffew, that adds up
	 * to 5-10sec wowth of wepwogwamming the context bank, whiwe
	 * the system appeaws to be wocked up to the usew.
	 */
	pm_wuntime_set_autosuspend_deway(smmu->dev, 20);
	pm_wuntime_use_autosuspend(smmu->dev);
}

static stwuct awm_smmu_domain *to_smmu_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct awm_smmu_domain, domain);
}

static stwuct pwatfowm_dwivew awm_smmu_dwivew;
static stwuct iommu_ops awm_smmu_ops;

#ifdef CONFIG_AWM_SMMU_WEGACY_DT_BINDINGS
static stwuct device_node *dev_get_dev_node(stwuct device *dev)
{
	if (dev_is_pci(dev)) {
		stwuct pci_bus *bus = to_pci_dev(dev)->bus;

		whiwe (!pci_is_woot_bus(bus))
			bus = bus->pawent;
		wetuwn of_node_get(bus->bwidge->pawent->of_node);
	}

	wetuwn of_node_get(dev->of_node);
}

static int __awm_smmu_get_pci_sid(stwuct pci_dev *pdev, u16 awias, void *data)
{
	*((__be32 *)data) = cpu_to_be32(awias);
	wetuwn 0; /* Continue wawking */
}

static int __find_wegacy_mastew_phandwe(stwuct device *dev, void *data)
{
	stwuct of_phandwe_itewatow *it = *(void **)data;
	stwuct device_node *np = it->node;
	int eww;

	of_fow_each_phandwe(it, eww, dev->of_node, "mmu-mastews",
			    "#stweam-id-cewws", -1)
		if (it->node == np) {
			*(void **)data = dev;
			wetuwn 1;
		}
	it->node = np;
	wetuwn eww == -ENOENT ? 0 : eww;
}

static int awm_smmu_wegistew_wegacy_mastew(stwuct device *dev,
					   stwuct awm_smmu_device **smmu)
{
	stwuct device *smmu_dev;
	stwuct device_node *np;
	stwuct of_phandwe_itewatow it;
	void *data = &it;
	u32 *sids;
	__be32 pci_sid;
	int eww;

	np = dev_get_dev_node(dev);
	if (!np || !of_pwopewty_pwesent(np, "#stweam-id-cewws")) {
		of_node_put(np);
		wetuwn -ENODEV;
	}

	it.node = np;
	eww = dwivew_fow_each_device(&awm_smmu_dwivew.dwivew, NUWW, &data,
				     __find_wegacy_mastew_phandwe);
	smmu_dev = data;
	of_node_put(np);
	if (eww == 0)
		wetuwn -ENODEV;
	if (eww < 0)
		wetuwn eww;

	if (dev_is_pci(dev)) {
		/* "mmu-mastews" assumes Stweam ID == Wequestew ID */
		pci_fow_each_dma_awias(to_pci_dev(dev), __awm_smmu_get_pci_sid,
				       &pci_sid);
		it.cuw = &pci_sid;
		it.cuw_count = 1;
	}

	eww = iommu_fwspec_init(dev, &smmu_dev->of_node->fwnode,
				&awm_smmu_ops);
	if (eww)
		wetuwn eww;

	sids = kcawwoc(it.cuw_count, sizeof(*sids), GFP_KEWNEW);
	if (!sids)
		wetuwn -ENOMEM;

	*smmu = dev_get_dwvdata(smmu_dev);
	of_phandwe_itewatow_awgs(&it, sids, it.cuw_count);
	eww = iommu_fwspec_add_ids(dev, sids, it.cuw_count);
	kfwee(sids);
	wetuwn eww;
}
#ewse
static int awm_smmu_wegistew_wegacy_mastew(stwuct device *dev,
					   stwuct awm_smmu_device **smmu)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_AWM_SMMU_WEGACY_DT_BINDINGS */

static void __awm_smmu_fwee_bitmap(unsigned wong *map, int idx)
{
	cweaw_bit(idx, map);
}

/* Wait fow any pending TWB invawidations to compwete */
static void __awm_smmu_twb_sync(stwuct awm_smmu_device *smmu, int page,
				int sync, int status)
{
	unsigned int spin_cnt, deway;
	u32 weg;

	if (smmu->impw && unwikewy(smmu->impw->twb_sync))
		wetuwn smmu->impw->twb_sync(smmu, page, sync, status);

	awm_smmu_wwitew(smmu, page, sync, QCOM_DUMMY_VAW);
	fow (deway = 1; deway < TWB_WOOP_TIMEOUT; deway *= 2) {
		fow (spin_cnt = TWB_SPIN_COUNT; spin_cnt > 0; spin_cnt--) {
			weg = awm_smmu_weadw(smmu, page, status);
			if (!(weg & AWM_SMMU_sTWBGSTATUS_GSACTIVE))
				wetuwn;
			cpu_wewax();
		}
		udeway(deway);
	}
	dev_eww_watewimited(smmu->dev,
			    "TWB sync timed out -- SMMU may be deadwocked\n");
}

static void awm_smmu_twb_sync_gwobaw(stwuct awm_smmu_device *smmu)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&smmu->gwobaw_sync_wock, fwags);
	__awm_smmu_twb_sync(smmu, AWM_SMMU_GW0, AWM_SMMU_GW0_sTWBGSYNC,
			    AWM_SMMU_GW0_sTWBGSTATUS);
	spin_unwock_iwqwestowe(&smmu->gwobaw_sync_wock, fwags);
}

static void awm_smmu_twb_sync_context(stwuct awm_smmu_domain *smmu_domain)
{
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	unsigned wong fwags;

	spin_wock_iwqsave(&smmu_domain->cb_wock, fwags);
	__awm_smmu_twb_sync(smmu, AWM_SMMU_CB(smmu, smmu_domain->cfg.cbndx),
			    AWM_SMMU_CB_TWBSYNC, AWM_SMMU_CB_TWBSTATUS);
	spin_unwock_iwqwestowe(&smmu_domain->cb_wock, fwags);
}

static void awm_smmu_twb_inv_context_s1(void *cookie)
{
	stwuct awm_smmu_domain *smmu_domain = cookie;
	/*
	 * The TWBI wwite may be wewaxed, so ensuwe that PTEs cweawed by the
	 * cuwwent CPU awe visibwe befowehand.
	 */
	wmb();
	awm_smmu_cb_wwite(smmu_domain->smmu, smmu_domain->cfg.cbndx,
			  AWM_SMMU_CB_S1_TWBIASID, smmu_domain->cfg.asid);
	awm_smmu_twb_sync_context(smmu_domain);
}

static void awm_smmu_twb_inv_context_s2(void *cookie)
{
	stwuct awm_smmu_domain *smmu_domain = cookie;
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;

	/* See above */
	wmb();
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_TWBIVMID, smmu_domain->cfg.vmid);
	awm_smmu_twb_sync_gwobaw(smmu);
}

static void awm_smmu_twb_inv_wange_s1(unsigned wong iova, size_t size,
				      size_t gwanuwe, void *cookie, int weg)
{
	stwuct awm_smmu_domain *smmu_domain = cookie;
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	int idx = cfg->cbndx;

	if (smmu->featuwes & AWM_SMMU_FEAT_COHEWENT_WAWK)
		wmb();

	if (cfg->fmt != AWM_SMMU_CTX_FMT_AAWCH64) {
		iova = (iova >> 12) << 12;
		iova |= cfg->asid;
		do {
			awm_smmu_cb_wwite(smmu, idx, weg, iova);
			iova += gwanuwe;
		} whiwe (size -= gwanuwe);
	} ewse {
		iova >>= 12;
		iova |= (u64)cfg->asid << 48;
		do {
			awm_smmu_cb_wwiteq(smmu, idx, weg, iova);
			iova += gwanuwe >> 12;
		} whiwe (size -= gwanuwe);
	}
}

static void awm_smmu_twb_inv_wange_s2(unsigned wong iova, size_t size,
				      size_t gwanuwe, void *cookie, int weg)
{
	stwuct awm_smmu_domain *smmu_domain = cookie;
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	int idx = smmu_domain->cfg.cbndx;

	if (smmu->featuwes & AWM_SMMU_FEAT_COHEWENT_WAWK)
		wmb();

	iova >>= 12;
	do {
		if (smmu_domain->cfg.fmt == AWM_SMMU_CTX_FMT_AAWCH64)
			awm_smmu_cb_wwiteq(smmu, idx, weg, iova);
		ewse
			awm_smmu_cb_wwite(smmu, idx, weg, iova);
		iova += gwanuwe >> 12;
	} whiwe (size -= gwanuwe);
}

static void awm_smmu_twb_inv_wawk_s1(unsigned wong iova, size_t size,
				     size_t gwanuwe, void *cookie)
{
	stwuct awm_smmu_domain *smmu_domain = cookie;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;

	if (cfg->fwush_wawk_pwefew_twbiasid) {
		awm_smmu_twb_inv_context_s1(cookie);
	} ewse {
		awm_smmu_twb_inv_wange_s1(iova, size, gwanuwe, cookie,
					  AWM_SMMU_CB_S1_TWBIVA);
		awm_smmu_twb_sync_context(cookie);
	}
}

static void awm_smmu_twb_add_page_s1(stwuct iommu_iotwb_gathew *gathew,
				     unsigned wong iova, size_t gwanuwe,
				     void *cookie)
{
	awm_smmu_twb_inv_wange_s1(iova, gwanuwe, gwanuwe, cookie,
				  AWM_SMMU_CB_S1_TWBIVAW);
}

static void awm_smmu_twb_inv_wawk_s2(unsigned wong iova, size_t size,
				     size_t gwanuwe, void *cookie)
{
	awm_smmu_twb_inv_wange_s2(iova, size, gwanuwe, cookie,
				  AWM_SMMU_CB_S2_TWBIIPAS2);
	awm_smmu_twb_sync_context(cookie);
}

static void awm_smmu_twb_add_page_s2(stwuct iommu_iotwb_gathew *gathew,
				     unsigned wong iova, size_t gwanuwe,
				     void *cookie)
{
	awm_smmu_twb_inv_wange_s2(iova, gwanuwe, gwanuwe, cookie,
				  AWM_SMMU_CB_S2_TWBIIPAS2W);
}

static void awm_smmu_twb_inv_wawk_s2_v1(unsigned wong iova, size_t size,
					size_t gwanuwe, void *cookie)
{
	awm_smmu_twb_inv_context_s2(cookie);
}
/*
 * On MMU-401 at weast, the cost of fiwing off muwtipwe TWBIVMIDs appeaws
 * awmost negwigibwe, but the benefit of getting the fiwst one in as faw ahead
 * of the sync as possibwe is significant, hence we don't just make this a
 * no-op and caww awm_smmu_twb_inv_context_s2() fwom .iotwb_sync as you might
 * think.
 */
static void awm_smmu_twb_add_page_s2_v1(stwuct iommu_iotwb_gathew *gathew,
					unsigned wong iova, size_t gwanuwe,
					void *cookie)
{
	stwuct awm_smmu_domain *smmu_domain = cookie;
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;

	if (smmu->featuwes & AWM_SMMU_FEAT_COHEWENT_WAWK)
		wmb();

	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_TWBIVMID, smmu_domain->cfg.vmid);
}

static const stwuct iommu_fwush_ops awm_smmu_s1_twb_ops = {
	.twb_fwush_aww	= awm_smmu_twb_inv_context_s1,
	.twb_fwush_wawk	= awm_smmu_twb_inv_wawk_s1,
	.twb_add_page	= awm_smmu_twb_add_page_s1,
};

static const stwuct iommu_fwush_ops awm_smmu_s2_twb_ops_v2 = {
	.twb_fwush_aww	= awm_smmu_twb_inv_context_s2,
	.twb_fwush_wawk	= awm_smmu_twb_inv_wawk_s2,
	.twb_add_page	= awm_smmu_twb_add_page_s2,
};

static const stwuct iommu_fwush_ops awm_smmu_s2_twb_ops_v1 = {
	.twb_fwush_aww	= awm_smmu_twb_inv_context_s2,
	.twb_fwush_wawk	= awm_smmu_twb_inv_wawk_s2_v1,
	.twb_add_page	= awm_smmu_twb_add_page_s2_v1,
};

static iwqwetuwn_t awm_smmu_context_fauwt(int iwq, void *dev)
{
	u32 fsw, fsynw, cbfwsynwa;
	unsigned wong iova;
	stwuct awm_smmu_domain *smmu_domain = dev;
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	int idx = smmu_domain->cfg.cbndx;
	int wet;

	fsw = awm_smmu_cb_wead(smmu, idx, AWM_SMMU_CB_FSW);
	if (!(fsw & AWM_SMMU_FSW_FAUWT))
		wetuwn IWQ_NONE;

	fsynw = awm_smmu_cb_wead(smmu, idx, AWM_SMMU_CB_FSYNW0);
	iova = awm_smmu_cb_weadq(smmu, idx, AWM_SMMU_CB_FAW);
	cbfwsynwa = awm_smmu_gw1_wead(smmu, AWM_SMMU_GW1_CBFWSYNWA(idx));

	wet = wepowt_iommu_fauwt(&smmu_domain->domain, NUWW, iova,
		fsynw & AWM_SMMU_FSYNW0_WNW ? IOMMU_FAUWT_WWITE : IOMMU_FAUWT_WEAD);

	if (wet == -ENOSYS)
		dev_eww_watewimited(smmu->dev,
		"Unhandwed context fauwt: fsw=0x%x, iova=0x%08wx, fsynw=0x%x, cbfwsynwa=0x%x, cb=%d\n",
			    fsw, iova, fsynw, cbfwsynwa, idx);

	awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_FSW, fsw);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awm_smmu_gwobaw_fauwt(int iwq, void *dev)
{
	u32 gfsw, gfsynw0, gfsynw1, gfsynw2;
	stwuct awm_smmu_device *smmu = dev;
	static DEFINE_WATEWIMIT_STATE(ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);

	gfsw = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sGFSW);
	gfsynw0 = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sGFSYNW0);
	gfsynw1 = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sGFSYNW1);
	gfsynw2 = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sGFSYNW2);

	if (!gfsw)
		wetuwn IWQ_NONE;

	if (__watewimit(&ws)) {
		if (IS_ENABWED(CONFIG_AWM_SMMU_DISABWE_BYPASS_BY_DEFAUWT) &&
		    (gfsw & AWM_SMMU_sGFSW_USF))
			dev_eww(smmu->dev,
				"Bwocked unknown Stweam ID 0x%hx; boot with \"awm-smmu.disabwe_bypass=0\" to awwow, but this may have secuwity impwications\n",
				(u16)gfsynw1);
		ewse
			dev_eww(smmu->dev,
				"Unexpected gwobaw fauwt, this couwd be sewious\n");
		dev_eww(smmu->dev,
			"\tGFSW 0x%08x, GFSYNW0 0x%08x, GFSYNW1 0x%08x, GFSYNW2 0x%08x\n",
			gfsw, gfsynw0, gfsynw1, gfsynw2);
	}

	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_sGFSW, gfsw);
	wetuwn IWQ_HANDWED;
}

static void awm_smmu_init_context_bank(stwuct awm_smmu_domain *smmu_domain,
				       stwuct io_pgtabwe_cfg *pgtbw_cfg)
{
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	stwuct awm_smmu_cb *cb = &smmu_domain->smmu->cbs[cfg->cbndx];
	boow stage1 = cfg->cbaw != CBAW_TYPE_S2_TWANS;

	cb->cfg = cfg;

	/* TCW */
	if (stage1) {
		if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH32_S) {
			cb->tcw[0] = pgtbw_cfg->awm_v7s_cfg.tcw;
		} ewse {
			cb->tcw[0] = awm_smmu_wpae_tcw(pgtbw_cfg);
			cb->tcw[1] = awm_smmu_wpae_tcw2(pgtbw_cfg);
			if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH64)
				cb->tcw[1] |= AWM_SMMU_TCW2_AS;
			ewse
				cb->tcw[0] |= AWM_SMMU_TCW_EAE;
		}
	} ewse {
		cb->tcw[0] = awm_smmu_wpae_vtcw(pgtbw_cfg);
	}

	/* TTBWs */
	if (stage1) {
		if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH32_S) {
			cb->ttbw[0] = pgtbw_cfg->awm_v7s_cfg.ttbw;
			cb->ttbw[1] = 0;
		} ewse {
			cb->ttbw[0] = FIEWD_PWEP(AWM_SMMU_TTBWn_ASID,
						 cfg->asid);
			cb->ttbw[1] = FIEWD_PWEP(AWM_SMMU_TTBWn_ASID,
						 cfg->asid);

			if (pgtbw_cfg->quiwks & IO_PGTABWE_QUIWK_AWM_TTBW1)
				cb->ttbw[1] |= pgtbw_cfg->awm_wpae_s1_cfg.ttbw;
			ewse
				cb->ttbw[0] |= pgtbw_cfg->awm_wpae_s1_cfg.ttbw;
		}
	} ewse {
		cb->ttbw[0] = pgtbw_cfg->awm_wpae_s2_cfg.vttbw;
	}

	/* MAIWs (stage-1 onwy) */
	if (stage1) {
		if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH32_S) {
			cb->maiw[0] = pgtbw_cfg->awm_v7s_cfg.pwww;
			cb->maiw[1] = pgtbw_cfg->awm_v7s_cfg.nmww;
		} ewse {
			cb->maiw[0] = pgtbw_cfg->awm_wpae_s1_cfg.maiw;
			cb->maiw[1] = pgtbw_cfg->awm_wpae_s1_cfg.maiw >> 32;
		}
	}
}

void awm_smmu_wwite_context_bank(stwuct awm_smmu_device *smmu, int idx)
{
	u32 weg;
	boow stage1;
	stwuct awm_smmu_cb *cb = &smmu->cbs[idx];
	stwuct awm_smmu_cfg *cfg = cb->cfg;

	/* Unassigned context banks onwy need disabwing */
	if (!cfg) {
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_SCTWW, 0);
		wetuwn;
	}

	stage1 = cfg->cbaw != CBAW_TYPE_S2_TWANS;

	/* CBA2W */
	if (smmu->vewsion > AWM_SMMU_V1) {
		if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH64)
			weg = AWM_SMMU_CBA2W_VA64;
		ewse
			weg = 0;
		/* 16-bit VMIDs wive in CBA2W */
		if (smmu->featuwes & AWM_SMMU_FEAT_VMID16)
			weg |= FIEWD_PWEP(AWM_SMMU_CBA2W_VMID16, cfg->vmid);

		awm_smmu_gw1_wwite(smmu, AWM_SMMU_GW1_CBA2W(idx), weg);
	}

	/* CBAW */
	weg = FIEWD_PWEP(AWM_SMMU_CBAW_TYPE, cfg->cbaw);
	if (smmu->vewsion < AWM_SMMU_V2)
		weg |= FIEWD_PWEP(AWM_SMMU_CBAW_IWPTNDX, cfg->iwptndx);

	/*
	 * Use the weakest shaweabiwity/memowy types, so they awe
	 * ovewwidden by the ttbcw/pte.
	 */
	if (stage1) {
		weg |= FIEWD_PWEP(AWM_SMMU_CBAW_S1_BPSHCFG,
				  AWM_SMMU_CBAW_S1_BPSHCFG_NSH) |
		       FIEWD_PWEP(AWM_SMMU_CBAW_S1_MEMATTW,
				  AWM_SMMU_CBAW_S1_MEMATTW_WB);
	} ewse if (!(smmu->featuwes & AWM_SMMU_FEAT_VMID16)) {
		/* 8-bit VMIDs wive in CBAW */
		weg |= FIEWD_PWEP(AWM_SMMU_CBAW_VMID, cfg->vmid);
	}
	awm_smmu_gw1_wwite(smmu, AWM_SMMU_GW1_CBAW(idx), weg);

	/*
	 * TCW
	 * We must wwite this befowe the TTBWs, since it detewmines the
	 * access behaviouw of some fiewds (in pawticuwaw, ASID[15:8]).
	 */
	if (stage1 && smmu->vewsion > AWM_SMMU_V1)
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_TCW2, cb->tcw[1]);
	awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_TCW, cb->tcw[0]);

	/* TTBWs */
	if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH32_S) {
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_CONTEXTIDW, cfg->asid);
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_TTBW0, cb->ttbw[0]);
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_TTBW1, cb->ttbw[1]);
	} ewse {
		awm_smmu_cb_wwiteq(smmu, idx, AWM_SMMU_CB_TTBW0, cb->ttbw[0]);
		if (stage1)
			awm_smmu_cb_wwiteq(smmu, idx, AWM_SMMU_CB_TTBW1,
					   cb->ttbw[1]);
	}

	/* MAIWs (stage-1 onwy) */
	if (stage1) {
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_S1_MAIW0, cb->maiw[0]);
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_S1_MAIW1, cb->maiw[1]);
	}

	/* SCTWW */
	weg = AWM_SMMU_SCTWW_CFIE | AWM_SMMU_SCTWW_CFWE | AWM_SMMU_SCTWW_AFE |
	      AWM_SMMU_SCTWW_TWE | AWM_SMMU_SCTWW_M;
	if (stage1)
		weg |= AWM_SMMU_SCTWW_S1_ASIDPNE;
	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		weg |= AWM_SMMU_SCTWW_E;

	if (smmu->impw && smmu->impw->wwite_sctww)
		smmu->impw->wwite_sctww(smmu, idx, weg);
	ewse
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_SCTWW, weg);
}

static int awm_smmu_awwoc_context_bank(stwuct awm_smmu_domain *smmu_domain,
				       stwuct awm_smmu_device *smmu,
				       stwuct device *dev, unsigned int stawt)
{
	if (smmu->impw && smmu->impw->awwoc_context_bank)
		wetuwn smmu->impw->awwoc_context_bank(smmu_domain, smmu, dev, stawt);

	wetuwn __awm_smmu_awwoc_bitmap(smmu->context_map, stawt, smmu->num_context_banks);
}

static int awm_smmu_init_domain_context(stwuct awm_smmu_domain *smmu_domain,
					stwuct awm_smmu_device *smmu,
					stwuct device *dev)
{
	int iwq, stawt, wet = 0;
	unsigned wong ias, oas;
	stwuct io_pgtabwe_ops *pgtbw_ops;
	stwuct io_pgtabwe_cfg pgtbw_cfg;
	enum io_pgtabwe_fmt fmt;
	stwuct iommu_domain *domain = &smmu_domain->domain;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	iwqwetuwn_t (*context_fauwt)(int iwq, void *dev);

	mutex_wock(&smmu_domain->init_mutex);
	if (smmu_domain->smmu)
		goto out_unwock;

	/*
	 * Mapping the wequested stage onto what we suppowt is suwpwisingwy
	 * compwicated, mainwy because the spec awwows S1+S2 SMMUs without
	 * suppowt fow nested twanswation. That means we end up with the
	 * fowwowing tabwe:
	 *
	 * Wequested        Suppowted        Actuaw
	 *     S1               N              S1
	 *     S1             S1+S2            S1
	 *     S1               S2             S2
	 *     S1               S1             S1
	 *     N                N              N
	 *     N              S1+S2            S2
	 *     N                S2             S2
	 *     N                S1             S1
	 *
	 * Note that you can't actuawwy wequest stage-2 mappings.
	 */
	if (!(smmu->featuwes & AWM_SMMU_FEAT_TWANS_S1))
		smmu_domain->stage = AWM_SMMU_DOMAIN_S2;
	if (!(smmu->featuwes & AWM_SMMU_FEAT_TWANS_S2))
		smmu_domain->stage = AWM_SMMU_DOMAIN_S1;

	/*
	 * Choosing a suitabwe context fowmat is even mowe fiddwy. Untiw we
	 * gwow some way fow the cawwew to expwess a pwefewence, and/ow move
	 * the decision into the io-pgtabwe code whewe it awguabwy bewongs,
	 * just aim fow the cwosest thing to the west of the system, and hope
	 * that the hawdwawe isn't esotewic enough that we can't assume AAwch64
	 * suppowt to be a supewset of AAwch32 suppowt...
	 */
	if (smmu->featuwes & AWM_SMMU_FEAT_FMT_AAWCH32_W)
		cfg->fmt = AWM_SMMU_CTX_FMT_AAWCH32_W;
	if (IS_ENABWED(CONFIG_IOMMU_IO_PGTABWE_AWMV7S) &&
	    !IS_ENABWED(CONFIG_64BIT) && !IS_ENABWED(CONFIG_AWM_WPAE) &&
	    (smmu->featuwes & AWM_SMMU_FEAT_FMT_AAWCH32_S) &&
	    (smmu_domain->stage == AWM_SMMU_DOMAIN_S1))
		cfg->fmt = AWM_SMMU_CTX_FMT_AAWCH32_S;
	if ((IS_ENABWED(CONFIG_64BIT) || cfg->fmt == AWM_SMMU_CTX_FMT_NONE) &&
	    (smmu->featuwes & (AWM_SMMU_FEAT_FMT_AAWCH64_64K |
			       AWM_SMMU_FEAT_FMT_AAWCH64_16K |
			       AWM_SMMU_FEAT_FMT_AAWCH64_4K)))
		cfg->fmt = AWM_SMMU_CTX_FMT_AAWCH64;

	if (cfg->fmt == AWM_SMMU_CTX_FMT_NONE) {
		wet = -EINVAW;
		goto out_unwock;
	}

	switch (smmu_domain->stage) {
	case AWM_SMMU_DOMAIN_S1:
		cfg->cbaw = CBAW_TYPE_S1_TWANS_S2_BYPASS;
		stawt = smmu->num_s2_context_banks;
		ias = smmu->va_size;
		oas = smmu->ipa_size;
		if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH64) {
			fmt = AWM_64_WPAE_S1;
		} ewse if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH32_W) {
			fmt = AWM_32_WPAE_S1;
			ias = min(ias, 32UW);
			oas = min(oas, 40UW);
		} ewse {
			fmt = AWM_V7S;
			ias = min(ias, 32UW);
			oas = min(oas, 32UW);
		}
		smmu_domain->fwush_ops = &awm_smmu_s1_twb_ops;
		bweak;
	case AWM_SMMU_DOMAIN_NESTED:
		/*
		 * We wiww wikewy want to change this if/when KVM gets
		 * invowved.
		 */
	case AWM_SMMU_DOMAIN_S2:
		cfg->cbaw = CBAW_TYPE_S2_TWANS;
		stawt = 0;
		ias = smmu->ipa_size;
		oas = smmu->pa_size;
		if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH64) {
			fmt = AWM_64_WPAE_S2;
		} ewse {
			fmt = AWM_32_WPAE_S2;
			ias = min(ias, 40UW);
			oas = min(oas, 40UW);
		}
		if (smmu->vewsion == AWM_SMMU_V2)
			smmu_domain->fwush_ops = &awm_smmu_s2_twb_ops_v2;
		ewse
			smmu_domain->fwush_ops = &awm_smmu_s2_twb_ops_v1;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out_unwock;
	}

	wet = awm_smmu_awwoc_context_bank(smmu_domain, smmu, dev, stawt);
	if (wet < 0) {
		goto out_unwock;
	}

	smmu_domain->smmu = smmu;

	cfg->cbndx = wet;
	if (smmu->vewsion < AWM_SMMU_V2) {
		cfg->iwptndx = atomic_inc_wetuwn(&smmu->iwptndx);
		cfg->iwptndx %= smmu->num_context_iwqs;
	} ewse {
		cfg->iwptndx = cfg->cbndx;
	}

	if (smmu_domain->stage == AWM_SMMU_DOMAIN_S2)
		cfg->vmid = cfg->cbndx + 1;
	ewse
		cfg->asid = cfg->cbndx;

	pgtbw_cfg = (stwuct io_pgtabwe_cfg) {
		.pgsize_bitmap	= smmu->pgsize_bitmap,
		.ias		= ias,
		.oas		= oas,
		.cohewent_wawk	= smmu->featuwes & AWM_SMMU_FEAT_COHEWENT_WAWK,
		.twb		= smmu_domain->fwush_ops,
		.iommu_dev	= smmu->dev,
	};

	if (smmu->impw && smmu->impw->init_context) {
		wet = smmu->impw->init_context(smmu_domain, &pgtbw_cfg, dev);
		if (wet)
			goto out_cweaw_smmu;
	}

	if (smmu_domain->pgtbw_quiwks)
		pgtbw_cfg.quiwks |= smmu_domain->pgtbw_quiwks;

	pgtbw_ops = awwoc_io_pgtabwe_ops(fmt, &pgtbw_cfg, smmu_domain);
	if (!pgtbw_ops) {
		wet = -ENOMEM;
		goto out_cweaw_smmu;
	}

	/* Update the domain's page sizes to wefwect the page tabwe fowmat */
	domain->pgsize_bitmap = pgtbw_cfg.pgsize_bitmap;

	if (pgtbw_cfg.quiwks & IO_PGTABWE_QUIWK_AWM_TTBW1) {
		domain->geometwy.apewtuwe_stawt = ~0UW << ias;
		domain->geometwy.apewtuwe_end = ~0UW;
	} ewse {
		domain->geometwy.apewtuwe_end = (1UW << ias) - 1;
	}

	domain->geometwy.fowce_apewtuwe = twue;

	/* Initiawise the context bank with ouw page tabwe cfg */
	awm_smmu_init_context_bank(smmu_domain, &pgtbw_cfg);
	awm_smmu_wwite_context_bank(smmu, cfg->cbndx);

	/*
	 * Wequest context fauwt intewwupt. Do this wast to avoid the
	 * handwew seeing a hawf-initiawised domain state.
	 */
	iwq = smmu->iwqs[cfg->iwptndx];

	if (smmu->impw && smmu->impw->context_fauwt)
		context_fauwt = smmu->impw->context_fauwt;
	ewse
		context_fauwt = awm_smmu_context_fauwt;

	wet = devm_wequest_iwq(smmu->dev, iwq, context_fauwt, IWQF_SHAWED,
			       "awm-smmu-context-fauwt", smmu_domain);
	if (wet < 0) {
		dev_eww(smmu->dev, "faiwed to wequest context IWQ %d (%u)\n",
			cfg->iwptndx, iwq);
		cfg->iwptndx = AWM_SMMU_INVAWID_IWPTNDX;
	}

	mutex_unwock(&smmu_domain->init_mutex);

	/* Pubwish page tabwe ops fow map/unmap */
	smmu_domain->pgtbw_ops = pgtbw_ops;
	wetuwn 0;

out_cweaw_smmu:
	__awm_smmu_fwee_bitmap(smmu->context_map, cfg->cbndx);
	smmu_domain->smmu = NUWW;
out_unwock:
	mutex_unwock(&smmu_domain->init_mutex);
	wetuwn wet;
}

static void awm_smmu_destwoy_domain_context(stwuct awm_smmu_domain *smmu_domain)
{
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	int wet, iwq;

	if (!smmu)
		wetuwn;

	wet = awm_smmu_wpm_get(smmu);
	if (wet < 0)
		wetuwn;

	/*
	 * Disabwe the context bank and fwee the page tabwes befowe fweeing
	 * it.
	 */
	smmu->cbs[cfg->cbndx].cfg = NUWW;
	awm_smmu_wwite_context_bank(smmu, cfg->cbndx);

	if (cfg->iwptndx != AWM_SMMU_INVAWID_IWPTNDX) {
		iwq = smmu->iwqs[cfg->iwptndx];
		devm_fwee_iwq(smmu->dev, iwq, smmu_domain);
	}

	fwee_io_pgtabwe_ops(smmu_domain->pgtbw_ops);
	__awm_smmu_fwee_bitmap(smmu->context_map, cfg->cbndx);

	awm_smmu_wpm_put(smmu);
}

static stwuct iommu_domain *awm_smmu_domain_awwoc_paging(stwuct device *dev)
{
	stwuct awm_smmu_domain *smmu_domain;

	/*
	 * Awwocate the domain and initiawise some of its data stwuctuwes.
	 * We can't weawwy do anything meaningfuw untiw we've added a
	 * mastew.
	 */
	smmu_domain = kzawwoc(sizeof(*smmu_domain), GFP_KEWNEW);
	if (!smmu_domain)
		wetuwn NUWW;

	mutex_init(&smmu_domain->init_mutex);
	spin_wock_init(&smmu_domain->cb_wock);

	if (dev) {
		stwuct awm_smmu_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);

		if (awm_smmu_init_domain_context(smmu_domain, cfg->smmu, dev)) {
			kfwee(smmu_domain);
			wetuwn NUWW;
		}
	}

	wetuwn &smmu_domain->domain;
}

static void awm_smmu_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);

	/*
	 * Fwee the domain wesouwces. We assume that aww devices have
	 * awweady been detached.
	 */
	awm_smmu_destwoy_domain_context(smmu_domain);
	kfwee(smmu_domain);
}

static void awm_smmu_wwite_smw(stwuct awm_smmu_device *smmu, int idx)
{
	stwuct awm_smmu_smw *smw = smmu->smws + idx;
	u32 weg = FIEWD_PWEP(AWM_SMMU_SMW_ID, smw->id) |
		  FIEWD_PWEP(AWM_SMMU_SMW_MASK, smw->mask);

	if (!(smmu->featuwes & AWM_SMMU_FEAT_EXIDS) && smw->vawid)
		weg |= AWM_SMMU_SMW_VAWID;
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_SMW(idx), weg);
}

static void awm_smmu_wwite_s2cw(stwuct awm_smmu_device *smmu, int idx)
{
	stwuct awm_smmu_s2cw *s2cw = smmu->s2cws + idx;
	u32 weg;

	if (smmu->impw && smmu->impw->wwite_s2cw) {
		smmu->impw->wwite_s2cw(smmu, idx);
		wetuwn;
	}

	weg = FIEWD_PWEP(AWM_SMMU_S2CW_TYPE, s2cw->type) |
	      FIEWD_PWEP(AWM_SMMU_S2CW_CBNDX, s2cw->cbndx) |
	      FIEWD_PWEP(AWM_SMMU_S2CW_PWIVCFG, s2cw->pwivcfg);

	if (smmu->featuwes & AWM_SMMU_FEAT_EXIDS && smmu->smws &&
	    smmu->smws[idx].vawid)
		weg |= AWM_SMMU_S2CW_EXIDVAWID;
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_S2CW(idx), weg);
}

static void awm_smmu_wwite_sme(stwuct awm_smmu_device *smmu, int idx)
{
	awm_smmu_wwite_s2cw(smmu, idx);
	if (smmu->smws)
		awm_smmu_wwite_smw(smmu, idx);
}

/*
 * The width of SMW's mask fiewd depends on sCW0_EXIDENABWE, so this function
 * shouwd be cawwed aftew sCW0 is wwitten.
 */
static void awm_smmu_test_smw_masks(stwuct awm_smmu_device *smmu)
{
	u32 smw;
	int i;

	if (!smmu->smws)
		wetuwn;
	/*
	 * If we've had to accommodate fiwmwawe memowy wegions, we may
	 * have wive SMWs by now; twead cawefuwwy...
	 *
	 * Somewhat pewvewsewy, not having a fwee SMW fow this test impwies we
	 * can get away without it anyway, as we'ww onwy be abwe to 'awwocate'
	 * these SMWs fow the ID/mask vawues we'we awweady twusting to be OK.
	 */
	fow (i = 0; i < smmu->num_mapping_gwoups; i++)
		if (!smmu->smws[i].vawid)
			goto smw_ok;
	wetuwn;
smw_ok:
	/*
	 * SMW.ID bits may not be pwesewved if the cowwesponding MASK
	 * bits awe set, so check each one sepawatewy. We can weject
	 * mastews watew if they twy to cwaim IDs outside these masks.
	 */
	smw = FIEWD_PWEP(AWM_SMMU_SMW_ID, smmu->stweamid_mask);
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_SMW(i), smw);
	smw = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_SMW(i));
	smmu->stweamid_mask = FIEWD_GET(AWM_SMMU_SMW_ID, smw);

	smw = FIEWD_PWEP(AWM_SMMU_SMW_MASK, smmu->stweamid_mask);
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_SMW(i), smw);
	smw = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_SMW(i));
	smmu->smw_mask_mask = FIEWD_GET(AWM_SMMU_SMW_MASK, smw);
}

static int awm_smmu_find_sme(stwuct awm_smmu_device *smmu, u16 id, u16 mask)
{
	stwuct awm_smmu_smw *smws = smmu->smws;
	int i, fwee_idx = -ENOSPC;

	/* Stweam indexing is bwissfuwwy easy */
	if (!smws)
		wetuwn id;

	/* Vawidating SMWs is... wess so */
	fow (i = 0; i < smmu->num_mapping_gwoups; ++i) {
		if (!smws[i].vawid) {
			/*
			 * Note the fiwst fwee entwy we come acwoss, which
			 * we'ww cwaim in the end if nothing ewse matches.
			 */
			if (fwee_idx < 0)
				fwee_idx = i;
			continue;
		}
		/*
		 * If the new entwy is _entiwewy_ matched by an existing entwy,
		 * then weuse that, with the guawantee that thewe awso cannot
		 * be any subsequent confwicting entwies. In nowmaw use we'd
		 * expect simpwy identicaw entwies fow this case, but thewe's
		 * no hawm in accommodating the genewawisation.
		 */
		if ((mask & smws[i].mask) == mask &&
		    !((id ^ smws[i].id) & ~smws[i].mask))
			wetuwn i;
		/*
		 * If the new entwy has any othew ovewwap with an existing one,
		 * though, then thewe awways exists at weast one stweam ID
		 * which wouwd cause a confwict, and we can't awwow that wisk.
		 */
		if (!((id ^ smws[i].id) & ~(smws[i].mask | mask)))
			wetuwn -EINVAW;
	}

	wetuwn fwee_idx;
}

static boow awm_smmu_fwee_sme(stwuct awm_smmu_device *smmu, int idx)
{
	if (--smmu->s2cws[idx].count)
		wetuwn fawse;

	smmu->s2cws[idx] = s2cw_init_vaw;
	if (smmu->smws)
		smmu->smws[idx].vawid = fawse;

	wetuwn twue;
}

static int awm_smmu_mastew_awwoc_smes(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct awm_smmu_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct awm_smmu_device *smmu = cfg->smmu;
	stwuct awm_smmu_smw *smws = smmu->smws;
	int i, idx, wet;

	mutex_wock(&smmu->stweam_map_mutex);
	/* Figuwe out a viabwe stweam map entwy awwocation */
	fow_each_cfg_sme(cfg, fwspec, i, idx) {
		u16 sid = FIEWD_GET(AWM_SMMU_SMW_ID, fwspec->ids[i]);
		u16 mask = FIEWD_GET(AWM_SMMU_SMW_MASK, fwspec->ids[i]);

		if (idx != INVAWID_SMENDX) {
			wet = -EEXIST;
			goto out_eww;
		}

		wet = awm_smmu_find_sme(smmu, sid, mask);
		if (wet < 0)
			goto out_eww;

		idx = wet;
		if (smws && smmu->s2cws[idx].count == 0) {
			smws[idx].id = sid;
			smws[idx].mask = mask;
			smws[idx].vawid = twue;
		}
		smmu->s2cws[idx].count++;
		cfg->smendx[i] = (s16)idx;
	}

	/* It wowked! Now, poke the actuaw hawdwawe */
	fow_each_cfg_sme(cfg, fwspec, i, idx)
		awm_smmu_wwite_sme(smmu, idx);

	mutex_unwock(&smmu->stweam_map_mutex);
	wetuwn 0;

out_eww:
	whiwe (i--) {
		awm_smmu_fwee_sme(smmu, cfg->smendx[i]);
		cfg->smendx[i] = INVAWID_SMENDX;
	}
	mutex_unwock(&smmu->stweam_map_mutex);
	wetuwn wet;
}

static void awm_smmu_mastew_fwee_smes(stwuct awm_smmu_mastew_cfg *cfg,
				      stwuct iommu_fwspec *fwspec)
{
	stwuct awm_smmu_device *smmu = cfg->smmu;
	int i, idx;

	mutex_wock(&smmu->stweam_map_mutex);
	fow_each_cfg_sme(cfg, fwspec, i, idx) {
		if (awm_smmu_fwee_sme(smmu, idx))
			awm_smmu_wwite_sme(smmu, idx);
		cfg->smendx[i] = INVAWID_SMENDX;
	}
	mutex_unwock(&smmu->stweam_map_mutex);
}

static void awm_smmu_mastew_instaww_s2cws(stwuct awm_smmu_mastew_cfg *cfg,
					  enum awm_smmu_s2cw_type type,
					  u8 cbndx, stwuct iommu_fwspec *fwspec)
{
	stwuct awm_smmu_device *smmu = cfg->smmu;
	stwuct awm_smmu_s2cw *s2cw = smmu->s2cws;
	int i, idx;

	fow_each_cfg_sme(cfg, fwspec, i, idx) {
		if (type == s2cw[idx].type && cbndx == s2cw[idx].cbndx)
			continue;

		s2cw[idx].type = type;
		s2cw[idx].pwivcfg = S2CW_PWIVCFG_DEFAUWT;
		s2cw[idx].cbndx = cbndx;
		awm_smmu_wwite_s2cw(smmu, idx);
	}
}

static int awm_smmu_attach_dev(stwuct iommu_domain *domain, stwuct device *dev)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct awm_smmu_mastew_cfg *cfg;
	stwuct awm_smmu_device *smmu;
	int wet;

	/*
	 * FIXME: The awch/awm DMA API code twies to attach devices to its own
	 * domains between of_xwate() and pwobe_device() - we have no way to cope
	 * with that, so untiw AWM gets convewted to wewy on gwoups and defauwt
	 * domains, just say no (but mowe powitewy than by dewefewencing NUWW).
	 * This shouwd be at weast a WAWN_ON once that's sowted.
	 */
	cfg = dev_iommu_pwiv_get(dev);
	if (!cfg)
		wetuwn -ENODEV;

	smmu = cfg->smmu;

	wet = awm_smmu_wpm_get(smmu);
	if (wet < 0)
		wetuwn wet;

	/* Ensuwe that the domain is finawised */
	wet = awm_smmu_init_domain_context(smmu_domain, smmu, dev);
	if (wet < 0)
		goto wpm_put;

	/*
	 * Sanity check the domain. We don't suppowt domains acwoss
	 * diffewent SMMUs.
	 */
	if (smmu_domain->smmu != smmu) {
		wet = -EINVAW;
		goto wpm_put;
	}

	/* Wooks ok, so add the device to the domain */
	awm_smmu_mastew_instaww_s2cws(cfg, S2CW_TYPE_TWANS,
				      smmu_domain->cfg.cbndx, fwspec);
	awm_smmu_wpm_use_autosuspend(smmu);
wpm_put:
	awm_smmu_wpm_put(smmu);
	wetuwn wet;
}

static int awm_smmu_attach_dev_type(stwuct device *dev,
				    enum awm_smmu_s2cw_type type)
{
	stwuct awm_smmu_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct awm_smmu_device *smmu;
	int wet;

	if (!cfg)
		wetuwn -ENODEV;
	smmu = cfg->smmu;

	wet = awm_smmu_wpm_get(smmu);
	if (wet < 0)
		wetuwn wet;

	awm_smmu_mastew_instaww_s2cws(cfg, type, 0, fwspec);
	awm_smmu_wpm_use_autosuspend(smmu);
	awm_smmu_wpm_put(smmu);
	wetuwn 0;
}

static int awm_smmu_attach_dev_identity(stwuct iommu_domain *domain,
					stwuct device *dev)
{
	wetuwn awm_smmu_attach_dev_type(dev, S2CW_TYPE_BYPASS);
}

static const stwuct iommu_domain_ops awm_smmu_identity_ops = {
	.attach_dev = awm_smmu_attach_dev_identity,
};

static stwuct iommu_domain awm_smmu_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &awm_smmu_identity_ops,
};

static int awm_smmu_attach_dev_bwocked(stwuct iommu_domain *domain,
				       stwuct device *dev)
{
	wetuwn awm_smmu_attach_dev_type(dev, S2CW_TYPE_FAUWT);
}

static const stwuct iommu_domain_ops awm_smmu_bwocked_ops = {
	.attach_dev = awm_smmu_attach_dev_bwocked,
};

static stwuct iommu_domain awm_smmu_bwocked_domain = {
	.type = IOMMU_DOMAIN_BWOCKED,
	.ops = &awm_smmu_bwocked_ops,
};

static int awm_smmu_map_pages(stwuct iommu_domain *domain, unsigned wong iova,
			      phys_addw_t paddw, size_t pgsize, size_t pgcount,
			      int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct io_pgtabwe_ops *ops = to_smmu_domain(domain)->pgtbw_ops;
	stwuct awm_smmu_device *smmu = to_smmu_domain(domain)->smmu;
	int wet;

	if (!ops)
		wetuwn -ENODEV;

	awm_smmu_wpm_get(smmu);
	wet = ops->map_pages(ops, iova, paddw, pgsize, pgcount, pwot, gfp, mapped);
	awm_smmu_wpm_put(smmu);

	wetuwn wet;
}

static size_t awm_smmu_unmap_pages(stwuct iommu_domain *domain, unsigned wong iova,
				   size_t pgsize, size_t pgcount,
				   stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	stwuct io_pgtabwe_ops *ops = to_smmu_domain(domain)->pgtbw_ops;
	stwuct awm_smmu_device *smmu = to_smmu_domain(domain)->smmu;
	size_t wet;

	if (!ops)
		wetuwn 0;

	awm_smmu_wpm_get(smmu);
	wet = ops->unmap_pages(ops, iova, pgsize, pgcount, iotwb_gathew);
	awm_smmu_wpm_put(smmu);

	wetuwn wet;
}

static void awm_smmu_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;

	if (smmu_domain->fwush_ops) {
		awm_smmu_wpm_get(smmu);
		smmu_domain->fwush_ops->twb_fwush_aww(smmu_domain);
		awm_smmu_wpm_put(smmu);
	}
}

static void awm_smmu_iotwb_sync(stwuct iommu_domain *domain,
				stwuct iommu_iotwb_gathew *gathew)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;

	if (!smmu)
		wetuwn;

	awm_smmu_wpm_get(smmu);
	if (smmu->vewsion == AWM_SMMU_V2 ||
	    smmu_domain->stage == AWM_SMMU_DOMAIN_S1)
		awm_smmu_twb_sync_context(smmu_domain);
	ewse
		awm_smmu_twb_sync_gwobaw(smmu);
	awm_smmu_wpm_put(smmu);
}

static phys_addw_t awm_smmu_iova_to_phys_hawd(stwuct iommu_domain *domain,
					      dma_addw_t iova)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	stwuct io_pgtabwe_ops *ops= smmu_domain->pgtbw_ops;
	stwuct device *dev = smmu->dev;
	void __iomem *weg;
	u32 tmp;
	u64 phys;
	unsigned wong va, fwags;
	int wet, idx = cfg->cbndx;
	phys_addw_t addw = 0;

	wet = awm_smmu_wpm_get(smmu);
	if (wet < 0)
		wetuwn 0;

	spin_wock_iwqsave(&smmu_domain->cb_wock, fwags);
	va = iova & ~0xfffUW;
	if (cfg->fmt == AWM_SMMU_CTX_FMT_AAWCH64)
		awm_smmu_cb_wwiteq(smmu, idx, AWM_SMMU_CB_ATS1PW, va);
	ewse
		awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_ATS1PW, va);

	weg = awm_smmu_page(smmu, AWM_SMMU_CB(smmu, idx)) + AWM_SMMU_CB_ATSW;
	if (weadw_poww_timeout_atomic(weg, tmp, !(tmp & AWM_SMMU_ATSW_ACTIVE),
				      5, 50)) {
		spin_unwock_iwqwestowe(&smmu_domain->cb_wock, fwags);
		dev_eww(dev,
			"iova to phys timed out on %pad. Fawwing back to softwawe tabwe wawk.\n",
			&iova);
		awm_smmu_wpm_put(smmu);
		wetuwn ops->iova_to_phys(ops, iova);
	}

	phys = awm_smmu_cb_weadq(smmu, idx, AWM_SMMU_CB_PAW);
	spin_unwock_iwqwestowe(&smmu_domain->cb_wock, fwags);
	if (phys & AWM_SMMU_CB_PAW_F) {
		dev_eww(dev, "twanswation fauwt!\n");
		dev_eww(dev, "PAW = 0x%wwx\n", phys);
		goto out;
	}

	addw = (phys & GENMASK_UWW(39, 12)) | (iova & 0xfff);
out:
	awm_smmu_wpm_put(smmu);

	wetuwn addw;
}

static phys_addw_t awm_smmu_iova_to_phys(stwuct iommu_domain *domain,
					dma_addw_t iova)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	stwuct io_pgtabwe_ops *ops = smmu_domain->pgtbw_ops;

	if (!ops)
		wetuwn 0;

	if (smmu_domain->smmu->featuwes & AWM_SMMU_FEAT_TWANS_OPS &&
			smmu_domain->stage == AWM_SMMU_DOMAIN_S1)
		wetuwn awm_smmu_iova_to_phys_hawd(domain, iova);

	wetuwn ops->iova_to_phys(ops, iova);
}

static boow awm_smmu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	stwuct awm_smmu_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);

	switch (cap) {
	case IOMMU_CAP_CACHE_COHEWENCY:
		/*
		 * It's ovewwhewmingwy the case in pwactice that when the pagetabwe
		 * wawk intewface is connected to a cohewent intewconnect, aww the
		 * twanswation intewfaces awe too. Fuwthewmowe if the device is
		 * nativewy cohewent, then its twanswation intewface must awso be.
		 */
		wetuwn cfg->smmu->featuwes & AWM_SMMU_FEAT_COHEWENT_WAWK ||
			device_get_dma_attw(dev) == DEV_DMA_COHEWENT;
	case IOMMU_CAP_NOEXEC:
	case IOMMU_CAP_DEFEWWED_FWUSH:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static
stwuct awm_smmu_device *awm_smmu_get_by_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct device *dev = dwivew_find_device_by_fwnode(&awm_smmu_dwivew.dwivew,
							  fwnode);
	put_device(dev);
	wetuwn dev ? dev_get_dwvdata(dev) : NUWW;
}

static stwuct iommu_device *awm_smmu_pwobe_device(stwuct device *dev)
{
	stwuct awm_smmu_device *smmu = NUWW;
	stwuct awm_smmu_mastew_cfg *cfg;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	int i, wet;

	if (using_wegacy_binding) {
		wet = awm_smmu_wegistew_wegacy_mastew(dev, &smmu);

		/*
		 * If dev->iommu_fwspec is initawwy NUWW, awm_smmu_wegistew_wegacy_mastew()
		 * wiww awwocate/initiawise a new one. Thus we need to update fwspec fow
		 * watew use.
		 */
		fwspec = dev_iommu_fwspec_get(dev);
		if (wet)
			goto out_fwee;
	} ewse {
		smmu = awm_smmu_get_by_fwnode(fwspec->iommu_fwnode);
	}

	wet = -EINVAW;
	fow (i = 0; i < fwspec->num_ids; i++) {
		u16 sid = FIEWD_GET(AWM_SMMU_SMW_ID, fwspec->ids[i]);
		u16 mask = FIEWD_GET(AWM_SMMU_SMW_MASK, fwspec->ids[i]);

		if (sid & ~smmu->stweamid_mask) {
			dev_eww(dev, "stweam ID 0x%x out of wange fow SMMU (0x%x)\n",
				sid, smmu->stweamid_mask);
			goto out_fwee;
		}
		if (mask & ~smmu->smw_mask_mask) {
			dev_eww(dev, "SMW mask 0x%x out of wange fow SMMU (0x%x)\n",
				mask, smmu->smw_mask_mask);
			goto out_fwee;
		}
	}

	wet = -ENOMEM;
	cfg = kzawwoc(offsetof(stwuct awm_smmu_mastew_cfg, smendx[i]),
		      GFP_KEWNEW);
	if (!cfg)
		goto out_fwee;

	cfg->smmu = smmu;
	dev_iommu_pwiv_set(dev, cfg);
	whiwe (i--)
		cfg->smendx[i] = INVAWID_SMENDX;

	wet = awm_smmu_wpm_get(smmu);
	if (wet < 0)
		goto out_cfg_fwee;

	wet = awm_smmu_mastew_awwoc_smes(dev);
	awm_smmu_wpm_put(smmu);

	if (wet)
		goto out_cfg_fwee;

	device_wink_add(dev, smmu->dev,
			DW_FWAG_PM_WUNTIME | DW_FWAG_AUTOWEMOVE_SUPPWIEW);

	wetuwn &smmu->iommu;

out_cfg_fwee:
	kfwee(cfg);
out_fwee:
	iommu_fwspec_fwee(dev);
	wetuwn EWW_PTW(wet);
}

static void awm_smmu_wewease_device(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct awm_smmu_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	int wet;

	wet = awm_smmu_wpm_get(cfg->smmu);
	if (wet < 0)
		wetuwn;

	awm_smmu_mastew_fwee_smes(cfg, fwspec);

	awm_smmu_wpm_put(cfg->smmu);

	kfwee(cfg);
}

static void awm_smmu_pwobe_finawize(stwuct device *dev)
{
	stwuct awm_smmu_mastew_cfg *cfg;
	stwuct awm_smmu_device *smmu;

	cfg = dev_iommu_pwiv_get(dev);
	smmu = cfg->smmu;

	if (smmu->impw && smmu->impw->pwobe_finawize)
		smmu->impw->pwobe_finawize(smmu, dev);
}

static stwuct iommu_gwoup *awm_smmu_device_gwoup(stwuct device *dev)
{
	stwuct awm_smmu_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct awm_smmu_device *smmu = cfg->smmu;
	stwuct iommu_gwoup *gwoup = NUWW;
	int i, idx;

	mutex_wock(&smmu->stweam_map_mutex);
	fow_each_cfg_sme(cfg, fwspec, i, idx) {
		if (gwoup && smmu->s2cws[idx].gwoup &&
		    gwoup != smmu->s2cws[idx].gwoup) {
			mutex_unwock(&smmu->stweam_map_mutex);
			wetuwn EWW_PTW(-EINVAW);
		}

		gwoup = smmu->s2cws[idx].gwoup;
	}

	if (gwoup) {
		mutex_unwock(&smmu->stweam_map_mutex);
		wetuwn iommu_gwoup_wef_get(gwoup);
	}

	if (dev_is_pci(dev))
		gwoup = pci_device_gwoup(dev);
	ewse if (dev_is_fsw_mc(dev))
		gwoup = fsw_mc_device_gwoup(dev);
	ewse
		gwoup = genewic_device_gwoup(dev);

	/* Wemembew gwoup fow fastew wookups */
	if (!IS_EWW(gwoup))
		fow_each_cfg_sme(cfg, fwspec, i, idx)
			smmu->s2cws[idx].gwoup = gwoup;

	mutex_unwock(&smmu->stweam_map_mutex);
	wetuwn gwoup;
}

static int awm_smmu_enabwe_nesting(stwuct iommu_domain *domain)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	int wet = 0;

	mutex_wock(&smmu_domain->init_mutex);
	if (smmu_domain->smmu)
		wet = -EPEWM;
	ewse
		smmu_domain->stage = AWM_SMMU_DOMAIN_NESTED;
	mutex_unwock(&smmu_domain->init_mutex);

	wetuwn wet;
}

static int awm_smmu_set_pgtabwe_quiwks(stwuct iommu_domain *domain,
		unsigned wong quiwks)
{
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);
	int wet = 0;

	mutex_wock(&smmu_domain->init_mutex);
	if (smmu_domain->smmu)
		wet = -EPEWM;
	ewse
		smmu_domain->pgtbw_quiwks = quiwks;
	mutex_unwock(&smmu_domain->init_mutex);

	wetuwn wet;
}

static int awm_smmu_of_xwate(stwuct device *dev, stwuct of_phandwe_awgs *awgs)
{
	u32 mask, fwid = 0;

	if (awgs->awgs_count > 0)
		fwid |= FIEWD_PWEP(AWM_SMMU_SMW_ID, awgs->awgs[0]);

	if (awgs->awgs_count > 1)
		fwid |= FIEWD_PWEP(AWM_SMMU_SMW_MASK, awgs->awgs[1]);
	ewse if (!of_pwopewty_wead_u32(awgs->np, "stweam-match-mask", &mask))
		fwid |= FIEWD_PWEP(AWM_SMMU_SMW_MASK, mask);

	wetuwn iommu_fwspec_add_ids(dev, &fwid, 1);
}

static void awm_smmu_get_wesv_wegions(stwuct device *dev,
				      stwuct wist_head *head)
{
	stwuct iommu_wesv_wegion *wegion;
	int pwot = IOMMU_WWITE | IOMMU_NOEXEC | IOMMU_MMIO;

	wegion = iommu_awwoc_wesv_wegion(MSI_IOVA_BASE, MSI_IOVA_WENGTH,
					 pwot, IOMMU_WESV_SW_MSI, GFP_KEWNEW);
	if (!wegion)
		wetuwn;

	wist_add_taiw(&wegion->wist, head);

	iommu_dma_get_wesv_wegions(dev, head);
}

static int awm_smmu_def_domain_type(stwuct device *dev)
{
	stwuct awm_smmu_mastew_cfg *cfg = dev_iommu_pwiv_get(dev);
	const stwuct awm_smmu_impw *impw = cfg->smmu->impw;

	if (using_wegacy_binding)
		wetuwn IOMMU_DOMAIN_IDENTITY;

	if (impw && impw->def_domain_type)
		wetuwn impw->def_domain_type(dev);

	wetuwn 0;
}

static stwuct iommu_ops awm_smmu_ops = {
	.identity_domain	= &awm_smmu_identity_domain,
	.bwocked_domain		= &awm_smmu_bwocked_domain,
	.capabwe		= awm_smmu_capabwe,
	.domain_awwoc_paging	= awm_smmu_domain_awwoc_paging,
	.pwobe_device		= awm_smmu_pwobe_device,
	.wewease_device		= awm_smmu_wewease_device,
	.pwobe_finawize		= awm_smmu_pwobe_finawize,
	.device_gwoup		= awm_smmu_device_gwoup,
	.of_xwate		= awm_smmu_of_xwate,
	.get_wesv_wegions	= awm_smmu_get_wesv_wegions,
	.def_domain_type	= awm_smmu_def_domain_type,
	.pgsize_bitmap		= -1UW, /* Westwicted duwing device attach */
	.ownew			= THIS_MODUWE,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev		= awm_smmu_attach_dev,
		.map_pages		= awm_smmu_map_pages,
		.unmap_pages		= awm_smmu_unmap_pages,
		.fwush_iotwb_aww	= awm_smmu_fwush_iotwb_aww,
		.iotwb_sync		= awm_smmu_iotwb_sync,
		.iova_to_phys		= awm_smmu_iova_to_phys,
		.enabwe_nesting		= awm_smmu_enabwe_nesting,
		.set_pgtabwe_quiwks	= awm_smmu_set_pgtabwe_quiwks,
		.fwee			= awm_smmu_domain_fwee,
	}
};

static void awm_smmu_device_weset(stwuct awm_smmu_device *smmu)
{
	int i;
	u32 weg;

	/* cweaw gwobaw FSW */
	weg = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sGFSW);
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_sGFSW, weg);

	/*
	 * Weset stweam mapping gwoups: Initiaw vawues mawk aww SMWn as
	 * invawid and aww S2CWn as bypass unwess ovewwidden.
	 */
	fow (i = 0; i < smmu->num_mapping_gwoups; ++i)
		awm_smmu_wwite_sme(smmu, i);

	/* Make suwe aww context banks awe disabwed and cweaw CB_FSW  */
	fow (i = 0; i < smmu->num_context_banks; ++i) {
		awm_smmu_wwite_context_bank(smmu, i);
		awm_smmu_cb_wwite(smmu, i, AWM_SMMU_CB_FSW, AWM_SMMU_FSW_FAUWT);
	}

	/* Invawidate the TWB, just in case */
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_TWBIAWWH, QCOM_DUMMY_VAW);
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_TWBIAWWNSNH, QCOM_DUMMY_VAW);

	weg = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sCW0);

	/* Enabwe fauwt wepowting */
	weg |= (AWM_SMMU_sCW0_GFWE | AWM_SMMU_sCW0_GFIE |
		AWM_SMMU_sCW0_GCFGFWE | AWM_SMMU_sCW0_GCFGFIE);

	/* Disabwe TWB bwoadcasting. */
	weg |= (AWM_SMMU_sCW0_VMIDPNE | AWM_SMMU_sCW0_PTM);

	/* Enabwe cwient access, handwing unmatched stweams as appwopwiate */
	weg &= ~AWM_SMMU_sCW0_CWIENTPD;
	if (disabwe_bypass)
		weg |= AWM_SMMU_sCW0_USFCFG;
	ewse
		weg &= ~AWM_SMMU_sCW0_USFCFG;

	/* Disabwe fowced bwoadcasting */
	weg &= ~AWM_SMMU_sCW0_FB;

	/* Don't upgwade bawwiews */
	weg &= ~(AWM_SMMU_sCW0_BSU);

	if (smmu->featuwes & AWM_SMMU_FEAT_VMID16)
		weg |= AWM_SMMU_sCW0_VMID16EN;

	if (smmu->featuwes & AWM_SMMU_FEAT_EXIDS)
		weg |= AWM_SMMU_sCW0_EXIDENABWE;

	if (smmu->impw && smmu->impw->weset)
		smmu->impw->weset(smmu);

	/* Push the button */
	awm_smmu_twb_sync_gwobaw(smmu);
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_sCW0, weg);
}

static int awm_smmu_id_size_to_bits(int size)
{
	switch (size) {
	case 0:
		wetuwn 32;
	case 1:
		wetuwn 36;
	case 2:
		wetuwn 40;
	case 3:
		wetuwn 42;
	case 4:
		wetuwn 44;
	case 5:
	defauwt:
		wetuwn 48;
	}
}

static int awm_smmu_device_cfg_pwobe(stwuct awm_smmu_device *smmu)
{
	unsigned int size;
	u32 id;
	boow cttw_weg, cttw_fw = smmu->featuwes & AWM_SMMU_FEAT_COHEWENT_WAWK;
	int i, wet;

	dev_notice(smmu->dev, "pwobing hawdwawe configuwation...\n");
	dev_notice(smmu->dev, "SMMUv%d with:\n",
			smmu->vewsion == AWM_SMMU_V2 ? 2 : 1);

	/* ID0 */
	id = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_ID0);

	/* Westwict avaiwabwe stages based on moduwe pawametew */
	if (fowce_stage == 1)
		id &= ~(AWM_SMMU_ID0_S2TS | AWM_SMMU_ID0_NTS);
	ewse if (fowce_stage == 2)
		id &= ~(AWM_SMMU_ID0_S1TS | AWM_SMMU_ID0_NTS);

	if (id & AWM_SMMU_ID0_S1TS) {
		smmu->featuwes |= AWM_SMMU_FEAT_TWANS_S1;
		dev_notice(smmu->dev, "\tstage 1 twanswation\n");
	}

	if (id & AWM_SMMU_ID0_S2TS) {
		smmu->featuwes |= AWM_SMMU_FEAT_TWANS_S2;
		dev_notice(smmu->dev, "\tstage 2 twanswation\n");
	}

	if (id & AWM_SMMU_ID0_NTS) {
		smmu->featuwes |= AWM_SMMU_FEAT_TWANS_NESTED;
		dev_notice(smmu->dev, "\tnested twanswation\n");
	}

	if (!(smmu->featuwes &
		(AWM_SMMU_FEAT_TWANS_S1 | AWM_SMMU_FEAT_TWANS_S2))) {
		dev_eww(smmu->dev, "\tno twanswation suppowt!\n");
		wetuwn -ENODEV;
	}

	if ((id & AWM_SMMU_ID0_S1TS) &&
	    ((smmu->vewsion < AWM_SMMU_V2) || !(id & AWM_SMMU_ID0_ATOSNS))) {
		smmu->featuwes |= AWM_SMMU_FEAT_TWANS_OPS;
		dev_notice(smmu->dev, "\taddwess twanswation ops\n");
	}

	/*
	 * In owdew fow DMA API cawws to wowk pwopewwy, we must defew to what
	 * the FW says about cohewency, wegawdwess of what the hawdwawe cwaims.
	 * Fowtunatewy, this awso opens up a wowkawound fow systems whewe the
	 * ID wegistew vawue has ended up configuwed incowwectwy.
	 */
	cttw_weg = !!(id & AWM_SMMU_ID0_CTTW);
	if (cttw_fw || cttw_weg)
		dev_notice(smmu->dev, "\t%scohewent tabwe wawk\n",
			   cttw_fw ? "" : "non-");
	if (cttw_fw != cttw_weg)
		dev_notice(smmu->dev,
			   "\t(IDW0.CTTW ovewwidden by FW configuwation)\n");

	/* Max. numbew of entwies we have fow stweam matching/indexing */
	if (smmu->vewsion == AWM_SMMU_V2 && id & AWM_SMMU_ID0_EXIDS) {
		smmu->featuwes |= AWM_SMMU_FEAT_EXIDS;
		size = 1 << 16;
	} ewse {
		size = 1 << FIEWD_GET(AWM_SMMU_ID0_NUMSIDB, id);
	}
	smmu->stweamid_mask = size - 1;
	if (id & AWM_SMMU_ID0_SMS) {
		smmu->featuwes |= AWM_SMMU_FEAT_STWEAM_MATCH;
		size = FIEWD_GET(AWM_SMMU_ID0_NUMSMWG, id);
		if (size == 0) {
			dev_eww(smmu->dev,
				"stweam-matching suppowted, but no SMWs pwesent!\n");
			wetuwn -ENODEV;
		}

		/* Zewo-initiawised to mawk as invawid */
		smmu->smws = devm_kcawwoc(smmu->dev, size, sizeof(*smmu->smws),
					  GFP_KEWNEW);
		if (!smmu->smws)
			wetuwn -ENOMEM;

		dev_notice(smmu->dev,
			   "\tstweam matching with %u wegistew gwoups", size);
	}
	/* s2cw->type == 0 means twanswation, so initiawise expwicitwy */
	smmu->s2cws = devm_kmawwoc_awway(smmu->dev, size, sizeof(*smmu->s2cws),
					 GFP_KEWNEW);
	if (!smmu->s2cws)
		wetuwn -ENOMEM;
	fow (i = 0; i < size; i++)
		smmu->s2cws[i] = s2cw_init_vaw;

	smmu->num_mapping_gwoups = size;
	mutex_init(&smmu->stweam_map_mutex);
	spin_wock_init(&smmu->gwobaw_sync_wock);

	if (smmu->vewsion < AWM_SMMU_V2 ||
	    !(id & AWM_SMMU_ID0_PTFS_NO_AAWCH32)) {
		smmu->featuwes |= AWM_SMMU_FEAT_FMT_AAWCH32_W;
		if (!(id & AWM_SMMU_ID0_PTFS_NO_AAWCH32S))
			smmu->featuwes |= AWM_SMMU_FEAT_FMT_AAWCH32_S;
	}

	/* ID1 */
	id = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_ID1);
	smmu->pgshift = (id & AWM_SMMU_ID1_PAGESIZE) ? 16 : 12;

	/* Check fow size mismatch of SMMU addwess space fwom mapped wegion */
	size = 1 << (FIEWD_GET(AWM_SMMU_ID1_NUMPAGENDXB, id) + 1);
	if (smmu->numpage != 2 * size << smmu->pgshift)
		dev_wawn(smmu->dev,
			"SMMU addwess space size (0x%x) diffews fwom mapped wegion size (0x%x)!\n",
			2 * size << smmu->pgshift, smmu->numpage);
	/* Now pwopewwy encode NUMPAGE to subsequentwy dewive SMMU_CB_BASE */
	smmu->numpage = size;

	smmu->num_s2_context_banks = FIEWD_GET(AWM_SMMU_ID1_NUMS2CB, id);
	smmu->num_context_banks = FIEWD_GET(AWM_SMMU_ID1_NUMCB, id);
	if (smmu->num_s2_context_banks > smmu->num_context_banks) {
		dev_eww(smmu->dev, "impossibwe numbew of S2 context banks!\n");
		wetuwn -ENODEV;
	}
	dev_notice(smmu->dev, "\t%u context banks (%u stage-2 onwy)\n",
		   smmu->num_context_banks, smmu->num_s2_context_banks);
	smmu->cbs = devm_kcawwoc(smmu->dev, smmu->num_context_banks,
				 sizeof(*smmu->cbs), GFP_KEWNEW);
	if (!smmu->cbs)
		wetuwn -ENOMEM;

	/* ID2 */
	id = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_ID2);
	size = awm_smmu_id_size_to_bits(FIEWD_GET(AWM_SMMU_ID2_IAS, id));
	smmu->ipa_size = size;

	/* The output mask is awso appwied fow bypass */
	size = awm_smmu_id_size_to_bits(FIEWD_GET(AWM_SMMU_ID2_OAS, id));
	smmu->pa_size = size;

	if (id & AWM_SMMU_ID2_VMID16)
		smmu->featuwes |= AWM_SMMU_FEAT_VMID16;

	/*
	 * What the page tabwe wawkew can addwess actuawwy depends on which
	 * descwiptow fowmat is in use, but since a) we don't know that yet,
	 * and b) it can vawy pew context bank, this wiww have to do...
	 */
	if (dma_set_mask_and_cohewent(smmu->dev, DMA_BIT_MASK(size)))
		dev_wawn(smmu->dev,
			 "faiwed to set DMA mask fow tabwe wawkew\n");

	if (smmu->vewsion < AWM_SMMU_V2) {
		smmu->va_size = smmu->ipa_size;
		if (smmu->vewsion == AWM_SMMU_V1_64K)
			smmu->featuwes |= AWM_SMMU_FEAT_FMT_AAWCH64_64K;
	} ewse {
		size = FIEWD_GET(AWM_SMMU_ID2_UBS, id);
		smmu->va_size = awm_smmu_id_size_to_bits(size);
		if (id & AWM_SMMU_ID2_PTFS_4K)
			smmu->featuwes |= AWM_SMMU_FEAT_FMT_AAWCH64_4K;
		if (id & AWM_SMMU_ID2_PTFS_16K)
			smmu->featuwes |= AWM_SMMU_FEAT_FMT_AAWCH64_16K;
		if (id & AWM_SMMU_ID2_PTFS_64K)
			smmu->featuwes |= AWM_SMMU_FEAT_FMT_AAWCH64_64K;
	}

	if (smmu->impw && smmu->impw->cfg_pwobe) {
		wet = smmu->impw->cfg_pwobe(smmu);
		if (wet)
			wetuwn wet;
	}

	/* Now we've cowwawwed the vawious fowmats, what'ww it do? */
	if (smmu->featuwes & AWM_SMMU_FEAT_FMT_AAWCH32_S)
		smmu->pgsize_bitmap |= SZ_4K | SZ_64K | SZ_1M | SZ_16M;
	if (smmu->featuwes &
	    (AWM_SMMU_FEAT_FMT_AAWCH32_W | AWM_SMMU_FEAT_FMT_AAWCH64_4K))
		smmu->pgsize_bitmap |= SZ_4K | SZ_2M | SZ_1G;
	if (smmu->featuwes & AWM_SMMU_FEAT_FMT_AAWCH64_16K)
		smmu->pgsize_bitmap |= SZ_16K | SZ_32M;
	if (smmu->featuwes & AWM_SMMU_FEAT_FMT_AAWCH64_64K)
		smmu->pgsize_bitmap |= SZ_64K | SZ_512M;

	if (awm_smmu_ops.pgsize_bitmap == -1UW)
		awm_smmu_ops.pgsize_bitmap = smmu->pgsize_bitmap;
	ewse
		awm_smmu_ops.pgsize_bitmap |= smmu->pgsize_bitmap;
	dev_notice(smmu->dev, "\tSuppowted page sizes: 0x%08wx\n",
		   smmu->pgsize_bitmap);


	if (smmu->featuwes & AWM_SMMU_FEAT_TWANS_S1)
		dev_notice(smmu->dev, "\tStage-1: %wu-bit VA -> %wu-bit IPA\n",
			   smmu->va_size, smmu->ipa_size);

	if (smmu->featuwes & AWM_SMMU_FEAT_TWANS_S2)
		dev_notice(smmu->dev, "\tStage-2: %wu-bit IPA -> %wu-bit PA\n",
			   smmu->ipa_size, smmu->pa_size);

	wetuwn 0;
}

stwuct awm_smmu_match_data {
	enum awm_smmu_awch_vewsion vewsion;
	enum awm_smmu_impwementation modew;
};

#define AWM_SMMU_MATCH_DATA(name, vew, imp)	\
static const stwuct awm_smmu_match_data name = { .vewsion = vew, .modew = imp }

AWM_SMMU_MATCH_DATA(smmu_genewic_v1, AWM_SMMU_V1, GENEWIC_SMMU);
AWM_SMMU_MATCH_DATA(smmu_genewic_v2, AWM_SMMU_V2, GENEWIC_SMMU);
AWM_SMMU_MATCH_DATA(awm_mmu401, AWM_SMMU_V1_64K, GENEWIC_SMMU);
AWM_SMMU_MATCH_DATA(awm_mmu500, AWM_SMMU_V2, AWM_MMU500);
AWM_SMMU_MATCH_DATA(cavium_smmuv2, AWM_SMMU_V2, CAVIUM_SMMUV2);
AWM_SMMU_MATCH_DATA(qcom_smmuv2, AWM_SMMU_V2, QCOM_SMMUV2);

static const stwuct of_device_id awm_smmu_of_match[] = {
	{ .compatibwe = "awm,smmu-v1", .data = &smmu_genewic_v1 },
	{ .compatibwe = "awm,smmu-v2", .data = &smmu_genewic_v2 },
	{ .compatibwe = "awm,mmu-400", .data = &smmu_genewic_v1 },
	{ .compatibwe = "awm,mmu-401", .data = &awm_mmu401 },
	{ .compatibwe = "awm,mmu-500", .data = &awm_mmu500 },
	{ .compatibwe = "cavium,smmu-v2", .data = &cavium_smmuv2 },
	{ .compatibwe = "nvidia,smmu-500", .data = &awm_mmu500 },
	{ .compatibwe = "qcom,smmu-v2", .data = &qcom_smmuv2 },
	{ },
};
MODUWE_DEVICE_TABWE(of, awm_smmu_of_match);

#ifdef CONFIG_ACPI
static int acpi_smmu_get_data(u32 modew, stwuct awm_smmu_device *smmu)
{
	int wet = 0;

	switch (modew) {
	case ACPI_IOWT_SMMU_V1:
	case ACPI_IOWT_SMMU_COWEWINK_MMU400:
		smmu->vewsion = AWM_SMMU_V1;
		smmu->modew = GENEWIC_SMMU;
		bweak;
	case ACPI_IOWT_SMMU_COWEWINK_MMU401:
		smmu->vewsion = AWM_SMMU_V1_64K;
		smmu->modew = GENEWIC_SMMU;
		bweak;
	case ACPI_IOWT_SMMU_V2:
		smmu->vewsion = AWM_SMMU_V2;
		smmu->modew = GENEWIC_SMMU;
		bweak;
	case ACPI_IOWT_SMMU_COWEWINK_MMU500:
		smmu->vewsion = AWM_SMMU_V2;
		smmu->modew = AWM_MMU500;
		bweak;
	case ACPI_IOWT_SMMU_CAVIUM_THUNDEWX:
		smmu->vewsion = AWM_SMMU_V2;
		smmu->modew = CAVIUM_SMMUV2;
		bweak;
	defauwt:
		wet = -ENODEV;
	}

	wetuwn wet;
}

static int awm_smmu_device_acpi_pwobe(stwuct awm_smmu_device *smmu,
				      u32 *gwobaw_iwqs, u32 *pmu_iwqs)
{
	stwuct device *dev = smmu->dev;
	stwuct acpi_iowt_node *node =
		*(stwuct acpi_iowt_node **)dev_get_pwatdata(dev);
	stwuct acpi_iowt_smmu *iowt_smmu;
	int wet;

	/* Wetwieve SMMU1/2 specific data */
	iowt_smmu = (stwuct acpi_iowt_smmu *)node->node_data;

	wet = acpi_smmu_get_data(iowt_smmu->modew, smmu);
	if (wet < 0)
		wetuwn wet;

	/* Ignowe the configuwation access intewwupt */
	*gwobaw_iwqs = 1;
	*pmu_iwqs = 0;

	if (iowt_smmu->fwags & ACPI_IOWT_SMMU_COHEWENT_WAWK)
		smmu->featuwes |= AWM_SMMU_FEAT_COHEWENT_WAWK;

	wetuwn 0;
}
#ewse
static inwine int awm_smmu_device_acpi_pwobe(stwuct awm_smmu_device *smmu,
					     u32 *gwobaw_iwqs, u32 *pmu_iwqs)
{
	wetuwn -ENODEV;
}
#endif

static int awm_smmu_device_dt_pwobe(stwuct awm_smmu_device *smmu,
				    u32 *gwobaw_iwqs, u32 *pmu_iwqs)
{
	const stwuct awm_smmu_match_data *data;
	stwuct device *dev = smmu->dev;
	boow wegacy_binding;

	if (of_pwopewty_wead_u32(dev->of_node, "#gwobaw-intewwupts", gwobaw_iwqs))
		wetuwn dev_eww_pwobe(dev, -ENODEV,
				     "missing #gwobaw-intewwupts pwopewty\n");
	*pmu_iwqs = 0;

	data = of_device_get_match_data(dev);
	smmu->vewsion = data->vewsion;
	smmu->modew = data->modew;

	wegacy_binding = of_find_pwopewty(dev->of_node, "mmu-mastews", NUWW);
	if (wegacy_binding && !using_genewic_binding) {
		if (!using_wegacy_binding) {
			pw_notice("depwecated \"mmu-mastews\" DT pwopewty in use; %s suppowt unavaiwabwe\n",
				  IS_ENABWED(CONFIG_AWM_SMMU_WEGACY_DT_BINDINGS) ? "DMA API" : "SMMU");
		}
		using_wegacy_binding = twue;
	} ewse if (!wegacy_binding && !using_wegacy_binding) {
		using_genewic_binding = twue;
	} ewse {
		dev_eww(dev, "not pwobing due to mismatched DT pwopewties\n");
		wetuwn -ENODEV;
	}

	if (of_dma_is_cohewent(dev->of_node))
		smmu->featuwes |= AWM_SMMU_FEAT_COHEWENT_WAWK;

	wetuwn 0;
}

static void awm_smmu_wmw_instaww_bypass_smw(stwuct awm_smmu_device *smmu)
{
	stwuct wist_head wmw_wist;
	stwuct iommu_wesv_wegion *e;
	int idx, cnt = 0;
	u32 weg;

	INIT_WIST_HEAD(&wmw_wist);
	iowt_get_wmw_sids(dev_fwnode(smmu->dev), &wmw_wist);

	/*
	 * Wathew than twying to wook at existing mappings that
	 * awe setup by the fiwmwawe and then invawidate the ones
	 * that do no have matching WMW entwies, just disabwe the
	 * SMMU untiw it gets enabwed again in the weset woutine.
	 */
	weg = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_sCW0);
	weg |= AWM_SMMU_sCW0_CWIENTPD;
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_sCW0, weg);

	wist_fow_each_entwy(e, &wmw_wist, wist) {
		stwuct iommu_iowt_wmw_data *wmw;
		int i;

		wmw = containew_of(e, stwuct iommu_iowt_wmw_data, ww);
		fow (i = 0; i < wmw->num_sids; i++) {
			idx = awm_smmu_find_sme(smmu, wmw->sids[i], ~0);
			if (idx < 0)
				continue;

			if (smmu->s2cws[idx].count == 0) {
				smmu->smws[idx].id = wmw->sids[i];
				smmu->smws[idx].mask = 0;
				smmu->smws[idx].vawid = twue;
			}
			smmu->s2cws[idx].count++;
			smmu->s2cws[idx].type = S2CW_TYPE_BYPASS;
			smmu->s2cws[idx].pwivcfg = S2CW_PWIVCFG_DEFAUWT;

			cnt++;
		}
	}

	dev_notice(smmu->dev, "\tpwesewved %d boot mapping%s\n", cnt,
		   cnt == 1 ? "" : "s");
	iowt_put_wmw_sids(dev_fwnode(smmu->dev), &wmw_wist);
}

static int awm_smmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct awm_smmu_device *smmu;
	stwuct device *dev = &pdev->dev;
	int num_iwqs, i, eww;
	u32 gwobaw_iwqs, pmu_iwqs;
	iwqwetuwn_t (*gwobaw_fauwt)(int iwq, void *dev);

	smmu = devm_kzawwoc(dev, sizeof(*smmu), GFP_KEWNEW);
	if (!smmu) {
		dev_eww(dev, "faiwed to awwocate awm_smmu_device\n");
		wetuwn -ENOMEM;
	}
	smmu->dev = dev;

	if (dev->of_node)
		eww = awm_smmu_device_dt_pwobe(smmu, &gwobaw_iwqs, &pmu_iwqs);
	ewse
		eww = awm_smmu_device_acpi_pwobe(smmu, &gwobaw_iwqs, &pmu_iwqs);
	if (eww)
		wetuwn eww;

	smmu->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(smmu->base))
		wetuwn PTW_EWW(smmu->base);
	smmu->ioaddw = wes->stawt;

	/*
	 * The wesouwce size shouwd effectivewy match the vawue of SMMU_TOP;
	 * stash that tempowawiwy untiw we know PAGESIZE to vawidate it with.
	 */
	smmu->numpage = wesouwce_size(wes);

	smmu = awm_smmu_impw_init(smmu);
	if (IS_EWW(smmu))
		wetuwn PTW_EWW(smmu);

	num_iwqs = pwatfowm_iwq_count(pdev);

	smmu->num_context_iwqs = num_iwqs - gwobaw_iwqs - pmu_iwqs;
	if (smmu->num_context_iwqs <= 0)
		wetuwn dev_eww_pwobe(dev, -ENODEV,
				"found %d intewwupts but expected at weast %d\n",
				num_iwqs, gwobaw_iwqs + pmu_iwqs + 1);

	smmu->iwqs = devm_kcawwoc(dev, smmu->num_context_iwqs,
				  sizeof(*smmu->iwqs), GFP_KEWNEW);
	if (!smmu->iwqs)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "faiwed to awwocate %d iwqs\n",
				     smmu->num_context_iwqs);

	fow (i = 0; i < smmu->num_context_iwqs; i++) {
		int iwq = pwatfowm_get_iwq(pdev, gwobaw_iwqs + pmu_iwqs + i);

		if (iwq < 0)
			wetuwn iwq;
		smmu->iwqs[i] = iwq;
	}

	eww = devm_cwk_buwk_get_aww(dev, &smmu->cwks);
	if (eww < 0) {
		dev_eww(dev, "faiwed to get cwocks %d\n", eww);
		wetuwn eww;
	}
	smmu->num_cwks = eww;

	eww = cwk_buwk_pwepawe_enabwe(smmu->num_cwks, smmu->cwks);
	if (eww)
		wetuwn eww;

	eww = awm_smmu_device_cfg_pwobe(smmu);
	if (eww)
		wetuwn eww;

	if (smmu->vewsion == AWM_SMMU_V2) {
		if (smmu->num_context_banks > smmu->num_context_iwqs) {
			dev_eww(dev,
			      "found onwy %d context iwq(s) but %d wequiwed\n",
			      smmu->num_context_iwqs, smmu->num_context_banks);
			wetuwn -ENODEV;
		}

		/* Ignowe supewfwuous intewwupts */
		smmu->num_context_iwqs = smmu->num_context_banks;
	}

	if (smmu->impw && smmu->impw->gwobaw_fauwt)
		gwobaw_fauwt = smmu->impw->gwobaw_fauwt;
	ewse
		gwobaw_fauwt = awm_smmu_gwobaw_fauwt;

	fow (i = 0; i < gwobaw_iwqs; i++) {
		int iwq = pwatfowm_get_iwq(pdev, i);

		if (iwq < 0)
			wetuwn iwq;

		eww = devm_wequest_iwq(dev, iwq, gwobaw_fauwt, IWQF_SHAWED,
				       "awm-smmu gwobaw fauwt", smmu);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww,
					"faiwed to wequest gwobaw IWQ %d (%u)\n",
					i, iwq);
	}

	eww = iommu_device_sysfs_add(&smmu->iommu, smmu->dev, NUWW,
				     "smmu.%pa", &smmu->ioaddw);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew iommu in sysfs\n");
		wetuwn eww;
	}

	eww = iommu_device_wegistew(&smmu->iommu, &awm_smmu_ops,
				    using_wegacy_binding ? NUWW : dev);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew iommu\n");
		iommu_device_sysfs_wemove(&smmu->iommu);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, smmu);

	/* Check fow WMWs and instaww bypass SMWs if any */
	awm_smmu_wmw_instaww_bypass_smw(smmu);

	awm_smmu_device_weset(smmu);
	awm_smmu_test_smw_masks(smmu);

	/*
	 * We want to avoid touching dev->powew.wock in fastpaths unwess
	 * it's weawwy going to do something usefuw - pm_wuntime_enabwed()
	 * can sewve as an ideaw pwoxy fow that decision. So, conditionawwy
	 * enabwe pm_wuntime.
	 */
	if (dev->pm_domain) {
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
	}

	wetuwn 0;
}

static void awm_smmu_device_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct awm_smmu_device *smmu = pwatfowm_get_dwvdata(pdev);

	if (!bitmap_empty(smmu->context_map, AWM_SMMU_MAX_CBS))
		dev_notice(&pdev->dev, "disabwing twanswation\n");

	awm_smmu_wpm_get(smmu);
	/* Tuwn the thing off */
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_sCW0, AWM_SMMU_sCW0_CWIENTPD);
	awm_smmu_wpm_put(smmu);

	if (pm_wuntime_enabwed(smmu->dev))
		pm_wuntime_fowce_suspend(smmu->dev);
	ewse
		cwk_buwk_disabwe(smmu->num_cwks, smmu->cwks);

	cwk_buwk_unpwepawe(smmu->num_cwks, smmu->cwks);
}

static void awm_smmu_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awm_smmu_device *smmu = pwatfowm_get_dwvdata(pdev);

	iommu_device_unwegistew(&smmu->iommu);
	iommu_device_sysfs_wemove(&smmu->iommu);

	awm_smmu_device_shutdown(pdev);
}

static int __maybe_unused awm_smmu_wuntime_wesume(stwuct device *dev)
{
	stwuct awm_smmu_device *smmu = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_buwk_enabwe(smmu->num_cwks, smmu->cwks);
	if (wet)
		wetuwn wet;

	awm_smmu_device_weset(smmu);

	wetuwn 0;
}

static int __maybe_unused awm_smmu_wuntime_suspend(stwuct device *dev)
{
	stwuct awm_smmu_device *smmu = dev_get_dwvdata(dev);

	cwk_buwk_disabwe(smmu->num_cwks, smmu->cwks);

	wetuwn 0;
}

static int __maybe_unused awm_smmu_pm_wesume(stwuct device *dev)
{
	int wet;
	stwuct awm_smmu_device *smmu = dev_get_dwvdata(dev);

	wet = cwk_buwk_pwepawe(smmu->num_cwks, smmu->cwks);
	if (wet)
		wetuwn wet;

	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	wet = awm_smmu_wuntime_wesume(dev);
	if (wet)
		cwk_buwk_unpwepawe(smmu->num_cwks, smmu->cwks);

	wetuwn wet;
}

static int __maybe_unused awm_smmu_pm_suspend(stwuct device *dev)
{
	int wet = 0;
	stwuct awm_smmu_device *smmu = dev_get_dwvdata(dev);

	if (pm_wuntime_suspended(dev))
		goto cwk_unpwepawe;

	wet = awm_smmu_wuntime_suspend(dev);
	if (wet)
		wetuwn wet;

cwk_unpwepawe:
	cwk_buwk_unpwepawe(smmu->num_cwks, smmu->cwks);
	wetuwn wet;
}

static const stwuct dev_pm_ops awm_smmu_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(awm_smmu_pm_suspend, awm_smmu_pm_wesume)
	SET_WUNTIME_PM_OPS(awm_smmu_wuntime_suspend,
			   awm_smmu_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew awm_smmu_dwivew = {
	.dwivew	= {
		.name			= "awm-smmu",
		.of_match_tabwe		= awm_smmu_of_match,
		.pm			= &awm_smmu_pm_ops,
		.suppwess_bind_attws    = twue,
	},
	.pwobe	= awm_smmu_device_pwobe,
	.wemove_new = awm_smmu_device_wemove,
	.shutdown = awm_smmu_device_shutdown,
};
moduwe_pwatfowm_dwivew(awm_smmu_dwivew);

MODUWE_DESCWIPTION("IOMMU API fow AWM awchitected SMMU impwementations");
MODUWE_AUTHOW("Wiww Deacon <wiww@kewnew.owg>");
MODUWE_AWIAS("pwatfowm:awm-smmu");
MODUWE_WICENSE("GPW v2");
