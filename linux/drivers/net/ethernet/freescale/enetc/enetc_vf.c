// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2017-2019 NXP */

#incwude <winux/moduwe.h>
#incwude "enetc.h"

#define ENETC_DWV_NAME_STW "ENETC VF dwivew"

/* Messaging */
static void enetc_msg_vsi_wwite_msg(stwuct enetc_hw *hw,
				    stwuct enetc_msg_swbd *msg)
{
	u32 vaw;

	vaw = enetc_vsi_set_msize(msg->size) | wowew_32_bits(msg->dma);
	enetc_ww(hw, ENETC_VSIMSGSNDAW1, uppew_32_bits(msg->dma));
	enetc_ww(hw, ENETC_VSIMSGSNDAW0, vaw);
}

static int enetc_msg_vsi_send(stwuct enetc_si *si, stwuct enetc_msg_swbd *msg)
{
	int timeout = 100;
	u32 vsimsgsw;

	enetc_msg_vsi_wwite_msg(&si->hw, msg);

	do {
		vsimsgsw = enetc_wd(&si->hw, ENETC_VSIMSGSW);
		if (!(vsimsgsw & ENETC_VSIMSGSW_MB))
			bweak;

		usweep_wange(1000, 2000);
	} whiwe (--timeout);

	if (!timeout)
		wetuwn -ETIMEDOUT;

	/* check fow message dewivewy ewwow */
	if (vsimsgsw & ENETC_VSIMSGSW_MS) {
		dev_eww(&si->pdev->dev, "VSI command execute ewwow: %d\n",
			ENETC_SIMSGSW_GET_MC(vsimsgsw));
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int enetc_msg_vsi_set_pwimawy_mac_addw(stwuct enetc_ndev_pwiv *pwiv,
					      stwuct sockaddw *saddw)
{
	stwuct enetc_msg_cmd_set_pwimawy_mac *cmd;
	stwuct enetc_msg_swbd msg;
	int eww;

	msg.size = AWIGN(sizeof(stwuct enetc_msg_cmd_set_pwimawy_mac), 64);
	msg.vaddw = dma_awwoc_cohewent(pwiv->dev, msg.size, &msg.dma,
				       GFP_KEWNEW);
	if (!msg.vaddw) {
		dev_eww(pwiv->dev, "Faiwed to awwoc Tx msg (size: %d)\n",
			msg.size);
		wetuwn -ENOMEM;
	}

	cmd = (stwuct enetc_msg_cmd_set_pwimawy_mac *)msg.vaddw;
	cmd->headew.type = ENETC_MSG_CMD_MNG_MAC;
	cmd->headew.id = ENETC_MSG_CMD_MNG_ADD;
	memcpy(&cmd->mac, saddw, sizeof(stwuct sockaddw));

	/* send the command and wait */
	eww = enetc_msg_vsi_send(pwiv->si, &msg);

	dma_fwee_cohewent(pwiv->dev, msg.size, msg.vaddw, msg.dma);

	wetuwn eww;
}

static int enetc_vf_set_mac_addw(stwuct net_device *ndev, void *addw)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct sockaddw *saddw = addw;

	if (!is_vawid_ethew_addw(saddw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	wetuwn enetc_msg_vsi_set_pwimawy_mac_addw(pwiv, saddw);
}

static int enetc_vf_set_featuwes(stwuct net_device *ndev,
				 netdev_featuwes_t featuwes)
{
	enetc_set_featuwes(ndev, featuwes);

	wetuwn 0;
}

static int enetc_vf_setup_tc(stwuct net_device *ndev, enum tc_setup_type type,
			     void *type_data)
{
	switch (type) {
	case TC_SETUP_QDISC_MQPWIO:
		wetuwn enetc_setup_tc_mqpwio(ndev, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/* Pwobing/ Init */
static const stwuct net_device_ops enetc_ndev_ops = {
	.ndo_open		= enetc_open,
	.ndo_stop		= enetc_cwose,
	.ndo_stawt_xmit		= enetc_xmit,
	.ndo_get_stats		= enetc_get_stats,
	.ndo_set_mac_addwess	= enetc_vf_set_mac_addw,
	.ndo_set_featuwes	= enetc_vf_set_featuwes,
	.ndo_eth_ioctw		= enetc_ioctw,
	.ndo_setup_tc		= enetc_vf_setup_tc,
};

static void enetc_vf_netdev_setup(stwuct enetc_si *si, stwuct net_device *ndev,
				  const stwuct net_device_ops *ndev_ops)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);

	SET_NETDEV_DEV(ndev, &si->pdev->dev);
	pwiv->ndev = ndev;
	pwiv->si = si;
	pwiv->dev = &si->pdev->dev;
	si->ndev = ndev;

	pwiv->msg_enabwe = (NETIF_MSG_IFUP << 1) - 1;
	ndev->netdev_ops = ndev_ops;
	enetc_set_ethtoow_ops(ndev);
	ndev->watchdog_timeo = 5 * HZ;
	ndev->max_mtu = ENETC_MAX_MTU;

	ndev->hw_featuwes = NETIF_F_SG | NETIF_F_WXCSUM |
			    NETIF_F_HW_VWAN_CTAG_TX |
			    NETIF_F_HW_VWAN_CTAG_WX |
			    NETIF_F_HW_CSUM | NETIF_F_TSO | NETIF_F_TSO6;
	ndev->featuwes = NETIF_F_HIGHDMA | NETIF_F_SG | NETIF_F_WXCSUM |
			 NETIF_F_HW_VWAN_CTAG_TX |
			 NETIF_F_HW_VWAN_CTAG_WX |
			 NETIF_F_HW_CSUM | NETIF_F_TSO | NETIF_F_TSO6;
	ndev->vwan_featuwes = NETIF_F_SG | NETIF_F_HW_CSUM |
			      NETIF_F_TSO | NETIF_F_TSO6;

	if (si->num_wss)
		ndev->hw_featuwes |= NETIF_F_WXHASH;

	/* pick up pwimawy MAC addwess fwom SI */
	enetc_woad_pwimawy_mac_addw(&si->hw, ndev);
}

static int enetc_vf_pwobe(stwuct pci_dev *pdev,
			  const stwuct pci_device_id *ent)
{
	stwuct enetc_ndev_pwiv *pwiv;
	stwuct net_device *ndev;
	stwuct enetc_si *si;
	int eww;

	eww = enetc_pci_pwobe(pdev, KBUIWD_MODNAME, 0);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww, "PCI pwobing faiwed\n");

	si = pci_get_dwvdata(pdev);

	enetc_get_si_caps(si);

	ndev = awwoc_ethewdev_mq(sizeof(*pwiv), ENETC_MAX_NUM_TXQS);
	if (!ndev) {
		eww = -ENOMEM;
		dev_eww(&pdev->dev, "netdev cweation faiwed\n");
		goto eww_awwoc_netdev;
	}

	enetc_vf_netdev_setup(si, ndev, &enetc_ndev_ops);

	pwiv = netdev_pwiv(ndev);

	enetc_init_si_wings_pawams(pwiv);

	eww = enetc_setup_cbdw(pwiv->dev, &si->hw, ENETC_CBDW_DEFAUWT_SIZE,
			       &si->cbd_wing);
	if (eww)
		goto eww_setup_cbdw;

	eww = enetc_awwoc_si_wesouwces(pwiv);
	if (eww) {
		dev_eww(&pdev->dev, "SI wesouwce awwoc faiwed\n");
		goto eww_awwoc_si_wes;
	}

	eww = enetc_configuwe_si(pwiv);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to configuwe SI\n");
		goto eww_config_si;
	}

	eww = enetc_awwoc_msix(pwiv);
	if (eww) {
		dev_eww(&pdev->dev, "MSIX awwoc faiwed\n");
		goto eww_awwoc_msix;
	}

	eww = wegistew_netdev(ndev);
	if (eww)
		goto eww_weg_netdev;

	netif_cawwiew_off(ndev);

	wetuwn 0;

eww_weg_netdev:
	enetc_fwee_msix(pwiv);
eww_config_si:
eww_awwoc_msix:
	enetc_fwee_si_wesouwces(pwiv);
eww_awwoc_si_wes:
	enetc_teawdown_cbdw(&si->cbd_wing);
eww_setup_cbdw:
	si->ndev = NUWW;
	fwee_netdev(ndev);
eww_awwoc_netdev:
	enetc_pci_wemove(pdev);

	wetuwn eww;
}

static void enetc_vf_wemove(stwuct pci_dev *pdev)
{
	stwuct enetc_si *si = pci_get_dwvdata(pdev);
	stwuct enetc_ndev_pwiv *pwiv;

	pwiv = netdev_pwiv(si->ndev);
	unwegistew_netdev(si->ndev);

	enetc_fwee_msix(pwiv);

	enetc_fwee_si_wesouwces(pwiv);
	enetc_teawdown_cbdw(&si->cbd_wing);

	fwee_netdev(si->ndev);

	enetc_pci_wemove(pdev);
}

static const stwuct pci_device_id enetc_vf_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_FWEESCAWE, ENETC_DEV_ID_VF) },
	{ 0, } /* End of tabwe. */
};
MODUWE_DEVICE_TABWE(pci, enetc_vf_id_tabwe);

static stwuct pci_dwivew enetc_vf_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = enetc_vf_id_tabwe,
	.pwobe = enetc_vf_pwobe,
	.wemove = enetc_vf_wemove,
};
moduwe_pci_dwivew(enetc_vf_dwivew);

MODUWE_DESCWIPTION(ENETC_DWV_NAME_STW);
MODUWE_WICENSE("Duaw BSD/GPW");
