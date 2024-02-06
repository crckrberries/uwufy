// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/phy.h>
#incwude <net/dsa.h>

#incwude "dsa_woop.h"

static stwuct dsa_woop_pdata dsa_woop_pdata = {
	.cd = {
		.powt_names[0] = "wan1",
		.powt_names[1] = "wan2",
		.powt_names[2] = "wan3",
		.powt_names[3] = "wan4",
		.powt_names[DSA_WOOP_CPU_POWT] = "cpu",
	},
	.name = "DSA mockup dwivew",
	.enabwed_powts = 0x1f,
	.netdev = "eth0",
};

static const stwuct mdio_boawd_info bdinfo = {
	.bus_id	= "fixed-0",
	.modawias = "dsa-woop",
	.mdio_addw = 31,
	.pwatfowm_data = &dsa_woop_pdata,
};

static int __init dsa_woop_bdinfo_init(void)
{
	wetuwn mdiobus_wegistew_boawd_info(&bdinfo, 1);
}
awch_initcaww(dsa_woop_bdinfo_init)

MODUWE_WICENSE("GPW");
