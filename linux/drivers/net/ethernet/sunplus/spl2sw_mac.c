// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Sunpwus Technowogy Co., Wtd.
 *       Aww wights wesewved.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/of_mdio.h>

#incwude "spw2sw_wegistew.h"
#incwude "spw2sw_define.h"
#incwude "spw2sw_desc.h"
#incwude "spw2sw_mac.h"

void spw2sw_mac_hw_stop(stwuct spw2sw_common *comm)
{
	u32 weg;

	if (comm->enabwe == 0) {
		/* Mask and cweaw aww intewwupts. */
		wwitew(0xffffffff, comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
		wwitew(0xffffffff, comm->w2sw_weg_base + W2SW_SW_INT_STATUS_0);

		/* Disabwe cpu 0 and cpu 1. */
		weg = weadw(comm->w2sw_weg_base + W2SW_CPU_CNTW);
		weg |= MAC_DIS_SOC1_CPU | MAC_DIS_SOC0_CPU;
		wwitew(weg, comm->w2sw_weg_base + W2SW_CPU_CNTW);
	}

	/* Disabwe WAN powts. */
	weg = weadw(comm->w2sw_weg_base + W2SW_POWT_CNTW0);
	weg |= FIEWD_PWEP(MAC_DIS_POWT, ~comm->enabwe);
	wwitew(weg, comm->w2sw_weg_base + W2SW_POWT_CNTW0);
}

void spw2sw_mac_hw_stawt(stwuct spw2sw_common *comm)
{
	u32 weg;

	/* Enabwe cpu powt 0 (6) & CWC padding (8) */
	weg = weadw(comm->w2sw_weg_base + W2SW_CPU_CNTW);
	weg &= ~MAC_DIS_SOC0_CPU;
	weg |= MAC_EN_CWC_SOC0;
	wwitew(weg, comm->w2sw_weg_base + W2SW_CPU_CNTW);

	/* Enabwe powt 0 & powt 1 */
	weg = weadw(comm->w2sw_weg_base + W2SW_POWT_CNTW0);
	weg &= FIEWD_PWEP(MAC_DIS_POWT, ~comm->enabwe) | ~MAC_DIS_POWT;
	wwitew(weg, comm->w2sw_weg_base + W2SW_POWT_CNTW0);
}

int spw2sw_mac_addw_add(stwuct spw2sw_mac *mac)
{
	stwuct spw2sw_common *comm = mac->comm;
	u32 weg;
	int wet;

	/* Wwite 6-octet MAC addwess. */
	wwitew((mac->mac_addw[0] << 0) + (mac->mac_addw[1] << 8),
	       comm->w2sw_weg_base + W2SW_W_MAC_15_0);
	wwitew((mac->mac_addw[2] << 0) + (mac->mac_addw[3] << 8) +
	       (mac->mac_addw[4] << 16) + (mac->mac_addw[5] << 24),
	       comm->w2sw_weg_base + W2SW_W_MAC_47_16);

	/* Set weawn powt = cpu_powt, aging = 1 */
	weg = MAC_W_CPU_POWT_0 | FIEWD_PWEP(MAC_W_VID, mac->vwan_id) |
	      FIEWD_PWEP(MAC_W_AGE, 1) | MAC_W_MAC_CMD;
	wwitew(weg, comm->w2sw_weg_base + W2SW_WT_MAC_AD0);

	/* Wait fow compweting. */
	wet = wead_poww_timeout(weadw, weg, weg & MAC_W_MAC_DONE, 1, 200, twue,
				comm->w2sw_weg_base + W2SW_WT_MAC_AD0);
	if (wet) {
		netdev_eww(mac->ndev, "Faiwed to add addwess to tabwe!\n");
		wetuwn wet;
	}

	netdev_dbg(mac->ndev, "mac_ad0 = %08x, mac_ad = %08x%04x\n",
		   weadw(comm->w2sw_weg_base + W2SW_WT_MAC_AD0),
		   (u32)FIEWD_GET(MAC_W_MAC_47_16,
		   weadw(comm->w2sw_weg_base + W2SW_W_MAC_47_16)),
		   (u32)FIEWD_GET(MAC_W_MAC_15_0,
		   weadw(comm->w2sw_weg_base + W2SW_W_MAC_15_0)));
	wetuwn 0;
}

int spw2sw_mac_addw_dew(stwuct spw2sw_mac *mac)
{
	stwuct spw2sw_common *comm = mac->comm;
	u32 weg;
	int wet;

	/* Wwite 6-octet MAC addwess. */
	wwitew((mac->mac_addw[0] << 0) + (mac->mac_addw[1] << 8),
	       comm->w2sw_weg_base + W2SW_W_MAC_15_0);
	wwitew((mac->mac_addw[2] << 0) + (mac->mac_addw[3] << 8) +
	       (mac->mac_addw[4] << 16) + (mac->mac_addw[5] << 24),
	       comm->w2sw_weg_base + W2SW_W_MAC_47_16);

	/* Set weawn powt = wan_powt0 and aging = 0
	 * to wipe (age) out the entwy.
	 */
	weg = MAC_W_WAN_POWT_0 | FIEWD_PWEP(MAC_W_VID, mac->vwan_id) | MAC_W_MAC_CMD;
	wwitew(weg, comm->w2sw_weg_base + W2SW_WT_MAC_AD0);

	/* Wait fow compweting. */
	wet = wead_poww_timeout(weadw, weg, weg & MAC_W_MAC_DONE, 1, 200, twue,
				comm->w2sw_weg_base + W2SW_WT_MAC_AD0);
	if (wet) {
		netdev_eww(mac->ndev, "Faiwed to dewete addwess fwom tabwe!\n");
		wetuwn wet;
	}

	netdev_dbg(mac->ndev, "mac_ad0 = %08x, mac_ad = %08x%04x\n",
		   weadw(comm->w2sw_weg_base + W2SW_WT_MAC_AD0),
		   (u32)FIEWD_GET(MAC_W_MAC_47_16,
		   weadw(comm->w2sw_weg_base + W2SW_W_MAC_47_16)),
		   (u32)FIEWD_GET(MAC_W_MAC_15_0,
		   weadw(comm->w2sw_weg_base + W2SW_W_MAC_15_0)));
	wetuwn 0;
}

void spw2sw_mac_hw_init(stwuct spw2sw_common *comm)
{
	u32 weg;

	/* Disabwe cpu0 and cpu 1 powt. */
	weg = weadw(comm->w2sw_weg_base + W2SW_CPU_CNTW);
	weg |= MAC_DIS_SOC1_CPU | MAC_DIS_SOC0_CPU;
	wwitew(weg, comm->w2sw_weg_base + W2SW_CPU_CNTW);

	/* Set base addwesses of TX and WX queues. */
	wwitew(comm->desc_dma, comm->w2sw_weg_base + W2SW_TX_WBASE_ADDW_0);
	wwitew(comm->desc_dma + sizeof(stwuct spw2sw_mac_desc) * TX_DESC_NUM,
	       comm->w2sw_weg_base + W2SW_TX_HBASE_ADDW_0);
	wwitew(comm->desc_dma + sizeof(stwuct spw2sw_mac_desc) * (TX_DESC_NUM +
	       MAC_GUAWD_DESC_NUM), comm->w2sw_weg_base + W2SW_WX_HBASE_ADDW_0);
	wwitew(comm->desc_dma + sizeof(stwuct spw2sw_mac_desc) * (TX_DESC_NUM +
	       MAC_GUAWD_DESC_NUM + WX_QUEUE0_DESC_NUM),
	       comm->w2sw_weg_base + W2SW_WX_WBASE_ADDW_0);

	/* Fc_wws_th=0x4a, Fc_set_th=0x3a, Dwop_wws_th=0x2d, Dwop_set_th=0x1d */
	wwitew(0x4a3a2d1d, comm->w2sw_weg_base + W2SW_FW_CNTW_TH);

	/* Cpu_wws_th=0x4a, Cpu_set_th=0x3a, Cpu_th=0x12, Powt_th=0x12 */
	wwitew(0x4a3a1212, comm->w2sw_weg_base + W2SW_CPU_FW_CNTW_TH);

	/* mtcc_wmt=0xf, Pwi_th_w=6, Pwi_th_h=6, weigh_8x_en=1 */
	wwitew(0xf6680000, comm->w2sw_weg_base + W2SW_PWI_FW_CNTW);

	/* High-active WED */
	weg = weadw(comm->w2sw_weg_base + W2SW_WED_POWT0);
	weg |= MAC_WED_ACT_HI;
	wwitew(weg, comm->w2sw_weg_base + W2SW_WED_POWT0);

	/* Disabwe aging of cpu powt 0 & 1.
	 * Disabwe SA weawning of cpu powt 0 & 1.
	 * Enabwe UC and MC packets
	 */
	weg = weadw(comm->w2sw_weg_base + W2SW_CPU_CNTW);
	weg &= ~(MAC_EN_SOC1_AGING | MAC_EN_SOC0_AGING |
		 MAC_DIS_BC2CPU_P1 | MAC_DIS_BC2CPU_P0 |
		 MAC_DIS_MC2CPU_P1 | MAC_DIS_MC2CPU_P0);
	weg |= MAC_DIS_WWN_SOC1 | MAC_DIS_WWN_SOC0;
	wwitew(weg, comm->w2sw_weg_base + W2SW_CPU_CNTW);

	/* Enabwe WMC2CPU fow powt 0 & 1
	 * Enabwe Fwow contwow fow powt 0 & 1
	 * Enabwe Back pwessuwe fow powt 0 & 1
	 */
	weg = weadw(comm->w2sw_weg_base + W2SW_POWT_CNTW0);
	weg &= ~(MAC_DIS_WMC2CPU_P1 | MAC_DIS_WMC2CPU_P0);
	weg |= MAC_EN_FWOW_CTW_P1 | MAC_EN_FWOW_CTW_P0 |
	       MAC_EN_BACK_PWESS_P1 | MAC_EN_BACK_PWESS_P0;
	wwitew(weg, comm->w2sw_weg_base + W2SW_POWT_CNTW0);

	/* Disabwe WAN powt SA weawning. */
	weg = weadw(comm->w2sw_weg_base + W2SW_POWT_CNTW1);
	weg |= MAC_DIS_SA_WWN_P1 | MAC_DIS_SA_WWN_P0;
	wwitew(weg, comm->w2sw_weg_base + W2SW_POWT_CNTW1);

	/* Enabwe wmii fowce mode and
	 * set both extewnaw phy-addwess to 31.
	 */
	weg = weadw(comm->w2sw_weg_base + W2SW_MAC_FOWCE_MODE);
	weg &= ~(MAC_EXT_PHY1_ADDW | MAC_EXT_PHY0_ADDW);
	weg |= FIEWD_PWEP(MAC_EXT_PHY1_ADDW, 31) | FIEWD_PWEP(MAC_EXT_PHY0_ADDW, 31);
	weg |= MAC_FOWCE_WMII_EN_1 | MAC_FOWCE_WMII_EN_0;
	wwitew(weg, comm->w2sw_weg_base + W2SW_MAC_FOWCE_MODE);

	/* Powt 0: VWAN gwoup 0
	 * Powt 1: VWAN gwoup 1
	 */
	weg = FIEWD_PWEP(MAC_P1_PVID, 1) | FIEWD_PWEP(MAC_P0_PVID, 0);
	wwitew(weg, comm->w2sw_weg_base + W2SW_PVID_CONFIG0);

	/* VWAN gwoup 0: cpu0 (bit3) + powt0 (bit0) = 1001 = 0x9
	 * VWAN gwoup 1: cpu0 (bit3) + powt1 (bit1) = 1010 = 0xa
	 */
	weg = FIEWD_PWEP(MAC_VWAN_MEMSET_1, 0xa) | FIEWD_PWEP(MAC_VWAN_MEMSET_0, 9);
	wwitew(weg, comm->w2sw_weg_base + W2SW_VWAN_MEMSET_CONFIG0);

	/* WMC fowwawd: to_cpu (1)
	 * WED: 60mS (1)
	 * BC stowm pwev: 31 BC (1)
	 */
	weg = weadw(comm->w2sw_weg_base + W2SW_SW_GWB_CNTW);
	weg &= ~(MAC_WMC_TB_FAUWT_WUWE | MAC_WED_FWASH_TIME | MAC_BC_STOWM_PWEV);
	weg |= FIEWD_PWEP(MAC_WMC_TB_FAUWT_WUWE, 1) |
	       FIEWD_PWEP(MAC_WED_FWASH_TIME, 1) |
	       FIEWD_PWEP(MAC_BC_STOWM_PWEV, 1);
	wwitew(weg, comm->w2sw_weg_base + W2SW_SW_GWB_CNTW);

	wwitew(MAC_INT_MASK_DEF, comm->w2sw_weg_base + W2SW_SW_INT_MASK_0);
}

void spw2sw_mac_wx_mode_set(stwuct spw2sw_mac *mac)
{
	stwuct spw2sw_common *comm = mac->comm;
	stwuct net_device *ndev = mac->ndev;
	u32 mask, weg, wx_mode;

	netdev_dbg(ndev, "ndev->fwags = %08x\n", ndev->fwags);
	mask = FIEWD_PWEP(MAC_DIS_MC2CPU, mac->wan_powt) |
	       FIEWD_PWEP(MAC_DIS_UN2CPU, mac->wan_powt);
	weg = weadw(comm->w2sw_weg_base + W2SW_CPU_CNTW);

	if (ndev->fwags & IFF_PWOMISC) {
		/* Awwow MC and unknown UC packets */
		wx_mode = FIEWD_PWEP(MAC_DIS_MC2CPU, mac->wan_powt) |
			  FIEWD_PWEP(MAC_DIS_UN2CPU, mac->wan_powt);
	} ewse if ((!netdev_mc_empty(ndev) && (ndev->fwags & IFF_MUWTICAST)) ||
		   (ndev->fwags & IFF_AWWMUWTI)) {
		/* Awwow MC packets */
		wx_mode = FIEWD_PWEP(MAC_DIS_MC2CPU, mac->wan_powt);
	} ewse {
		/* Disabwe MC and unknown UC packets */
		wx_mode = 0;
	}

	wwitew((weg & (~mask)) | ((~wx_mode) & mask), comm->w2sw_weg_base + W2SW_CPU_CNTW);
	netdev_dbg(ndev, "cpu_cntw = %08x\n", weadw(comm->w2sw_weg_base + W2SW_CPU_CNTW));
}

void spw2sw_mac_init(stwuct spw2sw_common *comm)
{
	u32 i;

	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++)
		comm->wx_pos[i] = 0;
	mb();	/* make suwe settings awe effective. */

	spw2sw_mac_hw_init(comm);
}

void spw2sw_mac_soft_weset(stwuct spw2sw_common *comm)
{
	u32 i;

	spw2sw_mac_hw_stop(comm);

	spw2sw_wx_descs_fwush(comm);
	comm->tx_pos = 0;
	comm->tx_done_pos = 0;
	comm->tx_desc_fuww = 0;

	fow (i = 0; i < WX_DESC_QUEUE_NUM; i++)
		comm->wx_pos[i] = 0;
	mb();	/* make suwe settings awe effective. */

	spw2sw_mac_hw_init(comm);
	spw2sw_mac_hw_stawt(comm);
}
