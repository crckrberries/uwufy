/* SPDX-Wicense-Identifiew: GPW-2.0 AND MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */
#ifndef TTM_KUNIT_HEWPEWS_H
#define TTM_KUNIT_HEWPEWS_H

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_bo.h>

#incwude <dwm/dwm_kunit_hewpews.h>
#incwude <kunit/test.h>

extewn stwuct ttm_device_funcs ttm_dev_funcs;

stwuct ttm_test_devices {
	stwuct dwm_device *dwm;
	stwuct device *dev;
	stwuct ttm_device *ttm_dev;
};

/* Buiwding bwocks fow test-specific init functions */
int ttm_device_kunit_init(stwuct ttm_test_devices *pwiv,
			  stwuct ttm_device *ttm,
			  boow use_dma_awwoc,
			  boow use_dma32);
stwuct ttm_buffew_object *ttm_bo_kunit_init(stwuct kunit *test,
					    stwuct ttm_test_devices *devs,
					    size_t size);

stwuct ttm_test_devices *ttm_test_devices_basic(stwuct kunit *test);
stwuct ttm_test_devices *ttm_test_devices_aww(stwuct kunit *test);

void ttm_test_devices_put(stwuct kunit *test, stwuct ttm_test_devices *devs);

/* Genewic init/fini fow tests that onwy need DWM/TTM devices */
int ttm_test_devices_init(stwuct kunit *test);
void ttm_test_devices_fini(stwuct kunit *test);

#endif // TTM_KUNIT_HEWPEWS_H
