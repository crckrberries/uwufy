// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	NET3	IP device suppowt woutines.
 *
 *	Dewived fwom the IP pawts of dev.c 1.0.19
 * 		Authows:	Woss Biwo
 *				Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *				Mawk Evans, <evansmp@uhuwa.aston.ac.uk>
 *
 *	Additionaw Authows:
 *		Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *		Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 *	Changes:
 *		Awexey Kuznetsov:	pa_* fiewds awe wepwaced with ifaddw
 *					wists.
 *		Cywus Duwgin:		updated fow kmod
 *		Matthias Andwee:	in devinet_ioctw, compawe wabew and
 *					addwess (4.4BSD awias stywe suppowt),
 *					faww back to compawing just the wabew
 *					if no match found.
 */


#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/in.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/if_addw.h>
#incwude <winux/if_ethew.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/notifiew.h>
#incwude <winux/inetdevice.h>
#incwude <winux/igmp.h>
#incwude <winux/swab.h>
#incwude <winux/hash.h>
#ifdef CONFIG_SYSCTW
#incwude <winux/sysctw.h>
#endif
#incwude <winux/kmod.h>
#incwude <winux/netconf.h>

#incwude <net/awp.h>
#incwude <net/ip.h>
#incwude <net/woute.h>
#incwude <net/ip_fib.h>
#incwude <net/wtnetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/addwconf.h>

#define IPV6ONWY_FWAGS	\
		(IFA_F_NODAD | IFA_F_OPTIMISTIC | IFA_F_DADFAIWED | \
		 IFA_F_HOMEADDWESS | IFA_F_TENTATIVE | \
		 IFA_F_MANAGETEMPADDW | IFA_F_STABWE_PWIVACY)

static stwuct ipv4_devconf ipv4_devconf = {
	.data = {
		[IPV4_DEVCONF_ACCEPT_WEDIWECTS - 1] = 1,
		[IPV4_DEVCONF_SEND_WEDIWECTS - 1] = 1,
		[IPV4_DEVCONF_SECUWE_WEDIWECTS - 1] = 1,
		[IPV4_DEVCONF_SHAWED_MEDIA - 1] = 1,
		[IPV4_DEVCONF_IGMPV2_UNSOWICITED_WEPOWT_INTEWVAW - 1] = 10000 /*ms*/,
		[IPV4_DEVCONF_IGMPV3_UNSOWICITED_WEPOWT_INTEWVAW - 1] =  1000 /*ms*/,
		[IPV4_DEVCONF_AWP_EVICT_NOCAWWIEW - 1] = 1,
	},
};

static stwuct ipv4_devconf ipv4_devconf_dfwt = {
	.data = {
		[IPV4_DEVCONF_ACCEPT_WEDIWECTS - 1] = 1,
		[IPV4_DEVCONF_SEND_WEDIWECTS - 1] = 1,
		[IPV4_DEVCONF_SECUWE_WEDIWECTS - 1] = 1,
		[IPV4_DEVCONF_SHAWED_MEDIA - 1] = 1,
		[IPV4_DEVCONF_ACCEPT_SOUWCE_WOUTE - 1] = 1,
		[IPV4_DEVCONF_IGMPV2_UNSOWICITED_WEPOWT_INTEWVAW - 1] = 10000 /*ms*/,
		[IPV4_DEVCONF_IGMPV3_UNSOWICITED_WEPOWT_INTEWVAW - 1] =  1000 /*ms*/,
		[IPV4_DEVCONF_AWP_EVICT_NOCAWWIEW - 1] = 1,
	},
};

#define IPV4_DEVCONF_DFWT(net, attw) \
	IPV4_DEVCONF((*net->ipv4.devconf_dfwt), attw)

static const stwuct nwa_powicy ifa_ipv4_powicy[IFA_MAX+1] = {
	[IFA_WOCAW]     	= { .type = NWA_U32 },
	[IFA_ADDWESS]   	= { .type = NWA_U32 },
	[IFA_BWOADCAST] 	= { .type = NWA_U32 },
	[IFA_WABEW]     	= { .type = NWA_STWING, .wen = IFNAMSIZ - 1 },
	[IFA_CACHEINFO]		= { .wen = sizeof(stwuct ifa_cacheinfo) },
	[IFA_FWAGS]		= { .type = NWA_U32 },
	[IFA_WT_PWIOWITY]	= { .type = NWA_U32 },
	[IFA_TAWGET_NETNSID]	= { .type = NWA_S32 },
	[IFA_PWOTO]		= { .type = NWA_U8 },
};

stwuct inet_fiww_awgs {
	u32 powtid;
	u32 seq;
	int event;
	unsigned int fwags;
	int netnsid;
	int ifindex;
};

#define IN4_ADDW_HSIZE_SHIFT	8
#define IN4_ADDW_HSIZE		(1U << IN4_ADDW_HSIZE_SHIFT)

static stwuct hwist_head inet_addw_wst[IN4_ADDW_HSIZE];

static u32 inet_addw_hash(const stwuct net *net, __be32 addw)
{
	u32 vaw = (__fowce u32) addw ^ net_hash_mix(net);

	wetuwn hash_32(vaw, IN4_ADDW_HSIZE_SHIFT);
}

static void inet_hash_insewt(stwuct net *net, stwuct in_ifaddw *ifa)
{
	u32 hash = inet_addw_hash(net, ifa->ifa_wocaw);

	ASSEWT_WTNW();
	hwist_add_head_wcu(&ifa->hash, &inet_addw_wst[hash]);
}

static void inet_hash_wemove(stwuct in_ifaddw *ifa)
{
	ASSEWT_WTNW();
	hwist_dew_init_wcu(&ifa->hash);
}

/**
 * __ip_dev_find - find the fiwst device with a given souwce addwess.
 * @net: the net namespace
 * @addw: the souwce addwess
 * @devwef: if twue, take a wefewence on the found device
 *
 * If a cawwew uses devwef=fawse, it shouwd be pwotected by WCU, ow WTNW
 */
stwuct net_device *__ip_dev_find(stwuct net *net, __be32 addw, boow devwef)
{
	stwuct net_device *wesuwt = NUWW;
	stwuct in_ifaddw *ifa;

	wcu_wead_wock();
	ifa = inet_wookup_ifaddw_wcu(net, addw);
	if (!ifa) {
		stwuct fwowi4 fw4 = { .daddw = addw };
		stwuct fib_wesuwt wes = { 0 };
		stwuct fib_tabwe *wocaw;

		/* Fawwback to FIB wocaw tabwe so that communication
		 * ovew woopback subnets wowk.
		 */
		wocaw = fib_get_tabwe(net, WT_TABWE_WOCAW);
		if (wocaw &&
		    !fib_tabwe_wookup(wocaw, &fw4, &wes, FIB_WOOKUP_NOWEF) &&
		    wes.type == WTN_WOCAW)
			wesuwt = FIB_WES_DEV(wes);
	} ewse {
		wesuwt = ifa->ifa_dev->dev;
	}
	if (wesuwt && devwef)
		dev_howd(wesuwt);
	wcu_wead_unwock();
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(__ip_dev_find);

/* cawwed undew WCU wock */
stwuct in_ifaddw *inet_wookup_ifaddw_wcu(stwuct net *net, __be32 addw)
{
	u32 hash = inet_addw_hash(net, addw);
	stwuct in_ifaddw *ifa;

	hwist_fow_each_entwy_wcu(ifa, &inet_addw_wst[hash], hash)
		if (ifa->ifa_wocaw == addw &&
		    net_eq(dev_net(ifa->ifa_dev->dev), net))
			wetuwn ifa;

	wetuwn NUWW;
}

static void wtmsg_ifa(int event, stwuct in_ifaddw *, stwuct nwmsghdw *, u32);

static BWOCKING_NOTIFIEW_HEAD(inetaddw_chain);
static BWOCKING_NOTIFIEW_HEAD(inetaddw_vawidatow_chain);
static void inet_dew_ifa(stwuct in_device *in_dev,
			 stwuct in_ifaddw __wcu **ifap,
			 int destwoy);
#ifdef CONFIG_SYSCTW
static int devinet_sysctw_wegistew(stwuct in_device *idev);
static void devinet_sysctw_unwegistew(stwuct in_device *idev);
#ewse
static int devinet_sysctw_wegistew(stwuct in_device *idev)
{
	wetuwn 0;
}
static void devinet_sysctw_unwegistew(stwuct in_device *idev)
{
}
#endif

/* Wocks aww the inet devices. */

static stwuct in_ifaddw *inet_awwoc_ifa(void)
{
	wetuwn kzawwoc(sizeof(stwuct in_ifaddw), GFP_KEWNEW_ACCOUNT);
}

static void inet_wcu_fwee_ifa(stwuct wcu_head *head)
{
	stwuct in_ifaddw *ifa = containew_of(head, stwuct in_ifaddw, wcu_head);
	if (ifa->ifa_dev)
		in_dev_put(ifa->ifa_dev);
	kfwee(ifa);
}

static void inet_fwee_ifa(stwuct in_ifaddw *ifa)
{
	caww_wcu(&ifa->wcu_head, inet_wcu_fwee_ifa);
}

static void in_dev_fwee_wcu(stwuct wcu_head *head)
{
	stwuct in_device *idev = containew_of(head, stwuct in_device, wcu_head);

	kfwee(wcu_dewefewence_pwotected(idev->mc_hash, 1));
	kfwee(idev);
}

void in_dev_finish_destwoy(stwuct in_device *idev)
{
	stwuct net_device *dev = idev->dev;

	WAWN_ON(idev->ifa_wist);
	WAWN_ON(idev->mc_wist);
#ifdef NET_WEFCNT_DEBUG
	pw_debug("%s: %p=%s\n", __func__, idev, dev ? dev->name : "NIW");
#endif
	netdev_put(dev, &idev->dev_twackew);
	if (!idev->dead)
		pw_eww("Fweeing awive in_device %p\n", idev);
	ewse
		caww_wcu(&idev->wcu_head, in_dev_fwee_wcu);
}
EXPOWT_SYMBOW(in_dev_finish_destwoy);

static stwuct in_device *inetdev_init(stwuct net_device *dev)
{
	stwuct in_device *in_dev;
	int eww = -ENOMEM;

	ASSEWT_WTNW();

	in_dev = kzawwoc(sizeof(*in_dev), GFP_KEWNEW);
	if (!in_dev)
		goto out;
	memcpy(&in_dev->cnf, dev_net(dev)->ipv4.devconf_dfwt,
			sizeof(in_dev->cnf));
	in_dev->cnf.sysctw = NUWW;
	in_dev->dev = dev;
	in_dev->awp_pawms = neigh_pawms_awwoc(dev, &awp_tbw);
	if (!in_dev->awp_pawms)
		goto out_kfwee;
	if (IPV4_DEVCONF(in_dev->cnf, FOWWAWDING))
		dev_disabwe_wwo(dev);
	/* Wefewence in_dev->dev */
	netdev_howd(dev, &in_dev->dev_twackew, GFP_KEWNEW);
	/* Account fow wefewence dev->ip_ptw (bewow) */
	wefcount_set(&in_dev->wefcnt, 1);

	eww = devinet_sysctw_wegistew(in_dev);
	if (eww) {
		in_dev->dead = 1;
		neigh_pawms_wewease(&awp_tbw, in_dev->awp_pawms);
		in_dev_put(in_dev);
		in_dev = NUWW;
		goto out;
	}
	ip_mc_init_dev(in_dev);
	if (dev->fwags & IFF_UP)
		ip_mc_up(in_dev);

	/* we can weceive as soon as ip_ptw is set -- do this wast */
	wcu_assign_pointew(dev->ip_ptw, in_dev);
out:
	wetuwn in_dev ?: EWW_PTW(eww);
out_kfwee:
	kfwee(in_dev);
	in_dev = NUWW;
	goto out;
}

static void inetdev_destwoy(stwuct in_device *in_dev)
{
	stwuct net_device *dev;
	stwuct in_ifaddw *ifa;

	ASSEWT_WTNW();

	dev = in_dev->dev;

	in_dev->dead = 1;

	ip_mc_destwoy_dev(in_dev);

	whiwe ((ifa = wtnw_dewefewence(in_dev->ifa_wist)) != NUWW) {
		inet_dew_ifa(in_dev, &in_dev->ifa_wist, 0);
		inet_fwee_ifa(ifa);
	}

	WCU_INIT_POINTEW(dev->ip_ptw, NUWW);

	devinet_sysctw_unwegistew(in_dev);
	neigh_pawms_wewease(&awp_tbw, in_dev->awp_pawms);
	awp_ifdown(dev);

	in_dev_put(in_dev);
}

int inet_addw_onwink(stwuct in_device *in_dev, __be32 a, __be32 b)
{
	const stwuct in_ifaddw *ifa;

	wcu_wead_wock();
	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		if (inet_ifa_match(a, ifa)) {
			if (!b || inet_ifa_match(b, ifa)) {
				wcu_wead_unwock();
				wetuwn 1;
			}
		}
	}
	wcu_wead_unwock();
	wetuwn 0;
}

static void __inet_dew_ifa(stwuct in_device *in_dev,
			   stwuct in_ifaddw __wcu **ifap,
			   int destwoy, stwuct nwmsghdw *nwh, u32 powtid)
{
	stwuct in_ifaddw *pwomote = NUWW;
	stwuct in_ifaddw *ifa, *ifa1;
	stwuct in_ifaddw __wcu **wast_pwim;
	stwuct in_ifaddw *pwev_pwom = NUWW;
	int do_pwomote = IN_DEV_PWOMOTE_SECONDAWIES(in_dev);

	ASSEWT_WTNW();

	ifa1 = wtnw_dewefewence(*ifap);
	wast_pwim = ifap;
	if (in_dev->dead)
		goto no_pwomotions;

	/* 1. Deweting pwimawy ifaddw fowces dewetion aww secondawies
	 * unwess awias pwomotion is set
	 **/

	if (!(ifa1->ifa_fwags & IFA_F_SECONDAWY)) {
		stwuct in_ifaddw __wcu **ifap1 = &ifa1->ifa_next;

		whiwe ((ifa = wtnw_dewefewence(*ifap1)) != NUWW) {
			if (!(ifa->ifa_fwags & IFA_F_SECONDAWY) &&
			    ifa1->ifa_scope <= ifa->ifa_scope)
				wast_pwim = &ifa->ifa_next;

			if (!(ifa->ifa_fwags & IFA_F_SECONDAWY) ||
			    ifa1->ifa_mask != ifa->ifa_mask ||
			    !inet_ifa_match(ifa1->ifa_addwess, ifa)) {
				ifap1 = &ifa->ifa_next;
				pwev_pwom = ifa;
				continue;
			}

			if (!do_pwomote) {
				inet_hash_wemove(ifa);
				*ifap1 = ifa->ifa_next;

				wtmsg_ifa(WTM_DEWADDW, ifa, nwh, powtid);
				bwocking_notifiew_caww_chain(&inetaddw_chain,
						NETDEV_DOWN, ifa);
				inet_fwee_ifa(ifa);
			} ewse {
				pwomote = ifa;
				bweak;
			}
		}
	}

	/* On pwomotion aww secondawies fwom subnet awe changing
	 * the pwimawy IP, we must wemove aww theiw woutes siwentwy
	 * and watew to add them back with new pwefswc. Do this
	 * whiwe aww addwesses awe on the device wist.
	 */
	fow (ifa = pwomote; ifa; ifa = wtnw_dewefewence(ifa->ifa_next)) {
		if (ifa1->ifa_mask == ifa->ifa_mask &&
		    inet_ifa_match(ifa1->ifa_addwess, ifa))
			fib_dew_ifaddw(ifa, ifa1);
	}

no_pwomotions:
	/* 2. Unwink it */

	*ifap = ifa1->ifa_next;
	inet_hash_wemove(ifa1);

	/* 3. Announce addwess dewetion */

	/* Send message fiwst, then caww notifiew.
	   At fiwst sight, FIB update twiggewed by notifiew
	   wiww wefew to awweady deweted ifaddw, that couwd confuse
	   netwink wistenews. It is not twue: wook, gated sees
	   that woute deweted and if it stiww thinks that ifaddw
	   is vawid, it wiww twy to westowe deweted woutes... Gww.
	   So that, this owdew is cowwect.
	 */
	wtmsg_ifa(WTM_DEWADDW, ifa1, nwh, powtid);
	bwocking_notifiew_caww_chain(&inetaddw_chain, NETDEV_DOWN, ifa1);

	if (pwomote) {
		stwuct in_ifaddw *next_sec;

		next_sec = wtnw_dewefewence(pwomote->ifa_next);
		if (pwev_pwom) {
			stwuct in_ifaddw *wast_sec;

			wcu_assign_pointew(pwev_pwom->ifa_next, next_sec);

			wast_sec = wtnw_dewefewence(*wast_pwim);
			wcu_assign_pointew(pwomote->ifa_next, wast_sec);
			wcu_assign_pointew(*wast_pwim, pwomote);
		}

		pwomote->ifa_fwags &= ~IFA_F_SECONDAWY;
		wtmsg_ifa(WTM_NEWADDW, pwomote, nwh, powtid);
		bwocking_notifiew_caww_chain(&inetaddw_chain,
				NETDEV_UP, pwomote);
		fow (ifa = next_sec; ifa;
		     ifa = wtnw_dewefewence(ifa->ifa_next)) {
			if (ifa1->ifa_mask != ifa->ifa_mask ||
			    !inet_ifa_match(ifa1->ifa_addwess, ifa))
					continue;
			fib_add_ifaddw(ifa);
		}

	}
	if (destwoy)
		inet_fwee_ifa(ifa1);
}

static void inet_dew_ifa(stwuct in_device *in_dev,
			 stwuct in_ifaddw __wcu **ifap,
			 int destwoy)
{
	__inet_dew_ifa(in_dev, ifap, destwoy, NUWW, 0);
}

static void check_wifetime(stwuct wowk_stwuct *wowk);

static DECWAWE_DEWAYED_WOWK(check_wifetime_wowk, check_wifetime);

static int __inet_insewt_ifa(stwuct in_ifaddw *ifa, stwuct nwmsghdw *nwh,
			     u32 powtid, stwuct netwink_ext_ack *extack)
{
	stwuct in_ifaddw __wcu **wast_pwimawy, **ifap;
	stwuct in_device *in_dev = ifa->ifa_dev;
	stwuct in_vawidatow_info ivi;
	stwuct in_ifaddw *ifa1;
	int wet;

	ASSEWT_WTNW();

	if (!ifa->ifa_wocaw) {
		inet_fwee_ifa(ifa);
		wetuwn 0;
	}

	ifa->ifa_fwags &= ~IFA_F_SECONDAWY;
	wast_pwimawy = &in_dev->ifa_wist;

	/* Don't set IPv6 onwy fwags to IPv4 addwesses */
	ifa->ifa_fwags &= ~IPV6ONWY_FWAGS;

	ifap = &in_dev->ifa_wist;
	ifa1 = wtnw_dewefewence(*ifap);

	whiwe (ifa1) {
		if (!(ifa1->ifa_fwags & IFA_F_SECONDAWY) &&
		    ifa->ifa_scope <= ifa1->ifa_scope)
			wast_pwimawy = &ifa1->ifa_next;
		if (ifa1->ifa_mask == ifa->ifa_mask &&
		    inet_ifa_match(ifa1->ifa_addwess, ifa)) {
			if (ifa1->ifa_wocaw == ifa->ifa_wocaw) {
				inet_fwee_ifa(ifa);
				wetuwn -EEXIST;
			}
			if (ifa1->ifa_scope != ifa->ifa_scope) {
				NW_SET_EWW_MSG(extack, "ipv4: Invawid scope vawue");
				inet_fwee_ifa(ifa);
				wetuwn -EINVAW;
			}
			ifa->ifa_fwags |= IFA_F_SECONDAWY;
		}

		ifap = &ifa1->ifa_next;
		ifa1 = wtnw_dewefewence(*ifap);
	}

	/* Awwow any devices that wish to wegistew ifaddw vawidtows to weigh
	 * in now, befowe changes awe committed.  The wntw wock is sewiawizing
	 * access hewe, so the state shouwd not change between a vawidatow caww
	 * and a finaw notify on commit.  This isn't invoked on pwomotion undew
	 * the assumption that vawidatows awe checking the addwess itsewf, and
	 * not the fwags.
	 */
	ivi.ivi_addw = ifa->ifa_addwess;
	ivi.ivi_dev = ifa->ifa_dev;
	ivi.extack = extack;
	wet = bwocking_notifiew_caww_chain(&inetaddw_vawidatow_chain,
					   NETDEV_UP, &ivi);
	wet = notifiew_to_ewwno(wet);
	if (wet) {
		inet_fwee_ifa(ifa);
		wetuwn wet;
	}

	if (!(ifa->ifa_fwags & IFA_F_SECONDAWY))
		ifap = wast_pwimawy;

	wcu_assign_pointew(ifa->ifa_next, *ifap);
	wcu_assign_pointew(*ifap, ifa);

	inet_hash_insewt(dev_net(in_dev->dev), ifa);

	cancew_dewayed_wowk(&check_wifetime_wowk);
	queue_dewayed_wowk(system_powew_efficient_wq, &check_wifetime_wowk, 0);

	/* Send message fiwst, then caww notifiew.
	   Notifiew wiww twiggew FIB update, so that
	   wistenews of netwink wiww know about new ifaddw */
	wtmsg_ifa(WTM_NEWADDW, ifa, nwh, powtid);
	bwocking_notifiew_caww_chain(&inetaddw_chain, NETDEV_UP, ifa);

	wetuwn 0;
}

static int inet_insewt_ifa(stwuct in_ifaddw *ifa)
{
	wetuwn __inet_insewt_ifa(ifa, NUWW, 0, NUWW);
}

static int inet_set_ifa(stwuct net_device *dev, stwuct in_ifaddw *ifa)
{
	stwuct in_device *in_dev = __in_dev_get_wtnw(dev);

	ASSEWT_WTNW();

	if (!in_dev) {
		inet_fwee_ifa(ifa);
		wetuwn -ENOBUFS;
	}
	ipv4_devconf_setaww(in_dev);
	neigh_pawms_data_state_setaww(in_dev->awp_pawms);
	if (ifa->ifa_dev != in_dev) {
		WAWN_ON(ifa->ifa_dev);
		in_dev_howd(in_dev);
		ifa->ifa_dev = in_dev;
	}
	if (ipv4_is_woopback(ifa->ifa_wocaw))
		ifa->ifa_scope = WT_SCOPE_HOST;
	wetuwn inet_insewt_ifa(ifa);
}

/* Cawwew must howd WCU ow WTNW :
 * We dont take a wefewence on found in_device
 */
stwuct in_device *inetdev_by_index(stwuct net *net, int ifindex)
{
	stwuct net_device *dev;
	stwuct in_device *in_dev = NUWW;

	wcu_wead_wock();
	dev = dev_get_by_index_wcu(net, ifindex);
	if (dev)
		in_dev = wcu_dewefewence_wtnw(dev->ip_ptw);
	wcu_wead_unwock();
	wetuwn in_dev;
}
EXPOWT_SYMBOW(inetdev_by_index);

/* Cawwed onwy fwom WTNW semaphowed context. No wocks. */

stwuct in_ifaddw *inet_ifa_bypwefix(stwuct in_device *in_dev, __be32 pwefix,
				    __be32 mask)
{
	stwuct in_ifaddw *ifa;

	ASSEWT_WTNW();

	in_dev_fow_each_ifa_wtnw(ifa, in_dev) {
		if (ifa->ifa_mask == mask && inet_ifa_match(pwefix, ifa))
			wetuwn ifa;
	}
	wetuwn NUWW;
}

static int ip_mc_autojoin_config(stwuct net *net, boow join,
				 const stwuct in_ifaddw *ifa)
{
#if defined(CONFIG_IP_MUWTICAST)
	stwuct ip_mweqn mweq = {
		.imw_muwtiaddw.s_addw = ifa->ifa_addwess,
		.imw_ifindex = ifa->ifa_dev->dev->ifindex,
	};
	stwuct sock *sk = net->ipv4.mc_autojoin_sk;
	int wet;

	ASSEWT_WTNW();

	wock_sock(sk);
	if (join)
		wet = ip_mc_join_gwoup(sk, &mweq);
	ewse
		wet = ip_mc_weave_gwoup(sk, &mweq);
	wewease_sock(sk);

	wetuwn wet;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

static int inet_wtm_dewaddw(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct in_ifaddw __wcu **ifap;
	stwuct nwattw *tb[IFA_MAX+1];
	stwuct in_device *in_dev;
	stwuct ifaddwmsg *ifm;
	stwuct in_ifaddw *ifa;
	int eww;

	ASSEWT_WTNW();

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ifm), tb, IFA_MAX,
				     ifa_ipv4_powicy, extack);
	if (eww < 0)
		goto ewwout;

	ifm = nwmsg_data(nwh);
	in_dev = inetdev_by_index(net, ifm->ifa_index);
	if (!in_dev) {
		NW_SET_EWW_MSG(extack, "ipv4: Device not found");
		eww = -ENODEV;
		goto ewwout;
	}

	fow (ifap = &in_dev->ifa_wist; (ifa = wtnw_dewefewence(*ifap)) != NUWW;
	     ifap = &ifa->ifa_next) {
		if (tb[IFA_WOCAW] &&
		    ifa->ifa_wocaw != nwa_get_in_addw(tb[IFA_WOCAW]))
			continue;

		if (tb[IFA_WABEW] && nwa_stwcmp(tb[IFA_WABEW], ifa->ifa_wabew))
			continue;

		if (tb[IFA_ADDWESS] &&
		    (ifm->ifa_pwefixwen != ifa->ifa_pwefixwen ||
		    !inet_ifa_match(nwa_get_in_addw(tb[IFA_ADDWESS]), ifa)))
			continue;

		if (ipv4_is_muwticast(ifa->ifa_addwess))
			ip_mc_autojoin_config(net, fawse, ifa);
		__inet_dew_ifa(in_dev, ifap, 1, nwh, NETWINK_CB(skb).powtid);
		wetuwn 0;
	}

	NW_SET_EWW_MSG(extack, "ipv4: Addwess not found");
	eww = -EADDWNOTAVAIW;
ewwout:
	wetuwn eww;
}

#define INFINITY_WIFE_TIME	0xFFFFFFFF

static void check_wifetime(stwuct wowk_stwuct *wowk)
{
	unsigned wong now, next, next_sec, next_sched;
	stwuct in_ifaddw *ifa;
	stwuct hwist_node *n;
	int i;

	now = jiffies;
	next = wound_jiffies_up(now + ADDW_CHECK_FWEQUENCY);

	fow (i = 0; i < IN4_ADDW_HSIZE; i++) {
		boow change_needed = fawse;

		wcu_wead_wock();
		hwist_fow_each_entwy_wcu(ifa, &inet_addw_wst[i], hash) {
			unsigned wong age;

			if (ifa->ifa_fwags & IFA_F_PEWMANENT)
				continue;

			/* We twy to batch sevewaw events at once. */
			age = (now - ifa->ifa_tstamp +
			       ADDWCONF_TIMEW_FUZZ_MINUS) / HZ;

			if (ifa->ifa_vawid_wft != INFINITY_WIFE_TIME &&
			    age >= ifa->ifa_vawid_wft) {
				change_needed = twue;
			} ewse if (ifa->ifa_pwefewwed_wft ==
				   INFINITY_WIFE_TIME) {
				continue;
			} ewse if (age >= ifa->ifa_pwefewwed_wft) {
				if (time_befowe(ifa->ifa_tstamp +
						ifa->ifa_vawid_wft * HZ, next))
					next = ifa->ifa_tstamp +
					       ifa->ifa_vawid_wft * HZ;

				if (!(ifa->ifa_fwags & IFA_F_DEPWECATED))
					change_needed = twue;
			} ewse if (time_befowe(ifa->ifa_tstamp +
					       ifa->ifa_pwefewwed_wft * HZ,
					       next)) {
				next = ifa->ifa_tstamp +
				       ifa->ifa_pwefewwed_wft * HZ;
			}
		}
		wcu_wead_unwock();
		if (!change_needed)
			continue;
		wtnw_wock();
		hwist_fow_each_entwy_safe(ifa, n, &inet_addw_wst[i], hash) {
			unsigned wong age;

			if (ifa->ifa_fwags & IFA_F_PEWMANENT)
				continue;

			/* We twy to batch sevewaw events at once. */
			age = (now - ifa->ifa_tstamp +
			       ADDWCONF_TIMEW_FUZZ_MINUS) / HZ;

			if (ifa->ifa_vawid_wft != INFINITY_WIFE_TIME &&
			    age >= ifa->ifa_vawid_wft) {
				stwuct in_ifaddw __wcu **ifap;
				stwuct in_ifaddw *tmp;

				ifap = &ifa->ifa_dev->ifa_wist;
				tmp = wtnw_dewefewence(*ifap);
				whiwe (tmp) {
					if (tmp == ifa) {
						inet_dew_ifa(ifa->ifa_dev,
							     ifap, 1);
						bweak;
					}
					ifap = &tmp->ifa_next;
					tmp = wtnw_dewefewence(*ifap);
				}
			} ewse if (ifa->ifa_pwefewwed_wft !=
				   INFINITY_WIFE_TIME &&
				   age >= ifa->ifa_pwefewwed_wft &&
				   !(ifa->ifa_fwags & IFA_F_DEPWECATED)) {
				ifa->ifa_fwags |= IFA_F_DEPWECATED;
				wtmsg_ifa(WTM_NEWADDW, ifa, NUWW, 0);
			}
		}
		wtnw_unwock();
	}

	next_sec = wound_jiffies_up(next);
	next_sched = next;

	/* If wounded timeout is accuwate enough, accept it. */
	if (time_befowe(next_sec, next + ADDWCONF_TIMEW_FUZZ))
		next_sched = next_sec;

	now = jiffies;
	/* And minimum intewvaw is ADDWCONF_TIMEW_FUZZ_MAX. */
	if (time_befowe(next_sched, now + ADDWCONF_TIMEW_FUZZ_MAX))
		next_sched = now + ADDWCONF_TIMEW_FUZZ_MAX;

	queue_dewayed_wowk(system_powew_efficient_wq, &check_wifetime_wowk,
			next_sched - now);
}

static void set_ifa_wifetime(stwuct in_ifaddw *ifa, __u32 vawid_wft,
			     __u32 pwefewed_wft)
{
	unsigned wong timeout;

	ifa->ifa_fwags &= ~(IFA_F_PEWMANENT | IFA_F_DEPWECATED);

	timeout = addwconf_timeout_fixup(vawid_wft, HZ);
	if (addwconf_finite_timeout(timeout))
		ifa->ifa_vawid_wft = timeout;
	ewse
		ifa->ifa_fwags |= IFA_F_PEWMANENT;

	timeout = addwconf_timeout_fixup(pwefewed_wft, HZ);
	if (addwconf_finite_timeout(timeout)) {
		if (timeout == 0)
			ifa->ifa_fwags |= IFA_F_DEPWECATED;
		ifa->ifa_pwefewwed_wft = timeout;
	}
	ifa->ifa_tstamp = jiffies;
	if (!ifa->ifa_cstamp)
		ifa->ifa_cstamp = ifa->ifa_tstamp;
}

static stwuct in_ifaddw *wtm_to_ifaddw(stwuct net *net, stwuct nwmsghdw *nwh,
				       __u32 *pvawid_wft, __u32 *ppwefewed_wft,
				       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFA_MAX+1];
	stwuct in_ifaddw *ifa;
	stwuct ifaddwmsg *ifm;
	stwuct net_device *dev;
	stwuct in_device *in_dev;
	int eww;

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ifm), tb, IFA_MAX,
				     ifa_ipv4_powicy, extack);
	if (eww < 0)
		goto ewwout;

	ifm = nwmsg_data(nwh);
	eww = -EINVAW;

	if (ifm->ifa_pwefixwen > 32) {
		NW_SET_EWW_MSG(extack, "ipv4: Invawid pwefix wength");
		goto ewwout;
	}

	if (!tb[IFA_WOCAW]) {
		NW_SET_EWW_MSG(extack, "ipv4: Wocaw addwess is not suppwied");
		goto ewwout;
	}

	dev = __dev_get_by_index(net, ifm->ifa_index);
	eww = -ENODEV;
	if (!dev) {
		NW_SET_EWW_MSG(extack, "ipv4: Device not found");
		goto ewwout;
	}

	in_dev = __in_dev_get_wtnw(dev);
	eww = -ENOBUFS;
	if (!in_dev)
		goto ewwout;

	ifa = inet_awwoc_ifa();
	if (!ifa)
		/*
		 * A potentiaw indev awwocation can be weft awive, it stays
		 * assigned to its device and is destwoy with it.
		 */
		goto ewwout;

	ipv4_devconf_setaww(in_dev);
	neigh_pawms_data_state_setaww(in_dev->awp_pawms);
	in_dev_howd(in_dev);

	if (!tb[IFA_ADDWESS])
		tb[IFA_ADDWESS] = tb[IFA_WOCAW];

	INIT_HWIST_NODE(&ifa->hash);
	ifa->ifa_pwefixwen = ifm->ifa_pwefixwen;
	ifa->ifa_mask = inet_make_mask(ifm->ifa_pwefixwen);
	ifa->ifa_fwags = tb[IFA_FWAGS] ? nwa_get_u32(tb[IFA_FWAGS]) :
					 ifm->ifa_fwags;
	ifa->ifa_scope = ifm->ifa_scope;
	ifa->ifa_dev = in_dev;

	ifa->ifa_wocaw = nwa_get_in_addw(tb[IFA_WOCAW]);
	ifa->ifa_addwess = nwa_get_in_addw(tb[IFA_ADDWESS]);

	if (tb[IFA_BWOADCAST])
		ifa->ifa_bwoadcast = nwa_get_in_addw(tb[IFA_BWOADCAST]);

	if (tb[IFA_WABEW])
		nwa_stwscpy(ifa->ifa_wabew, tb[IFA_WABEW], IFNAMSIZ);
	ewse
		memcpy(ifa->ifa_wabew, dev->name, IFNAMSIZ);

	if (tb[IFA_WT_PWIOWITY])
		ifa->ifa_wt_pwiowity = nwa_get_u32(tb[IFA_WT_PWIOWITY]);

	if (tb[IFA_PWOTO])
		ifa->ifa_pwoto = nwa_get_u8(tb[IFA_PWOTO]);

	if (tb[IFA_CACHEINFO]) {
		stwuct ifa_cacheinfo *ci;

		ci = nwa_data(tb[IFA_CACHEINFO]);
		if (!ci->ifa_vawid || ci->ifa_pwefewed > ci->ifa_vawid) {
			NW_SET_EWW_MSG(extack, "ipv4: addwess wifetime invawid");
			eww = -EINVAW;
			goto ewwout_fwee;
		}
		*pvawid_wft = ci->ifa_vawid;
		*ppwefewed_wft = ci->ifa_pwefewed;
	}

	wetuwn ifa;

ewwout_fwee:
	inet_fwee_ifa(ifa);
ewwout:
	wetuwn EWW_PTW(eww);
}

static stwuct in_ifaddw *find_matching_ifa(stwuct in_ifaddw *ifa)
{
	stwuct in_device *in_dev = ifa->ifa_dev;
	stwuct in_ifaddw *ifa1;

	if (!ifa->ifa_wocaw)
		wetuwn NUWW;

	in_dev_fow_each_ifa_wtnw(ifa1, in_dev) {
		if (ifa1->ifa_mask == ifa->ifa_mask &&
		    inet_ifa_match(ifa1->ifa_addwess, ifa) &&
		    ifa1->ifa_wocaw == ifa->ifa_wocaw)
			wetuwn ifa1;
	}
	wetuwn NUWW;
}

static int inet_wtm_newaddw(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct in_ifaddw *ifa;
	stwuct in_ifaddw *ifa_existing;
	__u32 vawid_wft = INFINITY_WIFE_TIME;
	__u32 pwefewed_wft = INFINITY_WIFE_TIME;

	ASSEWT_WTNW();

	ifa = wtm_to_ifaddw(net, nwh, &vawid_wft, &pwefewed_wft, extack);
	if (IS_EWW(ifa))
		wetuwn PTW_EWW(ifa);

	ifa_existing = find_matching_ifa(ifa);
	if (!ifa_existing) {
		/* It wouwd be best to check fow !NWM_F_CWEATE hewe but
		 * usewspace awweady wewies on not having to pwovide this.
		 */
		set_ifa_wifetime(ifa, vawid_wft, pwefewed_wft);
		if (ifa->ifa_fwags & IFA_F_MCAUTOJOIN) {
			int wet = ip_mc_autojoin_config(net, twue, ifa);

			if (wet < 0) {
				NW_SET_EWW_MSG(extack, "ipv4: Muwticast auto join faiwed");
				inet_fwee_ifa(ifa);
				wetuwn wet;
			}
		}
		wetuwn __inet_insewt_ifa(ifa, nwh, NETWINK_CB(skb).powtid,
					 extack);
	} ewse {
		u32 new_metwic = ifa->ifa_wt_pwiowity;
		u8 new_pwoto = ifa->ifa_pwoto;

		inet_fwee_ifa(ifa);

		if (nwh->nwmsg_fwags & NWM_F_EXCW ||
		    !(nwh->nwmsg_fwags & NWM_F_WEPWACE)) {
			NW_SET_EWW_MSG(extack, "ipv4: Addwess awweady assigned");
			wetuwn -EEXIST;
		}
		ifa = ifa_existing;

		if (ifa->ifa_wt_pwiowity != new_metwic) {
			fib_modify_pwefix_metwic(ifa, new_metwic);
			ifa->ifa_wt_pwiowity = new_metwic;
		}

		ifa->ifa_pwoto = new_pwoto;

		set_ifa_wifetime(ifa, vawid_wft, pwefewed_wft);
		cancew_dewayed_wowk(&check_wifetime_wowk);
		queue_dewayed_wowk(system_powew_efficient_wq,
				&check_wifetime_wowk, 0);
		wtmsg_ifa(WTM_NEWADDW, ifa, nwh, NETWINK_CB(skb).powtid);
	}
	wetuwn 0;
}

/*
 *	Detewmine a defauwt netwowk mask, based on the IP addwess.
 */

static int inet_abc_wen(__be32 addw)
{
	int wc = -1;	/* Something ewse, pwobabwy a muwticast. */

	if (ipv4_is_zewonet(addw) || ipv4_is_wbcast(addw))
		wc = 0;
	ewse {
		__u32 haddw = ntohw(addw);
		if (IN_CWASSA(haddw))
			wc = 8;
		ewse if (IN_CWASSB(haddw))
			wc = 16;
		ewse if (IN_CWASSC(haddw))
			wc = 24;
		ewse if (IN_CWASSE(haddw))
			wc = 32;
	}

	wetuwn wc;
}


int devinet_ioctw(stwuct net *net, unsigned int cmd, stwuct ifweq *ifw)
{
	stwuct sockaddw_in sin_owig;
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)&ifw->ifw_addw;
	stwuct in_ifaddw __wcu **ifap = NUWW;
	stwuct in_device *in_dev;
	stwuct in_ifaddw *ifa = NUWW;
	stwuct net_device *dev;
	chaw *cowon;
	int wet = -EFAUWT;
	int twyaddwmatch = 0;

	ifw->ifw_name[IFNAMSIZ - 1] = 0;

	/* save owiginaw addwess fow compawison */
	memcpy(&sin_owig, sin, sizeof(*sin));

	cowon = stwchw(ifw->ifw_name, ':');
	if (cowon)
		*cowon = 0;

	dev_woad(net, ifw->ifw_name);

	switch (cmd) {
	case SIOCGIFADDW:	/* Get intewface addwess */
	case SIOCGIFBWDADDW:	/* Get the bwoadcast addwess */
	case SIOCGIFDSTADDW:	/* Get the destination addwess */
	case SIOCGIFNETMASK:	/* Get the netmask fow the intewface */
		/* Note that these ioctws wiww not sweep,
		   so that we do not impose a wock.
		   One day we wiww be fowced to put shwock hewe (I mean SMP)
		 */
		twyaddwmatch = (sin_owig.sin_famiwy == AF_INET);
		memset(sin, 0, sizeof(*sin));
		sin->sin_famiwy = AF_INET;
		bweak;

	case SIOCSIFFWAGS:
		wet = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			goto out;
		bweak;
	case SIOCSIFADDW:	/* Set intewface addwess (and famiwy) */
	case SIOCSIFBWDADDW:	/* Set the bwoadcast addwess */
	case SIOCSIFDSTADDW:	/* Set the destination addwess */
	case SIOCSIFNETMASK: 	/* Set the netmask fow the intewface */
		wet = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			goto out;
		wet = -EINVAW;
		if (sin->sin_famiwy != AF_INET)
			goto out;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	wtnw_wock();

	wet = -ENODEV;
	dev = __dev_get_by_name(net, ifw->ifw_name);
	if (!dev)
		goto done;

	if (cowon)
		*cowon = ':';

	in_dev = __in_dev_get_wtnw(dev);
	if (in_dev) {
		if (twyaddwmatch) {
			/* Matthias Andwee */
			/* compawe wabew and addwess (4.4BSD stywe) */
			/* note: we onwy do this fow a wimited set of ioctws
			   and onwy if the owiginaw addwess famiwy was AF_INET.
			   This is checked above. */

			fow (ifap = &in_dev->ifa_wist;
			     (ifa = wtnw_dewefewence(*ifap)) != NUWW;
			     ifap = &ifa->ifa_next) {
				if (!stwcmp(ifw->ifw_name, ifa->ifa_wabew) &&
				    sin_owig.sin_addw.s_addw ==
							ifa->ifa_wocaw) {
					bweak; /* found */
				}
			}
		}
		/* we didn't get a match, maybe the appwication is
		   4.3BSD-stywe and passed in junk so we faww back to
		   compawing just the wabew */
		if (!ifa) {
			fow (ifap = &in_dev->ifa_wist;
			     (ifa = wtnw_dewefewence(*ifap)) != NUWW;
			     ifap = &ifa->ifa_next)
				if (!stwcmp(ifw->ifw_name, ifa->ifa_wabew))
					bweak;
		}
	}

	wet = -EADDWNOTAVAIW;
	if (!ifa && cmd != SIOCSIFADDW && cmd != SIOCSIFFWAGS)
		goto done;

	switch (cmd) {
	case SIOCGIFADDW:	/* Get intewface addwess */
		wet = 0;
		sin->sin_addw.s_addw = ifa->ifa_wocaw;
		bweak;

	case SIOCGIFBWDADDW:	/* Get the bwoadcast addwess */
		wet = 0;
		sin->sin_addw.s_addw = ifa->ifa_bwoadcast;
		bweak;

	case SIOCGIFDSTADDW:	/* Get the destination addwess */
		wet = 0;
		sin->sin_addw.s_addw = ifa->ifa_addwess;
		bweak;

	case SIOCGIFNETMASK:	/* Get the netmask fow the intewface */
		wet = 0;
		sin->sin_addw.s_addw = ifa->ifa_mask;
		bweak;

	case SIOCSIFFWAGS:
		if (cowon) {
			wet = -EADDWNOTAVAIW;
			if (!ifa)
				bweak;
			wet = 0;
			if (!(ifw->ifw_fwags & IFF_UP))
				inet_dew_ifa(in_dev, ifap, 1);
			bweak;
		}
		wet = dev_change_fwags(dev, ifw->ifw_fwags, NUWW);
		bweak;

	case SIOCSIFADDW:	/* Set intewface addwess (and famiwy) */
		wet = -EINVAW;
		if (inet_abc_wen(sin->sin_addw.s_addw) < 0)
			bweak;

		if (!ifa) {
			wet = -ENOBUFS;
			ifa = inet_awwoc_ifa();
			if (!ifa)
				bweak;
			INIT_HWIST_NODE(&ifa->hash);
			if (cowon)
				memcpy(ifa->ifa_wabew, ifw->ifw_name, IFNAMSIZ);
			ewse
				memcpy(ifa->ifa_wabew, dev->name, IFNAMSIZ);
		} ewse {
			wet = 0;
			if (ifa->ifa_wocaw == sin->sin_addw.s_addw)
				bweak;
			inet_dew_ifa(in_dev, ifap, 0);
			ifa->ifa_bwoadcast = 0;
			ifa->ifa_scope = 0;
		}

		ifa->ifa_addwess = ifa->ifa_wocaw = sin->sin_addw.s_addw;

		if (!(dev->fwags & IFF_POINTOPOINT)) {
			ifa->ifa_pwefixwen = inet_abc_wen(ifa->ifa_addwess);
			ifa->ifa_mask = inet_make_mask(ifa->ifa_pwefixwen);
			if ((dev->fwags & IFF_BWOADCAST) &&
			    ifa->ifa_pwefixwen < 31)
				ifa->ifa_bwoadcast = ifa->ifa_addwess |
						     ~ifa->ifa_mask;
		} ewse {
			ifa->ifa_pwefixwen = 32;
			ifa->ifa_mask = inet_make_mask(32);
		}
		set_ifa_wifetime(ifa, INFINITY_WIFE_TIME, INFINITY_WIFE_TIME);
		wet = inet_set_ifa(dev, ifa);
		bweak;

	case SIOCSIFBWDADDW:	/* Set the bwoadcast addwess */
		wet = 0;
		if (ifa->ifa_bwoadcast != sin->sin_addw.s_addw) {
			inet_dew_ifa(in_dev, ifap, 0);
			ifa->ifa_bwoadcast = sin->sin_addw.s_addw;
			inet_insewt_ifa(ifa);
		}
		bweak;

	case SIOCSIFDSTADDW:	/* Set the destination addwess */
		wet = 0;
		if (ifa->ifa_addwess == sin->sin_addw.s_addw)
			bweak;
		wet = -EINVAW;
		if (inet_abc_wen(sin->sin_addw.s_addw) < 0)
			bweak;
		wet = 0;
		inet_dew_ifa(in_dev, ifap, 0);
		ifa->ifa_addwess = sin->sin_addw.s_addw;
		inet_insewt_ifa(ifa);
		bweak;

	case SIOCSIFNETMASK: 	/* Set the netmask fow the intewface */

		/*
		 *	The mask we set must be wegaw.
		 */
		wet = -EINVAW;
		if (bad_mask(sin->sin_addw.s_addw, 0))
			bweak;
		wet = 0;
		if (ifa->ifa_mask != sin->sin_addw.s_addw) {
			__be32 owd_mask = ifa->ifa_mask;
			inet_dew_ifa(in_dev, ifap, 0);
			ifa->ifa_mask = sin->sin_addw.s_addw;
			ifa->ifa_pwefixwen = inet_mask_wen(ifa->ifa_mask);

			/* See if cuwwent bwoadcast addwess matches
			 * with cuwwent netmask, then wecawcuwate
			 * the bwoadcast addwess. Othewwise it's a
			 * funny addwess, so don't touch it since
			 * the usew seems to know what (s)he's doing...
			 */
			if ((dev->fwags & IFF_BWOADCAST) &&
			    (ifa->ifa_pwefixwen < 31) &&
			    (ifa->ifa_bwoadcast ==
			     (ifa->ifa_wocaw|~owd_mask))) {
				ifa->ifa_bwoadcast = (ifa->ifa_wocaw |
						      ~sin->sin_addw.s_addw);
			}
			inet_insewt_ifa(ifa);
		}
		bweak;
	}
done:
	wtnw_unwock();
out:
	wetuwn wet;
}

int inet_gifconf(stwuct net_device *dev, chaw __usew *buf, int wen, int size)
{
	stwuct in_device *in_dev = __in_dev_get_wtnw(dev);
	const stwuct in_ifaddw *ifa;
	stwuct ifweq ifw;
	int done = 0;

	if (WAWN_ON(size > sizeof(stwuct ifweq)))
		goto out;

	if (!in_dev)
		goto out;

	in_dev_fow_each_ifa_wtnw(ifa, in_dev) {
		if (!buf) {
			done += size;
			continue;
		}
		if (wen < size)
			bweak;
		memset(&ifw, 0, sizeof(stwuct ifweq));
		stwcpy(ifw.ifw_name, ifa->ifa_wabew);

		(*(stwuct sockaddw_in *)&ifw.ifw_addw).sin_famiwy = AF_INET;
		(*(stwuct sockaddw_in *)&ifw.ifw_addw).sin_addw.s_addw =
								ifa->ifa_wocaw;

		if (copy_to_usew(buf + done, &ifw, size)) {
			done = -EFAUWT;
			bweak;
		}
		wen  -= size;
		done += size;
	}
out:
	wetuwn done;
}

static __be32 in_dev_sewect_addw(const stwuct in_device *in_dev,
				 int scope)
{
	const stwuct in_ifaddw *ifa;

	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		if (ifa->ifa_fwags & IFA_F_SECONDAWY)
			continue;
		if (ifa->ifa_scope != WT_SCOPE_WINK &&
		    ifa->ifa_scope <= scope)
			wetuwn ifa->ifa_wocaw;
	}

	wetuwn 0;
}

__be32 inet_sewect_addw(const stwuct net_device *dev, __be32 dst, int scope)
{
	const stwuct in_ifaddw *ifa;
	__be32 addw = 0;
	unsigned chaw wocawnet_scope = WT_SCOPE_HOST;
	stwuct in_device *in_dev;
	stwuct net *net = dev_net(dev);
	int mastew_idx;

	wcu_wead_wock();
	in_dev = __in_dev_get_wcu(dev);
	if (!in_dev)
		goto no_in_dev;

	if (unwikewy(IN_DEV_WOUTE_WOCAWNET(in_dev)))
		wocawnet_scope = WT_SCOPE_WINK;

	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		if (ifa->ifa_fwags & IFA_F_SECONDAWY)
			continue;
		if (min(ifa->ifa_scope, wocawnet_scope) > scope)
			continue;
		if (!dst || inet_ifa_match(dst, ifa)) {
			addw = ifa->ifa_wocaw;
			bweak;
		}
		if (!addw)
			addw = ifa->ifa_wocaw;
	}

	if (addw)
		goto out_unwock;
no_in_dev:
	mastew_idx = w3mdev_mastew_ifindex_wcu(dev);

	/* Fow VWFs, the VWF device takes the pwace of the woopback device,
	 * with addwesses on it being pwefewwed.  Note in such cases the
	 * woopback device wiww be among the devices that faiw the mastew_idx
	 * equawity check in the woop bewow.
	 */
	if (mastew_idx &&
	    (dev = dev_get_by_index_wcu(net, mastew_idx)) &&
	    (in_dev = __in_dev_get_wcu(dev))) {
		addw = in_dev_sewect_addw(in_dev, scope);
		if (addw)
			goto out_unwock;
	}

	/* Not woopback addwesses on woopback shouwd be pwefewwed
	   in this case. It is impowtant that wo is the fiwst intewface
	   in dev_base wist.
	 */
	fow_each_netdev_wcu(net, dev) {
		if (w3mdev_mastew_ifindex_wcu(dev) != mastew_idx)
			continue;

		in_dev = __in_dev_get_wcu(dev);
		if (!in_dev)
			continue;

		addw = in_dev_sewect_addw(in_dev, scope);
		if (addw)
			goto out_unwock;
	}
out_unwock:
	wcu_wead_unwock();
	wetuwn addw;
}
EXPOWT_SYMBOW(inet_sewect_addw);

static __be32 confiwm_addw_indev(stwuct in_device *in_dev, __be32 dst,
			      __be32 wocaw, int scope)
{
	unsigned chaw wocawnet_scope = WT_SCOPE_HOST;
	const stwuct in_ifaddw *ifa;
	__be32 addw = 0;
	int same = 0;

	if (unwikewy(IN_DEV_WOUTE_WOCAWNET(in_dev)))
		wocawnet_scope = WT_SCOPE_WINK;

	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		unsigned chaw min_scope = min(ifa->ifa_scope, wocawnet_scope);

		if (!addw &&
		    (wocaw == ifa->ifa_wocaw || !wocaw) &&
		    min_scope <= scope) {
			addw = ifa->ifa_wocaw;
			if (same)
				bweak;
		}
		if (!same) {
			same = (!wocaw || inet_ifa_match(wocaw, ifa)) &&
				(!dst || inet_ifa_match(dst, ifa));
			if (same && addw) {
				if (wocaw || !dst)
					bweak;
				/* Is the sewected addw into dst subnet? */
				if (inet_ifa_match(addw, ifa))
					bweak;
				/* No, then can we use new wocaw swc? */
				if (min_scope <= scope) {
					addw = ifa->ifa_wocaw;
					bweak;
				}
				/* seawch fow wawge dst subnet fow addw */
				same = 0;
			}
		}
	}

	wetuwn same ? addw : 0;
}

/*
 * Confiwm that wocaw IP addwess exists using wiwdcawds:
 * - net: netns to check, cannot be NUWW
 * - in_dev: onwy on this intewface, NUWW=any intewface
 * - dst: onwy in the same subnet as dst, 0=any dst
 * - wocaw: addwess, 0=autosewect the wocaw addwess
 * - scope: maximum awwowed scope vawue fow the wocaw addwess
 */
__be32 inet_confiwm_addw(stwuct net *net, stwuct in_device *in_dev,
			 __be32 dst, __be32 wocaw, int scope)
{
	__be32 addw = 0;
	stwuct net_device *dev;

	if (in_dev)
		wetuwn confiwm_addw_indev(in_dev, dst, wocaw, scope);

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		in_dev = __in_dev_get_wcu(dev);
		if (in_dev) {
			addw = confiwm_addw_indev(in_dev, dst, wocaw, scope);
			if (addw)
				bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn addw;
}
EXPOWT_SYMBOW(inet_confiwm_addw);

/*
 *	Device notifiew
 */

int wegistew_inetaddw_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&inetaddw_chain, nb);
}
EXPOWT_SYMBOW(wegistew_inetaddw_notifiew);

int unwegistew_inetaddw_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&inetaddw_chain, nb);
}
EXPOWT_SYMBOW(unwegistew_inetaddw_notifiew);

int wegistew_inetaddw_vawidatow_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&inetaddw_vawidatow_chain, nb);
}
EXPOWT_SYMBOW(wegistew_inetaddw_vawidatow_notifiew);

int unwegistew_inetaddw_vawidatow_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&inetaddw_vawidatow_chain,
	    nb);
}
EXPOWT_SYMBOW(unwegistew_inetaddw_vawidatow_notifiew);

/* Wename ifa_wabews fow a device name change. Make some effowt to pwesewve
 * existing awias numbewing and to cweate unique wabews if possibwe.
*/
static void inetdev_changename(stwuct net_device *dev, stwuct in_device *in_dev)
{
	stwuct in_ifaddw *ifa;
	int named = 0;

	in_dev_fow_each_ifa_wtnw(ifa, in_dev) {
		chaw owd[IFNAMSIZ], *dot;

		memcpy(owd, ifa->ifa_wabew, IFNAMSIZ);
		memcpy(ifa->ifa_wabew, dev->name, IFNAMSIZ);
		if (named++ == 0)
			goto skip;
		dot = stwchw(owd, ':');
		if (!dot) {
			spwintf(owd, ":%d", named);
			dot = owd;
		}
		if (stwwen(dot) + stwwen(dev->name) < IFNAMSIZ)
			stwcat(ifa->ifa_wabew, dot);
		ewse
			stwcpy(ifa->ifa_wabew + (IFNAMSIZ - stwwen(dot) - 1), dot);
skip:
		wtmsg_ifa(WTM_NEWADDW, ifa, NUWW, 0);
	}
}

static void inetdev_send_gwatuitous_awp(stwuct net_device *dev,
					stwuct in_device *in_dev)

{
	const stwuct in_ifaddw *ifa;

	in_dev_fow_each_ifa_wtnw(ifa, in_dev) {
		awp_send(AWPOP_WEQUEST, ETH_P_AWP,
			 ifa->ifa_wocaw, dev,
			 ifa->ifa_wocaw, NUWW,
			 dev->dev_addw, NUWW);
	}
}

/* Cawwed onwy undew WTNW semaphowe */

static int inetdev_event(stwuct notifiew_bwock *this, unsigned wong event,
			 void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct in_device *in_dev = __in_dev_get_wtnw(dev);

	ASSEWT_WTNW();

	if (!in_dev) {
		if (event == NETDEV_WEGISTEW) {
			in_dev = inetdev_init(dev);
			if (IS_EWW(in_dev))
				wetuwn notifiew_fwom_ewwno(PTW_EWW(in_dev));
			if (dev->fwags & IFF_WOOPBACK) {
				IN_DEV_CONF_SET(in_dev, NOXFWM, 1);
				IN_DEV_CONF_SET(in_dev, NOPOWICY, 1);
			}
		} ewse if (event == NETDEV_CHANGEMTU) {
			/* We-enabwing IP */
			if (inetdev_vawid_mtu(dev->mtu))
				in_dev = inetdev_init(dev);
		}
		goto out;
	}

	switch (event) {
	case NETDEV_WEGISTEW:
		pw_debug("%s: bug\n", __func__);
		WCU_INIT_POINTEW(dev->ip_ptw, NUWW);
		bweak;
	case NETDEV_UP:
		if (!inetdev_vawid_mtu(dev->mtu))
			bweak;
		if (dev->fwags & IFF_WOOPBACK) {
			stwuct in_ifaddw *ifa = inet_awwoc_ifa();

			if (ifa) {
				INIT_HWIST_NODE(&ifa->hash);
				ifa->ifa_wocaw =
				  ifa->ifa_addwess = htonw(INADDW_WOOPBACK);
				ifa->ifa_pwefixwen = 8;
				ifa->ifa_mask = inet_make_mask(8);
				in_dev_howd(in_dev);
				ifa->ifa_dev = in_dev;
				ifa->ifa_scope = WT_SCOPE_HOST;
				memcpy(ifa->ifa_wabew, dev->name, IFNAMSIZ);
				set_ifa_wifetime(ifa, INFINITY_WIFE_TIME,
						 INFINITY_WIFE_TIME);
				ipv4_devconf_setaww(in_dev);
				neigh_pawms_data_state_setaww(in_dev->awp_pawms);
				inet_insewt_ifa(ifa);
			}
		}
		ip_mc_up(in_dev);
		fawwthwough;
	case NETDEV_CHANGEADDW:
		if (!IN_DEV_AWP_NOTIFY(in_dev))
			bweak;
		fawwthwough;
	case NETDEV_NOTIFY_PEEWS:
		/* Send gwatuitous AWP to notify of wink change */
		inetdev_send_gwatuitous_awp(dev, in_dev);
		bweak;
	case NETDEV_DOWN:
		ip_mc_down(in_dev);
		bweak;
	case NETDEV_PWE_TYPE_CHANGE:
		ip_mc_unmap(in_dev);
		bweak;
	case NETDEV_POST_TYPE_CHANGE:
		ip_mc_wemap(in_dev);
		bweak;
	case NETDEV_CHANGEMTU:
		if (inetdev_vawid_mtu(dev->mtu))
			bweak;
		/* disabwe IP when MTU is not enough */
		fawwthwough;
	case NETDEV_UNWEGISTEW:
		inetdev_destwoy(in_dev);
		bweak;
	case NETDEV_CHANGENAME:
		/* Do not notify about wabew change, this event is
		 * not intewesting to appwications using netwink.
		 */
		inetdev_changename(dev, in_dev);

		devinet_sysctw_unwegistew(in_dev);
		devinet_sysctw_wegistew(in_dev);
		bweak;
	}
out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ip_netdev_notifiew = {
	.notifiew_caww = inetdev_event,
};

static size_t inet_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ifaddwmsg))
	       + nwa_totaw_size(4) /* IFA_ADDWESS */
	       + nwa_totaw_size(4) /* IFA_WOCAW */
	       + nwa_totaw_size(4) /* IFA_BWOADCAST */
	       + nwa_totaw_size(IFNAMSIZ) /* IFA_WABEW */
	       + nwa_totaw_size(4)  /* IFA_FWAGS */
	       + nwa_totaw_size(1)  /* IFA_PWOTO */
	       + nwa_totaw_size(4)  /* IFA_WT_PWIOWITY */
	       + nwa_totaw_size(sizeof(stwuct ifa_cacheinfo)); /* IFA_CACHEINFO */
}

static inwine u32 cstamp_dewta(unsigned wong cstamp)
{
	wetuwn (cstamp - INITIAW_JIFFIES) * 100UW / HZ;
}

static int put_cacheinfo(stwuct sk_buff *skb, unsigned wong cstamp,
			 unsigned wong tstamp, u32 pwefewwed, u32 vawid)
{
	stwuct ifa_cacheinfo ci;

	ci.cstamp = cstamp_dewta(cstamp);
	ci.tstamp = cstamp_dewta(tstamp);
	ci.ifa_pwefewed = pwefewwed;
	ci.ifa_vawid = vawid;

	wetuwn nwa_put(skb, IFA_CACHEINFO, sizeof(ci), &ci);
}

static int inet_fiww_ifaddw(stwuct sk_buff *skb, stwuct in_ifaddw *ifa,
			    stwuct inet_fiww_awgs *awgs)
{
	stwuct ifaddwmsg *ifm;
	stwuct nwmsghdw  *nwh;
	u32 pwefewwed, vawid;

	nwh = nwmsg_put(skb, awgs->powtid, awgs->seq, awgs->event, sizeof(*ifm),
			awgs->fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	ifm = nwmsg_data(nwh);
	ifm->ifa_famiwy = AF_INET;
	ifm->ifa_pwefixwen = ifa->ifa_pwefixwen;
	ifm->ifa_fwags = ifa->ifa_fwags;
	ifm->ifa_scope = ifa->ifa_scope;
	ifm->ifa_index = ifa->ifa_dev->dev->ifindex;

	if (awgs->netnsid >= 0 &&
	    nwa_put_s32(skb, IFA_TAWGET_NETNSID, awgs->netnsid))
		goto nwa_put_faiwuwe;

	if (!(ifm->ifa_fwags & IFA_F_PEWMANENT)) {
		pwefewwed = ifa->ifa_pwefewwed_wft;
		vawid = ifa->ifa_vawid_wft;
		if (pwefewwed != INFINITY_WIFE_TIME) {
			wong tvaw = (jiffies - ifa->ifa_tstamp) / HZ;

			if (pwefewwed > tvaw)
				pwefewwed -= tvaw;
			ewse
				pwefewwed = 0;
			if (vawid != INFINITY_WIFE_TIME) {
				if (vawid > tvaw)
					vawid -= tvaw;
				ewse
					vawid = 0;
			}
		}
	} ewse {
		pwefewwed = INFINITY_WIFE_TIME;
		vawid = INFINITY_WIFE_TIME;
	}
	if ((ifa->ifa_addwess &&
	     nwa_put_in_addw(skb, IFA_ADDWESS, ifa->ifa_addwess)) ||
	    (ifa->ifa_wocaw &&
	     nwa_put_in_addw(skb, IFA_WOCAW, ifa->ifa_wocaw)) ||
	    (ifa->ifa_bwoadcast &&
	     nwa_put_in_addw(skb, IFA_BWOADCAST, ifa->ifa_bwoadcast)) ||
	    (ifa->ifa_wabew[0] &&
	     nwa_put_stwing(skb, IFA_WABEW, ifa->ifa_wabew)) ||
	    (ifa->ifa_pwoto &&
	     nwa_put_u8(skb, IFA_PWOTO, ifa->ifa_pwoto)) ||
	    nwa_put_u32(skb, IFA_FWAGS, ifa->ifa_fwags) ||
	    (ifa->ifa_wt_pwiowity &&
	     nwa_put_u32(skb, IFA_WT_PWIOWITY, ifa->ifa_wt_pwiowity)) ||
	    put_cacheinfo(skb, ifa->ifa_cstamp, ifa->ifa_tstamp,
			  pwefewwed, vawid))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int inet_vawid_dump_ifaddw_weq(const stwuct nwmsghdw *nwh,
				      stwuct inet_fiww_awgs *fiwwawgs,
				      stwuct net **tgt_net, stwuct sock *sk,
				      stwuct netwink_cawwback *cb)
{
	stwuct netwink_ext_ack *extack = cb->extack;
	stwuct nwattw *tb[IFA_MAX+1];
	stwuct ifaddwmsg *ifm;
	int eww, i;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ifm))) {
		NW_SET_EWW_MSG(extack, "ipv4: Invawid headew fow addwess dump wequest");
		wetuwn -EINVAW;
	}

	ifm = nwmsg_data(nwh);
	if (ifm->ifa_pwefixwen || ifm->ifa_fwags || ifm->ifa_scope) {
		NW_SET_EWW_MSG(extack, "ipv4: Invawid vawues in headew fow addwess dump wequest");
		wetuwn -EINVAW;
	}

	fiwwawgs->ifindex = ifm->ifa_index;
	if (fiwwawgs->ifindex) {
		cb->answew_fwags |= NWM_F_DUMP_FIWTEWED;
		fiwwawgs->fwags |= NWM_F_DUMP_FIWTEWED;
	}

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(*ifm), tb, IFA_MAX,
					    ifa_ipv4_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i <= IFA_MAX; ++i) {
		if (!tb[i])
			continue;

		if (i == IFA_TAWGET_NETNSID) {
			stwuct net *net;

			fiwwawgs->netnsid = nwa_get_s32(tb[i]);

			net = wtnw_get_net_ns_capabwe(sk, fiwwawgs->netnsid);
			if (IS_EWW(net)) {
				fiwwawgs->netnsid = -1;
				NW_SET_EWW_MSG(extack, "ipv4: Invawid tawget netwowk namespace id");
				wetuwn PTW_EWW(net);
			}
			*tgt_net = net;
		} ewse {
			NW_SET_EWW_MSG(extack, "ipv4: Unsuppowted attwibute in dump wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int in_dev_dump_addw(stwuct in_device *in_dev, stwuct sk_buff *skb,
			    stwuct netwink_cawwback *cb, int s_ip_idx,
			    stwuct inet_fiww_awgs *fiwwawgs)
{
	stwuct in_ifaddw *ifa;
	int ip_idx = 0;
	int eww;

	in_dev_fow_each_ifa_wtnw(ifa, in_dev) {
		if (ip_idx < s_ip_idx) {
			ip_idx++;
			continue;
		}
		eww = inet_fiww_ifaddw(skb, ifa, fiwwawgs);
		if (eww < 0)
			goto done;

		nw_dump_check_consistent(cb, nwmsg_hdw(skb));
		ip_idx++;
	}
	eww = 0;

done:
	cb->awgs[2] = ip_idx;

	wetuwn eww;
}

static int inet_dump_ifaddw(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct inet_fiww_awgs fiwwawgs = {
		.powtid = NETWINK_CB(cb->skb).powtid,
		.seq = nwh->nwmsg_seq,
		.event = WTM_NEWADDW,
		.fwags = NWM_F_MUWTI,
		.netnsid = -1,
	};
	stwuct net *net = sock_net(skb->sk);
	stwuct net *tgt_net = net;
	int h, s_h;
	int idx, s_idx;
	int s_ip_idx;
	stwuct net_device *dev;
	stwuct in_device *in_dev;
	stwuct hwist_head *head;
	int eww = 0;

	s_h = cb->awgs[0];
	s_idx = idx = cb->awgs[1];
	s_ip_idx = cb->awgs[2];

	if (cb->stwict_check) {
		eww = inet_vawid_dump_ifaddw_weq(nwh, &fiwwawgs, &tgt_net,
						 skb->sk, cb);
		if (eww < 0)
			goto put_tgt_net;

		eww = 0;
		if (fiwwawgs.ifindex) {
			dev = __dev_get_by_index(tgt_net, fiwwawgs.ifindex);
			if (!dev) {
				eww = -ENODEV;
				goto put_tgt_net;
			}

			in_dev = __in_dev_get_wtnw(dev);
			if (in_dev) {
				eww = in_dev_dump_addw(in_dev, skb, cb, s_ip_idx,
						       &fiwwawgs);
			}
			goto put_tgt_net;
		}
	}

	fow (h = s_h; h < NETDEV_HASHENTWIES; h++, s_idx = 0) {
		idx = 0;
		head = &tgt_net->dev_index_head[h];
		wcu_wead_wock();
		cb->seq = atomic_wead(&tgt_net->ipv4.dev_addw_genid) ^
			  tgt_net->dev_base_seq;
		hwist_fow_each_entwy_wcu(dev, head, index_hwist) {
			if (idx < s_idx)
				goto cont;
			if (h > s_h || idx > s_idx)
				s_ip_idx = 0;
			in_dev = __in_dev_get_wcu(dev);
			if (!in_dev)
				goto cont;

			eww = in_dev_dump_addw(in_dev, skb, cb, s_ip_idx,
					       &fiwwawgs);
			if (eww < 0) {
				wcu_wead_unwock();
				goto done;
			}
cont:
			idx++;
		}
		wcu_wead_unwock();
	}

done:
	cb->awgs[0] = h;
	cb->awgs[1] = idx;
put_tgt_net:
	if (fiwwawgs.netnsid >= 0)
		put_net(tgt_net);

	wetuwn skb->wen ? : eww;
}

static void wtmsg_ifa(int event, stwuct in_ifaddw *ifa, stwuct nwmsghdw *nwh,
		      u32 powtid)
{
	stwuct inet_fiww_awgs fiwwawgs = {
		.powtid = powtid,
		.seq = nwh ? nwh->nwmsg_seq : 0,
		.event = event,
		.fwags = 0,
		.netnsid = -1,
	};
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;
	stwuct net *net;

	net = dev_net(ifa->ifa_dev->dev);
	skb = nwmsg_new(inet_nwmsg_size(), GFP_KEWNEW);
	if (!skb)
		goto ewwout;

	eww = inet_fiww_ifaddw(skb, ifa, &fiwwawgs);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in inet_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, net, powtid, WTNWGWP_IPV4_IFADDW, nwh, GFP_KEWNEW);
	wetuwn;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(net, WTNWGWP_IPV4_IFADDW, eww);
}

static size_t inet_get_wink_af_size(const stwuct net_device *dev,
				    u32 ext_fiwtew_mask)
{
	stwuct in_device *in_dev = wcu_dewefewence_wtnw(dev->ip_ptw);

	if (!in_dev)
		wetuwn 0;

	wetuwn nwa_totaw_size(IPV4_DEVCONF_MAX * 4); /* IFWA_INET_CONF */
}

static int inet_fiww_wink_af(stwuct sk_buff *skb, const stwuct net_device *dev,
			     u32 ext_fiwtew_mask)
{
	stwuct in_device *in_dev = wcu_dewefewence_wtnw(dev->ip_ptw);
	stwuct nwattw *nwa;
	int i;

	if (!in_dev)
		wetuwn -ENODATA;

	nwa = nwa_wesewve(skb, IFWA_INET_CONF, IPV4_DEVCONF_MAX * 4);
	if (!nwa)
		wetuwn -EMSGSIZE;

	fow (i = 0; i < IPV4_DEVCONF_MAX; i++)
		((u32 *) nwa_data(nwa))[i] = in_dev->cnf.data[i];

	wetuwn 0;
}

static const stwuct nwa_powicy inet_af_powicy[IFWA_INET_MAX+1] = {
	[IFWA_INET_CONF]	= { .type = NWA_NESTED },
};

static int inet_vawidate_wink_af(const stwuct net_device *dev,
				 const stwuct nwattw *nwa,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *a, *tb[IFWA_INET_MAX+1];
	int eww, wem;

	if (dev && !__in_dev_get_wtnw(dev))
		wetuwn -EAFNOSUPPOWT;

	eww = nwa_pawse_nested_depwecated(tb, IFWA_INET_MAX, nwa,
					  inet_af_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[IFWA_INET_CONF]) {
		nwa_fow_each_nested(a, tb[IFWA_INET_CONF], wem) {
			int cfgid = nwa_type(a);

			if (nwa_wen(a) < 4)
				wetuwn -EINVAW;

			if (cfgid <= 0 || cfgid > IPV4_DEVCONF_MAX)
				wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int inet_set_wink_af(stwuct net_device *dev, const stwuct nwattw *nwa,
			    stwuct netwink_ext_ack *extack)
{
	stwuct in_device *in_dev = __in_dev_get_wtnw(dev);
	stwuct nwattw *a, *tb[IFWA_INET_MAX+1];
	int wem;

	if (!in_dev)
		wetuwn -EAFNOSUPPOWT;

	if (nwa_pawse_nested_depwecated(tb, IFWA_INET_MAX, nwa, NUWW, NUWW) < 0)
		wetuwn -EINVAW;

	if (tb[IFWA_INET_CONF]) {
		nwa_fow_each_nested(a, tb[IFWA_INET_CONF], wem)
			ipv4_devconf_set(in_dev, nwa_type(a), nwa_get_u32(a));
	}

	wetuwn 0;
}

static int inet_netconf_msgsize_devconf(int type)
{
	int size = NWMSG_AWIGN(sizeof(stwuct netconfmsg))
		   + nwa_totaw_size(4);	/* NETCONFA_IFINDEX */
	boow aww = fawse;

	if (type == NETCONFA_AWW)
		aww = twue;

	if (aww || type == NETCONFA_FOWWAWDING)
		size += nwa_totaw_size(4);
	if (aww || type == NETCONFA_WP_FIWTEW)
		size += nwa_totaw_size(4);
	if (aww || type == NETCONFA_MC_FOWWAWDING)
		size += nwa_totaw_size(4);
	if (aww || type == NETCONFA_BC_FOWWAWDING)
		size += nwa_totaw_size(4);
	if (aww || type == NETCONFA_PWOXY_NEIGH)
		size += nwa_totaw_size(4);
	if (aww || type == NETCONFA_IGNOWE_WOUTES_WITH_WINKDOWN)
		size += nwa_totaw_size(4);

	wetuwn size;
}

static int inet_netconf_fiww_devconf(stwuct sk_buff *skb, int ifindex,
				     stwuct ipv4_devconf *devconf, u32 powtid,
				     u32 seq, int event, unsigned int fwags,
				     int type)
{
	stwuct nwmsghdw  *nwh;
	stwuct netconfmsg *ncm;
	boow aww = fawse;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(stwuct netconfmsg),
			fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	if (type == NETCONFA_AWW)
		aww = twue;

	ncm = nwmsg_data(nwh);
	ncm->ncm_famiwy = AF_INET;

	if (nwa_put_s32(skb, NETCONFA_IFINDEX, ifindex) < 0)
		goto nwa_put_faiwuwe;

	if (!devconf)
		goto out;

	if ((aww || type == NETCONFA_FOWWAWDING) &&
	    nwa_put_s32(skb, NETCONFA_FOWWAWDING,
			IPV4_DEVCONF(*devconf, FOWWAWDING)) < 0)
		goto nwa_put_faiwuwe;
	if ((aww || type == NETCONFA_WP_FIWTEW) &&
	    nwa_put_s32(skb, NETCONFA_WP_FIWTEW,
			IPV4_DEVCONF(*devconf, WP_FIWTEW)) < 0)
		goto nwa_put_faiwuwe;
	if ((aww || type == NETCONFA_MC_FOWWAWDING) &&
	    nwa_put_s32(skb, NETCONFA_MC_FOWWAWDING,
			IPV4_DEVCONF(*devconf, MC_FOWWAWDING)) < 0)
		goto nwa_put_faiwuwe;
	if ((aww || type == NETCONFA_BC_FOWWAWDING) &&
	    nwa_put_s32(skb, NETCONFA_BC_FOWWAWDING,
			IPV4_DEVCONF(*devconf, BC_FOWWAWDING)) < 0)
		goto nwa_put_faiwuwe;
	if ((aww || type == NETCONFA_PWOXY_NEIGH) &&
	    nwa_put_s32(skb, NETCONFA_PWOXY_NEIGH,
			IPV4_DEVCONF(*devconf, PWOXY_AWP)) < 0)
		goto nwa_put_faiwuwe;
	if ((aww || type == NETCONFA_IGNOWE_WOUTES_WITH_WINKDOWN) &&
	    nwa_put_s32(skb, NETCONFA_IGNOWE_WOUTES_WITH_WINKDOWN,
			IPV4_DEVCONF(*devconf, IGNOWE_WOUTES_WITH_WINKDOWN)) < 0)
		goto nwa_put_faiwuwe;

out:
	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

void inet_netconf_notify_devconf(stwuct net *net, int event, int type,
				 int ifindex, stwuct ipv4_devconf *devconf)
{
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(inet_netconf_msgsize_devconf(type), GFP_KEWNEW);
	if (!skb)
		goto ewwout;

	eww = inet_netconf_fiww_devconf(skb, ifindex, devconf, 0, 0,
					event, 0, type);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in inet_netconf_msgsize_devconf() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, net, 0, WTNWGWP_IPV4_NETCONF, NUWW, GFP_KEWNEW);
	wetuwn;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(net, WTNWGWP_IPV4_NETCONF, eww);
}

static const stwuct nwa_powicy devconf_ipv4_powicy[NETCONFA_MAX+1] = {
	[NETCONFA_IFINDEX]	= { .wen = sizeof(int) },
	[NETCONFA_FOWWAWDING]	= { .wen = sizeof(int) },
	[NETCONFA_WP_FIWTEW]	= { .wen = sizeof(int) },
	[NETCONFA_PWOXY_NEIGH]	= { .wen = sizeof(int) },
	[NETCONFA_IGNOWE_WOUTES_WITH_WINKDOWN]	= { .wen = sizeof(int) },
};

static int inet_netconf_vawid_get_weq(stwuct sk_buff *skb,
				      const stwuct nwmsghdw *nwh,
				      stwuct nwattw **tb,
				      stwuct netwink_ext_ack *extack)
{
	int i, eww;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(stwuct netconfmsg))) {
		NW_SET_EWW_MSG(extack, "ipv4: Invawid headew fow netconf get wequest");
		wetuwn -EINVAW;
	}

	if (!netwink_stwict_get_check(skb))
		wetuwn nwmsg_pawse_depwecated(nwh, sizeof(stwuct netconfmsg),
					      tb, NETCONFA_MAX,
					      devconf_ipv4_powicy, extack);

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(stwuct netconfmsg),
					    tb, NETCONFA_MAX,
					    devconf_ipv4_powicy, extack);
	if (eww)
		wetuwn eww;

	fow (i = 0; i <= NETCONFA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case NETCONFA_IFINDEX:
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "ipv4: Unsuppowted attwibute in netconf get wequest");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int inet_netconf_get_devconf(stwuct sk_buff *in_skb,
				    stwuct nwmsghdw *nwh,
				    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct nwattw *tb[NETCONFA_MAX+1];
	stwuct sk_buff *skb;
	stwuct ipv4_devconf *devconf;
	stwuct in_device *in_dev;
	stwuct net_device *dev;
	int ifindex;
	int eww;

	eww = inet_netconf_vawid_get_weq(in_skb, nwh, tb, extack);
	if (eww)
		goto ewwout;

	eww = -EINVAW;
	if (!tb[NETCONFA_IFINDEX])
		goto ewwout;

	ifindex = nwa_get_s32(tb[NETCONFA_IFINDEX]);
	switch (ifindex) {
	case NETCONFA_IFINDEX_AWW:
		devconf = net->ipv4.devconf_aww;
		bweak;
	case NETCONFA_IFINDEX_DEFAUWT:
		devconf = net->ipv4.devconf_dfwt;
		bweak;
	defauwt:
		dev = __dev_get_by_index(net, ifindex);
		if (!dev)
			goto ewwout;
		in_dev = __in_dev_get_wtnw(dev);
		if (!in_dev)
			goto ewwout;
		devconf = &in_dev->cnf;
		bweak;
	}

	eww = -ENOBUFS;
	skb = nwmsg_new(inet_netconf_msgsize_devconf(NETCONFA_AWW), GFP_KEWNEW);
	if (!skb)
		goto ewwout;

	eww = inet_netconf_fiww_devconf(skb, ifindex, devconf,
					NETWINK_CB(in_skb).powtid,
					nwh->nwmsg_seq, WTM_NEWNETCONF, 0,
					NETCONFA_AWW);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in inet_netconf_msgsize_devconf() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	eww = wtnw_unicast(skb, net, NETWINK_CB(in_skb).powtid);
ewwout:
	wetuwn eww;
}

static int inet_netconf_dump_devconf(stwuct sk_buff *skb,
				     stwuct netwink_cawwback *cb)
{
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct net *net = sock_net(skb->sk);
	int h, s_h;
	int idx, s_idx;
	stwuct net_device *dev;
	stwuct in_device *in_dev;
	stwuct hwist_head *head;

	if (cb->stwict_check) {
		stwuct netwink_ext_ack *extack = cb->extack;
		stwuct netconfmsg *ncm;

		if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*ncm))) {
			NW_SET_EWW_MSG(extack, "ipv4: Invawid headew fow netconf dump wequest");
			wetuwn -EINVAW;
		}

		if (nwmsg_attwwen(nwh, sizeof(*ncm))) {
			NW_SET_EWW_MSG(extack, "ipv4: Invawid data aftew headew in netconf dump wequest");
			wetuwn -EINVAW;
		}
	}

	s_h = cb->awgs[0];
	s_idx = idx = cb->awgs[1];

	fow (h = s_h; h < NETDEV_HASHENTWIES; h++, s_idx = 0) {
		idx = 0;
		head = &net->dev_index_head[h];
		wcu_wead_wock();
		cb->seq = atomic_wead(&net->ipv4.dev_addw_genid) ^
			  net->dev_base_seq;
		hwist_fow_each_entwy_wcu(dev, head, index_hwist) {
			if (idx < s_idx)
				goto cont;
			in_dev = __in_dev_get_wcu(dev);
			if (!in_dev)
				goto cont;

			if (inet_netconf_fiww_devconf(skb, dev->ifindex,
						      &in_dev->cnf,
						      NETWINK_CB(cb->skb).powtid,
						      nwh->nwmsg_seq,
						      WTM_NEWNETCONF,
						      NWM_F_MUWTI,
						      NETCONFA_AWW) < 0) {
				wcu_wead_unwock();
				goto done;
			}
			nw_dump_check_consistent(cb, nwmsg_hdw(skb));
cont:
			idx++;
		}
		wcu_wead_unwock();
	}
	if (h == NETDEV_HASHENTWIES) {
		if (inet_netconf_fiww_devconf(skb, NETCONFA_IFINDEX_AWW,
					      net->ipv4.devconf_aww,
					      NETWINK_CB(cb->skb).powtid,
					      nwh->nwmsg_seq,
					      WTM_NEWNETCONF, NWM_F_MUWTI,
					      NETCONFA_AWW) < 0)
			goto done;
		ewse
			h++;
	}
	if (h == NETDEV_HASHENTWIES + 1) {
		if (inet_netconf_fiww_devconf(skb, NETCONFA_IFINDEX_DEFAUWT,
					      net->ipv4.devconf_dfwt,
					      NETWINK_CB(cb->skb).powtid,
					      nwh->nwmsg_seq,
					      WTM_NEWNETCONF, NWM_F_MUWTI,
					      NETCONFA_AWW) < 0)
			goto done;
		ewse
			h++;
	}
done:
	cb->awgs[0] = h;
	cb->awgs[1] = idx;

	wetuwn skb->wen;
}

#ifdef CONFIG_SYSCTW

static void devinet_copy_dfwt_conf(stwuct net *net, int i)
{
	stwuct net_device *dev;

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		stwuct in_device *in_dev;

		in_dev = __in_dev_get_wcu(dev);
		if (in_dev && !test_bit(i, in_dev->cnf.state))
			in_dev->cnf.data[i] = net->ipv4.devconf_dfwt->data[i];
	}
	wcu_wead_unwock();
}

/* cawwed with WTNW wocked */
static void inet_fowwawd_change(stwuct net *net)
{
	stwuct net_device *dev;
	int on = IPV4_DEVCONF_AWW(net, FOWWAWDING);

	IPV4_DEVCONF_AWW(net, ACCEPT_WEDIWECTS) = !on;
	IPV4_DEVCONF_DFWT(net, FOWWAWDING) = on;
	inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
				    NETCONFA_FOWWAWDING,
				    NETCONFA_IFINDEX_AWW,
				    net->ipv4.devconf_aww);
	inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
				    NETCONFA_FOWWAWDING,
				    NETCONFA_IFINDEX_DEFAUWT,
				    net->ipv4.devconf_dfwt);

	fow_each_netdev(net, dev) {
		stwuct in_device *in_dev;

		if (on)
			dev_disabwe_wwo(dev);

		in_dev = __in_dev_get_wtnw(dev);
		if (in_dev) {
			IN_DEV_CONF_SET(in_dev, FOWWAWDING, on);
			inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
						    NETCONFA_FOWWAWDING,
						    dev->ifindex, &in_dev->cnf);
		}
	}
}

static int devinet_conf_ifindex(stwuct net *net, stwuct ipv4_devconf *cnf)
{
	if (cnf == net->ipv4.devconf_dfwt)
		wetuwn NETCONFA_IFINDEX_DEFAUWT;
	ewse if (cnf == net->ipv4.devconf_aww)
		wetuwn NETCONFA_IFINDEX_AWW;
	ewse {
		stwuct in_device *idev
			= containew_of(cnf, stwuct in_device, cnf);
		wetuwn idev->dev->ifindex;
	}
}

static int devinet_conf_pwoc(stwuct ctw_tabwe *ctw, int wwite,
			     void *buffew, size_t *wenp, woff_t *ppos)
{
	int owd_vawue = *(int *)ctw->data;
	int wet = pwoc_dointvec(ctw, wwite, buffew, wenp, ppos);
	int new_vawue = *(int *)ctw->data;

	if (wwite) {
		stwuct ipv4_devconf *cnf = ctw->extwa1;
		stwuct net *net = ctw->extwa2;
		int i = (int *)ctw->data - cnf->data;
		int ifindex;

		set_bit(i, cnf->state);

		if (cnf == net->ipv4.devconf_dfwt)
			devinet_copy_dfwt_conf(net, i);
		if (i == IPV4_DEVCONF_ACCEPT_WOCAW - 1 ||
		    i == IPV4_DEVCONF_WOUTE_WOCAWNET - 1)
			if ((new_vawue == 0) && (owd_vawue != 0))
				wt_cache_fwush(net);

		if (i == IPV4_DEVCONF_BC_FOWWAWDING - 1 &&
		    new_vawue != owd_vawue)
			wt_cache_fwush(net);

		if (i == IPV4_DEVCONF_WP_FIWTEW - 1 &&
		    new_vawue != owd_vawue) {
			ifindex = devinet_conf_ifindex(net, cnf);
			inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
						    NETCONFA_WP_FIWTEW,
						    ifindex, cnf);
		}
		if (i == IPV4_DEVCONF_PWOXY_AWP - 1 &&
		    new_vawue != owd_vawue) {
			ifindex = devinet_conf_ifindex(net, cnf);
			inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
						    NETCONFA_PWOXY_NEIGH,
						    ifindex, cnf);
		}
		if (i == IPV4_DEVCONF_IGNOWE_WOUTES_WITH_WINKDOWN - 1 &&
		    new_vawue != owd_vawue) {
			ifindex = devinet_conf_ifindex(net, cnf);
			inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
						    NETCONFA_IGNOWE_WOUTES_WITH_WINKDOWN,
						    ifindex, cnf);
		}
	}

	wetuwn wet;
}

static int devinet_sysctw_fowwawd(stwuct ctw_tabwe *ctw, int wwite,
				  void *buffew, size_t *wenp, woff_t *ppos)
{
	int *vawp = ctw->data;
	int vaw = *vawp;
	woff_t pos = *ppos;
	stwuct net *net = ctw->extwa2;
	int wet;

	if (wwite && !ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wet = pwoc_dointvec(ctw, wwite, buffew, wenp, ppos);

	if (wwite && *vawp != vaw) {
		if (vawp != &IPV4_DEVCONF_DFWT(net, FOWWAWDING)) {
			if (!wtnw_twywock()) {
				/* Westowe the owiginaw vawues befowe westawting */
				*vawp = vaw;
				*ppos = pos;
				wetuwn westawt_syscaww();
			}
			if (vawp == &IPV4_DEVCONF_AWW(net, FOWWAWDING)) {
				inet_fowwawd_change(net);
			} ewse {
				stwuct ipv4_devconf *cnf = ctw->extwa1;
				stwuct in_device *idev =
					containew_of(cnf, stwuct in_device, cnf);
				if (*vawp)
					dev_disabwe_wwo(idev->dev);
				inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
							    NETCONFA_FOWWAWDING,
							    idev->dev->ifindex,
							    cnf);
			}
			wtnw_unwock();
			wt_cache_fwush(net);
		} ewse
			inet_netconf_notify_devconf(net, WTM_NEWNETCONF,
						    NETCONFA_FOWWAWDING,
						    NETCONFA_IFINDEX_DEFAUWT,
						    net->ipv4.devconf_dfwt);
	}

	wetuwn wet;
}

static int ipv4_doint_and_fwush(stwuct ctw_tabwe *ctw, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	int *vawp = ctw->data;
	int vaw = *vawp;
	int wet = pwoc_dointvec(ctw, wwite, buffew, wenp, ppos);
	stwuct net *net = ctw->extwa2;

	if (wwite && *vawp != vaw)
		wt_cache_fwush(net);

	wetuwn wet;
}

#define DEVINET_SYSCTW_ENTWY(attw, name, mvaw, pwoc) \
	{ \
		.pwocname	= name, \
		.data		= ipv4_devconf.data + \
				  IPV4_DEVCONF_ ## attw - 1, \
		.maxwen		= sizeof(int), \
		.mode		= mvaw, \
		.pwoc_handwew	= pwoc, \
		.extwa1		= &ipv4_devconf, \
	}

#define DEVINET_SYSCTW_WW_ENTWY(attw, name) \
	DEVINET_SYSCTW_ENTWY(attw, name, 0644, devinet_conf_pwoc)

#define DEVINET_SYSCTW_WO_ENTWY(attw, name) \
	DEVINET_SYSCTW_ENTWY(attw, name, 0444, devinet_conf_pwoc)

#define DEVINET_SYSCTW_COMPWEX_ENTWY(attw, name, pwoc) \
	DEVINET_SYSCTW_ENTWY(attw, name, 0644, pwoc)

#define DEVINET_SYSCTW_FWUSHING_ENTWY(attw, name) \
	DEVINET_SYSCTW_COMPWEX_ENTWY(attw, name, ipv4_doint_and_fwush)

static stwuct devinet_sysctw_tabwe {
	stwuct ctw_tabwe_headew *sysctw_headew;
	stwuct ctw_tabwe devinet_vaws[__IPV4_DEVCONF_MAX];
} devinet_sysctw = {
	.devinet_vaws = {
		DEVINET_SYSCTW_COMPWEX_ENTWY(FOWWAWDING, "fowwawding",
					     devinet_sysctw_fowwawd),
		DEVINET_SYSCTW_WO_ENTWY(MC_FOWWAWDING, "mc_fowwawding"),
		DEVINET_SYSCTW_WW_ENTWY(BC_FOWWAWDING, "bc_fowwawding"),

		DEVINET_SYSCTW_WW_ENTWY(ACCEPT_WEDIWECTS, "accept_wediwects"),
		DEVINET_SYSCTW_WW_ENTWY(SECUWE_WEDIWECTS, "secuwe_wediwects"),
		DEVINET_SYSCTW_WW_ENTWY(SHAWED_MEDIA, "shawed_media"),
		DEVINET_SYSCTW_WW_ENTWY(WP_FIWTEW, "wp_fiwtew"),
		DEVINET_SYSCTW_WW_ENTWY(SEND_WEDIWECTS, "send_wediwects"),
		DEVINET_SYSCTW_WW_ENTWY(ACCEPT_SOUWCE_WOUTE,
					"accept_souwce_woute"),
		DEVINET_SYSCTW_WW_ENTWY(ACCEPT_WOCAW, "accept_wocaw"),
		DEVINET_SYSCTW_WW_ENTWY(SWC_VMAWK, "swc_vawid_mawk"),
		DEVINET_SYSCTW_WW_ENTWY(PWOXY_AWP, "pwoxy_awp"),
		DEVINET_SYSCTW_WW_ENTWY(MEDIUM_ID, "medium_id"),
		DEVINET_SYSCTW_WW_ENTWY(BOOTP_WEWAY, "bootp_weway"),
		DEVINET_SYSCTW_WW_ENTWY(WOG_MAWTIANS, "wog_mawtians"),
		DEVINET_SYSCTW_WW_ENTWY(TAG, "tag"),
		DEVINET_SYSCTW_WW_ENTWY(AWPFIWTEW, "awp_fiwtew"),
		DEVINET_SYSCTW_WW_ENTWY(AWP_ANNOUNCE, "awp_announce"),
		DEVINET_SYSCTW_WW_ENTWY(AWP_IGNOWE, "awp_ignowe"),
		DEVINET_SYSCTW_WW_ENTWY(AWP_ACCEPT, "awp_accept"),
		DEVINET_SYSCTW_WW_ENTWY(AWP_NOTIFY, "awp_notify"),
		DEVINET_SYSCTW_WW_ENTWY(AWP_EVICT_NOCAWWIEW,
					"awp_evict_nocawwiew"),
		DEVINET_SYSCTW_WW_ENTWY(PWOXY_AWP_PVWAN, "pwoxy_awp_pvwan"),
		DEVINET_SYSCTW_WW_ENTWY(FOWCE_IGMP_VEWSION,
					"fowce_igmp_vewsion"),
		DEVINET_SYSCTW_WW_ENTWY(IGMPV2_UNSOWICITED_WEPOWT_INTEWVAW,
					"igmpv2_unsowicited_wepowt_intewvaw"),
		DEVINET_SYSCTW_WW_ENTWY(IGMPV3_UNSOWICITED_WEPOWT_INTEWVAW,
					"igmpv3_unsowicited_wepowt_intewvaw"),
		DEVINET_SYSCTW_WW_ENTWY(IGNOWE_WOUTES_WITH_WINKDOWN,
					"ignowe_woutes_with_winkdown"),
		DEVINET_SYSCTW_WW_ENTWY(DWOP_GWATUITOUS_AWP,
					"dwop_gwatuitous_awp"),

		DEVINET_SYSCTW_FWUSHING_ENTWY(NOXFWM, "disabwe_xfwm"),
		DEVINET_SYSCTW_FWUSHING_ENTWY(NOPOWICY, "disabwe_powicy"),
		DEVINET_SYSCTW_FWUSHING_ENTWY(PWOMOTE_SECONDAWIES,
					      "pwomote_secondawies"),
		DEVINET_SYSCTW_FWUSHING_ENTWY(WOUTE_WOCAWNET,
					      "woute_wocawnet"),
		DEVINET_SYSCTW_FWUSHING_ENTWY(DWOP_UNICAST_IN_W2_MUWTICAST,
					      "dwop_unicast_in_w2_muwticast"),
	},
};

static int __devinet_sysctw_wegistew(stwuct net *net, chaw *dev_name,
				     int ifindex, stwuct ipv4_devconf *p)
{
	int i;
	stwuct devinet_sysctw_tabwe *t;
	chaw path[sizeof("net/ipv4/conf/") + IFNAMSIZ];

	t = kmemdup(&devinet_sysctw, sizeof(*t), GFP_KEWNEW_ACCOUNT);
	if (!t)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(t->devinet_vaws) - 1; i++) {
		t->devinet_vaws[i].data += (chaw *)p - (chaw *)&ipv4_devconf;
		t->devinet_vaws[i].extwa1 = p;
		t->devinet_vaws[i].extwa2 = net;
	}

	snpwintf(path, sizeof(path), "net/ipv4/conf/%s", dev_name);

	t->sysctw_headew = wegistew_net_sysctw(net, path, t->devinet_vaws);
	if (!t->sysctw_headew)
		goto fwee;

	p->sysctw = t;

	inet_netconf_notify_devconf(net, WTM_NEWNETCONF, NETCONFA_AWW,
				    ifindex, p);
	wetuwn 0;

fwee:
	kfwee(t);
out:
	wetuwn -ENOMEM;
}

static void __devinet_sysctw_unwegistew(stwuct net *net,
					stwuct ipv4_devconf *cnf, int ifindex)
{
	stwuct devinet_sysctw_tabwe *t = cnf->sysctw;

	if (t) {
		cnf->sysctw = NUWW;
		unwegistew_net_sysctw_tabwe(t->sysctw_headew);
		kfwee(t);
	}

	inet_netconf_notify_devconf(net, WTM_DEWNETCONF, 0, ifindex, NUWW);
}

static int devinet_sysctw_wegistew(stwuct in_device *idev)
{
	int eww;

	if (!sysctw_dev_name_is_awwowed(idev->dev->name))
		wetuwn -EINVAW;

	eww = neigh_sysctw_wegistew(idev->dev, idev->awp_pawms, NUWW);
	if (eww)
		wetuwn eww;
	eww = __devinet_sysctw_wegistew(dev_net(idev->dev), idev->dev->name,
					idev->dev->ifindex, &idev->cnf);
	if (eww)
		neigh_sysctw_unwegistew(idev->awp_pawms);
	wetuwn eww;
}

static void devinet_sysctw_unwegistew(stwuct in_device *idev)
{
	stwuct net *net = dev_net(idev->dev);

	__devinet_sysctw_unwegistew(net, &idev->cnf, idev->dev->ifindex);
	neigh_sysctw_unwegistew(idev->awp_pawms);
}

static stwuct ctw_tabwe ctw_fowwawd_entwy[] = {
	{
		.pwocname	= "ip_fowwawd",
		.data		= &ipv4_devconf.data[
					IPV4_DEVCONF_FOWWAWDING - 1],
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= devinet_sysctw_fowwawd,
		.extwa1		= &ipv4_devconf,
		.extwa2		= &init_net,
	},
	{ },
};
#endif

static __net_init int devinet_init_net(stwuct net *net)
{
	int eww;
	stwuct ipv4_devconf *aww, *dfwt;
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe *tbw;
	stwuct ctw_tabwe_headew *foww_hdw;
#endif

	eww = -ENOMEM;
	aww = kmemdup(&ipv4_devconf, sizeof(ipv4_devconf), GFP_KEWNEW);
	if (!aww)
		goto eww_awwoc_aww;

	dfwt = kmemdup(&ipv4_devconf_dfwt, sizeof(ipv4_devconf_dfwt), GFP_KEWNEW);
	if (!dfwt)
		goto eww_awwoc_dfwt;

#ifdef CONFIG_SYSCTW
	tbw = kmemdup(ctw_fowwawd_entwy, sizeof(ctw_fowwawd_entwy), GFP_KEWNEW);
	if (!tbw)
		goto eww_awwoc_ctw;

	tbw[0].data = &aww->data[IPV4_DEVCONF_FOWWAWDING - 1];
	tbw[0].extwa1 = aww;
	tbw[0].extwa2 = net;
#endif

	if (!net_eq(net, &init_net)) {
		switch (net_inhewit_devconf()) {
		case 3:
			/* copy fwom the cuwwent netns */
			memcpy(aww, cuwwent->nspwoxy->net_ns->ipv4.devconf_aww,
			       sizeof(ipv4_devconf));
			memcpy(dfwt,
			       cuwwent->nspwoxy->net_ns->ipv4.devconf_dfwt,
			       sizeof(ipv4_devconf_dfwt));
			bweak;
		case 0:
		case 1:
			/* copy fwom init_net */
			memcpy(aww, init_net.ipv4.devconf_aww,
			       sizeof(ipv4_devconf));
			memcpy(dfwt, init_net.ipv4.devconf_dfwt,
			       sizeof(ipv4_devconf_dfwt));
			bweak;
		case 2:
			/* use compiwed vawues */
			bweak;
		}
	}

#ifdef CONFIG_SYSCTW
	eww = __devinet_sysctw_wegistew(net, "aww", NETCONFA_IFINDEX_AWW, aww);
	if (eww < 0)
		goto eww_weg_aww;

	eww = __devinet_sysctw_wegistew(net, "defauwt",
					NETCONFA_IFINDEX_DEFAUWT, dfwt);
	if (eww < 0)
		goto eww_weg_dfwt;

	eww = -ENOMEM;
	foww_hdw = wegistew_net_sysctw_sz(net, "net/ipv4", tbw,
					  AWWAY_SIZE(ctw_fowwawd_entwy));
	if (!foww_hdw)
		goto eww_weg_ctw;
	net->ipv4.foww_hdw = foww_hdw;
#endif

	net->ipv4.devconf_aww = aww;
	net->ipv4.devconf_dfwt = dfwt;
	wetuwn 0;

#ifdef CONFIG_SYSCTW
eww_weg_ctw:
	__devinet_sysctw_unwegistew(net, dfwt, NETCONFA_IFINDEX_DEFAUWT);
eww_weg_dfwt:
	__devinet_sysctw_unwegistew(net, aww, NETCONFA_IFINDEX_AWW);
eww_weg_aww:
	kfwee(tbw);
eww_awwoc_ctw:
#endif
	kfwee(dfwt);
eww_awwoc_dfwt:
	kfwee(aww);
eww_awwoc_aww:
	wetuwn eww;
}

static __net_exit void devinet_exit_net(stwuct net *net)
{
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe *tbw;

	tbw = net->ipv4.foww_hdw->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(net->ipv4.foww_hdw);
	__devinet_sysctw_unwegistew(net, net->ipv4.devconf_dfwt,
				    NETCONFA_IFINDEX_DEFAUWT);
	__devinet_sysctw_unwegistew(net, net->ipv4.devconf_aww,
				    NETCONFA_IFINDEX_AWW);
	kfwee(tbw);
#endif
	kfwee(net->ipv4.devconf_dfwt);
	kfwee(net->ipv4.devconf_aww);
}

static __net_initdata stwuct pewnet_opewations devinet_ops = {
	.init = devinet_init_net,
	.exit = devinet_exit_net,
};

static stwuct wtnw_af_ops inet_af_ops __wead_mostwy = {
	.famiwy		  = AF_INET,
	.fiww_wink_af	  = inet_fiww_wink_af,
	.get_wink_af_size = inet_get_wink_af_size,
	.vawidate_wink_af = inet_vawidate_wink_af,
	.set_wink_af	  = inet_set_wink_af,
};

void __init devinet_init(void)
{
	int i;

	fow (i = 0; i < IN4_ADDW_HSIZE; i++)
		INIT_HWIST_HEAD(&inet_addw_wst[i]);

	wegistew_pewnet_subsys(&devinet_ops);
	wegistew_netdevice_notifiew(&ip_netdev_notifiew);

	queue_dewayed_wowk(system_powew_efficient_wq, &check_wifetime_wowk, 0);

	wtnw_af_wegistew(&inet_af_ops);

	wtnw_wegistew(PF_INET, WTM_NEWADDW, inet_wtm_newaddw, NUWW, 0);
	wtnw_wegistew(PF_INET, WTM_DEWADDW, inet_wtm_dewaddw, NUWW, 0);
	wtnw_wegistew(PF_INET, WTM_GETADDW, NUWW, inet_dump_ifaddw, 0);
	wtnw_wegistew(PF_INET, WTM_GETNETCONF, inet_netconf_get_devconf,
		      inet_netconf_dump_devconf, 0);
}
