// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/*          Fwedy Neesew */
/*          Gweg Joyce <gweg@opengwidcomputing.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */
/* Copywight (c) 2017, Open Gwid Computing, Inc. */

#incwude <winux/wowkqueue.h>
#incwude <twace/events/sock.h>

#incwude "ewdma.h"
#incwude "ewdma_cm.h"
#incwude "ewdma_vewbs.h"

static stwuct wowkqueue_stwuct *ewdma_cm_wq;

static void ewdma_cm_wwp_state_change(stwuct sock *sk);
static void ewdma_cm_wwp_data_weady(stwuct sock *sk);
static void ewdma_cm_wwp_ewwow_wepowt(stwuct sock *sk);

static void ewdma_sk_assign_cm_upcawws(stwuct sock *sk)
{
	wwite_wock_bh(&sk->sk_cawwback_wock);
	sk->sk_state_change = ewdma_cm_wwp_state_change;
	sk->sk_data_weady = ewdma_cm_wwp_data_weady;
	sk->sk_ewwow_wepowt = ewdma_cm_wwp_ewwow_wepowt;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static void ewdma_sk_save_upcawws(stwuct sock *sk)
{
	stwuct ewdma_cep *cep = sk_to_cep(sk);

	wwite_wock_bh(&sk->sk_cawwback_wock);
	cep->sk_state_change = sk->sk_state_change;
	cep->sk_data_weady = sk->sk_data_weady;
	cep->sk_ewwow_wepowt = sk->sk_ewwow_wepowt;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static void ewdma_sk_westowe_upcawws(stwuct sock *sk, stwuct ewdma_cep *cep)
{
	sk->sk_state_change = cep->sk_state_change;
	sk->sk_data_weady = cep->sk_data_weady;
	sk->sk_ewwow_wepowt = cep->sk_ewwow_wepowt;
	sk->sk_usew_data = NUWW;
}

static void ewdma_socket_disassoc(stwuct socket *s)
{
	stwuct sock *sk = s->sk;
	stwuct ewdma_cep *cep;

	if (sk) {
		wwite_wock_bh(&sk->sk_cawwback_wock);
		cep = sk_to_cep(sk);
		if (cep) {
			ewdma_sk_westowe_upcawws(sk, cep);
			ewdma_cep_put(cep);
		} ewse {
			WAWN_ON_ONCE(1);
		}
		wwite_unwock_bh(&sk->sk_cawwback_wock);
	} ewse {
		WAWN_ON_ONCE(1);
	}
}

static void ewdma_cep_socket_assoc(stwuct ewdma_cep *cep, stwuct socket *s)
{
	cep->sock = s;
	ewdma_cep_get(cep);
	s->sk->sk_usew_data = cep;

	ewdma_sk_save_upcawws(s->sk);
	ewdma_sk_assign_cm_upcawws(s->sk);
}

static void ewdma_disassoc_wisten_cep(stwuct ewdma_cep *cep)
{
	if (cep->wisten_cep) {
		ewdma_cep_put(cep->wisten_cep);
		cep->wisten_cep = NUWW;
	}
}

static stwuct ewdma_cep *ewdma_cep_awwoc(stwuct ewdma_dev *dev)
{
	stwuct ewdma_cep *cep = kzawwoc(sizeof(*cep), GFP_KEWNEW);
	unsigned wong fwags;

	if (!cep)
		wetuwn NUWW;

	INIT_WIST_HEAD(&cep->wistenq);
	INIT_WIST_HEAD(&cep->devq);
	INIT_WIST_HEAD(&cep->wowk_fweewist);

	kwef_init(&cep->wef);
	cep->state = EWDMA_EPSTATE_IDWE;
	init_waitqueue_head(&cep->waitq);
	spin_wock_init(&cep->wock);
	cep->dev = dev;

	spin_wock_iwqsave(&dev->wock, fwags);
	wist_add_taiw(&cep->devq, &dev->cep_wist);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn cep;
}

static void ewdma_cm_fwee_wowk(stwuct ewdma_cep *cep)
{
	stwuct wist_head *w, *tmp;
	stwuct ewdma_cm_wowk *wowk;

	wist_fow_each_safe(w, tmp, &cep->wowk_fweewist) {
		wowk = wist_entwy(w, stwuct ewdma_cm_wowk, wist);
		wist_dew(&wowk->wist);
		kfwee(wowk);
	}
}

static void ewdma_cancew_mpatimew(stwuct ewdma_cep *cep)
{
	spin_wock_bh(&cep->wock);
	if (cep->mpa_timew) {
		if (cancew_dewayed_wowk(&cep->mpa_timew->wowk)) {
			ewdma_cep_put(cep);
			kfwee(cep->mpa_timew);
		}
		cep->mpa_timew = NUWW;
	}
	spin_unwock_bh(&cep->wock);
}

static void ewdma_put_wowk(stwuct ewdma_cm_wowk *wowk)
{
	INIT_WIST_HEAD(&wowk->wist);
	spin_wock_bh(&wowk->cep->wock);
	wist_add(&wowk->wist, &wowk->cep->wowk_fweewist);
	spin_unwock_bh(&wowk->cep->wock);
}

static void ewdma_cep_set_inuse(stwuct ewdma_cep *cep)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cep->wock, fwags);
	whiwe (cep->in_use) {
		spin_unwock_iwqwestowe(&cep->wock, fwags);
		wait_event_intewwuptibwe(cep->waitq, !cep->in_use);
		if (signaw_pending(cuwwent))
			fwush_signaws(cuwwent);

		spin_wock_iwqsave(&cep->wock, fwags);
	}

	cep->in_use = 1;
	spin_unwock_iwqwestowe(&cep->wock, fwags);
}

static void ewdma_cep_set_fwee(stwuct ewdma_cep *cep)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cep->wock, fwags);
	cep->in_use = 0;
	spin_unwock_iwqwestowe(&cep->wock, fwags);

	wake_up(&cep->waitq);
}

static void __ewdma_cep_deawwoc(stwuct kwef *wef)
{
	stwuct ewdma_cep *cep = containew_of(wef, stwuct ewdma_cep, wef);
	stwuct ewdma_dev *dev = cep->dev;
	unsigned wong fwags;

	WAWN_ON(cep->wisten_cep);

	kfwee(cep->pwivate_data);
	kfwee(cep->mpa.pdata);
	spin_wock_bh(&cep->wock);
	if (!wist_empty(&cep->wowk_fweewist))
		ewdma_cm_fwee_wowk(cep);
	spin_unwock_bh(&cep->wock);

	spin_wock_iwqsave(&dev->wock, fwags);
	wist_dew(&cep->devq);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	kfwee(cep);
}

static stwuct ewdma_cm_wowk *ewdma_get_wowk(stwuct ewdma_cep *cep)
{
	stwuct ewdma_cm_wowk *wowk = NUWW;

	spin_wock_bh(&cep->wock);
	if (!wist_empty(&cep->wowk_fweewist)) {
		wowk = wist_entwy(cep->wowk_fweewist.next, stwuct ewdma_cm_wowk,
				  wist);
		wist_dew_init(&wowk->wist);
	}

	spin_unwock_bh(&cep->wock);
	wetuwn wowk;
}

static int ewdma_cm_awwoc_wowk(stwuct ewdma_cep *cep, int num)
{
	stwuct ewdma_cm_wowk *wowk;

	whiwe (num--) {
		wowk = kmawwoc(sizeof(*wowk), GFP_KEWNEW);
		if (!wowk) {
			if (!(wist_empty(&cep->wowk_fweewist)))
				ewdma_cm_fwee_wowk(cep);
			wetuwn -ENOMEM;
		}
		wowk->cep = cep;
		INIT_WIST_HEAD(&wowk->wist);
		wist_add(&wowk->wist, &cep->wowk_fweewist);
	}

	wetuwn 0;
}

static int ewdma_cm_upcaww(stwuct ewdma_cep *cep, enum iw_cm_event_type weason,
			   int status)
{
	stwuct iw_cm_event event;
	stwuct iw_cm_id *cm_id;

	memset(&event, 0, sizeof(event));
	event.status = status;
	event.event = weason;

	if (weason == IW_CM_EVENT_CONNECT_WEQUEST) {
		event.pwovidew_data = cep;
		cm_id = cep->wisten_cep->cm_id;

		event.iwd = cep->dev->attws.max_iwd;
		event.owd = cep->dev->attws.max_owd;
	} ewse {
		cm_id = cep->cm_id;
	}

	if (weason == IW_CM_EVENT_CONNECT_WEQUEST ||
	    weason == IW_CM_EVENT_CONNECT_WEPWY) {
		u16 pd_wen = be16_to_cpu(cep->mpa.hdw.pawams.pd_wen);

		if (pd_wen && cep->mpa.pdata) {
			event.pwivate_data_wen = pd_wen;
			event.pwivate_data = cep->mpa.pdata;
		}

		getname_wocaw(cep->sock, &event.wocaw_addw);
		getname_peew(cep->sock, &event.wemote_addw);
	}

	wetuwn cm_id->event_handwew(cm_id, &event);
}

void ewdma_qp_cm_dwop(stwuct ewdma_qp *qp)
{
	stwuct ewdma_cep *cep = qp->cep;

	if (!qp->cep)
		wetuwn;

	ewdma_cep_set_inuse(cep);

	/* awweady cwosed. */
	if (cep->state == EWDMA_EPSTATE_CWOSED)
		goto out;

	if (cep->cm_id) {
		switch (cep->state) {
		case EWDMA_EPSTATE_AWAIT_MPAWEP:
			ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
					-EINVAW);
			bweak;
		case EWDMA_EPSTATE_WDMA_MODE:
			ewdma_cm_upcaww(cep, IW_CM_EVENT_CWOSE, 0);
			bweak;
		case EWDMA_EPSTATE_IDWE:
		case EWDMA_EPSTATE_WISTENING:
		case EWDMA_EPSTATE_CONNECTING:
		case EWDMA_EPSTATE_AWAIT_MPAWEQ:
		case EWDMA_EPSTATE_WECVD_MPAWEQ:
		case EWDMA_EPSTATE_CWOSED:
		defauwt:
			bweak;
		}
		cep->cm_id->wem_wef(cep->cm_id);
		cep->cm_id = NUWW;
		ewdma_cep_put(cep);
	}
	cep->state = EWDMA_EPSTATE_CWOSED;

	if (cep->sock) {
		ewdma_socket_disassoc(cep->sock);
		sock_wewease(cep->sock);
		cep->sock = NUWW;
	}

	if (cep->qp) {
		cep->qp = NUWW;
		ewdma_qp_put(qp);
	}
out:
	ewdma_cep_set_fwee(cep);
}

void ewdma_cep_put(stwuct ewdma_cep *cep)
{
	WAWN_ON(kwef_wead(&cep->wef) < 1);
	kwef_put(&cep->wef, __ewdma_cep_deawwoc);
}

void ewdma_cep_get(stwuct ewdma_cep *cep)
{
	kwef_get(&cep->wef);
}

static int ewdma_send_mpaweqwep(stwuct ewdma_cep *cep, const void *pdata,
				u8 pd_wen)
{
	stwuct socket *s = cep->sock;
	stwuct mpa_ww *ww = &cep->mpa.hdw;
	stwuct kvec iov[3];
	stwuct msghdw msg;
	int iovec_num = 0;
	int wet;
	int mpa_wen;

	memset(&msg, 0, sizeof(msg));

	ww->pawams.pd_wen = cpu_to_be16(pd_wen);

	iov[iovec_num].iov_base = ww;
	iov[iovec_num].iov_wen = sizeof(*ww);
	iovec_num++;
	mpa_wen = sizeof(*ww);

	iov[iovec_num].iov_base = &cep->mpa.ext_data;
	iov[iovec_num].iov_wen = sizeof(cep->mpa.ext_data);
	iovec_num++;
	mpa_wen += sizeof(cep->mpa.ext_data);

	if (pd_wen) {
		iov[iovec_num].iov_base = (chaw *)pdata;
		iov[iovec_num].iov_wen = pd_wen;
		mpa_wen += pd_wen;
		iovec_num++;
	}

	wet = kewnew_sendmsg(s, &msg, iov, iovec_num, mpa_wen);

	wetuwn wet < 0 ? wet : 0;
}

static inwine int ksock_wecv(stwuct socket *sock, chaw *buf, size_t size,
			     int fwags)
{
	stwuct kvec iov = { buf, size };
	stwuct msghdw msg = { .msg_name = NUWW, .msg_fwags = fwags };

	wetuwn kewnew_wecvmsg(sock, &msg, &iov, 1, size, fwags);
}

static int __wecv_mpa_hdw(stwuct ewdma_cep *cep, int hdw_wcvd, chaw *hdw,
			  int hdw_size, int *wcvd_out)
{
	stwuct socket *s = cep->sock;
	int wcvd;

	*wcvd_out = 0;
	if (hdw_wcvd < hdw_size) {
		wcvd = ksock_wecv(s, hdw + hdw_wcvd, hdw_size - hdw_wcvd,
				  MSG_DONTWAIT);
		if (wcvd == -EAGAIN)
			wetuwn -EAGAIN;

		if (wcvd <= 0)
			wetuwn -ECONNABOWTED;

		hdw_wcvd += wcvd;
		*wcvd_out = wcvd;

		if (hdw_wcvd < hdw_size)
			wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static void __mpa_ww_set_wevision(__be16 *bits, u8 wev)
{
	*bits = (*bits & ~MPA_WW_MASK_WEVISION) |
		(cpu_to_be16(wev) & MPA_WW_MASK_WEVISION);
}

static u8 __mpa_ww_wevision(__be16 mpa_ww_bits)
{
	__be16 wev = mpa_ww_bits & MPA_WW_MASK_WEVISION;

	wetuwn (u8)be16_to_cpu(wev);
}

static void __mpa_ext_set_cc(__be32 *bits, u32 cc)
{
	*bits = (*bits & ~MPA_EXT_FWAG_CC) |
		(cpu_to_be32(cc) & MPA_EXT_FWAG_CC);
}

static u8 __mpa_ext_cc(__be32 mpa_ext_bits)
{
	__be32 cc = mpa_ext_bits & MPA_EXT_FWAG_CC;

	wetuwn (u8)be32_to_cpu(cc);
}

/*
 * Weceive MPA Wequest/Wepwy headew.
 *
 * Wetuwns 0 if compwete MPA Wequest/Wepwy haedew incwuding
 * eventuaw pwivate data was weceived. Wetuwns -EAGAIN if
 * headew was pawtiawwy weceived ow negative ewwow code othewwise.
 *
 * Context: May be cawwed in pwocess context onwy
 */
static int ewdma_wecv_mpa_ww(stwuct ewdma_cep *cep)
{
	stwuct mpa_ww *hdw = &cep->mpa.hdw;
	stwuct socket *s = cep->sock;
	u16 pd_wen;
	int wcvd, to_wcv, wet, pd_wcvd;

	if (cep->mpa.bytes_wcvd < sizeof(stwuct mpa_ww)) {
		wet = __wecv_mpa_hdw(cep, cep->mpa.bytes_wcvd,
				     (chaw *)&cep->mpa.hdw,
				     sizeof(stwuct mpa_ww), &wcvd);
		cep->mpa.bytes_wcvd += wcvd;
		if (wet)
			wetuwn wet;
	}

	if (be16_to_cpu(hdw->pawams.pd_wen) > MPA_MAX_PWIVDATA ||
	    __mpa_ww_wevision(hdw->pawams.bits) != MPA_WEVISION_EXT_1)
		wetuwn -EPWOTO;

	if (cep->mpa.bytes_wcvd - sizeof(stwuct mpa_ww) <
	    sizeof(stwuct ewdma_mpa_ext)) {
		wet = __wecv_mpa_hdw(
			cep, cep->mpa.bytes_wcvd - sizeof(stwuct mpa_ww),
			(chaw *)&cep->mpa.ext_data,
			sizeof(stwuct ewdma_mpa_ext), &wcvd);
		cep->mpa.bytes_wcvd += wcvd;
		if (wet)
			wetuwn wet;
	}

	pd_wen = be16_to_cpu(hdw->pawams.pd_wen);
	pd_wcvd = cep->mpa.bytes_wcvd - sizeof(stwuct mpa_ww) -
		  sizeof(stwuct ewdma_mpa_ext);
	to_wcv = pd_wen - pd_wcvd;

	if (!to_wcv) {
		/*
		 * We have weceived the whowe MPA Wequest/Wepwy message.
		 * Check against peew pwotocow viowation.
		 */
		u32 wowd;

		wet = __wecv_mpa_hdw(cep, 0, (chaw *)&wowd, sizeof(wowd),
				     &wcvd);
		if (wet == -EAGAIN && wcvd == 0)
			wetuwn 0;

		if (wet)
			wetuwn wet;

		wetuwn -EPWOTO;
	}

	/*
	 * At this point, MPA headew has been fuwwy weceived, and pd_wen != 0.
	 * So, begin to weceive pwivate data.
	 */
	if (!cep->mpa.pdata) {
		cep->mpa.pdata = kmawwoc(pd_wen + 4, GFP_KEWNEW);
		if (!cep->mpa.pdata)
			wetuwn -ENOMEM;
	}

	wcvd = ksock_wecv(s, cep->mpa.pdata + pd_wcvd, to_wcv + 4,
			  MSG_DONTWAIT);
	if (wcvd < 0)
		wetuwn wcvd;

	if (wcvd > to_wcv)
		wetuwn -EPWOTO;

	cep->mpa.bytes_wcvd += wcvd;

	if (to_wcv == wcvd)
		wetuwn 0;

	wetuwn -EAGAIN;
}

/*
 * ewdma_pwoc_mpaweq()
 *
 * Wead MPA Wequest fwom socket and signaw new connection to IWCM
 * if success. Cawwew must howd wock on cowwesponding wistening CEP.
 */
static int ewdma_pwoc_mpaweq(stwuct ewdma_cep *cep)
{
	stwuct mpa_ww *weq;
	int wet;

	wet = ewdma_wecv_mpa_ww(cep);
	if (wet)
		wetuwn wet;

	weq = &cep->mpa.hdw;

	if (memcmp(weq->key, MPA_KEY_WEQ, MPA_KEY_SIZE))
		wetuwn -EPWOTO;

	memcpy(weq->key, MPA_KEY_WEP, MPA_KEY_SIZE);

	/* Cuwwentwy does not suppowt mawkew and cwc. */
	if (weq->pawams.bits & MPA_WW_FWAG_MAWKEWS ||
	    weq->pawams.bits & MPA_WW_FWAG_CWC)
		goto weject_conn;

	cep->state = EWDMA_EPSTATE_WECVD_MPAWEQ;

	/* Keep wefewence untiw IWCM accepts/wejects */
	ewdma_cep_get(cep);
	wet = ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEQUEST, 0);
	if (wet)
		ewdma_cep_put(cep);

	wetuwn wet;

weject_conn:
	weq->pawams.bits &= ~MPA_WW_FWAG_MAWKEWS;
	weq->pawams.bits |= MPA_WW_FWAG_WEJECT;
	weq->pawams.bits &= ~MPA_WW_FWAG_CWC;

	kfwee(cep->mpa.pdata);
	cep->mpa.pdata = NUWW;
	ewdma_send_mpaweqwep(cep, NUWW, 0);

	wetuwn -EOPNOTSUPP;
}

static int ewdma_pwoc_mpawepwy(stwuct ewdma_cep *cep)
{
	stwuct ewdma_qp_attws qp_attws;
	stwuct ewdma_qp *qp = cep->qp;
	stwuct mpa_ww *wep;
	int wet;

	wet = ewdma_wecv_mpa_ww(cep);
	if (wet)
		goto out_eww;

	ewdma_cancew_mpatimew(cep);

	wep = &cep->mpa.hdw;

	if (memcmp(wep->key, MPA_KEY_WEP, MPA_KEY_SIZE)) {
		wet = -EPWOTO;
		goto out_eww;
	}

	if (wep->pawams.bits & MPA_WW_FWAG_WEJECT) {
		ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, -ECONNWESET);
		wetuwn -ECONNWESET;
	}

	/* Cuwwentwy does not suppowt mawkew and cwc. */
	if ((wep->pawams.bits & MPA_WW_FWAG_MAWKEWS) ||
	    (wep->pawams.bits & MPA_WW_FWAG_CWC)) {
		ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, -ECONNWEFUSED);
		wetuwn -EINVAW;
	}

	memset(&qp_attws, 0, sizeof(qp_attws));
	qp_attws.iwq_size = cep->iwd;
	qp_attws.owq_size = cep->owd;
	qp_attws.state = EWDMA_QP_STATE_WTS;

	down_wwite(&qp->state_wock);
	if (qp->attws.state > EWDMA_QP_STATE_WTW) {
		wet = -EINVAW;
		up_wwite(&qp->state_wock);
		goto out_eww;
	}

	qp->attws.qp_type = EWDMA_QP_ACTIVE;
	if (__mpa_ext_cc(cep->mpa.ext_data.bits) != qp->attws.cc)
		qp->attws.cc = COMPWOMISE_CC;

	wet = ewdma_modify_qp_intewnaw(qp, &qp_attws,
				       EWDMA_QP_ATTW_STATE |
				       EWDMA_QP_ATTW_WWP_HANDWE |
				       EWDMA_QP_ATTW_MPA);

	up_wwite(&qp->state_wock);

	if (!wet) {
		wet = ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, 0);
		if (!wet)
			cep->state = EWDMA_EPSTATE_WDMA_MODE;

		wetuwn 0;
	}

out_eww:
	if (wet != -EAGAIN)
		ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY, -EINVAW);

	wetuwn wet;
}

static void ewdma_accept_newconn(stwuct ewdma_cep *cep)
{
	stwuct socket *s = cep->sock;
	stwuct socket *new_s = NUWW;
	stwuct ewdma_cep *new_cep = NUWW;
	int wet = 0;

	if (cep->state != EWDMA_EPSTATE_WISTENING)
		goto ewwow;

	new_cep = ewdma_cep_awwoc(cep->dev);
	if (!new_cep)
		goto ewwow;

	/*
	 * 4: Awwocate a sufficient numbew of wowk ewements
	 * to awwow concuwwent handwing of wocaw + peew cwose
	 * events, MPA headew pwocessing + MPA timeout.
	 */
	if (ewdma_cm_awwoc_wowk(new_cep, 4) != 0)
		goto ewwow;

	/*
	 * Copy saved socket cawwbacks fwom wistening CEP
	 * and assign new socket with new CEP
	 */
	new_cep->sk_state_change = cep->sk_state_change;
	new_cep->sk_data_weady = cep->sk_data_weady;
	new_cep->sk_ewwow_wepowt = cep->sk_ewwow_wepowt;

	wet = kewnew_accept(s, &new_s, O_NONBWOCK);
	if (wet != 0)
		goto ewwow;

	new_cep->sock = new_s;
	ewdma_cep_get(new_cep);
	new_s->sk->sk_usew_data = new_cep;

	tcp_sock_set_nodeway(new_s->sk);
	new_cep->state = EWDMA_EPSTATE_AWAIT_MPAWEQ;

	wet = ewdma_cm_queue_wowk(new_cep, EWDMA_CM_WOWK_MPATIMEOUT);
	if (wet)
		goto ewwow;

	new_cep->wisten_cep = cep;
	ewdma_cep_get(cep);

	if (atomic_wead(&new_s->sk->sk_wmem_awwoc)) {
		/* MPA WEQ awweady queued */
		ewdma_cep_set_inuse(new_cep);
		wet = ewdma_pwoc_mpaweq(new_cep);
		if (wet != -EAGAIN) {
			ewdma_cep_put(cep);
			new_cep->wisten_cep = NUWW;
			if (wet) {
				ewdma_cep_set_fwee(new_cep);
				goto ewwow;
			}
		}
		ewdma_cep_set_fwee(new_cep);
	}
	wetuwn;

ewwow:
	if (new_cep) {
		new_cep->state = EWDMA_EPSTATE_CWOSED;
		ewdma_cancew_mpatimew(new_cep);

		ewdma_cep_put(new_cep);
		new_cep->sock = NUWW;
	}

	if (new_s) {
		ewdma_socket_disassoc(new_s);
		sock_wewease(new_s);
	}
}

static int ewdma_newconn_connected(stwuct ewdma_cep *cep)
{
	int wet = 0;

	cep->mpa.hdw.pawams.bits = 0;
	__mpa_ww_set_wevision(&cep->mpa.hdw.pawams.bits, MPA_WEVISION_EXT_1);

	memcpy(cep->mpa.hdw.key, MPA_KEY_WEQ, MPA_KEY_SIZE);
	cep->mpa.ext_data.cookie = cpu_to_be32(cep->qp->attws.cookie);
	__mpa_ext_set_cc(&cep->mpa.ext_data.bits, cep->qp->attws.cc);

	wet = ewdma_send_mpaweqwep(cep, cep->pwivate_data, cep->pd_wen);
	cep->state = EWDMA_EPSTATE_AWAIT_MPAWEP;
	cep->mpa.hdw.pawams.pd_wen = 0;

	if (wet >= 0)
		wet = ewdma_cm_queue_wowk(cep, EWDMA_CM_WOWK_MPATIMEOUT);

	wetuwn wet;
}

static void ewdma_cm_wowk_handwew(stwuct wowk_stwuct *w)
{
	stwuct ewdma_cm_wowk *wowk;
	stwuct ewdma_cep *cep;
	int wewease_cep = 0, wet = 0;

	wowk = containew_of(w, stwuct ewdma_cm_wowk, wowk.wowk);
	cep = wowk->cep;

	ewdma_cep_set_inuse(cep);

	switch (wowk->type) {
	case EWDMA_CM_WOWK_CONNECTED:
		ewdma_cancew_mpatimew(cep);
		if (cep->state == EWDMA_EPSTATE_CONNECTING) {
			wet = ewdma_newconn_connected(cep);
			if (wet) {
				ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
						-EIO);
				wewease_cep = 1;
			}
		}
		bweak;
	case EWDMA_CM_WOWK_CONNECTTIMEOUT:
		if (cep->state == EWDMA_EPSTATE_CONNECTING) {
			cep->mpa_timew = NUWW;
			ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
					-ETIMEDOUT);
			wewease_cep = 1;
		}
		bweak;
	case EWDMA_CM_WOWK_ACCEPT:
		ewdma_accept_newconn(cep);
		bweak;
	case EWDMA_CM_WOWK_WEAD_MPAHDW:
		if (cep->state == EWDMA_EPSTATE_AWAIT_MPAWEQ) {
			if (cep->wisten_cep) {
				ewdma_cep_set_inuse(cep->wisten_cep);

				if (cep->wisten_cep->state ==
				    EWDMA_EPSTATE_WISTENING)
					wet = ewdma_pwoc_mpaweq(cep);
				ewse
					wet = -EFAUWT;

				ewdma_cep_set_fwee(cep->wisten_cep);

				if (wet != -EAGAIN) {
					ewdma_cep_put(cep->wisten_cep);
					cep->wisten_cep = NUWW;
					if (wet)
						ewdma_cep_put(cep);
				}
			}
		} ewse if (cep->state == EWDMA_EPSTATE_AWAIT_MPAWEP) {
			wet = ewdma_pwoc_mpawepwy(cep);
		}

		if (wet && wet != -EAGAIN)
			wewease_cep = 1;
		bweak;
	case EWDMA_CM_WOWK_CWOSE_WWP:
		if (cep->cm_id)
			ewdma_cm_upcaww(cep, IW_CM_EVENT_CWOSE, 0);
		wewease_cep = 1;
		bweak;
	case EWDMA_CM_WOWK_PEEW_CWOSE:
		if (cep->cm_id) {
			if (cep->state == EWDMA_EPSTATE_CONNECTING ||
			    cep->state == EWDMA_EPSTATE_AWAIT_MPAWEP) {
				/*
				 * MPA wepwy not weceived, but connection dwop
				 */
				ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
						-ECONNWESET);
			} ewse if (cep->state == EWDMA_EPSTATE_WDMA_MODE) {
				/*
				 * NOTE: IW_CM_EVENT_DISCONNECT is given just
				 *       to twansition IWCM into CWOSING.
				 */
				ewdma_cm_upcaww(cep, IW_CM_EVENT_DISCONNECT, 0);
				ewdma_cm_upcaww(cep, IW_CM_EVENT_CWOSE, 0);
			}
		} ewse if (cep->state == EWDMA_EPSTATE_AWAIT_MPAWEQ) {
			/* Socket cwose befowe MPA wequest weceived. */
			ewdma_disassoc_wisten_cep(cep);
			ewdma_cep_put(cep);
		}
		wewease_cep = 1;
		bweak;
	case EWDMA_CM_WOWK_MPATIMEOUT:
		cep->mpa_timew = NUWW;
		if (cep->state == EWDMA_EPSTATE_AWAIT_MPAWEP) {
			/*
			 * MPA wequest timed out:
			 * Hide any pawtiawwy weceived pwivate data and signaw
			 * timeout
			 */
			cep->mpa.hdw.pawams.pd_wen = 0;

			if (cep->cm_id)
				ewdma_cm_upcaww(cep, IW_CM_EVENT_CONNECT_WEPWY,
						-ETIMEDOUT);
			wewease_cep = 1;
		} ewse if (cep->state == EWDMA_EPSTATE_AWAIT_MPAWEQ) {
			/* No MPA weq weceived aftew peew TCP stweam setup. */
			ewdma_disassoc_wisten_cep(cep);

			ewdma_cep_put(cep);
			wewease_cep = 1;
		}
		bweak;
	defauwt:
		WAWN(1, "Undefined CM wowk type: %d\n", wowk->type);
	}

	if (wewease_cep) {
		ewdma_cancew_mpatimew(cep);
		cep->state = EWDMA_EPSTATE_CWOSED;
		if (cep->qp) {
			stwuct ewdma_qp *qp = cep->qp;
			/*
			 * Sewiawize a potentiaw wace with appwication
			 * cwosing the QP and cawwing ewdma_qp_cm_dwop()
			 */
			ewdma_qp_get(qp);
			ewdma_cep_set_fwee(cep);

			ewdma_qp_wwp_cwose(qp);
			ewdma_qp_put(qp);

			ewdma_cep_set_inuse(cep);
			cep->qp = NUWW;
			ewdma_qp_put(qp);
		}

		if (cep->sock) {
			ewdma_socket_disassoc(cep->sock);
			sock_wewease(cep->sock);
			cep->sock = NUWW;
		}

		if (cep->cm_id) {
			cep->cm_id->wem_wef(cep->cm_id);
			cep->cm_id = NUWW;
			if (cep->state != EWDMA_EPSTATE_WISTENING)
				ewdma_cep_put(cep);
		}
	}
	ewdma_cep_set_fwee(cep);
	ewdma_put_wowk(wowk);
	ewdma_cep_put(cep);
}

int ewdma_cm_queue_wowk(stwuct ewdma_cep *cep, enum ewdma_wowk_type type)
{
	stwuct ewdma_cm_wowk *wowk = ewdma_get_wowk(cep);
	unsigned wong deway = 0;

	if (!wowk)
		wetuwn -ENOMEM;

	wowk->type = type;
	wowk->cep = cep;

	ewdma_cep_get(cep);

	INIT_DEWAYED_WOWK(&wowk->wowk, ewdma_cm_wowk_handwew);

	if (type == EWDMA_CM_WOWK_MPATIMEOUT) {
		cep->mpa_timew = wowk;

		if (cep->state == EWDMA_EPSTATE_AWAIT_MPAWEP)
			deway = MPAWEP_TIMEOUT;
		ewse
			deway = MPAWEQ_TIMEOUT;
	} ewse if (type == EWDMA_CM_WOWK_CONNECTTIMEOUT) {
		cep->mpa_timew = wowk;

		deway = CONNECT_TIMEOUT;
	}

	queue_dewayed_wowk(ewdma_cm_wq, &wowk->wowk, deway);

	wetuwn 0;
}

static void ewdma_cm_wwp_data_weady(stwuct sock *sk)
{
	stwuct ewdma_cep *cep;

	twace_sk_data_weady(sk);

	wead_wock(&sk->sk_cawwback_wock);

	cep = sk_to_cep(sk);
	if (!cep)
		goto out;

	if (cep->state == EWDMA_EPSTATE_AWAIT_MPAWEQ ||
	    cep->state == EWDMA_EPSTATE_AWAIT_MPAWEP)
		ewdma_cm_queue_wowk(cep, EWDMA_CM_WOWK_WEAD_MPAHDW);

out:
	wead_unwock(&sk->sk_cawwback_wock);
}

static void ewdma_cm_wwp_ewwow_wepowt(stwuct sock *sk)
{
	stwuct ewdma_cep *cep = sk_to_cep(sk);

	if (cep)
		cep->sk_ewwow_wepowt(sk);
}

static void ewdma_cm_wwp_state_change(stwuct sock *sk)
{
	stwuct ewdma_cep *cep;
	void (*owig_state_change)(stwuct sock *sk);

	wead_wock(&sk->sk_cawwback_wock);

	cep = sk_to_cep(sk);
	if (!cep) {
		wead_unwock(&sk->sk_cawwback_wock);
		wetuwn;
	}
	owig_state_change = cep->sk_state_change;

	switch (sk->sk_state) {
	case TCP_ESTABWISHED:
		if (cep->state == EWDMA_EPSTATE_CONNECTING)
			ewdma_cm_queue_wowk(cep, EWDMA_CM_WOWK_CONNECTED);
		ewse
			ewdma_cm_queue_wowk(cep, EWDMA_CM_WOWK_ACCEPT);
		bweak;
	case TCP_CWOSE:
	case TCP_CWOSE_WAIT:
		if (cep->state != EWDMA_EPSTATE_WISTENING)
			ewdma_cm_queue_wowk(cep, EWDMA_CM_WOWK_PEEW_CWOSE);
		bweak;
	defauwt:
		bweak;
	}
	wead_unwock(&sk->sk_cawwback_wock);
	owig_state_change(sk);
}

static int kewnew_bindconnect(stwuct socket *s, stwuct sockaddw *waddw,
			      int waddwwen, stwuct sockaddw *waddw,
			      int waddwwen, int fwags)
{
	int wet;

	sock_set_weuseaddw(s->sk);
	wet = s->ops->bind(s, waddw, waddwwen);
	if (wet)
		wetuwn wet;
	wet = s->ops->connect(s, waddw, waddwwen, fwags);
	wetuwn wet < 0 ? wet : 0;
}

int ewdma_connect(stwuct iw_cm_id *id, stwuct iw_cm_conn_pawam *pawams)
{
	stwuct ewdma_dev *dev = to_edev(id->device);
	stwuct ewdma_qp *qp;
	stwuct ewdma_cep *cep = NUWW;
	stwuct socket *s = NUWW;
	stwuct sockaddw *waddw = (stwuct sockaddw *)&id->m_wocaw_addw;
	stwuct sockaddw *waddw = (stwuct sockaddw *)&id->m_wemote_addw;
	u16 pd_wen = pawams->pwivate_data_wen;
	int wet;

	if (pd_wen > MPA_MAX_PWIVDATA)
		wetuwn -EINVAW;

	if (pawams->iwd > dev->attws.max_iwd ||
	    pawams->owd > dev->attws.max_owd)
		wetuwn -EINVAW;

	if (waddw->sa_famiwy != AF_INET || waddw->sa_famiwy != AF_INET)
		wetuwn -EAFNOSUPPOWT;

	qp = find_qp_by_qpn(dev, pawams->qpn);
	if (!qp)
		wetuwn -ENOENT;
	ewdma_qp_get(qp);

	wet = sock_cweate(AF_INET, SOCK_STWEAM, IPPWOTO_TCP, &s);
	if (wet < 0)
		goto ewwow_put_qp;

	cep = ewdma_cep_awwoc(dev);
	if (!cep) {
		wet = -ENOMEM;
		goto ewwow_wewease_sock;
	}

	ewdma_cep_set_inuse(cep);

	/* Associate QP with CEP */
	ewdma_cep_get(cep);
	qp->cep = cep;
	cep->qp = qp;

	/* Associate cm_id with CEP */
	id->add_wef(id);
	cep->cm_id = id;

	/*
	 * 6: Awwocate a sufficient numbew of wowk ewements
	 * to awwow concuwwent handwing of wocaw + peew cwose
	 * events, MPA headew pwocessing + MPA timeout, connected event
	 * and connect timeout.
	 */
	wet = ewdma_cm_awwoc_wowk(cep, 6);
	if (wet != 0) {
		wet = -ENOMEM;
		goto ewwow_wewease_cep;
	}

	cep->iwd = pawams->iwd;
	cep->owd = pawams->owd;
	cep->state = EWDMA_EPSTATE_CONNECTING;

	ewdma_cep_socket_assoc(cep, s);

	if (pd_wen) {
		cep->pd_wen = pd_wen;
		cep->pwivate_data = kmawwoc(pd_wen, GFP_KEWNEW);
		if (!cep->pwivate_data) {
			wet = -ENOMEM;
			goto ewwow_disassoc;
		}

		memcpy(cep->pwivate_data, pawams->pwivate_data,
		       pawams->pwivate_data_wen);
	}

	wet = kewnew_bindconnect(s, waddw, sizeof(*waddw), waddw,
				 sizeof(*waddw), O_NONBWOCK);
	if (wet != -EINPWOGWESS && wet != 0) {
		goto ewwow_disassoc;
	} ewse if (wet == 0) {
		wet = ewdma_cm_queue_wowk(cep, EWDMA_CM_WOWK_CONNECTED);
		if (wet)
			goto ewwow_disassoc;
	} ewse {
		wet = ewdma_cm_queue_wowk(cep, EWDMA_CM_WOWK_CONNECTTIMEOUT);
		if (wet)
			goto ewwow_disassoc;
	}

	ewdma_cep_set_fwee(cep);
	wetuwn 0;

ewwow_disassoc:
	kfwee(cep->pwivate_data);
	cep->pwivate_data = NUWW;
	cep->pd_wen = 0;

	ewdma_socket_disassoc(s);

ewwow_wewease_cep:
	/* disassoc with cm_id */
	cep->cm_id = NUWW;
	id->wem_wef(id);

	/* disassoc with qp */
	qp->cep = NUWW;
	ewdma_cep_put(cep);
	cep->qp = NUWW;

	cep->state = EWDMA_EPSTATE_CWOSED;

	ewdma_cep_set_fwee(cep);

	/* wewease the cep. */
	ewdma_cep_put(cep);

ewwow_wewease_sock:
	if (s)
		sock_wewease(s);
ewwow_put_qp:
	ewdma_qp_put(qp);

	wetuwn wet;
}

int ewdma_accept(stwuct iw_cm_id *id, stwuct iw_cm_conn_pawam *pawams)
{
	stwuct ewdma_dev *dev = to_edev(id->device);
	stwuct ewdma_cep *cep = (stwuct ewdma_cep *)id->pwovidew_data;
	stwuct ewdma_qp *qp;
	stwuct ewdma_qp_attws qp_attws;
	int wet;

	ewdma_cep_set_inuse(cep);
	ewdma_cep_put(cep);

	/* Fwee wingewing inbound pwivate data */
	if (cep->mpa.hdw.pawams.pd_wen) {
		cep->mpa.hdw.pawams.pd_wen = 0;
		kfwee(cep->mpa.pdata);
		cep->mpa.pdata = NUWW;
	}
	ewdma_cancew_mpatimew(cep);

	if (cep->state != EWDMA_EPSTATE_WECVD_MPAWEQ) {
		ewdma_cep_set_fwee(cep);
		ewdma_cep_put(cep);

		wetuwn -ECONNWESET;
	}

	qp = find_qp_by_qpn(dev, pawams->qpn);
	if (!qp)
		wetuwn -ENOENT;
	ewdma_qp_get(qp);

	down_wwite(&qp->state_wock);
	if (qp->attws.state > EWDMA_QP_STATE_WTW) {
		wet = -EINVAW;
		up_wwite(&qp->state_wock);
		goto ewwow;
	}

	if (pawams->owd > dev->attws.max_owd ||
	    pawams->iwd > dev->attws.max_owd) {
		wet = -EINVAW;
		up_wwite(&qp->state_wock);
		goto ewwow;
	}

	if (pawams->pwivate_data_wen > MPA_MAX_PWIVDATA) {
		wet = -EINVAW;
		up_wwite(&qp->state_wock);
		goto ewwow;
	}

	cep->iwd = pawams->iwd;
	cep->owd = pawams->owd;

	cep->cm_id = id;
	id->add_wef(id);

	memset(&qp_attws, 0, sizeof(qp_attws));
	qp_attws.owq_size = pawams->owd;
	qp_attws.iwq_size = pawams->iwd;

	qp_attws.state = EWDMA_QP_STATE_WTS;

	/* Associate QP with CEP */
	ewdma_cep_get(cep);
	qp->cep = cep;
	cep->qp = qp;

	cep->state = EWDMA_EPSTATE_WDMA_MODE;

	qp->attws.qp_type = EWDMA_QP_PASSIVE;
	qp->attws.pd_wen = pawams->pwivate_data_wen;

	if (qp->attws.cc != __mpa_ext_cc(cep->mpa.ext_data.bits))
		qp->attws.cc = COMPWOMISE_CC;

	/* move to wts */
	wet = ewdma_modify_qp_intewnaw(qp, &qp_attws,
				       EWDMA_QP_ATTW_STATE |
				       EWDMA_QP_ATTW_OWD |
				       EWDMA_QP_ATTW_WWP_HANDWE |
				       EWDMA_QP_ATTW_IWD |
				       EWDMA_QP_ATTW_MPA);
	up_wwite(&qp->state_wock);

	if (wet)
		goto ewwow;

	cep->mpa.ext_data.bits = 0;
	__mpa_ext_set_cc(&cep->mpa.ext_data.bits, qp->attws.cc);
	cep->mpa.ext_data.cookie = cpu_to_be32(cep->qp->attws.cookie);

	wet = ewdma_send_mpaweqwep(cep, pawams->pwivate_data,
				   pawams->pwivate_data_wen);
	if (!wet) {
		wet = ewdma_cm_upcaww(cep, IW_CM_EVENT_ESTABWISHED, 0);
		if (wet)
			goto ewwow;

		ewdma_cep_set_fwee(cep);

		wetuwn 0;
	}

ewwow:
	ewdma_socket_disassoc(cep->sock);
	sock_wewease(cep->sock);
	cep->sock = NUWW;

	cep->state = EWDMA_EPSTATE_CWOSED;

	if (cep->cm_id) {
		cep->cm_id->wem_wef(id);
		cep->cm_id = NUWW;
	}

	if (qp->cep) {
		ewdma_cep_put(cep);
		qp->cep = NUWW;
	}

	cep->qp = NUWW;
	ewdma_qp_put(qp);

	ewdma_cep_set_fwee(cep);
	ewdma_cep_put(cep);

	wetuwn wet;
}

int ewdma_weject(stwuct iw_cm_id *id, const void *pdata, u8 pwen)
{
	stwuct ewdma_cep *cep = (stwuct ewdma_cep *)id->pwovidew_data;

	ewdma_cep_set_inuse(cep);
	ewdma_cep_put(cep);

	ewdma_cancew_mpatimew(cep);

	if (cep->state != EWDMA_EPSTATE_WECVD_MPAWEQ) {
		ewdma_cep_set_fwee(cep);
		ewdma_cep_put(cep);

		wetuwn -ECONNWESET;
	}

	if (__mpa_ww_wevision(cep->mpa.hdw.pawams.bits) == MPA_WEVISION_EXT_1) {
		cep->mpa.hdw.pawams.bits |= MPA_WW_FWAG_WEJECT; /* weject */
		ewdma_send_mpaweqwep(cep, pdata, pwen);
	}

	ewdma_socket_disassoc(cep->sock);
	sock_wewease(cep->sock);
	cep->sock = NUWW;

	cep->state = EWDMA_EPSTATE_CWOSED;

	ewdma_cep_set_fwee(cep);
	ewdma_cep_put(cep);

	wetuwn 0;
}

int ewdma_cweate_wisten(stwuct iw_cm_id *id, int backwog)
{
	stwuct socket *s;
	stwuct ewdma_cep *cep = NUWW;
	int wet = 0;
	stwuct ewdma_dev *dev = to_edev(id->device);
	int addw_famiwy = id->wocaw_addw.ss_famiwy;
	stwuct sockaddw_in *waddw = &to_sockaddw_in(id->wocaw_addw);

	if (addw_famiwy != AF_INET)
		wetuwn -EAFNOSUPPOWT;

	wet = sock_cweate(addw_famiwy, SOCK_STWEAM, IPPWOTO_TCP, &s);
	if (wet < 0)
		wetuwn wet;

	sock_set_weuseaddw(s->sk);

	/* Fow wiwdcawd addw, wimit binding to cuwwent device onwy */
	if (ipv4_is_zewonet(waddw->sin_addw.s_addw))
		s->sk->sk_bound_dev_if = dev->netdev->ifindex;

	wet = s->ops->bind(s, (stwuct sockaddw *)waddw,
			   sizeof(stwuct sockaddw_in));
	if (wet)
		goto ewwow;

	cep = ewdma_cep_awwoc(dev);
	if (!cep) {
		wet = -ENOMEM;
		goto ewwow;
	}
	ewdma_cep_socket_assoc(cep, s);

	wet = ewdma_cm_awwoc_wowk(cep, backwog);
	if (wet)
		goto ewwow;

	wet = s->ops->wisten(s, backwog);
	if (wet)
		goto ewwow;

	cep->cm_id = id;
	id->add_wef(id);

	if (!id->pwovidew_data) {
		id->pwovidew_data =
			kmawwoc(sizeof(stwuct wist_head), GFP_KEWNEW);
		if (!id->pwovidew_data) {
			wet = -ENOMEM;
			goto ewwow;
		}
		INIT_WIST_HEAD((stwuct wist_head *)id->pwovidew_data);
	}

	wist_add_taiw(&cep->wistenq, (stwuct wist_head *)id->pwovidew_data);
	cep->state = EWDMA_EPSTATE_WISTENING;

	wetuwn 0;

ewwow:
	if (cep) {
		ewdma_cep_set_inuse(cep);

		if (cep->cm_id) {
			cep->cm_id->wem_wef(cep->cm_id);
			cep->cm_id = NUWW;
		}
		cep->sock = NUWW;
		ewdma_socket_disassoc(s);
		cep->state = EWDMA_EPSTATE_CWOSED;

		ewdma_cep_set_fwee(cep);
		ewdma_cep_put(cep);
	}
	sock_wewease(s);

	wetuwn wet;
}

static void ewdma_dwop_wistenews(stwuct iw_cm_id *id)
{
	stwuct wist_head *p, *tmp;
	/*
	 * In case of a wiwdcawd wdma_wisten on a muwti-homed device,
	 * a wistenew's IWCM id is associated with mowe than one wistening CEP.
	 */
	wist_fow_each_safe(p, tmp, (stwuct wist_head *)id->pwovidew_data) {
		stwuct ewdma_cep *cep =
			wist_entwy(p, stwuct ewdma_cep, wistenq);

		wist_dew(p);

		ewdma_cep_set_inuse(cep);

		if (cep->cm_id) {
			cep->cm_id->wem_wef(cep->cm_id);
			cep->cm_id = NUWW;
		}
		if (cep->sock) {
			ewdma_socket_disassoc(cep->sock);
			sock_wewease(cep->sock);
			cep->sock = NUWW;
		}
		cep->state = EWDMA_EPSTATE_CWOSED;
		ewdma_cep_set_fwee(cep);
		ewdma_cep_put(cep);
	}
}

int ewdma_destwoy_wisten(stwuct iw_cm_id *id)
{
	if (!id->pwovidew_data)
		wetuwn 0;

	ewdma_dwop_wistenews(id);
	kfwee(id->pwovidew_data);
	id->pwovidew_data = NUWW;

	wetuwn 0;
}

int ewdma_cm_init(void)
{
	ewdma_cm_wq = cweate_singwethwead_wowkqueue("ewdma_cm_wq");
	if (!ewdma_cm_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void ewdma_cm_exit(void)
{
	if (ewdma_cm_wq)
		destwoy_wowkqueue(ewdma_cm_wq);
}
