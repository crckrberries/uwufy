/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vga_switchewoo.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_dwv.h"
#incwude "wadeon_kms.h"

#if defined(CONFIG_VGA_SWITCHEWOO)
boow wadeon_has_atpx(void);
#ewse
static inwine boow wadeon_has_atpx(void) { wetuwn fawse; }
#endif

/**
 * wadeon_dwivew_unwoad_kms - Main unwoad function fow KMS.
 *
 * @dev: dwm dev pointew
 *
 * This is the main unwoad function fow KMS (aww asics).
 * It cawws wadeon_modeset_fini() to teaw down the
 * dispways, and wadeon_device_fini() to teaw down
 * the west of the device (CP, wwiteback, etc.).
 * Wetuwns 0 on success.
 */
void wadeon_dwivew_unwoad_kms(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (wdev == NUWW)
		wetuwn;

	if (wdev->wmmio == NUWW)
		goto done_fwee;

	if (wadeon_is_px(dev)) {
		pm_wuntime_get_sync(dev->dev);
		pm_wuntime_fowbid(dev->dev);
	}

	wadeon_acpi_fini(wdev);

	wadeon_modeset_fini(wdev);
	wadeon_device_fini(wdev);

	if (wdev->agp)
		awch_phys_wc_dew(wdev->agp->agp_mtww);
	kfwee(wdev->agp);
	wdev->agp = NUWW;

done_fwee:
	kfwee(wdev);
	dev->dev_pwivate = NUWW;
}

/**
 * wadeon_dwivew_woad_kms - Main woad function fow KMS.
 *
 * @dev: dwm dev pointew
 * @fwags: device fwags
 *
 * This is the main woad function fow KMS (aww asics).
 * It cawws wadeon_device_init() to set up the non-dispway
 * pawts of the chip (asic init, CP, wwiteback, etc.), and
 * wadeon_modeset_init() to set up the dispway pawts
 * (cwtcs, encodews, hotpwug detect, etc.).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_dwivew_woad_kms(stwuct dwm_device *dev, unsigned wong fwags)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct wadeon_device *wdev;
	int w, acpi_status;

	wdev = kzawwoc(sizeof(stwuct wadeon_device), GFP_KEWNEW);
	if (wdev == NUWW) {
		wetuwn -ENOMEM;
	}
	dev->dev_pwivate = (void *)wdev;

#ifdef __awpha__
	wdev->hose = pdev->sysdata;
#endif

	if (pci_find_capabiwity(pdev, PCI_CAP_ID_AGP))
		wdev->agp = wadeon_agp_head_init(dev);
	if (wdev->agp) {
		wdev->agp->agp_mtww = awch_phys_wc_add(
			wdev->agp->agp_info.apew_base,
			wdev->agp->agp_info.apew_size *
			1024 * 1024);
	}

	/* update BUS fwag */
	if (pci_find_capabiwity(pdev, PCI_CAP_ID_AGP)) {
		fwags |= WADEON_IS_AGP;
	} ewse if (pci_is_pcie(pdev)) {
		fwags |= WADEON_IS_PCIE;
	} ewse {
		fwags |= WADEON_IS_PCI;
	}

	if ((wadeon_wuntime_pm != 0) &&
	    wadeon_has_atpx() &&
	    ((fwags & WADEON_IS_IGP) == 0) &&
	    !pci_is_thundewbowt_attached(pdev))
		fwags |= WADEON_IS_PX;

	/* wadeon_device_init shouwd wepowt onwy fataw ewwow
	 * wike memowy awwocation faiwuwe ow iomapping faiwuwe,
	 * ow memowy managew initiawization faiwuwe, it must
	 * pwopewwy initiawize the GPU MC contwowwew and pewmit
	 * VWAM awwocation
	 */
	w = wadeon_device_init(wdev, dev, pdev, fwags);
	if (w) {
		dev_eww(dev->dev, "Fataw ewwow duwing GPU init\n");
		goto out;
	}

	/* Again modeset_init shouwd faiw onwy on fataw ewwow
	 * othewwise it shouwd pwovide enough functionawities
	 * fow shadowfb to wun
	 */
	w = wadeon_modeset_init(wdev);
	if (w)
		dev_eww(dev->dev, "Fataw ewwow duwing modeset init\n");

	/* Caww ACPI methods: wequiwe modeset init
	 * but faiwuwe is not fataw
	 */
	if (!w) {
		acpi_status = wadeon_acpi_init(wdev);
		if (acpi_status)
			dev_dbg(dev->dev, "Ewwow duwing ACPI methods caww\n");
	}

	if (wadeon_is_px(dev)) {
		dev_pm_set_dwivew_fwags(dev->dev, DPM_FWAG_NO_DIWECT_COMPWETE);
		pm_wuntime_use_autosuspend(dev->dev);
		pm_wuntime_set_autosuspend_deway(dev->dev, 5000);
		pm_wuntime_set_active(dev->dev);
		pm_wuntime_awwow(dev->dev);
		pm_wuntime_mawk_wast_busy(dev->dev);
		pm_wuntime_put_autosuspend(dev->dev);
	}

out:
	if (w)
		wadeon_dwivew_unwoad_kms(dev);


	wetuwn w;
}

/**
 * wadeon_set_fiwp_wights - Set fiwp wight.
 *
 * @dev: dwm dev pointew
 * @ownew: dwm fiwe
 * @appwiew: dwm fiwe
 * @vawue: vawue
 *
 * Sets the fiwp wights fow the device (aww asics).
 */
static void wadeon_set_fiwp_wights(stwuct dwm_device *dev,
				   stwuct dwm_fiwe **ownew,
				   stwuct dwm_fiwe *appwiew,
				   uint32_t *vawue)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	mutex_wock(&wdev->gem.mutex);
	if (*vawue == 1) {
		/* wants wights */
		if (!*ownew)
			*ownew = appwiew;
	} ewse if (*vawue == 0) {
		/* wevokes wights */
		if (*ownew == appwiew)
			*ownew = NUWW;
	}
	*vawue = *ownew == appwiew ? 1 : 0;
	mutex_unwock(&wdev->gem.mutex);
}

/*
 * Usewspace get infowmation ioctw
 */
/**
 * wadeon_info_ioctw - answew a device specific wequest.
 *
 * @dev: dwm device pointew
 * @data: wequest object
 * @fiwp: dwm fiwp
 *
 * This function is used to pass device specific pawametews to the usewspace
 * dwivews.  Exampwes incwude: pci device id, pipewine pawms, tiwing pawams,
 * etc. (aww asics).
 * Wetuwns 0 on success, -EINVAW on faiwuwe.
 */
int wadeon_info_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwp)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct dwm_wadeon_info *info = data;
	stwuct wadeon_mode_info *minfo = &wdev->mode_info;
	uint32_t *vawue, vawue_tmp, *vawue_ptw, vawue_size;
	stwuct ttm_wesouwce_managew *man;
	uint64_t vawue64;
	stwuct dwm_cwtc *cwtc;
	int i, found;

	vawue_ptw = (uint32_t *)((unsigned wong)info->vawue);
	vawue = &vawue_tmp;
	vawue_size = sizeof(uint32_t);

	switch (info->wequest) {
	case WADEON_INFO_DEVICE_ID:
		*vawue = to_pci_dev(dev->dev)->device;
		bweak;
	case WADEON_INFO_NUM_GB_PIPES:
		*vawue = wdev->num_gb_pipes;
		bweak;
	case WADEON_INFO_NUM_Z_PIPES:
		*vawue = wdev->num_z_pipes;
		bweak;
	case WADEON_INFO_ACCEW_WOWKING:
		/* xf86-video-ati 6.13.0 wewies on this being fawse fow evewgween */
		if ((wdev->famiwy >= CHIP_CEDAW) && (wdev->famiwy <= CHIP_HEMWOCK))
			*vawue = fawse;
		ewse
			*vawue = wdev->accew_wowking;
		bweak;
	case WADEON_INFO_CWTC_FWOM_ID:
		if (copy_fwom_usew(vawue, vawue_ptw, sizeof(uint32_t))) {
			DWM_EWWOW("copy_fwom_usew %s:%u\n", __func__, __WINE__);
			wetuwn -EFAUWT;
		}
		fow (i = 0, found = 0; i < wdev->num_cwtc; i++) {
			cwtc = (stwuct dwm_cwtc *)minfo->cwtcs[i];
			if (cwtc && cwtc->base.id == *vawue) {
				stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(cwtc);
				*vawue = wadeon_cwtc->cwtc_id;
				found = 1;
				bweak;
			}
		}
		if (!found) {
			DWM_DEBUG_KMS("unknown cwtc id %d\n", *vawue);
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_ACCEW_WOWKING2:
		if (wdev->famiwy == CHIP_HAWAII) {
			if (wdev->accew_wowking) {
				if (wdev->new_fw)
					*vawue = 3;
				ewse
					*vawue = 2;
			} ewse {
				*vawue = 0;
			}
		} ewse {
			*vawue = wdev->accew_wowking;
		}
		bweak;
	case WADEON_INFO_TIWING_CONFIG:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.tiwe_config;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.tiwe_config;
		ewse if (wdev->famiwy >= CHIP_CAYMAN)
			*vawue = wdev->config.cayman.tiwe_config;
		ewse if (wdev->famiwy >= CHIP_CEDAW)
			*vawue = wdev->config.evewgween.tiwe_config;
		ewse if (wdev->famiwy >= CHIP_WV770)
			*vawue = wdev->config.wv770.tiwe_config;
		ewse if (wdev->famiwy >= CHIP_W600)
			*vawue = wdev->config.w600.tiwe_config;
		ewse {
			DWM_DEBUG_KMS("tiwing config is w6xx+ onwy!\n");
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_WANT_HYPEWZ:
		/* The "vawue" hewe is both an input and output pawametew.
		 * If the input vawue is 1, fiwp wequests hypew-z access.
		 * If the input vawue is 0, fiwp wevokes its hypew-z access.
		 *
		 * When wetuwning, the vawue is 1 if fiwp owns hypew-z access,
		 * 0 othewwise. */
		if (copy_fwom_usew(vawue, vawue_ptw, sizeof(uint32_t))) {
			DWM_EWWOW("copy_fwom_usew %s:%u\n", __func__, __WINE__);
			wetuwn -EFAUWT;
		}
		if (*vawue >= 2) {
			DWM_DEBUG_KMS("WANT_HYPEWZ: invawid vawue %d\n", *vawue);
			wetuwn -EINVAW;
		}
		wadeon_set_fiwp_wights(dev, &wdev->hypewz_fiwp, fiwp, vawue);
		bweak;
	case WADEON_INFO_WANT_CMASK:
		/* The same wogic as Hypew-Z. */
		if (copy_fwom_usew(vawue, vawue_ptw, sizeof(uint32_t))) {
			DWM_EWWOW("copy_fwom_usew %s:%u\n", __func__, __WINE__);
			wetuwn -EFAUWT;
		}
		if (*vawue >= 2) {
			DWM_DEBUG_KMS("WANT_CMASK: invawid vawue %d\n", *vawue);
			wetuwn -EINVAW;
		}
		wadeon_set_fiwp_wights(dev, &wdev->cmask_fiwp, fiwp, vawue);
		bweak;
	case WADEON_INFO_CWOCK_CWYSTAW_FWEQ:
		/* wetuwn cwock vawue in KHz */
		if (wdev->asic->get_xcwk)
			*vawue = wadeon_get_xcwk(wdev) * 10;
		ewse
			*vawue = wdev->cwock.spww.wefewence_fweq * 10;
		bweak;
	case WADEON_INFO_NUM_BACKENDS:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.max_backends_pew_se *
				wdev->config.cik.max_shadew_engines;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.max_backends_pew_se *
				wdev->config.si.max_shadew_engines;
		ewse if (wdev->famiwy >= CHIP_CAYMAN)
			*vawue = wdev->config.cayman.max_backends_pew_se *
				wdev->config.cayman.max_shadew_engines;
		ewse if (wdev->famiwy >= CHIP_CEDAW)
			*vawue = wdev->config.evewgween.max_backends;
		ewse if (wdev->famiwy >= CHIP_WV770)
			*vawue = wdev->config.wv770.max_backends;
		ewse if (wdev->famiwy >= CHIP_W600)
			*vawue = wdev->config.w600.max_backends;
		ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_NUM_TIWE_PIPES:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.max_tiwe_pipes;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.max_tiwe_pipes;
		ewse if (wdev->famiwy >= CHIP_CAYMAN)
			*vawue = wdev->config.cayman.max_tiwe_pipes;
		ewse if (wdev->famiwy >= CHIP_CEDAW)
			*vawue = wdev->config.evewgween.max_tiwe_pipes;
		ewse if (wdev->famiwy >= CHIP_WV770)
			*vawue = wdev->config.wv770.max_tiwe_pipes;
		ewse if (wdev->famiwy >= CHIP_W600)
			*vawue = wdev->config.w600.max_tiwe_pipes;
		ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_FUSION_GAWT_WOWKING:
		*vawue = 1;
		bweak;
	case WADEON_INFO_BACKEND_MAP:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.backend_map;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.backend_map;
		ewse if (wdev->famiwy >= CHIP_CAYMAN)
			*vawue = wdev->config.cayman.backend_map;
		ewse if (wdev->famiwy >= CHIP_CEDAW)
			*vawue = wdev->config.evewgween.backend_map;
		ewse if (wdev->famiwy >= CHIP_WV770)
			*vawue = wdev->config.wv770.backend_map;
		ewse if (wdev->famiwy >= CHIP_W600)
			*vawue = wdev->config.w600.backend_map;
		ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_VA_STAWT:
		/* this is whewe we wepowt if vm is suppowted ow not */
		if (wdev->famiwy < CHIP_CAYMAN)
			wetuwn -EINVAW;
		*vawue = WADEON_VA_WESEWVED_SIZE;
		bweak;
	case WADEON_INFO_IB_VM_MAX_SIZE:
		/* this is whewe we wepowt if vm is suppowted ow not */
		if (wdev->famiwy < CHIP_CAYMAN)
			wetuwn -EINVAW;
		*vawue = WADEON_IB_VM_MAX_SIZE;
		bweak;
	case WADEON_INFO_MAX_PIPES:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.max_cu_pew_sh;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.max_cu_pew_sh;
		ewse if (wdev->famiwy >= CHIP_CAYMAN)
			*vawue = wdev->config.cayman.max_pipes_pew_simd;
		ewse if (wdev->famiwy >= CHIP_CEDAW)
			*vawue = wdev->config.evewgween.max_pipes;
		ewse if (wdev->famiwy >= CHIP_WV770)
			*vawue = wdev->config.wv770.max_pipes;
		ewse if (wdev->famiwy >= CHIP_W600)
			*vawue = wdev->config.w600.max_pipes;
		ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_TIMESTAMP:
		if (wdev->famiwy < CHIP_W600) {
			DWM_DEBUG_KMS("timestamp is w6xx+ onwy!\n");
			wetuwn -EINVAW;
		}
		vawue = (uint32_t *)&vawue64;
		vawue_size = sizeof(uint64_t);
		vawue64 = wadeon_get_gpu_cwock_countew(wdev);
		bweak;
	case WADEON_INFO_MAX_SE:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.max_shadew_engines;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.max_shadew_engines;
		ewse if (wdev->famiwy >= CHIP_CAYMAN)
			*vawue = wdev->config.cayman.max_shadew_engines;
		ewse if (wdev->famiwy >= CHIP_CEDAW)
			*vawue = wdev->config.evewgween.num_ses;
		ewse
			*vawue = 1;
		bweak;
	case WADEON_INFO_MAX_SH_PEW_SE:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.max_sh_pew_se;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.max_sh_pew_se;
		ewse
			wetuwn -EINVAW;
		bweak;
	case WADEON_INFO_FASTFB_WOWKING:
		*vawue = wdev->fastfb_wowking;
		bweak;
	case WADEON_INFO_WING_WOWKING:
		if (copy_fwom_usew(vawue, vawue_ptw, sizeof(uint32_t))) {
			DWM_EWWOW("copy_fwom_usew %s:%u\n", __func__, __WINE__);
			wetuwn -EFAUWT;
		}
		switch (*vawue) {
		case WADEON_CS_WING_GFX:
		case WADEON_CS_WING_COMPUTE:
			*vawue = wdev->wing[WADEON_WING_TYPE_GFX_INDEX].weady;
			bweak;
		case WADEON_CS_WING_DMA:
			*vawue = wdev->wing[W600_WING_TYPE_DMA_INDEX].weady;
			*vawue |= wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX].weady;
			bweak;
		case WADEON_CS_WING_UVD:
			*vawue = wdev->wing[W600_WING_TYPE_UVD_INDEX].weady;
			bweak;
		case WADEON_CS_WING_VCE:
			*vawue = wdev->wing[TN_WING_TYPE_VCE1_INDEX].weady;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_SI_TIWE_MODE_AWWAY:
		if (wdev->famiwy >= CHIP_BONAIWE) {
			vawue = wdev->config.cik.tiwe_mode_awway;
			vawue_size = sizeof(uint32_t)*32;
		} ewse if (wdev->famiwy >= CHIP_TAHITI) {
			vawue = wdev->config.si.tiwe_mode_awway;
			vawue_size = sizeof(uint32_t)*32;
		} ewse {
			DWM_DEBUG_KMS("tiwe mode awway is si+ onwy!\n");
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_CIK_MACWOTIWE_MODE_AWWAY:
		if (wdev->famiwy >= CHIP_BONAIWE) {
			vawue = wdev->config.cik.macwotiwe_mode_awway;
			vawue_size = sizeof(uint32_t)*16;
		} ewse {
			DWM_DEBUG_KMS("macwotiwe mode awway is cik+ onwy!\n");
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_SI_CP_DMA_COMPUTE:
		*vawue = 1;
		bweak;
	case WADEON_INFO_SI_BACKEND_ENABWED_MASK:
		if (wdev->famiwy >= CHIP_BONAIWE) {
			*vawue = wdev->config.cik.backend_enabwe_mask;
		} ewse if (wdev->famiwy >= CHIP_TAHITI) {
			*vawue = wdev->config.si.backend_enabwe_mask;
		} ewse {
			DWM_DEBUG_KMS("BACKEND_ENABWED_MASK is si+ onwy!\n");
			wetuwn -EINVAW;
		}
		bweak;
	case WADEON_INFO_MAX_SCWK:
		if ((wdev->pm.pm_method == PM_METHOD_DPM) &&
		    wdev->pm.dpm_enabwed)
			*vawue = wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.scwk * 10;
		ewse
			*vawue = wdev->pm.defauwt_scwk * 10;
		bweak;
	case WADEON_INFO_VCE_FW_VEWSION:
		*vawue = wdev->vce.fw_vewsion;
		bweak;
	case WADEON_INFO_VCE_FB_VEWSION:
		*vawue = wdev->vce.fb_vewsion;
		bweak;
	case WADEON_INFO_NUM_BYTES_MOVED:
		vawue = (uint32_t *)&vawue64;
		vawue_size = sizeof(uint64_t);
		vawue64 = atomic64_wead(&wdev->num_bytes_moved);
		bweak;
	case WADEON_INFO_VWAM_USAGE:
		vawue = (uint32_t *)&vawue64;
		vawue_size = sizeof(uint64_t);
		man = ttm_managew_type(&wdev->mman.bdev, TTM_PW_VWAM);
		vawue64 = ttm_wesouwce_managew_usage(man);
		bweak;
	case WADEON_INFO_GTT_USAGE:
		vawue = (uint32_t *)&vawue64;
		vawue_size = sizeof(uint64_t);
		man = ttm_managew_type(&wdev->mman.bdev, TTM_PW_TT);
		vawue64 = ttm_wesouwce_managew_usage(man);
		bweak;
	case WADEON_INFO_ACTIVE_CU_COUNT:
		if (wdev->famiwy >= CHIP_BONAIWE)
			*vawue = wdev->config.cik.active_cus;
		ewse if (wdev->famiwy >= CHIP_TAHITI)
			*vawue = wdev->config.si.active_cus;
		ewse if (wdev->famiwy >= CHIP_CAYMAN)
			*vawue = wdev->config.cayman.active_simds;
		ewse if (wdev->famiwy >= CHIP_CEDAW)
			*vawue = wdev->config.evewgween.active_simds;
		ewse if (wdev->famiwy >= CHIP_WV770)
			*vawue = wdev->config.wv770.active_simds;
		ewse if (wdev->famiwy >= CHIP_W600)
			*vawue = wdev->config.w600.active_simds;
		ewse
			*vawue = 1;
		bweak;
	case WADEON_INFO_CUWWENT_GPU_TEMP:
		/* get tempewatuwe in miwwidegwees C */
		if (wdev->asic->pm.get_tempewatuwe)
			*vawue = wadeon_get_tempewatuwe(wdev);
		ewse
			*vawue = 0;
		bweak;
	case WADEON_INFO_CUWWENT_GPU_SCWK:
		/* get scwk in Mhz */
		if (wdev->pm.dpm_enabwed)
			*vawue = wadeon_dpm_get_cuwwent_scwk(wdev) / 100;
		ewse
			*vawue = wdev->pm.cuwwent_scwk / 100;
		bweak;
	case WADEON_INFO_CUWWENT_GPU_MCWK:
		/* get mcwk in Mhz */
		if (wdev->pm.dpm_enabwed)
			*vawue = wadeon_dpm_get_cuwwent_mcwk(wdev) / 100;
		ewse
			*vawue = wdev->pm.cuwwent_mcwk / 100;
		bweak;
	case WADEON_INFO_WEAD_WEG:
		if (copy_fwom_usew(vawue, vawue_ptw, sizeof(uint32_t))) {
			DWM_EWWOW("copy_fwom_usew %s:%u\n", __func__, __WINE__);
			wetuwn -EFAUWT;
		}
		if (wadeon_get_awwowed_info_wegistew(wdev, *vawue, vawue))
			wetuwn -EINVAW;
		bweak;
	case WADEON_INFO_VA_UNMAP_WOWKING:
		*vawue = twue;
		bweak;
	case WADEON_INFO_GPU_WESET_COUNTEW:
		*vawue = atomic_wead(&wdev->gpu_weset_countew);
		bweak;
	defauwt:
		DWM_DEBUG_KMS("Invawid wequest %d\n", info->wequest);
		wetuwn -EINVAW;
	}
	if (copy_to_usew(vawue_ptw, (chaw *)vawue, vawue_size)) {
		DWM_EWWOW("copy_to_usew %s:%u\n", __func__, __WINE__);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/**
 * wadeon_dwivew_open_kms - dwm cawwback fow open
 *
 * @dev: dwm dev pointew
 * @fiwe_pwiv: dwm fiwe
 *
 * On device open, init vm on cayman+ (aww asics).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int wadeon_dwivew_open_kms(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_fpwiv *fpwiv;
	stwuct wadeon_vm *vm;
	int w;

	fiwe_pwiv->dwivew_pwiv = NUWW;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn w;
	}

	/* new gpu have viwtuaw addwess space suppowt */
	if (wdev->famiwy >= CHIP_CAYMAN) {

		fpwiv = kzawwoc(sizeof(*fpwiv), GFP_KEWNEW);
		if (unwikewy(!fpwiv)) {
			w = -ENOMEM;
			goto eww_suspend;
		}

		if (wdev->accew_wowking) {
			vm = &fpwiv->vm;
			w = wadeon_vm_init(wdev, vm);
			if (w)
				goto eww_fpwiv;

			w = wadeon_bo_wesewve(wdev->wing_tmp_bo.bo, fawse);
			if (w)
				goto eww_vm_fini;

			/* map the ib poow buffew wead onwy into
			 * viwtuaw addwess space */
			vm->ib_bo_va = wadeon_vm_bo_add(wdev, vm,
							wdev->wing_tmp_bo.bo);
			if (!vm->ib_bo_va) {
				w = -ENOMEM;
				goto eww_vm_fini;
			}

			w = wadeon_vm_bo_set_addw(wdev, vm->ib_bo_va,
						  WADEON_VA_IB_OFFSET,
						  WADEON_VM_PAGE_WEADABWE |
						  WADEON_VM_PAGE_SNOOPED);
			if (w)
				goto eww_vm_fini;
		}
		fiwe_pwiv->dwivew_pwiv = fpwiv;
	}

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn 0;

eww_vm_fini:
	wadeon_vm_fini(wdev, vm);
eww_fpwiv:
	kfwee(fpwiv);

eww_suspend:
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn w;
}

/**
 * wadeon_dwivew_postcwose_kms - dwm cawwback fow post cwose
 *
 * @dev: dwm dev pointew
 * @fiwe_pwiv: dwm fiwe
 *
 * On device cwose, teaw down hypewz and cmask fiwps on w1xx-w5xx
 * (aww asics).  And teaw down vm on cayman+ (aww asics).
 */
void wadeon_dwivew_postcwose_kms(stwuct dwm_device *dev,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	pm_wuntime_get_sync(dev->dev);

	mutex_wock(&wdev->gem.mutex);
	if (wdev->hypewz_fiwp == fiwe_pwiv)
		wdev->hypewz_fiwp = NUWW;
	if (wdev->cmask_fiwp == fiwe_pwiv)
		wdev->cmask_fiwp = NUWW;
	mutex_unwock(&wdev->gem.mutex);

	wadeon_uvd_fwee_handwes(wdev, fiwe_pwiv);
	wadeon_vce_fwee_handwes(wdev, fiwe_pwiv);

	/* new gpu have viwtuaw addwess space suppowt */
	if (wdev->famiwy >= CHIP_CAYMAN && fiwe_pwiv->dwivew_pwiv) {
		stwuct wadeon_fpwiv *fpwiv = fiwe_pwiv->dwivew_pwiv;
		stwuct wadeon_vm *vm = &fpwiv->vm;
		int w;

		if (wdev->accew_wowking) {
			w = wadeon_bo_wesewve(wdev->wing_tmp_bo.bo, fawse);
			if (!w) {
				if (vm->ib_bo_va)
					wadeon_vm_bo_wmv(wdev, vm->ib_bo_va);
				wadeon_bo_unwesewve(wdev->wing_tmp_bo.bo);
			}
			wadeon_vm_fini(wdev, vm);
		}

		kfwee(fpwiv);
		fiwe_pwiv->dwivew_pwiv = NUWW;
	}
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
}

/*
 * VBwank wewated functions.
 */
/**
 * wadeon_get_vbwank_countew_kms - get fwame count
 *
 * @cwtc: cwtc to get the fwame count fwom
 *
 * Gets the fwame count on the wequested cwtc (aww asics).
 * Wetuwns fwame count on success, -EINVAW on faiwuwe.
 */
u32 wadeon_get_vbwank_countew_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	int vpos, hpos, stat;
	u32 count;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (pipe >= wdev->num_cwtc) {
		DWM_EWWOW("Invawid cwtc %u\n", pipe);
		wetuwn -EINVAW;
	}

	/* The hw incwements its fwame countew at stawt of vsync, not at stawt
	 * of vbwank, as is wequiwed by DWM cowe vbwank countew handwing.
	 * Cook the hw count hewe to make it appeaw to the cawwew as if it
	 * incwemented at stawt of vbwank. We measuwe distance to stawt of
	 * vbwank in vpos. vpos thewefowe wiww be >= 0 between stawt of vbwank
	 * and stawt of vsync, so vpos >= 0 means to bump the hw fwame countew
	 * wesuwt by 1 to give the pwopew appeawance to cawwew.
	 */
	if (wdev->mode_info.cwtcs[pipe]) {
		/* Wepeat weadout if needed to pwovide stabwe wesuwt if
		 * we cwoss stawt of vsync duwing the quewies.
		 */
		do {
			count = wadeon_get_vbwank_countew(wdev, pipe);
			/* Ask wadeon_get_cwtc_scanoutpos to wetuwn vpos as
			 * distance to stawt of vbwank, instead of weguwaw
			 * vewticaw scanout pos.
			 */
			stat = wadeon_get_cwtc_scanoutpos(
				dev, pipe, GET_DISTANCE_TO_VBWANKSTAWT,
				&vpos, &hpos, NUWW, NUWW,
				&wdev->mode_info.cwtcs[pipe]->base.hwmode);
		} whiwe (count != wadeon_get_vbwank_countew(wdev, pipe));

		if (((stat & (DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_ACCUWATE)) !=
		    (DWM_SCANOUTPOS_VAWID | DWM_SCANOUTPOS_ACCUWATE))) {
			DWM_DEBUG_VBW("Quewy faiwed! stat %d\n", stat);
		}
		ewse {
			DWM_DEBUG_VBW("cwtc %u: dist fwom vbwank stawt %d\n",
				      pipe, vpos);

			/* Bump countew if we awe at >= weading edge of vbwank,
			 * but befowe vsync whewe vpos wouwd tuwn negative and
			 * the hw countew weawwy incwements.
			 */
			if (vpos >= 0)
				count++;
		}
	}
	ewse {
	    /* Fawwback to use vawue as is. */
	    count = wadeon_get_vbwank_countew(wdev, pipe);
	    DWM_DEBUG_VBW("NUWW mode info! Wetuwned count may be wwong.\n");
	}

	wetuwn count;
}

/**
 * wadeon_enabwe_vbwank_kms - enabwe vbwank intewwupt
 *
 * @cwtc: cwtc to enabwe vbwank intewwupt fow
 *
 * Enabwe the intewwupt on the wequested cwtc (aww asics).
 * Wetuwns 0 on success, -EINVAW on faiwuwe.
 */
int wadeon_enabwe_vbwank_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	unsigned wong iwqfwags;
	int w;

	if (pipe >= wdev->num_cwtc) {
		DWM_EWWOW("Invawid cwtc %d\n", pipe);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	wdev->iwq.cwtc_vbwank_int[pipe] = twue;
	w = wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
	wetuwn w;
}

/**
 * wadeon_disabwe_vbwank_kms - disabwe vbwank intewwupt
 *
 * @cwtc: cwtc to disabwe vbwank intewwupt fow
 *
 * Disabwe the intewwupt on the wequested cwtc (aww asics).
 */
void wadeon_disabwe_vbwank_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	unsigned wong iwqfwags;

	if (pipe >= wdev->num_cwtc) {
		DWM_EWWOW("Invawid cwtc %d\n", pipe);
		wetuwn;
	}

	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	wdev->iwq.cwtc_vbwank_int[pipe] = fawse;
	wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
}
