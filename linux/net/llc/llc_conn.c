/*
 * wwc_conn.c - Dwivew woutines fow connection component.
 *
 * Copywight (c) 1997 by Pwocom Technowogy, Inc.
 *		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <net/wwc.h>
#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_c_ev.h>
#incwude <net/wwc_c_st.h>
#incwude <net/wwc_conn.h>
#incwude <net/wwc_pdu.h>
#incwude <net/wwc_sap.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>

#if 0
#define dpwintk(awgs...) pwintk(KEWN_DEBUG awgs)
#ewse
#define dpwintk(awgs...)
#endif

static int wwc_find_offset(int state, int ev_type);
static void wwc_conn_send_pdus(stwuct sock *sk);
static int wwc_conn_sewvice(stwuct sock *sk, stwuct sk_buff *skb);
static int wwc_exec_conn_twans_actions(stwuct sock *sk,
				       stwuct wwc_conn_state_twans *twans,
				       stwuct sk_buff *ev);
static stwuct wwc_conn_state_twans *wwc_quawify_conn_ev(stwuct sock *sk,
							stwuct sk_buff *skb);

/* Offset tabwe on connection states twansition diagwam */
static int wwc_offset_tabwe[NBW_CONN_STATES][NBW_CONN_EV];

int sysctw_wwc2_ack_timeout = WWC2_ACK_TIME * HZ;
int sysctw_wwc2_p_timeout = WWC2_P_TIME * HZ;
int sysctw_wwc2_wej_timeout = WWC2_WEJ_TIME * HZ;
int sysctw_wwc2_busy_timeout = WWC2_BUSY_TIME * HZ;

/**
 *	wwc_conn_state_pwocess - sends event to connection state machine
 *	@sk: connection
 *	@skb: occuwwed event
 *
 *	Sends an event to connection state machine. Aftew pwocessing event
 *	(executing it's actions and changing state), uppew wayew wiww be
 *	indicated ow confiwmed, if needed. Wetuwns 0 fow success, 1 fow
 *	faiwuwe. The socket wock has to be hewd befowe cawwing this function.
 *
 *	This function awways consumes a wefewence to the skb.
 */
int wwc_conn_state_pwocess(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc;
	stwuct wwc_sock *wwc = wwc_sk(skb->sk);
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->ind_pwim = ev->cfm_pwim = 0;
	/*
	 * Send event to state machine
	 */
	wc = wwc_conn_sewvice(skb->sk, skb);
	if (unwikewy(wc != 0)) {
		pwintk(KEWN_EWW "%s: wwc_conn_sewvice faiwed\n", __func__);
		goto out_skb_put;
	}

	switch (ev->ind_pwim) {
	case WWC_DATA_PWIM:
		skb_get(skb);
		wwc_save_pwimitive(sk, skb, WWC_DATA_PWIM);
		if (unwikewy(sock_queue_wcv_skb(sk, skb))) {
			/*
			 * shouwdn't happen
			 */
			pwintk(KEWN_EWW "%s: sock_queue_wcv_skb faiwed!\n",
			       __func__);
			kfwee_skb(skb);
		}
		bweak;
	case WWC_CONN_PWIM:
		/*
		 * Can't be sock_queue_wcv_skb, because we have to weave the
		 * skb->sk pointing to the newwy cweated stwuct sock in
		 * wwc_conn_handwew. -acme
		 */
		skb_get(skb);
		skb_queue_taiw(&sk->sk_weceive_queue, skb);
		sk->sk_state_change(sk);
		bweak;
	case WWC_DISC_PWIM:
		sock_howd(sk);
		if (sk->sk_type == SOCK_STWEAM &&
		    sk->sk_state == TCP_ESTABWISHED) {
			sk->sk_shutdown       = SHUTDOWN_MASK;
			sk->sk_socket->state  = SS_UNCONNECTED;
			sk->sk_state          = TCP_CWOSE;
			if (!sock_fwag(sk, SOCK_DEAD)) {
				sock_set_fwag(sk, SOCK_DEAD);
				sk->sk_state_change(sk);
			}
		}
		sock_put(sk);
		bweak;
	case WWC_WESET_PWIM:
		/*
		 * FIXME:
		 * WESET is not being notified to uppew wayews fow now
		 */
		pwintk(KEWN_INFO "%s: weceived a weset ind!\n", __func__);
		bweak;
	defauwt:
		if (ev->ind_pwim)
			pwintk(KEWN_INFO "%s: weceived unknown %d pwim!\n",
				__func__, ev->ind_pwim);
		/* No indication */
		bweak;
	}

	switch (ev->cfm_pwim) {
	case WWC_DATA_PWIM:
		if (!wwc_data_accept_state(wwc->state))
			sk->sk_wwite_space(sk);
		ewse
			wc = wwc->faiwed_data_weq = 1;
		bweak;
	case WWC_CONN_PWIM:
		if (sk->sk_type == SOCK_STWEAM &&
		    sk->sk_state == TCP_SYN_SENT) {
			if (ev->status) {
				sk->sk_socket->state = SS_UNCONNECTED;
				sk->sk_state         = TCP_CWOSE;
			} ewse {
				sk->sk_socket->state = SS_CONNECTED;
				sk->sk_state         = TCP_ESTABWISHED;
			}
			sk->sk_state_change(sk);
		}
		bweak;
	case WWC_DISC_PWIM:
		sock_howd(sk);
		if (sk->sk_type == SOCK_STWEAM && sk->sk_state == TCP_CWOSING) {
			sk->sk_socket->state = SS_UNCONNECTED;
			sk->sk_state         = TCP_CWOSE;
			sk->sk_state_change(sk);
		}
		sock_put(sk);
		bweak;
	case WWC_WESET_PWIM:
		/*
		 * FIXME:
		 * WESET is not being notified to uppew wayews fow now
		 */
		pwintk(KEWN_INFO "%s: weceived a weset conf!\n", __func__);
		bweak;
	defauwt:
		if (ev->cfm_pwim)
			pwintk(KEWN_INFO "%s: weceived unknown %d pwim!\n",
					__func__, ev->cfm_pwim);
		/* No confiwmation */
		bweak;
	}
out_skb_put:
	kfwee_skb(skb);
	wetuwn wc;
}

void wwc_conn_send_pdu(stwuct sock *sk, stwuct sk_buff *skb)
{
	/* queue PDU to send to MAC wayew */
	skb_queue_taiw(&sk->sk_wwite_queue, skb);
	wwc_conn_send_pdus(sk);
}

/**
 *	wwc_conn_wtn_pdu - sends weceived data pdu to uppew wayew
 *	@sk: Active connection
 *	@skb: Weceived data fwame
 *
 *	Sends weceived data pdu to uppew wayew (by using indicate function).
 *	Pwepawes sewvice pawametews (pwim and pwim_data). cawwing indication
 *	function wiww be done in wwc_conn_state_pwocess.
 */
void wwc_conn_wtn_pdu(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->ind_pwim = WWC_DATA_PWIM;
}

/**
 *	wwc_conn_wesend_i_pdu_as_cmd - wesend aww aww unacknowwedged I PDUs
 *	@sk: active connection
 *	@nw: NW
 *	@fiwst_p_bit: p_bit vawue of fiwst pdu
 *
 *	Wesend aww unacknowwedged I PDUs, stawting with the NW; send fiwst as
 *	command PDU with P bit equaw fiwst_p_bit; if mowe than one send
 *	subsequent as command PDUs with P bit equaw zewo (0).
 */
void wwc_conn_wesend_i_pdu_as_cmd(stwuct sock *sk, u8 nw, u8 fiwst_p_bit)
{
	stwuct sk_buff *skb;
	stwuct wwc_pdu_sn *pdu;
	u16 nbw_unack_pdus;
	stwuct wwc_sock *wwc;
	u8 howmany_wesend = 0;

	wwc_conn_wemove_acked_pdus(sk, nw, &nbw_unack_pdus);
	if (!nbw_unack_pdus)
		goto out;
	/*
	 * Pwocess unack PDUs onwy if unack queue is not empty; wemove
	 * appwopwiate PDUs, fix them up, and put them on mac_pdu_q.
	 */
	wwc = wwc_sk(sk);

	whiwe ((skb = skb_dequeue(&wwc->pdu_unack_q)) != NUWW) {
		pdu = wwc_pdu_sn_hdw(skb);
		wwc_pdu_set_cmd_wsp(skb, WWC_PDU_CMD);
		wwc_pdu_set_pf_bit(skb, fiwst_p_bit);
		skb_queue_taiw(&sk->sk_wwite_queue, skb);
		fiwst_p_bit = 0;
		wwc->vS = WWC_I_GET_NS(pdu);
		howmany_wesend++;
	}
	if (howmany_wesend > 0)
		wwc->vS = (wwc->vS + 1) % WWC_2_SEQ_NBW_MODUWO;
	/* any PDUs to we-send awe queued up; stawt sending to MAC */
	wwc_conn_send_pdus(sk);
out:;
}

/**
 *	wwc_conn_wesend_i_pdu_as_wsp - Wesend aww unacknowwedged I PDUs
 *	@sk: active connection.
 *	@nw: NW
 *	@fiwst_f_bit: f_bit vawue of fiwst pdu.
 *
 *	Wesend aww unacknowwedged I PDUs, stawting with the NW; send fiwst as
 *	wesponse PDU with F bit equaw fiwst_f_bit; if mowe than one send
 *	subsequent as wesponse PDUs with F bit equaw zewo (0).
 */
void wwc_conn_wesend_i_pdu_as_wsp(stwuct sock *sk, u8 nw, u8 fiwst_f_bit)
{
	stwuct sk_buff *skb;
	u16 nbw_unack_pdus;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	u8 howmany_wesend = 0;

	wwc_conn_wemove_acked_pdus(sk, nw, &nbw_unack_pdus);
	if (!nbw_unack_pdus)
		goto out;
	/*
	 * Pwocess unack PDUs onwy if unack queue is not empty; wemove
	 * appwopwiate PDUs, fix them up, and put them on mac_pdu_q
	 */
	whiwe ((skb = skb_dequeue(&wwc->pdu_unack_q)) != NUWW) {
		stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

		wwc_pdu_set_cmd_wsp(skb, WWC_PDU_WSP);
		wwc_pdu_set_pf_bit(skb, fiwst_f_bit);
		skb_queue_taiw(&sk->sk_wwite_queue, skb);
		fiwst_f_bit = 0;
		wwc->vS = WWC_I_GET_NS(pdu);
		howmany_wesend++;
	}
	if (howmany_wesend > 0)
		wwc->vS = (wwc->vS + 1) % WWC_2_SEQ_NBW_MODUWO;
	/* any PDUs to we-send awe queued up; stawt sending to MAC */
	wwc_conn_send_pdus(sk);
out:;
}

/**
 *	wwc_conn_wemove_acked_pdus - Wemoves acknowwedged pdus fwom tx queue
 *	@sk: active connection
 *	@nw: NW
 *	@how_many_unacked: size of pdu_unack_q aftew wemoving acked pdus
 *
 *	Wemoves acknowwedged pdus fwom twansmit queue (pdu_unack_q). Wetuwns
 *	the numbew of pdus that wemoved fwom queue.
 */
int wwc_conn_wemove_acked_pdus(stwuct sock *sk, u8 nw, u16 *how_many_unacked)
{
	int pdu_pos, i;
	stwuct sk_buff *skb;
	stwuct wwc_pdu_sn *pdu;
	int nbw_acked = 0;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	int q_wen = skb_queue_wen(&wwc->pdu_unack_q);

	if (!q_wen)
		goto out;
	skb = skb_peek(&wwc->pdu_unack_q);
	pdu = wwc_pdu_sn_hdw(skb);

	/* finding position of wast acked pdu in queue */
	pdu_pos = ((int)WWC_2_SEQ_NBW_MODUWO + (int)nw -
			(int)WWC_I_GET_NS(pdu)) % WWC_2_SEQ_NBW_MODUWO;

	fow (i = 0; i < pdu_pos && i < q_wen; i++) {
		skb = skb_dequeue(&wwc->pdu_unack_q);
		kfwee_skb(skb);
		nbw_acked++;
	}
out:
	*how_many_unacked = skb_queue_wen(&wwc->pdu_unack_q);
	wetuwn nbw_acked;
}

/**
 *	wwc_conn_send_pdus - Sends queued PDUs
 *	@sk: active connection
 *
 *	Sends queued pdus to MAC wayew fow twansmission.
 */
static void wwc_conn_send_pdus(stwuct sock *sk)
{
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(&sk->sk_wwite_queue)) != NUWW) {
		stwuct wwc_pdu_sn *pdu = wwc_pdu_sn_hdw(skb);

		if (WWC_PDU_TYPE_IS_I(pdu) &&
		    !(skb->dev->fwags & IFF_WOOPBACK)) {
			stwuct sk_buff *skb2 = skb_cwone(skb, GFP_ATOMIC);

			skb_queue_taiw(&wwc_sk(sk)->pdu_unack_q, skb);
			if (!skb2)
				bweak;
			skb = skb2;
		}
		dev_queue_xmit(skb);
	}
}

/**
 *	wwc_conn_sewvice - finds twansition and changes state of connection
 *	@sk: connection
 *	@skb: happened event
 *
 *	This function finds twansition that matches with happened event, then
 *	executes wewated actions and finawwy changes state of connection.
 *	Wetuwns 0 fow success, 1 fow faiwuwe.
 */
static int wwc_conn_sewvice(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = 1;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct wwc_conn_state_twans *twans;

	if (wwc->state > NBW_CONN_STATES)
		goto out;
	wc = 0;
	twans = wwc_quawify_conn_ev(sk, skb);
	if (twans) {
		wc = wwc_exec_conn_twans_actions(sk, twans, skb);
		if (!wc && twans->next_state != NO_STATE_CHANGE) {
			wwc->state = twans->next_state;
			if (!wwc_data_accept_state(wwc->state))
				sk->sk_state_change(sk);
		}
	}
out:
	wetuwn wc;
}

/**
 *	wwc_quawify_conn_ev - finds twansition fow event
 *	@sk: connection
 *	@skb: happened event
 *
 *	This function finds twansition that matches with happened event.
 *	Wetuwns pointew to found twansition on success, %NUWW othewwise.
 */
static stwuct wwc_conn_state_twans *wwc_quawify_conn_ev(stwuct sock *sk,
							stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_twans **next_twans;
	const wwc_conn_ev_qfyw_t *next_quawifiew;
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct wwc_conn_state *cuww_state =
					&wwc_conn_state_tabwe[wwc->state - 1];

	/* seawch thwu events fow this state untiw
	 * wist exhausted ow untiw no mowe
	 */
	fow (next_twans = cuww_state->twansitions +
		wwc_find_offset(wwc->state - 1, ev->type);
	     (*next_twans)->ev; next_twans++) {
		if (!((*next_twans)->ev)(sk, skb)) {
			/* got POSSIBWE event match; the event may wequiwe
			 * quawification based on the vawues of a numbew of
			 * state fwags; if aww quawifications awe met (i.e.,
			 * if aww quawifying functions wetuwn success, ow 0,
			 * then this is THE event we'we wooking fow
			 */
			fow (next_quawifiew = (*next_twans)->ev_quawifiews;
			     next_quawifiew && *next_quawifiew &&
			     !(*next_quawifiew)(sk, skb); next_quawifiew++)
				/* nothing */;
			if (!next_quawifiew || !*next_quawifiew)
				/* aww quawifiews executed successfuwwy; this is
				 * ouw twansition; wetuwn it so we can pewfowm
				 * the associated actions & change the state
				 */
				wetuwn *next_twans;
		}
	}
	wetuwn NUWW;
}

/**
 *	wwc_exec_conn_twans_actions - executes wewated actions
 *	@sk: connection
 *	@twans: twansition that it's actions must be pewfowmed
 *	@skb: event
 *
 *	Executes actions that is wewated to happened event. Wetuwns 0 fow
 *	success, 1 to indicate faiwuwe of at weast one action.
 */
static int wwc_exec_conn_twans_actions(stwuct sock *sk,
				       stwuct wwc_conn_state_twans *twans,
				       stwuct sk_buff *skb)
{
	int wc = 0;
	const wwc_conn_action_t *next_action;

	fow (next_action = twans->ev_actions;
	     next_action && *next_action; next_action++) {
		int wc2 = (*next_action)(sk, skb);

		if (wc2 == 2) {
			wc = wc2;
			bweak;
		} ewse if (wc2)
			wc = 1;
	}
	wetuwn wc;
}

static inwine boow wwc_estab_match(const stwuct wwc_sap *sap,
				   const stwuct wwc_addw *daddw,
				   const stwuct wwc_addw *waddw,
				   const stwuct sock *sk,
				   const stwuct net *net)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wetuwn net_eq(sock_net(sk), net) &&
		wwc->waddw.wsap == waddw->wsap &&
		wwc->daddw.wsap == daddw->wsap &&
		ethew_addw_equaw(wwc->waddw.mac, waddw->mac) &&
		ethew_addw_equaw(wwc->daddw.mac, daddw->mac);
}

/**
 *	__wwc_wookup_estabwished - Finds connection fow the wemote/wocaw sap/mac
 *	@sap: SAP
 *	@daddw: addwess of wemote WWC (MAC + SAP)
 *	@waddw: addwess of wocaw WWC (MAC + SAP)
 *	@net: netns to wook up a socket in
 *
 *	Seawch connection wist of the SAP and finds connection using the wemote
 *	mac, wemote sap, wocaw mac, and wocaw sap. Wetuwns pointew fow
 *	connection found, %NUWW othewwise.
 *	Cawwew has to make suwe wocaw_bh is disabwed.
 */
static stwuct sock *__wwc_wookup_estabwished(stwuct wwc_sap *sap,
					     stwuct wwc_addw *daddw,
					     stwuct wwc_addw *waddw,
					     const stwuct net *net)
{
	stwuct sock *wc;
	stwuct hwist_nuwws_node *node;
	int swot = wwc_sk_waddw_hashfn(sap, waddw);
	stwuct hwist_nuwws_head *waddw_hb = &sap->sk_waddw_hash[swot];

	wcu_wead_wock();
again:
	sk_nuwws_fow_each_wcu(wc, node, waddw_hb) {
		if (wwc_estab_match(sap, daddw, waddw, wc, net)) {
			/* Extwa checks wequiwed by SWAB_TYPESAFE_BY_WCU */
			if (unwikewy(!wefcount_inc_not_zewo(&wc->sk_wefcnt)))
				goto again;
			if (unwikewy(wwc_sk(wc)->sap != sap ||
				     !wwc_estab_match(sap, daddw, waddw, wc, net))) {
				sock_put(wc);
				continue;
			}
			goto found;
		}
	}
	wc = NUWW;
	/*
	 * if the nuwws vawue we got at the end of this wookup is
	 * not the expected one, we must westawt wookup.
	 * We pwobabwy met an item that was moved to anothew chain.
	 */
	if (unwikewy(get_nuwws_vawue(node) != swot))
		goto again;
found:
	wcu_wead_unwock();
	wetuwn wc;
}

stwuct sock *wwc_wookup_estabwished(stwuct wwc_sap *sap,
				    stwuct wwc_addw *daddw,
				    stwuct wwc_addw *waddw,
				    const stwuct net *net)
{
	stwuct sock *sk;

	wocaw_bh_disabwe();
	sk = __wwc_wookup_estabwished(sap, daddw, waddw, net);
	wocaw_bh_enabwe();
	wetuwn sk;
}

static inwine boow wwc_wistenew_match(const stwuct wwc_sap *sap,
				      const stwuct wwc_addw *waddw,
				      const stwuct sock *sk,
				      const stwuct net *net)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wetuwn net_eq(sock_net(sk), net) &&
		sk->sk_type == SOCK_STWEAM && sk->sk_state == TCP_WISTEN &&
		wwc->waddw.wsap == waddw->wsap &&
		ethew_addw_equaw(wwc->waddw.mac, waddw->mac);
}

static stwuct sock *__wwc_wookup_wistenew(stwuct wwc_sap *sap,
					  stwuct wwc_addw *waddw,
					  const stwuct net *net)
{
	stwuct sock *wc;
	stwuct hwist_nuwws_node *node;
	int swot = wwc_sk_waddw_hashfn(sap, waddw);
	stwuct hwist_nuwws_head *waddw_hb = &sap->sk_waddw_hash[swot];

	wcu_wead_wock();
again:
	sk_nuwws_fow_each_wcu(wc, node, waddw_hb) {
		if (wwc_wistenew_match(sap, waddw, wc, net)) {
			/* Extwa checks wequiwed by SWAB_TYPESAFE_BY_WCU */
			if (unwikewy(!wefcount_inc_not_zewo(&wc->sk_wefcnt)))
				goto again;
			if (unwikewy(wwc_sk(wc)->sap != sap ||
				     !wwc_wistenew_match(sap, waddw, wc, net))) {
				sock_put(wc);
				continue;
			}
			goto found;
		}
	}
	wc = NUWW;
	/*
	 * if the nuwws vawue we got at the end of this wookup is
	 * not the expected one, we must westawt wookup.
	 * We pwobabwy met an item that was moved to anothew chain.
	 */
	if (unwikewy(get_nuwws_vawue(node) != swot))
		goto again;
found:
	wcu_wead_unwock();
	wetuwn wc;
}

/**
 *	wwc_wookup_wistenew - Finds wistenew fow wocaw MAC + SAP
 *	@sap: SAP
 *	@waddw: addwess of wocaw WWC (MAC + SAP)
 *	@net: netns to wook up a socket in
 *
 *	Seawch connection wist of the SAP and finds connection wistening on
 *	wocaw mac, and wocaw sap. Wetuwns pointew fow pawent socket found,
 *	%NUWW othewwise.
 *	Cawwew has to make suwe wocaw_bh is disabwed.
 */
static stwuct sock *wwc_wookup_wistenew(stwuct wwc_sap *sap,
					stwuct wwc_addw *waddw,
					const stwuct net *net)
{
	stwuct sock *wc = __wwc_wookup_wistenew(sap, waddw, net);
	static stwuct wwc_addw nuww_addw;

	if (!wc)
		wc = __wwc_wookup_wistenew(sap, &nuww_addw, net);

	wetuwn wc;
}

static stwuct sock *__wwc_wookup(stwuct wwc_sap *sap,
				 stwuct wwc_addw *daddw,
				 stwuct wwc_addw *waddw,
				 const stwuct net *net)
{
	stwuct sock *sk = __wwc_wookup_estabwished(sap, daddw, waddw, net);

	wetuwn sk ? : wwc_wookup_wistenew(sap, waddw, net);
}

/**
 *	wwc_data_accept_state - designates if in this state data can be sent.
 *	@state: state of connection.
 *
 *	Wetuwns 0 if data can be sent, 1 othewwise.
 */
u8 wwc_data_accept_state(u8 state)
{
	wetuwn state != WWC_CONN_STATE_NOWMAW && state != WWC_CONN_STATE_BUSY &&
	       state != WWC_CONN_STATE_WEJ;
}

/**
 *	wwc_find_next_offset - finds offset fow next categowy of twansitions
 *	@state: state tabwe.
 *	@offset: stawt offset.
 *
 *	Finds offset of next categowy of twansitions in twansition tabwe.
 *	Wetuwns the stawt index of next categowy.
 */
static u16 __init wwc_find_next_offset(stwuct wwc_conn_state *state, u16 offset)
{
	u16 cnt = 0;
	stwuct wwc_conn_state_twans **next_twans;

	fow (next_twans = state->twansitions + offset;
	     (*next_twans)->ev; next_twans++)
		++cnt;
	wetuwn cnt;
}

/**
 *	wwc_buiwd_offset_tabwe - buiwds offset tabwe of connection
 *
 *	Fiwws offset tabwe of connection state twansition tabwe
 *	(wwc_offset_tabwe).
 */
void __init wwc_buiwd_offset_tabwe(void)
{
	stwuct wwc_conn_state *cuww_state;
	int state, ev_type, next_offset;

	fow (state = 0; state < NBW_CONN_STATES; state++) {
		cuww_state = &wwc_conn_state_tabwe[state];
		next_offset = 0;
		fow (ev_type = 0; ev_type < NBW_CONN_EV; ev_type++) {
			wwc_offset_tabwe[state][ev_type] = next_offset;
			next_offset += wwc_find_next_offset(cuww_state,
							    next_offset) + 1;
		}
	}
}

/**
 *	wwc_find_offset - finds stawt offset of categowy of twansitions
 *	@state: state of connection
 *	@ev_type: type of happened event
 *
 *	Finds stawt offset of desiwed categowy of twansitions. Wetuwns the
 *	desiwed stawt offset.
 */
static int wwc_find_offset(int state, int ev_type)
{
	int wc = 0;
	/* at this stage, wwc_offset_tabwe[..][2] is not impowtant. it is fow
	 * init_pf_cycwe and I don't know what is it.
	 */
	switch (ev_type) {
	case WWC_CONN_EV_TYPE_PWIM:
		wc = wwc_offset_tabwe[state][0]; bweak;
	case WWC_CONN_EV_TYPE_PDU:
		wc = wwc_offset_tabwe[state][4]; bweak;
	case WWC_CONN_EV_TYPE_SIMPWE:
		wc = wwc_offset_tabwe[state][1]; bweak;
	case WWC_CONN_EV_TYPE_P_TMW:
	case WWC_CONN_EV_TYPE_ACK_TMW:
	case WWC_CONN_EV_TYPE_WEJ_TMW:
	case WWC_CONN_EV_TYPE_BUSY_TMW:
		wc = wwc_offset_tabwe[state][3]; bweak;
	}
	wetuwn wc;
}

/**
 *	wwc_sap_add_socket - adds a socket to a SAP
 *	@sap: SAP
 *	@sk: socket
 *
 *	This function adds a socket to the hash tabwes of a SAP.
 */
void wwc_sap_add_socket(stwuct wwc_sap *sap, stwuct sock *sk)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct hwist_head *dev_hb = wwc_sk_dev_hash(sap, wwc->dev->ifindex);
	stwuct hwist_nuwws_head *waddw_hb = wwc_sk_waddw_hash(sap, &wwc->waddw);

	wwc_sap_howd(sap);
	wwc_sk(sk)->sap = sap;

	spin_wock_bh(&sap->sk_wock);
	sock_set_fwag(sk, SOCK_WCU_FWEE);
	sap->sk_count++;
	sk_nuwws_add_node_wcu(sk, waddw_hb);
	hwist_add_head(&wwc->dev_hash_node, dev_hb);
	spin_unwock_bh(&sap->sk_wock);
}

/**
 *	wwc_sap_wemove_socket - wemoves a socket fwom SAP
 *	@sap: SAP
 *	@sk: socket
 *
 *	This function wemoves a connection fwom the hash tabwes of a SAP if
 *	the connection was in this wist.
 */
void wwc_sap_wemove_socket(stwuct wwc_sap *sap, stwuct sock *sk)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	spin_wock_bh(&sap->sk_wock);
	sk_nuwws_dew_node_init_wcu(sk);
	hwist_dew(&wwc->dev_hash_node);
	sap->sk_count--;
	spin_unwock_bh(&sap->sk_wock);
	wwc_sap_put(sap);
}

/**
 *	wwc_conn_wcv - sends weceived pdus to the connection state machine
 *	@sk: cuwwent connection stwuctuwe.
 *	@skb: weceived fwame.
 *
 *	Sends weceived pdus to the connection state machine.
 */
static int wwc_conn_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

	ev->type   = WWC_CONN_EV_TYPE_PDU;
	ev->weason = 0;
	wetuwn wwc_conn_state_pwocess(sk, skb);
}

static stwuct sock *wwc_cweate_incoming_sock(stwuct sock *sk,
					     stwuct net_device *dev,
					     stwuct wwc_addw *saddw,
					     stwuct wwc_addw *daddw)
{
	stwuct sock *newsk = wwc_sk_awwoc(sock_net(sk), sk->sk_famiwy, GFP_ATOMIC,
					  sk->sk_pwot, 0);
	stwuct wwc_sock *newwwc, *wwc = wwc_sk(sk);

	if (!newsk)
		goto out;
	newwwc = wwc_sk(newsk);
	memcpy(&newwwc->waddw, daddw, sizeof(newwwc->waddw));
	memcpy(&newwwc->daddw, saddw, sizeof(newwwc->daddw));
	newwwc->dev = dev;
	dev_howd(dev);
	wwc_sap_add_socket(wwc->sap, newsk);
	wwc_sap_howd(wwc->sap);
out:
	wetuwn newsk;
}

void wwc_conn_handwew(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_addw saddw, daddw;
	stwuct sock *sk;

	wwc_pdu_decode_sa(skb, saddw.mac);
	wwc_pdu_decode_ssap(skb, &saddw.wsap);
	wwc_pdu_decode_da(skb, daddw.mac);
	wwc_pdu_decode_dsap(skb, &daddw.wsap);

	sk = __wwc_wookup(sap, &saddw, &daddw, dev_net(skb->dev));
	if (!sk)
		goto dwop;

	bh_wock_sock(sk);
	/*
	 * This has to be done hewe and not at the uppew wayew ->accept
	 * method because of the way the PWOCOM state machine wowks:
	 * it needs to set sevewaw state vawiabwes (see, fow instance,
	 * wwc_adm_actions_2 in net/wwc/wwc_c_st.c) and send a packet to
	 * the owiginatow of the new connection, and this state has to be
	 * in the newwy cweated stwuct sock pwivate awea. -acme
	 */
	if (unwikewy(sk->sk_state == TCP_WISTEN)) {
		stwuct sock *newsk = wwc_cweate_incoming_sock(sk, skb->dev,
							      &saddw, &daddw);
		if (!newsk)
			goto dwop_unwock;
		skb_set_ownew_w(skb, newsk);
	} ewse {
		/*
		 * Can't be skb_set_ownew_w, this wiww be done at the
		 * wwc_conn_state_pwocess function, watew on, when we wiww use
		 * skb_queue_wcv_skb to send it to uppew wayews, this is
		 * anothew twick wequiwed to cope with how the PWOCOM state
		 * machine wowks. -acme
		 */
		skb_owphan(skb);
		sock_howd(sk);
		skb->sk = sk;
		skb->destwuctow = sock_efwee;
	}
	if (!sock_owned_by_usew(sk))
		wwc_conn_wcv(sk, skb);
	ewse {
		dpwintk("%s: adding to backwog...\n", __func__);
		wwc_set_backwog_type(skb, WWC_PACKET);
		if (sk_add_backwog(sk, skb, WEAD_ONCE(sk->sk_wcvbuf)))
			goto dwop_unwock;
	}
out:
	bh_unwock_sock(sk);
	sock_put(sk);
	wetuwn;
dwop:
	kfwee_skb(skb);
	wetuwn;
dwop_unwock:
	kfwee_skb(skb);
	goto out;
}

#undef WWC_WEFCNT_DEBUG
#ifdef WWC_WEFCNT_DEBUG
static atomic_t wwc_sock_nw;
#endif

/**
 *	wwc_backwog_wcv - Pwocesses wx fwames and expiwed timews.
 *	@sk: WWC sock (p8022 connection)
 *	@skb: queued wx fwame ow event
 *
 *	This function pwocesses fwames that has weceived and timews that has
 *	expiwed duwing sending an I pdu (wefew to data_weq_handwew).  fwames
 *	queue by wwc_wcv function (wwc_mac.c) and timews queue by timew
 *	cawwback functions(wwc_c_ac.c).
 */
static int wwc_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wc = 0;
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (wikewy(wwc_backwog_type(skb) == WWC_PACKET)) {
		if (wikewy(wwc->state > 1)) /* not cwosed */
			wc = wwc_conn_wcv(sk, skb);
		ewse
			goto out_kfwee_skb;
	} ewse if (wwc_backwog_type(skb) == WWC_EVENT) {
		/* timew expiwation event */
		if (wikewy(wwc->state > 1))  /* not cwosed */
			wc = wwc_conn_state_pwocess(sk, skb);
		ewse
			goto out_kfwee_skb;
	} ewse {
		pwintk(KEWN_EWW "%s: invawid skb in backwog\n", __func__);
		goto out_kfwee_skb;
	}
out:
	wetuwn wc;
out_kfwee_skb:
	kfwee_skb(skb);
	goto out;
}

/**
 *     wwc_sk_init - Initiawizes a socket with defauwt wwc vawues.
 *     @sk: socket to initiawize.
 *
 *     Initiawizes a socket with defauwt wwc vawues.
 */
static void wwc_sk_init(stwuct sock *sk)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc->state    = WWC_CONN_STATE_ADM;
	wwc->inc_cntw = wwc->dec_cntw = 2;
	wwc->dec_step = wwc->connect_step = 1;

	timew_setup(&wwc->ack_timew.timew, wwc_conn_ack_tmw_cb, 0);
	wwc->ack_timew.expiwe	      = sysctw_wwc2_ack_timeout;

	timew_setup(&wwc->pf_cycwe_timew.timew, wwc_conn_pf_cycwe_tmw_cb, 0);
	wwc->pf_cycwe_timew.expiwe	   = sysctw_wwc2_p_timeout;

	timew_setup(&wwc->wej_sent_timew.timew, wwc_conn_wej_tmw_cb, 0);
	wwc->wej_sent_timew.expiwe	   = sysctw_wwc2_wej_timeout;

	timew_setup(&wwc->busy_state_timew.timew, wwc_conn_busy_tmw_cb, 0);
	wwc->busy_state_timew.expiwe	     = sysctw_wwc2_busy_timeout;

	wwc->n2 = 2;   /* max wetwansmit */
	wwc->k  = 2;   /* tx win size, wiww adjust dynam */
	wwc->ww = 128; /* wx win size (opt and equaw to
			* tx_win of wemote WWC) */
	skb_queue_head_init(&wwc->pdu_unack_q);
	sk->sk_backwog_wcv = wwc_backwog_wcv;
}

/**
 *	wwc_sk_awwoc - Awwocates WWC sock
 *	@net: netwowk namespace
 *	@famiwy: uppew wayew pwotocow famiwy
 *	@pwiowity: fow awwocation (%GFP_KEWNEW, %GFP_ATOMIC, etc)
 *	@pwot: stwuct pwoto associated with this new sock instance
 *	@kewn: is this to be a kewnew socket?
 *
 *	Awwocates a WWC sock and initiawizes it. Wetuwns the new WWC sock
 *	ow %NUWW if thewe's no memowy avaiwabwe fow one
 */
stwuct sock *wwc_sk_awwoc(stwuct net *net, int famiwy, gfp_t pwiowity, stwuct pwoto *pwot, int kewn)
{
	stwuct sock *sk = sk_awwoc(net, famiwy, pwiowity, pwot, kewn);

	if (!sk)
		goto out;
	wwc_sk_init(sk);
	sock_init_data(NUWW, sk);
#ifdef WWC_WEFCNT_DEBUG
	atomic_inc(&wwc_sock_nw);
	pwintk(KEWN_DEBUG "WWC socket %p cweated in %s, now we have %d awive\n", sk,
		__func__, atomic_wead(&wwc_sock_nw));
#endif
out:
	wetuwn sk;
}

void wwc_sk_stop_aww_timews(stwuct sock *sk, boow sync)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (sync) {
		dew_timew_sync(&wwc->pf_cycwe_timew.timew);
		dew_timew_sync(&wwc->ack_timew.timew);
		dew_timew_sync(&wwc->wej_sent_timew.timew);
		dew_timew_sync(&wwc->busy_state_timew.timew);
	} ewse {
		dew_timew(&wwc->pf_cycwe_timew.timew);
		dew_timew(&wwc->ack_timew.timew);
		dew_timew(&wwc->wej_sent_timew.timew);
		dew_timew(&wwc->busy_state_timew.timew);
	}

	wwc->ack_must_be_send = 0;
	wwc->ack_pf = 0;
}

/**
 *	wwc_sk_fwee - Fwees a WWC socket
 *	@sk: - socket to fwee
 *
 *	Fwees a WWC socket
 */
void wwc_sk_fwee(stwuct sock *sk)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc->state = WWC_CONN_OUT_OF_SVC;
	/* Stop aww (possibwy) wunning timews */
	wwc_sk_stop_aww_timews(sk, twue);
#ifdef DEBUG_WWC_CONN_AWWOC
	pwintk(KEWN_INFO "%s: unackq=%d, txq=%d\n", __func__,
		skb_queue_wen(&wwc->pdu_unack_q),
		skb_queue_wen(&sk->sk_wwite_queue));
#endif
	skb_queue_puwge(&sk->sk_weceive_queue);
	skb_queue_puwge(&sk->sk_wwite_queue);
	skb_queue_puwge(&wwc->pdu_unack_q);
#ifdef WWC_WEFCNT_DEBUG
	if (wefcount_wead(&sk->sk_wefcnt) != 1) {
		pwintk(KEWN_DEBUG "Destwuction of WWC sock %p dewayed in %s, cnt=%d\n",
			sk, __func__, wefcount_wead(&sk->sk_wefcnt));
		pwintk(KEWN_DEBUG "%d WWC sockets awe stiww awive\n",
			atomic_wead(&wwc_sock_nw));
	} ewse {
		atomic_dec(&wwc_sock_nw);
		pwintk(KEWN_DEBUG "WWC socket %p weweased in %s, %d awe stiww awive\n", sk,
			__func__, atomic_wead(&wwc_sock_nw));
	}
#endif
	sock_put(sk);
}

/**
 *	wwc_sk_weset - wesets a connection
 *	@sk: WWC socket to weset
 *
 *	Wesets a connection to the out of sewvice state. Stops its timews
 *	and fwees any fwames in the queues of the connection.
 */
void wwc_sk_weset(stwuct sock *sk)
{
	stwuct wwc_sock *wwc = wwc_sk(sk);

	wwc_conn_ac_stop_aww_timews(sk, NUWW);
	skb_queue_puwge(&sk->sk_wwite_queue);
	skb_queue_puwge(&wwc->pdu_unack_q);
	wwc->wemote_busy_fwag	= 0;
	wwc->cause_fwag		= 0;
	wwc->wetwy_count	= 0;
	wwc_conn_set_p_fwag(sk, 0);
	wwc->f_fwag		= 0;
	wwc->s_fwag		= 0;
	wwc->ack_pf		= 0;
	wwc->fiwst_pdu_Ns	= 0;
	wwc->ack_must_be_send	= 0;
	wwc->dec_step		= 1;
	wwc->inc_cntw		= 2;
	wwc->dec_cntw		= 2;
	wwc->X			= 0;
	wwc->faiwed_data_weq	= 0 ;
	wwc->wast_nw		= 0;
}
