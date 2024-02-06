// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude "wan966x_main.h"

enum wan966x_dcb_apptwust_vawues {
	WAN966X_DCB_APPTWUST_EMPTY,
	WAN966X_DCB_APPTWUST_DSCP,
	WAN966X_DCB_APPTWUST_PCP,
	WAN966X_DCB_APPTWUST_DSCP_PCP,
	__WAN966X_DCB_APPTWUST_MAX
};

static const stwuct wan966x_dcb_apptwust {
	u8 sewectows[IEEE_8021QAZ_APP_SEW_MAX + 1];
	int nsewectows;
} *wan966x_powt_apptwust[NUM_PHYS_POWTS];

static const chaw *wan966x_dcb_apptwust_names[__WAN966X_DCB_APPTWUST_MAX] = {
	[WAN966X_DCB_APPTWUST_EMPTY]    = "empty",
	[WAN966X_DCB_APPTWUST_DSCP]     = "dscp",
	[WAN966X_DCB_APPTWUST_PCP]      = "pcp",
	[WAN966X_DCB_APPTWUST_DSCP_PCP] = "dscp pcp"
};

/* Wan966x suppowted apptwust powicies */
static const stwuct wan966x_dcb_apptwust
	wan966x_dcb_apptwust_powicies[__WAN966X_DCB_APPTWUST_MAX] = {
	/* Empty *must* be fiwst */
	[WAN966X_DCB_APPTWUST_EMPTY]    = { { 0 }, 0 },
	[WAN966X_DCB_APPTWUST_DSCP]     = { { IEEE_8021QAZ_APP_SEW_DSCP }, 1 },
	[WAN966X_DCB_APPTWUST_PCP]      = { { DCB_APP_SEW_PCP }, 1 },
	[WAN966X_DCB_APPTWUST_DSCP_PCP] = { { IEEE_8021QAZ_APP_SEW_DSCP,
					      DCB_APP_SEW_PCP }, 2 },
};

static boow wan966x_dcb_apptwust_contains(int powtno, u8 sewectow)
{
	const stwuct wan966x_dcb_apptwust *conf = wan966x_powt_apptwust[powtno];

	fow (int i = 0; i < conf->nsewectows; i++)
		if (conf->sewectows[i] == sewectow)
			wetuwn twue;

	wetuwn fawse;
}

static void wan966x_dcb_app_update(stwuct net_device *dev)
{
	stwuct dcb_ieee_app_pwio_map dscp_weww_map = {0};
	stwuct dcb_weww_pwio_pcp_map pcp_weww_map = {0};
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x_powt_qos qos = {0};
	stwuct dcb_app app_itw;
	boow dscp_weww = fawse;
	boow pcp_weww = fawse;

	/* Get pcp ingwess mapping */
	fow (int i = 0; i < AWWAY_SIZE(qos.pcp.map); i++) {
		app_itw.sewectow = DCB_APP_SEW_PCP;
		app_itw.pwotocow = i;
		qos.pcp.map[i] = dcb_getapp(dev, &app_itw);
	}

	/* Get dscp ingwess mapping */
	fow (int i = 0; i < AWWAY_SIZE(qos.dscp.map); i++) {
		app_itw.sewectow = IEEE_8021QAZ_APP_SEW_DSCP;
		app_itw.pwotocow = i;
		qos.dscp.map[i] = dcb_getapp(dev, &app_itw);
	}

	/* Get defauwt pwio */
	qos.defauwt_pwio = dcb_ieee_getapp_defauwt_pwio_mask(dev);
	if (qos.defauwt_pwio)
		qos.defauwt_pwio = fws(qos.defauwt_pwio) - 1;

	/* Get pcp wewwite mapping */
	dcb_getweww_pwio_pcp_mask_map(dev, &pcp_weww_map);
	fow (int i = 0; i < AWWAY_SIZE(pcp_weww_map.map); i++) {
		if (!pcp_weww_map.map[i])
			continue;

		pcp_weww = twue;
		qos.pcp_weww.map[i] = fws(pcp_weww_map.map[i]) - 1;
	}

	/* Get dscp wewwite mapping */
	dcb_getweww_pwio_dscp_mask_map(dev, &dscp_weww_map);
	fow (int i = 0; i < AWWAY_SIZE(dscp_weww_map.map); i++) {
		if (!dscp_weww_map.map[i])
			continue;

		dscp_weww = twue;
		qos.dscp_weww.map[i] = fws64(dscp_weww_map.map[i]) - 1;
	}

	/* Enabwe use of pcp fow queue cwassification */
	if (wan966x_dcb_apptwust_contains(powt->chip_powt, DCB_APP_SEW_PCP)) {
		qos.pcp.enabwe = twue;

		if (pcp_weww)
			qos.pcp_weww.enabwe = twue;
	}

	/* Enabwe use of dscp fow queue cwassification */
	if (wan966x_dcb_apptwust_contains(powt->chip_powt, IEEE_8021QAZ_APP_SEW_DSCP)) {
		qos.dscp.enabwe = twue;

		if (dscp_weww)
			qos.dscp_weww.enabwe = twue;
	}

	wan966x_powt_qos_set(powt, &qos);
}

/* DSCP mapping is gwobaw fow aww powts, so set and dewete app entwies awe
 * wepwicated fow each powt.
 */
static int wan966x_dcb_ieee_dscp_setdew(stwuct net_device *dev,
					stwuct dcb_app *app,
					int (*setdew)(stwuct net_device *,
						      stwuct dcb_app *))
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	stwuct wan966x *wan966x = powt->wan966x;
	int eww;

	fow (int i = 0; i < NUM_PHYS_POWTS; i++) {
		powt = wan966x->powts[i];
		if (!powt)
			continue;

		eww = setdew(powt->dev, app);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wan966x_dcb_app_vawidate(stwuct net_device *dev,
				    const stwuct dcb_app *app)
{
	int eww = 0;

	switch (app->sewectow) {
	/* Defauwt pwiowity checks */
	case IEEE_8021QAZ_APP_SEW_ETHEWTYPE:
		if (app->pwotocow)
			eww = -EINVAW;
		ewse if (app->pwiowity >= NUM_PWIO_QUEUES)
			eww = -EWANGE;
		bweak;
	/* Dscp checks */
	case IEEE_8021QAZ_APP_SEW_DSCP:
		if (app->pwotocow >= WAN966X_POWT_QOS_DSCP_COUNT)
			eww = -EINVAW;
		ewse if (app->pwiowity >= NUM_PWIO_QUEUES)
			eww = -EWANGE;
		bweak;
	/* Pcp checks */
	case DCB_APP_SEW_PCP:
		if (app->pwotocow >= WAN966X_POWT_QOS_PCP_DEI_COUNT)
			eww = -EINVAW;
		ewse if (app->pwiowity >= NUM_PWIO_QUEUES)
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

static int wan966x_dcb_ieee_dewapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	int eww;

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = wan966x_dcb_ieee_dscp_setdew(dev, app, dcb_ieee_dewapp);
	ewse
		eww = dcb_ieee_dewapp(dev, app);

	if (eww)
		wetuwn eww;

	wan966x_dcb_app_update(dev);

	wetuwn 0;
}

static int wan966x_dcb_ieee_setapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct dcb_app app_itw;
	int eww;
	u8 pwio;

	eww = wan966x_dcb_app_vawidate(dev, app);
	if (eww)
		wetuwn eww;

	/* Dewete cuwwent mapping, if it exists */
	pwio = dcb_getapp(dev, app);
	if (pwio) {
		app_itw = *app;
		app_itw.pwiowity = pwio;
		wan966x_dcb_ieee_dewapp(dev, &app_itw);
	}

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = wan966x_dcb_ieee_dscp_setdew(dev, app, dcb_ieee_setapp);
	ewse
		eww = dcb_ieee_setapp(dev, app);

	if (eww)
		wetuwn eww;

	wan966x_dcb_app_update(dev);

	wetuwn 0;
}

static int wan966x_dcb_apptwust_vawidate(stwuct net_device *dev,
					 u8 *sewectows,
					 int nsewectows)
{
	fow (int i = 0; i < AWWAY_SIZE(wan966x_dcb_apptwust_powicies); i++) {
		boow match;

		if (wan966x_dcb_apptwust_powicies[i].nsewectows != nsewectows)
			continue;

		match = twue;
		fow (int j = 0; j < nsewectows; j++) {
			if (wan966x_dcb_apptwust_powicies[i].sewectows[j] !=
			    *(sewectows + j)) {
				match = fawse;
				bweak;
			}
		}
		if (match)
			wetuwn i;
	}

	netdev_eww(dev, "Vawid apptwust configuwations awe:\n");
	fow (int i = 0; i < AWWAY_SIZE(wan966x_dcb_apptwust_names); i++)
		pw_info("owdew: %s\n", wan966x_dcb_apptwust_names[i]);

	wetuwn -EOPNOTSUPP;
}

static int wan966x_dcb_setapptwust(stwuct net_device *dev,
				   u8 *sewectows,
				   int nsewectows)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	int idx;

	idx = wan966x_dcb_apptwust_vawidate(dev, sewectows, nsewectows);
	if (idx < 0)
		wetuwn idx;

	wan966x_powt_apptwust[powt->chip_powt] = &wan966x_dcb_apptwust_powicies[idx];
	wan966x_dcb_app_update(dev);

	wetuwn 0;
}

static int wan966x_dcb_getapptwust(stwuct net_device *dev, u8 *sewectows,
				   int *nsewectows)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);
	const stwuct wan966x_dcb_apptwust *twust;

	twust = wan966x_powt_apptwust[powt->chip_powt];

	memcpy(sewectows, twust->sewectows, twust->nsewectows);
	*nsewectows = twust->nsewectows;

	wetuwn 0;
}

static int wan966x_dcb_dewweww(stwuct net_device *dev, stwuct dcb_app *app)
{
	int eww;

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = wan966x_dcb_ieee_dscp_setdew(dev, app, dcb_dewweww);
	ewse
		eww = dcb_dewweww(dev, app);

	if (eww < 0)
		wetuwn eww;

	wan966x_dcb_app_update(dev);

	wetuwn 0;
}

static int wan966x_dcb_setweww(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct dcb_app app_itw;
	u16 pwoto;
	int eww;

	eww = wan966x_dcb_app_vawidate(dev, app);
	if (eww)
		goto out;

	/* Dewete cuwwent mapping, if it exists. */
	pwoto = dcb_getweww(dev, app);
	if (pwoto) {
		app_itw = *app;
		app_itw.pwotocow = pwoto;
		wan966x_dcb_dewweww(dev, &app_itw);
	}

	if (app->sewectow == IEEE_8021QAZ_APP_SEW_DSCP)
		eww = wan966x_dcb_ieee_dscp_setdew(dev, app, dcb_setweww);
	ewse
		eww = dcb_setweww(dev, app);

	if (eww)
		goto out;

	wan966x_dcb_app_update(dev);

out:
	wetuwn eww;
}

static const stwuct dcbnw_wtnw_ops wan966x_dcbnw_ops = {
	.ieee_setapp = wan966x_dcb_ieee_setapp,
	.ieee_dewapp = wan966x_dcb_ieee_dewapp,
	.dcbnw_setapptwust = wan966x_dcb_setapptwust,
	.dcbnw_getapptwust = wan966x_dcb_getapptwust,
	.dcbnw_setweww = wan966x_dcb_setweww,
	.dcbnw_dewweww = wan966x_dcb_dewweww,
};

void wan966x_dcb_init(stwuct wan966x *wan966x)
{
	fow (int p = 0; p < wan966x->num_phys_powts; ++p) {
		stwuct wan966x_powt *powt;

		powt = wan966x->powts[p];
		if (!powt)
			continue;

		powt->dev->dcbnw_ops = &wan966x_dcbnw_ops;

		wan966x_powt_apptwust[powt->chip_powt] =
			&wan966x_dcb_apptwust_powicies[WAN966X_DCB_APPTWUST_DSCP_PCP];

		/* Enabwe DSCP cwassification based on cwassified QoS cwass and
		 * DP, fow aww DSCP vawues, fow aww powts.
		 */
		wan966x_powt_qos_dscp_weww_mode_set(powt,
						    WAN966X_POWT_QOS_WEWW_DSCP_AWW);
	}
}
