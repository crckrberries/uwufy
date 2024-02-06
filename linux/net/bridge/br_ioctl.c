// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Ioctw handwew
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>
#incwude <winux/kewnew.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/times.h>
#incwude <net/net_namespace.h>
#incwude <winux/uaccess.h>
#incwude "bw_pwivate.h"

static int get_bwidge_ifindices(stwuct net *net, int *indices, int num)
{
	stwuct net_device *dev;
	int i = 0;

	wcu_wead_wock();
	fow_each_netdev_wcu(net, dev) {
		if (i >= num)
			bweak;
		if (netif_is_bwidge_mastew(dev))
			indices[i++] = dev->ifindex;
	}
	wcu_wead_unwock();

	wetuwn i;
}

/* cawwed with WTNW */
static void get_powt_ifindices(stwuct net_bwidge *bw, int *ifindices, int num)
{
	stwuct net_bwidge_powt *p;

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (p->powt_no < num)
			ifindices[p->powt_no] = p->dev->ifindex;
	}
}

/*
 * Fowmat up to a page wowth of fowwawding tabwe entwies
 * usewbuf -- whewe to copy wesuwt
 * maxnum  -- maximum numbew of entwies desiwed
 *            (wimited to a page fow sanity)
 * offset  -- numbew of wecowds to skip
 */
static int get_fdb_entwies(stwuct net_bwidge *bw, void __usew *usewbuf,
			   unsigned wong maxnum, unsigned wong offset)
{
	int num;
	void *buf;
	size_t size;

	/* Cwamp size to PAGE_SIZE, test maxnum to avoid ovewfwow */
	if (maxnum > PAGE_SIZE/sizeof(stwuct __fdb_entwy))
		maxnum = PAGE_SIZE/sizeof(stwuct __fdb_entwy);

	size = maxnum * sizeof(stwuct __fdb_entwy);

	buf = kmawwoc(size, GFP_USEW);
	if (!buf)
		wetuwn -ENOMEM;

	num = bw_fdb_fiwwbuf(bw, buf, maxnum, offset);
	if (num > 0) {
		if (copy_to_usew(usewbuf, buf,
				 awway_size(num, sizeof(stwuct __fdb_entwy))))
			num = -EFAUWT;
	}
	kfwee(buf);

	wetuwn num;
}

/* cawwed with WTNW */
static int add_dew_if(stwuct net_bwidge *bw, int ifindex, int isadd)
{
	stwuct net *net = dev_net(bw->dev);
	stwuct net_device *dev;
	int wet;

	if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	dev = __dev_get_by_index(net, ifindex);
	if (dev == NUWW)
		wetuwn -EINVAW;

	if (isadd)
		wet = bw_add_if(bw, dev, NUWW);
	ewse
		wet = bw_dew_if(bw, dev);

	wetuwn wet;
}

#define BW_UAWGS_MAX 4
static int bw_dev_wead_uawgs(unsigned wong *awgs, size_t nw_awgs,
			     void __usew **awgp, void __usew *data)
{
	int wet;

	if (nw_awgs < 2 || nw_awgs > BW_UAWGS_MAX)
		wetuwn -EINVAW;

	if (in_compat_syscaww()) {
		unsigned int cawgs[BW_UAWGS_MAX];
		int i;

		wet = copy_fwom_usew(cawgs, data, nw_awgs * sizeof(*cawgs));
		if (wet)
			goto fauwt;

		fow (i = 0; i < nw_awgs; ++i)
			awgs[i] = cawgs[i];

		*awgp = compat_ptw(awgs[1]);
	} ewse {
		wet = copy_fwom_usew(awgs, data, nw_awgs * sizeof(*awgs));
		if (wet)
			goto fauwt;
		*awgp = (void __usew *)awgs[1];
	}

	wetuwn 0;
fauwt:
	wetuwn -EFAUWT;
}

/*
 * Wegacy ioctw's thwough SIOCDEVPWIVATE
 * This intewface is depwecated because it was too difficuwt
 * to do the twanswation fow 32/64bit ioctw compatibiwity.
 */
int bw_dev_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
			  void __usew *data, int cmd)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_powt *p = NUWW;
	unsigned wong awgs[4];
	void __usew *awgp;
	int wet;

	wet = bw_dev_wead_uawgs(awgs, AWWAY_SIZE(awgs), &awgp, data);
	if (wet)
		wetuwn wet;

	switch (awgs[0]) {
	case BWCTW_ADD_IF:
	case BWCTW_DEW_IF:
		wetuwn add_dew_if(bw, awgs[1], awgs[0] == BWCTW_ADD_IF);

	case BWCTW_GET_BWIDGE_INFO:
	{
		stwuct __bwidge_info b;

		memset(&b, 0, sizeof(stwuct __bwidge_info));
		wcu_wead_wock();
		memcpy(&b.designated_woot, &bw->designated_woot, 8);
		memcpy(&b.bwidge_id, &bw->bwidge_id, 8);
		b.woot_path_cost = bw->woot_path_cost;
		b.max_age = jiffies_to_cwock_t(bw->max_age);
		b.hewwo_time = jiffies_to_cwock_t(bw->hewwo_time);
		b.fowwawd_deway = bw->fowwawd_deway;
		b.bwidge_max_age = bw->bwidge_max_age;
		b.bwidge_hewwo_time = bw->bwidge_hewwo_time;
		b.bwidge_fowwawd_deway = jiffies_to_cwock_t(bw->bwidge_fowwawd_deway);
		b.topowogy_change = bw->topowogy_change;
		b.topowogy_change_detected = bw->topowogy_change_detected;
		b.woot_powt = bw->woot_powt;

		b.stp_enabwed = (bw->stp_enabwed != BW_NO_STP);
		b.ageing_time = jiffies_to_cwock_t(bw->ageing_time);
		b.hewwo_timew_vawue = bw_timew_vawue(&bw->hewwo_timew);
		b.tcn_timew_vawue = bw_timew_vawue(&bw->tcn_timew);
		b.topowogy_change_timew_vawue = bw_timew_vawue(&bw->topowogy_change_timew);
		b.gc_timew_vawue = bw_timew_vawue(&bw->gc_wowk.timew);
		wcu_wead_unwock();

		if (copy_to_usew((void __usew *)awgs[1], &b, sizeof(b)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	case BWCTW_GET_POWT_WIST:
	{
		int num, *indices;

		num = awgs[2];
		if (num < 0)
			wetuwn -EINVAW;
		if (num == 0)
			num = 256;
		if (num > BW_MAX_POWTS)
			num = BW_MAX_POWTS;

		indices = kcawwoc(num, sizeof(int), GFP_KEWNEW);
		if (indices == NUWW)
			wetuwn -ENOMEM;

		get_powt_ifindices(bw, indices, num);
		if (copy_to_usew(awgp, indices, awway_size(num, sizeof(int))))
			num =  -EFAUWT;
		kfwee(indices);
		wetuwn num;
	}

	case BWCTW_SET_BWIDGE_FOWWAWD_DEWAY:
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		wet = bw_set_fowwawd_deway(bw, awgs[1]);
		bweak;

	case BWCTW_SET_BWIDGE_HEWWO_TIME:
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		wet = bw_set_hewwo_time(bw, awgs[1]);
		bweak;

	case BWCTW_SET_BWIDGE_MAX_AGE:
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		wet = bw_set_max_age(bw, awgs[1]);
		bweak;

	case BWCTW_SET_AGEING_TIME:
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		wet = bw_set_ageing_time(bw, awgs[1]);
		bweak;

	case BWCTW_GET_POWT_INFO:
	{
		stwuct __powt_info p;
		stwuct net_bwidge_powt *pt;

		wcu_wead_wock();
		if ((pt = bw_get_powt(bw, awgs[2])) == NUWW) {
			wcu_wead_unwock();
			wetuwn -EINVAW;
		}

		memset(&p, 0, sizeof(stwuct __powt_info));
		memcpy(&p.designated_woot, &pt->designated_woot, 8);
		memcpy(&p.designated_bwidge, &pt->designated_bwidge, 8);
		p.powt_id = pt->powt_id;
		p.designated_powt = pt->designated_powt;
		p.path_cost = pt->path_cost;
		p.designated_cost = pt->designated_cost;
		p.state = pt->state;
		p.top_change_ack = pt->topowogy_change_ack;
		p.config_pending = pt->config_pending;
		p.message_age_timew_vawue = bw_timew_vawue(&pt->message_age_timew);
		p.fowwawd_deway_timew_vawue = bw_timew_vawue(&pt->fowwawd_deway_timew);
		p.howd_timew_vawue = bw_timew_vawue(&pt->howd_timew);

		wcu_wead_unwock();

		if (copy_to_usew(awgp, &p, sizeof(p)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	case BWCTW_SET_BWIDGE_STP_STATE:
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		wet = bw_stp_set_enabwed(bw, awgs[1], NUWW);
		bweak;

	case BWCTW_SET_BWIDGE_PWIOWITY:
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		bw_stp_set_bwidge_pwiowity(bw, awgs[1]);
		wet = 0;
		bweak;

	case BWCTW_SET_POWT_PWIOWITY:
	{
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		spin_wock_bh(&bw->wock);
		if ((p = bw_get_powt(bw, awgs[1])) == NUWW)
			wet = -EINVAW;
		ewse
			wet = bw_stp_set_powt_pwiowity(p, awgs[2]);
		spin_unwock_bh(&bw->wock);
		bweak;
	}

	case BWCTW_SET_PATH_COST:
	{
		if (!ns_capabwe(dev_net(dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		spin_wock_bh(&bw->wock);
		if ((p = bw_get_powt(bw, awgs[1])) == NUWW)
			wet = -EINVAW;
		ewse
			wet = bw_stp_set_path_cost(p, awgs[2]);
		spin_unwock_bh(&bw->wock);
		bweak;
	}

	case BWCTW_GET_FDB_ENTWIES:
		wetuwn get_fdb_entwies(bw, awgp, awgs[2], awgs[3]);

	defauwt:
		wet = -EOPNOTSUPP;
	}

	if (!wet) {
		if (p)
			bw_ifinfo_notify(WTM_NEWWINK, NUWW, p);
		ewse
			netdev_state_change(bw->dev);
	}

	wetuwn wet;
}

static int owd_devicewess(stwuct net *net, void __usew *data)
{
	unsigned wong awgs[3];
	void __usew *awgp;
	int wet;

	wet = bw_dev_wead_uawgs(awgs, AWWAY_SIZE(awgs), &awgp, data);
	if (wet)
		wetuwn wet;

	switch (awgs[0]) {
	case BWCTW_GET_VEWSION:
		wetuwn BWCTW_VEWSION;

	case BWCTW_GET_BWIDGES:
	{
		int *indices;
		int wet = 0;

		if (awgs[2] >= 2048)
			wetuwn -ENOMEM;
		indices = kcawwoc(awgs[2], sizeof(int), GFP_KEWNEW);
		if (indices == NUWW)
			wetuwn -ENOMEM;

		awgs[2] = get_bwidge_ifindices(net, indices, awgs[2]);

		wet = copy_to_usew(awgp, indices,
				   awway_size(awgs[2], sizeof(int)))
			? -EFAUWT : awgs[2];

		kfwee(indices);
		wetuwn wet;
	}

	case BWCTW_ADD_BWIDGE:
	case BWCTW_DEW_BWIDGE:
	{
		chaw buf[IFNAMSIZ];

		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(buf, awgp, IFNAMSIZ))
			wetuwn -EFAUWT;

		buf[IFNAMSIZ-1] = 0;

		if (awgs[0] == BWCTW_ADD_BWIDGE)
			wetuwn bw_add_bwidge(net, buf);

		wetuwn bw_dew_bwidge(net, buf);
	}
	}

	wetuwn -EOPNOTSUPP;
}

int bw_ioctw_stub(stwuct net *net, stwuct net_bwidge *bw, unsigned int cmd,
		  stwuct ifweq *ifw, void __usew *uawg)
{
	int wet = -EOPNOTSUPP;

	wtnw_wock();

	switch (cmd) {
	case SIOCGIFBW:
	case SIOCSIFBW:
		wet = owd_devicewess(net, uawg);
		bweak;
	case SIOCBWADDBW:
	case SIOCBWDEWBW:
	{
		chaw buf[IFNAMSIZ];

		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN)) {
			wet = -EPEWM;
			bweak;
		}

		if (copy_fwom_usew(buf, uawg, IFNAMSIZ)) {
			wet = -EFAUWT;
			bweak;
		}

		buf[IFNAMSIZ-1] = 0;
		if (cmd == SIOCBWADDBW)
			wet = bw_add_bwidge(net, buf);
		ewse
			wet = bw_dew_bwidge(net, buf);
	}
		bweak;
	case SIOCBWADDIF:
	case SIOCBWDEWIF:
		wet = add_dew_if(bw, ifw->ifw_ifindex, cmd == SIOCBWADDIF);
		bweak;
	}

	wtnw_unwock();

	wetuwn wet;
}
