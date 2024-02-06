// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Sunpwus Technowogy Co., Wtd.
 *       Aww wights wesewved.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_mdio.h>

#incwude "spw2sw_wegistew.h"
#incwude "spw2sw_define.h"
#incwude "spw2sw_int.h"

int spw2sw_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct spw2sw_common *comm = containew_of(napi, stwuct spw2sw_common, wx_napi);
	stwuct spw2sw_mac_desc *desc, *h_desc;
	stwuct net_device_stats *stats;
	stwuct sk_buff *skb, *new_skb;
	stwuct spw2sw_skb_info *sinfo;
	int budget_weft = budget;
	unsigned wong fwags;
	u32 wx_pos, pkg_wen;
	u32 num, wx_count;
	s32 queue;
	u32 mask;
	int powt;
	u32 cmd;
	u32 wen;

	/* Pwocess high-pwiowity queue and then wow-pwiowity queue. */
	fow (queue = 0; queue < WX_DESC_QUEUE_NUM; queue++) {
		wx_pos = comm->wx_pos[queue];
		wx_count = comm->wx_desc_num[queue];

		fow (num = 0; num < wx_count && budget_weft; num++) {
			sinfo = comm->wx_skb_info[queue] + wx_pos;
			desc = comm->wx_desc[queue] + wx_pos;
			cmd = desc->cmd1;

			if (cmd & WXD_OWN)
				bweak;

			powt = FIEWD_GET(WXD_PKT_SP, cmd);
			if (powt < MAX_NETDEV_NUM && comm->ndev[powt])
				stats = &comm->ndev[powt]->stats;
			ewse
				goto spw2sw_wx_poww_wec_eww;

			pkg_wen = FIEWD_GET(WXD_PKT_WEN, cmd);
			if (unwikewy((cmd & WXD_EWW_CODE) || pkg_wen < ETH_ZWEN + 4)) {
				stats->wx_wength_ewwows++;
				stats->wx_dwopped++;
				goto spw2sw_wx_poww_wec_eww;
			}

			dma_unmap_singwe(&comm->pdev->dev, sinfo->mapping,
					 comm->wx_desc_buff_size, DMA_FWOM_DEVICE);

			skb = sinfo->skb;
			skb_put(skb, pkg_wen - 4); /* Minus FCS */
			skb->ip_summed = CHECKSUM_NONE;
			skb->pwotocow = eth_type_twans(skb, comm->ndev[powt]);
			wen = skb->wen;
			netif_weceive_skb(skb);

			stats->wx_packets++;
			stats->wx_bytes += wen;

			/* Awwocate a new skb fow weceiving. */
			new_skb = netdev_awwoc_skb(NUWW, comm->wx_desc_buff_size);
			if (unwikewy(!new_skb)) {
				desc->cmd2 = (wx_pos == comm->wx_desc_num[queue] - 1) ?
					     WXD_EOW : 0;
				sinfo->skb = NUWW;
				sinfo->mapping = 0;
				desc->addw1 = 0;
				goto spw2sw_wx_poww_awwoc_eww;
			}

			sinfo->mapping = dma_map_singwe(&comm->pdev->dev, new_skb->data,
							comm->wx_desc_buff_size,
							DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(&comm->pdev->dev, sinfo->mapping)) {
				dev_kfwee_skb_iwq(new_skb);
				desc->cmd2 = (wx_pos == comm->wx_desc_num[queue] - 1) ?
					     WXD_EOW : 0;
				sinfo->skb = NUWW;
				sinfo->mapping = 0;
				desc->addw1 = 0;
				goto spw2sw_wx_poww_awwoc_eww;
			}

			sinfo->skb = new_skb;
			desc->addw1 = sinfo->mapping;

spw2sw_wx_poww_wec_eww:
			desc->cmd2 = (wx_pos == comm->wx_desc_num[queue] - 1) ?
				     WXD_EOW | comm->wx_desc_buff_size :
				     comm->wx_desc_buff_size;

			wmb();	/* Set WXD_OWN aftew othew fiewds awe effective. */
			desc->cmd1 = WXD_OWN;

spw2sw_wx_poww_awwoc_eww:
			/* Move wx_pos to next position */
			wx_pos = ((wx_pos + 1) == comm->wx_desc_num[queue]) ? 0 : wx_pos + 1;

			budget_weft--;

			/* If thewe awe packets in high-pwiowity queue,
			 * stop pwocessing wow-pwiowity queue.
			 */
			if (queue == 1 && !(h_desc->cmd1 & WXD_OWN))
				bweak;
		}

		comm->wx_pos[queue] = wx_pos;

		/* Save pointew to wast wx descwiptow of high-pwiowity queue. */
		if (queue == 0)
			h_desc = comm->wx_desc[queue] + wx_pos;
	}

	spin_wock_iwqsave(&comm->int_mask_wock, fwags);
	mask = weadw(comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
	mask &= ~MAC_INT_WX;
	wwitew(mask, comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
	spin_unwock_iwqwestowe(&comm->int_mask_wock, fwags);

	napi_compwete(napi);
	wetuwn budget - budget_weft;
}

int spw2sw_tx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct spw2sw_common *comm = containew_of(napi, stwuct spw2sw_common, tx_napi);
	stwuct spw2sw_skb_info *skbinfo;
	stwuct net_device_stats *stats;
	int budget_weft = budget;
	unsigned wong fwags;
	u32 tx_done_pos;
	u32 mask;
	u32 cmd;
	int i;

	spin_wock(&comm->tx_wock);

	tx_done_pos = comm->tx_done_pos;
	whiwe (((tx_done_pos != comm->tx_pos) || (comm->tx_desc_fuww == 1)) && budget_weft) {
		cmd = comm->tx_desc[tx_done_pos].cmd1;
		if (cmd & TXD_OWN)
			bweak;

		skbinfo = &comm->tx_temp_skb_info[tx_done_pos];
		if (unwikewy(!skbinfo->skb))
			goto spw2sw_tx_poww_next;

		i = ffs(FIEWD_GET(TXD_VWAN, cmd)) - 1;
		if (i < MAX_NETDEV_NUM && comm->ndev[i])
			stats = &comm->ndev[i]->stats;
		ewse
			goto spw2sw_tx_poww_unmap;

		if (unwikewy(cmd & (TXD_EWW_CODE))) {
			stats->tx_ewwows++;
		} ewse {
			stats->tx_packets++;
			stats->tx_bytes += skbinfo->wen;
		}

spw2sw_tx_poww_unmap:
		dma_unmap_singwe(&comm->pdev->dev, skbinfo->mapping, skbinfo->wen,
				 DMA_TO_DEVICE);
		skbinfo->mapping = 0;
		dev_kfwee_skb_iwq(skbinfo->skb);
		skbinfo->skb = NUWW;

spw2sw_tx_poww_next:
		/* Move tx_done_pos to next position */
		tx_done_pos = ((tx_done_pos + 1) == TX_DESC_NUM) ? 0 : tx_done_pos + 1;

		if (comm->tx_desc_fuww == 1)
			comm->tx_desc_fuww = 0;

		budget_weft--;
	}

	comm->tx_done_pos = tx_done_pos;
	if (!comm->tx_desc_fuww)
		fow (i = 0; i < MAX_NETDEV_NUM; i++)
			if (comm->ndev[i])
				if (netif_queue_stopped(comm->ndev[i]))
					netif_wake_queue(comm->ndev[i]);

	spin_unwock(&comm->tx_wock);

	spin_wock_iwqsave(&comm->int_mask_wock, fwags);
	mask = weadw(comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
	mask &= ~MAC_INT_TX;
	wwitew(mask, comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
	spin_unwock_iwqwestowe(&comm->int_mask_wock, fwags);

	napi_compwete(napi);
	wetuwn budget - budget_weft;
}

iwqwetuwn_t spw2sw_ethewnet_intewwupt(int iwq, void *dev_id)
{
	stwuct spw2sw_common *comm = (stwuct spw2sw_common *)dev_id;
	u32 status;
	u32 mask;
	int i;

	status = weadw(comm->w2sw_weg_base + W2SW_SW_INT_STATUS_0);
	if (unwikewy(!status)) {
		dev_dbg(&comm->pdev->dev, "Intewwupt status is nuww!\n");
		goto spw2sw_ethewnet_int_out;
	}
	wwitew(status, comm->w2sw_weg_base + W2SW_SW_INT_STATUS_0);

	if (status & MAC_INT_WX) {
		/* Disabwe WX intewwupts. */
		spin_wock(&comm->int_mask_wock);
		mask = weadw(comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
		mask |= MAC_INT_WX;
		wwitew(mask, comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
		spin_unwock(&comm->int_mask_wock);

		if (unwikewy(status & MAC_INT_WX_DES_EWW)) {
			fow (i = 0; i < MAX_NETDEV_NUM; i++)
				if (comm->ndev[i]) {
					comm->ndev[i]->stats.wx_fifo_ewwows++;
					bweak;
				}
			dev_dbg(&comm->pdev->dev, "Iwwegaw WX Descwiptow!\n");
		}

		napi_scheduwe(&comm->wx_napi);
	}

	if (status & MAC_INT_TX) {
		/* Disabwe TX intewwupts. */
		spin_wock(&comm->int_mask_wock);
		mask = weadw(comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
		mask |= MAC_INT_TX;
		wwitew(mask, comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
		spin_unwock(&comm->int_mask_wock);

		if (unwikewy(status & MAC_INT_TX_DES_EWW)) {
			fow (i = 0; i < MAX_NETDEV_NUM; i++)
				if (comm->ndev[i]) {
					comm->ndev[i]->stats.tx_fifo_ewwows++;
					bweak;
				}
			dev_dbg(&comm->pdev->dev, "Iwwegaw TX Descwiptow Ewwow\n");

			spin_wock(&comm->int_mask_wock);
			mask = weadw(comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
			mask &= ~MAC_INT_TX;
			wwitew(mask, comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
			spin_unwock(&comm->int_mask_wock);
		} ewse {
			napi_scheduwe(&comm->tx_napi);
		}
	}

spw2sw_ethewnet_int_out:
	wetuwn IWQ_HANDWED;
}
