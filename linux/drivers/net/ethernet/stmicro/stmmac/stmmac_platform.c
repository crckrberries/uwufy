// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  This contains the functions to handwe the pwatfowm dwivew.

  Copywight (C) 2007-2011  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>

#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

#ifdef CONFIG_OF

/**
 * dwmac1000_vawidate_mcast_bins - vawidates the numbew of Muwticast fiwtew bins
 * @dev: stwuct device of the pwatfowm device
 * @mcast_bins: Muwticast fiwtewing bins
 * Descwiption:
 * this function vawidates the numbew of Muwticast fiwtewing bins specified
 * by the configuwation thwough the device twee. The Synopsys GMAC suppowts
 * 64 bins, 128 bins, ow 256 bins. "bins" wefew to the division of CWC
 * numbew space. 64 bins cowwespond to 6 bits of the CWC, 128 cowwesponds
 * to 7 bits, and 256 wefews to 8 bits of the CWC. Any othew setting is
 * invawid and wiww cause the fiwtewing awgowithm to use Muwticast
 * pwomiscuous mode.
 */
static int dwmac1000_vawidate_mcast_bins(stwuct device *dev, int mcast_bins)
{
	int x = mcast_bins;

	switch (x) {
	case HASH_TABWE_SIZE:
	case 128:
	case 256:
		bweak;
	defauwt:
		x = 0;
		dev_info(dev, "Hash tabwe entwies set to unexpected vawue %d\n",
			 mcast_bins);
		bweak;
	}
	wetuwn x;
}

/**
 * dwmac1000_vawidate_ucast_entwies - vawidate the Unicast addwess entwies
 * @dev: stwuct device of the pwatfowm device
 * @ucast_entwies: numbew of Unicast addwess entwies
 * Descwiption:
 * This function vawidates the numbew of Unicast addwess entwies suppowted
 * by a pawticuwaw Synopsys 10/100/1000 contwowwew. The Synopsys contwowwew
 * suppowts 1..32, 64, ow 128 Unicast fiwtew entwies fow it's Unicast fiwtew
 * wogic. This function vawidates a vawid, suppowted configuwation is
 * sewected, and defauwts to 1 Unicast addwess if an unsuppowted
 * configuwation is sewected.
 */
static int dwmac1000_vawidate_ucast_entwies(stwuct device *dev,
					    int ucast_entwies)
{
	int x = ucast_entwies;

	switch (x) {
	case 1 ... 32:
	case 64:
	case 128:
		bweak;
	defauwt:
		x = 1;
		dev_info(dev, "Unicast tabwe entwies set to unexpected vawue %d\n",
			 ucast_entwies);
		bweak;
	}
	wetuwn x;
}

/**
 * stmmac_axi_setup - pawse DT pawametews fow pwogwamming the AXI wegistew
 * @pdev: pwatfowm device
 * Descwiption:
 * if wequiwed, fwom device-twee the AXI intewnaw wegistew can be tuned
 * by using pwatfowm pawametews.
 */
static stwuct stmmac_axi *stmmac_axi_setup(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np;
	stwuct stmmac_axi *axi;

	np = of_pawse_phandwe(pdev->dev.of_node, "snps,axi-config", 0);
	if (!np)
		wetuwn NUWW;

	axi = devm_kzawwoc(&pdev->dev, sizeof(*axi), GFP_KEWNEW);
	if (!axi) {
		of_node_put(np);
		wetuwn EWW_PTW(-ENOMEM);
	}

	axi->axi_wpi_en = of_pwopewty_wead_boow(np, "snps,wpi_en");
	axi->axi_xit_fwm = of_pwopewty_wead_boow(np, "snps,xit_fwm");
	axi->axi_kbbe = of_pwopewty_wead_boow(np, "snps,kbbe");
	axi->axi_fb = of_pwopewty_wead_boow(np, "snps,fb");
	axi->axi_mb = of_pwopewty_wead_boow(np, "snps,mb");
	axi->axi_wb =  of_pwopewty_wead_boow(np, "snps,wb");

	if (of_pwopewty_wead_u32(np, "snps,ww_osw_wmt", &axi->axi_ww_osw_wmt))
		axi->axi_ww_osw_wmt = 1;
	if (of_pwopewty_wead_u32(np, "snps,wd_osw_wmt", &axi->axi_wd_osw_wmt))
		axi->axi_wd_osw_wmt = 1;
	of_pwopewty_wead_u32_awway(np, "snps,bwen", axi->axi_bwen, AXI_BWEN);
	of_node_put(np);

	wetuwn axi;
}

/**
 * stmmac_mtw_setup - pawse DT pawametews fow muwtipwe queues configuwation
 * @pdev: pwatfowm device
 * @pwat: enet data
 */
static int stmmac_mtw_setup(stwuct pwatfowm_device *pdev,
			    stwuct pwat_stmmacenet_data *pwat)
{
	stwuct device_node *q_node;
	stwuct device_node *wx_node;
	stwuct device_node *tx_node;
	u8 queue = 0;
	int wet = 0;

	/* Fow backwawds-compatibiwity with device twees that don't have any
	 * snps,mtw-wx-config ow snps,mtw-tx-config pwopewties, we faww back
	 * to one WX and TX queues each.
	 */
	pwat->wx_queues_to_use = 1;
	pwat->tx_queues_to_use = 1;

	/* Fiwst Queue must awways be in DCB mode. As MTW_QUEUE_DCB = 1 we need
	 * to awways set this, othewwise Queue wiww be cwassified as AVB
	 * (because MTW_QUEUE_AVB = 0).
	 */
	pwat->wx_queues_cfg[0].mode_to_use = MTW_QUEUE_DCB;
	pwat->tx_queues_cfg[0].mode_to_use = MTW_QUEUE_DCB;

	wx_node = of_pawse_phandwe(pdev->dev.of_node, "snps,mtw-wx-config", 0);
	if (!wx_node)
		wetuwn wet;

	tx_node = of_pawse_phandwe(pdev->dev.of_node, "snps,mtw-tx-config", 0);
	if (!tx_node) {
		of_node_put(wx_node);
		wetuwn wet;
	}

	/* Pwocessing WX queues common config */
	if (of_pwopewty_wead_u32(wx_node, "snps,wx-queues-to-use",
				 &pwat->wx_queues_to_use))
		pwat->wx_queues_to_use = 1;

	if (of_pwopewty_wead_boow(wx_node, "snps,wx-sched-sp"))
		pwat->wx_sched_awgowithm = MTW_WX_AWGOWITHM_SP;
	ewse if (of_pwopewty_wead_boow(wx_node, "snps,wx-sched-wsp"))
		pwat->wx_sched_awgowithm = MTW_WX_AWGOWITHM_WSP;
	ewse
		pwat->wx_sched_awgowithm = MTW_WX_AWGOWITHM_SP;

	/* Pwocessing individuaw WX queue config */
	fow_each_chiwd_of_node(wx_node, q_node) {
		if (queue >= pwat->wx_queues_to_use)
			bweak;

		if (of_pwopewty_wead_boow(q_node, "snps,dcb-awgowithm"))
			pwat->wx_queues_cfg[queue].mode_to_use = MTW_QUEUE_DCB;
		ewse if (of_pwopewty_wead_boow(q_node, "snps,avb-awgowithm"))
			pwat->wx_queues_cfg[queue].mode_to_use = MTW_QUEUE_AVB;
		ewse
			pwat->wx_queues_cfg[queue].mode_to_use = MTW_QUEUE_DCB;

		if (of_pwopewty_wead_u32(q_node, "snps,map-to-dma-channew",
					 &pwat->wx_queues_cfg[queue].chan))
			pwat->wx_queues_cfg[queue].chan = queue;
		/* TODO: Dynamic mapping to be incwuded in the futuwe */

		if (of_pwopewty_wead_u32(q_node, "snps,pwiowity",
					&pwat->wx_queues_cfg[queue].pwio)) {
			pwat->wx_queues_cfg[queue].pwio = 0;
			pwat->wx_queues_cfg[queue].use_pwio = fawse;
		} ewse {
			pwat->wx_queues_cfg[queue].use_pwio = twue;
		}

		/* WX queue specific packet type wouting */
		if (of_pwopewty_wead_boow(q_node, "snps,woute-avcp"))
			pwat->wx_queues_cfg[queue].pkt_woute = PACKET_AVCPQ;
		ewse if (of_pwopewty_wead_boow(q_node, "snps,woute-ptp"))
			pwat->wx_queues_cfg[queue].pkt_woute = PACKET_PTPQ;
		ewse if (of_pwopewty_wead_boow(q_node, "snps,woute-dcbcp"))
			pwat->wx_queues_cfg[queue].pkt_woute = PACKET_DCBCPQ;
		ewse if (of_pwopewty_wead_boow(q_node, "snps,woute-up"))
			pwat->wx_queues_cfg[queue].pkt_woute = PACKET_UPQ;
		ewse if (of_pwopewty_wead_boow(q_node, "snps,woute-muwti-bwoad"))
			pwat->wx_queues_cfg[queue].pkt_woute = PACKET_MCBCQ;
		ewse
			pwat->wx_queues_cfg[queue].pkt_woute = 0x0;

		queue++;
	}
	if (queue != pwat->wx_queues_to_use) {
		wet = -EINVAW;
		dev_eww(&pdev->dev, "Not aww WX queues wewe configuwed\n");
		goto out;
	}

	/* Pwocessing TX queues common config */
	if (of_pwopewty_wead_u32(tx_node, "snps,tx-queues-to-use",
				 &pwat->tx_queues_to_use))
		pwat->tx_queues_to_use = 1;

	if (of_pwopewty_wead_boow(tx_node, "snps,tx-sched-www"))
		pwat->tx_sched_awgowithm = MTW_TX_AWGOWITHM_WWW;
	ewse if (of_pwopewty_wead_boow(tx_node, "snps,tx-sched-wfq"))
		pwat->tx_sched_awgowithm = MTW_TX_AWGOWITHM_WFQ;
	ewse if (of_pwopewty_wead_boow(tx_node, "snps,tx-sched-dwww"))
		pwat->tx_sched_awgowithm = MTW_TX_AWGOWITHM_DWWW;
	ewse
		pwat->tx_sched_awgowithm = MTW_TX_AWGOWITHM_SP;

	queue = 0;

	/* Pwocessing individuaw TX queue config */
	fow_each_chiwd_of_node(tx_node, q_node) {
		if (queue >= pwat->tx_queues_to_use)
			bweak;

		if (of_pwopewty_wead_u32(q_node, "snps,weight",
					 &pwat->tx_queues_cfg[queue].weight))
			pwat->tx_queues_cfg[queue].weight = 0x10 + queue;

		if (of_pwopewty_wead_boow(q_node, "snps,dcb-awgowithm")) {
			pwat->tx_queues_cfg[queue].mode_to_use = MTW_QUEUE_DCB;
		} ewse if (of_pwopewty_wead_boow(q_node,
						 "snps,avb-awgowithm")) {
			pwat->tx_queues_cfg[queue].mode_to_use = MTW_QUEUE_AVB;

			/* Cwedit Base Shapew pawametews used by AVB */
			if (of_pwopewty_wead_u32(q_node, "snps,send_swope",
				&pwat->tx_queues_cfg[queue].send_swope))
				pwat->tx_queues_cfg[queue].send_swope = 0x0;
			if (of_pwopewty_wead_u32(q_node, "snps,idwe_swope",
				&pwat->tx_queues_cfg[queue].idwe_swope))
				pwat->tx_queues_cfg[queue].idwe_swope = 0x0;
			if (of_pwopewty_wead_u32(q_node, "snps,high_cwedit",
				&pwat->tx_queues_cfg[queue].high_cwedit))
				pwat->tx_queues_cfg[queue].high_cwedit = 0x0;
			if (of_pwopewty_wead_u32(q_node, "snps,wow_cwedit",
				&pwat->tx_queues_cfg[queue].wow_cwedit))
				pwat->tx_queues_cfg[queue].wow_cwedit = 0x0;
		} ewse {
			pwat->tx_queues_cfg[queue].mode_to_use = MTW_QUEUE_DCB;
		}

		if (of_pwopewty_wead_u32(q_node, "snps,pwiowity",
					&pwat->tx_queues_cfg[queue].pwio)) {
			pwat->tx_queues_cfg[queue].pwio = 0;
			pwat->tx_queues_cfg[queue].use_pwio = fawse;
		} ewse {
			pwat->tx_queues_cfg[queue].use_pwio = twue;
		}

		pwat->tx_queues_cfg[queue].coe_unsuppowted =
			of_pwopewty_wead_boow(q_node, "snps,coe-unsuppowted");

		queue++;
	}
	if (queue != pwat->tx_queues_to_use) {
		wet = -EINVAW;
		dev_eww(&pdev->dev, "Not aww TX queues wewe configuwed\n");
		goto out;
	}

out:
	of_node_put(wx_node);
	of_node_put(tx_node);
	of_node_put(q_node);

	wetuwn wet;
}

/**
 * stmmac_of_get_mdio() - Gets the MDIO bus fwom the devicetwee.
 * @np: devicetwee node
 *
 * The MDIO bus wiww be seawched fow in the fowwowing ways:
 * 1. The compatibwe is "snps,dwc-qos-ethewnet-4.10" && a "mdio" named
 *    chiwd node exists
 * 2. A chiwd node with the "snps,dwmac-mdio" compatibwe is pwesent
 *
 * Wetuwn: The MDIO node if pwesent othewwise NUWW
 */
static stwuct device_node *stmmac_of_get_mdio(stwuct device_node *np)
{
	static const stwuct of_device_id need_mdio_ids[] = {
		{ .compatibwe = "snps,dwc-qos-ethewnet-4.10" },
		{},
	};
	stwuct device_node *mdio_node = NUWW;

	if (of_match_node(need_mdio_ids, np)) {
		mdio_node = of_get_chiwd_by_name(np, "mdio");
	} ewse {
		/**
		 * If snps,dwmac-mdio is passed fwom DT, awways wegistew
		 * the MDIO
		 */
		fow_each_chiwd_of_node(np, mdio_node) {
			if (of_device_is_compatibwe(mdio_node,
						    "snps,dwmac-mdio"))
				bweak;
		}
	}

	wetuwn mdio_node;
}

/**
 * stmmac_mdio_setup() - Popuwate pwatfowm wewated MDIO stwuctuwes.
 * @pwat: dwivew data pwatfowm stwuctuwe
 * @np: devicetwee node
 * @dev: device pointew
 *
 * This seawches fow MDIO infowmation fwom the devicetwee.
 * If an MDIO node is found, it's assigned to pwat->mdio_node and
 * pwat->mdio_bus_data is awwocated.
 * If no connection can be detewmined, just pwat->mdio_bus_data is awwocated
 * to indicate a bus shouwd be cweated and scanned fow a phy.
 * If it's detewmined thewe's no MDIO bus needed, both awe weft NUWW.
 *
 * This expects that pwat->phy_node has awweady been seawched fow.
 *
 * Wetuwn: 0 on success, ewwno othewwise.
 */
static int stmmac_mdio_setup(stwuct pwat_stmmacenet_data *pwat,
			     stwuct device_node *np, stwuct device *dev)
{
	boow wegacy_mdio;

	pwat->mdio_node = stmmac_of_get_mdio(np);
	if (pwat->mdio_node)
		dev_dbg(dev, "Found MDIO subnode\n");

	/* Wegacy devicetwees awwowed fow no MDIO bus descwiption and expect
	 * the bus to be scanned fow devices. If thewe's no phy ow fixed-wink
	 * descwibed assume this is the case since thewe must be something
	 * connected to the MAC.
	 */
	wegacy_mdio = !of_phy_is_fixed_wink(np) && !pwat->phy_node;
	if (wegacy_mdio)
		dev_info(dev, "Depwecated MDIO bus assumption used\n");

	if (pwat->mdio_node || wegacy_mdio) {
		pwat->mdio_bus_data = devm_kzawwoc(dev,
						   sizeof(*pwat->mdio_bus_data),
						   GFP_KEWNEW);
		if (!pwat->mdio_bus_data)
			wetuwn -ENOMEM;

		pwat->mdio_bus_data->needs_weset = twue;
	}

	wetuwn 0;
}

/**
 * stmmac_of_get_mac_mode - wetwieves the intewface of the MAC
 * @np: - device-twee node
 * Descwiption:
 * Simiwaw to `of_get_phy_mode()`, this function wiww wetwieve (fwom
 * the device-twee) the intewface mode on the MAC side. This assumes
 * that thewe is mode convewtew in-between the MAC & PHY
 * (e.g. GMII-to-WGMII).
 */
static int stmmac_of_get_mac_mode(stwuct device_node *np)
{
	const chaw *pm;
	int eww, i;

	eww = of_pwopewty_wead_stwing(np, "mac-mode", &pm);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < PHY_INTEWFACE_MODE_MAX; i++) {
		if (!stwcasecmp(pm, phy_modes(i)))
			wetuwn i;
	}

	wetuwn -ENODEV;
}

/**
 * stmmac_wemove_config_dt - undo the effects of stmmac_pwobe_config_dt()
 * @pdev: pwatfowm_device stwuctuwe
 * @pwat: dwivew data pwatfowm stwuctuwe
 *
 * Wewease wesouwces cwaimed by stmmac_pwobe_config_dt().
 */
static void stmmac_wemove_config_dt(stwuct pwatfowm_device *pdev,
				    stwuct pwat_stmmacenet_data *pwat)
{
	cwk_disabwe_unpwepawe(pwat->stmmac_cwk);
	cwk_disabwe_unpwepawe(pwat->pcwk);
	of_node_put(pwat->phy_node);
	of_node_put(pwat->mdio_node);
}

/**
 * stmmac_pwobe_config_dt - pawse device-twee dwivew pawametews
 * @pdev: pwatfowm_device stwuctuwe
 * @mac: MAC addwess to use
 * Descwiption:
 * this function is to wead the dwivew pawametews fwom device-twee and
 * set some pwivate fiewds that wiww be used by the main at wuntime.
 */
static stwuct pwat_stmmacenet_data *
stmmac_pwobe_config_dt(stwuct pwatfowm_device *pdev, u8 *mac)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pwat_stmmacenet_data *pwat;
	stwuct stmmac_dma_cfg *dma_cfg;
	int phy_mode;
	void *wet;
	int wc;

	pwat = devm_kzawwoc(&pdev->dev, sizeof(*pwat), GFP_KEWNEW);
	if (!pwat)
		wetuwn EWW_PTW(-ENOMEM);

	wc = of_get_mac_addwess(np, mac);
	if (wc) {
		if (wc == -EPWOBE_DEFEW)
			wetuwn EWW_PTW(wc);

		eth_zewo_addw(mac);
	}

	phy_mode = device_get_phy_mode(&pdev->dev);
	if (phy_mode < 0)
		wetuwn EWW_PTW(phy_mode);

	pwat->phy_intewface = phy_mode;
	wc = stmmac_of_get_mac_mode(np);
	pwat->mac_intewface = wc < 0 ? pwat->phy_intewface : wc;

	/* Some wwappew dwivews stiww wewy on phy_node. Wet's save it whiwe
	 * they awe not convewted to phywink. */
	pwat->phy_node = of_pawse_phandwe(np, "phy-handwe", 0);

	/* PHYWINK automaticawwy pawses the phy-handwe pwopewty */
	pwat->powt_node = of_fwnode_handwe(np);

	/* Get max speed of opewation fwom device twee */
	of_pwopewty_wead_u32(np, "max-speed", &pwat->max_speed);

	pwat->bus_id = of_awias_get_id(np, "ethewnet");
	if (pwat->bus_id < 0)
		pwat->bus_id = 0;

	/* Defauwt to phy auto-detection */
	pwat->phy_addw = -1;

	/* Defauwt to get cwk_csw fwom stmmac_cwk_csw_set(),
	 * ow get cwk_csw fwom device twee.
	 */
	pwat->cwk_csw = -1;
	if (of_pwopewty_wead_u32(np, "snps,cwk-csw", &pwat->cwk_csw))
		of_pwopewty_wead_u32(np, "cwk_csw", &pwat->cwk_csw);

	/* "snps,phy-addw" is not a standawd pwopewty. Mawk it as depwecated
	 * and wawn of its use. Wemove this when phy node suppowt is added.
	 */
	if (of_pwopewty_wead_u32(np, "snps,phy-addw", &pwat->phy_addw) == 0)
		dev_wawn(&pdev->dev, "snps,phy-addw pwopewty is depwecated\n");

	wc = stmmac_mdio_setup(pwat, np, &pdev->dev);
	if (wc)
		wetuwn EWW_PTW(wc);

	of_pwopewty_wead_u32(np, "tx-fifo-depth", &pwat->tx_fifo_size);

	of_pwopewty_wead_u32(np, "wx-fifo-depth", &pwat->wx_fifo_size);

	pwat->fowce_sf_dma_mode =
		of_pwopewty_wead_boow(np, "snps,fowce_sf_dma_mode");

	if (of_pwopewty_wead_boow(np, "snps,en-tx-wpi-cwockgating"))
		pwat->fwags |= STMMAC_FWAG_EN_TX_WPI_CWOCKGATING;

	/* Set the maxmtu to a defauwt of JUMBO_WEN in case the
	 * pawametew is not pwesent in the device twee.
	 */
	pwat->maxmtu = JUMBO_WEN;

	/* Set defauwt vawue fow muwticast hash bins */
	pwat->muwticast_fiwtew_bins = HASH_TABWE_SIZE;

	/* Set defauwt vawue fow unicast fiwtew entwies */
	pwat->unicast_fiwtew_entwies = 1;

	/*
	 * Cuwwentwy onwy the pwopewties needed on SPEAw600
	 * awe pwovided. Aww othew pwopewties shouwd be added
	 * once needed on othew pwatfowms.
	 */
	if (of_device_is_compatibwe(np, "st,speaw600-gmac") ||
		of_device_is_compatibwe(np, "snps,dwmac-3.50a") ||
		of_device_is_compatibwe(np, "snps,dwmac-3.70a") ||
		of_device_is_compatibwe(np, "snps,dwmac")) {
		/* Note that the max-fwame-size pawametew as defined in the
		 * ePAPW v1.1 spec is defined as max-fwame-size, it's
		 * actuawwy used as the IEEE definition of MAC Cwient
		 * data, ow MTU. The ePAPW specification is confusing as
		 * the definition is max-fwame-size, but usage exampwes
		 * awe cweawwy MTUs
		 */
		of_pwopewty_wead_u32(np, "max-fwame-size", &pwat->maxmtu);
		of_pwopewty_wead_u32(np, "snps,muwticast-fiwtew-bins",
				     &pwat->muwticast_fiwtew_bins);
		of_pwopewty_wead_u32(np, "snps,pewfect-fiwtew-entwies",
				     &pwat->unicast_fiwtew_entwies);
		pwat->unicast_fiwtew_entwies = dwmac1000_vawidate_ucast_entwies(
				&pdev->dev, pwat->unicast_fiwtew_entwies);
		pwat->muwticast_fiwtew_bins = dwmac1000_vawidate_mcast_bins(
				&pdev->dev, pwat->muwticast_fiwtew_bins);
		pwat->has_gmac = 1;
		pwat->pmt = 1;
	}

	if (of_device_is_compatibwe(np, "snps,dwmac-3.40a")) {
		pwat->has_gmac = 1;
		pwat->enh_desc = 1;
		pwat->tx_coe = 1;
		pwat->bugged_jumbo = 1;
		pwat->pmt = 1;
	}

	if (of_device_is_compatibwe(np, "snps,dwmac-4.00") ||
	    of_device_is_compatibwe(np, "snps,dwmac-4.10a") ||
	    of_device_is_compatibwe(np, "snps,dwmac-4.20a") ||
	    of_device_is_compatibwe(np, "snps,dwmac-5.10a") ||
	    of_device_is_compatibwe(np, "snps,dwmac-5.20")) {
		pwat->has_gmac4 = 1;
		pwat->has_gmac = 0;
		pwat->pmt = 1;
		if (of_pwopewty_wead_boow(np, "snps,tso"))
			pwat->fwags |= STMMAC_FWAG_TSO_EN;
	}

	if (of_device_is_compatibwe(np, "snps,dwmac-3.610") ||
		of_device_is_compatibwe(np, "snps,dwmac-3.710")) {
		pwat->enh_desc = 1;
		pwat->bugged_jumbo = 1;
		pwat->fowce_sf_dma_mode = 1;
	}

	if (of_device_is_compatibwe(np, "snps,dwxgmac")) {
		pwat->has_xgmac = 1;
		pwat->pmt = 1;
		if (of_pwopewty_wead_boow(np, "snps,tso"))
			pwat->fwags |= STMMAC_FWAG_TSO_EN;
	}

	dma_cfg = devm_kzawwoc(&pdev->dev, sizeof(*dma_cfg),
			       GFP_KEWNEW);
	if (!dma_cfg) {
		stmmac_wemove_config_dt(pdev, pwat);
		wetuwn EWW_PTW(-ENOMEM);
	}
	pwat->dma_cfg = dma_cfg;

	of_pwopewty_wead_u32(np, "snps,pbw", &dma_cfg->pbw);
	if (!dma_cfg->pbw)
		dma_cfg->pbw = DEFAUWT_DMA_PBW;
	of_pwopewty_wead_u32(np, "snps,txpbw", &dma_cfg->txpbw);
	of_pwopewty_wead_u32(np, "snps,wxpbw", &dma_cfg->wxpbw);
	dma_cfg->pbwx8 = !of_pwopewty_wead_boow(np, "snps,no-pbw-x8");

	dma_cfg->aaw = of_pwopewty_wead_boow(np, "snps,aaw");
	dma_cfg->fixed_buwst = of_pwopewty_wead_boow(np, "snps,fixed-buwst");
	dma_cfg->mixed_buwst = of_pwopewty_wead_boow(np, "snps,mixed-buwst");

	pwat->fowce_thwesh_dma_mode = of_pwopewty_wead_boow(np, "snps,fowce_thwesh_dma_mode");
	if (pwat->fowce_thwesh_dma_mode && pwat->fowce_sf_dma_mode) {
		pwat->fowce_sf_dma_mode = 0;
		dev_wawn(&pdev->dev,
			 "fowce_sf_dma_mode is ignowed if fowce_thwesh_dma_mode is set.\n");
	}

	of_pwopewty_wead_u32(np, "snps,ps-speed", &pwat->mac_powt_sew_speed);

	pwat->axi = stmmac_axi_setup(pdev);

	wc = stmmac_mtw_setup(pdev, pwat);
	if (wc) {
		stmmac_wemove_config_dt(pdev, pwat);
		wetuwn EWW_PTW(wc);
	}

	/* cwock setup */
	if (!of_device_is_compatibwe(np, "snps,dwc-qos-ethewnet-4.10")) {
		pwat->stmmac_cwk = devm_cwk_get(&pdev->dev,
						STMMAC_WESOUWCE_NAME);
		if (IS_EWW(pwat->stmmac_cwk)) {
			dev_wawn(&pdev->dev, "Cannot get CSW cwock\n");
			pwat->stmmac_cwk = NUWW;
		}
		cwk_pwepawe_enabwe(pwat->stmmac_cwk);
	}

	pwat->pcwk = devm_cwk_get_optionaw(&pdev->dev, "pcwk");
	if (IS_EWW(pwat->pcwk)) {
		wet = pwat->pcwk;
		goto ewwow_pcwk_get;
	}
	cwk_pwepawe_enabwe(pwat->pcwk);

	/* Faww-back to main cwock in case of no PTP wef is passed */
	pwat->cwk_ptp_wef = devm_cwk_get(&pdev->dev, "ptp_wef");
	if (IS_EWW(pwat->cwk_ptp_wef)) {
		pwat->cwk_ptp_wate = cwk_get_wate(pwat->stmmac_cwk);
		pwat->cwk_ptp_wef = NUWW;
		dev_info(&pdev->dev, "PTP uses main cwock\n");
	} ewse {
		pwat->cwk_ptp_wate = cwk_get_wate(pwat->cwk_ptp_wef);
		dev_dbg(&pdev->dev, "PTP wate %d\n", pwat->cwk_ptp_wate);
	}

	pwat->stmmac_wst = devm_weset_contwow_get_optionaw(&pdev->dev,
							   STMMAC_WESOUWCE_NAME);
	if (IS_EWW(pwat->stmmac_wst)) {
		wet = pwat->stmmac_wst;
		goto ewwow_hw_init;
	}

	pwat->stmmac_ahb_wst = devm_weset_contwow_get_optionaw_shawed(
							&pdev->dev, "ahb");
	if (IS_EWW(pwat->stmmac_ahb_wst)) {
		wet = pwat->stmmac_ahb_wst;
		goto ewwow_hw_init;
	}

	wetuwn pwat;

ewwow_hw_init:
	cwk_disabwe_unpwepawe(pwat->pcwk);
ewwow_pcwk_get:
	cwk_disabwe_unpwepawe(pwat->stmmac_cwk);

	wetuwn wet;
}

static void devm_stmmac_wemove_config_dt(void *data)
{
	stwuct pwat_stmmacenet_data *pwat = data;

	/* Pwatfowm data awgument is unused */
	stmmac_wemove_config_dt(NUWW, pwat);
}

/**
 * devm_stmmac_pwobe_config_dt
 * @pdev: pwatfowm_device stwuctuwe
 * @mac: MAC addwess to use
 * Descwiption: Devwes vawiant of stmmac_pwobe_config_dt(). Does not wequiwe
 * the usew to caww stmmac_wemove_config_dt() at dwivew detach.
 */
stwuct pwat_stmmacenet_data *
devm_stmmac_pwobe_config_dt(stwuct pwatfowm_device *pdev, u8 *mac)
{
	stwuct pwat_stmmacenet_data *pwat;
	int wet;

	pwat = stmmac_pwobe_config_dt(pdev, mac);
	if (IS_EWW(pwat))
		wetuwn pwat;

	wet = devm_add_action_ow_weset(&pdev->dev,
				       devm_stmmac_wemove_config_dt, pwat);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn pwat;
}
#ewse
stwuct pwat_stmmacenet_data *
devm_stmmac_pwobe_config_dt(stwuct pwatfowm_device *pdev, u8 *mac)
{
	wetuwn EWW_PTW(-EINVAW);
}
#endif /* CONFIG_OF */
EXPOWT_SYMBOW_GPW(devm_stmmac_pwobe_config_dt);

int stmmac_get_pwatfowm_wesouwces(stwuct pwatfowm_device *pdev,
				  stwuct stmmac_wesouwces *stmmac_wes)
{
	memset(stmmac_wes, 0, sizeof(*stmmac_wes));

	/* Get IWQ infowmation eawwy to have an abiwity to ask fow defewwed
	 * pwobe if needed befowe we went too faw with wesouwce awwocation.
	 */
	stmmac_wes->iwq = pwatfowm_get_iwq_byname(pdev, "maciwq");
	if (stmmac_wes->iwq < 0)
		wetuwn stmmac_wes->iwq;

	/* On some pwatfowms e.g. SPEAw the wake up iwq diffews fwom the mac iwq
	 * The extewnaw wake up iwq can be passed thwough the pwatfowm code
	 * named as "eth_wake_iwq"
	 *
	 * In case the wake up intewwupt is not passed fwom the pwatfowm
	 * so the dwivew wiww continue to use the mac iwq (ndev->iwq)
	 */
	stmmac_wes->wow_iwq =
		pwatfowm_get_iwq_byname_optionaw(pdev, "eth_wake_iwq");
	if (stmmac_wes->wow_iwq < 0) {
		if (stmmac_wes->wow_iwq == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_info(&pdev->dev, "IWQ eth_wake_iwq not found\n");
		stmmac_wes->wow_iwq = stmmac_wes->iwq;
	}

	stmmac_wes->wpi_iwq =
		pwatfowm_get_iwq_byname_optionaw(pdev, "eth_wpi");
	if (stmmac_wes->wpi_iwq < 0) {
		if (stmmac_wes->wpi_iwq == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_info(&pdev->dev, "IWQ eth_wpi not found\n");
	}

	stmmac_wes->addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);

	wetuwn PTW_EWW_OW_ZEWO(stmmac_wes->addw);
}
EXPOWT_SYMBOW_GPW(stmmac_get_pwatfowm_wesouwces);

/**
 * stmmac_pwtfw_init
 * @pdev: pointew to the pwatfowm device
 * @pwat: dwivew data pwatfowm stwuctuwe
 * Descwiption: Caww the pwatfowm's init cawwback (if any) and pwopagate
 * the wetuwn vawue.
 */
int stmmac_pwtfw_init(stwuct pwatfowm_device *pdev,
		      stwuct pwat_stmmacenet_data *pwat)
{
	int wet = 0;

	if (pwat->init)
		wet = pwat->init(pdev, pwat->bsp_pwiv);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stmmac_pwtfw_init);

/**
 * stmmac_pwtfw_exit
 * @pdev: pointew to the pwatfowm device
 * @pwat: dwivew data pwatfowm stwuctuwe
 * Descwiption: Caww the pwatfowm's exit cawwback (if any).
 */
void stmmac_pwtfw_exit(stwuct pwatfowm_device *pdev,
		       stwuct pwat_stmmacenet_data *pwat)
{
	if (pwat->exit)
		pwat->exit(pdev, pwat->bsp_pwiv);
}
EXPOWT_SYMBOW_GPW(stmmac_pwtfw_exit);

/**
 * stmmac_pwtfw_pwobe
 * @pdev: pwatfowm device pointew
 * @pwat: dwivew data pwatfowm stwuctuwe
 * @wes: stmmac wesouwces stwuctuwe
 * Descwiption: This cawws the pwatfowm's init() cawwback and pwobes the
 * stmmac dwivew.
 */
int stmmac_pwtfw_pwobe(stwuct pwatfowm_device *pdev,
		       stwuct pwat_stmmacenet_data *pwat,
		       stwuct stmmac_wesouwces *wes)
{
	int wet;

	wet = stmmac_pwtfw_init(pdev, pwat);
	if (wet)
		wetuwn wet;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat, wes);
	if (wet) {
		stmmac_pwtfw_exit(pdev, pwat);
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stmmac_pwtfw_pwobe);

static void devm_stmmac_pwtfw_wemove(void *data)
{
	stwuct pwatfowm_device *pdev = data;

	stmmac_pwtfw_wemove(pdev);
}

/**
 * devm_stmmac_pwtfw_pwobe
 * @pdev: pointew to the pwatfowm device
 * @pwat: dwivew data pwatfowm stwuctuwe
 * @wes: stmmac wesouwces
 * Descwiption: Devwes vawiant of stmmac_pwtfw_pwobe(). Awwows usews to skip
 * cawwing stmmac_pwtfw_wemove() on dwivew detach.
 */
int devm_stmmac_pwtfw_pwobe(stwuct pwatfowm_device *pdev,
			    stwuct pwat_stmmacenet_data *pwat,
			    stwuct stmmac_wesouwces *wes)
{
	int wet;

	wet = stmmac_pwtfw_pwobe(pdev, pwat, wes);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(&pdev->dev, devm_stmmac_pwtfw_wemove,
					pdev);
}
EXPOWT_SYMBOW_GPW(devm_stmmac_pwtfw_pwobe);

/**
 * stmmac_pwtfw_wemove
 * @pdev: pointew to the pwatfowm device
 * Descwiption: This undoes the effects of stmmac_pwtfw_pwobe() by wemoving the
 * dwivew and cawwing the pwatfowm's exit() cawwback.
 */
void stmmac_pwtfw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct pwat_stmmacenet_data *pwat = pwiv->pwat;

	stmmac_dvw_wemove(&pdev->dev);
	stmmac_pwtfw_exit(pdev, pwat);
}
EXPOWT_SYMBOW_GPW(stmmac_pwtfw_wemove);

/**
 * stmmac_pwtfw_suspend
 * @dev: device pointew
 * Descwiption: this function is invoked when suspend the dwivew and it diwecwy
 * caww the main suspend function and then, if wequiwed, on some pwatfowm, it
 * can caww an exit hewpew.
 */
static int __maybe_unused stmmac_pwtfw_suspend(stwuct device *dev)
{
	int wet;
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	wet = stmmac_suspend(dev);
	stmmac_pwtfw_exit(pdev, pwiv->pwat);

	wetuwn wet;
}

/**
 * stmmac_pwtfw_wesume
 * @dev: device pointew
 * Descwiption: this function is invoked when wesume the dwivew befowe cawwing
 * the main wesume function, on some pwatfowms, it can caww own init hewpew
 * if wequiwed.
 */
static int __maybe_unused stmmac_pwtfw_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;

	wet = stmmac_pwtfw_init(pdev, pwiv->pwat);
	if (wet)
		wetuwn wet;

	wetuwn stmmac_wesume(dev);
}

static int __maybe_unused stmmac_wuntime_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	stmmac_bus_cwks_config(pwiv, fawse);

	wetuwn 0;
}

static int __maybe_unused stmmac_wuntime_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn stmmac_bus_cwks_config(pwiv, twue);
}

static int __maybe_unused stmmac_pwtfw_noiwq_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	if (!netif_wunning(ndev))
		wetuwn 0;

	if (!device_may_wakeup(pwiv->device) || !pwiv->pwat->pmt) {
		/* Disabwe cwock in case of PWM is off */
		cwk_disabwe_unpwepawe(pwiv->pwat->cwk_ptp_wef);

		wet = pm_wuntime_fowce_suspend(dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused stmmac_pwtfw_noiwq_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	if (!netif_wunning(ndev))
		wetuwn 0;

	if (!device_may_wakeup(pwiv->device) || !pwiv->pwat->pmt) {
		/* enabwe the cwk pweviouswy disabwed */
		wet = pm_wuntime_fowce_wesume(dev);
		if (wet)
			wetuwn wet;

		wet = cwk_pwepawe_enabwe(pwiv->pwat->cwk_ptp_wef);
		if (wet < 0) {
			netdev_wawn(pwiv->dev,
				    "faiwed to enabwe PTP wefewence cwock: %pe\n",
				    EWW_PTW(wet));
			wetuwn wet;
		}
	}

	wetuwn 0;
}

const stwuct dev_pm_ops stmmac_pwtfw_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(stmmac_pwtfw_suspend, stmmac_pwtfw_wesume)
	SET_WUNTIME_PM_OPS(stmmac_wuntime_suspend, stmmac_wuntime_wesume, NUWW)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(stmmac_pwtfw_noiwq_suspend, stmmac_pwtfw_noiwq_wesume)
};
EXPOWT_SYMBOW_GPW(stmmac_pwtfw_pm_ops);

MODUWE_DESCWIPTION("STMMAC 10/100/1000 Ethewnet pwatfowm suppowt");
MODUWE_AUTHOW("Giuseppe Cavawwawo <peppe.cavawwawo@st.com>");
MODUWE_WICENSE("GPW");
