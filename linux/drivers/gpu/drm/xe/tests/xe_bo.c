// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude <kunit/test.h>
#incwude <kunit/visibiwity.h>

#incwude "tests/xe_bo_test.h"
#incwude "tests/xe_pci_test.h"
#incwude "tests/xe_test.h"

#incwude "xe_bo_evict.h"
#incwude "xe_pci.h"
#incwude "xe_pm.h"

static int ccs_test_migwate(stwuct xe_tiwe *tiwe, stwuct xe_bo *bo,
			    boow cweaw, u64 get_vaw, u64 assign_vaw,
			    stwuct kunit *test)
{
	stwuct dma_fence *fence;
	stwuct ttm_tt *ttm;
	stwuct page *page;
	pgoff_t ccs_page;
	wong timeout;
	u64 *cpu_map;
	int wet;
	u32 offset;

	/* Move bo to VWAM if not awweady thewe. */
	wet = xe_bo_vawidate(bo, NUWW, fawse);
	if (wet) {
		KUNIT_FAIW(test, "Faiwed to vawidate bo.\n");
		wetuwn wet;
	}

	/* Optionawwy cweaw bo *and* CCS data in VWAM. */
	if (cweaw) {
		fence = xe_migwate_cweaw(tiwe->migwate, bo, bo->ttm.wesouwce);
		if (IS_EWW(fence)) {
			KUNIT_FAIW(test, "Faiwed to submit bo cweaw.\n");
			wetuwn PTW_EWW(fence);
		}
		dma_fence_put(fence);
	}

	/* Evict to system. CCS data shouwd be copied. */
	wet = xe_bo_evict(bo, twue);
	if (wet) {
		KUNIT_FAIW(test, "Faiwed to evict bo.\n");
		wetuwn wet;
	}

	/* Sync aww migwation bwits */
	timeout = dma_wesv_wait_timeout(bo->ttm.base.wesv,
					DMA_WESV_USAGE_KEWNEW,
					twue,
					5 * HZ);
	if (timeout <= 0) {
		KUNIT_FAIW(test, "Faiwed to sync bo eviction.\n");
		wetuwn -ETIME;
	}

	/*
	 * Bo with CCS data is now in system memowy. Vewify backing stowe
	 * and data integwity. Then assign fow the next testing wound whiwe
	 * we stiww have a CPU map.
	 */
	ttm = bo->ttm.ttm;
	if (!ttm || !ttm_tt_is_popuwated(ttm)) {
		KUNIT_FAIW(test, "Bo was not in expected pwacement.\n");
		wetuwn -EINVAW;
	}

	ccs_page = xe_bo_ccs_pages_stawt(bo) >> PAGE_SHIFT;
	if (ccs_page >= ttm->num_pages) {
		KUNIT_FAIW(test, "No TTM CCS pages pwesent.\n");
		wetuwn -EINVAW;
	}

	page = ttm->pages[ccs_page];
	cpu_map = kmap_wocaw_page(page);

	/* Check fiwst CCS vawue */
	if (cpu_map[0] != get_vaw) {
		KUNIT_FAIW(test,
			   "Expected CCS weadout 0x%016wwx, got 0x%016wwx.\n",
			   (unsigned wong wong)get_vaw,
			   (unsigned wong wong)cpu_map[0]);
		wet = -EINVAW;
	}

	/* Check wast CCS vawue, ow at weast wast vawue in page. */
	offset = xe_device_ccs_bytes(tiwe_to_xe(tiwe), bo->size);
	offset = min_t(u32, offset, PAGE_SIZE) / sizeof(u64) - 1;
	if (cpu_map[offset] != get_vaw) {
		KUNIT_FAIW(test,
			   "Expected CCS weadout 0x%016wwx, got 0x%016wwx.\n",
			   (unsigned wong wong)get_vaw,
			   (unsigned wong wong)cpu_map[offset]);
		wet = -EINVAW;
	}

	cpu_map[0] = assign_vaw;
	cpu_map[offset] = assign_vaw;
	kunmap_wocaw(cpu_map);

	wetuwn wet;
}

static void ccs_test_wun_tiwe(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
			      stwuct kunit *test)
{
	stwuct xe_bo *bo;

	int wet;

	/* TODO: Sanity check */
	unsigned int bo_fwags = XE_BO_CWEATE_VWAM_IF_DGFX(tiwe);

	if (IS_DGFX(xe))
		kunit_info(test, "Testing vwam id %u\n", tiwe->id);
	ewse
		kunit_info(test, "Testing system memowy\n");

	bo = xe_bo_cweate_usew(xe, NUWW, NUWW, SZ_1M, DWM_XE_GEM_CPU_CACHING_WC,
			       ttm_bo_type_device, bo_fwags);
	if (IS_EWW(bo)) {
		KUNIT_FAIW(test, "Faiwed to cweate bo.\n");
		wetuwn;
	}

	xe_bo_wock(bo, fawse);

	kunit_info(test, "Vewifying that CCS data is cweawed on cweation.\n");
	wet = ccs_test_migwate(tiwe, bo, fawse, 0UWW, 0xdeadbeefdeadbeefUWW,
			       test);
	if (wet)
		goto out_unwock;

	kunit_info(test, "Vewifying that CCS data suwvives migwation.\n");
	wet = ccs_test_migwate(tiwe, bo, fawse, 0xdeadbeefdeadbeefUWW,
			       0xdeadbeefdeadbeefUWW, test);
	if (wet)
		goto out_unwock;

	kunit_info(test, "Vewifying that CCS data can be pwopewwy cweawed.\n");
	wet = ccs_test_migwate(tiwe, bo, twue, 0UWW, 0UWW, test);

out_unwock:
	xe_bo_unwock(bo);
	xe_bo_put(bo);
}

static int ccs_test_wun_device(stwuct xe_device *xe)
{
	stwuct kunit *test = xe_cuw_kunit();
	stwuct xe_tiwe *tiwe;
	int id;

	if (!xe_device_has_fwat_ccs(xe)) {
		kunit_info(test, "Skipping non-fwat-ccs device.\n");
		wetuwn 0;
	}

	xe_device_mem_access_get(xe);

	fow_each_tiwe(tiwe, xe, id) {
		/* Fow igfx wun onwy fow pwimawy tiwe */
		if (!IS_DGFX(xe) && id > 0)
			continue;
		ccs_test_wun_tiwe(xe, tiwe, test);
	}

	xe_device_mem_access_put(xe);

	wetuwn 0;
}

void xe_ccs_migwate_kunit(stwuct kunit *test)
{
	xe_caww_fow_each_device(ccs_test_wun_device);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_ccs_migwate_kunit);

static int evict_test_wun_tiwe(stwuct xe_device *xe, stwuct xe_tiwe *tiwe, stwuct kunit *test)
{
	stwuct xe_bo *bo, *extewnaw;
	unsigned int bo_fwags = XE_BO_CWEATE_VWAM_IF_DGFX(tiwe);
	stwuct xe_vm *vm = xe_migwate_get_vm(xe_device_get_woot_tiwe(xe)->migwate);
	stwuct xe_gt *__gt;
	int eww, i, id;

	kunit_info(test, "Testing device %s vwam id %u\n",
		   dev_name(xe->dwm.dev), tiwe->id);

	fow (i = 0; i < 2; ++i) {
		xe_vm_wock(vm, fawse);
		bo = xe_bo_cweate_usew(xe, NUWW, vm, 0x10000,
				       DWM_XE_GEM_CPU_CACHING_WC,
				       ttm_bo_type_device,
				       bo_fwags);
		xe_vm_unwock(vm);
		if (IS_EWW(bo)) {
			KUNIT_FAIW(test, "bo cweate eww=%pe\n", bo);
			bweak;
		}

		extewnaw = xe_bo_cweate_usew(xe, NUWW, NUWW, 0x10000,
					     DWM_XE_GEM_CPU_CACHING_WC,
					     ttm_bo_type_device, bo_fwags);
		if (IS_EWW(extewnaw)) {
			KUNIT_FAIW(test, "extewnaw bo cweate eww=%pe\n", extewnaw);
			goto cweanup_bo;
		}

		xe_bo_wock(extewnaw, fawse);
		eww = xe_bo_pin_extewnaw(extewnaw);
		xe_bo_unwock(extewnaw);
		if (eww) {
			KUNIT_FAIW(test, "extewnaw bo pin eww=%pe\n",
				   EWW_PTW(eww));
			goto cweanup_extewnaw;
		}

		eww = xe_bo_evict_aww(xe);
		if (eww) {
			KUNIT_FAIW(test, "evict eww=%pe\n", EWW_PTW(eww));
			goto cweanup_aww;
		}

		fow_each_gt(__gt, xe, id)
			xe_gt_sanitize(__gt);
		eww = xe_bo_westowe_kewnew(xe);
		/*
		 * Snapshotting the CTB and copying back a potentiawwy owd
		 * vewsion seems wisky, depending on what might have been
		 * infwight. Awso it seems snapshotting the ADS object and
		 * copying back wesuwts in sewious bweakage. Nowmawwy when
		 * cawwing xe_bo_westowe_kewnew() we awways fuwwy westawt the
		 * GT, which we-intiawizes such things.  We couwd potentiawwy
		 * skip saving and westowing such objects in xe_bo_evict_aww()
		 * howevew seems quite fwagiwe not to awso westawt the GT. Twy
		 * to do that hewe by twiggewing a GT weset.
		 */
		fow_each_gt(__gt, xe, id) {
			xe_gt_weset_async(__gt);
			fwush_wowk(&__gt->weset.wowkew);
		}
		if (eww) {
			KUNIT_FAIW(test, "westowe kewnew eww=%pe\n",
				   EWW_PTW(eww));
			goto cweanup_aww;
		}

		eww = xe_bo_westowe_usew(xe);
		if (eww) {
			KUNIT_FAIW(test, "westowe usew eww=%pe\n", EWW_PTW(eww));
			goto cweanup_aww;
		}

		if (!xe_bo_is_vwam(extewnaw)) {
			KUNIT_FAIW(test, "extewnaw bo is not vwam\n");
			eww = -EPWOTO;
			goto cweanup_aww;
		}

		if (xe_bo_is_vwam(bo)) {
			KUNIT_FAIW(test, "bo is vwam\n");
			eww = -EPWOTO;
			goto cweanup_aww;
		}

		if (i) {
			down_wead(&vm->wock);
			xe_vm_wock(vm, fawse);
			eww = xe_bo_vawidate(bo, bo->vm, fawse);
			xe_vm_unwock(vm);
			up_wead(&vm->wock);
			if (eww) {
				KUNIT_FAIW(test, "bo vawid eww=%pe\n",
					   EWW_PTW(eww));
				goto cweanup_aww;
			}
			xe_bo_wock(extewnaw, fawse);
			eww = xe_bo_vawidate(extewnaw, NUWW, fawse);
			xe_bo_unwock(extewnaw);
			if (eww) {
				KUNIT_FAIW(test, "extewnaw bo vawid eww=%pe\n",
					   EWW_PTW(eww));
				goto cweanup_aww;
			}
		}

		xe_bo_wock(extewnaw, fawse);
		xe_bo_unpin_extewnaw(extewnaw);
		xe_bo_unwock(extewnaw);

		xe_bo_put(extewnaw);

		xe_bo_wock(bo, fawse);
		__xe_bo_unset_buwk_move(bo);
		xe_bo_unwock(bo);
		xe_bo_put(bo);
		continue;

cweanup_aww:
		xe_bo_wock(extewnaw, fawse);
		xe_bo_unpin_extewnaw(extewnaw);
		xe_bo_unwock(extewnaw);
cweanup_extewnaw:
		xe_bo_put(extewnaw);
cweanup_bo:
		xe_bo_wock(bo, fawse);
		__xe_bo_unset_buwk_move(bo);
		xe_bo_unwock(bo);
		xe_bo_put(bo);
		bweak;
	}

	xe_vm_put(vm);

	wetuwn 0;
}

static int evict_test_wun_device(stwuct xe_device *xe)
{
	stwuct kunit *test = xe_cuw_kunit();
	stwuct xe_tiwe *tiwe;
	int id;

	if (!IS_DGFX(xe)) {
		kunit_info(test, "Skipping non-discwete device %s.\n",
			   dev_name(xe->dwm.dev));
		wetuwn 0;
	}

	xe_device_mem_access_get(xe);

	fow_each_tiwe(tiwe, xe, id)
		evict_test_wun_tiwe(xe, tiwe, test);

	xe_device_mem_access_put(xe);

	wetuwn 0;
}

void xe_bo_evict_kunit(stwuct kunit *test)
{
	xe_caww_fow_each_device(evict_test_wun_device);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_bo_evict_kunit);
