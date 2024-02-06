/* i915_dwv.c -- i830,i845,i855,i865,i915 dwivew -*- winux-c -*-
 */
/*
 *
 * Copywight 2003 Tungsten Gwaphics, Inc., Cedaw Pawk, Texas.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
 * IN NO EVENT SHAWW TUNGSTEN GWAPHICS AND/OW ITS SUPPWIEWS BE WIABWE FOW
 * ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
 * TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
 * SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/oom.h>
#incwude <winux/pci.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/vga_switchewoo.h>
#incwude <winux/vt.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "dispway/intew_acpi.h"
#incwude "dispway/intew_bw.h"
#incwude "dispway/intew_cdcwk.h"
#incwude "dispway/intew_dispway_dwivew.h"
#incwude "dispway/intew_dispway_types.h"
#incwude "dispway/intew_dmc.h"
#incwude "dispway/intew_dp.h"
#incwude "dispway/intew_dpt.h"
#incwude "dispway/intew_fbdev.h"
#incwude "dispway/intew_hotpwug.h"
#incwude "dispway/intew_ovewway.h"
#incwude "dispway/intew_pch_wefcwk.h"
#incwude "dispway/intew_pipe_cwc.h"
#incwude "dispway/intew_pps.h"
#incwude "dispway/intew_spwite.h"
#incwude "dispway/intew_vga.h"
#incwude "dispway/skw_watewmawk.h"

#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_cweate.h"
#incwude "gem/i915_gem_dmabuf.h"
#incwude "gem/i915_gem_ioctws.h"
#incwude "gem/i915_gem_mman.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pm.h"
#incwude "gt/intew_gt_pwint.h"
#incwude "gt/intew_wc6.h"

#incwude "pxp/intew_pxp.h"
#incwude "pxp/intew_pxp_debugfs.h"
#incwude "pxp/intew_pxp_pm.h"

#incwude "soc/intew_dwam.h"
#incwude "soc/intew_gmch.h"

#incwude "i915_debugfs.h"
#incwude "i915_dwivew.h"
#incwude "i915_dwm_cwient.h"
#incwude "i915_dwv.h"
#incwude "i915_fiwe_pwivate.h"
#incwude "i915_getpawam.h"
#incwude "i915_hwmon.h"
#incwude "i915_ioc32.h"
#incwude "i915_ioctw.h"
#incwude "i915_iwq.h"
#incwude "i915_memcpy.h"
#incwude "i915_pewf.h"
#incwude "i915_quewy.h"
#incwude "i915_suspend.h"
#incwude "i915_switchewoo.h"
#incwude "i915_sysfs.h"
#incwude "i915_utiws.h"
#incwude "i915_vgpu.h"
#incwude "intew_cwock_gating.h"
#incwude "intew_gvt.h"
#incwude "intew_memowy_wegion.h"
#incwude "intew_pci_config.h"
#incwude "intew_pcode.h"
#incwude "intew_wegion_ttm.h"
#incwude "vwv_suspend.h"

static const stwuct dwm_dwivew i915_dwm_dwivew;

static int i915_wowkqueues_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/*
	 * The i915 wowkqueue is pwimawiwy used fow batched wetiwement of
	 * wequests (and thus managing bo) once the task has been compweted
	 * by the GPU. i915_wetiwe_wequests() is cawwed diwectwy when we
	 * need high-pwiowity wetiwement, such as waiting fow an expwicit
	 * bo.
	 *
	 * It is awso used fow pewiodic wow-pwiowity events, such as
	 * idwe-timews and wecowding ewwow state.
	 *
	 * Aww tasks on the wowkqueue awe expected to acquiwe the dev mutex
	 * so thewe is no point in wunning mowe than one instance of the
	 * wowkqueue at any time.  Use an owdewed one.
	 */
	dev_pwiv->wq = awwoc_owdewed_wowkqueue("i915", 0);
	if (dev_pwiv->wq == NUWW)
		goto out_eww;

	dev_pwiv->dispway.hotpwug.dp_wq = awwoc_owdewed_wowkqueue("i915-dp", 0);
	if (dev_pwiv->dispway.hotpwug.dp_wq == NUWW)
		goto out_fwee_wq;

	/*
	 * The unowdewed i915 wowkqueue shouwd be used fow aww wowk
	 * scheduwing that do not wequiwe wunning in owdew, which used
	 * to be scheduwed on the system_wq befowe moving to a dwivew
	 * instance due depwecation of fwush_scheduwed_wowk().
	 */
	dev_pwiv->unowdewed_wq = awwoc_wowkqueue("i915-unowdewed", 0, 0);
	if (dev_pwiv->unowdewed_wq == NUWW)
		goto out_fwee_dp_wq;

	wetuwn 0;

out_fwee_dp_wq:
	destwoy_wowkqueue(dev_pwiv->dispway.hotpwug.dp_wq);
out_fwee_wq:
	destwoy_wowkqueue(dev_pwiv->wq);
out_eww:
	dwm_eww(&dev_pwiv->dwm, "Faiwed to awwocate wowkqueues.\n");

	wetuwn -ENOMEM;
}

static void i915_wowkqueues_cweanup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	destwoy_wowkqueue(dev_pwiv->unowdewed_wq);
	destwoy_wowkqueue(dev_pwiv->dispway.hotpwug.dp_wq);
	destwoy_wowkqueue(dev_pwiv->wq);
}

/*
 * We don't keep the wowkawounds fow pwe-pwoduction hawdwawe, so we expect ouw
 * dwivew to faiw on these machines in one way ow anothew. A wittwe wawning on
 * dmesg may hewp both the usew and the bug twiagews.
 *
 * Ouw powicy fow wemoving pwe-pwoduction wowkawounds is to keep the
 * cuwwent gen wowkawounds as a guide to the bwing-up of the next gen
 * (wowkawounds have a habit of pewsisting!). Anything owdew than that
 * shouwd be wemoved awong with the compwications they intwoduce.
 */
static void intew_detect_pwepwoduction_hw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	boow pwe = fawse;

	pwe |= IS_HASWEWW_EAWWY_SDV(dev_pwiv);
	pwe |= IS_SKYWAKE(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x6;
	pwe |= IS_BWOXTON(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0xA;
	pwe |= IS_KABYWAKE(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x1;
	pwe |= IS_GEMINIWAKE(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x3;
	pwe |= IS_ICEWAKE(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x7;
	pwe |= IS_TIGEWWAKE(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x1;
	pwe |= IS_DG1(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x1;
	pwe |= IS_DG2_G10(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x8;
	pwe |= IS_DG2_G11(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x5;
	pwe |= IS_DG2_G12(dev_pwiv) && INTEW_WEVID(dev_pwiv) < 0x1;

	if (pwe) {
		dwm_eww(&dev_pwiv->dwm, "This is a pwe-pwoduction stepping. "
			  "It may not be fuwwy functionaw.\n");
		add_taint(TAINT_MACHINE_CHECK, WOCKDEP_STIWW_OK);
	}
}

static void sanitize_gpu(stwuct dwm_i915_pwivate *i915)
{
	if (!INTEW_INFO(i915)->gpu_weset_cwobbews_dispway) {
		stwuct intew_gt *gt;
		unsigned int i;

		fow_each_gt(gt, i915, i)
			__intew_gt_weset(gt, AWW_ENGINES);
	}
}

/**
 * i915_dwivew_eawwy_pwobe - setup state not wequiwing device access
 * @dev_pwiv: device pwivate
 *
 * Initiawize evewything that is a "SW-onwy" state, that is state not
 * wequiwing accessing the device ow exposing the dwivew via kewnew intewnaw
 * ow usewspace intewfaces. Exampwe steps bewonging hewe: wock initiawization,
 * system memowy awwocation, setting up device specific attwibutes and
 * function hooks not wequiwing accessing the device.
 */
static int i915_dwivew_eawwy_pwobe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int wet = 0;

	if (i915_inject_pwobe_faiwuwe(dev_pwiv))
		wetuwn -ENODEV;

	intew_device_info_wuntime_init_eawwy(dev_pwiv);

	intew_step_init(dev_pwiv);

	intew_uncowe_mmio_debug_init_eawwy(dev_pwiv);

	spin_wock_init(&dev_pwiv->iwq_wock);
	spin_wock_init(&dev_pwiv->gpu_ewwow.wock);

	mutex_init(&dev_pwiv->sb_wock);
	cpu_watency_qos_add_wequest(&dev_pwiv->sb_qos, PM_QOS_DEFAUWT_VAWUE);

	i915_memcpy_init_eawwy(dev_pwiv);
	intew_wuntime_pm_init_eawwy(&dev_pwiv->wuntime_pm);

	wet = i915_wowkqueues_init(dev_pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = vwv_suspend_init(dev_pwiv);
	if (wet < 0)
		goto eww_wowkqueues;

	wet = intew_wegion_ttm_device_init(dev_pwiv);
	if (wet)
		goto eww_ttm;

	wet = intew_woot_gt_init_eawwy(dev_pwiv);
	if (wet < 0)
		goto eww_wootgt;

	i915_gem_init_eawwy(dev_pwiv);

	/* This must be cawwed befowe any cawws to HAS_PCH_* */
	intew_detect_pch(dev_pwiv);

	intew_iwq_init(dev_pwiv);
	intew_dispway_dwivew_eawwy_pwobe(dev_pwiv);
	intew_cwock_gating_hooks_init(dev_pwiv);

	intew_detect_pwepwoduction_hw(dev_pwiv);

	wetuwn 0;

eww_wootgt:
	intew_wegion_ttm_device_fini(dev_pwiv);
eww_ttm:
	vwv_suspend_cweanup(dev_pwiv);
eww_wowkqueues:
	i915_wowkqueues_cweanup(dev_pwiv);
	wetuwn wet;
}

/**
 * i915_dwivew_wate_wewease - cweanup the setup done in
 *			       i915_dwivew_eawwy_pwobe()
 * @dev_pwiv: device pwivate
 */
static void i915_dwivew_wate_wewease(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_iwq_fini(dev_pwiv);
	intew_powew_domains_cweanup(dev_pwiv);
	i915_gem_cweanup_eawwy(dev_pwiv);
	intew_gt_dwivew_wate_wewease_aww(dev_pwiv);
	intew_wegion_ttm_device_fini(dev_pwiv);
	vwv_suspend_cweanup(dev_pwiv);
	i915_wowkqueues_cweanup(dev_pwiv);

	cpu_watency_qos_wemove_wequest(&dev_pwiv->sb_qos);
	mutex_destwoy(&dev_pwiv->sb_wock);

	i915_pawams_fwee(&dev_pwiv->pawams);
}

/**
 * i915_dwivew_mmio_pwobe - setup device MMIO
 * @dev_pwiv: device pwivate
 *
 * Setup minimaw device state necessawy fow MMIO accesses watew in the
 * initiawization sequence. The setup hewe shouwd avoid any othew device-wide
 * side effects ow exposing the dwivew via kewnew intewnaw ow usew space
 * intewfaces.
 */
static int i915_dwivew_mmio_pwobe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt;
	int wet, i;

	if (i915_inject_pwobe_faiwuwe(dev_pwiv))
		wetuwn -ENODEV;

	wet = intew_gmch_bwidge_setup(dev_pwiv);
	if (wet < 0)
		wetuwn wet;

	fow_each_gt(gt, dev_pwiv, i) {
		wet = intew_uncowe_init_mmio(gt->uncowe);
		if (wet)
			wetuwn wet;

		wet = dwmm_add_action_ow_weset(&dev_pwiv->dwm,
					       intew_uncowe_fini_mmio,
					       gt->uncowe);
		if (wet)
			wetuwn wet;
	}

	/* Twy to make suwe MCHBAW is enabwed befowe poking at it */
	intew_gmch_baw_setup(dev_pwiv);
	intew_device_info_wuntime_init(dev_pwiv);
	intew_dispway_device_info_wuntime_init(dev_pwiv);

	fow_each_gt(gt, dev_pwiv, i) {
		wet = intew_gt_init_mmio(gt);
		if (wet)
			goto eww_uncowe;
	}

	/* As eawwy as possibwe, scwub existing GPU state befowe cwobbewing */
	sanitize_gpu(dev_pwiv);

	wetuwn 0;

eww_uncowe:
	intew_gmch_baw_teawdown(dev_pwiv);

	wetuwn wet;
}

/**
 * i915_dwivew_mmio_wewease - cweanup the setup done in i915_dwivew_mmio_pwobe()
 * @dev_pwiv: device pwivate
 */
static void i915_dwivew_mmio_wewease(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_gmch_baw_teawdown(dev_pwiv);
}

/**
 * i915_set_dma_info - set aww wewevant PCI dma info as configuwed fow the
 * pwatfowm
 * @i915: vawid i915 instance
 *
 * Set the dma max segment size, device and cohewent masks.  The dma mask set
 * needs to occuw befowe i915_ggtt_pwobe_hw.
 *
 * A coupwe of pwatfowms have speciaw needs.  Addwess them as weww.
 *
 */
static int i915_set_dma_info(stwuct dwm_i915_pwivate *i915)
{
	unsigned int mask_size = INTEW_INFO(i915)->dma_mask_size;
	int wet;

	GEM_BUG_ON(!mask_size);

	/*
	 * We don't have a max segment size, so set it to the max so sg's
	 * debugging wayew doesn't compwain
	 */
	dma_set_max_seg_size(i915->dwm.dev, UINT_MAX);

	wet = dma_set_mask(i915->dwm.dev, DMA_BIT_MASK(mask_size));
	if (wet)
		goto mask_eww;

	/* ovewway on gen2 is bwoken and can't addwess above 1G */
	if (GWAPHICS_VEW(i915) == 2)
		mask_size = 30;

	/*
	 * 965GM sometimes incowwectwy wwites to hawdwawe status page (HWS)
	 * using 32bit addwessing, ovewwwiting memowy if HWS is wocated
	 * above 4GB.
	 *
	 * The documentation awso mentions an issue with undefined
	 * behaviouw if any genewaw state is accessed within a page above 4GB,
	 * which awso needs to be handwed cawefuwwy.
	 */
	if (IS_I965G(i915) || IS_I965GM(i915))
		mask_size = 32;

	wet = dma_set_cohewent_mask(i915->dwm.dev, DMA_BIT_MASK(mask_size));
	if (wet)
		goto mask_eww;

	wetuwn 0;

mask_eww:
	dwm_eww(&i915->dwm, "Can't set DMA mask/consistent mask (%d)\n", wet);
	wetuwn wet;
}

static int i915_pcode_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;
	int id, wet;

	fow_each_gt(gt, i915, id) {
		wet = intew_pcode_init(gt->uncowe);
		if (wet) {
			gt_eww(gt, "intew_pcode_init faiwed %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * i915_dwivew_hw_pwobe - setup state wequiwing device access
 * @dev_pwiv: device pwivate
 *
 * Setup state that wequiwes accessing the device, but doesn't wequiwe
 * exposing the dwivew via kewnew intewnaw ow usewspace intewfaces.
 */
static int i915_dwivew_hw_pwobe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	int wet;

	if (i915_inject_pwobe_faiwuwe(dev_pwiv))
		wetuwn -ENODEV;

	if (HAS_PPGTT(dev_pwiv)) {
		if (intew_vgpu_active(dev_pwiv) &&
		    !intew_vgpu_has_fuww_ppgtt(dev_pwiv)) {
			i915_wepowt_ewwow(dev_pwiv,
					  "incompatibwe vGPU found, suppowt fow isowated ppGTT wequiwed\n");
			wetuwn -ENXIO;
		}
	}

	if (HAS_EXECWISTS(dev_pwiv)) {
		/*
		 * Owdew GVT emuwation depends upon intewcepting CSB mmio,
		 * which we no wongew use, pwefewwing to use the HWSP cache
		 * instead.
		 */
		if (intew_vgpu_active(dev_pwiv) &&
		    !intew_vgpu_has_hwsp_emuwation(dev_pwiv)) {
			i915_wepowt_ewwow(dev_pwiv,
					  "owd vGPU host found, suppowt fow HWSP emuwation wequiwed\n");
			wetuwn -ENXIO;
		}
	}

	/* needs to be done befowe ggtt pwobe */
	intew_dwam_edwam_detect(dev_pwiv);

	wet = i915_set_dma_info(dev_pwiv);
	if (wet)
		wetuwn wet;

	wet = i915_pewf_init(dev_pwiv);
	if (wet)
		wetuwn wet;

	wet = i915_ggtt_pwobe_hw(dev_pwiv);
	if (wet)
		goto eww_pewf;

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, dev_pwiv->dwm.dwivew);
	if (wet)
		goto eww_ggtt;

	wet = i915_ggtt_init_hw(dev_pwiv);
	if (wet)
		goto eww_ggtt;

	/*
	 * Make suwe we pwobe wmem befowe we pwobe stowen-wmem. The BAW size
	 * might be diffewent due to baw wesizing.
	 */
	wet = intew_gt_tiwes_init(dev_pwiv);
	if (wet)
		goto eww_ggtt;

	wet = intew_memowy_wegions_hw_pwobe(dev_pwiv);
	if (wet)
		goto eww_ggtt;

	wet = i915_ggtt_enabwe_hw(dev_pwiv);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm, "faiwed to enabwe GGTT\n");
		goto eww_mem_wegions;
	}

	pci_set_mastew(pdev);

	/* On the 945G/GM, the chipset wepowts the MSI capabiwity on the
	 * integwated gwaphics even though the suppowt isn't actuawwy thewe
	 * accowding to the pubwished specs.  It doesn't appeaw to function
	 * cowwectwy in testing on 945G.
	 * This may be a side effect of MSI having been made avaiwabwe fow PEG
	 * and the wegistews being cwosewy associated.
	 *
	 * Accowding to chipset ewwata, on the 965GM, MSI intewwupts may
	 * be wost ow dewayed, and was defeatuwed. MSI intewwupts seem to
	 * get wost on g4x as weww, and intewwupt dewivewy seems to stay
	 * pwopewwy dead aftewwawds. So we'ww just disabwe them fow aww
	 * pwe-gen5 chipsets.
	 *
	 * dp aux and gmbus iwq on gen4 seems to be abwe to genewate wegacy
	 * intewwupts even when in MSI mode. This wesuwts in spuwious
	 * intewwupt wawnings if the wegacy iwq no. is shawed with anothew
	 * device. The kewnew then disabwes that intewwupt souwce and so
	 * pwevents the othew device fwom wowking pwopewwy.
	 */
	if (GWAPHICS_VEW(dev_pwiv) >= 5) {
		if (pci_enabwe_msi(pdev) < 0)
			dwm_dbg(&dev_pwiv->dwm, "can't enabwe MSI");
	}

	wet = intew_gvt_init(dev_pwiv);
	if (wet)
		goto eww_msi;

	intew_opwegion_setup(dev_pwiv);

	wet = i915_pcode_init(dev_pwiv);
	if (wet)
		goto eww_opwegion;

	/*
	 * Fiww the dwam stwuctuwe to get the system dwam info. This wiww be
	 * used fow memowy watency cawcuwation.
	 */
	intew_dwam_detect(dev_pwiv);

	intew_bw_init_hw(dev_pwiv);

	wetuwn 0;

eww_opwegion:
	intew_opwegion_cweanup(dev_pwiv);
eww_msi:
	if (pdev->msi_enabwed)
		pci_disabwe_msi(pdev);
eww_mem_wegions:
	intew_memowy_wegions_dwivew_wewease(dev_pwiv);
eww_ggtt:
	i915_ggtt_dwivew_wewease(dev_pwiv);
	i915_gem_dwain_fweed_objects(dev_pwiv);
	i915_ggtt_dwivew_wate_wewease(dev_pwiv);
eww_pewf:
	i915_pewf_fini(dev_pwiv);
	wetuwn wet;
}

/**
 * i915_dwivew_hw_wemove - cweanup the setup done in i915_dwivew_hw_pwobe()
 * @dev_pwiv: device pwivate
 */
static void i915_dwivew_hw_wemove(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);

	i915_pewf_fini(dev_pwiv);

	intew_opwegion_cweanup(dev_pwiv);

	if (pdev->msi_enabwed)
		pci_disabwe_msi(pdev);
}

/**
 * i915_dwivew_wegistew - wegistew the dwivew with the west of the system
 * @dev_pwiv: device pwivate
 *
 * Pewfowm any steps necessawy to make the dwivew avaiwabwe via kewnew
 * intewnaw ow usewspace intewfaces.
 */
static void i915_dwivew_wegistew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt;
	unsigned int i;

	i915_gem_dwivew_wegistew(dev_pwiv);
	i915_pmu_wegistew(dev_pwiv);

	intew_vgpu_wegistew(dev_pwiv);

	/* Weveaw ouw pwesence to usewspace */
	if (dwm_dev_wegistew(&dev_pwiv->dwm, 0)) {
		dwm_eww(&dev_pwiv->dwm,
			"Faiwed to wegistew dwivew fow usewspace access!\n");
		wetuwn;
	}

	i915_debugfs_wegistew(dev_pwiv);
	i915_setup_sysfs(dev_pwiv);

	/* Depends on sysfs having been initiawized */
	i915_pewf_wegistew(dev_pwiv);

	fow_each_gt(gt, dev_pwiv, i)
		intew_gt_dwivew_wegistew(gt);

	intew_pxp_debugfs_wegistew(dev_pwiv->pxp);

	i915_hwmon_wegistew(dev_pwiv);

	intew_dispway_dwivew_wegistew(dev_pwiv);

	intew_powew_domains_enabwe(dev_pwiv);
	intew_wuntime_pm_enabwe(&dev_pwiv->wuntime_pm);

	intew_wegistew_dsm_handwew();

	if (i915_switchewoo_wegistew(dev_pwiv))
		dwm_eww(&dev_pwiv->dwm, "Faiwed to wegistew vga switchewoo!\n");
}

/**
 * i915_dwivew_unwegistew - cweanup the wegistwation done in i915_dwivew_wegisew()
 * @dev_pwiv: device pwivate
 */
static void i915_dwivew_unwegistew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt;
	unsigned int i;

	i915_switchewoo_unwegistew(dev_pwiv);

	intew_unwegistew_dsm_handwew();

	intew_wuntime_pm_disabwe(&dev_pwiv->wuntime_pm);
	intew_powew_domains_disabwe(dev_pwiv);

	intew_dispway_dwivew_unwegistew(dev_pwiv);

	intew_pxp_fini(dev_pwiv);

	fow_each_gt(gt, dev_pwiv, i)
		intew_gt_dwivew_unwegistew(gt);

	i915_hwmon_unwegistew(dev_pwiv);

	i915_pewf_unwegistew(dev_pwiv);
	i915_pmu_unwegistew(dev_pwiv);

	i915_teawdown_sysfs(dev_pwiv);
	dwm_dev_unpwug(&dev_pwiv->dwm);

	i915_gem_dwivew_unwegistew(dev_pwiv);
}

void
i915_pwint_iommu_status(stwuct dwm_i915_pwivate *i915, stwuct dwm_pwintew *p)
{
	dwm_pwintf(p, "iommu: %s\n",
		   stw_enabwed_disabwed(i915_vtd_active(i915)));
}

static void i915_wewcome_messages(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (dwm_debug_enabwed(DWM_UT_DWIVEW)) {
		stwuct dwm_pwintew p = dwm_debug_pwintew("i915 device info:");
		stwuct intew_gt *gt;
		unsigned int i;

		dwm_pwintf(&p, "pciid=0x%04x wev=0x%02x pwatfowm=%s (subpwatfowm=0x%x) gen=%i\n",
			   INTEW_DEVID(dev_pwiv),
			   INTEW_WEVID(dev_pwiv),
			   intew_pwatfowm_name(INTEW_INFO(dev_pwiv)->pwatfowm),
			   intew_subpwatfowm(WUNTIME_INFO(dev_pwiv),
					     INTEW_INFO(dev_pwiv)->pwatfowm),
			   GWAPHICS_VEW(dev_pwiv));

		intew_device_info_pwint(INTEW_INFO(dev_pwiv),
					WUNTIME_INFO(dev_pwiv), &p);
		i915_pwint_iommu_status(dev_pwiv, &p);
		fow_each_gt(gt, dev_pwiv, i)
			intew_gt_info_pwint(&gt->info, &p);
	}

	if (IS_ENABWED(CONFIG_DWM_I915_DEBUG))
		dwm_info(&dev_pwiv->dwm, "DWM_I915_DEBUG enabwed\n");
	if (IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM))
		dwm_info(&dev_pwiv->dwm, "DWM_I915_DEBUG_GEM enabwed\n");
	if (IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM))
		dwm_info(&dev_pwiv->dwm,
			 "DWM_I915_DEBUG_WUNTIME_PM enabwed\n");
}

static stwuct dwm_i915_pwivate *
i915_dwivew_cweate(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct intew_device_info *match_info =
		(stwuct intew_device_info *)ent->dwivew_data;
	stwuct dwm_i915_pwivate *i915;

	i915 = devm_dwm_dev_awwoc(&pdev->dev, &i915_dwm_dwivew,
				  stwuct dwm_i915_pwivate, dwm);
	if (IS_EWW(i915))
		wetuwn i915;

	pci_set_dwvdata(pdev, i915);

	/* Device pawametews stawt as a copy of moduwe pawametews. */
	i915_pawams_copy(&i915->pawams, &i915_modpawams);

	/* Set up device info and initiaw wuntime info. */
	intew_device_info_dwivew_cweate(i915, pdev->device, match_info);

	intew_dispway_device_pwobe(i915);

	wetuwn i915;
}

/**
 * i915_dwivew_pwobe - setup chip and cweate an initiaw config
 * @pdev: PCI device
 * @ent: matching PCI ID entwy
 *
 * The dwivew pwobe woutine has to do sevewaw things:
 *   - dwive output discovewy via intew_dispway_dwivew_pwobe()
 *   - initiawize the memowy managew
 *   - awwocate initiaw config memowy
 *   - setup the DWM fwamebuffew with the awwocated memowy
 */
int i915_dwivew_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct dwm_i915_pwivate *i915;
	int wet;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		pw_eww("Faiwed to enabwe gwaphics device: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	i915 = i915_dwivew_cweate(pdev, ent);
	if (IS_EWW(i915)) {
		pci_disabwe_device(pdev);
		wetuwn PTW_EWW(i915);
	}

	wet = i915_dwivew_eawwy_pwobe(i915);
	if (wet < 0)
		goto out_pci_disabwe;

	disabwe_wpm_wakewef_assewts(&i915->wuntime_pm);

	intew_vgpu_detect(i915);

	wet = intew_gt_pwobe_aww(i915);
	if (wet < 0)
		goto out_wuntime_pm_put;

	wet = i915_dwivew_mmio_pwobe(i915);
	if (wet < 0)
		goto out_wuntime_pm_put;

	wet = i915_dwivew_hw_pwobe(i915);
	if (wet < 0)
		goto out_cweanup_mmio;

	wet = intew_dispway_dwivew_pwobe_noiwq(i915);
	if (wet < 0)
		goto out_cweanup_hw;

	wet = intew_iwq_instaww(i915);
	if (wet)
		goto out_cweanup_modeset;

	wet = intew_dispway_dwivew_pwobe_nogem(i915);
	if (wet)
		goto out_cweanup_iwq;

	wet = i915_gem_init(i915);
	if (wet)
		goto out_cweanup_modeset2;

	wet = intew_pxp_init(i915);
	if (wet != -ENODEV)
		dwm_dbg(&i915->dwm, "pxp init faiwed with %d\n", wet);

	wet = intew_dispway_dwivew_pwobe(i915);
	if (wet)
		goto out_cweanup_gem;

	i915_dwivew_wegistew(i915);

	enabwe_wpm_wakewef_assewts(&i915->wuntime_pm);

	i915_wewcome_messages(i915);

	i915->do_wewease = twue;

	wetuwn 0;

out_cweanup_gem:
	i915_gem_suspend(i915);
	i915_gem_dwivew_wemove(i915);
	i915_gem_dwivew_wewease(i915);
out_cweanup_modeset2:
	/* FIXME cwean up the ewwow path */
	intew_dispway_dwivew_wemove(i915);
	intew_iwq_uninstaww(i915);
	intew_dispway_dwivew_wemove_noiwq(i915);
	goto out_cweanup_modeset;
out_cweanup_iwq:
	intew_iwq_uninstaww(i915);
out_cweanup_modeset:
	intew_dispway_dwivew_wemove_nogem(i915);
out_cweanup_hw:
	i915_dwivew_hw_wemove(i915);
	intew_memowy_wegions_dwivew_wewease(i915);
	i915_ggtt_dwivew_wewease(i915);
	i915_gem_dwain_fweed_objects(i915);
	i915_ggtt_dwivew_wate_wewease(i915);
out_cweanup_mmio:
	i915_dwivew_mmio_wewease(i915);
out_wuntime_pm_put:
	enabwe_wpm_wakewef_assewts(&i915->wuntime_pm);
	i915_dwivew_wate_wewease(i915);
out_pci_disabwe:
	pci_disabwe_device(pdev);
	i915_pwobe_ewwow(i915, "Device initiawization faiwed (%d)\n", wet);
	wetuwn wet;
}

void i915_dwivew_wemove(stwuct dwm_i915_pwivate *i915)
{
	intew_wakewef_t wakewef;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	i915_dwivew_unwegistew(i915);

	/* Fwush any extewnaw code that stiww may be undew the WCU wock */
	synchwonize_wcu();

	i915_gem_suspend(i915);

	intew_gvt_dwivew_wemove(i915);

	intew_dispway_dwivew_wemove(i915);

	intew_iwq_uninstaww(i915);

	intew_dispway_dwivew_wemove_noiwq(i915);

	i915_weset_ewwow_state(i915);
	i915_gem_dwivew_wemove(i915);

	intew_dispway_dwivew_wemove_nogem(i915);

	i915_dwivew_hw_wemove(i915);

	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
}

static void i915_dwivew_wewease(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_wuntime_pm *wpm = &dev_pwiv->wuntime_pm;
	intew_wakewef_t wakewef;

	if (!dev_pwiv->do_wewease)
		wetuwn;

	wakewef = intew_wuntime_pm_get(wpm);

	i915_gem_dwivew_wewease(dev_pwiv);

	intew_memowy_wegions_dwivew_wewease(dev_pwiv);
	i915_ggtt_dwivew_wewease(dev_pwiv);
	i915_gem_dwain_fweed_objects(dev_pwiv);
	i915_ggtt_dwivew_wate_wewease(dev_pwiv);

	i915_dwivew_mmio_wewease(dev_pwiv);

	intew_wuntime_pm_put(wpm, wakewef);

	intew_wuntime_pm_dwivew_wewease(wpm);

	i915_dwivew_wate_wewease(dev_pwiv);

	intew_dispway_device_wemove(dev_pwiv);
}

static int i915_dwivew_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	int wet;

	wet = i915_gem_open(i915, fiwe);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/**
 * i915_dwivew_wastcwose - cwean up aftew aww DWM cwients have exited
 * @dev: DWM device
 *
 * Take cawe of cweaning up aftew aww DWM cwients have exited.  In the
 * mode setting case, we want to westowe the kewnew's initiaw mode (just
 * in case the wast cwient weft us in a bad state).
 *
 * Additionawwy, in the non-mode setting case, we'ww teaw down the GTT
 * and DMA stwuctuwes, since the kewnew won't be using them, and cwea
 * up any GEM state.
 */
static void i915_dwivew_wastcwose(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);

	intew_fbdev_westowe_mode(i915);

	vga_switchewoo_pwocess_dewayed_switch();
}

static void i915_dwivew_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;

	i915_gem_context_cwose(fiwe);
	i915_dwm_cwient_put(fiwe_pwiv->cwient);

	kfwee_wcu(fiwe_pwiv, wcu);

	/* Catch up with aww the defewwed fwees fwom "this" cwient */
	i915_gem_fwush_fwee_objects(to_i915(dev));
}

static void intew_suspend_encodews(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_encodew *encodew;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	/*
	 * TODO: check and wemove howding the modeset wocks if none of
	 * the encodews depends on this.
	 */
	dwm_modeset_wock_aww(&dev_pwiv->dwm);
	fow_each_intew_encodew(&dev_pwiv->dwm, encodew)
		if (encodew->suspend)
			encodew->suspend(encodew);
	dwm_modeset_unwock_aww(&dev_pwiv->dwm);

	fow_each_intew_encodew(&dev_pwiv->dwm, encodew)
		if (encodew->suspend_compwete)
			encodew->suspend_compwete(encodew);
}

static void intew_shutdown_encodews(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_encodew *encodew;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	/*
	 * TODO: check and wemove howding the modeset wocks if none of
	 * the encodews depends on this.
	 */
	dwm_modeset_wock_aww(&dev_pwiv->dwm);
	fow_each_intew_encodew(&dev_pwiv->dwm, encodew)
		if (encodew->shutdown)
			encodew->shutdown(encodew);
	dwm_modeset_unwock_aww(&dev_pwiv->dwm);

	fow_each_intew_encodew(&dev_pwiv->dwm, encodew)
		if (encodew->shutdown_compwete)
			encodew->shutdown_compwete(encodew);
}

void i915_dwivew_shutdown(stwuct dwm_i915_pwivate *i915)
{
	disabwe_wpm_wakewef_assewts(&i915->wuntime_pm);
	intew_wuntime_pm_disabwe(&i915->wuntime_pm);
	intew_powew_domains_disabwe(i915);

	if (HAS_DISPWAY(i915)) {
		dwm_kms_hewpew_poww_disabwe(&i915->dwm);

		dwm_atomic_hewpew_shutdown(&i915->dwm);
	}

	intew_dp_mst_suspend(i915);

	intew_wuntime_pm_disabwe_intewwupts(i915);
	intew_hpd_cancew_wowk(i915);

	intew_suspend_encodews(i915);
	intew_shutdown_encodews(i915);

	intew_dmc_suspend(i915);

	i915_gem_suspend(i915);

	/*
	 * The onwy wequiwement is to weboot with dispway DC states disabwed,
	 * fow now weaving aww dispway powew wewws in the INIT powew domain
	 * enabwed.
	 *
	 * TODO:
	 * - unify the pci_dwivew::shutdown sequence hewe with the
	 *   pci_dwivew.dwivew.pm.powewoff,powewoff_wate sequence.
	 * - unify the dwivew wemove and system/wuntime suspend sequences with
	 *   the above unified shutdown/powewoff sequence.
	 */
	intew_powew_domains_dwivew_wemove(i915);
	enabwe_wpm_wakewef_assewts(&i915->wuntime_pm);

	intew_wuntime_pm_dwivew_wast_wewease(&i915->wuntime_pm);
}

static boow suspend_to_idwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
#if IS_ENABWED(CONFIG_ACPI_SWEEP)
	if (acpi_tawget_system_state() < ACPI_STATE_S3)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static void i915_dwm_compwete(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);

	intew_pxp_wesume_compwete(i915->pxp);
}

static int i915_dwm_pwepawe(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);

	intew_pxp_suspend_pwepawe(i915->pxp);

	/*
	 * NB intew_dispway_dwivew_suspend() may issue new wequests aftew we've
	 * ostensibwy mawked the GPU as weady-to-sweep hewe. We need to
	 * spwit out that wowk and puww it fowwawd so that aftew point,
	 * the GPU is not woken again.
	 */
	wetuwn i915_gem_backup_suspend(i915);
}

static int i915_dwm_suspend(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	pci_powew_t opwegion_tawget_state;

	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	/* We do a wot of poking in a wot of wegistews, make suwe they wowk
	 * pwopewwy. */
	intew_powew_domains_disabwe(dev_pwiv);
	if (HAS_DISPWAY(dev_pwiv))
		dwm_kms_hewpew_poww_disabwe(dev);

	pci_save_state(pdev);

	intew_dispway_dwivew_suspend(dev_pwiv);

	intew_dp_mst_suspend(dev_pwiv);

	intew_wuntime_pm_disabwe_intewwupts(dev_pwiv);
	intew_hpd_cancew_wowk(dev_pwiv);

	intew_suspend_encodews(dev_pwiv);

	/* Must be cawwed befowe GGTT is suspended. */
	intew_dpt_suspend(dev_pwiv);
	i915_ggtt_suspend(to_gt(dev_pwiv)->ggtt);

	i915_save_dispway(dev_pwiv);

	opwegion_tawget_state = suspend_to_idwe(dev_pwiv) ? PCI_D1 : PCI_D3cowd;
	intew_opwegion_suspend(dev_pwiv, opwegion_tawget_state);

	intew_fbdev_set_suspend(dev, FBINFO_STATE_SUSPENDED, twue);

	dev_pwiv->suspend_count++;

	intew_dmc_suspend(dev_pwiv);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	i915_gem_dwain_fweed_objects(dev_pwiv);

	wetuwn 0;
}

static int i915_dwm_suspend_wate(stwuct dwm_device *dev, boow hibewnation)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	stwuct intew_wuntime_pm *wpm = &dev_pwiv->wuntime_pm;
	stwuct intew_gt *gt;
	int wet, i;
	boow s2idwe = !hibewnation && suspend_to_idwe(dev_pwiv);

	disabwe_wpm_wakewef_assewts(wpm);

	intew_pxp_suspend(dev_pwiv->pxp);

	i915_gem_suspend_wate(dev_pwiv);

	fow_each_gt(gt, dev_pwiv, i)
		intew_uncowe_suspend(gt->uncowe);

	intew_powew_domains_suspend(dev_pwiv, s2idwe);

	intew_dispway_powew_suspend_wate(dev_pwiv);

	wet = vwv_suspend_compwete(dev_pwiv);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm, "Suspend compwete faiwed: %d\n", wet);
		intew_powew_domains_wesume(dev_pwiv);

		goto out;
	}

	pci_disabwe_device(pdev);
	/*
	 * Duwing hibewnation on some pwatfowms the BIOS may twy to access
	 * the device even though it's awweady in D3 and hang the machine. So
	 * weave the device in D0 on those pwatfowms and hope the BIOS wiww
	 * powew down the device pwopewwy. The issue was seen on muwtipwe owd
	 * GENs with diffewent BIOS vendows, so having an expwicit bwackwist
	 * is inpwacticaw; appwy the wowkawound on evewything pwe GEN6. The
	 * pwatfowms whewe the issue was seen:
	 * Wenovo Thinkpad X301, X61s, X60, T60, X41
	 * Fujitsu FSC S7110
	 * Acew Aspiwe 1830T
	 */
	if (!(hibewnation && GWAPHICS_VEW(dev_pwiv) < 6))
		pci_set_powew_state(pdev, PCI_D3hot);

out:
	enabwe_wpm_wakewef_assewts(wpm);
	if (!dev_pwiv->uncowe.usew_fowcewake_count)
		intew_wuntime_pm_dwivew_wewease(wpm);

	wetuwn wet;
}

int i915_dwivew_suspend_switchewoo(stwuct dwm_i915_pwivate *i915,
				   pm_message_t state)
{
	int ewwow;

	if (dwm_WAWN_ON_ONCE(&i915->dwm, state.event != PM_EVENT_SUSPEND &&
			     state.event != PM_EVENT_FWEEZE))
		wetuwn -EINVAW;

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	ewwow = i915_dwm_suspend(&i915->dwm);
	if (ewwow)
		wetuwn ewwow;

	wetuwn i915_dwm_suspend_wate(&i915->dwm, fawse);
}

static int i915_dwm_wesume(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_gt *gt;
	int wet, i;

	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wet = i915_pcode_init(dev_pwiv);
	if (wet)
		wetuwn wet;

	sanitize_gpu(dev_pwiv);

	wet = i915_ggtt_enabwe_hw(dev_pwiv);
	if (wet)
		dwm_eww(&dev_pwiv->dwm, "faiwed to we-enabwe GGTT\n");

	i915_ggtt_wesume(to_gt(dev_pwiv)->ggtt);

	fow_each_gt(gt, dev_pwiv, i)
		if (GWAPHICS_VEW(gt->i915) >= 8)
			setup_pwivate_pat(gt);

	/* Must be cawwed aftew GGTT is wesumed. */
	intew_dpt_wesume(dev_pwiv);

	intew_dmc_wesume(dev_pwiv);

	i915_westowe_dispway(dev_pwiv);
	intew_pps_unwock_wegs_wa(dev_pwiv);

	intew_init_pch_wefcwk(dev_pwiv);

	/*
	 * Intewwupts have to be enabwed befowe any batches awe wun. If not the
	 * GPU wiww hang. i915_gem_init_hw() wiww initiate batches to
	 * update/westowe the context.
	 *
	 * dwm_mode_config_weset() needs AUX intewwupts.
	 *
	 * Modeset enabwing in intew_dispway_dwivew_init_hw() awso needs wowking
	 * intewwupts.
	 */
	intew_wuntime_pm_enabwe_intewwupts(dev_pwiv);

	if (HAS_DISPWAY(dev_pwiv))
		dwm_mode_config_weset(dev);

	i915_gem_wesume(dev_pwiv);

	intew_dispway_dwivew_init_hw(dev_pwiv);

	intew_cwock_gating_init(dev_pwiv);
	intew_hpd_init(dev_pwiv);

	/* MST sideband wequiwes HPD intewwupts enabwed */
	intew_dp_mst_wesume(dev_pwiv);
	intew_dispway_dwivew_wesume(dev_pwiv);

	intew_hpd_poww_disabwe(dev_pwiv);
	if (HAS_DISPWAY(dev_pwiv))
		dwm_kms_hewpew_poww_enabwe(dev);

	intew_opwegion_wesume(dev_pwiv);

	intew_fbdev_set_suspend(dev, FBINFO_STATE_WUNNING, fawse);

	intew_powew_domains_enabwe(dev_pwiv);

	intew_gvt_wesume(dev_pwiv);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wetuwn 0;
}

static int i915_dwm_wesume_eawwy(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	stwuct intew_gt *gt;
	int wet, i;

	/*
	 * We have a wesume owdewing issue with the snd-hda dwivew awso
	 * wequiwing ouw device to be powew up. Due to the wack of a
	 * pawent/chiwd wewationship we cuwwentwy sowve this with an eawwy
	 * wesume hook.
	 *
	 * FIXME: This shouwd be sowved with a speciaw hdmi sink device ow
	 * simiwaw so that powew domains can be empwoyed.
	 */

	/*
	 * Note that we need to set the powew state expwicitwy, since we
	 * powewed off the device duwing fweeze and the PCI cowe won't powew
	 * it back up fow us duwing thaw. Powewing off the device duwing
	 * fweeze is not a hawd wequiwement though, and duwing the
	 * suspend/wesume phases the PCI cowe makes suwe we get hewe with the
	 * device powewed on. So in case we change ouw fweeze wogic and keep
	 * the device powewed we can awso wemove the fowwowing set powew state
	 * caww.
	 */
	wet = pci_set_powew_state(pdev, PCI_D0);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"faiwed to set PCI D0 powew state (%d)\n", wet);
		wetuwn wet;
	}

	/*
	 * Note that pci_enabwe_device() fiwst enabwes any pawent bwidge
	 * device and onwy then sets the powew state fow this device. The
	 * bwidge enabwing is a nop though, since bwidge devices awe wesumed
	 * fiwst. The owdew of enabwing powew and enabwing the device is
	 * imposed by the PCI cowe as descwibed above, so hewe we pwesewve the
	 * same owdew fow the fweeze/thaw phases.
	 *
	 * TODO: eventuawwy we shouwd wemove pci_disabwe_device() /
	 * pci_enabwe_enabwe_device() fwom suspend/wesume. Due to how they
	 * depend on the device enabwe wefcount we can't anyway depend on them
	 * disabwing/enabwing the device.
	 */
	if (pci_enabwe_device(pdev))
		wetuwn -EIO;

	pci_set_mastew(pdev);

	disabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wet = vwv_wesume_pwepawe(dev_pwiv, fawse);
	if (wet)
		dwm_eww(&dev_pwiv->dwm,
			"Wesume pwepawe faiwed: %d, continuing anyway\n", wet);

	fow_each_gt(gt, dev_pwiv, i)
		intew_gt_wesume_eawwy(gt);

	intew_dispway_powew_wesume_eawwy(dev_pwiv);

	intew_powew_domains_wesume(dev_pwiv);

	enabwe_wpm_wakewef_assewts(&dev_pwiv->wuntime_pm);

	wetuwn wet;
}

int i915_dwivew_wesume_switchewoo(stwuct dwm_i915_pwivate *i915)
{
	int wet;

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	wet = i915_dwm_wesume_eawwy(&i915->dwm);
	if (wet)
		wetuwn wet;

	wetuwn i915_dwm_wesume(&i915->dwm);
}

static int i915_pm_pwepawe(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	if (!i915) {
		dev_eww(kdev, "DWM not initiawized, abowting suspend.\n");
		wetuwn -ENODEV;
	}

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	wetuwn i915_dwm_pwepawe(&i915->dwm);
}

static int i915_pm_suspend(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	if (!i915) {
		dev_eww(kdev, "DWM not initiawized, abowting suspend.\n");
		wetuwn -ENODEV;
	}

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	wetuwn i915_dwm_suspend(&i915->dwm);
}

static int i915_pm_suspend_wate(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	/*
	 * We have a suspend owdewing issue with the snd-hda dwivew awso
	 * wequiwing ouw device to be powew up. Due to the wack of a
	 * pawent/chiwd wewationship we cuwwentwy sowve this with an wate
	 * suspend hook.
	 *
	 * FIXME: This shouwd be sowved with a speciaw hdmi sink device ow
	 * simiwaw so that powew domains can be empwoyed.
	 */
	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	wetuwn i915_dwm_suspend_wate(&i915->dwm, fawse);
}

static int i915_pm_powewoff_wate(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	wetuwn i915_dwm_suspend_wate(&i915->dwm, twue);
}

static int i915_pm_wesume_eawwy(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	wetuwn i915_dwm_wesume_eawwy(&i915->dwm);
}

static int i915_pm_wesume(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn 0;

	wetuwn i915_dwm_wesume(&i915->dwm);
}

static void i915_pm_compwete(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);

	if (i915->dwm.switch_powew_state == DWM_SWITCH_POWEW_OFF)
		wetuwn;

	i915_dwm_compwete(&i915->dwm);
}

/* fweeze: befowe cweating the hibewnation_image */
static int i915_pm_fweeze(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);
	int wet;

	if (i915->dwm.switch_powew_state != DWM_SWITCH_POWEW_OFF) {
		wet = i915_dwm_suspend(&i915->dwm);
		if (wet)
			wetuwn wet;
	}

	wet = i915_gem_fweeze(i915);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int i915_pm_fweeze_wate(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(kdev);
	int wet;

	if (i915->dwm.switch_powew_state != DWM_SWITCH_POWEW_OFF) {
		wet = i915_dwm_suspend_wate(&i915->dwm, twue);
		if (wet)
			wetuwn wet;
	}

	wet = i915_gem_fweeze_wate(i915);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/* thaw: cawwed aftew cweating the hibewnation image, but befowe tuwning off. */
static int i915_pm_thaw_eawwy(stwuct device *kdev)
{
	wetuwn i915_pm_wesume_eawwy(kdev);
}

static int i915_pm_thaw(stwuct device *kdev)
{
	wetuwn i915_pm_wesume(kdev);
}

/* westowe: cawwed aftew woading the hibewnation image. */
static int i915_pm_westowe_eawwy(stwuct device *kdev)
{
	wetuwn i915_pm_wesume_eawwy(kdev);
}

static int i915_pm_westowe(stwuct device *kdev)
{
	wetuwn i915_pm_wesume(kdev);
}

static int intew_wuntime_suspend(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = kdev_to_i915(kdev);
	stwuct intew_wuntime_pm *wpm = &dev_pwiv->wuntime_pm;
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	stwuct pci_dev *woot_pdev;
	stwuct intew_gt *gt;
	int wet, i;

	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !HAS_WUNTIME_PM(dev_pwiv)))
		wetuwn -ENODEV;

	dwm_dbg(&dev_pwiv->dwm, "Suspending device\n");

	disabwe_wpm_wakewef_assewts(wpm);

	/*
	 * We awe safe hewe against we-fauwts, since the fauwt handwew takes
	 * an WPM wefewence.
	 */
	i915_gem_wuntime_suspend(dev_pwiv);

	intew_pxp_wuntime_suspend(dev_pwiv->pxp);

	fow_each_gt(gt, dev_pwiv, i)
		intew_gt_wuntime_suspend(gt);

	intew_wuntime_pm_disabwe_intewwupts(dev_pwiv);

	fow_each_gt(gt, dev_pwiv, i)
		intew_uncowe_suspend(gt->uncowe);

	intew_dispway_powew_suspend(dev_pwiv);

	wet = vwv_suspend_compwete(dev_pwiv);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"Wuntime suspend faiwed, disabwing it (%d)\n", wet);
		intew_uncowe_wuntime_wesume(&dev_pwiv->uncowe);

		intew_wuntime_pm_enabwe_intewwupts(dev_pwiv);

		fow_each_gt(gt, dev_pwiv, i)
			intew_gt_wuntime_wesume(gt);

		enabwe_wpm_wakewef_assewts(wpm);

		wetuwn wet;
	}

	enabwe_wpm_wakewef_assewts(wpm);
	intew_wuntime_pm_dwivew_wewease(wpm);

	if (intew_uncowe_awm_uncwaimed_mmio_detection(&dev_pwiv->uncowe))
		dwm_eww(&dev_pwiv->dwm,
			"Uncwaimed access detected pwiow to suspending\n");

	/*
	 * FIXME: Tempowawy hammew to avoid fweezing the machine on ouw DGFX
	 * This shouwd be totawwy wemoved when we handwe the pci states pwopewwy
	 * on wuntime PM.
	 */
	woot_pdev = pcie_find_woot_powt(pdev);
	if (woot_pdev)
		pci_d3cowd_disabwe(woot_pdev);

	/*
	 * FIXME: We weawwy shouwd find a document that wefewences the awguments
	 * used bewow!
	 */
	if (IS_BWOADWEWW(dev_pwiv)) {
		/*
		 * On Bwoadweww, if we use PCI_D1 the PCH DDI powts wiww stop
		 * being detected, and the caww we do at intew_wuntime_wesume()
		 * won't be abwe to westowe them. Since PCI_D3hot matches the
		 * actuaw specification and appeaws to be wowking, use it.
		 */
		intew_opwegion_notify_adaptew(dev_pwiv, PCI_D3hot);
	} ewse {
		/*
		 * cuwwent vewsions of fiwmwawe which depend on this opwegion
		 * notification have wepuwposed the D1 definition to mean
		 * "wuntime suspended" vs. what you wouwd nowmawwy expect (D3)
		 * to distinguish it fwom notifications that might be sent via
		 * the suspend path.
		 */
		intew_opwegion_notify_adaptew(dev_pwiv, PCI_D1);
	}

	assewt_fowcewakes_inactive(&dev_pwiv->uncowe);

	if (!IS_VAWWEYVIEW(dev_pwiv) && !IS_CHEWWYVIEW(dev_pwiv))
		intew_hpd_poww_enabwe(dev_pwiv);

	dwm_dbg(&dev_pwiv->dwm, "Device suspended\n");
	wetuwn 0;
}

static int intew_wuntime_wesume(stwuct device *kdev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = kdev_to_i915(kdev);
	stwuct intew_wuntime_pm *wpm = &dev_pwiv->wuntime_pm;
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	stwuct pci_dev *woot_pdev;
	stwuct intew_gt *gt;
	int wet, i;

	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, !HAS_WUNTIME_PM(dev_pwiv)))
		wetuwn -ENODEV;

	dwm_dbg(&dev_pwiv->dwm, "Wesuming device\n");

	dwm_WAWN_ON_ONCE(&dev_pwiv->dwm, atomic_wead(&wpm->wakewef_count));
	disabwe_wpm_wakewef_assewts(wpm);

	intew_opwegion_notify_adaptew(dev_pwiv, PCI_D0);

	woot_pdev = pcie_find_woot_powt(pdev);
	if (woot_pdev)
		pci_d3cowd_enabwe(woot_pdev);

	if (intew_uncowe_uncwaimed_mmio(&dev_pwiv->uncowe))
		dwm_dbg(&dev_pwiv->dwm,
			"Uncwaimed access duwing suspend, bios?\n");

	intew_dispway_powew_wesume(dev_pwiv);

	wet = vwv_wesume_pwepawe(dev_pwiv, twue);

	fow_each_gt(gt, dev_pwiv, i)
		intew_uncowe_wuntime_wesume(gt->uncowe);

	intew_wuntime_pm_enabwe_intewwupts(dev_pwiv);

	/*
	 * No point of wowwing back things in case of an ewwow, as the best
	 * we can do is to hope that things wiww stiww wowk (and disabwe WPM).
	 */
	fow_each_gt(gt, dev_pwiv, i)
		intew_gt_wuntime_wesume(gt);

	intew_pxp_wuntime_wesume(dev_pwiv->pxp);

	/*
	 * On VWV/CHV dispway intewwupts awe pawt of the dispway
	 * powew weww, so hpd is weinitiawized fwom thewe. Fow
	 * evewyone ewse do it hewe.
	 */
	if (!IS_VAWWEYVIEW(dev_pwiv) && !IS_CHEWWYVIEW(dev_pwiv)) {
		intew_hpd_init(dev_pwiv);
		intew_hpd_poww_disabwe(dev_pwiv);
	}

	skw_watewmawk_ipc_update(dev_pwiv);

	enabwe_wpm_wakewef_assewts(wpm);

	if (wet)
		dwm_eww(&dev_pwiv->dwm,
			"Wuntime wesume faiwed, disabwing it (%d)\n", wet);
	ewse
		dwm_dbg(&dev_pwiv->dwm, "Device wesumed\n");

	wetuwn wet;
}

const stwuct dev_pm_ops i915_pm_ops = {
	/*
	 * S0ix (via system suspend) and S3 event handwews [PMSG_SUSPEND,
	 * PMSG_WESUME]
	 */
	.pwepawe = i915_pm_pwepawe,
	.suspend = i915_pm_suspend,
	.suspend_wate = i915_pm_suspend_wate,
	.wesume_eawwy = i915_pm_wesume_eawwy,
	.wesume = i915_pm_wesume,
	.compwete = i915_pm_compwete,

	/*
	 * S4 event handwews
	 * @fweeze, @fweeze_wate    : cawwed (1) befowe cweating the
	 *                            hibewnation image [PMSG_FWEEZE] and
	 *                            (2) aftew webooting, befowe westowing
	 *                            the image [PMSG_QUIESCE]
	 * @thaw, @thaw_eawwy       : cawwed (1) aftew cweating the hibewnation
	 *                            image, befowe wwiting it [PMSG_THAW]
	 *                            and (2) aftew faiwing to cweate ow
	 *                            westowe the image [PMSG_WECOVEW]
	 * @powewoff, @powewoff_wate: cawwed aftew wwiting the hibewnation
	 *                            image, befowe webooting [PMSG_HIBEWNATE]
	 * @westowe, @westowe_eawwy : cawwed aftew webooting and westowing the
	 *                            hibewnation image [PMSG_WESTOWE]
	 */
	.fweeze = i915_pm_fweeze,
	.fweeze_wate = i915_pm_fweeze_wate,
	.thaw_eawwy = i915_pm_thaw_eawwy,
	.thaw = i915_pm_thaw,
	.powewoff = i915_pm_suspend,
	.powewoff_wate = i915_pm_powewoff_wate,
	.westowe_eawwy = i915_pm_westowe_eawwy,
	.westowe = i915_pm_westowe,

	/* S0ix (via wuntime suspend) event handwews */
	.wuntime_suspend = intew_wuntime_suspend,
	.wuntime_wesume = intew_wuntime_wesume,
};

static const stwuct fiwe_opewations i915_dwivew_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_open,
	.wewease = dwm_wewease_nogwobaw,
	.unwocked_ioctw = dwm_ioctw,
	.mmap = i915_gem_mmap,
	.poww = dwm_poww,
	.wead = dwm_wead,
	.compat_ioctw = i915_ioc32_compat_ioctw,
	.wwseek = noop_wwseek,
#ifdef CONFIG_PWOC_FS
	.show_fdinfo = dwm_show_fdinfo,
#endif
};

static int
i915_gem_weject_pin_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe)
{
	wetuwn -ENODEV;
}

static const stwuct dwm_ioctw_desc i915_ioctws[] = {
	DWM_IOCTW_DEF_DWV(I915_INIT, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_FWUSH, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_FWIP, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_BATCHBUFFEW, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_IWQ_EMIT, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_IWQ_WAIT, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_GETPAWAM, i915_getpawam_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_SETPAWAM, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_AWWOC, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_FWEE, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_INIT_HEAP, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_CMDBUFFEW, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_DESTWOY_HEAP,  dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_SET_VBWANK_PIPE,  dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_GET_VBWANK_PIPE,  dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_VBWANK_SWAP, dwm_noop, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_HWS_ADDW, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_GEM_INIT, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_GEM_EXECBUFFEW, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(I915_GEM_EXECBUFFEW2_WW, i915_gem_execbuffew2_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_PIN, i915_gem_weject_pin_ioctw, DWM_AUTH|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_GEM_UNPIN, i915_gem_weject_pin_ioctw, DWM_AUTH|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_GEM_BUSY, i915_gem_busy_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_SET_CACHING, i915_gem_set_caching_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_GET_CACHING, i915_gem_get_caching_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_THWOTTWE, i915_gem_thwottwe_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_ENTEWVT, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_GEM_WEAVEVT, dwm_noop, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(I915_GEM_CWEATE, i915_gem_cweate_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_CWEATE_EXT, i915_gem_cweate_ext_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_PWEAD, i915_gem_pwead_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_PWWITE, i915_gem_pwwite_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_MMAP, i915_gem_mmap_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_MMAP_OFFSET, i915_gem_mmap_offset_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_SET_DOMAIN, i915_gem_set_domain_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_SW_FINISH, i915_gem_sw_finish_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_SET_TIWING, i915_gem_set_tiwing_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_GET_TIWING, i915_gem_get_tiwing_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_GET_APEWTUWE, i915_gem_get_apewtuwe_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GET_PIPE_FWOM_CWTC_ID, intew_get_pipe_fwom_cwtc_id_ioctw, 0),
	DWM_IOCTW_DEF_DWV(I915_GEM_MADVISE, i915_gem_madvise_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_OVEWWAY_PUT_IMAGE, intew_ovewway_put_image_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF_DWV(I915_OVEWWAY_ATTWS, intew_ovewway_attws_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF_DWV(I915_SET_SPWITE_COWOWKEY, intew_spwite_set_cowowkey_ioctw, DWM_MASTEW),
	DWM_IOCTW_DEF_DWV(I915_GET_SPWITE_COWOWKEY, dwm_noop, DWM_MASTEW),
	DWM_IOCTW_DEF_DWV(I915_GEM_WAIT, i915_gem_wait_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_CONTEXT_CWEATE_EXT, i915_gem_context_cweate_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_CONTEXT_DESTWOY, i915_gem_context_destwoy_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_WEG_WEAD, i915_weg_wead_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GET_WESET_STATS, i915_gem_context_weset_stats_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_USEWPTW, i915_gem_usewptw_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_CONTEXT_GETPAWAM, i915_gem_context_getpawam_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_CONTEXT_SETPAWAM, i915_gem_context_setpawam_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_PEWF_OPEN, i915_pewf_open_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_PEWF_ADD_CONFIG, i915_pewf_add_config_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_PEWF_WEMOVE_CONFIG, i915_pewf_wemove_config_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_QUEWY, i915_quewy_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_VM_CWEATE, i915_gem_vm_cweate_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(I915_GEM_VM_DESTWOY, i915_gem_vm_destwoy_ioctw, DWM_WENDEW_AWWOW),
};

/*
 * Intewface histowy:
 *
 * 1.1: Owiginaw.
 * 1.2: Add Powew Management
 * 1.3: Add vbwank suppowt
 * 1.4: Fix cmdbuffew path, add heap destwoy
 * 1.5: Add vbwank pipe configuwation
 * 1.6: - New ioctw fow scheduwing buffew swaps on vewticaw bwank
 *      - Suppowt vewticaw bwank on secondawy dispway pipe
 */
#define DWIVEW_MAJOW		1
#define DWIVEW_MINOW		6
#define DWIVEW_PATCHWEVEW	0

static const stwuct dwm_dwivew i915_dwm_dwivew = {
	/* Don't use MTWWs hewe; the Xsewvew ow usewspace app shouwd
	 * deaw with them fow Intew hawdwawe.
	 */
	.dwivew_featuwes =
	    DWIVEW_GEM |
	    DWIVEW_WENDEW | DWIVEW_MODESET | DWIVEW_ATOMIC | DWIVEW_SYNCOBJ |
	    DWIVEW_SYNCOBJ_TIMEWINE,
	.wewease = i915_dwivew_wewease,
	.open = i915_dwivew_open,
	.wastcwose = i915_dwivew_wastcwose,
	.postcwose = i915_dwivew_postcwose,
	.show_fdinfo = PTW_IF(IS_ENABWED(CONFIG_PWOC_FS), i915_dwm_cwient_fdinfo),

	.gem_pwime_impowt = i915_gem_pwime_impowt,

	.dumb_cweate = i915_gem_dumb_cweate,
	.dumb_map_offset = i915_gem_dumb_mmap_offset,

	.ioctws = i915_ioctws,
	.num_ioctws = AWWAY_SIZE(i915_ioctws),
	.fops = &i915_dwivew_fops,
	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};
