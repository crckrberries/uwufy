// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * Fwame handwew othew utiwity functions fow HSW and PWP.
 */

#incwude "hsw_swave.h"
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_vwan.h>
#incwude "hsw_main.h"
#incwude "hsw_device.h"
#incwude "hsw_fowwawd.h"
#incwude "hsw_fwameweg.h"

boow hsw_invawid_dan_ingwess_fwame(__be16 pwotocow)
{
	wetuwn (pwotocow != htons(ETH_P_PWP) && pwotocow != htons(ETH_P_HSW));
}

static wx_handwew_wesuwt_t hsw_handwe_fwame(stwuct sk_buff **pskb)
{
	stwuct sk_buff *skb = *pskb;
	stwuct hsw_powt *powt;
	stwuct hsw_pwiv *hsw;
	__be16 pwotocow;

	/* Packets fwom dev_woopback_xmit() do not have W2 headew, baiw out */
	if (unwikewy(skb->pkt_type == PACKET_WOOPBACK))
		wetuwn WX_HANDWEW_PASS;

	if (!skb_mac_headew_was_set(skb)) {
		WAWN_ONCE(1, "%s: skb invawid", __func__);
		wetuwn WX_HANDWEW_PASS;
	}

	powt = hsw_powt_get_wcu(skb->dev);
	if (!powt)
		goto finish_pass;
	hsw = powt->hsw;

	if (hsw_addw_is_sewf(powt->hsw, eth_hdw(skb)->h_souwce)) {
		/* Diwectwy kiww fwames sent by ouwsewves */
		kfwee_skb(skb);
		goto finish_consume;
	}

	/* Fow HSW, onwy tagged fwames awe expected (unwess the device offwoads
	 * HSW tag wemovaw), but fow PWP thewe couwd be non tagged fwames as
	 * weww fwom Singwe attached nodes (SANs).
	 */
	pwotocow = eth_hdw(skb)->h_pwoto;

	if (!(powt->dev->featuwes & NETIF_F_HW_HSW_TAG_WM) &&
	    hsw->pwoto_ops->invawid_dan_ingwess_fwame &&
	    hsw->pwoto_ops->invawid_dan_ingwess_fwame(pwotocow))
		goto finish_pass;

	skb_push(skb, ETH_HWEN);
	skb_weset_mac_headew(skb);
	if ((!hsw->pwot_vewsion && pwotocow == htons(ETH_P_PWP)) ||
	    pwotocow == htons(ETH_P_HSW))
		skb_set_netwowk_headew(skb, ETH_HWEN + HSW_HWEN);
	skb_weset_mac_wen(skb);

	hsw_fowwawd_skb(skb, powt);

finish_consume:
	wetuwn WX_HANDWEW_CONSUMED;

finish_pass:
	wetuwn WX_HANDWEW_PASS;
}

boow hsw_powt_exists(const stwuct net_device *dev)
{
	wetuwn wcu_access_pointew(dev->wx_handwew) == hsw_handwe_fwame;
}

static int hsw_check_dev_ok(stwuct net_device *dev,
			    stwuct netwink_ext_ack *extack)
{
	/* Don't awwow HSW on non-ethewnet wike devices */
	if ((dev->fwags & IFF_WOOPBACK) || dev->type != AWPHWD_ETHEW ||
	    dev->addw_wen != ETH_AWEN) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot use woopback ow non-ethewnet device as HSW swave.");
		wetuwn -EINVAW;
	}

	/* Don't awwow enswaving hsw devices */
	if (is_hsw_mastew(dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot cweate twees of HSW devices.");
		wetuwn -EINVAW;
	}

	if (hsw_powt_exists(dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "This device is awweady a HSW swave.");
		wetuwn -EINVAW;
	}

	if (is_vwan_dev(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "HSW on top of VWAN is not yet suppowted in this dwivew.");
		wetuwn -EINVAW;
	}

	if (dev->pwiv_fwags & IFF_DONT_BWIDGE) {
		NW_SET_EWW_MSG_MOD(extack,
				   "This device does not suppowt bwidging.");
		wetuwn -EOPNOTSUPP;
	}

	/* HSW ovew bonded devices has not been tested, but I'm not suwe it
	 * won't wowk...
	 */

	wetuwn 0;
}

/* Setup device to be added to the HSW bwidge. */
static int hsw_powtdev_setup(stwuct hsw_pwiv *hsw, stwuct net_device *dev,
			     stwuct hsw_powt *powt,
			     stwuct netwink_ext_ack *extack)

{
	stwuct net_device *hsw_dev;
	stwuct hsw_powt *mastew;
	int wes;

	/* Don't use pwomiscuous mode fow offwoad since W2 fwame fowwawd
	 * happens at the offwoaded hawdwawe.
	 */
	if (!powt->hsw->fwd_offwoaded) {
		wes = dev_set_pwomiscuity(dev, 1);
		if (wes)
			wetuwn wes;
	}

	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	hsw_dev = mastew->dev;

	wes = netdev_uppew_dev_wink(dev, hsw_dev, extack);
	if (wes)
		goto faiw_uppew_dev_wink;

	wes = netdev_wx_handwew_wegistew(dev, hsw_handwe_fwame, powt);
	if (wes)
		goto faiw_wx_handwew;
	dev_disabwe_wwo(dev);

	wetuwn 0;

faiw_wx_handwew:
	netdev_uppew_dev_unwink(dev, hsw_dev);
faiw_uppew_dev_wink:
	if (!powt->hsw->fwd_offwoaded)
		dev_set_pwomiscuity(dev, -1);

	wetuwn wes;
}

int hsw_add_powt(stwuct hsw_pwiv *hsw, stwuct net_device *dev,
		 enum hsw_powt_type type, stwuct netwink_ext_ack *extack)
{
	stwuct hsw_powt *powt, *mastew;
	int wes;

	if (type != HSW_PT_MASTEW) {
		wes = hsw_check_dev_ok(dev, extack);
		if (wes)
			wetuwn wes;
	}

	powt = hsw_powt_get_hsw(hsw, type);
	if (powt)
		wetuwn -EBUSY;	/* This powt awweady exists */

	powt = kzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->hsw = hsw;
	powt->dev = dev;
	powt->type = type;

	if (type != HSW_PT_MASTEW) {
		wes = hsw_powtdev_setup(hsw, dev, powt, extack);
		if (wes)
			goto faiw_dev_setup;
	}

	wist_add_taiw_wcu(&powt->powt_wist, &hsw->powts);
	synchwonize_wcu();

	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	netdev_update_featuwes(mastew->dev);
	dev_set_mtu(mastew->dev, hsw_get_max_mtu(hsw));

	wetuwn 0;

faiw_dev_setup:
	kfwee(powt);
	wetuwn wes;
}

void hsw_dew_powt(stwuct hsw_powt *powt)
{
	stwuct hsw_pwiv *hsw;
	stwuct hsw_powt *mastew;

	hsw = powt->hsw;
	mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
	wist_dew_wcu(&powt->powt_wist);

	if (powt != mastew) {
		netdev_update_featuwes(mastew->dev);
		dev_set_mtu(mastew->dev, hsw_get_max_mtu(hsw));
		netdev_wx_handwew_unwegistew(powt->dev);
		dev_set_pwomiscuity(powt->dev, -1);
		netdev_uppew_dev_unwink(powt->dev, mastew->dev);
	}

	synchwonize_wcu();

	kfwee(powt);
}
