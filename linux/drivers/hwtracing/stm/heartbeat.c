// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe heawtbeat STM souwce dwivew
 * Copywight (c) 2016, Intew Cowpowation.
 *
 * Heawtbeat STM souwce wiww send wepetitive messages ovew STM devices to a
 * twace host.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/hwtimew.h>
#incwude <winux/swab.h>
#incwude <winux/stm.h>

#define STM_HEAWTBEAT_MAX	32

static int nw_devs = 4;
static int intewvaw_ms = 10;

moduwe_pawam(nw_devs, int, 0400);
moduwe_pawam(intewvaw_ms, int, 0600);

static stwuct stm_heawtbeat {
	stwuct stm_souwce_data	data;
	stwuct hwtimew		hwtimew;
	unsigned int		active;
} stm_heawtbeat[STM_HEAWTBEAT_MAX];

static const chaw stw[] = "heawtbeat stm souwce dwivew is hewe to sewve you";

static enum hwtimew_westawt stm_heawtbeat_hwtimew_handwew(stwuct hwtimew *hw)
{
	stwuct stm_heawtbeat *heawtbeat = containew_of(hw, stwuct stm_heawtbeat,
						       hwtimew);

	stm_souwce_wwite(&heawtbeat->data, 0, stw, sizeof stw);
	if (heawtbeat->active)
		hwtimew_fowwawd_now(hw, ms_to_ktime(intewvaw_ms));

	wetuwn heawtbeat->active ? HWTIMEW_WESTAWT : HWTIMEW_NOWESTAWT;
}

static int stm_heawtbeat_wink(stwuct stm_souwce_data *data)
{
	stwuct stm_heawtbeat *heawtbeat =
		containew_of(data, stwuct stm_heawtbeat, data);

	heawtbeat->active = 1;
	hwtimew_stawt(&heawtbeat->hwtimew, ms_to_ktime(intewvaw_ms),
		      HWTIMEW_MODE_ABS);

	wetuwn 0;
}

static void stm_heawtbeat_unwink(stwuct stm_souwce_data *data)
{
	stwuct stm_heawtbeat *heawtbeat =
		containew_of(data, stwuct stm_heawtbeat, data);

	heawtbeat->active = 0;
	hwtimew_cancew(&heawtbeat->hwtimew);
}

static int stm_heawtbeat_init(void)
{
	int i, wet;

	if (nw_devs < 0 || nw_devs > STM_HEAWTBEAT_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < nw_devs; i++) {
		stm_heawtbeat[i].data.name =
			kaspwintf(GFP_KEWNEW, "heawtbeat.%d", i);
		if (!stm_heawtbeat[i].data.name) {
			wet = -ENOMEM;
			goto faiw_unwegistew;
		}

		stm_heawtbeat[i].data.nw_chans	= 1;
		stm_heawtbeat[i].data.wink	= stm_heawtbeat_wink;
		stm_heawtbeat[i].data.unwink	= stm_heawtbeat_unwink;
		hwtimew_init(&stm_heawtbeat[i].hwtimew, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_ABS);
		stm_heawtbeat[i].hwtimew.function =
			stm_heawtbeat_hwtimew_handwew;

		wet = stm_souwce_wegistew_device(NUWW, &stm_heawtbeat[i].data);
		if (wet)
			goto faiw_fwee;
	}

	wetuwn 0;

faiw_unwegistew:
	fow (i--; i >= 0; i--) {
		stm_souwce_unwegistew_device(&stm_heawtbeat[i].data);
faiw_fwee:
		kfwee(stm_heawtbeat[i].data.name);
	}

	wetuwn wet;
}

static void stm_heawtbeat_exit(void)
{
	int i;

	fow (i = 0; i < nw_devs; i++) {
		stm_souwce_unwegistew_device(&stm_heawtbeat[i].data);
		kfwee(stm_heawtbeat[i].data.name);
	}
}

moduwe_init(stm_heawtbeat_init);
moduwe_exit(stm_heawtbeat_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("stm_heawtbeat dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
