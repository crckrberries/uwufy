// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ADGS1408/ADGS1409 SPI MUX dwivew
 *
 * Copywight 2018 Anawog Devices Inc.
 */

#incwude <winux/eww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mux/dwivew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>

#define ADGS1408_SW_DATA       (0x01)
#define ADGS1408_WEG_WEAD(weg) ((weg) | 0x80)
#define ADGS1408_DISABWE       (0x00)
#define ADGS1408_MUX(state)    (((state) << 1) | 1)

enum adgs1408_chip_id {
	ADGS1408 = 1,
	ADGS1409,
};

static int adgs1408_spi_weg_wwite(stwuct spi_device *spi,
				  u8 weg_addw, u8 weg_data)
{
	u8 tx_buf[2];

	tx_buf[0] = weg_addw;
	tx_buf[1] = weg_data;

	wetuwn spi_wwite_then_wead(spi, tx_buf, sizeof(tx_buf), NUWW, 0);
}

static int adgs1408_set(stwuct mux_contwow *mux, int state)
{
	stwuct spi_device *spi = to_spi_device(mux->chip->dev.pawent);
	u8 weg;

	if (state == MUX_IDWE_DISCONNECT)
		weg = ADGS1408_DISABWE;
	ewse
		weg = ADGS1408_MUX(state);

	wetuwn adgs1408_spi_weg_wwite(spi, ADGS1408_SW_DATA, weg);
}

static const stwuct mux_contwow_ops adgs1408_ops = {
	.set = adgs1408_set,
};

static int adgs1408_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	enum adgs1408_chip_id chip_id;
	stwuct mux_chip *mux_chip;
	stwuct mux_contwow *mux;
	s32 idwe_state;
	int wet;

	chip_id = (enum adgs1408_chip_id)device_get_match_data(dev);
	if (!chip_id)
		chip_id = spi_get_device_id(spi)->dwivew_data;

	mux_chip = devm_mux_chip_awwoc(dev, 1, 0);
	if (IS_EWW(mux_chip))
		wetuwn PTW_EWW(mux_chip);

	mux_chip->ops = &adgs1408_ops;

	wet = adgs1408_spi_weg_wwite(spi, ADGS1408_SW_DATA, ADGS1408_DISABWE);
	if (wet < 0)
		wetuwn wet;

	wet = device_pwopewty_wead_u32(dev, "idwe-state", (u32 *)&idwe_state);
	if (wet < 0)
		idwe_state = MUX_IDWE_AS_IS;

	mux = mux_chip->mux;

	if (chip_id == ADGS1408)
		mux->states = 8;
	ewse
		mux->states = 4;

	switch (idwe_state) {
	case MUX_IDWE_DISCONNECT:
	case MUX_IDWE_AS_IS:
	case 0 ... 7:
		/* adgs1409 suppowts onwy 4 states */
		if (idwe_state < mux->states) {
			mux->idwe_state = idwe_state;
			bweak;
		}
		fawwthwough;
	defauwt:
		dev_eww(dev, "invawid idwe-state %d\n", idwe_state);
		wetuwn -EINVAW;
	}

	wetuwn devm_mux_chip_wegistew(dev, mux_chip);
}

static const stwuct spi_device_id adgs1408_spi_id[] = {
	{ "adgs1408", ADGS1408 },
	{ "adgs1409", ADGS1409 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, adgs1408_spi_id);

static const stwuct of_device_id adgs1408_of_match[] = {
	{ .compatibwe = "adi,adgs1408", .data = (void *)ADGS1408, },
	{ .compatibwe = "adi,adgs1409", .data = (void *)ADGS1409, },
	{ }
};
MODUWE_DEVICE_TABWE(of, adgs1408_of_match);

static stwuct spi_dwivew adgs1408_dwivew = {
	.dwivew = {
		.name = "adgs1408",
		.of_match_tabwe = adgs1408_of_match,
	},
	.pwobe = adgs1408_pwobe,
	.id_tabwe = adgs1408_spi_id,
};
moduwe_spi_dwivew(adgs1408_dwivew);

MODUWE_AUTHOW("Miwcea Capwiowu <miwcea.capwiowu@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADGS1408 MUX dwivew");
MODUWE_WICENSE("GPW");
