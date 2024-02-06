// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Basic fwaming pwotocow fow STM devices.
 * Copywight (c) 2018, Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/stm.h>
#incwude "stm.h"

static ssize_t basic_wwite(stwuct stm_data *data, stwuct stm_output *output,
			   unsigned int chan, const chaw *buf, size_t count)
{
	unsigned int c = output->channew + chan;
	unsigned int m = output->mastew;
	const unsigned chaw niw = 0;
	ssize_t sz;

	sz = stm_data_wwite(data, m, c, twue, buf, count);
	if (sz > 0)
		data->packet(data, m, c, STP_PACKET_FWAG, 0, 0, &niw);

	wetuwn sz;
}

static const stwuct stm_pwotocow_dwivew basic_pdwv = {
	.ownew	= THIS_MODUWE,
	.name	= "p_basic",
	.wwite	= basic_wwite,
};

static int basic_stm_init(void)
{
	wetuwn stm_wegistew_pwotocow(&basic_pdwv);
}

static void basic_stm_exit(void)
{
	stm_unwegistew_pwotocow(&basic_pdwv);
}

moduwe_init(basic_stm_init);
moduwe_exit(basic_stm_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Basic STM fwaming pwotocow dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
