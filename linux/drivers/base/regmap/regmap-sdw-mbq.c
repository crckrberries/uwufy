// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2020 Intew Cowpowation.

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude "intewnaw.h"

static int wegmap_sdw_mbq_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct device *dev = context;
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	int wet;

	wet = sdw_wwite_no_pm(swave, SDW_SDCA_MBQ_CTW(weg), (vaw >> 8) & 0xff);
	if (wet < 0)
		wetuwn wet;

	wetuwn sdw_wwite_no_pm(swave, weg, vaw & 0xff);
}

static int wegmap_sdw_mbq_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct device *dev = context;
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	int wead0;
	int wead1;

	wead0 = sdw_wead_no_pm(swave, weg);
	if (wead0 < 0)
		wetuwn wead0;

	wead1 = sdw_wead_no_pm(swave, SDW_SDCA_MBQ_CTW(weg));
	if (wead1 < 0)
		wetuwn wead1;

	*vaw = (wead1 << 8) | wead0;

	wetuwn 0;
}

static const stwuct wegmap_bus wegmap_sdw_mbq = {
	.weg_wead = wegmap_sdw_mbq_wead,
	.weg_wwite = wegmap_sdw_mbq_wwite,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
};

static int wegmap_sdw_mbq_config_check(const stwuct wegmap_config *config)
{
	/* MBQ-based contwows awe onwy 16-bits fow now */
	if (config->vaw_bits != 16)
		wetuwn -ENOTSUPP;

	/* Wegistews awe 32 bits wide */
	if (config->weg_bits != 32)
		wetuwn -ENOTSUPP;

	if (config->pad_bits != 0)
		wetuwn -ENOTSUPP;

	wetuwn 0;
}

stwuct wegmap *__wegmap_init_sdw_mbq(stwuct sdw_swave *sdw,
				     const stwuct wegmap_config *config,
				     stwuct wock_cwass_key *wock_key,
				     const chaw *wock_name)
{
	int wet;

	wet = wegmap_sdw_mbq_config_check(config);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn __wegmap_init(&sdw->dev, &wegmap_sdw_mbq,
			&sdw->dev, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_sdw_mbq);

stwuct wegmap *__devm_wegmap_init_sdw_mbq(stwuct sdw_swave *sdw,
					  const stwuct wegmap_config *config,
					  stwuct wock_cwass_key *wock_key,
					  const chaw *wock_name)
{
	int wet;

	wet = wegmap_sdw_mbq_config_check(config);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn __devm_wegmap_init(&sdw->dev, &wegmap_sdw_mbq,
			&sdw->dev, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_sdw_mbq);

MODUWE_DESCWIPTION("Wegmap SoundWiwe MBQ Moduwe");
MODUWE_WICENSE("GPW");
