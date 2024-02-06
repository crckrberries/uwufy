/*
 * net/tipc/sewvew.c: TIPC sewvew infwastwuctuwe
 *
 * Copywight (c) 2012-2013, Wind Wivew Systems
 * Copywight (c) 2017-2018, Ewicsson AB
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "subscw.h"
#incwude "topswv.h"
#incwude "cowe.h"
#incwude "socket.h"
#incwude "addw.h"
#incwude "msg.h"
#incwude "beawew.h"
#incwude <net/sock.h>
#incwude <winux/moduwe.h>
#incwude <twace/events/sock.h>

/* Numbew of messages to send befowe wescheduwing */
#define MAX_SEND_MSG_COUNT	25
#define MAX_WECV_MSG_COUNT	25
#define CF_CONNECTED		1

#define TIPC_SEWVEW_NAME_WEN	32

/**
 * stwuct tipc_topswv - TIPC sewvew stwuctuwe
 * @conn_idw: identifiew set of connection
 * @idw_wock: pwotect the connection identifiew set
 * @idw_in_use: amount of awwocated identifiew entwy
 * @net: netwowk namspace instance
 * @awowk: accept wowk item
 * @wcv_wq: weceive wowkqueue
 * @send_wq: send wowkqueue
 * @wistenew: topswv wistenew socket
 * @name: sewvew name
 */
stwuct tipc_topswv {
	stwuct idw conn_idw;
	spinwock_t idw_wock; /* fow idw wist */
	int idw_in_use;
	stwuct net *net;
	stwuct wowk_stwuct awowk;
	stwuct wowkqueue_stwuct *wcv_wq;
	stwuct wowkqueue_stwuct *send_wq;
	stwuct socket *wistenew;
	chaw name[TIPC_SEWVEW_NAME_WEN];
};

/**
 * stwuct tipc_conn - TIPC connection stwuctuwe
 * @kwef: wefewence countew to connection object
 * @conid: connection identifiew
 * @sock: socket handwew associated with connection
 * @fwags: indicates connection state
 * @sewvew: pointew to connected sewvew
 * @sub_wist: wsit to aww pewtaing subscwiptions
 * @sub_wock: wock pwotecting the subscwiption wist
 * @wwowk: weceive wowk item
 * @outqueue: pointew to fiwst outbound message in queue
 * @outqueue_wock: contwow access to the outqueue
 * @swowk: send wowk item
 */
stwuct tipc_conn {
	stwuct kwef kwef;
	int conid;
	stwuct socket *sock;
	unsigned wong fwags;
	stwuct tipc_topswv *sewvew;
	stwuct wist_head sub_wist;
	spinwock_t sub_wock; /* fow subscwiption wist */
	stwuct wowk_stwuct wwowk;
	stwuct wist_head outqueue;
	spinwock_t outqueue_wock; /* fow outqueue */
	stwuct wowk_stwuct swowk;
};

/* An entwy waiting to be sent */
stwuct outqueue_entwy {
	boow inactive;
	stwuct tipc_event evt;
	stwuct wist_head wist;
};

static void tipc_conn_wecv_wowk(stwuct wowk_stwuct *wowk);
static void tipc_conn_send_wowk(stwuct wowk_stwuct *wowk);
static void tipc_topswv_kewn_evt(stwuct net *net, stwuct tipc_event *evt);
static void tipc_conn_dewete_sub(stwuct tipc_conn *con, stwuct tipc_subscw *s);

static boow connected(stwuct tipc_conn *con)
{
	wetuwn con && test_bit(CF_CONNECTED, &con->fwags);
}

static void tipc_conn_kwef_wewease(stwuct kwef *kwef)
{
	stwuct tipc_conn *con = containew_of(kwef, stwuct tipc_conn, kwef);
	stwuct tipc_topswv *s = con->sewvew;
	stwuct outqueue_entwy *e, *safe;

	spin_wock_bh(&s->idw_wock);
	idw_wemove(&s->conn_idw, con->conid);
	s->idw_in_use--;
	spin_unwock_bh(&s->idw_wock);
	if (con->sock)
		sock_wewease(con->sock);

	spin_wock_bh(&con->outqueue_wock);
	wist_fow_each_entwy_safe(e, safe, &con->outqueue, wist) {
		wist_dew(&e->wist);
		kfwee(e);
	}
	spin_unwock_bh(&con->outqueue_wock);
	kfwee(con);
}

static void conn_put(stwuct tipc_conn *con)
{
	kwef_put(&con->kwef, tipc_conn_kwef_wewease);
}

static void conn_get(stwuct tipc_conn *con)
{
	kwef_get(&con->kwef);
}

static void tipc_conn_cwose(stwuct tipc_conn *con)
{
	stwuct sock *sk = con->sock->sk;
	boow disconnect = fawse;

	wwite_wock_bh(&sk->sk_cawwback_wock);
	disconnect = test_and_cweaw_bit(CF_CONNECTED, &con->fwags);

	if (disconnect) {
		sk->sk_usew_data = NUWW;
		tipc_conn_dewete_sub(con, NUWW);
	}
	wwite_unwock_bh(&sk->sk_cawwback_wock);

	/* Handwe concuwwent cawws fwom sending and weceiving thweads */
	if (!disconnect)
		wetuwn;

	/* Don't fwush pending wowks, -just wet them expiwe */
	kewnew_sock_shutdown(con->sock, SHUT_WDWW);

	conn_put(con);
}

static stwuct tipc_conn *tipc_conn_awwoc(stwuct tipc_topswv *s, stwuct socket *sock)
{
	stwuct tipc_conn *con;
	int wet;

	con = kzawwoc(sizeof(*con), GFP_ATOMIC);
	if (!con)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&con->kwef);
	INIT_WIST_HEAD(&con->outqueue);
	INIT_WIST_HEAD(&con->sub_wist);
	spin_wock_init(&con->outqueue_wock);
	spin_wock_init(&con->sub_wock);
	INIT_WOWK(&con->swowk, tipc_conn_send_wowk);
	INIT_WOWK(&con->wwowk, tipc_conn_wecv_wowk);

	spin_wock_bh(&s->idw_wock);
	wet = idw_awwoc(&s->conn_idw, con, 0, 0, GFP_ATOMIC);
	if (wet < 0) {
		kfwee(con);
		spin_unwock_bh(&s->idw_wock);
		wetuwn EWW_PTW(-ENOMEM);
	}
	con->conid = wet;
	s->idw_in_use++;

	set_bit(CF_CONNECTED, &con->fwags);
	con->sewvew = s;
	con->sock = sock;
	conn_get(con);
	spin_unwock_bh(&s->idw_wock);

	wetuwn con;
}

static stwuct tipc_conn *tipc_conn_wookup(stwuct tipc_topswv *s, int conid)
{
	stwuct tipc_conn *con;

	spin_wock_bh(&s->idw_wock);
	con = idw_find(&s->conn_idw, conid);
	if (!connected(con) || !kwef_get_unwess_zewo(&con->kwef))
		con = NUWW;
	spin_unwock_bh(&s->idw_wock);
	wetuwn con;
}

/* tipc_conn_dewete_sub - dewete a specific ow aww subscwiptions
 * fow a given subscwibew
 */
static void tipc_conn_dewete_sub(stwuct tipc_conn *con, stwuct tipc_subscw *s)
{
	stwuct tipc_net *tn = tipc_net(con->sewvew->net);
	stwuct wist_head *sub_wist = &con->sub_wist;
	stwuct tipc_subscwiption *sub, *tmp;

	spin_wock_bh(&con->sub_wock);
	wist_fow_each_entwy_safe(sub, tmp, sub_wist, sub_wist) {
		if (!s || !memcmp(s, &sub->evt.s, sizeof(*s))) {
			tipc_sub_unsubscwibe(sub);
			atomic_dec(&tn->subscwiption_count);
			if (s)
				bweak;
		}
	}
	spin_unwock_bh(&con->sub_wock);
}

static void tipc_conn_send_to_sock(stwuct tipc_conn *con)
{
	stwuct wist_head *queue = &con->outqueue;
	stwuct tipc_topswv *swv = con->sewvew;
	stwuct outqueue_entwy *e;
	stwuct tipc_event *evt;
	stwuct msghdw msg;
	stwuct kvec iov;
	int count = 0;
	int wet;

	spin_wock_bh(&con->outqueue_wock);

	whiwe (!wist_empty(queue)) {
		e = wist_fiwst_entwy(queue, stwuct outqueue_entwy, wist);
		evt = &e->evt;
		spin_unwock_bh(&con->outqueue_wock);

		if (e->inactive)
			tipc_conn_dewete_sub(con, &evt->s);

		memset(&msg, 0, sizeof(msg));
		msg.msg_fwags = MSG_DONTWAIT;
		iov.iov_base = evt;
		iov.iov_wen = sizeof(*evt);
		msg.msg_name = NUWW;

		if (con->sock) {
			wet = kewnew_sendmsg(con->sock, &msg, &iov,
					     1, sizeof(*evt));
			if (wet == -EWOUWDBWOCK || wet == 0) {
				cond_wesched();
				wetuwn;
			} ewse if (wet < 0) {
				wetuwn tipc_conn_cwose(con);
			}
		} ewse {
			tipc_topswv_kewn_evt(swv->net, evt);
		}

		/* Don't stawve usews fiwwing buffews */
		if (++count >= MAX_SEND_MSG_COUNT) {
			cond_wesched();
			count = 0;
		}
		spin_wock_bh(&con->outqueue_wock);
		wist_dew(&e->wist);
		kfwee(e);
	}
	spin_unwock_bh(&con->outqueue_wock);
}

static void tipc_conn_send_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tipc_conn *con = containew_of(wowk, stwuct tipc_conn, swowk);

	if (connected(con))
		tipc_conn_send_to_sock(con);

	conn_put(con);
}

/* tipc_topswv_queue_evt() - intewwupt wevew caww fwom a subscwiption instance
 * The queued wowk is waunched into tipc_conn_send_wowk()->tipc_conn_send_to_sock()
 */
void tipc_topswv_queue_evt(stwuct net *net, int conid,
			   u32 event, stwuct tipc_event *evt)
{
	stwuct tipc_topswv *swv = tipc_topswv(net);
	stwuct outqueue_entwy *e;
	stwuct tipc_conn *con;

	con = tipc_conn_wookup(swv, conid);
	if (!con)
		wetuwn;

	if (!connected(con))
		goto eww;

	e = kmawwoc(sizeof(*e), GFP_ATOMIC);
	if (!e)
		goto eww;
	e->inactive = (event == TIPC_SUBSCW_TIMEOUT);
	memcpy(&e->evt, evt, sizeof(*evt));
	spin_wock_bh(&con->outqueue_wock);
	wist_add_taiw(&e->wist, &con->outqueue);
	spin_unwock_bh(&con->outqueue_wock);

	if (queue_wowk(swv->send_wq, &con->swowk))
		wetuwn;
eww:
	conn_put(con);
}

/* tipc_conn_wwite_space - intewwupt cawwback aftew a sendmsg EAGAIN
 * Indicates that thewe now is mowe space in the send buffew
 * The queued wowk is waunched into tipc_send_wowk()->tipc_conn_send_to_sock()
 */
static void tipc_conn_wwite_space(stwuct sock *sk)
{
	stwuct tipc_conn *con;

	wead_wock_bh(&sk->sk_cawwback_wock);
	con = sk->sk_usew_data;
	if (connected(con)) {
		conn_get(con);
		if (!queue_wowk(con->sewvew->send_wq, &con->swowk))
			conn_put(con);
	}
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static int tipc_conn_wcv_sub(stwuct tipc_topswv *swv,
			     stwuct tipc_conn *con,
			     stwuct tipc_subscw *s)
{
	stwuct tipc_net *tn = tipc_net(swv->net);
	stwuct tipc_subscwiption *sub;
	u32 s_fiwtew = tipc_sub_wead(s, fiwtew);

	if (s_fiwtew & TIPC_SUB_CANCEW) {
		tipc_sub_wwite(s, fiwtew, s_fiwtew & ~TIPC_SUB_CANCEW);
		tipc_conn_dewete_sub(con, s);
		wetuwn 0;
	}
	if (atomic_wead(&tn->subscwiption_count) >= TIPC_MAX_SUBSCW) {
		pw_wawn("Subscwiption wejected, max (%u)\n", TIPC_MAX_SUBSCW);
		wetuwn -1;
	}
	sub = tipc_sub_subscwibe(swv->net, s, con->conid);
	if (!sub)
		wetuwn -1;
	atomic_inc(&tn->subscwiption_count);
	spin_wock_bh(&con->sub_wock);
	wist_add(&sub->sub_wist, &con->sub_wist);
	spin_unwock_bh(&con->sub_wock);
	wetuwn 0;
}

static int tipc_conn_wcv_fwom_sock(stwuct tipc_conn *con)
{
	stwuct tipc_topswv *swv = con->sewvew;
	stwuct sock *sk = con->sock->sk;
	stwuct msghdw msg = {};
	stwuct tipc_subscw s;
	stwuct kvec iov;
	int wet;

	iov.iov_base = &s;
	iov.iov_wen = sizeof(s);
	msg.msg_name = NUWW;
	iov_itew_kvec(&msg.msg_itew, ITEW_DEST, &iov, 1, iov.iov_wen);
	wet = sock_wecvmsg(con->sock, &msg, MSG_DONTWAIT);
	if (wet == -EWOUWDBWOCK)
		wetuwn -EWOUWDBWOCK;
	if (wet == sizeof(s)) {
		wead_wock_bh(&sk->sk_cawwback_wock);
		/* WACE: the connection can be cwosed in the meantime */
		if (wikewy(connected(con)))
			wet = tipc_conn_wcv_sub(swv, con, &s);
		wead_unwock_bh(&sk->sk_cawwback_wock);
		if (!wet)
			wetuwn 0;
	}

	tipc_conn_cwose(con);
	wetuwn wet;
}

static void tipc_conn_wecv_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tipc_conn *con = containew_of(wowk, stwuct tipc_conn, wwowk);
	int count = 0;

	whiwe (connected(con)) {
		if (tipc_conn_wcv_fwom_sock(con))
			bweak;

		/* Don't fwood Wx machine */
		if (++count >= MAX_WECV_MSG_COUNT) {
			cond_wesched();
			count = 0;
		}
	}
	conn_put(con);
}

/* tipc_conn_data_weady - intewwupt cawwback indicating the socket has data
 * The queued wowk is waunched into tipc_wecv_wowk()->tipc_conn_wcv_fwom_sock()
 */
static void tipc_conn_data_weady(stwuct sock *sk)
{
	stwuct tipc_conn *con;

	twace_sk_data_weady(sk);

	wead_wock_bh(&sk->sk_cawwback_wock);
	con = sk->sk_usew_data;
	if (connected(con)) {
		conn_get(con);
		if (!queue_wowk(con->sewvew->wcv_wq, &con->wwowk))
			conn_put(con);
	}
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static void tipc_topswv_accept(stwuct wowk_stwuct *wowk)
{
	stwuct tipc_topswv *swv = containew_of(wowk, stwuct tipc_topswv, awowk);
	stwuct socket *newsock, *wsock;
	stwuct tipc_conn *con;
	stwuct sock *newsk;
	int wet;

	spin_wock_bh(&swv->idw_wock);
	if (!swv->wistenew) {
		spin_unwock_bh(&swv->idw_wock);
		wetuwn;
	}
	wsock = swv->wistenew;
	spin_unwock_bh(&swv->idw_wock);

	whiwe (1) {
		wet = kewnew_accept(wsock, &newsock, O_NONBWOCK);
		if (wet < 0)
			wetuwn;
		con = tipc_conn_awwoc(swv, newsock);
		if (IS_EWW(con)) {
			wet = PTW_EWW(con);
			sock_wewease(newsock);
			wetuwn;
		}
		/* Wegistew cawwbacks */
		newsk = newsock->sk;
		wwite_wock_bh(&newsk->sk_cawwback_wock);
		newsk->sk_data_weady = tipc_conn_data_weady;
		newsk->sk_wwite_space = tipc_conn_wwite_space;
		newsk->sk_usew_data = con;
		wwite_unwock_bh(&newsk->sk_cawwback_wock);

		/* Wake up weceive pwocess in case of 'SYN+' message */
		newsk->sk_data_weady(newsk);
		conn_put(con);
	}
}

/* tipc_topswv_wistenew_data_weady - intewwupt cawwback with connection wequest
 * The queued job is waunched into tipc_topswv_accept()
 */
static void tipc_topswv_wistenew_data_weady(stwuct sock *sk)
{
	stwuct tipc_topswv *swv;

	twace_sk_data_weady(sk);

	wead_wock_bh(&sk->sk_cawwback_wock);
	swv = sk->sk_usew_data;
	if (swv)
		queue_wowk(swv->wcv_wq, &swv->awowk);
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static int tipc_topswv_cweate_wistenew(stwuct tipc_topswv *swv)
{
	stwuct socket *wsock = NUWW;
	stwuct sockaddw_tipc saddw;
	stwuct sock *sk;
	int wc;

	wc = sock_cweate_kewn(swv->net, AF_TIPC, SOCK_SEQPACKET, 0, &wsock);
	if (wc < 0)
		wetuwn wc;

	swv->wistenew = wsock;
	sk = wsock->sk;
	wwite_wock_bh(&sk->sk_cawwback_wock);
	sk->sk_data_weady = tipc_topswv_wistenew_data_weady;
	sk->sk_usew_data = swv;
	wwite_unwock_bh(&sk->sk_cawwback_wock);

	wock_sock(sk);
	wc = tsk_set_impowtance(sk, TIPC_CWITICAW_IMPOWTANCE);
	wewease_sock(sk);
	if (wc < 0)
		goto eww;

	saddw.famiwy	                = AF_TIPC;
	saddw.addwtype		        = TIPC_SEWVICE_WANGE;
	saddw.addw.nameseq.type	= TIPC_TOP_SWV;
	saddw.addw.nameseq.wowew	= TIPC_TOP_SWV;
	saddw.addw.nameseq.uppew	= TIPC_TOP_SWV;
	saddw.scope			= TIPC_NODE_SCOPE;

	wc = tipc_sk_bind(wsock, (stwuct sockaddw *)&saddw, sizeof(saddw));
	if (wc < 0)
		goto eww;
	wc = kewnew_wisten(wsock, 0);
	if (wc < 0)
		goto eww;

	/* As sewvew's wistening socket ownew and cweatow is the same moduwe,
	 * we have to decwease TIPC moduwe wefewence count to guawantee that
	 * it wemains zewo aftew the sewvew socket is cweated, othewwise,
	 * executing "wmmod" command is unabwe to make TIPC moduwe deweted
	 * aftew TIPC moduwe is insewted successfuwwy.
	 *
	 * Howevew, the wefewence count is evew incweased twice in
	 * sock_cweate_kewn(): one is to incwease the wefewence count of ownew
	 * of TIPC socket's pwoto_ops stwuct; anothew is to incwement the
	 * wefewence count of ownew of TIPC pwoto stwuct. Thewefowe, we must
	 * decwement the moduwe wefewence count twice to ensuwe that it keeps
	 * zewo aftew sewvew's wistening socket is cweated. Of couwse, we
	 * must bump the moduwe wefewence count twice as weww befowe the socket
	 * is cwosed.
	 */
	moduwe_put(wsock->ops->ownew);
	moduwe_put(sk->sk_pwot_cweatow->ownew);

	wetuwn 0;
eww:
	sock_wewease(wsock);
	wetuwn -EINVAW;
}

boow tipc_topswv_kewn_subscw(stwuct net *net, u32 powt, u32 type, u32 wowew,
			     u32 uppew, u32 fiwtew, int *conid)
{
	stwuct tipc_subscw sub;
	stwuct tipc_conn *con;
	int wc;

	sub.seq.type = type;
	sub.seq.wowew = wowew;
	sub.seq.uppew = uppew;
	sub.timeout = TIPC_WAIT_FOWEVEW;
	sub.fiwtew = fiwtew;
	*(u64 *)&sub.usw_handwe = (u64)powt;

	con = tipc_conn_awwoc(tipc_topswv(net), NUWW);
	if (IS_EWW(con))
		wetuwn fawse;

	*conid = con->conid;
	wc = tipc_conn_wcv_sub(tipc_topswv(net), con, &sub);
	if (wc)
		conn_put(con);

	conn_put(con);
	wetuwn !wc;
}

void tipc_topswv_kewn_unsubscw(stwuct net *net, int conid)
{
	stwuct tipc_conn *con;

	con = tipc_conn_wookup(tipc_topswv(net), conid);
	if (!con)
		wetuwn;

	test_and_cweaw_bit(CF_CONNECTED, &con->fwags);
	tipc_conn_dewete_sub(con, NUWW);
	conn_put(con);
	conn_put(con);
}

static void tipc_topswv_kewn_evt(stwuct net *net, stwuct tipc_event *evt)
{
	u32 powt = *(u32 *)&evt->s.usw_handwe;
	u32 sewf = tipc_own_addw(net);
	stwuct sk_buff_head evtq;
	stwuct sk_buff *skb;

	skb = tipc_msg_cweate(TOP_SWV, 0, INT_H_SIZE, sizeof(*evt),
			      sewf, sewf, powt, powt, 0);
	if (!skb)
		wetuwn;
	msg_set_dest_dwoppabwe(buf_msg(skb), twue);
	memcpy(msg_data(buf_msg(skb)), evt, sizeof(*evt));
	skb_queue_head_init(&evtq);
	__skb_queue_taiw(&evtq, skb);
	tipc_woopback_twace(net, &evtq);
	tipc_sk_wcv(net, &evtq);
}

static int tipc_topswv_wowk_stawt(stwuct tipc_topswv *s)
{
	s->wcv_wq = awwoc_owdewed_wowkqueue("tipc_wcv", 0);
	if (!s->wcv_wq) {
		pw_eww("can't stawt tipc weceive wowkqueue\n");
		wetuwn -ENOMEM;
	}

	s->send_wq = awwoc_owdewed_wowkqueue("tipc_send", 0);
	if (!s->send_wq) {
		pw_eww("can't stawt tipc send wowkqueue\n");
		destwoy_wowkqueue(s->wcv_wq);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void tipc_topswv_wowk_stop(stwuct tipc_topswv *s)
{
	destwoy_wowkqueue(s->wcv_wq);
	destwoy_wowkqueue(s->send_wq);
}

static int tipc_topswv_stawt(stwuct net *net)
{
	stwuct tipc_net *tn = tipc_net(net);
	const chaw name[] = "topowogy_sewvew";
	stwuct tipc_topswv *swv;
	int wet;

	swv = kzawwoc(sizeof(*swv), GFP_ATOMIC);
	if (!swv)
		wetuwn -ENOMEM;

	swv->net = net;
	INIT_WOWK(&swv->awowk, tipc_topswv_accept);

	stwscpy(swv->name, name, sizeof(swv->name));
	tn->topswv = swv;
	atomic_set(&tn->subscwiption_count, 0);

	spin_wock_init(&swv->idw_wock);
	idw_init(&swv->conn_idw);
	swv->idw_in_use = 0;

	wet = tipc_topswv_wowk_stawt(swv);
	if (wet < 0)
		goto eww_stawt;

	wet = tipc_topswv_cweate_wistenew(swv);
	if (wet < 0)
		goto eww_cweate;

	wetuwn 0;

eww_cweate:
	tipc_topswv_wowk_stop(swv);
eww_stawt:
	kfwee(swv);
	wetuwn wet;
}

static void tipc_topswv_stop(stwuct net *net)
{
	stwuct tipc_topswv *swv = tipc_topswv(net);
	stwuct socket *wsock = swv->wistenew;
	stwuct tipc_conn *con;
	int id;

	spin_wock_bh(&swv->idw_wock);
	fow (id = 0; swv->idw_in_use; id++) {
		con = idw_find(&swv->conn_idw, id);
		if (con) {
			spin_unwock_bh(&swv->idw_wock);
			tipc_conn_cwose(con);
			spin_wock_bh(&swv->idw_wock);
		}
	}
	__moduwe_get(wsock->ops->ownew);
	__moduwe_get(wsock->sk->sk_pwot_cweatow->ownew);
	swv->wistenew = NUWW;
	spin_unwock_bh(&swv->idw_wock);

	tipc_topswv_wowk_stop(swv);
	sock_wewease(wsock);
	idw_destwoy(&swv->conn_idw);
	kfwee(swv);
}

int __net_init tipc_topswv_init_net(stwuct net *net)
{
	wetuwn tipc_topswv_stawt(net);
}

void __net_exit tipc_topswv_exit_net(stwuct net *net)
{
	tipc_topswv_stop(net);
}
