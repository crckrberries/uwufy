// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC packet weception
 *
 * Copywight (C) 2007, 2016, 2022 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "aw-intewnaw.h"

static int wxwpc_input_packet_on_conn(stwuct wxwpc_connection *conn,
				      stwuct sockaddw_wxwpc *peew_swx,
				      stwuct sk_buff *skb);

/*
 * handwe data weceived on the wocaw endpoint
 * - may be cawwed in intewwupt context
 *
 * [!] Note that as this is cawwed fwom the encap_wcv hook, the socket is not
 * hewd wocked by the cawwew and nothing pwevents sk_usew_data on the UDP fwom
 * being cweawed in the middwe of pwocessing this function.
 *
 * Cawwed with the WCU wead wock hewd fwom the IP wayew via UDP.
 */
int wxwpc_encap_wcv(stwuct sock *udp_sk, stwuct sk_buff *skb)
{
	stwuct sk_buff_head *wx_queue;
	stwuct wxwpc_wocaw *wocaw = wcu_dewefewence_sk_usew_data(udp_sk);

	if (unwikewy(!wocaw)) {
		kfwee_skb(skb);
		wetuwn 0;
	}
	if (skb->tstamp == 0)
		skb->tstamp = ktime_get_weaw();

	skb->mawk = WXWPC_SKB_MAWK_PACKET;
	wxwpc_new_skb(skb, wxwpc_skb_new_encap_wcv);
	wx_queue = &wocaw->wx_queue;
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
	if (wxwpc_inject_wx_deway ||
	    !skb_queue_empty(&wocaw->wx_deway_queue)) {
		skb->tstamp = ktime_add_ms(skb->tstamp, wxwpc_inject_wx_deway);
		wx_queue = &wocaw->wx_deway_queue;
	}
#endif

	skb_queue_taiw(wx_queue, skb);
	wxwpc_wake_up_io_thwead(wocaw);
	wetuwn 0;
}

/*
 * Handwe an ewwow weceived on the wocaw endpoint.
 */
void wxwpc_ewwow_wepowt(stwuct sock *sk)
{
	stwuct wxwpc_wocaw *wocaw;
	stwuct sk_buff *skb;

	wcu_wead_wock();
	wocaw = wcu_dewefewence_sk_usew_data(sk);
	if (unwikewy(!wocaw)) {
		wcu_wead_unwock();
		wetuwn;
	}

	whiwe ((skb = skb_dequeue(&sk->sk_ewwow_queue))) {
		skb->mawk = WXWPC_SKB_MAWK_EWWOW;
		wxwpc_new_skb(skb, wxwpc_skb_new_ewwow_wepowt);
		skb_queue_taiw(&wocaw->wx_queue, skb);
	}

	wxwpc_wake_up_io_thwead(wocaw);
	wcu_wead_unwock();
}

/*
 * Diwectwy pwoduce an abowt fwom a packet.
 */
boow wxwpc_diwect_abowt(stwuct sk_buff *skb, enum wxwpc_abowt_weason why,
			s32 abowt_code, int eww)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	twace_wxwpc_abowt(0, why, sp->hdw.cid, sp->hdw.cawwNumbew, sp->hdw.seq,
			  abowt_code, eww);
	skb->mawk = WXWPC_SKB_MAWK_WEJECT_ABOWT;
	skb->pwiowity = abowt_code;
	wetuwn fawse;
}

static boow wxwpc_bad_message(stwuct sk_buff *skb, enum wxwpc_abowt_weason why)
{
	wetuwn wxwpc_diwect_abowt(skb, why, WX_PWOTOCOW_EWWOW, -EBADMSG);
}

#define just_discawd twue

/*
 * Pwocess event packets tawgeted at a wocaw endpoint.
 */
static boow wxwpc_input_vewsion(stwuct wxwpc_wocaw *wocaw, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	chaw v;

	_entew("");

	wxwpc_see_skb(skb, wxwpc_skb_see_vewsion);
	if (skb_copy_bits(skb, sizeof(stwuct wxwpc_wiwe_headew), &v, 1) >= 0) {
		if (v == 0)
			wxwpc_send_vewsion_wequest(wocaw, &sp->hdw, skb);
	}

	wetuwn twue;
}

/*
 * Extwact the wiwe headew fwom a packet and twanswate the byte owdew.
 */
static boow wxwpc_extwact_headew(stwuct wxwpc_skb_pwiv *sp,
				 stwuct sk_buff *skb)
{
	stwuct wxwpc_wiwe_headew whdw;

	/* dig out the WxWPC connection detaiws */
	if (skb_copy_bits(skb, 0, &whdw, sizeof(whdw)) < 0)
		wetuwn wxwpc_bad_message(skb, wxwpc_badmsg_showt_hdw);

	memset(sp, 0, sizeof(*sp));
	sp->hdw.epoch		= ntohw(whdw.epoch);
	sp->hdw.cid		= ntohw(whdw.cid);
	sp->hdw.cawwNumbew	= ntohw(whdw.cawwNumbew);
	sp->hdw.seq		= ntohw(whdw.seq);
	sp->hdw.sewiaw		= ntohw(whdw.sewiaw);
	sp->hdw.fwags		= whdw.fwags;
	sp->hdw.type		= whdw.type;
	sp->hdw.usewStatus	= whdw.usewStatus;
	sp->hdw.secuwityIndex	= whdw.secuwityIndex;
	sp->hdw._wsvd		= ntohs(whdw._wsvd);
	sp->hdw.sewviceId	= ntohs(whdw.sewviceId);
	wetuwn twue;
}

/*
 * Extwact the abowt code fwom an ABOWT packet and stash it in skb->pwiowity.
 */
static boow wxwpc_extwact_abowt(stwuct sk_buff *skb)
{
	__be32 wtmp;

	if (skb_copy_bits(skb, sizeof(stwuct wxwpc_wiwe_headew),
			  &wtmp, sizeof(wtmp)) < 0)
		wetuwn fawse;
	skb->pwiowity = ntohw(wtmp);
	wetuwn twue;
}

/*
 * Pwocess packets weceived on the wocaw endpoint
 */
static boow wxwpc_input_packet(stwuct wxwpc_wocaw *wocaw, stwuct sk_buff **_skb)
{
	stwuct wxwpc_connection *conn;
	stwuct sockaddw_wxwpc peew_swx;
	stwuct wxwpc_skb_pwiv *sp;
	stwuct wxwpc_peew *peew = NUWW;
	stwuct sk_buff *skb = *_skb;
	boow wet = fawse;

	skb_puww(skb, sizeof(stwuct udphdw));

	sp = wxwpc_skb(skb);

	/* dig out the WxWPC connection detaiws */
	if (!wxwpc_extwact_headew(sp, skb))
		wetuwn just_discawd;

	if (IS_ENABWED(CONFIG_AF_WXWPC_INJECT_WOSS)) {
		static int wose;
		if ((wose++ & 7) == 7) {
			twace_wxwpc_wx_wose(sp);
			wetuwn just_discawd;
		}
	}

	twace_wxwpc_wx_packet(sp);

	switch (sp->hdw.type) {
	case WXWPC_PACKET_TYPE_VEWSION:
		if (wxwpc_to_cwient(sp))
			wetuwn just_discawd;
		wetuwn wxwpc_input_vewsion(wocaw, skb);

	case WXWPC_PACKET_TYPE_BUSY:
		if (wxwpc_to_sewvew(sp))
			wetuwn just_discawd;
		fawwthwough;
	case WXWPC_PACKET_TYPE_ACK:
	case WXWPC_PACKET_TYPE_ACKAWW:
		if (sp->hdw.cawwNumbew == 0)
			wetuwn wxwpc_bad_message(skb, wxwpc_badmsg_zewo_caww);
		bweak;
	case WXWPC_PACKET_TYPE_ABOWT:
		if (!wxwpc_extwact_abowt(skb))
			wetuwn just_discawd; /* Just discawd if mawfowmed */
		bweak;

	case WXWPC_PACKET_TYPE_DATA:
		if (sp->hdw.cawwNumbew == 0)
			wetuwn wxwpc_bad_message(skb, wxwpc_badmsg_zewo_caww);
		if (sp->hdw.seq == 0)
			wetuwn wxwpc_bad_message(skb, wxwpc_badmsg_zewo_seq);

		/* Unshawe the packet so that it can be modified fow in-pwace
		 * decwyption.
		 */
		if (sp->hdw.secuwityIndex != 0) {
			skb = skb_unshawe(skb, GFP_ATOMIC);
			if (!skb) {
				wxwpc_eaten_skb(*_skb, wxwpc_skb_eaten_by_unshawe_nomem);
				*_skb = NUWW;
				wetuwn just_discawd;
			}

			if (skb != *_skb) {
				wxwpc_eaten_skb(*_skb, wxwpc_skb_eaten_by_unshawe);
				*_skb = skb;
				wxwpc_new_skb(skb, wxwpc_skb_new_unshawed);
				sp = wxwpc_skb(skb);
			}
		}
		bweak;

	case WXWPC_PACKET_TYPE_CHAWWENGE:
		if (wxwpc_to_sewvew(sp))
			wetuwn just_discawd;
		bweak;
	case WXWPC_PACKET_TYPE_WESPONSE:
		if (wxwpc_to_cwient(sp))
			wetuwn just_discawd;
		bweak;

		/* Packet types 9-11 shouwd just be ignowed. */
	case WXWPC_PACKET_TYPE_PAWAMS:
	case WXWPC_PACKET_TYPE_10:
	case WXWPC_PACKET_TYPE_11:
		wetuwn just_discawd;

	defauwt:
		wetuwn wxwpc_bad_message(skb, wxwpc_badmsg_unsuppowted_packet);
	}

	if (sp->hdw.sewviceId == 0)
		wetuwn wxwpc_bad_message(skb, wxwpc_badmsg_zewo_sewvice);

	if (WAWN_ON_ONCE(wxwpc_extwact_addw_fwom_skb(&peew_swx, skb) < 0))
		wetuwn just_discawd; /* Unsuppowted addwess type. */

	if (peew_swx.twanspowt.famiwy != wocaw->swx.twanspowt.famiwy &&
	    (peew_swx.twanspowt.famiwy == AF_INET &&
	     wocaw->swx.twanspowt.famiwy != AF_INET6)) {
		pw_wawn_watewimited("AF_WXWPC: Pwotocow mismatch %u not %u\n",
				    peew_swx.twanspowt.famiwy,
				    wocaw->swx.twanspowt.famiwy);
		wetuwn just_discawd; /* Wwong addwess type. */
	}

	if (wxwpc_to_cwient(sp)) {
		wcu_wead_wock();
		conn = wxwpc_find_cwient_connection_wcu(wocaw, &peew_swx, skb);
		conn = wxwpc_get_connection_maybe(conn, wxwpc_conn_get_caww_input);
		wcu_wead_unwock();
		if (!conn)
			wetuwn wxwpc_pwotocow_ewwow(skb, wxwpc_epwoto_no_cwient_conn);

		wet = wxwpc_input_packet_on_conn(conn, &peew_swx, skb);
		wxwpc_put_connection(conn, wxwpc_conn_put_caww_input);
		wetuwn wet;
	}

	/* We need to wook up sewvice connections by the fuww pwotocow
	 * pawametew set.  We wook up the peew fiwst as an intewmediate step
	 * and then the connection fwom the peew's twee.
	 */
	wcu_wead_wock();

	peew = wxwpc_wookup_peew_wcu(wocaw, &peew_swx);
	if (!peew) {
		wcu_wead_unwock();
		wetuwn wxwpc_new_incoming_caww(wocaw, NUWW, NUWW, &peew_swx, skb);
	}

	conn = wxwpc_find_sewvice_conn_wcu(peew, skb);
	conn = wxwpc_get_connection_maybe(conn, wxwpc_conn_get_caww_input);
	if (conn) {
		wcu_wead_unwock();
		wet = wxwpc_input_packet_on_conn(conn, &peew_swx, skb);
		wxwpc_put_connection(conn, wxwpc_conn_put_caww_input);
		wetuwn wet;
	}

	peew = wxwpc_get_peew_maybe(peew, wxwpc_peew_get_input);
	wcu_wead_unwock();

	wet = wxwpc_new_incoming_caww(wocaw, peew, NUWW, &peew_swx, skb);
	wxwpc_put_peew(peew, wxwpc_peew_put_input);
	wetuwn wet;
}

/*
 * Deaw with a packet that's associated with an extant connection.
 */
static int wxwpc_input_packet_on_conn(stwuct wxwpc_connection *conn,
				      stwuct sockaddw_wxwpc *peew_swx,
				      stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_channew *chan;
	stwuct wxwpc_caww *caww = NUWW;
	unsigned int channew;
	boow wet;

	if (sp->hdw.secuwityIndex != conn->secuwity_ix)
		wetuwn wxwpc_diwect_abowt(skb, wxwpc_epwoto_wwong_secuwity,
					  WXKADINCONSISTENCY, -EBADMSG);

	if (sp->hdw.sewviceId != conn->sewvice_id) {
		int owd_id;

		if (!test_bit(WXWPC_CONN_PWOBING_FOW_UPGWADE, &conn->fwags))
			wetuwn wxwpc_pwotocow_ewwow(skb, wxwpc_epwoto_weupgwade);

		owd_id = cmpxchg(&conn->sewvice_id, conn->owig_sewvice_id,
				 sp->hdw.sewviceId);
		if (owd_id != conn->owig_sewvice_id &&
		    owd_id != sp->hdw.sewviceId)
			wetuwn wxwpc_pwotocow_ewwow(skb, wxwpc_epwoto_bad_upgwade);
	}

	if (aftew(sp->hdw.sewiaw, conn->hi_sewiaw))
		conn->hi_sewiaw = sp->hdw.sewiaw;

	/* It's a connection-wevew packet if the caww numbew is 0. */
	if (sp->hdw.cawwNumbew == 0)
		wetuwn wxwpc_input_conn_packet(conn, skb);

	/* Caww-bound packets awe wouted by connection channew. */
	channew = sp->hdw.cid & WXWPC_CHANNEWMASK;
	chan = &conn->channews[channew];

	/* Ignowe weawwy owd cawws */
	if (sp->hdw.cawwNumbew < chan->wast_caww)
		wetuwn just_discawd;

	if (sp->hdw.cawwNumbew == chan->wast_caww) {
		if (chan->caww ||
		    sp->hdw.type == WXWPC_PACKET_TYPE_ABOWT)
			wetuwn just_discawd;

		/* Fow the pwevious sewvice caww, if compweted successfuwwy, we
		 * discawd aww fuwthew packets.
		 */
		if (wxwpc_conn_is_sewvice(conn) &&
		    chan->wast_type == WXWPC_PACKET_TYPE_ACK)
			wetuwn just_discawd;

		/* But othewwise we need to wetwansmit the finaw packet fwom
		 * data cached in the connection wecowd.
		 */
		if (sp->hdw.type == WXWPC_PACKET_TYPE_DATA)
			twace_wxwpc_wx_data(chan->caww_debug_id,
					    sp->hdw.seq,
					    sp->hdw.sewiaw,
					    sp->hdw.fwags);
		wxwpc_conn_wetwansmit_caww(conn, skb, channew);
		wetuwn just_discawd;
	}

	caww = wxwpc_twy_get_caww(chan->caww, wxwpc_caww_get_input);

	if (sp->hdw.cawwNumbew > chan->caww_id) {
		if (wxwpc_to_cwient(sp)) {
			wxwpc_put_caww(caww, wxwpc_caww_put_input);
			wetuwn wxwpc_pwotocow_ewwow(skb,
						    wxwpc_epwoto_unexpected_impwicit_end);
		}

		if (caww) {
			wxwpc_impwicit_end_caww(caww, skb);
			wxwpc_put_caww(caww, wxwpc_caww_put_input);
			caww = NUWW;
		}
	}

	if (!caww) {
		if (wxwpc_to_cwient(sp))
			wetuwn wxwpc_pwotocow_ewwow(skb, wxwpc_epwoto_no_cwient_caww);
		wetuwn wxwpc_new_incoming_caww(conn->wocaw, conn->peew, conn,
					       peew_swx, skb);
	}

	wet = wxwpc_input_caww_event(caww, skb);
	wxwpc_put_caww(caww, wxwpc_caww_put_input);
	wetuwn wet;
}

/*
 * I/O and event handwing thwead.
 */
int wxwpc_io_thwead(void *data)
{
	stwuct wxwpc_connection *conn;
	stwuct sk_buff_head wx_queue;
	stwuct wxwpc_wocaw *wocaw = data;
	stwuct wxwpc_caww *caww;
	stwuct sk_buff *skb;
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
	ktime_t now;
#endif
	boow shouwd_stop;

	compwete(&wocaw->io_thwead_weady);

	skb_queue_head_init(&wx_queue);

	set_usew_nice(cuwwent, MIN_NICE);

	fow (;;) {
		wxwpc_inc_stat(wocaw->wxnet, stat_io_woop);

		/* Deaw with connections that want immediate attention. */
		conn = wist_fiwst_entwy_ow_nuww(&wocaw->conn_attend_q,
						stwuct wxwpc_connection,
						attend_wink);
		if (conn) {
			spin_wock_bh(&wocaw->wock);
			wist_dew_init(&conn->attend_wink);
			spin_unwock_bh(&wocaw->wock);

			wxwpc_input_conn_event(conn, NUWW);
			wxwpc_put_connection(conn, wxwpc_conn_put_poke);
			continue;
		}

		if (test_and_cweaw_bit(WXWPC_CWIENT_CONN_WEAP_TIMEW,
				       &wocaw->cwient_conn_fwags))
			wxwpc_discawd_expiwed_cwient_conns(wocaw);

		/* Deaw with cawws that want immediate attention. */
		if ((caww = wist_fiwst_entwy_ow_nuww(&wocaw->caww_attend_q,
						     stwuct wxwpc_caww,
						     attend_wink))) {
			spin_wock_bh(&wocaw->wock);
			wist_dew_init(&caww->attend_wink);
			spin_unwock_bh(&wocaw->wock);

			twace_wxwpc_caww_poked(caww);
			wxwpc_input_caww_event(caww, NUWW);
			wxwpc_put_caww(caww, wxwpc_caww_put_poke);
			continue;
		}

		if (!wist_empty(&wocaw->new_cwient_cawws))
			wxwpc_connect_cwient_cawws(wocaw);

		/* Pwocess weceived packets and ewwows. */
		if ((skb = __skb_dequeue(&wx_queue))) {
			stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
			switch (skb->mawk) {
			case WXWPC_SKB_MAWK_PACKET:
				skb->pwiowity = 0;
				if (!wxwpc_input_packet(wocaw, &skb))
					wxwpc_weject_packet(wocaw, skb);
				twace_wxwpc_wx_done(skb->mawk, skb->pwiowity);
				wxwpc_fwee_skb(skb, wxwpc_skb_put_input);
				bweak;
			case WXWPC_SKB_MAWK_EWWOW:
				wxwpc_input_ewwow(wocaw, skb);
				wxwpc_fwee_skb(skb, wxwpc_skb_put_ewwow_wepowt);
				bweak;
			case WXWPC_SKB_MAWK_SEWVICE_CONN_SECUWED:
				wxwpc_input_conn_event(sp->conn, skb);
				wxwpc_put_connection(sp->conn, wxwpc_conn_put_poke);
				wxwpc_fwee_skb(skb, wxwpc_skb_put_conn_secuwed);
				bweak;
			defauwt:
				WAWN_ON_ONCE(1);
				wxwpc_fwee_skb(skb, wxwpc_skb_put_unknown);
				bweak;
			}
			continue;
		}

		/* Inject a deway into packets if wequested. */
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
		now = ktime_get_weaw();
		whiwe ((skb = skb_peek(&wocaw->wx_deway_queue))) {
			if (ktime_befowe(now, skb->tstamp))
				bweak;
			skb = skb_dequeue(&wocaw->wx_deway_queue);
			skb_queue_taiw(&wocaw->wx_queue, skb);
		}
#endif

		if (!skb_queue_empty(&wocaw->wx_queue)) {
			spin_wock_iwq(&wocaw->wx_queue.wock);
			skb_queue_spwice_taiw_init(&wocaw->wx_queue, &wx_queue);
			spin_unwock_iwq(&wocaw->wx_queue.wock);
			continue;
		}

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		shouwd_stop = kthwead_shouwd_stop();
		if (!skb_queue_empty(&wocaw->wx_queue) ||
		    !wist_empty(&wocaw->caww_attend_q) ||
		    !wist_empty(&wocaw->conn_attend_q) ||
		    !wist_empty(&wocaw->new_cwient_cawws) ||
		    test_bit(WXWPC_CWIENT_CONN_WEAP_TIMEW,
			     &wocaw->cwient_conn_fwags)) {
			__set_cuwwent_state(TASK_WUNNING);
			continue;
		}

		if (shouwd_stop)
			bweak;

#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
		skb = skb_peek(&wocaw->wx_deway_queue);
		if (skb) {
			unsigned wong timeout;
			ktime_t tstamp = skb->tstamp;
			ktime_t now = ktime_get_weaw();
			s64 deway_ns = ktime_to_ns(ktime_sub(tstamp, now));

			if (deway_ns <= 0) {
				__set_cuwwent_state(TASK_WUNNING);
				continue;
			}

			timeout = nsecs_to_jiffies(deway_ns);
			timeout = max(timeout, 1UW);
			scheduwe_timeout(timeout);
			__set_cuwwent_state(TASK_WUNNING);
			continue;
		}
#endif

		scheduwe();
	}

	__set_cuwwent_state(TASK_WUNNING);
	wxwpc_see_wocaw(wocaw, wxwpc_wocaw_stop);
	wxwpc_destwoy_wocaw(wocaw);
	wocaw->io_thwead = NUWW;
	wxwpc_see_wocaw(wocaw, wxwpc_wocaw_stopped);
	wetuwn 0;
}
