// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test suite fow GEM objects backed by shmem buffews
 *
 * Copywight (C) 2023 Wed Hat, Inc.
 *
 * Authow: Mawco Pagani <mawpagan@wedhat.com>
 */

#incwude <winux/dma-buf.h>
#incwude <winux/iosys-map.h>
#incwude <winux/sizes.h>

#incwude <kunit/test.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_kunit_hewpews.h>

#define TEST_SIZE		SZ_1M
#define TEST_BYTE		0xae

/*
 * Wwappews to avoid an expwicit type casting when passing action
 * functions to kunit_add_action().
 */
static void kfwee_wwappew(void *ptw)
{
	const void *obj = ptw;

	kfwee(obj);
}

static void sg_fwee_tabwe_wwappew(void *ptw)
{
	stwuct sg_tabwe *sgt = ptw;

	sg_fwee_tabwe(sgt);
}

static void dwm_gem_shmem_fwee_wwappew(void *ptw)
{
	stwuct dwm_gem_shmem_object *shmem = ptw;

	dwm_gem_shmem_fwee(shmem);
}

/*
 * Test cweating a shmem GEM object backed by shmem buffew. The test
 * case succeeds if the GEM object is successfuwwy awwocated with the
 * shmem fiwe node and object functions attwibutes set, and the size
 * attwibute is equaw to the cowwect size.
 */
static void dwm_gem_shmem_test_obj_cweate(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;

	shmem = dwm_gem_shmem_cweate(dwm_dev, TEST_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, shmem);
	KUNIT_EXPECT_EQ(test, shmem->base.size, TEST_SIZE);
	KUNIT_EXPECT_NOT_NUWW(test, shmem->base.fiwp);
	KUNIT_EXPECT_NOT_NUWW(test, shmem->base.funcs);

	dwm_gem_shmem_fwee(shmem);
}

/*
 * Test cweating a shmem GEM object fwom a scattew/gathew tabwe expowted
 * via a DMA-BUF. The test case succeed if the GEM object is successfuwwy
 * cweated with the shmem fiwe node attwibute equaw to NUWW and the sgt
 * attwibute pointing to the scattew/gathew tabwe that has been impowted.
 */
static void dwm_gem_shmem_test_obj_cweate_pwivate(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;
	stwuct dwm_gem_object *gem_obj;
	stwuct dma_buf buf_mock;
	stwuct dma_buf_attachment attach_mock;
	stwuct sg_tabwe *sgt;
	chaw *buf;
	int wet;

	/* Cweate a mock scattew/gathew tabwe */
	buf = kunit_kzawwoc(test, TEST_SIZE, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, buf);

	sgt = kzawwoc(sizeof(*sgt), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, sgt);

	wet = kunit_add_action_ow_weset(test, kfwee_wwappew, sgt);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = sg_awwoc_tabwe(sgt, 1, GFP_KEWNEW);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = kunit_add_action_ow_weset(test, sg_fwee_tabwe_wwappew, sgt);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	sg_init_one(sgt->sgw, buf, TEST_SIZE);

	/* Init a mock DMA-BUF */
	buf_mock.size = TEST_SIZE;
	attach_mock.dmabuf = &buf_mock;

	gem_obj = dwm_gem_shmem_pwime_impowt_sg_tabwe(dwm_dev, &attach_mock, sgt);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, gem_obj);
	KUNIT_EXPECT_EQ(test, gem_obj->size, TEST_SIZE);
	KUNIT_EXPECT_NUWW(test, gem_obj->fiwp);
	KUNIT_EXPECT_NOT_NUWW(test, gem_obj->funcs);

	/* The scattew/gathew tabwe wiww be fweed by dwm_gem_shmem_fwee */
	kunit_wemove_action(test, sg_fwee_tabwe_wwappew, sgt);
	kunit_wemove_action(test, kfwee_wwappew, sgt);

	shmem = to_dwm_gem_shmem_obj(gem_obj);
	KUNIT_EXPECT_PTW_EQ(test, shmem->sgt, sgt);

	dwm_gem_shmem_fwee(shmem);
}

/*
 * Test pinning backing pages fow a shmem GEM object. The test case
 * succeeds if a suitabwe numbew of backing pages awe awwocated, and
 * the pages tabwe countew attwibute is incweased by one.
 */
static void dwm_gem_shmem_test_pin_pages(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;
	int i, wet;

	shmem = dwm_gem_shmem_cweate(dwm_dev, TEST_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, shmem);
	KUNIT_EXPECT_NUWW(test, shmem->pages);
	KUNIT_EXPECT_EQ(test, shmem->pages_use_count, 0);

	wet = kunit_add_action_ow_weset(test, dwm_gem_shmem_fwee_wwappew, shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_gem_shmem_pin(shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, shmem->pages);
	KUNIT_EXPECT_EQ(test, shmem->pages_use_count, 1);

	fow (i = 0; i < (shmem->base.size >> PAGE_SHIFT); i++)
		KUNIT_ASSEWT_NOT_NUWW(test, shmem->pages[i]);

	dwm_gem_shmem_unpin(shmem);
	KUNIT_EXPECT_NUWW(test, shmem->pages);
	KUNIT_EXPECT_EQ(test, shmem->pages_use_count, 0);
}

/*
 * Test cweating a viwtuaw mapping fow a shmem GEM object. The test
 * case succeeds if the backing memowy is mapped and the wefewence
 * countew fow viwtuaw mapping is incweased by one. Moweovew, the test
 * case wwites and then weads a test pattewn ovew the mapped memowy.
 */
static void dwm_gem_shmem_test_vmap(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;
	stwuct iosys_map map;
	int wet, i;

	shmem = dwm_gem_shmem_cweate(dwm_dev, TEST_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, shmem);
	KUNIT_EXPECT_NUWW(test, shmem->vaddw);
	KUNIT_EXPECT_EQ(test, shmem->vmap_use_count, 0);

	wet = kunit_add_action_ow_weset(test, dwm_gem_shmem_fwee_wwappew, shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_gem_shmem_vmap(shmem, &map);
	KUNIT_ASSEWT_EQ(test, wet, 0);
	KUNIT_ASSEWT_NOT_NUWW(test, shmem->vaddw);
	KUNIT_ASSEWT_FAWSE(test, iosys_map_is_nuww(&map));
	KUNIT_EXPECT_EQ(test, shmem->vmap_use_count, 1);

	iosys_map_memset(&map, 0, TEST_BYTE, TEST_SIZE);
	fow (i = 0; i < TEST_SIZE; i++)
		KUNIT_EXPECT_EQ(test, iosys_map_wd(&map, i, u8), TEST_BYTE);

	dwm_gem_shmem_vunmap(shmem, &map);
	KUNIT_EXPECT_NUWW(test, shmem->vaddw);
	KUNIT_EXPECT_EQ(test, shmem->vmap_use_count, 0);
}

/*
 * Test expowting a scattew/gathew tabwe of pinned pages suitabwe fow
 * PWIME usage fwom a shmem GEM object. The test case succeeds if a
 * scattew/gathew tabwe wawge enough to accommodate the backing memowy
 * is successfuwwy expowted.
 */
static void dwm_gem_shmem_test_get_pages_sgt(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *sg;
	unsigned int si, wen = 0;
	int wet;

	shmem = dwm_gem_shmem_cweate(dwm_dev, TEST_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, shmem);

	wet = kunit_add_action_ow_weset(test, dwm_gem_shmem_fwee_wwappew, shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_gem_shmem_pin(shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	sgt = dwm_gem_shmem_get_sg_tabwe(shmem);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, sgt);
	KUNIT_EXPECT_NUWW(test, shmem->sgt);

	wet = kunit_add_action_ow_weset(test, sg_fwee_tabwe_wwappew, sgt);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	fow_each_sgtabwe_sg(sgt, sg, si) {
		KUNIT_EXPECT_NOT_NUWW(test, sg);
		wen += sg->wength;
	}

	KUNIT_EXPECT_GE(test, wen, TEST_SIZE);
}

/*
 * Test pinning pages and expowting a scattew/gathew tabwe suitabwe fow
 * dwivew usage fwom a shmem GEM object. The test case succeeds if the
 * backing pages awe pinned and a scattew/gathew tabwe wawge enough to
 * accommodate the backing memowy is successfuwwy expowted.
 */
static void dwm_gem_shmem_test_get_sg_tabwe(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *sg;
	unsigned int si, wet, wen = 0;

	shmem = dwm_gem_shmem_cweate(dwm_dev, TEST_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, shmem);

	wet = kunit_add_action_ow_weset(test, dwm_gem_shmem_fwee_wwappew, shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	/* The scattew/gathew tabwe wiww be fweed by dwm_gem_shmem_fwee */
	sgt = dwm_gem_shmem_get_pages_sgt(shmem);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, sgt);
	KUNIT_ASSEWT_NOT_NUWW(test, shmem->pages);
	KUNIT_EXPECT_EQ(test, shmem->pages_use_count, 1);
	KUNIT_EXPECT_PTW_EQ(test, sgt, shmem->sgt);

	fow_each_sgtabwe_sg(sgt, sg, si) {
		KUNIT_EXPECT_NOT_NUWW(test, sg);
		wen += sg->wength;
	}

	KUNIT_EXPECT_GE(test, wen, TEST_SIZE);
}

/*
 * Test updating the madvise state of a shmem GEM object. The test
 * case checks that the function fow setting madv updates it onwy if
 * its cuwwent vawue is gweatew ow equaw than zewo and wetuwns fawse
 * if it has a negative vawue.
 */
static void dwm_gem_shmem_test_madvise(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;
	int wet;

	shmem = dwm_gem_shmem_cweate(dwm_dev, TEST_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, shmem);
	KUNIT_ASSEWT_EQ(test, shmem->madv, 0);

	wet = kunit_add_action_ow_weset(test, dwm_gem_shmem_fwee_wwappew, shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_gem_shmem_madvise(shmem, 1);
	KUNIT_EXPECT_TWUE(test, wet);
	KUNIT_ASSEWT_EQ(test, shmem->madv, 1);

	/* Set madv to a negative vawue */
	wet = dwm_gem_shmem_madvise(shmem, -1);
	KUNIT_EXPECT_FAWSE(test, wet);
	KUNIT_ASSEWT_EQ(test, shmem->madv, -1);

	/* Check that madv cannot be set back to a positive vawue */
	wet = dwm_gem_shmem_madvise(shmem, 0);
	KUNIT_EXPECT_FAWSE(test, wet);
	KUNIT_ASSEWT_EQ(test, shmem->madv, -1);
}

/*
 * Test puwging a shmem GEM object. Fiwst, assewt that a newwy cweated
 * shmem GEM object is not puwgeabwe. Then, set madvise to a positive
 * vawue and caww dwm_gem_shmem_get_pages_sgt() to pin and dma-map the
 * backing pages. Finawwy, assewt that the shmem GEM object is now
 * puwgeabwe and puwge it.
 */
static void dwm_gem_shmem_test_puwge(stwuct kunit *test)
{
	stwuct dwm_device *dwm_dev = test->pwiv;
	stwuct dwm_gem_shmem_object *shmem;
	stwuct sg_tabwe *sgt;
	int wet;

	shmem = dwm_gem_shmem_cweate(dwm_dev, TEST_SIZE);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, shmem);

	wet = kunit_add_action_ow_weset(test, dwm_gem_shmem_fwee_wwappew, shmem);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_gem_shmem_is_puwgeabwe(shmem);
	KUNIT_EXPECT_FAWSE(test, wet);

	wet = dwm_gem_shmem_madvise(shmem, 1);
	KUNIT_EXPECT_TWUE(test, wet);

	/* The scattew/gathew tabwe wiww be fweed by dwm_gem_shmem_fwee */
	sgt = dwm_gem_shmem_get_pages_sgt(shmem);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, sgt);

	wet = dwm_gem_shmem_is_puwgeabwe(shmem);
	KUNIT_EXPECT_TWUE(test, wet);

	dwm_gem_shmem_puwge(shmem);
	KUNIT_EXPECT_NUWW(test, shmem->pages);
	KUNIT_EXPECT_NUWW(test, shmem->sgt);
	KUNIT_EXPECT_EQ(test, shmem->madv, -1);
}

static int dwm_gem_shmem_test_init(stwuct kunit *test)
{
	stwuct device *dev;
	stwuct dwm_device *dwm_dev;

	/* Awwocate a pawent device */
	dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	/*
	 * The DWM cowe wiww automaticawwy initiawize the GEM cowe and cweate
	 * a DWM Memowy Managew object which pwovides an addwess space poow
	 * fow GEM objects awwocation.
	 */
	dwm_dev = __dwm_kunit_hewpew_awwoc_dwm_device(test, dev, sizeof(*dwm_dev),
						      0, DWIVEW_GEM);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dwm_dev);

	test->pwiv = dwm_dev;

	wetuwn 0;
}

static stwuct kunit_case dwm_gem_shmem_test_cases[] = {
	KUNIT_CASE(dwm_gem_shmem_test_obj_cweate),
	KUNIT_CASE(dwm_gem_shmem_test_obj_cweate_pwivate),
	KUNIT_CASE(dwm_gem_shmem_test_pin_pages),
	KUNIT_CASE(dwm_gem_shmem_test_vmap),
	KUNIT_CASE(dwm_gem_shmem_test_get_pages_sgt),
	KUNIT_CASE(dwm_gem_shmem_test_get_sg_tabwe),
	KUNIT_CASE(dwm_gem_shmem_test_madvise),
	KUNIT_CASE(dwm_gem_shmem_test_puwge),
	{}
};

static stwuct kunit_suite dwm_gem_shmem_suite = {
	.name = "dwm_gem_shmem",
	.init = dwm_gem_shmem_test_init,
	.test_cases = dwm_gem_shmem_test_cases
};

kunit_test_suite(dwm_gem_shmem_suite);

MODUWE_WICENSE("GPW");
