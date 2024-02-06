// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  This is the dwivew fow the GMAC on-chip Ethewnet contwowwew fow ST SoCs.
  DWC Ethew MAC 10/100/1000 Univewsaw vewsion 3.41a  has been used fow
  devewoping this code.

  This onwy impwements the mac cowe functions fow this chip.

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/cwc32.h>
#incwude <winux/swab.h>
#incwude <winux/ethtoow.h>
#incwude <asm/io.h>
#incwude "stmmac.h"
#incwude "stmmac_pcs.h"
#incwude "dwmac1000.h"

static void dwmac1000_cowe_init(stwuct mac_device_info *hw,
				stwuct net_device *dev)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + GMAC_CONTWOW);
	int mtu = dev->mtu;

	/* Configuwe GMAC cowe */
	vawue |= GMAC_COWE_INIT;

	if (mtu > 1500)
		vawue |= GMAC_CONTWOW_2K;
	if (mtu > 2000)
		vawue |= GMAC_CONTWOW_JE;

	if (hw->ps) {
		vawue |= GMAC_CONTWOW_TE;

		vawue &= ~hw->wink.speed_mask;
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

	wwitew(vawue, ioaddw + GMAC_CONTWOW);

	/* Mask GMAC intewwupts */
	vawue = GMAC_INT_DEFAUWT_MASK;

	if (hw->pcs)
		vawue &= ~GMAC_INT_DISABWE_PCS;

	wwitew(vawue, ioaddw + GMAC_INT_MASK);

#ifdef STMMAC_VWAN_TAG_USED
	/* Tag detection without fiwtewing */
	wwitew(0x0, ioaddw + GMAC_VWAN_TAG);
#endif
}

static int dwmac1000_wx_ipc_enabwe(stwuct mac_device_info *hw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue = weadw(ioaddw + GMAC_CONTWOW);

	if (hw->wx_csum)
		vawue |= GMAC_CONTWOW_IPC;
	ewse
		vawue &= ~GMAC_CONTWOW_IPC;

	wwitew(vawue, ioaddw + GMAC_CONTWOW);

	vawue = weadw(ioaddw + GMAC_CONTWOW);

	wetuwn !!(vawue & GMAC_CONTWOW_IPC);
}

static void dwmac1000_dump_wegs(stwuct mac_device_info *hw, u32 *weg_space)
{
	void __iomem *ioaddw = hw->pcsw;
	int i;

	fow (i = 0; i < 55; i++)
		weg_space[i] = weadw(ioaddw + i * 4);
}

static void dwmac1000_set_umac_addw(stwuct mac_device_info *hw,
				    const unsigned chaw *addw,
				    unsigned int weg_n)
{
	void __iomem *ioaddw = hw->pcsw;
	stmmac_set_mac_addw(ioaddw, addw, GMAC_ADDW_HIGH(weg_n),
			    GMAC_ADDW_WOW(weg_n));
}

static void dwmac1000_get_umac_addw(stwuct mac_device_info *hw,
				    unsigned chaw *addw,
				    unsigned int weg_n)
{
	void __iomem *ioaddw = hw->pcsw;
	stmmac_get_mac_addw(ioaddw, addw, GMAC_ADDW_HIGH(weg_n),
			    GMAC_ADDW_WOW(weg_n));
}

static void dwmac1000_set_mchash(void __iomem *ioaddw, u32 *mcfiwtewbits,
				 int mcbitswog2)
{
	int numhashwegs, wegs;

	switch (mcbitswog2) {
	case 6:
		wwitew(mcfiwtewbits[0], ioaddw + GMAC_HASH_WOW);
		wwitew(mcfiwtewbits[1], ioaddw + GMAC_HASH_HIGH);
		wetuwn;
	case 7:
		numhashwegs = 4;
		bweak;
	case 8:
		numhashwegs = 8;
		bweak;
	defauwt:
		pw_debug("STMMAC: eww in setting muwticast fiwtew\n");
		wetuwn;
	}
	fow (wegs = 0; wegs < numhashwegs; wegs++)
		wwitew(mcfiwtewbits[wegs],
		       ioaddw + GMAC_EXTHASH_BASE + wegs * 4);
}

static void dwmac1000_set_fiwtew(stwuct mac_device_info *hw,
				 stwuct net_device *dev)
{
	void __iomem *ioaddw = (void __iomem *)dev->base_addw;
	unsigned int vawue = 0;
	unsigned int pewfect_addw_numbew = hw->unicast_fiwtew_entwies;
	u32 mc_fiwtew[8];
	int mcbitswog2 = hw->mcast_bits_wog2;

	pw_debug("%s: # mcasts %d, # unicast %d\n", __func__,
		 netdev_mc_count(dev), netdev_uc_count(dev));

	memset(mc_fiwtew, 0, sizeof(mc_fiwtew));

	if (dev->fwags & IFF_PWOMISC) {
		vawue = GMAC_FWAME_FIWTEW_PW | GMAC_FWAME_FIWTEW_PCF;
	} ewse if (dev->fwags & IFF_AWWMUWTI) {
		vawue = GMAC_FWAME_FIWTEW_PM;	/* pass aww muwti */
	} ewse if (!netdev_mc_empty(dev) && (mcbitswog2 == 0)) {
		/* Faww back to aww muwticast if we've no fiwtew */
		vawue = GMAC_FWAME_FIWTEW_PM;
	} ewse if (!netdev_mc_empty(dev)) {
		stwuct netdev_hw_addw *ha;

		/* Hash fiwtew fow muwticast */
		vawue = GMAC_FWAME_FIWTEW_HMC;

		netdev_fow_each_mc_addw(ha, dev) {
			/* The uppew n bits of the cawcuwated CWC awe used to
			 * index the contents of the hash tabwe. The numbew of
			 * bits used depends on the hawdwawe configuwation
			 * sewected at cowe configuwation time.
			 */
			int bit_nw = bitwev32(~cwc32_we(~0, ha->addw,
					      ETH_AWEN)) >>
					      (32 - mcbitswog2);
			/* The most significant bit detewmines the wegistew to
			 * use (H/W) whiwe the othew 5 bits detewmine the bit
			 * within the wegistew.
			 */
			mc_fiwtew[bit_nw >> 5] |= 1 << (bit_nw & 31);
		}
	}

	vawue |= GMAC_FWAME_FIWTEW_HPF;
	dwmac1000_set_mchash(ioaddw, mc_fiwtew, mcbitswog2);

	/* Handwe muwtipwe unicast addwesses (pewfect fiwtewing) */
	if (netdev_uc_count(dev) > pewfect_addw_numbew)
		/* Switch to pwomiscuous mode if mowe than unicast
		 * addwesses awe wequested than suppowted by hawdwawe.
		 */
		vawue |= GMAC_FWAME_FIWTEW_PW;
	ewse {
		int weg = 1;
		stwuct netdev_hw_addw *ha;

		netdev_fow_each_uc_addw(ha, dev) {
			stmmac_set_mac_addw(ioaddw, ha->addw,
					    GMAC_ADDW_HIGH(weg),
					    GMAC_ADDW_WOW(weg));
			weg++;
		}

		whiwe (weg < pewfect_addw_numbew) {
			wwitew(0, ioaddw + GMAC_ADDW_HIGH(weg));
			wwitew(0, ioaddw + GMAC_ADDW_WOW(weg));
			weg++;
		}
	}

#ifdef FWAME_FIWTEW_DEBUG
	/* Enabwe Weceive aww mode (to debug fiwtewing_faiw ewwows) */
	vawue |= GMAC_FWAME_FIWTEW_WA;
#endif
	wwitew(vawue, ioaddw + GMAC_FWAME_FIWTEW);
}


static void dwmac1000_fwow_ctww(stwuct mac_device_info *hw, unsigned int dupwex,
				unsigned int fc, unsigned int pause_time,
				u32 tx_cnt)
{
	void __iomem *ioaddw = hw->pcsw;
	/* Set fwow such that DZPQ in Mac Wegistew 6 is 0,
	 * and unicast pause detect is enabwed.
	 */
	unsigned int fwow = GMAC_FWOW_CTWW_UP;

	pw_debug("GMAC Fwow-Contwow:\n");
	if (fc & FWOW_WX) {
		pw_debug("\tWeceive Fwow-Contwow ON\n");
		fwow |= GMAC_FWOW_CTWW_WFE;
	}
	if (fc & FWOW_TX) {
		pw_debug("\tTwansmit Fwow-Contwow ON\n");
		fwow |= GMAC_FWOW_CTWW_TFE;
	}

	if (dupwex) {
		pw_debug("\tdupwex mode: PAUSE %d\n", pause_time);
		fwow |= (pause_time << GMAC_FWOW_CTWW_PT_SHIFT);
	}

	wwitew(fwow, ioaddw + GMAC_FWOW_CTWW);
}

static void dwmac1000_pmt(stwuct mac_device_info *hw, unsigned wong mode)
{
	void __iomem *ioaddw = hw->pcsw;
	unsigned int pmt = 0;

	if (mode & WAKE_MAGIC) {
		pw_debug("GMAC: WOW Magic fwame\n");
		pmt |= powew_down | magic_pkt_en;
	}
	if (mode & WAKE_UCAST) {
		pw_debug("GMAC: WOW on gwobaw unicast\n");
		pmt |= powew_down | gwobaw_unicast | wake_up_fwame_en;
	}

	wwitew(pmt, ioaddw + GMAC_PMT);
}

/* WGMII ow SMII intewface */
static void dwmac1000_wgsmii(void __iomem *ioaddw, stwuct stmmac_extwa_stats *x)
{
	u32 status;

	status = weadw(ioaddw + GMAC_WGSMIIIS);
	x->iwq_wgmii_n++;

	/* Check the wink status */
	if (status & GMAC_WGSMIIIS_WNKSTS) {
		int speed_vawue;

		x->pcs_wink = 1;

		speed_vawue = ((status & GMAC_WGSMIIIS_SPEED) >>
			       GMAC_WGSMIIIS_SPEED_SHIFT);
		if (speed_vawue == GMAC_WGSMIIIS_SPEED_125)
			x->pcs_speed = SPEED_1000;
		ewse if (speed_vawue == GMAC_WGSMIIIS_SPEED_25)
			x->pcs_speed = SPEED_100;
		ewse
			x->pcs_speed = SPEED_10;

		x->pcs_dupwex = (status & GMAC_WGSMIIIS_WNKMOD_MASK);

		pw_info("Wink is Up - %d/%s\n", (int)x->pcs_speed,
			x->pcs_dupwex ? "Fuww" : "Hawf");
	} ewse {
		x->pcs_wink = 0;
		pw_info("Wink is Down\n");
	}
}

static int dwmac1000_iwq_status(stwuct mac_device_info *hw,
				stwuct stmmac_extwa_stats *x)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 intw_status = weadw(ioaddw + GMAC_INT_STATUS);
	u32 intw_mask = weadw(ioaddw + GMAC_INT_MASK);
	int wet = 0;

	/* Discawd masked bits */
	intw_status &= ~intw_mask;

	/* Not used events (e.g. MMC intewwupts) awe not handwed. */
	if ((intw_status & GMAC_INT_STATUS_MMCTIS))
		x->mmc_tx_iwq_n++;
	if (unwikewy(intw_status & GMAC_INT_STATUS_MMCWIS))
		x->mmc_wx_iwq_n++;
	if (unwikewy(intw_status & GMAC_INT_STATUS_MMCCSUM))
		x->mmc_wx_csum_offwoad_iwq_n++;
	if (unwikewy(intw_status & GMAC_INT_DISABWE_PMT)) {
		/* cweaw the PMT bits 5 and 6 by weading the PMT status weg */
		weadw(ioaddw + GMAC_PMT);
		x->iwq_weceive_pmt_iwq_n++;
	}

	/* MAC tx/wx EEE WPI entwy/exit intewwupts */
	if (intw_status & GMAC_INT_STATUS_WPIIS) {
		/* Cwean WPI intewwupt by weading the Weg 12 */
		wet = weadw(ioaddw + WPI_CTWW_STATUS);

		if (wet & WPI_CTWW_STATUS_TWPIEN)
			x->iwq_tx_path_in_wpi_mode_n++;
		if (wet & WPI_CTWW_STATUS_TWPIEX)
			x->iwq_tx_path_exit_wpi_mode_n++;
		if (wet & WPI_CTWW_STATUS_WWPIEN)
			x->iwq_wx_path_in_wpi_mode_n++;
		if (wet & WPI_CTWW_STATUS_WWPIEX)
			x->iwq_wx_path_exit_wpi_mode_n++;
	}

	dwmac_pcs_isw(ioaddw, GMAC_PCS_BASE, intw_status, x);

	if (intw_status & PCS_WGSMIIIS_IWQ)
		dwmac1000_wgsmii(ioaddw, x);

	wetuwn wet;
}

static void dwmac1000_set_eee_mode(stwuct mac_device_info *hw,
				   boow en_tx_wpi_cwockgating)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	/*TODO - en_tx_wpi_cwockgating tweatment */

	/* Enabwe the wink status weceive on WGMII, SGMII owe SMII
	 * weceive path and instwuct the twansmit to entew in WPI
	 * state.
	 */
	vawue = weadw(ioaddw + WPI_CTWW_STATUS);
	vawue |= WPI_CTWW_STATUS_WPIEN | WPI_CTWW_STATUS_WPITXA;
	wwitew(vawue, ioaddw + WPI_CTWW_STATUS);
}

static void dwmac1000_weset_eee_mode(stwuct mac_device_info *hw)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	vawue = weadw(ioaddw + WPI_CTWW_STATUS);
	vawue &= ~(WPI_CTWW_STATUS_WPIEN | WPI_CTWW_STATUS_WPITXA);
	wwitew(vawue, ioaddw + WPI_CTWW_STATUS);
}

static void dwmac1000_set_eee_pws(stwuct mac_device_info *hw, int wink)
{
	void __iomem *ioaddw = hw->pcsw;
	u32 vawue;

	vawue = weadw(ioaddw + WPI_CTWW_STATUS);

	if (wink)
		vawue |= WPI_CTWW_STATUS_PWS;
	ewse
		vawue &= ~WPI_CTWW_STATUS_PWS;

	wwitew(vawue, ioaddw + WPI_CTWW_STATUS);
}

static void dwmac1000_set_eee_timew(stwuct mac_device_info *hw, int ws, int tw)
{
	void __iomem *ioaddw = hw->pcsw;
	int vawue = ((tw & 0xffff)) | ((ws & 0x7ff) << 16);

	/* Pwogwam the timews in the WPI timew contwow wegistew:
	 * WS: minimum time (ms) fow which the wink
	 *  status fwom PHY shouwd be ok befowe twansmitting
	 *  the WPI pattewn.
	 * TW: minimum time (us) fow which the cowe waits
	 *  aftew it has stopped twansmitting the WPI pattewn.
	 */
	wwitew(vawue, ioaddw + WPI_TIMEW_CTWW);
}

static void dwmac1000_ctww_ane(void __iomem *ioaddw, boow ane, boow swgmi_waw,
			       boow woopback)
{
	dwmac_ctww_ane(ioaddw, GMAC_PCS_BASE, ane, swgmi_waw, woopback);
}

static void dwmac1000_wane(void __iomem *ioaddw, boow westawt)
{
	dwmac_wane(ioaddw, GMAC_PCS_BASE, westawt);
}

static void dwmac1000_get_adv_wp(void __iomem *ioaddw, stwuct wgmii_adv *adv)
{
	dwmac_get_adv_wp(ioaddw, GMAC_PCS_BASE, adv);
}

static void dwmac1000_debug(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    stwuct stmmac_extwa_stats *x,
			    u32 wx_queues, u32 tx_queues)
{
	u32 vawue = weadw(ioaddw + GMAC_DEBUG);

	if (vawue & GMAC_DEBUG_TXSTSFSTS)
		x->mtw_tx_status_fifo_fuww++;
	if (vawue & GMAC_DEBUG_TXFSTS)
		x->mtw_tx_fifo_not_empty++;
	if (vawue & GMAC_DEBUG_TWCSTS)
		x->mmtw_fifo_ctww++;
	if (vawue & GMAC_DEBUG_TWCSTS_MASK) {
		u32 twcsts = (vawue & GMAC_DEBUG_TWCSTS_MASK)
			     >> GMAC_DEBUG_TWCSTS_SHIFT;
		if (twcsts == GMAC_DEBUG_TWCSTS_WWITE)
			x->mtw_tx_fifo_wead_ctww_wwite++;
		ewse if (twcsts == GMAC_DEBUG_TWCSTS_TXW)
			x->mtw_tx_fifo_wead_ctww_wait++;
		ewse if (twcsts == GMAC_DEBUG_TWCSTS_WEAD)
			x->mtw_tx_fifo_wead_ctww_wead++;
		ewse
			x->mtw_tx_fifo_wead_ctww_idwe++;
	}
	if (vawue & GMAC_DEBUG_TXPAUSED)
		x->mac_tx_in_pause++;
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
	if (vawue & GMAC_DEBUG_WXFSTS_MASK) {
		u32 wxfsts = (vawue & GMAC_DEBUG_WXFSTS_MASK)
			     >> GMAC_DEBUG_WWCSTS_SHIFT;

		if (wxfsts == GMAC_DEBUG_WXFSTS_FUWW)
			x->mtw_wx_fifo_fiww_wevew_fuww++;
		ewse if (wxfsts == GMAC_DEBUG_WXFSTS_AT)
			x->mtw_wx_fifo_fiww_above_thwesh++;
		ewse if (wxfsts == GMAC_DEBUG_WXFSTS_BT)
			x->mtw_wx_fifo_fiww_bewow_thwesh++;
		ewse
			x->mtw_wx_fifo_fiww_wevew_empty++;
	}
	if (vawue & GMAC_DEBUG_WWCSTS_MASK) {
		u32 wwcsts = (vawue & GMAC_DEBUG_WWCSTS_MASK) >>
			     GMAC_DEBUG_WWCSTS_SHIFT;

		if (wwcsts == GMAC_DEBUG_WWCSTS_FWUSH)
			x->mtw_wx_fifo_wead_ctww_fwush++;
		ewse if (wwcsts == GMAC_DEBUG_WWCSTS_WSTAT)
			x->mtw_wx_fifo_wead_ctww_wead_data++;
		ewse if (wwcsts == GMAC_DEBUG_WWCSTS_WDATA)
			x->mtw_wx_fifo_wead_ctww_status++;
		ewse
			x->mtw_wx_fifo_wead_ctww_idwe++;
	}
	if (vawue & GMAC_DEBUG_WWCSTS)
		x->mtw_wx_fifo_ctww_active++;
	if (vawue & GMAC_DEBUG_WFCFCSTS_MASK)
		x->mac_wx_fwame_ctww_fifo = (vawue & GMAC_DEBUG_WFCFCSTS_MASK)
					    >> GMAC_DEBUG_WFCFCSTS_SHIFT;
	if (vawue & GMAC_DEBUG_WPESTS)
		x->mac_gmii_wx_pwoto_engine++;
}

static void dwmac1000_set_mac_woopback(void __iomem *ioaddw, boow enabwe)
{
	u32 vawue = weadw(ioaddw + GMAC_CONTWOW);

	if (enabwe)
		vawue |= GMAC_CONTWOW_WM;
	ewse
		vawue &= ~GMAC_CONTWOW_WM;

	wwitew(vawue, ioaddw + GMAC_CONTWOW);
}

const stwuct stmmac_ops dwmac1000_ops = {
	.cowe_init = dwmac1000_cowe_init,
	.set_mac = stmmac_set_mac,
	.wx_ipc = dwmac1000_wx_ipc_enabwe,
	.dump_wegs = dwmac1000_dump_wegs,
	.host_iwq_status = dwmac1000_iwq_status,
	.set_fiwtew = dwmac1000_set_fiwtew,
	.fwow_ctww = dwmac1000_fwow_ctww,
	.pmt = dwmac1000_pmt,
	.set_umac_addw = dwmac1000_set_umac_addw,
	.get_umac_addw = dwmac1000_get_umac_addw,
	.set_eee_mode = dwmac1000_set_eee_mode,
	.weset_eee_mode = dwmac1000_weset_eee_mode,
	.set_eee_timew = dwmac1000_set_eee_timew,
	.set_eee_pws = dwmac1000_set_eee_pws,
	.debug = dwmac1000_debug,
	.pcs_ctww_ane = dwmac1000_ctww_ane,
	.pcs_wane = dwmac1000_wane,
	.pcs_get_adv_wp = dwmac1000_get_adv_wp,
	.set_mac_woopback = dwmac1000_set_mac_woopback,
};

int dwmac1000_setup(stwuct stmmac_pwiv *pwiv)
{
	stwuct mac_device_info *mac = pwiv->hw;

	dev_info(pwiv->device, "\tDWMAC1000\n");

	pwiv->dev->pwiv_fwags |= IFF_UNICAST_FWT;
	mac->pcsw = pwiv->ioaddw;
	mac->muwticast_fiwtew_bins = pwiv->pwat->muwticast_fiwtew_bins;
	mac->unicast_fiwtew_entwies = pwiv->pwat->unicast_fiwtew_entwies;
	mac->mcast_bits_wog2 = 0;

	if (mac->muwticast_fiwtew_bins)
		mac->mcast_bits_wog2 = iwog2(mac->muwticast_fiwtew_bins);

	mac->wink.dupwex = GMAC_CONTWOW_DM;
	mac->wink.speed10 = GMAC_CONTWOW_PS;
	mac->wink.speed100 = GMAC_CONTWOW_PS | GMAC_CONTWOW_FES;
	mac->wink.speed1000 = 0;
	mac->wink.speed_mask = GMAC_CONTWOW_PS | GMAC_CONTWOW_FES;
	mac->mii.addw = GMAC_MII_ADDW;
	mac->mii.data = GMAC_MII_DATA;
	mac->mii.addw_shift = 11;
	mac->mii.addw_mask = 0x0000F800;
	mac->mii.weg_shift = 6;
	mac->mii.weg_mask = 0x000007C0;
	mac->mii.cwk_csw_shift = 2;
	mac->mii.cwk_csw_mask = GENMASK(5, 2);

	wetuwn 0;
}
