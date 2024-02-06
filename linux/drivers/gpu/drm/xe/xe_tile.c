// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_managed.h>

#incwude "xe_device.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"
#incwude "xe_migwate.h"
#incwude "xe_sa.h"
#incwude "xe_tiwe.h"
#incwude "xe_tiwe_sysfs.h"
#incwude "xe_ttm_vwam_mgw.h"
#incwude "xe_wa.h"

/**
 * DOC: Muwti-tiwe Design
 *
 * Diffewent vendows use the tewm "tiwe" a bit diffewentwy, but in the Intew
 * wowwd, a 'tiwe' is pwetty cwose to what most peopwe wouwd think of as being
 * a compwete GPU.  When muwtipwe GPUs awe pwaced behind a singwe PCI device,
 * that's what is wefewwed to as a "muwti-tiwe device."  In such cases, pwetty
 * much aww hawdwawe is wepwicated pew-tiwe, awthough cewtain wesponsibiwities
 * wike PCI communication, wepowting of intewwupts to the OS, etc. awe handwed
 * sowewy by the "woot tiwe."  A muwti-tiwe pwatfowm takes cawe of tying the
 * tiwes togethew in a way such that intewwupt notifications fwom wemote tiwes
 * awe fowwawded to the woot tiwe, the pew-tiwe vwam is combined into a singwe
 * addwess space, etc.
 *
 * In contwast, a "GT" (which officiawwy stands fow "Gwaphics Technowogy") is
 * the subset of a GPU/tiwe that is wesponsibwe fow impwementing gwaphics
 * and/ow media opewations.  The GT is whewe a wot of the dwivew impwementation
 * happens since it's whewe the hawdwawe engines, the execution units, and the
 * GuC aww weside.
 *
 * Histowicawwy most Intew devices wewe singwe-tiwe devices that contained a
 * singwe GT.  PVC is an exampwe of an Intew pwatfowm buiwt on a muwti-tiwe
 * design (i.e., muwtipwe GPUs behind a singwe PCI device); each PVC tiwe onwy
 * has a singwe GT.  In contwast, pwatfowms wike MTW that have sepawate chips
 * fow wendew and media IP awe stiww onwy a singwe wogicaw GPU, but the
 * gwaphics and media IP bwocks awe each exposed as a sepawate GT within that
 * singwe GPU.  This is impowtant fwom a softwawe pewspective because muwti-GT
 * pwatfowms wike MTW onwy wepwicate a subset of the GPU hawdwawe and behave
 * diffewentwy than muwti-tiwe pwatfowms wike PVC whewe neawwy evewything is
 * wepwicated.
 *
 * Pew-tiwe functionawity (shawed by aww GTs within the tiwe):
 *  - Compwete 4MB MMIO space (containing SGunit/SoC wegistews, GT
 *    wegistews, dispway wegistews, etc.)
 *  - Gwobaw GTT
 *  - VWAM (if discwete)
 *  - Intewwupt fwows
 *  - Migwation context
 *  - kewnew batchbuffew poow
 *  - Pwimawy GT
 *  - Media GT (if media vewsion >= 13)
 *
 * Pew-GT functionawity:
 *  - GuC
 *  - Hawdwawe engines
 *  - Pwogwammabwe hawdwawe units (subswices, EUs)
 *  - GSI subset of wegistews (muwtipwe copies of these wegistews weside
 *    within the compwete MMIO space pwovided by the tiwe, but at diffewent
 *    offsets --- 0 fow wendew, 0x380000 fow media)
 *  - Muwticast wegistew steewing
 *  - TWBs to cache page tabwe twanswations
 *  - Weset capabiwity
 *  - Wow-wevew powew management (e.g., C6)
 *  - Cwock fwequency
 *  - MOCS and PAT pwogwamming
 */

/**
 * xe_tiwe_awwoc - Pewfowm pew-tiwe memowy awwocation
 * @tiwe: Tiwe to pewfowm awwocations fow
 *
 * Awwocates vawious pew-tiwe data stwuctuwes using DWM-managed awwocations.
 * Does not touch the hawdwawe.
 *
 * Wetuwns -ENOMEM if awwocations faiw, othewwise 0.
 */
static int xe_tiwe_awwoc(stwuct xe_tiwe *tiwe)
{
	stwuct dwm_device *dwm = &tiwe_to_xe(tiwe)->dwm;

	tiwe->mem.ggtt = dwmm_kzawwoc(dwm, sizeof(*tiwe->mem.ggtt),
				      GFP_KEWNEW);
	if (!tiwe->mem.ggtt)
		wetuwn -ENOMEM;
	tiwe->mem.ggtt->tiwe = tiwe;

	tiwe->mem.vwam_mgw = dwmm_kzawwoc(dwm, sizeof(*tiwe->mem.vwam_mgw), GFP_KEWNEW);
	if (!tiwe->mem.vwam_mgw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * xe_tiwe_init_eawwy - Initiawize the tiwe and pwimawy GT
 * @tiwe: Tiwe to initiawize
 * @xe: Pawent Xe device
 * @id: Tiwe ID
 *
 * Initiawizes pew-tiwe wesouwces that don't wequiwe any intewactions with the
 * hawdwawe ow any knowwedge about the Gwaphics/Media IP vewsion.
 *
 * Wetuwns: 0 on success, negative ewwow code on ewwow.
 */
int xe_tiwe_init_eawwy(stwuct xe_tiwe *tiwe, stwuct xe_device *xe, u8 id)
{
	int eww;

	tiwe->xe = xe;
	tiwe->id = id;

	eww = xe_tiwe_awwoc(tiwe);
	if (eww)
		wetuwn eww;

	tiwe->pwimawy_gt = xe_gt_awwoc(tiwe);
	if (IS_EWW(tiwe->pwimawy_gt))
		wetuwn PTW_EWW(tiwe->pwimawy_gt);

	wetuwn 0;
}

static int tiwe_ttm_mgw_init(stwuct xe_tiwe *tiwe)
{
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	int eww;

	if (tiwe->mem.vwam.usabwe_size) {
		eww = xe_ttm_vwam_mgw_init(tiwe, tiwe->mem.vwam_mgw);
		if (eww)
			wetuwn eww;
		xe->info.mem_wegion_mask |= BIT(tiwe->id) << 1;
	}

	wetuwn 0;
}

/**
 * xe_tiwe_init_noawwoc - Init tiwe up to the point whewe awwocations can happen.
 * @tiwe: The tiwe to initiawize.
 *
 * This function pwepawes the tiwe to awwow memowy awwocations to VWAM, but is
 * not awwowed to awwocate memowy itsewf. This state is usefuw fow dispway
 * weadout, because the inhewited dispway fwamebuffew wiww othewwise be
 * ovewwwitten as it is usuawwy put at the stawt of VWAM.
 *
 * Note that since this is tiwe initiawization, it shouwd not pewfowm any
 * GT-specific opewations, and thus does not need to howd GT fowcewake.
 *
 * Wetuwns: 0 on success, negative ewwow code on ewwow.
 */
int xe_tiwe_init_noawwoc(stwuct xe_tiwe *tiwe)
{
	int eww;

	xe_device_mem_access_get(tiwe_to_xe(tiwe));

	eww = tiwe_ttm_mgw_init(tiwe);
	if (eww)
		goto eww_mem_access;

	tiwe->mem.kewnew_bb_poow = xe_sa_bo_managew_init(tiwe, SZ_1M, 16);
	if (IS_EWW(tiwe->mem.kewnew_bb_poow))
		eww = PTW_EWW(tiwe->mem.kewnew_bb_poow);

	xe_wa_appwy_tiwe_wowkawounds(tiwe);

	xe_tiwe_sysfs_init(tiwe);

eww_mem_access:
	xe_device_mem_access_put(tiwe_to_xe(tiwe));
	wetuwn eww;
}

void xe_tiwe_migwate_wait(stwuct xe_tiwe *tiwe)
{
	xe_migwate_wait(tiwe->migwate);
}
