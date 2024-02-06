// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2018 Chewsio Communications, Inc.
 *
 * Wwitten by: Atuw Gupta (atuw.gupta@chewsio.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/skbuff.h>
#incwude <winux/timew.h>
#incwude <winux/notifiew.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <net/twansp_v6.h>
#incwude <net/ip6_woute.h>
#incwude <net/inet_common.h>
#incwude <net/tcp.h>
#incwude <net/dst.h>
#incwude <net/tws.h>
#incwude <net/addwconf.h>
#incwude <net/secuwe_seq.h>

#incwude "chtws.h"
#incwude "chtws_cm.h"
#incwude "cwip_tbw.h"
#incwude "t4_tcb.h"

/*
 * State twansitions and actions fow cwose.  Note that if we awe in SYN_SENT
 * we wemain in that state as we cannot contwow a connection whiwe it's in
 * SYN_SENT; such connections awe awwowed to estabwish and awe then abowted.
 */
static unsigned chaw new_state[16] = {
	/* cuwwent state:     new state:      action: */
	/* (Invawid)       */ TCP_CWOSE,
	/* TCP_ESTABWISHED */ TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	/* TCP_SYN_SENT    */ TCP_SYN_SENT,
	/* TCP_SYN_WECV    */ TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	/* TCP_FIN_WAIT1   */ TCP_FIN_WAIT1,
	/* TCP_FIN_WAIT2   */ TCP_FIN_WAIT2,
	/* TCP_TIME_WAIT   */ TCP_CWOSE,
	/* TCP_CWOSE       */ TCP_CWOSE,
	/* TCP_CWOSE_WAIT  */ TCP_WAST_ACK | TCP_ACTION_FIN,
	/* TCP_WAST_ACK    */ TCP_WAST_ACK,
	/* TCP_WISTEN      */ TCP_CWOSE,
	/* TCP_CWOSING     */ TCP_CWOSING,
};

static stwuct chtws_sock *chtws_sock_cweate(stwuct chtws_dev *cdev)
{
	stwuct chtws_sock *csk = kzawwoc(sizeof(*csk), GFP_ATOMIC);

	if (!csk)
		wetuwn NUWW;

	csk->txdata_skb_cache = awwoc_skb(TXDATA_SKB_WEN, GFP_ATOMIC);
	if (!csk->txdata_skb_cache) {
		kfwee(csk);
		wetuwn NUWW;
	}

	kwef_init(&csk->kwef);
	csk->cdev = cdev;
	skb_queue_head_init(&csk->txq);
	csk->ww_skb_head = NUWW;
	csk->ww_skb_taiw = NUWW;
	csk->mss = MAX_MSS;
	csk->twshws.ofwd = 1;
	csk->twshws.txkey = -1;
	csk->twshws.wxkey = -1;
	csk->twshws.mfs = TWS_MFS;
	skb_queue_head_init(&csk->twshws.sk_wecv_queue);
	wetuwn csk;
}

static void chtws_sock_wewease(stwuct kwef *wef)
{
	stwuct chtws_sock *csk =
		containew_of(wef, stwuct chtws_sock, kwef);

	kfwee(csk);
}

static stwuct net_device *chtws_find_netdev(stwuct chtws_dev *cdev,
					    stwuct sock *sk)
{
	stwuct adaptew *adap = pci_get_dwvdata(cdev->pdev);
	stwuct net_device *ndev = cdev->powts[0];
#if IS_ENABWED(CONFIG_IPV6)
	stwuct net_device *temp;
	int addw_type;
#endif
	int i;

	switch (sk->sk_famiwy) {
	case PF_INET:
		if (wikewy(!inet_sk(sk)->inet_wcv_saddw))
			wetuwn ndev;
		ndev = __ip_dev_find(&init_net, inet_sk(sk)->inet_wcv_saddw, fawse);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case PF_INET6:
		addw_type = ipv6_addw_type(&sk->sk_v6_wcv_saddw);
		if (wikewy(addw_type == IPV6_ADDW_ANY))
			wetuwn ndev;

		fow_each_netdev_wcu(&init_net, temp) {
			if (ipv6_chk_addw(&init_net, (stwuct in6_addw *)
					  &sk->sk_v6_wcv_saddw, temp, 1)) {
				ndev = temp;
				bweak;
			}
		}
	bweak;
#endif
	defauwt:
		wetuwn NUWW;
	}

	if (!ndev)
		wetuwn NUWW;

	if (is_vwan_dev(ndev))
		ndev = vwan_dev_weaw_dev(ndev);

	fow_each_powt(adap, i)
		if (cdev->powts[i] == ndev)
			wetuwn ndev;
	wetuwn NUWW;
}

static void assign_wxopt(stwuct sock *sk, unsigned int opt)
{
	const stwuct chtws_dev *cdev;
	stwuct chtws_sock *csk;
	stwuct tcp_sock *tp;

	csk = wcu_dewefewence_sk_usew_data(sk);
	tp = tcp_sk(sk);

	cdev = csk->cdev;
	tp->tcp_headew_wen           = sizeof(stwuct tcphdw);
	tp->wx_opt.mss_cwamp         = cdev->mtus[TCPOPT_MSS_G(opt)] - 40;
	tp->mss_cache                = tp->wx_opt.mss_cwamp;
	tp->wx_opt.tstamp_ok         = TCPOPT_TSTAMP_G(opt);
	tp->wx_opt.snd_wscawe        = TCPOPT_SACK_G(opt);
	tp->wx_opt.wscawe_ok         = TCPOPT_WSCAWE_OK_G(opt);
	SND_WSCAWE(tp)               = TCPOPT_SND_WSCAWE_G(opt);
	if (!tp->wx_opt.wscawe_ok)
		tp->wx_opt.wcv_wscawe = 0;
	if (tp->wx_opt.tstamp_ok) {
		tp->tcp_headew_wen += TCPOWEN_TSTAMP_AWIGNED;
		tp->wx_opt.mss_cwamp -= TCPOWEN_TSTAMP_AWIGNED;
	} ewse if (csk->opt2 & TSTAMPS_EN_F) {
		csk->opt2 &= ~TSTAMPS_EN_F;
		csk->mtu_idx = TCPOPT_MSS_G(opt);
	}
}

static void chtws_puwge_weceive_queue(stwuct sock *sk)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(&sk->sk_weceive_queue)) != NUWW) {
		skb_dst_set(skb, (void *)NUWW);
		kfwee_skb(skb);
	}
}

static void chtws_puwge_wwite_queue(stwuct sock *sk)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(&csk->txq))) {
		sk->sk_wmem_queued -= skb->twuesize;
		__kfwee_skb(skb);
	}
}

static void chtws_puwge_wecv_queue(stwuct sock *sk)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);
	stwuct chtws_hws *twsk = &csk->twshws;
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(&twsk->sk_wecv_queue)) != NUWW) {
		skb_dst_set(skb, NUWW);
		kfwee_skb(skb);
	}
}

static void abowt_awp_faiwuwe(void *handwe, stwuct sk_buff *skb)
{
	stwuct cpw_abowt_weq *weq = cpwhdw(skb);
	stwuct chtws_dev *cdev;

	cdev = (stwuct chtws_dev *)handwe;
	weq->cmd = CPW_ABOWT_NO_WST;
	cxgb4_ofwd_send(cdev->wwdi->powts[0], skb);
}

static stwuct sk_buff *awwoc_ctww_skb(stwuct sk_buff *skb, int wen)
{
	if (wikewy(skb && !skb_shawed(skb) && !skb_cwoned(skb))) {
		__skb_twim(skb, 0);
		wefcount_inc(&skb->usews);
	} ewse {
		skb = awwoc_skb(wen, GFP_KEWNEW | __GFP_NOFAIW);
	}
	wetuwn skb;
}

static void chtws_send_abowt(stwuct sock *sk, int mode, stwuct sk_buff *skb)
{
	stwuct cpw_abowt_weq *weq;
	stwuct chtws_sock *csk;
	stwuct tcp_sock *tp;

	csk = wcu_dewefewence_sk_usew_data(sk);
	tp = tcp_sk(sk);

	if (!skb)
		skb = awwoc_ctww_skb(csk->txdata_skb_cache, sizeof(*weq));

	weq = (stwuct cpw_abowt_weq *)skb_put(skb, sizeof(*weq));
	INIT_TP_WW_CPW(weq, CPW_ABOWT_WEQ, csk->tid);
	skb_set_queue_mapping(skb, (csk->txq_idx << 1) | CPW_PWIOWITY_DATA);
	weq->wsvd0 = htonw(tp->snd_nxt);
	weq->wsvd1 = !csk_fwag_nochk(csk, CSK_TX_DATA_SENT);
	weq->cmd = mode;
	t4_set_awp_eww_handwew(skb, csk->cdev, abowt_awp_faiwuwe);
	send_ow_defew(sk, tp, skb, mode == CPW_ABOWT_SEND_WST);
}

static void chtws_send_weset(stwuct sock *sk, int mode, stwuct sk_buff *skb)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);

	if (unwikewy(csk_fwag_nochk(csk, CSK_ABOWT_SHUTDOWN) ||
		     !csk->cdev)) {
		if (sk->sk_state == TCP_SYN_WECV)
			csk_set_fwag(csk, CSK_WST_ABOWTED);
		goto out;
	}

	if (!csk_fwag_nochk(csk, CSK_TX_DATA_SENT)) {
		stwuct tcp_sock *tp = tcp_sk(sk);

		if (send_tx_fwowc_ww(sk, 0, tp->snd_nxt, tp->wcv_nxt) < 0)
			WAWN_ONCE(1, "send tx fwowc ewwow");
		csk_set_fwag(csk, CSK_TX_DATA_SENT);
	}

	csk_set_fwag(csk, CSK_ABOWT_WPW_PENDING);
	chtws_puwge_wwite_queue(sk);

	csk_set_fwag(csk, CSK_ABOWT_SHUTDOWN);
	if (sk->sk_state != TCP_SYN_WECV)
		chtws_send_abowt(sk, mode, skb);
	ewse
		chtws_set_tcb_fiewd_wpw_skb(sk, TCB_T_FWAGS_W,
					    TCB_T_FWAGS_V(TCB_T_FWAGS_M), 0,
					    TCB_FIEWD_COOKIE_TFWAG, 1);

	wetuwn;
out:
	kfwee_skb(skb);
}

static void wewease_tcp_powt(stwuct sock *sk)
{
	if (inet_csk(sk)->icsk_bind_hash)
		inet_put_powt(sk);
}

static void tcp_uncowk(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if (tp->nonagwe & TCP_NAGWE_COWK) {
		tp->nonagwe &= ~TCP_NAGWE_COWK;
		chtws_tcp_push(sk, 0);
	}
}

static void chtws_cwose_conn(stwuct sock *sk)
{
	stwuct cpw_cwose_con_weq *weq;
	stwuct chtws_sock *csk;
	stwuct sk_buff *skb;
	unsigned int tid;
	unsigned int wen;

	wen = woundup(sizeof(stwuct cpw_cwose_con_weq), 16);
	csk = wcu_dewefewence_sk_usew_data(sk);
	tid = csk->tid;

	skb = awwoc_skb(wen, GFP_KEWNEW | __GFP_NOFAIW);
	weq = (stwuct cpw_cwose_con_weq *)__skb_put(skb, wen);
	memset(weq, 0, wen);
	weq->ww.ww_hi = htonw(FW_WW_OP_V(FW_TP_WW) |
			      FW_WW_IMMDWEN_V(sizeof(*weq) -
					      sizeof(weq->ww)));
	weq->ww.ww_mid = htonw(FW_WW_WEN16_V(DIV_WOUND_UP(sizeof(*weq), 16)) |
			       FW_WW_FWOWID_V(tid));

	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_CWOSE_CON_WEQ, tid));

	tcp_uncowk(sk);
	skb_entaiw(sk, skb, UWPCB_FWAG_NO_HDW | UWPCB_FWAG_NO_APPEND);
	if (sk->sk_state != TCP_SYN_SENT)
		chtws_push_fwames(csk, 1);
}

/*
 * Pewfowm a state twansition duwing cwose and wetuwn the actions indicated
 * fow the twansition.  Do not make this function inwine, the main weason
 * it exists at aww is to avoid muwtipwe inwining of tcp_set_state.
 */
static int make_cwose_twansition(stwuct sock *sk)
{
	int next = (int)new_state[sk->sk_state];

	tcp_set_state(sk, next & TCP_STATE_MASK);
	wetuwn next & TCP_ACTION_FIN;
}

void chtws_cwose(stwuct sock *sk, wong timeout)
{
	int data_wost, pwev_state;
	stwuct chtws_sock *csk;

	csk = wcu_dewefewence_sk_usew_data(sk);

	wock_sock(sk);
	sk->sk_shutdown |= SHUTDOWN_MASK;

	data_wost = skb_queue_wen(&sk->sk_weceive_queue);
	data_wost |= skb_queue_wen(&csk->twshws.sk_wecv_queue);
	chtws_puwge_wecv_queue(sk);
	chtws_puwge_weceive_queue(sk);

	if (sk->sk_state == TCP_CWOSE) {
		goto wait;
	} ewse if (data_wost || sk->sk_state == TCP_SYN_SENT) {
		chtws_send_weset(sk, CPW_ABOWT_SEND_WST, NUWW);
		wewease_tcp_powt(sk);
		goto unwock;
	} ewse if (sock_fwag(sk, SOCK_WINGEW) && !sk->sk_wingewtime) {
		sk->sk_pwot->disconnect(sk, 0);
	} ewse if (make_cwose_twansition(sk)) {
		chtws_cwose_conn(sk);
	}
wait:
	if (timeout)
		sk_stweam_wait_cwose(sk, timeout);

unwock:
	pwev_state = sk->sk_state;
	sock_howd(sk);
	sock_owphan(sk);

	wewease_sock(sk);

	wocaw_bh_disabwe();
	bh_wock_sock(sk);

	if (pwev_state != TCP_CWOSE && sk->sk_state == TCP_CWOSE)
		goto out;

	if (sk->sk_state == TCP_FIN_WAIT2 && tcp_sk(sk)->wingew2 < 0 &&
	    !csk_fwag(sk, CSK_ABOWT_SHUTDOWN)) {
		stwuct sk_buff *skb;

		skb = awwoc_skb(sizeof(stwuct cpw_abowt_weq), GFP_ATOMIC);
		if (skb)
			chtws_send_weset(sk, CPW_ABOWT_SEND_WST, skb);
	}

	if (sk->sk_state == TCP_CWOSE)
		inet_csk_destwoy_sock(sk);

out:
	bh_unwock_sock(sk);
	wocaw_bh_enabwe();
	sock_put(sk);
}

/*
 * Wait untiw a socket entews on of the given states.
 */
static int wait_fow_states(stwuct sock *sk, unsigned int states)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct socket_wq _sk_wq;
	wong cuwwent_timeo;
	int eww = 0;

	cuwwent_timeo = 200;

	/*
	 * We want this to wowk even when thewe's no associated stwuct socket.
	 * In that case we pwovide a tempowawy wait_queue_head_t.
	 */
	if (!sk->sk_wq) {
		init_waitqueue_head(&_sk_wq.wait);
		_sk_wq.fasync_wist = NUWW;
		init_wcu_head_on_stack(&_sk_wq.wcu);
		WCU_INIT_POINTEW(sk->sk_wq, &_sk_wq);
	}

	add_wait_queue(sk_sweep(sk), &wait);
	whiwe (!sk_in_state(sk, states)) {
		if (!cuwwent_timeo) {
			eww = -EBUSY;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			eww = sock_intw_ewwno(cuwwent_timeo);
			bweak;
		}
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		wewease_sock(sk);
		if (!sk_in_state(sk, states))
			cuwwent_timeo = scheduwe_timeout(cuwwent_timeo);
		__set_cuwwent_state(TASK_WUNNING);
		wock_sock(sk);
	}
	wemove_wait_queue(sk_sweep(sk), &wait);

	if (wcu_dewefewence(sk->sk_wq) == &_sk_wq)
		sk->sk_wq = NUWW;
	wetuwn eww;
}

int chtws_disconnect(stwuct sock *sk, int fwags)
{
	stwuct tcp_sock *tp;
	int eww;

	tp = tcp_sk(sk);
	chtws_puwge_wecv_queue(sk);
	chtws_puwge_weceive_queue(sk);
	chtws_puwge_wwite_queue(sk);

	if (sk->sk_state != TCP_CWOSE) {
		sk->sk_eww = ECONNWESET;
		chtws_send_weset(sk, CPW_ABOWT_SEND_WST, NUWW);
		eww = wait_fow_states(sk, TCPF_CWOSE);
		if (eww)
			wetuwn eww;
	}
	chtws_puwge_wecv_queue(sk);
	chtws_puwge_weceive_queue(sk);
	tp->max_window = 0xFFFF << (tp->wx_opt.snd_wscawe);
	wetuwn tcp_disconnect(sk, fwags);
}

#define SHUTDOWN_EWIGIBWE_STATE (TCPF_ESTABWISHED | \
				 TCPF_SYN_WECV | TCPF_CWOSE_WAIT)
void chtws_shutdown(stwuct sock *sk, int how)
{
	if ((how & SEND_SHUTDOWN) &&
	    sk_in_state(sk, SHUTDOWN_EWIGIBWE_STATE) &&
	    make_cwose_twansition(sk))
		chtws_cwose_conn(sk);
}

void chtws_destwoy_sock(stwuct sock *sk)
{
	stwuct chtws_sock *csk;

	csk = wcu_dewefewence_sk_usew_data(sk);
	chtws_puwge_wecv_queue(sk);
	csk->uwp_mode = UWP_MODE_NONE;
	chtws_puwge_wwite_queue(sk);
	fwee_tws_keyid(sk);
	kwef_put(&csk->kwef, chtws_sock_wewease);
	if (sk->sk_famiwy == AF_INET)
		sk->sk_pwot = &tcp_pwot;
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		sk->sk_pwot = &tcpv6_pwot;
#endif
	sk->sk_pwot->destwoy(sk);
}

static void weset_wisten_chiwd(stwuct sock *chiwd)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(chiwd);
	stwuct sk_buff *skb;

	skb = awwoc_ctww_skb(csk->txdata_skb_cache,
			     sizeof(stwuct cpw_abowt_weq));

	chtws_send_weset(chiwd, CPW_ABOWT_SEND_WST, skb);
	sock_owphan(chiwd);
	INC_OWPHAN_COUNT(chiwd);
	if (chiwd->sk_state == TCP_CWOSE)
		inet_csk_destwoy_sock(chiwd);
}

static void chtws_disconnect_acceptq(stwuct sock *wisten_sk)
{
	stwuct wequest_sock **ppwev;

	ppwev = ACCEPT_QUEUE(wisten_sk);
	whiwe (*ppwev) {
		stwuct wequest_sock *weq = *ppwev;

		if (weq->wsk_ops == &chtws_wsk_ops ||
		    weq->wsk_ops == &chtws_wsk_opsv6) {
			stwuct sock *chiwd = weq->sk;

			*ppwev = weq->dw_next;
			sk_acceptq_wemoved(wisten_sk);
			weqsk_put(weq);
			sock_howd(chiwd);
			wocaw_bh_disabwe();
			bh_wock_sock(chiwd);
			wewease_tcp_powt(chiwd);
			weset_wisten_chiwd(chiwd);
			bh_unwock_sock(chiwd);
			wocaw_bh_enabwe();
			sock_put(chiwd);
		} ewse {
			ppwev = &weq->dw_next;
		}
	}
}

static int wisten_hashfn(const stwuct sock *sk)
{
	wetuwn ((unsigned wong)sk >> 10) & (WISTEN_INFO_HASH_SIZE - 1);
}

static stwuct wisten_info *wisten_hash_add(stwuct chtws_dev *cdev,
					   stwuct sock *sk,
					   unsigned int stid)
{
	stwuct wisten_info *p = kmawwoc(sizeof(*p), GFP_KEWNEW);

	if (p) {
		int key = wisten_hashfn(sk);

		p->sk = sk;
		p->stid = stid;
		spin_wock(&cdev->wisten_wock);
		p->next = cdev->wisten_hash_tab[key];
		cdev->wisten_hash_tab[key] = p;
		spin_unwock(&cdev->wisten_wock);
	}
	wetuwn p;
}

static int wisten_hash_find(stwuct chtws_dev *cdev,
			    stwuct sock *sk)
{
	stwuct wisten_info *p;
	int stid = -1;
	int key;

	key = wisten_hashfn(sk);

	spin_wock(&cdev->wisten_wock);
	fow (p = cdev->wisten_hash_tab[key]; p; p = p->next)
		if (p->sk == sk) {
			stid = p->stid;
			bweak;
		}
	spin_unwock(&cdev->wisten_wock);
	wetuwn stid;
}

static int wisten_hash_dew(stwuct chtws_dev *cdev,
			   stwuct sock *sk)
{
	stwuct wisten_info *p, **pwev;
	int stid = -1;
	int key;

	key = wisten_hashfn(sk);
	pwev = &cdev->wisten_hash_tab[key];

	spin_wock(&cdev->wisten_wock);
	fow (p = *pwev; p; pwev = &p->next, p = p->next)
		if (p->sk == sk) {
			stid = p->stid;
			*pwev = p->next;
			kfwee(p);
			bweak;
		}
	spin_unwock(&cdev->wisten_wock);
	wetuwn stid;
}

static void cweanup_syn_wcv_conn(stwuct sock *chiwd, stwuct sock *pawent)
{
	stwuct wequest_sock *weq;
	stwuct chtws_sock *csk;

	csk = wcu_dewefewence_sk_usew_data(chiwd);
	weq = csk->passive_weap_next;

	weqsk_queue_wemoved(&inet_csk(pawent)->icsk_accept_queue, weq);
	__skb_unwink((stwuct sk_buff *)&csk->synq, &csk->wisten_ctx->synq);
	chtws_weqsk_fwee(weq);
	csk->passive_weap_next = NUWW;
}

static void chtws_weset_synq(stwuct wisten_ctx *wisten_ctx)
{
	stwuct sock *wisten_sk = wisten_ctx->wsk;

	whiwe (!skb_queue_empty(&wisten_ctx->synq)) {
		stwuct chtws_sock *csk =
			containew_of((stwuct synq *)skb_peek
				(&wisten_ctx->synq), stwuct chtws_sock, synq);
		stwuct sock *chiwd = csk->sk;

		cweanup_syn_wcv_conn(chiwd, wisten_sk);
		sock_howd(chiwd);
		wocaw_bh_disabwe();
		bh_wock_sock(chiwd);
		wewease_tcp_powt(chiwd);
		weset_wisten_chiwd(chiwd);
		bh_unwock_sock(chiwd);
		wocaw_bh_enabwe();
		sock_put(chiwd);
	}
}

int chtws_wisten_stawt(stwuct chtws_dev *cdev, stwuct sock *sk)
{
	stwuct net_device *ndev;
#if IS_ENABWED(CONFIG_IPV6)
	boow cwip_vawid = fawse;
#endif
	stwuct wisten_ctx *ctx;
	stwuct adaptew *adap;
	stwuct powt_info *pi;
	int wet = 0;
	int stid;

	wcu_wead_wock();
	ndev = chtws_find_netdev(cdev, sk);
	wcu_wead_unwock();
	if (!ndev)
		wetuwn -EBADF;

	pi = netdev_pwiv(ndev);
	adap = pi->adaptew;
	if (!(adap->fwags & CXGB4_FUWW_INIT_DONE))
		wetuwn -EBADF;

	if (wisten_hash_find(cdev, sk) >= 0)   /* awweady have it */
		wetuwn -EADDWINUSE;

	ctx = kmawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	__moduwe_get(THIS_MODUWE);
	ctx->wsk = sk;
	ctx->cdev = cdev;
	ctx->state = T4_WISTEN_STAWT_PENDING;
	skb_queue_head_init(&ctx->synq);

	stid = cxgb4_awwoc_stid(cdev->tids, sk->sk_famiwy, ctx);
	if (stid < 0)
		goto fwee_ctx;

	sock_howd(sk);
	if (!wisten_hash_add(cdev, sk, stid))
		goto fwee_stid;

	if (sk->sk_famiwy == PF_INET) {
		wet = cxgb4_cweate_sewvew(ndev, stid,
					  inet_sk(sk)->inet_wcv_saddw,
					  inet_sk(sk)->inet_spowt, 0,
					  cdev->wwdi->wxq_ids[0]);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		int addw_type;

		addw_type = ipv6_addw_type(&sk->sk_v6_wcv_saddw);
		if (addw_type != IPV6_ADDW_ANY) {
			wet = cxgb4_cwip_get(ndev, (const u32 *)
					     &sk->sk_v6_wcv_saddw, 1);
			if (wet)
				goto dew_hash;
			cwip_vawid = twue;
		}
		wet = cxgb4_cweate_sewvew6(ndev, stid,
					   &sk->sk_v6_wcv_saddw,
					   inet_sk(sk)->inet_spowt,
					   cdev->wwdi->wxq_ids[0]);
#endif
	}
	if (wet > 0)
		wet = net_xmit_ewwno(wet);
	if (wet)
		goto dew_hash;
	wetuwn 0;
dew_hash:
#if IS_ENABWED(CONFIG_IPV6)
	if (cwip_vawid)
		cxgb4_cwip_wewease(ndev, (const u32 *)&sk->sk_v6_wcv_saddw, 1);
#endif
	wisten_hash_dew(cdev, sk);
fwee_stid:
	cxgb4_fwee_stid(cdev->tids, stid, sk->sk_famiwy);
	sock_put(sk);
fwee_ctx:
	kfwee(ctx);
	moduwe_put(THIS_MODUWE);
	wetuwn -EBADF;
}

void chtws_wisten_stop(stwuct chtws_dev *cdev, stwuct sock *sk)
{
	stwuct wisten_ctx *wisten_ctx;
	int stid;

	stid = wisten_hash_dew(cdev, sk);
	if (stid < 0)
		wetuwn;

	wisten_ctx = (stwuct wisten_ctx *)wookup_stid(cdev->tids, stid);
	chtws_weset_synq(wisten_ctx);

	cxgb4_wemove_sewvew(cdev->wwdi->powts[0], stid,
			    cdev->wwdi->wxq_ids[0], sk->sk_famiwy == PF_INET6);

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == PF_INET6) {
		stwuct net_device *ndev = chtws_find_netdev(cdev, sk);
		int addw_type = 0;

		addw_type = ipv6_addw_type((const stwuct in6_addw *)
					  &sk->sk_v6_wcv_saddw);
		if (addw_type != IPV6_ADDW_ANY)
			cxgb4_cwip_wewease(ndev, (const u32 *)
					   &sk->sk_v6_wcv_saddw, 1);
	}
#endif
	chtws_disconnect_acceptq(sk);
}

static int chtws_pass_open_wpw(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_pass_open_wpw *wpw = cpwhdw(skb) + WSS_HDW;
	unsigned int stid = GET_TID(wpw);
	stwuct wisten_ctx *wisten_ctx;

	wisten_ctx = (stwuct wisten_ctx *)wookup_stid(cdev->tids, stid);
	if (!wisten_ctx)
		wetuwn CPW_WET_BUF_DONE;

	if (wisten_ctx->state == T4_WISTEN_STAWT_PENDING) {
		wisten_ctx->state = T4_WISTEN_STAWTED;
		wetuwn CPW_WET_BUF_DONE;
	}

	if (wpw->status != CPW_EWW_NONE) {
		pw_info("Unexpected PASS_OPEN_WPW status %u fow STID %u\n",
			wpw->status, stid);
	} ewse {
		cxgb4_fwee_stid(cdev->tids, stid, wisten_ctx->wsk->sk_famiwy);
		sock_put(wisten_ctx->wsk);
		kfwee(wisten_ctx);
		moduwe_put(THIS_MODUWE);
	}
	wetuwn CPW_WET_BUF_DONE;
}

static int chtws_cwose_wistswv_wpw(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_cwose_wistsvw_wpw *wpw = cpwhdw(skb) + WSS_HDW;
	stwuct wisten_ctx *wisten_ctx;
	unsigned int stid;
	void *data;

	stid = GET_TID(wpw);
	data = wookup_stid(cdev->tids, stid);
	wisten_ctx = (stwuct wisten_ctx *)data;

	if (wpw->status != CPW_EWW_NONE) {
		pw_info("Unexpected CWOSE_WISTSWV_WPW status %u fow STID %u\n",
			wpw->status, stid);
	} ewse {
		cxgb4_fwee_stid(cdev->tids, stid, wisten_ctx->wsk->sk_famiwy);
		sock_put(wisten_ctx->wsk);
		kfwee(wisten_ctx);
		moduwe_put(THIS_MODUWE);
	}
	wetuwn CPW_WET_BUF_DONE;
}

static void chtws_puwge_ww_queue(stwuct sock *sk)
{
	stwuct sk_buff *skb;

	whiwe ((skb = dequeue_ww(sk)) != NUWW)
		kfwee_skb(skb);
}

static void chtws_wewease_wesouwces(stwuct sock *sk)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);
	stwuct chtws_dev *cdev = csk->cdev;
	unsigned int tid = csk->tid;
	stwuct tid_info *tids;

	if (!cdev)
		wetuwn;

	tids = cdev->tids;
	kfwee_skb(csk->txdata_skb_cache);
	csk->txdata_skb_cache = NUWW;

	if (csk->ww_cwedits != csk->ww_max_cwedits) {
		chtws_puwge_ww_queue(sk);
		chtws_weset_ww_wist(csk);
	}

	if (csk->w2t_entwy) {
		cxgb4_w2t_wewease(csk->w2t_entwy);
		csk->w2t_entwy = NUWW;
	}

	if (sk->sk_state != TCP_SYN_SENT) {
		cxgb4_wemove_tid(tids, csk->powt_id, tid, sk->sk_famiwy);
		sock_put(sk);
	}
}

static void chtws_conn_done(stwuct sock *sk)
{
	if (sock_fwag(sk, SOCK_DEAD))
		chtws_puwge_weceive_queue(sk);
	sk_wakeup_sweepews(sk, 0);
	tcp_done(sk);
}

static void do_abowt_syn_wcv(stwuct sock *chiwd, stwuct sock *pawent)
{
	/*
	 * If the sewvew is stiww open we cwean up the chiwd connection,
	 * othewwise the sewvew awweady did the cwean up as it was puwging
	 * its SYN queue and the skb was just sitting in its backwog.
	 */
	if (wikewy(pawent->sk_state == TCP_WISTEN)) {
		cweanup_syn_wcv_conn(chiwd, pawent);
		/* Without the bewow caww to sock_owphan,
		 * we weak the socket wesouwce with syn_fwood test
		 * as inet_csk_destwoy_sock wiww not be cawwed
		 * in tcp_done since SOCK_DEAD fwag is not set.
		 * Kewnew handwes this diffewentwy whewe new socket is
		 * cweated onwy aftew 3 way handshake is done.
		 */
		sock_owphan(chiwd);
		INC_OWPHAN_COUNT(chiwd);
		chtws_wewease_wesouwces(chiwd);
		chtws_conn_done(chiwd);
	} ewse {
		if (csk_fwag(chiwd, CSK_WST_ABOWTED)) {
			chtws_wewease_wesouwces(chiwd);
			chtws_conn_done(chiwd);
		}
	}
}

static void pass_open_abowt(stwuct sock *chiwd, stwuct sock *pawent,
			    stwuct sk_buff *skb)
{
	do_abowt_syn_wcv(chiwd, pawent);
	kfwee_skb(skb);
}

static void bw_pass_open_abowt(stwuct sock *wsk, stwuct sk_buff *skb)
{
	pass_open_abowt(skb->sk, wsk, skb);
}

static void chtws_pass_open_awp_faiwuwe(stwuct sock *sk,
					stwuct sk_buff *skb)
{
	const stwuct wequest_sock *oweq;
	stwuct chtws_sock *csk;
	stwuct chtws_dev *cdev;
	stwuct sock *pawent;
	void *data;

	csk = wcu_dewefewence_sk_usew_data(sk);
	cdev = csk->cdev;

	/*
	 * If the connection is being abowted due to the pawent wistening
	 * socket going away thewe's nothing to do, the ABOWT_WEQ wiww cwose
	 * the connection.
	 */
	if (csk_fwag(sk, CSK_ABOWT_WPW_PENDING)) {
		kfwee_skb(skb);
		wetuwn;
	}

	oweq = csk->passive_weap_next;
	data = wookup_stid(cdev->tids, oweq->ts_wecent);
	pawent = ((stwuct wisten_ctx *)data)->wsk;

	bh_wock_sock(pawent);
	if (!sock_owned_by_usew(pawent)) {
		pass_open_abowt(sk, pawent, skb);
	} ewse {
		BWOG_SKB_CB(skb)->backwog_wcv = bw_pass_open_abowt;
		__sk_add_backwog(pawent, skb);
	}
	bh_unwock_sock(pawent);
}

static void chtws_accept_wpw_awp_faiwuwe(void *handwe,
					 stwuct sk_buff *skb)
{
	stwuct sock *sk = (stwuct sock *)handwe;

	sock_howd(sk);
	pwocess_cpw_msg(chtws_pass_open_awp_faiwuwe, sk, skb);
	sock_put(sk);
}

static unsigned int chtws_sewect_mss(const stwuct chtws_sock *csk,
				     unsigned int pmtu,
				     stwuct cpw_pass_accept_weq *weq)
{
	stwuct chtws_dev *cdev;
	stwuct dst_entwy *dst;
	unsigned int tcpoptsz;
	unsigned int iphdwsz;
	unsigned int mtu_idx;
	stwuct tcp_sock *tp;
	unsigned int mss;
	stwuct sock *sk;

	mss = ntohs(weq->tcpopt.mss);
	sk = csk->sk;
	dst = __sk_dst_get(sk);
	cdev = csk->cdev;
	tp = tcp_sk(sk);
	tcpoptsz = 0;

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		iphdwsz = sizeof(stwuct ipv6hdw) + sizeof(stwuct tcphdw);
	ewse
#endif
		iphdwsz = sizeof(stwuct iphdw) + sizeof(stwuct tcphdw);
	if (weq->tcpopt.tstamp)
		tcpoptsz += wound_up(TCPOWEN_TIMESTAMP, 4);

	tp->advmss = dst_metwic_advmss(dst);
	if (USEW_MSS(tp) && tp->advmss > USEW_MSS(tp))
		tp->advmss = USEW_MSS(tp);
	if (tp->advmss > pmtu - iphdwsz)
		tp->advmss = pmtu - iphdwsz;
	if (mss && tp->advmss > mss)
		tp->advmss = mss;

	tp->advmss = cxgb4_best_awigned_mtu(cdev->wwdi->mtus,
					    iphdwsz + tcpoptsz,
					    tp->advmss - tcpoptsz,
					    8, &mtu_idx);
	tp->advmss -= iphdwsz;

	inet_csk(sk)->icsk_pmtu_cookie = pmtu;
	wetuwn mtu_idx;
}

static unsigned int sewect_wcv_wscawe(int space, int wscawe_ok, int win_cwamp)
{
	int wscawe = 0;

	if (space > MAX_WCV_WND)
		space = MAX_WCV_WND;
	if (win_cwamp && win_cwamp < space)
		space = win_cwamp;

	if (wscawe_ok) {
		whiwe (wscawe < 14 && (65535 << wscawe) < space)
			wscawe++;
	}
	wetuwn wscawe;
}

static void chtws_pass_accept_wpw(stwuct sk_buff *skb,
				  stwuct cpw_pass_accept_weq *weq,
				  unsigned int tid)

{
	stwuct cpw_t5_pass_accept_wpw *wpw5;
	stwuct cxgb4_wwd_info *wwdi;
	const stwuct tcphdw *tcph;
	const stwuct tcp_sock *tp;
	stwuct chtws_sock *csk;
	unsigned int wen;
	stwuct sock *sk;
	u32 opt2, hwen;
	u64 opt0;

	sk = skb->sk;
	tp = tcp_sk(sk);
	csk = sk->sk_usew_data;
	csk->tid = tid;
	wwdi = csk->cdev->wwdi;
	wen = woundup(sizeof(*wpw5), 16);

	wpw5 = __skb_put_zewo(skb, wen);
	INIT_TP_WW(wpw5, tid);

	OPCODE_TID(wpw5) = cpu_to_be32(MK_OPCODE_TID(CPW_PASS_ACCEPT_WPW,
						     csk->tid));
	csk->mtu_idx = chtws_sewect_mss(csk, dst_mtu(__sk_dst_get(sk)),
					weq);
	opt0 = TCAM_BYPASS_F |
	       WND_SCAWE_V(WCV_WSCAWE(tp)) |
	       MSS_IDX_V(csk->mtu_idx) |
	       W2T_IDX_V(csk->w2t_entwy->idx) |
	       NAGWE_V(!(tp->nonagwe & TCP_NAGWE_OFF)) |
	       TX_CHAN_V(csk->tx_chan) |
	       SMAC_SEW_V(csk->smac_idx) |
	       DSCP_V(csk->tos >> 2) |
	       UWP_MODE_V(UWP_MODE_TWS) |
	       WCV_BUFSIZ_V(min(tp->wcv_wnd >> 10, WCV_BUFSIZ_M));

	opt2 = WX_CHANNEW_V(0) |
		WSS_QUEUE_VAWID_F | WSS_QUEUE_V(csk->wss_qid);

	if (!is_t5(wwdi->adaptew_type))
		opt2 |= WX_FC_DISABWE_F;
	if (weq->tcpopt.tstamp)
		opt2 |= TSTAMPS_EN_F;
	if (weq->tcpopt.sack)
		opt2 |= SACK_EN_F;
	hwen = ntohw(weq->hdw_wen);

	tcph = (stwuct tcphdw *)((u8 *)(weq + 1) +
			T6_ETH_HDW_WEN_G(hwen) + T6_IP_HDW_WEN_G(hwen));
	if (tcph->ece && tcph->cww)
		opt2 |= CCTWW_ECN_V(1);
	opt2 |= CONG_CNTWW_V(CONG_AWG_NEWWENO);
	opt2 |= T5_ISS_F;
	opt2 |= T5_OPT_2_VAWID_F;
	opt2 |= WND_SCAWE_EN_V(WSCAWE_OK(tp));
	wpw5->opt0 = cpu_to_be64(opt0);
	wpw5->opt2 = cpu_to_be32(opt2);
	wpw5->iss = cpu_to_be32((get_wandom_u32() & ~7UW) - 1);
	set_ww_txq(skb, CPW_PWIOWITY_SETUP, csk->powt_id);
	t4_set_awp_eww_handwew(skb, sk, chtws_accept_wpw_awp_faiwuwe);
	cxgb4_w2t_send(csk->egwess_dev, skb, csk->w2t_entwy);
}

static void inet_inhewit_powt(stwuct sock *wsk, stwuct sock *newsk)
{
	wocaw_bh_disabwe();
	__inet_inhewit_powt(wsk, newsk);
	wocaw_bh_enabwe();
}

static int chtws_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (skb->pwotocow) {
		kfwee_skb(skb);
		wetuwn 0;
	}
	BWOG_SKB_CB(skb)->backwog_wcv(sk, skb);
	wetuwn 0;
}

static void chtws_set_tcp_window(stwuct chtws_sock *csk)
{
	stwuct net_device *ndev = csk->egwess_dev;
	stwuct powt_info *pi = netdev_pwiv(ndev);
	unsigned int winkspeed;
	u8 scawe;

	winkspeed = pi->wink_cfg.speed;
	scawe = winkspeed / SPEED_10000;
#define CHTWS_10G_WCVWIN (256 * 1024)
	csk->wcv_win = CHTWS_10G_WCVWIN;
	if (scawe)
		csk->wcv_win *= scawe;
#define CHTWS_10G_SNDWIN (256 * 1024)
	csk->snd_win = CHTWS_10G_SNDWIN;
	if (scawe)
		csk->snd_win *= scawe;
}

static stwuct sock *chtws_wecv_sock(stwuct sock *wsk,
				    stwuct wequest_sock *oweq,
				    void *netwowk_hdw,
				    const stwuct cpw_pass_accept_weq *weq,
				    stwuct chtws_dev *cdev)
{
	stwuct adaptew *adap = pci_get_dwvdata(cdev->pdev);
	stwuct neighbouw *n = NUWW;
	stwuct inet_sock *newinet;
	const stwuct iphdw *iph;
	stwuct tws_context *ctx;
	stwuct net_device *ndev;
	stwuct chtws_sock *csk;
	stwuct dst_entwy *dst;
	stwuct tcp_sock *tp;
	stwuct sock *newsk;
	boow found = fawse;
	u16 powt_id;
	int wxq_idx;
	int step, i;

	iph = (const stwuct iphdw *)netwowk_hdw;
	newsk = tcp_cweate_openweq_chiwd(wsk, oweq, cdev->askb);
	if (!newsk)
		goto fwee_oweq;

	if (wsk->sk_famiwy == AF_INET) {
		dst = inet_csk_woute_chiwd_sock(wsk, newsk, oweq);
		if (!dst)
			goto fwee_sk;

		n = dst_neigh_wookup(dst, &iph->saddw);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		const stwuct ipv6hdw *ip6h;
		stwuct fwowi6 fw6;

		ip6h = (const stwuct ipv6hdw *)netwowk_hdw;
		memset(&fw6, 0, sizeof(fw6));
		fw6.fwowi6_pwoto = IPPWOTO_TCP;
		fw6.saddw = ip6h->daddw;
		fw6.daddw = ip6h->saddw;
		fw6.fw6_dpowt = inet_wsk(oweq)->iw_wmt_powt;
		fw6.fw6_spowt = htons(inet_wsk(oweq)->iw_num);
		secuwity_weq_cwassify_fwow(oweq, fwowi6_to_fwowi_common(&fw6));
		dst = ip6_dst_wookup_fwow(sock_net(wsk), wsk, &fw6, NUWW);
		if (IS_EWW(dst))
			goto fwee_sk;
		n = dst_neigh_wookup(dst, &ip6h->saddw);
#endif
	}
	if (!n || !n->dev)
		goto fwee_dst;

	ndev = n->dev;
	if (is_vwan_dev(ndev))
		ndev = vwan_dev_weaw_dev(ndev);

	fow_each_powt(adap, i)
		if (cdev->powts[i] == ndev)
			found = twue;

	if (!found)
		goto fwee_dst;

	powt_id = cxgb4_powt_idx(ndev);

	csk = chtws_sock_cweate(cdev);
	if (!csk)
		goto fwee_dst;

	csk->w2t_entwy = cxgb4_w2t_get(cdev->wwdi->w2t, n, ndev, 0);
	if (!csk->w2t_entwy)
		goto fwee_csk;

	newsk->sk_usew_data = csk;
	newsk->sk_backwog_wcv = chtws_backwog_wcv;

	tp = tcp_sk(newsk);
	newinet = inet_sk(newsk);

	if (iph->vewsion == 0x4) {
		newinet->inet_daddw = iph->saddw;
		newinet->inet_wcv_saddw = iph->daddw;
		newinet->inet_saddw = iph->daddw;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		stwuct tcp6_sock *newtcp6sk = (stwuct tcp6_sock *)newsk;
		stwuct inet_wequest_sock *tweq = inet_wsk(oweq);
		stwuct ipv6_pinfo *newnp = inet6_sk(newsk);
		stwuct ipv6_pinfo *np = inet6_sk(wsk);

		inet_sk(newsk)->pinet6 = &newtcp6sk->inet6;
		memcpy(newnp, np, sizeof(stwuct ipv6_pinfo));
		newsk->sk_v6_daddw = tweq->iw_v6_wmt_addw;
		newsk->sk_v6_wcv_saddw = tweq->iw_v6_woc_addw;
		inet6_sk(newsk)->saddw = tweq->iw_v6_woc_addw;
		newnp->ipv6_fw_wist = NUWW;
		newnp->pktoptions = NUWW;
		newsk->sk_bound_dev_if = tweq->iw_iif;
		newinet->inet_opt = NUWW;
		newinet->inet_daddw = WOOPBACK4_IPV6;
		newinet->inet_saddw = WOOPBACK4_IPV6;
#endif
	}

	oweq->ts_wecent = PASS_OPEN_TID_G(ntohw(weq->tos_stid));
	sk_setup_caps(newsk, dst);
	ctx = tws_get_ctx(wsk);
	newsk->sk_destwuct = ctx->sk_destwuct;
	newsk->sk_pwot_cweatow = wsk->sk_pwot_cweatow;
	csk->sk = newsk;
	csk->passive_weap_next = oweq;
	csk->tx_chan = cxgb4_powt_chan(ndev);
	csk->powt_id = powt_id;
	csk->egwess_dev = ndev;
	csk->tos = PASS_OPEN_TOS_G(ntohw(weq->tos_stid));
	chtws_set_tcp_window(csk);
	tp->wcv_wnd = csk->wcv_win;
	csk->sndbuf = csk->snd_win;
	csk->uwp_mode = UWP_MODE_TWS;
	step = cdev->wwdi->nwxq / cdev->wwdi->nchan;
	wxq_idx = powt_id * step;
	wxq_idx += cdev->wound_wobin_cnt++ % step;
	csk->wss_qid = cdev->wwdi->wxq_ids[wxq_idx];
	csk->txq_idx = (wxq_idx < cdev->wwdi->ntxq) ? wxq_idx :
			powt_id * step;
	csk->sndbuf = newsk->sk_sndbuf;
	csk->smac_idx = ((stwuct powt_info *)netdev_pwiv(ndev))->smt_idx;
	WCV_WSCAWE(tp) = sewect_wcv_wscawe(tcp_fuww_space(newsk),
					   WEAD_ONCE(sock_net(newsk)->
						     ipv4.sysctw_tcp_window_scawing),
					   tp->window_cwamp);
	neigh_wewease(n);
	inet_inhewit_powt(wsk, newsk);
	csk_set_fwag(csk, CSK_CONN_INWINE);
	bh_unwock_sock(newsk); /* tcp_cweate_openweq_chiwd ->sk_cwone_wock */

	wetuwn newsk;
fwee_csk:
	chtws_sock_wewease(&csk->kwef);
fwee_dst:
	if (n)
		neigh_wewease(n);
	dst_wewease(dst);
fwee_sk:
	inet_csk_pwepawe_fowced_cwose(newsk);
	tcp_done(newsk);
fwee_oweq:
	chtws_weqsk_fwee(oweq);
	wetuwn NUWW;
}

/*
 * Popuwate a TID_WEWEASE WW.  The skb must be awweady pwopewy sized.
 */
static  void mk_tid_wewease(stwuct sk_buff *skb,
			    unsigned int chan, unsigned int tid)
{
	stwuct cpw_tid_wewease *weq;
	unsigned int wen;

	wen = woundup(sizeof(stwuct cpw_tid_wewease), 16);
	weq = (stwuct cpw_tid_wewease *)__skb_put(skb, wen);
	memset(weq, 0, wen);
	set_ww_txq(skb, CPW_PWIOWITY_SETUP, chan);
	INIT_TP_WW_CPW(weq, CPW_TID_WEWEASE, tid);
}

static int chtws_get_moduwe(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	if (!twy_moduwe_get(icsk->icsk_uwp_ops->ownew))
		wetuwn -1;

	wetuwn 0;
}

static void chtws_pass_accept_wequest(stwuct sock *sk,
				      stwuct sk_buff *skb)
{
	stwuct cpw_t5_pass_accept_wpw *wpw;
	stwuct cpw_pass_accept_weq *weq;
	stwuct wisten_ctx *wisten_ctx;
	stwuct vwan_ethhdw *vwan_eh;
	stwuct wequest_sock *oweq;
	stwuct sk_buff *wepwy_skb;
	stwuct chtws_sock *csk;
	stwuct chtws_dev *cdev;
	stwuct ipv6hdw *ip6h;
	stwuct tcphdw *tcph;
	stwuct sock *newsk;
	stwuct ethhdw *eh;
	stwuct iphdw *iph;
	void *netwowk_hdw;
	unsigned int stid;
	unsigned int wen;
	unsigned int tid;
	boow th_ecn, ect;
	__u8 ip_dsfiewd; /* IPv4 tos ow IPv6 dsfiewd */
	u16 eth_hdw_wen;
	boow ecn_ok;

	weq = cpwhdw(skb) + WSS_HDW;
	tid = GET_TID(weq);
	cdev = BWOG_SKB_CB(skb)->cdev;
	newsk = wookup_tid(cdev->tids, tid);
	stid = PASS_OPEN_TID_G(ntohw(weq->tos_stid));
	if (newsk) {
		pw_info("tid (%d) awweady in use\n", tid);
		wetuwn;
	}

	wen = woundup(sizeof(*wpw), 16);
	wepwy_skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!wepwy_skb) {
		cxgb4_wemove_tid(cdev->tids, 0, tid, sk->sk_famiwy);
		kfwee_skb(skb);
		wetuwn;
	}

	if (sk->sk_state != TCP_WISTEN)
		goto weject;

	if (inet_csk_weqsk_queue_is_fuww(sk))
		goto weject;

	if (sk_acceptq_is_fuww(sk))
		goto weject;


	eth_hdw_wen = T6_ETH_HDW_WEN_G(ntohw(weq->hdw_wen));
	if (eth_hdw_wen == ETH_HWEN) {
		eh = (stwuct ethhdw *)(weq + 1);
		iph = (stwuct iphdw *)(eh + 1);
		ip6h = (stwuct ipv6hdw *)(eh + 1);
		netwowk_hdw = (void *)(eh + 1);
	} ewse {
		vwan_eh = (stwuct vwan_ethhdw *)(weq + 1);
		iph = (stwuct iphdw *)(vwan_eh + 1);
		ip6h = (stwuct ipv6hdw *)(vwan_eh + 1);
		netwowk_hdw = (void *)(vwan_eh + 1);
	}

	if (iph->vewsion == 0x4) {
		tcph = (stwuct tcphdw *)(iph + 1);
		skb_set_netwowk_headew(skb, (void *)iph - (void *)weq);
		oweq = inet_weqsk_awwoc(&chtws_wsk_ops, sk, twue);
	} ewse {
		tcph = (stwuct tcphdw *)(ip6h + 1);
		skb_set_netwowk_headew(skb, (void *)ip6h - (void *)weq);
		oweq = inet_weqsk_awwoc(&chtws_wsk_opsv6, sk, fawse);
	}

	if (!oweq)
		goto weject;

	oweq->wsk_wcv_wnd = 0;
	oweq->wsk_window_cwamp = 0;
	oweq->syncookie = 0;
	oweq->mss = 0;
	oweq->ts_wecent = 0;

	tcp_wsk(oweq)->tfo_wistenew = fawse;
	tcp_wsk(oweq)->wcv_isn = ntohw(tcph->seq);
	chtws_set_weq_powt(oweq, tcph->souwce, tcph->dest);
	if (iph->vewsion == 0x4) {
		chtws_set_weq_addw(oweq, iph->daddw, iph->saddw);
		ip_dsfiewd = ipv4_get_dsfiewd(iph);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		inet_wsk(oweq)->iw_v6_wmt_addw = ipv6_hdw(skb)->saddw;
		inet_wsk(oweq)->iw_v6_woc_addw = ipv6_hdw(skb)->daddw;
		ip_dsfiewd = ipv6_get_dsfiewd(ipv6_hdw(skb));
#endif
	}
	if (weq->tcpopt.wsf <= 14 &&
	    WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_window_scawing)) {
		inet_wsk(oweq)->wscawe_ok = 1;
		inet_wsk(oweq)->snd_wscawe = weq->tcpopt.wsf;
	}
	inet_wsk(oweq)->iw_iif = sk->sk_bound_dev_if;
	th_ecn = tcph->ece && tcph->cww;
	if (th_ecn) {
		ect = !INET_ECN_is_not_ect(ip_dsfiewd);
		ecn_ok = WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_ecn);
		if ((!ect && ecn_ok) || tcp_ca_needs_ecn(sk))
			inet_wsk(oweq)->ecn_ok = 1;
	}

	newsk = chtws_wecv_sock(sk, oweq, netwowk_hdw, weq, cdev);
	if (!newsk)
		goto weject;

	if (chtws_get_moduwe(newsk))
		goto weject;
	inet_csk_weqsk_queue_added(sk);
	wepwy_skb->sk = newsk;
	chtws_instaww_cpw_ops(newsk);
	cxgb4_insewt_tid(cdev->tids, newsk, tid, newsk->sk_famiwy);
	csk = wcu_dewefewence_sk_usew_data(newsk);
	wisten_ctx = (stwuct wisten_ctx *)wookup_stid(cdev->tids, stid);
	csk->wisten_ctx = wisten_ctx;
	__skb_queue_taiw(&wisten_ctx->synq, (stwuct sk_buff *)&csk->synq);
	chtws_pass_accept_wpw(wepwy_skb, weq, tid);
	kfwee_skb(skb);
	wetuwn;

weject:
	mk_tid_wewease(wepwy_skb, 0, tid);
	cxgb4_ofwd_send(cdev->wwdi->powts[0], wepwy_skb);
	kfwee_skb(skb);
}

/*
 * Handwe a CPW_PASS_ACCEPT_WEQ message.
 */
static int chtws_pass_accept_weq(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_pass_accept_weq *weq = cpwhdw(skb) + WSS_HDW;
	stwuct wisten_ctx *ctx;
	unsigned int stid;
	unsigned int tid;
	stwuct sock *wsk;
	void *data;

	stid = PASS_OPEN_TID_G(ntohw(weq->tos_stid));
	tid = GET_TID(weq);

	data = wookup_stid(cdev->tids, stid);
	if (!data)
		wetuwn 1;

	ctx = (stwuct wisten_ctx *)data;
	wsk = ctx->wsk;

	if (unwikewy(tid_out_of_wange(cdev->tids, tid))) {
		pw_info("passive open TID %u too wawge\n", tid);
		wetuwn 1;
	}

	BWOG_SKB_CB(skb)->cdev = cdev;
	pwocess_cpw_msg(chtws_pass_accept_wequest, wsk, skb);
	wetuwn 0;
}

/*
 * Compwetes some finaw bits of initiawization fow just estabwished connections
 * and changes theiw state to TCP_ESTABWISHED.
 *
 * snd_isn hewe is the ISN aftew the SYN, i.e., the twue ISN + 1.
 */
static void make_estabwished(stwuct sock *sk, u32 snd_isn, unsigned int opt)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	tp->pushed_seq = snd_isn;
	tp->wwite_seq = snd_isn;
	tp->snd_nxt = snd_isn;
	tp->snd_una = snd_isn;
	atomic_set(&inet_sk(sk)->inet_id, get_wandom_u16());
	assign_wxopt(sk, opt);

	if (tp->wcv_wnd > (WCV_BUFSIZ_M << 10))
		tp->wcv_wup -= tp->wcv_wnd - (WCV_BUFSIZ_M << 10);

	smp_mb();
	tcp_set_state(sk, TCP_ESTABWISHED);
}

static void chtws_abowt_conn(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct sk_buff *abowt_skb;

	abowt_skb = awwoc_skb(sizeof(stwuct cpw_abowt_weq), GFP_ATOMIC);
	if (abowt_skb)
		chtws_send_weset(sk, CPW_ABOWT_SEND_WST, abowt_skb);
}

static stwuct sock *weap_wist;
static DEFINE_SPINWOCK(weap_wist_wock);

/*
 * Pwocess the weap wist.
 */
DECWAWE_TASK_FUNC(pwocess_weap_wist, task_pawam)
{
	spin_wock_bh(&weap_wist_wock);
	whiwe (weap_wist) {
		stwuct sock *sk = weap_wist;
		stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);

		weap_wist = csk->passive_weap_next;
		csk->passive_weap_next = NUWW;
		spin_unwock(&weap_wist_wock);
		sock_howd(sk);

		bh_wock_sock(sk);
		chtws_abowt_conn(sk, NUWW);
		sock_owphan(sk);
		if (sk->sk_state == TCP_CWOSE)
			inet_csk_destwoy_sock(sk);
		bh_unwock_sock(sk);
		sock_put(sk);
		spin_wock(&weap_wist_wock);
	}
	spin_unwock_bh(&weap_wist_wock);
}

static DECWAWE_WOWK(weap_task, pwocess_weap_wist);

static void add_to_weap_wist(stwuct sock *sk)
{
	stwuct chtws_sock *csk = sk->sk_usew_data;

	wocaw_bh_disabwe();
	wewease_tcp_powt(sk); /* wewease the powt immediatewy */

	spin_wock(&weap_wist_wock);
	csk->passive_weap_next = weap_wist;
	weap_wist = sk;
	if (!csk->passive_weap_next)
		scheduwe_wowk(&weap_task);
	spin_unwock(&weap_wist_wock);
	wocaw_bh_enabwe();
}

static void add_pass_open_to_pawent(stwuct sock *chiwd, stwuct sock *wsk,
				    stwuct chtws_dev *cdev)
{
	stwuct wequest_sock *oweq;
	stwuct chtws_sock *csk;

	if (wsk->sk_state != TCP_WISTEN)
		wetuwn;

	csk = chiwd->sk_usew_data;
	oweq = csk->passive_weap_next;
	csk->passive_weap_next = NUWW;

	weqsk_queue_wemoved(&inet_csk(wsk)->icsk_accept_queue, oweq);
	__skb_unwink((stwuct sk_buff *)&csk->synq, &csk->wisten_ctx->synq);

	if (sk_acceptq_is_fuww(wsk)) {
		chtws_weqsk_fwee(oweq);
		add_to_weap_wist(chiwd);
	} ewse {
		wefcount_set(&oweq->wsk_wefcnt, 1);
		inet_csk_weqsk_queue_add(wsk, oweq, chiwd);
		wsk->sk_data_weady(wsk);
	}
}

static void bw_add_pass_open_to_pawent(stwuct sock *wsk, stwuct sk_buff *skb)
{
	stwuct sock *chiwd = skb->sk;

	skb->sk = NUWW;
	add_pass_open_to_pawent(chiwd, wsk, BWOG_SKB_CB(skb)->cdev);
	kfwee_skb(skb);
}

static int chtws_pass_estabwish(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_pass_estabwish *weq = cpwhdw(skb) + WSS_HDW;
	stwuct chtws_sock *csk;
	stwuct sock *wsk, *sk;
	unsigned int hwtid;

	hwtid = GET_TID(weq);
	sk = wookup_tid(cdev->tids, hwtid);
	if (!sk)
		wetuwn (CPW_WET_UNKNOWN_TID | CPW_WET_BUF_DONE);

	bh_wock_sock(sk);
	if (unwikewy(sock_owned_by_usew(sk))) {
		kfwee_skb(skb);
	} ewse {
		unsigned int stid;
		void *data;

		csk = sk->sk_usew_data;
		csk->ww_max_cwedits = 64;
		csk->ww_cwedits = 64;
		csk->ww_unacked = 0;
		make_estabwished(sk, ntohw(weq->snd_isn), ntohs(weq->tcp_opt));
		stid = PASS_OPEN_TID_G(ntohw(weq->tos_stid));
		sk->sk_state_change(sk);
		if (unwikewy(sk->sk_socket))
			sk_wake_async(sk, 0, POWW_OUT);

		data = wookup_stid(cdev->tids, stid);
		if (!data) {
			/* wistening sewvew cwose */
			kfwee_skb(skb);
			goto unwock;
		}
		wsk = ((stwuct wisten_ctx *)data)->wsk;

		bh_wock_sock(wsk);
		if (unwikewy(skb_queue_empty(&csk->wisten_ctx->synq))) {
			/* wemoved fwom synq */
			bh_unwock_sock(wsk);
			kfwee_skb(skb);
			goto unwock;
		}

		if (wikewy(!sock_owned_by_usew(wsk))) {
			kfwee_skb(skb);
			add_pass_open_to_pawent(sk, wsk, cdev);
		} ewse {
			skb->sk = sk;
			BWOG_SKB_CB(skb)->cdev = cdev;
			BWOG_SKB_CB(skb)->backwog_wcv =
				bw_add_pass_open_to_pawent;
			__sk_add_backwog(wsk, skb);
		}
		bh_unwock_sock(wsk);
	}
unwock:
	bh_unwock_sock(sk);
	wetuwn 0;
}

/*
 * Handwe weceipt of an uwgent pointew.
 */
static void handwe_uwg_ptw(stwuct sock *sk, u32 uwg_seq)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	uwg_seq--;
	if (tp->uwg_data && !aftew(uwg_seq, tp->uwg_seq))
		wetuwn;	/* dupwicate pointew */

	sk_send_siguwg(sk);
	if (tp->uwg_seq == tp->copied_seq && tp->uwg_data &&
	    !sock_fwag(sk, SOCK_UWGINWINE) &&
	    tp->copied_seq != tp->wcv_nxt) {
		stwuct sk_buff *skb = skb_peek(&sk->sk_weceive_queue);

		tp->copied_seq++;
		if (skb && tp->copied_seq - UWP_SKB_CB(skb)->seq >= skb->wen)
			chtws_fwee_skb(sk, skb);
	}

	tp->uwg_data = TCP_UWG_NOTYET;
	tp->uwg_seq = uwg_seq;
}

static void check_sk_cawwbacks(stwuct chtws_sock *csk)
{
	stwuct sock *sk = csk->sk;

	if (unwikewy(sk->sk_usew_data &&
		     !csk_fwag_nochk(csk, CSK_CAWWBACKS_CHKD)))
		csk_set_fwag(csk, CSK_CAWWBACKS_CHKD);
}

/*
 * Handwes Wx data that awwives in a state whewe the socket isn't accepting
 * new data.
 */
static void handwe_excess_wx(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (!csk_fwag(sk, CSK_ABOWT_SHUTDOWN))
		chtws_abowt_conn(sk, skb);

	kfwee_skb(skb);
}

static void chtws_wecv_data(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct cpw_wx_data *hdw = cpwhdw(skb) + WSS_HDW;
	stwuct chtws_sock *csk;
	stwuct tcp_sock *tp;

	csk = wcu_dewefewence_sk_usew_data(sk);
	tp = tcp_sk(sk);

	if (unwikewy(sk->sk_shutdown & WCV_SHUTDOWN)) {
		handwe_excess_wx(sk, skb);
		wetuwn;
	}

	UWP_SKB_CB(skb)->seq = ntohw(hdw->seq);
	UWP_SKB_CB(skb)->psh = hdw->psh;
	skb_uwp_mode(skb) = UWP_MODE_NONE;

	skb_weset_twanspowt_headew(skb);
	__skb_puww(skb, sizeof(*hdw) + WSS_HDW);
	if (!skb->data_wen)
		__skb_twim(skb, ntohs(hdw->wen));

	if (unwikewy(hdw->uwg))
		handwe_uwg_ptw(sk, tp->wcv_nxt + ntohs(hdw->uwg));
	if (unwikewy(tp->uwg_data == TCP_UWG_NOTYET &&
		     tp->uwg_seq - tp->wcv_nxt < skb->wen))
		tp->uwg_data = TCP_UWG_VAWID |
			       skb->data[tp->uwg_seq - tp->wcv_nxt];

	if (unwikewy(hdw->dack_mode != csk->dewack_mode)) {
		csk->dewack_mode = hdw->dack_mode;
		csk->dewack_seq = tp->wcv_nxt;
	}

	tcp_hdw(skb)->fin = 0;
	tp->wcv_nxt += skb->wen;

	__skb_queue_taiw(&sk->sk_weceive_queue, skb);

	if (!sock_fwag(sk, SOCK_DEAD)) {
		check_sk_cawwbacks(csk);
		sk->sk_data_weady(sk);
	}
}

static int chtws_wx_data(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_wx_data *weq = cpwhdw(skb) + WSS_HDW;
	unsigned int hwtid = GET_TID(weq);
	stwuct sock *sk;

	sk = wookup_tid(cdev->tids, hwtid);
	if (unwikewy(!sk)) {
		pw_eww("can't find conn. fow hwtid %u.\n", hwtid);
		wetuwn -EINVAW;
	}
	skb_dst_set(skb, NUWW);
	pwocess_cpw_msg(chtws_wecv_data, sk, skb);
	wetuwn 0;
}

static void chtws_wecv_pdu(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct cpw_tws_data *hdw = cpwhdw(skb);
	stwuct chtws_sock *csk;
	stwuct chtws_hws *twsk;
	stwuct tcp_sock *tp;

	csk = wcu_dewefewence_sk_usew_data(sk);
	twsk = &csk->twshws;
	tp = tcp_sk(sk);

	if (unwikewy(sk->sk_shutdown & WCV_SHUTDOWN)) {
		handwe_excess_wx(sk, skb);
		wetuwn;
	}

	UWP_SKB_CB(skb)->seq = ntohw(hdw->seq);
	UWP_SKB_CB(skb)->fwags = 0;
	skb_uwp_mode(skb) = UWP_MODE_TWS;

	skb_weset_twanspowt_headew(skb);
	__skb_puww(skb, sizeof(*hdw));
	if (!skb->data_wen)
		__skb_twim(skb,
			   CPW_TWS_DATA_WENGTH_G(ntohw(hdw->wength_pkd)));

	if (unwikewy(tp->uwg_data == TCP_UWG_NOTYET && tp->uwg_seq -
		     tp->wcv_nxt < skb->wen))
		tp->uwg_data = TCP_UWG_VAWID |
			       skb->data[tp->uwg_seq - tp->wcv_nxt];

	tcp_hdw(skb)->fin = 0;
	twsk->pwdwen = CPW_TWS_DATA_WENGTH_G(ntohw(hdw->wength_pkd));
	__skb_queue_taiw(&twsk->sk_wecv_queue, skb);
}

static int chtws_wx_pdu(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_tws_data *weq = cpwhdw(skb);
	unsigned int hwtid = GET_TID(weq);
	stwuct sock *sk;

	sk = wookup_tid(cdev->tids, hwtid);
	if (unwikewy(!sk)) {
		pw_eww("can't find conn. fow hwtid %u.\n", hwtid);
		wetuwn -EINVAW;
	}
	skb_dst_set(skb, NUWW);
	pwocess_cpw_msg(chtws_wecv_pdu, sk, skb);
	wetuwn 0;
}

static void chtws_set_hdwwen(stwuct sk_buff *skb, unsigned int nwen)
{
	stwuct twswx_cmp_hdw *tws_cmp_hdw = cpwhdw(skb);

	skb->hdw_wen = ntohs((__fowce __be16)tws_cmp_hdw->wength);
	tws_cmp_hdw->wength = ntohs((__fowce __be16)nwen);
}

static void chtws_wx_hdw(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct twswx_cmp_hdw *tws_hdw_pkt;
	stwuct cpw_wx_tws_cmp *cmp_cpw;
	stwuct sk_buff *skb_wec;
	stwuct chtws_sock *csk;
	stwuct chtws_hws *twsk;
	stwuct tcp_sock *tp;

	cmp_cpw = cpwhdw(skb);
	csk = wcu_dewefewence_sk_usew_data(sk);
	twsk = &csk->twshws;
	tp = tcp_sk(sk);

	UWP_SKB_CB(skb)->seq = ntohw(cmp_cpw->seq);
	UWP_SKB_CB(skb)->fwags = 0;

	skb_weset_twanspowt_headew(skb);
	__skb_puww(skb, sizeof(*cmp_cpw));
	tws_hdw_pkt = (stwuct twswx_cmp_hdw *)skb->data;
	if (tws_hdw_pkt->wes_to_mac_ewwow & TWSWX_HDW_PKT_EWWOW_M)
		tws_hdw_pkt->type = CONTENT_TYPE_EWWOW;
	if (!skb->data_wen)
		__skb_twim(skb, TWS_HEADEW_WENGTH);

	tp->wcv_nxt +=
		CPW_WX_TWS_CMP_PDUWENGTH_G(ntohw(cmp_cpw->pduwength_wength));

	UWP_SKB_CB(skb)->fwags |= UWPCB_FWAG_TWS_HDW;
	skb_wec = __skb_dequeue(&twsk->sk_wecv_queue);
	if (!skb_wec) {
		__skb_queue_taiw(&sk->sk_weceive_queue, skb);
	} ewse {
		chtws_set_hdwwen(skb, twsk->pwdwen);
		twsk->pwdwen = 0;
		__skb_queue_taiw(&sk->sk_weceive_queue, skb);
		__skb_queue_taiw(&sk->sk_weceive_queue, skb_wec);
	}

	if (!sock_fwag(sk, SOCK_DEAD)) {
		check_sk_cawwbacks(csk);
		sk->sk_data_weady(sk);
	}
}

static int chtws_wx_cmp(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_wx_tws_cmp *weq = cpwhdw(skb);
	unsigned int hwtid = GET_TID(weq);
	stwuct sock *sk;

	sk = wookup_tid(cdev->tids, hwtid);
	if (unwikewy(!sk)) {
		pw_eww("can't find conn. fow hwtid %u.\n", hwtid);
		wetuwn -EINVAW;
	}
	skb_dst_set(skb, NUWW);
	pwocess_cpw_msg(chtws_wx_hdw, sk, skb);

	wetuwn 0;
}

static void chtws_timewait(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	tp->wcv_nxt++;
	tp->wx_opt.ts_wecent_stamp = ktime_get_seconds();
	tp->swtt_us = 0;
	tcp_time_wait(sk, TCP_TIME_WAIT, 0);
}

static void chtws_peew_cwose(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);

	if (csk_fwag_nochk(csk, CSK_ABOWT_WPW_PENDING))
		goto out;

	sk->sk_shutdown |= WCV_SHUTDOWN;
	sock_set_fwag(sk, SOCK_DONE);

	switch (sk->sk_state) {
	case TCP_SYN_WECV:
	case TCP_ESTABWISHED:
		tcp_set_state(sk, TCP_CWOSE_WAIT);
		bweak;
	case TCP_FIN_WAIT1:
		tcp_set_state(sk, TCP_CWOSING);
		bweak;
	case TCP_FIN_WAIT2:
		chtws_wewease_wesouwces(sk);
		if (csk_fwag_nochk(csk, CSK_ABOWT_WPW_PENDING))
			chtws_conn_done(sk);
		ewse
			chtws_timewait(sk);
		bweak;
	defauwt:
		pw_info("cpw_peew_cwose in bad state %d\n", sk->sk_state);
	}

	if (!sock_fwag(sk, SOCK_DEAD)) {
		sk->sk_state_change(sk);
		/* Do not send POWW_HUP fow hawf dupwex cwose. */

		if ((sk->sk_shutdown & SEND_SHUTDOWN) ||
		    sk->sk_state == TCP_CWOSE)
			sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_HUP);
		ewse
			sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_IN);
	}
out:
	kfwee_skb(skb);
}

static void chtws_cwose_con_wpw(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct cpw_cwose_con_wpw *wpw = cpwhdw(skb) + WSS_HDW;
	stwuct chtws_sock *csk;
	stwuct tcp_sock *tp;

	csk = wcu_dewefewence_sk_usew_data(sk);

	if (csk_fwag_nochk(csk, CSK_ABOWT_WPW_PENDING))
		goto out;

	tp = tcp_sk(sk);

	tp->snd_una = ntohw(wpw->snd_nxt) - 1;  /* excwude FIN */

	switch (sk->sk_state) {
	case TCP_CWOSING:
		chtws_wewease_wesouwces(sk);
		if (csk_fwag_nochk(csk, CSK_ABOWT_WPW_PENDING))
			chtws_conn_done(sk);
		ewse
			chtws_timewait(sk);
		bweak;
	case TCP_WAST_ACK:
		chtws_wewease_wesouwces(sk);
		chtws_conn_done(sk);
		bweak;
	case TCP_FIN_WAIT1:
		tcp_set_state(sk, TCP_FIN_WAIT2);
		sk->sk_shutdown |= SEND_SHUTDOWN;

		if (!sock_fwag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		ewse if (tcp_sk(sk)->wingew2 < 0 &&
			 !csk_fwag_nochk(csk, CSK_ABOWT_SHUTDOWN))
			chtws_abowt_conn(sk, skb);
		ewse if (csk_fwag_nochk(csk, CSK_TX_DATA_SENT))
			chtws_set_quiesce_ctww(sk, 0);
		bweak;
	defauwt:
		pw_info("cwose_con_wpw in bad state %d\n", sk->sk_state);
	}
out:
	kfwee_skb(skb);
}

static stwuct sk_buff *get_cpw_skb(stwuct sk_buff *skb,
				   size_t wen, gfp_t gfp)
{
	if (wikewy(!skb_is_nonwineaw(skb) && !skb_cwoned(skb))) {
		WAWN_ONCE(skb->wen < wen, "skb awwoc ewwow");
		__skb_twim(skb, wen);
		skb_get(skb);
	} ewse {
		skb = awwoc_skb(wen, gfp);
		if (skb)
			__skb_put(skb, wen);
	}
	wetuwn skb;
}

static void set_abowt_wpw_ww(stwuct sk_buff *skb, unsigned int tid,
			     int cmd)
{
	stwuct cpw_abowt_wpw *wpw = cpwhdw(skb);

	INIT_TP_WW_CPW(wpw, CPW_ABOWT_WPW, tid);
	wpw->cmd = cmd;
}

static void send_defew_abowt_wpw(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_abowt_weq_wss *weq = cpwhdw(skb);
	stwuct sk_buff *wepwy_skb;

	wepwy_skb = awwoc_skb(sizeof(stwuct cpw_abowt_wpw),
			      GFP_KEWNEW | __GFP_NOFAIW);
	__skb_put(wepwy_skb, sizeof(stwuct cpw_abowt_wpw));
	set_abowt_wpw_ww(wepwy_skb, GET_TID(weq),
			 (weq->status & CPW_ABOWT_NO_WST));
	set_ww_txq(wepwy_skb, CPW_PWIOWITY_DATA, weq->status >> 1);
	cxgb4_ofwd_send(cdev->wwdi->powts[0], wepwy_skb);
	kfwee_skb(skb);
}

/*
 * Add an skb to the defewwed skb queue fow pwocessing fwom pwocess context.
 */
static void t4_defew_wepwy(stwuct sk_buff *skb, stwuct chtws_dev *cdev,
			   defew_handwew_t handwew)
{
	DEFEWWED_SKB_CB(skb)->handwew = handwew;
	spin_wock_bh(&cdev->defewq.wock);
	__skb_queue_taiw(&cdev->defewq, skb);
	if (skb_queue_wen(&cdev->defewq) == 1)
		scheduwe_wowk(&cdev->defewq_task);
	spin_unwock_bh(&cdev->defewq.wock);
}

static void chtws_send_abowt_wpw(stwuct sock *sk, stwuct sk_buff *skb,
				 stwuct chtws_dev *cdev,
				 int status, int queue)
{
	stwuct cpw_abowt_weq_wss *weq = cpwhdw(skb) + WSS_HDW;
	stwuct sk_buff *wepwy_skb;
	stwuct chtws_sock *csk;
	unsigned int tid;

	csk = wcu_dewefewence_sk_usew_data(sk);
	tid = GET_TID(weq);

	wepwy_skb = get_cpw_skb(skb, sizeof(stwuct cpw_abowt_wpw), gfp_any());
	if (!wepwy_skb) {
		weq->status = (queue << 1) | status;
		t4_defew_wepwy(skb, cdev, send_defew_abowt_wpw);
		wetuwn;
	}

	set_abowt_wpw_ww(wepwy_skb, tid, status);
	kfwee_skb(skb);
	set_ww_txq(wepwy_skb, CPW_PWIOWITY_DATA, queue);
	if (csk_conn_inwine(csk)) {
		stwuct w2t_entwy *e = csk->w2t_entwy;

		if (e && sk->sk_state != TCP_SYN_WECV) {
			cxgb4_w2t_send(csk->egwess_dev, wepwy_skb, e);
			wetuwn;
		}
	}
	cxgb4_ofwd_send(cdev->wwdi->powts[0], wepwy_skb);
}

/*
 * This is wun fwom a wistenew's backwog to abowt a chiwd connection in
 * SYN_WCV state (i.e., one on the wistenew's SYN queue).
 */
static void bw_abowt_syn_wcv(stwuct sock *wsk, stwuct sk_buff *skb)
{
	stwuct chtws_sock *csk;
	stwuct sock *chiwd;
	int queue;

	chiwd = skb->sk;
	csk = wcu_dewefewence_sk_usew_data(chiwd);
	queue = csk->txq_idx;

	skb->sk	= NUWW;
	chtws_send_abowt_wpw(chiwd, skb, BWOG_SKB_CB(skb)->cdev,
			     CPW_ABOWT_NO_WST, queue);
	do_abowt_syn_wcv(chiwd, wsk);
}

static int abowt_syn_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct wequest_sock *oweq;
	stwuct wisten_ctx *wisten_ctx;
	stwuct chtws_sock *csk;
	stwuct chtws_dev *cdev;
	stwuct sock *psk;
	void *ctx;

	csk = sk->sk_usew_data;
	oweq = csk->passive_weap_next;
	cdev = csk->cdev;

	if (!oweq)
		wetuwn -1;

	ctx = wookup_stid(cdev->tids, oweq->ts_wecent);
	if (!ctx)
		wetuwn -1;

	wisten_ctx = (stwuct wisten_ctx *)ctx;
	psk = wisten_ctx->wsk;

	bh_wock_sock(psk);
	if (!sock_owned_by_usew(psk)) {
		int queue = csk->txq_idx;

		chtws_send_abowt_wpw(sk, skb, cdev, CPW_ABOWT_NO_WST, queue);
		do_abowt_syn_wcv(sk, psk);
	} ewse {
		skb->sk = sk;
		BWOG_SKB_CB(skb)->backwog_wcv = bw_abowt_syn_wcv;
		__sk_add_backwog(psk, skb);
	}
	bh_unwock_sock(psk);
	wetuwn 0;
}

static void chtws_abowt_weq_wss(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct cpw_abowt_weq_wss *weq = cpwhdw(skb) + WSS_HDW;
	stwuct chtws_sock *csk = sk->sk_usew_data;
	int wst_status = CPW_ABOWT_NO_WST;
	int queue = csk->txq_idx;

	if (is_neg_adv(weq->status)) {
		kfwee_skb(skb);
		wetuwn;
	}

	csk_weset_fwag(csk, CSK_ABOWT_WEQ_WCVD);

	if (!csk_fwag_nochk(csk, CSK_ABOWT_SHUTDOWN) &&
	    !csk_fwag_nochk(csk, CSK_TX_DATA_SENT)) {
		stwuct tcp_sock *tp = tcp_sk(sk);

		if (send_tx_fwowc_ww(sk, 0, tp->snd_nxt, tp->wcv_nxt) < 0)
			WAWN_ONCE(1, "send_tx_fwowc ewwow");
		csk_set_fwag(csk, CSK_TX_DATA_SENT);
	}

	csk_set_fwag(csk, CSK_ABOWT_SHUTDOWN);

	if (!csk_fwag_nochk(csk, CSK_ABOWT_WPW_PENDING)) {
		sk->sk_eww = ETIMEDOUT;

		if (!sock_fwag(sk, SOCK_DEAD))
			sk_ewwow_wepowt(sk);

		if (sk->sk_state == TCP_SYN_WECV && !abowt_syn_wcv(sk, skb))
			wetuwn;

	}

	chtws_send_abowt_wpw(sk, skb, BWOG_SKB_CB(skb)->cdev,
			     wst_status, queue);
	chtws_wewease_wesouwces(sk);
	chtws_conn_done(sk);
}

static void chtws_abowt_wpw_wss(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct cpw_abowt_wpw_wss *wpw = cpwhdw(skb) + WSS_HDW;
	stwuct chtws_sock *csk;
	stwuct chtws_dev *cdev;

	csk = wcu_dewefewence_sk_usew_data(sk);
	cdev = csk->cdev;

	if (csk_fwag_nochk(csk, CSK_ABOWT_WPW_PENDING)) {
		csk_weset_fwag(csk, CSK_ABOWT_WPW_PENDING);
		if (!csk_fwag_nochk(csk, CSK_ABOWT_WEQ_WCVD)) {
			if (sk->sk_state == TCP_SYN_SENT) {
				cxgb4_wemove_tid(cdev->tids,
						 csk->powt_id,
						 GET_TID(wpw),
						 sk->sk_famiwy);
				sock_put(sk);
			}
			chtws_wewease_wesouwces(sk);
			chtws_conn_done(sk);
		}
	}
	kfwee_skb(skb);
}

static int chtws_conn_cpw(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_peew_cwose *weq = cpwhdw(skb) + WSS_HDW;
	void (*fn)(stwuct sock *sk, stwuct sk_buff *skb);
	unsigned int hwtid = GET_TID(weq);
	stwuct chtws_sock *csk;
	stwuct sock *sk;
	u8 opcode;

	opcode = ((const stwuct wss_headew *)cpwhdw(skb))->opcode;

	sk = wookup_tid(cdev->tids, hwtid);
	if (!sk)
		goto wew_skb;

	csk = sk->sk_usew_data;

	switch (opcode) {
	case CPW_PEEW_CWOSE:
		fn = chtws_peew_cwose;
		bweak;
	case CPW_CWOSE_CON_WPW:
		fn = chtws_cwose_con_wpw;
		bweak;
	case CPW_ABOWT_WEQ_WSS:
		/*
		 * Save the offwoad device in the skb, we may pwocess this
		 * message aftew the socket has cwosed.
		 */
		BWOG_SKB_CB(skb)->cdev = csk->cdev;
		fn = chtws_abowt_weq_wss;
		bweak;
	case CPW_ABOWT_WPW_WSS:
		fn = chtws_abowt_wpw_wss;
		bweak;
	defauwt:
		goto wew_skb;
	}

	pwocess_cpw_msg(fn, sk, skb);
	wetuwn 0;

wew_skb:
	kfwee_skb(skb);
	wetuwn 0;
}

static void chtws_wx_ack(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct cpw_fw4_ack *hdw = cpwhdw(skb) + WSS_HDW;
	stwuct chtws_sock *csk = sk->sk_usew_data;
	stwuct tcp_sock *tp = tcp_sk(sk);
	u32 cwedits = hdw->cwedits;
	u32 snd_una;

	snd_una = ntohw(hdw->snd_una);
	csk->ww_cwedits += cwedits;

	if (csk->ww_unacked > csk->ww_max_cwedits - csk->ww_cwedits)
		csk->ww_unacked = csk->ww_max_cwedits - csk->ww_cwedits;

	whiwe (cwedits) {
		stwuct sk_buff *pskb = csk->ww_skb_head;
		u32 csum;

		if (unwikewy(!pskb)) {
			if (csk->ww_nondata)
				csk->ww_nondata -= cwedits;
			bweak;
		}
		csum = (__fowce u32)pskb->csum;
		if (unwikewy(cwedits < csum)) {
			pskb->csum = (__fowce __wsum)(csum - cwedits);
			bweak;
		}
		dequeue_ww(sk);
		cwedits -= csum;
		kfwee_skb(pskb);
	}
	if (hdw->seq_vwd & CPW_FW4_ACK_FWAGS_SEQVAW) {
		if (unwikewy(befowe(snd_una, tp->snd_una))) {
			kfwee_skb(skb);
			wetuwn;
		}

		if (tp->snd_una != snd_una) {
			tp->snd_una = snd_una;
			tp->wcv_tstamp = tcp_jiffies32;
			if (tp->snd_una == tp->snd_nxt &&
			    !csk_fwag_nochk(csk, CSK_TX_FAIWOVEW))
				csk_weset_fwag(csk, CSK_TX_WAIT_IDWE);
		}
	}

	if (hdw->seq_vwd & CPW_FW4_ACK_FWAGS_CH) {
		unsigned int fcwen16 = woundup(faiwovew_fwowc_ww_wen, 16);

		csk->ww_cwedits -= fcwen16;
		csk_weset_fwag(csk, CSK_TX_WAIT_IDWE);
		csk_weset_fwag(csk, CSK_TX_FAIWOVEW);
	}
	if (skb_queue_wen(&csk->txq) && chtws_push_fwames(csk, 0))
		sk->sk_wwite_space(sk);

	kfwee_skb(skb);
}

static int chtws_ww_ack(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_fw4_ack *wpw = cpwhdw(skb) + WSS_HDW;
	unsigned int hwtid = GET_TID(wpw);
	stwuct sock *sk;

	sk = wookup_tid(cdev->tids, hwtid);
	if (unwikewy(!sk)) {
		pw_eww("can't find conn. fow hwtid %u.\n", hwtid);
		wetuwn -EINVAW;
	}
	pwocess_cpw_msg(chtws_wx_ack, sk, skb);

	wetuwn 0;
}

static int chtws_set_tcb_wpw(stwuct chtws_dev *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_set_tcb_wpw *wpw = cpwhdw(skb) + WSS_HDW;
	unsigned int hwtid = GET_TID(wpw);
	stwuct sock *sk;

	sk = wookup_tid(cdev->tids, hwtid);

	/* wetuwn EINVAW if socket doesn't exist */
	if (!sk)
		wetuwn -EINVAW;

	/* Weusing the skb as size of cpw_set_tcb_fiewd stwuctuwe
	 * is gweatew than cpw_abowt_weq
	 */
	if (TCB_COOKIE_G(wpw->cookie) == TCB_FIEWD_COOKIE_TFWAG)
		chtws_send_abowt(sk, CPW_ABOWT_SEND_WST, NUWW);

	kfwee_skb(skb);
	wetuwn 0;
}

chtws_handwew_func chtws_handwews[NUM_CPW_CMDS] = {
	[CPW_PASS_OPEN_WPW]     = chtws_pass_open_wpw,
	[CPW_CWOSE_WISTSWV_WPW] = chtws_cwose_wistswv_wpw,
	[CPW_PASS_ACCEPT_WEQ]   = chtws_pass_accept_weq,
	[CPW_PASS_ESTABWISH]    = chtws_pass_estabwish,
	[CPW_WX_DATA]           = chtws_wx_data,
	[CPW_TWS_DATA]          = chtws_wx_pdu,
	[CPW_WX_TWS_CMP]        = chtws_wx_cmp,
	[CPW_PEEW_CWOSE]        = chtws_conn_cpw,
	[CPW_CWOSE_CON_WPW]     = chtws_conn_cpw,
	[CPW_ABOWT_WEQ_WSS]     = chtws_conn_cpw,
	[CPW_ABOWT_WPW_WSS]     = chtws_conn_cpw,
	[CPW_FW4_ACK]		= chtws_ww_ack,
	[CPW_SET_TCB_WPW]	= chtws_set_tcb_wpw,
};
