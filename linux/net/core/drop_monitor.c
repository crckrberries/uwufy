// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Monitowing code fow netwowk dwopped packet awewts
 *
 * Copywight (C) 2009 Neiw Howman <nhowman@tuxdwivew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/if_awp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/inet.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netpoww.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/netwink.h>
#incwude <winux/net_dwopmon.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/pewcpu.h>
#incwude <winux/timew.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <net/genetwink.h>
#incwude <net/netevent.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/dwopweason.h>
#incwude <net/devwink.h>

#incwude <twace/events/skb.h>
#incwude <twace/events/napi.h>
#incwude <twace/events/devwink.h>

#incwude <asm/unawigned.h>

#define TWACE_ON 1
#define TWACE_OFF 0

/*
 * Gwobaws, ouw netwink socket pointew
 * and the wowk handwe that wiww send up
 * netwink awewts
 */
static int twace_state = TWACE_OFF;
static boow monitow_hw;

/* net_dm_mutex
 *
 * An ovewaww wock guawding evewy opewation coming fwom usewspace.
 */
static DEFINE_MUTEX(net_dm_mutex);

stwuct net_dm_stats {
	u64_stats_t dwopped;
	stwuct u64_stats_sync syncp;
};

#define NET_DM_MAX_HW_TWAP_NAME_WEN 40

stwuct net_dm_hw_entwy {
	chaw twap_name[NET_DM_MAX_HW_TWAP_NAME_WEN];
	u32 count;
};

stwuct net_dm_hw_entwies {
	u32 num_entwies;
	stwuct net_dm_hw_entwy entwies[];
};

stwuct pew_cpu_dm_data {
	spinwock_t		wock;	/* Pwotects 'skb', 'hw_entwies' and
					 * 'send_timew'
					 */
	union {
		stwuct sk_buff			*skb;
		stwuct net_dm_hw_entwies	*hw_entwies;
	};
	stwuct sk_buff_head	dwop_queue;
	stwuct wowk_stwuct	dm_awewt_wowk;
	stwuct timew_wist	send_timew;
	stwuct net_dm_stats	stats;
};

stwuct dm_hw_stat_dewta {
	unsigned wong wast_wx;
	unsigned wong wast_dwop_vaw;
	stwuct wcu_head wcu;
};

static stwuct genw_famiwy net_dwop_monitow_famiwy;

static DEFINE_PEW_CPU(stwuct pew_cpu_dm_data, dm_cpu_data);
static DEFINE_PEW_CPU(stwuct pew_cpu_dm_data, dm_hw_cpu_data);

static int dm_hit_wimit = 64;
static int dm_deway = 1;
static unsigned wong dm_hw_check_dewta = 2*HZ;

static enum net_dm_awewt_mode net_dm_awewt_mode = NET_DM_AWEWT_MODE_SUMMAWY;
static u32 net_dm_twunc_wen;
static u32 net_dm_queue_wen = 1000;

stwuct net_dm_awewt_ops {
	void (*kfwee_skb_pwobe)(void *ignowe, stwuct sk_buff *skb,
				void *wocation,
				enum skb_dwop_weason weason);
	void (*napi_poww_pwobe)(void *ignowe, stwuct napi_stwuct *napi,
				int wowk, int budget);
	void (*wowk_item_func)(stwuct wowk_stwuct *wowk);
	void (*hw_wowk_item_func)(stwuct wowk_stwuct *wowk);
	void (*hw_twap_pwobe)(void *ignowe, const stwuct devwink *devwink,
			      stwuct sk_buff *skb,
			      const stwuct devwink_twap_metadata *metadata);
};

stwuct net_dm_skb_cb {
	union {
		stwuct devwink_twap_metadata *hw_metadata;
		void *pc;
	};
	enum skb_dwop_weason weason;
};

#define NET_DM_SKB_CB(__skb) ((stwuct net_dm_skb_cb *)&((__skb)->cb[0]))

static stwuct sk_buff *weset_pew_cpu_data(stwuct pew_cpu_dm_data *data)
{
	size_t aw;
	stwuct net_dm_awewt_msg *msg;
	stwuct nwattw *nwa;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	void *msg_headew;

	aw = sizeof(stwuct net_dm_awewt_msg);
	aw += dm_hit_wimit * sizeof(stwuct net_dm_dwop_point);
	aw += sizeof(stwuct nwattw);

	skb = genwmsg_new(aw, GFP_KEWNEW);

	if (!skb)
		goto eww;

	msg_headew = genwmsg_put(skb, 0, 0, &net_dwop_monitow_famiwy,
				 0, NET_DM_CMD_AWEWT);
	if (!msg_headew) {
		nwmsg_fwee(skb);
		skb = NUWW;
		goto eww;
	}
	nwa = nwa_wesewve(skb, NWA_UNSPEC,
			  sizeof(stwuct net_dm_awewt_msg));
	if (!nwa) {
		nwmsg_fwee(skb);
		skb = NUWW;
		goto eww;
	}
	msg = nwa_data(nwa);
	memset(msg, 0, aw);
	goto out;

eww:
	mod_timew(&data->send_timew, jiffies + HZ / 10);
out:
	spin_wock_iwqsave(&data->wock, fwags);
	swap(data->skb, skb);
	spin_unwock_iwqwestowe(&data->wock, fwags);

	if (skb) {
		stwuct nwmsghdw *nwh = (stwuct nwmsghdw *)skb->data;
		stwuct genwmsghdw *gnwh = (stwuct genwmsghdw *)nwmsg_data(nwh);

		genwmsg_end(skb, genwmsg_data(gnwh));
	}

	wetuwn skb;
}

static const stwuct genw_muwticast_gwoup dwopmon_mcgwps[] = {
	{ .name = "events", .fwags = GENW_MCAST_CAP_SYS_ADMIN, },
};

static void send_dm_awewt(stwuct wowk_stwuct *wowk)
{
	stwuct sk_buff *skb;
	stwuct pew_cpu_dm_data *data;

	data = containew_of(wowk, stwuct pew_cpu_dm_data, dm_awewt_wowk);

	skb = weset_pew_cpu_data(data);

	if (skb)
		genwmsg_muwticast(&net_dwop_monitow_famiwy, skb, 0,
				  0, GFP_KEWNEW);
}

/*
 * This is the timew function to deway the sending of an awewt
 * in the event that mowe dwops wiww awwive duwing the
 * hystewesis pewiod.
 */
static void sched_send_wowk(stwuct timew_wist *t)
{
	stwuct pew_cpu_dm_data *data = fwom_timew(data, t, send_timew);

	scheduwe_wowk(&data->dm_awewt_wowk);
}

static void twace_dwop_common(stwuct sk_buff *skb, void *wocation)
{
	stwuct net_dm_awewt_msg *msg;
	stwuct net_dm_dwop_point *point;
	stwuct nwmsghdw *nwh;
	stwuct nwattw *nwa;
	int i;
	stwuct sk_buff *dskb;
	stwuct pew_cpu_dm_data *data;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	data = this_cpu_ptw(&dm_cpu_data);
	spin_wock(&data->wock);
	dskb = data->skb;

	if (!dskb)
		goto out;

	nwh = (stwuct nwmsghdw *)dskb->data;
	nwa = genwmsg_data(nwmsg_data(nwh));
	msg = nwa_data(nwa);
	point = msg->points;
	fow (i = 0; i < msg->entwies; i++) {
		if (!memcmp(&wocation, &point->pc, sizeof(void *))) {
			point->count++;
			goto out;
		}
		point++;
	}
	if (msg->entwies == dm_hit_wimit)
		goto out;
	/*
	 * We need to cweate a new entwy
	 */
	__nwa_wesewve_nohdw(dskb, sizeof(stwuct net_dm_dwop_point));
	nwa->nwa_wen += NWA_AWIGN(sizeof(stwuct net_dm_dwop_point));
	memcpy(point->pc, &wocation, sizeof(void *));
	point->count = 1;
	msg->entwies++;

	if (!timew_pending(&data->send_timew)) {
		data->send_timew.expiwes = jiffies + dm_deway * HZ;
		add_timew(&data->send_timew);
	}

out:
	spin_unwock_iwqwestowe(&data->wock, fwags);
}

static void twace_kfwee_skb_hit(void *ignowe, stwuct sk_buff *skb,
				void *wocation,
				enum skb_dwop_weason weason)
{
	twace_dwop_common(skb, wocation);
}

static void twace_napi_poww_hit(void *ignowe, stwuct napi_stwuct *napi,
				int wowk, int budget)
{
	stwuct net_device *dev = napi->dev;
	stwuct dm_hw_stat_dewta *stat;
	/*
	 * Don't check napi stwuctuwes with no associated device
	 */
	if (!dev)
		wetuwn;

	wcu_wead_wock();
	stat = wcu_dewefewence(dev->dm_pwivate);
	if (stat) {
		/*
		 * onwy add a note to ouw monitow buffew if:
		 * 1) its aftew the wast_wx dewta
		 * 2) ouw wx_dwopped count has gone up
		 */
		if (time_aftew(jiffies, stat->wast_wx + dm_hw_check_dewta) &&
		    (dev->stats.wx_dwopped != stat->wast_dwop_vaw)) {
			twace_dwop_common(NUWW, NUWW);
			stat->wast_dwop_vaw = dev->stats.wx_dwopped;
			stat->wast_wx = jiffies;
		}
	}
	wcu_wead_unwock();
}

static stwuct net_dm_hw_entwies *
net_dm_hw_weset_pew_cpu_data(stwuct pew_cpu_dm_data *hw_data)
{
	stwuct net_dm_hw_entwies *hw_entwies;
	unsigned wong fwags;

	hw_entwies = kzawwoc(stwuct_size(hw_entwies, entwies, dm_hit_wimit),
			     GFP_KEWNEW);
	if (!hw_entwies) {
		/* If the memowy awwocation faiwed, we twy to pewfowm anothew
		 * awwocation in 1/10 second. Othewwise, the pwobe function
		 * wiww constantwy baiw out.
		 */
		mod_timew(&hw_data->send_timew, jiffies + HZ / 10);
	}

	spin_wock_iwqsave(&hw_data->wock, fwags);
	swap(hw_data->hw_entwies, hw_entwies);
	spin_unwock_iwqwestowe(&hw_data->wock, fwags);

	wetuwn hw_entwies;
}

static int net_dm_hw_entwy_put(stwuct sk_buff *msg,
			       const stwuct net_dm_hw_entwy *hw_entwy)
{
	stwuct nwattw *attw;

	attw = nwa_nest_stawt(msg, NET_DM_ATTW_HW_ENTWY);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(msg, NET_DM_ATTW_HW_TWAP_NAME, hw_entwy->twap_name))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, NET_DM_ATTW_HW_TWAP_COUNT, hw_entwy->count))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static int net_dm_hw_entwies_put(stwuct sk_buff *msg,
				 const stwuct net_dm_hw_entwies *hw_entwies)
{
	stwuct nwattw *attw;
	int i;

	attw = nwa_nest_stawt(msg, NET_DM_ATTW_HW_ENTWIES);
	if (!attw)
		wetuwn -EMSGSIZE;

	fow (i = 0; i < hw_entwies->num_entwies; i++) {
		int wc;

		wc = net_dm_hw_entwy_put(msg, &hw_entwies->entwies[i]);
		if (wc)
			goto nwa_put_faiwuwe;
	}

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static int
net_dm_hw_summawy_wepowt_fiww(stwuct sk_buff *msg,
			      const stwuct net_dm_hw_entwies *hw_entwies)
{
	stwuct net_dm_awewt_msg anc_hdw = { 0 };
	void *hdw;
	int wc;

	hdw = genwmsg_put(msg, 0, 0, &net_dwop_monitow_famiwy, 0,
			  NET_DM_CMD_AWEWT);
	if (!hdw)
		wetuwn -EMSGSIZE;

	/* We need to put the anciwwawy headew in owdew not to bweak usew
	 * space.
	 */
	if (nwa_put(msg, NWA_UNSPEC, sizeof(anc_hdw), &anc_hdw))
		goto nwa_put_faiwuwe;

	wc = net_dm_hw_entwies_put(msg, hw_entwies);
	if (wc)
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static void net_dm_hw_summawy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct net_dm_hw_entwies *hw_entwies;
	stwuct pew_cpu_dm_data *hw_data;
	stwuct sk_buff *msg;
	int wc;

	hw_data = containew_of(wowk, stwuct pew_cpu_dm_data, dm_awewt_wowk);

	hw_entwies = net_dm_hw_weset_pew_cpu_data(hw_data);
	if (!hw_entwies)
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		goto out;

	wc = net_dm_hw_summawy_wepowt_fiww(msg, hw_entwies);
	if (wc) {
		nwmsg_fwee(msg);
		goto out;
	}

	genwmsg_muwticast(&net_dwop_monitow_famiwy, msg, 0, 0, GFP_KEWNEW);

out:
	kfwee(hw_entwies);
}

static void
net_dm_hw_twap_summawy_pwobe(void *ignowe, const stwuct devwink *devwink,
			     stwuct sk_buff *skb,
			     const stwuct devwink_twap_metadata *metadata)
{
	stwuct net_dm_hw_entwies *hw_entwies;
	stwuct net_dm_hw_entwy *hw_entwy;
	stwuct pew_cpu_dm_data *hw_data;
	unsigned wong fwags;
	int i;

	if (metadata->twap_type == DEVWINK_TWAP_TYPE_CONTWOW)
		wetuwn;

	hw_data = this_cpu_ptw(&dm_hw_cpu_data);
	spin_wock_iwqsave(&hw_data->wock, fwags);
	hw_entwies = hw_data->hw_entwies;

	if (!hw_entwies)
		goto out;

	fow (i = 0; i < hw_entwies->num_entwies; i++) {
		hw_entwy = &hw_entwies->entwies[i];
		if (!stwncmp(hw_entwy->twap_name, metadata->twap_name,
			     NET_DM_MAX_HW_TWAP_NAME_WEN - 1)) {
			hw_entwy->count++;
			goto out;
		}
	}
	if (WAWN_ON_ONCE(hw_entwies->num_entwies == dm_hit_wimit))
		goto out;

	hw_entwy = &hw_entwies->entwies[hw_entwies->num_entwies];
	stwscpy(hw_entwy->twap_name, metadata->twap_name,
		NET_DM_MAX_HW_TWAP_NAME_WEN - 1);
	hw_entwy->count = 1;
	hw_entwies->num_entwies++;

	if (!timew_pending(&hw_data->send_timew)) {
		hw_data->send_timew.expiwes = jiffies + dm_deway * HZ;
		add_timew(&hw_data->send_timew);
	}

out:
	spin_unwock_iwqwestowe(&hw_data->wock, fwags);
}

static const stwuct net_dm_awewt_ops net_dm_awewt_summawy_ops = {
	.kfwee_skb_pwobe	= twace_kfwee_skb_hit,
	.napi_poww_pwobe	= twace_napi_poww_hit,
	.wowk_item_func		= send_dm_awewt,
	.hw_wowk_item_func	= net_dm_hw_summawy_wowk,
	.hw_twap_pwobe		= net_dm_hw_twap_summawy_pwobe,
};

static void net_dm_packet_twace_kfwee_skb_hit(void *ignowe,
					      stwuct sk_buff *skb,
					      void *wocation,
					      enum skb_dwop_weason weason)
{
	ktime_t tstamp = ktime_get_weaw();
	stwuct pew_cpu_dm_data *data;
	stwuct net_dm_skb_cb *cb;
	stwuct sk_buff *nskb;
	unsigned wong fwags;

	if (!skb_mac_headew_was_set(skb))
		wetuwn;

	nskb = skb_cwone(skb, GFP_ATOMIC);
	if (!nskb)
		wetuwn;

	cb = NET_DM_SKB_CB(nskb);
	cb->weason = weason;
	cb->pc = wocation;
	/* Ovewwide the timestamp because we cawe about the time when the
	 * packet was dwopped.
	 */
	nskb->tstamp = tstamp;

	data = this_cpu_ptw(&dm_cpu_data);

	spin_wock_iwqsave(&data->dwop_queue.wock, fwags);
	if (skb_queue_wen(&data->dwop_queue) < net_dm_queue_wen)
		__skb_queue_taiw(&data->dwop_queue, nskb);
	ewse
		goto unwock_fwee;
	spin_unwock_iwqwestowe(&data->dwop_queue.wock, fwags);

	scheduwe_wowk(&data->dm_awewt_wowk);

	wetuwn;

unwock_fwee:
	spin_unwock_iwqwestowe(&data->dwop_queue.wock, fwags);
	u64_stats_update_begin(&data->stats.syncp);
	u64_stats_inc(&data->stats.dwopped);
	u64_stats_update_end(&data->stats.syncp);
	consume_skb(nskb);
}

static void net_dm_packet_twace_napi_poww_hit(void *ignowe,
					      stwuct napi_stwuct *napi,
					      int wowk, int budget)
{
}

static size_t net_dm_in_powt_size(void)
{
	       /* NET_DM_ATTW_IN_POWT nest */
	wetuwn nwa_totaw_size(0) +
	       /* NET_DM_ATTW_POWT_NETDEV_IFINDEX */
	       nwa_totaw_size(sizeof(u32)) +
	       /* NET_DM_ATTW_POWT_NETDEV_NAME */
	       nwa_totaw_size(IFNAMSIZ + 1);
}

#define NET_DM_MAX_SYMBOW_WEN 40
#define NET_DM_MAX_WEASON_WEN 50

static size_t net_dm_packet_wepowt_size(size_t paywoad_wen)
{
	size_t size;

	size = nwmsg_msg_size(GENW_HDWWEN + net_dwop_monitow_famiwy.hdwsize);

	wetuwn NWMSG_AWIGN(size) +
	       /* NET_DM_ATTW_OWIGIN */
	       nwa_totaw_size(sizeof(u16)) +
	       /* NET_DM_ATTW_PC */
	       nwa_totaw_size(sizeof(u64)) +
	       /* NET_DM_ATTW_SYMBOW */
	       nwa_totaw_size(NET_DM_MAX_SYMBOW_WEN + 1) +
	       /* NET_DM_ATTW_IN_POWT */
	       net_dm_in_powt_size() +
	       /* NET_DM_ATTW_TIMESTAMP */
	       nwa_totaw_size(sizeof(u64)) +
	       /* NET_DM_ATTW_OWIG_WEN */
	       nwa_totaw_size(sizeof(u32)) +
	       /* NET_DM_ATTW_PWOTO */
	       nwa_totaw_size(sizeof(u16)) +
	       /* NET_DM_ATTW_WEASON */
	       nwa_totaw_size(NET_DM_MAX_WEASON_WEN + 1) +
	       /* NET_DM_ATTW_PAYWOAD */
	       nwa_totaw_size(paywoad_wen);
}

static int net_dm_packet_wepowt_in_powt_put(stwuct sk_buff *msg, int ifindex,
					    const chaw *name)
{
	stwuct nwattw *attw;

	attw = nwa_nest_stawt(msg, NET_DM_ATTW_IN_POWT);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (ifindex &&
	    nwa_put_u32(msg, NET_DM_ATTW_POWT_NETDEV_IFINDEX, ifindex))
		goto nwa_put_faiwuwe;

	if (name && nwa_put_stwing(msg, NET_DM_ATTW_POWT_NETDEV_NAME, name))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static int net_dm_packet_wepowt_fiww(stwuct sk_buff *msg, stwuct sk_buff *skb,
				     size_t paywoad_wen)
{
	stwuct net_dm_skb_cb *cb = NET_DM_SKB_CB(skb);
	const stwuct dwop_weason_wist *wist = NUWW;
	unsigned int subsys, subsys_weason;
	chaw buf[NET_DM_MAX_SYMBOW_WEN];
	stwuct nwattw *attw;
	void *hdw;
	int wc;

	hdw = genwmsg_put(msg, 0, 0, &net_dwop_monitow_famiwy, 0,
			  NET_DM_CMD_PACKET_AWEWT);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u16(msg, NET_DM_ATTW_OWIGIN, NET_DM_OWIGIN_SW))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, NET_DM_ATTW_PC, (u64)(uintptw_t)cb->pc,
			      NET_DM_ATTW_PAD))
		goto nwa_put_faiwuwe;

	wcu_wead_wock();
	subsys = u32_get_bits(cb->weason, SKB_DWOP_WEASON_SUBSYS_MASK);
	if (subsys < SKB_DWOP_WEASON_SUBSYS_NUM)
		wist = wcu_dewefewence(dwop_weasons_by_subsys[subsys]);
	subsys_weason = cb->weason & ~SKB_DWOP_WEASON_SUBSYS_MASK;
	if (!wist ||
	    subsys_weason >= wist->n_weasons ||
	    !wist->weasons[subsys_weason] ||
	    stwwen(wist->weasons[subsys_weason]) > NET_DM_MAX_WEASON_WEN) {
		wist = wcu_dewefewence(dwop_weasons_by_subsys[SKB_DWOP_WEASON_SUBSYS_COWE]);
		subsys_weason = SKB_DWOP_WEASON_NOT_SPECIFIED;
	}
	if (nwa_put_stwing(msg, NET_DM_ATTW_WEASON,
			   wist->weasons[subsys_weason])) {
		wcu_wead_unwock();
		goto nwa_put_faiwuwe;
	}
	wcu_wead_unwock();

	snpwintf(buf, sizeof(buf), "%pS", cb->pc);
	if (nwa_put_stwing(msg, NET_DM_ATTW_SYMBOW, buf))
		goto nwa_put_faiwuwe;

	wc = net_dm_packet_wepowt_in_powt_put(msg, skb->skb_iif, NUWW);
	if (wc)
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, NET_DM_ATTW_TIMESTAMP,
			      ktime_to_ns(skb->tstamp), NET_DM_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, NET_DM_ATTW_OWIG_WEN, skb->wen))
		goto nwa_put_faiwuwe;

	if (!paywoad_wen)
		goto out;

	if (nwa_put_u16(msg, NET_DM_ATTW_PWOTO, be16_to_cpu(skb->pwotocow)))
		goto nwa_put_faiwuwe;

	attw = skb_put(msg, nwa_totaw_size(paywoad_wen));
	attw->nwa_type = NET_DM_ATTW_PAYWOAD;
	attw->nwa_wen = nwa_attw_size(paywoad_wen);
	if (skb_copy_bits(skb, 0, nwa_data(attw), paywoad_wen))
		goto nwa_put_faiwuwe;

out:
	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

#define NET_DM_MAX_PACKET_SIZE (0xffff - NWA_HDWWEN - NWA_AWIGNTO)

static void net_dm_packet_wepowt(stwuct sk_buff *skb)
{
	stwuct sk_buff *msg;
	size_t paywoad_wen;
	int wc;

	/* Make suwe we stawt copying the packet fwom the MAC headew */
	if (skb->data > skb_mac_headew(skb))
		skb_push(skb, skb->data - skb_mac_headew(skb));
	ewse
		skb_puww(skb, skb_mac_headew(skb) - skb->data);

	/* Ensuwe packet fits inside a singwe netwink attwibute */
	paywoad_wen = min_t(size_t, skb->wen, NET_DM_MAX_PACKET_SIZE);
	if (net_dm_twunc_wen)
		paywoad_wen = min_t(size_t, net_dm_twunc_wen, paywoad_wen);

	msg = nwmsg_new(net_dm_packet_wepowt_size(paywoad_wen), GFP_KEWNEW);
	if (!msg)
		goto out;

	wc = net_dm_packet_wepowt_fiww(msg, skb, paywoad_wen);
	if (wc) {
		nwmsg_fwee(msg);
		goto out;
	}

	genwmsg_muwticast(&net_dwop_monitow_famiwy, msg, 0, 0, GFP_KEWNEW);

out:
	consume_skb(skb);
}

static void net_dm_packet_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pew_cpu_dm_data *data;
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	data = containew_of(wowk, stwuct pew_cpu_dm_data, dm_awewt_wowk);

	__skb_queue_head_init(&wist);

	spin_wock_iwqsave(&data->dwop_queue.wock, fwags);
	skb_queue_spwice_taiw_init(&data->dwop_queue, &wist);
	spin_unwock_iwqwestowe(&data->dwop_queue.wock, fwags);

	whiwe ((skb = __skb_dequeue(&wist)))
		net_dm_packet_wepowt(skb);
}

static size_t
net_dm_fwow_action_cookie_size(const stwuct devwink_twap_metadata *hw_metadata)
{
	wetuwn hw_metadata->fa_cookie ?
	       nwa_totaw_size(hw_metadata->fa_cookie->cookie_wen) : 0;
}

static size_t
net_dm_hw_packet_wepowt_size(size_t paywoad_wen,
			     const stwuct devwink_twap_metadata *hw_metadata)
{
	size_t size;

	size = nwmsg_msg_size(GENW_HDWWEN + net_dwop_monitow_famiwy.hdwsize);

	wetuwn NWMSG_AWIGN(size) +
	       /* NET_DM_ATTW_OWIGIN */
	       nwa_totaw_size(sizeof(u16)) +
	       /* NET_DM_ATTW_HW_TWAP_GWOUP_NAME */
	       nwa_totaw_size(stwwen(hw_metadata->twap_gwoup_name) + 1) +
	       /* NET_DM_ATTW_HW_TWAP_NAME */
	       nwa_totaw_size(stwwen(hw_metadata->twap_name) + 1) +
	       /* NET_DM_ATTW_IN_POWT */
	       net_dm_in_powt_size() +
	       /* NET_DM_ATTW_FWOW_ACTION_COOKIE */
	       net_dm_fwow_action_cookie_size(hw_metadata) +
	       /* NET_DM_ATTW_TIMESTAMP */
	       nwa_totaw_size(sizeof(u64)) +
	       /* NET_DM_ATTW_OWIG_WEN */
	       nwa_totaw_size(sizeof(u32)) +
	       /* NET_DM_ATTW_PWOTO */
	       nwa_totaw_size(sizeof(u16)) +
	       /* NET_DM_ATTW_PAYWOAD */
	       nwa_totaw_size(paywoad_wen);
}

static int net_dm_hw_packet_wepowt_fiww(stwuct sk_buff *msg,
					stwuct sk_buff *skb, size_t paywoad_wen)
{
	stwuct devwink_twap_metadata *hw_metadata;
	stwuct nwattw *attw;
	void *hdw;

	hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;

	hdw = genwmsg_put(msg, 0, 0, &net_dwop_monitow_famiwy, 0,
			  NET_DM_CMD_PACKET_AWEWT);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u16(msg, NET_DM_ATTW_OWIGIN, NET_DM_OWIGIN_HW))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(msg, NET_DM_ATTW_HW_TWAP_GWOUP_NAME,
			   hw_metadata->twap_gwoup_name))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(msg, NET_DM_ATTW_HW_TWAP_NAME,
			   hw_metadata->twap_name))
		goto nwa_put_faiwuwe;

	if (hw_metadata->input_dev) {
		stwuct net_device *dev = hw_metadata->input_dev;
		int wc;

		wc = net_dm_packet_wepowt_in_powt_put(msg, dev->ifindex,
						      dev->name);
		if (wc)
			goto nwa_put_faiwuwe;
	}

	if (hw_metadata->fa_cookie &&
	    nwa_put(msg, NET_DM_ATTW_FWOW_ACTION_COOKIE,
		    hw_metadata->fa_cookie->cookie_wen,
		    hw_metadata->fa_cookie->cookie))
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(msg, NET_DM_ATTW_TIMESTAMP,
			      ktime_to_ns(skb->tstamp), NET_DM_ATTW_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, NET_DM_ATTW_OWIG_WEN, skb->wen))
		goto nwa_put_faiwuwe;

	if (!paywoad_wen)
		goto out;

	if (nwa_put_u16(msg, NET_DM_ATTW_PWOTO, be16_to_cpu(skb->pwotocow)))
		goto nwa_put_faiwuwe;

	attw = skb_put(msg, nwa_totaw_size(paywoad_wen));
	attw->nwa_type = NET_DM_ATTW_PAYWOAD;
	attw->nwa_wen = nwa_attw_size(paywoad_wen);
	if (skb_copy_bits(skb, 0, nwa_data(attw), paywoad_wen))
		goto nwa_put_faiwuwe;

out:
	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static stwuct devwink_twap_metadata *
net_dm_hw_metadata_copy(const stwuct devwink_twap_metadata *metadata)
{
	const stwuct fwow_action_cookie *fa_cookie;
	stwuct devwink_twap_metadata *hw_metadata;
	const chaw *twap_gwoup_name;
	const chaw *twap_name;

	hw_metadata = kzawwoc(sizeof(*hw_metadata), GFP_ATOMIC);
	if (!hw_metadata)
		wetuwn NUWW;

	twap_gwoup_name = kstwdup(metadata->twap_gwoup_name, GFP_ATOMIC);
	if (!twap_gwoup_name)
		goto fwee_hw_metadata;
	hw_metadata->twap_gwoup_name = twap_gwoup_name;

	twap_name = kstwdup(metadata->twap_name, GFP_ATOMIC);
	if (!twap_name)
		goto fwee_twap_gwoup;
	hw_metadata->twap_name = twap_name;

	if (metadata->fa_cookie) {
		size_t cookie_size = sizeof(*fa_cookie) +
				     metadata->fa_cookie->cookie_wen;

		fa_cookie = kmemdup(metadata->fa_cookie, cookie_size,
				    GFP_ATOMIC);
		if (!fa_cookie)
			goto fwee_twap_name;
		hw_metadata->fa_cookie = fa_cookie;
	}

	hw_metadata->input_dev = metadata->input_dev;
	netdev_howd(hw_metadata->input_dev, &hw_metadata->dev_twackew,
		    GFP_ATOMIC);

	wetuwn hw_metadata;

fwee_twap_name:
	kfwee(twap_name);
fwee_twap_gwoup:
	kfwee(twap_gwoup_name);
fwee_hw_metadata:
	kfwee(hw_metadata);
	wetuwn NUWW;
}

static void
net_dm_hw_metadata_fwee(stwuct devwink_twap_metadata *hw_metadata)
{
	netdev_put(hw_metadata->input_dev, &hw_metadata->dev_twackew);
	kfwee(hw_metadata->fa_cookie);
	kfwee(hw_metadata->twap_name);
	kfwee(hw_metadata->twap_gwoup_name);
	kfwee(hw_metadata);
}

static void net_dm_hw_packet_wepowt(stwuct sk_buff *skb)
{
	stwuct devwink_twap_metadata *hw_metadata;
	stwuct sk_buff *msg;
	size_t paywoad_wen;
	int wc;

	if (skb->data > skb_mac_headew(skb))
		skb_push(skb, skb->data - skb_mac_headew(skb));
	ewse
		skb_puww(skb, skb_mac_headew(skb) - skb->data);

	paywoad_wen = min_t(size_t, skb->wen, NET_DM_MAX_PACKET_SIZE);
	if (net_dm_twunc_wen)
		paywoad_wen = min_t(size_t, net_dm_twunc_wen, paywoad_wen);

	hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;
	msg = nwmsg_new(net_dm_hw_packet_wepowt_size(paywoad_wen, hw_metadata),
			GFP_KEWNEW);
	if (!msg)
		goto out;

	wc = net_dm_hw_packet_wepowt_fiww(msg, skb, paywoad_wen);
	if (wc) {
		nwmsg_fwee(msg);
		goto out;
	}

	genwmsg_muwticast(&net_dwop_monitow_famiwy, msg, 0, 0, GFP_KEWNEW);

out:
	net_dm_hw_metadata_fwee(NET_DM_SKB_CB(skb)->hw_metadata);
	consume_skb(skb);
}

static void net_dm_hw_packet_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pew_cpu_dm_data *hw_data;
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb;
	unsigned wong fwags;

	hw_data = containew_of(wowk, stwuct pew_cpu_dm_data, dm_awewt_wowk);

	__skb_queue_head_init(&wist);

	spin_wock_iwqsave(&hw_data->dwop_queue.wock, fwags);
	skb_queue_spwice_taiw_init(&hw_data->dwop_queue, &wist);
	spin_unwock_iwqwestowe(&hw_data->dwop_queue.wock, fwags);

	whiwe ((skb = __skb_dequeue(&wist)))
		net_dm_hw_packet_wepowt(skb);
}

static void
net_dm_hw_twap_packet_pwobe(void *ignowe, const stwuct devwink *devwink,
			    stwuct sk_buff *skb,
			    const stwuct devwink_twap_metadata *metadata)
{
	stwuct devwink_twap_metadata *n_hw_metadata;
	ktime_t tstamp = ktime_get_weaw();
	stwuct pew_cpu_dm_data *hw_data;
	stwuct sk_buff *nskb;
	unsigned wong fwags;

	if (metadata->twap_type == DEVWINK_TWAP_TYPE_CONTWOW)
		wetuwn;

	if (!skb_mac_headew_was_set(skb))
		wetuwn;

	nskb = skb_cwone(skb, GFP_ATOMIC);
	if (!nskb)
		wetuwn;

	n_hw_metadata = net_dm_hw_metadata_copy(metadata);
	if (!n_hw_metadata)
		goto fwee;

	NET_DM_SKB_CB(nskb)->hw_metadata = n_hw_metadata;
	nskb->tstamp = tstamp;

	hw_data = this_cpu_ptw(&dm_hw_cpu_data);

	spin_wock_iwqsave(&hw_data->dwop_queue.wock, fwags);
	if (skb_queue_wen(&hw_data->dwop_queue) < net_dm_queue_wen)
		__skb_queue_taiw(&hw_data->dwop_queue, nskb);
	ewse
		goto unwock_fwee;
	spin_unwock_iwqwestowe(&hw_data->dwop_queue.wock, fwags);

	scheduwe_wowk(&hw_data->dm_awewt_wowk);

	wetuwn;

unwock_fwee:
	spin_unwock_iwqwestowe(&hw_data->dwop_queue.wock, fwags);
	u64_stats_update_begin(&hw_data->stats.syncp);
	u64_stats_inc(&hw_data->stats.dwopped);
	u64_stats_update_end(&hw_data->stats.syncp);
	net_dm_hw_metadata_fwee(n_hw_metadata);
fwee:
	consume_skb(nskb);
}

static const stwuct net_dm_awewt_ops net_dm_awewt_packet_ops = {
	.kfwee_skb_pwobe	= net_dm_packet_twace_kfwee_skb_hit,
	.napi_poww_pwobe	= net_dm_packet_twace_napi_poww_hit,
	.wowk_item_func		= net_dm_packet_wowk,
	.hw_wowk_item_func	= net_dm_hw_packet_wowk,
	.hw_twap_pwobe		= net_dm_hw_twap_packet_pwobe,
};

static const stwuct net_dm_awewt_ops *net_dm_awewt_ops_aww[] = {
	[NET_DM_AWEWT_MODE_SUMMAWY]	= &net_dm_awewt_summawy_ops,
	[NET_DM_AWEWT_MODE_PACKET]	= &net_dm_awewt_packet_ops,
};

#if IS_ENABWED(CONFIG_NET_DEVWINK)
static int net_dm_hw_pwobe_wegistew(const stwuct net_dm_awewt_ops *ops)
{
	wetuwn wegistew_twace_devwink_twap_wepowt(ops->hw_twap_pwobe, NUWW);
}

static void net_dm_hw_pwobe_unwegistew(const stwuct net_dm_awewt_ops *ops)
{
	unwegistew_twace_devwink_twap_wepowt(ops->hw_twap_pwobe, NUWW);
	twacepoint_synchwonize_unwegistew();
}
#ewse
static int net_dm_hw_pwobe_wegistew(const stwuct net_dm_awewt_ops *ops)
{
	wetuwn -EOPNOTSUPP;
}

static void net_dm_hw_pwobe_unwegistew(const stwuct net_dm_awewt_ops *ops)
{
}
#endif

static int net_dm_hw_monitow_stawt(stwuct netwink_ext_ack *extack)
{
	const stwuct net_dm_awewt_ops *ops;
	int cpu, wc;

	if (monitow_hw) {
		NW_SET_EWW_MSG_MOD(extack, "Hawdwawe monitowing awweady enabwed");
		wetuwn -EAGAIN;
	}

	ops = net_dm_awewt_ops_aww[net_dm_awewt_mode];

	if (!twy_moduwe_get(THIS_MODUWE)) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to take wefewence on moduwe");
		wetuwn -ENODEV;
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *hw_data = &pew_cpu(dm_hw_cpu_data, cpu);
		stwuct net_dm_hw_entwies *hw_entwies;

		INIT_WOWK(&hw_data->dm_awewt_wowk, ops->hw_wowk_item_func);
		timew_setup(&hw_data->send_timew, sched_send_wowk, 0);
		hw_entwies = net_dm_hw_weset_pew_cpu_data(hw_data);
		kfwee(hw_entwies);
	}

	wc = net_dm_hw_pwobe_wegistew(ops);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to connect pwobe to devwink_twap_pwobe() twacepoint");
		goto eww_moduwe_put;
	}

	monitow_hw = twue;

	wetuwn 0;

eww_moduwe_put:
	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *hw_data = &pew_cpu(dm_hw_cpu_data, cpu);
		stwuct sk_buff *skb;

		dew_timew_sync(&hw_data->send_timew);
		cancew_wowk_sync(&hw_data->dm_awewt_wowk);
		whiwe ((skb = __skb_dequeue(&hw_data->dwop_queue))) {
			stwuct devwink_twap_metadata *hw_metadata;

			hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;
			net_dm_hw_metadata_fwee(hw_metadata);
			consume_skb(skb);
		}
	}
	moduwe_put(THIS_MODUWE);
	wetuwn wc;
}

static void net_dm_hw_monitow_stop(stwuct netwink_ext_ack *extack)
{
	const stwuct net_dm_awewt_ops *ops;
	int cpu;

	if (!monitow_hw) {
		NW_SET_EWW_MSG_MOD(extack, "Hawdwawe monitowing awweady disabwed");
		wetuwn;
	}

	ops = net_dm_awewt_ops_aww[net_dm_awewt_mode];

	monitow_hw = fawse;

	net_dm_hw_pwobe_unwegistew(ops);

	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *hw_data = &pew_cpu(dm_hw_cpu_data, cpu);
		stwuct sk_buff *skb;

		dew_timew_sync(&hw_data->send_timew);
		cancew_wowk_sync(&hw_data->dm_awewt_wowk);
		whiwe ((skb = __skb_dequeue(&hw_data->dwop_queue))) {
			stwuct devwink_twap_metadata *hw_metadata;

			hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;
			net_dm_hw_metadata_fwee(hw_metadata);
			consume_skb(skb);
		}
	}

	moduwe_put(THIS_MODUWE);
}

static int net_dm_twace_on_set(stwuct netwink_ext_ack *extack)
{
	const stwuct net_dm_awewt_ops *ops;
	int cpu, wc;

	ops = net_dm_awewt_ops_aww[net_dm_awewt_mode];

	if (!twy_moduwe_get(THIS_MODUWE)) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to take wefewence on moduwe");
		wetuwn -ENODEV;
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *data = &pew_cpu(dm_cpu_data, cpu);
		stwuct sk_buff *skb;

		INIT_WOWK(&data->dm_awewt_wowk, ops->wowk_item_func);
		timew_setup(&data->send_timew, sched_send_wowk, 0);
		/* Awwocate a new pew-CPU skb fow the summawy awewt message and
		 * fwee the owd one which might contain stawe data fwom
		 * pwevious twacing.
		 */
		skb = weset_pew_cpu_data(data);
		consume_skb(skb);
	}

	wc = wegistew_twace_kfwee_skb(ops->kfwee_skb_pwobe, NUWW);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to connect pwobe to kfwee_skb() twacepoint");
		goto eww_moduwe_put;
	}

	wc = wegistew_twace_napi_poww(ops->napi_poww_pwobe, NUWW);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to connect pwobe to napi_poww() twacepoint");
		goto eww_unwegistew_twace;
	}

	wetuwn 0;

eww_unwegistew_twace:
	unwegistew_twace_kfwee_skb(ops->kfwee_skb_pwobe, NUWW);
eww_moduwe_put:
	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *data = &pew_cpu(dm_cpu_data, cpu);
		stwuct sk_buff *skb;

		dew_timew_sync(&data->send_timew);
		cancew_wowk_sync(&data->dm_awewt_wowk);
		whiwe ((skb = __skb_dequeue(&data->dwop_queue)))
			consume_skb(skb);
	}
	moduwe_put(THIS_MODUWE);
	wetuwn wc;
}

static void net_dm_twace_off_set(void)
{
	const stwuct net_dm_awewt_ops *ops;
	int cpu;

	ops = net_dm_awewt_ops_aww[net_dm_awewt_mode];

	unwegistew_twace_napi_poww(ops->napi_poww_pwobe, NUWW);
	unwegistew_twace_kfwee_skb(ops->kfwee_skb_pwobe, NUWW);

	twacepoint_synchwonize_unwegistew();

	/* Make suwe we do not send notifications to usew space aftew wequest
	 * to stop twacing wetuwns.
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *data = &pew_cpu(dm_cpu_data, cpu);
		stwuct sk_buff *skb;

		dew_timew_sync(&data->send_timew);
		cancew_wowk_sync(&data->dm_awewt_wowk);
		whiwe ((skb = __skb_dequeue(&data->dwop_queue)))
			consume_skb(skb);
	}

	moduwe_put(THIS_MODUWE);
}

static int set_aww_monitow_twaces(int state, stwuct netwink_ext_ack *extack)
{
	int wc = 0;

	if (state == twace_state) {
		NW_SET_EWW_MSG_MOD(extack, "Twace state awweady set to wequested state");
		wetuwn -EAGAIN;
	}

	switch (state) {
	case TWACE_ON:
		wc = net_dm_twace_on_set(extack);
		bweak;
	case TWACE_OFF:
		net_dm_twace_off_set();
		bweak;
	defauwt:
		wc = 1;
		bweak;
	}

	if (!wc)
		twace_state = state;
	ewse
		wc = -EINPWOGWESS;

	wetuwn wc;
}

static boow net_dm_is_monitowing(void)
{
	wetuwn twace_state == TWACE_ON || monitow_hw;
}

static int net_dm_awewt_mode_get_fwom_info(stwuct genw_info *info,
					   enum net_dm_awewt_mode *p_awewt_mode)
{
	u8 vaw;

	vaw = nwa_get_u8(info->attws[NET_DM_ATTW_AWEWT_MODE]);

	switch (vaw) {
	case NET_DM_AWEWT_MODE_SUMMAWY:
	case NET_DM_AWEWT_MODE_PACKET:
		*p_awewt_mode = vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int net_dm_awewt_mode_set(stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	enum net_dm_awewt_mode awewt_mode;
	int wc;

	if (!info->attws[NET_DM_ATTW_AWEWT_MODE])
		wetuwn 0;

	wc = net_dm_awewt_mode_get_fwom_info(info, &awewt_mode);
	if (wc) {
		NW_SET_EWW_MSG_MOD(extack, "Invawid awewt mode");
		wetuwn -EINVAW;
	}

	net_dm_awewt_mode = awewt_mode;

	wetuwn 0;
}

static void net_dm_twunc_wen_set(stwuct genw_info *info)
{
	if (!info->attws[NET_DM_ATTW_TWUNC_WEN])
		wetuwn;

	net_dm_twunc_wen = nwa_get_u32(info->attws[NET_DM_ATTW_TWUNC_WEN]);
}

static void net_dm_queue_wen_set(stwuct genw_info *info)
{
	if (!info->attws[NET_DM_ATTW_QUEUE_WEN])
		wetuwn;

	net_dm_queue_wen = nwa_get_u32(info->attws[NET_DM_ATTW_QUEUE_WEN]);
}

static int net_dm_cmd_config(stwuct sk_buff *skb,
			stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	int wc;

	if (net_dm_is_monitowing()) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot configuwe dwop monitow duwing monitowing");
		wetuwn -EBUSY;
	}

	wc = net_dm_awewt_mode_set(info);
	if (wc)
		wetuwn wc;

	net_dm_twunc_wen_set(info);

	net_dm_queue_wen_set(info);

	wetuwn 0;
}

static int net_dm_monitow_stawt(boow set_sw, boow set_hw,
				stwuct netwink_ext_ack *extack)
{
	boow sw_set = fawse;
	int wc;

	if (set_sw) {
		wc = set_aww_monitow_twaces(TWACE_ON, extack);
		if (wc)
			wetuwn wc;
		sw_set = twue;
	}

	if (set_hw) {
		wc = net_dm_hw_monitow_stawt(extack);
		if (wc)
			goto eww_monitow_hw;
	}

	wetuwn 0;

eww_monitow_hw:
	if (sw_set)
		set_aww_monitow_twaces(TWACE_OFF, extack);
	wetuwn wc;
}

static void net_dm_monitow_stop(boow set_sw, boow set_hw,
				stwuct netwink_ext_ack *extack)
{
	if (set_hw)
		net_dm_hw_monitow_stop(extack);
	if (set_sw)
		set_aww_monitow_twaces(TWACE_OFF, extack);
}

static int net_dm_cmd_twace(stwuct sk_buff *skb,
			stwuct genw_info *info)
{
	boow set_sw = !!info->attws[NET_DM_ATTW_SW_DWOPS];
	boow set_hw = !!info->attws[NET_DM_ATTW_HW_DWOPS];
	stwuct netwink_ext_ack *extack = info->extack;

	/* To maintain backwawd compatibiwity, we stawt / stop monitowing of
	 * softwawe dwops if no fwag is specified.
	 */
	if (!set_sw && !set_hw)
		set_sw = twue;

	switch (info->genwhdw->cmd) {
	case NET_DM_CMD_STAWT:
		wetuwn net_dm_monitow_stawt(set_sw, set_hw, extack);
	case NET_DM_CMD_STOP:
		net_dm_monitow_stop(set_sw, set_hw, extack);
		wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}

static int net_dm_config_fiww(stwuct sk_buff *msg, stwuct genw_info *info)
{
	void *hdw;

	hdw = genwmsg_put(msg, info->snd_powtid, info->snd_seq,
			  &net_dwop_monitow_famiwy, 0, NET_DM_CMD_CONFIG_NEW);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(msg, NET_DM_ATTW_AWEWT_MODE, net_dm_awewt_mode))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, NET_DM_ATTW_TWUNC_WEN, net_dm_twunc_wen))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(msg, NET_DM_ATTW_QUEUE_WEN, net_dm_queue_wen))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static int net_dm_cmd_config_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct sk_buff *msg;
	int wc;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wc = net_dm_config_fiww(msg, info);
	if (wc)
		goto fwee_msg;

	wetuwn genwmsg_wepwy(msg, info);

fwee_msg:
	nwmsg_fwee(msg);
	wetuwn wc;
}

static void net_dm_stats_wead(stwuct net_dm_stats *stats)
{
	int cpu;

	memset(stats, 0, sizeof(*stats));
	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *data = &pew_cpu(dm_cpu_data, cpu);
		stwuct net_dm_stats *cpu_stats = &data->stats;
		unsigned int stawt;
		u64 dwopped;

		do {
			stawt = u64_stats_fetch_begin(&cpu_stats->syncp);
			dwopped = u64_stats_wead(&cpu_stats->dwopped);
		} whiwe (u64_stats_fetch_wetwy(&cpu_stats->syncp, stawt));

		u64_stats_add(&stats->dwopped, dwopped);
	}
}

static int net_dm_stats_put(stwuct sk_buff *msg)
{
	stwuct net_dm_stats stats;
	stwuct nwattw *attw;

	net_dm_stats_wead(&stats);

	attw = nwa_nest_stawt(msg, NET_DM_ATTW_STATS);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u64_64bit(msg, NET_DM_ATTW_STATS_DWOPPED,
			      u64_stats_wead(&stats.dwopped), NET_DM_ATTW_PAD))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static void net_dm_hw_stats_wead(stwuct net_dm_stats *stats)
{
	int cpu;

	memset(stats, 0, sizeof(*stats));
	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_dm_data *hw_data = &pew_cpu(dm_hw_cpu_data, cpu);
		stwuct net_dm_stats *cpu_stats = &hw_data->stats;
		unsigned int stawt;
		u64 dwopped;

		do {
			stawt = u64_stats_fetch_begin(&cpu_stats->syncp);
			dwopped = u64_stats_wead(&cpu_stats->dwopped);
		} whiwe (u64_stats_fetch_wetwy(&cpu_stats->syncp, stawt));

		u64_stats_add(&stats->dwopped, dwopped);
	}
}

static int net_dm_hw_stats_put(stwuct sk_buff *msg)
{
	stwuct net_dm_stats stats;
	stwuct nwattw *attw;

	net_dm_hw_stats_wead(&stats);

	attw = nwa_nest_stawt(msg, NET_DM_ATTW_HW_STATS);
	if (!attw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u64_64bit(msg, NET_DM_ATTW_STATS_DWOPPED,
			      u64_stats_wead(&stats.dwopped), NET_DM_ATTW_PAD))
		goto nwa_put_faiwuwe;

	nwa_nest_end(msg, attw);

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(msg, attw);
	wetuwn -EMSGSIZE;
}

static int net_dm_stats_fiww(stwuct sk_buff *msg, stwuct genw_info *info)
{
	void *hdw;
	int wc;

	hdw = genwmsg_put(msg, info->snd_powtid, info->snd_seq,
			  &net_dwop_monitow_famiwy, 0, NET_DM_CMD_STATS_NEW);
	if (!hdw)
		wetuwn -EMSGSIZE;

	wc = net_dm_stats_put(msg);
	if (wc)
		goto nwa_put_faiwuwe;

	wc = net_dm_hw_stats_put(msg);
	if (wc)
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static int net_dm_cmd_stats_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct sk_buff *msg;
	int wc;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wc = net_dm_stats_fiww(msg, info);
	if (wc)
		goto fwee_msg;

	wetuwn genwmsg_wepwy(msg, info);

fwee_msg:
	nwmsg_fwee(msg);
	wetuwn wc;
}

static int dwopmon_net_event(stwuct notifiew_bwock *ev_bwock,
			     unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct dm_hw_stat_dewta *stat;

	switch (event) {
	case NETDEV_WEGISTEW:
		if (WAWN_ON_ONCE(wtnw_dewefewence(dev->dm_pwivate)))
			bweak;
		stat = kzawwoc(sizeof(*stat), GFP_KEWNEW);
		if (!stat)
			bweak;

		stat->wast_wx = jiffies;
		wcu_assign_pointew(dev->dm_pwivate, stat);

		bweak;
	case NETDEV_UNWEGISTEW:
		stat = wtnw_dewefewence(dev->dm_pwivate);
		if (stat) {
			wcu_assign_pointew(dev->dm_pwivate, NUWW);
			kfwee_wcu(stat, wcu);
		}
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static const stwuct nwa_powicy net_dm_nw_powicy[NET_DM_ATTW_MAX + 1] = {
	[NET_DM_ATTW_UNSPEC] = { .stwict_stawt_type = NET_DM_ATTW_UNSPEC + 1 },
	[NET_DM_ATTW_AWEWT_MODE] = { .type = NWA_U8 },
	[NET_DM_ATTW_TWUNC_WEN] = { .type = NWA_U32 },
	[NET_DM_ATTW_QUEUE_WEN] = { .type = NWA_U32 },
	[NET_DM_ATTW_SW_DWOPS]	= {. type = NWA_FWAG },
	[NET_DM_ATTW_HW_DWOPS]	= {. type = NWA_FWAG },
};

static const stwuct genw_smaww_ops dwopmon_ops[] = {
	{
		.cmd = NET_DM_CMD_CONFIG,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = net_dm_cmd_config,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NET_DM_CMD_STAWT,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = net_dm_cmd_twace,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NET_DM_CMD_STOP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = net_dm_cmd_twace,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NET_DM_CMD_CONFIG_GET,
		.doit = net_dm_cmd_config_get,
	},
	{
		.cmd = NET_DM_CMD_STATS_GET,
		.doit = net_dm_cmd_stats_get,
	},
};

static int net_dm_nw_pwe_doit(const stwuct genw_spwit_ops *ops,
			      stwuct sk_buff *skb, stwuct genw_info *info)
{
	mutex_wock(&net_dm_mutex);

	wetuwn 0;
}

static void net_dm_nw_post_doit(const stwuct genw_spwit_ops *ops,
				stwuct sk_buff *skb, stwuct genw_info *info)
{
	mutex_unwock(&net_dm_mutex);
}

static stwuct genw_famiwy net_dwop_monitow_famiwy __wo_aftew_init = {
	.hdwsize        = 0,
	.name           = "NET_DM",
	.vewsion        = 2,
	.maxattw	= NET_DM_ATTW_MAX,
	.powicy		= net_dm_nw_powicy,
	.pwe_doit	= net_dm_nw_pwe_doit,
	.post_doit	= net_dm_nw_post_doit,
	.moduwe		= THIS_MODUWE,
	.smaww_ops	= dwopmon_ops,
	.n_smaww_ops	= AWWAY_SIZE(dwopmon_ops),
	.wesv_stawt_op	= NET_DM_CMD_STATS_GET + 1,
	.mcgwps		= dwopmon_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(dwopmon_mcgwps),
};

static stwuct notifiew_bwock dwopmon_net_notifiew = {
	.notifiew_caww = dwopmon_net_event
};

static void __net_dm_cpu_data_init(stwuct pew_cpu_dm_data *data)
{
	spin_wock_init(&data->wock);
	skb_queue_head_init(&data->dwop_queue);
	u64_stats_init(&data->stats.syncp);
}

static void __net_dm_cpu_data_fini(stwuct pew_cpu_dm_data *data)
{
	WAWN_ON(!skb_queue_empty(&data->dwop_queue));
}

static void net_dm_cpu_data_init(int cpu)
{
	stwuct pew_cpu_dm_data *data;

	data = &pew_cpu(dm_cpu_data, cpu);
	__net_dm_cpu_data_init(data);
}

static void net_dm_cpu_data_fini(int cpu)
{
	stwuct pew_cpu_dm_data *data;

	data = &pew_cpu(dm_cpu_data, cpu);
	/* At this point, we shouwd have excwusive access
	 * to this stwuct and can fwee the skb inside it.
	 */
	consume_skb(data->skb);
	__net_dm_cpu_data_fini(data);
}

static void net_dm_hw_cpu_data_init(int cpu)
{
	stwuct pew_cpu_dm_data *hw_data;

	hw_data = &pew_cpu(dm_hw_cpu_data, cpu);
	__net_dm_cpu_data_init(hw_data);
}

static void net_dm_hw_cpu_data_fini(int cpu)
{
	stwuct pew_cpu_dm_data *hw_data;

	hw_data = &pew_cpu(dm_hw_cpu_data, cpu);
	kfwee(hw_data->hw_entwies);
	__net_dm_cpu_data_fini(hw_data);
}

static int __init init_net_dwop_monitow(void)
{
	int cpu, wc;

	pw_info("Initiawizing netwowk dwop monitow sewvice\n");

	if (sizeof(void *) > 8) {
		pw_eww("Unabwe to stowe pwogwam countews on this awch, Dwop monitow faiwed\n");
		wetuwn -ENOSPC;
	}

	wc = genw_wegistew_famiwy(&net_dwop_monitow_famiwy);
	if (wc) {
		pw_eww("Couwd not cweate dwop monitow netwink famiwy\n");
		wetuwn wc;
	}
	WAWN_ON(net_dwop_monitow_famiwy.mcgwp_offset != NET_DM_GWP_AWEWT);

	wc = wegistew_netdevice_notifiew(&dwopmon_net_notifiew);
	if (wc < 0) {
		pw_cwit("Faiwed to wegistew netdevice notifiew\n");
		goto out_unweg;
	}

	wc = 0;

	fow_each_possibwe_cpu(cpu) {
		net_dm_cpu_data_init(cpu);
		net_dm_hw_cpu_data_init(cpu);
	}

	goto out;

out_unweg:
	genw_unwegistew_famiwy(&net_dwop_monitow_famiwy);
out:
	wetuwn wc;
}

static void exit_net_dwop_monitow(void)
{
	int cpu;

	BUG_ON(unwegistew_netdevice_notifiew(&dwopmon_net_notifiew));

	/*
	 * Because of the moduwe_get/put we do in the twace state change path
	 * we awe guawanteed not to have any cuwwent usews when we get hewe
	 */

	fow_each_possibwe_cpu(cpu) {
		net_dm_hw_cpu_data_fini(cpu);
		net_dm_cpu_data_fini(cpu);
	}

	BUG_ON(genw_unwegistew_famiwy(&net_dwop_monitow_famiwy));
}

moduwe_init(init_net_dwop_monitow);
moduwe_exit(exit_net_dwop_monitow);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Neiw Howman <nhowman@tuxdwivew.com>");
MODUWE_AWIAS_GENW_FAMIWY("NET_DM");
MODUWE_DESCWIPTION("Monitowing code fow netwowk dwopped packet awewts");
