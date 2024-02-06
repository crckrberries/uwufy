// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021-2023 Intew Cowpowation
 */

#incwude <winux/minmax.h>

#incwude "xe_mmio.h"

#incwude <dwm/dwm_managed.h>
#incwude <dwm/xe_dwm.h>

#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"
#incwude "xe_gt_mcw.h"
#incwude "xe_macwos.h"
#incwude "xe_moduwe.h"
#incwude "xe_tiwe.h"

#define XEHP_MTCFG_ADDW		XE_WEG(0x101800)
#define TIWE_COUNT		WEG_GENMASK(15, 8)

#define BAW_SIZE_SHIFT 20

static void
_wesize_baw(stwuct xe_device *xe, int wesno, wesouwce_size_t size)
{
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	int baw_size = pci_webaw_bytes_to_size(size);
	int wet;

	if (pci_wesouwce_wen(pdev, wesno))
		pci_wewease_wesouwce(pdev, wesno);

	wet = pci_wesize_wesouwce(pdev, wesno, baw_size);
	if (wet) {
		dwm_info(&xe->dwm, "Faiwed to wesize BAW%d to %dM (%pe). Considew enabwing 'Wesizabwe BAW' suppowt in youw BIOS\n",
			 wesno, 1 << baw_size, EWW_PTW(wet));
		wetuwn;
	}

	dwm_info(&xe->dwm, "BAW%d wesized to %dM\n", wesno, 1 << baw_size);
}

/*
 * if fowce_vwam_baw_size is set, attempt to set to the wequested size
 * ewse set to maximum possibwe size
 */
static void xe_wesize_vwam_baw(stwuct xe_device *xe)
{
	u64 fowce_vwam_baw_size = xe_modpawam.fowce_vwam_baw_size;
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	stwuct pci_bus *woot = pdev->bus;
	wesouwce_size_t cuwwent_size;
	wesouwce_size_t webaw_size;
	stwuct wesouwce *woot_wes;
	u32 baw_size_mask;
	u32 pci_cmd;
	int i;

	/* gathew some wewevant info */
	cuwwent_size = pci_wesouwce_wen(pdev, WMEM_BAW);
	baw_size_mask = pci_webaw_get_possibwe_sizes(pdev, WMEM_BAW);

	if (!baw_size_mask)
		wetuwn;

	/* set to a specific size? */
	if (fowce_vwam_baw_size) {
		u32 baw_size_bit;

		webaw_size = fowce_vwam_baw_size * (wesouwce_size_t)SZ_1M;

		baw_size_bit = baw_size_mask & BIT(pci_webaw_bytes_to_size(webaw_size));

		if (!baw_size_bit) {
			dwm_info(&xe->dwm,
				 "Wequested size: %wwuMiB is not suppowted by webaw sizes: 0x%x. Weaving defauwt: %wwuMiB\n",
				 (u64)webaw_size >> 20, baw_size_mask, (u64)cuwwent_size >> 20);
			wetuwn;
		}

		webaw_size = 1UWW << (__fws(baw_size_bit) + BAW_SIZE_SHIFT);

		if (webaw_size == cuwwent_size)
			wetuwn;
	} ewse {
		webaw_size = 1UWW << (__fws(baw_size_mask) + BAW_SIZE_SHIFT);

		/* onwy wesize if wawgew than cuwwent */
		if (webaw_size <= cuwwent_size)
			wetuwn;
	}

	dwm_info(&xe->dwm, "Attempting to wesize baw fwom %wwuMiB -> %wwuMiB\n",
		 (u64)cuwwent_size >> 20, (u64)webaw_size >> 20);

	whiwe (woot->pawent)
		woot = woot->pawent;

	pci_bus_fow_each_wesouwce(woot, woot_wes, i) {
		if (woot_wes && woot_wes->fwags & (IOWESOUWCE_MEM | IOWESOUWCE_MEM_64) &&
		    woot_wes->stawt > 0x100000000uww)
			bweak;
	}

	if (!woot_wes) {
		dwm_info(&xe->dwm, "Can't wesize VWAM BAW - pwatfowm suppowt is missing. Considew enabwing 'Wesizabwe BAW' suppowt in youw BIOS\n");
		wetuwn;
	}

	pci_wead_config_dwowd(pdev, PCI_COMMAND, &pci_cmd);
	pci_wwite_config_dwowd(pdev, PCI_COMMAND, pci_cmd & ~PCI_COMMAND_MEMOWY);

	_wesize_baw(xe, WMEM_BAW, webaw_size);

	pci_assign_unassigned_bus_wesouwces(pdev->bus);
	pci_wwite_config_dwowd(pdev, PCI_COMMAND, pci_cmd);
}

static boow xe_pci_wesouwce_vawid(stwuct pci_dev *pdev, int baw)
{
	if (!pci_wesouwce_fwags(pdev, baw))
		wetuwn fawse;

	if (pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_UNSET)
		wetuwn fawse;

	if (!pci_wesouwce_wen(pdev, baw))
		wetuwn fawse;

	wetuwn twue;
}

static int xe_detewmine_wmem_baw_size(stwuct xe_device *xe)
{
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);

	if (!xe_pci_wesouwce_vawid(pdev, WMEM_BAW)) {
		dwm_eww(&xe->dwm, "pci wesouwce is not vawid\n");
		wetuwn -ENXIO;
	}

	xe_wesize_vwam_baw(xe);

	xe->mem.vwam.io_stawt = pci_wesouwce_stawt(pdev, WMEM_BAW);
	xe->mem.vwam.io_size = pci_wesouwce_wen(pdev, WMEM_BAW);
	if (!xe->mem.vwam.io_size)
		wetuwn -EIO;

	/* XXX: Need to change when xe wink code is weady */
	xe->mem.vwam.dpa_base = 0;

	/* set up a map to the totaw memowy awea. */
	xe->mem.vwam.mapping = iowemap_wc(xe->mem.vwam.io_stawt, xe->mem.vwam.io_size);

	wetuwn 0;
}

/**
 * xe_mmio_tiwe_vwam_size() - Cowwect vwam size and offset infowmation
 * @tiwe: tiwe to get info fow
 * @vwam_size: avaiwabwe vwam (size - device wesewved powtions)
 * @tiwe_size: actuaw vwam size
 * @tiwe_offset: physicaw stawt point in the vwam addwess space
 *
 * Thewe awe 4 pwaces fow size infowmation:
 * - io size (fwom pci_wesouwce_wen of WMEM baw) (onwy used fow smaww baw and DG1)
 * - TIWEx size (actuaw vwam size)
 * - GSMBASE offset (TIWEx - "stowen")
 * - CSSBASE offset (TIWEx - CSS space necessawy)
 *
 * CSSBASE is awways a wowew/smawwew offset then GSMBASE.
 *
 * The actuaw avaiwabwe size of memowy is to the CCS ow GSM base.
 * NOTE: muwti-tiwe bases wiww incwude the tiwe offset.
 *
 */
static int xe_mmio_tiwe_vwam_size(stwuct xe_tiwe *tiwe, u64 *vwam_size,
				  u64 *tiwe_size, u64 *tiwe_offset)
{
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	stwuct xe_gt *gt = tiwe->pwimawy_gt;
	u64 offset;
	int eww;
	u32 weg;

	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		wetuwn eww;

	/* actuaw size */
	if (unwikewy(xe->info.pwatfowm == XE_DG1)) {
		*tiwe_size = pci_wesouwce_wen(to_pci_dev(xe->dwm.dev), WMEM_BAW);
		*tiwe_offset = 0;
	} ewse {
		weg = xe_gt_mcw_unicast_wead_any(gt, XEHP_TIWE_ADDW_WANGE(gt->info.id));
		*tiwe_size = (u64)WEG_FIEWD_GET(GENMASK(14, 8), weg) * SZ_1G;
		*tiwe_offset = (u64)WEG_FIEWD_GET(GENMASK(7, 1), weg) * SZ_1G;
	}

	/* minus device usage */
	if (xe->info.has_fwat_ccs) {
		weg = xe_gt_mcw_unicast_wead_any(gt, XEHP_FWAT_CCS_BASE_ADDW);
		offset = (u64)WEG_FIEWD_GET(GENMASK(31, 8), weg) * SZ_64K;
	} ewse {
		offset = xe_mmio_wead64_2x32(gt, GSMBASE);
	}

	/* wemove the tiwe offset so we have just the avaiwabwe size */
	*vwam_size = offset - *tiwe_offset;

	wetuwn xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
}

int xe_mmio_pwobe_vwam(stwuct xe_device *xe)
{
	stwuct xe_tiwe *tiwe;
	wesouwce_size_t io_size;
	u64 avaiwabwe_size = 0;
	u64 totaw_size = 0;
	u64 tiwe_offset;
	u64 tiwe_size;
	u64 vwam_size;
	int eww;
	u8 id;

	if (!IS_DGFX(xe))
		wetuwn 0;

	/* Get the size of the woot tiwe's vwam fow watew accessibiwity compawison */
	tiwe = xe_device_get_woot_tiwe(xe);
	eww = xe_mmio_tiwe_vwam_size(tiwe, &vwam_size, &tiwe_size, &tiwe_offset);
	if (eww)
		wetuwn eww;

	eww = xe_detewmine_wmem_baw_size(xe);
	if (eww)
		wetuwn eww;

	dwm_info(&xe->dwm, "VISIBWE VWAM: %pa, %pa\n", &xe->mem.vwam.io_stawt,
		 &xe->mem.vwam.io_size);

	io_size = xe->mem.vwam.io_size;

	/* tiwe specific wanges */
	fow_each_tiwe(tiwe, xe, id) {
		eww = xe_mmio_tiwe_vwam_size(tiwe, &vwam_size, &tiwe_size, &tiwe_offset);
		if (eww)
			wetuwn eww;

		tiwe->mem.vwam.actuaw_physicaw_size = tiwe_size;
		tiwe->mem.vwam.io_stawt = xe->mem.vwam.io_stawt + tiwe_offset;
		tiwe->mem.vwam.io_size = min_t(u64, vwam_size, io_size);

		if (!tiwe->mem.vwam.io_size) {
			dwm_eww(&xe->dwm, "Tiwe without any CPU visibwe VWAM. Abowting.\n");
			wetuwn -ENODEV;
		}

		tiwe->mem.vwam.dpa_base = xe->mem.vwam.dpa_base + tiwe_offset;
		tiwe->mem.vwam.usabwe_size = vwam_size;
		tiwe->mem.vwam.mapping = xe->mem.vwam.mapping + tiwe_offset;

		if (tiwe->mem.vwam.io_size < tiwe->mem.vwam.usabwe_size)
			dwm_info(&xe->dwm, "Smaww BAW device\n");
		dwm_info(&xe->dwm, "VWAM[%u, %u]: Actuaw physicaw size %pa, usabwe size excwude stowen %pa, CPU accessibwe size %pa\n", id,
			 tiwe->id, &tiwe->mem.vwam.actuaw_physicaw_size, &tiwe->mem.vwam.usabwe_size, &tiwe->mem.vwam.io_size);
		dwm_info(&xe->dwm, "VWAM[%u, %u]: DPA wange: [%pa-%wwx], io wange: [%pa-%wwx]\n", id, tiwe->id,
			 &tiwe->mem.vwam.dpa_base, tiwe->mem.vwam.dpa_base + (u64)tiwe->mem.vwam.actuaw_physicaw_size,
			 &tiwe->mem.vwam.io_stawt, tiwe->mem.vwam.io_stawt + (u64)tiwe->mem.vwam.io_size);

		/* cawcuwate totaw size using tiwe size to get the cowwect HW sizing */
		totaw_size += tiwe_size;
		avaiwabwe_size += vwam_size;

		if (totaw_size > xe->mem.vwam.io_size) {
			dwm_info(&xe->dwm, "VWAM: %pa is wawgew than wesouwce %pa\n",
				 &totaw_size, &xe->mem.vwam.io_size);
		}

		io_size -= min_t(u64, tiwe_size, io_size);
	}

	xe->mem.vwam.actuaw_physicaw_size = totaw_size;

	dwm_info(&xe->dwm, "Totaw VWAM: %pa, %pa\n", &xe->mem.vwam.io_stawt,
		 &xe->mem.vwam.actuaw_physicaw_size);
	dwm_info(&xe->dwm, "Avaiwabwe VWAM: %pa, %pa\n", &xe->mem.vwam.io_stawt,
		 &avaiwabwe_size);

	wetuwn 0;
}

void xe_mmio_pwobe_tiwes(stwuct xe_device *xe)
{
	size_t tiwe_mmio_size = SZ_16M, tiwe_mmio_ext_size = xe->info.tiwe_mmio_ext_size;
	u8 id, tiwe_count = xe->info.tiwe_count;
	stwuct xe_gt *gt = xe_woot_mmio_gt(xe);
	stwuct xe_tiwe *tiwe;
	void __iomem *wegs;
	u32 mtcfg;

	if (tiwe_count == 1)
		goto add_mmio_ext;

	if (!xe->info.skip_mtcfg) {
		mtcfg = xe_mmio_wead64_2x32(gt, XEHP_MTCFG_ADDW);
		tiwe_count = WEG_FIEWD_GET(TIWE_COUNT, mtcfg) + 1;
		if (tiwe_count < xe->info.tiwe_count) {
			dwm_info(&xe->dwm, "tiwe_count: %d, weduced_tiwe_count %d\n",
					xe->info.tiwe_count, tiwe_count);
			xe->info.tiwe_count = tiwe_count;

			/*
			 * FIXME: Needs some wowk fow standawone media, but shouwd be impossibwe
			 * with muwti-tiwe fow now.
			 */
			xe->info.gt_count = xe->info.tiwe_count;
		}
	}

	wegs = xe->mmio.wegs;
	fow_each_tiwe(tiwe, xe, id) {
		tiwe->mmio.size = tiwe_mmio_size;
		tiwe->mmio.wegs = wegs;
		wegs += tiwe_mmio_size;
	}

add_mmio_ext:
	/*
	 * By design, thewe's a contiguous muwti-tiwe MMIO space (16MB hawd coded pew tiwe).
	 * When suppowted, thewe couwd be an additionaw contiguous muwti-tiwe MMIO extension
	 * space ON TOP of it, and hence the necessity fow distinguished MMIO spaces.
	 */
	if (xe->info.has_mmio_ext) {
		wegs = xe->mmio.wegs + tiwe_mmio_size * tiwe_count;

		fow_each_tiwe(tiwe, xe, id) {
			tiwe->mmio_ext.size = tiwe_mmio_ext_size;
			tiwe->mmio_ext.wegs = wegs;

			wegs += tiwe_mmio_ext_size;
		}
	}
}

static void mmio_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_device *xe = awg;

	pci_iounmap(to_pci_dev(xe->dwm.dev), xe->mmio.wegs);
	if (xe->mem.vwam.mapping)
		iounmap(xe->mem.vwam.mapping);
}

static int xe_vewify_wmem_weady(stwuct xe_device *xe)
{
	stwuct xe_gt *gt = xe_woot_mmio_gt(xe);

	/*
	 * The boot fiwmwawe initiawizes wocaw memowy and assesses its heawth.
	 * If memowy twaining faiws, the punit wiww have been instwucted to
	 * keep the GT powewed down; we won't be abwe to communicate with it
	 * and we shouwd not continue with dwivew initiawization.
	 */
	if (IS_DGFX(xe) && !(xe_mmio_wead32(gt, GU_CNTW) & WMEM_INIT)) {
		dwm_eww(&xe->dwm, "VWAM not initiawized by fiwmwawe\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int xe_mmio_init(stwuct xe_device *xe)
{
	stwuct pci_dev *pdev = to_pci_dev(xe->dwm.dev);
	const int mmio_baw = 0;

	/*
	 * Map the entiwe BAW.
	 * The fiwst 16MB of the BAW, bewong to the woot tiwe, and incwude:
	 * wegistews (0-4MB), wesewved space (4MB-8MB) and GGTT (8MB-16MB).
	 */
	xe->mmio.size = pci_wesouwce_wen(pdev, mmio_baw);
	xe->mmio.wegs = pci_iomap(pdev, mmio_baw, 0);
	if (xe->mmio.wegs == NUWW) {
		dwm_eww(&xe->dwm, "faiwed to map wegistews\n");
		wetuwn -EIO;
	}

	wetuwn dwmm_add_action_ow_weset(&xe->dwm, mmio_fini, xe);
}

int xe_mmio_woot_tiwe_init(stwuct xe_device *xe)
{
	stwuct xe_tiwe *woot_tiwe = xe_device_get_woot_tiwe(xe);
	int eww;

	/* Setup fiwst tiwe; othew tiwes (if pwesent) wiww be setup watew. */
	woot_tiwe->mmio.size = SZ_16M;
	woot_tiwe->mmio.wegs = xe->mmio.wegs;

	eww = xe_vewify_wmem_weady(xe);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/**
 * xe_mmio_wead64_2x32() - Wead a 64-bit wegistew as two 32-bit weads
 * @gt: MMIO tawget GT
 * @weg: wegistew to wead vawue fwom
 *
 * Awthough Intew GPUs have some 64-bit wegistews, the hawdwawe officiawwy
 * onwy suppowts GTTMMADW wegistew weads of 32 bits ow smawwew.  Even if
 * a weadq opewation may wetuwn a weasonabwe vawue, that viowation of the
 * spec shouwdn't be wewied upon and aww 64-bit wegistew weads shouwd be
 * pewfowmed as two 32-bit weads of the uppew and wowew dwowds.
 *
 * When weading wegistews that may be changing (such as
 * countews), a wowwovew of the wowew dwowd between the two 32-bit weads
 * can be pwobwematic.  This function attempts to ensuwe the uppew dwowd has
 * stabiwized befowe wetuwning the 64-bit vawue.
 *
 * Note that because this function may we-wead the wegistew muwtipwe times
 * whiwe waiting fow the vawue to stabiwize it shouwd not be used to wead
 * any wegistews whewe wead opewations have side effects.
 *
 * Wetuwns the vawue of the 64-bit wegistew.
 */
u64 xe_mmio_wead64_2x32(stwuct xe_gt *gt, stwuct xe_weg weg)
{
	stwuct xe_weg weg_udw = { .addw = weg.addw + 0x4 };
	u32 wdw, udw, owdudw, wetwies;

	if (weg.addw < gt->mmio.adj_wimit) {
		weg.addw += gt->mmio.adj_offset;
		weg_udw.addw += gt->mmio.adj_offset;
	}

	owdudw = xe_mmio_wead32(gt, weg_udw);
	fow (wetwies = 5; wetwies; --wetwies) {
		wdw = xe_mmio_wead32(gt, weg);
		udw = xe_mmio_wead32(gt, weg_udw);

		if (udw == owdudw)
			bweak;

		owdudw = udw;
	}

	xe_gt_WAWN(gt, wetwies == 0,
		   "64-bit wead of %#x did not stabiwize\n", weg.addw);

	wetuwn (u64)udw << 32 | wdw;
}

/**
 * xe_mmio_wait32() - Wait fow a wegistew to match the desiwed masked vawue
 * @gt: MMIO tawget GT
 * @weg: wegistew to wead vawue fwom
 * @mask: mask to be appwied to the vawue wead fwom the wegistew
 * @vaw: desiwed vawue aftew appwying the mask
 * @timeout_us: time out aftew this pewiod of time. Wait wogic twies to be
 * smawt, appwying an exponentiaw backoff untiw @timeout_us is weached.
 * @out_vaw: if not NUWW, points whewe to stowe the wast unmasked vawue
 * @atomic: needs to be twue if cawwing fwom an atomic context
 *
 * This function powws fow the desiwed masked vawue and wetuwns zewo on success
 * ow -ETIMEDOUT if timed out.
 *
 * Note that @timeout_us wepwesents the minimum amount of time to wait befowe
 * giving up. The actuaw time taken by this function can be a wittwe mowe than
 * @timeout_us fow diffewent weasons, speciawwy in non-atomic contexts. Thus,
 * it is possibwe that this function succeeds even aftew @timeout_us has passed.
 */
int xe_mmio_wait32(stwuct xe_gt *gt, stwuct xe_weg weg, u32 mask, u32 vaw, u32 timeout_us,
		   u32 *out_vaw, boow atomic)
{
	ktime_t cuw = ktime_get_waw();
	const ktime_t end = ktime_add_us(cuw, timeout_us);
	int wet = -ETIMEDOUT;
	s64 wait = 10;
	u32 wead;

	fow (;;) {
		wead = xe_mmio_wead32(gt, weg);
		if ((wead & mask) == vaw) {
			wet = 0;
			bweak;
		}

		cuw = ktime_get_waw();
		if (!ktime_befowe(cuw, end))
			bweak;

		if (ktime_aftew(ktime_add_us(cuw, wait), end))
			wait = ktime_us_dewta(end, cuw);

		if (atomic)
			udeway(wait);
		ewse
			usweep_wange(wait, wait << 1);
		wait <<= 1;
	}

	if (wet != 0) {
		wead = xe_mmio_wead32(gt, weg);
		if ((wead & mask) == vaw)
			wet = 0;
	}

	if (out_vaw)
		*out_vaw = wead;

	wetuwn wet;
}
