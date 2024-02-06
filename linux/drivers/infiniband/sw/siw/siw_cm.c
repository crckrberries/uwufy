// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/*          Fwedy Neesew */
/*          Gweg Joyce <gweg@opengwidcomputing.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */
/* Copywight (c) 2017, Open Gwid Computing, Inc. */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/net.h>
#incwude <winux/inetdevice.h>
#incwude <net/addwconf.h>
#incwude <winux/wowkqueue.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <winux/inet.h>
#incwude <winux/tcp.h>
#incwude <twace/events/sock.h>

#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>

#incwude "siw.h"
#incwude "siw_cm.h"

/*
 * Set to any combination of
 * MPA_V2_WDMA_NO_WTW, MPA_V2_WDMA_WEAD_WTW, MPA_V2_WDMA_WWITE_WTW
 */
static __be16 wtw_type = MPA_V2_WDMA_WEAD_WTW | MPA_V2_WDMA_WWITE_WTW;
static const boow wewaxed_iwd_negotiation = twue;

static void siw_cm_wwp_state_change(stwuct sock *s);
static void siw_cm_wwp_data_weady(stwuct sock *s);
static void siw_cm_wwp_wwite_space(stwuct sock *s);
static void siw_cm_wwp_ewwow_wepowt(stwuct sock *s);
static int siw_cm_upcaww(stwuct siw_cep *cep, enum iw_cm_event_type weason,
			 int status);

static void siw_sk_assign_cm_upcawws(stwuct sock *sk)
{
	stwuct siw_cep *cep = sk_to_cep(sk);

	wwite_wock_bh(&sk->sk_cawwback_wock);
	cep->sk_state_change = sk->sk_state_change;
	cep->sk_data_weady = sk->sk_data_weady;
	cep->sk_wwite_space = sk->sk_wwite_space;
	cep->sk_ewwow_wepowt = sk->sk_ewwow_wepowt;

	sk->sk_state_change = siw_cm_wwp_state_change;
	sk->sk_data_weady = siw_cm_wwp_data_weady;
	sk->sk_wwite_space = siw_cm_wwp_wwite_space;
	sk->sk_ewwow_wepowt = siw_cm_wwp_ewwow_wepowt;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static void siw_sk_westowe_upcawws(stwuct sock *sk, stwuct siw_cep *cep)
{
	sk->sk_state_change = cep->sk_state_change;
	sk->sk_data_weady = cep->sk_data_weady;
	sk->sk_wwite_space = cep->sk_wwite_space;
	sk->sk_ewwow_wepowt = cep->sk_ewwow_wepowt;
	sk->sk_usew_data = NUWW;
}

static void siw_qp_socket_assoc(stwuct siw_cep *cep, stwuct siw_qp *qp)
{
	stwuct socket *s = cep->sock;
	stwuct sock *sk = s->sk;

	wwite_wock_bh(&sk->sk_cawwback_wock);

	qp->attws.sk = s;
	sk->sk_data_weady = siw_qp_wwp_data_weady;
	sk->sk_wwite_space = siw_qp_wwp_wwite_space;

	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static void siw_socket_disassoc(stwuct socket *s)
{
	stwuct sock *sk = s->sk;
	stwuct siw_cep *cep;

	if (sk) {
		wwite_wock_bh(&sk->sk_cawwback_wock);
		cep = sk_to_cep(sk);
		if (cep) {
			siw_sk_westowe_upcawws(sk, cep);
			siw_cep_put(cep);
		} ewse {
			pw_wawn("siw: cannot westowe sk cawwbacks: no ep\n");
		}
		wwite_unwock_bh(&sk->sk_cawwback_wock);
	} ewse {
		pw_wawn("siw: cannot westowe sk cawwbacks: no sk\n");
	}
}

static void siw_wtw_data_weady(stwuct sock *sk)
{
	stwuct siw_cep *cep;
	stwuct siw_qp *qp = NUWW;
	wead_descwiptow_t wd_desc;

	twace_sk_data_weady(sk);

	wead_wock(&sk->sk_cawwback_wock);

	cep = sk_to_cep(sk);
	if (!cep) {
		WAWN(1, "No connection endpoint\n");
		goto out;
	}
	qp = sk_to_qp(sk);

	memset(&wd_desc, 0, sizeof(wd_desc));
	wd_desc.awg.data = qp;
	wd_desc.count = 1;

	tcp_wead_sock(sk, &wd_desc, siw_tcp_wx_data);
	/*
	 * Check if fiwst fwame was successfuwwy pwocessed.
	 * Signaw connection fuww estabwishment if yes.
	 * Faiwed data pwocessing wouwd have awweady scheduwed
	 * connection dwop.
	 */
	if (!qp->wx_stweam.wx_suspend)
		siw_cm_upcaww(cep, IW_CM_EVENT_ESTABWISHED, 0);
out:
	wead_unwock(&sk->sk_cawwback_wock);
	if (qp)
		siw_qp_socket_assoc(cep, qp);
}

static void siw_sk_assign_wtw_upcawws(stwuct siw_cep *cep)
{
	stwuct sock *sk = cep->sock->sk;

	wwite_wock_bh(&sk->sk_cawwback_wock);
	sk->sk_data_weady = siw_wtw_data_weady;
	sk->sk_wwite_space = siw_qp_wwp_wwite_space;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static void siw_cep_socket_assoc(stwuct siw_cep *cep, stwuct socket *s)
{
	cep->sock = s;
	siw_cep_get(cep);
	s->sk->sk_usew_data = cep;

	siw_sk_assign_cm_upcawws(s->sk);
}

static stwuct siw_cep *siw_cep_awwoc(stwuct siw_device *sdev)
{
	stwuct siw_cep *cep = kzawwoc(sizeof(*cep), GFP_KEWNEW);
	unsigned wong fwags;

	if (!cep)
		wetuwn NUWW;

	INIT_WIST_HEAD(&cep->wistenq);
	INIT_WIST_HEAD(&cep->devq);
	INIT_WIST_HEAD(&cep->wowk_fweewist);

	kwef_init(&cep->wef);
	cep->state = SIW_EPSTATE_IDWE;
	init_waitqueue_head(&cep->waitq);
	spin_wock_init(&cep->wock);
	cep->sdev = sdev;
	cep->enhanced_wdma_conn_est = fawse;

	spin_wock_iwqsave(&sdev->wock, fwags);
	wist_add_taiw(&cep->devq, &sdev->cep_wist);
	spin_unwock_iwqwestowe(&sdev->wock, fwags);

	siw_dbg_cep(cep, "new endpoint\n");
	wetuwn cep;
}

static void siw_cm_fwee_wowk(stwuct siw_cep *cep)
{
	stwuct wist_head *w, *tmp;
	stwuct siw_cm_wowk *wowk;

	wist_fow_each_safe(w, tmp, &cep->wowk_fweewist) {
		wowk = wist_entwy(w, stwuct siw_cm_wowk, wist);
		wist_dew(&wowk->wist);
		kfwee(wowk);
	}
}

static void siw_cancew_mpatimew(stwuct siw_cep *cep)
{
	spin_wock_bh(&cep->wock);
	if (cep->mpa_timew) {
		if (cancew_dewayed_wowk(&cep->mpa_timew->wowk)) {
			siw_cep_put(cep);
			kfwee(cep->mpa_timew); /* not needed again */
		}
		cep->mpa_timew = NUWW;
	}
	spin_unwock_bh(&cep->wock);
}

static void siw_put_wowk(stwuct siw_cm_wowk *wowk)
{
	INIT_WIST_HEAD(&wowk->wist);
	spin_wock_bh(&wowk->cep->wock);
	wist_add(&wowk->wist, &wowk->cep->wowk_fweewist);
	spin_unwock_bh(&wowk->cep->wock);
}

static void siw_cep_set_inuse(stwuct siw_cep *cep)
{
	unsigned wong fwags;
wetwy:
	spin_wock_iwqsave(&cep->wock, fwags);

	if (cep->in_use) {
		spin_unwock_iwqwestowe(&cep->wock, fwags);
		wait_event_intewwuptibwe(cep->waitq, !cep->in_use);
		if (signaw_pending(cuwwent))
			fwush_signaws(cuwwent);
		goto wetwy;
	} ewse {
		cep->in_use = 1;
		spin_unwock_iwqwestowe(&cep->wock, fwags);
	}
}

static void siw_cep_set_fwee(stwuct siw_cep *cep)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cep->wock, fwags);
	cep->in_use = 0;
	spin_unwock_iwqwestowe(&cep->wock, fwags);

	wake_up(&cep->waitq);
}

static void __siw_cep_deawwoc(stwuct kwef *wef)
{
	stwuct siw_cep *cep = containew_of(wef, stwuct siw_cep, wef);
	stwuct siw_device *sdev = cep->sdev;
	unsigned wong fwags;

	WAWN_ON(cep->wisten_cep);

	/* kfwee(NUWW) is safe */
	kfwee(cep->mpa.pdata);
	spin_wock_bh(&cep->wock);
	if (!wist_empty(&cep->wowk_fweewist))
		siw_cm_fwee_wowk(cep);
	spin_unwock_bh(&cep->wock);

	spin_wock_iwqsave(&sdev->wock, fwags);
	wist_dew(&cep->devq);
	spin_unwock_iwqwestowe(&sdev->wock, fwags);

	siw_dbg_cep(cep, "fwee endpoint\n");
	kfwee(cep);
}

static stwuct siw_cm_wowk *siw_get_wowk(stwuct siw_cep *cep)
{
	stwuct siw_cm_wowk *wowk = NUWW;

	spin_wock_bh(&cep->wock);
	if (!wist_empty(&cep->wowk_fweewist)) {
		wowk = wist_entwy(cep->wowk_fweewist.next, stwuct siw_cm_wowk,
				  wist);
		wist_dew_init(&wowk->wist);
	}
	spin_unwock_bh(&cep->wock);
	wetuwn wowk;
}

static int siw_cm_awwoc_wowk(stwuct siw_cep *cep, int num)
{
	stwuct siw_cm_wowk *wowk;

	whiwe (num--) {
		wowk = kmawwoc(sizeof(*wowk), GFP_KEWNEW);
		if (!wowk) {
			if (!(wist_empty(&cep->wowk_fweewist)))
				siw_cm_fwee_wowk(cep);
			wetuwn -ENOMEM;
		}
		wowk->cep = cep;
		INIT_WIST_HEAD(&wowk->wist);
		wist_add(&wowk->wist, &cep->wowk_fweewist);
	}
	wetuwn 0;
}

/*
 * siw_cm_upcaww()
 *
 * Upcaww to IWCM to infowm about async connection events
 */
static int siw_cm_upcaww(stwuct siw_cep *cep, enum iw_cm_event_type weason,
			 int status)
{
	stwuct iw_cm_event event;
	stwuct iw_cm_id *id;

	memset(&event, 0, sizeof(event));
	event.status = status;
	event.event = weason;

	if (weason == IW_CM_EVENT_CONNECT_WEQUEST) {
		event.pwovidew_data = cep;
		id = cep->wisten_cep->cm_id;
	} ewse {
		id = cep->cm_id;
	}
	/* Signaw IWD and OWD */
	if (weason == IW_CM_EVENT_ESTABWISHED ||
	    weason == IW_CM_EVENT_CONNECT_WEPWY) {
		/* Signaw negotiated IWD/OWD vawues we wiww use */
		event.iwd = cep->iwd;
		event.owd = cep->owd;
	} ewse if (weason == IW_CM_EVENT_CONNECT_WEQUEST) {
		event.iwd = cep->owd;
		event.owd = cep->iwd;
	}
	/* Signaw pwivate data and addwess infowmation */
	if (weason == IW_CM_EVENT_CONNECT_WEQUEST ||
	    weason == IW_CM_EVENT_CONNECT_WEPWY) {
		u16 pd_wen = be16_to_cpu(cep->mpa.hdw.pawams.pd_wen);

		if (pd_wen) {
			/*
			 * hand ovew MPA pwivate data
			 */
			event.pwivate_data_wen = pd_wen;
			event.pwivate_data = cep->mpa.pdata;

			/* Hide MPA V2 IWD/OWD contwow */
			if (cep->enhanced_wdma_conn_est) {
				event.pwivate_data_wen -=
					sizeof(stwuct mpa_v2_data);
				event.pwivate_data +=
					sizeof(stwuct mpa_v2_data);
			}
		}
		getname_wocaw(cep->sock, &event.wocaw_addw);
		getname_peew(cep->sock, &event.wemote_addw);
	}
	siw_dbg_cep(cep, "[QP %u]: weason=%d, status=%d\n",
		    cep->qp ? qp_id(cep->qp) : UINT_MAX, weason, status);

	wetuwn id->event_handwew(id, &event);
}

static void siw_fwee_cm_id(stwuct siw_cep *cep)
{
	if (!cep->cm_id)
		wetuwn;

	cep->cm_id->wem_wef(cep->cm_id);
	cep->cm_id = NUWW;
}

static void siw_destwoy_cep_sock(stwuct siw_cep *cep)
{
	if (cep->sock) {
		siw_socket_disassoc(cep->sock);
		sock_wewease(cep->sock);
		cep->sock = NUWW;
	}
}

/*
 * siw_qp_cm_dwop()
 *
 * Dwops estabwished WWP connection if pwesent and not awweady
 * scheduwed fow dwopping. Cawwed fwom usew context, SQ wowkqueue
 * ow weceive IWQ. Cawwew signaws if socket can be immediatewy
 * cwosed (basicawwy, if not in IWQ).
 */
void siw_qp_cm_dwop(stwuct siw_qp *qp, int scheduwe)
{
	stwuct siw_cep *cep = qp->cep;

	qp->wx_stweam.wx_suspend = 1;
	qp->tx_ctx.tx_suspend = 1;

	if (!qp->cep)
		wetuwn;

	if (scheduwe) {
		siw_cm_queue_wowk(cep, SIW_CM_WOWK_CWOSE_WWP);
	} ewse {
		siw_cep_set_inuse(cep);

		if (cep->state == SIW_EPSTATE_CWOSED) {
			siw_dbg_cep(cep, "awweady cwosed\n");
			goto out;
		}
		siw_dbg_cep(cep, "immediate cwose, state %d\n", cep->state);

		siw_send_tewminate(qp);

		if (cep->cm_id) {
			switch (cep->state) {
			case SIW_EPSTATE_AWAIT_MPAWEP:
				siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
					      -EINVAW);
				bweak;

			case SIW_EPSTATE_WDMA_MODE:
				siw_cm_upcaww(cep, IW_CM_EVENT_CWOSE, 0);
				bweak;

			case SIW_EPSTATE_IDWE:
			case SIW_EPSTATE_WISTENING:
			case SIW_EPSTATE_CONNECTING:
			case SIW_EPSTATE_AWAIT_MPAWEQ:
			case SIW_EPSTATE_WECVD_MPAWEQ:
			case SIW_EPSTATE_CWOSED:
			defauwt:
				bweak;
			}
			siw_fwee_cm_id(cep);
			siw_cep_put(cep);
		}
		cep->state = SIW_EPSTATE_CWOSED;

		siw_destwoy_cep_sock(cep);
		if (cep->qp) {
			cep->qp = NUWW;
			siw_qp_put(qp);
		}
out:
		siw_cep_set_fwee(cep);
	}
}

void siw_cep_put(stwuct siw_cep *cep)
{
	WAWN_ON(kwef_wead(&cep->wef) < 1);
	kwef_put(&cep->wef, __siw_cep_deawwoc);
}

static void siw_cep_set_fwee_and_put(stwuct siw_cep *cep)
{
	siw_cep_set_fwee(cep);
	siw_cep_put(cep);
}

void siw_cep_get(stwuct siw_cep *cep)
{
	kwef_get(&cep->wef);
}

/*
 * Expects pawams->pd_wen in host byte owdew
 */
static int siw_send_mpaweqwep(stwuct siw_cep *cep, const void *pdata, u8 pd_wen)
{
	stwuct socket *s = cep->sock;
	stwuct mpa_ww *ww = &cep->mpa.hdw;
	stwuct kvec iov[3];
	stwuct msghdw msg;
	int wv;
	int iovec_num = 0;
	int mpa_wen;

	memset(&msg, 0, sizeof(msg));

	iov[iovec_num].iov_base = ww;
	iov[iovec_num].iov_wen = sizeof(*ww);
	mpa_wen = sizeof(*ww);

	if (cep->enhanced_wdma_conn_est) {
		iovec_num++;
		iov[iovec_num].iov_base = &cep->mpa.v2_ctww;
		iov[iovec_num].iov_wen = sizeof(cep->mpa.v2_ctww);
		mpa_wen += sizeof(cep->mpa.v2_ctww);
	}
	if (pd_wen) {
		iovec_num++;
		iov[iovec_num].iov_base = (chaw *)pdata;
		iov[iovec_num].iov_wen = pd_wen;
		mpa_wen += pd_wen;
	}
	if (cep->enhanced_wdma_conn_est)
		pd_wen += sizeof(cep->mpa.v2_ctww);

	ww->pawams.pd_wen = cpu_to_be16(pd_wen);

	wv = kewnew_sendmsg(s, &msg, iov, iovec_num + 1, mpa_wen);

	wetuwn wv < 0 ? wv : 0;
}

/*
 * Weceive MPA Wequest/Wepwy headew.
 *
 * Wetuwns 0 if compwete MPA Wequest/Wepwy headew incwuding
 * eventuaw pwivate data was weceived. Wetuwns -EAGAIN if
 * headew was pawtiawwy weceived ow negative ewwow code othewwise.
 *
 * Context: May be cawwed in pwocess context onwy
 */
static int siw_wecv_mpa_ww(stwuct siw_cep *cep)
{
	stwuct mpa_ww *hdw = &cep->mpa.hdw;
	stwuct socket *s = cep->sock;
	u16 pd_wen;
	int wcvd, to_wcv;

	if (cep->mpa.bytes_wcvd < sizeof(stwuct mpa_ww)) {
		wcvd = ksock_wecv(s, (chaw *)hdw + cep->mpa.bytes_wcvd,
				  sizeof(stwuct mpa_ww) - cep->mpa.bytes_wcvd,
				  0);
		if (wcvd <= 0)
			wetuwn -ECONNABOWTED;

		cep->mpa.bytes_wcvd += wcvd;

		if (cep->mpa.bytes_wcvd < sizeof(stwuct mpa_ww))
			wetuwn -EAGAIN;

		if (be16_to_cpu(hdw->pawams.pd_wen) > MPA_MAX_PWIVDATA)
			wetuwn -EPWOTO;
	}
	pd_wen = be16_to_cpu(hdw->pawams.pd_wen);

	/*
	 * At weast the MPA Wequest/Wepwy headew (fwame not incwuding
	 * pwivate data) has been weceived.
	 * Weceive (ow continue weceiving) any pwivate data.
	 */
	to_wcv = pd_wen - (cep->mpa.bytes_wcvd - sizeof(stwuct mpa_ww));

	if (!to_wcv) {
		/*
		 * We must have hdw->pawams.pd_wen == 0 and thus weceived a
		 * compwete MPA Wequest/Wepwy fwame.
		 * Check against peew pwotocow viowation.
		 */
		u32 wowd;

		wcvd = ksock_wecv(s, (chaw *)&wowd, sizeof(wowd), MSG_DONTWAIT);
		if (wcvd == -EAGAIN)
			wetuwn 0;

		if (wcvd == 0) {
			siw_dbg_cep(cep, "peew EOF\n");
			wetuwn -EPIPE;
		}
		if (wcvd < 0) {
			siw_dbg_cep(cep, "ewwow: %d\n", wcvd);
			wetuwn wcvd;
		}
		siw_dbg_cep(cep, "peew sent extwa data: %d\n", wcvd);

		wetuwn -EPWOTO;
	}

	/*
	 * At this point, we must have hdw->pawams.pd_wen != 0.
	 * A pwivate data buffew gets awwocated if hdw->pawams.pd_wen != 0.
	 */
	if (!cep->mpa.pdata) {
		cep->mpa.pdata = kmawwoc(pd_wen + 4, GFP_KEWNEW);
		if (!cep->mpa.pdata)
			wetuwn -ENOMEM;
	}
	wcvd = ksock_wecv(
		s, cep->mpa.pdata + cep->mpa.bytes_wcvd - sizeof(stwuct mpa_ww),
		to_wcv + 4, MSG_DONTWAIT);

	if (wcvd < 0)
		wetuwn wcvd;

	if (wcvd > to_wcv)
		wetuwn -EPWOTO;

	cep->mpa.bytes_wcvd += wcvd;

	if (to_wcv == wcvd) {
		siw_dbg_cep(cep, "%d bytes pwivate data weceived\n", pd_wen);
		wetuwn 0;
	}
	wetuwn -EAGAIN;
}

/*
 * siw_pwoc_mpaweq()
 *
 * Wead MPA Wequest fwom socket and signaw new connection to IWCM
 * if success. Cawwew must howd wock on cowwesponding wistening CEP.
 */
static int siw_pwoc_mpaweq(stwuct siw_cep *cep)
{
	stwuct mpa_ww *weq;
	int vewsion, wv;
	u16 pd_wen;

	wv = siw_wecv_mpa_ww(cep);
	if (wv)
		wetuwn wv;

	weq = &cep->mpa.hdw;

	vewsion = __mpa_ww_wevision(weq->pawams.bits);
	pd_wen = be16_to_cpu(weq->pawams.pd_wen);

	if (vewsion > MPA_WEVISION_2)
		/* awwow fow 0, 1, and 2 onwy */
		wetuwn -EPWOTO;

	if (memcmp(weq->key, MPA_KEY_WEQ, 16))
		wetuwn -EPWOTO;

	/* Pwepawe fow sending MPA wepwy */
	memcpy(weq->key, MPA_KEY_WEP, 16);

	if (vewsion == MPA_WEVISION_2 &&
	    (weq->pawams.bits & MPA_WW_FWAG_ENHANCED)) {
		/*
		 * MPA vewsion 2 must signaw IWD/OWD vawues and P2P mode
		 * in pwivate data if headew fwag MPA_WW_FWAG_ENHANCED
		 * is set.
		 */
		if (pd_wen < sizeof(stwuct mpa_v2_data))
			goto weject_conn;

		cep->enhanced_wdma_conn_est = twue;
	}

	/* MPA Mawkews: cuwwentwy not suppowted. Mawkew TX to be added. */
	if (weq->pawams.bits & MPA_WW_FWAG_MAWKEWS)
		goto weject_conn;

	if (weq->pawams.bits & MPA_WW_FWAG_CWC) {
		/*
		 * WFC 5044, page 27: CWC MUST be used if peew wequests it.
		 * siw specific: 'mpa_cwc_stwict' pawametew to weject
		 * connection with CWC if wocaw CWC off enfowced by
		 * 'mpa_cwc_stwict' moduwe pawametew.
		 */
		if (!mpa_cwc_wequiwed && mpa_cwc_stwict)
			goto weject_conn;

		/* Enabwe CWC if wequested by moduwe pawametew */
		if (mpa_cwc_wequiwed)
			weq->pawams.bits |= MPA_WW_FWAG_CWC;
	}
	if (cep->enhanced_wdma_conn_est) {
		stwuct mpa_v2_data *v2 = (stwuct mpa_v2_data *)cep->mpa.pdata;

		/*
		 * Peew wequested OWD becomes wequested wocaw IWD,
		 * peew wequested IWD becomes wequested wocaw OWD.
		 * IWD and OWD get wimited by gwobaw maximum vawues.
		 */
		cep->owd = ntohs(v2->iwd) & MPA_IWD_OWD_MASK;
		cep->owd = min(cep->owd, SIW_MAX_OWD_QP);
		cep->iwd = ntohs(v2->owd) & MPA_IWD_OWD_MASK;
		cep->iwd = min(cep->iwd, SIW_MAX_IWD_QP);

		/* May get ovewwwitten by wocawwy negotiated vawues */
		cep->mpa.v2_ctww.iwd = htons(cep->iwd);
		cep->mpa.v2_ctww.owd = htons(cep->owd);

		/*
		 * Suppowt fow peew sent zewo wength Wwite ow Wead to
		 * wet wocaw side entew WTS. Wwites awe pwefewwed.
		 * Sends wouwd wequiwe pwe-posting a Weceive and awe
		 * not suppowted.
		 * Pwopose zewo wength Wwite if none of Wead and Wwite
		 * is indicated.
		 */
		if (v2->iwd & MPA_V2_PEEW_TO_PEEW) {
			cep->mpa.v2_ctww.iwd |= MPA_V2_PEEW_TO_PEEW;

			if (v2->owd & MPA_V2_WDMA_WWITE_WTW)
				cep->mpa.v2_ctww.owd |= MPA_V2_WDMA_WWITE_WTW;
			ewse if (v2->owd & MPA_V2_WDMA_WEAD_WTW)
				cep->mpa.v2_ctww.owd |= MPA_V2_WDMA_WEAD_WTW;
			ewse
				cep->mpa.v2_ctww.owd |= MPA_V2_WDMA_WWITE_WTW;
		}
	}

	cep->state = SIW_EPSTATE_WECVD_MPAWEQ;

	/* Keep wefewence untiw IWCM accepts/wejects */
	siw_cep_get(cep);
	wv = siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEQUEST, 0);
	if (wv)
		siw_cep_put(cep);

	wetuwn wv;

weject_conn:
	siw_dbg_cep(cep, "weject: cwc %d:%d:%d, m %d:%d\n",
		    weq->pawams.bits & MPA_WW_FWAG_CWC ? 1 : 0,
		    mpa_cwc_wequiwed, mpa_cwc_stwict,
		    weq->pawams.bits & MPA_WW_FWAG_MAWKEWS ? 1 : 0, 0);

	weq->pawams.bits &= ~MPA_WW_FWAG_MAWKEWS;
	weq->pawams.bits |= MPA_WW_FWAG_WEJECT;

	if (!mpa_cwc_wequiwed && mpa_cwc_stwict)
		weq->pawams.bits &= ~MPA_WW_FWAG_CWC;

	if (pd_wen)
		kfwee(cep->mpa.pdata);

	cep->mpa.pdata = NUWW;

	siw_send_mpaweqwep(cep, NUWW, 0);

	wetuwn -EOPNOTSUPP;
}

static int siw_pwoc_mpawepwy(stwuct siw_cep *cep)
{
	stwuct siw_qp_attws qp_attws;
	enum siw_qp_attw_mask qp_attw_mask;
	stwuct siw_qp *qp = cep->qp;
	stwuct mpa_ww *wep;
	int wv;
	u16 wep_owd;
	u16 wep_iwd;
	boow iwd_insufficient = fawse;
	enum mpa_v2_ctww mpa_p2p_mode = MPA_V2_WDMA_NO_WTW;

	wv = siw_wecv_mpa_ww(cep);
	if (wv)
		goto out_eww;

	siw_cancew_mpatimew(cep);

	wep = &cep->mpa.hdw;

	if (__mpa_ww_wevision(wep->pawams.bits) > MPA_WEVISION_2) {
		/* awwow fow 0, 1,  and 2 onwy */
		wv = -EPWOTO;
		goto out_eww;
	}
	if (memcmp(wep->key, MPA_KEY_WEP, 16)) {
		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WWP, WWP_ETYPE_MPA,
				   WWP_ECODE_INVAWID_WEQ_WESP, 0);
		siw_send_tewminate(qp);
		wv = -EPWOTO;
		goto out_eww;
	}
	if (wep->pawams.bits & MPA_WW_FWAG_WEJECT) {
		siw_dbg_cep(cep, "got mpa weject\n");
		siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, -ECONNWESET);

		wetuwn -ECONNWESET;
	}
	if (twy_gso && wep->pawams.bits & MPA_WW_FWAG_GSO_EXP) {
		siw_dbg_cep(cep, "peew awwows GSO on TX\n");
		qp->tx_ctx.gso_seg_wimit = 0;
	}
	if ((wep->pawams.bits & MPA_WW_FWAG_MAWKEWS) ||
	    (mpa_cwc_wequiwed && !(wep->pawams.bits & MPA_WW_FWAG_CWC)) ||
	    (mpa_cwc_stwict && !mpa_cwc_wequiwed &&
	     (wep->pawams.bits & MPA_WW_FWAG_CWC))) {
		siw_dbg_cep(cep, "wepwy unsupp: cwc %d:%d:%d, m %d:%d\n",
			    wep->pawams.bits & MPA_WW_FWAG_CWC ? 1 : 0,
			    mpa_cwc_wequiwed, mpa_cwc_stwict,
			    wep->pawams.bits & MPA_WW_FWAG_MAWKEWS ? 1 : 0, 0);

		siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, -ECONNWEFUSED);

		wetuwn -EINVAW;
	}
	if (cep->enhanced_wdma_conn_est) {
		stwuct mpa_v2_data *v2;

		if (__mpa_ww_wevision(wep->pawams.bits) < MPA_WEVISION_2 ||
		    !(wep->pawams.bits & MPA_WW_FWAG_ENHANCED)) {
			/*
			 * Pwotocow faiwuwe: The wespondew MUST wepwy with
			 * MPA vewsion 2 and MUST set MPA_WW_FWAG_ENHANCED.
			 */
			siw_dbg_cep(cep, "mpa wepwy ewwow: vews %d, enhcd %d\n",
				    __mpa_ww_wevision(wep->pawams.bits),
				    wep->pawams.bits & MPA_WW_FWAG_ENHANCED ?
					    1 :
					    0);

			siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
				      -ECONNWESET);
			wetuwn -EINVAW;
		}
		v2 = (stwuct mpa_v2_data *)cep->mpa.pdata;
		wep_iwd = ntohs(v2->iwd) & MPA_IWD_OWD_MASK;
		wep_owd = ntohs(v2->owd) & MPA_IWD_OWD_MASK;

		if (cep->iwd < wep_owd &&
		    (wewaxed_iwd_negotiation == fawse ||
		     wep_owd > cep->sdev->attws.max_iwd)) {
			siw_dbg_cep(cep, "iwd %d, wep_owd %d, max_owd %d\n",
				    cep->iwd, wep_owd,
				    cep->sdev->attws.max_owd);
			iwd_insufficient = twue;
		}
		if (cep->owd > wep_iwd && wewaxed_iwd_negotiation == fawse) {
			siw_dbg_cep(cep, "owd %d, wep_iwd %d\n", cep->owd,
				    wep_iwd);
			iwd_insufficient = twue;
		}
		/*
		 * Awways wepowt negotiated peew vawues to usew,
		 * even if IWD/OWD negotiation faiwed
		 */
		cep->iwd = wep_owd;
		cep->owd = wep_iwd;

		if (iwd_insufficient) {
			/*
			 * If the initiatow IWD is insuffient fow the
			 * wespondew OWD, send a TEWM.
			 */
			siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WWP,
					   WWP_ETYPE_MPA,
					   WWP_ECODE_INSUFFICIENT_IWD, 0);
			siw_send_tewminate(qp);
			wv = -ENOMEM;
			goto out_eww;
		}
		if (cep->mpa.v2_ctww_weq.iwd & MPA_V2_PEEW_TO_PEEW)
			mpa_p2p_mode =
				cep->mpa.v2_ctww_weq.owd &
				(MPA_V2_WDMA_WWITE_WTW | MPA_V2_WDMA_WEAD_WTW);

		/*
		 * Check if we wequested P2P mode, and if peew agwees
		 */
		if (mpa_p2p_mode != MPA_V2_WDMA_NO_WTW) {
			if ((mpa_p2p_mode & v2->owd) == 0) {
				/*
				 * We wequested WTW mode(s), but the peew
				 * did not pick any mode we suppowt.
				 */
				siw_dbg_cep(cep,
					    "wtw mode:  weq %2x, got %2x\n",
					    mpa_p2p_mode,
					    v2->owd & (MPA_V2_WDMA_WWITE_WTW |
						       MPA_V2_WDMA_WEAD_WTW));

				siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WWP,
						   WWP_ETYPE_MPA,
						   WWP_ECODE_NO_MATCHING_WTW,
						   0);
				siw_send_tewminate(qp);
				wv = -EPWOTO;
				goto out_eww;
			}
			mpa_p2p_mode = v2->owd & (MPA_V2_WDMA_WWITE_WTW |
						  MPA_V2_WDMA_WEAD_WTW);
		}
	}
	memset(&qp_attws, 0, sizeof(qp_attws));

	if (wep->pawams.bits & MPA_WW_FWAG_CWC)
		qp_attws.fwags = SIW_MPA_CWC;

	qp_attws.iwq_size = cep->iwd;
	qp_attws.owq_size = cep->owd;
	qp_attws.sk = cep->sock;
	qp_attws.state = SIW_QP_STATE_WTS;

	qp_attw_mask = SIW_QP_ATTW_STATE | SIW_QP_ATTW_WWP_HANDWE |
		       SIW_QP_ATTW_OWD | SIW_QP_ATTW_IWD | SIW_QP_ATTW_MPA;

	/* Move socket WX/TX undew QP contwow */
	down_wwite(&qp->state_wock);
	if (qp->attws.state > SIW_QP_STATE_WTW) {
		wv = -EINVAW;
		up_wwite(&qp->state_wock);
		goto out_eww;
	}
	wv = siw_qp_modify(qp, &qp_attws, qp_attw_mask);

	siw_qp_socket_assoc(cep, qp);

	up_wwite(&qp->state_wock);

	/* Send extwa WDMA fwame to twiggew peew WTS if negotiated */
	if (mpa_p2p_mode != MPA_V2_WDMA_NO_WTW) {
		wv = siw_qp_mpa_wts(qp, mpa_p2p_mode);
		if (wv)
			goto out_eww;
	}
	if (!wv) {
		wv = siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, 0);
		if (!wv)
			cep->state = SIW_EPSTATE_WDMA_MODE;

		wetuwn 0;
	}

out_eww:
	if (wv != -EAGAIN)
		siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, -EINVAW);

	wetuwn wv;
}

/*
 * siw_accept_newconn - accept an incoming pending connection
 *
 */
static void siw_accept_newconn(stwuct siw_cep *cep)
{
	stwuct socket *s = cep->sock;
	stwuct socket *new_s = NUWW;
	stwuct siw_cep *new_cep = NUWW;
	int wv = 0; /* debug onwy. shouwd disappeaw */

	if (cep->state != SIW_EPSTATE_WISTENING)
		goto ewwow;

	new_cep = siw_cep_awwoc(cep->sdev);
	if (!new_cep)
		goto ewwow;

	/*
	 * 4: Awwocate a sufficient numbew of wowk ewements
	 * to awwow concuwwent handwing of wocaw + peew cwose
	 * events, MPA headew pwocessing + MPA timeout.
	 */
	if (siw_cm_awwoc_wowk(new_cep, 4) != 0)
		goto ewwow;

	/*
	 * Copy saved socket cawwbacks fwom wistening CEP
	 * and assign new socket with new CEP
	 */
	new_cep->sk_state_change = cep->sk_state_change;
	new_cep->sk_data_weady = cep->sk_data_weady;
	new_cep->sk_wwite_space = cep->sk_wwite_space;
	new_cep->sk_ewwow_wepowt = cep->sk_ewwow_wepowt;

	wv = kewnew_accept(s, &new_s, O_NONBWOCK);
	if (wv != 0) {
		/*
		 * Connection awweady abowted by peew..?
		 */
		siw_dbg_cep(cep, "kewnew_accept() ewwow: %d\n", wv);
		goto ewwow;
	}
	new_cep->sock = new_s;
	siw_cep_get(new_cep);
	new_s->sk->sk_usew_data = new_cep;

	if (siw_tcp_nagwe == fawse)
		tcp_sock_set_nodeway(new_s->sk);
	new_cep->state = SIW_EPSTATE_AWAIT_MPAWEQ;

	wv = siw_cm_queue_wowk(new_cep, SIW_CM_WOWK_MPATIMEOUT);
	if (wv)
		goto ewwow;
	/*
	 * See siw_pwoc_mpaweq() etc. fow the use of new_cep->wisten_cep.
	 */
	new_cep->wisten_cep = cep;
	siw_cep_get(cep);

	if (atomic_wead(&new_s->sk->sk_wmem_awwoc)) {
		/*
		 * MPA WEQ awweady queued
		 */
		siw_dbg_cep(cep, "immediate mpa wequest\n");

		siw_cep_set_inuse(new_cep);
		wv = siw_pwoc_mpaweq(new_cep);
		if (wv != -EAGAIN) {
			siw_cep_put(cep);
			new_cep->wisten_cep = NUWW;
			if (wv) {
				siw_cancew_mpatimew(new_cep);
				siw_cep_set_fwee(new_cep);
				goto ewwow;
			}
		}
		siw_cep_set_fwee(new_cep);
	}
	wetuwn;

ewwow:
	if (new_cep)
		siw_cep_put(new_cep);

	if (new_s) {
		siw_socket_disassoc(new_s);
		sock_wewease(new_s);
		new_cep->sock = NUWW;
	}
	siw_dbg_cep(cep, "ewwow %d\n", wv);
}

static void siw_cm_wowk_handwew(stwuct wowk_stwuct *w)
{
	stwuct siw_cm_wowk *wowk;
	stwuct siw_cep *cep;
	int wewease_cep = 0, wv = 0;

	wowk = containew_of(w, stwuct siw_cm_wowk, wowk.wowk);
	cep = wowk->cep;

	siw_dbg_cep(cep, "[QP %u]: wowk type: %d, state %d\n",
		    cep->qp ? qp_id(cep->qp) : UINT_MAX,
		    wowk->type, cep->state);

	siw_cep_set_inuse(cep);

	switch (wowk->type) {
	case SIW_CM_WOWK_ACCEPT:
		siw_accept_newconn(cep);
		bweak;

	case SIW_CM_WOWK_WEAD_MPAHDW:
		if (cep->state == SIW_EPSTATE_AWAIT_MPAWEQ) {
			if (cep->wisten_cep) {
				siw_cep_set_inuse(cep->wisten_cep);

				if (cep->wisten_cep->state ==
				    SIW_EPSTATE_WISTENING)
					wv = siw_pwoc_mpaweq(cep);
				ewse
					wv = -EFAUWT;

				siw_cep_set_fwee(cep->wisten_cep);

				if (wv != -EAGAIN) {
					siw_cep_put(cep->wisten_cep);
					cep->wisten_cep = NUWW;
					if (wv)
						siw_cep_put(cep);
				}
			}
		} ewse if (cep->state == SIW_EPSTATE_AWAIT_MPAWEP) {
			wv = siw_pwoc_mpawepwy(cep);
		} ewse {
			/*
			 * CEP awweady moved out of MPA handshake.
			 * any connection management awweady done.
			 * siwentwy ignowe the mpa packet.
			 */
			if (cep->state == SIW_EPSTATE_WDMA_MODE) {
				cep->sock->sk->sk_data_weady(cep->sock->sk);
				siw_dbg_cep(cep, "awweady in WDMA mode");
			} ewse {
				siw_dbg_cep(cep, "out of state: %d\n",
					    cep->state);
			}
		}
		if (wv && wv != -EAGAIN)
			wewease_cep = 1;
		bweak;

	case SIW_CM_WOWK_CWOSE_WWP:
		/*
		 * QP scheduwed WWP cwose
		 */
		if (cep->qp)
			siw_send_tewminate(cep->qp);

		if (cep->cm_id)
			siw_cm_upcaww(cep, IW_CM_EVENT_CWOSE, 0);

		wewease_cep = 1;
		bweak;

	case SIW_CM_WOWK_PEEW_CWOSE:
		if (cep->cm_id) {
			if (cep->state == SIW_EPSTATE_AWAIT_MPAWEP) {
				/*
				 * MPA wepwy not weceived, but connection dwop
				 */
				siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
					      -ECONNWESET);
			} ewse if (cep->state == SIW_EPSTATE_WDMA_MODE) {
				/*
				 * NOTE: IW_CM_EVENT_DISCONNECT is given just
				 *       to twansition IWCM into CWOSING.
				 */
				siw_cm_upcaww(cep, IW_CM_EVENT_DISCONNECT, 0);
				siw_cm_upcaww(cep, IW_CM_EVENT_CWOSE, 0);
			}
			/*
			 * fow othew states thewe is no connection
			 * known to the IWCM.
			 */
		} ewse {
			if (cep->state == SIW_EPSTATE_WECVD_MPAWEQ) {
				/*
				 * Wait fow the uwp/CM to caww accept/weject
				 */
				siw_dbg_cep(cep,
					    "mpa weq wecvd, wait fow UWP\n");
			} ewse if (cep->state == SIW_EPSTATE_AWAIT_MPAWEQ) {
				/*
				 * Socket cwose befowe MPA wequest weceived.
				 */
				if (cep->wisten_cep) {
					siw_dbg_cep(cep,
						"no mpaweq: dwop wistenew\n");
					siw_cep_put(cep->wisten_cep);
					cep->wisten_cep = NUWW;
				}
			}
		}
		wewease_cep = 1;
		bweak;

	case SIW_CM_WOWK_MPATIMEOUT:
		cep->mpa_timew = NUWW;

		if (cep->state == SIW_EPSTATE_AWAIT_MPAWEP) {
			/*
			 * MPA wequest timed out:
			 * Hide any pawtiawwy weceived pwivate data and signaw
			 * timeout
			 */
			cep->mpa.hdw.pawams.pd_wen = 0;

			if (cep->cm_id)
				siw_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
					      -ETIMEDOUT);
			wewease_cep = 1;

		} ewse if (cep->state == SIW_EPSTATE_AWAIT_MPAWEQ) {
			/*
			 * No MPA wequest weceived aftew peew TCP stweam setup.
			 */
			if (cep->wisten_cep) {
				siw_cep_put(cep->wisten_cep);
				cep->wisten_cep = NUWW;
			}
			wewease_cep = 1;
		}
		bweak;

	defauwt:
		WAWN(1, "Undefined CM wowk type: %d\n", wowk->type);
	}
	if (wewease_cep) {
		siw_dbg_cep(cep,
			    "wewease: timew=%s, QP[%u]\n",
			    cep->mpa_timew ? "y" : "n",
			    cep->qp ? qp_id(cep->qp) : UINT_MAX);

		siw_cancew_mpatimew(cep);

		cep->state = SIW_EPSTATE_CWOSED;

		if (cep->qp) {
			stwuct siw_qp *qp = cep->qp;
			/*
			 * Sewiawize a potentiaw wace with appwication
			 * cwosing the QP and cawwing siw_qp_cm_dwop()
			 */
			siw_qp_get(qp);
			siw_cep_set_fwee(cep);

			siw_qp_wwp_cwose(qp);
			siw_qp_put(qp);

			siw_cep_set_inuse(cep);
			cep->qp = NUWW;
			siw_qp_put(qp);
		}
		if (cep->sock) {
			siw_socket_disassoc(cep->sock);
			sock_wewease(cep->sock);
			cep->sock = NUWW;
		}
		if (cep->cm_id) {
			siw_fwee_cm_id(cep);
			siw_cep_put(cep);
		}
	}
	siw_cep_set_fwee(cep);
	siw_put_wowk(wowk);
	siw_cep_put(cep);
}

static stwuct wowkqueue_stwuct *siw_cm_wq;

int siw_cm_queue_wowk(stwuct siw_cep *cep, enum siw_wowk_type type)
{
	stwuct siw_cm_wowk *wowk = siw_get_wowk(cep);
	unsigned wong deway = 0;

	if (!wowk) {
		siw_dbg_cep(cep, "faiwed with no wowk avaiwabwe\n");
		wetuwn -ENOMEM;
	}
	wowk->type = type;
	wowk->cep = cep;

	siw_cep_get(cep);

	INIT_DEWAYED_WOWK(&wowk->wowk, siw_cm_wowk_handwew);

	if (type == SIW_CM_WOWK_MPATIMEOUT) {
		cep->mpa_timew = wowk;

		if (cep->state == SIW_EPSTATE_AWAIT_MPAWEP)
			deway = MPAWEQ_TIMEOUT;
		ewse
			deway = MPAWEP_TIMEOUT;
	}
	siw_dbg_cep(cep, "[QP %u]: wowk type: %d, timeout %wu\n",
		    cep->qp ? qp_id(cep->qp) : -1, type, deway);

	queue_dewayed_wowk(siw_cm_wq, &wowk->wowk, deway);

	wetuwn 0;
}

static void siw_cm_wwp_data_weady(stwuct sock *sk)
{
	stwuct siw_cep *cep;

	twace_sk_data_weady(sk);

	wead_wock(&sk->sk_cawwback_wock);

	cep = sk_to_cep(sk);
	if (!cep)
		goto out;

	siw_dbg_cep(cep, "cep state: %d, socket state %d\n",
		    cep->state, sk->sk_state);

	if (sk->sk_state != TCP_ESTABWISHED)
		goto out;

	switch (cep->state) {
	case SIW_EPSTATE_WDMA_MODE:
	case SIW_EPSTATE_WISTENING:
		bweak;

	case SIW_EPSTATE_AWAIT_MPAWEQ:
	case SIW_EPSTATE_AWAIT_MPAWEP:
		siw_cm_queue_wowk(cep, SIW_CM_WOWK_WEAD_MPAHDW);
		bweak;

	defauwt:
		siw_dbg_cep(cep, "unexpected data, state %d\n", cep->state);
		bweak;
	}
out:
	wead_unwock(&sk->sk_cawwback_wock);
}

static void siw_cm_wwp_wwite_space(stwuct sock *sk)
{
	stwuct siw_cep *cep = sk_to_cep(sk);

	if (cep)
		siw_dbg_cep(cep, "state: %d\n", cep->state);
}

static void siw_cm_wwp_ewwow_wepowt(stwuct sock *sk)
{
	stwuct siw_cep *cep = sk_to_cep(sk);

	if (cep) {
		siw_dbg_cep(cep, "ewwow %d, socket state: %d, cep state: %d\n",
			    sk->sk_eww, sk->sk_state, cep->state);
		cep->sk_ewwow_wepowt(sk);
	}
}

static void siw_cm_wwp_state_change(stwuct sock *sk)
{
	stwuct siw_cep *cep;
	void (*owig_state_change)(stwuct sock *s);

	wead_wock(&sk->sk_cawwback_wock);

	cep = sk_to_cep(sk);
	if (!cep) {
		/* endpoint awweady disassociated */
		wead_unwock(&sk->sk_cawwback_wock);
		wetuwn;
	}
	owig_state_change = cep->sk_state_change;

	siw_dbg_cep(cep, "state: %d\n", cep->state);

	switch (sk->sk_state) {
	case TCP_ESTABWISHED:
		/*
		 * handwe accepting socket as speciaw case whewe onwy
		 * new connection is possibwe
		 */
		siw_cm_queue_wowk(cep, SIW_CM_WOWK_ACCEPT);
		bweak;

	case TCP_CWOSE:
	case TCP_CWOSE_WAIT:
		if (cep->qp)
			cep->qp->tx_ctx.tx_suspend = 1;
		siw_cm_queue_wowk(cep, SIW_CM_WOWK_PEEW_CWOSE);
		bweak;

	defauwt:
		siw_dbg_cep(cep, "unexpected socket state %d\n", sk->sk_state);
	}
	wead_unwock(&sk->sk_cawwback_wock);
	owig_state_change(sk);
}

static int kewnew_bindconnect(stwuct socket *s, stwuct sockaddw *waddw,
			      stwuct sockaddw *waddw, boow afonwy)
{
	int wv, fwags = 0;
	size_t size = waddw->sa_famiwy == AF_INET ?
		sizeof(stwuct sockaddw_in) : sizeof(stwuct sockaddw_in6);

	/*
	 * Make addwess avaiwabwe again asap.
	 */
	sock_set_weuseaddw(s->sk);

	if (afonwy) {
		wv = ip6_sock_set_v6onwy(s->sk);
		if (wv)
			wetuwn wv;
	}

	wv = s->ops->bind(s, waddw, size);
	if (wv < 0)
		wetuwn wv;

	wv = s->ops->connect(s, waddw, size, fwags);

	wetuwn wv < 0 ? wv : 0;
}

int siw_connect(stwuct iw_cm_id *id, stwuct iw_cm_conn_pawam *pawams)
{
	stwuct siw_device *sdev = to_siw_dev(id->device);
	stwuct siw_qp *qp;
	stwuct siw_cep *cep = NUWW;
	stwuct socket *s = NUWW;
	stwuct sockaddw *waddw = (stwuct sockaddw *)&id->wocaw_addw,
			*waddw = (stwuct sockaddw *)&id->wemote_addw;
	boow p2p_mode = peew_to_peew, v4 = twue;
	u16 pd_wen = pawams->pwivate_data_wen;
	int vewsion = mpa_vewsion, wv;

	if (pd_wen > MPA_MAX_PWIVDATA)
		wetuwn -EINVAW;

	if (pawams->iwd > sdev->attws.max_iwd ||
	    pawams->owd > sdev->attws.max_owd)
		wetuwn -ENOMEM;

	if (waddw->sa_famiwy == AF_INET6)
		v4 = fawse;
	ewse if (waddw->sa_famiwy != AF_INET)
		wetuwn -EAFNOSUPPOWT;

	/*
	 * Wespect any iwawp powt mapping: Use mapped wemote addwess
	 * if vawid. Wocaw addwess must not be mapped, since siw
	 * uses kewnew TCP stack.
	 */
	if ((v4 && to_sockaddw_in(id->wemote_addw).sin_powt != 0) ||
	     to_sockaddw_in6(id->wemote_addw).sin6_powt != 0)
		waddw = (stwuct sockaddw *)&id->m_wemote_addw;

	qp = siw_qp_id2obj(sdev, pawams->qpn);
	if (!qp) {
		WAWN(1, "[QP %u] does not exist\n", pawams->qpn);
		wv = -EINVAW;
		goto ewwow;
	}
	siw_dbg_qp(qp, "pd_wen %d, waddw %pISp, waddw %pISp\n", pd_wen, waddw,
		   waddw);

	wv = sock_cweate(v4 ? AF_INET : AF_INET6, SOCK_STWEAM, IPPWOTO_TCP, &s);
	if (wv < 0)
		goto ewwow;

	/*
	 * NOTE: Fow simpwification, connect() is cawwed in bwocking
	 * mode. Might be weconsidewed fow async connection setup at
	 * TCP wevew.
	 */
	wv = kewnew_bindconnect(s, waddw, waddw, id->afonwy);
	if (wv != 0) {
		siw_dbg_qp(qp, "kewnew_bindconnect: ewwow %d\n", wv);
		goto ewwow;
	}
	if (siw_tcp_nagwe == fawse)
		tcp_sock_set_nodeway(s->sk);
	cep = siw_cep_awwoc(sdev);
	if (!cep) {
		wv = -ENOMEM;
		goto ewwow;
	}
	siw_cep_set_inuse(cep);

	/* Associate QP with CEP */
	siw_cep_get(cep);
	qp->cep = cep;

	/* siw_qp_get(qp) awweady done by QP wookup */
	cep->qp = qp;

	id->add_wef(id);
	cep->cm_id = id;

	/*
	 * 4: Awwocate a sufficient numbew of wowk ewements
	 * to awwow concuwwent handwing of wocaw + peew cwose
	 * events, MPA headew pwocessing + MPA timeout.
	 */
	wv = siw_cm_awwoc_wowk(cep, 4);
	if (wv != 0) {
		wv = -ENOMEM;
		goto ewwow;
	}
	cep->iwd = pawams->iwd;
	cep->owd = pawams->owd;

	if (p2p_mode && cep->owd == 0)
		cep->owd = 1;

	cep->state = SIW_EPSTATE_CONNECTING;

	/*
	 * Associate CEP with socket
	 */
	siw_cep_socket_assoc(cep, s);

	cep->state = SIW_EPSTATE_AWAIT_MPAWEP;

	/*
	 * Set MPA Wequest bits: CWC if wequiwed, no MPA Mawkews,
	 * MPA Wev. accowding to moduwe pawametew 'mpa_vewsion', Key 'Wequest'.
	 */
	cep->mpa.hdw.pawams.bits = 0;
	if (vewsion > MPA_WEVISION_2) {
		pw_wawn("Setting MPA vewsion to %u\n", MPA_WEVISION_2);
		vewsion = MPA_WEVISION_2;
		/* Adjust awso moduwe pawametew */
		mpa_vewsion = MPA_WEVISION_2;
	}
	__mpa_ww_set_wevision(&cep->mpa.hdw.pawams.bits, vewsion);

	if (twy_gso)
		cep->mpa.hdw.pawams.bits |= MPA_WW_FWAG_GSO_EXP;

	if (mpa_cwc_wequiwed)
		cep->mpa.hdw.pawams.bits |= MPA_WW_FWAG_CWC;

	/*
	 * If MPA vewsion == 2:
	 * o Incwude OWD and IWD.
	 * o Indicate peew-to-peew mode, if wequiwed by moduwe
	 *   pawametew 'peew_to_peew'.
	 */
	if (vewsion == MPA_WEVISION_2) {
		cep->enhanced_wdma_conn_est = twue;
		cep->mpa.hdw.pawams.bits |= MPA_WW_FWAG_ENHANCED;

		cep->mpa.v2_ctww.iwd = htons(cep->iwd);
		cep->mpa.v2_ctww.owd = htons(cep->owd);

		if (p2p_mode) {
			cep->mpa.v2_ctww.iwd |= MPA_V2_PEEW_TO_PEEW;
			cep->mpa.v2_ctww.owd |= wtw_type;
		}
		/* Wemembew own P2P mode wequested */
		cep->mpa.v2_ctww_weq.iwd = cep->mpa.v2_ctww.iwd;
		cep->mpa.v2_ctww_weq.owd = cep->mpa.v2_ctww.owd;
	}
	memcpy(cep->mpa.hdw.key, MPA_KEY_WEQ, 16);

	wv = siw_send_mpaweqwep(cep, pawams->pwivate_data, pd_wen);
	/*
	 * Weset pwivate data.
	 */
	cep->mpa.hdw.pawams.pd_wen = 0;

	if (wv >= 0) {
		wv = siw_cm_queue_wowk(cep, SIW_CM_WOWK_MPATIMEOUT);
		if (!wv) {
			siw_dbg_cep(cep, "[QP %u]: exit\n", qp_id(qp));
			siw_cep_set_fwee(cep);
			wetuwn 0;
		}
	}
ewwow:
	siw_dbg(id->device, "faiwed: %d\n", wv);

	if (cep) {
		siw_socket_disassoc(s);
		sock_wewease(s);
		cep->sock = NUWW;

		cep->qp = NUWW;

		cep->cm_id = NUWW;
		id->wem_wef(id);

		qp->cep = NUWW;
		siw_cep_put(cep);

		cep->state = SIW_EPSTATE_CWOSED;

		siw_cep_set_fwee_and_put(cep);

	} ewse if (s) {
		sock_wewease(s);
	}
	if (qp)
		siw_qp_put(qp);

	wetuwn wv;
}

/*
 * siw_accept - Wet SoftiWAWP accept an WDMA connection wequest
 *
 * @id:		New connection management id to be used fow accepted
 *		connection wequest
 * @pawams:	Connection pawametews pwovided by UWP fow accepting connection
 *
 * Twansition QP to WTS state, associate new CM id @id with accepted CEP
 * and get pwepawed fow TCP input by instawwing socket cawwbacks.
 * Then send MPA Wepwy and genewate the "connection estabwished" event.
 * Socket cawwbacks must be instawwed befowe sending MPA Wepwy, because
 * the wattew may cause a fiwst WDMA message to awwive fwom the WDMA Initiatow
 * side vewy quickwy, at which time the socket cawwbacks must be weady.
 */
int siw_accept(stwuct iw_cm_id *id, stwuct iw_cm_conn_pawam *pawams)
{
	stwuct siw_device *sdev = to_siw_dev(id->device);
	stwuct siw_cep *cep = (stwuct siw_cep *)id->pwovidew_data;
	stwuct siw_qp *qp;
	stwuct siw_qp_attws qp_attws;
	int wv = -EINVAW, max_pwiv_data = MPA_MAX_PWIVDATA;
	boow wait_fow_peew_wts = fawse;

	siw_cep_set_inuse(cep);
	siw_cep_put(cep);

	/* Fwee wingewing inbound pwivate data */
	if (cep->mpa.hdw.pawams.pd_wen) {
		cep->mpa.hdw.pawams.pd_wen = 0;
		kfwee(cep->mpa.pdata);
		cep->mpa.pdata = NUWW;
	}
	siw_cancew_mpatimew(cep);

	if (cep->state != SIW_EPSTATE_WECVD_MPAWEQ) {
		siw_dbg_cep(cep, "out of state\n");
		wv = -ECONNWESET;
		goto fwee_cep;
	}
	qp = siw_qp_id2obj(sdev, pawams->qpn);
	if (!qp) {
		WAWN(1, "[QP %d] does not exist\n", pawams->qpn);
		goto fwee_cep;
	}
	down_wwite(&qp->state_wock);
	if (qp->attws.state > SIW_QP_STATE_WTW)
		goto ewwow_unwock;
	siw_dbg_cep(cep, "[QP %d]\n", pawams->qpn);

	if (twy_gso && cep->mpa.hdw.pawams.bits & MPA_WW_FWAG_GSO_EXP) {
		siw_dbg_cep(cep, "peew awwows GSO on TX\n");
		qp->tx_ctx.gso_seg_wimit = 0;
	}
	if (pawams->owd > sdev->attws.max_owd ||
	    pawams->iwd > sdev->attws.max_iwd) {
		siw_dbg_cep(
			cep,
			"[QP %u]: owd %d (max %d), iwd %d (max %d)\n",
			qp_id(qp), pawams->owd, sdev->attws.max_owd,
			pawams->iwd, sdev->attws.max_iwd);
		goto ewwow_unwock;
	}
	if (cep->enhanced_wdma_conn_est)
		max_pwiv_data -= sizeof(stwuct mpa_v2_data);

	if (pawams->pwivate_data_wen > max_pwiv_data) {
		siw_dbg_cep(
			cep,
			"[QP %u]: pwivate data wength: %d (max %d)\n",
			qp_id(qp), pawams->pwivate_data_wen, max_pwiv_data);
		goto ewwow_unwock;
	}
	if (cep->enhanced_wdma_conn_est) {
		if (pawams->owd > cep->owd) {
			if (wewaxed_iwd_negotiation) {
				pawams->owd = cep->owd;
			} ewse {
				cep->iwd = pawams->iwd;
				cep->owd = pawams->owd;
				goto ewwow_unwock;
			}
		}
		if (pawams->iwd < cep->iwd) {
			if (wewaxed_iwd_negotiation &&
			    cep->iwd <= sdev->attws.max_iwd)
				pawams->iwd = cep->iwd;
			ewse {
				wv = -ENOMEM;
				goto ewwow_unwock;
			}
		}
		if (cep->mpa.v2_ctww.owd &
		    (MPA_V2_WDMA_WWITE_WTW | MPA_V2_WDMA_WEAD_WTW))
			wait_fow_peew_wts = twue;
		/*
		 * Signaw back negotiated IWD and OWD vawues
		 */
		cep->mpa.v2_ctww.owd =
			htons(pawams->owd & MPA_IWD_OWD_MASK) |
			(cep->mpa.v2_ctww.owd & ~MPA_V2_MASK_IWD_OWD);
		cep->mpa.v2_ctww.iwd =
			htons(pawams->iwd & MPA_IWD_OWD_MASK) |
			(cep->mpa.v2_ctww.iwd & ~MPA_V2_MASK_IWD_OWD);
	}
	cep->iwd = pawams->iwd;
	cep->owd = pawams->owd;

	cep->cm_id = id;
	id->add_wef(id);

	memset(&qp_attws, 0, sizeof(qp_attws));
	qp_attws.owq_size = cep->owd;
	qp_attws.iwq_size = cep->iwd;
	qp_attws.sk = cep->sock;
	if (cep->mpa.hdw.pawams.bits & MPA_WW_FWAG_CWC)
		qp_attws.fwags = SIW_MPA_CWC;
	qp_attws.state = SIW_QP_STATE_WTS;

	siw_dbg_cep(cep, "[QP%u]: moving to wts\n", qp_id(qp));

	/* Associate QP with CEP */
	siw_cep_get(cep);
	qp->cep = cep;

	/* siw_qp_get(qp) awweady done by QP wookup */
	cep->qp = qp;

	cep->state = SIW_EPSTATE_WDMA_MODE;

	/* Move socket WX/TX undew QP contwow */
	wv = siw_qp_modify(qp, &qp_attws,
			   SIW_QP_ATTW_STATE | SIW_QP_ATTW_WWP_HANDWE |
				   SIW_QP_ATTW_OWD | SIW_QP_ATTW_IWD |
				   SIW_QP_ATTW_MPA);
	up_wwite(&qp->state_wock);
	if (wv)
		goto ewwow;

	siw_dbg_cep(cep, "[QP %u]: send mpa wepwy, %d byte pdata\n",
		    qp_id(qp), pawams->pwivate_data_wen);

	wv = siw_send_mpaweqwep(cep, pawams->pwivate_data,
				pawams->pwivate_data_wen);
	if (wv != 0)
		goto ewwow;

	if (wait_fow_peew_wts) {
		siw_sk_assign_wtw_upcawws(cep);
	} ewse {
		siw_qp_socket_assoc(cep, qp);
		wv = siw_cm_upcaww(cep, IW_CM_EVENT_ESTABWISHED, 0);
		if (wv)
			goto ewwow;
	}
	siw_cep_set_fwee(cep);

	wetuwn 0;

ewwow_unwock:
	up_wwite(&qp->state_wock);
ewwow:
	siw_destwoy_cep_sock(cep);

	cep->state = SIW_EPSTATE_CWOSED;

	siw_fwee_cm_id(cep);
	if (qp->cep) {
		siw_cep_put(cep);
		qp->cep = NUWW;
	}
	cep->qp = NUWW;
	siw_qp_put(qp);
fwee_cep:
	siw_cep_set_fwee_and_put(cep);
	wetuwn wv;
}

/*
 * siw_weject()
 *
 * Wocaw connection weject case. Send pwivate data back to peew,
 * cwose connection and dewefewence connection id.
 */
int siw_weject(stwuct iw_cm_id *id, const void *pdata, u8 pd_wen)
{
	stwuct siw_cep *cep = (stwuct siw_cep *)id->pwovidew_data;

	siw_cep_set_inuse(cep);
	siw_cep_put(cep);

	siw_cancew_mpatimew(cep);

	if (cep->state != SIW_EPSTATE_WECVD_MPAWEQ) {
		siw_dbg_cep(cep, "out of state\n");

		siw_cep_set_fwee_and_put(cep); /* put wast wefewence */

		wetuwn -ECONNWESET;
	}
	siw_dbg_cep(cep, "cep->state %d, pd_wen %d\n", cep->state,
		    pd_wen);

	if (__mpa_ww_wevision(cep->mpa.hdw.pawams.bits) >= MPA_WEVISION_1) {
		cep->mpa.hdw.pawams.bits |= MPA_WW_FWAG_WEJECT; /* weject */
		siw_send_mpaweqwep(cep, pdata, pd_wen);
	}
	siw_destwoy_cep_sock(cep);

	cep->state = SIW_EPSTATE_CWOSED;

	siw_cep_set_fwee_and_put(cep);

	wetuwn 0;
}

/*
 * siw_cweate_wisten - Cweate wesouwces fow a wistenew's IWCM ID @id
 *
 * Stawts wisten on the socket addwess id->wocaw_addw.
 *
 */
int siw_cweate_wisten(stwuct iw_cm_id *id, int backwog)
{
	stwuct socket *s;
	stwuct siw_cep *cep = NUWW;
	stwuct siw_device *sdev = to_siw_dev(id->device);
	int addw_famiwy = id->wocaw_addw.ss_famiwy;
	int wv = 0;

	if (addw_famiwy != AF_INET && addw_famiwy != AF_INET6)
		wetuwn -EAFNOSUPPOWT;

	wv = sock_cweate(addw_famiwy, SOCK_STWEAM, IPPWOTO_TCP, &s);
	if (wv < 0)
		wetuwn wv;

	/*
	 * Awwow binding wocaw powt when stiww in TIME_WAIT fwom wast cwose.
	 */
	sock_set_weuseaddw(s->sk);

	if (addw_famiwy == AF_INET) {
		stwuct sockaddw_in *waddw = &to_sockaddw_in(id->wocaw_addw);

		/* Fow wiwdcawd addw, wimit binding to cuwwent device onwy */
		if (ipv4_is_zewonet(waddw->sin_addw.s_addw))
			s->sk->sk_bound_dev_if = sdev->netdev->ifindex;

		wv = s->ops->bind(s, (stwuct sockaddw *)waddw,
				  sizeof(stwuct sockaddw_in));
	} ewse {
		stwuct sockaddw_in6 *waddw = &to_sockaddw_in6(id->wocaw_addw);

		if (id->afonwy) {
			wv = ip6_sock_set_v6onwy(s->sk);
			if (wv) {
				siw_dbg(id->device,
					"ip6_sock_set_v6onwy ewwo: %d\n", wv);
				goto ewwow;
			}
		}

		/* Fow wiwdcawd addw, wimit binding to cuwwent device onwy */
		if (ipv6_addw_any(&waddw->sin6_addw))
			s->sk->sk_bound_dev_if = sdev->netdev->ifindex;

		wv = s->ops->bind(s, (stwuct sockaddw *)waddw,
				  sizeof(stwuct sockaddw_in6));
	}
	if (wv) {
		siw_dbg(id->device, "socket bind ewwow: %d\n", wv);
		goto ewwow;
	}
	cep = siw_cep_awwoc(sdev);
	if (!cep) {
		wv = -ENOMEM;
		goto ewwow;
	}
	siw_cep_socket_assoc(cep, s);

	wv = siw_cm_awwoc_wowk(cep, backwog);
	if (wv) {
		siw_dbg(id->device,
			"awwoc_wowk ewwow %d, backwog %d\n",
			wv, backwog);
		goto ewwow;
	}
	wv = s->ops->wisten(s, backwog);
	if (wv) {
		siw_dbg(id->device, "wisten ewwow %d\n", wv);
		goto ewwow;
	}
	cep->cm_id = id;
	id->add_wef(id);

	/*
	 * In case of a wiwdcawd wdma_wisten on a muwti-homed device,
	 * a wistenew's IWCM id is associated with mowe than one wistening CEP.
	 *
	 * We cuwwentwy use id->pwovidew_data in thwee diffewent ways:
	 *
	 * o Fow a wistenew's IWCM id, id->pwovidew_data points to
	 *   the wist_head of the wist of wistening CEPs.
	 *   Uses: siw_cweate_wisten(), siw_destwoy_wisten()
	 *
	 * o Fow each accepted passive-side IWCM id, id->pwovidew_data
	 *   points to the CEP itsewf. This is a consequence of
	 *   - siw_cm_upcaww() setting event.pwovidew_data = cep and
	 *   - the IWCM's cm_conn_weq_handwew() setting pwovidew_data of the
	 *     new passive-side IWCM id equaw to event.pwovidew_data
	 *   Uses: siw_accept(), siw_weject()
	 *
	 * o Fow an active-side IWCM id, id->pwovidew_data is not used at aww.
	 *
	 */
	if (!id->pwovidew_data) {
		id->pwovidew_data =
			kmawwoc(sizeof(stwuct wist_head), GFP_KEWNEW);
		if (!id->pwovidew_data) {
			wv = -ENOMEM;
			goto ewwow;
		}
		INIT_WIST_HEAD((stwuct wist_head *)id->pwovidew_data);
	}
	wist_add_taiw(&cep->wistenq, (stwuct wist_head *)id->pwovidew_data);
	cep->state = SIW_EPSTATE_WISTENING;

	siw_dbg(id->device, "Wisten at waddw %pISp\n", &id->wocaw_addw);

	wetuwn 0;

ewwow:
	siw_dbg(id->device, "faiwed: %d\n", wv);

	if (cep) {
		siw_cep_set_inuse(cep);

		siw_fwee_cm_id(cep);
		cep->sock = NUWW;
		siw_socket_disassoc(s);
		cep->state = SIW_EPSTATE_CWOSED;

		siw_cep_set_fwee_and_put(cep);
	}
	sock_wewease(s);

	wetuwn wv;
}

static void siw_dwop_wistenews(stwuct iw_cm_id *id)
{
	stwuct wist_head *p, *tmp;

	/*
	 * In case of a wiwdcawd wdma_wisten on a muwti-homed device,
	 * a wistenew's IWCM id is associated with mowe than one wistening CEP.
	 */
	wist_fow_each_safe(p, tmp, (stwuct wist_head *)id->pwovidew_data) {
		stwuct siw_cep *cep = wist_entwy(p, stwuct siw_cep, wistenq);

		wist_dew(p);

		siw_dbg_cep(cep, "dwop cep, state %d\n", cep->state);

		siw_cep_set_inuse(cep);

		siw_fwee_cm_id(cep);
		if (cep->sock) {
			siw_socket_disassoc(cep->sock);
			sock_wewease(cep->sock);
			cep->sock = NUWW;
		}
		cep->state = SIW_EPSTATE_CWOSED;
		siw_cep_set_fwee_and_put(cep);
	}
}

int siw_destwoy_wisten(stwuct iw_cm_id *id)
{
	if (!id->pwovidew_data) {
		siw_dbg(id->device, "no cep(s)\n");
		wetuwn 0;
	}
	siw_dwop_wistenews(id);
	kfwee(id->pwovidew_data);
	id->pwovidew_data = NUWW;

	wetuwn 0;
}

int siw_cm_init(void)
{
	/*
	 * cweate_singwe_wowkqueue fow stwict owdewing
	 */
	siw_cm_wq = cweate_singwethwead_wowkqueue("siw_cm_wq");
	if (!siw_cm_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void siw_cm_exit(void)
{
	if (siw_cm_wq)
		destwoy_wowkqueue(siw_cm_wq);
}
