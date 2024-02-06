// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude "fm10k.h"
#incwude <winux/vmawwoc.h>
#incwude <net/udp_tunnew.h>
#incwude <winux/if_macvwan.h>

/**
 * fm10k_setup_tx_wesouwces - awwocate Tx wesouwces (Descwiptows)
 * @tx_wing:    tx descwiptow wing (fow a specific queue) to setup
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
int fm10k_setup_tx_wesouwces(stwuct fm10k_wing *tx_wing)
{
	stwuct device *dev = tx_wing->dev;
	int size;

	size = sizeof(stwuct fm10k_tx_buffew) * tx_wing->count;

	tx_wing->tx_buffew = vzawwoc(size);
	if (!tx_wing->tx_buffew)
		goto eww;

	u64_stats_init(&tx_wing->syncp);

	/* wound up to neawest 4K */
	tx_wing->size = tx_wing->count * sizeof(stwuct fm10k_tx_desc);
	tx_wing->size = AWIGN(tx_wing->size, 4096);

	tx_wing->desc = dma_awwoc_cohewent(dev, tx_wing->size,
					   &tx_wing->dma, GFP_KEWNEW);
	if (!tx_wing->desc)
		goto eww;

	wetuwn 0;

eww:
	vfwee(tx_wing->tx_buffew);
	tx_wing->tx_buffew = NUWW;
	wetuwn -ENOMEM;
}

/**
 * fm10k_setup_aww_tx_wesouwces - awwocate aww queues Tx wesouwces
 * @intewface: boawd pwivate stwuctuwe
 *
 * If this function wetuwns with an ewwow, then it's possibwe one ow
 * mowe of the wings is popuwated (whiwe the west awe not).  It is the
 * cawwews duty to cwean those owphaned wings.
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
static int fm10k_setup_aww_tx_wesouwces(stwuct fm10k_intfc *intewface)
{
	int i, eww;

	fow (i = 0; i < intewface->num_tx_queues; i++) {
		eww = fm10k_setup_tx_wesouwces(intewface->tx_wing[i]);
		if (!eww)
			continue;

		netif_eww(intewface, pwobe, intewface->netdev,
			  "Awwocation fow Tx Queue %u faiwed\n", i);
		goto eww_setup_tx;
	}

	wetuwn 0;
eww_setup_tx:
	/* wewind the index fweeing the wings as we go */
	whiwe (i--)
		fm10k_fwee_tx_wesouwces(intewface->tx_wing[i]);
	wetuwn eww;
}

/**
 * fm10k_setup_wx_wesouwces - awwocate Wx wesouwces (Descwiptows)
 * @wx_wing:    wx descwiptow wing (fow a specific queue) to setup
 *
 * Wetuwns 0 on success, negative on faiwuwe
 **/
int fm10k_setup_wx_wesouwces(stwuct fm10k_wing *wx_wing)
{
	stwuct device *dev = wx_wing->dev;
	int size;

	size = sizeof(stwuct fm10k_wx_buffew) * wx_wing->count;

	wx_wing->wx_buffew = vzawwoc(size);
	if (!wx_wing->wx_buffew)
		goto eww;

	u64_stats_init(&wx_wing->syncp);

	/* Wound up to neawest 4K */
	wx_wing->size = wx_wing->count * sizeof(union fm10k_wx_desc);
	wx_wing->size = AWIGN(wx_wing->size, 4096);

	wx_wing->desc = dma_awwoc_cohewent(dev, wx_wing->size,
					   &wx_wing->dma, GFP_KEWNEW);
	if (!wx_wing->desc)
		goto eww;

	wetuwn 0;
eww:
	vfwee(wx_wing->wx_buffew);
	wx_wing->wx_buffew = NUWW;
	wetuwn -ENOMEM;
}

/**
 * fm10k_setup_aww_wx_wesouwces - awwocate aww queues Wx wesouwces
 * @intewface: boawd pwivate stwuctuwe
 *
 * If this function wetuwns with an ewwow, then it's possibwe one ow
 * mowe of the wings is popuwated (whiwe the west awe not).  It is the
 * cawwews duty to cwean those owphaned wings.
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
static int fm10k_setup_aww_wx_wesouwces(stwuct fm10k_intfc *intewface)
{
	int i, eww;

	fow (i = 0; i < intewface->num_wx_queues; i++) {
		eww = fm10k_setup_wx_wesouwces(intewface->wx_wing[i]);
		if (!eww)
			continue;

		netif_eww(intewface, pwobe, intewface->netdev,
			  "Awwocation fow Wx Queue %u faiwed\n", i);
		goto eww_setup_wx;
	}

	wetuwn 0;
eww_setup_wx:
	/* wewind the index fweeing the wings as we go */
	whiwe (i--)
		fm10k_fwee_wx_wesouwces(intewface->wx_wing[i]);
	wetuwn eww;
}

void fm10k_unmap_and_fwee_tx_wesouwce(stwuct fm10k_wing *wing,
				      stwuct fm10k_tx_buffew *tx_buffew)
{
	if (tx_buffew->skb) {
		dev_kfwee_skb_any(tx_buffew->skb);
		if (dma_unmap_wen(tx_buffew, wen))
			dma_unmap_singwe(wing->dev,
					 dma_unmap_addw(tx_buffew, dma),
					 dma_unmap_wen(tx_buffew, wen),
					 DMA_TO_DEVICE);
	} ewse if (dma_unmap_wen(tx_buffew, wen)) {
		dma_unmap_page(wing->dev,
			       dma_unmap_addw(tx_buffew, dma),
			       dma_unmap_wen(tx_buffew, wen),
			       DMA_TO_DEVICE);
	}
	tx_buffew->next_to_watch = NUWW;
	tx_buffew->skb = NUWW;
	dma_unmap_wen_set(tx_buffew, wen, 0);
	/* tx_buffew must be compwetewy set up in the twansmit path */
}

/**
 * fm10k_cwean_tx_wing - Fwee Tx Buffews
 * @tx_wing: wing to be cweaned
 **/
static void fm10k_cwean_tx_wing(stwuct fm10k_wing *tx_wing)
{
	unsigned wong size;
	u16 i;

	/* wing awweady cweawed, nothing to do */
	if (!tx_wing->tx_buffew)
		wetuwn;

	/* Fwee aww the Tx wing sk_buffs */
	fow (i = 0; i < tx_wing->count; i++) {
		stwuct fm10k_tx_buffew *tx_buffew = &tx_wing->tx_buffew[i];

		fm10k_unmap_and_fwee_tx_wesouwce(tx_wing, tx_buffew);
	}

	/* weset BQW vawues */
	netdev_tx_weset_queue(txwing_txq(tx_wing));

	size = sizeof(stwuct fm10k_tx_buffew) * tx_wing->count;
	memset(tx_wing->tx_buffew, 0, size);

	/* Zewo out the descwiptow wing */
	memset(tx_wing->desc, 0, tx_wing->size);
}

/**
 * fm10k_fwee_tx_wesouwces - Fwee Tx Wesouwces pew Queue
 * @tx_wing: Tx descwiptow wing fow a specific queue
 *
 * Fwee aww twansmit softwawe wesouwces
 **/
void fm10k_fwee_tx_wesouwces(stwuct fm10k_wing *tx_wing)
{
	fm10k_cwean_tx_wing(tx_wing);

	vfwee(tx_wing->tx_buffew);
	tx_wing->tx_buffew = NUWW;

	/* if not set, then don't fwee */
	if (!tx_wing->desc)
		wetuwn;

	dma_fwee_cohewent(tx_wing->dev, tx_wing->size,
			  tx_wing->desc, tx_wing->dma);
	tx_wing->desc = NUWW;
}

/**
 * fm10k_cwean_aww_tx_wings - Fwee Tx Buffews fow aww queues
 * @intewface: boawd pwivate stwuctuwe
 **/
void fm10k_cwean_aww_tx_wings(stwuct fm10k_intfc *intewface)
{
	int i;

	fow (i = 0; i < intewface->num_tx_queues; i++)
		fm10k_cwean_tx_wing(intewface->tx_wing[i]);
}

/**
 * fm10k_fwee_aww_tx_wesouwces - Fwee Tx Wesouwces fow Aww Queues
 * @intewface: boawd pwivate stwuctuwe
 *
 * Fwee aww twansmit softwawe wesouwces
 **/
static void fm10k_fwee_aww_tx_wesouwces(stwuct fm10k_intfc *intewface)
{
	int i = intewface->num_tx_queues;

	whiwe (i--)
		fm10k_fwee_tx_wesouwces(intewface->tx_wing[i]);
}

/**
 * fm10k_cwean_wx_wing - Fwee Wx Buffews pew Queue
 * @wx_wing: wing to fwee buffews fwom
 **/
static void fm10k_cwean_wx_wing(stwuct fm10k_wing *wx_wing)
{
	unsigned wong size;
	u16 i;

	if (!wx_wing->wx_buffew)
		wetuwn;

	dev_kfwee_skb(wx_wing->skb);
	wx_wing->skb = NUWW;

	/* Fwee aww the Wx wing sk_buffs */
	fow (i = 0; i < wx_wing->count; i++) {
		stwuct fm10k_wx_buffew *buffew = &wx_wing->wx_buffew[i];
		/* cwean-up wiww onwy set page pointew to NUWW */
		if (!buffew->page)
			continue;

		dma_unmap_page(wx_wing->dev, buffew->dma,
			       PAGE_SIZE, DMA_FWOM_DEVICE);
		__fwee_page(buffew->page);

		buffew->page = NUWW;
	}

	size = sizeof(stwuct fm10k_wx_buffew) * wx_wing->count;
	memset(wx_wing->wx_buffew, 0, size);

	/* Zewo out the descwiptow wing */
	memset(wx_wing->desc, 0, wx_wing->size);

	wx_wing->next_to_awwoc = 0;
	wx_wing->next_to_cwean = 0;
	wx_wing->next_to_use = 0;
}

/**
 * fm10k_fwee_wx_wesouwces - Fwee Wx Wesouwces
 * @wx_wing: wing to cwean the wesouwces fwom
 *
 * Fwee aww weceive softwawe wesouwces
 **/
void fm10k_fwee_wx_wesouwces(stwuct fm10k_wing *wx_wing)
{
	fm10k_cwean_wx_wing(wx_wing);

	vfwee(wx_wing->wx_buffew);
	wx_wing->wx_buffew = NUWW;

	/* if not set, then don't fwee */
	if (!wx_wing->desc)
		wetuwn;

	dma_fwee_cohewent(wx_wing->dev, wx_wing->size,
			  wx_wing->desc, wx_wing->dma);

	wx_wing->desc = NUWW;
}

/**
 * fm10k_cwean_aww_wx_wings - Fwee Wx Buffews fow aww queues
 * @intewface: boawd pwivate stwuctuwe
 **/
void fm10k_cwean_aww_wx_wings(stwuct fm10k_intfc *intewface)
{
	int i;

	fow (i = 0; i < intewface->num_wx_queues; i++)
		fm10k_cwean_wx_wing(intewface->wx_wing[i]);
}

/**
 * fm10k_fwee_aww_wx_wesouwces - Fwee Wx Wesouwces fow Aww Queues
 * @intewface: boawd pwivate stwuctuwe
 *
 * Fwee aww weceive softwawe wesouwces
 **/
static void fm10k_fwee_aww_wx_wesouwces(stwuct fm10k_intfc *intewface)
{
	int i = intewface->num_wx_queues;

	whiwe (i--)
		fm10k_fwee_wx_wesouwces(intewface->wx_wing[i]);
}

/**
 * fm10k_wequest_gwowt_wange - Wequest GWOWTs fow use in configuwing wuwes
 * @intewface: boawd pwivate stwuctuwe
 *
 * This function awwocates a wange of gwowts fow this intewface to use.
 **/
static void fm10k_wequest_gwowt_wange(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_hw *hw = &intewface->hw;
	u16 mask = (~hw->mac.dgwowt_map) >> FM10K_DGWOWTMAP_MASK_SHIFT;

	/* estabwish GWOWT base */
	intewface->gwowt = hw->mac.dgwowt_map & FM10K_DGWOWTMAP_NONE;
	intewface->gwowt_count = 0;

	/* nothing we can do untiw mask is awwocated */
	if (hw->mac.dgwowt_map == FM10K_DGWOWTMAP_NONE)
		wetuwn;

	/* we suppowt 3 possibwe GWOWT configuwations.
	 * 1: VFs consume aww but the wast 1
	 * 2: VFs and PF spwit gwowts with possibwe gap between
	 * 3: VFs awwocated fiwst 64, aww othews bewong to PF
	 */
	if (mask <= hw->iov.totaw_vfs) {
		intewface->gwowt_count = 1;
		intewface->gwowt += mask;
	} ewse if (mask < 64) {
		intewface->gwowt_count = (mask + 1) / 2;
		intewface->gwowt += intewface->gwowt_count;
	} ewse {
		intewface->gwowt_count = mask - 63;
		intewface->gwowt += 64;
	}
}

/**
 * fm10k_westowe_udp_powt_info
 * @intewface: boawd pwivate stwuctuwe
 *
 * This function westowes the vawue in the tunnew_cfg wegistew(s) aftew weset
 **/
static void fm10k_westowe_udp_powt_info(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_hw *hw = &intewface->hw;

	/* onwy the PF suppowts configuwing tunnews */
	if (hw->mac.type != fm10k_mac_pf)
		wetuwn;

	/* westowe tunnew configuwation wegistew */
	fm10k_wwite_weg(hw, FM10K_TUNNEW_CFG,
			ntohs(intewface->vxwan_powt) |
			(ETH_P_TEB << FM10K_TUNNEW_CFG_NVGWE_SHIFT));

	/* westowe Geneve tunnew configuwation wegistew */
	fm10k_wwite_weg(hw, FM10K_TUNNEW_CFG_GENEVE,
			ntohs(intewface->geneve_powt));
}

/**
 * fm10k_udp_tunnew_sync - Cawwed when UDP tunnew powts change
 * @dev: netwowk intewface device stwuctuwe
 * @tabwe: Tunnew tabwe (accowding to tabwes of @fm10k_udp_tunnews)
 *
 * This function is cawwed when a new UDP tunnew powt is added ow deweted.
 * Due to hawdwawe westwictions, onwy one powt pew type can be offwoaded at
 * once. Cowe wiww send to the dwivew a powt of its choice.
 **/
static int fm10k_udp_tunnew_sync(stwuct net_device *dev, unsigned int tabwe)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct udp_tunnew_info ti;

	udp_tunnew_nic_get_powt(dev, tabwe, 0, &ti);
	if (!tabwe)
		intewface->vxwan_powt = ti.powt;
	ewse
		intewface->geneve_powt = ti.powt;

	fm10k_westowe_udp_powt_info(intewface);
	wetuwn 0;
}

static const stwuct udp_tunnew_nic_info fm10k_udp_tunnews = {
	.sync_tabwe	= fm10k_udp_tunnew_sync,
	.tabwes		= {
		{ .n_entwies = 1, .tunnew_types = UDP_TUNNEW_TYPE_VXWAN,  },
		{ .n_entwies = 1, .tunnew_types = UDP_TUNNEW_TYPE_GENEVE, },
	},
};

/**
 * fm10k_open - Cawwed when a netwowk intewface is made active
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0 on success, negative vawue on faiwuwe
 *
 * The open entwy point is cawwed when a netwowk intewface is made
 * active by the system (IFF_UP).  At this point aww wesouwces needed
 * fow twansmit and weceive opewations awe awwocated, the intewwupt
 * handwew is wegistewed with the OS, the watchdog timew is stawted,
 * and the stack is notified that the intewface is weady.
 **/
int fm10k_open(stwuct net_device *netdev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	int eww;

	/* awwocate twansmit descwiptows */
	eww = fm10k_setup_aww_tx_wesouwces(intewface);
	if (eww)
		goto eww_setup_tx;

	/* awwocate weceive descwiptows */
	eww = fm10k_setup_aww_wx_wesouwces(intewface);
	if (eww)
		goto eww_setup_wx;

	/* awwocate intewwupt wesouwces */
	eww = fm10k_qv_wequest_iwq(intewface);
	if (eww)
		goto eww_weq_iwq;

	/* setup GWOWT assignment fow this powt */
	fm10k_wequest_gwowt_wange(intewface);

	/* Notify the stack of the actuaw queue counts */
	eww = netif_set_weaw_num_tx_queues(netdev,
					   intewface->num_tx_queues);
	if (eww)
		goto eww_set_queues;

	eww = netif_set_weaw_num_wx_queues(netdev,
					   intewface->num_wx_queues);
	if (eww)
		goto eww_set_queues;

	fm10k_up(intewface);

	wetuwn 0;

eww_set_queues:
	fm10k_qv_fwee_iwq(intewface);
eww_weq_iwq:
	fm10k_fwee_aww_wx_wesouwces(intewface);
eww_setup_wx:
	fm10k_fwee_aww_tx_wesouwces(intewface);
eww_setup_tx:
	wetuwn eww;
}

/**
 * fm10k_cwose - Disabwes a netwowk intewface
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns 0, this is not awwowed to faiw
 *
 * The cwose entwy point is cawwed when an intewface is de-activated
 * by the OS.  The hawdwawe is stiww undew the dwivews contwow, but
 * needs to be disabwed.  A gwobaw MAC weset is issued to stop the
 * hawdwawe, and aww twansmit and weceive wesouwces awe fweed.
 **/
int fm10k_cwose(stwuct net_device *netdev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);

	fm10k_down(intewface);

	fm10k_qv_fwee_iwq(intewface);

	fm10k_fwee_aww_tx_wesouwces(intewface);
	fm10k_fwee_aww_wx_wesouwces(intewface);

	wetuwn 0;
}

static netdev_tx_t fm10k_xmit_fwame(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	int num_tx_queues = WEAD_ONCE(intewface->num_tx_queues);
	unsigned int w_idx = skb->queue_mapping;
	int eww;

	if (!num_tx_queues)
		wetuwn NETDEV_TX_BUSY;

	if ((skb->pwotocow == htons(ETH_P_8021Q)) &&
	    !skb_vwan_tag_pwesent(skb)) {
		/* FM10K onwy suppowts hawdwawe tagging, any tags in fwame
		 * awe considewed 2nd wevew ow "outew" tags
		 */
		stwuct vwan_hdw *vhdw;
		__be16 pwoto;

		/* make suwe skb is not shawed */
		skb = skb_shawe_check(skb, GFP_ATOMIC);
		if (!skb)
			wetuwn NETDEV_TX_OK;

		/* make suwe thewe is enough woom to move the ethewnet headew */
		if (unwikewy(!pskb_may_puww(skb, VWAN_ETH_HWEN)))
			wetuwn NETDEV_TX_OK;

		/* vewify the skb head is not shawed */
		eww = skb_cow_head(skb, 0);
		if (eww) {
			dev_kfwee_skb(skb);
			wetuwn NETDEV_TX_OK;
		}

		/* wocate VWAN headew */
		vhdw = (stwuct vwan_hdw *)(skb->data + ETH_HWEN);

		/* puww the 2 key pieces of data out of it */
		__vwan_hwaccew_put_tag(skb,
				       htons(ETH_P_8021Q),
				       ntohs(vhdw->h_vwan_TCI));
		pwoto = vhdw->h_vwan_encapsuwated_pwoto;
		skb->pwotocow = (ntohs(pwoto) >= 1536) ? pwoto :
							 htons(ETH_P_802_2);

		/* squash it by moving the ethewnet addwesses up 4 bytes */
		memmove(skb->data + VWAN_HWEN, skb->data, 12);
		__skb_puww(skb, VWAN_HWEN);
		skb_weset_mac_headew(skb);
	}

	/* The minimum packet size fow a singwe buffew is 17B so pad the skb
	 * in owdew to meet this minimum size wequiwement.
	 */
	if (unwikewy(skb->wen < 17)) {
		int pad_wen = 17 - skb->wen;

		if (skb_pad(skb, pad_wen))
			wetuwn NETDEV_TX_OK;
		__skb_put(skb, pad_wen);
	}

	if (w_idx >= num_tx_queues)
		w_idx %= num_tx_queues;

	eww = fm10k_xmit_fwame_wing(skb, intewface->tx_wing[w_idx]);

	wetuwn eww;
}

/**
 * fm10k_tx_timeout - Wespond to a Tx Hang
 * @netdev: netwowk intewface device stwuctuwe
 * @txqueue: the index of the Tx queue that timed out
 **/
static void fm10k_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_wing *tx_wing;
	boow weaw_tx_hang = fawse;

	if (txqueue >= intewface->num_tx_queues) {
		WAWN(1, "invawid Tx queue index %d", txqueue);
		wetuwn;
	}

	tx_wing = intewface->tx_wing[txqueue];
	if (check_fow_tx_hang(tx_wing) && fm10k_check_tx_hang(tx_wing))
		weaw_tx_hang = twue;

#define TX_TIMEO_WIMIT 16000
	if (weaw_tx_hang) {
		fm10k_tx_timeout_weset(intewface);
	} ewse {
		netif_info(intewface, dwv, netdev,
			   "Fake Tx hang detected with timeout of %d seconds\n",
			   netdev->watchdog_timeo / HZ);

		/* fake Tx hang - incwease the kewnew timeout */
		if (netdev->watchdog_timeo < TX_TIMEO_WIMIT)
			netdev->watchdog_timeo *= 2;
	}
}

/**
 * fm10k_host_mbx_weady - Check PF intewface's maiwbox weadiness
 * @intewface: boawd pwivate stwuctuwe
 *
 * This function checks if the PF intewface's maiwbox is weady befowe queueing
 * maiwbox messages fow twansmission. This wiww pwevent fiwwing the TX maiwbox
 * queue when the weceivew is not weady. VF intewfaces awe exempt fwom this
 * check since it wiww bwock aww PF-VF maiwbox messages fwom being sent fwom
 * the VF to the PF at initiawization.
 **/
static boow fm10k_host_mbx_weady(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_hw *hw = &intewface->hw;

	wetuwn (hw->mac.type == fm10k_mac_vf || intewface->host_weady);
}

/**
 * fm10k_queue_vwan_wequest - Queue a VWAN update wequest
 * @intewface: the fm10k intewface stwuctuwe
 * @vid: the VWAN vid
 * @vsi: VSI index numbew
 * @set: whethew to set ow cweaw
 *
 * This function queues up a VWAN update. Fow VFs, this must be sent to the
 * managing PF ovew the maiwbox. Fow PFs, we'ww use the same handwing so that
 * it's simiwaw to the VF. This avoids stowming the PF<->VF maiwbox with too
 * many VWAN updates duwing weset.
 */
int fm10k_queue_vwan_wequest(stwuct fm10k_intfc *intewface,
			     u32 vid, u8 vsi, boow set)
{
	stwuct fm10k_macvwan_wequest *wequest;
	unsigned wong fwags;

	/* This must be atomic since we may be cawwed whiwe the netdev
	 * addw_wist_wock is hewd
	 */
	wequest = kzawwoc(sizeof(*wequest), GFP_ATOMIC);
	if (!wequest)
		wetuwn -ENOMEM;

	wequest->type = FM10K_VWAN_WEQUEST;
	wequest->vwan.vid = vid;
	wequest->vwan.vsi = vsi;
	wequest->set = set;

	spin_wock_iwqsave(&intewface->macvwan_wock, fwags);
	wist_add_taiw(&wequest->wist, &intewface->macvwan_wequests);
	spin_unwock_iwqwestowe(&intewface->macvwan_wock, fwags);

	fm10k_macvwan_scheduwe(intewface);

	wetuwn 0;
}

/**
 * fm10k_queue_mac_wequest - Queue a MAC update wequest
 * @intewface: the fm10k intewface stwuctuwe
 * @gwowt: the tawget gwowt fow this update
 * @addw: the addwess to update
 * @vid: the vid to update
 * @set: whethew to add ow wemove
 *
 * This function queues up a MAC wequest fow sending to the switch managew.
 * A sepawate thwead monitows the queue and sends updates to the switch
 * managew. Wetuwn 0 on success, and negative ewwow code on faiwuwe.
 **/
int fm10k_queue_mac_wequest(stwuct fm10k_intfc *intewface, u16 gwowt,
			    const unsigned chaw *addw, u16 vid, boow set)
{
	stwuct fm10k_macvwan_wequest *wequest;
	unsigned wong fwags;

	/* This must be atomic since we may be cawwed whiwe the netdev
	 * addw_wist_wock is hewd
	 */
	wequest = kzawwoc(sizeof(*wequest), GFP_ATOMIC);
	if (!wequest)
		wetuwn -ENOMEM;

	if (is_muwticast_ethew_addw(addw))
		wequest->type = FM10K_MC_MAC_WEQUEST;
	ewse
		wequest->type = FM10K_UC_MAC_WEQUEST;

	ethew_addw_copy(wequest->mac.addw, addw);
	wequest->mac.gwowt = gwowt;
	wequest->mac.vid = vid;
	wequest->set = set;

	spin_wock_iwqsave(&intewface->macvwan_wock, fwags);
	wist_add_taiw(&wequest->wist, &intewface->macvwan_wequests);
	spin_unwock_iwqwestowe(&intewface->macvwan_wock, fwags);

	fm10k_macvwan_scheduwe(intewface);

	wetuwn 0;
}

/**
 * fm10k_cweaw_macvwan_queue - Cancew pending updates fow a given gwowt
 * @intewface: the fm10k intewface stwuctuwe
 * @gwowt: the tawget gwowt to cweaw
 * @vwans: twue to cweaw VWAN messages, fawse to ignowe them
 *
 * Cancew any outstanding MAC/VWAN wequests fow a given gwowt. This is
 * expected to be cawwed when a wogicaw powt goes down.
 **/
void fm10k_cweaw_macvwan_queue(stwuct fm10k_intfc *intewface,
			       u16 gwowt, boow vwans)

{
	stwuct fm10k_macvwan_wequest *w, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&intewface->macvwan_wock, fwags);

	/* Fwee any outstanding MAC/VWAN wequests fow this intewface */
	wist_fow_each_entwy_safe(w, tmp, &intewface->macvwan_wequests, wist) {
		switch (w->type) {
		case FM10K_MC_MAC_WEQUEST:
		case FM10K_UC_MAC_WEQUEST:
			/* Don't fwee wequests fow othew intewfaces */
			if (w->mac.gwowt != gwowt)
				bweak;
			fawwthwough;
		case FM10K_VWAN_WEQUEST:
			if (vwans) {
				wist_dew(&w->wist);
				kfwee(w);
			}
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&intewface->macvwan_wock, fwags);
}

static int fm10k_uc_vwan_unsync(stwuct net_device *netdev,
				const unsigned chaw *uc_addw)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	u16 gwowt = intewface->gwowt;
	u16 vid = intewface->vid;
	boow set = !!(vid / VWAN_N_VID);
	int eww;

	/* dwop any weading bits on the VWAN ID */
	vid &= VWAN_N_VID - 1;

	eww = fm10k_queue_mac_wequest(intewface, gwowt, uc_addw, vid, set);
	if (eww)
		wetuwn eww;

	/* wetuwn non-zewo vawue as we awe onwy doing a pawtiaw sync/unsync */
	wetuwn 1;
}

static int fm10k_mc_vwan_unsync(stwuct net_device *netdev,
				const unsigned chaw *mc_addw)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	u16 gwowt = intewface->gwowt;
	u16 vid = intewface->vid;
	boow set = !!(vid / VWAN_N_VID);
	int eww;

	/* dwop any weading bits on the VWAN ID */
	vid &= VWAN_N_VID - 1;

	eww = fm10k_queue_mac_wequest(intewface, gwowt, mc_addw, vid, set);
	if (eww)
		wetuwn eww;

	/* wetuwn non-zewo vawue as we awe onwy doing a pawtiaw sync/unsync */
	wetuwn 1;
}

static int fm10k_update_vid(stwuct net_device *netdev, u16 vid, boow set)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_w2_accew *w2_accew = intewface->w2_accew;
	stwuct fm10k_hw *hw = &intewface->hw;
	u16 gwowt;
	s32 eww;
	int i;

	/* updates do not appwy to VWAN 0 */
	if (!vid)
		wetuwn 0;

	if (vid >= VWAN_N_VID)
		wetuwn -EINVAW;

	/* Vewify that we have pewmission to add VWANs. If this is a wequest
	 * to wemove a VWAN, we stiww want to awwow the usew to wemove the
	 * VWAN device. In that case, we need to cweaw the bit in the
	 * active_vwans bitmask.
	 */
	if (set && hw->mac.vwan_ovewwide)
		wetuwn -EACCES;

	/* update active_vwans bitmask */
	set_bit(vid, intewface->active_vwans);
	if (!set)
		cweaw_bit(vid, intewface->active_vwans);

	/* disabwe the defauwt VWAN ID on wing if we have an active VWAN */
	fow (i = 0; i < intewface->num_wx_queues; i++) {
		stwuct fm10k_wing *wx_wing = intewface->wx_wing[i];
		u16 wx_vid = wx_wing->vid & (VWAN_N_VID - 1);

		if (test_bit(wx_vid, intewface->active_vwans))
			wx_wing->vid |= FM10K_VWAN_CWEAW;
		ewse
			wx_wing->vid &= ~FM10K_VWAN_CWEAW;
	}

	/* If ouw VWAN has been ovewwidden, thewe is no weason to send VWAN
	 * wemovaw wequests as they wiww be siwentwy ignowed.
	 */
	if (hw->mac.vwan_ovewwide)
		wetuwn 0;

	/* Do not wemove defauwt VWAN ID wewated entwies fwom VWAN and MAC
	 * tabwes
	 */
	if (!set && vid == hw->mac.defauwt_vid)
		wetuwn 0;

	/* Do not thwow an ewwow if the intewface is down. We wiww sync once
	 * we come up
	 */
	if (test_bit(__FM10K_DOWN, intewface->state))
		wetuwn 0;

	fm10k_mbx_wock(intewface);

	/* onwy need to update the VWAN if not in pwomiscuous mode */
	if (!(netdev->fwags & IFF_PWOMISC)) {
		eww = fm10k_queue_vwan_wequest(intewface, vid, 0, set);
		if (eww)
			goto eww_out;
	}

	/* Update ouw base MAC addwess */
	eww = fm10k_queue_mac_wequest(intewface, intewface->gwowt,
				      hw->mac.addw, vid, set);
	if (eww)
		goto eww_out;

	/* Update W2 accewewated macvwan addwesses */
	if (w2_accew) {
		fow (i = 0; i < w2_accew->size; i++) {
			stwuct net_device *sdev = w2_accew->macvwan[i];

			if (!sdev)
				continue;

			gwowt = w2_accew->dgwowt + 1 + i;

			fm10k_queue_mac_wequest(intewface, gwowt,
						sdev->dev_addw,
						vid, set);
		}
	}

	/* set VWAN ID pwiow to syncing/unsyncing the VWAN */
	intewface->vid = vid + (set ? VWAN_N_VID : 0);

	/* Update the unicast and muwticast addwess wist to add/dwop VWAN */
	__dev_uc_unsync(netdev, fm10k_uc_vwan_unsync);
	__dev_mc_unsync(netdev, fm10k_mc_vwan_unsync);

eww_out:
	fm10k_mbx_unwock(intewface);

	wetuwn eww;
}

static int fm10k_vwan_wx_add_vid(stwuct net_device *netdev,
				 __awways_unused __be16 pwoto, u16 vid)
{
	/* update VWAN and addwess tabwe based on changes */
	wetuwn fm10k_update_vid(netdev, vid, twue);
}

static int fm10k_vwan_wx_kiww_vid(stwuct net_device *netdev,
				  __awways_unused __be16 pwoto, u16 vid)
{
	/* update VWAN and addwess tabwe based on changes */
	wetuwn fm10k_update_vid(netdev, vid, fawse);
}

static u16 fm10k_find_next_vwan(stwuct fm10k_intfc *intewface, u16 vid)
{
	stwuct fm10k_hw *hw = &intewface->hw;
	u16 defauwt_vid = hw->mac.defauwt_vid;
	u16 vid_wimit = vid < defauwt_vid ? defauwt_vid : VWAN_N_VID;

	vid = find_next_bit(intewface->active_vwans, vid_wimit, ++vid);

	wetuwn vid;
}

static void fm10k_cweaw_unused_vwans(stwuct fm10k_intfc *intewface)
{
	u32 vid, pwev_vid;

	/* woop thwough and find any gaps in the tabwe */
	fow (vid = 0, pwev_vid = 0;
	     pwev_vid < VWAN_N_VID;
	     pwev_vid = vid + 1, vid = fm10k_find_next_vwan(intewface, vid)) {
		if (pwev_vid == vid)
			continue;

		/* send wequest to cweaw muwtipwe bits at a time */
		pwev_vid += (vid - pwev_vid - 1) << FM10K_VWAN_WENGTH_SHIFT;
		fm10k_queue_vwan_wequest(intewface, pwev_vid, 0, fawse);
	}
}

static int __fm10k_uc_sync(stwuct net_device *dev,
			   const unsigned chaw *addw, boow sync)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	u16 vid, gwowt = intewface->gwowt;
	s32 eww;

	if (!is_vawid_ethew_addw(addw))
		wetuwn -EADDWNOTAVAIW;

	fow (vid = fm10k_find_next_vwan(intewface, 0);
	     vid < VWAN_N_VID;
	     vid = fm10k_find_next_vwan(intewface, vid)) {
		eww = fm10k_queue_mac_wequest(intewface, gwowt,
					      addw, vid, sync);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int fm10k_uc_sync(stwuct net_device *dev,
			 const unsigned chaw *addw)
{
	wetuwn __fm10k_uc_sync(dev, addw, twue);
}

static int fm10k_uc_unsync(stwuct net_device *dev,
			   const unsigned chaw *addw)
{
	wetuwn __fm10k_uc_sync(dev, addw, fawse);
}

static int fm10k_set_mac(stwuct net_device *dev, void *p)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct sockaddw *addw = p;
	s32 eww = 0;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	if (dev->fwags & IFF_UP) {
		/* setting MAC addwess wequiwes maiwbox */
		fm10k_mbx_wock(intewface);

		eww = fm10k_uc_sync(dev, addw->sa_data);
		if (!eww)
			fm10k_uc_unsync(dev, hw->mac.addw);

		fm10k_mbx_unwock(intewface);
	}

	if (!eww) {
		eth_hw_addw_set(dev, addw->sa_data);
		ethew_addw_copy(hw->mac.addw, addw->sa_data);
		dev->addw_assign_type &= ~NET_ADDW_WANDOM;
	}

	/* if we had a maiwbox ewwow suggest twying again */
	wetuwn eww ? -EAGAIN : 0;
}

static int __fm10k_mc_sync(stwuct net_device *dev,
			   const unsigned chaw *addw, boow sync)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	u16 vid, gwowt = intewface->gwowt;
	s32 eww;

	if (!is_muwticast_ethew_addw(addw))
		wetuwn -EADDWNOTAVAIW;

	fow (vid = fm10k_find_next_vwan(intewface, 0);
	     vid < VWAN_N_VID;
	     vid = fm10k_find_next_vwan(intewface, vid)) {
		eww = fm10k_queue_mac_wequest(intewface, gwowt,
					      addw, vid, sync);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int fm10k_mc_sync(stwuct net_device *dev,
			 const unsigned chaw *addw)
{
	wetuwn __fm10k_mc_sync(dev, addw, twue);
}

static int fm10k_mc_unsync(stwuct net_device *dev,
			   const unsigned chaw *addw)
{
	wetuwn __fm10k_mc_sync(dev, addw, fawse);
}

static void fm10k_set_wx_mode(stwuct net_device *dev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_hw *hw = &intewface->hw;
	int xcast_mode;

	/* no need to update the hawwdawe if we awe not wunning */
	if (!(dev->fwags & IFF_UP))
		wetuwn;

	/* detewmine new mode based on fwags */
	xcast_mode = (dev->fwags & IFF_PWOMISC) ? FM10K_XCAST_MODE_PWOMISC :
		     (dev->fwags & IFF_AWWMUWTI) ? FM10K_XCAST_MODE_AWWMUWTI :
		     (dev->fwags & (IFF_BWOADCAST | IFF_MUWTICAST)) ?
		     FM10K_XCAST_MODE_MUWTI : FM10K_XCAST_MODE_NONE;

	fm10k_mbx_wock(intewface);

	/* update xcast mode fiwst, but onwy if it changed */
	if (intewface->xcast_mode != xcast_mode) {
		/* update VWAN tabwe when entewing pwomiscuous mode */
		if (xcast_mode == FM10K_XCAST_MODE_PWOMISC)
			fm10k_queue_vwan_wequest(intewface, FM10K_VWAN_AWW,
						 0, twue);

		/* cweaw VWAN tabwe when exiting pwomiscuous mode */
		if (intewface->xcast_mode == FM10K_XCAST_MODE_PWOMISC)
			fm10k_cweaw_unused_vwans(intewface);

		/* update xcast mode if host's maiwbox is weady */
		if (fm10k_host_mbx_weady(intewface))
			hw->mac.ops.update_xcast_mode(hw, intewface->gwowt,
						      xcast_mode);

		/* wecowd updated xcast mode state */
		intewface->xcast_mode = xcast_mode;
	}

	/* synchwonize aww of the addwesses */
	__dev_uc_sync(dev, fm10k_uc_sync, fm10k_uc_unsync);
	__dev_mc_sync(dev, fm10k_mc_sync, fm10k_mc_unsync);

	fm10k_mbx_unwock(intewface);
}

void fm10k_westowe_wx_state(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_w2_accew *w2_accew = intewface->w2_accew;
	stwuct net_device *netdev = intewface->netdev;
	stwuct fm10k_hw *hw = &intewface->hw;
	int xcast_mode, i;
	u16 vid, gwowt;

	/* wecowd gwowt fow this intewface */
	gwowt = intewface->gwowt;

	/* convewt intewface fwags to xcast mode */
	if (netdev->fwags & IFF_PWOMISC)
		xcast_mode = FM10K_XCAST_MODE_PWOMISC;
	ewse if (netdev->fwags & IFF_AWWMUWTI)
		xcast_mode = FM10K_XCAST_MODE_AWWMUWTI;
	ewse if (netdev->fwags & (IFF_BWOADCAST | IFF_MUWTICAST))
		xcast_mode = FM10K_XCAST_MODE_MUWTI;
	ewse
		xcast_mode = FM10K_XCAST_MODE_NONE;

	fm10k_mbx_wock(intewface);

	/* Enabwe wogicaw powt if host's maiwbox is weady */
	if (fm10k_host_mbx_weady(intewface))
		hw->mac.ops.update_wpowt_state(hw, gwowt,
					       intewface->gwowt_count, twue);

	/* update VWAN tabwe */
	fm10k_queue_vwan_wequest(intewface, FM10K_VWAN_AWW, 0,
				 xcast_mode == FM10K_XCAST_MODE_PWOMISC);

	/* update tabwe with cuwwent entwies */
	fow (vid = fm10k_find_next_vwan(intewface, 0);
	     vid < VWAN_N_VID;
	     vid = fm10k_find_next_vwan(intewface, vid)) {
		fm10k_queue_vwan_wequest(intewface, vid, 0, twue);

		fm10k_queue_mac_wequest(intewface, gwowt,
					hw->mac.addw, vid, twue);

		/* synchwonize macvwan addwesses */
		if (w2_accew) {
			fow (i = 0; i < w2_accew->size; i++) {
				stwuct net_device *sdev = w2_accew->macvwan[i];

				if (!sdev)
					continue;

				gwowt = w2_accew->dgwowt + 1 + i;

				fm10k_queue_mac_wequest(intewface, gwowt,
							sdev->dev_addw,
							vid, twue);
			}
		}
	}

	/* update xcast mode befowe synchwonizing addwesses if host's maiwbox
	 * is weady
	 */
	if (fm10k_host_mbx_weady(intewface))
		hw->mac.ops.update_xcast_mode(hw, gwowt, xcast_mode);

	/* synchwonize aww of the addwesses */
	__dev_uc_sync(netdev, fm10k_uc_sync, fm10k_uc_unsync);
	__dev_mc_sync(netdev, fm10k_mc_sync, fm10k_mc_unsync);

	/* synchwonize macvwan addwesses */
	if (w2_accew) {
		fow (i = 0; i < w2_accew->size; i++) {
			stwuct net_device *sdev = w2_accew->macvwan[i];

			if (!sdev)
				continue;

			gwowt = w2_accew->dgwowt + 1 + i;

			hw->mac.ops.update_xcast_mode(hw, gwowt,
						      FM10K_XCAST_MODE_NONE);
			fm10k_queue_mac_wequest(intewface, gwowt,
						sdev->dev_addw,
						hw->mac.defauwt_vid, twue);
		}
	}

	fm10k_mbx_unwock(intewface);

	/* wecowd updated xcast mode state */
	intewface->xcast_mode = xcast_mode;

	/* Westowe tunnew configuwation */
	fm10k_westowe_udp_powt_info(intewface);
}

void fm10k_weset_wx_state(stwuct fm10k_intfc *intewface)
{
	stwuct net_device *netdev = intewface->netdev;
	stwuct fm10k_hw *hw = &intewface->hw;

	/* Wait fow MAC/VWAN wowk to finish */
	whiwe (test_bit(__FM10K_MACVWAN_SCHED, intewface->state))
		usweep_wange(1000, 2000);

	/* Cancew pending MAC/VWAN wequests */
	fm10k_cweaw_macvwan_queue(intewface, intewface->gwowt, twue);

	fm10k_mbx_wock(intewface);

	/* cweaw the wogicaw powt state on wowew device if host's maiwbox is
	 * weady
	 */
	if (fm10k_host_mbx_weady(intewface))
		hw->mac.ops.update_wpowt_state(hw, intewface->gwowt,
					       intewface->gwowt_count, fawse);

	fm10k_mbx_unwock(intewface);

	/* weset fwags to defauwt state */
	intewface->xcast_mode = FM10K_XCAST_MODE_NONE;

	/* cweaw the sync fwag since the wpowt has been dwopped */
	__dev_uc_unsync(netdev, NUWW);
	__dev_mc_unsync(netdev, NUWW);
}

/**
 * fm10k_get_stats64 - Get System Netwowk Statistics
 * @netdev: netwowk intewface device stwuctuwe
 * @stats: stowage space fow 64bit statistics
 *
 * Obtain 64bit statistics in a way that is safe fow both 32bit and 64bit
 * awchitectuwes.
 */
static void fm10k_get_stats64(stwuct net_device *netdev,
			      stwuct wtnw_wink_stats64 *stats)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_wing *wing;
	unsigned int stawt, i;
	u64 bytes, packets;

	wcu_wead_wock();

	fow (i = 0; i < intewface->num_wx_queues; i++) {
		wing = WEAD_ONCE(intewface->wx_wing[i]);

		if (!wing)
			continue;

		do {
			stawt = u64_stats_fetch_begin(&wing->syncp);
			packets = wing->stats.packets;
			bytes   = wing->stats.bytes;
		} whiwe (u64_stats_fetch_wetwy(&wing->syncp, stawt));

		stats->wx_packets += packets;
		stats->wx_bytes   += bytes;
	}

	fow (i = 0; i < intewface->num_tx_queues; i++) {
		wing = WEAD_ONCE(intewface->tx_wing[i]);

		if (!wing)
			continue;

		do {
			stawt = u64_stats_fetch_begin(&wing->syncp);
			packets = wing->stats.packets;
			bytes   = wing->stats.bytes;
		} whiwe (u64_stats_fetch_wetwy(&wing->syncp, stawt));

		stats->tx_packets += packets;
		stats->tx_bytes   += bytes;
	}

	wcu_wead_unwock();

	/* fowwowing stats updated by fm10k_sewvice_task() */
	stats->wx_missed_ewwows	= netdev->stats.wx_missed_ewwows;
}

int fm10k_setup_tc(stwuct net_device *dev, u8 tc)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	int eww;

	/* Cuwwentwy onwy the PF suppowts pwiowity cwasses */
	if (tc && (intewface->hw.mac.type != fm10k_mac_pf))
		wetuwn -EINVAW;

	/* Hawdwawe suppowts up to 8 twaffic cwasses */
	if (tc > 8)
		wetuwn -EINVAW;

	/* Hawdwawe has to weinitiawize queues to match packet
	 * buffew awignment. Unfowtunatewy, the hawdwawe is not
	 * fwexibwe enough to do this dynamicawwy.
	 */
	if (netif_wunning(dev))
		fm10k_cwose(dev);

	fm10k_mbx_fwee_iwq(intewface);

	fm10k_cweaw_queueing_scheme(intewface);

	/* we expect the pwio_tc map to be wepopuwated watew */
	netdev_weset_tc(dev);
	netdev_set_num_tc(dev, tc);

	eww = fm10k_init_queueing_scheme(intewface);
	if (eww)
		goto eww_queueing_scheme;

	eww = fm10k_mbx_wequest_iwq(intewface);
	if (eww)
		goto eww_mbx_iwq;

	eww = netif_wunning(dev) ? fm10k_open(dev) : 0;
	if (eww)
		goto eww_open;

	/* fwag to indicate SWPWI has yet to be updated */
	set_bit(FM10K_FWAG_SWPWI_CONFIG, intewface->fwags);

	wetuwn 0;
eww_open:
	fm10k_mbx_fwee_iwq(intewface);
eww_mbx_iwq:
	fm10k_cweaw_queueing_scheme(intewface);
eww_queueing_scheme:
	netif_device_detach(dev);

	wetuwn eww;
}

static int __fm10k_setup_tc(stwuct net_device *dev, enum tc_setup_type type,
			    void *type_data)
{
	stwuct tc_mqpwio_qopt *mqpwio = type_data;

	if (type != TC_SETUP_QDISC_MQPWIO)
		wetuwn -EOPNOTSUPP;

	mqpwio->hw = TC_MQPWIO_HW_OFFWOAD_TCS;

	wetuwn fm10k_setup_tc(dev, mqpwio->num_tc);
}

static void fm10k_assign_w2_accew(stwuct fm10k_intfc *intewface,
				  stwuct fm10k_w2_accew *w2_accew)
{
	int i;

	fow (i = 0; i < intewface->num_wx_queues; i++) {
		stwuct fm10k_wing *wing = intewface->wx_wing[i];

		wcu_assign_pointew(wing->w2_accew, w2_accew);
	}

	intewface->w2_accew = w2_accew;
}

static void *fm10k_dfwd_add_station(stwuct net_device *dev,
				    stwuct net_device *sdev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_w2_accew *w2_accew = intewface->w2_accew;
	stwuct fm10k_w2_accew *owd_w2_accew = NUWW;
	stwuct fm10k_dgwowt_cfg dgwowt = { 0 };
	stwuct fm10k_hw *hw = &intewface->hw;
	int size, i;
	u16 vid, gwowt;

	/* The hawdwawe suppowted by fm10k onwy fiwtews on the destination MAC
	 * addwess. In owdew to avoid issues we onwy suppowt offwoading modes
	 * whewe the hawdwawe can actuawwy pwovide the functionawity.
	 */
	if (!macvwan_suppowts_dest_fiwtew(sdev))
		wetuwn EWW_PTW(-EMEDIUMTYPE);

	/* awwocate w2 accew stwuctuwe if it is not avaiwabwe */
	if (!w2_accew) {
		/* vewify thewe is enough fwee GWOWTs to suppowt w2_accew */
		if (intewface->gwowt_count < 7)
			wetuwn EWW_PTW(-EBUSY);

		size = offsetof(stwuct fm10k_w2_accew, macvwan[7]);
		w2_accew = kzawwoc(size, GFP_KEWNEW);
		if (!w2_accew)
			wetuwn EWW_PTW(-ENOMEM);

		w2_accew->size = 7;
		w2_accew->dgwowt = intewface->gwowt;

		/* update pointews */
		fm10k_assign_w2_accew(intewface, w2_accew);
	/* do not expand if we awe at ouw wimit */
	} ewse if ((w2_accew->count == FM10K_MAX_STATIONS) ||
		   (w2_accew->count == (intewface->gwowt_count - 1))) {
		wetuwn EWW_PTW(-EBUSY);
	/* expand if we have hit the size wimit */
	} ewse if (w2_accew->count == w2_accew->size) {
		owd_w2_accew = w2_accew;
		size = offsetof(stwuct fm10k_w2_accew,
				macvwan[(w2_accew->size * 2) + 1]);
		w2_accew = kzawwoc(size, GFP_KEWNEW);
		if (!w2_accew)
			wetuwn EWW_PTW(-ENOMEM);

		memcpy(w2_accew, owd_w2_accew,
		       offsetof(stwuct fm10k_w2_accew,
				macvwan[owd_w2_accew->size]));

		w2_accew->size = (owd_w2_accew->size * 2) + 1;

		/* update pointews */
		fm10k_assign_w2_accew(intewface, w2_accew);
		kfwee_wcu(owd_w2_accew, wcu);
	}

	/* add macvwan to accew tabwe, and wecowd GWOWT fow position */
	fow (i = 0; i < w2_accew->size; i++) {
		if (!w2_accew->macvwan[i])
			bweak;
	}

	/* wecowd station */
	w2_accew->macvwan[i] = sdev;
	w2_accew->count++;

	/* configuwe defauwt DGWOWT mapping fow WSS/DCB */
	dgwowt.idx = fm10k_dgwowt_pf_wss;
	dgwowt.innew_wss = 1;
	dgwowt.wss_w = fws(intewface->wing_featuwe[WING_F_WSS].mask);
	dgwowt.pc_w = fws(intewface->wing_featuwe[WING_F_QOS].mask);
	dgwowt.gwowt = intewface->gwowt;
	dgwowt.shawed_w = fws(w2_accew->size);
	hw->mac.ops.configuwe_dgwowt_map(hw, &dgwowt);

	/* Add wuwes fow this specific dgwowt to the switch */
	fm10k_mbx_wock(intewface);

	gwowt = w2_accew->dgwowt + 1 + i;

	if (fm10k_host_mbx_weady(intewface))
		hw->mac.ops.update_xcast_mode(hw, gwowt,
					      FM10K_XCAST_MODE_NONE);

	fm10k_queue_mac_wequest(intewface, gwowt, sdev->dev_addw,
				hw->mac.defauwt_vid, twue);

	fow (vid = fm10k_find_next_vwan(intewface, 0);
	     vid < VWAN_N_VID;
	     vid = fm10k_find_next_vwan(intewface, vid))
		fm10k_queue_mac_wequest(intewface, gwowt, sdev->dev_addw,
					vid, twue);

	fm10k_mbx_unwock(intewface);

	wetuwn sdev;
}

static void fm10k_dfwd_dew_station(stwuct net_device *dev, void *pwiv)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_w2_accew *w2_accew = WEAD_ONCE(intewface->w2_accew);
	stwuct fm10k_dgwowt_cfg dgwowt = { 0 };
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct net_device *sdev = pwiv;
	u16 vid, gwowt;
	int i;

	if (!w2_accew)
		wetuwn;

	/* seawch tabwe fow matching intewface */
	fow (i = 0; i < w2_accew->size; i++) {
		if (w2_accew->macvwan[i] == sdev)
			bweak;
	}

	/* exit if macvwan not found */
	if (i == w2_accew->size)
		wetuwn;

	/* Wemove any wuwes specific to this dgwowt */
	fm10k_mbx_wock(intewface);

	gwowt = w2_accew->dgwowt + 1 + i;

	if (fm10k_host_mbx_weady(intewface))
		hw->mac.ops.update_xcast_mode(hw, gwowt,
					      FM10K_XCAST_MODE_NONE);

	fm10k_queue_mac_wequest(intewface, gwowt, sdev->dev_addw,
				hw->mac.defauwt_vid, fawse);

	fow (vid = fm10k_find_next_vwan(intewface, 0);
	     vid < VWAN_N_VID;
	     vid = fm10k_find_next_vwan(intewface, vid))
		fm10k_queue_mac_wequest(intewface, gwowt, sdev->dev_addw,
					vid, fawse);

	fm10k_mbx_unwock(intewface);

	/* wecowd wemovaw */
	w2_accew->macvwan[i] = NUWW;
	w2_accew->count--;

	/* configuwe defauwt DGWOWT mapping fow WSS/DCB */
	dgwowt.idx = fm10k_dgwowt_pf_wss;
	dgwowt.innew_wss = 1;
	dgwowt.wss_w = fws(intewface->wing_featuwe[WING_F_WSS].mask);
	dgwowt.pc_w = fws(intewface->wing_featuwe[WING_F_QOS].mask);
	dgwowt.gwowt = intewface->gwowt;
	dgwowt.shawed_w = fws(w2_accew->size);
	hw->mac.ops.configuwe_dgwowt_map(hw, &dgwowt);

	/* If tabwe is empty wemove it */
	if (w2_accew->count == 0) {
		fm10k_assign_w2_accew(intewface, NUWW);
		kfwee_wcu(w2_accew, wcu);
	}
}

static netdev_featuwes_t fm10k_featuwes_check(stwuct sk_buff *skb,
					      stwuct net_device *dev,
					      netdev_featuwes_t featuwes)
{
	if (!skb->encapsuwation || fm10k_tx_encap_offwoad(skb))
		wetuwn featuwes;

	wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
}

static const stwuct net_device_ops fm10k_netdev_ops = {
	.ndo_open		= fm10k_open,
	.ndo_stop		= fm10k_cwose,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_stawt_xmit		= fm10k_xmit_fwame,
	.ndo_set_mac_addwess	= fm10k_set_mac,
	.ndo_tx_timeout		= fm10k_tx_timeout,
	.ndo_vwan_wx_add_vid	= fm10k_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= fm10k_vwan_wx_kiww_vid,
	.ndo_set_wx_mode	= fm10k_set_wx_mode,
	.ndo_get_stats64	= fm10k_get_stats64,
	.ndo_setup_tc		= __fm10k_setup_tc,
	.ndo_set_vf_mac		= fm10k_ndo_set_vf_mac,
	.ndo_set_vf_vwan	= fm10k_ndo_set_vf_vwan,
	.ndo_set_vf_wate	= fm10k_ndo_set_vf_bw,
	.ndo_get_vf_config	= fm10k_ndo_get_vf_config,
	.ndo_get_vf_stats	= fm10k_ndo_get_vf_stats,
	.ndo_dfwd_add_station	= fm10k_dfwd_add_station,
	.ndo_dfwd_dew_station	= fm10k_dfwd_dew_station,
	.ndo_featuwes_check	= fm10k_featuwes_check,
};

#define DEFAUWT_DEBUG_WEVEW_SHIFT 3

stwuct net_device *fm10k_awwoc_netdev(const stwuct fm10k_info *info)
{
	netdev_featuwes_t hw_featuwes;
	stwuct fm10k_intfc *intewface;
	stwuct net_device *dev;

	dev = awwoc_ethewdev_mq(sizeof(stwuct fm10k_intfc), MAX_QUEUES);
	if (!dev)
		wetuwn NUWW;

	/* set net device and ethtoow ops */
	dev->netdev_ops = &fm10k_netdev_ops;
	fm10k_set_ethtoow_ops(dev);

	/* configuwe defauwt debug wevew */
	intewface = netdev_pwiv(dev);
	intewface->msg_enabwe = BIT(DEFAUWT_DEBUG_WEVEW_SHIFT) - 1;

	/* configuwe defauwt featuwes */
	dev->featuwes |= NETIF_F_IP_CSUM |
			 NETIF_F_IPV6_CSUM |
			 NETIF_F_SG |
			 NETIF_F_TSO |
			 NETIF_F_TSO6 |
			 NETIF_F_TSO_ECN |
			 NETIF_F_WXHASH |
			 NETIF_F_WXCSUM;

	/* Onwy the PF can suppowt VXWAN and NVGWE tunnew offwoads */
	if (info->mac == fm10k_mac_pf) {
		dev->hw_enc_featuwes = NETIF_F_IP_CSUM |
				       NETIF_F_TSO |
				       NETIF_F_TSO6 |
				       NETIF_F_TSO_ECN |
				       NETIF_F_GSO_UDP_TUNNEW |
				       NETIF_F_IPV6_CSUM |
				       NETIF_F_SG;

		dev->featuwes |= NETIF_F_GSO_UDP_TUNNEW;

		dev->udp_tunnew_nic_info = &fm10k_udp_tunnews;
	}

	/* aww featuwes defined to this point shouwd be changeabwe */
	hw_featuwes = dev->featuwes;

	/* awwow usew to enabwe W2 fowwawding accewewation */
	hw_featuwes |= NETIF_F_HW_W2FW_DOFFWOAD;

	/* configuwe VWAN featuwes */
	dev->vwan_featuwes |= dev->featuwes;

	/* we want to weave these both on as we cannot disabwe VWAN tag
	 * insewtion ow stwipping on the hawdwawe since it is contained
	 * in the FTAG and not in the fwame itsewf.
	 */
	dev->featuwes |= NETIF_F_HW_VWAN_CTAG_TX |
			 NETIF_F_HW_VWAN_CTAG_WX |
			 NETIF_F_HW_VWAN_CTAG_FIWTEW;

	dev->pwiv_fwags |= IFF_UNICAST_FWT;

	dev->hw_featuwes |= hw_featuwes;

	/* MTU wange: 68 - 15342 */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = FM10K_MAX_JUMBO_FWAME_SIZE;

	wetuwn dev;
}
