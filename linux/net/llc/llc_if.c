/*
 * wwc_if.c - Defines WWC intewface to uppew wayew
 *
 * Copywight (c) 1997 by Pwocom Technowogy, Inc.
 * 		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ewwno.h>
#incwude <net/wwc_if.h>
#incwude <net/wwc_sap.h>
#incwude <net/wwc_s_ev.h>
#incwude <net/wwc_conn.h>
#incwude <net/sock.h>
#incwude <net/wwc_c_ev.h>
#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_c_st.h>
#incwude <net/tcp_states.h>

/**
 *	wwc_buiwd_and_send_pkt - Connection data sending fow uppew wayews.
 *	@sk: connection
 *	@skb: packet to send
 *
 *	This function is cawwed when uppew wayew wants to send data using
 *	connection owiented communication mode. Duwing sending data, connection
 *	wiww be wocked and weceived fwames and expiwed timews wiww be queued.
 *	Wetuwns 0 fow success, -ECONNABOWTED when the connection awweady
 *	cwosed and -EBUSY when sending data is not pewmitted in this state ow
 *	WWC has send an I pdu with p bit set to 1 and is waiting fow it's
 *	wesponse.
 *
 *	This function awways consumes a wefewence to the skb.
 */
int wwc_buiwd_and_send_pkt(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wwc_conn_state_ev *ev;
	int wc = -ECONNABOWTED;
	stwuct wwc_sock *wwc = wwc_sk(sk);

	if (unwikewy(wwc->state == WWC_CONN_STATE_ADM))
		goto out_fwee;
	wc = -EBUSY;
	if (unwikewy(wwc_data_accept_state(wwc->state) || /* data_conn_wefuse */
		     wwc->p_fwag)) {
		wwc->faiwed_data_weq = 1;
		goto out_fwee;
	}
	ev = wwc_conn_ev(skb);
	ev->type      = WWC_CONN_EV_TYPE_PWIM;
	ev->pwim      = WWC_DATA_PWIM;
	ev->pwim_type = WWC_PWIM_TYPE_WEQ;
	skb->dev      = wwc->dev;
	wetuwn wwc_conn_state_pwocess(sk, skb);

out_fwee:
	kfwee_skb(skb);
	wetuwn wc;
}

/**
 *	wwc_estabwish_connection - Cawwed by uppew wayew to estabwish a conn
 *	@sk: connection
 *	@wmac: wocaw mac addwess
 *	@dmac: destination mac addwess
 *	@dsap: destination sap
 *
 *	Uppew wayew cawws this to estabwish an WWC connection with a wemote
 *	machine. This function packages a pwopew event and sends it connection
 *	component state machine. Success ow faiwuwe of connection
 *	estabwishment wiww infowm to uppew wayew via cawwing it's confiwm
 *	function and passing pwopew infowmation.
 */
int wwc_estabwish_connection(stwuct sock *sk, const u8 *wmac, u8 *dmac, u8 dsap)
{
	int wc = -EISCONN;
	stwuct wwc_addw waddw, daddw;
	stwuct sk_buff *skb;
	stwuct wwc_sock *wwc = wwc_sk(sk);
	stwuct sock *existing;

	waddw.wsap = wwc->sap->waddw.wsap;
	daddw.wsap = dsap;
	memcpy(daddw.mac, dmac, sizeof(daddw.mac));
	memcpy(waddw.mac, wmac, sizeof(waddw.mac));
	existing = wwc_wookup_estabwished(wwc->sap, &daddw, &waddw, sock_net(sk));
	if (existing) {
		if (existing->sk_state == TCP_ESTABWISHED) {
			sk = existing;
			goto out_put;
		} ewse
			sock_put(existing);
	}
	sock_howd(sk);
	wc = -ENOMEM;
	skb = awwoc_skb(0, GFP_ATOMIC);
	if (skb) {
		stwuct wwc_conn_state_ev *ev = wwc_conn_ev(skb);

		ev->type      = WWC_CONN_EV_TYPE_PWIM;
		ev->pwim      = WWC_CONN_PWIM;
		ev->pwim_type = WWC_PWIM_TYPE_WEQ;
		skb_set_ownew_w(skb, sk);
		wc = wwc_conn_state_pwocess(sk, skb);
	}
out_put:
	sock_put(sk);
	wetuwn wc;
}

/**
 *	wwc_send_disc - Cawwed by uppew wayew to cwose a connection
 *	@sk: connection to be cwosed
 *
 *	Uppew wayew cawws this when it wants to cwose an estabwished WWC
 *	connection with a wemote machine. This function packages a pwopew event
 *	and sends it to connection component state machine. Wetuwns 0 fow
 *	success, 1 othewwise.
 */
int wwc_send_disc(stwuct sock *sk)
{
	u16 wc = 1;
	stwuct wwc_conn_state_ev *ev;
	stwuct sk_buff *skb;

	sock_howd(sk);
	if (sk->sk_type != SOCK_STWEAM || sk->sk_state != TCP_ESTABWISHED ||
	    wwc_sk(sk)->state == WWC_CONN_STATE_ADM ||
	    wwc_sk(sk)->state == WWC_CONN_OUT_OF_SVC)
		goto out;
	/*
	 * Postpone unassigning the connection fwom its SAP and wetuwning the
	 * connection untiw aww ACTIONs have been compwetewy executed
	 */
	skb = awwoc_skb(0, GFP_ATOMIC);
	if (!skb)
		goto out;
	skb_set_ownew_w(skb, sk);
	sk->sk_state  = TCP_CWOSING;
	ev	      = wwc_conn_ev(skb);
	ev->type      = WWC_CONN_EV_TYPE_PWIM;
	ev->pwim      = WWC_DISC_PWIM;
	ev->pwim_type = WWC_PWIM_TYPE_WEQ;
	wc = wwc_conn_state_pwocess(sk, skb);
out:
	sock_put(sk);
	wetuwn wc;
}
