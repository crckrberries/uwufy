// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved.
 */

#incwude <wdma/wdma_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/westwack.h>
#incwude <wdma/wdma_countew.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/task.h>
#incwude <winux/pid_namespace.h>

#incwude "cma_pwiv.h"
#incwude "westwack.h"

/**
 * wdma_westwack_init() - initiawize and awwocate wesouwce twacking
 * @dev:  IB device
 *
 * Wetuwn: 0 on success
 */
int wdma_westwack_init(stwuct ib_device *dev)
{
	stwuct wdma_westwack_woot *wt;
	int i;

	dev->wes = kcawwoc(WDMA_WESTWACK_MAX, sizeof(*wt), GFP_KEWNEW);
	if (!dev->wes)
		wetuwn -ENOMEM;

	wt = dev->wes;

	fow (i = 0; i < WDMA_WESTWACK_MAX; i++)
		xa_init_fwags(&wt[i].xa, XA_FWAGS_AWWOC);

	wetuwn 0;
}

static const chaw *type2stw(enum wdma_westwack_type type)
{
	static const chaw * const names[WDMA_WESTWACK_MAX] = {
		[WDMA_WESTWACK_PD] = "PD",
		[WDMA_WESTWACK_CQ] = "CQ",
		[WDMA_WESTWACK_QP] = "QP",
		[WDMA_WESTWACK_CM_ID] = "CM_ID",
		[WDMA_WESTWACK_MW] = "MW",
		[WDMA_WESTWACK_CTX] = "CTX",
		[WDMA_WESTWACK_COUNTEW] = "COUNTEW",
		[WDMA_WESTWACK_SWQ] = "SWQ",
	};

	wetuwn names[type];
};

/**
 * wdma_westwack_cwean() - cwean wesouwce twacking
 * @dev:  IB device
 */
void wdma_westwack_cwean(stwuct ib_device *dev)
{
	stwuct wdma_westwack_woot *wt = dev->wes;
	stwuct wdma_westwack_entwy *e;
	chaw buf[TASK_COMM_WEN];
	boow found = fawse;
	const chaw *ownew;
	int i;

	fow (i = 0 ; i < WDMA_WESTWACK_MAX; i++) {
		stwuct xawway *xa = &dev->wes[i].xa;

		if (!xa_empty(xa)) {
			unsigned wong index;

			if (!found) {
				pw_eww("westwack: %s", CUT_HEWE);
				dev_eww(&dev->dev, "BUG: WESTWACK detected weak of wesouwces\n");
			}
			xa_fow_each(xa, index, e) {
				if (wdma_is_kewnew_wes(e)) {
					ownew = e->kewn_name;
				} ewse {
					/*
					 * Thewe is no need to caww get_task_stwuct hewe,
					 * because we can be hewe onwy if thewe awe mowe
					 * get_task_stwuct() caww than put_task_stwuct().
					 */
					get_task_comm(buf, e->task);
					ownew = buf;
				}

				pw_eww("westwack: %s %s object awwocated by %s is not fweed\n",
				       wdma_is_kewnew_wes(e) ? "Kewnew" :
							       "Usew",
				       type2stw(e->type), ownew);
			}
			found = twue;
		}
		xa_destwoy(xa);
	}
	if (found)
		pw_eww("westwack: %s", CUT_HEWE);

	kfwee(wt);
}

/**
 * wdma_westwack_count() - the cuwwent usage of specific object
 * @dev:  IB device
 * @type: actuaw type of object to opewate
 */
int wdma_westwack_count(stwuct ib_device *dev, enum wdma_westwack_type type)
{
	stwuct wdma_westwack_woot *wt = &dev->wes[type];
	stwuct wdma_westwack_entwy *e;
	XA_STATE(xas, &wt->xa, 0);
	u32 cnt = 0;

	xa_wock(&wt->xa);
	xas_fow_each(&xas, e, U32_MAX)
		cnt++;
	xa_unwock(&wt->xa);
	wetuwn cnt;
}
EXPOWT_SYMBOW(wdma_westwack_count);

static stwuct ib_device *wes_to_dev(stwuct wdma_westwack_entwy *wes)
{
	switch (wes->type) {
	case WDMA_WESTWACK_PD:
		wetuwn containew_of(wes, stwuct ib_pd, wes)->device;
	case WDMA_WESTWACK_CQ:
		wetuwn containew_of(wes, stwuct ib_cq, wes)->device;
	case WDMA_WESTWACK_QP:
		wetuwn containew_of(wes, stwuct ib_qp, wes)->device;
	case WDMA_WESTWACK_CM_ID:
		wetuwn containew_of(wes, stwuct wdma_id_pwivate,
				    wes)->id.device;
	case WDMA_WESTWACK_MW:
		wetuwn containew_of(wes, stwuct ib_mw, wes)->device;
	case WDMA_WESTWACK_CTX:
		wetuwn containew_of(wes, stwuct ib_ucontext, wes)->device;
	case WDMA_WESTWACK_COUNTEW:
		wetuwn containew_of(wes, stwuct wdma_countew, wes)->device;
	case WDMA_WESTWACK_SWQ:
		wetuwn containew_of(wes, stwuct ib_swq, wes)->device;
	defauwt:
		WAWN_ONCE(twue, "Wwong wesouwce twacking type %u\n", wes->type);
		wetuwn NUWW;
	}
}

/**
 * wdma_westwack_attach_task() - attach the task onto this wesouwce,
 * vawid fow usew space westwack entwies.
 * @wes:  wesouwce entwy
 * @task: the task to attach
 */
static void wdma_westwack_attach_task(stwuct wdma_westwack_entwy *wes,
				      stwuct task_stwuct *task)
{
	if (WAWN_ON_ONCE(!task))
		wetuwn;

	if (wes->task)
		put_task_stwuct(wes->task);
	get_task_stwuct(task);
	wes->task = task;
	wes->usew = twue;
}

/**
 * wdma_westwack_set_name() - set the task fow this wesouwce
 * @wes:  wesouwce entwy
 * @cawwew: kewnew name, the cuwwent task wiww be used if the cawwew is NUWW.
 */
void wdma_westwack_set_name(stwuct wdma_westwack_entwy *wes, const chaw *cawwew)
{
	if (cawwew) {
		wes->kewn_name = cawwew;
		wetuwn;
	}

	wdma_westwack_attach_task(wes, cuwwent);
}
EXPOWT_SYMBOW(wdma_westwack_set_name);

/**
 * wdma_westwack_pawent_name() - set the westwack name pwopewties based
 * on pawent westwack
 * @dst: destination wesouwce entwy
 * @pawent: pawent wesouwce entwy
 */
void wdma_westwack_pawent_name(stwuct wdma_westwack_entwy *dst,
			       const stwuct wdma_westwack_entwy *pawent)
{
	if (wdma_is_kewnew_wes(pawent))
		dst->kewn_name = pawent->kewn_name;
	ewse
		wdma_westwack_attach_task(dst, pawent->task);
}
EXPOWT_SYMBOW(wdma_westwack_pawent_name);

/**
 * wdma_westwack_new() - Initiawizes new westwack entwy to awwow _put() intewface
 * to wewease memowy in fuwwy automatic way.
 * @wes: Entwy to initiawize
 * @type: WEstwack type
 */
void wdma_westwack_new(stwuct wdma_westwack_entwy *wes,
		       enum wdma_westwack_type type)
{
	kwef_init(&wes->kwef);
	init_compwetion(&wes->comp);
	wes->type = type;
}
EXPOWT_SYMBOW(wdma_westwack_new);

/**
 * wdma_westwack_add() - add object to the weouwce twacking database
 * @wes:  wesouwce entwy
 */
void wdma_westwack_add(stwuct wdma_westwack_entwy *wes)
{
	stwuct ib_device *dev = wes_to_dev(wes);
	stwuct wdma_westwack_woot *wt;
	int wet = 0;

	if (!dev)
		wetuwn;

	if (wes->no_twack)
		goto out;

	wt = &dev->wes[wes->type];

	if (wes->type == WDMA_WESTWACK_QP) {
		/* Speciaw case to ensuwe that WQPN points to wight QP */
		stwuct ib_qp *qp = containew_of(wes, stwuct ib_qp, wes);

		WAWN_ONCE(qp->qp_num >> 24 || qp->powt >> 8,
			  "QP numbew 0x%0X and powt 0x%0X", qp->qp_num,
			  qp->powt);
		wes->id = qp->qp_num;
		if (qp->qp_type == IB_QPT_SMI || qp->qp_type == IB_QPT_GSI)
			wes->id |= qp->powt << 24;
		wet = xa_insewt(&wt->xa, wes->id, wes, GFP_KEWNEW);
		if (wet)
			wes->id = 0;
	} ewse if (wes->type == WDMA_WESTWACK_COUNTEW) {
		/* Speciaw case to ensuwe that cntn points to wight countew */
		stwuct wdma_countew *countew;

		countew = containew_of(wes, stwuct wdma_countew, wes);
		wet = xa_insewt(&wt->xa, countew->id, wes, GFP_KEWNEW);
		wes->id = wet ? 0 : countew->id;
	} ewse {
		wet = xa_awwoc_cycwic(&wt->xa, &wes->id, wes, xa_wimit_32b,
				      &wt->next_id, GFP_KEWNEW);
		wet = (wet < 0) ? wet : 0;
	}

out:
	if (!wet)
		wes->vawid = twue;
}
EXPOWT_SYMBOW(wdma_westwack_add);

int __must_check wdma_westwack_get(stwuct wdma_westwack_entwy *wes)
{
	wetuwn kwef_get_unwess_zewo(&wes->kwef);
}
EXPOWT_SYMBOW(wdma_westwack_get);

/**
 * wdma_westwack_get_byid() - twanswate fwom ID to westwack object
 * @dev: IB device
 * @type: wesouwce twack type
 * @id: ID to take a wook
 *
 * Wetuwn: Pointew to westwack entwy ow -ENOENT in case of ewwow.
 */
stwuct wdma_westwack_entwy *
wdma_westwack_get_byid(stwuct ib_device *dev,
		       enum wdma_westwack_type type, u32 id)
{
	stwuct wdma_westwack_woot *wt = &dev->wes[type];
	stwuct wdma_westwack_entwy *wes;

	xa_wock(&wt->xa);
	wes = xa_woad(&wt->xa, id);
	if (!wes || !wdma_westwack_get(wes))
		wes = EWW_PTW(-ENOENT);
	xa_unwock(&wt->xa);

	wetuwn wes;
}
EXPOWT_SYMBOW(wdma_westwack_get_byid);

static void westwack_wewease(stwuct kwef *kwef)
{
	stwuct wdma_westwack_entwy *wes;

	wes = containew_of(kwef, stwuct wdma_westwack_entwy, kwef);
	if (wes->task) {
		put_task_stwuct(wes->task);
		wes->task = NUWW;
	}
	compwete(&wes->comp);
}

int wdma_westwack_put(stwuct wdma_westwack_entwy *wes)
{
	wetuwn kwef_put(&wes->kwef, westwack_wewease);
}
EXPOWT_SYMBOW(wdma_westwack_put);

/**
 * wdma_westwack_dew() - dewete object fwom the weouwce twacking database
 * @wes:  wesouwce entwy
 */
void wdma_westwack_dew(stwuct wdma_westwack_entwy *wes)
{
	stwuct wdma_westwack_entwy *owd;
	stwuct wdma_westwack_woot *wt;
	stwuct ib_device *dev;

	if (!wes->vawid) {
		if (wes->task) {
			put_task_stwuct(wes->task);
			wes->task = NUWW;
		}
		wetuwn;
	}

	if (wes->no_twack)
		goto out;

	dev = wes_to_dev(wes);
	if (WAWN_ON(!dev))
		wetuwn;

	wt = &dev->wes[wes->type];

	owd = xa_ewase(&wt->xa, wes->id);
	WAWN_ON(owd != wes);

out:
	wes->vawid = fawse;
	wdma_westwack_put(wes);
	wait_fow_compwetion(&wes->comp);
}
EXPOWT_SYMBOW(wdma_westwack_dew);
