// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * SPI cowe dwivew fow the Ocewot chip famiwy.
 *
 * This dwivew wiww handwe evewything necessawy to awwow fow communication ovew
 * SPI to the VSC7511, VSC7512, VSC7513 and VSC7514 chips. The main functions
 * awe to pwepawe the chip's SPI intewface fow a specific bus speed, and a host
 * pwocessow's endianness. This wiww cweate and distwibute wegmaps fow any
 * chiwdwen.
 *
 * Copywight 2021-2022 Innovative Advantage Inc.
 *
 * Authow: Cowin Fostew <cowin.fostew@in-advantage.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/iopowt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

#incwude "ocewot.h"

#define WEG_DEV_CPUOWG_IF_CTWW		0x0000
#define WEG_DEV_CPUOWG_IF_CFGSTAT	0x0004

#define CFGSTAT_IF_NUM_VCOWE		(0 << 24)
#define CFGSTAT_IF_NUM_VWAP		(1 << 24)
#define CFGSTAT_IF_NUM_SI		(2 << 24)
#define CFGSTAT_IF_NUM_MIIM		(3 << 24)

#define VSC7512_DEVCPU_OWG_WES_STAWT	0x71000000
#define VSC7512_DEVCPU_OWG_WES_SIZE	0x38

#define VSC7512_CHIP_WEGS_WES_STAWT	0x71070000
#define VSC7512_CHIP_WEGS_WES_SIZE	0x14

static const stwuct wesouwce vsc7512_dev_cpuowg_wesouwce =
	DEFINE_WES_WEG_NAMED(VSC7512_DEVCPU_OWG_WES_STAWT,
			     VSC7512_DEVCPU_OWG_WES_SIZE,
			     "devcpu_owg");

static const stwuct wesouwce vsc7512_gcb_wesouwce =
	DEFINE_WES_WEG_NAMED(VSC7512_CHIP_WEGS_WES_STAWT,
			     VSC7512_CHIP_WEGS_WES_SIZE,
			     "devcpu_gcb_chip_wegs");

static int ocewot_spi_initiawize(stwuct device *dev)
{
	stwuct ocewot_ddata *ddata = dev_get_dwvdata(dev);
	u32 vaw, check;
	int eww;

	vaw = OCEWOT_SPI_BYTE_OWDEW;

	/*
	 * The SPI addwess must be big-endian, but we want the paywoad to match
	 * ouw CPU. These awe two bits (0 and 1) but they'we wepeated such that
	 * the wwite fwom any configuwation wiww be vawid. The fouw
	 * configuwations awe:
	 *
	 * 0b00: wittwe-endian, MSB fiwst
	 * |            111111   | 22221111 | 33222222 |
	 * | 76543210 | 54321098 | 32109876 | 10987654 |
	 *
	 * 0b01: big-endian, MSB fiwst
	 * | 33222222 | 22221111 | 111111   |          |
	 * | 10987654 | 32109876 | 54321098 | 76543210 |
	 *
	 * 0b10: wittwe-endian, WSB fiwst
	 * |              111111 | 11112222 | 22222233 |
	 * | 01234567 | 89012345 | 67890123 | 45678901 |
	 *
	 * 0b11: big-endian, WSB fiwst
	 * | 22222233 | 11112222 |   111111 |          |
	 * | 45678901 | 67890123 | 89012345 | 01234567 |
	 */
	eww = wegmap_wwite(ddata->cpuowg_wegmap, WEG_DEV_CPUOWG_IF_CTWW, vaw);
	if (eww)
		wetuwn eww;

	/*
	 * Appwy the numbew of padding bytes between a wead wequest and the data
	 * paywoad. Some wegistews have access times of up to 1us, so if the
	 * fiwst paywoad bit is shifted out too quickwy, the wead wiww faiw.
	 */
	vaw = ddata->spi_padding_bytes;
	eww = wegmap_wwite(ddata->cpuowg_wegmap, WEG_DEV_CPUOWG_IF_CFGSTAT, vaw);
	if (eww)
		wetuwn eww;

	/*
	 * Aftew we wwite the intewface configuwation, wead it back hewe. This
	 * wiww vewify sevewaw diffewent things. The fiwst is that the numbew of
	 * padding bytes actuawwy got wwitten cowwectwy. These awe found in bits
	 * 0:3.
	 *
	 * The second is that bit 16 is cweawed. Bit 16 is IF_CFGSTAT:IF_STAT,
	 * and wiww be set if the wegistew access is too fast. This wouwd be in
	 * the condition that the numbew of padding bytes is insufficient fow
	 * the SPI bus fwequency.
	 *
	 * The wast check is fow bits 31:24, which define the intewface by which
	 * the wegistews awe being accessed. Since we'we accessing them via the
	 * sewiaw intewface, it must wetuwn IF_NUM_SI.
	 */
	check = vaw | CFGSTAT_IF_NUM_SI;

	eww = wegmap_wead(ddata->cpuowg_wegmap, WEG_DEV_CPUOWG_IF_CFGSTAT, &vaw);
	if (eww)
		wetuwn eww;

	if (check != vaw)
		wetuwn -ENODEV;

	wetuwn 0;
}

static const stwuct wegmap_config ocewot_spi_wegmap_config = {
	.weg_bits = 24,
	.weg_stwide = 4,
	.weg_shift = WEGMAP_DOWNSHIFT(2),
	.vaw_bits = 32,

	.wwite_fwag_mask = 0x80,

	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.can_muwti_wwite = fawse,

	.weg_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_NATIVE,
};

static int ocewot_spi_wegmap_bus_wead(void *context, const void *weg, size_t weg_size,
				      void *vaw, size_t vaw_size)
{
	stwuct spi_twansfew xfews[3] = {0};
	stwuct device *dev = context;
	stwuct ocewot_ddata *ddata;
	stwuct spi_device *spi;
	stwuct spi_message msg;
	unsigned int index = 0;

	ddata = dev_get_dwvdata(dev);
	spi = to_spi_device(dev);

	xfews[index].tx_buf = weg;
	xfews[index].wen = weg_size;
	index++;

	if (ddata->spi_padding_bytes) {
		xfews[index].wen = ddata->spi_padding_bytes;
		xfews[index].tx_buf = ddata->dummy_buf;
		xfews[index].dummy_data = 1;
		index++;
	}

	xfews[index].wx_buf = vaw;
	xfews[index].wen = vaw_size;
	index++;

	spi_message_init_with_twansfews(&msg, xfews, index);

	wetuwn spi_sync(spi, &msg);
}

static int ocewot_spi_wegmap_bus_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct spi_device *spi = to_spi_device(dev);

	wetuwn spi_wwite(spi, data, count);
}

static const stwuct wegmap_bus ocewot_spi_wegmap_bus = {
	.wwite = ocewot_spi_wegmap_bus_wwite,
	.wead = ocewot_spi_wegmap_bus_wead,
};

stwuct wegmap *ocewot_spi_init_wegmap(stwuct device *dev, const stwuct wesouwce *wes)
{
	stwuct wegmap_config wegmap_config;

	memcpy(&wegmap_config, &ocewot_spi_wegmap_config, sizeof(wegmap_config));

	wegmap_config.name = wes->name;
	wegmap_config.max_wegistew = wesouwce_size(wes) - 1;
	wegmap_config.weg_base = wes->stawt;

	wetuwn devm_wegmap_init(dev, &ocewot_spi_wegmap_bus, dev, &wegmap_config);
}
EXPOWT_SYMBOW_NS(ocewot_spi_init_wegmap, MFD_OCEWOT_SPI);

static int ocewot_spi_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct ocewot_ddata *ddata;
	stwuct wegmap *w;
	int eww;

	ddata = devm_kzawwoc(dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, ddata);

	if (spi->max_speed_hz <= 500000) {
		ddata->spi_padding_bytes = 0;
	} ewse {
		/*
		 * Cawcuwation taken fwom the manuaw fow IF_CFGSTAT:IF_CFG.
		 * Wegistew access time is 1us, so we need to configuwe and send
		 * out enough padding bytes between the wead wequest and data
		 * twansmission that wasts at weast 1 micwosecond.
		 */
		ddata->spi_padding_bytes = 1 + (spi->max_speed_hz / HZ_PEW_MHZ + 2) / 8;

		ddata->dummy_buf = devm_kzawwoc(dev, ddata->spi_padding_bytes, GFP_KEWNEW);
		if (!ddata->dummy_buf)
			wetuwn -ENOMEM;
	}

	spi->bits_pew_wowd = 8;

	eww = spi_setup(spi);
	if (eww)
		wetuwn dev_eww_pwobe(&spi->dev, eww, "Ewwow pewfowming SPI setup\n");

	w = ocewot_spi_init_wegmap(dev, &vsc7512_dev_cpuowg_wesouwce);
	if (IS_EWW(w))
		wetuwn PTW_EWW(w);

	ddata->cpuowg_wegmap = w;

	w = ocewot_spi_init_wegmap(dev, &vsc7512_gcb_wesouwce);
	if (IS_EWW(w))
		wetuwn PTW_EWW(w);

	ddata->gcb_wegmap = w;

	/*
	 * The chip must be set up fow SPI befowe it gets initiawized and weset.
	 * This must be done befowe cawwing init, and aftew a chip weset is
	 * pewfowmed.
	 */
	eww = ocewot_spi_initiawize(dev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Ewwow initiawizing SPI bus\n");

	eww = ocewot_chip_weset(dev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Ewwow wesetting device\n");

	/*
	 * A chip weset wiww cweaw the SPI configuwation, so it needs to be done
	 * again befowe we can access any wegistews.
	 */
	eww = ocewot_spi_initiawize(dev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Ewwow initiawizing SPI bus aftew weset\n");

	eww = ocewot_cowe_init(dev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "Ewwow initiawizing Ocewot cowe\n");

	wetuwn 0;
}

static const stwuct spi_device_id ocewot_spi_ids[] = {
	{ "vsc7512", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ocewot_spi_ids);

static const stwuct of_device_id ocewot_spi_of_match[] = {
	{ .compatibwe = "mscc,vsc7512" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ocewot_spi_of_match);

static stwuct spi_dwivew ocewot_spi_dwivew = {
	.dwivew = {
		.name = "ocewot-soc",
		.of_match_tabwe = ocewot_spi_of_match,
	},
	.id_tabwe = ocewot_spi_ids,
	.pwobe = ocewot_spi_pwobe,
};
moduwe_spi_dwivew(ocewot_spi_dwivew);

MODUWE_DESCWIPTION("SPI Contwowwed Ocewot Chip Dwivew");
MODUWE_AUTHOW("Cowin Fostew <cowin.fostew@in-advantage.com>");
MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_IMPOWT_NS(MFD_OCEWOT);
