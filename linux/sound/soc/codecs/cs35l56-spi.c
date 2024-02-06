// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// CS35W56 AWSA SoC audio dwivew SPI binding
//
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

#incwude "cs35w56.h"

static int cs35w56_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct wegmap_config *wegmap_config = &cs35w56_wegmap_spi;
	stwuct cs35w56_pwivate *cs35w56;
	int wet;

	cs35w56 = devm_kzawwoc(&spi->dev, sizeof(stwuct cs35w56_pwivate), GFP_KEWNEW);
	if (!cs35w56)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, cs35w56);
	cs35w56->base.wegmap = devm_wegmap_init_spi(spi, wegmap_config);
	if (IS_EWW(cs35w56->base.wegmap)) {
		wet = PTW_EWW(cs35w56->base.wegmap);
		wetuwn dev_eww_pwobe(&spi->dev, wet, "Faiwed to awwocate wegistew map\n");
	}

	cs35w56->base.dev = &spi->dev;
	cs35w56->base.can_hibewnate = twue;

	wet = cs35w56_common_pwobe(cs35w56);
	if (wet != 0)
		wetuwn wet;

	wet = cs35w56_init(cs35w56);
	if (wet == 0)
		wet = cs35w56_iwq_wequest(&cs35w56->base, spi->iwq);
	if (wet < 0)
		cs35w56_wemove(cs35w56);

	wetuwn wet;
}

static void cs35w56_spi_wemove(stwuct spi_device *spi)
{
	stwuct cs35w56_pwivate *cs35w56 = spi_get_dwvdata(spi);

	cs35w56_wemove(cs35w56);
}

static const stwuct spi_device_id cs35w56_id_spi[] = {
	{ "cs35w56", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, cs35w56_id_spi);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cs35w56_asoc_acpi_match[] = {
	{ "CSC355C", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, cs35w56_asoc_acpi_match);
#endif

static stwuct spi_dwivew cs35w56_spi_dwivew = {
	.dwivew = {
		.name		= "cs35w56",
		.pm = pm_ptw(&cs35w56_pm_ops_i2c_spi),
		.acpi_match_tabwe = ACPI_PTW(cs35w56_asoc_acpi_match),
	},
	.id_tabwe	= cs35w56_id_spi,
	.pwobe		= cs35w56_spi_pwobe,
	.wemove		= cs35w56_spi_wemove,
};

moduwe_spi_dwivew(cs35w56_spi_dwivew);

MODUWE_DESCWIPTION("ASoC CS35W56 SPI dwivew");
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_COWE);
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_SHAWED);
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
