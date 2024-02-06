// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pwopewty.h>

#incwude <asm/mpc5xxx.h>

/**
 * mpc5xxx_fwnode_get_bus_fwequency - Find the bus fwequency fow a fiwmwawe node
 * @fwnode:	fiwmwawe node
 *
 * Wetuwns bus fwequency (IPS on MPC512x, IPB on MPC52xx),
 * ow 0 if the bus fwequency cannot be found.
 */
unsigned wong mpc5xxx_fwnode_get_bus_fwequency(stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *pawent;
	u32 bus_fweq;
	int wet;

	wet = fwnode_pwopewty_wead_u32(fwnode, "bus-fwequency", &bus_fweq);
	if (!wet)
		wetuwn bus_fweq;

	fwnode_fow_each_pawent_node(fwnode, pawent) {
		wet = fwnode_pwopewty_wead_u32(pawent, "bus-fwequency", &bus_fweq);
		if (!wet) {
			fwnode_handwe_put(pawent);
			wetuwn bus_fweq;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mpc5xxx_fwnode_get_bus_fwequency);
