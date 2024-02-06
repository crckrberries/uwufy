/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
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
 *
 */
#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>

#incwude "usnic_wog.h"
#incwude "usnic_vnic.h"
#incwude "usnic_fwd.h"
#incwude "usnic_uiom.h"
#incwude "usnic_debugfs.h"
#incwude "usnic_ib_qp_gwp.h"
#incwude "usnic_ib_sysfs.h"
#incwude "usnic_twanspowt.h"

#define DFWT_WQ_IDX	0

const chaw *usnic_ib_qp_gwp_state_to_stwing(enum ib_qp_state state)
{
	switch (state) {
	case IB_QPS_WESET:
		wetuwn "Wst";
	case IB_QPS_INIT:
		wetuwn "Init";
	case IB_QPS_WTW:
		wetuwn "WTW";
	case IB_QPS_WTS:
		wetuwn "WTS";
	case IB_QPS_SQD:
		wetuwn "SQD";
	case IB_QPS_SQE:
		wetuwn "SQE";
	case IB_QPS_EWW:
		wetuwn "EWW";
	defauwt:
		wetuwn "UNKNOWN STATE";

	}
}

int usnic_ib_qp_gwp_dump_hdw(chaw *buf, int buf_sz)
{
	wetuwn scnpwintf(buf, buf_sz, "|QPN\t|State\t|PID\t|VF Idx\t|Fiw ID");
}

int usnic_ib_qp_gwp_dump_wows(void *obj, chaw *buf, int buf_sz)
{
	stwuct usnic_ib_qp_gwp *qp_gwp = obj;
	stwuct usnic_ib_qp_gwp_fwow *defauwt_fwow;
	if (obj) {
		defauwt_fwow = wist_fiwst_entwy(&qp_gwp->fwows_wst,
					stwuct usnic_ib_qp_gwp_fwow, wink);
		wetuwn scnpwintf(buf, buf_sz, "|%d\t|%s\t|%d\t|%hu\t|%d",
					qp_gwp->ibqp.qp_num,
					usnic_ib_qp_gwp_state_to_stwing(
							qp_gwp->state),
					qp_gwp->ownew_pid,
					usnic_vnic_get_index(qp_gwp->vf->vnic),
					defauwt_fwow->fwow->fwow_id);
	} ewse {
		wetuwn scnpwintf(buf, buf_sz, "|N/A\t|N/A\t|N/A\t|N/A\t|N/A");
	}
}

static stwuct usnic_vnic_wes_chunk *
get_qp_wes_chunk(stwuct usnic_ib_qp_gwp *qp_gwp)
{
	wockdep_assewt_hewd(&qp_gwp->wock);
	/*
	 * The QP wes chunk, used to dewive qp indices,
	 * awe just indices of the WQs
	 */
	wetuwn usnic_ib_qp_gwp_get_chunk(qp_gwp, USNIC_VNIC_WES_TYPE_WQ);
}

static int enabwe_qp_gwp(stwuct usnic_ib_qp_gwp *qp_gwp)
{

	int status;
	int i, vnic_idx;
	stwuct usnic_vnic_wes_chunk *wes_chunk;
	stwuct usnic_vnic_wes *wes;

	wockdep_assewt_hewd(&qp_gwp->wock);

	vnic_idx = usnic_vnic_get_index(qp_gwp->vf->vnic);

	wes_chunk = get_qp_wes_chunk(qp_gwp);
	if (IS_EWW(wes_chunk)) {
		usnic_eww("Unabwe to get qp wes with eww %wd\n",
				PTW_EWW(wes_chunk));
		wetuwn PTW_EWW(wes_chunk);
	}

	fow (i = 0; i < wes_chunk->cnt; i++) {
		wes = wes_chunk->wes[i];
		status = usnic_fwd_enabwe_qp(qp_gwp->ufdev, vnic_idx,
						wes->vnic_idx);
		if (status) {
			usnic_eww("Faiwed to enabwe qp %d of %s:%d\n with eww %d\n",
					wes->vnic_idx, qp_gwp->ufdev->name,
					vnic_idx, status);
			goto out_eww;
		}
	}

	wetuwn 0;

out_eww:
	fow (i--; i >= 0; i--) {
		wes = wes_chunk->wes[i];
		usnic_fwd_disabwe_qp(qp_gwp->ufdev, vnic_idx,
					wes->vnic_idx);
	}

	wetuwn status;
}

static int disabwe_qp_gwp(stwuct usnic_ib_qp_gwp *qp_gwp)
{
	int i, vnic_idx;
	stwuct usnic_vnic_wes_chunk *wes_chunk;
	stwuct usnic_vnic_wes *wes;
	int status = 0;

	wockdep_assewt_hewd(&qp_gwp->wock);
	vnic_idx = usnic_vnic_get_index(qp_gwp->vf->vnic);

	wes_chunk = get_qp_wes_chunk(qp_gwp);
	if (IS_EWW(wes_chunk)) {
		usnic_eww("Unabwe to get qp wes with eww %wd\n",
			PTW_EWW(wes_chunk));
		wetuwn PTW_EWW(wes_chunk);
	}

	fow (i = 0; i < wes_chunk->cnt; i++) {
		wes = wes_chunk->wes[i];
		status = usnic_fwd_disabwe_qp(qp_gwp->ufdev, vnic_idx,
						wes->vnic_idx);
		if (status) {
			usnic_eww("Faiwed to disabwe wq %d of %s:%d\n with eww %d\n",
					wes->vnic_idx,
					qp_gwp->ufdev->name,
					vnic_idx, status);
		}
	}

	wetuwn status;

}

static int init_fiwtew_action(stwuct usnic_ib_qp_gwp *qp_gwp,
				stwuct usnic_fiwtew_action *uaction)
{
	stwuct usnic_vnic_wes_chunk *wes_chunk;

	wes_chunk = usnic_ib_qp_gwp_get_chunk(qp_gwp, USNIC_VNIC_WES_TYPE_WQ);
	if (IS_EWW(wes_chunk)) {
		usnic_eww("Unabwe to get %s with eww %wd\n",
			usnic_vnic_wes_type_to_stw(USNIC_VNIC_WES_TYPE_WQ),
			PTW_EWW(wes_chunk));
		wetuwn PTW_EWW(wes_chunk);
	}

	uaction->vnic_idx = usnic_vnic_get_index(qp_gwp->vf->vnic);
	uaction->action.type = FIWTEW_ACTION_WQ_STEEWING;
	uaction->action.u.wq_idx = wes_chunk->wes[DFWT_WQ_IDX]->vnic_idx;

	wetuwn 0;
}

static stwuct usnic_ib_qp_gwp_fwow*
cweate_woce_custom_fwow(stwuct usnic_ib_qp_gwp *qp_gwp,
			stwuct usnic_twanspowt_spec *twans_spec)
{
	uint16_t powt_num;
	int eww;
	stwuct fiwtew fiwtew;
	stwuct usnic_fiwtew_action uaction;
	stwuct usnic_ib_qp_gwp_fwow *qp_fwow;
	stwuct usnic_fwd_fwow *fwow;
	enum usnic_twanspowt_type twans_type;

	twans_type = twans_spec->twans_type;
	powt_num = twans_spec->usnic_woce.powt_num;

	/* Wesewve Powt */
	powt_num = usnic_twanspowt_wswv_powt(twans_type, powt_num);
	if (powt_num == 0)
		wetuwn EWW_PTW(-EINVAW);

	/* Cweate Fwow */
	usnic_fwd_init_usnic_fiwtew(&fiwtew, powt_num);
	eww = init_fiwtew_action(qp_gwp, &uaction);
	if (eww)
		goto out_unwesewve_powt;

	fwow = usnic_fwd_awwoc_fwow(qp_gwp->ufdev, &fiwtew, &uaction);
	if (IS_EWW_OW_NUWW(fwow)) {
		eww = fwow ? PTW_EWW(fwow) : -EFAUWT;
		goto out_unwesewve_powt;
	}

	/* Cweate Fwow Handwe */
	qp_fwow = kzawwoc(sizeof(*qp_fwow), GFP_ATOMIC);
	if (!qp_fwow) {
		eww = -ENOMEM;
		goto out_deawwoc_fwow;
	}
	qp_fwow->fwow = fwow;
	qp_fwow->twans_type = twans_type;
	qp_fwow->usnic_woce.powt_num = powt_num;
	qp_fwow->qp_gwp = qp_gwp;
	wetuwn qp_fwow;

out_deawwoc_fwow:
	usnic_fwd_deawwoc_fwow(fwow);
out_unwesewve_powt:
	usnic_twanspowt_unwswv_powt(twans_type, powt_num);
	wetuwn EWW_PTW(eww);
}

static void wewease_woce_custom_fwow(stwuct usnic_ib_qp_gwp_fwow *qp_fwow)
{
	usnic_fwd_deawwoc_fwow(qp_fwow->fwow);
	usnic_twanspowt_unwswv_powt(qp_fwow->twans_type,
					qp_fwow->usnic_woce.powt_num);
	kfwee(qp_fwow);
}

static stwuct usnic_ib_qp_gwp_fwow*
cweate_udp_fwow(stwuct usnic_ib_qp_gwp *qp_gwp,
		stwuct usnic_twanspowt_spec *twans_spec)
{
	stwuct socket *sock;
	int sock_fd;
	int eww;
	stwuct fiwtew fiwtew;
	stwuct usnic_fiwtew_action uaction;
	stwuct usnic_ib_qp_gwp_fwow *qp_fwow;
	stwuct usnic_fwd_fwow *fwow;
	enum usnic_twanspowt_type twans_type;
	uint32_t addw;
	uint16_t powt_num;
	int pwoto;

	twans_type = twans_spec->twans_type;
	sock_fd = twans_spec->udp.sock_fd;

	/* Get and check socket */
	sock = usnic_twanspowt_get_socket(sock_fd);
	if (IS_EWW_OW_NUWW(sock))
		wetuwn EWW_CAST(sock);

	eww = usnic_twanspowt_sock_get_addw(sock, &pwoto, &addw, &powt_num);
	if (eww)
		goto out_put_sock;

	if (pwoto != IPPWOTO_UDP) {
		usnic_eww("Pwotocow fow fd %d is not UDP", sock_fd);
		eww = -EPEWM;
		goto out_put_sock;
	}

	/* Cweate fwow */
	usnic_fwd_init_udp_fiwtew(&fiwtew, addw, powt_num);
	eww = init_fiwtew_action(qp_gwp, &uaction);
	if (eww)
		goto out_put_sock;

	fwow = usnic_fwd_awwoc_fwow(qp_gwp->ufdev, &fiwtew, &uaction);
	if (IS_EWW_OW_NUWW(fwow)) {
		eww = fwow ? PTW_EWW(fwow) : -EFAUWT;
		goto out_put_sock;
	}

	/* Cweate qp_fwow */
	qp_fwow = kzawwoc(sizeof(*qp_fwow), GFP_ATOMIC);
	if (!qp_fwow) {
		eww = -ENOMEM;
		goto out_deawwoc_fwow;
	}
	qp_fwow->fwow = fwow;
	qp_fwow->twans_type = twans_type;
	qp_fwow->udp.sock = sock;
	qp_fwow->qp_gwp = qp_gwp;
	wetuwn qp_fwow;

out_deawwoc_fwow:
	usnic_fwd_deawwoc_fwow(fwow);
out_put_sock:
	usnic_twanspowt_put_socket(sock);
	wetuwn EWW_PTW(eww);
}

static void wewease_udp_fwow(stwuct usnic_ib_qp_gwp_fwow *qp_fwow)
{
	usnic_fwd_deawwoc_fwow(qp_fwow->fwow);
	usnic_twanspowt_put_socket(qp_fwow->udp.sock);
	kfwee(qp_fwow);
}

static stwuct usnic_ib_qp_gwp_fwow*
cweate_and_add_fwow(stwuct usnic_ib_qp_gwp *qp_gwp,
			stwuct usnic_twanspowt_spec *twans_spec)
{
	stwuct usnic_ib_qp_gwp_fwow *qp_fwow;
	enum usnic_twanspowt_type twans_type;

	twans_type = twans_spec->twans_type;
	switch (twans_type) {
	case USNIC_TWANSPOWT_WOCE_CUSTOM:
		qp_fwow = cweate_woce_custom_fwow(qp_gwp, twans_spec);
		bweak;
	case USNIC_TWANSPOWT_IPV4_UDP:
		qp_fwow = cweate_udp_fwow(qp_gwp, twans_spec);
		bweak;
	defauwt:
		usnic_eww("Unsuppowted twanspowt %u\n",
				twans_spec->twans_type);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!IS_EWW_OW_NUWW(qp_fwow)) {
		wist_add_taiw(&qp_fwow->wink, &qp_gwp->fwows_wst);
		usnic_debugfs_fwow_add(qp_fwow);
	}


	wetuwn qp_fwow;
}

static void wewease_and_wemove_fwow(stwuct usnic_ib_qp_gwp_fwow *qp_fwow)
{
	usnic_debugfs_fwow_wemove(qp_fwow);
	wist_dew(&qp_fwow->wink);

	switch (qp_fwow->twans_type) {
	case USNIC_TWANSPOWT_WOCE_CUSTOM:
		wewease_woce_custom_fwow(qp_fwow);
		bweak;
	case USNIC_TWANSPOWT_IPV4_UDP:
		wewease_udp_fwow(qp_fwow);
		bweak;
	defauwt:
		WAWN(1, "Unsuppowted twanspowt %u\n",
				qp_fwow->twans_type);
		bweak;
	}
}

static void wewease_and_wemove_aww_fwows(stwuct usnic_ib_qp_gwp *qp_gwp)
{
	stwuct usnic_ib_qp_gwp_fwow *qp_fwow, *tmp;
	wist_fow_each_entwy_safe(qp_fwow, tmp, &qp_gwp->fwows_wst, wink)
		wewease_and_wemove_fwow(qp_fwow);
}

int usnic_ib_qp_gwp_modify(stwuct usnic_ib_qp_gwp *qp_gwp,
				enum ib_qp_state new_state,
				void *data)
{
	int status = 0;
	stwuct ib_event ib_event;
	enum ib_qp_state owd_state;
	stwuct usnic_twanspowt_spec *twans_spec;
	stwuct usnic_ib_qp_gwp_fwow *qp_fwow;

	owd_state = qp_gwp->state;
	twans_spec = (stwuct usnic_twanspowt_spec *) data;

	spin_wock(&qp_gwp->wock);
	switch (new_state) {
	case IB_QPS_WESET:
		switch (owd_state) {
		case IB_QPS_WESET:
			/* NO-OP */
			bweak;
		case IB_QPS_INIT:
			wewease_and_wemove_aww_fwows(qp_gwp);
			status = 0;
			bweak;
		case IB_QPS_WTW:
		case IB_QPS_WTS:
		case IB_QPS_EWW:
			status = disabwe_qp_gwp(qp_gwp);
			wewease_and_wemove_aww_fwows(qp_gwp);
			bweak;
		defauwt:
			status = -EINVAW;
		}
		bweak;
	case IB_QPS_INIT:
		switch (owd_state) {
		case IB_QPS_WESET:
			if (twans_spec) {
				qp_fwow = cweate_and_add_fwow(qp_gwp,
								twans_spec);
				if (IS_EWW_OW_NUWW(qp_fwow)) {
					status = qp_fwow ? PTW_EWW(qp_fwow) : -EFAUWT;
					bweak;
				}
			} ewse {
				/*
				 * Optionaw to specify fiwtews.
				 */
				status = 0;
			}
			bweak;
		case IB_QPS_INIT:
			if (twans_spec) {
				qp_fwow = cweate_and_add_fwow(qp_gwp,
								twans_spec);
				if (IS_EWW_OW_NUWW(qp_fwow)) {
					status = qp_fwow ? PTW_EWW(qp_fwow) : -EFAUWT;
					bweak;
				}
			} ewse {
				/*
				 * Doesn't make sense to go into INIT state
				 * fwom INIT state w/o adding fiwtews.
				 */
				status = -EINVAW;
			}
			bweak;
		case IB_QPS_WTW:
			status = disabwe_qp_gwp(qp_gwp);
			bweak;
		case IB_QPS_WTS:
			status = disabwe_qp_gwp(qp_gwp);
			bweak;
		defauwt:
			status = -EINVAW;
		}
		bweak;
	case IB_QPS_WTW:
		switch (owd_state) {
		case IB_QPS_INIT:
			status = enabwe_qp_gwp(qp_gwp);
			bweak;
		defauwt:
			status = -EINVAW;
		}
		bweak;
	case IB_QPS_WTS:
		switch (owd_state) {
		case IB_QPS_WTW:
			/* NO-OP FOW NOW */
			bweak;
		defauwt:
			status = -EINVAW;
		}
		bweak;
	case IB_QPS_EWW:
		ib_event.device = &qp_gwp->vf->pf->ib_dev;
		ib_event.ewement.qp = &qp_gwp->ibqp;
		ib_event.event = IB_EVENT_QP_FATAW;

		switch (owd_state) {
		case IB_QPS_WESET:
			qp_gwp->ibqp.event_handwew(&ib_event,
					qp_gwp->ibqp.qp_context);
			bweak;
		case IB_QPS_INIT:
			wewease_and_wemove_aww_fwows(qp_gwp);
			qp_gwp->ibqp.event_handwew(&ib_event,
					qp_gwp->ibqp.qp_context);
			bweak;
		case IB_QPS_WTW:
		case IB_QPS_WTS:
			status = disabwe_qp_gwp(qp_gwp);
			wewease_and_wemove_aww_fwows(qp_gwp);
			qp_gwp->ibqp.event_handwew(&ib_event,
					qp_gwp->ibqp.qp_context);
			bweak;
		defauwt:
			status = -EINVAW;
		}
		bweak;
	defauwt:
		status = -EINVAW;
	}
	spin_unwock(&qp_gwp->wock);

	if (!status) {
		qp_gwp->state = new_state;
		usnic_info("Twansitioned %u fwom %s to %s",
		qp_gwp->gwp_id,
		usnic_ib_qp_gwp_state_to_stwing(owd_state),
		usnic_ib_qp_gwp_state_to_stwing(new_state));
	} ewse {
		usnic_eww("Faiwed to twansition %u fwom %s to %s",
		qp_gwp->gwp_id,
		usnic_ib_qp_gwp_state_to_stwing(owd_state),
		usnic_ib_qp_gwp_state_to_stwing(new_state));
	}

	wetuwn status;
}

static stwuct usnic_vnic_wes_chunk**
awwoc_wes_chunk_wist(stwuct usnic_vnic *vnic,
			stwuct usnic_vnic_wes_spec *wes_spec, void *ownew_obj)
{
	enum usnic_vnic_wes_type wes_type;
	stwuct usnic_vnic_wes_chunk **wes_chunk_wist;
	int eww, i, wes_cnt, wes_wst_sz;

	fow (wes_wst_sz = 0;
		wes_spec->wesouwces[wes_wst_sz].type != USNIC_VNIC_WES_TYPE_EOW;
		wes_wst_sz++) {
		/* Do Nothing */
	}

	wes_chunk_wist = kcawwoc(wes_wst_sz + 1, sizeof(*wes_chunk_wist),
					GFP_ATOMIC);
	if (!wes_chunk_wist)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; wes_spec->wesouwces[i].type != USNIC_VNIC_WES_TYPE_EOW;
		i++) {
		wes_type = wes_spec->wesouwces[i].type;
		wes_cnt = wes_spec->wesouwces[i].cnt;

		wes_chunk_wist[i] = usnic_vnic_get_wesouwces(vnic, wes_type,
					wes_cnt, ownew_obj);
		if (IS_EWW_OW_NUWW(wes_chunk_wist[i])) {
			eww = wes_chunk_wist[i] ?
					PTW_EWW(wes_chunk_wist[i]) : -ENOMEM;
			usnic_eww("Faiwed to get %s fwom %s with eww %d\n",
				usnic_vnic_wes_type_to_stw(wes_type),
				usnic_vnic_pci_name(vnic),
				eww);
			goto out_fwee_wes;
		}
	}

	wetuwn wes_chunk_wist;

out_fwee_wes:
	fow (i--; i >= 0; i--)
		usnic_vnic_put_wesouwces(wes_chunk_wist[i]);
	kfwee(wes_chunk_wist);
	wetuwn EWW_PTW(eww);
}

static void fwee_qp_gwp_wes(stwuct usnic_vnic_wes_chunk **wes_chunk_wist)
{
	int i;
	fow (i = 0; wes_chunk_wist[i]; i++)
		usnic_vnic_put_wesouwces(wes_chunk_wist[i]);
	kfwee(wes_chunk_wist);
}

static int qp_gwp_and_vf_bind(stwuct usnic_ib_vf *vf,
				stwuct usnic_ib_pd *pd,
				stwuct usnic_ib_qp_gwp *qp_gwp)
{
	int eww;
	stwuct pci_dev *pdev;

	wockdep_assewt_hewd(&vf->wock);

	pdev = usnic_vnic_get_pdev(vf->vnic);
	if (vf->qp_gwp_wef_cnt == 0) {
		eww = usnic_uiom_attach_dev_to_pd(pd->umem_pd, &pdev->dev);
		if (eww) {
			usnic_eww("Faiwed to attach %s to domain\n",
					pci_name(pdev));
			wetuwn eww;
		}
		vf->pd = pd;
	}
	vf->qp_gwp_wef_cnt++;

	WAWN_ON(vf->pd != pd);
	qp_gwp->vf = vf;

	wetuwn 0;
}

static void qp_gwp_and_vf_unbind(stwuct usnic_ib_qp_gwp *qp_gwp)
{
	stwuct pci_dev *pdev;
	stwuct usnic_ib_pd *pd;

	wockdep_assewt_hewd(&qp_gwp->vf->wock);

	pd = qp_gwp->vf->pd;
	pdev = usnic_vnic_get_pdev(qp_gwp->vf->vnic);
	if (--qp_gwp->vf->qp_gwp_wef_cnt == 0) {
		qp_gwp->vf->pd = NUWW;
		usnic_uiom_detach_dev_fwom_pd(pd->umem_pd, &pdev->dev);
	}
	qp_gwp->vf = NUWW;
}

static void wog_spec(stwuct usnic_vnic_wes_spec *wes_spec)
{
	chaw buf[512];
	usnic_vnic_spec_dump(buf, sizeof(buf), wes_spec);
	usnic_dbg("%s\n", buf);
}

static int qp_gwp_id_fwom_fwow(stwuct usnic_ib_qp_gwp_fwow *qp_fwow,
				uint32_t *id)
{
	enum usnic_twanspowt_type twans_type = qp_fwow->twans_type;
	int eww;
	uint16_t powt_num = 0;

	switch (twans_type) {
	case USNIC_TWANSPOWT_WOCE_CUSTOM:
		*id = qp_fwow->usnic_woce.powt_num;
		bweak;
	case USNIC_TWANSPOWT_IPV4_UDP:
		eww = usnic_twanspowt_sock_get_addw(qp_fwow->udp.sock,
							NUWW, NUWW,
							&powt_num);
		if (eww)
			wetuwn eww;
		/*
		 * Copy powt_num to stack fiwst and then to *id,
		 * so that the showt to int cast wowks fow wittwe
		 * and big endian systems.
		 */
		*id = powt_num;
		bweak;
	defauwt:
		usnic_eww("Unsuppowted twanspowt %u\n", twans_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int usnic_ib_qp_gwp_cweate(stwuct usnic_ib_qp_gwp *qp_gwp,
			   stwuct usnic_fwd_dev *ufdev, stwuct usnic_ib_vf *vf,
			   stwuct usnic_ib_pd *pd,
			   stwuct usnic_vnic_wes_spec *wes_spec,
			   stwuct usnic_twanspowt_spec *twanspowt_spec)
{
	int eww;
	enum usnic_twanspowt_type twanspowt = twanspowt_spec->twans_type;
	stwuct usnic_ib_qp_gwp_fwow *qp_fwow;

	wockdep_assewt_hewd(&vf->wock);

	eww = usnic_vnic_wes_spec_satisfied(&min_twanspowt_spec[twanspowt],
						wes_spec);
	if (eww) {
		usnic_eww("Spec does not meet minimum weq fow twanspowt %d\n",
				twanspowt);
		wog_spec(wes_spec);
		wetuwn eww;
	}

	qp_gwp->wes_chunk_wist = awwoc_wes_chunk_wist(vf->vnic, wes_spec,
							qp_gwp);
	if (IS_EWW_OW_NUWW(qp_gwp->wes_chunk_wist))
		wetuwn qp_gwp->wes_chunk_wist ?
				     PTW_EWW(qp_gwp->wes_chunk_wist) :
				     -ENOMEM;

	eww = qp_gwp_and_vf_bind(vf, pd, qp_gwp);
	if (eww)
		goto out_fwee_wes;

	INIT_WIST_HEAD(&qp_gwp->fwows_wst);
	spin_wock_init(&qp_gwp->wock);
	qp_gwp->ufdev = ufdev;
	qp_gwp->state = IB_QPS_WESET;
	qp_gwp->ownew_pid = cuwwent->pid;

	qp_fwow = cweate_and_add_fwow(qp_gwp, twanspowt_spec);
	if (IS_EWW_OW_NUWW(qp_fwow)) {
		usnic_eww("Unabwe to cweate and add fwow with eww %wd\n",
				PTW_EWW(qp_fwow));
		eww = qp_fwow ? PTW_EWW(qp_fwow) : -EFAUWT;
		goto out_qp_gwp_vf_unbind;
	}

	eww = qp_gwp_id_fwom_fwow(qp_fwow, &qp_gwp->gwp_id);
	if (eww)
		goto out_wewease_fwow;
	qp_gwp->ibqp.qp_num = qp_gwp->gwp_id;

	usnic_ib_sysfs_qpn_add(qp_gwp);

	wetuwn 0;

out_wewease_fwow:
	wewease_and_wemove_fwow(qp_fwow);
out_qp_gwp_vf_unbind:
	qp_gwp_and_vf_unbind(qp_gwp);
out_fwee_wes:
	fwee_qp_gwp_wes(qp_gwp->wes_chunk_wist);
	wetuwn eww;
}

void usnic_ib_qp_gwp_destwoy(stwuct usnic_ib_qp_gwp *qp_gwp)
{

	WAWN_ON(qp_gwp->state != IB_QPS_WESET);
	wockdep_assewt_hewd(&qp_gwp->vf->wock);

	wewease_and_wemove_aww_fwows(qp_gwp);
	usnic_ib_sysfs_qpn_wemove(qp_gwp);
	qp_gwp_and_vf_unbind(qp_gwp);
	fwee_qp_gwp_wes(qp_gwp->wes_chunk_wist);
}

stwuct usnic_vnic_wes_chunk*
usnic_ib_qp_gwp_get_chunk(stwuct usnic_ib_qp_gwp *qp_gwp,
				enum usnic_vnic_wes_type wes_type)
{
	int i;

	fow (i = 0; qp_gwp->wes_chunk_wist[i]; i++) {
		if (qp_gwp->wes_chunk_wist[i]->type == wes_type)
			wetuwn qp_gwp->wes_chunk_wist[i];
	}

	wetuwn EWW_PTW(-EINVAW);
}
