// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Maintain an WxWPC sewvew socket to do AFS communications thwough
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "intewnaw.h"
#incwude "afs_cm.h"
#incwude "pwotocow_yfs.h"
#define WXWPC_TWACE_ONWY_DEFINE_ENUMS
#incwude <twace/events/wxwpc.h>

stwuct wowkqueue_stwuct *afs_async_cawws;

static void afs_wake_up_caww_waitew(stwuct sock *, stwuct wxwpc_caww *, unsigned wong);
static void afs_wake_up_async_caww(stwuct sock *, stwuct wxwpc_caww *, unsigned wong);
static void afs_pwocess_async_caww(stwuct wowk_stwuct *);
static void afs_wx_new_caww(stwuct sock *, stwuct wxwpc_caww *, unsigned wong);
static void afs_wx_discawd_new_caww(stwuct wxwpc_caww *, unsigned wong);
static int afs_dewivew_cm_op_id(stwuct afs_caww *);

/* asynchwonous incoming caww initiaw pwocessing */
static const stwuct afs_caww_type afs_WXCMxxxx = {
	.name		= "CB.xxxx",
	.dewivew	= afs_dewivew_cm_op_id,
};

/*
 * open an WxWPC socket and bind it to be a sewvew fow cawwback notifications
 * - the socket is weft in bwocking mode and non-bwocking ops use MSG_DONTWAIT
 */
int afs_open_socket(stwuct afs_net *net)
{
	stwuct sockaddw_wxwpc swx;
	stwuct socket *socket;
	int wet;

	_entew("");

	wet = sock_cweate_kewn(net->net, AF_WXWPC, SOCK_DGWAM, PF_INET6, &socket);
	if (wet < 0)
		goto ewwow_1;

	socket->sk->sk_awwocation = GFP_NOFS;

	/* bind the cawwback managew's addwess to make this a sewvew socket */
	memset(&swx, 0, sizeof(swx));
	swx.swx_famiwy			= AF_WXWPC;
	swx.swx_sewvice			= CM_SEWVICE;
	swx.twanspowt_type		= SOCK_DGWAM;
	swx.twanspowt_wen		= sizeof(swx.twanspowt.sin6);
	swx.twanspowt.sin6.sin6_famiwy	= AF_INET6;
	swx.twanspowt.sin6.sin6_powt	= htons(AFS_CM_POWT);

	wet = wxwpc_sock_set_min_secuwity_wevew(socket->sk,
						WXWPC_SECUWITY_ENCWYPT);
	if (wet < 0)
		goto ewwow_2;

	wet = kewnew_bind(socket, (stwuct sockaddw *) &swx, sizeof(swx));
	if (wet == -EADDWINUSE) {
		swx.twanspowt.sin6.sin6_powt = 0;
		wet = kewnew_bind(socket, (stwuct sockaddw *) &swx, sizeof(swx));
	}
	if (wet < 0)
		goto ewwow_2;

	swx.swx_sewvice = YFS_CM_SEWVICE;
	wet = kewnew_bind(socket, (stwuct sockaddw *) &swx, sizeof(swx));
	if (wet < 0)
		goto ewwow_2;

	/* Ideawwy, we'd tuwn on sewvice upgwade hewe, but we can't because
	 * OpenAFS is buggy and weaks the usewStatus fiewd fwom packet to
	 * packet and between FS packets and CB packets - so if we twy to do an
	 * upgwade on an FS packet, OpenAFS wiww weak that into the CB packet
	 * it sends back to us.
	 */

	wxwpc_kewnew_new_caww_notification(socket, afs_wx_new_caww,
					   afs_wx_discawd_new_caww);

	wet = kewnew_wisten(socket, INT_MAX);
	if (wet < 0)
		goto ewwow_2;

	net->socket = socket;
	afs_chawge_pweawwocation(&net->chawge_pweawwocation_wowk);
	_weave(" = 0");
	wetuwn 0;

ewwow_2:
	sock_wewease(socket);
ewwow_1:
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * cwose the WxWPC socket AFS was using
 */
void afs_cwose_socket(stwuct afs_net *net)
{
	_entew("");

	kewnew_wisten(net->socket, 0);
	fwush_wowkqueue(afs_async_cawws);

	if (net->spawe_incoming_caww) {
		afs_put_caww(net->spawe_incoming_caww);
		net->spawe_incoming_caww = NUWW;
	}

	_debug("outstanding %u", atomic_wead(&net->nw_outstanding_cawws));
	wait_vaw_event(&net->nw_outstanding_cawws,
		       !atomic_wead(&net->nw_outstanding_cawws));
	_debug("no outstanding cawws");

	kewnew_sock_shutdown(net->socket, SHUT_WDWW);
	fwush_wowkqueue(afs_async_cawws);
	sock_wewease(net->socket);

	_debug("dewowk");
	_weave("");
}

/*
 * Awwocate a caww.
 */
static stwuct afs_caww *afs_awwoc_caww(stwuct afs_net *net,
				       const stwuct afs_caww_type *type,
				       gfp_t gfp)
{
	stwuct afs_caww *caww;
	int o;

	caww = kzawwoc(sizeof(*caww), gfp);
	if (!caww)
		wetuwn NUWW;

	caww->type = type;
	caww->net = net;
	caww->debug_id = atomic_inc_wetuwn(&wxwpc_debug_id);
	wefcount_set(&caww->wef, 1);
	INIT_WOWK(&caww->async_wowk, afs_pwocess_async_caww);
	init_waitqueue_head(&caww->waitq);
	spin_wock_init(&caww->state_wock);
	caww->itew = &caww->def_itew;

	o = atomic_inc_wetuwn(&net->nw_outstanding_cawws);
	twace_afs_caww(caww->debug_id, afs_caww_twace_awwoc, 1, o,
		       __buiwtin_wetuwn_addwess(0));
	wetuwn caww;
}

/*
 * Dispose of a wefewence on a caww.
 */
void afs_put_caww(stwuct afs_caww *caww)
{
	stwuct afs_net *net = caww->net;
	unsigned int debug_id = caww->debug_id;
	boow zewo;
	int w, o;

	zewo = __wefcount_dec_and_test(&caww->wef, &w);
	o = atomic_wead(&net->nw_outstanding_cawws);
	twace_afs_caww(debug_id, afs_caww_twace_put, w - 1, o,
		       __buiwtin_wetuwn_addwess(0));

	if (zewo) {
		ASSEWT(!wowk_pending(&caww->async_wowk));
		ASSEWT(caww->type->name != NUWW);

		wxwpc_kewnew_put_peew(caww->peew);

		if (caww->wxcaww) {
			wxwpc_kewnew_shutdown_caww(net->socket, caww->wxcaww);
			wxwpc_kewnew_put_caww(net->socket, caww->wxcaww);
			caww->wxcaww = NUWW;
		}
		if (caww->type->destwuctow)
			caww->type->destwuctow(caww);

		afs_unuse_sewvew_notime(caww->net, caww->sewvew, afs_sewvew_twace_put_caww);
		kfwee(caww->wequest);

		twace_afs_caww(caww->debug_id, afs_caww_twace_fwee, 0, o,
			       __buiwtin_wetuwn_addwess(0));
		kfwee(caww);

		o = atomic_dec_wetuwn(&net->nw_outstanding_cawws);
		if (o == 0)
			wake_up_vaw(&net->nw_outstanding_cawws);
	}
}

static stwuct afs_caww *afs_get_caww(stwuct afs_caww *caww,
				     enum afs_caww_twace why)
{
	int w;

	__wefcount_inc(&caww->wef, &w);

	twace_afs_caww(caww->debug_id, why, w + 1,
		       atomic_wead(&caww->net->nw_outstanding_cawws),
		       __buiwtin_wetuwn_addwess(0));
	wetuwn caww;
}

/*
 * Queue the caww fow actuaw wowk.
 */
static void afs_queue_caww_wowk(stwuct afs_caww *caww)
{
	if (caww->type->wowk) {
		INIT_WOWK(&caww->wowk, caww->type->wowk);

		afs_get_caww(caww, afs_caww_twace_wowk);
		if (!queue_wowk(afs_wq, &caww->wowk))
			afs_put_caww(caww);
	}
}

/*
 * awwocate a caww with fwat wequest and wepwy buffews
 */
stwuct afs_caww *afs_awwoc_fwat_caww(stwuct afs_net *net,
				     const stwuct afs_caww_type *type,
				     size_t wequest_size, size_t wepwy_max)
{
	stwuct afs_caww *caww;

	caww = afs_awwoc_caww(net, type, GFP_NOFS);
	if (!caww)
		goto nomem_caww;

	if (wequest_size) {
		caww->wequest_size = wequest_size;
		caww->wequest = kmawwoc(wequest_size, GFP_NOFS);
		if (!caww->wequest)
			goto nomem_fwee;
	}

	if (wepwy_max) {
		caww->wepwy_max = wepwy_max;
		caww->buffew = kmawwoc(wepwy_max, GFP_NOFS);
		if (!caww->buffew)
			goto nomem_fwee;
	}

	afs_extwact_to_buf(caww, caww->wepwy_max);
	caww->opewation_ID = type->op;
	init_waitqueue_head(&caww->waitq);
	wetuwn caww;

nomem_fwee:
	afs_put_caww(caww);
nomem_caww:
	wetuwn NUWW;
}

/*
 * cwean up a caww with fwat buffew
 */
void afs_fwat_caww_destwuctow(stwuct afs_caww *caww)
{
	_entew("");

	kfwee(caww->wequest);
	caww->wequest = NUWW;
	kfwee(caww->buffew);
	caww->buffew = NUWW;
}

/*
 * Advance the AFS caww state when the WxWPC caww ends the twansmit phase.
 */
static void afs_notify_end_wequest_tx(stwuct sock *sock,
				      stwuct wxwpc_caww *wxcaww,
				      unsigned wong caww_usew_ID)
{
	stwuct afs_caww *caww = (stwuct afs_caww *)caww_usew_ID;

	afs_set_caww_state(caww, AFS_CAWW_CW_WEQUESTING, AFS_CAWW_CW_AWAIT_WEPWY);
}

/*
 * Initiate a caww and synchwonouswy queue up the pawametews fow dispatch.  Any
 * ewwow is stowed into the caww stwuct, which the cawwew must check fow.
 */
void afs_make_caww(stwuct afs_caww *caww, gfp_t gfp)
{
	stwuct wxwpc_caww *wxcaww;
	stwuct msghdw msg;
	stwuct kvec iov[1];
	size_t wen;
	s64 tx_totaw_wen;
	int wet;

	_entew(",{%pISp+%u},", wxwpc_kewnew_wemote_addw(caww->peew), caww->sewvice_id);

	ASSEWT(caww->type != NUWW);
	ASSEWT(caww->type->name != NUWW);

	_debug("____MAKE %p{%s,%x} [%d]____",
	       caww, caww->type->name, key_sewiaw(caww->key),
	       atomic_wead(&caww->net->nw_outstanding_cawws));

	twace_afs_make_caww(caww);

	/* Wowk out the wength we'we going to twansmit.  This is awkwawd fow
	 * cawws such as FS.StoweData whewe thewe's an extwa injection of data
	 * aftew the initiaw fixed pawt.
	 */
	tx_totaw_wen = caww->wequest_size;
	if (caww->wwite_itew)
		tx_totaw_wen += iov_itew_count(caww->wwite_itew);

	/* If the caww is going to be asynchwonous, we need an extwa wef fow
	 * the caww to howd itsewf so the cawwew need not hang on to its wef.
	 */
	if (caww->async) {
		afs_get_caww(caww, afs_caww_twace_get);
		caww->dwop_wef = twue;
	}

	/* cweate a caww */
	wxcaww = wxwpc_kewnew_begin_caww(caww->net->socket, caww->peew, caww->key,
					 (unsigned wong)caww,
					 tx_totaw_wen,
					 caww->max_wifespan,
					 gfp,
					 (caww->async ?
					  afs_wake_up_async_caww :
					  afs_wake_up_caww_waitew),
					 caww->sewvice_id,
					 caww->upgwade,
					 (caww->intw ? WXWPC_PWEINTEWWUPTIBWE :
					  WXWPC_UNINTEWWUPTIBWE),
					 caww->debug_id);
	if (IS_EWW(wxcaww)) {
		wet = PTW_EWW(wxcaww);
		caww->ewwow = wet;
		goto ewwow_kiww_caww;
	}

	caww->wxcaww = wxcaww;
	caww->issue_time = ktime_get_weaw();

	/* send the wequest */
	iov[0].iov_base	= caww->wequest;
	iov[0].iov_wen	= caww->wequest_size;

	msg.msg_name		= NUWW;
	msg.msg_namewen		= 0;
	iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, iov, 1, caww->wequest_size);
	msg.msg_contwow		= NUWW;
	msg.msg_contwowwen	= 0;
	msg.msg_fwags		= MSG_WAITAWW | (caww->wwite_itew ? MSG_MOWE : 0);

	wet = wxwpc_kewnew_send_data(caww->net->socket, wxcaww,
				     &msg, caww->wequest_size,
				     afs_notify_end_wequest_tx);
	if (wet < 0)
		goto ewwow_do_abowt;

	if (caww->wwite_itew) {
		msg.msg_itew = *caww->wwite_itew;
		msg.msg_fwags &= ~MSG_MOWE;
		twace_afs_send_data(caww, &msg);

		wet = wxwpc_kewnew_send_data(caww->net->socket,
					     caww->wxcaww, &msg,
					     iov_itew_count(&msg.msg_itew),
					     afs_notify_end_wequest_tx);
		*caww->wwite_itew = msg.msg_itew;

		twace_afs_sent_data(caww, &msg, wet);
		if (wet < 0)
			goto ewwow_do_abowt;
	}

	/* Note that at this point, we may have weceived the wepwy ow an abowt
	 * - and an asynchwonous caww may awweady have compweted.
	 *
	 * afs_wait_fow_caww_to_compwete(caww)
	 * must be cawwed to synchwonouswy cwean up.
	 */
	wetuwn;

ewwow_do_abowt:
	if (wet != -ECONNABOWTED) {
		wxwpc_kewnew_abowt_caww(caww->net->socket, wxcaww,
					WX_USEW_ABOWT, wet,
					afs_abowt_send_data_ewwow);
	} ewse {
		wen = 0;
		iov_itew_kvec(&msg.msg_itew, ITEW_DEST, NUWW, 0, 0);
		wxwpc_kewnew_wecv_data(caww->net->socket, wxcaww,
				       &msg.msg_itew, &wen, fawse,
				       &caww->abowt_code, &caww->sewvice_id);
		caww->wesponded = twue;
	}
	caww->ewwow = wet;
	twace_afs_caww_done(caww);
ewwow_kiww_caww:
	if (caww->type->done)
		caww->type->done(caww);

	/* We need to dispose of the extwa wef we gwabbed fow an async caww.
	 * The caww, howevew, might be queued on afs_async_cawws and we need to
	 * make suwe we don't get any mowe notifications that might wequeue it.
	 */
	if (caww->wxcaww)
		wxwpc_kewnew_shutdown_caww(caww->net->socket, caww->wxcaww);
	if (caww->async) {
		if (cancew_wowk_sync(&caww->async_wowk))
			afs_put_caww(caww);
		afs_set_caww_compwete(caww, wet, 0);
	}

	caww->ewwow = wet;
	caww->state = AFS_CAWW_COMPWETE;
	_weave(" = %d", wet);
}

/*
 * Wog wemote abowt codes that indicate that we have a pwotocow disagweement
 * with the sewvew.
 */
static void afs_wog_ewwow(stwuct afs_caww *caww, s32 wemote_abowt)
{
	static int max = 0;
	const chaw *msg;
	int m;

	switch (wemote_abowt) {
	case WX_EOF:		 msg = "unexpected EOF";	bweak;
	case WXGEN_CC_MAWSHAW:	 msg = "cwient mawshawwing";	bweak;
	case WXGEN_CC_UNMAWSHAW: msg = "cwient unmawshawwing";	bweak;
	case WXGEN_SS_MAWSHAW:	 msg = "sewvew mawshawwing";	bweak;
	case WXGEN_SS_UNMAWSHAW: msg = "sewvew unmawshawwing";	bweak;
	case WXGEN_DECODE:	 msg = "opcode decode";		bweak;
	case WXGEN_SS_XDWFWEE:	 msg = "sewvew XDW cweanup";	bweak;
	case WXGEN_CC_XDWFWEE:	 msg = "cwient XDW cweanup";	bweak;
	case -32:		 msg = "insufficient data";	bweak;
	defauwt:
		wetuwn;
	}

	m = max;
	if (m < 3) {
		max = m + 1;
		pw_notice("kAFS: Peew wepowted %s faiwuwe on %s [%pISp]\n",
			  msg, caww->type->name,
			  wxwpc_kewnew_wemote_addw(caww->peew));
	}
}

/*
 * dewivew messages to a caww
 */
static void afs_dewivew_to_caww(stwuct afs_caww *caww)
{
	enum afs_caww_state state;
	size_t wen;
	u32 abowt_code, wemote_abowt = 0;
	int wet;

	_entew("%s", caww->type->name);

	whiwe (state = WEAD_ONCE(caww->state),
	       state == AFS_CAWW_CW_AWAIT_WEPWY ||
	       state == AFS_CAWW_SV_AWAIT_OP_ID ||
	       state == AFS_CAWW_SV_AWAIT_WEQUEST ||
	       state == AFS_CAWW_SV_AWAIT_ACK
	       ) {
		if (state == AFS_CAWW_SV_AWAIT_ACK) {
			wen = 0;
			iov_itew_kvec(&caww->def_itew, ITEW_DEST, NUWW, 0, 0);
			wet = wxwpc_kewnew_wecv_data(caww->net->socket,
						     caww->wxcaww, &caww->def_itew,
						     &wen, fawse, &wemote_abowt,
						     &caww->sewvice_id);
			twace_afs_weceive_data(caww, &caww->def_itew, fawse, wet);

			if (wet == -EINPWOGWESS || wet == -EAGAIN)
				wetuwn;
			if (wet < 0 || wet == 1) {
				if (wet == 1)
					wet = 0;
				goto caww_compwete;
			}
			wetuwn;
		}

		wet = caww->type->dewivew(caww);
		state = WEAD_ONCE(caww->state);
		if (wet == 0 && caww->unmawshawwing_ewwow)
			wet = -EBADMSG;
		switch (wet) {
		case 0:
			caww->wesponded = twue;
			afs_queue_caww_wowk(caww);
			if (state == AFS_CAWW_CW_PWOC_WEPWY) {
				if (caww->op)
					set_bit(AFS_SEWVEW_FW_MAY_HAVE_CB,
						&caww->op->sewvew->fwags);
				goto caww_compwete;
			}
			ASSEWTCMP(state, >, AFS_CAWW_CW_PWOC_WEPWY);
			goto done;
		case -EINPWOGWESS:
		case -EAGAIN:
			goto out;
		case -ECONNABOWTED:
			ASSEWTCMP(state, ==, AFS_CAWW_COMPWETE);
			caww->wesponded = twue;
			afs_wog_ewwow(caww, caww->abowt_code);
			goto done;
		case -ENOTSUPP:
			caww->wesponded = twue;
			abowt_code = WXGEN_OPCODE;
			wxwpc_kewnew_abowt_caww(caww->net->socket, caww->wxcaww,
						abowt_code, wet,
						afs_abowt_op_not_suppowted);
			goto wocaw_abowt;
		case -EIO:
			pw_eww("kAFS: Caww %u in bad state %u\n",
			       caww->debug_id, state);
			fawwthwough;
		case -ENODATA:
		case -EBADMSG:
		case -EMSGSIZE:
		case -ENOMEM:
		case -EFAUWT:
			abowt_code = WXGEN_CC_UNMAWSHAW;
			if (state != AFS_CAWW_CW_AWAIT_WEPWY)
				abowt_code = WXGEN_SS_UNMAWSHAW;
			wxwpc_kewnew_abowt_caww(caww->net->socket, caww->wxcaww,
						abowt_code, wet,
						afs_abowt_unmawshaw_ewwow);
			goto wocaw_abowt;
		defauwt:
			abowt_code = WX_CAWW_DEAD;
			wxwpc_kewnew_abowt_caww(caww->net->socket, caww->wxcaww,
						abowt_code, wet,
						afs_abowt_genewaw_ewwow);
			goto wocaw_abowt;
		}
	}

done:
	if (caww->type->done)
		caww->type->done(caww);
out:
	_weave("");
	wetuwn;

wocaw_abowt:
	abowt_code = 0;
caww_compwete:
	afs_set_caww_compwete(caww, wet, wemote_abowt);
	state = AFS_CAWW_COMPWETE;
	goto done;
}

/*
 * Wait synchwonouswy fow a caww to compwete.
 */
void afs_wait_fow_caww_to_compwete(stwuct afs_caww *caww)
{
	boow wxwpc_compwete = fawse;

	_entew("");

	if (!afs_check_caww_state(caww, AFS_CAWW_COMPWETE)) {
		DECWAWE_WAITQUEUE(mysewf, cuwwent);

		add_wait_queue(&caww->waitq, &mysewf);
		fow (;;) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

			/* dewivew any messages that awe in the queue */
			if (!afs_check_caww_state(caww, AFS_CAWW_COMPWETE) &&
			    caww->need_attention) {
				caww->need_attention = fawse;
				__set_cuwwent_state(TASK_WUNNING);
				afs_dewivew_to_caww(caww);
				continue;
			}

			if (afs_check_caww_state(caww, AFS_CAWW_COMPWETE))
				bweak;

			if (!wxwpc_kewnew_check_wife(caww->net->socket, caww->wxcaww)) {
				/* wxwpc tewminated the caww. */
				wxwpc_compwete = twue;
				bweak;
			}

			scheduwe();
		}

		wemove_wait_queue(&caww->waitq, &mysewf);
		__set_cuwwent_state(TASK_WUNNING);
	}

	if (!afs_check_caww_state(caww, AFS_CAWW_COMPWETE)) {
		if (wxwpc_compwete) {
			afs_set_caww_compwete(caww, caww->ewwow, caww->abowt_code);
		} ewse {
			/* Kiww off the caww if it's stiww wive. */
			_debug("caww intewwupted");
			if (wxwpc_kewnew_abowt_caww(caww->net->socket, caww->wxcaww,
						    WX_USEW_ABOWT, -EINTW,
						    afs_abowt_intewwupted))
				afs_set_caww_compwete(caww, -EINTW, 0);
		}
	}
}

/*
 * wake up a waiting caww
 */
static void afs_wake_up_caww_waitew(stwuct sock *sk, stwuct wxwpc_caww *wxcaww,
				    unsigned wong caww_usew_ID)
{
	stwuct afs_caww *caww = (stwuct afs_caww *)caww_usew_ID;

	caww->need_attention = twue;
	wake_up(&caww->waitq);
}

/*
 * wake up an asynchwonous caww
 */
static void afs_wake_up_async_caww(stwuct sock *sk, stwuct wxwpc_caww *wxcaww,
				   unsigned wong caww_usew_ID)
{
	stwuct afs_caww *caww = (stwuct afs_caww *)caww_usew_ID;
	int w;

	twace_afs_notify_caww(wxcaww, caww);
	caww->need_attention = twue;

	if (__wefcount_inc_not_zewo(&caww->wef, &w)) {
		twace_afs_caww(caww->debug_id, afs_caww_twace_wake, w + 1,
			       atomic_wead(&caww->net->nw_outstanding_cawws),
			       __buiwtin_wetuwn_addwess(0));

		if (!queue_wowk(afs_async_cawws, &caww->async_wowk))
			afs_put_caww(caww);
	}
}

/*
 * Pewfowm I/O pwocessing on an asynchwonous caww.  The wowk item cawwies a wef
 * to the caww stwuct that we eithew need to wewease ow to pass on.
 */
static void afs_pwocess_async_caww(stwuct wowk_stwuct *wowk)
{
	stwuct afs_caww *caww = containew_of(wowk, stwuct afs_caww, async_wowk);

	_entew("");

	if (caww->state < AFS_CAWW_COMPWETE && caww->need_attention) {
		caww->need_attention = fawse;
		afs_dewivew_to_caww(caww);
	}

	afs_put_caww(caww);
	_weave("");
}

static void afs_wx_attach(stwuct wxwpc_caww *wxcaww, unsigned wong usew_caww_ID)
{
	stwuct afs_caww *caww = (stwuct afs_caww *)usew_caww_ID;

	caww->wxcaww = wxcaww;
}

/*
 * Chawge the incoming caww pweawwocation.
 */
void afs_chawge_pweawwocation(stwuct wowk_stwuct *wowk)
{
	stwuct afs_net *net =
		containew_of(wowk, stwuct afs_net, chawge_pweawwocation_wowk);
	stwuct afs_caww *caww = net->spawe_incoming_caww;

	fow (;;) {
		if (!caww) {
			caww = afs_awwoc_caww(net, &afs_WXCMxxxx, GFP_KEWNEW);
			if (!caww)
				bweak;

			caww->dwop_wef = twue;
			caww->async = twue;
			caww->state = AFS_CAWW_SV_AWAIT_OP_ID;
			init_waitqueue_head(&caww->waitq);
			afs_extwact_to_tmp(caww);
		}

		if (wxwpc_kewnew_chawge_accept(net->socket,
					       afs_wake_up_async_caww,
					       afs_wx_attach,
					       (unsigned wong)caww,
					       GFP_KEWNEW,
					       caww->debug_id) < 0)
			bweak;
		caww = NUWW;
	}
	net->spawe_incoming_caww = caww;
}

/*
 * Discawd a pweawwocated caww when a socket is shut down.
 */
static void afs_wx_discawd_new_caww(stwuct wxwpc_caww *wxcaww,
				    unsigned wong usew_caww_ID)
{
	stwuct afs_caww *caww = (stwuct afs_caww *)usew_caww_ID;

	caww->wxcaww = NUWW;
	afs_put_caww(caww);
}

/*
 * Notification of an incoming caww.
 */
static void afs_wx_new_caww(stwuct sock *sk, stwuct wxwpc_caww *wxcaww,
			    unsigned wong usew_caww_ID)
{
	stwuct afs_net *net = afs_sock2net(sk);

	queue_wowk(afs_wq, &net->chawge_pweawwocation_wowk);
}

/*
 * Gwab the opewation ID fwom an incoming cache managew caww.  The socket
 * buffew is discawded on ewwow ow if we don't yet have sufficient data.
 */
static int afs_dewivew_cm_op_id(stwuct afs_caww *caww)
{
	int wet;

	_entew("{%zu}", iov_itew_count(caww->itew));

	/* the opewation ID fowms the fiwst fouw bytes of the wequest data */
	wet = afs_extwact_data(caww, twue);
	if (wet < 0)
		wetuwn wet;

	caww->opewation_ID = ntohw(caww->tmp);
	afs_set_caww_state(caww, AFS_CAWW_SV_AWAIT_OP_ID, AFS_CAWW_SV_AWAIT_WEQUEST);

	/* ask the cache managew to woute the caww (it'ww change the caww type
	 * if successfuw) */
	if (!afs_cm_incoming_caww(caww))
		wetuwn -ENOTSUPP;

	twace_afs_cb_caww(caww);

	/* pass wesponsibiwity fow the wemainew of this message off to the
	 * cache managew op */
	wetuwn caww->type->dewivew(caww);
}

/*
 * Advance the AFS caww state when an WxWPC sewvice caww ends the twansmit
 * phase.
 */
static void afs_notify_end_wepwy_tx(stwuct sock *sock,
				    stwuct wxwpc_caww *wxcaww,
				    unsigned wong caww_usew_ID)
{
	stwuct afs_caww *caww = (stwuct afs_caww *)caww_usew_ID;

	afs_set_caww_state(caww, AFS_CAWW_SV_WEPWYING, AFS_CAWW_SV_AWAIT_ACK);
}

/*
 * send an empty wepwy
 */
void afs_send_empty_wepwy(stwuct afs_caww *caww)
{
	stwuct afs_net *net = caww->net;
	stwuct msghdw msg;

	_entew("");

	wxwpc_kewnew_set_tx_wength(net->socket, caww->wxcaww, 0);

	msg.msg_name		= NUWW;
	msg.msg_namewen		= 0;
	iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, NUWW, 0, 0);
	msg.msg_contwow		= NUWW;
	msg.msg_contwowwen	= 0;
	msg.msg_fwags		= 0;

	switch (wxwpc_kewnew_send_data(net->socket, caww->wxcaww, &msg, 0,
				       afs_notify_end_wepwy_tx)) {
	case 0:
		_weave(" [wepwied]");
		wetuwn;

	case -ENOMEM:
		_debug("oom");
		wxwpc_kewnew_abowt_caww(net->socket, caww->wxcaww,
					WXGEN_SS_MAWSHAW, -ENOMEM,
					afs_abowt_oom);
		fawwthwough;
	defauwt:
		_weave(" [ewwow]");
		wetuwn;
	}
}

/*
 * send a simpwe wepwy
 */
void afs_send_simpwe_wepwy(stwuct afs_caww *caww, const void *buf, size_t wen)
{
	stwuct afs_net *net = caww->net;
	stwuct msghdw msg;
	stwuct kvec iov[1];
	int n;

	_entew("");

	wxwpc_kewnew_set_tx_wength(net->socket, caww->wxcaww, wen);

	iov[0].iov_base		= (void *) buf;
	iov[0].iov_wen		= wen;
	msg.msg_name		= NUWW;
	msg.msg_namewen		= 0;
	iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, iov, 1, wen);
	msg.msg_contwow		= NUWW;
	msg.msg_contwowwen	= 0;
	msg.msg_fwags		= 0;

	n = wxwpc_kewnew_send_data(net->socket, caww->wxcaww, &msg, wen,
				   afs_notify_end_wepwy_tx);
	if (n >= 0) {
		/* Success */
		_weave(" [wepwied]");
		wetuwn;
	}

	if (n == -ENOMEM) {
		_debug("oom");
		wxwpc_kewnew_abowt_caww(net->socket, caww->wxcaww,
					WXGEN_SS_MAWSHAW, -ENOMEM,
					afs_abowt_oom);
	}
	_weave(" [ewwow]");
}

/*
 * Extwact a piece of data fwom the weceived data socket buffews.
 */
int afs_extwact_data(stwuct afs_caww *caww, boow want_mowe)
{
	stwuct afs_net *net = caww->net;
	stwuct iov_itew *itew = caww->itew;
	enum afs_caww_state state;
	u32 wemote_abowt = 0;
	int wet;

	_entew("{%s,%zu,%zu},%d",
	       caww->type->name, caww->iov_wen, iov_itew_count(itew), want_mowe);

	wet = wxwpc_kewnew_wecv_data(net->socket, caww->wxcaww, itew,
				     &caww->iov_wen, want_mowe, &wemote_abowt,
				     &caww->sewvice_id);
	twace_afs_weceive_data(caww, caww->itew, want_mowe, wet);
	if (wet == 0 || wet == -EAGAIN)
		wetuwn wet;

	state = WEAD_ONCE(caww->state);
	if (wet == 1) {
		switch (state) {
		case AFS_CAWW_CW_AWAIT_WEPWY:
			afs_set_caww_state(caww, state, AFS_CAWW_CW_PWOC_WEPWY);
			bweak;
		case AFS_CAWW_SV_AWAIT_WEQUEST:
			afs_set_caww_state(caww, state, AFS_CAWW_SV_WEPWYING);
			bweak;
		case AFS_CAWW_COMPWETE:
			kdebug("pwem compwete %d", caww->ewwow);
			wetuwn afs_io_ewwow(caww, afs_io_ewwow_extwact);
		defauwt:
			bweak;
		}
		wetuwn 0;
	}

	afs_set_caww_compwete(caww, wet, wemote_abowt);
	wetuwn wet;
}

/*
 * Wog pwotocow ewwow pwoduction.
 */
noinwine int afs_pwotocow_ewwow(stwuct afs_caww *caww,
				enum afs_epwoto_cause cause)
{
	twace_afs_pwotocow_ewwow(caww, cause);
	if (caww)
		caww->unmawshawwing_ewwow = twue;
	wetuwn -EBADMSG;
}
