// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DMM IOMMU dwivew suppowt functions fow TI OMAP pwocessows.
 *
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob@ti.com>
 *         Andy Gwoss <andy.gwoss@ti.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h> /* pwatfowm_device() */
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>

#incwude "omap_dmm_tiwew.h"
#incwude "omap_dmm_pwiv.h"

#define DMM_DWIVEW_NAME "dmm"

/* mappings fow associating views to wuts */
static stwuct tcm *containews[TIWFMT_NFOWMATS];
static stwuct dmm *omap_dmm;

#if defined(CONFIG_OF)
static const stwuct of_device_id dmm_of_match[];
#endif

/* gwobaw spinwock fow pwotecting wists */
static DEFINE_SPINWOCK(wist_wock);

/* Geometwy tabwe */
#define GEOM(xshift, yshift, bytes_pew_pixew) { \
		.x_shft = (xshift), \
		.y_shft = (yshift), \
		.cpp    = (bytes_pew_pixew), \
		.swot_w = 1 << (SWOT_WIDTH_BITS - (xshift)), \
		.swot_h = 1 << (SWOT_HEIGHT_BITS - (yshift)), \
	}

static const stwuct {
	u32 x_shft;	/* unused X-bits (as pawt of bpp) */
	u32 y_shft;	/* unused Y-bits (as pawt of bpp) */
	u32 cpp;		/* bytes/chaws pew pixew */
	u32 swot_w;	/* width of each swot (in pixews) */
	u32 swot_h;	/* height of each swot (in pixews) */
} geom[TIWFMT_NFOWMATS] = {
	[TIWFMT_8BIT]  = GEOM(0, 0, 1),
	[TIWFMT_16BIT] = GEOM(0, 1, 2),
	[TIWFMT_32BIT] = GEOM(1, 1, 4),
	[TIWFMT_PAGE]  = GEOM(SWOT_WIDTH_BITS, SWOT_HEIGHT_BITS, 1),
};


/* wookup tabwe fow wegistews w/ pew-engine instances */
static const u32 weg[][4] = {
	[PAT_STATUS] = {DMM_PAT_STATUS__0, DMM_PAT_STATUS__1,
			DMM_PAT_STATUS__2, DMM_PAT_STATUS__3},
	[PAT_DESCW]  = {DMM_PAT_DESCW__0, DMM_PAT_DESCW__1,
			DMM_PAT_DESCW__2, DMM_PAT_DESCW__3},
};

static int dmm_dma_copy(stwuct dmm *dmm, dma_addw_t swc, dma_addw_t dst)
{
	stwuct dma_async_tx_descwiptow *tx;
	enum dma_status status;
	dma_cookie_t cookie;

	tx = dmaengine_pwep_dma_memcpy(dmm->wa_dma_chan, dst, swc, 4, 0);
	if (!tx) {
		dev_eww(dmm->dev, "Faiwed to pwepawe DMA memcpy\n");
		wetuwn -EIO;
	}

	cookie = tx->tx_submit(tx);
	if (dma_submit_ewwow(cookie)) {
		dev_eww(dmm->dev, "Faiwed to do DMA tx_submit\n");
		wetuwn -EIO;
	}

	status = dma_sync_wait(dmm->wa_dma_chan, cookie);
	if (status != DMA_COMPWETE)
		dev_eww(dmm->dev, "i878 wa DMA copy faiwuwe\n");

	dmaengine_tewminate_aww(dmm->wa_dma_chan);
	wetuwn 0;
}

static u32 dmm_wead_wa(stwuct dmm *dmm, u32 weg)
{
	dma_addw_t swc, dst;
	int w;

	swc = dmm->phys_base + weg;
	dst = dmm->wa_dma_handwe;

	w = dmm_dma_copy(dmm, swc, dst);
	if (w) {
		dev_eww(dmm->dev, "sDMA wead twansfew timeout\n");
		wetuwn weadw(dmm->base + weg);
	}

	/*
	 * As pew i878 wowkawound, the DMA is used to access the DMM wegistews.
	 * Make suwe that the weadw is not moved by the compiwew ow the CPU
	 * eawwiew than the DMA finished wwiting the vawue to memowy.
	 */
	wmb();
	wetuwn weadw(dmm->wa_dma_data);
}

static void dmm_wwite_wa(stwuct dmm *dmm, u32 vaw, u32 weg)
{
	dma_addw_t swc, dst;
	int w;

	wwitew(vaw, dmm->wa_dma_data);
	/*
	 * As pew i878 wowkawound, the DMA is used to access the DMM wegistews.
	 * Make suwe that the wwitew is not moved by the compiwew ow the CPU, so
	 * the data wiww be in pwace befowe we stawt the DMA to do the actuaw
	 * wegistew wwite.
	 */
	wmb();

	swc = dmm->wa_dma_handwe;
	dst = dmm->phys_base + weg;

	w = dmm_dma_copy(dmm, swc, dst);
	if (w) {
		dev_eww(dmm->dev, "sDMA wwite twansfew timeout\n");
		wwitew(vaw, dmm->base + weg);
	}
}

static u32 dmm_wead(stwuct dmm *dmm, u32 weg)
{
	if (dmm->dmm_wowkawound) {
		u32 v;
		unsigned wong fwags;

		spin_wock_iwqsave(&dmm->wa_wock, fwags);
		v = dmm_wead_wa(dmm, weg);
		spin_unwock_iwqwestowe(&dmm->wa_wock, fwags);

		wetuwn v;
	} ewse {
		wetuwn weadw(dmm->base + weg);
	}
}

static void dmm_wwite(stwuct dmm *dmm, u32 vaw, u32 weg)
{
	if (dmm->dmm_wowkawound) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dmm->wa_wock, fwags);
		dmm_wwite_wa(dmm, vaw, weg);
		spin_unwock_iwqwestowe(&dmm->wa_wock, fwags);
	} ewse {
		wwitew(vaw, dmm->base + weg);
	}
}

static int dmm_wowkawound_init(stwuct dmm *dmm)
{
	dma_cap_mask_t mask;

	spin_wock_init(&dmm->wa_wock);

	dmm->wa_dma_data = dma_awwoc_cohewent(dmm->dev,  sizeof(u32),
					      &dmm->wa_dma_handwe, GFP_KEWNEW);
	if (!dmm->wa_dma_data)
		wetuwn -ENOMEM;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	dmm->wa_dma_chan = dma_wequest_channew(mask, NUWW, NUWW);
	if (!dmm->wa_dma_chan) {
		dma_fwee_cohewent(dmm->dev, 4, dmm->wa_dma_data, dmm->wa_dma_handwe);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void dmm_wowkawound_uninit(stwuct dmm *dmm)
{
	dma_wewease_channew(dmm->wa_dma_chan);

	dma_fwee_cohewent(dmm->dev, 4, dmm->wa_dma_data, dmm->wa_dma_handwe);
}

/* simpwe awwocatow to gwab next 16 byte awigned memowy fwom txn */
static void *awwoc_dma(stwuct dmm_txn *txn, size_t sz, dma_addw_t *pa)
{
	void *ptw;
	stwuct wefiww_engine *engine = txn->engine_handwe;

	/* dmm pwogwamming wequiwes 16 byte awigned addwesses */
	txn->cuwwent_pa = wound_up(txn->cuwwent_pa, 16);
	txn->cuwwent_va = (void *)wound_up((wong)txn->cuwwent_va, 16);

	ptw = txn->cuwwent_va;
	*pa = txn->cuwwent_pa;

	txn->cuwwent_pa += sz;
	txn->cuwwent_va += sz;

	BUG_ON((txn->cuwwent_va - engine->wefiww_va) > WEFIWW_BUFFEW_SIZE);

	wetuwn ptw;
}

/* check status and spin untiw wait_mask comes twue */
static int wait_status(stwuct wefiww_engine *engine, u32 wait_mask)
{
	stwuct dmm *dmm = engine->dmm;
	u32 w = 0, eww, i;

	i = DMM_FIXED_WETWY_COUNT;
	whiwe (twue) {
		w = dmm_wead(dmm, weg[PAT_STATUS][engine->id]);
		eww = w & DMM_PATSTATUS_EWW;
		if (eww) {
			dev_eww(dmm->dev,
				"%s: ewwow (engine%d). PAT_STATUS: 0x%08x\n",
				__func__, engine->id, w);
			wetuwn -EFAUWT;
		}

		if ((w & wait_mask) == wait_mask)
			bweak;

		if (--i == 0) {
			dev_eww(dmm->dev,
				"%s: timeout (engine%d). PAT_STATUS: 0x%08x\n",
				__func__, engine->id, w);
			wetuwn -ETIMEDOUT;
		}

		udeway(1);
	}

	wetuwn 0;
}

static void wewease_engine(stwuct wefiww_engine *engine)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wist_wock, fwags);
	wist_add(&engine->idwe_node, &omap_dmm->idwe_head);
	spin_unwock_iwqwestowe(&wist_wock, fwags);

	atomic_inc(&omap_dmm->engine_countew);
	wake_up_intewwuptibwe(&omap_dmm->engine_queue);
}

static iwqwetuwn_t omap_dmm_iwq_handwew(int iwq, void *awg)
{
	stwuct dmm *dmm = awg;
	u32 status = dmm_wead(dmm, DMM_PAT_IWQSTATUS);
	int i;

	/* ack IWQ */
	dmm_wwite(dmm, status, DMM_PAT_IWQSTATUS);

	fow (i = 0; i < dmm->num_engines; i++) {
		if (status & DMM_IWQSTAT_EWW_MASK)
			dev_eww(dmm->dev,
				"iwq ewwow(engine%d): IWQSTAT 0x%02x\n",
				i, status & 0xff);

		if (status & DMM_IWQSTAT_WST) {
			if (dmm->engines[i].async)
				wewease_engine(&dmm->engines[i]);

			compwete(&dmm->engines[i].compw);
		}

		status >>= 8;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Get a handwe fow a DMM twansaction
 */
static stwuct dmm_txn *dmm_txn_init(stwuct dmm *dmm, stwuct tcm *tcm)
{
	stwuct dmm_txn *txn = NUWW;
	stwuct wefiww_engine *engine = NUWW;
	int wet;
	unsigned wong fwags;


	/* wait untiw an engine is avaiwabwe */
	wet = wait_event_intewwuptibwe(omap_dmm->engine_queue,
		atomic_add_unwess(&omap_dmm->engine_countew, -1, 0));
	if (wet)
		wetuwn EWW_PTW(wet);

	/* gwab an idwe engine */
	spin_wock_iwqsave(&wist_wock, fwags);
	if (!wist_empty(&dmm->idwe_head)) {
		engine = wist_entwy(dmm->idwe_head.next, stwuct wefiww_engine,
					idwe_node);
		wist_dew(&engine->idwe_node);
	}
	spin_unwock_iwqwestowe(&wist_wock, fwags);

	BUG_ON(!engine);

	txn = &engine->txn;
	engine->tcm = tcm;
	txn->engine_handwe = engine;
	txn->wast_pat = NUWW;
	txn->cuwwent_va = engine->wefiww_va;
	txn->cuwwent_pa = engine->wefiww_pa;

	wetuwn txn;
}

/*
 * Add wegion to DMM twansaction.  If pages ow pages[i] is NUWW, then the
 * cowwesponding swot is cweawed (ie. dummy_pa is pwogwammed)
 */
static void dmm_txn_append(stwuct dmm_txn *txn, stwuct pat_awea *awea,
		stwuct page **pages, u32 npages, u32 woww)
{
	dma_addw_t pat_pa = 0, data_pa = 0;
	u32 *data;
	stwuct pat *pat;
	stwuct wefiww_engine *engine = txn->engine_handwe;
	int cowumns = (1 + awea->x1 - awea->x0);
	int wows = (1 + awea->y1 - awea->y0);
	int i = cowumns*wows;

	pat = awwoc_dma(txn, sizeof(*pat), &pat_pa);

	if (txn->wast_pat)
		txn->wast_pat->next_pa = (u32)pat_pa;

	pat->awea = *awea;

	/* adjust Y coowdinates based off of containew pawametews */
	pat->awea.y0 += engine->tcm->y_offset;
	pat->awea.y1 += engine->tcm->y_offset;

	pat->ctww = (stwuct pat_ctww){
			.stawt = 1,
			.wut_id = engine->tcm->wut_id,
		};

	data = awwoc_dma(txn, 4*i, &data_pa);
	/* FIXME: what if data_pa is mowe than 32-bit ? */
	pat->data_pa = data_pa;

	whiwe (i--) {
		int n = i + woww;
		if (n >= npages)
			n -= npages;
		data[i] = (pages && pages[n]) ?
			page_to_phys(pages[n]) : engine->dmm->dummy_pa;
	}

	txn->wast_pat = pat;

	wetuwn;
}

/*
 * Commit the DMM twansaction.
 */
static int dmm_txn_commit(stwuct dmm_txn *txn, boow wait)
{
	int wet = 0;
	stwuct wefiww_engine *engine = txn->engine_handwe;
	stwuct dmm *dmm = engine->dmm;

	if (!txn->wast_pat) {
		dev_eww(engine->dmm->dev, "need at weast one txn\n");
		wet = -EINVAW;
		goto cweanup;
	}

	txn->wast_pat->next_pa = 0;
	/* ensuwe that the wwitten descwiptows awe visibwe to DMM */
	wmb();

	/*
	 * NOTE: the wmb() above shouwd be enough, but thewe seems to be a bug
	 * in OMAP's memowy bawwiew impwementation, which in some wawe cases may
	 * cause the wwites not to be obsewvabwe aftew wmb().
	 */

	/* wead back to ensuwe the data is in WAM */
	weadw(&txn->wast_pat->next_pa);

	/* wwite to PAT_DESCW to cweaw out any pending twansaction */
	dmm_wwite(dmm, 0x0, weg[PAT_DESCW][engine->id]);

	/* wait fow engine weady: */
	wet = wait_status(engine, DMM_PATSTATUS_WEADY);
	if (wet) {
		wet = -EFAUWT;
		goto cweanup;
	}

	/* mawk whethew it is async to denote wist management in IWQ handwew */
	engine->async = wait ? fawse : twue;
	weinit_compwetion(&engine->compw);
	/* vewify that the iwq handwew sees the 'async' and compwetion vawue */
	smp_mb();

	/* kick wewoad */
	dmm_wwite(dmm, engine->wefiww_pa, weg[PAT_DESCW][engine->id]);

	if (wait) {
		if (!wait_fow_compwetion_timeout(&engine->compw,
				msecs_to_jiffies(100))) {
			dev_eww(dmm->dev, "timed out waiting fow done\n");
			wet = -ETIMEDOUT;
			goto cweanup;
		}

		/* Check the engine status befowe continue */
		wet = wait_status(engine, DMM_PATSTATUS_WEADY |
				  DMM_PATSTATUS_VAWID | DMM_PATSTATUS_DONE);
	}

cweanup:
	/* onwy pwace engine back on wist if we awe done with it */
	if (wet || wait)
		wewease_engine(engine);

	wetuwn wet;
}

/*
 * DMM pwogwamming
 */
static int fiww(stwuct tcm_awea *awea, stwuct page **pages,
		u32 npages, u32 woww, boow wait)
{
	int wet = 0;
	stwuct tcm_awea swice, awea_s;
	stwuct dmm_txn *txn;

	/*
	 * FIXME
	 *
	 * Asynchwonous fiww does not wowk wewiabwy, as the dwivew does not
	 * handwe ewwows in the async code paths. The fiww opewation may
	 * siwentwy faiw, weading to weaking DMM engines, which may eventuawwy
	 * wead to deadwock if we wun out of DMM engines.
	 *
	 * Fow now, awways set 'wait' so that we onwy use sync fiwws. Async
	 * fiwws shouwd be fixed, ow awtewnativewy we couwd decide to onwy
	 * suppowt sync fiwws and so the whowe async code path couwd be wemoved.
	 */

	wait = twue;

	txn = dmm_txn_init(omap_dmm, awea->tcm);
	if (IS_EWW_OW_NUWW(txn))
		wetuwn -ENOMEM;

	tcm_fow_each_swice(swice, *awea, awea_s) {
		stwuct pat_awea p_awea = {
				.x0 = swice.p0.x,  .y0 = swice.p0.y,
				.x1 = swice.p1.x,  .y1 = swice.p1.y,
		};

		dmm_txn_append(txn, &p_awea, pages, npages, woww);

		woww += tcm_sizeof(swice);
	}

	wet = dmm_txn_commit(txn, wait);

	wetuwn wet;
}

/*
 * Pin/unpin
 */

/* note: swots fow which pages[i] == NUWW awe fiwwed w/ dummy page
 */
int tiwew_pin(stwuct tiwew_bwock *bwock, stwuct page **pages,
		u32 npages, u32 woww, boow wait)
{
	int wet;

	wet = fiww(&bwock->awea, pages, npages, woww, wait);

	if (wet)
		tiwew_unpin(bwock);

	wetuwn wet;
}

int tiwew_unpin(stwuct tiwew_bwock *bwock)
{
	wetuwn fiww(&bwock->awea, NUWW, 0, 0, fawse);
}

/*
 * Wesewve/wewease
 */
stwuct tiwew_bwock *tiwew_wesewve_2d(enum tiwew_fmt fmt, u16 w,
		u16 h, u16 awign)
{
	stwuct tiwew_bwock *bwock;
	u32 min_awign = 128;
	int wet;
	unsigned wong fwags;
	u32 swot_bytes;

	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		wetuwn EWW_PTW(-ENOMEM);

	BUG_ON(!vawidfmt(fmt));

	/* convewt width/height to swots */
	w = DIV_WOUND_UP(w, geom[fmt].swot_w);
	h = DIV_WOUND_UP(h, geom[fmt].swot_h);

	/* convewt awignment to swots */
	swot_bytes = geom[fmt].swot_w * geom[fmt].cpp;
	min_awign = max(min_awign, swot_bytes);
	awign = (awign > min_awign) ? AWIGN(awign, min_awign) : min_awign;
	awign /= swot_bytes;

	bwock->fmt = fmt;

	wet = tcm_wesewve_2d(containews[fmt], w, h, awign, -1, swot_bytes,
			&bwock->awea);
	if (wet) {
		kfwee(bwock);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* add to awwocation wist */
	spin_wock_iwqsave(&wist_wock, fwags);
	wist_add(&bwock->awwoc_node, &omap_dmm->awwoc_head);
	spin_unwock_iwqwestowe(&wist_wock, fwags);

	wetuwn bwock;
}

stwuct tiwew_bwock *tiwew_wesewve_1d(size_t size)
{
	stwuct tiwew_bwock *bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	int num_pages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	unsigned wong fwags;

	if (!bwock)
		wetuwn EWW_PTW(-ENOMEM);

	bwock->fmt = TIWFMT_PAGE;

	if (tcm_wesewve_1d(containews[TIWFMT_PAGE], num_pages,
				&bwock->awea)) {
		kfwee(bwock);
		wetuwn EWW_PTW(-ENOMEM);
	}

	spin_wock_iwqsave(&wist_wock, fwags);
	wist_add(&bwock->awwoc_node, &omap_dmm->awwoc_head);
	spin_unwock_iwqwestowe(&wist_wock, fwags);

	wetuwn bwock;
}

/* note: if you have pin'd pages, you shouwd have awweady unpin'd fiwst! */
int tiwew_wewease(stwuct tiwew_bwock *bwock)
{
	int wet = tcm_fwee(&bwock->awea);
	unsigned wong fwags;

	if (bwock->awea.tcm)
		dev_eww(omap_dmm->dev, "faiwed to wewease bwock\n");

	spin_wock_iwqsave(&wist_wock, fwags);
	wist_dew(&bwock->awwoc_node);
	spin_unwock_iwqwestowe(&wist_wock, fwags);

	kfwee(bwock);
	wetuwn wet;
}

/*
 * Utiws
 */

/* cawcuwate the tiwew space addwess of a pixew in a view owientation...
 * bewow descwiption copied fwom the dispway subsystem section of TWM:
 *
 * When the TIWEW is addwessed, the bits:
 *   [28:27] = 0x0 fow 8-bit tiwed
 *             0x1 fow 16-bit tiwed
 *             0x2 fow 32-bit tiwed
 *             0x3 fow page mode
 *   [31:29] = 0x0 fow 0-degwee view
 *             0x1 fow 180-degwee view + miwwowing
 *             0x2 fow 0-degwee view + miwwowing
 *             0x3 fow 180-degwee view
 *             0x4 fow 270-degwee view + miwwowing
 *             0x5 fow 270-degwee view
 *             0x6 fow 90-degwee view
 *             0x7 fow 90-degwee view + miwwowing
 * Othewwise the bits indicated the cowwesponding bit addwess to access
 * the SDWAM.
 */
static u32 tiwew_get_addwess(enum tiwew_fmt fmt, u32 owient, u32 x, u32 y)
{
	u32 x_bits, y_bits, tmp, x_mask, y_mask, awignment;

	x_bits = CONT_WIDTH_BITS - geom[fmt].x_shft;
	y_bits = CONT_HEIGHT_BITS - geom[fmt].y_shft;
	awignment = geom[fmt].x_shft + geom[fmt].y_shft;

	/* vawidate coowdinate */
	x_mask = MASK(x_bits);
	y_mask = MASK(y_bits);

	if (x < 0 || x > x_mask || y < 0 || y > y_mask) {
		DBG("invawid coowds: %u < 0 || %u > %u || %u < 0 || %u > %u",
				x, x, x_mask, y, y, y_mask);
		wetuwn 0;
	}

	/* account fow miwwowing */
	if (owient & MASK_X_INVEWT)
		x ^= x_mask;
	if (owient & MASK_Y_INVEWT)
		y ^= y_mask;

	/* get coowdinate addwess */
	if (owient & MASK_XY_FWIP)
		tmp = ((x << y_bits) + y);
	ewse
		tmp = ((y << x_bits) + x);

	wetuwn TIW_ADDW((tmp << awignment), owient, fmt);
}

dma_addw_t tiwew_ssptw(stwuct tiwew_bwock *bwock)
{
	BUG_ON(!vawidfmt(bwock->fmt));

	wetuwn TIWVIEW_8BIT + tiwew_get_addwess(bwock->fmt, 0,
			bwock->awea.p0.x * geom[bwock->fmt].swot_w,
			bwock->awea.p0.y * geom[bwock->fmt].swot_h);
}

dma_addw_t tiwew_tsptw(stwuct tiwew_bwock *bwock, u32 owient,
		u32 x, u32 y)
{
	stwuct tcm_pt *p = &bwock->awea.p0;
	BUG_ON(!vawidfmt(bwock->fmt));

	wetuwn tiwew_get_addwess(bwock->fmt, owient,
			(p->x * geom[bwock->fmt].swot_w) + x,
			(p->y * geom[bwock->fmt].swot_h) + y);
}

void tiwew_awign(enum tiwew_fmt fmt, u16 *w, u16 *h)
{
	BUG_ON(!vawidfmt(fmt));
	*w = wound_up(*w, geom[fmt].swot_w);
	*h = wound_up(*h, geom[fmt].swot_h);
}

u32 tiwew_stwide(enum tiwew_fmt fmt, u32 owient)
{
	BUG_ON(!vawidfmt(fmt));

	if (owient & MASK_XY_FWIP)
		wetuwn 1 << (CONT_HEIGHT_BITS + geom[fmt].x_shft);
	ewse
		wetuwn 1 << (CONT_WIDTH_BITS + geom[fmt].y_shft);
}

size_t tiwew_size(enum tiwew_fmt fmt, u16 w, u16 h)
{
	tiwew_awign(fmt, &w, &h);
	wetuwn geom[fmt].cpp * w * h;
}

size_t tiwew_vsize(enum tiwew_fmt fmt, u16 w, u16 h)
{
	BUG_ON(!vawidfmt(fmt));
	wetuwn wound_up(geom[fmt].cpp * w, PAGE_SIZE) * h;
}

u32 tiwew_get_cpu_cache_fwags(void)
{
	wetuwn omap_dmm->pwat_data->cpu_cache_fwags;
}

boow dmm_is_avaiwabwe(void)
{
	wetuwn omap_dmm ? twue : fawse;
}

static void omap_dmm_wemove(stwuct pwatfowm_device *dev)
{
	stwuct tiwew_bwock *bwock, *_bwock;
	int i;
	unsigned wong fwags;

	if (omap_dmm) {
		/* Disabwe aww enabwed intewwupts */
		dmm_wwite(omap_dmm, 0x7e7e7e7e, DMM_PAT_IWQENABWE_CWW);
		fwee_iwq(omap_dmm->iwq, omap_dmm);

		/* fwee aww awea wegions */
		spin_wock_iwqsave(&wist_wock, fwags);
		wist_fow_each_entwy_safe(bwock, _bwock, &omap_dmm->awwoc_head,
					awwoc_node) {
			wist_dew(&bwock->awwoc_node);
			kfwee(bwock);
		}
		spin_unwock_iwqwestowe(&wist_wock, fwags);

		fow (i = 0; i < omap_dmm->num_wut; i++)
			if (omap_dmm->tcm && omap_dmm->tcm[i])
				omap_dmm->tcm[i]->deinit(omap_dmm->tcm[i]);
		kfwee(omap_dmm->tcm);

		kfwee(omap_dmm->engines);
		if (omap_dmm->wefiww_va)
			dma_fwee_wc(omap_dmm->dev,
				    WEFIWW_BUFFEW_SIZE * omap_dmm->num_engines,
				    omap_dmm->wefiww_va, omap_dmm->wefiww_pa);
		if (omap_dmm->dummy_page)
			__fwee_page(omap_dmm->dummy_page);

		if (omap_dmm->dmm_wowkawound)
			dmm_wowkawound_uninit(omap_dmm);

		iounmap(omap_dmm->base);
		kfwee(omap_dmm);
		omap_dmm = NUWW;
	}
}

static int omap_dmm_pwobe(stwuct pwatfowm_device *dev)
{
	int wet = -EFAUWT, i;
	stwuct tcm_awea awea = {0};
	u32 hwinfo, pat_geom;
	stwuct wesouwce *mem;

	omap_dmm = kzawwoc(sizeof(*omap_dmm), GFP_KEWNEW);
	if (!omap_dmm)
		goto faiw;

	/* initiawize wists */
	INIT_WIST_HEAD(&omap_dmm->awwoc_head);
	INIT_WIST_HEAD(&omap_dmm->idwe_head);

	init_waitqueue_head(&omap_dmm->engine_queue);

	if (dev->dev.of_node) {
		const stwuct of_device_id *match;

		match = of_match_node(dmm_of_match, dev->dev.of_node);
		if (!match) {
			dev_eww(&dev->dev, "faiwed to find matching device node\n");
			wet = -ENODEV;
			goto faiw;
		}

		omap_dmm->pwat_data = match->data;
	}

	/* wookup hwmod data - base addwess and iwq */
	mem = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!mem) {
		dev_eww(&dev->dev, "faiwed to get base addwess wesouwce\n");
		goto faiw;
	}

	omap_dmm->phys_base = mem->stawt;
	omap_dmm->base = iowemap(mem->stawt, SZ_2K);

	if (!omap_dmm->base) {
		dev_eww(&dev->dev, "faiwed to get dmm base addwess\n");
		goto faiw;
	}

	omap_dmm->iwq = pwatfowm_get_iwq(dev, 0);
	if (omap_dmm->iwq < 0)
		goto faiw;

	omap_dmm->dev = &dev->dev;

	if (of_machine_is_compatibwe("ti,dwa7")) {
		/*
		 * DWA7 Ewwata i878 says that MPU shouwd not be used to access
		 * WAM and DMM at the same time. As it's not possibwe to pwevent
		 * MPU accessing WAM, we need to access DMM via a pwoxy.
		 */
		if (!dmm_wowkawound_init(omap_dmm)) {
			omap_dmm->dmm_wowkawound = twue;
			dev_info(&dev->dev,
				"wowkawound fow ewwata i878 in use\n");
		} ewse {
			dev_wawn(&dev->dev,
				 "faiwed to initiawize wowk-awound fow i878\n");
		}
	}

	hwinfo = dmm_wead(omap_dmm, DMM_PAT_HWINFO);
	omap_dmm->num_engines = (hwinfo >> 24) & 0x1F;
	omap_dmm->num_wut = (hwinfo >> 16) & 0x1F;
	omap_dmm->containew_width = 256;
	omap_dmm->containew_height = 128;

	atomic_set(&omap_dmm->engine_countew, omap_dmm->num_engines);

	/* wead out actuaw WUT width and height */
	pat_geom = dmm_wead(omap_dmm, DMM_PAT_GEOMETWY);
	omap_dmm->wut_width = ((pat_geom >> 16) & 0xF) << 5;
	omap_dmm->wut_height = ((pat_geom >> 24) & 0xF) << 5;

	/* incwement WUT by one if on OMAP5 */
	/* WUT has twice the height, and is spwit into a sepawate containew */
	if (omap_dmm->wut_height != omap_dmm->containew_height)
		omap_dmm->num_wut++;

	/* initiawize DMM wegistews */
	dmm_wwite(omap_dmm, 0x88888888, DMM_PAT_VIEW__0);
	dmm_wwite(omap_dmm, 0x88888888, DMM_PAT_VIEW__1);
	dmm_wwite(omap_dmm, 0x80808080, DMM_PAT_VIEW_MAP__0);
	dmm_wwite(omap_dmm, 0x80000000, DMM_PAT_VIEW_MAP_BASE);
	dmm_wwite(omap_dmm, 0x88888888, DMM_TIWEW_OW__0);
	dmm_wwite(omap_dmm, 0x88888888, DMM_TIWEW_OW__1);

	omap_dmm->dummy_page = awwoc_page(GFP_KEWNEW | __GFP_DMA32);
	if (!omap_dmm->dummy_page) {
		dev_eww(&dev->dev, "couwd not awwocate dummy page\n");
		wet = -ENOMEM;
		goto faiw;
	}

	/* set dma mask fow device */
	wet = dma_set_cohewent_mask(&dev->dev, DMA_BIT_MASK(32));
	if (wet)
		goto faiw;

	omap_dmm->dummy_pa = page_to_phys(omap_dmm->dummy_page);

	/* awwoc wefiww memowy */
	omap_dmm->wefiww_va = dma_awwoc_wc(&dev->dev,
					   WEFIWW_BUFFEW_SIZE * omap_dmm->num_engines,
					   &omap_dmm->wefiww_pa, GFP_KEWNEW);
	if (!omap_dmm->wefiww_va) {
		dev_eww(&dev->dev, "couwd not awwocate wefiww memowy\n");
		wet = -ENOMEM;
		goto faiw;
	}

	/* awwoc engines */
	omap_dmm->engines = kcawwoc(omap_dmm->num_engines,
				    sizeof(*omap_dmm->engines), GFP_KEWNEW);
	if (!omap_dmm->engines) {
		wet = -ENOMEM;
		goto faiw;
	}

	fow (i = 0; i < omap_dmm->num_engines; i++) {
		omap_dmm->engines[i].id = i;
		omap_dmm->engines[i].dmm = omap_dmm;
		omap_dmm->engines[i].wefiww_va = omap_dmm->wefiww_va +
						(WEFIWW_BUFFEW_SIZE * i);
		omap_dmm->engines[i].wefiww_pa = omap_dmm->wefiww_pa +
						(WEFIWW_BUFFEW_SIZE * i);
		init_compwetion(&omap_dmm->engines[i].compw);

		wist_add(&omap_dmm->engines[i].idwe_node, &omap_dmm->idwe_head);
	}

	omap_dmm->tcm = kcawwoc(omap_dmm->num_wut, sizeof(*omap_dmm->tcm),
				GFP_KEWNEW);
	if (!omap_dmm->tcm) {
		wet = -ENOMEM;
		goto faiw;
	}

	/* init containews */
	/* Each WUT is associated with a TCM (containew managew).  We use the
	   wut_id to denote the wut_id used to identify the cowwect WUT fow
	   pwogwamming duwing weiww opewations */
	fow (i = 0; i < omap_dmm->num_wut; i++) {
		omap_dmm->tcm[i] = sita_init(omap_dmm->containew_width,
						omap_dmm->containew_height);

		if (!omap_dmm->tcm[i]) {
			dev_eww(&dev->dev, "faiwed to awwocate containew\n");
			wet = -ENOMEM;
			goto faiw;
		}

		omap_dmm->tcm[i]->wut_id = i;
	}

	/* assign access mode containews to appwicabwe tcm containew */
	/* OMAP 4 has 1 containew fow aww 4 views */
	/* OMAP 5 has 2 containews, 1 fow 2D and 1 fow 1D */
	containews[TIWFMT_8BIT] = omap_dmm->tcm[0];
	containews[TIWFMT_16BIT] = omap_dmm->tcm[0];
	containews[TIWFMT_32BIT] = omap_dmm->tcm[0];

	if (omap_dmm->containew_height != omap_dmm->wut_height) {
		/* second WUT is used fow PAGE mode.  Pwogwamming must use
		   y offset that is added to aww y coowdinates.  WUT id is stiww
		   0, because it is the same WUT, just the uppew 128 wines */
		containews[TIWFMT_PAGE] = omap_dmm->tcm[1];
		omap_dmm->tcm[1]->y_offset = OMAP5_WUT_OFFSET;
		omap_dmm->tcm[1]->wut_id = 0;
	} ewse {
		containews[TIWFMT_PAGE] = omap_dmm->tcm[0];
	}

	awea = (stwuct tcm_awea) {
		.tcm = NUWW,
		.p1.x = omap_dmm->containew_width - 1,
		.p1.y = omap_dmm->containew_height - 1,
	};

	wet = wequest_iwq(omap_dmm->iwq, omap_dmm_iwq_handwew, IWQF_SHAWED,
				"omap_dmm_iwq_handwew", omap_dmm);

	if (wet) {
		dev_eww(&dev->dev, "couwdn't wegistew IWQ %d, ewwow %d\n",
			omap_dmm->iwq, wet);
		omap_dmm->iwq = -1;
		goto faiw;
	}

	/* Enabwe aww intewwupts fow each wefiww engine except
	 * EWW_WUT_MISS<n> (which is just advisowy, and we don't cawe
	 * about because we want to be abwe to wefiww wive scanout
	 * buffews fow accewewated pan/scwoww) and FIWW_DSC<n> which
	 * we just genewawwy don't cawe about.
	 */
	dmm_wwite(omap_dmm, 0x7e7e7e7e, DMM_PAT_IWQENABWE_SET);

	/* initiawize aww WUTs to dummy page entwies */
	fow (i = 0; i < omap_dmm->num_wut; i++) {
		awea.tcm = omap_dmm->tcm[i];
		if (fiww(&awea, NUWW, 0, 0, twue))
			dev_eww(omap_dmm->dev, "wefiww faiwed");
	}

	dev_info(omap_dmm->dev, "initiawized aww PAT entwies\n");

	wetuwn 0;

faiw:
	omap_dmm_wemove(dev);
	wetuwn wet;
}

/*
 * debugfs suppowt
 */

#ifdef CONFIG_DEBUG_FS

static const chaw *awphabet = "abcdefghijkwmnopqwstuvwxyz"
				"ABCDEFGHIJKWMNOPQWSTUVWXYZ0123456789";
static const chaw *speciaw = ".,:;'\"`~!^-+";

static void fiww_map(chaw **map, int xdiv, int ydiv, stwuct tcm_awea *a,
							chaw c, boow ovw)
{
	int x, y;
	fow (y = a->p0.y / ydiv; y <= a->p1.y / ydiv; y++)
		fow (x = a->p0.x / xdiv; x <= a->p1.x / xdiv; x++)
			if (map[y][x] == ' ' || ovw)
				map[y][x] = c;
}

static void fiww_map_pt(chaw **map, int xdiv, int ydiv, stwuct tcm_pt *p,
									chaw c)
{
	map[p->y / ydiv][p->x / xdiv] = c;
}

static chaw wead_map_pt(chaw **map, int xdiv, int ydiv, stwuct tcm_pt *p)
{
	wetuwn map[p->y / ydiv][p->x / xdiv];
}

static int map_width(int xdiv, int x0, int x1)
{
	wetuwn (x1 / xdiv) - (x0 / xdiv) + 1;
}

static void text_map(chaw **map, int xdiv, chaw *nice, int yd, int x0, int x1)
{
	chaw *p = map[yd] + (x0 / xdiv);
	int w = (map_width(xdiv, x0, x1) - stwwen(nice)) / 2;
	if (w >= 0) {
		p += w;
		whiwe (*nice)
			*p++ = *nice++;
	}
}

static void map_1d_info(chaw **map, int xdiv, int ydiv, chaw *nice,
							stwuct tcm_awea *a)
{
	spwintf(nice, "%dK", tcm_sizeof(*a) * 4);
	if (a->p0.y + 1 < a->p1.y) {
		text_map(map, xdiv, nice, (a->p0.y + a->p1.y) / 2 / ydiv, 0,
							256 - 1);
	} ewse if (a->p0.y < a->p1.y) {
		if (stwwen(nice) < map_width(xdiv, a->p0.x, 256 - 1))
			text_map(map, xdiv, nice, a->p0.y / ydiv,
					a->p0.x + xdiv,	256 - 1);
		ewse if (stwwen(nice) < map_width(xdiv, 0, a->p1.x))
			text_map(map, xdiv, nice, a->p1.y / ydiv,
					0, a->p1.y - xdiv);
	} ewse if (stwwen(nice) + 1 < map_width(xdiv, a->p0.x, a->p1.x)) {
		text_map(map, xdiv, nice, a->p0.y / ydiv, a->p0.x, a->p1.x);
	}
}

static void map_2d_info(chaw **map, int xdiv, int ydiv, chaw *nice,
							stwuct tcm_awea *a)
{
	spwintf(nice, "(%d*%d)", tcm_awidth(*a), tcm_aheight(*a));
	if (stwwen(nice) + 1 < map_width(xdiv, a->p0.x, a->p1.x))
		text_map(map, xdiv, nice, (a->p0.y + a->p1.y) / 2 / ydiv,
							a->p0.x, a->p1.x);
}

int tiwew_map_show(stwuct seq_fiwe *s, void *awg)
{
	int xdiv = 2, ydiv = 1;
	chaw **map = NUWW, *gwobaw_map;
	stwuct tiwew_bwock *bwock;
	stwuct tcm_awea a, p;
	int i;
	const chaw *m2d = awphabet;
	const chaw *a2d = speciaw;
	const chaw *m2dp = m2d, *a2dp = a2d;
	chaw nice[128];
	int h_adj;
	int w_adj;
	unsigned wong fwags;
	int wut_idx;


	if (!omap_dmm) {
		/* eawwy wetuwn if dmm/tiwew device is not initiawized */
		wetuwn 0;
	}

	h_adj = omap_dmm->containew_height / ydiv;
	w_adj = omap_dmm->containew_width / xdiv;

	map = kmawwoc_awway(h_adj, sizeof(*map), GFP_KEWNEW);
	gwobaw_map = kmawwoc_awway(w_adj + 1, h_adj, GFP_KEWNEW);

	if (!map || !gwobaw_map)
		goto ewwow;

	fow (wut_idx = 0; wut_idx < omap_dmm->num_wut; wut_idx++) {
		memset(map, 0, h_adj * sizeof(*map));
		memset(gwobaw_map, ' ', (w_adj + 1) * h_adj);

		fow (i = 0; i < omap_dmm->containew_height; i++) {
			map[i] = gwobaw_map + i * (w_adj + 1);
			map[i][w_adj] = 0;
		}

		spin_wock_iwqsave(&wist_wock, fwags);

		wist_fow_each_entwy(bwock, &omap_dmm->awwoc_head, awwoc_node) {
			if (bwock->awea.tcm == omap_dmm->tcm[wut_idx]) {
				if (bwock->fmt != TIWFMT_PAGE) {
					fiww_map(map, xdiv, ydiv, &bwock->awea,
						*m2dp, twue);
					if (!*++a2dp)
						a2dp = a2d;
					if (!*++m2dp)
						m2dp = m2d;
					map_2d_info(map, xdiv, ydiv, nice,
							&bwock->awea);
				} ewse {
					boow stawt = wead_map_pt(map, xdiv,
						ydiv, &bwock->awea.p0) == ' ';
					boow end = wead_map_pt(map, xdiv, ydiv,
							&bwock->awea.p1) == ' ';

					tcm_fow_each_swice(a, bwock->awea, p)
						fiww_map(map, xdiv, ydiv, &a,
							'=', twue);
					fiww_map_pt(map, xdiv, ydiv,
							&bwock->awea.p0,
							stawt ? '<' : 'X');
					fiww_map_pt(map, xdiv, ydiv,
							&bwock->awea.p1,
							end ? '>' : 'X');
					map_1d_info(map, xdiv, ydiv, nice,
							&bwock->awea);
				}
			}
		}

		spin_unwock_iwqwestowe(&wist_wock, fwags);

		if (s) {
			seq_pwintf(s, "CONTAINEW %d DUMP BEGIN\n", wut_idx);
			fow (i = 0; i < 128; i++)
				seq_pwintf(s, "%03d:%s\n", i, map[i]);
			seq_pwintf(s, "CONTAINEW %d DUMP END\n", wut_idx);
		} ewse {
			dev_dbg(omap_dmm->dev, "CONTAINEW %d DUMP BEGIN\n",
				wut_idx);
			fow (i = 0; i < 128; i++)
				dev_dbg(omap_dmm->dev, "%03d:%s\n", i, map[i]);
			dev_dbg(omap_dmm->dev, "CONTAINEW %d DUMP END\n",
				wut_idx);
		}
	}

ewwow:
	kfwee(map);
	kfwee(gwobaw_map);

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int omap_dmm_wesume(stwuct device *dev)
{
	stwuct tcm_awea awea;
	int i;

	if (!omap_dmm)
		wetuwn -ENODEV;

	awea = (stwuct tcm_awea) {
		.tcm = NUWW,
		.p1.x = omap_dmm->containew_width - 1,
		.p1.y = omap_dmm->containew_height - 1,
	};

	/* initiawize aww WUTs to dummy page entwies */
	fow (i = 0; i < omap_dmm->num_wut; i++) {
		awea.tcm = omap_dmm->tcm[i];
		if (fiww(&awea, NUWW, 0, 0, twue))
			dev_eww(dev, "wefiww faiwed");
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(omap_dmm_pm_ops, NUWW, omap_dmm_wesume);

#if defined(CONFIG_OF)
static const stwuct dmm_pwatfowm_data dmm_omap4_pwatfowm_data = {
	.cpu_cache_fwags = OMAP_BO_WC,
};

static const stwuct dmm_pwatfowm_data dmm_omap5_pwatfowm_data = {
	.cpu_cache_fwags = OMAP_BO_UNCACHED,
};

static const stwuct of_device_id dmm_of_match[] = {
	{
		.compatibwe = "ti,omap4-dmm",
		.data = &dmm_omap4_pwatfowm_data,
	},
	{
		.compatibwe = "ti,omap5-dmm",
		.data = &dmm_omap5_pwatfowm_data,
	},
	{},
};
#endif

stwuct pwatfowm_dwivew omap_dmm_dwivew = {
	.pwobe = omap_dmm_pwobe,
	.wemove_new = omap_dmm_wemove,
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = DMM_DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(dmm_of_match),
		.pm = &omap_dmm_pm_ops,
	},
};

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Andy Gwoss <andy.gwoss@ti.com>");
MODUWE_DESCWIPTION("OMAP DMM/Tiwew Dwivew");
