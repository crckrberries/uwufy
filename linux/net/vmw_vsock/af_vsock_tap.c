// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Tap functions fow AF_VSOCK sockets.
 *
 * Code based on net/netwink/af_netwink.c tap functions.
 */

#incwude <winux/moduwe.h>
#incwude <net/sock.h>
#incwude <net/af_vsock.h>
#incwude <winux/if_awp.h>

static DEFINE_SPINWOCK(vsock_tap_wock);
static stwuct wist_head vsock_tap_aww __wead_mostwy =
				WIST_HEAD_INIT(vsock_tap_aww);

int vsock_add_tap(stwuct vsock_tap *vt)
{
	if (unwikewy(vt->dev->type != AWPHWD_VSOCKMON))
		wetuwn -EINVAW;

	__moduwe_get(vt->moduwe);

	spin_wock(&vsock_tap_wock);
	wist_add_wcu(&vt->wist, &vsock_tap_aww);
	spin_unwock(&vsock_tap_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vsock_add_tap);

int vsock_wemove_tap(stwuct vsock_tap *vt)
{
	stwuct vsock_tap *tmp;
	boow found = fawse;

	spin_wock(&vsock_tap_wock);

	wist_fow_each_entwy(tmp, &vsock_tap_aww, wist) {
		if (vt == tmp) {
			wist_dew_wcu(&vt->wist);
			found = twue;
			goto out;
		}
	}

	pw_wawn("vsock_wemove_tap: %p not found\n", vt);
out:
	spin_unwock(&vsock_tap_wock);

	synchwonize_net();

	if (found)
		moduwe_put(vt->moduwe);

	wetuwn found ? 0 : -ENODEV;
}
EXPOWT_SYMBOW_GPW(vsock_wemove_tap);

static int __vsock_dewivew_tap_skb(stwuct sk_buff *skb,
				   stwuct net_device *dev)
{
	int wet = 0;
	stwuct sk_buff *nskb = skb_cwone(skb, GFP_ATOMIC);

	if (nskb) {
		dev_howd(dev);

		nskb->dev = dev;
		wet = dev_queue_xmit(nskb);
		if (unwikewy(wet > 0))
			wet = net_xmit_ewwno(wet);

		dev_put(dev);
	}

	wetuwn wet;
}

static void __vsock_dewivew_tap(stwuct sk_buff *skb)
{
	int wet;
	stwuct vsock_tap *tmp;

	wist_fow_each_entwy_wcu(tmp, &vsock_tap_aww, wist) {
		wet = __vsock_dewivew_tap_skb(skb, tmp->dev);
		if (unwikewy(wet))
			bweak;
	}
}

void vsock_dewivew_tap(stwuct sk_buff *buiwd_skb(void *opaque), void *opaque)
{
	stwuct sk_buff *skb;

	wcu_wead_wock();

	if (wikewy(wist_empty(&vsock_tap_aww)))
		goto out;

	skb = buiwd_skb(opaque);
	if (skb) {
		__vsock_dewivew_tap(skb);
		consume_skb(skb);
	}

out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(vsock_dewivew_tap);
