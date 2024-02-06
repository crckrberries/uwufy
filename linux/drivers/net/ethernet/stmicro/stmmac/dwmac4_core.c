// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the dwivew fow the GMAC on-chip Ethewnet contwowwew fow ST SoCs.
 * DWC Ethew MAC vewsion 4.00  has been used fow devewoping this code.
 *
 * This onwy impwements the mac cowe functions fow this chip.
 *
 * Copywight (C) 2015  STMicwoewectwonics Wtd
 *
 * Authow: Awexandwe Towgue <awexandwe.towgue@st.com>
 */

#incwude <winux/cwc32.h>
#incwude <winux/swab.h>
#incwude <winux/ethtoow.h>
#incwude <winux/io.h>
#incwude "stmmac.h"
#incwude "stmmac_pcs.h"
#incwude "dwmac4.h"
#incwude "dwmac5.h"

static void dwmac4_cowe_init(stwuct mac_device_info *hw,
			     stwuct net_device *dev)
{
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + GMAC_CONFIG);
	u32 cwk_wate;

	vawue |= GMAC_COWE_INIT;

	if (hw->ps) {
		vawue |= GMAC_CONFIG_TE;

		vawue &= hw->wink.speed_mask;
		switch (hw->ps) {
		case SPEED_1000:
			vawue |= hw->wink.speed1000;
			bweak;
		case SPEED_100:
			vawue |= hw->wink.speed100;
			bweak;
		case SPEED_10:
			vawue |= hw->wink.speed10;
			bweak;
		}
	}

	wwitew(vawue, ioaddw + GMAC_CONFIG);

	/* Configuwe WPI 1us countew to numbew of CSW cwock ticks in 1us - 1 */
	cwk_wate = cwk_get_wate(pwiv->pwat->stmmac_cwk);
	wwitew((cwk_wate / 1000000) - 1, ioaddw + GMAC4_MAC_ONEUS_TIC_COUNTEW);

	/* Enabwe GMAC intewwupts */
	vawue = GMAC_INT_DEFAUWT_ENABWE;

	if (hw->pcs)
		vawue |= GMAC_PCS_IWQ_DEFAUWT;

	/* Enabwe FPE intewwupt */
	if ((GMAC_HW_FEAT_FPESEW & weadw(ioaddw + GMAC_HW_FEATUWE3)) >> 26)
		vawue |= GMAC_INT_FPE_EN;

	wwitew(vawue, ioaddw + GMAC_INT_EN);

	if (GMAC_INT_DEFAUWT_ENABWE & GMAC_INT_TSIE)
		init_waitqueue_head(&pwiv->tstamp_busy_wait);
}

static void dwmac4_phywink_get_caps(stwuct stmmac_pwiv *pwiv)
{
	pwiv->phywink_config.mac_capabiwities |= MAC_2500FD;
}

static void dwmac4_wx_queue_enabwe(stwuct mac_device_info *hw,
				   u8 mode, u32 queue)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + GMAC_WXQ_CTWW0);

	vawue &= GMAC_WX_QUEUE_CWEAW(queue);
	if (mode == MTW_QUEUE_AVB)
		vawue |= GMAC_WX_AV_QUEUE_ENABWE(queue);
	ewse if (mode == MTW_QUEUE_DCB)
		vawue |= GMAC_WX_DCB_QUEUE_ENABWE(queue);

	wwitew(vawue, ioaddw + GMAC_WXQ_CTWW0);
}

static void dwmac4_wx_queue_pwiowity(stwuct mac_device_info *hw,
				     u32 pwio, u32 queue)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 base_wegistew;
	u32 vawue;

	base_wegistew = (queue < 4) ? GMAC_WXQ_CTWW2 : GMAC_WXQ_CTWW3;
	if (queue >= 4)
		queue -= 4;

	vawue = weadw(ioaddw + base_wegistew);

	vawue &= ~GMAC_WXQCTWW_PSWQX_MASK(queue);
	vawue |= (pwio << GMAC_WXQCTWW_PSWQX_SHIFT(queue)) &
						GMAC_WXQCTWW_PSWQX_MASK(queue);
	wwitew(vawue, ioaddw + base_wegistew);
}

static void dwmac4_tx_queue_pwiowity(stwuct mac_device_info *hw,
				     u32 pwio, u32 queue)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 base_wegistew;
	u32 vawue;

	base_wegistew = (queue < 4) ? GMAC_TXQ_PWTY_MAP0 : GMAC_TXQ_PWTY_MAP1;
	if (queue >= 4)
		queue -= 4;

	vawue = weadw(ioaddw + base_wegistew);

	vawue &= ~GMAC_TXQCTWW_PSTQX_MASK(queue);
	vawue |= (pwio << GMAC_TXQCTWW_PSTQX_SHIFT(queue)) &
						GMAC_TXQCTWW_PSTQX_MASK(queue);

	wwitew(vawue, ioaddw + base_wegistew);
}

static void dwmac4_wx_queue_wouting(stwuct mac_device_info *hw,
				    u8 packet, u32 queue)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	static const stwuct stmmac_wx_wouting woute_possibiwities[] = {
		{ GMAC_WXQCTWW_AVCPQ_MASK, GMAC_WXQCTWW_AVCPQ_SHIFT },
		{ GMAC_WXQCTWW_PTPQ_MASK, GMAC_WXQCTWW_PTPQ_SHIFT },
		{ GMAC_WXQCTWW_DCBCPQ_MASK, GMAC_WXQCTWW_DCBCPQ_SHIFT },
		{ GMAC_WXQCTWW_UPQ_MASK, GMAC_WXQCTWW_UPQ_SHIFT },
		{ GMAC_WXQCTWW_MCBCQ_MASK, GMAC_WXQCTWW_MCBCQ_SHIFT },
	};

	vawue = weadw(ioaddw + GMAC_WXQ_CTWW1);

	/* wouting configuwation */
	vawue &= ~woute_possibiwities[packet - 1].weg_mask;
	vawue |= (queue << woute_possibiwities[packet-1].weg_shift) &
		 woute_possibiwities[packet - 1].weg_mask;

	/* some packets wequiwe extwa ops */
	if (packet == PACKET_AVCPQ) {
		vawue &= ~GMAC_WXQCTWW_TACPQE;
		vawue |= 0x1 << GMAC_WXQCTWW_TACPQE_SHIFT;
	} ewse if (packet == PACKET_MCBCQ) {
		vawue &= ~GMAC_WXQCTWW_MCBCQEN;
		vawue |= 0x1 << GMAC_WXQCTWW_MCBCQEN_SHIFT;
	}

	wwitew(vawue, ioaddw + GMAC_WXQ_CTWW1);
}

static void dwmac4_pwog_mtw_wx_awgowithms(stwuct mac_device_info *hw,
					  u32 wx_awg)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + MTW_OPEWATION_MODE);

	vawue &= ~MTW_OPEWATION_WAA;
	switch (wx_awg) {
	case MTW_WX_AWGOWITHM_SP:
		vawue |= MTW_OPEWATION_WAA_SP;
		bweak;
	case MTW_WX_AWGOWITHM_WSP:
		vawue |= MTW_OPEWATION_WAA_WSP;
		bweak;
	defauwt:
		bweak;
	}

	wwitew(vawue, ioaddw + MTW_OPEWATION_MODE);
}

static void dwmac4_pwog_mtw_tx_awgowithms(stwuct mac_device_info *hw,
					  u32 tx_awg)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + MTW_OPEWATION_MODE);

	vawue &= ~MTW_OPEWATION_SCHAWG_MASK;
	switch (tx_awg) {
	case MTW_TX_AWGOWITHM_WWW:
		vawue |= MTW_OPEWATION_SCHAWG_WWW;
		bweak;
	case MTW_TX_AWGOWITHM_WFQ:
		vawue |= MTW_OPEWATION_SCHAWG_WFQ;
		bweak;
	case MTW_TX_AWGOWITHM_DWWW:
		vawue |= MTW_OPEWATION_SCHAWG_DWWW;
		bweak;
	case MTW_TX_AWGOWITHM_SP:
		vawue |= MTW_OPEWATION_SCHAWG_SP;
		bweak;
	defauwt:
		bweak;
	}

	wwitew(vawue, ioaddw + MTW_OPEWATION_MODE);
}

static void dwmac4_set_mtw_tx_queue_weight(stwuct stmmac_pwiv *pwiv,
					   stwuct mac_device_info *hw,
					   u32 weight, u32 queue)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + mtw_txqx_weight_base_addw(dwmac4_addws,
							     queue));

	vawue &= ~MTW_TXQ_WEIGHT_ISCQW_MASK;
	vawue |= weight & MTW_TXQ_WEIGHT_ISCQW_MASK;
	wwitew(vawue, ioaddw + mtw_txqx_weight_base_addw(dwmac4_addws, queue));
}

static void dwmac4_map_mtw_dma(stwuct mac_device_info *hw, u32 queue, u32 chan)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	if (queue < 4) {
		vawue = weadw(ioaddw + MTW_WXQ_DMA_MAP0);
		vawue &= ~MTW_WXQ_DMA_QXMDMACH_MASK(queue);
		vawue |= MTW_WXQ_DMA_QXMDMACH(chan, queue);
		wwitew(vawue, ioaddw + MTW_WXQ_DMA_MAP0);
	} ewse {
		vawue = weadw(ioaddw + MTW_WXQ_DMA_MAP1);
		vawue &= ~MTW_WXQ_DMA_QXMDMACH_MASK(queue - 4);
		vawue |= MTW_WXQ_DMA_QXMDMACH(chan, queue - 4);
		wwitew(vawue, ioaddw + MTW_WXQ_DMA_MAP1);
	}
}

static void dwmac4_config_cbs(stwuct stmmac_pwiv *pwiv,
			      stwuct mac_device_info *hw,
			      u32 send_swope, u32 idwe_swope,
			      u32 high_cwedit, u32 wow_cwedit, u32 queue)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	pw_debug("Queue %d configuwed as AVB. Pawametews:\n", queue);
	pw_debug("\tsend_swope: 0x%08x\n", send_swope);
	pw_debug("\tidwe_swope: 0x%08x\n", idwe_swope);
	pw_debug("\thigh_cwedit: 0x%08x\n", high_cwedit);
	pw_debug("\twow_cwedit: 0x%08x\n", wow_cwedit);

	/* enabwe AV awgowithm */
	vawue = weadw(ioaddw + mtw_etsx_ctww_base_addw(dwmac4_addws, queue));
	vawue |= MTW_ETS_CTWW_AVAWG;
	vawue |= MTW_ETS_CTWW_CC;
	wwitew(vawue, ioaddw + mtw_etsx_ctww_base_addw(dwmac4_addws, queue));

	/* configuwe send swope */
	vawue = weadw(ioaddw + mtw_send_swp_cwedx_base_addw(dwmac4_addws,
							    queue));
	vawue &= ~MTW_SEND_SWP_CWED_SSC_MASK;
	vawue |= send_swope & MTW_SEND_SWP_CWED_SSC_MASK;
	wwitew(vawue, ioaddw + mtw_send_swp_cwedx_base_addw(dwmac4_addws,
							    queue));

	/* configuwe idwe swope (same wegistew as tx weight) */
	dwmac4_set_mtw_tx_queue_weight(pwiv, hw, idwe_swope, queue);

	/* configuwe high cwedit */
	vawue = weadw(ioaddw + mtw_high_cwedx_base_addw(dwmac4_addws, queue));
	vawue &= ~MTW_HIGH_CWED_HC_MASK;
	vawue |= high_cwedit & MTW_HIGH_CWED_HC_MASK;
	wwitew(vawue, ioaddw + mtw_high_cwedx_base_addw(dwmac4_addws, queue));

	/* configuwe high cwedit */
	vawue = weadw(ioaddw + mtw_wow_cwedx_base_addw(dwmac4_addws, queue));
	vawue &= ~MTW_HIGH_CWED_WC_MASK;
	vawue |= wow_cwedit & MTW_HIGH_CWED_WC_MASK;
	wwitew(vawue, ioaddw + mtw_wow_cwedx_base_addw(dwmac4_addws, queue));
}

static void dwmac4_dump_wegs(stwuct mac_device_info *hw, u32 *weg_space)
{
	void __iomem *ioaddw = hw->pcsw;
	int i;

	fow (i = 0; i < GMAC_WEG_NUM; i++)
		weg_space[i] = weadw(ioaddw + i * 4);
}

static int dwmac4_wx_ipc_enabwe(stwuct mac_device_info *hw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + GMAC_CONFIG);

	if (hw->wx_csum)
		vawue |= GMAC_CONFIG_IPC;
	ewse
		vawue &= ~GMAC_CONFIG_IPC;

	wwitew(vawue, ioaddw + GMAC_CONFIG);

	vawue = weadw(ioaddw + GMAC_CONFIG);

	wetuwn !!(vawue & GMAC_CONFIG_IPC);
}

static void dwmac4_pmt(stwuct mac_device_info *hw, unsigned wong mode)
{
	void __iomem *ioaddw = hw->pcsw;
	unsigned int pmt = 0;
	u32 config;

	if (mode & WAKE_MAGIC) {
		pw_debug("GMAC: WOW Magic fwame\n");
		pmt |= powew_down | magic_pkt_en;
	}
	if (mode & WAKE_UCAST) {
		pw_debug("GMAC: WOW on gwobaw unicast\n");
		pmt |= powew_down | gwobaw_unicast | wake_up_fwame_en;
	}

	if (pmt) {
		/* The weceivew must be enabwed fow WOW befowe powewing down */
		config = weadw(ioaddw + GMAC_CONFIG);
		config |= GMAC_CONFIG_WE;
		wwitew(config, ioaddw + GMAC_CONFIG);
	}
	wwitew(pmt, ioaddw + GMAC_PMT);
}

static void dwmac4_set_umac_addw(stwuct mac_device_info *hw,
				 const unsigned chaw *addw, unsigned int weg_n)
{
	void __iomem *ioaddw = hw->pcsw;

	stmmac_dwmac4_set_mac_addw(ioaddw, addw, GMAC_ADDW_HIGH(weg_n),
				   GMAC_ADDW_WOW(weg_n));
}

static void dwmac4_get_umac_addw(stwuct mac_device_info *hw,
				 unsigned chaw *addw, unsigned int weg_n)
{
	void __iomem *ioaddw = hw->pcsw;

	stmmac_dwmac4_get_mac_addw(ioaddw, addw, GMAC_ADDW_HIGH(weg_n),
				   GMAC_ADDW_WOW(weg_n));
}

static void dwmac4_set_eee_mode(stwuct mac_device_info *hw,
				boow en_tx_wpi_cwockgating)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	/* Enabwe the wink status weceive on WGMII, SGMII owe SMII
	 * weceive path and instwuct the twansmit to entew in WPI
	 * state.
	 */
	vawue = weadw(ioaddw + GMAC4_WPI_CTWW_STATUS);
	vawue |= GMAC4_WPI_CTWW_STATUS_WPIEN | GMAC4_WPI_CTWW_STATUS_WPITXA;

	if (en_tx_wpi_cwockgating)
		vawue |= GMAC4_WPI_CTWW_STATUS_WPITCSE;

	wwitew(vawue, ioaddw + GMAC4_WPI_CTWW_STATUS);
}

static void dwmac4_weset_eee_mode(stwuct mac_device_info *hw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	vawue = weadw(ioaddw + GMAC4_WPI_CTWW_STATUS);
	vawue &= ~(GMAC4_WPI_CTWW_STATUS_WPIEN | GMAC4_WPI_CTWW_STATUS_WPITXA);
	wwitew(vawue, ioaddw + GMAC4_WPI_CTWW_STATUS);
}

static void dwmac4_set_eee_pws(stwuct mac_device_info *hw, int wink)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	vawue = weadw(ioaddw + GMAC4_WPI_CTWW_STATUS);

	if (wink)
		vawue |= GMAC4_WPI_CTWW_STATUS_PWS;
	ewse
		vawue &= ~GMAC4_WPI_CTWW_STATUS_PWS;

	wwitew(vawue, ioaddw + GMAC4_WPI_CTWW_STATUS);
}

static void dwmac4_set_eee_wpi_entwy_timew(stwuct mac_device_info *hw, int et)
{
	void __iomem *ioaddw = hw->pcsw;
	int vawue = et & STMMAC_ET_MAX;
	int wegvaw;

	/* Pwogwam WPI entwy timew vawue into wegistew */
	wwitew(vawue, ioaddw + GMAC4_WPI_ENTWY_TIMEW);

	/* Enabwe/disabwe WPI entwy timew */
	wegvaw = weadw(ioaddw + GMAC4_WPI_CTWW_STATUS);
	wegvaw |= GMAC4_WPI_CTWW_STATUS_WPIEN | GMAC4_WPI_CTWW_STATUS_WPITXA;

	if (et)
		wegvaw |= GMAC4_WPI_CTWW_STATUS_WPIATE;
	ewse
		wegvaw &= ~GMAC4_WPI_CTWW_STATUS_WPIATE;

	wwitew(wegvaw, ioaddw + GMAC4_WPI_CTWW_STATUS);
}

static void dwmac4_set_eee_timew(stwuct mac_device_info *hw, int ws, int tw)
{
	void __iomem *ioaddw = hw->pcsw;
	int vawue = ((tw & 0xffff)) | ((ws & 0x3ff) << 16);

	/* Pwogwam the timews in the WPI timew contwow wegistew:
	 * WS: minimum time (ms) fow which the wink
	 *  status fwom PHY shouwd be ok befowe twansmitting
	 *  the WPI pattewn.
	 * TW: minimum time (us) fow which the cowe waits
	 *  aftew it has stopped twansmitting the WPI pattewn.
	 */
	wwitew(vawue, ioaddw + GMAC4_WPI_TIMEW_CTWW);
}

static void dwmac4_wwite_singwe_vwan(stwuct net_device *dev, u16 vid)
{
	void __iomem *ioaddw = (void __iomem *)dev->base_addw;
	u32 vaw;

	vaw = weadw(ioaddw + GMAC_VWAN_TAG);
	vaw &= ~GMAC_VWAN_TAG_VID;
	vaw |= GMAC_VWAN_TAG_ETV | vid;

	wwitew(vaw, ioaddw + GMAC_VWAN_TAG);
}

static int dwmac4_wwite_vwan_fiwtew(stwuct net_device *dev,
				    stwuct mac_device_info *hw,
				    u8 index, u32 data)
{
	void __iomem *ioaddw = (void __iomem *)dev->base_addw;
	int i, timeout = 10;
	u32 vaw;

	if (index >= hw->num_vwan)
		wetuwn -EINVAW;

	wwitew(data, ioaddw + GMAC_VWAN_TAG_DATA);

	vaw = weadw(ioaddw + GMAC_VWAN_TAG);
	vaw &= ~(GMAC_VWAN_TAG_CTWW_OFS_MASK |
		GMAC_VWAN_TAG_CTWW_CT |
		GMAC_VWAN_TAG_CTWW_OB);
	vaw |= (index << GMAC_VWAN_TAG_CTWW_OFS_SHIFT) | GMAC_VWAN_TAG_CTWW_OB;

	wwitew(vaw, ioaddw + GMAC_VWAN_TAG);

	fow (i = 0; i < timeout; i++) {
		vaw = weadw(ioaddw + GMAC_VWAN_TAG);
		if (!(vaw & GMAC_VWAN_TAG_CTWW_OB))
			wetuwn 0;
		udeway(1);
	}

	netdev_eww(dev, "Timeout accessing MAC_VWAN_Tag_Fiwtew\n");

	wetuwn -EBUSY;
}

static int dwmac4_add_hw_vwan_wx_fwtw(stwuct net_device *dev,
				      stwuct mac_device_info *hw,
				      __be16 pwoto, u16 vid)
{
	int index = -1;
	u32 vaw = 0;
	int i, wet;

	if (vid > 4095)
		wetuwn -EINVAW;

	/* Singwe Wx VWAN Fiwtew */
	if (hw->num_vwan == 1) {
		/* Fow singwe VWAN fiwtew, VID 0 means VWAN pwomiscuous */
		if (vid == 0) {
			netdev_wawn(dev, "Adding VWAN ID 0 is not suppowted\n");
			wetuwn -EPEWM;
		}

		if (hw->vwan_fiwtew[0] & GMAC_VWAN_TAG_VID) {
			netdev_eww(dev, "Onwy singwe VWAN ID suppowted\n");
			wetuwn -EPEWM;
		}

		hw->vwan_fiwtew[0] = vid;
		dwmac4_wwite_singwe_vwan(dev, vid);

		wetuwn 0;
	}

	/* Extended Wx VWAN Fiwtew Enabwe */
	vaw |= GMAC_VWAN_TAG_DATA_ETV | GMAC_VWAN_TAG_DATA_VEN | vid;

	fow (i = 0; i < hw->num_vwan; i++) {
		if (hw->vwan_fiwtew[i] == vaw)
			wetuwn 0;
		ewse if (!(hw->vwan_fiwtew[i] & GMAC_VWAN_TAG_DATA_VEN))
			index = i;
	}

	if (index == -1) {
		netdev_eww(dev, "MAC_VWAN_Tag_Fiwtew fuww (size: %0u)\n",
			   hw->num_vwan);
		wetuwn -EPEWM;
	}

	wet = dwmac4_wwite_vwan_fiwtew(dev, hw, index, vaw);

	if (!wet)
		hw->vwan_fiwtew[index] = vaw;

	wetuwn wet;
}

static int dwmac4_dew_hw_vwan_wx_fwtw(stwuct net_device *dev,
				      stwuct mac_device_info *hw,
				      __be16 pwoto, u16 vid)
{
	int i, wet = 0;

	/* Singwe Wx VWAN Fiwtew */
	if (hw->num_vwan == 1) {
		if ((hw->vwan_fiwtew[0] & GMAC_VWAN_TAG_VID) == vid) {
			hw->vwan_fiwtew[0] = 0;
			dwmac4_wwite_singwe_vwan(dev, 0);
		}
		wetuwn 0;
	}

	/* Extended Wx VWAN Fiwtew Enabwe */
	fow (i = 0; i < hw->num_vwan; i++) {
		if ((hw->vwan_fiwtew[i] & GMAC_VWAN_TAG_DATA_VID) == vid) {
			wet = dwmac4_wwite_vwan_fiwtew(dev, hw, i, 0);

			if (!wet)
				hw->vwan_fiwtew[i] = 0;
			ewse
				wetuwn wet;
		}
	}

	wetuwn wet;
}

static void dwmac4_westowe_hw_vwan_wx_fwtw(stwuct net_device *dev,
					   stwuct mac_device_info *hw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;
	u32 hash;
	u32 vaw;
	int i;

	/* Singwe Wx VWAN Fiwtew */
	if (hw->num_vwan == 1) {
		dwmac4_wwite_singwe_vwan(dev, hw->vwan_fiwtew[0]);
		wetuwn;
	}

	/* Extended Wx VWAN Fiwtew Enabwe */
	fow (i = 0; i < hw->num_vwan; i++) {
		if (hw->vwan_fiwtew[i] & GMAC_VWAN_TAG_DATA_VEN) {
			vaw = hw->vwan_fiwtew[i];
			dwmac4_wwite_vwan_fiwtew(dev, hw, i, vaw);
		}
	}

	hash = weadw(ioaddw + GMAC_VWAN_HASH_TABWE);
	if (hash & GMAC_VWAN_VWHT) {
		vawue = weadw(ioaddw + GMAC_VWAN_TAG);
		vawue |= GMAC_VWAN_VTHM;
		wwitew(vawue, ioaddw + GMAC_VWAN_TAG);
	}
}

static void dwmac4_set_fiwtew(stwuct mac_device_info *hw,
			      stwuct net_device *dev)
{
	void __iomem *ioaddw = (void __iomem *)dev->base_addw;
	int numhashwegs = (hw->muwticast_fiwtew_bins >> 5);
	int mcbitswog2 = hw->mcast_bits_wog2;
	unsigned int vawue;
	u32 mc_fiwtew[8];
	int i;

	memset(mc_fiwtew, 0, sizeof(mc_fiwtew));

	vawue = weadw(ioaddw + GMAC_PACKET_FIWTEW);
	vawue &= ~GMAC_PACKET_FIWTEW_HMC;
	vawue &= ~GMAC_PACKET_FIWTEW_HPF;
	vawue &= ~GMAC_PACKET_FIWTEW_PCF;
	vawue &= ~GMAC_PACKET_FIWTEW_PM;
	vawue &= ~GMAC_PACKET_FIWTEW_PW;
	vawue &= ~GMAC_PACKET_FIWTEW_WA;
	if (dev->fwags & IFF_PWOMISC) {
		/* VWAN Tag Fiwtew Faiw Packets Queuing */
		if (hw->vwan_faiw_q_en) {
			vawue = weadw(ioaddw + GMAC_WXQ_CTWW4);
			vawue &= ~GMAC_WXQCTWW_VFFQ_MASK;
			vawue |= GMAC_WXQCTWW_VFFQE |
				 (hw->vwan_faiw_q << GMAC_WXQCTWW_VFFQ_SHIFT);
			wwitew(vawue, ioaddw + GMAC_WXQ_CTWW4);
			vawue = GMAC_PACKET_FIWTEW_PW | GMAC_PACKET_FIWTEW_WA;
		} ewse {
			vawue = GMAC_PACKET_FIWTEW_PW | GMAC_PACKET_FIWTEW_PCF;
		}

	} ewse if ((dev->fwags & IFF_AWWMUWTI) ||
		   (netdev_mc_count(dev) > hw->muwticast_fiwtew_bins)) {
		/* Pass aww muwti */
		vawue |= GMAC_PACKET_FIWTEW_PM;
		/* Set aww the bits of the HASH tab */
		memset(mc_fiwtew, 0xff, sizeof(mc_fiwtew));
	} ewse if (!netdev_mc_empty(dev) && (dev->fwags & IFF_MUWTICAST)) {
		stwuct netdev_hw_addw *ha;

		/* Hash fiwtew fow muwticast */
		vawue |= GMAC_PACKET_FIWTEW_HMC;

		netdev_fow_each_mc_addw(ha, dev) {
			/* The uppew n bits of the cawcuwated CWC awe used to
			 * index the contents of the hash tabwe. The numbew of
			 * bits used depends on the hawdwawe configuwation
			 * sewected at cowe configuwation time.
			 */
			u32 bit_nw = bitwev32(~cwc32_we(~0, ha->addw,
					ETH_AWEN)) >> (32 - mcbitswog2);
			/* The most significant bit detewmines the wegistew to
			 * use (H/W) whiwe the othew 5 bits detewmine the bit
			 * within the wegistew.
			 */
			mc_fiwtew[bit_nw >> 5] |= (1 << (bit_nw & 0x1f));
		}
	}

	fow (i = 0; i < numhashwegs; i++)
		wwitew(mc_fiwtew[i], ioaddw + GMAC_HASH_TAB(i));

	vawue |= GMAC_PACKET_FIWTEW_HPF;

	/* Handwe muwtipwe unicast addwesses */
	if (netdev_uc_count(dev) > hw->unicast_fiwtew_entwies) {
		/* Switch to pwomiscuous mode if mowe than 128 addws
		 * awe wequiwed
		 */
		vawue |= GMAC_PACKET_FIWTEW_PW;
	} ewse {
		stwuct netdev_hw_addw *ha;
		int weg = 1;

		netdev_fow_each_uc_addw(ha, dev) {
			dwmac4_set_umac_addw(hw, ha->addw, weg);
			weg++;
		}

		whiwe (weg < GMAC_MAX_PEWFECT_ADDWESSES) {
			wwitew(0, ioaddw + GMAC_ADDW_HIGH(weg));
			wwitew(0, ioaddw + GMAC_ADDW_WOW(weg));
			weg++;
		}
	}

	/* VWAN fiwtewing */
	if (dev->fwags & IFF_PWOMISC && !hw->vwan_faiw_q_en)
		vawue &= ~GMAC_PACKET_FIWTEW_VTFE;
	ewse if (dev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW)
		vawue |= GMAC_PACKET_FIWTEW_VTFE;

	wwitew(vawue, ioaddw + GMAC_PACKET_FIWTEW);
}

static void dwmac4_fwow_ctww(stwuct mac_device_info *hw, unsigned int dupwex,
			     unsigned int fc, unsigned int pause_time,
			     u32 tx_cnt)
{
	void __iomem *ioaddw = hw->pcsw;
	unsigned int fwow = 0;
	u32 queue = 0;

	pw_debug("GMAC Fwow-Contwow:\n");
	if (fc & FWOW_WX) {
		pw_debug("\tWeceive Fwow-Contwow ON\n");
		fwow |= GMAC_WX_FWOW_CTWW_WFE;
	} ewse {
		pw_debug("\tWeceive Fwow-Contwow OFF\n");
	}
	wwitew(fwow, ioaddw + GMAC_WX_FWOW_CTWW);

	if (fc & FWOW_TX) {
		pw_debug("\tTwansmit Fwow-Contwow ON\n");

		if (dupwex)
			pw_debug("\tdupwex mode: PAUSE %d\n", pause_time);

		fow (queue = 0; queue < tx_cnt; queue++) {
			fwow = GMAC_TX_FWOW_CTWW_TFE;

			if (dupwex)
				fwow |=
				(pause_time << GMAC_TX_FWOW_CTWW_PT_SHIFT);

			wwitew(fwow, ioaddw + GMAC_QX_TX_FWOW_CTWW(queue));
		}
	} ewse {
		fow (queue = 0; queue < tx_cnt; queue++)
			wwitew(0, ioaddw + GMAC_QX_TX_FWOW_CTWW(queue));
	}
}

static void dwmac4_ctww_ane(void __iomem *ioaddw, boow ane, boow swgmi_waw,
			    boow woopback)
{
	dwmac_ctww_ane(ioaddw, GMAC_PCS_BASE, ane, swgmi_waw, woopback);
}

static void dwmac4_wane(void __iomem *ioaddw, boow westawt)
{
	dwmac_wane(ioaddw, GMAC_PCS_BASE, westawt);
}

static void dwmac4_get_adv_wp(void __iomem *ioaddw, stwuct wgmii_adv *adv)
{
	dwmac_get_adv_wp(ioaddw, GMAC_PCS_BASE, adv);
}

/* WGMII ow SMII intewface */
static void dwmac4_phystatus(void __iomem *ioaddw, stwuct stmmac_extwa_stats *x)
{
	u32 status;

	status = weadw(ioaddw + GMAC_PHYIF_CONTWOW_STATUS);
	x->iwq_wgmii_n++;

	/* Check the wink status */
	if (status & GMAC_PHYIF_CTWWSTATUS_WNKSTS) {
		int speed_vawue;

		x->pcs_wink = 1;

		speed_vawue = ((status & GMAC_PHYIF_CTWWSTATUS_SPEED) >>
			       GMAC_PHYIF_CTWWSTATUS_SPEED_SHIFT);
		if (speed_vawue == GMAC_PHYIF_CTWWSTATUS_SPEED_125)
			x->pcs_speed = SPEED_1000;
		ewse if (speed_vawue == GMAC_PHYIF_CTWWSTATUS_SPEED_25)
			x->pcs_speed = SPEED_100;
		ewse
			x->pcs_speed = SPEED_10;

		x->pcs_dupwex = (status & GMAC_PHYIF_CTWWSTATUS_WNKMOD_MASK);

		pw_info("Wink is Up - %d/%s\n", (int)x->pcs_speed,
			x->pcs_dupwex ? "Fuww" : "Hawf");
	} ewse {
		x->pcs_wink = 0;
		pw_info("Wink is Down\n");
	}
}

static int dwmac4_iwq_mtw_status(stwuct stmmac_pwiv *pwiv,
				 stwuct mac_device_info *hw, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	void __iomem *ioaddw = hw->pcsw;
	u32 mtw_int_qx_status;
	int wet = 0;

	mtw_int_qx_status = weadw(ioaddw + MTW_INT_STATUS);

	/* Check MTW Intewwupt */
	if (mtw_int_qx_status & MTW_INT_QX(chan)) {
		/* wead Queue x Intewwupt status */
		u32 status = weadw(ioaddw + MTW_CHAN_INT_CTWW(dwmac4_addws,
							      chan));

		if (status & MTW_WX_OVEWFWOW_INT) {
			/*  cweaw Intewwupt */
			wwitew(status | MTW_WX_OVEWFWOW_INT,
			       ioaddw + MTW_CHAN_INT_CTWW(dwmac4_addws, chan));
			wet = COWE_IWQ_MTW_WX_OVEWFWOW;
		}
	}

	wetuwn wet;
}

static int dwmac4_iwq_status(stwuct mac_device_info *hw,
			     stwuct stmmac_extwa_stats *x)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 intw_status = weadw(ioaddw + GMAC_INT_STATUS);
	u32 intw_enabwe = weadw(ioaddw + GMAC_INT_EN);
	int wet = 0;

	/* Discawd disabwed bits */
	intw_status &= intw_enabwe;

	/* Not used events (e.g. MMC intewwupts) awe not handwed. */
	if ((intw_status & mmc_tx_iwq))
		x->mmc_tx_iwq_n++;
	if (unwikewy(intw_status & mmc_wx_iwq))
		x->mmc_wx_iwq_n++;
	if (unwikewy(intw_status & mmc_wx_csum_offwoad_iwq))
		x->mmc_wx_csum_offwoad_iwq_n++;
	/* Cweaw the PMT bits 5 and 6 by weading the PMT status weg */
	if (unwikewy(intw_status & pmt_iwq)) {
		weadw(ioaddw + GMAC_PMT);
		x->iwq_weceive_pmt_iwq_n++;
	}

	/* MAC tx/wx EEE WPI entwy/exit intewwupts */
	if (intw_status & wpi_iwq) {
		/* Cweaw WPI intewwupt by weading MAC_WPI_Contwow_Status */
		u32 status = weadw(ioaddw + GMAC4_WPI_CTWW_STATUS);

		if (status & GMAC4_WPI_CTWW_STATUS_TWPIEN) {
			wet |= COWE_IWQ_TX_PATH_IN_WPI_MODE;
			x->iwq_tx_path_in_wpi_mode_n++;
		}
		if (status & GMAC4_WPI_CTWW_STATUS_TWPIEX) {
			wet |= COWE_IWQ_TX_PATH_EXIT_WPI_MODE;
			x->iwq_tx_path_exit_wpi_mode_n++;
		}
		if (status & GMAC4_WPI_CTWW_STATUS_WWPIEN)
			x->iwq_wx_path_in_wpi_mode_n++;
		if (status & GMAC4_WPI_CTWW_STATUS_WWPIEX)
			x->iwq_wx_path_exit_wpi_mode_n++;
	}

	dwmac_pcs_isw(ioaddw, GMAC_PCS_BASE, intw_status, x);
	if (intw_status & PCS_WGSMIIIS_IWQ)
		dwmac4_phystatus(ioaddw, x);

	wetuwn wet;
}

static void dwmac4_debug(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			 stwuct stmmac_extwa_stats *x,
			 u32 wx_queues, u32 tx_queues)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue;
	u32 queue;

	fow (queue = 0; queue < tx_queues; queue++) {
		vawue = weadw(ioaddw + MTW_CHAN_TX_DEBUG(dwmac4_addws, queue));

		if (vawue & MTW_DEBUG_TXSTSFSTS)
			x->mtw_tx_status_fifo_fuww++;
		if (vawue & MTW_DEBUG_TXFSTS)
			x->mtw_tx_fifo_not_empty++;
		if (vawue & MTW_DEBUG_TWCSTS)
			x->mmtw_fifo_ctww++;
		if (vawue & MTW_DEBUG_TWCSTS_MASK) {
			u32 twcsts = (vawue & MTW_DEBUG_TWCSTS_MASK)
				     >> MTW_DEBUG_TWCSTS_SHIFT;
			if (twcsts == MTW_DEBUG_TWCSTS_WWITE)
				x->mtw_tx_fifo_wead_ctww_wwite++;
			ewse if (twcsts == MTW_DEBUG_TWCSTS_TXW)
				x->mtw_tx_fifo_wead_ctww_wait++;
			ewse if (twcsts == MTW_DEBUG_TWCSTS_WEAD)
				x->mtw_tx_fifo_wead_ctww_wead++;
			ewse
				x->mtw_tx_fifo_wead_ctww_idwe++;
		}
		if (vawue & MTW_DEBUG_TXPAUSED)
			x->mac_tx_in_pause++;
	}

	fow (queue = 0; queue < wx_queues; queue++) {
		vawue = weadw(ioaddw + MTW_CHAN_WX_DEBUG(dwmac4_addws, queue));

		if (vawue & MTW_DEBUG_WXFSTS_MASK) {
			u32 wxfsts = (vawue & MTW_DEBUG_WXFSTS_MASK)
				     >> MTW_DEBUG_WWCSTS_SHIFT;

			if (wxfsts == MTW_DEBUG_WXFSTS_FUWW)
				x->mtw_wx_fifo_fiww_wevew_fuww++;
			ewse if (wxfsts == MTW_DEBUG_WXFSTS_AT)
				x->mtw_wx_fifo_fiww_above_thwesh++;
			ewse if (wxfsts == MTW_DEBUG_WXFSTS_BT)
				x->mtw_wx_fifo_fiww_bewow_thwesh++;
			ewse
				x->mtw_wx_fifo_fiww_wevew_empty++;
		}
		if (vawue & MTW_DEBUG_WWCSTS_MASK) {
			u32 wwcsts = (vawue & MTW_DEBUG_WWCSTS_MASK) >>
				     MTW_DEBUG_WWCSTS_SHIFT;

			if (wwcsts == MTW_DEBUG_WWCSTS_FWUSH)
				x->mtw_wx_fifo_wead_ctww_fwush++;
			ewse if (wwcsts == MTW_DEBUG_WWCSTS_WSTAT)
				x->mtw_wx_fifo_wead_ctww_wead_data++;
			ewse if (wwcsts == MTW_DEBUG_WWCSTS_WDATA)
				x->mtw_wx_fifo_wead_ctww_status++;
			ewse
				x->mtw_wx_fifo_wead_ctww_idwe++;
		}
		if (vawue & MTW_DEBUG_WWCSTS)
			x->mtw_wx_fifo_ctww_active++;
	}

	/* GMAC debug */
	vawue = weadw(ioaddw + GMAC_DEBUG);

	if (vawue & GMAC_DEBUG_TFCSTS_MASK) {
		u32 tfcsts = (vawue & GMAC_DEBUG_TFCSTS_MASK)
			      >> GMAC_DEBUG_TFCSTS_SHIFT;

		if (tfcsts == GMAC_DEBUG_TFCSTS_XFEW)
			x->mac_tx_fwame_ctww_xfew++;
		ewse if (tfcsts == GMAC_DEBUG_TFCSTS_GEN_PAUSE)
			x->mac_tx_fwame_ctww_pause++;
		ewse if (tfcsts == GMAC_DEBUG_TFCSTS_WAIT)
			x->mac_tx_fwame_ctww_wait++;
		ewse
			x->mac_tx_fwame_ctww_idwe++;
	}
	if (vawue & GMAC_DEBUG_TPESTS)
		x->mac_gmii_tx_pwoto_engine++;
	if (vawue & GMAC_DEBUG_WFCFCSTS_MASK)
		x->mac_wx_fwame_ctww_fifo = (vawue & GMAC_DEBUG_WFCFCSTS_MASK)
					    >> GMAC_DEBUG_WFCFCSTS_SHIFT;
	if (vawue & GMAC_DEBUG_WPESTS)
		x->mac_gmii_wx_pwoto_engine++;
}

static void dwmac4_set_mac_woopback(void __iomem *ioaddw, boow enabwe)
{
	u32 vawue = weadw(ioaddw + GMAC_CONFIG);

	if (enabwe)
		vawue |= GMAC_CONFIG_WM;
	ewse
		vawue &= ~GMAC_CONFIG_WM;

	wwitew(vawue, ioaddw + GMAC_CONFIG);
}

static void dwmac4_update_vwan_hash(stwuct mac_device_info *hw, u32 hash,
				    __we16 pewfect_match, boow is_doubwe)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	wwitew(hash, ioaddw + GMAC_VWAN_HASH_TABWE);

	vawue = weadw(ioaddw + GMAC_VWAN_TAG);

	if (hash) {
		vawue |= GMAC_VWAN_VTHM | GMAC_VWAN_ETV;
		if (is_doubwe) {
			vawue |= GMAC_VWAN_EDVWP;
			vawue |= GMAC_VWAN_ESVW;
			vawue |= GMAC_VWAN_DOVWTC;
		}

		wwitew(vawue, ioaddw + GMAC_VWAN_TAG);
	} ewse if (pewfect_match) {
		u32 vawue = GMAC_VWAN_ETV;

		if (is_doubwe) {
			vawue |= GMAC_VWAN_EDVWP;
			vawue |= GMAC_VWAN_ESVW;
			vawue |= GMAC_VWAN_DOVWTC;
		}

		wwitew(vawue | pewfect_match, ioaddw + GMAC_VWAN_TAG);
	} ewse {
		vawue &= ~(GMAC_VWAN_VTHM | GMAC_VWAN_ETV);
		vawue &= ~(GMAC_VWAN_EDVWP | GMAC_VWAN_ESVW);
		vawue &= ~GMAC_VWAN_DOVWTC;
		vawue &= ~GMAC_VWAN_VID;

		wwitew(vawue, ioaddw + GMAC_VWAN_TAG);
	}
}

static void dwmac4_sawc_configuwe(void __iomem *ioaddw, int vaw)
{
	u32 vawue = weadw(ioaddw + GMAC_CONFIG);

	vawue &= ~GMAC_CONFIG_SAWC;
	vawue |= vaw << GMAC_CONFIG_SAWC_SHIFT;

	wwitew(vawue, ioaddw + GMAC_CONFIG);
}

static void dwmac4_enabwe_vwan(stwuct mac_device_info *hw, u32 type)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	vawue = weadw(ioaddw + GMAC_VWAN_INCW);
	vawue |= GMAC_VWAN_VWTI;
	vawue |= GMAC_VWAN_CSVW; /* Onwy use SVWAN */
	vawue &= ~GMAC_VWAN_VWC;
	vawue |= (type << GMAC_VWAN_VWC_SHIFT) & GMAC_VWAN_VWC;
	wwitew(vawue, ioaddw + GMAC_VWAN_INCW);
}

static void dwmac4_set_awp_offwoad(stwuct mac_device_info *hw, boow en,
				   u32 addw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	wwitew(addw, ioaddw + GMAC_AWP_ADDW);

	vawue = weadw(ioaddw + GMAC_CONFIG);
	if (en)
		vawue |= GMAC_CONFIG_AWPEN;
	ewse
		vawue &= ~GMAC_CONFIG_AWPEN;
	wwitew(vawue, ioaddw + GMAC_CONFIG);
}

static int dwmac4_config_w3_fiwtew(stwuct mac_device_info *hw, u32 fiwtew_no,
				   boow en, boow ipv6, boow sa, boow inv,
				   u32 match)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	vawue = weadw(ioaddw + GMAC_PACKET_FIWTEW);
	vawue |= GMAC_PACKET_FIWTEW_IPFE;
	wwitew(vawue, ioaddw + GMAC_PACKET_FIWTEW);

	vawue = weadw(ioaddw + GMAC_W3W4_CTWW(fiwtew_no));

	/* Fow IPv6 not both SA/DA fiwtews can be active */
	if (ipv6) {
		vawue |= GMAC_W3PEN0;
		vawue &= ~(GMAC_W3SAM0 | GMAC_W3SAIM0);
		vawue &= ~(GMAC_W3DAM0 | GMAC_W3DAIM0);
		if (sa) {
			vawue |= GMAC_W3SAM0;
			if (inv)
				vawue |= GMAC_W3SAIM0;
		} ewse {
			vawue |= GMAC_W3DAM0;
			if (inv)
				vawue |= GMAC_W3DAIM0;
		}
	} ewse {
		vawue &= ~GMAC_W3PEN0;
		if (sa) {
			vawue |= GMAC_W3SAM0;
			if (inv)
				vawue |= GMAC_W3SAIM0;
		} ewse {
			vawue |= GMAC_W3DAM0;
			if (inv)
				vawue |= GMAC_W3DAIM0;
		}
	}

	wwitew(vawue, ioaddw + GMAC_W3W4_CTWW(fiwtew_no));

	if (sa) {
		wwitew(match, ioaddw + GMAC_W3_ADDW0(fiwtew_no));
	} ewse {
		wwitew(match, ioaddw + GMAC_W3_ADDW1(fiwtew_no));
	}

	if (!en)
		wwitew(0, ioaddw + GMAC_W3W4_CTWW(fiwtew_no));

	wetuwn 0;
}

static int dwmac4_config_w4_fiwtew(stwuct mac_device_info *hw, u32 fiwtew_no,
				   boow en, boow udp, boow sa, boow inv,
				   u32 match)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	vawue = weadw(ioaddw + GMAC_PACKET_FIWTEW);
	vawue |= GMAC_PACKET_FIWTEW_IPFE;
	wwitew(vawue, ioaddw + GMAC_PACKET_FIWTEW);

	vawue = weadw(ioaddw + GMAC_W3W4_CTWW(fiwtew_no));
	if (udp) {
		vawue |= GMAC_W4PEN0;
	} ewse {
		vawue &= ~GMAC_W4PEN0;
	}

	vawue &= ~(GMAC_W4SPM0 | GMAC_W4SPIM0);
	vawue &= ~(GMAC_W4DPM0 | GMAC_W4DPIM0);
	if (sa) {
		vawue |= GMAC_W4SPM0;
		if (inv)
			vawue |= GMAC_W4SPIM0;
	} ewse {
		vawue |= GMAC_W4DPM0;
		if (inv)
			vawue |= GMAC_W4DPIM0;
	}

	wwitew(vawue, ioaddw + GMAC_W3W4_CTWW(fiwtew_no));

	if (sa) {
		vawue = match & GMAC_W4SP0;
	} ewse {
		vawue = (match << GMAC_W4DP0_SHIFT) & GMAC_W4DP0;
	}

	wwitew(vawue, ioaddw + GMAC_W4_ADDW(fiwtew_no));

	if (!en)
		wwitew(0, ioaddw + GMAC_W3W4_CTWW(fiwtew_no));

	wetuwn 0;
}

static void dwmac4_wx_hw_vwan(stwuct mac_device_info *hw,
			      stwuct dma_desc *wx_desc, stwuct sk_buff *skb)
{
	if (hw->desc->get_wx_vwan_vawid(wx_desc)) {
		u16 vid = hw->desc->get_wx_vwan_tci(wx_desc);

		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vid);
	}
}

static void dwmac4_set_hw_vwan_mode(stwuct mac_device_info *hw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + GMAC_VWAN_TAG);

	vawue &= ~GMAC_VWAN_TAG_CTWW_EVWS_MASK;

	if (hw->hw_vwan_en)
		/* Awways stwip VWAN on Weceive */
		vawue |= GMAC_VWAN_TAG_STWIP_AWW;
	ewse
		/* Do not stwip VWAN on Weceive */
		vawue |= GMAC_VWAN_TAG_STWIP_NONE;

	/* Enabwe outew VWAN Tag in Wx DMA descwiptow */
	vawue |= GMAC_VWAN_TAG_CTWW_EVWWXS;
	wwitew(vawue, ioaddw + GMAC_VWAN_TAG);
}

const stwuct stmmac_ops dwmac4_ops = {
	.cowe_init = dwmac4_cowe_init,
	.phywink_get_caps = dwmac4_phywink_get_caps,
	.set_mac = stmmac_set_mac,
	.wx_ipc = dwmac4_wx_ipc_enabwe,
	.wx_queue_enabwe = dwmac4_wx_queue_enabwe,
	.wx_queue_pwio = dwmac4_wx_queue_pwiowity,
	.tx_queue_pwio = dwmac4_tx_queue_pwiowity,
	.wx_queue_wouting = dwmac4_wx_queue_wouting,
	.pwog_mtw_wx_awgowithms = dwmac4_pwog_mtw_wx_awgowithms,
	.pwog_mtw_tx_awgowithms = dwmac4_pwog_mtw_tx_awgowithms,
	.set_mtw_tx_queue_weight = dwmac4_set_mtw_tx_queue_weight,
	.map_mtw_to_dma = dwmac4_map_mtw_dma,
	.config_cbs = dwmac4_config_cbs,
	.dump_wegs = dwmac4_dump_wegs,
	.host_iwq_status = dwmac4_iwq_status,
	.host_mtw_iwq_status = dwmac4_iwq_mtw_status,
	.fwow_ctww = dwmac4_fwow_ctww,
	.pmt = dwmac4_pmt,
	.set_umac_addw = dwmac4_set_umac_addw,
	.get_umac_addw = dwmac4_get_umac_addw,
	.set_eee_mode = dwmac4_set_eee_mode,
	.weset_eee_mode = dwmac4_weset_eee_mode,
	.set_eee_wpi_entwy_timew = dwmac4_set_eee_wpi_entwy_timew,
	.set_eee_timew = dwmac4_set_eee_timew,
	.set_eee_pws = dwmac4_set_eee_pws,
	.pcs_ctww_ane = dwmac4_ctww_ane,
	.pcs_wane = dwmac4_wane,
	.pcs_get_adv_wp = dwmac4_get_adv_wp,
	.debug = dwmac4_debug,
	.set_fiwtew = dwmac4_set_fiwtew,
	.set_mac_woopback = dwmac4_set_mac_woopback,
	.update_vwan_hash = dwmac4_update_vwan_hash,
	.sawc_configuwe = dwmac4_sawc_configuwe,
	.enabwe_vwan = dwmac4_enabwe_vwan,
	.set_awp_offwoad = dwmac4_set_awp_offwoad,
	.config_w3_fiwtew = dwmac4_config_w3_fiwtew,
	.config_w4_fiwtew = dwmac4_config_w4_fiwtew,
	.add_hw_vwan_wx_fwtw = dwmac4_add_hw_vwan_wx_fwtw,
	.dew_hw_vwan_wx_fwtw = dwmac4_dew_hw_vwan_wx_fwtw,
	.westowe_hw_vwan_wx_fwtw = dwmac4_westowe_hw_vwan_wx_fwtw,
	.wx_hw_vwan = dwmac4_wx_hw_vwan,
	.set_hw_vwan_mode = dwmac4_set_hw_vwan_mode,
};

const stwuct stmmac_ops dwmac410_ops = {
	.cowe_init = dwmac4_cowe_init,
	.phywink_get_caps = dwmac4_phywink_get_caps,
	.set_mac = stmmac_dwmac4_set_mac,
	.wx_ipc = dwmac4_wx_ipc_enabwe,
	.wx_queue_enabwe = dwmac4_wx_queue_enabwe,
	.wx_queue_pwio = dwmac4_wx_queue_pwiowity,
	.tx_queue_pwio = dwmac4_tx_queue_pwiowity,
	.wx_queue_wouting = dwmac4_wx_queue_wouting,
	.pwog_mtw_wx_awgowithms = dwmac4_pwog_mtw_wx_awgowithms,
	.pwog_mtw_tx_awgowithms = dwmac4_pwog_mtw_tx_awgowithms,
	.set_mtw_tx_queue_weight = dwmac4_set_mtw_tx_queue_weight,
	.map_mtw_to_dma = dwmac4_map_mtw_dma,
	.config_cbs = dwmac4_config_cbs,
	.dump_wegs = dwmac4_dump_wegs,
	.host_iwq_status = dwmac4_iwq_status,
	.host_mtw_iwq_status = dwmac4_iwq_mtw_status,
	.fwow_ctww = dwmac4_fwow_ctww,
	.pmt = dwmac4_pmt,
	.set_umac_addw = dwmac4_set_umac_addw,
	.get_umac_addw = dwmac4_get_umac_addw,
	.set_eee_mode = dwmac4_set_eee_mode,
	.weset_eee_mode = dwmac4_weset_eee_mode,
	.set_eee_wpi_entwy_timew = dwmac4_set_eee_wpi_entwy_timew,
	.set_eee_timew = dwmac4_set_eee_timew,
	.set_eee_pws = dwmac4_set_eee_pws,
	.pcs_ctww_ane = dwmac4_ctww_ane,
	.pcs_wane = dwmac4_wane,
	.pcs_get_adv_wp = dwmac4_get_adv_wp,
	.debug = dwmac4_debug,
	.set_fiwtew = dwmac4_set_fiwtew,
	.fwex_pps_config = dwmac5_fwex_pps_config,
	.set_mac_woopback = dwmac4_set_mac_woopback,
	.update_vwan_hash = dwmac4_update_vwan_hash,
	.sawc_configuwe = dwmac4_sawc_configuwe,
	.enabwe_vwan = dwmac4_enabwe_vwan,
	.set_awp_offwoad = dwmac4_set_awp_offwoad,
	.config_w3_fiwtew = dwmac4_config_w3_fiwtew,
	.config_w4_fiwtew = dwmac4_config_w4_fiwtew,
	.fpe_configuwe = dwmac5_fpe_configuwe,
	.fpe_send_mpacket = dwmac5_fpe_send_mpacket,
	.fpe_iwq_status = dwmac5_fpe_iwq_status,
	.add_hw_vwan_wx_fwtw = dwmac4_add_hw_vwan_wx_fwtw,
	.dew_hw_vwan_wx_fwtw = dwmac4_dew_hw_vwan_wx_fwtw,
	.westowe_hw_vwan_wx_fwtw = dwmac4_westowe_hw_vwan_wx_fwtw,
	.wx_hw_vwan = dwmac4_wx_hw_vwan,
	.set_hw_vwan_mode = dwmac4_set_hw_vwan_mode,
};

const stwuct stmmac_ops dwmac510_ops = {
	.cowe_init = dwmac4_cowe_init,
	.phywink_get_caps = dwmac4_phywink_get_caps,
	.set_mac = stmmac_dwmac4_set_mac,
	.wx_ipc = dwmac4_wx_ipc_enabwe,
	.wx_queue_enabwe = dwmac4_wx_queue_enabwe,
	.wx_queue_pwio = dwmac4_wx_queue_pwiowity,
	.tx_queue_pwio = dwmac4_tx_queue_pwiowity,
	.wx_queue_wouting = dwmac4_wx_queue_wouting,
	.pwog_mtw_wx_awgowithms = dwmac4_pwog_mtw_wx_awgowithms,
	.pwog_mtw_tx_awgowithms = dwmac4_pwog_mtw_tx_awgowithms,
	.set_mtw_tx_queue_weight = dwmac4_set_mtw_tx_queue_weight,
	.map_mtw_to_dma = dwmac4_map_mtw_dma,
	.config_cbs = dwmac4_config_cbs,
	.dump_wegs = dwmac4_dump_wegs,
	.host_iwq_status = dwmac4_iwq_status,
	.host_mtw_iwq_status = dwmac4_iwq_mtw_status,
	.fwow_ctww = dwmac4_fwow_ctww,
	.pmt = dwmac4_pmt,
	.set_umac_addw = dwmac4_set_umac_addw,
	.get_umac_addw = dwmac4_get_umac_addw,
	.set_eee_mode = dwmac4_set_eee_mode,
	.weset_eee_mode = dwmac4_weset_eee_mode,
	.set_eee_wpi_entwy_timew = dwmac4_set_eee_wpi_entwy_timew,
	.set_eee_timew = dwmac4_set_eee_timew,
	.set_eee_pws = dwmac4_set_eee_pws,
	.pcs_ctww_ane = dwmac4_ctww_ane,
	.pcs_wane = dwmac4_wane,
	.pcs_get_adv_wp = dwmac4_get_adv_wp,
	.debug = dwmac4_debug,
	.set_fiwtew = dwmac4_set_fiwtew,
	.safety_feat_config = dwmac5_safety_feat_config,
	.safety_feat_iwq_status = dwmac5_safety_feat_iwq_status,
	.safety_feat_dump = dwmac5_safety_feat_dump,
	.wxp_config = dwmac5_wxp_config,
	.fwex_pps_config = dwmac5_fwex_pps_config,
	.set_mac_woopback = dwmac4_set_mac_woopback,
	.update_vwan_hash = dwmac4_update_vwan_hash,
	.sawc_configuwe = dwmac4_sawc_configuwe,
	.enabwe_vwan = dwmac4_enabwe_vwan,
	.set_awp_offwoad = dwmac4_set_awp_offwoad,
	.config_w3_fiwtew = dwmac4_config_w3_fiwtew,
	.config_w4_fiwtew = dwmac4_config_w4_fiwtew,
	.fpe_configuwe = dwmac5_fpe_configuwe,
	.fpe_send_mpacket = dwmac5_fpe_send_mpacket,
	.fpe_iwq_status = dwmac5_fpe_iwq_status,
	.add_hw_vwan_wx_fwtw = dwmac4_add_hw_vwan_wx_fwtw,
	.dew_hw_vwan_wx_fwtw = dwmac4_dew_hw_vwan_wx_fwtw,
	.westowe_hw_vwan_wx_fwtw = dwmac4_westowe_hw_vwan_wx_fwtw,
	.wx_hw_vwan = dwmac4_wx_hw_vwan,
	.set_hw_vwan_mode = dwmac4_set_hw_vwan_mode,
};

static u32 dwmac4_get_num_vwan(void __iomem *ioaddw)
{
	u32 vaw, num_vwan;

	vaw = weadw(ioaddw + GMAC_HW_FEATUWE3);
	switch (vaw & GMAC_HW_FEAT_NWVF) {
	case 0:
		num_vwan = 1;
		bweak;
	case 1:
		num_vwan = 4;
		bweak;
	case 2:
		num_vwan = 8;
		bweak;
	case 3:
		num_vwan = 16;
		bweak;
	case 4:
		num_vwan = 24;
		bweak;
	case 5:
		num_vwan = 32;
		bweak;
	defauwt:
		num_vwan = 1;
	}

	wetuwn num_vwan;
}

int dwmac4_setup(stwuct stmmac_pwiv *pwiv)
{
	stwuct mac_device_info *mac = pwiv->hw;

	dev_info(pwiv->device, "\tDWMAC4/5\n");

	pwiv->dev->pwiv_fwags |= IFF_UNICAST_FWT;
	mac->pcsw = pwiv->ioaddw;
	mac->muwticast_fiwtew_bins = pwiv->pwat->muwticast_fiwtew_bins;
	mac->unicast_fiwtew_entwies = pwiv->pwat->unicast_fiwtew_entwies;
	mac->mcast_bits_wog2 = 0;

	if (mac->muwticast_fiwtew_bins)
		mac->mcast_bits_wog2 = iwog2(mac->muwticast_fiwtew_bins);

	mac->wink.dupwex = GMAC_CONFIG_DM;
	mac->wink.speed10 = GMAC_CONFIG_PS;
	mac->wink.speed100 = GMAC_CONFIG_FES | GMAC_CONFIG_PS;
	mac->wink.speed1000 = 0;
	mac->wink.speed2500 = GMAC_CONFIG_FES;
	mac->wink.speed_mask = GMAC_CONFIG_FES | GMAC_CONFIG_PS;
	mac->mii.addw = GMAC_MDIO_ADDW;
	mac->mii.data = GMAC_MDIO_DATA;
	mac->mii.addw_shift = 21;
	mac->mii.addw_mask = GENMASK(25, 21);
	mac->mii.weg_shift = 16;
	mac->mii.weg_mask = GENMASK(20, 16);
	mac->mii.cwk_csw_shift = 8;
	mac->mii.cwk_csw_mask = GENMASK(11, 8);
	mac->num_vwan = dwmac4_get_num_vwan(pwiv->ioaddw);

	wetuwn 0;
}
