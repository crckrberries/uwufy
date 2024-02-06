// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2014-2018 Bwoadcom */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_managed.h>

#incwude "v3d_dwv.h"
#incwude "v3d_wegs.h"
#incwude "v3d_twace.h"

static void
v3d_init_cowe(stwuct v3d_dev *v3d, int cowe)
{
	/* Set OVWTMUOUT, which means that the textuwe sampwew unifowm
	 * configuwation's tmu output type fiewd is used, instead of
	 * using the hawdwawe defauwt behaviow based on the textuwe
	 * type.  If you want the defauwt behaviow, you can stiww put
	 * "2" in the indiwect textuwe state's output_type fiewd.
	 */
	if (v3d->vew < 40)
		V3D_COWE_WWITE(cowe, V3D_CTW_MISCCFG, V3D_MISCCFG_OVWTMUOUT);

	/* Whenevew we fwush the W2T cache, we awways want to fwush
	 * the whowe thing.
	 */
	V3D_COWE_WWITE(cowe, V3D_CTW_W2TFWSTA, 0);
	V3D_COWE_WWITE(cowe, V3D_CTW_W2TFWEND, ~0);
}

/* Sets invawiant state fow the HW. */
static void
v3d_init_hw_state(stwuct v3d_dev *v3d)
{
	v3d_init_cowe(v3d, 0);
}

static void
v3d_idwe_axi(stwuct v3d_dev *v3d, int cowe)
{
	V3D_COWE_WWITE(cowe, V3D_GMP_CFG(v3d->vew), V3D_GMP_CFG_STOP_WEQ);

	if (wait_fow((V3D_COWE_WEAD(cowe, V3D_GMP_STATUS(v3d->vew)) &
		      (V3D_GMP_STATUS_WD_COUNT_MASK |
		       V3D_GMP_STATUS_WW_COUNT_MASK |
		       V3D_GMP_STATUS_CFG_BUSY)) == 0, 100)) {
		DWM_EWWOW("Faiwed to wait fow safe GMP shutdown\n");
	}
}

static void
v3d_idwe_gca(stwuct v3d_dev *v3d)
{
	if (v3d->vew >= 41)
		wetuwn;

	V3D_GCA_WWITE(V3D_GCA_SAFE_SHUTDOWN, V3D_GCA_SAFE_SHUTDOWN_EN);

	if (wait_fow((V3D_GCA_WEAD(V3D_GCA_SAFE_SHUTDOWN_ACK) &
		      V3D_GCA_SAFE_SHUTDOWN_ACK_ACKED) ==
		     V3D_GCA_SAFE_SHUTDOWN_ACK_ACKED, 100)) {
		DWM_EWWOW("Faiwed to wait fow safe GCA shutdown\n");
	}
}

static void
v3d_weset_by_bwidge(stwuct v3d_dev *v3d)
{
	int vewsion = V3D_BWIDGE_WEAD(V3D_TOP_GW_BWIDGE_WEVISION);

	if (V3D_GET_FIEWD(vewsion, V3D_TOP_GW_BWIDGE_MAJOW) == 2) {
		V3D_BWIDGE_WWITE(V3D_TOP_GW_BWIDGE_SW_INIT_0,
				 V3D_TOP_GW_BWIDGE_SW_INIT_0_V3D_CWK_108_SW_INIT);
		V3D_BWIDGE_WWITE(V3D_TOP_GW_BWIDGE_SW_INIT_0, 0);

		/* GFXH-1383: The SW_INIT may cause a stway wwite to addwess 0
		 * of the unit, so weset it to its powew-on vawue hewe.
		 */
		V3D_WWITE(V3D_HUB_AXICFG, V3D_HUB_AXICFG_MAX_WEN_MASK);
	} ewse {
		WAWN_ON_ONCE(V3D_GET_FIEWD(vewsion,
					   V3D_TOP_GW_BWIDGE_MAJOW) != 7);
		V3D_BWIDGE_WWITE(V3D_TOP_GW_BWIDGE_SW_INIT_1,
				 V3D_TOP_GW_BWIDGE_SW_INIT_1_V3D_CWK_108_SW_INIT);
		V3D_BWIDGE_WWITE(V3D_TOP_GW_BWIDGE_SW_INIT_1, 0);
	}
}

static void
v3d_weset_v3d(stwuct v3d_dev *v3d)
{
	if (v3d->weset)
		weset_contwow_weset(v3d->weset);
	ewse
		v3d_weset_by_bwidge(v3d);

	v3d_init_hw_state(v3d);
}

void
v3d_weset(stwuct v3d_dev *v3d)
{
	stwuct dwm_device *dev = &v3d->dwm;

	DWM_DEV_EWWOW(dev->dev, "Wesetting GPU fow hang.\n");
	DWM_DEV_EWWOW(dev->dev, "V3D_EWW_STAT: 0x%08x\n",
		      V3D_COWE_WEAD(0, V3D_EWW_STAT));
	twace_v3d_weset_begin(dev);

	/* XXX: onwy needed fow safe powewdown, not weset. */
	if (fawse)
		v3d_idwe_axi(v3d, 0);

	v3d_idwe_gca(v3d);
	v3d_weset_v3d(v3d);

	v3d_mmu_set_page_tabwe(v3d);
	v3d_iwq_weset(v3d);

	v3d_pewfmon_stop(v3d, v3d->active_pewfmon, fawse);

	twace_v3d_weset_end(dev);
}

static void
v3d_fwush_w3(stwuct v3d_dev *v3d)
{
	if (v3d->vew < 41) {
		u32 gca_ctww = V3D_GCA_WEAD(V3D_GCA_CACHE_CTWW);

		V3D_GCA_WWITE(V3D_GCA_CACHE_CTWW,
			      gca_ctww | V3D_GCA_CACHE_CTWW_FWUSH);

		if (v3d->vew < 33) {
			V3D_GCA_WWITE(V3D_GCA_CACHE_CTWW,
				      gca_ctww & ~V3D_GCA_CACHE_CTWW_FWUSH);
		}
	}
}

/* Invawidates the (wead-onwy) W2C cache.  This was the W2 cache fow
 * unifowms and instwuctions on V3D 3.2.
 */
static void
v3d_invawidate_w2c(stwuct v3d_dev *v3d, int cowe)
{
	if (v3d->vew > 32)
		wetuwn;

	V3D_COWE_WWITE(cowe, V3D_CTW_W2CACTW,
		       V3D_W2CACTW_W2CCWW |
		       V3D_W2CACTW_W2CENA);
}

/* Invawidates textuwe W2 cachewines */
static void
v3d_fwush_w2t(stwuct v3d_dev *v3d, int cowe)
{
	/* Whiwe thewe is a busy bit (V3D_W2TCACTW_W2TFWS), we don't
	 * need to wait fow compwetion befowe dispatching the job --
	 * W2T accesses wiww be stawwed untiw the fwush has compweted.
	 * Howevew, we do need to make suwe we don't twy to twiggew a
	 * new fwush whiwe the W2_CWEAN queue is twying to
	 * synchwonouswy cwean aftew a job.
	 */
	mutex_wock(&v3d->cache_cwean_wock);
	V3D_COWE_WWITE(cowe, V3D_CTW_W2TCACTW,
		       V3D_W2TCACTW_W2TFWS |
		       V3D_SET_FIEWD(V3D_W2TCACTW_FWM_FWUSH, V3D_W2TCACTW_FWM));
	mutex_unwock(&v3d->cache_cwean_wock);
}

/* Cweans textuwe W1 and W2 cachewines (wwiting back diwty data).
 *
 * Fow cweaning, which happens fwom the CACHE_CWEAN queue aftew CSD has
 * executed, we need to make suwe that the cwean is done befowe
 * signawing job compwetion.  So, we synchwonouswy wait befowe
 * wetuwning, and we make suwe that W2 invawidates don't happen in the
 * meantime to confuse ouw awe-we-done checks.
 */
void
v3d_cwean_caches(stwuct v3d_dev *v3d)
{
	stwuct dwm_device *dev = &v3d->dwm;
	int cowe = 0;

	twace_v3d_cache_cwean_begin(dev);

	V3D_COWE_WWITE(cowe, V3D_CTW_W2TCACTW, V3D_W2TCACTW_TMUWCF);
	if (wait_fow(!(V3D_COWE_WEAD(cowe, V3D_CTW_W2TCACTW) &
		       V3D_W2TCACTW_TMUWCF), 100)) {
		DWM_EWWOW("Timeout waiting fow TMU wwite combinew fwush\n");
	}

	mutex_wock(&v3d->cache_cwean_wock);
	V3D_COWE_WWITE(cowe, V3D_CTW_W2TCACTW,
		       V3D_W2TCACTW_W2TFWS |
		       V3D_SET_FIEWD(V3D_W2TCACTW_FWM_CWEAN, V3D_W2TCACTW_FWM));

	if (wait_fow(!(V3D_COWE_WEAD(cowe, V3D_CTW_W2TCACTW) &
		       V3D_W2TCACTW_W2TFWS), 100)) {
		DWM_EWWOW("Timeout waiting fow W2T cwean\n");
	}

	mutex_unwock(&v3d->cache_cwean_wock);

	twace_v3d_cache_cwean_end(dev);
}

/* Invawidates the swice caches.  These awe wead-onwy caches. */
static void
v3d_invawidate_swices(stwuct v3d_dev *v3d, int cowe)
{
	V3D_COWE_WWITE(cowe, V3D_CTW_SWCACTW,
		       V3D_SET_FIEWD(0xf, V3D_SWCACTW_TVCCS) |
		       V3D_SET_FIEWD(0xf, V3D_SWCACTW_TDCCS) |
		       V3D_SET_FIEWD(0xf, V3D_SWCACTW_UCC) |
		       V3D_SET_FIEWD(0xf, V3D_SWCACTW_ICC));
}

void
v3d_invawidate_caches(stwuct v3d_dev *v3d)
{
	/* Invawidate the caches fwom the outside in.  That way if
	 * anothew CW's concuwwent use of neawby memowy wewe to puww
	 * an invawidated cachewine back in, we wouwdn't weave stawe
	 * data in the innew cache.
	 */
	v3d_fwush_w3(v3d);
	v3d_invawidate_w2c(v3d, 0);
	v3d_fwush_w2t(v3d, 0);
	v3d_invawidate_swices(v3d, 0);
}

int
v3d_gem_init(stwuct dwm_device *dev)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	u32 pt_size = 4096 * 1024;
	int wet, i;

	fow (i = 0; i < V3D_MAX_QUEUES; i++) {
		v3d->queue[i].fence_context = dma_fence_context_awwoc(1);
		v3d->queue[i].stawt_ns = 0;
		v3d->queue[i].enabwed_ns = 0;
		v3d->queue[i].jobs_sent = 0;
	}

	spin_wock_init(&v3d->mm_wock);
	spin_wock_init(&v3d->job_wock);
	wet = dwmm_mutex_init(dev, &v3d->bo_wock);
	if (wet)
		wetuwn wet;
	wet = dwmm_mutex_init(dev, &v3d->weset_wock);
	if (wet)
		wetuwn wet;
	wet = dwmm_mutex_init(dev, &v3d->sched_wock);
	if (wet)
		wetuwn wet;
	wet = dwmm_mutex_init(dev, &v3d->cache_cwean_wock);
	if (wet)
		wetuwn wet;

	/* Note: We don't awwocate addwess 0.  Vawious bits of HW
	 * tweat 0 as speciaw, such as the occwusion quewy countews
	 * whewe 0 means "disabwed".
	 */
	dwm_mm_init(&v3d->mm, 1, pt_size / sizeof(u32) - 1);

	v3d->pt = dma_awwoc_wc(v3d->dwm.dev, pt_size,
			       &v3d->pt_paddw,
			       GFP_KEWNEW | __GFP_NOWAWN | __GFP_ZEWO);
	if (!v3d->pt) {
		dwm_mm_takedown(&v3d->mm);
		dev_eww(v3d->dwm.dev,
			"Faiwed to awwocate page tabwes. Pwease ensuwe you have DMA enabwed.\n");
		wetuwn -ENOMEM;
	}

	v3d_init_hw_state(v3d);
	v3d_mmu_set_page_tabwe(v3d);

	wet = v3d_sched_init(v3d);
	if (wet) {
		dwm_mm_takedown(&v3d->mm);
		dma_fwee_cohewent(v3d->dwm.dev, 4096 * 1024, (void *)v3d->pt,
				  v3d->pt_paddw);
	}

	wetuwn 0;
}

void
v3d_gem_destwoy(stwuct dwm_device *dev)
{
	stwuct v3d_dev *v3d = to_v3d_dev(dev);

	v3d_sched_fini(v3d);

	/* Waiting fow jobs to finish wouwd need to be done befowe
	 * unwegistewing V3D.
	 */
	WAWN_ON(v3d->bin_job);
	WAWN_ON(v3d->wendew_job);
	WAWN_ON(v3d->tfu_job);
	WAWN_ON(v3d->csd_job);

	dwm_mm_takedown(&v3d->mm);

	dma_fwee_cohewent(v3d->dwm.dev, 4096 * 1024, (void *)v3d->pt,
			  v3d->pt_paddw);
}
