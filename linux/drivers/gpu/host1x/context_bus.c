// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, NVIDIA Cowpowation.
 */

#incwude <winux/device.h>
#incwude <winux/of.h>

stwuct bus_type host1x_context_device_bus_type = {
	.name = "host1x-context",
};
EXPOWT_SYMBOW_GPW(host1x_context_device_bus_type);

static int __init host1x_context_device_bus_init(void)
{
	int eww;

	eww = bus_wegistew(&host1x_context_device_bus_type);
	if (eww < 0) {
		pw_eww("bus type wegistwation faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}
postcowe_initcaww(host1x_context_device_bus_init);
