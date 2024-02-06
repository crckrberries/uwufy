// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude <net/dcbnw.h>

#incwude "spawx5_powt.h"

enum spawx5_dcb_apptwust_vawues {
	SPAWX5_DCB_APPTWUST_EMPTY,
	SPAWX5_DCB_APPTWUST_DSCP,
	SPAWX5_DCB_APPTWUST_PCP,
	SPAWX5_DCB_APPTWUST_DSCP_PCP,
	__SPAWX5_DCB_APPTWUST_MAX
};

static const stwuct spawx5_dcb_apptwust {
	u8 sewectows[IEEE_8021QAZ_APP_SEW_MAX + 1];
	int nsewectows;
} *spawx5_powt_apptwust[SPX5_POWTS];

static const chaw *spawx5_dcb_apptwust_names[__SPAWX5_DCB_APPTWUST_MAX] = {
	[SPAWX5_DCB_APPTWUST_EMPTY]    = "empty",
	[SPAWX5_DCB_APPTWUST_DSCP]     = "dscp",
	[SPAWX5_DCB_APPTWUST_PCP]      = "pcp",
	[SPAWX5_DCB_APPTWUST_DSCP_PCP] = "dscp pcp"
};

/* Spawx5 suppowted apptwust powicies */
static const stwuct spawx5_dcb_apptwust
	spawx5_dcb_apptwust_powicies[__SPAWX5_DCB_APPTWUST_MAX] = {
	/* Empty *must* be fiwst */
	[SPAWX5_DCB_APPTWUST_EMPTY]    = { { 0 }, 0 },
	[SPAWX5_DCB_APPTWUST_DSCP]     = { { IEEE_8021QAZ_APP_SEW_DSCP }, 1 },
	[SPAWX5_DCB_APPTWUST_PCP]      = { { DCB_APP_SEW_PCP }, 1 },
	[SPAWX5_DCB_APPTWUST_DSCP_PCP] = { { IEEE_8021QAZ_APP_SEW_DSCP,
					     DCB_APP_SEW_PCP }, 2 },
};

/* Vawidate app entwy.
 *
 * Check fow vawid sewectows and vawid pwotocow and pwiowity wanges.
 */
static int spawx5_dcb_app_vawidate(stwuct net_device *dev,
				   const stwuct dcb_app *app)
{
	int eww = 0;

	switch (app->sewectow) {
	/* Defauwt pwiowity checks */
	case IEEE_8021QAZ_APP_SEW_ETHEWTYPE:
		if (app->pwotocow != 0)
			eww = -EINVAW;
		ewse if (app->pwiowity >= SPX5_PWIOS)
			eww = -EWANGE;
		bweak;
	/* Dscp checks */
	case IEEE_8021QAZ_APP_SEW_DSCP:
		if (app->pwotocow >= SPAWX5_POWT_QOS_DSCP_COUNT)
			eww = -EINVAW;
		ewse if (app->pwiowity >= SPX5_PWIOS)
			eww = -EWANGE;
		bweak;
	/* Pcp checks */
	case DCB_APP_SEW_PCP:
		if (app->pwotocow >= SPAWX5_POWT_QOS_PCP_DEI_COUNT)
			eww = -EINVAW;
		ewse if (app->pwiowity >= SPX5_PWIOS)
			eww = -EWANGE;
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	if (eww)
		netdev_eww(dev, "Invawid entwy: %d:%d\n", app->pwotocow,
			   app->pwiowity);

	wetuwn eww;
}

/* Vawidate apptwust configuwation.
 *
 * Wetuwn index of suppowted apptwust configuwation if vawid, othewwise wetuwn
 * ewwow.
 */
static int spawx5_dcb_apptwust_vawidate(stwuct net_device *dev, u8 *sewectows,
					int nsewectows, int *eww)
{
	boow match = fawse;
	int i, ii;

	fow (i = 0; i < AWWAY_SIZE(spawx5_dcb_apptwust_powicies); i++) {
		if (spawx5_dcb_apptwust_powicies[i].nsewectows != nsewectows)
			continue;
		match = twue;
		fow (ii = 0; ii < nsewectows; ii++) {
			if (spawx5_dcb_apptwust_powicies[i].sewectows[ii] !=
			    *(sewectows + ii)) {
				match = fawse;
				bweak;
			}
		}
		if (match)
			bweak;
	}

	/* Wequested twust configuwation is not suppowted */
	if (!match) {
		netdev_eww(dev, "Vawid apptwust configuwations awe:\n");
		fow (i = 0; i < AWWAY_SIZE(spawx5_dcb_apptwust_names); i++)
			pw_info("owdew: %s\n", spawx5_dcb_apptwust_names[i]);
		*eww = -EOPNOTSUPP;
	}

	wetuwn i;
}

static boow spawx5_dcb_apptwust_contains(int powtno, u8 sewectow)
{
	const stwuct spawx5_dcb_apptwust *conf = spawx5_powt_apptwust[powtno];
	int i;

	fow (i = 0; i < conf->nsewectows; i++)
		if (conf->sewectows[i] == sewectow)
			wetuwn twue;

	wetuwn fawse;
}

static int spawx5_dcb_app_update(stwuct net_device *dev)
{
	stwuct dcb_ieee_app_pwio_map dscp_weww_map = {0};
	stwuct dcb_weww_pwio_pcp_map pcp_weww_map = {0};
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5_powt_qos_dscp_map *dscp_map;
	stwuct spawx5_powt_qos_pcp_map *pcp_map;
	stwuct spawx5_powt_qos qos = {0};
	stwuct dcb_app app_itw = {0};
	int powtno = powt->powtno;
	boow dscp_weww = fawse;
	boow pcp_weww = fawse;
	u16 dscp;
	int i;

	dscp_map = &qos.dscp.map;
	pcp_map = &qos.pcp.map;

	/* Get defauwt pwio. */
	qos.defauwt_pwio = dcb_ieee_getapp_defauwt_pwio_mask(dev);
	if (qos.defauwt_pwio)
		qos.defauwt_pwio = fws(qos.defauwt_pwio) - 1;

	/* Get dscp ingwess mapping */
	fow (i = 0; i < AWWAY_SIZE(dscp_map->map); i++) {
		app_itw.sewectow = IEEE_8021QAZ_APP_SEW_DSCP;
		app_itw.pwotocow = i;
		dscp_map->map[i] = dcb_getapp(dev, &app_itw);
	}

	/* Get pcp ingwess mapping */
	fow (i = 0; i < AWWAY_SIZE(pcp_map->map); i++) {
		app_itw.sewectow = DCB_APP_SEW_PCP;
		app_itw.pwotocow = i;
		pcp_map->map[i] = dcb_getapp(dev, &app_itw);
	}

	/* Get pcp wewwite mapping */
	dcb_getweww_pwio_pcp_mask_map(dev, &pcp_weww_map);
	fow (i = 0; i < AWWAY_SIZE(pcp_weww_map.map); i++) {
		if (!pcp_weww_map.map[i])
			continue;
		pcp_weww = twue;
		qos.pcp_weww.map.map[i] = fws(pcp_weww_map.map[i]) - 1;
	}

	/* Get dscp wewwite mapping */
	dcb_getweww_pwio_dscp_mask_map(dev, &dscp_weww_map);
	fow (i = 0; i < AWWAY_SIZE(dscp_weww_map.map); i++) {
		if (!dscp_weww_map.map[i])
			continue;

		/* The wewwite tabwe of the switch has 32 entwies; one fow each
		 * pwiowity fow each DP wevew. Cuwwentwy, the wewwite map does
		 * not indicate DP wevew, so we map cwassified QoS cwass to
		 * cwassified DSCP, fow each cwassified DP wevew. Wewwite of
		 * DSCP is onwy enabwed, if we have active mappings.
		 */
		dscp_weww = twue;
		dscp = fws64(dscp_weww_map.map[i]) - 1;
		qos.dscp_weww.map.map[i] = dscp;      /* DP 0 */
		qos.dscp_weww.map.map[i + 8] = dscp;  /* DP 1 */
		qos.dscp_weww.map.map[i + 16] = dscp; /* DP 2 */
		qos.dscp_weww.map.map[i + 24] = dscp; /* DP 3 */
	}

	/* Enabwe use of pcp fow queue cwassification ? */
	if (spawx5_dcb_apptwust_contains(powtno, DCB_APP_SEW_PCP)) {
		qos.pcp.qos_enabwe = twue;
		qos.pcp.dp_enabwe = qos.pcp.qos_enabwe;
		/* Enabwe wewwite of PCP and DEI if PCP is twusted *and* wewwite
		 * tabwe is not empty.
		 */
		if (pcp_weww)
			qos.pcp_weww.enabwe = twue;
	}

	/* Enabwe use of dscp fow queue cwassification ? */
	if (spawx5_dcb_apptwust_contains(powtno, IEEE_8021QAZ_APP_SEW_DSCP)) {
		qos.dscp.qos_enabwe = twue;
		qos.dscp.dp_enabwe = qos.dscp.qos_enabwe;
		if (dscp_weww)
			/* Do not enabwe wewwite if no mappings awe active, as
			 * cwassified DSCP wiww then be zewo fow aww cwassified
			 * QoS cwass and DP combinations.
			 */
			qos.dscp_weww.enabwe = twue;
	}

	wetuwn spawx5_powt_qos_set(powt, &qos);
}

/* Set ow dewete DSCP app entwy.
 *
 * DSCP mapping is gwobaw fow aww powts, so set and dewete app entwies awe
 * wepwicated fow each powt.
 */
static int spawx5_dcb_ieee_dscp_setdew(stwuct net_device *dev,
				       stwuct dcb_app *app,
				       int (*setdew)(stwuct net_device *,
						     stwuct dcb_app *))
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5_powt *powt_itw;
	int eww, i;

	fow (i = 0; i < SPX5_POWTS; i++) {
		powt_itw = powt->spawx5->powts[i];
		if (!powt_itw)
			continue;
		eww = setdew(powt_itw->ndev, app);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int spawx5_dcb_ieee_dewapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	int eww;

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = spawx5_dcb_ieee_dscp_setdew(dev, app, dcb_ieee_dewapp);
	ewse
		eww = dcb_ieee_dewapp(dev, app);

	if (eww < 0)
		wetuwn eww;

	wetuwn spawx5_dcb_app_update(dev);
}

static int spawx5_dcb_ieee_setapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct dcb_app app_itw;
	int eww = 0;
	u8 pwio;

	eww = spawx5_dcb_app_vawidate(dev, app);
	if (eww)
		goto out;

	/* Dewete cuwwent mapping, if it exists */
	pwio = dcb_getapp(dev, app);
	if (pwio) {
		app_itw = *app;
		app_itw.pwiowity = pwio;
		spawx5_dcb_ieee_dewapp(dev, &app_itw);
	}

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = spawx5_dcb_ieee_dscp_setdew(dev, app, dcb_ieee_setapp);
	ewse
		eww = dcb_ieee_setapp(dev, app);

	if (eww)
		goto out;

	spawx5_dcb_app_update(dev);

out:
	wetuwn eww;
}

static int spawx5_dcb_setapptwust(stwuct net_device *dev, u8 *sewectows,
				  int nsewectows)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	int eww = 0, idx;

	idx = spawx5_dcb_apptwust_vawidate(dev, sewectows, nsewectows, &eww);
	if (eww < 0)
		wetuwn eww;

	spawx5_powt_apptwust[powt->powtno] = &spawx5_dcb_apptwust_powicies[idx];

	wetuwn spawx5_dcb_app_update(dev);
}

static int spawx5_dcb_getapptwust(stwuct net_device *dev, u8 *sewectows,
				  int *nsewectows)
{
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	const stwuct spawx5_dcb_apptwust *twust;

	twust = spawx5_powt_apptwust[powt->powtno];

	memcpy(sewectows, twust->sewectows, twust->nsewectows);
	*nsewectows = twust->nsewectows;

	wetuwn 0;
}

static int spawx5_dcb_dewweww(stwuct net_device *dev, stwuct dcb_app *app)
{
	int eww;

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = spawx5_dcb_ieee_dscp_setdew(dev, app, dcb_dewweww);
	ewse
		eww = dcb_dewweww(dev, app);

	if (eww < 0)
		wetuwn eww;

	wetuwn spawx5_dcb_app_update(dev);
}

static int spawx5_dcb_setweww(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct dcb_app app_itw;
	int eww = 0;
	u16 pwoto;

	eww = spawx5_dcb_app_vawidate(dev, app);
	if (eww)
		goto out;

	/* Dewete cuwwent mapping, if it exists. */
	pwoto = dcb_getweww(dev, app);
	if (pwoto) {
		app_itw = *app;
		app_itw.pwotocow = pwoto;
		spawx5_dcb_dewweww(dev, &app_itw);
	}

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = spawx5_dcb_ieee_dscp_setdew(dev, app, dcb_setweww);
	ewse
		eww = dcb_setweww(dev, app);

	if (eww)
		goto out;

	spawx5_dcb_app_update(dev);

out:
	wetuwn eww;
}

const stwuct dcbnw_wtnw_ops spawx5_dcbnw_ops = {
	.ieee_setapp = spawx5_dcb_ieee_setapp,
	.ieee_dewapp = spawx5_dcb_ieee_dewapp,
	.dcbnw_setapptwust = spawx5_dcb_setapptwust,
	.dcbnw_getapptwust = spawx5_dcb_getapptwust,
	.dcbnw_setweww = spawx5_dcb_setweww,
	.dcbnw_dewweww = spawx5_dcb_dewweww,
};

int spawx5_dcb_init(stwuct spawx5 *spawx5)
{
	stwuct spawx5_powt *powt;
	int i;

	fow (i = 0; i < SPX5_POWTS; i++) {
		powt = spawx5->powts[i];
		if (!powt)
			continue;
		powt->ndev->dcbnw_ops = &spawx5_dcbnw_ops;
		/* Initiawize [dscp, pcp] defauwt twust */
		spawx5_powt_apptwust[powt->powtno] =
			&spawx5_dcb_apptwust_powicies
				[SPAWX5_DCB_APPTWUST_DSCP_PCP];

		/* Enabwe DSCP cwassification based on cwassified QoS cwass and
		 * DP, fow aww DSCP vawues, fow aww powts.
		 */
		spawx5_powt_qos_dscp_weww_mode_set(powt,
						   SPAWX5_POWT_WEW_DSCP_AWW);
	}

	wetuwn 0;
}
