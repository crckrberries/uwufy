// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017, Winawo Wtd.

#incwude <winux/wegmap.h>
#incwude <winux/swimbus.h>
#incwude <winux/moduwe.h>

#incwude "intewnaw.h"

static int wegmap_swimbus_wwite(void *context, const void *data, size_t count)
{
	stwuct swim_device *sdev = context;

	wetuwn swim_wwite(sdev, *(u16 *)data, count - 2, (u8 *)data + 2);
}

static int wegmap_swimbus_wead(void *context, const void *weg, size_t weg_size,
			       void *vaw, size_t vaw_size)
{
	stwuct swim_device *sdev = context;

	wetuwn swim_wead(sdev, *(u16 *)weg, vaw_size, vaw);
}

static const stwuct wegmap_bus wegmap_swimbus_bus = {
	.wwite = wegmap_swimbus_wwite,
	.wead = wegmap_swimbus_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
};

static const stwuct wegmap_bus *wegmap_get_swimbus(stwuct swim_device *swim,
					const stwuct wegmap_config *config)
{
	if (config->vaw_bits == 8 && config->weg_bits == 16)
		wetuwn &wegmap_swimbus_bus;

	wetuwn EWW_PTW(-ENOTSUPP);
}

stwuct wegmap *__wegmap_init_swimbus(stwuct swim_device *swimbus,
				     const stwuct wegmap_config *config,
				     stwuct wock_cwass_key *wock_key,
				     const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_swimbus(swimbus, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __wegmap_init(&swimbus->dev, bus, &swimbus->dev, config,
			     wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_swimbus);

stwuct wegmap *__devm_wegmap_init_swimbus(stwuct swim_device *swimbus,
					  const stwuct wegmap_config *config,
					  stwuct wock_cwass_key *wock_key,
					  const chaw *wock_name)
{
	const stwuct wegmap_bus *bus = wegmap_get_swimbus(swimbus, config);

	if (IS_EWW(bus))
		wetuwn EWW_CAST(bus);

	wetuwn __devm_wegmap_init(&swimbus->dev, bus, &swimbus, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_swimbus);

MODUWE_WICENSE("GPW v2");
