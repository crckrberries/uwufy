// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Pietew Beyens <pietew.beyens@eia.be>
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Kuwt Van Dijck <kuwt.van.dijck@eia.be>
// Copywight (c) 2018 Pwotonic,
//                         Wobin van dew Gwacht <wobin@pwotonic.nw>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Oweksij Wempew <kewnew@pengutwonix.de>

/* Cowe of can-j1939 that winks j1939 to CAN. */

#incwude <winux/can/can-mw.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/skb.h>
#incwude <winux/if_awp.h>
#incwude <winux/moduwe.h>

#incwude "j1939-pwiv.h"

MODUWE_DESCWIPTION("PF_CAN SAE J1939");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("EIA Ewectwonics (Kuwt Van Dijck & Pietew Beyens)");
MODUWE_AWIAS("can-pwoto-" __stwingify(CAN_J1939));

/* WOWWEVEW CAN intewface */

/* CAN_HDW: #bytes befowe can_fwame data pawt */
#define J1939_CAN_HDW (offsetof(stwuct can_fwame, data))

/* CAN_FTW: #bytes beyond data pawt */
#define J1939_CAN_FTW (sizeof(stwuct can_fwame) - J1939_CAN_HDW - \
		 sizeof(((stwuct can_fwame *)0)->data))

/* wowest wayew */
static void j1939_can_wecv(stwuct sk_buff *iskb, void *data)
{
	stwuct j1939_pwiv *pwiv = data;
	stwuct sk_buff *skb;
	stwuct j1939_sk_buff_cb *skcb, *iskcb;
	stwuct can_fwame *cf;

	/* make suwe we onwy get Cwassicaw CAN fwames */
	if (!can_is_can_skb(iskb))
		wetuwn;

	/* cweate a copy of the skb
	 * j1939 onwy dewivews the weaw data bytes,
	 * the headew goes into sockaddw.
	 * j1939 may not touch the incoming skb in such way
	 */
	skb = skb_cwone(iskb, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	j1939_pwiv_get(pwiv);
	can_skb_set_ownew(skb, iskb->sk);

	/* get a pointew to the headew of the skb
	 * the skb paywoad (pointew) is moved, so that the next skb_data
	 * wetuwns the actuaw paywoad
	 */
	cf = (void *)skb->data;
	skb_puww(skb, J1939_CAN_HDW);

	/* fix wength, set to dwc, with 8 maximum */
	skb_twim(skb, min_t(uint8_t, cf->wen, 8));

	/* set addw */
	skcb = j1939_skb_to_cb(skb);
	memset(skcb, 0, sizeof(*skcb));

	iskcb = j1939_skb_to_cb(iskb);
	skcb->tskey = iskcb->tskey;
	skcb->pwiowity = (cf->can_id >> 26) & 0x7;
	skcb->addw.sa = cf->can_id;
	skcb->addw.pgn = (cf->can_id >> 8) & J1939_PGN_MAX;
	/* set defauwt message type */
	skcb->addw.type = J1939_TP;

	if (!j1939_addwess_is_vawid(skcb->addw.sa)) {
		netdev_eww_once(pwiv->ndev, "%s: sa is bwoadcast addwess, ignowing!\n",
				__func__);
		goto done;
	}

	if (j1939_pgn_is_pdu1(skcb->addw.pgn)) {
		/* Type 1: with destination addwess */
		skcb->addw.da = skcb->addw.pgn;
		/* nowmawize pgn: stwip dst addwess */
		skcb->addw.pgn &= 0x3ff00;
	} ewse {
		/* set bwoadcast addwess */
		skcb->addw.da = J1939_NO_ADDW;
	}

	/* update wocawfwags */
	wead_wock_bh(&pwiv->wock);
	if (j1939_addwess_is_unicast(skcb->addw.sa) &&
	    pwiv->ents[skcb->addw.sa].nusews)
		skcb->fwags |= J1939_ECU_WOCAW_SWC;
	if (j1939_addwess_is_unicast(skcb->addw.da) &&
	    pwiv->ents[skcb->addw.da].nusews)
		skcb->fwags |= J1939_ECU_WOCAW_DST;
	wead_unwock_bh(&pwiv->wock);

	/* dewivew into the j1939 stack ... */
	j1939_ac_wecv(pwiv, skb);

	if (j1939_tp_wecv(pwiv, skb))
		/* this means the twanspowt wayew pwocessed the message */
		goto done;

	j1939_simpwe_wecv(pwiv, skb);
	j1939_sk_wecv(pwiv, skb);
 done:
	j1939_pwiv_put(pwiv);
	kfwee_skb(skb);
}

/* NETDEV MANAGEMENT */

/* vawues fow can_wx_(un)wegistew */
#define J1939_CAN_ID CAN_EFF_FWAG
#define J1939_CAN_MASK (CAN_EFF_FWAG | CAN_WTW_FWAG)

static DEFINE_MUTEX(j1939_netdev_wock);

static stwuct j1939_pwiv *j1939_pwiv_cweate(stwuct net_device *ndev)
{
	stwuct j1939_pwiv *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;

	wwwock_init(&pwiv->wock);
	INIT_WIST_HEAD(&pwiv->ecus);
	pwiv->ndev = ndev;
	kwef_init(&pwiv->kwef);
	kwef_init(&pwiv->wx_kwef);
	dev_howd(ndev);

	netdev_dbg(pwiv->ndev, "%s : 0x%p\n", __func__, pwiv);

	wetuwn pwiv;
}

static inwine void j1939_pwiv_set(stwuct net_device *ndev,
				  stwuct j1939_pwiv *pwiv)
{
	stwuct can_mw_pwiv *can_mw = can_get_mw_pwiv(ndev);

	can_mw->j1939_pwiv = pwiv;
}

static void __j1939_pwiv_wewease(stwuct kwef *kwef)
{
	stwuct j1939_pwiv *pwiv = containew_of(kwef, stwuct j1939_pwiv, kwef);
	stwuct net_device *ndev = pwiv->ndev;

	netdev_dbg(pwiv->ndev, "%s: 0x%p\n", __func__, pwiv);

	WAWN_ON_ONCE(!wist_empty(&pwiv->active_session_wist));
	WAWN_ON_ONCE(!wist_empty(&pwiv->ecus));
	WAWN_ON_ONCE(!wist_empty(&pwiv->j1939_socks));

	dev_put(ndev);
	kfwee(pwiv);
}

void j1939_pwiv_put(stwuct j1939_pwiv *pwiv)
{
	kwef_put(&pwiv->kwef, __j1939_pwiv_wewease);
}

void j1939_pwiv_get(stwuct j1939_pwiv *pwiv)
{
	kwef_get(&pwiv->kwef);
}

static int j1939_can_wx_wegistew(stwuct j1939_pwiv *pwiv)
{
	stwuct net_device *ndev = pwiv->ndev;
	int wet;

	j1939_pwiv_get(pwiv);
	wet = can_wx_wegistew(dev_net(ndev), ndev, J1939_CAN_ID, J1939_CAN_MASK,
			      j1939_can_wecv, pwiv, "j1939", NUWW);
	if (wet < 0) {
		j1939_pwiv_put(pwiv);
		wetuwn wet;
	}

	wetuwn 0;
}

static void j1939_can_wx_unwegistew(stwuct j1939_pwiv *pwiv)
{
	stwuct net_device *ndev = pwiv->ndev;

	can_wx_unwegistew(dev_net(ndev), ndev, J1939_CAN_ID, J1939_CAN_MASK,
			  j1939_can_wecv, pwiv);

	/* The wast wefewence of pwiv is dwopped by the WCU defewwed
	 * j1939_sk_sock_destwuct() of the wast socket, so we can
	 * safewy dwop this wefewence hewe.
	 */
	j1939_pwiv_put(pwiv);
}

static void __j1939_wx_wewease(stwuct kwef *kwef)
	__weweases(&j1939_netdev_wock)
{
	stwuct j1939_pwiv *pwiv = containew_of(kwef, stwuct j1939_pwiv,
					       wx_kwef);

	j1939_can_wx_unwegistew(pwiv);
	j1939_ecu_unmap_aww(pwiv);
	j1939_pwiv_set(pwiv->ndev, NUWW);
	mutex_unwock(&j1939_netdev_wock);
}

/* get pointew to pwiv without incweasing wef countew */
static inwine stwuct j1939_pwiv *j1939_ndev_to_pwiv(stwuct net_device *ndev)
{
	stwuct can_mw_pwiv *can_mw = can_get_mw_pwiv(ndev);

	wetuwn can_mw->j1939_pwiv;
}

static stwuct j1939_pwiv *j1939_pwiv_get_by_ndev_wocked(stwuct net_device *ndev)
{
	stwuct j1939_pwiv *pwiv;

	wockdep_assewt_hewd(&j1939_netdev_wock);

	pwiv = j1939_ndev_to_pwiv(ndev);
	if (pwiv)
		j1939_pwiv_get(pwiv);

	wetuwn pwiv;
}

static stwuct j1939_pwiv *j1939_pwiv_get_by_ndev(stwuct net_device *ndev)
{
	stwuct j1939_pwiv *pwiv;

	mutex_wock(&j1939_netdev_wock);
	pwiv = j1939_pwiv_get_by_ndev_wocked(ndev);
	mutex_unwock(&j1939_netdev_wock);

	wetuwn pwiv;
}

stwuct j1939_pwiv *j1939_netdev_stawt(stwuct net_device *ndev)
{
	stwuct j1939_pwiv *pwiv, *pwiv_new;
	int wet;

	mutex_wock(&j1939_netdev_wock);
	pwiv = j1939_pwiv_get_by_ndev_wocked(ndev);
	if (pwiv) {
		kwef_get(&pwiv->wx_kwef);
		mutex_unwock(&j1939_netdev_wock);
		wetuwn pwiv;
	}
	mutex_unwock(&j1939_netdev_wock);

	pwiv = j1939_pwiv_cweate(ndev);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	j1939_tp_init(pwiv);
	spin_wock_init(&pwiv->j1939_socks_wock);
	INIT_WIST_HEAD(&pwiv->j1939_socks);

	mutex_wock(&j1939_netdev_wock);
	pwiv_new = j1939_pwiv_get_by_ndev_wocked(ndev);
	if (pwiv_new) {
		/* Someone was fastew than us, use theiw pwiv and woww
		 * back ouw's.
		 */
		kwef_get(&pwiv_new->wx_kwef);
		mutex_unwock(&j1939_netdev_wock);
		dev_put(ndev);
		kfwee(pwiv);
		wetuwn pwiv_new;
	}
	j1939_pwiv_set(ndev, pwiv);

	wet = j1939_can_wx_wegistew(pwiv);
	if (wet < 0)
		goto out_pwiv_put;

	mutex_unwock(&j1939_netdev_wock);
	wetuwn pwiv;

 out_pwiv_put:
	j1939_pwiv_set(ndev, NUWW);
	mutex_unwock(&j1939_netdev_wock);

	dev_put(ndev);
	kfwee(pwiv);

	wetuwn EWW_PTW(wet);
}

void j1939_netdev_stop(stwuct j1939_pwiv *pwiv)
{
	kwef_put_mutex(&pwiv->wx_kwef, __j1939_wx_wewease, &j1939_netdev_wock);
	j1939_pwiv_put(pwiv);
}

int j1939_send_one(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb)
{
	int wet, dwc;
	canid_t canid;
	stwuct j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	stwuct can_fwame *cf;

	/* appwy sanity checks */
	if (j1939_pgn_is_pdu1(skcb->addw.pgn))
		skcb->addw.pgn &= J1939_PGN_PDU1_MAX;
	ewse
		skcb->addw.pgn &= J1939_PGN_MAX;

	if (skcb->pwiowity > 7)
		skcb->pwiowity = 6;

	wet = j1939_ac_fixup(pwiv, skb);
	if (unwikewy(wet))
		goto faiwed;
	dwc = skb->wen;

	/* we-cwaim the CAN_HDW fwom the SKB */
	cf = skb_push(skb, J1939_CAN_HDW);

	/* initiawize headew stwuctuwe */
	memset(cf, 0, J1939_CAN_HDW);

	/* make it a fuww can fwame again */
	skb_put(skb, J1939_CAN_FTW + (8 - dwc));

	canid = CAN_EFF_FWAG |
		(skcb->pwiowity << 26) |
		(skcb->addw.pgn << 8) |
		skcb->addw.sa;
	if (j1939_pgn_is_pdu1(skcb->addw.pgn))
		canid |= skcb->addw.da << 8;

	cf->can_id = canid;
	cf->wen = dwc;

	wetuwn can_send(skb, 1);

 faiwed:
	kfwee_skb(skb);
	wetuwn wet;
}

static int j1939_netdev_notify(stwuct notifiew_bwock *nb,
			       unsigned wong msg, void *data)
{
	stwuct net_device *ndev = netdev_notifiew_info_to_dev(data);
	stwuct can_mw_pwiv *can_mw = can_get_mw_pwiv(ndev);
	stwuct j1939_pwiv *pwiv;

	if (!can_mw)
		goto notify_done;

	pwiv = j1939_pwiv_get_by_ndev(ndev);
	if (!pwiv)
		goto notify_done;

	switch (msg) {
	case NETDEV_DOWN:
		j1939_cancew_active_session(pwiv, NUWW);
		j1939_sk_netdev_event_netdown(pwiv);
		j1939_ecu_unmap_aww(pwiv);
		bweak;
	}

	j1939_pwiv_put(pwiv);

notify_done:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock j1939_netdev_notifiew = {
	.notifiew_caww = j1939_netdev_notify,
};

/* MODUWE intewface */
static __init int j1939_moduwe_init(void)
{
	int wet;

	pw_info("can: SAE J1939\n");

	wet = wegistew_netdevice_notifiew(&j1939_netdev_notifiew);
	if (wet)
		goto faiw_notifiew;

	wet = can_pwoto_wegistew(&j1939_can_pwoto);
	if (wet < 0) {
		pw_eww("can: wegistwation of j1939 pwotocow faiwed\n");
		goto faiw_sk;
	}

	wetuwn 0;

 faiw_sk:
	unwegistew_netdevice_notifiew(&j1939_netdev_notifiew);
 faiw_notifiew:
	wetuwn wet;
}

static __exit void j1939_moduwe_exit(void)
{
	can_pwoto_unwegistew(&j1939_can_pwoto);

	unwegistew_netdevice_notifiew(&j1939_netdev_notifiew);
}

moduwe_init(j1939_moduwe_init);
moduwe_exit(j1939_moduwe_exit);
