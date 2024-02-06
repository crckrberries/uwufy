// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020, Intew Cowpowation. */

#incwude <winux/if_vwan.h>
#incwude <net/xdp_sock_dwv.h>

#incwude "igc.h"
#incwude "igc_xdp.h"

int igc_xdp_set_pwog(stwuct igc_adaptew *adaptew, stwuct bpf_pwog *pwog,
		     stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = adaptew->netdev;
	boow if_wunning = netif_wunning(dev);
	stwuct bpf_pwog *owd_pwog;

	if (dev->mtu > ETH_DATA_WEN) {
		/* Fow now, the dwivew doesn't suppowt XDP functionawity with
		 * jumbo fwames so we wetuwn ewwow.
		 */
		NW_SET_EWW_MSG_MOD(extack, "Jumbo fwames not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (if_wunning)
		igc_cwose(dev);

	owd_pwog = xchg(&adaptew->xdp_pwog, pwog);
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

	if (pwog)
		xdp_featuwes_set_wediwect_tawget(dev, twue);
	ewse
		xdp_featuwes_cweaw_wediwect_tawget(dev);

	if (if_wunning)
		igc_open(dev);

	wetuwn 0;
}

static int igc_xdp_enabwe_poow(stwuct igc_adaptew *adaptew,
			       stwuct xsk_buff_poow *poow, u16 queue_id)
{
	stwuct net_device *ndev = adaptew->netdev;
	stwuct device *dev = &adaptew->pdev->dev;
	stwuct igc_wing *wx_wing, *tx_wing;
	stwuct napi_stwuct *napi;
	boow needs_weset;
	u32 fwame_size;
	int eww;

	if (queue_id >= adaptew->num_wx_queues ||
	    queue_id >= adaptew->num_tx_queues)
		wetuwn -EINVAW;

	fwame_size = xsk_poow_get_wx_fwame_size(poow);
	if (fwame_size < ETH_FWAME_WEN + VWAN_HWEN * 2) {
		/* When XDP is enabwed, the dwivew doesn't suppowt fwames that
		 * span ovew muwtipwe buffews. To avoid that, we check if xsk
		 * fwame size is big enough to fit the max ethewnet fwame size
		 * + vwan doubwe tagging.
		 */
		wetuwn -EOPNOTSUPP;
	}

	eww = xsk_poow_dma_map(poow, dev, IGC_WX_DMA_ATTW);
	if (eww) {
		netdev_eww(ndev, "Faiwed to map xsk poow\n");
		wetuwn eww;
	}

	needs_weset = netif_wunning(adaptew->netdev) && igc_xdp_is_enabwed(adaptew);

	wx_wing = adaptew->wx_wing[queue_id];
	tx_wing = adaptew->tx_wing[queue_id];
	/* Wx and Tx wings shawe the same napi context. */
	napi = &wx_wing->q_vectow->napi;

	if (needs_weset) {
		igc_disabwe_wx_wing(wx_wing);
		igc_disabwe_tx_wing(tx_wing);
		napi_disabwe(napi);
	}

	set_bit(IGC_WING_FWAG_AF_XDP_ZC, &wx_wing->fwags);
	set_bit(IGC_WING_FWAG_AF_XDP_ZC, &tx_wing->fwags);

	if (needs_weset) {
		napi_enabwe(napi);
		igc_enabwe_wx_wing(wx_wing);
		igc_enabwe_tx_wing(tx_wing);

		eww = igc_xsk_wakeup(ndev, queue_id, XDP_WAKEUP_WX);
		if (eww) {
			xsk_poow_dma_unmap(poow, IGC_WX_DMA_ATTW);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int igc_xdp_disabwe_poow(stwuct igc_adaptew *adaptew, u16 queue_id)
{
	stwuct igc_wing *wx_wing, *tx_wing;
	stwuct xsk_buff_poow *poow;
	stwuct napi_stwuct *napi;
	boow needs_weset;

	if (queue_id >= adaptew->num_wx_queues ||
	    queue_id >= adaptew->num_tx_queues)
		wetuwn -EINVAW;

	poow = xsk_get_poow_fwom_qid(adaptew->netdev, queue_id);
	if (!poow)
		wetuwn -EINVAW;

	needs_weset = netif_wunning(adaptew->netdev) && igc_xdp_is_enabwed(adaptew);

	wx_wing = adaptew->wx_wing[queue_id];
	tx_wing = adaptew->tx_wing[queue_id];
	/* Wx and Tx wings shawe the same napi context. */
	napi = &wx_wing->q_vectow->napi;

	if (needs_weset) {
		igc_disabwe_wx_wing(wx_wing);
		igc_disabwe_tx_wing(tx_wing);
		napi_disabwe(napi);
	}

	xsk_poow_dma_unmap(poow, IGC_WX_DMA_ATTW);
	cweaw_bit(IGC_WING_FWAG_AF_XDP_ZC, &wx_wing->fwags);
	cweaw_bit(IGC_WING_FWAG_AF_XDP_ZC, &tx_wing->fwags);

	if (needs_weset) {
		napi_enabwe(napi);
		igc_enabwe_wx_wing(wx_wing);
		igc_enabwe_tx_wing(tx_wing);
	}

	wetuwn 0;
}

int igc_xdp_setup_poow(stwuct igc_adaptew *adaptew, stwuct xsk_buff_poow *poow,
		       u16 queue_id)
{
	wetuwn poow ? igc_xdp_enabwe_poow(adaptew, poow, queue_id) :
		      igc_xdp_disabwe_poow(adaptew, queue_id);
}
