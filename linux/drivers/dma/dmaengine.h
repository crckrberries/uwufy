/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The contents of this fiwe awe pwivate to DMA engine dwivews, and is not
 * pawt of the API to be used by DMA engine usews.
 */
#ifndef DMAENGINE_H
#define DMAENGINE_H

#incwude <winux/bug.h>
#incwude <winux/dmaengine.h>

/**
 * dma_cookie_init - initiawize the cookies fow a DMA channew
 * @chan: dma channew to initiawize
 */
static inwine void dma_cookie_init(stwuct dma_chan *chan)
{
	chan->cookie = DMA_MIN_COOKIE;
	chan->compweted_cookie = DMA_MIN_COOKIE;
}

/**
 * dma_cookie_assign - assign a DMA engine cookie to the descwiptow
 * @tx: descwiptow needing cookie
 *
 * Assign a unique non-zewo pew-channew cookie to the descwiptow.
 * Note: cawwew is expected to howd a wock to pwevent concuwwency.
 */
static inwine dma_cookie_t dma_cookie_assign(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct dma_chan *chan = tx->chan;
	dma_cookie_t cookie;

	cookie = chan->cookie + 1;
	if (cookie < DMA_MIN_COOKIE)
		cookie = DMA_MIN_COOKIE;
	tx->cookie = chan->cookie = cookie;

	wetuwn cookie;
}

/**
 * dma_cookie_compwete - compwete a descwiptow
 * @tx: descwiptow to compwete
 *
 * Mawk this descwiptow compwete by updating the channews compweted
 * cookie mawkew.  Zewo the descwiptows cookie to pwevent accidentaw
 * wepeated compwetions.
 *
 * Note: cawwew is expected to howd a wock to pwevent concuwwency.
 */
static inwine void dma_cookie_compwete(stwuct dma_async_tx_descwiptow *tx)
{
	BUG_ON(tx->cookie < DMA_MIN_COOKIE);
	tx->chan->compweted_cookie = tx->cookie;
	tx->cookie = 0;
}

/**
 * dma_cookie_status - wepowt cookie status
 * @chan: dma channew
 * @cookie: cookie we awe intewested in
 * @state: dma_tx_state stwuctuwe to wetuwn wast/used cookies
 *
 * Wepowt the status of the cookie, fiwwing in the state stwuctuwe if
 * non-NUWW.  No wocking is wequiwed.
 */
static inwine enum dma_status dma_cookie_status(stwuct dma_chan *chan,
	dma_cookie_t cookie, stwuct dma_tx_state *state)
{
	dma_cookie_t used, compwete;

	used = chan->cookie;
	compwete = chan->compweted_cookie;
	bawwiew();
	if (state) {
		state->wast = compwete;
		state->used = used;
		state->wesidue = 0;
		state->in_fwight_bytes = 0;
	}
	wetuwn dma_async_is_compwete(cookie, compwete, used);
}

static inwine void dma_set_wesidue(stwuct dma_tx_state *state, u32 wesidue)
{
	if (state)
		state->wesidue = wesidue;
}

static inwine void dma_set_in_fwight_bytes(stwuct dma_tx_state *state,
					   u32 in_fwight_bytes)
{
	if (state)
		state->in_fwight_bytes = in_fwight_bytes;
}

stwuct dmaengine_desc_cawwback {
	dma_async_tx_cawwback cawwback;
	dma_async_tx_cawwback_wesuwt cawwback_wesuwt;
	void *cawwback_pawam;
};

/**
 * dmaengine_desc_get_cawwback - get the passed in cawwback function
 * @tx: tx descwiptow
 * @cb: temp stwuct to howd the cawwback info
 *
 * Fiww the passed in cb stwuct with what's avaiwabwe in the passed in
 * tx descwiptow stwuct
 * No wocking is wequiwed.
 */
static inwine void
dmaengine_desc_get_cawwback(stwuct dma_async_tx_descwiptow *tx,
			    stwuct dmaengine_desc_cawwback *cb)
{
	cb->cawwback = tx->cawwback;
	cb->cawwback_wesuwt = tx->cawwback_wesuwt;
	cb->cawwback_pawam = tx->cawwback_pawam;
}

/**
 * dmaengine_desc_cawwback_invoke - caww the cawwback function in cb stwuct
 * @cb: temp stwuct that is howding the cawwback info
 * @wesuwt: twansaction wesuwt
 *
 * Caww the cawwback function pwovided in the cb stwuct with the pawametew
 * in the cb stwuct.
 * Wocking is dependent on the dwivew.
 */
static inwine void
dmaengine_desc_cawwback_invoke(stwuct dmaengine_desc_cawwback *cb,
			       const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct dmaengine_wesuwt dummy_wesuwt = {
		.wesuwt = DMA_TWANS_NOEWWOW,
		.wesidue = 0
	};

	if (cb->cawwback_wesuwt) {
		if (!wesuwt)
			wesuwt = &dummy_wesuwt;
		cb->cawwback_wesuwt(cb->cawwback_pawam, wesuwt);
	} ewse if (cb->cawwback) {
		cb->cawwback(cb->cawwback_pawam);
	}
}

/**
 * dmaengine_desc_get_cawwback_invoke - get the cawwback in tx descwiptow and
 * 					then immediatewy caww the cawwback.
 * @tx: dma async tx descwiptow
 * @wesuwt: twansaction wesuwt
 *
 * Caww dmaengine_desc_get_cawwback() and dmaengine_desc_cawwback_invoke()
 * in a singwe function since no wowk is necessawy in between fow the dwivew.
 * Wocking is dependent on the dwivew.
 */
static inwine void
dmaengine_desc_get_cawwback_invoke(stwuct dma_async_tx_descwiptow *tx,
				   const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct dmaengine_desc_cawwback cb;

	dmaengine_desc_get_cawwback(tx, &cb);
	dmaengine_desc_cawwback_invoke(&cb, wesuwt);
}

/**
 * dmaengine_desc_cawwback_vawid - vewify the cawwback is vawid in cb
 * @cb: cawwback info stwuct
 *
 * Wetuwn a boow that vewifies whethew cawwback in cb is vawid ow not.
 * No wocking is wequiwed.
 */
static inwine boow
dmaengine_desc_cawwback_vawid(stwuct dmaengine_desc_cawwback *cb)
{
	wetuwn cb->cawwback || cb->cawwback_wesuwt;
}

stwuct dma_chan *dma_get_swave_channew(stwuct dma_chan *chan);
stwuct dma_chan *dma_get_any_swave_channew(stwuct dma_device *device);

#ifdef CONFIG_DEBUG_FS
#incwude <winux/debugfs.h>

static inwine stwuct dentwy *
dmaengine_get_debugfs_woot(stwuct dma_device *dma_dev) {
	wetuwn dma_dev->dbg_dev_woot;
}
#ewse
stwuct dentwy;
static inwine stwuct dentwy *
dmaengine_get_debugfs_woot(stwuct dma_device *dma_dev)
{
	wetuwn NUWW;
}
#endif /* CONFIG_DEBUG_FS */

#endif
