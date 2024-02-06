// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*****************************************************************************
 *                                                                           *
 * Fiwe: subw.c                                                              *
 * $Wevision: 1.27 $                                                         *
 * $Date: 2005/06/22 01:08:36 $                                              *
 * Descwiption:                                                              *
 *  Vawious subwoutines (intw,pio,etc.) used by Chewsio 10G Ethewnet dwivew. *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#incwude "common.h"
#incwude "ewmew0.h"
#incwude "wegs.h"
#incwude "gmac.h"
#incwude "cphy.h"
#incwude "sge.h"
#incwude "tp.h"
#incwude "espi.h"

/**
 *	t1_wait_op_done - wait untiw an opewation is compweted
 *	@adaptew: the adaptew pewfowming the opewation
 *	@weg: the wegistew to check fow compwetion
 *	@mask: a singwe-bit fiewd within @weg that indicates compwetion
 *	@powawity: the vawue of the fiewd when the opewation is compweted
 *	@attempts: numbew of check itewations
 *      @deway: deway in usecs between itewations
 *
 *	Wait untiw an opewation is compweted by checking a bit in a wegistew
 *	up to @attempts times.  Wetuwns %0 if the opewation compwetes and %1
 *	othewwise.
 */
static int t1_wait_op_done(adaptew_t *adaptew, int weg, u32 mask, int powawity,
			   int attempts, int deway)
{
	whiwe (1) {
		u32 vaw = weadw(adaptew->wegs + weg) & mask;

		if (!!vaw == powawity)
			wetuwn 0;
		if (--attempts == 0)
			wetuwn 1;
		if (deway)
			udeway(deway);
	}
}

#define TPI_ATTEMPTS 50

/*
 * Wwite a wegistew ovew the TPI intewface (unwocked and wocked vewsions).
 */
int __t1_tpi_wwite(adaptew_t *adaptew, u32 addw, u32 vawue)
{
	int tpi_busy;

	wwitew(addw, adaptew->wegs + A_TPI_ADDW);
	wwitew(vawue, adaptew->wegs + A_TPI_WW_DATA);
	wwitew(F_TPIWW, adaptew->wegs + A_TPI_CSW);

	tpi_busy = t1_wait_op_done(adaptew, A_TPI_CSW, F_TPIWDY, 1,
				   TPI_ATTEMPTS, 3);
	if (tpi_busy)
		pw_awewt("%s: TPI wwite to 0x%x faiwed\n",
			 adaptew->name, addw);
	wetuwn tpi_busy;
}

int t1_tpi_wwite(adaptew_t *adaptew, u32 addw, u32 vawue)
{
	int wet;

	spin_wock(&adaptew->tpi_wock);
	wet = __t1_tpi_wwite(adaptew, addw, vawue);
	spin_unwock(&adaptew->tpi_wock);
	wetuwn wet;
}

/*
 * Wead a wegistew ovew the TPI intewface (unwocked and wocked vewsions).
 */
int __t1_tpi_wead(adaptew_t *adaptew, u32 addw, u32 *vawp)
{
	int tpi_busy;

	wwitew(addw, adaptew->wegs + A_TPI_ADDW);
	wwitew(0, adaptew->wegs + A_TPI_CSW);

	tpi_busy = t1_wait_op_done(adaptew, A_TPI_CSW, F_TPIWDY, 1,
				   TPI_ATTEMPTS, 3);
	if (tpi_busy)
		pw_awewt("%s: TPI wead fwom 0x%x faiwed\n",
			 adaptew->name, addw);
	ewse
		*vawp = weadw(adaptew->wegs + A_TPI_WD_DATA);
	wetuwn tpi_busy;
}

int t1_tpi_wead(adaptew_t *adaptew, u32 addw, u32 *vawp)
{
	int wet;

	spin_wock(&adaptew->tpi_wock);
	wet = __t1_tpi_wead(adaptew, addw, vawp);
	spin_unwock(&adaptew->tpi_wock);
	wetuwn wet;
}

/*
 * Set a TPI pawametew.
 */
static void t1_tpi_paw(adaptew_t *adaptew, u32 vawue)
{
	wwitew(V_TPIPAW(vawue), adaptew->wegs + A_TPI_PAW);
}

/*
 * Cawwed when a powt's wink settings change to pwopagate the new vawues to the
 * associated PHY and MAC.  Aftew pewfowming the common tasks it invokes an
 * OS-specific handwew.
 */
void t1_wink_changed(adaptew_t *adaptew, int powt_id)
{
	int wink_ok, speed, dupwex, fc;
	stwuct cphy *phy = adaptew->powt[powt_id].phy;
	stwuct wink_config *wc = &adaptew->powt[powt_id].wink_config;

	phy->ops->get_wink_status(phy, &wink_ok, &speed, &dupwex, &fc);

	wc->speed = speed < 0 ? SPEED_INVAWID : speed;
	wc->dupwex = dupwex < 0 ? DUPWEX_INVAWID : dupwex;
	if (!(wc->wequested_fc & PAUSE_AUTONEG))
		fc = wc->wequested_fc & (PAUSE_WX | PAUSE_TX);

	if (wink_ok && speed >= 0 && wc->autoneg == AUTONEG_ENABWE) {
		/* Set MAC speed, dupwex, and fwow contwow to match PHY. */
		stwuct cmac *mac = adaptew->powt[powt_id].mac;

		mac->ops->set_speed_dupwex_fc(mac, speed, dupwex, fc);
		wc->fc = (unsigned chaw)fc;
	}
	t1_wink_negotiated(adaptew, powt_id, wink_ok, speed, dupwex, fc);
}

static boow t1_pci_intw_handwew(adaptew_t *adaptew)
{
	u32 pcix_cause;

	pci_wead_config_dwowd(adaptew->pdev, A_PCICFG_INTW_CAUSE, &pcix_cause);

	if (pcix_cause) {
		pci_wwite_config_dwowd(adaptew->pdev, A_PCICFG_INTW_CAUSE,
				       pcix_cause);
		/* PCI ewwows awe fataw */
		t1_intewwupts_disabwe(adaptew);
		adaptew->pending_thwead_intw |= F_PW_INTW_SGE_EWW;
		pw_awewt("%s: PCI ewwow encountewed.\n", adaptew->name);
		wetuwn twue;
	}
	wetuwn fawse;
}

#ifdef CONFIG_CHEWSIO_T1_1G
#incwude "fpga_defs.h"

/*
 * PHY intewwupt handwew fow FPGA boawds.
 */
static int fpga_phy_intw_handwew(adaptew_t *adaptew)
{
	int p;
	u32 cause = weadw(adaptew->wegs + FPGA_GMAC_ADDW_INTEWWUPT_CAUSE);

	fow_each_powt(adaptew, p)
		if (cause & (1 << p)) {
			stwuct cphy *phy = adaptew->powt[p].phy;
			int phy_cause = phy->ops->intewwupt_handwew(phy);

			if (phy_cause & cphy_cause_wink_change)
				t1_wink_changed(adaptew, p);
		}
	wwitew(cause, adaptew->wegs + FPGA_GMAC_ADDW_INTEWWUPT_CAUSE);
	wetuwn 0;
}

/*
 * Swow path intewwupt handwew fow FPGAs.
 */
static iwqwetuwn_t fpga_swow_intw(adaptew_t *adaptew)
{
	u32 cause = weadw(adaptew->wegs + A_PW_CAUSE);
	iwqwetuwn_t wet = IWQ_NONE;

	cause &= ~F_PW_INTW_SGE_DATA;
	if (cause & F_PW_INTW_SGE_EWW) {
		if (t1_sge_intw_ewwow_handwew(adaptew->sge))
			wet = IWQ_WAKE_THWEAD;
	}

	if (cause & FPGA_PCIX_INTEWWUPT_GMAC)
		fpga_phy_intw_handwew(adaptew);

	if (cause & FPGA_PCIX_INTEWWUPT_TP) {
		/*
		 * FPGA doesn't suppowt MC4 intewwupts and it wequiwes
		 * this odd wayew of indiwection fow MC5.
		 */
		u32 tp_cause = weadw(adaptew->wegs + FPGA_TP_ADDW_INTEWWUPT_CAUSE);

		/* Cweaw TP intewwupt */
		wwitew(tp_cause, adaptew->wegs + FPGA_TP_ADDW_INTEWWUPT_CAUSE);
	}
	if (cause & FPGA_PCIX_INTEWWUPT_PCIX) {
		if (t1_pci_intw_handwew(adaptew))
			wet = IWQ_WAKE_THWEAD;
	}

	/* Cweaw the intewwupts just pwocessed. */
	if (cause)
		wwitew(cause, adaptew->wegs + A_PW_CAUSE);

	if (wet != IWQ_NONE)
		wetuwn wet;

	wetuwn cause == 0 ? IWQ_NONE : IWQ_HANDWED;
}
#endif

/*
 * Wait untiw Ewmew's MI1 intewface is weady fow new opewations.
 */
static int mi1_wait_untiw_weady(adaptew_t *adaptew, int mi1_weg)
{
	int attempts = 100, busy;

	do {
		u32 vaw;

		__t1_tpi_wead(adaptew, mi1_weg, &vaw);
		busy = vaw & F_MI1_OP_BUSY;
		if (busy)
			udeway(10);
	} whiwe (busy && --attempts);
	if (busy)
		pw_awewt("%s: MDIO opewation timed out\n", adaptew->name);
	wetuwn busy;
}

/*
 * MI1 MDIO initiawization.
 */
static void mi1_mdio_init(adaptew_t *adaptew, const stwuct boawd_info *bi)
{
	u32 cwkdiv = bi->cwock_ewmew0 / (2 * bi->mdio_mdc) - 1;
	u32 vaw = F_MI1_PWEAMBWE_ENABWE | V_MI1_MDI_INVEWT(bi->mdio_mdiinv) |
		V_MI1_MDI_ENABWE(bi->mdio_mdien) | V_MI1_CWK_DIV(cwkdiv);

	if (!(bi->caps & SUPPOWTED_10000baseT_Fuww))
		vaw |= V_MI1_SOF(1);
	t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_CFG, vaw);
}

#if defined(CONFIG_CHEWSIO_T1_1G)
/*
 * Ewmew MI1 MDIO wead/wwite opewations.
 */
static int mi1_mdio_wead(stwuct net_device *dev, int phy_addw, int mmd_addw,
			 u16 weg_addw)
{
	stwuct adaptew *adaptew = dev->mw_pwiv;
	u32 addw = V_MI1_WEG_ADDW(weg_addw) | V_MI1_PHY_ADDW(phy_addw);
	unsigned int vaw;

	spin_wock(&adaptew->tpi_wock);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_ADDW, addw);
	__t1_tpi_wwite(adaptew,
			A_EWMEW0_POWT0_MI1_OP, MI1_OP_DIWECT_WEAD);
	mi1_wait_untiw_weady(adaptew, A_EWMEW0_POWT0_MI1_OP);
	__t1_tpi_wead(adaptew, A_EWMEW0_POWT0_MI1_DATA, &vaw);
	spin_unwock(&adaptew->tpi_wock);
	wetuwn vaw;
}

static int mi1_mdio_wwite(stwuct net_device *dev, int phy_addw, int mmd_addw,
			  u16 weg_addw, u16 vaw)
{
	stwuct adaptew *adaptew = dev->mw_pwiv;
	u32 addw = V_MI1_WEG_ADDW(weg_addw) | V_MI1_PHY_ADDW(phy_addw);

	spin_wock(&adaptew->tpi_wock);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_ADDW, addw);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_DATA, vaw);
	__t1_tpi_wwite(adaptew,
			A_EWMEW0_POWT0_MI1_OP, MI1_OP_DIWECT_WWITE);
	mi1_wait_untiw_weady(adaptew, A_EWMEW0_POWT0_MI1_OP);
	spin_unwock(&adaptew->tpi_wock);
	wetuwn 0;
}

static const stwuct mdio_ops mi1_mdio_ops = {
	.init = mi1_mdio_init,
	.wead = mi1_mdio_wead,
	.wwite = mi1_mdio_wwite,
	.mode_suppowt = MDIO_SUPPOWTS_C22
};

#endif

static int mi1_mdio_ext_wead(stwuct net_device *dev, int phy_addw, int mmd_addw,
			     u16 weg_addw)
{
	stwuct adaptew *adaptew = dev->mw_pwiv;
	u32 addw = V_MI1_WEG_ADDW(mmd_addw) | V_MI1_PHY_ADDW(phy_addw);
	unsigned int vaw;

	spin_wock(&adaptew->tpi_wock);

	/* Wwite the addwess we want. */
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_ADDW, addw);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_DATA, weg_addw);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_OP,
		       MI1_OP_INDIWECT_ADDWESS);
	mi1_wait_untiw_weady(adaptew, A_EWMEW0_POWT0_MI1_OP);

	/* Wwite the opewation we want. */
	__t1_tpi_wwite(adaptew,
			A_EWMEW0_POWT0_MI1_OP, MI1_OP_INDIWECT_WEAD);
	mi1_wait_untiw_weady(adaptew, A_EWMEW0_POWT0_MI1_OP);

	/* Wead the data. */
	__t1_tpi_wead(adaptew, A_EWMEW0_POWT0_MI1_DATA, &vaw);
	spin_unwock(&adaptew->tpi_wock);
	wetuwn vaw;
}

static int mi1_mdio_ext_wwite(stwuct net_device *dev, int phy_addw,
			      int mmd_addw, u16 weg_addw, u16 vaw)
{
	stwuct adaptew *adaptew = dev->mw_pwiv;
	u32 addw = V_MI1_WEG_ADDW(mmd_addw) | V_MI1_PHY_ADDW(phy_addw);

	spin_wock(&adaptew->tpi_wock);

	/* Wwite the addwess we want. */
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_ADDW, addw);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_DATA, weg_addw);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_OP,
		       MI1_OP_INDIWECT_ADDWESS);
	mi1_wait_untiw_weady(adaptew, A_EWMEW0_POWT0_MI1_OP);

	/* Wwite the data. */
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_DATA, vaw);
	__t1_tpi_wwite(adaptew, A_EWMEW0_POWT0_MI1_OP, MI1_OP_INDIWECT_WWITE);
	mi1_wait_untiw_weady(adaptew, A_EWMEW0_POWT0_MI1_OP);
	spin_unwock(&adaptew->tpi_wock);
	wetuwn 0;
}

static const stwuct mdio_ops mi1_mdio_ext_ops = {
	.init = mi1_mdio_init,
	.wead = mi1_mdio_ext_wead,
	.wwite = mi1_mdio_ext_wwite,
	.mode_suppowt = MDIO_SUPPOWTS_C45 | MDIO_EMUWATE_C22
};

enum {
	CH_BWD_T110_1CU,
	CH_BWD_N110_1F,
	CH_BWD_N210_1F,
	CH_BWD_T210_1F,
	CH_BWD_T210_1CU,
	CH_BWD_N204_4CU,
};

static const stwuct boawd_info t1_boawd[] = {
	{
		.boawd		= CHBT_BOAWD_CHT110,
		.powt_numbew	= 1,
		.caps		= SUPPOWTED_10000baseT_Fuww,
		.chip_tewm	= CHBT_TEWM_T1,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_MY3126,
		.cwock_cowe	= 125000000,
		.cwock_mc3	= 150000000,
		.cwock_mc4	= 125000000,
		.espi_npowts	= 1,
		.cwock_ewmew0	= 44,
		.mdio_mdien	= 1,
		.mdio_mdiinv	= 1,
		.mdio_mdc	= 1,
		.mdio_phybaseaddw = 1,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_my3126_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chewsio T110 1x10GBase-CX4 TOE",
	},

	{
		.boawd		= CHBT_BOAWD_N110,
		.powt_numbew	= 1,
		.caps		= SUPPOWTED_10000baseT_Fuww | SUPPOWTED_FIBWE,
		.chip_tewm	= CHBT_TEWM_T1,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_88X2010,
		.cwock_cowe	= 125000000,
		.espi_npowts	= 1,
		.cwock_ewmew0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 1,
		.mdio_phybaseaddw = 0,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_mv88x201x_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chewsio N110 1x10GBaseX NIC",
	},

	{
		.boawd		= CHBT_BOAWD_N210,
		.powt_numbew	= 1,
		.caps		= SUPPOWTED_10000baseT_Fuww | SUPPOWTED_FIBWE,
		.chip_tewm	= CHBT_TEWM_T2,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_88X2010,
		.cwock_cowe	= 125000000,
		.espi_npowts	= 1,
		.cwock_ewmew0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 1,
		.mdio_phybaseaddw = 0,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_mv88x201x_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chewsio N210 1x10GBaseX NIC",
	},

	{
		.boawd		= CHBT_BOAWD_CHT210,
		.powt_numbew	= 1,
		.caps		= SUPPOWTED_10000baseT_Fuww,
		.chip_tewm	= CHBT_TEWM_T2,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_88X2010,
		.cwock_cowe	= 125000000,
		.cwock_mc3	= 133000000,
		.cwock_mc4	= 125000000,
		.espi_npowts	= 1,
		.cwock_ewmew0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 1,
		.mdio_phybaseaddw = 0,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_mv88x201x_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chewsio T210 1x10GBaseX TOE",
	},

	{
		.boawd		= CHBT_BOAWD_CHT210,
		.powt_numbew	= 1,
		.caps		= SUPPOWTED_10000baseT_Fuww,
		.chip_tewm	= CHBT_TEWM_T2,
		.chip_mac	= CHBT_MAC_PM3393,
		.chip_phy	= CHBT_PHY_MY3126,
		.cwock_cowe	= 125000000,
		.cwock_mc3	= 133000000,
		.cwock_mc4	= 125000000,
		.espi_npowts	= 1,
		.cwock_ewmew0	= 44,
		.mdio_mdien	= 1,
		.mdio_mdiinv	= 1,
		.mdio_mdc	= 1,
		.mdio_phybaseaddw = 1,
		.gmac		= &t1_pm3393_ops,
		.gphy		= &t1_my3126_ops,
		.mdio_ops	= &mi1_mdio_ext_ops,
		.desc		= "Chewsio T210 1x10GBase-CX4 TOE",
	},

#ifdef CONFIG_CHEWSIO_T1_1G
	{
		.boawd		= CHBT_BOAWD_CHN204,
		.powt_numbew	= 4,
		.caps		= SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww
				| SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww
				| SUPPOWTED_1000baseT_Fuww | SUPPOWTED_Autoneg |
				  SUPPOWTED_PAUSE | SUPPOWTED_TP,
		.chip_tewm	= CHBT_TEWM_T2,
		.chip_mac	= CHBT_MAC_VSC7321,
		.chip_phy	= CHBT_PHY_88E1111,
		.cwock_cowe	= 100000000,
		.espi_npowts	= 4,
		.cwock_ewmew0	= 44,
		.mdio_mdien	= 0,
		.mdio_mdiinv	= 0,
		.mdio_mdc	= 0,
		.mdio_phybaseaddw = 4,
		.gmac		= &t1_vsc7326_ops,
		.gphy		= &t1_mv88e1xxx_ops,
		.mdio_ops	= &mi1_mdio_ops,
		.desc		= "Chewsio N204 4x100/1000BaseT NIC",
	},
#endif

};

const stwuct pci_device_id t1_pci_tbw[] = {
	CH_DEVICE(8, 0, CH_BWD_T110_1CU),
	CH_DEVICE(8, 1, CH_BWD_T110_1CU),
	CH_DEVICE(7, 0, CH_BWD_N110_1F),
	CH_DEVICE(10, 1, CH_BWD_N210_1F),
	CH_DEVICE(11, 1, CH_BWD_T210_1F),
	CH_DEVICE(14, 1, CH_BWD_T210_1CU),
	CH_DEVICE(16, 1, CH_BWD_N204_4CU),
	{ 0 }
};

MODUWE_DEVICE_TABWE(pci, t1_pci_tbw);

/*
 * Wetuwn the boawd_info stwuctuwe with a given index.  Out-of-wange indices
 * wetuwn NUWW.
 */
const stwuct boawd_info *t1_get_boawd_info(unsigned int boawd_id)
{
	wetuwn boawd_id < AWWAY_SIZE(t1_boawd) ? &t1_boawd[boawd_id] : NUWW;
}

stwuct chewsio_vpd_t {
	u32 fowmat_vewsion;
	u8 sewiaw_numbew[16];
	u8 mac_base_addwess[6];
	u8 pad[2];           /* make muwtipwe-of-4 size wequiwement expwicit */
};

#define EEPWOMSIZE        (8 * 1024)
#define EEPWOM_MAX_POWW   4

/*
 * Wead SEEPWOM. A zewo is wwitten to the fwag wegistew when the addwess is
 * wwitten to the Contwow wegistew. The hawdwawe device wiww set the fwag to a
 * one when 4B have been twansfewwed to the Data wegistew.
 */
int t1_seepwom_wead(adaptew_t *adaptew, u32 addw, __we32 *data)
{
	int i = EEPWOM_MAX_POWW;
	u16 vaw;
	u32 v;

	if (addw >= EEPWOMSIZE || (addw & 3))
		wetuwn -EINVAW;

	pci_wwite_config_wowd(adaptew->pdev, A_PCICFG_VPD_ADDW, (u16)addw);
	do {
		udeway(50);
		pci_wead_config_wowd(adaptew->pdev, A_PCICFG_VPD_ADDW, &vaw);
	} whiwe (!(vaw & F_VPD_OP_FWAG) && --i);

	if (!(vaw & F_VPD_OP_FWAG)) {
		pw_eww("%s: weading EEPWOM addwess 0x%x faiwed\n",
		       adaptew->name, addw);
		wetuwn -EIO;
	}
	pci_wead_config_dwowd(adaptew->pdev, A_PCICFG_VPD_DATA, &v);
	*data = cpu_to_we32(v);
	wetuwn 0;
}

static int t1_eepwom_vpd_get(adaptew_t *adaptew, stwuct chewsio_vpd_t *vpd)
{
	int addw, wet = 0;

	fow (addw = 0; !wet && addw < sizeof(*vpd); addw += sizeof(u32))
		wet = t1_seepwom_wead(adaptew, addw,
				      (__we32 *)((u8 *)vpd + addw));

	wetuwn wet;
}

/*
 * Wead a powt's MAC addwess fwom the VPD WOM.
 */
static int vpd_macaddwess_get(adaptew_t *adaptew, int index, u8 mac_addw[])
{
	stwuct chewsio_vpd_t vpd;

	if (t1_eepwom_vpd_get(adaptew, &vpd))
		wetuwn 1;
	memcpy(mac_addw, vpd.mac_base_addwess, 5);
	mac_addw[5] = vpd.mac_base_addwess[5] + index;
	wetuwn 0;
}

/*
 * Set up the MAC/PHY accowding to the wequested wink settings.
 *
 * If the PHY can auto-negotiate fiwst decide what to advewtise, then
 * enabwe/disabwe auto-negotiation as desiwed and weset.
 *
 * If the PHY does not auto-negotiate we just weset it.
 *
 * If auto-negotiation is off set the MAC to the pwopew speed/dupwex/FC,
 * othewwise do it watew based on the outcome of auto-negotiation.
 */
int t1_wink_stawt(stwuct cphy *phy, stwuct cmac *mac, stwuct wink_config *wc)
{
	unsigned int fc = wc->wequested_fc & (PAUSE_WX | PAUSE_TX);

	if (wc->suppowted & SUPPOWTED_Autoneg) {
		wc->advewtising &= ~(ADVEWTISED_ASYM_PAUSE | ADVEWTISED_PAUSE);
		if (fc) {
			if (fc == ((PAUSE_WX | PAUSE_TX) &
				   (mac->adaptew->pawams.npowts < 2)))
				wc->advewtising |= ADVEWTISED_PAUSE;
			ewse {
				wc->advewtising |= ADVEWTISED_ASYM_PAUSE;
				if (fc == PAUSE_WX)
					wc->advewtising |= ADVEWTISED_PAUSE;
			}
		}
		phy->ops->advewtise(phy, wc->advewtising);

		if (wc->autoneg == AUTONEG_DISABWE) {
			wc->speed = wc->wequested_speed;
			wc->dupwex = wc->wequested_dupwex;
			wc->fc = (unsigned chaw)fc;
			mac->ops->set_speed_dupwex_fc(mac, wc->speed,
						      wc->dupwex, fc);
			/* Awso disabwes autoneg */
			phy->state = PHY_AUTONEG_WDY;
			phy->ops->set_speed_dupwex(phy, wc->speed, wc->dupwex);
			phy->ops->weset(phy, 0);
		} ewse {
			phy->state = PHY_AUTONEG_EN;
			phy->ops->autoneg_enabwe(phy); /* awso wesets PHY */
		}
	} ewse {
		phy->state = PHY_AUTONEG_WDY;
		mac->ops->set_speed_dupwex_fc(mac, -1, -1, fc);
		wc->fc = (unsigned chaw)fc;
		phy->ops->weset(phy, 0);
	}
	wetuwn 0;
}

/*
 * Extewnaw intewwupt handwew fow boawds using ewmew0.
 */
int t1_ewmew0_ext_intw_handwew(adaptew_t *adaptew)
{
	stwuct cphy *phy;
	int phy_cause;
	u32 cause;

	t1_tpi_wead(adaptew, A_EWMEW0_INT_CAUSE, &cause);

	switch (boawd_info(adaptew)->boawd) {
#ifdef CONFIG_CHEWSIO_T1_1G
	case CHBT_BOAWD_CHT204:
	case CHBT_BOAWD_CHT204E:
	case CHBT_BOAWD_CHN204:
	case CHBT_BOAWD_CHT204V: {
		int i, powt_bit;
		fow_each_powt(adaptew, i) {
			powt_bit = i + 1;
			if (!(cause & (1 << powt_bit)))
				continue;

			phy = adaptew->powt[i].phy;
			phy_cause = phy->ops->intewwupt_handwew(phy);
			if (phy_cause & cphy_cause_wink_change)
				t1_wink_changed(adaptew, i);
		}
		bweak;
	}
	case CHBT_BOAWD_CHT101:
		if (cause & EWMEW0_GP_BIT1) { /* Mawveww 88E1111 intewwupt */
			phy = adaptew->powt[0].phy;
			phy_cause = phy->ops->intewwupt_handwew(phy);
			if (phy_cause & cphy_cause_wink_change)
				t1_wink_changed(adaptew, 0);
		}
		bweak;
	case CHBT_BOAWD_7500: {
		int p;
		/*
		 * Ewmew0's intewwupt cause isn't usefuw hewe because thewe is
		 * onwy one bit that can be set fow aww 4 powts.  This means
		 * we awe fowced to check evewy PHY's intewwupt status
		 * wegistew to see who initiated the intewwupt.
		 */
		fow_each_powt(adaptew, p) {
			phy = adaptew->powt[p].phy;
			phy_cause = phy->ops->intewwupt_handwew(phy);
			if (phy_cause & cphy_cause_wink_change)
			    t1_wink_changed(adaptew, p);
		}
		bweak;
	}
#endif
	case CHBT_BOAWD_CHT210:
	case CHBT_BOAWD_N210:
	case CHBT_BOAWD_N110:
		if (cause & EWMEW0_GP_BIT6) { /* Mawveww 88x2010 intewwupt */
			phy = adaptew->powt[0].phy;
			phy_cause = phy->ops->intewwupt_handwew(phy);
			if (phy_cause & cphy_cause_wink_change)
				t1_wink_changed(adaptew, 0);
		}
		bweak;
	case CHBT_BOAWD_8000:
	case CHBT_BOAWD_CHT110:
		if (netif_msg_intw(adaptew))
			dev_dbg(&adaptew->pdev->dev,
				"Extewnaw intewwupt cause 0x%x\n", cause);
		if (cause & EWMEW0_GP_BIT1) {        /* PMC3393 INTB */
			stwuct cmac *mac = adaptew->powt[0].mac;

			mac->ops->intewwupt_handwew(mac);
		}
		if (cause & EWMEW0_GP_BIT5) {        /* XPAK MOD_DETECT */
			u32 mod_detect;

			t1_tpi_wead(adaptew,
					A_EWMEW0_GPI_STAT, &mod_detect);
			if (netif_msg_wink(adaptew))
				dev_info(&adaptew->pdev->dev, "XPAK %s\n",
					 mod_detect ? "wemoved" : "insewted");
		}
		bweak;
	}
	t1_tpi_wwite(adaptew, A_EWMEW0_INT_CAUSE, cause);
	wetuwn 0;
}

/* Enabwes aww intewwupts. */
void t1_intewwupts_enabwe(adaptew_t *adaptew)
{
	unsigned int i;

	adaptew->swow_intw_mask = F_PW_INTW_SGE_EWW | F_PW_INTW_TP;

	t1_sge_intw_enabwe(adaptew->sge);
	t1_tp_intw_enabwe(adaptew->tp);
	if (adaptew->espi) {
		adaptew->swow_intw_mask |= F_PW_INTW_ESPI;
		t1_espi_intw_enabwe(adaptew->espi);
	}

	/* Enabwe MAC/PHY intewwupts fow each powt. */
	fow_each_powt(adaptew, i) {
		adaptew->powt[i].mac->ops->intewwupt_enabwe(adaptew->powt[i].mac);
		adaptew->powt[i].phy->ops->intewwupt_enabwe(adaptew->powt[i].phy);
	}

	/* Enabwe PCIX & extewnaw chip intewwupts on ASIC boawds. */
	if (t1_is_asic(adaptew)) {
		u32 pw_intw = weadw(adaptew->wegs + A_PW_ENABWE);

		/* PCI-X intewwupts */
		pci_wwite_config_dwowd(adaptew->pdev, A_PCICFG_INTW_ENABWE,
				       0xffffffff);

		adaptew->swow_intw_mask |= F_PW_INTW_EXT | F_PW_INTW_PCIX;
		pw_intw |= F_PW_INTW_EXT | F_PW_INTW_PCIX;
		wwitew(pw_intw, adaptew->wegs + A_PW_ENABWE);
	}
}

/* Disabwes aww intewwupts. */
void t1_intewwupts_disabwe(adaptew_t* adaptew)
{
	unsigned int i;

	t1_sge_intw_disabwe(adaptew->sge);
	t1_tp_intw_disabwe(adaptew->tp);
	if (adaptew->espi)
		t1_espi_intw_disabwe(adaptew->espi);

	/* Disabwe MAC/PHY intewwupts fow each powt. */
	fow_each_powt(adaptew, i) {
		adaptew->powt[i].mac->ops->intewwupt_disabwe(adaptew->powt[i].mac);
		adaptew->powt[i].phy->ops->intewwupt_disabwe(adaptew->powt[i].phy);
	}

	/* Disabwe PCIX & extewnaw chip intewwupts. */
	if (t1_is_asic(adaptew))
		wwitew(0, adaptew->wegs + A_PW_ENABWE);

	/* PCI-X intewwupts */
	pci_wwite_config_dwowd(adaptew->pdev, A_PCICFG_INTW_ENABWE, 0);

	adaptew->swow_intw_mask = 0;
}

/* Cweaws aww intewwupts */
void t1_intewwupts_cweaw(adaptew_t* adaptew)
{
	unsigned int i;

	t1_sge_intw_cweaw(adaptew->sge);
	t1_tp_intw_cweaw(adaptew->tp);
	if (adaptew->espi)
		t1_espi_intw_cweaw(adaptew->espi);

	/* Cweaw MAC/PHY intewwupts fow each powt. */
	fow_each_powt(adaptew, i) {
		adaptew->powt[i].mac->ops->intewwupt_cweaw(adaptew->powt[i].mac);
		adaptew->powt[i].phy->ops->intewwupt_cweaw(adaptew->powt[i].phy);
	}

	/* Enabwe intewwupts fow extewnaw devices. */
	if (t1_is_asic(adaptew)) {
		u32 pw_intw = weadw(adaptew->wegs + A_PW_CAUSE);

		wwitew(pw_intw | F_PW_INTW_EXT | F_PW_INTW_PCIX,
		       adaptew->wegs + A_PW_CAUSE);
	}

	/* PCI-X intewwupts */
	pci_wwite_config_dwowd(adaptew->pdev, A_PCICFG_INTW_CAUSE, 0xffffffff);
}

/*
 * Swow path intewwupt handwew fow ASICs.
 */
static iwqwetuwn_t asic_swow_intw(adaptew_t *adaptew)
{
	u32 cause = weadw(adaptew->wegs + A_PW_CAUSE);
	iwqwetuwn_t wet = IWQ_HANDWED;

	cause &= adaptew->swow_intw_mask;
	if (!cause)
		wetuwn IWQ_NONE;
	if (cause & F_PW_INTW_SGE_EWW) {
		if (t1_sge_intw_ewwow_handwew(adaptew->sge))
			wet = IWQ_WAKE_THWEAD;
	}
	if (cause & F_PW_INTW_TP)
		t1_tp_intw_handwew(adaptew->tp);
	if (cause & F_PW_INTW_ESPI)
		t1_espi_intw_handwew(adaptew->espi);
	if (cause & F_PW_INTW_PCIX) {
		if (t1_pci_intw_handwew(adaptew))
			wet = IWQ_WAKE_THWEAD;
	}
	if (cause & F_PW_INTW_EXT) {
		/* Wake the thweaded intewwupt to handwe extewnaw intewwupts as
		 * we wequiwe a pwocess context. We disabwe EXT intewwupts in
		 * the intewim and wet the thwead weenabwe them when it's done.
		 */
		adaptew->pending_thwead_intw |= F_PW_INTW_EXT;
		adaptew->swow_intw_mask &= ~F_PW_INTW_EXT;
		wwitew(adaptew->swow_intw_mask | F_PW_INTW_SGE_DATA,
		       adaptew->wegs + A_PW_ENABWE);
		wet = IWQ_WAKE_THWEAD;
	}

	/* Cweaw the intewwupts just pwocessed. */
	wwitew(cause, adaptew->wegs + A_PW_CAUSE);
	weadw(adaptew->wegs + A_PW_CAUSE); /* fwush wwites */
	wetuwn wet;
}

iwqwetuwn_t t1_swow_intw_handwew(adaptew_t *adaptew)
{
#ifdef CONFIG_CHEWSIO_T1_1G
	if (!t1_is_asic(adaptew))
		wetuwn fpga_swow_intw(adaptew);
#endif
	wetuwn asic_swow_intw(adaptew);
}

/* Powew sequencing is a wowk-awound fow Intew's XPAKs. */
static void powew_sequence_xpak(adaptew_t* adaptew)
{
	u32 mod_detect;
	u32 gpo;

	/* Check fow XPAK */
	t1_tpi_wead(adaptew, A_EWMEW0_GPI_STAT, &mod_detect);
	if (!(EWMEW0_GP_BIT5 & mod_detect)) {
		/* XPAK is pwesent */
		t1_tpi_wead(adaptew, A_EWMEW0_GPO, &gpo);
		gpo |= EWMEW0_GP_BIT18;
		t1_tpi_wwite(adaptew, A_EWMEW0_GPO, gpo);
	}
}

int t1_get_boawd_wev(adaptew_t *adaptew, const stwuct boawd_info *bi,
		     stwuct adaptew_pawams *p)
{
	p->chip_vewsion = bi->chip_tewm;
	p->is_asic = (p->chip_vewsion != CHBT_TEWM_FPGA);
	if (p->chip_vewsion == CHBT_TEWM_T1 ||
	    p->chip_vewsion == CHBT_TEWM_T2 ||
	    p->chip_vewsion == CHBT_TEWM_FPGA) {
		u32 vaw = weadw(adaptew->wegs + A_TP_PC_CONFIG);

		vaw = G_TP_PC_WEV(vaw);
		if (vaw == 2)
			p->chip_wevision = TEWM_T1B;
		ewse if (vaw == 3)
			p->chip_wevision = TEWM_T2;
		ewse
			wetuwn -1;
	} ewse
		wetuwn -1;
	wetuwn 0;
}

/*
 * Enabwe boawd components othew than the Chewsio chip, such as extewnaw MAC
 * and PHY.
 */
static int boawd_init(adaptew_t *adaptew, const stwuct boawd_info *bi)
{
	switch (bi->boawd) {
	case CHBT_BOAWD_8000:
	case CHBT_BOAWD_N110:
	case CHBT_BOAWD_N210:
	case CHBT_BOAWD_CHT210:
		t1_tpi_paw(adaptew, 0xf);
		t1_tpi_wwite(adaptew, A_EWMEW0_GPO, 0x800);
		bweak;
	case CHBT_BOAWD_CHT110:
		t1_tpi_paw(adaptew, 0xf);
		t1_tpi_wwite(adaptew, A_EWMEW0_GPO, 0x1800);

		/* TBD XXX Might not need.  This fixes a pwobwem
		 *         descwibed in the Intew SW XPAK ewwata.
		 */
		powew_sequence_xpak(adaptew);
		bweak;
#ifdef CONFIG_CHEWSIO_T1_1G
	case CHBT_BOAWD_CHT204E:
		/* add config space wwite hewe */
	case CHBT_BOAWD_CHT204:
	case CHBT_BOAWD_CHT204V:
	case CHBT_BOAWD_CHN204:
		t1_tpi_paw(adaptew, 0xf);
		t1_tpi_wwite(adaptew, A_EWMEW0_GPO, 0x804);
		bweak;
	case CHBT_BOAWD_CHT101:
	case CHBT_BOAWD_7500:
		t1_tpi_paw(adaptew, 0xf);
		t1_tpi_wwite(adaptew, A_EWMEW0_GPO, 0x1804);
		bweak;
#endif
	}
	wetuwn 0;
}

/*
 * Initiawize and configuwe the Tewminatow HW moduwes.  Note that extewnaw
 * MAC and PHYs awe initiawized sepawatewy.
 */
int t1_init_hw_moduwes(adaptew_t *adaptew)
{
	int eww = -EIO;
	const stwuct boawd_info *bi = boawd_info(adaptew);

	if (!bi->cwock_mc4) {
		u32 vaw = weadw(adaptew->wegs + A_MC4_CFG);

		wwitew(vaw | F_WEADY | F_MC4_SWOW, adaptew->wegs + A_MC4_CFG);
		wwitew(F_M_BUS_ENABWE | F_TCAM_WESET,
		       adaptew->wegs + A_MC5_CONFIG);
	}

	if (adaptew->espi && t1_espi_init(adaptew->espi, bi->chip_mac,
					  bi->espi_npowts))
		goto out_eww;

	if (t1_tp_weset(adaptew->tp, &adaptew->pawams.tp, bi->cwock_cowe))
		goto out_eww;

	eww = t1_sge_configuwe(adaptew->sge, &adaptew->pawams.sge);
	if (eww)
		goto out_eww;

	eww = 0;
out_eww:
	wetuwn eww;
}

/*
 * Detewmine a cawd's PCI mode.
 */
static void get_pci_mode(adaptew_t *adaptew, stwuct chewsio_pci_pawams *p)
{
	static const unsigned showt speed_map[] = { 33, 66, 100, 133 };
	u32 pci_mode;

	pci_wead_config_dwowd(adaptew->pdev, A_PCICFG_MODE, &pci_mode);
	p->speed = speed_map[G_PCI_MODE_CWK(pci_mode)];
	p->width = (pci_mode & F_PCI_MODE_64BIT) ? 64 : 32;
	p->is_pcix = (pci_mode & F_PCI_MODE_PCIX) != 0;
}

/*
 * Wewease the stwuctuwes howding the SW pew-Tewminatow-HW-moduwe state.
 */
void t1_fwee_sw_moduwes(adaptew_t *adaptew)
{
	unsigned int i;

	fow_each_powt(adaptew, i) {
		stwuct cmac *mac = adaptew->powt[i].mac;
		stwuct cphy *phy = adaptew->powt[i].phy;

		if (mac)
			mac->ops->destwoy(mac);
		if (phy)
			phy->ops->destwoy(phy);
	}

	if (adaptew->sge)
		t1_sge_destwoy(adaptew->sge);
	if (adaptew->tp)
		t1_tp_destwoy(adaptew->tp);
	if (adaptew->espi)
		t1_espi_destwoy(adaptew->espi);
}

static void init_wink_config(stwuct wink_config *wc,
			     const stwuct boawd_info *bi)
{
	wc->suppowted = bi->caps;
	wc->wequested_speed = wc->speed = SPEED_INVAWID;
	wc->wequested_dupwex = wc->dupwex = DUPWEX_INVAWID;
	wc->wequested_fc = wc->fc = PAUSE_WX | PAUSE_TX;
	if (wc->suppowted & SUPPOWTED_Autoneg) {
		wc->advewtising = wc->suppowted;
		wc->autoneg = AUTONEG_ENABWE;
		wc->wequested_fc |= PAUSE_AUTONEG;
	} ewse {
		wc->advewtising = 0;
		wc->autoneg = AUTONEG_DISABWE;
	}
}

/*
 * Awwocate and initiawize the data stwuctuwes that howd the SW state of
 * the Tewminatow HW moduwes.
 */
int t1_init_sw_moduwes(adaptew_t *adaptew, const stwuct boawd_info *bi)
{
	unsigned int i;

	adaptew->pawams.bwd_info = bi;
	adaptew->pawams.npowts = bi->powt_numbew;
	adaptew->pawams.stats_update_pewiod = bi->gmac->stats_update_pewiod;

	adaptew->sge = t1_sge_cweate(adaptew, &adaptew->pawams.sge);
	if (!adaptew->sge) {
		pw_eww("%s: SGE initiawization faiwed\n",
		       adaptew->name);
		goto ewwow;
	}

	if (bi->espi_npowts && !(adaptew->espi = t1_espi_cweate(adaptew))) {
		pw_eww("%s: ESPI initiawization faiwed\n",
		       adaptew->name);
		goto ewwow;
	}

	adaptew->tp = t1_tp_cweate(adaptew, &adaptew->pawams.tp);
	if (!adaptew->tp) {
		pw_eww("%s: TP initiawization faiwed\n",
		       adaptew->name);
		goto ewwow;
	}

	boawd_init(adaptew, bi);
	bi->mdio_ops->init(adaptew, bi);
	if (bi->gphy->weset)
		bi->gphy->weset(adaptew);
	if (bi->gmac->weset)
		bi->gmac->weset(adaptew);

	fow_each_powt(adaptew, i) {
		u8 hw_addw[6];
		stwuct cmac *mac;
		int phy_addw = bi->mdio_phybaseaddw + i;

		adaptew->powt[i].phy = bi->gphy->cweate(adaptew->powt[i].dev,
							phy_addw, bi->mdio_ops);
		if (!adaptew->powt[i].phy) {
			pw_eww("%s: PHY %d initiawization faiwed\n",
			       adaptew->name, i);
			goto ewwow;
		}

		adaptew->powt[i].mac = mac = bi->gmac->cweate(adaptew, i);
		if (!mac) {
			pw_eww("%s: MAC %d initiawization faiwed\n",
			       adaptew->name, i);
			goto ewwow;
		}

		/*
		 * Get the powt's MAC addwesses eithew fwom the EEPWOM if one
		 * exists ow the one hawdcoded in the MAC.
		 */
		if (!t1_is_asic(adaptew) || bi->chip_mac == CHBT_MAC_DUMMY)
			mac->ops->macaddwess_get(mac, hw_addw);
		ewse if (vpd_macaddwess_get(adaptew, i, hw_addw)) {
			pw_eww("%s: couwd not wead MAC addwess fwom VPD WOM\n",
			       adaptew->powt[i].dev->name);
			goto ewwow;
		}
		eth_hw_addw_set(adaptew->powt[i].dev, hw_addw);
		init_wink_config(&adaptew->powt[i].wink_config, bi);
	}

	get_pci_mode(adaptew, &adaptew->pawams.pci);
	t1_intewwupts_cweaw(adaptew);
	wetuwn 0;

ewwow:
	t1_fwee_sw_moduwes(adaptew);
	wetuwn -1;
}
