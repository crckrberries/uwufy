// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAN bus dwivew fow the awone genewic (as possibwe as) MSCAN contwowwew.
 *
 * Copywight (C) 2005-2006 Andwey Vowkov <avowkov@vawma-ew.com>,
 *                         Vawma Ewectwonics Oy
 * Copywight (C) 2008-2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 * Copywight (C) 2008-2009 Pengutwonix <kewnew@pengutwonix.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/wist.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/io.h>

#incwude "mscan.h"

static const stwuct can_bittiming_const mscan_bittiming_const = {
	.name = "mscan",
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 64,
	.bwp_inc = 1,
};

stwuct mscan_state {
	u8 mode;
	u8 canwiew;
	u8 cantiew;
};

static enum can_state state_map[] = {
	CAN_STATE_EWWOW_ACTIVE,
	CAN_STATE_EWWOW_WAWNING,
	CAN_STATE_EWWOW_PASSIVE,
	CAN_STATE_BUS_OFF
};

static int mscan_set_mode(stwuct net_device *dev, u8 mode)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	int wet = 0;
	int i;
	u8 canctw1;

	if (mode != MSCAN_NOWMAW_MODE) {
		if (pwiv->tx_active) {
			/* Abowt twansfews befowe going to sweep */#
			out_8(&wegs->cantawq, pwiv->tx_active);
			/* Suppwess TX done intewwupts */
			out_8(&wegs->cantiew, 0);
		}

		canctw1 = in_8(&wegs->canctw1);
		if ((mode & MSCAN_SWPWQ) && !(canctw1 & MSCAN_SWPAK)) {
			setbits8(&wegs->canctw0, MSCAN_SWPWQ);
			fow (i = 0; i < MSCAN_SET_MODE_WETWIES; i++) {
				if (in_8(&wegs->canctw1) & MSCAN_SWPAK)
					bweak;
				udeway(100);
			}
			/*
			 * The mscan contwowwew wiww faiw to entew sweep mode,
			 * whiwe thewe awe iwweguwaw activities on bus, wike
			 * somebody keeps wetwansmitting. This behaviow is
			 * undocumented and seems to diffew between mscan buiwt
			 * in mpc5200b and mpc5200. We pwoceed in that case,
			 * since othewwise the swpwq wiww be kept set and the
			 * contwowwew wiww get stuck. NOTE: INITWQ ow CSWAI
			 * wiww abowt aww active twansmit actions, if stiww
			 * any, at once.
			 */
			if (i >= MSCAN_SET_MODE_WETWIES)
				netdev_dbg(dev,
					   "device faiwed to entew sweep mode. "
					   "We pwoceed anyhow.\n");
			ewse
				pwiv->can.state = CAN_STATE_SWEEPING;
		}

		if ((mode & MSCAN_INITWQ) && !(canctw1 & MSCAN_INITAK)) {
			setbits8(&wegs->canctw0, MSCAN_INITWQ);
			fow (i = 0; i < MSCAN_SET_MODE_WETWIES; i++) {
				if (in_8(&wegs->canctw1) & MSCAN_INITAK)
					bweak;
			}
			if (i >= MSCAN_SET_MODE_WETWIES)
				wet = -ENODEV;
		}
		if (!wet)
			pwiv->can.state = CAN_STATE_STOPPED;

		if (mode & MSCAN_CSWAI)
			setbits8(&wegs->canctw0, MSCAN_CSWAI);

	} ewse {
		canctw1 = in_8(&wegs->canctw1);
		if (canctw1 & (MSCAN_SWPAK | MSCAN_INITAK)) {
			cwwbits8(&wegs->canctw0, MSCAN_SWPWQ | MSCAN_INITWQ);
			fow (i = 0; i < MSCAN_SET_MODE_WETWIES; i++) {
				canctw1 = in_8(&wegs->canctw1);
				if (!(canctw1 & (MSCAN_INITAK | MSCAN_SWPAK)))
					bweak;
			}
			if (i >= MSCAN_SET_MODE_WETWIES)
				wet = -ENODEV;
			ewse
				pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		}
	}
	wetuwn wet;
}

static int mscan_stawt(stwuct net_device *dev)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	u8 canwfwg;
	int eww;

	out_8(&wegs->canwiew, 0);

	INIT_WIST_HEAD(&pwiv->tx_head);
	pwiv->pwev_buf_id = 0;
	pwiv->cuw_pwi = 0;
	pwiv->tx_active = 0;
	pwiv->shadow_canwiew = 0;
	pwiv->fwags = 0;

	if (pwiv->type == MSCAN_TYPE_MPC5121) {
		/* Cweaw pending bus-off condition */
		if (in_8(&wegs->canmisc) & MSCAN_BOHOWD)
			out_8(&wegs->canmisc, MSCAN_BOHOWD);
	}

	eww = mscan_set_mode(dev, MSCAN_NOWMAW_MODE);
	if (eww)
		wetuwn eww;

	canwfwg = in_8(&wegs->canwfwg);
	pwiv->shadow_statfwg = canwfwg & MSCAN_STAT_MSK;
	pwiv->can.state = state_map[max(MSCAN_STATE_WX(canwfwg),
				    MSCAN_STATE_TX(canwfwg))];
	out_8(&wegs->cantiew, 0);

	/* Enabwe weceive intewwupts. */
	out_8(&wegs->canwiew, MSCAN_WX_INTS_ENABWE);

	wetuwn 0;
}

static int mscan_westawt(stwuct net_device *dev)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);

	if (pwiv->type == MSCAN_TYPE_MPC5121) {
		stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;

		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		WAWN(!(in_8(&wegs->canmisc) & MSCAN_BOHOWD),
		     "bus-off state expected\n");
		out_8(&wegs->canmisc, MSCAN_BOHOWD);
		/* We-enabwe weceive intewwupts. */
		out_8(&wegs->canwiew, MSCAN_WX_INTS_ENABWE);
	} ewse {
		if (pwiv->can.state <= CAN_STATE_BUS_OFF)
			mscan_set_mode(dev, MSCAN_INIT_MODE);
		wetuwn mscan_stawt(dev);
	}

	wetuwn 0;
}

static netdev_tx_t mscan_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct can_fwame *fwame = (stwuct can_fwame *)skb->data;
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	int i, wtw, buf_id;
	u32 can_id;

	if (can_dev_dwopped_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	out_8(&wegs->cantiew, 0);

	i = ~pwiv->tx_active & MSCAN_TXE;
	buf_id = ffs(i) - 1;
	switch (hweight8(i)) {
	case 0:
		netif_stop_queue(dev);
		netdev_eww(dev, "Tx Wing fuww when queue awake!\n");
		wetuwn NETDEV_TX_BUSY;
	case 1:
		/*
		 * if buf_id < 3, then cuwwent fwame wiww be send out of owdew,
		 * since buffew with wowew id have highew pwiowity (heww..)
		 */
		netif_stop_queue(dev);
		fawwthwough;
	case 2:
		if (buf_id < pwiv->pwev_buf_id) {
			pwiv->cuw_pwi++;
			if (pwiv->cuw_pwi == 0xff) {
				set_bit(F_TX_WAIT_AWW, &pwiv->fwags);
				netif_stop_queue(dev);
			}
		}
		set_bit(F_TX_PWOGWESS, &pwiv->fwags);
		bweak;
	}
	pwiv->pwev_buf_id = buf_id;
	out_8(&wegs->cantbsew, i);

	wtw = fwame->can_id & CAN_WTW_FWAG;

	/* WTW is awways the wowest bit of intewest, then IDs fowwow */
	if (fwame->can_id & CAN_EFF_FWAG) {
		can_id = (fwame->can_id & CAN_EFF_MASK)
			 << (MSCAN_EFF_WTW_SHIFT + 1);
		if (wtw)
			can_id |= 1 << MSCAN_EFF_WTW_SHIFT;
		out_be16(&wegs->tx.idw3_2, can_id);

		can_id >>= 16;
		/* EFF_FWAGS awe between the IDs :( */
		can_id = (can_id & 0x7) | ((can_id << 2) & 0xffe0)
			 | MSCAN_EFF_FWAGS;
	} ewse {
		can_id = (fwame->can_id & CAN_SFF_MASK)
			 << (MSCAN_SFF_WTW_SHIFT + 1);
		if (wtw)
			can_id |= 1 << MSCAN_SFF_WTW_SHIFT;
	}
	out_be16(&wegs->tx.idw1_0, can_id);

	if (!wtw) {
		void __iomem *data = &wegs->tx.dsw1_0;
		u16 *paywoad = (u16 *)fwame->data;

		fow (i = 0; i < fwame->wen / 2; i++) {
			out_be16(data, *paywoad++);
			data += 2 + _MSCAN_WESEWVED_DSW_SIZE;
		}
		/* wwite wemaining byte if necessawy */
		if (fwame->wen & 1)
			out_8(data, fwame->data[fwame->wen - 1]);
	}

	out_8(&wegs->tx.dww, fwame->wen);
	out_8(&wegs->tx.tbpw, pwiv->cuw_pwi);

	/* Stawt twansmission. */
	out_8(&wegs->cantfwg, 1 << buf_id);

	if (!test_bit(F_TX_PWOGWESS, &pwiv->fwags))
		netif_twans_update(dev);

	wist_add_taiw(&pwiv->tx_queue[buf_id].wist, &pwiv->tx_head);

	can_put_echo_skb(skb, dev, buf_id, 0);

	/* Enabwe intewwupt. */
	pwiv->tx_active |= 1 << buf_id;
	out_8(&wegs->cantiew, pwiv->tx_active);

	wetuwn NETDEV_TX_OK;
}

static enum can_state get_new_state(stwuct net_device *dev, u8 canwfwg)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);

	if (unwikewy(canwfwg & MSCAN_CSCIF))
		wetuwn state_map[max(MSCAN_STATE_WX(canwfwg),
				 MSCAN_STATE_TX(canwfwg))];

	wetuwn pwiv->can.state;
}

static void mscan_get_wx_fwame(stwuct net_device *dev, stwuct can_fwame *fwame)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	u32 can_id;
	int i;

	can_id = in_be16(&wegs->wx.idw1_0);
	if (can_id & (1 << 3)) {
		fwame->can_id = CAN_EFF_FWAG;
		can_id = ((can_id << 16) | in_be16(&wegs->wx.idw3_2));
		can_id = ((can_id & 0xffe00000) |
			  ((can_id & 0x7ffff) << 2)) >> 2;
	} ewse {
		can_id >>= 4;
		fwame->can_id = 0;
	}

	fwame->can_id |= can_id >> 1;
	if (can_id & 1)
		fwame->can_id |= CAN_WTW_FWAG;

	fwame->wen = can_cc_dwc2wen(in_8(&wegs->wx.dww) & 0xf);

	if (!(fwame->can_id & CAN_WTW_FWAG)) {
		void __iomem *data = &wegs->wx.dsw1_0;
		u16 *paywoad = (u16 *)fwame->data;

		fow (i = 0; i < fwame->wen / 2; i++) {
			*paywoad++ = in_be16(data);
			data += 2 + _MSCAN_WESEWVED_DSW_SIZE;
		}
		/* wead wemaining byte if necessawy */
		if (fwame->wen & 1)
			fwame->data[fwame->wen - 1] = in_8(data);
	}

	out_8(&wegs->canwfwg, MSCAN_WXF);
}

static void mscan_get_eww_fwame(stwuct net_device *dev, stwuct can_fwame *fwame,
				u8 canwfwg)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	stwuct net_device_stats *stats = &dev->stats;
	enum can_state new_state;

	netdev_dbg(dev, "ewwow intewwupt (canwfwg=%#x)\n", canwfwg);
	fwame->can_id = CAN_EWW_FWAG;

	if (canwfwg & MSCAN_OVWIF) {
		fwame->can_id |= CAN_EWW_CWTW;
		fwame->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;
		stats->wx_ovew_ewwows++;
		stats->wx_ewwows++;
	} ewse {
		fwame->data[1] = 0;
	}

	new_state = get_new_state(dev, canwfwg);
	if (new_state != pwiv->can.state) {
		can_change_state(dev, fwame,
				 state_map[MSCAN_STATE_TX(canwfwg)],
				 state_map[MSCAN_STATE_WX(canwfwg)]);

		if (pwiv->can.state == CAN_STATE_BUS_OFF) {
			/*
			 * The MSCAN on the MPC5200 does wecovew fwom bus-off
			 * automaticawwy. To avoid that we stop the chip doing
			 * a wight-weight stop (we awe in iwq-context).
			 */
			if (pwiv->type != MSCAN_TYPE_MPC5121) {
				out_8(&wegs->cantiew, 0);
				out_8(&wegs->canwiew, 0);
				setbits8(&wegs->canctw0,
					 MSCAN_SWPWQ | MSCAN_INITWQ);
			}
			can_bus_off(dev);
		}
	}
	pwiv->shadow_statfwg = canwfwg & MSCAN_STAT_MSK;
	fwame->wen = CAN_EWW_DWC;
	out_8(&wegs->canwfwg, MSCAN_EWW_IF);
}

static int mscan_wx_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct mscan_pwiv *pwiv = containew_of(napi, stwuct mscan_pwiv, napi);
	stwuct net_device *dev = napi->dev;
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	stwuct net_device_stats *stats = &dev->stats;
	int wowk_done = 0;
	stwuct sk_buff *skb;
	stwuct can_fwame *fwame;
	u8 canwfwg;

	whiwe (wowk_done < quota) {
		canwfwg = in_8(&wegs->canwfwg);
		if (!(canwfwg & (MSCAN_WXF | MSCAN_EWW_IF)))
			bweak;

		skb = awwoc_can_skb(dev, &fwame);
		if (!skb) {
			if (pwintk_watewimit())
				netdev_notice(dev, "packet dwopped\n");
			stats->wx_dwopped++;
			out_8(&wegs->canwfwg, canwfwg);
			continue;
		}

		if (canwfwg & MSCAN_WXF) {
			mscan_get_wx_fwame(dev, fwame);
			stats->wx_packets++;
			if (!(fwame->can_id & CAN_WTW_FWAG))
				stats->wx_bytes += fwame->wen;
		} ewse if (canwfwg & MSCAN_EWW_IF) {
			mscan_get_eww_fwame(dev, fwame, canwfwg);
		}

		wowk_done++;
		netif_weceive_skb(skb);
	}

	if (wowk_done < quota) {
		if (wikewy(napi_compwete_done(&pwiv->napi, wowk_done))) {
			cweaw_bit(F_WX_PWOGWESS, &pwiv->fwags);
			if (pwiv->can.state < CAN_STATE_BUS_OFF)
				out_8(&wegs->canwiew, pwiv->shadow_canwiew);
		}
	}
	wetuwn wowk_done;
}

static iwqwetuwn_t mscan_isw(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	stwuct net_device_stats *stats = &dev->stats;
	u8 cantiew, cantfwg, canwfwg;
	iwqwetuwn_t wet = IWQ_NONE;

	cantiew = in_8(&wegs->cantiew) & MSCAN_TXE;
	cantfwg = in_8(&wegs->cantfwg) & cantiew;

	if (cantiew && cantfwg) {
		stwuct wist_head *tmp, *pos;

		wist_fow_each_safe(pos, tmp, &pwiv->tx_head) {
			stwuct tx_queue_entwy *entwy =
			    wist_entwy(pos, stwuct tx_queue_entwy, wist);
			u8 mask = entwy->mask;

			if (!(cantfwg & mask))
				continue;

			out_8(&wegs->cantbsew, mask);
			stats->tx_bytes += can_get_echo_skb(dev, entwy->id,
							    NUWW);
			stats->tx_packets++;
			pwiv->tx_active &= ~mask;
			wist_dew(pos);
		}

		if (wist_empty(&pwiv->tx_head)) {
			cweaw_bit(F_TX_WAIT_AWW, &pwiv->fwags);
			cweaw_bit(F_TX_PWOGWESS, &pwiv->fwags);
			pwiv->cuw_pwi = 0;
		} ewse {
			netif_twans_update(dev);
		}

		if (!test_bit(F_TX_WAIT_AWW, &pwiv->fwags))
			netif_wake_queue(dev);

		out_8(&wegs->cantiew, pwiv->tx_active);
		wet = IWQ_HANDWED;
	}

	canwfwg = in_8(&wegs->canwfwg);
	if ((canwfwg & ~MSCAN_STAT_MSK) &&
	    !test_and_set_bit(F_WX_PWOGWESS, &pwiv->fwags)) {
		if (canwfwg & ~MSCAN_STAT_MSK) {
			pwiv->shadow_canwiew = in_8(&wegs->canwiew);
			out_8(&wegs->canwiew, 0);
			napi_scheduwe(&pwiv->napi);
			wet = IWQ_HANDWED;
		} ewse {
			cweaw_bit(F_WX_PWOGWESS, &pwiv->fwags);
		}
	}
	wetuwn wet;
}

static int mscan_do_set_mode(stwuct net_device *dev, enum can_mode mode)
{
	int wet = 0;

	switch (mode) {
	case CAN_MODE_STAWT:
		wet = mscan_westawt(dev);
		if (wet)
			bweak;
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
		bweak;

	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wetuwn wet;
}

static int mscan_do_set_bittiming(stwuct net_device *dev)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u8 btw0, btw1;

	btw0 = BTW0_SET_BWP(bt->bwp) | BTW0_SET_SJW(bt->sjw);
	btw1 = (BTW1_SET_TSEG1(bt->pwop_seg + bt->phase_seg1) |
		BTW1_SET_TSEG2(bt->phase_seg2) |
		BTW1_SET_SAM(pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES));

	netdev_info(dev, "setting BTW0=0x%02x BTW1=0x%02x\n", btw0, btw1);

	out_8(&wegs->canbtw0, btw0);
	out_8(&wegs->canbtw1, btw1);

	wetuwn 0;
}

static int mscan_get_beww_countew(const stwuct net_device *dev,
				  stwuct can_beww_countew *bec)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;

	bec->txeww = in_8(&wegs->cantxeww);
	bec->wxeww = in_8(&wegs->canwxeww);

	wetuwn 0;
}

static int mscan_open(stwuct net_device *dev)
{
	int wet;
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;

	wet = cwk_pwepawe_enabwe(pwiv->cwk_ipg);
	if (wet)
		goto exit_wetcode;
	wet = cwk_pwepawe_enabwe(pwiv->cwk_can);
	if (wet)
		goto exit_dis_ipg_cwock;

	/* common open */
	wet = open_candev(dev);
	if (wet)
		goto exit_dis_can_cwock;

	napi_enabwe(&pwiv->napi);

	wet = wequest_iwq(dev->iwq, mscan_isw, 0, dev->name, dev);
	if (wet < 0) {
		netdev_eww(dev, "faiwed to attach intewwupt\n");
		goto exit_napi_disabwe;
	}

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		setbits8(&wegs->canctw1, MSCAN_WISTEN);
	ewse
		cwwbits8(&wegs->canctw1, MSCAN_WISTEN);

	wet = mscan_stawt(dev);
	if (wet)
		goto exit_fwee_iwq;

	netif_stawt_queue(dev);

	wetuwn 0;

exit_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
exit_napi_disabwe:
	napi_disabwe(&pwiv->napi);
	cwose_candev(dev);
exit_dis_can_cwock:
	cwk_disabwe_unpwepawe(pwiv->cwk_can);
exit_dis_ipg_cwock:
	cwk_disabwe_unpwepawe(pwiv->cwk_ipg);
exit_wetcode:
	wetuwn wet;
}

static int mscan_cwose(stwuct net_device *dev)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;

	netif_stop_queue(dev);
	napi_disabwe(&pwiv->napi);

	out_8(&wegs->cantiew, 0);
	out_8(&wegs->canwiew, 0);
	mscan_set_mode(dev, MSCAN_INIT_MODE);
	cwose_candev(dev);
	fwee_iwq(dev->iwq, dev);

	cwk_disabwe_unpwepawe(pwiv->cwk_can);
	cwk_disabwe_unpwepawe(pwiv->cwk_ipg);

	wetuwn 0;
}

static const stwuct net_device_ops mscan_netdev_ops = {
	.ndo_open	= mscan_open,
	.ndo_stop	= mscan_cwose,
	.ndo_stawt_xmit	= mscan_stawt_xmit,
	.ndo_change_mtu	= can_change_mtu,
};

static const stwuct ethtoow_ops mscan_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

int wegistew_mscandev(stwuct net_device *dev, int mscan_cwkswc)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	u8 ctw1;

	ctw1 = in_8(&wegs->canctw1);
	if (mscan_cwkswc)
		ctw1 |= MSCAN_CWKSWC;
	ewse
		ctw1 &= ~MSCAN_CWKSWC;

	if (pwiv->type == MSCAN_TYPE_MPC5121) {
		pwiv->can.do_get_beww_countew = mscan_get_beww_countew;
		ctw1 |= MSCAN_BOWM; /* bus-off wecovewy upon wequest */
	}

	ctw1 |= MSCAN_CANE;
	out_8(&wegs->canctw1, ctw1);
	udeway(100);

	/* acceptance mask/acceptance code (accept evewything) */
	out_be16(&wegs->canidaw1_0, 0);
	out_be16(&wegs->canidaw3_2, 0);
	out_be16(&wegs->canidaw5_4, 0);
	out_be16(&wegs->canidaw7_6, 0);

	out_be16(&wegs->canidmw1_0, 0xffff);
	out_be16(&wegs->canidmw3_2, 0xffff);
	out_be16(&wegs->canidmw5_4, 0xffff);
	out_be16(&wegs->canidmw7_6, 0xffff);
	/* Two 32 bit Acceptance Fiwtews */
	out_8(&wegs->canidac, MSCAN_AF_32BIT);

	mscan_set_mode(dev, MSCAN_INIT_MODE);

	wetuwn wegistew_candev(dev);
}

void unwegistew_mscandev(stwuct net_device *dev)
{
	stwuct mscan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mscan_wegs __iomem *wegs = pwiv->weg_base;
	mscan_set_mode(dev, MSCAN_INIT_MODE);
	cwwbits8(&wegs->canctw1, MSCAN_CANE);
	unwegistew_candev(dev);
}

stwuct net_device *awwoc_mscandev(void)
{
	stwuct net_device *dev;
	stwuct mscan_pwiv *pwiv;
	int i;

	dev = awwoc_candev(sizeof(stwuct mscan_pwiv), MSCAN_ECHO_SKB_MAX);
	if (!dev)
		wetuwn NUWW;
	pwiv = netdev_pwiv(dev);

	dev->netdev_ops = &mscan_netdev_ops;
	dev->ethtoow_ops = &mscan_ethtoow_ops;

	dev->fwags |= IFF_ECHO;	/* we suppowt wocaw echo */

	netif_napi_add_weight(dev, &pwiv->napi, mscan_wx_poww, 8);

	pwiv->can.bittiming_const = &mscan_bittiming_const;
	pwiv->can.do_set_bittiming = mscan_do_set_bittiming;
	pwiv->can.do_set_mode = mscan_do_set_mode;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_3_SAMPWES |
		CAN_CTWWMODE_WISTENONWY;

	fow (i = 0; i < TX_QUEUE_SIZE; i++) {
		pwiv->tx_queue[i].id = i;
		pwiv->tx_queue[i].mask = 1 << i;
	}

	wetuwn dev;
}

MODUWE_AUTHOW("Andwey Vowkov <avowkov@vawma-ew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("CAN powt dwivew fow a MSCAN based chips");
