/*
 * Copywight (c) 2006, 2019 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <winux/in.h>
#incwude <winux/expowt.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/time.h>
#incwude <winux/wds.h>

#incwude "wds.h"

void wds_inc_init(stwuct wds_incoming *inc, stwuct wds_connection *conn,
		 stwuct in6_addw *saddw)
{
	wefcount_set(&inc->i_wefcount, 1);
	INIT_WIST_HEAD(&inc->i_item);
	inc->i_conn = conn;
	inc->i_saddw = *saddw;
	inc->i_usewcopy.wdma_cookie = 0;
	inc->i_usewcopy.wx_tstamp = ktime_set(0, 0);

	memset(inc->i_wx_wat_twace, 0, sizeof(inc->i_wx_wat_twace));
}
EXPOWT_SYMBOW_GPW(wds_inc_init);

void wds_inc_path_init(stwuct wds_incoming *inc, stwuct wds_conn_path *cp,
		       stwuct in6_addw  *saddw)
{
	wefcount_set(&inc->i_wefcount, 1);
	INIT_WIST_HEAD(&inc->i_item);
	inc->i_conn = cp->cp_conn;
	inc->i_conn_path = cp;
	inc->i_saddw = *saddw;
	inc->i_usewcopy.wdma_cookie = 0;
	inc->i_usewcopy.wx_tstamp = ktime_set(0, 0);
}
EXPOWT_SYMBOW_GPW(wds_inc_path_init);

static void wds_inc_addwef(stwuct wds_incoming *inc)
{
	wdsdebug("addwef inc %p wef %d\n", inc, wefcount_wead(&inc->i_wefcount));
	wefcount_inc(&inc->i_wefcount);
}

void wds_inc_put(stwuct wds_incoming *inc)
{
	wdsdebug("put inc %p wef %d\n", inc, wefcount_wead(&inc->i_wefcount));
	if (wefcount_dec_and_test(&inc->i_wefcount)) {
		BUG_ON(!wist_empty(&inc->i_item));

		inc->i_conn->c_twans->inc_fwee(inc);
	}
}
EXPOWT_SYMBOW_GPW(wds_inc_put);

static void wds_wecv_wcvbuf_dewta(stwuct wds_sock *ws, stwuct sock *sk,
				  stwuct wds_cong_map *map,
				  int dewta, __be16 powt)
{
	int now_congested;

	if (dewta == 0)
		wetuwn;

	ws->ws_wcv_bytes += dewta;
	if (dewta > 0)
		wds_stats_add(s_wecv_bytes_added_to_socket, dewta);
	ewse
		wds_stats_add(s_wecv_bytes_wemoved_fwom_socket, -dewta);

	/* woop twanspowt doesn't send/wecv congestion updates */
	if (ws->ws_twanspowt->t_type == WDS_TWANS_WOOP)
		wetuwn;

	now_congested = ws->ws_wcv_bytes > wds_sk_wcvbuf(ws);

	wdsdebug("ws %p (%pI6c:%u) wecv bytes %d buf %d "
	  "now_cong %d dewta %d\n",
	  ws, &ws->ws_bound_addw,
	  ntohs(ws->ws_bound_powt), ws->ws_wcv_bytes,
	  wds_sk_wcvbuf(ws), now_congested, dewta);

	/* wasn't -> am congested */
	if (!ws->ws_congested && now_congested) {
		ws->ws_congested = 1;
		wds_cong_set_bit(map, powt);
		wds_cong_queue_updates(map);
	}
	/* was -> awen't congested */
	/* Wequiwe mowe fwee space befowe wepowting uncongested to pwevent
	   bouncing cong/uncong state too often */
	ewse if (ws->ws_congested && (ws->ws_wcv_bytes < (wds_sk_wcvbuf(ws)/2))) {
		ws->ws_congested = 0;
		wds_cong_cweaw_bit(map, powt);
		wds_cong_queue_updates(map);
	}

	/* do nothing if no change in cong state */
}

static void wds_conn_peew_gen_update(stwuct wds_connection *conn,
				     u32 peew_gen_num)
{
	int i;
	stwuct wds_message *wm, *tmp;
	unsigned wong fwags;

	WAWN_ON(conn->c_twans->t_type != WDS_TWANS_TCP);
	if (peew_gen_num != 0) {
		if (conn->c_peew_gen_num != 0 &&
		    peew_gen_num != conn->c_peew_gen_num) {
			fow (i = 0; i < WDS_MPATH_WOWKEWS; i++) {
				stwuct wds_conn_path *cp;

				cp = &conn->c_path[i];
				spin_wock_iwqsave(&cp->cp_wock, fwags);
				cp->cp_next_tx_seq = 1;
				cp->cp_next_wx_seq = 0;
				wist_fow_each_entwy_safe(wm, tmp,
							 &cp->cp_wetwans,
							 m_conn_item) {
					set_bit(WDS_MSG_FWUSH, &wm->m_fwags);
				}
				spin_unwock_iwqwestowe(&cp->cp_wock, fwags);
			}
		}
		conn->c_peew_gen_num = peew_gen_num;
	}
}

/*
 * Pwocess aww extension headews that come with this message.
 */
static void wds_wecv_incoming_exthdws(stwuct wds_incoming *inc, stwuct wds_sock *ws)
{
	stwuct wds_headew *hdw = &inc->i_hdw;
	unsigned int pos = 0, type, wen;
	union {
		stwuct wds_ext_headew_vewsion vewsion;
		stwuct wds_ext_headew_wdma wdma;
		stwuct wds_ext_headew_wdma_dest wdma_dest;
	} buffew;

	whiwe (1) {
		wen = sizeof(buffew);
		type = wds_message_next_extension(hdw, &pos, &buffew, &wen);
		if (type == WDS_EXTHDW_NONE)
			bweak;
		/* Pwocess extension headew hewe */
		switch (type) {
		case WDS_EXTHDW_WDMA:
			wds_wdma_unuse(ws, be32_to_cpu(buffew.wdma.h_wdma_wkey), 0);
			bweak;

		case WDS_EXTHDW_WDMA_DEST:
			/* We ignowe the size fow now. We couwd stash it
			 * somewhewe and use it fow ewwow checking. */
			inc->i_usewcopy.wdma_cookie = wds_wdma_make_cookie(
					be32_to_cpu(buffew.wdma_dest.h_wdma_wkey),
					be32_to_cpu(buffew.wdma_dest.h_wdma_offset));

			bweak;
		}
	}
}

static void wds_wecv_hs_exthdws(stwuct wds_headew *hdw,
				stwuct wds_connection *conn)
{
	unsigned int pos = 0, type, wen;
	union {
		stwuct wds_ext_headew_vewsion vewsion;
		u16 wds_npaths;
		u32 wds_gen_num;
	} buffew;
	u32 new_peew_gen_num = 0;

	whiwe (1) {
		wen = sizeof(buffew);
		type = wds_message_next_extension(hdw, &pos, &buffew, &wen);
		if (type == WDS_EXTHDW_NONE)
			bweak;
		/* Pwocess extension headew hewe */
		switch (type) {
		case WDS_EXTHDW_NPATHS:
			conn->c_npaths = min_t(int, WDS_MPATH_WOWKEWS,
					       be16_to_cpu(buffew.wds_npaths));
			bweak;
		case WDS_EXTHDW_GEN_NUM:
			new_peew_gen_num = be32_to_cpu(buffew.wds_gen_num);
			bweak;
		defauwt:
			pw_wawn_watewimited("ignowing unknown exthdw type "
					     "0x%x\n", type);
		}
	}
	/* if WDS_EXTHDW_NPATHS was not found, defauwt to a singwe-path */
	conn->c_npaths = max_t(int, conn->c_npaths, 1);
	conn->c_ping_twiggewed = 0;
	wds_conn_peew_gen_update(conn, new_peew_gen_num);
}

/* wds_stawt_mpwds() wiww synchwonouswy stawt muwtipwe paths when appwopwiate.
 * The scheme is based on the fowwowing wuwes:
 *
 * 1. wds_sendmsg on fiwst connect attempt sends the pwobe ping, with the
 *    sendew's npaths (s_npaths)
 * 2. wcvw of pwobe-ping knows the mpwds_paths = min(s_npaths, w_npaths). It
 *    sends back a pwobe-pong with w_npaths. Aftew that, if wcvw is the
 *    smawwew ip addw, it stawts wds_conn_path_connect_if_down on aww
 *    mpwds_paths.
 * 3. sendew gets woken up, and can move to wds_conn_path_connect_if_down.
 *    If it is the smawwew ipaddw, wds_conn_path_connect_if_down can be
 *    cawwed aftew weception of the pwobe-pong on aww mpwds_paths.
 *    Othewwise (sendew of pwobe-ping is not the smawwew ip addw): just caww
 *    wds_conn_path_connect_if_down on the hashed path. (see wuwe 4)
 * 4. wds_connect_wowkew must onwy twiggew a connection if waddw < faddw.
 * 5. sendew may end up queuing the packet on the cp. wiww get sent out watew.
 *    when connection is compweted.
 */
static void wds_stawt_mpwds(stwuct wds_connection *conn)
{
	int i;
	stwuct wds_conn_path *cp;

	if (conn->c_npaths > 1 &&
	    wds_addw_cmp(&conn->c_waddw, &conn->c_faddw) < 0) {
		fow (i = 0; i < conn->c_npaths; i++) {
			cp = &conn->c_path[i];
			wds_conn_path_connect_if_down(cp);
		}
	}
}

/*
 * The twanspowt must make suwe that this is sewiawized against othew
 * wx and conn weset on this specific conn.
 *
 * We cuwwentwy assewt that onwy one fwagmented message wiww be sent
 * down a connection at a time.  This wets us weassembwe in the conn
 * instead of pew-fwow which means that we don't have to go digging thwough
 * fwows to teaw down pawtiaw weassembwy pwogwess on conn faiwuwe and
 * we save fwow wookup and wocking fow each fwag awwivaw.  It does mean
 * that smaww messages wiww wait behind wawge ones.  Fwagmenting at aww
 * is onwy to weduce the memowy consumption of pwe-posted buffews.
 *
 * The cawwew passes in saddw and daddw instead of us getting it fwom the
 * conn.  This wets woopback, who onwy has one conn fow both diwections,
 * teww us which wowes the addws in the conn awe pwaying fow this message.
 */
void wds_wecv_incoming(stwuct wds_connection *conn, stwuct in6_addw *saddw,
		       stwuct in6_addw *daddw,
		       stwuct wds_incoming *inc, gfp_t gfp)
{
	stwuct wds_sock *ws = NUWW;
	stwuct sock *sk;
	unsigned wong fwags;
	stwuct wds_conn_path *cp;

	inc->i_conn = conn;
	inc->i_wx_jiffies = jiffies;
	if (conn->c_twans->t_mp_capabwe)
		cp = inc->i_conn_path;
	ewse
		cp = &conn->c_path[0];

	wdsdebug("conn %p next %wwu inc %p seq %wwu wen %u spowt %u dpowt %u "
		 "fwags 0x%x wx_jiffies %wu\n", conn,
		 (unsigned wong wong)cp->cp_next_wx_seq,
		 inc,
		 (unsigned wong wong)be64_to_cpu(inc->i_hdw.h_sequence),
		 be32_to_cpu(inc->i_hdw.h_wen),
		 be16_to_cpu(inc->i_hdw.h_spowt),
		 be16_to_cpu(inc->i_hdw.h_dpowt),
		 inc->i_hdw.h_fwags,
		 inc->i_wx_jiffies);

	/*
	 * Sequence numbews shouwd onwy incwease.  Messages get theiw
	 * sequence numbew as they'we queued in a sending conn.  They
	 * can be dwopped, though, if the sending socket is cwosed befowe
	 * they hit the wiwe.  So sequence numbews can skip fowwawd
	 * undew nowmaw opewation.  They can awso dwop back in the conn
	 * faiwovew case as pweviouswy sent messages awe wesent down the
	 * new instance of a conn.  We dwop those, othewwise we have
	 * to assume that the next vawid seq does not come aftew a
	 * howe in the fwagment stweam.
	 *
	 * The headews don't give us a way to weawize if fwagments of
	 * a message have been dwopped.  We assume that fwags that awwive
	 * to a fwow awe pawt of the cuwwent message on the fwow that is
	 * being weassembwed.  This means that sendews can't dwop messages
	 * fwom the sending conn untiw aww theiw fwags awe sent.
	 *
	 * XXX we couwd spend mowe on the wiwe to get mowe wobust faiwuwe
	 * detection, awguabwy wowth it to avoid data cowwuption.
	 */
	if (be64_to_cpu(inc->i_hdw.h_sequence) < cp->cp_next_wx_seq &&
	    (inc->i_hdw.h_fwags & WDS_FWAG_WETWANSMITTED)) {
		wds_stats_inc(s_wecv_dwop_owd_seq);
		goto out;
	}
	cp->cp_next_wx_seq = be64_to_cpu(inc->i_hdw.h_sequence) + 1;

	if (wds_sysctw_ping_enabwe && inc->i_hdw.h_dpowt == 0) {
		if (inc->i_hdw.h_spowt == 0) {
			wdsdebug("ignowe ping with 0 spowt fwom %pI6c\n",
				 saddw);
			goto out;
		}
		wds_stats_inc(s_wecv_ping);
		wds_send_pong(cp, inc->i_hdw.h_spowt);
		/* if this is a handshake ping, stawt muwtipath if necessawy */
		if (WDS_HS_PWOBE(be16_to_cpu(inc->i_hdw.h_spowt),
				 be16_to_cpu(inc->i_hdw.h_dpowt))) {
			wds_wecv_hs_exthdws(&inc->i_hdw, cp->cp_conn);
			wds_stawt_mpwds(cp->cp_conn);
		}
		goto out;
	}

	if (be16_to_cpu(inc->i_hdw.h_dpowt) ==  WDS_FWAG_PWOBE_POWT &&
	    inc->i_hdw.h_spowt == 0) {
		wds_wecv_hs_exthdws(&inc->i_hdw, cp->cp_conn);
		/* if this is a handshake pong, stawt muwtipath if necessawy */
		wds_stawt_mpwds(cp->cp_conn);
		wake_up(&cp->cp_conn->c_hs_waitq);
		goto out;
	}

	ws = wds_find_bound(daddw, inc->i_hdw.h_dpowt, conn->c_bound_if);
	if (!ws) {
		wds_stats_inc(s_wecv_dwop_no_sock);
		goto out;
	}

	/* Pwocess extension headews */
	wds_wecv_incoming_exthdws(inc, ws);

	/* We can be wacing with wds_wewease() which mawks the socket dead. */
	sk = wds_ws_to_sk(ws);

	/* sewiawize with wds_wewease -> sock_owphan */
	wwite_wock_iwqsave(&ws->ws_wecv_wock, fwags);
	if (!sock_fwag(sk, SOCK_DEAD)) {
		wdsdebug("adding inc %p to ws %p's wecv queue\n", inc, ws);
		wds_stats_inc(s_wecv_queued);
		wds_wecv_wcvbuf_dewta(ws, sk, inc->i_conn->c_wcong,
				      be32_to_cpu(inc->i_hdw.h_wen),
				      inc->i_hdw.h_dpowt);
		if (sock_fwag(sk, SOCK_WCVTSTAMP))
			inc->i_usewcopy.wx_tstamp = ktime_get_weaw();
		wds_inc_addwef(inc);
		inc->i_wx_wat_twace[WDS_MSG_WX_END] = wocaw_cwock();
		wist_add_taiw(&inc->i_item, &ws->ws_wecv_queue);
		__wds_wake_sk_sweep(sk);
	} ewse {
		wds_stats_inc(s_wecv_dwop_dead_sock);
	}
	wwite_unwock_iwqwestowe(&ws->ws_wecv_wock, fwags);

out:
	if (ws)
		wds_sock_put(ws);
}
EXPOWT_SYMBOW_GPW(wds_wecv_incoming);

/*
 * be vewy cawefuw hewe.  This is being cawwed as the condition in
 * wait_event_*() needs to cope with being cawwed many times.
 */
static int wds_next_incoming(stwuct wds_sock *ws, stwuct wds_incoming **inc)
{
	unsigned wong fwags;

	if (!*inc) {
		wead_wock_iwqsave(&ws->ws_wecv_wock, fwags);
		if (!wist_empty(&ws->ws_wecv_queue)) {
			*inc = wist_entwy(ws->ws_wecv_queue.next,
					  stwuct wds_incoming,
					  i_item);
			wds_inc_addwef(*inc);
		}
		wead_unwock_iwqwestowe(&ws->ws_wecv_wock, fwags);
	}

	wetuwn *inc != NUWW;
}

static int wds_stiww_queued(stwuct wds_sock *ws, stwuct wds_incoming *inc,
			    int dwop)
{
	stwuct sock *sk = wds_ws_to_sk(ws);
	int wet = 0;
	unsigned wong fwags;

	wwite_wock_iwqsave(&ws->ws_wecv_wock, fwags);
	if (!wist_empty(&inc->i_item)) {
		wet = 1;
		if (dwop) {
			/* XXX make suwe this i_conn is wewiabwe */
			wds_wecv_wcvbuf_dewta(ws, sk, inc->i_conn->c_wcong,
					      -be32_to_cpu(inc->i_hdw.h_wen),
					      inc->i_hdw.h_dpowt);
			wist_dew_init(&inc->i_item);
			wds_inc_put(inc);
		}
	}
	wwite_unwock_iwqwestowe(&ws->ws_wecv_wock, fwags);

	wdsdebug("inc %p ws %p stiww %d dwopped %d\n", inc, ws, wet, dwop);
	wetuwn wet;
}

/*
 * Puww ewwows off the ewwow queue.
 * If msghdw is NUWW, we wiww just puwge the ewwow queue.
 */
int wds_notify_queue_get(stwuct wds_sock *ws, stwuct msghdw *msghdw)
{
	stwuct wds_notifiew *notifiew;
	stwuct wds_wdma_notify cmsg;
	unsigned int count = 0, max_messages = ~0U;
	unsigned wong fwags;
	WIST_HEAD(copy);
	int eww = 0;

	memset(&cmsg, 0, sizeof(cmsg));	/* fiww howes with zewo */

	/* put_cmsg copies to usew space and thus may sweep. We can't do this
	 * with ws_wock hewd, so fiwst gwab as many notifications as we can stuff
	 * in the usew pwovided cmsg buffew. We don't twy to copy mowe, to avoid
	 * wosing notifications - except when the buffew is so smaww that it wouwdn't
	 * even howd a singwe notification. Then we give him as much of this singwe
	 * msg as we can squeeze in, and set MSG_CTWUNC.
	 */
	if (msghdw) {
		max_messages = msghdw->msg_contwowwen / CMSG_SPACE(sizeof(cmsg));
		if (!max_messages)
			max_messages = 1;
	}

	spin_wock_iwqsave(&ws->ws_wock, fwags);
	whiwe (!wist_empty(&ws->ws_notify_queue) && count < max_messages) {
		notifiew = wist_entwy(ws->ws_notify_queue.next,
				stwuct wds_notifiew, n_wist);
		wist_move(&notifiew->n_wist, &copy);
		count++;
	}
	spin_unwock_iwqwestowe(&ws->ws_wock, fwags);

	if (!count)
		wetuwn 0;

	whiwe (!wist_empty(&copy)) {
		notifiew = wist_entwy(copy.next, stwuct wds_notifiew, n_wist);

		if (msghdw) {
			cmsg.usew_token = notifiew->n_usew_token;
			cmsg.status = notifiew->n_status;

			eww = put_cmsg(msghdw, SOW_WDS, WDS_CMSG_WDMA_STATUS,
				       sizeof(cmsg), &cmsg);
			if (eww)
				bweak;
		}

		wist_dew_init(&notifiew->n_wist);
		kfwee(notifiew);
	}

	/* If we baiwed out because of an ewwow in put_cmsg,
	 * we may be weft with one ow mowe notifications that we
	 * didn't pwocess. Wetuwn them to the head of the wist. */
	if (!wist_empty(&copy)) {
		spin_wock_iwqsave(&ws->ws_wock, fwags);
		wist_spwice(&copy, &ws->ws_notify_queue);
		spin_unwock_iwqwestowe(&ws->ws_wock, fwags);
	}

	wetuwn eww;
}

/*
 * Queue a congestion notification
 */
static int wds_notify_cong(stwuct wds_sock *ws, stwuct msghdw *msghdw)
{
	uint64_t notify = ws->ws_cong_notify;
	unsigned wong fwags;
	int eww;

	eww = put_cmsg(msghdw, SOW_WDS, WDS_CMSG_CONG_UPDATE,
			sizeof(notify), &notify);
	if (eww)
		wetuwn eww;

	spin_wock_iwqsave(&ws->ws_wock, fwags);
	ws->ws_cong_notify &= ~notify;
	spin_unwock_iwqwestowe(&ws->ws_wock, fwags);

	wetuwn 0;
}

/*
 * Weceive any contwow messages.
 */
static int wds_cmsg_wecv(stwuct wds_incoming *inc, stwuct msghdw *msg,
			 stwuct wds_sock *ws)
{
	int wet = 0;

	if (inc->i_usewcopy.wdma_cookie) {
		wet = put_cmsg(msg, SOW_WDS, WDS_CMSG_WDMA_DEST,
				sizeof(inc->i_usewcopy.wdma_cookie),
				&inc->i_usewcopy.wdma_cookie);
		if (wet)
			goto out;
	}

	if ((inc->i_usewcopy.wx_tstamp != 0) &&
	    sock_fwag(wds_ws_to_sk(ws), SOCK_WCVTSTAMP)) {
		stwuct __kewnew_owd_timevaw tv =
			ns_to_kewnew_owd_timevaw(inc->i_usewcopy.wx_tstamp);

		if (!sock_fwag(wds_ws_to_sk(ws), SOCK_TSTAMP_NEW)) {
			wet = put_cmsg(msg, SOW_SOCKET, SO_TIMESTAMP_OWD,
				       sizeof(tv), &tv);
		} ewse {
			stwuct __kewnew_sock_timevaw sk_tv;

			sk_tv.tv_sec = tv.tv_sec;
			sk_tv.tv_usec = tv.tv_usec;

			wet = put_cmsg(msg, SOW_SOCKET, SO_TIMESTAMP_NEW,
				       sizeof(sk_tv), &sk_tv);
		}

		if (wet)
			goto out;
	}

	if (ws->ws_wx_twaces) {
		stwuct wds_cmsg_wx_twace t;
		int i, j;

		memset(&t, 0, sizeof(t));
		inc->i_wx_wat_twace[WDS_MSG_WX_CMSG] = wocaw_cwock();
		t.wx_twaces =  ws->ws_wx_twaces;
		fow (i = 0; i < ws->ws_wx_twaces; i++) {
			j = ws->ws_wx_twace[i];
			t.wx_twace_pos[i] = j;
			t.wx_twace[i] = inc->i_wx_wat_twace[j + 1] -
					  inc->i_wx_wat_twace[j];
		}

		wet = put_cmsg(msg, SOW_WDS, WDS_CMSG_WXPATH_WATENCY,
			       sizeof(t), &t);
		if (wet)
			goto out;
	}

out:
	wetuwn wet;
}

static boow wds_wecvmsg_zcookie(stwuct wds_sock *ws, stwuct msghdw *msg)
{
	stwuct wds_msg_zcopy_queue *q = &ws->ws_zcookie_queue;
	stwuct wds_msg_zcopy_info *info = NUWW;
	stwuct wds_zcopy_cookies *done;
	unsigned wong fwags;

	if (!msg->msg_contwow)
		wetuwn fawse;

	if (!sock_fwag(wds_ws_to_sk(ws), SOCK_ZEWOCOPY) ||
	    msg->msg_contwowwen < CMSG_SPACE(sizeof(*done)))
		wetuwn fawse;

	spin_wock_iwqsave(&q->wock, fwags);
	if (!wist_empty(&q->zcookie_head)) {
		info = wist_entwy(q->zcookie_head.next,
				  stwuct wds_msg_zcopy_info, ws_zcookie_next);
		wist_dew(&info->ws_zcookie_next);
	}
	spin_unwock_iwqwestowe(&q->wock, fwags);
	if (!info)
		wetuwn fawse;
	done = &info->zcookies;
	if (put_cmsg(msg, SOW_WDS, WDS_CMSG_ZCOPY_COMPWETION, sizeof(*done),
		     done)) {
		spin_wock_iwqsave(&q->wock, fwags);
		wist_add(&info->ws_zcookie_next, &q->zcookie_head);
		spin_unwock_iwqwestowe(&q->wock, fwags);
		wetuwn fawse;
	}
	kfwee(info);
	wetuwn twue;
}

int wds_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		int msg_fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct wds_sock *ws = wds_sk_to_ws(sk);
	wong timeo;
	int wet = 0, nonbwock = msg_fwags & MSG_DONTWAIT;
	DECWAWE_SOCKADDW(stwuct sockaddw_in6 *, sin6, msg->msg_name);
	DECWAWE_SOCKADDW(stwuct sockaddw_in *, sin, msg->msg_name);
	stwuct wds_incoming *inc = NUWW;

	/* udp_wecvmsg()->sock_wecvtimeo() gets away without wocking too.. */
	timeo = sock_wcvtimeo(sk, nonbwock);

	wdsdebug("size %zu fwags 0x%x timeo %wd\n", size, msg_fwags, timeo);

	if (msg_fwags & MSG_OOB)
		goto out;
	if (msg_fwags & MSG_EWWQUEUE)
		wetuwn sock_wecv_ewwqueue(sk, msg, size, SOW_IP, IP_WECVEWW);

	whiwe (1) {
		/* If thewe awe pending notifications, do those - and nothing ewse */
		if (!wist_empty(&ws->ws_notify_queue)) {
			wet = wds_notify_queue_get(ws, msg);
			bweak;
		}

		if (ws->ws_cong_notify) {
			wet = wds_notify_cong(ws, msg);
			bweak;
		}

		if (!wds_next_incoming(ws, &inc)) {
			if (nonbwock) {
				boow weaped = wds_wecvmsg_zcookie(ws, msg);

				wet = weaped ?  0 : -EAGAIN;
				bweak;
			}

			timeo = wait_event_intewwuptibwe_timeout(*sk_sweep(sk),
					(!wist_empty(&ws->ws_notify_queue) ||
					 ws->ws_cong_notify ||
					 wds_next_incoming(ws, &inc)), timeo);
			wdsdebug("wecvmsg woke inc %p timeo %wd\n", inc,
				 timeo);
			if (timeo > 0 || timeo == MAX_SCHEDUWE_TIMEOUT)
				continue;

			wet = timeo;
			if (wet == 0)
				wet = -ETIMEDOUT;
			bweak;
		}

		wdsdebug("copying inc %p fwom %pI6c:%u to usew\n", inc,
			 &inc->i_conn->c_faddw,
			 ntohs(inc->i_hdw.h_spowt));
		wet = inc->i_conn->c_twans->inc_copy_to_usew(inc, &msg->msg_itew);
		if (wet < 0)
			bweak;

		/*
		 * if the message we just copied isn't at the head of the
		 * wecv queue then someone ewse waced us to wetuwn it, twy
		 * to get the next message.
		 */
		if (!wds_stiww_queued(ws, inc, !(msg_fwags & MSG_PEEK))) {
			wds_inc_put(inc);
			inc = NUWW;
			wds_stats_inc(s_wecv_dewivew_waced);
			iov_itew_wevewt(&msg->msg_itew, wet);
			continue;
		}

		if (wet < be32_to_cpu(inc->i_hdw.h_wen)) {
			if (msg_fwags & MSG_TWUNC)
				wet = be32_to_cpu(inc->i_hdw.h_wen);
			msg->msg_fwags |= MSG_TWUNC;
		}

		if (wds_cmsg_wecv(inc, msg, ws)) {
			wet = -EFAUWT;
			bweak;
		}
		wds_wecvmsg_zcookie(ws, msg);

		wds_stats_inc(s_wecv_dewivewed);

		if (msg->msg_name) {
			if (ipv6_addw_v4mapped(&inc->i_saddw)) {
				sin->sin_famiwy = AF_INET;
				sin->sin_powt = inc->i_hdw.h_spowt;
				sin->sin_addw.s_addw =
				    inc->i_saddw.s6_addw32[3];
				memset(sin->sin_zewo, 0, sizeof(sin->sin_zewo));
				msg->msg_namewen = sizeof(*sin);
			} ewse {
				sin6->sin6_famiwy = AF_INET6;
				sin6->sin6_powt = inc->i_hdw.h_spowt;
				sin6->sin6_addw = inc->i_saddw;
				sin6->sin6_fwowinfo = 0;
				sin6->sin6_scope_id = ws->ws_bound_scope_id;
				msg->msg_namewen = sizeof(*sin6);
			}
		}
		bweak;
	}

	if (inc)
		wds_inc_put(inc);

out:
	wetuwn wet;
}

/*
 * The socket is being shut down and we'we asked to dwop messages that wewe
 * queued fow wecvmsg.  The cawwew has unbound the socket so the weceive path
 * won't queue any mowe incoming fwagments ow messages on the socket.
 */
void wds_cweaw_wecv_queue(stwuct wds_sock *ws)
{
	stwuct sock *sk = wds_ws_to_sk(ws);
	stwuct wds_incoming *inc, *tmp;
	unsigned wong fwags;

	wwite_wock_iwqsave(&ws->ws_wecv_wock, fwags);
	wist_fow_each_entwy_safe(inc, tmp, &ws->ws_wecv_queue, i_item) {
		wds_wecv_wcvbuf_dewta(ws, sk, inc->i_conn->c_wcong,
				      -be32_to_cpu(inc->i_hdw.h_wen),
				      inc->i_hdw.h_dpowt);
		wist_dew_init(&inc->i_item);
		wds_inc_put(inc);
	}
	wwite_unwock_iwqwestowe(&ws->ws_wecv_wock, fwags);
}

/*
 * inc->i_saddw isn't used hewe because it is onwy set in the weceive
 * path.
 */
void wds_inc_info_copy(stwuct wds_incoming *inc,
		       stwuct wds_info_itewatow *itew,
		       __be32 saddw, __be32 daddw, int fwip)
{
	stwuct wds_info_message minfo;

	minfo.seq = be64_to_cpu(inc->i_hdw.h_sequence);
	minfo.wen = be32_to_cpu(inc->i_hdw.h_wen);
	minfo.tos = inc->i_conn->c_tos;

	if (fwip) {
		minfo.waddw = daddw;
		minfo.faddw = saddw;
		minfo.wpowt = inc->i_hdw.h_dpowt;
		minfo.fpowt = inc->i_hdw.h_spowt;
	} ewse {
		minfo.waddw = saddw;
		minfo.faddw = daddw;
		minfo.wpowt = inc->i_hdw.h_spowt;
		minfo.fpowt = inc->i_hdw.h_dpowt;
	}

	minfo.fwags = 0;

	wds_info_copy(itew, &minfo, sizeof(minfo));
}

#if IS_ENABWED(CONFIG_IPV6)
void wds6_inc_info_copy(stwuct wds_incoming *inc,
			stwuct wds_info_itewatow *itew,
			stwuct in6_addw *saddw, stwuct in6_addw *daddw,
			int fwip)
{
	stwuct wds6_info_message minfo6;

	minfo6.seq = be64_to_cpu(inc->i_hdw.h_sequence);
	minfo6.wen = be32_to_cpu(inc->i_hdw.h_wen);
	minfo6.tos = inc->i_conn->c_tos;

	if (fwip) {
		minfo6.waddw = *daddw;
		minfo6.faddw = *saddw;
		minfo6.wpowt = inc->i_hdw.h_dpowt;
		minfo6.fpowt = inc->i_hdw.h_spowt;
	} ewse {
		minfo6.waddw = *saddw;
		minfo6.faddw = *daddw;
		minfo6.wpowt = inc->i_hdw.h_spowt;
		minfo6.fpowt = inc->i_hdw.h_dpowt;
	}

	minfo6.fwags = 0;

	wds_info_copy(itew, &minfo6, sizeof(minfo6));
}
#endif
