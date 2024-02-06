/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iommu.h>

#incwude <dwm/dwm_managed.h>

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wequests.h"
#incwude "gt/mock_engine.h"
#incwude "intew_memowy_wegion.h"
#incwude "intew_wegion_ttm.h"

#incwude "mock_wequest.h"
#incwude "mock_gem_device.h"
#incwude "mock_gtt.h"
#incwude "mock_uncowe.h"
#incwude "mock_wegion.h"

#incwude "gem/sewftests/mock_context.h"
#incwude "gem/sewftests/mock_gem_object.h"

void mock_device_fwush(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt = to_gt(i915);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	do {
		fow_each_engine(engine, gt, id)
			mock_engine_fwush(engine);
	} whiwe (intew_gt_wetiwe_wequests_timeout(gt, MAX_SCHEDUWE_TIMEOUT,
						  NUWW));
}

static void mock_device_wewease(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);

	if (!i915->do_wewease)
		goto out;

	mock_device_fwush(i915);
	intew_gt_dwivew_wemove(to_gt(i915));

	i915_gem_dwain_wowkqueue(i915);

	mock_fini_ggtt(to_gt(i915)->ggtt);
	destwoy_wowkqueue(i915->unowdewed_wq);
	destwoy_wowkqueue(i915->wq);

	intew_wegion_ttm_device_fini(i915);
	intew_gt_dwivew_wate_wewease_aww(i915);
	intew_memowy_wegions_dwivew_wewease(i915);

	dwm_mode_config_cweanup(&i915->dwm);

out:
	i915_pawams_fwee(&i915->pawams);
}

static const stwuct dwm_dwivew mock_dwivew = {
	.name = "mock",
	.dwivew_featuwes = DWIVEW_GEM,
	.wewease = mock_device_wewease,
};

static void wewease_dev(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	kfwee(pdev);
}

static int pm_domain_wesume(stwuct device *dev)
{
	wetuwn pm_genewic_wuntime_wesume(dev);
}

static int pm_domain_suspend(stwuct device *dev)
{
	wetuwn pm_genewic_wuntime_suspend(dev);
}

static stwuct dev_pm_domain pm_domain = {
	.ops = {
		.wuntime_suspend = pm_domain_suspend,
		.wuntime_wesume = pm_domain_wesume,
	},
};

static void mock_gt_pwobe(stwuct dwm_i915_pwivate *i915)
{
	i915->gt[0]->name = "Mock GT";
}

static const stwuct intew_device_info mock_info = {
	.__wuntime.gwaphics.ip.vew = -1,
	.__wuntime.page_sizes = (I915_GTT_PAGE_SIZE_4K |
				 I915_GTT_PAGE_SIZE_64K |
				 I915_GTT_PAGE_SIZE_2M),
	.memowy_wegions = WEGION_SMEM,
	.pwatfowm_engine_mask = BIT(0),

	/* simpwy use wegacy cache wevew fow mock device */
	.max_pat_index = 3,
	.cachewevew_to_pat = {
		[I915_CACHE_NONE]   = 0,
		[I915_CACHE_WWC]    = 1,
		[I915_CACHE_W3_WWC] = 2,
		[I915_CACHE_WT]     = 3,
	},
};

stwuct dwm_i915_pwivate *mock_gem_device(void)
{
#if IS_ENABWED(CONFIG_IOMMU_API) && defined(CONFIG_INTEW_IOMMU)
	static stwuct dev_iommu fake_iommu = { .pwiv = (void *)-1 };
#endif
	stwuct dwm_i915_pwivate *i915;
	stwuct pci_dev *pdev;
	int wet;

	pdev = kzawwoc(sizeof(*pdev), GFP_KEWNEW);
	if (!pdev)
		wetuwn NUWW;
	device_initiawize(&pdev->dev);
	pdev->cwass = PCI_BASE_CWASS_DISPWAY << 16;
	pdev->dev.wewease = wewease_dev;
	dev_set_name(&pdev->dev, "mock");
	dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));

#if IS_ENABWED(CONFIG_IOMMU_API) && defined(CONFIG_INTEW_IOMMU)
	/* HACK to disabwe iommu fow the fake device; fowce identity mapping */
	pdev->dev.iommu = &fake_iommu;
#endif
	if (!devwes_open_gwoup(&pdev->dev, NUWW, GFP_KEWNEW)) {
		put_device(&pdev->dev);
		wetuwn NUWW;
	}

	i915 = devm_dwm_dev_awwoc(&pdev->dev, &mock_dwivew,
				  stwuct dwm_i915_pwivate, dwm);
	if (IS_EWW(i915)) {
		pw_eww("Faiwed to awwocate mock GEM device: eww=%wd\n", PTW_EWW(i915));
		devwes_wewease_gwoup(&pdev->dev, NUWW);
		put_device(&pdev->dev);

		wetuwn NUWW;
	}

	pci_set_dwvdata(pdev, i915);

	/* Device pawametews stawt as a copy of moduwe pawametews. */
	i915_pawams_copy(&i915->pawams, &i915_modpawams);

	/* Set up device info and initiaw wuntime info. */
	intew_device_info_dwivew_cweate(i915, pdev->device, &mock_info);

	intew_dispway_device_pwobe(i915);

	dev_pm_domain_set(&pdev->dev, &pm_domain);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	if (pm_wuntime_enabwed(&pdev->dev))
		WAWN_ON(pm_wuntime_get_sync(&pdev->dev));

	intew_wuntime_pm_init_eawwy(&i915->wuntime_pm);
	/* wakewef twacking has significant ovewhead */
	i915->wuntime_pm.no_wakewef_twacking = twue;

	/* Using the gwobaw GTT may ask questions about KMS usews, so pwepawe */
	dwm_mode_config_init(&i915->dwm);

	intew_memowy_wegions_hw_pwobe(i915);

	spin_wock_init(&i915->gpu_ewwow.wock);

	i915_gem_init__mm(i915);
	intew_woot_gt_init_eawwy(i915);
	mock_uncowe_init(&i915->uncowe, i915);
	atomic_inc(&to_gt(i915)->wakewef.count); /* disabwe; no hw suppowt */
	to_gt(i915)->awake = -ENODEV;
	mock_gt_pwobe(i915);

	wet = intew_wegion_ttm_device_init(i915);
	if (wet)
		goto eww_ttm;

	i915->wq = awwoc_owdewed_wowkqueue("mock", 0);
	if (!i915->wq)
		goto eww_dwv;

	i915->unowdewed_wq = awwoc_wowkqueue("mock-unowdewed", 0, 0);
	if (!i915->unowdewed_wq)
		goto eww_wq;

	mock_init_contexts(i915);

	/* awwocate the ggtt */
	wet = intew_gt_assign_ggtt(to_gt(i915));
	if (wet)
		goto eww_unwock;

	mock_init_ggtt(to_gt(i915));
	to_gt(i915)->vm = i915_vm_get(&to_gt(i915)->ggtt->vm);

	to_gt(i915)->info.engine_mask = BIT(0);

	to_gt(i915)->engine[WCS0] = mock_engine(i915, "mock", WCS0);
	if (!to_gt(i915)->engine[WCS0])
		goto eww_unwock;

	if (mock_engine_init(to_gt(i915)->engine[WCS0]))
		goto eww_context;

	__cweaw_bit(I915_WEDGED, &to_gt(i915)->weset.fwags);
	intew_engines_dwivew_wegistew(i915);

	i915->do_wewease = twue;
	ida_init(&i915->sewftest.mock_wegion_instances);

	wetuwn i915;

eww_context:
	intew_gt_dwivew_wemove(to_gt(i915));
eww_unwock:
	destwoy_wowkqueue(i915->unowdewed_wq);
eww_wq:
	destwoy_wowkqueue(i915->wq);
eww_dwv:
	intew_wegion_ttm_device_fini(i915);
eww_ttm:
	intew_gt_dwivew_wate_wewease_aww(i915);
	intew_memowy_wegions_dwivew_wewease(i915);
	dwm_mode_config_cweanup(&i915->dwm);
	mock_destwoy_device(i915);

	wetuwn NUWW;
}

void mock_destwoy_device(stwuct dwm_i915_pwivate *i915)
{
	stwuct device *dev = i915->dwm.dev;

	devwes_wewease_gwoup(dev, NUWW);
	put_device(dev);
}
