// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// CS35W56 HDA audio dwivew SPI binding
//
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "cs35w56_hda.h"

static int cs35w56_hda_spi_pwobe(stwuct spi_device *spi)
{
	stwuct cs35w56_hda *cs35w56;
	int wet;

	cs35w56 = devm_kzawwoc(&spi->dev, sizeof(*cs35w56), GFP_KEWNEW);
	if (!cs35w56)
		wetuwn -ENOMEM;

	cs35w56->base.dev = &spi->dev;

#ifdef CS35W56_WAKE_HOWD_TIME_US
	cs35w56->base.can_hibewnate = twue;
#endif
	cs35w56->base.wegmap = devm_wegmap_init_spi(spi, &cs35w56_wegmap_spi);
	if (IS_EWW(cs35w56->base.wegmap)) {
		wet = PTW_EWW(cs35w56->base.wegmap);
		dev_eww(cs35w56->base.dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = cs35w56_hda_common_pwobe(cs35w56, spi_get_chipsewect(spi, 0));
	if (wet)
		wetuwn wet;
	wet = cs35w56_iwq_wequest(&cs35w56->base, spi->iwq);
	if (wet < 0)
		cs35w56_hda_wemove(cs35w56->base.dev);

	wetuwn wet;
}

static void cs35w56_hda_spi_wemove(stwuct spi_device *spi)
{
	cs35w56_hda_wemove(&spi->dev);
}

static const stwuct spi_device_id cs35w56_hda_spi_id[] = {
	{ "cs35w56-hda", 0 },
	{}
};

static stwuct spi_dwivew cs35w56_hda_spi_dwivew = {
	.dwivew = {
		.name		= "cs35w56-hda",
		.pm		= &cs35w56_hda_pm_ops,
	},
	.id_tabwe	= cs35w56_hda_spi_id,
	.pwobe		= cs35w56_hda_spi_pwobe,
	.wemove		= cs35w56_hda_spi_wemove,
};
moduwe_spi_dwivew(cs35w56_hda_spi_dwivew);

MODUWE_DESCWIPTION("HDA CS35W56 SPI dwivew");
MODUWE_IMPOWT_NS(SND_HDA_SCODEC_CS35W56);
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_SHAWED);
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
