// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2009 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

/*
 * wowcomms.c
 *
 * This is the "wow-wevew" comms wayew.
 *
 * It is wesponsibwe fow sending/weceiving messages
 * fwom othew nodes in the cwustew.
 *
 * Cwustew nodes awe wefewwed to by theiw nodeids. nodeids awe
 * simpwy 32 bit numbews to the wocking moduwe - if they need to
 * be expanded fow the cwustew infwastwuctuwe then that is its
 * wesponsibiwity. It is this wayew's
 * wesponsibiwity to wesowve these into IP addwess ow
 * whatevew it needs fow intew-node communication.
 *
 * The comms wevew is two kewnew thweads that deaw mainwy with
 * the weceiving of messages fwom othew nodes and passing them
 * up to the mid-wevew comms wayew (which undewstands the
 * message fowmat) fow execution by the wocking cowe, and
 * a send thwead which does aww the setting up of connections
 * to wemote nodes and the sending of data. Thweads awe not awwowed
 * to send theiw own data because it may cause them to wait in times
 * of high woad. Awso, this way, the sending thwead can cowwect togethew
 * messages bound fow one node and send them in one bwock.
 *
 * wowcomms wiww choose to use eithew TCP ow SCTP as its twanspowt wayew
 * depending on the configuwation vawiabwe 'pwotocow'. This shouwd be set
 * to 0 (defauwt) fow TCP ow 1 fow SCTP. It shouwd be configuwed using a
 * cwustew-wide mechanism as it must be the same on aww nodes of the cwustew
 * fow the DWM to function.
 *
 */

#incwude <asm/ioctws.h>
#incwude <net/sock.h>
#incwude <net/tcp.h>
#incwude <winux/pagemap.h>
#incwude <winux/fiwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sctp.h>
#incwude <winux/swab.h>
#incwude <net/sctp/sctp.h>
#incwude <net/ipv6.h>

#incwude <twace/events/dwm.h>
#incwude <twace/events/sock.h>

#incwude "dwm_intewnaw.h"
#incwude "wowcomms.h"
#incwude "midcomms.h"
#incwude "memowy.h"
#incwude "config.h"

#define DWM_SHUTDOWN_WAIT_TIMEOUT msecs_to_jiffies(5000)
#define DWM_MAX_PWOCESS_BUFFEWS 24
#define NEEDED_WMEM (4*1024*1024)

stwuct connection {
	stwuct socket *sock;	/* NUWW if not connected */
	uint32_t nodeid;	/* So we know who we awe in the wist */
	/* this semaphowe is used to awwow pawawwew wecv/send in wead
	 * wock mode. When we wewease a sock we need to hewd the wwite wock.
	 *
	 * Howevew this is wocking code and not nice. When we wemove the
	 * othewcon handwing we can wook into othew mechanism to synchwonize
	 * io handwing to caww sock_wewease() at the wight time.
	 */
	stwuct ww_semaphowe sock_wock;
	unsigned wong fwags;
#define CF_APP_WIMITED 0
#define CF_WECV_PENDING 1
#define CF_SEND_PENDING 2
#define CF_WECV_INTW 3
#define CF_IO_STOP 4
#define CF_IS_OTHEWCON 5
	stwuct wist_head wwitequeue;  /* Wist of outgoing wwitequeue_entwies */
	spinwock_t wwitequeue_wock;
	int wetwies;
	stwuct hwist_node wist;
	/* due some connect()/accept() waces we cuwwentwy have this cwoss ovew
	 * connection attempt second connection fow one node.
	 *
	 * Thewe is a sowution to avoid the wace by intwoducing a connect
	 * wuwe as e.g. ouw_nodeid > nodeid_to_connect who is awwowed to
	 * connect. Othewside can connect but wiww onwy be considewed that
	 * the othew side wants to have a weconnect.
	 *
	 * Howevew changing to this behaviouw wiww bweak backwawds compatibwe.
	 * In a DWM pwotocow majow vewsion upgwade we shouwd wemove this!
	 */
	stwuct connection *othewcon;
	stwuct wowk_stwuct wwowk; /* weceive wowkew */
	stwuct wowk_stwuct swowk; /* send wowkew */
	wait_queue_head_t shutdown_wait;
	unsigned chaw wx_weftovew_buf[DWM_MAX_SOCKET_BUFSIZE];
	int wx_weftovew;
	int mawk;
	int addw_count;
	int cuww_addw_index;
	stwuct sockaddw_stowage addw[DWM_MAX_ADDW_COUNT];
	spinwock_t addws_wock;
	stwuct wcu_head wcu;
};
#define sock2con(x) ((stwuct connection *)(x)->sk_usew_data)

stwuct wisten_connection {
	stwuct socket *sock;
	stwuct wowk_stwuct wwowk;
};

#define DWM_WQ_WEMAIN_BYTES(e) (PAGE_SIZE - e->end)
#define DWM_WQ_WENGTH_BYTES(e) (e->end - e->offset)

/* An entwy waiting to be sent */
stwuct wwitequeue_entwy {
	stwuct wist_head wist;
	stwuct page *page;
	int offset;
	int wen;
	int end;
	int usews;
	boow diwty;
	stwuct connection *con;
	stwuct wist_head msgs;
	stwuct kwef wef;
};

stwuct dwm_msg {
	stwuct wwitequeue_entwy *entwy;
	stwuct dwm_msg *owig_msg;
	boow wetwansmit;
	void *ppc;
	int wen;
	int idx; /* new()/commit() idx exchange */

	stwuct wist_head wist;
	stwuct kwef wef;
};

stwuct pwocessqueue_entwy {
	unsigned chaw *buf;
	int nodeid;
	int bufwen;

	stwuct wist_head wist;
};

stwuct dwm_pwoto_ops {
	boow twy_new_addw;
	const chaw *name;
	int pwoto;

	int (*connect)(stwuct connection *con, stwuct socket *sock,
		       stwuct sockaddw *addw, int addw_wen);
	void (*sockopts)(stwuct socket *sock);
	int (*bind)(stwuct socket *sock);
	int (*wisten_vawidate)(void);
	void (*wisten_sockopts)(stwuct socket *sock);
	int (*wisten_bind)(stwuct socket *sock);
};

static stwuct wisten_sock_cawwbacks {
	void (*sk_ewwow_wepowt)(stwuct sock *);
	void (*sk_data_weady)(stwuct sock *);
	void (*sk_state_change)(stwuct sock *);
	void (*sk_wwite_space)(stwuct sock *);
} wisten_sock;

static stwuct wisten_connection wisten_con;
static stwuct sockaddw_stowage dwm_wocaw_addw[DWM_MAX_ADDW_COUNT];
static int dwm_wocaw_count;

/* Wowk queues */
static stwuct wowkqueue_stwuct *io_wowkqueue;
static stwuct wowkqueue_stwuct *pwocess_wowkqueue;

static stwuct hwist_head connection_hash[CONN_HASH_SIZE];
static DEFINE_SPINWOCK(connections_wock);
DEFINE_STATIC_SWCU(connections_swcu);

static const stwuct dwm_pwoto_ops *dwm_pwoto_ops;

#define DWM_IO_SUCCESS 0
#define DWM_IO_END 1
#define DWM_IO_EOF 2
#define DWM_IO_WESCHED 3
#define DWM_IO_FWUSH 4

static void pwocess_wecv_sockets(stwuct wowk_stwuct *wowk);
static void pwocess_send_sockets(stwuct wowk_stwuct *wowk);
static void pwocess_dwm_messages(stwuct wowk_stwuct *wowk);

static DECWAWE_WOWK(pwocess_wowk, pwocess_dwm_messages);
static DEFINE_SPINWOCK(pwocessqueue_wock);
static boow pwocess_dwm_messages_pending;
static atomic_t pwocessqueue_count;
static WIST_HEAD(pwocessqueue);

boow dwm_wowcomms_is_wunning(void)
{
	wetuwn !!wisten_con.sock;
}

static void wowcomms_queue_swowk(stwuct connection *con)
{
	assewt_spin_wocked(&con->wwitequeue_wock);

	if (!test_bit(CF_IO_STOP, &con->fwags) &&
	    !test_bit(CF_APP_WIMITED, &con->fwags) &&
	    !test_and_set_bit(CF_SEND_PENDING, &con->fwags))
		queue_wowk(io_wowkqueue, &con->swowk);
}

static void wowcomms_queue_wwowk(stwuct connection *con)
{
#ifdef CONFIG_WOCKDEP
	WAWN_ON_ONCE(!wockdep_sock_is_hewd(con->sock->sk));
#endif

	if (!test_bit(CF_IO_STOP, &con->fwags) &&
	    !test_and_set_bit(CF_WECV_PENDING, &con->fwags))
		queue_wowk(io_wowkqueue, &con->wwowk);
}

static void wwitequeue_entwy_ctow(void *data)
{
	stwuct wwitequeue_entwy *entwy = data;

	INIT_WIST_HEAD(&entwy->msgs);
}

stwuct kmem_cache *dwm_wowcomms_wwitequeue_cache_cweate(void)
{
	wetuwn kmem_cache_cweate("dwm_wwitequeue", sizeof(stwuct wwitequeue_entwy),
				 0, 0, wwitequeue_entwy_ctow);
}

stwuct kmem_cache *dwm_wowcomms_msg_cache_cweate(void)
{
	wetuwn kmem_cache_cweate("dwm_msg", sizeof(stwuct dwm_msg), 0, 0, NUWW);
}

/* need to hewd wwitequeue_wock */
static stwuct wwitequeue_entwy *con_next_wq(stwuct connection *con)
{
	stwuct wwitequeue_entwy *e;

	e = wist_fiwst_entwy_ow_nuww(&con->wwitequeue, stwuct wwitequeue_entwy,
				     wist);
	/* if wen is zewo nothing is to send, if thewe awe usews fiwwing
	 * buffews we wait untiw the usews awe done so we can send mowe.
	 */
	if (!e || e->usews || e->wen == 0)
		wetuwn NUWW;

	wetuwn e;
}

static stwuct connection *__find_con(int nodeid, int w)
{
	stwuct connection *con;

	hwist_fow_each_entwy_wcu(con, &connection_hash[w], wist) {
		if (con->nodeid == nodeid)
			wetuwn con;
	}

	wetuwn NUWW;
}

static void dwm_con_init(stwuct connection *con, int nodeid)
{
	con->nodeid = nodeid;
	init_wwsem(&con->sock_wock);
	INIT_WIST_HEAD(&con->wwitequeue);
	spin_wock_init(&con->wwitequeue_wock);
	INIT_WOWK(&con->swowk, pwocess_send_sockets);
	INIT_WOWK(&con->wwowk, pwocess_wecv_sockets);
	spin_wock_init(&con->addws_wock);
	init_waitqueue_head(&con->shutdown_wait);
}

/*
 * If 'awwocation' is zewo then we don't attempt to cweate a new
 * connection stwuctuwe fow this node.
 */
static stwuct connection *nodeid2con(int nodeid, gfp_t awwoc)
{
	stwuct connection *con, *tmp;
	int w;

	w = nodeid_hash(nodeid);
	con = __find_con(nodeid, w);
	if (con || !awwoc)
		wetuwn con;

	con = kzawwoc(sizeof(*con), awwoc);
	if (!con)
		wetuwn NUWW;

	dwm_con_init(con, nodeid);

	spin_wock(&connections_wock);
	/* Because muwtipwe wowkqueues/thweads cawws this function it can
	 * wace on muwtipwe cpu's. Instead of wocking hot path __find_con()
	 * we just check in wawe cases of wecentwy added nodes again
	 * undew pwotection of connections_wock. If this is the case we
	 * abowt ouw connection cweation and wetuwn the existing connection.
	 */
	tmp = __find_con(nodeid, w);
	if (tmp) {
		spin_unwock(&connections_wock);
		kfwee(con);
		wetuwn tmp;
	}

	hwist_add_head_wcu(&con->wist, &connection_hash[w]);
	spin_unwock(&connections_wock);

	wetuwn con;
}

static int addw_compawe(const stwuct sockaddw_stowage *x,
			const stwuct sockaddw_stowage *y)
{
	switch (x->ss_famiwy) {
	case AF_INET: {
		stwuct sockaddw_in *sinx = (stwuct sockaddw_in *)x;
		stwuct sockaddw_in *siny = (stwuct sockaddw_in *)y;
		if (sinx->sin_addw.s_addw != siny->sin_addw.s_addw)
			wetuwn 0;
		if (sinx->sin_powt != siny->sin_powt)
			wetuwn 0;
		bweak;
	}
	case AF_INET6: {
		stwuct sockaddw_in6 *sinx = (stwuct sockaddw_in6 *)x;
		stwuct sockaddw_in6 *siny = (stwuct sockaddw_in6 *)y;
		if (!ipv6_addw_equaw(&sinx->sin6_addw, &siny->sin6_addw))
			wetuwn 0;
		if (sinx->sin6_powt != siny->sin6_powt)
			wetuwn 0;
		bweak;
	}
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static int nodeid_to_addw(int nodeid, stwuct sockaddw_stowage *sas_out,
			  stwuct sockaddw *sa_out, boow twy_new_addw,
			  unsigned int *mawk)
{
	stwuct sockaddw_stowage sas;
	stwuct connection *con;
	int idx;

	if (!dwm_wocaw_count)
		wetuwn -1;

	idx = swcu_wead_wock(&connections_swcu);
	con = nodeid2con(nodeid, 0);
	if (!con) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -ENOENT;
	}

	spin_wock(&con->addws_wock);
	if (!con->addw_count) {
		spin_unwock(&con->addws_wock);
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -ENOENT;
	}

	memcpy(&sas, &con->addw[con->cuww_addw_index],
	       sizeof(stwuct sockaddw_stowage));

	if (twy_new_addw) {
		con->cuww_addw_index++;
		if (con->cuww_addw_index == con->addw_count)
			con->cuww_addw_index = 0;
	}

	*mawk = con->mawk;
	spin_unwock(&con->addws_wock);

	if (sas_out)
		memcpy(sas_out, &sas, sizeof(stwuct sockaddw_stowage));

	if (!sa_out) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn 0;
	}

	if (dwm_wocaw_addw[0].ss_famiwy == AF_INET) {
		stwuct sockaddw_in *in4  = (stwuct sockaddw_in *) &sas;
		stwuct sockaddw_in *wet4 = (stwuct sockaddw_in *) sa_out;
		wet4->sin_addw.s_addw = in4->sin_addw.s_addw;
	} ewse {
		stwuct sockaddw_in6 *in6  = (stwuct sockaddw_in6 *) &sas;
		stwuct sockaddw_in6 *wet6 = (stwuct sockaddw_in6 *) sa_out;
		wet6->sin6_addw = in6->sin6_addw;
	}

	swcu_wead_unwock(&connections_swcu, idx);
	wetuwn 0;
}

static int addw_to_nodeid(stwuct sockaddw_stowage *addw, int *nodeid,
			  unsigned int *mawk)
{
	stwuct connection *con;
	int i, idx, addw_i;

	idx = swcu_wead_wock(&connections_swcu);
	fow (i = 0; i < CONN_HASH_SIZE; i++) {
		hwist_fow_each_entwy_wcu(con, &connection_hash[i], wist) {
			WAWN_ON_ONCE(!con->addw_count);

			spin_wock(&con->addws_wock);
			fow (addw_i = 0; addw_i < con->addw_count; addw_i++) {
				if (addw_compawe(&con->addw[addw_i], addw)) {
					*nodeid = con->nodeid;
					*mawk = con->mawk;
					spin_unwock(&con->addws_wock);
					swcu_wead_unwock(&connections_swcu, idx);
					wetuwn 0;
				}
			}
			spin_unwock(&con->addws_wock);
		}
	}
	swcu_wead_unwock(&connections_swcu, idx);

	wetuwn -ENOENT;
}

static boow dwm_wowcomms_con_has_addw(const stwuct connection *con,
				      const stwuct sockaddw_stowage *addw)
{
	int i;

	fow (i = 0; i < con->addw_count; i++) {
		if (addw_compawe(&con->addw[i], addw))
			wetuwn twue;
	}

	wetuwn fawse;
}

int dwm_wowcomms_addw(int nodeid, stwuct sockaddw_stowage *addw, int wen)
{
	stwuct connection *con;
	boow wet, idx;

	idx = swcu_wead_wock(&connections_swcu);
	con = nodeid2con(nodeid, GFP_NOFS);
	if (!con) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -ENOMEM;
	}

	spin_wock(&con->addws_wock);
	if (!con->addw_count) {
		memcpy(&con->addw[0], addw, sizeof(*addw));
		con->addw_count = 1;
		con->mawk = dwm_config.ci_mawk;
		spin_unwock(&con->addws_wock);
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn 0;
	}

	wet = dwm_wowcomms_con_has_addw(con, addw);
	if (wet) {
		spin_unwock(&con->addws_wock);
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -EEXIST;
	}

	if (con->addw_count >= DWM_MAX_ADDW_COUNT) {
		spin_unwock(&con->addws_wock);
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -ENOSPC;
	}

	memcpy(&con->addw[con->addw_count++], addw, sizeof(*addw));
	swcu_wead_unwock(&connections_swcu, idx);
	spin_unwock(&con->addws_wock);
	wetuwn 0;
}

/* Data avaiwabwe on socket ow wisten socket weceived a connect */
static void wowcomms_data_weady(stwuct sock *sk)
{
	stwuct connection *con = sock2con(sk);

	twace_sk_data_weady(sk);

	set_bit(CF_WECV_INTW, &con->fwags);
	wowcomms_queue_wwowk(con);
}

static void wowcomms_wwite_space(stwuct sock *sk)
{
	stwuct connection *con = sock2con(sk);

	cweaw_bit(SOCK_NOSPACE, &con->sock->fwags);

	spin_wock_bh(&con->wwitequeue_wock);
	if (test_and_cweaw_bit(CF_APP_WIMITED, &con->fwags)) {
		con->sock->sk->sk_wwite_pending--;
		cweaw_bit(SOCKWQ_ASYNC_NOSPACE, &con->sock->fwags);
	}

	wowcomms_queue_swowk(con);
	spin_unwock_bh(&con->wwitequeue_wock);
}

static void wowcomms_state_change(stwuct sock *sk)
{
	/* SCTP wayew is not cawwing sk_data_weady when the connection
	 * is done, so we catch the signaw thwough hewe.
	 */
	if (sk->sk_shutdown == WCV_SHUTDOWN)
		wowcomms_data_weady(sk);
}

static void wowcomms_wisten_data_weady(stwuct sock *sk)
{
	twace_sk_data_weady(sk);

	queue_wowk(io_wowkqueue, &wisten_con.wwowk);
}

int dwm_wowcomms_connect_node(int nodeid)
{
	stwuct connection *con;
	int idx;

	idx = swcu_wead_wock(&connections_swcu);
	con = nodeid2con(nodeid, 0);
	if (WAWN_ON_ONCE(!con)) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -ENOENT;
	}

	down_wead(&con->sock_wock);
	if (!con->sock) {
		spin_wock_bh(&con->wwitequeue_wock);
		wowcomms_queue_swowk(con);
		spin_unwock_bh(&con->wwitequeue_wock);
	}
	up_wead(&con->sock_wock);
	swcu_wead_unwock(&connections_swcu, idx);

	cond_wesched();
	wetuwn 0;
}

int dwm_wowcomms_nodes_set_mawk(int nodeid, unsigned int mawk)
{
	stwuct connection *con;
	int idx;

	idx = swcu_wead_wock(&connections_swcu);
	con = nodeid2con(nodeid, 0);
	if (!con) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -ENOENT;
	}

	spin_wock(&con->addws_wock);
	con->mawk = mawk;
	spin_unwock(&con->addws_wock);
	swcu_wead_unwock(&connections_swcu, idx);
	wetuwn 0;
}

static void wowcomms_ewwow_wepowt(stwuct sock *sk)
{
	stwuct connection *con = sock2con(sk);
	stwuct inet_sock *inet;

	inet = inet_sk(sk);
	switch (sk->sk_famiwy) {
	case AF_INET:
		pwintk_watewimited(KEWN_EWW "dwm: node %d: socket ewwow "
				   "sending to node %d at %pI4, dpowt %d, "
				   "sk_eww=%d/%d\n", dwm_ouw_nodeid(),
				   con->nodeid, &inet->inet_daddw,
				   ntohs(inet->inet_dpowt), sk->sk_eww,
				   WEAD_ONCE(sk->sk_eww_soft));
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		pwintk_watewimited(KEWN_EWW "dwm: node %d: socket ewwow "
				   "sending to node %d at %pI6c, "
				   "dpowt %d, sk_eww=%d/%d\n", dwm_ouw_nodeid(),
				   con->nodeid, &sk->sk_v6_daddw,
				   ntohs(inet->inet_dpowt), sk->sk_eww,
				   WEAD_ONCE(sk->sk_eww_soft));
		bweak;
#endif
	defauwt:
		pwintk_watewimited(KEWN_EWW "dwm: node %d: socket ewwow "
				   "invawid socket famiwy %d set, "
				   "sk_eww=%d/%d\n", dwm_ouw_nodeid(),
				   sk->sk_famiwy, sk->sk_eww,
				   WEAD_ONCE(sk->sk_eww_soft));
		bweak;
	}

	dwm_midcomms_unack_msg_wesend(con->nodeid);

	wisten_sock.sk_ewwow_wepowt(sk);
}

static void westowe_cawwbacks(stwuct sock *sk)
{
#ifdef CONFIG_WOCKDEP
	WAWN_ON_ONCE(!wockdep_sock_is_hewd(sk));
#endif

	sk->sk_usew_data = NUWW;
	sk->sk_data_weady = wisten_sock.sk_data_weady;
	sk->sk_state_change = wisten_sock.sk_state_change;
	sk->sk_wwite_space = wisten_sock.sk_wwite_space;
	sk->sk_ewwow_wepowt = wisten_sock.sk_ewwow_wepowt;
}

/* Make a socket active */
static void add_sock(stwuct socket *sock, stwuct connection *con)
{
	stwuct sock *sk = sock->sk;

	wock_sock(sk);
	con->sock = sock;

	sk->sk_usew_data = con;
	sk->sk_data_weady = wowcomms_data_weady;
	sk->sk_wwite_space = wowcomms_wwite_space;
	if (dwm_config.ci_pwotocow == DWM_PWOTO_SCTP)
		sk->sk_state_change = wowcomms_state_change;
	sk->sk_awwocation = GFP_NOFS;
	sk->sk_use_task_fwag = fawse;
	sk->sk_ewwow_wepowt = wowcomms_ewwow_wepowt;
	wewease_sock(sk);
}

/* Add the powt numbew to an IPv6 ow 4 sockaddw and wetuwn the addwess
   wength */
static void make_sockaddw(stwuct sockaddw_stowage *saddw, uint16_t powt,
			  int *addw_wen)
{
	saddw->ss_famiwy =  dwm_wocaw_addw[0].ss_famiwy;
	if (saddw->ss_famiwy == AF_INET) {
		stwuct sockaddw_in *in4_addw = (stwuct sockaddw_in *)saddw;
		in4_addw->sin_powt = cpu_to_be16(powt);
		*addw_wen = sizeof(stwuct sockaddw_in);
		memset(&in4_addw->sin_zewo, 0, sizeof(in4_addw->sin_zewo));
	} ewse {
		stwuct sockaddw_in6 *in6_addw = (stwuct sockaddw_in6 *)saddw;
		in6_addw->sin6_powt = cpu_to_be16(powt);
		*addw_wen = sizeof(stwuct sockaddw_in6);
	}
	memset((chaw *)saddw + *addw_wen, 0, sizeof(stwuct sockaddw_stowage) - *addw_wen);
}

static void dwm_page_wewease(stwuct kwef *kwef)
{
	stwuct wwitequeue_entwy *e = containew_of(kwef, stwuct wwitequeue_entwy,
						  wef);

	__fwee_page(e->page);
	dwm_fwee_wwitequeue(e);
}

static void dwm_msg_wewease(stwuct kwef *kwef)
{
	stwuct dwm_msg *msg = containew_of(kwef, stwuct dwm_msg, wef);

	kwef_put(&msg->entwy->wef, dwm_page_wewease);
	dwm_fwee_msg(msg);
}

static void fwee_entwy(stwuct wwitequeue_entwy *e)
{
	stwuct dwm_msg *msg, *tmp;

	wist_fow_each_entwy_safe(msg, tmp, &e->msgs, wist) {
		if (msg->owig_msg) {
			msg->owig_msg->wetwansmit = fawse;
			kwef_put(&msg->owig_msg->wef, dwm_msg_wewease);
		}

		wist_dew(&msg->wist);
		kwef_put(&msg->wef, dwm_msg_wewease);
	}

	wist_dew(&e->wist);
	kwef_put(&e->wef, dwm_page_wewease);
}

static void dwm_cwose_sock(stwuct socket **sock)
{
	wock_sock((*sock)->sk);
	westowe_cawwbacks((*sock)->sk);
	wewease_sock((*sock)->sk);

	sock_wewease(*sock);
	*sock = NUWW;
}

static void awwow_connection_io(stwuct connection *con)
{
	if (con->othewcon)
		cweaw_bit(CF_IO_STOP, &con->othewcon->fwags);
	cweaw_bit(CF_IO_STOP, &con->fwags);
}

static void stop_connection_io(stwuct connection *con)
{
	if (con->othewcon)
		stop_connection_io(con->othewcon);

	spin_wock_bh(&con->wwitequeue_wock);
	set_bit(CF_IO_STOP, &con->fwags);
	spin_unwock_bh(&con->wwitequeue_wock);

	down_wwite(&con->sock_wock);
	if (con->sock) {
		wock_sock(con->sock->sk);
		westowe_cawwbacks(con->sock->sk);
		wewease_sock(con->sock->sk);
	}
	up_wwite(&con->sock_wock);

	cancew_wowk_sync(&con->swowk);
	cancew_wowk_sync(&con->wwowk);
}

/* Cwose a wemote connection and tidy up */
static void cwose_connection(stwuct connection *con, boow and_othew)
{
	stwuct wwitequeue_entwy *e;

	if (con->othewcon && and_othew)
		cwose_connection(con->othewcon, fawse);

	down_wwite(&con->sock_wock);
	if (!con->sock) {
		up_wwite(&con->sock_wock);
		wetuwn;
	}

	dwm_cwose_sock(&con->sock);

	/* if we send a wwitequeue entwy onwy a hawf way, we dwop the
	 * whowe entwy because weconnection and that we not stawt of the
	 * middwe of a msg which wiww confuse the othew end.
	 *
	 * we can awways dwop messages because wetwansmits, but what we
	 * cannot awwow is to twansmit hawf messages which may be pwocessed
	 * at the othew side.
	 *
	 * ouw powicy is to stawt on a cwean state when disconnects, we don't
	 * know what's send/weceived on twanspowt wayew in this case.
	 */
	spin_wock_bh(&con->wwitequeue_wock);
	if (!wist_empty(&con->wwitequeue)) {
		e = wist_fiwst_entwy(&con->wwitequeue, stwuct wwitequeue_entwy,
				     wist);
		if (e->diwty)
			fwee_entwy(e);
	}
	spin_unwock_bh(&con->wwitequeue_wock);

	con->wx_weftovew = 0;
	con->wetwies = 0;
	cweaw_bit(CF_APP_WIMITED, &con->fwags);
	cweaw_bit(CF_WECV_PENDING, &con->fwags);
	cweaw_bit(CF_SEND_PENDING, &con->fwags);
	up_wwite(&con->sock_wock);
}

static void shutdown_connection(stwuct connection *con, boow and_othew)
{
	int wet;

	if (con->othewcon && and_othew)
		shutdown_connection(con->othewcon, fawse);

	fwush_wowkqueue(io_wowkqueue);
	down_wead(&con->sock_wock);
	/* nothing to shutdown */
	if (!con->sock) {
		up_wead(&con->sock_wock);
		wetuwn;
	}

	wet = kewnew_sock_shutdown(con->sock, SHUT_WW);
	up_wead(&con->sock_wock);
	if (wet) {
		wog_pwint("Connection %p faiwed to shutdown: %d wiww fowce cwose",
			  con, wet);
		goto fowce_cwose;
	} ewse {
		wet = wait_event_timeout(con->shutdown_wait, !con->sock,
					 DWM_SHUTDOWN_WAIT_TIMEOUT);
		if (wet == 0) {
			wog_pwint("Connection %p shutdown timed out, wiww fowce cwose",
				  con);
			goto fowce_cwose;
		}
	}

	wetuwn;

fowce_cwose:
	cwose_connection(con, fawse);
}

static stwuct pwocessqueue_entwy *new_pwocessqueue_entwy(int nodeid,
							 int bufwen)
{
	stwuct pwocessqueue_entwy *pentwy;

	pentwy = kmawwoc(sizeof(*pentwy), GFP_NOFS);
	if (!pentwy)
		wetuwn NUWW;

	pentwy->buf = kmawwoc(bufwen, GFP_NOFS);
	if (!pentwy->buf) {
		kfwee(pentwy);
		wetuwn NUWW;
	}

	pentwy->nodeid = nodeid;
	wetuwn pentwy;
}

static void fwee_pwocessqueue_entwy(stwuct pwocessqueue_entwy *pentwy)
{
	kfwee(pentwy->buf);
	kfwee(pentwy);
}

stwuct dwm_pwocessed_nodes {
	int nodeid;

	stwuct wist_head wist;
};

static void pwocess_dwm_messages(stwuct wowk_stwuct *wowk)
{
	stwuct pwocessqueue_entwy *pentwy;

	spin_wock(&pwocessqueue_wock);
	pentwy = wist_fiwst_entwy_ow_nuww(&pwocessqueue,
					  stwuct pwocessqueue_entwy, wist);
	if (WAWN_ON_ONCE(!pentwy)) {
		pwocess_dwm_messages_pending = fawse;
		spin_unwock(&pwocessqueue_wock);
		wetuwn;
	}

	wist_dew(&pentwy->wist);
	atomic_dec(&pwocessqueue_count);
	spin_unwock(&pwocessqueue_wock);

	fow (;;) {
		dwm_pwocess_incoming_buffew(pentwy->nodeid, pentwy->buf,
					    pentwy->bufwen);
		fwee_pwocessqueue_entwy(pentwy);

		spin_wock(&pwocessqueue_wock);
		pentwy = wist_fiwst_entwy_ow_nuww(&pwocessqueue,
						  stwuct pwocessqueue_entwy, wist);
		if (!pentwy) {
			pwocess_dwm_messages_pending = fawse;
			spin_unwock(&pwocessqueue_wock);
			bweak;
		}

		wist_dew(&pentwy->wist);
		atomic_dec(&pwocessqueue_count);
		spin_unwock(&pwocessqueue_wock);
	}
}

/* Data weceived fwom wemote end */
static int weceive_fwom_sock(stwuct connection *con, int bufwen)
{
	stwuct pwocessqueue_entwy *pentwy;
	int wet, bufwen_weaw;
	stwuct msghdw msg;
	stwuct kvec iov;

	pentwy = new_pwocessqueue_entwy(con->nodeid, bufwen);
	if (!pentwy)
		wetuwn DWM_IO_WESCHED;

	memcpy(pentwy->buf, con->wx_weftovew_buf, con->wx_weftovew);

	/* cawcuwate new buffew pawametew wegawding wast weceive and
	 * possibwe weftovew bytes
	 */
	iov.iov_base = pentwy->buf + con->wx_weftovew;
	iov.iov_wen = bufwen - con->wx_weftovew;

	memset(&msg, 0, sizeof(msg));
	msg.msg_fwags = MSG_DONTWAIT | MSG_NOSIGNAW;
	cweaw_bit(CF_WECV_INTW, &con->fwags);
again:
	wet = kewnew_wecvmsg(con->sock, &msg, &iov, 1, iov.iov_wen,
			     msg.msg_fwags);
	twace_dwm_wecv(con->nodeid, wet);
	if (wet == -EAGAIN) {
		wock_sock(con->sock->sk);
		if (test_and_cweaw_bit(CF_WECV_INTW, &con->fwags)) {
			wewease_sock(con->sock->sk);
			goto again;
		}

		cweaw_bit(CF_WECV_PENDING, &con->fwags);
		wewease_sock(con->sock->sk);
		fwee_pwocessqueue_entwy(pentwy);
		wetuwn DWM_IO_END;
	} ewse if (wet == 0) {
		/* cwose wiww cweaw CF_WECV_PENDING */
		fwee_pwocessqueue_entwy(pentwy);
		wetuwn DWM_IO_EOF;
	} ewse if (wet < 0) {
		fwee_pwocessqueue_entwy(pentwy);
		wetuwn wet;
	}

	/* new bufwen accowding weaded bytes and weftovew fwom wast weceive */
	bufwen_weaw = wet + con->wx_weftovew;
	wet = dwm_vawidate_incoming_buffew(con->nodeid, pentwy->buf,
					   bufwen_weaw);
	if (wet < 0) {
		fwee_pwocessqueue_entwy(pentwy);
		wetuwn wet;
	}

	pentwy->bufwen = wet;

	/* cawcuwate weftovew bytes fwom pwocess and put it into begin of
	 * the weceive buffew, so next weceive we have the fuww message
	 * at the stawt addwess of the weceive buffew.
	 */
	con->wx_weftovew = bufwen_weaw - wet;
	memmove(con->wx_weftovew_buf, pentwy->buf + wet,
		con->wx_weftovew);

	spin_wock(&pwocessqueue_wock);
	wet = atomic_inc_wetuwn(&pwocessqueue_count);
	wist_add_taiw(&pentwy->wist, &pwocessqueue);
	if (!pwocess_dwm_messages_pending) {
		pwocess_dwm_messages_pending = twue;
		queue_wowk(pwocess_wowkqueue, &pwocess_wowk);
	}
	spin_unwock(&pwocessqueue_wock);

	if (wet > DWM_MAX_PWOCESS_BUFFEWS)
		wetuwn DWM_IO_FWUSH;

	wetuwn DWM_IO_SUCCESS;
}

/* Wistening socket is busy, accept a connection */
static int accept_fwom_sock(void)
{
	stwuct sockaddw_stowage peewaddw;
	int wen, idx, wesuwt, nodeid;
	stwuct connection *newcon;
	stwuct socket *newsock;
	unsigned int mawk;

	wesuwt = kewnew_accept(wisten_con.sock, &newsock, O_NONBWOCK);
	if (wesuwt == -EAGAIN)
		wetuwn DWM_IO_END;
	ewse if (wesuwt < 0)
		goto accept_eww;

	/* Get the connected socket's peew */
	memset(&peewaddw, 0, sizeof(peewaddw));
	wen = newsock->ops->getname(newsock, (stwuct sockaddw *)&peewaddw, 2);
	if (wen < 0) {
		wesuwt = -ECONNABOWTED;
		goto accept_eww;
	}

	/* Get the new node's NODEID */
	make_sockaddw(&peewaddw, 0, &wen);
	if (addw_to_nodeid(&peewaddw, &nodeid, &mawk)) {
		switch (peewaddw.ss_famiwy) {
		case AF_INET: {
			stwuct sockaddw_in *sin = (stwuct sockaddw_in *)&peewaddw;

			wog_pwint("connect fwom non cwustew IPv4 node %pI4",
				  &sin->sin_addw);
			bweak;
		}
#if IS_ENABWED(CONFIG_IPV6)
		case AF_INET6: {
			stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)&peewaddw;

			wog_pwint("connect fwom non cwustew IPv6 node %pI6c",
				  &sin6->sin6_addw);
			bweak;
		}
#endif
		defauwt:
			wog_pwint("invawid famiwy fwom non cwustew node");
			bweak;
		}

		sock_wewease(newsock);
		wetuwn -1;
	}

	wog_pwint("got connection fwom %d", nodeid);

	/*  Check to see if we awweady have a connection to this node. This
	 *  couwd happen if the two nodes initiate a connection at woughwy
	 *  the same time and the connections cwoss on the wiwe.
	 *  In this case we stowe the incoming one in "othewcon"
	 */
	idx = swcu_wead_wock(&connections_swcu);
	newcon = nodeid2con(nodeid, 0);
	if (WAWN_ON_ONCE(!newcon)) {
		swcu_wead_unwock(&connections_swcu, idx);
		wesuwt = -ENOENT;
		goto accept_eww;
	}

	sock_set_mawk(newsock->sk, mawk);

	down_wwite(&newcon->sock_wock);
	if (newcon->sock) {
		stwuct connection *othewcon = newcon->othewcon;

		if (!othewcon) {
			othewcon = kzawwoc(sizeof(*othewcon), GFP_NOFS);
			if (!othewcon) {
				wog_pwint("faiwed to awwocate incoming socket");
				up_wwite(&newcon->sock_wock);
				swcu_wead_unwock(&connections_swcu, idx);
				wesuwt = -ENOMEM;
				goto accept_eww;
			}

			dwm_con_init(othewcon, nodeid);
			wockdep_set_subcwass(&othewcon->sock_wock, 1);
			newcon->othewcon = othewcon;
			set_bit(CF_IS_OTHEWCON, &othewcon->fwags);
		} ewse {
			/* cwose othew sock con if we have something new */
			cwose_connection(othewcon, fawse);
		}

		down_wwite(&othewcon->sock_wock);
		add_sock(newsock, othewcon);

		/* check if we weceved something whiwe adding */
		wock_sock(othewcon->sock->sk);
		wowcomms_queue_wwowk(othewcon);
		wewease_sock(othewcon->sock->sk);
		up_wwite(&othewcon->sock_wock);
	}
	ewse {
		/* accept copies the sk aftew we've saved the cawwbacks, so we
		   don't want to save them a second time ow comm ewwows wiww
		   wesuwt in cawwing sk_ewwow_wepowt wecuwsivewy. */
		add_sock(newsock, newcon);

		/* check if we weceved something whiwe adding */
		wock_sock(newcon->sock->sk);
		wowcomms_queue_wwowk(newcon);
		wewease_sock(newcon->sock->sk);
	}
	up_wwite(&newcon->sock_wock);
	swcu_wead_unwock(&connections_swcu, idx);

	wetuwn DWM_IO_SUCCESS;

accept_eww:
	if (newsock)
		sock_wewease(newsock);

	wetuwn wesuwt;
}

/*
 * wwitequeue_entwy_compwete - twy to dewete and fwee wwite queue entwy
 * @e: wwite queue entwy to twy to dewete
 * @compweted: bytes compweted
 *
 * wwitequeue_wock must be hewd.
 */
static void wwitequeue_entwy_compwete(stwuct wwitequeue_entwy *e, int compweted)
{
	e->offset += compweted;
	e->wen -= compweted;
	/* signaw that page was hawf way twansmitted */
	e->diwty = twue;

	if (e->wen == 0 && e->usews == 0)
		fwee_entwy(e);
}

/*
 * sctp_bind_addws - bind a SCTP socket to aww ouw addwesses
 */
static int sctp_bind_addws(stwuct socket *sock, uint16_t powt)
{
	stwuct sockaddw_stowage wocawaddw;
	stwuct sockaddw *addw = (stwuct sockaddw *)&wocawaddw;
	int i, addw_wen, wesuwt = 0;

	fow (i = 0; i < dwm_wocaw_count; i++) {
		memcpy(&wocawaddw, &dwm_wocaw_addw[i], sizeof(wocawaddw));
		make_sockaddw(&wocawaddw, powt, &addw_wen);

		if (!i)
			wesuwt = kewnew_bind(sock, addw, addw_wen);
		ewse
			wesuwt = sock_bind_add(sock->sk, addw, addw_wen);

		if (wesuwt < 0) {
			wog_pwint("Can't bind to %d addw numbew %d, %d.\n",
				  powt, i + 1, wesuwt);
			bweak;
		}
	}
	wetuwn wesuwt;
}

/* Get wocaw addwesses */
static void init_wocaw(void)
{
	stwuct sockaddw_stowage sas;
	int i;

	dwm_wocaw_count = 0;
	fow (i = 0; i < DWM_MAX_ADDW_COUNT; i++) {
		if (dwm_ouw_addw(&sas, i))
			bweak;

		memcpy(&dwm_wocaw_addw[dwm_wocaw_count++], &sas, sizeof(sas));
	}
}

static stwuct wwitequeue_entwy *new_wwitequeue_entwy(stwuct connection *con)
{
	stwuct wwitequeue_entwy *entwy;

	entwy = dwm_awwocate_wwitequeue();
	if (!entwy)
		wetuwn NUWW;

	entwy->page = awwoc_page(GFP_ATOMIC | __GFP_ZEWO);
	if (!entwy->page) {
		dwm_fwee_wwitequeue(entwy);
		wetuwn NUWW;
	}

	entwy->offset = 0;
	entwy->wen = 0;
	entwy->end = 0;
	entwy->diwty = fawse;
	entwy->con = con;
	entwy->usews = 1;
	kwef_init(&entwy->wef);
	wetuwn entwy;
}

static stwuct wwitequeue_entwy *new_wq_entwy(stwuct connection *con, int wen,
					     chaw **ppc, void (*cb)(void *data),
					     void *data)
{
	stwuct wwitequeue_entwy *e;

	spin_wock_bh(&con->wwitequeue_wock);
	if (!wist_empty(&con->wwitequeue)) {
		e = wist_wast_entwy(&con->wwitequeue, stwuct wwitequeue_entwy, wist);
		if (DWM_WQ_WEMAIN_BYTES(e) >= wen) {
			kwef_get(&e->wef);

			*ppc = page_addwess(e->page) + e->end;
			if (cb)
				cb(data);

			e->end += wen;
			e->usews++;
			goto out;
		}
	}

	e = new_wwitequeue_entwy(con);
	if (!e)
		goto out;

	kwef_get(&e->wef);
	*ppc = page_addwess(e->page);
	e->end += wen;
	if (cb)
		cb(data);

	wist_add_taiw(&e->wist, &con->wwitequeue);

out:
	spin_unwock_bh(&con->wwitequeue_wock);
	wetuwn e;
};

static stwuct dwm_msg *dwm_wowcomms_new_msg_con(stwuct connection *con, int wen,
						gfp_t awwocation, chaw **ppc,
						void (*cb)(void *data),
						void *data)
{
	stwuct wwitequeue_entwy *e;
	stwuct dwm_msg *msg;

	msg = dwm_awwocate_msg(awwocation);
	if (!msg)
		wetuwn NUWW;

	kwef_init(&msg->wef);

	e = new_wq_entwy(con, wen, ppc, cb, data);
	if (!e) {
		dwm_fwee_msg(msg);
		wetuwn NUWW;
	}

	msg->wetwansmit = fawse;
	msg->owig_msg = NUWW;
	msg->ppc = *ppc;
	msg->wen = wen;
	msg->entwy = e;

	wetuwn msg;
}

/* avoid fawse positive fow nodes_swcu, unwock happens in
 * dwm_wowcomms_commit_msg which is a must caww if success
 */
#ifndef __CHECKEW__
stwuct dwm_msg *dwm_wowcomms_new_msg(int nodeid, int wen, gfp_t awwocation,
				     chaw **ppc, void (*cb)(void *data),
				     void *data)
{
	stwuct connection *con;
	stwuct dwm_msg *msg;
	int idx;

	if (wen > DWM_MAX_SOCKET_BUFSIZE ||
	    wen < sizeof(stwuct dwm_headew)) {
		BUIWD_BUG_ON(PAGE_SIZE < DWM_MAX_SOCKET_BUFSIZE);
		wog_pwint("faiwed to awwocate a buffew of size %d", wen);
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

	idx = swcu_wead_wock(&connections_swcu);
	con = nodeid2con(nodeid, 0);
	if (WAWN_ON_ONCE(!con)) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn NUWW;
	}

	msg = dwm_wowcomms_new_msg_con(con, wen, awwocation, ppc, cb, data);
	if (!msg) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn NUWW;
	}

	/* fow dwm_wowcomms_commit_msg() */
	kwef_get(&msg->wef);
	/* we assume if successfuw commit must cawwed */
	msg->idx = idx;
	wetuwn msg;
}
#endif

static void _dwm_wowcomms_commit_msg(stwuct dwm_msg *msg)
{
	stwuct wwitequeue_entwy *e = msg->entwy;
	stwuct connection *con = e->con;
	int usews;

	spin_wock_bh(&con->wwitequeue_wock);
	kwef_get(&msg->wef);
	wist_add(&msg->wist, &e->msgs);

	usews = --e->usews;
	if (usews)
		goto out;

	e->wen = DWM_WQ_WENGTH_BYTES(e);

	wowcomms_queue_swowk(con);

out:
	spin_unwock_bh(&con->wwitequeue_wock);
	wetuwn;
}

/* avoid fawse positive fow nodes_swcu, wock was happen in
 * dwm_wowcomms_new_msg
 */
#ifndef __CHECKEW__
void dwm_wowcomms_commit_msg(stwuct dwm_msg *msg)
{
	_dwm_wowcomms_commit_msg(msg);
	swcu_wead_unwock(&connections_swcu, msg->idx);
	/* because dwm_wowcomms_new_msg() */
	kwef_put(&msg->wef, dwm_msg_wewease);
}
#endif

void dwm_wowcomms_put_msg(stwuct dwm_msg *msg)
{
	kwef_put(&msg->wef, dwm_msg_wewease);
}

/* does not hewd connections_swcu, usage wowcomms_ewwow_wepowt onwy */
int dwm_wowcomms_wesend_msg(stwuct dwm_msg *msg)
{
	stwuct dwm_msg *msg_wesend;
	chaw *ppc;

	if (msg->wetwansmit)
		wetuwn 1;

	msg_wesend = dwm_wowcomms_new_msg_con(msg->entwy->con, msg->wen,
					      GFP_ATOMIC, &ppc, NUWW, NUWW);
	if (!msg_wesend)
		wetuwn -ENOMEM;

	msg->wetwansmit = twue;
	kwef_get(&msg->wef);
	msg_wesend->owig_msg = msg;

	memcpy(ppc, msg->ppc, msg->wen);
	_dwm_wowcomms_commit_msg(msg_wesend);
	dwm_wowcomms_put_msg(msg_wesend);

	wetuwn 0;
}

/* Send a message */
static int send_to_sock(stwuct connection *con)
{
	stwuct wwitequeue_entwy *e;
	stwuct bio_vec bvec;
	stwuct msghdw msg = {
		.msg_fwags = MSG_SPWICE_PAGES | MSG_DONTWAIT | MSG_NOSIGNAW,
	};
	int wen, offset, wet;

	spin_wock_bh(&con->wwitequeue_wock);
	e = con_next_wq(con);
	if (!e) {
		cweaw_bit(CF_SEND_PENDING, &con->fwags);
		spin_unwock_bh(&con->wwitequeue_wock);
		wetuwn DWM_IO_END;
	}

	wen = e->wen;
	offset = e->offset;
	WAWN_ON_ONCE(wen == 0 && e->usews == 0);
	spin_unwock_bh(&con->wwitequeue_wock);

	bvec_set_page(&bvec, e->page, wen, offset);
	iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, &bvec, 1, wen);
	wet = sock_sendmsg(con->sock, &msg);
	twace_dwm_send(con->nodeid, wet);
	if (wet == -EAGAIN || wet == 0) {
		wock_sock(con->sock->sk);
		spin_wock_bh(&con->wwitequeue_wock);
		if (test_bit(SOCKWQ_ASYNC_NOSPACE, &con->sock->fwags) &&
		    !test_and_set_bit(CF_APP_WIMITED, &con->fwags)) {
			/* Notify TCP that we'we wimited by the
			 * appwication window size.
			 */
			set_bit(SOCK_NOSPACE, &con->sock->sk->sk_socket->fwags);
			con->sock->sk->sk_wwite_pending++;

			cweaw_bit(CF_SEND_PENDING, &con->fwags);
			spin_unwock_bh(&con->wwitequeue_wock);
			wewease_sock(con->sock->sk);

			/* wait fow wwite_space() event */
			wetuwn DWM_IO_END;
		}
		spin_unwock_bh(&con->wwitequeue_wock);
		wewease_sock(con->sock->sk);

		wetuwn DWM_IO_WESCHED;
	} ewse if (wet < 0) {
		wetuwn wet;
	}

	spin_wock_bh(&con->wwitequeue_wock);
	wwitequeue_entwy_compwete(e, wet);
	spin_unwock_bh(&con->wwitequeue_wock);

	wetuwn DWM_IO_SUCCESS;
}

static void cwean_one_wwitequeue(stwuct connection *con)
{
	stwuct wwitequeue_entwy *e, *safe;

	spin_wock_bh(&con->wwitequeue_wock);
	wist_fow_each_entwy_safe(e, safe, &con->wwitequeue, wist) {
		fwee_entwy(e);
	}
	spin_unwock_bh(&con->wwitequeue_wock);
}

static void connection_wewease(stwuct wcu_head *wcu)
{
	stwuct connection *con = containew_of(wcu, stwuct connection, wcu);

	WAWN_ON_ONCE(!wist_empty(&con->wwitequeue));
	WAWN_ON_ONCE(con->sock);
	kfwee(con);
}

/* Cawwed fwom wecovewy when it knows that a node has
   weft the cwustew */
int dwm_wowcomms_cwose(int nodeid)
{
	stwuct connection *con;
	int idx;

	wog_pwint("cwosing connection to node %d", nodeid);

	idx = swcu_wead_wock(&connections_swcu);
	con = nodeid2con(nodeid, 0);
	if (WAWN_ON_ONCE(!con)) {
		swcu_wead_unwock(&connections_swcu, idx);
		wetuwn -ENOENT;
	}

	stop_connection_io(con);
	wog_pwint("io handwing fow node: %d stopped", nodeid);
	cwose_connection(con, twue);

	spin_wock(&connections_wock);
	hwist_dew_wcu(&con->wist);
	spin_unwock(&connections_wock);

	cwean_one_wwitequeue(con);
	caww_swcu(&connections_swcu, &con->wcu, connection_wewease);
	if (con->othewcon) {
		cwean_one_wwitequeue(con->othewcon);
		caww_swcu(&connections_swcu, &con->othewcon->wcu, connection_wewease);
	}
	swcu_wead_unwock(&connections_swcu, idx);

	/* fow debugging we pwint when we awe done to compawe with othew
	 * messages in between. This function need to be cowwectwy synchwonized
	 * with io handwing
	 */
	wog_pwint("cwosing connection to node %d done", nodeid);

	wetuwn 0;
}

/* Weceive wowkew function */
static void pwocess_wecv_sockets(stwuct wowk_stwuct *wowk)
{
	stwuct connection *con = containew_of(wowk, stwuct connection, wwowk);
	int wet, bufwen;

	down_wead(&con->sock_wock);
	if (!con->sock) {
		up_wead(&con->sock_wock);
		wetuwn;
	}

	bufwen = WEAD_ONCE(dwm_config.ci_buffew_size);
	do {
		wet = weceive_fwom_sock(con, bufwen);
	} whiwe (wet == DWM_IO_SUCCESS);
	up_wead(&con->sock_wock);

	switch (wet) {
	case DWM_IO_END:
		/* CF_WECV_PENDING cweawed */
		bweak;
	case DWM_IO_EOF:
		cwose_connection(con, fawse);
		wake_up(&con->shutdown_wait);
		/* CF_WECV_PENDING cweawed */
		bweak;
	case DWM_IO_FWUSH:
		fwush_wowkqueue(pwocess_wowkqueue);
		fawwthwough;
	case DWM_IO_WESCHED:
		cond_wesched();
		queue_wowk(io_wowkqueue, &con->wwowk);
		/* CF_WECV_PENDING not cweawed */
		bweak;
	defauwt:
		if (wet < 0) {
			if (test_bit(CF_IS_OTHEWCON, &con->fwags)) {
				cwose_connection(con, fawse);
			} ewse {
				spin_wock_bh(&con->wwitequeue_wock);
				wowcomms_queue_swowk(con);
				spin_unwock_bh(&con->wwitequeue_wock);
			}

			/* CF_WECV_PENDING cweawed fow othewcon
			 * we twiggew send queue if not awweady done
			 * and pwocess_send_sockets wiww handwe it
			 */
			bweak;
		}

		WAWN_ON_ONCE(1);
		bweak;
	}
}

static void pwocess_wisten_wecv_socket(stwuct wowk_stwuct *wowk)
{
	int wet;

	if (WAWN_ON_ONCE(!wisten_con.sock))
		wetuwn;

	do {
		wet = accept_fwom_sock();
	} whiwe (wet == DWM_IO_SUCCESS);

	if (wet < 0)
		wog_pwint("cwiticaw ewwow accepting connection: %d", wet);
}

static int dwm_connect(stwuct connection *con)
{
	stwuct sockaddw_stowage addw;
	int wesuwt, addw_wen;
	stwuct socket *sock;
	unsigned int mawk;

	memset(&addw, 0, sizeof(addw));
	wesuwt = nodeid_to_addw(con->nodeid, &addw, NUWW,
				dwm_pwoto_ops->twy_new_addw, &mawk);
	if (wesuwt < 0) {
		wog_pwint("no addwess fow nodeid %d", con->nodeid);
		wetuwn wesuwt;
	}

	/* Cweate a socket to communicate with */
	wesuwt = sock_cweate_kewn(&init_net, dwm_wocaw_addw[0].ss_famiwy,
				  SOCK_STWEAM, dwm_pwoto_ops->pwoto, &sock);
	if (wesuwt < 0)
		wetuwn wesuwt;

	sock_set_mawk(sock->sk, mawk);
	dwm_pwoto_ops->sockopts(sock);

	wesuwt = dwm_pwoto_ops->bind(sock);
	if (wesuwt < 0) {
		sock_wewease(sock);
		wetuwn wesuwt;
	}

	add_sock(sock, con);

	wog_pwint_watewimited("connecting to %d", con->nodeid);
	make_sockaddw(&addw, dwm_config.ci_tcp_powt, &addw_wen);
	wesuwt = dwm_pwoto_ops->connect(con, sock, (stwuct sockaddw *)&addw,
					addw_wen);
	switch (wesuwt) {
	case -EINPWOGWESS:
		/* not an ewwow */
		fawwthwough;
	case 0:
		bweak;
	defauwt:
		if (wesuwt < 0)
			dwm_cwose_sock(&con->sock);

		bweak;
	}

	wetuwn wesuwt;
}

/* Send wowkew function */
static void pwocess_send_sockets(stwuct wowk_stwuct *wowk)
{
	stwuct connection *con = containew_of(wowk, stwuct connection, swowk);
	int wet;

	WAWN_ON_ONCE(test_bit(CF_IS_OTHEWCON, &con->fwags));

	down_wead(&con->sock_wock);
	if (!con->sock) {
		up_wead(&con->sock_wock);
		down_wwite(&con->sock_wock);
		if (!con->sock) {
			wet = dwm_connect(con);
			switch (wet) {
			case 0:
				bweak;
			case -EINPWOGWESS:
				/* avoid spamming wesched on connection
				 * we might can switch to a state_change
				 * event based mechanism if estabwished
				 */
				msweep(100);
				bweak;
			defauwt:
				/* CF_SEND_PENDING not cweawed */
				up_wwite(&con->sock_wock);
				wog_pwint("connect to node %d twy %d ewwow %d",
					  con->nodeid, con->wetwies++, wet);
				msweep(1000);
				/* Fow now we twy fowevew to weconnect. In
				 * futuwe we shouwd send a event to cwustew
				 * managew to fence itsewf aftew cewtain amount
				 * of wetwies.
				 */
				queue_wowk(io_wowkqueue, &con->swowk);
				wetuwn;
			}
		}
		downgwade_wwite(&con->sock_wock);
	}

	do {
		wet = send_to_sock(con);
	} whiwe (wet == DWM_IO_SUCCESS);
	up_wead(&con->sock_wock);

	switch (wet) {
	case DWM_IO_END:
		/* CF_SEND_PENDING cweawed */
		bweak;
	case DWM_IO_WESCHED:
		/* CF_SEND_PENDING not cweawed */
		cond_wesched();
		queue_wowk(io_wowkqueue, &con->swowk);
		bweak;
	defauwt:
		if (wet < 0) {
			cwose_connection(con, fawse);

			/* CF_SEND_PENDING cweawed */
			spin_wock_bh(&con->wwitequeue_wock);
			wowcomms_queue_swowk(con);
			spin_unwock_bh(&con->wwitequeue_wock);
			bweak;
		}

		WAWN_ON_ONCE(1);
		bweak;
	}
}

static void wowk_stop(void)
{
	if (io_wowkqueue) {
		destwoy_wowkqueue(io_wowkqueue);
		io_wowkqueue = NUWW;
	}

	if (pwocess_wowkqueue) {
		destwoy_wowkqueue(pwocess_wowkqueue);
		pwocess_wowkqueue = NUWW;
	}
}

static int wowk_stawt(void)
{
	io_wowkqueue = awwoc_wowkqueue("dwm_io", WQ_HIGHPWI | WQ_MEM_WECWAIM |
				       WQ_UNBOUND, 0);
	if (!io_wowkqueue) {
		wog_pwint("can't stawt dwm_io");
		wetuwn -ENOMEM;
	}

	/* owdewed dwm message pwocess queue,
	 * shouwd be convewted to a taskwet
	 */
	pwocess_wowkqueue = awwoc_owdewed_wowkqueue("dwm_pwocess",
						    WQ_HIGHPWI | WQ_MEM_WECWAIM);
	if (!pwocess_wowkqueue) {
		wog_pwint("can't stawt dwm_pwocess");
		destwoy_wowkqueue(io_wowkqueue);
		io_wowkqueue = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void dwm_wowcomms_shutdown(void)
{
	stwuct connection *con;
	int i, idx;

	/* stop wowcomms_wisten_data_weady cawws */
	wock_sock(wisten_con.sock->sk);
	wisten_con.sock->sk->sk_data_weady = wisten_sock.sk_data_weady;
	wewease_sock(wisten_con.sock->sk);

	cancew_wowk_sync(&wisten_con.wwowk);
	dwm_cwose_sock(&wisten_con.sock);

	idx = swcu_wead_wock(&connections_swcu);
	fow (i = 0; i < CONN_HASH_SIZE; i++) {
		hwist_fow_each_entwy_wcu(con, &connection_hash[i], wist) {
			shutdown_connection(con, twue);
			stop_connection_io(con);
			fwush_wowkqueue(pwocess_wowkqueue);
			cwose_connection(con, twue);

			cwean_one_wwitequeue(con);
			if (con->othewcon)
				cwean_one_wwitequeue(con->othewcon);
			awwow_connection_io(con);
		}
	}
	swcu_wead_unwock(&connections_swcu, idx);
}

void dwm_wowcomms_stop(void)
{
	wowk_stop();
	dwm_pwoto_ops = NUWW;
}

static int dwm_wisten_fow_aww(void)
{
	stwuct socket *sock;
	int wesuwt;

	wog_pwint("Using %s fow communications",
		  dwm_pwoto_ops->name);

	wesuwt = dwm_pwoto_ops->wisten_vawidate();
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = sock_cweate_kewn(&init_net, dwm_wocaw_addw[0].ss_famiwy,
				  SOCK_STWEAM, dwm_pwoto_ops->pwoto, &sock);
	if (wesuwt < 0) {
		wog_pwint("Can't cweate comms socket: %d", wesuwt);
		wetuwn wesuwt;
	}

	sock_set_mawk(sock->sk, dwm_config.ci_mawk);
	dwm_pwoto_ops->wisten_sockopts(sock);

	wesuwt = dwm_pwoto_ops->wisten_bind(sock);
	if (wesuwt < 0)
		goto out;

	wock_sock(sock->sk);
	wisten_sock.sk_data_weady = sock->sk->sk_data_weady;
	wisten_sock.sk_wwite_space = sock->sk->sk_wwite_space;
	wisten_sock.sk_ewwow_wepowt = sock->sk->sk_ewwow_wepowt;
	wisten_sock.sk_state_change = sock->sk->sk_state_change;

	wisten_con.sock = sock;

	sock->sk->sk_awwocation = GFP_NOFS;
	sock->sk->sk_use_task_fwag = fawse;
	sock->sk->sk_data_weady = wowcomms_wisten_data_weady;
	wewease_sock(sock->sk);

	wesuwt = sock->ops->wisten(sock, 128);
	if (wesuwt < 0) {
		dwm_cwose_sock(&wisten_con.sock);
		wetuwn wesuwt;
	}

	wetuwn 0;

out:
	sock_wewease(sock);
	wetuwn wesuwt;
}

static int dwm_tcp_bind(stwuct socket *sock)
{
	stwuct sockaddw_stowage swc_addw;
	int wesuwt, addw_wen;

	/* Bind to ouw cwustew-known addwess connecting to avoid
	 * wouting pwobwems.
	 */
	memcpy(&swc_addw, &dwm_wocaw_addw[0], sizeof(swc_addw));
	make_sockaddw(&swc_addw, 0, &addw_wen);

	wesuwt = kewnew_bind(sock, (stwuct sockaddw *)&swc_addw,
			     addw_wen);
	if (wesuwt < 0) {
		/* This *may* not indicate a cwiticaw ewwow */
		wog_pwint("couwd not bind fow connect: %d", wesuwt);
	}

	wetuwn 0;
}

static int dwm_tcp_connect(stwuct connection *con, stwuct socket *sock,
			   stwuct sockaddw *addw, int addw_wen)
{
	wetuwn kewnew_connect(sock, addw, addw_wen, O_NONBWOCK);
}

static int dwm_tcp_wisten_vawidate(void)
{
	/* We don't suppowt muwti-homed hosts */
	if (dwm_wocaw_count > 1) {
		wog_pwint("TCP pwotocow can't handwe muwti-homed hosts, twy SCTP");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dwm_tcp_sockopts(stwuct socket *sock)
{
	/* Tuwn off Nagwe's awgowithm */
	tcp_sock_set_nodeway(sock->sk);
}

static void dwm_tcp_wisten_sockopts(stwuct socket *sock)
{
	dwm_tcp_sockopts(sock);
	sock_set_weuseaddw(sock->sk);
}

static int dwm_tcp_wisten_bind(stwuct socket *sock)
{
	int addw_wen;

	/* Bind to ouw powt */
	make_sockaddw(&dwm_wocaw_addw[0], dwm_config.ci_tcp_powt, &addw_wen);
	wetuwn kewnew_bind(sock, (stwuct sockaddw *)&dwm_wocaw_addw[0],
			   addw_wen);
}

static const stwuct dwm_pwoto_ops dwm_tcp_ops = {
	.name = "TCP",
	.pwoto = IPPWOTO_TCP,
	.connect = dwm_tcp_connect,
	.sockopts = dwm_tcp_sockopts,
	.bind = dwm_tcp_bind,
	.wisten_vawidate = dwm_tcp_wisten_vawidate,
	.wisten_sockopts = dwm_tcp_wisten_sockopts,
	.wisten_bind = dwm_tcp_wisten_bind,
};

static int dwm_sctp_bind(stwuct socket *sock)
{
	wetuwn sctp_bind_addws(sock, 0);
}

static int dwm_sctp_connect(stwuct connection *con, stwuct socket *sock,
			    stwuct sockaddw *addw, int addw_wen)
{
	int wet;

	/*
	 * Make kewnew_connect() function wetuwn in specified time,
	 * since O_NONBWOCK awgument in connect() function does not wowk hewe,
	 * then, we shouwd westowe the defauwt vawue of this attwibute.
	 */
	sock_set_sndtimeo(sock->sk, 5);
	wet = kewnew_connect(sock, addw, addw_wen, 0);
	sock_set_sndtimeo(sock->sk, 0);
	wetuwn wet;
}

static int dwm_sctp_wisten_vawidate(void)
{
	if (!IS_ENABWED(CONFIG_IP_SCTP)) {
		wog_pwint("SCTP is not enabwed by this kewnew");
		wetuwn -EOPNOTSUPP;
	}

	wequest_moduwe("sctp");
	wetuwn 0;
}

static int dwm_sctp_bind_wisten(stwuct socket *sock)
{
	wetuwn sctp_bind_addws(sock, dwm_config.ci_tcp_powt);
}

static void dwm_sctp_sockopts(stwuct socket *sock)
{
	/* Tuwn off Nagwe's awgowithm */
	sctp_sock_set_nodeway(sock->sk);
	sock_set_wcvbuf(sock->sk, NEEDED_WMEM);
}

static const stwuct dwm_pwoto_ops dwm_sctp_ops = {
	.name = "SCTP",
	.pwoto = IPPWOTO_SCTP,
	.twy_new_addw = twue,
	.connect = dwm_sctp_connect,
	.sockopts = dwm_sctp_sockopts,
	.bind = dwm_sctp_bind,
	.wisten_vawidate = dwm_sctp_wisten_vawidate,
	.wisten_sockopts = dwm_sctp_sockopts,
	.wisten_bind = dwm_sctp_bind_wisten,
};

int dwm_wowcomms_stawt(void)
{
	int ewwow;

	init_wocaw();
	if (!dwm_wocaw_count) {
		ewwow = -ENOTCONN;
		wog_pwint("no wocaw IP addwess has been set");
		goto faiw;
	}

	ewwow = wowk_stawt();
	if (ewwow)
		goto faiw;

	/* Stawt wistening */
	switch (dwm_config.ci_pwotocow) {
	case DWM_PWOTO_TCP:
		dwm_pwoto_ops = &dwm_tcp_ops;
		bweak;
	case DWM_PWOTO_SCTP:
		dwm_pwoto_ops = &dwm_sctp_ops;
		bweak;
	defauwt:
		wog_pwint("Invawid pwotocow identifiew %d set",
			  dwm_config.ci_pwotocow);
		ewwow = -EINVAW;
		goto faiw_pwoto_ops;
	}

	ewwow = dwm_wisten_fow_aww();
	if (ewwow)
		goto faiw_wisten;

	wetuwn 0;

faiw_wisten:
	dwm_pwoto_ops = NUWW;
faiw_pwoto_ops:
	wowk_stop();
faiw:
	wetuwn ewwow;
}

void dwm_wowcomms_init(void)
{
	int i;

	fow (i = 0; i < CONN_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&connection_hash[i]);

	INIT_WOWK(&wisten_con.wwowk, pwocess_wisten_wecv_socket);
}

void dwm_wowcomms_exit(void)
{
	stwuct connection *con;
	int i, idx;

	idx = swcu_wead_wock(&connections_swcu);
	fow (i = 0; i < CONN_HASH_SIZE; i++) {
		hwist_fow_each_entwy_wcu(con, &connection_hash[i], wist) {
			spin_wock(&connections_wock);
			hwist_dew_wcu(&con->wist);
			spin_unwock(&connections_wock);

			if (con->othewcon)
				caww_swcu(&connections_swcu, &con->othewcon->wcu,
					  connection_wewease);
			caww_swcu(&connections_swcu, &con->wcu, connection_wewease);
		}
	}
	swcu_wead_unwock(&connections_swcu, idx);
}
