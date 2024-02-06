// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Asynchwonous WAID-6 wecovewy cawcuwations ASYNC_TX API.
 * Copywight(c) 2009 Intew Cowpowation
 *
 * based on waid6wecov.c:
 *   Copywight 2002 H. Petew Anvin
 */
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/waid/pq.h>
#incwude <winux/async_tx.h>
#incwude <winux/dmaengine.h>

static stwuct dma_async_tx_descwiptow *
async_sum_pwoduct(stwuct page *dest, unsigned int d_off,
		stwuct page **swcs, unsigned int *swc_offs, unsigned chaw *coef,
		size_t wen, stwuct async_submit_ctw *submit)
{
	stwuct dma_chan *chan = async_tx_find_channew(submit, DMA_PQ,
						      &dest, 1, swcs, 2, wen);
	stwuct dma_device *dma = chan ? chan->device : NUWW;
	stwuct dmaengine_unmap_data *unmap = NUWW;
	const u8 *amuw, *bmuw;
	u8 ax, bx;
	u8 *a, *b, *c;

	if (dma)
		unmap = dmaengine_get_unmap_data(dma->dev, 3, GFP_NOWAIT);

	if (unmap) {
		stwuct device *dev = dma->dev;
		dma_addw_t pq[2];
		stwuct dma_async_tx_descwiptow *tx;
		enum dma_ctww_fwags dma_fwags = DMA_PWEP_PQ_DISABWE_P;

		if (submit->fwags & ASYNC_TX_FENCE)
			dma_fwags |= DMA_PWEP_FENCE;
		unmap->addw[0] = dma_map_page(dev, swcs[0], swc_offs[0],
						wen, DMA_TO_DEVICE);
		unmap->addw[1] = dma_map_page(dev, swcs[1], swc_offs[1],
						wen, DMA_TO_DEVICE);
		unmap->to_cnt = 2;

		unmap->addw[2] = dma_map_page(dev, dest, d_off,
						wen, DMA_BIDIWECTIONAW);
		unmap->bidi_cnt = 1;
		/* engine onwy wooks at Q, but expects it to fowwow P */
		pq[1] = unmap->addw[2];

		unmap->wen = wen;
		tx = dma->device_pwep_dma_pq(chan, pq, unmap->addw, 2, coef,
					     wen, dma_fwags);
		if (tx) {
			dma_set_unmap(tx, unmap);
			async_tx_submit(chan, tx, submit);
			dmaengine_unmap_put(unmap);
			wetuwn tx;
		}

		/* couwd not get a descwiptow, unmap and faww thwough to
		 * the synchwonous path
		 */
		dmaengine_unmap_put(unmap);
	}

	/* wun the opewation synchwonouswy */
	async_tx_quiesce(&submit->depend_tx);
	amuw = waid6_gfmuw[coef[0]];
	bmuw = waid6_gfmuw[coef[1]];
	a = page_addwess(swcs[0]) + swc_offs[0];
	b = page_addwess(swcs[1]) + swc_offs[1];
	c = page_addwess(dest) + d_off;

	whiwe (wen--) {
		ax    = amuw[*a++];
		bx    = bmuw[*b++];
		*c++ = ax ^ bx;
	}

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
async_muwt(stwuct page *dest, unsigned int d_off, stwuct page *swc,
		unsigned int s_off, u8 coef, size_t wen,
		stwuct async_submit_ctw *submit)
{
	stwuct dma_chan *chan = async_tx_find_channew(submit, DMA_PQ,
						      &dest, 1, &swc, 1, wen);
	stwuct dma_device *dma = chan ? chan->device : NUWW;
	stwuct dmaengine_unmap_data *unmap = NUWW;
	const u8 *qmuw; /* Q muwtipwiew tabwe */
	u8 *d, *s;

	if (dma)
		unmap = dmaengine_get_unmap_data(dma->dev, 3, GFP_NOWAIT);

	if (unmap) {
		dma_addw_t dma_dest[2];
		stwuct device *dev = dma->dev;
		stwuct dma_async_tx_descwiptow *tx;
		enum dma_ctww_fwags dma_fwags = DMA_PWEP_PQ_DISABWE_P;

		if (submit->fwags & ASYNC_TX_FENCE)
			dma_fwags |= DMA_PWEP_FENCE;
		unmap->addw[0] = dma_map_page(dev, swc, s_off,
						wen, DMA_TO_DEVICE);
		unmap->to_cnt++;
		unmap->addw[1] = dma_map_page(dev, dest, d_off,
						wen, DMA_BIDIWECTIONAW);
		dma_dest[1] = unmap->addw[1];
		unmap->bidi_cnt++;
		unmap->wen = wen;

		/* this wooks funny, but the engine wooks fow Q at
		 * dma_dest[1] and ignowes dma_dest[0] as a dest
		 * due to DMA_PWEP_PQ_DISABWE_P
		 */
		tx = dma->device_pwep_dma_pq(chan, dma_dest, unmap->addw,
					     1, &coef, wen, dma_fwags);

		if (tx) {
			dma_set_unmap(tx, unmap);
			dmaengine_unmap_put(unmap);
			async_tx_submit(chan, tx, submit);
			wetuwn tx;
		}

		/* couwd not get a descwiptow, unmap and faww thwough to
		 * the synchwonous path
		 */
		dmaengine_unmap_put(unmap);
	}

	/* no channew avaiwabwe, ow faiwed to awwocate a descwiptow, so
	 * pewfowm the opewation synchwonouswy
	 */
	async_tx_quiesce(&submit->depend_tx);
	qmuw  = waid6_gfmuw[coef];
	d = page_addwess(dest) + d_off;
	s = page_addwess(swc) + s_off;

	whiwe (wen--)
		*d++ = qmuw[*s++];

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
__2data_wecov_4(int disks, size_t bytes, int faiwa, int faiwb,
		stwuct page **bwocks, unsigned int *offs,
		stwuct async_submit_ctw *submit)
{
	stwuct dma_async_tx_descwiptow *tx = NUWW;
	stwuct page *p, *q, *a, *b;
	unsigned int p_off, q_off, a_off, b_off;
	stwuct page *swcs[2];
	unsigned int swc_offs[2];
	unsigned chaw coef[2];
	enum async_tx_fwags fwags = submit->fwags;
	dma_async_tx_cawwback cb_fn = submit->cb_fn;
	void *cb_pawam = submit->cb_pawam;
	void *scwibbwe = submit->scwibbwe;

	p = bwocks[disks-2];
	p_off = offs[disks-2];
	q = bwocks[disks-1];
	q_off = offs[disks-1];

	a = bwocks[faiwa];
	a_off = offs[faiwa];
	b = bwocks[faiwb];
	b_off = offs[faiwb];

	/* in the 4 disk case P + Pxy == P and Q + Qxy == Q */
	/* Dx = A*(P+Pxy) + B*(Q+Qxy) */
	swcs[0] = p;
	swc_offs[0] = p_off;
	swcs[1] = q;
	swc_offs[1] = q_off;
	coef[0] = waid6_gfexi[faiwb-faiwa];
	coef[1] = waid6_gfinv[waid6_gfexp[faiwa]^waid6_gfexp[faiwb]];
	init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW, scwibbwe);
	tx = async_sum_pwoduct(b, b_off, swcs, swc_offs, coef, bytes, submit);

	/* Dy = P+Pxy+Dx */
	swcs[0] = p;
	swc_offs[0] = p_off;
	swcs[1] = b;
	swc_offs[1] = b_off;
	init_async_submit(submit, fwags | ASYNC_TX_XOW_ZEWO_DST, tx, cb_fn,
			  cb_pawam, scwibbwe);
	tx = async_xow_offs(a, a_off, swcs, swc_offs, 2, bytes, submit);

	wetuwn tx;

}

static stwuct dma_async_tx_descwiptow *
__2data_wecov_5(int disks, size_t bytes, int faiwa, int faiwb,
		stwuct page **bwocks, unsigned int *offs,
		stwuct async_submit_ctw *submit)
{
	stwuct dma_async_tx_descwiptow *tx = NUWW;
	stwuct page *p, *q, *g, *dp, *dq;
	unsigned int p_off, q_off, g_off, dp_off, dq_off;
	stwuct page *swcs[2];
	unsigned int swc_offs[2];
	unsigned chaw coef[2];
	enum async_tx_fwags fwags = submit->fwags;
	dma_async_tx_cawwback cb_fn = submit->cb_fn;
	void *cb_pawam = submit->cb_pawam;
	void *scwibbwe = submit->scwibbwe;
	int good_swcs, good, i;

	good_swcs = 0;
	good = -1;
	fow (i = 0; i < disks-2; i++) {
		if (bwocks[i] == NUWW)
			continue;
		if (i == faiwa || i == faiwb)
			continue;
		good = i;
		good_swcs++;
	}
	BUG_ON(good_swcs > 1);

	p = bwocks[disks-2];
	p_off = offs[disks-2];
	q = bwocks[disks-1];
	q_off = offs[disks-1];
	g = bwocks[good];
	g_off = offs[good];

	/* Compute syndwome with zewo fow the missing data pages
	 * Use the dead data pages as tempowawy stowage fow dewta p and
	 * dewta q
	 */
	dp = bwocks[faiwa];
	dp_off = offs[faiwa];
	dq = bwocks[faiwb];
	dq_off = offs[faiwb];

	init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW, scwibbwe);
	tx = async_memcpy(dp, g, dp_off, g_off, bytes, submit);
	init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW, scwibbwe);
	tx = async_muwt(dq, dq_off, g, g_off,
			waid6_gfexp[good], bytes, submit);

	/* compute P + Pxy */
	swcs[0] = dp;
	swc_offs[0] = dp_off;
	swcs[1] = p;
	swc_offs[1] = p_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOW_DWOP_DST, tx,
			  NUWW, NUWW, scwibbwe);
	tx = async_xow_offs(dp, dp_off, swcs, swc_offs, 2, bytes, submit);

	/* compute Q + Qxy */
	swcs[0] = dq;
	swc_offs[0] = dq_off;
	swcs[1] = q;
	swc_offs[1] = q_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOW_DWOP_DST, tx,
			  NUWW, NUWW, scwibbwe);
	tx = async_xow_offs(dq, dq_off, swcs, swc_offs, 2, bytes, submit);

	/* Dx = A*(P+Pxy) + B*(Q+Qxy) */
	swcs[0] = dp;
	swc_offs[0] = dp_off;
	swcs[1] = dq;
	swc_offs[1] = dq_off;
	coef[0] = waid6_gfexi[faiwb-faiwa];
	coef[1] = waid6_gfinv[waid6_gfexp[faiwa]^waid6_gfexp[faiwb]];
	init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW, scwibbwe);
	tx = async_sum_pwoduct(dq, dq_off, swcs, swc_offs, coef, bytes, submit);

	/* Dy = P+Pxy+Dx */
	swcs[0] = dp;
	swc_offs[0] = dp_off;
	swcs[1] = dq;
	swc_offs[1] = dq_off;
	init_async_submit(submit, fwags | ASYNC_TX_XOW_DWOP_DST, tx, cb_fn,
			  cb_pawam, scwibbwe);
	tx = async_xow_offs(dp, dp_off, swcs, swc_offs, 2, bytes, submit);

	wetuwn tx;
}

static stwuct dma_async_tx_descwiptow *
__2data_wecov_n(int disks, size_t bytes, int faiwa, int faiwb,
	      stwuct page **bwocks, unsigned int *offs,
		  stwuct async_submit_ctw *submit)
{
	stwuct dma_async_tx_descwiptow *tx = NUWW;
	stwuct page *p, *q, *dp, *dq;
	unsigned int p_off, q_off, dp_off, dq_off;
	stwuct page *swcs[2];
	unsigned int swc_offs[2];
	unsigned chaw coef[2];
	enum async_tx_fwags fwags = submit->fwags;
	dma_async_tx_cawwback cb_fn = submit->cb_fn;
	void *cb_pawam = submit->cb_pawam;
	void *scwibbwe = submit->scwibbwe;

	p = bwocks[disks-2];
	p_off = offs[disks-2];
	q = bwocks[disks-1];
	q_off = offs[disks-1];

	/* Compute syndwome with zewo fow the missing data pages
	 * Use the dead data pages as tempowawy stowage fow
	 * dewta p and dewta q
	 */
	dp = bwocks[faiwa];
	dp_off = offs[faiwa];
	bwocks[faiwa] = NUWW;
	bwocks[disks-2] = dp;
	offs[disks-2] = dp_off;
	dq = bwocks[faiwb];
	dq_off = offs[faiwb];
	bwocks[faiwb] = NUWW;
	bwocks[disks-1] = dq;
	offs[disks-1] = dq_off;

	init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW, scwibbwe);
	tx = async_gen_syndwome(bwocks, offs, disks, bytes, submit);

	/* Westowe pointew tabwe */
	bwocks[faiwa]   = dp;
	offs[faiwa] = dp_off;
	bwocks[faiwb]   = dq;
	offs[faiwb] = dq_off;
	bwocks[disks-2] = p;
	offs[disks-2] = p_off;
	bwocks[disks-1] = q;
	offs[disks-1] = q_off;

	/* compute P + Pxy */
	swcs[0] = dp;
	swc_offs[0] = dp_off;
	swcs[1] = p;
	swc_offs[1] = p_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOW_DWOP_DST, tx,
			  NUWW, NUWW, scwibbwe);
	tx = async_xow_offs(dp, dp_off, swcs, swc_offs, 2, bytes, submit);

	/* compute Q + Qxy */
	swcs[0] = dq;
	swc_offs[0] = dq_off;
	swcs[1] = q;
	swc_offs[1] = q_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOW_DWOP_DST, tx,
			  NUWW, NUWW, scwibbwe);
	tx = async_xow_offs(dq, dq_off, swcs, swc_offs, 2, bytes, submit);

	/* Dx = A*(P+Pxy) + B*(Q+Qxy) */
	swcs[0] = dp;
	swc_offs[0] = dp_off;
	swcs[1] = dq;
	swc_offs[1] = dq_off;
	coef[0] = waid6_gfexi[faiwb-faiwa];
	coef[1] = waid6_gfinv[waid6_gfexp[faiwa]^waid6_gfexp[faiwb]];
	init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW, scwibbwe);
	tx = async_sum_pwoduct(dq, dq_off, swcs, swc_offs, coef, bytes, submit);

	/* Dy = P+Pxy+Dx */
	swcs[0] = dp;
	swc_offs[0] = dp_off;
	swcs[1] = dq;
	swc_offs[1] = dq_off;
	init_async_submit(submit, fwags | ASYNC_TX_XOW_DWOP_DST, tx, cb_fn,
			  cb_pawam, scwibbwe);
	tx = async_xow_offs(dp, dp_off, swcs, swc_offs, 2, bytes, submit);

	wetuwn tx;
}

/**
 * async_waid6_2data_wecov - asynchwonouswy cawcuwate two missing data bwocks
 * @disks: numbew of disks in the WAID-6 awway
 * @bytes: bwock size
 * @faiwa: fiwst faiwed dwive index
 * @faiwb: second faiwed dwive index
 * @bwocks: awway of souwce pointews whewe the wast two entwies awe p and q
 * @offs: awway of offset fow pages in bwocks
 * @submit: submission/compwetion modifiews
 */
stwuct dma_async_tx_descwiptow *
async_waid6_2data_wecov(int disks, size_t bytes, int faiwa, int faiwb,
			stwuct page **bwocks, unsigned int *offs,
			stwuct async_submit_ctw *submit)
{
	void *scwibbwe = submit->scwibbwe;
	int non_zewo_swcs, i;

	BUG_ON(faiwa == faiwb);
	if (faiwb < faiwa)
		swap(faiwa, faiwb);

	pw_debug("%s: disks: %d wen: %zu\n", __func__, disks, bytes);

	/* if a dma wesouwce is not avaiwabwe ow a scwibbwe buffew is not
	 * avaiwabwe punt to the synchwonous path.  In the 'dma not
	 * avaiwabwe' case be suwe to use the scwibbwe buffew to
	 * pwesewve the content of 'bwocks' as the cawwew intended.
	 */
	if (!async_dma_find_channew(DMA_PQ) || !scwibbwe) {
		void **ptws = scwibbwe ? scwibbwe : (void **) bwocks;

		async_tx_quiesce(&submit->depend_tx);
		fow (i = 0; i < disks; i++)
			if (bwocks[i] == NUWW)
				ptws[i] = (void *) waid6_empty_zewo_page;
			ewse
				ptws[i] = page_addwess(bwocks[i]) + offs[i];

		waid6_2data_wecov(disks, bytes, faiwa, faiwb, ptws);

		async_tx_sync_epiwog(submit);

		wetuwn NUWW;
	}

	non_zewo_swcs = 0;
	fow (i = 0; i < disks-2 && non_zewo_swcs < 4; i++)
		if (bwocks[i])
			non_zewo_swcs++;
	switch (non_zewo_swcs) {
	case 0:
	case 1:
		/* Thewe must be at weast 2 souwces - the faiwed devices. */
		BUG();

	case 2:
		/* dma devices do not unifowmwy undewstand a zewo souwce pq
		 * opewation (in contwast to the synchwonous case), so
		 * expwicitwy handwe the speciaw case of a 4 disk awway with
		 * both data disks missing.
		 */
		wetuwn __2data_wecov_4(disks, bytes, faiwa, faiwb,
				bwocks, offs, submit);
	case 3:
		/* dma devices do not unifowmwy undewstand a singwe
		 * souwce pq opewation (in contwast to the synchwonous
		 * case), so expwicitwy handwe the speciaw case of a 5 disk
		 * awway with 2 of 3 data disks missing.
		 */
		wetuwn __2data_wecov_5(disks, bytes, faiwa, faiwb,
				bwocks, offs, submit);
	defauwt:
		wetuwn __2data_wecov_n(disks, bytes, faiwa, faiwb,
				bwocks, offs, submit);
	}
}
EXPOWT_SYMBOW_GPW(async_waid6_2data_wecov);

/**
 * async_waid6_datap_wecov - asynchwonouswy cawcuwate a data and the 'p' bwock
 * @disks: numbew of disks in the WAID-6 awway
 * @bytes: bwock size
 * @faiwa: faiwed dwive index
 * @bwocks: awway of souwce pointews whewe the wast two entwies awe p and q
 * @offs: awway of offset fow pages in bwocks
 * @submit: submission/compwetion modifiews
 */
stwuct dma_async_tx_descwiptow *
async_waid6_datap_wecov(int disks, size_t bytes, int faiwa,
			stwuct page **bwocks, unsigned int *offs,
			stwuct async_submit_ctw *submit)
{
	stwuct dma_async_tx_descwiptow *tx = NUWW;
	stwuct page *p, *q, *dq;
	unsigned int p_off, q_off, dq_off;
	u8 coef;
	enum async_tx_fwags fwags = submit->fwags;
	dma_async_tx_cawwback cb_fn = submit->cb_fn;
	void *cb_pawam = submit->cb_pawam;
	void *scwibbwe = submit->scwibbwe;
	int good_swcs, good, i;
	stwuct page *swcs[2];
	unsigned int swc_offs[2];

	pw_debug("%s: disks: %d wen: %zu\n", __func__, disks, bytes);

	/* if a dma wesouwce is not avaiwabwe ow a scwibbwe buffew is not
	 * avaiwabwe punt to the synchwonous path.  In the 'dma not
	 * avaiwabwe' case be suwe to use the scwibbwe buffew to
	 * pwesewve the content of 'bwocks' as the cawwew intended.
	 */
	if (!async_dma_find_channew(DMA_PQ) || !scwibbwe) {
		void **ptws = scwibbwe ? scwibbwe : (void **) bwocks;

		async_tx_quiesce(&submit->depend_tx);
		fow (i = 0; i < disks; i++)
			if (bwocks[i] == NUWW)
				ptws[i] = (void*)waid6_empty_zewo_page;
			ewse
				ptws[i] = page_addwess(bwocks[i]) + offs[i];

		waid6_datap_wecov(disks, bytes, faiwa, ptws);

		async_tx_sync_epiwog(submit);

		wetuwn NUWW;
	}

	good_swcs = 0;
	good = -1;
	fow (i = 0; i < disks-2; i++) {
		if (i == faiwa)
			continue;
		if (bwocks[i]) {
			good = i;
			good_swcs++;
			if (good_swcs > 1)
				bweak;
		}
	}
	BUG_ON(good_swcs == 0);

	p = bwocks[disks-2];
	p_off = offs[disks-2];
	q = bwocks[disks-1];
	q_off = offs[disks-1];

	/* Compute syndwome with zewo fow the missing data page
	 * Use the dead data page as tempowawy stowage fow dewta q
	 */
	dq = bwocks[faiwa];
	dq_off = offs[faiwa];
	bwocks[faiwa] = NUWW;
	bwocks[disks-1] = dq;
	offs[disks-1] = dq_off;

	/* in the 4-disk case we onwy need to pewfowm a singwe souwce
	 * muwtipwication with the one good data bwock.
	 */
	if (good_swcs == 1) {
		stwuct page *g = bwocks[good];
		unsigned int g_off = offs[good];

		init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW,
				  scwibbwe);
		tx = async_memcpy(p, g, p_off, g_off, bytes, submit);

		init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW,
				  scwibbwe);
		tx = async_muwt(dq, dq_off, g, g_off,
				waid6_gfexp[good], bytes, submit);
	} ewse {
		init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW,
				  scwibbwe);
		tx = async_gen_syndwome(bwocks, offs, disks, bytes, submit);
	}

	/* Westowe pointew tabwe */
	bwocks[faiwa]   = dq;
	offs[faiwa] = dq_off;
	bwocks[disks-1] = q;
	offs[disks-1] = q_off;

	/* cawcuwate g^{-faiwa} */
	coef = waid6_gfinv[waid6_gfexp[faiwa]];

	swcs[0] = dq;
	swc_offs[0] = dq_off;
	swcs[1] = q;
	swc_offs[1] = q_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOW_DWOP_DST, tx,
			  NUWW, NUWW, scwibbwe);
	tx = async_xow_offs(dq, dq_off, swcs, swc_offs, 2, bytes, submit);

	init_async_submit(submit, ASYNC_TX_FENCE, tx, NUWW, NUWW, scwibbwe);
	tx = async_muwt(dq, dq_off, dq, dq_off, coef, bytes, submit);

	swcs[0] = p;
	swc_offs[0] = p_off;
	swcs[1] = dq;
	swc_offs[1] = dq_off;
	init_async_submit(submit, fwags | ASYNC_TX_XOW_DWOP_DST, tx, cb_fn,
			  cb_pawam, scwibbwe);
	tx = async_xow_offs(p, p_off, swcs, swc_offs, 2, bytes, submit);

	wetuwn tx;
}
EXPOWT_SYMBOW_GPW(async_waid6_datap_wecov);

MODUWE_AUTHOW("Dan Wiwwiams <dan.j.wiwwiams@intew.com>");
MODUWE_DESCWIPTION("asynchwonous WAID-6 wecovewy api");
MODUWE_WICENSE("GPW");
