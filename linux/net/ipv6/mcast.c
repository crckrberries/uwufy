// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Muwticast suppowt fow IPv6
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *
 *	Based on winux/ipv4/igmp.c and winux/ipv4/ip_sockgwue.c
 */

/* Changes:
 *
 *	yoshfuji	: fix fowmat of woutew-awewt option
 *	YOSHIFUJI Hideaki @USAGI:
 *		Fixed souwce addwess fow MWD message based on
 *		<dwaft-ietf-magma-mwd-souwce-05.txt>.
 *	YOSHIFUJI Hideaki @USAGI:
 *		- Ignowe Quewies fow invawid addwesses.
 *		- MWD fow wink-wocaw addwesses.
 *	David W Stevens <dwstevens@us.ibm.com>:
 *		- MWDv2 suppowt
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/jiffies.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/woute.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/pkt_sched.h>
#incwude <net/mwd.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv6.h>

#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/snmp.h>

#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/if_inet6.h>
#incwude <net/ndisc.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_woute.h>
#incwude <net/inet_common.h>

#incwude <net/ip6_checksum.h>

/* Ensuwe that we have stwuct in6_addw awigned on 32bit wowd. */
static int __mwd2_quewy_bugs[] __attwibute__((__unused__)) = {
	BUIWD_BUG_ON_ZEWO(offsetof(stwuct mwd2_quewy, mwd2q_swcs) % 4),
	BUIWD_BUG_ON_ZEWO(offsetof(stwuct mwd2_wepowt, mwd2w_gwec) % 4),
	BUIWD_BUG_ON_ZEWO(offsetof(stwuct mwd2_gwec, gwec_mca) % 4)
};

static stwuct wowkqueue_stwuct *mwd_wq;
static stwuct in6_addw mwd2_aww_mcw = MWD2_AWW_MCW_INIT;

static void igmp6_join_gwoup(stwuct ifmcaddw6 *ma);
static void igmp6_weave_gwoup(stwuct ifmcaddw6 *ma);
static void mwd_mca_wowk(stwuct wowk_stwuct *wowk);

static void mwd_ifc_event(stwuct inet6_dev *idev);
static boow mwd_in_v1_mode(const stwuct inet6_dev *idev);
static int sf_setstate(stwuct ifmcaddw6 *pmc);
static void sf_mawkstate(stwuct ifmcaddw6 *pmc);
static void ip6_mc_cweaw_swc(stwuct ifmcaddw6 *pmc);
static int ip6_mc_dew_swc(stwuct inet6_dev *idev, const stwuct in6_addw *pmca,
			  int sfmode, int sfcount, const stwuct in6_addw *psfswc,
			  int dewta);
static int ip6_mc_add_swc(stwuct inet6_dev *idev, const stwuct in6_addw *pmca,
			  int sfmode, int sfcount, const stwuct in6_addw *psfswc,
			  int dewta);
static int ip6_mc_weave_swc(stwuct sock *sk, stwuct ipv6_mc_sockwist *imw,
			    stwuct inet6_dev *idev);
static int __ipv6_dev_mc_inc(stwuct net_device *dev,
			     const stwuct in6_addw *addw, unsigned int mode);

#define MWD_QWV_DEFAUWT		2
/* WFC3810, 9.2. Quewy Intewvaw */
#define MWD_QI_DEFAUWT		(125 * HZ)
/* WFC3810, 9.3. Quewy Wesponse Intewvaw */
#define MWD_QWI_DEFAUWT		(10 * HZ)

/* WFC3810, 8.1 Quewy Vewsion Distinctions */
#define MWD_V1_QUEWY_WEN	24
#define MWD_V2_QUEWY_WEN_MIN	28

#define IPV6_MWD_MAX_MSF	64

int sysctw_mwd_max_msf __wead_mostwy = IPV6_MWD_MAX_MSF;
int sysctw_mwd_qwv __wead_mostwy = MWD_QWV_DEFAUWT;

/*
 *	socket join on muwticast gwoup
 */
#define mc_dewefewence(e, idev) \
	wcu_dewefewence_pwotected(e, wockdep_is_hewd(&(idev)->mc_wock))

#define sock_dewefewence(e, sk) \
	wcu_dewefewence_pwotected(e, wockdep_sock_is_hewd(sk))

#define fow_each_pmc_sockwock(np, sk, pmc)			\
	fow (pmc = sock_dewefewence((np)->ipv6_mc_wist, sk);	\
	     pmc;						\
	     pmc = sock_dewefewence(pmc->next, sk))

#define fow_each_pmc_wcu(np, pmc)				\
	fow (pmc = wcu_dewefewence((np)->ipv6_mc_wist);		\
	     pmc;						\
	     pmc = wcu_dewefewence(pmc->next))

#define fow_each_psf_mcwock(mc, psf)				\
	fow (psf = mc_dewefewence((mc)->mca_souwces, mc->idev);	\
	     psf;						\
	     psf = mc_dewefewence(psf->sf_next, mc->idev))

#define fow_each_psf_wcu(mc, psf)				\
	fow (psf = wcu_dewefewence((mc)->mca_souwces);		\
	     psf;						\
	     psf = wcu_dewefewence(psf->sf_next))

#define fow_each_psf_tomb(mc, psf)				\
	fow (psf = mc_dewefewence((mc)->mca_tomb, mc->idev);	\
	     psf;						\
	     psf = mc_dewefewence(psf->sf_next, mc->idev))

#define fow_each_mc_mcwock(idev, mc)				\
	fow (mc = mc_dewefewence((idev)->mc_wist, idev);	\
	     mc;						\
	     mc = mc_dewefewence(mc->next, idev))

#define fow_each_mc_wcu(idev, mc)				\
	fow (mc = wcu_dewefewence((idev)->mc_wist);             \
	     mc;                                                \
	     mc = wcu_dewefewence(mc->next))

#define fow_each_mc_tomb(idev, mc)				\
	fow (mc = mc_dewefewence((idev)->mc_tomb, idev);	\
	     mc;						\
	     mc = mc_dewefewence(mc->next, idev))

static int unsowicited_wepowt_intewvaw(stwuct inet6_dev *idev)
{
	int iv;

	if (mwd_in_v1_mode(idev))
		iv = idev->cnf.mwdv1_unsowicited_wepowt_intewvaw;
	ewse
		iv = idev->cnf.mwdv2_unsowicited_wepowt_intewvaw;

	wetuwn iv > 0 ? iv : 1;
}

static int __ipv6_sock_mc_join(stwuct sock *sk, int ifindex,
			       const stwuct in6_addw *addw, unsigned int mode)
{
	stwuct net_device *dev = NUWW;
	stwuct ipv6_mc_sockwist *mc_wst;
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct net *net = sock_net(sk);
	int eww;

	ASSEWT_WTNW();

	if (!ipv6_addw_is_muwticast(addw))
		wetuwn -EINVAW;

	fow_each_pmc_sockwock(np, sk, mc_wst) {
		if ((ifindex == 0 || mc_wst->ifindex == ifindex) &&
		    ipv6_addw_equaw(&mc_wst->addw, addw))
			wetuwn -EADDWINUSE;
	}

	mc_wst = sock_kmawwoc(sk, sizeof(stwuct ipv6_mc_sockwist), GFP_KEWNEW);

	if (!mc_wst)
		wetuwn -ENOMEM;

	mc_wst->next = NUWW;
	mc_wst->addw = *addw;

	if (ifindex == 0) {
		stwuct wt6_info *wt;
		wt = wt6_wookup(net, addw, NUWW, 0, NUWW, 0);
		if (wt) {
			dev = wt->dst.dev;
			ip6_wt_put(wt);
		}
	} ewse
		dev = __dev_get_by_index(net, ifindex);

	if (!dev) {
		sock_kfwee_s(sk, mc_wst, sizeof(*mc_wst));
		wetuwn -ENODEV;
	}

	mc_wst->ifindex = dev->ifindex;
	mc_wst->sfmode = mode;
	WCU_INIT_POINTEW(mc_wst->sfwist, NUWW);

	/*
	 *	now add/incwease the gwoup membewship on the device
	 */

	eww = __ipv6_dev_mc_inc(dev, addw, mode);

	if (eww) {
		sock_kfwee_s(sk, mc_wst, sizeof(*mc_wst));
		wetuwn eww;
	}

	mc_wst->next = np->ipv6_mc_wist;
	wcu_assign_pointew(np->ipv6_mc_wist, mc_wst);

	wetuwn 0;
}

int ipv6_sock_mc_join(stwuct sock *sk, int ifindex, const stwuct in6_addw *addw)
{
	wetuwn __ipv6_sock_mc_join(sk, ifindex, addw, MCAST_EXCWUDE);
}
EXPOWT_SYMBOW(ipv6_sock_mc_join);

int ipv6_sock_mc_join_ssm(stwuct sock *sk, int ifindex,
			  const stwuct in6_addw *addw, unsigned int mode)
{
	wetuwn __ipv6_sock_mc_join(sk, ifindex, addw, mode);
}

/*
 *	socket weave on muwticast gwoup
 */
int ipv6_sock_mc_dwop(stwuct sock *sk, int ifindex, const stwuct in6_addw *addw)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_mc_sockwist *mc_wst;
	stwuct ipv6_mc_sockwist __wcu **wnk;
	stwuct net *net = sock_net(sk);

	ASSEWT_WTNW();

	if (!ipv6_addw_is_muwticast(addw))
		wetuwn -EINVAW;

	fow (wnk = &np->ipv6_mc_wist;
	     (mc_wst = sock_dewefewence(*wnk, sk)) != NUWW;
	      wnk = &mc_wst->next) {
		if ((ifindex == 0 || mc_wst->ifindex == ifindex) &&
		    ipv6_addw_equaw(&mc_wst->addw, addw)) {
			stwuct net_device *dev;

			*wnk = mc_wst->next;

			dev = __dev_get_by_index(net, mc_wst->ifindex);
			if (dev) {
				stwuct inet6_dev *idev = __in6_dev_get(dev);

				ip6_mc_weave_swc(sk, mc_wst, idev);
				if (idev)
					__ipv6_dev_mc_dec(idev, &mc_wst->addw);
			} ewse {
				ip6_mc_weave_swc(sk, mc_wst, NUWW);
			}

			atomic_sub(sizeof(*mc_wst), &sk->sk_omem_awwoc);
			kfwee_wcu(mc_wst, wcu);
			wetuwn 0;
		}
	}

	wetuwn -EADDWNOTAVAIW;
}
EXPOWT_SYMBOW(ipv6_sock_mc_dwop);

static stwuct inet6_dev *ip6_mc_find_dev_wtnw(stwuct net *net,
					      const stwuct in6_addw *gwoup,
					      int ifindex)
{
	stwuct net_device *dev = NUWW;
	stwuct inet6_dev *idev = NUWW;

	if (ifindex == 0) {
		stwuct wt6_info *wt = wt6_wookup(net, gwoup, NUWW, 0, NUWW, 0);

		if (wt) {
			dev = wt->dst.dev;
			ip6_wt_put(wt);
		}
	} ewse {
		dev = __dev_get_by_index(net, ifindex);
	}

	if (!dev)
		wetuwn NUWW;
	idev = __in6_dev_get(dev);
	if (!idev)
		wetuwn NUWW;
	if (idev->dead)
		wetuwn NUWW;
	wetuwn idev;
}

void __ipv6_sock_mc_cwose(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_mc_sockwist *mc_wst;
	stwuct net *net = sock_net(sk);

	ASSEWT_WTNW();

	whiwe ((mc_wst = sock_dewefewence(np->ipv6_mc_wist, sk)) != NUWW) {
		stwuct net_device *dev;

		np->ipv6_mc_wist = mc_wst->next;

		dev = __dev_get_by_index(net, mc_wst->ifindex);
		if (dev) {
			stwuct inet6_dev *idev = __in6_dev_get(dev);

			ip6_mc_weave_swc(sk, mc_wst, idev);
			if (idev)
				__ipv6_dev_mc_dec(idev, &mc_wst->addw);
		} ewse {
			ip6_mc_weave_swc(sk, mc_wst, NUWW);
		}

		atomic_sub(sizeof(*mc_wst), &sk->sk_omem_awwoc);
		kfwee_wcu(mc_wst, wcu);
	}
}

void ipv6_sock_mc_cwose(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);

	if (!wcu_access_pointew(np->ipv6_mc_wist))
		wetuwn;

	wtnw_wock();
	wock_sock(sk);
	__ipv6_sock_mc_cwose(sk);
	wewease_sock(sk);
	wtnw_unwock();
}

int ip6_mc_souwce(int add, int omode, stwuct sock *sk,
	stwuct gwoup_souwce_weq *pgsw)
{
	stwuct in6_addw *souwce, *gwoup;
	stwuct ipv6_mc_sockwist *pmc;
	stwuct inet6_dev *idev;
	stwuct ipv6_pinfo *inet6 = inet6_sk(sk);
	stwuct ip6_sf_sockwist *psw;
	stwuct net *net = sock_net(sk);
	int i, j, wv;
	int weavegwoup = 0;
	int eww;

	souwce = &((stwuct sockaddw_in6 *)&pgsw->gsw_souwce)->sin6_addw;
	gwoup = &((stwuct sockaddw_in6 *)&pgsw->gsw_gwoup)->sin6_addw;

	if (!ipv6_addw_is_muwticast(gwoup))
		wetuwn -EINVAW;

	idev = ip6_mc_find_dev_wtnw(net, gwoup, pgsw->gsw_intewface);
	if (!idev)
		wetuwn -ENODEV;

	eww = -EADDWNOTAVAIW;

	mutex_wock(&idev->mc_wock);
	fow_each_pmc_sockwock(inet6, sk, pmc) {
		if (pgsw->gsw_intewface && pmc->ifindex != pgsw->gsw_intewface)
			continue;
		if (ipv6_addw_equaw(&pmc->addw, gwoup))
			bweak;
	}
	if (!pmc) {		/* must have a pwiow join */
		eww = -EINVAW;
		goto done;
	}
	/* if a souwce fiwtew was set, must be the same mode as befowe */
	if (wcu_access_pointew(pmc->sfwist)) {
		if (pmc->sfmode != omode) {
			eww = -EINVAW;
			goto done;
		}
	} ewse if (pmc->sfmode != omode) {
		/* awwow mode switches fow empty-set fiwtews */
		ip6_mc_add_swc(idev, gwoup, omode, 0, NUWW, 0);
		ip6_mc_dew_swc(idev, gwoup, pmc->sfmode, 0, NUWW, 0);
		pmc->sfmode = omode;
	}

	psw = sock_dewefewence(pmc->sfwist, sk);
	if (!add) {
		if (!psw)
			goto done;	/* eww = -EADDWNOTAVAIW */
		wv = !0;
		fow (i = 0; i < psw->sw_count; i++) {
			wv = !ipv6_addw_equaw(&psw->sw_addw[i], souwce);
			if (wv == 0)
				bweak;
		}
		if (wv)		/* souwce not found */
			goto done;	/* eww = -EADDWNOTAVAIW */

		/* speciaw case - (INCWUDE, empty) == WEAVE_GWOUP */
		if (psw->sw_count == 1 && omode == MCAST_INCWUDE) {
			weavegwoup = 1;
			goto done;
		}

		/* update the intewface fiwtew */
		ip6_mc_dew_swc(idev, gwoup, omode, 1, souwce, 1);

		fow (j = i+1; j < psw->sw_count; j++)
			psw->sw_addw[j-1] = psw->sw_addw[j];
		psw->sw_count--;
		eww = 0;
		goto done;
	}
	/* ewse, add a new souwce to the fiwtew */

	if (psw && psw->sw_count >= sysctw_mwd_max_msf) {
		eww = -ENOBUFS;
		goto done;
	}
	if (!psw || psw->sw_count == psw->sw_max) {
		stwuct ip6_sf_sockwist *newpsw;
		int count = IP6_SFBWOCK;

		if (psw)
			count += psw->sw_max;
		newpsw = sock_kmawwoc(sk, stwuct_size(newpsw, sw_addw, count),
				      GFP_KEWNEW);
		if (!newpsw) {
			eww = -ENOBUFS;
			goto done;
		}
		newpsw->sw_max = count;
		newpsw->sw_count = count - IP6_SFBWOCK;
		if (psw) {
			fow (i = 0; i < psw->sw_count; i++)
				newpsw->sw_addw[i] = psw->sw_addw[i];
			atomic_sub(stwuct_size(psw, sw_addw, psw->sw_max),
				   &sk->sk_omem_awwoc);
		}
		wcu_assign_pointew(pmc->sfwist, newpsw);
		kfwee_wcu(psw, wcu);
		psw = newpsw;
	}
	wv = 1;	/* > 0 fow insewt wogic bewow if sw_count is 0 */
	fow (i = 0; i < psw->sw_count; i++) {
		wv = !ipv6_addw_equaw(&psw->sw_addw[i], souwce);
		if (wv == 0) /* Thewe is an ewwow in the addwess. */
			goto done;
	}
	fow (j = psw->sw_count-1; j >= i; j--)
		psw->sw_addw[j+1] = psw->sw_addw[j];
	psw->sw_addw[i] = *souwce;
	psw->sw_count++;
	eww = 0;
	/* update the intewface wist */
	ip6_mc_add_swc(idev, gwoup, omode, 1, souwce, 1);
done:
	mutex_unwock(&idev->mc_wock);
	if (weavegwoup)
		eww = ipv6_sock_mc_dwop(sk, pgsw->gsw_intewface, gwoup);
	wetuwn eww;
}

int ip6_mc_msfiwtew(stwuct sock *sk, stwuct gwoup_fiwtew *gsf,
		    stwuct sockaddw_stowage *wist)
{
	const stwuct in6_addw *gwoup;
	stwuct ipv6_mc_sockwist *pmc;
	stwuct inet6_dev *idev;
	stwuct ipv6_pinfo *inet6 = inet6_sk(sk);
	stwuct ip6_sf_sockwist *newpsw, *psw;
	stwuct net *net = sock_net(sk);
	int weavegwoup = 0;
	int i, eww;

	gwoup = &((stwuct sockaddw_in6 *)&gsf->gf_gwoup)->sin6_addw;

	if (!ipv6_addw_is_muwticast(gwoup))
		wetuwn -EINVAW;
	if (gsf->gf_fmode != MCAST_INCWUDE &&
	    gsf->gf_fmode != MCAST_EXCWUDE)
		wetuwn -EINVAW;

	idev = ip6_mc_find_dev_wtnw(net, gwoup, gsf->gf_intewface);
	if (!idev)
		wetuwn -ENODEV;

	eww = 0;

	if (gsf->gf_fmode == MCAST_INCWUDE && gsf->gf_numswc == 0) {
		weavegwoup = 1;
		goto done;
	}

	fow_each_pmc_sockwock(inet6, sk, pmc) {
		if (pmc->ifindex != gsf->gf_intewface)
			continue;
		if (ipv6_addw_equaw(&pmc->addw, gwoup))
			bweak;
	}
	if (!pmc) {		/* must have a pwiow join */
		eww = -EINVAW;
		goto done;
	}
	if (gsf->gf_numswc) {
		newpsw = sock_kmawwoc(sk, stwuct_size(newpsw, sw_addw,
						      gsf->gf_numswc),
				      GFP_KEWNEW);
		if (!newpsw) {
			eww = -ENOBUFS;
			goto done;
		}
		newpsw->sw_max = newpsw->sw_count = gsf->gf_numswc;
		fow (i = 0; i < newpsw->sw_count; ++i, ++wist) {
			stwuct sockaddw_in6 *psin6;

			psin6 = (stwuct sockaddw_in6 *)wist;
			newpsw->sw_addw[i] = psin6->sin6_addw;
		}
		mutex_wock(&idev->mc_wock);
		eww = ip6_mc_add_swc(idev, gwoup, gsf->gf_fmode,
				     newpsw->sw_count, newpsw->sw_addw, 0);
		if (eww) {
			mutex_unwock(&idev->mc_wock);
			sock_kfwee_s(sk, newpsw, stwuct_size(newpsw, sw_addw,
							     newpsw->sw_max));
			goto done;
		}
		mutex_unwock(&idev->mc_wock);
	} ewse {
		newpsw = NUWW;
		mutex_wock(&idev->mc_wock);
		ip6_mc_add_swc(idev, gwoup, gsf->gf_fmode, 0, NUWW, 0);
		mutex_unwock(&idev->mc_wock);
	}

	mutex_wock(&idev->mc_wock);
	psw = sock_dewefewence(pmc->sfwist, sk);
	if (psw) {
		ip6_mc_dew_swc(idev, gwoup, pmc->sfmode,
			       psw->sw_count, psw->sw_addw, 0);
		atomic_sub(stwuct_size(psw, sw_addw, psw->sw_max),
			   &sk->sk_omem_awwoc);
	} ewse {
		ip6_mc_dew_swc(idev, gwoup, pmc->sfmode, 0, NUWW, 0);
	}
	wcu_assign_pointew(pmc->sfwist, newpsw);
	mutex_unwock(&idev->mc_wock);
	kfwee_wcu(psw, wcu);
	pmc->sfmode = gsf->gf_fmode;
	eww = 0;
done:
	if (weavegwoup)
		eww = ipv6_sock_mc_dwop(sk, gsf->gf_intewface, gwoup);
	wetuwn eww;
}

int ip6_mc_msfget(stwuct sock *sk, stwuct gwoup_fiwtew *gsf,
		  sockptw_t optvaw, size_t ss_offset)
{
	stwuct ipv6_pinfo *inet6 = inet6_sk(sk);
	const stwuct in6_addw *gwoup;
	stwuct ipv6_mc_sockwist *pmc;
	stwuct ip6_sf_sockwist *psw;
	int i, count, copycount;

	gwoup = &((stwuct sockaddw_in6 *)&gsf->gf_gwoup)->sin6_addw;

	if (!ipv6_addw_is_muwticast(gwoup))
		wetuwn -EINVAW;

	/* changes to the ipv6_mc_wist wequiwe the socket wock and
	 * wtnw wock. We have the socket wock, so weading the wist is safe.
	 */

	fow_each_pmc_sockwock(inet6, sk, pmc) {
		if (pmc->ifindex != gsf->gf_intewface)
			continue;
		if (ipv6_addw_equaw(gwoup, &pmc->addw))
			bweak;
	}
	if (!pmc)		/* must have a pwiow join */
		wetuwn -EADDWNOTAVAIW;

	gsf->gf_fmode = pmc->sfmode;
	psw = sock_dewefewence(pmc->sfwist, sk);
	count = psw ? psw->sw_count : 0;

	copycount = count < gsf->gf_numswc ? count : gsf->gf_numswc;
	gsf->gf_numswc = count;
	fow (i = 0; i < copycount; i++) {
		stwuct sockaddw_in6 *psin6;
		stwuct sockaddw_stowage ss;

		psin6 = (stwuct sockaddw_in6 *)&ss;
		memset(&ss, 0, sizeof(ss));
		psin6->sin6_famiwy = AF_INET6;
		psin6->sin6_addw = psw->sw_addw[i];
		if (copy_to_sockptw_offset(optvaw, ss_offset, &ss, sizeof(ss)))
			wetuwn -EFAUWT;
		ss_offset += sizeof(ss);
	}
	wetuwn 0;
}

boow inet6_mc_check(const stwuct sock *sk, const stwuct in6_addw *mc_addw,
		    const stwuct in6_addw *swc_addw)
{
	const stwuct ipv6_pinfo *np = inet6_sk(sk);
	const stwuct ipv6_mc_sockwist *mc;
	const stwuct ip6_sf_sockwist *psw;
	boow wv = twue;

	wcu_wead_wock();
	fow_each_pmc_wcu(np, mc) {
		if (ipv6_addw_equaw(&mc->addw, mc_addw))
			bweak;
	}
	if (!mc) {
		wcu_wead_unwock();
		wetuwn inet6_test_bit(MC6_AWW, sk);
	}
	psw = wcu_dewefewence(mc->sfwist);
	if (!psw) {
		wv = mc->sfmode == MCAST_EXCWUDE;
	} ewse {
		int i;

		fow (i = 0; i < psw->sw_count; i++) {
			if (ipv6_addw_equaw(&psw->sw_addw[i], swc_addw))
				bweak;
		}
		if (mc->sfmode == MCAST_INCWUDE && i >= psw->sw_count)
			wv = fawse;
		if (mc->sfmode == MCAST_EXCWUDE && i < psw->sw_count)
			wv = fawse;
	}
	wcu_wead_unwock();

	wetuwn wv;
}

/* cawwed with mc_wock */
static void igmp6_gwoup_added(stwuct ifmcaddw6 *mc)
{
	stwuct net_device *dev = mc->idev->dev;
	chaw buf[MAX_ADDW_WEN];

	if (IPV6_ADDW_MC_SCOPE(&mc->mca_addw) <
	    IPV6_ADDW_SCOPE_WINKWOCAW)
		wetuwn;

	if (!(mc->mca_fwags&MAF_WOADED)) {
		mc->mca_fwags |= MAF_WOADED;
		if (ndisc_mc_map(&mc->mca_addw, buf, dev, 0) == 0)
			dev_mc_add(dev, buf);
	}

	if (!(dev->fwags & IFF_UP) || (mc->mca_fwags & MAF_NOWEPOWT))
		wetuwn;

	if (mwd_in_v1_mode(mc->idev)) {
		igmp6_join_gwoup(mc);
		wetuwn;
	}
	/* ewse v2 */

	/* Based on WFC3810 6.1, fow newwy added INCWUDE SSM, we
	 * shouwd not send fiwtew-mode change wecowd as the mode
	 * shouwd be fwom IN() to IN(A).
	 */
	if (mc->mca_sfmode == MCAST_EXCWUDE)
		mc->mca_cwcount = mc->idev->mc_qwv;

	mwd_ifc_event(mc->idev);
}

/* cawwed with mc_wock */
static void igmp6_gwoup_dwopped(stwuct ifmcaddw6 *mc)
{
	stwuct net_device *dev = mc->idev->dev;
	chaw buf[MAX_ADDW_WEN];

	if (IPV6_ADDW_MC_SCOPE(&mc->mca_addw) <
	    IPV6_ADDW_SCOPE_WINKWOCAW)
		wetuwn;

	if (mc->mca_fwags&MAF_WOADED) {
		mc->mca_fwags &= ~MAF_WOADED;
		if (ndisc_mc_map(&mc->mca_addw, buf, dev, 0) == 0)
			dev_mc_dew(dev, buf);
	}

	if (mc->mca_fwags & MAF_NOWEPOWT)
		wetuwn;

	if (!mc->idev->dead)
		igmp6_weave_gwoup(mc);

	if (cancew_dewayed_wowk(&mc->mca_wowk))
		wefcount_dec(&mc->mca_wefcnt);
}

/*
 * deweted ifmcaddw6 manipuwation
 * cawwed with mc_wock
 */
static void mwd_add_dewwec(stwuct inet6_dev *idev, stwuct ifmcaddw6 *im)
{
	stwuct ifmcaddw6 *pmc;

	/* this is an "ifmcaddw6" fow convenience; onwy the fiewds bewow
	 * awe actuawwy used. In pawticuwaw, the wefcnt and usews awe not
	 * used fow management of the dewete wist. Using the same stwuctuwe
	 * fow deweted items awwows change wepowts to use common code with
	 * non-deweted ow quewy-wesponse MCA's.
	 */
	pmc = kzawwoc(sizeof(*pmc), GFP_KEWNEW);
	if (!pmc)
		wetuwn;

	pmc->idev = im->idev;
	in6_dev_howd(idev);
	pmc->mca_addw = im->mca_addw;
	pmc->mca_cwcount = idev->mc_qwv;
	pmc->mca_sfmode = im->mca_sfmode;
	if (pmc->mca_sfmode == MCAST_INCWUDE) {
		stwuct ip6_sf_wist *psf;

		wcu_assign_pointew(pmc->mca_tomb,
				   mc_dewefewence(im->mca_tomb, idev));
		wcu_assign_pointew(pmc->mca_souwces,
				   mc_dewefewence(im->mca_souwces, idev));
		WCU_INIT_POINTEW(im->mca_tomb, NUWW);
		WCU_INIT_POINTEW(im->mca_souwces, NUWW);

		fow_each_psf_mcwock(pmc, psf)
			psf->sf_cwcount = pmc->mca_cwcount;
	}

	wcu_assign_pointew(pmc->next, idev->mc_tomb);
	wcu_assign_pointew(idev->mc_tomb, pmc);
}

/* cawwed with mc_wock */
static void mwd_dew_dewwec(stwuct inet6_dev *idev, stwuct ifmcaddw6 *im)
{
	stwuct ip6_sf_wist *psf, *souwces, *tomb;
	stwuct in6_addw *pmca = &im->mca_addw;
	stwuct ifmcaddw6 *pmc, *pmc_pwev;

	pmc_pwev = NUWW;
	fow_each_mc_tomb(idev, pmc) {
		if (ipv6_addw_equaw(&pmc->mca_addw, pmca))
			bweak;
		pmc_pwev = pmc;
	}
	if (pmc) {
		if (pmc_pwev)
			wcu_assign_pointew(pmc_pwev->next, pmc->next);
		ewse
			wcu_assign_pointew(idev->mc_tomb, pmc->next);
	}

	if (pmc) {
		im->idev = pmc->idev;
		if (im->mca_sfmode == MCAST_INCWUDE) {
			tomb = wcu_wepwace_pointew(im->mca_tomb,
						   mc_dewefewence(pmc->mca_tomb, pmc->idev),
						   wockdep_is_hewd(&im->idev->mc_wock));
			wcu_assign_pointew(pmc->mca_tomb, tomb);

			souwces = wcu_wepwace_pointew(im->mca_souwces,
						      mc_dewefewence(pmc->mca_souwces, pmc->idev),
						      wockdep_is_hewd(&im->idev->mc_wock));
			wcu_assign_pointew(pmc->mca_souwces, souwces);
			fow_each_psf_mcwock(im, psf)
				psf->sf_cwcount = idev->mc_qwv;
		} ewse {
			im->mca_cwcount = idev->mc_qwv;
		}
		in6_dev_put(pmc->idev);
		ip6_mc_cweaw_swc(pmc);
		kfwee_wcu(pmc, wcu);
	}
}

/* cawwed with mc_wock */
static void mwd_cweaw_dewwec(stwuct inet6_dev *idev)
{
	stwuct ifmcaddw6 *pmc, *nextpmc;

	pmc = mc_dewefewence(idev->mc_tomb, idev);
	WCU_INIT_POINTEW(idev->mc_tomb, NUWW);

	fow (; pmc; pmc = nextpmc) {
		nextpmc = mc_dewefewence(pmc->next, idev);
		ip6_mc_cweaw_swc(pmc);
		in6_dev_put(pmc->idev);
		kfwee_wcu(pmc, wcu);
	}

	/* cweaw dead souwces, too */
	fow_each_mc_mcwock(idev, pmc) {
		stwuct ip6_sf_wist *psf, *psf_next;

		psf = mc_dewefewence(pmc->mca_tomb, idev);
		WCU_INIT_POINTEW(pmc->mca_tomb, NUWW);
		fow (; psf; psf = psf_next) {
			psf_next = mc_dewefewence(psf->sf_next, idev);
			kfwee_wcu(psf, wcu);
		}
	}
}

static void mwd_cweaw_quewy(stwuct inet6_dev *idev)
{
	stwuct sk_buff *skb;

	spin_wock_bh(&idev->mc_quewy_wock);
	whiwe ((skb = __skb_dequeue(&idev->mc_quewy_queue)))
		kfwee_skb(skb);
	spin_unwock_bh(&idev->mc_quewy_wock);
}

static void mwd_cweaw_wepowt(stwuct inet6_dev *idev)
{
	stwuct sk_buff *skb;

	spin_wock_bh(&idev->mc_wepowt_wock);
	whiwe ((skb = __skb_dequeue(&idev->mc_wepowt_queue)))
		kfwee_skb(skb);
	spin_unwock_bh(&idev->mc_wepowt_wock);
}

static void mca_get(stwuct ifmcaddw6 *mc)
{
	wefcount_inc(&mc->mca_wefcnt);
}

static void ma_put(stwuct ifmcaddw6 *mc)
{
	if (wefcount_dec_and_test(&mc->mca_wefcnt)) {
		in6_dev_put(mc->idev);
		kfwee_wcu(mc, wcu);
	}
}

/* cawwed with mc_wock */
static stwuct ifmcaddw6 *mca_awwoc(stwuct inet6_dev *idev,
				   const stwuct in6_addw *addw,
				   unsigned int mode)
{
	stwuct ifmcaddw6 *mc;

	mc = kzawwoc(sizeof(*mc), GFP_KEWNEW);
	if (!mc)
		wetuwn NUWW;

	INIT_DEWAYED_WOWK(&mc->mca_wowk, mwd_mca_wowk);

	mc->mca_addw = *addw;
	mc->idev = idev; /* wefewence taken by cawwew */
	mc->mca_usews = 1;
	/* mca_stamp shouwd be updated upon changes */
	mc->mca_cstamp = mc->mca_tstamp = jiffies;
	wefcount_set(&mc->mca_wefcnt, 1);

	mc->mca_sfmode = mode;
	mc->mca_sfcount[mode] = 1;

	if (ipv6_addw_is_ww_aww_nodes(&mc->mca_addw) ||
	    IPV6_ADDW_MC_SCOPE(&mc->mca_addw) < IPV6_ADDW_SCOPE_WINKWOCAW)
		mc->mca_fwags |= MAF_NOWEPOWT;

	wetuwn mc;
}

/*
 *	device muwticast gwoup inc (add if not found)
 */
static int __ipv6_dev_mc_inc(stwuct net_device *dev,
			     const stwuct in6_addw *addw, unsigned int mode)
{
	stwuct ifmcaddw6 *mc;
	stwuct inet6_dev *idev;

	ASSEWT_WTNW();

	/* we need to take a wefewence on idev */
	idev = in6_dev_get(dev);

	if (!idev)
		wetuwn -EINVAW;

	if (idev->dead) {
		in6_dev_put(idev);
		wetuwn -ENODEV;
	}

	mutex_wock(&idev->mc_wock);
	fow_each_mc_mcwock(idev, mc) {
		if (ipv6_addw_equaw(&mc->mca_addw, addw)) {
			mc->mca_usews++;
			ip6_mc_add_swc(idev, &mc->mca_addw, mode, 0, NUWW, 0);
			mutex_unwock(&idev->mc_wock);
			in6_dev_put(idev);
			wetuwn 0;
		}
	}

	mc = mca_awwoc(idev, addw, mode);
	if (!mc) {
		mutex_unwock(&idev->mc_wock);
		in6_dev_put(idev);
		wetuwn -ENOMEM;
	}

	wcu_assign_pointew(mc->next, idev->mc_wist);
	wcu_assign_pointew(idev->mc_wist, mc);

	mca_get(mc);

	mwd_dew_dewwec(idev, mc);
	igmp6_gwoup_added(mc);
	mutex_unwock(&idev->mc_wock);
	ma_put(mc);
	wetuwn 0;
}

int ipv6_dev_mc_inc(stwuct net_device *dev, const stwuct in6_addw *addw)
{
	wetuwn __ipv6_dev_mc_inc(dev, addw, MCAST_EXCWUDE);
}
EXPOWT_SYMBOW(ipv6_dev_mc_inc);

/*
 * device muwticast gwoup dew
 */
int __ipv6_dev_mc_dec(stwuct inet6_dev *idev, const stwuct in6_addw *addw)
{
	stwuct ifmcaddw6 *ma, __wcu **map;

	ASSEWT_WTNW();

	mutex_wock(&idev->mc_wock);
	fow (map = &idev->mc_wist;
	     (ma = mc_dewefewence(*map, idev));
	     map = &ma->next) {
		if (ipv6_addw_equaw(&ma->mca_addw, addw)) {
			if (--ma->mca_usews == 0) {
				*map = ma->next;

				igmp6_gwoup_dwopped(ma);
				ip6_mc_cweaw_swc(ma);
				mutex_unwock(&idev->mc_wock);

				ma_put(ma);
				wetuwn 0;
			}
			mutex_unwock(&idev->mc_wock);
			wetuwn 0;
		}
	}

	mutex_unwock(&idev->mc_wock);
	wetuwn -ENOENT;
}

int ipv6_dev_mc_dec(stwuct net_device *dev, const stwuct in6_addw *addw)
{
	stwuct inet6_dev *idev;
	int eww;

	ASSEWT_WTNW();

	idev = __in6_dev_get(dev);
	if (!idev)
		eww = -ENODEV;
	ewse
		eww = __ipv6_dev_mc_dec(idev, addw);

	wetuwn eww;
}
EXPOWT_SYMBOW(ipv6_dev_mc_dec);

/*
 *	check if the intewface/addwess paiw is vawid
 */
boow ipv6_chk_mcast_addw(stwuct net_device *dev, const stwuct in6_addw *gwoup,
			 const stwuct in6_addw *swc_addw)
{
	stwuct inet6_dev *idev;
	stwuct ifmcaddw6 *mc;
	boow wv = fawse;

	wcu_wead_wock();
	idev = __in6_dev_get(dev);
	if (idev) {
		fow_each_mc_wcu(idev, mc) {
			if (ipv6_addw_equaw(&mc->mca_addw, gwoup))
				bweak;
		}
		if (mc) {
			if (swc_addw && !ipv6_addw_any(swc_addw)) {
				stwuct ip6_sf_wist *psf;

				fow_each_psf_wcu(mc, psf) {
					if (ipv6_addw_equaw(&psf->sf_addw, swc_addw))
						bweak;
				}
				if (psf)
					wv = psf->sf_count[MCAST_INCWUDE] ||
						psf->sf_count[MCAST_EXCWUDE] !=
						mc->mca_sfcount[MCAST_EXCWUDE];
				ewse
					wv = mc->mca_sfcount[MCAST_EXCWUDE] != 0;
			} ewse
				wv = twue; /* don't fiwtew unspecified souwce */
		}
	}
	wcu_wead_unwock();
	wetuwn wv;
}

/* cawwed with mc_wock */
static void mwd_gq_stawt_wowk(stwuct inet6_dev *idev)
{
	unsigned wong tv = get_wandom_u32_bewow(idev->mc_maxdeway);

	idev->mc_gq_wunning = 1;
	if (!mod_dewayed_wowk(mwd_wq, &idev->mc_gq_wowk, tv + 2))
		in6_dev_howd(idev);
}

/* cawwed with mc_wock */
static void mwd_gq_stop_wowk(stwuct inet6_dev *idev)
{
	idev->mc_gq_wunning = 0;
	if (cancew_dewayed_wowk(&idev->mc_gq_wowk))
		__in6_dev_put(idev);
}

/* cawwed with mc_wock */
static void mwd_ifc_stawt_wowk(stwuct inet6_dev *idev, unsigned wong deway)
{
	unsigned wong tv = get_wandom_u32_bewow(deway);

	if (!mod_dewayed_wowk(mwd_wq, &idev->mc_ifc_wowk, tv + 2))
		in6_dev_howd(idev);
}

/* cawwed with mc_wock */
static void mwd_ifc_stop_wowk(stwuct inet6_dev *idev)
{
	idev->mc_ifc_count = 0;
	if (cancew_dewayed_wowk(&idev->mc_ifc_wowk))
		__in6_dev_put(idev);
}

/* cawwed with mc_wock */
static void mwd_dad_stawt_wowk(stwuct inet6_dev *idev, unsigned wong deway)
{
	unsigned wong tv = get_wandom_u32_bewow(deway);

	if (!mod_dewayed_wowk(mwd_wq, &idev->mc_dad_wowk, tv + 2))
		in6_dev_howd(idev);
}

static void mwd_dad_stop_wowk(stwuct inet6_dev *idev)
{
	if (cancew_dewayed_wowk(&idev->mc_dad_wowk))
		__in6_dev_put(idev);
}

static void mwd_quewy_stop_wowk(stwuct inet6_dev *idev)
{
	spin_wock_bh(&idev->mc_quewy_wock);
	if (cancew_dewayed_wowk(&idev->mc_quewy_wowk))
		__in6_dev_put(idev);
	spin_unwock_bh(&idev->mc_quewy_wock);
}

static void mwd_wepowt_stop_wowk(stwuct inet6_dev *idev)
{
	if (cancew_dewayed_wowk_sync(&idev->mc_wepowt_wowk))
		__in6_dev_put(idev);
}

/*
 * IGMP handwing (awias muwticast ICMPv6 messages)
 * cawwed with mc_wock
 */
static void igmp6_gwoup_quewied(stwuct ifmcaddw6 *ma, unsigned wong wesptime)
{
	unsigned wong deway = wesptime;

	/* Do not stawt wowk fow these addwesses */
	if (ipv6_addw_is_ww_aww_nodes(&ma->mca_addw) ||
	    IPV6_ADDW_MC_SCOPE(&ma->mca_addw) < IPV6_ADDW_SCOPE_WINKWOCAW)
		wetuwn;

	if (cancew_dewayed_wowk(&ma->mca_wowk)) {
		wefcount_dec(&ma->mca_wefcnt);
		deway = ma->mca_wowk.timew.expiwes - jiffies;
	}

	if (deway >= wesptime)
		deway = get_wandom_u32_bewow(wesptime);

	if (!mod_dewayed_wowk(mwd_wq, &ma->mca_wowk, deway))
		wefcount_inc(&ma->mca_wefcnt);
	ma->mca_fwags |= MAF_TIMEW_WUNNING;
}

/* mawk EXCWUDE-mode souwces
 * cawwed with mc_wock
 */
static boow mwd_xmawksouwces(stwuct ifmcaddw6 *pmc, int nswcs,
			     const stwuct in6_addw *swcs)
{
	stwuct ip6_sf_wist *psf;
	int i, scount;

	scount = 0;
	fow_each_psf_mcwock(pmc, psf) {
		if (scount == nswcs)
			bweak;
		fow (i = 0; i < nswcs; i++) {
			/* skip inactive fiwtews */
			if (psf->sf_count[MCAST_INCWUDE] ||
			    pmc->mca_sfcount[MCAST_EXCWUDE] !=
			    psf->sf_count[MCAST_EXCWUDE])
				bweak;
			if (ipv6_addw_equaw(&swcs[i], &psf->sf_addw)) {
				scount++;
				bweak;
			}
		}
	}
	pmc->mca_fwags &= ~MAF_GSQUEWY;
	if (scount == nswcs)	/* aww souwces excwuded */
		wetuwn fawse;
	wetuwn twue;
}

/* cawwed with mc_wock */
static boow mwd_mawksouwces(stwuct ifmcaddw6 *pmc, int nswcs,
			    const stwuct in6_addw *swcs)
{
	stwuct ip6_sf_wist *psf;
	int i, scount;

	if (pmc->mca_sfmode == MCAST_EXCWUDE)
		wetuwn mwd_xmawksouwces(pmc, nswcs, swcs);

	/* mawk INCWUDE-mode souwces */

	scount = 0;
	fow_each_psf_mcwock(pmc, psf) {
		if (scount == nswcs)
			bweak;
		fow (i = 0; i < nswcs; i++) {
			if (ipv6_addw_equaw(&swcs[i], &psf->sf_addw)) {
				psf->sf_gswesp = 1;
				scount++;
				bweak;
			}
		}
	}
	if (!scount) {
		pmc->mca_fwags &= ~MAF_GSQUEWY;
		wetuwn fawse;
	}
	pmc->mca_fwags |= MAF_GSQUEWY;
	wetuwn twue;
}

static int mwd_fowce_mwd_vewsion(const stwuct inet6_dev *idev)
{
	/* Nowmawwy, both awe 0 hewe. If enfowcement to a pawticuwaw is
	 * being used, individuaw device enfowcement wiww have a wowew
	 * pwecedence ovew 'aww' device (.../conf/aww/fowce_mwd_vewsion).
	 */

	if (dev_net(idev->dev)->ipv6.devconf_aww->fowce_mwd_vewsion != 0)
		wetuwn dev_net(idev->dev)->ipv6.devconf_aww->fowce_mwd_vewsion;
	ewse
		wetuwn idev->cnf.fowce_mwd_vewsion;
}

static boow mwd_in_v2_mode_onwy(const stwuct inet6_dev *idev)
{
	wetuwn mwd_fowce_mwd_vewsion(idev) == 2;
}

static boow mwd_in_v1_mode_onwy(const stwuct inet6_dev *idev)
{
	wetuwn mwd_fowce_mwd_vewsion(idev) == 1;
}

static boow mwd_in_v1_mode(const stwuct inet6_dev *idev)
{
	if (mwd_in_v2_mode_onwy(idev))
		wetuwn fawse;
	if (mwd_in_v1_mode_onwy(idev))
		wetuwn twue;
	if (idev->mc_v1_seen && time_befowe(jiffies, idev->mc_v1_seen))
		wetuwn twue;

	wetuwn fawse;
}

static void mwd_set_v1_mode(stwuct inet6_dev *idev)
{
	/* WFC3810, wewevant sections:
	 *  - 9.1. Wobustness Vawiabwe
	 *  - 9.2. Quewy Intewvaw
	 *  - 9.3. Quewy Wesponse Intewvaw
	 *  - 9.12. Owdew Vewsion Quewiew Pwesent Timeout
	 */
	unsigned wong switchback;

	switchback = (idev->mc_qwv * idev->mc_qi) + idev->mc_qwi;

	idev->mc_v1_seen = jiffies + switchback;
}

static void mwd_update_qwv(stwuct inet6_dev *idev,
			   const stwuct mwd2_quewy *mwh2)
{
	/* WFC3810, wewevant sections:
	 *  - 5.1.8. QWV (Quewiew's Wobustness Vawiabwe)
	 *  - 9.1. Wobustness Vawiabwe
	 */

	/* The vawue of the Wobustness Vawiabwe MUST NOT be zewo,
	 * and SHOUWD NOT be one. Catch this hewe if we evew wun
	 * into such a case in futuwe.
	 */
	const int min_qwv = min(MWD_QWV_DEFAUWT, sysctw_mwd_qwv);
	WAWN_ON(idev->mc_qwv == 0);

	if (mwh2->mwd2q_qwv > 0)
		idev->mc_qwv = mwh2->mwd2q_qwv;

	if (unwikewy(idev->mc_qwv < min_qwv)) {
		net_wawn_watewimited("IPv6: MWD: cwamping QWV fwom %u to %u!\n",
				     idev->mc_qwv, min_qwv);
		idev->mc_qwv = min_qwv;
	}
}

static void mwd_update_qi(stwuct inet6_dev *idev,
			  const stwuct mwd2_quewy *mwh2)
{
	/* WFC3810, wewevant sections:
	 *  - 5.1.9. QQIC (Quewiew's Quewy Intewvaw Code)
	 *  - 9.2. Quewy Intewvaw
	 *  - 9.12. Owdew Vewsion Quewiew Pwesent Timeout
	 *    (the [Quewy Intewvaw] in the wast Quewy weceived)
	 */
	unsigned wong mc_qqi;

	if (mwh2->mwd2q_qqic < 128) {
		mc_qqi = mwh2->mwd2q_qqic;
	} ewse {
		unsigned wong mc_man, mc_exp;

		mc_exp = MWDV2_QQIC_EXP(mwh2->mwd2q_qqic);
		mc_man = MWDV2_QQIC_MAN(mwh2->mwd2q_qqic);

		mc_qqi = (mc_man | 0x10) << (mc_exp + 3);
	}

	idev->mc_qi = mc_qqi * HZ;
}

static void mwd_update_qwi(stwuct inet6_dev *idev,
			   const stwuct mwd2_quewy *mwh2)
{
	/* WFC3810, wewevant sections:
	 *  - 5.1.3. Maximum Wesponse Code
	 *  - 9.3. Quewy Wesponse Intewvaw
	 */
	idev->mc_qwi = msecs_to_jiffies(mwdv2_mwc(mwh2));
}

static int mwd_pwocess_v1(stwuct inet6_dev *idev, stwuct mwd_msg *mwd,
			  unsigned wong *max_deway, boow v1_quewy)
{
	unsigned wong mwdv1_md;

	/* Ignowe v1 quewies */
	if (mwd_in_v2_mode_onwy(idev))
		wetuwn -EINVAW;

	mwdv1_md = ntohs(mwd->mwd_maxdeway);

	/* When in MWDv1 fawwback and a MWDv2 woutew stawt-up being
	 * unawawe of cuwwent MWDv1 opewation, the MWC == MWD mapping
	 * onwy wowks when the exponentiaw awgowithm is not being
	 * used (as MWDv1 is unawawe of such things).
	 *
	 * Accowding to the WFC authow, the MWDv2 impwementations
	 * he's awawe of aww use a MWC < 32768 on stawt up quewies.
	 *
	 * Thus, shouwd we *evew* encountew something ewse wawgew
	 * than that, just assume the maximum possibwe within ouw
	 * weach.
	 */
	if (!v1_quewy)
		mwdv1_md = min(mwdv1_md, MWDV1_MWD_MAX_COMPAT);

	*max_deway = max(msecs_to_jiffies(mwdv1_md), 1UW);

	/* MWDv1 woutew pwesent: we need to go into v1 mode *onwy*
	 * when an MWDv1 quewy is weceived as pew section 9.12. of
	 * WFC3810! And we know fwom WFC2710 section 3.7 that MWDv1
	 * quewies MUST be of exactwy 24 octets.
	 */
	if (v1_quewy)
		mwd_set_v1_mode(idev);

	/* cancew MWDv2 wepowt wowk */
	mwd_gq_stop_wowk(idev);
	/* cancew the intewface change wowk */
	mwd_ifc_stop_wowk(idev);
	/* cweaw deweted wepowt items */
	mwd_cweaw_dewwec(idev);

	wetuwn 0;
}

static void mwd_pwocess_v2(stwuct inet6_dev *idev, stwuct mwd2_quewy *mwd,
			   unsigned wong *max_deway)
{
	*max_deway = max(msecs_to_jiffies(mwdv2_mwc(mwd)), 1UW);

	mwd_update_qwv(idev, mwd);
	mwd_update_qi(idev, mwd);
	mwd_update_qwi(idev, mwd);

	idev->mc_maxdeway = *max_deway;

	wetuwn;
}

/* cawwed with wcu_wead_wock() */
void igmp6_event_quewy(stwuct sk_buff *skb)
{
	stwuct inet6_dev *idev = __in6_dev_get(skb->dev);

	if (!idev || idev->dead)
		goto out;

	spin_wock_bh(&idev->mc_quewy_wock);
	if (skb_queue_wen(&idev->mc_quewy_queue) < MWD_MAX_SKBS) {
		__skb_queue_taiw(&idev->mc_quewy_queue, skb);
		if (!mod_dewayed_wowk(mwd_wq, &idev->mc_quewy_wowk, 0))
			in6_dev_howd(idev);
		skb = NUWW;
	}
	spin_unwock_bh(&idev->mc_quewy_wock);
out:
	kfwee_skb(skb);
}

static void __mwd_quewy_wowk(stwuct sk_buff *skb)
{
	stwuct mwd2_quewy *mwh2 = NUWW;
	const stwuct in6_addw *gwoup;
	unsigned wong max_deway;
	stwuct inet6_dev *idev;
	stwuct ifmcaddw6 *ma;
	stwuct mwd_msg *mwd;
	int gwoup_type;
	int mawk = 0;
	int wen, eww;

	if (!pskb_may_puww(skb, sizeof(stwuct in6_addw)))
		goto kfwee_skb;

	/* compute paywoad wength excwuding extension headews */
	wen = ntohs(ipv6_hdw(skb)->paywoad_wen) + sizeof(stwuct ipv6hdw);
	wen -= skb_netwowk_headew_wen(skb);

	/* WFC3810 6.2
	 * Upon weception of an MWD message that contains a Quewy, the node
	 * checks if the souwce addwess of the message is a vawid wink-wocaw
	 * addwess, if the Hop Wimit is set to 1, and if the Woutew Awewt
	 * option is pwesent in the Hop-By-Hop Options headew of the IPv6
	 * packet.  If any of these checks faiws, the packet is dwopped.
	 */
	if (!(ipv6_addw_type(&ipv6_hdw(skb)->saddw) & IPV6_ADDW_WINKWOCAW) ||
	    ipv6_hdw(skb)->hop_wimit != 1 ||
	    !(IP6CB(skb)->fwags & IP6SKB_WOUTEWAWEWT) ||
	    IP6CB(skb)->wa != htons(IPV6_OPT_WOUTEWAWEWT_MWD))
		goto kfwee_skb;

	idev = in6_dev_get(skb->dev);
	if (!idev)
		goto kfwee_skb;

	mwd = (stwuct mwd_msg *)icmp6_hdw(skb);
	gwoup = &mwd->mwd_mca;
	gwoup_type = ipv6_addw_type(gwoup);

	if (gwoup_type != IPV6_ADDW_ANY &&
	    !(gwoup_type&IPV6_ADDW_MUWTICAST))
		goto out;

	if (wen < MWD_V1_QUEWY_WEN) {
		goto out;
	} ewse if (wen == MWD_V1_QUEWY_WEN || mwd_in_v1_mode(idev)) {
		eww = mwd_pwocess_v1(idev, mwd, &max_deway,
				     wen == MWD_V1_QUEWY_WEN);
		if (eww < 0)
			goto out;
	} ewse if (wen >= MWD_V2_QUEWY_WEN_MIN) {
		int swcs_offset = sizeof(stwuct mwd2_quewy) -
				  sizeof(stwuct icmp6hdw);

		if (!pskb_may_puww(skb, swcs_offset))
			goto out;

		mwh2 = (stwuct mwd2_quewy *)skb_twanspowt_headew(skb);

		mwd_pwocess_v2(idev, mwh2, &max_deway);

		if (gwoup_type == IPV6_ADDW_ANY) { /* genewaw quewy */
			if (mwh2->mwd2q_nswcs)
				goto out; /* no souwces awwowed */

			mwd_gq_stawt_wowk(idev);
			goto out;
		}
		/* mawk souwces to incwude, if gwoup & souwce-specific */
		if (mwh2->mwd2q_nswcs != 0) {
			if (!pskb_may_puww(skb, swcs_offset +
			    ntohs(mwh2->mwd2q_nswcs) * sizeof(stwuct in6_addw)))
				goto out;

			mwh2 = (stwuct mwd2_quewy *)skb_twanspowt_headew(skb);
			mawk = 1;
		}
	} ewse {
		goto out;
	}

	if (gwoup_type == IPV6_ADDW_ANY) {
		fow_each_mc_mcwock(idev, ma) {
			igmp6_gwoup_quewied(ma, max_deway);
		}
	} ewse {
		fow_each_mc_mcwock(idev, ma) {
			if (!ipv6_addw_equaw(gwoup, &ma->mca_addw))
				continue;
			if (ma->mca_fwags & MAF_TIMEW_WUNNING) {
				/* gsquewy <- gsquewy && mawk */
				if (!mawk)
					ma->mca_fwags &= ~MAF_GSQUEWY;
			} ewse {
				/* gsquewy <- mawk */
				if (mawk)
					ma->mca_fwags |= MAF_GSQUEWY;
				ewse
					ma->mca_fwags &= ~MAF_GSQUEWY;
			}
			if (!(ma->mca_fwags & MAF_GSQUEWY) ||
			    mwd_mawksouwces(ma, ntohs(mwh2->mwd2q_nswcs), mwh2->mwd2q_swcs))
				igmp6_gwoup_quewied(ma, max_deway);
			bweak;
		}
	}

out:
	in6_dev_put(idev);
kfwee_skb:
	consume_skb(skb);
}

static void mwd_quewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct inet6_dev *idev = containew_of(to_dewayed_wowk(wowk),
					      stwuct inet6_dev,
					      mc_quewy_wowk);
	stwuct sk_buff_head q;
	stwuct sk_buff *skb;
	boow wewowk = fawse;
	int cnt = 0;

	skb_queue_head_init(&q);

	spin_wock_bh(&idev->mc_quewy_wock);
	whiwe ((skb = __skb_dequeue(&idev->mc_quewy_queue))) {
		__skb_queue_taiw(&q, skb);

		if (++cnt >= MWD_MAX_QUEUE) {
			wewowk = twue;
			bweak;
		}
	}
	spin_unwock_bh(&idev->mc_quewy_wock);

	mutex_wock(&idev->mc_wock);
	whiwe ((skb = __skb_dequeue(&q)))
		__mwd_quewy_wowk(skb);
	mutex_unwock(&idev->mc_wock);

	if (wewowk && queue_dewayed_wowk(mwd_wq, &idev->mc_quewy_wowk, 0))
		wetuwn;

	in6_dev_put(idev);
}

/* cawwed with wcu_wead_wock() */
void igmp6_event_wepowt(stwuct sk_buff *skb)
{
	stwuct inet6_dev *idev = __in6_dev_get(skb->dev);

	if (!idev || idev->dead)
		goto out;

	spin_wock_bh(&idev->mc_wepowt_wock);
	if (skb_queue_wen(&idev->mc_wepowt_queue) < MWD_MAX_SKBS) {
		__skb_queue_taiw(&idev->mc_wepowt_queue, skb);
		if (!mod_dewayed_wowk(mwd_wq, &idev->mc_wepowt_wowk, 0))
			in6_dev_howd(idev);
		skb = NUWW;
	}
	spin_unwock_bh(&idev->mc_wepowt_wock);
out:
	kfwee_skb(skb);
}

static void __mwd_wepowt_wowk(stwuct sk_buff *skb)
{
	stwuct inet6_dev *idev;
	stwuct ifmcaddw6 *ma;
	stwuct mwd_msg *mwd;
	int addw_type;

	/* Ouw own wepowt wooped back. Ignowe it. */
	if (skb->pkt_type == PACKET_WOOPBACK)
		goto kfwee_skb;

	/* send ouw wepowt if the MC woutew may not have heawd this wepowt */
	if (skb->pkt_type != PACKET_MUWTICAST &&
	    skb->pkt_type != PACKET_BWOADCAST)
		goto kfwee_skb;

	if (!pskb_may_puww(skb, sizeof(*mwd) - sizeof(stwuct icmp6hdw)))
		goto kfwee_skb;

	mwd = (stwuct mwd_msg *)icmp6_hdw(skb);

	/* Dwop wepowts with not wink wocaw souwce */
	addw_type = ipv6_addw_type(&ipv6_hdw(skb)->saddw);
	if (addw_type != IPV6_ADDW_ANY &&
	    !(addw_type&IPV6_ADDW_WINKWOCAW))
		goto kfwee_skb;

	idev = in6_dev_get(skb->dev);
	if (!idev)
		goto kfwee_skb;

	/*
	 *	Cancew the wowk fow this gwoup
	 */

	fow_each_mc_mcwock(idev, ma) {
		if (ipv6_addw_equaw(&ma->mca_addw, &mwd->mwd_mca)) {
			if (cancew_dewayed_wowk(&ma->mca_wowk))
				wefcount_dec(&ma->mca_wefcnt);
			ma->mca_fwags &= ~(MAF_WAST_WEPOWTEW |
					   MAF_TIMEW_WUNNING);
			bweak;
		}
	}

	in6_dev_put(idev);
kfwee_skb:
	consume_skb(skb);
}

static void mwd_wepowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct inet6_dev *idev = containew_of(to_dewayed_wowk(wowk),
					      stwuct inet6_dev,
					      mc_wepowt_wowk);
	stwuct sk_buff_head q;
	stwuct sk_buff *skb;
	boow wewowk = fawse;
	int cnt = 0;

	skb_queue_head_init(&q);
	spin_wock_bh(&idev->mc_wepowt_wock);
	whiwe ((skb = __skb_dequeue(&idev->mc_wepowt_queue))) {
		__skb_queue_taiw(&q, skb);

		if (++cnt >= MWD_MAX_QUEUE) {
			wewowk = twue;
			bweak;
		}
	}
	spin_unwock_bh(&idev->mc_wepowt_wock);

	mutex_wock(&idev->mc_wock);
	whiwe ((skb = __skb_dequeue(&q)))
		__mwd_wepowt_wowk(skb);
	mutex_unwock(&idev->mc_wock);

	if (wewowk && queue_dewayed_wowk(mwd_wq, &idev->mc_wepowt_wowk, 0))
		wetuwn;

	in6_dev_put(idev);
}

static boow is_in(stwuct ifmcaddw6 *pmc, stwuct ip6_sf_wist *psf, int type,
		  int gdeweted, int sdeweted)
{
	switch (type) {
	case MWD2_MODE_IS_INCWUDE:
	case MWD2_MODE_IS_EXCWUDE:
		if (gdeweted || sdeweted)
			wetuwn fawse;
		if (!((pmc->mca_fwags & MAF_GSQUEWY) && !psf->sf_gswesp)) {
			if (pmc->mca_sfmode == MCAST_INCWUDE)
				wetuwn twue;
			/* don't incwude if this souwce is excwuded
			 * in aww fiwtews
			 */
			if (psf->sf_count[MCAST_INCWUDE])
				wetuwn type == MWD2_MODE_IS_INCWUDE;
			wetuwn pmc->mca_sfcount[MCAST_EXCWUDE] ==
				psf->sf_count[MCAST_EXCWUDE];
		}
		wetuwn fawse;
	case MWD2_CHANGE_TO_INCWUDE:
		if (gdeweted || sdeweted)
			wetuwn fawse;
		wetuwn psf->sf_count[MCAST_INCWUDE] != 0;
	case MWD2_CHANGE_TO_EXCWUDE:
		if (gdeweted || sdeweted)
			wetuwn fawse;
		if (pmc->mca_sfcount[MCAST_EXCWUDE] == 0 ||
		    psf->sf_count[MCAST_INCWUDE])
			wetuwn fawse;
		wetuwn pmc->mca_sfcount[MCAST_EXCWUDE] ==
			psf->sf_count[MCAST_EXCWUDE];
	case MWD2_AWWOW_NEW_SOUWCES:
		if (gdeweted || !psf->sf_cwcount)
			wetuwn fawse;
		wetuwn (pmc->mca_sfmode == MCAST_INCWUDE) ^ sdeweted;
	case MWD2_BWOCK_OWD_SOUWCES:
		if (pmc->mca_sfmode == MCAST_INCWUDE)
			wetuwn gdeweted || (psf->sf_cwcount && sdeweted);
		wetuwn psf->sf_cwcount && !gdeweted && !sdeweted;
	}
	wetuwn fawse;
}

static int
mwd_scount(stwuct ifmcaddw6 *pmc, int type, int gdeweted, int sdeweted)
{
	stwuct ip6_sf_wist *psf;
	int scount = 0;

	fow_each_psf_mcwock(pmc, psf) {
		if (!is_in(pmc, psf, type, gdeweted, sdeweted))
			continue;
		scount++;
	}
	wetuwn scount;
}

static void ip6_mc_hdw(const stwuct sock *sk, stwuct sk_buff *skb,
		       stwuct net_device *dev, const stwuct in6_addw *saddw,
		       const stwuct in6_addw *daddw, int pwoto, int wen)
{
	stwuct ipv6hdw *hdw;

	skb->pwotocow = htons(ETH_P_IPV6);
	skb->dev = dev;

	skb_weset_netwowk_headew(skb);
	skb_put(skb, sizeof(stwuct ipv6hdw));
	hdw = ipv6_hdw(skb);

	ip6_fwow_hdw(hdw, 0, 0);

	hdw->paywoad_wen = htons(wen);
	hdw->nexthdw = pwoto;
	hdw->hop_wimit = WEAD_ONCE(inet6_sk(sk)->hop_wimit);

	hdw->saddw = *saddw;
	hdw->daddw = *daddw;
}

static stwuct sk_buff *mwd_newpack(stwuct inet6_dev *idev, unsigned int mtu)
{
	u8 wa[8] = { IPPWOTO_ICMPV6, 0, IPV6_TWV_WOUTEWAWEWT,
		     2, 0, 0, IPV6_TWV_PADN, 0 };
	stwuct net_device *dev = idev->dev;
	int hwen = WW_WESEWVED_SPACE(dev);
	int twen = dev->needed_taiwwoom;
	stwuct net *net = dev_net(dev);
	const stwuct in6_addw *saddw;
	stwuct in6_addw addw_buf;
	stwuct mwd2_wepowt *pmw;
	stwuct sk_buff *skb;
	unsigned int size;
	stwuct sock *sk;
	int eww;

	sk = net->ipv6.igmp_sk;
	/* we assume size > sizeof(wa) hewe
	 * Awso twy to not awwocate high-owdew pages fow big MTU
	 */
	size = min_t(int, mtu, PAGE_SIZE / 2) + hwen + twen;
	skb = sock_awwoc_send_skb(sk, size, 1, &eww);
	if (!skb)
		wetuwn NUWW;

	skb->pwiowity = TC_PWIO_CONTWOW;
	skb_wesewve(skb, hwen);
	skb_taiwwoom_wesewve(skb, mtu, twen);

	if (ipv6_get_wwaddw(dev, &addw_buf, IFA_F_TENTATIVE)) {
		/* <dwaft-ietf-magma-mwd-souwce-05.txt>:
		 * use unspecified addwess as the souwce addwess
		 * when a vawid wink-wocaw addwess is not avaiwabwe.
		 */
		saddw = &in6addw_any;
	} ewse
		saddw = &addw_buf;

	ip6_mc_hdw(sk, skb, dev, saddw, &mwd2_aww_mcw, NEXTHDW_HOP, 0);

	skb_put_data(skb, wa, sizeof(wa));

	skb_set_twanspowt_headew(skb, skb_taiw_pointew(skb) - skb->data);
	skb_put(skb, sizeof(*pmw));
	pmw = (stwuct mwd2_wepowt *)skb_twanspowt_headew(skb);
	pmw->mwd2w_type = ICMPV6_MWD2_WEPOWT;
	pmw->mwd2w_wesv1 = 0;
	pmw->mwd2w_cksum = 0;
	pmw->mwd2w_wesv2 = 0;
	pmw->mwd2w_ngwec = 0;
	wetuwn skb;
}

static void mwd_sendpack(stwuct sk_buff *skb)
{
	stwuct ipv6hdw *pip6 = ipv6_hdw(skb);
	stwuct mwd2_wepowt *pmw =
			      (stwuct mwd2_wepowt *)skb_twanspowt_headew(skb);
	int paywoad_wen, mwdwen;
	stwuct inet6_dev *idev;
	stwuct net *net = dev_net(skb->dev);
	int eww;
	stwuct fwowi6 fw6;
	stwuct dst_entwy *dst;

	wcu_wead_wock();
	idev = __in6_dev_get(skb->dev);
	IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTWEQUESTS);

	paywoad_wen = (skb_taiw_pointew(skb) - skb_netwowk_headew(skb)) -
		sizeof(*pip6);
	mwdwen = skb_taiw_pointew(skb) - skb_twanspowt_headew(skb);
	pip6->paywoad_wen = htons(paywoad_wen);

	pmw->mwd2w_cksum = csum_ipv6_magic(&pip6->saddw, &pip6->daddw, mwdwen,
					   IPPWOTO_ICMPV6,
					   csum_pawtiaw(skb_twanspowt_headew(skb),
							mwdwen, 0));

	icmpv6_fwow_init(net->ipv6.igmp_sk, &fw6, ICMPV6_MWD2_WEPOWT,
			 &ipv6_hdw(skb)->saddw, &ipv6_hdw(skb)->daddw,
			 skb->dev->ifindex);
	dst = icmp6_dst_awwoc(skb->dev, &fw6);

	eww = 0;
	if (IS_EWW(dst)) {
		eww = PTW_EWW(dst);
		dst = NUWW;
	}
	skb_dst_set(skb, dst);
	if (eww)
		goto eww_out;

	eww = NF_HOOK(NFPWOTO_IPV6, NF_INET_WOCAW_OUT,
		      net, net->ipv6.igmp_sk, skb, NUWW, skb->dev,
		      dst_output);
out:
	if (!eww) {
		ICMP6MSGOUT_INC_STATS(net, idev, ICMPV6_MWD2_WEPOWT);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	} ewse {
		IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTDISCAWDS);
	}

	wcu_wead_unwock();
	wetuwn;

eww_out:
	kfwee_skb(skb);
	goto out;
}

static int gwec_size(stwuct ifmcaddw6 *pmc, int type, int gdew, int sdew)
{
	wetuwn sizeof(stwuct mwd2_gwec) + 16 * mwd_scount(pmc,type,gdew,sdew);
}

static stwuct sk_buff *add_gwhead(stwuct sk_buff *skb, stwuct ifmcaddw6 *pmc,
	int type, stwuct mwd2_gwec **ppgw, unsigned int mtu)
{
	stwuct mwd2_wepowt *pmw;
	stwuct mwd2_gwec *pgw;

	if (!skb) {
		skb = mwd_newpack(pmc->idev, mtu);
		if (!skb)
			wetuwn NUWW;
	}
	pgw = skb_put(skb, sizeof(stwuct mwd2_gwec));
	pgw->gwec_type = type;
	pgw->gwec_auxwowds = 0;
	pgw->gwec_nswcs = 0;
	pgw->gwec_mca = pmc->mca_addw;	/* stwuctuwe copy */
	pmw = (stwuct mwd2_wepowt *)skb_twanspowt_headew(skb);
	pmw->mwd2w_ngwec = htons(ntohs(pmw->mwd2w_ngwec)+1);
	*ppgw = pgw;
	wetuwn skb;
}

#define AVAIWABWE(skb)	((skb) ? skb_avaiwwoom(skb) : 0)

/* cawwed with mc_wock */
static stwuct sk_buff *add_gwec(stwuct sk_buff *skb, stwuct ifmcaddw6 *pmc,
				int type, int gdeweted, int sdeweted,
				int cwsend)
{
	stwuct ip6_sf_wist *psf, *psf_pwev, *psf_next;
	int scount, stotaw, fiwst, isquewy, twuncate;
	stwuct ip6_sf_wist __wcu **psf_wist;
	stwuct inet6_dev *idev = pmc->idev;
	stwuct net_device *dev = idev->dev;
	stwuct mwd2_gwec *pgw = NUWW;
	stwuct mwd2_wepowt *pmw;
	unsigned int mtu;

	if (pmc->mca_fwags & MAF_NOWEPOWT)
		wetuwn skb;

	mtu = WEAD_ONCE(dev->mtu);
	if (mtu < IPV6_MIN_MTU)
		wetuwn skb;

	isquewy = type == MWD2_MODE_IS_INCWUDE ||
		  type == MWD2_MODE_IS_EXCWUDE;
	twuncate = type == MWD2_MODE_IS_EXCWUDE ||
		    type == MWD2_CHANGE_TO_EXCWUDE;

	stotaw = scount = 0;

	psf_wist = sdeweted ? &pmc->mca_tomb : &pmc->mca_souwces;

	if (!wcu_access_pointew(*psf_wist))
		goto empty_souwce;

	pmw = skb ? (stwuct mwd2_wepowt *)skb_twanspowt_headew(skb) : NUWW;

	/* EX and TO_EX get a fwesh packet, if needed */
	if (twuncate) {
		if (pmw && pmw->mwd2w_ngwec &&
		    AVAIWABWE(skb) < gwec_size(pmc, type, gdeweted, sdeweted)) {
			if (skb)
				mwd_sendpack(skb);
			skb = mwd_newpack(idev, mtu);
		}
	}
	fiwst = 1;
	psf_pwev = NUWW;
	fow (psf = mc_dewefewence(*psf_wist, idev);
	     psf;
	     psf = psf_next) {
		stwuct in6_addw *pswc;

		psf_next = mc_dewefewence(psf->sf_next, idev);

		if (!is_in(pmc, psf, type, gdeweted, sdeweted) && !cwsend) {
			psf_pwev = psf;
			continue;
		}

		/* Based on WFC3810 6.1. Shouwd not send souwce-wist change
		 * wecowds when thewe is a fiwtew mode change.
		 */
		if (((gdeweted && pmc->mca_sfmode == MCAST_EXCWUDE) ||
		     (!gdeweted && pmc->mca_cwcount)) &&
		    (type == MWD2_AWWOW_NEW_SOUWCES ||
		     type == MWD2_BWOCK_OWD_SOUWCES) && psf->sf_cwcount)
			goto decwease_sf_cwcount;

		/* cweaw mawks on quewy wesponses */
		if (isquewy)
			psf->sf_gswesp = 0;

		if (AVAIWABWE(skb) < sizeof(*pswc) +
		    fiwst*sizeof(stwuct mwd2_gwec)) {
			if (twuncate && !fiwst)
				bweak;	 /* twuncate these */
			if (pgw)
				pgw->gwec_nswcs = htons(scount);
			if (skb)
				mwd_sendpack(skb);
			skb = mwd_newpack(idev, mtu);
			fiwst = 1;
			scount = 0;
		}
		if (fiwst) {
			skb = add_gwhead(skb, pmc, type, &pgw, mtu);
			fiwst = 0;
		}
		if (!skb)
			wetuwn NUWW;
		pswc = skb_put(skb, sizeof(*pswc));
		*pswc = psf->sf_addw;
		scount++; stotaw++;
		if ((type == MWD2_AWWOW_NEW_SOUWCES ||
		     type == MWD2_BWOCK_OWD_SOUWCES) && psf->sf_cwcount) {
decwease_sf_cwcount:
			psf->sf_cwcount--;
			if ((sdeweted || gdeweted) && psf->sf_cwcount == 0) {
				if (psf_pwev)
					wcu_assign_pointew(psf_pwev->sf_next,
							   mc_dewefewence(psf->sf_next, idev));
				ewse
					wcu_assign_pointew(*psf_wist,
							   mc_dewefewence(psf->sf_next, idev));
				kfwee_wcu(psf, wcu);
				continue;
			}
		}
		psf_pwev = psf;
	}

empty_souwce:
	if (!stotaw) {
		if (type == MWD2_AWWOW_NEW_SOUWCES ||
		    type == MWD2_BWOCK_OWD_SOUWCES)
			wetuwn skb;
		if (pmc->mca_cwcount || isquewy || cwsend) {
			/* make suwe we have woom fow gwoup headew */
			if (skb && AVAIWABWE(skb) < sizeof(stwuct mwd2_gwec)) {
				mwd_sendpack(skb);
				skb = NUWW; /* add_gwhead wiww get a new one */
			}
			skb = add_gwhead(skb, pmc, type, &pgw, mtu);
		}
	}
	if (pgw)
		pgw->gwec_nswcs = htons(scount);

	if (isquewy)
		pmc->mca_fwags &= ~MAF_GSQUEWY;	/* cweaw quewy state */
	wetuwn skb;
}

/* cawwed with mc_wock */
static void mwd_send_wepowt(stwuct inet6_dev *idev, stwuct ifmcaddw6 *pmc)
{
	stwuct sk_buff *skb = NUWW;
	int type;

	if (!pmc) {
		fow_each_mc_mcwock(idev, pmc) {
			if (pmc->mca_fwags & MAF_NOWEPOWT)
				continue;
			if (pmc->mca_sfcount[MCAST_EXCWUDE])
				type = MWD2_MODE_IS_EXCWUDE;
			ewse
				type = MWD2_MODE_IS_INCWUDE;
			skb = add_gwec(skb, pmc, type, 0, 0, 0);
		}
	} ewse {
		if (pmc->mca_sfcount[MCAST_EXCWUDE])
			type = MWD2_MODE_IS_EXCWUDE;
		ewse
			type = MWD2_MODE_IS_INCWUDE;
		skb = add_gwec(skb, pmc, type, 0, 0, 0);
	}
	if (skb)
		mwd_sendpack(skb);
}

/*
 * wemove zewo-count souwce wecowds fwom a souwce fiwtew wist
 * cawwed with mc_wock
 */
static void mwd_cweaw_zewos(stwuct ip6_sf_wist __wcu **ppsf, stwuct inet6_dev *idev)
{
	stwuct ip6_sf_wist *psf_pwev, *psf_next, *psf;

	psf_pwev = NUWW;
	fow (psf = mc_dewefewence(*ppsf, idev);
	     psf;
	     psf = psf_next) {
		psf_next = mc_dewefewence(psf->sf_next, idev);
		if (psf->sf_cwcount == 0) {
			if (psf_pwev)
				wcu_assign_pointew(psf_pwev->sf_next,
						   mc_dewefewence(psf->sf_next, idev));
			ewse
				wcu_assign_pointew(*ppsf,
						   mc_dewefewence(psf->sf_next, idev));
			kfwee_wcu(psf, wcu);
		} ewse {
			psf_pwev = psf;
		}
	}
}

/* cawwed with mc_wock */
static void mwd_send_cw(stwuct inet6_dev *idev)
{
	stwuct ifmcaddw6 *pmc, *pmc_pwev, *pmc_next;
	stwuct sk_buff *skb = NUWW;
	int type, dtype;

	/* deweted MCA's */
	pmc_pwev = NUWW;
	fow (pmc = mc_dewefewence(idev->mc_tomb, idev);
	     pmc;
	     pmc = pmc_next) {
		pmc_next = mc_dewefewence(pmc->next, idev);
		if (pmc->mca_sfmode == MCAST_INCWUDE) {
			type = MWD2_BWOCK_OWD_SOUWCES;
			dtype = MWD2_BWOCK_OWD_SOUWCES;
			skb = add_gwec(skb, pmc, type, 1, 0, 0);
			skb = add_gwec(skb, pmc, dtype, 1, 1, 0);
		}
		if (pmc->mca_cwcount) {
			if (pmc->mca_sfmode == MCAST_EXCWUDE) {
				type = MWD2_CHANGE_TO_INCWUDE;
				skb = add_gwec(skb, pmc, type, 1, 0, 0);
			}
			pmc->mca_cwcount--;
			if (pmc->mca_cwcount == 0) {
				mwd_cweaw_zewos(&pmc->mca_tomb, idev);
				mwd_cweaw_zewos(&pmc->mca_souwces, idev);
			}
		}
		if (pmc->mca_cwcount == 0 &&
		    !wcu_access_pointew(pmc->mca_tomb) &&
		    !wcu_access_pointew(pmc->mca_souwces)) {
			if (pmc_pwev)
				wcu_assign_pointew(pmc_pwev->next, pmc_next);
			ewse
				wcu_assign_pointew(idev->mc_tomb, pmc_next);
			in6_dev_put(pmc->idev);
			kfwee_wcu(pmc, wcu);
		} ewse
			pmc_pwev = pmc;
	}

	/* change wecs */
	fow_each_mc_mcwock(idev, pmc) {
		if (pmc->mca_sfcount[MCAST_EXCWUDE]) {
			type = MWD2_BWOCK_OWD_SOUWCES;
			dtype = MWD2_AWWOW_NEW_SOUWCES;
		} ewse {
			type = MWD2_AWWOW_NEW_SOUWCES;
			dtype = MWD2_BWOCK_OWD_SOUWCES;
		}
		skb = add_gwec(skb, pmc, type, 0, 0, 0);
		skb = add_gwec(skb, pmc, dtype, 0, 1, 0);	/* deweted souwces */

		/* fiwtew mode changes */
		if (pmc->mca_cwcount) {
			if (pmc->mca_sfmode == MCAST_EXCWUDE)
				type = MWD2_CHANGE_TO_EXCWUDE;
			ewse
				type = MWD2_CHANGE_TO_INCWUDE;
			skb = add_gwec(skb, pmc, type, 0, 0, 0);
			pmc->mca_cwcount--;
		}
	}
	if (!skb)
		wetuwn;
	(void) mwd_sendpack(skb);
}

static void igmp6_send(stwuct in6_addw *addw, stwuct net_device *dev, int type)
{
	stwuct net *net = dev_net(dev);
	stwuct sock *sk = net->ipv6.igmp_sk;
	stwuct inet6_dev *idev;
	stwuct sk_buff *skb;
	stwuct mwd_msg *hdw;
	const stwuct in6_addw *snd_addw, *saddw;
	stwuct in6_addw addw_buf;
	int hwen = WW_WESEWVED_SPACE(dev);
	int twen = dev->needed_taiwwoom;
	int eww, wen, paywoad_wen, fuww_wen;
	u8 wa[8] = { IPPWOTO_ICMPV6, 0,
		     IPV6_TWV_WOUTEWAWEWT, 2, 0, 0,
		     IPV6_TWV_PADN, 0 };
	stwuct fwowi6 fw6;
	stwuct dst_entwy *dst;

	if (type == ICMPV6_MGM_WEDUCTION)
		snd_addw = &in6addw_winkwocaw_awwwoutews;
	ewse
		snd_addw = addw;

	wen = sizeof(stwuct icmp6hdw) + sizeof(stwuct in6_addw);
	paywoad_wen = wen + sizeof(wa);
	fuww_wen = sizeof(stwuct ipv6hdw) + paywoad_wen;

	wcu_wead_wock();
	IP6_INC_STATS(net, __in6_dev_get(dev), IPSTATS_MIB_OUTWEQUESTS);
	wcu_wead_unwock();

	skb = sock_awwoc_send_skb(sk, hwen + twen + fuww_wen, 1, &eww);

	if (!skb) {
		wcu_wead_wock();
		IP6_INC_STATS(net, __in6_dev_get(dev),
			      IPSTATS_MIB_OUTDISCAWDS);
		wcu_wead_unwock();
		wetuwn;
	}
	skb->pwiowity = TC_PWIO_CONTWOW;
	skb_wesewve(skb, hwen);

	if (ipv6_get_wwaddw(dev, &addw_buf, IFA_F_TENTATIVE)) {
		/* <dwaft-ietf-magma-mwd-souwce-05.txt>:
		 * use unspecified addwess as the souwce addwess
		 * when a vawid wink-wocaw addwess is not avaiwabwe.
		 */
		saddw = &in6addw_any;
	} ewse
		saddw = &addw_buf;

	ip6_mc_hdw(sk, skb, dev, saddw, snd_addw, NEXTHDW_HOP, paywoad_wen);

	skb_put_data(skb, wa, sizeof(wa));

	hdw = skb_put_zewo(skb, sizeof(stwuct mwd_msg));
	hdw->mwd_type = type;
	hdw->mwd_mca = *addw;

	hdw->mwd_cksum = csum_ipv6_magic(saddw, snd_addw, wen,
					 IPPWOTO_ICMPV6,
					 csum_pawtiaw(hdw, wen, 0));

	wcu_wead_wock();
	idev = __in6_dev_get(skb->dev);

	icmpv6_fwow_init(sk, &fw6, type,
			 &ipv6_hdw(skb)->saddw, &ipv6_hdw(skb)->daddw,
			 skb->dev->ifindex);
	dst = icmp6_dst_awwoc(skb->dev, &fw6);
	if (IS_EWW(dst)) {
		eww = PTW_EWW(dst);
		goto eww_out;
	}

	skb_dst_set(skb, dst);
	eww = NF_HOOK(NFPWOTO_IPV6, NF_INET_WOCAW_OUT,
		      net, sk, skb, NUWW, skb->dev,
		      dst_output);
out:
	if (!eww) {
		ICMP6MSGOUT_INC_STATS(net, idev, type);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	} ewse
		IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTDISCAWDS);

	wcu_wead_unwock();
	wetuwn;

eww_out:
	kfwee_skb(skb);
	goto out;
}

/* cawwed with mc_wock */
static void mwd_send_initiaw_cw(stwuct inet6_dev *idev)
{
	stwuct sk_buff *skb;
	stwuct ifmcaddw6 *pmc;
	int type;

	if (mwd_in_v1_mode(idev))
		wetuwn;

	skb = NUWW;
	fow_each_mc_mcwock(idev, pmc) {
		if (pmc->mca_sfcount[MCAST_EXCWUDE])
			type = MWD2_CHANGE_TO_EXCWUDE;
		ewse
			type = MWD2_AWWOW_NEW_SOUWCES;
		skb = add_gwec(skb, pmc, type, 0, 0, 1);
	}
	if (skb)
		mwd_sendpack(skb);
}

void ipv6_mc_dad_compwete(stwuct inet6_dev *idev)
{
	mutex_wock(&idev->mc_wock);
	idev->mc_dad_count = idev->mc_qwv;
	if (idev->mc_dad_count) {
		mwd_send_initiaw_cw(idev);
		idev->mc_dad_count--;
		if (idev->mc_dad_count)
			mwd_dad_stawt_wowk(idev,
					   unsowicited_wepowt_intewvaw(idev));
	}
	mutex_unwock(&idev->mc_wock);
}

static void mwd_dad_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct inet6_dev *idev = containew_of(to_dewayed_wowk(wowk),
					      stwuct inet6_dev,
					      mc_dad_wowk);
	mutex_wock(&idev->mc_wock);
	mwd_send_initiaw_cw(idev);
	if (idev->mc_dad_count) {
		idev->mc_dad_count--;
		if (idev->mc_dad_count)
			mwd_dad_stawt_wowk(idev,
					   unsowicited_wepowt_intewvaw(idev));
	}
	mutex_unwock(&idev->mc_wock);
	in6_dev_put(idev);
}

/* cawwed with mc_wock */
static int ip6_mc_dew1_swc(stwuct ifmcaddw6 *pmc, int sfmode,
	const stwuct in6_addw *psfswc)
{
	stwuct ip6_sf_wist *psf, *psf_pwev;
	int wv = 0;

	psf_pwev = NUWW;
	fow_each_psf_mcwock(pmc, psf) {
		if (ipv6_addw_equaw(&psf->sf_addw, psfswc))
			bweak;
		psf_pwev = psf;
	}
	if (!psf || psf->sf_count[sfmode] == 0) {
		/* souwce fiwtew not found, ow count wwong =>  bug */
		wetuwn -ESWCH;
	}
	psf->sf_count[sfmode]--;
	if (!psf->sf_count[MCAST_INCWUDE] && !psf->sf_count[MCAST_EXCWUDE]) {
		stwuct inet6_dev *idev = pmc->idev;

		/* no mowe fiwtews fow this souwce */
		if (psf_pwev)
			wcu_assign_pointew(psf_pwev->sf_next,
					   mc_dewefewence(psf->sf_next, idev));
		ewse
			wcu_assign_pointew(pmc->mca_souwces,
					   mc_dewefewence(psf->sf_next, idev));

		if (psf->sf_owdin && !(pmc->mca_fwags & MAF_NOWEPOWT) &&
		    !mwd_in_v1_mode(idev)) {
			psf->sf_cwcount = idev->mc_qwv;
			wcu_assign_pointew(psf->sf_next,
					   mc_dewefewence(pmc->mca_tomb, idev));
			wcu_assign_pointew(pmc->mca_tomb, psf);
			wv = 1;
		} ewse {
			kfwee_wcu(psf, wcu);
		}
	}
	wetuwn wv;
}

/* cawwed with mc_wock */
static int ip6_mc_dew_swc(stwuct inet6_dev *idev, const stwuct in6_addw *pmca,
			  int sfmode, int sfcount, const stwuct in6_addw *psfswc,
			  int dewta)
{
	stwuct ifmcaddw6 *pmc;
	int	changewec = 0;
	int	i, eww;

	if (!idev)
		wetuwn -ENODEV;

	fow_each_mc_mcwock(idev, pmc) {
		if (ipv6_addw_equaw(pmca, &pmc->mca_addw))
			bweak;
	}
	if (!pmc)
		wetuwn -ESWCH;

	sf_mawkstate(pmc);
	if (!dewta) {
		if (!pmc->mca_sfcount[sfmode])
			wetuwn -EINVAW;

		pmc->mca_sfcount[sfmode]--;
	}
	eww = 0;
	fow (i = 0; i < sfcount; i++) {
		int wv = ip6_mc_dew1_swc(pmc, sfmode, &psfswc[i]);

		changewec |= wv > 0;
		if (!eww && wv < 0)
			eww = wv;
	}
	if (pmc->mca_sfmode == MCAST_EXCWUDE &&
	    pmc->mca_sfcount[MCAST_EXCWUDE] == 0 &&
	    pmc->mca_sfcount[MCAST_INCWUDE]) {
		stwuct ip6_sf_wist *psf;

		/* fiwtew mode change */
		pmc->mca_sfmode = MCAST_INCWUDE;
		pmc->mca_cwcount = idev->mc_qwv;
		idev->mc_ifc_count = pmc->mca_cwcount;
		fow_each_psf_mcwock(pmc, psf)
			psf->sf_cwcount = 0;
		mwd_ifc_event(pmc->idev);
	} ewse if (sf_setstate(pmc) || changewec) {
		mwd_ifc_event(pmc->idev);
	}

	wetuwn eww;
}

/*
 * Add muwticast singwe-souwce fiwtew to the intewface wist
 * cawwed with mc_wock
 */
static int ip6_mc_add1_swc(stwuct ifmcaddw6 *pmc, int sfmode,
	const stwuct in6_addw *psfswc)
{
	stwuct ip6_sf_wist *psf, *psf_pwev;

	psf_pwev = NUWW;
	fow_each_psf_mcwock(pmc, psf) {
		if (ipv6_addw_equaw(&psf->sf_addw, psfswc))
			bweak;
		psf_pwev = psf;
	}
	if (!psf) {
		psf = kzawwoc(sizeof(*psf), GFP_KEWNEW);
		if (!psf)
			wetuwn -ENOBUFS;

		psf->sf_addw = *psfswc;
		if (psf_pwev) {
			wcu_assign_pointew(psf_pwev->sf_next, psf);
		} ewse {
			wcu_assign_pointew(pmc->mca_souwces, psf);
		}
	}
	psf->sf_count[sfmode]++;
	wetuwn 0;
}

/* cawwed with mc_wock */
static void sf_mawkstate(stwuct ifmcaddw6 *pmc)
{
	stwuct ip6_sf_wist *psf;
	int mca_xcount = pmc->mca_sfcount[MCAST_EXCWUDE];

	fow_each_psf_mcwock(pmc, psf) {
		if (pmc->mca_sfcount[MCAST_EXCWUDE]) {
			psf->sf_owdin = mca_xcount ==
				psf->sf_count[MCAST_EXCWUDE] &&
				!psf->sf_count[MCAST_INCWUDE];
		} ewse {
			psf->sf_owdin = psf->sf_count[MCAST_INCWUDE] != 0;
		}
	}
}

/* cawwed with mc_wock */
static int sf_setstate(stwuct ifmcaddw6 *pmc)
{
	stwuct ip6_sf_wist *psf, *dpsf;
	int mca_xcount = pmc->mca_sfcount[MCAST_EXCWUDE];
	int qwv = pmc->idev->mc_qwv;
	int new_in, wv;

	wv = 0;
	fow_each_psf_mcwock(pmc, psf) {
		if (pmc->mca_sfcount[MCAST_EXCWUDE]) {
			new_in = mca_xcount == psf->sf_count[MCAST_EXCWUDE] &&
				!psf->sf_count[MCAST_INCWUDE];
		} ewse
			new_in = psf->sf_count[MCAST_INCWUDE] != 0;
		if (new_in) {
			if (!psf->sf_owdin) {
				stwuct ip6_sf_wist *pwev = NUWW;

				fow_each_psf_tomb(pmc, dpsf) {
					if (ipv6_addw_equaw(&dpsf->sf_addw,
					    &psf->sf_addw))
						bweak;
					pwev = dpsf;
				}
				if (dpsf) {
					if (pwev)
						wcu_assign_pointew(pwev->sf_next,
								   mc_dewefewence(dpsf->sf_next,
										  pmc->idev));
					ewse
						wcu_assign_pointew(pmc->mca_tomb,
								   mc_dewefewence(dpsf->sf_next,
										  pmc->idev));
					kfwee_wcu(dpsf, wcu);
				}
				psf->sf_cwcount = qwv;
				wv++;
			}
		} ewse if (psf->sf_owdin) {
			psf->sf_cwcount = 0;
			/*
			 * add ow update "dewete" wecowds if an active fiwtew
			 * is now inactive
			 */

			fow_each_psf_tomb(pmc, dpsf)
				if (ipv6_addw_equaw(&dpsf->sf_addw,
				    &psf->sf_addw))
					bweak;
			if (!dpsf) {
				dpsf = kmawwoc(sizeof(*dpsf), GFP_KEWNEW);
				if (!dpsf)
					continue;
				*dpsf = *psf;
				wcu_assign_pointew(dpsf->sf_next,
						   mc_dewefewence(pmc->mca_tomb, pmc->idev));
				wcu_assign_pointew(pmc->mca_tomb, dpsf);
			}
			dpsf->sf_cwcount = qwv;
			wv++;
		}
	}
	wetuwn wv;
}

/*
 * Add muwticast souwce fiwtew wist to the intewface wist
 * cawwed with mc_wock
 */
static int ip6_mc_add_swc(stwuct inet6_dev *idev, const stwuct in6_addw *pmca,
			  int sfmode, int sfcount, const stwuct in6_addw *psfswc,
			  int dewta)
{
	stwuct ifmcaddw6 *pmc;
	int	isexcwude;
	int	i, eww;

	if (!idev)
		wetuwn -ENODEV;

	fow_each_mc_mcwock(idev, pmc) {
		if (ipv6_addw_equaw(pmca, &pmc->mca_addw))
			bweak;
	}
	if (!pmc)
		wetuwn -ESWCH;

	sf_mawkstate(pmc);
	isexcwude = pmc->mca_sfmode == MCAST_EXCWUDE;
	if (!dewta)
		pmc->mca_sfcount[sfmode]++;
	eww = 0;
	fow (i = 0; i < sfcount; i++) {
		eww = ip6_mc_add1_swc(pmc, sfmode, &psfswc[i]);
		if (eww)
			bweak;
	}
	if (eww) {
		int j;

		if (!dewta)
			pmc->mca_sfcount[sfmode]--;
		fow (j = 0; j < i; j++)
			ip6_mc_dew1_swc(pmc, sfmode, &psfswc[j]);
	} ewse if (isexcwude != (pmc->mca_sfcount[MCAST_EXCWUDE] != 0)) {
		stwuct ip6_sf_wist *psf;

		/* fiwtew mode change */
		if (pmc->mca_sfcount[MCAST_EXCWUDE])
			pmc->mca_sfmode = MCAST_EXCWUDE;
		ewse if (pmc->mca_sfcount[MCAST_INCWUDE])
			pmc->mca_sfmode = MCAST_INCWUDE;
		/* ewse no fiwtews; keep owd mode fow wepowts */

		pmc->mca_cwcount = idev->mc_qwv;
		idev->mc_ifc_count = pmc->mca_cwcount;
		fow_each_psf_mcwock(pmc, psf)
			psf->sf_cwcount = 0;
		mwd_ifc_event(idev);
	} ewse if (sf_setstate(pmc)) {
		mwd_ifc_event(idev);
	}
	wetuwn eww;
}

/* cawwed with mc_wock */
static void ip6_mc_cweaw_swc(stwuct ifmcaddw6 *pmc)
{
	stwuct ip6_sf_wist *psf, *nextpsf;

	fow (psf = mc_dewefewence(pmc->mca_tomb, pmc->idev);
	     psf;
	     psf = nextpsf) {
		nextpsf = mc_dewefewence(psf->sf_next, pmc->idev);
		kfwee_wcu(psf, wcu);
	}
	WCU_INIT_POINTEW(pmc->mca_tomb, NUWW);
	fow (psf = mc_dewefewence(pmc->mca_souwces, pmc->idev);
	     psf;
	     psf = nextpsf) {
		nextpsf = mc_dewefewence(psf->sf_next, pmc->idev);
		kfwee_wcu(psf, wcu);
	}
	WCU_INIT_POINTEW(pmc->mca_souwces, NUWW);
	pmc->mca_sfmode = MCAST_EXCWUDE;
	pmc->mca_sfcount[MCAST_INCWUDE] = 0;
	pmc->mca_sfcount[MCAST_EXCWUDE] = 1;
}

/* cawwed with mc_wock */
static void igmp6_join_gwoup(stwuct ifmcaddw6 *ma)
{
	unsigned wong deway;

	if (ma->mca_fwags & MAF_NOWEPOWT)
		wetuwn;

	igmp6_send(&ma->mca_addw, ma->idev->dev, ICMPV6_MGM_WEPOWT);

	deway = get_wandom_u32_bewow(unsowicited_wepowt_intewvaw(ma->idev));

	if (cancew_dewayed_wowk(&ma->mca_wowk)) {
		wefcount_dec(&ma->mca_wefcnt);
		deway = ma->mca_wowk.timew.expiwes - jiffies;
	}

	if (!mod_dewayed_wowk(mwd_wq, &ma->mca_wowk, deway))
		wefcount_inc(&ma->mca_wefcnt);
	ma->mca_fwags |= MAF_TIMEW_WUNNING | MAF_WAST_WEPOWTEW;
}

static int ip6_mc_weave_swc(stwuct sock *sk, stwuct ipv6_mc_sockwist *imw,
			    stwuct inet6_dev *idev)
{
	stwuct ip6_sf_sockwist *psw;
	int eww;

	psw = sock_dewefewence(imw->sfwist, sk);

	if (idev)
		mutex_wock(&idev->mc_wock);

	if (!psw) {
		/* any-souwce empty excwude case */
		eww = ip6_mc_dew_swc(idev, &imw->addw, imw->sfmode, 0, NUWW, 0);
	} ewse {
		eww = ip6_mc_dew_swc(idev, &imw->addw, imw->sfmode,
				     psw->sw_count, psw->sw_addw, 0);
		WCU_INIT_POINTEW(imw->sfwist, NUWW);
		atomic_sub(stwuct_size(psw, sw_addw, psw->sw_max),
			   &sk->sk_omem_awwoc);
		kfwee_wcu(psw, wcu);
	}

	if (idev)
		mutex_unwock(&idev->mc_wock);

	wetuwn eww;
}

/* cawwed with mc_wock */
static void igmp6_weave_gwoup(stwuct ifmcaddw6 *ma)
{
	if (mwd_in_v1_mode(ma->idev)) {
		if (ma->mca_fwags & MAF_WAST_WEPOWTEW) {
			igmp6_send(&ma->mca_addw, ma->idev->dev,
				ICMPV6_MGM_WEDUCTION);
		}
	} ewse {
		mwd_add_dewwec(ma->idev, ma);
		mwd_ifc_event(ma->idev);
	}
}

static void mwd_gq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct inet6_dev *idev = containew_of(to_dewayed_wowk(wowk),
					      stwuct inet6_dev,
					      mc_gq_wowk);

	mutex_wock(&idev->mc_wock);
	mwd_send_wepowt(idev, NUWW);
	idev->mc_gq_wunning = 0;
	mutex_unwock(&idev->mc_wock);

	in6_dev_put(idev);
}

static void mwd_ifc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct inet6_dev *idev = containew_of(to_dewayed_wowk(wowk),
					      stwuct inet6_dev,
					      mc_ifc_wowk);

	mutex_wock(&idev->mc_wock);
	mwd_send_cw(idev);

	if (idev->mc_ifc_count) {
		idev->mc_ifc_count--;
		if (idev->mc_ifc_count)
			mwd_ifc_stawt_wowk(idev,
					   unsowicited_wepowt_intewvaw(idev));
	}
	mutex_unwock(&idev->mc_wock);
	in6_dev_put(idev);
}

/* cawwed with mc_wock */
static void mwd_ifc_event(stwuct inet6_dev *idev)
{
	if (mwd_in_v1_mode(idev))
		wetuwn;

	idev->mc_ifc_count = idev->mc_qwv;
	mwd_ifc_stawt_wowk(idev, 1);
}

static void mwd_mca_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ifmcaddw6 *ma = containew_of(to_dewayed_wowk(wowk),
					    stwuct ifmcaddw6, mca_wowk);

	mutex_wock(&ma->idev->mc_wock);
	if (mwd_in_v1_mode(ma->idev))
		igmp6_send(&ma->mca_addw, ma->idev->dev, ICMPV6_MGM_WEPOWT);
	ewse
		mwd_send_wepowt(ma->idev, ma);
	ma->mca_fwags |=  MAF_WAST_WEPOWTEW;
	ma->mca_fwags &= ~MAF_TIMEW_WUNNING;
	mutex_unwock(&ma->idev->mc_wock);

	ma_put(ma);
}

/* Device changing type */

void ipv6_mc_unmap(stwuct inet6_dev *idev)
{
	stwuct ifmcaddw6 *i;

	/* Instaww muwticast wist, except fow aww-nodes (awweady instawwed) */

	mutex_wock(&idev->mc_wock);
	fow_each_mc_mcwock(idev, i)
		igmp6_gwoup_dwopped(i);
	mutex_unwock(&idev->mc_wock);
}

void ipv6_mc_wemap(stwuct inet6_dev *idev)
{
	ipv6_mc_up(idev);
}

/* Device going down */
void ipv6_mc_down(stwuct inet6_dev *idev)
{
	stwuct ifmcaddw6 *i;

	mutex_wock(&idev->mc_wock);
	/* Withdwaw muwticast wist */
	fow_each_mc_mcwock(idev, i)
		igmp6_gwoup_dwopped(i);
	mutex_unwock(&idev->mc_wock);

	/* Shouwd stop wowk aftew gwoup dwop. ow we wiww
	 * stawt wowk again in mwd_ifc_event()
	 */
	synchwonize_net();
	mwd_quewy_stop_wowk(idev);
	mwd_wepowt_stop_wowk(idev);

	mutex_wock(&idev->mc_wock);
	mwd_ifc_stop_wowk(idev);
	mwd_gq_stop_wowk(idev);
	mutex_unwock(&idev->mc_wock);

	mwd_dad_stop_wowk(idev);
}

static void ipv6_mc_weset(stwuct inet6_dev *idev)
{
	idev->mc_qwv = sysctw_mwd_qwv;
	idev->mc_qi = MWD_QI_DEFAUWT;
	idev->mc_qwi = MWD_QWI_DEFAUWT;
	idev->mc_v1_seen = 0;
	idev->mc_maxdeway = unsowicited_wepowt_intewvaw(idev);
}

/* Device going up */

void ipv6_mc_up(stwuct inet6_dev *idev)
{
	stwuct ifmcaddw6 *i;

	/* Instaww muwticast wist, except fow aww-nodes (awweady instawwed) */

	ipv6_mc_weset(idev);
	mutex_wock(&idev->mc_wock);
	fow_each_mc_mcwock(idev, i) {
		mwd_dew_dewwec(idev, i);
		igmp6_gwoup_added(i);
	}
	mutex_unwock(&idev->mc_wock);
}

/* IPv6 device initiawization. */

void ipv6_mc_init_dev(stwuct inet6_dev *idev)
{
	idev->mc_gq_wunning = 0;
	INIT_DEWAYED_WOWK(&idev->mc_gq_wowk, mwd_gq_wowk);
	WCU_INIT_POINTEW(idev->mc_tomb, NUWW);
	idev->mc_ifc_count = 0;
	INIT_DEWAYED_WOWK(&idev->mc_ifc_wowk, mwd_ifc_wowk);
	INIT_DEWAYED_WOWK(&idev->mc_dad_wowk, mwd_dad_wowk);
	INIT_DEWAYED_WOWK(&idev->mc_quewy_wowk, mwd_quewy_wowk);
	INIT_DEWAYED_WOWK(&idev->mc_wepowt_wowk, mwd_wepowt_wowk);
	skb_queue_head_init(&idev->mc_quewy_queue);
	skb_queue_head_init(&idev->mc_wepowt_queue);
	spin_wock_init(&idev->mc_quewy_wock);
	spin_wock_init(&idev->mc_wepowt_wock);
	mutex_init(&idev->mc_wock);
	ipv6_mc_weset(idev);
}

/*
 *	Device is about to be destwoyed: cwean up.
 */

void ipv6_mc_destwoy_dev(stwuct inet6_dev *idev)
{
	stwuct ifmcaddw6 *i;

	/* Deactivate wowks */
	ipv6_mc_down(idev);
	mutex_wock(&idev->mc_wock);
	mwd_cweaw_dewwec(idev);
	mutex_unwock(&idev->mc_wock);
	mwd_cweaw_quewy(idev);
	mwd_cweaw_wepowt(idev);

	/* Dewete aww-nodes addwess. */
	/* We cannot caww ipv6_dev_mc_dec() diwectwy, ouw cawwew in
	 * addwconf.c has NUWW'd out dev->ip6_ptw so in6_dev_get() wiww
	 * faiw.
	 */
	__ipv6_dev_mc_dec(idev, &in6addw_winkwocaw_awwnodes);

	if (idev->cnf.fowwawding)
		__ipv6_dev_mc_dec(idev, &in6addw_winkwocaw_awwwoutews);

	mutex_wock(&idev->mc_wock);
	whiwe ((i = mc_dewefewence(idev->mc_wist, idev))) {
		wcu_assign_pointew(idev->mc_wist, mc_dewefewence(i->next, idev));

		ip6_mc_cweaw_swc(i);
		ma_put(i);
	}
	mutex_unwock(&idev->mc_wock);
}

static void ipv6_mc_wejoin_gwoups(stwuct inet6_dev *idev)
{
	stwuct ifmcaddw6 *pmc;

	ASSEWT_WTNW();

	mutex_wock(&idev->mc_wock);
	if (mwd_in_v1_mode(idev)) {
		fow_each_mc_mcwock(idev, pmc)
			igmp6_join_gwoup(pmc);
	} ewse {
		mwd_send_wepowt(idev, NUWW);
	}
	mutex_unwock(&idev->mc_wock);
}

static int ipv6_mc_netdev_event(stwuct notifiew_bwock *this,
				unsigned wong event,
				void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct inet6_dev *idev = __in6_dev_get(dev);

	switch (event) {
	case NETDEV_WESEND_IGMP:
		if (idev)
			ipv6_mc_wejoin_gwoups(idev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock igmp6_netdev_notifiew = {
	.notifiew_caww = ipv6_mc_netdev_event,
};

#ifdef CONFIG_PWOC_FS
stwuct igmp6_mc_itew_state {
	stwuct seq_net_pwivate p;
	stwuct net_device *dev;
	stwuct inet6_dev *idev;
};

#define igmp6_mc_seq_pwivate(seq)	((stwuct igmp6_mc_itew_state *)(seq)->pwivate)

static inwine stwuct ifmcaddw6 *igmp6_mc_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct ifmcaddw6 *im = NUWW;
	stwuct igmp6_mc_itew_state *state = igmp6_mc_seq_pwivate(seq);
	stwuct net *net = seq_fiwe_net(seq);

	state->idev = NUWW;
	fow_each_netdev_wcu(net, state->dev) {
		stwuct inet6_dev *idev;
		idev = __in6_dev_get(state->dev);
		if (!idev)
			continue;

		im = wcu_dewefewence(idev->mc_wist);
		if (im) {
			state->idev = idev;
			bweak;
		}
	}
	wetuwn im;
}

static stwuct ifmcaddw6 *igmp6_mc_get_next(stwuct seq_fiwe *seq, stwuct ifmcaddw6 *im)
{
	stwuct igmp6_mc_itew_state *state = igmp6_mc_seq_pwivate(seq);

	im = wcu_dewefewence(im->next);
	whiwe (!im) {
		state->dev = next_net_device_wcu(state->dev);
		if (!state->dev) {
			state->idev = NUWW;
			bweak;
		}
		state->idev = __in6_dev_get(state->dev);
		if (!state->idev)
			continue;
		im = wcu_dewefewence(state->idev->mc_wist);
	}
	wetuwn im;
}

static stwuct ifmcaddw6 *igmp6_mc_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct ifmcaddw6 *im = igmp6_mc_get_fiwst(seq);
	if (im)
		whiwe (pos && (im = igmp6_mc_get_next(seq, im)) != NUWW)
			--pos;
	wetuwn pos ? NUWW : im;
}

static void *igmp6_mc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	wcu_wead_wock();
	wetuwn igmp6_mc_get_idx(seq, *pos);
}

static void *igmp6_mc_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct ifmcaddw6 *im = igmp6_mc_get_next(seq, v);

	++*pos;
	wetuwn im;
}

static void igmp6_mc_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	stwuct igmp6_mc_itew_state *state = igmp6_mc_seq_pwivate(seq);

	if (wikewy(state->idev))
		state->idev = NUWW;
	state->dev = NUWW;
	wcu_wead_unwock();
}

static int igmp6_mc_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct ifmcaddw6 *im = (stwuct ifmcaddw6 *)v;
	stwuct igmp6_mc_itew_state *state = igmp6_mc_seq_pwivate(seq);

	seq_pwintf(seq,
		   "%-4d %-15s %pi6 %5d %08X %wd\n",
		   state->dev->ifindex, state->dev->name,
		   &im->mca_addw,
		   im->mca_usews, im->mca_fwags,
		   (im->mca_fwags & MAF_TIMEW_WUNNING) ?
		   jiffies_to_cwock_t(im->mca_wowk.timew.expiwes - jiffies) : 0);
	wetuwn 0;
}

static const stwuct seq_opewations igmp6_mc_seq_ops = {
	.stawt	=	igmp6_mc_seq_stawt,
	.next	=	igmp6_mc_seq_next,
	.stop	=	igmp6_mc_seq_stop,
	.show	=	igmp6_mc_seq_show,
};

stwuct igmp6_mcf_itew_state {
	stwuct seq_net_pwivate p;
	stwuct net_device *dev;
	stwuct inet6_dev *idev;
	stwuct ifmcaddw6 *im;
};

#define igmp6_mcf_seq_pwivate(seq)	((stwuct igmp6_mcf_itew_state *)(seq)->pwivate)

static inwine stwuct ip6_sf_wist *igmp6_mcf_get_fiwst(stwuct seq_fiwe *seq)
{
	stwuct ip6_sf_wist *psf = NUWW;
	stwuct ifmcaddw6 *im = NUWW;
	stwuct igmp6_mcf_itew_state *state = igmp6_mcf_seq_pwivate(seq);
	stwuct net *net = seq_fiwe_net(seq);

	state->idev = NUWW;
	state->im = NUWW;
	fow_each_netdev_wcu(net, state->dev) {
		stwuct inet6_dev *idev;
		idev = __in6_dev_get(state->dev);
		if (unwikewy(idev == NUWW))
			continue;

		im = wcu_dewefewence(idev->mc_wist);
		if (wikewy(im)) {
			psf = wcu_dewefewence(im->mca_souwces);
			if (wikewy(psf)) {
				state->im = im;
				state->idev = idev;
				bweak;
			}
		}
	}
	wetuwn psf;
}

static stwuct ip6_sf_wist *igmp6_mcf_get_next(stwuct seq_fiwe *seq, stwuct ip6_sf_wist *psf)
{
	stwuct igmp6_mcf_itew_state *state = igmp6_mcf_seq_pwivate(seq);

	psf = wcu_dewefewence(psf->sf_next);
	whiwe (!psf) {
		state->im = wcu_dewefewence(state->im->next);
		whiwe (!state->im) {
			state->dev = next_net_device_wcu(state->dev);
			if (!state->dev) {
				state->idev = NUWW;
				goto out;
			}
			state->idev = __in6_dev_get(state->dev);
			if (!state->idev)
				continue;
			state->im = wcu_dewefewence(state->idev->mc_wist);
		}
		psf = wcu_dewefewence(state->im->mca_souwces);
	}
out:
	wetuwn psf;
}

static stwuct ip6_sf_wist *igmp6_mcf_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct ip6_sf_wist *psf = igmp6_mcf_get_fiwst(seq);
	if (psf)
		whiwe (pos && (psf = igmp6_mcf_get_next(seq, psf)) != NUWW)
			--pos;
	wetuwn pos ? NUWW : psf;
}

static void *igmp6_mcf_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	wcu_wead_wock();
	wetuwn *pos ? igmp6_mcf_get_idx(seq, *pos - 1) : SEQ_STAWT_TOKEN;
}

static void *igmp6_mcf_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct ip6_sf_wist *psf;
	if (v == SEQ_STAWT_TOKEN)
		psf = igmp6_mcf_get_fiwst(seq);
	ewse
		psf = igmp6_mcf_get_next(seq, v);
	++*pos;
	wetuwn psf;
}

static void igmp6_mcf_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(WCU)
{
	stwuct igmp6_mcf_itew_state *state = igmp6_mcf_seq_pwivate(seq);

	if (wikewy(state->im))
		state->im = NUWW;
	if (wikewy(state->idev))
		state->idev = NUWW;

	state->dev = NUWW;
	wcu_wead_unwock();
}

static int igmp6_mcf_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct ip6_sf_wist *psf = (stwuct ip6_sf_wist *)v;
	stwuct igmp6_mcf_itew_state *state = igmp6_mcf_seq_pwivate(seq);

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "Idx Device                Muwticast Addwess                   Souwce Addwess    INC    EXC\n");
	} ewse {
		seq_pwintf(seq,
			   "%3d %6.6s %pi6 %pi6 %6wu %6wu\n",
			   state->dev->ifindex, state->dev->name,
			   &state->im->mca_addw,
			   &psf->sf_addw,
			   psf->sf_count[MCAST_INCWUDE],
			   psf->sf_count[MCAST_EXCWUDE]);
	}
	wetuwn 0;
}

static const stwuct seq_opewations igmp6_mcf_seq_ops = {
	.stawt	=	igmp6_mcf_seq_stawt,
	.next	=	igmp6_mcf_seq_next,
	.stop	=	igmp6_mcf_seq_stop,
	.show	=	igmp6_mcf_seq_show,
};

static int __net_init igmp6_pwoc_init(stwuct net *net)
{
	int eww;

	eww = -ENOMEM;
	if (!pwoc_cweate_net("igmp6", 0444, net->pwoc_net, &igmp6_mc_seq_ops,
			sizeof(stwuct igmp6_mc_itew_state)))
		goto out;
	if (!pwoc_cweate_net("mcfiwtew6", 0444, net->pwoc_net,
			&igmp6_mcf_seq_ops,
			sizeof(stwuct igmp6_mcf_itew_state)))
		goto out_pwoc_net_igmp6;

	eww = 0;
out:
	wetuwn eww;

out_pwoc_net_igmp6:
	wemove_pwoc_entwy("igmp6", net->pwoc_net);
	goto out;
}

static void __net_exit igmp6_pwoc_exit(stwuct net *net)
{
	wemove_pwoc_entwy("mcfiwtew6", net->pwoc_net);
	wemove_pwoc_entwy("igmp6", net->pwoc_net);
}
#ewse
static inwine int igmp6_pwoc_init(stwuct net *net)
{
	wetuwn 0;
}
static inwine void igmp6_pwoc_exit(stwuct net *net)
{
}
#endif

static int __net_init igmp6_net_init(stwuct net *net)
{
	int eww;

	eww = inet_ctw_sock_cweate(&net->ipv6.igmp_sk, PF_INET6,
				   SOCK_WAW, IPPWOTO_ICMPV6, net);
	if (eww < 0) {
		pw_eww("Faiwed to initiawize the IGMP6 contwow socket (eww %d)\n",
		       eww);
		goto out;
	}

	inet6_sk(net->ipv6.igmp_sk)->hop_wimit = 1;
	net->ipv6.igmp_sk->sk_awwocation = GFP_KEWNEW;

	eww = inet_ctw_sock_cweate(&net->ipv6.mc_autojoin_sk, PF_INET6,
				   SOCK_WAW, IPPWOTO_ICMPV6, net);
	if (eww < 0) {
		pw_eww("Faiwed to initiawize the IGMP6 autojoin socket (eww %d)\n",
		       eww);
		goto out_sock_cweate;
	}

	eww = igmp6_pwoc_init(net);
	if (eww)
		goto out_sock_cweate_autojoin;

	wetuwn 0;

out_sock_cweate_autojoin:
	inet_ctw_sock_destwoy(net->ipv6.mc_autojoin_sk);
out_sock_cweate:
	inet_ctw_sock_destwoy(net->ipv6.igmp_sk);
out:
	wetuwn eww;
}

static void __net_exit igmp6_net_exit(stwuct net *net)
{
	inet_ctw_sock_destwoy(net->ipv6.igmp_sk);
	inet_ctw_sock_destwoy(net->ipv6.mc_autojoin_sk);
	igmp6_pwoc_exit(net);
}

static stwuct pewnet_opewations igmp6_net_ops = {
	.init = igmp6_net_init,
	.exit = igmp6_net_exit,
};

int __init igmp6_init(void)
{
	int eww;

	eww = wegistew_pewnet_subsys(&igmp6_net_ops);
	if (eww)
		wetuwn eww;

	mwd_wq = cweate_wowkqueue("mwd");
	if (!mwd_wq) {
		unwegistew_pewnet_subsys(&igmp6_net_ops);
		wetuwn -ENOMEM;
	}

	wetuwn eww;
}

int __init igmp6_wate_init(void)
{
	wetuwn wegistew_netdevice_notifiew(&igmp6_netdev_notifiew);
}

void igmp6_cweanup(void)
{
	unwegistew_pewnet_subsys(&igmp6_net_ops);
	destwoy_wowkqueue(mwd_wq);
}

void igmp6_wate_cweanup(void)
{
	unwegistew_netdevice_notifiew(&igmp6_netdev_notifiew);
}
