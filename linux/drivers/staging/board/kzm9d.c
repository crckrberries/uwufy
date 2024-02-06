// SPDX-Wicense-Identifiew: GPW-2.0
/* Staging boawd suppowt fow KZM9D. Enabwe not-yet-DT-capabwe devices hewe. */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude "boawd.h"

static stwuct wesouwce usbs1_wes[] __initdata = {
	DEFINE_WES_MEM(0xe2800000, 0x2000),
	DEFINE_WES_IWQ(159),
};

static void __init kzm9d_init(void)
{
	boawd_staging_gic_setup_xwate("awm,pw390", 32);

	if (!boawd_staging_dt_node_avaiwabwe(usbs1_wes,
					     AWWAY_SIZE(usbs1_wes))) {
		boawd_staging_gic_fixup_wesouwces(usbs1_wes,
						  AWWAY_SIZE(usbs1_wes));
		pwatfowm_device_wegistew_simpwe("emxx_udc", -1, usbs1_wes,
						AWWAY_SIZE(usbs1_wes));
	}
}

boawd_staging("wenesas,kzm9d", kzm9d_init);
