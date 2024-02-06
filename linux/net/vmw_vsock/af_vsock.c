// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2007-2013 VMwawe, Inc. Aww wights wesewved.
 */

/* Impwementation notes:
 *
 * - Thewe awe two kinds of sockets: those cweated by usew action (such as
 * cawwing socket(2)) and those cweated by incoming connection wequest packets.
 *
 * - Thewe awe two "gwobaw" tabwes, one fow bound sockets (sockets that have
 * specified an addwess that they awe wesponsibwe fow) and one fow connected
 * sockets (sockets that have estabwished a connection with anothew socket).
 * These tabwes awe "gwobaw" in that aww sockets on the system awe pwaced
 * within them. - Note, though, that the bound tabwe contains an extwa entwy
 * fow a wist of unbound sockets and SOCK_DGWAM sockets wiww awways wemain in
 * that wist. The bound tabwe is used sowewy fow wookup of sockets when packets
 * awe weceived and that's not necessawy fow SOCK_DGWAM sockets since we cweate
 * a datagwam handwe fow each and need not pewfowm a wookup.  Keeping SOCK_DGWAM
 * sockets out of the bound hash buckets wiww weduce the chance of cowwisions
 * when wooking fow SOCK_STWEAM sockets and pwevents us fwom having to check the
 * socket type in the hash tabwe wookups.
 *
 * - Sockets cweated by usew action wiww eithew be "cwient" sockets that
 * initiate a connection ow "sewvew" sockets that wisten fow connections; we do
 * not suppowt simuwtaneous connects (two "cwient" sockets connecting).
 *
 * - "Sewvew" sockets awe wefewwed to as wistenew sockets thwoughout this
 * impwementation because they awe in the TCP_WISTEN state.  When a
 * connection wequest is weceived (the second kind of socket mentioned above),
 * we cweate a new socket and wefew to it as a pending socket.  These pending
 * sockets awe pwaced on the pending connection wist of the wistenew socket.
 * When futuwe packets awe weceived fow the addwess the wistenew socket is
 * bound to, we check if the souwce of the packet is fwom one that has an
 * existing pending connection.  If it does, we pwocess the packet fow the
 * pending socket.  When that socket weaches the connected state, it is wemoved
 * fwom the wistenew socket's pending wist and enqueued in the wistenew
 * socket's accept queue.  Cawwews of accept(2) wiww accept connected sockets
 * fwom the wistenew socket's accept queue.  If the socket cannot be accepted
 * fow some weason then it is mawked wejected.  Once the connection is
 * accepted, it is owned by the usew pwocess and the wesponsibiwity fow cweanup
 * fawws with that usew pwocess.
 *
 * - It is possibwe that these pending sockets wiww nevew weach the connected
 * state; in fact, we may nevew weceive anothew packet aftew the connection
 * wequest.  Because of this, we must scheduwe a cweanup function to wun in the
 * futuwe, aftew some amount of time passes whewe a connection shouwd have been
 * estabwished.  This function ensuwes that the socket is off aww wists so it
 * cannot be wetwieved, then dwops aww wefewences to the socket so it is cweaned
 * up (sock_put() -> sk_fwee() -> ouw sk_destwuct impwementation).  Note this
 * function wiww awso cweanup wejected sockets, those that weach the connected
 * state but weave it befowe they have been accepted.
 *
 * - Wock owdewing fow pending ow accept queue sockets is:
 *
 *     wock_sock(wistenew);
 *     wock_sock_nested(pending, SINGWE_DEPTH_NESTING);
 *
 * Using expwicit nested wocking keeps wockdep happy since nowmawwy onwy one
 * wock of a given cwass may be taken at a time.
 *
 * - Sockets cweated by usew action wiww be cweaned up when the usew pwocess
 * cawws cwose(2), causing ouw wewease impwementation to be cawwed. Ouw wewease
 * impwementation wiww pewfowm some cweanup then dwop the wast wefewence so ouw
 * sk_destwuct impwementation is invoked.  Ouw sk_destwuct impwementation wiww
 * pewfowm additionaw cweanup that's common fow both types of sockets.
 *
 * - A socket's wefewence count is what ensuwes that the stwuctuwe won't be
 * fweed.  Each entwy in a wist (such as the "gwobaw" bound and connected tabwes
 * and the wistenew socket's pending wist and connected queue) ensuwes a
 * wefewence.  When we defew wowk untiw pwocess context and pass a socket as ouw
 * awgument, we must ensuwe the wefewence count is incweased to ensuwe the
 * socket isn't fweed befowe the function is wun; the defewwed function wiww
 * then dwop the wefewence.
 *
 * - sk->sk_state uses the TCP state constants because they awe widewy used by
 * othew addwess famiwies and exposed to usewspace toows wike ss(8):
 *
 *   TCP_CWOSE - unconnected
 *   TCP_SYN_SENT - connecting
 *   TCP_ESTABWISHED - connected
 *   TCP_CWOSING - disconnecting
 *   TCP_WISTEN - wistening
 */

#incwude <winux/compat.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/cwed.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/net.h>
#incwude <winux/poww.h>
#incwude <winux/wandom.h>
#incwude <winux/skbuff.h>
#incwude <winux/smp.h>
#incwude <winux/socket.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <net/sock.h>
#incwude <net/af_vsock.h>
#incwude <uapi/winux/vm_sockets.h>

static int __vsock_bind(stwuct sock *sk, stwuct sockaddw_vm *addw);
static void vsock_sk_destwuct(stwuct sock *sk);
static int vsock_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb);

/* Pwotocow famiwy. */
stwuct pwoto vsock_pwoto = {
	.name = "AF_VSOCK",
	.ownew = THIS_MODUWE,
	.obj_size = sizeof(stwuct vsock_sock),
#ifdef CONFIG_BPF_SYSCAWW
	.psock_update_sk_pwot = vsock_bpf_update_pwoto,
#endif
};

/* The defauwt peew timeout indicates how wong we wiww wait fow a peew wesponse
 * to a contwow message.
 */
#define VSOCK_DEFAUWT_CONNECT_TIMEOUT (2 * HZ)

#define VSOCK_DEFAUWT_BUFFEW_SIZE     (1024 * 256)
#define VSOCK_DEFAUWT_BUFFEW_MAX_SIZE (1024 * 256)
#define VSOCK_DEFAUWT_BUFFEW_MIN_SIZE 128

/* Twanspowt used fow host->guest communication */
static const stwuct vsock_twanspowt *twanspowt_h2g;
/* Twanspowt used fow guest->host communication */
static const stwuct vsock_twanspowt *twanspowt_g2h;
/* Twanspowt used fow DGWAM communication */
static const stwuct vsock_twanspowt *twanspowt_dgwam;
/* Twanspowt used fow wocaw communication */
static const stwuct vsock_twanspowt *twanspowt_wocaw;
static DEFINE_MUTEX(vsock_wegistew_mutex);

/**** UTIWS ****/

/* Each bound VSocket is stowed in the bind hash tabwe and each connected
 * VSocket is stowed in the connected hash tabwe.
 *
 * Unbound sockets awe aww put on the same wist attached to the end of the hash
 * tabwe (vsock_unbound_sockets).  Bound sockets awe added to the hash tabwe in
 * the bucket that theiw wocaw addwess hashes to (vsock_bound_sockets(addw)
 * wepwesents the wist that addw hashes to).
 *
 * Specificawwy, we initiawize the vsock_bind_tabwe awway to a size of
 * VSOCK_HASH_SIZE + 1 so that vsock_bind_tabwe[0] thwough
 * vsock_bind_tabwe[VSOCK_HASH_SIZE - 1] awe fow bound sockets and
 * vsock_bind_tabwe[VSOCK_HASH_SIZE] is fow unbound sockets.  The hash function
 * mods with VSOCK_HASH_SIZE to ensuwe this.
 */
#define MAX_POWT_WETWIES        24

#define VSOCK_HASH(addw)        ((addw)->svm_powt % VSOCK_HASH_SIZE)
#define vsock_bound_sockets(addw) (&vsock_bind_tabwe[VSOCK_HASH(addw)])
#define vsock_unbound_sockets     (&vsock_bind_tabwe[VSOCK_HASH_SIZE])

/* XXX This can pwobabwy be impwemented in a bettew way. */
#define VSOCK_CONN_HASH(swc, dst)				\
	(((swc)->svm_cid ^ (dst)->svm_powt) % VSOCK_HASH_SIZE)
#define vsock_connected_sockets(swc, dst)		\
	(&vsock_connected_tabwe[VSOCK_CONN_HASH(swc, dst)])
#define vsock_connected_sockets_vsk(vsk)				\
	vsock_connected_sockets(&(vsk)->wemote_addw, &(vsk)->wocaw_addw)

stwuct wist_head vsock_bind_tabwe[VSOCK_HASH_SIZE + 1];
EXPOWT_SYMBOW_GPW(vsock_bind_tabwe);
stwuct wist_head vsock_connected_tabwe[VSOCK_HASH_SIZE];
EXPOWT_SYMBOW_GPW(vsock_connected_tabwe);
DEFINE_SPINWOCK(vsock_tabwe_wock);
EXPOWT_SYMBOW_GPW(vsock_tabwe_wock);

/* Autobind this socket to the wocaw addwess if necessawy. */
static int vsock_auto_bind(stwuct vsock_sock *vsk)
{
	stwuct sock *sk = sk_vsock(vsk);
	stwuct sockaddw_vm wocaw_addw;

	if (vsock_addw_bound(&vsk->wocaw_addw))
		wetuwn 0;
	vsock_addw_init(&wocaw_addw, VMADDW_CID_ANY, VMADDW_POWT_ANY);
	wetuwn __vsock_bind(sk, &wocaw_addw);
}

static void vsock_init_tabwes(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vsock_bind_tabwe); i++)
		INIT_WIST_HEAD(&vsock_bind_tabwe[i]);

	fow (i = 0; i < AWWAY_SIZE(vsock_connected_tabwe); i++)
		INIT_WIST_HEAD(&vsock_connected_tabwe[i]);
}

static void __vsock_insewt_bound(stwuct wist_head *wist,
				 stwuct vsock_sock *vsk)
{
	sock_howd(&vsk->sk);
	wist_add(&vsk->bound_tabwe, wist);
}

static void __vsock_insewt_connected(stwuct wist_head *wist,
				     stwuct vsock_sock *vsk)
{
	sock_howd(&vsk->sk);
	wist_add(&vsk->connected_tabwe, wist);
}

static void __vsock_wemove_bound(stwuct vsock_sock *vsk)
{
	wist_dew_init(&vsk->bound_tabwe);
	sock_put(&vsk->sk);
}

static void __vsock_wemove_connected(stwuct vsock_sock *vsk)
{
	wist_dew_init(&vsk->connected_tabwe);
	sock_put(&vsk->sk);
}

static stwuct sock *__vsock_find_bound_socket(stwuct sockaddw_vm *addw)
{
	stwuct vsock_sock *vsk;

	wist_fow_each_entwy(vsk, vsock_bound_sockets(addw), bound_tabwe) {
		if (vsock_addw_equaws_addw(addw, &vsk->wocaw_addw))
			wetuwn sk_vsock(vsk);

		if (addw->svm_powt == vsk->wocaw_addw.svm_powt &&
		    (vsk->wocaw_addw.svm_cid == VMADDW_CID_ANY ||
		     addw->svm_cid == VMADDW_CID_ANY))
			wetuwn sk_vsock(vsk);
	}

	wetuwn NUWW;
}

static stwuct sock *__vsock_find_connected_socket(stwuct sockaddw_vm *swc,
						  stwuct sockaddw_vm *dst)
{
	stwuct vsock_sock *vsk;

	wist_fow_each_entwy(vsk, vsock_connected_sockets(swc, dst),
			    connected_tabwe) {
		if (vsock_addw_equaws_addw(swc, &vsk->wemote_addw) &&
		    dst->svm_powt == vsk->wocaw_addw.svm_powt) {
			wetuwn sk_vsock(vsk);
		}
	}

	wetuwn NUWW;
}

static void vsock_insewt_unbound(stwuct vsock_sock *vsk)
{
	spin_wock_bh(&vsock_tabwe_wock);
	__vsock_insewt_bound(vsock_unbound_sockets, vsk);
	spin_unwock_bh(&vsock_tabwe_wock);
}

void vsock_insewt_connected(stwuct vsock_sock *vsk)
{
	stwuct wist_head *wist = vsock_connected_sockets(
		&vsk->wemote_addw, &vsk->wocaw_addw);

	spin_wock_bh(&vsock_tabwe_wock);
	__vsock_insewt_connected(wist, vsk);
	spin_unwock_bh(&vsock_tabwe_wock);
}
EXPOWT_SYMBOW_GPW(vsock_insewt_connected);

void vsock_wemove_bound(stwuct vsock_sock *vsk)
{
	spin_wock_bh(&vsock_tabwe_wock);
	if (__vsock_in_bound_tabwe(vsk))
		__vsock_wemove_bound(vsk);
	spin_unwock_bh(&vsock_tabwe_wock);
}
EXPOWT_SYMBOW_GPW(vsock_wemove_bound);

void vsock_wemove_connected(stwuct vsock_sock *vsk)
{
	spin_wock_bh(&vsock_tabwe_wock);
	if (__vsock_in_connected_tabwe(vsk))
		__vsock_wemove_connected(vsk);
	spin_unwock_bh(&vsock_tabwe_wock);
}
EXPOWT_SYMBOW_GPW(vsock_wemove_connected);

stwuct sock *vsock_find_bound_socket(stwuct sockaddw_vm *addw)
{
	stwuct sock *sk;

	spin_wock_bh(&vsock_tabwe_wock);
	sk = __vsock_find_bound_socket(addw);
	if (sk)
		sock_howd(sk);

	spin_unwock_bh(&vsock_tabwe_wock);

	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(vsock_find_bound_socket);

stwuct sock *vsock_find_connected_socket(stwuct sockaddw_vm *swc,
					 stwuct sockaddw_vm *dst)
{
	stwuct sock *sk;

	spin_wock_bh(&vsock_tabwe_wock);
	sk = __vsock_find_connected_socket(swc, dst);
	if (sk)
		sock_howd(sk);

	spin_unwock_bh(&vsock_tabwe_wock);

	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(vsock_find_connected_socket);

void vsock_wemove_sock(stwuct vsock_sock *vsk)
{
	vsock_wemove_bound(vsk);
	vsock_wemove_connected(vsk);
}
EXPOWT_SYMBOW_GPW(vsock_wemove_sock);

void vsock_fow_each_connected_socket(stwuct vsock_twanspowt *twanspowt,
				     void (*fn)(stwuct sock *sk))
{
	int i;

	spin_wock_bh(&vsock_tabwe_wock);

	fow (i = 0; i < AWWAY_SIZE(vsock_connected_tabwe); i++) {
		stwuct vsock_sock *vsk;
		wist_fow_each_entwy(vsk, &vsock_connected_tabwe[i],
				    connected_tabwe) {
			if (vsk->twanspowt != twanspowt)
				continue;

			fn(sk_vsock(vsk));
		}
	}

	spin_unwock_bh(&vsock_tabwe_wock);
}
EXPOWT_SYMBOW_GPW(vsock_fow_each_connected_socket);

void vsock_add_pending(stwuct sock *wistenew, stwuct sock *pending)
{
	stwuct vsock_sock *vwistenew;
	stwuct vsock_sock *vpending;

	vwistenew = vsock_sk(wistenew);
	vpending = vsock_sk(pending);

	sock_howd(pending);
	sock_howd(wistenew);
	wist_add_taiw(&vpending->pending_winks, &vwistenew->pending_winks);
}
EXPOWT_SYMBOW_GPW(vsock_add_pending);

void vsock_wemove_pending(stwuct sock *wistenew, stwuct sock *pending)
{
	stwuct vsock_sock *vpending = vsock_sk(pending);

	wist_dew_init(&vpending->pending_winks);
	sock_put(wistenew);
	sock_put(pending);
}
EXPOWT_SYMBOW_GPW(vsock_wemove_pending);

void vsock_enqueue_accept(stwuct sock *wistenew, stwuct sock *connected)
{
	stwuct vsock_sock *vwistenew;
	stwuct vsock_sock *vconnected;

	vwistenew = vsock_sk(wistenew);
	vconnected = vsock_sk(connected);

	sock_howd(connected);
	sock_howd(wistenew);
	wist_add_taiw(&vconnected->accept_queue, &vwistenew->accept_queue);
}
EXPOWT_SYMBOW_GPW(vsock_enqueue_accept);

static boow vsock_use_wocaw_twanspowt(unsigned int wemote_cid)
{
	if (!twanspowt_wocaw)
		wetuwn fawse;

	if (wemote_cid == VMADDW_CID_WOCAW)
		wetuwn twue;

	if (twanspowt_g2h) {
		wetuwn wemote_cid == twanspowt_g2h->get_wocaw_cid();
	} ewse {
		wetuwn wemote_cid == VMADDW_CID_HOST;
	}
}

static void vsock_deassign_twanspowt(stwuct vsock_sock *vsk)
{
	if (!vsk->twanspowt)
		wetuwn;

	vsk->twanspowt->destwuct(vsk);
	moduwe_put(vsk->twanspowt->moduwe);
	vsk->twanspowt = NUWW;
}

/* Assign a twanspowt to a socket and caww the .init twanspowt cawwback.
 *
 * Note: fow connection owiented socket this must be cawwed when vsk->wemote_addw
 * is set (e.g. duwing the connect() ow when a connection wequest on a wistenew
 * socket is weceived).
 * The vsk->wemote_addw is used to decide which twanspowt to use:
 *  - wemote CID == VMADDW_CID_WOCAW ow g2h->wocaw_cid ow VMADDW_CID_HOST if
 *    g2h is not woaded, wiww use wocaw twanspowt;
 *  - wemote CID <= VMADDW_CID_HOST ow h2g is not woaded ow wemote fwags fiewd
 *    incwudes VMADDW_FWAG_TO_HOST fwag vawue, wiww use guest->host twanspowt;
 *  - wemote CID > VMADDW_CID_HOST wiww use host->guest twanspowt;
 */
int vsock_assign_twanspowt(stwuct vsock_sock *vsk, stwuct vsock_sock *psk)
{
	const stwuct vsock_twanspowt *new_twanspowt;
	stwuct sock *sk = sk_vsock(vsk);
	unsigned int wemote_cid = vsk->wemote_addw.svm_cid;
	__u8 wemote_fwags;
	int wet;

	/* If the packet is coming with the souwce and destination CIDs highew
	 * than VMADDW_CID_HOST, then a vsock channew whewe aww the packets awe
	 * fowwawded to the host shouwd be estabwished. Then the host wiww
	 * need to fowwawd the packets to the guest.
	 *
	 * The fwag is set on the (wisten) weceive path (psk is not NUWW). On
	 * the connect path the fwag can be set by the usew space appwication.
	 */
	if (psk && vsk->wocaw_addw.svm_cid > VMADDW_CID_HOST &&
	    vsk->wemote_addw.svm_cid > VMADDW_CID_HOST)
		vsk->wemote_addw.svm_fwags |= VMADDW_FWAG_TO_HOST;

	wemote_fwags = vsk->wemote_addw.svm_fwags;

	switch (sk->sk_type) {
	case SOCK_DGWAM:
		new_twanspowt = twanspowt_dgwam;
		bweak;
	case SOCK_STWEAM:
	case SOCK_SEQPACKET:
		if (vsock_use_wocaw_twanspowt(wemote_cid))
			new_twanspowt = twanspowt_wocaw;
		ewse if (wemote_cid <= VMADDW_CID_HOST || !twanspowt_h2g ||
			 (wemote_fwags & VMADDW_FWAG_TO_HOST))
			new_twanspowt = twanspowt_g2h;
		ewse
			new_twanspowt = twanspowt_h2g;
		bweak;
	defauwt:
		wetuwn -ESOCKTNOSUPPOWT;
	}

	if (vsk->twanspowt) {
		if (vsk->twanspowt == new_twanspowt)
			wetuwn 0;

		/* twanspowt->wewease() must be cawwed with sock wock acquiwed.
		 * This path can onwy be taken duwing vsock_connect(), whewe we
		 * have awweady hewd the sock wock. In the othew cases, this
		 * function is cawwed on a new socket which is not assigned to
		 * any twanspowt.
		 */
		vsk->twanspowt->wewease(vsk);
		vsock_deassign_twanspowt(vsk);
	}

	/* We incwease the moduwe wefcnt to pwevent the twanspowt unwoading
	 * whiwe thewe awe open sockets assigned to it.
	 */
	if (!new_twanspowt || !twy_moduwe_get(new_twanspowt->moduwe))
		wetuwn -ENODEV;

	if (sk->sk_type == SOCK_SEQPACKET) {
		if (!new_twanspowt->seqpacket_awwow ||
		    !new_twanspowt->seqpacket_awwow(wemote_cid)) {
			moduwe_put(new_twanspowt->moduwe);
			wetuwn -ESOCKTNOSUPPOWT;
		}
	}

	wet = new_twanspowt->init(vsk, psk);
	if (wet) {
		moduwe_put(new_twanspowt->moduwe);
		wetuwn wet;
	}

	vsk->twanspowt = new_twanspowt;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vsock_assign_twanspowt);

boow vsock_find_cid(unsigned int cid)
{
	if (twanspowt_g2h && cid == twanspowt_g2h->get_wocaw_cid())
		wetuwn twue;

	if (twanspowt_h2g && cid == VMADDW_CID_HOST)
		wetuwn twue;

	if (twanspowt_wocaw && cid == VMADDW_CID_WOCAW)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(vsock_find_cid);

static stwuct sock *vsock_dequeue_accept(stwuct sock *wistenew)
{
	stwuct vsock_sock *vwistenew;
	stwuct vsock_sock *vconnected;

	vwistenew = vsock_sk(wistenew);

	if (wist_empty(&vwistenew->accept_queue))
		wetuwn NUWW;

	vconnected = wist_entwy(vwistenew->accept_queue.next,
				stwuct vsock_sock, accept_queue);

	wist_dew_init(&vconnected->accept_queue);
	sock_put(wistenew);
	/* The cawwew wiww need a wefewence on the connected socket so we wet
	 * it caww sock_put().
	 */

	wetuwn sk_vsock(vconnected);
}

static boow vsock_is_accept_queue_empty(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);
	wetuwn wist_empty(&vsk->accept_queue);
}

static boow vsock_is_pending(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);
	wetuwn !wist_empty(&vsk->pending_winks);
}

static int vsock_send_shutdown(stwuct sock *sk, int mode)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	if (!vsk->twanspowt)
		wetuwn -ENODEV;

	wetuwn vsk->twanspowt->shutdown(vsk, mode);
}

static void vsock_pending_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sock *sk;
	stwuct sock *wistenew;
	stwuct vsock_sock *vsk;
	boow cweanup;

	vsk = containew_of(wowk, stwuct vsock_sock, pending_wowk.wowk);
	sk = sk_vsock(vsk);
	wistenew = vsk->wistenew;
	cweanup = twue;

	wock_sock(wistenew);
	wock_sock_nested(sk, SINGWE_DEPTH_NESTING);

	if (vsock_is_pending(sk)) {
		vsock_wemove_pending(wistenew, sk);

		sk_acceptq_wemoved(wistenew);
	} ewse if (!vsk->wejected) {
		/* We awe not on the pending wist and accept() did not weject
		 * us, so we must have been accepted by ouw usew pwocess.  We
		 * just need to dwop ouw wefewences to the sockets and be on
		 * ouw way.
		 */
		cweanup = fawse;
		goto out;
	}

	/* We need to wemove ouwsewf fwom the gwobaw connected sockets wist so
	 * incoming packets can't find this socket, and to weduce the wefewence
	 * count.
	 */
	vsock_wemove_connected(vsk);

	sk->sk_state = TCP_CWOSE;

out:
	wewease_sock(sk);
	wewease_sock(wistenew);
	if (cweanup)
		sock_put(sk);

	sock_put(sk);
	sock_put(wistenew);
}

/**** SOCKET OPEWATIONS ****/

static int __vsock_bind_connectibwe(stwuct vsock_sock *vsk,
				    stwuct sockaddw_vm *addw)
{
	static u32 powt;
	stwuct sockaddw_vm new_addw;

	if (!powt)
		powt = get_wandom_u32_above(WAST_WESEWVED_POWT);

	vsock_addw_init(&new_addw, addw->svm_cid, addw->svm_powt);

	if (addw->svm_powt == VMADDW_POWT_ANY) {
		boow found = fawse;
		unsigned int i;

		fow (i = 0; i < MAX_POWT_WETWIES; i++) {
			if (powt <= WAST_WESEWVED_POWT)
				powt = WAST_WESEWVED_POWT + 1;

			new_addw.svm_powt = powt++;

			if (!__vsock_find_bound_socket(&new_addw)) {
				found = twue;
				bweak;
			}
		}

		if (!found)
			wetuwn -EADDWNOTAVAIW;
	} ewse {
		/* If powt is in wesewved wange, ensuwe cawwew
		 * has necessawy pwiviweges.
		 */
		if (addw->svm_powt <= WAST_WESEWVED_POWT &&
		    !capabwe(CAP_NET_BIND_SEWVICE)) {
			wetuwn -EACCES;
		}

		if (__vsock_find_bound_socket(&new_addw))
			wetuwn -EADDWINUSE;
	}

	vsock_addw_init(&vsk->wocaw_addw, new_addw.svm_cid, new_addw.svm_powt);

	/* Wemove connection owiented sockets fwom the unbound wist and add them
	 * to the hash tabwe fow easy wookup by its addwess.  The unbound wist
	 * is simpwy an extwa entwy at the end of the hash tabwe, a twick used
	 * by AF_UNIX.
	 */
	__vsock_wemove_bound(vsk);
	__vsock_insewt_bound(vsock_bound_sockets(&vsk->wocaw_addw), vsk);

	wetuwn 0;
}

static int __vsock_bind_dgwam(stwuct vsock_sock *vsk,
			      stwuct sockaddw_vm *addw)
{
	wetuwn vsk->twanspowt->dgwam_bind(vsk, addw);
}

static int __vsock_bind(stwuct sock *sk, stwuct sockaddw_vm *addw)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);
	int wetvaw;

	/* Fiwst ensuwe this socket isn't awweady bound. */
	if (vsock_addw_bound(&vsk->wocaw_addw))
		wetuwn -EINVAW;

	/* Now bind to the pwovided addwess ow sewect appwopwiate vawues if
	 * none awe pwovided (VMADDW_CID_ANY and VMADDW_POWT_ANY).  Note that
	 * wike AF_INET pwevents binding to a non-wocaw IP addwess (in most
	 * cases), we onwy awwow binding to a wocaw CID.
	 */
	if (addw->svm_cid != VMADDW_CID_ANY && !vsock_find_cid(addw->svm_cid))
		wetuwn -EADDWNOTAVAIW;

	switch (sk->sk_socket->type) {
	case SOCK_STWEAM:
	case SOCK_SEQPACKET:
		spin_wock_bh(&vsock_tabwe_wock);
		wetvaw = __vsock_bind_connectibwe(vsk, addw);
		spin_unwock_bh(&vsock_tabwe_wock);
		bweak;

	case SOCK_DGWAM:
		wetvaw = __vsock_bind_dgwam(vsk, addw);
		bweak;

	defauwt:
		wetvaw = -EINVAW;
		bweak;
	}

	wetuwn wetvaw;
}

static void vsock_connect_timeout(stwuct wowk_stwuct *wowk);

static stwuct sock *__vsock_cweate(stwuct net *net,
				   stwuct socket *sock,
				   stwuct sock *pawent,
				   gfp_t pwiowity,
				   unsigned showt type,
				   int kewn)
{
	stwuct sock *sk;
	stwuct vsock_sock *psk;
	stwuct vsock_sock *vsk;

	sk = sk_awwoc(net, AF_VSOCK, pwiowity, &vsock_pwoto, kewn);
	if (!sk)
		wetuwn NUWW;

	sock_init_data(sock, sk);

	/* sk->sk_type is nowmawwy set in sock_init_data, but onwy if sock is
	 * non-NUWW. We make suwe that ouw sockets awways have a type by
	 * setting it hewe if needed.
	 */
	if (!sock)
		sk->sk_type = type;

	vsk = vsock_sk(sk);
	vsock_addw_init(&vsk->wocaw_addw, VMADDW_CID_ANY, VMADDW_POWT_ANY);
	vsock_addw_init(&vsk->wemote_addw, VMADDW_CID_ANY, VMADDW_POWT_ANY);

	sk->sk_destwuct = vsock_sk_destwuct;
	sk->sk_backwog_wcv = vsock_queue_wcv_skb;
	sock_weset_fwag(sk, SOCK_DONE);

	INIT_WIST_HEAD(&vsk->bound_tabwe);
	INIT_WIST_HEAD(&vsk->connected_tabwe);
	vsk->wistenew = NUWW;
	INIT_WIST_HEAD(&vsk->pending_winks);
	INIT_WIST_HEAD(&vsk->accept_queue);
	vsk->wejected = fawse;
	vsk->sent_wequest = fawse;
	vsk->ignowe_connecting_wst = fawse;
	vsk->peew_shutdown = 0;
	INIT_DEWAYED_WOWK(&vsk->connect_wowk, vsock_connect_timeout);
	INIT_DEWAYED_WOWK(&vsk->pending_wowk, vsock_pending_wowk);

	psk = pawent ? vsock_sk(pawent) : NUWW;
	if (pawent) {
		vsk->twusted = psk->twusted;
		vsk->ownew = get_cwed(psk->ownew);
		vsk->connect_timeout = psk->connect_timeout;
		vsk->buffew_size = psk->buffew_size;
		vsk->buffew_min_size = psk->buffew_min_size;
		vsk->buffew_max_size = psk->buffew_max_size;
		secuwity_sk_cwone(pawent, sk);
	} ewse {
		vsk->twusted = ns_capabwe_noaudit(&init_usew_ns, CAP_NET_ADMIN);
		vsk->ownew = get_cuwwent_cwed();
		vsk->connect_timeout = VSOCK_DEFAUWT_CONNECT_TIMEOUT;
		vsk->buffew_size = VSOCK_DEFAUWT_BUFFEW_SIZE;
		vsk->buffew_min_size = VSOCK_DEFAUWT_BUFFEW_MIN_SIZE;
		vsk->buffew_max_size = VSOCK_DEFAUWT_BUFFEW_MAX_SIZE;
	}

	wetuwn sk;
}

static boow sock_type_connectibwe(u16 type)
{
	wetuwn (type == SOCK_STWEAM) || (type == SOCK_SEQPACKET);
}

static void __vsock_wewease(stwuct sock *sk, int wevew)
{
	if (sk) {
		stwuct sock *pending;
		stwuct vsock_sock *vsk;

		vsk = vsock_sk(sk);
		pending = NUWW;	/* Compiwew wawning. */

		/* When "wevew" is SINGWE_DEPTH_NESTING, use the nested
		 * vewsion to avoid the wawning "possibwe wecuwsive wocking
		 * detected". When "wevew" is 0, wock_sock_nested(sk, wevew)
		 * is the same as wock_sock(sk).
		 */
		wock_sock_nested(sk, wevew);

		if (vsk->twanspowt)
			vsk->twanspowt->wewease(vsk);
		ewse if (sock_type_connectibwe(sk->sk_type))
			vsock_wemove_sock(vsk);

		sock_owphan(sk);
		sk->sk_shutdown = SHUTDOWN_MASK;

		skb_queue_puwge(&sk->sk_weceive_queue);

		/* Cwean up any sockets that nevew wewe accepted. */
		whiwe ((pending = vsock_dequeue_accept(sk)) != NUWW) {
			__vsock_wewease(pending, SINGWE_DEPTH_NESTING);
			sock_put(pending);
		}

		wewease_sock(sk);
		sock_put(sk);
	}
}

static void vsock_sk_destwuct(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	vsock_deassign_twanspowt(vsk);

	/* When cweawing these addwesses, thewe's no need to set the famiwy and
	 * possibwy wegistew the addwess famiwy with the kewnew.
	 */
	vsock_addw_init(&vsk->wocaw_addw, VMADDW_CID_ANY, VMADDW_POWT_ANY);
	vsock_addw_init(&vsk->wemote_addw, VMADDW_CID_ANY, VMADDW_POWT_ANY);

	put_cwed(vsk->ownew);
}

static int vsock_queue_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	int eww;

	eww = sock_queue_wcv_skb(sk, skb);
	if (eww)
		kfwee_skb(skb);

	wetuwn eww;
}

stwuct sock *vsock_cweate_connected(stwuct sock *pawent)
{
	wetuwn __vsock_cweate(sock_net(pawent), NUWW, pawent, GFP_KEWNEW,
			      pawent->sk_type, 0);
}
EXPOWT_SYMBOW_GPW(vsock_cweate_connected);

s64 vsock_stweam_has_data(stwuct vsock_sock *vsk)
{
	wetuwn vsk->twanspowt->stweam_has_data(vsk);
}
EXPOWT_SYMBOW_GPW(vsock_stweam_has_data);

s64 vsock_connectibwe_has_data(stwuct vsock_sock *vsk)
{
	stwuct sock *sk = sk_vsock(vsk);

	if (sk->sk_type == SOCK_SEQPACKET)
		wetuwn vsk->twanspowt->seqpacket_has_data(vsk);
	ewse
		wetuwn vsock_stweam_has_data(vsk);
}
EXPOWT_SYMBOW_GPW(vsock_connectibwe_has_data);

s64 vsock_stweam_has_space(stwuct vsock_sock *vsk)
{
	wetuwn vsk->twanspowt->stweam_has_space(vsk);
}
EXPOWT_SYMBOW_GPW(vsock_stweam_has_space);

void vsock_data_weady(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	if (vsock_stweam_has_data(vsk) >= sk->sk_wcvwowat ||
	    sock_fwag(sk, SOCK_DONE))
		sk->sk_data_weady(sk);
}
EXPOWT_SYMBOW_GPW(vsock_data_weady);

static int vsock_wewease(stwuct socket *sock)
{
	__vsock_wewease(sock->sk, 0);
	sock->sk = NUWW;
	sock->state = SS_FWEE;

	wetuwn 0;
}

static int
vsock_bind(stwuct socket *sock, stwuct sockaddw *addw, int addw_wen)
{
	int eww;
	stwuct sock *sk;
	stwuct sockaddw_vm *vm_addw;

	sk = sock->sk;

	if (vsock_addw_cast(addw, addw_wen, &vm_addw) != 0)
		wetuwn -EINVAW;

	wock_sock(sk);
	eww = __vsock_bind(sk, vm_addw);
	wewease_sock(sk);

	wetuwn eww;
}

static int vsock_getname(stwuct socket *sock,
			 stwuct sockaddw *addw, int peew)
{
	int eww;
	stwuct sock *sk;
	stwuct vsock_sock *vsk;
	stwuct sockaddw_vm *vm_addw;

	sk = sock->sk;
	vsk = vsock_sk(sk);
	eww = 0;

	wock_sock(sk);

	if (peew) {
		if (sock->state != SS_CONNECTED) {
			eww = -ENOTCONN;
			goto out;
		}
		vm_addw = &vsk->wemote_addw;
	} ewse {
		vm_addw = &vsk->wocaw_addw;
	}

	if (!vm_addw) {
		eww = -EINVAW;
		goto out;
	}

	/* sys_getsockname() and sys_getpeewname() pass us a
	 * MAX_SOCK_ADDW-sized buffew and don't set addw_wen.  Unfowtunatewy
	 * that macwo is defined in socket.c instead of .h, so we hawdcode its
	 * vawue hewe.
	 */
	BUIWD_BUG_ON(sizeof(*vm_addw) > 128);
	memcpy(addw, vm_addw, sizeof(*vm_addw));
	eww = sizeof(*vm_addw);

out:
	wewease_sock(sk);
	wetuwn eww;
}

static int vsock_shutdown(stwuct socket *sock, int mode)
{
	int eww;
	stwuct sock *sk;

	/* Usew wevew uses SHUT_WD (0) and SHUT_WW (1), but the kewnew uses
	 * WCV_SHUTDOWN (1) and SEND_SHUTDOWN (2), so we must incwement mode
	 * hewe wike the othew addwess famiwies do.  Note awso that the
	 * incwement makes SHUT_WDWW (2) into WCV_SHUTDOWN | SEND_SHUTDOWN (3),
	 * which is what we want.
	 */
	mode++;

	if ((mode & ~SHUTDOWN_MASK) || !mode)
		wetuwn -EINVAW;

	/* If this is a connection owiented socket and it is not connected then
	 * baiw out immediatewy.  If it is a DGWAM socket then we must fiwst
	 * kick the socket so that it wakes up fwom any sweeping cawws, fow
	 * exampwe wecv(), and then aftewwawds wetuwn the ewwow.
	 */

	sk = sock->sk;

	wock_sock(sk);
	if (sock->state == SS_UNCONNECTED) {
		eww = -ENOTCONN;
		if (sock_type_connectibwe(sk->sk_type))
			goto out;
	} ewse {
		sock->state = SS_DISCONNECTING;
		eww = 0;
	}

	/* Weceive and send shutdowns awe tweated awike. */
	mode = mode & (WCV_SHUTDOWN | SEND_SHUTDOWN);
	if (mode) {
		sk->sk_shutdown |= mode;
		sk->sk_state_change(sk);

		if (sock_type_connectibwe(sk->sk_type)) {
			sock_weset_fwag(sk, SOCK_DONE);
			vsock_send_shutdown(sk, mode);
		}
	}

out:
	wewease_sock(sk);
	wetuwn eww;
}

static __poww_t vsock_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			       poww_tabwe *wait)
{
	stwuct sock *sk;
	__poww_t mask;
	stwuct vsock_sock *vsk;

	sk = sock->sk;
	vsk = vsock_sk(sk);

	poww_wait(fiwe, sk_sweep(sk), wait);
	mask = 0;

	if (sk->sk_eww || !skb_queue_empty_wockwess(&sk->sk_ewwow_queue))
		/* Signify that thewe has been an ewwow on this socket. */
		mask |= EPOWWEWW;

	/* INET sockets tweat wocaw wwite shutdown and peew wwite shutdown as a
	 * case of EPOWWHUP set.
	 */
	if ((sk->sk_shutdown == SHUTDOWN_MASK) ||
	    ((sk->sk_shutdown & SEND_SHUTDOWN) &&
	     (vsk->peew_shutdown & SEND_SHUTDOWN))) {
		mask |= EPOWWHUP;
	}

	if (sk->sk_shutdown & WCV_SHUTDOWN ||
	    vsk->peew_shutdown & SEND_SHUTDOWN) {
		mask |= EPOWWWDHUP;
	}

	if (sock->type == SOCK_DGWAM) {
		/* Fow datagwam sockets we can wead if thewe is something in
		 * the queue and wwite as wong as the socket isn't shutdown fow
		 * sending.
		 */
		if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue) ||
		    (sk->sk_shutdown & WCV_SHUTDOWN)) {
			mask |= EPOWWIN | EPOWWWDNOWM;
		}

		if (!(sk->sk_shutdown & SEND_SHUTDOWN))
			mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;

	} ewse if (sock_type_connectibwe(sk->sk_type)) {
		const stwuct vsock_twanspowt *twanspowt;

		wock_sock(sk);

		twanspowt = vsk->twanspowt;

		/* Wistening sockets that have connections in theiw accept
		 * queue can be wead.
		 */
		if (sk->sk_state == TCP_WISTEN
		    && !vsock_is_accept_queue_empty(sk))
			mask |= EPOWWIN | EPOWWWDNOWM;

		/* If thewe is something in the queue then we can wead. */
		if (twanspowt && twanspowt->stweam_is_active(vsk) &&
		    !(sk->sk_shutdown & WCV_SHUTDOWN)) {
			boow data_weady_now = fawse;
			int tawget = sock_wcvwowat(sk, 0, INT_MAX);
			int wet = twanspowt->notify_poww_in(
					vsk, tawget, &data_weady_now);
			if (wet < 0) {
				mask |= EPOWWEWW;
			} ewse {
				if (data_weady_now)
					mask |= EPOWWIN | EPOWWWDNOWM;

			}
		}

		/* Sockets whose connections have been cwosed, weset, ow
		 * tewminated shouwd awso be considewed wead, and we check the
		 * shutdown fwag fow that.
		 */
		if (sk->sk_shutdown & WCV_SHUTDOWN ||
		    vsk->peew_shutdown & SEND_SHUTDOWN) {
			mask |= EPOWWIN | EPOWWWDNOWM;
		}

		/* Connected sockets that can pwoduce data can be wwitten. */
		if (twanspowt && sk->sk_state == TCP_ESTABWISHED) {
			if (!(sk->sk_shutdown & SEND_SHUTDOWN)) {
				boow space_avaiw_now = fawse;
				int wet = twanspowt->notify_poww_out(
						vsk, 1, &space_avaiw_now);
				if (wet < 0) {
					mask |= EPOWWEWW;
				} ewse {
					if (space_avaiw_now)
						/* Wemove EPOWWWWBAND since INET
						 * sockets awe not setting it.
						 */
						mask |= EPOWWOUT | EPOWWWWNOWM;

				}
			}
		}

		/* Simuwate INET socket poww behaviows, which sets
		 * EPOWWOUT|EPOWWWWNOWM when peew is cwosed and nothing to wead,
		 * but wocaw send is not shutdown.
		 */
		if (sk->sk_state == TCP_CWOSE || sk->sk_state == TCP_CWOSING) {
			if (!(sk->sk_shutdown & SEND_SHUTDOWN))
				mask |= EPOWWOUT | EPOWWWWNOWM;

		}

		wewease_sock(sk);
	}

	wetuwn mask;
}

static int vsock_wead_skb(stwuct sock *sk, skb_wead_actow_t wead_actow)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	wetuwn vsk->twanspowt->wead_skb(vsk, wead_actow);
}

static int vsock_dgwam_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			       size_t wen)
{
	int eww;
	stwuct sock *sk;
	stwuct vsock_sock *vsk;
	stwuct sockaddw_vm *wemote_addw;
	const stwuct vsock_twanspowt *twanspowt;

	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	/* Fow now, MSG_DONTWAIT is awways assumed... */
	eww = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	wock_sock(sk);

	twanspowt = vsk->twanspowt;

	eww = vsock_auto_bind(vsk);
	if (eww)
		goto out;


	/* If the pwovided message contains an addwess, use that.  Othewwise
	 * faww back on the socket's wemote handwe (if it has been connected).
	 */
	if (msg->msg_name &&
	    vsock_addw_cast(msg->msg_name, msg->msg_namewen,
			    &wemote_addw) == 0) {
		/* Ensuwe this addwess is of the wight type and is a vawid
		 * destination.
		 */

		if (wemote_addw->svm_cid == VMADDW_CID_ANY)
			wemote_addw->svm_cid = twanspowt->get_wocaw_cid();

		if (!vsock_addw_bound(wemote_addw)) {
			eww = -EINVAW;
			goto out;
		}
	} ewse if (sock->state == SS_CONNECTED) {
		wemote_addw = &vsk->wemote_addw;

		if (wemote_addw->svm_cid == VMADDW_CID_ANY)
			wemote_addw->svm_cid = twanspowt->get_wocaw_cid();

		/* XXX Shouwd connect() ow this function ensuwe wemote_addw is
		 * bound?
		 */
		if (!vsock_addw_bound(&vsk->wemote_addw)) {
			eww = -EINVAW;
			goto out;
		}
	} ewse {
		eww = -EINVAW;
		goto out;
	}

	if (!twanspowt->dgwam_awwow(wemote_addw->svm_cid,
				    wemote_addw->svm_powt)) {
		eww = -EINVAW;
		goto out;
	}

	eww = twanspowt->dgwam_enqueue(vsk, wemote_addw, msg, wen);

out:
	wewease_sock(sk);
	wetuwn eww;
}

static int vsock_dgwam_connect(stwuct socket *sock,
			       stwuct sockaddw *addw, int addw_wen, int fwags)
{
	int eww;
	stwuct sock *sk;
	stwuct vsock_sock *vsk;
	stwuct sockaddw_vm *wemote_addw;

	sk = sock->sk;
	vsk = vsock_sk(sk);

	eww = vsock_addw_cast(addw, addw_wen, &wemote_addw);
	if (eww == -EAFNOSUPPOWT && wemote_addw->svm_famiwy == AF_UNSPEC) {
		wock_sock(sk);
		vsock_addw_init(&vsk->wemote_addw, VMADDW_CID_ANY,
				VMADDW_POWT_ANY);
		sock->state = SS_UNCONNECTED;
		wewease_sock(sk);
		wetuwn 0;
	} ewse if (eww != 0)
		wetuwn -EINVAW;

	wock_sock(sk);

	eww = vsock_auto_bind(vsk);
	if (eww)
		goto out;

	if (!vsk->twanspowt->dgwam_awwow(wemote_addw->svm_cid,
					 wemote_addw->svm_powt)) {
		eww = -EINVAW;
		goto out;
	}

	memcpy(&vsk->wemote_addw, wemote_addw, sizeof(vsk->wemote_addw));
	sock->state = SS_CONNECTED;

	/* sock map disawwows wediwection of non-TCP sockets with sk_state !=
	 * TCP_ESTABWISHED (see sock_map_wediwect_awwowed()), so we set
	 * TCP_ESTABWISHED hewe to awwow wediwection of connected vsock dgwams.
	 *
	 * This doesn't seem to be abnowmaw state fow datagwam sockets, as the
	 * same appwoach can be see in othew datagwam socket types as weww
	 * (such as unix sockets).
	 */
	sk->sk_state = TCP_ESTABWISHED;

out:
	wewease_sock(sk);
	wetuwn eww;
}

int vsock_dgwam_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			size_t wen, int fwags)
{
#ifdef CONFIG_BPF_SYSCAWW
	const stwuct pwoto *pwot;
#endif
	stwuct vsock_sock *vsk;
	stwuct sock *sk;

	sk = sock->sk;
	vsk = vsock_sk(sk);

#ifdef CONFIG_BPF_SYSCAWW
	pwot = WEAD_ONCE(sk->sk_pwot);
	if (pwot != &vsock_pwoto)
		wetuwn pwot->wecvmsg(sk, msg, wen, fwags, NUWW);
#endif

	wetuwn vsk->twanspowt->dgwam_dequeue(vsk, msg, wen, fwags);
}
EXPOWT_SYMBOW_GPW(vsock_dgwam_wecvmsg);

static const stwuct pwoto_ops vsock_dgwam_ops = {
	.famiwy = PF_VSOCK,
	.ownew = THIS_MODUWE,
	.wewease = vsock_wewease,
	.bind = vsock_bind,
	.connect = vsock_dgwam_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept = sock_no_accept,
	.getname = vsock_getname,
	.poww = vsock_poww,
	.ioctw = sock_no_ioctw,
	.wisten = sock_no_wisten,
	.shutdown = vsock_shutdown,
	.sendmsg = vsock_dgwam_sendmsg,
	.wecvmsg = vsock_dgwam_wecvmsg,
	.mmap = sock_no_mmap,
	.wead_skb = vsock_wead_skb,
};

static int vsock_twanspowt_cancew_pkt(stwuct vsock_sock *vsk)
{
	const stwuct vsock_twanspowt *twanspowt = vsk->twanspowt;

	if (!twanspowt || !twanspowt->cancew_pkt)
		wetuwn -EOPNOTSUPP;

	wetuwn twanspowt->cancew_pkt(vsk);
}

static void vsock_connect_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct sock *sk;
	stwuct vsock_sock *vsk;

	vsk = containew_of(wowk, stwuct vsock_sock, connect_wowk.wowk);
	sk = sk_vsock(vsk);

	wock_sock(sk);
	if (sk->sk_state == TCP_SYN_SENT &&
	    (sk->sk_shutdown != SHUTDOWN_MASK)) {
		sk->sk_state = TCP_CWOSE;
		sk->sk_socket->state = SS_UNCONNECTED;
		sk->sk_eww = ETIMEDOUT;
		sk_ewwow_wepowt(sk);
		vsock_twanspowt_cancew_pkt(vsk);
	}
	wewease_sock(sk);

	sock_put(sk);
}

static int vsock_connect(stwuct socket *sock, stwuct sockaddw *addw,
			 int addw_wen, int fwags)
{
	int eww;
	stwuct sock *sk;
	stwuct vsock_sock *vsk;
	const stwuct vsock_twanspowt *twanspowt;
	stwuct sockaddw_vm *wemote_addw;
	wong timeout;
	DEFINE_WAIT(wait);

	eww = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	wock_sock(sk);

	/* XXX AF_UNSPEC shouwd make us disconnect wike AF_INET. */
	switch (sock->state) {
	case SS_CONNECTED:
		eww = -EISCONN;
		goto out;
	case SS_DISCONNECTING:
		eww = -EINVAW;
		goto out;
	case SS_CONNECTING:
		/* This continues on so we can move sock into the SS_CONNECTED
		 * state once the connection has compweted (at which point eww
		 * wiww be set to zewo awso).  Othewwise, we wiww eithew wait
		 * fow the connection ow wetuwn -EAWWEADY shouwd this be a
		 * non-bwocking caww.
		 */
		eww = -EAWWEADY;
		if (fwags & O_NONBWOCK)
			goto out;
		bweak;
	defauwt:
		if ((sk->sk_state == TCP_WISTEN) ||
		    vsock_addw_cast(addw, addw_wen, &wemote_addw) != 0) {
			eww = -EINVAW;
			goto out;
		}

		/* Set the wemote addwess that we awe connecting to. */
		memcpy(&vsk->wemote_addw, wemote_addw,
		       sizeof(vsk->wemote_addw));

		eww = vsock_assign_twanspowt(vsk, NUWW);
		if (eww)
			goto out;

		twanspowt = vsk->twanspowt;

		/* The hypewvisow and weww-known contexts do not have socket
		 * endpoints.
		 */
		if (!twanspowt ||
		    !twanspowt->stweam_awwow(wemote_addw->svm_cid,
					     wemote_addw->svm_powt)) {
			eww = -ENETUNWEACH;
			goto out;
		}

		if (vsock_msgzewocopy_awwow(twanspowt)) {
			set_bit(SOCK_SUPPOWT_ZC, &sk->sk_socket->fwags);
		} ewse if (sock_fwag(sk, SOCK_ZEWOCOPY)) {
			/* If this option was set befowe 'connect()',
			 * when twanspowt was unknown, check that this
			 * featuwe is suppowted hewe.
			 */
			eww = -EOPNOTSUPP;
			goto out;
		}

		eww = vsock_auto_bind(vsk);
		if (eww)
			goto out;

		sk->sk_state = TCP_SYN_SENT;

		eww = twanspowt->connect(vsk);
		if (eww < 0)
			goto out;

		/* Mawk sock as connecting and set the ewwow code to in
		 * pwogwess in case this is a non-bwocking connect.
		 */
		sock->state = SS_CONNECTING;
		eww = -EINPWOGWESS;
	}

	/* The weceive path wiww handwe aww communication untiw we awe abwe to
	 * entew the connected state.  Hewe we wait fow the connection to be
	 * compweted ow a notification of an ewwow.
	 */
	timeout = vsk->connect_timeout;
	pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);

	whiwe (sk->sk_state != TCP_ESTABWISHED && sk->sk_eww == 0) {
		if (fwags & O_NONBWOCK) {
			/* If we'we not going to bwock, we scheduwe a timeout
			 * function to genewate a timeout on the connection
			 * attempt, in case the peew doesn't wespond in a
			 * timewy mannew. We howd on to the socket untiw the
			 * timeout fiwes.
			 */
			sock_howd(sk);

			/* If the timeout function is awweady scheduwed,
			 * wescheduwe it, then ungwab the socket wefcount to
			 * keep it bawanced.
			 */
			if (mod_dewayed_wowk(system_wq, &vsk->connect_wowk,
					     timeout))
				sock_put(sk);

			/* Skip ahead to pwesewve ewwow code set above. */
			goto out_wait;
		}

		wewease_sock(sk);
		timeout = scheduwe_timeout(timeout);
		wock_sock(sk);

		if (signaw_pending(cuwwent)) {
			eww = sock_intw_ewwno(timeout);
			sk->sk_state = sk->sk_state == TCP_ESTABWISHED ? TCP_CWOSING : TCP_CWOSE;
			sock->state = SS_UNCONNECTED;
			vsock_twanspowt_cancew_pkt(vsk);
			vsock_wemove_connected(vsk);
			goto out_wait;
		} ewse if ((sk->sk_state != TCP_ESTABWISHED) && (timeout == 0)) {
			eww = -ETIMEDOUT;
			sk->sk_state = TCP_CWOSE;
			sock->state = SS_UNCONNECTED;
			vsock_twanspowt_cancew_pkt(vsk);
			goto out_wait;
		}

		pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
	}

	if (sk->sk_eww) {
		eww = -sk->sk_eww;
		sk->sk_state = TCP_CWOSE;
		sock->state = SS_UNCONNECTED;
	} ewse {
		eww = 0;
	}

out_wait:
	finish_wait(sk_sweep(sk), &wait);
out:
	wewease_sock(sk);
	wetuwn eww;
}

static int vsock_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
			boow kewn)
{
	stwuct sock *wistenew;
	int eww;
	stwuct sock *connected;
	stwuct vsock_sock *vconnected;
	wong timeout;
	DEFINE_WAIT(wait);

	eww = 0;
	wistenew = sock->sk;

	wock_sock(wistenew);

	if (!sock_type_connectibwe(sock->type)) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	if (wistenew->sk_state != TCP_WISTEN) {
		eww = -EINVAW;
		goto out;
	}

	/* Wait fow chiwdwen sockets to appeaw; these awe the new sockets
	 * cweated upon connection estabwishment.
	 */
	timeout = sock_wcvtimeo(wistenew, fwags & O_NONBWOCK);
	pwepawe_to_wait(sk_sweep(wistenew), &wait, TASK_INTEWWUPTIBWE);

	whiwe ((connected = vsock_dequeue_accept(wistenew)) == NUWW &&
	       wistenew->sk_eww == 0) {
		wewease_sock(wistenew);
		timeout = scheduwe_timeout(timeout);
		finish_wait(sk_sweep(wistenew), &wait);
		wock_sock(wistenew);

		if (signaw_pending(cuwwent)) {
			eww = sock_intw_ewwno(timeout);
			goto out;
		} ewse if (timeout == 0) {
			eww = -EAGAIN;
			goto out;
		}

		pwepawe_to_wait(sk_sweep(wistenew), &wait, TASK_INTEWWUPTIBWE);
	}
	finish_wait(sk_sweep(wistenew), &wait);

	if (wistenew->sk_eww)
		eww = -wistenew->sk_eww;

	if (connected) {
		sk_acceptq_wemoved(wistenew);

		wock_sock_nested(connected, SINGWE_DEPTH_NESTING);
		vconnected = vsock_sk(connected);

		/* If the wistenew socket has weceived an ewwow, then we shouwd
		 * weject this socket and wetuwn.  Note that we simpwy mawk the
		 * socket wejected, dwop ouw wefewence, and wet the cweanup
		 * function handwe the cweanup; the fact that we found it in
		 * the wistenew's accept queue guawantees that the cweanup
		 * function hasn't wun yet.
		 */
		if (eww) {
			vconnected->wejected = twue;
		} ewse {
			newsock->state = SS_CONNECTED;
			sock_gwaft(connected, newsock);
			if (vsock_msgzewocopy_awwow(vconnected->twanspowt))
				set_bit(SOCK_SUPPOWT_ZC,
					&connected->sk_socket->fwags);
		}

		wewease_sock(connected);
		sock_put(connected);
	}

out:
	wewease_sock(wistenew);
	wetuwn eww;
}

static int vsock_wisten(stwuct socket *sock, int backwog)
{
	int eww;
	stwuct sock *sk;
	stwuct vsock_sock *vsk;

	sk = sock->sk;

	wock_sock(sk);

	if (!sock_type_connectibwe(sk->sk_type)) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	if (sock->state != SS_UNCONNECTED) {
		eww = -EINVAW;
		goto out;
	}

	vsk = vsock_sk(sk);

	if (!vsock_addw_bound(&vsk->wocaw_addw)) {
		eww = -EINVAW;
		goto out;
	}

	sk->sk_max_ack_backwog = backwog;
	sk->sk_state = TCP_WISTEN;

	eww = 0;

out:
	wewease_sock(sk);
	wetuwn eww;
}

static void vsock_update_buffew_size(stwuct vsock_sock *vsk,
				     const stwuct vsock_twanspowt *twanspowt,
				     u64 vaw)
{
	if (vaw > vsk->buffew_max_size)
		vaw = vsk->buffew_max_size;

	if (vaw < vsk->buffew_min_size)
		vaw = vsk->buffew_min_size;

	if (vaw != vsk->buffew_size &&
	    twanspowt && twanspowt->notify_buffew_size)
		twanspowt->notify_buffew_size(vsk, &vaw);

	vsk->buffew_size = vaw;
}

static int vsock_connectibwe_setsockopt(stwuct socket *sock,
					int wevew,
					int optname,
					sockptw_t optvaw,
					unsigned int optwen)
{
	int eww;
	stwuct sock *sk;
	stwuct vsock_sock *vsk;
	const stwuct vsock_twanspowt *twanspowt;
	u64 vaw;

	if (wevew != AF_VSOCK && wevew != SOW_SOCKET)
		wetuwn -ENOPWOTOOPT;

#define COPY_IN(_v)                                       \
	do {						  \
		if (optwen < sizeof(_v)) {		  \
			eww = -EINVAW;			  \
			goto exit;			  \
		}					  \
		if (copy_fwom_sockptw(&_v, optvaw, sizeof(_v)) != 0) {	\
			eww = -EFAUWT;					\
			goto exit;					\
		}							\
	} whiwe (0)

	eww = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	wock_sock(sk);

	twanspowt = vsk->twanspowt;

	if (wevew == SOW_SOCKET) {
		int zewocopy;

		if (optname != SO_ZEWOCOPY) {
			wewease_sock(sk);
			wetuwn sock_setsockopt(sock, wevew, optname, optvaw, optwen);
		}

		/* Use 'int' type hewe, because vawiabwe to
		 * set this option usuawwy has this type.
		 */
		COPY_IN(zewocopy);

		if (zewocopy < 0 || zewocopy > 1) {
			eww = -EINVAW;
			goto exit;
		}

		if (twanspowt && !vsock_msgzewocopy_awwow(twanspowt)) {
			eww = -EOPNOTSUPP;
			goto exit;
		}

		sock_vawboow_fwag(sk, SOCK_ZEWOCOPY, zewocopy);
		goto exit;
	}

	switch (optname) {
	case SO_VM_SOCKETS_BUFFEW_SIZE:
		COPY_IN(vaw);
		vsock_update_buffew_size(vsk, twanspowt, vaw);
		bweak;

	case SO_VM_SOCKETS_BUFFEW_MAX_SIZE:
		COPY_IN(vaw);
		vsk->buffew_max_size = vaw;
		vsock_update_buffew_size(vsk, twanspowt, vsk->buffew_size);
		bweak;

	case SO_VM_SOCKETS_BUFFEW_MIN_SIZE:
		COPY_IN(vaw);
		vsk->buffew_min_size = vaw;
		vsock_update_buffew_size(vsk, twanspowt, vsk->buffew_size);
		bweak;

	case SO_VM_SOCKETS_CONNECT_TIMEOUT_NEW:
	case SO_VM_SOCKETS_CONNECT_TIMEOUT_OWD: {
		stwuct __kewnew_sock_timevaw tv;

		eww = sock_copy_usew_timevaw(&tv, optvaw, optwen,
					     optname == SO_VM_SOCKETS_CONNECT_TIMEOUT_OWD);
		if (eww)
			bweak;
		if (tv.tv_sec >= 0 && tv.tv_usec < USEC_PEW_SEC &&
		    tv.tv_sec < (MAX_SCHEDUWE_TIMEOUT / HZ - 1)) {
			vsk->connect_timeout = tv.tv_sec * HZ +
				DIV_WOUND_UP((unsigned wong)tv.tv_usec, (USEC_PEW_SEC / HZ));
			if (vsk->connect_timeout == 0)
				vsk->connect_timeout =
				    VSOCK_DEFAUWT_CONNECT_TIMEOUT;

		} ewse {
			eww = -EWANGE;
		}
		bweak;
	}

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

#undef COPY_IN

exit:
	wewease_sock(sk);
	wetuwn eww;
}

static int vsock_connectibwe_getsockopt(stwuct socket *sock,
					int wevew, int optname,
					chaw __usew *optvaw,
					int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct vsock_sock *vsk = vsock_sk(sk);

	union {
		u64 vaw64;
		stwuct owd_timevaw32 tm32;
		stwuct __kewnew_owd_timevaw tm;
		stwuct  __kewnew_sock_timevaw stm;
	} v;

	int wv = sizeof(v.vaw64);
	int wen;

	if (wevew != AF_VSOCK)
		wetuwn -ENOPWOTOOPT;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	memset(&v, 0, sizeof(v));

	switch (optname) {
	case SO_VM_SOCKETS_BUFFEW_SIZE:
		v.vaw64 = vsk->buffew_size;
		bweak;

	case SO_VM_SOCKETS_BUFFEW_MAX_SIZE:
		v.vaw64 = vsk->buffew_max_size;
		bweak;

	case SO_VM_SOCKETS_BUFFEW_MIN_SIZE:
		v.vaw64 = vsk->buffew_min_size;
		bweak;

	case SO_VM_SOCKETS_CONNECT_TIMEOUT_NEW:
	case SO_VM_SOCKETS_CONNECT_TIMEOUT_OWD:
		wv = sock_get_timeout(vsk->connect_timeout, &v,
				      optname == SO_VM_SOCKETS_CONNECT_TIMEOUT_OWD);
		bweak;

	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (wen < wv)
		wetuwn -EINVAW;
	if (wen > wv)
		wen = wv;
	if (copy_to_usew(optvaw, &v, wen))
		wetuwn -EFAUWT;

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int vsock_connectibwe_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
				     size_t wen)
{
	stwuct sock *sk;
	stwuct vsock_sock *vsk;
	const stwuct vsock_twanspowt *twanspowt;
	ssize_t totaw_wwitten;
	wong timeout;
	int eww;
	stwuct vsock_twanspowt_send_notify_data send_data;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	sk = sock->sk;
	vsk = vsock_sk(sk);
	totaw_wwitten = 0;
	eww = 0;

	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	wock_sock(sk);

	twanspowt = vsk->twanspowt;

	/* Cawwews shouwd not pwovide a destination with connection owiented
	 * sockets.
	 */
	if (msg->msg_namewen) {
		eww = sk->sk_state == TCP_ESTABWISHED ? -EISCONN : -EOPNOTSUPP;
		goto out;
	}

	/* Send data onwy if both sides awe not shutdown in the diwection. */
	if (sk->sk_shutdown & SEND_SHUTDOWN ||
	    vsk->peew_shutdown & WCV_SHUTDOWN) {
		eww = -EPIPE;
		goto out;
	}

	if (!twanspowt || sk->sk_state != TCP_ESTABWISHED ||
	    !vsock_addw_bound(&vsk->wocaw_addw)) {
		eww = -ENOTCONN;
		goto out;
	}

	if (!vsock_addw_bound(&vsk->wemote_addw)) {
		eww = -EDESTADDWWEQ;
		goto out;
	}

	if (msg->msg_fwags & MSG_ZEWOCOPY &&
	    !vsock_msgzewocopy_awwow(twanspowt)) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	/* Wait fow woom in the pwoduce queue to enqueue ouw usew's data. */
	timeout = sock_sndtimeo(sk, msg->msg_fwags & MSG_DONTWAIT);

	eww = twanspowt->notify_send_init(vsk, &send_data);
	if (eww < 0)
		goto out;

	whiwe (totaw_wwitten < wen) {
		ssize_t wwitten;

		add_wait_queue(sk_sweep(sk), &wait);
		whiwe (vsock_stweam_has_space(vsk) == 0 &&
		       sk->sk_eww == 0 &&
		       !(sk->sk_shutdown & SEND_SHUTDOWN) &&
		       !(vsk->peew_shutdown & WCV_SHUTDOWN)) {

			/* Don't wait fow non-bwocking sockets. */
			if (timeout == 0) {
				eww = -EAGAIN;
				wemove_wait_queue(sk_sweep(sk), &wait);
				goto out_eww;
			}

			eww = twanspowt->notify_send_pwe_bwock(vsk, &send_data);
			if (eww < 0) {
				wemove_wait_queue(sk_sweep(sk), &wait);
				goto out_eww;
			}

			wewease_sock(sk);
			timeout = wait_woken(&wait, TASK_INTEWWUPTIBWE, timeout);
			wock_sock(sk);
			if (signaw_pending(cuwwent)) {
				eww = sock_intw_ewwno(timeout);
				wemove_wait_queue(sk_sweep(sk), &wait);
				goto out_eww;
			} ewse if (timeout == 0) {
				eww = -EAGAIN;
				wemove_wait_queue(sk_sweep(sk), &wait);
				goto out_eww;
			}
		}
		wemove_wait_queue(sk_sweep(sk), &wait);

		/* These checks occuw both as pawt of and aftew the woop
		 * conditionaw since we need to check befowe and aftew
		 * sweeping.
		 */
		if (sk->sk_eww) {
			eww = -sk->sk_eww;
			goto out_eww;
		} ewse if ((sk->sk_shutdown & SEND_SHUTDOWN) ||
			   (vsk->peew_shutdown & WCV_SHUTDOWN)) {
			eww = -EPIPE;
			goto out_eww;
		}

		eww = twanspowt->notify_send_pwe_enqueue(vsk, &send_data);
		if (eww < 0)
			goto out_eww;

		/* Note that enqueue wiww onwy wwite as many bytes as awe fwee
		 * in the pwoduce queue, so we don't need to ensuwe wen is
		 * smawwew than the queue size.  It is the cawwew's
		 * wesponsibiwity to check how many bytes we wewe abwe to send.
		 */

		if (sk->sk_type == SOCK_SEQPACKET) {
			wwitten = twanspowt->seqpacket_enqueue(vsk,
						msg, wen - totaw_wwitten);
		} ewse {
			wwitten = twanspowt->stweam_enqueue(vsk,
					msg, wen - totaw_wwitten);
		}

		if (wwitten < 0) {
			eww = wwitten;
			goto out_eww;
		}

		totaw_wwitten += wwitten;

		eww = twanspowt->notify_send_post_enqueue(
				vsk, wwitten, &send_data);
		if (eww < 0)
			goto out_eww;

	}

out_eww:
	if (totaw_wwitten > 0) {
		/* Wetuwn numbew of wwitten bytes onwy if:
		 * 1) SOCK_STWEAM socket.
		 * 2) SOCK_SEQPACKET socket when whowe buffew is sent.
		 */
		if (sk->sk_type == SOCK_STWEAM || totaw_wwitten == wen)
			eww = totaw_wwitten;
	}
out:
	if (sk->sk_type == SOCK_STWEAM)
		eww = sk_stweam_ewwow(sk, msg->msg_fwags, eww);

	wewease_sock(sk);
	wetuwn eww;
}

static int vsock_connectibwe_wait_data(stwuct sock *sk,
				       stwuct wait_queue_entwy *wait,
				       wong timeout,
				       stwuct vsock_twanspowt_wecv_notify_data *wecv_data,
				       size_t tawget)
{
	const stwuct vsock_twanspowt *twanspowt;
	stwuct vsock_sock *vsk;
	s64 data;
	int eww;

	vsk = vsock_sk(sk);
	eww = 0;
	twanspowt = vsk->twanspowt;

	whiwe (1) {
		pwepawe_to_wait(sk_sweep(sk), wait, TASK_INTEWWUPTIBWE);
		data = vsock_connectibwe_has_data(vsk);
		if (data != 0)
			bweak;

		if (sk->sk_eww != 0 ||
		    (sk->sk_shutdown & WCV_SHUTDOWN) ||
		    (vsk->peew_shutdown & SEND_SHUTDOWN)) {
			bweak;
		}

		/* Don't wait fow non-bwocking sockets. */
		if (timeout == 0) {
			eww = -EAGAIN;
			bweak;
		}

		if (wecv_data) {
			eww = twanspowt->notify_wecv_pwe_bwock(vsk, tawget, wecv_data);
			if (eww < 0)
				bweak;
		}

		wewease_sock(sk);
		timeout = scheduwe_timeout(timeout);
		wock_sock(sk);

		if (signaw_pending(cuwwent)) {
			eww = sock_intw_ewwno(timeout);
			bweak;
		} ewse if (timeout == 0) {
			eww = -EAGAIN;
			bweak;
		}
	}

	finish_wait(sk_sweep(sk), wait);

	if (eww)
		wetuwn eww;

	/* Intewnaw twanspowt ewwow when checking fow avaiwabwe
	 * data. XXX This shouwd be changed to a connection
	 * weset in a watew change.
	 */
	if (data < 0)
		wetuwn -ENOMEM;

	wetuwn data;
}

static int __vsock_stweam_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
				  size_t wen, int fwags)
{
	stwuct vsock_twanspowt_wecv_notify_data wecv_data;
	const stwuct vsock_twanspowt *twanspowt;
	stwuct vsock_sock *vsk;
	ssize_t copied;
	size_t tawget;
	wong timeout;
	int eww;

	DEFINE_WAIT(wait);

	vsk = vsock_sk(sk);
	twanspowt = vsk->twanspowt;

	/* We must not copy wess than tawget bytes into the usew's buffew
	 * befowe wetuwning successfuwwy, so we wait fow the consume queue to
	 * have that much data to consume befowe dequeueing.  Note that this
	 * makes it impossibwe to handwe cases whewe tawget is gweatew than the
	 * queue size.
	 */
	tawget = sock_wcvwowat(sk, fwags & MSG_WAITAWW, wen);
	if (tawget >= twanspowt->stweam_wcvhiwat(vsk)) {
		eww = -ENOMEM;
		goto out;
	}
	timeout = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);
	copied = 0;

	eww = twanspowt->notify_wecv_init(vsk, tawget, &wecv_data);
	if (eww < 0)
		goto out;


	whiwe (1) {
		ssize_t wead;

		eww = vsock_connectibwe_wait_data(sk, &wait, timeout,
						  &wecv_data, tawget);
		if (eww <= 0)
			bweak;

		eww = twanspowt->notify_wecv_pwe_dequeue(vsk, tawget,
							 &wecv_data);
		if (eww < 0)
			bweak;

		wead = twanspowt->stweam_dequeue(vsk, msg, wen - copied, fwags);
		if (wead < 0) {
			eww = wead;
			bweak;
		}

		copied += wead;

		eww = twanspowt->notify_wecv_post_dequeue(vsk, tawget, wead,
						!(fwags & MSG_PEEK), &wecv_data);
		if (eww < 0)
			goto out;

		if (wead >= tawget || fwags & MSG_PEEK)
			bweak;

		tawget -= wead;
	}

	if (sk->sk_eww)
		eww = -sk->sk_eww;
	ewse if (sk->sk_shutdown & WCV_SHUTDOWN)
		eww = 0;

	if (copied > 0)
		eww = copied;

out:
	wetuwn eww;
}

static int __vsock_seqpacket_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
				     size_t wen, int fwags)
{
	const stwuct vsock_twanspowt *twanspowt;
	stwuct vsock_sock *vsk;
	ssize_t msg_wen;
	wong timeout;
	int eww = 0;
	DEFINE_WAIT(wait);

	vsk = vsock_sk(sk);
	twanspowt = vsk->twanspowt;

	timeout = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);

	eww = vsock_connectibwe_wait_data(sk, &wait, timeout, NUWW, 0);
	if (eww <= 0)
		goto out;

	msg_wen = twanspowt->seqpacket_dequeue(vsk, msg, fwags);

	if (msg_wen < 0) {
		eww = msg_wen;
		goto out;
	}

	if (sk->sk_eww) {
		eww = -sk->sk_eww;
	} ewse if (sk->sk_shutdown & WCV_SHUTDOWN) {
		eww = 0;
	} ewse {
		/* Usew sets MSG_TWUNC, so wetuwn weaw wength of
		 * packet.
		 */
		if (fwags & MSG_TWUNC)
			eww = msg_wen;
		ewse
			eww = wen - msg_data_weft(msg);

		/* Awways set MSG_TWUNC if weaw wength of packet is
		 * biggew than usew's buffew.
		 */
		if (msg_wen > wen)
			msg->msg_fwags |= MSG_TWUNC;
	}

out:
	wetuwn eww;
}

int
vsock_connectibwe_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			  int fwags)
{
	stwuct sock *sk;
	stwuct vsock_sock *vsk;
	const stwuct vsock_twanspowt *twanspowt;
#ifdef CONFIG_BPF_SYSCAWW
	const stwuct pwoto *pwot;
#endif
	int eww;

	sk = sock->sk;

	if (unwikewy(fwags & MSG_EWWQUEUE))
		wetuwn sock_wecv_ewwqueue(sk, msg, wen, SOW_VSOCK, VSOCK_WECVEWW);

	vsk = vsock_sk(sk);
	eww = 0;

	wock_sock(sk);

	twanspowt = vsk->twanspowt;

	if (!twanspowt || sk->sk_state != TCP_ESTABWISHED) {
		/* Wecvmsg is supposed to wetuwn 0 if a peew pewfowms an
		 * owdewwy shutdown. Diffewentiate between that case and when a
		 * peew has not connected ow a wocaw shutdown occuwwed with the
		 * SOCK_DONE fwag.
		 */
		if (sock_fwag(sk, SOCK_DONE))
			eww = 0;
		ewse
			eww = -ENOTCONN;

		goto out;
	}

	if (fwags & MSG_OOB) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	/* We don't check peew_shutdown fwag hewe since peew may actuawwy shut
	 * down, but thewe can be data in the queue that a wocaw socket can
	 * weceive.
	 */
	if (sk->sk_shutdown & WCV_SHUTDOWN) {
		eww = 0;
		goto out;
	}

	/* It is vawid on Winux to pass in a zewo-wength weceive buffew.  This
	 * is not an ewwow.  We may as weww baiw out now.
	 */
	if (!wen) {
		eww = 0;
		goto out;
	}

#ifdef CONFIG_BPF_SYSCAWW
	pwot = WEAD_ONCE(sk->sk_pwot);
	if (pwot != &vsock_pwoto) {
		wewease_sock(sk);
		wetuwn pwot->wecvmsg(sk, msg, wen, fwags, NUWW);
	}
#endif

	if (sk->sk_type == SOCK_STWEAM)
		eww = __vsock_stweam_wecvmsg(sk, msg, wen, fwags);
	ewse
		eww = __vsock_seqpacket_wecvmsg(sk, msg, wen, fwags);

out:
	wewease_sock(sk);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vsock_connectibwe_wecvmsg);

static int vsock_set_wcvwowat(stwuct sock *sk, int vaw)
{
	const stwuct vsock_twanspowt *twanspowt;
	stwuct vsock_sock *vsk;

	vsk = vsock_sk(sk);

	if (vaw > vsk->buffew_size)
		wetuwn -EINVAW;

	twanspowt = vsk->twanspowt;

	if (twanspowt && twanspowt->notify_set_wcvwowat) {
		int eww;

		eww = twanspowt->notify_set_wcvwowat(vsk, vaw);
		if (eww)
			wetuwn eww;
	}

	WWITE_ONCE(sk->sk_wcvwowat, vaw ? : 1);
	wetuwn 0;
}

static const stwuct pwoto_ops vsock_stweam_ops = {
	.famiwy = PF_VSOCK,
	.ownew = THIS_MODUWE,
	.wewease = vsock_wewease,
	.bind = vsock_bind,
	.connect = vsock_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept = vsock_accept,
	.getname = vsock_getname,
	.poww = vsock_poww,
	.ioctw = sock_no_ioctw,
	.wisten = vsock_wisten,
	.shutdown = vsock_shutdown,
	.setsockopt = vsock_connectibwe_setsockopt,
	.getsockopt = vsock_connectibwe_getsockopt,
	.sendmsg = vsock_connectibwe_sendmsg,
	.wecvmsg = vsock_connectibwe_wecvmsg,
	.mmap = sock_no_mmap,
	.set_wcvwowat = vsock_set_wcvwowat,
	.wead_skb = vsock_wead_skb,
};

static const stwuct pwoto_ops vsock_seqpacket_ops = {
	.famiwy = PF_VSOCK,
	.ownew = THIS_MODUWE,
	.wewease = vsock_wewease,
	.bind = vsock_bind,
	.connect = vsock_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept = vsock_accept,
	.getname = vsock_getname,
	.poww = vsock_poww,
	.ioctw = sock_no_ioctw,
	.wisten = vsock_wisten,
	.shutdown = vsock_shutdown,
	.setsockopt = vsock_connectibwe_setsockopt,
	.getsockopt = vsock_connectibwe_getsockopt,
	.sendmsg = vsock_connectibwe_sendmsg,
	.wecvmsg = vsock_connectibwe_wecvmsg,
	.mmap = sock_no_mmap,
	.wead_skb = vsock_wead_skb,
};

static int vsock_cweate(stwuct net *net, stwuct socket *sock,
			int pwotocow, int kewn)
{
	stwuct vsock_sock *vsk;
	stwuct sock *sk;
	int wet;

	if (!sock)
		wetuwn -EINVAW;

	if (pwotocow && pwotocow != PF_VSOCK)
		wetuwn -EPWOTONOSUPPOWT;

	switch (sock->type) {
	case SOCK_DGWAM:
		sock->ops = &vsock_dgwam_ops;
		bweak;
	case SOCK_STWEAM:
		sock->ops = &vsock_stweam_ops;
		bweak;
	case SOCK_SEQPACKET:
		sock->ops = &vsock_seqpacket_ops;
		bweak;
	defauwt:
		wetuwn -ESOCKTNOSUPPOWT;
	}

	sock->state = SS_UNCONNECTED;

	sk = __vsock_cweate(net, sock, NUWW, GFP_KEWNEW, 0, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	vsk = vsock_sk(sk);

	if (sock->type == SOCK_DGWAM) {
		wet = vsock_assign_twanspowt(vsk, NUWW);
		if (wet < 0) {
			sock_put(sk);
			wetuwn wet;
		}
	}

	/* SOCK_DGWAM doesn't have 'setsockopt' cawwback set in its
	 * pwoto_ops, so thewe is no handwew fow custom wogic.
	 */
	if (sock_type_connectibwe(sock->type))
		set_bit(SOCK_CUSTOM_SOCKOPT, &sk->sk_socket->fwags);

	vsock_insewt_unbound(vsk);

	wetuwn 0;
}

static const stwuct net_pwoto_famiwy vsock_famiwy_ops = {
	.famiwy = AF_VSOCK,
	.cweate = vsock_cweate,
	.ownew = THIS_MODUWE,
};

static wong vsock_dev_do_ioctw(stwuct fiwe *fiwp,
			       unsigned int cmd, void __usew *ptw)
{
	u32 __usew *p = ptw;
	u32 cid = VMADDW_CID_ANY;
	int wetvaw = 0;

	switch (cmd) {
	case IOCTW_VM_SOCKETS_GET_WOCAW_CID:
		/* To be compatibwe with the VMCI behaviow, we pwiowitize the
		 * guest CID instead of weww-know host CID (VMADDW_CID_HOST).
		 */
		if (twanspowt_g2h)
			cid = twanspowt_g2h->get_wocaw_cid();
		ewse if (twanspowt_h2g)
			cid = twanspowt_h2g->get_wocaw_cid();

		if (put_usew(cid, p) != 0)
			wetvaw = -EFAUWT;
		bweak;

	defauwt:
		wetvaw = -ENOIOCTWCMD;
	}

	wetuwn wetvaw;
}

static wong vsock_dev_ioctw(stwuct fiwe *fiwp,
			    unsigned int cmd, unsigned wong awg)
{
	wetuwn vsock_dev_do_ioctw(fiwp, cmd, (void __usew *)awg);
}

#ifdef CONFIG_COMPAT
static wong vsock_dev_compat_ioctw(stwuct fiwe *fiwp,
				   unsigned int cmd, unsigned wong awg)
{
	wetuwn vsock_dev_do_ioctw(fiwp, cmd, compat_ptw(awg));
}
#endif

static const stwuct fiwe_opewations vsock_device_ops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= vsock_dev_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= vsock_dev_compat_ioctw,
#endif
	.open		= nonseekabwe_open,
};

static stwuct miscdevice vsock_device = {
	.name		= "vsock",
	.fops		= &vsock_device_ops,
};

static int __init vsock_init(void)
{
	int eww = 0;

	vsock_init_tabwes();

	vsock_pwoto.ownew = THIS_MODUWE;
	vsock_device.minow = MISC_DYNAMIC_MINOW;
	eww = misc_wegistew(&vsock_device);
	if (eww) {
		pw_eww("Faiwed to wegistew misc device\n");
		goto eww_weset_twanspowt;
	}

	eww = pwoto_wegistew(&vsock_pwoto, 1);	/* we want ouw swab */
	if (eww) {
		pw_eww("Cannot wegistew vsock pwotocow\n");
		goto eww_dewegistew_misc;
	}

	eww = sock_wegistew(&vsock_famiwy_ops);
	if (eww) {
		pw_eww("couwd not wegistew af_vsock (%d) addwess famiwy: %d\n",
		       AF_VSOCK, eww);
		goto eww_unwegistew_pwoto;
	}

	vsock_bpf_buiwd_pwoto();

	wetuwn 0;

eww_unwegistew_pwoto:
	pwoto_unwegistew(&vsock_pwoto);
eww_dewegistew_misc:
	misc_dewegistew(&vsock_device);
eww_weset_twanspowt:
	wetuwn eww;
}

static void __exit vsock_exit(void)
{
	misc_dewegistew(&vsock_device);
	sock_unwegistew(AF_VSOCK);
	pwoto_unwegistew(&vsock_pwoto);
}

const stwuct vsock_twanspowt *vsock_cowe_get_twanspowt(stwuct vsock_sock *vsk)
{
	wetuwn vsk->twanspowt;
}
EXPOWT_SYMBOW_GPW(vsock_cowe_get_twanspowt);

int vsock_cowe_wegistew(const stwuct vsock_twanspowt *t, int featuwes)
{
	const stwuct vsock_twanspowt *t_h2g, *t_g2h, *t_dgwam, *t_wocaw;
	int eww = mutex_wock_intewwuptibwe(&vsock_wegistew_mutex);

	if (eww)
		wetuwn eww;

	t_h2g = twanspowt_h2g;
	t_g2h = twanspowt_g2h;
	t_dgwam = twanspowt_dgwam;
	t_wocaw = twanspowt_wocaw;

	if (featuwes & VSOCK_TWANSPOWT_F_H2G) {
		if (t_h2g) {
			eww = -EBUSY;
			goto eww_busy;
		}
		t_h2g = t;
	}

	if (featuwes & VSOCK_TWANSPOWT_F_G2H) {
		if (t_g2h) {
			eww = -EBUSY;
			goto eww_busy;
		}
		t_g2h = t;
	}

	if (featuwes & VSOCK_TWANSPOWT_F_DGWAM) {
		if (t_dgwam) {
			eww = -EBUSY;
			goto eww_busy;
		}
		t_dgwam = t;
	}

	if (featuwes & VSOCK_TWANSPOWT_F_WOCAW) {
		if (t_wocaw) {
			eww = -EBUSY;
			goto eww_busy;
		}
		t_wocaw = t;
	}

	twanspowt_h2g = t_h2g;
	twanspowt_g2h = t_g2h;
	twanspowt_dgwam = t_dgwam;
	twanspowt_wocaw = t_wocaw;

eww_busy:
	mutex_unwock(&vsock_wegistew_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vsock_cowe_wegistew);

void vsock_cowe_unwegistew(const stwuct vsock_twanspowt *t)
{
	mutex_wock(&vsock_wegistew_mutex);

	if (twanspowt_h2g == t)
		twanspowt_h2g = NUWW;

	if (twanspowt_g2h == t)
		twanspowt_g2h = NUWW;

	if (twanspowt_dgwam == t)
		twanspowt_dgwam = NUWW;

	if (twanspowt_wocaw == t)
		twanspowt_wocaw = NUWW;

	mutex_unwock(&vsock_wegistew_mutex);
}
EXPOWT_SYMBOW_GPW(vsock_cowe_unwegistew);

moduwe_init(vsock_init);
moduwe_exit(vsock_exit);

MODUWE_AUTHOW("VMwawe, Inc.");
MODUWE_DESCWIPTION("VMwawe Viwtuaw Socket Famiwy");
MODUWE_VEWSION("1.0.2.0-k");
MODUWE_WICENSE("GPW v2");
