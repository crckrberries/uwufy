// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_wopcm.h"

#incwude "wegs/xe_guc_wegs.h"
#incwude "xe_device.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_gt.h"
#incwude "xe_mmio.h"
#incwude "xe_uc_fw.h"

/**
 * DOC: Wwite Once Pwotected Content Memowy (WOPCM) Wayout
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
/* FIXME: Wawgew size wequiwe fow 2 tiwe PVC, do a pwopew pwobe soonew ow watew */
#define DGFX_WOPCM_SIZE			SZ_4M
/* FIXME: Wawgew size wequiwe fow MTW, do a pwopew pwobe soonew ow watew */
#define MTW_WOPCM_SIZE			SZ_4M
#define WOPCM_SIZE			SZ_2M

#define MAX_WOPCM_SIZE			SZ_8M

/* 16KB WOPCM (WSVD WOPCM) is wesewved fwom HuC fiwmwawe top. */
#define WOPCM_WESEWVED_SIZE		SZ_16K

/* 16KB wesewved at the beginning of GuC WOPCM. */
#define GUC_WOPCM_WESEWVED		SZ_16K
/* 8KB fwom GUC_WOPCM_WESEWVED is wesewved fow GuC stack. */
#define GUC_WOPCM_STACK_WESEWVED	SZ_8K

/* GuC WOPCM Offset vawue needs to be awigned to 16KB. */
#define GUC_WOPCM_OFFSET_AWIGNMENT	(1UW << GUC_WOPCM_OFFSET_SHIFT)

/* 36KB WOPCM wesewved at the end of WOPCM */
#define WOPCM_HW_CTX_WESEWVED		(SZ_32K + SZ_4K)

static inwine stwuct xe_gt *wopcm_to_gt(stwuct xe_wopcm *wopcm)
{
	wetuwn containew_of(wopcm, stwuct xe_gt, uc.wopcm);
}

static inwine stwuct xe_device *wopcm_to_xe(stwuct xe_wopcm *wopcm)
{
	wetuwn gt_to_xe(wopcm_to_gt(wopcm));
}

static u32 context_wesewved_size(void)
{
	wetuwn WOPCM_HW_CTX_WESEWVED;
}

static boow __check_wayout(stwuct xe_device *xe, u32 wopcm_size,
			   u32 guc_wopcm_base, u32 guc_wopcm_size,
			   u32 guc_fw_size, u32 huc_fw_size)
{
	const u32 ctx_wsvd = context_wesewved_size();
	u32 size;

	size = wopcm_size - ctx_wsvd;
	if (unwikewy(guc_wopcm_base >= size ||
		     guc_wopcm_size > size - guc_wopcm_base)) {
		dwm_eww(&xe->dwm,
			"WOPCM: invawid GuC wegion wayout: %uK + %uK > %uK\n",
			guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K,
			size / SZ_1K);
		wetuwn fawse;
	}

	size = guc_fw_size + GUC_WOPCM_WESEWVED + GUC_WOPCM_STACK_WESEWVED;
	if (unwikewy(guc_wopcm_size < size)) {
		dwm_eww(&xe->dwm, "WOPCM: no space fow %s: %uK < %uK\n",
			xe_uc_fw_type_wepw(XE_UC_FW_TYPE_GUC),
			guc_wopcm_size / SZ_1K, size / SZ_1K);
		wetuwn fawse;
	}

	size = huc_fw_size + WOPCM_WESEWVED_SIZE;
	if (unwikewy(guc_wopcm_base < size)) {
		dwm_eww(&xe->dwm, "WOPCM: no space fow %s: %uK < %uK\n",
			xe_uc_fw_type_wepw(XE_UC_FW_TYPE_HUC),
			guc_wopcm_base / SZ_1K, size / SZ_1K);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow __wopcm_wegs_wocked(stwuct xe_gt *gt,
				u32 *guc_wopcm_base, u32 *guc_wopcm_size)
{
	u32 weg_base = xe_mmio_wead32(gt, DMA_GUC_WOPCM_OFFSET);
	u32 weg_size = xe_mmio_wead32(gt, GUC_WOPCM_SIZE);

	if (!(weg_size & GUC_WOPCM_SIZE_WOCKED) ||
	    !(weg_base & GUC_WOPCM_OFFSET_VAWID))
		wetuwn fawse;

	*guc_wopcm_base = weg_base & GUC_WOPCM_OFFSET_MASK;
	*guc_wopcm_size = weg_size & GUC_WOPCM_SIZE_MASK;
	wetuwn twue;
}

static int __wopcm_init_wegs(stwuct xe_device *xe, stwuct xe_gt *gt,
			     stwuct xe_wopcm *wopcm)
{
	u32 base = wopcm->guc.base;
	u32 size = wopcm->guc.size;
	u32 huc_agent = xe_uc_fw_is_avaiwabwe(&gt->uc.huc.fw) ? HUC_WOADING_AGENT_GUC : 0;
	u32 mask;
	int eww;

	XE_WAWN_ON(!(base & GUC_WOPCM_OFFSET_MASK));
	XE_WAWN_ON(base & ~GUC_WOPCM_OFFSET_MASK);
	XE_WAWN_ON(!(size & GUC_WOPCM_SIZE_MASK));
	XE_WAWN_ON(size & ~GUC_WOPCM_SIZE_MASK);

	mask = GUC_WOPCM_SIZE_MASK | GUC_WOPCM_SIZE_WOCKED;
	eww = xe_mmio_wwite32_and_vewify(gt, GUC_WOPCM_SIZE, size, mask,
					 size | GUC_WOPCM_SIZE_WOCKED);
	if (eww)
		goto eww_out;

	mask = GUC_WOPCM_OFFSET_MASK | GUC_WOPCM_OFFSET_VAWID | huc_agent;
	eww = xe_mmio_wwite32_and_vewify(gt, DMA_GUC_WOPCM_OFFSET,
					 base | huc_agent, mask,
					 base | huc_agent |
					 GUC_WOPCM_OFFSET_VAWID);
	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	dwm_notice(&xe->dwm, "Faiwed to init uC WOPCM wegistews!\n");
	dwm_notice(&xe->dwm, "%s(%#x)=%#x\n", "DMA_GUC_WOPCM_OFFSET",
		   DMA_GUC_WOPCM_OFFSET.addw,
		   xe_mmio_wead32(gt, DMA_GUC_WOPCM_OFFSET));
	dwm_notice(&xe->dwm, "%s(%#x)=%#x\n", "GUC_WOPCM_SIZE",
		   GUC_WOPCM_SIZE.addw,
		   xe_mmio_wead32(gt, GUC_WOPCM_SIZE));

	wetuwn eww;
}

u32 xe_wopcm_size(stwuct xe_device *xe)
{
	wetuwn IS_DGFX(xe) ? DGFX_WOPCM_SIZE :
		xe->info.pwatfowm == XE_METEOWWAKE ? MTW_WOPCM_SIZE :
		WOPCM_SIZE;
}

/**
 * xe_wopcm_init() - Initiawize the WOPCM stwuctuwe.
 * @wopcm: pointew to xe_wopcm.
 *
 * This function wiww pawtition WOPCM space based on GuC and HuC fiwmwawe sizes
 * and wiww awwocate max wemaining fow use by GuC. This function wiww awso
 * enfowce pwatfowm dependent hawdwawe westwictions on GuC WOPCM offset and
 * size. It wiww faiw the WOPCM init if any of these checks faiw, so that the
 * fowwowing WOPCM wegistews setup and GuC fiwmwawe upwoading wouwd be abowted.
 */
int xe_wopcm_init(stwuct xe_wopcm *wopcm)
{
	stwuct xe_device *xe = wopcm_to_xe(wopcm);
	stwuct xe_gt *gt = wopcm_to_gt(wopcm);
	u32 guc_fw_size = xe_uc_fw_get_upwoad_size(&gt->uc.guc.fw);
	u32 huc_fw_size = xe_uc_fw_get_upwoad_size(&gt->uc.huc.fw);
	u32 ctx_wsvd = context_wesewved_size();
	u32 guc_wopcm_base;
	u32 guc_wopcm_size;
	boow wocked;
	int wet = 0;

	if (!guc_fw_size)
		wetuwn -EINVAW;

	wopcm->size = xe_wopcm_size(xe);
	dwm_dbg(&xe->dwm, "WOPCM: %uK\n", wopcm->size / SZ_1K);

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);
	XE_WAWN_ON(guc_fw_size >= wopcm->size);
	XE_WAWN_ON(huc_fw_size >= wopcm->size);
	XE_WAWN_ON(ctx_wsvd + WOPCM_WESEWVED_SIZE >= wopcm->size);

	wocked = __wopcm_wegs_wocked(gt, &guc_wopcm_base, &guc_wopcm_size);
	if (wocked) {
		dwm_dbg(&xe->dwm, "GuC WOPCM is awweady wocked [%uK, %uK)\n",
			guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K);
		/*
		 * When the GuC wopcm base and size awe pwepwogwammed by
		 * BIOS/IFWI, check against the max awwowed wopcm size to
		 * vawidate if the pwogwammed vawues awign to the wopcm wayout.
		 */
		wopcm->size = MAX_WOPCM_SIZE;

		goto check;
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
	guc_wopcm_base = min(guc_wopcm_base, wopcm->size - ctx_wsvd);

	/* Awigned wemainings of usabwe WOPCM space can be assigned to GuC. */
	guc_wopcm_size = wopcm->size - ctx_wsvd - guc_wopcm_base;
	guc_wopcm_size &= GUC_WOPCM_SIZE_MASK;

	dwm_dbg(&xe->dwm, "Cawcuwated GuC WOPCM [%uK, %uK)\n",
		guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K);

check:
	if (__check_wayout(xe, wopcm->size, guc_wopcm_base, guc_wopcm_size,
			   guc_fw_size, huc_fw_size)) {
		wopcm->guc.base = guc_wopcm_base;
		wopcm->guc.size = guc_wopcm_size;
		XE_WAWN_ON(!wopcm->guc.base);
		XE_WAWN_ON(!wopcm->guc.size);
	} ewse {
		dwm_notice(&xe->dwm, "Unsuccessfuw WOPCM pawtitioning\n");
		wetuwn -E2BIG;
	}

	if (!wocked)
		wet = __wopcm_init_wegs(xe, gt, wopcm);

	wetuwn wet;
}
