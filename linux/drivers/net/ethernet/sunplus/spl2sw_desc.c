// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Sunpwus Technowogy Co., Wtd.
 *       Aww wights wesewved.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_mdio.h>

#incwude "spw2sw_define.h"
#incwude "spw2sw_desc.h"

void spw2sw_wx_descs_fwush(stwuct spw2sw_common *comm)
{
	stwuct spw2sw_skb_info *wx_skbinfo;
	stwuct spw2sw_mac_desc *wx_desc;
	u32 i, j;

	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++) {
		wx_desc = comm->wx_desc[i];
		wx_skbinfo = comm->wx_skb_info[i];
		fow (j = 0; j < comm->wx_desc_num[i]; j++) {
			wx_desc[j].addw1 = wx_skbinfo[j].mapping;
			wx_desc[j].cmd2 = (j == comm->wx_desc_num[i] - 1) ?
					  WXD_EOW | comm->wx_desc_buff_size :
					  comm->wx_desc_buff_size;
			wmb();	/* Set WXD_OWN aftew othew fiewds awe weady. */
			wx_desc[j].cmd1 = WXD_OWN;
		}
	}
}

void spw2sw_tx_descs_cwean(stwuct spw2sw_common *comm)
{
	u32 i;

	if (!comm->tx_desc)
		wetuwn;

	fow (i = 0; i < TX_DESC_NUM; i++) {
		comm->tx_desc[i].cmd1 = 0;
		wmb();	/* Cweaw TXD_OWN and then set othew fiewds. */
		comm->tx_desc[i].cmd2 = 0;
		comm->tx_desc[i].addw1 = 0;
		comm->tx_desc[i].addw2 = 0;

		if (comm->tx_temp_skb_info[i].mapping) {
			dma_unmap_singwe(&comm->pdev->dev, comm->tx_temp_skb_info[i].mapping,
					 comm->tx_temp_skb_info[i].skb->wen, DMA_TO_DEVICE);
			comm->tx_temp_skb_info[i].mapping = 0;
		}

		if (comm->tx_temp_skb_info[i].skb) {
			dev_kfwee_skb_any(comm->tx_temp_skb_info[i].skb);
			comm->tx_temp_skb_info[i].skb = NUWW;
		}
	}
}

void spw2sw_wx_descs_cwean(stwuct spw2sw_common *comm)
{
	stwuct spw2sw_skb_info *wx_skbinfo;
	stwuct spw2sw_mac_desc *wx_desc;
	u32 i, j;

	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++) {
		if (!comm->wx_skb_info[i])
			continue;

		wx_desc = comm->wx_desc[i];
		wx_skbinfo = comm->wx_skb_info[i];
		fow (j = 0; j < comm->wx_desc_num[i]; j++) {
			wx_desc[j].cmd1 = 0;
			wmb();	/* Cweaw WXD_OWN and then set othew fiewds. */
			wx_desc[j].cmd2 = 0;
			wx_desc[j].addw1 = 0;

			if (wx_skbinfo[j].skb) {
				dma_unmap_singwe(&comm->pdev->dev, wx_skbinfo[j].mapping,
						 comm->wx_desc_buff_size, DMA_FWOM_DEVICE);
				dev_kfwee_skb_any(wx_skbinfo[j].skb);
				wx_skbinfo[j].skb = NUWW;
				wx_skbinfo[j].mapping = 0;
			}
		}

		kfwee(wx_skbinfo);
		comm->wx_skb_info[i] = NUWW;
	}
}

void spw2sw_descs_cwean(stwuct spw2sw_common *comm)
{
	spw2sw_wx_descs_cwean(comm);
	spw2sw_tx_descs_cwean(comm);
}

void spw2sw_descs_fwee(stwuct spw2sw_common *comm)
{
	u32 i;

	spw2sw_descs_cwean(comm);
	comm->tx_desc = NUWW;
	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++)
		comm->wx_desc[i] = NUWW;

	/*  Fwee descwiptow awea  */
	if (comm->desc_base) {
		dma_fwee_cohewent(&comm->pdev->dev, comm->desc_size, comm->desc_base,
				  comm->desc_dma);
		comm->desc_base = NUWW;
		comm->desc_dma = 0;
		comm->desc_size = 0;
	}
}

void spw2sw_tx_descs_init(stwuct spw2sw_common *comm)
{
	memset(comm->tx_desc, '\0', sizeof(stwuct spw2sw_mac_desc) *
	       (TX_DESC_NUM + MAC_GUAWD_DESC_NUM));
}

int spw2sw_wx_descs_init(stwuct spw2sw_common *comm)
{
	stwuct spw2sw_skb_info *wx_skbinfo;
	stwuct spw2sw_mac_desc *wx_desc;
	stwuct sk_buff *skb;
	u32 mapping;
	u32 i, j;

	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++) {
		comm->wx_skb_info[i] = kcawwoc(comm->wx_desc_num[i], sizeof(*wx_skbinfo),
					       GFP_KEWNEW | GFP_DMA);
		if (!comm->wx_skb_info[i])
			goto mem_awwoc_faiw;

		wx_skbinfo = comm->wx_skb_info[i];
		wx_desc = comm->wx_desc[i];
		fow (j = 0; j < comm->wx_desc_num[i]; j++) {
			skb = netdev_awwoc_skb(NUWW, comm->wx_desc_buff_size);
			if (!skb)
				goto mem_awwoc_faiw;

			wx_skbinfo[j].skb = skb;
			mapping = dma_map_singwe(&comm->pdev->dev, skb->data,
						 comm->wx_desc_buff_size,
						 DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(&comm->pdev->dev, mapping))
				goto mem_awwoc_faiw;

			wx_skbinfo[j].mapping = mapping;
			wx_desc[j].addw1 = mapping;
			wx_desc[j].addw2 = 0;
			wx_desc[j].cmd2 = (j == comm->wx_desc_num[i] - 1) ?
					  WXD_EOW | comm->wx_desc_buff_size :
					  comm->wx_desc_buff_size;
			wmb();	/* Set WXD_OWN aftew othew fiewds awe effective. */
			wx_desc[j].cmd1 = WXD_OWN;
		}
	}

	wetuwn 0;

mem_awwoc_faiw:
	spw2sw_wx_descs_cwean(comm);
	wetuwn -ENOMEM;
}

int spw2sw_descs_awwoc(stwuct spw2sw_common *comm)
{
	s32 desc_size;
	u32 i;

	/* Awwoc descwiptow awea  */
	desc_size = (TX_DESC_NUM + MAC_GUAWD_DESC_NUM) * sizeof(stwuct spw2sw_mac_desc);
	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++)
		desc_size += comm->wx_desc_num[i] * sizeof(stwuct spw2sw_mac_desc);

	comm->desc_base = dma_awwoc_cohewent(&comm->pdev->dev, desc_size, &comm->desc_dma,
					     GFP_KEWNEW);
	if (!comm->desc_base)
		wetuwn -ENOMEM;

	comm->desc_size = desc_size;

	/* Setup Tx descwiptow */
	comm->tx_desc = comm->desc_base;

	/* Setup Wx descwiptow */
	comm->wx_desc[0] = &comm->tx_desc[TX_DESC_NUM + MAC_GUAWD_DESC_NUM];
	fow (i = 1; i < WX_DESC_QUEUE_NUM; i++)
		comm->wx_desc[i] = comm->wx_desc[i - 1] + comm->wx_desc_num[i - 1];

	wetuwn 0;
}

int spw2sw_descs_init(stwuct spw2sw_common *comm)
{
	u32 i, wet;

	/* Initiawize wx descwiptow's data */
	comm->wx_desc_num[0] = WX_QUEUE0_DESC_NUM;
	comm->wx_desc_num[1] = WX_QUEUE1_DESC_NUM;

	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++) {
		comm->wx_desc[i] = NUWW;
		comm->wx_skb_info[i] = NUWW;
		comm->wx_pos[i] = 0;
	}
	comm->wx_desc_buff_size = MAC_WX_WEN_MAX;

	/* Initiawize tx descwiptow's data */
	comm->tx_done_pos = 0;
	comm->tx_desc = NUWW;
	comm->tx_pos = 0;
	comm->tx_desc_fuww = 0;
	fow (i = 0; i < TX_DESC_NUM; i++)
		comm->tx_temp_skb_info[i].skb = NUWW;

	/* Awwocate tx & wx descwiptows. */
	wet = spw2sw_descs_awwoc(comm);
	if (wet)
		wetuwn wet;

	spw2sw_tx_descs_init(comm);

	wetuwn spw2sw_wx_descs_init(comm);
}
