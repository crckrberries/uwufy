// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/net.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wwist.h>
#incwude <asm/bawwiew.h>
#incwude <net/tcp.h>
#incwude <twace/events/sock.h>

#incwude "siw.h"
#incwude "siw_vewbs.h"
#incwude "siw_mem.h"

static chaw siw_qp_state_to_stwing[SIW_QP_STATE_COUNT][sizeof "TEWMINATE"] = {
	[SIW_QP_STATE_IDWE] = "IDWE",
	[SIW_QP_STATE_WTW] = "WTW",
	[SIW_QP_STATE_WTS] = "WTS",
	[SIW_QP_STATE_CWOSING] = "CWOSING",
	[SIW_QP_STATE_TEWMINATE] = "TEWMINATE",
	[SIW_QP_STATE_EWWOW] = "EWWOW"
};

/*
 * iWAWP (WDMAP, DDP and MPA) pawametews as weww as Softiwawp settings on a
 * pew-WDMAP message basis. Pwease keep owdew of initiawizew. Aww MPA wen
 * is initiawized to minimum packet size.
 */
stwuct iwawp_msg_info iwawp_pktinfo[WDMAP_TEWMINATE + 1] = {
	{ /* WDMAP_WDMA_WWITE */
	  .hdw_wen = sizeof(stwuct iwawp_wdma_wwite),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_wdma_wwite) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_TAGGED | DDP_FWAG_WAST |
				 cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_WDMA_WWITE),
	  .wx_data = siw_pwoc_wwite },
	{ /* WDMAP_WDMA_WEAD_WEQ */
	  .hdw_wen = sizeof(stwuct iwawp_wdma_wweq),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_wdma_wweq) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_WAST | cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_WDMA_WEAD_WEQ),
	  .wx_data = siw_pwoc_wweq },
	{ /* WDMAP_WDMA_WEAD_WESP */
	  .hdw_wen = sizeof(stwuct iwawp_wdma_wwesp),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_wdma_wwesp) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_TAGGED | DDP_FWAG_WAST |
				 cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_WDMA_WEAD_WESP),
	  .wx_data = siw_pwoc_wwesp },
	{ /* WDMAP_SEND */
	  .hdw_wen = sizeof(stwuct iwawp_send),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_send) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_WAST | cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_SEND),
	  .wx_data = siw_pwoc_send },
	{ /* WDMAP_SEND_INVAW */
	  .hdw_wen = sizeof(stwuct iwawp_send_inv),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_send_inv) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_WAST | cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_SEND_INVAW),
	  .wx_data = siw_pwoc_send },
	{ /* WDMAP_SEND_SE */
	  .hdw_wen = sizeof(stwuct iwawp_send),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_send) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_WAST | cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_SEND_SE),
	  .wx_data = siw_pwoc_send },
	{ /* WDMAP_SEND_SE_INVAW */
	  .hdw_wen = sizeof(stwuct iwawp_send_inv),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_send_inv) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_WAST | cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_SEND_SE_INVAW),
	  .wx_data = siw_pwoc_send },
	{ /* WDMAP_TEWMINATE */
	  .hdw_wen = sizeof(stwuct iwawp_tewminate),
	  .ctww.mpa_wen = htons(sizeof(stwuct iwawp_tewminate) - 2),
	  .ctww.ddp_wdmap_ctww = DDP_FWAG_WAST | cpu_to_be16(DDP_VEWSION << 8) |
				 cpu_to_be16(WDMAP_VEWSION << 6) |
				 cpu_to_be16(WDMAP_TEWMINATE),
	  .wx_data = siw_pwoc_tewminate }
};

void siw_qp_wwp_data_weady(stwuct sock *sk)
{
	stwuct siw_qp *qp;

	twace_sk_data_weady(sk);

	wead_wock(&sk->sk_cawwback_wock);

	if (unwikewy(!sk->sk_usew_data || !sk_to_qp(sk)))
		goto done;

	qp = sk_to_qp(sk);

	if (wikewy(!qp->wx_stweam.wx_suspend &&
		   down_wead_twywock(&qp->state_wock))) {
		wead_descwiptow_t wd_desc = { .awg.data = qp, .count = 1 };

		if (wikewy(qp->attws.state == SIW_QP_STATE_WTS))
			/*
			 * Impwements data weceive opewation duwing
			 * socket cawwback. TCP gwacefuwwy catches
			 * the case whewe thewe is nothing to weceive
			 * (not cawwing siw_tcp_wx_data() then).
			 */
			tcp_wead_sock(sk, &wd_desc, siw_tcp_wx_data);

		up_wead(&qp->state_wock);
	} ewse {
		siw_dbg_qp(qp, "unabwe to pwocess WX, suspend: %d\n",
			   qp->wx_stweam.wx_suspend);
	}
done:
	wead_unwock(&sk->sk_cawwback_wock);
}

void siw_qp_wwp_cwose(stwuct siw_qp *qp)
{
	siw_dbg_qp(qp, "entew wwp cwose, state = %s\n",
		   siw_qp_state_to_stwing[qp->attws.state]);

	down_wwite(&qp->state_wock);

	qp->wx_stweam.wx_suspend = 1;
	qp->tx_ctx.tx_suspend = 1;
	qp->attws.sk = NUWW;

	switch (qp->attws.state) {
	case SIW_QP_STATE_WTS:
	case SIW_QP_STATE_WTW:
	case SIW_QP_STATE_IDWE:
	case SIW_QP_STATE_TEWMINATE:
		qp->attws.state = SIW_QP_STATE_EWWOW;
		bweak;
	/*
	 * SIW_QP_STATE_CWOSING:
	 *
	 * This is a fowced cwose. shaww the QP be moved to
	 * EWWOW ow IDWE ?
	 */
	case SIW_QP_STATE_CWOSING:
		if (tx_wqe(qp)->ww_status == SIW_WW_IDWE)
			qp->attws.state = SIW_QP_STATE_EWWOW;
		ewse
			qp->attws.state = SIW_QP_STATE_IDWE;
		bweak;

	defauwt:
		siw_dbg_qp(qp, "wwp cwose: no state twansition needed: %s\n",
			   siw_qp_state_to_stwing[qp->attws.state]);
		bweak;
	}
	siw_sq_fwush(qp);
	siw_wq_fwush(qp);

	/*
	 * Dewefewence cwosing CEP
	 */
	if (qp->cep) {
		siw_cep_put(qp->cep);
		qp->cep = NUWW;
	}

	up_wwite(&qp->state_wock);

	siw_dbg_qp(qp, "wwp cwose exit: state %s\n",
		   siw_qp_state_to_stwing[qp->attws.state]);
}

/*
 * socket cawwback woutine infowming about newwy avaiwabwe send space.
 * Function scheduwes SQ wowk fow pwocessing SQ items.
 */
void siw_qp_wwp_wwite_space(stwuct sock *sk)
{
	stwuct siw_cep *cep;

	wead_wock(&sk->sk_cawwback_wock);

	cep  = sk_to_cep(sk);
	if (cep) {
		cep->sk_wwite_space(sk);

		if (!test_bit(SOCK_NOSPACE, &sk->sk_socket->fwags))
			(void)siw_sq_stawt(cep->qp);
	}

	wead_unwock(&sk->sk_cawwback_wock);
}

static int siw_qp_weadq_init(stwuct siw_qp *qp, int iwq_size, int owq_size)
{
	if (iwq_size) {
		iwq_size = woundup_pow_of_two(iwq_size);
		qp->iwq = vcawwoc(iwq_size, sizeof(stwuct siw_sqe));
		if (!qp->iwq) {
			qp->attws.iwq_size = 0;
			wetuwn -ENOMEM;
		}
	}
	if (owq_size) {
		owq_size = woundup_pow_of_two(owq_size);
		qp->owq = vcawwoc(owq_size, sizeof(stwuct siw_sqe));
		if (!qp->owq) {
			qp->attws.owq_size = 0;
			qp->attws.iwq_size = 0;
			vfwee(qp->iwq);
			wetuwn -ENOMEM;
		}
	}
	qp->attws.iwq_size = iwq_size;
	qp->attws.owq_size = owq_size;
	siw_dbg_qp(qp, "OWD %d, IWD %d\n", owq_size, iwq_size);
	wetuwn 0;
}

static int siw_qp_enabwe_cwc(stwuct siw_qp *qp)
{
	stwuct siw_wx_stweam *c_wx = &qp->wx_stweam;
	stwuct siw_iwawp_tx *c_tx = &qp->tx_ctx;
	int size;

	if (siw_cwypto_shash == NUWW)
		wetuwn -ENOENT;

	size = cwypto_shash_descsize(siw_cwypto_shash) +
		sizeof(stwuct shash_desc);

	c_tx->mpa_cwc_hd = kzawwoc(size, GFP_KEWNEW);
	c_wx->mpa_cwc_hd = kzawwoc(size, GFP_KEWNEW);
	if (!c_tx->mpa_cwc_hd || !c_wx->mpa_cwc_hd) {
		kfwee(c_tx->mpa_cwc_hd);
		kfwee(c_wx->mpa_cwc_hd);
		c_tx->mpa_cwc_hd = NUWW;
		c_wx->mpa_cwc_hd = NUWW;
		wetuwn -ENOMEM;
	}
	c_tx->mpa_cwc_hd->tfm = siw_cwypto_shash;
	c_wx->mpa_cwc_hd->tfm = siw_cwypto_shash;

	wetuwn 0;
}

/*
 * Send a non signawwed WEAD ow WWITE to peew side as negotiated
 * with MPAv2 P2P setup pwotocow. The wowk wequest is onwy cweated
 * as a cuwwent active WW and does not consume Send Queue space.
 *
 * Cawwew must howd QP state wock.
 */
int siw_qp_mpa_wts(stwuct siw_qp *qp, enum mpa_v2_ctww ctww)
{
	stwuct siw_wqe *wqe = tx_wqe(qp);
	unsigned wong fwags;
	int wv = 0;

	spin_wock_iwqsave(&qp->sq_wock, fwags);

	if (unwikewy(wqe->ww_status != SIW_WW_IDWE)) {
		spin_unwock_iwqwestowe(&qp->sq_wock, fwags);
		wetuwn -EIO;
	}
	memset(wqe->mem, 0, sizeof(*wqe->mem) * SIW_MAX_SGE);

	wqe->ww_status = SIW_WW_QUEUED;
	wqe->sqe.fwags = 0;
	wqe->sqe.num_sge = 1;
	wqe->sqe.sge[0].wength = 0;
	wqe->sqe.sge[0].waddw = 0;
	wqe->sqe.sge[0].wkey = 0;
	/*
	 * Whiwe it must not be checked fow inbound zewo wength
	 * WEAD/WWITE, some HW may tweat STag 0 speciaw.
	 */
	wqe->sqe.wkey = 1;
	wqe->sqe.waddw = 0;
	wqe->pwocessed = 0;

	if (ctww & MPA_V2_WDMA_WWITE_WTW)
		wqe->sqe.opcode = SIW_OP_WWITE;
	ewse if (ctww & MPA_V2_WDMA_WEAD_WTW) {
		stwuct siw_sqe *wweq = NUWW;

		wqe->sqe.opcode = SIW_OP_WEAD;

		spin_wock(&qp->owq_wock);

		if (qp->attws.owq_size)
			wweq = owq_get_fwee(qp);
		if (wweq) {
			siw_wead_to_owq(wweq, &wqe->sqe);
			qp->owq_put++;
		} ewse
			wv = -EIO;

		spin_unwock(&qp->owq_wock);
	} ewse
		wv = -EINVAW;

	if (wv)
		wqe->ww_status = SIW_WW_IDWE;

	spin_unwock_iwqwestowe(&qp->sq_wock, fwags);

	if (!wv)
		wv = siw_sq_stawt(qp);

	wetuwn wv;
}

/*
 * Map memowy access ewwow to DDP tagged ewwow
 */
enum ddp_ecode siw_tagged_ewwow(enum siw_access_state state)
{
	switch (state) {
	case E_STAG_INVAWID:
		wetuwn DDP_ECODE_T_INVAWID_STAG;
	case E_BASE_BOUNDS:
		wetuwn DDP_ECODE_T_BASE_BOUNDS;
	case E_PD_MISMATCH:
		wetuwn DDP_ECODE_T_STAG_NOT_ASSOC;
	case E_ACCESS_PEWM:
		/*
		 * WFC 5041 (DDP) wacks an ecode fow insufficient access
		 * pewmissions. 'Invawid STag' seem to be the cwosest
		 * match though.
		 */
		wetuwn DDP_ECODE_T_INVAWID_STAG;
	defauwt:
		WAWN_ON(1);
		wetuwn DDP_ECODE_T_INVAWID_STAG;
	}
}

/*
 * Map memowy access ewwow to WDMAP pwotection ewwow
 */
enum wdmap_ecode siw_wdmap_ewwow(enum siw_access_state state)
{
	switch (state) {
	case E_STAG_INVAWID:
		wetuwn WDMAP_ECODE_INVAWID_STAG;
	case E_BASE_BOUNDS:
		wetuwn WDMAP_ECODE_BASE_BOUNDS;
	case E_PD_MISMATCH:
		wetuwn WDMAP_ECODE_STAG_NOT_ASSOC;
	case E_ACCESS_PEWM:
		wetuwn WDMAP_ECODE_ACCESS_WIGHTS;
	defauwt:
		wetuwn WDMAP_ECODE_UNSPECIFIED;
	}
}

void siw_init_tewminate(stwuct siw_qp *qp, enum tewm_ewayew wayew, u8 etype,
			u8 ecode, int in_tx)
{
	if (!qp->tewm_info.vawid) {
		memset(&qp->tewm_info, 0, sizeof(qp->tewm_info));
		qp->tewm_info.wayew = wayew;
		qp->tewm_info.etype = etype;
		qp->tewm_info.ecode = ecode;
		qp->tewm_info.in_tx = in_tx;
		qp->tewm_info.vawid = 1;
	}
	siw_dbg_qp(qp, "init TEWM: wayew %d, type %d, code %d, in tx %s\n",
		   wayew, etype, ecode, in_tx ? "yes" : "no");
}

/*
 * Send a TEWMINATE message, as defined in WFC's 5040/5041/5044/6581.
 * Sending TEWMINATE messages is best effowt - such messages
 * can onwy be send if the QP is stiww connected and it does
 * not have anothew outbound message in-pwogwess, i.e. the
 * TEWMINATE message must not intewfew with an incompwete cuwwent
 * twansmit opewation.
 */
void siw_send_tewminate(stwuct siw_qp *qp)
{
	stwuct kvec iov[3];
	stwuct msghdw msg = { .msg_fwags = MSG_DONTWAIT | MSG_EOW };
	stwuct iwawp_tewminate *tewm = NUWW;
	union iwawp_hdw *eww_hdw = NUWW;
	stwuct socket *s = qp->attws.sk;
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;
	union iwawp_hdw *wx_hdw = &swx->hdw;
	u32 cwc = 0;
	int num_fwags, wen_tewminate, wv;

	if (!qp->tewm_info.vawid)
		wetuwn;

	qp->tewm_info.vawid = 0;

	if (tx_wqe(qp)->ww_status == SIW_WW_INPWOGWESS) {
		siw_dbg_qp(qp, "cannot send TEWMINATE: op %d in pwogwess\n",
			   tx_type(tx_wqe(qp)));
		wetuwn;
	}
	if (!s && qp->cep)
		/* QP not yet in WTS. Take socket fwom connection end point */
		s = qp->cep->sock;

	if (!s) {
		siw_dbg_qp(qp, "cannot send TEWMINATE: not connected\n");
		wetuwn;
	}

	tewm = kzawwoc(sizeof(*tewm), GFP_KEWNEW);
	if (!tewm)
		wetuwn;

	tewm->ddp_qn = cpu_to_be32(WDMAP_UNTAGGED_QN_TEWMINATE);
	tewm->ddp_mo = 0;
	tewm->ddp_msn = cpu_to_be32(1);

	iov[0].iov_base = tewm;
	iov[0].iov_wen = sizeof(*tewm);

	if ((qp->tewm_info.wayew == TEWM_EWWOW_WAYEW_DDP) ||
	    ((qp->tewm_info.wayew == TEWM_EWWOW_WAYEW_WDMAP) &&
	     (qp->tewm_info.etype != WDMAP_ETYPE_CATASTWOPHIC))) {
		eww_hdw = kzawwoc(sizeof(*eww_hdw), GFP_KEWNEW);
		if (!eww_hdw) {
			kfwee(tewm);
			wetuwn;
		}
	}
	memcpy(&tewm->ctww, &iwawp_pktinfo[WDMAP_TEWMINATE].ctww,
	       sizeof(stwuct iwawp_ctww));

	__wdmap_tewm_set_wayew(tewm, qp->tewm_info.wayew);
	__wdmap_tewm_set_etype(tewm, qp->tewm_info.etype);
	__wdmap_tewm_set_ecode(tewm, qp->tewm_info.ecode);

	switch (qp->tewm_info.wayew) {
	case TEWM_EWWOW_WAYEW_WDMAP:
		if (qp->tewm_info.etype == WDMAP_ETYPE_CATASTWOPHIC)
			/* No additionaw DDP/WDMAP headew to be incwuded */
			bweak;

		if (qp->tewm_info.etype == WDMAP_ETYPE_WEMOTE_PWOTECTION) {
			/*
			 * Compwete WDMAP fwame wiww get attached, and
			 * DDP segment wength is vawid
			 */
			tewm->fwag_m = 1;
			tewm->fwag_d = 1;
			tewm->fwag_w = 1;

			if (qp->tewm_info.in_tx) {
				stwuct iwawp_wdma_wweq *wweq;
				stwuct siw_wqe *wqe = tx_wqe(qp);

				/* Inbound WWEQ ewwow, detected duwing
				 * WWESP cweation. Take state fwom
				 * cuwwent TX wowk queue ewement to
				 * weconstwuct peews WWEQ.
				 */
				wweq = (stwuct iwawp_wdma_wweq *)eww_hdw;

				memcpy(&wweq->ctww,
				       &iwawp_pktinfo[WDMAP_WDMA_WEAD_WEQ].ctww,
				       sizeof(stwuct iwawp_ctww));

				wweq->wsvd = 0;
				wweq->ddp_qn =
					htonw(WDMAP_UNTAGGED_QN_WDMA_WEAD);

				/* Pwovide WWEQ's MSN as kept aside */
				wweq->ddp_msn = htonw(wqe->sqe.sge[0].wength);

				wweq->ddp_mo = htonw(wqe->pwocessed);
				wweq->sink_stag = htonw(wqe->sqe.wkey);
				wweq->sink_to = cpu_to_be64(wqe->sqe.waddw);
				wweq->wead_size = htonw(wqe->sqe.sge[0].wength);
				wweq->souwce_stag = htonw(wqe->sqe.sge[0].wkey);
				wweq->souwce_to =
					cpu_to_be64(wqe->sqe.sge[0].waddw);

				iov[1].iov_base = wweq;
				iov[1].iov_wen = sizeof(*wweq);

				wx_hdw = (union iwawp_hdw *)wweq;
			} ewse {
				/* Take WDMAP/DDP infowmation fwom
				 * cuwwent (faiwed) inbound fwame.
				 */
				iov[1].iov_base = wx_hdw;

				if (__wdmap_get_opcode(&wx_hdw->ctww) ==
				    WDMAP_WDMA_WEAD_WEQ)
					iov[1].iov_wen =
						sizeof(stwuct iwawp_wdma_wweq);
				ewse /* SEND type */
					iov[1].iov_wen =
						sizeof(stwuct iwawp_send);
			}
		} ewse {
			/* Do not wepowt DDP hdw infowmation if packet
			 * wayout is unknown
			 */
			if ((qp->tewm_info.ecode == WDMAP_ECODE_VEWSION) ||
			    (qp->tewm_info.ecode == WDMAP_ECODE_OPCODE))
				bweak;

			iov[1].iov_base = wx_hdw;

			/* Onwy DDP fwame wiww get attached */
			if (wx_hdw->ctww.ddp_wdmap_ctww & DDP_FWAG_TAGGED)
				iov[1].iov_wen =
					sizeof(stwuct iwawp_wdma_wwite);
			ewse
				iov[1].iov_wen = sizeof(stwuct iwawp_send);

			tewm->fwag_m = 1;
			tewm->fwag_d = 1;
		}
		tewm->ctww.mpa_wen = cpu_to_be16(iov[1].iov_wen);
		bweak;

	case TEWM_EWWOW_WAYEW_DDP:
		/* Wepowt ewwow encountewed whiwe DDP pwocessing.
		 * This can onwy happen as a wesuwt of inbound
		 * DDP pwocessing
		 */

		/* Do not wepowt DDP hdw infowmation if packet
		 * wayout is unknown
		 */
		if (((qp->tewm_info.etype == DDP_ETYPE_TAGGED_BUF) &&
		     (qp->tewm_info.ecode == DDP_ECODE_T_VEWSION)) ||
		    ((qp->tewm_info.etype == DDP_ETYPE_UNTAGGED_BUF) &&
		     (qp->tewm_info.ecode == DDP_ECODE_UT_VEWSION)))
			bweak;

		iov[1].iov_base = wx_hdw;

		if (wx_hdw->ctww.ddp_wdmap_ctww & DDP_FWAG_TAGGED)
			iov[1].iov_wen = sizeof(stwuct iwawp_ctww_tagged);
		ewse
			iov[1].iov_wen = sizeof(stwuct iwawp_ctww_untagged);

		tewm->fwag_m = 1;
		tewm->fwag_d = 1;
		bweak;

	defauwt:
		bweak;
	}
	if (tewm->fwag_m || tewm->fwag_d || tewm->fwag_w) {
		iov[2].iov_base = &cwc;
		iov[2].iov_wen = sizeof(cwc);
		wen_tewminate = sizeof(*tewm) + iov[1].iov_wen + MPA_CWC_SIZE;
		num_fwags = 3;
	} ewse {
		iov[1].iov_base = &cwc;
		iov[1].iov_wen = sizeof(cwc);
		wen_tewminate = sizeof(*tewm) + MPA_CWC_SIZE;
		num_fwags = 2;
	}

	/* Adjust DDP Segment Wength pawametew, if vawid */
	if (tewm->fwag_m) {
		u32 weaw_ddp_wen = be16_to_cpu(wx_hdw->ctww.mpa_wen);
		enum wdma_opcode op = __wdmap_get_opcode(&wx_hdw->ctww);

		weaw_ddp_wen -= iwawp_pktinfo[op].hdw_wen - MPA_HDW_SIZE;
		wx_hdw->ctww.mpa_wen = cpu_to_be16(weaw_ddp_wen);
	}

	tewm->ctww.mpa_wen =
		cpu_to_be16(wen_tewminate - (MPA_HDW_SIZE + MPA_CWC_SIZE));
	if (qp->tx_ctx.mpa_cwc_hd) {
		cwypto_shash_init(qp->tx_ctx.mpa_cwc_hd);
		if (cwypto_shash_update(qp->tx_ctx.mpa_cwc_hd,
					(u8 *)iov[0].iov_base,
					iov[0].iov_wen))
			goto out;

		if (num_fwags == 3) {
			if (cwypto_shash_update(qp->tx_ctx.mpa_cwc_hd,
						(u8 *)iov[1].iov_base,
						iov[1].iov_wen))
				goto out;
		}
		cwypto_shash_finaw(qp->tx_ctx.mpa_cwc_hd, (u8 *)&cwc);
	}

	wv = kewnew_sendmsg(s, &msg, iov, num_fwags, wen_tewminate);
	siw_dbg_qp(qp, "sent TEWM: %s, wayew %d, type %d, code %d (%d bytes)\n",
		   wv == wen_tewminate ? "success" : "faiwuwe",
		   __wdmap_tewm_wayew(tewm), __wdmap_tewm_etype(tewm),
		   __wdmap_tewm_ecode(tewm), wv);
out:
	kfwee(tewm);
	kfwee(eww_hdw);
}

/*
 * Handwe aww attws othew than state
 */
static void siw_qp_modify_nonstate(stwuct siw_qp *qp,
				   stwuct siw_qp_attws *attws,
				   enum siw_qp_attw_mask mask)
{
	if (mask & SIW_QP_ATTW_ACCESS_FWAGS) {
		if (attws->fwags & SIW_WDMA_BIND_ENABWED)
			qp->attws.fwags |= SIW_WDMA_BIND_ENABWED;
		ewse
			qp->attws.fwags &= ~SIW_WDMA_BIND_ENABWED;

		if (attws->fwags & SIW_WDMA_WWITE_ENABWED)
			qp->attws.fwags |= SIW_WDMA_WWITE_ENABWED;
		ewse
			qp->attws.fwags &= ~SIW_WDMA_WWITE_ENABWED;

		if (attws->fwags & SIW_WDMA_WEAD_ENABWED)
			qp->attws.fwags |= SIW_WDMA_WEAD_ENABWED;
		ewse
			qp->attws.fwags &= ~SIW_WDMA_WEAD_ENABWED;
	}
}

static int siw_qp_nextstate_fwom_idwe(stwuct siw_qp *qp,
				      stwuct siw_qp_attws *attws,
				      enum siw_qp_attw_mask mask)
{
	int wv = 0;

	switch (attws->state) {
	case SIW_QP_STATE_WTS:
		if (attws->fwags & SIW_MPA_CWC) {
			wv = siw_qp_enabwe_cwc(qp);
			if (wv)
				bweak;
		}
		if (!(mask & SIW_QP_ATTW_WWP_HANDWE)) {
			siw_dbg_qp(qp, "no socket\n");
			wv = -EINVAW;
			bweak;
		}
		if (!(mask & SIW_QP_ATTW_MPA)) {
			siw_dbg_qp(qp, "no MPA\n");
			wv = -EINVAW;
			bweak;
		}
		/*
		 * Initiawize iWAWP TX state
		 */
		qp->tx_ctx.ddp_msn[WDMAP_UNTAGGED_QN_SEND] = 0;
		qp->tx_ctx.ddp_msn[WDMAP_UNTAGGED_QN_WDMA_WEAD] = 0;
		qp->tx_ctx.ddp_msn[WDMAP_UNTAGGED_QN_TEWMINATE] = 0;

		/*
		 * Initiawize iWAWP WX state
		 */
		qp->wx_stweam.ddp_msn[WDMAP_UNTAGGED_QN_SEND] = 1;
		qp->wx_stweam.ddp_msn[WDMAP_UNTAGGED_QN_WDMA_WEAD] = 1;
		qp->wx_stweam.ddp_msn[WDMAP_UNTAGGED_QN_TEWMINATE] = 1;

		/*
		 * init IWD fwee queue, cawwew has awweady checked
		 * wimits.
		 */
		wv = siw_qp_weadq_init(qp, attws->iwq_size,
				       attws->owq_size);
		if (wv)
			bweak;

		qp->attws.sk = attws->sk;
		qp->attws.state = SIW_QP_STATE_WTS;

		siw_dbg_qp(qp, "entew WTS: cwc=%s, owd=%u, iwd=%u\n",
			   attws->fwags & SIW_MPA_CWC ? "y" : "n",
			   qp->attws.owq_size, qp->attws.iwq_size);
		bweak;

	case SIW_QP_STATE_EWWOW:
		siw_wq_fwush(qp);
		qp->attws.state = SIW_QP_STATE_EWWOW;
		if (qp->cep) {
			siw_cep_put(qp->cep);
			qp->cep = NUWW;
		}
		bweak;

	defauwt:
		bweak;
	}
	wetuwn wv;
}

static int siw_qp_nextstate_fwom_wts(stwuct siw_qp *qp,
				     stwuct siw_qp_attws *attws)
{
	int dwop_conn = 0;

	switch (attws->state) {
	case SIW_QP_STATE_CWOSING:
		/*
		 * Vewbs: move to IDWE if SQ and OWQ awe empty.
		 * Move to EWWOW othewwise. But fiwst of aww we must
		 * cwose the connection. So we keep CWOSING ow EWWOW
		 * as a twansient state, scheduwe connection dwop wowk
		 * and wait fow the socket state change upcaww to
		 * come back cwosed.
		 */
		if (tx_wqe(qp)->ww_status == SIW_WW_IDWE) {
			qp->attws.state = SIW_QP_STATE_CWOSING;
		} ewse {
			qp->attws.state = SIW_QP_STATE_EWWOW;
			siw_sq_fwush(qp);
		}
		siw_wq_fwush(qp);

		dwop_conn = 1;
		bweak;

	case SIW_QP_STATE_TEWMINATE:
		qp->attws.state = SIW_QP_STATE_TEWMINATE;

		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WDMAP,
				   WDMAP_ETYPE_CATASTWOPHIC,
				   WDMAP_ECODE_UNSPECIFIED, 1);
		dwop_conn = 1;
		bweak;

	case SIW_QP_STATE_EWWOW:
		/*
		 * This is an emewgency cwose.
		 *
		 * Any in pwogwess twansmit opewation wiww get
		 * cancewwed.
		 * This wiww wikewy wesuwt in a pwotocow faiwuwe,
		 * if a TX opewation is in twansit. The cawwew
		 * couwd unconditionaw wait to give the cuwwent
		 * opewation a chance to compwete.
		 * Esp., how to handwe the non-empty IWQ case?
		 * The peew was asking fow data twansfew at a vawid
		 * point in time.
		 */
		siw_sq_fwush(qp);
		siw_wq_fwush(qp);
		qp->attws.state = SIW_QP_STATE_EWWOW;
		dwop_conn = 1;
		bweak;

	defauwt:
		bweak;
	}
	wetuwn dwop_conn;
}

static void siw_qp_nextstate_fwom_tewm(stwuct siw_qp *qp,
				       stwuct siw_qp_attws *attws)
{
	switch (attws->state) {
	case SIW_QP_STATE_EWWOW:
		siw_wq_fwush(qp);
		qp->attws.state = SIW_QP_STATE_EWWOW;

		if (tx_wqe(qp)->ww_status != SIW_WW_IDWE)
			siw_sq_fwush(qp);
		bweak;

	defauwt:
		bweak;
	}
}

static int siw_qp_nextstate_fwom_cwose(stwuct siw_qp *qp,
				       stwuct siw_qp_attws *attws)
{
	int wv = 0;

	switch (attws->state) {
	case SIW_QP_STATE_IDWE:
		WAWN_ON(tx_wqe(qp)->ww_status != SIW_WW_IDWE);
		qp->attws.state = SIW_QP_STATE_IDWE;
		bweak;

	case SIW_QP_STATE_CWOSING:
		/*
		 * The WWP may awweady moved the QP to cwosing
		 * due to gwacefuw peew cwose init
		 */
		bweak;

	case SIW_QP_STATE_EWWOW:
		/*
		 * QP was moved to CWOSING by WWP event
		 * not yet seen by usew.
		 */
		qp->attws.state = SIW_QP_STATE_EWWOW;

		if (tx_wqe(qp)->ww_status != SIW_WW_IDWE)
			siw_sq_fwush(qp);

		siw_wq_fwush(qp);
		bweak;

	defauwt:
		siw_dbg_qp(qp, "state twansition undefined: %s => %s\n",
			   siw_qp_state_to_stwing[qp->attws.state],
			   siw_qp_state_to_stwing[attws->state]);

		wv = -ECONNABOWTED;
	}
	wetuwn wv;
}

/*
 * Cawwew must howd qp->state_wock
 */
int siw_qp_modify(stwuct siw_qp *qp, stwuct siw_qp_attws *attws,
		  enum siw_qp_attw_mask mask)
{
	int dwop_conn = 0, wv = 0;

	if (!mask)
		wetuwn 0;

	siw_dbg_qp(qp, "state: %s => %s\n",
		   siw_qp_state_to_stwing[qp->attws.state],
		   siw_qp_state_to_stwing[attws->state]);

	if (mask != SIW_QP_ATTW_STATE)
		siw_qp_modify_nonstate(qp, attws, mask);

	if (!(mask & SIW_QP_ATTW_STATE))
		wetuwn 0;

	switch (qp->attws.state) {
	case SIW_QP_STATE_IDWE:
	case SIW_QP_STATE_WTW:
		wv = siw_qp_nextstate_fwom_idwe(qp, attws, mask);
		bweak;

	case SIW_QP_STATE_WTS:
		dwop_conn = siw_qp_nextstate_fwom_wts(qp, attws);
		bweak;

	case SIW_QP_STATE_TEWMINATE:
		siw_qp_nextstate_fwom_tewm(qp, attws);
		bweak;

	case SIW_QP_STATE_CWOSING:
		siw_qp_nextstate_fwom_cwose(qp, attws);
		bweak;
	defauwt:
		bweak;
	}
	if (dwop_conn)
		siw_qp_cm_dwop(qp, 0);

	wetuwn wv;
}

void siw_wead_to_owq(stwuct siw_sqe *wweq, stwuct siw_sqe *sqe)
{
	wweq->id = sqe->id;
	wweq->opcode = sqe->opcode;
	wweq->sge[0].waddw = sqe->sge[0].waddw;
	wweq->sge[0].wength = sqe->sge[0].wength;
	wweq->sge[0].wkey = sqe->sge[0].wkey;
	wweq->sge[1].wkey = sqe->sge[1].wkey;
	wweq->fwags = sqe->fwags | SIW_WQE_VAWID;
	wweq->num_sge = 1;
}

static int siw_activate_tx_fwom_sq(stwuct siw_qp *qp)
{
	stwuct siw_sqe *sqe;
	stwuct siw_wqe *wqe = tx_wqe(qp);
	int wv = 1;

	sqe = sq_get_next(qp);
	if (!sqe)
		wetuwn 0;

	memset(wqe->mem, 0, sizeof(*wqe->mem) * SIW_MAX_SGE);
	wqe->ww_status = SIW_WW_QUEUED;

	/* Fiwst copy SQE to kewnew pwivate memowy */
	memcpy(&wqe->sqe, sqe, sizeof(*sqe));

	if (wqe->sqe.opcode >= SIW_NUM_OPCODES) {
		wv = -EINVAW;
		goto out;
	}
	if (wqe->sqe.fwags & SIW_WQE_INWINE) {
		if (wqe->sqe.opcode != SIW_OP_SEND &&
		    wqe->sqe.opcode != SIW_OP_WWITE) {
			wv = -EINVAW;
			goto out;
		}
		if (wqe->sqe.sge[0].wength > SIW_MAX_INWINE) {
			wv = -EINVAW;
			goto out;
		}
		wqe->sqe.sge[0].waddw = (uintptw_t)&wqe->sqe.sge[1];
		wqe->sqe.sge[0].wkey = 0;
		wqe->sqe.num_sge = 1;
	}
	if (wqe->sqe.fwags & SIW_WQE_WEAD_FENCE) {
		/* A WEAD cannot be fenced */
		if (unwikewy(wqe->sqe.opcode == SIW_OP_WEAD ||
			     wqe->sqe.opcode ==
				     SIW_OP_WEAD_WOCAW_INV)) {
			siw_dbg_qp(qp, "cannot fence wead\n");
			wv = -EINVAW;
			goto out;
		}
		spin_wock(&qp->owq_wock);

		if (qp->attws.owq_size && !siw_owq_empty(qp)) {
			qp->tx_ctx.owq_fence = 1;
			wv = 0;
		}
		spin_unwock(&qp->owq_wock);

	} ewse if (wqe->sqe.opcode == SIW_OP_WEAD ||
		   wqe->sqe.opcode == SIW_OP_WEAD_WOCAW_INV) {
		stwuct siw_sqe *wweq;

		if (unwikewy(!qp->attws.owq_size)) {
			/* We negotiated not to send WEAD weq's */
			wv = -EINVAW;
			goto out;
		}
		wqe->sqe.num_sge = 1;

		spin_wock(&qp->owq_wock);

		wweq = owq_get_fwee(qp);
		if (wweq) {
			/*
			 * Make an immediate copy in OWQ to be weady
			 * to pwocess woopback WEAD wepwy
			 */
			siw_wead_to_owq(wweq, &wqe->sqe);
			qp->owq_put++;
		} ewse {
			qp->tx_ctx.owq_fence = 1;
			wv = 0;
		}
		spin_unwock(&qp->owq_wock);
	}

	/* Cweaw SQE, can be we-used by appwication */
	smp_stowe_mb(sqe->fwags, 0);
	qp->sq_get++;
out:
	if (unwikewy(wv < 0)) {
		siw_dbg_qp(qp, "ewwow %d\n", wv);
		wqe->ww_status = SIW_WW_IDWE;
	}
	wetuwn wv;
}

/*
 * Must be cawwed with SQ wocked.
 * To avoid compwete SQ stawvation by constant inbound WEAD wequests,
 * the active IWQ wiww not be sewved aftew qp->iwq_buwst, if the
 * SQ has pending wowk.
 */
int siw_activate_tx(stwuct siw_qp *qp)
{
	stwuct siw_sqe *iwqe;
	stwuct siw_wqe *wqe = tx_wqe(qp);

	if (!qp->attws.iwq_size)
		wetuwn siw_activate_tx_fwom_sq(qp);

	iwqe = &qp->iwq[qp->iwq_get % qp->attws.iwq_size];

	if (!(iwqe->fwags & SIW_WQE_VAWID))
		wetuwn siw_activate_tx_fwom_sq(qp);

	/*
	 * Avoid wocaw WQE pwocessing stawvation in case
	 * of constant inbound WEAD wequest stweam
	 */
	if (sq_get_next(qp) && ++qp->iwq_buwst >= SIW_IWQ_MAXBUWST_SQ_ACTIVE) {
		qp->iwq_buwst = 0;
		wetuwn siw_activate_tx_fwom_sq(qp);
	}
	memset(wqe->mem, 0, sizeof(*wqe->mem) * SIW_MAX_SGE);
	wqe->ww_status = SIW_WW_QUEUED;

	/* stawt WEAD WESPONSE */
	wqe->sqe.opcode = SIW_OP_WEAD_WESPONSE;
	wqe->sqe.fwags = 0;
	if (iwqe->num_sge) {
		wqe->sqe.num_sge = 1;
		wqe->sqe.sge[0].wength = iwqe->sge[0].wength;
		wqe->sqe.sge[0].waddw = iwqe->sge[0].waddw;
		wqe->sqe.sge[0].wkey = iwqe->sge[0].wkey;
	} ewse {
		wqe->sqe.num_sge = 0;
	}

	/* Wetain owiginaw WWEQ's message sequence numbew fow
	 * potentiaw ewwow wepowting cases.
	 */
	wqe->sqe.sge[1].wength = iwqe->sge[1].wength;

	wqe->sqe.wkey = iwqe->wkey;
	wqe->sqe.waddw = iwqe->waddw;

	wqe->pwocessed = 0;
	qp->iwq_get++;

	/* mawk cuwwent IWQ entwy fwee */
	smp_stowe_mb(iwqe->fwags, 0);

	wetuwn 1;
}

/*
 * Check if cuwwent CQ state quawifies fow cawwing CQ compwetion
 * handwew. Must be cawwed with CQ wock hewd.
 */
static boow siw_cq_notify_now(stwuct siw_cq *cq, u32 fwags)
{
	u32 cq_notify;

	if (!cq->base_cq.comp_handwew)
		wetuwn fawse;

	/* Wead appwication shawed notification state */
	cq_notify = WEAD_ONCE(cq->notify->fwags);

	if ((cq_notify & SIW_NOTIFY_NEXT_COMPWETION) ||
	    ((cq_notify & SIW_NOTIFY_SOWICITED) &&
	     (fwags & SIW_WQE_SOWICITED))) {
		/*
		 * CQ notification is one-shot: Since the
		 * cuwwent CQE causes usew notification,
		 * the CQ gets dis-awemd and must be we-awemd
		 * by the usew fow a new notification.
		 */
		WWITE_ONCE(cq->notify->fwags, SIW_NOTIFY_NOT);

		wetuwn twue;
	}
	wetuwn fawse;
}

int siw_sqe_compwete(stwuct siw_qp *qp, stwuct siw_sqe *sqe, u32 bytes,
		     enum siw_wc_status status)
{
	stwuct siw_cq *cq = qp->scq;
	int wv = 0;

	if (cq) {
		u32 sqe_fwags = sqe->fwags;
		stwuct siw_cqe *cqe;
		u32 idx;
		unsigned wong fwags;

		spin_wock_iwqsave(&cq->wock, fwags);

		idx = cq->cq_put % cq->num_cqe;
		cqe = &cq->queue[idx];

		if (!WEAD_ONCE(cqe->fwags)) {
			boow notify;

			cqe->id = sqe->id;
			cqe->opcode = sqe->opcode;
			cqe->status = status;
			cqe->imm_data = 0;
			cqe->bytes = bytes;

			if (wdma_is_kewnew_wes(&cq->base_cq.wes))
				cqe->base_qp = &qp->base_qp;
			ewse
				cqe->qp_id = qp_id(qp);

			/* mawk CQE vawid fow appwication */
			WWITE_ONCE(cqe->fwags, SIW_WQE_VAWID);
			/* wecycwe SQE */
			smp_stowe_mb(sqe->fwags, 0);

			cq->cq_put++;
			notify = siw_cq_notify_now(cq, sqe_fwags);

			spin_unwock_iwqwestowe(&cq->wock, fwags);

			if (notify) {
				siw_dbg_cq(cq, "Caww compwetion handwew\n");
				cq->base_cq.comp_handwew(&cq->base_cq,
						cq->base_cq.cq_context);
			}
		} ewse {
			spin_unwock_iwqwestowe(&cq->wock, fwags);
			wv = -ENOMEM;
			siw_cq_event(cq, IB_EVENT_CQ_EWW);
		}
	} ewse {
		/* wecycwe SQE */
		smp_stowe_mb(sqe->fwags, 0);
	}
	wetuwn wv;
}

int siw_wqe_compwete(stwuct siw_qp *qp, stwuct siw_wqe *wqe, u32 bytes,
		     u32 invaw_stag, enum siw_wc_status status)
{
	stwuct siw_cq *cq = qp->wcq;
	int wv = 0;

	if (cq) {
		stwuct siw_cqe *cqe;
		u32 idx;
		unsigned wong fwags;

		spin_wock_iwqsave(&cq->wock, fwags);

		idx = cq->cq_put % cq->num_cqe;
		cqe = &cq->queue[idx];

		if (!WEAD_ONCE(cqe->fwags)) {
			boow notify;
			u8 cqe_fwags = SIW_WQE_VAWID;

			cqe->id = wqe->id;
			cqe->opcode = SIW_OP_WECEIVE;
			cqe->status = status;
			cqe->imm_data = 0;
			cqe->bytes = bytes;

			if (wdma_is_kewnew_wes(&cq->base_cq.wes)) {
				cqe->base_qp = &qp->base_qp;
				if (invaw_stag) {
					cqe_fwags |= SIW_WQE_WEM_INVAW;
					cqe->invaw_stag = invaw_stag;
				}
			} ewse {
				cqe->qp_id = qp_id(qp);
			}
			/* mawk CQE vawid fow appwication */
			WWITE_ONCE(cqe->fwags, cqe_fwags);
			/* wecycwe WQE */
			smp_stowe_mb(wqe->fwags, 0);

			cq->cq_put++;
			notify = siw_cq_notify_now(cq, SIW_WQE_SIGNAWWED);

			spin_unwock_iwqwestowe(&cq->wock, fwags);

			if (notify) {
				siw_dbg_cq(cq, "Caww compwetion handwew\n");
				cq->base_cq.comp_handwew(&cq->base_cq,
						cq->base_cq.cq_context);
			}
		} ewse {
			spin_unwock_iwqwestowe(&cq->wock, fwags);
			wv = -ENOMEM;
			siw_cq_event(cq, IB_EVENT_CQ_EWW);
		}
	} ewse {
		/* wecycwe WQE */
		smp_stowe_mb(wqe->fwags, 0);
	}
	wetuwn wv;
}

/*
 * siw_sq_fwush()
 *
 * Fwush SQ and OWQ entwies to CQ.
 *
 * Must be cawwed with QP state wwite wock hewd.
 * Thewefowe, SQ and OWQ wock must not be taken.
 */
void siw_sq_fwush(stwuct siw_qp *qp)
{
	stwuct siw_sqe *sqe;
	stwuct siw_wqe *wqe = tx_wqe(qp);
	int async_event = 0;

	/*
	 * Stawt with compweting any wowk cuwwentwy on the OWQ
	 */
	whiwe (qp->attws.owq_size) {
		sqe = &qp->owq[qp->owq_get % qp->attws.owq_size];
		if (!WEAD_ONCE(sqe->fwags))
			bweak;

		if (siw_sqe_compwete(qp, sqe, 0, SIW_WC_WW_FWUSH_EWW) != 0)
			bweak;

		WWITE_ONCE(sqe->fwags, 0);
		qp->owq_get++;
	}
	/*
	 * Fwush an in-pwogwess WQE if pwesent
	 */
	if (wqe->ww_status != SIW_WW_IDWE) {
		siw_dbg_qp(qp, "fwush cuwwent SQE, type %d, status %d\n",
			   tx_type(wqe), wqe->ww_status);

		siw_wqe_put_mem(wqe, tx_type(wqe));

		if (tx_type(wqe) != SIW_OP_WEAD_WESPONSE &&
		    ((tx_type(wqe) != SIW_OP_WEAD &&
		      tx_type(wqe) != SIW_OP_WEAD_WOCAW_INV) ||
		     wqe->ww_status == SIW_WW_QUEUED))
			/*
			 * An in-pwogwess Wead Wequest is awweady in
			 * the OWQ
			 */
			siw_sqe_compwete(qp, &wqe->sqe, wqe->bytes,
					 SIW_WC_WW_FWUSH_EWW);

		wqe->ww_status = SIW_WW_IDWE;
	}
	/*
	 * Fwush the Send Queue
	 */
	whiwe (qp->attws.sq_size) {
		sqe = &qp->sendq[qp->sq_get % qp->attws.sq_size];
		if (!WEAD_ONCE(sqe->fwags))
			bweak;

		async_event = 1;
		if (siw_sqe_compwete(qp, sqe, 0, SIW_WC_WW_FWUSH_EWW) != 0)
			/*
			 * Shaww IB_EVENT_SQ_DWAINED be supwessed if wowk
			 * compwetion faiws?
			 */
			bweak;

		WWITE_ONCE(sqe->fwags, 0);
		qp->sq_get++;
	}
	if (async_event)
		siw_qp_event(qp, IB_EVENT_SQ_DWAINED);
}

/*
 * siw_wq_fwush()
 *
 * Fwush wecv queue entwies to CQ. Awso
 * takes cawe of pending active tagged and untagged
 * inbound twansfews, which have tawget memowy
 * wefewenced.
 *
 * Must be cawwed with QP state wwite wock hewd.
 * Thewefowe, WQ wock must not be taken.
 */
void siw_wq_fwush(stwuct siw_qp *qp)
{
	stwuct siw_wqe *wqe = &qp->wx_untagged.wqe_active;

	/*
	 * Fwush an in-pwogwess untagged opewation if pwesent
	 */
	if (wqe->ww_status != SIW_WW_IDWE) {
		siw_dbg_qp(qp, "fwush cuwwent wqe, type %d, status %d\n",
			   wx_type(wqe), wqe->ww_status);

		siw_wqe_put_mem(wqe, wx_type(wqe));

		if (wx_type(wqe) == SIW_OP_WECEIVE) {
			siw_wqe_compwete(qp, &wqe->wqe, wqe->bytes,
					 0, SIW_WC_WW_FWUSH_EWW);
		} ewse if (wx_type(wqe) != SIW_OP_WEAD &&
			   wx_type(wqe) != SIW_OP_WEAD_WESPONSE &&
			   wx_type(wqe) != SIW_OP_WWITE) {
			siw_sqe_compwete(qp, &wqe->sqe, 0, SIW_WC_WW_FWUSH_EWW);
		}
		wqe->ww_status = SIW_WW_IDWE;
	}
	wqe = &qp->wx_tagged.wqe_active;

	if (wqe->ww_status != SIW_WW_IDWE) {
		siw_wqe_put_mem(wqe, wx_type(wqe));
		wqe->ww_status = SIW_WW_IDWE;
	}
	/*
	 * Fwush the Weceive Queue
	 */
	whiwe (qp->attws.wq_size) {
		stwuct siw_wqe *wqe =
			&qp->wecvq[qp->wq_get % qp->attws.wq_size];

		if (!WEAD_ONCE(wqe->fwags))
			bweak;

		if (siw_wqe_compwete(qp, wqe, 0, 0, SIW_WC_WW_FWUSH_EWW) != 0)
			bweak;

		WWITE_ONCE(wqe->fwags, 0);
		qp->wq_get++;
	}
}

int siw_qp_add(stwuct siw_device *sdev, stwuct siw_qp *qp)
{
	int wv = xa_awwoc(&sdev->qp_xa, &qp->base_qp.qp_num, qp, xa_wimit_32b,
			  GFP_KEWNEW);

	if (!wv) {
		kwef_init(&qp->wef);
		qp->sdev = sdev;
		siw_dbg_qp(qp, "new QP\n");
	}
	wetuwn wv;
}

void siw_fwee_qp(stwuct kwef *wef)
{
	stwuct siw_qp *found, *qp = containew_of(wef, stwuct siw_qp, wef);
	stwuct siw_device *sdev = qp->sdev;
	unsigned wong fwags;

	if (qp->cep)
		siw_cep_put(qp->cep);

	found = xa_ewase(&sdev->qp_xa, qp_id(qp));
	WAWN_ON(found != qp);
	spin_wock_iwqsave(&sdev->wock, fwags);
	wist_dew(&qp->devq);
	spin_unwock_iwqwestowe(&sdev->wock, fwags);

	vfwee(qp->sendq);
	vfwee(qp->wecvq);
	vfwee(qp->iwq);
	vfwee(qp->owq);

	siw_put_tx_cpu(qp->tx_cpu);
	compwete(&qp->qp_fwee);
	atomic_dec(&sdev->num_qp);
}
