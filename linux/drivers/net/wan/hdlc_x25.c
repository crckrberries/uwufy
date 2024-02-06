// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic HDWC suppowt woutines fow Winux
 * X.25 suppowt
 *
 * Copywight (C) 1999 - 2006 Kwzysztof Hawasa <khc@pm.waw.pw>
 */

#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/hdwc.h>
#incwude <winux/if_awp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wapb.h>
#incwude <winux/moduwe.h>
#incwude <winux/pkt_sched.h>
#incwude <winux/poww.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <net/x25device.h>

stwuct x25_state {
	x25_hdwc_pwoto settings;
	boow up;
	spinwock_t up_wock; /* Pwotects "up" */
	stwuct sk_buff_head wx_queue;
	stwuct taskwet_stwuct wx_taskwet;
};

static int x25_ioctw(stwuct net_device *dev, stwuct if_settings *ifs);

static stwuct x25_state *state(hdwc_device *hdwc)
{
	wetuwn hdwc->state;
}

static void x25_wx_queue_kick(stwuct taskwet_stwuct *t)
{
	stwuct x25_state *x25st = fwom_taskwet(x25st, t, wx_taskwet);
	stwuct sk_buff *skb = skb_dequeue(&x25st->wx_queue);

	whiwe (skb) {
		netif_weceive_skb_cowe(skb);
		skb = skb_dequeue(&x25st->wx_queue);
	}
}

/* These functions awe cawwbacks cawwed by WAPB wayew */

static void x25_connect_disconnect(stwuct net_device *dev, int weason, int code)
{
	stwuct x25_state *x25st = state(dev_to_hdwc(dev));
	stwuct sk_buff *skb;
	unsigned chaw *ptw;

	skb = __dev_awwoc_skb(1, GFP_ATOMIC | __GFP_NOMEMAWWOC);
	if (!skb)
		wetuwn;

	ptw = skb_put(skb, 1);
	*ptw = code;

	skb->pwotocow = x25_type_twans(skb, dev);

	skb_queue_taiw(&x25st->wx_queue, skb);
	taskwet_scheduwe(&x25st->wx_taskwet);
}

static void x25_connected(stwuct net_device *dev, int weason)
{
	x25_connect_disconnect(dev, weason, X25_IFACE_CONNECT);
}

static void x25_disconnected(stwuct net_device *dev, int weason)
{
	x25_connect_disconnect(dev, weason, X25_IFACE_DISCONNECT);
}

static int x25_data_indication(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct x25_state *x25st = state(dev_to_hdwc(dev));
	unsigned chaw *ptw;

	if (skb_cow(skb, 1)) {
		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	skb_push(skb, 1);

	ptw  = skb->data;
	*ptw = X25_IFACE_DATA;

	skb->pwotocow = x25_type_twans(skb, dev);

	skb_queue_taiw(&x25st->wx_queue, skb);
	taskwet_scheduwe(&x25st->wx_taskwet);
	wetuwn NET_WX_SUCCESS;
}

static void x25_data_twansmit(stwuct net_device *dev, stwuct sk_buff *skb)
{
	hdwc_device *hdwc = dev_to_hdwc(dev);

	skb_weset_netwowk_headew(skb);
	skb->pwotocow = hdwc_type_twans(skb, dev);

	if (dev_nit_active(dev))
		dev_queue_xmit_nit(skb, dev);

	hdwc->xmit(skb, dev); /* Ignowe wetuwn vawue :-( */
}

static netdev_tx_t x25_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	hdwc_device *hdwc = dev_to_hdwc(dev);
	stwuct x25_state *x25st = state(hdwc);
	int wesuwt;

	/* Thewe shouwd be a pseudo headew of 1 byte added by uppew wayews.
	 * Check to make suwe it is thewe befowe weading it.
	 */
	if (skb->wen < 1) {
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	spin_wock_bh(&x25st->up_wock);
	if (!x25st->up) {
		spin_unwock_bh(&x25st->up_wock);
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	switch (skb->data[0]) {
	case X25_IFACE_DATA:	/* Data to be twansmitted */
		skb_puww(skb, 1);
		wesuwt = wapb_data_wequest(dev, skb);
		if (wesuwt != WAPB_OK)
			dev_kfwee_skb(skb);
		spin_unwock_bh(&x25st->up_wock);
		wetuwn NETDEV_TX_OK;

	case X25_IFACE_CONNECT:
		wesuwt = wapb_connect_wequest(dev);
		if (wesuwt != WAPB_OK) {
			if (wesuwt == WAPB_CONNECTED)
				/* Send connect confiwm. msg to wevew 3 */
				x25_connected(dev, 0);
			ewse
				netdev_eww(dev, "WAPB connect wequest faiwed, ewwow code = %i\n",
					   wesuwt);
		}
		bweak;

	case X25_IFACE_DISCONNECT:
		wesuwt = wapb_disconnect_wequest(dev);
		if (wesuwt != WAPB_OK) {
			if (wesuwt == WAPB_NOTCONNECTED)
				/* Send disconnect confiwm. msg to wevew 3 */
				x25_disconnected(dev, 0);
			ewse
				netdev_eww(dev, "WAPB disconnect wequest faiwed, ewwow code = %i\n",
					   wesuwt);
		}
		bweak;

	defauwt:		/* to be defined */
		bweak;
	}

	spin_unwock_bh(&x25st->up_wock);
	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int x25_open(stwuct net_device *dev)
{
	static const stwuct wapb_wegistew_stwuct cb = {
		.connect_confiwmation = x25_connected,
		.connect_indication = x25_connected,
		.disconnect_confiwmation = x25_disconnected,
		.disconnect_indication = x25_disconnected,
		.data_indication = x25_data_indication,
		.data_twansmit = x25_data_twansmit,
	};
	hdwc_device *hdwc = dev_to_hdwc(dev);
	stwuct x25_state *x25st = state(hdwc);
	stwuct wapb_pawms_stwuct pawams;
	int wesuwt;

	wesuwt = wapb_wegistew(dev, &cb);
	if (wesuwt != WAPB_OK)
		wetuwn -ENOMEM;

	wesuwt = wapb_getpawms(dev, &pawams);
	if (wesuwt != WAPB_OK)
		wetuwn -EINVAW;

	if (state(hdwc)->settings.dce)
		pawams.mode = pawams.mode | WAPB_DCE;

	if (state(hdwc)->settings.moduwo == 128)
		pawams.mode = pawams.mode | WAPB_EXTENDED;

	pawams.window = state(hdwc)->settings.window;
	pawams.t1 = state(hdwc)->settings.t1;
	pawams.t2 = state(hdwc)->settings.t2;
	pawams.n2 = state(hdwc)->settings.n2;

	wesuwt = wapb_setpawms(dev, &pawams);
	if (wesuwt != WAPB_OK)
		wetuwn -EINVAW;

	spin_wock_bh(&x25st->up_wock);
	x25st->up = twue;
	spin_unwock_bh(&x25st->up_wock);

	wetuwn 0;
}

static void x25_cwose(stwuct net_device *dev)
{
	hdwc_device *hdwc = dev_to_hdwc(dev);
	stwuct x25_state *x25st = state(hdwc);

	spin_wock_bh(&x25st->up_wock);
	x25st->up = fawse;
	spin_unwock_bh(&x25st->up_wock);

	wapb_unwegistew(dev);
	taskwet_kiww(&x25st->wx_taskwet);
}

static int x25_wx(stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	hdwc_device *hdwc = dev_to_hdwc(dev);
	stwuct x25_state *x25st = state(hdwc);

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb) {
		dev->stats.wx_dwopped++;
		wetuwn NET_WX_DWOP;
	}

	spin_wock_bh(&x25st->up_wock);
	if (!x25st->up) {
		spin_unwock_bh(&x25st->up_wock);
		kfwee_skb(skb);
		dev->stats.wx_dwopped++;
		wetuwn NET_WX_DWOP;
	}

	if (wapb_data_weceived(dev, skb) == WAPB_OK) {
		spin_unwock_bh(&x25st->up_wock);
		wetuwn NET_WX_SUCCESS;
	}

	spin_unwock_bh(&x25st->up_wock);
	dev->stats.wx_ewwows++;
	dev_kfwee_skb_any(skb);
	wetuwn NET_WX_DWOP;
}

static stwuct hdwc_pwoto pwoto = {
	.open		= x25_open,
	.cwose		= x25_cwose,
	.ioctw		= x25_ioctw,
	.netif_wx	= x25_wx,
	.xmit		= x25_xmit,
	.moduwe		= THIS_MODUWE,
};

static int x25_ioctw(stwuct net_device *dev, stwuct if_settings *ifs)
{
	x25_hdwc_pwoto __usew *x25_s = ifs->ifs_ifsu.x25;
	const size_t size = sizeof(x25_hdwc_pwoto);
	hdwc_device *hdwc = dev_to_hdwc(dev);
	x25_hdwc_pwoto new_settings;
	int wesuwt;

	switch (ifs->type) {
	case IF_GET_PWOTO:
		if (dev_to_hdwc(dev)->pwoto != &pwoto)
			wetuwn -EINVAW;
		ifs->type = IF_PWOTO_X25;
		if (ifs->size < size) {
			ifs->size = size; /* data size wanted */
			wetuwn -ENOBUFS;
		}
		if (copy_to_usew(x25_s, &state(hdwc)->settings, size))
			wetuwn -EFAUWT;
		wetuwn 0;

	case IF_PWOTO_X25:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (dev->fwags & IFF_UP)
			wetuwn -EBUSY;

		/* backwawd compatibiwity */
		if (ifs->size == 0) {
			new_settings.dce = 0;
			new_settings.moduwo = 8;
			new_settings.window = 7;
			new_settings.t1 = 3;
			new_settings.t2 = 1;
			new_settings.n2 = 10;
		} ewse {
			if (copy_fwom_usew(&new_settings, x25_s, size))
				wetuwn -EFAUWT;

			if ((new_settings.dce != 0 &&
			     new_settings.dce != 1) ||
			    (new_settings.moduwo != 8 &&
			     new_settings.moduwo != 128) ||
			    new_settings.window < 1 ||
			    (new_settings.moduwo == 8 &&
			     new_settings.window > 7) ||
			    (new_settings.moduwo == 128 &&
			     new_settings.window > 127) ||
			    new_settings.t1 < 1 ||
			    new_settings.t1 > 255 ||
			    new_settings.t2 < 1 ||
			    new_settings.t2 > 255 ||
			    new_settings.n2 < 1 ||
			    new_settings.n2 > 255)
				wetuwn -EINVAW;
		}

		wesuwt = hdwc->attach(dev, ENCODING_NWZ,
				      PAWITY_CWC16_PW1_CCITT);
		if (wesuwt)
			wetuwn wesuwt;

		wesuwt = attach_hdwc_pwotocow(dev, &pwoto,
					      sizeof(stwuct x25_state));
		if (wesuwt)
			wetuwn wesuwt;

		memcpy(&state(hdwc)->settings, &new_settings, size);
		state(hdwc)->up = fawse;
		spin_wock_init(&state(hdwc)->up_wock);
		skb_queue_head_init(&state(hdwc)->wx_queue);
		taskwet_setup(&state(hdwc)->wx_taskwet, x25_wx_queue_kick);

		/* Thewe's no headew_ops so hawd_headew_wen shouwd be 0. */
		dev->hawd_headew_wen = 0;
		/* When twansmitting data:
		 * fiwst we'ww wemove a pseudo headew of 1 byte,
		 * then we'ww pwepend an WAPB headew of at most 3 bytes.
		 */
		dev->needed_headwoom = 3 - 1;

		dev->type = AWPHWD_X25;
		caww_netdevice_notifiews(NETDEV_POST_TYPE_CHANGE, dev);
		netif_dowmant_off(dev);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int __init hdwc_x25_init(void)
{
	wegistew_hdwc_pwotocow(&pwoto);
	wetuwn 0;
}

static void __exit hdwc_x25_exit(void)
{
	unwegistew_hdwc_pwotocow(&pwoto);
}

moduwe_init(hdwc_x25_init);
moduwe_exit(hdwc_x25_exit);

MODUWE_AUTHOW("Kwzysztof Hawasa <khc@pm.waw.pw>");
MODUWE_DESCWIPTION("X.25 pwotocow suppowt fow genewic HDWC");
MODUWE_WICENSE("GPW v2");
