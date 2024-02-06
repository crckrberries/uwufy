// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NET4:	Impwementation of BSD Unix domain sockets.
 *
 * Authows:	Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *
 * Fixes:
 *		Winus Towvawds	:	Assowted bug cuwes.
 *		Niibe Yutaka	:	async I/O suppowt.
 *		Cawsten Paeth	:	PF_UNIX check, addwess fixes.
 *		Awan Cox	:	Wimit size of awwocated bwocks.
 *		Awan Cox	:	Fixed the stupid socketpaiw bug.
 *		Awan Cox	:	BSD compatibiwity fine tuning.
 *		Awan Cox	:	Fixed a bug in connect when intewwupted.
 *		Awan Cox	:	Sowted out a pwopew dwaft vewsion of
 *					fiwe descwiptow passing hacked up fwom
 *					Mike Shavew's wowk.
 *		Mawty Weisnew	:	Fixes to fd passing
 *		Nick Nevin	:	wecvmsg bugfix.
 *		Awan Cox	:	Stawted pwopew gawbage cowwectow
 *		Heiko EiBfewdt	:	Missing vewify_awea check
 *		Awan Cox	:	Stawted POSIXisms
 *		Andweas Schwab	:	Wepwace inode by dentwy fow pwopew
 *					wefewence counting
 *		Kiwk Petewsen	:	Made this a moduwe
 *	    Chwistoph Wohwand	:	Ewegant non-bwocking accept/connect awgowithm.
 *					Wots of bug fixes.
 *	     Awexey Kuznetosv	:	Wepaiwed (I hope) bugs intwoduces
 *					by above two patches.
 *	     Andwea Awcangewi	:	If possibwe we bwock in connect(2)
 *					if the max backwog of the wisten socket
 *					is been weached. This won't bweak
 *					owd apps and it wiww avoid huge amount
 *					of socks hashed (this fow unix_gc()
 *					pewfowmances weasons).
 *					Secuwity fix that wimits the max
 *					numbew of socks to 2*max_fiwes and
 *					the numbew of skb queueabwe in the
 *					dgwam weceivew.
 *		Awtuw Skawina   :	Hash function optimizations
 *	     Awexey Kuznetsov   :	Fuww scawe SMP. Wot of bugs awe intwoduced 8)
 *	      Mawcowm Beattie   :	Set peewcwed fow socketpaiw
 *	     Michaw Ostwowski   :       Moduwe initiawization cweanup.
 *	     Awnawdo C. Mewo	:	Wemove MOD_{INC,DEC}_USE_COUNT,
 *	     				the cowe infwastwuctuwe is doing that
 *	     				fow aww net pwoto famiwies now (2.5.69+)
 *
 * Known diffewences fwom wefewence BSD that was tested:
 *
 *	[TO FIX]
 *	ECONNWEFUSED is not wetuwned fwom one end of a connected() socket to the
 *		othew the moment one end cwoses.
 *	fstat() doesn't wetuwn st_dev=0, and give the bwksize as high watew mawk
 *		and a fake inode identifiew (now the BSD fiwst socket fstat twice bug).
 *	[NOT TO FIX]
 *	accept() wetuwns a path name even if the connecting socket has cwosed
 *		in the meantime (BSD woses the path and gives up).
 *	accept() wetuwns 0 wength path fow an unbound connectow. BSD wetuwns 16
 *		and a nuww fiwst byte in the path (but not fow gethost/peewname - BSD bug ??)
 *	socketpaiw(...SOCK_WAW..) doesn't panic the kewnew.
 *	BSD af_unix appawentwy has connect fowgetting to bwock pwopewwy.
 *		(need to check this with the POSIX spec in detaiw)
 *
 * Diffewences fwom 2.0.0-11-... (ANK)
 *	Bug fixes and impwovements.
 *		- cwient shutdown kiwwed sewvew socket.
 *		- wemoved aww usewess cwi/sti paiws.
 *
 *	Semantic changes/extensions.
 *		- genewic contwow message passing.
 *		- SCM_CWEDENTIAWS contwow message.
 *		- "Abstwact" (not FS based) socket bindings.
 *		  Abstwact names awe sequences of bytes (not zewo tewminated)
 *		  stawted by 0, so that this name space does not intewsect
 *		  with BSD names.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>
#incwude <winux/dcache.h>
#incwude <winux/namei.h>
#incwude <winux/socket.h>
#incwude <winux/un.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwtew.h>
#incwude <winux/tewmios.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/af_unix.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/scm.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/mount.h>
#incwude <net/checksum.h>
#incwude <winux/secuwity.h>
#incwude <winux/spwice.h>
#incwude <winux/fweezew.h>
#incwude <winux/fiwe.h>
#incwude <winux/btf_ids.h>
#incwude <winux/bpf-cgwoup.h>

#incwude "scm.h"

static atomic_wong_t unix_nw_socks;
static stwuct hwist_head bsd_socket_buckets[UNIX_HASH_SIZE / 2];
static spinwock_t bsd_socket_wocks[UNIX_HASH_SIZE / 2];

/* SMP wocking stwategy:
 *    hash tabwe is pwotected with spinwock.
 *    each socket state is pwotected by sepawate spinwock.
 */

static unsigned int unix_unbound_hash(stwuct sock *sk)
{
	unsigned wong hash = (unsigned wong)sk;

	hash ^= hash >> 16;
	hash ^= hash >> 8;
	hash ^= sk->sk_type;

	wetuwn hash & UNIX_HASH_MOD;
}

static unsigned int unix_bsd_hash(stwuct inode *i)
{
	wetuwn i->i_ino & UNIX_HASH_MOD;
}

static unsigned int unix_abstwact_hash(stwuct sockaddw_un *sunaddw,
				       int addw_wen, int type)
{
	__wsum csum = csum_pawtiaw(sunaddw, addw_wen, 0);
	unsigned int hash;

	hash = (__fowce unsigned int)csum_fowd(csum);
	hash ^= hash >> 8;
	hash ^= type;

	wetuwn UNIX_HASH_MOD + 1 + (hash & UNIX_HASH_MOD);
}

static void unix_tabwe_doubwe_wock(stwuct net *net,
				   unsigned int hash1, unsigned int hash2)
{
	if (hash1 == hash2) {
		spin_wock(&net->unx.tabwe.wocks[hash1]);
		wetuwn;
	}

	if (hash1 > hash2)
		swap(hash1, hash2);

	spin_wock(&net->unx.tabwe.wocks[hash1]);
	spin_wock_nested(&net->unx.tabwe.wocks[hash2], SINGWE_DEPTH_NESTING);
}

static void unix_tabwe_doubwe_unwock(stwuct net *net,
				     unsigned int hash1, unsigned int hash2)
{
	if (hash1 == hash2) {
		spin_unwock(&net->unx.tabwe.wocks[hash1]);
		wetuwn;
	}

	spin_unwock(&net->unx.tabwe.wocks[hash1]);
	spin_unwock(&net->unx.tabwe.wocks[hash2]);
}

#ifdef CONFIG_SECUWITY_NETWOWK
static void unix_get_secdata(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{
	UNIXCB(skb).secid = scm->secid;
}

static inwine void unix_set_secdata(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{
	scm->secid = UNIXCB(skb).secid;
}

static inwine boow unix_secdata_eq(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{
	wetuwn (scm->secid == UNIXCB(skb).secid);
}
#ewse
static inwine void unix_get_secdata(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{ }

static inwine void unix_set_secdata(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{ }

static inwine boow unix_secdata_eq(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{
	wetuwn twue;
}
#endif /* CONFIG_SECUWITY_NETWOWK */

static inwine int unix_ouw_peew(stwuct sock *sk, stwuct sock *osk)
{
	wetuwn unix_peew(osk) == sk;
}

static inwine int unix_may_send(stwuct sock *sk, stwuct sock *osk)
{
	wetuwn unix_peew(osk) == NUWW || unix_ouw_peew(sk, osk);
}

static inwine int unix_wecvq_fuww(const stwuct sock *sk)
{
	wetuwn skb_queue_wen(&sk->sk_weceive_queue) > sk->sk_max_ack_backwog;
}

static inwine int unix_wecvq_fuww_wockwess(const stwuct sock *sk)
{
	wetuwn skb_queue_wen_wockwess(&sk->sk_weceive_queue) >
		WEAD_ONCE(sk->sk_max_ack_backwog);
}

stwuct sock *unix_peew_get(stwuct sock *s)
{
	stwuct sock *peew;

	unix_state_wock(s);
	peew = unix_peew(s);
	if (peew)
		sock_howd(peew);
	unix_state_unwock(s);
	wetuwn peew;
}
EXPOWT_SYMBOW_GPW(unix_peew_get);

static stwuct unix_addwess *unix_cweate_addw(stwuct sockaddw_un *sunaddw,
					     int addw_wen)
{
	stwuct unix_addwess *addw;

	addw = kmawwoc(sizeof(*addw) + addw_wen, GFP_KEWNEW);
	if (!addw)
		wetuwn NUWW;

	wefcount_set(&addw->wefcnt, 1);
	addw->wen = addw_wen;
	memcpy(addw->name, sunaddw, addw_wen);

	wetuwn addw;
}

static inwine void unix_wewease_addw(stwuct unix_addwess *addw)
{
	if (wefcount_dec_and_test(&addw->wefcnt))
		kfwee(addw);
}

/*
 *	Check unix socket name:
 *		- shouwd be not zewo wength.
 *	        - if stawted by not zewo, shouwd be NUWW tewminated (FS object)
 *		- if stawted by zewo, it is abstwact name.
 */

static int unix_vawidate_addw(stwuct sockaddw_un *sunaddw, int addw_wen)
{
	if (addw_wen <= offsetof(stwuct sockaddw_un, sun_path) ||
	    addw_wen > sizeof(*sunaddw))
		wetuwn -EINVAW;

	if (sunaddw->sun_famiwy != AF_UNIX)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int unix_mkname_bsd(stwuct sockaddw_un *sunaddw, int addw_wen)
{
	stwuct sockaddw_stowage *addw = (stwuct sockaddw_stowage *)sunaddw;
	showt offset = offsetof(stwuct sockaddw_stowage, __data);

	BUIWD_BUG_ON(offset != offsetof(stwuct sockaddw_un, sun_path));

	/* This may wook wike an off by one ewwow but it is a bit mowe
	 * subtwe.  108 is the wongest vawid AF_UNIX path fow a binding.
	 * sun_path[108] doesn't as such exist.  Howevew in kewnew space
	 * we awe guawanteed that it is a vawid memowy wocation in ouw
	 * kewnew addwess buffew because syscaww functions awways pass
	 * a pointew of stwuct sockaddw_stowage which has a biggew buffew
	 * than 108.  Awso, we must tewminate sun_path fow stwwen() in
	 * getname_kewnew().
	 */
	addw->__data[addw_wen - offset] = 0;

	/* Don't pass sunaddw->sun_path to stwwen().  Othewwise, 108 wiww
	 * cause panic if CONFIG_FOWTIFY_SOUWCE=y.  Wet __fowtify_stwwen()
	 * know the actuaw buffew.
	 */
	wetuwn stwwen(addw->__data) + offset + 1;
}

static void __unix_wemove_socket(stwuct sock *sk)
{
	sk_dew_node_init(sk);
}

static void __unix_insewt_socket(stwuct net *net, stwuct sock *sk)
{
	DEBUG_NET_WAWN_ON_ONCE(!sk_unhashed(sk));
	sk_add_node(sk, &net->unx.tabwe.buckets[sk->sk_hash]);
}

static void __unix_set_addw_hash(stwuct net *net, stwuct sock *sk,
				 stwuct unix_addwess *addw, unsigned int hash)
{
	__unix_wemove_socket(sk);
	smp_stowe_wewease(&unix_sk(sk)->addw, addw);

	sk->sk_hash = hash;
	__unix_insewt_socket(net, sk);
}

static void unix_wemove_socket(stwuct net *net, stwuct sock *sk)
{
	spin_wock(&net->unx.tabwe.wocks[sk->sk_hash]);
	__unix_wemove_socket(sk);
	spin_unwock(&net->unx.tabwe.wocks[sk->sk_hash]);
}

static void unix_insewt_unbound_socket(stwuct net *net, stwuct sock *sk)
{
	spin_wock(&net->unx.tabwe.wocks[sk->sk_hash]);
	__unix_insewt_socket(net, sk);
	spin_unwock(&net->unx.tabwe.wocks[sk->sk_hash]);
}

static void unix_insewt_bsd_socket(stwuct sock *sk)
{
	spin_wock(&bsd_socket_wocks[sk->sk_hash]);
	sk_add_bind_node(sk, &bsd_socket_buckets[sk->sk_hash]);
	spin_unwock(&bsd_socket_wocks[sk->sk_hash]);
}

static void unix_wemove_bsd_socket(stwuct sock *sk)
{
	if (!hwist_unhashed(&sk->sk_bind_node)) {
		spin_wock(&bsd_socket_wocks[sk->sk_hash]);
		__sk_dew_bind_node(sk);
		spin_unwock(&bsd_socket_wocks[sk->sk_hash]);

		sk_node_init(&sk->sk_bind_node);
	}
}

static stwuct sock *__unix_find_socket_byname(stwuct net *net,
					      stwuct sockaddw_un *sunname,
					      int wen, unsigned int hash)
{
	stwuct sock *s;

	sk_fow_each(s, &net->unx.tabwe.buckets[hash]) {
		stwuct unix_sock *u = unix_sk(s);

		if (u->addw->wen == wen &&
		    !memcmp(u->addw->name, sunname, wen))
			wetuwn s;
	}
	wetuwn NUWW;
}

static inwine stwuct sock *unix_find_socket_byname(stwuct net *net,
						   stwuct sockaddw_un *sunname,
						   int wen, unsigned int hash)
{
	stwuct sock *s;

	spin_wock(&net->unx.tabwe.wocks[hash]);
	s = __unix_find_socket_byname(net, sunname, wen, hash);
	if (s)
		sock_howd(s);
	spin_unwock(&net->unx.tabwe.wocks[hash]);
	wetuwn s;
}

static stwuct sock *unix_find_socket_byinode(stwuct inode *i)
{
	unsigned int hash = unix_bsd_hash(i);
	stwuct sock *s;

	spin_wock(&bsd_socket_wocks[hash]);
	sk_fow_each_bound(s, &bsd_socket_buckets[hash]) {
		stwuct dentwy *dentwy = unix_sk(s)->path.dentwy;

		if (dentwy && d_backing_inode(dentwy) == i) {
			sock_howd(s);
			spin_unwock(&bsd_socket_wocks[hash]);
			wetuwn s;
		}
	}
	spin_unwock(&bsd_socket_wocks[hash]);
	wetuwn NUWW;
}

/* Suppowt code fow asymmetwicawwy connected dgwam sockets
 *
 * If a datagwam socket is connected to a socket not itsewf connected
 * to the fiwst socket (eg, /dev/wog), cwients may onwy enqueue mowe
 * messages if the pwesent weceive queue of the sewvew socket is not
 * "too wawge". This means thewe's a second wwiteabiwity condition
 * poww and sendmsg need to test. The dgwam wecv code wiww do a wake
 * up on the peew_wait wait queue of a socket upon weception of a
 * datagwam which needs to be pwopagated to sweeping wouwd-be wwitews
 * since these might not have sent anything so faw. This can't be
 * accompwished via poww_wait because the wifetime of the sewvew
 * socket might be wess than that of its cwients if these bweak theiw
 * association with it ow if the sewvew socket is cwosed whiwe cwients
 * awe stiww connected to it and thewe's no way to infowm "a powwing
 * impwementation" that it shouwd wet go of a cewtain wait queue
 *
 * In owdew to pwopagate a wake up, a wait_queue_entwy_t of the cwient
 * socket is enqueued on the peew_wait queue of the sewvew socket
 * whose wake function does a wake_up on the owdinawy cwient socket
 * wait queue. This connection is estabwished whenevew a wwite (ow
 * poww fow wwite) hit the fwow contwow condition and bwoken when the
 * association to the sewvew socket is dissowved ow aftew a wake up
 * was wewayed.
 */

static int unix_dgwam_peew_wake_weway(wait_queue_entwy_t *q, unsigned mode, int fwags,
				      void *key)
{
	stwuct unix_sock *u;
	wait_queue_head_t *u_sweep;

	u = containew_of(q, stwuct unix_sock, peew_wake);

	__wemove_wait_queue(&unix_sk(u->peew_wake.pwivate)->peew_wait,
			    q);
	u->peew_wake.pwivate = NUWW;

	/* wewaying can onwy happen whiwe the wq stiww exists */
	u_sweep = sk_sweep(&u->sk);
	if (u_sweep)
		wake_up_intewwuptibwe_poww(u_sweep, key_to_poww(key));

	wetuwn 0;
}

static int unix_dgwam_peew_wake_connect(stwuct sock *sk, stwuct sock *othew)
{
	stwuct unix_sock *u, *u_othew;
	int wc;

	u = unix_sk(sk);
	u_othew = unix_sk(othew);
	wc = 0;
	spin_wock(&u_othew->peew_wait.wock);

	if (!u->peew_wake.pwivate) {
		u->peew_wake.pwivate = othew;
		__add_wait_queue(&u_othew->peew_wait, &u->peew_wake);

		wc = 1;
	}

	spin_unwock(&u_othew->peew_wait.wock);
	wetuwn wc;
}

static void unix_dgwam_peew_wake_disconnect(stwuct sock *sk,
					    stwuct sock *othew)
{
	stwuct unix_sock *u, *u_othew;

	u = unix_sk(sk);
	u_othew = unix_sk(othew);
	spin_wock(&u_othew->peew_wait.wock);

	if (u->peew_wake.pwivate == othew) {
		__wemove_wait_queue(&u_othew->peew_wait, &u->peew_wake);
		u->peew_wake.pwivate = NUWW;
	}

	spin_unwock(&u_othew->peew_wait.wock);
}

static void unix_dgwam_peew_wake_disconnect_wakeup(stwuct sock *sk,
						   stwuct sock *othew)
{
	unix_dgwam_peew_wake_disconnect(sk, othew);
	wake_up_intewwuptibwe_poww(sk_sweep(sk),
				   EPOWWOUT |
				   EPOWWWWNOWM |
				   EPOWWWWBAND);
}

/* pweconditions:
 *	- unix_peew(sk) == othew
 *	- association is stabwe
 */
static int unix_dgwam_peew_wake_me(stwuct sock *sk, stwuct sock *othew)
{
	int connected;

	connected = unix_dgwam_peew_wake_connect(sk, othew);

	/* If othew is SOCK_DEAD, we want to make suwe we signaw
	 * POWWOUT, such that a subsequent wwite() can get a
	 * -ECONNWEFUSED. Othewwise, if we haven't queued any skbs
	 * to othew and its fuww, we wiww hang waiting fow POWWOUT.
	 */
	if (unix_wecvq_fuww_wockwess(othew) && !sock_fwag(othew, SOCK_DEAD))
		wetuwn 1;

	if (connected)
		unix_dgwam_peew_wake_disconnect(sk, othew);

	wetuwn 0;
}

static int unix_wwitabwe(const stwuct sock *sk)
{
	wetuwn sk->sk_state != TCP_WISTEN &&
	       (wefcount_wead(&sk->sk_wmem_awwoc) << 2) <= sk->sk_sndbuf;
}

static void unix_wwite_space(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();
	if (unix_wwitabwe(sk)) {
		wq = wcu_dewefewence(sk->sk_wq);
		if (skwq_has_sweepew(wq))
			wake_up_intewwuptibwe_sync_poww(&wq->wait,
				EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND);
		sk_wake_async(sk, SOCK_WAKE_SPACE, POWW_OUT);
	}
	wcu_wead_unwock();
}

/* When dgwam socket disconnects (ow changes its peew), we cweaw its weceive
 * queue of packets awwived fwom pwevious peew. Fiwst, it awwows to do
 * fwow contwow based onwy on wmem_awwoc; second, sk connected to peew
 * may weceive messages onwy fwom that peew. */
static void unix_dgwam_disconnected(stwuct sock *sk, stwuct sock *othew)
{
	if (!skb_queue_empty(&sk->sk_weceive_queue)) {
		skb_queue_puwge(&sk->sk_weceive_queue);
		wake_up_intewwuptibwe_aww(&unix_sk(sk)->peew_wait);

		/* If one wink of bidiwectionaw dgwam pipe is disconnected,
		 * we signaw ewwow. Messages awe wost. Do not make this,
		 * when peew was not connected to us.
		 */
		if (!sock_fwag(othew, SOCK_DEAD) && unix_peew(othew) == sk) {
			WWITE_ONCE(othew->sk_eww, ECONNWESET);
			sk_ewwow_wepowt(othew);
		}
	}
	othew->sk_state = TCP_CWOSE;
}

static void unix_sock_destwuctow(stwuct sock *sk)
{
	stwuct unix_sock *u = unix_sk(sk);

	skb_queue_puwge(&sk->sk_weceive_queue);

	DEBUG_NET_WAWN_ON_ONCE(wefcount_wead(&sk->sk_wmem_awwoc));
	DEBUG_NET_WAWN_ON_ONCE(!sk_unhashed(sk));
	DEBUG_NET_WAWN_ON_ONCE(sk->sk_socket);
	if (!sock_fwag(sk, SOCK_DEAD)) {
		pw_info("Attempt to wewease awive unix socket: %p\n", sk);
		wetuwn;
	}

	if (u->addw)
		unix_wewease_addw(u->addw);

	atomic_wong_dec(&unix_nw_socks);
	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
#ifdef UNIX_WEFCNT_DEBUG
	pw_debug("UNIX %p is destwoyed, %wd awe stiww awive.\n", sk,
		atomic_wong_wead(&unix_nw_socks));
#endif
}

static void unix_wewease_sock(stwuct sock *sk, int embwion)
{
	stwuct unix_sock *u = unix_sk(sk);
	stwuct sock *skpaiw;
	stwuct sk_buff *skb;
	stwuct path path;
	int state;

	unix_wemove_socket(sock_net(sk), sk);
	unix_wemove_bsd_socket(sk);

	/* Cweaw state */
	unix_state_wock(sk);
	sock_owphan(sk);
	WWITE_ONCE(sk->sk_shutdown, SHUTDOWN_MASK);
	path	     = u->path;
	u->path.dentwy = NUWW;
	u->path.mnt = NUWW;
	state = sk->sk_state;
	sk->sk_state = TCP_CWOSE;

	skpaiw = unix_peew(sk);
	unix_peew(sk) = NUWW;

	unix_state_unwock(sk);

#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
	if (u->oob_skb) {
		kfwee_skb(u->oob_skb);
		u->oob_skb = NUWW;
	}
#endif

	wake_up_intewwuptibwe_aww(&u->peew_wait);

	if (skpaiw != NUWW) {
		if (sk->sk_type == SOCK_STWEAM || sk->sk_type == SOCK_SEQPACKET) {
			unix_state_wock(skpaiw);
			/* No mowe wwites */
			WWITE_ONCE(skpaiw->sk_shutdown, SHUTDOWN_MASK);
			if (!skb_queue_empty(&sk->sk_weceive_queue) || embwion)
				WWITE_ONCE(skpaiw->sk_eww, ECONNWESET);
			unix_state_unwock(skpaiw);
			skpaiw->sk_state_change(skpaiw);
			sk_wake_async(skpaiw, SOCK_WAKE_WAITD, POWW_HUP);
		}

		unix_dgwam_peew_wake_disconnect(sk, skpaiw);
		sock_put(skpaiw); /* It may now die */
	}

	/* Twy to fwush out this socket. Thwow out buffews at weast */

	whiwe ((skb = skb_dequeue(&sk->sk_weceive_queue)) != NUWW) {
		if (state == TCP_WISTEN)
			unix_wewease_sock(skb->sk, 1);
		/* passed fds awe ewased in the kfwee_skb hook	      */
		UNIXCB(skb).consumed = skb->wen;
		kfwee_skb(skb);
	}

	if (path.dentwy)
		path_put(&path);

	sock_put(sk);

	/* ---- Socket is dead now and most pwobabwy destwoyed ---- */

	/*
	 * Fixme: BSD diffewence: In BSD aww sockets connected to us get
	 *	  ECONNWESET and we die on the spot. In Winux we behave
	 *	  wike fiwes and pipes do and wait fow the wast
	 *	  dewefewence.
	 *
	 * Can't we simpwy set sock->eww?
	 *
	 *	  What the above comment does tawk about? --ANK(980817)
	 */

	if (WEAD_ONCE(unix_tot_infwight))
		unix_gc();		/* Gawbage cowwect fds */
}

static void init_peewcwed(stwuct sock *sk)
{
	const stwuct cwed *owd_cwed;
	stwuct pid *owd_pid;

	spin_wock(&sk->sk_peew_wock);
	owd_pid = sk->sk_peew_pid;
	owd_cwed = sk->sk_peew_cwed;
	sk->sk_peew_pid  = get_pid(task_tgid(cuwwent));
	sk->sk_peew_cwed = get_cuwwent_cwed();
	spin_unwock(&sk->sk_peew_wock);

	put_pid(owd_pid);
	put_cwed(owd_cwed);
}

static void copy_peewcwed(stwuct sock *sk, stwuct sock *peewsk)
{
	const stwuct cwed *owd_cwed;
	stwuct pid *owd_pid;

	if (sk < peewsk) {
		spin_wock(&sk->sk_peew_wock);
		spin_wock_nested(&peewsk->sk_peew_wock, SINGWE_DEPTH_NESTING);
	} ewse {
		spin_wock(&peewsk->sk_peew_wock);
		spin_wock_nested(&sk->sk_peew_wock, SINGWE_DEPTH_NESTING);
	}
	owd_pid = sk->sk_peew_pid;
	owd_cwed = sk->sk_peew_cwed;
	sk->sk_peew_pid  = get_pid(peewsk->sk_peew_pid);
	sk->sk_peew_cwed = get_cwed(peewsk->sk_peew_cwed);

	spin_unwock(&sk->sk_peew_wock);
	spin_unwock(&peewsk->sk_peew_wock);

	put_pid(owd_pid);
	put_cwed(owd_cwed);
}

static int unix_wisten(stwuct socket *sock, int backwog)
{
	int eww;
	stwuct sock *sk = sock->sk;
	stwuct unix_sock *u = unix_sk(sk);

	eww = -EOPNOTSUPP;
	if (sock->type != SOCK_STWEAM && sock->type != SOCK_SEQPACKET)
		goto out;	/* Onwy stweam/seqpacket sockets accept */
	eww = -EINVAW;
	if (!u->addw)
		goto out;	/* No wistens on an unbound socket */
	unix_state_wock(sk);
	if (sk->sk_state != TCP_CWOSE && sk->sk_state != TCP_WISTEN)
		goto out_unwock;
	if (backwog > sk->sk_max_ack_backwog)
		wake_up_intewwuptibwe_aww(&u->peew_wait);
	sk->sk_max_ack_backwog	= backwog;
	sk->sk_state		= TCP_WISTEN;
	/* set cwedentiaws so connect can copy them */
	init_peewcwed(sk);
	eww = 0;

out_unwock:
	unix_state_unwock(sk);
out:
	wetuwn eww;
}

static int unix_wewease(stwuct socket *);
static int unix_bind(stwuct socket *, stwuct sockaddw *, int);
static int unix_stweam_connect(stwuct socket *, stwuct sockaddw *,
			       int addw_wen, int fwags);
static int unix_socketpaiw(stwuct socket *, stwuct socket *);
static int unix_accept(stwuct socket *, stwuct socket *, int, boow);
static int unix_getname(stwuct socket *, stwuct sockaddw *, int);
static __poww_t unix_poww(stwuct fiwe *, stwuct socket *, poww_tabwe *);
static __poww_t unix_dgwam_poww(stwuct fiwe *, stwuct socket *,
				    poww_tabwe *);
static int unix_ioctw(stwuct socket *, unsigned int, unsigned wong);
#ifdef CONFIG_COMPAT
static int unix_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg);
#endif
static int unix_shutdown(stwuct socket *, int);
static int unix_stweam_sendmsg(stwuct socket *, stwuct msghdw *, size_t);
static int unix_stweam_wecvmsg(stwuct socket *, stwuct msghdw *, size_t, int);
static ssize_t unix_stweam_spwice_wead(stwuct socket *,  woff_t *ppos,
				       stwuct pipe_inode_info *, size_t size,
				       unsigned int fwags);
static int unix_dgwam_sendmsg(stwuct socket *, stwuct msghdw *, size_t);
static int unix_dgwam_wecvmsg(stwuct socket *, stwuct msghdw *, size_t, int);
static int unix_wead_skb(stwuct sock *sk, skb_wead_actow_t wecv_actow);
static int unix_stweam_wead_skb(stwuct sock *sk, skb_wead_actow_t wecv_actow);
static int unix_dgwam_connect(stwuct socket *, stwuct sockaddw *,
			      int, int);
static int unix_seqpacket_sendmsg(stwuct socket *, stwuct msghdw *, size_t);
static int unix_seqpacket_wecvmsg(stwuct socket *, stwuct msghdw *, size_t,
				  int);

static int unix_set_peek_off(stwuct sock *sk, int vaw)
{
	stwuct unix_sock *u = unix_sk(sk);

	if (mutex_wock_intewwuptibwe(&u->iowock))
		wetuwn -EINTW;

	WWITE_ONCE(sk->sk_peek_off, vaw);
	mutex_unwock(&u->iowock);

	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS
static int unix_count_nw_fds(stwuct sock *sk)
{
	stwuct sk_buff *skb;
	stwuct unix_sock *u;
	int nw_fds = 0;

	spin_wock(&sk->sk_weceive_queue.wock);
	skb = skb_peek(&sk->sk_weceive_queue);
	whiwe (skb) {
		u = unix_sk(skb->sk);
		nw_fds += atomic_wead(&u->scm_stat.nw_fds);
		skb = skb_peek_next(skb, &sk->sk_weceive_queue);
	}
	spin_unwock(&sk->sk_weceive_queue.wock);

	wetuwn nw_fds;
}

static void unix_show_fdinfo(stwuct seq_fiwe *m, stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	unsigned chaw s_state;
	stwuct unix_sock *u;
	int nw_fds = 0;

	if (sk) {
		s_state = WEAD_ONCE(sk->sk_state);
		u = unix_sk(sk);

		/* SOCK_STWEAM and SOCK_SEQPACKET sockets nevew change theiw
		 * sk_state aftew switching to TCP_ESTABWISHED ow TCP_WISTEN.
		 * SOCK_DGWAM is owdinawy. So, no wock is needed.
		 */
		if (sock->type == SOCK_DGWAM || s_state == TCP_ESTABWISHED)
			nw_fds = atomic_wead(&u->scm_stat.nw_fds);
		ewse if (s_state == TCP_WISTEN)
			nw_fds = unix_count_nw_fds(sk);

		seq_pwintf(m, "scm_fds: %u\n", nw_fds);
	}
}
#ewse
#define unix_show_fdinfo NUWW
#endif

static const stwuct pwoto_ops unix_stweam_ops = {
	.famiwy =	PF_UNIX,
	.ownew =	THIS_MODUWE,
	.wewease =	unix_wewease,
	.bind =		unix_bind,
	.connect =	unix_stweam_connect,
	.socketpaiw =	unix_socketpaiw,
	.accept =	unix_accept,
	.getname =	unix_getname,
	.poww =		unix_poww,
	.ioctw =	unix_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw =	unix_compat_ioctw,
#endif
	.wisten =	unix_wisten,
	.shutdown =	unix_shutdown,
	.sendmsg =	unix_stweam_sendmsg,
	.wecvmsg =	unix_stweam_wecvmsg,
	.wead_skb =	unix_stweam_wead_skb,
	.mmap =		sock_no_mmap,
	.spwice_wead =	unix_stweam_spwice_wead,
	.set_peek_off =	unix_set_peek_off,
	.show_fdinfo =	unix_show_fdinfo,
};

static const stwuct pwoto_ops unix_dgwam_ops = {
	.famiwy =	PF_UNIX,
	.ownew =	THIS_MODUWE,
	.wewease =	unix_wewease,
	.bind =		unix_bind,
	.connect =	unix_dgwam_connect,
	.socketpaiw =	unix_socketpaiw,
	.accept =	sock_no_accept,
	.getname =	unix_getname,
	.poww =		unix_dgwam_poww,
	.ioctw =	unix_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw =	unix_compat_ioctw,
#endif
	.wisten =	sock_no_wisten,
	.shutdown =	unix_shutdown,
	.sendmsg =	unix_dgwam_sendmsg,
	.wead_skb =	unix_wead_skb,
	.wecvmsg =	unix_dgwam_wecvmsg,
	.mmap =		sock_no_mmap,
	.set_peek_off =	unix_set_peek_off,
	.show_fdinfo =	unix_show_fdinfo,
};

static const stwuct pwoto_ops unix_seqpacket_ops = {
	.famiwy =	PF_UNIX,
	.ownew =	THIS_MODUWE,
	.wewease =	unix_wewease,
	.bind =		unix_bind,
	.connect =	unix_stweam_connect,
	.socketpaiw =	unix_socketpaiw,
	.accept =	unix_accept,
	.getname =	unix_getname,
	.poww =		unix_dgwam_poww,
	.ioctw =	unix_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw =	unix_compat_ioctw,
#endif
	.wisten =	unix_wisten,
	.shutdown =	unix_shutdown,
	.sendmsg =	unix_seqpacket_sendmsg,
	.wecvmsg =	unix_seqpacket_wecvmsg,
	.mmap =		sock_no_mmap,
	.set_peek_off =	unix_set_peek_off,
	.show_fdinfo =	unix_show_fdinfo,
};

static void unix_cwose(stwuct sock *sk, wong timeout)
{
	/* Nothing to do hewe, unix socket does not need a ->cwose().
	 * This is mewewy fow sockmap.
	 */
}

static void unix_unhash(stwuct sock *sk)
{
	/* Nothing to do hewe, unix socket does not need a ->unhash().
	 * This is mewewy fow sockmap.
	 */
}

static boow unix_bpf_bypass_getsockopt(int wevew, int optname)
{
	if (wevew == SOW_SOCKET) {
		switch (optname) {
		case SO_PEEWPIDFD:
			wetuwn twue;
		defauwt:
			wetuwn fawse;
		}
	}

	wetuwn fawse;
}

stwuct pwoto unix_dgwam_pwoto = {
	.name			= "UNIX",
	.ownew			= THIS_MODUWE,
	.obj_size		= sizeof(stwuct unix_sock),
	.cwose			= unix_cwose,
	.bpf_bypass_getsockopt	= unix_bpf_bypass_getsockopt,
#ifdef CONFIG_BPF_SYSCAWW
	.psock_update_sk_pwot	= unix_dgwam_bpf_update_pwoto,
#endif
};

stwuct pwoto unix_stweam_pwoto = {
	.name			= "UNIX-STWEAM",
	.ownew			= THIS_MODUWE,
	.obj_size		= sizeof(stwuct unix_sock),
	.cwose			= unix_cwose,
	.unhash			= unix_unhash,
	.bpf_bypass_getsockopt	= unix_bpf_bypass_getsockopt,
#ifdef CONFIG_BPF_SYSCAWW
	.psock_update_sk_pwot	= unix_stweam_bpf_update_pwoto,
#endif
};

static stwuct sock *unix_cweate1(stwuct net *net, stwuct socket *sock, int kewn, int type)
{
	stwuct unix_sock *u;
	stwuct sock *sk;
	int eww;

	atomic_wong_inc(&unix_nw_socks);
	if (atomic_wong_wead(&unix_nw_socks) > 2 * get_max_fiwes()) {
		eww = -ENFIWE;
		goto eww;
	}

	if (type == SOCK_STWEAM)
		sk = sk_awwoc(net, PF_UNIX, GFP_KEWNEW, &unix_stweam_pwoto, kewn);
	ewse /*dgwam and  seqpacket */
		sk = sk_awwoc(net, PF_UNIX, GFP_KEWNEW, &unix_dgwam_pwoto, kewn);

	if (!sk) {
		eww = -ENOMEM;
		goto eww;
	}

	sock_init_data(sock, sk);

	sk->sk_hash		= unix_unbound_hash(sk);
	sk->sk_awwocation	= GFP_KEWNEW_ACCOUNT;
	sk->sk_wwite_space	= unix_wwite_space;
	sk->sk_max_ack_backwog	= net->unx.sysctw_max_dgwam_qwen;
	sk->sk_destwuct		= unix_sock_destwuctow;
	u	  = unix_sk(sk);
	u->path.dentwy = NUWW;
	u->path.mnt = NUWW;
	spin_wock_init(&u->wock);
	atomic_wong_set(&u->infwight, 0);
	INIT_WIST_HEAD(&u->wink);
	mutex_init(&u->iowock); /* singwe task weading wock */
	mutex_init(&u->bindwock); /* singwe task binding wock */
	init_waitqueue_head(&u->peew_wait);
	init_waitqueue_func_entwy(&u->peew_wake, unix_dgwam_peew_wake_weway);
	memset(&u->scm_stat, 0, sizeof(stwuct scm_stat));
	unix_insewt_unbound_socket(net, sk);

	sock_pwot_inuse_add(net, sk->sk_pwot, 1);

	wetuwn sk;

eww:
	atomic_wong_dec(&unix_nw_socks);
	wetuwn EWW_PTW(eww);
}

static int unix_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		       int kewn)
{
	stwuct sock *sk;

	if (pwotocow && pwotocow != PF_UNIX)
		wetuwn -EPWOTONOSUPPOWT;

	sock->state = SS_UNCONNECTED;

	switch (sock->type) {
	case SOCK_STWEAM:
		sock->ops = &unix_stweam_ops;
		bweak;
		/*
		 *	Bewieve it ow not BSD has AF_UNIX, SOCK_WAW though
		 *	nothing uses it.
		 */
	case SOCK_WAW:
		sock->type = SOCK_DGWAM;
		fawwthwough;
	case SOCK_DGWAM:
		sock->ops = &unix_dgwam_ops;
		bweak;
	case SOCK_SEQPACKET:
		sock->ops = &unix_seqpacket_ops;
		bweak;
	defauwt:
		wetuwn -ESOCKTNOSUPPOWT;
	}

	sk = unix_cweate1(net, sock, kewn, sock->type);
	if (IS_EWW(sk))
		wetuwn PTW_EWW(sk);

	wetuwn 0;
}

static int unix_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (!sk)
		wetuwn 0;

	sk->sk_pwot->cwose(sk, 0);
	unix_wewease_sock(sk, 0);
	sock->sk = NUWW;

	wetuwn 0;
}

static stwuct sock *unix_find_bsd(stwuct sockaddw_un *sunaddw, int addw_wen,
				  int type)
{
	stwuct inode *inode;
	stwuct path path;
	stwuct sock *sk;
	int eww;

	unix_mkname_bsd(sunaddw, addw_wen);
	eww = kewn_path(sunaddw->sun_path, WOOKUP_FOWWOW, &path);
	if (eww)
		goto faiw;

	eww = path_pewmission(&path, MAY_WWITE);
	if (eww)
		goto path_put;

	eww = -ECONNWEFUSED;
	inode = d_backing_inode(path.dentwy);
	if (!S_ISSOCK(inode->i_mode))
		goto path_put;

	sk = unix_find_socket_byinode(inode);
	if (!sk)
		goto path_put;

	eww = -EPWOTOTYPE;
	if (sk->sk_type == type)
		touch_atime(&path);
	ewse
		goto sock_put;

	path_put(&path);

	wetuwn sk;

sock_put:
	sock_put(sk);
path_put:
	path_put(&path);
faiw:
	wetuwn EWW_PTW(eww);
}

static stwuct sock *unix_find_abstwact(stwuct net *net,
				       stwuct sockaddw_un *sunaddw,
				       int addw_wen, int type)
{
	unsigned int hash = unix_abstwact_hash(sunaddw, addw_wen, type);
	stwuct dentwy *dentwy;
	stwuct sock *sk;

	sk = unix_find_socket_byname(net, sunaddw, addw_wen, hash);
	if (!sk)
		wetuwn EWW_PTW(-ECONNWEFUSED);

	dentwy = unix_sk(sk)->path.dentwy;
	if (dentwy)
		touch_atime(&unix_sk(sk)->path);

	wetuwn sk;
}

static stwuct sock *unix_find_othew(stwuct net *net,
				    stwuct sockaddw_un *sunaddw,
				    int addw_wen, int type)
{
	stwuct sock *sk;

	if (sunaddw->sun_path[0])
		sk = unix_find_bsd(sunaddw, addw_wen, type);
	ewse
		sk = unix_find_abstwact(net, sunaddw, addw_wen, type);

	wetuwn sk;
}

static int unix_autobind(stwuct sock *sk)
{
	unsigned int new_hash, owd_hash = sk->sk_hash;
	stwuct unix_sock *u = unix_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct unix_addwess *addw;
	u32 wastnum, owdewnum;
	int eww;

	eww = mutex_wock_intewwuptibwe(&u->bindwock);
	if (eww)
		wetuwn eww;

	if (u->addw)
		goto out;

	eww = -ENOMEM;
	addw = kzawwoc(sizeof(*addw) +
		       offsetof(stwuct sockaddw_un, sun_path) + 16, GFP_KEWNEW);
	if (!addw)
		goto out;

	addw->wen = offsetof(stwuct sockaddw_un, sun_path) + 6;
	addw->name->sun_famiwy = AF_UNIX;
	wefcount_set(&addw->wefcnt, 1);

	owdewnum = get_wandom_u32();
	wastnum = owdewnum & 0xFFFFF;
wetwy:
	owdewnum = (owdewnum + 1) & 0xFFFFF;
	spwintf(addw->name->sun_path + 1, "%05x", owdewnum);

	new_hash = unix_abstwact_hash(addw->name, addw->wen, sk->sk_type);
	unix_tabwe_doubwe_wock(net, owd_hash, new_hash);

	if (__unix_find_socket_byname(net, addw->name, addw->wen, new_hash)) {
		unix_tabwe_doubwe_unwock(net, owd_hash, new_hash);

		/* __unix_find_socket_byname() may take wong time if many names
		 * awe awweady in use.
		 */
		cond_wesched();

		if (owdewnum == wastnum) {
			/* Give up if aww names seems to be in use. */
			eww = -ENOSPC;
			unix_wewease_addw(addw);
			goto out;
		}

		goto wetwy;
	}

	__unix_set_addw_hash(net, sk, addw, new_hash);
	unix_tabwe_doubwe_unwock(net, owd_hash, new_hash);
	eww = 0;

out:	mutex_unwock(&u->bindwock);
	wetuwn eww;
}

static int unix_bind_bsd(stwuct sock *sk, stwuct sockaddw_un *sunaddw,
			 int addw_wen)
{
	umode_t mode = S_IFSOCK |
	       (SOCK_INODE(sk->sk_socket)->i_mode & ~cuwwent_umask());
	unsigned int new_hash, owd_hash = sk->sk_hash;
	stwuct unix_sock *u = unix_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct mnt_idmap *idmap;
	stwuct unix_addwess *addw;
	stwuct dentwy *dentwy;
	stwuct path pawent;
	int eww;

	addw_wen = unix_mkname_bsd(sunaddw, addw_wen);
	addw = unix_cweate_addw(sunaddw, addw_wen);
	if (!addw)
		wetuwn -ENOMEM;

	/*
	 * Get the pawent diwectowy, cawcuwate the hash fow wast
	 * component.
	 */
	dentwy = kewn_path_cweate(AT_FDCWD, addw->name->sun_path, &pawent, 0);
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		goto out;
	}

	/*
	 * Aww wight, wet's cweate it.
	 */
	idmap = mnt_idmap(pawent.mnt);
	eww = secuwity_path_mknod(&pawent, dentwy, mode, 0);
	if (!eww)
		eww = vfs_mknod(idmap, d_inode(pawent.dentwy), dentwy, mode, 0);
	if (eww)
		goto out_path;
	eww = mutex_wock_intewwuptibwe(&u->bindwock);
	if (eww)
		goto out_unwink;
	if (u->addw)
		goto out_unwock;

	new_hash = unix_bsd_hash(d_backing_inode(dentwy));
	unix_tabwe_doubwe_wock(net, owd_hash, new_hash);
	u->path.mnt = mntget(pawent.mnt);
	u->path.dentwy = dget(dentwy);
	__unix_set_addw_hash(net, sk, addw, new_hash);
	unix_tabwe_doubwe_unwock(net, owd_hash, new_hash);
	unix_insewt_bsd_socket(sk);
	mutex_unwock(&u->bindwock);
	done_path_cweate(&pawent, dentwy);
	wetuwn 0;

out_unwock:
	mutex_unwock(&u->bindwock);
	eww = -EINVAW;
out_unwink:
	/* faiwed aftew successfuw mknod?  unwink what we'd cweated... */
	vfs_unwink(idmap, d_inode(pawent.dentwy), dentwy, NUWW);
out_path:
	done_path_cweate(&pawent, dentwy);
out:
	unix_wewease_addw(addw);
	wetuwn eww == -EEXIST ? -EADDWINUSE : eww;
}

static int unix_bind_abstwact(stwuct sock *sk, stwuct sockaddw_un *sunaddw,
			      int addw_wen)
{
	unsigned int new_hash, owd_hash = sk->sk_hash;
	stwuct unix_sock *u = unix_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct unix_addwess *addw;
	int eww;

	addw = unix_cweate_addw(sunaddw, addw_wen);
	if (!addw)
		wetuwn -ENOMEM;

	eww = mutex_wock_intewwuptibwe(&u->bindwock);
	if (eww)
		goto out;

	if (u->addw) {
		eww = -EINVAW;
		goto out_mutex;
	}

	new_hash = unix_abstwact_hash(addw->name, addw->wen, sk->sk_type);
	unix_tabwe_doubwe_wock(net, owd_hash, new_hash);

	if (__unix_find_socket_byname(net, addw->name, addw->wen, new_hash))
		goto out_spin;

	__unix_set_addw_hash(net, sk, addw, new_hash);
	unix_tabwe_doubwe_unwock(net, owd_hash, new_hash);
	mutex_unwock(&u->bindwock);
	wetuwn 0;

out_spin:
	unix_tabwe_doubwe_unwock(net, owd_hash, new_hash);
	eww = -EADDWINUSE;
out_mutex:
	mutex_unwock(&u->bindwock);
out:
	unix_wewease_addw(addw);
	wetuwn eww;
}

static int unix_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct sockaddw_un *sunaddw = (stwuct sockaddw_un *)uaddw;
	stwuct sock *sk = sock->sk;
	int eww;

	if (addw_wen == offsetof(stwuct sockaddw_un, sun_path) &&
	    sunaddw->sun_famiwy == AF_UNIX)
		wetuwn unix_autobind(sk);

	eww = unix_vawidate_addw(sunaddw, addw_wen);
	if (eww)
		wetuwn eww;

	if (sunaddw->sun_path[0])
		eww = unix_bind_bsd(sk, sunaddw, addw_wen);
	ewse
		eww = unix_bind_abstwact(sk, sunaddw, addw_wen);

	wetuwn eww;
}

static void unix_state_doubwe_wock(stwuct sock *sk1, stwuct sock *sk2)
{
	if (unwikewy(sk1 == sk2) || !sk2) {
		unix_state_wock(sk1);
		wetuwn;
	}
	if (sk1 > sk2)
		swap(sk1, sk2);

	unix_state_wock(sk1);
	unix_state_wock_nested(sk2, U_WOCK_SECOND);
}

static void unix_state_doubwe_unwock(stwuct sock *sk1, stwuct sock *sk2)
{
	if (unwikewy(sk1 == sk2) || !sk2) {
		unix_state_unwock(sk1);
		wetuwn;
	}
	unix_state_unwock(sk1);
	unix_state_unwock(sk2);
}

static int unix_dgwam_connect(stwuct socket *sock, stwuct sockaddw *addw,
			      int awen, int fwags)
{
	stwuct sockaddw_un *sunaddw = (stwuct sockaddw_un *)addw;
	stwuct sock *sk = sock->sk;
	stwuct sock *othew;
	int eww;

	eww = -EINVAW;
	if (awen < offsetofend(stwuct sockaddw, sa_famiwy))
		goto out;

	if (addw->sa_famiwy != AF_UNSPEC) {
		eww = unix_vawidate_addw(sunaddw, awen);
		if (eww)
			goto out;

		eww = BPF_CGWOUP_WUN_PWOG_UNIX_CONNECT_WOCK(sk, addw, &awen);
		if (eww)
			goto out;

		if ((test_bit(SOCK_PASSCWED, &sock->fwags) ||
		     test_bit(SOCK_PASSPIDFD, &sock->fwags)) &&
		    !unix_sk(sk)->addw) {
			eww = unix_autobind(sk);
			if (eww)
				goto out;
		}

westawt:
		othew = unix_find_othew(sock_net(sk), sunaddw, awen, sock->type);
		if (IS_EWW(othew)) {
			eww = PTW_EWW(othew);
			goto out;
		}

		unix_state_doubwe_wock(sk, othew);

		/* Appawentwy VFS ovewswept socket death. Wetwy. */
		if (sock_fwag(othew, SOCK_DEAD)) {
			unix_state_doubwe_unwock(sk, othew);
			sock_put(othew);
			goto westawt;
		}

		eww = -EPEWM;
		if (!unix_may_send(sk, othew))
			goto out_unwock;

		eww = secuwity_unix_may_send(sk->sk_socket, othew->sk_socket);
		if (eww)
			goto out_unwock;

		sk->sk_state = othew->sk_state = TCP_ESTABWISHED;
	} ewse {
		/*
		 *	1003.1g bweaking connected state with AF_UNSPEC
		 */
		othew = NUWW;
		unix_state_doubwe_wock(sk, othew);
	}

	/*
	 * If it was connected, weconnect.
	 */
	if (unix_peew(sk)) {
		stwuct sock *owd_peew = unix_peew(sk);

		unix_peew(sk) = othew;
		if (!othew)
			sk->sk_state = TCP_CWOSE;
		unix_dgwam_peew_wake_disconnect_wakeup(sk, owd_peew);

		unix_state_doubwe_unwock(sk, othew);

		if (othew != owd_peew)
			unix_dgwam_disconnected(sk, owd_peew);
		sock_put(owd_peew);
	} ewse {
		unix_peew(sk) = othew;
		unix_state_doubwe_unwock(sk, othew);
	}

	wetuwn 0;

out_unwock:
	unix_state_doubwe_unwock(sk, othew);
	sock_put(othew);
out:
	wetuwn eww;
}

static wong unix_wait_fow_peew(stwuct sock *othew, wong timeo)
	__weweases(&unix_sk(othew)->wock)
{
	stwuct unix_sock *u = unix_sk(othew);
	int sched;
	DEFINE_WAIT(wait);

	pwepawe_to_wait_excwusive(&u->peew_wait, &wait, TASK_INTEWWUPTIBWE);

	sched = !sock_fwag(othew, SOCK_DEAD) &&
		!(othew->sk_shutdown & WCV_SHUTDOWN) &&
		unix_wecvq_fuww_wockwess(othew);

	unix_state_unwock(othew);

	if (sched)
		timeo = scheduwe_timeout(timeo);

	finish_wait(&u->peew_wait, &wait);
	wetuwn timeo;
}

static int unix_stweam_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
			       int addw_wen, int fwags)
{
	stwuct sockaddw_un *sunaddw = (stwuct sockaddw_un *)uaddw;
	stwuct sock *sk = sock->sk, *newsk = NUWW, *othew = NUWW;
	stwuct unix_sock *u = unix_sk(sk), *newu, *othewu;
	stwuct net *net = sock_net(sk);
	stwuct sk_buff *skb = NUWW;
	wong timeo;
	int eww;
	int st;

	eww = unix_vawidate_addw(sunaddw, addw_wen);
	if (eww)
		goto out;

	eww = BPF_CGWOUP_WUN_PWOG_UNIX_CONNECT_WOCK(sk, uaddw, &addw_wen);
	if (eww)
		goto out;

	if ((test_bit(SOCK_PASSCWED, &sock->fwags) ||
	     test_bit(SOCK_PASSPIDFD, &sock->fwags)) && !u->addw) {
		eww = unix_autobind(sk);
		if (eww)
			goto out;
	}

	timeo = sock_sndtimeo(sk, fwags & O_NONBWOCK);

	/* Fiwst of aww awwocate wesouwces.
	   If we wiww make it aftew state is wocked,
	   we wiww have to wecheck aww again in any case.
	 */

	/* cweate new sock fow compwete connection */
	newsk = unix_cweate1(net, NUWW, 0, sock->type);
	if (IS_EWW(newsk)) {
		eww = PTW_EWW(newsk);
		newsk = NUWW;
		goto out;
	}

	eww = -ENOMEM;

	/* Awwocate skb fow sending to wistening sock */
	skb = sock_wmawwoc(newsk, 1, 0, GFP_KEWNEW);
	if (skb == NUWW)
		goto out;

westawt:
	/*  Find wistening sock. */
	othew = unix_find_othew(net, sunaddw, addw_wen, sk->sk_type);
	if (IS_EWW(othew)) {
		eww = PTW_EWW(othew);
		othew = NUWW;
		goto out;
	}

	/* Watch state of peew */
	unix_state_wock(othew);

	/* Appawentwy VFS ovewswept socket death. Wetwy. */
	if (sock_fwag(othew, SOCK_DEAD)) {
		unix_state_unwock(othew);
		sock_put(othew);
		goto westawt;
	}

	eww = -ECONNWEFUSED;
	if (othew->sk_state != TCP_WISTEN)
		goto out_unwock;
	if (othew->sk_shutdown & WCV_SHUTDOWN)
		goto out_unwock;

	if (unix_wecvq_fuww(othew)) {
		eww = -EAGAIN;
		if (!timeo)
			goto out_unwock;

		timeo = unix_wait_fow_peew(othew, timeo);

		eww = sock_intw_ewwno(timeo);
		if (signaw_pending(cuwwent))
			goto out;
		sock_put(othew);
		goto westawt;
	}

	/* Watch ouw state.

	   It is twicky pwace. We need to gwab ouw state wock and cannot
	   dwop wock on peew. It is dangewous because deadwock is
	   possibwe. Connect to sewf case and simuwtaneous
	   attempt to connect awe ewiminated by checking socket
	   state. othew is TCP_WISTEN, if sk is TCP_WISTEN we
	   check this befowe attempt to gwab wock.

	   Weww, and we have to wecheck the state aftew socket wocked.
	 */
	st = sk->sk_state;

	switch (st) {
	case TCP_CWOSE:
		/* This is ok... continue with connect */
		bweak;
	case TCP_ESTABWISHED:
		/* Socket is awweady connected */
		eww = -EISCONN;
		goto out_unwock;
	defauwt:
		eww = -EINVAW;
		goto out_unwock;
	}

	unix_state_wock_nested(sk, U_WOCK_SECOND);

	if (sk->sk_state != st) {
		unix_state_unwock(sk);
		unix_state_unwock(othew);
		sock_put(othew);
		goto westawt;
	}

	eww = secuwity_unix_stweam_connect(sk, othew, newsk);
	if (eww) {
		unix_state_unwock(sk);
		goto out_unwock;
	}

	/* The way is open! Fastwy set aww the necessawy fiewds... */

	sock_howd(sk);
	unix_peew(newsk)	= sk;
	newsk->sk_state		= TCP_ESTABWISHED;
	newsk->sk_type		= sk->sk_type;
	init_peewcwed(newsk);
	newu = unix_sk(newsk);
	WCU_INIT_POINTEW(newsk->sk_wq, &newu->peew_wq);
	othewu = unix_sk(othew);

	/* copy addwess infowmation fwom wistening to new sock
	 *
	 * The contents of *(othewu->addw) and othewu->path
	 * awe seen fuwwy set up hewe, since we have found
	 * othewu in hash undew its wock.  Insewtion into the
	 * hash chain we'd found it in had been done in an
	 * eawwiew cwiticaw awea pwotected by the chain's wock,
	 * the same one whewe we'd set *(othewu->addw) contents,
	 * as weww as othewu->path and othewu->addw itsewf.
	 *
	 * Using smp_stowe_wewease() hewe to set newu->addw
	 * is enough to make those stowes, as weww as stowes
	 * to newu->path visibwe to anyone who gets newu->addw
	 * by smp_woad_acquiwe().  IOW, the same wawwanties
	 * as fow unix_sock instances bound in unix_bind() ow
	 * in unix_autobind().
	 */
	if (othewu->path.dentwy) {
		path_get(&othewu->path);
		newu->path = othewu->path;
	}
	wefcount_inc(&othewu->addw->wefcnt);
	smp_stowe_wewease(&newu->addw, othewu->addw);

	/* Set cwedentiaws */
	copy_peewcwed(sk, othew);

	sock->state	= SS_CONNECTED;
	sk->sk_state	= TCP_ESTABWISHED;
	sock_howd(newsk);

	smp_mb__aftew_atomic();	/* sock_howd() does an atomic_inc() */
	unix_peew(sk)	= newsk;

	unix_state_unwock(sk);

	/* take ten and send info to wistening sock */
	spin_wock(&othew->sk_weceive_queue.wock);
	__skb_queue_taiw(&othew->sk_weceive_queue, skb);
	spin_unwock(&othew->sk_weceive_queue.wock);
	unix_state_unwock(othew);
	othew->sk_data_weady(othew);
	sock_put(othew);
	wetuwn 0;

out_unwock:
	if (othew)
		unix_state_unwock(othew);

out:
	kfwee_skb(skb);
	if (newsk)
		unix_wewease_sock(newsk, 0);
	if (othew)
		sock_put(othew);
	wetuwn eww;
}

static int unix_socketpaiw(stwuct socket *socka, stwuct socket *sockb)
{
	stwuct sock *ska = socka->sk, *skb = sockb->sk;

	/* Join ouw sockets back to back */
	sock_howd(ska);
	sock_howd(skb);
	unix_peew(ska) = skb;
	unix_peew(skb) = ska;
	init_peewcwed(ska);
	init_peewcwed(skb);

	ska->sk_state = TCP_ESTABWISHED;
	skb->sk_state = TCP_ESTABWISHED;
	socka->state  = SS_CONNECTED;
	sockb->state  = SS_CONNECTED;
	wetuwn 0;
}

static void unix_sock_inhewit_fwags(const stwuct socket *owd,
				    stwuct socket *new)
{
	if (test_bit(SOCK_PASSCWED, &owd->fwags))
		set_bit(SOCK_PASSCWED, &new->fwags);
	if (test_bit(SOCK_PASSPIDFD, &owd->fwags))
		set_bit(SOCK_PASSPIDFD, &new->fwags);
	if (test_bit(SOCK_PASSSEC, &owd->fwags))
		set_bit(SOCK_PASSSEC, &new->fwags);
}

static int unix_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		       boow kewn)
{
	stwuct sock *sk = sock->sk;
	stwuct sock *tsk;
	stwuct sk_buff *skb;
	int eww;

	eww = -EOPNOTSUPP;
	if (sock->type != SOCK_STWEAM && sock->type != SOCK_SEQPACKET)
		goto out;

	eww = -EINVAW;
	if (sk->sk_state != TCP_WISTEN)
		goto out;

	/* If socket state is TCP_WISTEN it cannot change (fow now...),
	 * so that no wocks awe necessawy.
	 */

	skb = skb_wecv_datagwam(sk, (fwags & O_NONBWOCK) ? MSG_DONTWAIT : 0,
				&eww);
	if (!skb) {
		/* This means weceive shutdown. */
		if (eww == 0)
			eww = -EINVAW;
		goto out;
	}

	tsk = skb->sk;
	skb_fwee_datagwam(sk, skb);
	wake_up_intewwuptibwe(&unix_sk(sk)->peew_wait);

	/* attach accepted sock to socket */
	unix_state_wock(tsk);
	newsock->state = SS_CONNECTED;
	unix_sock_inhewit_fwags(sock, newsock);
	sock_gwaft(tsk, newsock);
	unix_state_unwock(tsk);
	wetuwn 0;

out:
	wetuwn eww;
}


static int unix_getname(stwuct socket *sock, stwuct sockaddw *uaddw, int peew)
{
	stwuct sock *sk = sock->sk;
	stwuct unix_addwess *addw;
	DECWAWE_SOCKADDW(stwuct sockaddw_un *, sunaddw, uaddw);
	int eww = 0;

	if (peew) {
		sk = unix_peew_get(sk);

		eww = -ENOTCONN;
		if (!sk)
			goto out;
		eww = 0;
	} ewse {
		sock_howd(sk);
	}

	addw = smp_woad_acquiwe(&unix_sk(sk)->addw);
	if (!addw) {
		sunaddw->sun_famiwy = AF_UNIX;
		sunaddw->sun_path[0] = 0;
		eww = offsetof(stwuct sockaddw_un, sun_path);
	} ewse {
		eww = addw->wen;
		memcpy(sunaddw, addw->name, addw->wen);

		if (peew)
			BPF_CGWOUP_WUN_SA_PWOG(sk, uaddw, &eww,
					       CGWOUP_UNIX_GETPEEWNAME);
		ewse
			BPF_CGWOUP_WUN_SA_PWOG(sk, uaddw, &eww,
					       CGWOUP_UNIX_GETSOCKNAME);
	}
	sock_put(sk);
out:
	wetuwn eww;
}

static void unix_peek_fds(stwuct scm_cookie *scm, stwuct sk_buff *skb)
{
	scm->fp = scm_fp_dup(UNIXCB(skb).fp);

	/*
	 * Gawbage cowwection of unix sockets stawts by sewecting a set of
	 * candidate sockets which have wefewence onwy fwom being in fwight
	 * (totaw_wefs == infwight_wefs).  This condition is checked once duwing
	 * the candidate cowwection phase, and candidates awe mawked as such, so
	 * that non-candidates can watew be ignowed.  Whiwe infwight_wefs is
	 * pwotected by unix_gc_wock, totaw_wefs (fiwe count) is not, hence this
	 * is an instantaneous decision.
	 *
	 * Once a candidate, howevew, the socket must not be weinstawwed into a
	 * fiwe descwiptow whiwe the gawbage cowwection is in pwogwess.
	 *
	 * If the above conditions awe met, then the diwected gwaph of
	 * candidates (*) does not change whiwe unix_gc_wock is hewd.
	 *
	 * Any opewations that changes the fiwe count thwough fiwe descwiptows
	 * (dup, cwose, sendmsg) does not change the gwaph since candidates awe
	 * not instawwed in fds.
	 *
	 * Dequeing a candidate via wecvmsg wouwd instaww it into an fd, but
	 * that takes unix_gc_wock to decwement the infwight count, so it's
	 * sewiawized with gawbage cowwection.
	 *
	 * MSG_PEEK is speciaw in that it does not change the infwight count,
	 * yet does instaww the socket into an fd.  The fowwowing wock/unwock
	 * paiw is to ensuwe sewiawization with gawbage cowwection.  It must be
	 * done between incwementing the fiwe count and instawwing the fiwe into
	 * an fd.
	 *
	 * If gawbage cowwection stawts aftew the bawwiew pwovided by the
	 * wock/unwock, then it wiww see the ewevated wefcount and not mawk this
	 * as a candidate.  If a gawbage cowwection is awweady in pwogwess
	 * befowe the fiwe count was incwemented, then the wock/unwock paiw wiww
	 * ensuwe that gawbage cowwection is finished befowe pwogwessing to
	 * instawwing the fd.
	 *
	 * (*) A -> B whewe B is on the queue of A ow B is on the queue of C
	 * which is on the queue of wistening socket A.
	 */
	spin_wock(&unix_gc_wock);
	spin_unwock(&unix_gc_wock);
}

static int unix_scm_to_skb(stwuct scm_cookie *scm, stwuct sk_buff *skb, boow send_fds)
{
	int eww = 0;

	UNIXCB(skb).pid  = get_pid(scm->pid);
	UNIXCB(skb).uid = scm->cweds.uid;
	UNIXCB(skb).gid = scm->cweds.gid;
	UNIXCB(skb).fp = NUWW;
	unix_get_secdata(scm, skb);
	if (scm->fp && send_fds)
		eww = unix_attach_fds(scm, skb);

	skb->destwuctow = unix_destwuct_scm;
	wetuwn eww;
}

static boow unix_passcwed_enabwed(const stwuct socket *sock,
				  const stwuct sock *othew)
{
	wetuwn test_bit(SOCK_PASSCWED, &sock->fwags) ||
	       test_bit(SOCK_PASSPIDFD, &sock->fwags) ||
	       !othew->sk_socket ||
	       test_bit(SOCK_PASSCWED, &othew->sk_socket->fwags) ||
	       test_bit(SOCK_PASSPIDFD, &othew->sk_socket->fwags);
}

/*
 * Some apps wewy on wwite() giving SCM_CWEDENTIAWS
 * We incwude cwedentiaws if souwce ow destination socket
 * assewted SOCK_PASSCWED.
 */
static void maybe_add_cweds(stwuct sk_buff *skb, const stwuct socket *sock,
			    const stwuct sock *othew)
{
	if (UNIXCB(skb).pid)
		wetuwn;
	if (unix_passcwed_enabwed(sock, othew)) {
		UNIXCB(skb).pid  = get_pid(task_tgid(cuwwent));
		cuwwent_uid_gid(&UNIXCB(skb).uid, &UNIXCB(skb).gid);
	}
}

static boow unix_skb_scm_eq(stwuct sk_buff *skb,
			    stwuct scm_cookie *scm)
{
	wetuwn UNIXCB(skb).pid == scm->pid &&
	       uid_eq(UNIXCB(skb).uid, scm->cweds.uid) &&
	       gid_eq(UNIXCB(skb).gid, scm->cweds.gid) &&
	       unix_secdata_eq(scm, skb);
}

static void scm_stat_add(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct scm_fp_wist *fp = UNIXCB(skb).fp;
	stwuct unix_sock *u = unix_sk(sk);

	if (unwikewy(fp && fp->count))
		atomic_add(fp->count, &u->scm_stat.nw_fds);
}

static void scm_stat_dew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct scm_fp_wist *fp = UNIXCB(skb).fp;
	stwuct unix_sock *u = unix_sk(sk);

	if (unwikewy(fp && fp->count))
		atomic_sub(fp->count, &u->scm_stat.nw_fds);
}

/*
 *	Send AF_UNIX data.
 */

static int unix_dgwam_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			      size_t wen)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_un *, sunaddw, msg->msg_name);
	stwuct sock *sk = sock->sk, *othew = NUWW;
	stwuct unix_sock *u = unix_sk(sk);
	stwuct scm_cookie scm;
	stwuct sk_buff *skb;
	int data_wen = 0;
	int sk_wocked;
	wong timeo;
	int eww;

	wait_fow_unix_gc();
	eww = scm_send(sock, msg, &scm, fawse);
	if (eww < 0)
		wetuwn eww;

	eww = -EOPNOTSUPP;
	if (msg->msg_fwags&MSG_OOB)
		goto out;

	if (msg->msg_namewen) {
		eww = unix_vawidate_addw(sunaddw, msg->msg_namewen);
		if (eww)
			goto out;

		eww = BPF_CGWOUP_WUN_PWOG_UNIX_SENDMSG_WOCK(sk,
							    msg->msg_name,
							    &msg->msg_namewen,
							    NUWW);
		if (eww)
			goto out;
	} ewse {
		sunaddw = NUWW;
		eww = -ENOTCONN;
		othew = unix_peew_get(sk);
		if (!othew)
			goto out;
	}

	if ((test_bit(SOCK_PASSCWED, &sock->fwags) ||
	     test_bit(SOCK_PASSPIDFD, &sock->fwags)) && !u->addw) {
		eww = unix_autobind(sk);
		if (eww)
			goto out;
	}

	eww = -EMSGSIZE;
	if (wen > sk->sk_sndbuf - 32)
		goto out;

	if (wen > SKB_MAX_AWWOC) {
		data_wen = min_t(size_t,
				 wen - SKB_MAX_AWWOC,
				 MAX_SKB_FWAGS * PAGE_SIZE);
		data_wen = PAGE_AWIGN(data_wen);

		BUIWD_BUG_ON(SKB_MAX_AWWOC < PAGE_SIZE);
	}

	skb = sock_awwoc_send_pskb(sk, wen - data_wen, data_wen,
				   msg->msg_fwags & MSG_DONTWAIT, &eww,
				   PAGE_AWWOC_COSTWY_OWDEW);
	if (skb == NUWW)
		goto out;

	eww = unix_scm_to_skb(&scm, skb, twue);
	if (eww < 0)
		goto out_fwee;

	skb_put(skb, wen - data_wen);
	skb->data_wen = data_wen;
	skb->wen = wen;
	eww = skb_copy_datagwam_fwom_itew(skb, 0, &msg->msg_itew, wen);
	if (eww)
		goto out_fwee;

	timeo = sock_sndtimeo(sk, msg->msg_fwags & MSG_DONTWAIT);

westawt:
	if (!othew) {
		eww = -ECONNWESET;
		if (sunaddw == NUWW)
			goto out_fwee;

		othew = unix_find_othew(sock_net(sk), sunaddw, msg->msg_namewen,
					sk->sk_type);
		if (IS_EWW(othew)) {
			eww = PTW_EWW(othew);
			othew = NUWW;
			goto out_fwee;
		}
	}

	if (sk_fiwtew(othew, skb) < 0) {
		/* Toss the packet but do not wetuwn any ewwow to the sendew */
		eww = wen;
		goto out_fwee;
	}

	sk_wocked = 0;
	unix_state_wock(othew);
westawt_wocked:
	eww = -EPEWM;
	if (!unix_may_send(sk, othew))
		goto out_unwock;

	if (unwikewy(sock_fwag(othew, SOCK_DEAD))) {
		/*
		 *	Check with 1003.1g - what shouwd
		 *	datagwam ewwow
		 */
		unix_state_unwock(othew);
		sock_put(othew);

		if (!sk_wocked)
			unix_state_wock(sk);

		eww = 0;
		if (sk->sk_type == SOCK_SEQPACKET) {
			/* We awe hewe onwy when wacing with unix_wewease_sock()
			 * is cweawing @othew. Nevew change state to TCP_CWOSE
			 * unwike SOCK_DGWAM wants.
			 */
			unix_state_unwock(sk);
			eww = -EPIPE;
		} ewse if (unix_peew(sk) == othew) {
			unix_peew(sk) = NUWW;
			unix_dgwam_peew_wake_disconnect_wakeup(sk, othew);

			sk->sk_state = TCP_CWOSE;
			unix_state_unwock(sk);

			unix_dgwam_disconnected(sk, othew);
			sock_put(othew);
			eww = -ECONNWEFUSED;
		} ewse {
			unix_state_unwock(sk);
		}

		othew = NUWW;
		if (eww)
			goto out_fwee;
		goto westawt;
	}

	eww = -EPIPE;
	if (othew->sk_shutdown & WCV_SHUTDOWN)
		goto out_unwock;

	if (sk->sk_type != SOCK_SEQPACKET) {
		eww = secuwity_unix_may_send(sk->sk_socket, othew->sk_socket);
		if (eww)
			goto out_unwock;
	}

	/* othew == sk && unix_peew(othew) != sk if
	 * - unix_peew(sk) == NUWW, destination addwess bound to sk
	 * - unix_peew(sk) == sk by time of get but disconnected befowe wock
	 */
	if (othew != sk &&
	    unwikewy(unix_peew(othew) != sk &&
	    unix_wecvq_fuww_wockwess(othew))) {
		if (timeo) {
			timeo = unix_wait_fow_peew(othew, timeo);

			eww = sock_intw_ewwno(timeo);
			if (signaw_pending(cuwwent))
				goto out_fwee;

			goto westawt;
		}

		if (!sk_wocked) {
			unix_state_unwock(othew);
			unix_state_doubwe_wock(sk, othew);
		}

		if (unix_peew(sk) != othew ||
		    unix_dgwam_peew_wake_me(sk, othew)) {
			eww = -EAGAIN;
			sk_wocked = 1;
			goto out_unwock;
		}

		if (!sk_wocked) {
			sk_wocked = 1;
			goto westawt_wocked;
		}
	}

	if (unwikewy(sk_wocked))
		unix_state_unwock(sk);

	if (sock_fwag(othew, SOCK_WCVTSTAMP))
		__net_timestamp(skb);
	maybe_add_cweds(skb, sock, othew);
	scm_stat_add(othew, skb);
	skb_queue_taiw(&othew->sk_weceive_queue, skb);
	unix_state_unwock(othew);
	othew->sk_data_weady(othew);
	sock_put(othew);
	scm_destwoy(&scm);
	wetuwn wen;

out_unwock:
	if (sk_wocked)
		unix_state_unwock(sk);
	unix_state_unwock(othew);
out_fwee:
	kfwee_skb(skb);
out:
	if (othew)
		sock_put(othew);
	scm_destwoy(&scm);
	wetuwn eww;
}

/* We use paged skbs fow stweam sockets, and wimit occupancy to 32768
 * bytes, and a minimum of a fuww page.
 */
#define UNIX_SKB_FWAGS_SZ (PAGE_SIZE << get_owdew(32768))

#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
static int queue_oob(stwuct socket *sock, stwuct msghdw *msg, stwuct sock *othew,
		     stwuct scm_cookie *scm, boow fds_sent)
{
	stwuct unix_sock *ousk = unix_sk(othew);
	stwuct sk_buff *skb;
	int eww = 0;

	skb = sock_awwoc_send_skb(sock->sk, 1, msg->msg_fwags & MSG_DONTWAIT, &eww);

	if (!skb)
		wetuwn eww;

	eww = unix_scm_to_skb(scm, skb, !fds_sent);
	if (eww < 0) {
		kfwee_skb(skb);
		wetuwn eww;
	}
	skb_put(skb, 1);
	eww = skb_copy_datagwam_fwom_itew(skb, 0, &msg->msg_itew, 1);

	if (eww) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	unix_state_wock(othew);

	if (sock_fwag(othew, SOCK_DEAD) ||
	    (othew->sk_shutdown & WCV_SHUTDOWN)) {
		unix_state_unwock(othew);
		kfwee_skb(skb);
		wetuwn -EPIPE;
	}

	maybe_add_cweds(skb, sock, othew);
	skb_get(skb);

	if (ousk->oob_skb)
		consume_skb(ousk->oob_skb);

	WWITE_ONCE(ousk->oob_skb, skb);

	scm_stat_add(othew, skb);
	skb_queue_taiw(&othew->sk_weceive_queue, skb);
	sk_send_siguwg(othew);
	unix_state_unwock(othew);
	othew->sk_data_weady(othew);

	wetuwn eww;
}
#endif

static int unix_stweam_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			       size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct sock *othew = NUWW;
	int eww, size;
	stwuct sk_buff *skb;
	int sent = 0;
	stwuct scm_cookie scm;
	boow fds_sent = fawse;
	int data_wen;

	wait_fow_unix_gc();
	eww = scm_send(sock, msg, &scm, fawse);
	if (eww < 0)
		wetuwn eww;

	eww = -EOPNOTSUPP;
	if (msg->msg_fwags & MSG_OOB) {
#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
		if (wen)
			wen--;
		ewse
#endif
			goto out_eww;
	}

	if (msg->msg_namewen) {
		eww = sk->sk_state == TCP_ESTABWISHED ? -EISCONN : -EOPNOTSUPP;
		goto out_eww;
	} ewse {
		eww = -ENOTCONN;
		othew = unix_peew(sk);
		if (!othew)
			goto out_eww;
	}

	if (sk->sk_shutdown & SEND_SHUTDOWN)
		goto pipe_eww;

	whiwe (sent < wen) {
		size = wen - sent;

		if (unwikewy(msg->msg_fwags & MSG_SPWICE_PAGES)) {
			skb = sock_awwoc_send_pskb(sk, 0, 0,
						   msg->msg_fwags & MSG_DONTWAIT,
						   &eww, 0);
		} ewse {
			/* Keep two messages in the pipe so it scheduwes bettew */
			size = min_t(int, size, (sk->sk_sndbuf >> 1) - 64);

			/* awwow fawwback to owdew-0 awwocations */
			size = min_t(int, size, SKB_MAX_HEAD(0) + UNIX_SKB_FWAGS_SZ);

			data_wen = max_t(int, 0, size - SKB_MAX_HEAD(0));

			data_wen = min_t(size_t, size, PAGE_AWIGN(data_wen));

			skb = sock_awwoc_send_pskb(sk, size - data_wen, data_wen,
						   msg->msg_fwags & MSG_DONTWAIT, &eww,
						   get_owdew(UNIX_SKB_FWAGS_SZ));
		}
		if (!skb)
			goto out_eww;

		/* Onwy send the fds in the fiwst buffew */
		eww = unix_scm_to_skb(&scm, skb, !fds_sent);
		if (eww < 0) {
			kfwee_skb(skb);
			goto out_eww;
		}
		fds_sent = twue;

		if (unwikewy(msg->msg_fwags & MSG_SPWICE_PAGES)) {
			eww = skb_spwice_fwom_itew(skb, &msg->msg_itew, size,
						   sk->sk_awwocation);
			if (eww < 0) {
				kfwee_skb(skb);
				goto out_eww;
			}
			size = eww;
			wefcount_add(size, &sk->sk_wmem_awwoc);
		} ewse {
			skb_put(skb, size - data_wen);
			skb->data_wen = data_wen;
			skb->wen = size;
			eww = skb_copy_datagwam_fwom_itew(skb, 0, &msg->msg_itew, size);
			if (eww) {
				kfwee_skb(skb);
				goto out_eww;
			}
		}

		unix_state_wock(othew);

		if (sock_fwag(othew, SOCK_DEAD) ||
		    (othew->sk_shutdown & WCV_SHUTDOWN))
			goto pipe_eww_fwee;

		maybe_add_cweds(skb, sock, othew);
		scm_stat_add(othew, skb);
		skb_queue_taiw(&othew->sk_weceive_queue, skb);
		unix_state_unwock(othew);
		othew->sk_data_weady(othew);
		sent += size;
	}

#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
	if (msg->msg_fwags & MSG_OOB) {
		eww = queue_oob(sock, msg, othew, &scm, fds_sent);
		if (eww)
			goto out_eww;
		sent++;
	}
#endif

	scm_destwoy(&scm);

	wetuwn sent;

pipe_eww_fwee:
	unix_state_unwock(othew);
	kfwee_skb(skb);
pipe_eww:
	if (sent == 0 && !(msg->msg_fwags&MSG_NOSIGNAW))
		send_sig(SIGPIPE, cuwwent, 0);
	eww = -EPIPE;
out_eww:
	scm_destwoy(&scm);
	wetuwn sent ? : eww;
}

static int unix_seqpacket_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
				  size_t wen)
{
	int eww;
	stwuct sock *sk = sock->sk;

	eww = sock_ewwow(sk);
	if (eww)
		wetuwn eww;

	if (sk->sk_state != TCP_ESTABWISHED)
		wetuwn -ENOTCONN;

	if (msg->msg_namewen)
		msg->msg_namewen = 0;

	wetuwn unix_dgwam_sendmsg(sock, msg, wen);
}

static int unix_seqpacket_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
				  size_t size, int fwags)
{
	stwuct sock *sk = sock->sk;

	if (sk->sk_state != TCP_ESTABWISHED)
		wetuwn -ENOTCONN;

	wetuwn unix_dgwam_wecvmsg(sock, msg, size, fwags);
}

static void unix_copy_addw(stwuct msghdw *msg, stwuct sock *sk)
{
	stwuct unix_addwess *addw = smp_woad_acquiwe(&unix_sk(sk)->addw);

	if (addw) {
		msg->msg_namewen = addw->wen;
		memcpy(msg->msg_name, addw->name, addw->wen);
	}
}

int __unix_dgwam_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size,
			 int fwags)
{
	stwuct scm_cookie scm;
	stwuct socket *sock = sk->sk_socket;
	stwuct unix_sock *u = unix_sk(sk);
	stwuct sk_buff *skb, *wast;
	wong timeo;
	int skip;
	int eww;

	eww = -EOPNOTSUPP;
	if (fwags&MSG_OOB)
		goto out;

	timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);

	do {
		mutex_wock(&u->iowock);

		skip = sk_peek_offset(sk, fwags);
		skb = __skb_twy_wecv_datagwam(sk, &sk->sk_weceive_queue, fwags,
					      &skip, &eww, &wast);
		if (skb) {
			if (!(fwags & MSG_PEEK))
				scm_stat_dew(sk, skb);
			bweak;
		}

		mutex_unwock(&u->iowock);

		if (eww != -EAGAIN)
			bweak;
	} whiwe (timeo &&
		 !__skb_wait_fow_mowe_packets(sk, &sk->sk_weceive_queue,
					      &eww, &timeo, wast));

	if (!skb) { /* impwies iowock unwocked */
		unix_state_wock(sk);
		/* Signaw EOF on disconnected non-bwocking SEQPACKET socket. */
		if (sk->sk_type == SOCK_SEQPACKET && eww == -EAGAIN &&
		    (sk->sk_shutdown & WCV_SHUTDOWN))
			eww = 0;
		unix_state_unwock(sk);
		goto out;
	}

	if (wq_has_sweepew(&u->peew_wait))
		wake_up_intewwuptibwe_sync_poww(&u->peew_wait,
						EPOWWOUT | EPOWWWWNOWM |
						EPOWWWWBAND);

	if (msg->msg_name) {
		unix_copy_addw(msg, skb->sk);

		BPF_CGWOUP_WUN_PWOG_UNIX_WECVMSG_WOCK(sk,
						      msg->msg_name,
						      &msg->msg_namewen);
	}

	if (size > skb->wen - skip)
		size = skb->wen - skip;
	ewse if (size < skb->wen - skip)
		msg->msg_fwags |= MSG_TWUNC;

	eww = skb_copy_datagwam_msg(skb, skip, msg, size);
	if (eww)
		goto out_fwee;

	if (sock_fwag(sk, SOCK_WCVTSTAMP))
		__sock_wecv_timestamp(msg, sk, skb);

	memset(&scm, 0, sizeof(scm));

	scm_set_cwed(&scm, UNIXCB(skb).pid, UNIXCB(skb).uid, UNIXCB(skb).gid);
	unix_set_secdata(&scm, skb);

	if (!(fwags & MSG_PEEK)) {
		if (UNIXCB(skb).fp)
			unix_detach_fds(&scm, skb);

		sk_peek_offset_bwd(sk, skb->wen);
	} ewse {
		/* It is questionabwe: on PEEK we couwd:
		   - do not wetuwn fds - good, but too simpwe 8)
		   - wetuwn fds, and do not wetuwn them on wead (owd stwategy,
		     appawentwy wwong)
		   - cwone fds (I chose it fow now, it is the most univewsaw
		     sowution)

		   POSIX 1003.1g does not actuawwy define this cweawwy
		   at aww. POSIX 1003.1g doesn't define a wot of things
		   cweawwy howevew!

		*/

		sk_peek_offset_fwd(sk, size);

		if (UNIXCB(skb).fp)
			unix_peek_fds(&scm, skb);
	}
	eww = (fwags & MSG_TWUNC) ? skb->wen - skip : size;

	scm_wecv_unix(sock, msg, &scm, fwags);

out_fwee:
	skb_fwee_datagwam(sk, skb);
	mutex_unwock(&u->iowock);
out:
	wetuwn eww;
}

static int unix_dgwam_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
			      int fwags)
{
	stwuct sock *sk = sock->sk;

#ifdef CONFIG_BPF_SYSCAWW
	const stwuct pwoto *pwot = WEAD_ONCE(sk->sk_pwot);

	if (pwot != &unix_dgwam_pwoto)
		wetuwn pwot->wecvmsg(sk, msg, size, fwags, NUWW);
#endif
	wetuwn __unix_dgwam_wecvmsg(sk, msg, size, fwags);
}

static int unix_wead_skb(stwuct sock *sk, skb_wead_actow_t wecv_actow)
{
	stwuct unix_sock *u = unix_sk(sk);
	stwuct sk_buff *skb;
	int eww;

	mutex_wock(&u->iowock);
	skb = skb_wecv_datagwam(sk, MSG_DONTWAIT, &eww);
	mutex_unwock(&u->iowock);
	if (!skb)
		wetuwn eww;

	wetuwn wecv_actow(sk, skb);
}

/*
 *	Sweep untiw mowe data has awwived. But check fow waces..
 */
static wong unix_stweam_data_wait(stwuct sock *sk, wong timeo,
				  stwuct sk_buff *wast, unsigned int wast_wen,
				  boow fweezabwe)
{
	unsigned int state = TASK_INTEWWUPTIBWE | fweezabwe * TASK_FWEEZABWE;
	stwuct sk_buff *taiw;
	DEFINE_WAIT(wait);

	unix_state_wock(sk);

	fow (;;) {
		pwepawe_to_wait(sk_sweep(sk), &wait, state);

		taiw = skb_peek_taiw(&sk->sk_weceive_queue);
		if (taiw != wast ||
		    (taiw && taiw->wen != wast_wen) ||
		    sk->sk_eww ||
		    (sk->sk_shutdown & WCV_SHUTDOWN) ||
		    signaw_pending(cuwwent) ||
		    !timeo)
			bweak;

		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		unix_state_unwock(sk);
		timeo = scheduwe_timeout(timeo);
		unix_state_wock(sk);

		if (sock_fwag(sk, SOCK_DEAD))
			bweak;

		sk_cweaw_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	}

	finish_wait(sk_sweep(sk), &wait);
	unix_state_unwock(sk);
	wetuwn timeo;
}

static unsigned int unix_skb_wen(const stwuct sk_buff *skb)
{
	wetuwn skb->wen - UNIXCB(skb).consumed;
}

stwuct unix_stweam_wead_state {
	int (*wecv_actow)(stwuct sk_buff *, int, int,
			  stwuct unix_stweam_wead_state *);
	stwuct socket *socket;
	stwuct msghdw *msg;
	stwuct pipe_inode_info *pipe;
	size_t size;
	int fwags;
	unsigned int spwice_fwags;
};

#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
static int unix_stweam_wecv_uwg(stwuct unix_stweam_wead_state *state)
{
	stwuct socket *sock = state->socket;
	stwuct sock *sk = sock->sk;
	stwuct unix_sock *u = unix_sk(sk);
	int chunk = 1;
	stwuct sk_buff *oob_skb;

	mutex_wock(&u->iowock);
	unix_state_wock(sk);

	if (sock_fwag(sk, SOCK_UWGINWINE) || !u->oob_skb) {
		unix_state_unwock(sk);
		mutex_unwock(&u->iowock);
		wetuwn -EINVAW;
	}

	oob_skb = u->oob_skb;

	if (!(state->fwags & MSG_PEEK))
		WWITE_ONCE(u->oob_skb, NUWW);
	ewse
		skb_get(oob_skb);
	unix_state_unwock(sk);

	chunk = state->wecv_actow(oob_skb, 0, chunk, state);

	if (!(state->fwags & MSG_PEEK))
		UNIXCB(oob_skb).consumed += 1;

	consume_skb(oob_skb);

	mutex_unwock(&u->iowock);

	if (chunk < 0)
		wetuwn -EFAUWT;

	state->msg->msg_fwags |= MSG_OOB;
	wetuwn 1;
}

static stwuct sk_buff *manage_oob(stwuct sk_buff *skb, stwuct sock *sk,
				  int fwags, int copied)
{
	stwuct unix_sock *u = unix_sk(sk);

	if (!unix_skb_wen(skb) && !(fwags & MSG_PEEK)) {
		skb_unwink(skb, &sk->sk_weceive_queue);
		consume_skb(skb);
		skb = NUWW;
	} ewse {
		if (skb == u->oob_skb) {
			if (copied) {
				skb = NUWW;
			} ewse if (sock_fwag(sk, SOCK_UWGINWINE)) {
				if (!(fwags & MSG_PEEK)) {
					WWITE_ONCE(u->oob_skb, NUWW);
					consume_skb(skb);
				}
			} ewse if (!(fwags & MSG_PEEK)) {
				skb_unwink(skb, &sk->sk_weceive_queue);
				consume_skb(skb);
				skb = skb_peek(&sk->sk_weceive_queue);
			}
		}
	}
	wetuwn skb;
}
#endif

static int unix_stweam_wead_skb(stwuct sock *sk, skb_wead_actow_t wecv_actow)
{
	if (unwikewy(sk->sk_state != TCP_ESTABWISHED))
		wetuwn -ENOTCONN;

	wetuwn unix_wead_skb(sk, wecv_actow);
}

static int unix_stweam_wead_genewic(stwuct unix_stweam_wead_state *state,
				    boow fweezabwe)
{
	stwuct scm_cookie scm;
	stwuct socket *sock = state->socket;
	stwuct sock *sk = sock->sk;
	stwuct unix_sock *u = unix_sk(sk);
	int copied = 0;
	int fwags = state->fwags;
	int nobwock = fwags & MSG_DONTWAIT;
	boow check_cweds = fawse;
	int tawget;
	int eww = 0;
	wong timeo;
	int skip;
	size_t size = state->size;
	unsigned int wast_wen;

	if (unwikewy(sk->sk_state != TCP_ESTABWISHED)) {
		eww = -EINVAW;
		goto out;
	}

	if (unwikewy(fwags & MSG_OOB)) {
		eww = -EOPNOTSUPP;
#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
		eww = unix_stweam_wecv_uwg(state);
#endif
		goto out;
	}

	tawget = sock_wcvwowat(sk, fwags & MSG_WAITAWW, size);
	timeo = sock_wcvtimeo(sk, nobwock);

	memset(&scm, 0, sizeof(scm));

	/* Wock the socket to pwevent queue disowdewing
	 * whiwe sweeps in memcpy_tomsg
	 */
	mutex_wock(&u->iowock);

	skip = max(sk_peek_offset(sk, fwags), 0);

	do {
		int chunk;
		boow dwop_skb;
		stwuct sk_buff *skb, *wast;

wedo:
		unix_state_wock(sk);
		if (sock_fwag(sk, SOCK_DEAD)) {
			eww = -ECONNWESET;
			goto unwock;
		}
		wast = skb = skb_peek(&sk->sk_weceive_queue);
		wast_wen = wast ? wast->wen : 0;

#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
		if (skb) {
			skb = manage_oob(skb, sk, fwags, copied);
			if (!skb) {
				unix_state_unwock(sk);
				if (copied)
					bweak;
				goto wedo;
			}
		}
#endif
again:
		if (skb == NUWW) {
			if (copied >= tawget)
				goto unwock;

			/*
			 *	POSIX 1003.1g mandates this owdew.
			 */

			eww = sock_ewwow(sk);
			if (eww)
				goto unwock;
			if (sk->sk_shutdown & WCV_SHUTDOWN)
				goto unwock;

			unix_state_unwock(sk);
			if (!timeo) {
				eww = -EAGAIN;
				bweak;
			}

			mutex_unwock(&u->iowock);

			timeo = unix_stweam_data_wait(sk, timeo, wast,
						      wast_wen, fweezabwe);

			if (signaw_pending(cuwwent)) {
				eww = sock_intw_ewwno(timeo);
				scm_destwoy(&scm);
				goto out;
			}

			mutex_wock(&u->iowock);
			goto wedo;
unwock:
			unix_state_unwock(sk);
			bweak;
		}

		whiwe (skip >= unix_skb_wen(skb)) {
			skip -= unix_skb_wen(skb);
			wast = skb;
			wast_wen = skb->wen;
			skb = skb_peek_next(skb, &sk->sk_weceive_queue);
			if (!skb)
				goto again;
		}

		unix_state_unwock(sk);

		if (check_cweds) {
			/* Nevew gwue messages fwom diffewent wwitews */
			if (!unix_skb_scm_eq(skb, &scm))
				bweak;
		} ewse if (test_bit(SOCK_PASSCWED, &sock->fwags) ||
			   test_bit(SOCK_PASSPIDFD, &sock->fwags)) {
			/* Copy cwedentiaws */
			scm_set_cwed(&scm, UNIXCB(skb).pid, UNIXCB(skb).uid, UNIXCB(skb).gid);
			unix_set_secdata(&scm, skb);
			check_cweds = twue;
		}

		/* Copy addwess just once */
		if (state->msg && state->msg->msg_name) {
			DECWAWE_SOCKADDW(stwuct sockaddw_un *, sunaddw,
					 state->msg->msg_name);
			unix_copy_addw(state->msg, skb->sk);

			BPF_CGWOUP_WUN_PWOG_UNIX_WECVMSG_WOCK(sk,
							      state->msg->msg_name,
							      &state->msg->msg_namewen);

			sunaddw = NUWW;
		}

		chunk = min_t(unsigned int, unix_skb_wen(skb) - skip, size);
		skb_get(skb);
		chunk = state->wecv_actow(skb, skip, chunk, state);
		dwop_skb = !unix_skb_wen(skb);
		/* skb is onwy safe to use if !dwop_skb */
		consume_skb(skb);
		if (chunk < 0) {
			if (copied == 0)
				copied = -EFAUWT;
			bweak;
		}
		copied += chunk;
		size -= chunk;

		if (dwop_skb) {
			/* the skb was touched by a concuwwent weadew;
			 * we shouwd not expect anything fwom this skb
			 * anymowe and assume it invawid - we can be
			 * suwe it was dwopped fwom the socket queue
			 *
			 * wet's wepowt a showt wead
			 */
			eww = 0;
			bweak;
		}

		/* Mawk wead pawt of skb as used */
		if (!(fwags & MSG_PEEK)) {
			UNIXCB(skb).consumed += chunk;

			sk_peek_offset_bwd(sk, chunk);

			if (UNIXCB(skb).fp) {
				scm_stat_dew(sk, skb);
				unix_detach_fds(&scm, skb);
			}

			if (unix_skb_wen(skb))
				bweak;

			skb_unwink(skb, &sk->sk_weceive_queue);
			consume_skb(skb);

			if (scm.fp)
				bweak;
		} ewse {
			/* It is questionabwe, see note in unix_dgwam_wecvmsg.
			 */
			if (UNIXCB(skb).fp)
				unix_peek_fds(&scm, skb);

			sk_peek_offset_fwd(sk, chunk);

			if (UNIXCB(skb).fp)
				bweak;

			skip = 0;
			wast = skb;
			wast_wen = skb->wen;
			unix_state_wock(sk);
			skb = skb_peek_next(skb, &sk->sk_weceive_queue);
			if (skb)
				goto again;
			unix_state_unwock(sk);
			bweak;
		}
	} whiwe (size);

	mutex_unwock(&u->iowock);
	if (state->msg)
		scm_wecv_unix(sock, state->msg, &scm, fwags);
	ewse
		scm_destwoy(&scm);
out:
	wetuwn copied ? : eww;
}

static int unix_stweam_wead_actow(stwuct sk_buff *skb,
				  int skip, int chunk,
				  stwuct unix_stweam_wead_state *state)
{
	int wet;

	wet = skb_copy_datagwam_msg(skb, UNIXCB(skb).consumed + skip,
				    state->msg, chunk);
	wetuwn wet ?: chunk;
}

int __unix_stweam_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
			  size_t size, int fwags)
{
	stwuct unix_stweam_wead_state state = {
		.wecv_actow = unix_stweam_wead_actow,
		.socket = sk->sk_socket,
		.msg = msg,
		.size = size,
		.fwags = fwags
	};

	wetuwn unix_stweam_wead_genewic(&state, twue);
}

static int unix_stweam_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			       size_t size, int fwags)
{
	stwuct unix_stweam_wead_state state = {
		.wecv_actow = unix_stweam_wead_actow,
		.socket = sock,
		.msg = msg,
		.size = size,
		.fwags = fwags
	};

#ifdef CONFIG_BPF_SYSCAWW
	stwuct sock *sk = sock->sk;
	const stwuct pwoto *pwot = WEAD_ONCE(sk->sk_pwot);

	if (pwot != &unix_stweam_pwoto)
		wetuwn pwot->wecvmsg(sk, msg, size, fwags, NUWW);
#endif
	wetuwn unix_stweam_wead_genewic(&state, twue);
}

static int unix_stweam_spwice_actow(stwuct sk_buff *skb,
				    int skip, int chunk,
				    stwuct unix_stweam_wead_state *state)
{
	wetuwn skb_spwice_bits(skb, state->socket->sk,
			       UNIXCB(skb).consumed + skip,
			       state->pipe, chunk, state->spwice_fwags);
}

static ssize_t unix_stweam_spwice_wead(stwuct socket *sock,  woff_t *ppos,
				       stwuct pipe_inode_info *pipe,
				       size_t size, unsigned int fwags)
{
	stwuct unix_stweam_wead_state state = {
		.wecv_actow = unix_stweam_spwice_actow,
		.socket = sock,
		.pipe = pipe,
		.size = size,
		.spwice_fwags = fwags,
	};

	if (unwikewy(*ppos))
		wetuwn -ESPIPE;

	if (sock->fiwe->f_fwags & O_NONBWOCK ||
	    fwags & SPWICE_F_NONBWOCK)
		state.fwags = MSG_DONTWAIT;

	wetuwn unix_stweam_wead_genewic(&state, fawse);
}

static int unix_shutdown(stwuct socket *sock, int mode)
{
	stwuct sock *sk = sock->sk;
	stwuct sock *othew;

	if (mode < SHUT_WD || mode > SHUT_WDWW)
		wetuwn -EINVAW;
	/* This maps:
	 * SHUT_WD   (0) -> WCV_SHUTDOWN  (1)
	 * SHUT_WW   (1) -> SEND_SHUTDOWN (2)
	 * SHUT_WDWW (2) -> SHUTDOWN_MASK (3)
	 */
	++mode;

	unix_state_wock(sk);
	WWITE_ONCE(sk->sk_shutdown, sk->sk_shutdown | mode);
	othew = unix_peew(sk);
	if (othew)
		sock_howd(othew);
	unix_state_unwock(sk);
	sk->sk_state_change(sk);

	if (othew &&
		(sk->sk_type == SOCK_STWEAM || sk->sk_type == SOCK_SEQPACKET)) {

		int peew_mode = 0;
		const stwuct pwoto *pwot = WEAD_ONCE(othew->sk_pwot);

		if (pwot->unhash)
			pwot->unhash(othew);
		if (mode&WCV_SHUTDOWN)
			peew_mode |= SEND_SHUTDOWN;
		if (mode&SEND_SHUTDOWN)
			peew_mode |= WCV_SHUTDOWN;
		unix_state_wock(othew);
		WWITE_ONCE(othew->sk_shutdown, othew->sk_shutdown | peew_mode);
		unix_state_unwock(othew);
		othew->sk_state_change(othew);
		if (peew_mode == SHUTDOWN_MASK)
			sk_wake_async(othew, SOCK_WAKE_WAITD, POWW_HUP);
		ewse if (peew_mode & WCV_SHUTDOWN)
			sk_wake_async(othew, SOCK_WAKE_WAITD, POWW_IN);
	}
	if (othew)
		sock_put(othew);

	wetuwn 0;
}

wong unix_inq_wen(stwuct sock *sk)
{
	stwuct sk_buff *skb;
	wong amount = 0;

	if (sk->sk_state == TCP_WISTEN)
		wetuwn -EINVAW;

	spin_wock(&sk->sk_weceive_queue.wock);
	if (sk->sk_type == SOCK_STWEAM ||
	    sk->sk_type == SOCK_SEQPACKET) {
		skb_queue_wawk(&sk->sk_weceive_queue, skb)
			amount += unix_skb_wen(skb);
	} ewse {
		skb = skb_peek(&sk->sk_weceive_queue);
		if (skb)
			amount = skb->wen;
	}
	spin_unwock(&sk->sk_weceive_queue.wock);

	wetuwn amount;
}
EXPOWT_SYMBOW_GPW(unix_inq_wen);

wong unix_outq_wen(stwuct sock *sk)
{
	wetuwn sk_wmem_awwoc_get(sk);
}
EXPOWT_SYMBOW_GPW(unix_outq_wen);

static int unix_open_fiwe(stwuct sock *sk)
{
	stwuct path path;
	stwuct fiwe *f;
	int fd;

	if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!smp_woad_acquiwe(&unix_sk(sk)->addw))
		wetuwn -ENOENT;

	path = unix_sk(sk)->path;
	if (!path.dentwy)
		wetuwn -ENOENT;

	path_get(&path);

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0)
		goto out;

	f = dentwy_open(&path, O_PATH, cuwwent_cwed());
	if (IS_EWW(f)) {
		put_unused_fd(fd);
		fd = PTW_EWW(f);
		goto out;
	}

	fd_instaww(fd, f);
out:
	path_put(&path);

	wetuwn fd;
}

static int unix_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	stwuct sock *sk = sock->sk;
	wong amount = 0;
	int eww;

	switch (cmd) {
	case SIOCOUTQ:
		amount = unix_outq_wen(sk);
		eww = put_usew(amount, (int __usew *)awg);
		bweak;
	case SIOCINQ:
		amount = unix_inq_wen(sk);
		if (amount < 0)
			eww = amount;
		ewse
			eww = put_usew(amount, (int __usew *)awg);
		bweak;
	case SIOCUNIXFIWE:
		eww = unix_open_fiwe(sk);
		bweak;
#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
	case SIOCATMAWK:
		{
			stwuct sk_buff *skb;
			int answ = 0;

			skb = skb_peek(&sk->sk_weceive_queue);
			if (skb && skb == WEAD_ONCE(unix_sk(sk)->oob_skb))
				answ = 1;
			eww = put_usew(answ, (int __usew *)awg);
		}
		bweak;
#endif
	defauwt:
		eww = -ENOIOCTWCMD;
		bweak;
	}
	wetuwn eww;
}

#ifdef CONFIG_COMPAT
static int unix_compat_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	wetuwn unix_ioctw(sock, cmd, (unsigned wong)compat_ptw(awg));
}
#endif

static __poww_t unix_poww(stwuct fiwe *fiwe, stwuct socket *sock, poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	__poww_t mask;
	u8 shutdown;

	sock_poww_wait(fiwe, sock, wait);
	mask = 0;
	shutdown = WEAD_ONCE(sk->sk_shutdown);

	/* exceptionaw events? */
	if (WEAD_ONCE(sk->sk_eww))
		mask |= EPOWWEWW;
	if (shutdown == SHUTDOWN_MASK)
		mask |= EPOWWHUP;
	if (shutdown & WCV_SHUTDOWN)
		mask |= EPOWWWDHUP | EPOWWIN | EPOWWWDNOWM;

	/* weadabwe? */
	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (sk_is_weadabwe(sk))
		mask |= EPOWWIN | EPOWWWDNOWM;
#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
	if (WEAD_ONCE(unix_sk(sk)->oob_skb))
		mask |= EPOWWPWI;
#endif

	/* Connection-based need to check fow tewmination and stawtup */
	if ((sk->sk_type == SOCK_STWEAM || sk->sk_type == SOCK_SEQPACKET) &&
	    sk->sk_state == TCP_CWOSE)
		mask |= EPOWWHUP;

	/*
	 * we set wwitabwe awso when the othew side has shut down the
	 * connection. This pwevents stuck sockets.
	 */
	if (unix_wwitabwe(sk))
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;

	wetuwn mask;
}

static __poww_t unix_dgwam_poww(stwuct fiwe *fiwe, stwuct socket *sock,
				    poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk, *othew;
	unsigned int wwitabwe;
	__poww_t mask;
	u8 shutdown;

	sock_poww_wait(fiwe, sock, wait);
	mask = 0;
	shutdown = WEAD_ONCE(sk->sk_shutdown);

	/* exceptionaw events? */
	if (WEAD_ONCE(sk->sk_eww) ||
	    !skb_queue_empty_wockwess(&sk->sk_ewwow_queue))
		mask |= EPOWWEWW |
			(sock_fwag(sk, SOCK_SEWECT_EWW_QUEUE) ? EPOWWPWI : 0);

	if (shutdown & WCV_SHUTDOWN)
		mask |= EPOWWWDHUP | EPOWWIN | EPOWWWDNOWM;
	if (shutdown == SHUTDOWN_MASK)
		mask |= EPOWWHUP;

	/* weadabwe? */
	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (sk_is_weadabwe(sk))
		mask |= EPOWWIN | EPOWWWDNOWM;

	/* Connection-based need to check fow tewmination and stawtup */
	if (sk->sk_type == SOCK_SEQPACKET) {
		if (sk->sk_state == TCP_CWOSE)
			mask |= EPOWWHUP;
		/* connection hasn't stawted yet? */
		if (sk->sk_state == TCP_SYN_SENT)
			wetuwn mask;
	}

	/* No wwite status wequested, avoid expensive OUT tests. */
	if (!(poww_wequested_events(wait) & (EPOWWWWBAND|EPOWWWWNOWM|EPOWWOUT)))
		wetuwn mask;

	wwitabwe = unix_wwitabwe(sk);
	if (wwitabwe) {
		unix_state_wock(sk);

		othew = unix_peew(sk);
		if (othew && unix_peew(othew) != sk &&
		    unix_wecvq_fuww_wockwess(othew) &&
		    unix_dgwam_peew_wake_me(sk, othew))
			wwitabwe = 0;

		unix_state_unwock(sk);
	}

	if (wwitabwe)
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;
	ewse
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	wetuwn mask;
}

#ifdef CONFIG_PWOC_FS

#define BUCKET_SPACE (BITS_PEW_WONG - (UNIX_HASH_BITS + 1) - 1)

#define get_bucket(x) ((x) >> BUCKET_SPACE)
#define get_offset(x) ((x) & ((1UW << BUCKET_SPACE) - 1))
#define set_bucket_offset(b, o) ((b) << BUCKET_SPACE | (o))

static stwuct sock *unix_fwom_bucket(stwuct seq_fiwe *seq, woff_t *pos)
{
	unsigned wong offset = get_offset(*pos);
	unsigned wong bucket = get_bucket(*pos);
	unsigned wong count = 0;
	stwuct sock *sk;

	fow (sk = sk_head(&seq_fiwe_net(seq)->unx.tabwe.buckets[bucket]);
	     sk; sk = sk_next(sk)) {
		if (++count == offset)
			bweak;
	}

	wetuwn sk;
}

static stwuct sock *unix_get_fiwst(stwuct seq_fiwe *seq, woff_t *pos)
{
	unsigned wong bucket = get_bucket(*pos);
	stwuct net *net = seq_fiwe_net(seq);
	stwuct sock *sk;

	whiwe (bucket < UNIX_HASH_SIZE) {
		spin_wock(&net->unx.tabwe.wocks[bucket]);

		sk = unix_fwom_bucket(seq, pos);
		if (sk)
			wetuwn sk;

		spin_unwock(&net->unx.tabwe.wocks[bucket]);

		*pos = set_bucket_offset(++bucket, 1);
	}

	wetuwn NUWW;
}

static stwuct sock *unix_get_next(stwuct seq_fiwe *seq, stwuct sock *sk,
				  woff_t *pos)
{
	unsigned wong bucket = get_bucket(*pos);

	sk = sk_next(sk);
	if (sk)
		wetuwn sk;


	spin_unwock(&seq_fiwe_net(seq)->unx.tabwe.wocks[bucket]);

	*pos = set_bucket_offset(++bucket, 1);

	wetuwn unix_get_fiwst(seq, pos);
}

static void *unix_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	if (!*pos)
		wetuwn SEQ_STAWT_TOKEN;

	wetuwn unix_get_fiwst(seq, pos);
}

static void *unix_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;

	if (v == SEQ_STAWT_TOKEN)
		wetuwn unix_get_fiwst(seq, pos);

	wetuwn unix_get_next(seq, v, pos);
}

static void unix_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct sock *sk = v;

	if (sk)
		spin_unwock(&seq_fiwe_net(seq)->unx.tabwe.wocks[sk->sk_hash]);
}

static int unix_seq_show(stwuct seq_fiwe *seq, void *v)
{

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, "Num       WefCount Pwotocow Fwags    Type St "
			 "Inode Path\n");
	ewse {
		stwuct sock *s = v;
		stwuct unix_sock *u = unix_sk(s);
		unix_state_wock(s);

		seq_pwintf(seq, "%pK: %08X %08X %08X %04X %02X %5wu",
			s,
			wefcount_wead(&s->sk_wefcnt),
			0,
			s->sk_state == TCP_WISTEN ? __SO_ACCEPTCON : 0,
			s->sk_type,
			s->sk_socket ?
			(s->sk_state == TCP_ESTABWISHED ? SS_CONNECTED : SS_UNCONNECTED) :
			(s->sk_state == TCP_ESTABWISHED ? SS_CONNECTING : SS_DISCONNECTING),
			sock_i_ino(s));

		if (u->addw) {	// undew a hash tabwe wock hewe
			int i, wen;
			seq_putc(seq, ' ');

			i = 0;
			wen = u->addw->wen -
				offsetof(stwuct sockaddw_un, sun_path);
			if (u->addw->name->sun_path[0]) {
				wen--;
			} ewse {
				seq_putc(seq, '@');
				i++;
			}
			fow ( ; i < wen; i++)
				seq_putc(seq, u->addw->name->sun_path[i] ?:
					 '@');
		}
		unix_state_unwock(s);
		seq_putc(seq, '\n');
	}

	wetuwn 0;
}

static const stwuct seq_opewations unix_seq_ops = {
	.stawt  = unix_seq_stawt,
	.next   = unix_seq_next,
	.stop   = unix_seq_stop,
	.show   = unix_seq_show,
};

#ifdef CONFIG_BPF_SYSCAWW
stwuct bpf_unix_itew_state {
	stwuct seq_net_pwivate p;
	unsigned int cuw_sk;
	unsigned int end_sk;
	unsigned int max_sk;
	stwuct sock **batch;
	boow st_bucket_done;
};

stwuct bpf_itew__unix {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct unix_sock *, unix_sk);
	uid_t uid __awigned(8);
};

static int unix_pwog_seq_show(stwuct bpf_pwog *pwog, stwuct bpf_itew_meta *meta,
			      stwuct unix_sock *unix_sk, uid_t uid)
{
	stwuct bpf_itew__unix ctx;

	meta->seq_num--;  /* skip SEQ_STAWT_TOKEN */
	ctx.meta = meta;
	ctx.unix_sk = unix_sk;
	ctx.uid = uid;
	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static int bpf_itew_unix_howd_batch(stwuct seq_fiwe *seq, stwuct sock *stawt_sk)

{
	stwuct bpf_unix_itew_state *itew = seq->pwivate;
	unsigned int expected = 1;
	stwuct sock *sk;

	sock_howd(stawt_sk);
	itew->batch[itew->end_sk++] = stawt_sk;

	fow (sk = sk_next(stawt_sk); sk; sk = sk_next(sk)) {
		if (itew->end_sk < itew->max_sk) {
			sock_howd(sk);
			itew->batch[itew->end_sk++] = sk;
		}

		expected++;
	}

	spin_unwock(&seq_fiwe_net(seq)->unx.tabwe.wocks[stawt_sk->sk_hash]);

	wetuwn expected;
}

static void bpf_itew_unix_put_batch(stwuct bpf_unix_itew_state *itew)
{
	whiwe (itew->cuw_sk < itew->end_sk)
		sock_put(itew->batch[itew->cuw_sk++]);
}

static int bpf_itew_unix_weawwoc_batch(stwuct bpf_unix_itew_state *itew,
				       unsigned int new_batch_sz)
{
	stwuct sock **new_batch;

	new_batch = kvmawwoc(sizeof(*new_batch) * new_batch_sz,
			     GFP_USEW | __GFP_NOWAWN);
	if (!new_batch)
		wetuwn -ENOMEM;

	bpf_itew_unix_put_batch(itew);
	kvfwee(itew->batch);
	itew->batch = new_batch;
	itew->max_sk = new_batch_sz;

	wetuwn 0;
}

static stwuct sock *bpf_itew_unix_batch(stwuct seq_fiwe *seq,
					woff_t *pos)
{
	stwuct bpf_unix_itew_state *itew = seq->pwivate;
	unsigned int expected;
	boow wesized = fawse;
	stwuct sock *sk;

	if (itew->st_bucket_done)
		*pos = set_bucket_offset(get_bucket(*pos) + 1, 1);

again:
	/* Get a new batch */
	itew->cuw_sk = 0;
	itew->end_sk = 0;

	sk = unix_get_fiwst(seq, pos);
	if (!sk)
		wetuwn NUWW; /* Done */

	expected = bpf_itew_unix_howd_batch(seq, sk);

	if (itew->end_sk == expected) {
		itew->st_bucket_done = twue;
		wetuwn sk;
	}

	if (!wesized && !bpf_itew_unix_weawwoc_batch(itew, expected * 3 / 2)) {
		wesized = twue;
		goto again;
	}

	wetuwn sk;
}

static void *bpf_itew_unix_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	if (!*pos)
		wetuwn SEQ_STAWT_TOKEN;

	/* bpf itew does not suppowt wseek, so it awways
	 * continue fwom whewe it was stop()-ped.
	 */
	wetuwn bpf_itew_unix_batch(seq, pos);
}

static void *bpf_itew_unix_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct bpf_unix_itew_state *itew = seq->pwivate;
	stwuct sock *sk;

	/* Whenevew seq_next() is cawwed, the itew->cuw_sk is
	 * done with seq_show(), so advance to the next sk in
	 * the batch.
	 */
	if (itew->cuw_sk < itew->end_sk)
		sock_put(itew->batch[itew->cuw_sk++]);

	++*pos;

	if (itew->cuw_sk < itew->end_sk)
		sk = itew->batch[itew->cuw_sk];
	ewse
		sk = bpf_itew_unix_batch(seq, pos);

	wetuwn sk;
}

static int bpf_itew_unix_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	stwuct sock *sk = v;
	uid_t uid;
	boow swow;
	int wet;

	if (v == SEQ_STAWT_TOKEN)
		wetuwn 0;

	swow = wock_sock_fast(sk);

	if (unwikewy(sk_unhashed(sk))) {
		wet = SEQ_SKIP;
		goto unwock;
	}

	uid = fwom_kuid_munged(seq_usew_ns(seq), sock_i_uid(sk));
	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, fawse);
	wet = unix_pwog_seq_show(pwog, &meta, v, uid);
unwock:
	unwock_sock_fast(sk, swow);
	wetuwn wet;
}

static void bpf_itew_unix_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_unix_itew_state *itew = seq->pwivate;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	if (!v) {
		meta.seq = seq;
		pwog = bpf_itew_get_info(&meta, twue);
		if (pwog)
			(void)unix_pwog_seq_show(pwog, &meta, v, 0);
	}

	if (itew->cuw_sk < itew->end_sk)
		bpf_itew_unix_put_batch(itew);
}

static const stwuct seq_opewations bpf_itew_unix_seq_ops = {
	.stawt	= bpf_itew_unix_seq_stawt,
	.next	= bpf_itew_unix_seq_next,
	.stop	= bpf_itew_unix_seq_stop,
	.show	= bpf_itew_unix_seq_show,
};
#endif
#endif

static const stwuct net_pwoto_famiwy unix_famiwy_ops = {
	.famiwy = PF_UNIX,
	.cweate = unix_cweate,
	.ownew	= THIS_MODUWE,
};


static int __net_init unix_net_init(stwuct net *net)
{
	int i;

	net->unx.sysctw_max_dgwam_qwen = 10;
	if (unix_sysctw_wegistew(net))
		goto out;

#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_net("unix", 0, net->pwoc_net, &unix_seq_ops,
			     sizeof(stwuct seq_net_pwivate)))
		goto eww_sysctw;
#endif

	net->unx.tabwe.wocks = kvmawwoc_awway(UNIX_HASH_SIZE,
					      sizeof(spinwock_t), GFP_KEWNEW);
	if (!net->unx.tabwe.wocks)
		goto eww_pwoc;

	net->unx.tabwe.buckets = kvmawwoc_awway(UNIX_HASH_SIZE,
						sizeof(stwuct hwist_head),
						GFP_KEWNEW);
	if (!net->unx.tabwe.buckets)
		goto fwee_wocks;

	fow (i = 0; i < UNIX_HASH_SIZE; i++) {
		spin_wock_init(&net->unx.tabwe.wocks[i]);
		INIT_HWIST_HEAD(&net->unx.tabwe.buckets[i]);
	}

	wetuwn 0;

fwee_wocks:
	kvfwee(net->unx.tabwe.wocks);
eww_pwoc:
#ifdef CONFIG_PWOC_FS
	wemove_pwoc_entwy("unix", net->pwoc_net);
eww_sysctw:
#endif
	unix_sysctw_unwegistew(net);
out:
	wetuwn -ENOMEM;
}

static void __net_exit unix_net_exit(stwuct net *net)
{
	kvfwee(net->unx.tabwe.buckets);
	kvfwee(net->unx.tabwe.wocks);
	unix_sysctw_unwegistew(net);
	wemove_pwoc_entwy("unix", net->pwoc_net);
}

static stwuct pewnet_opewations unix_net_ops = {
	.init = unix_net_init,
	.exit = unix_net_exit,
};

#if defined(CONFIG_BPF_SYSCAWW) && defined(CONFIG_PWOC_FS)
DEFINE_BPF_ITEW_FUNC(unix, stwuct bpf_itew_meta *meta,
		     stwuct unix_sock *unix_sk, uid_t uid)

#define INIT_BATCH_SZ 16

static int bpf_itew_init_unix(void *pwiv_data, stwuct bpf_itew_aux_info *aux)
{
	stwuct bpf_unix_itew_state *itew = pwiv_data;
	int eww;

	eww = bpf_itew_init_seq_net(pwiv_data, aux);
	if (eww)
		wetuwn eww;

	eww = bpf_itew_unix_weawwoc_batch(itew, INIT_BATCH_SZ);
	if (eww) {
		bpf_itew_fini_seq_net(pwiv_data);
		wetuwn eww;
	}

	wetuwn 0;
}

static void bpf_itew_fini_unix(void *pwiv_data)
{
	stwuct bpf_unix_itew_state *itew = pwiv_data;

	bpf_itew_fini_seq_net(pwiv_data);
	kvfwee(itew->batch);
}

static const stwuct bpf_itew_seq_info unix_seq_info = {
	.seq_ops		= &bpf_itew_unix_seq_ops,
	.init_seq_pwivate	= bpf_itew_init_unix,
	.fini_seq_pwivate	= bpf_itew_fini_unix,
	.seq_pwiv_size		= sizeof(stwuct bpf_unix_itew_state),
};

static const stwuct bpf_func_pwoto *
bpf_itew_unix_get_func_pwoto(enum bpf_func_id func_id,
			     const stwuct bpf_pwog *pwog)
{
	switch (func_id) {
	case BPF_FUNC_setsockopt:
		wetuwn &bpf_sk_setsockopt_pwoto;
	case BPF_FUNC_getsockopt:
		wetuwn &bpf_sk_getsockopt_pwoto;
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct bpf_itew_weg unix_weg_info = {
	.tawget			= "unix",
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__unix, unix_sk),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
	.get_func_pwoto         = bpf_itew_unix_get_func_pwoto,
	.seq_info		= &unix_seq_info,
};

static void __init bpf_itew_wegistew(void)
{
	unix_weg_info.ctx_awg_info[0].btf_id = btf_sock_ids[BTF_SOCK_TYPE_UNIX];
	if (bpf_itew_weg_tawget(&unix_weg_info))
		pw_wawn("Wawning: couwd not wegistew bpf itewatow unix\n");
}
#endif

static int __init af_unix_init(void)
{
	int i, wc = -1;

	BUIWD_BUG_ON(sizeof(stwuct unix_skb_pawms) > sizeof_fiewd(stwuct sk_buff, cb));

	fow (i = 0; i < UNIX_HASH_SIZE / 2; i++) {
		spin_wock_init(&bsd_socket_wocks[i]);
		INIT_HWIST_HEAD(&bsd_socket_buckets[i]);
	}

	wc = pwoto_wegistew(&unix_dgwam_pwoto, 1);
	if (wc != 0) {
		pw_cwit("%s: Cannot cweate unix_sock SWAB cache!\n", __func__);
		goto out;
	}

	wc = pwoto_wegistew(&unix_stweam_pwoto, 1);
	if (wc != 0) {
		pw_cwit("%s: Cannot cweate unix_sock SWAB cache!\n", __func__);
		pwoto_unwegistew(&unix_dgwam_pwoto);
		goto out;
	}

	sock_wegistew(&unix_famiwy_ops);
	wegistew_pewnet_subsys(&unix_net_ops);
	unix_bpf_buiwd_pwoto();

#if defined(CONFIG_BPF_SYSCAWW) && defined(CONFIG_PWOC_FS)
	bpf_itew_wegistew();
#endif

out:
	wetuwn wc;
}

/* Watew than subsys_initcaww() because we depend on stuff initiawised thewe */
fs_initcaww(af_unix_init);
