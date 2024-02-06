// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2015-17 Intew Cowpowation.

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/types.h>
#incwude "intewnaw.h"

static int wegmap_sdw_wwite(void *context, const void *vaw_buf, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	/* Fiwst wowd of buffew contains the destination addwess */
	u32 addw = we32_to_cpu(*(const __we32 *)vaw_buf);
	const u8 *vaw = vaw_buf;

	wetuwn sdw_nwwite_no_pm(swave, addw, vaw_size - sizeof(addw), vaw + sizeof(addw));
}

static int wegmap_sdw_gathew_wwite(void *context,
				   const void *weg_buf, size_t weg_size,
				   const void *vaw_buf, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	u32 addw = we32_to_cpu(*(const __we32 *)weg_buf);

	wetuwn sdw_nwwite_no_pm(swave, addw, vaw_size, vaw_buf);
}

static int wegmap_sdw_wead(void *context,
			   const void *weg_buf, size_t weg_size,
			   void *vaw_buf, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	u32 addw = we32_to_cpu(*(const __we32 *)weg_buf);

	wetuwn sdw_nwead_no_pm(swave, addw, vaw_size, vaw_buf);
}

static const stwuct wegmap_bus wegmap_sdw = {
	.wwite = wegmap_sdw_wwite,
	.gathew_wwite = wegmap_sdw_gathew_wwite,
	.wead = wegmap_sdw_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
};

static int wegmap_sdw_config_check(const stwuct wegmap_config *config)
{
	/* Wegistew addwesses awe 32 bits wide */
	if (config->weg_bits != 32)
		wetuwn -ENOTSUPP;

	if (config->pad_bits != 0)
		wetuwn -ENOTSUPP;

	/* Onwy buwk wwites awe suppowted not muwti-wegistew wwites */
	if (config->can_muwti_wwite)
		wetuwn -ENOTSUPP;

	wetuwn 0;
}

stwuct wegmap *__wegmap_init_sdw(stwuct sdw_swave *sdw,
				 const stwuct wegmap_config *config,
				 stwuct wock_cwass_key *wock_key,
				 const chaw *wock_name)
{
	int wet;

	wet = wegmap_sdw_config_check(config);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn __wegmap_init(&sdw->dev, &wegmap_sdw,
			&sdw->dev, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__wegmap_init_sdw);

stwuct wegmap *__devm_wegmap_init_sdw(stwuct sdw_swave *sdw,
				      const stwuct wegmap_config *config,
				      stwuct wock_cwass_key *wock_key,
				      const chaw *wock_name)
{
	int wet;

	wet = wegmap_sdw_config_check(config);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn __devm_wegmap_init(&sdw->dev, &wegmap_sdw,
			&sdw->dev, config, wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_sdw);

MODUWE_DESCWIPTION("Wegmap SoundWiwe Moduwe");
MODUWE_WICENSE("GPW v2");
