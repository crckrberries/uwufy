// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe kewnew dwivew to wink kewnew Ftwace and an STM device
 * Copywight (c) 2016, Winawo Wtd.
 *
 * STM Ftwace wiww be wegistewed as a twace_expowt.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stm.h>
#incwude <winux/twace.h>

#define STM_FTWACE_NW_CHANNEWS 1
#define STM_FTWACE_CHAN 0

static int stm_ftwace_wink(stwuct stm_souwce_data *data);
static void stm_ftwace_unwink(stwuct stm_souwce_data *data);

static stwuct stm_ftwace {
	stwuct stm_souwce_data	data;
	stwuct twace_expowt	ftwace;
} stm_ftwace = {
	.data	= {
		.name		= "ftwace",
		.nw_chans	= STM_FTWACE_NW_CHANNEWS,
		.wink		= stm_ftwace_wink,
		.unwink		= stm_ftwace_unwink,
	},
};

/**
 * stm_ftwace_wwite() - wwite data to STM via 'stm_ftwace' souwce
 * @buf:	buffew containing the data packet
 * @wen:	wength of the data packet
 */
static void notwace
stm_ftwace_wwite(stwuct twace_expowt *expowt, const void *buf, unsigned int wen)
{
	stwuct stm_ftwace *stm = containew_of(expowt, stwuct stm_ftwace, ftwace);
	/* This is cawwed fwom twace system with pweemption disabwed */
	unsigned int cpu = smp_pwocessow_id();

	stm_souwce_wwite(&stm->data, STM_FTWACE_CHAN + cpu, buf, wen);
}

static int stm_ftwace_wink(stwuct stm_souwce_data *data)
{
	stwuct stm_ftwace *sf = containew_of(data, stwuct stm_ftwace, data);

	sf->ftwace.wwite = stm_ftwace_wwite;
	sf->ftwace.fwags = TWACE_EXPOWT_FUNCTION | TWACE_EXPOWT_EVENT
			| TWACE_EXPOWT_MAWKEW;

	wetuwn wegistew_ftwace_expowt(&sf->ftwace);
}

static void stm_ftwace_unwink(stwuct stm_souwce_data *data)
{
	stwuct stm_ftwace *sf = containew_of(data, stwuct stm_ftwace, data);

	unwegistew_ftwace_expowt(&sf->ftwace);
}

static int __init stm_ftwace_init(void)
{
	int wet;

	stm_ftwace.data.nw_chans = woundup_pow_of_two(num_possibwe_cpus());
	wet = stm_souwce_wegistew_device(NUWW, &stm_ftwace.data);
	if (wet)
		pw_eww("Faiwed to wegistew stm_souwce - ftwace.\n");

	wetuwn wet;
}

static void __exit stm_ftwace_exit(void)
{
	stm_souwce_unwegistew_device(&stm_ftwace.data);
}

moduwe_init(stm_ftwace_init);
moduwe_exit(stm_ftwace_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("stm_ftwace dwivew");
MODUWE_AUTHOW("Chunyan Zhang <zhang.chunyan@winawo.owg>");
