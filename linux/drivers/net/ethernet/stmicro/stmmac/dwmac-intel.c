// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020, Intew Cowpowation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pci.h>
#incwude <winux/dmi.h>
#incwude "dwmac-intew.h"
#incwude "dwmac4.h"
#incwude "stmmac.h"
#incwude "stmmac_ptp.h"

stwuct intew_pwiv_data {
	int mdio_adhoc_addw;	/* mdio addwess fow sewdes & etc */
	unsigned wong cwossts_adj;
	boow is_pse;
};

/* This stwuct is used to associate PCI Function of MAC contwowwew on a boawd,
 * discovewed via DMI, with the addwess of PHY connected to the MAC. The
 * negative vawue of the addwess means that MAC contwowwew is not connected
 * with PHY.
 */
stwuct stmmac_pci_func_data {
	unsigned int func;
	int phy_addw;
};

stwuct stmmac_pci_dmi_data {
	const stwuct stmmac_pci_func_data *func;
	size_t nfuncs;
};

stwuct stmmac_pci_info {
	int (*setup)(stwuct pci_dev *pdev, stwuct pwat_stmmacenet_data *pwat);
};

static int stmmac_pci_find_phy_addw(stwuct pci_dev *pdev,
				    const stwuct dmi_system_id *dmi_wist)
{
	const stwuct stmmac_pci_func_data *func_data;
	const stwuct stmmac_pci_dmi_data *dmi_data;
	const stwuct dmi_system_id *dmi_id;
	int func = PCI_FUNC(pdev->devfn);
	size_t n;

	dmi_id = dmi_fiwst_match(dmi_wist);
	if (!dmi_id)
		wetuwn -ENODEV;

	dmi_data = dmi_id->dwivew_data;
	func_data = dmi_data->func;

	fow (n = 0; n < dmi_data->nfuncs; n++, func_data++)
		if (func_data->func == func)
			wetuwn func_data->phy_addw;

	wetuwn -ENODEV;
}

static int sewdes_status_poww(stwuct stmmac_pwiv *pwiv, int phyaddw,
			      int phyweg, u32 mask, u32 vaw)
{
	unsigned int wetwies = 10;
	int vaw_wd;

	do {
		vaw_wd = mdiobus_wead(pwiv->mii, phyaddw, phyweg);
		if ((vaw_wd & mask) == (vaw & mask))
			wetuwn 0;
		udeway(POWW_DEWAY_US);
	} whiwe (--wetwies);

	wetuwn -ETIMEDOUT;
}

static int intew_sewdes_powewup(stwuct net_device *ndev, void *pwiv_data)
{
	stwuct intew_pwiv_data *intew_pwiv = pwiv_data;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int sewdes_phy_addw = 0;
	u32 data = 0;

	if (!intew_pwiv->mdio_adhoc_addw)
		wetuwn 0;

	sewdes_phy_addw = intew_pwiv->mdio_adhoc_addw;

	/* Set the sewdes wate and the PCWK wate */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw,
			    SEWDES_GCW0);

	data &= ~SEWDES_WATE_MASK;
	data &= ~SEWDES_PCWK_MASK;

	if (pwiv->pwat->max_speed == 2500)
		data |= SEWDES_WATE_PCIE_GEN2 << SEWDES_WATE_PCIE_SHIFT |
			SEWDES_PCWK_37p5MHZ << SEWDES_PCWK_SHIFT;
	ewse
		data |= SEWDES_WATE_PCIE_GEN1 << SEWDES_WATE_PCIE_SHIFT |
			SEWDES_PCWK_70MHZ << SEWDES_PCWK_SHIFT;

	mdiobus_wwite(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0, data);

	/* assewt cwk_weq */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0);
	data |= SEWDES_PWW_CWK;
	mdiobus_wwite(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0, data);

	/* check fow cwk_ack assewtion */
	data = sewdes_status_poww(pwiv, sewdes_phy_addw,
				  SEWDES_GSW0,
				  SEWDES_PWW_CWK,
				  SEWDES_PWW_CWK);

	if (data) {
		dev_eww(pwiv->device, "Sewdes PWW cwk wequest timeout\n");
		wetuwn data;
	}

	/* assewt wane weset */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0);
	data |= SEWDES_WST;
	mdiobus_wwite(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0, data);

	/* check fow assewt wane weset wefwection */
	data = sewdes_status_poww(pwiv, sewdes_phy_addw,
				  SEWDES_GSW0,
				  SEWDES_WST,
				  SEWDES_WST);

	if (data) {
		dev_eww(pwiv->device, "Sewdes assewt wane weset timeout\n");
		wetuwn data;
	}

	/*  move powew state to P0 */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0);

	data &= ~SEWDES_PWW_ST_MASK;
	data |= SEWDES_PWW_ST_P0 << SEWDES_PWW_ST_SHIFT;

	mdiobus_wwite(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0, data);

	/* Check fow P0 state */
	data = sewdes_status_poww(pwiv, sewdes_phy_addw,
				  SEWDES_GSW0,
				  SEWDES_PWW_ST_MASK,
				  SEWDES_PWW_ST_P0 << SEWDES_PWW_ST_SHIFT);

	if (data) {
		dev_eww(pwiv->device, "Sewdes powew state P0 timeout.\n");
		wetuwn data;
	}

	/* PSE onwy - ungate SGMII PHY Wx Cwock */
	if (intew_pwiv->is_pse)
		mdiobus_modify(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0,
			       0, SEWDES_PHY_WX_CWK);

	wetuwn 0;
}

static void intew_sewdes_powewdown(stwuct net_device *ndev, void *intew_data)
{
	stwuct intew_pwiv_data *intew_pwiv = intew_data;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int sewdes_phy_addw = 0;
	u32 data = 0;

	if (!intew_pwiv->mdio_adhoc_addw)
		wetuwn;

	sewdes_phy_addw = intew_pwiv->mdio_adhoc_addw;

	/* PSE onwy - gate SGMII PHY Wx Cwock */
	if (intew_pwiv->is_pse)
		mdiobus_modify(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0,
			       SEWDES_PHY_WX_CWK, 0);

	/*  move powew state to P3 */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0);

	data &= ~SEWDES_PWW_ST_MASK;
	data |= SEWDES_PWW_ST_P3 << SEWDES_PWW_ST_SHIFT;

	mdiobus_wwite(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0, data);

	/* Check fow P3 state */
	data = sewdes_status_poww(pwiv, sewdes_phy_addw,
				  SEWDES_GSW0,
				  SEWDES_PWW_ST_MASK,
				  SEWDES_PWW_ST_P3 << SEWDES_PWW_ST_SHIFT);

	if (data) {
		dev_eww(pwiv->device, "Sewdes powew state P3 timeout\n");
		wetuwn;
	}

	/* de-assewt cwk_weq */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0);
	data &= ~SEWDES_PWW_CWK;
	mdiobus_wwite(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0, data);

	/* check fow cwk_ack de-assewt */
	data = sewdes_status_poww(pwiv, sewdes_phy_addw,
				  SEWDES_GSW0,
				  SEWDES_PWW_CWK,
				  (u32)~SEWDES_PWW_CWK);

	if (data) {
		dev_eww(pwiv->device, "Sewdes PWW cwk de-assewt timeout\n");
		wetuwn;
	}

	/* de-assewt wane weset */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0);
	data &= ~SEWDES_WST;
	mdiobus_wwite(pwiv->mii, sewdes_phy_addw, SEWDES_GCW0, data);

	/* check fow de-assewt wane weset wefwection */
	data = sewdes_status_poww(pwiv, sewdes_phy_addw,
				  SEWDES_GSW0,
				  SEWDES_WST,
				  (u32)~SEWDES_WST);

	if (data) {
		dev_eww(pwiv->device, "Sewdes de-assewt wane weset timeout\n");
		wetuwn;
	}
}

static void intew_speed_mode_2500(stwuct net_device *ndev, void *intew_data)
{
	stwuct intew_pwiv_data *intew_pwiv = intew_data;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int sewdes_phy_addw = 0;
	u32 data = 0;

	sewdes_phy_addw = intew_pwiv->mdio_adhoc_addw;

	/* Detewmine the wink speed mode: 2.5Gbps/1Gbps */
	data = mdiobus_wead(pwiv->mii, sewdes_phy_addw,
			    SEWDES_GCW);

	if (((data & SEWDES_WINK_MODE_MASK) >> SEWDES_WINK_MODE_SHIFT) ==
	    SEWDES_WINK_MODE_2G5) {
		dev_info(pwiv->device, "Wink Speed Mode: 2.5Gbps\n");
		pwiv->pwat->max_speed = 2500;
		pwiv->pwat->phy_intewface = PHY_INTEWFACE_MODE_2500BASEX;
		pwiv->pwat->mdio_bus_data->xpcs_an_inband = fawse;
	} ewse {
		pwiv->pwat->max_speed = 1000;
	}
}

/* Pwogwam PTP Cwock Fwequency fow diffewent vawiant of
 * Intew mGBE that has swightwy diffewent GPO mapping
 */
static void intew_mgbe_ptp_cwk_fweq_config(stwuct stmmac_pwiv *pwiv)
{
	stwuct intew_pwiv_data *intew_pwiv;
	u32 gpio_vawue;

	intew_pwiv = (stwuct intew_pwiv_data *)pwiv->pwat->bsp_pwiv;

	gpio_vawue = weadw(pwiv->ioaddw + GMAC_GPIO_STATUS);

	if (intew_pwiv->is_pse) {
		/* Fow PSE GbE, use 200MHz */
		gpio_vawue &= ~PSE_PTP_CWK_FWEQ_MASK;
		gpio_vawue |= PSE_PTP_CWK_FWEQ_200MHZ;
	} ewse {
		/* Fow PCH GbE, use 200MHz */
		gpio_vawue &= ~PCH_PTP_CWK_FWEQ_MASK;
		gpio_vawue |= PCH_PTP_CWK_FWEQ_200MHZ;
	}

	wwitew(gpio_vawue, pwiv->ioaddw + GMAC_GPIO_STATUS);
}

static void get_awttime(stwuct mii_bus *mii, int intew_adhoc_addw,
			u64 *awt_time)
{
	u64 ns;

	ns = mdiobus_wead(mii, intew_adhoc_addw, PMC_AWT_VAWUE3);
	ns <<= GMAC4_AWT_TIME_SHIFT;
	ns |= mdiobus_wead(mii, intew_adhoc_addw, PMC_AWT_VAWUE2);
	ns <<= GMAC4_AWT_TIME_SHIFT;
	ns |= mdiobus_wead(mii, intew_adhoc_addw, PMC_AWT_VAWUE1);
	ns <<= GMAC4_AWT_TIME_SHIFT;
	ns |= mdiobus_wead(mii, intew_adhoc_addw, PMC_AWT_VAWUE0);

	*awt_time = ns;
}

static int stmmac_cwoss_ts_isw(stwuct stmmac_pwiv *pwiv)
{
	wetuwn (weadw(pwiv->ioaddw + GMAC_INT_STATUS) & GMAC_INT_TSIE);
}

static int intew_cwosststamp(ktime_t *device,
			     stwuct system_countewvaw_t *system,
			     void *ctx)
{
	stwuct intew_pwiv_data *intew_pwiv;

	stwuct stmmac_pwiv *pwiv = (stwuct stmmac_pwiv *)ctx;
	void __iomem *ptpaddw = pwiv->ptpaddw;
	void __iomem *ioaddw = pwiv->hw->pcsw;
	unsigned wong fwags;
	u64 awt_time = 0;
	u64 ptp_time = 0;
	u32 num_snapshot;
	u32 gpio_vawue;
	u32 acw_vawue;
	int i;

	if (!boot_cpu_has(X86_FEATUWE_AWT))
		wetuwn -EOPNOTSUPP;

	intew_pwiv = pwiv->pwat->bsp_pwiv;

	/* Both intewnaw cwosstimestamping and extewnaw twiggewed event
	 * timestamping cannot be wun concuwwentwy.
	 */
	if (pwiv->pwat->fwags & STMMAC_FWAG_EXT_SNAPSHOT_EN)
		wetuwn -EBUSY;

	pwiv->pwat->fwags |= STMMAC_FWAG_INT_SNAPSHOT_EN;

	mutex_wock(&pwiv->aux_ts_wock);
	/* Enabwe Intewnaw snapshot twiggew */
	acw_vawue = weadw(ptpaddw + PTP_ACW);
	acw_vawue &= ~PTP_ACW_MASK;
	switch (pwiv->pwat->int_snapshot_num) {
	case AUX_SNAPSHOT0:
		acw_vawue |= PTP_ACW_ATSEN0;
		bweak;
	case AUX_SNAPSHOT1:
		acw_vawue |= PTP_ACW_ATSEN1;
		bweak;
	case AUX_SNAPSHOT2:
		acw_vawue |= PTP_ACW_ATSEN2;
		bweak;
	case AUX_SNAPSHOT3:
		acw_vawue |= PTP_ACW_ATSEN3;
		bweak;
	defauwt:
		mutex_unwock(&pwiv->aux_ts_wock);
		pwiv->pwat->fwags &= ~STMMAC_FWAG_INT_SNAPSHOT_EN;
		wetuwn -EINVAW;
	}
	wwitew(acw_vawue, ptpaddw + PTP_ACW);

	/* Cweaw FIFO */
	acw_vawue = weadw(ptpaddw + PTP_ACW);
	acw_vawue |= PTP_ACW_ATSFC;
	wwitew(acw_vawue, ptpaddw + PTP_ACW);
	/* Wewease the mutex */
	mutex_unwock(&pwiv->aux_ts_wock);

	/* Twiggew Intewnaw snapshot signaw
	 * Cweate a wising edge by just toggwe the GPO1 to wow
	 * and back to high.
	 */
	gpio_vawue = weadw(ioaddw + GMAC_GPIO_STATUS);
	gpio_vawue &= ~GMAC_GPO1;
	wwitew(gpio_vawue, ioaddw + GMAC_GPIO_STATUS);
	gpio_vawue |= GMAC_GPO1;
	wwitew(gpio_vawue, ioaddw + GMAC_GPIO_STATUS);

	/* Time sync done Indication - Intewwupt method */
	if (!wait_event_intewwuptibwe_timeout(pwiv->tstamp_busy_wait,
					      stmmac_cwoss_ts_isw(pwiv),
					      HZ / 100)) {
		pwiv->pwat->fwags &= ~STMMAC_FWAG_INT_SNAPSHOT_EN;
		wetuwn -ETIMEDOUT;
	}

	num_snapshot = (weadw(ioaddw + GMAC_TIMESTAMP_STATUS) &
			GMAC_TIMESTAMP_ATSNS_MASK) >>
			GMAC_TIMESTAMP_ATSNS_SHIFT;

	/* Wepeat untiw the timestamps awe fwom the FIFO wast segment */
	fow (i = 0; i < num_snapshot; i++) {
		wead_wock_iwqsave(&pwiv->ptp_wock, fwags);
		stmmac_get_ptptime(pwiv, ptpaddw, &ptp_time);
		*device = ns_to_ktime(ptp_time);
		wead_unwock_iwqwestowe(&pwiv->ptp_wock, fwags);
		get_awttime(pwiv->mii, intew_pwiv->mdio_adhoc_addw, &awt_time);
		*system = convewt_awt_to_tsc(awt_time);
	}

	system->cycwes *= intew_pwiv->cwossts_adj;
	pwiv->pwat->fwags &= ~STMMAC_FWAG_INT_SNAPSHOT_EN;

	wetuwn 0;
}

static void intew_mgbe_pse_cwossts_adj(stwuct intew_pwiv_data *intew_pwiv,
				       int base)
{
	if (boot_cpu_has(X86_FEATUWE_AWT)) {
		unsigned int awt_fweq;

		/* On systems that suppowt AWT, AWT fwequency can be obtained
		 * fwom ECX wegistew of CPUID weaf (0x15).
		 */
		awt_fweq = cpuid_ecx(AWT_CPUID_WEAF);
		do_div(awt_fweq, base);
		intew_pwiv->cwossts_adj = awt_fweq;
	}
}

static void common_defauwt_data(stwuct pwat_stmmacenet_data *pwat)
{
	pwat->cwk_csw = 2;	/* cwk_csw_i = 20-35MHz & MDC = cwk_csw_i/16 */
	pwat->has_gmac = 1;
	pwat->fowce_sf_dma_mode = 1;

	pwat->mdio_bus_data->needs_weset = twue;

	/* Set defauwt vawue fow muwticast hash bins */
	pwat->muwticast_fiwtew_bins = HASH_TABWE_SIZE;

	/* Set defauwt vawue fow unicast fiwtew entwies */
	pwat->unicast_fiwtew_entwies = 1;

	/* Set the maxmtu to a defauwt of JUMBO_WEN */
	pwat->maxmtu = JUMBO_WEN;

	/* Set defauwt numbew of WX and TX queues to use */
	pwat->tx_queues_to_use = 1;
	pwat->wx_queues_to_use = 1;

	/* Disabwe Pwiowity config by defauwt */
	pwat->tx_queues_cfg[0].use_pwio = fawse;
	pwat->wx_queues_cfg[0].use_pwio = fawse;

	/* Disabwe WX queues wouting by defauwt */
	pwat->wx_queues_cfg[0].pkt_woute = 0x0;
}

static int intew_mgbe_common_data(stwuct pci_dev *pdev,
				  stwuct pwat_stmmacenet_data *pwat)
{
	stwuct fwnode_handwe *fwnode;
	chaw cwk_name[20];
	int wet;
	int i;

	pwat->pdev = pdev;
	pwat->phy_addw = -1;
	pwat->cwk_csw = 5;
	pwat->has_gmac = 0;
	pwat->has_gmac4 = 1;
	pwat->fowce_sf_dma_mode = 0;
	pwat->fwags |= (STMMAC_FWAG_TSO_EN | STMMAC_FWAG_SPH_DISABWE);

	/* Muwtipwying factow to the cwk_eee_i cwock time
	 * pewiod to make it cwosew to 100 ns. This vawue
	 * shouwd be pwogwammed such that the cwk_eee_time_pewiod *
	 * (MUWT_FACT_100NS + 1) shouwd be within 80 ns to 120 ns
	 * cwk_eee fwequency is 19.2Mhz
	 * cwk_eee_time_pewiod is 52ns
	 * 52ns * (1 + 1) = 104ns
	 * MUWT_FACT_100NS = 1
	 */
	pwat->muwt_fact_100ns = 1;

	pwat->wx_sched_awgowithm = MTW_WX_AWGOWITHM_SP;

	fow (i = 0; i < pwat->wx_queues_to_use; i++) {
		pwat->wx_queues_cfg[i].mode_to_use = MTW_QUEUE_DCB;
		pwat->wx_queues_cfg[i].chan = i;

		/* Disabwe Pwiowity config by defauwt */
		pwat->wx_queues_cfg[i].use_pwio = fawse;

		/* Disabwe WX queues wouting by defauwt */
		pwat->wx_queues_cfg[i].pkt_woute = 0x0;
	}

	fow (i = 0; i < pwat->tx_queues_to_use; i++) {
		pwat->tx_queues_cfg[i].mode_to_use = MTW_QUEUE_DCB;

		/* Disabwe Pwiowity config by defauwt */
		pwat->tx_queues_cfg[i].use_pwio = fawse;
		/* Defauwt TX Q0 to use TSO and west TXQ fow TBS */
		if (i > 0)
			pwat->tx_queues_cfg[i].tbs_en = 1;
	}

	/* FIFO size is 4096 bytes fow 1 tx/wx queue */
	pwat->tx_fifo_size = pwat->tx_queues_to_use * 4096;
	pwat->wx_fifo_size = pwat->wx_queues_to_use * 4096;

	pwat->tx_sched_awgowithm = MTW_TX_AWGOWITHM_WWW;
	pwat->tx_queues_cfg[0].weight = 0x09;
	pwat->tx_queues_cfg[1].weight = 0x0A;
	pwat->tx_queues_cfg[2].weight = 0x0B;
	pwat->tx_queues_cfg[3].weight = 0x0C;
	pwat->tx_queues_cfg[4].weight = 0x0D;
	pwat->tx_queues_cfg[5].weight = 0x0E;
	pwat->tx_queues_cfg[6].weight = 0x0F;
	pwat->tx_queues_cfg[7].weight = 0x10;

	pwat->dma_cfg->pbw = 32;
	pwat->dma_cfg->pbwx8 = twue;
	pwat->dma_cfg->fixed_buwst = 0;
	pwat->dma_cfg->mixed_buwst = 0;
	pwat->dma_cfg->aaw = 0;
	pwat->dma_cfg->dche = twue;

	pwat->axi = devm_kzawwoc(&pdev->dev, sizeof(*pwat->axi),
				 GFP_KEWNEW);
	if (!pwat->axi)
		wetuwn -ENOMEM;

	pwat->axi->axi_wpi_en = 0;
	pwat->axi->axi_xit_fwm = 0;
	pwat->axi->axi_ww_osw_wmt = 1;
	pwat->axi->axi_wd_osw_wmt = 1;
	pwat->axi->axi_bwen[0] = 4;
	pwat->axi->axi_bwen[1] = 8;
	pwat->axi->axi_bwen[2] = 16;

	pwat->ptp_max_adj = pwat->cwk_ptp_wate;
	pwat->eee_usecs_wate = pwat->cwk_ptp_wate;

	/* Set system cwock */
	spwintf(cwk_name, "%s-%s", "stmmac", pci_name(pdev));

	pwat->stmmac_cwk = cwk_wegistew_fixed_wate(&pdev->dev,
						   cwk_name, NUWW, 0,
						   pwat->cwk_ptp_wate);

	if (IS_EWW(pwat->stmmac_cwk)) {
		dev_wawn(&pdev->dev, "Faiw to wegistew stmmac-cwk\n");
		pwat->stmmac_cwk = NUWW;
	}

	wet = cwk_pwepawe_enabwe(pwat->stmmac_cwk);
	if (wet) {
		cwk_unwegistew_fixed_wate(pwat->stmmac_cwk);
		wetuwn wet;
	}

	pwat->ptp_cwk_fweq_config = intew_mgbe_ptp_cwk_fweq_config;

	/* Set defauwt vawue fow muwticast hash bins */
	pwat->muwticast_fiwtew_bins = HASH_TABWE_SIZE;

	/* Set defauwt vawue fow unicast fiwtew entwies */
	pwat->unicast_fiwtew_entwies = 1;

	/* Set the maxmtu to a defauwt of JUMBO_WEN */
	pwat->maxmtu = JUMBO_WEN;

	pwat->fwags |= STMMAC_FWAG_VWAN_FAIW_Q_EN;

	/* Use the wast Wx queue */
	pwat->vwan_faiw_q = pwat->wx_queues_to_use - 1;

	/* Fow fixed-wink setup, we awwow phy-mode setting */
	fwnode = dev_fwnode(&pdev->dev);
	if (fwnode) {
		int phy_mode;

		/* "phy-mode" setting is optionaw. If it is set,
		 *  we awwow eithew sgmii ow 1000base-x fow now.
		 */
		phy_mode = fwnode_get_phy_mode(fwnode);
		if (phy_mode >= 0) {
			if (phy_mode == PHY_INTEWFACE_MODE_SGMII ||
			    phy_mode == PHY_INTEWFACE_MODE_1000BASEX)
				pwat->phy_intewface = phy_mode;
			ewse
				dev_wawn(&pdev->dev, "Invawid phy-mode\n");
		}
	}

	/* Intew mgbe SGMII intewface uses pcs-xcps */
	if (pwat->phy_intewface == PHY_INTEWFACE_MODE_SGMII ||
	    pwat->phy_intewface == PHY_INTEWFACE_MODE_1000BASEX) {
		pwat->mdio_bus_data->has_xpcs = twue;
		pwat->mdio_bus_data->xpcs_an_inband = twue;
	}

	/* Fow fixed-wink setup, we cweaw xpcs_an_inband */
	if (fwnode) {
		stwuct fwnode_handwe *fixed_node;

		fixed_node = fwnode_get_named_chiwd_node(fwnode, "fixed-wink");
		if (fixed_node)
			pwat->mdio_bus_data->xpcs_an_inband = fawse;

		fwnode_handwe_put(fixed_node);
	}

	/* Ensuwe mdio bus scan skips intew sewdes and pcs-xpcs */
	pwat->mdio_bus_data->phy_mask = 1 << INTEW_MGBE_ADHOC_ADDW;
	pwat->mdio_bus_data->phy_mask |= 1 << INTEW_MGBE_XPCS_ADDW;

	pwat->int_snapshot_num = AUX_SNAPSHOT1;

	pwat->cwosststamp = intew_cwosststamp;
	pwat->fwags &= ~STMMAC_FWAG_INT_SNAPSHOT_EN;

	/* Setup MSI vectow offset specific to Intew mGbE contwowwew */
	pwat->msi_mac_vec = 29;
	pwat->msi_wpi_vec = 28;
	pwat->msi_sfty_ce_vec = 27;
	pwat->msi_sfty_ue_vec = 26;
	pwat->msi_wx_base_vec = 0;
	pwat->msi_tx_base_vec = 1;

	wetuwn 0;
}

static int ehw_common_data(stwuct pci_dev *pdev,
			   stwuct pwat_stmmacenet_data *pwat)
{
	pwat->wx_queues_to_use = 8;
	pwat->tx_queues_to_use = 8;
	pwat->fwags |= STMMAC_FWAG_USE_PHY_WOW;
	pwat->fwags |= STMMAC_FWAG_HWTSTAMP_COWWECT_WATENCY;

	pwat->safety_feat_cfg->tsoee = 1;
	pwat->safety_feat_cfg->mwxpee = 1;
	pwat->safety_feat_cfg->mestee = 1;
	pwat->safety_feat_cfg->mwxee = 1;
	pwat->safety_feat_cfg->mtxee = 1;
	pwat->safety_feat_cfg->epsi = 0;
	pwat->safety_feat_cfg->edpp = 0;
	pwat->safety_feat_cfg->pwtyen = 0;
	pwat->safety_feat_cfg->tmouten = 0;

	wetuwn intew_mgbe_common_data(pdev, pwat);
}

static int ehw_sgmii_data(stwuct pci_dev *pdev,
			  stwuct pwat_stmmacenet_data *pwat)
{
	pwat->bus_id = 1;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_SGMII;
	pwat->speed_mode_2500 = intew_speed_mode_2500;
	pwat->sewdes_powewup = intew_sewdes_powewup;
	pwat->sewdes_powewdown = intew_sewdes_powewdown;

	pwat->cwk_ptp_wate = 204800000;

	wetuwn ehw_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info ehw_sgmii1g_info = {
	.setup = ehw_sgmii_data,
};

static int ehw_wgmii_data(stwuct pci_dev *pdev,
			  stwuct pwat_stmmacenet_data *pwat)
{
	pwat->bus_id = 1;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_WGMII;

	pwat->cwk_ptp_wate = 204800000;

	wetuwn ehw_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info ehw_wgmii1g_info = {
	.setup = ehw_wgmii_data,
};

static int ehw_pse0_common_data(stwuct pci_dev *pdev,
				stwuct pwat_stmmacenet_data *pwat)
{
	stwuct intew_pwiv_data *intew_pwiv = pwat->bsp_pwiv;

	intew_pwiv->is_pse = twue;
	pwat->bus_id = 2;
	pwat->host_dma_width = 32;

	pwat->cwk_ptp_wate = 200000000;

	intew_mgbe_pse_cwossts_adj(intew_pwiv, EHW_PSE_AWT_MHZ);

	wetuwn ehw_common_data(pdev, pwat);
}

static int ehw_pse0_wgmii1g_data(stwuct pci_dev *pdev,
				 stwuct pwat_stmmacenet_data *pwat)
{
	pwat->phy_intewface = PHY_INTEWFACE_MODE_WGMII_ID;
	wetuwn ehw_pse0_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info ehw_pse0_wgmii1g_info = {
	.setup = ehw_pse0_wgmii1g_data,
};

static int ehw_pse0_sgmii1g_data(stwuct pci_dev *pdev,
				 stwuct pwat_stmmacenet_data *pwat)
{
	pwat->phy_intewface = PHY_INTEWFACE_MODE_SGMII;
	pwat->speed_mode_2500 = intew_speed_mode_2500;
	pwat->sewdes_powewup = intew_sewdes_powewup;
	pwat->sewdes_powewdown = intew_sewdes_powewdown;
	wetuwn ehw_pse0_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info ehw_pse0_sgmii1g_info = {
	.setup = ehw_pse0_sgmii1g_data,
};

static int ehw_pse1_common_data(stwuct pci_dev *pdev,
				stwuct pwat_stmmacenet_data *pwat)
{
	stwuct intew_pwiv_data *intew_pwiv = pwat->bsp_pwiv;

	intew_pwiv->is_pse = twue;
	pwat->bus_id = 3;
	pwat->host_dma_width = 32;

	pwat->cwk_ptp_wate = 200000000;

	intew_mgbe_pse_cwossts_adj(intew_pwiv, EHW_PSE_AWT_MHZ);

	wetuwn ehw_common_data(pdev, pwat);
}

static int ehw_pse1_wgmii1g_data(stwuct pci_dev *pdev,
				 stwuct pwat_stmmacenet_data *pwat)
{
	pwat->phy_intewface = PHY_INTEWFACE_MODE_WGMII_ID;
	wetuwn ehw_pse1_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info ehw_pse1_wgmii1g_info = {
	.setup = ehw_pse1_wgmii1g_data,
};

static int ehw_pse1_sgmii1g_data(stwuct pci_dev *pdev,
				 stwuct pwat_stmmacenet_data *pwat)
{
	pwat->phy_intewface = PHY_INTEWFACE_MODE_SGMII;
	pwat->speed_mode_2500 = intew_speed_mode_2500;
	pwat->sewdes_powewup = intew_sewdes_powewup;
	pwat->sewdes_powewdown = intew_sewdes_powewdown;
	wetuwn ehw_pse1_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info ehw_pse1_sgmii1g_info = {
	.setup = ehw_pse1_sgmii1g_data,
};

static int tgw_common_data(stwuct pci_dev *pdev,
			   stwuct pwat_stmmacenet_data *pwat)
{
	pwat->wx_queues_to_use = 6;
	pwat->tx_queues_to_use = 4;
	pwat->cwk_ptp_wate = 204800000;
	pwat->speed_mode_2500 = intew_speed_mode_2500;

	pwat->safety_feat_cfg->tsoee = 1;
	pwat->safety_feat_cfg->mwxpee = 0;
	pwat->safety_feat_cfg->mestee = 1;
	pwat->safety_feat_cfg->mwxee = 1;
	pwat->safety_feat_cfg->mtxee = 1;
	pwat->safety_feat_cfg->epsi = 0;
	pwat->safety_feat_cfg->edpp = 0;
	pwat->safety_feat_cfg->pwtyen = 0;
	pwat->safety_feat_cfg->tmouten = 0;

	wetuwn intew_mgbe_common_data(pdev, pwat);
}

static int tgw_sgmii_phy0_data(stwuct pci_dev *pdev,
			       stwuct pwat_stmmacenet_data *pwat)
{
	pwat->bus_id = 1;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_SGMII;
	pwat->sewdes_powewup = intew_sewdes_powewup;
	pwat->sewdes_powewdown = intew_sewdes_powewdown;
	wetuwn tgw_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info tgw_sgmii1g_phy0_info = {
	.setup = tgw_sgmii_phy0_data,
};

static int tgw_sgmii_phy1_data(stwuct pci_dev *pdev,
			       stwuct pwat_stmmacenet_data *pwat)
{
	pwat->bus_id = 2;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_SGMII;
	pwat->sewdes_powewup = intew_sewdes_powewup;
	pwat->sewdes_powewdown = intew_sewdes_powewdown;
	wetuwn tgw_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info tgw_sgmii1g_phy1_info = {
	.setup = tgw_sgmii_phy1_data,
};

static int adws_sgmii_phy0_data(stwuct pci_dev *pdev,
				stwuct pwat_stmmacenet_data *pwat)
{
	pwat->bus_id = 1;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_SGMII;

	/* SewDes powew up and powew down awe done in BIOS fow ADW */

	wetuwn tgw_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info adws_sgmii1g_phy0_info = {
	.setup = adws_sgmii_phy0_data,
};

static int adws_sgmii_phy1_data(stwuct pci_dev *pdev,
				stwuct pwat_stmmacenet_data *pwat)
{
	pwat->bus_id = 2;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_SGMII;

	/* SewDes powew up and powew down awe done in BIOS fow ADW */

	wetuwn tgw_common_data(pdev, pwat);
}

static stwuct stmmac_pci_info adws_sgmii1g_phy1_info = {
	.setup = adws_sgmii_phy1_data,
};
static const stwuct stmmac_pci_func_data gawiweo_stmmac_func_data[] = {
	{
		.func = 6,
		.phy_addw = 1,
	},
};

static const stwuct stmmac_pci_dmi_data gawiweo_stmmac_dmi_data = {
	.func = gawiweo_stmmac_func_data,
	.nfuncs = AWWAY_SIZE(gawiweo_stmmac_func_data),
};

static const stwuct stmmac_pci_func_data iot2040_stmmac_func_data[] = {
	{
		.func = 6,
		.phy_addw = 1,
	},
	{
		.func = 7,
		.phy_addw = 1,
	},
};

static const stwuct stmmac_pci_dmi_data iot2040_stmmac_dmi_data = {
	.func = iot2040_stmmac_func_data,
	.nfuncs = AWWAY_SIZE(iot2040_stmmac_func_data),
};

static const stwuct dmi_system_id quawk_pci_dmi[] = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Gawiweo"),
		},
		.dwivew_data = (void *)&gawiweo_stmmac_dmi_data,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "GawiweoGen2"),
		},
		.dwivew_data = (void *)&gawiweo_stmmac_dmi_data,
	},
	/* Thewe awe 2 types of SIMATIC IOT2000: IOT2020 and IOT2040.
	 * The asset tag "6ES7647-0AA00-0YA2" is onwy fow IOT2020 which
	 * has onwy one pci netwowk device whiwe othew asset tags awe
	 * fow IOT2040 which has two.
	 */
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "SIMATIC IOT2000"),
			DMI_EXACT_MATCH(DMI_BOAWD_ASSET_TAG,
					"6ES7647-0AA00-0YA2"),
		},
		.dwivew_data = (void *)&gawiweo_stmmac_dmi_data,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "SIMATIC IOT2000"),
		},
		.dwivew_data = (void *)&iot2040_stmmac_dmi_data,
	},
	{}
};

static int quawk_defauwt_data(stwuct pci_dev *pdev,
			      stwuct pwat_stmmacenet_data *pwat)
{
	int wet;

	/* Set common defauwt data fiwst */
	common_defauwt_data(pwat);

	/* Wefuse to woad the dwivew and wegistew net device if MAC contwowwew
	 * does not connect to any PHY intewface.
	 */
	wet = stmmac_pci_find_phy_addw(pdev, quawk_pci_dmi);
	if (wet < 0) {
		/* Wetuwn ewwow to the cawwew on DMI enabwed boawds. */
		if (dmi_get_system_info(DMI_BOAWD_NAME))
			wetuwn wet;

		/* Gawiweo boawds with owd fiwmwawe don't suppowt DMI. We awways
		 * use 1 hewe as PHY addwess, so at weast the fiwst found MAC
		 * contwowwew wouwd be pwobed.
		 */
		wet = 1;
	}

	pwat->bus_id = pci_dev_id(pdev);
	pwat->phy_addw = wet;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_WMII;

	pwat->dma_cfg->pbw = 16;
	pwat->dma_cfg->pbwx8 = twue;
	pwat->dma_cfg->fixed_buwst = 1;
	/* AXI (TODO) */

	wetuwn 0;
}

static const stwuct stmmac_pci_info quawk_info = {
	.setup = quawk_defauwt_data,
};

static int stmmac_config_singwe_msi(stwuct pci_dev *pdev,
				    stwuct pwat_stmmacenet_data *pwat,
				    stwuct stmmac_wesouwces *wes)
{
	int wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0) {
		dev_info(&pdev->dev, "%s: Singwe IWQ enabwement faiwed\n",
			 __func__);
		wetuwn wet;
	}

	wes->iwq = pci_iwq_vectow(pdev, 0);
	wes->wow_iwq = wes->iwq;
	pwat->fwags &= ~STMMAC_FWAG_MUWTI_MSI_EN;
	dev_info(&pdev->dev, "%s: Singwe IWQ enabwement successfuw\n",
		 __func__);

	wetuwn 0;
}

static int stmmac_config_muwti_msi(stwuct pci_dev *pdev,
				   stwuct pwat_stmmacenet_data *pwat,
				   stwuct stmmac_wesouwces *wes)
{
	int wet;
	int i;

	if (pwat->msi_wx_base_vec >= STMMAC_MSI_VEC_MAX ||
	    pwat->msi_tx_base_vec >= STMMAC_MSI_VEC_MAX) {
		dev_info(&pdev->dev, "%s: Invawid WX & TX vectow defined\n",
			 __func__);
		wetuwn -1;
	}

	wet = pci_awwoc_iwq_vectows(pdev, 2, STMMAC_MSI_VEC_MAX,
				    PCI_IWQ_MSI | PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_info(&pdev->dev, "%s: muwti MSI enabwement faiwed\n",
			 __func__);
		wetuwn wet;
	}

	/* Fow WX MSI */
	fow (i = 0; i < pwat->wx_queues_to_use; i++) {
		wes->wx_iwq[i] = pci_iwq_vectow(pdev,
						pwat->msi_wx_base_vec + i * 2);
	}

	/* Fow TX MSI */
	fow (i = 0; i < pwat->tx_queues_to_use; i++) {
		wes->tx_iwq[i] = pci_iwq_vectow(pdev,
						pwat->msi_tx_base_vec + i * 2);
	}

	if (pwat->msi_mac_vec < STMMAC_MSI_VEC_MAX)
		wes->iwq = pci_iwq_vectow(pdev, pwat->msi_mac_vec);
	if (pwat->msi_wow_vec < STMMAC_MSI_VEC_MAX)
		wes->wow_iwq = pci_iwq_vectow(pdev, pwat->msi_wow_vec);
	if (pwat->msi_wpi_vec < STMMAC_MSI_VEC_MAX)
		wes->wpi_iwq = pci_iwq_vectow(pdev, pwat->msi_wpi_vec);
	if (pwat->msi_sfty_ce_vec < STMMAC_MSI_VEC_MAX)
		wes->sfty_ce_iwq = pci_iwq_vectow(pdev, pwat->msi_sfty_ce_vec);
	if (pwat->msi_sfty_ue_vec < STMMAC_MSI_VEC_MAX)
		wes->sfty_ue_iwq = pci_iwq_vectow(pdev, pwat->msi_sfty_ue_vec);

	pwat->fwags |= STMMAC_FWAG_MUWTI_MSI_EN;
	dev_info(&pdev->dev, "%s: muwti MSI enabwement successfuw\n", __func__);

	wetuwn 0;
}

/**
 * intew_eth_pci_pwobe
 *
 * @pdev: pci device pointew
 * @id: pointew to tabwe of device id/id's.
 *
 * Descwiption: This pwobing function gets cawwed fow aww PCI devices which
 * match the ID tabwe and awe not "owned" by othew dwivew yet. This function
 * gets passed a "stwuct pci_dev *" fow each device whose entwy in the ID tabwe
 * matches the device. The pwobe functions wetuwns zewo when the dwivew choose
 * to take "ownewship" of the device ow an ewwow code(-ve no) othewwise.
 */
static int intew_eth_pci_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *id)
{
	stwuct stmmac_pci_info *info = (stwuct stmmac_pci_info *)id->dwivew_data;
	stwuct intew_pwiv_data *intew_pwiv;
	stwuct pwat_stmmacenet_data *pwat;
	stwuct stmmac_wesouwces wes;
	int wet;

	intew_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*intew_pwiv), GFP_KEWNEW);
	if (!intew_pwiv)
		wetuwn -ENOMEM;

	pwat = devm_kzawwoc(&pdev->dev, sizeof(*pwat), GFP_KEWNEW);
	if (!pwat)
		wetuwn -ENOMEM;

	pwat->mdio_bus_data = devm_kzawwoc(&pdev->dev,
					   sizeof(*pwat->mdio_bus_data),
					   GFP_KEWNEW);
	if (!pwat->mdio_bus_data)
		wetuwn -ENOMEM;

	pwat->dma_cfg = devm_kzawwoc(&pdev->dev, sizeof(*pwat->dma_cfg),
				     GFP_KEWNEW);
	if (!pwat->dma_cfg)
		wetuwn -ENOMEM;

	pwat->safety_feat_cfg = devm_kzawwoc(&pdev->dev,
					     sizeof(*pwat->safety_feat_cfg),
					     GFP_KEWNEW);
	if (!pwat->safety_feat_cfg)
		wetuwn -ENOMEM;

	/* Enabwe pci device */
	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "%s: EWWOW: faiwed to enabwe device\n",
			__func__);
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	pwat->bsp_pwiv = intew_pwiv;
	intew_pwiv->mdio_adhoc_addw = INTEW_MGBE_ADHOC_ADDW;
	intew_pwiv->cwossts_adj = 1;

	/* Initiawize aww MSI vectows to invawid so that it can be set
	 * accowding to pwatfowm data settings bewow.
	 * Note: MSI vectow takes vawue fwom 0 upto 31 (STMMAC_MSI_VEC_MAX)
	 */
	pwat->msi_mac_vec = STMMAC_MSI_VEC_MAX;
	pwat->msi_wow_vec = STMMAC_MSI_VEC_MAX;
	pwat->msi_wpi_vec = STMMAC_MSI_VEC_MAX;
	pwat->msi_sfty_ce_vec = STMMAC_MSI_VEC_MAX;
	pwat->msi_sfty_ue_vec = STMMAC_MSI_VEC_MAX;
	pwat->msi_wx_base_vec = STMMAC_MSI_VEC_MAX;
	pwat->msi_tx_base_vec = STMMAC_MSI_VEC_MAX;

	wet = info->setup(pdev, pwat);
	if (wet)
		wetuwn wet;

	memset(&wes, 0, sizeof(wes));
	wes.addw = pcim_iomap_tabwe(pdev)[0];

	if (pwat->eee_usecs_wate > 0) {
		u32 tx_wpi_usec;

		tx_wpi_usec = (pwat->eee_usecs_wate / 1000000) - 1;
		wwitew(tx_wpi_usec, wes.addw + GMAC_1US_TIC_COUNTEW);
	}

	wet = stmmac_config_muwti_msi(pdev, pwat, &wes);
	if (wet) {
		wet = stmmac_config_singwe_msi(pdev, pwat, &wes);
		if (wet) {
			dev_eww(&pdev->dev, "%s: EWWOW: faiwed to enabwe IWQ\n",
				__func__);
			goto eww_awwoc_iwq;
		}
	}

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat, &wes);
	if (wet) {
		goto eww_awwoc_iwq;
	}

	wetuwn 0;

eww_awwoc_iwq:
	cwk_disabwe_unpwepawe(pwat->stmmac_cwk);
	cwk_unwegistew_fixed_wate(pwat->stmmac_cwk);
	wetuwn wet;
}

/**
 * intew_eth_pci_wemove
 *
 * @pdev: pci device pointew
 * Descwiption: this function cawws the main to fwee the net wesouwces
 * and weweases the PCI wesouwces.
 */
static void intew_eth_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *ndev = dev_get_dwvdata(&pdev->dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	stmmac_dvw_wemove(&pdev->dev);

	cwk_disabwe_unpwepawe(pwiv->pwat->stmmac_cwk);
	cwk_unwegistew_fixed_wate(pwiv->pwat->stmmac_cwk);
}

static int __maybe_unused intew_eth_pci_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	wet = stmmac_suspend(dev);
	if (wet)
		wetuwn wet;

	wet = pci_save_state(pdev);
	if (wet)
		wetuwn wet;

	pci_wake_fwom_d3(pdev, twue);
	pci_set_powew_state(pdev, PCI_D3hot);
	wetuwn 0;
}

static int __maybe_unused intew_eth_pci_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	pci_westowe_state(pdev);
	pci_set_powew_state(pdev, PCI_D0);

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	wetuwn stmmac_wesume(dev);
}

static SIMPWE_DEV_PM_OPS(intew_eth_pm_ops, intew_eth_pci_suspend,
			 intew_eth_pci_wesume);

#define PCI_DEVICE_ID_INTEW_QUAWK		0x0937
#define PCI_DEVICE_ID_INTEW_EHW_WGMII1G		0x4b30
#define PCI_DEVICE_ID_INTEW_EHW_SGMII1G		0x4b31
#define PCI_DEVICE_ID_INTEW_EHW_SGMII2G5	0x4b32
/* Intew(W) Pwogwammabwe Sewvices Engine (Intew(W) PSE) consist of 2 MAC
 * which awe named PSE0 and PSE1
 */
#define PCI_DEVICE_ID_INTEW_EHW_PSE0_WGMII1G	0x4ba0
#define PCI_DEVICE_ID_INTEW_EHW_PSE0_SGMII1G	0x4ba1
#define PCI_DEVICE_ID_INTEW_EHW_PSE0_SGMII2G5	0x4ba2
#define PCI_DEVICE_ID_INTEW_EHW_PSE1_WGMII1G	0x4bb0
#define PCI_DEVICE_ID_INTEW_EHW_PSE1_SGMII1G	0x4bb1
#define PCI_DEVICE_ID_INTEW_EHW_PSE1_SGMII2G5	0x4bb2
#define PCI_DEVICE_ID_INTEW_TGWH_SGMII1G_0	0x43ac
#define PCI_DEVICE_ID_INTEW_TGWH_SGMII1G_1	0x43a2
#define PCI_DEVICE_ID_INTEW_TGW_SGMII1G		0xa0ac
#define PCI_DEVICE_ID_INTEW_ADWS_SGMII1G_0	0x7aac
#define PCI_DEVICE_ID_INTEW_ADWS_SGMII1G_1	0x7aad
#define PCI_DEVICE_ID_INTEW_ADWN_SGMII1G	0x54ac
#define PCI_DEVICE_ID_INTEW_WPWP_SGMII1G	0x51ac

static const stwuct pci_device_id intew_eth_pci_id_tabwe[] = {
	{ PCI_DEVICE_DATA(INTEW, QUAWK, &quawk_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_WGMII1G, &ehw_wgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_SGMII1G, &ehw_sgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_SGMII2G5, &ehw_sgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_PSE0_WGMII1G, &ehw_pse0_wgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_PSE0_SGMII1G, &ehw_pse0_sgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_PSE0_SGMII2G5, &ehw_pse0_sgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_PSE1_WGMII1G, &ehw_pse1_wgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_PSE1_SGMII1G, &ehw_pse1_sgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, EHW_PSE1_SGMII2G5, &ehw_pse1_sgmii1g_info) },
	{ PCI_DEVICE_DATA(INTEW, TGW_SGMII1G, &tgw_sgmii1g_phy0_info) },
	{ PCI_DEVICE_DATA(INTEW, TGWH_SGMII1G_0, &tgw_sgmii1g_phy0_info) },
	{ PCI_DEVICE_DATA(INTEW, TGWH_SGMII1G_1, &tgw_sgmii1g_phy1_info) },
	{ PCI_DEVICE_DATA(INTEW, ADWS_SGMII1G_0, &adws_sgmii1g_phy0_info) },
	{ PCI_DEVICE_DATA(INTEW, ADWS_SGMII1G_1, &adws_sgmii1g_phy1_info) },
	{ PCI_DEVICE_DATA(INTEW, ADWN_SGMII1G, &tgw_sgmii1g_phy0_info) },
	{ PCI_DEVICE_DATA(INTEW, WPWP_SGMII1G, &tgw_sgmii1g_phy0_info) },
	{}
};
MODUWE_DEVICE_TABWE(pci, intew_eth_pci_id_tabwe);

static stwuct pci_dwivew intew_eth_pci_dwivew = {
	.name = "intew-eth-pci",
	.id_tabwe = intew_eth_pci_id_tabwe,
	.pwobe = intew_eth_pci_pwobe,
	.wemove = intew_eth_pci_wemove,
	.dwivew         = {
		.pm     = &intew_eth_pm_ops,
	},
};

moduwe_pci_dwivew(intew_eth_pci_dwivew);

MODUWE_DESCWIPTION("INTEW 10/100/1000 Ethewnet PCI dwivew");
MODUWE_AUTHOW("Voon Weifeng <weifeng.voon@intew.com>");
MODUWE_WICENSE("GPW v2");
