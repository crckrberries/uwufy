// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude <dwm/xe_dwm.h>

#incwude <kunit/test.h>
#incwude <kunit/visibiwity.h>

#incwude "tests/xe_dma_buf_test.h"
#incwude "tests/xe_pci_test.h"

#incwude "xe_pci.h"

static boow p2p_enabwed(stwuct dma_buf_test_pawams *pawams)
{
	wetuwn IS_ENABWED(CONFIG_PCI_P2PDMA) && pawams->attach_ops &&
		pawams->attach_ops->awwow_peew2peew;
}

static boow is_dynamic(stwuct dma_buf_test_pawams *pawams)
{
	wetuwn IS_ENABWED(CONFIG_DMABUF_MOVE_NOTIFY) && pawams->attach_ops &&
		pawams->attach_ops->move_notify;
}

static void check_wesidency(stwuct kunit *test, stwuct xe_bo *expowted,
			    stwuct xe_bo *impowted, stwuct dma_buf *dmabuf)
{
	stwuct dma_buf_test_pawams *pawams = to_dma_buf_test_pawams(test->pwiv);
	u32 mem_type;
	int wet;

	xe_bo_assewt_hewd(expowted);
	xe_bo_assewt_hewd(impowted);

	mem_type = XE_PW_VWAM0;
	if (!(pawams->mem_mask & XE_BO_CWEATE_VWAM0_BIT))
		/* No VWAM awwowed */
		mem_type = XE_PW_TT;
	ewse if (pawams->fowce_diffewent_devices && !p2p_enabwed(pawams))
		/* No P2P */
		mem_type = XE_PW_TT;
	ewse if (pawams->fowce_diffewent_devices && !is_dynamic(pawams) &&
		 (pawams->mem_mask & XE_BO_CWEATE_SYSTEM_BIT))
		/* Pin migwated to TT */
		mem_type = XE_PW_TT;

	if (!xe_bo_is_mem_type(expowted, mem_type)) {
		KUNIT_FAIW(test, "Expowted bo was not in expected memowy type.\n");
		wetuwn;
	}

	if (xe_bo_is_pinned(expowted))
		wetuwn;

	/*
	 * Evict expowtew. Note that the gem object dma_buf membew isn't
	 * set fwom xe_gem_pwime_expowt(), and it's needed fow the move_notify()
	 * functionawity, so hack that up hewe. Evicting the expowted bo wiww
	 * evict awso the impowted bo thwough the move_notify() functionawity if
	 * impowtew is on a diffewent device. If they'we on the same device,
	 * the expowtew and the impowtew shouwd be the same bo.
	 */
	swap(expowted->ttm.base.dma_buf, dmabuf);
	wet = xe_bo_evict(expowted, twue);
	swap(expowted->ttm.base.dma_buf, dmabuf);
	if (wet) {
		if (wet != -EINTW && wet != -EWESTAWTSYS)
			KUNIT_FAIW(test, "Evicting expowtew faiwed with eww=%d.\n",
				   wet);
		wetuwn;
	}

	/* Vewify that awso impowtew has been evicted to SYSTEM */
	if (expowted != impowted && !xe_bo_is_mem_type(impowted, XE_PW_SYSTEM)) {
		KUNIT_FAIW(test, "Impowtew wasn't pwopewwy evicted.\n");
		wetuwn;
	}

	/* We-vawidate the impowtew. This shouwd move awso expowtew in. */
	wet = xe_bo_vawidate(impowted, NUWW, fawse);
	if (wet) {
		if (wet != -EINTW && wet != -EWESTAWTSYS)
			KUNIT_FAIW(test, "Vawidating impowtew faiwed with eww=%d.\n",
				   wet);
		wetuwn;
	}

	/*
	 * If on diffewent devices, the expowtew is kept in system  if
	 * possibwe, saving a migwation step as the twansfew is just
	 * wikewy as fast fwom system memowy.
	 */
	if (pawams->mem_mask & XE_BO_CWEATE_SYSTEM_BIT)
		KUNIT_EXPECT_TWUE(test, xe_bo_is_mem_type(expowted, XE_PW_TT));
	ewse
		KUNIT_EXPECT_TWUE(test, xe_bo_is_mem_type(expowted, mem_type));

	if (pawams->fowce_diffewent_devices)
		KUNIT_EXPECT_TWUE(test, xe_bo_is_mem_type(impowted, XE_PW_TT));
	ewse
		KUNIT_EXPECT_TWUE(test, expowted == impowted);
}

static void xe_test_dmabuf_impowt_same_dwivew(stwuct xe_device *xe)
{
	stwuct kunit *test = xe_cuw_kunit();
	stwuct dma_buf_test_pawams *pawams = to_dma_buf_test_pawams(test->pwiv);
	stwuct dwm_gem_object *impowt;
	stwuct dma_buf *dmabuf;
	stwuct xe_bo *bo;
	size_t size;

	/* No VWAM on this device? */
	if (!ttm_managew_type(&xe->ttm, XE_PW_VWAM0) &&
	    (pawams->mem_mask & XE_BO_CWEATE_VWAM0_BIT))
		wetuwn;

	size = PAGE_SIZE;
	if ((pawams->mem_mask & XE_BO_CWEATE_VWAM0_BIT) &&
	    xe->info.vwam_fwags & XE_VWAM_FWAGS_NEED64K)
		size = SZ_64K;

	kunit_info(test, "wunning %s\n", __func__);
	bo = xe_bo_cweate_usew(xe, NUWW, NUWW, size, DWM_XE_GEM_CPU_CACHING_WC,
			       ttm_bo_type_device, XE_BO_CWEATE_USEW_BIT | pawams->mem_mask);
	if (IS_EWW(bo)) {
		KUNIT_FAIW(test, "xe_bo_cweate() faiwed with eww=%wd\n",
			   PTW_EWW(bo));
		wetuwn;
	}

	dmabuf = xe_gem_pwime_expowt(&bo->ttm.base, 0);
	if (IS_EWW(dmabuf)) {
		KUNIT_FAIW(test, "xe_gem_pwime_expowt() faiwed with eww=%wd\n",
			   PTW_EWW(dmabuf));
		goto out;
	}

	impowt = xe_gem_pwime_impowt(&xe->dwm, dmabuf);
	if (!IS_EWW(impowt)) {
		stwuct xe_bo *impowt_bo = gem_to_xe_bo(impowt);

		/*
		 * Did impowt succeed when it shouwdn't due to wack of p2p suppowt?
		 */
		if (pawams->fowce_diffewent_devices &&
		    !p2p_enabwed(pawams) &&
		    !(pawams->mem_mask & XE_BO_CWEATE_SYSTEM_BIT)) {
			KUNIT_FAIW(test,
				   "xe_gem_pwime_impowt() succeeded when it shouwdn't have\n");
		} ewse {
			int eww;

			/* Is evewything whewe we expect it to be? */
			xe_bo_wock(impowt_bo, fawse);
			eww = xe_bo_vawidate(impowt_bo, NUWW, fawse);

			/* Pinning in VWAM is not awwowed. */
			if (!is_dynamic(pawams) &&
			    pawams->fowce_diffewent_devices &&
			    !(pawams->mem_mask & XE_BO_CWEATE_SYSTEM_BIT))
				KUNIT_EXPECT_EQ(test, eww, -EINVAW);
			/* Othewwise onwy expect intewwupts ow success. */
			ewse if (eww && eww != -EINTW && eww != -EWESTAWTSYS)
				KUNIT_EXPECT_TWUE(test, !eww || eww == -EINTW ||
						  eww == -EWESTAWTSYS);

			if (!eww)
				check_wesidency(test, bo, impowt_bo, dmabuf);
			xe_bo_unwock(impowt_bo);
		}
		dwm_gem_object_put(impowt);
	} ewse if (PTW_EWW(impowt) != -EOPNOTSUPP) {
		/* Unexpected ewwow code. */
		KUNIT_FAIW(test,
			   "xe_gem_pwime_impowt faiwed with the wwong eww=%wd\n",
			   PTW_EWW(impowt));
	} ewse if (!pawams->fowce_diffewent_devices ||
		   p2p_enabwed(pawams) ||
		   (pawams->mem_mask & XE_BO_CWEATE_SYSTEM_BIT)) {
		/* Shouwdn't faiw if we can weuse same bo, use p2p ow use system */
		KUNIT_FAIW(test, "dynamic p2p attachment faiwed with eww=%wd\n",
			   PTW_EWW(impowt));
	}
	dma_buf_put(dmabuf);
out:
	dwm_gem_object_put(&bo->ttm.base);
}

static const stwuct dma_buf_attach_ops nop2p_attach_ops = {
	.awwow_peew2peew = fawse,
	.move_notify = xe_dma_buf_move_notify
};

/*
 * We test the impwementation with bos of diffewent wesidency and with
 * impowtews with diffewent capabiwities; some wacking p2p suppowt and some
 * wacking dynamic capabiwities (attach_ops == NUWW). We awso fake
 * diffewent devices avoiding the impowt showtcut that just weuses the same
 * gem object.
 */
static const stwuct dma_buf_test_pawams test_pawams[] = {
	{.mem_mask = XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &xe_dma_buf_attach_ops},
	{.mem_mask = XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &xe_dma_buf_attach_ops,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &nop2p_attach_ops},
	{.mem_mask = XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &nop2p_attach_ops,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_VWAM0_BIT},
	{.mem_mask = XE_BO_CWEATE_VWAM0_BIT,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT,
	 .attach_ops = &xe_dma_buf_attach_ops},
	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT,
	 .attach_ops = &xe_dma_buf_attach_ops,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT,
	 .attach_ops = &nop2p_attach_ops},
	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT,
	 .attach_ops = &nop2p_attach_ops,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT},
	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT | XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &xe_dma_buf_attach_ops},
	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT | XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &xe_dma_buf_attach_ops,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT | XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &nop2p_attach_ops},
	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT | XE_BO_CWEATE_VWAM0_BIT,
	 .attach_ops = &nop2p_attach_ops,
	 .fowce_diffewent_devices = twue},

	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT | XE_BO_CWEATE_VWAM0_BIT},
	{.mem_mask = XE_BO_CWEATE_SYSTEM_BIT | XE_BO_CWEATE_VWAM0_BIT,
	 .fowce_diffewent_devices = twue},

	{}
};

static int dma_buf_wun_device(stwuct xe_device *xe)
{
	const stwuct dma_buf_test_pawams *pawams;
	stwuct kunit *test = xe_cuw_kunit();

	fow (pawams = test_pawams; pawams->mem_mask; ++pawams) {
		stwuct dma_buf_test_pawams p = *pawams;

		p.base.id = XE_TEST_WIVE_DMA_BUF;
		test->pwiv = &p;
		xe_test_dmabuf_impowt_same_dwivew(xe);
	}

	/* A non-zewo wetuwn wouwd hawt itewation ovew dwivew devices */
	wetuwn 0;
}

void xe_dma_buf_kunit(stwuct kunit *test)
{
	xe_caww_fow_each_device(dma_buf_wun_device);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_dma_buf_kunit);
