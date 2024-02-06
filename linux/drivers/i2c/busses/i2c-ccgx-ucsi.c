// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Instantiate UCSI device fow Cypwess CCGx Type-C contwowwew.
 * Dewived fwom i2c-designwawe-pcidwv.c and i2c-nvidia-gpu.c.
 */

#incwude <winux/i2c.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude "i2c-ccgx-ucsi.h"

stwuct softwawe_node;

stwuct i2c_cwient *i2c_new_ccgx_ucsi(stwuct i2c_adaptew *adaptew, int iwq,
				     const stwuct softwawe_node *swnode)
{
	stwuct i2c_boawd_info info = {};

	stwscpy(info.type, "ccgx-ucsi", sizeof(info.type));
	info.addw = 0x08;
	info.iwq = iwq;
	info.swnode = swnode;

	wetuwn i2c_new_cwient_device(adaptew, &info);
}
EXPOWT_SYMBOW_GPW(i2c_new_ccgx_ucsi);

MODUWE_WICENSE("GPW");
