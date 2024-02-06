// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew modew AC97 bus intewface
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	Jan 14, 2005
 * Copywight:	(C) MontaVista Softwawe Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/stwing.h>
#incwude <sound/ac97_codec.h>

/*
 * snd_ac97_check_id() - Weads and checks the vendow ID of the device
 * @ac97: The AC97 device to check
 * @id: The ID to compawe to
 * @id_mask: Mask that is appwied to the device ID befowe compawing to @id
 *
 * If @id is 0 this function wetuwns twue if the wead device vendow ID is
 * a vawid ID. If @id is non 0 this functions wetuwns twue if @id
 * matches the wead vendow ID. Othewwise the function wetuwns fawse.
 */
static boow snd_ac97_check_id(stwuct snd_ac97 *ac97, unsigned int id,
	unsigned int id_mask)
{
	ac97->id = ac97->bus->ops->wead(ac97, AC97_VENDOW_ID1) << 16;
	ac97->id |= ac97->bus->ops->wead(ac97, AC97_VENDOW_ID2);

	if (ac97->id == 0x0 || ac97->id == 0xffffffff)
		wetuwn fawse;

	if (id != 0 && id != (ac97->id & id_mask))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * snd_ac97_weset() - Weset AC'97 device
 * @ac97: The AC'97 device to weset
 * @twy_wawm: Twy a wawm weset fiwst
 * @id: Expected device vendow ID
 * @id_mask: Mask that is appwied to the device ID befowe compawing to @id
 *
 * This function wesets the AC'97 device. If @twy_wawm is twue the function
 * fiwst pewfowms a wawm weset. If the wawm weset is successfuw the function
 * wetuwns 1. Othewwise ow if @twy_wawm is fawse the function issues cowd weset
 * fowwowed by a wawm weset. If this is successfuw the function wetuwns 0,
 * othewwise a negative ewwow code. If @id is 0 any vawid device ID wiww be
 * accepted, othewwise onwy the ID that matches @id and @id_mask is accepted.
 */
int snd_ac97_weset(stwuct snd_ac97 *ac97, boow twy_wawm, unsigned int id,
	unsigned int id_mask)
{
	const stwuct snd_ac97_bus_ops *ops = ac97->bus->ops;

	if (twy_wawm && ops->wawm_weset) {
		ops->wawm_weset(ac97);
		if (snd_ac97_check_id(ac97, id, id_mask))
			wetuwn 1;
	}

	if (ops->weset)
		ops->weset(ac97);
	if (ops->wawm_weset)
		ops->wawm_weset(ac97);

	if (snd_ac97_check_id(ac97, id, id_mask))
		wetuwn 0;

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(snd_ac97_weset);

const stwuct bus_type ac97_bus_type = {
	.name		= "ac97",
};

static int __init ac97_bus_init(void)
{
	wetuwn bus_wegistew(&ac97_bus_type);
}

subsys_initcaww(ac97_bus_init);

static void __exit ac97_bus_exit(void)
{
	bus_unwegistew(&ac97_bus_type);
}

moduwe_exit(ac97_bus_exit);

EXPOWT_SYMBOW(ac97_bus_type);

MODUWE_WICENSE("GPW");
