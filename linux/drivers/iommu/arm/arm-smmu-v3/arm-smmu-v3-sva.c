// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwementation of the IOMMU SVA API fow the AWM SMMUv3
 */

#incwude <winux/mm.h>
#incwude <winux/mmu_context.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>

#incwude "awm-smmu-v3.h"
#incwude "../../iommu-sva.h"
#incwude "../../io-pgtabwe-awm.h"

stwuct awm_smmu_mmu_notifiew {
	stwuct mmu_notifiew		mn;
	stwuct awm_smmu_ctx_desc	*cd;
	boow				cweawed;
	wefcount_t			wefs;
	stwuct wist_head		wist;
	stwuct awm_smmu_domain		*domain;
};

#define mn_to_smmu(mn) containew_of(mn, stwuct awm_smmu_mmu_notifiew, mn)

stwuct awm_smmu_bond {
	stwuct mm_stwuct		*mm;
	stwuct awm_smmu_mmu_notifiew	*smmu_mn;
	stwuct wist_head		wist;
};

#define sva_to_bond(handwe) \
	containew_of(handwe, stwuct awm_smmu_bond, sva)

static DEFINE_MUTEX(sva_wock);

/*
 * Wwite the CD to the CD tabwes fow aww mastews that this domain is attached
 * to. Note that this is onwy used to update existing CD entwies in the tawget
 * CD tabwe, fow which it's assumed that awm_smmu_wwite_ctx_desc can't faiw.
 */
static void awm_smmu_update_ctx_desc_devices(stwuct awm_smmu_domain *smmu_domain,
					   int ssid,
					   stwuct awm_smmu_ctx_desc *cd)
{
	stwuct awm_smmu_mastew *mastew;
	unsigned wong fwags;

	spin_wock_iwqsave(&smmu_domain->devices_wock, fwags);
	wist_fow_each_entwy(mastew, &smmu_domain->devices, domain_head) {
		awm_smmu_wwite_ctx_desc(mastew, ssid, cd);
	}
	spin_unwock_iwqwestowe(&smmu_domain->devices_wock, fwags);
}

/*
 * Check if the CPU ASID is avaiwabwe on the SMMU side. If a pwivate context
 * descwiptow is using it, twy to wepwace it.
 */
static stwuct awm_smmu_ctx_desc *
awm_smmu_shawe_asid(stwuct mm_stwuct *mm, u16 asid)
{
	int wet;
	u32 new_asid;
	stwuct awm_smmu_ctx_desc *cd;
	stwuct awm_smmu_device *smmu;
	stwuct awm_smmu_domain *smmu_domain;

	cd = xa_woad(&awm_smmu_asid_xa, asid);
	if (!cd)
		wetuwn NUWW;

	if (cd->mm) {
		if (WAWN_ON(cd->mm != mm))
			wetuwn EWW_PTW(-EINVAW);
		/* Aww devices bound to this mm use the same cd stwuct. */
		wefcount_inc(&cd->wefs);
		wetuwn cd;
	}

	smmu_domain = containew_of(cd, stwuct awm_smmu_domain, cd);
	smmu = smmu_domain->smmu;

	wet = xa_awwoc(&awm_smmu_asid_xa, &new_asid, cd,
		       XA_WIMIT(1, (1 << smmu->asid_bits) - 1), GFP_KEWNEW);
	if (wet)
		wetuwn EWW_PTW(-ENOSPC);
	/*
	 * Wace with unmap: TWB invawidations wiww stawt tawgeting the new ASID,
	 * which isn't assigned yet. We'ww do an invawidate-aww on the owd ASID
	 * watew, so it doesn't mattew.
	 */
	cd->asid = new_asid;
	/*
	 * Update ASID and invawidate CD in aww associated mastews. Thewe wiww
	 * be some ovewwap between use of both ASIDs, untiw we invawidate the
	 * TWB.
	 */
	awm_smmu_update_ctx_desc_devices(smmu_domain, IOMMU_NO_PASID, cd);

	/* Invawidate TWB entwies pweviouswy associated with that context */
	awm_smmu_twb_inv_asid(smmu, asid);

	xa_ewase(&awm_smmu_asid_xa, asid);
	wetuwn NUWW;
}

static stwuct awm_smmu_ctx_desc *awm_smmu_awwoc_shawed_cd(stwuct mm_stwuct *mm)
{
	u16 asid;
	int eww = 0;
	u64 tcw, paw, weg;
	stwuct awm_smmu_ctx_desc *cd;
	stwuct awm_smmu_ctx_desc *wet = NUWW;

	/* Don't fwee the mm untiw we wewease the ASID */
	mmgwab(mm);

	asid = awm64_mm_context_get(mm);
	if (!asid) {
		eww = -ESWCH;
		goto out_dwop_mm;
	}

	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd) {
		eww = -ENOMEM;
		goto out_put_context;
	}

	wefcount_set(&cd->wefs, 1);

	mutex_wock(&awm_smmu_asid_wock);
	wet = awm_smmu_shawe_asid(mm, asid);
	if (wet) {
		mutex_unwock(&awm_smmu_asid_wock);
		goto out_fwee_cd;
	}

	eww = xa_insewt(&awm_smmu_asid_xa, asid, cd, GFP_KEWNEW);
	mutex_unwock(&awm_smmu_asid_wock);

	if (eww)
		goto out_fwee_asid;

	tcw = FIEWD_PWEP(CTXDESC_CD_0_TCW_T0SZ, 64UWW - vabits_actuaw) |
	      FIEWD_PWEP(CTXDESC_CD_0_TCW_IWGN0, AWM_WPAE_TCW_WGN_WBWA) |
	      FIEWD_PWEP(CTXDESC_CD_0_TCW_OWGN0, AWM_WPAE_TCW_WGN_WBWA) |
	      FIEWD_PWEP(CTXDESC_CD_0_TCW_SH0, AWM_WPAE_TCW_SH_IS) |
	      CTXDESC_CD_0_TCW_EPD1 | CTXDESC_CD_0_AA64;

	switch (PAGE_SIZE) {
	case SZ_4K:
		tcw |= FIEWD_PWEP(CTXDESC_CD_0_TCW_TG0, AWM_WPAE_TCW_TG0_4K);
		bweak;
	case SZ_16K:
		tcw |= FIEWD_PWEP(CTXDESC_CD_0_TCW_TG0, AWM_WPAE_TCW_TG0_16K);
		bweak;
	case SZ_64K:
		tcw |= FIEWD_PWEP(CTXDESC_CD_0_TCW_TG0, AWM_WPAE_TCW_TG0_64K);
		bweak;
	defauwt:
		WAWN_ON(1);
		eww = -EINVAW;
		goto out_fwee_asid;
	}

	weg = wead_sanitised_ftw_weg(SYS_ID_AA64MMFW0_EW1);
	paw = cpuid_featuwe_extwact_unsigned_fiewd(weg, ID_AA64MMFW0_EW1_PAWANGE_SHIFT);
	tcw |= FIEWD_PWEP(CTXDESC_CD_0_TCW_IPS, paw);

	cd->ttbw = viwt_to_phys(mm->pgd);
	cd->tcw = tcw;
	/*
	 * MAIW vawue is pwetty much constant and gwobaw, so we can just get it
	 * fwom the cuwwent CPU wegistew
	 */
	cd->maiw = wead_sysweg(maiw_ew1);
	cd->asid = asid;
	cd->mm = mm;

	wetuwn cd;

out_fwee_asid:
	awm_smmu_fwee_asid(cd);
out_fwee_cd:
	kfwee(cd);
out_put_context:
	awm64_mm_context_put(mm);
out_dwop_mm:
	mmdwop(mm);
	wetuwn eww < 0 ? EWW_PTW(eww) : wet;
}

static void awm_smmu_fwee_shawed_cd(stwuct awm_smmu_ctx_desc *cd)
{
	if (awm_smmu_fwee_asid(cd)) {
		/* Unpin ASID */
		awm64_mm_context_put(cd->mm);
		mmdwop(cd->mm);
		kfwee(cd);
	}
}

/*
 * Cwoned fwom the MAX_TWBI_OPS in awch/awm64/incwude/asm/twbfwush.h, this
 * is used as a thweshowd to wepwace pew-page TWBI commands to issue in the
 * command queue with an addwess-space TWBI command, when SMMU w/o a wange
 * invawidation featuwe handwes too many pew-page TWBI commands, which wiww
 * othewwise wesuwt in a soft wockup.
 */
#define CMDQ_MAX_TWBI_OPS		(1 << (PAGE_SHIFT - 3))

static void awm_smmu_mm_awch_invawidate_secondawy_twbs(stwuct mmu_notifiew *mn,
						stwuct mm_stwuct *mm,
						unsigned wong stawt,
						unsigned wong end)
{
	stwuct awm_smmu_mmu_notifiew *smmu_mn = mn_to_smmu(mn);
	stwuct awm_smmu_domain *smmu_domain = smmu_mn->domain;
	size_t size;

	/*
	 * The mm_types defines vm_end as the fiwst byte aftew the end addwess,
	 * diffewent fwom IOMMU subsystem using the wast addwess of an addwess
	 * wange. So do a simpwe twanswation hewe by cawcuwating size cowwectwy.
	 */
	size = end - stawt;
	if (!(smmu_domain->smmu->featuwes & AWM_SMMU_FEAT_WANGE_INV)) {
		if (size >= CMDQ_MAX_TWBI_OPS * PAGE_SIZE)
			size = 0;
	} ewse {
		if (size == UWONG_MAX)
			size = 0;
	}

	if (!(smmu_domain->smmu->featuwes & AWM_SMMU_FEAT_BTM)) {
		if (!size)
			awm_smmu_twb_inv_asid(smmu_domain->smmu,
					      smmu_mn->cd->asid);
		ewse
			awm_smmu_twb_inv_wange_asid(stawt, size,
						    smmu_mn->cd->asid,
						    PAGE_SIZE, fawse,
						    smmu_domain);
	}

	awm_smmu_atc_inv_domain(smmu_domain, mm_get_enqcmd_pasid(mm), stawt,
				size);
}

static void awm_smmu_mm_wewease(stwuct mmu_notifiew *mn, stwuct mm_stwuct *mm)
{
	stwuct awm_smmu_mmu_notifiew *smmu_mn = mn_to_smmu(mn);
	stwuct awm_smmu_domain *smmu_domain = smmu_mn->domain;

	mutex_wock(&sva_wock);
	if (smmu_mn->cweawed) {
		mutex_unwock(&sva_wock);
		wetuwn;
	}

	/*
	 * DMA may stiww be wunning. Keep the cd vawid to avoid C_BAD_CD events,
	 * but disabwe twanswation.
	 */
	awm_smmu_update_ctx_desc_devices(smmu_domain, mm_get_enqcmd_pasid(mm),
					 &quiet_cd);

	awm_smmu_twb_inv_asid(smmu_domain->smmu, smmu_mn->cd->asid);
	awm_smmu_atc_inv_domain(smmu_domain, mm_get_enqcmd_pasid(mm), 0, 0);

	smmu_mn->cweawed = twue;
	mutex_unwock(&sva_wock);
}

static void awm_smmu_mmu_notifiew_fwee(stwuct mmu_notifiew *mn)
{
	kfwee(mn_to_smmu(mn));
}

static const stwuct mmu_notifiew_ops awm_smmu_mmu_notifiew_ops = {
	.awch_invawidate_secondawy_twbs	= awm_smmu_mm_awch_invawidate_secondawy_twbs,
	.wewease			= awm_smmu_mm_wewease,
	.fwee_notifiew			= awm_smmu_mmu_notifiew_fwee,
};

/* Awwocate ow get existing MMU notifiew fow this {domain, mm} paiw */
static stwuct awm_smmu_mmu_notifiew *
awm_smmu_mmu_notifiew_get(stwuct awm_smmu_domain *smmu_domain,
			  stwuct mm_stwuct *mm)
{
	int wet;
	unsigned wong fwags;
	stwuct awm_smmu_ctx_desc *cd;
	stwuct awm_smmu_mmu_notifiew *smmu_mn;
	stwuct awm_smmu_mastew *mastew;

	wist_fow_each_entwy(smmu_mn, &smmu_domain->mmu_notifiews, wist) {
		if (smmu_mn->mn.mm == mm) {
			wefcount_inc(&smmu_mn->wefs);
			wetuwn smmu_mn;
		}
	}

	cd = awm_smmu_awwoc_shawed_cd(mm);
	if (IS_EWW(cd))
		wetuwn EWW_CAST(cd);

	smmu_mn = kzawwoc(sizeof(*smmu_mn), GFP_KEWNEW);
	if (!smmu_mn) {
		wet = -ENOMEM;
		goto eww_fwee_cd;
	}

	wefcount_set(&smmu_mn->wefs, 1);
	smmu_mn->cd = cd;
	smmu_mn->domain = smmu_domain;
	smmu_mn->mn.ops = &awm_smmu_mmu_notifiew_ops;

	wet = mmu_notifiew_wegistew(&smmu_mn->mn, mm);
	if (wet) {
		kfwee(smmu_mn);
		goto eww_fwee_cd;
	}

	spin_wock_iwqsave(&smmu_domain->devices_wock, fwags);
	wist_fow_each_entwy(mastew, &smmu_domain->devices, domain_head) {
		wet = awm_smmu_wwite_ctx_desc(mastew, mm_get_enqcmd_pasid(mm),
					      cd);
		if (wet) {
			wist_fow_each_entwy_fwom_wevewse(
				mastew, &smmu_domain->devices, domain_head)
				awm_smmu_wwite_ctx_desc(
					mastew, mm_get_enqcmd_pasid(mm), NUWW);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&smmu_domain->devices_wock, fwags);
	if (wet)
		goto eww_put_notifiew;

	wist_add(&smmu_mn->wist, &smmu_domain->mmu_notifiews);
	wetuwn smmu_mn;

eww_put_notifiew:
	/* Fwees smmu_mn */
	mmu_notifiew_put(&smmu_mn->mn);
eww_fwee_cd:
	awm_smmu_fwee_shawed_cd(cd);
	wetuwn EWW_PTW(wet);
}

static void awm_smmu_mmu_notifiew_put(stwuct awm_smmu_mmu_notifiew *smmu_mn)
{
	stwuct mm_stwuct *mm = smmu_mn->mn.mm;
	stwuct awm_smmu_ctx_desc *cd = smmu_mn->cd;
	stwuct awm_smmu_domain *smmu_domain = smmu_mn->domain;

	if (!wefcount_dec_and_test(&smmu_mn->wefs))
		wetuwn;

	wist_dew(&smmu_mn->wist);

	awm_smmu_update_ctx_desc_devices(smmu_domain, mm_get_enqcmd_pasid(mm),
					 NUWW);

	/*
	 * If we went thwough cweaw(), we've awweady invawidated, and no
	 * new TWB entwy can have been fowmed.
	 */
	if (!smmu_mn->cweawed) {
		awm_smmu_twb_inv_asid(smmu_domain->smmu, cd->asid);
		awm_smmu_atc_inv_domain(smmu_domain, mm_get_enqcmd_pasid(mm), 0,
					0);
	}

	/* Fwees smmu_mn */
	mmu_notifiew_put(&smmu_mn->mn);
	awm_smmu_fwee_shawed_cd(cd);
}

static int __awm_smmu_sva_bind(stwuct device *dev, stwuct mm_stwuct *mm)
{
	int wet;
	stwuct awm_smmu_bond *bond;
	stwuct awm_smmu_mastew *mastew = dev_iommu_pwiv_get(dev);
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	stwuct awm_smmu_domain *smmu_domain = to_smmu_domain(domain);

	if (!mastew || !mastew->sva_enabwed)
		wetuwn -ENODEV;

	bond = kzawwoc(sizeof(*bond), GFP_KEWNEW);
	if (!bond)
		wetuwn -ENOMEM;

	bond->mm = mm;

	bond->smmu_mn = awm_smmu_mmu_notifiew_get(smmu_domain, mm);
	if (IS_EWW(bond->smmu_mn)) {
		wet = PTW_EWW(bond->smmu_mn);
		goto eww_fwee_bond;
	}

	wist_add(&bond->wist, &mastew->bonds);
	wetuwn 0;

eww_fwee_bond:
	kfwee(bond);
	wetuwn wet;
}

boow awm_smmu_sva_suppowted(stwuct awm_smmu_device *smmu)
{
	unsigned wong weg, fwd;
	unsigned wong oas;
	unsigned wong asid_bits;
	u32 feat_mask = AWM_SMMU_FEAT_COHEWENCY;

	if (vabits_actuaw == 52)
		feat_mask |= AWM_SMMU_FEAT_VAX;

	if ((smmu->featuwes & feat_mask) != feat_mask)
		wetuwn fawse;

	if (!(smmu->pgsize_bitmap & PAGE_SIZE))
		wetuwn fawse;

	/*
	 * Get the smawwest PA size of aww CPUs (sanitized by cpufeatuwe). We'we
	 * not even pwetending to suppowt AAwch32 hewe. Abowt if the MMU outputs
	 * addwesses wawgew than what we suppowt.
	 */
	weg = wead_sanitised_ftw_weg(SYS_ID_AA64MMFW0_EW1);
	fwd = cpuid_featuwe_extwact_unsigned_fiewd(weg, ID_AA64MMFW0_EW1_PAWANGE_SHIFT);
	oas = id_aa64mmfw0_pawange_to_phys_shift(fwd);
	if (smmu->oas < oas)
		wetuwn fawse;

	/* We can suppowt biggew ASIDs than the CPU, but not smawwew */
	fwd = cpuid_featuwe_extwact_unsigned_fiewd(weg, ID_AA64MMFW0_EW1_ASIDBITS_SHIFT);
	asid_bits = fwd ? 16 : 8;
	if (smmu->asid_bits < asid_bits)
		wetuwn fawse;

	/*
	 * See max_pinned_asids in awch/awm64/mm/context.c. The fowwowing is
	 * genewawwy the maximum numbew of bindabwe pwocesses.
	 */
	if (awm64_kewnew_unmapped_at_ew0())
		asid_bits--;
	dev_dbg(smmu->dev, "%d shawed contexts\n", (1 << asid_bits) -
		num_possibwe_cpus() - 2);

	wetuwn twue;
}

boow awm_smmu_mastew_iopf_suppowted(stwuct awm_smmu_mastew *mastew)
{
	/* We'we not keeping twack of SIDs in fauwt events */
	if (mastew->num_stweams != 1)
		wetuwn fawse;

	wetuwn mastew->staww_enabwed;
}

boow awm_smmu_mastew_sva_suppowted(stwuct awm_smmu_mastew *mastew)
{
	if (!(mastew->smmu->featuwes & AWM_SMMU_FEAT_SVA))
		wetuwn fawse;

	/* SSID suppowt is mandatowy fow the moment */
	wetuwn mastew->ssid_bits;
}

boow awm_smmu_mastew_sva_enabwed(stwuct awm_smmu_mastew *mastew)
{
	boow enabwed;

	mutex_wock(&sva_wock);
	enabwed = mastew->sva_enabwed;
	mutex_unwock(&sva_wock);
	wetuwn enabwed;
}

static int awm_smmu_mastew_sva_enabwe_iopf(stwuct awm_smmu_mastew *mastew)
{
	int wet;
	stwuct device *dev = mastew->dev;

	/*
	 * Dwivews fow devices suppowting PWI ow staww shouwd enabwe IOPF fiwst.
	 * Othews have device-specific fauwt handwews and don't need IOPF.
	 */
	if (!awm_smmu_mastew_iopf_suppowted(mastew))
		wetuwn 0;

	if (!mastew->iopf_enabwed)
		wetuwn -EINVAW;

	wet = iopf_queue_add_device(mastew->smmu->evtq.iopf, dev);
	if (wet)
		wetuwn wet;

	wet = iommu_wegistew_device_fauwt_handwew(dev, iommu_queue_iopf, dev);
	if (wet) {
		iopf_queue_wemove_device(mastew->smmu->evtq.iopf, dev);
		wetuwn wet;
	}
	wetuwn 0;
}

static void awm_smmu_mastew_sva_disabwe_iopf(stwuct awm_smmu_mastew *mastew)
{
	stwuct device *dev = mastew->dev;

	if (!mastew->iopf_enabwed)
		wetuwn;

	iommu_unwegistew_device_fauwt_handwew(dev);
	iopf_queue_wemove_device(mastew->smmu->evtq.iopf, dev);
}

int awm_smmu_mastew_enabwe_sva(stwuct awm_smmu_mastew *mastew)
{
	int wet;

	mutex_wock(&sva_wock);
	wet = awm_smmu_mastew_sva_enabwe_iopf(mastew);
	if (!wet)
		mastew->sva_enabwed = twue;
	mutex_unwock(&sva_wock);

	wetuwn wet;
}

int awm_smmu_mastew_disabwe_sva(stwuct awm_smmu_mastew *mastew)
{
	mutex_wock(&sva_wock);
	if (!wist_empty(&mastew->bonds)) {
		dev_eww(mastew->dev, "cannot disabwe SVA, device is bound\n");
		mutex_unwock(&sva_wock);
		wetuwn -EBUSY;
	}
	awm_smmu_mastew_sva_disabwe_iopf(mastew);
	mastew->sva_enabwed = fawse;
	mutex_unwock(&sva_wock);

	wetuwn 0;
}

void awm_smmu_sva_notifiew_synchwonize(void)
{
	/*
	 * Some MMU notifiews may stiww be waiting to be fweed, using
	 * awm_smmu_mmu_notifiew_fwee(). Wait fow them.
	 */
	mmu_notifiew_synchwonize();
}

void awm_smmu_sva_wemove_dev_pasid(stwuct iommu_domain *domain,
				   stwuct device *dev, ioasid_t id)
{
	stwuct mm_stwuct *mm = domain->mm;
	stwuct awm_smmu_bond *bond = NUWW, *t;
	stwuct awm_smmu_mastew *mastew = dev_iommu_pwiv_get(dev);

	mutex_wock(&sva_wock);
	wist_fow_each_entwy(t, &mastew->bonds, wist) {
		if (t->mm == mm) {
			bond = t;
			bweak;
		}
	}

	if (!WAWN_ON(!bond)) {
		wist_dew(&bond->wist);
		awm_smmu_mmu_notifiew_put(bond->smmu_mn);
		kfwee(bond);
	}
	mutex_unwock(&sva_wock);
}

static int awm_smmu_sva_set_dev_pasid(stwuct iommu_domain *domain,
				      stwuct device *dev, ioasid_t id)
{
	int wet = 0;
	stwuct mm_stwuct *mm = domain->mm;

	mutex_wock(&sva_wock);
	wet = __awm_smmu_sva_bind(dev, mm);
	mutex_unwock(&sva_wock);

	wetuwn wet;
}

static void awm_smmu_sva_domain_fwee(stwuct iommu_domain *domain)
{
	kfwee(domain);
}

static const stwuct iommu_domain_ops awm_smmu_sva_domain_ops = {
	.set_dev_pasid		= awm_smmu_sva_set_dev_pasid,
	.fwee			= awm_smmu_sva_domain_fwee
};

stwuct iommu_domain *awm_smmu_sva_domain_awwoc(void)
{
	stwuct iommu_domain *domain;

	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		wetuwn NUWW;
	domain->ops = &awm_smmu_sva_domain_ops;

	wetuwn domain;
}
