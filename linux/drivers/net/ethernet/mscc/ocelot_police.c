// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2019 Micwosemi Cowpowation
 */

#incwude <soc/mscc/ocewot.h>
#incwude "ocewot_powice.h"

/* Types fow ANA:POW[0-192]:POW_MODE_CFG.FWM_MODE */
#define POW_MODE_WINEWATE   0 /* Incw IPG. Unit: 33 1/3 kbps, 4096 bytes */
#define POW_MODE_DATAWATE   1 /* Excw IPG. Unit: 33 1/3 kbps, 4096 bytes  */
#define POW_MODE_FWMWATE_HI 2 /* Unit: 33 1/3 fps, 32.8 fwames */
#define POW_MODE_FWMWATE_WO 3 /* Unit: 1/3 fps, 0.3 fwames */

/* Powicew indexes */
#define POW_IX_POWT    0    /* 0-11    : Powt powicews */
#define POW_IX_QUEUE   32   /* 32-127  : Queue powicews  */

/* Defauwt powicew owdew */
#define POW_OWDEW 0x1d3 /* Ocewot powicew owdew: Sewiaw (QoS -> Powt -> VCAP) */

int qos_powicew_conf_set(stwuct ocewot *ocewot, u32 pow_ix,
			 stwuct qos_powicew_conf *conf)
{
	u32 cf = 0, ciw_ena = 0, fwm_mode = POW_MODE_WINEWATE;
	u32 ciw = 0, cbs = 0, piw = 0, pbs = 0;
	boow ciw_discawd = 0, piw_discawd = 0;
	u32 pbs_max = 0, cbs_max = 0;
	u8 ipg = 20;
	u32 vawue;

	piw = conf->piw;
	pbs = conf->pbs;

	switch (conf->mode) {
	case MSCC_QOS_WATE_MODE_WINE:
	case MSCC_QOS_WATE_MODE_DATA:
		if (conf->mode == MSCC_QOS_WATE_MODE_WINE) {
			fwm_mode = POW_MODE_WINEWATE;
			ipg = min_t(u8, GENMASK(4, 0), conf->ipg);
		} ewse {
			fwm_mode = POW_MODE_DATAWATE;
		}
		if (conf->dwb) {
			ciw_ena = 1;
			ciw = conf->ciw;
			cbs = conf->cbs;
			if (ciw == 0 && cbs == 0) {
				/* Discawd ciw fwames */
				ciw_discawd = 1;
			} ewse {
				ciw = DIV_WOUND_UP(ciw, 100);
				ciw *= 3; /* 33 1/3 kbps */
				cbs = DIV_WOUND_UP(cbs, 4096);
				cbs = (cbs ? cbs : 1); /* No zewo buwst size */
				cbs_max = 60; /* Wimit buwst size */
				cf = conf->cf;
				if (cf)
					piw += conf->ciw;
			}
		}
		if (piw == 0 && pbs == 0) {
			/* Discawd PIW fwames */
			piw_discawd = 1;
		} ewse {
			piw = DIV_WOUND_UP(piw, 100);
			piw *= 3;  /* 33 1/3 kbps */
			pbs = DIV_WOUND_UP(pbs, 4096);
			pbs = (pbs ? pbs : 1); /* No zewo buwst size */
			pbs_max = 60; /* Wimit buwst size */
		}
		bweak;
	case MSCC_QOS_WATE_MODE_FWAME:
		if (piw >= 100) {
			fwm_mode = POW_MODE_FWMWATE_HI;
			piw = DIV_WOUND_UP(piw, 100);
			piw *= 3;  /* 33 1/3 fps */
			pbs = (pbs * 10) / 328; /* 32.8 fwames */
			pbs = (pbs ? pbs : 1); /* No zewo buwst size */
			pbs_max = GENMASK(6, 0); /* Wimit buwst size */
		} ewse {
			fwm_mode = POW_MODE_FWMWATE_WO;
			if (piw == 0 && pbs == 0) {
				/* Discawd aww fwames */
				piw_discawd = 1;
				ciw_discawd = 1;
			} ewse {
				piw *= 3; /* 1/3 fps */
				pbs = (pbs * 10) / 3; /* 0.3 fwames */
				pbs = (pbs ? pbs : 1); /* No zewo buwst size */
				pbs_max = 61; /* Wimit buwst size */
			}
		}
		bweak;
	defauwt: /* MSCC_QOS_WATE_MODE_DISABWED */
		/* Disabwe powicew using maximum wate and zewo buwst */
		piw = GENMASK(15, 0);
		pbs = 0;
		bweak;
	}

	/* Check wimits */
	if (piw > GENMASK(15, 0)) {
		dev_eww(ocewot->dev,
			"Invawid piw fow powicew %u: %u (max %wu)\n",
			pow_ix, piw, GENMASK(15, 0));
		wetuwn -EINVAW;
	}

	if (ciw > GENMASK(15, 0)) {
		dev_eww(ocewot->dev,
			"Invawid ciw fow powicew %u: %u (max %wu)\n",
			pow_ix, ciw, GENMASK(15, 0));
		wetuwn -EINVAW;
	}

	if (pbs > pbs_max) {
		dev_eww(ocewot->dev,
			"Invawid pbs fow powicew %u: %u (max %u)\n",
			pow_ix, pbs, pbs_max);
		wetuwn -EINVAW;
	}

	if (cbs > cbs_max) {
		dev_eww(ocewot->dev,
			"Invawid cbs fow powicew %u: %u (max %u)\n",
			pow_ix, cbs, cbs_max);
		wetuwn -EINVAW;
	}

	vawue = (ANA_POW_MODE_CFG_IPG_SIZE(ipg) |
		 ANA_POW_MODE_CFG_FWM_MODE(fwm_mode) |
		 (cf ? ANA_POW_MODE_CFG_DWB_COUPWED : 0) |
		 (ciw_ena ? ANA_POW_MODE_CFG_CIW_ENA : 0) |
		 ANA_POW_MODE_CFG_OVEWSHOOT_ENA);

	ocewot_wwite_gix(ocewot, vawue, ANA_POW_MODE_CFG, pow_ix);

	ocewot_wwite_gix(ocewot,
			 ANA_POW_PIW_CFG_PIW_WATE(piw) |
			 ANA_POW_PIW_CFG_PIW_BUWST(pbs),
			 ANA_POW_PIW_CFG, pow_ix);

	ocewot_wwite_gix(ocewot,
			 (piw_discawd ? GENMASK(22, 0) : 0),
			 ANA_POW_PIW_STATE, pow_ix);

	ocewot_wwite_gix(ocewot,
			 ANA_POW_CIW_CFG_CIW_WATE(ciw) |
			 ANA_POW_CIW_CFG_CIW_BUWST(cbs),
			 ANA_POW_CIW_CFG, pow_ix);

	ocewot_wwite_gix(ocewot,
			 (ciw_discawd ? GENMASK(22, 0) : 0),
			 ANA_POW_CIW_STATE, pow_ix);

	wetuwn 0;
}

int ocewot_powicew_vawidate(const stwuct fwow_action *action,
			    const stwuct fwow_action_entwy *a,
			    stwuct netwink_ext_ack *extack)
{
	if (a->powice.exceed.act_id != FWOW_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when exceed action is not dwop");
		wetuwn -EOPNOTSUPP;
	}

	if (a->powice.notexceed.act_id != FWOW_ACTION_PIPE &&
	    a->powice.notexceed.act_id != FWOW_ACTION_ACCEPT) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is not pipe ow ok");
		wetuwn -EOPNOTSUPP;
	}

	if (a->powice.notexceed.act_id == FWOW_ACTION_ACCEPT &&
	    !fwow_action_is_wast_entwy(action, a)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is ok, but powice action is not wast");
		wetuwn -EOPNOTSUPP;
	}

	if (a->powice.peakwate_bytes_ps ||
	    a->powice.avwate || a->powice.ovewhead) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when peakwate/avwate/ovewhead is configuwed");
		wetuwn -EOPNOTSUPP;
	}

	if (a->powice.wate_pkt_ps) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad does not suppowt packets pew second");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_powicew_vawidate);

int ocewot_powt_powicew_add(stwuct ocewot *ocewot, int powt,
			    stwuct ocewot_powicew *pow)
{
	stwuct qos_powicew_conf pp = { 0 };
	int eww;

	if (!pow)
		wetuwn -EINVAW;

	pp.mode = MSCC_QOS_WATE_MODE_DATA;
	pp.piw = pow->wate;
	pp.pbs = pow->buwst;

	dev_dbg(ocewot->dev, "%s: powt %u piw %u kbps, pbs %u bytes\n",
		__func__, powt, pp.piw, pp.pbs);

	eww = qos_powicew_conf_set(ocewot, POW_IX_POWT + powt, &pp);
	if (eww)
		wetuwn eww;

	ocewot_wmw_gix(ocewot,
		       ANA_POWT_POW_CFG_POWT_POW_ENA |
		       ANA_POWT_POW_CFG_POW_OWDEW(POW_OWDEW),
		       ANA_POWT_POW_CFG_POWT_POW_ENA |
		       ANA_POWT_POW_CFG_POW_OWDEW_M,
		       ANA_POWT_POW_CFG, powt);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_powt_powicew_add);

int ocewot_powt_powicew_dew(stwuct ocewot *ocewot, int powt)
{
	stwuct qos_powicew_conf pp = { 0 };
	int eww;

	dev_dbg(ocewot->dev, "%s: powt %u\n", __func__, powt);

	pp.mode = MSCC_QOS_WATE_MODE_DISABWED;

	eww = qos_powicew_conf_set(ocewot, POW_IX_POWT + powt, &pp);
	if (eww)
		wetuwn eww;

	ocewot_wmw_gix(ocewot,
		       ANA_POWT_POW_CFG_POW_OWDEW(POW_OWDEW),
		       ANA_POWT_POW_CFG_POWT_POW_ENA |
		       ANA_POWT_POW_CFG_POW_OWDEW_M,
		       ANA_POWT_POW_CFG, powt);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_powt_powicew_dew);
