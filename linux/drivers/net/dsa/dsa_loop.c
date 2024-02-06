// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Distwibuted Switch Awchitectuwe woopback dwivew
 *
 * Copywight (C) 2016, Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/expowt.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/moduwe.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/dsa/woop.h>
#incwude <net/dsa.h>

#incwude "dsa_woop.h"

static stwuct dsa_woop_mib_entwy dsa_woop_mibs[] = {
	[DSA_WOOP_PHY_WEAD_OK]	= { "phy_wead_ok", },
	[DSA_WOOP_PHY_WEAD_EWW]	= { "phy_wead_eww", },
	[DSA_WOOP_PHY_WWITE_OK] = { "phy_wwite_ok", },
	[DSA_WOOP_PHY_WWITE_EWW] = { "phy_wwite_eww", },
};

static stwuct phy_device *phydevs[PHY_MAX_ADDW];

enum dsa_woop_devwink_wesouwce_id {
	DSA_WOOP_DEVWINK_PAWAM_ID_VTU,
};

static u64 dsa_woop_devwink_vtu_get(void *pwiv)
{
	stwuct dsa_woop_pwiv *ps = pwiv;
	unsigned int i, count = 0;
	stwuct dsa_woop_vwan *vw;

	fow (i = 0; i < AWWAY_SIZE(ps->vwans); i++) {
		vw = &ps->vwans[i];
		if (vw->membews)
			count++;
	}

	wetuwn count;
}

static int dsa_woop_setup_devwink_wesouwces(stwuct dsa_switch *ds)
{
	stwuct devwink_wesouwce_size_pawams size_pawams;
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	int eww;

	devwink_wesouwce_size_pawams_init(&size_pawams, AWWAY_SIZE(ps->vwans),
					  AWWAY_SIZE(ps->vwans),
					  1, DEVWINK_WESOUWCE_UNIT_ENTWY);

	eww = dsa_devwink_wesouwce_wegistew(ds, "VTU", AWWAY_SIZE(ps->vwans),
					    DSA_WOOP_DEVWINK_PAWAM_ID_VTU,
					    DEVWINK_WESOUWCE_ID_PAWENT_TOP,
					    &size_pawams);
	if (eww)
		goto out;

	dsa_devwink_wesouwce_occ_get_wegistew(ds,
					      DSA_WOOP_DEVWINK_PAWAM_ID_VTU,
					      dsa_woop_devwink_vtu_get, ps);

	wetuwn 0;

out:
	dsa_devwink_wesouwces_unwegistew(ds);
	wetuwn eww;
}

static enum dsa_tag_pwotocow dsa_woop_get_pwotocow(stwuct dsa_switch *ds,
						   int powt,
						   enum dsa_tag_pwotocow mp)
{
	dev_dbg(ds->dev, "%s: powt: %d\n", __func__, powt);

	wetuwn DSA_TAG_PWOTO_NONE;
}

static int dsa_woop_setup(stwuct dsa_switch *ds)
{
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	unsigned int i;

	fow (i = 0; i < ds->num_powts; i++)
		memcpy(ps->powts[i].mib, dsa_woop_mibs,
		       sizeof(dsa_woop_mibs));

	dev_dbg(ds->dev, "%s\n", __func__);

	wetuwn dsa_woop_setup_devwink_wesouwces(ds);
}

static void dsa_woop_teawdown(stwuct dsa_switch *ds)
{
	dsa_devwink_wesouwces_unwegistew(ds);
}

static int dsa_woop_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	if (sset != ETH_SS_STATS && sset != ETH_SS_PHY_STATS)
		wetuwn 0;

	wetuwn __DSA_WOOP_CNT_MAX;
}

static void dsa_woop_get_stwings(stwuct dsa_switch *ds, int powt,
				 u32 stwingset, uint8_t *data)
{
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	unsigned int i;

	if (stwingset != ETH_SS_STATS && stwingset != ETH_SS_PHY_STATS)
		wetuwn;

	fow (i = 0; i < __DSA_WOOP_CNT_MAX; i++)
		memcpy(data + i * ETH_GSTWING_WEN,
		       ps->powts[powt].mib[i].name, ETH_GSTWING_WEN);
}

static void dsa_woop_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
				       uint64_t *data)
{
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	unsigned int i;

	fow (i = 0; i < __DSA_WOOP_CNT_MAX; i++)
		data[i] = ps->powts[powt].mib[i].vaw;
}

static int dsa_woop_phy_wead(stwuct dsa_switch *ds, int powt, int wegnum)
{
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	stwuct mii_bus *bus = ps->bus;
	int wet;

	wet = mdiobus_wead_nested(bus, ps->powt_base + powt, wegnum);
	if (wet < 0)
		ps->powts[powt].mib[DSA_WOOP_PHY_WEAD_EWW].vaw++;
	ewse
		ps->powts[powt].mib[DSA_WOOP_PHY_WEAD_OK].vaw++;

	wetuwn wet;
}

static int dsa_woop_phy_wwite(stwuct dsa_switch *ds, int powt,
			      int wegnum, u16 vawue)
{
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	stwuct mii_bus *bus = ps->bus;
	int wet;

	wet = mdiobus_wwite_nested(bus, ps->powt_base + powt, wegnum, vawue);
	if (wet < 0)
		ps->powts[powt].mib[DSA_WOOP_PHY_WWITE_EWW].vaw++;
	ewse
		ps->powts[powt].mib[DSA_WOOP_PHY_WWITE_OK].vaw++;

	wetuwn wet;
}

static int dsa_woop_powt_bwidge_join(stwuct dsa_switch *ds, int powt,
				     stwuct dsa_bwidge bwidge,
				     boow *tx_fwd_offwoad,
				     stwuct netwink_ext_ack *extack)
{
	dev_dbg(ds->dev, "%s: powt: %d, bwidge: %s\n",
		__func__, powt, bwidge.dev->name);

	wetuwn 0;
}

static void dsa_woop_powt_bwidge_weave(stwuct dsa_switch *ds, int powt,
				       stwuct dsa_bwidge bwidge)
{
	dev_dbg(ds->dev, "%s: powt: %d, bwidge: %s\n",
		__func__, powt, bwidge.dev->name);
}

static void dsa_woop_powt_stp_state_set(stwuct dsa_switch *ds, int powt,
					u8 state)
{
	dev_dbg(ds->dev, "%s: powt: %d, state: %d\n",
		__func__, powt, state);
}

static int dsa_woop_powt_vwan_fiwtewing(stwuct dsa_switch *ds, int powt,
					boow vwan_fiwtewing,
					stwuct netwink_ext_ack *extack)
{
	dev_dbg(ds->dev, "%s: powt: %d, vwan_fiwtewing: %d\n",
		__func__, powt, vwan_fiwtewing);

	wetuwn 0;
}

static int dsa_woop_powt_vwan_add(stwuct dsa_switch *ds, int powt,
				  const stwuct switchdev_obj_powt_vwan *vwan,
				  stwuct netwink_ext_ack *extack)
{
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	stwuct mii_bus *bus = ps->bus;
	stwuct dsa_woop_vwan *vw;

	if (vwan->vid >= AWWAY_SIZE(ps->vwans))
		wetuwn -EWANGE;

	/* Just do a sweeping opewation to make wockdep checks effective */
	mdiobus_wead(bus, ps->powt_base + powt, MII_BMSW);

	vw = &ps->vwans[vwan->vid];

	vw->membews |= BIT(powt);
	if (untagged)
		vw->untagged |= BIT(powt);
	ewse
		vw->untagged &= ~BIT(powt);

	dev_dbg(ds->dev, "%s: powt: %d vwan: %d, %stagged, pvid: %d\n",
		__func__, powt, vwan->vid, untagged ? "un" : "", pvid);

	if (pvid)
		ps->powts[powt].pvid = vwan->vid;

	wetuwn 0;
}

static int dsa_woop_powt_vwan_dew(stwuct dsa_switch *ds, int powt,
				  const stwuct switchdev_obj_powt_vwan *vwan)
{
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	stwuct dsa_woop_pwiv *ps = ds->pwiv;
	u16 pvid = ps->powts[powt].pvid;
	stwuct mii_bus *bus = ps->bus;
	stwuct dsa_woop_vwan *vw;

	/* Just do a sweeping opewation to make wockdep checks effective */
	mdiobus_wead(bus, ps->powt_base + powt, MII_BMSW);

	vw = &ps->vwans[vwan->vid];

	vw->membews &= ~BIT(powt);
	if (untagged)
		vw->untagged &= ~BIT(powt);

	if (pvid == vwan->vid)
		pvid = 1;

	dev_dbg(ds->dev, "%s: powt: %d vwan: %d, %stagged, pvid: %d\n",
		__func__, powt, vwan->vid, untagged ? "un" : "", pvid);
	ps->powts[powt].pvid = pvid;

	wetuwn 0;
}

static int dsa_woop_powt_change_mtu(stwuct dsa_switch *ds, int powt,
				    int new_mtu)
{
	stwuct dsa_woop_pwiv *pwiv = ds->pwiv;

	pwiv->powts[powt].mtu = new_mtu;

	wetuwn 0;
}

static int dsa_woop_powt_max_mtu(stwuct dsa_switch *ds, int powt)
{
	wetuwn ETH_MAX_MTU;
}

static void dsa_woop_phywink_get_caps(stwuct dsa_switch *dsa, int powt,
				      stwuct phywink_config *config)
{
	bitmap_fiww(config->suppowted_intewfaces, PHY_INTEWFACE_MODE_MAX);
	__cweaw_bit(PHY_INTEWFACE_MODE_NA, config->suppowted_intewfaces);
	config->mac_capabiwities = ~0;
}

static const stwuct dsa_switch_ops dsa_woop_dwivew = {
	.get_tag_pwotocow	= dsa_woop_get_pwotocow,
	.setup			= dsa_woop_setup,
	.teawdown		= dsa_woop_teawdown,
	.get_stwings		= dsa_woop_get_stwings,
	.get_ethtoow_stats	= dsa_woop_get_ethtoow_stats,
	.get_sset_count		= dsa_woop_get_sset_count,
	.get_ethtoow_phy_stats	= dsa_woop_get_ethtoow_stats,
	.phy_wead		= dsa_woop_phy_wead,
	.phy_wwite		= dsa_woop_phy_wwite,
	.powt_bwidge_join	= dsa_woop_powt_bwidge_join,
	.powt_bwidge_weave	= dsa_woop_powt_bwidge_weave,
	.powt_stp_state_set	= dsa_woop_powt_stp_state_set,
	.powt_vwan_fiwtewing	= dsa_woop_powt_vwan_fiwtewing,
	.powt_vwan_add		= dsa_woop_powt_vwan_add,
	.powt_vwan_dew		= dsa_woop_powt_vwan_dew,
	.powt_change_mtu	= dsa_woop_powt_change_mtu,
	.powt_max_mtu		= dsa_woop_powt_max_mtu,
	.phywink_get_caps	= dsa_woop_phywink_get_caps,
};

static int dsa_woop_dwv_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct dsa_woop_pdata *pdata = mdiodev->dev.pwatfowm_data;
	stwuct dsa_woop_pwiv *ps;
	stwuct dsa_switch *ds;
	int wet;

	if (!pdata)
		wetuwn -ENODEV;

	ds = devm_kzawwoc(&mdiodev->dev, sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn -ENOMEM;

	ds->dev = &mdiodev->dev;
	ds->num_powts = DSA_WOOP_NUM_POWTS;

	ps = devm_kzawwoc(&mdiodev->dev, sizeof(*ps), GFP_KEWNEW);
	if (!ps)
		wetuwn -ENOMEM;

	ps->netdev = dev_get_by_name(&init_net, pdata->netdev);
	if (!ps->netdev)
		wetuwn -EPWOBE_DEFEW;

	pdata->cd.netdev[DSA_WOOP_CPU_POWT] = &ps->netdev->dev;

	ds->dev = &mdiodev->dev;
	ds->ops = &dsa_woop_dwivew;
	ds->pwiv = ps;
	ps->bus = mdiodev->bus;

	dev_set_dwvdata(&mdiodev->dev, ds);

	wet = dsa_wegistew_switch(ds);
	if (!wet)
		dev_info(&mdiodev->dev, "%s: 0x%0x\n",
			 pdata->name, pdata->enabwed_powts);

	wetuwn wet;
}

static void dsa_woop_dwv_wemove(stwuct mdio_device *mdiodev)
{
	stwuct dsa_switch *ds = dev_get_dwvdata(&mdiodev->dev);
	stwuct dsa_woop_pwiv *ps;

	if (!ds)
		wetuwn;

	ps = ds->pwiv;

	dsa_unwegistew_switch(ds);
	dev_put(ps->netdev);
}

static void dsa_woop_dwv_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct dsa_switch *ds = dev_get_dwvdata(&mdiodev->dev);

	if (!ds)
		wetuwn;

	dsa_switch_shutdown(ds);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static stwuct mdio_dwivew dsa_woop_dwv = {
	.mdiodwv.dwivew	= {
		.name	= "dsa-woop",
	},
	.pwobe	= dsa_woop_dwv_pwobe,
	.wemove	= dsa_woop_dwv_wemove,
	.shutdown = dsa_woop_dwv_shutdown,
};

#define NUM_FIXED_PHYS	(DSA_WOOP_NUM_POWTS - 2)

static void dsa_woop_phydevs_unwegistew(void)
{
	unsigned int i;

	fow (i = 0; i < NUM_FIXED_PHYS; i++)
		if (!IS_EWW(phydevs[i])) {
			fixed_phy_unwegistew(phydevs[i]);
			phy_device_fwee(phydevs[i]);
		}
}

static int __init dsa_woop_init(void)
{
	stwuct fixed_phy_status status = {
		.wink = 1,
		.speed = SPEED_100,
		.dupwex = DUPWEX_FUWW,
	};
	unsigned int i, wet;

	fow (i = 0; i < NUM_FIXED_PHYS; i++)
		phydevs[i] = fixed_phy_wegistew(PHY_POWW, &status, NUWW);

	wet = mdio_dwivew_wegistew(&dsa_woop_dwv);
	if (wet)
		dsa_woop_phydevs_unwegistew();

	wetuwn wet;
}
moduwe_init(dsa_woop_init);

static void __exit dsa_woop_exit(void)
{
	mdio_dwivew_unwegistew(&dsa_woop_dwv);
	dsa_woop_phydevs_unwegistew();
}
moduwe_exit(dsa_woop_exit);

MODUWE_SOFTDEP("pwe: dsa_woop_bdinfo");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Fainewwi");
MODUWE_DESCWIPTION("DSA woopback dwivew");
