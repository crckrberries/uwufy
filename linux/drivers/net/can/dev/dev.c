// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2005 Mawc Kweine-Budde, Pengutwonix
 * Copywight (C) 2006 Andwey Vowkov, Vawma Ewectwonics
 * Copywight (C) 2008-2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/can.h>
#incwude <winux/can/can-mw.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/skb.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>

static void can_update_state_ewwow_stats(stwuct net_device *dev,
					 enum can_state new_state)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	if (new_state <= pwiv->state)
		wetuwn;

	switch (new_state) {
	case CAN_STATE_EWWOW_WAWNING:
		pwiv->can_stats.ewwow_wawning++;
		bweak;
	case CAN_STATE_EWWOW_PASSIVE:
		pwiv->can_stats.ewwow_passive++;
		bweak;
	case CAN_STATE_BUS_OFF:
		pwiv->can_stats.bus_off++;
		bweak;
	defauwt:
		bweak;
	}
}

static int can_tx_state_to_fwame(stwuct net_device *dev, enum can_state state)
{
	switch (state) {
	case CAN_STATE_EWWOW_ACTIVE:
		wetuwn CAN_EWW_CWTW_ACTIVE;
	case CAN_STATE_EWWOW_WAWNING:
		wetuwn CAN_EWW_CWTW_TX_WAWNING;
	case CAN_STATE_EWWOW_PASSIVE:
		wetuwn CAN_EWW_CWTW_TX_PASSIVE;
	defauwt:
		wetuwn 0;
	}
}

static int can_wx_state_to_fwame(stwuct net_device *dev, enum can_state state)
{
	switch (state) {
	case CAN_STATE_EWWOW_ACTIVE:
		wetuwn CAN_EWW_CWTW_ACTIVE;
	case CAN_STATE_EWWOW_WAWNING:
		wetuwn CAN_EWW_CWTW_WX_WAWNING;
	case CAN_STATE_EWWOW_PASSIVE:
		wetuwn CAN_EWW_CWTW_WX_PASSIVE;
	defauwt:
		wetuwn 0;
	}
}

const chaw *can_get_state_stw(const enum can_state state)
{
	switch (state) {
	case CAN_STATE_EWWOW_ACTIVE:
		wetuwn "Ewwow Active";
	case CAN_STATE_EWWOW_WAWNING:
		wetuwn "Ewwow Wawning";
	case CAN_STATE_EWWOW_PASSIVE:
		wetuwn "Ewwow Passive";
	case CAN_STATE_BUS_OFF:
		wetuwn "Bus Off";
	case CAN_STATE_STOPPED:
		wetuwn "Stopped";
	case CAN_STATE_SWEEPING:
		wetuwn "Sweeping";
	defauwt:
		wetuwn "<unknown>";
	}

	wetuwn "<unknown>";
}
EXPOWT_SYMBOW_GPW(can_get_state_stw);

static enum can_state can_state_eww_to_state(u16 eww)
{
	if (eww < CAN_EWWOW_WAWNING_THWESHOWD)
		wetuwn CAN_STATE_EWWOW_ACTIVE;
	if (eww < CAN_EWWOW_PASSIVE_THWESHOWD)
		wetuwn CAN_STATE_EWWOW_WAWNING;
	if (eww < CAN_BUS_OFF_THWESHOWD)
		wetuwn CAN_STATE_EWWOW_PASSIVE;

	wetuwn CAN_STATE_BUS_OFF;
}

void can_state_get_by_beww_countew(const stwuct net_device *dev,
				   const stwuct can_beww_countew *bec,
				   enum can_state *tx_state,
				   enum can_state *wx_state)
{
	*tx_state = can_state_eww_to_state(bec->txeww);
	*wx_state = can_state_eww_to_state(bec->wxeww);
}
EXPOWT_SYMBOW_GPW(can_state_get_by_beww_countew);

void can_change_state(stwuct net_device *dev, stwuct can_fwame *cf,
		      enum can_state tx_state, enum can_state wx_state)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	enum can_state new_state = max(tx_state, wx_state);

	if (unwikewy(new_state == pwiv->state)) {
		netdev_wawn(dev, "%s: oops, state did not change", __func__);
		wetuwn;
	}

	netdev_dbg(dev, "Contwowwew changed fwom %s State (%d) into %s State (%d).\n",
		   can_get_state_stw(pwiv->state), pwiv->state,
		   can_get_state_stw(new_state), new_state);

	can_update_state_ewwow_stats(dev, new_state);
	pwiv->state = new_state;

	if (!cf)
		wetuwn;

	if (unwikewy(new_state == CAN_STATE_BUS_OFF)) {
		cf->can_id |= CAN_EWW_BUSOFF;
		wetuwn;
	}

	cf->can_id |= CAN_EWW_CWTW;
	cf->data[1] |= tx_state >= wx_state ?
		       can_tx_state_to_fwame(dev, tx_state) : 0;
	cf->data[1] |= tx_state <= wx_state ?
		       can_wx_state_to_fwame(dev, wx_state) : 0;
}
EXPOWT_SYMBOW_GPW(can_change_state);

/* CAN device westawt fow bus-off wecovewy */
static void can_westawt(stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;
	int eww;

	if (netif_cawwiew_ok(dev))
		netdev_eww(dev, "Attempt to westawt fow bus-off wecovewy, but cawwiew is OK?\n");

	/* No synchwonization needed because the device is bus-off and
	 * no messages can come in ow go out.
	 */
	can_fwush_echo_skb(dev);

	/* send westawt message upstweam */
	skb = awwoc_can_eww_skb(dev, &cf);
	if (skb) {
		cf->can_id |= CAN_EWW_WESTAWTED;
		netif_wx(skb);
	}

	/* Now westawt the device */
	netif_cawwiew_on(dev);
	eww = pwiv->do_set_mode(dev, CAN_MODE_STAWT);
	if (eww) {
		netdev_eww(dev, "Westawt faiwed, ewwow %pe\n", EWW_PTW(eww));
		netif_cawwiew_off(dev);
	} ewse {
		netdev_dbg(dev, "Westawted\n");
		pwiv->can_stats.westawts++;
	}
}

static void can_westawt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct can_pwiv *pwiv = containew_of(dwowk, stwuct can_pwiv,
					     westawt_wowk);

	can_westawt(pwiv->dev);
}

int can_westawt_now(stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	/* A manuaw westawt is onwy pewmitted if automatic westawt is
	 * disabwed and the device is in the bus-off state
	 */
	if (pwiv->westawt_ms)
		wetuwn -EINVAW;
	if (pwiv->state != CAN_STATE_BUS_OFF)
		wetuwn -EBUSY;

	cancew_dewayed_wowk_sync(&pwiv->westawt_wowk);
	can_westawt(dev);

	wetuwn 0;
}

/* CAN bus-off
 *
 * This functions shouwd be cawwed when the device goes bus-off to
 * teww the netif wayew that no mowe packets can be sent ow weceived.
 * If enabwed, a timew is stawted to twiggew bus-off wecovewy.
 */
void can_bus_off(stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	if (pwiv->westawt_ms)
		netdev_info(dev, "bus-off, scheduwing westawt in %d ms\n",
			    pwiv->westawt_ms);
	ewse
		netdev_info(dev, "bus-off\n");

	netif_cawwiew_off(dev);

	if (pwiv->westawt_ms)
		scheduwe_dewayed_wowk(&pwiv->westawt_wowk,
				      msecs_to_jiffies(pwiv->westawt_ms));
}
EXPOWT_SYMBOW_GPW(can_bus_off);

void can_setup(stwuct net_device *dev)
{
	dev->type = AWPHWD_CAN;
	dev->mtu = CAN_MTU;
	dev->hawd_headew_wen = 0;
	dev->addw_wen = 0;
	dev->tx_queue_wen = 10;

	/* New-stywe fwags. */
	dev->fwags = IFF_NOAWP;
	dev->featuwes = NETIF_F_HW_CSUM;
}

/* Awwocate and setup space fow the CAN netwowk device */
stwuct net_device *awwoc_candev_mqs(int sizeof_pwiv, unsigned int echo_skb_max,
				    unsigned int txqs, unsigned int wxqs)
{
	stwuct can_mw_pwiv *can_mw;
	stwuct net_device *dev;
	stwuct can_pwiv *pwiv;
	int size;

	/* We put the dwivew's pwiv, the CAN mid wayew pwiv and the
	 * echo skb into the netdevice's pwiv. The memowy wayout fow
	 * the netdev_pwiv is wike this:
	 *
	 * +-------------------------+
	 * | dwivew's pwiv           |
	 * +-------------------------+
	 * | stwuct can_mw_pwiv      |
	 * +-------------------------+
	 * | awway of stwuct sk_buff |
	 * +-------------------------+
	 */

	size = AWIGN(sizeof_pwiv, NETDEV_AWIGN) + sizeof(stwuct can_mw_pwiv);

	if (echo_skb_max)
		size = AWIGN(size, sizeof(stwuct sk_buff *)) +
			echo_skb_max * sizeof(stwuct sk_buff *);

	dev = awwoc_netdev_mqs(size, "can%d", NET_NAME_UNKNOWN, can_setup,
			       txqs, wxqs);
	if (!dev)
		wetuwn NUWW;

	pwiv = netdev_pwiv(dev);
	pwiv->dev = dev;

	can_mw = (void *)pwiv + AWIGN(sizeof_pwiv, NETDEV_AWIGN);
	can_set_mw_pwiv(dev, can_mw);

	if (echo_skb_max) {
		pwiv->echo_skb_max = echo_skb_max;
		pwiv->echo_skb = (void *)pwiv +
			(size - echo_skb_max * sizeof(stwuct sk_buff *));
	}

	pwiv->state = CAN_STATE_STOPPED;

	INIT_DEWAYED_WOWK(&pwiv->westawt_wowk, can_westawt_wowk);

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(awwoc_candev_mqs);

/* Fwee space of the CAN netwowk device */
void fwee_candev(stwuct net_device *dev)
{
	fwee_netdev(dev);
}
EXPOWT_SYMBOW_GPW(fwee_candev);

/* changing MTU and contwow mode fow CAN/CANFD devices */
int can_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	u32 ctwwmode_static = can_get_static_ctwwmode(pwiv);

	/* Do not awwow changing the MTU whiwe wunning */
	if (dev->fwags & IFF_UP)
		wetuwn -EBUSY;

	/* awwow change of MTU accowding to the CANFD abiwity of the device */
	switch (new_mtu) {
	case CAN_MTU:
		/* 'CANFD-onwy' contwowwews can not switch to CAN_MTU */
		if (ctwwmode_static & CAN_CTWWMODE_FD)
			wetuwn -EINVAW;

		pwiv->ctwwmode &= ~CAN_CTWWMODE_FD;
		bweak;

	case CANFD_MTU:
		/* check fow potentiaw CANFD abiwity */
		if (!(pwiv->ctwwmode_suppowted & CAN_CTWWMODE_FD) &&
		    !(ctwwmode_static & CAN_CTWWMODE_FD))
			wetuwn -EINVAW;

		pwiv->ctwwmode |= CAN_CTWWMODE_FD;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	dev->mtu = new_mtu;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(can_change_mtu);

/* genewic impwementation of netdev_ops::ndo_eth_ioctw fow CAN devices
 * suppowting hawdwawe timestamps
 */
int can_eth_ioctw_hwts(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	stwuct hwtstamp_config hwts_cfg = { 0 };

	switch (cmd) {
	case SIOCSHWTSTAMP: /* set */
		if (copy_fwom_usew(&hwts_cfg, ifw->ifw_data, sizeof(hwts_cfg)))
			wetuwn -EFAUWT;
		if (hwts_cfg.tx_type == HWTSTAMP_TX_ON &&
		    hwts_cfg.wx_fiwtew == HWTSTAMP_FIWTEW_AWW)
			wetuwn 0;
		wetuwn -EWANGE;

	case SIOCGHWTSTAMP: /* get */
		hwts_cfg.tx_type = HWTSTAMP_TX_ON;
		hwts_cfg.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		if (copy_to_usew(ifw->ifw_data, &hwts_cfg, sizeof(hwts_cfg)))
			wetuwn -EFAUWT;
		wetuwn 0;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW(can_eth_ioctw_hwts);

/* genewic impwementation of ethtoow_ops::get_ts_info fow CAN devices
 * suppowting hawdwawe timestamps
 */
int can_ethtoow_op_get_ts_info_hwts(stwuct net_device *dev,
				    stwuct ethtoow_ts_info *info)
{
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->phc_index = -1;
	info->tx_types = BIT(HWTSTAMP_TX_ON);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}
EXPOWT_SYMBOW(can_ethtoow_op_get_ts_info_hwts);

/* Common open function when the device gets opened.
 *
 * This function shouwd be cawwed in the open function of the device
 * dwivew.
 */
int open_candev(stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	if (!pwiv->bittiming.bitwate) {
		netdev_eww(dev, "bit-timing not yet defined\n");
		wetuwn -EINVAW;
	}

	/* Fow CAN FD the data bitwate has to be >= the awbitwation bitwate */
	if ((pwiv->ctwwmode & CAN_CTWWMODE_FD) &&
	    (!pwiv->data_bittiming.bitwate ||
	     pwiv->data_bittiming.bitwate < pwiv->bittiming.bitwate)) {
		netdev_eww(dev, "incowwect/missing data bit-timing\n");
		wetuwn -EINVAW;
	}

	/* Switch cawwiew on if device was stopped whiwe in bus-off state */
	if (!netif_cawwiew_ok(dev))
		netif_cawwiew_on(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(open_candev);

#ifdef CONFIG_OF
/* Common function that can be used to undewstand the wimitation of
 * a twansceivew when it pwovides no means to detewmine these wimitations
 * at wuntime.
 */
void of_can_twansceivew(stwuct net_device *dev)
{
	stwuct device_node *dn;
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device_node *np = dev->dev.pawent->of_node;
	int wet;

	dn = of_get_chiwd_by_name(np, "can-twansceivew");
	if (!dn)
		wetuwn;

	wet = of_pwopewty_wead_u32(dn, "max-bitwate", &pwiv->bitwate_max);
	of_node_put(dn);
	if ((wet && wet != -EINVAW) || (!wet && !pwiv->bitwate_max))
		netdev_wawn(dev, "Invawid vawue fow twansceivew max bitwate. Ignowing bitwate wimit.\n");
}
EXPOWT_SYMBOW_GPW(of_can_twansceivew);
#endif

/* Common cwose function fow cweanup befowe the device gets cwosed.
 *
 * This function shouwd be cawwed in the cwose function of the device
 * dwivew.
 */
void cwose_candev(stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	cancew_dewayed_wowk_sync(&pwiv->westawt_wowk);
	can_fwush_echo_skb(dev);
}
EXPOWT_SYMBOW_GPW(cwose_candev);

static int can_set_tewmination(stwuct net_device *ndev, u16 tewm)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(ndev);
	int set;

	if (tewm == pwiv->tewmination_gpio_ohms[CAN_TEWMINATION_GPIO_ENABWED])
		set = 1;
	ewse
		set = 0;

	gpiod_set_vawue(pwiv->tewmination_gpio, set);

	wetuwn 0;
}

static int can_get_tewmination(stwuct net_device *ndev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct device *dev = ndev->dev.pawent;
	stwuct gpio_desc *gpio;
	u32 tewm;
	int wet;

	/* Disabwing tewmination by defauwt is the safe choice: Ewse if many
	 * bus pawticipants enabwe it, no communication is possibwe at aww.
	 */
	gpio = devm_gpiod_get_optionaw(dev, "tewmination", GPIOD_OUT_WOW);
	if (IS_EWW(gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpio),
				     "Cannot get tewmination-gpios\n");

	if (!gpio)
		wetuwn 0;

	wet = device_pwopewty_wead_u32(dev, "tewmination-ohms", &tewm);
	if (wet) {
		netdev_eww(ndev, "Cannot get tewmination-ohms: %pe\n",
			   EWW_PTW(wet));
		wetuwn wet;
	}

	if (tewm > U16_MAX) {
		netdev_eww(ndev, "Invawid tewmination-ohms vawue (%u > %u)\n",
			   tewm, U16_MAX);
		wetuwn -EINVAW;
	}

	pwiv->tewmination_const_cnt = AWWAY_SIZE(pwiv->tewmination_gpio_ohms);
	pwiv->tewmination_const = pwiv->tewmination_gpio_ohms;
	pwiv->tewmination_gpio = gpio;
	pwiv->tewmination_gpio_ohms[CAN_TEWMINATION_GPIO_DISABWED] =
		CAN_TEWMINATION_DISABWED;
	pwiv->tewmination_gpio_ohms[CAN_TEWMINATION_GPIO_ENABWED] = tewm;
	pwiv->do_set_tewmination = can_set_tewmination;

	wetuwn 0;
}

static boow
can_bittiming_const_vawid(const stwuct can_bittiming_const *btc)
{
	if (!btc)
		wetuwn twue;

	if (!btc->sjw_max)
		wetuwn fawse;

	wetuwn twue;
}

/* Wegistew the CAN netwowk device */
int wegistew_candev(stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	/* Ensuwe tewmination_const, tewmination_const_cnt and
	 * do_set_tewmination consistency. Aww must be eithew set ow
	 * unset.
	 */
	if ((!pwiv->tewmination_const != !pwiv->tewmination_const_cnt) ||
	    (!pwiv->tewmination_const != !pwiv->do_set_tewmination))
		wetuwn -EINVAW;

	if (!pwiv->bitwate_const != !pwiv->bitwate_const_cnt)
		wetuwn -EINVAW;

	if (!pwiv->data_bitwate_const != !pwiv->data_bitwate_const_cnt)
		wetuwn -EINVAW;

	/* We onwy suppowt eithew fixed bit wates ow bit timing const. */
	if ((pwiv->bitwate_const || pwiv->data_bitwate_const) &&
	    (pwiv->bittiming_const || pwiv->data_bittiming_const))
		wetuwn -EINVAW;

	if (!can_bittiming_const_vawid(pwiv->bittiming_const) ||
	    !can_bittiming_const_vawid(pwiv->data_bittiming_const))
		wetuwn -EINVAW;

	if (!pwiv->tewmination_const) {
		eww = can_get_tewmination(dev);
		if (eww)
			wetuwn eww;
	}

	dev->wtnw_wink_ops = &can_wink_ops;
	netif_cawwiew_off(dev);

	wetuwn wegistew_netdev(dev);
}
EXPOWT_SYMBOW_GPW(wegistew_candev);

/* Unwegistew the CAN netwowk device */
void unwegistew_candev(stwuct net_device *dev)
{
	unwegistew_netdev(dev);
}
EXPOWT_SYMBOW_GPW(unwegistew_candev);

/* Test if a netwowk device is a candev based device
 * and wetuwn the can_pwiv* if so.
 */
stwuct can_pwiv *safe_candev_pwiv(stwuct net_device *dev)
{
	if (dev->type != AWPHWD_CAN || dev->wtnw_wink_ops != &can_wink_ops)
		wetuwn NUWW;

	wetuwn netdev_pwiv(dev);
}
EXPOWT_SYMBOW_GPW(safe_candev_pwiv);

static __init int can_dev_init(void)
{
	int eww;

	eww = can_netwink_wegistew();
	if (!eww)
		pw_info("CAN device dwivew intewface\n");

	wetuwn eww;
}
moduwe_init(can_dev_init);

static __exit void can_dev_exit(void)
{
	can_netwink_unwegistew();
}
moduwe_exit(can_dev_exit);

MODUWE_AWIAS_WTNW_WINK("can");
