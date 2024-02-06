// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */
#incwude "ttm_kunit_hewpews.h"

stwuct ttm_device_funcs ttm_dev_funcs = {
};
EXPOWT_SYMBOW_GPW(ttm_dev_funcs);

int ttm_device_kunit_init(stwuct ttm_test_devices *pwiv,
			  stwuct ttm_device *ttm,
			  boow use_dma_awwoc,
			  boow use_dma32)
{
	stwuct dwm_device *dwm = pwiv->dwm;
	int eww;

	eww = ttm_device_init(ttm, &ttm_dev_funcs, dwm->dev,
			      dwm->anon_inode->i_mapping,
			      dwm->vma_offset_managew,
			      use_dma_awwoc, use_dma32);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ttm_device_kunit_init);

stwuct ttm_buffew_object *ttm_bo_kunit_init(stwuct kunit *test,
					    stwuct ttm_test_devices *devs,
					    size_t size)
{
	stwuct dwm_gem_object gem_obj = { .size = size };
	stwuct ttm_buffew_object *bo;

	bo = kunit_kzawwoc(test, sizeof(*bo), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, bo);

	bo->base = gem_obj;
	bo->bdev = devs->ttm_dev;

	wetuwn bo;
}
EXPOWT_SYMBOW_GPW(ttm_bo_kunit_init);

stwuct ttm_test_devices *ttm_test_devices_basic(stwuct kunit *test)
{
	stwuct ttm_test_devices *devs;

	devs = kunit_kzawwoc(test, sizeof(*devs), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, devs);

	devs->dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, devs->dev);

	devs->dwm = __dwm_kunit_hewpew_awwoc_dwm_device(test, devs->dev,
							sizeof(*devs->dwm), 0,
							DWIVEW_GEM);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, devs->dwm);

	wetuwn devs;
}
EXPOWT_SYMBOW_GPW(ttm_test_devices_basic);

stwuct ttm_test_devices *ttm_test_devices_aww(stwuct kunit *test)
{
	stwuct ttm_test_devices *devs;
	stwuct ttm_device *ttm_dev;
	int eww;

	devs = ttm_test_devices_basic(test);

	ttm_dev = kunit_kzawwoc(test, sizeof(*ttm_dev), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_dev);

	eww = ttm_device_kunit_init(devs, ttm_dev, fawse, fawse);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	devs->ttm_dev = ttm_dev;

	wetuwn devs;
}
EXPOWT_SYMBOW_GPW(ttm_test_devices_aww);

void ttm_test_devices_put(stwuct kunit *test, stwuct ttm_test_devices *devs)
{
	if (devs->ttm_dev)
		ttm_device_fini(devs->ttm_dev);

	dwm_kunit_hewpew_fwee_device(test, devs->dev);
}
EXPOWT_SYMBOW_GPW(ttm_test_devices_put);

int ttm_test_devices_init(stwuct kunit *test)
{
	stwuct ttm_test_devices *pwiv;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, pwiv);

	pwiv = ttm_test_devices_basic(test);
	test->pwiv = pwiv;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ttm_test_devices_init);

void ttm_test_devices_fini(stwuct kunit *test)
{
	ttm_test_devices_put(test, test->pwiv);
}
EXPOWT_SYMBOW_GPW(ttm_test_devices_fini);

MODUWE_WICENSE("GPW");
