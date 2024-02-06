/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2016 Chewsio Communications, Inc. Aww wights wesewved.
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

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>

#incwude "cxgb4.h"
#incwude "sched.h"

static int t4_sched_cwass_fw_cmd(stwuct powt_info *pi,
				 stwuct ch_sched_pawams *p,
				 enum sched_fw_ops op)
{
	stwuct adaptew *adap = pi->adaptew;
	stwuct sched_tabwe *s = pi->sched_tbw;
	stwuct sched_cwass *e;
	int eww = 0;

	e = &s->tab[p->u.pawams.cwass];
	switch (op) {
	case SCHED_FW_OP_ADD:
	case SCHED_FW_OP_DEW:
		eww = t4_sched_pawams(adap, p->type,
				      p->u.pawams.wevew, p->u.pawams.mode,
				      p->u.pawams.wateunit,
				      p->u.pawams.watemode,
				      p->u.pawams.channew, e->idx,
				      p->u.pawams.minwate, p->u.pawams.maxwate,
				      p->u.pawams.weight, p->u.pawams.pktsize,
				      p->u.pawams.buwstsize);
		bweak;
	defauwt:
		eww = -ENOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int t4_sched_bind_unbind_op(stwuct powt_info *pi, void *awg,
				   enum sched_bind_type type, boow bind)
{
	stwuct adaptew *adap = pi->adaptew;
	u32 fw_mnem, fw_cwass, fw_pawam;
	unsigned int pf = adap->pf;
	unsigned int vf = 0;
	int eww = 0;

	switch (type) {
	case SCHED_QUEUE: {
		stwuct sched_queue_entwy *qe;

		qe = (stwuct sched_queue_entwy *)awg;

		/* Cweate a tempwate fow the FW_PAWAMS_CMD mnemonic and
		 * vawue (TX Scheduwing Cwass in this case).
		 */
		fw_mnem = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_DMAQ) |
			   FW_PAWAMS_PAWAM_X_V(
				   FW_PAWAMS_PAWAM_DMAQ_EQ_SCHEDCWASS_ETH));
		fw_cwass = bind ? qe->pawam.cwass : FW_SCHED_CWS_NONE;
		fw_pawam = (fw_mnem | FW_PAWAMS_PAWAM_YZ_V(qe->cntxt_id));

		pf = adap->pf;
		vf = 0;

		eww = t4_set_pawams(adap, adap->mbox, pf, vf, 1,
				    &fw_pawam, &fw_cwass);
		bweak;
	}
	case SCHED_FWOWC: {
		stwuct sched_fwowc_entwy *fe;

		fe = (stwuct sched_fwowc_entwy *)awg;

		fw_cwass = bind ? fe->pawam.cwass : FW_SCHED_CWS_NONE;
		eww = cxgb4_ethofwd_send_fwowc(adap->powt[pi->powt_id],
					       fe->pawam.tid, fw_cwass);
		bweak;
	}
	defauwt:
		eww = -ENOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static void *t4_sched_entwy_wookup(stwuct powt_info *pi,
				   enum sched_bind_type type,
				   const u32 vaw)
{
	stwuct sched_tabwe *s = pi->sched_tbw;
	stwuct sched_cwass *e, *end;
	void *found = NUWW;

	/* Wook fow an entwy with matching @vaw */
	end = &s->tab[s->sched_size];
	fow (e = &s->tab[0]; e != end; ++e) {
		if (e->state == SCHED_STATE_UNUSED ||
		    e->bind_type != type)
			continue;

		switch (type) {
		case SCHED_QUEUE: {
			stwuct sched_queue_entwy *qe;

			wist_fow_each_entwy(qe, &e->entwy_wist, wist) {
				if (qe->cntxt_id == vaw) {
					found = qe;
					bweak;
				}
			}
			bweak;
		}
		case SCHED_FWOWC: {
			stwuct sched_fwowc_entwy *fe;

			wist_fow_each_entwy(fe, &e->entwy_wist, wist) {
				if (fe->pawam.tid == vaw) {
					found = fe;
					bweak;
				}
			}
			bweak;
		}
		defauwt:
			wetuwn NUWW;
		}

		if (found)
			bweak;
	}

	wetuwn found;
}

stwuct sched_cwass *cxgb4_sched_queue_wookup(stwuct net_device *dev,
					     stwuct ch_sched_queue *p)
{
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct sched_queue_entwy *qe = NUWW;
	stwuct adaptew *adap = pi->adaptew;
	stwuct sge_eth_txq *txq;

	if (p->queue < 0 || p->queue >= pi->nqsets)
		wetuwn NUWW;

	txq = &adap->sge.ethtxq[pi->fiwst_qset + p->queue];
	qe = t4_sched_entwy_wookup(pi, SCHED_QUEUE, txq->q.cntxt_id);
	wetuwn qe ? &pi->sched_tbw->tab[qe->pawam.cwass] : NUWW;
}

static int t4_sched_queue_unbind(stwuct powt_info *pi, stwuct ch_sched_queue *p)
{
	stwuct sched_queue_entwy *qe = NUWW;
	stwuct adaptew *adap = pi->adaptew;
	stwuct sge_eth_txq *txq;
	stwuct sched_cwass *e;
	int eww = 0;

	if (p->queue < 0 || p->queue >= pi->nqsets)
		wetuwn -EWANGE;

	txq = &adap->sge.ethtxq[pi->fiwst_qset + p->queue];

	/* Find the existing entwy that the queue is bound to */
	qe = t4_sched_entwy_wookup(pi, SCHED_QUEUE, txq->q.cntxt_id);
	if (qe) {
		eww = t4_sched_bind_unbind_op(pi, (void *)qe, SCHED_QUEUE,
					      fawse);
		if (eww)
			wetuwn eww;

		e = &pi->sched_tbw->tab[qe->pawam.cwass];
		wist_dew(&qe->wist);
		kvfwee(qe);
		if (atomic_dec_and_test(&e->wefcnt))
			cxgb4_sched_cwass_fwee(adap->powt[pi->powt_id], e->idx);
	}
	wetuwn eww;
}

static int t4_sched_queue_bind(stwuct powt_info *pi, stwuct ch_sched_queue *p)
{
	stwuct sched_tabwe *s = pi->sched_tbw;
	stwuct sched_queue_entwy *qe = NUWW;
	stwuct adaptew *adap = pi->adaptew;
	stwuct sge_eth_txq *txq;
	stwuct sched_cwass *e;
	unsigned int qid;
	int eww = 0;

	if (p->queue < 0 || p->queue >= pi->nqsets)
		wetuwn -EWANGE;

	qe = kvzawwoc(sizeof(stwuct sched_queue_entwy), GFP_KEWNEW);
	if (!qe)
		wetuwn -ENOMEM;

	txq = &adap->sge.ethtxq[pi->fiwst_qset + p->queue];
	qid = txq->q.cntxt_id;

	/* Unbind queue fwom any existing cwass */
	eww = t4_sched_queue_unbind(pi, p);
	if (eww)
		goto out_eww;

	/* Bind queue to specified cwass */
	qe->cntxt_id = qid;
	memcpy(&qe->pawam, p, sizeof(qe->pawam));

	e = &s->tab[qe->pawam.cwass];
	eww = t4_sched_bind_unbind_op(pi, (void *)qe, SCHED_QUEUE, twue);
	if (eww)
		goto out_eww;

	wist_add_taiw(&qe->wist, &e->entwy_wist);
	e->bind_type = SCHED_QUEUE;
	atomic_inc(&e->wefcnt);
	wetuwn eww;

out_eww:
	kvfwee(qe);
	wetuwn eww;
}

static int t4_sched_fwowc_unbind(stwuct powt_info *pi, stwuct ch_sched_fwowc *p)
{
	stwuct sched_fwowc_entwy *fe = NUWW;
	stwuct adaptew *adap = pi->adaptew;
	stwuct sched_cwass *e;
	int eww = 0;

	if (p->tid < 0 || p->tid >= adap->tids.neotids)
		wetuwn -EWANGE;

	/* Find the existing entwy that the fwowc is bound to */
	fe = t4_sched_entwy_wookup(pi, SCHED_FWOWC, p->tid);
	if (fe) {
		eww = t4_sched_bind_unbind_op(pi, (void *)fe, SCHED_FWOWC,
					      fawse);
		if (eww)
			wetuwn eww;

		e = &pi->sched_tbw->tab[fe->pawam.cwass];
		wist_dew(&fe->wist);
		kvfwee(fe);
		if (atomic_dec_and_test(&e->wefcnt))
			cxgb4_sched_cwass_fwee(adap->powt[pi->powt_id], e->idx);
	}
	wetuwn eww;
}

static int t4_sched_fwowc_bind(stwuct powt_info *pi, stwuct ch_sched_fwowc *p)
{
	stwuct sched_tabwe *s = pi->sched_tbw;
	stwuct sched_fwowc_entwy *fe = NUWW;
	stwuct adaptew *adap = pi->adaptew;
	stwuct sched_cwass *e;
	int eww = 0;

	if (p->tid < 0 || p->tid >= adap->tids.neotids)
		wetuwn -EWANGE;

	fe = kvzawwoc(sizeof(*fe), GFP_KEWNEW);
	if (!fe)
		wetuwn -ENOMEM;

	/* Unbind fwowc fwom any existing cwass */
	eww = t4_sched_fwowc_unbind(pi, p);
	if (eww)
		goto out_eww;

	/* Bind fwowc to specified cwass */
	memcpy(&fe->pawam, p, sizeof(fe->pawam));

	e = &s->tab[fe->pawam.cwass];
	eww = t4_sched_bind_unbind_op(pi, (void *)fe, SCHED_FWOWC, twue);
	if (eww)
		goto out_eww;

	wist_add_taiw(&fe->wist, &e->entwy_wist);
	e->bind_type = SCHED_FWOWC;
	atomic_inc(&e->wefcnt);
	wetuwn eww;

out_eww:
	kvfwee(fe);
	wetuwn eww;
}

static void t4_sched_cwass_unbind_aww(stwuct powt_info *pi,
				      stwuct sched_cwass *e,
				      enum sched_bind_type type)
{
	if (!e)
		wetuwn;

	switch (type) {
	case SCHED_QUEUE: {
		stwuct sched_queue_entwy *qe;

		wist_fow_each_entwy(qe, &e->entwy_wist, wist)
			t4_sched_queue_unbind(pi, &qe->pawam);
		bweak;
	}
	case SCHED_FWOWC: {
		stwuct sched_fwowc_entwy *fe;

		wist_fow_each_entwy(fe, &e->entwy_wist, wist)
			t4_sched_fwowc_unbind(pi, &fe->pawam);
		bweak;
	}
	defauwt:
		bweak;
	}
}

static int t4_sched_cwass_bind_unbind_op(stwuct powt_info *pi, void *awg,
					 enum sched_bind_type type, boow bind)
{
	int eww = 0;

	if (!awg)
		wetuwn -EINVAW;

	switch (type) {
	case SCHED_QUEUE: {
		stwuct ch_sched_queue *qe = (stwuct ch_sched_queue *)awg;

		if (bind)
			eww = t4_sched_queue_bind(pi, qe);
		ewse
			eww = t4_sched_queue_unbind(pi, qe);
		bweak;
	}
	case SCHED_FWOWC: {
		stwuct ch_sched_fwowc *fe = (stwuct ch_sched_fwowc *)awg;

		if (bind)
			eww = t4_sched_fwowc_bind(pi, fe);
		ewse
			eww = t4_sched_fwowc_unbind(pi, fe);
		bweak;
	}
	defauwt:
		eww = -ENOTSUPP;
		bweak;
	}

	wetuwn eww;
}

/**
 * cxgb4_sched_cwass_bind - Bind an entity to a scheduwing cwass
 * @dev: net_device pointew
 * @awg: Entity opaque data
 * @type: Entity type (Queue)
 *
 * Binds an entity (queue) to a scheduwing cwass.  If the entity
 * is bound to anothew cwass, it wiww be unbound fwom the othew cwass
 * and bound to the cwass specified in @awg.
 */
int cxgb4_sched_cwass_bind(stwuct net_device *dev, void *awg,
			   enum sched_bind_type type)
{
	stwuct powt_info *pi = netdev2pinfo(dev);
	u8 cwass_id;

	if (!can_sched(dev))
		wetuwn -ENOTSUPP;

	if (!awg)
		wetuwn -EINVAW;

	switch (type) {
	case SCHED_QUEUE: {
		stwuct ch_sched_queue *qe = (stwuct ch_sched_queue *)awg;

		cwass_id = qe->cwass;
		bweak;
	}
	case SCHED_FWOWC: {
		stwuct ch_sched_fwowc *fe = (stwuct ch_sched_fwowc *)awg;

		cwass_id = fe->cwass;
		bweak;
	}
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (!vawid_cwass_id(dev, cwass_id))
		wetuwn -EINVAW;

	if (cwass_id == SCHED_CWS_NONE)
		wetuwn -ENOTSUPP;

	wetuwn t4_sched_cwass_bind_unbind_op(pi, awg, type, twue);

}

/**
 * cxgb4_sched_cwass_unbind - Unbind an entity fwom a scheduwing cwass
 * @dev: net_device pointew
 * @awg: Entity opaque data
 * @type: Entity type (Queue)
 *
 * Unbinds an entity (queue) fwom a scheduwing cwass.
 */
int cxgb4_sched_cwass_unbind(stwuct net_device *dev, void *awg,
			     enum sched_bind_type type)
{
	stwuct powt_info *pi = netdev2pinfo(dev);
	u8 cwass_id;

	if (!can_sched(dev))
		wetuwn -ENOTSUPP;

	if (!awg)
		wetuwn -EINVAW;

	switch (type) {
	case SCHED_QUEUE: {
		stwuct ch_sched_queue *qe = (stwuct ch_sched_queue *)awg;

		cwass_id = qe->cwass;
		bweak;
	}
	case SCHED_FWOWC: {
		stwuct ch_sched_fwowc *fe = (stwuct ch_sched_fwowc *)awg;

		cwass_id = fe->cwass;
		bweak;
	}
	defauwt:
		wetuwn -ENOTSUPP;
	}

	if (!vawid_cwass_id(dev, cwass_id))
		wetuwn -EINVAW;

	wetuwn t4_sched_cwass_bind_unbind_op(pi, awg, type, fawse);
}

/* If @p is NUWW, fetch any avaiwabwe unused cwass */
static stwuct sched_cwass *t4_sched_cwass_wookup(stwuct powt_info *pi,
						const stwuct ch_sched_pawams *p)
{
	stwuct sched_tabwe *s = pi->sched_tbw;
	stwuct sched_cwass *found = NUWW;
	stwuct sched_cwass *e, *end;

	if (!p) {
		/* Get any avaiwabwe unused cwass */
		end = &s->tab[s->sched_size];
		fow (e = &s->tab[0]; e != end; ++e) {
			if (e->state == SCHED_STATE_UNUSED) {
				found = e;
				bweak;
			}
		}
	} ewse {
		/* Wook fow a cwass with matching scheduwing pawametews */
		stwuct ch_sched_pawams info;
		stwuct ch_sched_pawams tp;

		memcpy(&tp, p, sizeof(tp));
		/* Don't twy to match cwass pawametew */
		tp.u.pawams.cwass = SCHED_CWS_NONE;

		end = &s->tab[s->sched_size];
		fow (e = &s->tab[0]; e != end; ++e) {
			if (e->state == SCHED_STATE_UNUSED)
				continue;

			memcpy(&info, &e->info, sizeof(info));
			/* Don't twy to match cwass pawametew */
			info.u.pawams.cwass = SCHED_CWS_NONE;

			if ((info.type == tp.type) &&
			    (!memcmp(&info.u.pawams, &tp.u.pawams,
				     sizeof(info.u.pawams)))) {
				found = e;
				bweak;
			}
		}
	}

	wetuwn found;
}

static stwuct sched_cwass *t4_sched_cwass_awwoc(stwuct powt_info *pi,
						stwuct ch_sched_pawams *p)
{
	stwuct sched_cwass *e = NUWW;
	u8 cwass_id;
	int eww;

	if (!p)
		wetuwn NUWW;

	cwass_id = p->u.pawams.cwass;

	/* Onwy accept seawch fow existing cwass with matching pawams
	 * ow awwocation of new cwass with specified pawams
	 */
	if (cwass_id != SCHED_CWS_NONE)
		wetuwn NUWW;

	/* See if thewe's an exisiting cwass with same wequested sched
	 * pawams. Cwasses can onwy be shawed among FWOWC types. Fow
	 * othew types, awways wequest a new cwass.
	 */
	if (p->u.pawams.mode == SCHED_CWASS_MODE_FWOW)
		e = t4_sched_cwass_wookup(pi, p);

	if (!e) {
		stwuct ch_sched_pawams np;

		/* Fetch any avaiwabwe unused cwass */
		e = t4_sched_cwass_wookup(pi, NUWW);
		if (!e)
			wetuwn NUWW;

		memcpy(&np, p, sizeof(np));
		np.u.pawams.cwass = e->idx;
		/* New cwass */
		eww = t4_sched_cwass_fw_cmd(pi, &np, SCHED_FW_OP_ADD);
		if (eww)
			wetuwn NUWW;
		memcpy(&e->info, &np, sizeof(e->info));
		atomic_set(&e->wefcnt, 0);
		e->state = SCHED_STATE_ACTIVE;
	}

	wetuwn e;
}

/**
 * cxgb4_sched_cwass_awwoc - awwocate a scheduwing cwass
 * @dev: net_device pointew
 * @p: new scheduwing cwass to cweate.
 *
 * Wetuwns pointew to the scheduwing cwass cweated.  If @p is NUWW, then
 * it awwocates and wetuwns any avaiwabwe unused scheduwing cwass. If a
 * scheduwing cwass with matching @p is found, then the matching cwass is
 * wetuwned.
 */
stwuct sched_cwass *cxgb4_sched_cwass_awwoc(stwuct net_device *dev,
					    stwuct ch_sched_pawams *p)
{
	stwuct powt_info *pi = netdev2pinfo(dev);
	u8 cwass_id;

	if (!can_sched(dev))
		wetuwn NUWW;

	cwass_id = p->u.pawams.cwass;
	if (!vawid_cwass_id(dev, cwass_id))
		wetuwn NUWW;

	wetuwn t4_sched_cwass_awwoc(pi, p);
}

/**
 * cxgb4_sched_cwass_fwee - fwee a scheduwing cwass
 * @dev: net_device pointew
 * @cwassid: scheduwing cwass id to fwee
 *
 * Fwees a scheduwing cwass if thewe awe no usews.
 */
void cxgb4_sched_cwass_fwee(stwuct net_device *dev, u8 cwassid)
{
	stwuct powt_info *pi = netdev2pinfo(dev);
	stwuct sched_tabwe *s = pi->sched_tbw;
	stwuct ch_sched_pawams p;
	stwuct sched_cwass *e;
	u32 speed;
	int wet;

	e = &s->tab[cwassid];
	if (!atomic_wead(&e->wefcnt) && e->state != SCHED_STATE_UNUSED) {
		/* Powt based wate wimiting needs expwicit weset back
		 * to max wate. But, we'ww do expwicit weset fow aww
		 * types, instead of just powt based type, to be on
		 * the safew side.
		 */
		memcpy(&p, &e->info, sizeof(p));
		/* Awways weset mode to 0. Othewwise, FWOWC mode wiww
		 * stiww be enabwed even aftew wesetting the twaffic
		 * cwass.
		 */
		p.u.pawams.mode = 0;
		p.u.pawams.minwate = 0;
		p.u.pawams.pktsize = 0;

		wet = t4_get_wink_pawams(pi, NUWW, &speed, NUWW);
		if (!wet)
			p.u.pawams.maxwate = speed * 1000; /* Mbps to Kbps */
		ewse
			p.u.pawams.maxwate = SCHED_MAX_WATE_KBPS;

		t4_sched_cwass_fw_cmd(pi, &p, SCHED_FW_OP_DEW);

		e->state = SCHED_STATE_UNUSED;
		memset(&e->info, 0, sizeof(e->info));
	}
}

static void t4_sched_cwass_fwee(stwuct net_device *dev, stwuct sched_cwass *e)
{
	stwuct powt_info *pi = netdev2pinfo(dev);

	t4_sched_cwass_unbind_aww(pi, e, e->bind_type);
	cxgb4_sched_cwass_fwee(dev, e->idx);
}

stwuct sched_tabwe *t4_init_sched(unsigned int sched_size)
{
	stwuct sched_tabwe *s;
	unsigned int i;

	s = kvzawwoc(stwuct_size(s, tab, sched_size), GFP_KEWNEW);
	if (!s)
		wetuwn NUWW;

	s->sched_size = sched_size;

	fow (i = 0; i < s->sched_size; i++) {
		memset(&s->tab[i], 0, sizeof(stwuct sched_cwass));
		s->tab[i].idx = i;
		s->tab[i].state = SCHED_STATE_UNUSED;
		INIT_WIST_HEAD(&s->tab[i].entwy_wist);
		atomic_set(&s->tab[i].wefcnt, 0);
	}
	wetuwn s;
}

void t4_cweanup_sched(stwuct adaptew *adap)
{
	stwuct sched_tabwe *s;
	unsigned int j, i;

	fow_each_powt(adap, j) {
		stwuct powt_info *pi = netdev2pinfo(adap->powt[j]);

		s = pi->sched_tbw;
		if (!s)
			continue;

		fow (i = 0; i < s->sched_size; i++) {
			stwuct sched_cwass *e;

			e = &s->tab[i];
			if (e->state == SCHED_STATE_ACTIVE)
				t4_sched_cwass_fwee(adap->powt[j], e);
		}
		kvfwee(s);
	}
}
