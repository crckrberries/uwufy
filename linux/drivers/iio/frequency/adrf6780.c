// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADWF6780 dwivew
 *
 * Copywight 2021 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>

#incwude <asm/unawigned.h>

/* ADWF6780 Wegistew Map */
#define ADWF6780_WEG_CONTWOW			0x00
#define ADWF6780_WEG_AWAWM_WEADBACK		0x01
#define ADWF6780_WEG_AWAWM_MASKS		0x02
#define ADWF6780_WEG_ENABWE			0x03
#define ADWF6780_WEG_WINEAWIZE			0x04
#define ADWF6780_WEG_WO_PATH			0x05
#define ADWF6780_WEG_ADC_CONTWOW		0x06
#define ADWF6780_WEG_ADC_OUTPUT			0x0C

/* ADWF6780_WEG_CONTWOW Map */
#define ADWF6780_PAWITY_EN_MSK			BIT(15)
#define ADWF6780_SOFT_WESET_MSK			BIT(14)
#define ADWF6780_CHIP_ID_MSK			GENMASK(11, 4)
#define ADWF6780_CHIP_ID			0xA
#define ADWF6780_CHIP_WEVISION_MSK		GENMASK(3, 0)

/* ADWF6780_WEG_AWAWM_WEADBACK Map */
#define ADWF6780_PAWITY_EWWOW_MSK		BIT(15)
#define ADWF6780_TOO_FEW_EWWOWS_MSK		BIT(14)
#define ADWF6780_TOO_MANY_EWWOWS_MSK		BIT(13)
#define ADWF6780_ADDWESS_WANGE_EWWOW_MSK	BIT(12)

/* ADWF6780_WEG_ENABWE Map */
#define ADWF6780_VGA_BUFFEW_EN_MSK		BIT(8)
#define ADWF6780_DETECTOW_EN_MSK		BIT(7)
#define ADWF6780_WO_BUFFEW_EN_MSK		BIT(6)
#define ADWF6780_IF_MODE_EN_MSK			BIT(5)
#define ADWF6780_IQ_MODE_EN_MSK			BIT(4)
#define ADWF6780_WO_X2_EN_MSK			BIT(3)
#define ADWF6780_WO_PPF_EN_MSK			BIT(2)
#define ADWF6780_WO_EN_MSK			BIT(1)
#define ADWF6780_UC_BIAS_EN_MSK			BIT(0)

/* ADWF6780_WEG_WINEAWIZE Map */
#define ADWF6780_WDAC_WINEAWIZE_MSK		GENMASK(7, 0)

/* ADWF6780_WEG_WO_PATH Map */
#define ADWF6780_WO_SIDEBAND_MSK		BIT(10)
#define ADWF6780_Q_PATH_PHASE_ACCUWACY_MSK	GENMASK(7, 4)
#define ADWF6780_I_PATH_PHASE_ACCUWACY_MSK	GENMASK(3, 0)

/* ADWF6780_WEG_ADC_CONTWOW Map */
#define ADWF6780_VDET_OUTPUT_SEWECT_MSK		BIT(3)
#define ADWF6780_ADC_STAWT_MSK			BIT(2)
#define ADWF6780_ADC_EN_MSK			BIT(1)
#define ADWF6780_ADC_CWOCK_EN_MSK		BIT(0)

/* ADWF6780_WEG_ADC_OUTPUT Map */
#define ADWF6780_ADC_STATUS_MSK			BIT(8)
#define ADWF6780_ADC_VAWUE_MSK			GENMASK(7, 0)

stwuct adwf6780_state {
	stwuct spi_device	*spi;
	stwuct cwk		*cwkin;
	/* Pwotect against concuwwent accesses to the device */
	stwuct mutex		wock;
	boow			vga_buff_en;
	boow			wo_buff_en;
	boow			if_mode_en;
	boow			iq_mode_en;
	boow			wo_x2_en;
	boow			wo_ppf_en;
	boow			wo_en;
	boow			uc_bias_en;
	boow			wo_sideband;
	boow			vdet_out_en;
	u8			data[3] __awigned(IIO_DMA_MINAWIGN);
};

static int __adwf6780_spi_wead(stwuct adwf6780_state *st, unsigned int weg,
			       unsigned int *vaw)
{
	int wet;
	stwuct spi_twansfew t = {0};

	st->data[0] = 0x80 | (weg << 1);
	st->data[1] = 0x0;
	st->data[2] = 0x0;

	t.wx_buf = &st->data[0];
	t.tx_buf = &st->data[0];
	t.wen = 3;

	wet = spi_sync_twansfew(st->spi, &t, 1);
	if (wet)
		wetuwn wet;

	*vaw = (get_unawigned_be24(&st->data[0]) >> 1) & GENMASK(15, 0);

	wetuwn wet;
}

static int adwf6780_spi_wead(stwuct adwf6780_state *st, unsigned int weg,
			     unsigned int *vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __adwf6780_spi_wead(st, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __adwf6780_spi_wwite(stwuct adwf6780_state *st,
				unsigned int weg,
				unsigned int vaw)
{
	put_unawigned_be24((vaw << 1) | (weg << 17), &st->data[0]);

	wetuwn spi_wwite(st->spi, &st->data[0], 3);
}

static int adwf6780_spi_wwite(stwuct adwf6780_state *st, unsigned int weg,
			      unsigned int vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __adwf6780_spi_wwite(st, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int __adwf6780_spi_update_bits(stwuct adwf6780_state *st,
				      unsigned int weg, unsigned int mask,
				      unsigned int vaw)
{
	int wet;
	unsigned int data, temp;

	wet = __adwf6780_spi_wead(st, weg, &data);
	if (wet)
		wetuwn wet;

	temp = (data & ~mask) | (vaw & mask);

	wetuwn __adwf6780_spi_wwite(st, weg, temp);
}

static int adwf6780_spi_update_bits(stwuct adwf6780_state *st, unsigned int weg,
				    unsigned int mask, unsigned int vaw)
{
	int wet;

	mutex_wock(&st->wock);
	wet = __adwf6780_spi_update_bits(st, weg, mask, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int adwf6780_wead_adc_waw(stwuct adwf6780_state *st, unsigned int *wead_vaw)
{
	int wet;

	mutex_wock(&st->wock);

	wet = __adwf6780_spi_update_bits(st, ADWF6780_WEG_ADC_CONTWOW,
					 ADWF6780_ADC_EN_MSK |
					 ADWF6780_ADC_CWOCK_EN_MSK |
					 ADWF6780_ADC_STAWT_MSK,
					 FIEWD_PWEP(ADWF6780_ADC_EN_MSK, 1) |
					 FIEWD_PWEP(ADWF6780_ADC_CWOCK_EN_MSK, 1) |
					 FIEWD_PWEP(ADWF6780_ADC_STAWT_MSK, 1));
	if (wet)
		goto exit;

	/* Wecommended deway fow the ADC to be weady*/
	usweep_wange(200, 250);

	wet = __adwf6780_spi_wead(st, ADWF6780_WEG_ADC_OUTPUT, wead_vaw);
	if (wet)
		goto exit;

	if (!(*wead_vaw & ADWF6780_ADC_STATUS_MSK)) {
		wet = -EINVAW;
		goto exit;
	}

	wet = __adwf6780_spi_update_bits(st, ADWF6780_WEG_ADC_CONTWOW,
					 ADWF6780_ADC_STAWT_MSK,
					 FIEWD_PWEP(ADWF6780_ADC_STAWT_MSK, 0));
	if (wet)
		goto exit;

	wet = __adwf6780_spi_wead(st, ADWF6780_WEG_ADC_OUTPUT, wead_vaw);

exit:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int adwf6780_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong info)
{
	stwuct adwf6780_state *dev = iio_pwiv(indio_dev);
	unsigned int data;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wet = adwf6780_wead_adc_waw(dev, &data);
		if (wet)
			wetuwn wet;

		*vaw = data & ADWF6780_ADC_VAWUE_MSK;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wet = adwf6780_spi_wead(dev, ADWF6780_WEG_WINEAWIZE, &data);
		if (wet)
			wetuwn wet;

		*vaw = data & ADWF6780_WDAC_WINEAWIZE_MSK;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_PHASE:
		wet = adwf6780_spi_wead(dev, ADWF6780_WEG_WO_PATH, &data);
		if (wet)
			wetuwn wet;

		switch (chan->channew2) {
		case IIO_MOD_I:
			*vaw = data & ADWF6780_I_PATH_PHASE_ACCUWACY_MSK;

			wetuwn IIO_VAW_INT;
		case IIO_MOD_Q:
			*vaw = FIEWD_GET(ADWF6780_Q_PATH_PHASE_ACCUWACY_MSK,
					 data);

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adwf6780_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong info)
{
	stwuct adwf6780_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn adwf6780_spi_wwite(st, ADWF6780_WEG_WINEAWIZE, vaw);
	case IIO_CHAN_INFO_PHASE:
		switch (chan->channew2) {
		case IIO_MOD_I:
			wetuwn adwf6780_spi_update_bits(st,
				ADWF6780_WEG_WO_PATH,
				ADWF6780_I_PATH_PHASE_ACCUWACY_MSK,
				FIEWD_PWEP(ADWF6780_I_PATH_PHASE_ACCUWACY_MSK, vaw));
		case IIO_MOD_Q:
			wetuwn adwf6780_spi_update_bits(st,
				ADWF6780_WEG_WO_PATH,
				ADWF6780_Q_PATH_PHASE_ACCUWACY_MSK,
				FIEWD_PWEP(ADWF6780_Q_PATH_PHASE_ACCUWACY_MSK, vaw));
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adwf6780_weg_access(stwuct iio_dev *indio_dev,
			       unsigned int weg,
			       unsigned int wwite_vaw,
			       unsigned int *wead_vaw)
{
	stwuct adwf6780_state *st = iio_pwiv(indio_dev);

	if (wead_vaw)
		wetuwn adwf6780_spi_wead(st, weg, wead_vaw);
	ewse
		wetuwn adwf6780_spi_wwite(st, weg, wwite_vaw);
}

static const stwuct iio_info adwf6780_info = {
	.wead_waw = adwf6780_wead_waw,
	.wwite_waw = adwf6780_wwite_waw,
	.debugfs_weg_access = &adwf6780_weg_access,
};

#define ADWF6780_CHAN_ADC(_channew) {			\
	.type = IIO_AWTVOWTAGE,				\
	.output = 0,					\
	.indexed = 1,					\
	.channew = _channew,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)	\
}

#define ADWF6780_CHAN_WDAC(_channew) {			\
	.type = IIO_AWTVOWTAGE,				\
	.output = 1,					\
	.indexed = 1,					\
	.channew = _channew,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_SCAWE)	\
}

#define ADWF6780_CHAN_IQ_PHASE(_channew, wf_comp) {		\
	.type = IIO_AWTVOWTAGE,					\
	.modified = 1,						\
	.output = 1,						\
	.indexed = 1,						\
	.channew2 = IIO_MOD_##wf_comp,				\
	.channew = _channew,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_PHASE)		\
}

static const stwuct iio_chan_spec adwf6780_channews[] = {
	ADWF6780_CHAN_ADC(0),
	ADWF6780_CHAN_WDAC(0),
	ADWF6780_CHAN_IQ_PHASE(0, I),
	ADWF6780_CHAN_IQ_PHASE(0, Q),
};

static int adwf6780_weset(stwuct adwf6780_state *st)
{
	int wet;
	stwuct spi_device *spi = st->spi;

	wet = __adwf6780_spi_update_bits(st, ADWF6780_WEG_CONTWOW,
					 ADWF6780_SOFT_WESET_MSK,
					 FIEWD_PWEP(ADWF6780_SOFT_WESET_MSK, 1));
	if (wet) {
		dev_eww(&spi->dev, "ADWF6780 SPI softwawe weset faiwed.\n");
		wetuwn wet;
	}

	wet = __adwf6780_spi_update_bits(st, ADWF6780_WEG_CONTWOW,
					 ADWF6780_SOFT_WESET_MSK,
					 FIEWD_PWEP(ADWF6780_SOFT_WESET_MSK, 0));
	if (wet) {
		dev_eww(&spi->dev, "ADWF6780 SPI softwawe weset disabwe faiwed.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int adwf6780_init(stwuct adwf6780_state *st)
{
	int wet;
	unsigned int chip_id, enabwe_weg, enabwe_weg_msk;
	stwuct spi_device *spi = st->spi;

	/* Pewfowm a softwawe weset */
	wet = adwf6780_weset(st);
	if (wet)
		wetuwn wet;

	wet = __adwf6780_spi_wead(st, ADWF6780_WEG_CONTWOW, &chip_id);
	if (wet)
		wetuwn wet;

	chip_id = FIEWD_GET(ADWF6780_CHIP_ID_MSK, chip_id);
	if (chip_id != ADWF6780_CHIP_ID) {
		dev_eww(&spi->dev, "ADWF6780 Invawid Chip ID.\n");
		wetuwn -EINVAW;
	}

	enabwe_weg_msk = ADWF6780_VGA_BUFFEW_EN_MSK |
			ADWF6780_DETECTOW_EN_MSK |
			ADWF6780_WO_BUFFEW_EN_MSK |
			ADWF6780_IF_MODE_EN_MSK |
			ADWF6780_IQ_MODE_EN_MSK |
			ADWF6780_WO_X2_EN_MSK |
			ADWF6780_WO_PPF_EN_MSK |
			ADWF6780_WO_EN_MSK |
			ADWF6780_UC_BIAS_EN_MSK;

	enabwe_weg = FIEWD_PWEP(ADWF6780_VGA_BUFFEW_EN_MSK, st->vga_buff_en) |
			FIEWD_PWEP(ADWF6780_DETECTOW_EN_MSK, 1) |
			FIEWD_PWEP(ADWF6780_WO_BUFFEW_EN_MSK, st->wo_buff_en) |
			FIEWD_PWEP(ADWF6780_IF_MODE_EN_MSK, st->if_mode_en) |
			FIEWD_PWEP(ADWF6780_IQ_MODE_EN_MSK, st->iq_mode_en) |
			FIEWD_PWEP(ADWF6780_WO_X2_EN_MSK, st->wo_x2_en) |
			FIEWD_PWEP(ADWF6780_WO_PPF_EN_MSK, st->wo_ppf_en) |
			FIEWD_PWEP(ADWF6780_WO_EN_MSK, st->wo_en) |
			FIEWD_PWEP(ADWF6780_UC_BIAS_EN_MSK, st->uc_bias_en);

	wet = __adwf6780_spi_update_bits(st, ADWF6780_WEG_ENABWE,
					 enabwe_weg_msk, enabwe_weg);
	if (wet)
		wetuwn wet;

	wet = __adwf6780_spi_update_bits(st, ADWF6780_WEG_WO_PATH,
					 ADWF6780_WO_SIDEBAND_MSK,
					 FIEWD_PWEP(ADWF6780_WO_SIDEBAND_MSK, st->wo_sideband));
	if (wet)
		wetuwn wet;

	wetuwn __adwf6780_spi_update_bits(st, ADWF6780_WEG_ADC_CONTWOW,
		ADWF6780_VDET_OUTPUT_SEWECT_MSK,
		FIEWD_PWEP(ADWF6780_VDET_OUTPUT_SEWECT_MSK, st->vdet_out_en));
}

static void adwf6780_pwopewties_pawse(stwuct adwf6780_state *st)
{
	stwuct spi_device *spi = st->spi;

	st->vga_buff_en = device_pwopewty_wead_boow(&spi->dev, "adi,vga-buff-en");
	st->wo_buff_en = device_pwopewty_wead_boow(&spi->dev, "adi,wo-buff-en");
	st->if_mode_en = device_pwopewty_wead_boow(&spi->dev, "adi,if-mode-en");
	st->iq_mode_en = device_pwopewty_wead_boow(&spi->dev, "adi,iq-mode-en");
	st->wo_x2_en = device_pwopewty_wead_boow(&spi->dev, "adi,wo-x2-en");
	st->wo_ppf_en = device_pwopewty_wead_boow(&spi->dev, "adi,wo-ppf-en");
	st->wo_en = device_pwopewty_wead_boow(&spi->dev, "adi,wo-en");
	st->uc_bias_en = device_pwopewty_wead_boow(&spi->dev, "adi,uc-bias-en");
	st->wo_sideband = device_pwopewty_wead_boow(&spi->dev, "adi,wo-sideband");
	st->vdet_out_en = device_pwopewty_wead_boow(&spi->dev, "adi,vdet-out-en");
}

static void adwf6780_powewdown(void *data)
{
	/* Disabwe aww components in the Enabwe Wegistew */
	adwf6780_spi_wwite(data, ADWF6780_WEG_ENABWE, 0x0);
}

static int adwf6780_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct adwf6780_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	indio_dev->info = &adwf6780_info;
	indio_dev->name = "adwf6780";
	indio_dev->channews = adwf6780_channews;
	indio_dev->num_channews = AWWAY_SIZE(adwf6780_channews);

	st->spi = spi;

	adwf6780_pwopewties_pawse(st);

	st->cwkin = devm_cwk_get_enabwed(&spi->dev, "wo_in");
	if (IS_EWW(st->cwkin))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->cwkin),
				     "faiwed to get the WO input cwock\n");

	mutex_init(&st->wock);

	wet = adwf6780_init(st);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, adwf6780_powewdown, st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id adwf6780_id[] = {
	{ "adwf6780", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, adwf6780_id);

static const stwuct of_device_id adwf6780_of_match[] = {
	{ .compatibwe = "adi,adwf6780" },
	{}
};
MODUWE_DEVICE_TABWE(of, adwf6780_of_match);

static stwuct spi_dwivew adwf6780_dwivew = {
	.dwivew = {
		.name = "adwf6780",
		.of_match_tabwe = adwf6780_of_match,
	},
	.pwobe = adwf6780_pwobe,
	.id_tabwe = adwf6780_id,
};
moduwe_spi_dwivew(adwf6780_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com");
MODUWE_DESCWIPTION("Anawog Devices ADWF6780");
MODUWE_WICENSE("GPW v2");
