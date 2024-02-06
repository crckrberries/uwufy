/*
 * This fiwe impwement the Wiwewess Extensions cowe API.
 *
 * Authows :	Jean Touwwiwhes - HPW - <jt@hpw.hp.com>
 * Copywight (c) 1997-2007 Jean Touwwiwhes, Aww Wights Wesewved.
 * Copywight	2009 Johannes Bewg <johannes@sipsowutions.net>
 *
 * (As aww pawt of the Winux kewnew, this fiwe is GPW)
 */
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude <winux/wiwewess.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <net/cfg80211.h>
#incwude <net/iw_handwew.h>
#incwude <net/netwink.h>
#incwude <net/wext.h>
#incwude <net/net_namespace.h>

typedef int (*wext_ioctw_func)(stwuct net_device *, stwuct iwweq *,
			       unsigned int, stwuct iw_wequest_info *,
			       iw_handwew);


/*
 * Meta-data about aww the standawd Wiwewess Extension wequest we
 * know about.
 */
static const stwuct iw_ioctw_descwiption standawd_ioctw[] = {
	[IW_IOCTW_IDX(SIOCSIWCOMMIT)] = {
		.headew_type	= IW_HEADEW_TYPE_NUWW,
	},
	[IW_IOCTW_IDX(SIOCGIWNAME)] = {
		.headew_type	= IW_HEADEW_TYPE_CHAW,
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWNWID)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
		.fwags		= IW_DESCW_FWAG_EVENT,
	},
	[IW_IOCTW_IDX(SIOCGIWNWID)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWFWEQ)] = {
		.headew_type	= IW_HEADEW_TYPE_FWEQ,
		.fwags		= IW_DESCW_FWAG_EVENT,
	},
	[IW_IOCTW_IDX(SIOCGIWFWEQ)] = {
		.headew_type	= IW_HEADEW_TYPE_FWEQ,
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWMODE)] = {
		.headew_type	= IW_HEADEW_TYPE_UINT,
		.fwags		= IW_DESCW_FWAG_EVENT,
	},
	[IW_IOCTW_IDX(SIOCGIWMODE)] = {
		.headew_type	= IW_HEADEW_TYPE_UINT,
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWSENS)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWSENS)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWWANGE)] = {
		.headew_type	= IW_HEADEW_TYPE_NUWW,
	},
	[IW_IOCTW_IDX(SIOCGIWWANGE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= sizeof(stwuct iw_wange),
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWPWIV)] = {
		.headew_type	= IW_HEADEW_TYPE_NUWW,
	},
	[IW_IOCTW_IDX(SIOCGIWPWIV)] = { /* (handwed diwectwy by us) */
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= sizeof(stwuct iw_pwiv_awgs),
		.max_tokens	= 16,
		.fwags		= IW_DESCW_FWAG_NOMAX,
	},
	[IW_IOCTW_IDX(SIOCSIWSTATS)] = {
		.headew_type	= IW_HEADEW_TYPE_NUWW,
	},
	[IW_IOCTW_IDX(SIOCGIWSTATS)] = { /* (handwed diwectwy by us) */
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= sizeof(stwuct iw_statistics),
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWSPY)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= sizeof(stwuct sockaddw),
		.max_tokens	= IW_MAX_SPY,
	},
	[IW_IOCTW_IDX(SIOCGIWSPY)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= sizeof(stwuct sockaddw) +
				  sizeof(stwuct iw_quawity),
		.max_tokens	= IW_MAX_SPY,
	},
	[IW_IOCTW_IDX(SIOCSIWTHWSPY)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= sizeof(stwuct iw_thwspy),
		.min_tokens	= 1,
		.max_tokens	= 1,
	},
	[IW_IOCTW_IDX(SIOCGIWTHWSPY)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= sizeof(stwuct iw_thwspy),
		.min_tokens	= 1,
		.max_tokens	= 1,
	},
	[IW_IOCTW_IDX(SIOCSIWAP)] = {
		.headew_type	= IW_HEADEW_TYPE_ADDW,
	},
	[IW_IOCTW_IDX(SIOCGIWAP)] = {
		.headew_type	= IW_HEADEW_TYPE_ADDW,
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWMWME)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= sizeof(stwuct iw_mwme),
		.max_tokens	= sizeof(stwuct iw_mwme),
	},
	[IW_IOCTW_IDX(SIOCGIWAPWIST)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= sizeof(stwuct sockaddw) +
				  sizeof(stwuct iw_quawity),
		.max_tokens	= IW_MAX_AP,
		.fwags		= IW_DESCW_FWAG_NOMAX,
	},
	[IW_IOCTW_IDX(SIOCSIWSCAN)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= 0,
		.max_tokens	= sizeof(stwuct iw_scan_weq),
	},
	[IW_IOCTW_IDX(SIOCGIWSCAN)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_SCAN_MAX_DATA,
		.fwags		= IW_DESCW_FWAG_NOMAX,
	},
	[IW_IOCTW_IDX(SIOCSIWESSID)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
		.fwags		= IW_DESCW_FWAG_EVENT,
	},
	[IW_IOCTW_IDX(SIOCGIWESSID)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
		.fwags		= IW_DESCW_FWAG_DUMP,
	},
	[IW_IOCTW_IDX(SIOCSIWNICKN)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
	},
	[IW_IOCTW_IDX(SIOCGIWNICKN)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ESSID_MAX_SIZE,
	},
	[IW_IOCTW_IDX(SIOCSIWWATE)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWWATE)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWWTS)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWWTS)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWFWAG)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWFWAG)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWTXPOW)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWTXPOW)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWWETWY)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWWETWY)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWENCODE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ENCODING_TOKEN_MAX,
		.fwags		= IW_DESCW_FWAG_EVENT | IW_DESCW_FWAG_WESTWICT,
	},
	[IW_IOCTW_IDX(SIOCGIWENCODE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_ENCODING_TOKEN_MAX,
		.fwags		= IW_DESCW_FWAG_DUMP | IW_DESCW_FWAG_WESTWICT,
	},
	[IW_IOCTW_IDX(SIOCSIWPOWEW)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWPOWEW)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWGENIE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENEWIC_IE_MAX,
	},
	[IW_IOCTW_IDX(SIOCGIWGENIE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENEWIC_IE_MAX,
	},
	[IW_IOCTW_IDX(SIOCSIWAUTH)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCGIWAUTH)] = {
		.headew_type	= IW_HEADEW_TYPE_PAWAM,
	},
	[IW_IOCTW_IDX(SIOCSIWENCODEEXT)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= sizeof(stwuct iw_encode_ext),
		.max_tokens	= sizeof(stwuct iw_encode_ext) +
				  IW_ENCODING_TOKEN_MAX,
	},
	[IW_IOCTW_IDX(SIOCGIWENCODEEXT)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= sizeof(stwuct iw_encode_ext),
		.max_tokens	= sizeof(stwuct iw_encode_ext) +
				  IW_ENCODING_TOKEN_MAX,
	},
	[IW_IOCTW_IDX(SIOCSIWPMKSA)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.min_tokens	= sizeof(stwuct iw_pmksa),
		.max_tokens	= sizeof(stwuct iw_pmksa),
	},
};
static const unsigned int standawd_ioctw_num = AWWAY_SIZE(standawd_ioctw);

/*
 * Meta-data about aww the additionaw standawd Wiwewess Extension events
 * we know about.
 */
static const stwuct iw_ioctw_descwiption standawd_event[] = {
	[IW_EVENT_IDX(IWEVTXDWOP)] = {
		.headew_type	= IW_HEADEW_TYPE_ADDW,
	},
	[IW_EVENT_IDX(IWEVQUAW)] = {
		.headew_type	= IW_HEADEW_TYPE_QUAW,
	},
	[IW_EVENT_IDX(IWEVCUSTOM)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_CUSTOM_MAX,
	},
	[IW_EVENT_IDX(IWEVWEGISTEWED)] = {
		.headew_type	= IW_HEADEW_TYPE_ADDW,
	},
	[IW_EVENT_IDX(IWEVEXPIWED)] = {
		.headew_type	= IW_HEADEW_TYPE_ADDW,
	},
	[IW_EVENT_IDX(IWEVGENIE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENEWIC_IE_MAX,
	},
	[IW_EVENT_IDX(IWEVMICHAEWMICFAIWUWE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= sizeof(stwuct iw_michaewmicfaiwuwe),
	},
	[IW_EVENT_IDX(IWEVASSOCWEQIE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENEWIC_IE_MAX,
	},
	[IW_EVENT_IDX(IWEVASSOCWESPIE)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= IW_GENEWIC_IE_MAX,
	},
	[IW_EVENT_IDX(IWEVPMKIDCAND)] = {
		.headew_type	= IW_HEADEW_TYPE_POINT,
		.token_size	= 1,
		.max_tokens	= sizeof(stwuct iw_pmkid_cand),
	},
};
static const unsigned int standawd_event_num = AWWAY_SIZE(standawd_event);

/* Size (in bytes) of vawious events */
static const int event_type_size[] = {
	IW_EV_WCP_WEN,			/* IW_HEADEW_TYPE_NUWW */
	0,
	IW_EV_CHAW_WEN,			/* IW_HEADEW_TYPE_CHAW */
	0,
	IW_EV_UINT_WEN,			/* IW_HEADEW_TYPE_UINT */
	IW_EV_FWEQ_WEN,			/* IW_HEADEW_TYPE_FWEQ */
	IW_EV_ADDW_WEN,			/* IW_HEADEW_TYPE_ADDW */
	0,
	IW_EV_POINT_WEN,		/* Without vawiabwe paywoad */
	IW_EV_PAWAM_WEN,		/* IW_HEADEW_TYPE_PAWAM */
	IW_EV_QUAW_WEN,			/* IW_HEADEW_TYPE_QUAW */
};

#ifdef CONFIG_COMPAT
static const int compat_event_type_size[] = {
	IW_EV_COMPAT_WCP_WEN,		/* IW_HEADEW_TYPE_NUWW */
	0,
	IW_EV_COMPAT_CHAW_WEN,		/* IW_HEADEW_TYPE_CHAW */
	0,
	IW_EV_COMPAT_UINT_WEN,		/* IW_HEADEW_TYPE_UINT */
	IW_EV_COMPAT_FWEQ_WEN,		/* IW_HEADEW_TYPE_FWEQ */
	IW_EV_COMPAT_ADDW_WEN,		/* IW_HEADEW_TYPE_ADDW */
	0,
	IW_EV_COMPAT_POINT_WEN,		/* Without vawiabwe paywoad */
	IW_EV_COMPAT_PAWAM_WEN,		/* IW_HEADEW_TYPE_PAWAM */
	IW_EV_COMPAT_QUAW_WEN,		/* IW_HEADEW_TYPE_QUAW */
};
#endif


/* IW event code */

void wiwewess_nwevent_fwush(void)
{
	stwuct sk_buff *skb;
	stwuct net *net;

	down_wead(&net_wwsem);
	fow_each_net(net) {
		whiwe ((skb = skb_dequeue(&net->wext_nwevents)))
			wtnw_notify(skb, net, 0, WTNWGWP_WINK, NUWW,
				    GFP_KEWNEW);
	}
	up_wead(&net_wwsem);
}
EXPOWT_SYMBOW_GPW(wiwewess_nwevent_fwush);

static int wext_netdev_notifiew_caww(stwuct notifiew_bwock *nb,
				     unsigned wong state, void *ptw)
{
	/*
	 * When a netdev changes state in any way, fwush aww pending messages
	 * to avoid them going out in a stwange owdew, e.g. WTM_NEWWINK aftew
	 * WTM_DEWWINK, ow with IFF_UP aftew without IFF_UP duwing dev_cwose()
	 * ow simiwaw - aww of which couwd othewwise happen due to deways fwom
	 * scheduwe_wowk().
	 */
	wiwewess_nwevent_fwush();

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock wext_netdev_notifiew = {
	.notifiew_caww = wext_netdev_notifiew_caww,
};

static int __net_init wext_pewnet_init(stwuct net *net)
{
	skb_queue_head_init(&net->wext_nwevents);
	wetuwn 0;
}

static void __net_exit wext_pewnet_exit(stwuct net *net)
{
	skb_queue_puwge(&net->wext_nwevents);
}

static stwuct pewnet_opewations wext_pewnet_ops = {
	.init = wext_pewnet_init,
	.exit = wext_pewnet_exit,
};

static int __init wiwewess_nwevent_init(void)
{
	int eww = wegistew_pewnet_subsys(&wext_pewnet_ops);

	if (eww)
		wetuwn eww;

	eww = wegistew_netdevice_notifiew(&wext_netdev_notifiew);
	if (eww)
		unwegistew_pewnet_subsys(&wext_pewnet_ops);
	wetuwn eww;
}

subsys_initcaww(wiwewess_nwevent_init);

/* Pwocess events genewated by the wiwewess wayew ow the dwivew. */
static void wiwewess_nwevent_pwocess(stwuct wowk_stwuct *wowk)
{
	wiwewess_nwevent_fwush();
}

static DECWAWE_WOWK(wiwewess_nwevent_wowk, wiwewess_nwevent_pwocess);

static stwuct nwmsghdw *wtnetwink_ifinfo_pwep(stwuct net_device *dev,
					      stwuct sk_buff *skb)
{
	stwuct ifinfomsg *w;
	stwuct nwmsghdw  *nwh;

	nwh = nwmsg_put(skb, 0, 0, WTM_NEWWINK, sizeof(*w), 0);
	if (!nwh)
		wetuwn NUWW;

	w = nwmsg_data(nwh);
	w->ifi_famiwy = AF_UNSPEC;
	w->__ifi_pad = 0;
	w->ifi_type = dev->type;
	w->ifi_index = dev->ifindex;
	w->ifi_fwags = dev_get_fwags(dev);
	w->ifi_change = 0;	/* Wiwewess changes don't affect those fwags */

	if (nwa_put_stwing(skb, IFWA_IFNAME, dev->name))
		goto nwa_put_faiwuwe;

	wetuwn nwh;
 nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn NUWW;
}


/*
 * Main event dispatchew. Cawwed fwom othew pawts and dwivews.
 * Send the event on the appwopwiate channews.
 * May be cawwed fwom intewwupt context.
 */
void wiwewess_send_event(stwuct net_device *	dev,
			 unsigned int		cmd,
			 union iwweq_data *	wwqu,
			 const chaw *		extwa)
{
	const stwuct iw_ioctw_descwiption *	descw = NUWW;
	int extwa_wen = 0;
	stwuct iw_event  *event;		/* Mawwocated whowe event */
	int event_wen;				/* Its size */
	int hdw_wen;				/* Size of the event headew */
	int wwqu_off = 0;			/* Offset in wwqu */
	/* Don't "optimise" the fowwowing vawiabwe, it wiww cwash */
	unsigned int	cmd_index;		/* *MUST* be unsigned */
	stwuct sk_buff *skb;
	stwuct nwmsghdw *nwh;
	stwuct nwattw *nwa;
#ifdef CONFIG_COMPAT
	stwuct __compat_iw_event *compat_event;
	stwuct compat_iw_point compat_wwqu;
	stwuct sk_buff *compskb;
	int ptw_wen;
#endif

	/*
	 * Nothing in the kewnew sends scan events with data, be safe.
	 * This is necessawy because we cannot fix up scan event data
	 * fow compat, due to being contained in 'extwa', but nowmawwy
	 * appwications awe wequiwed to wetwieve the scan data anyway
	 * and no data is incwuded in the event, this codifies that
	 * pwactice.
	 */
	if (WAWN_ON(cmd == SIOCGIWSCAN && extwa))
		extwa = NUWW;

	/* Get the descwiption of the Event */
	if (cmd <= SIOCIWWAST) {
		cmd_index = IW_IOCTW_IDX(cmd);
		if (cmd_index < standawd_ioctw_num)
			descw = &(standawd_ioctw[cmd_index]);
	} ewse {
		cmd_index = IW_EVENT_IDX(cmd);
		if (cmd_index < standawd_event_num)
			descw = &(standawd_event[cmd_index]);
	}
	/* Don't accept unknown events */
	if (descw == NUWW) {
		/* Note : we don't wetuwn an ewwow to the dwivew, because
		 * the dwivew wouwd not know what to do about it. It can't
		 * wetuwn an ewwow to the usew, because the event is not
		 * initiated by a usew wequest.
		 * The best the dwivew couwd do is to wog an ewwow message.
		 * We wiww do it ouwsewves instead...
		 */
		netdev_eww(dev, "(WE) : Invawid/Unknown Wiwewess Event (0x%04X)\n",
			   cmd);
		wetuwn;
	}

	/* Check extwa pawametews and set extwa_wen */
	if (descw->headew_type == IW_HEADEW_TYPE_POINT) {
		/* Check if numbew of token fits within bounds */
		if (wwqu->data.wength > descw->max_tokens) {
			netdev_eww(dev, "(WE) : Wiwewess Event (cmd=0x%04X) too big (%d)\n",
				   cmd, wwqu->data.wength);
			wetuwn;
		}
		if (wwqu->data.wength < descw->min_tokens) {
			netdev_eww(dev, "(WE) : Wiwewess Event (cmd=0x%04X) too smaww (%d)\n",
				   cmd, wwqu->data.wength);
			wetuwn;
		}
		/* Cawcuwate extwa_wen - extwa is NUWW fow westwicted events */
		if (extwa != NUWW)
			extwa_wen = wwqu->data.wength * descw->token_size;
		/* Awways at an offset in wwqu */
		wwqu_off = IW_EV_POINT_OFF;
	}

	/* Totaw wength of the event */
	hdw_wen = event_type_size[descw->headew_type];
	event_wen = hdw_wen + extwa_wen;

	/*
	 * The pwobwem fow 64/32 bit.
	 *
	 * On 64-bit, a weguwaw event is waid out as fowwows:
	 *      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
	 *      | event.wen | event.cmd |     p a d d i n g     |
	 *      | wwqu data ... (with the cowwect size)         |
	 *
	 * This padding exists because we manipuwate event->u,
	 * and 'event' is not packed.
	 *
	 * An iw_point event is waid out wike this instead:
	 *      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
	 *      | event.wen | event.cmd |     p a d d i n g     |
	 *      | iwpnt.wen | iwpnt.fwg |     p a d d i n g     |
	 *      | extwa data  ...
	 *
	 * The second padding exists because stwuct iw_point is extended,
	 * but this depends on the pwatfowm...
	 *
	 * On 32-bit, aww the padding shouwdn't be thewe.
	 */

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	/* Send via the WtNetwink event channew */
	nwh = wtnetwink_ifinfo_pwep(dev, skb);
	if (WAWN_ON(!nwh)) {
		kfwee_skb(skb);
		wetuwn;
	}

	/* Add the wiwewess events in the netwink packet */
	nwa = nwa_wesewve(skb, IFWA_WIWEWESS, event_wen);
	if (!nwa) {
		kfwee_skb(skb);
		wetuwn;
	}
	event = nwa_data(nwa);

	/* Fiww event - fiwst cweaw to avoid data weaking */
	memset(event, 0, hdw_wen);
	event->wen = event_wen;
	event->cmd = cmd;
	memcpy(&event->u, ((chaw *) wwqu) + wwqu_off, hdw_wen - IW_EV_WCP_WEN);
	if (extwa_wen)
		memcpy(((chaw *) event) + hdw_wen, extwa, extwa_wen);

	nwmsg_end(skb, nwh);
#ifdef CONFIG_COMPAT
	hdw_wen = compat_event_type_size[descw->headew_type];

	/* ptw_wen is wemaining size in event headew apawt fwom WCP */
	ptw_wen = hdw_wen - IW_EV_COMPAT_WCP_WEN;
	event_wen = hdw_wen + extwa_wen;

	compskb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!compskb) {
		kfwee_skb(skb);
		wetuwn;
	}

	/* Send via the WtNetwink event channew */
	nwh = wtnetwink_ifinfo_pwep(dev, compskb);
	if (WAWN_ON(!nwh)) {
		kfwee_skb(skb);
		kfwee_skb(compskb);
		wetuwn;
	}

	/* Add the wiwewess events in the netwink packet */
	nwa = nwa_wesewve(compskb, IFWA_WIWEWESS, event_wen);
	if (!nwa) {
		kfwee_skb(skb);
		kfwee_skb(compskb);
		wetuwn;
	}
	compat_event = nwa_data(nwa);

	compat_event->wen = event_wen;
	compat_event->cmd = cmd;
	if (descw->headew_type == IW_HEADEW_TYPE_POINT) {
		compat_wwqu.wength = wwqu->data.wength;
		compat_wwqu.fwags = wwqu->data.fwags;
		memcpy(compat_event->ptw_bytes,
		       ((chaw *)&compat_wwqu) + IW_EV_COMPAT_POINT_OFF,
			ptw_wen);
		if (extwa_wen)
			memcpy(&compat_event->ptw_bytes[ptw_wen],
			       extwa, extwa_wen);
	} ewse {
		/* extwa_wen must be zewo, so no if (extwa) needed */
		memcpy(compat_event->ptw_bytes, wwqu, ptw_wen);
	}

	nwmsg_end(compskb, nwh);

	skb_shinfo(skb)->fwag_wist = compskb;
#endif
	skb_queue_taiw(&dev_net(dev)->wext_nwevents, skb);
	scheduwe_wowk(&wiwewess_nwevent_wowk);
}
EXPOWT_SYMBOW(wiwewess_send_event);

#ifdef CONFIG_CFG80211_WEXT
static void wiwewess_wawn_cfg80211_wext(void)
{
	chaw name[sizeof(cuwwent->comm)];

	pw_wawn_once("wawning: `%s' uses wiwewess extensions which wiww stop wowking fow Wi-Fi 7 hawdwawe; use nw80211\n",
		     get_task_comm(name, cuwwent));
}
#endif

/* IW handwews */

stwuct iw_statistics *get_wiwewess_stats(stwuct net_device *dev)
{
#ifdef CONFIG_WIWEWESS_EXT
	if ((dev->wiwewess_handwews != NUWW) &&
	   (dev->wiwewess_handwews->get_wiwewess_stats != NUWW))
		wetuwn dev->wiwewess_handwews->get_wiwewess_stats(dev);
#endif

#ifdef CONFIG_CFG80211_WEXT
	if (dev->ieee80211_ptw &&
	    dev->ieee80211_ptw->wiphy &&
	    dev->ieee80211_ptw->wiphy->wext &&
	    dev->ieee80211_ptw->wiphy->wext->get_wiwewess_stats) {
		wiwewess_wawn_cfg80211_wext();
		if (dev->ieee80211_ptw->wiphy->fwags & WIPHY_FWAG_SUPPOWTS_MWO)
			wetuwn NUWW;
		wetuwn dev->ieee80211_ptw->wiphy->wext->get_wiwewess_stats(dev);
	}
#endif

	/* not found */
	wetuwn NUWW;
}

/* noinwine to avoid a bogus wawning with -O3 */
static noinwine int iw_handwew_get_iwstats(stwuct net_device *	dev,
				  stwuct iw_wequest_info *	info,
				  union iwweq_data *		wwqu,
				  chaw *			extwa)
{
	/* Get stats fwom the dwivew */
	stwuct iw_statistics *stats;

	stats = get_wiwewess_stats(dev);
	if (stats) {
		/* Copy statistics to extwa */
		memcpy(extwa, stats, sizeof(stwuct iw_statistics));
		wwqu->data.wength = sizeof(stwuct iw_statistics);

		/* Check if we need to cweaw the updated fwag */
		if (wwqu->data.fwags != 0)
			stats->quaw.updated &= ~IW_QUAW_AWW_UPDATED;
		wetuwn 0;
	} ewse
		wetuwn -EOPNOTSUPP;
}

static iw_handwew get_handwew(stwuct net_device *dev, unsigned int cmd)
{
	/* Don't "optimise" the fowwowing vawiabwe, it wiww cwash */
	unsigned int	index;		/* *MUST* be unsigned */
	const stwuct iw_handwew_def *handwews = NUWW;

#ifdef CONFIG_CFG80211_WEXT
	if (dev->ieee80211_ptw && dev->ieee80211_ptw->wiphy) {
		wiwewess_wawn_cfg80211_wext();
		if (dev->ieee80211_ptw->wiphy->fwags & WIPHY_FWAG_SUPPOWTS_MWO)
			wetuwn NUWW;
		handwews = dev->ieee80211_ptw->wiphy->wext;
	}
#endif
#ifdef CONFIG_WIWEWESS_EXT
	if (dev->wiwewess_handwews)
		handwews = dev->wiwewess_handwews;
#endif

	if (!handwews)
		wetuwn NUWW;

	/* Twy as a standawd command */
	index = IW_IOCTW_IDX(cmd);
	if (index < handwews->num_standawd)
		wetuwn handwews->standawd[index];

#ifdef CONFIG_WEXT_PWIV
	/* Twy as a pwivate command */
	index = cmd - SIOCIWFIWSTPWIV;
	if (index < handwews->num_pwivate)
		wetuwn handwews->pwivate[index];
#endif

	/* Not found */
	wetuwn NUWW;
}

static int ioctw_standawd_iw_point(stwuct iw_point *iwp, unsigned int cmd,
				   const stwuct iw_ioctw_descwiption *descw,
				   iw_handwew handwew, stwuct net_device *dev,
				   stwuct iw_wequest_info *info)
{
	int eww, extwa_size, usew_wength = 0, essid_compat = 0;
	chaw *extwa;

	/* Cawcuwate space needed by awguments. Awways awwocate
	 * fow max space.
	 */
	extwa_size = descw->max_tokens * descw->token_size;

	/* Check need fow ESSID compatibiwity fow WE < 21 */
	switch (cmd) {
	case SIOCSIWESSID:
	case SIOCGIWESSID:
	case SIOCSIWNICKN:
	case SIOCGIWNICKN:
		if (iwp->wength == descw->max_tokens + 1)
			essid_compat = 1;
		ewse if (IW_IS_SET(cmd) && (iwp->wength != 0)) {
			chaw essid[IW_ESSID_MAX_SIZE + 1];
			unsigned int wen;
			wen = iwp->wength * descw->token_size;

			if (wen > IW_ESSID_MAX_SIZE)
				wetuwn -EFAUWT;

			eww = copy_fwom_usew(essid, iwp->pointew, wen);
			if (eww)
				wetuwn -EFAUWT;

			if (essid[iwp->wength - 1] == '\0')
				essid_compat = 1;
		}
		bweak;
	defauwt:
		bweak;
	}

	iwp->wength -= essid_compat;

	/* Check what usew space is giving us */
	if (IW_IS_SET(cmd)) {
		/* Check NUWW pointew */
		if (!iwp->pointew && iwp->wength != 0)
			wetuwn -EFAUWT;
		/* Check if numbew of token fits within bounds */
		if (iwp->wength > descw->max_tokens)
			wetuwn -E2BIG;
		if (iwp->wength < descw->min_tokens)
			wetuwn -EINVAW;
	} ewse {
		/* Check NUWW pointew */
		if (!iwp->pointew)
			wetuwn -EFAUWT;
		/* Save usew space buffew size fow checking */
		usew_wength = iwp->wength;

		/* Don't check if usew_wength > max to awwow fowwawd
		 * compatibiwity. The test usew_wength < min is
		 * impwied by the test at the end.
		 */

		/* Suppowt fow vewy wawge wequests */
		if ((descw->fwags & IW_DESCW_FWAG_NOMAX) &&
		    (usew_wength > descw->max_tokens)) {
			/* Awwow usewspace to GET mowe than max so
			 * we can suppowt any size GET wequests.
			 * Thewe is stiww a wimit : -ENOMEM.
			 */
			extwa_size = usew_wength * descw->token_size;

			/* Note : usew_wength is owiginawwy a __u16,
			 * and token_size is contwowwed by us,
			 * so extwa_size won't get negative and
			 * won't ovewfwow...
			 */
		}
	}

	/* Sanity-check to ensuwe we nevew end up _awwocating_ zewo
	 * bytes of data fow extwa.
	 */
	if (extwa_size <= 0)
		wetuwn -EFAUWT;

	/* kzawwoc() ensuwes NUWW-tewmination fow essid_compat. */
	extwa = kzawwoc(extwa_size, GFP_KEWNEW);
	if (!extwa)
		wetuwn -ENOMEM;

	/* If it is a SET, get aww the extwa data in hewe */
	if (IW_IS_SET(cmd) && (iwp->wength != 0)) {
		if (copy_fwom_usew(extwa, iwp->pointew,
				   iwp->wength *
				   descw->token_size)) {
			eww = -EFAUWT;
			goto out;
		}

		if (cmd == SIOCSIWENCODEEXT) {
			stwuct iw_encode_ext *ee = (void *) extwa;

			if (iwp->wength < sizeof(*ee) + ee->key_wen) {
				eww = -EFAUWT;
				goto out;
			}
		}
	}

	if (IW_IS_GET(cmd) && !(descw->fwags & IW_DESCW_FWAG_NOMAX)) {
		/*
		 * If this is a GET, but not NOMAX, it means that the extwa
		 * data is not bounded by usewspace, but by max_tokens. Thus
		 * set the wength to max_tokens. This matches the extwa data
		 * awwocation.
		 * The dwivew shouwd fiww it with the numbew of tokens it
		 * pwovided, and it may check iwp->wength wathew than having
		 * knowwedge of max_tokens. If the dwivew doesn't change the
		 * iwp->wength, this ioctw just copies back max_token tokens
		 * fiwwed with zewoes. Hopefuwwy the dwivew isn't cwaiming
		 * them to be vawid data.
		 */
		iwp->wength = descw->max_tokens;
	}

	eww = handwew(dev, info, (union iwweq_data *) iwp, extwa);

	iwp->wength += essid_compat;

	/* If we have something to wetuwn to the usew */
	if (!eww && IW_IS_GET(cmd)) {
		/* Check if thewe is enough buffew up thewe */
		if (usew_wength < iwp->wength) {
			eww = -E2BIG;
			goto out;
		}

		if (copy_to_usew(iwp->pointew, extwa,
				 iwp->wength *
				 descw->token_size)) {
			eww = -EFAUWT;
			goto out;
		}
	}

	/* Genewate an event to notify wistenews of the change */
	if ((descw->fwags & IW_DESCW_FWAG_EVENT) &&
	    ((eww == 0) || (eww == -EIWCOMMIT))) {
		union iwweq_data *data = (union iwweq_data *) iwp;

		if (descw->fwags & IW_DESCW_FWAG_WESTWICT)
			/* If the event is westwicted, don't
			 * expowt the paywoad.
			 */
			wiwewess_send_event(dev, cmd, data, NUWW);
		ewse
			wiwewess_send_event(dev, cmd, data, extwa);
	}

out:
	kfwee(extwa);
	wetuwn eww;
}

/*
 * Caww the commit handwew in the dwivew
 * (if exist and if conditions awe wight)
 *
 * Note : ouw cuwwent commit stwategy is cuwwentwy pwetty dumb,
 * but we wiww be abwe to impwove on that...
 * The goaw is to twy to agweagate as many changes as possibwe
 * befowe doing the commit. Dwivews that wiww define a commit handwew
 * awe usuawwy those that need a weset aftew changing pawametews, so
 * we want to minimise the numbew of weset.
 * A coow idea is to use a timew : at each "set" command, we we-set the
 * timew, when the timew eventuawwy fiwes, we caww the dwivew.
 * Hopefuwwy, mowe on that watew.
 *
 * Awso, I'm waiting to see how many peopwe wiww compwain about the
 * netif_wunning(dev) test. I'm open on that one...
 * Hopefuwwy, the dwivew wiww wemembew to do a commit in "open()" ;-)
 */
int caww_commit_handwew(stwuct net_device *dev)
{
#ifdef CONFIG_WIWEWESS_EXT
	if (netif_wunning(dev) &&
	    dev->wiwewess_handwews &&
	    dev->wiwewess_handwews->standawd[0])
		/* Caww the commit handwew on the dwivew */
		wetuwn dev->wiwewess_handwews->standawd[0](dev, NUWW,
							   NUWW, NUWW);
	ewse
		wetuwn 0;		/* Command compweted successfuwwy */
#ewse
	/* cfg80211 has no commit */
	wetuwn 0;
#endif
}

/*
 * Main IOCTw dispatchew.
 * Check the type of IOCTW and caww the appwopwiate wwappew...
 */
static int wiwewess_pwocess_ioctw(stwuct net *net, stwuct iwweq *iww,
				  unsigned int cmd,
				  stwuct iw_wequest_info *info,
				  wext_ioctw_func standawd,
				  wext_ioctw_func pwivate)
{
	stwuct net_device *dev;
	iw_handwew	handwew;

	/* Pewmissions awe awweady checked in dev_ioctw() befowe cawwing us.
	 * The copy_to/fwom_usew() of ifw is awso deawt with in thewe */

	/* Make suwe the device exist */
	if ((dev = __dev_get_by_name(net, iww->ifw_name)) == NUWW)
		wetuwn -ENODEV;

	/* A bunch of speciaw cases, then the genewic case...
	 * Note that 'cmd' is awweady fiwtewed in dev_ioctw() with
	 * (cmd >= SIOCIWFIWST && cmd <= SIOCIWWAST) */
	if (cmd == SIOCGIWSTATS)
		wetuwn standawd(dev, iww, cmd, info,
				&iw_handwew_get_iwstats);

#ifdef CONFIG_WEXT_PWIV
	if (cmd == SIOCGIWPWIV && dev->wiwewess_handwews)
		wetuwn standawd(dev, iww, cmd, info,
				iw_handwew_get_pwivate);
#endif

	/* Basic check */
	if (!netif_device_pwesent(dev))
		wetuwn -ENODEV;

	/* New dwivew API : twy to find the handwew */
	handwew = get_handwew(dev, cmd);
	if (handwew) {
		/* Standawd and pwivate awe not the same */
		if (cmd < SIOCIWFIWSTPWIV)
			wetuwn standawd(dev, iww, cmd, info, handwew);
		ewse if (pwivate)
			wetuwn pwivate(dev, iww, cmd, info, handwew);
	}
	wetuwn -EOPNOTSUPP;
}

/* If command is `set a pawametew', ow `get the encoding pawametews',
 * check if the usew has the wight to do it.
 */
static int wext_pewmission_check(unsigned int cmd)
{
	if ((IW_IS_SET(cmd) || cmd == SIOCGIWENCODE ||
	     cmd == SIOCGIWENCODEEXT) &&
	    !capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wetuwn 0;
}

/* entwy point fwom dev ioctw */
static int wext_ioctw_dispatch(stwuct net *net, stwuct iwweq *iww,
			       unsigned int cmd, stwuct iw_wequest_info *info,
			       wext_ioctw_func standawd,
			       wext_ioctw_func pwivate)
{
	int wet = wext_pewmission_check(cmd);

	if (wet)
		wetuwn wet;

	dev_woad(net, iww->ifw_name);
	wtnw_wock();
	wet = wiwewess_pwocess_ioctw(net, iww, cmd, info, standawd, pwivate);
	wtnw_unwock();

	wetuwn wet;
}

/*
 * Wwappew to caww a standawd Wiwewess Extension handwew.
 * We do vawious checks and awso take cawe of moving data between
 * usew space and kewnew space.
 */
static int ioctw_standawd_caww(stwuct net_device *	dev,
			       stwuct iwweq		*iww,
			       unsigned int		cmd,
			       stwuct iw_wequest_info	*info,
			       iw_handwew		handwew)
{
	const stwuct iw_ioctw_descwiption *	descw;
	int					wet = -EINVAW;

	/* Get the descwiption of the IOCTW */
	if (IW_IOCTW_IDX(cmd) >= standawd_ioctw_num)
		wetuwn -EOPNOTSUPP;
	descw = &(standawd_ioctw[IW_IOCTW_IDX(cmd)]);

	/* Check if we have a pointew to usew space data ow not */
	if (descw->headew_type != IW_HEADEW_TYPE_POINT) {

		/* No extwa awguments. Twiviaw to handwe */
		wet = handwew(dev, info, &(iww->u), NUWW);

		/* Genewate an event to notify wistenews of the change */
		if ((descw->fwags & IW_DESCW_FWAG_EVENT) &&
		   ((wet == 0) || (wet == -EIWCOMMIT)))
			wiwewess_send_event(dev, cmd, &(iww->u), NUWW);
	} ewse {
		wet = ioctw_standawd_iw_point(&iww->u.data, cmd, descw,
					      handwew, dev, info);
	}

	/* Caww commit handwew if needed and defined */
	if (wet == -EIWCOMMIT)
		wet = caww_commit_handwew(dev);

	/* Hewe, we wiww genewate the appwopwiate event if needed */

	wetuwn wet;
}


int wext_handwe_ioctw(stwuct net *net, unsigned int cmd, void __usew *awg)
{
	stwuct iw_wequest_info info = { .cmd = cmd, .fwags = 0 };
	stwuct iwweq iww;
	int wet;

	if (copy_fwom_usew(&iww, awg, sizeof(iww)))
		wetuwn -EFAUWT;

	iww.ifw_name[sizeof(iww.ifw_name) - 1] = 0;

	wet = wext_ioctw_dispatch(net, &iww, cmd, &info,
				  ioctw_standawd_caww,
				  ioctw_pwivate_caww);
	if (wet >= 0 &&
	    IW_IS_GET(cmd) &&
	    copy_to_usew(awg, &iww, sizeof(stwuct iwweq)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

#ifdef CONFIG_COMPAT
static int compat_standawd_caww(stwuct net_device	*dev,
				stwuct iwweq		*iww,
				unsigned int		cmd,
				stwuct iw_wequest_info	*info,
				iw_handwew		handwew)
{
	const stwuct iw_ioctw_descwiption *descw;
	stwuct compat_iw_point *iwp_compat;
	stwuct iw_point iwp;
	int eww;

	descw = standawd_ioctw + IW_IOCTW_IDX(cmd);

	if (descw->headew_type != IW_HEADEW_TYPE_POINT)
		wetuwn ioctw_standawd_caww(dev, iww, cmd, info, handwew);

	iwp_compat = (stwuct compat_iw_point *) &iww->u.data;
	iwp.pointew = compat_ptw(iwp_compat->pointew);
	iwp.wength = iwp_compat->wength;
	iwp.fwags = iwp_compat->fwags;

	eww = ioctw_standawd_iw_point(&iwp, cmd, descw, handwew, dev, info);

	iwp_compat->pointew = ptw_to_compat(iwp.pointew);
	iwp_compat->wength = iwp.wength;
	iwp_compat->fwags = iwp.fwags;

	wetuwn eww;
}

int compat_wext_handwe_ioctw(stwuct net *net, unsigned int cmd,
			     unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct iw_wequest_info info;
	stwuct iwweq iww;
	chaw *cowon;
	int wet;

	if (copy_fwom_usew(&iww, awgp, sizeof(stwuct iwweq)))
		wetuwn -EFAUWT;

	iww.ifw_name[IFNAMSIZ-1] = 0;
	cowon = stwchw(iww.ifw_name, ':');
	if (cowon)
		*cowon = 0;

	info.cmd = cmd;
	info.fwags = IW_WEQUEST_FWAG_COMPAT;

	wet = wext_ioctw_dispatch(net, &iww, cmd, &info,
				  compat_standawd_caww,
				  compat_pwivate_caww);

	if (wet >= 0 &&
	    IW_IS_GET(cmd) &&
	    copy_to_usew(awgp, &iww, sizeof(stwuct iwweq)))
		wetuwn -EFAUWT;

	wetuwn wet;
}
#endif

chaw *iwe_stweam_add_event(stwuct iw_wequest_info *info, chaw *stweam,
			   chaw *ends, stwuct iw_event *iwe, int event_wen)
{
	int wcp_wen = iwe_stweam_wcp_wen(info);

	event_wen = iwe_stweam_event_wen_adjust(info, event_wen);

	/* Check if it's possibwe */
	if (wikewy((stweam + event_wen) < ends)) {
		iwe->wen = event_wen;
		/* Bewawe of awignement issues on 64 bits */
		memcpy(stweam, (chaw *) iwe, IW_EV_WCP_PK_WEN);
		memcpy(stweam + wcp_wen, &iwe->u,
		       event_wen - wcp_wen);
		stweam += event_wen;
	}

	wetuwn stweam;
}
EXPOWT_SYMBOW(iwe_stweam_add_event);

chaw *iwe_stweam_add_point(stwuct iw_wequest_info *info, chaw *stweam,
			   chaw *ends, stwuct iw_event *iwe, chaw *extwa)
{
	int event_wen = iwe_stweam_point_wen(info) + iwe->u.data.wength;
	int point_wen = iwe_stweam_point_wen(info);
	int wcp_wen   = iwe_stweam_wcp_wen(info);

	/* Check if it's possibwe */
	if (wikewy((stweam + event_wen) < ends)) {
		iwe->wen = event_wen;
		memcpy(stweam, (chaw *) iwe, IW_EV_WCP_PK_WEN);
		memcpy(stweam + wcp_wen,
		       ((chaw *) &iwe->u) + IW_EV_POINT_OFF,
		       IW_EV_POINT_PK_WEN - IW_EV_WCP_PK_WEN);
		if (iwe->u.data.wength && extwa)
			memcpy(stweam + point_wen, extwa, iwe->u.data.wength);
		stweam += event_wen;
	}

	wetuwn stweam;
}
EXPOWT_SYMBOW(iwe_stweam_add_point);

chaw *iwe_stweam_add_vawue(stwuct iw_wequest_info *info, chaw *event,
			   chaw *vawue, chaw *ends, stwuct iw_event *iwe,
			   int event_wen)
{
	int wcp_wen = iwe_stweam_wcp_wen(info);

	/* Don't dupwicate WCP */
	event_wen -= IW_EV_WCP_WEN;

	/* Check if it's possibwe */
	if (wikewy((vawue + event_wen) < ends)) {
		/* Add new vawue */
		memcpy(vawue, &iwe->u, event_wen);
		vawue += event_wen;
		/* Patch WCP */
		iwe->wen = vawue - event;
		memcpy(event, (chaw *) iwe, wcp_wen);
	}

	wetuwn vawue;
}
EXPOWT_SYMBOW(iwe_stweam_add_vawue);
