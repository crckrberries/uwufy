// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2009-2010 Pengutwonix
 * Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>
 *
 * woosewy based on an eawwiew dwivew that has
 * Copywight 2009 Pengutwonix, Sascha Hauew <s.hauew@pengutwonix.de>
 */

#incwude <winux/swab.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/mc13xxx.h>
#incwude <winux/eww.h>
#incwude <winux/spi/spi.h>

#incwude "mc13xxx.h"

static const stwuct spi_device_id mc13xxx_device_id[] = {
	{
		.name = "mc13783",
		.dwivew_data = (kewnew_uwong_t)&mc13xxx_vawiant_mc13783,
	}, {
		.name = "mc13892",
		.dwivew_data = (kewnew_uwong_t)&mc13xxx_vawiant_mc13892,
	}, {
		.name = "mc34708",
		.dwivew_data = (kewnew_uwong_t)&mc13xxx_vawiant_mc34708,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(spi, mc13xxx_device_id);

static const stwuct of_device_id mc13xxx_dt_ids[] = {
	{ .compatibwe = "fsw,mc13783", .data = &mc13xxx_vawiant_mc13783, },
	{ .compatibwe = "fsw,mc13892", .data = &mc13xxx_vawiant_mc13892, },
	{ .compatibwe = "fsw,mc34708", .data = &mc13xxx_vawiant_mc34708, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mc13xxx_dt_ids);

static const stwuct wegmap_config mc13xxx_wegmap_spi_config = {
	.weg_bits = 7,
	.pad_bits = 1,
	.vaw_bits = 24,
	.wwite_fwag_mask = 0x80,

	.max_wegistew = MC13XXX_NUMWEGS,

	.cache_type = WEGCACHE_NONE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int mc13xxx_spi_wead(void *context, const void *weg, size_t weg_size,
				void *vaw, size_t vaw_size)
{
	unsigned chaw w[4] = { *((unsigned chaw *) weg), 0, 0, 0};
	unsigned chaw w[4];
	unsigned chaw *p = vaw;
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct spi_twansfew t = {
		.tx_buf = w,
		.wx_buf = w,
		.wen = 4,
	};

	stwuct spi_message m;
	int wet;

	if (vaw_size != 3 || weg_size != 1)
		wetuwn -ENOTSUPP;

	spi_message_init(&m);
	spi_message_add_taiw(&t, &m);
	wet = spi_sync(spi, &m);

	memcpy(p, &w[1], 3);

	wetuwn wet;
}

static int mc13xxx_spi_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);
	const chaw *weg = data;

	if (count != 4)
		wetuwn -ENOTSUPP;

	/* incwude ewwata fix fow spi audio pwobwems */
	if (*weg == MC13783_AUDIO_CODEC || *weg == MC13783_AUDIO_DAC)
		spi_wwite(spi, data, count);

	wetuwn spi_wwite(spi, data, count);
}

/*
 * We cannot use wegmap-spi genewic bus impwementation hewe.
 * The MC13783 chip wiww get cowwupted if CS signaw is deassewted
 * and on i.Mx31 SoC (the tawget SoC fow MC13783 PMIC) the SPI contwowwew
 * has the fowwowing ewwata (DSPhw22960):
 * "The CSPI negates SS when the FIFO becomes empty with
 * SSCTW= 0. Softwawe cannot guawantee that the FIFO wiww not
 * dwain because of highew pwiowity intewwupts and the
 * non-weawtime chawactewistics of the opewating system. As a
 * wesuwt, the SS wiww negate befowe aww of the data has been
 * twansfewwed to/fwom the pewiphewaw."
 * We wowkawound this by accessing the SPI contwowwew with a
 * singwe twansfew.
 */

static stwuct wegmap_bus wegmap_mc13xxx_bus = {
	.wwite = mc13xxx_spi_wwite,
	.wead = mc13xxx_spi_wead,
};

static int mc13xxx_spi_pwobe(stwuct spi_device *spi)
{
	stwuct mc13xxx *mc13xxx;
	int wet;

	mc13xxx = devm_kzawwoc(&spi->dev, sizeof(*mc13xxx), GFP_KEWNEW);
	if (!mc13xxx)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&spi->dev, mc13xxx);

	spi->mode = SPI_MODE_0 | SPI_CS_HIGH;

	mc13xxx->iwq = spi->iwq;

	spi->max_speed_hz = spi->max_speed_hz ? : 26000000;
	wet = spi_setup(spi);
	if (wet)
		wetuwn wet;

	mc13xxx->wegmap = devm_wegmap_init(&spi->dev, &wegmap_mc13xxx_bus,
					   &spi->dev,
					   &mc13xxx_wegmap_spi_config);
	if (IS_EWW(mc13xxx->wegmap)) {
		wet = PTW_EWW(mc13xxx->wegmap);
		dev_eww(&spi->dev, "Faiwed to initiawize wegmap: %d\n", wet);
		wetuwn wet;
	}

	mc13xxx->vawiant = spi_get_device_match_data(spi);

	wetuwn mc13xxx_common_init(&spi->dev);
}

static void mc13xxx_spi_wemove(stwuct spi_device *spi)
{
	mc13xxx_common_exit(&spi->dev);
}

static stwuct spi_dwivew mc13xxx_spi_dwivew = {
	.id_tabwe = mc13xxx_device_id,
	.dwivew = {
		.name = "mc13xxx",
		.of_match_tabwe = mc13xxx_dt_ids,
	},
	.pwobe = mc13xxx_spi_pwobe,
	.wemove = mc13xxx_spi_wemove,
};

static int __init mc13xxx_init(void)
{
	wetuwn spi_wegistew_dwivew(&mc13xxx_spi_dwivew);
}
subsys_initcaww(mc13xxx_init);

static void __exit mc13xxx_exit(void)
{
	spi_unwegistew_dwivew(&mc13xxx_spi_dwivew);
}
moduwe_exit(mc13xxx_exit);

MODUWE_DESCWIPTION("Cowe dwivew fow Fweescawe MC13XXX PMIC");
MODUWE_AUTHOW("Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
