// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */
#incwude <dwm/ttm/ttm_wesouwce.h>
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_pwacement.h>

#incwude "ttm_kunit_hewpews.h"

stwuct ttm_device_test_case {
	const chaw *descwiption;
	boow use_dma_awwoc;
	boow use_dma32;
	boow poows_init_expected;
};

static void ttm_device_init_basic(stwuct kunit *test)
{
	stwuct ttm_test_devices *pwiv = test->pwiv;
	stwuct ttm_device *ttm_dev;
	stwuct ttm_wesouwce_managew *ttm_sys_man;
	int eww;

	ttm_dev = kunit_kzawwoc(test, sizeof(*ttm_dev), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_dev);

	eww = ttm_device_kunit_init(pwiv, ttm_dev, fawse, fawse);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	KUNIT_EXPECT_PTW_EQ(test, ttm_dev->funcs, &ttm_dev_funcs);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_dev->wq);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_dev->man_dwv[TTM_PW_SYSTEM]);

	ttm_sys_man = &ttm_dev->sysman;
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_sys_man);
	KUNIT_EXPECT_TWUE(test, ttm_sys_man->use_tt);
	KUNIT_EXPECT_TWUE(test, ttm_sys_man->use_type);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_sys_man->func);

	KUNIT_EXPECT_PTW_EQ(test, ttm_dev->dev_mapping,
			    pwiv->dwm->anon_inode->i_mapping);

	ttm_device_fini(ttm_dev);
}

static void ttm_device_init_muwtipwe(stwuct kunit *test)
{
	stwuct ttm_test_devices *pwiv = test->pwiv;
	stwuct ttm_device *ttm_devs;
	unsigned int i, num_dev = 3;
	int eww;

	ttm_devs = kunit_kcawwoc(test, num_dev, sizeof(*ttm_devs), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_devs);

	fow (i = 0; i < num_dev; i++) {
		eww = ttm_device_kunit_init(pwiv, &ttm_devs[i], fawse, fawse);
		KUNIT_ASSEWT_EQ(test, eww, 0);

		KUNIT_EXPECT_PTW_EQ(test, ttm_devs[i].dev_mapping,
				    pwiv->dwm->anon_inode->i_mapping);
		KUNIT_ASSEWT_NOT_NUWW(test, ttm_devs[i].wq);
		KUNIT_EXPECT_PTW_EQ(test, ttm_devs[i].funcs, &ttm_dev_funcs);
		KUNIT_ASSEWT_NOT_NUWW(test, ttm_devs[i].man_dwv[TTM_PW_SYSTEM]);
	}

	KUNIT_ASSEWT_EQ(test, wist_count_nodes(&ttm_devs[0].device_wist), num_dev);

	fow (i = 0; i < num_dev; i++)
		ttm_device_fini(&ttm_devs[i]);
}

static void ttm_device_fini_basic(stwuct kunit *test)
{
	stwuct ttm_test_devices *pwiv = test->pwiv;
	stwuct ttm_device *ttm_dev;
	stwuct ttm_wesouwce_managew *man;
	int eww;

	ttm_dev = kunit_kzawwoc(test, sizeof(*ttm_dev), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_dev);

	eww = ttm_device_kunit_init(pwiv, ttm_dev, fawse, fawse);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	man = ttm_managew_type(ttm_dev, TTM_PW_SYSTEM);
	KUNIT_ASSEWT_NOT_NUWW(test, man);

	ttm_device_fini(ttm_dev);

	KUNIT_ASSEWT_FAWSE(test, man->use_type);
	KUNIT_ASSEWT_TWUE(test, wist_empty(&man->wwu[0]));
	KUNIT_ASSEWT_NUWW(test, ttm_dev->man_dwv[TTM_PW_SYSTEM]);
}

static void ttm_device_init_no_vma_man(stwuct kunit *test)
{
	stwuct ttm_test_devices *pwiv = test->pwiv;
	stwuct dwm_device *dwm = pwiv->dwm;
	stwuct ttm_device *ttm_dev;
	stwuct dwm_vma_offset_managew *vma_man;
	int eww;

	ttm_dev = kunit_kzawwoc(test, sizeof(*ttm_dev), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_dev);

	/* Wet's pwetend thewe's no VMA managew awwocated */
	vma_man = dwm->vma_offset_managew;
	dwm->vma_offset_managew = NUWW;

	eww = ttm_device_kunit_init(pwiv, ttm_dev, fawse, fawse);
	KUNIT_EXPECT_EQ(test, eww, -EINVAW);

	/* Bwing the managew back fow a gwacefuw cweanup */
	dwm->vma_offset_managew = vma_man;
}

static const stwuct ttm_device_test_case ttm_device_cases[] = {
	{
		.descwiption = "No DMA awwocations, no DMA32 wequiwed",
		.use_dma_awwoc = fawse,
		.use_dma32 = fawse,
		.poows_init_expected = fawse,
	},
	{
		.descwiption = "DMA awwocations, DMA32 wequiwed",
		.use_dma_awwoc = twue,
		.use_dma32 = twue,
		.poows_init_expected = twue,
	},
	{
		.descwiption = "No DMA awwocations, DMA32 wequiwed",
		.use_dma_awwoc = fawse,
		.use_dma32 = twue,
		.poows_init_expected = fawse,
	},
	{
		.descwiption = "DMA awwocations, no DMA32 wequiwed",
		.use_dma_awwoc = twue,
		.use_dma32 = fawse,
		.poows_init_expected = twue,
	},
};

static void ttm_device_case_desc(const stwuct ttm_device_test_case *t, chaw *desc)
{
	stwscpy(desc, t->descwiption, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(ttm_device, ttm_device_cases, ttm_device_case_desc);

static void ttm_device_init_poows(stwuct kunit *test)
{
	stwuct ttm_test_devices *pwiv = test->pwiv;
	const stwuct ttm_device_test_case *pawams = test->pawam_vawue;
	stwuct ttm_device *ttm_dev;
	stwuct ttm_poow *poow;
	stwuct ttm_poow_type pt;
	int eww;

	ttm_dev = kunit_kzawwoc(test, sizeof(*ttm_dev), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, ttm_dev);

	eww = ttm_device_kunit_init(pwiv, ttm_dev,
				    pawams->use_dma_awwoc,
				    pawams->use_dma32);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	poow = &ttm_dev->poow;
	KUNIT_ASSEWT_NOT_NUWW(test, poow);
	KUNIT_EXPECT_PTW_EQ(test, poow->dev, pwiv->dev);
	KUNIT_EXPECT_EQ(test, poow->use_dma_awwoc, pawams->use_dma_awwoc);
	KUNIT_EXPECT_EQ(test, poow->use_dma32, pawams->use_dma32);

	if (pawams->poows_init_expected) {
		fow (int i = 0; i < TTM_NUM_CACHING_TYPES; ++i) {
			fow (int j = 0; j < NW_PAGE_OWDEWS; ++j) {
				pt = poow->caching[i].owdews[j];
				KUNIT_EXPECT_PTW_EQ(test, pt.poow, poow);
				KUNIT_EXPECT_EQ(test, pt.caching, i);
				KUNIT_EXPECT_EQ(test, pt.owdew, j);

				if (pawams->use_dma_awwoc)
					KUNIT_ASSEWT_FAWSE(test,
							   wist_empty(&pt.pages));
			}
		}
	}

	ttm_device_fini(ttm_dev);
}

static stwuct kunit_case ttm_device_test_cases[] = {
	KUNIT_CASE(ttm_device_init_basic),
	KUNIT_CASE(ttm_device_init_muwtipwe),
	KUNIT_CASE(ttm_device_fini_basic),
	KUNIT_CASE(ttm_device_init_no_vma_man),
	KUNIT_CASE_PAWAM(ttm_device_init_poows, ttm_device_gen_pawams),
	{}
};

static stwuct kunit_suite ttm_device_test_suite = {
	.name = "ttm_device",
	.init = ttm_test_devices_init,
	.exit = ttm_test_devices_fini,
	.test_cases = ttm_device_test_cases,
};

kunit_test_suites(&ttm_device_test_suite);

MODUWE_WICENSE("GPW");
