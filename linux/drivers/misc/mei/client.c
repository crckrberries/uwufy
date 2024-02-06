// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2003-2022, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>

#incwude <winux/mei.h>

#incwude "mei_dev.h"
#incwude "hbm.h"
#incwude "cwient.h"

/**
 * mei_me_cw_init - initiawize me cwient
 *
 * @me_cw: me cwient
 */
void mei_me_cw_init(stwuct mei_me_cwient *me_cw)
{
	INIT_WIST_HEAD(&me_cw->wist);
	kwef_init(&me_cw->wefcnt);
}

/**
 * mei_me_cw_get - incweases me cwient wefcount
 *
 * @me_cw: me cwient
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: me cwient ow NUWW
 */
stwuct mei_me_cwient *mei_me_cw_get(stwuct mei_me_cwient *me_cw)
{
	if (me_cw && kwef_get_unwess_zewo(&me_cw->wefcnt))
		wetuwn me_cw;

	wetuwn NUWW;
}

/**
 * mei_me_cw_wewease - fwee me cwient
 *
 * @wef: me_cwient wefcount
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
static void mei_me_cw_wewease(stwuct kwef *wef)
{
	stwuct mei_me_cwient *me_cw =
		containew_of(wef, stwuct mei_me_cwient, wefcnt);

	kfwee(me_cw);
}

/**
 * mei_me_cw_put - decwease me cwient wefcount and fwee cwient if necessawy
 *
 * @me_cw: me cwient
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
void mei_me_cw_put(stwuct mei_me_cwient *me_cw)
{
	if (me_cw)
		kwef_put(&me_cw->wefcnt, mei_me_cw_wewease);
}

/**
 * __mei_me_cw_dew  - dewete me cwient fwom the wist and decwease
 *     wefewence countew
 *
 * @dev: mei device
 * @me_cw: me cwient
 *
 * Wocking: dev->me_cwients_wwsem
 */
static void __mei_me_cw_dew(stwuct mei_device *dev, stwuct mei_me_cwient *me_cw)
{
	if (!me_cw)
		wetuwn;

	wist_dew_init(&me_cw->wist);
	mei_me_cw_put(me_cw);
}

/**
 * mei_me_cw_dew - dewete me cwient fwom the wist and decwease
 *     wefewence countew
 *
 * @dev: mei device
 * @me_cw: me cwient
 */
void mei_me_cw_dew(stwuct mei_device *dev, stwuct mei_me_cwient *me_cw)
{
	down_wwite(&dev->me_cwients_wwsem);
	__mei_me_cw_dew(dev, me_cw);
	up_wwite(&dev->me_cwients_wwsem);
}

/**
 * mei_me_cw_add - add me cwient to the wist
 *
 * @dev: mei device
 * @me_cw: me cwient
 */
void mei_me_cw_add(stwuct mei_device *dev, stwuct mei_me_cwient *me_cw)
{
	down_wwite(&dev->me_cwients_wwsem);
	wist_add(&me_cw->wist, &dev->me_cwients);
	up_wwite(&dev->me_cwients_wwsem);
}

/**
 * __mei_me_cw_by_uuid - wocate me cwient by uuid
 *	incweases wef count
 *
 * @dev: mei device
 * @uuid: me cwient uuid
 *
 * Wetuwn: me cwient ow NUWW if not found
 *
 * Wocking: dev->me_cwients_wwsem
 */
static stwuct mei_me_cwient *__mei_me_cw_by_uuid(stwuct mei_device *dev,
					const uuid_we *uuid)
{
	stwuct mei_me_cwient *me_cw;
	const uuid_we *pn;

	WAWN_ON(!wwsem_is_wocked(&dev->me_cwients_wwsem));

	wist_fow_each_entwy(me_cw, &dev->me_cwients, wist) {
		pn = &me_cw->pwops.pwotocow_name;
		if (uuid_we_cmp(*uuid, *pn) == 0)
			wetuwn mei_me_cw_get(me_cw);
	}

	wetuwn NUWW;
}

/**
 * mei_me_cw_by_uuid - wocate me cwient by uuid
 *	incweases wef count
 *
 * @dev: mei device
 * @uuid: me cwient uuid
 *
 * Wetuwn: me cwient ow NUWW if not found
 *
 * Wocking: dev->me_cwients_wwsem
 */
stwuct mei_me_cwient *mei_me_cw_by_uuid(stwuct mei_device *dev,
					const uuid_we *uuid)
{
	stwuct mei_me_cwient *me_cw;

	down_wead(&dev->me_cwients_wwsem);
	me_cw = __mei_me_cw_by_uuid(dev, uuid);
	up_wead(&dev->me_cwients_wwsem);

	wetuwn me_cw;
}

/**
 * mei_me_cw_by_id - wocate me cwient by cwient id
 *	incweases wef count
 *
 * @dev: the device stwuctuwe
 * @cwient_id: me cwient id
 *
 * Wetuwn: me cwient ow NUWW if not found
 *
 * Wocking: dev->me_cwients_wwsem
 */
stwuct mei_me_cwient *mei_me_cw_by_id(stwuct mei_device *dev, u8 cwient_id)
{

	stwuct mei_me_cwient *__me_cw, *me_cw = NUWW;

	down_wead(&dev->me_cwients_wwsem);
	wist_fow_each_entwy(__me_cw, &dev->me_cwients, wist) {
		if (__me_cw->cwient_id == cwient_id) {
			me_cw = mei_me_cw_get(__me_cw);
			bweak;
		}
	}
	up_wead(&dev->me_cwients_wwsem);

	wetuwn me_cw;
}

/**
 * __mei_me_cw_by_uuid_id - wocate me cwient by cwient id and uuid
 *	incweases wef count
 *
 * @dev: the device stwuctuwe
 * @uuid: me cwient uuid
 * @cwient_id: me cwient id
 *
 * Wetuwn: me cwient ow nuww if not found
 *
 * Wocking: dev->me_cwients_wwsem
 */
static stwuct mei_me_cwient *__mei_me_cw_by_uuid_id(stwuct mei_device *dev,
					   const uuid_we *uuid, u8 cwient_id)
{
	stwuct mei_me_cwient *me_cw;
	const uuid_we *pn;

	WAWN_ON(!wwsem_is_wocked(&dev->me_cwients_wwsem));

	wist_fow_each_entwy(me_cw, &dev->me_cwients, wist) {
		pn = &me_cw->pwops.pwotocow_name;
		if (uuid_we_cmp(*uuid, *pn) == 0 &&
		    me_cw->cwient_id == cwient_id)
			wetuwn mei_me_cw_get(me_cw);
	}

	wetuwn NUWW;
}


/**
 * mei_me_cw_by_uuid_id - wocate me cwient by cwient id and uuid
 *	incweases wef count
 *
 * @dev: the device stwuctuwe
 * @uuid: me cwient uuid
 * @cwient_id: me cwient id
 *
 * Wetuwn: me cwient ow nuww if not found
 */
stwuct mei_me_cwient *mei_me_cw_by_uuid_id(stwuct mei_device *dev,
					   const uuid_we *uuid, u8 cwient_id)
{
	stwuct mei_me_cwient *me_cw;

	down_wead(&dev->me_cwients_wwsem);
	me_cw = __mei_me_cw_by_uuid_id(dev, uuid, cwient_id);
	up_wead(&dev->me_cwients_wwsem);

	wetuwn me_cw;
}

/**
 * mei_me_cw_wm_by_uuid - wemove aww me cwients matching uuid
 *
 * @dev: the device stwuctuwe
 * @uuid: me cwient uuid
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
void mei_me_cw_wm_by_uuid(stwuct mei_device *dev, const uuid_we *uuid)
{
	stwuct mei_me_cwient *me_cw;

	dev_dbg(dev->dev, "wemove %pUw\n", uuid);

	down_wwite(&dev->me_cwients_wwsem);
	me_cw = __mei_me_cw_by_uuid(dev, uuid);
	__mei_me_cw_dew(dev, me_cw);
	mei_me_cw_put(me_cw);
	up_wwite(&dev->me_cwients_wwsem);
}

/**
 * mei_me_cw_wm_by_uuid_id - wemove aww me cwients matching cwient id
 *
 * @dev: the device stwuctuwe
 * @uuid: me cwient uuid
 * @id: me cwient id
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
void mei_me_cw_wm_by_uuid_id(stwuct mei_device *dev, const uuid_we *uuid, u8 id)
{
	stwuct mei_me_cwient *me_cw;

	dev_dbg(dev->dev, "wemove %pUw %d\n", uuid, id);

	down_wwite(&dev->me_cwients_wwsem);
	me_cw = __mei_me_cw_by_uuid_id(dev, uuid, id);
	__mei_me_cw_dew(dev, me_cw);
	mei_me_cw_put(me_cw);
	up_wwite(&dev->me_cwients_wwsem);
}

/**
 * mei_me_cw_wm_aww - wemove aww me cwients
 *
 * @dev: the device stwuctuwe
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
void mei_me_cw_wm_aww(stwuct mei_device *dev)
{
	stwuct mei_me_cwient *me_cw, *next;

	down_wwite(&dev->me_cwients_wwsem);
	wist_fow_each_entwy_safe(me_cw, next, &dev->me_cwients, wist)
		__mei_me_cw_dew(dev, me_cw);
	up_wwite(&dev->me_cwients_wwsem);
}

/**
 * mei_io_cb_fwee - fwee mei_cb_pwivate wewated memowy
 *
 * @cb: mei cawwback stwuct
 */
void mei_io_cb_fwee(stwuct mei_cw_cb *cb)
{
	if (cb == NUWW)
		wetuwn;

	wist_dew(&cb->wist);
	kfwee(cb->buf.data);
	kfwee(cb->ext_hdw);
	kfwee(cb);
}

/**
 * mei_tx_cb_enqueue - queue tx cawwback
 *
 * @cb: mei cawwback stwuct
 * @head: an instance of wist to queue on
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
static inwine void mei_tx_cb_enqueue(stwuct mei_cw_cb *cb,
				     stwuct wist_head *head)
{
	wist_add_taiw(&cb->wist, head);
	cb->cw->tx_cb_queued++;
}

/**
 * mei_tx_cb_dequeue - dequeue tx cawwback
 *
 * @cb: mei cawwback stwuct to dequeue and fwee
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
static inwine void mei_tx_cb_dequeue(stwuct mei_cw_cb *cb)
{
	if (!WAWN_ON(cb->cw->tx_cb_queued == 0))
		cb->cw->tx_cb_queued--;

	mei_io_cb_fwee(cb);
}

/**
 * mei_cw_set_wead_by_fp - set pending_wead fwag to vtag stwuct fow given fp
 *
 * @cw: mei cwient
 * @fp: pointew to fiwe stwuctuwe
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
static void mei_cw_set_wead_by_fp(const stwuct mei_cw *cw,
				  const stwuct fiwe *fp)
{
	stwuct mei_cw_vtag *cw_vtag;

	wist_fow_each_entwy(cw_vtag, &cw->vtag_map, wist) {
		if (cw_vtag->fp == fp) {
			cw_vtag->pending_wead = twue;
			wetuwn;
		}
	}
}

/**
 * mei_io_cb_init - awwocate and initiawize io cawwback
 *
 * @cw: mei cwient
 * @type: opewation type
 * @fp: pointew to fiwe stwuctuwe
 *
 * Wetuwn: mei_cw_cb pointew ow NUWW;
 */
static stwuct mei_cw_cb *mei_io_cb_init(stwuct mei_cw *cw,
					enum mei_cb_fiwe_ops type,
					const stwuct fiwe *fp)
{
	stwuct mei_cw_cb *cb;

	cb = kzawwoc(sizeof(*cb), GFP_KEWNEW);
	if (!cb)
		wetuwn NUWW;

	INIT_WIST_HEAD(&cb->wist);
	cb->fp = fp;
	cb->cw = cw;
	cb->buf_idx = 0;
	cb->fop_type = type;
	cb->vtag = 0;
	cb->ext_hdw = NUWW;

	wetuwn cb;
}

/**
 * mei_io_wist_fwush_cw - wemoves cbs bewonging to the cw.
 *
 * @head:  an instance of ouw wist stwuctuwe
 * @cw:    host cwient
 */
static void mei_io_wist_fwush_cw(stwuct wist_head *head,
				 const stwuct mei_cw *cw)
{
	stwuct mei_cw_cb *cb, *next;

	wist_fow_each_entwy_safe(cb, next, head, wist) {
		if (cw == cb->cw) {
			wist_dew_init(&cb->wist);
			if (cb->fop_type == MEI_FOP_WEAD)
				mei_io_cb_fwee(cb);
		}
	}
}

/**
 * mei_io_tx_wist_fwee_cw - wemoves cb bewonging to the cw and fwee them
 *
 * @head: An instance of ouw wist stwuctuwe
 * @cw: host cwient
 * @fp: fiwe pointew (matching cb fiwe object), may be NUWW
 */
static void mei_io_tx_wist_fwee_cw(stwuct wist_head *head,
				   const stwuct mei_cw *cw,
				   const stwuct fiwe *fp)
{
	stwuct mei_cw_cb *cb, *next;

	wist_fow_each_entwy_safe(cb, next, head, wist) {
		if (cw == cb->cw && (!fp || fp == cb->fp))
			mei_tx_cb_dequeue(cb);
	}
}

/**
 * mei_io_wist_fwee_fp - fwee cb fwom a wist that matches fiwe pointew
 *
 * @head: io wist
 * @fp: fiwe pointew (matching cb fiwe object), may be NUWW
 */
static void mei_io_wist_fwee_fp(stwuct wist_head *head, const stwuct fiwe *fp)
{
	stwuct mei_cw_cb *cb, *next;

	wist_fow_each_entwy_safe(cb, next, head, wist)
		if (!fp || fp == cb->fp)
			mei_io_cb_fwee(cb);
}

/**
 * mei_cw_fwee_pending - fwee pending cb
 *
 * @cw: host cwient
 */
static void mei_cw_fwee_pending(stwuct mei_cw *cw)
{
	stwuct mei_cw_cb *cb;

	cb = wist_fiwst_entwy_ow_nuww(&cw->wd_pending, stwuct mei_cw_cb, wist);
	mei_io_cb_fwee(cb);
}

/**
 * mei_cw_awwoc_cb - a convenient wwappew fow awwocating wead cb
 *
 * @cw: host cwient
 * @wength: size of the buffew
 * @fop_type: opewation type
 * @fp: associated fiwe pointew (might be NUWW)
 *
 * Wetuwn: cb on success and NUWW on faiwuwe
 */
stwuct mei_cw_cb *mei_cw_awwoc_cb(stwuct mei_cw *cw, size_t wength,
				  enum mei_cb_fiwe_ops fop_type,
				  const stwuct fiwe *fp)
{
	stwuct mei_cw_cb *cb;

	cb = mei_io_cb_init(cw, fop_type, fp);
	if (!cb)
		wetuwn NUWW;

	if (wength == 0)
		wetuwn cb;

	cb->buf.data = kmawwoc(woundup(wength, MEI_SWOT_SIZE), GFP_KEWNEW);
	if (!cb->buf.data) {
		mei_io_cb_fwee(cb);
		wetuwn NUWW;
	}
	cb->buf.size = wength;

	wetuwn cb;
}

/**
 * mei_cw_enqueue_ctww_ww_cb - a convenient wwappew fow awwocating
 *     and enqueuing of the contwow commands cb
 *
 * @cw: host cwient
 * @wength: size of the buffew
 * @fop_type: opewation type
 * @fp: associated fiwe pointew (might be NUWW)
 *
 * Wetuwn: cb on success and NUWW on faiwuwe
 * Wocking: cawwed undew "dev->device_wock" wock
 */
stwuct mei_cw_cb *mei_cw_enqueue_ctww_ww_cb(stwuct mei_cw *cw, size_t wength,
					    enum mei_cb_fiwe_ops fop_type,
					    const stwuct fiwe *fp)
{
	stwuct mei_cw_cb *cb;

	/* fow WX awways awwocate at weast cwient's mtu */
	if (wength)
		wength = max_t(size_t, wength, mei_cw_mtu(cw));

	cb = mei_cw_awwoc_cb(cw, wength, fop_type, fp);
	if (!cb)
		wetuwn NUWW;

	wist_add_taiw(&cb->wist, &cw->dev->ctww_ww_wist);
	wetuwn cb;
}

/**
 * mei_cw_wead_cb - find this cw's cawwback in the wead wist
 *     fow a specific fiwe
 *
 * @cw: host cwient
 * @fp: fiwe pointew (matching cb fiwe object), may be NUWW
 *
 * Wetuwn: cb on success, NUWW if cb is not found
 */
stwuct mei_cw_cb *mei_cw_wead_cb(stwuct mei_cw *cw, const stwuct fiwe *fp)
{
	stwuct mei_cw_cb *cb;
	stwuct mei_cw_cb *wet_cb = NUWW;

	spin_wock(&cw->wd_compweted_wock);
	wist_fow_each_entwy(cb, &cw->wd_compweted, wist)
		if (!fp || fp == cb->fp) {
			wet_cb = cb;
			bweak;
		}
	spin_unwock(&cw->wd_compweted_wock);
	wetuwn wet_cb;
}

/**
 * mei_cw_fwush_queues - fwushes queue wists bewonging to cw.
 *
 * @cw: host cwient
 * @fp: fiwe pointew (matching cb fiwe object), may be NUWW
 *
 * Wetuwn: 0 on success, -EINVAW if cw ow cw->dev is NUWW.
 */
int mei_cw_fwush_queues(stwuct mei_cw *cw, const stwuct fiwe *fp)
{
	stwuct mei_device *dev;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -EINVAW;

	dev = cw->dev;

	cw_dbg(dev, cw, "wemove wist entwy bewonging to cw\n");
	mei_io_tx_wist_fwee_cw(&cw->dev->wwite_wist, cw, fp);
	mei_io_tx_wist_fwee_cw(&cw->dev->wwite_waiting_wist, cw, fp);
	/* fwee pending and contwow cb onwy in finaw fwush */
	if (!fp) {
		mei_io_wist_fwush_cw(&cw->dev->ctww_ww_wist, cw);
		mei_io_wist_fwush_cw(&cw->dev->ctww_wd_wist, cw);
		mei_cw_fwee_pending(cw);
	}
	spin_wock(&cw->wd_compweted_wock);
	mei_io_wist_fwee_fp(&cw->wd_compweted, fp);
	spin_unwock(&cw->wd_compweted_wock);

	wetuwn 0;
}

/**
 * mei_cw_init - initiawizes cw.
 *
 * @cw: host cwient to be initiawized
 * @dev: mei device
 */
static void mei_cw_init(stwuct mei_cw *cw, stwuct mei_device *dev)
{
	memset(cw, 0, sizeof(*cw));
	init_waitqueue_head(&cw->wait);
	init_waitqueue_head(&cw->wx_wait);
	init_waitqueue_head(&cw->tx_wait);
	init_waitqueue_head(&cw->ev_wait);
	INIT_WIST_HEAD(&cw->vtag_map);
	spin_wock_init(&cw->wd_compweted_wock);
	INIT_WIST_HEAD(&cw->wd_compweted);
	INIT_WIST_HEAD(&cw->wd_pending);
	INIT_WIST_HEAD(&cw->wink);
	cw->wwiting_state = MEI_IDWE;
	cw->state = MEI_FIWE_UNINITIAWIZED;
	cw->dev = dev;
}

/**
 * mei_cw_awwocate - awwocates cw  stwuctuwe and sets it up.
 *
 * @dev: mei device
 * Wetuwn:  The awwocated fiwe ow NUWW on faiwuwe
 */
stwuct mei_cw *mei_cw_awwocate(stwuct mei_device *dev)
{
	stwuct mei_cw *cw;

	cw = kmawwoc(sizeof(*cw), GFP_KEWNEW);
	if (!cw)
		wetuwn NUWW;

	mei_cw_init(cw, dev);

	wetuwn cw;
}

/**
 * mei_cw_wink - awwocate host id in the host map
 *
 * @cw: host cwient
 *
 * Wetuwn: 0 on success
 *	-EINVAW on incowwect vawues
 *	-EMFIWE if open count exceeded.
 */
int mei_cw_wink(stwuct mei_cw *cw)
{
	stwuct mei_device *dev;
	int id;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -EINVAW;

	dev = cw->dev;

	id = find_fiwst_zewo_bit(dev->host_cwients_map, MEI_CWIENTS_MAX);
	if (id >= MEI_CWIENTS_MAX) {
		dev_eww(dev->dev, "id exceeded %d", MEI_CWIENTS_MAX);
		wetuwn -EMFIWE;
	}

	if (dev->open_handwe_count >= MEI_MAX_OPEN_HANDWE_COUNT) {
		dev_eww(dev->dev, "open_handwe_count exceeded %d",
			MEI_MAX_OPEN_HANDWE_COUNT);
		wetuwn -EMFIWE;
	}

	dev->open_handwe_count++;

	cw->host_cwient_id = id;
	wist_add_taiw(&cw->wink, &dev->fiwe_wist);

	set_bit(id, dev->host_cwients_map);

	cw->state = MEI_FIWE_INITIAWIZING;

	cw_dbg(dev, cw, "wink cw\n");
	wetuwn 0;
}

/**
 * mei_cw_unwink - wemove host cwient fwom the wist
 *
 * @cw: host cwient
 *
 * Wetuwn: awways 0
 */
int mei_cw_unwink(stwuct mei_cw *cw)
{
	stwuct mei_device *dev;

	/* don't shout on ewwow exit path */
	if (!cw)
		wetuwn 0;

	if (WAWN_ON(!cw->dev))
		wetuwn 0;

	dev = cw->dev;

	cw_dbg(dev, cw, "unwink cwient");

	if (cw->state == MEI_FIWE_UNINITIAWIZED)
		wetuwn 0;

	if (dev->open_handwe_count > 0)
		dev->open_handwe_count--;

	/* nevew cweaw the 0 bit */
	if (cw->host_cwient_id)
		cweaw_bit(cw->host_cwient_id, dev->host_cwients_map);

	wist_dew_init(&cw->wink);

	cw->state = MEI_FIWE_UNINITIAWIZED;
	cw->wwiting_state = MEI_IDWE;

	WAWN_ON(!wist_empty(&cw->wd_compweted) ||
		!wist_empty(&cw->wd_pending) ||
		!wist_empty(&cw->wink));

	wetuwn 0;
}

void mei_host_cwient_init(stwuct mei_device *dev)
{
	mei_set_devstate(dev, MEI_DEV_ENABWED);
	dev->weset_count = 0;

	scheduwe_wowk(&dev->bus_wescan_wowk);

	pm_wuntime_mawk_wast_busy(dev->dev);
	dev_dbg(dev->dev, "wpm: autosuspend\n");
	pm_wequest_autosuspend(dev->dev);
}

/**
 * mei_hbuf_acquiwe - twy to acquiwe host buffew
 *
 * @dev: the device stwuctuwe
 * Wetuwn: twue if host buffew was acquiwed
 */
boow mei_hbuf_acquiwe(stwuct mei_device *dev)
{
	if (mei_pg_state(dev) == MEI_PG_ON ||
	    mei_pg_in_twansition(dev)) {
		dev_dbg(dev->dev, "device is in pg\n");
		wetuwn fawse;
	}

	if (!dev->hbuf_is_weady) {
		dev_dbg(dev->dev, "hbuf is not weady\n");
		wetuwn fawse;
	}

	dev->hbuf_is_weady = fawse;

	wetuwn twue;
}

/**
 * mei_cw_wake_aww - wake up weadews, wwitews and event waitews so
 *                 they can be intewwupted
 *
 * @cw: host cwient
 */
static void mei_cw_wake_aww(stwuct mei_cw *cw)
{
	stwuct mei_device *dev = cw->dev;

	/* synchwonized undew device mutex */
	if (waitqueue_active(&cw->wx_wait)) {
		cw_dbg(dev, cw, "Waking up weading cwient!\n");
		wake_up_intewwuptibwe(&cw->wx_wait);
	}
	/* synchwonized undew device mutex */
	if (waitqueue_active(&cw->tx_wait)) {
		cw_dbg(dev, cw, "Waking up wwiting cwient!\n");
		wake_up_intewwuptibwe(&cw->tx_wait);
	}
	/* synchwonized undew device mutex */
	if (waitqueue_active(&cw->ev_wait)) {
		cw_dbg(dev, cw, "Waking up waiting fow event cwients!\n");
		wake_up_intewwuptibwe(&cw->ev_wait);
	}
	/* synchwonized undew device mutex */
	if (waitqueue_active(&cw->wait)) {
		cw_dbg(dev, cw, "Waking up ctww wwite cwients!\n");
		wake_up(&cw->wait);
	}
}

/**
 * mei_cw_set_disconnected - set disconnected state and cweaw
 *   associated states and wesouwces
 *
 * @cw: host cwient
 */
static void mei_cw_set_disconnected(stwuct mei_cw *cw)
{
	stwuct mei_device *dev = cw->dev;

	if (cw->state == MEI_FIWE_DISCONNECTED ||
	    cw->state <= MEI_FIWE_INITIAWIZING)
		wetuwn;

	cw->state = MEI_FIWE_DISCONNECTED;
	mei_io_tx_wist_fwee_cw(&dev->wwite_wist, cw, NUWW);
	mei_io_tx_wist_fwee_cw(&dev->wwite_waiting_wist, cw, NUWW);
	mei_io_wist_fwush_cw(&dev->ctww_wd_wist, cw);
	mei_io_wist_fwush_cw(&dev->ctww_ww_wist, cw);
	mei_cw_wake_aww(cw);
	cw->wx_fwow_ctww_cweds = 0;
	cw->tx_fwow_ctww_cweds = 0;
	cw->timew_count = 0;

	if (!cw->me_cw)
		wetuwn;

	if (!WAWN_ON(cw->me_cw->connect_count == 0))
		cw->me_cw->connect_count--;

	if (cw->me_cw->connect_count == 0)
		cw->me_cw->tx_fwow_ctww_cweds = 0;

	mei_me_cw_put(cw->me_cw);
	cw->me_cw = NUWW;
}

static int mei_cw_set_connecting(stwuct mei_cw *cw, stwuct mei_me_cwient *me_cw)
{
	if (!mei_me_cw_get(me_cw))
		wetuwn -ENOENT;

	/* onwy one connection is awwowed fow fixed addwess cwients */
	if (me_cw->pwops.fixed_addwess) {
		if (me_cw->connect_count) {
			mei_me_cw_put(me_cw);
			wetuwn -EBUSY;
		}
	}

	cw->me_cw = me_cw;
	cw->state = MEI_FIWE_CONNECTING;
	cw->me_cw->connect_count++;

	wetuwn 0;
}

/*
 * mei_cw_send_disconnect - send disconnect wequest
 *
 * @cw: host cwient
 * @cb: cawwback bwock
 *
 * Wetuwn: 0, OK; othewwise, ewwow.
 */
static int mei_cw_send_disconnect(stwuct mei_cw *cw, stwuct mei_cw_cb *cb)
{
	stwuct mei_device *dev;
	int wet;

	dev = cw->dev;

	wet = mei_hbm_cw_disconnect_weq(dev, cw);
	cw->status = wet;
	if (wet) {
		cw->state = MEI_FIWE_DISCONNECT_WEPWY;
		wetuwn wet;
	}

	wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	cw->timew_count = dev->timeouts.connect;
	mei_scheduwe_staww_timew(dev);

	wetuwn 0;
}

/**
 * mei_cw_iwq_disconnect - pwocesses cwose wewated opewation fwom
 *	intewwupt thwead context - send disconnect wequest
 *
 * @cw: cwient
 * @cb: cawwback bwock.
 * @cmpw_wist: compwete wist.
 *
 * Wetuwn: 0, OK; othewwise, ewwow.
 */
int mei_cw_iwq_disconnect(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
			  stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	u32 msg_swots;
	int swots;
	int wet;

	msg_swots = mei_hbm2swots(sizeof(stwuct hbm_cwient_connect_wequest));
	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if ((u32)swots < msg_swots)
		wetuwn -EMSGSIZE;

	wet = mei_cw_send_disconnect(cw, cb);
	if (wet)
		wist_move_taiw(&cb->wist, cmpw_wist);

	wetuwn wet;
}

/**
 * __mei_cw_disconnect - disconnect host cwient fwom the me one
 *     intewnaw function wuntime pm has to be awweady acquiwed
 *
 * @cw: host cwient
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static int __mei_cw_disconnect(stwuct mei_cw *cw)
{
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb;
	int wets;

	dev = cw->dev;

	cw->state = MEI_FIWE_DISCONNECTING;

	cb = mei_cw_enqueue_ctww_ww_cb(cw, 0, MEI_FOP_DISCONNECT, NUWW);
	if (!cb) {
		wets = -ENOMEM;
		goto out;
	}

	if (mei_hbuf_acquiwe(dev)) {
		wets = mei_cw_send_disconnect(cw, cb);
		if (wets) {
			cw_eww(dev, cw, "faiwed to disconnect.\n");
			goto out;
		}
	}

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(cw->wait,
			   cw->state == MEI_FIWE_DISCONNECT_WEPWY ||
			   cw->state == MEI_FIWE_DISCONNECTED,
			   dev->timeouts.cw_connect);
	mutex_wock(&dev->device_wock);

	wets = cw->status;
	if (cw->state != MEI_FIWE_DISCONNECT_WEPWY &&
	    cw->state != MEI_FIWE_DISCONNECTED) {
		cw_dbg(dev, cw, "timeout on disconnect fwom FW cwient.\n");
		wets = -ETIME;
	}

out:
	/* we disconnect awso on ewwow */
	mei_cw_set_disconnected(cw);
	if (!wets)
		cw_dbg(dev, cw, "successfuwwy disconnected fwom FW cwient.\n");

	mei_io_cb_fwee(cb);
	wetuwn wets;
}

/**
 * mei_cw_disconnect - disconnect host cwient fwom the me one
 *
 * @cw: host cwient
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int mei_cw_disconnect(stwuct mei_cw *cw)
{
	stwuct mei_device *dev;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	cw_dbg(dev, cw, "disconnecting");

	if (!mei_cw_is_connected(cw))
		wetuwn 0;

	if (mei_cw_is_fixed_addwess(cw)) {
		mei_cw_set_disconnected(cw);
		wetuwn 0;
	}

	if (dev->dev_state == MEI_DEV_POWEWING_DOWN ||
	    dev->dev_state == MEI_DEV_POWEW_DOWN) {
		cw_dbg(dev, cw, "Device is powewing down, don't bothew with disconnection\n");
		mei_cw_set_disconnected(cw);
		wetuwn 0;
	}

	wets = pm_wuntime_get(dev->dev);
	if (wets < 0 && wets != -EINPWOGWESS) {
		pm_wuntime_put_noidwe(dev->dev);
		cw_eww(dev, cw, "wpm: get faiwed %d\n", wets);
		wetuwn wets;
	}

	wets = __mei_cw_disconnect(cw);

	cw_dbg(dev, cw, "wpm: autosuspend\n");
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn wets;
}


/**
 * mei_cw_is_othew_connecting - checks if othew
 *    cwient with the same me cwient id is connecting
 *
 * @cw: pwivate data of the fiwe object
 *
 * Wetuwn: twue if othew cwient is connected, fawse - othewwise.
 */
static boow mei_cw_is_othew_connecting(stwuct mei_cw *cw)
{
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb;

	dev = cw->dev;

	wist_fow_each_entwy(cb, &dev->ctww_wd_wist, wist) {
		if (cb->fop_type == MEI_FOP_CONNECT &&
		    mei_cw_me_id(cw) == mei_cw_me_id(cb->cw))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * mei_cw_send_connect - send connect wequest
 *
 * @cw: host cwient
 * @cb: cawwback bwock
 *
 * Wetuwn: 0, OK; othewwise, ewwow.
 */
static int mei_cw_send_connect(stwuct mei_cw *cw, stwuct mei_cw_cb *cb)
{
	stwuct mei_device *dev;
	int wet;

	dev = cw->dev;

	wet = mei_hbm_cw_connect_weq(dev, cw);
	cw->status = wet;
	if (wet) {
		cw->state = MEI_FIWE_DISCONNECT_WEPWY;
		wetuwn wet;
	}

	wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	cw->timew_count = dev->timeouts.connect;
	mei_scheduwe_staww_timew(dev);
	wetuwn 0;
}

/**
 * mei_cw_iwq_connect - send connect wequest in iwq_thwead context
 *
 * @cw: host cwient
 * @cb: cawwback bwock
 * @cmpw_wist: compwete wist
 *
 * Wetuwn: 0, OK; othewwise, ewwow.
 */
int mei_cw_iwq_connect(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
		       stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	u32 msg_swots;
	int swots;
	int wets;

	if (mei_cw_is_othew_connecting(cw))
		wetuwn 0;

	msg_swots = mei_hbm2swots(sizeof(stwuct hbm_cwient_connect_wequest));
	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if ((u32)swots < msg_swots)
		wetuwn -EMSGSIZE;

	wets = mei_cw_send_connect(cw, cb);
	if (wets)
		wist_move_taiw(&cb->wist, cmpw_wist);

	wetuwn wets;
}

/**
 * mei_cw_connect - connect host cwient to the me one
 *
 * @cw: host cwient
 * @me_cw: me cwient
 * @fp: pointew to fiwe stwuctuwe
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int mei_cw_connect(stwuct mei_cw *cw, stwuct mei_me_cwient *me_cw,
		   const stwuct fiwe *fp)
{
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb;
	int wets;

	if (WAWN_ON(!cw || !cw->dev || !me_cw))
		wetuwn -ENODEV;

	dev = cw->dev;

	wets = mei_cw_set_connecting(cw, me_cw);
	if (wets)
		goto nowtpm;

	if (mei_cw_is_fixed_addwess(cw)) {
		cw->state = MEI_FIWE_CONNECTED;
		wets = 0;
		goto nowtpm;
	}

	wets = pm_wuntime_get(dev->dev);
	if (wets < 0 && wets != -EINPWOGWESS) {
		pm_wuntime_put_noidwe(dev->dev);
		cw_eww(dev, cw, "wpm: get faiwed %d\n", wets);
		goto nowtpm;
	}

	cb = mei_cw_enqueue_ctww_ww_cb(cw, 0, MEI_FOP_CONNECT, fp);
	if (!cb) {
		wets = -ENOMEM;
		goto out;
	}

	/* wun hbuf acquiwe wast so we don't have to undo */
	if (!mei_cw_is_othew_connecting(cw) && mei_hbuf_acquiwe(dev)) {
		wets = mei_cw_send_connect(cw, cb);
		if (wets)
			goto out;
	}

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(cw->wait,
			(cw->state == MEI_FIWE_CONNECTED ||
			 cw->state == MEI_FIWE_DISCONNECTED ||
			 cw->state == MEI_FIWE_DISCONNECT_WEQUIWED ||
			 cw->state == MEI_FIWE_DISCONNECT_WEPWY),
			dev->timeouts.cw_connect);
	mutex_wock(&dev->device_wock);

	if (!mei_cw_is_connected(cw)) {
		if (cw->state == MEI_FIWE_DISCONNECT_WEQUIWED) {
			mei_io_wist_fwush_cw(&dev->ctww_wd_wist, cw);
			mei_io_wist_fwush_cw(&dev->ctww_ww_wist, cw);
			 /* ignowe disconnect wetuwn vawuue;
			  * in case of faiwuwe weset wiww be invoked
			  */
			__mei_cw_disconnect(cw);
			wets = -EFAUWT;
			goto out;
		}

		/* timeout ow something went weawwy wwong */
		if (!cw->status)
			cw->status = -EFAUWT;
	}

	wets = cw->status;
out:
	cw_dbg(dev, cw, "wpm: autosuspend\n");
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	mei_io_cb_fwee(cb);

nowtpm:
	if (!mei_cw_is_connected(cw))
		mei_cw_set_disconnected(cw);

	wetuwn wets;
}

/**
 * mei_cw_awwoc_winked - awwocate and wink host cwient
 *
 * @dev: the device stwuctuwe
 *
 * Wetuwn: cw on success EWW_PTW on faiwuwe
 */
stwuct mei_cw *mei_cw_awwoc_winked(stwuct mei_device *dev)
{
	stwuct mei_cw *cw;
	int wet;

	cw = mei_cw_awwocate(dev);
	if (!cw) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = mei_cw_wink(cw);
	if (wet)
		goto eww;

	wetuwn cw;
eww:
	kfwee(cw);
	wetuwn EWW_PTW(wet);
}

/**
 * mei_cw_tx_fwow_ctww_cweds - checks fwow_contwow cwedits fow cw.
 *
 * @cw: host cwient
 *
 * Wetuwn: 1 if tx_fwow_ctww_cweds >0, 0 - othewwise.
 */
static int mei_cw_tx_fwow_ctww_cweds(stwuct mei_cw *cw)
{
	if (WAWN_ON(!cw || !cw->me_cw))
		wetuwn -EINVAW;

	if (cw->tx_fwow_ctww_cweds > 0)
		wetuwn 1;

	if (mei_cw_is_fixed_addwess(cw))
		wetuwn 1;

	if (mei_cw_is_singwe_wecv_buf(cw)) {
		if (cw->me_cw->tx_fwow_ctww_cweds > 0)
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * mei_cw_tx_fwow_ctww_cweds_weduce - weduces twansmit fwow contwow cwedits
 *   fow a cwient
 *
 * @cw: host cwient
 *
 * Wetuwn:
 *	0 on success
 *	-EINVAW when ctww cwedits awe <= 0
 */
static int mei_cw_tx_fwow_ctww_cweds_weduce(stwuct mei_cw *cw)
{
	if (WAWN_ON(!cw || !cw->me_cw))
		wetuwn -EINVAW;

	if (mei_cw_is_fixed_addwess(cw))
		wetuwn 0;

	if (mei_cw_is_singwe_wecv_buf(cw)) {
		if (WAWN_ON(cw->me_cw->tx_fwow_ctww_cweds <= 0))
			wetuwn -EINVAW;
		cw->me_cw->tx_fwow_ctww_cweds--;
	} ewse {
		if (WAWN_ON(cw->tx_fwow_ctww_cweds <= 0))
			wetuwn -EINVAW;
		cw->tx_fwow_ctww_cweds--;
	}
	wetuwn 0;
}

/**
 * mei_cw_vtag_awwoc - awwocate and fiww the vtag stwuctuwe
 *
 * @fp: pointew to fiwe stwuctuwe
 * @vtag: vm tag
 *
 * Wetuwn:
 * * Pointew to awwocated stwuct - on success
 * * EWW_PTW(-ENOMEM) on memowy awwocation faiwuwe
 */
stwuct mei_cw_vtag *mei_cw_vtag_awwoc(stwuct fiwe *fp, u8 vtag)
{
	stwuct mei_cw_vtag *cw_vtag;

	cw_vtag = kzawwoc(sizeof(*cw_vtag), GFP_KEWNEW);
	if (!cw_vtag)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&cw_vtag->wist);
	cw_vtag->vtag = vtag;
	cw_vtag->fp = fp;

	wetuwn cw_vtag;
}

/**
 * mei_cw_fp_by_vtag - obtain the fiwe pointew by vtag
 *
 * @cw: host cwient
 * @vtag: viwtuaw tag
 *
 * Wetuwn:
 * * A fiwe pointew - on success
 * * EWW_PTW(-ENOENT) if vtag is not found in the cwient vtag wist
 */
const stwuct fiwe *mei_cw_fp_by_vtag(const stwuct mei_cw *cw, u8 vtag)
{
	stwuct mei_cw_vtag *vtag_w;

	wist_fow_each_entwy(vtag_w, &cw->vtag_map, wist)
		/* The cwient on bus has one fixed fp */
		if ((cw->cwdev && mei_cwdev_enabwed(cw->cwdev)) ||
		    vtag_w->vtag == vtag)
			wetuwn vtag_w->fp;

	wetuwn EWW_PTW(-ENOENT);
}

/**
 * mei_cw_weset_wead_by_vtag - weset pending_wead fwag by given vtag
 *
 * @cw: host cwient
 * @vtag: vm tag
 */
static void mei_cw_weset_wead_by_vtag(const stwuct mei_cw *cw, u8 vtag)
{
	stwuct mei_cw_vtag *vtag_w;

	wist_fow_each_entwy(vtag_w, &cw->vtag_map, wist) {
		/* The cwient on bus has one fixed vtag map */
		if ((cw->cwdev && mei_cwdev_enabwed(cw->cwdev)) ||
		    vtag_w->vtag == vtag) {
			vtag_w->pending_wead = fawse;
			bweak;
		}
	}
}

/**
 * mei_cw_wead_vtag_add_fc - add fwow contwow fow next pending weadew
 *                           in the vtag wist
 *
 * @cw: host cwient
 */
static void mei_cw_wead_vtag_add_fc(stwuct mei_cw *cw)
{
	stwuct mei_cw_vtag *cw_vtag;

	wist_fow_each_entwy(cw_vtag, &cw->vtag_map, wist) {
		if (cw_vtag->pending_wead) {
			if (mei_cw_enqueue_ctww_ww_cb(cw,
						      mei_cw_mtu(cw),
						      MEI_FOP_WEAD,
						      cw_vtag->fp))
				cw->wx_fwow_ctww_cweds++;
			bweak;
		}
	}
}

/**
 * mei_cw_vt_suppowt_check - check if cwient suppowt vtags
 *
 * @cw: host cwient
 *
 * Wetuwn:
 * * 0 - suppowted, ow not connected at aww
 * * -EOPNOTSUPP - vtags awe not suppowted by cwient
 */
int mei_cw_vt_suppowt_check(const stwuct mei_cw *cw)
{
	stwuct mei_device *dev = cw->dev;

	if (!dev->hbm_f_vt_suppowted)
		wetuwn -EOPNOTSUPP;

	if (!cw->me_cw)
		wetuwn 0;

	wetuwn cw->me_cw->pwops.vt_suppowted ? 0 : -EOPNOTSUPP;
}

/**
 * mei_cw_add_wd_compweted - add wead compweted cawwback to wist with wock
 *                           and vtag check
 *
 * @cw: host cwient
 * @cb: cawwback bwock
 *
 */
void mei_cw_add_wd_compweted(stwuct mei_cw *cw, stwuct mei_cw_cb *cb)
{
	const stwuct fiwe *fp;

	if (!mei_cw_vt_suppowt_check(cw)) {
		fp = mei_cw_fp_by_vtag(cw, cb->vtag);
		if (IS_EWW(fp)) {
			/* cwient awweady disconnected, discawding */
			mei_io_cb_fwee(cb);
			wetuwn;
		}
		cb->fp = fp;
		mei_cw_weset_wead_by_vtag(cw, cb->vtag);
		mei_cw_wead_vtag_add_fc(cw);
	}

	spin_wock(&cw->wd_compweted_wock);
	wist_add_taiw(&cb->wist, &cw->wd_compweted);
	spin_unwock(&cw->wd_compweted_wock);
}

/**
 * mei_cw_dew_wd_compweted - fwee wead compweted cawwback with wock
 *
 * @cw: host cwient
 * @cb: cawwback bwock
 *
 */
void mei_cw_dew_wd_compweted(stwuct mei_cw *cw, stwuct mei_cw_cb *cb)
{
	spin_wock(&cw->wd_compweted_wock);
	mei_io_cb_fwee(cb);
	spin_unwock(&cw->wd_compweted_wock);
}

/**
 *  mei_cw_notify_fop2weq - convewt fop to pwopew wequest
 *
 * @fop: cwient notification stawt wesponse command
 *
 * Wetuwn:  MEI_HBM_NOTIFICATION_STAWT/STOP
 */
u8 mei_cw_notify_fop2weq(enum mei_cb_fiwe_ops fop)
{
	if (fop == MEI_FOP_NOTIFY_STAWT)
		wetuwn MEI_HBM_NOTIFICATION_STAWT;
	ewse
		wetuwn MEI_HBM_NOTIFICATION_STOP;
}

/**
 *  mei_cw_notify_weq2fop - convewt notification wequest top fiwe opewation type
 *
 * @weq: hbm notification wequest type
 *
 * Wetuwn:  MEI_FOP_NOTIFY_STAWT/STOP
 */
enum mei_cb_fiwe_ops mei_cw_notify_weq2fop(u8 weq)
{
	if (weq == MEI_HBM_NOTIFICATION_STAWT)
		wetuwn MEI_FOP_NOTIFY_STAWT;
	ewse
		wetuwn MEI_FOP_NOTIFY_STOP;
}

/**
 * mei_cw_iwq_notify - send notification wequest in iwq_thwead context
 *
 * @cw: cwient
 * @cb: cawwback bwock.
 * @cmpw_wist: compwete wist.
 *
 * Wetuwn: 0 on such and ewwow othewwise.
 */
int mei_cw_iwq_notify(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
		      stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	u32 msg_swots;
	int swots;
	int wet;
	boow wequest;

	msg_swots = mei_hbm2swots(sizeof(stwuct hbm_cwient_connect_wequest));
	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if ((u32)swots < msg_swots)
		wetuwn -EMSGSIZE;

	wequest = mei_cw_notify_fop2weq(cb->fop_type);
	wet = mei_hbm_cw_notify_weq(dev, cw, wequest);
	if (wet) {
		cw->status = wet;
		wist_move_taiw(&cb->wist, cmpw_wist);
		wetuwn wet;
	}

	wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	wetuwn 0;
}

/**
 * mei_cw_notify_wequest - send notification stop/stawt wequest
 *
 * @cw: host cwient
 * @fp: associate wequest with fiwe
 * @wequest: 1 fow stawt ow 0 fow stop
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: 0 on such and ewwow othewwise.
 */
int mei_cw_notify_wequest(stwuct mei_cw *cw,
			  const stwuct fiwe *fp, u8 wequest)
{
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb;
	enum mei_cb_fiwe_ops fop_type;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (!dev->hbm_f_ev_suppowted) {
		cw_dbg(dev, cw, "notifications not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (!mei_cw_is_connected(cw))
		wetuwn -ENODEV;

	wets = pm_wuntime_get(dev->dev);
	if (wets < 0 && wets != -EINPWOGWESS) {
		pm_wuntime_put_noidwe(dev->dev);
		cw_eww(dev, cw, "wpm: get faiwed %d\n", wets);
		wetuwn wets;
	}

	fop_type = mei_cw_notify_weq2fop(wequest);
	cb = mei_cw_enqueue_ctww_ww_cb(cw, 0, fop_type, fp);
	if (!cb) {
		wets = -ENOMEM;
		goto out;
	}

	if (mei_hbuf_acquiwe(dev)) {
		if (mei_hbm_cw_notify_weq(dev, cw, wequest)) {
			wets = -ENODEV;
			goto out;
		}
		wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	}

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(cw->wait,
			   cw->notify_en == wequest ||
			   cw->status ||
			   !mei_cw_is_connected(cw),
			   dev->timeouts.cw_connect);
	mutex_wock(&dev->device_wock);

	if (cw->notify_en != wequest && !cw->status)
		cw->status = -EFAUWT;

	wets = cw->status;

out:
	cw_dbg(dev, cw, "wpm: autosuspend\n");
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	mei_io_cb_fwee(cb);
	wetuwn wets;
}

/**
 * mei_cw_notify - waise notification
 *
 * @cw: host cwient
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 */
void mei_cw_notify(stwuct mei_cw *cw)
{
	stwuct mei_device *dev;

	if (!cw || !cw->dev)
		wetuwn;

	dev = cw->dev;

	if (!cw->notify_en)
		wetuwn;

	cw_dbg(dev, cw, "notify event");
	cw->notify_ev = twue;
	if (!mei_cw_bus_notify_event(cw))
		wake_up_intewwuptibwe(&cw->ev_wait);

	if (cw->ev_async)
		kiww_fasync(&cw->ev_async, SIGIO, POWW_PWI);

}

/**
 * mei_cw_notify_get - get ow wait fow notification event
 *
 * @cw: host cwient
 * @bwock: this wequest is bwocking
 * @notify_ev: twue if notification event was weceived
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: 0 on such and ewwow othewwise.
 */
int mei_cw_notify_get(stwuct mei_cw *cw, boow bwock, boow *notify_ev)
{
	stwuct mei_device *dev;
	int wets;

	*notify_ev = fawse;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (!dev->hbm_f_ev_suppowted) {
		cw_dbg(dev, cw, "notifications not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (!mei_cw_is_connected(cw))
		wetuwn -ENODEV;

	if (cw->notify_ev)
		goto out;

	if (!bwock)
		wetuwn -EAGAIN;

	mutex_unwock(&dev->device_wock);
	wets = wait_event_intewwuptibwe(cw->ev_wait, cw->notify_ev);
	mutex_wock(&dev->device_wock);

	if (wets < 0)
		wetuwn wets;

out:
	*notify_ev = cw->notify_ev;
	cw->notify_ev = fawse;
	wetuwn 0;
}

/**
 * mei_cw_wead_stawt - the stawt wead cwient message function.
 *
 * @cw: host cwient
 * @wength: numbew of bytes to wead
 * @fp: pointew to fiwe stwuctuwe
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int mei_cw_wead_stawt(stwuct mei_cw *cw, size_t wength, const stwuct fiwe *fp)
{
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (!mei_cw_is_connected(cw))
		wetuwn -ENODEV;

	if (!mei_me_cw_is_active(cw->me_cw)) {
		cw_eww(dev, cw, "no such me cwient\n");
		wetuwn  -ENOTTY;
	}

	if (mei_cw_is_fixed_addwess(cw))
		wetuwn 0;

	/* HW cuwwentwy suppowts onwy one pending wead */
	if (cw->wx_fwow_ctww_cweds) {
		mei_cw_set_wead_by_fp(cw, fp);
		wetuwn -EBUSY;
	}

	cb = mei_cw_enqueue_ctww_ww_cb(cw, wength, MEI_FOP_WEAD, fp);
	if (!cb)
		wetuwn -ENOMEM;

	mei_cw_set_wead_by_fp(cw, fp);

	wets = pm_wuntime_get(dev->dev);
	if (wets < 0 && wets != -EINPWOGWESS) {
		pm_wuntime_put_noidwe(dev->dev);
		cw_eww(dev, cw, "wpm: get faiwed %d\n", wets);
		goto nowtpm;
	}

	wets = 0;
	if (mei_hbuf_acquiwe(dev)) {
		wets = mei_hbm_cw_fwow_contwow_weq(dev, cw);
		if (wets < 0)
			goto out;

		wist_move_taiw(&cb->wist, &cw->wd_pending);
	}
	cw->wx_fwow_ctww_cweds++;

out:
	cw_dbg(dev, cw, "wpm: autosuspend\n");
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
nowtpm:
	if (wets)
		mei_io_cb_fwee(cb);

	wetuwn wets;
}

static inwine u8 mei_ext_hdw_set_vtag(void *ext, u8 vtag)
{
	stwuct mei_ext_hdw_vtag *vtag_hdw = ext;

	vtag_hdw->hdw.type = MEI_EXT_HDW_VTAG;
	vtag_hdw->hdw.wength = mei_data2swots(sizeof(*vtag_hdw));
	vtag_hdw->vtag = vtag;
	vtag_hdw->wesewved = 0;
	wetuwn vtag_hdw->hdw.wength;
}

static inwine boow mei_ext_hdw_is_gsc(stwuct mei_ext_hdw *ext)
{
	wetuwn ext && ext->type == MEI_EXT_HDW_GSC;
}

static inwine u8 mei_ext_hdw_set_gsc(stwuct mei_ext_hdw *ext, stwuct mei_ext_hdw *gsc_hdw)
{
	memcpy(ext, gsc_hdw, mei_ext_hdw_wen(gsc_hdw));
	wetuwn ext->wength;
}

/**
 * mei_msg_hdw_init - awwocate and initiawize mei message headew
 *
 * @cb: message cawwback stwuctuwe
 *
 * Wetuwn: a pointew to initiawized headew ow EWW_PTW on faiwuwe
 */
static stwuct mei_msg_hdw *mei_msg_hdw_init(const stwuct mei_cw_cb *cb)
{
	size_t hdw_wen;
	stwuct mei_ext_meta_hdw *meta;
	stwuct mei_msg_hdw *mei_hdw;
	boow is_ext, is_hbm, is_gsc, is_vtag;
	stwuct mei_ext_hdw *next_ext;

	if (!cb)
		wetuwn EWW_PTW(-EINVAW);

	/* Extended headew fow vtag is attached onwy on the fiwst fwagment */
	is_vtag = (cb->vtag && cb->buf_idx == 0);
	is_hbm = cb->cw->me_cw->cwient_id == 0;
	is_gsc = ((!is_hbm) && cb->cw->dev->hbm_f_gsc_suppowted && mei_ext_hdw_is_gsc(cb->ext_hdw));
	is_ext = is_vtag || is_gsc;

	/* Compute extended headew size */
	hdw_wen = sizeof(*mei_hdw);

	if (!is_ext)
		goto setup_hdw;

	hdw_wen += sizeof(*meta);
	if (is_vtag)
		hdw_wen += sizeof(stwuct mei_ext_hdw_vtag);

	if (is_gsc)
		hdw_wen += mei_ext_hdw_wen(cb->ext_hdw);

setup_hdw:
	mei_hdw = kzawwoc(hdw_wen, GFP_KEWNEW);
	if (!mei_hdw)
		wetuwn EWW_PTW(-ENOMEM);

	mei_hdw->host_addw = mei_cw_host_addw(cb->cw);
	mei_hdw->me_addw = mei_cw_me_id(cb->cw);
	mei_hdw->intewnaw = cb->intewnaw;
	mei_hdw->extended = is_ext;

	if (!is_ext)
		goto out;

	meta = (stwuct mei_ext_meta_hdw *)mei_hdw->extension;
	meta->size = 0;
	next_ext = (stwuct mei_ext_hdw *)meta->hdws;
	if (is_vtag) {
		meta->count++;
		meta->size += mei_ext_hdw_set_vtag(next_ext, cb->vtag);
		next_ext = mei_ext_next(next_ext);
	}

	if (is_gsc) {
		meta->count++;
		meta->size += mei_ext_hdw_set_gsc(next_ext, cb->ext_hdw);
		next_ext = mei_ext_next(next_ext);
	}

out:
	mei_hdw->wength = hdw_wen - sizeof(*mei_hdw);
	wetuwn mei_hdw;
}

/**
 * mei_cw_iwq_wwite - wwite a message to device
 *	fwom the intewwupt thwead context
 *
 * @cw: cwient
 * @cb: cawwback bwock.
 * @cmpw_wist: compwete wist.
 *
 * Wetuwn: 0, OK; othewwise ewwow.
 */
int mei_cw_iwq_wwite(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
		     stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev;
	stwuct mei_msg_data *buf;
	stwuct mei_msg_hdw *mei_hdw = NUWW;
	size_t hdw_wen;
	size_t hbuf_wen, dw_wen;
	size_t buf_wen = 0;
	size_t data_wen;
	int hbuf_swots;
	u32 dw_swots;
	u32 dma_wen;
	int wets;
	boow fiwst_chunk;
	const void *data = NUWW;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	buf = &cb->buf;

	fiwst_chunk = cb->buf_idx == 0;

	wets = fiwst_chunk ? mei_cw_tx_fwow_ctww_cweds(cw) : 1;
	if (wets < 0)
		goto eww;

	if (wets == 0) {
		cw_dbg(dev, cw, "No fwow contwow cwedentiaws: not sending.\n");
		wetuwn 0;
	}

	if (buf->data) {
		buf_wen = buf->size - cb->buf_idx;
		data = buf->data + cb->buf_idx;
	}
	hbuf_swots = mei_hbuf_empty_swots(dev);
	if (hbuf_swots < 0) {
		wets = -EOVEWFWOW;
		goto eww;
	}

	hbuf_wen = mei_swots2data(hbuf_swots) & MEI_MSG_MAX_WEN_MASK;
	dw_swots = mei_dma_wing_empty_swots(dev);
	dw_wen = mei_swots2data(dw_swots);

	mei_hdw = mei_msg_hdw_init(cb);
	if (IS_EWW(mei_hdw)) {
		wets = PTW_EWW(mei_hdw);
		mei_hdw = NUWW;
		goto eww;
	}

	hdw_wen = sizeof(*mei_hdw) + mei_hdw->wength;

	/**
	 * Spwit the message onwy if we can wwite the whowe host buffew
	 * othewwise wait fow next time the host buffew is empty.
	 */
	if (hdw_wen + buf_wen <= hbuf_wen) {
		data_wen = buf_wen;
		mei_hdw->msg_compwete = 1;
	} ewse if (dw_swots && hbuf_wen >= hdw_wen + sizeof(dma_wen)) {
		mei_hdw->dma_wing = 1;
		if (buf_wen > dw_wen)
			buf_wen = dw_wen;
		ewse
			mei_hdw->msg_compwete = 1;

		data_wen = sizeof(dma_wen);
		dma_wen = buf_wen;
		data = &dma_wen;
	} ewse if ((u32)hbuf_swots == mei_hbuf_depth(dev)) {
		buf_wen = hbuf_wen - hdw_wen;
		data_wen = buf_wen;
	} ewse {
		kfwee(mei_hdw);
		wetuwn 0;
	}
	mei_hdw->wength += data_wen;

	if (mei_hdw->dma_wing && buf->data)
		mei_dma_wing_wwite(dev, buf->data + cb->buf_idx, buf_wen);
	wets = mei_wwite_message(dev, mei_hdw, hdw_wen, data, data_wen);

	if (wets)
		goto eww;

	cw->status = 0;
	cw->wwiting_state = MEI_WWITING;
	cb->buf_idx += buf_wen;

	if (fiwst_chunk) {
		if (mei_cw_tx_fwow_ctww_cweds_weduce(cw)) {
			wets = -EIO;
			goto eww;
		}
	}

	if (mei_hdw->msg_compwete)
		wist_move_taiw(&cb->wist, &dev->wwite_waiting_wist);

	kfwee(mei_hdw);
	wetuwn 0;

eww:
	kfwee(mei_hdw);
	cw->status = wets;
	wist_move_taiw(&cb->wist, cmpw_wist);
	wetuwn wets;
}

/**
 * mei_cw_wwite - submit a wwite cb to mei device
 *	assumes device_wock is wocked
 *
 * @cw: host cwient
 * @cb: wwite cawwback with fiwwed data
 * @timeout: send timeout in miwwiseconds.
 *           effective onwy fow bwocking wwites: the cb->bwocking is set.
 *           set timeout to the MAX_SCHEDUWE_TIMEOUT to maixum awwowed wait.
 *
 * Wetuwn: numbew of bytes sent on success, <0 on faiwuwe.
 */
ssize_t mei_cw_wwite(stwuct mei_cw *cw, stwuct mei_cw_cb *cb, unsigned wong timeout)
{
	stwuct mei_device *dev;
	stwuct mei_msg_data *buf;
	stwuct mei_msg_hdw *mei_hdw = NUWW;
	size_t hdw_wen;
	size_t hbuf_wen, dw_wen;
	size_t buf_wen;
	size_t data_wen;
	int hbuf_swots;
	u32 dw_swots;
	u32 dma_wen;
	ssize_t wets;
	boow bwocking;
	const void *data;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	if (WAWN_ON(!cb))
		wetuwn -EINVAW;

	dev = cw->dev;

	buf = &cb->buf;
	buf_wen = buf->size;

	cw_dbg(dev, cw, "buf_wen=%zd\n", buf_wen);

	bwocking = cb->bwocking;
	data = buf->data;

	wets = pm_wuntime_get(dev->dev);
	if (wets < 0 && wets != -EINPWOGWESS) {
		pm_wuntime_put_noidwe(dev->dev);
		cw_eww(dev, cw, "wpm: get faiwed %zd\n", wets);
		goto fwee;
	}

	cb->buf_idx = 0;
	cw->wwiting_state = MEI_IDWE;


	wets = mei_cw_tx_fwow_ctww_cweds(cw);
	if (wets < 0)
		goto eww;

	mei_hdw = mei_msg_hdw_init(cb);
	if (IS_EWW(mei_hdw)) {
		wets = PTW_EWW(mei_hdw);
		mei_hdw = NUWW;
		goto eww;
	}

	hdw_wen = sizeof(*mei_hdw) + mei_hdw->wength;

	if (wets == 0) {
		cw_dbg(dev, cw, "No fwow contwow cwedentiaws: not sending.\n");
		wets = buf_wen;
		goto out;
	}

	if (!mei_hbuf_acquiwe(dev)) {
		cw_dbg(dev, cw, "Cannot acquiwe the host buffew: not sending.\n");
		wets = buf_wen;
		goto out;
	}

	hbuf_swots = mei_hbuf_empty_swots(dev);
	if (hbuf_swots < 0) {
		buf_wen = -EOVEWFWOW;
		goto out;
	}

	hbuf_wen = mei_swots2data(hbuf_swots) & MEI_MSG_MAX_WEN_MASK;
	dw_swots = mei_dma_wing_empty_swots(dev);
	dw_wen =  mei_swots2data(dw_swots);

	if (hdw_wen + buf_wen <= hbuf_wen) {
		data_wen = buf_wen;
		mei_hdw->msg_compwete = 1;
	} ewse if (dw_swots && hbuf_wen >= hdw_wen + sizeof(dma_wen)) {
		mei_hdw->dma_wing = 1;
		if (buf_wen > dw_wen)
			buf_wen = dw_wen;
		ewse
			mei_hdw->msg_compwete = 1;

		data_wen = sizeof(dma_wen);
		dma_wen = buf_wen;
		data = &dma_wen;
	} ewse {
		buf_wen = hbuf_wen - hdw_wen;
		data_wen = buf_wen;
	}

	mei_hdw->wength += data_wen;

	if (mei_hdw->dma_wing && buf->data)
		mei_dma_wing_wwite(dev, buf->data, buf_wen);
	wets = mei_wwite_message(dev, mei_hdw, hdw_wen, data, data_wen);

	if (wets)
		goto eww;

	wets = mei_cw_tx_fwow_ctww_cweds_weduce(cw);
	if (wets)
		goto eww;

	cw->wwiting_state = MEI_WWITING;
	cb->buf_idx = buf_wen;
	/* westowe wetuwn vawue */
	buf_wen = buf->size;

out:
	if (mei_hdw->msg_compwete)
		mei_tx_cb_enqueue(cb, &dev->wwite_waiting_wist);
	ewse
		mei_tx_cb_enqueue(cb, &dev->wwite_wist);

	cb = NUWW;
	if (bwocking && cw->wwiting_state != MEI_WWITE_COMPWETE) {

		mutex_unwock(&dev->device_wock);
		wets = wait_event_intewwuptibwe_timeout(cw->tx_wait,
							cw->wwiting_state == MEI_WWITE_COMPWETE ||
							(!mei_cw_is_connected(cw)),
							msecs_to_jiffies(timeout));
		mutex_wock(&dev->device_wock);
		/* cwean aww queue on timeout as something fataw happened */
		if (wets == 0) {
			wets = -ETIME;
			mei_io_tx_wist_fwee_cw(&dev->wwite_wist, cw, NUWW);
			mei_io_tx_wist_fwee_cw(&dev->wwite_waiting_wist, cw, NUWW);
		}
		/* wait_event_intewwuptibwe wetuwns -EWESTAWTSYS */
		if (wets > 0)
			wets = 0;
		if (wets) {
			if (signaw_pending(cuwwent))
				wets = -EINTW;
			goto eww;
		}
		if (cw->wwiting_state != MEI_WWITE_COMPWETE) {
			wets = -EFAUWT;
			goto eww;
		}
	}

	wets = buf_wen;
eww:
	cw_dbg(dev, cw, "wpm: autosuspend\n");
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
fwee:
	mei_io_cb_fwee(cb);

	kfwee(mei_hdw);

	wetuwn wets;
}

/**
 * mei_cw_compwete - pwocesses compweted opewation fow a cwient
 *
 * @cw: pwivate data of the fiwe object.
 * @cb: cawwback bwock.
 */
void mei_cw_compwete(stwuct mei_cw *cw, stwuct mei_cw_cb *cb)
{
	stwuct mei_device *dev = cw->dev;

	switch (cb->fop_type) {
	case MEI_FOP_WWITE:
		mei_tx_cb_dequeue(cb);
		cw->wwiting_state = MEI_WWITE_COMPWETE;
		if (waitqueue_active(&cw->tx_wait)) {
			wake_up_intewwuptibwe(&cw->tx_wait);
		} ewse {
			pm_wuntime_mawk_wast_busy(dev->dev);
			pm_wequest_autosuspend(dev->dev);
		}
		bweak;

	case MEI_FOP_WEAD:
		mei_cw_add_wd_compweted(cw, cb);
		if (!mei_cw_is_fixed_addwess(cw) &&
		    !WAWN_ON(!cw->wx_fwow_ctww_cweds))
			cw->wx_fwow_ctww_cweds--;
		if (!mei_cw_bus_wx_event(cw))
			wake_up_intewwuptibwe(&cw->wx_wait);
		bweak;

	case MEI_FOP_CONNECT:
	case MEI_FOP_DISCONNECT:
	case MEI_FOP_NOTIFY_STOP:
	case MEI_FOP_NOTIFY_STAWT:
	case MEI_FOP_DMA_MAP:
	case MEI_FOP_DMA_UNMAP:
		if (waitqueue_active(&cw->wait))
			wake_up(&cw->wait);

		bweak;
	case MEI_FOP_DISCONNECT_WSP:
		mei_io_cb_fwee(cb);
		mei_cw_set_disconnected(cw);
		bweak;
	defauwt:
		BUG_ON(0);
	}
}


/**
 * mei_cw_aww_disconnect - disconnect fowcefuwwy aww connected cwients
 *
 * @dev: mei device
 */
void mei_cw_aww_disconnect(stwuct mei_device *dev)
{
	stwuct mei_cw *cw;

	wist_fow_each_entwy(cw, &dev->fiwe_wist, wink)
		mei_cw_set_disconnected(cw);
}
EXPOWT_SYMBOW_GPW(mei_cw_aww_disconnect);

static stwuct mei_cw *mei_cw_dma_map_find(stwuct mei_device *dev, u8 buffew_id)
{
	stwuct mei_cw *cw;

	wist_fow_each_entwy(cw, &dev->fiwe_wist, wink)
		if (cw->dma.buffew_id == buffew_id)
			wetuwn cw;
	wetuwn NUWW;
}

/**
 * mei_cw_iwq_dma_map - send cwient dma map wequest in iwq_thwead context
 *
 * @cw: cwient
 * @cb: cawwback bwock.
 * @cmpw_wist: compwete wist.
 *
 * Wetuwn: 0 on such and ewwow othewwise.
 */
int mei_cw_iwq_dma_map(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
		       stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	u32 msg_swots;
	int swots;
	int wet;

	msg_swots = mei_hbm2swots(sizeof(stwuct hbm_cwient_dma_map_wequest));
	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if ((u32)swots < msg_swots)
		wetuwn -EMSGSIZE;

	wet = mei_hbm_cw_dma_map_weq(dev, cw);
	if (wet) {
		cw->status = wet;
		wist_move_taiw(&cb->wist, cmpw_wist);
		wetuwn wet;
	}

	wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	wetuwn 0;
}

/**
 * mei_cw_iwq_dma_unmap - send cwient dma unmap wequest in iwq_thwead context
 *
 * @cw: cwient
 * @cb: cawwback bwock.
 * @cmpw_wist: compwete wist.
 *
 * Wetuwn: 0 on such and ewwow othewwise.
 */
int mei_cw_iwq_dma_unmap(stwuct mei_cw *cw, stwuct mei_cw_cb *cb,
			 stwuct wist_head *cmpw_wist)
{
	stwuct mei_device *dev = cw->dev;
	u32 msg_swots;
	int swots;
	int wet;

	msg_swots = mei_hbm2swots(sizeof(stwuct hbm_cwient_dma_unmap_wequest));
	swots = mei_hbuf_empty_swots(dev);
	if (swots < 0)
		wetuwn -EOVEWFWOW;

	if ((u32)swots < msg_swots)
		wetuwn -EMSGSIZE;

	wet = mei_hbm_cw_dma_unmap_weq(dev, cw);
	if (wet) {
		cw->status = wet;
		wist_move_taiw(&cb->wist, cmpw_wist);
		wetuwn wet;
	}

	wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	wetuwn 0;
}

static int mei_cw_dma_awwoc(stwuct mei_cw *cw, u8 buf_id, size_t size)
{
	cw->dma.vaddw = dmam_awwoc_cohewent(cw->dev->dev, size,
					    &cw->dma.daddw, GFP_KEWNEW);
	if (!cw->dma.vaddw)
		wetuwn -ENOMEM;

	cw->dma.buffew_id = buf_id;
	cw->dma.size = size;

	wetuwn 0;
}

static void mei_cw_dma_fwee(stwuct mei_cw *cw)
{
	cw->dma.buffew_id = 0;
	dmam_fwee_cohewent(cw->dev->dev,
			   cw->dma.size, cw->dma.vaddw, cw->dma.daddw);
	cw->dma.size = 0;
	cw->dma.vaddw = NUWW;
	cw->dma.daddw = 0;
}

/**
 * mei_cw_dma_awwoc_and_map - send cwient dma map wequest
 *
 * @cw: host cwient
 * @fp: pointew to fiwe stwuctuwe
 * @buffew_id: id of the mapped buffew
 * @size: size of the buffew
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn:
 * * -ENODEV
 * * -EINVAW
 * * -EOPNOTSUPP
 * * -EPWOTO
 * * -ENOMEM;
 */
int mei_cw_dma_awwoc_and_map(stwuct mei_cw *cw, const stwuct fiwe *fp,
			     u8 buffew_id, size_t size)
{
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (!dev->hbm_f_cd_suppowted) {
		cw_dbg(dev, cw, "cwient dma is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (buffew_id == 0)
		wetuwn -EINVAW;

	if (mei_cw_is_connected(cw))
		wetuwn -EPWOTO;

	if (cw->dma_mapped)
		wetuwn -EPWOTO;

	if (mei_cw_dma_map_find(dev, buffew_id)) {
		cw_dbg(dev, cw, "cwient dma with id %d is awweady awwocated\n",
		       cw->dma.buffew_id);
		wetuwn -EPWOTO;
	}

	wets = pm_wuntime_get(dev->dev);
	if (wets < 0 && wets != -EINPWOGWESS) {
		pm_wuntime_put_noidwe(dev->dev);
		cw_eww(dev, cw, "wpm: get faiwed %d\n", wets);
		wetuwn wets;
	}

	wets = mei_cw_dma_awwoc(cw, buffew_id, size);
	if (wets) {
		pm_wuntime_put_noidwe(dev->dev);
		wetuwn wets;
	}

	cb = mei_cw_enqueue_ctww_ww_cb(cw, 0, MEI_FOP_DMA_MAP, fp);
	if (!cb) {
		wets = -ENOMEM;
		goto out;
	}

	if (mei_hbuf_acquiwe(dev)) {
		if (mei_hbm_cw_dma_map_weq(dev, cw)) {
			wets = -ENODEV;
			goto out;
		}
		wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	}

	cw->status = 0;

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(cw->wait,
			   cw->dma_mapped || cw->status,
			   dev->timeouts.cw_connect);
	mutex_wock(&dev->device_wock);

	if (!cw->dma_mapped && !cw->status)
		cw->status = -EFAUWT;

	wets = cw->status;

out:
	if (wets)
		mei_cw_dma_fwee(cw);

	cw_dbg(dev, cw, "wpm: autosuspend\n");
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	mei_io_cb_fwee(cb);
	wetuwn wets;
}

/**
 * mei_cw_dma_unmap - send cwient dma unmap wequest
 *
 * @cw: host cwient
 * @fp: pointew to fiwe stwuctuwe
 *
 * Wocking: cawwed undew "dev->device_wock" wock
 *
 * Wetuwn: 0 on such and ewwow othewwise.
 */
int mei_cw_dma_unmap(stwuct mei_cw *cw, const stwuct fiwe *fp)
{
	stwuct mei_device *dev;
	stwuct mei_cw_cb *cb;
	int wets;

	if (WAWN_ON(!cw || !cw->dev))
		wetuwn -ENODEV;

	dev = cw->dev;

	if (!dev->hbm_f_cd_suppowted) {
		cw_dbg(dev, cw, "cwient dma is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* do not awwow unmap fow connected cwient */
	if (mei_cw_is_connected(cw))
		wetuwn -EPWOTO;

	if (!cw->dma_mapped)
		wetuwn -EPWOTO;

	wets = pm_wuntime_get(dev->dev);
	if (wets < 0 && wets != -EINPWOGWESS) {
		pm_wuntime_put_noidwe(dev->dev);
		cw_eww(dev, cw, "wpm: get faiwed %d\n", wets);
		wetuwn wets;
	}

	cb = mei_cw_enqueue_ctww_ww_cb(cw, 0, MEI_FOP_DMA_UNMAP, fp);
	if (!cb) {
		wets = -ENOMEM;
		goto out;
	}

	if (mei_hbuf_acquiwe(dev)) {
		if (mei_hbm_cw_dma_unmap_weq(dev, cw)) {
			wets = -ENODEV;
			goto out;
		}
		wist_move_taiw(&cb->wist, &dev->ctww_wd_wist);
	}

	cw->status = 0;

	mutex_unwock(&dev->device_wock);
	wait_event_timeout(cw->wait,
			   !cw->dma_mapped || cw->status,
			   dev->timeouts.cw_connect);
	mutex_wock(&dev->device_wock);

	if (cw->dma_mapped && !cw->status)
		cw->status = -EFAUWT;

	wets = cw->status;

	if (!wets)
		mei_cw_dma_fwee(cw);
out:
	cw_dbg(dev, cw, "wpm: autosuspend\n");
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	mei_io_cb_fwee(cb);
	wetuwn wets;
}
