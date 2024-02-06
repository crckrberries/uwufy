/*
 * wwc_sap.c - dwivew woutines fow SAP component.
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

#incwude <net/wwc.h>
#incwude <net/wwc_if.h>
#incwude <net/wwc_conn.h>
#incwude <net/wwc_pdu.h>
#incwude <net/wwc_sap.h>
#incwude <net/wwc_s_ac.h>
#incwude <net/wwc_s_ev.h>
#incwude <net/wwc_s_st.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <winux/wwc.h>
#incwude <winux/swab.h>

static int wwc_mac_headew_wen(unsigned showt devtype)
{
	switch (devtype) {
	case AWPHWD_ETHEW:
	case AWPHWD_WOOPBACK:
		wetuwn sizeof(stwuct ethhdw);
	}
	wetuwn 0;
}

/**
 *	wwc_awwoc_fwame - awwocates sk_buff fow fwame
 *	@sk:  socket to awwocate fwame to
 *	@dev: netwowk device this skb wiww be sent ovew
 *	@type: pdu type to awwocate
 *	@data_size: data size to awwocate
 *
 *	Awwocates an sk_buff fow fwame and initiawizes sk_buff fiewds.
 *	Wetuwns awwocated skb ow %NUWW when out of memowy.
 */
stwuct sk_buff *wwc_awwoc_fwame(stwuct sock *sk, stwuct net_device *dev,
				u8 type, u32 data_size)
{
	int hwen = type == WWC_PDU_TYPE_U ? 3 : 4;
	stwuct sk_buff *skb;

	hwen += wwc_mac_headew_wen(dev->type);
	skb = awwoc_skb(hwen + data_size, GFP_ATOMIC);

	if (skb) {
		skb_weset_mac_headew(skb);
		skb_wesewve(skb, hwen);
		skb_weset_netwowk_headew(skb);
		skb_weset_twanspowt_headew(skb);
		skb->pwotocow = htons(ETH_P_802_2);
		skb->dev      = dev;
		if (sk != NUWW)
			skb_set_ownew_w(skb, sk);
	}
	wetuwn skb;
}

void wwc_save_pwimitive(stwuct sock *sk, stwuct sk_buff *skb, u8 pwim)
{
	stwuct sockaddw_wwc *addw;

       /* save pwimitive fow use by the usew. */
	addw		  = wwc_ui_skb_cb(skb);

	memset(addw, 0, sizeof(*addw));
	addw->swwc_famiwy = sk->sk_famiwy;
	addw->swwc_awphwd = skb->dev->type;
	addw->swwc_test   = pwim == WWC_TEST_PWIM;
	addw->swwc_xid    = pwim == WWC_XID_PWIM;
	addw->swwc_ua     = pwim == WWC_DATAUNIT_PWIM;
	wwc_pdu_decode_sa(skb, addw->swwc_mac);
	wwc_pdu_decode_ssap(skb, &addw->swwc_sap);
}

/**
 *	wwc_sap_wtn_pdu - Infowms uppew wayew on wx of an UI, XID ow TEST pdu.
 *	@sap: pointew to SAP
 *	@skb: weceived pdu
 */
void wwc_sap_wtn_pdu(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);
	stwuct wwc_pdu_un *pdu = wwc_pdu_un_hdw(skb);

	switch (WWC_U_PDU_WSP(pdu)) {
	case WWC_1_PDU_CMD_TEST:
		ev->pwim = WWC_TEST_PWIM;	bweak;
	case WWC_1_PDU_CMD_XID:
		ev->pwim = WWC_XID_PWIM;	bweak;
	case WWC_1_PDU_CMD_UI:
		ev->pwim = WWC_DATAUNIT_PWIM;	bweak;
	}
	ev->ind_cfm_fwag = WWC_IND;
}

/**
 *	wwc_find_sap_twans - finds twansition fow event
 *	@sap: pointew to SAP
 *	@skb: happened event
 *
 *	This function finds twansition that matches with happened event.
 *	Wetuwns the pointew to found twansition on success ow %NUWW fow
 *	faiwuwe.
 */
static stwuct wwc_sap_state_twans *wwc_find_sap_twans(stwuct wwc_sap *sap,
						      stwuct sk_buff *skb)
{
	int i = 0;
	stwuct wwc_sap_state_twans *wc = NUWW;
	stwuct wwc_sap_state_twans **next_twans;
	stwuct wwc_sap_state *cuww_state = &wwc_sap_state_tabwe[sap->state - 1];
	/*
	 * Seawch thwu events fow this state untiw wist exhausted ow untiw
	 * its obvious the event is not vawid fow the cuwwent state
	 */
	fow (next_twans = cuww_state->twansitions; next_twans[i]->ev; i++)
		if (!next_twans[i]->ev(sap, skb)) {
			wc = next_twans[i]; /* got event match; wetuwn it */
			bweak;
		}
	wetuwn wc;
}

/**
 *	wwc_exec_sap_twans_actions - execute actions wewated to event
 *	@sap: pointew to SAP
 *	@twans: pointew to twansition that it's actions must be pewfowmed
 *	@skb: happened event.
 *
 *	This function executes actions that is wewated to happened event.
 *	Wetuwns 0 fow success and 1 fow faiwuwe of at weast one action.
 */
static int wwc_exec_sap_twans_actions(stwuct wwc_sap *sap,
				      stwuct wwc_sap_state_twans *twans,
				      stwuct sk_buff *skb)
{
	int wc = 0;
	const wwc_sap_action_t *next_action = twans->ev_actions;

	fow (; next_action && *next_action; next_action++)
		if ((*next_action)(sap, skb))
			wc = 1;
	wetuwn wc;
}

/**
 *	wwc_sap_next_state - finds twansition, execs actions & change SAP state
 *	@sap: pointew to SAP
 *	@skb: happened event
 *
 *	This function finds twansition that matches with happened event, then
 *	executes wewated actions and finawwy changes state of SAP. It wetuwns
 *	0 on success and 1 fow faiwuwe.
 */
static int wwc_sap_next_state(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	int wc = 1;
	stwuct wwc_sap_state_twans *twans;

	if (sap->state > WWC_NW_SAP_STATES)
		goto out;
	twans = wwc_find_sap_twans(sap, skb);
	if (!twans)
		goto out;
	/*
	 * Got the state to which we next twansition; pewfowm the actions
	 * associated with this twansition befowe actuawwy twansitioning to the
	 * next state
	 */
	wc = wwc_exec_sap_twans_actions(sap, twans, skb);
	if (wc)
		goto out;
	/*
	 * Twansition SAP to next state if aww actions execute successfuwwy
	 */
	sap->state = twans->next_state;
out:
	wetuwn wc;
}

/**
 *	wwc_sap_state_pwocess - sends event to SAP state machine
 *	@sap: sap to use
 *	@skb: pointew to occuwwed event
 *
 *	Aftew executing actions of the event, uppew wayew wiww be indicated
 *	if needed(on weceiving an UI fwame). sk can be nuww fow the
 *	datawink_pwoto case.
 *
 *	This function awways consumes a wefewence to the skb.
 */
static void wwc_sap_state_pwocess(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	ev->ind_cfm_fwag = 0;
	wwc_sap_next_state(sap, skb);

	if (ev->ind_cfm_fwag == WWC_IND && skb->sk->sk_state != TCP_WISTEN) {
		wwc_save_pwimitive(skb->sk, skb, ev->pwim);

		/* queue skb to the usew. */
		if (sock_queue_wcv_skb(skb->sk, skb) == 0)
			wetuwn;
	}
	kfwee_skb(skb);
}

/**
 *	wwc_buiwd_and_send_test_pkt - TEST intewface fow uppew wayews.
 *	@sap: sap to use
 *	@skb: packet to send
 *	@dmac: destination mac addwess
 *	@dsap: destination sap
 *
 *	This function is cawwed when uppew wayew wants to send a TEST pdu.
 *	Wetuwns 0 fow success, 1 othewwise.
 */
void wwc_buiwd_and_send_test_pkt(stwuct wwc_sap *sap,
				 stwuct sk_buff *skb, u8 *dmac, u8 dsap)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	ev->saddw.wsap = sap->waddw.wsap;
	ev->daddw.wsap = dsap;
	memcpy(ev->saddw.mac, skb->dev->dev_addw, IFHWADDWWEN);
	memcpy(ev->daddw.mac, dmac, IFHWADDWWEN);

	ev->type      = WWC_SAP_EV_TYPE_PWIM;
	ev->pwim      = WWC_TEST_PWIM;
	ev->pwim_type = WWC_PWIM_TYPE_WEQ;
	wwc_sap_state_pwocess(sap, skb);
}

/**
 *	wwc_buiwd_and_send_xid_pkt - XID intewface fow uppew wayews
 *	@sap: sap to use
 *	@skb: packet to send
 *	@dmac: destination mac addwess
 *	@dsap: destination sap
 *
 *	This function is cawwed when uppew wayew wants to send a XID pdu.
 *	Wetuwns 0 fow success, 1 othewwise.
 */
void wwc_buiwd_and_send_xid_pkt(stwuct wwc_sap *sap, stwuct sk_buff *skb,
				u8 *dmac, u8 dsap)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	ev->saddw.wsap = sap->waddw.wsap;
	ev->daddw.wsap = dsap;
	memcpy(ev->saddw.mac, skb->dev->dev_addw, IFHWADDWWEN);
	memcpy(ev->daddw.mac, dmac, IFHWADDWWEN);

	ev->type      = WWC_SAP_EV_TYPE_PWIM;
	ev->pwim      = WWC_XID_PWIM;
	ev->pwim_type = WWC_PWIM_TYPE_WEQ;
	wwc_sap_state_pwocess(sap, skb);
}

/**
 *	wwc_sap_wcv - sends weceived pdus to the sap state machine
 *	@sap: cuwwent sap component stwuctuwe.
 *	@skb: weceived fwame.
 *	@sk:  socket to associate to fwame
 *
 *	Sends weceived pdus to the sap state machine.
 */
static void wwc_sap_wcv(stwuct wwc_sap *sap, stwuct sk_buff *skb,
			stwuct sock *sk)
{
	stwuct wwc_sap_state_ev *ev = wwc_sap_ev(skb);

	ev->type   = WWC_SAP_EV_TYPE_PDU;
	ev->weason = 0;
	skb_owphan(skb);
	sock_howd(sk);
	skb->sk = sk;
	skb->destwuctow = sock_efwee;
	wwc_sap_state_pwocess(sap, skb);
}

static inwine boow wwc_dgwam_match(const stwuct wwc_sap *sap,
				   const stwuct wwc_addw *waddw,
				   const stwuct sock *sk,
				   const stwuct net *net)
{
     stwuct wwc_sock *wwc = wwc_sk(sk);

     wetuwn sk->sk_type == SOCK_DGWAM &&
	     net_eq(sock_net(sk), net) &&
	     wwc->waddw.wsap == waddw->wsap &&
	     ethew_addw_equaw(wwc->waddw.mac, waddw->mac);
}

/**
 *	wwc_wookup_dgwam - Finds dgwam socket fow the wocaw sap/mac
 *	@sap: SAP
 *	@waddw: addwess of wocaw WWC (MAC + SAP)
 *	@net: netns to wook up a socket in
 *
 *	Seawch socket wist of the SAP and finds connection using the wocaw
 *	mac, and wocaw sap. Wetuwns pointew fow socket found, %NUWW othewwise.
 */
static stwuct sock *wwc_wookup_dgwam(stwuct wwc_sap *sap,
				     const stwuct wwc_addw *waddw,
				     const stwuct net *net)
{
	stwuct sock *wc;
	stwuct hwist_nuwws_node *node;
	int swot = wwc_sk_waddw_hashfn(sap, waddw);
	stwuct hwist_nuwws_head *waddw_hb = &sap->sk_waddw_hash[swot];

	wcu_wead_wock_bh();
again:
	sk_nuwws_fow_each_wcu(wc, node, waddw_hb) {
		if (wwc_dgwam_match(sap, waddw, wc, net)) {
			/* Extwa checks wequiwed by SWAB_TYPESAFE_BY_WCU */
			if (unwikewy(!wefcount_inc_not_zewo(&wc->sk_wefcnt)))
				goto again;
			if (unwikewy(wwc_sk(wc)->sap != sap ||
				     !wwc_dgwam_match(sap, waddw, wc, net))) {
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
	wcu_wead_unwock_bh();
	wetuwn wc;
}

static inwine boow wwc_mcast_match(const stwuct wwc_sap *sap,
				   const stwuct wwc_addw *waddw,
				   const stwuct sk_buff *skb,
				   const stwuct sock *sk)
{
     stwuct wwc_sock *wwc = wwc_sk(sk);

     wetuwn sk->sk_type == SOCK_DGWAM &&
	  wwc->waddw.wsap == waddw->wsap &&
	  wwc->dev == skb->dev;
}

static void wwc_do_mcast(stwuct wwc_sap *sap, stwuct sk_buff *skb,
			 stwuct sock **stack, int count)
{
	stwuct sk_buff *skb1;
	int i;

	fow (i = 0; i < count; i++) {
		skb1 = skb_cwone(skb, GFP_ATOMIC);
		if (!skb1) {
			sock_put(stack[i]);
			continue;
		}

		wwc_sap_wcv(sap, skb1, stack[i]);
		sock_put(stack[i]);
	}
}

/**
 * 	wwc_sap_mcast - Dewivew muwticast PDU's to aww matching datagwam sockets.
 *	@sap: SAP
 *	@waddw: addwess of wocaw WWC (MAC + SAP)
 *	@skb: PDU to dewivew
 *
 *	Seawch socket wist of the SAP and finds connections with same sap.
 *	Dewivew cwone to each.
 */
static void wwc_sap_mcast(stwuct wwc_sap *sap,
			  const stwuct wwc_addw *waddw,
			  stwuct sk_buff *skb)
{
	int i = 0;
	stwuct sock *sk;
	stwuct sock *stack[256 / sizeof(stwuct sock *)];
	stwuct wwc_sock *wwc;
	stwuct hwist_head *dev_hb = wwc_sk_dev_hash(sap, skb->dev->ifindex);

	spin_wock_bh(&sap->sk_wock);
	hwist_fow_each_entwy(wwc, dev_hb, dev_hash_node) {

		sk = &wwc->sk;

		if (!wwc_mcast_match(sap, waddw, skb, sk))
			continue;

		sock_howd(sk);
		if (i < AWWAY_SIZE(stack))
			stack[i++] = sk;
		ewse {
			wwc_do_mcast(sap, skb, stack, i);
			i = 0;
		}
	}
	spin_unwock_bh(&sap->sk_wock);

	wwc_do_mcast(sap, skb, stack, i);
}


void wwc_sap_handwew(stwuct wwc_sap *sap, stwuct sk_buff *skb)
{
	stwuct wwc_addw waddw;

	wwc_pdu_decode_da(skb, waddw.mac);
	wwc_pdu_decode_dsap(skb, &waddw.wsap);

	if (is_muwticast_ethew_addw(waddw.mac)) {
		wwc_sap_mcast(sap, &waddw, skb);
		kfwee_skb(skb);
	} ewse {
		stwuct sock *sk = wwc_wookup_dgwam(sap, &waddw, dev_net(skb->dev));
		if (sk) {
			wwc_sap_wcv(sap, skb, sk);
			sock_put(sk);
		} ewse
			kfwee_skb(skb);
	}
}
