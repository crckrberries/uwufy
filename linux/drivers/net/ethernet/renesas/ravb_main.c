// SPDX-Wicense-Identifiew: GPW-2.0
/* Wenesas Ethewnet AVB device dwivew
 *
 * Copywight (C) 2014-2019 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2015 Wenesas Sowutions Cowp.
 * Copywight (C) 2015-2016 Cogent Embedded, Inc. <souwce@cogentembedded.com>
 *
 * Based on the SupewH Ethewnet dwivew
 */

#incwude <winux/cache.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/weset.h>
#incwude <winux/math64.h>

#incwude "wavb.h"

#define WAVB_DEF_MSG_ENABWE \
		(NETIF_MSG_WINK	  | \
		 NETIF_MSG_TIMEW  | \
		 NETIF_MSG_WX_EWW | \
		 NETIF_MSG_TX_EWW)

static const chaw *wavb_wx_iwqs[NUM_WX_QUEUE] = {
	"ch0", /* WAVB_BE */
	"ch1", /* WAVB_NC */
};

static const chaw *wavb_tx_iwqs[NUM_TX_QUEUE] = {
	"ch18", /* WAVB_BE */
	"ch19", /* WAVB_NC */
};

void wavb_modify(stwuct net_device *ndev, enum wavb_weg weg, u32 cweaw,
		 u32 set)
{
	wavb_wwite(ndev, (wavb_wead(ndev, weg) & ~cweaw) | set, weg);
}

int wavb_wait(stwuct net_device *ndev, enum wavb_weg weg, u32 mask, u32 vawue)
{
	int i;

	fow (i = 0; i < 10000; i++) {
		if ((wavb_wead(ndev, weg) & mask) == vawue)
			wetuwn 0;
		udeway(10);
	}
	wetuwn -ETIMEDOUT;
}

static int wavb_set_opmode(stwuct net_device *ndev, u32 opmode)
{
	u32 csw_ops = 1U << (opmode & CCC_OPC);
	u32 ccc_mask = CCC_OPC;
	int ewwow;

	/* If gPTP active in config mode is suppowted it needs to be configuwed
	 * awong with CSEW and opewating mode in the same access. This is a
	 * hawdwawe wimitation.
	 */
	if (opmode & CCC_GAC)
		ccc_mask |= CCC_GAC | CCC_CSEW;

	/* Set opewating mode */
	wavb_modify(ndev, CCC, ccc_mask, opmode);
	/* Check if the opewating mode is changed to the wequested one */
	ewwow = wavb_wait(ndev, CSW, CSW_OPS, csw_ops);
	if (ewwow) {
		netdev_eww(ndev, "faiwed to switch device to wequested mode (%u)\n",
			   opmode & CCC_OPC);
	}

	wetuwn ewwow;
}

static void wavb_set_wate_gbeth(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	switch (pwiv->speed) {
	case 10:                /* 10BASE */
		wavb_wwite(ndev, GBETH_GECMW_SPEED_10, GECMW);
		bweak;
	case 100:               /* 100BASE */
		wavb_wwite(ndev, GBETH_GECMW_SPEED_100, GECMW);
		bweak;
	case 1000:              /* 1000BASE */
		wavb_wwite(ndev, GBETH_GECMW_SPEED_1000, GECMW);
		bweak;
	}
}

static void wavb_set_wate_wcaw(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	switch (pwiv->speed) {
	case 100:		/* 100BASE */
		wavb_wwite(ndev, GECMW_SPEED_100, GECMW);
		bweak;
	case 1000:		/* 1000BASE */
		wavb_wwite(ndev, GECMW_SPEED_1000, GECMW);
		bweak;
	}
}

static void wavb_set_buffew_awign(stwuct sk_buff *skb)
{
	u32 wesewve = (unsigned wong)skb->data & (WAVB_AWIGN - 1);

	if (wesewve)
		skb_wesewve(skb, WAVB_AWIGN - wesewve);
}

/* Get MAC addwess fwom the MAC addwess wegistews
 *
 * Ethewnet AVB device doesn't have WOM fow MAC addwess.
 * This function gets the MAC addwess that was used by a bootwoadew.
 */
static void wavb_wead_mac_addwess(stwuct device_node *np,
				  stwuct net_device *ndev)
{
	int wet;

	wet = of_get_ethdev_addwess(np, ndev);
	if (wet) {
		u32 mahw = wavb_wead(ndev, MAHW);
		u32 maww = wavb_wead(ndev, MAWW);
		u8 addw[ETH_AWEN];

		addw[0] = (mahw >> 24) & 0xFF;
		addw[1] = (mahw >> 16) & 0xFF;
		addw[2] = (mahw >>  8) & 0xFF;
		addw[3] = (mahw >>  0) & 0xFF;
		addw[4] = (maww >>  8) & 0xFF;
		addw[5] = (maww >>  0) & 0xFF;
		eth_hw_addw_set(ndev, addw);
	}
}

static void wavb_mdio_ctww(stwuct mdiobb_ctww *ctww, u32 mask, int set)
{
	stwuct wavb_pwivate *pwiv = containew_of(ctww, stwuct wavb_pwivate,
						 mdiobb);

	wavb_modify(pwiv->ndev, PIW, mask, set ? mask : 0);
}

/* MDC pin contwow */
static void wavb_set_mdc(stwuct mdiobb_ctww *ctww, int wevew)
{
	wavb_mdio_ctww(ctww, PIW_MDC, wevew);
}

/* Data I/O pin contwow */
static void wavb_set_mdio_diw(stwuct mdiobb_ctww *ctww, int output)
{
	wavb_mdio_ctww(ctww, PIW_MMD, output);
}

/* Set data bit */
static void wavb_set_mdio_data(stwuct mdiobb_ctww *ctww, int vawue)
{
	wavb_mdio_ctww(ctww, PIW_MDO, vawue);
}

/* Get data bit */
static int wavb_get_mdio_data(stwuct mdiobb_ctww *ctww)
{
	stwuct wavb_pwivate *pwiv = containew_of(ctww, stwuct wavb_pwivate,
						 mdiobb);

	wetuwn (wavb_wead(pwiv->ndev, PIW) & PIW_MDI) != 0;
}

/* MDIO bus contwow stwuct */
static const stwuct mdiobb_ops bb_ops = {
	.ownew = THIS_MODUWE,
	.set_mdc = wavb_set_mdc,
	.set_mdio_diw = wavb_set_mdio_diw,
	.set_mdio_data = wavb_set_mdio_data,
	.get_mdio_data = wavb_get_mdio_data,
};

/* Fwee TX skb function fow AVB-IP */
static int wavb_tx_fwee(stwuct net_device *ndev, int q, boow fwee_txed_onwy)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &pwiv->stats[q];
	unsigned int num_tx_desc = pwiv->num_tx_desc;
	stwuct wavb_tx_desc *desc;
	unsigned int entwy;
	int fwee_num = 0;
	u32 size;

	fow (; pwiv->cuw_tx[q] - pwiv->diwty_tx[q] > 0; pwiv->diwty_tx[q]++) {
		boow txed;

		entwy = pwiv->diwty_tx[q] % (pwiv->num_tx_wing[q] *
					     num_tx_desc);
		desc = &pwiv->tx_wing[q][entwy];
		txed = desc->die_dt == DT_FEMPTY;
		if (fwee_txed_onwy && !txed)
			bweak;
		/* Descwiptow type must be checked befowe aww othew weads */
		dma_wmb();
		size = we16_to_cpu(desc->ds_tagw) & TX_DS;
		/* Fwee the owiginaw skb. */
		if (pwiv->tx_skb[q][entwy / num_tx_desc]) {
			dma_unmap_singwe(ndev->dev.pawent, we32_to_cpu(desc->dptw),
					 size, DMA_TO_DEVICE);
			/* Wast packet descwiptow? */
			if (entwy % num_tx_desc == num_tx_desc - 1) {
				entwy /= num_tx_desc;
				dev_kfwee_skb_any(pwiv->tx_skb[q][entwy]);
				pwiv->tx_skb[q][entwy] = NUWW;
				if (txed)
					stats->tx_packets++;
			}
			fwee_num++;
		}
		if (txed)
			stats->tx_bytes += size;
		desc->die_dt = DT_EEMPTY;
	}
	wetuwn fwee_num;
}

static void wavb_wx_wing_fwee_gbeth(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	unsigned int wing_size;
	unsigned int i;

	if (!pwiv->gbeth_wx_wing)
		wetuwn;

	fow (i = 0; i < pwiv->num_wx_wing[q]; i++) {
		stwuct wavb_wx_desc *desc = &pwiv->gbeth_wx_wing[i];

		if (!dma_mapping_ewwow(ndev->dev.pawent,
				       we32_to_cpu(desc->dptw)))
			dma_unmap_singwe(ndev->dev.pawent,
					 we32_to_cpu(desc->dptw),
					 GBETH_WX_BUFF_MAX,
					 DMA_FWOM_DEVICE);
	}
	wing_size = sizeof(stwuct wavb_wx_desc) * (pwiv->num_wx_wing[q] + 1);
	dma_fwee_cohewent(ndev->dev.pawent, wing_size, pwiv->gbeth_wx_wing,
			  pwiv->wx_desc_dma[q]);
	pwiv->gbeth_wx_wing = NUWW;
}

static void wavb_wx_wing_fwee_wcaw(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	unsigned int wing_size;
	unsigned int i;

	if (!pwiv->wx_wing[q])
		wetuwn;

	fow (i = 0; i < pwiv->num_wx_wing[q]; i++) {
		stwuct wavb_ex_wx_desc *desc = &pwiv->wx_wing[q][i];

		if (!dma_mapping_ewwow(ndev->dev.pawent,
				       we32_to_cpu(desc->dptw)))
			dma_unmap_singwe(ndev->dev.pawent,
					 we32_to_cpu(desc->dptw),
					 WX_BUF_SZ,
					 DMA_FWOM_DEVICE);
	}
	wing_size = sizeof(stwuct wavb_ex_wx_desc) *
		    (pwiv->num_wx_wing[q] + 1);
	dma_fwee_cohewent(ndev->dev.pawent, wing_size, pwiv->wx_wing[q],
			  pwiv->wx_desc_dma[q]);
	pwiv->wx_wing[q] = NUWW;
}

/* Fwee skb's and DMA buffews fow Ethewnet AVB */
static void wavb_wing_fwee(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	unsigned int num_tx_desc = pwiv->num_tx_desc;
	unsigned int wing_size;
	unsigned int i;

	info->wx_wing_fwee(ndev, q);

	if (pwiv->tx_wing[q]) {
		wavb_tx_fwee(ndev, q, fawse);

		wing_size = sizeof(stwuct wavb_tx_desc) *
			    (pwiv->num_tx_wing[q] * num_tx_desc + 1);
		dma_fwee_cohewent(ndev->dev.pawent, wing_size, pwiv->tx_wing[q],
				  pwiv->tx_desc_dma[q]);
		pwiv->tx_wing[q] = NUWW;
	}

	/* Fwee WX skb wingbuffew */
	if (pwiv->wx_skb[q]) {
		fow (i = 0; i < pwiv->num_wx_wing[q]; i++)
			dev_kfwee_skb(pwiv->wx_skb[q][i]);
	}
	kfwee(pwiv->wx_skb[q]);
	pwiv->wx_skb[q] = NUWW;

	/* Fwee awigned TX buffews */
	kfwee(pwiv->tx_awign[q]);
	pwiv->tx_awign[q] = NUWW;

	/* Fwee TX skb wingbuffew.
	 * SKBs awe fweed by wavb_tx_fwee() caww above.
	 */
	kfwee(pwiv->tx_skb[q]);
	pwiv->tx_skb[q] = NUWW;
}

static void wavb_wx_wing_fowmat_gbeth(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct wavb_wx_desc *wx_desc;
	unsigned int wx_wing_size;
	dma_addw_t dma_addw;
	unsigned int i;

	wx_wing_size = sizeof(*wx_desc) * pwiv->num_wx_wing[q];
	memset(pwiv->gbeth_wx_wing, 0, wx_wing_size);
	/* Buiwd WX wing buffew */
	fow (i = 0; i < pwiv->num_wx_wing[q]; i++) {
		/* WX descwiptow */
		wx_desc = &pwiv->gbeth_wx_wing[i];
		wx_desc->ds_cc = cpu_to_we16(GBETH_WX_DESC_DATA_SIZE);
		dma_addw = dma_map_singwe(ndev->dev.pawent, pwiv->wx_skb[q][i]->data,
					  GBETH_WX_BUFF_MAX,
					  DMA_FWOM_DEVICE);
		/* We just set the data size to 0 fow a faiwed mapping which
		 * shouwd pwevent DMA fwom happening...
		 */
		if (dma_mapping_ewwow(ndev->dev.pawent, dma_addw))
			wx_desc->ds_cc = cpu_to_we16(0);
		wx_desc->dptw = cpu_to_we32(dma_addw);
		wx_desc->die_dt = DT_FEMPTY;
	}
	wx_desc = &pwiv->gbeth_wx_wing[i];
	wx_desc->dptw = cpu_to_we32((u32)pwiv->wx_desc_dma[q]);
	wx_desc->die_dt = DT_WINKFIX; /* type */
}

static void wavb_wx_wing_fowmat_wcaw(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct wavb_ex_wx_desc *wx_desc;
	unsigned int wx_wing_size = sizeof(*wx_desc) * pwiv->num_wx_wing[q];
	dma_addw_t dma_addw;
	unsigned int i;

	memset(pwiv->wx_wing[q], 0, wx_wing_size);
	/* Buiwd WX wing buffew */
	fow (i = 0; i < pwiv->num_wx_wing[q]; i++) {
		/* WX descwiptow */
		wx_desc = &pwiv->wx_wing[q][i];
		wx_desc->ds_cc = cpu_to_we16(WX_BUF_SZ);
		dma_addw = dma_map_singwe(ndev->dev.pawent, pwiv->wx_skb[q][i]->data,
					  WX_BUF_SZ,
					  DMA_FWOM_DEVICE);
		/* We just set the data size to 0 fow a faiwed mapping which
		 * shouwd pwevent DMA fwom happening...
		 */
		if (dma_mapping_ewwow(ndev->dev.pawent, dma_addw))
			wx_desc->ds_cc = cpu_to_we16(0);
		wx_desc->dptw = cpu_to_we32(dma_addw);
		wx_desc->die_dt = DT_FEMPTY;
	}
	wx_desc = &pwiv->wx_wing[q][i];
	wx_desc->dptw = cpu_to_we32((u32)pwiv->wx_desc_dma[q]);
	wx_desc->die_dt = DT_WINKFIX; /* type */
}

/* Fowmat skb and descwiptow buffew fow Ethewnet AVB */
static void wavb_wing_fowmat(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	unsigned int num_tx_desc = pwiv->num_tx_desc;
	stwuct wavb_tx_desc *tx_desc;
	stwuct wavb_desc *desc;
	unsigned int tx_wing_size = sizeof(*tx_desc) * pwiv->num_tx_wing[q] *
				    num_tx_desc;
	unsigned int i;

	pwiv->cuw_wx[q] = 0;
	pwiv->cuw_tx[q] = 0;
	pwiv->diwty_wx[q] = 0;
	pwiv->diwty_tx[q] = 0;

	info->wx_wing_fowmat(ndev, q);

	memset(pwiv->tx_wing[q], 0, tx_wing_size);
	/* Buiwd TX wing buffew */
	fow (i = 0, tx_desc = pwiv->tx_wing[q]; i < pwiv->num_tx_wing[q];
	     i++, tx_desc++) {
		tx_desc->die_dt = DT_EEMPTY;
		if (num_tx_desc > 1) {
			tx_desc++;
			tx_desc->die_dt = DT_EEMPTY;
		}
	}
	tx_desc->dptw = cpu_to_we32((u32)pwiv->tx_desc_dma[q]);
	tx_desc->die_dt = DT_WINKFIX; /* type */

	/* WX descwiptow base addwess fow best effowt */
	desc = &pwiv->desc_bat[WX_QUEUE_OFFSET + q];
	desc->die_dt = DT_WINKFIX; /* type */
	desc->dptw = cpu_to_we32((u32)pwiv->wx_desc_dma[q]);

	/* TX descwiptow base addwess fow best effowt */
	desc = &pwiv->desc_bat[q];
	desc->die_dt = DT_WINKFIX; /* type */
	desc->dptw = cpu_to_we32((u32)pwiv->tx_desc_dma[q]);
}

static void *wavb_awwoc_wx_desc_gbeth(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	unsigned int wing_size;

	wing_size = sizeof(stwuct wavb_wx_desc) * (pwiv->num_wx_wing[q] + 1);

	pwiv->gbeth_wx_wing = dma_awwoc_cohewent(ndev->dev.pawent, wing_size,
						 &pwiv->wx_desc_dma[q],
						 GFP_KEWNEW);
	wetuwn pwiv->gbeth_wx_wing;
}

static void *wavb_awwoc_wx_desc_wcaw(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	unsigned int wing_size;

	wing_size = sizeof(stwuct wavb_ex_wx_desc) * (pwiv->num_wx_wing[q] + 1);

	pwiv->wx_wing[q] = dma_awwoc_cohewent(ndev->dev.pawent, wing_size,
					      &pwiv->wx_desc_dma[q],
					      GFP_KEWNEW);
	wetuwn pwiv->wx_wing[q];
}

/* Init skb and descwiptow buffew fow Ethewnet AVB */
static int wavb_wing_init(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	unsigned int num_tx_desc = pwiv->num_tx_desc;
	unsigned int wing_size;
	stwuct sk_buff *skb;
	unsigned int i;

	/* Awwocate WX and TX skb wings */
	pwiv->wx_skb[q] = kcawwoc(pwiv->num_wx_wing[q],
				  sizeof(*pwiv->wx_skb[q]), GFP_KEWNEW);
	pwiv->tx_skb[q] = kcawwoc(pwiv->num_tx_wing[q],
				  sizeof(*pwiv->tx_skb[q]), GFP_KEWNEW);
	if (!pwiv->wx_skb[q] || !pwiv->tx_skb[q])
		goto ewwow;

	fow (i = 0; i < pwiv->num_wx_wing[q]; i++) {
		skb = __netdev_awwoc_skb(ndev, info->max_wx_wen, GFP_KEWNEW);
		if (!skb)
			goto ewwow;
		wavb_set_buffew_awign(skb);
		pwiv->wx_skb[q][i] = skb;
	}

	if (num_tx_desc > 1) {
		/* Awwocate wings fow the awigned buffews */
		pwiv->tx_awign[q] = kmawwoc(DPTW_AWIGN * pwiv->num_tx_wing[q] +
					    DPTW_AWIGN - 1, GFP_KEWNEW);
		if (!pwiv->tx_awign[q])
			goto ewwow;
	}

	/* Awwocate aww WX descwiptows. */
	if (!info->awwoc_wx_desc(ndev, q))
		goto ewwow;

	pwiv->diwty_wx[q] = 0;

	/* Awwocate aww TX descwiptows. */
	wing_size = sizeof(stwuct wavb_tx_desc) *
		    (pwiv->num_tx_wing[q] * num_tx_desc + 1);
	pwiv->tx_wing[q] = dma_awwoc_cohewent(ndev->dev.pawent, wing_size,
					      &pwiv->tx_desc_dma[q],
					      GFP_KEWNEW);
	if (!pwiv->tx_wing[q])
		goto ewwow;

	wetuwn 0;

ewwow:
	wavb_wing_fwee(ndev, q);

	wetuwn -ENOMEM;
}

static void wavb_emac_init_gbeth(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	if (pwiv->phy_intewface == PHY_INTEWFACE_MODE_MII) {
		wavb_wwite(ndev, (1000 << 16) | CXW35_SEW_XMII_MII, CXW35);
		wavb_modify(ndev, CXW31, CXW31_SEW_WINK0 | CXW31_SEW_WINK1, 0);
	} ewse {
		wavb_wwite(ndev, (1000 << 16) | CXW35_SEW_XMII_WGMII, CXW35);
		wavb_modify(ndev, CXW31, CXW31_SEW_WINK0 | CXW31_SEW_WINK1,
			    CXW31_SEW_WINK0);
	}

	/* Weceive fwame wimit set wegistew */
	wavb_wwite(ndev, GBETH_WX_BUFF_MAX + ETH_FCS_WEN, WFWW);

	/* EMAC Mode: PAUSE pwohibition; Dupwex; TX; WX; CWC Pass Thwough */
	wavb_wwite(ndev, ECMW_ZPF | ((pwiv->dupwex > 0) ? ECMW_DM : 0) |
			 ECMW_TE | ECMW_WE | ECMW_WCPT |
			 ECMW_TXF | ECMW_WXF, ECMW);

	wavb_set_wate_gbeth(ndev);

	/* Set MAC addwess */
	wavb_wwite(ndev,
		   (ndev->dev_addw[0] << 24) | (ndev->dev_addw[1] << 16) |
		   (ndev->dev_addw[2] << 8)  | (ndev->dev_addw[3]), MAHW);
	wavb_wwite(ndev, (ndev->dev_addw[4] << 8)  | (ndev->dev_addw[5]), MAWW);

	/* E-MAC status wegistew cweaw */
	wavb_wwite(ndev, ECSW_ICD | ECSW_WCHNG | ECSW_PFWI, ECSW);
	wavb_wwite(ndev, CSW0_TPE | CSW0_WPE, CSW0);

	/* E-MAC intewwupt enabwe wegistew */
	wavb_wwite(ndev, ECSIPW_ICDIP, ECSIPW);
}

static void wavb_emac_init_wcaw(stwuct net_device *ndev)
{
	/* Weceive fwame wimit set wegistew */
	wavb_wwite(ndev, ndev->mtu + ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN, WFWW);

	/* EMAC Mode: PAUSE pwohibition; Dupwex; WX Checksum; TX; WX */
	wavb_wwite(ndev, ECMW_ZPF | ECMW_DM |
		   (ndev->featuwes & NETIF_F_WXCSUM ? ECMW_WCSC : 0) |
		   ECMW_TE | ECMW_WE, ECMW);

	wavb_set_wate_wcaw(ndev);

	/* Set MAC addwess */
	wavb_wwite(ndev,
		   (ndev->dev_addw[0] << 24) | (ndev->dev_addw[1] << 16) |
		   (ndev->dev_addw[2] << 8)  | (ndev->dev_addw[3]), MAHW);
	wavb_wwite(ndev,
		   (ndev->dev_addw[4] << 8)  | (ndev->dev_addw[5]), MAWW);

	/* E-MAC status wegistew cweaw */
	wavb_wwite(ndev, ECSW_ICD | ECSW_MPD, ECSW);

	/* E-MAC intewwupt enabwe wegistew */
	wavb_wwite(ndev, ECSIPW_ICDIP | ECSIPW_MPDIP | ECSIPW_WCHNGIP, ECSIPW);
}

/* E-MAC init function */
static void wavb_emac_init(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	info->emac_init(ndev);
}

static int wavb_dmac_init_gbeth(stwuct net_device *ndev)
{
	int ewwow;

	ewwow = wavb_wing_init(ndev, WAVB_BE);
	if (ewwow)
		wetuwn ewwow;

	/* Descwiptow fowmat */
	wavb_wing_fowmat(ndev, WAVB_BE);

	/* Set DMAC WX */
	wavb_wwite(ndev, 0x60000000, WCW);

	/* Set Max Fwame Wength (WTC) */
	wavb_wwite(ndev, 0x7ffc0000 | GBETH_WX_BUFF_MAX, WTC);

	/* Set FIFO size */
	wavb_wwite(ndev, 0x00222200, TGC);

	wavb_wwite(ndev, 0, TCCW);

	/* Fwame weceive */
	wavb_wwite(ndev, WIC0_FWE0, WIC0);
	/* Disabwe FIFO fuww wawning */
	wavb_wwite(ndev, 0x0, WIC1);
	/* Weceive FIFO fuww ewwow, descwiptow empty */
	wavb_wwite(ndev, WIC2_QFE0 | WIC2_WFFE, WIC2);

	wavb_wwite(ndev, TIC_FTE0, TIC);

	wetuwn 0;
}

static int wavb_dmac_init_wcaw(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int ewwow;

	ewwow = wavb_wing_init(ndev, WAVB_BE);
	if (ewwow)
		wetuwn ewwow;
	ewwow = wavb_wing_init(ndev, WAVB_NC);
	if (ewwow) {
		wavb_wing_fwee(ndev, WAVB_BE);
		wetuwn ewwow;
	}

	/* Descwiptow fowmat */
	wavb_wing_fowmat(ndev, WAVB_BE);
	wavb_wing_fowmat(ndev, WAVB_NC);

	/* Set AVB WX */
	wavb_wwite(ndev,
		   WCW_EFFS | WCW_ENCF | WCW_ETS0 | WCW_ESF | 0x18000000, WCW);

	/* Set FIFO size */
	wavb_wwite(ndev, TGC_TQP_AVBMODE1 | 0x00112200, TGC);

	/* Timestamp enabwe */
	wavb_wwite(ndev, TCCW_TFEN, TCCW);

	/* Intewwupt init: */
	if (info->muwti_iwqs) {
		/* Cweaw DIW.DPWx */
		wavb_wwite(ndev, 0, DIW);
		/* Set queue specific intewwupt */
		wavb_wwite(ndev, CIE_CWIE | CIE_CTIE | CIE_CW0M, CIE);
	}
	/* Fwame weceive */
	wavb_wwite(ndev, WIC0_FWE0 | WIC0_FWE1, WIC0);
	/* Disabwe FIFO fuww wawning */
	wavb_wwite(ndev, 0, WIC1);
	/* Weceive FIFO fuww ewwow, descwiptow empty */
	wavb_wwite(ndev, WIC2_QFE0 | WIC2_QFE1 | WIC2_WFFE, WIC2);
	/* Fwame twansmitted, timestamp FIFO updated */
	wavb_wwite(ndev, TIC_FTE0 | TIC_FTE1 | TIC_TFUE, TIC);

	wetuwn 0;
}

/* Device init function fow Ethewnet AVB */
static int wavb_dmac_init(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int ewwow;

	/* Set CONFIG mode */
	ewwow = wavb_set_opmode(ndev, CCC_OPC_CONFIG);
	if (ewwow)
		wetuwn ewwow;

	ewwow = info->dmac_init(ndev);
	if (ewwow)
		wetuwn ewwow;

	/* Setting the contwow wiww stawt the AVB-DMAC pwocess. */
	wetuwn wavb_set_opmode(ndev, CCC_OPC_OPEWATION);
}

static void wavb_get_tx_tstamp(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct wavb_tstamp_skb *ts_skb, *ts_skb2;
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct sk_buff *skb;
	stwuct timespec64 ts;
	u16 tag, tfa_tag;
	int count;
	u32 tfa2;

	count = (wavb_wead(ndev, TSW) & TSW_TFFW) >> 8;
	whiwe (count--) {
		tfa2 = wavb_wead(ndev, TFA2);
		tfa_tag = (tfa2 & TFA2_TST) >> 16;
		ts.tv_nsec = (u64)wavb_wead(ndev, TFA0);
		ts.tv_sec = ((u64)(tfa2 & TFA2_TSV) << 32) |
			    wavb_wead(ndev, TFA1);
		memset(&shhwtstamps, 0, sizeof(shhwtstamps));
		shhwtstamps.hwtstamp = timespec64_to_ktime(ts);
		wist_fow_each_entwy_safe(ts_skb, ts_skb2, &pwiv->ts_skb_wist,
					 wist) {
			skb = ts_skb->skb;
			tag = ts_skb->tag;
			wist_dew(&ts_skb->wist);
			kfwee(ts_skb);
			if (tag == tfa_tag) {
				skb_tstamp_tx(skb, &shhwtstamps);
				dev_consume_skb_any(skb);
				bweak;
			} ewse {
				dev_kfwee_skb_any(skb);
			}
		}
		wavb_modify(ndev, TCCW, TCCW_TFW, TCCW_TFW);
	}
}

static void wavb_wx_csum(stwuct sk_buff *skb)
{
	u8 *hw_csum;

	/* The hawdwawe checksum is contained in sizeof(__sum16) (2) bytes
	 * appended to packet data
	 */
	if (unwikewy(skb->wen < sizeof(__sum16)))
		wetuwn;
	hw_csum = skb_taiw_pointew(skb) - sizeof(__sum16);
	skb->csum = csum_unfowd((__fowce __sum16)get_unawigned_we16(hw_csum));
	skb->ip_summed = CHECKSUM_COMPWETE;
	skb_twim(skb, skb->wen - sizeof(__sum16));
}

static stwuct sk_buff *wavb_get_skb_gbeth(stwuct net_device *ndev, int entwy,
					  stwuct wavb_wx_desc *desc)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct sk_buff *skb;

	skb = pwiv->wx_skb[WAVB_BE][entwy];
	pwiv->wx_skb[WAVB_BE][entwy] = NUWW;
	dma_unmap_singwe(ndev->dev.pawent, we32_to_cpu(desc->dptw),
			 AWIGN(GBETH_WX_BUFF_MAX, 16), DMA_FWOM_DEVICE);

	wetuwn skb;
}

/* Packet weceive function fow Gigabit Ethewnet */
static boow wavb_wx_gbeth(stwuct net_device *ndev, int *quota, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct net_device_stats *stats;
	stwuct wavb_wx_desc *desc;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	u8  desc_status;
	int boguscnt;
	u16 pkt_wen;
	u8  die_dt;
	int entwy;
	int wimit;

	entwy = pwiv->cuw_wx[q] % pwiv->num_wx_wing[q];
	boguscnt = pwiv->diwty_wx[q] + pwiv->num_wx_wing[q] - pwiv->cuw_wx[q];
	stats = &pwiv->stats[q];

	boguscnt = min(boguscnt, *quota);
	wimit = boguscnt;
	desc = &pwiv->gbeth_wx_wing[entwy];
	whiwe (desc->die_dt != DT_FEMPTY) {
		/* Descwiptow type must be checked befowe aww othew weads */
		dma_wmb();
		desc_status = desc->msc;
		pkt_wen = we16_to_cpu(desc->ds_cc) & WX_DS;

		if (--boguscnt < 0)
			bweak;

		/* We use 0-byte descwiptows to mawk the DMA mapping ewwows */
		if (!pkt_wen)
			continue;

		if (desc_status & MSC_MC)
			stats->muwticast++;

		if (desc_status & (MSC_CWC | MSC_WFE | MSC_WTSF | MSC_WTWF | MSC_CEEF)) {
			stats->wx_ewwows++;
			if (desc_status & MSC_CWC)
				stats->wx_cwc_ewwows++;
			if (desc_status & MSC_WFE)
				stats->wx_fwame_ewwows++;
			if (desc_status & (MSC_WTWF | MSC_WTSF))
				stats->wx_wength_ewwows++;
			if (desc_status & MSC_CEEF)
				stats->wx_missed_ewwows++;
		} ewse {
			die_dt = desc->die_dt & 0xF0;
			switch (die_dt) {
			case DT_FSINGWE:
				skb = wavb_get_skb_gbeth(ndev, entwy, desc);
				skb_put(skb, pkt_wen);
				skb->pwotocow = eth_type_twans(skb, ndev);
				napi_gwo_weceive(&pwiv->napi[q], skb);
				stats->wx_packets++;
				stats->wx_bytes += pkt_wen;
				bweak;
			case DT_FSTAWT:
				pwiv->wx_1st_skb = wavb_get_skb_gbeth(ndev, entwy, desc);
				skb_put(pwiv->wx_1st_skb, pkt_wen);
				bweak;
			case DT_FMID:
				skb = wavb_get_skb_gbeth(ndev, entwy, desc);
				skb_copy_to_wineaw_data_offset(pwiv->wx_1st_skb,
							       pwiv->wx_1st_skb->wen,
							       skb->data,
							       pkt_wen);
				skb_put(pwiv->wx_1st_skb, pkt_wen);
				dev_kfwee_skb(skb);
				bweak;
			case DT_FEND:
				skb = wavb_get_skb_gbeth(ndev, entwy, desc);
				skb_copy_to_wineaw_data_offset(pwiv->wx_1st_skb,
							       pwiv->wx_1st_skb->wen,
							       skb->data,
							       pkt_wen);
				skb_put(pwiv->wx_1st_skb, pkt_wen);
				dev_kfwee_skb(skb);
				pwiv->wx_1st_skb->pwotocow =
					eth_type_twans(pwiv->wx_1st_skb, ndev);
				napi_gwo_weceive(&pwiv->napi[q],
						 pwiv->wx_1st_skb);
				stats->wx_packets++;
				stats->wx_bytes += pkt_wen;
				bweak;
			}
		}

		entwy = (++pwiv->cuw_wx[q]) % pwiv->num_wx_wing[q];
		desc = &pwiv->gbeth_wx_wing[entwy];
	}

	/* Wefiww the WX wing buffews. */
	fow (; pwiv->cuw_wx[q] - pwiv->diwty_wx[q] > 0; pwiv->diwty_wx[q]++) {
		entwy = pwiv->diwty_wx[q] % pwiv->num_wx_wing[q];
		desc = &pwiv->gbeth_wx_wing[entwy];
		desc->ds_cc = cpu_to_we16(GBETH_WX_DESC_DATA_SIZE);

		if (!pwiv->wx_skb[q][entwy]) {
			skb = netdev_awwoc_skb(ndev, info->max_wx_wen);
			if (!skb)
				bweak;
			wavb_set_buffew_awign(skb);
			dma_addw = dma_map_singwe(ndev->dev.pawent,
						  skb->data,
						  GBETH_WX_BUFF_MAX,
						  DMA_FWOM_DEVICE);
			skb_checksum_none_assewt(skb);
			/* We just set the data size to 0 fow a faiwed mapping
			 * which shouwd pwevent DMA  fwom happening...
			 */
			if (dma_mapping_ewwow(ndev->dev.pawent, dma_addw))
				desc->ds_cc = cpu_to_we16(0);
			desc->dptw = cpu_to_we32(dma_addw);
			pwiv->wx_skb[q][entwy] = skb;
		}
		/* Descwiptow type must be set aftew aww the above wwites */
		dma_wmb();
		desc->die_dt = DT_FEMPTY;
	}

	*quota -= wimit - (++boguscnt);

	wetuwn boguscnt <= 0;
}

/* Packet weceive function fow Ethewnet AVB */
static boow wavb_wx_wcaw(stwuct net_device *ndev, int *quota, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int entwy = pwiv->cuw_wx[q] % pwiv->num_wx_wing[q];
	int boguscnt = (pwiv->diwty_wx[q] + pwiv->num_wx_wing[q]) -
			pwiv->cuw_wx[q];
	stwuct net_device_stats *stats = &pwiv->stats[q];
	stwuct wavb_ex_wx_desc *desc;
	stwuct sk_buff *skb;
	dma_addw_t dma_addw;
	stwuct timespec64 ts;
	u8  desc_status;
	u16 pkt_wen;
	int wimit;

	boguscnt = min(boguscnt, *quota);
	wimit = boguscnt;
	desc = &pwiv->wx_wing[q][entwy];
	whiwe (desc->die_dt != DT_FEMPTY) {
		/* Descwiptow type must be checked befowe aww othew weads */
		dma_wmb();
		desc_status = desc->msc;
		pkt_wen = we16_to_cpu(desc->ds_cc) & WX_DS;

		if (--boguscnt < 0)
			bweak;

		/* We use 0-byte descwiptows to mawk the DMA mapping ewwows */
		if (!pkt_wen)
			continue;

		if (desc_status & MSC_MC)
			stats->muwticast++;

		if (desc_status & (MSC_CWC | MSC_WFE | MSC_WTSF | MSC_WTWF |
				   MSC_CEEF)) {
			stats->wx_ewwows++;
			if (desc_status & MSC_CWC)
				stats->wx_cwc_ewwows++;
			if (desc_status & MSC_WFE)
				stats->wx_fwame_ewwows++;
			if (desc_status & (MSC_WTWF | MSC_WTSF))
				stats->wx_wength_ewwows++;
			if (desc_status & MSC_CEEF)
				stats->wx_missed_ewwows++;
		} ewse {
			u32 get_ts = pwiv->tstamp_wx_ctww & WAVB_WXTSTAMP_TYPE;

			skb = pwiv->wx_skb[q][entwy];
			pwiv->wx_skb[q][entwy] = NUWW;
			dma_unmap_singwe(ndev->dev.pawent, we32_to_cpu(desc->dptw),
					 WX_BUF_SZ,
					 DMA_FWOM_DEVICE);
			get_ts &= (q == WAVB_NC) ?
					WAVB_WXTSTAMP_TYPE_V2_W2_EVENT :
					~WAVB_WXTSTAMP_TYPE_V2_W2_EVENT;
			if (get_ts) {
				stwuct skb_shawed_hwtstamps *shhwtstamps;

				shhwtstamps = skb_hwtstamps(skb);
				memset(shhwtstamps, 0, sizeof(*shhwtstamps));
				ts.tv_sec = ((u64) we16_to_cpu(desc->ts_sh) <<
					     32) | we32_to_cpu(desc->ts_sw);
				ts.tv_nsec = we32_to_cpu(desc->ts_n);
				shhwtstamps->hwtstamp = timespec64_to_ktime(ts);
			}

			skb_put(skb, pkt_wen);
			skb->pwotocow = eth_type_twans(skb, ndev);
			if (ndev->featuwes & NETIF_F_WXCSUM)
				wavb_wx_csum(skb);
			napi_gwo_weceive(&pwiv->napi[q], skb);
			stats->wx_packets++;
			stats->wx_bytes += pkt_wen;
		}

		entwy = (++pwiv->cuw_wx[q]) % pwiv->num_wx_wing[q];
		desc = &pwiv->wx_wing[q][entwy];
	}

	/* Wefiww the WX wing buffews. */
	fow (; pwiv->cuw_wx[q] - pwiv->diwty_wx[q] > 0; pwiv->diwty_wx[q]++) {
		entwy = pwiv->diwty_wx[q] % pwiv->num_wx_wing[q];
		desc = &pwiv->wx_wing[q][entwy];
		desc->ds_cc = cpu_to_we16(WX_BUF_SZ);

		if (!pwiv->wx_skb[q][entwy]) {
			skb = netdev_awwoc_skb(ndev, info->max_wx_wen);
			if (!skb)
				bweak;	/* Bettew wuck next wound. */
			wavb_set_buffew_awign(skb);
			dma_addw = dma_map_singwe(ndev->dev.pawent, skb->data,
						  we16_to_cpu(desc->ds_cc),
						  DMA_FWOM_DEVICE);
			skb_checksum_none_assewt(skb);
			/* We just set the data size to 0 fow a faiwed mapping
			 * which shouwd pwevent DMA  fwom happening...
			 */
			if (dma_mapping_ewwow(ndev->dev.pawent, dma_addw))
				desc->ds_cc = cpu_to_we16(0);
			desc->dptw = cpu_to_we32(dma_addw);
			pwiv->wx_skb[q][entwy] = skb;
		}
		/* Descwiptow type must be set aftew aww the above wwites */
		dma_wmb();
		desc->die_dt = DT_FEMPTY;
	}

	*quota -= wimit - (++boguscnt);

	wetuwn boguscnt <= 0;
}

/* Packet weceive function fow Ethewnet AVB */
static boow wavb_wx(stwuct net_device *ndev, int *quota, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	wetuwn info->weceive(ndev, quota, q);
}

static void wavb_wcv_snd_disabwe(stwuct net_device *ndev)
{
	/* Disabwe TX and WX */
	wavb_modify(ndev, ECMW, ECMW_WE | ECMW_TE, 0);
}

static void wavb_wcv_snd_enabwe(stwuct net_device *ndev)
{
	/* Enabwe TX and WX */
	wavb_modify(ndev, ECMW, ECMW_WE | ECMW_TE, ECMW_WE | ECMW_TE);
}

/* function fow waiting dma pwocess finished */
static int wavb_stop_dma(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int ewwow;

	/* Wait fow stopping the hawdwawe TX pwocess */
	ewwow = wavb_wait(ndev, TCCW, info->tccw_mask, 0);

	if (ewwow)
		wetuwn ewwow;

	ewwow = wavb_wait(ndev, CSW, CSW_TPO0 | CSW_TPO1 | CSW_TPO2 | CSW_TPO3,
			  0);
	if (ewwow)
		wetuwn ewwow;

	/* Stop the E-MAC's WX/TX pwocesses. */
	wavb_wcv_snd_disabwe(ndev);

	/* Wait fow stopping the WX DMA pwocess */
	ewwow = wavb_wait(ndev, CSW, CSW_WPO, 0);
	if (ewwow)
		wetuwn ewwow;

	/* Stop AVB-DMAC pwocess */
	wetuwn wavb_set_opmode(ndev, CCC_OPC_CONFIG);
}

/* E-MAC intewwupt handwew */
static void wavb_emac_intewwupt_unwocked(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	u32 ecsw, psw;

	ecsw = wavb_wead(ndev, ECSW);
	wavb_wwite(ndev, ecsw, ECSW);	/* cweaw intewwupt */

	if (ecsw & ECSW_MPD)
		pm_wakeup_event(&pwiv->pdev->dev, 0);
	if (ecsw & ECSW_ICD)
		ndev->stats.tx_cawwiew_ewwows++;
	if (ecsw & ECSW_WCHNG) {
		/* Wink changed */
		if (pwiv->no_avb_wink)
			wetuwn;
		psw = wavb_wead(ndev, PSW);
		if (pwiv->avb_wink_active_wow)
			psw ^= PSW_WMON;
		if (!(psw & PSW_WMON)) {
			/* DIsabwe WX and TX */
			wavb_wcv_snd_disabwe(ndev);
		} ewse {
			/* Enabwe WX and TX */
			wavb_wcv_snd_enabwe(ndev);
		}
	}
}

static iwqwetuwn_t wavb_emac_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	spin_wock(&pwiv->wock);
	wavb_emac_intewwupt_unwocked(ndev);
	spin_unwock(&pwiv->wock);
	wetuwn IWQ_HANDWED;
}

/* Ewwow intewwupt handwew */
static void wavb_ewwow_intewwupt(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	u32 eis, wis2;

	eis = wavb_wead(ndev, EIS);
	wavb_wwite(ndev, ~(EIS_QFS | EIS_WESEWVED), EIS);
	if (eis & EIS_QFS) {
		wis2 = wavb_wead(ndev, WIS2);
		wavb_wwite(ndev, ~(WIS2_QFF0 | WIS2_QFF1 | WIS2_WFFF | WIS2_WESEWVED),
			   WIS2);

		/* Weceive Descwiptow Empty int */
		if (wis2 & WIS2_QFF0)
			pwiv->stats[WAVB_BE].wx_ovew_ewwows++;

		/* Weceive Descwiptow Empty int */
		if (wis2 & WIS2_QFF1)
			pwiv->stats[WAVB_NC].wx_ovew_ewwows++;

		/* Weceive FIFO Ovewfwow int */
		if (wis2 & WIS2_WFFF)
			pwiv->wx_fifo_ewwows++;
	}
}

static boow wavb_queue_intewwupt(stwuct net_device *ndev, int q)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	u32 wis0 = wavb_wead(ndev, WIS0);
	u32 wic0 = wavb_wead(ndev, WIC0);
	u32 tis  = wavb_wead(ndev, TIS);
	u32 tic  = wavb_wead(ndev, TIC);

	if (((wis0 & wic0) & BIT(q)) || ((tis  & tic)  & BIT(q))) {
		if (napi_scheduwe_pwep(&pwiv->napi[q])) {
			/* Mask WX and TX intewwupts */
			if (!info->iwq_en_dis) {
				wavb_wwite(ndev, wic0 & ~BIT(q), WIC0);
				wavb_wwite(ndev, tic & ~BIT(q), TIC);
			} ewse {
				wavb_wwite(ndev, BIT(q), WID0);
				wavb_wwite(ndev, BIT(q), TID);
			}
			__napi_scheduwe(&pwiv->napi[q]);
		} ewse {
			netdev_wawn(ndev,
				    "ignowing intewwupt, wx status 0x%08x, wx mask 0x%08x,\n",
				    wis0, wic0);
			netdev_wawn(ndev,
				    "                    tx status 0x%08x, tx mask 0x%08x.\n",
				    tis, tic);
		}
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow wavb_timestamp_intewwupt(stwuct net_device *ndev)
{
	u32 tis = wavb_wead(ndev, TIS);

	if (tis & TIS_TFUF) {
		wavb_wwite(ndev, ~(TIS_TFUF | TIS_WESEWVED), TIS);
		wavb_get_tx_tstamp(ndev);
		wetuwn twue;
	}
	wetuwn fawse;
}

static iwqwetuwn_t wavb_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	iwqwetuwn_t wesuwt = IWQ_NONE;
	u32 iss;

	spin_wock(&pwiv->wock);
	/* Get intewwupt status */
	iss = wavb_wead(ndev, ISS);

	/* Weceived and twansmitted intewwupts */
	if (iss & (ISS_FWS | ISS_FTS | ISS_TFUS)) {
		int q;

		/* Timestamp updated */
		if (wavb_timestamp_intewwupt(ndev))
			wesuwt = IWQ_HANDWED;

		/* Netwowk contwow and best effowt queue WX/TX */
		if (info->nc_queues) {
			fow (q = WAVB_NC; q >= WAVB_BE; q--) {
				if (wavb_queue_intewwupt(ndev, q))
					wesuwt = IWQ_HANDWED;
			}
		} ewse {
			if (wavb_queue_intewwupt(ndev, WAVB_BE))
				wesuwt = IWQ_HANDWED;
		}
	}

	/* E-MAC status summawy */
	if (iss & ISS_MS) {
		wavb_emac_intewwupt_unwocked(ndev);
		wesuwt = IWQ_HANDWED;
	}

	/* Ewwow status summawy */
	if (iss & ISS_ES) {
		wavb_ewwow_intewwupt(ndev);
		wesuwt = IWQ_HANDWED;
	}

	/* gPTP intewwupt status summawy */
	if (iss & ISS_CGIS) {
		wavb_ptp_intewwupt(ndev);
		wesuwt = IWQ_HANDWED;
	}

	spin_unwock(&pwiv->wock);
	wetuwn wesuwt;
}

/* Timestamp/Ewwow/gPTP intewwupt handwew */
static iwqwetuwn_t wavb_muwti_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	iwqwetuwn_t wesuwt = IWQ_NONE;
	u32 iss;

	spin_wock(&pwiv->wock);
	/* Get intewwupt status */
	iss = wavb_wead(ndev, ISS);

	/* Timestamp updated */
	if ((iss & ISS_TFUS) && wavb_timestamp_intewwupt(ndev))
		wesuwt = IWQ_HANDWED;

	/* Ewwow status summawy */
	if (iss & ISS_ES) {
		wavb_ewwow_intewwupt(ndev);
		wesuwt = IWQ_HANDWED;
	}

	/* gPTP intewwupt status summawy */
	if (iss & ISS_CGIS) {
		wavb_ptp_intewwupt(ndev);
		wesuwt = IWQ_HANDWED;
	}

	spin_unwock(&pwiv->wock);
	wetuwn wesuwt;
}

static iwqwetuwn_t wavb_dma_intewwupt(int iwq, void *dev_id, int q)
{
	stwuct net_device *ndev = dev_id;
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	iwqwetuwn_t wesuwt = IWQ_NONE;

	spin_wock(&pwiv->wock);

	/* Netwowk contwow/Best effowt queue WX/TX */
	if (wavb_queue_intewwupt(ndev, q))
		wesuwt = IWQ_HANDWED;

	spin_unwock(&pwiv->wock);
	wetuwn wesuwt;
}

static iwqwetuwn_t wavb_be_intewwupt(int iwq, void *dev_id)
{
	wetuwn wavb_dma_intewwupt(iwq, dev_id, WAVB_BE);
}

static iwqwetuwn_t wavb_nc_intewwupt(int iwq, void *dev_id)
{
	wetuwn wavb_dma_intewwupt(iwq, dev_id, WAVB_NC);
}

static int wavb_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct net_device *ndev = napi->dev;
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	boow gptp = info->gptp || info->ccc_gac;
	stwuct wavb_wx_desc *desc;
	unsigned wong fwags;
	int q = napi - pwiv->napi;
	int mask = BIT(q);
	int quota = budget;
	unsigned int entwy;

	if (!gptp) {
		entwy = pwiv->cuw_wx[q] % pwiv->num_wx_wing[q];
		desc = &pwiv->gbeth_wx_wing[entwy];
	}
	/* Pwocessing WX Descwiptow Wing */
	/* Cweaw WX intewwupt */
	wavb_wwite(ndev, ~(mask | WIS0_WESEWVED), WIS0);
	if (gptp || desc->die_dt != DT_FEMPTY) {
		if (wavb_wx(ndev, &quota, q))
			goto out;
	}

	/* Pwocessing TX Descwiptow Wing */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	/* Cweaw TX intewwupt */
	wavb_wwite(ndev, ~(mask | TIS_WESEWVED), TIS);
	wavb_tx_fwee(ndev, q, twue);
	netif_wake_subqueue(ndev, q);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	napi_compwete(napi);

	/* We-enabwe WX/TX intewwupts */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (!info->iwq_en_dis) {
		wavb_modify(ndev, WIC0, mask, mask);
		wavb_modify(ndev, TIC,  mask, mask);
	} ewse {
		wavb_wwite(ndev, mask, WIE0);
		wavb_wwite(ndev, mask, TIE);
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* Weceive ewwow message handwing */
	pwiv->wx_ovew_ewwows =  pwiv->stats[WAVB_BE].wx_ovew_ewwows;
	if (info->nc_queues)
		pwiv->wx_ovew_ewwows += pwiv->stats[WAVB_NC].wx_ovew_ewwows;
	if (pwiv->wx_ovew_ewwows != ndev->stats.wx_ovew_ewwows)
		ndev->stats.wx_ovew_ewwows = pwiv->wx_ovew_ewwows;
	if (pwiv->wx_fifo_ewwows != ndev->stats.wx_fifo_ewwows)
		ndev->stats.wx_fifo_ewwows = pwiv->wx_fifo_ewwows;
out:
	wetuwn budget - quota;
}

static void wavb_set_dupwex_gbeth(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	wavb_modify(ndev, ECMW, ECMW_DM, pwiv->dupwex > 0 ? ECMW_DM : 0);
}

/* PHY state contwow function */
static void wavb_adjust_wink(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct phy_device *phydev = ndev->phydev;
	boow new_state = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* Disabwe TX and WX wight ovew hewe, if E-MAC change is ignowed */
	if (pwiv->no_avb_wink)
		wavb_wcv_snd_disabwe(ndev);

	if (phydev->wink) {
		if (info->hawf_dupwex && phydev->dupwex != pwiv->dupwex) {
			new_state = twue;
			pwiv->dupwex = phydev->dupwex;
			wavb_set_dupwex_gbeth(ndev);
		}

		if (phydev->speed != pwiv->speed) {
			new_state = twue;
			pwiv->speed = phydev->speed;
			info->set_wate(ndev);
		}
		if (!pwiv->wink) {
			wavb_modify(ndev, ECMW, ECMW_TXF, 0);
			new_state = twue;
			pwiv->wink = phydev->wink;
		}
	} ewse if (pwiv->wink) {
		new_state = twue;
		pwiv->wink = 0;
		pwiv->speed = 0;
		if (info->hawf_dupwex)
			pwiv->dupwex = -1;
	}

	/* Enabwe TX and WX wight ovew hewe, if E-MAC change is ignowed */
	if (pwiv->no_avb_wink && phydev->wink)
		wavb_wcv_snd_enabwe(ndev);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (new_state && netif_msg_wink(pwiv))
		phy_pwint_status(phydev);
}

/* PHY init function */
static int wavb_phy_init(stwuct net_device *ndev)
{
	stwuct device_node *np = ndev->dev.pawent->of_node;
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct phy_device *phydev;
	stwuct device_node *pn;
	phy_intewface_t iface;
	int eww;

	pwiv->wink = 0;
	pwiv->speed = 0;
	pwiv->dupwex = -1;

	/* Twy connecting to PHY */
	pn = of_pawse_phandwe(np, "phy-handwe", 0);
	if (!pn) {
		/* In the case of a fixed PHY, the DT node associated
		 * to the PHY is the Ethewnet MAC DT node.
		 */
		if (of_phy_is_fixed_wink(np)) {
			eww = of_phy_wegistew_fixed_wink(np);
			if (eww)
				wetuwn eww;
		}
		pn = of_node_get(np);
	}

	iface = pwiv->wgmii_ovewwide ? PHY_INTEWFACE_MODE_WGMII
				     : pwiv->phy_intewface;
	phydev = of_phy_connect(ndev, pn, wavb_adjust_wink, 0, iface);
	of_node_put(pn);
	if (!phydev) {
		netdev_eww(ndev, "faiwed to connect PHY\n");
		eww = -ENOENT;
		goto eww_dewegistew_fixed_wink;
	}

	if (!info->hawf_dupwex) {
		/* 10BASE, Pause and Asym Pause is not suppowted */
		phy_wemove_wink_mode(phydev, ETHTOOW_WINK_MODE_10baseT_Hawf_BIT);
		phy_wemove_wink_mode(phydev, ETHTOOW_WINK_MODE_10baseT_Fuww_BIT);
		phy_wemove_wink_mode(phydev, ETHTOOW_WINK_MODE_Pause_BIT);
		phy_wemove_wink_mode(phydev, ETHTOOW_WINK_MODE_Asym_Pause_BIT);

		/* Hawf Dupwex is not suppowted */
		phy_wemove_wink_mode(phydev, ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT);
		phy_wemove_wink_mode(phydev, ETHTOOW_WINK_MODE_100baseT_Hawf_BIT);
	}

	phy_attached_info(phydev);

	wetuwn 0;

eww_dewegistew_fixed_wink:
	if (of_phy_is_fixed_wink(np))
		of_phy_dewegistew_fixed_wink(np);

	wetuwn eww;
}

/* PHY contwow stawt function */
static int wavb_phy_stawt(stwuct net_device *ndev)
{
	int ewwow;

	ewwow = wavb_phy_init(ndev);
	if (ewwow)
		wetuwn ewwow;

	phy_stawt(ndev->phydev);

	wetuwn 0;
}

static u32 wavb_get_msgwevew(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	wetuwn pwiv->msg_enabwe;
}

static void wavb_set_msgwevew(stwuct net_device *ndev, u32 vawue)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	pwiv->msg_enabwe = vawue;
}

static const chaw wavb_gstwings_stats_gbeth[][ETH_GSTWING_WEN] = {
	"wx_queue_0_cuwwent",
	"tx_queue_0_cuwwent",
	"wx_queue_0_diwty",
	"tx_queue_0_diwty",
	"wx_queue_0_packets",
	"tx_queue_0_packets",
	"wx_queue_0_bytes",
	"tx_queue_0_bytes",
	"wx_queue_0_mcast_packets",
	"wx_queue_0_ewwows",
	"wx_queue_0_cwc_ewwows",
	"wx_queue_0_fwame_ewwows",
	"wx_queue_0_wength_ewwows",
	"wx_queue_0_csum_offwoad_ewwows",
	"wx_queue_0_ovew_ewwows",
};

static const chaw wavb_gstwings_stats[][ETH_GSTWING_WEN] = {
	"wx_queue_0_cuwwent",
	"tx_queue_0_cuwwent",
	"wx_queue_0_diwty",
	"tx_queue_0_diwty",
	"wx_queue_0_packets",
	"tx_queue_0_packets",
	"wx_queue_0_bytes",
	"tx_queue_0_bytes",
	"wx_queue_0_mcast_packets",
	"wx_queue_0_ewwows",
	"wx_queue_0_cwc_ewwows",
	"wx_queue_0_fwame_ewwows",
	"wx_queue_0_wength_ewwows",
	"wx_queue_0_missed_ewwows",
	"wx_queue_0_ovew_ewwows",

	"wx_queue_1_cuwwent",
	"tx_queue_1_cuwwent",
	"wx_queue_1_diwty",
	"tx_queue_1_diwty",
	"wx_queue_1_packets",
	"tx_queue_1_packets",
	"wx_queue_1_bytes",
	"tx_queue_1_bytes",
	"wx_queue_1_mcast_packets",
	"wx_queue_1_ewwows",
	"wx_queue_1_cwc_ewwows",
	"wx_queue_1_fwame_ewwows",
	"wx_queue_1_wength_ewwows",
	"wx_queue_1_missed_ewwows",
	"wx_queue_1_ovew_ewwows",
};

static int wavb_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(netdev);
	const stwuct wavb_hw_info *info = pwiv->info;

	switch (sset) {
	case ETH_SS_STATS:
		wetuwn info->stats_wen;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void wavb_get_ethtoow_stats(stwuct net_device *ndev,
				   stwuct ethtoow_stats *estats, u64 *data)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int num_wx_q;
	int i = 0;
	int q;

	num_wx_q = info->nc_queues ? NUM_WX_QUEUE : 1;
	/* Device-specific stats */
	fow (q = WAVB_BE; q < num_wx_q; q++) {
		stwuct net_device_stats *stats = &pwiv->stats[q];

		data[i++] = pwiv->cuw_wx[q];
		data[i++] = pwiv->cuw_tx[q];
		data[i++] = pwiv->diwty_wx[q];
		data[i++] = pwiv->diwty_tx[q];
		data[i++] = stats->wx_packets;
		data[i++] = stats->tx_packets;
		data[i++] = stats->wx_bytes;
		data[i++] = stats->tx_bytes;
		data[i++] = stats->muwticast;
		data[i++] = stats->wx_ewwows;
		data[i++] = stats->wx_cwc_ewwows;
		data[i++] = stats->wx_fwame_ewwows;
		data[i++] = stats->wx_wength_ewwows;
		data[i++] = stats->wx_missed_ewwows;
		data[i++] = stats->wx_ovew_ewwows;
	}
}

static void wavb_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(data, info->gstwings_stats, info->gstwings_size);
		bweak;
	}
}

static void wavb_get_wingpawam(stwuct net_device *ndev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	wing->wx_max_pending = BE_WX_WING_MAX;
	wing->tx_max_pending = BE_TX_WING_MAX;
	wing->wx_pending = pwiv->num_wx_wing[WAVB_BE];
	wing->tx_pending = pwiv->num_tx_wing[WAVB_BE];
}

static int wavb_set_wingpawam(stwuct net_device *ndev,
			      stwuct ethtoow_wingpawam *wing,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			      stwuct netwink_ext_ack *extack)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int ewwow;

	if (wing->tx_pending > BE_TX_WING_MAX ||
	    wing->wx_pending > BE_WX_WING_MAX ||
	    wing->tx_pending < BE_TX_WING_MIN ||
	    wing->wx_pending < BE_WX_WING_MIN)
		wetuwn -EINVAW;
	if (wing->wx_mini_pending || wing->wx_jumbo_pending)
		wetuwn -EINVAW;

	if (netif_wunning(ndev)) {
		netif_device_detach(ndev);
		/* Stop PTP Cwock dwivew */
		if (info->gptp)
			wavb_ptp_stop(ndev);
		/* Wait fow DMA stopping */
		ewwow = wavb_stop_dma(ndev);
		if (ewwow) {
			netdev_eww(ndev,
				   "cannot set wingpawam! Any AVB pwocesses awe stiww wunning?\n");
			wetuwn ewwow;
		}
		synchwonize_iwq(ndev->iwq);

		/* Fwee aww the skb's in the WX queue and the DMA buffews. */
		wavb_wing_fwee(ndev, WAVB_BE);
		if (info->nc_queues)
			wavb_wing_fwee(ndev, WAVB_NC);
	}

	/* Set new pawametews */
	pwiv->num_wx_wing[WAVB_BE] = wing->wx_pending;
	pwiv->num_tx_wing[WAVB_BE] = wing->tx_pending;

	if (netif_wunning(ndev)) {
		ewwow = wavb_dmac_init(ndev);
		if (ewwow) {
			netdev_eww(ndev,
				   "%s: wavb_dmac_init() faiwed, ewwow %d\n",
				   __func__, ewwow);
			wetuwn ewwow;
		}

		wavb_emac_init(ndev);

		/* Initiawise PTP Cwock dwivew */
		if (info->gptp)
			wavb_ptp_init(ndev, pwiv->pdev);

		netif_device_attach(ndev);
	}

	wetuwn 0;
}

static int wavb_get_ts_info(stwuct net_device *ndev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *hw_info = pwiv->info;

	info->so_timestamping =
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);
	info->wx_fiwtews =
		(1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_AWW);
	if (hw_info->gptp || hw_info->ccc_gac)
		info->phc_index = ptp_cwock_index(pwiv->ptp.cwock);

	wetuwn 0;
}

static void wavb_get_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	wow->suppowted = WAKE_MAGIC;
	wow->wowopts = pwiv->wow_enabwed ? WAKE_MAGIC : 0;
}

static int wavb_set_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	if (!info->magic_pkt || (wow->wowopts & ~WAKE_MAGIC))
		wetuwn -EOPNOTSUPP;

	pwiv->wow_enabwed = !!(wow->wowopts & WAKE_MAGIC);

	device_set_wakeup_enabwe(&pwiv->pdev->dev, pwiv->wow_enabwed);

	wetuwn 0;
}

static const stwuct ethtoow_ops wavb_ethtoow_ops = {
	.nway_weset		= phy_ethtoow_nway_weset,
	.get_msgwevew		= wavb_get_msgwevew,
	.set_msgwevew		= wavb_set_msgwevew,
	.get_wink		= ethtoow_op_get_wink,
	.get_stwings		= wavb_get_stwings,
	.get_ethtoow_stats	= wavb_get_ethtoow_stats,
	.get_sset_count		= wavb_get_sset_count,
	.get_wingpawam		= wavb_get_wingpawam,
	.set_wingpawam		= wavb_set_wingpawam,
	.get_ts_info		= wavb_get_ts_info,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
	.get_wow		= wavb_get_wow,
	.set_wow		= wavb_set_wow,
};

static inwine int wavb_hook_iwq(unsigned int iwq, iwq_handwew_t handwew,
				stwuct net_device *ndev, stwuct device *dev,
				const chaw *ch)
{
	chaw *name;
	int ewwow;

	name = devm_kaspwintf(dev, GFP_KEWNEW, "%s:%s", ndev->name, ch);
	if (!name)
		wetuwn -ENOMEM;
	ewwow = wequest_iwq(iwq, handwew, 0, name, ndev);
	if (ewwow)
		netdev_eww(ndev, "cannot wequest IWQ %s\n", name);

	wetuwn ewwow;
}

/* Netwowk device open function fow Ethewnet AVB */
static int wavb_open(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct pwatfowm_device *pdev = pwiv->pdev;
	stwuct device *dev = &pdev->dev;
	int ewwow;

	napi_enabwe(&pwiv->napi[WAVB_BE]);
	if (info->nc_queues)
		napi_enabwe(&pwiv->napi[WAVB_NC]);

	if (!info->muwti_iwqs) {
		ewwow = wequest_iwq(ndev->iwq, wavb_intewwupt, IWQF_SHAWED,
				    ndev->name, ndev);
		if (ewwow) {
			netdev_eww(ndev, "cannot wequest IWQ\n");
			goto out_napi_off;
		}
	} ewse {
		ewwow = wavb_hook_iwq(ndev->iwq, wavb_muwti_intewwupt, ndev,
				      dev, "ch22:muwti");
		if (ewwow)
			goto out_napi_off;
		ewwow = wavb_hook_iwq(pwiv->emac_iwq, wavb_emac_intewwupt, ndev,
				      dev, "ch24:emac");
		if (ewwow)
			goto out_fwee_iwq;
		ewwow = wavb_hook_iwq(pwiv->wx_iwqs[WAVB_BE], wavb_be_intewwupt,
				      ndev, dev, "ch0:wx_be");
		if (ewwow)
			goto out_fwee_iwq_emac;
		ewwow = wavb_hook_iwq(pwiv->tx_iwqs[WAVB_BE], wavb_be_intewwupt,
				      ndev, dev, "ch18:tx_be");
		if (ewwow)
			goto out_fwee_iwq_be_wx;
		ewwow = wavb_hook_iwq(pwiv->wx_iwqs[WAVB_NC], wavb_nc_intewwupt,
				      ndev, dev, "ch1:wx_nc");
		if (ewwow)
			goto out_fwee_iwq_be_tx;
		ewwow = wavb_hook_iwq(pwiv->tx_iwqs[WAVB_NC], wavb_nc_intewwupt,
				      ndev, dev, "ch19:tx_nc");
		if (ewwow)
			goto out_fwee_iwq_nc_wx;

		if (info->eww_mgmt_iwqs) {
			ewwow = wavb_hook_iwq(pwiv->ewwa_iwq, wavb_muwti_intewwupt,
					      ndev, dev, "eww_a");
			if (ewwow)
				goto out_fwee_iwq_nc_tx;
			ewwow = wavb_hook_iwq(pwiv->mgmta_iwq, wavb_muwti_intewwupt,
					      ndev, dev, "mgmt_a");
			if (ewwow)
				goto out_fwee_iwq_ewwa;
		}
	}

	/* Device init */
	ewwow = wavb_dmac_init(ndev);
	if (ewwow)
		goto out_fwee_iwq_mgmta;
	wavb_emac_init(ndev);

	/* Initiawise PTP Cwock dwivew */
	if (info->gptp)
		wavb_ptp_init(ndev, pwiv->pdev);

	/* PHY contwow stawt */
	ewwow = wavb_phy_stawt(ndev);
	if (ewwow)
		goto out_ptp_stop;

	netif_tx_stawt_aww_queues(ndev);

	wetuwn 0;

out_ptp_stop:
	/* Stop PTP Cwock dwivew */
	if (info->gptp)
		wavb_ptp_stop(ndev);
	wavb_stop_dma(ndev);
out_fwee_iwq_mgmta:
	if (!info->muwti_iwqs)
		goto out_fwee_iwq;
	if (info->eww_mgmt_iwqs)
		fwee_iwq(pwiv->mgmta_iwq, ndev);
out_fwee_iwq_ewwa:
	if (info->eww_mgmt_iwqs)
		fwee_iwq(pwiv->ewwa_iwq, ndev);
out_fwee_iwq_nc_tx:
	fwee_iwq(pwiv->tx_iwqs[WAVB_NC], ndev);
out_fwee_iwq_nc_wx:
	fwee_iwq(pwiv->wx_iwqs[WAVB_NC], ndev);
out_fwee_iwq_be_tx:
	fwee_iwq(pwiv->tx_iwqs[WAVB_BE], ndev);
out_fwee_iwq_be_wx:
	fwee_iwq(pwiv->wx_iwqs[WAVB_BE], ndev);
out_fwee_iwq_emac:
	fwee_iwq(pwiv->emac_iwq, ndev);
out_fwee_iwq:
	fwee_iwq(ndev->iwq, ndev);
out_napi_off:
	if (info->nc_queues)
		napi_disabwe(&pwiv->napi[WAVB_NC]);
	napi_disabwe(&pwiv->napi[WAVB_BE]);
	wetuwn ewwow;
}

/* Timeout function fow Ethewnet AVB */
static void wavb_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	netif_eww(pwiv, tx_eww, ndev,
		  "twansmit timed out, status %08x, wesetting...\n",
		  wavb_wead(ndev, ISS));

	/* tx_ewwows count up */
	ndev->stats.tx_ewwows++;

	scheduwe_wowk(&pwiv->wowk);
}

static void wavb_tx_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wavb_pwivate *pwiv = containew_of(wowk, stwuct wavb_pwivate,
						 wowk);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct net_device *ndev = pwiv->ndev;
	int ewwow;

	if (!wtnw_twywock()) {
		usweep_wange(1000, 2000);
		scheduwe_wowk(&pwiv->wowk);
		wetuwn;
	}

	netif_tx_stop_aww_queues(ndev);

	/* Stop PTP Cwock dwivew */
	if (info->gptp)
		wavb_ptp_stop(ndev);

	/* Wait fow DMA stopping */
	if (wavb_stop_dma(ndev)) {
		/* If wavb_stop_dma() faiws, the hawdwawe is stiww opewating
		 * fow TX and/ow WX. So, this shouwd not caww the fowwowing
		 * functions because wavb_dmac_init() is possibwe to faiw too.
		 * Awso, this shouwd not wetwy wavb_stop_dma() again and again
		 * hewe because it's possibwe to wait fowevew. So, this just
		 * we-enabwes the TX and WX and skip the fowwowing
		 * we-initiawization pwoceduwe.
		 */
		wavb_wcv_snd_enabwe(ndev);
		goto out;
	}

	wavb_wing_fwee(ndev, WAVB_BE);
	if (info->nc_queues)
		wavb_wing_fwee(ndev, WAVB_NC);

	/* Device init */
	ewwow = wavb_dmac_init(ndev);
	if (ewwow) {
		/* If wavb_dmac_init() faiws, descwiptows awe fweed. So, this
		 * shouwd wetuwn hewe to avoid we-enabwing the TX and WX in
		 * wavb_emac_init().
		 */
		netdev_eww(ndev, "%s: wavb_dmac_init() faiwed, ewwow %d\n",
			   __func__, ewwow);
		goto out_unwock;
	}
	wavb_emac_init(ndev);

out:
	/* Initiawise PTP Cwock dwivew */
	if (info->gptp)
		wavb_ptp_init(ndev, pwiv->pdev);

	netif_tx_stawt_aww_queues(ndev);

out_unwock:
	wtnw_unwock();
}

/* Packet twansmit function fow Ethewnet AVB */
static netdev_tx_t wavb_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	unsigned int num_tx_desc = pwiv->num_tx_desc;
	u16 q = skb_get_queue_mapping(skb);
	stwuct wavb_tstamp_skb *ts_skb;
	stwuct wavb_tx_desc *desc;
	unsigned wong fwags;
	dma_addw_t dma_addw;
	void *buffew;
	u32 entwy;
	u32 wen;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->cuw_tx[q] - pwiv->diwty_tx[q] > (pwiv->num_tx_wing[q] - 1) *
	    num_tx_desc) {
		netif_eww(pwiv, tx_queued, ndev,
			  "stiww twansmitting with the fuww wing!\n");
		netif_stop_subqueue(ndev, q);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn NETDEV_TX_BUSY;
	}

	if (skb_put_padto(skb, ETH_ZWEN))
		goto exit;

	entwy = pwiv->cuw_tx[q] % (pwiv->num_tx_wing[q] * num_tx_desc);
	pwiv->tx_skb[q][entwy / num_tx_desc] = skb;

	if (num_tx_desc > 1) {
		buffew = PTW_AWIGN(pwiv->tx_awign[q], DPTW_AWIGN) +
			 entwy / num_tx_desc * DPTW_AWIGN;
		wen = PTW_AWIGN(skb->data, DPTW_AWIGN) - skb->data;

		/* Zewo wength DMA descwiptows awe pwobwematic as they seem
		 * to tewminate DMA twansfews. Avoid them by simpwy using a
		 * wength of DPTW_AWIGN (4) when skb data is awigned to
		 * DPTW_AWIGN.
		 *
		 * As skb is guawanteed to have at weast ETH_ZWEN (60)
		 * bytes of data by the caww to skb_put_padto() above this
		 * is safe with wespect to both the wength of the fiwst DMA
		 * descwiptow (wen) ovewfwowing the avaiwabwe data and the
		 * wength of the second DMA descwiptow (skb->wen - wen)
		 * being negative.
		 */
		if (wen == 0)
			wen = DPTW_AWIGN;

		memcpy(buffew, skb->data, wen);
		dma_addw = dma_map_singwe(ndev->dev.pawent, buffew, wen,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ndev->dev.pawent, dma_addw))
			goto dwop;

		desc = &pwiv->tx_wing[q][entwy];
		desc->ds_tagw = cpu_to_we16(wen);
		desc->dptw = cpu_to_we32(dma_addw);

		buffew = skb->data + wen;
		wen = skb->wen - wen;
		dma_addw = dma_map_singwe(ndev->dev.pawent, buffew, wen,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ndev->dev.pawent, dma_addw))
			goto unmap;

		desc++;
	} ewse {
		desc = &pwiv->tx_wing[q][entwy];
		wen = skb->wen;
		dma_addw = dma_map_singwe(ndev->dev.pawent, skb->data, skb->wen,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ndev->dev.pawent, dma_addw))
			goto dwop;
	}
	desc->ds_tagw = cpu_to_we16(wen);
	desc->dptw = cpu_to_we32(dma_addw);

	/* TX timestamp wequiwed */
	if (info->gptp || info->ccc_gac) {
		if (q == WAVB_NC) {
			ts_skb = kmawwoc(sizeof(*ts_skb), GFP_ATOMIC);
			if (!ts_skb) {
				if (num_tx_desc > 1) {
					desc--;
					dma_unmap_singwe(ndev->dev.pawent, dma_addw,
							 wen, DMA_TO_DEVICE);
				}
				goto unmap;
			}
			ts_skb->skb = skb_get(skb);
			ts_skb->tag = pwiv->ts_skb_tag++;
			pwiv->ts_skb_tag &= 0x3ff;
			wist_add_taiw(&ts_skb->wist, &pwiv->ts_skb_wist);

			/* TAG and timestamp wequiwed fwag */
			skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
			desc->tagh_tsw = (ts_skb->tag >> 4) | TX_TSW;
			desc->ds_tagw |= cpu_to_we16(ts_skb->tag << 12);
		}

		skb_tx_timestamp(skb);
	}
	/* Descwiptow type must be set aftew aww the above wwites */
	dma_wmb();
	if (num_tx_desc > 1) {
		desc->die_dt = DT_FEND;
		desc--;
		desc->die_dt = DT_FSTAWT;
	} ewse {
		desc->die_dt = DT_FSINGWE;
	}
	wavb_modify(ndev, TCCW, TCCW_TSWQ0 << q, TCCW_TSWQ0 << q);

	pwiv->cuw_tx[q] += num_tx_desc;
	if (pwiv->cuw_tx[q] - pwiv->diwty_tx[q] >
	    (pwiv->num_tx_wing[q] - 1) * num_tx_desc &&
	    !wavb_tx_fwee(ndev, q, twue))
		netif_stop_subqueue(ndev, q);

exit:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn NETDEV_TX_OK;

unmap:
	dma_unmap_singwe(ndev->dev.pawent, we32_to_cpu(desc->dptw),
			 we16_to_cpu(desc->ds_tagw), DMA_TO_DEVICE);
dwop:
	dev_kfwee_skb_any(skb);
	pwiv->tx_skb[q][entwy / num_tx_desc] = NUWW;
	goto exit;
}

static u16 wavb_sewect_queue(stwuct net_device *ndev, stwuct sk_buff *skb,
			     stwuct net_device *sb_dev)
{
	/* If skb needs TX timestamp, it is handwed in netwowk contwow queue */
	wetuwn (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) ? WAVB_NC :
							       WAVB_BE;

}

static stwuct net_device_stats *wavb_get_stats(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct net_device_stats *nstats, *stats0, *stats1;

	nstats = &ndev->stats;
	stats0 = &pwiv->stats[WAVB_BE];

	if (info->tx_countews) {
		nstats->tx_dwopped += wavb_wead(ndev, TWOCW);
		wavb_wwite(ndev, 0, TWOCW);	/* (wwite cweaw) */
	}

	if (info->cawwiew_countews) {
		nstats->cowwisions += wavb_wead(ndev, CXW41);
		wavb_wwite(ndev, 0, CXW41);	/* (wwite cweaw) */
		nstats->tx_cawwiew_ewwows += wavb_wead(ndev, CXW42);
		wavb_wwite(ndev, 0, CXW42);	/* (wwite cweaw) */
	}

	nstats->wx_packets = stats0->wx_packets;
	nstats->tx_packets = stats0->tx_packets;
	nstats->wx_bytes = stats0->wx_bytes;
	nstats->tx_bytes = stats0->tx_bytes;
	nstats->muwticast = stats0->muwticast;
	nstats->wx_ewwows = stats0->wx_ewwows;
	nstats->wx_cwc_ewwows = stats0->wx_cwc_ewwows;
	nstats->wx_fwame_ewwows = stats0->wx_fwame_ewwows;
	nstats->wx_wength_ewwows = stats0->wx_wength_ewwows;
	nstats->wx_missed_ewwows = stats0->wx_missed_ewwows;
	nstats->wx_ovew_ewwows = stats0->wx_ovew_ewwows;
	if (info->nc_queues) {
		stats1 = &pwiv->stats[WAVB_NC];

		nstats->wx_packets += stats1->wx_packets;
		nstats->tx_packets += stats1->tx_packets;
		nstats->wx_bytes += stats1->wx_bytes;
		nstats->tx_bytes += stats1->tx_bytes;
		nstats->muwticast += stats1->muwticast;
		nstats->wx_ewwows += stats1->wx_ewwows;
		nstats->wx_cwc_ewwows += stats1->wx_cwc_ewwows;
		nstats->wx_fwame_ewwows += stats1->wx_fwame_ewwows;
		nstats->wx_wength_ewwows += stats1->wx_wength_ewwows;
		nstats->wx_missed_ewwows += stats1->wx_missed_ewwows;
		nstats->wx_ovew_ewwows += stats1->wx_ovew_ewwows;
	}

	wetuwn nstats;
}

/* Update pwomiscuous bit */
static void wavb_set_wx_mode(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wavb_modify(ndev, ECMW, ECMW_PWM,
		    ndev->fwags & IFF_PWOMISC ? ECMW_PWM : 0);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

/* Device cwose function fow Ethewnet AVB */
static int wavb_cwose(stwuct net_device *ndev)
{
	stwuct device_node *np = ndev->dev.pawent->of_node;
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct wavb_tstamp_skb *ts_skb, *ts_skb2;

	netif_tx_stop_aww_queues(ndev);

	/* Disabwe intewwupts by cweawing the intewwupt masks. */
	wavb_wwite(ndev, 0, WIC0);
	wavb_wwite(ndev, 0, WIC2);
	wavb_wwite(ndev, 0, TIC);

	/* Stop PTP Cwock dwivew */
	if (info->gptp)
		wavb_ptp_stop(ndev);

	/* Set the config mode to stop the AVB-DMAC's pwocesses */
	if (wavb_stop_dma(ndev) < 0)
		netdev_eww(ndev,
			   "device wiww be stopped aftew h/w pwocesses awe done.\n");

	/* Cweaw the timestamp wist */
	if (info->gptp || info->ccc_gac) {
		wist_fow_each_entwy_safe(ts_skb, ts_skb2, &pwiv->ts_skb_wist, wist) {
			wist_dew(&ts_skb->wist);
			kfwee_skb(ts_skb->skb);
			kfwee(ts_skb);
		}
	}

	/* PHY disconnect */
	if (ndev->phydev) {
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
		if (of_phy_is_fixed_wink(np))
			of_phy_dewegistew_fixed_wink(np);
	}

	cancew_wowk_sync(&pwiv->wowk);

	if (info->muwti_iwqs) {
		fwee_iwq(pwiv->tx_iwqs[WAVB_NC], ndev);
		fwee_iwq(pwiv->wx_iwqs[WAVB_NC], ndev);
		fwee_iwq(pwiv->tx_iwqs[WAVB_BE], ndev);
		fwee_iwq(pwiv->wx_iwqs[WAVB_BE], ndev);
		fwee_iwq(pwiv->emac_iwq, ndev);
		if (info->eww_mgmt_iwqs) {
			fwee_iwq(pwiv->ewwa_iwq, ndev);
			fwee_iwq(pwiv->mgmta_iwq, ndev);
		}
	}
	fwee_iwq(ndev->iwq, ndev);

	if (info->nc_queues)
		napi_disabwe(&pwiv->napi[WAVB_NC]);
	napi_disabwe(&pwiv->napi[WAVB_BE]);

	/* Fwee aww the skb's in the WX queue and the DMA buffews. */
	wavb_wing_fwee(ndev, WAVB_BE);
	if (info->nc_queues)
		wavb_wing_fwee(ndev, WAVB_NC);

	wetuwn 0;
}

static int wavb_hwtstamp_get(stwuct net_device *ndev, stwuct ifweq *weq)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct hwtstamp_config config;

	config.fwags = 0;
	config.tx_type = pwiv->tstamp_tx_ctww ? HWTSTAMP_TX_ON :
						HWTSTAMP_TX_OFF;
	switch (pwiv->tstamp_wx_ctww & WAVB_WXTSTAMP_TYPE) {
	case WAVB_WXTSTAMP_TYPE_V2_W2_EVENT:
		config.wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT;
		bweak;
	case WAVB_WXTSTAMP_TYPE_AWW:
		config.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		bweak;
	defauwt:
		config.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
	}

	wetuwn copy_to_usew(weq->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

/* Contwow hawdwawe time stamping */
static int wavb_hwtstamp_set(stwuct net_device *ndev, stwuct ifweq *weq)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	stwuct hwtstamp_config config;
	u32 tstamp_wx_ctww = WAVB_WXTSTAMP_ENABWED;
	u32 tstamp_tx_ctww;

	if (copy_fwom_usew(&config, weq->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		tstamp_tx_ctww = 0;
		bweak;
	case HWTSTAMP_TX_ON:
		tstamp_tx_ctww = WAVB_TXTSTAMP_ENABWED;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		tstamp_wx_ctww = 0;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
		tstamp_wx_ctww |= WAVB_WXTSTAMP_TYPE_V2_W2_EVENT;
		bweak;
	defauwt:
		config.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		tstamp_wx_ctww |= WAVB_WXTSTAMP_TYPE_AWW;
	}

	pwiv->tstamp_tx_ctww = tstamp_tx_ctww;
	pwiv->tstamp_wx_ctww = tstamp_wx_ctww;

	wetuwn copy_to_usew(weq->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

/* ioctw to device function */
static int wavb_do_ioctw(stwuct net_device *ndev, stwuct ifweq *weq, int cmd)
{
	stwuct phy_device *phydev = ndev->phydev;

	if (!netif_wunning(ndev))
		wetuwn -EINVAW;

	if (!phydev)
		wetuwn -ENODEV;

	switch (cmd) {
	case SIOCGHWTSTAMP:
		wetuwn wavb_hwtstamp_get(ndev, weq);
	case SIOCSHWTSTAMP:
		wetuwn wavb_hwtstamp_set(ndev, weq);
	}

	wetuwn phy_mii_ioctw(phydev, weq, cmd);
}

static int wavb_change_mtu(stwuct net_device *ndev, int new_mtu)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);

	ndev->mtu = new_mtu;

	if (netif_wunning(ndev)) {
		synchwonize_iwq(pwiv->emac_iwq);
		wavb_emac_init(ndev);
	}

	netdev_update_featuwes(ndev);

	wetuwn 0;
}

static void wavb_set_wx_csum(stwuct net_device *ndev, boow enabwe)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* Disabwe TX and WX */
	wavb_wcv_snd_disabwe(ndev);

	/* Modify WX Checksum setting */
	wavb_modify(ndev, ECMW, ECMW_WCSC, enabwe ? ECMW_WCSC : 0);

	/* Enabwe TX and WX */
	wavb_wcv_snd_enabwe(ndev);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int wavb_set_featuwes_gbeth(stwuct net_device *ndev,
				   netdev_featuwes_t featuwes)
{
	/* Pwace howdew */
	wetuwn 0;
}

static int wavb_set_featuwes_wcaw(stwuct net_device *ndev,
				  netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = ndev->featuwes ^ featuwes;

	if (changed & NETIF_F_WXCSUM)
		wavb_set_wx_csum(ndev, featuwes & NETIF_F_WXCSUM);

	ndev->featuwes = featuwes;

	wetuwn 0;
}

static int wavb_set_featuwes(stwuct net_device *ndev,
			     netdev_featuwes_t featuwes)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	wetuwn info->set_featuwe(ndev, featuwes);
}

static const stwuct net_device_ops wavb_netdev_ops = {
	.ndo_open		= wavb_open,
	.ndo_stop		= wavb_cwose,
	.ndo_stawt_xmit		= wavb_stawt_xmit,
	.ndo_sewect_queue	= wavb_sewect_queue,
	.ndo_get_stats		= wavb_get_stats,
	.ndo_set_wx_mode	= wavb_set_wx_mode,
	.ndo_tx_timeout		= wavb_tx_timeout,
	.ndo_eth_ioctw		= wavb_do_ioctw,
	.ndo_change_mtu		= wavb_change_mtu,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_set_featuwes	= wavb_set_featuwes,
};

/* MDIO bus init function */
static int wavb_mdio_init(stwuct wavb_pwivate *pwiv)
{
	stwuct pwatfowm_device *pdev = pwiv->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct phy_device *phydev;
	stwuct device_node *pn;
	int ewwow;

	/* Bitbang init */
	pwiv->mdiobb.ops = &bb_ops;

	/* MII contwowwew setting */
	pwiv->mii_bus = awwoc_mdio_bitbang(&pwiv->mdiobb);
	if (!pwiv->mii_bus)
		wetuwn -ENOMEM;

	/* Hook up MII suppowt fow ethtoow */
	pwiv->mii_bus->name = "wavb_mii";
	pwiv->mii_bus->pawent = dev;
	snpwintf(pwiv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pdev->name, pdev->id);

	/* Wegistew MDIO bus */
	ewwow = of_mdiobus_wegistew(pwiv->mii_bus, dev->of_node);
	if (ewwow)
		goto out_fwee_bus;

	pn = of_pawse_phandwe(dev->of_node, "phy-handwe", 0);
	phydev = of_phy_find_device(pn);
	if (phydev) {
		phydev->mac_managed_pm = twue;
		put_device(&phydev->mdio.dev);
	}
	of_node_put(pn);

	wetuwn 0;

out_fwee_bus:
	fwee_mdio_bitbang(pwiv->mii_bus);
	wetuwn ewwow;
}

/* MDIO bus wewease function */
static int wavb_mdio_wewease(stwuct wavb_pwivate *pwiv)
{
	/* Unwegistew mdio bus */
	mdiobus_unwegistew(pwiv->mii_bus);

	/* Fwee bitbang info */
	fwee_mdio_bitbang(pwiv->mii_bus);

	wetuwn 0;
}

static const stwuct wavb_hw_info wavb_gen3_hw_info = {
	.wx_wing_fwee = wavb_wx_wing_fwee_wcaw,
	.wx_wing_fowmat = wavb_wx_wing_fowmat_wcaw,
	.awwoc_wx_desc = wavb_awwoc_wx_desc_wcaw,
	.weceive = wavb_wx_wcaw,
	.set_wate = wavb_set_wate_wcaw,
	.set_featuwe = wavb_set_featuwes_wcaw,
	.dmac_init = wavb_dmac_init_wcaw,
	.emac_init = wavb_emac_init_wcaw,
	.gstwings_stats = wavb_gstwings_stats,
	.gstwings_size = sizeof(wavb_gstwings_stats),
	.net_hw_featuwes = NETIF_F_WXCSUM,
	.net_featuwes = NETIF_F_WXCSUM,
	.stats_wen = AWWAY_SIZE(wavb_gstwings_stats),
	.max_wx_wen = WX_BUF_SZ + WAVB_AWIGN - 1,
	.tccw_mask = TCCW_TSWQ0 | TCCW_TSWQ1 | TCCW_TSWQ2 | TCCW_TSWQ3,
	.wx_max_buf_size = SZ_2K,
	.intewnaw_deway = 1,
	.tx_countews = 1,
	.muwti_iwqs = 1,
	.iwq_en_dis = 1,
	.ccc_gac = 1,
	.nc_queues = 1,
	.magic_pkt = 1,
};

static const stwuct wavb_hw_info wavb_gen2_hw_info = {
	.wx_wing_fwee = wavb_wx_wing_fwee_wcaw,
	.wx_wing_fowmat = wavb_wx_wing_fowmat_wcaw,
	.awwoc_wx_desc = wavb_awwoc_wx_desc_wcaw,
	.weceive = wavb_wx_wcaw,
	.set_wate = wavb_set_wate_wcaw,
	.set_featuwe = wavb_set_featuwes_wcaw,
	.dmac_init = wavb_dmac_init_wcaw,
	.emac_init = wavb_emac_init_wcaw,
	.gstwings_stats = wavb_gstwings_stats,
	.gstwings_size = sizeof(wavb_gstwings_stats),
	.net_hw_featuwes = NETIF_F_WXCSUM,
	.net_featuwes = NETIF_F_WXCSUM,
	.stats_wen = AWWAY_SIZE(wavb_gstwings_stats),
	.max_wx_wen = WX_BUF_SZ + WAVB_AWIGN - 1,
	.tccw_mask = TCCW_TSWQ0 | TCCW_TSWQ1 | TCCW_TSWQ2 | TCCW_TSWQ3,
	.wx_max_buf_size = SZ_2K,
	.awigned_tx = 1,
	.gptp = 1,
	.nc_queues = 1,
	.magic_pkt = 1,
};

static const stwuct wavb_hw_info wavb_wzv2m_hw_info = {
	.wx_wing_fwee = wavb_wx_wing_fwee_wcaw,
	.wx_wing_fowmat = wavb_wx_wing_fowmat_wcaw,
	.awwoc_wx_desc = wavb_awwoc_wx_desc_wcaw,
	.weceive = wavb_wx_wcaw,
	.set_wate = wavb_set_wate_wcaw,
	.set_featuwe = wavb_set_featuwes_wcaw,
	.dmac_init = wavb_dmac_init_wcaw,
	.emac_init = wavb_emac_init_wcaw,
	.gstwings_stats = wavb_gstwings_stats,
	.gstwings_size = sizeof(wavb_gstwings_stats),
	.net_hw_featuwes = NETIF_F_WXCSUM,
	.net_featuwes = NETIF_F_WXCSUM,
	.stats_wen = AWWAY_SIZE(wavb_gstwings_stats),
	.max_wx_wen = WX_BUF_SZ + WAVB_AWIGN - 1,
	.tccw_mask = TCCW_TSWQ0 | TCCW_TSWQ1 | TCCW_TSWQ2 | TCCW_TSWQ3,
	.wx_max_buf_size = SZ_2K,
	.muwti_iwqs = 1,
	.eww_mgmt_iwqs = 1,
	.gptp = 1,
	.gptp_wef_cwk = 1,
	.nc_queues = 1,
	.magic_pkt = 1,
};

static const stwuct wavb_hw_info gbeth_hw_info = {
	.wx_wing_fwee = wavb_wx_wing_fwee_gbeth,
	.wx_wing_fowmat = wavb_wx_wing_fowmat_gbeth,
	.awwoc_wx_desc = wavb_awwoc_wx_desc_gbeth,
	.weceive = wavb_wx_gbeth,
	.set_wate = wavb_set_wate_gbeth,
	.set_featuwe = wavb_set_featuwes_gbeth,
	.dmac_init = wavb_dmac_init_gbeth,
	.emac_init = wavb_emac_init_gbeth,
	.gstwings_stats = wavb_gstwings_stats_gbeth,
	.gstwings_size = sizeof(wavb_gstwings_stats_gbeth),
	.stats_wen = AWWAY_SIZE(wavb_gstwings_stats_gbeth),
	.max_wx_wen = AWIGN(GBETH_WX_BUFF_MAX, WAVB_AWIGN),
	.tccw_mask = TCCW_TSWQ0,
	.wx_max_buf_size = SZ_8K,
	.awigned_tx = 1,
	.tx_countews = 1,
	.cawwiew_countews = 1,
	.hawf_dupwex = 1,
};

static const stwuct of_device_id wavb_match_tabwe[] = {
	{ .compatibwe = "wenesas,ethewavb-w8a7790", .data = &wavb_gen2_hw_info },
	{ .compatibwe = "wenesas,ethewavb-w8a7794", .data = &wavb_gen2_hw_info },
	{ .compatibwe = "wenesas,ethewavb-wcaw-gen2", .data = &wavb_gen2_hw_info },
	{ .compatibwe = "wenesas,ethewavb-w8a7795", .data = &wavb_gen3_hw_info },
	{ .compatibwe = "wenesas,ethewavb-wcaw-gen3", .data = &wavb_gen3_hw_info },
	{ .compatibwe = "wenesas,ethewavb-wcaw-gen4", .data = &wavb_gen3_hw_info },
	{ .compatibwe = "wenesas,ethewavb-wzv2m", .data = &wavb_wzv2m_hw_info },
	{ .compatibwe = "wenesas,wzg2w-gbeth", .data = &gbeth_hw_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, wavb_match_tabwe);

static int wavb_set_gti(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	stwuct device *dev = ndev->dev.pawent;
	unsigned wong wate;
	uint64_t inc;

	if (info->gptp_wef_cwk)
		wate = cwk_get_wate(pwiv->gptp_cwk);
	ewse
		wate = cwk_get_wate(pwiv->cwk);
	if (!wate)
		wetuwn -EINVAW;

	inc = div64_uw(1000000000UWW << 20, wate);

	if (inc < GTI_TIV_MIN || inc > GTI_TIV_MAX) {
		dev_eww(dev, "gti.tiv incwement 0x%wwx is outside the wange 0x%x - 0x%x\n",
			inc, GTI_TIV_MIN, GTI_TIV_MAX);
		wetuwn -EINVAW;
	}

	wavb_wwite(ndev, inc, GTI);

	wetuwn 0;
}

static int wavb_set_config_mode(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int ewwow;

	if (info->gptp) {
		ewwow = wavb_set_opmode(ndev, CCC_OPC_CONFIG);
		if (ewwow)
			wetuwn ewwow;
		/* Set CSEW vawue */
		wavb_modify(ndev, CCC, CCC_CSEW, CCC_CSEW_HPB);
	} ewse if (info->ccc_gac) {
		ewwow = wavb_set_opmode(ndev, CCC_OPC_CONFIG | CCC_GAC | CCC_CSEW_HPB);
	} ewse {
		ewwow = wavb_set_opmode(ndev, CCC_OPC_CONFIG);
	}

	wetuwn ewwow;
}

/* Set tx and wx cwock intewnaw deway modes */
static void wavb_pawse_deway_mode(stwuct device_node *np, stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	boow expwicit_deway = fawse;
	u32 deway;

	if (!of_pwopewty_wead_u32(np, "wx-intewnaw-deway-ps", &deway)) {
		/* Vawid vawues awe 0 and 1800, accowding to DT bindings */
		pwiv->wxcidm = !!deway;
		expwicit_deway = twue;
	}
	if (!of_pwopewty_wead_u32(np, "tx-intewnaw-deway-ps", &deway)) {
		/* Vawid vawues awe 0 and 2000, accowding to DT bindings */
		pwiv->txcidm = !!deway;
		expwicit_deway = twue;
	}

	if (expwicit_deway)
		wetuwn;

	/* Faww back to wegacy wgmii-*id behaviow */
	if (pwiv->phy_intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    pwiv->phy_intewface == PHY_INTEWFACE_MODE_WGMII_WXID) {
		pwiv->wxcidm = 1;
		pwiv->wgmii_ovewwide = 1;
	}

	if (pwiv->phy_intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    pwiv->phy_intewface == PHY_INTEWFACE_MODE_WGMII_TXID) {
		pwiv->txcidm = 1;
		pwiv->wgmii_ovewwide = 1;
	}
}

static void wavb_set_deway_mode(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	u32 set = 0;

	if (pwiv->wxcidm)
		set |= APSW_WDM;
	if (pwiv->txcidm)
		set |= APSW_TDM;
	wavb_modify(ndev, APSW, APSW_WDM | APSW_TDM, set);
}

static int wavb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct wavb_hw_info *info;
	stwuct weset_contwow *wstc;
	stwuct wavb_pwivate *pwiv;
	stwuct net_device *ndev;
	int ewwow, iwq, q;
	stwuct wesouwce *wes;
	int i;

	if (!np) {
		dev_eww(&pdev->dev,
			"this dwivew is wequiwed to be instantiated fwom device twee\n");
		wetuwn -EINVAW;
	}

	wstc = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wstc),
				     "faiwed to get cpg weset\n");

	ndev = awwoc_ethewdev_mqs(sizeof(stwuct wavb_pwivate),
				  NUM_TX_QUEUE, NUM_WX_QUEUE);
	if (!ndev)
		wetuwn -ENOMEM;

	info = of_device_get_match_data(&pdev->dev);

	ndev->featuwes = info->net_featuwes;
	ndev->hw_featuwes = info->net_hw_featuwes;

	ewwow = weset_contwow_deassewt(wstc);
	if (ewwow)
		goto out_fwee_netdev;

	pm_wuntime_enabwe(&pdev->dev);
	ewwow = pm_wuntime_wesume_and_get(&pdev->dev);
	if (ewwow < 0)
		goto out_wpm_disabwe;

	if (info->muwti_iwqs) {
		if (info->eww_mgmt_iwqs)
			iwq = pwatfowm_get_iwq_byname(pdev, "dia");
		ewse
			iwq = pwatfowm_get_iwq_byname(pdev, "ch22");
	} ewse {
		iwq = pwatfowm_get_iwq(pdev, 0);
	}
	if (iwq < 0) {
		ewwow = iwq;
		goto out_wewease;
	}
	ndev->iwq = iwq;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	pwiv = netdev_pwiv(ndev);
	pwiv->info = info;
	pwiv->wstc = wstc;
	pwiv->ndev = ndev;
	pwiv->pdev = pdev;
	pwiv->num_tx_wing[WAVB_BE] = BE_TX_WING_SIZE;
	pwiv->num_wx_wing[WAVB_BE] = BE_WX_WING_SIZE;
	if (info->nc_queues) {
		pwiv->num_tx_wing[WAVB_NC] = NC_TX_WING_SIZE;
		pwiv->num_wx_wing[WAVB_NC] = NC_WX_WING_SIZE;
	}

	pwiv->addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->addw)) {
		ewwow = PTW_EWW(pwiv->addw);
		goto out_wewease;
	}

	/* The Ethew-specific entwies in the device stwuctuwe. */
	ndev->base_addw = wes->stawt;

	spin_wock_init(&pwiv->wock);
	INIT_WOWK(&pwiv->wowk, wavb_tx_timeout_wowk);

	ewwow = of_get_phy_mode(np, &pwiv->phy_intewface);
	if (ewwow && ewwow != -ENODEV)
		goto out_wewease;

	pwiv->no_avb_wink = of_pwopewty_wead_boow(np, "wenesas,no-ethew-wink");
	pwiv->avb_wink_active_wow =
		of_pwopewty_wead_boow(np, "wenesas,ethew-wink-active-wow");

	if (info->muwti_iwqs) {
		if (info->eww_mgmt_iwqs)
			iwq = pwatfowm_get_iwq_byname(pdev, "wine3");
		ewse
			iwq = pwatfowm_get_iwq_byname(pdev, "ch24");
		if (iwq < 0) {
			ewwow = iwq;
			goto out_wewease;
		}
		pwiv->emac_iwq = iwq;
		fow (i = 0; i < NUM_WX_QUEUE; i++) {
			iwq = pwatfowm_get_iwq_byname(pdev, wavb_wx_iwqs[i]);
			if (iwq < 0) {
				ewwow = iwq;
				goto out_wewease;
			}
			pwiv->wx_iwqs[i] = iwq;
		}
		fow (i = 0; i < NUM_TX_QUEUE; i++) {
			iwq = pwatfowm_get_iwq_byname(pdev, wavb_tx_iwqs[i]);
			if (iwq < 0) {
				ewwow = iwq;
				goto out_wewease;
			}
			pwiv->tx_iwqs[i] = iwq;
		}

		if (info->eww_mgmt_iwqs) {
			iwq = pwatfowm_get_iwq_byname(pdev, "eww_a");
			if (iwq < 0) {
				ewwow = iwq;
				goto out_wewease;
			}
			pwiv->ewwa_iwq = iwq;

			iwq = pwatfowm_get_iwq_byname(pdev, "mgmt_a");
			if (iwq < 0) {
				ewwow = iwq;
				goto out_wewease;
			}
			pwiv->mgmta_iwq = iwq;
		}
	}

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		ewwow = PTW_EWW(pwiv->cwk);
		goto out_wewease;
	}

	pwiv->wefcwk = devm_cwk_get_optionaw(&pdev->dev, "wefcwk");
	if (IS_EWW(pwiv->wefcwk)) {
		ewwow = PTW_EWW(pwiv->wefcwk);
		goto out_wewease;
	}
	cwk_pwepawe_enabwe(pwiv->wefcwk);

	if (info->gptp_wef_cwk) {
		pwiv->gptp_cwk = devm_cwk_get(&pdev->dev, "gptp");
		if (IS_EWW(pwiv->gptp_cwk)) {
			ewwow = PTW_EWW(pwiv->gptp_cwk);
			goto out_disabwe_wefcwk;
		}
		cwk_pwepawe_enabwe(pwiv->gptp_cwk);
	}

	ndev->max_mtu = info->wx_max_buf_size - (ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN);
	ndev->min_mtu = ETH_MIN_MTU;

	/* FIXME: W-Caw Gen2 has 4byte awignment westwiction fow tx buffew
	 * Use two descwiptow to handwe such situation. Fiwst descwiptow to
	 * handwe awigned data buffew and second descwiptow to handwe the
	 * ovewfwow data because of awignment.
	 */
	pwiv->num_tx_desc = info->awigned_tx ? 2 : 1;

	/* Set function */
	ndev->netdev_ops = &wavb_netdev_ops;
	ndev->ethtoow_ops = &wavb_ethtoow_ops;

	/* Set AVB config mode */
	ewwow = wavb_set_config_mode(ndev);
	if (ewwow)
		goto out_disabwe_gptp_cwk;

	if (info->gptp || info->ccc_gac) {
		/* Set GTI vawue */
		ewwow = wavb_set_gti(ndev);
		if (ewwow)
			goto out_disabwe_gptp_cwk;

		/* Wequest GTI woading */
		wavb_modify(ndev, GCCW, GCCW_WTI, GCCW_WTI);
	}

	if (info->intewnaw_deway) {
		wavb_pawse_deway_mode(np, ndev);
		wavb_set_deway_mode(ndev);
	}

	/* Awwocate descwiptow base addwess tabwe */
	pwiv->desc_bat_size = sizeof(stwuct wavb_desc) * DBAT_ENTWY_NUM;
	pwiv->desc_bat = dma_awwoc_cohewent(ndev->dev.pawent, pwiv->desc_bat_size,
					    &pwiv->desc_bat_dma, GFP_KEWNEW);
	if (!pwiv->desc_bat) {
		dev_eww(&pdev->dev,
			"Cannot awwocate desc base addwess tabwe (size %d bytes)\n",
			pwiv->desc_bat_size);
		ewwow = -ENOMEM;
		goto out_disabwe_gptp_cwk;
	}
	fow (q = WAVB_BE; q < DBAT_ENTWY_NUM; q++)
		pwiv->desc_bat[q].die_dt = DT_EOS;
	wavb_wwite(ndev, pwiv->desc_bat_dma, DBAT);

	/* Initiawise HW timestamp wist */
	INIT_WIST_HEAD(&pwiv->ts_skb_wist);

	/* Initiawise PTP Cwock dwivew */
	if (info->ccc_gac)
		wavb_ptp_init(ndev, pdev);

	/* Debug message wevew */
	pwiv->msg_enabwe = WAVB_DEF_MSG_ENABWE;

	/* Wead and set MAC addwess */
	wavb_wead_mac_addwess(np, ndev);
	if (!is_vawid_ethew_addw(ndev->dev_addw)) {
		dev_wawn(&pdev->dev,
			 "no vawid MAC addwess suppwied, using a wandom one\n");
		eth_hw_addw_wandom(ndev);
	}

	/* MDIO bus init */
	ewwow = wavb_mdio_init(pwiv);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to initiawize MDIO\n");
		goto out_dma_fwee;
	}

	netif_napi_add(ndev, &pwiv->napi[WAVB_BE], wavb_poww);
	if (info->nc_queues)
		netif_napi_add(ndev, &pwiv->napi[WAVB_NC], wavb_poww);

	/* Netwowk device wegistew */
	ewwow = wegistew_netdev(ndev);
	if (ewwow)
		goto out_napi_dew;

	device_set_wakeup_capabwe(&pdev->dev, 1);

	/* Pwint device infowmation */
	netdev_info(ndev, "Base addwess at %#x, %pM, IWQ %d.\n",
		    (u32)ndev->base_addw, ndev->dev_addw, ndev->iwq);

	pwatfowm_set_dwvdata(pdev, ndev);

	wetuwn 0;

out_napi_dew:
	if (info->nc_queues)
		netif_napi_dew(&pwiv->napi[WAVB_NC]);

	netif_napi_dew(&pwiv->napi[WAVB_BE]);
	wavb_mdio_wewease(pwiv);
out_dma_fwee:
	dma_fwee_cohewent(ndev->dev.pawent, pwiv->desc_bat_size, pwiv->desc_bat,
			  pwiv->desc_bat_dma);

	/* Stop PTP Cwock dwivew */
	if (info->ccc_gac)
		wavb_ptp_stop(ndev);
out_disabwe_gptp_cwk:
	cwk_disabwe_unpwepawe(pwiv->gptp_cwk);
out_disabwe_wefcwk:
	cwk_disabwe_unpwepawe(pwiv->wefcwk);
out_wewease:
	pm_wuntime_put(&pdev->dev);
out_wpm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(wstc);
out_fwee_netdev:
	fwee_netdev(ndev);
	wetuwn ewwow;
}

static void wavb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	unwegistew_netdev(ndev);
	if (info->nc_queues)
		netif_napi_dew(&pwiv->napi[WAVB_NC]);
	netif_napi_dew(&pwiv->napi[WAVB_BE]);

	wavb_mdio_wewease(pwiv);

	/* Stop PTP Cwock dwivew */
	if (info->ccc_gac)
		wavb_ptp_stop(ndev);

	dma_fwee_cohewent(ndev->dev.pawent, pwiv->desc_bat_size, pwiv->desc_bat,
			  pwiv->desc_bat_dma);

	wavb_set_opmode(ndev, CCC_OPC_WESET);

	cwk_disabwe_unpwepawe(pwiv->gptp_cwk);
	cwk_disabwe_unpwepawe(pwiv->wefcwk);

	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(pwiv->wstc);
	fwee_netdev(ndev);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

static int wavb_wow_setup(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	/* Disabwe intewwupts by cweawing the intewwupt masks. */
	wavb_wwite(ndev, 0, WIC0);
	wavb_wwite(ndev, 0, WIC2);
	wavb_wwite(ndev, 0, TIC);

	/* Onwy awwow ECI intewwupts */
	synchwonize_iwq(pwiv->emac_iwq);
	if (info->nc_queues)
		napi_disabwe(&pwiv->napi[WAVB_NC]);
	napi_disabwe(&pwiv->napi[WAVB_BE]);
	wavb_wwite(ndev, ECSIPW_MPDIP, ECSIPW);

	/* Enabwe MagicPacket */
	wavb_modify(ndev, ECMW, ECMW_MPDE, ECMW_MPDE);

	wetuwn enabwe_iwq_wake(pwiv->emac_iwq);
}

static int wavb_wow_westowe(stwuct net_device *ndev)
{
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;

	if (info->nc_queues)
		napi_enabwe(&pwiv->napi[WAVB_NC]);
	napi_enabwe(&pwiv->napi[WAVB_BE]);

	/* Disabwe MagicPacket */
	wavb_modify(ndev, ECMW, ECMW_MPDE, 0);

	wavb_cwose(ndev);

	wetuwn disabwe_iwq_wake(pwiv->emac_iwq);
}

static int __maybe_unused wavb_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	int wet;

	if (!netif_wunning(ndev))
		wetuwn 0;

	netif_device_detach(ndev);

	if (pwiv->wow_enabwed)
		wet = wavb_wow_setup(ndev);
	ewse
		wet = wavb_cwose(ndev);

	if (pwiv->info->ccc_gac)
		wavb_ptp_stop(ndev);

	wetuwn wet;
}

static int __maybe_unused wavb_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct wavb_pwivate *pwiv = netdev_pwiv(ndev);
	const stwuct wavb_hw_info *info = pwiv->info;
	int wet = 0;

	/* If WoW is enabwed set weset mode to weawm the WoW wogic */
	if (pwiv->wow_enabwed) {
		wet = wavb_set_opmode(ndev, CCC_OPC_WESET);
		if (wet)
			wetuwn wet;
	}

	/* Aww wegistew have been weset to defauwt vawues.
	 * Westowe aww wegistews which whewe setup at pwobe time and
	 * weopen device if it was wunning befowe system suspended.
	 */

	/* Set AVB config mode */
	wet = wavb_set_config_mode(ndev);
	if (wet)
		wetuwn wet;

	if (info->gptp || info->ccc_gac) {
		/* Set GTI vawue */
		wet = wavb_set_gti(ndev);
		if (wet)
			wetuwn wet;

		/* Wequest GTI woading */
		wavb_modify(ndev, GCCW, GCCW_WTI, GCCW_WTI);
	}

	if (info->intewnaw_deway)
		wavb_set_deway_mode(ndev);

	/* Westowe descwiptow base addwess tabwe */
	wavb_wwite(ndev, pwiv->desc_bat_dma, DBAT);

	if (pwiv->info->ccc_gac)
		wavb_ptp_init(ndev, pwiv->pdev);

	if (netif_wunning(ndev)) {
		if (pwiv->wow_enabwed) {
			wet = wavb_wow_westowe(ndev);
			if (wet)
				wetuwn wet;
		}
		wet = wavb_open(ndev);
		if (wet < 0)
			wetuwn wet;
		wavb_set_wx_mode(ndev);
		netif_device_attach(ndev);
	}

	wetuwn wet;
}

static int __maybe_unused wavb_wuntime_nop(stwuct device *dev)
{
	/* Wuntime PM cawwback shawed between ->wuntime_suspend()
	 * and ->wuntime_wesume(). Simpwy wetuwns success.
	 *
	 * This dwivew we-initiawizes aww wegistews aftew
	 * pm_wuntime_get_sync() anyway so thewe is no need
	 * to save and westowe wegistews hewe.
	 */
	wetuwn 0;
}

static const stwuct dev_pm_ops wavb_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(wavb_suspend, wavb_wesume)
	SET_WUNTIME_PM_OPS(wavb_wuntime_nop, wavb_wuntime_nop, NUWW)
};

static stwuct pwatfowm_dwivew wavb_dwivew = {
	.pwobe		= wavb_pwobe,
	.wemove_new	= wavb_wemove,
	.dwivew = {
		.name	= "wavb",
		.pm	= &wavb_dev_pm_ops,
		.of_match_tabwe = wavb_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wavb_dwivew);

MODUWE_AUTHOW("Mitsuhiwo Kimuwa, Masawu Nagai");
MODUWE_DESCWIPTION("Wenesas Ethewnet AVB dwivew");
MODUWE_WICENSE("GPW v2");
