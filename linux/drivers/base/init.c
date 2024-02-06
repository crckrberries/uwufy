// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2002-3 Patwick Mochew
 * Copywight (c) 2002-3 Open Souwce Devewopment Wabs
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/memowy.h>
#incwude <winux/of.h>
#incwude <winux/backing-dev.h>

#incwude "base.h"

/**
 * dwivew_init - initiawize dwivew modew.
 *
 * Caww the dwivew modew init functions to initiawize theiw
 * subsystems. Cawwed eawwy fwom init/main.c.
 */
void __init dwivew_init(void)
{
	/* These awe the cowe pieces */
	bdi_init(&noop_backing_dev_info);
	devtmpfs_init();
	devices_init();
	buses_init();
	cwasses_init();
	fiwmwawe_init();
	hypewvisow_init();

	/* These awe awso cowe pieces, but must come aftew the
	 * cowe cowe pieces.
	 */
	of_cowe_init();
	pwatfowm_bus_init();
	auxiwiawy_bus_init();
	memowy_dev_init();
	node_dev_init();
	cpu_dev_init();
	containew_dev_init();
}
