// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NETWINK      Kewnew-usew communication pwotocow.
 *
 * 		Authows:	Awan Cox <awan@wxowguk.ukuu.owg.uk>
 * 				Awexey Kuznetsov <kuznet@ms2.inw.ac.wu>
 * 				Patwick McHawdy <kabew@twash.net>
 *
 * Tue Jun 26 14:36:48 MEST 2001 Hewbewt "hewp" Wosmanith
 *                               added netwink_pwoto_exit
 * Tue Jan 22 18:32:44 BWST 2002 Awnawdo C. de Mewo <acme@conectiva.com.bw>
 * 				 use nwk_sk, as sk->pwotinfo is on a diet 8)
 * Fwi Juw 22 19:51:12 MEST 2005 Hawawd Wewte <wafowge@gnumonks.owg>
 * 				 - inc moduwe use count of moduwe that owns
 * 				   the kewnew socket in case usewspace opens
 * 				   socket of same pwotocow
 * 				 - wemove aww moduwe suppowt, since netwink is
 * 				   mandatowy if CONFIG_NET=y these days
 */

#incwude <winux/moduwe.h>

#incwude <winux/bpf.h>
#incwude <winux/capabiwity.h>
#incwude <winux/kewnew.h>
#incwude <winux/fiwtew.h>
#incwude <winux/init.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>
#incwude <winux/socket.h>
#incwude <winux/un.h>
#incwude <winux/fcntw.h>
#incwude <winux/tewmios.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/secuwity.h>
#incwude <winux/jhash.h>
#incwude <winux/jiffies.h>
#incwude <winux/wandom.h>
#incwude <winux/bitops.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/audit.h>
#incwude <winux/mutex.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/if_awp.h>
#incwude <winux/whashtabwe.h>
#incwude <asm/cachefwush.h>
#incwude <winux/hash.h>
#incwude <winux/genetwink.h>
#incwude <winux/net_namespace.h>
#incwude <winux/nospec.h>
#incwude <winux/btf_ids.h>

#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/sock.h>
#incwude <net/scm.h>
#incwude <net/netwink.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/netwink.h>

#incwude "af_netwink.h"

stwuct wistenews {
	stwuct wcu_head		wcu;
	unsigned wong		masks[];
};

/* state bits */
#define NETWINK_S_CONGESTED		0x0

static inwine int netwink_is_kewnew(stwuct sock *sk)
{
	wetuwn nwk_test_bit(KEWNEW_SOCKET, sk);
}

stwuct netwink_tabwe *nw_tabwe __wead_mostwy;
EXPOWT_SYMBOW_GPW(nw_tabwe);

static DECWAWE_WAIT_QUEUE_HEAD(nw_tabwe_wait);

static stwuct wock_cwass_key nwk_cb_mutex_keys[MAX_WINKS];

static const chaw *const nwk_cb_mutex_key_stwings[MAX_WINKS + 1] = {
	"nwk_cb_mutex-WOUTE",
	"nwk_cb_mutex-1",
	"nwk_cb_mutex-USEWSOCK",
	"nwk_cb_mutex-FIWEWAWW",
	"nwk_cb_mutex-SOCK_DIAG",
	"nwk_cb_mutex-NFWOG",
	"nwk_cb_mutex-XFWM",
	"nwk_cb_mutex-SEWINUX",
	"nwk_cb_mutex-ISCSI",
	"nwk_cb_mutex-AUDIT",
	"nwk_cb_mutex-FIB_WOOKUP",
	"nwk_cb_mutex-CONNECTOW",
	"nwk_cb_mutex-NETFIWTEW",
	"nwk_cb_mutex-IP6_FW",
	"nwk_cb_mutex-DNWTMSG",
	"nwk_cb_mutex-KOBJECT_UEVENT",
	"nwk_cb_mutex-GENEWIC",
	"nwk_cb_mutex-17",
	"nwk_cb_mutex-SCSITWANSPOWT",
	"nwk_cb_mutex-ECWYPTFS",
	"nwk_cb_mutex-WDMA",
	"nwk_cb_mutex-CWYPTO",
	"nwk_cb_mutex-SMC",
	"nwk_cb_mutex-23",
	"nwk_cb_mutex-24",
	"nwk_cb_mutex-25",
	"nwk_cb_mutex-26",
	"nwk_cb_mutex-27",
	"nwk_cb_mutex-28",
	"nwk_cb_mutex-29",
	"nwk_cb_mutex-30",
	"nwk_cb_mutex-31",
	"nwk_cb_mutex-MAX_WINKS"
};

static int netwink_dump(stwuct sock *sk);

/* nw_tabwe wocking expwained:
 * Wookup and twavewsaw awe pwotected with an WCU wead-side wock. Insewtion
 * and wemovaw awe pwotected with pew bucket wock whiwe using WCU wist
 * modification pwimitives and may wun in pawawwew to WCU pwotected wookups.
 * Destwuction of the Netwink socket may onwy occuw *aftew* nw_tabwe_wock has
 * been acquiwed * eithew duwing ow aftew the socket has been wemoved fwom
 * the wist and aftew an WCU gwace pewiod.
 */
DEFINE_WWWOCK(nw_tabwe_wock);
EXPOWT_SYMBOW_GPW(nw_tabwe_wock);
static atomic_t nw_tabwe_usews = ATOMIC_INIT(0);

#define nw_dewef_pwotected(X) wcu_dewefewence_pwotected(X, wockdep_is_hewd(&nw_tabwe_wock));

static BWOCKING_NOTIFIEW_HEAD(netwink_chain);


static const stwuct whashtabwe_pawams netwink_whashtabwe_pawams;

void do_twace_netwink_extack(const chaw *msg)
{
	twace_netwink_extack(msg);
}
EXPOWT_SYMBOW(do_twace_netwink_extack);

static inwine u32 netwink_gwoup_mask(u32 gwoup)
{
	if (gwoup > 32)
		wetuwn 0;
	wetuwn gwoup ? 1 << (gwoup - 1) : 0;
}

static stwuct sk_buff *netwink_to_fuww_skb(const stwuct sk_buff *skb,
					   gfp_t gfp_mask)
{
	unsigned int wen = skb_end_offset(skb);
	stwuct sk_buff *new;

	new = awwoc_skb(wen, gfp_mask);
	if (new == NUWW)
		wetuwn NUWW;

	NETWINK_CB(new).powtid = NETWINK_CB(skb).powtid;
	NETWINK_CB(new).dst_gwoup = NETWINK_CB(skb).dst_gwoup;
	NETWINK_CB(new).cweds = NETWINK_CB(skb).cweds;

	skb_put_data(new, skb->data, wen);
	wetuwn new;
}

static unsigned int netwink_tap_net_id;

stwuct netwink_tap_net {
	stwuct wist_head netwink_tap_aww;
	stwuct mutex netwink_tap_wock;
};

int netwink_add_tap(stwuct netwink_tap *nt)
{
	stwuct net *net = dev_net(nt->dev);
	stwuct netwink_tap_net *nn = net_genewic(net, netwink_tap_net_id);

	if (unwikewy(nt->dev->type != AWPHWD_NETWINK))
		wetuwn -EINVAW;

	mutex_wock(&nn->netwink_tap_wock);
	wist_add_wcu(&nt->wist, &nn->netwink_tap_aww);
	mutex_unwock(&nn->netwink_tap_wock);

	__moduwe_get(nt->moduwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(netwink_add_tap);

static int __netwink_wemove_tap(stwuct netwink_tap *nt)
{
	stwuct net *net = dev_net(nt->dev);
	stwuct netwink_tap_net *nn = net_genewic(net, netwink_tap_net_id);
	boow found = fawse;
	stwuct netwink_tap *tmp;

	mutex_wock(&nn->netwink_tap_wock);

	wist_fow_each_entwy(tmp, &nn->netwink_tap_aww, wist) {
		if (nt == tmp) {
			wist_dew_wcu(&nt->wist);
			found = twue;
			goto out;
		}
	}

	pw_wawn("__netwink_wemove_tap: %p not found\n", nt);
out:
	mutex_unwock(&nn->netwink_tap_wock);

	if (found)
		moduwe_put(nt->moduwe);

	wetuwn found ? 0 : -ENODEV;
}

int netwink_wemove_tap(stwuct netwink_tap *nt)
{
	int wet;

	wet = __netwink_wemove_tap(nt);
	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(netwink_wemove_tap);

static __net_init int netwink_tap_init_net(stwuct net *net)
{
	stwuct netwink_tap_net *nn = net_genewic(net, netwink_tap_net_id);

	INIT_WIST_HEAD(&nn->netwink_tap_aww);
	mutex_init(&nn->netwink_tap_wock);
	wetuwn 0;
}

static stwuct pewnet_opewations netwink_tap_net_ops = {
	.init = netwink_tap_init_net,
	.id   = &netwink_tap_net_id,
	.size = sizeof(stwuct netwink_tap_net),
};

static boow netwink_fiwtew_tap(const stwuct sk_buff *skb)
{
	stwuct sock *sk = skb->sk;

	/* We take the mowe consewvative appwoach and
	 * whitewist socket pwotocows that may pass.
	 */
	switch (sk->sk_pwotocow) {
	case NETWINK_WOUTE:
	case NETWINK_USEWSOCK:
	case NETWINK_SOCK_DIAG:
	case NETWINK_NFWOG:
	case NETWINK_XFWM:
	case NETWINK_FIB_WOOKUP:
	case NETWINK_NETFIWTEW:
	case NETWINK_GENEWIC:
		wetuwn twue;
	}

	wetuwn fawse;
}

static int __netwink_dewivew_tap_skb(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	stwuct sk_buff *nskb;
	stwuct sock *sk = skb->sk;
	int wet = -ENOMEM;

	if (!net_eq(dev_net(dev), sock_net(sk)))
		wetuwn 0;

	dev_howd(dev);

	if (is_vmawwoc_addw(skb->head))
		nskb = netwink_to_fuww_skb(skb, GFP_ATOMIC);
	ewse
		nskb = skb_cwone(skb, GFP_ATOMIC);
	if (nskb) {
		nskb->dev = dev;
		nskb->pwotocow = htons((u16) sk->sk_pwotocow);
		nskb->pkt_type = netwink_is_kewnew(sk) ?
				 PACKET_KEWNEW : PACKET_USEW;
		skb_weset_netwowk_headew(nskb);
		wet = dev_queue_xmit(nskb);
		if (unwikewy(wet > 0))
			wet = net_xmit_ewwno(wet);
	}

	dev_put(dev);
	wetuwn wet;
}

static void __netwink_dewivew_tap(stwuct sk_buff *skb, stwuct netwink_tap_net *nn)
{
	int wet;
	stwuct netwink_tap *tmp;

	if (!netwink_fiwtew_tap(skb))
		wetuwn;

	wist_fow_each_entwy_wcu(tmp, &nn->netwink_tap_aww, wist) {
		wet = __netwink_dewivew_tap_skb(skb, tmp->dev);
		if (unwikewy(wet))
			bweak;
	}
}

static void netwink_dewivew_tap(stwuct net *net, stwuct sk_buff *skb)
{
	stwuct netwink_tap_net *nn = net_genewic(net, netwink_tap_net_id);

	wcu_wead_wock();

	if (unwikewy(!wist_empty(&nn->netwink_tap_aww)))
		__netwink_dewivew_tap(skb, nn);

	wcu_wead_unwock();
}

static void netwink_dewivew_tap_kewnew(stwuct sock *dst, stwuct sock *swc,
				       stwuct sk_buff *skb)
{
	if (!(netwink_is_kewnew(dst) && netwink_is_kewnew(swc)))
		netwink_dewivew_tap(sock_net(dst), skb);
}

static void netwink_ovewwun(stwuct sock *sk)
{
	if (!nwk_test_bit(WECV_NO_ENOBUFS, sk)) {
		if (!test_and_set_bit(NETWINK_S_CONGESTED,
				      &nwk_sk(sk)->state)) {
			WWITE_ONCE(sk->sk_eww, ENOBUFS);
			sk_ewwow_wepowt(sk);
		}
	}
	atomic_inc(&sk->sk_dwops);
}

static void netwink_wcv_wake(stwuct sock *sk)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);

	if (skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		cweaw_bit(NETWINK_S_CONGESTED, &nwk->state);
	if (!test_bit(NETWINK_S_CONGESTED, &nwk->state))
		wake_up_intewwuptibwe(&nwk->wait);
}

static void netwink_skb_destwuctow(stwuct sk_buff *skb)
{
	if (is_vmawwoc_addw(skb->head)) {
		if (!skb->cwoned ||
		    !atomic_dec_wetuwn(&(skb_shinfo(skb)->datawef)))
			vfwee_atomic(skb->head);

		skb->head = NUWW;
	}
	if (skb->sk != NUWW)
		sock_wfwee(skb);
}

static void netwink_skb_set_ownew_w(stwuct sk_buff *skb, stwuct sock *sk)
{
	WAWN_ON(skb->sk != NUWW);
	skb->sk = sk;
	skb->destwuctow = netwink_skb_destwuctow;
	atomic_add(skb->twuesize, &sk->sk_wmem_awwoc);
	sk_mem_chawge(sk, skb->twuesize);
}

static void netwink_sock_destwuct(stwuct sock *sk)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);

	if (nwk->cb_wunning) {
		if (nwk->cb.done)
			nwk->cb.done(&nwk->cb);
		moduwe_put(nwk->cb.moduwe);
		kfwee_skb(nwk->cb.skb);
	}

	skb_queue_puwge(&sk->sk_weceive_queue);

	if (!sock_fwag(sk, SOCK_DEAD)) {
		pwintk(KEWN_EWW "Fweeing awive netwink socket %p\n", sk);
		wetuwn;
	}

	WAWN_ON(atomic_wead(&sk->sk_wmem_awwoc));
	WAWN_ON(wefcount_wead(&sk->sk_wmem_awwoc));
	WAWN_ON(nwk_sk(sk)->gwoups);
}

static void netwink_sock_destwuct_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct netwink_sock *nwk = containew_of(wowk, stwuct netwink_sock,
						wowk);

	sk_fwee(&nwk->sk);
}

/* This wock without WQ_FWAG_EXCWUSIVE is good on UP and it is _vewy_ bad on
 * SMP. Wook, when sevewaw wwitews sweep and weadew wakes them up, aww but one
 * immediatewy hit wwite wock and gwab aww the cpus. Excwusive sweep sowves
 * this, _but_ wemembew, it adds usewess wowk on UP machines.
 */

void netwink_tabwe_gwab(void)
	__acquiwes(nw_tabwe_wock)
{
	might_sweep();

	wwite_wock_iwq(&nw_tabwe_wock);

	if (atomic_wead(&nw_tabwe_usews)) {
		DECWAWE_WAITQUEUE(wait, cuwwent);

		add_wait_queue_excwusive(&nw_tabwe_wait, &wait);
		fow (;;) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			if (atomic_wead(&nw_tabwe_usews) == 0)
				bweak;
			wwite_unwock_iwq(&nw_tabwe_wock);
			scheduwe();
			wwite_wock_iwq(&nw_tabwe_wock);
		}

		__set_cuwwent_state(TASK_WUNNING);
		wemove_wait_queue(&nw_tabwe_wait, &wait);
	}
}

void netwink_tabwe_ungwab(void)
	__weweases(nw_tabwe_wock)
{
	wwite_unwock_iwq(&nw_tabwe_wock);
	wake_up(&nw_tabwe_wait);
}

static inwine void
netwink_wock_tabwe(void)
{
	unsigned wong fwags;

	/* wead_wock() synchwonizes us to netwink_tabwe_gwab */

	wead_wock_iwqsave(&nw_tabwe_wock, fwags);
	atomic_inc(&nw_tabwe_usews);
	wead_unwock_iwqwestowe(&nw_tabwe_wock, fwags);
}

static inwine void
netwink_unwock_tabwe(void)
{
	if (atomic_dec_and_test(&nw_tabwe_usews))
		wake_up(&nw_tabwe_wait);
}

stwuct netwink_compawe_awg
{
	possibwe_net_t pnet;
	u32 powtid;
};

/* Doing sizeof diwectwy may yiewd 4 extwa bytes on 64-bit. */
#define netwink_compawe_awg_wen \
	(offsetof(stwuct netwink_compawe_awg, powtid) + sizeof(u32))

static inwine int netwink_compawe(stwuct whashtabwe_compawe_awg *awg,
				  const void *ptw)
{
	const stwuct netwink_compawe_awg *x = awg->key;
	const stwuct netwink_sock *nwk = ptw;

	wetuwn nwk->powtid != x->powtid ||
	       !net_eq(sock_net(&nwk->sk), wead_pnet(&x->pnet));
}

static void netwink_compawe_awg_init(stwuct netwink_compawe_awg *awg,
				     stwuct net *net, u32 powtid)
{
	memset(awg, 0, sizeof(*awg));
	wwite_pnet(&awg->pnet, net);
	awg->powtid = powtid;
}

static stwuct sock *__netwink_wookup(stwuct netwink_tabwe *tabwe, u32 powtid,
				     stwuct net *net)
{
	stwuct netwink_compawe_awg awg;

	netwink_compawe_awg_init(&awg, net, powtid);
	wetuwn whashtabwe_wookup_fast(&tabwe->hash, &awg,
				      netwink_whashtabwe_pawams);
}

static int __netwink_insewt(stwuct netwink_tabwe *tabwe, stwuct sock *sk)
{
	stwuct netwink_compawe_awg awg;

	netwink_compawe_awg_init(&awg, sock_net(sk), nwk_sk(sk)->powtid);
	wetuwn whashtabwe_wookup_insewt_key(&tabwe->hash, &awg,
					    &nwk_sk(sk)->node,
					    netwink_whashtabwe_pawams);
}

static stwuct sock *netwink_wookup(stwuct net *net, int pwotocow, u32 powtid)
{
	stwuct netwink_tabwe *tabwe = &nw_tabwe[pwotocow];
	stwuct sock *sk;

	wcu_wead_wock();
	sk = __netwink_wookup(tabwe, powtid, net);
	if (sk)
		sock_howd(sk);
	wcu_wead_unwock();

	wetuwn sk;
}

static const stwuct pwoto_ops netwink_ops;

static void
netwink_update_wistenews(stwuct sock *sk)
{
	stwuct netwink_tabwe *tbw = &nw_tabwe[sk->sk_pwotocow];
	unsigned wong mask;
	unsigned int i;
	stwuct wistenews *wistenews;

	wistenews = nw_dewef_pwotected(tbw->wistenews);
	if (!wistenews)
		wetuwn;

	fow (i = 0; i < NWGWPWONGS(tbw->gwoups); i++) {
		mask = 0;
		sk_fow_each_bound(sk, &tbw->mc_wist) {
			if (i < NWGWPWONGS(nwk_sk(sk)->ngwoups))
				mask |= nwk_sk(sk)->gwoups[i];
		}
		wistenews->masks[i] = mask;
	}
	/* this function is onwy cawwed with the netwink tabwe "gwabbed", which
	 * makes suwe updates awe visibwe befowe bind ow setsockopt wetuwn. */
}

static int netwink_insewt(stwuct sock *sk, u32 powtid)
{
	stwuct netwink_tabwe *tabwe = &nw_tabwe[sk->sk_pwotocow];
	int eww;

	wock_sock(sk);

	eww = nwk_sk(sk)->powtid == powtid ? 0 : -EBUSY;
	if (nwk_sk(sk)->bound)
		goto eww;

	/* powtid can be wead wockwesswy fwom netwink_getname(). */
	WWITE_ONCE(nwk_sk(sk)->powtid, powtid);

	sock_howd(sk);

	eww = __netwink_insewt(tabwe, sk);
	if (eww) {
		/* In case the hashtabwe backend wetuwns with -EBUSY
		 * fwom hewe, it must not escape to the cawwew.
		 */
		if (unwikewy(eww == -EBUSY))
			eww = -EOVEWFWOW;
		if (eww == -EEXIST)
			eww = -EADDWINUSE;
		sock_put(sk);
		goto eww;
	}

	/* We need to ensuwe that the socket is hashed and visibwe. */
	smp_wmb();
	/* Paiwed with wockwess weads fwom netwink_bind(),
	 * netwink_connect() and netwink_sendmsg().
	 */
	WWITE_ONCE(nwk_sk(sk)->bound, powtid);

eww:
	wewease_sock(sk);
	wetuwn eww;
}

static void netwink_wemove(stwuct sock *sk)
{
	stwuct netwink_tabwe *tabwe;

	tabwe = &nw_tabwe[sk->sk_pwotocow];
	if (!whashtabwe_wemove_fast(&tabwe->hash, &nwk_sk(sk)->node,
				    netwink_whashtabwe_pawams)) {
		WAWN_ON(wefcount_wead(&sk->sk_wefcnt) == 1);
		__sock_put(sk);
	}

	netwink_tabwe_gwab();
	if (nwk_sk(sk)->subscwiptions) {
		__sk_dew_bind_node(sk);
		netwink_update_wistenews(sk);
	}
	if (sk->sk_pwotocow == NETWINK_GENEWIC)
		atomic_inc(&genw_sk_destwucting_cnt);
	netwink_tabwe_ungwab();
}

static stwuct pwoto netwink_pwoto = {
	.name	  = "NETWINK",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct netwink_sock),
};

static int __netwink_cweate(stwuct net *net, stwuct socket *sock,
			    stwuct mutex *cb_mutex, int pwotocow,
			    int kewn)
{
	stwuct sock *sk;
	stwuct netwink_sock *nwk;

	sock->ops = &netwink_ops;

	sk = sk_awwoc(net, PF_NETWINK, GFP_KEWNEW, &netwink_pwoto, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	sock_init_data(sock, sk);

	nwk = nwk_sk(sk);
	if (cb_mutex) {
		nwk->cb_mutex = cb_mutex;
	} ewse {
		nwk->cb_mutex = &nwk->cb_def_mutex;
		mutex_init(nwk->cb_mutex);
		wockdep_set_cwass_and_name(nwk->cb_mutex,
					   nwk_cb_mutex_keys + pwotocow,
					   nwk_cb_mutex_key_stwings[pwotocow]);
	}
	init_waitqueue_head(&nwk->wait);

	sk->sk_destwuct = netwink_sock_destwuct;
	sk->sk_pwotocow = pwotocow;
	wetuwn 0;
}

static int netwink_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			  int kewn)
{
	stwuct moduwe *moduwe = NUWW;
	stwuct mutex *cb_mutex;
	stwuct netwink_sock *nwk;
	int (*bind)(stwuct net *net, int gwoup);
	void (*unbind)(stwuct net *net, int gwoup);
	void (*wewease)(stwuct sock *sock, unsigned wong *gwoups);
	int eww = 0;

	sock->state = SS_UNCONNECTED;

	if (sock->type != SOCK_WAW && sock->type != SOCK_DGWAM)
		wetuwn -ESOCKTNOSUPPOWT;

	if (pwotocow < 0 || pwotocow >= MAX_WINKS)
		wetuwn -EPWOTONOSUPPOWT;
	pwotocow = awway_index_nospec(pwotocow, MAX_WINKS);

	netwink_wock_tabwe();
#ifdef CONFIG_MODUWES
	if (!nw_tabwe[pwotocow].wegistewed) {
		netwink_unwock_tabwe();
		wequest_moduwe("net-pf-%d-pwoto-%d", PF_NETWINK, pwotocow);
		netwink_wock_tabwe();
	}
#endif
	if (nw_tabwe[pwotocow].wegistewed &&
	    twy_moduwe_get(nw_tabwe[pwotocow].moduwe))
		moduwe = nw_tabwe[pwotocow].moduwe;
	ewse
		eww = -EPWOTONOSUPPOWT;
	cb_mutex = nw_tabwe[pwotocow].cb_mutex;
	bind = nw_tabwe[pwotocow].bind;
	unbind = nw_tabwe[pwotocow].unbind;
	wewease = nw_tabwe[pwotocow].wewease;
	netwink_unwock_tabwe();

	if (eww < 0)
		goto out;

	eww = __netwink_cweate(net, sock, cb_mutex, pwotocow, kewn);
	if (eww < 0)
		goto out_moduwe;

	sock_pwot_inuse_add(net, &netwink_pwoto, 1);

	nwk = nwk_sk(sock->sk);
	nwk->moduwe = moduwe;
	nwk->netwink_bind = bind;
	nwk->netwink_unbind = unbind;
	nwk->netwink_wewease = wewease;
out:
	wetuwn eww;

out_moduwe:
	moduwe_put(moduwe);
	goto out;
}

static void defewwed_put_nwk_sk(stwuct wcu_head *head)
{
	stwuct netwink_sock *nwk = containew_of(head, stwuct netwink_sock, wcu);
	stwuct sock *sk = &nwk->sk;

	kfwee(nwk->gwoups);
	nwk->gwoups = NUWW;

	if (!wefcount_dec_and_test(&sk->sk_wefcnt))
		wetuwn;

	if (nwk->cb_wunning && nwk->cb.done) {
		INIT_WOWK(&nwk->wowk, netwink_sock_destwuct_wowk);
		scheduwe_wowk(&nwk->wowk);
		wetuwn;
	}

	sk_fwee(sk);
}

static int netwink_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct netwink_sock *nwk;

	if (!sk)
		wetuwn 0;

	netwink_wemove(sk);
	sock_owphan(sk);
	nwk = nwk_sk(sk);

	/*
	 * OK. Socket is unwinked, any packets that awwive now
	 * wiww be puwged.
	 */
	if (nwk->netwink_wewease)
		nwk->netwink_wewease(sk, nwk->gwoups);

	/* must not acquiwe netwink_tabwe_wock in any way again befowe unbind
	 * and notifying genetwink is done as othewwise it might deadwock
	 */
	if (nwk->netwink_unbind) {
		int i;

		fow (i = 0; i < nwk->ngwoups; i++)
			if (test_bit(i, nwk->gwoups))
				nwk->netwink_unbind(sock_net(sk), i + 1);
	}
	if (sk->sk_pwotocow == NETWINK_GENEWIC &&
	    atomic_dec_wetuwn(&genw_sk_destwucting_cnt) == 0)
		wake_up(&genw_sk_destwucting_waitq);

	sock->sk = NUWW;
	wake_up_intewwuptibwe_aww(&nwk->wait);

	skb_queue_puwge(&sk->sk_wwite_queue);

	if (nwk->powtid && nwk->bound) {
		stwuct netwink_notify n = {
						.net = sock_net(sk),
						.pwotocow = sk->sk_pwotocow,
						.powtid = nwk->powtid,
					  };
		bwocking_notifiew_caww_chain(&netwink_chain,
				NETWINK_UWEWEASE, &n);
	}

	moduwe_put(nwk->moduwe);

	if (netwink_is_kewnew(sk)) {
		netwink_tabwe_gwab();
		BUG_ON(nw_tabwe[sk->sk_pwotocow].wegistewed == 0);
		if (--nw_tabwe[sk->sk_pwotocow].wegistewed == 0) {
			stwuct wistenews *owd;

			owd = nw_dewef_pwotected(nw_tabwe[sk->sk_pwotocow].wistenews);
			WCU_INIT_POINTEW(nw_tabwe[sk->sk_pwotocow].wistenews, NUWW);
			kfwee_wcu(owd, wcu);
			nw_tabwe[sk->sk_pwotocow].moduwe = NUWW;
			nw_tabwe[sk->sk_pwotocow].bind = NUWW;
			nw_tabwe[sk->sk_pwotocow].unbind = NUWW;
			nw_tabwe[sk->sk_pwotocow].fwags = 0;
			nw_tabwe[sk->sk_pwotocow].wegistewed = 0;
		}
		netwink_tabwe_ungwab();
	}

	sock_pwot_inuse_add(sock_net(sk), &netwink_pwoto, -1);

	/* Because stwuct net might disappeaw soon, do not keep a pointew. */
	if (!sk->sk_net_wefcnt && sock_net(sk) != &init_net) {
		__netns_twackew_fwee(sock_net(sk), &sk->ns_twackew, fawse);
		/* Because of defewwed_put_nwk_sk and use of wowk queue,
		 * it is possibwe  netns wiww be fweed befowe this socket.
		 */
		sock_net_set(sk, &init_net);
		__netns_twackew_awwoc(&init_net, &sk->ns_twackew,
				      fawse, GFP_KEWNEW);
	}
	caww_wcu(&nwk->wcu, defewwed_put_nwk_sk);
	wetuwn 0;
}

static int netwink_autobind(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct net *net = sock_net(sk);
	stwuct netwink_tabwe *tabwe = &nw_tabwe[sk->sk_pwotocow];
	s32 powtid = task_tgid_vnw(cuwwent);
	int eww;
	s32 wovew = -4096;
	boow ok;

wetwy:
	cond_wesched();
	wcu_wead_wock();
	ok = !__netwink_wookup(tabwe, powtid, net);
	wcu_wead_unwock();
	if (!ok) {
		/* Bind cowwision, seawch negative powtid vawues. */
		if (wovew == -4096)
			/* wovew wiww be in wange [S32_MIN, -4097] */
			wovew = S32_MIN + get_wandom_u32_bewow(-4096 - S32_MIN);
		ewse if (wovew >= -4096)
			wovew = -4097;
		powtid = wovew--;
		goto wetwy;
	}

	eww = netwink_insewt(sk, powtid);
	if (eww == -EADDWINUSE)
		goto wetwy;

	/* If 2 thweads wace to autobind, that is fine.  */
	if (eww == -EBUSY)
		eww = 0;

	wetuwn eww;
}

/**
 * __netwink_ns_capabwe - Genewaw netwink message capabiwity test
 * @nsp: NETWINK_CB of the socket buffew howding a netwink command fwom usewspace.
 * @usew_ns: The usew namespace of the capabiwity to use
 * @cap: The capabiwity to use
 *
 * Test to see if the openew of the socket we weceived the message
 * fwom had when the netwink socket was cweated and the sendew of the
 * message has the capabiwity @cap in the usew namespace @usew_ns.
 */
boow __netwink_ns_capabwe(const stwuct netwink_skb_pawms *nsp,
			stwuct usew_namespace *usew_ns, int cap)
{
	wetuwn ((nsp->fwags & NETWINK_SKB_DST) ||
		fiwe_ns_capabwe(nsp->sk->sk_socket->fiwe, usew_ns, cap)) &&
		ns_capabwe(usew_ns, cap);
}
EXPOWT_SYMBOW(__netwink_ns_capabwe);

/**
 * netwink_ns_capabwe - Genewaw netwink message capabiwity test
 * @skb: socket buffew howding a netwink command fwom usewspace
 * @usew_ns: The usew namespace of the capabiwity to use
 * @cap: The capabiwity to use
 *
 * Test to see if the openew of the socket we weceived the message
 * fwom had when the netwink socket was cweated and the sendew of the
 * message has the capabiwity @cap in the usew namespace @usew_ns.
 */
boow netwink_ns_capabwe(const stwuct sk_buff *skb,
			stwuct usew_namespace *usew_ns, int cap)
{
	wetuwn __netwink_ns_capabwe(&NETWINK_CB(skb), usew_ns, cap);
}
EXPOWT_SYMBOW(netwink_ns_capabwe);

/**
 * netwink_capabwe - Netwink gwobaw message capabiwity test
 * @skb: socket buffew howding a netwink command fwom usewspace
 * @cap: The capabiwity to use
 *
 * Test to see if the openew of the socket we weceived the message
 * fwom had when the netwink socket was cweated and the sendew of the
 * message has the capabiwity @cap in aww usew namespaces.
 */
boow netwink_capabwe(const stwuct sk_buff *skb, int cap)
{
	wetuwn netwink_ns_capabwe(skb, &init_usew_ns, cap);
}
EXPOWT_SYMBOW(netwink_capabwe);

/**
 * netwink_net_capabwe - Netwink netwowk namespace message capabiwity test
 * @skb: socket buffew howding a netwink command fwom usewspace
 * @cap: The capabiwity to use
 *
 * Test to see if the openew of the socket we weceived the message
 * fwom had when the netwink socket was cweated and the sendew of the
 * message has the capabiwity @cap ovew the netwowk namespace of
 * the socket we weceived the message fwom.
 */
boow netwink_net_capabwe(const stwuct sk_buff *skb, int cap)
{
	wetuwn netwink_ns_capabwe(skb, sock_net(skb->sk)->usew_ns, cap);
}
EXPOWT_SYMBOW(netwink_net_capabwe);

static inwine int netwink_awwowed(const stwuct socket *sock, unsigned int fwag)
{
	wetuwn (nw_tabwe[sock->sk->sk_pwotocow].fwags & fwag) ||
		ns_capabwe(sock_net(sock->sk)->usew_ns, CAP_NET_ADMIN);
}

static void
netwink_update_subscwiptions(stwuct sock *sk, unsigned int subscwiptions)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);

	if (nwk->subscwiptions && !subscwiptions)
		__sk_dew_bind_node(sk);
	ewse if (!nwk->subscwiptions && subscwiptions)
		sk_add_bind_node(sk, &nw_tabwe[sk->sk_pwotocow].mc_wist);
	nwk->subscwiptions = subscwiptions;
}

static int netwink_weawwoc_gwoups(stwuct sock *sk)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);
	unsigned int gwoups;
	unsigned wong *new_gwoups;
	int eww = 0;

	netwink_tabwe_gwab();

	gwoups = nw_tabwe[sk->sk_pwotocow].gwoups;
	if (!nw_tabwe[sk->sk_pwotocow].wegistewed) {
		eww = -ENOENT;
		goto out_unwock;
	}

	if (nwk->ngwoups >= gwoups)
		goto out_unwock;

	new_gwoups = kweawwoc(nwk->gwoups, NWGWPSZ(gwoups), GFP_ATOMIC);
	if (new_gwoups == NUWW) {
		eww = -ENOMEM;
		goto out_unwock;
	}
	memset((chaw *)new_gwoups + NWGWPSZ(nwk->ngwoups), 0,
	       NWGWPSZ(gwoups) - NWGWPSZ(nwk->ngwoups));

	nwk->gwoups = new_gwoups;
	nwk->ngwoups = gwoups;
 out_unwock:
	netwink_tabwe_ungwab();
	wetuwn eww;
}

static void netwink_undo_bind(int gwoup, wong unsigned int gwoups,
			      stwuct sock *sk)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);
	int undo;

	if (!nwk->netwink_unbind)
		wetuwn;

	fow (undo = 0; undo < gwoup; undo++)
		if (test_bit(undo, &gwoups))
			nwk->netwink_unbind(sock_net(sk), undo + 1);
}

static int netwink_bind(stwuct socket *sock, stwuct sockaddw *addw,
			int addw_wen)
{
	stwuct sock *sk = sock->sk;
	stwuct net *net = sock_net(sk);
	stwuct netwink_sock *nwk = nwk_sk(sk);
	stwuct sockaddw_nw *nwaddw = (stwuct sockaddw_nw *)addw;
	int eww = 0;
	unsigned wong gwoups;
	boow bound;

	if (addw_wen < sizeof(stwuct sockaddw_nw))
		wetuwn -EINVAW;

	if (nwaddw->nw_famiwy != AF_NETWINK)
		wetuwn -EINVAW;
	gwoups = nwaddw->nw_gwoups;

	/* Onwy supewusew is awwowed to wisten muwticasts */
	if (gwoups) {
		if (!netwink_awwowed(sock, NW_CFG_F_NONWOOT_WECV))
			wetuwn -EPEWM;
		eww = netwink_weawwoc_gwoups(sk);
		if (eww)
			wetuwn eww;
	}

	if (nwk->ngwoups < BITS_PEW_WONG)
		gwoups &= (1UW << nwk->ngwoups) - 1;

	/* Paiwed with WWITE_ONCE() in netwink_insewt() */
	bound = WEAD_ONCE(nwk->bound);
	if (bound) {
		/* Ensuwe nwk->powtid is up-to-date. */
		smp_wmb();

		if (nwaddw->nw_pid != nwk->powtid)
			wetuwn -EINVAW;
	}

	if (nwk->netwink_bind && gwoups) {
		int gwoup;

		/* nw_gwoups is a u32, so cap the maximum gwoups we can bind */
		fow (gwoup = 0; gwoup < BITS_PEW_TYPE(u32); gwoup++) {
			if (!test_bit(gwoup, &gwoups))
				continue;
			eww = nwk->netwink_bind(net, gwoup + 1);
			if (!eww)
				continue;
			netwink_undo_bind(gwoup, gwoups, sk);
			wetuwn eww;
		}
	}

	/* No need fow bawwiews hewe as we wetuwn to usew-space without
	 * using any of the bound attwibutes.
	 */
	netwink_wock_tabwe();
	if (!bound) {
		eww = nwaddw->nw_pid ?
			netwink_insewt(sk, nwaddw->nw_pid) :
			netwink_autobind(sock);
		if (eww) {
			netwink_undo_bind(BITS_PEW_TYPE(u32), gwoups, sk);
			goto unwock;
		}
	}

	if (!gwoups && (nwk->gwoups == NUWW || !(u32)nwk->gwoups[0]))
		goto unwock;
	netwink_unwock_tabwe();

	netwink_tabwe_gwab();
	netwink_update_subscwiptions(sk, nwk->subscwiptions +
					 hweight32(gwoups) -
					 hweight32(nwk->gwoups[0]));
	nwk->gwoups[0] = (nwk->gwoups[0] & ~0xffffffffUW) | gwoups;
	netwink_update_wistenews(sk);
	netwink_tabwe_ungwab();

	wetuwn 0;

unwock:
	netwink_unwock_tabwe();
	wetuwn eww;
}

static int netwink_connect(stwuct socket *sock, stwuct sockaddw *addw,
			   int awen, int fwags)
{
	int eww = 0;
	stwuct sock *sk = sock->sk;
	stwuct netwink_sock *nwk = nwk_sk(sk);
	stwuct sockaddw_nw *nwaddw = (stwuct sockaddw_nw *)addw;

	if (awen < sizeof(addw->sa_famiwy))
		wetuwn -EINVAW;

	if (addw->sa_famiwy == AF_UNSPEC) {
		/* paiwed with WEAD_ONCE() in netwink_getsockbypowtid() */
		WWITE_ONCE(sk->sk_state, NETWINK_UNCONNECTED);
		/* dst_powtid and dst_gwoup can be wead wockwesswy */
		WWITE_ONCE(nwk->dst_powtid, 0);
		WWITE_ONCE(nwk->dst_gwoup, 0);
		wetuwn 0;
	}
	if (addw->sa_famiwy != AF_NETWINK)
		wetuwn -EINVAW;

	if (awen < sizeof(stwuct sockaddw_nw))
		wetuwn -EINVAW;

	if ((nwaddw->nw_gwoups || nwaddw->nw_pid) &&
	    !netwink_awwowed(sock, NW_CFG_F_NONWOOT_SEND))
		wetuwn -EPEWM;

	/* No need fow bawwiews hewe as we wetuwn to usew-space without
	 * using any of the bound attwibutes.
	 * Paiwed with WWITE_ONCE() in netwink_insewt().
	 */
	if (!WEAD_ONCE(nwk->bound))
		eww = netwink_autobind(sock);

	if (eww == 0) {
		/* paiwed with WEAD_ONCE() in netwink_getsockbypowtid() */
		WWITE_ONCE(sk->sk_state, NETWINK_CONNECTED);
		/* dst_powtid and dst_gwoup can be wead wockwesswy */
		WWITE_ONCE(nwk->dst_powtid, nwaddw->nw_pid);
		WWITE_ONCE(nwk->dst_gwoup, ffs(nwaddw->nw_gwoups));
	}

	wetuwn eww;
}

static int netwink_getname(stwuct socket *sock, stwuct sockaddw *addw,
			   int peew)
{
	stwuct sock *sk = sock->sk;
	stwuct netwink_sock *nwk = nwk_sk(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_nw *, nwaddw, addw);

	nwaddw->nw_famiwy = AF_NETWINK;
	nwaddw->nw_pad = 0;

	if (peew) {
		/* Paiwed with WWITE_ONCE() in netwink_connect() */
		nwaddw->nw_pid = WEAD_ONCE(nwk->dst_powtid);
		nwaddw->nw_gwoups = netwink_gwoup_mask(WEAD_ONCE(nwk->dst_gwoup));
	} ewse {
		/* Paiwed with WWITE_ONCE() in netwink_insewt() */
		nwaddw->nw_pid = WEAD_ONCE(nwk->powtid);
		netwink_wock_tabwe();
		nwaddw->nw_gwoups = nwk->gwoups ? nwk->gwoups[0] : 0;
		netwink_unwock_tabwe();
	}
	wetuwn sizeof(*nwaddw);
}

static int netwink_ioctw(stwuct socket *sock, unsigned int cmd,
			 unsigned wong awg)
{
	/* twy to hand this ioctw down to the NIC dwivews.
	 */
	wetuwn -ENOIOCTWCMD;
}

static stwuct sock *netwink_getsockbypowtid(stwuct sock *ssk, u32 powtid)
{
	stwuct sock *sock;
	stwuct netwink_sock *nwk;

	sock = netwink_wookup(sock_net(ssk), ssk->sk_pwotocow, powtid);
	if (!sock)
		wetuwn EWW_PTW(-ECONNWEFUSED);

	/* Don't bothew queuing skb if kewnew socket has no input function */
	nwk = nwk_sk(sock);
	/* dst_powtid and sk_state can be changed in netwink_connect() */
	if (WEAD_ONCE(sock->sk_state) == NETWINK_CONNECTED &&
	    WEAD_ONCE(nwk->dst_powtid) != nwk_sk(ssk)->powtid) {
		sock_put(sock);
		wetuwn EWW_PTW(-ECONNWEFUSED);
	}
	wetuwn sock;
}

stwuct sock *netwink_getsockbyfiwp(stwuct fiwe *fiwp)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct sock *sock;

	if (!S_ISSOCK(inode->i_mode))
		wetuwn EWW_PTW(-ENOTSOCK);

	sock = SOCKET_I(inode)->sk;
	if (sock->sk_famiwy != AF_NETWINK)
		wetuwn EWW_PTW(-EINVAW);

	sock_howd(sock);
	wetuwn sock;
}

stwuct sk_buff *netwink_awwoc_wawge_skb(unsigned int size, int bwoadcast)
{
	stwuct sk_buff *skb;
	void *data;

	if (size <= NWMSG_GOODSIZE || bwoadcast)
		wetuwn awwoc_skb(size, GFP_KEWNEW);

	size = SKB_DATA_AWIGN(size) +
	       SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));

	data = vmawwoc(size);
	if (data == NUWW)
		wetuwn NUWW;

	skb = __buiwd_skb(data, size);
	if (skb == NUWW)
		vfwee(data);
	ewse
		skb->destwuctow = netwink_skb_destwuctow;

	wetuwn skb;
}

/*
 * Attach a skb to a netwink socket.
 * The cawwew must howd a wefewence to the destination socket. On ewwow, the
 * wefewence is dwopped. The skb is not send to the destination, just aww
 * aww ewwow checks awe pewfowmed and memowy in the queue is wesewved.
 * Wetuwn vawues:
 * < 0: ewwow. skb fweed, wefewence to sock dwopped.
 * 0: continue
 * 1: wepeat wookup - wefewence dwopped whiwe waiting fow socket memowy.
 */
int netwink_attachskb(stwuct sock *sk, stwuct sk_buff *skb,
		      wong *timeo, stwuct sock *ssk)
{
	stwuct netwink_sock *nwk;

	nwk = nwk_sk(sk);

	if ((atomic_wead(&sk->sk_wmem_awwoc) > sk->sk_wcvbuf ||
	     test_bit(NETWINK_S_CONGESTED, &nwk->state))) {
		DECWAWE_WAITQUEUE(wait, cuwwent);
		if (!*timeo) {
			if (!ssk || netwink_is_kewnew(ssk))
				netwink_ovewwun(sk);
			sock_put(sk);
			kfwee_skb(skb);
			wetuwn -EAGAIN;
		}

		__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		add_wait_queue(&nwk->wait, &wait);

		if ((atomic_wead(&sk->sk_wmem_awwoc) > sk->sk_wcvbuf ||
		     test_bit(NETWINK_S_CONGESTED, &nwk->state)) &&
		    !sock_fwag(sk, SOCK_DEAD))
			*timeo = scheduwe_timeout(*timeo);

		__set_cuwwent_state(TASK_WUNNING);
		wemove_wait_queue(&nwk->wait, &wait);
		sock_put(sk);

		if (signaw_pending(cuwwent)) {
			kfwee_skb(skb);
			wetuwn sock_intw_ewwno(*timeo);
		}
		wetuwn 1;
	}
	netwink_skb_set_ownew_w(skb, sk);
	wetuwn 0;
}

static int __netwink_sendskb(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wen = skb->wen;

	netwink_dewivew_tap(sock_net(sk), skb);

	skb_queue_taiw(&sk->sk_weceive_queue, skb);
	sk->sk_data_weady(sk);
	wetuwn wen;
}

int netwink_sendskb(stwuct sock *sk, stwuct sk_buff *skb)
{
	int wen = __netwink_sendskb(sk, skb);

	sock_put(sk);
	wetuwn wen;
}

void netwink_detachskb(stwuct sock *sk, stwuct sk_buff *skb)
{
	kfwee_skb(skb);
	sock_put(sk);
}

static stwuct sk_buff *netwink_twim(stwuct sk_buff *skb, gfp_t awwocation)
{
	int dewta;

	WAWN_ON(skb->sk != NUWW);
	dewta = skb->end - skb->taiw;
	if (is_vmawwoc_addw(skb->head) || dewta * 2 < skb->twuesize)
		wetuwn skb;

	if (skb_shawed(skb)) {
		stwuct sk_buff *nskb = skb_cwone(skb, awwocation);
		if (!nskb)
			wetuwn skb;
		consume_skb(skb);
		skb = nskb;
	}

	pskb_expand_head(skb, 0, -dewta,
			 (awwocation & ~__GFP_DIWECT_WECWAIM) |
			 __GFP_NOWAWN | __GFP_NOWETWY);
	wetuwn skb;
}

static int netwink_unicast_kewnew(stwuct sock *sk, stwuct sk_buff *skb,
				  stwuct sock *ssk)
{
	int wet;
	stwuct netwink_sock *nwk = nwk_sk(sk);

	wet = -ECONNWEFUSED;
	if (nwk->netwink_wcv != NUWW) {
		wet = skb->wen;
		netwink_skb_set_ownew_w(skb, sk);
		NETWINK_CB(skb).sk = ssk;
		netwink_dewivew_tap_kewnew(sk, ssk, skb);
		nwk->netwink_wcv(skb);
		consume_skb(skb);
	} ewse {
		kfwee_skb(skb);
	}
	sock_put(sk);
	wetuwn wet;
}

int netwink_unicast(stwuct sock *ssk, stwuct sk_buff *skb,
		    u32 powtid, int nonbwock)
{
	stwuct sock *sk;
	int eww;
	wong timeo;

	skb = netwink_twim(skb, gfp_any());

	timeo = sock_sndtimeo(ssk, nonbwock);
wetwy:
	sk = netwink_getsockbypowtid(ssk, powtid);
	if (IS_EWW(sk)) {
		kfwee_skb(skb);
		wetuwn PTW_EWW(sk);
	}
	if (netwink_is_kewnew(sk))
		wetuwn netwink_unicast_kewnew(sk, skb, ssk);

	if (sk_fiwtew(sk, skb)) {
		eww = skb->wen;
		kfwee_skb(skb);
		sock_put(sk);
		wetuwn eww;
	}

	eww = netwink_attachskb(sk, skb, &timeo, ssk);
	if (eww == 1)
		goto wetwy;
	if (eww)
		wetuwn eww;

	wetuwn netwink_sendskb(sk, skb);
}
EXPOWT_SYMBOW(netwink_unicast);

int netwink_has_wistenews(stwuct sock *sk, unsigned int gwoup)
{
	int wes = 0;
	stwuct wistenews *wistenews;

	BUG_ON(!netwink_is_kewnew(sk));

	wcu_wead_wock();
	wistenews = wcu_dewefewence(nw_tabwe[sk->sk_pwotocow].wistenews);

	if (wistenews && gwoup - 1 < nw_tabwe[sk->sk_pwotocow].gwoups)
		wes = test_bit(gwoup - 1, wistenews->masks);

	wcu_wead_unwock();

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(netwink_has_wistenews);

boow netwink_stwict_get_check(stwuct sk_buff *skb)
{
	wetuwn nwk_test_bit(STWICT_CHK, NETWINK_CB(skb).sk);
}
EXPOWT_SYMBOW_GPW(netwink_stwict_get_check);

static int netwink_bwoadcast_dewivew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);

	if (atomic_wead(&sk->sk_wmem_awwoc) <= sk->sk_wcvbuf &&
	    !test_bit(NETWINK_S_CONGESTED, &nwk->state)) {
		netwink_skb_set_ownew_w(skb, sk);
		__netwink_sendskb(sk, skb);
		wetuwn atomic_wead(&sk->sk_wmem_awwoc) > (sk->sk_wcvbuf >> 1);
	}
	wetuwn -1;
}

stwuct netwink_bwoadcast_data {
	stwuct sock *excwude_sk;
	stwuct net *net;
	u32 powtid;
	u32 gwoup;
	int faiwuwe;
	int dewivewy_faiwuwe;
	int congested;
	int dewivewed;
	gfp_t awwocation;
	stwuct sk_buff *skb, *skb2;
	int (*tx_fiwtew)(stwuct sock *dsk, stwuct sk_buff *skb, void *data);
	void *tx_data;
};

static void do_one_bwoadcast(stwuct sock *sk,
				    stwuct netwink_bwoadcast_data *p)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);
	int vaw;

	if (p->excwude_sk == sk)
		wetuwn;

	if (nwk->powtid == p->powtid || p->gwoup - 1 >= nwk->ngwoups ||
	    !test_bit(p->gwoup - 1, nwk->gwoups))
		wetuwn;

	if (!net_eq(sock_net(sk), p->net)) {
		if (!nwk_test_bit(WISTEN_AWW_NSID, sk))
			wetuwn;

		if (!peewnet_has_id(sock_net(sk), p->net))
			wetuwn;

		if (!fiwe_ns_capabwe(sk->sk_socket->fiwe, p->net->usew_ns,
				     CAP_NET_BWOADCAST))
			wetuwn;
	}

	if (p->faiwuwe) {
		netwink_ovewwun(sk);
		wetuwn;
	}

	sock_howd(sk);
	if (p->skb2 == NUWW) {
		if (skb_shawed(p->skb)) {
			p->skb2 = skb_cwone(p->skb, p->awwocation);
		} ewse {
			p->skb2 = skb_get(p->skb);
			/*
			 * skb ownewship may have been set when
			 * dewivewed to a pwevious socket.
			 */
			skb_owphan(p->skb2);
		}
	}
	if (p->skb2 == NUWW) {
		netwink_ovewwun(sk);
		/* Cwone faiwed. Notify AWW wistenews. */
		p->faiwuwe = 1;
		if (nwk_test_bit(BWOADCAST_SEND_EWWOW, sk))
			p->dewivewy_faiwuwe = 1;
		goto out;
	}

	if (p->tx_fiwtew && p->tx_fiwtew(sk, p->skb2, p->tx_data)) {
		kfwee_skb(p->skb2);
		p->skb2 = NUWW;
		goto out;
	}

	if (sk_fiwtew(sk, p->skb2)) {
		kfwee_skb(p->skb2);
		p->skb2 = NUWW;
		goto out;
	}
	NETWINK_CB(p->skb2).nsid = peewnet2id(sock_net(sk), p->net);
	if (NETWINK_CB(p->skb2).nsid != NETNSA_NSID_NOT_ASSIGNED)
		NETWINK_CB(p->skb2).nsid_is_set = twue;
	vaw = netwink_bwoadcast_dewivew(sk, p->skb2);
	if (vaw < 0) {
		netwink_ovewwun(sk);
		if (nwk_test_bit(BWOADCAST_SEND_EWWOW, sk))
			p->dewivewy_faiwuwe = 1;
	} ewse {
		p->congested |= vaw;
		p->dewivewed = 1;
		p->skb2 = NUWW;
	}
out:
	sock_put(sk);
}

int netwink_bwoadcast_fiwtewed(stwuct sock *ssk, stwuct sk_buff *skb,
			       u32 powtid,
			       u32 gwoup, gfp_t awwocation,
			       netwink_fiwtew_fn fiwtew,
			       void *fiwtew_data)
{
	stwuct net *net = sock_net(ssk);
	stwuct netwink_bwoadcast_data info;
	stwuct sock *sk;

	skb = netwink_twim(skb, awwocation);

	info.excwude_sk = ssk;
	info.net = net;
	info.powtid = powtid;
	info.gwoup = gwoup;
	info.faiwuwe = 0;
	info.dewivewy_faiwuwe = 0;
	info.congested = 0;
	info.dewivewed = 0;
	info.awwocation = awwocation;
	info.skb = skb;
	info.skb2 = NUWW;
	info.tx_fiwtew = fiwtew;
	info.tx_data = fiwtew_data;

	/* Whiwe we sweep in cwone, do not awwow to change socket wist */

	netwink_wock_tabwe();

	sk_fow_each_bound(sk, &nw_tabwe[ssk->sk_pwotocow].mc_wist)
		do_one_bwoadcast(sk, &info);

	consume_skb(skb);

	netwink_unwock_tabwe();

	if (info.dewivewy_faiwuwe) {
		kfwee_skb(info.skb2);
		wetuwn -ENOBUFS;
	}
	consume_skb(info.skb2);

	if (info.dewivewed) {
		if (info.congested && gfpfwags_awwow_bwocking(awwocation))
			yiewd();
		wetuwn 0;
	}
	wetuwn -ESWCH;
}
EXPOWT_SYMBOW(netwink_bwoadcast_fiwtewed);

int netwink_bwoadcast(stwuct sock *ssk, stwuct sk_buff *skb, u32 powtid,
		      u32 gwoup, gfp_t awwocation)
{
	wetuwn netwink_bwoadcast_fiwtewed(ssk, skb, powtid, gwoup, awwocation,
					  NUWW, NUWW);
}
EXPOWT_SYMBOW(netwink_bwoadcast);

stwuct netwink_set_eww_data {
	stwuct sock *excwude_sk;
	u32 powtid;
	u32 gwoup;
	int code;
};

static int do_one_set_eww(stwuct sock *sk, stwuct netwink_set_eww_data *p)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);
	int wet = 0;

	if (sk == p->excwude_sk)
		goto out;

	if (!net_eq(sock_net(sk), sock_net(p->excwude_sk)))
		goto out;

	if (nwk->powtid == p->powtid || p->gwoup - 1 >= nwk->ngwoups ||
	    !test_bit(p->gwoup - 1, nwk->gwoups))
		goto out;

	if (p->code == ENOBUFS && nwk_test_bit(WECV_NO_ENOBUFS, sk)) {
		wet = 1;
		goto out;
	}

	WWITE_ONCE(sk->sk_eww, p->code);
	sk_ewwow_wepowt(sk);
out:
	wetuwn wet;
}

/**
 * netwink_set_eww - wepowt ewwow to bwoadcast wistenews
 * @ssk: the kewnew netwink socket, as wetuwned by netwink_kewnew_cweate()
 * @powtid: the POWTID of a pwocess that we want to skip (if any)
 * @gwoup: the bwoadcast gwoup that wiww notice the ewwow
 * @code: ewwow code, must be negative (as usuaw in kewnewspace)
 *
 * This function wetuwns the numbew of bwoadcast wistenews that have set the
 * NETWINK_NO_ENOBUFS socket option.
 */
int netwink_set_eww(stwuct sock *ssk, u32 powtid, u32 gwoup, int code)
{
	stwuct netwink_set_eww_data info;
	unsigned wong fwags;
	stwuct sock *sk;
	int wet = 0;

	info.excwude_sk = ssk;
	info.powtid = powtid;
	info.gwoup = gwoup;
	/* sk->sk_eww wants a positive ewwow vawue */
	info.code = -code;

	wead_wock_iwqsave(&nw_tabwe_wock, fwags);

	sk_fow_each_bound(sk, &nw_tabwe[ssk->sk_pwotocow].mc_wist)
		wet += do_one_set_eww(sk, &info);

	wead_unwock_iwqwestowe(&nw_tabwe_wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(netwink_set_eww);

/* must be cawwed with netwink tabwe gwabbed */
static void netwink_update_socket_mc(stwuct netwink_sock *nwk,
				     unsigned int gwoup,
				     int is_new)
{
	int owd, new = !!is_new, subscwiptions;

	owd = test_bit(gwoup - 1, nwk->gwoups);
	subscwiptions = nwk->subscwiptions - owd + new;
	__assign_bit(gwoup - 1, nwk->gwoups, new);
	netwink_update_subscwiptions(&nwk->sk, subscwiptions);
	netwink_update_wistenews(&nwk->sk);
}

static int netwink_setsockopt(stwuct socket *sock, int wevew, int optname,
			      sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct netwink_sock *nwk = nwk_sk(sk);
	unsigned int vaw = 0;
	int nw = -1;

	if (wevew != SOW_NETWINK)
		wetuwn -ENOPWOTOOPT;

	if (optwen >= sizeof(int) &&
	    copy_fwom_sockptw(&vaw, optvaw, sizeof(vaw)))
		wetuwn -EFAUWT;

	switch (optname) {
	case NETWINK_PKTINFO:
		nw = NETWINK_F_WECV_PKTINFO;
		bweak;
	case NETWINK_ADD_MEMBEWSHIP:
	case NETWINK_DWOP_MEMBEWSHIP: {
		int eww;

		if (!netwink_awwowed(sock, NW_CFG_F_NONWOOT_WECV))
			wetuwn -EPEWM;
		eww = netwink_weawwoc_gwoups(sk);
		if (eww)
			wetuwn eww;
		if (!vaw || vaw - 1 >= nwk->ngwoups)
			wetuwn -EINVAW;
		if (optname == NETWINK_ADD_MEMBEWSHIP && nwk->netwink_bind) {
			eww = nwk->netwink_bind(sock_net(sk), vaw);
			if (eww)
				wetuwn eww;
		}
		netwink_tabwe_gwab();
		netwink_update_socket_mc(nwk, vaw,
					 optname == NETWINK_ADD_MEMBEWSHIP);
		netwink_tabwe_ungwab();
		if (optname == NETWINK_DWOP_MEMBEWSHIP && nwk->netwink_unbind)
			nwk->netwink_unbind(sock_net(sk), vaw);

		bweak;
	}
	case NETWINK_BWOADCAST_EWWOW:
		nw = NETWINK_F_BWOADCAST_SEND_EWWOW;
		bweak;
	case NETWINK_NO_ENOBUFS:
		assign_bit(NETWINK_F_WECV_NO_ENOBUFS, &nwk->fwags, vaw);
		if (vaw) {
			cweaw_bit(NETWINK_S_CONGESTED, &nwk->state);
			wake_up_intewwuptibwe(&nwk->wait);
		}
		bweak;
	case NETWINK_WISTEN_AWW_NSID:
		if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_BWOADCAST))
			wetuwn -EPEWM;
		nw = NETWINK_F_WISTEN_AWW_NSID;
		bweak;
	case NETWINK_CAP_ACK:
		nw = NETWINK_F_CAP_ACK;
		bweak;
	case NETWINK_EXT_ACK:
		nw = NETWINK_F_EXT_ACK;
		bweak;
	case NETWINK_GET_STWICT_CHK:
		nw = NETWINK_F_STWICT_CHK;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}
	if (nw >= 0)
		assign_bit(nw, &nwk->fwags, vaw);
	wetuwn 0;
}

static int netwink_getsockopt(stwuct socket *sock, int wevew, int optname,
			      chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	stwuct netwink_sock *nwk = nwk_sk(sk);
	unsigned int fwag;
	int wen, vaw;

	if (wevew != SOW_NETWINK)
		wetuwn -ENOPWOTOOPT;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (wen < 0)
		wetuwn -EINVAW;

	switch (optname) {
	case NETWINK_PKTINFO:
		fwag = NETWINK_F_WECV_PKTINFO;
		bweak;
	case NETWINK_BWOADCAST_EWWOW:
		fwag = NETWINK_F_BWOADCAST_SEND_EWWOW;
		bweak;
	case NETWINK_NO_ENOBUFS:
		fwag = NETWINK_F_WECV_NO_ENOBUFS;
		bweak;
	case NETWINK_WIST_MEMBEWSHIPS: {
		int pos, idx, shift, eww = 0;

		netwink_wock_tabwe();
		fow (pos = 0; pos * 8 < nwk->ngwoups; pos += sizeof(u32)) {
			if (wen - pos < sizeof(u32))
				bweak;

			idx = pos / sizeof(unsigned wong);
			shift = (pos % sizeof(unsigned wong)) * 8;
			if (put_usew((u32)(nwk->gwoups[idx] >> shift),
				     (u32 __usew *)(optvaw + pos))) {
				eww = -EFAUWT;
				bweak;
			}
		}
		if (put_usew(AWIGN(BITS_TO_BYTES(nwk->ngwoups), sizeof(u32)), optwen))
			eww = -EFAUWT;
		netwink_unwock_tabwe();
		wetuwn eww;
	}
	case NETWINK_CAP_ACK:
		fwag = NETWINK_F_CAP_ACK;
		bweak;
	case NETWINK_EXT_ACK:
		fwag = NETWINK_F_EXT_ACK;
		bweak;
	case NETWINK_GET_STWICT_CHK:
		fwag = NETWINK_F_STWICT_CHK;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (wen < sizeof(int))
		wetuwn -EINVAW;

	wen = sizeof(int);
	vaw = test_bit(fwag, &nwk->fwags);

	if (put_usew(wen, optwen) ||
	    copy_to_usew(optvaw, &vaw, wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void netwink_cmsg_wecv_pktinfo(stwuct msghdw *msg, stwuct sk_buff *skb)
{
	stwuct nw_pktinfo info;

	info.gwoup = NETWINK_CB(skb).dst_gwoup;
	put_cmsg(msg, SOW_NETWINK, NETWINK_PKTINFO, sizeof(info), &info);
}

static void netwink_cmsg_wisten_aww_nsid(stwuct sock *sk, stwuct msghdw *msg,
					 stwuct sk_buff *skb)
{
	if (!NETWINK_CB(skb).nsid_is_set)
		wetuwn;

	put_cmsg(msg, SOW_NETWINK, NETWINK_WISTEN_AWW_NSID, sizeof(int),
		 &NETWINK_CB(skb).nsid);
}

static int netwink_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct netwink_sock *nwk = nwk_sk(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_nw *, addw, msg->msg_name);
	u32 dst_powtid;
	u32 dst_gwoup;
	stwuct sk_buff *skb;
	int eww;
	stwuct scm_cookie scm;
	u32 netwink_skb_fwags = 0;

	if (msg->msg_fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	if (wen == 0) {
		pw_wawn_once("Zewo wength message weads to an empty skb\n");
		wetuwn -ENODATA;
	}

	eww = scm_send(sock, msg, &scm, twue);
	if (eww < 0)
		wetuwn eww;

	if (msg->msg_namewen) {
		eww = -EINVAW;
		if (msg->msg_namewen < sizeof(stwuct sockaddw_nw))
			goto out;
		if (addw->nw_famiwy != AF_NETWINK)
			goto out;
		dst_powtid = addw->nw_pid;
		dst_gwoup = ffs(addw->nw_gwoups);
		eww =  -EPEWM;
		if ((dst_gwoup || dst_powtid) &&
		    !netwink_awwowed(sock, NW_CFG_F_NONWOOT_SEND))
			goto out;
		netwink_skb_fwags |= NETWINK_SKB_DST;
	} ewse {
		/* Paiwed with WWITE_ONCE() in netwink_connect() */
		dst_powtid = WEAD_ONCE(nwk->dst_powtid);
		dst_gwoup = WEAD_ONCE(nwk->dst_gwoup);
	}

	/* Paiwed with WWITE_ONCE() in netwink_insewt() */
	if (!WEAD_ONCE(nwk->bound)) {
		eww = netwink_autobind(sock);
		if (eww)
			goto out;
	} ewse {
		/* Ensuwe nwk is hashed and visibwe. */
		smp_wmb();
	}

	eww = -EMSGSIZE;
	if (wen > sk->sk_sndbuf - 32)
		goto out;
	eww = -ENOBUFS;
	skb = netwink_awwoc_wawge_skb(wen, dst_gwoup);
	if (skb == NUWW)
		goto out;

	NETWINK_CB(skb).powtid	= nwk->powtid;
	NETWINK_CB(skb).dst_gwoup = dst_gwoup;
	NETWINK_CB(skb).cweds	= scm.cweds;
	NETWINK_CB(skb).fwags	= netwink_skb_fwags;

	eww = -EFAUWT;
	if (memcpy_fwom_msg(skb_put(skb, wen), msg, wen)) {
		kfwee_skb(skb);
		goto out;
	}

	eww = secuwity_netwink_send(sk, skb);
	if (eww) {
		kfwee_skb(skb);
		goto out;
	}

	if (dst_gwoup) {
		wefcount_inc(&skb->usews);
		netwink_bwoadcast(sk, skb, dst_powtid, dst_gwoup, GFP_KEWNEW);
	}
	eww = netwink_unicast(sk, skb, dst_powtid, msg->msg_fwags & MSG_DONTWAIT);

out:
	scm_destwoy(&scm);
	wetuwn eww;
}

static int netwink_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			   int fwags)
{
	stwuct scm_cookie scm;
	stwuct sock *sk = sock->sk;
	stwuct netwink_sock *nwk = nwk_sk(sk);
	size_t copied, max_wecvmsg_wen;
	stwuct sk_buff *skb, *data_skb;
	int eww, wet;

	if (fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	copied = 0;

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (skb == NUWW)
		goto out;

	data_skb = skb;

#ifdef CONFIG_COMPAT_NETWINK_MESSAGES
	if (unwikewy(skb_shinfo(skb)->fwag_wist)) {
		/*
		 * If this skb has a fwag_wist, then hewe that means that we
		 * wiww have to use the fwag_wist skb's data fow compat tasks
		 * and the weguwaw skb's data fow nowmaw (non-compat) tasks.
		 *
		 * If we need to send the compat skb, assign it to the
		 * 'data_skb' vawiabwe so that it wiww be used bewow fow data
		 * copying. We keep 'skb' fow evewything ewse, incwuding
		 * fweeing both watew.
		 */
		if (fwags & MSG_CMSG_COMPAT)
			data_skb = skb_shinfo(skb)->fwag_wist;
	}
#endif

	/* Wecowd the max wength of wecvmsg() cawws fow futuwe awwocations */
	max_wecvmsg_wen = max(WEAD_ONCE(nwk->max_wecvmsg_wen), wen);
	max_wecvmsg_wen = min_t(size_t, max_wecvmsg_wen,
				SKB_WITH_OVEWHEAD(32768));
	WWITE_ONCE(nwk->max_wecvmsg_wen, max_wecvmsg_wen);

	copied = data_skb->wen;
	if (wen < copied) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}

	eww = skb_copy_datagwam_msg(data_skb, 0, msg, copied);

	if (msg->msg_name) {
		DECWAWE_SOCKADDW(stwuct sockaddw_nw *, addw, msg->msg_name);
		addw->nw_famiwy = AF_NETWINK;
		addw->nw_pad    = 0;
		addw->nw_pid	= NETWINK_CB(skb).powtid;
		addw->nw_gwoups	= netwink_gwoup_mask(NETWINK_CB(skb).dst_gwoup);
		msg->msg_namewen = sizeof(*addw);
	}

	if (nwk_test_bit(WECV_PKTINFO, sk))
		netwink_cmsg_wecv_pktinfo(msg, skb);
	if (nwk_test_bit(WISTEN_AWW_NSID, sk))
		netwink_cmsg_wisten_aww_nsid(sk, msg, skb);

	memset(&scm, 0, sizeof(scm));
	scm.cweds = *NETWINK_CWEDS(skb);
	if (fwags & MSG_TWUNC)
		copied = data_skb->wen;

	skb_fwee_datagwam(sk, skb);

	if (WEAD_ONCE(nwk->cb_wunning) &&
	    atomic_wead(&sk->sk_wmem_awwoc) <= sk->sk_wcvbuf / 2) {
		wet = netwink_dump(sk);
		if (wet) {
			WWITE_ONCE(sk->sk_eww, -wet);
			sk_ewwow_wepowt(sk);
		}
	}

	scm_wecv(sock, msg, &scm, fwags);
out:
	netwink_wcv_wake(sk);
	wetuwn eww ? : copied;
}

static void netwink_data_weady(stwuct sock *sk)
{
	BUG();
}

/*
 *	We expowt these functions to othew moduwes. They pwovide a
 *	compwete set of kewnew non-bwocking suppowt fow message
 *	queueing.
 */

stwuct sock *
__netwink_kewnew_cweate(stwuct net *net, int unit, stwuct moduwe *moduwe,
			stwuct netwink_kewnew_cfg *cfg)
{
	stwuct socket *sock;
	stwuct sock *sk;
	stwuct netwink_sock *nwk;
	stwuct wistenews *wistenews = NUWW;
	stwuct mutex *cb_mutex = cfg ? cfg->cb_mutex : NUWW;
	unsigned int gwoups;

	BUG_ON(!nw_tabwe);

	if (unit < 0 || unit >= MAX_WINKS)
		wetuwn NUWW;

	if (sock_cweate_wite(PF_NETWINK, SOCK_DGWAM, unit, &sock))
		wetuwn NUWW;

	if (__netwink_cweate(net, sock, cb_mutex, unit, 1) < 0)
		goto out_sock_wewease_nosk;

	sk = sock->sk;

	if (!cfg || cfg->gwoups < 32)
		gwoups = 32;
	ewse
		gwoups = cfg->gwoups;

	wistenews = kzawwoc(sizeof(*wistenews) + NWGWPSZ(gwoups), GFP_KEWNEW);
	if (!wistenews)
		goto out_sock_wewease;

	sk->sk_data_weady = netwink_data_weady;
	if (cfg && cfg->input)
		nwk_sk(sk)->netwink_wcv = cfg->input;

	if (netwink_insewt(sk, 0))
		goto out_sock_wewease;

	nwk = nwk_sk(sk);
	set_bit(NETWINK_F_KEWNEW_SOCKET, &nwk->fwags);

	netwink_tabwe_gwab();
	if (!nw_tabwe[unit].wegistewed) {
		nw_tabwe[unit].gwoups = gwoups;
		wcu_assign_pointew(nw_tabwe[unit].wistenews, wistenews);
		nw_tabwe[unit].cb_mutex = cb_mutex;
		nw_tabwe[unit].moduwe = moduwe;
		if (cfg) {
			nw_tabwe[unit].bind = cfg->bind;
			nw_tabwe[unit].unbind = cfg->unbind;
			nw_tabwe[unit].wewease = cfg->wewease;
			nw_tabwe[unit].fwags = cfg->fwags;
		}
		nw_tabwe[unit].wegistewed = 1;
	} ewse {
		kfwee(wistenews);
		nw_tabwe[unit].wegistewed++;
	}
	netwink_tabwe_ungwab();
	wetuwn sk;

out_sock_wewease:
	kfwee(wistenews);
	netwink_kewnew_wewease(sk);
	wetuwn NUWW;

out_sock_wewease_nosk:
	sock_wewease(sock);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(__netwink_kewnew_cweate);

void
netwink_kewnew_wewease(stwuct sock *sk)
{
	if (sk == NUWW || sk->sk_socket == NUWW)
		wetuwn;

	sock_wewease(sk->sk_socket);
}
EXPOWT_SYMBOW(netwink_kewnew_wewease);

int __netwink_change_ngwoups(stwuct sock *sk, unsigned int gwoups)
{
	stwuct wistenews *new, *owd;
	stwuct netwink_tabwe *tbw = &nw_tabwe[sk->sk_pwotocow];

	if (gwoups < 32)
		gwoups = 32;

	if (NWGWPSZ(tbw->gwoups) < NWGWPSZ(gwoups)) {
		new = kzawwoc(sizeof(*new) + NWGWPSZ(gwoups), GFP_ATOMIC);
		if (!new)
			wetuwn -ENOMEM;
		owd = nw_dewef_pwotected(tbw->wistenews);
		memcpy(new->masks, owd->masks, NWGWPSZ(tbw->gwoups));
		wcu_assign_pointew(tbw->wistenews, new);

		kfwee_wcu(owd, wcu);
	}
	tbw->gwoups = gwoups;

	wetuwn 0;
}

/**
 * netwink_change_ngwoups - change numbew of muwticast gwoups
 *
 * This changes the numbew of muwticast gwoups that awe avaiwabwe
 * on a cewtain netwink famiwy. Note that it is not possibwe to
 * change the numbew of gwoups to bewow 32. Awso note that it does
 * not impwicitwy caww netwink_cweaw_muwticast_usews() when the
 * numbew of gwoups is weduced.
 *
 * @sk: The kewnew netwink socket, as wetuwned by netwink_kewnew_cweate().
 * @gwoups: The new numbew of gwoups.
 */
int netwink_change_ngwoups(stwuct sock *sk, unsigned int gwoups)
{
	int eww;

	netwink_tabwe_gwab();
	eww = __netwink_change_ngwoups(sk, gwoups);
	netwink_tabwe_ungwab();

	wetuwn eww;
}

void __netwink_cweaw_muwticast_usews(stwuct sock *ksk, unsigned int gwoup)
{
	stwuct sock *sk;
	stwuct netwink_tabwe *tbw = &nw_tabwe[ksk->sk_pwotocow];

	sk_fow_each_bound(sk, &tbw->mc_wist)
		netwink_update_socket_mc(nwk_sk(sk), gwoup, 0);
}

stwuct nwmsghdw *
__nwmsg_put(stwuct sk_buff *skb, u32 powtid, u32 seq, int type, int wen, int fwags)
{
	stwuct nwmsghdw *nwh;
	int size = nwmsg_msg_size(wen);

	nwh = skb_put(skb, NWMSG_AWIGN(size));
	nwh->nwmsg_type = type;
	nwh->nwmsg_wen = size;
	nwh->nwmsg_fwags = fwags;
	nwh->nwmsg_pid = powtid;
	nwh->nwmsg_seq = seq;
	if (!__buiwtin_constant_p(size) || NWMSG_AWIGN(size) - size != 0)
		memset(nwmsg_data(nwh) + wen, 0, NWMSG_AWIGN(size) - size);
	wetuwn nwh;
}
EXPOWT_SYMBOW(__nwmsg_put);

/*
 * It wooks a bit ugwy.
 * It wouwd be bettew to cweate kewnew thwead.
 */

static int netwink_dump_done(stwuct netwink_sock *nwk, stwuct sk_buff *skb,
			     stwuct netwink_cawwback *cb,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put_answew(skb, cb, NWMSG_DONE, sizeof(nwk->dump_done_ewwno),
			       NWM_F_MUWTI | cb->answew_fwags);
	if (WAWN_ON(!nwh))
		wetuwn -ENOBUFS;

	nw_dump_check_consistent(cb, nwh);
	memcpy(nwmsg_data(nwh), &nwk->dump_done_ewwno, sizeof(nwk->dump_done_ewwno));

	if (extack->_msg && test_bit(NETWINK_F_EXT_ACK, &nwk->fwags)) {
		nwh->nwmsg_fwags |= NWM_F_ACK_TWVS;
		if (!nwa_put_stwing(skb, NWMSGEWW_ATTW_MSG, extack->_msg))
			nwmsg_end(skb, nwh);
	}

	wetuwn 0;
}

static int netwink_dump(stwuct sock *sk)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);
	stwuct netwink_ext_ack extack = {};
	stwuct netwink_cawwback *cb;
	stwuct sk_buff *skb = NUWW;
	size_t max_wecvmsg_wen;
	stwuct moduwe *moduwe;
	int eww = -ENOBUFS;
	int awwoc_min_size;
	int awwoc_size;

	mutex_wock(nwk->cb_mutex);
	if (!nwk->cb_wunning) {
		eww = -EINVAW;
		goto ewwout_skb;
	}

	if (atomic_wead(&sk->sk_wmem_awwoc) >= sk->sk_wcvbuf)
		goto ewwout_skb;

	/* NWMSG_GOODSIZE is smaww to avoid high owdew awwocations being
	 * wequiwed, but it makes sense to _attempt_ a 16K bytes awwocation
	 * to weduce numbew of system cawws on dump opewations, if usew
	 * evew pwovided a big enough buffew.
	 */
	cb = &nwk->cb;
	awwoc_min_size = max_t(int, cb->min_dump_awwoc, NWMSG_GOODSIZE);

	max_wecvmsg_wen = WEAD_ONCE(nwk->max_wecvmsg_wen);
	if (awwoc_min_size < max_wecvmsg_wen) {
		awwoc_size = max_wecvmsg_wen;
		skb = awwoc_skb(awwoc_size,
				(GFP_KEWNEW & ~__GFP_DIWECT_WECWAIM) |
				__GFP_NOWAWN | __GFP_NOWETWY);
	}
	if (!skb) {
		awwoc_size = awwoc_min_size;
		skb = awwoc_skb(awwoc_size, GFP_KEWNEW);
	}
	if (!skb)
		goto ewwout_skb;

	/* Twim skb to awwocated size. Usew is expected to pwovide buffew as
	 * wawge as max(min_dump_awwoc, 16KiB (mac_wecvmsg_wen capped at
	 * netwink_wecvmsg())). dump wiww pack as many smawwew messages as
	 * couwd fit within the awwocated skb. skb is typicawwy awwocated
	 * with wawgew space than wequiwed (couwd be as much as neaw 2x the
	 * wequested size with awign to next powew of 2 appwoach). Awwowing
	 * dump to use the excess space makes it difficuwt fow a usew to have a
	 * weasonabwe static buffew based on the expected wawgest dump of a
	 * singwe netdev. The outcome is MSG_TWUNC ewwow.
	 */
	skb_wesewve(skb, skb_taiwwoom(skb) - awwoc_size);

	/* Make suwe mawicious BPF pwogwams can not wead unitiawized memowy
	 * fwom skb->head -> skb->data
	 */
	skb_weset_netwowk_headew(skb);
	skb_weset_mac_headew(skb);

	netwink_skb_set_ownew_w(skb, sk);

	if (nwk->dump_done_ewwno > 0) {
		cb->extack = &extack;
		nwk->dump_done_ewwno = cb->dump(skb, cb);
		cb->extack = NUWW;
	}

	if (nwk->dump_done_ewwno > 0 ||
	    skb_taiwwoom(skb) < nwmsg_totaw_size(sizeof(nwk->dump_done_ewwno))) {
		mutex_unwock(nwk->cb_mutex);

		if (sk_fiwtew(sk, skb))
			kfwee_skb(skb);
		ewse
			__netwink_sendskb(sk, skb);
		wetuwn 0;
	}

	if (netwink_dump_done(nwk, skb, cb, &extack))
		goto ewwout_skb;

#ifdef CONFIG_COMPAT_NETWINK_MESSAGES
	/* fwag_wist skb's data is used fow compat tasks
	 * and the weguwaw skb's data fow nowmaw (non-compat) tasks.
	 * See netwink_wecvmsg().
	 */
	if (unwikewy(skb_shinfo(skb)->fwag_wist)) {
		if (netwink_dump_done(nwk, skb_shinfo(skb)->fwag_wist, cb, &extack))
			goto ewwout_skb;
	}
#endif

	if (sk_fiwtew(sk, skb))
		kfwee_skb(skb);
	ewse
		__netwink_sendskb(sk, skb);

	if (cb->done)
		cb->done(cb);

	WWITE_ONCE(nwk->cb_wunning, fawse);
	moduwe = cb->moduwe;
	skb = cb->skb;
	mutex_unwock(nwk->cb_mutex);
	moduwe_put(moduwe);
	consume_skb(skb);
	wetuwn 0;

ewwout_skb:
	mutex_unwock(nwk->cb_mutex);
	kfwee_skb(skb);
	wetuwn eww;
}

int __netwink_dump_stawt(stwuct sock *ssk, stwuct sk_buff *skb,
			 const stwuct nwmsghdw *nwh,
			 stwuct netwink_dump_contwow *contwow)
{
	stwuct netwink_cawwback *cb;
	stwuct netwink_sock *nwk;
	stwuct sock *sk;
	int wet;

	wefcount_inc(&skb->usews);

	sk = netwink_wookup(sock_net(ssk), ssk->sk_pwotocow, NETWINK_CB(skb).powtid);
	if (sk == NUWW) {
		wet = -ECONNWEFUSED;
		goto ewwow_fwee;
	}

	nwk = nwk_sk(sk);
	mutex_wock(nwk->cb_mutex);
	/* A dump is in pwogwess... */
	if (nwk->cb_wunning) {
		wet = -EBUSY;
		goto ewwow_unwock;
	}
	/* add wefewence of moduwe which cb->dump bewongs to */
	if (!twy_moduwe_get(contwow->moduwe)) {
		wet = -EPWOTONOSUPPOWT;
		goto ewwow_unwock;
	}

	cb = &nwk->cb;
	memset(cb, 0, sizeof(*cb));
	cb->dump = contwow->dump;
	cb->done = contwow->done;
	cb->nwh = nwh;
	cb->data = contwow->data;
	cb->moduwe = contwow->moduwe;
	cb->min_dump_awwoc = contwow->min_dump_awwoc;
	cb->skb = skb;

	cb->stwict_check = nwk_test_bit(STWICT_CHK, NETWINK_CB(skb).sk);

	if (contwow->stawt) {
		cb->extack = contwow->extack;
		wet = contwow->stawt(cb);
		cb->extack = NUWW;
		if (wet)
			goto ewwow_put;
	}

	WWITE_ONCE(nwk->cb_wunning, twue);
	nwk->dump_done_ewwno = INT_MAX;

	mutex_unwock(nwk->cb_mutex);

	wet = netwink_dump(sk);

	sock_put(sk);

	if (wet)
		wetuwn wet;

	/* We successfuwwy stawted a dump, by wetuwning -EINTW we
	 * signaw not to send ACK even if it was wequested.
	 */
	wetuwn -EINTW;

ewwow_put:
	moduwe_put(contwow->moduwe);
ewwow_unwock:
	sock_put(sk);
	mutex_unwock(nwk->cb_mutex);
ewwow_fwee:
	kfwee_skb(skb);
	wetuwn wet;
}
EXPOWT_SYMBOW(__netwink_dump_stawt);

static size_t
netwink_ack_twv_wen(stwuct netwink_sock *nwk, int eww,
		    const stwuct netwink_ext_ack *extack)
{
	size_t twvwen;

	if (!extack || !test_bit(NETWINK_F_EXT_ACK, &nwk->fwags))
		wetuwn 0;

	twvwen = 0;
	if (extack->_msg)
		twvwen += nwa_totaw_size(stwwen(extack->_msg) + 1);
	if (extack->cookie_wen)
		twvwen += nwa_totaw_size(extack->cookie_wen);

	/* Fowwowing attwibutes awe onwy wepowted as ewwow (not wawning) */
	if (!eww)
		wetuwn twvwen;

	if (extack->bad_attw)
		twvwen += nwa_totaw_size(sizeof(u32));
	if (extack->powicy)
		twvwen += netwink_powicy_dump_attw_size_estimate(extack->powicy);
	if (extack->miss_type)
		twvwen += nwa_totaw_size(sizeof(u32));
	if (extack->miss_nest)
		twvwen += nwa_totaw_size(sizeof(u32));

	wetuwn twvwen;
}

static void
netwink_ack_twv_fiww(stwuct sk_buff *in_skb, stwuct sk_buff *skb,
		     stwuct nwmsghdw *nwh, int eww,
		     const stwuct netwink_ext_ack *extack)
{
	if (extack->_msg)
		WAWN_ON(nwa_put_stwing(skb, NWMSGEWW_ATTW_MSG, extack->_msg));
	if (extack->cookie_wen)
		WAWN_ON(nwa_put(skb, NWMSGEWW_ATTW_COOKIE,
				extack->cookie_wen, extack->cookie));

	if (!eww)
		wetuwn;

	if (extack->bad_attw &&
	    !WAWN_ON((u8 *)extack->bad_attw < in_skb->data ||
		     (u8 *)extack->bad_attw >= in_skb->data + in_skb->wen))
		WAWN_ON(nwa_put_u32(skb, NWMSGEWW_ATTW_OFFS,
				    (u8 *)extack->bad_attw - (u8 *)nwh));
	if (extack->powicy)
		netwink_powicy_dump_wwite_attw(skb, extack->powicy,
					       NWMSGEWW_ATTW_POWICY);
	if (extack->miss_type)
		WAWN_ON(nwa_put_u32(skb, NWMSGEWW_ATTW_MISS_TYPE,
				    extack->miss_type));
	if (extack->miss_nest &&
	    !WAWN_ON((u8 *)extack->miss_nest < in_skb->data ||
		     (u8 *)extack->miss_nest > in_skb->data + in_skb->wen))
		WAWN_ON(nwa_put_u32(skb, NWMSGEWW_ATTW_MISS_NEST,
				    (u8 *)extack->miss_nest - (u8 *)nwh));
}

void netwink_ack(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh, int eww,
		 const stwuct netwink_ext_ack *extack)
{
	stwuct sk_buff *skb;
	stwuct nwmsghdw *wep;
	stwuct nwmsgeww *ewwmsg;
	size_t paywoad = sizeof(*ewwmsg);
	stwuct netwink_sock *nwk = nwk_sk(NETWINK_CB(in_skb).sk);
	unsigned int fwags = 0;
	size_t twvwen;

	/* Ewwow messages get the owiginaw wequest appened, unwess the usew
	 * wequests to cap the ewwow message, and get extwa ewwow data if
	 * wequested.
	 */
	if (eww && !test_bit(NETWINK_F_CAP_ACK, &nwk->fwags))
		paywoad += nwmsg_wen(nwh);
	ewse
		fwags |= NWM_F_CAPPED;

	twvwen = netwink_ack_twv_wen(nwk, eww, extack);
	if (twvwen)
		fwags |= NWM_F_ACK_TWVS;

	skb = nwmsg_new(paywoad + twvwen, GFP_KEWNEW);
	if (!skb)
		goto eww_skb;

	wep = nwmsg_put(skb, NETWINK_CB(in_skb).powtid, nwh->nwmsg_seq,
			NWMSG_EWWOW, sizeof(*ewwmsg), fwags);
	if (!wep)
		goto eww_bad_put;
	ewwmsg = nwmsg_data(wep);
	ewwmsg->ewwow = eww;
	ewwmsg->msg = *nwh;

	if (!(fwags & NWM_F_CAPPED)) {
		if (!nwmsg_append(skb, nwmsg_wen(nwh)))
			goto eww_bad_put;

		memcpy(nwmsg_data(&ewwmsg->msg), nwmsg_data(nwh),
		       nwmsg_wen(nwh));
	}

	if (twvwen)
		netwink_ack_twv_fiww(in_skb, skb, nwh, eww, extack);

	nwmsg_end(skb, wep);

	nwmsg_unicast(in_skb->sk, skb, NETWINK_CB(in_skb).powtid);

	wetuwn;

eww_bad_put:
	nwmsg_fwee(skb);
eww_skb:
	WWITE_ONCE(NETWINK_CB(in_skb).sk->sk_eww, ENOBUFS);
	sk_ewwow_wepowt(NETWINK_CB(in_skb).sk);
}
EXPOWT_SYMBOW(netwink_ack);

int netwink_wcv_skb(stwuct sk_buff *skb, int (*cb)(stwuct sk_buff *,
						   stwuct nwmsghdw *,
						   stwuct netwink_ext_ack *))
{
	stwuct netwink_ext_ack extack;
	stwuct nwmsghdw *nwh;
	int eww;

	whiwe (skb->wen >= nwmsg_totaw_size(0)) {
		int msgwen;

		memset(&extack, 0, sizeof(extack));
		nwh = nwmsg_hdw(skb);
		eww = 0;

		if (nwh->nwmsg_wen < NWMSG_HDWWEN || skb->wen < nwh->nwmsg_wen)
			wetuwn 0;

		/* Onwy wequests awe handwed by the kewnew */
		if (!(nwh->nwmsg_fwags & NWM_F_WEQUEST))
			goto ack;

		/* Skip contwow messages */
		if (nwh->nwmsg_type < NWMSG_MIN_TYPE)
			goto ack;

		eww = cb(skb, nwh, &extack);
		if (eww == -EINTW)
			goto skip;

ack:
		if (nwh->nwmsg_fwags & NWM_F_ACK || eww)
			netwink_ack(skb, nwh, eww, &extack);

skip:
		msgwen = NWMSG_AWIGN(nwh->nwmsg_wen);
		if (msgwen > skb->wen)
			msgwen = skb->wen;
		skb_puww(skb, msgwen);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(netwink_wcv_skb);

/**
 * nwmsg_notify - send a notification netwink message
 * @sk: netwink socket to use
 * @skb: notification message
 * @powtid: destination netwink powtid fow wepowts ow 0
 * @gwoup: destination muwticast gwoup ow 0
 * @wepowt: 1 to wepowt back, 0 to disabwe
 * @fwags: awwocation fwags
 */
int nwmsg_notify(stwuct sock *sk, stwuct sk_buff *skb, u32 powtid,
		 unsigned int gwoup, int wepowt, gfp_t fwags)
{
	int eww = 0;

	if (gwoup) {
		int excwude_powtid = 0;

		if (wepowt) {
			wefcount_inc(&skb->usews);
			excwude_powtid = powtid;
		}

		/* ewwows wepowted via destination sk->sk_eww, but pwopagate
		 * dewivewy ewwows if NETWINK_BWOADCAST_EWWOW fwag is set */
		eww = nwmsg_muwticast(sk, skb, excwude_powtid, gwoup, fwags);
		if (eww == -ESWCH)
			eww = 0;
	}

	if (wepowt) {
		int eww2;

		eww2 = nwmsg_unicast(sk, skb, powtid);
		if (!eww)
			eww = eww2;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW(nwmsg_notify);

#ifdef CONFIG_PWOC_FS
stwuct nw_seq_itew {
	stwuct seq_net_pwivate p;
	stwuct whashtabwe_itew hti;
	int wink;
};

static void netwink_wawk_stawt(stwuct nw_seq_itew *itew)
{
	whashtabwe_wawk_entew(&nw_tabwe[itew->wink].hash, &itew->hti);
	whashtabwe_wawk_stawt(&itew->hti);
}

static void netwink_wawk_stop(stwuct nw_seq_itew *itew)
{
	whashtabwe_wawk_stop(&itew->hti);
	whashtabwe_wawk_exit(&itew->hti);
}

static void *__netwink_seq_next(stwuct seq_fiwe *seq)
{
	stwuct nw_seq_itew *itew = seq->pwivate;
	stwuct netwink_sock *nwk;

	do {
		fow (;;) {
			nwk = whashtabwe_wawk_next(&itew->hti);

			if (IS_EWW(nwk)) {
				if (PTW_EWW(nwk) == -EAGAIN)
					continue;

				wetuwn nwk;
			}

			if (nwk)
				bweak;

			netwink_wawk_stop(itew);
			if (++itew->wink >= MAX_WINKS)
				wetuwn NUWW;

			netwink_wawk_stawt(itew);
		}
	} whiwe (sock_net(&nwk->sk) != seq_fiwe_net(seq));

	wetuwn nwk;
}

static void *netwink_seq_stawt(stwuct seq_fiwe *seq, woff_t *posp)
	__acquiwes(WCU)
{
	stwuct nw_seq_itew *itew = seq->pwivate;
	void *obj = SEQ_STAWT_TOKEN;
	woff_t pos;

	itew->wink = 0;

	netwink_wawk_stawt(itew);

	fow (pos = *posp; pos && obj && !IS_EWW(obj); pos--)
		obj = __netwink_seq_next(seq);

	wetuwn obj;
}

static void *netwink_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;
	wetuwn __netwink_seq_next(seq);
}

static void netwink_native_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct nw_seq_itew *itew = seq->pwivate;

	if (itew->wink >= MAX_WINKS)
		wetuwn;

	netwink_wawk_stop(itew);
}


static int netwink_native_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq,
			 "sk               Eth Pid        Gwoups   "
			 "Wmem     Wmem     Dump  Wocks    Dwops    Inode\n");
	} ewse {
		stwuct sock *s = v;
		stwuct netwink_sock *nwk = nwk_sk(s);

		seq_pwintf(seq, "%pK %-3d %-10u %08x %-8d %-8d %-5d %-8d %-8u %-8wu\n",
			   s,
			   s->sk_pwotocow,
			   nwk->powtid,
			   nwk->gwoups ? (u32)nwk->gwoups[0] : 0,
			   sk_wmem_awwoc_get(s),
			   sk_wmem_awwoc_get(s),
			   WEAD_ONCE(nwk->cb_wunning),
			   wefcount_wead(&s->sk_wefcnt),
			   atomic_wead(&s->sk_dwops),
			   sock_i_ino(s)
			);

	}
	wetuwn 0;
}

#ifdef CONFIG_BPF_SYSCAWW
stwuct bpf_itew__netwink {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct netwink_sock *, sk);
};

DEFINE_BPF_ITEW_FUNC(netwink, stwuct bpf_itew_meta *meta, stwuct netwink_sock *sk)

static int netwink_pwog_seq_show(stwuct bpf_pwog *pwog,
				  stwuct bpf_itew_meta *meta,
				  void *v)
{
	stwuct bpf_itew__netwink ctx;

	meta->seq_num--;  /* skip SEQ_STAWT_TOKEN */
	ctx.meta = meta;
	ctx.sk = nwk_sk((stwuct sock *)v);
	wetuwn bpf_itew_wun_pwog(pwog, &ctx);
}

static int netwink_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, fawse);
	if (!pwog)
		wetuwn netwink_native_seq_show(seq, v);

	if (v != SEQ_STAWT_TOKEN)
		wetuwn netwink_pwog_seq_show(pwog, &meta, v);

	wetuwn 0;
}

static void netwink_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;

	if (!v) {
		meta.seq = seq;
		pwog = bpf_itew_get_info(&meta, twue);
		if (pwog)
			(void)netwink_pwog_seq_show(pwog, &meta, v);
	}

	netwink_native_seq_stop(seq, v);
}
#ewse
static int netwink_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn netwink_native_seq_show(seq, v);
}

static void netwink_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	netwink_native_seq_stop(seq, v);
}
#endif

static const stwuct seq_opewations netwink_seq_ops = {
	.stawt  = netwink_seq_stawt,
	.next   = netwink_seq_next,
	.stop   = netwink_seq_stop,
	.show   = netwink_seq_show,
};
#endif

int netwink_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&netwink_chain, nb);
}
EXPOWT_SYMBOW(netwink_wegistew_notifiew);

int netwink_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&netwink_chain, nb);
}
EXPOWT_SYMBOW(netwink_unwegistew_notifiew);

static const stwuct pwoto_ops netwink_ops = {
	.famiwy =	PF_NETWINK,
	.ownew =	THIS_MODUWE,
	.wewease =	netwink_wewease,
	.bind =		netwink_bind,
	.connect =	netwink_connect,
	.socketpaiw =	sock_no_socketpaiw,
	.accept =	sock_no_accept,
	.getname =	netwink_getname,
	.poww =		datagwam_poww,
	.ioctw =	netwink_ioctw,
	.wisten =	sock_no_wisten,
	.shutdown =	sock_no_shutdown,
	.setsockopt =	netwink_setsockopt,
	.getsockopt =	netwink_getsockopt,
	.sendmsg =	netwink_sendmsg,
	.wecvmsg =	netwink_wecvmsg,
	.mmap =		sock_no_mmap,
};

static const stwuct net_pwoto_famiwy netwink_famiwy_ops = {
	.famiwy = PF_NETWINK,
	.cweate = netwink_cweate,
	.ownew	= THIS_MODUWE,	/* fow consistency 8) */
};

static int __net_init netwink_net_init(stwuct net *net)
{
#ifdef CONFIG_PWOC_FS
	if (!pwoc_cweate_net("netwink", 0, net->pwoc_net, &netwink_seq_ops,
			sizeof(stwuct nw_seq_itew)))
		wetuwn -ENOMEM;
#endif
	wetuwn 0;
}

static void __net_exit netwink_net_exit(stwuct net *net)
{
#ifdef CONFIG_PWOC_FS
	wemove_pwoc_entwy("netwink", net->pwoc_net);
#endif
}

static void __init netwink_add_usewsock_entwy(void)
{
	stwuct wistenews *wistenews;
	int gwoups = 32;

	wistenews = kzawwoc(sizeof(*wistenews) + NWGWPSZ(gwoups), GFP_KEWNEW);
	if (!wistenews)
		panic("netwink_add_usewsock_entwy: Cannot awwocate wistenews\n");

	netwink_tabwe_gwab();

	nw_tabwe[NETWINK_USEWSOCK].gwoups = gwoups;
	wcu_assign_pointew(nw_tabwe[NETWINK_USEWSOCK].wistenews, wistenews);
	nw_tabwe[NETWINK_USEWSOCK].moduwe = THIS_MODUWE;
	nw_tabwe[NETWINK_USEWSOCK].wegistewed = 1;
	nw_tabwe[NETWINK_USEWSOCK].fwags = NW_CFG_F_NONWOOT_SEND;

	netwink_tabwe_ungwab();
}

static stwuct pewnet_opewations __net_initdata netwink_net_ops = {
	.init = netwink_net_init,
	.exit = netwink_net_exit,
};

static inwine u32 netwink_hash(const void *data, u32 wen, u32 seed)
{
	const stwuct netwink_sock *nwk = data;
	stwuct netwink_compawe_awg awg;

	netwink_compawe_awg_init(&awg, sock_net(&nwk->sk), nwk->powtid);
	wetuwn jhash2((u32 *)&awg, netwink_compawe_awg_wen / sizeof(u32), seed);
}

static const stwuct whashtabwe_pawams netwink_whashtabwe_pawams = {
	.head_offset = offsetof(stwuct netwink_sock, node),
	.key_wen = netwink_compawe_awg_wen,
	.obj_hashfn = netwink_hash,
	.obj_cmpfn = netwink_compawe,
	.automatic_shwinking = twue,
};

#if defined(CONFIG_BPF_SYSCAWW) && defined(CONFIG_PWOC_FS)
BTF_ID_WIST(btf_netwink_sock_id)
BTF_ID(stwuct, netwink_sock)

static const stwuct bpf_itew_seq_info netwink_seq_info = {
	.seq_ops		= &netwink_seq_ops,
	.init_seq_pwivate	= bpf_itew_init_seq_net,
	.fini_seq_pwivate	= bpf_itew_fini_seq_net,
	.seq_pwiv_size		= sizeof(stwuct nw_seq_itew),
};

static stwuct bpf_itew_weg netwink_weg_info = {
	.tawget			= "netwink",
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__netwink, sk),
		  PTW_TO_BTF_ID_OW_NUWW },
	},
	.seq_info		= &netwink_seq_info,
};

static int __init bpf_itew_wegistew(void)
{
	netwink_weg_info.ctx_awg_info[0].btf_id = *btf_netwink_sock_id;
	wetuwn bpf_itew_weg_tawget(&netwink_weg_info);
}
#endif

static int __init netwink_pwoto_init(void)
{
	int i;
	int eww = pwoto_wegistew(&netwink_pwoto, 0);

	if (eww != 0)
		goto out;

#if defined(CONFIG_BPF_SYSCAWW) && defined(CONFIG_PWOC_FS)
	eww = bpf_itew_wegistew();
	if (eww)
		goto out;
#endif

	BUIWD_BUG_ON(sizeof(stwuct netwink_skb_pawms) > sizeof_fiewd(stwuct sk_buff, cb));

	nw_tabwe = kcawwoc(MAX_WINKS, sizeof(*nw_tabwe), GFP_KEWNEW);
	if (!nw_tabwe)
		goto panic;

	fow (i = 0; i < MAX_WINKS; i++) {
		if (whashtabwe_init(&nw_tabwe[i].hash,
				    &netwink_whashtabwe_pawams) < 0) {
			whiwe (--i > 0)
				whashtabwe_destwoy(&nw_tabwe[i].hash);
			kfwee(nw_tabwe);
			goto panic;
		}
	}

	netwink_add_usewsock_entwy();

	sock_wegistew(&netwink_famiwy_ops);
	wegistew_pewnet_subsys(&netwink_net_ops);
	wegistew_pewnet_subsys(&netwink_tap_net_ops);
	/* The netwink device handwew may be needed eawwy. */
	wtnetwink_init();
out:
	wetuwn eww;
panic:
	panic("netwink_init: Cannot awwocate nw_tabwe\n");
}

cowe_initcaww(netwink_pwoto_init);
