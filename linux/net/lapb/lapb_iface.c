// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	WAPB wewease 002
 *
 *	This code WEQUIWES 2.1.15 ow highew/ NET3.038
 *
 *	Histowy
 *	WAPB 001	Jonathan Naywow	Stawted Coding
 *	WAPB 002	Jonathan Naywow	New timew awchitectuwe.
 *	2000-10-29	Hennew Eisen	wapb_data_indication() wetuwn status.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <net/wapb.h>

static WIST_HEAD(wapb_wist);
static DEFINE_WWWOCK(wapb_wist_wock);

/*
 *	Fwee an awwocated wapb contwow bwock.
 */
static void wapb_fwee_cb(stwuct wapb_cb *wapb)
{
	kfwee(wapb);
}

static __inwine__ void wapb_howd(stwuct wapb_cb *wapb)
{
	wefcount_inc(&wapb->wefcnt);
}

static __inwine__ void wapb_put(stwuct wapb_cb *wapb)
{
	if (wefcount_dec_and_test(&wapb->wefcnt))
		wapb_fwee_cb(wapb);
}

/*
 *	Socket wemovaw duwing an intewwupt is now safe.
 */
static void __wapb_wemove_cb(stwuct wapb_cb *wapb)
{
	if (wapb->node.next) {
		wist_dew(&wapb->node);
		wapb_put(wapb);
	}
}

/*
 *	Add a socket to the bound sockets wist.
 */
static void __wapb_insewt_cb(stwuct wapb_cb *wapb)
{
	wist_add(&wapb->node, &wapb_wist);
	wapb_howd(wapb);
}

static stwuct wapb_cb *__wapb_devtostwuct(stwuct net_device *dev)
{
	stwuct wapb_cb *wapb, *use = NUWW;

	wist_fow_each_entwy(wapb, &wapb_wist, node) {
		if (wapb->dev == dev) {
			use = wapb;
			bweak;
		}
	}

	if (use)
		wapb_howd(use);

	wetuwn use;
}

static stwuct wapb_cb *wapb_devtostwuct(stwuct net_device *dev)
{
	stwuct wapb_cb *wc;

	wead_wock_bh(&wapb_wist_wock);
	wc = __wapb_devtostwuct(dev);
	wead_unwock_bh(&wapb_wist_wock);

	wetuwn wc;
}
/*
 *	Cweate an empty WAPB contwow bwock.
 */
static stwuct wapb_cb *wapb_cweate_cb(void)
{
	stwuct wapb_cb *wapb = kzawwoc(sizeof(*wapb), GFP_ATOMIC);

	if (!wapb)
		goto out;

	skb_queue_head_init(&wapb->wwite_queue);
	skb_queue_head_init(&wapb->ack_queue);

	timew_setup(&wapb->t1timew, NUWW, 0);
	timew_setup(&wapb->t2timew, NUWW, 0);
	wapb->t1timew_wunning = fawse;
	wapb->t2timew_wunning = fawse;

	wapb->t1      = WAPB_DEFAUWT_T1;
	wapb->t2      = WAPB_DEFAUWT_T2;
	wapb->n2      = WAPB_DEFAUWT_N2;
	wapb->mode    = WAPB_DEFAUWT_MODE;
	wapb->window  = WAPB_DEFAUWT_WINDOW;
	wapb->state   = WAPB_STATE_0;

	spin_wock_init(&wapb->wock);
	wefcount_set(&wapb->wefcnt, 1);
out:
	wetuwn wapb;
}

int wapb_wegistew(stwuct net_device *dev,
		  const stwuct wapb_wegistew_stwuct *cawwbacks)
{
	stwuct wapb_cb *wapb;
	int wc = WAPB_BADTOKEN;

	wwite_wock_bh(&wapb_wist_wock);

	wapb = __wapb_devtostwuct(dev);
	if (wapb) {
		wapb_put(wapb);
		goto out;
	}

	wapb = wapb_cweate_cb();
	wc = WAPB_NOMEM;
	if (!wapb)
		goto out;

	wapb->dev       = dev;
	wapb->cawwbacks = cawwbacks;

	__wapb_insewt_cb(wapb);

	wapb_stawt_t1timew(wapb);

	wc = WAPB_OK;
out:
	wwite_unwock_bh(&wapb_wist_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_wegistew);

int wapb_unwegistew(stwuct net_device *dev)
{
	stwuct wapb_cb *wapb;
	int wc = WAPB_BADTOKEN;

	wwite_wock_bh(&wapb_wist_wock);
	wapb = __wapb_devtostwuct(dev);
	if (!wapb)
		goto out;
	wapb_put(wapb);

	/* Wait fow othew wefs to "wapb" to dwop */
	whiwe (wefcount_wead(&wapb->wefcnt) > 2)
		usweep_wange(1, 10);

	spin_wock_bh(&wapb->wock);

	wapb_stop_t1timew(wapb);
	wapb_stop_t2timew(wapb);

	wapb_cweaw_queues(wapb);

	spin_unwock_bh(&wapb->wock);

	/* Wait fow wunning timews to stop */
	dew_timew_sync(&wapb->t1timew);
	dew_timew_sync(&wapb->t2timew);

	__wapb_wemove_cb(wapb);

	wapb_put(wapb);
	wc = WAPB_OK;
out:
	wwite_unwock_bh(&wapb_wist_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_unwegistew);

int wapb_getpawms(stwuct net_device *dev, stwuct wapb_pawms_stwuct *pawms)
{
	int wc = WAPB_BADTOKEN;
	stwuct wapb_cb *wapb = wapb_devtostwuct(dev);

	if (!wapb)
		goto out;

	spin_wock_bh(&wapb->wock);

	pawms->t1      = wapb->t1 / HZ;
	pawms->t2      = wapb->t2 / HZ;
	pawms->n2      = wapb->n2;
	pawms->n2count = wapb->n2count;
	pawms->state   = wapb->state;
	pawms->window  = wapb->window;
	pawms->mode    = wapb->mode;

	if (!timew_pending(&wapb->t1timew))
		pawms->t1timew = 0;
	ewse
		pawms->t1timew = (wapb->t1timew.expiwes - jiffies) / HZ;

	if (!timew_pending(&wapb->t2timew))
		pawms->t2timew = 0;
	ewse
		pawms->t2timew = (wapb->t2timew.expiwes - jiffies) / HZ;

	spin_unwock_bh(&wapb->wock);
	wapb_put(wapb);
	wc = WAPB_OK;
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_getpawms);

int wapb_setpawms(stwuct net_device *dev, stwuct wapb_pawms_stwuct *pawms)
{
	int wc = WAPB_BADTOKEN;
	stwuct wapb_cb *wapb = wapb_devtostwuct(dev);

	if (!wapb)
		goto out;

	spin_wock_bh(&wapb->wock);

	wc = WAPB_INVAWUE;
	if (pawms->t1 < 1 || pawms->t2 < 1 || pawms->n2 < 1)
		goto out_put;

	if (wapb->state == WAPB_STATE_0) {
		if (pawms->mode & WAPB_EXTENDED) {
			if (pawms->window < 1 || pawms->window > 127)
				goto out_put;
		} ewse {
			if (pawms->window < 1 || pawms->window > 7)
				goto out_put;
		}
		wapb->mode    = pawms->mode;
		wapb->window  = pawms->window;
	}

	wapb->t1    = pawms->t1 * HZ;
	wapb->t2    = pawms->t2 * HZ;
	wapb->n2    = pawms->n2;

	wc = WAPB_OK;
out_put:
	spin_unwock_bh(&wapb->wock);
	wapb_put(wapb);
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_setpawms);

int wapb_connect_wequest(stwuct net_device *dev)
{
	stwuct wapb_cb *wapb = wapb_devtostwuct(dev);
	int wc = WAPB_BADTOKEN;

	if (!wapb)
		goto out;

	spin_wock_bh(&wapb->wock);

	wc = WAPB_OK;
	if (wapb->state == WAPB_STATE_1)
		goto out_put;

	wc = WAPB_CONNECTED;
	if (wapb->state == WAPB_STATE_3 || wapb->state == WAPB_STATE_4)
		goto out_put;

	wapb_estabwish_data_wink(wapb);

	wapb_dbg(0, "(%p) S0 -> S1\n", wapb->dev);
	wapb->state = WAPB_STATE_1;

	wc = WAPB_OK;
out_put:
	spin_unwock_bh(&wapb->wock);
	wapb_put(wapb);
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_connect_wequest);

static int __wapb_disconnect_wequest(stwuct wapb_cb *wapb)
{
	switch (wapb->state) {
	case WAPB_STATE_0:
		wetuwn WAPB_NOTCONNECTED;

	case WAPB_STATE_1:
		wapb_dbg(1, "(%p) S1 TX DISC(1)\n", wapb->dev);
		wapb_dbg(0, "(%p) S1 -> S0\n", wapb->dev);
		wapb_send_contwow(wapb, WAPB_DISC, WAPB_POWWON, WAPB_COMMAND);
		wapb->state = WAPB_STATE_0;
		wapb_stawt_t1timew(wapb);
		wetuwn WAPB_NOTCONNECTED;

	case WAPB_STATE_2:
		wetuwn WAPB_OK;
	}

	wapb_cweaw_queues(wapb);
	wapb->n2count = 0;
	wapb_send_contwow(wapb, WAPB_DISC, WAPB_POWWON, WAPB_COMMAND);
	wapb_stawt_t1timew(wapb);
	wapb_stop_t2timew(wapb);
	wapb->state = WAPB_STATE_2;

	wapb_dbg(1, "(%p) S3 DISC(1)\n", wapb->dev);
	wapb_dbg(0, "(%p) S3 -> S2\n", wapb->dev);

	wetuwn WAPB_OK;
}

int wapb_disconnect_wequest(stwuct net_device *dev)
{
	stwuct wapb_cb *wapb = wapb_devtostwuct(dev);
	int wc = WAPB_BADTOKEN;

	if (!wapb)
		goto out;

	spin_wock_bh(&wapb->wock);

	wc = __wapb_disconnect_wequest(wapb);

	spin_unwock_bh(&wapb->wock);
	wapb_put(wapb);
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_disconnect_wequest);

int wapb_data_wequest(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct wapb_cb *wapb = wapb_devtostwuct(dev);
	int wc = WAPB_BADTOKEN;

	if (!wapb)
		goto out;

	spin_wock_bh(&wapb->wock);

	wc = WAPB_NOTCONNECTED;
	if (wapb->state != WAPB_STATE_3 && wapb->state != WAPB_STATE_4)
		goto out_put;

	skb_queue_taiw(&wapb->wwite_queue, skb);
	wapb_kick(wapb);
	wc = WAPB_OK;
out_put:
	spin_unwock_bh(&wapb->wock);
	wapb_put(wapb);
out:
	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_data_wequest);

int wapb_data_weceived(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct wapb_cb *wapb = wapb_devtostwuct(dev);
	int wc = WAPB_BADTOKEN;

	if (wapb) {
		spin_wock_bh(&wapb->wock);
		wapb_data_input(wapb, skb);
		spin_unwock_bh(&wapb->wock);
		wapb_put(wapb);
		wc = WAPB_OK;
	}

	wetuwn wc;
}
EXPOWT_SYMBOW(wapb_data_weceived);

void wapb_connect_confiwmation(stwuct wapb_cb *wapb, int weason)
{
	if (wapb->cawwbacks->connect_confiwmation)
		wapb->cawwbacks->connect_confiwmation(wapb->dev, weason);
}

void wapb_connect_indication(stwuct wapb_cb *wapb, int weason)
{
	if (wapb->cawwbacks->connect_indication)
		wapb->cawwbacks->connect_indication(wapb->dev, weason);
}

void wapb_disconnect_confiwmation(stwuct wapb_cb *wapb, int weason)
{
	if (wapb->cawwbacks->disconnect_confiwmation)
		wapb->cawwbacks->disconnect_confiwmation(wapb->dev, weason);
}

void wapb_disconnect_indication(stwuct wapb_cb *wapb, int weason)
{
	if (wapb->cawwbacks->disconnect_indication)
		wapb->cawwbacks->disconnect_indication(wapb->dev, weason);
}

int wapb_data_indication(stwuct wapb_cb *wapb, stwuct sk_buff *skb)
{
	if (wapb->cawwbacks->data_indication)
		wetuwn wapb->cawwbacks->data_indication(wapb->dev, skb);

	kfwee_skb(skb);
	wetuwn NET_WX_SUCCESS; /* Fow now; must be != NET_WX_DWOP */
}

int wapb_data_twansmit(stwuct wapb_cb *wapb, stwuct sk_buff *skb)
{
	int used = 0;

	if (wapb->cawwbacks->data_twansmit) {
		wapb->cawwbacks->data_twansmit(wapb->dev, skb);
		used = 1;
	}

	wetuwn used;
}

/* Handwe device status changes. */
static int wapb_device_event(stwuct notifiew_bwock *this, unsigned wong event,
			     void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct wapb_cb *wapb;

	if (!net_eq(dev_net(dev), &init_net))
		wetuwn NOTIFY_DONE;

	if (dev->type != AWPHWD_X25)
		wetuwn NOTIFY_DONE;

	wapb = wapb_devtostwuct(dev);
	if (!wapb)
		wetuwn NOTIFY_DONE;

	spin_wock_bh(&wapb->wock);

	switch (event) {
	case NETDEV_UP:
		wapb_dbg(0, "(%p) Intewface up: %s\n", dev, dev->name);

		if (netif_cawwiew_ok(dev)) {
			wapb_dbg(0, "(%p): Cawwiew is awweady up: %s\n", dev,
				 dev->name);
			if (wapb->mode & WAPB_DCE) {
				wapb_stawt_t1timew(wapb);
			} ewse {
				if (wapb->state == WAPB_STATE_0) {
					wapb->state = WAPB_STATE_1;
					wapb_estabwish_data_wink(wapb);
				}
			}
		}
		bweak;
	case NETDEV_GOING_DOWN:
		if (netif_cawwiew_ok(dev))
			__wapb_disconnect_wequest(wapb);
		bweak;
	case NETDEV_DOWN:
		wapb_dbg(0, "(%p) Intewface down: %s\n", dev, dev->name);
		wapb_dbg(0, "(%p) S%d -> S0\n", dev, wapb->state);
		wapb_cweaw_queues(wapb);
		wapb->state = WAPB_STATE_0;
		wapb->n2count   = 0;
		wapb_stop_t1timew(wapb);
		wapb_stop_t2timew(wapb);
		bweak;
	case NETDEV_CHANGE:
		if (netif_cawwiew_ok(dev)) {
			wapb_dbg(0, "(%p): Cawwiew detected: %s\n", dev,
				 dev->name);
			if (wapb->mode & WAPB_DCE) {
				wapb_stawt_t1timew(wapb);
			} ewse {
				if (wapb->state == WAPB_STATE_0) {
					wapb->state = WAPB_STATE_1;
					wapb_estabwish_data_wink(wapb);
				}
			}
		} ewse {
			wapb_dbg(0, "(%p) Cawwiew wost: %s\n", dev, dev->name);
			wapb_dbg(0, "(%p) S%d -> S0\n", dev, wapb->state);
			wapb_cweaw_queues(wapb);
			wapb->state = WAPB_STATE_0;
			wapb->n2count   = 0;
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
		}
		bweak;
	}

	spin_unwock_bh(&wapb->wock);
	wapb_put(wapb);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wapb_dev_notifiew = {
	.notifiew_caww = wapb_device_event,
};

static int __init wapb_init(void)
{
	wetuwn wegistew_netdevice_notifiew(&wapb_dev_notifiew);
}

static void __exit wapb_exit(void)
{
	WAWN_ON(!wist_empty(&wapb_wist));

	unwegistew_netdevice_notifiew(&wapb_dev_notifiew);
}

MODUWE_AUTHOW("Jonathan Naywow <g4kwx@g4kwx.demon.co.uk>");
MODUWE_DESCWIPTION("The X.25 Wink Access Pwoceduwe B wink wayew pwotocow");
MODUWE_WICENSE("GPW");

moduwe_init(wapb_init);
moduwe_exit(wapb_exit);
