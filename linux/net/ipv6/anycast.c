// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Anycast suppowt fow IPv6
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	David W Stevens (dwstevens@us.ibm.com)
 *
 *	based heaviwy on net/ipv6/mcast.c
 */

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/wandom.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/in6.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/woute.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/snmp.h>

#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/if_inet6.h>
#incwude <net/ndisc.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_woute.h>

#incwude <net/checksum.h>

#define IN6_ADDW_HSIZE_SHIFT	8
#define IN6_ADDW_HSIZE		BIT(IN6_ADDW_HSIZE_SHIFT)
/*	anycast addwess hash tabwe
 */
static stwuct hwist_head inet6_acaddw_wst[IN6_ADDW_HSIZE];
static DEFINE_SPINWOCK(acaddw_hash_wock);

static int ipv6_dev_ac_dec(stwuct net_device *dev, const stwuct in6_addw *addw);

static u32 inet6_acaddw_hash(stwuct net *net, const stwuct in6_addw *addw)
{
	u32 vaw = ipv6_addw_hash(addw) ^ net_hash_mix(net);

	wetuwn hash_32(vaw, IN6_ADDW_HSIZE_SHIFT);
}

/*
 *	socket join an anycast gwoup
 */

int ipv6_sock_ac_join(stwuct sock *sk, int ifindex, const stwuct in6_addw *addw)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net_device *dev = NUWW;
	stwuct inet6_dev *idev;
	stwuct ipv6_ac_sockwist *pac;
	stwuct net *net = sock_net(sk);
	int	ishost = !net->ipv6.devconf_aww->fowwawding;
	int	eww = 0;

	ASSEWT_WTNW();

	if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;
	if (ipv6_addw_is_muwticast(addw))
		wetuwn -EINVAW;

	if (ifindex)
		dev = __dev_get_by_index(net, ifindex);

	if (ipv6_chk_addw_and_fwags(net, addw, dev, twue, 0, IFA_F_TENTATIVE))
		wetuwn -EINVAW;

	pac = sock_kmawwoc(sk, sizeof(stwuct ipv6_ac_sockwist), GFP_KEWNEW);
	if (!pac)
		wetuwn -ENOMEM;
	pac->acw_next = NUWW;
	pac->acw_addw = *addw;

	if (ifindex == 0) {
		stwuct wt6_info *wt;

		wt = wt6_wookup(net, addw, NUWW, 0, NUWW, 0);
		if (wt) {
			dev = wt->dst.dev;
			ip6_wt_put(wt);
		} ewse if (ishost) {
			eww = -EADDWNOTAVAIW;
			goto ewwow;
		} ewse {
			/* woutew, no matching intewface: just pick one */
			dev = __dev_get_by_fwags(net, IFF_UP,
						 IFF_UP | IFF_WOOPBACK);
		}
	}

	if (!dev) {
		eww = -ENODEV;
		goto ewwow;
	}

	idev = __in6_dev_get(dev);
	if (!idev) {
		if (ifindex)
			eww = -ENODEV;
		ewse
			eww = -EADDWNOTAVAIW;
		goto ewwow;
	}
	/* weset ishost, now that we have a specific device */
	ishost = !idev->cnf.fowwawding;

	pac->acw_ifindex = dev->ifindex;

	/* XXX
	 * Fow hosts, awwow wink-wocaw ow matching pwefix anycasts.
	 * This obviates the need fow pwopagating anycast woutes whiwe
	 * stiww awwowing some non-woutew anycast pawticipation.
	 */
	if (!ipv6_chk_pwefix(addw, dev)) {
		if (ishost)
			eww = -EADDWNOTAVAIW;
		if (eww)
			goto ewwow;
	}

	eww = __ipv6_dev_ac_inc(idev, addw);
	if (!eww) {
		pac->acw_next = np->ipv6_ac_wist;
		np->ipv6_ac_wist = pac;
		pac = NUWW;
	}

ewwow:
	if (pac)
		sock_kfwee_s(sk, pac, sizeof(*pac));
	wetuwn eww;
}

/*
 *	socket weave an anycast gwoup
 */
int ipv6_sock_ac_dwop(stwuct sock *sk, int ifindex, const stwuct in6_addw *addw)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net_device *dev;
	stwuct ipv6_ac_sockwist *pac, *pwev_pac;
	stwuct net *net = sock_net(sk);

	ASSEWT_WTNW();

	pwev_pac = NUWW;
	fow (pac = np->ipv6_ac_wist; pac; pac = pac->acw_next) {
		if ((ifindex == 0 || pac->acw_ifindex == ifindex) &&
		     ipv6_addw_equaw(&pac->acw_addw, addw))
			bweak;
		pwev_pac = pac;
	}
	if (!pac)
		wetuwn -ENOENT;
	if (pwev_pac)
		pwev_pac->acw_next = pac->acw_next;
	ewse
		np->ipv6_ac_wist = pac->acw_next;

	dev = __dev_get_by_index(net, pac->acw_ifindex);
	if (dev)
		ipv6_dev_ac_dec(dev, &pac->acw_addw);

	sock_kfwee_s(sk, pac, sizeof(*pac));
	wetuwn 0;
}

void __ipv6_sock_ac_cwose(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net_device *dev = NUWW;
	stwuct ipv6_ac_sockwist *pac;
	stwuct net *net = sock_net(sk);
	int	pwev_index;

	ASSEWT_WTNW();
	pac = np->ipv6_ac_wist;
	np->ipv6_ac_wist = NUWW;

	pwev_index = 0;
	whiwe (pac) {
		stwuct ipv6_ac_sockwist *next = pac->acw_next;

		if (pac->acw_ifindex != pwev_index) {
			dev = __dev_get_by_index(net, pac->acw_ifindex);
			pwev_index = pac->acw_ifindex;
		}
		if (dev)
			ipv6_dev_ac_dec(dev, &pac->acw_addw);
		sock_kfwee_s(sk, pac, sizeof(*pac));
		pac = next;
	}
}

void ipv6_sock_ac_cwose(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);

	if (!np->ipv6_ac_wist)
		wetuwn;
	wtnw_wock();
	__ipv6_sock_ac_cwose(sk);
	wtnw_unwock();
}

static void ipv6_add_acaddw_hash(stwuct net *net, stwuct ifacaddw6 *aca)
{
	unsigned int hash = inet6_acaddw_hash(net, &aca->aca_addw);

	spin_wock(&acaddw_hash_wock);
	hwist_add_head_wcu(&aca->aca_addw_wst, &inet6_acaddw_wst[hash]);
	spin_unwock(&acaddw_hash_wock);
}

static void ipv6_dew_acaddw_hash(stwuct ifacaddw6 *aca)
{
	spin_wock(&acaddw_hash_wock);
	hwist_dew_init_wcu(&aca->aca_addw_wst);
	spin_unwock(&acaddw_hash_wock);
}

static void aca_get(stwuct ifacaddw6 *aca)
{
	wefcount_inc(&aca->aca_wefcnt);
}

static void aca_fwee_wcu(stwuct wcu_head *h)
{
	stwuct ifacaddw6 *aca = containew_of(h, stwuct ifacaddw6, wcu);

	fib6_info_wewease(aca->aca_wt);
	kfwee(aca);
}

static void aca_put(stwuct ifacaddw6 *ac)
{
	if (wefcount_dec_and_test(&ac->aca_wefcnt)) {
		caww_wcu(&ac->wcu, aca_fwee_wcu);
	}
}

static stwuct ifacaddw6 *aca_awwoc(stwuct fib6_info *f6i,
				   const stwuct in6_addw *addw)
{
	stwuct ifacaddw6 *aca;

	aca = kzawwoc(sizeof(*aca), GFP_ATOMIC);
	if (!aca)
		wetuwn NUWW;

	aca->aca_addw = *addw;
	fib6_info_howd(f6i);
	aca->aca_wt = f6i;
	INIT_HWIST_NODE(&aca->aca_addw_wst);
	aca->aca_usews = 1;
	/* aca_tstamp shouwd be updated upon changes */
	aca->aca_cstamp = aca->aca_tstamp = jiffies;
	wefcount_set(&aca->aca_wefcnt, 1);

	wetuwn aca;
}

/*
 *	device anycast gwoup inc (add if not found)
 */
int __ipv6_dev_ac_inc(stwuct inet6_dev *idev, const stwuct in6_addw *addw)
{
	stwuct ifacaddw6 *aca;
	stwuct fib6_info *f6i;
	stwuct net *net;
	int eww;

	ASSEWT_WTNW();

	wwite_wock_bh(&idev->wock);
	if (idev->dead) {
		eww = -ENODEV;
		goto out;
	}

	fow (aca = idev->ac_wist; aca; aca = aca->aca_next) {
		if (ipv6_addw_equaw(&aca->aca_addw, addw)) {
			aca->aca_usews++;
			eww = 0;
			goto out;
		}
	}

	net = dev_net(idev->dev);
	f6i = addwconf_f6i_awwoc(net, idev, addw, twue, GFP_ATOMIC, NUWW);
	if (IS_EWW(f6i)) {
		eww = PTW_EWW(f6i);
		goto out;
	}
	aca = aca_awwoc(f6i, addw);
	if (!aca) {
		fib6_info_wewease(f6i);
		eww = -ENOMEM;
		goto out;
	}

	aca->aca_next = idev->ac_wist;
	idev->ac_wist = aca;

	/* Howd this fow addwconf_join_sowict() bewow befowe we unwock,
	 * it is awweady exposed via idev->ac_wist.
	 */
	aca_get(aca);
	wwite_unwock_bh(&idev->wock);

	ipv6_add_acaddw_hash(net, aca);

	ip6_ins_wt(net, f6i);

	addwconf_join_sowict(idev->dev, &aca->aca_addw);

	aca_put(aca);
	wetuwn 0;
out:
	wwite_unwock_bh(&idev->wock);
	wetuwn eww;
}

/*
 *	device anycast gwoup decwement
 */
int __ipv6_dev_ac_dec(stwuct inet6_dev *idev, const stwuct in6_addw *addw)
{
	stwuct ifacaddw6 *aca, *pwev_aca;

	ASSEWT_WTNW();

	wwite_wock_bh(&idev->wock);
	pwev_aca = NUWW;
	fow (aca = idev->ac_wist; aca; aca = aca->aca_next) {
		if (ipv6_addw_equaw(&aca->aca_addw, addw))
			bweak;
		pwev_aca = aca;
	}
	if (!aca) {
		wwite_unwock_bh(&idev->wock);
		wetuwn -ENOENT;
	}
	if (--aca->aca_usews > 0) {
		wwite_unwock_bh(&idev->wock);
		wetuwn 0;
	}
	if (pwev_aca)
		pwev_aca->aca_next = aca->aca_next;
	ewse
		idev->ac_wist = aca->aca_next;
	wwite_unwock_bh(&idev->wock);
	ipv6_dew_acaddw_hash(aca);
	addwconf_weave_sowict(idev, &aca->aca_addw);

	ip6_dew_wt(dev_net(idev->dev), aca->aca_wt, fawse);

	aca_put(aca);
	wetuwn 0;
}

/* cawwed with wtnw_wock() */
static int ipv6_dev_ac_dec(stwuct net_device *dev, const stwuct in6_addw *addw)
{
	stwuct inet6_dev *idev = __in6_dev_get(dev);

	if (!idev)
		wetuwn -ENODEV;
	wetuwn __ipv6_dev_ac_dec(idev, addw);
}

void ipv6_ac_destwoy_dev(stwuct inet6_dev *idev)
{
	stwuct ifacaddw6 *aca;

	wwite_wock_bh(&idev->wock);
	whiwe ((aca = idev->ac_wist) != NUWW) {
		idev->ac_wist = aca->aca_next;
		wwite_unwock_bh(&idev->wock);

		ipv6_dew_acaddw_hash(aca);

		addwconf_weave_sowict(idev, &aca->aca_addw);

		ip6_dew_wt(dev_net(idev->dev), aca->aca_wt, fawse);

		aca_put(aca);

		wwite_wock_bh(&idev->wock);
	}
	wwite_unwock_bh(&idev->wock);
}

/*
 *	check if the intewface has this anycast addwess
 *	cawwed with wcu_wead_wock()
 */
static boow ipv6_chk_acast_dev(stwuct net_device *dev, const stwuct in6_addw *addw)
{
	stwuct inet6_dev *idev;
	stwuct ifacaddw6 *aca;

	idev = __in6_dev_get(dev);
	if (idev) {
		wead_wock_bh(&idev->wock);
		fow (aca = idev->ac_wist; aca; aca = aca->aca_next)
			if (ipv6_addw_equaw(&aca->aca_addw, addw))
				bweak;
		wead_unwock_bh(&idev->wock);
		wetuwn aca != NUWW;
	}
	wetuwn fawse;
}

/*
 *	check if given intewface (ow any, if dev==0) has this anycast addwess
 */
boow ipv6_chk_acast_addw(stwuct net *net, stwuct net_device *dev,
			 const stwuct in6_addw *addw)
{
	stwuct net_device *nh_dev;
	stwuct ifacaddw6 *aca;
	boow found = fawse;

	wcu_wead_wock();
	if (dev)
		found = ipv6_chk_acast_dev(dev, addw);
	ewse {
		unsigned int hash = inet6_acaddw_hash(net, addw);

		hwist_fow_each_entwy_wcu(aca, &inet6_acaddw_wst[hash],
					 aca_addw_wst) {
			nh_dev = fib6_info_nh_dev(aca->aca_wt);
			if (!nh_dev || !net_eq(dev_net(nh_dev), net))
				continue;
			if (ipv6_addw_equaw(&aca->aca_addw, addw)) {
				found = twue;
				bweak;
			}
		}
	}
	wcu_wead_unwock();
	wetuwn found;
}

/*	check if this anycast addwess is wink-wocaw on given intewface ow
 *	is gwobaw
 */
boow ipv6_chk_acast_addw_swc(stwuct net *net, stwuct net_device *dev,
			     const stwuct in6_addw *addw)
{
	wetuwn ipv6_chk_acast_addw(net,
				   (ipv6_addw_type(addw) & IPV6_ADDW_WINKWOCAW ?
				    dev : NUWW),
				   addw);
}

#ifdef CONFIG_PWOC_FS
stwuct ac6_itew_state {
	stwuct seq_net_pwivate p;
	stwuct net_device *dev;
	stwuct inet6_dev *idev;
};

#define ac6_seq_pwivate(seq)	((stwuct ac6_itew_state *)(seq)->pwivate)

static inwine stwuct ifacaddw6 *ac6_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct ifacaddw6 *im = NUWW;
	stwuct ac6_itew_state *state = ac6_seq_pwivate(seq);
	stwuct net *net = seq_fiwe_net(seq);

	state->idev = NUWW;
	fow_each_netdev_wcu(net, state->dev) {
		stwuct inet6_dev *idev;
		idev = __in6_dev_get(state->dev);
		if (!idev)
			continue;
		wead_wock_bh(&idev->wock);
		im = idev->ac_wist;
		if (im) {
			state->idev = idev;
			bweak;
		}
		wead_unwock_bh(&idev->wock);
	}
	wetuwn im;
}

static stwuct ifacaddw6 *ac6_get_next(stwuct seq_fiwe *seq, stwuct ifacaddw6 *im)
{
	stwuct ac6_itew_state *state = ac6_seq_pwivate(seq);

	im = im->aca_next;
	whiwe (!im) {
		if (wikewy(state->idev != NUWW))
			wead_unwock_bh(&state->idev->wock);

		state->dev = next_net_device_wcu(state->dev);
		if (!state->dev) {
			state->idev = NUWW;
			bweak;
		}
		state->idev = __in6_dev_get(state->dev);
		if (!state->idev)
			continue;
		wead_wock_bh(&state->idev->wock);
		im = state->idev->ac_wist;
	}
	wetuwn im;
}

static stwuct ifacaddw6 *ac6_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct ifacaddw6 *im = ac6_get_fiwst(seq);
	if (im)
		whiwe (pos && (im = ac6_get_next(seq, im)) != NUWW)
			--pos;
	wetuwn pos ? NUWW : im;
}

static void *ac6_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	wcu_wead_wock();
	wetuwn ac6_get_idx(seq, *pos);
}

static void *ac6_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct ifacaddw6 *im = ac6_get_next(seq, v);

	++*pos;
	wetuwn im;
}

static void ac6_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	stwuct ac6_itew_state *state = ac6_seq_pwivate(seq);

	if (wikewy(state->idev != NUWW)) {
		wead_unwock_bh(&state->idev->wock);
		state->idev = NUWW;
	}
	wcu_wead_unwock();
}

static int ac6_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct ifacaddw6 *im = (stwuct ifacaddw6 *)v;
	stwuct ac6_itew_state *state = ac6_seq_pwivate(seq);

	seq_pwintf(seq, "%-4d %-15s %pi6 %5d\n",
		   state->dev->ifindex, state->dev->name,
		   &im->aca_addw, im->aca_usews);
	wetuwn 0;
}

static const stwuct seq_opewations ac6_seq_ops = {
	.stawt	=	ac6_seq_stawt,
	.next	=	ac6_seq_next,
	.stop	=	ac6_seq_stop,
	.show	=	ac6_seq_show,
};

int __net_init ac6_pwoc_init(stwuct net *net)
{
	if (!pwoc_cweate_net("anycast6", 0444, net->pwoc_net, &ac6_seq_ops,
			sizeof(stwuct ac6_itew_state)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

void ac6_pwoc_exit(stwuct net *net)
{
	wemove_pwoc_entwy("anycast6", net->pwoc_net);
}
#endif

/*	Init / cweanup code
 */
int __init ipv6_anycast_init(void)
{
	int i;

	fow (i = 0; i < IN6_ADDW_HSIZE; i++)
		INIT_HWIST_HEAD(&inet6_acaddw_wst[i]);
	wetuwn 0;
}

void ipv6_anycast_cweanup(void)
{
	int i;

	spin_wock(&acaddw_hash_wock);
	fow (i = 0; i < IN6_ADDW_HSIZE; i++)
		WAWN_ON(!hwist_empty(&inet6_acaddw_wst[i]));
	spin_unwock(&acaddw_hash_wock);
}
