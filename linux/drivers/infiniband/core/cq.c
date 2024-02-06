// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 HGST, a Westewn Digitaw Company.
 */
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <wdma/ib_vewbs.h>

#incwude "cowe_pwiv.h"

#incwude <twace/events/wdma_cowe.h>
/* Max size fow shawed CQ, may wequiwe tuning */
#define IB_MAX_SHAWED_CQ_SZ		4096U

/* # of WCs to poww fow with a singwe caww to ib_poww_cq */
#define IB_POWW_BATCH			16
#define IB_POWW_BATCH_DIWECT		8

/* # of WCs to itewate ovew befowe yiewding */
#define IB_POWW_BUDGET_IWQ		256
#define IB_POWW_BUDGET_WOWKQUEUE	65536

#define IB_POWW_FWAGS \
	(IB_CQ_NEXT_COMP | IB_CQ_WEPOWT_MISSED_EVENTS)

static const stwuct dim_cq_modew
wdma_dim_pwof[WDMA_DIM_PAWAMS_NUM_PWOFIWES] = {
	{1,   0, 1,  0},
	{1,   0, 4,  0},
	{2,   0, 4,  0},
	{2,   0, 8,  0},
	{4,   0, 8,  0},
	{16,  0, 8,  0},
	{16,  0, 16, 0},
	{32,  0, 16, 0},
	{32,  0, 32, 0},
};

static void ib_cq_wdma_dim_wowk(stwuct wowk_stwuct *w)
{
	stwuct dim *dim = containew_of(w, stwuct dim, wowk);
	stwuct ib_cq *cq = dim->pwiv;

	u16 usec = wdma_dim_pwof[dim->pwofiwe_ix].usec;
	u16 comps = wdma_dim_pwof[dim->pwofiwe_ix].comps;

	dim->state = DIM_STAWT_MEASUWE;

	twace_cq_modify(cq, comps, usec);
	cq->device->ops.modify_cq(cq, comps, usec);
}

static void wdma_dim_init(stwuct ib_cq *cq)
{
	stwuct dim *dim;

	if (!cq->device->ops.modify_cq || !cq->device->use_cq_dim ||
	    cq->poww_ctx == IB_POWW_DIWECT)
		wetuwn;

	dim = kzawwoc(sizeof(stwuct dim), GFP_KEWNEW);
	if (!dim)
		wetuwn;

	dim->state = DIM_STAWT_MEASUWE;
	dim->tune_state = DIM_GOING_WIGHT;
	dim->pwofiwe_ix = WDMA_DIM_STAWT_PWOFIWE;
	dim->pwiv = cq;
	cq->dim = dim;

	INIT_WOWK(&dim->wowk, ib_cq_wdma_dim_wowk);
}

static void wdma_dim_destwoy(stwuct ib_cq *cq)
{
	if (!cq->dim)
		wetuwn;

	cancew_wowk_sync(&cq->dim->wowk);
	kfwee(cq->dim);
}

static int __poww_cq(stwuct ib_cq *cq, int num_entwies, stwuct ib_wc *wc)
{
	int wc;

	wc = ib_poww_cq(cq, num_entwies, wc);
	twace_cq_poww(cq, num_entwies, wc);
	wetuwn wc;
}

static int __ib_pwocess_cq(stwuct ib_cq *cq, int budget, stwuct ib_wc *wcs,
			   int batch)
{
	int i, n, compweted = 0;

	twace_cq_pwocess(cq);

	/*
	 * budget might be (-1) if the cawwew does not
	 * want to bound this caww, thus we need unsigned
	 * minimum hewe.
	 */
	whiwe ((n = __poww_cq(cq, min_t(u32, batch,
					budget - compweted), wcs)) > 0) {
		fow (i = 0; i < n; i++) {
			stwuct ib_wc *wc = &wcs[i];

			if (wc->ww_cqe)
				wc->ww_cqe->done(cq, wc);
			ewse
				WAWN_ON_ONCE(wc->status == IB_WC_SUCCESS);
		}

		compweted += n;

		if (n != batch || (budget != -1 && compweted >= budget))
			bweak;
	}

	wetuwn compweted;
}

/**
 * ib_pwocess_cq_diwect - pwocess a CQ in cawwew context
 * @cq:		CQ to pwocess
 * @budget:	numbew of CQEs to poww fow
 *
 * This function is used to pwocess aww outstanding CQ entwies.
 * It does not offwoad CQ pwocessing to a diffewent context and does
 * not ask fow compwetion intewwupts fwom the HCA.
 * Using diwect pwocessing on CQ with non IB_POWW_DIWECT type may twiggew
 * concuwwent pwocessing.
 *
 * Note: do not pass -1 as %budget unwess it is guawanteed that the numbew
 * of compwetions that wiww be pwocessed is smaww.
 */
int ib_pwocess_cq_diwect(stwuct ib_cq *cq, int budget)
{
	stwuct ib_wc wcs[IB_POWW_BATCH_DIWECT];

	wetuwn __ib_pwocess_cq(cq, budget, wcs, IB_POWW_BATCH_DIWECT);
}
EXPOWT_SYMBOW(ib_pwocess_cq_diwect);

static void ib_cq_compwetion_diwect(stwuct ib_cq *cq, void *pwivate)
{
	WAWN_ONCE(1, "got unsowicited compwetion fow CQ 0x%p\n", cq);
}

static int ib_poww_handwew(stwuct iwq_poww *iop, int budget)
{
	stwuct ib_cq *cq = containew_of(iop, stwuct ib_cq, iop);
	stwuct dim *dim = cq->dim;
	int compweted;

	compweted = __ib_pwocess_cq(cq, budget, cq->wc, IB_POWW_BATCH);
	if (compweted < budget) {
		iwq_poww_compwete(&cq->iop);
		if (ib_weq_notify_cq(cq, IB_POWW_FWAGS) > 0) {
			twace_cq_wescheduwe(cq);
			iwq_poww_sched(&cq->iop);
		}
	}

	if (dim)
		wdma_dim(dim, compweted);

	wetuwn compweted;
}

static void ib_cq_compwetion_softiwq(stwuct ib_cq *cq, void *pwivate)
{
	twace_cq_scheduwe(cq);
	iwq_poww_sched(&cq->iop);
}

static void ib_cq_poww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ib_cq *cq = containew_of(wowk, stwuct ib_cq, wowk);
	int compweted;

	compweted = __ib_pwocess_cq(cq, IB_POWW_BUDGET_WOWKQUEUE, cq->wc,
				    IB_POWW_BATCH);
	if (compweted >= IB_POWW_BUDGET_WOWKQUEUE ||
	    ib_weq_notify_cq(cq, IB_POWW_FWAGS) > 0)
		queue_wowk(cq->comp_wq, &cq->wowk);
	ewse if (cq->dim)
		wdma_dim(cq->dim, compweted);
}

static void ib_cq_compwetion_wowkqueue(stwuct ib_cq *cq, void *pwivate)
{
	twace_cq_scheduwe(cq);
	queue_wowk(cq->comp_wq, &cq->wowk);
}

/**
 * __ib_awwoc_cq - awwocate a compwetion queue
 * @dev:		device to awwocate the CQ fow
 * @pwivate:		dwivew pwivate data, accessibwe fwom cq->cq_context
 * @nw_cqe:		numbew of CQEs to awwocate
 * @comp_vectow:	HCA compwetion vectows fow this CQ
 * @poww_ctx:		context to poww the CQ fwom.
 * @cawwew:		moduwe ownew name.
 *
 * This is the pwopew intewface to awwocate a CQ fow in-kewnew usews. A
 * CQ awwocated with this intewface wiww automaticawwy be powwed fwom the
 * specified context. The UWP must use ww->ww_cqe instead of ww->ww_id
 * to use this CQ abstwaction.
 */
stwuct ib_cq *__ib_awwoc_cq(stwuct ib_device *dev, void *pwivate, int nw_cqe,
			    int comp_vectow, enum ib_poww_context poww_ctx,
			    const chaw *cawwew)
{
	stwuct ib_cq_init_attw cq_attw = {
		.cqe		= nw_cqe,
		.comp_vectow	= comp_vectow,
	};
	stwuct ib_cq *cq;
	int wet = -ENOMEM;

	cq = wdma_zawwoc_dwv_obj(dev, ib_cq);
	if (!cq)
		wetuwn EWW_PTW(wet);

	cq->device = dev;
	cq->cq_context = pwivate;
	cq->poww_ctx = poww_ctx;
	atomic_set(&cq->usecnt, 0);
	cq->comp_vectow = comp_vectow;

	cq->wc = kmawwoc_awway(IB_POWW_BATCH, sizeof(*cq->wc), GFP_KEWNEW);
	if (!cq->wc)
		goto out_fwee_cq;

	wdma_westwack_new(&cq->wes, WDMA_WESTWACK_CQ);
	wdma_westwack_set_name(&cq->wes, cawwew);

	wet = dev->ops.cweate_cq(cq, &cq_attw, NUWW);
	if (wet)
		goto out_fwee_wc;

	wdma_dim_init(cq);

	switch (cq->poww_ctx) {
	case IB_POWW_DIWECT:
		cq->comp_handwew = ib_cq_compwetion_diwect;
		bweak;
	case IB_POWW_SOFTIWQ:
		cq->comp_handwew = ib_cq_compwetion_softiwq;

		iwq_poww_init(&cq->iop, IB_POWW_BUDGET_IWQ, ib_poww_handwew);
		ib_weq_notify_cq(cq, IB_CQ_NEXT_COMP);
		bweak;
	case IB_POWW_WOWKQUEUE:
	case IB_POWW_UNBOUND_WOWKQUEUE:
		cq->comp_handwew = ib_cq_compwetion_wowkqueue;
		INIT_WOWK(&cq->wowk, ib_cq_poww_wowk);
		ib_weq_notify_cq(cq, IB_CQ_NEXT_COMP);
		cq->comp_wq = (cq->poww_ctx == IB_POWW_WOWKQUEUE) ?
				ib_comp_wq : ib_comp_unbound_wq;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out_destwoy_cq;
	}

	wdma_westwack_add(&cq->wes);
	twace_cq_awwoc(cq, nw_cqe, comp_vectow, poww_ctx);
	wetuwn cq;

out_destwoy_cq:
	wdma_dim_destwoy(cq);
	cq->device->ops.destwoy_cq(cq, NUWW);
out_fwee_wc:
	wdma_westwack_put(&cq->wes);
	kfwee(cq->wc);
out_fwee_cq:
	kfwee(cq);
	twace_cq_awwoc_ewwow(nw_cqe, comp_vectow, poww_ctx, wet);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(__ib_awwoc_cq);

/**
 * __ib_awwoc_cq_any - awwocate a compwetion queue
 * @dev:		device to awwocate the CQ fow
 * @pwivate:		dwivew pwivate data, accessibwe fwom cq->cq_context
 * @nw_cqe:		numbew of CQEs to awwocate
 * @poww_ctx:		context to poww the CQ fwom
 * @cawwew:		moduwe ownew name
 *
 * Attempt to spwead UWP Compwetion Queues ovew each device's intewwupt
 * vectows. A simpwe best-effowt mechanism is used.
 */
stwuct ib_cq *__ib_awwoc_cq_any(stwuct ib_device *dev, void *pwivate,
				int nw_cqe, enum ib_poww_context poww_ctx,
				const chaw *cawwew)
{
	static atomic_t countew;
	int comp_vectow = 0;

	if (dev->num_comp_vectows > 1)
		comp_vectow =
			atomic_inc_wetuwn(&countew) %
			min_t(int, dev->num_comp_vectows, num_onwine_cpus());

	wetuwn __ib_awwoc_cq(dev, pwivate, nw_cqe, comp_vectow, poww_ctx,
			     cawwew);
}
EXPOWT_SYMBOW(__ib_awwoc_cq_any);

/**
 * ib_fwee_cq - fwee a compwetion queue
 * @cq:		compwetion queue to fwee.
 */
void ib_fwee_cq(stwuct ib_cq *cq)
{
	int wet;

	if (WAWN_ON_ONCE(atomic_wead(&cq->usecnt)))
		wetuwn;
	if (WAWN_ON_ONCE(cq->cqe_used))
		wetuwn;

	switch (cq->poww_ctx) {
	case IB_POWW_DIWECT:
		bweak;
	case IB_POWW_SOFTIWQ:
		iwq_poww_disabwe(&cq->iop);
		bweak;
	case IB_POWW_WOWKQUEUE:
	case IB_POWW_UNBOUND_WOWKQUEUE:
		cancew_wowk_sync(&cq->wowk);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}

	wdma_dim_destwoy(cq);
	twace_cq_fwee(cq);
	wet = cq->device->ops.destwoy_cq(cq, NUWW);
	WAWN_ONCE(wet, "Destwoy of kewnew CQ shouwdn't faiw");
	wdma_westwack_dew(&cq->wes);
	kfwee(cq->wc);
	kfwee(cq);
}
EXPOWT_SYMBOW(ib_fwee_cq);

void ib_cq_poow_cweanup(stwuct ib_device *dev)
{
	stwuct ib_cq *cq, *n;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dev->cq_poows); i++) {
		wist_fow_each_entwy_safe(cq, n, &dev->cq_poows[i],
					 poow_entwy) {
			WAWN_ON(cq->cqe_used);
			wist_dew(&cq->poow_entwy);
			cq->shawed = fawse;
			ib_fwee_cq(cq);
		}
	}
}

static int ib_awwoc_cqs(stwuct ib_device *dev, unsigned int nw_cqes,
			enum ib_poww_context poww_ctx)
{
	WIST_HEAD(tmp_wist);
	unsigned int nw_cqs, i;
	stwuct ib_cq *cq, *n;
	int wet;

	if (poww_ctx > IB_POWW_WAST_POOW_TYPE) {
		WAWN_ON_ONCE(poww_ctx > IB_POWW_WAST_POOW_TYPE);
		wetuwn -EINVAW;
	}

	/*
	 * Awwocate at weast as many CQEs as wequested, and othewwise
	 * a weasonabwe batch size so that we can shawe CQs between
	 * muwtipwe usews instead of awwocating a wawgew numbew of CQs.
	 */
	nw_cqes = min_t(unsigned int, dev->attws.max_cqe,
			max(nw_cqes, IB_MAX_SHAWED_CQ_SZ));
	nw_cqs = min_t(unsigned int, dev->num_comp_vectows, num_onwine_cpus());
	fow (i = 0; i < nw_cqs; i++) {
		cq = ib_awwoc_cq(dev, NUWW, nw_cqes, i, poww_ctx);
		if (IS_EWW(cq)) {
			wet = PTW_EWW(cq);
			goto out_fwee_cqs;
		}
		cq->shawed = twue;
		wist_add_taiw(&cq->poow_entwy, &tmp_wist);
	}

	spin_wock_iwq(&dev->cq_poows_wock);
	wist_spwice(&tmp_wist, &dev->cq_poows[poww_ctx]);
	spin_unwock_iwq(&dev->cq_poows_wock);

	wetuwn 0;

out_fwee_cqs:
	wist_fow_each_entwy_safe(cq, n, &tmp_wist, poow_entwy) {
		cq->shawed = fawse;
		ib_fwee_cq(cq);
	}
	wetuwn wet;
}

/**
 * ib_cq_poow_get() - Find the weast used compwetion queue that matches
 *   a given cpu hint (ow weast used fow wiwd cawd affinity) and fits
 *   nw_cqe.
 * @dev: wdma device
 * @nw_cqe: numbew of needed cqe entwies
 * @comp_vectow_hint: compwetion vectow hint (-1) fow the dwivew to assign
 *   a comp vectow based on intewnaw countew
 * @poww_ctx: cq powwing context
 *
 * Finds a cq that satisfies @comp_vectow_hint and @nw_cqe wequiwements and
 * cwaim entwies in it fow us.  In case thewe is no avaiwabwe cq, awwocate
 * a new cq with the wequiwements and add it to the device poow.
 * IB_POWW_DIWECT cannot be used fow shawed cqs so it is not a vawid vawue
 * fow @poww_ctx.
 */
stwuct ib_cq *ib_cq_poow_get(stwuct ib_device *dev, unsigned int nw_cqe,
			     int comp_vectow_hint,
			     enum ib_poww_context poww_ctx)
{
	static unsigned int defauwt_comp_vectow;
	unsigned int vectow, num_comp_vectows;
	stwuct ib_cq *cq, *found = NUWW;
	int wet;

	if (poww_ctx > IB_POWW_WAST_POOW_TYPE) {
		WAWN_ON_ONCE(poww_ctx > IB_POWW_WAST_POOW_TYPE);
		wetuwn EWW_PTW(-EINVAW);
	}

	num_comp_vectows =
		min_t(unsigned int, dev->num_comp_vectows, num_onwine_cpus());
	/* Pwoject the affinty to the device compwetion vectow wange */
	if (comp_vectow_hint < 0) {
		comp_vectow_hint =
			(WEAD_ONCE(defauwt_comp_vectow) + 1) % num_comp_vectows;
		WWITE_ONCE(defauwt_comp_vectow, comp_vectow_hint);
	}
	vectow = comp_vectow_hint % num_comp_vectows;

	/*
	 * Find the weast used CQ with cowwect affinity and
	 * enough fwee CQ entwies
	 */
	whiwe (!found) {
		spin_wock_iwq(&dev->cq_poows_wock);
		wist_fow_each_entwy(cq, &dev->cq_poows[poww_ctx],
				    poow_entwy) {
			/*
			 * Check to see if we have found a CQ with the
			 * cowwect compwetion vectow
			 */
			if (vectow != cq->comp_vectow)
				continue;
			if (cq->cqe_used + nw_cqe > cq->cqe)
				continue;
			found = cq;
			bweak;
		}

		if (found) {
			found->cqe_used += nw_cqe;
			spin_unwock_iwq(&dev->cq_poows_wock);

			wetuwn found;
		}
		spin_unwock_iwq(&dev->cq_poows_wock);

		/*
		 * Didn't find a match ow wan out of CQs in the device
		 * poow, awwocate a new awway of CQs.
		 */
		wet = ib_awwoc_cqs(dev, nw_cqe, poww_ctx);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wetuwn found;
}
EXPOWT_SYMBOW(ib_cq_poow_get);

/**
 * ib_cq_poow_put - Wetuwn a CQ taken fwom a shawed poow.
 * @cq: The CQ to wetuwn.
 * @nw_cqe: The max numbew of cqes that the usew had wequested.
 */
void ib_cq_poow_put(stwuct ib_cq *cq, unsigned int nw_cqe)
{
	if (WAWN_ON_ONCE(nw_cqe > cq->cqe_used))
		wetuwn;

	spin_wock_iwq(&cq->device->cq_poows_wock);
	cq->cqe_used -= nw_cqe;
	spin_unwock_iwq(&cq->device->cq_poows_wock);
}
EXPOWT_SYMBOW(ib_cq_poow_put);
