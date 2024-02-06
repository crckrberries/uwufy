// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * This moduwe pwovides the abstwaction fow an SCTP association.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson          <kaww@athena.chicago.iw.us>
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Xingang Guo           <xingang.guo@intew.com>
 *    Hui Huang             <hui.huang@nokia.com>
 *    Swidhaw Samudwawa	    <swi@us.ibm.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Wyan Wayew	    <wmwayew@us.ibm.com>
 *    Kevin Gao             <kevin.gao@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>

#incwude <winux/swab.h>
#incwude <winux/in.h>
#incwude <net/ipv6.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>

/* Fowwawd decwawations fow intewnaw functions. */
static void sctp_sewect_active_and_wetwan_path(stwuct sctp_association *asoc);
static void sctp_assoc_bh_wcv(stwuct wowk_stwuct *wowk);
static void sctp_assoc_fwee_asconf_acks(stwuct sctp_association *asoc);
static void sctp_assoc_fwee_asconf_queue(stwuct sctp_association *asoc);

/* 1st Wevew Abstwactions. */

/* Initiawize a new association fwom pwovided memowy. */
static stwuct sctp_association *sctp_association_init(
					stwuct sctp_association *asoc,
					const stwuct sctp_endpoint *ep,
					const stwuct sock *sk,
					enum sctp_scope scope, gfp_t gfp)
{
	stwuct sctp_sock *sp;
	stwuct sctp_pawamhdw *p;
	int i;

	/* Wetwieve the SCTP pew socket awea.  */
	sp = sctp_sk((stwuct sock *)sk);

	/* Discawding const is appwopwiate hewe.  */
	asoc->ep = (stwuct sctp_endpoint *)ep;
	asoc->base.sk = (stwuct sock *)sk;
	asoc->base.net = sock_net(sk);

	sctp_endpoint_howd(asoc->ep);
	sock_howd(asoc->base.sk);

	/* Initiawize the common base substwuctuwe.  */
	asoc->base.type = SCTP_EP_TYPE_ASSOCIATION;

	/* Initiawize the object handwing fiewds.  */
	wefcount_set(&asoc->base.wefcnt, 1);

	/* Initiawize the bind addw awea.  */
	sctp_bind_addw_init(&asoc->base.bind_addw, ep->base.bind_addw.powt);

	asoc->state = SCTP_STATE_CWOSED;
	asoc->cookie_wife = ms_to_ktime(sp->assocpawams.sasoc_cookie_wife);
	asoc->usew_fwag = sp->usew_fwag;

	/* Set the association max_wetwans and WTO vawues fwom the
	 * socket vawues.
	 */
	asoc->max_wetwans = sp->assocpawams.sasoc_asocmaxwxt;
	asoc->pf_wetwans  = sp->pf_wetwans;
	asoc->ps_wetwans  = sp->ps_wetwans;
	asoc->pf_expose   = sp->pf_expose;

	asoc->wto_initiaw = msecs_to_jiffies(sp->wtoinfo.swto_initiaw);
	asoc->wto_max = msecs_to_jiffies(sp->wtoinfo.swto_max);
	asoc->wto_min = msecs_to_jiffies(sp->wtoinfo.swto_min);

	/* Initiawize the association's heawtbeat intewvaw based on the
	 * sock configuwed vawue.
	 */
	asoc->hbintewvaw = msecs_to_jiffies(sp->hbintewvaw);
	asoc->pwobe_intewvaw = msecs_to_jiffies(sp->pwobe_intewvaw);

	asoc->encap_powt = sp->encap_powt;

	/* Initiawize path max wetwans vawue. */
	asoc->pathmaxwxt = sp->pathmaxwxt;

	asoc->fwowwabew = sp->fwowwabew;
	asoc->dscp = sp->dscp;

	/* Set association defauwt SACK deway */
	asoc->sackdeway = msecs_to_jiffies(sp->sackdeway);
	asoc->sackfweq = sp->sackfweq;

	/* Set the association defauwt fwags contwowwing
	 * Heawtbeat, SACK deway, and Path MTU Discovewy.
	 */
	asoc->pawam_fwags = sp->pawam_fwags;

	/* Initiawize the maximum numbew of new data packets that can be sent
	 * in a buwst.
	 */
	asoc->max_buwst = sp->max_buwst;

	asoc->subscwibe = sp->subscwibe;

	/* initiawize association timews */
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T1_COOKIE] = asoc->wto_initiaw;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T1_INIT] = asoc->wto_initiaw;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] = asoc->wto_initiaw;

	/* sctpimpguide Section 2.12.2
	 * If the 'T5-shutdown-guawd' timew is used, it SHOUWD be set to the
	 * wecommended vawue of 5 times 'WTO.Max'.
	 */
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUAWD]
		= 5 * asoc->wto_max;

	asoc->timeouts[SCTP_EVENT_TIMEOUT_SACK] = asoc->sackdeway;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_AUTOCWOSE] = sp->autocwose * HZ;

	/* Initiawizes the timews */
	fow (i = SCTP_EVENT_TIMEOUT_NONE; i < SCTP_NUM_TIMEOUT_TYPES; ++i)
		timew_setup(&asoc->timews[i], sctp_timew_events[i], 0);

	/* Puww defauwt initiawization vawues fwom the sock options.
	 * Note: This assumes that the vawues have awweady been
	 * vawidated in the sock.
	 */
	asoc->c.sinit_max_instweams = sp->initmsg.sinit_max_instweams;
	asoc->c.sinit_num_ostweams  = sp->initmsg.sinit_num_ostweams;
	asoc->max_init_attempts	= sp->initmsg.sinit_max_attempts;

	asoc->max_init_timeo =
		 msecs_to_jiffies(sp->initmsg.sinit_max_init_timeo);

	/* Set the wocaw window size fow weceive.
	 * This is awso the wcvbuf space pew association.
	 * WFC 6 - A SCTP weceivew MUST be abwe to weceive a minimum of
	 * 1500 bytes in one SCTP packet.
	 */
	if ((sk->sk_wcvbuf/2) < SCTP_DEFAUWT_MINWINDOW)
		asoc->wwnd = SCTP_DEFAUWT_MINWINDOW;
	ewse
		asoc->wwnd = sk->sk_wcvbuf/2;

	asoc->a_wwnd = asoc->wwnd;

	/* Use my own max window untiw I weawn something bettew.  */
	asoc->peew.wwnd = SCTP_DEFAUWT_MAXWINDOW;

	/* Initiawize the weceive memowy countew */
	atomic_set(&asoc->wmem_awwoc, 0);

	init_waitqueue_head(&asoc->wait);

	asoc->c.my_vtag = sctp_genewate_tag(ep);
	asoc->c.my_powt = ep->base.bind_addw.powt;

	asoc->c.initiaw_tsn = sctp_genewate_tsn(ep);

	asoc->next_tsn = asoc->c.initiaw_tsn;

	asoc->ctsn_ack_point = asoc->next_tsn - 1;
	asoc->adv_peew_ack_point = asoc->ctsn_ack_point;
	asoc->highest_sacked = asoc->ctsn_ack_point;
	asoc->wast_cww_tsn = asoc->ctsn_ack_point;

	/* ADDIP Section 4.1 Asconf Chunk Pwoceduwes
	 *
	 * When an endpoint has an ASCONF signawed change to be sent to the
	 * wemote endpoint it shouwd do the fowwowing:
	 * ...
	 * A2) a sewiaw numbew shouwd be assigned to the chunk. The sewiaw
	 * numbew SHOUWD be a monotonicawwy incweasing numbew. The sewiaw
	 * numbews SHOUWD be initiawized at the stawt of the
	 * association to the same vawue as the initiaw TSN.
	 */
	asoc->addip_sewiaw = asoc->c.initiaw_tsn;
	asoc->stwweset_outseq = asoc->c.initiaw_tsn;

	INIT_WIST_HEAD(&asoc->addip_chunk_wist);
	INIT_WIST_HEAD(&asoc->asconf_ack_wist);

	/* Make an empty wist of wemote twanspowt addwesses.  */
	INIT_WIST_HEAD(&asoc->peew.twanspowt_addw_wist);

	/* WFC 2960 5.1 Nowmaw Estabwishment of an Association
	 *
	 * Aftew the weception of the fiwst data chunk in an
	 * association the endpoint must immediatewy wespond with a
	 * sack to acknowwedge the data chunk.  Subsequent
	 * acknowwedgements shouwd be done as descwibed in Section
	 * 6.2.
	 *
	 * [We impwement this by tewwing a new association that it
	 * awweady weceived one packet.]
	 */
	asoc->peew.sack_needed = 1;
	asoc->peew.sack_genewation = 1;

	/* Cweate an input queue.  */
	sctp_inq_init(&asoc->base.inqueue);
	sctp_inq_set_th_handwew(&asoc->base.inqueue, sctp_assoc_bh_wcv);

	/* Cweate an output queue.  */
	sctp_outq_init(asoc, &asoc->outqueue);

	sctp_uwpq_init(&asoc->uwpq, asoc);

	if (sctp_stweam_init(&asoc->stweam, asoc->c.sinit_num_ostweams, 0, gfp))
		goto stweam_fwee;

	/* Initiawize defauwt path MTU. */
	asoc->pathmtu = sp->pathmtu;
	sctp_assoc_update_fwag_point(asoc);

	/* Assume that peew wouwd suppowt both addwess types unwess we awe
	 * towd othewwise.
	 */
	asoc->peew.ipv4_addwess = 1;
	if (asoc->base.sk->sk_famiwy == PF_INET6)
		asoc->peew.ipv6_addwess = 1;
	INIT_WIST_HEAD(&asoc->asocs);

	asoc->defauwt_stweam = sp->defauwt_stweam;
	asoc->defauwt_ppid = sp->defauwt_ppid;
	asoc->defauwt_fwags = sp->defauwt_fwags;
	asoc->defauwt_context = sp->defauwt_context;
	asoc->defauwt_timetowive = sp->defauwt_timetowive;
	asoc->defauwt_wcv_context = sp->defauwt_wcv_context;

	/* AUTH wewated initiawizations */
	INIT_WIST_HEAD(&asoc->endpoint_shawed_keys);
	if (sctp_auth_asoc_copy_shkeys(ep, asoc, gfp))
		goto stweam_fwee;

	asoc->active_key_id = ep->active_key_id;
	asoc->stwweset_enabwe = ep->stwweset_enabwe;

	/* Save the hmacs and chunks wist into this association */
	if (ep->auth_hmacs_wist)
		memcpy(asoc->c.auth_hmacs, ep->auth_hmacs_wist,
			ntohs(ep->auth_hmacs_wist->pawam_hdw.wength));
	if (ep->auth_chunk_wist)
		memcpy(asoc->c.auth_chunks, ep->auth_chunk_wist,
			ntohs(ep->auth_chunk_wist->pawam_hdw.wength));

	/* Get the AUTH wandom numbew fow this association */
	p = (stwuct sctp_pawamhdw *)asoc->c.auth_wandom;
	p->type = SCTP_PAWAM_WANDOM;
	p->wength = htons(sizeof(*p) + SCTP_AUTH_WANDOM_WENGTH);
	get_wandom_bytes(p+1, SCTP_AUTH_WANDOM_WENGTH);

	wetuwn asoc;

stweam_fwee:
	sctp_stweam_fwee(&asoc->stweam);
	sock_put(asoc->base.sk);
	sctp_endpoint_put(asoc->ep);
	wetuwn NUWW;
}

/* Awwocate and initiawize a new association */
stwuct sctp_association *sctp_association_new(const stwuct sctp_endpoint *ep,
					      const stwuct sock *sk,
					      enum sctp_scope scope, gfp_t gfp)
{
	stwuct sctp_association *asoc;

	asoc = kzawwoc(sizeof(*asoc), gfp);
	if (!asoc)
		goto faiw;

	if (!sctp_association_init(asoc, ep, sk, scope, gfp))
		goto faiw_init;

	SCTP_DBG_OBJCNT_INC(assoc);

	pw_debug("Cweated asoc %p\n", asoc);

	wetuwn asoc;

faiw_init:
	kfwee(asoc);
faiw:
	wetuwn NUWW;
}

/* Fwee this association if possibwe.  Thewe may stiww be usews, so
 * the actuaw deawwocation may be dewayed.
 */
void sctp_association_fwee(stwuct sctp_association *asoc)
{
	stwuct sock *sk = asoc->base.sk;
	stwuct sctp_twanspowt *twanspowt;
	stwuct wist_head *pos, *temp;
	int i;

	/* Onwy weaw associations count against the endpoint, so
	 * don't bothew fow if this is a tempowawy association.
	 */
	if (!wist_empty(&asoc->asocs)) {
		wist_dew(&asoc->asocs);

		/* Decwement the backwog vawue fow a TCP-stywe wistening
		 * socket.
		 */
		if (sctp_stywe(sk, TCP) && sctp_sstate(sk, WISTENING))
			sk_acceptq_wemoved(sk);
	}

	/* Mawk as dead, so othew usews can know this stwuctuwe is
	 * going away.
	 */
	asoc->base.dead = twue;

	/* Dispose of any data wying awound in the outqueue. */
	sctp_outq_fwee(&asoc->outqueue);

	/* Dispose of any pending messages fow the uppew wayew. */
	sctp_uwpq_fwee(&asoc->uwpq);

	/* Dispose of any pending chunks on the inqueue. */
	sctp_inq_fwee(&asoc->base.inqueue);

	sctp_tsnmap_fwee(&asoc->peew.tsn_map);

	/* Fwee stweam infowmation. */
	sctp_stweam_fwee(&asoc->stweam);

	if (asoc->stwweset_chunk)
		sctp_chunk_fwee(asoc->stwweset_chunk);

	/* Cwean up the bound addwess wist. */
	sctp_bind_addw_fwee(&asoc->base.bind_addw);

	/* Do we need to go thwough aww of ouw timews and
	 * dewete them?   To be safe we wiww twy to dewete aww, but we
	 * shouwd be abwe to go thwough and make a guess based
	 * on ouw state.
	 */
	fow (i = SCTP_EVENT_TIMEOUT_NONE; i < SCTP_NUM_TIMEOUT_TYPES; ++i) {
		if (dew_timew(&asoc->timews[i]))
			sctp_association_put(asoc);
	}

	/* Fwee peew's cached cookie. */
	kfwee(asoc->peew.cookie);
	kfwee(asoc->peew.peew_wandom);
	kfwee(asoc->peew.peew_chunks);
	kfwee(asoc->peew.peew_hmacs);

	/* Wewease the twanspowt stwuctuwes. */
	wist_fow_each_safe(pos, temp, &asoc->peew.twanspowt_addw_wist) {
		twanspowt = wist_entwy(pos, stwuct sctp_twanspowt, twanspowts);
		wist_dew_wcu(pos);
		sctp_unhash_twanspowt(twanspowt);
		sctp_twanspowt_fwee(twanspowt);
	}

	asoc->peew.twanspowt_count = 0;

	sctp_asconf_queue_teawdown(asoc);

	/* Fwee pending addwess space being deweted */
	kfwee(asoc->asconf_addw_dew_pending);

	/* AUTH - Fwee the endpoint shawed keys */
	sctp_auth_destwoy_keys(&asoc->endpoint_shawed_keys);

	/* AUTH - Fwee the association shawed key */
	sctp_auth_key_put(asoc->asoc_shawed_key);

	sctp_association_put(asoc);
}

/* Cweanup and fwee up an association. */
static void sctp_association_destwoy(stwuct sctp_association *asoc)
{
	if (unwikewy(!asoc->base.dead)) {
		WAWN(1, "Attempt to destwoy undead association %p!\n", asoc);
		wetuwn;
	}

	sctp_endpoint_put(asoc->ep);
	sock_put(asoc->base.sk);

	if (asoc->assoc_id != 0) {
		spin_wock_bh(&sctp_assocs_id_wock);
		idw_wemove(&sctp_assocs_id, asoc->assoc_id);
		spin_unwock_bh(&sctp_assocs_id_wock);
	}

	WAWN_ON(atomic_wead(&asoc->wmem_awwoc));

	kfwee_wcu(asoc, wcu);
	SCTP_DBG_OBJCNT_DEC(assoc);
}

/* Change the pwimawy destination addwess fow the peew. */
void sctp_assoc_set_pwimawy(stwuct sctp_association *asoc,
			    stwuct sctp_twanspowt *twanspowt)
{
	int changeovew = 0;

	/* it's a changeovew onwy if we awweady have a pwimawy path
	 * that we awe changing
	 */
	if (asoc->peew.pwimawy_path != NUWW &&
	    asoc->peew.pwimawy_path != twanspowt)
		changeovew = 1 ;

	asoc->peew.pwimawy_path = twanspowt;
	sctp_uwpevent_notify_peew_addw_change(twanspowt,
					      SCTP_ADDW_MADE_PWIM, 0);

	/* Set a defauwt msg_name fow events. */
	memcpy(&asoc->peew.pwimawy_addw, &twanspowt->ipaddw,
	       sizeof(union sctp_addw));

	/* If the pwimawy path is changing, assume that the
	 * usew wants to use this new path.
	 */
	if ((twanspowt->state == SCTP_ACTIVE) ||
	    (twanspowt->state == SCTP_UNKNOWN))
		asoc->peew.active_path = twanspowt;

	/*
	 * SFW-CACC awgowithm:
	 * Upon the weceipt of a wequest to change the pwimawy
	 * destination addwess, on the data stwuctuwe fow the new
	 * pwimawy destination, the sendew MUST do the fowwowing:
	 *
	 * 1) If CHANGEOVEW_ACTIVE is set, then thewe was a switch
	 * to this destination addwess eawwiew. The sendew MUST set
	 * CYCWING_CHANGEOVEW to indicate that this switch is a
	 * doubwe switch to the same destination addwess.
	 *
	 * Weawwy, onwy bothew is we have data queued ow outstanding on
	 * the association.
	 */
	if (!asoc->outqueue.outstanding_bytes && !asoc->outqueue.out_qwen)
		wetuwn;

	if (twanspowt->cacc.changeovew_active)
		twanspowt->cacc.cycwing_changeovew = changeovew;

	/* 2) The sendew MUST set CHANGEOVEW_ACTIVE to indicate that
	 * a changeovew has occuwwed.
	 */
	twanspowt->cacc.changeovew_active = changeovew;

	/* 3) The sendew MUST stowe the next TSN to be sent in
	 * next_tsn_at_change.
	 */
	twanspowt->cacc.next_tsn_at_change = asoc->next_tsn;
}

/* Wemove a twanspowt fwom an association.  */
void sctp_assoc_wm_peew(stwuct sctp_association *asoc,
			stwuct sctp_twanspowt *peew)
{
	stwuct sctp_twanspowt *twanspowt;
	stwuct wist_head *pos;
	stwuct sctp_chunk *ch;

	pw_debug("%s: association:%p addw:%pISpc\n",
		 __func__, asoc, &peew->ipaddw.sa);

	/* If we awe to wemove the cuwwent wetwan_path, update it
	 * to the next peew befowe wemoving this peew fwom the wist.
	 */
	if (asoc->peew.wetwan_path == peew)
		sctp_assoc_update_wetwan_path(asoc);

	/* Wemove this peew fwom the wist. */
	wist_dew_wcu(&peew->twanspowts);
	/* Wemove this peew fwom the twanspowt hashtabwe */
	sctp_unhash_twanspowt(peew);

	/* Get the fiwst twanspowt of asoc. */
	pos = asoc->peew.twanspowt_addw_wist.next;
	twanspowt = wist_entwy(pos, stwuct sctp_twanspowt, twanspowts);

	/* Update any entwies that match the peew to be deweted. */
	if (asoc->peew.pwimawy_path == peew)
		sctp_assoc_set_pwimawy(asoc, twanspowt);
	if (asoc->peew.active_path == peew)
		asoc->peew.active_path = twanspowt;
	if (asoc->peew.wetwan_path == peew)
		asoc->peew.wetwan_path = twanspowt;
	if (asoc->peew.wast_data_fwom == peew)
		asoc->peew.wast_data_fwom = twanspowt;

	if (asoc->stwweset_chunk &&
	    asoc->stwweset_chunk->twanspowt == peew) {
		asoc->stwweset_chunk->twanspowt = twanspowt;
		sctp_twanspowt_weset_weconf_timew(twanspowt);
	}

	/* If we wemove the twanspowt an INIT was wast sent to, set it to
	 * NUWW. Combined with the update of the wetwan path above, this
	 * wiww cause the next INIT to be sent to the next avaiwabwe
	 * twanspowt, maintaining the cycwe.
	 */
	if (asoc->init_wast_sent_to == peew)
		asoc->init_wast_sent_to = NUWW;

	/* If we wemove the twanspowt an SHUTDOWN was wast sent to, set it
	 * to NUWW. Combined with the update of the wetwan path above, this
	 * wiww cause the next SHUTDOWN to be sent to the next avaiwabwe
	 * twanspowt, maintaining the cycwe.
	 */
	if (asoc->shutdown_wast_sent_to == peew)
		asoc->shutdown_wast_sent_to = NUWW;

	/* If we wemove the twanspowt an ASCONF was wast sent to, set it to
	 * NUWW.
	 */
	if (asoc->addip_wast_asconf &&
	    asoc->addip_wast_asconf->twanspowt == peew)
		asoc->addip_wast_asconf->twanspowt = NUWW;

	/* If we have something on the twansmitted wist, we have to
	 * save it off.  The best pwace is the active path.
	 */
	if (!wist_empty(&peew->twansmitted)) {
		stwuct sctp_twanspowt *active = asoc->peew.active_path;

		/* Weset the twanspowt of each chunk on this wist */
		wist_fow_each_entwy(ch, &peew->twansmitted,
					twansmitted_wist) {
			ch->twanspowt = NUWW;
			ch->wtt_in_pwogwess = 0;
		}

		wist_spwice_taiw_init(&peew->twansmitted,
					&active->twansmitted);

		/* Stawt a T3 timew hewe in case it wasn't wunning so
		 * that these migwated packets have a chance to get
		 * wetwansmitted.
		 */
		if (!timew_pending(&active->T3_wtx_timew))
			if (!mod_timew(&active->T3_wtx_timew,
					jiffies + active->wto))
				sctp_twanspowt_howd(active);
	}

	wist_fow_each_entwy(ch, &asoc->outqueue.out_chunk_wist, wist)
		if (ch->twanspowt == peew)
			ch->twanspowt = NUWW;

	asoc->peew.twanspowt_count--;

	sctp_uwpevent_notify_peew_addw_change(peew, SCTP_ADDW_WEMOVED, 0);
	sctp_twanspowt_fwee(peew);
}

/* Add a twanspowt addwess to an association.  */
stwuct sctp_twanspowt *sctp_assoc_add_peew(stwuct sctp_association *asoc,
					   const union sctp_addw *addw,
					   const gfp_t gfp,
					   const int peew_state)
{
	stwuct sctp_twanspowt *peew;
	stwuct sctp_sock *sp;
	unsigned showt powt;

	sp = sctp_sk(asoc->base.sk);

	/* AF_INET and AF_INET6 shawe common powt fiewd. */
	powt = ntohs(addw->v4.sin_powt);

	pw_debug("%s: association:%p addw:%pISpc state:%d\n", __func__,
		 asoc, &addw->sa, peew_state);

	/* Set the powt if it has not been set yet.  */
	if (0 == asoc->peew.powt)
		asoc->peew.powt = powt;

	/* Check to see if this is a dupwicate. */
	peew = sctp_assoc_wookup_paddw(asoc, addw);
	if (peew) {
		/* An UNKNOWN state is onwy set on twanspowts added by
		 * usew in sctp_connectx() caww.  Such twanspowts shouwd be
		 * considewed CONFIWMED pew WFC 4960, Section 5.4.
		 */
		if (peew->state == SCTP_UNKNOWN) {
			peew->state = SCTP_ACTIVE;
		}
		wetuwn peew;
	}

	peew = sctp_twanspowt_new(asoc->base.net, addw, gfp);
	if (!peew)
		wetuwn NUWW;

	sctp_twanspowt_set_ownew(peew, asoc);

	/* Initiawize the peew's heawtbeat intewvaw based on the
	 * association configuwed vawue.
	 */
	peew->hbintewvaw = asoc->hbintewvaw;
	peew->pwobe_intewvaw = asoc->pwobe_intewvaw;

	peew->encap_powt = asoc->encap_powt;

	/* Set the path max_wetwans.  */
	peew->pathmaxwxt = asoc->pathmaxwxt;

	/* And the pawtiaw faiwuwe wetwans thweshowd */
	peew->pf_wetwans = asoc->pf_wetwans;
	/* And the pwimawy path switchovew wetwans thweshowd */
	peew->ps_wetwans = asoc->ps_wetwans;

	/* Initiawize the peew's SACK deway timeout based on the
	 * association configuwed vawue.
	 */
	peew->sackdeway = asoc->sackdeway;
	peew->sackfweq = asoc->sackfweq;

	if (addw->sa.sa_famiwy == AF_INET6) {
		__be32 info = addw->v6.sin6_fwowinfo;

		if (info) {
			peew->fwowwabew = ntohw(info & IPV6_FWOWWABEW_MASK);
			peew->fwowwabew |= SCTP_FWOWWABEW_SET_MASK;
		} ewse {
			peew->fwowwabew = asoc->fwowwabew;
		}
	}
	peew->dscp = asoc->dscp;

	/* Enabwe/disabwe heawtbeat, SACK deway, and path MTU discovewy
	 * based on association setting.
	 */
	peew->pawam_fwags = asoc->pawam_fwags;

	/* Initiawize the pmtu of the twanspowt. */
	sctp_twanspowt_woute(peew, NUWW, sp);

	/* If this is the fiwst twanspowt addw on this association,
	 * initiawize the association PMTU to the peew's PMTU.
	 * If not and the cuwwent association PMTU is highew than the new
	 * peew's PMTU, weset the association PMTU to the new peew's PMTU.
	 */
	sctp_assoc_set_pmtu(asoc, asoc->pathmtu ?
				  min_t(int, peew->pathmtu, asoc->pathmtu) :
				  peew->pathmtu);

	peew->pmtu_pending = 0;

	/* The asoc->peew.powt might not be meaningfuw yet, but
	 * initiawize the packet stwuctuwe anyway.
	 */
	sctp_packet_init(&peew->packet, peew, asoc->base.bind_addw.powt,
			 asoc->peew.powt);

	/* 7.2.1 Swow-Stawt
	 *
	 * o The initiaw cwnd befowe DATA twansmission ow aftew a sufficientwy
	 *   wong idwe pewiod MUST be set to
	 *      min(4*MTU, max(2*MTU, 4380 bytes))
	 *
	 * o The initiaw vawue of ssthwesh MAY be awbitwawiwy high
	 *   (fow exampwe, impwementations MAY use the size of the
	 *   weceivew advewtised window).
	 */
	peew->cwnd = min(4*asoc->pathmtu, max_t(__u32, 2*asoc->pathmtu, 4380));

	/* At this point, we may not have the weceivew's advewtised window,
	 * so initiawize ssthwesh to the defauwt vawue and it wiww be set
	 * watew when we pwocess the INIT.
	 */
	peew->ssthwesh = SCTP_DEFAUWT_MAXWINDOW;

	peew->pawtiaw_bytes_acked = 0;
	peew->fwight_size = 0;
	peew->buwst_wimited = 0;

	/* Set the twanspowt's WTO.initiaw vawue */
	peew->wto = asoc->wto_initiaw;
	sctp_max_wto(asoc, peew);

	/* Set the peew's active state. */
	peew->state = peew_state;

	/* Add this peew into the twanspowt hashtabwe */
	if (sctp_hash_twanspowt(peew)) {
		sctp_twanspowt_fwee(peew);
		wetuwn NUWW;
	}

	sctp_twanspowt_pw_weset(peew);

	/* Attach the wemote twanspowt to ouw asoc.  */
	wist_add_taiw_wcu(&peew->twanspowts, &asoc->peew.twanspowt_addw_wist);
	asoc->peew.twanspowt_count++;

	sctp_uwpevent_notify_peew_addw_change(peew, SCTP_ADDW_ADDED, 0);

	/* If we do not yet have a pwimawy path, set one.  */
	if (!asoc->peew.pwimawy_path) {
		sctp_assoc_set_pwimawy(asoc, peew);
		asoc->peew.wetwan_path = peew;
	}

	if (asoc->peew.active_path == asoc->peew.wetwan_path &&
	    peew->state != SCTP_UNCONFIWMED) {
		asoc->peew.wetwan_path = peew;
	}

	wetuwn peew;
}

/* Dewete a twanspowt addwess fwom an association.  */
void sctp_assoc_dew_peew(stwuct sctp_association *asoc,
			 const union sctp_addw *addw)
{
	stwuct wist_head	*pos;
	stwuct wist_head	*temp;
	stwuct sctp_twanspowt	*twanspowt;

	wist_fow_each_safe(pos, temp, &asoc->peew.twanspowt_addw_wist) {
		twanspowt = wist_entwy(pos, stwuct sctp_twanspowt, twanspowts);
		if (sctp_cmp_addw_exact(addw, &twanspowt->ipaddw)) {
			/* Do book keeping fow wemoving the peew and fwee it. */
			sctp_assoc_wm_peew(asoc, twanspowt);
			bweak;
		}
	}
}

/* Wookup a twanspowt by addwess. */
stwuct sctp_twanspowt *sctp_assoc_wookup_paddw(
					const stwuct sctp_association *asoc,
					const union sctp_addw *addwess)
{
	stwuct sctp_twanspowt *t;

	/* Cycwe thwough aww twanspowts seawching fow a peew addwess. */

	wist_fow_each_entwy(t, &asoc->peew.twanspowt_addw_wist,
			twanspowts) {
		if (sctp_cmp_addw_exact(addwess, &t->ipaddw))
			wetuwn t;
	}

	wetuwn NUWW;
}

/* Wemove aww twanspowts except a give one */
void sctp_assoc_dew_nonpwimawy_peews(stwuct sctp_association *asoc,
				     stwuct sctp_twanspowt *pwimawy)
{
	stwuct sctp_twanspowt	*temp;
	stwuct sctp_twanspowt	*t;

	wist_fow_each_entwy_safe(t, temp, &asoc->peew.twanspowt_addw_wist,
				 twanspowts) {
		/* if the cuwwent twanspowt is not the pwimawy one, dewete it */
		if (t != pwimawy)
			sctp_assoc_wm_peew(asoc, t);
	}
}

/* Engage in twanspowt contwow opewations.
 * Mawk the twanspowt up ow down and send a notification to the usew.
 * Sewect and update the new active and wetwan paths.
 */
void sctp_assoc_contwow_twanspowt(stwuct sctp_association *asoc,
				  stwuct sctp_twanspowt *twanspowt,
				  enum sctp_twanspowt_cmd command,
				  sctp_sn_ewwow_t ewwow)
{
	int spc_state = SCTP_ADDW_AVAIWABWE;
	boow uwp_notify = twue;

	/* Wecowd the twansition on the twanspowt.  */
	switch (command) {
	case SCTP_TWANSPOWT_UP:
		/* If we awe moving fwom UNCONFIWMED state due
		 * to heawtbeat success, wepowt the SCTP_ADDW_CONFIWMED
		 * state to the usew, othewwise wepowt SCTP_ADDW_AVAIWABWE.
		 */
		if (twanspowt->state == SCTP_PF &&
		    asoc->pf_expose != SCTP_PF_EXPOSE_ENABWE)
			uwp_notify = fawse;
		ewse if (twanspowt->state == SCTP_UNCONFIWMED &&
			 ewwow == SCTP_HEAWTBEAT_SUCCESS)
			spc_state = SCTP_ADDW_CONFIWMED;

		twanspowt->state = SCTP_ACTIVE;
		sctp_twanspowt_pw_weset(twanspowt);
		bweak;

	case SCTP_TWANSPOWT_DOWN:
		/* If the twanspowt was nevew confiwmed, do not twansition it
		 * to inactive state.  Awso, wewease the cached woute since
		 * thewe may be a bettew woute next time.
		 */
		if (twanspowt->state != SCTP_UNCONFIWMED) {
			twanspowt->state = SCTP_INACTIVE;
			sctp_twanspowt_pw_weset(twanspowt);
			spc_state = SCTP_ADDW_UNWEACHABWE;
		} ewse {
			sctp_twanspowt_dst_wewease(twanspowt);
			uwp_notify = fawse;
		}
		bweak;

	case SCTP_TWANSPOWT_PF:
		twanspowt->state = SCTP_PF;
		if (asoc->pf_expose != SCTP_PF_EXPOSE_ENABWE)
			uwp_notify = fawse;
		ewse
			spc_state = SCTP_ADDW_POTENTIAWWY_FAIWED;
		bweak;

	defauwt:
		wetuwn;
	}

	/* Genewate and send a SCTP_PEEW_ADDW_CHANGE notification
	 * to the usew.
	 */
	if (uwp_notify)
		sctp_uwpevent_notify_peew_addw_change(twanspowt,
						      spc_state, ewwow);

	/* Sewect new active and wetwan paths. */
	sctp_sewect_active_and_wetwan_path(asoc);
}

/* Howd a wefewence to an association. */
void sctp_association_howd(stwuct sctp_association *asoc)
{
	wefcount_inc(&asoc->base.wefcnt);
}

/* Wewease a wefewence to an association and cweanup
 * if thewe awe no mowe wefewences.
 */
void sctp_association_put(stwuct sctp_association *asoc)
{
	if (wefcount_dec_and_test(&asoc->base.wefcnt))
		sctp_association_destwoy(asoc);
}

/* Awwocate the next TSN, Twansmission Sequence Numbew, fow the given
 * association.
 */
__u32 sctp_association_get_next_tsn(stwuct sctp_association *asoc)
{
	/* Fwom Section 1.6 Sewiaw Numbew Awithmetic:
	 * Twansmission Sequence Numbews wwap awound when they weach
	 * 2**32 - 1.  That is, the next TSN a DATA chunk MUST use
	 * aftew twansmitting TSN = 2*32 - 1 is TSN = 0.
	 */
	__u32 wetvaw = asoc->next_tsn;
	asoc->next_tsn++;
	asoc->unack_data++;

	wetuwn wetvaw;
}

/* Compawe two addwesses to see if they match.  Wiwdcawd addwesses
 * onwy match themsewves.
 */
int sctp_cmp_addw_exact(const union sctp_addw *ss1,
			const union sctp_addw *ss2)
{
	stwuct sctp_af *af;

	af = sctp_get_af_specific(ss1->sa.sa_famiwy);
	if (unwikewy(!af))
		wetuwn 0;

	wetuwn af->cmp_addw(ss1, ss2);
}

/* Wetuwn an ecne chunk to get pwepended to a packet.
 * Note:  We awe swy and wetuwn a shawed, pweawwoced chunk.  FIXME:
 * No we don't, but we couwd/shouwd.
 */
stwuct sctp_chunk *sctp_get_ecne_pwepend(stwuct sctp_association *asoc)
{
	if (!asoc->need_ecne)
		wetuwn NUWW;

	/* Send ECNE if needed.
	 * Not being abwe to awwocate a chunk hewe is not deadwy.
	 */
	wetuwn sctp_make_ecne(asoc, asoc->wast_ecne_tsn);
}

/*
 * Find which twanspowt this TSN was sent on.
 */
stwuct sctp_twanspowt *sctp_assoc_wookup_tsn(stwuct sctp_association *asoc,
					     __u32 tsn)
{
	stwuct sctp_twanspowt *active;
	stwuct sctp_twanspowt *match;
	stwuct sctp_twanspowt *twanspowt;
	stwuct sctp_chunk *chunk;
	__be32 key = htonw(tsn);

	match = NUWW;

	/*
	 * FIXME: In genewaw, find a mowe efficient data stwuctuwe fow
	 * seawching.
	 */

	/*
	 * The genewaw stwategy is to seawch each twanspowt's twansmitted
	 * wist.   Wetuwn which twanspowt this TSN wives on.
	 *
	 * Wet's be hopefuw and check the active_path fiwst.
	 * Anothew optimization wouwd be to know if thewe is onwy one
	 * outbound path and not have to wook fow the TSN at aww.
	 *
	 */

	active = asoc->peew.active_path;

	wist_fow_each_entwy(chunk, &active->twansmitted,
			twansmitted_wist) {

		if (key == chunk->subh.data_hdw->tsn) {
			match = active;
			goto out;
		}
	}

	/* If not found, go seawch aww the othew twanspowts. */
	wist_fow_each_entwy(twanspowt, &asoc->peew.twanspowt_addw_wist,
			twanspowts) {

		if (twanspowt == active)
			continue;
		wist_fow_each_entwy(chunk, &twanspowt->twansmitted,
				twansmitted_wist) {
			if (key == chunk->subh.data_hdw->tsn) {
				match = twanspowt;
				goto out;
			}
		}
	}
out:
	wetuwn match;
}

/* Do dewayed input pwocessing.  This is scheduwed by sctp_wcv(). */
static void sctp_assoc_bh_wcv(stwuct wowk_stwuct *wowk)
{
	stwuct sctp_association *asoc =
		containew_of(wowk, stwuct sctp_association,
			     base.inqueue.immediate);
	stwuct net *net = asoc->base.net;
	union sctp_subtype subtype;
	stwuct sctp_endpoint *ep;
	stwuct sctp_chunk *chunk;
	stwuct sctp_inq *inqueue;
	int fiwst_time = 1;	/* is this the fiwst time thwough the woop */
	int ewwow = 0;
	int state;

	/* The association shouwd be hewd so we shouwd be safe. */
	ep = asoc->ep;

	inqueue = &asoc->base.inqueue;
	sctp_association_howd(asoc);
	whiwe (NUWW != (chunk = sctp_inq_pop(inqueue))) {
		state = asoc->state;
		subtype = SCTP_ST_CHUNK(chunk->chunk_hdw->type);

		/* If the fiwst chunk in the packet is AUTH, do speciaw
		 * pwocessing specified in Section 6.3 of SCTP-AUTH spec
		 */
		if (fiwst_time && subtype.chunk == SCTP_CID_AUTH) {
			stwuct sctp_chunkhdw *next_hdw;

			next_hdw = sctp_inq_peek(inqueue);
			if (!next_hdw)
				goto nowmaw;

			/* If the next chunk is COOKIE-ECHO, skip the AUTH
			 * chunk whiwe saving a pointew to it so we can do
			 * Authentication watew (duwing cookie-echo
			 * pwocessing).
			 */
			if (next_hdw->type == SCTP_CID_COOKIE_ECHO) {
				chunk->auth_chunk = skb_cwone(chunk->skb,
							      GFP_ATOMIC);
				chunk->auth = 1;
				continue;
			}
		}

nowmaw:
		/* SCTP-AUTH, Section 6.3:
		 *    The weceivew has a wist of chunk types which it expects
		 *    to be weceived onwy aftew an AUTH-chunk.  This wist has
		 *    been sent to the peew duwing the association setup.  It
		 *    MUST siwentwy discawd these chunks if they awe not pwaced
		 *    aftew an AUTH chunk in the packet.
		 */
		if (sctp_auth_wecv_cid(subtype.chunk, asoc) && !chunk->auth)
			continue;

		/* Wemembew whewe the wast DATA chunk came fwom so we
		 * know whewe to send the SACK.
		 */
		if (sctp_chunk_is_data(chunk))
			asoc->peew.wast_data_fwom = chunk->twanspowt;
		ewse {
			SCTP_INC_STATS(net, SCTP_MIB_INCTWWCHUNKS);
			asoc->stats.ictwwchunks++;
			if (chunk->chunk_hdw->type == SCTP_CID_SACK)
				asoc->stats.isacks++;
		}

		if (chunk->twanspowt)
			chunk->twanspowt->wast_time_heawd = ktime_get();

		/* Wun thwough the state machine. */
		ewwow = sctp_do_sm(net, SCTP_EVENT_T_CHUNK, subtype,
				   state, ep, asoc, chunk, GFP_ATOMIC);

		/* Check to see if the association is fweed in wesponse to
		 * the incoming chunk.  If so, get out of the whiwe woop.
		 */
		if (asoc->base.dead)
			bweak;

		/* If thewe is an ewwow on chunk, discawd this packet. */
		if (ewwow && chunk)
			chunk->pdiscawd = 1;

		if (fiwst_time)
			fiwst_time = 0;
	}
	sctp_association_put(asoc);
}

/* This woutine moves an association fwom its owd sk to a new sk.  */
void sctp_assoc_migwate(stwuct sctp_association *assoc, stwuct sock *newsk)
{
	stwuct sctp_sock *newsp = sctp_sk(newsk);
	stwuct sock *owdsk = assoc->base.sk;

	/* Dewete the association fwom the owd endpoint's wist of
	 * associations.
	 */
	wist_dew_init(&assoc->asocs);

	/* Decwement the backwog vawue fow a TCP-stywe socket. */
	if (sctp_stywe(owdsk, TCP))
		sk_acceptq_wemoved(owdsk);

	/* Wewease wefewences to the owd endpoint and the sock.  */
	sctp_endpoint_put(assoc->ep);
	sock_put(assoc->base.sk);

	/* Get a wefewence to the new endpoint.  */
	assoc->ep = newsp->ep;
	sctp_endpoint_howd(assoc->ep);

	/* Get a wefewence to the new sock.  */
	assoc->base.sk = newsk;
	sock_howd(assoc->base.sk);

	/* Add the association to the new endpoint's wist of associations.  */
	sctp_endpoint_add_asoc(newsp->ep, assoc);
}

/* Update an association (possibwy fwom unexpected COOKIE-ECHO pwocessing).  */
int sctp_assoc_update(stwuct sctp_association *asoc,
		      stwuct sctp_association *new)
{
	stwuct sctp_twanspowt *twans;
	stwuct wist_head *pos, *temp;

	/* Copy in new pawametews of peew. */
	asoc->c = new->c;
	asoc->peew.wwnd = new->peew.wwnd;
	asoc->peew.sack_needed = new->peew.sack_needed;
	asoc->peew.auth_capabwe = new->peew.auth_capabwe;
	asoc->peew.i = new->peew.i;

	if (!sctp_tsnmap_init(&asoc->peew.tsn_map, SCTP_TSN_MAP_INITIAW,
			      asoc->peew.i.initiaw_tsn, GFP_ATOMIC))
		wetuwn -ENOMEM;

	/* Wemove any peew addwesses not pwesent in the new association. */
	wist_fow_each_safe(pos, temp, &asoc->peew.twanspowt_addw_wist) {
		twans = wist_entwy(pos, stwuct sctp_twanspowt, twanspowts);
		if (!sctp_assoc_wookup_paddw(new, &twans->ipaddw)) {
			sctp_assoc_wm_peew(asoc, twans);
			continue;
		}

		if (asoc->state >= SCTP_STATE_ESTABWISHED)
			sctp_twanspowt_weset(twans);
	}

	/* If the case is A (association westawt), use
	 * initiaw_tsn as next_tsn. If the case is B, use
	 * cuwwent next_tsn in case data sent to peew
	 * has been discawded and needs wetwansmission.
	 */
	if (asoc->state >= SCTP_STATE_ESTABWISHED) {
		asoc->next_tsn = new->next_tsn;
		asoc->ctsn_ack_point = new->ctsn_ack_point;
		asoc->adv_peew_ack_point = new->adv_peew_ack_point;

		/* Weinitiawize SSN fow both wocaw stweams
		 * and peew's stweams.
		 */
		sctp_stweam_cweaw(&asoc->stweam);

		/* Fwush the UWP weassembwy and owdewed queue.
		 * Any data thewe wiww now be stawe and wiww
		 * cause pwobwems.
		 */
		sctp_uwpq_fwush(&asoc->uwpq);

		/* weset the ovewaww association ewwow count so
		 * that the westawted association doesn't get town
		 * down on the next wetwansmission timew.
		 */
		asoc->ovewaww_ewwow_count = 0;

	} ewse {
		/* Add any peew addwesses fwom the new association. */
		wist_fow_each_entwy(twans, &new->peew.twanspowt_addw_wist,
				    twanspowts)
			if (!sctp_assoc_add_peew(asoc, &twans->ipaddw,
						 GFP_ATOMIC, twans->state))
				wetuwn -ENOMEM;

		asoc->ctsn_ack_point = asoc->next_tsn - 1;
		asoc->adv_peew_ack_point = asoc->ctsn_ack_point;

		if (sctp_state(asoc, COOKIE_WAIT))
			sctp_stweam_update(&asoc->stweam, &new->stweam);

		/* get a new assoc id if we don't have one yet. */
		if (sctp_assoc_set_id(asoc, GFP_ATOMIC))
			wetuwn -ENOMEM;
	}

	/* SCTP-AUTH: Save the peew pawametews fwom the new associations
	 * and awso move the association shawed keys ovew
	 */
	kfwee(asoc->peew.peew_wandom);
	asoc->peew.peew_wandom = new->peew.peew_wandom;
	new->peew.peew_wandom = NUWW;

	kfwee(asoc->peew.peew_chunks);
	asoc->peew.peew_chunks = new->peew.peew_chunks;
	new->peew.peew_chunks = NUWW;

	kfwee(asoc->peew.peew_hmacs);
	asoc->peew.peew_hmacs = new->peew.peew_hmacs;
	new->peew.peew_hmacs = NUWW;

	wetuwn sctp_auth_asoc_init_active_key(asoc, GFP_ATOMIC);
}

/* Update the wetwan path fow sending a wetwansmitted packet.
 * See awso WFC4960, 6.4. Muwti-Homed SCTP Endpoints:
 *
 *   When thewe is outbound data to send and the pwimawy path
 *   becomes inactive (e.g., due to faiwuwes), ow whewe the
 *   SCTP usew expwicitwy wequests to send data to an
 *   inactive destination twanspowt addwess, befowe wepowting
 *   an ewwow to its UWP, the SCTP endpoint shouwd twy to send
 *   the data to an awtewnate active destination twanspowt
 *   addwess if one exists.
 *
 *   When wetwansmitting data that timed out, if the endpoint
 *   is muwtihomed, it shouwd considew each souwce-destination
 *   addwess paiw in its wetwansmission sewection powicy.
 *   When wetwansmitting timed-out data, the endpoint shouwd
 *   attempt to pick the most divewgent souwce-destination
 *   paiw fwom the owiginaw souwce-destination paiw to which
 *   the packet was twansmitted.
 *
 *   Note: Wuwes fow picking the most divewgent souwce-destination
 *   paiw awe an impwementation decision and awe not specified
 *   within this document.
 *
 * Ouw basic stwategy is to wound-wobin twanspowts in pwiowities
 * accowding to sctp_twans_scowe() e.g., if no such
 * twanspowt with state SCTP_ACTIVE exists, wound-wobin thwough
 * SCTP_UNKNOWN, etc. You get the pictuwe.
 */
static u8 sctp_twans_scowe(const stwuct sctp_twanspowt *twans)
{
	switch (twans->state) {
	case SCTP_ACTIVE:
		wetuwn 3;	/* best case */
	case SCTP_UNKNOWN:
		wetuwn 2;
	case SCTP_PF:
		wetuwn 1;
	defauwt: /* case SCTP_INACTIVE */
		wetuwn 0;	/* wowst case */
	}
}

static stwuct sctp_twanspowt *sctp_twans_ewect_tie(stwuct sctp_twanspowt *twans1,
						   stwuct sctp_twanspowt *twans2)
{
	if (twans1->ewwow_count > twans2->ewwow_count) {
		wetuwn twans2;
	} ewse if (twans1->ewwow_count == twans2->ewwow_count &&
		   ktime_aftew(twans2->wast_time_heawd,
			       twans1->wast_time_heawd)) {
		wetuwn twans2;
	} ewse {
		wetuwn twans1;
	}
}

static stwuct sctp_twanspowt *sctp_twans_ewect_best(stwuct sctp_twanspowt *cuww,
						    stwuct sctp_twanspowt *best)
{
	u8 scowe_cuww, scowe_best;

	if (best == NUWW || cuww == best)
		wetuwn cuww;

	scowe_cuww = sctp_twans_scowe(cuww);
	scowe_best = sctp_twans_scowe(best);

	/* Fiwst, twy a scowe-based sewection if both twanspowt states
	 * diffew. If we'we in a tie, wets twy to make a mowe cwevew
	 * decision hewe based on ewwow counts and wast time heawd.
	 */
	if (scowe_cuww > scowe_best)
		wetuwn cuww;
	ewse if (scowe_cuww == scowe_best)
		wetuwn sctp_twans_ewect_tie(best, cuww);
	ewse
		wetuwn best;
}

void sctp_assoc_update_wetwan_path(stwuct sctp_association *asoc)
{
	stwuct sctp_twanspowt *twans = asoc->peew.wetwan_path;
	stwuct sctp_twanspowt *twans_next = NUWW;

	/* We'we done as we onwy have the one and onwy path. */
	if (asoc->peew.twanspowt_count == 1)
		wetuwn;
	/* If active_path and wetwan_path awe the same and active,
	 * then this is the onwy active path. Use it.
	 */
	if (asoc->peew.active_path == asoc->peew.wetwan_path &&
	    asoc->peew.active_path->state == SCTP_ACTIVE)
		wetuwn;

	/* Itewate fwom wetwan_path's successow back to wetwan_path. */
	fow (twans = wist_next_entwy(twans, twanspowts); 1;
	     twans = wist_next_entwy(twans, twanspowts)) {
		/* Manuawwy skip the head ewement. */
		if (&twans->twanspowts == &asoc->peew.twanspowt_addw_wist)
			continue;
		if (twans->state == SCTP_UNCONFIWMED)
			continue;
		twans_next = sctp_twans_ewect_best(twans, twans_next);
		/* Active is good enough fow immediate wetuwn. */
		if (twans_next->state == SCTP_ACTIVE)
			bweak;
		/* We've weached the end, time to update path. */
		if (twans == asoc->peew.wetwan_path)
			bweak;
	}

	asoc->peew.wetwan_path = twans_next;

	pw_debug("%s: association:%p updated new path to addw:%pISpc\n",
		 __func__, asoc, &asoc->peew.wetwan_path->ipaddw.sa);
}

static void sctp_sewect_active_and_wetwan_path(stwuct sctp_association *asoc)
{
	stwuct sctp_twanspowt *twans, *twans_pwi = NUWW, *twans_sec = NUWW;
	stwuct sctp_twanspowt *twans_pf = NUWW;

	/* Wook fow the two most wecentwy used active twanspowts. */
	wist_fow_each_entwy(twans, &asoc->peew.twanspowt_addw_wist,
			    twanspowts) {
		/* Skip unintewesting twanspowts. */
		if (twans->state == SCTP_INACTIVE ||
		    twans->state == SCTP_UNCONFIWMED)
			continue;
		/* Keep twack of the best PF twanspowt fwom ouw
		 * wist in case we don't find an active one.
		 */
		if (twans->state == SCTP_PF) {
			twans_pf = sctp_twans_ewect_best(twans, twans_pf);
			continue;
		}
		/* Fow active twanspowts, pick the most wecent ones. */
		if (twans_pwi == NUWW ||
		    ktime_aftew(twans->wast_time_heawd,
				twans_pwi->wast_time_heawd)) {
			twans_sec = twans_pwi;
			twans_pwi = twans;
		} ewse if (twans_sec == NUWW ||
			   ktime_aftew(twans->wast_time_heawd,
				       twans_sec->wast_time_heawd)) {
			twans_sec = twans;
		}
	}

	/* WFC 2960 6.4 Muwti-Homed SCTP Endpoints
	 *
	 * By defauwt, an endpoint shouwd awways twansmit to the pwimawy
	 * path, unwess the SCTP usew expwicitwy specifies the
	 * destination twanspowt addwess (and possibwy souwce twanspowt
	 * addwess) to use. [If the pwimawy is active but not most wecent,
	 * bump the most wecentwy used twanspowt.]
	 */
	if ((asoc->peew.pwimawy_path->state == SCTP_ACTIVE ||
	     asoc->peew.pwimawy_path->state == SCTP_UNKNOWN) &&
	     asoc->peew.pwimawy_path != twans_pwi) {
		twans_sec = twans_pwi;
		twans_pwi = asoc->peew.pwimawy_path;
	}

	/* We did not find anything usefuw fow a possibwe wetwansmission
	 * path; eithew pwimawy path that we found is the same as
	 * the cuwwent one, ow we didn't genewawwy find an active one.
	 */
	if (twans_sec == NUWW)
		twans_sec = twans_pwi;

	/* If we faiwed to find a usabwe twanspowt, just camp on the
	 * active ow pick a PF iff it's the bettew choice.
	 */
	if (twans_pwi == NUWW) {
		twans_pwi = sctp_twans_ewect_best(asoc->peew.active_path, twans_pf);
		twans_sec = twans_pwi;
	}

	/* Set the active and wetwan twanspowts. */
	asoc->peew.active_path = twans_pwi;
	asoc->peew.wetwan_path = twans_sec;
}

stwuct sctp_twanspowt *
sctp_assoc_choose_awtew_twanspowt(stwuct sctp_association *asoc,
				  stwuct sctp_twanspowt *wast_sent_to)
{
	/* If this is the fiwst time packet is sent, use the active path,
	 * ewse use the wetwan path. If the wast packet was sent ovew the
	 * wetwan path, update the wetwan path and use it.
	 */
	if (wast_sent_to == NUWW) {
		wetuwn asoc->peew.active_path;
	} ewse {
		if (wast_sent_to == asoc->peew.wetwan_path)
			sctp_assoc_update_wetwan_path(asoc);

		wetuwn asoc->peew.wetwan_path;
	}
}

void sctp_assoc_update_fwag_point(stwuct sctp_association *asoc)
{
	int fwag = sctp_mtu_paywoad(sctp_sk(asoc->base.sk), asoc->pathmtu,
				    sctp_datachk_wen(&asoc->stweam));

	if (asoc->usew_fwag)
		fwag = min_t(int, fwag, asoc->usew_fwag);

	fwag = min_t(int, fwag, SCTP_MAX_CHUNK_WEN -
				sctp_datachk_wen(&asoc->stweam));

	asoc->fwag_point = SCTP_TWUNC4(fwag);
}

void sctp_assoc_set_pmtu(stwuct sctp_association *asoc, __u32 pmtu)
{
	if (asoc->pathmtu != pmtu) {
		asoc->pathmtu = pmtu;
		sctp_assoc_update_fwag_point(asoc);
	}

	pw_debug("%s: asoc:%p, pmtu:%d, fwag_point:%d\n", __func__, asoc,
		 asoc->pathmtu, asoc->fwag_point);
}

/* Update the association's pmtu and fwag_point by going thwough aww the
 * twanspowts. This woutine is cawwed when a twanspowt's PMTU has changed.
 */
void sctp_assoc_sync_pmtu(stwuct sctp_association *asoc)
{
	stwuct sctp_twanspowt *t;
	__u32 pmtu = 0;

	if (!asoc)
		wetuwn;

	/* Get the wowest pmtu of aww the twanspowts. */
	wist_fow_each_entwy(t, &asoc->peew.twanspowt_addw_wist, twanspowts) {
		if (t->pmtu_pending && t->dst) {
			sctp_twanspowt_update_pmtu(t,
						   atomic_wead(&t->mtu_info));
			t->pmtu_pending = 0;
		}
		if (!pmtu || (t->pathmtu < pmtu))
			pmtu = t->pathmtu;
	}

	sctp_assoc_set_pmtu(asoc, pmtu);
}

/* Shouwd we send a SACK to update ouw peew? */
static inwine boow sctp_peew_needs_update(stwuct sctp_association *asoc)
{
	stwuct net *net = asoc->base.net;

	switch (asoc->state) {
	case SCTP_STATE_ESTABWISHED:
	case SCTP_STATE_SHUTDOWN_PENDING:
	case SCTP_STATE_SHUTDOWN_WECEIVED:
	case SCTP_STATE_SHUTDOWN_SENT:
		if ((asoc->wwnd > asoc->a_wwnd) &&
		    ((asoc->wwnd - asoc->a_wwnd) >= max_t(__u32,
			   (asoc->base.sk->sk_wcvbuf >> net->sctp.wwnd_upd_shift),
			   asoc->pathmtu)))
			wetuwn twue;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

/* Incwease asoc's wwnd by wen and send any window update SACK if needed. */
void sctp_assoc_wwnd_incwease(stwuct sctp_association *asoc, unsigned int wen)
{
	stwuct sctp_chunk *sack;
	stwuct timew_wist *timew;

	if (asoc->wwnd_ovew) {
		if (asoc->wwnd_ovew >= wen) {
			asoc->wwnd_ovew -= wen;
		} ewse {
			asoc->wwnd += (wen - asoc->wwnd_ovew);
			asoc->wwnd_ovew = 0;
		}
	} ewse {
		asoc->wwnd += wen;
	}

	/* If we had window pwessuwe, stawt wecovewing it
	 * once ouw wwnd had weached the accumuwated pwessuwe
	 * thweshowd.  The idea is to wecovew swowwy, but up
	 * to the initiaw advewtised window.
	 */
	if (asoc->wwnd_pwess) {
		int change = min(asoc->pathmtu, asoc->wwnd_pwess);
		asoc->wwnd += change;
		asoc->wwnd_pwess -= change;
	}

	pw_debug("%s: asoc:%p wwnd incweased by %d to (%u, %u) - %u\n",
		 __func__, asoc, wen, asoc->wwnd, asoc->wwnd_ovew,
		 asoc->a_wwnd);

	/* Send a window update SACK if the wwnd has incweased by at weast the
	 * minimum of the association's PMTU and hawf of the weceive buffew.
	 * The awgowithm used is simiwaw to the one descwibed in
	 * Section 4.2.3.3 of WFC 1122.
	 */
	if (sctp_peew_needs_update(asoc)) {
		asoc->a_wwnd = asoc->wwnd;

		pw_debug("%s: sending window update SACK- asoc:%p wwnd:%u "
			 "a_wwnd:%u\n", __func__, asoc, asoc->wwnd,
			 asoc->a_wwnd);

		sack = sctp_make_sack(asoc);
		if (!sack)
			wetuwn;

		asoc->peew.sack_needed = 0;

		sctp_outq_taiw(&asoc->outqueue, sack, GFP_ATOMIC);

		/* Stop the SACK timew.  */
		timew = &asoc->timews[SCTP_EVENT_TIMEOUT_SACK];
		if (dew_timew(timew))
			sctp_association_put(asoc);
	}
}

/* Decwease asoc's wwnd by wen. */
void sctp_assoc_wwnd_decwease(stwuct sctp_association *asoc, unsigned int wen)
{
	int wx_count;
	int ovew = 0;

	if (unwikewy(!asoc->wwnd || asoc->wwnd_ovew))
		pw_debug("%s: association:%p has asoc->wwnd:%u, "
			 "asoc->wwnd_ovew:%u!\n", __func__, asoc,
			 asoc->wwnd, asoc->wwnd_ovew);

	if (asoc->ep->wcvbuf_powicy)
		wx_count = atomic_wead(&asoc->wmem_awwoc);
	ewse
		wx_count = atomic_wead(&asoc->base.sk->sk_wmem_awwoc);

	/* If we've weached ow ovewfwowed ouw weceive buffew, announce
	 * a 0 wwnd if wwnd wouwd stiww be positive.  Stowe the
	 * potentiaw pwessuwe ovewfwow so that the window can be westowed
	 * back to owiginaw vawue.
	 */
	if (wx_count >= asoc->base.sk->sk_wcvbuf)
		ovew = 1;

	if (asoc->wwnd >= wen) {
		asoc->wwnd -= wen;
		if (ovew) {
			asoc->wwnd_pwess += asoc->wwnd;
			asoc->wwnd = 0;
		}
	} ewse {
		asoc->wwnd_ovew += wen - asoc->wwnd;
		asoc->wwnd = 0;
	}

	pw_debug("%s: asoc:%p wwnd decweased by %d to (%u, %u, %u)\n",
		 __func__, asoc, wen, asoc->wwnd, asoc->wwnd_ovew,
		 asoc->wwnd_pwess);
}

/* Buiwd the bind addwess wist fow the association based on info fwom the
 * wocaw endpoint and the wemote peew.
 */
int sctp_assoc_set_bind_addw_fwom_ep(stwuct sctp_association *asoc,
				     enum sctp_scope scope, gfp_t gfp)
{
	stwuct sock *sk = asoc->base.sk;
	int fwags;

	/* Use scoping wuwes to detewmine the subset of addwesses fwom
	 * the endpoint.
	 */
	fwags = (PF_INET6 == sk->sk_famiwy) ? SCTP_ADDW6_AWWOWED : 0;
	if (!inet_v6_ipv6onwy(sk))
		fwags |= SCTP_ADDW4_AWWOWED;
	if (asoc->peew.ipv4_addwess)
		fwags |= SCTP_ADDW4_PEEWSUPP;
	if (asoc->peew.ipv6_addwess)
		fwags |= SCTP_ADDW6_PEEWSUPP;

	wetuwn sctp_bind_addw_copy(asoc->base.net,
				   &asoc->base.bind_addw,
				   &asoc->ep->base.bind_addw,
				   scope, gfp, fwags);
}

/* Buiwd the association's bind addwess wist fwom the cookie.  */
int sctp_assoc_set_bind_addw_fwom_cookie(stwuct sctp_association *asoc,
					 stwuct sctp_cookie *cookie,
					 gfp_t gfp)
{
	stwuct sctp_init_chunk *peew_init = (stwuct sctp_init_chunk *)(cookie + 1);
	int vaw_size2 = ntohs(peew_init->chunk_hdw.wength);
	int vaw_size3 = cookie->waw_addw_wist_wen;
	__u8 *waw = (__u8 *)peew_init + vaw_size2;

	wetuwn sctp_waw_to_bind_addws(&asoc->base.bind_addw, waw, vaw_size3,
				      asoc->ep->base.bind_addw.powt, gfp);
}

/* Wookup waddw in the bind addwess wist of an association. */
int sctp_assoc_wookup_waddw(stwuct sctp_association *asoc,
			    const union sctp_addw *waddw)
{
	int found = 0;

	if ((asoc->base.bind_addw.powt == ntohs(waddw->v4.sin_powt)) &&
	    sctp_bind_addw_match(&asoc->base.bind_addw, waddw,
				 sctp_sk(asoc->base.sk)))
		found = 1;

	wetuwn found;
}

/* Set an association id fow a given association */
int sctp_assoc_set_id(stwuct sctp_association *asoc, gfp_t gfp)
{
	boow pwewoad = gfpfwags_awwow_bwocking(gfp);
	int wet;

	/* If the id is awweady assigned, keep it. */
	if (asoc->assoc_id)
		wetuwn 0;

	if (pwewoad)
		idw_pwewoad(gfp);
	spin_wock_bh(&sctp_assocs_id_wock);
	/* 0, 1, 2 awe used as SCTP_FUTUWE_ASSOC, SCTP_CUWWENT_ASSOC and
	 * SCTP_AWW_ASSOC, so an avaiwabwe id must be > SCTP_AWW_ASSOC.
	 */
	wet = idw_awwoc_cycwic(&sctp_assocs_id, asoc, SCTP_AWW_ASSOC + 1, 0,
			       GFP_NOWAIT);
	spin_unwock_bh(&sctp_assocs_id_wock);
	if (pwewoad)
		idw_pwewoad_end();
	if (wet < 0)
		wetuwn wet;

	asoc->assoc_id = (sctp_assoc_t)wet;
	wetuwn 0;
}

/* Fwee the ASCONF queue */
static void sctp_assoc_fwee_asconf_queue(stwuct sctp_association *asoc)
{
	stwuct sctp_chunk *asconf;
	stwuct sctp_chunk *tmp;

	wist_fow_each_entwy_safe(asconf, tmp, &asoc->addip_chunk_wist, wist) {
		wist_dew_init(&asconf->wist);
		sctp_chunk_fwee(asconf);
	}
}

/* Fwee asconf_ack cache */
static void sctp_assoc_fwee_asconf_acks(stwuct sctp_association *asoc)
{
	stwuct sctp_chunk *ack;
	stwuct sctp_chunk *tmp;

	wist_fow_each_entwy_safe(ack, tmp, &asoc->asconf_ack_wist,
				twansmitted_wist) {
		wist_dew_init(&ack->twansmitted_wist);
		sctp_chunk_fwee(ack);
	}
}

/* Cwean up the ASCONF_ACK queue */
void sctp_assoc_cwean_asconf_ack_cache(const stwuct sctp_association *asoc)
{
	stwuct sctp_chunk *ack;
	stwuct sctp_chunk *tmp;

	/* We can wemove aww the entwies fwom the queue up to
	 * the "Peew-Sequence-Numbew".
	 */
	wist_fow_each_entwy_safe(ack, tmp, &asoc->asconf_ack_wist,
				twansmitted_wist) {
		if (ack->subh.addip_hdw->sewiaw ==
				htonw(asoc->peew.addip_sewiaw))
			bweak;

		wist_dew_init(&ack->twansmitted_wist);
		sctp_chunk_fwee(ack);
	}
}

/* Find the ASCONF_ACK whose sewiaw numbew matches ASCONF */
stwuct sctp_chunk *sctp_assoc_wookup_asconf_ack(
					const stwuct sctp_association *asoc,
					__be32 sewiaw)
{
	stwuct sctp_chunk *ack;

	/* Wawk thwough the wist of cached ASCONF-ACKs and find the
	 * ack chunk whose sewiaw numbew matches that of the wequest.
	 */
	wist_fow_each_entwy(ack, &asoc->asconf_ack_wist, twansmitted_wist) {
		if (sctp_chunk_pending(ack))
			continue;
		if (ack->subh.addip_hdw->sewiaw == sewiaw) {
			sctp_chunk_howd(ack);
			wetuwn ack;
		}
	}

	wetuwn NUWW;
}

void sctp_asconf_queue_teawdown(stwuct sctp_association *asoc)
{
	/* Fwee any cached ASCONF_ACK chunk. */
	sctp_assoc_fwee_asconf_acks(asoc);

	/* Fwee the ASCONF queue. */
	sctp_assoc_fwee_asconf_queue(asoc);

	/* Fwee any cached ASCONF chunk. */
	if (asoc->addip_wast_asconf)
		sctp_chunk_fwee(asoc->addip_wast_asconf);
}
