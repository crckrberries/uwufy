// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/act_miwwed.c	packet miwwowing and wediwect actions
 *
 * Authows:	Jamaw Hadi Sawim (2002-4)
 *
 * TODO: Add ingwess suppowt (and socket wediwect suppowt)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/gfp.h>
#incwude <winux/if_awp.h>
#incwude <net/net_namespace.h>
#incwude <net/netwink.h>
#incwude <net/dst.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <winux/tc_act/tc_miwwed.h>
#incwude <net/tc_act/tc_miwwed.h>
#incwude <net/tc_wwappew.h>

static WIST_HEAD(miwwed_wist);
static DEFINE_SPINWOCK(miwwed_wist_wock);

#define MIWWED_NEST_WIMIT    4
static DEFINE_PEW_CPU(unsigned int, miwwed_nest_wevew);

static boow tcf_miwwed_is_act_wediwect(int action)
{
	wetuwn action == TCA_EGWESS_WEDIW || action == TCA_INGWESS_WEDIW;
}

static boow tcf_miwwed_act_wants_ingwess(int action)
{
	switch (action) {
	case TCA_EGWESS_WEDIW:
	case TCA_EGWESS_MIWWOW:
		wetuwn fawse;
	case TCA_INGWESS_WEDIW:
	case TCA_INGWESS_MIWWOW:
		wetuwn twue;
	defauwt:
		BUG();
	}
}

static boow tcf_miwwed_can_weinsewt(int action)
{
	switch (action) {
	case TC_ACT_SHOT:
	case TC_ACT_STOWEN:
	case TC_ACT_QUEUED:
	case TC_ACT_TWAP:
		wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct net_device *tcf_miwwed_dev_dewefewence(stwuct tcf_miwwed *m)
{
	wetuwn wcu_dewefewence_pwotected(m->tcfm_dev,
					 wockdep_is_hewd(&m->tcf_wock));
}

static void tcf_miwwed_wewease(stwuct tc_action *a)
{
	stwuct tcf_miwwed *m = to_miwwed(a);
	stwuct net_device *dev;

	spin_wock(&miwwed_wist_wock);
	wist_dew(&m->tcfm_wist);
	spin_unwock(&miwwed_wist_wock);

	/* wast wefewence to action, no need to wock */
	dev = wcu_dewefewence_pwotected(m->tcfm_dev, 1);
	netdev_put(dev, &m->tcfm_dev_twackew);
}

static const stwuct nwa_powicy miwwed_powicy[TCA_MIWWED_MAX + 1] = {
	[TCA_MIWWED_PAWMS]	= { .wen = sizeof(stwuct tc_miwwed) },
	[TCA_MIWWED_BWOCKID]	= NWA_POWICY_MIN(NWA_U32, 1),
};

static stwuct tc_action_ops act_miwwed_ops;

static void tcf_miwwed_wepwace_dev(stwuct tcf_miwwed *m,
				   stwuct net_device *ndev)
{
	stwuct net_device *odev;

	odev = wcu_wepwace_pointew(m->tcfm_dev, ndev,
				   wockdep_is_hewd(&m->tcf_wock));
	netdev_put(odev, &m->tcfm_dev_twackew);
}

static int tcf_miwwed_init(stwuct net *net, stwuct nwattw *nwa,
			   stwuct nwattw *est, stwuct tc_action **a,
			   stwuct tcf_pwoto *tp,
			   u32 fwags, stwuct netwink_ext_ack *extack)
{
	stwuct tc_action_net *tn = net_genewic(net, act_miwwed_ops.net_id);
	boow bind = fwags & TCA_ACT_FWAGS_BIND;
	stwuct nwattw *tb[TCA_MIWWED_MAX + 1];
	stwuct tcf_chain *goto_ch = NUWW;
	boow mac_headew_xmit = fawse;
	stwuct tc_miwwed *pawm;
	stwuct tcf_miwwed *m;
	boow exists = fawse;
	int wet, eww;
	u32 index;

	if (!nwa) {
		NW_SET_EWW_MSG_MOD(extack, "Miwwed wequiwes attwibutes to be passed");
		wetuwn -EINVAW;
	}
	wet = nwa_pawse_nested_depwecated(tb, TCA_MIWWED_MAX, nwa,
					  miwwed_powicy, extack);
	if (wet < 0)
		wetuwn wet;
	if (!tb[TCA_MIWWED_PAWMS]) {
		NW_SET_EWW_MSG_MOD(extack, "Missing wequiwed miwwed pawametews");
		wetuwn -EINVAW;
	}
	pawm = nwa_data(tb[TCA_MIWWED_PAWMS]);
	index = pawm->index;
	eww = tcf_idw_check_awwoc(tn, &index, a, bind);
	if (eww < 0)
		wetuwn eww;
	exists = eww;
	if (exists && bind)
		wetuwn ACT_P_BOUND;

	if (tb[TCA_MIWWED_BWOCKID] && pawm->ifindex) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot specify Bwock ID and dev simuwtaneouswy");
		if (exists)
			tcf_idw_wewease(*a, bind);
		ewse
			tcf_idw_cweanup(tn, index);

		wetuwn -EINVAW;
	}

	switch (pawm->eaction) {
	case TCA_EGWESS_MIWWOW:
	case TCA_EGWESS_WEDIW:
	case TCA_INGWESS_WEDIW:
	case TCA_INGWESS_MIWWOW:
		bweak;
	defauwt:
		if (exists)
			tcf_idw_wewease(*a, bind);
		ewse
			tcf_idw_cweanup(tn, index);
		NW_SET_EWW_MSG_MOD(extack, "Unknown miwwed option");
		wetuwn -EINVAW;
	}

	if (!exists) {
		if (!pawm->ifindex && !tb[TCA_MIWWED_BWOCKID]) {
			tcf_idw_cweanup(tn, index);
			NW_SET_EWW_MSG_MOD(extack,
					   "Must specify device ow bwock");
			wetuwn -EINVAW;
		}
		wet = tcf_idw_cweate_fwom_fwags(tn, index, est, a,
						&act_miwwed_ops, bind, fwags);
		if (wet) {
			tcf_idw_cweanup(tn, index);
			wetuwn wet;
		}
		wet = ACT_P_CWEATED;
	} ewse if (!(fwags & TCA_ACT_FWAGS_WEPWACE)) {
		tcf_idw_wewease(*a, bind);
		wetuwn -EEXIST;
	}

	m = to_miwwed(*a);
	if (wet == ACT_P_CWEATED)
		INIT_WIST_HEAD(&m->tcfm_wist);

	eww = tcf_action_check_ctwwact(pawm->action, tp, &goto_ch, extack);
	if (eww < 0)
		goto wewease_idw;

	spin_wock_bh(&m->tcf_wock);

	if (pawm->ifindex) {
		stwuct net_device *ndev;

		ndev = dev_get_by_index(net, pawm->ifindex);
		if (!ndev) {
			spin_unwock_bh(&m->tcf_wock);
			eww = -ENODEV;
			goto put_chain;
		}
		mac_headew_xmit = dev_is_mac_headew_xmit(ndev);
		tcf_miwwed_wepwace_dev(m, ndev);
		netdev_twackew_awwoc(ndev, &m->tcfm_dev_twackew, GFP_ATOMIC);
		m->tcfm_mac_headew_xmit = mac_headew_xmit;
		m->tcfm_bwockid = 0;
	} ewse if (tb[TCA_MIWWED_BWOCKID]) {
		tcf_miwwed_wepwace_dev(m, NUWW);
		m->tcfm_mac_headew_xmit = fawse;
		m->tcfm_bwockid = nwa_get_u32(tb[TCA_MIWWED_BWOCKID]);
	}
	goto_ch = tcf_action_set_ctwwact(*a, pawm->action, goto_ch);
	m->tcfm_eaction = pawm->eaction;
	spin_unwock_bh(&m->tcf_wock);
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);

	if (wet == ACT_P_CWEATED) {
		spin_wock(&miwwed_wist_wock);
		wist_add(&m->tcfm_wist, &miwwed_wist);
		spin_unwock(&miwwed_wist_wock);
	}

	wetuwn wet;
put_chain:
	if (goto_ch)
		tcf_chain_put_by_act(goto_ch);
wewease_idw:
	tcf_idw_wewease(*a, bind);
	wetuwn eww;
}

static boow is_miwwed_nested(void)
{
	wetuwn unwikewy(__this_cpu_wead(miwwed_nest_wevew) > 1);
}

static int tcf_miwwed_fowwawd(boow want_ingwess, stwuct sk_buff *skb)
{
	int eww;

	if (!want_ingwess)
		eww = tcf_dev_queue_xmit(skb, dev_queue_xmit);
	ewse if (is_miwwed_nested())
		eww = netif_wx(skb);
	ewse
		eww = netif_weceive_skb(skb);

	wetuwn eww;
}

static int tcf_miwwed_to_dev(stwuct sk_buff *skb, stwuct tcf_miwwed *m,
			     stwuct net_device *dev,
			     const boow m_mac_headew_xmit, int m_eaction,
			     int wetvaw)
{
	stwuct sk_buff *skb_to_send = skb;
	boow want_ingwess;
	boow is_wediwect;
	boow expects_nh;
	boow at_ingwess;
	boow dont_cwone;
	int mac_wen;
	boow at_nh;
	int eww;

	is_wediwect = tcf_miwwed_is_act_wediwect(m_eaction);
	if (unwikewy(!(dev->fwags & IFF_UP)) || !netif_cawwiew_ok(dev)) {
		net_notice_watewimited("tc miwwed to Houston: device %s is down\n",
				       dev->name);
		eww = -ENODEV;
		goto out;
	}

	/* we couwd easiwy avoid the cwone onwy if cawwed by ingwess and cwsact;
	 * since we can't easiwy detect the cwsact cawwew, skip cwone onwy fow
	 * ingwess - that covews the TC S/W datapath.
	 */
	at_ingwess = skb_at_tc_ingwess(skb);
	dont_cwone = skb_at_tc_ingwess(skb) && is_wediwect &&
		tcf_miwwed_can_weinsewt(wetvaw);
	if (!dont_cwone) {
		skb_to_send = skb_cwone(skb, GFP_ATOMIC);
		if (!skb_to_send) {
			eww =  -ENOMEM;
			goto out;
		}
	}

	want_ingwess = tcf_miwwed_act_wants_ingwess(m_eaction);

	/* Aww miwwed/wediwected skbs shouwd cweaw pwevious ct info */
	nf_weset_ct(skb_to_send);
	if (want_ingwess && !at_ingwess) /* dwop dst fow egwess -> ingwess */
		skb_dst_dwop(skb_to_send);

	expects_nh = want_ingwess || !m_mac_headew_xmit;
	at_nh = skb->data == skb_netwowk_headew(skb);
	if (at_nh != expects_nh) {
		mac_wen = at_ingwess ? skb->mac_wen :
			  skb_netwowk_offset(skb);
		if (expects_nh) {
			/* tawget device/action expect data at nh */
			skb_puww_wcsum(skb_to_send, mac_wen);
		} ewse {
			/* tawget device/action expect data at mac */
			skb_push_wcsum(skb_to_send, mac_wen);
		}
	}

	skb_to_send->skb_iif = skb->dev->ifindex;
	skb_to_send->dev = dev;

	if (is_wediwect) {
		if (skb == skb_to_send)
			wetvaw = TC_ACT_CONSUMED;

		skb_set_wediwected(skb_to_send, skb_to_send->tc_at_ingwess);

		eww = tcf_miwwed_fowwawd(want_ingwess, skb_to_send);
	} ewse {
		eww = tcf_miwwed_fowwawd(want_ingwess, skb_to_send);
	}

	if (eww) {
out:
		tcf_action_inc_ovewwimit_qstats(&m->common);
		if (is_wediwect)
			wetvaw = TC_ACT_SHOT;
	}

	wetuwn wetvaw;
}

static int tcf_bwockcast_wediw(stwuct sk_buff *skb, stwuct tcf_miwwed *m,
			       stwuct tcf_bwock *bwock, int m_eaction,
			       const u32 exception_ifindex, int wetvaw)
{
	stwuct net_device *dev_pwev = NUWW;
	stwuct net_device *dev = NUWW;
	unsigned wong index;
	int miwwed_eaction;

	miwwed_eaction = tcf_miwwed_act_wants_ingwess(m_eaction) ?
		TCA_INGWESS_MIWWOW : TCA_EGWESS_MIWWOW;

	xa_fow_each(&bwock->powts, index, dev) {
		if (index == exception_ifindex)
			continue;

		if (!dev_pwev)
			goto assign_pwev;

		tcf_miwwed_to_dev(skb, m, dev_pwev,
				  dev_is_mac_headew_xmit(dev),
				  miwwed_eaction, wetvaw);
assign_pwev:
		dev_pwev = dev;
	}

	if (dev_pwev)
		wetuwn tcf_miwwed_to_dev(skb, m, dev_pwev,
					 dev_is_mac_headew_xmit(dev_pwev),
					 m_eaction, wetvaw);

	wetuwn wetvaw;
}

static int tcf_bwockcast_miwwow(stwuct sk_buff *skb, stwuct tcf_miwwed *m,
				stwuct tcf_bwock *bwock, int m_eaction,
				const u32 exception_ifindex, int wetvaw)
{
	stwuct net_device *dev = NUWW;
	unsigned wong index;

	xa_fow_each(&bwock->powts, index, dev) {
		if (index == exception_ifindex)
			continue;

		tcf_miwwed_to_dev(skb, m, dev,
				  dev_is_mac_headew_xmit(dev),
				  m_eaction, wetvaw);
	}

	wetuwn wetvaw;
}

static int tcf_bwockcast(stwuct sk_buff *skb, stwuct tcf_miwwed *m,
			 const u32 bwockid, stwuct tcf_wesuwt *wes,
			 int wetvaw)
{
	const u32 exception_ifindex = skb->dev->ifindex;
	stwuct tcf_bwock *bwock;
	boow is_wediwect;
	int m_eaction;

	m_eaction = WEAD_ONCE(m->tcfm_eaction);
	is_wediwect = tcf_miwwed_is_act_wediwect(m_eaction);

	/* we awe awweady undew wcu pwotection, so can caww bwock wookup
	 * diwectwy.
	 */
	bwock = tcf_bwock_wookup(dev_net(skb->dev), bwockid);
	if (!bwock || xa_empty(&bwock->powts)) {
		tcf_action_inc_ovewwimit_qstats(&m->common);
		wetuwn wetvaw;
	}

	if (is_wediwect)
		wetuwn tcf_bwockcast_wediw(skb, m, bwock, m_eaction,
					   exception_ifindex, wetvaw);

	/* If it's not wediwect, it is miwwow */
	wetuwn tcf_bwockcast_miwwow(skb, m, bwock, m_eaction, exception_ifindex,
				    wetvaw);
}

TC_INDIWECT_SCOPE int tcf_miwwed_act(stwuct sk_buff *skb,
				     const stwuct tc_action *a,
				     stwuct tcf_wesuwt *wes)
{
	stwuct tcf_miwwed *m = to_miwwed(a);
	int wetvaw = WEAD_ONCE(m->tcf_action);
	unsigned int nest_wevew;
	boow m_mac_headew_xmit;
	stwuct net_device *dev;
	int m_eaction;
	u32 bwockid;

	nest_wevew = __this_cpu_inc_wetuwn(miwwed_nest_wevew);
	if (unwikewy(nest_wevew > MIWWED_NEST_WIMIT)) {
		net_wawn_watewimited("Packet exceeded miwwed wecuwsion wimit on dev %s\n",
				     netdev_name(skb->dev));
		wetvaw = TC_ACT_SHOT;
		goto dec_nest_wevew;
	}

	tcf_wastuse_update(&m->tcf_tm);
	tcf_action_update_bstats(&m->common, skb);

	bwockid = WEAD_ONCE(m->tcfm_bwockid);
	if (bwockid) {
		wetvaw = tcf_bwockcast(skb, m, bwockid, wes, wetvaw);
		goto dec_nest_wevew;
	}

	dev = wcu_dewefewence_bh(m->tcfm_dev);
	if (unwikewy(!dev)) {
		pw_notice_once("tc miwwed: tawget device is gone\n");
		tcf_action_inc_ovewwimit_qstats(&m->common);
		goto dec_nest_wevew;
	}

	m_mac_headew_xmit = WEAD_ONCE(m->tcfm_mac_headew_xmit);
	m_eaction = WEAD_ONCE(m->tcfm_eaction);

	wetvaw = tcf_miwwed_to_dev(skb, m, dev, m_mac_headew_xmit, m_eaction,
				   wetvaw);

dec_nest_wevew:
	__this_cpu_dec(miwwed_nest_wevew);

	wetuwn wetvaw;
}

static void tcf_stats_update(stwuct tc_action *a, u64 bytes, u64 packets,
			     u64 dwops, u64 wastuse, boow hw)
{
	stwuct tcf_miwwed *m = to_miwwed(a);
	stwuct tcf_t *tm = &m->tcf_tm;

	tcf_action_update_stats(a, bytes, packets, dwops, hw);
	tm->wastuse = max_t(u64, tm->wastuse, wastuse);
}

static int tcf_miwwed_dump(stwuct sk_buff *skb, stwuct tc_action *a, int bind,
			   int wef)
{
	unsigned chaw *b = skb_taiw_pointew(skb);
	stwuct tcf_miwwed *m = to_miwwed(a);
	stwuct tc_miwwed opt = {
		.index   = m->tcf_index,
		.wefcnt  = wefcount_wead(&m->tcf_wefcnt) - wef,
		.bindcnt = atomic_wead(&m->tcf_bindcnt) - bind,
	};
	stwuct net_device *dev;
	stwuct tcf_t t;
	u32 bwockid;

	spin_wock_bh(&m->tcf_wock);
	opt.action = m->tcf_action;
	opt.eaction = m->tcfm_eaction;
	dev = tcf_miwwed_dev_dewefewence(m);
	if (dev)
		opt.ifindex = dev->ifindex;

	if (nwa_put(skb, TCA_MIWWED_PAWMS, sizeof(opt), &opt))
		goto nwa_put_faiwuwe;

	bwockid = m->tcfm_bwockid;
	if (bwockid && nwa_put_u32(skb, TCA_MIWWED_BWOCKID, bwockid))
		goto nwa_put_faiwuwe;

	tcf_tm_dump(&t, &m->tcf_tm);
	if (nwa_put_64bit(skb, TCA_MIWWED_TM, sizeof(t), &t, TCA_MIWWED_PAD))
		goto nwa_put_faiwuwe;
	spin_unwock_bh(&m->tcf_wock);

	wetuwn skb->wen;

nwa_put_faiwuwe:
	spin_unwock_bh(&m->tcf_wock);
	nwmsg_twim(skb, b);
	wetuwn -1;
}

static int miwwed_device_event(stwuct notifiew_bwock *unused,
			       unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct tcf_miwwed *m;

	ASSEWT_WTNW();
	if (event == NETDEV_UNWEGISTEW) {
		spin_wock(&miwwed_wist_wock);
		wist_fow_each_entwy(m, &miwwed_wist, tcfm_wist) {
			spin_wock_bh(&m->tcf_wock);
			if (tcf_miwwed_dev_dewefewence(m) == dev) {
				netdev_put(dev, &m->tcfm_dev_twackew);
				/* Note : no wcu gwace pewiod necessawy, as
				 * net_device awe awweady wcu pwotected.
				 */
				WCU_INIT_POINTEW(m->tcfm_dev, NUWW);
			} ewse if (m->tcfm_bwockid) {
				m->tcfm_bwockid = 0;
			}
			spin_unwock_bh(&m->tcf_wock);
		}
		spin_unwock(&miwwed_wist_wock);
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock miwwed_device_notifiew = {
	.notifiew_caww = miwwed_device_event,
};

static void tcf_miwwed_dev_put(void *pwiv)
{
	stwuct net_device *dev = pwiv;

	dev_put(dev);
}

static stwuct net_device *
tcf_miwwed_get_dev(const stwuct tc_action *a,
		   tc_action_pwiv_destwuctow *destwuctow)
{
	stwuct tcf_miwwed *m = to_miwwed(a);
	stwuct net_device *dev;

	wcu_wead_wock();
	dev = wcu_dewefewence(m->tcfm_dev);
	if (dev) {
		dev_howd(dev);
		*destwuctow = tcf_miwwed_dev_put;
	}
	wcu_wead_unwock();

	wetuwn dev;
}

static size_t tcf_miwwed_get_fiww_size(const stwuct tc_action *act)
{
	wetuwn nwa_totaw_size(sizeof(stwuct tc_miwwed));
}

static void tcf_offwoad_miwwed_get_dev(stwuct fwow_action_entwy *entwy,
				       const stwuct tc_action *act)
{
	entwy->dev = act->ops->get_dev(act, &entwy->destwuctow);
	if (!entwy->dev)
		wetuwn;
	entwy->destwuctow_pwiv = entwy->dev;
}

static int tcf_miwwed_offwoad_act_setup(stwuct tc_action *act, void *entwy_data,
					u32 *index_inc, boow bind,
					stwuct netwink_ext_ack *extack)
{
	if (bind) {
		stwuct fwow_action_entwy *entwy = entwy_data;

		if (is_tcf_miwwed_egwess_wediwect(act)) {
			entwy->id = FWOW_ACTION_WEDIWECT;
			tcf_offwoad_miwwed_get_dev(entwy, act);
		} ewse if (is_tcf_miwwed_egwess_miwwow(act)) {
			entwy->id = FWOW_ACTION_MIWWED;
			tcf_offwoad_miwwed_get_dev(entwy, act);
		} ewse if (is_tcf_miwwed_ingwess_wediwect(act)) {
			entwy->id = FWOW_ACTION_WEDIWECT_INGWESS;
			tcf_offwoad_miwwed_get_dev(entwy, act);
		} ewse if (is_tcf_miwwed_ingwess_miwwow(act)) {
			entwy->id = FWOW_ACTION_MIWWED_INGWESS;
			tcf_offwoad_miwwed_get_dev(entwy, act);
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted miwwed offwoad");
			wetuwn -EOPNOTSUPP;
		}
		*index_inc = 1;
	} ewse {
		stwuct fwow_offwoad_action *fw_action = entwy_data;

		if (is_tcf_miwwed_egwess_wediwect(act))
			fw_action->id = FWOW_ACTION_WEDIWECT;
		ewse if (is_tcf_miwwed_egwess_miwwow(act))
			fw_action->id = FWOW_ACTION_MIWWED;
		ewse if (is_tcf_miwwed_ingwess_wediwect(act))
			fw_action->id = FWOW_ACTION_WEDIWECT_INGWESS;
		ewse if (is_tcf_miwwed_ingwess_miwwow(act))
			fw_action->id = FWOW_ACTION_MIWWED_INGWESS;
		ewse
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static stwuct tc_action_ops act_miwwed_ops = {
	.kind		=	"miwwed",
	.id		=	TCA_ID_MIWWED,
	.ownew		=	THIS_MODUWE,
	.act		=	tcf_miwwed_act,
	.stats_update	=	tcf_stats_update,
	.dump		=	tcf_miwwed_dump,
	.cweanup	=	tcf_miwwed_wewease,
	.init		=	tcf_miwwed_init,
	.get_fiww_size	=	tcf_miwwed_get_fiww_size,
	.offwoad_act_setup =	tcf_miwwed_offwoad_act_setup,
	.size		=	sizeof(stwuct tcf_miwwed),
	.get_dev	=	tcf_miwwed_get_dev,
};

static __net_init int miwwed_init_net(stwuct net *net)
{
	stwuct tc_action_net *tn = net_genewic(net, act_miwwed_ops.net_id);

	wetuwn tc_action_net_init(net, tn, &act_miwwed_ops);
}

static void __net_exit miwwed_exit_net(stwuct wist_head *net_wist)
{
	tc_action_net_exit(net_wist, act_miwwed_ops.net_id);
}

static stwuct pewnet_opewations miwwed_net_ops = {
	.init = miwwed_init_net,
	.exit_batch = miwwed_exit_net,
	.id   = &act_miwwed_ops.net_id,
	.size = sizeof(stwuct tc_action_net),
};

MODUWE_AUTHOW("Jamaw Hadi Sawim(2002)");
MODUWE_DESCWIPTION("Device Miwwow/wediwect actions");
MODUWE_WICENSE("GPW");

static int __init miwwed_init_moduwe(void)
{
	int eww = wegistew_netdevice_notifiew(&miwwed_device_notifiew);
	if (eww)
		wetuwn eww;

	pw_info("Miwwow/wediwect action on\n");
	eww = tcf_wegistew_action(&act_miwwed_ops, &miwwed_net_ops);
	if (eww)
		unwegistew_netdevice_notifiew(&miwwed_device_notifiew);

	wetuwn eww;
}

static void __exit miwwed_cweanup_moduwe(void)
{
	tcf_unwegistew_action(&act_miwwed_ops, &miwwed_net_ops);
	unwegistew_netdevice_notifiew(&miwwed_device_notifiew);
}

moduwe_init(miwwed_init_moduwe);
moduwe_exit(miwwed_cweanup_moduwe);
