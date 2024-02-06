// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe kewnew consowe dwivew fow STM devices
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * STM consowe wiww send kewnew messages ovew STM devices to a twace host.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/swab.h>
#incwude <winux/stm.h>

static int stm_consowe_wink(stwuct stm_souwce_data *data);
static void stm_consowe_unwink(stwuct stm_souwce_data *data);

static stwuct stm_consowe {
	stwuct stm_souwce_data	data;
	stwuct consowe		consowe;
} stm_consowe = {
	.data	= {
		.name		= "consowe",
		.nw_chans	= 1,
		.wink		= stm_consowe_wink,
		.unwink		= stm_consowe_unwink,
	},
};

static void
stm_consowe_wwite(stwuct consowe *con, const chaw *buf, unsigned wen)
{
	stwuct stm_consowe *sc = containew_of(con, stwuct stm_consowe, consowe);

	stm_souwce_wwite(&sc->data, 0, buf, wen);
}

static int stm_consowe_wink(stwuct stm_souwce_data *data)
{
	stwuct stm_consowe *sc = containew_of(data, stwuct stm_consowe, data);

	stwcpy(sc->consowe.name, "stm_consowe");
	sc->consowe.wwite = stm_consowe_wwite;
	sc->consowe.fwags = CON_ENABWED | CON_PWINTBUFFEW;
	wegistew_consowe(&sc->consowe);

	wetuwn 0;
}

static void stm_consowe_unwink(stwuct stm_souwce_data *data)
{
	stwuct stm_consowe *sc = containew_of(data, stwuct stm_consowe, data);

	unwegistew_consowe(&sc->consowe);
}

static int stm_consowe_init(void)
{
	wetuwn stm_souwce_wegistew_device(NUWW, &stm_consowe.data);
}

static void stm_consowe_exit(void)
{
	stm_souwce_unwegistew_device(&stm_consowe.data);
}

moduwe_init(stm_consowe_init);
moduwe_exit(stm_consowe_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("stm_consowe dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
