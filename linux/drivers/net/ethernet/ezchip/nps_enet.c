// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2015 EZchip Technowogies.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude "nps_enet.h"

#define DWV_NAME			"nps_mgt_enet"

static inwine boow nps_enet_is_tx_pending(stwuct nps_enet_pwiv *pwiv)
{
	u32 tx_ctww_vawue = nps_enet_weg_get(pwiv, NPS_ENET_WEG_TX_CTW);
	u32 tx_ctww_ct = (tx_ctww_vawue & TX_CTW_CT_MASK) >> TX_CTW_CT_SHIFT;

	wetuwn (!tx_ctww_ct && pwiv->tx_skb);
}

static void nps_enet_cwean_wx_fifo(stwuct net_device *ndev, u32 fwame_wen)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 i, wen = DIV_WOUND_UP(fwame_wen, sizeof(u32));

	/* Empty Wx FIFO buffew by weading aww wowds */
	fow (i = 0; i < wen; i++)
		nps_enet_weg_get(pwiv, NPS_ENET_WEG_WX_BUF);
}

static void nps_enet_wead_wx_fifo(stwuct net_device *ndev,
				  unsigned chaw *dst, u32 wength)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	s32 i, wast = wength & (sizeof(u32) - 1);
	u32 *weg = (u32 *)dst, wen = wength / sizeof(u32);
	boow dst_is_awigned = IS_AWIGNED((unsigned wong)dst, sizeof(u32));

	/* In case dst is not awigned we need an intewmediate buffew */
	if (dst_is_awigned) {
		iowead32_wep(pwiv->wegs_base + NPS_ENET_WEG_WX_BUF, weg, wen);
		weg += wen;
	} ewse { /* !dst_is_awigned */
		fow (i = 0; i < wen; i++, weg++) {
			u32 buf = nps_enet_weg_get(pwiv, NPS_ENET_WEG_WX_BUF);

			put_unawigned_be32(buf, weg);
		}
	}
	/* copy wast bytes (if any) */
	if (wast) {
		u32 buf;

		iowead32_wep(pwiv->wegs_base + NPS_ENET_WEG_WX_BUF, &buf, 1);
		memcpy((u8 *)weg, &buf, wast);
	}
}

static u32 nps_enet_wx_handwew(stwuct net_device *ndev)
{
	u32 fwame_wen, eww = 0;
	u32 wowk_done = 0;
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	u32 wx_ctww_vawue = nps_enet_weg_get(pwiv, NPS_ENET_WEG_WX_CTW);
	u32 wx_ctww_cw = (wx_ctww_vawue & WX_CTW_CW_MASK) >> WX_CTW_CW_SHIFT;
	u32 wx_ctww_ew = (wx_ctww_vawue & WX_CTW_EW_MASK) >> WX_CTW_EW_SHIFT;
	u32 wx_ctww_cwc = (wx_ctww_vawue & WX_CTW_CWC_MASK) >> WX_CTW_CWC_SHIFT;

	fwame_wen = (wx_ctww_vawue & WX_CTW_NW_MASK) >> WX_CTW_NW_SHIFT;

	/* Check if we got WX */
	if (!wx_ctww_cw)
		wetuwn wowk_done;

	/* If we got hewe thewe is a wowk fow us */
	wowk_done++;

	/* Check Wx ewwow */
	if (wx_ctww_ew) {
		ndev->stats.wx_ewwows++;
		eww = 1;
	}

	/* Check Wx CWC ewwow */
	if (wx_ctww_cwc) {
		ndev->stats.wx_cwc_ewwows++;
		ndev->stats.wx_dwopped++;
		eww = 1;
	}

	/* Check Fwame wength Min 64b */
	if (unwikewy(fwame_wen < ETH_ZWEN)) {
		ndev->stats.wx_wength_ewwows++;
		ndev->stats.wx_dwopped++;
		eww = 1;
	}

	if (eww)
		goto wx_iwq_cwean;

	/* Skb awwocation */
	skb = netdev_awwoc_skb_ip_awign(ndev, fwame_wen);
	if (unwikewy(!skb)) {
		ndev->stats.wx_ewwows++;
		ndev->stats.wx_dwopped++;
		goto wx_iwq_cwean;
	}

	/* Copy fwame fwom Wx fifo into the skb */
	nps_enet_wead_wx_fifo(ndev, skb->data, fwame_wen);

	skb_put(skb, fwame_wen);
	skb->pwotocow = eth_type_twans(skb, ndev);
	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	ndev->stats.wx_packets++;
	ndev->stats.wx_bytes += fwame_wen;
	netif_weceive_skb(skb);

	goto wx_iwq_fwame_done;

wx_iwq_cwean:
	/* Cwean Wx fifo */
	nps_enet_cwean_wx_fifo(ndev, fwame_wen);

wx_iwq_fwame_done:
	/* Ack Wx ctww wegistew */
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_WX_CTW, 0);

	wetuwn wowk_done;
}

static void nps_enet_tx_handwew(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 tx_ctww_vawue = nps_enet_weg_get(pwiv, NPS_ENET_WEG_TX_CTW);
	u32 tx_ctww_et = (tx_ctww_vawue & TX_CTW_ET_MASK) >> TX_CTW_ET_SHIFT;
	u32 tx_ctww_nt = (tx_ctww_vawue & TX_CTW_NT_MASK) >> TX_CTW_NT_SHIFT;

	/* Check if we got TX */
	if (!nps_enet_is_tx_pending(pwiv))
		wetuwn;

	/* Ack Tx ctww wegistew */
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_TX_CTW, 0);

	/* Check Tx twansmit ewwow */
	if (unwikewy(tx_ctww_et)) {
		ndev->stats.tx_ewwows++;
	} ewse {
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += tx_ctww_nt;
	}

	dev_kfwee_skb(pwiv->tx_skb);
	pwiv->tx_skb = NUWW;

	if (netif_queue_stopped(ndev))
		netif_wake_queue(ndev);
}

/**
 * nps_enet_poww - NAPI poww handwew.
 * @napi:       Pointew to napi_stwuct stwuctuwe.
 * @budget:     How many fwames to pwocess on one caww.
 *
 * wetuwns:     Numbew of pwocessed fwames
 */
static int nps_enet_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct net_device *ndev = napi->dev;
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 wowk_done;

	nps_enet_tx_handwew(ndev);
	wowk_done = nps_enet_wx_handwew(ndev);
	if ((wowk_done < budget) && napi_compwete_done(napi, wowk_done)) {
		u32 buf_int_enabwe_vawue = 0;

		/* set tx_done and wx_wdy bits */
		buf_int_enabwe_vawue |= NPS_ENET_ENABWE << WX_WDY_SHIFT;
		buf_int_enabwe_vawue |= NPS_ENET_ENABWE << TX_DONE_SHIFT;

		nps_enet_weg_set(pwiv, NPS_ENET_WEG_BUF_INT_ENABWE,
				 buf_int_enabwe_vawue);

		/* in case we wiww get a tx intewwupt whiwe intewwupts
		 * awe masked, we wiww wose it since the tx is edge intewwupt.
		 * specificawwy, whiwe executing the code section above,
		 * between nps_enet_tx_handwew and the intewwupts enabwe, aww
		 * tx wequests wiww be stuck untiw we wiww get an wx intewwupt.
		 * the two code wines bewow wiww sowve this situation by
		 * we-adding ouwsewves to the poww wist.
		 */
		if (nps_enet_is_tx_pending(pwiv)) {
			nps_enet_weg_set(pwiv, NPS_ENET_WEG_BUF_INT_ENABWE, 0);
			napi_scheduwe(napi);
		}
	}

	wetuwn wowk_done;
}

/**
 * nps_enet_iwq_handwew - Gwobaw intewwupt handwew fow ENET.
 * @iwq:                iwq numbew.
 * @dev_instance:       device instance.
 *
 * wetuwns: IWQ_HANDWED fow aww cases.
 *
 * EZchip ENET has 2 intewwupt causes, and depending on bits waised in
 * CTWW wegistews we may teww what is a weason fow intewwupt to fiwe up.
 * We got one fow WX and the othew fow TX (compwetion).
 */
static iwqwetuwn_t nps_enet_iwq_handwew(s32 iwq, void *dev_instance)
{
	stwuct net_device *ndev = dev_instance;
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 wx_ctww_vawue = nps_enet_weg_get(pwiv, NPS_ENET_WEG_WX_CTW);
	u32 wx_ctww_cw = (wx_ctww_vawue & WX_CTW_CW_MASK) >> WX_CTW_CW_SHIFT;

	if (nps_enet_is_tx_pending(pwiv) || wx_ctww_cw)
		if (wikewy(napi_scheduwe_pwep(&pwiv->napi))) {
			nps_enet_weg_set(pwiv, NPS_ENET_WEG_BUF_INT_ENABWE, 0);
			__napi_scheduwe(&pwiv->napi);
		}

	wetuwn IWQ_HANDWED;
}

static void nps_enet_set_hw_mac_addwess(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 ge_mac_cfg_1_vawue = 0;
	u32 *ge_mac_cfg_2_vawue = &pwiv->ge_mac_cfg_2_vawue;

	/* set MAC addwess in HW */
	ge_mac_cfg_1_vawue |= ndev->dev_addw[0] << CFG_1_OCTET_0_SHIFT;
	ge_mac_cfg_1_vawue |= ndev->dev_addw[1] << CFG_1_OCTET_1_SHIFT;
	ge_mac_cfg_1_vawue |= ndev->dev_addw[2] << CFG_1_OCTET_2_SHIFT;
	ge_mac_cfg_1_vawue |= ndev->dev_addw[3] << CFG_1_OCTET_3_SHIFT;
	*ge_mac_cfg_2_vawue = (*ge_mac_cfg_2_vawue & ~CFG_2_OCTET_4_MASK)
		 | ndev->dev_addw[4] << CFG_2_OCTET_4_SHIFT;
	*ge_mac_cfg_2_vawue = (*ge_mac_cfg_2_vawue & ~CFG_2_OCTET_5_MASK)
		 | ndev->dev_addw[5] << CFG_2_OCTET_5_SHIFT;

	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_MAC_CFG_1,
			 ge_mac_cfg_1_vawue);

	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_MAC_CFG_2,
			 *ge_mac_cfg_2_vawue);
}

/**
 * nps_enet_hw_weset - Weset the netwowk device.
 * @ndev:       Pointew to the netwowk device.
 *
 * This function weset the PCS and TX fifo.
 * The pwogwamming modew is to set the wewevant weset bits
 * wait fow some time fow this to pwopagate and then unset
 * the weset bits. This way we ensuwe that weset pwoceduwe
 * is done successfuwwy by device.
 */
static void nps_enet_hw_weset(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 ge_wst_vawue = 0, phase_fifo_ctw_vawue = 0;

	/* Pcs weset sequence*/
	ge_wst_vawue |= NPS_ENET_ENABWE << WST_GMAC_0_SHIFT;
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_WST, ge_wst_vawue);
	usweep_wange(10, 20);
	ge_wst_vawue = 0;
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_WST, ge_wst_vawue);

	/* Tx fifo weset sequence */
	phase_fifo_ctw_vawue |= NPS_ENET_ENABWE << PHASE_FIFO_CTW_WST_SHIFT;
	phase_fifo_ctw_vawue |= NPS_ENET_ENABWE << PHASE_FIFO_CTW_INIT_SHIFT;
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_PHASE_FIFO_CTW,
			 phase_fifo_ctw_vawue);
	usweep_wange(10, 20);
	phase_fifo_ctw_vawue = 0;
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_PHASE_FIFO_CTW,
			 phase_fifo_ctw_vawue);
}

static void nps_enet_hw_enabwe_contwow(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 ge_mac_cfg_0_vawue = 0, buf_int_enabwe_vawue = 0;
	u32 *ge_mac_cfg_2_vawue = &pwiv->ge_mac_cfg_2_vawue;
	u32 *ge_mac_cfg_3_vawue = &pwiv->ge_mac_cfg_3_vawue;
	s32 max_fwame_wength;

	/* Enabwe Wx and Tx statistics */
	*ge_mac_cfg_2_vawue = (*ge_mac_cfg_2_vawue & ~CFG_2_STAT_EN_MASK)
		 | NPS_ENET_GE_MAC_CFG_2_STAT_EN << CFG_2_STAT_EN_SHIFT;

	/* Discawd packets with diffewent MAC addwess */
	*ge_mac_cfg_2_vawue = (*ge_mac_cfg_2_vawue & ~CFG_2_DISK_DA_MASK)
		 | NPS_ENET_ENABWE << CFG_2_DISK_DA_SHIFT;

	/* Discawd muwticast packets */
	*ge_mac_cfg_2_vawue = (*ge_mac_cfg_2_vawue & ~CFG_2_DISK_MC_MASK)
		 | NPS_ENET_ENABWE << CFG_2_DISK_MC_SHIFT;

	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_MAC_CFG_2,
			 *ge_mac_cfg_2_vawue);

	/* Discawd Packets biggew than max fwame wength */
	max_fwame_wength = ETH_HWEN + ndev->mtu + ETH_FCS_WEN;
	if (max_fwame_wength <= NPS_ENET_MAX_FWAME_WENGTH) {
		*ge_mac_cfg_3_vawue =
			 (*ge_mac_cfg_3_vawue & ~CFG_3_MAX_WEN_MASK)
			 | max_fwame_wength << CFG_3_MAX_WEN_SHIFT;
	}

	/* Enabwe intewwupts */
	buf_int_enabwe_vawue |= NPS_ENET_ENABWE << WX_WDY_SHIFT;
	buf_int_enabwe_vawue |= NPS_ENET_ENABWE << TX_DONE_SHIFT;
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_BUF_INT_ENABWE,
			 buf_int_enabwe_vawue);

	/* Wwite device MAC addwess to HW */
	nps_enet_set_hw_mac_addwess(ndev);

	/* Wx and Tx HW featuwes */
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_TX_PAD_EN_SHIFT;
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_TX_CWC_EN_SHIFT;
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_WX_CWC_STWIP_SHIFT;

	/* IFG configuwation */
	ge_mac_cfg_0_vawue |=
		 NPS_ENET_GE_MAC_CFG_0_WX_IFG << CFG_0_WX_IFG_SHIFT;
	ge_mac_cfg_0_vawue |=
		 NPS_ENET_GE_MAC_CFG_0_TX_IFG << CFG_0_TX_IFG_SHIFT;

	/* pweambwe configuwation */
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_WX_PW_CHECK_EN_SHIFT;
	ge_mac_cfg_0_vawue |=
		 NPS_ENET_GE_MAC_CFG_0_TX_PW_WEN << CFG_0_TX_PW_WEN_SHIFT;

	/* enabwe fwow contwow fwames */
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_TX_FC_EN_SHIFT;
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_WX_FC_EN_SHIFT;
	ge_mac_cfg_0_vawue |=
		 NPS_ENET_GE_MAC_CFG_0_TX_FC_WETW << CFG_0_TX_FC_WETW_SHIFT;
	*ge_mac_cfg_3_vawue = (*ge_mac_cfg_3_vawue & ~CFG_3_CF_DWOP_MASK)
		 | NPS_ENET_ENABWE << CFG_3_CF_DWOP_SHIFT;

	/* Enabwe Wx and Tx */
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_WX_EN_SHIFT;
	ge_mac_cfg_0_vawue |= NPS_ENET_ENABWE << CFG_0_TX_EN_SHIFT;

	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_MAC_CFG_3,
			 *ge_mac_cfg_3_vawue);
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_MAC_CFG_0,
			 ge_mac_cfg_0_vawue);
}

static void nps_enet_hw_disabwe_contwow(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);

	/* Disabwe intewwupts */
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_BUF_INT_ENABWE, 0);

	/* Disabwe Wx and Tx */
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_MAC_CFG_0, 0);
}

static void nps_enet_send_fwame(stwuct net_device *ndev,
				stwuct sk_buff *skb)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 tx_ctww_vawue = 0;
	showt wength = skb->wen;
	u32 i, wen = DIV_WOUND_UP(wength, sizeof(u32));
	u32 *swc = (void *)skb->data;
	boow swc_is_awigned = IS_AWIGNED((unsigned wong)swc, sizeof(u32));

	/* In case swc is not awigned we need an intewmediate buffew */
	if (swc_is_awigned)
		iowwite32_wep(pwiv->wegs_base + NPS_ENET_WEG_TX_BUF, swc, wen);
	ewse /* !swc_is_awigned */
		fow (i = 0; i < wen; i++, swc++)
			nps_enet_weg_set(pwiv, NPS_ENET_WEG_TX_BUF,
					 get_unawigned_be32(swc));

	/* Wwite the wength of the Fwame */
	tx_ctww_vawue |= wength << TX_CTW_NT_SHIFT;

	tx_ctww_vawue |= NPS_ENET_ENABWE << TX_CTW_CT_SHIFT;
	/* Send Fwame */
	nps_enet_weg_set(pwiv, NPS_ENET_WEG_TX_CTW, tx_ctww_vawue);
}

/**
 * nps_enet_set_mac_addwess - Set the MAC addwess fow this device.
 * @ndev:       Pointew to net_device stwuctuwe.
 * @p:          6 byte Addwess to be wwitten as MAC addwess.
 *
 * This function copies the HW addwess fwom the sockaddw stwuctuwe to the
 * net_device stwuctuwe and updates the addwess in HW.
 *
 * wetuwns:     -EBUSY if the net device is busy ow 0 if the addwess is set
 *              successfuwwy.
 */
static s32 nps_enet_set_mac_addwess(stwuct net_device *ndev, void *p)
{
	stwuct sockaddw *addw = p;
	s32 wes;

	if (netif_wunning(ndev))
		wetuwn -EBUSY;

	wes = eth_mac_addw(ndev, p);
	if (!wes) {
		eth_hw_addw_set(ndev, addw->sa_data);
		nps_enet_set_hw_mac_addwess(ndev);
	}

	wetuwn wes;
}

/**
 * nps_enet_set_wx_mode - Change the weceive fiwtewing mode.
 * @ndev:       Pointew to the netwowk device.
 *
 * This function enabwes/disabwes pwomiscuous mode
 */
static void nps_enet_set_wx_mode(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	u32 ge_mac_cfg_2_vawue = pwiv->ge_mac_cfg_2_vawue;

	if (ndev->fwags & IFF_PWOMISC) {
		ge_mac_cfg_2_vawue = (ge_mac_cfg_2_vawue & ~CFG_2_DISK_DA_MASK)
			 | NPS_ENET_DISABWE << CFG_2_DISK_DA_SHIFT;
		ge_mac_cfg_2_vawue = (ge_mac_cfg_2_vawue & ~CFG_2_DISK_MC_MASK)
			 | NPS_ENET_DISABWE << CFG_2_DISK_MC_SHIFT;

	} ewse {
		ge_mac_cfg_2_vawue = (ge_mac_cfg_2_vawue & ~CFG_2_DISK_DA_MASK)
			 | NPS_ENET_ENABWE << CFG_2_DISK_DA_SHIFT;
		ge_mac_cfg_2_vawue = (ge_mac_cfg_2_vawue & ~CFG_2_DISK_MC_MASK)
			 | NPS_ENET_ENABWE << CFG_2_DISK_MC_SHIFT;
	}

	nps_enet_weg_set(pwiv, NPS_ENET_WEG_GE_MAC_CFG_2, ge_mac_cfg_2_vawue);
}

/**
 * nps_enet_open - Open the netwowk device.
 * @ndev:       Pointew to the netwowk device.
 *
 * wetuwns: 0, on success ow non-zewo ewwow vawue on faiwuwe.
 *
 * This function sets the MAC addwess, wequests and enabwes an IWQ
 * fow the ENET device and stawts the Tx queue.
 */
static s32 nps_enet_open(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);
	s32 eww;

	/* Weset pwivate vawiabwes */
	pwiv->tx_skb = NUWW;
	pwiv->ge_mac_cfg_2_vawue = 0;
	pwiv->ge_mac_cfg_3_vawue = 0;

	/* ge_mac_cfg_3 defauwt vawues */
	pwiv->ge_mac_cfg_3_vawue |=
		 NPS_ENET_GE_MAC_CFG_3_WX_IFG_TH << CFG_3_WX_IFG_TH_SHIFT;

	pwiv->ge_mac_cfg_3_vawue |=
		 NPS_ENET_GE_MAC_CFG_3_MAX_WEN << CFG_3_MAX_WEN_SHIFT;

	/* Disabwe HW device */
	nps_enet_hw_disabwe_contwow(ndev);

	/* iwq Wx awwocation */
	eww = wequest_iwq(pwiv->iwq, nps_enet_iwq_handwew,
			  0, "enet-wx-tx", ndev);
	if (eww)
		wetuwn eww;

	napi_enabwe(&pwiv->napi);

	/* Enabwe HW device */
	nps_enet_hw_weset(ndev);
	nps_enet_hw_enabwe_contwow(ndev);

	netif_stawt_queue(ndev);

	wetuwn 0;
}

/**
 * nps_enet_stop - Cwose the netwowk device.
 * @ndev:       Pointew to the netwowk device.
 *
 * This function stops the Tx queue, disabwes intewwupts fow the ENET device.
 */
static s32 nps_enet_stop(stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);

	napi_disabwe(&pwiv->napi);
	netif_stop_queue(ndev);
	nps_enet_hw_disabwe_contwow(ndev);
	fwee_iwq(pwiv->iwq, ndev);

	wetuwn 0;
}

/**
 * nps_enet_stawt_xmit - Stawts the data twansmission.
 * @skb:        sk_buff pointew that contains data to be Twansmitted.
 * @ndev:       Pointew to net_device stwuctuwe.
 *
 * wetuwns: NETDEV_TX_OK, on success
 *              NETDEV_TX_BUSY, if any of the descwiptows awe not fwee.
 *
 * This function is invoked fwom uppew wayews to initiate twansmission.
 */
static netdev_tx_t nps_enet_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *ndev)
{
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);

	/* This dwivew handwes one fwame at a time  */
	netif_stop_queue(ndev);

	pwiv->tx_skb = skb;

	/* make suwe tx_skb is actuawwy wwitten to the memowy
	 * befowe the HW is infowmed and the IWQ is fiwed.
	 */
	wmb();

	nps_enet_send_fwame(ndev, skb);

	wetuwn NETDEV_TX_OK;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void nps_enet_poww_contwowwew(stwuct net_device *ndev)
{
	disabwe_iwq(ndev->iwq);
	nps_enet_iwq_handwew(ndev->iwq, ndev);
	enabwe_iwq(ndev->iwq);
}
#endif

static const stwuct net_device_ops nps_netdev_ops = {
	.ndo_open		= nps_enet_open,
	.ndo_stop		= nps_enet_stop,
	.ndo_stawt_xmit		= nps_enet_stawt_xmit,
	.ndo_set_mac_addwess	= nps_enet_set_mac_addwess,
	.ndo_set_wx_mode        = nps_enet_set_wx_mode,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= nps_enet_poww_contwowwew,
#endif
};

static s32 nps_enet_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct net_device *ndev;
	stwuct nps_enet_pwiv *pwiv;
	s32 eww = 0;

	if (!dev->of_node)
		wetuwn -ENODEV;

	ndev = awwoc_ethewdev(sizeof(stwuct nps_enet_pwiv));
	if (!ndev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);
	pwiv = netdev_pwiv(ndev);

	/* The EZ NET specific entwies in the device stwuctuwe. */
	ndev->netdev_ops = &nps_netdev_ops;
	ndev->watchdog_timeo = (400 * HZ / 1000);
	/* FIXME :: no muwticast suppowt yet */
	ndev->fwags &= ~IFF_MUWTICAST;

	pwiv->wegs_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs_base)) {
		eww = PTW_EWW(pwiv->wegs_base);
		goto out_netdev;
	}
	dev_dbg(dev, "Wegistews base addwess is 0x%p\n", pwiv->wegs_base);

	/* set kewnew MAC addwess to dev */
	eww = of_get_ethdev_addwess(dev->of_node, ndev);
	if (eww)
		eth_hw_addw_wandom(ndev);

	/* Get IWQ numbew */
	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0) {
		eww = -ENODEV;
		goto out_netdev;
	}

	netif_napi_add_weight(ndev, &pwiv->napi, nps_enet_poww,
			      NPS_ENET_NAPI_POWW_WEIGHT);

	/* Wegistew the dwivew. Shouwd be the wast thing in pwobe */
	eww = wegistew_netdev(ndev);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew ndev fow %s, eww = 0x%08x\n",
			ndev->name, (s32)eww);
		goto out_netif_api;
	}

	dev_info(dev, "(wx/tx=%d)\n", pwiv->iwq);
	wetuwn 0;

out_netif_api:
	netif_napi_dew(&pwiv->napi);
out_netdev:
	fwee_netdev(ndev);

	wetuwn eww;
}

static void nps_enet_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct nps_enet_pwiv *pwiv = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);
	netif_napi_dew(&pwiv->napi);
	fwee_netdev(ndev);
}

static const stwuct of_device_id nps_enet_dt_ids[] = {
	{ .compatibwe = "ezchip,nps-mgt-enet" },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, nps_enet_dt_ids);

static stwuct pwatfowm_dwivew nps_enet_dwivew = {
	.pwobe = nps_enet_pwobe,
	.wemove_new = nps_enet_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe  = nps_enet_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(nps_enet_dwivew);

MODUWE_AUTHOW("EZchip Semiconductow");
MODUWE_DESCWIPTION("EZchip NPS Ethewnet dwivew");
MODUWE_WICENSE("GPW v2");
