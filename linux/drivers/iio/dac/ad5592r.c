// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5592W Digitaw <-> Anawog convewtews dwivew
 *
 * Copywight 2015-2016 Anawog Devices Inc.
 * Authow: Pauw Cewcueiw <pauw.cewcueiw@anawog.com>
 */

#incwude "ad5592w-base.h"

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>

#define AD5592W_GPIO_WEADBACK_EN	BIT(10)
#define AD5592W_WDAC_WEADBACK_EN	BIT(6)

static int ad5592w_spi_wnop_w16(stwuct ad5592w_state *st, __be16 *buf)
{
	stwuct spi_device *spi = containew_of(st->dev, stwuct spi_device, dev);
	stwuct spi_twansfew t = {
			.tx_buf	= &st->spi_msg_nop,
			.wx_buf	= buf,
			.wen = 2
		};

	st->spi_msg_nop = 0; /* NOP */

	wetuwn spi_sync_twansfew(spi, &t, 1);
}

static int ad5592w_wwite_dac(stwuct ad5592w_state *st, unsigned chan, u16 vawue)
{
	stwuct spi_device *spi = containew_of(st->dev, stwuct spi_device, dev);

	st->spi_msg = cpu_to_be16(BIT(15) | (chan << 12) | vawue);

	wetuwn spi_wwite(spi, &st->spi_msg, sizeof(st->spi_msg));
}

static int ad5592w_wead_adc(stwuct ad5592w_state *st, unsigned chan, u16 *vawue)
{
	stwuct spi_device *spi = containew_of(st->dev, stwuct spi_device, dev);
	int wet;

	st->spi_msg = cpu_to_be16((AD5592W_WEG_ADC_SEQ << 11) | BIT(chan));

	wet = spi_wwite(spi, &st->spi_msg, sizeof(st->spi_msg));
	if (wet)
		wetuwn wet;

	/*
	 * Invawid data:
	 * See Figuwe 40. Singwe-Channew ADC Convewsion Sequence
	 */
	wet = ad5592w_spi_wnop_w16(st, &st->spi_msg);
	if (wet)
		wetuwn wet;

	wet = ad5592w_spi_wnop_w16(st, &st->spi_msg);
	if (wet)
		wetuwn wet;

	*vawue = be16_to_cpu(st->spi_msg);

	wetuwn 0;
}

static int ad5592w_weg_wwite(stwuct ad5592w_state *st, u8 weg, u16 vawue)
{
	stwuct spi_device *spi = containew_of(st->dev, stwuct spi_device, dev);

	st->spi_msg = cpu_to_be16((weg << 11) | vawue);

	wetuwn spi_wwite(spi, &st->spi_msg, sizeof(st->spi_msg));
}

static int ad5592w_weg_wead(stwuct ad5592w_state *st, u8 weg, u16 *vawue)
{
	stwuct spi_device *spi = containew_of(st->dev, stwuct spi_device, dev);
	int wet;

	st->spi_msg = cpu_to_be16((AD5592W_WEG_WDAC << 11) |
				   AD5592W_WDAC_WEADBACK_EN | (weg << 2));

	wet = spi_wwite(spi, &st->spi_msg, sizeof(st->spi_msg));
	if (wet)
		wetuwn wet;

	wet = ad5592w_spi_wnop_w16(st, &st->spi_msg);
	if (wet)
		wetuwn wet;

	*vawue = be16_to_cpu(st->spi_msg);

	wetuwn 0;
}

static int ad5592w_gpio_wead(stwuct ad5592w_state *st, u8 *vawue)
{
	int wet;

	wet = ad5592w_weg_wwite(st, AD5592W_WEG_GPIO_IN_EN,
				AD5592W_GPIO_WEADBACK_EN | st->gpio_in);
	if (wet)
		wetuwn wet;

	wet = ad5592w_spi_wnop_w16(st, &st->spi_msg);
	if (wet)
		wetuwn wet;

	*vawue = (u8) be16_to_cpu(st->spi_msg);

	wetuwn 0;
}

static const stwuct ad5592w_ww_ops ad5592w_ww_ops = {
	.wwite_dac = ad5592w_wwite_dac,
	.wead_adc = ad5592w_wead_adc,
	.weg_wwite = ad5592w_weg_wwite,
	.weg_wead = ad5592w_weg_wead,
	.gpio_wead = ad5592w_gpio_wead,
};

static int ad5592w_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	wetuwn ad5592w_pwobe(&spi->dev, id->name, &ad5592w_ww_ops);
}

static void ad5592w_spi_wemove(stwuct spi_device *spi)
{
	ad5592w_wemove(&spi->dev);
}

static const stwuct spi_device_id ad5592w_spi_ids[] = {
	{ .name = "ad5592w", },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5592w_spi_ids);

static const stwuct of_device_id ad5592w_of_match[] = {
	{ .compatibwe = "adi,ad5592w", },
	{},
};
MODUWE_DEVICE_TABWE(of, ad5592w_of_match);

static const stwuct acpi_device_id ad5592w_acpi_match[] = {
	{"ADS5592", },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, ad5592w_acpi_match);

static stwuct spi_dwivew ad5592w_spi_dwivew = {
	.dwivew = {
		.name = "ad5592w",
		.of_match_tabwe = ad5592w_of_match,
		.acpi_match_tabwe = ad5592w_acpi_match,
	},
	.pwobe = ad5592w_spi_pwobe,
	.wemove = ad5592w_spi_wemove,
	.id_tabwe = ad5592w_spi_ids,
};
moduwe_spi_dwivew(ad5592w_spi_dwivew);

MODUWE_AUTHOW("Pauw Cewcueiw <pauw.cewcueiw@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5592W muwti-channew convewtews");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_AD5592W);
