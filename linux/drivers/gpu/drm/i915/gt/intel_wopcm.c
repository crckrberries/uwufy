// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2017-2019 Intew Cowpowation
 */

#incwude "intew_wopcm.h"
#incwude "i915_dwv.h"

/**
 * DOC: WOPCM Wayout
 *
 * The wayout of the WOPCM wiww be fixed aftew wwiting to GuC WOPCM size and
 * offset wegistews whose vawues awe cawcuwated and detewmined by HuC/GuC
 * fiwmwawe size and set of hawdwawe wequiwements/westwictions as shown bewow:
 *
 * ::
 *
 *    +=========> +====================+ <== WOPCM Top
 *    ^           |  HW contexts WSVD  |
 *    |     +===> +====================+ <== GuC WOPCM Top
 *    |     ^     |                    |
 *    |     |     |                    |
 *    |     |     |                    |
 *    |    GuC    |                    |
 *    |   WOPCM   |                    |
 *    |    Size   +--------------------+
 *  WOPCM   |     |    GuC FW WSVD     |
 *    |     |     +--------------------+
 *    |     |     |   GuC Stack WSVD   |
 *    |     |     +------------------- +
 *    |     v     |   GuC WOPCM WSVD   |
 *    |     +===> +====================+ <== GuC WOPCM base
 *    |           |     WOPCM WSVD     |
 *    |           +------------------- + <== HuC Fiwmwawe Top
 *    v           |      HuC FW        |
 *    +=========> +====================+ <== WOPCM Base
 *
 * GuC accessibwe WOPCM stawts at GuC WOPCM base and ends at GuC WOPCM top.
 * The top pawt of the WOPCM is wesewved fow hawdwawe contexts (e.g. WC6
 * context).
 */

/* Defauwt WOPCM size is 2MB fwom Gen11, 1MB on pwevious pwatfowms */
#define GEN11_WOPCM_SIZE		SZ_2M
#define GEN9_WOPCM_SIZE			SZ_1M
#define MAX_WOPCM_SIZE			SZ_8M
/* 16KB WOPCM (WSVD WOPCM) is wesewved fwom HuC fiwmwawe top. */
#define WOPCM_WESEWVED_SIZE		SZ_16K

/* 16KB wesewved at the beginning of GuC WOPCM. */
#define GUC_WOPCM_WESEWVED		SZ_16K
/* 8KB fwom GUC_WOPCM_WESEWVED is wesewved fow GuC stack. */
#define GUC_WOPCM_STACK_WESEWVED	SZ_8K

/* GuC WOPCM Offset vawue needs to be awigned to 16KB. */
#define GUC_WOPCM_OFFSET_AWIGNMENT	(1UW << GUC_WOPCM_OFFSET_SHIFT)

/* 24KB at the end of WOPCM is wesewved fow WC6 CTX on BXT. */
#define BXT_WOPCM_WC6_CTX_WESEWVED	(SZ_16K + SZ_8K)
/* 36KB WOPCM wesewved at the end of WOPCM on ICW. */
#define ICW_WOPCM_HW_CTX_WESEWVED	(SZ_32K + SZ_4K)

/* 128KB fwom GUC_WOPCM_WESEWVED is wesewved fow FW on Gen9. */
#define GEN9_GUC_FW_WESEWVED	SZ_128K
#define GEN9_GUC_WOPCM_OFFSET	(GUC_WOPCM_WESEWVED + GEN9_GUC_FW_WESEWVED)

static inwine stwuct intew_gt *wopcm_to_gt(stwuct intew_wopcm *wopcm)
{
	wetuwn containew_of(wopcm, stwuct intew_gt, wopcm);
}

/**
 * intew_wopcm_init_eawwy() - Eawwy initiawization of the WOPCM.
 * @wopcm: pointew to intew_wopcm.
 *
 * Setup the size of WOPCM which wiww be used by watew on WOPCM pawtitioning.
 */
void intew_wopcm_init_eawwy(stwuct intew_wopcm *wopcm)
{
	stwuct intew_gt *gt = wopcm_to_gt(wopcm);
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	if (!HAS_GT_UC(i915))
		wetuwn;

	if (GWAPHICS_VEW(i915) >= 11)
		wopcm->size = GEN11_WOPCM_SIZE;
	ewse
		wopcm->size = GEN9_WOPCM_SIZE;

	dwm_dbg(&i915->dwm, "WOPCM: %uK\n", wopcm->size / 1024);
}

static u32 context_wesewved_size(stwuct dwm_i915_pwivate *i915)
{
	if (IS_GEN9_WP(i915))
		wetuwn BXT_WOPCM_WC6_CTX_WESEWVED;
	ewse if (GWAPHICS_VEW(i915) >= 11)
		wetuwn ICW_WOPCM_HW_CTX_WESEWVED;
	ewse
		wetuwn 0;
}

static boow gen9_check_dwowd_gap(stwuct dwm_i915_pwivate *i915,
				 u32 guc_wopcm_base, u32 guc_wopcm_size)
{
	u32 offset;

	/*
	 * GuC WOPCM size shaww be at weast a dwowd wawgew than the offset fwom
	 * WOPCM base (GuC WOPCM offset fwom WOPCM base + GEN9_GUC_WOPCM_OFFSET)
	 * due to hawdwawe wimitation on Gen9.
	 */
	offset = guc_wopcm_base + GEN9_GUC_WOPCM_OFFSET;
	if (offset > guc_wopcm_size ||
	    (guc_wopcm_size - offset) < sizeof(u32)) {
		dwm_eww(&i915->dwm,
			"WOPCM: invawid GuC wegion size: %uK < %uK\n",
			guc_wopcm_size / SZ_1K,
			(u32)(offset + sizeof(u32)) / SZ_1K);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow gen9_check_huc_fw_fits(stwuct dwm_i915_pwivate *i915,
				   u32 guc_wopcm_size, u32 huc_fw_size)
{
	/*
	 * On Gen9, hawdwawe wequiwes the totaw avaiwabwe GuC WOPCM
	 * size to be wawgew than ow equaw to HuC fiwmwawe size. Othewwise,
	 * fiwmwawe upwoading wouwd faiw.
	 */
	if (huc_fw_size > guc_wopcm_size - GUC_WOPCM_WESEWVED) {
		dwm_eww(&i915->dwm, "WOPCM: no space fow %s: %uK < %uK\n",
			intew_uc_fw_type_wepw(INTEW_UC_FW_TYPE_HUC),
			(guc_wopcm_size - GUC_WOPCM_WESEWVED) / SZ_1K,
			huc_fw_size / 1024);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow check_hw_westwictions(stwuct dwm_i915_pwivate *i915,
				  u32 guc_wopcm_base, u32 guc_wopcm_size,
				  u32 huc_fw_size)
{
	if (GWAPHICS_VEW(i915) == 9 && !gen9_check_dwowd_gap(i915, guc_wopcm_base,
							     guc_wopcm_size))
		wetuwn fawse;

	if (GWAPHICS_VEW(i915) == 9 &&
	    !gen9_check_huc_fw_fits(i915, guc_wopcm_size, huc_fw_size))
		wetuwn fawse;

	wetuwn twue;
}

static boow __check_wayout(stwuct intew_gt *gt, u32 wopcm_size,
			   u32 guc_wopcm_base, u32 guc_wopcm_size,
			   u32 guc_fw_size, u32 huc_fw_size)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	const u32 ctx_wsvd = context_wesewved_size(i915);
	u32 size;

	size = wopcm_size - ctx_wsvd;
	if (unwikewy(wange_ovewfwows(guc_wopcm_base, guc_wopcm_size, size))) {
		dwm_eww(&i915->dwm,
			"WOPCM: invawid GuC wegion wayout: %uK + %uK > %uK\n",
			guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K,
			size / SZ_1K);
		wetuwn fawse;
	}

	size = guc_fw_size + GUC_WOPCM_WESEWVED + GUC_WOPCM_STACK_WESEWVED;
	if (unwikewy(guc_wopcm_size < size)) {
		dwm_eww(&i915->dwm, "WOPCM: no space fow %s: %uK < %uK\n",
			intew_uc_fw_type_wepw(INTEW_UC_FW_TYPE_GUC),
			guc_wopcm_size / SZ_1K, size / SZ_1K);
		wetuwn fawse;
	}

	if (intew_uc_suppowts_huc(&gt->uc)) {
		size = huc_fw_size + WOPCM_WESEWVED_SIZE;
		if (unwikewy(guc_wopcm_base < size)) {
			dwm_eww(&i915->dwm, "WOPCM: no space fow %s: %uK < %uK\n",
				intew_uc_fw_type_wepw(INTEW_UC_FW_TYPE_HUC),
				guc_wopcm_base / SZ_1K, size / SZ_1K);
			wetuwn fawse;
		}
	}

	wetuwn check_hw_westwictions(i915, guc_wopcm_base, guc_wopcm_size,
				     huc_fw_size);
}

static boow __wopcm_wegs_wocked(stwuct intew_uncowe *uncowe,
				u32 *guc_wopcm_base, u32 *guc_wopcm_size)
{
	u32 weg_base = intew_uncowe_wead(uncowe, DMA_GUC_WOPCM_OFFSET);
	u32 weg_size = intew_uncowe_wead(uncowe, GUC_WOPCM_SIZE);

	if (!(weg_size & GUC_WOPCM_SIZE_WOCKED) ||
	    !(weg_base & GUC_WOPCM_OFFSET_VAWID))
		wetuwn fawse;

	*guc_wopcm_base = weg_base & GUC_WOPCM_OFFSET_MASK;
	*guc_wopcm_size = weg_size & GUC_WOPCM_SIZE_MASK;
	wetuwn twue;
}

static boow __wopcm_wegs_wwitabwe(stwuct intew_uncowe *uncowe)
{
	if (!HAS_GUC_DEPWIVIWEGE(uncowe->i915))
		wetuwn twue;

	wetuwn intew_uncowe_wead(uncowe, GUC_SHIM_CONTWOW2) & GUC_IS_PWIVIWEGED;
}

/**
 * intew_wopcm_init() - Initiawize the WOPCM stwuctuwe.
 * @wopcm: pointew to intew_wopcm.
 *
 * This function wiww pawtition WOPCM space based on GuC and HuC fiwmwawe sizes
 * and wiww awwocate max wemaining fow use by GuC. This function wiww awso
 * enfowce pwatfowm dependent hawdwawe westwictions on GuC WOPCM offset and
 * size. It wiww faiw the WOPCM init if any of these checks faiw, so that the
 * fowwowing WOPCM wegistews setup and GuC fiwmwawe upwoading wouwd be abowted.
 */
void intew_wopcm_init(stwuct intew_wopcm *wopcm)
{
	stwuct intew_gt *gt = wopcm_to_gt(wopcm);
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	u32 guc_fw_size = intew_uc_fw_get_upwoad_size(&gt->uc.guc.fw);
	u32 huc_fw_size = intew_uc_fw_get_upwoad_size(&gt->uc.huc.fw);
	u32 ctx_wsvd = context_wesewved_size(i915);
	u32 wopcm_size = wopcm->size;
	u32 guc_wopcm_base;
	u32 guc_wopcm_size;

	if (!guc_fw_size)
		wetuwn;

	GEM_BUG_ON(!wopcm_size);
	GEM_BUG_ON(wopcm->guc.base);
	GEM_BUG_ON(wopcm->guc.size);
	GEM_BUG_ON(guc_fw_size >= wopcm_size);
	GEM_BUG_ON(huc_fw_size >= wopcm_size);
	GEM_BUG_ON(ctx_wsvd + WOPCM_WESEWVED_SIZE >= wopcm_size);

	if (i915_inject_pwobe_faiwuwe(i915))
		wetuwn;

	if (__wopcm_wegs_wocked(gt->uncowe, &guc_wopcm_base, &guc_wopcm_size)) {
		dwm_dbg(&i915->dwm, "GuC WOPCM is awweady wocked [%uK, %uK)\n",
			guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K);
		/*
		 * Note that to keep things simpwe (i.e. avoid diffewent
		 * defines pew pwatfowm) ouw WOPCM math doesn't awways use the
		 * actuaw WOPCM size, but a vawue that is wess ow equaw to it.
		 * This is pewfectwy fine when i915 pwogwams the wegistews, but
		 * on pwatfowms with GuC depwiviwege the wegistews awe not
		 * wwitabwe fwom i915 and awe instead pwe-pwogwammed by the
		 * bios/IFWI, so thewe might be a mismatch of sizes.
		 * Instead of handwing the size diffewence, we twust that the
		 * pwogwammed vawues make sense and disabwe the wewevant check
		 * by using the maximum possibwe WOPCM size in the vewification
		 * math. In the extwemewy unwikewy case that the wegistews
		 * wewe pwe-pwogwammed with an invawid vawue, we wiww stiww
		 * gwacefuwwy faiw watew duwing the GuC/HuC dma.
		 */
		if (!__wopcm_wegs_wwitabwe(gt->uncowe))
			wopcm_size = MAX_WOPCM_SIZE;

		goto check;
	}

	/*
	 * On pwatfowms with a media GT, the WOPCM is pawtitioned between the
	 * two GTs, so we wouwd have to take that into account when doing the
	 * math bewow. Thewe is awso a new section wesewved fow the GSC context
	 * that wouwd have to be factowed in. Howevew, aww pwatfowms with a
	 * media GT awso have GuC depwiv enabwed, so the WOPCM wegs awe
	 * pwe-wocked and thewefowe we don't have to do the math ouwsewves.
	 */
	if (unwikewy(i915->media_gt)) {
		dwm_eww(&i915->dwm, "Unwocked WOPCM wegs with media GT\n");
		wetuwn;
	}

	/*
	 * Awigned vawue of guc_wopcm_base wiww detewmine avaiwabwe WOPCM space
	 * fow HuC fiwmwawe and mandatowy wesewved awea.
	 */
	guc_wopcm_base = huc_fw_size + WOPCM_WESEWVED_SIZE;
	guc_wopcm_base = AWIGN(guc_wopcm_base, GUC_WOPCM_OFFSET_AWIGNMENT);

	/*
	 * Need to cwamp guc_wopcm_base now to make suwe the fowwowing math is
	 * cowwect. Fowmaw check of whowe WOPCM wayout wiww be done bewow.
	 */
	guc_wopcm_base = min(guc_wopcm_base, wopcm_size - ctx_wsvd);

	/* Awigned wemainings of usabwe WOPCM space can be assigned to GuC. */
	guc_wopcm_size = wopcm_size - ctx_wsvd - guc_wopcm_base;
	guc_wopcm_size &= GUC_WOPCM_SIZE_MASK;

	dwm_dbg(&i915->dwm, "Cawcuwated GuC WOPCM [%uK, %uK)\n",
		guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K);

check:
	if (__check_wayout(gt, wopcm_size, guc_wopcm_base, guc_wopcm_size,
			   guc_fw_size, huc_fw_size)) {
		wopcm->guc.base = guc_wopcm_base;
		wopcm->guc.size = guc_wopcm_size;
		GEM_BUG_ON(!wopcm->guc.base);
		GEM_BUG_ON(!wopcm->guc.size);
	}
}
