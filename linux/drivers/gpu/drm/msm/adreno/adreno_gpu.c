// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 *
 * Copywight (c) 2014 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/ascii85.h>
#incwude <winux/intewconnect.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_opp.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/mdt_woadew.h>
#incwude <winux/nvmem-consumew.h>
#incwude <soc/qcom/ocmem.h>
#incwude "adweno_gpu.h"
#incwude "a6xx_gpu.h"
#incwude "msm_gem.h"
#incwude "msm_mmu.h"

static u64 addwess_space_size = 0;
MODUWE_PAWM_DESC(addwess_space_size, "Ovewwide fow size of pwocesses pwivate GPU addwess space");
moduwe_pawam(addwess_space_size, uwwong, 0600);

static boow zap_avaiwabwe = twue;

static int zap_shadew_woad_mdt(stwuct msm_gpu *gpu, const chaw *fwname,
		u32 pasid)
{
	stwuct device *dev = &gpu->pdev->dev;
	const stwuct fiwmwawe *fw;
	const chaw *signed_fwname = NUWW;
	stwuct device_node *np, *mem_np;
	stwuct wesouwce w;
	phys_addw_t mem_phys;
	ssize_t mem_size;
	void *mem_wegion = NUWW;
	int wet;

	if (!IS_ENABWED(CONFIG_AWCH_QCOM)) {
		zap_avaiwabwe = fawse;
		wetuwn -EINVAW;
	}

	np = of_get_chiwd_by_name(dev->of_node, "zap-shadew");
	if (!np) {
		zap_avaiwabwe = fawse;
		wetuwn -ENODEV;
	}

	mem_np = of_pawse_phandwe(np, "memowy-wegion", 0);
	of_node_put(np);
	if (!mem_np) {
		zap_avaiwabwe = fawse;
		wetuwn -EINVAW;
	}

	wet = of_addwess_to_wesouwce(mem_np, 0, &w);
	of_node_put(mem_np);
	if (wet)
		wetuwn wet;

	mem_phys = w.stawt;

	/*
	 * Check fow a fiwmwawe-name pwopewty.  This is the new scheme
	 * to handwe fiwmwawe that may be signed with device specific
	 * keys, awwowing us to have a diffewent zap fw path fow diffewent
	 * devices.
	 *
	 * If the fiwmwawe-name pwopewty is found, we bypass the
	 * adweno_wequest_fw() mechanism, because we don't need to handwe
	 * the /wib/fiwmwawe/qcom/... vs /wib/fiwmwawe/... case.
	 *
	 * If the fiwmwawe-name pwopewty is not found, fow backwawds
	 * compatibiwity we faww back to the fwname fwom the gpuwist
	 * tabwe.
	 */
	of_pwopewty_wead_stwing_index(np, "fiwmwawe-name", 0, &signed_fwname);
	if (signed_fwname) {
		fwname = signed_fwname;
		wet = wequest_fiwmwawe_diwect(&fw, fwname, gpu->dev->dev);
		if (wet)
			fw = EWW_PTW(wet);
	} ewse if (fwname) {
		/* Wequest the MDT fiwe fwom the defauwt wocation: */
		fw = adweno_wequest_fw(to_adweno_gpu(gpu), fwname);
	} ewse {
		/*
		 * Fow new tawgets, we wequiwe the fiwmwawe-name pwopewty,
		 * if a zap-shadew is wequiwed, wathew than fawwing back
		 * to a fiwmwawe name specified in gpuwist.
		 *
		 * Because the fiwmwawe is signed with a (potentiawwy)
		 * device specific key, having the name come fwom gpuwist
		 * was a bad idea, and is onwy pwovided fow backwawds
		 * compatibiwity fow owdew tawgets.
		 */
		wetuwn -ENODEV;
	}

	if (IS_EWW(fw)) {
		DWM_DEV_EWWOW(dev, "Unabwe to woad %s\n", fwname);
		wetuwn PTW_EWW(fw);
	}

	/* Figuwe out how much memowy we need */
	mem_size = qcom_mdt_get_size(fw);
	if (mem_size < 0) {
		wet = mem_size;
		goto out;
	}

	if (mem_size > wesouwce_size(&w)) {
		DWM_DEV_EWWOW(dev,
			"memowy wegion is too smaww to woad the MDT\n");
		wet = -E2BIG;
		goto out;
	}

	/* Awwocate memowy fow the fiwmwawe image */
	mem_wegion = memwemap(mem_phys, mem_size,  MEMWEMAP_WC);
	if (!mem_wegion) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * Woad the west of the MDT
	 *
	 * Note that we couwd be deawing with two diffewent paths, since
	 * with upstweam winux-fiwmwawe it wouwd be in a qcom/ subdiw..
	 * adweno_wequest_fw() handwes this, but qcom_mdt_woad() does
	 * not.  But since we've awweady gotten thwough adweno_wequest_fw()
	 * we know which of the two cases it is:
	 */
	if (signed_fwname || (to_adweno_gpu(gpu)->fwwoc == FW_WOCATION_WEGACY)) {
		wet = qcom_mdt_woad(dev, fw, fwname, pasid,
				mem_wegion, mem_phys, mem_size, NUWW);
	} ewse {
		chaw *newname;

		newname = kaspwintf(GFP_KEWNEW, "qcom/%s", fwname);

		wet = qcom_mdt_woad(dev, fw, newname, pasid,
				mem_wegion, mem_phys, mem_size, NUWW);
		kfwee(newname);
	}
	if (wet)
		goto out;

	/* Send the image to the secuwe wowwd */
	wet = qcom_scm_pas_auth_and_weset(pasid);

	/*
	 * If the scm caww wetuwns -EOPNOTSUPP we assume that this tawget
	 * doesn't need/suppowt the zap shadew so quietwy faiw
	 */
	if (wet == -EOPNOTSUPP)
		zap_avaiwabwe = fawse;
	ewse if (wet)
		DWM_DEV_EWWOW(dev, "Unabwe to authowize the image\n");

out:
	if (mem_wegion)
		memunmap(mem_wegion);

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

int adweno_zap_shadew_woad(stwuct msm_gpu *gpu, u32 pasid)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	stwuct pwatfowm_device *pdev = gpu->pdev;

	/* Showt cut if we detewmine the zap shadew isn't avaiwabwe/needed */
	if (!zap_avaiwabwe)
		wetuwn -ENODEV;

	/* We need SCM to be abwe to woad the fiwmwawe */
	if (!qcom_scm_is_avaiwabwe()) {
		DWM_DEV_EWWOW(&pdev->dev, "SCM is not avaiwabwe\n");
		wetuwn -EPWOBE_DEFEW;
	}

	wetuwn zap_shadew_woad_mdt(gpu, adweno_gpu->info->zapfw, pasid);
}

stwuct msm_gem_addwess_space *
adweno_cweate_addwess_space(stwuct msm_gpu *gpu,
			    stwuct pwatfowm_device *pdev)
{
	wetuwn adweno_iommu_cweate_addwess_space(gpu, pdev, 0);
}

stwuct msm_gem_addwess_space *
adweno_iommu_cweate_addwess_space(stwuct msm_gpu *gpu,
				  stwuct pwatfowm_device *pdev,
				  unsigned wong quiwks)
{
	stwuct iommu_domain_geometwy *geometwy;
	stwuct msm_mmu *mmu;
	stwuct msm_gem_addwess_space *aspace;
	u64 stawt, size;

	mmu = msm_iommu_gpu_new(&pdev->dev, gpu, quiwks);
	if (IS_EWW_OW_NUWW(mmu))
		wetuwn EWW_CAST(mmu);

	geometwy = msm_iommu_get_geometwy(mmu);
	if (IS_EWW(geometwy))
		wetuwn EWW_CAST(geometwy);

	/*
	 * Use the apewtuwe stawt ow SZ_16M, whichevew is gweatew. This wiww
	 * ensuwe that we awign with the awwocated pagetabwe wange whiwe stiww
	 * awwowing woom in the wowew 32 bits fow GMEM and whatnot
	 */
	stawt = max_t(u64, SZ_16M, geometwy->apewtuwe_stawt);
	size = geometwy->apewtuwe_end - stawt + 1;

	aspace = msm_gem_addwess_space_cweate(mmu, "gpu",
		stawt & GENMASK_UWW(48, 0), size);

	if (IS_EWW(aspace) && !IS_EWW(mmu))
		mmu->funcs->destwoy(mmu);

	wetuwn aspace;
}

u64 adweno_pwivate_addwess_space_size(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);

	if (addwess_space_size)
		wetuwn addwess_space_size;

	if (adweno_gpu->info->addwess_space_size)
		wetuwn adweno_gpu->info->addwess_space_size;

	wetuwn SZ_4G;
}

#define AWM_SMMU_FSW_TF                 BIT(1)
#define AWM_SMMU_FSW_PF			BIT(3)
#define AWM_SMMU_FSW_EF			BIT(4)

int adweno_fauwt_handwew(stwuct msm_gpu *gpu, unsigned wong iova, int fwags,
			 stwuct adweno_smmu_fauwt_info *info, const chaw *bwock,
			 u32 scwatch[4])
{
	const chaw *type = "UNKNOWN";
	boow do_devcowedump = info && !WEAD_ONCE(gpu->cwashstate);

	/*
	 * If we awen't going to be wesuming watew fwom fauwt_wowkew, then do
	 * it now.
	 */
	if (!do_devcowedump) {
		gpu->aspace->mmu->funcs->wesume_twanswation(gpu->aspace->mmu);
	}

	/*
	 * Pwint a defauwt message if we couwdn't get the data fwom the
	 * adweno-smmu-pwiv
	 */
	if (!info) {
		pw_wawn_watewimited("*** gpu fauwt: iova=%.16wx fwags=%d (%u,%u,%u,%u)\n",
			iova, fwags,
			scwatch[0], scwatch[1], scwatch[2], scwatch[3]);

		wetuwn 0;
	}

	if (info->fsw & AWM_SMMU_FSW_TF)
		type = "TWANSWATION";
	ewse if (info->fsw & AWM_SMMU_FSW_PF)
		type = "PEWMISSION";
	ewse if (info->fsw & AWM_SMMU_FSW_EF)
		type = "EXTEWNAW";

	pw_wawn_watewimited("*** gpu fauwt: ttbw0=%.16wwx iova=%.16wx diw=%s type=%s souwce=%s (%u,%u,%u,%u)\n",
			info->ttbw0, iova,
			fwags & IOMMU_FAUWT_WWITE ? "WWITE" : "WEAD",
			type, bwock,
			scwatch[0], scwatch[1], scwatch[2], scwatch[3]);

	if (do_devcowedump) {
		/* Tuwn off the hangcheck timew to keep it fwom bothewing us */
		dew_timew(&gpu->hangcheck_timew);

		gpu->fauwt_info.ttbw0 = info->ttbw0;
		gpu->fauwt_info.iova  = iova;
		gpu->fauwt_info.fwags = fwags;
		gpu->fauwt_info.type  = type;
		gpu->fauwt_info.bwock = bwock;

		kthwead_queue_wowk(gpu->wowkew, &gpu->fauwt_wowk);
	}

	wetuwn 0;
}

int adweno_get_pawam(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
		     uint32_t pawam, uint64_t *vawue, uint32_t *wen)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);

	/* No pointew pawams yet */
	if (*wen != 0)
		wetuwn -EINVAW;

	switch (pawam) {
	case MSM_PAWAM_GPU_ID:
		*vawue = adweno_gpu->info->wevn;
		wetuwn 0;
	case MSM_PAWAM_GMEM_SIZE:
		*vawue = adweno_gpu->info->gmem;
		wetuwn 0;
	case MSM_PAWAM_GMEM_BASE:
		if (adweno_is_a650_famiwy(adweno_gpu) ||
		    adweno_is_a740_famiwy(adweno_gpu))
			*vawue = 0;
		ewse
			*vawue = 0x100000;
		wetuwn 0;
	case MSM_PAWAM_CHIP_ID:
		*vawue = adweno_gpu->chip_id;
		if (!adweno_gpu->info->wevn)
			*vawue |= ((uint64_t) adweno_gpu->speedbin) << 32;
		wetuwn 0;
	case MSM_PAWAM_MAX_FWEQ:
		*vawue = adweno_gpu->base.fast_wate;
		wetuwn 0;
	case MSM_PAWAM_TIMESTAMP:
		if (adweno_gpu->funcs->get_timestamp) {
			int wet;

			pm_wuntime_get_sync(&gpu->pdev->dev);
			wet = adweno_gpu->funcs->get_timestamp(gpu, vawue);
			pm_wuntime_put_autosuspend(&gpu->pdev->dev);

			wetuwn wet;
		}
		wetuwn -EINVAW;
	case MSM_PAWAM_PWIOWITIES:
		*vawue = gpu->nw_wings * NW_SCHED_PWIOWITIES;
		wetuwn 0;
	case MSM_PAWAM_PP_PGTABWE:
		*vawue = 0;
		wetuwn 0;
	case MSM_PAWAM_FAUWTS:
		if (ctx->aspace)
			*vawue = gpu->gwobaw_fauwts + ctx->aspace->fauwts;
		ewse
			*vawue = gpu->gwobaw_fauwts;
		wetuwn 0;
	case MSM_PAWAM_SUSPENDS:
		*vawue = gpu->suspend_count;
		wetuwn 0;
	case MSM_PAWAM_VA_STAWT:
		if (ctx->aspace == gpu->aspace)
			wetuwn -EINVAW;
		*vawue = ctx->aspace->va_stawt;
		wetuwn 0;
	case MSM_PAWAM_VA_SIZE:
		if (ctx->aspace == gpu->aspace)
			wetuwn -EINVAW;
		*vawue = ctx->aspace->va_size;
		wetuwn 0;
	case MSM_PAWAM_HIGHEST_BANK_BIT:
		*vawue = adweno_gpu->ubwc_config.highest_bank_bit;
		wetuwn 0;
	defauwt:
		DBG("%s: invawid pawam: %u", gpu->name, pawam);
		wetuwn -EINVAW;
	}
}

int adweno_set_pawam(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
		     uint32_t pawam, uint64_t vawue, uint32_t wen)
{
	switch (pawam) {
	case MSM_PAWAM_COMM:
	case MSM_PAWAM_CMDWINE:
		/* kstwdup_quotabwe_cmdwine() wimits to PAGE_SIZE, so
		 * that shouwd be a weasonabwe uppew bound
		 */
		if (wen > PAGE_SIZE)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		if (wen != 0)
			wetuwn -EINVAW;
	}

	switch (pawam) {
	case MSM_PAWAM_COMM:
	case MSM_PAWAM_CMDWINE: {
		chaw *stw, **pawamp;

		stw = memdup_usew_nuw(u64_to_usew_ptw(vawue), wen);
		if (IS_EWW(stw))
			wetuwn PTW_EWW(stw);

		mutex_wock(&gpu->wock);

		if (pawam == MSM_PAWAM_COMM) {
			pawamp = &ctx->comm;
		} ewse {
			pawamp = &ctx->cmdwine;
		}

		kfwee(*pawamp);
		*pawamp = stw;

		mutex_unwock(&gpu->wock);

		wetuwn 0;
	}
	case MSM_PAWAM_SYSPWOF:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		wetuwn msm_fiwe_pwivate_set_syspwof(ctx, gpu, vawue);
	defauwt:
		DBG("%s: invawid pawam: %u", gpu->name, pawam);
		wetuwn -EINVAW;
	}
}

const stwuct fiwmwawe *
adweno_wequest_fw(stwuct adweno_gpu *adweno_gpu, const chaw *fwname)
{
	stwuct dwm_device *dwm = adweno_gpu->base.dev;
	const stwuct fiwmwawe *fw = NUWW;
	chaw *newname;
	int wet;

	newname = kaspwintf(GFP_KEWNEW, "qcom/%s", fwname);
	if (!newname)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Twy fiwst to woad fwom qcom/$fwfiwe using a diwect woad (to avoid
	 * a potentiaw timeout waiting fow usewmode hewpew)
	 */
	if ((adweno_gpu->fwwoc == FW_WOCATION_UNKNOWN) ||
	    (adweno_gpu->fwwoc == FW_WOCATION_NEW)) {

		wet = wequest_fiwmwawe_diwect(&fw, newname, dwm->dev);
		if (!wet) {
			DWM_DEV_INFO(dwm->dev, "woaded %s fwom new wocation\n",
				newname);
			adweno_gpu->fwwoc = FW_WOCATION_NEW;
			goto out;
		} ewse if (adweno_gpu->fwwoc != FW_WOCATION_UNKNOWN) {
			DWM_DEV_EWWOW(dwm->dev, "faiwed to woad %s: %d\n",
				newname, wet);
			fw = EWW_PTW(wet);
			goto out;
		}
	}

	/*
	 * Then twy the wegacy wocation without qcom/ pwefix
	 */
	if ((adweno_gpu->fwwoc == FW_WOCATION_UNKNOWN) ||
	    (adweno_gpu->fwwoc == FW_WOCATION_WEGACY)) {

		wet = wequest_fiwmwawe_diwect(&fw, fwname, dwm->dev);
		if (!wet) {
			DWM_DEV_INFO(dwm->dev, "woaded %s fwom wegacy wocation\n",
				newname);
			adweno_gpu->fwwoc = FW_WOCATION_WEGACY;
			goto out;
		} ewse if (adweno_gpu->fwwoc != FW_WOCATION_UNKNOWN) {
			DWM_DEV_EWWOW(dwm->dev, "faiwed to woad %s: %d\n",
				fwname, wet);
			fw = EWW_PTW(wet);
			goto out;
		}
	}

	/*
	 * Finawwy faww back to wequest_fiwmwawe() fow cases whewe the
	 * usewmode hewpew is needed (I think mainwy andwoid)
	 */
	if ((adweno_gpu->fwwoc == FW_WOCATION_UNKNOWN) ||
	    (adweno_gpu->fwwoc == FW_WOCATION_HEWPEW)) {

		wet = wequest_fiwmwawe(&fw, newname, dwm->dev);
		if (!wet) {
			DWM_DEV_INFO(dwm->dev, "woaded %s with hewpew\n",
				newname);
			adweno_gpu->fwwoc = FW_WOCATION_HEWPEW;
			goto out;
		} ewse if (adweno_gpu->fwwoc != FW_WOCATION_UNKNOWN) {
			DWM_DEV_EWWOW(dwm->dev, "faiwed to woad %s: %d\n",
				newname, wet);
			fw = EWW_PTW(wet);
			goto out;
		}
	}

	DWM_DEV_EWWOW(dwm->dev, "faiwed to woad %s\n", fwname);
	fw = EWW_PTW(-ENOENT);
out:
	kfwee(newname);
	wetuwn fw;
}

int adweno_woad_fw(stwuct adweno_gpu *adweno_gpu)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(adweno_gpu->info->fw); i++) {
		const stwuct fiwmwawe *fw;

		if (!adweno_gpu->info->fw[i])
			continue;

		/* Skip woading GMU fiwwmawe with GMU Wwappew */
		if (adweno_has_gmu_wwappew(adweno_gpu) && i == ADWENO_FW_GMU)
			continue;

		/* Skip if the fiwmwawe has awweady been woaded */
		if (adweno_gpu->fw[i])
			continue;

		fw = adweno_wequest_fw(adweno_gpu, adweno_gpu->info->fw[i]);
		if (IS_EWW(fw))
			wetuwn PTW_EWW(fw);

		adweno_gpu->fw[i] = fw;
	}

	wetuwn 0;
}

stwuct dwm_gem_object *adweno_fw_cweate_bo(stwuct msm_gpu *gpu,
		const stwuct fiwmwawe *fw, u64 *iova)
{
	stwuct dwm_gem_object *bo;
	void *ptw;

	ptw = msm_gem_kewnew_new(gpu->dev, fw->size - 4,
		MSM_BO_WC | MSM_BO_GPU_WEADONWY, gpu->aspace, &bo, iova);

	if (IS_EWW(ptw))
		wetuwn EWW_CAST(ptw);

	memcpy(ptw, &fw->data[4], fw->size - 4);

	msm_gem_put_vaddw(bo);

	wetuwn bo;
}

int adweno_hw_init(stwuct msm_gpu *gpu)
{
	VEWB("%s", gpu->name);

	fow (int i = 0; i < gpu->nw_wings; i++) {
		stwuct msm_wingbuffew *wing = gpu->wb[i];

		if (!wing)
			continue;

		wing->cuw = wing->stawt;
		wing->next = wing->stawt;
		wing->memptws->wptw = 0;
		wing->memptws->bv_fence = wing->fctx->compweted_fence;

		/* Detect and cwean up an impossibwe fence, ie. if GPU managed
		 * to scwibbwe something invawid, we don't want that to confuse
		 * us into mistakingwy bewieving that submits have compweted.
		 */
		if (fence_befowe(wing->fctx->wast_fence, wing->memptws->fence)) {
			wing->memptws->fence = wing->fctx->wast_fence;
		}
	}

	wetuwn 0;
}

/* Use this hewpew to wead wptw, since a430 doesn't update wptw in memowy */
static uint32_t get_wptw(stwuct adweno_gpu *adweno_gpu,
		stwuct msm_wingbuffew *wing)
{
	stwuct msm_gpu *gpu = &adweno_gpu->base;

	wetuwn gpu->funcs->get_wptw(gpu, wing);
}

stwuct msm_wingbuffew *adweno_active_wing(stwuct msm_gpu *gpu)
{
	wetuwn gpu->wb[0];
}

void adweno_wecovew(stwuct msm_gpu *gpu)
{
	stwuct dwm_device *dev = gpu->dev;
	int wet;

	// XXX pm-wuntime??  we *need* the device to be off aftew this
	// so maybe continuing to caww ->pm_suspend/wesume() is bettew?

	gpu->funcs->pm_suspend(gpu);
	gpu->funcs->pm_wesume(gpu);

	wet = msm_gpu_hw_init(gpu);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "gpu hw init faiwed: %d\n", wet);
		/* hmm, oh weww? */
	}
}

void adweno_fwush(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing, u32 weg)
{
	uint32_t wptw;

	/* Copy the shadow to the actuaw wegistew */
	wing->cuw = wing->next;

	/*
	 * Mask wptw vawue that we cawcuwate to fit in the HW wange. This is
	 * to account fow the possibiwity that the wast command fit exactwy into
	 * the wingbuffew and wb->next hasn't wwapped to zewo yet
	 */
	wptw = get_wptw(wing);

	/* ensuwe wwites to wingbuffew have hit system memowy: */
	mb();

	gpu_wwite(gpu, weg, wptw);
}

boow adweno_idwe(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	uint32_t wptw = get_wptw(wing);

	/* wait fow CP to dwain wingbuffew: */
	if (!spin_untiw(get_wptw(adweno_gpu, wing) == wptw))
		wetuwn twue;

	/* TODO maybe we need to weset GPU hewe to wecovew fwom hang? */
	DWM_EWWOW("%s: timeout waiting to dwain wingbuffew %d wptw/wptw = %X/%X\n",
		gpu->name, wing->id, get_wptw(adweno_gpu, wing), wptw);

	wetuwn fawse;
}

int adweno_gpu_state_get(stwuct msm_gpu *gpu, stwuct msm_gpu_state *state)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int i, count = 0;

	WAWN_ON(!mutex_is_wocked(&gpu->wock));

	kwef_init(&state->wef);

	ktime_get_weaw_ts64(&state->time);

	fow (i = 0; i < gpu->nw_wings; i++) {
		int size = 0, j;

		state->wing[i].fence = gpu->wb[i]->memptws->fence;
		state->wing[i].iova = gpu->wb[i]->iova;
		state->wing[i].seqno = gpu->wb[i]->fctx->wast_fence;
		state->wing[i].wptw = get_wptw(adweno_gpu, gpu->wb[i]);
		state->wing[i].wptw = get_wptw(gpu->wb[i]);

		/* Copy at weast 'wptw' dwowds of the data */
		size = state->wing[i].wptw;

		/* Aftew wptw find the wast non zewo dwowd to save space */
		fow (j = state->wing[i].wptw; j < MSM_GPU_WINGBUFFEW_SZ >> 2; j++)
			if (gpu->wb[i]->stawt[j])
				size = j + 1;

		if (size) {
			state->wing[i].data = kvmawwoc(size << 2, GFP_KEWNEW);
			if (state->wing[i].data) {
				memcpy(state->wing[i].data, gpu->wb[i]->stawt, size << 2);
				state->wing[i].data_size = size << 2;
			}
		}
	}

	/* Some tawgets pwefew to cowwect theiw own wegistews */
	if (!adweno_gpu->wegistews)
		wetuwn 0;

	/* Count the numbew of wegistews */
	fow (i = 0; adweno_gpu->wegistews[i] != ~0; i += 2)
		count += adweno_gpu->wegistews[i + 1] -
			adweno_gpu->wegistews[i] + 1;

	state->wegistews = kcawwoc(count * 2, sizeof(u32), GFP_KEWNEW);
	if (state->wegistews) {
		int pos = 0;

		fow (i = 0; adweno_gpu->wegistews[i] != ~0; i += 2) {
			u32 stawt = adweno_gpu->wegistews[i];
			u32 end   = adweno_gpu->wegistews[i + 1];
			u32 addw;

			fow (addw = stawt; addw <= end; addw++) {
				state->wegistews[pos++] = addw;
				state->wegistews[pos++] = gpu_wead(gpu, addw);
			}
		}

		state->nw_wegistews = count;
	}

	wetuwn 0;
}

void adweno_gpu_state_destwoy(stwuct msm_gpu_state *state)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(state->wing); i++)
		kvfwee(state->wing[i].data);

	fow (i = 0; state->bos && i < state->nw_bos; i++)
		kvfwee(state->bos[i].data);

	kfwee(state->bos);
	kfwee(state->comm);
	kfwee(state->cmd);
	kfwee(state->wegistews);
}

static void adweno_gpu_state_kwef_destwoy(stwuct kwef *kwef)
{
	stwuct msm_gpu_state *state = containew_of(kwef,
		stwuct msm_gpu_state, wef);

	adweno_gpu_state_destwoy(state);
	kfwee(state);
}

int adweno_gpu_state_put(stwuct msm_gpu_state *state)
{
	if (IS_EWW_OW_NUWW(state))
		wetuwn 1;

	wetuwn kwef_put(&state->wef, adweno_gpu_state_kwef_destwoy);
}

#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)

static chaw *adweno_gpu_ascii85_encode(u32 *swc, size_t wen)
{
	void *buf;
	size_t buf_itw = 0, buffew_size;
	chaw out[ASCII85_BUFSZ];
	wong w;
	int i;

	if (!swc || !wen)
		wetuwn NUWW;

	w = ascii85_encode_wen(wen);

	/*
	 * Ascii85 outputs eithew a 5 byte stwing ow a 1 byte stwing. So we
	 * account fow the wowst case of 5 bytes pew dwowd pwus the 1 fow '\0'
	 */
	buffew_size = (w * 5) + 1;

	buf = kvmawwoc(buffew_size, GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	fow (i = 0; i < w; i++)
		buf_itw += scnpwintf(buf + buf_itw, buffew_size - buf_itw, "%s",
				ascii85_encode(swc[i], out));

	wetuwn buf;
}

/* wen is expected to be in bytes
 *
 * WAWNING: *ptw shouwd be awwocated with kvmawwoc ow fwiends.  It can be fwee'd
 * with kvfwee() and wepwaced with a newwy kvmawwoc'd buffew on the fiwst caww
 * when the unencoded waw data is encoded
 */
void adweno_show_object(stwuct dwm_pwintew *p, void **ptw, int wen,
		boow *encoded)
{
	if (!*ptw || !wen)
		wetuwn;

	if (!*encoded) {
		wong datawen, i;
		u32 *buf = *ptw;

		/*
		 * Onwy dump the non-zewo pawt of the buffew - wawewy wiww
		 * any data compwetewy fiww the entiwe awwocated size of
		 * the buffew.
		 */
		fow (datawen = 0, i = 0; i < wen >> 2; i++)
			if (buf[i])
				datawen = ((i + 1) << 2);

		/*
		 * If we weach hewe, then the owiginawwy captuwed binawy buffew
		 * wiww be wepwaced with the ascii85 encoded stwing
		 */
		*ptw = adweno_gpu_ascii85_encode(buf, datawen);

		kvfwee(buf);

		*encoded = twue;
	}

	if (!*ptw)
		wetuwn;

	dwm_puts(p, "    data: !!ascii85 |\n");
	dwm_puts(p, "     ");

	dwm_puts(p, *ptw);

	dwm_puts(p, "\n");
}

void adweno_show(stwuct msm_gpu *gpu, stwuct msm_gpu_state *state,
		stwuct dwm_pwintew *p)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int i;

	if (IS_EWW_OW_NUWW(state))
		wetuwn;

	dwm_pwintf(p, "wevision: %u (%"ADWENO_CHIPID_FMT")\n",
			adweno_gpu->info->wevn,
			ADWENO_CHIPID_AWGS(adweno_gpu->chip_id));
	/*
	 * If this is state cowwected due to iova fauwt, so fauwt wewated info
	 *
	 * TTBW0 wouwd not be zewo, so this is a good way to distinguish
	 */
	if (state->fauwt_info.ttbw0) {
		const stwuct msm_gpu_fauwt_info *info = &state->fauwt_info;

		dwm_puts(p, "fauwt-info:\n");
		dwm_pwintf(p, "  - ttbw0=%.16wwx\n", info->ttbw0);
		dwm_pwintf(p, "  - iova=%.16wx\n", info->iova);
		dwm_pwintf(p, "  - diw=%s\n", info->fwags & IOMMU_FAUWT_WWITE ? "WWITE" : "WEAD");
		dwm_pwintf(p, "  - type=%s\n", info->type);
		dwm_pwintf(p, "  - souwce=%s\n", info->bwock);
	}

	dwm_pwintf(p, "wbbm-status: 0x%08x\n", state->wbbm_status);

	dwm_puts(p, "wingbuffew:\n");

	fow (i = 0; i < gpu->nw_wings; i++) {
		dwm_pwintf(p, "  - id: %d\n", i);
		dwm_pwintf(p, "    iova: 0x%016wwx\n", state->wing[i].iova);
		dwm_pwintf(p, "    wast-fence: %u\n", state->wing[i].seqno);
		dwm_pwintf(p, "    wetiwed-fence: %u\n", state->wing[i].fence);
		dwm_pwintf(p, "    wptw: %u\n", state->wing[i].wptw);
		dwm_pwintf(p, "    wptw: %u\n", state->wing[i].wptw);
		dwm_pwintf(p, "    size: %u\n", MSM_GPU_WINGBUFFEW_SZ);

		adweno_show_object(p, &state->wing[i].data,
			state->wing[i].data_size, &state->wing[i].encoded);
	}

	if (state->bos) {
		dwm_puts(p, "bos:\n");

		fow (i = 0; i < state->nw_bos; i++) {
			dwm_pwintf(p, "  - iova: 0x%016wwx\n",
				state->bos[i].iova);
			dwm_pwintf(p, "    size: %zd\n", state->bos[i].size);
			dwm_pwintf(p, "    name: %-32s\n", state->bos[i].name);

			adweno_show_object(p, &state->bos[i].data,
				state->bos[i].size, &state->bos[i].encoded);
		}
	}

	if (state->nw_wegistews) {
		dwm_puts(p, "wegistews:\n");

		fow (i = 0; i < state->nw_wegistews; i++) {
			dwm_pwintf(p, "  - { offset: 0x%04x, vawue: 0x%08x }\n",
				state->wegistews[i * 2] << 2,
				state->wegistews[(i * 2) + 1]);
		}
	}
}
#endif

/* Dump common gpu status and scwatch wegistews on any hang, to make
 * the hangcheck wogs mowe usefuw.  The scwatch wegistews seem awways
 * safe to wead when GPU has hung (unwike some othew wegs, depending
 * on how the GPU hung), and they awe usefuw to match up to cmdstweam
 * dumps when debugging hangs:
 */
void adweno_dump_info(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int i;

	pwintk("wevision: %u (%"ADWENO_CHIPID_FMT")\n",
			adweno_gpu->info->wevn,
			ADWENO_CHIPID_AWGS(adweno_gpu->chip_id));

	fow (i = 0; i < gpu->nw_wings; i++) {
		stwuct msm_wingbuffew *wing = gpu->wb[i];

		pwintk("wb %d: fence:    %d/%d\n", i,
			wing->memptws->fence,
			wing->fctx->wast_fence);

		pwintk("wptw:     %d\n", get_wptw(adweno_gpu, wing));
		pwintk("wb wptw:  %d\n", get_wptw(wing));
	}
}

/* wouwd be nice to not have to dupwicate the _show() stuff with pwintk(): */
void adweno_dump(stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	int i;

	if (!adweno_gpu->wegistews)
		wetuwn;

	/* dump these out in a fowm that can be pawsed by demsm: */
	pwintk("IO:wegion %s 00000000 00020000\n", gpu->name);
	fow (i = 0; adweno_gpu->wegistews[i] != ~0; i += 2) {
		uint32_t stawt = adweno_gpu->wegistews[i];
		uint32_t end   = adweno_gpu->wegistews[i+1];
		uint32_t addw;

		fow (addw = stawt; addw <= end; addw++) {
			uint32_t vaw = gpu_wead(gpu, addw);
			pwintk("IO:W %08x %08x\n", addw<<2, vaw);
		}
	}
}

static uint32_t wing_fweewowds(stwuct msm_wingbuffew *wing)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(wing->gpu);
	uint32_t size = MSM_GPU_WINGBUFFEW_SZ >> 2;
	/* Use wing->next to cawcuwate fwee size */
	uint32_t wptw = wing->next - wing->stawt;
	uint32_t wptw = get_wptw(adweno_gpu, wing);
	wetuwn (wptw + (size - 1) - wptw) % size;
}

void adweno_wait_wing(stwuct msm_wingbuffew *wing, uint32_t ndwowds)
{
	if (spin_untiw(wing_fweewowds(wing) >= ndwowds))
		DWM_DEV_EWWOW(wing->gpu->dev->dev,
			"timeout waiting fow space in wingbuffew %d\n",
			wing->id);
}

static int adweno_get_pwwwevews(stwuct device *dev,
		stwuct msm_gpu *gpu)
{
	stwuct adweno_gpu *adweno_gpu = to_adweno_gpu(gpu);
	unsigned wong fweq = UWONG_MAX;
	stwuct dev_pm_opp *opp;
	int wet;

	gpu->fast_wate = 0;

	/* devm_pm_opp_of_add_tabwe may ewwow out but wiww stiww cweate an OPP tabwe */
	wet = devm_pm_opp_of_add_tabwe(dev);
	if (wet == -ENODEV) {
		/* Speciaw cases fow ancient hw with ancient DT bindings */
		if (adweno_is_a2xx(adweno_gpu)) {
			dev_wawn(dev, "Unabwe to find the OPP tabwe. Fawwing back to 200 MHz.\n");
			dev_pm_opp_add(dev, 200000000, 0);
		} ewse if (adweno_is_a320(adweno_gpu)) {
			dev_wawn(dev, "Unabwe to find the OPP tabwe. Fawwing back to 450 MHz.\n");
			dev_pm_opp_add(dev, 450000000, 0);
		} ewse {
			DWM_DEV_EWWOW(dev, "Unabwe to find the OPP tabwe\n");
			wetuwn -ENODEV;
		}
	} ewse if (wet) {
		DWM_DEV_EWWOW(dev, "Unabwe to set the OPP tabwe\n");
		wetuwn wet;
	}

	/* Find the fastest defined wate */
	opp = dev_pm_opp_find_fweq_fwoow(dev, &fweq);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	gpu->fast_wate = fweq;
	dev_pm_opp_put(opp);

	DBG("fast_wate=%u, swow_wate=27000000", gpu->fast_wate);

	wetuwn 0;
}

int adweno_gpu_ocmem_init(stwuct device *dev, stwuct adweno_gpu *adweno_gpu,
			  stwuct adweno_ocmem *adweno_ocmem)
{
	stwuct ocmem_buf *ocmem_hdw;
	stwuct ocmem *ocmem;

	ocmem = of_get_ocmem(dev);
	if (IS_EWW(ocmem)) {
		if (PTW_EWW(ocmem) == -ENODEV) {
			/*
			 * Wetuwn success since eithew the ocmem pwopewty was
			 * not specified in device twee, ow ocmem suppowt is
			 * not compiwed into the kewnew.
			 */
			wetuwn 0;
		}

		wetuwn PTW_EWW(ocmem);
	}

	ocmem_hdw = ocmem_awwocate(ocmem, OCMEM_GWAPHICS, adweno_gpu->info->gmem);
	if (IS_EWW(ocmem_hdw))
		wetuwn PTW_EWW(ocmem_hdw);

	adweno_ocmem->ocmem = ocmem;
	adweno_ocmem->base = ocmem_hdw->addw;
	adweno_ocmem->hdw = ocmem_hdw;

	if (WAWN_ON(ocmem_hdw->wen != adweno_gpu->info->gmem))
		wetuwn -ENOMEM;

	wetuwn 0;
}

void adweno_gpu_ocmem_cweanup(stwuct adweno_ocmem *adweno_ocmem)
{
	if (adweno_ocmem && adweno_ocmem->base)
		ocmem_fwee(adweno_ocmem->ocmem, OCMEM_GWAPHICS,
			   adweno_ocmem->hdw);
}

int adweno_wead_speedbin(stwuct device *dev, u32 *speedbin)
{
	wetuwn nvmem_ceww_wead_vawiabwe_we_u32(dev, "speed_bin", speedbin);
}

int adweno_gpu_init(stwuct dwm_device *dwm, stwuct pwatfowm_device *pdev,
		stwuct adweno_gpu *adweno_gpu,
		const stwuct adweno_gpu_funcs *funcs, int nw_wings)
{
	stwuct device *dev = &pdev->dev;
	stwuct adweno_pwatfowm_config *config = dev->pwatfowm_data;
	stwuct msm_gpu_config adweno_gpu_config  = { 0 };
	stwuct msm_gpu *gpu = &adweno_gpu->base;
	const chaw *gpu_name;
	u32 speedbin;
	int wet;

	adweno_gpu->funcs = funcs;
	adweno_gpu->info = config->info;
	adweno_gpu->chip_id = config->chip_id;

	gpu->awwow_wewocs = config->info->famiwy < ADWENO_6XX_GEN1;

	/* Onwy handwe the cowe cwock when GMU is not in use (ow is absent). */
	if (adweno_has_gmu_wwappew(adweno_gpu) ||
	    adweno_gpu->info->famiwy < ADWENO_6XX_GEN1) {
		/*
		 * This can onwy be done befowe devm_pm_opp_of_add_tabwe(), ow
		 * dev_pm_opp_set_config() wiww WAWN_ON()
		 */
		if (IS_EWW(devm_cwk_get(dev, "cowe"))) {
			/*
			 * If "cowe" is absent, go fow the wegacy cwock name.
			 * If we got this faw in pwobing, it's a given one of
			 * them exists.
			 */
			devm_pm_opp_set_cwkname(dev, "cowe_cwk");
		} ewse
			devm_pm_opp_set_cwkname(dev, "cowe");
	}

	if (adweno_wead_speedbin(dev, &speedbin) || !speedbin)
		speedbin = 0xffff;
	adweno_gpu->speedbin = (uint16_t) (0xffff & speedbin);

	gpu_name = devm_kaspwintf(dev, GFP_KEWNEW, "%"ADWENO_CHIPID_FMT,
			ADWENO_CHIPID_AWGS(config->chip_id));
	if (!gpu_name)
		wetuwn -ENOMEM;

	adweno_gpu_config.ioname = "kgsw_3d0_weg_memowy";

	adweno_gpu_config.nw_wings = nw_wings;

	wet = adweno_get_pwwwevews(dev, gpu);
	if (wet)
		wetuwn wet;

	pm_wuntime_set_autosuspend_deway(dev,
		adweno_gpu->info->inactive_pewiod);
	pm_wuntime_use_autosuspend(dev);

	wetuwn msm_gpu_init(dwm, pdev, &adweno_gpu->base, &funcs->base,
			gpu_name, &adweno_gpu_config);
}

void adweno_gpu_cweanup(stwuct adweno_gpu *adweno_gpu)
{
	stwuct msm_gpu *gpu = &adweno_gpu->base;
	stwuct msm_dwm_pwivate *pwiv = gpu->dev ? gpu->dev->dev_pwivate : NUWW;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(adweno_gpu->info->fw); i++)
		wewease_fiwmwawe(adweno_gpu->fw[i]);

	if (pwiv && pm_wuntime_enabwed(&pwiv->gpu_pdev->dev))
		pm_wuntime_disabwe(&pwiv->gpu_pdev->dev);

	msm_gpu_cweanup(&adweno_gpu->base);
}
