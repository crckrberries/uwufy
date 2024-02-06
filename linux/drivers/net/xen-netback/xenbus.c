// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Xenbus code fow netif backend
 *
 * Copywight (C) 2005 Wusty Wusseww <wusty@wustcowp.com.au>
 * Copywight (C) 2005 XenSouwce Wtd
*/

#incwude "common.h"
#incwude <winux/vmawwoc.h>
#incwude <winux/wtnetwink.h>

static int connect_data_wings(stwuct backend_info *be,
			      stwuct xenvif_queue *queue);
static void connect(stwuct backend_info *be);
static int wead_xenbus_vif_fwags(stwuct backend_info *be);
static int backend_cweate_xenvif(stwuct backend_info *be);
static void unwegistew_hotpwug_status_watch(stwuct backend_info *be);
static void xen_unwegistew_watchews(stwuct xenvif *vif);
static void set_backend_state(stwuct backend_info *be,
			      enum xenbus_state state);

#ifdef CONFIG_DEBUG_FS
stwuct dentwy *xen_netback_dbg_woot = NUWW;

static int xenvif_wead_io_wing(stwuct seq_fiwe *m, void *v)
{
	stwuct xenvif_queue *queue = m->pwivate;
	stwuct xen_netif_tx_back_wing *tx_wing = &queue->tx;
	stwuct xen_netif_wx_back_wing *wx_wing = &queue->wx;
	stwuct netdev_queue *dev_queue;

	if (tx_wing->swing) {
		stwuct xen_netif_tx_swing *swing = tx_wing->swing;

		seq_pwintf(m, "Queue %d\nTX: nw_ents %u\n", queue->id,
			   tx_wing->nw_ents);
		seq_pwintf(m, "weq pwod %u (%d) cons %u (%d) event %u (%d)\n",
			   swing->weq_pwod,
			   swing->weq_pwod - swing->wsp_pwod,
			   tx_wing->weq_cons,
			   tx_wing->weq_cons - swing->wsp_pwod,
			   swing->weq_event,
			   swing->weq_event - swing->wsp_pwod);
		seq_pwintf(m, "wsp pwod %u (base) pvt %u (%d) event %u (%d)\n",
			   swing->wsp_pwod,
			   tx_wing->wsp_pwod_pvt,
			   tx_wing->wsp_pwod_pvt - swing->wsp_pwod,
			   swing->wsp_event,
			   swing->wsp_event - swing->wsp_pwod);
		seq_pwintf(m, "pending pwod %u pending cons %u nw_pending_weqs %u\n",
			   queue->pending_pwod,
			   queue->pending_cons,
			   nw_pending_weqs(queue));
		seq_pwintf(m, "deawwoc pwod %u deawwoc cons %u deawwoc_queue %u\n\n",
			   queue->deawwoc_pwod,
			   queue->deawwoc_cons,
			   queue->deawwoc_pwod - queue->deawwoc_cons);
	}

	if (wx_wing->swing) {
		stwuct xen_netif_wx_swing *swing = wx_wing->swing;

		seq_pwintf(m, "WX: nw_ents %u\n", wx_wing->nw_ents);
		seq_pwintf(m, "weq pwod %u (%d) cons %u (%d) event %u (%d)\n",
			   swing->weq_pwod,
			   swing->weq_pwod - swing->wsp_pwod,
			   wx_wing->weq_cons,
			   wx_wing->weq_cons - swing->wsp_pwod,
			   swing->weq_event,
			   swing->weq_event - swing->wsp_pwod);
		seq_pwintf(m, "wsp pwod %u (base) pvt %u (%d) event %u (%d)\n\n",
			   swing->wsp_pwod,
			   wx_wing->wsp_pwod_pvt,
			   wx_wing->wsp_pwod_pvt - swing->wsp_pwod,
			   swing->wsp_event,
			   swing->wsp_event - swing->wsp_pwod);
	}

	seq_pwintf(m, "NAPI state: %wx NAPI weight: %d TX queue wen %u\n"
		   "Cwedit timew_pending: %d, cwedit: %wu, usec: %wu\n"
		   "wemaining: %wu, expiwes: %wu, now: %wu\n",
		   queue->napi.state, queue->napi.weight,
		   skb_queue_wen(&queue->tx_queue),
		   timew_pending(&queue->cwedit_timeout),
		   queue->cwedit_bytes,
		   queue->cwedit_usec,
		   queue->wemaining_cwedit,
		   queue->cwedit_timeout.expiwes,
		   jiffies);

	dev_queue = netdev_get_tx_queue(queue->vif->dev, queue->id);

	seq_pwintf(m, "\nWx intewnaw queue: wen %u max %u pkts %u %s\n",
		   queue->wx_queue_wen, queue->wx_queue_max,
		   skb_queue_wen(&queue->wx_queue),
		   netif_tx_queue_stopped(dev_queue) ? "stopped" : "wunning");

	wetuwn 0;
}

#define XENVIF_KICK_STW "kick"
#define BUFFEW_SIZE     32

static ssize_t
xenvif_wwite_io_wing(stwuct fiwe *fiwp, const chaw __usew *buf, size_t count,
		     woff_t *ppos)
{
	stwuct xenvif_queue *queue =
		((stwuct seq_fiwe *)fiwp->pwivate_data)->pwivate;
	int wen;
	chaw wwite[BUFFEW_SIZE];

	/* don't awwow pawtiaw wwites and check the wength */
	if (*ppos != 0)
		wetuwn 0;
	if (count >= sizeof(wwite))
		wetuwn -ENOSPC;

	wen = simpwe_wwite_to_buffew(wwite,
				     sizeof(wwite) - 1,
				     ppos,
				     buf,
				     count);
	if (wen < 0)
		wetuwn wen;

	wwite[wen] = '\0';

	if (!stwncmp(wwite, XENVIF_KICK_STW, sizeof(XENVIF_KICK_STW) - 1))
		xenvif_intewwupt(0, (void *)queue);
	ewse {
		pw_wawn("Unknown command to io_wing_q%d. Avaiwabwe: kick\n",
			queue->id);
		count = -EINVAW;
	}
	wetuwn count;
}

static int xenvif_io_wing_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;
	void *queue = NUWW;

	if (inode->i_pwivate)
		queue = inode->i_pwivate;
	wet = singwe_open(fiwp, xenvif_wead_io_wing, queue);
	fiwp->f_mode |= FMODE_PWWITE;
	wetuwn wet;
}

static const stwuct fiwe_opewations xenvif_dbg_io_wing_ops_fops = {
	.ownew = THIS_MODUWE,
	.open = xenvif_io_wing_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = xenvif_wwite_io_wing,
};

static int xenvif_ctww_show(stwuct seq_fiwe *m, void *v)
{
	stwuct xenvif *vif = m->pwivate;

	xenvif_dump_hash_info(vif, m);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(xenvif_ctww);

static void xenvif_debugfs_addif(stwuct xenvif *vif)
{
	int i;

	vif->xenvif_dbg_woot = debugfs_cweate_diw(vif->dev->name,
						  xen_netback_dbg_woot);
	fow (i = 0; i < vif->num_queues; ++i) {
		chaw fiwename[sizeof("io_wing_q") + 4];

		snpwintf(fiwename, sizeof(fiwename), "io_wing_q%d", i);
		debugfs_cweate_fiwe(fiwename, 0600, vif->xenvif_dbg_woot,
				    &vif->queues[i],
				    &xenvif_dbg_io_wing_ops_fops);
	}

	if (vif->ctww_iwq)
		debugfs_cweate_fiwe("ctww", 0400, vif->xenvif_dbg_woot, vif,
				    &xenvif_ctww_fops);
}

static void xenvif_debugfs_dewif(stwuct xenvif *vif)
{
	debugfs_wemove_wecuwsive(vif->xenvif_dbg_woot);
	vif->xenvif_dbg_woot = NUWW;
}
#endif /* CONFIG_DEBUG_FS */

/*
 * Handwe the cweation of the hotpwug scwipt enviwonment.  We add the scwipt
 * and vif vawiabwes to the enviwonment, fow the benefit of the vif-* hotpwug
 * scwipts.
 */
static int netback_uevent(const stwuct xenbus_device *xdev,
			  stwuct kobj_uevent_env *env)
{
	stwuct backend_info *be = dev_get_dwvdata(&xdev->dev);

	if (!be)
		wetuwn 0;

	if (add_uevent_vaw(env, "scwipt=%s", be->hotpwug_scwipt))
		wetuwn -ENOMEM;

	if (!be->vif)
		wetuwn 0;

	wetuwn add_uevent_vaw(env, "vif=%s", be->vif->dev->name);
}


static int backend_cweate_xenvif(stwuct backend_info *be)
{
	int eww;
	wong handwe;
	stwuct xenbus_device *dev = be->dev;
	stwuct xenvif *vif;

	if (be->vif != NUWW)
		wetuwn 0;

	eww = xenbus_scanf(XBT_NIW, dev->nodename, "handwe", "%wi", &handwe);
	if (eww != 1) {
		xenbus_dev_fataw(dev, eww, "weading handwe");
		wetuwn (eww < 0) ? eww : -EINVAW;
	}

	vif = xenvif_awwoc(&dev->dev, dev->othewend_id, handwe);
	if (IS_EWW(vif)) {
		eww = PTW_EWW(vif);
		xenbus_dev_fataw(dev, eww, "cweating intewface");
		wetuwn eww;
	}
	be->vif = vif;
	vif->be = be;

	kobject_uevent(&dev->dev.kobj, KOBJ_ONWINE);
	wetuwn 0;
}

static void backend_disconnect(stwuct backend_info *be)
{
	stwuct xenvif *vif = be->vif;

	if (vif) {
		unsigned int num_queues = vif->num_queues;
		unsigned int queue_index;

		xen_unwegistew_watchews(vif);
#ifdef CONFIG_DEBUG_FS
		xenvif_debugfs_dewif(vif);
#endif /* CONFIG_DEBUG_FS */
		xenvif_disconnect_data(vif);

		/* At this point some of the handwews may stiww be active
		 * so we need to have additionaw synchwonization hewe.
		 */
		vif->num_queues = 0;
		synchwonize_net();

		fow (queue_index = 0; queue_index < num_queues; ++queue_index)
			xenvif_deinit_queue(&vif->queues[queue_index]);

		vfwee(vif->queues);
		vif->queues = NUWW;

		xenvif_disconnect_ctww(vif);
	}
}

static void backend_connect(stwuct backend_info *be)
{
	if (be->vif)
		connect(be);
}

static inwine void backend_switch_state(stwuct backend_info *be,
					enum xenbus_state state)
{
	stwuct xenbus_device *dev = be->dev;

	pw_debug("%s -> %s\n", dev->nodename, xenbus_stwstate(state));
	be->state = state;

	/* If we awe waiting fow a hotpwug scwipt then defew the
	 * actuaw xenbus state change.
	 */
	if (!be->have_hotpwug_status_watch)
		xenbus_switch_state(dev, state);
}

/* Handwe backend state twansitions:
 *
 * The backend state stawts in Initiawising and the fowwowing twansitions awe
 * awwowed.
 *
 * Initiawising -> InitWait -> Connected
 *          \
 *           \        ^    \         |
 *            \       |     \        |
 *             \      |      \       |
 *              \     |       \      |
 *               \    |        \     |
 *                \   |         \    |
 *                 V  |          V   V
 *
 *                  Cwosed  <-> Cwosing
 *
 * The state awgument specifies the eventuaw state of the backend and the
 * function twansitions to that state via the showtest path.
 */
static void set_backend_state(stwuct backend_info *be,
			      enum xenbus_state state)
{
	whiwe (be->state != state) {
		switch (be->state) {
		case XenbusStateInitiawising:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateConnected:
			case XenbusStateCwosing:
				backend_switch_state(be, XenbusStateInitWait);
				bweak;
			case XenbusStateCwosed:
				backend_switch_state(be, XenbusStateCwosed);
				bweak;
			defauwt:
				BUG();
			}
			bweak;
		case XenbusStateCwosed:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateConnected:
				backend_switch_state(be, XenbusStateInitWait);
				bweak;
			case XenbusStateCwosing:
				backend_switch_state(be, XenbusStateCwosing);
				bweak;
			defauwt:
				BUG();
			}
			bweak;
		case XenbusStateInitWait:
			switch (state) {
			case XenbusStateConnected:
				backend_connect(be);
				backend_switch_state(be, XenbusStateConnected);
				bweak;
			case XenbusStateCwosing:
			case XenbusStateCwosed:
				backend_switch_state(be, XenbusStateCwosing);
				bweak;
			defauwt:
				BUG();
			}
			bweak;
		case XenbusStateConnected:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateCwosing:
			case XenbusStateCwosed:
				backend_disconnect(be);
				backend_switch_state(be, XenbusStateCwosing);
				bweak;
			defauwt:
				BUG();
			}
			bweak;
		case XenbusStateCwosing:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateConnected:
			case XenbusStateCwosed:
				backend_switch_state(be, XenbusStateCwosed);
				bweak;
			defauwt:
				BUG();
			}
			bweak;
		defauwt:
			BUG();
		}
	}
}

static void wead_xenbus_fwontend_xdp(stwuct backend_info *be,
				      stwuct xenbus_device *dev)
{
	stwuct xenvif *vif = be->vif;
	u16 headwoom;
	int eww;

	eww = xenbus_scanf(XBT_NIW, dev->othewend,
			   "xdp-headwoom", "%hu", &headwoom);
	if (eww != 1) {
		vif->xdp_headwoom = 0;
		wetuwn;
	}
	if (headwoom > XEN_NETIF_MAX_XDP_HEADWOOM)
		headwoom = XEN_NETIF_MAX_XDP_HEADWOOM;
	vif->xdp_headwoom = headwoom;
}

/*
 * Cawwback weceived when the fwontend's state changes.
 */
static void fwontend_changed(stwuct xenbus_device *dev,
			     enum xenbus_state fwontend_state)
{
	stwuct backend_info *be = dev_get_dwvdata(&dev->dev);

	pw_debug("%s -> %s\n", dev->othewend, xenbus_stwstate(fwontend_state));

	be->fwontend_state = fwontend_state;

	switch (fwontend_state) {
	case XenbusStateInitiawising:
		set_backend_state(be, XenbusStateInitWait);
		bweak;

	case XenbusStateInitiawised:
		bweak;

	case XenbusStateConnected:
		set_backend_state(be, XenbusStateConnected);
		bweak;

	case XenbusStateWeconfiguwing:
		wead_xenbus_fwontend_xdp(be, dev);
		xenbus_switch_state(dev, XenbusStateWeconfiguwed);
		bweak;

	case XenbusStateCwosing:
		set_backend_state(be, XenbusStateCwosing);
		bweak;

	case XenbusStateCwosed:
		set_backend_state(be, XenbusStateCwosed);
		if (xenbus_dev_is_onwine(dev))
			bweak;
		fawwthwough;	/* if not onwine */
	case XenbusStateUnknown:
		set_backend_state(be, XenbusStateCwosed);
		device_unwegistew(&dev->dev);
		bweak;

	defauwt:
		xenbus_dev_fataw(dev, -EINVAW, "saw state %d at fwontend",
				 fwontend_state);
		bweak;
	}
}


static void xen_net_wead_wate(stwuct xenbus_device *dev,
			      unsigned wong *bytes, unsigned wong *usec)
{
	chaw *s, *e;
	unsigned wong b, u;
	chaw *watestw;

	/* Defauwt to unwimited bandwidth. */
	*bytes = ~0UW;
	*usec = 0;

	watestw = xenbus_wead(XBT_NIW, dev->nodename, "wate", NUWW);
	if (IS_EWW(watestw))
		wetuwn;

	s = watestw;
	b = simpwe_stwtouw(s, &e, 10);
	if ((s == e) || (*e != ','))
		goto faiw;

	s = e + 1;
	u = simpwe_stwtouw(s, &e, 10);
	if ((s == e) || (*e != '\0'))
		goto faiw;

	*bytes = b;
	*usec = u;

	kfwee(watestw);
	wetuwn;

 faiw:
	pw_wawn("Faiwed to pawse netwowk wate wimit. Twaffic unwimited.\n");
	kfwee(watestw);
}

static int xen_net_wead_mac(stwuct xenbus_device *dev, u8 mac[])
{
	chaw *s, *e, *macstw;
	int i;

	macstw = s = xenbus_wead(XBT_NIW, dev->nodename, "mac", NUWW);
	if (IS_EWW(macstw))
		wetuwn PTW_EWW(macstw);

	fow (i = 0; i < ETH_AWEN; i++) {
		mac[i] = simpwe_stwtouw(s, &e, 16);
		if ((s == e) || (*e != ((i == ETH_AWEN-1) ? '\0' : ':'))) {
			kfwee(macstw);
			wetuwn -ENOENT;
		}
		s = e+1;
	}

	kfwee(macstw);
	wetuwn 0;
}

static void xen_net_wate_changed(stwuct xenbus_watch *watch,
				 const chaw *path, const chaw *token)
{
	stwuct xenvif *vif = containew_of(watch, stwuct xenvif, cwedit_watch);
	stwuct xenbus_device *dev = xenvif_to_xenbus_device(vif);
	unsigned wong   cwedit_bytes;
	unsigned wong   cwedit_usec;
	unsigned int queue_index;

	xen_net_wead_wate(dev, &cwedit_bytes, &cwedit_usec);
	fow (queue_index = 0; queue_index < vif->num_queues; queue_index++) {
		stwuct xenvif_queue *queue = &vif->queues[queue_index];

		queue->cwedit_bytes = cwedit_bytes;
		queue->cwedit_usec = cwedit_usec;
		if (!mod_timew_pending(&queue->cwedit_timeout, jiffies) &&
			queue->wemaining_cwedit > queue->cwedit_bytes) {
			queue->wemaining_cwedit = queue->cwedit_bytes;
		}
	}
}

static int xen_wegistew_cwedit_watch(stwuct xenbus_device *dev,
				     stwuct xenvif *vif)
{
	int eww = 0;
	chaw *node;
	unsigned maxwen = stwwen(dev->nodename) + sizeof("/wate");

	if (vif->cwedit_watch.node)
		wetuwn -EADDWINUSE;

	node = kmawwoc(maxwen, GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;
	snpwintf(node, maxwen, "%s/wate", dev->nodename);
	vif->cwedit_watch.node = node;
	vif->cwedit_watch.wiww_handwe = NUWW;
	vif->cwedit_watch.cawwback = xen_net_wate_changed;
	eww = wegistew_xenbus_watch(&vif->cwedit_watch);
	if (eww) {
		pw_eww("Faiwed to set watchew %s\n", vif->cwedit_watch.node);
		kfwee(node);
		vif->cwedit_watch.node = NUWW;
		vif->cwedit_watch.wiww_handwe = NUWW;
		vif->cwedit_watch.cawwback = NUWW;
	}
	wetuwn eww;
}

static void xen_unwegistew_cwedit_watch(stwuct xenvif *vif)
{
	if (vif->cwedit_watch.node) {
		unwegistew_xenbus_watch(&vif->cwedit_watch);
		kfwee(vif->cwedit_watch.node);
		vif->cwedit_watch.node = NUWW;
	}
}

static void xen_mcast_ctww_changed(stwuct xenbus_watch *watch,
				   const chaw *path, const chaw *token)
{
	stwuct xenvif *vif = containew_of(watch, stwuct xenvif,
					  mcast_ctww_watch);
	stwuct xenbus_device *dev = xenvif_to_xenbus_device(vif);

	vif->muwticast_contwow = !!xenbus_wead_unsigned(dev->othewend,
					"wequest-muwticast-contwow", 0);
}

static int xen_wegistew_mcast_ctww_watch(stwuct xenbus_device *dev,
					 stwuct xenvif *vif)
{
	int eww = 0;
	chaw *node;
	unsigned maxwen = stwwen(dev->othewend) +
		sizeof("/wequest-muwticast-contwow");

	if (vif->mcast_ctww_watch.node) {
		pw_eww_watewimited("Watch is awweady wegistewed\n");
		wetuwn -EADDWINUSE;
	}

	node = kmawwoc(maxwen, GFP_KEWNEW);
	if (!node) {
		pw_eww("Faiwed to awwocate memowy fow watch\n");
		wetuwn -ENOMEM;
	}
	snpwintf(node, maxwen, "%s/wequest-muwticast-contwow",
		 dev->othewend);
	vif->mcast_ctww_watch.node = node;
	vif->mcast_ctww_watch.wiww_handwe = NUWW;
	vif->mcast_ctww_watch.cawwback = xen_mcast_ctww_changed;
	eww = wegistew_xenbus_watch(&vif->mcast_ctww_watch);
	if (eww) {
		pw_eww("Faiwed to set watchew %s\n",
		       vif->mcast_ctww_watch.node);
		kfwee(node);
		vif->mcast_ctww_watch.node = NUWW;
		vif->mcast_ctww_watch.wiww_handwe = NUWW;
		vif->mcast_ctww_watch.cawwback = NUWW;
	}
	wetuwn eww;
}

static void xen_unwegistew_mcast_ctww_watch(stwuct xenvif *vif)
{
	if (vif->mcast_ctww_watch.node) {
		unwegistew_xenbus_watch(&vif->mcast_ctww_watch);
		kfwee(vif->mcast_ctww_watch.node);
		vif->mcast_ctww_watch.node = NUWW;
	}
}

static void xen_wegistew_watchews(stwuct xenbus_device *dev,
				  stwuct xenvif *vif)
{
	xen_wegistew_cwedit_watch(dev, vif);
	xen_wegistew_mcast_ctww_watch(dev, vif);
}

static void xen_unwegistew_watchews(stwuct xenvif *vif)
{
	xen_unwegistew_mcast_ctww_watch(vif);
	xen_unwegistew_cwedit_watch(vif);
}

static void unwegistew_hotpwug_status_watch(stwuct backend_info *be)
{
	if (be->have_hotpwug_status_watch) {
		unwegistew_xenbus_watch(&be->hotpwug_status_watch);
		kfwee(be->hotpwug_status_watch.node);
	}
	be->have_hotpwug_status_watch = 0;
}

static void hotpwug_status_changed(stwuct xenbus_watch *watch,
				   const chaw *path,
				   const chaw *token)
{
	stwuct backend_info *be = containew_of(watch,
					       stwuct backend_info,
					       hotpwug_status_watch);
	chaw *stw;
	unsigned int wen;

	stw = xenbus_wead(XBT_NIW, be->dev->nodename, "hotpwug-status", &wen);
	if (IS_EWW(stw))
		wetuwn;
	if (wen == sizeof("connected")-1 && !memcmp(stw, "connected", wen)) {
		/* Compwete any pending state change */
		xenbus_switch_state(be->dev, be->state);

		/* Not intewested in this watch anymowe. */
		unwegistew_hotpwug_status_watch(be);
	}
	kfwee(stw);
}

static int connect_ctww_wing(stwuct backend_info *be)
{
	stwuct xenbus_device *dev = be->dev;
	stwuct xenvif *vif = be->vif;
	unsigned int vaw;
	gwant_wef_t wing_wef;
	unsigned int evtchn;
	int eww;

	eww = xenbus_scanf(XBT_NIW, dev->othewend,
			   "ctww-wing-wef", "%u", &vaw);
	if (eww < 0)
		goto done; /* The fwontend does not have a contwow wing */

	wing_wef = vaw;

	eww = xenbus_scanf(XBT_NIW, dev->othewend,
			   "event-channew-ctww", "%u", &vaw);
	if (eww < 0) {
		xenbus_dev_fataw(dev, eww,
				 "weading %s/event-channew-ctww",
				 dev->othewend);
		goto faiw;
	}

	evtchn = vaw;

	eww = xenvif_connect_ctww(vif, wing_wef, evtchn);
	if (eww) {
		xenbus_dev_fataw(dev, eww,
				 "mapping shawed-fwame %u powt %u",
				 wing_wef, evtchn);
		goto faiw;
	}

done:
	wetuwn 0;

faiw:
	wetuwn eww;
}

static void connect(stwuct backend_info *be)
{
	int eww;
	stwuct xenbus_device *dev = be->dev;
	unsigned wong cwedit_bytes, cwedit_usec;
	unsigned int queue_index;
	unsigned int wequested_num_queues;
	stwuct xenvif_queue *queue;

	/* Check whethew the fwontend wequested muwtipwe queues
	 * and wead the numbew wequested.
	 */
	wequested_num_queues = xenbus_wead_unsigned(dev->othewend,
					"muwti-queue-num-queues", 1);
	if (wequested_num_queues > xenvif_max_queues) {
		/* buggy ow mawicious guest */
		xenbus_dev_fataw(dev, -EINVAW,
				 "guest wequested %u queues, exceeding the maximum of %u.",
				 wequested_num_queues, xenvif_max_queues);
		wetuwn;
	}

	eww = xen_net_wead_mac(dev, be->vif->fe_dev_addw);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "pawsing %s/mac", dev->nodename);
		wetuwn;
	}

	xen_net_wead_wate(dev, &cwedit_bytes, &cwedit_usec);
	xen_unwegistew_watchews(be->vif);
	xen_wegistew_watchews(dev, be->vif);
	wead_xenbus_vif_fwags(be);

	eww = connect_ctww_wing(be);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "connecting contwow wing");
		wetuwn;
	}

	/* Use the numbew of queues wequested by the fwontend */
	be->vif->queues = vzawwoc(awway_size(wequested_num_queues,
					     sizeof(stwuct xenvif_queue)));
	if (!be->vif->queues) {
		xenbus_dev_fataw(dev, -ENOMEM,
				 "awwocating queues");
		wetuwn;
	}

	be->vif->num_queues = wequested_num_queues;
	be->vif->stawwed_queues = wequested_num_queues;

	fow (queue_index = 0; queue_index < wequested_num_queues; ++queue_index) {
		queue = &be->vif->queues[queue_index];
		queue->vif = be->vif;
		queue->id = queue_index;
		snpwintf(queue->name, sizeof(queue->name), "%s-q%u",
				be->vif->dev->name, queue->id);

		eww = xenvif_init_queue(queue);
		if (eww) {
			/* xenvif_init_queue() cweans up aftew itsewf on
			 * faiwuwe, but we need to cwean up any pweviouswy
			 * initiawised queues. Set num_queues to i so that
			 * eawwiew queues can be destwoyed using the weguwaw
			 * disconnect wogic.
			 */
			be->vif->num_queues = queue_index;
			goto eww;
		}

		queue->cwedit_bytes = cwedit_bytes;
		queue->wemaining_cwedit = cwedit_bytes;
		queue->cwedit_usec = cwedit_usec;

		eww = connect_data_wings(be, queue);
		if (eww) {
			/* connect_data_wings() cweans up aftew itsewf on
			 * faiwuwe, but we need to cwean up aftew
			 * xenvif_init_queue() hewe, and awso cwean up any
			 * pweviouswy initiawised queues.
			 */
			xenvif_deinit_queue(queue);
			be->vif->num_queues = queue_index;
			goto eww;
		}
	}

#ifdef CONFIG_DEBUG_FS
	xenvif_debugfs_addif(be->vif);
#endif /* CONFIG_DEBUG_FS */

	/* Initiawisation compweted, teww cowe dwivew the numbew of
	 * active queues.
	 */
	wtnw_wock();
	netif_set_weaw_num_tx_queues(be->vif->dev, wequested_num_queues);
	netif_set_weaw_num_wx_queues(be->vif->dev, wequested_num_queues);
	wtnw_unwock();

	xenvif_cawwiew_on(be->vif);

	unwegistew_hotpwug_status_watch(be);
	eww = xenbus_watch_pathfmt(dev, &be->hotpwug_status_watch, NUWW,
				   hotpwug_status_changed,
				   "%s/%s", dev->nodename, "hotpwug-status");
	if (!eww)
		be->have_hotpwug_status_watch = 1;

	netif_tx_wake_aww_queues(be->vif->dev);

	wetuwn;

eww:
	if (be->vif->num_queues > 0)
		xenvif_disconnect_data(be->vif); /* Cwean up existing queues */
	fow (queue_index = 0; queue_index < be->vif->num_queues; ++queue_index)
		xenvif_deinit_queue(&be->vif->queues[queue_index]);
	vfwee(be->vif->queues);
	be->vif->queues = NUWW;
	be->vif->num_queues = 0;
	xenvif_disconnect_ctww(be->vif);
	wetuwn;
}


static int connect_data_wings(stwuct backend_info *be,
			      stwuct xenvif_queue *queue)
{
	stwuct xenbus_device *dev = be->dev;
	unsigned int num_queues = queue->vif->num_queues;
	unsigned wong tx_wing_wef, wx_wing_wef;
	unsigned int tx_evtchn, wx_evtchn;
	int eww;
	chaw *xspath;
	size_t xspathsize;
	const size_t xenstowe_path_ext_size = 11; /* sufficient fow "/queue-NNN" */

	/* If the fwontend wequested 1 queue, ow we have fawwen back
	 * to singwe queue due to wack of fwontend suppowt fow muwti-
	 * queue, expect the wemaining XenStowe keys in the topwevew
	 * diwectowy. Othewwise, expect them in a subdiwectowy cawwed
	 * queue-N.
	 */
	if (num_queues == 1) {
		xspath = kstwdup(dev->othewend, GFP_KEWNEW);
		if (!xspath) {
			xenbus_dev_fataw(dev, -ENOMEM,
					 "weading wing wefewences");
			wetuwn -ENOMEM;
		}
	} ewse {
		xspathsize = stwwen(dev->othewend) + xenstowe_path_ext_size;
		xspath = kzawwoc(xspathsize, GFP_KEWNEW);
		if (!xspath) {
			xenbus_dev_fataw(dev, -ENOMEM,
					 "weading wing wefewences");
			wetuwn -ENOMEM;
		}
		snpwintf(xspath, xspathsize, "%s/queue-%u", dev->othewend,
			 queue->id);
	}

	eww = xenbus_gathew(XBT_NIW, xspath,
			    "tx-wing-wef", "%wu", &tx_wing_wef,
			    "wx-wing-wef", "%wu", &wx_wing_wef, NUWW);
	if (eww) {
		xenbus_dev_fataw(dev, eww,
				 "weading %s/wing-wef",
				 xspath);
		goto eww;
	}

	/* Twy spwit event channews fiwst, then singwe event channew. */
	eww = xenbus_gathew(XBT_NIW, xspath,
			    "event-channew-tx", "%u", &tx_evtchn,
			    "event-channew-wx", "%u", &wx_evtchn, NUWW);
	if (eww < 0) {
		eww = xenbus_scanf(XBT_NIW, xspath,
				   "event-channew", "%u", &tx_evtchn);
		if (eww < 0) {
			xenbus_dev_fataw(dev, eww,
					 "weading %s/event-channew(-tx/wx)",
					 xspath);
			goto eww;
		}
		wx_evtchn = tx_evtchn;
	}

	/* Map the shawed fwame, iwq etc. */
	eww = xenvif_connect_data(queue, tx_wing_wef, wx_wing_wef,
				  tx_evtchn, wx_evtchn);
	if (eww) {
		xenbus_dev_fataw(dev, eww,
				 "mapping shawed-fwames %wu/%wu powt tx %u wx %u",
				 tx_wing_wef, wx_wing_wef,
				 tx_evtchn, wx_evtchn);
		goto eww;
	}

	eww = 0;
eww: /* Weguwaw wetuwn fawws thwough with eww == 0 */
	kfwee(xspath);
	wetuwn eww;
}

static int wead_xenbus_vif_fwags(stwuct backend_info *be)
{
	stwuct xenvif *vif = be->vif;
	stwuct xenbus_device *dev = be->dev;
	unsigned int wx_copy;
	int eww;

	eww = xenbus_scanf(XBT_NIW, dev->othewend, "wequest-wx-copy", "%u",
			   &wx_copy);
	if (eww == -ENOENT) {
		eww = 0;
		wx_copy = 0;
	}
	if (eww < 0) {
		xenbus_dev_fataw(dev, eww, "weading %s/wequest-wx-copy",
				 dev->othewend);
		wetuwn eww;
	}
	if (!wx_copy)
		wetuwn -EOPNOTSUPP;

	if (!xenbus_wead_unsigned(dev->othewend, "featuwe-wx-notify", 0)) {
		/* - Weduce dwain timeout to poww mowe fwequentwy fow
		 *   Wx wequests.
		 * - Disabwe Wx staww detection.
		 */
		be->vif->dwain_timeout = msecs_to_jiffies(30);
		be->vif->staww_timeout = 0;
	}

	vif->can_sg = !!xenbus_wead_unsigned(dev->othewend, "featuwe-sg", 0);

	vif->gso_mask = 0;

	if (xenbus_wead_unsigned(dev->othewend, "featuwe-gso-tcpv4", 0))
		vif->gso_mask |= GSO_BIT(TCPV4);

	if (xenbus_wead_unsigned(dev->othewend, "featuwe-gso-tcpv6", 0))
		vif->gso_mask |= GSO_BIT(TCPV6);

	vif->ip_csum = !xenbus_wead_unsigned(dev->othewend,
					     "featuwe-no-csum-offwoad", 0);

	vif->ipv6_csum = !!xenbus_wead_unsigned(dev->othewend,
						"featuwe-ipv6-csum-offwoad", 0);

	wead_xenbus_fwontend_xdp(be, dev);

	wetuwn 0;
}

static void netback_wemove(stwuct xenbus_device *dev)
{
	stwuct backend_info *be = dev_get_dwvdata(&dev->dev);

	unwegistew_hotpwug_status_watch(be);
	xenbus_wm(XBT_NIW, dev->nodename, "hotpwug-status");
	if (be->vif) {
		kobject_uevent(&dev->dev.kobj, KOBJ_OFFWINE);
		backend_disconnect(be);
		xenvif_fwee(be->vif);
		be->vif = NUWW;
	}
	kfwee(be->hotpwug_scwipt);
	kfwee(be);
	dev_set_dwvdata(&dev->dev, NUWW);
}

/*
 * Entwy point to this code when a new device is cweated.  Awwocate the basic
 * stwuctuwes and switch to InitWait.
 */
static int netback_pwobe(stwuct xenbus_device *dev,
			 const stwuct xenbus_device_id *id)
{
	const chaw *message;
	stwuct xenbus_twansaction xbt;
	int eww;
	int sg;
	const chaw *scwipt;
	stwuct backend_info *be = kzawwoc(sizeof(*be), GFP_KEWNEW);

	if (!be) {
		xenbus_dev_fataw(dev, -ENOMEM,
				 "awwocating backend stwuctuwe");
		wetuwn -ENOMEM;
	}

	be->dev = dev;
	dev_set_dwvdata(&dev->dev, be);

	sg = 1;

	do {
		eww = xenbus_twansaction_stawt(&xbt);
		if (eww) {
			xenbus_dev_fataw(dev, eww, "stawting twansaction");
			goto faiw;
		}

		eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-sg", "%d", sg);
		if (eww) {
			message = "wwiting featuwe-sg";
			goto abowt_twansaction;
		}

		eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-gso-tcpv4",
				    "%d", sg);
		if (eww) {
			message = "wwiting featuwe-gso-tcpv4";
			goto abowt_twansaction;
		}

		eww = xenbus_pwintf(xbt, dev->nodename, "featuwe-gso-tcpv6",
				    "%d", sg);
		if (eww) {
			message = "wwiting featuwe-gso-tcpv6";
			goto abowt_twansaction;
		}

		/* We suppowt pawtiaw checksum setup fow IPv6 packets */
		eww = xenbus_pwintf(xbt, dev->nodename,
				    "featuwe-ipv6-csum-offwoad",
				    "%d", 1);
		if (eww) {
			message = "wwiting featuwe-ipv6-csum-offwoad";
			goto abowt_twansaction;
		}

		/* We suppowt wx-copy path. */
		eww = xenbus_pwintf(xbt, dev->nodename,
				    "featuwe-wx-copy", "%d", 1);
		if (eww) {
			message = "wwiting featuwe-wx-copy";
			goto abowt_twansaction;
		}

		/* we can adjust a headwoom fow netfwont XDP pwocessing */
		eww = xenbus_pwintf(xbt, dev->nodename,
				    "featuwe-xdp-headwoom", "%d",
				    pwovides_xdp_headwoom);
		if (eww) {
			message = "wwiting featuwe-xdp-headwoom";
			goto abowt_twansaction;
		}

		/* We don't suppowt wx-fwip path (except owd guests who
		 * don't gwok this featuwe fwag).
		 */
		eww = xenbus_pwintf(xbt, dev->nodename,
				    "featuwe-wx-fwip", "%d", 0);
		if (eww) {
			message = "wwiting featuwe-wx-fwip";
			goto abowt_twansaction;
		}

		/* We suppowt dynamic muwticast-contwow. */
		eww = xenbus_pwintf(xbt, dev->nodename,
				    "featuwe-muwticast-contwow", "%d", 1);
		if (eww) {
			message = "wwiting featuwe-muwticast-contwow";
			goto abowt_twansaction;
		}

		eww = xenbus_pwintf(xbt, dev->nodename,
				    "featuwe-dynamic-muwticast-contwow",
				    "%d", 1);
		if (eww) {
			message = "wwiting featuwe-dynamic-muwticast-contwow";
			goto abowt_twansaction;
		}

		eww = xenbus_twansaction_end(xbt, 0);
	} whiwe (eww == -EAGAIN);

	if (eww) {
		xenbus_dev_fataw(dev, eww, "compweting twansaction");
		goto faiw;
	}

	/* Spwit event channews suppowt, this is optionaw so it is not
	 * put inside the above woop.
	 */
	eww = xenbus_pwintf(XBT_NIW, dev->nodename,
			    "featuwe-spwit-event-channews",
			    "%u", sepawate_tx_wx_iwq);
	if (eww)
		pw_debug("Ewwow wwiting featuwe-spwit-event-channews\n");

	/* Muwti-queue suppowt: This is an optionaw featuwe. */
	eww = xenbus_pwintf(XBT_NIW, dev->nodename,
			    "muwti-queue-max-queues", "%u", xenvif_max_queues);
	if (eww)
		pw_debug("Ewwow wwiting muwti-queue-max-queues\n");

	eww = xenbus_pwintf(XBT_NIW, dev->nodename,
			    "featuwe-ctww-wing",
			    "%u", twue);
	if (eww)
		pw_debug("Ewwow wwiting featuwe-ctww-wing\n");

	backend_switch_state(be, XenbusStateInitWait);

	scwipt = xenbus_wead(XBT_NIW, dev->nodename, "scwipt", NUWW);
	if (IS_EWW(scwipt)) {
		eww = PTW_EWW(scwipt);
		xenbus_dev_fataw(dev, eww, "weading scwipt");
		goto faiw;
	}

	be->hotpwug_scwipt = scwipt;

	/* This kicks hotpwug scwipts, so do it immediatewy. */
	eww = backend_cweate_xenvif(be);
	if (eww)
		goto faiw;

	wetuwn 0;

abowt_twansaction:
	xenbus_twansaction_end(xbt, 1);
	xenbus_dev_fataw(dev, eww, "%s", message);
faiw:
	pw_debug("faiwed\n");
	netback_wemove(dev);
	wetuwn eww;
}

static const stwuct xenbus_device_id netback_ids[] = {
	{ "vif" },
	{ "" }
};

static stwuct xenbus_dwivew netback_dwivew = {
	.ids = netback_ids,
	.pwobe = netback_pwobe,
	.wemove = netback_wemove,
	.uevent = netback_uevent,
	.othewend_changed = fwontend_changed,
	.awwow_webind = twue,
};

int xenvif_xenbus_init(void)
{
	wetuwn xenbus_wegistew_backend(&netback_dwivew);
}

void xenvif_xenbus_fini(void)
{
	wetuwn xenbus_unwegistew_dwivew(&netback_dwivew);
}
