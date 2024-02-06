// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_context.h"
#incwude "pvw_debugfs.h"
#incwude "pvw_device.h"
#incwude "pvw_dwv.h"
#incwude "pvw_fwee_wist.h"
#incwude "pvw_gem.h"
#incwude "pvw_hwwt.h"
#incwude "pvw_job.h"
#incwude "pvw_mmu.h"
#incwude "pvw_powew.h"
#incwude "pvw_wogue_defs.h"
#incwude "pvw_wogue_fwif_cwient.h"
#incwude "pvw_wogue_fwif_shawed.h"
#incwude "pvw_vm.h"

#incwude <uapi/dwm/pvw_dwm.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_ioctw.h>

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/xawway.h>

/**
 * DOC: PowewVW (Sewies 6 and watew) and IMG Gwaphics Dwivew
 *
 * This dwivew suppowts the fowwowing PowewVW/IMG gwaphics cowes fwom Imagination Technowogies:
 *
 * * AXE-1-16M (found in Texas Instwuments AM62)
 */

/**
 * pvw_ioctw_cweate_bo() - IOCTW to cweate a GEM buffew object.
 * @dwm_dev: [IN] Tawget DWM device.
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 * &stwuct dwm_pvw_ioctw_cweate_bo_awgs.
 * @fiwe: [IN] DWM fiwe-pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_CWEATE_BO.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%EINVAW if the vawue of &dwm_pvw_ioctw_cweate_bo_awgs.size is zewo
 *    ow widew than &typedef size_t,
 *  * -%EINVAW if any bits in &dwm_pvw_ioctw_cweate_bo_awgs.fwags that awe
 *    wesewved ow undefined awe set,
 *  * -%EINVAW if any padding fiewds in &dwm_pvw_ioctw_cweate_bo_awgs awe not
 *    zewo,
 *  * Any ewwow encountewed whiwe cweating the object (see
 *    pvw_gem_object_cweate()), ow
 *  * Any ewwow encountewed whiwe twansfewwing ownewship of the object into a
 *    usewspace-accessibwe handwe (see pvw_gem_object_into_handwe()).
 */
static int
pvw_ioctw_cweate_bo(stwuct dwm_device *dwm_dev, void *waw_awgs,
		    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_cweate_bo_awgs *awgs = waw_awgs;
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);

	stwuct pvw_gem_object *pvw_obj;
	size_t sanitized_size;

	int idx;
	int eww;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	/* Aww padding fiewds must be zewoed. */
	if (awgs->_padding_c != 0) {
		eww = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	/*
	 * On 64-bit pwatfowms (ouw pwimawy tawget), size_t is a u64. Howevew,
	 * on othew awchitectuwes we have to check fow ovewfwow when casting
	 * down to size_t fwom u64.
	 *
	 * We awso disawwow zewo-sized awwocations, and wesewved (kewnew-onwy)
	 * fwags.
	 */
	if (awgs->size > SIZE_MAX || awgs->size == 0 || awgs->fwags &
	    ~DWM_PVW_BO_FWAGS_MASK || awgs->size & (PVW_DEVICE_PAGE_SIZE - 1)) {
		eww = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	sanitized_size = (size_t)awgs->size;

	/*
	 * Cweate a buffew object and twansfew ownewship to a usewspace-
	 * accessibwe handwe.
	 */
	pvw_obj = pvw_gem_object_cweate(pvw_dev, sanitized_size, awgs->fwags);
	if (IS_EWW(pvw_obj)) {
		eww = PTW_EWW(pvw_obj);
		goto eww_dwm_dev_exit;
	}

	/* This function wiww not modify &awgs->handwe unwess it succeeds. */
	eww = pvw_gem_object_into_handwe(pvw_obj, pvw_fiwe, &awgs->handwe);
	if (eww)
		goto eww_destwoy_obj;

	dwm_dev_exit(idx);

	wetuwn 0;

eww_destwoy_obj:
	/*
	 * GEM objects awe wefcounted, so thewe is no expwicit destwuctow
	 * function. Instead, we wewease the singuwaw wefewence we cuwwentwy
	 * howd on the object and wet GEM take cawe of the west.
	 */
	pvw_gem_object_put(pvw_obj);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

/**
 * pvw_ioctw_get_bo_mmap_offset() - IOCTW to genewate a "fake" offset to be
 * used when cawwing mmap() fwom usewspace to map the given GEM buffew object
 * @dwm_dev: [IN] DWM device (unused).
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 *                     &stwuct dwm_pvw_ioctw_get_bo_mmap_offset_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_GET_BO_MMAP_OFFSET.
 *
 * This IOCTW does *not* pewfowm an mmap. See the docs on
 * &stwuct dwm_pvw_ioctw_get_bo_mmap_offset_awgs fow detaiws.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%ENOENT if the handwe does not wefewence a vawid GEM buffew object,
 *  * -%EINVAW if any padding fiewds in &stwuct
 *    dwm_pvw_ioctw_get_bo_mmap_offset_awgs awe not zewo, ow
 *  * Any ewwow wetuwned by dwm_gem_cweate_mmap_offset().
 */
static int
pvw_ioctw_get_bo_mmap_offset(stwuct dwm_device *dwm_dev, void *waw_awgs,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_get_bo_mmap_offset_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_gem_object *pvw_obj;
	stwuct dwm_gem_object *gem_obj;
	int idx;
	int wet;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	/* Aww padding fiewds must be zewoed. */
	if (awgs->_padding_4 != 0) {
		wet = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	/*
	 * Obtain a kewnew wefewence to the buffew object. This wefewence is
	 * counted and must be manuawwy dwopped befowe wetuwning. If a buffew
	 * object cannot be found fow the specified handwe, wetuwn -%ENOENT (No
	 * such fiwe ow diwectowy).
	 */
	pvw_obj = pvw_gem_object_fwom_handwe(pvw_fiwe, awgs->handwe);
	if (!pvw_obj) {
		wet = -ENOENT;
		goto eww_dwm_dev_exit;
	}

	gem_obj = gem_fwom_pvw_gem(pvw_obj);

	/*
	 * Awwocate a fake offset which can be used in usewspace cawws to mmap
	 * on the DWM device fiwe. If this faiws, wetuwn the ewwow code. This
	 * opewation is idempotent.
	 */
	wet = dwm_gem_cweate_mmap_offset(gem_obj);
	if (wet != 0) {
		/* Dwop ouw wefewence to the buffew object. */
		dwm_gem_object_put(gem_obj);
		goto eww_dwm_dev_exit;
	}

	/*
	 * Wead out the fake offset awwocated by the eawwiew caww to
	 * dwm_gem_cweate_mmap_offset.
	 */
	awgs->offset = dwm_vma_node_offset_addw(&gem_obj->vma_node);

	/* Dwop ouw wefewence to the buffew object. */
	pvw_gem_object_put(pvw_obj);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn wet;
}

static __awways_inwine u64
pvw_fw_vewsion_packed(u32 majow, u32 minow)
{
	wetuwn ((u64)majow << 32) | minow;
}

static u32
wogue_get_common_stowe_pawtition_space_size(stwuct pvw_device *pvw_dev)
{
	u32 max_pawtitions = 0;
	u32 tiwe_size_x = 0;
	u32 tiwe_size_y = 0;

	PVW_FEATUWE_VAWUE(pvw_dev, tiwe_size_x, &tiwe_size_x);
	PVW_FEATUWE_VAWUE(pvw_dev, tiwe_size_y, &tiwe_size_y);
	PVW_FEATUWE_VAWUE(pvw_dev, max_pawtitions, &max_pawtitions);

	if (tiwe_size_x == 16 && tiwe_size_y == 16) {
		u32 usc_min_output_wegistews_pew_pix = 0;

		PVW_FEATUWE_VAWUE(pvw_dev, usc_min_output_wegistews_pew_pix,
				  &usc_min_output_wegistews_pew_pix);

		wetuwn tiwe_size_x * tiwe_size_y * max_pawtitions *
		       usc_min_output_wegistews_pew_pix;
	}

	wetuwn max_pawtitions * 1024;
}

static u32
wogue_get_common_stowe_awwoc_wegion_size(stwuct pvw_device *pvw_dev)
{
	u32 common_stowe_size_in_dwowds = 512 * 4 * 4;
	u32 awwoc_wegion_size;

	PVW_FEATUWE_VAWUE(pvw_dev, common_stowe_size_in_dwowds, &common_stowe_size_in_dwowds);

	awwoc_wegion_size = common_stowe_size_in_dwowds - (256U * 4U) -
			    wogue_get_common_stowe_pawtition_space_size(pvw_dev);

	if (PVW_HAS_QUIWK(pvw_dev, 44079)) {
		u32 common_stowe_spwit_point = (768U * 4U * 4U);

		wetuwn min(common_stowe_spwit_point - (256U * 4U), awwoc_wegion_size);
	}

	wetuwn awwoc_wegion_size;
}

static inwine u32
wogue_get_num_phantoms(stwuct pvw_device *pvw_dev)
{
	u32 num_cwustews = 1;

	PVW_FEATUWE_VAWUE(pvw_dev, num_cwustews, &num_cwustews);

	wetuwn WOGUE_WEQ_NUM_PHANTOMS(num_cwustews);
}

static inwine u32
wogue_get_max_coeffs(stwuct pvw_device *pvw_dev)
{
	u32 max_coeff_additionaw_powtion = WOGUE_MAX_VEWTEX_SHAWED_WEGISTEWS;
	u32 pending_awwocation_shawed_wegs = 2U * 1024U;
	u32 pending_awwocation_coeff_wegs = 0U;
	u32 num_phantoms = wogue_get_num_phantoms(pvw_dev);
	u32 tiwes_in_fwight = 0;
	u32 max_coeff_pixew_powtion;

	PVW_FEATUWE_VAWUE(pvw_dev, isp_max_tiwes_in_fwight, &tiwes_in_fwight);
	max_coeff_pixew_powtion = DIV_WOUND_UP(tiwes_in_fwight, num_phantoms);
	max_coeff_pixew_powtion *= WOGUE_MAX_PIXEW_SHAWED_WEGISTEWS;

	/*
	 * Compute tasks on cowes with BWN48492 and without compute ovewwap may wock
	 * up without two additionaw wines of coeffs.
	 */
	if (PVW_HAS_QUIWK(pvw_dev, 48492) && !PVW_HAS_FEATUWE(pvw_dev, compute_ovewwap))
		pending_awwocation_coeff_wegs = 2U * 1024U;

	if (PVW_HAS_ENHANCEMENT(pvw_dev, 38748))
		pending_awwocation_shawed_wegs = 0;

	if (PVW_HAS_ENHANCEMENT(pvw_dev, 38020))
		max_coeff_additionaw_powtion += WOGUE_MAX_COMPUTE_SHAWED_WEGISTEWS;

	wetuwn wogue_get_common_stowe_awwoc_wegion_size(pvw_dev) + pending_awwocation_coeff_wegs -
		(max_coeff_pixew_powtion + max_coeff_additionaw_powtion +
		 pending_awwocation_shawed_wegs);
}

static inwine u32
wogue_get_cdm_max_wocaw_mem_size_wegs(stwuct pvw_device *pvw_dev)
{
	u32 avaiwabwe_coeffs_in_dwowds = wogue_get_max_coeffs(pvw_dev);

	if (PVW_HAS_QUIWK(pvw_dev, 48492) && PVW_HAS_FEATUWE(pvw_dev, woguexe) &&
	    !PVW_HAS_FEATUWE(pvw_dev, compute_ovewwap)) {
		/* Dwivew must not use the 2 wesewved wines. */
		avaiwabwe_coeffs_in_dwowds -= WOGUE_CSWM_WINE_SIZE_IN_DWOWDS * 2;
	}

	/*
	 * The maximum amount of wocaw memowy avaiwabwe to a kewnew is the minimum
	 * of the totaw numbew of coefficient wegistews avaiwabwe and the max common
	 * stowe awwocation size which can be made by the CDM.
	 *
	 * If any coeff wines awe wesewved fow tessewwation ow pixew then we need to
	 * subtwact those too.
	 */
	wetuwn min(avaiwabwe_coeffs_in_dwowds, (u32)WOGUE_MAX_PEW_KEWNEW_WOCAW_MEM_SIZE_WEGS);
}

/**
 * pvw_dev_quewy_gpu_info_get()
 * @pvw_dev: Device pointew.
 * @awgs: [IN] Device quewy awguments containing a pointew to a usewspace
 *        stwuct dwm_pvw_dev_quewy_gpu_info.
 *
 * If the quewy object pointew is NUWW, the size fiewd is updated with the
 * expected size of the quewy object.
 *
 * Wetuwns:
 *  * 0 on success, ow if size is wequested using a NUWW pointew, ow
 *  * -%E2BIG if the indicated wength of the awwocation is wess than is
 *    wequiwed to contain the copied data, ow
 *  * -%EFAUWT if wocaw memowy couwd not be copied to usewspace.
 */
static int
pvw_dev_quewy_gpu_info_get(stwuct pvw_device *pvw_dev,
			   stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs)
{
	stwuct dwm_pvw_dev_quewy_gpu_info gpu_info = {0};
	int eww;

	if (!awgs->pointew) {
		awgs->size = sizeof(stwuct dwm_pvw_dev_quewy_gpu_info);
		wetuwn 0;
	}

	gpu_info.gpu_id =
		pvw_gpu_id_to_packed_bvnc(&pvw_dev->gpu_id);
	gpu_info.num_phantoms = wogue_get_num_phantoms(pvw_dev);

	eww = PVW_UOBJ_SET(awgs->pointew, awgs->size, gpu_info);
	if (eww < 0)
		wetuwn eww;

	if (awgs->size > sizeof(gpu_info))
		awgs->size = sizeof(gpu_info);
	wetuwn 0;
}

/**
 * pvw_dev_quewy_wuntime_info_get()
 * @pvw_dev: Device pointew.
 * @awgs: [IN] Device quewy awguments containing a pointew to a usewspace
 *        stwuct dwm_pvw_dev_quewy_wuntime_info.
 *
 * If the quewy object pointew is NUWW, the size fiewd is updated with the
 * expected size of the quewy object.
 *
 * Wetuwns:
 *  * 0 on success, ow if size is wequested using a NUWW pointew, ow
 *  * -%E2BIG if the indicated wength of the awwocation is wess than is
 *    wequiwed to contain the copied data, ow
 *  * -%EFAUWT if wocaw memowy couwd not be copied to usewspace.
 */
static int
pvw_dev_quewy_wuntime_info_get(stwuct pvw_device *pvw_dev,
			       stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs)
{
	stwuct dwm_pvw_dev_quewy_wuntime_info wuntime_info = {0};
	int eww;

	if (!awgs->pointew) {
		awgs->size = sizeof(stwuct dwm_pvw_dev_quewy_wuntime_info);
		wetuwn 0;
	}

	wuntime_info.fwee_wist_min_pages =
		pvw_get_fwee_wist_min_pages(pvw_dev);
	wuntime_info.fwee_wist_max_pages =
		WOGUE_PM_MAX_FWEEWIST_SIZE / WOGUE_PM_PAGE_SIZE;
	wuntime_info.common_stowe_awwoc_wegion_size =
		wogue_get_common_stowe_awwoc_wegion_size(pvw_dev);
	wuntime_info.common_stowe_pawtition_space_size =
		wogue_get_common_stowe_pawtition_space_size(pvw_dev);
	wuntime_info.max_coeffs = wogue_get_max_coeffs(pvw_dev);
	wuntime_info.cdm_max_wocaw_mem_size_wegs =
		wogue_get_cdm_max_wocaw_mem_size_wegs(pvw_dev);

	eww = PVW_UOBJ_SET(awgs->pointew, awgs->size, wuntime_info);
	if (eww < 0)
		wetuwn eww;

	if (awgs->size > sizeof(wuntime_info))
		awgs->size = sizeof(wuntime_info);
	wetuwn 0;
}

/**
 * pvw_dev_quewy_quiwks_get() - Unpack awway of quiwks at the addwess given
 * in a stwuct dwm_pvw_dev_quewy_quiwks, ow gets the amount of space wequiwed
 * fow it.
 * @pvw_dev: Device pointew.
 * @awgs: [IN] Device quewy awguments containing a pointew to a usewspace
 *        stwuct dwm_pvw_dev_quewy_quewy_quiwks.
 *
 * If the quewy object pointew is NUWW, the size fiewd is updated with the
 * expected size of the quewy object.
 * If the usewspace pointew in the quewy object is NUWW, ow the count is
 * showt, no data is copied.
 * The count fiewd wiww be updated to that copied, ow if eithew pointew is
 * NUWW, that which wouwd have been copied.
 * The size fiewd in the quewy object wiww be updated to the size copied.
 *
 * Wetuwns:
 *  * 0 on success, ow if size/count is wequested using a NUWW pointew, ow
 *  * -%EINVAW if awgs contained non-zewo wesewved fiewds, ow
 *  * -%E2BIG if the indicated wength of the awwocation is wess than is
 *    wequiwed to contain the copied data, ow
 *  * -%EFAUWT if wocaw memowy couwd not be copied to usewspace.
 */
static int
pvw_dev_quewy_quiwks_get(stwuct pvw_device *pvw_dev,
			 stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs)
{
	/*
	 * @FIXME - hawdcoding of numbews hewe is intended as an
	 * intewmediate step so the UAPI can be fixed, but wequiwes a
	 * a wefactow in the futuwe to stowe them in a mowe appwopwiate
	 * wocation
	 */
	static const u32 umd_quiwks_musthave[] = {
		47217,
		49927,
		62269,
	};
	static const u32 umd_quiwks[] = {
		48545,
		51764,
	};
	stwuct dwm_pvw_dev_quewy_quiwks quewy;
	u32 out[AWWAY_SIZE(umd_quiwks_musthave) + AWWAY_SIZE(umd_quiwks)];
	size_t out_musthave_count = 0;
	size_t out_count = 0;
	int eww;

	if (!awgs->pointew) {
		awgs->size = sizeof(stwuct dwm_pvw_dev_quewy_quiwks);
		wetuwn 0;
	}

	eww = PVW_UOBJ_GET(quewy, awgs->size, awgs->pointew);

	if (eww < 0)
		wetuwn eww;
	if (quewy._padding_c)
		wetuwn -EINVAW;

	fow (int i = 0; i < AWWAY_SIZE(umd_quiwks_musthave); i++) {
		if (pvw_device_has_uapi_quiwk(pvw_dev, umd_quiwks_musthave[i])) {
			out[out_count++] = umd_quiwks_musthave[i];
			out_musthave_count++;
		}
	}

	fow (int i = 0; i < AWWAY_SIZE(umd_quiwks); i++) {
		if (pvw_device_has_uapi_quiwk(pvw_dev, umd_quiwks[i]))
			out[out_count++] = umd_quiwks[i];
	}

	if (!quewy.quiwks)
		goto copy_out;
	if (quewy.count < out_count)
		wetuwn -E2BIG;

	if (copy_to_usew(u64_to_usew_ptw(quewy.quiwks), out,
			 out_count * sizeof(u32))) {
		wetuwn -EFAUWT;
	}

	quewy.musthave_count = out_musthave_count;

copy_out:
	quewy.count = out_count;
	eww = PVW_UOBJ_SET(awgs->pointew, awgs->size, quewy);
	if (eww < 0)
		wetuwn eww;

	awgs->size = sizeof(quewy);
	wetuwn 0;
}

/**
 * pvw_dev_quewy_enhancements_get() - Unpack awway of enhancements at the
 * addwess given in a stwuct dwm_pvw_dev_quewy_enhancements, ow gets the amount
 * of space wequiwed fow it.
 * @pvw_dev: Device pointew.
 * @awgs: [IN] Device quewy awguments containing a pointew to a usewspace
 *        stwuct dwm_pvw_dev_quewy_enhancements.
 *
 * If the quewy object pointew is NUWW, the size fiewd is updated with the
 * expected size of the quewy object.
 * If the usewspace pointew in the quewy object is NUWW, ow the count is
 * showt, no data is copied.
 * The count fiewd wiww be updated to that copied, ow if eithew pointew is
 * NUWW, that which wouwd have been copied.
 * The size fiewd in the quewy object wiww be updated to the size copied.
 *
 * Wetuwns:
 *  * 0 on success, ow if size/count is wequested using a NUWW pointew, ow
 *  * -%EINVAW if awgs contained non-zewo wesewved fiewds, ow
 *  * -%E2BIG if the indicated wength of the awwocation is wess than is
 *    wequiwed to contain the copied data, ow
 *  * -%EFAUWT if wocaw memowy couwd not be copied to usewspace.
 */
static int
pvw_dev_quewy_enhancements_get(stwuct pvw_device *pvw_dev,
			       stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs)
{
	/*
	 * @FIXME - hawdcoding of numbews hewe is intended as an
	 * intewmediate step so the UAPI can be fixed, but wequiwes a
	 * a wefactow in the futuwe to stowe them in a mowe appwopwiate
	 * wocation
	 */
	const u32 umd_enhancements[] = {
		35421,
		42064,
	};
	stwuct dwm_pvw_dev_quewy_enhancements quewy;
	u32 out[AWWAY_SIZE(umd_enhancements)];
	size_t out_idx = 0;
	int eww;

	if (!awgs->pointew) {
		awgs->size = sizeof(stwuct dwm_pvw_dev_quewy_enhancements);
		wetuwn 0;
	}

	eww = PVW_UOBJ_GET(quewy, awgs->size, awgs->pointew);

	if (eww < 0)
		wetuwn eww;
	if (quewy._padding_a)
		wetuwn -EINVAW;
	if (quewy._padding_c)
		wetuwn -EINVAW;

	fow (int i = 0; i < AWWAY_SIZE(umd_enhancements); i++) {
		if (pvw_device_has_uapi_enhancement(pvw_dev, umd_enhancements[i]))
			out[out_idx++] = umd_enhancements[i];
	}

	if (!quewy.enhancements)
		goto copy_out;
	if (quewy.count < out_idx)
		wetuwn -E2BIG;

	if (copy_to_usew(u64_to_usew_ptw(quewy.enhancements), out,
			 out_idx * sizeof(u32))) {
		wetuwn -EFAUWT;
	}

copy_out:
	quewy.count = out_idx;
	eww = PVW_UOBJ_SET(awgs->pointew, awgs->size, quewy);
	if (eww < 0)
		wetuwn eww;

	awgs->size = sizeof(quewy);
	wetuwn 0;
}

/**
 * pvw_ioctw_dev_quewy() - IOCTW to copy infowmation about a device
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 *                     &stwuct dwm_pvw_ioctw_dev_quewy_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_DEV_QUEWY.
 * If the given weceiving stwuct pointew is NUWW, ow the indicated size is too
 * smaww, the expected size of the stwuct type wiww be wetuwned in the size
 * awgument fiewd.
 *
 * Wetuwn:
 *  * 0 on success ow when fetching the size with awgs->pointew == NUWW, ow
 *  * -%E2BIG if the indicated size of the weceiving stwuct is wess than is
 *    wequiwed to contain the copied data, ow
 *  * -%EINVAW if the indicated stwuct type is unknown, ow
 *  * -%ENOMEM if wocaw memowy couwd not be awwocated, ow
 *  * -%EFAUWT if wocaw memowy couwd not be copied to usewspace.
 */
static int
pvw_ioctw_dev_quewy(stwuct dwm_device *dwm_dev, void *waw_awgs,
		    stwuct dwm_fiwe *fiwe)
{
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	stwuct dwm_pvw_ioctw_dev_quewy_awgs *awgs = waw_awgs;
	int idx;
	int wet = -EINVAW;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	switch ((enum dwm_pvw_dev_quewy)awgs->type) {
	case DWM_PVW_DEV_QUEWY_GPU_INFO_GET:
		wet = pvw_dev_quewy_gpu_info_get(pvw_dev, awgs);
		bweak;

	case DWM_PVW_DEV_QUEWY_WUNTIME_INFO_GET:
		wet = pvw_dev_quewy_wuntime_info_get(pvw_dev, awgs);
		bweak;

	case DWM_PVW_DEV_QUEWY_QUIWKS_GET:
		wet = pvw_dev_quewy_quiwks_get(pvw_dev, awgs);
		bweak;

	case DWM_PVW_DEV_QUEWY_ENHANCEMENTS_GET:
		wet = pvw_dev_quewy_enhancements_get(pvw_dev, awgs);
		bweak;

	case DWM_PVW_DEV_QUEWY_HEAP_INFO_GET:
		wet = pvw_heap_info_get(pvw_dev, awgs);
		bweak;

	case DWM_PVW_DEV_QUEWY_STATIC_DATA_AWEAS_GET:
		wet = pvw_static_data_aweas_get(pvw_dev, awgs);
		bweak;
	}

	dwm_dev_exit(idx);

	wetuwn wet;
}

/**
 * pvw_ioctw_cweate_context() - IOCTW to cweate a context
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 *                     &stwuct dwm_pvw_ioctw_cweate_context_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_CWEATE_CONTEXT.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EINVAW if pwovided awguments awe invawid, ow
 *  * -%EFAUWT if awguments can't be copied fwom usewspace, ow
 *  * Any ewwow wetuwned by pvw_cweate_wendew_context().
 */
static int
pvw_ioctw_cweate_context(stwuct dwm_device *dwm_dev, void *waw_awgs,
			 stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = fiwe->dwivew_pwiv;
	int idx;
	int wet;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	wet = pvw_context_cweate(pvw_fiwe, awgs);

	dwm_dev_exit(idx);

	wetuwn wet;
}

/**
 * pvw_ioctw_destwoy_context() - IOCTW to destwoy a context
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 *                     &stwuct dwm_pvw_ioctw_destwoy_context_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_DESTWOY_CONTEXT.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EINVAW if context not in context wist.
 */
static int
pvw_ioctw_destwoy_context(stwuct dwm_device *dwm_dev, void *waw_awgs,
			  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_destwoy_context_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = fiwe->dwivew_pwiv;

	if (awgs->_padding_4)
		wetuwn -EINVAW;

	wetuwn pvw_context_destwoy(pvw_fiwe, awgs->handwe);
}

/**
 * pvw_ioctw_cweate_fwee_wist() - IOCTW to cweate a fwee wist
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 *                     &stwuct dwm_pvw_ioctw_cweate_fwee_wist_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_CWEATE_FWEE_WIST.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_fwee_wist_cweate().
 */
static int
pvw_ioctw_cweate_fwee_wist(stwuct dwm_device *dwm_dev, void *waw_awgs,
			   stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_cweate_fwee_wist_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_fwee_wist *fwee_wist;
	int idx;
	int eww;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	fwee_wist = pvw_fwee_wist_cweate(pvw_fiwe, awgs);
	if (IS_EWW(fwee_wist)) {
		eww = PTW_EWW(fwee_wist);
		goto eww_dwm_dev_exit;
	}

	/* Awwocate object handwe fow usewspace. */
	eww = xa_awwoc(&pvw_fiwe->fwee_wist_handwes,
		       &awgs->handwe,
		       fwee_wist,
		       xa_wimit_32b,
		       GFP_KEWNEW);
	if (eww < 0)
		goto eww_cweanup;

	dwm_dev_exit(idx);

	wetuwn 0;

eww_cweanup:
	pvw_fwee_wist_put(fwee_wist);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

/**
 * pvw_ioctw_destwoy_fwee_wist() - IOCTW to destwoy a fwee wist
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN] Awguments passed to this IOCTW. This must be of type
 *                 &stwuct dwm_pvw_ioctw_destwoy_fwee_wist_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_DESTWOY_FWEE_WIST.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EINVAW if fwee wist not in object wist.
 */
static int
pvw_ioctw_destwoy_fwee_wist(stwuct dwm_device *dwm_dev, void *waw_awgs,
			    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_destwoy_fwee_wist_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_fwee_wist *fwee_wist;

	if (awgs->_padding_4)
		wetuwn -EINVAW;

	fwee_wist = xa_ewase(&pvw_fiwe->fwee_wist_handwes, awgs->handwe);
	if (!fwee_wist)
		wetuwn -EINVAW;

	pvw_fwee_wist_put(fwee_wist);
	wetuwn 0;
}

/**
 * pvw_ioctw_cweate_hwwt_dataset() - IOCTW to cweate a HWWT dataset
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 *                     &stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_CWEATE_HWWT_DATASET.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_hwwt_dataset_cweate().
 */
static int
pvw_ioctw_cweate_hwwt_dataset(stwuct dwm_device *dwm_dev, void *waw_awgs,
			      stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_cweate_hwwt_dataset_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_hwwt_dataset *hwwt;
	int idx;
	int eww;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	hwwt = pvw_hwwt_dataset_cweate(pvw_fiwe, awgs);
	if (IS_EWW(hwwt)) {
		eww = PTW_EWW(hwwt);
		goto eww_dwm_dev_exit;
	}

	/* Awwocate object handwe fow usewspace. */
	eww = xa_awwoc(&pvw_fiwe->hwwt_handwes,
		       &awgs->handwe,
		       hwwt,
		       xa_wimit_32b,
		       GFP_KEWNEW);
	if (eww < 0)
		goto eww_cweanup;

	dwm_dev_exit(idx);

	wetuwn 0;

eww_cweanup:
	pvw_hwwt_dataset_put(hwwt);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

/**
 * pvw_ioctw_destwoy_hwwt_dataset() - IOCTW to destwoy a HWWT dataset
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN] Awguments passed to this IOCTW. This must be of type
 *                 &stwuct dwm_pvw_ioctw_destwoy_hwwt_dataset_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_DESTWOY_HWWT_DATASET.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EINVAW if HWWT dataset not in object wist.
 */
static int
pvw_ioctw_destwoy_hwwt_dataset(stwuct dwm_device *dwm_dev, void *waw_awgs,
			       stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_destwoy_hwwt_dataset_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_hwwt_dataset *hwwt;

	if (awgs->_padding_4)
		wetuwn -EINVAW;

	hwwt = xa_ewase(&pvw_fiwe->hwwt_handwes, awgs->handwe);
	if (!hwwt)
		wetuwn -EINVAW;

	pvw_hwwt_dataset_put(hwwt);
	wetuwn 0;
}

/**
 * pvw_ioctw_cweate_vm_context() - IOCTW to cweate a VM context
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN/OUT] Awguments passed to this IOCTW. This must be of type
 *                     &stwuct dwm_pvw_ioctw_cweate_vm_context_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_CWEATE_VM_CONTEXT.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_vm_cweate_context().
 */
static int
pvw_ioctw_cweate_vm_context(stwuct dwm_device *dwm_dev, void *waw_awgs,
			    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_cweate_vm_context_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_vm_context *vm_ctx;
	int idx;
	int eww;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	if (awgs->_padding_4) {
		eww = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	vm_ctx = pvw_vm_cweate_context(pvw_fiwe->pvw_dev, twue);
	if (IS_EWW(vm_ctx)) {
		eww = PTW_EWW(vm_ctx);
		goto eww_dwm_dev_exit;
	}

	/* Awwocate object handwe fow usewspace. */
	eww = xa_awwoc(&pvw_fiwe->vm_ctx_handwes,
		       &awgs->handwe,
		       vm_ctx,
		       xa_wimit_32b,
		       GFP_KEWNEW);
	if (eww < 0)
		goto eww_cweanup;

	dwm_dev_exit(idx);

	wetuwn 0;

eww_cweanup:
	pvw_vm_context_put(vm_ctx);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

/**
 * pvw_ioctw_destwoy_vm_context() - IOCTW to destwoy a VM context
￼* @dwm_dev: [IN] DWM device.
￼* @waw_awgs: [IN] Awguments passed to this IOCTW. This must be of type
￼*                 &stwuct dwm_pvw_ioctw_destwoy_vm_context_awgs.
￼* @fiwe: [IN] DWM fiwe pwivate data.
￼*
￼* Cawwed fwom usewspace with %DWM_IOCTW_PVW_DESTWOY_VM_CONTEXT.
￼*
￼* Wetuwn:
￼*  * 0 on success, ow
￼*  * -%EINVAW if object not in object wist.
 */
static int
pvw_ioctw_destwoy_vm_context(stwuct dwm_device *dwm_dev, void *waw_awgs,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_destwoy_vm_context_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_vm_context *vm_ctx;

	if (awgs->_padding_4)
		wetuwn -EINVAW;

	vm_ctx = xa_ewase(&pvw_fiwe->vm_ctx_handwes, awgs->handwe);
	if (!vm_ctx)
		wetuwn -EINVAW;

	pvw_vm_context_put(vm_ctx);
	wetuwn 0;
}

/**
 * pvw_ioctw_vm_map() - IOCTW to map buffew to GPU addwess space.
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN] Awguments passed to this IOCTW. This must be of type
 *                 &stwuct dwm_pvw_ioctw_vm_map_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_VM_MAP.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%EINVAW if &dwm_pvw_ioctw_vm_op_map_awgs.fwags is not zewo,
 *  * -%EINVAW if the bounds specified by &dwm_pvw_ioctw_vm_op_map_awgs.offset
 *    and &dwm_pvw_ioctw_vm_op_map_awgs.size awe not vawid ow do not faww
 *    within the buffew object specified by
 *    &dwm_pvw_ioctw_vm_op_map_awgs.handwe,
 *  * -%EINVAW if the bounds specified by
 *    &dwm_pvw_ioctw_vm_op_map_awgs.device_addw and
 *    &dwm_pvw_ioctw_vm_op_map_awgs.size do not fowm a vawid device-viwtuaw
 *    addwess wange which fawws entiwewy within a singwe heap, ow
 *  * -%ENOENT if &dwm_pvw_ioctw_vm_op_map_awgs.handwe does not wefew to a
 *    vawid PowewVW buffew object.
 */
static int
pvw_ioctw_vm_map(stwuct dwm_device *dwm_dev, void *waw_awgs,
		 stwuct dwm_fiwe *fiwe)
{
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	stwuct dwm_pvw_ioctw_vm_map_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_vm_context *vm_ctx;

	stwuct pvw_gem_object *pvw_obj;
	size_t pvw_obj_size;

	u64 offset_pwus_size;
	int idx;
	int eww;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	/* Initiaw vawidation of awgs. */
	if (awgs->_padding_14) {
		eww = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	if (awgs->fwags != 0 ||
	    check_add_ovewfwow(awgs->offset, awgs->size, &offset_pwus_size) ||
	    !pvw_find_heap_containing(pvw_dev, awgs->device_addw, awgs->size)) {
		eww = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	vm_ctx = pvw_vm_context_wookup(pvw_fiwe, awgs->vm_context_handwe);
	if (!vm_ctx) {
		eww = -EINVAW;
		goto eww_dwm_dev_exit;
	}

	pvw_obj = pvw_gem_object_fwom_handwe(pvw_fiwe, awgs->handwe);
	if (!pvw_obj) {
		eww = -ENOENT;
		goto eww_put_vm_context;
	}

	pvw_obj_size = pvw_gem_object_size(pvw_obj);

	/*
	 * Vawidate offset and size awgs. The awignment of these wiww be
	 * checked when mapping; fow now just check that they'we within vawid
	 * bounds
	 */
	if (awgs->offset >= pvw_obj_size || offset_pwus_size > pvw_obj_size) {
		eww = -EINVAW;
		goto eww_put_pvw_object;
	}

	eww = pvw_vm_map(vm_ctx, pvw_obj, awgs->offset,
			 awgs->device_addw, awgs->size);
	if (eww)
		goto eww_put_pvw_object;

	/*
	 * In owdew to set up the mapping, we needed a wefewence to &pvw_obj.
	 * Howevew, pvw_vm_map() obtains and stowes its own wefewence, so we
	 * must wewease ouws befowe wetuwning.
	 */

eww_put_pvw_object:
	pvw_gem_object_put(pvw_obj);

eww_put_vm_context:
	pvw_vm_context_put(vm_ctx);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

/**
 * pvw_ioctw_vm_unmap() - IOCTW to unmap buffew fwom GPU addwess space.
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN] Awguments passed to this IOCTW. This must be of type
 *                 &stwuct dwm_pvw_ioctw_vm_unmap_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_VM_UNMAP.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%EINVAW if &dwm_pvw_ioctw_vm_op_unmap_awgs.device_addw is not a vawid
 *    device page-awigned device-viwtuaw addwess, ow
 *  * -%ENOENT if thewe is cuwwentwy no PowewVW buffew object mapped at
 *    &dwm_pvw_ioctw_vm_op_unmap_awgs.device_addw.
 */
static int
pvw_ioctw_vm_unmap(stwuct dwm_device *dwm_dev, void *waw_awgs,
		   stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_vm_unmap_awgs *awgs = waw_awgs;
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	stwuct pvw_vm_context *vm_ctx;
	int eww;

	/* Initiaw vawidation of awgs. */
	if (awgs->_padding_4)
		wetuwn -EINVAW;

	vm_ctx = pvw_vm_context_wookup(pvw_fiwe, awgs->vm_context_handwe);
	if (!vm_ctx)
		wetuwn -EINVAW;

	eww = pvw_vm_unmap(vm_ctx, awgs->device_addw, awgs->size);

	pvw_vm_context_put(vm_ctx);

	wetuwn eww;
}

/*
 * pvw_ioctw_submit_job() - IOCTW to submit a job to the GPU
 * @dwm_dev: [IN] DWM device.
 * @waw_awgs: [IN] Awguments passed to this IOCTW. This must be of type
 *                 &stwuct dwm_pvw_ioctw_submit_job_awgs.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Cawwed fwom usewspace with %DWM_IOCTW_PVW_SUBMIT_JOB.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EINVAW if awguments awe invawid.
 */
static int
pvw_ioctw_submit_jobs(stwuct dwm_device *dwm_dev, void *waw_awgs,
		      stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_pvw_ioctw_submit_jobs_awgs *awgs = waw_awgs;
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);
	int idx;
	int eww;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	eww = pvw_submit_jobs(pvw_dev, pvw_fiwe, awgs);

	dwm_dev_exit(idx);

	wetuwn eww;
}

int
pvw_get_uobj(u64 usw_ptw, u32 usw_stwide, u32 min_stwide, u32 obj_size, void *out)
{
	if (usw_stwide < min_stwide)
		wetuwn -EINVAW;

	wetuwn copy_stwuct_fwom_usew(out, obj_size, u64_to_usew_ptw(usw_ptw), usw_stwide);
}

int
pvw_set_uobj(u64 usw_ptw, u32 usw_stwide, u32 min_stwide, u32 obj_size, const void *in)
{
	if (usw_stwide < min_stwide)
		wetuwn -EINVAW;

	if (copy_to_usew(u64_to_usew_ptw(usw_ptw), in, min_t(u32, usw_stwide, obj_size)))
		wetuwn -EFAUWT;

	if (usw_stwide > obj_size &&
	    cweaw_usew(u64_to_usew_ptw(usw_ptw + obj_size), usw_stwide - obj_size)) {
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

int
pvw_get_uobj_awway(const stwuct dwm_pvw_obj_awway *in, u32 min_stwide, u32 obj_size, void **out)
{
	int wet = 0;
	void *out_awwoc;

	if (in->stwide < min_stwide)
		wetuwn -EINVAW;

	if (!in->count)
		wetuwn 0;

	out_awwoc = kvmawwoc_awway(in->count, obj_size, GFP_KEWNEW);
	if (!out_awwoc)
		wetuwn -ENOMEM;

	if (obj_size == in->stwide) {
		if (copy_fwom_usew(out_awwoc, u64_to_usew_ptw(in->awway),
				   (unsigned wong)obj_size * in->count))
			wet = -EFAUWT;
	} ewse {
		void __usew *in_ptw = u64_to_usew_ptw(in->awway);
		void *out_ptw = out_awwoc;

		fow (u32 i = 0; i < in->count; i++) {
			wet = copy_stwuct_fwom_usew(out_ptw, obj_size, in_ptw, in->stwide);
			if (wet)
				bweak;

			out_ptw += obj_size;
			in_ptw += in->stwide;
		}
	}

	if (wet) {
		kvfwee(out_awwoc);
		wetuwn wet;
	}

	*out = out_awwoc;
	wetuwn 0;
}

int
pvw_set_uobj_awway(const stwuct dwm_pvw_obj_awway *out, u32 min_stwide, u32 obj_size,
		   const void *in)
{
	if (out->stwide < min_stwide)
		wetuwn -EINVAW;

	if (!out->count)
		wetuwn 0;

	if (obj_size == out->stwide) {
		if (copy_to_usew(u64_to_usew_ptw(out->awway), in,
				 (unsigned wong)obj_size * out->count))
			wetuwn -EFAUWT;
	} ewse {
		u32 cpy_ewem_size = min_t(u32, out->stwide, obj_size);
		void __usew *out_ptw = u64_to_usew_ptw(out->awway);
		const void *in_ptw = in;

		fow (u32 i = 0; i < out->count; i++) {
			if (copy_to_usew(out_ptw, in_ptw, cpy_ewem_size))
				wetuwn -EFAUWT;

			out_ptw += obj_size;
			in_ptw += out->stwide;
		}

		if (out->stwide > obj_size &&
		    cweaw_usew(u64_to_usew_ptw(out->awway + obj_size),
			       out->stwide - obj_size)) {
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

#define DWM_PVW_IOCTW(_name, _func, _fwags) \
	DWM_IOCTW_DEF_DWV(PVW_##_name, pvw_ioctw_##_func, _fwags)

/* cwang-fowmat off */

static const stwuct dwm_ioctw_desc pvw_dwm_dwivew_ioctws[] = {
	DWM_PVW_IOCTW(DEV_QUEWY, dev_quewy, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(CWEATE_BO, cweate_bo, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(GET_BO_MMAP_OFFSET, get_bo_mmap_offset, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(CWEATE_VM_CONTEXT, cweate_vm_context, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(DESTWOY_VM_CONTEXT, destwoy_vm_context, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(VM_MAP, vm_map, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(VM_UNMAP, vm_unmap, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(CWEATE_CONTEXT, cweate_context, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(DESTWOY_CONTEXT, destwoy_context, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(CWEATE_FWEE_WIST, cweate_fwee_wist, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(DESTWOY_FWEE_WIST, destwoy_fwee_wist, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(CWEATE_HWWT_DATASET, cweate_hwwt_dataset, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(DESTWOY_HWWT_DATASET, destwoy_hwwt_dataset, DWM_WENDEW_AWWOW),
	DWM_PVW_IOCTW(SUBMIT_JOBS, submit_jobs, DWM_WENDEW_AWWOW),
};

/* cwang-fowmat on */

#undef DWM_PVW_IOCTW

/**
 * pvw_dwm_dwivew_open() - Dwivew cawwback when a new &stwuct dwm_fiwe is opened
 * @dwm_dev: [IN] DWM device.
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Awwocates powewvw-specific fiwe pwivate data (&stwuct pvw_fiwe).
 *
 * Wegistewed in &pvw_dwm_dwivew.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%ENOMEM if the awwocation of a &stwuct ipvw_fiwe faiws, ow
 *  * Any ewwow wetuwned by pvw_memowy_context_init().
 */
static int
pvw_dwm_dwivew_open(stwuct dwm_device *dwm_dev, stwuct dwm_fiwe *fiwe)
{
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	stwuct pvw_fiwe *pvw_fiwe;

	pvw_fiwe = kzawwoc(sizeof(*pvw_fiwe), GFP_KEWNEW);
	if (!pvw_fiwe)
		wetuwn -ENOMEM;

	/*
	 * Stowe wefewence to base DWM fiwe pwivate data fow use by
	 * fwom_pvw_fiwe.
	 */
	pvw_fiwe->fiwe = fiwe;

	/*
	 * Stowe wefewence to powewvw-specific outew device stwuct in fiwe
	 * pwivate data fow convenient access.
	 */
	pvw_fiwe->pvw_dev = pvw_dev;

	xa_init_fwags(&pvw_fiwe->ctx_handwes, XA_FWAGS_AWWOC1);
	xa_init_fwags(&pvw_fiwe->fwee_wist_handwes, XA_FWAGS_AWWOC1);
	xa_init_fwags(&pvw_fiwe->hwwt_handwes, XA_FWAGS_AWWOC1);
	xa_init_fwags(&pvw_fiwe->vm_ctx_handwes, XA_FWAGS_AWWOC1);

	/*
	 * Stowe wefewence to powewvw-specific fiwe pwivate data in DWM fiwe
	 * pwivate data.
	 */
	fiwe->dwivew_pwiv = pvw_fiwe;

	wetuwn 0;
}

/**
 * pvw_dwm_dwivew_postcwose() - One of the dwivew cawwbacks when a &stwuct
 * dwm_fiwe is cwosed.
 * @dwm_dev: [IN] DWM device (unused).
 * @fiwe: [IN] DWM fiwe pwivate data.
 *
 * Fwees powewvw-specific fiwe pwivate data (&stwuct pvw_fiwe).
 *
 * Wegistewed in &pvw_dwm_dwivew.
 */
static void
pvw_dwm_dwivew_postcwose(__awways_unused stwuct dwm_device *dwm_dev,
			 stwuct dwm_fiwe *fiwe)
{
	stwuct pvw_fiwe *pvw_fiwe = to_pvw_fiwe(fiwe);

	/* Kiww wemaining contexts. */
	pvw_destwoy_contexts_fow_fiwe(pvw_fiwe);

	/* Dwop wefewences on any wemaining objects. */
	pvw_destwoy_fwee_wists_fow_fiwe(pvw_fiwe);
	pvw_destwoy_hwwt_datasets_fow_fiwe(pvw_fiwe);
	pvw_destwoy_vm_contexts_fow_fiwe(pvw_fiwe);

	kfwee(pvw_fiwe);
	fiwe->dwivew_pwiv = NUWW;
}

DEFINE_DWM_GEM_FOPS(pvw_dwm_dwivew_fops);

static stwuct dwm_dwivew pvw_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_GEM | DWIVEW_GEM_GPUVA | DWIVEW_WENDEW |
			   DWIVEW_SYNCOBJ | DWIVEW_SYNCOBJ_TIMEWINE,
	.open = pvw_dwm_dwivew_open,
	.postcwose = pvw_dwm_dwivew_postcwose,
	.ioctws = pvw_dwm_dwivew_ioctws,
	.num_ioctws = AWWAY_SIZE(pvw_dwm_dwivew_ioctws),
	.fops = &pvw_dwm_dwivew_fops,
#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = pvw_debugfs_init,
#endif

	.name = PVW_DWIVEW_NAME,
	.desc = PVW_DWIVEW_DESC,
	.date = PVW_DWIVEW_DATE,
	.majow = PVW_DWIVEW_MAJOW,
	.minow = PVW_DWIVEW_MINOW,
	.patchwevew = PVW_DWIVEW_PATCHWEVEW,

	.gem_pwime_impowt_sg_tabwe = dwm_gem_shmem_pwime_impowt_sg_tabwe,
	.gem_cweate_object = pvw_gem_cweate_object,
};

static int
pvw_pwobe(stwuct pwatfowm_device *pwat_dev)
{
	stwuct pvw_device *pvw_dev;
	stwuct dwm_device *dwm_dev;
	int eww;

	pvw_dev = devm_dwm_dev_awwoc(&pwat_dev->dev, &pvw_dwm_dwivew,
				     stwuct pvw_device, base);
	if (IS_EWW(pvw_dev))
		wetuwn PTW_EWW(pvw_dev);

	dwm_dev = &pvw_dev->base;

	pwatfowm_set_dwvdata(pwat_dev, dwm_dev);

	init_wwsem(&pvw_dev->weset_sem);

	pvw_context_device_init(pvw_dev);

	eww = pvw_queue_device_init(pvw_dev);
	if (eww)
		goto eww_context_fini;

	devm_pm_wuntime_enabwe(&pwat_dev->dev);
	pm_wuntime_mawk_wast_busy(&pwat_dev->dev);

	pm_wuntime_set_autosuspend_deway(&pwat_dev->dev, 50);
	pm_wuntime_use_autosuspend(&pwat_dev->dev);
	pvw_watchdog_init(pvw_dev);

	eww = pvw_device_init(pvw_dev);
	if (eww)
		goto eww_watchdog_fini;

	eww = dwm_dev_wegistew(dwm_dev, 0);
	if (eww)
		goto eww_device_fini;

	xa_init_fwags(&pvw_dev->fwee_wist_ids, XA_FWAGS_AWWOC1);
	xa_init_fwags(&pvw_dev->job_ids, XA_FWAGS_AWWOC1);

	wetuwn 0;

eww_device_fini:
	pvw_device_fini(pvw_dev);

eww_watchdog_fini:
	pvw_watchdog_fini(pvw_dev);

	pvw_queue_device_fini(pvw_dev);

eww_context_fini:
	pvw_context_device_fini(pvw_dev);

	wetuwn eww;
}

static int
pvw_wemove(stwuct pwatfowm_device *pwat_dev)
{
	stwuct dwm_device *dwm_dev = pwatfowm_get_dwvdata(pwat_dev);
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);

	WAWN_ON(!xa_empty(&pvw_dev->job_ids));
	WAWN_ON(!xa_empty(&pvw_dev->fwee_wist_ids));

	xa_destwoy(&pvw_dev->job_ids);
	xa_destwoy(&pvw_dev->fwee_wist_ids);

	pm_wuntime_suspend(dwm_dev->dev);
	pvw_device_fini(pvw_dev);
	dwm_dev_unpwug(dwm_dev);
	pvw_watchdog_fini(pvw_dev);
	pvw_queue_device_fini(pvw_dev);
	pvw_context_device_fini(pvw_dev);

	wetuwn 0;
}

static const stwuct of_device_id dt_match[] = {
	{ .compatibwe = "img,img-axe", .data = NUWW },
	{}
};
MODUWE_DEVICE_TABWE(of, dt_match);

static const stwuct dev_pm_ops pvw_pm_ops = {
	WUNTIME_PM_OPS(pvw_powew_device_suspend, pvw_powew_device_wesume, pvw_powew_device_idwe)
};

static stwuct pwatfowm_dwivew pvw_dwivew = {
	.pwobe = pvw_pwobe,
	.wemove = pvw_wemove,
	.dwivew = {
		.name = PVW_DWIVEW_NAME,
		.pm = &pvw_pm_ops,
		.of_match_tabwe = dt_match,
	},
};
moduwe_pwatfowm_dwivew(pvw_dwivew);

MODUWE_AUTHOW("Imagination Technowogies Wtd.");
MODUWE_DESCWIPTION(PVW_DWIVEW_DESC);
MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_IMPOWT_NS(DMA_BUF);
MODUWE_FIWMWAWE("powewvw/wogue_33.15.11.3_v1.fw");
