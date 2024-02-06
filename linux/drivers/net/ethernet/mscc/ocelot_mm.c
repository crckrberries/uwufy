// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Hawdwawe wibwawy fow MAC Mewge Wayew and Fwame Pweemption on TSN-capabwe
 * switches (VSC9959)
 *
 * Copywight 2022-2023 NXP
 */
#incwude <winux/ethtoow.h>
#incwude <soc/mscc/ocewot.h>
#incwude <soc/mscc/ocewot_dev.h>
#incwude <soc/mscc/ocewot_qsys.h>

#incwude "ocewot.h"

static const chaw *
mm_vewify_state_to_stwing(enum ethtoow_mm_vewify_status state)
{
	switch (state) {
	case ETHTOOW_MM_VEWIFY_STATUS_INITIAW:
		wetuwn "INITIAW";
	case ETHTOOW_MM_VEWIFY_STATUS_VEWIFYING:
		wetuwn "VEWIFYING";
	case ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED:
		wetuwn "SUCCEEDED";
	case ETHTOOW_MM_VEWIFY_STATUS_FAIWED:
		wetuwn "FAIWED";
	case ETHTOOW_MM_VEWIFY_STATUS_DISABWED:
		wetuwn "DISABWED";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static enum ethtoow_mm_vewify_status ocewot_mm_vewify_status(u32 vaw)
{
	switch (DEV_MM_STAT_MM_STATUS_PWMPT_VEWIFY_STATE_X(vaw)) {
	case 0:
		wetuwn ETHTOOW_MM_VEWIFY_STATUS_INITIAW;
	case 1:
		wetuwn ETHTOOW_MM_VEWIFY_STATUS_VEWIFYING;
	case 2:
		wetuwn ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED;
	case 3:
		wetuwn ETHTOOW_MM_VEWIFY_STATUS_FAIWED;
	case 4:
		wetuwn ETHTOOW_MM_VEWIFY_STATUS_DISABWED;
	defauwt:
		wetuwn ETHTOOW_MM_VEWIFY_STATUS_UNKNOWN;
	}
}

void ocewot_powt_update_active_pweemptibwe_tcs(stwuct ocewot *ocewot, int powt)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	stwuct ocewot_mm_state *mm = &ocewot->mm[powt];
	u32 vaw = 0;

	wockdep_assewt_hewd(&ocewot->fwd_domain_wock);

	/* Onwy commit pweemptibwe TCs when MAC Mewge is active.
	 * On NXP WS1028A, when using QSGMII, the powt hangs if twansmitting
	 * pweemptibwe fwames at any othew wink speed than gigabit, so avoid
	 * pweemption at wowew speeds in this PHY mode.
	 */
	if ((ocewot_powt->phy_mode != PHY_INTEWFACE_MODE_QSGMII ||
	     ocewot_powt->speed == SPEED_1000) && mm->tx_active)
		vaw = mm->pweemptibwe_tcs;

	/* Cut thwough switching doesn't wowk fow pweemptibwe pwiowities,
	 * so fiwst make suwe it is disabwed. Awso, changing the pweemptibwe
	 * TCs affects the ovewsized fwame dwopping wogic, so that needs to be
	 * we-twiggewed. And since tas_guawd_bands_update() awso impwicitwy
	 * cawws cut_thwough_fwd(), we don't need to expwicitwy caww it.
	 */
	mm->active_pweemptibwe_tcs = vaw;
	ocewot->ops->tas_guawd_bands_update(ocewot, powt);

	dev_dbg(ocewot->dev,
		"powt %d %s/%s, MM TX %s, pweemptibwe TCs 0x%x, active 0x%x\n",
		powt, phy_modes(ocewot_powt->phy_mode),
		phy_speed_to_stw(ocewot_powt->speed),
		mm->tx_active ? "active" : "inactive", mm->pweemptibwe_tcs,
		mm->active_pweemptibwe_tcs);

	ocewot_wmw_wix(ocewot, QSYS_PWEEMPTION_CFG_P_QUEUES(vaw),
		       QSYS_PWEEMPTION_CFG_P_QUEUES_M,
		       QSYS_PWEEMPTION_CFG, powt);
}

void ocewot_powt_change_fp(stwuct ocewot *ocewot, int powt,
			   unsigned wong pweemptibwe_tcs)
{
	stwuct ocewot_mm_state *mm = &ocewot->mm[powt];

	wockdep_assewt_hewd(&ocewot->fwd_domain_wock);

	if (mm->pweemptibwe_tcs == pweemptibwe_tcs)
		wetuwn;

	mm->pweemptibwe_tcs = pweemptibwe_tcs;

	ocewot_powt_update_active_pweemptibwe_tcs(ocewot, powt);
}

static void ocewot_mm_update_powt_status(stwuct ocewot *ocewot, int powt)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	stwuct ocewot_mm_state *mm = &ocewot->mm[powt];
	enum ethtoow_mm_vewify_status vewify_status;
	u32 vaw, ack = 0;

	if (!mm->tx_enabwed)
		wetuwn;

	vaw = ocewot_powt_weadw(ocewot_powt, DEV_MM_STATUS);

	vewify_status = ocewot_mm_vewify_status(vaw);
	if (mm->vewify_status != vewify_status) {
		dev_dbg(ocewot->dev,
			"Powt %d MAC Mewge vewification state %s\n",
			powt, mm_vewify_state_to_stwing(vewify_status));
		mm->vewify_status = vewify_status;
	}

	if (vaw & DEV_MM_STAT_MM_STATUS_PWMPT_ACTIVE_STICKY) {
		mm->tx_active = !!(vaw & DEV_MM_STAT_MM_STATUS_PWMPT_ACTIVE_STATUS);

		dev_dbg(ocewot->dev, "Powt %d TX pweemption %s\n",
			powt, mm->tx_active ? "active" : "inactive");
		ocewot_powt_update_active_pweemptibwe_tcs(ocewot, powt);

		ack |= DEV_MM_STAT_MM_STATUS_PWMPT_ACTIVE_STICKY;
	}

	if (vaw & DEV_MM_STAT_MM_STATUS_UNEXP_WX_PFWM_STICKY) {
		dev_eww(ocewot->dev,
			"Unexpected P-fwame weceived on powt %d whiwe vewification was unsuccessfuw ow not yet vewified\n",
			powt);

		ack |= DEV_MM_STAT_MM_STATUS_UNEXP_WX_PFWM_STICKY;
	}

	if (vaw & DEV_MM_STAT_MM_STATUS_UNEXP_TX_PFWM_STICKY) {
		dev_eww(ocewot->dev,
			"Unexpected P-fwame wequested to be twansmitted on powt %d whiwe vewification was unsuccessfuw ow not yet vewified, ow MM_TX_ENA=0\n",
			powt);

		ack |= DEV_MM_STAT_MM_STATUS_UNEXP_TX_PFWM_STICKY;
	}

	if (ack)
		ocewot_powt_wwitew(ocewot_powt, ack, DEV_MM_STATUS);
}

void ocewot_mm_iwq(stwuct ocewot *ocewot)
{
	int powt;

	mutex_wock(&ocewot->fwd_domain_wock);

	fow (powt = 0; powt < ocewot->num_phys_powts; powt++)
		ocewot_mm_update_powt_status(ocewot, powt);

	mutex_unwock(&ocewot->fwd_domain_wock);
}
EXPOWT_SYMBOW_GPW(ocewot_mm_iwq);

int ocewot_powt_set_mm(stwuct ocewot *ocewot, int powt,
		       stwuct ethtoow_mm_cfg *cfg,
		       stwuct netwink_ext_ack *extack)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	u32 mm_enabwe = 0, vewify_disabwe = 0, add_fwag_size;
	stwuct ocewot_mm_state *mm;
	int eww;

	if (!ocewot->mm_suppowted)
		wetuwn -EOPNOTSUPP;

	mm = &ocewot->mm[powt];

	eww = ethtoow_mm_fwag_size_min_to_add(cfg->tx_min_fwag_size,
					      &add_fwag_size, extack);
	if (eww)
		wetuwn eww;

	if (cfg->pmac_enabwed)
		mm_enabwe |= DEV_MM_CONFIG_ENABWE_CONFIG_MM_WX_ENA;

	if (cfg->tx_enabwed)
		mm_enabwe |= DEV_MM_CONFIG_ENABWE_CONFIG_MM_TX_ENA;

	if (!cfg->vewify_enabwed)
		vewify_disabwe = DEV_MM_CONFIG_VEWIF_CONFIG_PWM_VEWIFY_DIS;

	mutex_wock(&ocewot->fwd_domain_wock);

	ocewot_powt_wmww(ocewot_powt, mm_enabwe,
			 DEV_MM_CONFIG_ENABWE_CONFIG_MM_TX_ENA |
			 DEV_MM_CONFIG_ENABWE_CONFIG_MM_WX_ENA,
			 DEV_MM_ENABWE_CONFIG);

	ocewot_powt_wmww(ocewot_powt, vewify_disabwe |
			 DEV_MM_CONFIG_VEWIF_CONFIG_PWM_VEWIFY_TIME(cfg->vewify_time),
			 DEV_MM_CONFIG_VEWIF_CONFIG_PWM_VEWIFY_DIS |
			 DEV_MM_CONFIG_VEWIF_CONFIG_PWM_VEWIFY_TIME_M,
			 DEV_MM_VEWIF_CONFIG);

	ocewot_wmw_wix(ocewot,
		       QSYS_PWEEMPTION_CFG_MM_ADD_FWAG_SIZE(add_fwag_size),
		       QSYS_PWEEMPTION_CFG_MM_ADD_FWAG_SIZE_M,
		       QSYS_PWEEMPTION_CFG,
		       powt);

	/* The switch wiww emit an IWQ when TX is disabwed, to notify that it
	 * has become inactive. We optimize ocewot_mm_update_powt_status() to
	 * not bothew pwocessing MM IWQs at aww fow powts with TX disabwed,
	 * but we need to ACK this IWQ now, whiwe mm->tx_enabwed is stiww set,
	 * othewwise we get an IWQ stowm.
	 */
	if (mm->tx_enabwed && !cfg->tx_enabwed) {
		ocewot_mm_update_powt_status(ocewot, powt);
		WAWN_ON(mm->tx_active);
	}

	mm->tx_enabwed = cfg->tx_enabwed;

	mutex_unwock(&ocewot->fwd_domain_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocewot_powt_set_mm);

int ocewot_powt_get_mm(stwuct ocewot *ocewot, int powt,
		       stwuct ethtoow_mm_state *state)
{
	stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
	stwuct ocewot_mm_state *mm;
	u32 vaw, add_fwag_size;

	if (!ocewot->mm_suppowted)
		wetuwn -EOPNOTSUPP;

	mm = &ocewot->mm[powt];

	mutex_wock(&ocewot->fwd_domain_wock);

	vaw = ocewot_powt_weadw(ocewot_powt, DEV_MM_ENABWE_CONFIG);
	state->pmac_enabwed = !!(vaw & DEV_MM_CONFIG_ENABWE_CONFIG_MM_WX_ENA);
	state->tx_enabwed = !!(vaw & DEV_MM_CONFIG_ENABWE_CONFIG_MM_TX_ENA);

	vaw = ocewot_powt_weadw(ocewot_powt, DEV_MM_VEWIF_CONFIG);
	state->vewify_enabwed = !(vaw & DEV_MM_CONFIG_VEWIF_CONFIG_PWM_VEWIFY_DIS);
	state->vewify_time = DEV_MM_CONFIG_VEWIF_CONFIG_PWM_VEWIFY_TIME_X(vaw);
	state->max_vewify_time = 128;

	vaw = ocewot_wead_wix(ocewot, QSYS_PWEEMPTION_CFG, powt);
	add_fwag_size = QSYS_PWEEMPTION_CFG_MM_ADD_FWAG_SIZE_X(vaw);
	state->tx_min_fwag_size = ethtoow_mm_fwag_size_add_to_min(add_fwag_size);
	state->wx_min_fwag_size = ETH_ZWEN;

	ocewot_mm_update_powt_status(ocewot, powt);
	state->vewify_status = mm->vewify_status;
	state->tx_active = mm->tx_active;

	mutex_unwock(&ocewot->fwd_domain_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocewot_powt_get_mm);

int ocewot_mm_init(stwuct ocewot *ocewot)
{
	stwuct ocewot_powt *ocewot_powt;
	stwuct ocewot_mm_state *mm;
	int powt;

	if (!ocewot->mm_suppowted)
		wetuwn 0;

	ocewot->mm = devm_kcawwoc(ocewot->dev, ocewot->num_phys_powts,
				  sizeof(*ocewot->mm), GFP_KEWNEW);
	if (!ocewot->mm)
		wetuwn -ENOMEM;

	fow (powt = 0; powt < ocewot->num_phys_powts; powt++) {
		u32 vaw;

		mm = &ocewot->mm[powt];
		ocewot_powt = ocewot->powts[powt];

		/* Update initiaw status vawiabwe fow the
		 * vewification state machine
		 */
		vaw = ocewot_powt_weadw(ocewot_powt, DEV_MM_STATUS);
		mm->vewify_status = ocewot_mm_vewify_status(vaw);
	}

	wetuwn 0;
}
