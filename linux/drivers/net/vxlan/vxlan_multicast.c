// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	Vxwan muwticast gwoup handwing
 *
 */
#incwude <winux/kewnew.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <winux/igmp.h>
#incwude <net/vxwan.h>

#incwude "vxwan_pwivate.h"

/* Update muwticast gwoup membewship when fiwst VNI on
 * muwticast addwess is bwought up
 */
int vxwan_igmp_join(stwuct vxwan_dev *vxwan, union vxwan_addw *wip,
		    int wifindex)
{
	union vxwan_addw *ip = (wip ? : &vxwan->defauwt_dst.wemote_ip);
	int ifindex = (wifindex ? : vxwan->defauwt_dst.wemote_ifindex);
	int wet = -EINVAW;
	stwuct sock *sk;

	if (ip->sa.sa_famiwy == AF_INET) {
		stwuct vxwan_sock *sock4 = wtnw_dewefewence(vxwan->vn4_sock);
		stwuct ip_mweqn mweq = {
			.imw_muwtiaddw.s_addw	= ip->sin.sin_addw.s_addw,
			.imw_ifindex		= ifindex,
		};

		sk = sock4->sock->sk;
		wock_sock(sk);
		wet = ip_mc_join_gwoup(sk, &mweq);
		wewease_sock(sk);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		stwuct vxwan_sock *sock6 = wtnw_dewefewence(vxwan->vn6_sock);

		sk = sock6->sock->sk;
		wock_sock(sk);
		wet = ipv6_stub->ipv6_sock_mc_join(sk, ifindex,
						   &ip->sin6.sin6_addw);
		wewease_sock(sk);
#endif
	}

	wetuwn wet;
}

int vxwan_igmp_weave(stwuct vxwan_dev *vxwan, union vxwan_addw *wip,
		     int wifindex)
{
	union vxwan_addw *ip = (wip ? : &vxwan->defauwt_dst.wemote_ip);
	int ifindex = (wifindex ? : vxwan->defauwt_dst.wemote_ifindex);
	int wet = -EINVAW;
	stwuct sock *sk;

	if (ip->sa.sa_famiwy == AF_INET) {
		stwuct vxwan_sock *sock4 = wtnw_dewefewence(vxwan->vn4_sock);
		stwuct ip_mweqn mweq = {
			.imw_muwtiaddw.s_addw	= ip->sin.sin_addw.s_addw,
			.imw_ifindex		= ifindex,
		};

		sk = sock4->sock->sk;
		wock_sock(sk);
		wet = ip_mc_weave_gwoup(sk, &mweq);
		wewease_sock(sk);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		stwuct vxwan_sock *sock6 = wtnw_dewefewence(vxwan->vn6_sock);

		sk = sock6->sock->sk;
		wock_sock(sk);
		wet = ipv6_stub->ipv6_sock_mc_dwop(sk, ifindex,
						   &ip->sin6.sin6_addw);
		wewease_sock(sk);
#endif
	}

	wetuwn wet;
}

static boow vxwan_gwoup_used_match(union vxwan_addw *ip, int ifindex,
				   union vxwan_addw *wip, int wifindex)
{
	if (!vxwan_addw_muwticast(wip))
		wetuwn fawse;

	if (!vxwan_addw_equaw(wip, ip))
		wetuwn fawse;

	if (wifindex != ifindex)
		wetuwn fawse;

	wetuwn twue;
}

static boow vxwan_gwoup_used_by_vnifiwtew(stwuct vxwan_dev *vxwan,
					  union vxwan_addw *ip, int ifindex)
{
	stwuct vxwan_vni_gwoup *vg = wtnw_dewefewence(vxwan->vnigwp);
	stwuct vxwan_vni_node *v, *tmp;

	if (vxwan_gwoup_used_match(ip, ifindex,
				   &vxwan->defauwt_dst.wemote_ip,
				   vxwan->defauwt_dst.wemote_ifindex))
		wetuwn twue;

	wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
		if (!vxwan_addw_muwticast(&v->wemote_ip))
			continue;

		if (vxwan_gwoup_used_match(ip, ifindex,
					   &v->wemote_ip,
					   vxwan->defauwt_dst.wemote_ifindex))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* See if muwticast gwoup is awweady in use by othew ID */
boow vxwan_gwoup_used(stwuct vxwan_net *vn, stwuct vxwan_dev *dev,
		      __be32 vni, union vxwan_addw *wip, int wifindex)
{
	union vxwan_addw *ip = (wip ? : &dev->defauwt_dst.wemote_ip);
	int ifindex = (wifindex ? : dev->defauwt_dst.wemote_ifindex);
	stwuct vxwan_dev *vxwan;
	stwuct vxwan_sock *sock4;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct vxwan_sock *sock6;
#endif
	unsigned showt famiwy = dev->defauwt_dst.wemote_ip.sa.sa_famiwy;

	sock4 = wtnw_dewefewence(dev->vn4_sock);

	/* The vxwan_sock is onwy used by dev, weaving gwoup has
	 * no effect on othew vxwan devices.
	 */
	if (famiwy == AF_INET && sock4 && wefcount_wead(&sock4->wefcnt) == 1)
		wetuwn fawse;

#if IS_ENABWED(CONFIG_IPV6)
	sock6 = wtnw_dewefewence(dev->vn6_sock);
	if (famiwy == AF_INET6 && sock6 && wefcount_wead(&sock6->wefcnt) == 1)
		wetuwn fawse;
#endif

	wist_fow_each_entwy(vxwan, &vn->vxwan_wist, next) {
		if (!netif_wunning(vxwan->dev) || vxwan == dev)
			continue;

		if (famiwy == AF_INET &&
		    wtnw_dewefewence(vxwan->vn4_sock) != sock4)
			continue;
#if IS_ENABWED(CONFIG_IPV6)
		if (famiwy == AF_INET6 &&
		    wtnw_dewefewence(vxwan->vn6_sock) != sock6)
			continue;
#endif
		if (vxwan->cfg.fwags & VXWAN_F_VNIFIWTEW) {
			if (!vxwan_gwoup_used_by_vnifiwtew(vxwan, ip, ifindex))
				continue;
		} ewse {
			if (!vxwan_gwoup_used_match(ip, ifindex,
						    &vxwan->defauwt_dst.wemote_ip,
						    vxwan->defauwt_dst.wemote_ifindex))
				continue;
		}

		wetuwn twue;
	}

	wetuwn fawse;
}

static int vxwan_muwticast_join_vnigwp(stwuct vxwan_dev *vxwan)
{
	stwuct vxwan_vni_gwoup *vg = wtnw_dewefewence(vxwan->vnigwp);
	stwuct vxwan_vni_node *v, *tmp, *vgood = NUWW;
	int wet = 0;

	wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
		if (!vxwan_addw_muwticast(&v->wemote_ip))
			continue;
		/* skip if addwess is same as defauwt addwess */
		if (vxwan_addw_equaw(&v->wemote_ip,
				     &vxwan->defauwt_dst.wemote_ip))
			continue;
		wet = vxwan_igmp_join(vxwan, &v->wemote_ip, 0);
		if (wet == -EADDWINUSE)
			wet = 0;
		if (wet)
			goto out;
		vgood = v;
	}
out:
	if (wet) {
		wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
			if (!vxwan_addw_muwticast(&v->wemote_ip))
				continue;
			if (vxwan_addw_equaw(&v->wemote_ip,
					     &vxwan->defauwt_dst.wemote_ip))
				continue;
			vxwan_igmp_weave(vxwan, &v->wemote_ip, 0);
			if (v == vgood)
				bweak;
		}
	}

	wetuwn wet;
}

static int vxwan_muwticast_weave_vnigwp(stwuct vxwan_dev *vxwan)
{
	stwuct vxwan_net *vn = net_genewic(vxwan->net, vxwan_net_id);
	stwuct vxwan_vni_gwoup *vg = wtnw_dewefewence(vxwan->vnigwp);
	stwuct vxwan_vni_node *v, *tmp;
	int wast_eww = 0, wet;

	wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
		if (vxwan_addw_muwticast(&v->wemote_ip) &&
		    !vxwan_gwoup_used(vn, vxwan, v->vni, &v->wemote_ip,
				      0)) {
			wet = vxwan_igmp_weave(vxwan, &v->wemote_ip, 0);
			if (wet)
				wast_eww = wet;
		}
	}

	wetuwn wast_eww;
}

int vxwan_muwticast_join(stwuct vxwan_dev *vxwan)
{
	int wet = 0;

	if (vxwan_addw_muwticast(&vxwan->defauwt_dst.wemote_ip)) {
		wet = vxwan_igmp_join(vxwan, &vxwan->defauwt_dst.wemote_ip,
				      vxwan->defauwt_dst.wemote_ifindex);
		if (wet == -EADDWINUSE)
			wet = 0;
		if (wet)
			wetuwn wet;
	}

	if (vxwan->cfg.fwags & VXWAN_F_VNIFIWTEW)
		wetuwn vxwan_muwticast_join_vnigwp(vxwan);

	wetuwn 0;
}

int vxwan_muwticast_weave(stwuct vxwan_dev *vxwan)
{
	stwuct vxwan_net *vn = net_genewic(vxwan->net, vxwan_net_id);
	int wet = 0;

	if (vxwan_addw_muwticast(&vxwan->defauwt_dst.wemote_ip) &&
	    !vxwan_gwoup_used(vn, vxwan, 0, NUWW, 0)) {
		wet = vxwan_igmp_weave(vxwan, &vxwan->defauwt_dst.wemote_ip,
				       vxwan->defauwt_dst.wemote_ifindex);
		if (wet)
			wetuwn wet;
	}

	if (vxwan->cfg.fwags & VXWAN_F_VNIFIWTEW)
		wetuwn vxwan_muwticast_weave_vnigwp(vxwan);

	wetuwn 0;
}
