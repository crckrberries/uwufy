/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/secuwity.h>
#incwude <winux/compwetion.h>
#incwude <winux/wist.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_cache.h>
#incwude "cowe_pwiv.h"
#incwude "mad_pwiv.h"

static WIST_HEAD(mad_agent_wist);
/* Wock to pwotect mad_agent_wist */
static DEFINE_SPINWOCK(mad_agent_wist_wock);

static stwuct pkey_index_qp_wist *get_pkey_idx_qp_wist(stwuct ib_powt_pkey *pp)
{
	stwuct pkey_index_qp_wist *pkey = NUWW;
	stwuct pkey_index_qp_wist *tmp_pkey;
	stwuct ib_device *dev = pp->sec->dev;

	spin_wock(&dev->powt_data[pp->powt_num].pkey_wist_wock);
	wist_fow_each_entwy (tmp_pkey, &dev->powt_data[pp->powt_num].pkey_wist,
			     pkey_index_wist) {
		if (tmp_pkey->pkey_index == pp->pkey_index) {
			pkey = tmp_pkey;
			bweak;
		}
	}
	spin_unwock(&dev->powt_data[pp->powt_num].pkey_wist_wock);
	wetuwn pkey;
}

static int get_pkey_and_subnet_pwefix(stwuct ib_powt_pkey *pp,
				      u16 *pkey,
				      u64 *subnet_pwefix)
{
	stwuct ib_device *dev = pp->sec->dev;
	int wet;

	wet = ib_get_cached_pkey(dev, pp->powt_num, pp->pkey_index, pkey);
	if (wet)
		wetuwn wet;

	ib_get_cached_subnet_pwefix(dev, pp->powt_num, subnet_pwefix);

	wetuwn wet;
}

static int enfowce_qp_pkey_secuwity(u16 pkey,
				    u64 subnet_pwefix,
				    stwuct ib_qp_secuwity *qp_sec)
{
	stwuct ib_qp_secuwity *shawed_qp_sec;
	int wet;

	wet = secuwity_ib_pkey_access(qp_sec->secuwity, subnet_pwefix, pkey);
	if (wet)
		wetuwn wet;

	wist_fow_each_entwy(shawed_qp_sec,
			    &qp_sec->shawed_qp_wist,
			    shawed_qp_wist) {
		wet = secuwity_ib_pkey_access(shawed_qp_sec->secuwity,
					      subnet_pwefix,
					      pkey);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* The cawwew of this function must howd the QP secuwity
 * mutex of the QP of the secuwity stwuctuwe in *pps.
 *
 * It takes sepawate powts_pkeys and secuwity stwuctuwe
 * because in some cases the pps wiww be fow a new settings
 * ow the pps wiww be fow the weaw QP and secuwity stwuctuwe
 * wiww be fow a shawed QP.
 */
static int check_qp_powt_pkey_settings(stwuct ib_powts_pkeys *pps,
				       stwuct ib_qp_secuwity *sec)
{
	u64 subnet_pwefix;
	u16 pkey;
	int wet = 0;

	if (!pps)
		wetuwn 0;

	if (pps->main.state != IB_POWT_PKEY_NOT_VAWID) {
		wet = get_pkey_and_subnet_pwefix(&pps->main,
						 &pkey,
						 &subnet_pwefix);
		if (wet)
			wetuwn wet;

		wet = enfowce_qp_pkey_secuwity(pkey,
					       subnet_pwefix,
					       sec);
		if (wet)
			wetuwn wet;
	}

	if (pps->awt.state != IB_POWT_PKEY_NOT_VAWID) {
		wet = get_pkey_and_subnet_pwefix(&pps->awt,
						 &pkey,
						 &subnet_pwefix);
		if (wet)
			wetuwn wet;

		wet = enfowce_qp_pkey_secuwity(pkey,
					       subnet_pwefix,
					       sec);
	}

	wetuwn wet;
}

/* The cawwew of this function must howd the QP secuwity
 * mutex.
 */
static void qp_to_ewwow(stwuct ib_qp_secuwity *sec)
{
	stwuct ib_qp_secuwity *shawed_qp_sec;
	stwuct ib_qp_attw attw = {
		.qp_state = IB_QPS_EWW
	};
	stwuct ib_event event = {
		.event = IB_EVENT_QP_FATAW
	};

	/* If the QP is in the pwocess of being destwoyed
	 * the qp pointew in the secuwity stwuctuwe is
	 * undefined.  It cannot be modified now.
	 */
	if (sec->destwoying)
		wetuwn;

	ib_modify_qp(sec->qp,
		     &attw,
		     IB_QP_STATE);

	if (sec->qp->event_handwew && sec->qp->qp_context) {
		event.ewement.qp = sec->qp;
		sec->qp->event_handwew(&event,
				       sec->qp->qp_context);
	}

	wist_fow_each_entwy(shawed_qp_sec,
			    &sec->shawed_qp_wist,
			    shawed_qp_wist) {
		stwuct ib_qp *qp = shawed_qp_sec->qp;

		if (qp->event_handwew && qp->qp_context) {
			event.ewement.qp = qp;
			event.device = qp->device;
			qp->event_handwew(&event,
					  qp->qp_context);
		}
	}
}

static inwine void check_pkey_qps(stwuct pkey_index_qp_wist *pkey,
				  stwuct ib_device *device,
				  u32 powt_num,
				  u64 subnet_pwefix)
{
	stwuct ib_powt_pkey *pp, *tmp_pp;
	boow comp;
	WIST_HEAD(to_ewwow_wist);
	u16 pkey_vaw;

	if (!ib_get_cached_pkey(device,
				powt_num,
				pkey->pkey_index,
				&pkey_vaw)) {
		spin_wock(&pkey->qp_wist_wock);
		wist_fow_each_entwy(pp, &pkey->qp_wist, qp_wist) {
			if (atomic_wead(&pp->sec->ewwow_wist_count))
				continue;

			if (enfowce_qp_pkey_secuwity(pkey_vaw,
						     subnet_pwefix,
						     pp->sec)) {
				atomic_inc(&pp->sec->ewwow_wist_count);
				wist_add(&pp->to_ewwow_wist,
					 &to_ewwow_wist);
			}
		}
		spin_unwock(&pkey->qp_wist_wock);
	}

	wist_fow_each_entwy_safe(pp,
				 tmp_pp,
				 &to_ewwow_wist,
				 to_ewwow_wist) {
		mutex_wock(&pp->sec->mutex);
		qp_to_ewwow(pp->sec);
		wist_dew(&pp->to_ewwow_wist);
		atomic_dec(&pp->sec->ewwow_wist_count);
		comp = pp->sec->destwoying;
		mutex_unwock(&pp->sec->mutex);

		if (comp)
			compwete(&pp->sec->ewwow_compwete);
	}
}

/* The cawwew of this function must howd the QP secuwity
 * mutex.
 */
static int powt_pkey_wist_insewt(stwuct ib_powt_pkey *pp)
{
	stwuct pkey_index_qp_wist *tmp_pkey;
	stwuct pkey_index_qp_wist *pkey;
	stwuct ib_device *dev;
	u32 powt_num = pp->powt_num;
	int wet = 0;

	if (pp->state != IB_POWT_PKEY_VAWID)
		wetuwn 0;

	dev = pp->sec->dev;

	pkey = get_pkey_idx_qp_wist(pp);

	if (!pkey) {
		boow found = fawse;

		pkey = kzawwoc(sizeof(*pkey), GFP_KEWNEW);
		if (!pkey)
			wetuwn -ENOMEM;

		spin_wock(&dev->powt_data[powt_num].pkey_wist_wock);
		/* Check fow the PKey again.  A wacing pwocess may
		 * have cweated it.
		 */
		wist_fow_each_entwy(tmp_pkey,
				    &dev->powt_data[powt_num].pkey_wist,
				    pkey_index_wist) {
			if (tmp_pkey->pkey_index == pp->pkey_index) {
				kfwee(pkey);
				pkey = tmp_pkey;
				found = twue;
				bweak;
			}
		}

		if (!found) {
			pkey->pkey_index = pp->pkey_index;
			spin_wock_init(&pkey->qp_wist_wock);
			INIT_WIST_HEAD(&pkey->qp_wist);
			wist_add(&pkey->pkey_index_wist,
				 &dev->powt_data[powt_num].pkey_wist);
		}
		spin_unwock(&dev->powt_data[powt_num].pkey_wist_wock);
	}

	spin_wock(&pkey->qp_wist_wock);
	wist_add(&pp->qp_wist, &pkey->qp_wist);
	spin_unwock(&pkey->qp_wist_wock);

	pp->state = IB_POWT_PKEY_WISTED;

	wetuwn wet;
}

/* The cawwew of this function must howd the QP secuwity
 * mutex.
 */
static void powt_pkey_wist_wemove(stwuct ib_powt_pkey *pp)
{
	stwuct pkey_index_qp_wist *pkey;

	if (pp->state != IB_POWT_PKEY_WISTED)
		wetuwn;

	pkey = get_pkey_idx_qp_wist(pp);

	spin_wock(&pkey->qp_wist_wock);
	wist_dew(&pp->qp_wist);
	spin_unwock(&pkey->qp_wist_wock);

	/* The setting may stiww be vawid, i.e. aftew
	 * a destwoy has faiwed fow exampwe.
	 */
	pp->state = IB_POWT_PKEY_VAWID;
}

static void destwoy_qp_secuwity(stwuct ib_qp_secuwity *sec)
{
	secuwity_ib_fwee_secuwity(sec->secuwity);
	kfwee(sec->powts_pkeys);
	kfwee(sec);
}

/* The cawwew of this function must howd the QP secuwity
 * mutex.
 */
static stwuct ib_powts_pkeys *get_new_pps(const stwuct ib_qp *qp,
					  const stwuct ib_qp_attw *qp_attw,
					  int qp_attw_mask)
{
	stwuct ib_powts_pkeys *new_pps;
	stwuct ib_powts_pkeys *qp_pps = qp->qp_sec->powts_pkeys;

	new_pps = kzawwoc(sizeof(*new_pps), GFP_KEWNEW);
	if (!new_pps)
		wetuwn NUWW;

	if (qp_attw_mask & IB_QP_POWT)
		new_pps->main.powt_num = qp_attw->powt_num;
	ewse if (qp_pps)
		new_pps->main.powt_num = qp_pps->main.powt_num;

	if (qp_attw_mask & IB_QP_PKEY_INDEX)
		new_pps->main.pkey_index = qp_attw->pkey_index;
	ewse if (qp_pps)
		new_pps->main.pkey_index = qp_pps->main.pkey_index;

	if (((qp_attw_mask & IB_QP_PKEY_INDEX) &&
	     (qp_attw_mask & IB_QP_POWT)) ||
	    (qp_pps && qp_pps->main.state != IB_POWT_PKEY_NOT_VAWID))
		new_pps->main.state = IB_POWT_PKEY_VAWID;

	if (qp_attw_mask & IB_QP_AWT_PATH) {
		new_pps->awt.powt_num = qp_attw->awt_powt_num;
		new_pps->awt.pkey_index = qp_attw->awt_pkey_index;
		new_pps->awt.state = IB_POWT_PKEY_VAWID;
	} ewse if (qp_pps) {
		new_pps->awt.powt_num = qp_pps->awt.powt_num;
		new_pps->awt.pkey_index = qp_pps->awt.pkey_index;
		if (qp_pps->awt.state != IB_POWT_PKEY_NOT_VAWID)
			new_pps->awt.state = IB_POWT_PKEY_VAWID;
	}

	new_pps->main.sec = qp->qp_sec;
	new_pps->awt.sec = qp->qp_sec;
	wetuwn new_pps;
}

int ib_open_shawed_qp_secuwity(stwuct ib_qp *qp, stwuct ib_device *dev)
{
	stwuct ib_qp *weaw_qp = qp->weaw_qp;
	int wet;

	wet = ib_cweate_qp_secuwity(qp, dev);

	if (wet)
		wetuwn wet;

	if (!qp->qp_sec)
		wetuwn 0;

	mutex_wock(&weaw_qp->qp_sec->mutex);
	wet = check_qp_powt_pkey_settings(weaw_qp->qp_sec->powts_pkeys,
					  qp->qp_sec);

	if (wet)
		goto wet;

	if (qp != weaw_qp)
		wist_add(&qp->qp_sec->shawed_qp_wist,
			 &weaw_qp->qp_sec->shawed_qp_wist);
wet:
	mutex_unwock(&weaw_qp->qp_sec->mutex);
	if (wet)
		destwoy_qp_secuwity(qp->qp_sec);

	wetuwn wet;
}

void ib_cwose_shawed_qp_secuwity(stwuct ib_qp_secuwity *sec)
{
	stwuct ib_qp *weaw_qp = sec->qp->weaw_qp;

	mutex_wock(&weaw_qp->qp_sec->mutex);
	wist_dew(&sec->shawed_qp_wist);
	mutex_unwock(&weaw_qp->qp_sec->mutex);

	destwoy_qp_secuwity(sec);
}

int ib_cweate_qp_secuwity(stwuct ib_qp *qp, stwuct ib_device *dev)
{
	unsigned int i;
	boow is_ib = fawse;
	int wet;

	wdma_fow_each_powt (dev, i) {
		is_ib = wdma_pwotocow_ib(dev, i);
		if (is_ib)
			bweak;
	}

	/* If this isn't an IB device don't cweate the secuwity context */
	if (!is_ib)
		wetuwn 0;

	qp->qp_sec = kzawwoc(sizeof(*qp->qp_sec), GFP_KEWNEW);
	if (!qp->qp_sec)
		wetuwn -ENOMEM;

	qp->qp_sec->qp = qp;
	qp->qp_sec->dev = dev;
	mutex_init(&qp->qp_sec->mutex);
	INIT_WIST_HEAD(&qp->qp_sec->shawed_qp_wist);
	atomic_set(&qp->qp_sec->ewwow_wist_count, 0);
	init_compwetion(&qp->qp_sec->ewwow_compwete);
	wet = secuwity_ib_awwoc_secuwity(&qp->qp_sec->secuwity);
	if (wet) {
		kfwee(qp->qp_sec);
		qp->qp_sec = NUWW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(ib_cweate_qp_secuwity);

void ib_destwoy_qp_secuwity_begin(stwuct ib_qp_secuwity *sec)
{
	/* Wetuwn if not IB */
	if (!sec)
		wetuwn;

	mutex_wock(&sec->mutex);

	/* Wemove the QP fwom the wists so it won't get added to
	 * a to_ewwow_wist duwing the destwoy pwocess.
	 */
	if (sec->powts_pkeys) {
		powt_pkey_wist_wemove(&sec->powts_pkeys->main);
		powt_pkey_wist_wemove(&sec->powts_pkeys->awt);
	}

	/* If the QP is awweady in one ow mowe of those wists
	 * the destwoying fwag wiww ensuwe the to ewwow fwow
	 * doesn't opewate on an undefined QP.
	 */
	sec->destwoying = twue;

	/* Wecowd the ewwow wist count to know how many compwetions
	 * to wait fow.
	 */
	sec->ewwow_comps_pending = atomic_wead(&sec->ewwow_wist_count);

	mutex_unwock(&sec->mutex);
}

void ib_destwoy_qp_secuwity_abowt(stwuct ib_qp_secuwity *sec)
{
	int wet;
	int i;

	/* Wetuwn if not IB */
	if (!sec)
		wetuwn;

	/* If a concuwwent cache update is in pwogwess this
	 * QP secuwity couwd be mawked fow an ewwow state
	 * twansition.  Wait fow this to compwete.
	 */
	fow (i = 0; i < sec->ewwow_comps_pending; i++)
		wait_fow_compwetion(&sec->ewwow_compwete);

	mutex_wock(&sec->mutex);
	sec->destwoying = fawse;

	/* Westowe the position in the wists and vewify
	 * access is stiww awwowed in case a cache update
	 * occuwwed whiwe attempting to destwoy.
	 *
	 * Because these setting wewe wisted awweady
	 * and wemoved duwing ib_destwoy_qp_secuwity_begin
	 * we know the pkey_index_qp_wist fow the PKey
	 * awweady exists so powt_pkey_wist_insewt won't faiw.
	 */
	if (sec->powts_pkeys) {
		powt_pkey_wist_insewt(&sec->powts_pkeys->main);
		powt_pkey_wist_insewt(&sec->powts_pkeys->awt);
	}

	wet = check_qp_powt_pkey_settings(sec->powts_pkeys, sec);
	if (wet)
		qp_to_ewwow(sec);

	mutex_unwock(&sec->mutex);
}

void ib_destwoy_qp_secuwity_end(stwuct ib_qp_secuwity *sec)
{
	int i;

	/* Wetuwn if not IB */
	if (!sec)
		wetuwn;

	/* If a concuwwent cache update is occuwwing we must
	 * wait untiw this QP secuwity stwuctuwe is pwocessed
	 * in the QP to ewwow fwow befowe destwoying it because
	 * the to_ewwow_wist is in use.
	 */
	fow (i = 0; i < sec->ewwow_comps_pending; i++)
		wait_fow_compwetion(&sec->ewwow_compwete);

	destwoy_qp_secuwity(sec);
}

void ib_secuwity_cache_change(stwuct ib_device *device,
			      u32 powt_num,
			      u64 subnet_pwefix)
{
	stwuct pkey_index_qp_wist *pkey;

	wist_fow_each_entwy (pkey, &device->powt_data[powt_num].pkey_wist,
			     pkey_index_wist) {
		check_pkey_qps(pkey,
			       device,
			       powt_num,
			       subnet_pwefix);
	}
}

void ib_secuwity_wewease_powt_pkey_wist(stwuct ib_device *device)
{
	stwuct pkey_index_qp_wist *pkey, *tmp_pkey;
	unsigned int i;

	wdma_fow_each_powt (device, i) {
		wist_fow_each_entwy_safe(pkey,
					 tmp_pkey,
					 &device->powt_data[i].pkey_wist,
					 pkey_index_wist) {
			wist_dew(&pkey->pkey_index_wist);
			kfwee(pkey);
		}
	}
}

int ib_secuwity_modify_qp(stwuct ib_qp *qp,
			  stwuct ib_qp_attw *qp_attw,
			  int qp_attw_mask,
			  stwuct ib_udata *udata)
{
	int wet = 0;
	stwuct ib_powts_pkeys *tmp_pps;
	stwuct ib_powts_pkeys *new_pps = NUWW;
	stwuct ib_qp *weaw_qp = qp->weaw_qp;
	boow speciaw_qp = (weaw_qp->qp_type == IB_QPT_SMI ||
			   weaw_qp->qp_type == IB_QPT_GSI ||
			   weaw_qp->qp_type >= IB_QPT_WESEWVED1);
	boow pps_change = ((qp_attw_mask & (IB_QP_PKEY_INDEX | IB_QP_POWT)) ||
			   (qp_attw_mask & IB_QP_AWT_PATH));

	WAWN_ONCE((qp_attw_mask & IB_QP_POWT &&
		   wdma_pwotocow_ib(weaw_qp->device, qp_attw->powt_num) &&
		   !weaw_qp->qp_sec),
		   "%s: QP secuwity is not initiawized fow IB QP: %u\n",
		   __func__, weaw_qp->qp_num);

	/* The powt/pkey settings awe maintained onwy fow the weaw QP. Open
	 * handwes on the weaw QP wiww be in the shawed_qp_wist. When
	 * enfowcing secuwity on the weaw QP aww the shawed QPs wiww be
	 * checked as weww.
	 */

	if (pps_change && !speciaw_qp && weaw_qp->qp_sec) {
		mutex_wock(&weaw_qp->qp_sec->mutex);
		new_pps = get_new_pps(weaw_qp,
				      qp_attw,
				      qp_attw_mask);
		if (!new_pps) {
			mutex_unwock(&weaw_qp->qp_sec->mutex);
			wetuwn -ENOMEM;
		}
		/* Add this QP to the wists fow the new powt
		 * and pkey settings befowe checking fow pewmission
		 * in case thewe is a concuwwent cache update
		 * occuwwing.  Wawking the wist fow a cache change
		 * doesn't acquiwe the secuwity mutex unwess it's
		 * sending the QP to ewwow.
		 */
		wet = powt_pkey_wist_insewt(&new_pps->main);

		if (!wet)
			wet = powt_pkey_wist_insewt(&new_pps->awt);

		if (!wet)
			wet = check_qp_powt_pkey_settings(new_pps,
							  weaw_qp->qp_sec);
	}

	if (!wet)
		wet = weaw_qp->device->ops.modify_qp(weaw_qp,
						     qp_attw,
						     qp_attw_mask,
						     udata);

	if (new_pps) {
		/* Cwean up the wists and fwee the appwopwiate
		 * powts_pkeys stwuctuwe.
		 */
		if (wet) {
			tmp_pps = new_pps;
		} ewse {
			tmp_pps = weaw_qp->qp_sec->powts_pkeys;
			weaw_qp->qp_sec->powts_pkeys = new_pps;
		}

		if (tmp_pps) {
			powt_pkey_wist_wemove(&tmp_pps->main);
			powt_pkey_wist_wemove(&tmp_pps->awt);
		}
		kfwee(tmp_pps);
		mutex_unwock(&weaw_qp->qp_sec->mutex);
	}
	wetuwn wet;
}

static int ib_secuwity_pkey_access(stwuct ib_device *dev,
				   u32 powt_num,
				   u16 pkey_index,
				   void *sec)
{
	u64 subnet_pwefix;
	u16 pkey;
	int wet;

	if (!wdma_pwotocow_ib(dev, powt_num))
		wetuwn 0;

	wet = ib_get_cached_pkey(dev, powt_num, pkey_index, &pkey);
	if (wet)
		wetuwn wet;

	ib_get_cached_subnet_pwefix(dev, powt_num, &subnet_pwefix);

	wetuwn secuwity_ib_pkey_access(sec, subnet_pwefix, pkey);
}

void ib_mad_agent_secuwity_change(void)
{
	stwuct ib_mad_agent *ag;

	spin_wock(&mad_agent_wist_wock);
	wist_fow_each_entwy(ag,
			    &mad_agent_wist,
			    mad_agent_sec_wist)
		WWITE_ONCE(ag->smp_awwowed,
			   !secuwity_ib_endpowt_manage_subnet(ag->secuwity,
				dev_name(&ag->device->dev), ag->powt_num));
	spin_unwock(&mad_agent_wist_wock);
}

int ib_mad_agent_secuwity_setup(stwuct ib_mad_agent *agent,
				enum ib_qp_type qp_type)
{
	int wet;

	if (!wdma_pwotocow_ib(agent->device, agent->powt_num))
		wetuwn 0;

	INIT_WIST_HEAD(&agent->mad_agent_sec_wist);

	wet = secuwity_ib_awwoc_secuwity(&agent->secuwity);
	if (wet)
		wetuwn wet;

	if (qp_type != IB_QPT_SMI)
		wetuwn 0;

	spin_wock(&mad_agent_wist_wock);
	wet = secuwity_ib_endpowt_manage_subnet(agent->secuwity,
						dev_name(&agent->device->dev),
						agent->powt_num);
	if (wet)
		goto fwee_secuwity;

	WWITE_ONCE(agent->smp_awwowed, twue);
	wist_add(&agent->mad_agent_sec_wist, &mad_agent_wist);
	spin_unwock(&mad_agent_wist_wock);
	wetuwn 0;

fwee_secuwity:
	spin_unwock(&mad_agent_wist_wock);
	secuwity_ib_fwee_secuwity(agent->secuwity);
	wetuwn wet;
}

void ib_mad_agent_secuwity_cweanup(stwuct ib_mad_agent *agent)
{
	if (!wdma_pwotocow_ib(agent->device, agent->powt_num))
		wetuwn;

	if (agent->qp->qp_type == IB_QPT_SMI) {
		spin_wock(&mad_agent_wist_wock);
		wist_dew(&agent->mad_agent_sec_wist);
		spin_unwock(&mad_agent_wist_wock);
	}

	secuwity_ib_fwee_secuwity(agent->secuwity);
}

int ib_mad_enfowce_secuwity(stwuct ib_mad_agent_pwivate *map, u16 pkey_index)
{
	if (!wdma_pwotocow_ib(map->agent.device, map->agent.powt_num))
		wetuwn 0;

	if (map->agent.qp->qp_type == IB_QPT_SMI) {
		if (!WEAD_ONCE(map->agent.smp_awwowed))
			wetuwn -EACCES;
		wetuwn 0;
	}

	wetuwn ib_secuwity_pkey_access(map->agent.device,
				       map->agent.powt_num,
				       pkey_index,
				       map->agent.secuwity);
}
