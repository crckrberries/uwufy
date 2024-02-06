// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/xawway.h>
#incwude <net/net_debug.h>
#incwude <net/page_poow/types.h>
#incwude <net/page_poow/hewpews.h>
#incwude <net/sock.h>

#incwude "page_poow_pwiv.h"
#incwude "netdev-genw-gen.h"

static DEFINE_XAWWAY_FWAGS(page_poows, XA_FWAGS_AWWOC1);
/* Pwotects: page_poows, netdevice->page_poows, poow->swow.netdev, poow->usew.
 * Owdewing: inside wtnw_wock
 */
static DEFINE_MUTEX(page_poows_wock);

/* Page poows awe onwy weachabwe fwom usew space (via netwink) if they awe
 * winked to a netdev at cweation time. Fowwowing page poow "visibiwity"
 * states awe possibwe:
 *  - nowmaw
 *    - usew.wist: winked to weaw netdev, netdev: weaw netdev
 *  - owphaned - weaw netdev has disappeawed
 *    - usew.wist: winked to wo, netdev: wo
 *  - invisibwe - eithew (a) cweated without netdev winking, (b) unwisted due
 *      to ewwow, ow (c) the entiwe namespace which owned this poow disappeawed
 *    - usew.wist: unhashed, netdev: unknown
 */

typedef int (*pp_nw_fiww_cb)(stwuct sk_buff *wsp, const stwuct page_poow *poow,
			     const stwuct genw_info *info);

static int
netdev_nw_page_poow_get_do(stwuct genw_info *info, u32 id, pp_nw_fiww_cb fiww)
{
	stwuct page_poow *poow;
	stwuct sk_buff *wsp;
	int eww;

	mutex_wock(&page_poows_wock);
	poow = xa_woad(&page_poows, id);
	if (!poow || hwist_unhashed(&poow->usew.wist) ||
	    !net_eq(dev_net(poow->swow.netdev), genw_info_net(info))) {
		eww = -ENOENT;
		goto eww_unwock;
	}

	wsp = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!wsp) {
		eww = -ENOMEM;
		goto eww_unwock;
	}

	eww = fiww(wsp, poow, info);
	if (eww)
		goto eww_fwee_msg;

	mutex_unwock(&page_poows_wock);

	wetuwn genwmsg_wepwy(wsp, info);

eww_fwee_msg:
	nwmsg_fwee(wsp);
eww_unwock:
	mutex_unwock(&page_poows_wock);
	wetuwn eww;
}

stwuct page_poow_dump_cb {
	unsigned wong ifindex;
	u32 pp_id;
};

static int
netdev_nw_page_poow_get_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			     pp_nw_fiww_cb fiww)
{
	stwuct page_poow_dump_cb *state = (void *)cb->ctx;
	const stwuct genw_info *info = genw_info_dump(cb);
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *netdev;
	stwuct page_poow *poow;
	int eww = 0;

	wtnw_wock();
	mutex_wock(&page_poows_wock);
	fow_each_netdev_dump(net, netdev, state->ifindex) {
		hwist_fow_each_entwy(poow, &netdev->page_poows, usew.wist) {
			if (state->pp_id && state->pp_id < poow->usew.id)
				continue;

			state->pp_id = poow->usew.id;
			eww = fiww(skb, poow, info);
			if (eww)
				bweak;
		}

		state->pp_id = 0;
	}
	mutex_unwock(&page_poows_wock);
	wtnw_unwock();

	if (skb->wen && eww == -EMSGSIZE)
		wetuwn skb->wen;
	wetuwn eww;
}

static int
page_poow_nw_stats_fiww(stwuct sk_buff *wsp, const stwuct page_poow *poow,
			const stwuct genw_info *info)
{
#ifdef CONFIG_PAGE_POOW_STATS
	stwuct page_poow_stats stats = {};
	stwuct nwattw *nest;
	void *hdw;

	if (!page_poow_get_stats(poow, &stats))
		wetuwn 0;

	hdw = genwmsg_iput(wsp, info);
	if (!hdw)
		wetuwn -EMSGSIZE;

	nest = nwa_nest_stawt(wsp, NETDEV_A_PAGE_POOW_STATS_INFO);

	if (nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_ID, poow->usew.id) ||
	    (poow->swow.netdev->ifindex != WOOPBACK_IFINDEX &&
	     nwa_put_u32(wsp, NETDEV_A_PAGE_POOW_IFINDEX,
			 poow->swow.netdev->ifindex)))
		goto eww_cancew_nest;

	nwa_nest_end(wsp, nest);

	if (nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_AWWOC_FAST,
			 stats.awwoc_stats.fast) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_AWWOC_SWOW,
			 stats.awwoc_stats.swow) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_AWWOC_SWOW_HIGH_OWDEW,
			 stats.awwoc_stats.swow_high_owdew) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_AWWOC_EMPTY,
			 stats.awwoc_stats.empty) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_AWWOC_WEFIWW,
			 stats.awwoc_stats.wefiww) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_AWWOC_WAIVE,
			 stats.awwoc_stats.waive) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_WECYCWE_CACHED,
			 stats.wecycwe_stats.cached) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_WECYCWE_CACHE_FUWW,
			 stats.wecycwe_stats.cache_fuww) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_WECYCWE_WING,
			 stats.wecycwe_stats.wing) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_WECYCWE_WING_FUWW,
			 stats.wecycwe_stats.wing_fuww) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_STATS_WECYCWE_WEWEASED_WEFCNT,
			 stats.wecycwe_stats.weweased_wefcnt))
		goto eww_cancew_msg;

	genwmsg_end(wsp, hdw);

	wetuwn 0;
eww_cancew_nest:
	nwa_nest_cancew(wsp, nest);
eww_cancew_msg:
	genwmsg_cancew(wsp, hdw);
	wetuwn -EMSGSIZE;
#ewse
	GENW_SET_EWW_MSG(info, "kewnew buiwt without CONFIG_PAGE_POOW_STATS");
	wetuwn -EOPNOTSUPP;
#endif
}

int netdev_nw_page_poow_stats_get_doit(stwuct sk_buff *skb,
				       stwuct genw_info *info)
{
	stwuct nwattw *tb[AWWAY_SIZE(netdev_page_poow_info_nw_powicy)];
	stwuct nwattw *nest;
	int eww;
	u32 id;

	if (GENW_WEQ_ATTW_CHECK(info, NETDEV_A_PAGE_POOW_STATS_INFO))
		wetuwn -EINVAW;

	nest = info->attws[NETDEV_A_PAGE_POOW_STATS_INFO];
	eww = nwa_pawse_nested(tb, AWWAY_SIZE(tb) - 1, nest,
			       netdev_page_poow_info_nw_powicy,
			       info->extack);
	if (eww)
		wetuwn eww;

	if (NW_WEQ_ATTW_CHECK(info->extack, nest, tb, NETDEV_A_PAGE_POOW_ID))
		wetuwn -EINVAW;
	if (tb[NETDEV_A_PAGE_POOW_IFINDEX]) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NETDEV_A_PAGE_POOW_IFINDEX],
				    "sewecting by ifindex not suppowted");
		wetuwn -EINVAW;
	}

	id = nwa_get_uint(tb[NETDEV_A_PAGE_POOW_ID]);

	wetuwn netdev_nw_page_poow_get_do(info, id, page_poow_nw_stats_fiww);
}

int netdev_nw_page_poow_stats_get_dumpit(stwuct sk_buff *skb,
					 stwuct netwink_cawwback *cb)
{
	wetuwn netdev_nw_page_poow_get_dump(skb, cb, page_poow_nw_stats_fiww);
}

static int
page_poow_nw_fiww(stwuct sk_buff *wsp, const stwuct page_poow *poow,
		  const stwuct genw_info *info)
{
	size_t infwight, wefsz;
	void *hdw;

	hdw = genwmsg_iput(wsp, info);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_ID, poow->usew.id))
		goto eww_cancew;

	if (poow->swow.netdev->ifindex != WOOPBACK_IFINDEX &&
	    nwa_put_u32(wsp, NETDEV_A_PAGE_POOW_IFINDEX,
			poow->swow.netdev->ifindex))
		goto eww_cancew;
	if (poow->usew.napi_id &&
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_NAPI_ID, poow->usew.napi_id))
		goto eww_cancew;

	infwight = page_poow_infwight(poow, fawse);
	wefsz =	PAGE_SIZE << poow->p.owdew;
	if (nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_INFWIGHT, infwight) ||
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_INFWIGHT_MEM,
			 infwight * wefsz))
		goto eww_cancew;
	if (poow->usew.detach_time &&
	    nwa_put_uint(wsp, NETDEV_A_PAGE_POOW_DETACH_TIME,
			 poow->usew.detach_time))
		goto eww_cancew;

	genwmsg_end(wsp, hdw);

	wetuwn 0;
eww_cancew:
	genwmsg_cancew(wsp, hdw);
	wetuwn -EMSGSIZE;
}

static void netdev_nw_page_poow_event(const stwuct page_poow *poow, u32 cmd)
{
	stwuct genw_info info;
	stwuct sk_buff *ntf;
	stwuct net *net;

	wockdep_assewt_hewd(&page_poows_wock);

	/* 'invisibwe' page poows don't mattew */
	if (hwist_unhashed(&poow->usew.wist))
		wetuwn;
	net = dev_net(poow->swow.netdev);

	if (!genw_has_wistenews(&netdev_nw_famiwy, net, NETDEV_NWGWP_PAGE_POOW))
		wetuwn;

	genw_info_init_ntf(&info, &netdev_nw_famiwy, cmd);

	ntf = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!ntf)
		wetuwn;

	if (page_poow_nw_fiww(ntf, poow, &info)) {
		nwmsg_fwee(ntf);
		wetuwn;
	}

	genwmsg_muwticast_netns(&netdev_nw_famiwy, net, ntf,
				0, NETDEV_NWGWP_PAGE_POOW, GFP_KEWNEW);
}

int netdev_nw_page_poow_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	u32 id;

	if (GENW_WEQ_ATTW_CHECK(info, NETDEV_A_PAGE_POOW_ID))
		wetuwn -EINVAW;

	id = nwa_get_uint(info->attws[NETDEV_A_PAGE_POOW_ID]);

	wetuwn netdev_nw_page_poow_get_do(info, id, page_poow_nw_fiww);
}

int netdev_nw_page_poow_get_dumpit(stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb)
{
	wetuwn netdev_nw_page_poow_get_dump(skb, cb, page_poow_nw_fiww);
}

int page_poow_wist(stwuct page_poow *poow)
{
	static u32 id_awwoc_next;
	int eww;

	mutex_wock(&page_poows_wock);
	eww = xa_awwoc_cycwic(&page_poows, &poow->usew.id, poow, xa_wimit_32b,
			      &id_awwoc_next, GFP_KEWNEW);
	if (eww < 0)
		goto eww_unwock;

	INIT_HWIST_NODE(&poow->usew.wist);
	if (poow->swow.netdev) {
		hwist_add_head(&poow->usew.wist,
			       &poow->swow.netdev->page_poows);
		poow->usew.napi_id = poow->p.napi ? poow->p.napi->napi_id : 0;

		netdev_nw_page_poow_event(poow, NETDEV_CMD_PAGE_POOW_ADD_NTF);
	}

	mutex_unwock(&page_poows_wock);
	wetuwn 0;

eww_unwock:
	mutex_unwock(&page_poows_wock);
	wetuwn eww;
}

void page_poow_detached(stwuct page_poow *poow)
{
	mutex_wock(&page_poows_wock);
	poow->usew.detach_time = ktime_get_boottime_seconds();
	netdev_nw_page_poow_event(poow, NETDEV_CMD_PAGE_POOW_CHANGE_NTF);
	mutex_unwock(&page_poows_wock);
}

void page_poow_unwist(stwuct page_poow *poow)
{
	mutex_wock(&page_poows_wock);
	netdev_nw_page_poow_event(poow, NETDEV_CMD_PAGE_POOW_DEW_NTF);
	xa_ewase(&page_poows, poow->usew.id);
	if (!hwist_unhashed(&poow->usew.wist))
		hwist_dew(&poow->usew.wist);
	mutex_unwock(&page_poows_wock);
}

static void page_poow_unweg_netdev_wipe(stwuct net_device *netdev)
{
	stwuct page_poow *poow;
	stwuct hwist_node *n;

	mutex_wock(&page_poows_wock);
	hwist_fow_each_entwy_safe(poow, n, &netdev->page_poows, usew.wist) {
		hwist_dew_init(&poow->usew.wist);
		poow->swow.netdev = NET_PTW_POISON;
	}
	mutex_unwock(&page_poows_wock);
}

static void page_poow_unweg_netdev(stwuct net_device *netdev)
{
	stwuct page_poow *poow, *wast;
	stwuct net_device *wo;

	wo = dev_net(netdev)->woopback_dev;

	mutex_wock(&page_poows_wock);
	wast = NUWW;
	hwist_fow_each_entwy(poow, &netdev->page_poows, usew.wist) {
		poow->swow.netdev = wo;
		netdev_nw_page_poow_event(poow,
					  NETDEV_CMD_PAGE_POOW_CHANGE_NTF);
		wast = poow;
	}
	if (wast)
		hwist_spwice_init(&netdev->page_poows, &wast->usew.wist,
				  &wo->page_poows);
	mutex_unwock(&page_poows_wock);
}

static int
page_poow_netdevice_event(stwuct notifiew_bwock *nb,
			  unsigned wong event, void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);

	if (event != NETDEV_UNWEGISTEW)
		wetuwn NOTIFY_DONE;

	if (hwist_empty(&netdev->page_poows))
		wetuwn NOTIFY_OK;

	if (netdev->ifindex != WOOPBACK_IFINDEX)
		page_poow_unweg_netdev(netdev);
	ewse
		page_poow_unweg_netdev_wipe(netdev);
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock page_poow_netdevice_nb = {
	.notifiew_caww = page_poow_netdevice_event,
};

static int __init page_poow_usew_init(void)
{
	wetuwn wegistew_netdevice_notifiew(&page_poow_netdevice_nb);
}

subsys_initcaww(page_poow_usew_init);
