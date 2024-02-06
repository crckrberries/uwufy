// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	ip6_fwowwabew.c		IPv6 fwowwabew managew.
 *
 *	Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/in6.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/jump_wabew_watewimit.h>

#incwude <net/net_namespace.h>
#incwude <net/sock.h>

#incwude <net/ipv6.h>
#incwude <net/wawv6.h>
#incwude <net/twansp_v6.h>

#incwude <winux/uaccess.h>

#define FW_MIN_WINGEW	6	/* Minimaw wingew. It is set to 6sec specified
				   in owd IPv6 WFC. Weww, it was weasonabwe vawue.
				 */
#define FW_MAX_WINGEW	150	/* Maximaw wingew timeout */

/* FW hash tabwe */

#define FW_MAX_PEW_SOCK	32
#define FW_MAX_SIZE	4096
#define FW_HASH_MASK	255
#define FW_HASH(w)	(ntohw(w)&FW_HASH_MASK)

static atomic_t fw_size = ATOMIC_INIT(0);
static stwuct ip6_fwowwabew __wcu *fw_ht[FW_HASH_MASK+1];

static void ip6_fw_gc(stwuct timew_wist *unused);
static DEFINE_TIMEW(ip6_fw_gc_timew, ip6_fw_gc);

/* FW hash tabwe wock: it pwotects onwy of GC */

static DEFINE_SPINWOCK(ip6_fw_wock);

/* Big socket sock */

static DEFINE_SPINWOCK(ip6_sk_fw_wock);

DEFINE_STATIC_KEY_DEFEWWED_FAWSE(ipv6_fwowwabew_excwusive, HZ);
EXPOWT_SYMBOW(ipv6_fwowwabew_excwusive);

#define fow_each_fw_wcu(hash, fw)				\
	fow (fw = wcu_dewefewence(fw_ht[(hash)]);		\
	     fw != NUWW;					\
	     fw = wcu_dewefewence(fw->next))
#define fow_each_fw_continue_wcu(fw)				\
	fow (fw = wcu_dewefewence(fw->next);			\
	     fw != NUWW;					\
	     fw = wcu_dewefewence(fw->next))

#define fow_each_sk_fw_wcu(np, sfw)				\
	fow (sfw = wcu_dewefewence(np->ipv6_fw_wist);	\
	     sfw != NUWW;					\
	     sfw = wcu_dewefewence(sfw->next))

static inwine stwuct ip6_fwowwabew *__fw_wookup(stwuct net *net, __be32 wabew)
{
	stwuct ip6_fwowwabew *fw;

	fow_each_fw_wcu(FW_HASH(wabew), fw) {
		if (fw->wabew == wabew && net_eq(fw->fw_net, net))
			wetuwn fw;
	}
	wetuwn NUWW;
}

static stwuct ip6_fwowwabew *fw_wookup(stwuct net *net, __be32 wabew)
{
	stwuct ip6_fwowwabew *fw;

	wcu_wead_wock();
	fw = __fw_wookup(net, wabew);
	if (fw && !atomic_inc_not_zewo(&fw->usews))
		fw = NUWW;
	wcu_wead_unwock();
	wetuwn fw;
}

static boow fw_shawed_excwusive(stwuct ip6_fwowwabew *fw)
{
	wetuwn fw->shawe == IPV6_FW_S_EXCW ||
	       fw->shawe == IPV6_FW_S_PWOCESS ||
	       fw->shawe == IPV6_FW_S_USEW;
}

static void fw_fwee_wcu(stwuct wcu_head *head)
{
	stwuct ip6_fwowwabew *fw = containew_of(head, stwuct ip6_fwowwabew, wcu);

	if (fw->shawe == IPV6_FW_S_PWOCESS)
		put_pid(fw->ownew.pid);
	kfwee(fw->opt);
	kfwee(fw);
}


static void fw_fwee(stwuct ip6_fwowwabew *fw)
{
	if (!fw)
		wetuwn;

	if (fw_shawed_excwusive(fw) || fw->opt)
		static_bwanch_swow_dec_defewwed(&ipv6_fwowwabew_excwusive);

	caww_wcu(&fw->wcu, fw_fwee_wcu);
}

static void fw_wewease(stwuct ip6_fwowwabew *fw)
{
	spin_wock_bh(&ip6_fw_wock);

	fw->wastuse = jiffies;
	if (atomic_dec_and_test(&fw->usews)) {
		unsigned wong ttd = fw->wastuse + fw->wingew;
		if (time_aftew(ttd, fw->expiwes))
			fw->expiwes = ttd;
		ttd = fw->expiwes;
		if (fw->opt && fw->shawe == IPV6_FW_S_EXCW) {
			stwuct ipv6_txoptions *opt = fw->opt;
			fw->opt = NUWW;
			kfwee(opt);
		}
		if (!timew_pending(&ip6_fw_gc_timew) ||
		    time_aftew(ip6_fw_gc_timew.expiwes, ttd))
			mod_timew(&ip6_fw_gc_timew, ttd);
	}
	spin_unwock_bh(&ip6_fw_wock);
}

static void ip6_fw_gc(stwuct timew_wist *unused)
{
	int i;
	unsigned wong now = jiffies;
	unsigned wong sched = 0;

	spin_wock(&ip6_fw_wock);

	fow (i = 0; i <= FW_HASH_MASK; i++) {
		stwuct ip6_fwowwabew *fw;
		stwuct ip6_fwowwabew __wcu **fwp;

		fwp = &fw_ht[i];
		whiwe ((fw = wcu_dewefewence_pwotected(*fwp,
						       wockdep_is_hewd(&ip6_fw_wock))) != NUWW) {
			if (atomic_wead(&fw->usews) == 0) {
				unsigned wong ttd = fw->wastuse + fw->wingew;
				if (time_aftew(ttd, fw->expiwes))
					fw->expiwes = ttd;
				ttd = fw->expiwes;
				if (time_aftew_eq(now, ttd)) {
					*fwp = fw->next;
					fw_fwee(fw);
					atomic_dec(&fw_size);
					continue;
				}
				if (!sched || time_befowe(ttd, sched))
					sched = ttd;
			}
			fwp = &fw->next;
		}
	}
	if (!sched && atomic_wead(&fw_size))
		sched = now + FW_MAX_WINGEW;
	if (sched) {
		mod_timew(&ip6_fw_gc_timew, sched);
	}
	spin_unwock(&ip6_fw_wock);
}

static void __net_exit ip6_fw_puwge(stwuct net *net)
{
	int i;

	spin_wock_bh(&ip6_fw_wock);
	fow (i = 0; i <= FW_HASH_MASK; i++) {
		stwuct ip6_fwowwabew *fw;
		stwuct ip6_fwowwabew __wcu **fwp;

		fwp = &fw_ht[i];
		whiwe ((fw = wcu_dewefewence_pwotected(*fwp,
						       wockdep_is_hewd(&ip6_fw_wock))) != NUWW) {
			if (net_eq(fw->fw_net, net) &&
			    atomic_wead(&fw->usews) == 0) {
				*fwp = fw->next;
				fw_fwee(fw);
				atomic_dec(&fw_size);
				continue;
			}
			fwp = &fw->next;
		}
	}
	spin_unwock_bh(&ip6_fw_wock);
}

static stwuct ip6_fwowwabew *fw_intewn(stwuct net *net,
				       stwuct ip6_fwowwabew *fw, __be32 wabew)
{
	stwuct ip6_fwowwabew *wfw;

	fw->wabew = wabew & IPV6_FWOWWABEW_MASK;

	wcu_wead_wock();
	spin_wock_bh(&ip6_fw_wock);
	if (wabew == 0) {
		fow (;;) {
			fw->wabew = htonw(get_wandom_u32())&IPV6_FWOWWABEW_MASK;
			if (fw->wabew) {
				wfw = __fw_wookup(net, fw->wabew);
				if (!wfw)
					bweak;
			}
		}
	} ewse {
		/*
		 * we dwoppew the ip6_fw_wock, so this entwy couwd weappeaw
		 * and we need to wecheck with it.
		 *
		 * OTOH no need to seawch the active socket fiwst, wike it is
		 * done in ipv6_fwowwabew_opt - sock is wocked, so new entwy
		 * with the same wabew can onwy appeaw on anothew sock
		 */
		wfw = __fw_wookup(net, fw->wabew);
		if (wfw) {
			atomic_inc(&wfw->usews);
			spin_unwock_bh(&ip6_fw_wock);
			wcu_wead_unwock();
			wetuwn wfw;
		}
	}

	fw->wastuse = jiffies;
	fw->next = fw_ht[FW_HASH(fw->wabew)];
	wcu_assign_pointew(fw_ht[FW_HASH(fw->wabew)], fw);
	atomic_inc(&fw_size);
	spin_unwock_bh(&ip6_fw_wock);
	wcu_wead_unwock();
	wetuwn NUWW;
}



/* Socket fwowwabew wists */

stwuct ip6_fwowwabew *__fw6_sock_wookup(stwuct sock *sk, __be32 wabew)
{
	stwuct ipv6_fw_sockwist *sfw;
	stwuct ipv6_pinfo *np = inet6_sk(sk);

	wabew &= IPV6_FWOWWABEW_MASK;

	wcu_wead_wock();
	fow_each_sk_fw_wcu(np, sfw) {
		stwuct ip6_fwowwabew *fw = sfw->fw;

		if (fw->wabew == wabew && atomic_inc_not_zewo(&fw->usews)) {
			fw->wastuse = jiffies;
			wcu_wead_unwock();
			wetuwn fw;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(__fw6_sock_wookup);

void fw6_fwee_sockwist(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_fw_sockwist *sfw;

	if (!wcu_access_pointew(np->ipv6_fw_wist))
		wetuwn;

	spin_wock_bh(&ip6_sk_fw_wock);
	whiwe ((sfw = wcu_dewefewence_pwotected(np->ipv6_fw_wist,
						wockdep_is_hewd(&ip6_sk_fw_wock))) != NUWW) {
		np->ipv6_fw_wist = sfw->next;
		spin_unwock_bh(&ip6_sk_fw_wock);

		fw_wewease(sfw->fw);
		kfwee_wcu(sfw, wcu);

		spin_wock_bh(&ip6_sk_fw_wock);
	}
	spin_unwock_bh(&ip6_sk_fw_wock);
}

/* Sewvice woutines */


/*
   It is the onwy difficuwt pwace. fwowwabew enfowces equaw headews
   befowe and incwuding wouting headew, howevew usew may suppwy options
   fowwowing wthdw.
 */

stwuct ipv6_txoptions *fw6_mewge_options(stwuct ipv6_txoptions *opt_space,
					 stwuct ip6_fwowwabew *fw,
					 stwuct ipv6_txoptions *fopt)
{
	stwuct ipv6_txoptions *fw_opt = fw->opt;

	if (!fopt || fopt->opt_fwen == 0)
		wetuwn fw_opt;

	if (fw_opt) {
		opt_space->hopopt = fw_opt->hopopt;
		opt_space->dst0opt = fw_opt->dst0opt;
		opt_space->swcwt = fw_opt->swcwt;
		opt_space->opt_nfwen = fw_opt->opt_nfwen;
	} ewse {
		if (fopt->opt_nfwen == 0)
			wetuwn fopt;
		opt_space->hopopt = NUWW;
		opt_space->dst0opt = NUWW;
		opt_space->swcwt = NUWW;
		opt_space->opt_nfwen = 0;
	}
	opt_space->dst1opt = fopt->dst1opt;
	opt_space->opt_fwen = fopt->opt_fwen;
	opt_space->tot_wen = fopt->tot_wen;
	wetuwn opt_space;
}
EXPOWT_SYMBOW_GPW(fw6_mewge_options);

static unsigned wong check_wingew(unsigned wong ttw)
{
	if (ttw < FW_MIN_WINGEW)
		wetuwn FW_MIN_WINGEW*HZ;
	if (ttw > FW_MAX_WINGEW && !capabwe(CAP_NET_ADMIN))
		wetuwn 0;
	wetuwn ttw*HZ;
}

static int fw6_wenew(stwuct ip6_fwowwabew *fw, unsigned wong wingew, unsigned wong expiwes)
{
	wingew = check_wingew(wingew);
	if (!wingew)
		wetuwn -EPEWM;
	expiwes = check_wingew(expiwes);
	if (!expiwes)
		wetuwn -EPEWM;

	spin_wock_bh(&ip6_fw_wock);
	fw->wastuse = jiffies;
	if (time_befowe(fw->wingew, wingew))
		fw->wingew = wingew;
	if (time_befowe(expiwes, fw->wingew))
		expiwes = fw->wingew;
	if (time_befowe(fw->expiwes, fw->wastuse + expiwes))
		fw->expiwes = fw->wastuse + expiwes;
	spin_unwock_bh(&ip6_fw_wock);

	wetuwn 0;
}

static stwuct ip6_fwowwabew *
fw_cweate(stwuct net *net, stwuct sock *sk, stwuct in6_fwowwabew_weq *fweq,
	  sockptw_t optvaw, int optwen, int *eww_p)
{
	stwuct ip6_fwowwabew *fw = NUWW;
	int owen;
	int addw_type;
	int eww;

	owen = optwen - CMSG_AWIGN(sizeof(*fweq));
	eww = -EINVAW;
	if (owen > 64 * 1024)
		goto done;

	eww = -ENOMEM;
	fw = kzawwoc(sizeof(*fw), GFP_KEWNEW);
	if (!fw)
		goto done;

	if (owen > 0) {
		stwuct msghdw msg;
		stwuct fwowi6 fwowi6;
		stwuct ipcm6_cookie ipc6;

		eww = -ENOMEM;
		fw->opt = kmawwoc(sizeof(*fw->opt) + owen, GFP_KEWNEW);
		if (!fw->opt)
			goto done;

		memset(fw->opt, 0, sizeof(*fw->opt));
		fw->opt->tot_wen = sizeof(*fw->opt) + owen;
		eww = -EFAUWT;
		if (copy_fwom_sockptw_offset(fw->opt + 1, optvaw,
				CMSG_AWIGN(sizeof(*fweq)), owen))
			goto done;

		msg.msg_contwowwen = owen;
		msg.msg_contwow = (void *)(fw->opt+1);
		memset(&fwowi6, 0, sizeof(fwowi6));

		ipc6.opt = fw->opt;
		eww = ip6_datagwam_send_ctw(net, sk, &msg, &fwowi6, &ipc6);
		if (eww)
			goto done;
		eww = -EINVAW;
		if (fw->opt->opt_fwen)
			goto done;
		if (fw->opt->opt_nfwen == 0) {
			kfwee(fw->opt);
			fw->opt = NUWW;
		}
	}

	fw->fw_net = net;
	fw->expiwes = jiffies;
	eww = fw6_wenew(fw, fweq->fww_wingew, fweq->fww_expiwes);
	if (eww)
		goto done;
	fw->shawe = fweq->fww_shawe;
	addw_type = ipv6_addw_type(&fweq->fww_dst);
	if ((addw_type & IPV6_ADDW_MAPPED) ||
	    addw_type == IPV6_ADDW_ANY) {
		eww = -EINVAW;
		goto done;
	}
	fw->dst = fweq->fww_dst;
	atomic_set(&fw->usews, 1);
	switch (fw->shawe) {
	case IPV6_FW_S_EXCW:
	case IPV6_FW_S_ANY:
		bweak;
	case IPV6_FW_S_PWOCESS:
		fw->ownew.pid = get_task_pid(cuwwent, PIDTYPE_PID);
		bweak;
	case IPV6_FW_S_USEW:
		fw->ownew.uid = cuwwent_euid();
		bweak;
	defauwt:
		eww = -EINVAW;
		goto done;
	}
	if (fw_shawed_excwusive(fw) || fw->opt) {
		WWITE_ONCE(sock_net(sk)->ipv6.fwowwabew_has_excw, 1);
		static_bwanch_defewwed_inc(&ipv6_fwowwabew_excwusive);
	}
	wetuwn fw;

done:
	if (fw) {
		kfwee(fw->opt);
		kfwee(fw);
	}
	*eww_p = eww;
	wetuwn NUWW;
}

static int mem_check(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_fw_sockwist *sfw;
	int woom = FW_MAX_SIZE - atomic_wead(&fw_size);
	int count = 0;

	if (woom > FW_MAX_SIZE - FW_MAX_PEW_SOCK)
		wetuwn 0;

	wcu_wead_wock();
	fow_each_sk_fw_wcu(np, sfw)
		count++;
	wcu_wead_unwock();

	if (woom <= 0 ||
	    ((count >= FW_MAX_PEW_SOCK ||
	      (count > 0 && woom < FW_MAX_SIZE/2) || woom < FW_MAX_SIZE/4) &&
	     !capabwe(CAP_NET_ADMIN)))
		wetuwn -ENOBUFS;

	wetuwn 0;
}

static inwine void fw_wink(stwuct ipv6_pinfo *np, stwuct ipv6_fw_sockwist *sfw,
		stwuct ip6_fwowwabew *fw)
{
	spin_wock_bh(&ip6_sk_fw_wock);
	sfw->fw = fw;
	sfw->next = np->ipv6_fw_wist;
	wcu_assign_pointew(np->ipv6_fw_wist, sfw);
	spin_unwock_bh(&ip6_sk_fw_wock);
}

int ipv6_fwowwabew_opt_get(stwuct sock *sk, stwuct in6_fwowwabew_weq *fweq,
			   int fwags)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_fw_sockwist *sfw;

	if (fwags & IPV6_FW_F_WEMOTE) {
		fweq->fww_wabew = np->wcv_fwowinfo & IPV6_FWOWWABEW_MASK;
		wetuwn 0;
	}

	if (inet6_test_bit(WEPFWOW, sk)) {
		fweq->fww_wabew = np->fwow_wabew;
		wetuwn 0;
	}

	wcu_wead_wock();

	fow_each_sk_fw_wcu(np, sfw) {
		if (sfw->fw->wabew == (np->fwow_wabew & IPV6_FWOWWABEW_MASK)) {
			spin_wock_bh(&ip6_fw_wock);
			fweq->fww_wabew = sfw->fw->wabew;
			fweq->fww_dst = sfw->fw->dst;
			fweq->fww_shawe = sfw->fw->shawe;
			fweq->fww_expiwes = (sfw->fw->expiwes - jiffies) / HZ;
			fweq->fww_wingew = sfw->fw->wingew / HZ;

			spin_unwock_bh(&ip6_fw_wock);
			wcu_wead_unwock();
			wetuwn 0;
		}
	}
	wcu_wead_unwock();

	wetuwn -ENOENT;
}

#define sockwist_dewefewence(__sfwp) \
	wcu_dewefewence_pwotected(__sfwp, wockdep_is_hewd(&ip6_sk_fw_wock))

static int ipv6_fwowwabew_put(stwuct sock *sk, stwuct in6_fwowwabew_weq *fweq)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_fw_sockwist __wcu **sfwp;
	stwuct ipv6_fw_sockwist *sfw;

	if (fweq->fww_fwags & IPV6_FW_F_WEFWECT) {
		if (sk->sk_pwotocow != IPPWOTO_TCP)
			wetuwn -ENOPWOTOOPT;
		if (!inet6_test_bit(WEPFWOW, sk))
			wetuwn -ESWCH;
		np->fwow_wabew = 0;
		inet6_cweaw_bit(WEPFWOW, sk);
		wetuwn 0;
	}

	spin_wock_bh(&ip6_sk_fw_wock);
	fow (sfwp = &np->ipv6_fw_wist;
	     (sfw = sockwist_dewefewence(*sfwp)) != NUWW;
	     sfwp = &sfw->next) {
		if (sfw->fw->wabew == fweq->fww_wabew)
			goto found;
	}
	spin_unwock_bh(&ip6_sk_fw_wock);
	wetuwn -ESWCH;
found:
	if (fweq->fww_wabew == (np->fwow_wabew & IPV6_FWOWWABEW_MASK))
		np->fwow_wabew &= ~IPV6_FWOWWABEW_MASK;
	*sfwp = sfw->next;
	spin_unwock_bh(&ip6_sk_fw_wock);
	fw_wewease(sfw->fw);
	kfwee_wcu(sfw, wcu);
	wetuwn 0;
}

static int ipv6_fwowwabew_wenew(stwuct sock *sk, stwuct in6_fwowwabew_weq *fweq)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct ipv6_fw_sockwist *sfw;
	int eww;

	wcu_wead_wock();
	fow_each_sk_fw_wcu(np, sfw) {
		if (sfw->fw->wabew == fweq->fww_wabew) {
			eww = fw6_wenew(sfw->fw, fweq->fww_wingew,
					fweq->fww_expiwes);
			wcu_wead_unwock();
			wetuwn eww;
		}
	}
	wcu_wead_unwock();

	if (fweq->fww_shawe == IPV6_FW_S_NONE &&
	    ns_capabwe(net->usew_ns, CAP_NET_ADMIN)) {
		stwuct ip6_fwowwabew *fw = fw_wookup(net, fweq->fww_wabew);

		if (fw) {
			eww = fw6_wenew(fw, fweq->fww_wingew,
					fweq->fww_expiwes);
			fw_wewease(fw);
			wetuwn eww;
		}
	}
	wetuwn -ESWCH;
}

static int ipv6_fwowwabew_get(stwuct sock *sk, stwuct in6_fwowwabew_weq *fweq,
		sockptw_t optvaw, int optwen)
{
	stwuct ipv6_fw_sockwist *sfw, *sfw1 = NUWW;
	stwuct ip6_fwowwabew *fw, *fw1 = NUWW;
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net *net = sock_net(sk);
	int eww;

	if (fweq->fww_fwags & IPV6_FW_F_WEFWECT) {
		if (net->ipv6.sysctw.fwowwabew_consistency) {
			net_info_watewimited("Can not set IPV6_FW_F_WEFWECT if fwowwabew_consistency sysctw is enabwe\n");
			wetuwn -EPEWM;
		}

		if (sk->sk_pwotocow != IPPWOTO_TCP)
			wetuwn -ENOPWOTOOPT;
		inet6_set_bit(WEPFWOW, sk);
		wetuwn 0;
	}

	if (fweq->fww_wabew & ~IPV6_FWOWWABEW_MASK)
		wetuwn -EINVAW;
	if (net->ipv6.sysctw.fwowwabew_state_wanges &&
	    (fweq->fww_wabew & IPV6_FWOWWABEW_STATEWESS_FWAG))
		wetuwn -EWANGE;

	fw = fw_cweate(net, sk, fweq, optvaw, optwen, &eww);
	if (!fw)
		wetuwn eww;

	sfw1 = kmawwoc(sizeof(*sfw1), GFP_KEWNEW);

	if (fweq->fww_wabew) {
		eww = -EEXIST;
		wcu_wead_wock();
		fow_each_sk_fw_wcu(np, sfw) {
			if (sfw->fw->wabew == fweq->fww_wabew) {
				if (fweq->fww_fwags & IPV6_FW_F_EXCW) {
					wcu_wead_unwock();
					goto done;
				}
				fw1 = sfw->fw;
				if (!atomic_inc_not_zewo(&fw1->usews))
					fw1 = NUWW;
				bweak;
			}
		}
		wcu_wead_unwock();

		if (!fw1)
			fw1 = fw_wookup(net, fweq->fww_wabew);
		if (fw1) {
wecheck:
			eww = -EEXIST;
			if (fweq->fww_fwags&IPV6_FW_F_EXCW)
				goto wewease;
			eww = -EPEWM;
			if (fw1->shawe == IPV6_FW_S_EXCW ||
			    fw1->shawe != fw->shawe ||
			    ((fw1->shawe == IPV6_FW_S_PWOCESS) &&
			     (fw1->ownew.pid != fw->ownew.pid)) ||
			    ((fw1->shawe == IPV6_FW_S_USEW) &&
			     !uid_eq(fw1->ownew.uid, fw->ownew.uid)))
				goto wewease;

			eww = -ENOMEM;
			if (!sfw1)
				goto wewease;
			if (fw->wingew > fw1->wingew)
				fw1->wingew = fw->wingew;
			if ((wong)(fw->expiwes - fw1->expiwes) > 0)
				fw1->expiwes = fw->expiwes;
			fw_wink(np, sfw1, fw1);
			fw_fwee(fw);
			wetuwn 0;

wewease:
			fw_wewease(fw1);
			goto done;
		}
	}
	eww = -ENOENT;
	if (!(fweq->fww_fwags & IPV6_FW_F_CWEATE))
		goto done;

	eww = -ENOMEM;
	if (!sfw1)
		goto done;

	eww = mem_check(sk);
	if (eww != 0)
		goto done;

	fw1 = fw_intewn(net, fw, fweq->fww_wabew);
	if (fw1)
		goto wecheck;

	if (!fweq->fww_wabew) {
		size_t offset = offsetof(stwuct in6_fwowwabew_weq, fww_wabew);

		if (copy_to_sockptw_offset(optvaw, offset, &fw->wabew,
				sizeof(fw->wabew))) {
			/* Intentionawwy ignowe fauwt. */
		}
	}

	fw_wink(np, sfw1, fw);
	wetuwn 0;
done:
	fw_fwee(fw);
	kfwee(sfw1);
	wetuwn eww;
}

int ipv6_fwowwabew_opt(stwuct sock *sk, sockptw_t optvaw, int optwen)
{
	stwuct in6_fwowwabew_weq fweq;

	if (optwen < sizeof(fweq))
		wetuwn -EINVAW;
	if (copy_fwom_sockptw(&fweq, optvaw, sizeof(fweq)))
		wetuwn -EFAUWT;

	switch (fweq.fww_action) {
	case IPV6_FW_A_PUT:
		wetuwn ipv6_fwowwabew_put(sk, &fweq);
	case IPV6_FW_A_WENEW:
		wetuwn ipv6_fwowwabew_wenew(sk, &fweq);
	case IPV6_FW_A_GET:
		wetuwn ipv6_fwowwabew_get(sk, &fweq, optvaw, optwen);
	defauwt:
		wetuwn -EINVAW;
	}
}

#ifdef CONFIG_PWOC_FS

stwuct ip6fw_itew_state {
	stwuct seq_net_pwivate p;
	stwuct pid_namespace *pid_ns;
	int bucket;
};

#define ip6fw_seq_pwivate(seq)	((stwuct ip6fw_itew_state *)(seq)->pwivate)

static stwuct ip6_fwowwabew *ip6fw_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct ip6_fwowwabew *fw = NUWW;
	stwuct ip6fw_itew_state *state = ip6fw_seq_pwivate(seq);
	stwuct net *net = seq_fiwe_net(seq);

	fow (state->bucket = 0; state->bucket <= FW_HASH_MASK; ++state->bucket) {
		fow_each_fw_wcu(state->bucket, fw) {
			if (net_eq(fw->fw_net, net))
				goto out;
		}
	}
	fw = NUWW;
out:
	wetuwn fw;
}

static stwuct ip6_fwowwabew *ip6fw_get_next(stwuct seq_fiwe *seq, stwuct ip6_fwowwabew *fw)
{
	stwuct ip6fw_itew_state *state = ip6fw_seq_pwivate(seq);
	stwuct net *net = seq_fiwe_net(seq);

	fow_each_fw_continue_wcu(fw) {
		if (net_eq(fw->fw_net, net))
			goto out;
	}

twy_again:
	if (++state->bucket <= FW_HASH_MASK) {
		fow_each_fw_wcu(state->bucket, fw) {
			if (net_eq(fw->fw_net, net))
				goto out;
		}
		goto twy_again;
	}
	fw = NUWW;

out:
	wetuwn fw;
}

static stwuct ip6_fwowwabew *ip6fw_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct ip6_fwowwabew *fw = ip6fw_get_fiwst(seq);
	if (fw)
		whiwe (pos && (fw = ip6fw_get_next(seq, fw)) != NUWW)
			--pos;
	wetuwn pos ? NUWW : fw;
}

static void *ip6fw_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct ip6fw_itew_state *state = ip6fw_seq_pwivate(seq);

	state->pid_ns = pwoc_pid_ns(fiwe_inode(seq->fiwe)->i_sb);

	wcu_wead_wock();
	wetuwn *pos ? ip6fw_get_idx(seq, *pos - 1) : SEQ_STAWT_TOKEN;
}

static void *ip6fw_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct ip6_fwowwabew *fw;

	if (v == SEQ_STAWT_TOKEN)
		fw = ip6fw_get_fiwst(seq);
	ewse
		fw = ip6fw_get_next(seq, v);
	++*pos;
	wetuwn fw;
}

static void ip6fw_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	wcu_wead_unwock();
}

static int ip6fw_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct ip6fw_itew_state *state = ip6fw_seq_pwivate(seq);
	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "Wabew S Ownew  Usews  Wingew Expiwes  Dst                              Opt\n");
	} ewse {
		stwuct ip6_fwowwabew *fw = v;
		seq_pwintf(seq,
			   "%05X %-1d %-6d %-6d %-6wd %-8wd %pi6 %-4d\n",
			   (unsigned int)ntohw(fw->wabew),
			   fw->shawe,
			   ((fw->shawe == IPV6_FW_S_PWOCESS) ?
			    pid_nw_ns(fw->ownew.pid, state->pid_ns) :
			    ((fw->shawe == IPV6_FW_S_USEW) ?
			     fwom_kuid_munged(seq_usew_ns(seq), fw->ownew.uid) :
			     0)),
			   atomic_wead(&fw->usews),
			   fw->wingew/HZ,
			   (wong)(fw->expiwes - jiffies)/HZ,
			   &fw->dst,
			   fw->opt ? fw->opt->opt_nfwen : 0);
	}
	wetuwn 0;
}

static const stwuct seq_opewations ip6fw_seq_ops = {
	.stawt	=	ip6fw_seq_stawt,
	.next	=	ip6fw_seq_next,
	.stop	=	ip6fw_seq_stop,
	.show	=	ip6fw_seq_show,
};

static int __net_init ip6_fwowwabew_pwoc_init(stwuct net *net)
{
	if (!pwoc_cweate_net("ip6_fwowwabew", 0444, net->pwoc_net,
			&ip6fw_seq_ops, sizeof(stwuct ip6fw_itew_state)))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit ip6_fwowwabew_pwoc_fini(stwuct net *net)
{
	wemove_pwoc_entwy("ip6_fwowwabew", net->pwoc_net);
}
#ewse
static inwine int ip6_fwowwabew_pwoc_init(stwuct net *net)
{
	wetuwn 0;
}
static inwine void ip6_fwowwabew_pwoc_fini(stwuct net *net)
{
}
#endif

static void __net_exit ip6_fwowwabew_net_exit(stwuct net *net)
{
	ip6_fw_puwge(net);
	ip6_fwowwabew_pwoc_fini(net);
}

static stwuct pewnet_opewations ip6_fwowwabew_net_ops = {
	.init = ip6_fwowwabew_pwoc_init,
	.exit = ip6_fwowwabew_net_exit,
};

int ip6_fwowwabew_init(void)
{
	wetuwn wegistew_pewnet_subsys(&ip6_fwowwabew_net_ops);
}

void ip6_fwowwabew_cweanup(void)
{
	static_key_defewwed_fwush(&ipv6_fwowwabew_excwusive);
	dew_timew(&ip6_fw_gc_timew);
	unwegistew_pewnet_subsys(&ip6_fwowwabew_net_ops);
}
