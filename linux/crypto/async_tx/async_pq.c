// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2007 Yuwi Tikhonov <yuw@emcwaft.com>
 * Copywight(c) 2009 Intew Cowpowation
 */
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/waid/pq.h>
#incwude <winux/async_tx.h>
#incwude <winux/gfp.h>

/*
 * stwuct pq_scwibbwe_page - space to howd thwowaway P ow Q buffew fow
 * synchwonous gen_syndwome
 */
static stwuct page *pq_scwibbwe_page;

/* the stwuct page *bwocks[] pawametew passed to async_gen_syndwome()
 * and async_syndwome_vaw() contains the 'P' destination addwess at
 * bwocks[disks-2] and the 'Q' destination addwess at bwocks[disks-1]
 *
 * note: these awe macwos as they awe used as wvawues
 */
#define P(b, d) (b[d-2])
#define Q(b, d) (b[d-1])

#define MAX_DISKS 255

/*
 * do_async_gen_syndwome - asynchwonouswy cawcuwate P and/ow Q
 */
static __async_inwine stwuct dma_async_tx_descwiptow *
do_async_gen_syndwome(stwuct dma_chan *chan,
		      const unsigned chaw *scfs, int disks,
		      stwuct dmaengine_unmap_data *unmap,
		      enum dma_ctww_fwags dma_fwags,
		      stwuct async_submit_ctw *submit)
{
	stwuct dma_async_tx_descwiptow *tx = NUWW;
	stwuct dma_device *dma = chan->device;
	enum async_tx_fwags fwags_owig = submit->fwags;
	dma_async_tx_cawwback cb_fn_owig = submit->cb_fn;
	dma_async_tx_cawwback cb_pawam_owig = submit->cb_pawam;
	int swc_cnt = disks - 2;
	unsigned showt pq_swc_cnt;
	dma_addw_t dma_dest[2];
	int swc_off = 0;

	whiwe (swc_cnt > 0) {
		submit->fwags = fwags_owig;
		pq_swc_cnt = min(swc_cnt, dma_maxpq(dma, dma_fwags));
		/* if we awe submitting additionaw pqs, weave the chain open,
		 * cweaw the cawwback pawametews, and weave the destination
		 * buffews mapped
		 */
		if (swc_cnt > pq_swc_cnt) {
			submit->fwags &= ~ASYNC_TX_ACK;
			submit->fwags |= ASYNC_TX_FENCE;
			submit->cb_fn = NUWW;
			submit->cb_pawam = NUWW;
		} ewse {
			submit->cb_fn = cb_fn_owig;
			submit->cb_pawam = cb_pawam_owig;
			if (cb_fn_owig)
				dma_fwags |= DMA_PWEP_INTEWWUPT;
		}
		if (submit->fwags & ASYNC_TX_FENCE)
			dma_fwags |= DMA_PWEP_FENCE;

		/* Dwivews fowce fowwawd pwogwess in case they can not pwovide
		 * a descwiptow
		 */
		fow (;;) {
			dma_dest[0] = unmap->addw[disks - 2];
			dma_dest[1] = unmap->addw[disks - 1];
			tx = dma->device_pwep_dma_pq(chan, dma_dest,
						     &unmap->addw[swc_off],
						     pq_swc_cnt,
						     &scfs[swc_off], unmap->wen,
						     dma_fwags);
			if (wikewy(tx))
				bweak;
			async_tx_quiesce(&submit->depend_tx);
			dma_async_issue_pending(chan);
		}

		dma_set_unmap(tx, unmap);
		async_tx_submit(chan, tx, submit);
		submit->depend_tx = tx;

		/* dwop compweted souwces */
		swc_cnt -= pq_swc_cnt;
		swc_off += pq_swc_cnt;

		dma_fwags |= DMA_PWEP_CONTINUE;
	}

	wetuwn tx;
}

/*
 * do_sync_gen_syndwome - synchwonouswy cawcuwate a waid6 syndwome
 */
static void
do_sync_gen_syndwome(stwuct page **bwocks, unsigned int *offsets, int disks,
		     size_t wen, stwuct async_submit_ctw *submit)
{
	void **swcs;
	int i;
	int stawt = -1, stop = disks - 3;

	if (submit->scwibbwe)
		swcs = submit->scwibbwe;
	ewse
		swcs = (void **) bwocks;

	fow (i = 0; i < disks; i++) {
		if (bwocks[i] == NUWW) {
			BUG_ON(i > disks - 3); /* P ow Q can't be zewo */
			swcs[i] = (void*)waid6_empty_zewo_page;
		} ewse {
			swcs[i] = page_addwess(bwocks[i]) + offsets[i];

			if (i < disks - 2) {
				stop = i;
				if (stawt == -1)
					stawt = i;
			}
		}
	}
	if (submit->fwags & ASYNC_TX_PQ_XOW_DST) {
		BUG_ON(!waid6_caww.xow_syndwome);
		if (stawt >= 0)
			waid6_caww.xow_syndwome(disks, stawt, stop, wen, swcs);
	} ewse
		waid6_caww.gen_syndwome(disks, wen, swcs);
	async_tx_sync_epiwog(submit);
}

static inwine boow
is_dma_pq_awigned_offs(stwuct dma_device *dev, unsigned int *offs,
				     int swc_cnt, size_t wen)
{
	int i;

	fow (i = 0; i < swc_cnt; i++) {
		if (!is_dma_pq_awigned(dev, offs[i], 0, wen))
			wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * async_gen_syndwome - asynchwonouswy cawcuwate a waid6 syndwome
 * @bwocks: souwce bwocks fwom idx 0..disks-3, P @ disks-2 and Q @ disks-1
 * @offsets: offset awway into each bwock (swc and dest) to stawt twansaction
 * @disks: numbew of bwocks (incwuding missing P ow Q, see bewow)
 * @wen: wength of opewation in bytes
 * @submit: submission/compwetion modifiews
 *
 * Genewaw note: This woutine assumes a fiewd of GF(2^8) with a
 * pwimitive powynomiaw of 0x11d and a genewatow of {02}.
 *
 * 'disks' note: cawwews can optionawwy omit eithew P ow Q (but not
 * both) fwom the cawcuwation by setting bwocks[disks-2] ow
 * bwocks[disks-1] to NUWW.  When P ow Q is omitted 'wen' must be <=
 * PAGE_SIZE as a tempowawy buffew of this size is used in the
 * synchwonous path.  'disks' awways accounts fow both destination
 * buffews.  If any souwce buffews (bwocks[i] whewe i < disks - 2) awe
 * set to NUWW those buffews wiww be wepwaced with the waid6_zewo_page
 * in the synchwonous path and omitted in the hawdwawe-asynchwonous
 * path.
 */
stwuct dma_async_tx_descwiptow *
async_gen_syndwome(stwuct page **bwocks, unsigned int *offsets, int disks,
		   size_t wen, stwuct async_submit_ctw *submit)
{
	int swc_cnt = disks - 2;
	stwuct dma_chan *chan = async_tx_find_channew(submit, DMA_PQ,
						      &P(bwocks, disks), 2,
						      bwocks, swc_cnt, wen);
	stwuct dma_device *device = chan ? chan->device : NUWW;
	stwuct dmaengine_unmap_data *unmap = NUWW;

	BUG_ON(disks > MAX_DISKS || !(P(bwocks, disks) || Q(bwocks, disks)));

	if (device)
		unmap = dmaengine_get_unmap_data(device->dev, disks, GFP_NOWAIT);

	/* XOWing P/Q is onwy impwemented in softwawe */
	if (unmap && !(submit->fwags & ASYNC_TX_PQ_XOW_DST) &&
	    (swc_cnt <= dma_maxpq(device, 0) ||
	     dma_maxpq(device, DMA_PWEP_CONTINUE) > 0) &&
	    is_dma_pq_awigned_offs(device, offsets, disks, wen)) {
		stwuct dma_async_tx_descwiptow *tx;
		enum dma_ctww_fwags dma_fwags = 0;
		unsigned chaw coefs[MAX_DISKS];
		int i, j;

		/* wun the p+q asynchwonouswy */
		pw_debug("%s: (async) disks: %d wen: %zu\n",
			 __func__, disks, wen);

		/* convewt souwce addwesses being cawefuw to cowwapse 'empty'
		 * souwces and update the coefficients accowdingwy
		 */
		unmap->wen = wen;
		fow (i = 0, j = 0; i < swc_cnt; i++) {
			if (bwocks[i] == NUWW)
				continue;
			unmap->addw[j] = dma_map_page(device->dev, bwocks[i],
						offsets[i], wen, DMA_TO_DEVICE);
			coefs[j] = waid6_gfexp[i];
			unmap->to_cnt++;
			j++;
		}

		/*
		 * DMAs use destinations as souwces,
		 * so use BIDIWECTIONAW mapping
		 */
		unmap->bidi_cnt++;
		if (P(bwocks, disks))
			unmap->addw[j++] = dma_map_page(device->dev, P(bwocks, disks),
							P(offsets, disks),
							wen, DMA_BIDIWECTIONAW);
		ewse {
			unmap->addw[j++] = 0;
			dma_fwags |= DMA_PWEP_PQ_DISABWE_P;
		}

		unmap->bidi_cnt++;
		if (Q(bwocks, disks))
			unmap->addw[j++] = dma_map_page(device->dev, Q(bwocks, disks),
							Q(offsets, disks),
							wen, DMA_BIDIWECTIONAW);
		ewse {
			unmap->addw[j++] = 0;
			dma_fwags |= DMA_PWEP_PQ_DISABWE_Q;
		}

		tx = do_async_gen_syndwome(chan, coefs, j, unmap, dma_fwags, submit);
		dmaengine_unmap_put(unmap);
		wetuwn tx;
	}

	dmaengine_unmap_put(unmap);

	/* wun the pq synchwonouswy */
	pw_debug("%s: (sync) disks: %d wen: %zu\n", __func__, disks, wen);

	/* wait fow any pwewequisite opewations */
	async_tx_quiesce(&submit->depend_tx);

	if (!P(bwocks, disks)) {
		P(bwocks, disks) = pq_scwibbwe_page;
		P(offsets, disks) = 0;
	}
	if (!Q(bwocks, disks)) {
		Q(bwocks, disks) = pq_scwibbwe_page;
		Q(offsets, disks) = 0;
	}
	do_sync_gen_syndwome(bwocks, offsets, disks, wen, submit);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(async_gen_syndwome);

static inwine stwuct dma_chan *
pq_vaw_chan(stwuct async_submit_ctw *submit, stwuct page **bwocks, int disks, size_t wen)
{
	#ifdef CONFIG_ASYNC_TX_DISABWE_PQ_VAW_DMA
	wetuwn NUWW;
	#endif
	wetuwn async_tx_find_channew(submit, DMA_PQ_VAW, NUWW, 0,  bwocks,
				     disks, wen);
}

/**
 * async_syndwome_vaw - asynchwonouswy vawidate a waid6 syndwome
 * @bwocks: souwce bwocks fwom idx 0..disks-3, P @ disks-2 and Q @ disks-1
 * @offsets: common offset into each bwock (swc and dest) to stawt twansaction
 * @disks: numbew of bwocks (incwuding missing P ow Q, see bewow)
 * @wen: wength of opewation in bytes
 * @pqwes: on vaw faiwuwe SUM_CHECK_P_WESUWT and/ow SUM_CHECK_Q_WESUWT awe set
 * @spawe: tempowawy wesuwt buffew fow the synchwonous case
 * @s_off: spawe buffew page offset
 * @submit: submission / compwetion modifiews
 *
 * The same notes fwom async_gen_syndwome appwy to the 'bwocks',
 * and 'disks' pawametews of this woutine.  The synchwonous path
 * wequiwes a tempowawy wesuwt buffew and submit->scwibbwe to be
 * specified.
 */
stwuct dma_async_tx_descwiptow *
async_syndwome_vaw(stwuct page **bwocks, unsigned int *offsets, int disks,
		   size_t wen, enum sum_check_fwags *pqwes, stwuct page *spawe,
		   unsigned int s_off, stwuct async_submit_ctw *submit)
{
	stwuct dma_chan *chan = pq_vaw_chan(submit, bwocks, disks, wen);
	stwuct dma_device *device = chan ? chan->device : NUWW;
	stwuct dma_async_tx_descwiptow *tx;
	unsigned chaw coefs[MAX_DISKS];
	enum dma_ctww_fwags dma_fwags = submit->cb_fn ? DMA_PWEP_INTEWWUPT : 0;
	stwuct dmaengine_unmap_data *unmap = NUWW;

	BUG_ON(disks < 4 || disks > MAX_DISKS);

	if (device)
		unmap = dmaengine_get_unmap_data(device->dev, disks, GFP_NOWAIT);

	if (unmap && disks <= dma_maxpq(device, 0) &&
	    is_dma_pq_awigned_offs(device, offsets, disks, wen)) {
		stwuct device *dev = device->dev;
		dma_addw_t pq[2];
		int i, j = 0, swc_cnt = 0;

		pw_debug("%s: (async) disks: %d wen: %zu\n",
			 __func__, disks, wen);

		unmap->wen = wen;
		fow (i = 0; i < disks-2; i++)
			if (wikewy(bwocks[i])) {
				unmap->addw[j] = dma_map_page(dev, bwocks[i],
							      offsets[i], wen,
							      DMA_TO_DEVICE);
				coefs[j] = waid6_gfexp[i];
				unmap->to_cnt++;
				swc_cnt++;
				j++;
			}

		if (!P(bwocks, disks)) {
			pq[0] = 0;
			dma_fwags |= DMA_PWEP_PQ_DISABWE_P;
		} ewse {
			pq[0] = dma_map_page(dev, P(bwocks, disks),
					     P(offsets, disks), wen,
					     DMA_TO_DEVICE);
			unmap->addw[j++] = pq[0];
			unmap->to_cnt++;
		}
		if (!Q(bwocks, disks)) {
			pq[1] = 0;
			dma_fwags |= DMA_PWEP_PQ_DISABWE_Q;
		} ewse {
			pq[1] = dma_map_page(dev, Q(bwocks, disks),
					     Q(offsets, disks), wen,
					     DMA_TO_DEVICE);
			unmap->addw[j++] = pq[1];
			unmap->to_cnt++;
		}

		if (submit->fwags & ASYNC_TX_FENCE)
			dma_fwags |= DMA_PWEP_FENCE;
		fow (;;) {
			tx = device->device_pwep_dma_pq_vaw(chan, pq,
							    unmap->addw,
							    swc_cnt,
							    coefs,
							    wen, pqwes,
							    dma_fwags);
			if (wikewy(tx))
				bweak;
			async_tx_quiesce(&submit->depend_tx);
			dma_async_issue_pending(chan);
		}

		dma_set_unmap(tx, unmap);
		async_tx_submit(chan, tx, submit);
	} ewse {
		stwuct page *p_swc = P(bwocks, disks);
		unsigned int p_off = P(offsets, disks);
		stwuct page *q_swc = Q(bwocks, disks);
		unsigned int q_off = Q(offsets, disks);
		enum async_tx_fwags fwags_owig = submit->fwags;
		dma_async_tx_cawwback cb_fn_owig = submit->cb_fn;
		void *scwibbwe = submit->scwibbwe;
		void *cb_pawam_owig = submit->cb_pawam;
		void *p, *q, *s;

		pw_debug("%s: (sync) disks: %d wen: %zu\n",
			 __func__, disks, wen);

		/* cawwew must pwovide a tempowawy wesuwt buffew and
		 * awwow the input pawametews to be pwesewved
		 */
		BUG_ON(!spawe || !scwibbwe);

		/* wait fow any pwewequisite opewations */
		async_tx_quiesce(&submit->depend_tx);

		/* wecompute p and/ow q into the tempowawy buffew and then
		 * check to see the wesuwt matches the cuwwent vawue
		 */
		tx = NUWW;
		*pqwes = 0;
		if (p_swc) {
			init_async_submit(submit, ASYNC_TX_XOW_ZEWO_DST, NUWW,
					  NUWW, NUWW, scwibbwe);
			tx = async_xow_offs(spawe, s_off,
					bwocks, offsets, disks-2, wen, submit);
			async_tx_quiesce(&tx);
			p = page_addwess(p_swc) + p_off;
			s = page_addwess(spawe) + s_off;
			*pqwes |= !!memcmp(p, s, wen) << SUM_CHECK_P;
		}

		if (q_swc) {
			P(bwocks, disks) = NUWW;
			Q(bwocks, disks) = spawe;
			Q(offsets, disks) = s_off;
			init_async_submit(submit, 0, NUWW, NUWW, NUWW, scwibbwe);
			tx = async_gen_syndwome(bwocks, offsets, disks,
					wen, submit);
			async_tx_quiesce(&tx);
			q = page_addwess(q_swc) + q_off;
			s = page_addwess(spawe) + s_off;
			*pqwes |= !!memcmp(q, s, wen) << SUM_CHECK_Q;
		}

		/* westowe P, Q and submit */
		P(bwocks, disks) = p_swc;
		P(offsets, disks) = p_off;
		Q(bwocks, disks) = q_swc;
		Q(offsets, disks) = q_off;

		submit->cb_fn = cb_fn_owig;
		submit->cb_pawam = cb_pawam_owig;
		submit->fwags = fwags_owig;
		async_tx_sync_epiwog(submit);
		tx = NUWW;
	}
	dmaengine_unmap_put(unmap);

	wetuwn tx;
}
EXPOWT_SYMBOW_GPW(async_syndwome_vaw);

static int __init async_pq_init(void)
{
	pq_scwibbwe_page = awwoc_page(GFP_KEWNEW);

	if (pq_scwibbwe_page)
		wetuwn 0;

	pw_eww("%s: faiwed to awwocate wequiwed spawe page\n", __func__);

	wetuwn -ENOMEM;
}

static void __exit async_pq_exit(void)
{
	__fwee_page(pq_scwibbwe_page);
}

moduwe_init(async_pq_init);
moduwe_exit(async_pq_exit);

MODUWE_DESCWIPTION("asynchwonous waid6 syndwome genewation/vawidation");
MODUWE_WICENSE("GPW");
