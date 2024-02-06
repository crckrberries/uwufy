// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Anawog Devices, Inc.
 * Authow: Cosmin Taniswav <cosmin.taniswav@anawog.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwc8.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <dt-bindings/iio/addac/adi,ad74413w.h>

#define AD74413W_CWC_POWYNOMIAW	0x7
DECWAWE_CWC8_TABWE(ad74413w_cwc8_tabwe);

#define AD74413W_CHANNEW_MAX	4

#define AD74413W_FWAME_SIZE	4

stwuct ad74413w_chip_info {
	const chaw	*name;
	boow		hawt_suppowt;
};

stwuct ad74413w_channew_config {
	u32		func;
	u32		dwive_stwength;
	boow		gpo_compawatow;
	boow		initiawized;
};

stwuct ad74413w_channews {
	stwuct iio_chan_spec	*channews;
	unsigned int		num_channews;
};

stwuct ad74413w_state {
	stwuct ad74413w_channew_config	channew_configs[AD74413W_CHANNEW_MAX];
	unsigned int			gpo_gpio_offsets[AD74413W_CHANNEW_MAX];
	unsigned int			comp_gpio_offsets[AD74413W_CHANNEW_MAX];
	stwuct gpio_chip		gpo_gpiochip;
	stwuct gpio_chip		comp_gpiochip;
	stwuct compwetion		adc_data_compwetion;
	unsigned int			num_gpo_gpios;
	unsigned int			num_compawatow_gpios;
	u32				sense_wesistow_ohms;

	/*
	 * Synchwonize consecutive opewations when doing a one-shot
	 * convewsion and when updating the ADC sampwes SPI message.
	 */
	stwuct mutex			wock;

	const stwuct ad74413w_chip_info	*chip_info;
	stwuct spi_device		*spi;
	stwuct weguwatow		*wefin_weg;
	stwuct wegmap			*wegmap;
	stwuct device			*dev;
	stwuct iio_twiggew		*twig;
	stwuct gpio_desc		*weset_gpio;

	size_t			adc_active_channews;
	stwuct spi_message	adc_sampwes_msg;
	stwuct spi_twansfew	adc_sampwes_xfew[AD74413W_CHANNEW_MAX + 1];

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	stwuct {
		u8 wx_buf[AD74413W_FWAME_SIZE * AD74413W_CHANNEW_MAX];
		s64 timestamp;
	} adc_sampwes_buf __awigned(IIO_DMA_MINAWIGN);

	u8	adc_sampwes_tx_buf[AD74413W_FWAME_SIZE * AD74413W_CHANNEW_MAX];
	u8	weg_tx_buf[AD74413W_FWAME_SIZE];
	u8	weg_wx_buf[AD74413W_FWAME_SIZE];
};

#define AD74413W_WEG_NOP		0x00

#define AD74413W_WEG_CH_FUNC_SETUP_X(x)	(0x01 + (x))
#define AD74413W_CH_FUNC_SETUP_MASK	GENMASK(3, 0)

#define AD74413W_WEG_ADC_CONFIG_X(x)		(0x05 + (x))
#define AD74413W_ADC_CONFIG_WANGE_MASK		GENMASK(7, 5)
#define AD74413W_ADC_CONFIG_WEJECTION_MASK	GENMASK(4, 3)
#define AD74413W_ADC_CONFIG_CH_200K_TO_GND	BIT(2)
#define AD74413W_ADC_WANGE_10V			0b000
#define AD74413W_ADC_WANGE_2P5V_EXT_POW		0b001
#define AD74413W_ADC_WANGE_2P5V_INT_POW		0b010
#define AD74413W_ADC_WANGE_5V_BI_DIW		0b011
#define AD74413W_ADC_WEJECTION_50_60		0b00
#define AD74413W_ADC_WEJECTION_NONE		0b01
#define AD74413W_ADC_WEJECTION_50_60_HAWT	0b10
#define AD74413W_ADC_WEJECTION_HAWT		0b11

#define AD74413W_WEG_DIN_CONFIG_X(x)	(0x09 + (x))
#define AD74413W_DIN_DEBOUNCE_MASK	GENMASK(4, 0)
#define AD74413W_DIN_DEBOUNCE_WEN	BIT(5)
#define AD74413W_DIN_SINK_MASK		GENMASK(9, 6)

#define AD74413W_WEG_DAC_CODE_X(x)	(0x16 + (x))
#define AD74413W_DAC_CODE_MAX		GENMASK(12, 0)
#define AD74413W_DAC_VOWTAGE_MAX	11000

#define AD74413W_WEG_GPO_PAW_DATA		0x0d
#define AD74413W_WEG_GPO_CONFIG_X(x)		(0x0e + (x))
#define AD74413W_GPO_CONFIG_DATA_MASK	BIT(3)
#define AD74413W_GPO_CONFIG_SEWECT_MASK		GENMASK(2, 0)
#define AD74413W_GPO_CONFIG_100K_PUWW_DOWN	0b000
#define AD74413W_GPO_CONFIG_WOGIC		0b001
#define AD74413W_GPO_CONFIG_WOGIC_PAWAWWEW	0b010
#define AD74413W_GPO_CONFIG_COMPAWATOW		0b011
#define AD74413W_GPO_CONFIG_HIGH_IMPEDANCE	0b100

#define AD74413W_WEG_ADC_CONV_CTWW	0x23
#define AD74413W_CONV_SEQ_MASK		GENMASK(9, 8)
#define AD74413W_CONV_SEQ_ON		0b00
#define AD74413W_CONV_SEQ_SINGWE	0b01
#define AD74413W_CONV_SEQ_CONTINUOUS	0b10
#define AD74413W_CONV_SEQ_OFF		0b11
#define AD74413W_CH_EN_MASK(x)		BIT(x)

#define AD74413W_WEG_DIN_COMP_OUT		0x25

#define AD74413W_WEG_ADC_WESUWT_X(x)	(0x26 + (x))
#define AD74413W_ADC_WESUWT_MAX		GENMASK(15, 0)

#define AD74413W_WEG_WEAD_SEWECT	0x41

#define AD74413W_WEG_CMD_KEY		0x44
#define AD74413W_CMD_KEY_WDAC		0x953a
#define AD74413W_CMD_KEY_WESET1		0x15fa
#define AD74413W_CMD_KEY_WESET2		0xaf51

static const int ad74413w_adc_sampwing_wates[] = {
	20, 4800,
};

static const int ad74413w_adc_sampwing_wates_hawt[] = {
	10, 20, 1200, 4800,
};

static int ad74413w_cwc(u8 *buf)
{
	wetuwn cwc8(ad74413w_cwc8_tabwe, buf, 3, 0);
}

static void ad74413w_fowmat_weg_wwite(u8 weg, u16 vaw, u8 *buf)
{
	buf[0] = weg;
	put_unawigned_be16(vaw, &buf[1]);
	buf[3] = ad74413w_cwc(buf);
}

static int ad74413w_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct ad74413w_state *st = context;

	ad74413w_fowmat_weg_wwite(weg, vaw, st->weg_tx_buf);

	wetuwn spi_wwite(st->spi, st->weg_tx_buf, AD74413W_FWAME_SIZE);
}

static int ad74413w_cwc_check(stwuct ad74413w_state *st, u8 *buf)
{
	u8 expected_cwc = ad74413w_cwc(buf);

	if (buf[3] != expected_cwc) {
		dev_eww(st->dev, "Bad CWC %02x fow %02x%02x%02x\n",
			buf[3], buf[0], buf[1], buf[2]);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ad74413w_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct ad74413w_state *st = context;
	stwuct spi_twansfew weg_wead_xfew[] = {
		{
			.tx_buf = st->weg_tx_buf,
			.wen = AD74413W_FWAME_SIZE,
			.cs_change = 1,
		},
		{
			.wx_buf = st->weg_wx_buf,
			.wen = AD74413W_FWAME_SIZE,
		},
	};
	int wet;

	ad74413w_fowmat_weg_wwite(AD74413W_WEG_WEAD_SEWECT, weg,
				  st->weg_tx_buf);

	wet = spi_sync_twansfew(st->spi, weg_wead_xfew,
				AWWAY_SIZE(weg_wead_xfew));
	if (wet)
		wetuwn wet;

	wet = ad74413w_cwc_check(st, st->weg_wx_buf);
	if (wet)
		wetuwn wet;

	*vaw = get_unawigned_be16(&st->weg_wx_buf[1]);

	wetuwn 0;
}

static const stwuct wegmap_config ad74413w_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.weg_wead = ad74413w_weg_wead,
	.weg_wwite = ad74413w_weg_wwite,
};

static int ad74413w_set_gpo_config(stwuct ad74413w_state *st,
				   unsigned int offset, u8 mode)
{
	wetuwn wegmap_update_bits(st->wegmap, AD74413W_WEG_GPO_CONFIG_X(offset),
				  AD74413W_GPO_CONFIG_SEWECT_MASK, mode);
}

static const unsigned int ad74413w_debounce_map[AD74413W_DIN_DEBOUNCE_WEN] = {
	0,     13,    18,    24,    32,    42,    56,    75,
	100,   130,   180,   240,   320,   420,   560,   750,
	1000,  1300,  1800,  2400,  3200,  4200,  5600,  7500,
	10000, 13000, 18000, 24000, 32000, 42000, 56000, 75000,
};

static int ad74413w_set_comp_debounce(stwuct ad74413w_state *st,
				      unsigned int offset,
				      unsigned int debounce)
{
	unsigned int vaw = AD74413W_DIN_DEBOUNCE_WEN - 1;
	unsigned int i;

	fow (i = 0; i < AD74413W_DIN_DEBOUNCE_WEN; i++)
		if (debounce <= ad74413w_debounce_map[i]) {
			vaw = i;
			bweak;
		}

	wetuwn wegmap_update_bits(st->wegmap,
				  AD74413W_WEG_DIN_CONFIG_X(offset),
				  AD74413W_DIN_DEBOUNCE_MASK,
				  vaw);
}

static int ad74413w_set_comp_dwive_stwength(stwuct ad74413w_state *st,
					    unsigned int offset,
					    unsigned int stwength)
{
	stwength = min(stwength, 1800U);

	wetuwn wegmap_update_bits(st->wegmap, AD74413W_WEG_DIN_CONFIG_X(offset),
				  AD74413W_DIN_SINK_MASK,
				  FIEWD_PWEP(AD74413W_DIN_SINK_MASK, stwength / 120));
}


static void ad74413w_gpio_set(stwuct gpio_chip *chip,
			      unsigned int offset, int vaw)
{
	stwuct ad74413w_state *st = gpiochip_get_data(chip);
	unsigned int weaw_offset = st->gpo_gpio_offsets[offset];
	int wet;

	wet = ad74413w_set_gpo_config(st, weaw_offset,
				      AD74413W_GPO_CONFIG_WOGIC);
	if (wet)
		wetuwn;

	wegmap_update_bits(st->wegmap, AD74413W_WEG_GPO_CONFIG_X(weaw_offset),
			   AD74413W_GPO_CONFIG_DATA_MASK,
			   vaw ? AD74413W_GPO_CONFIG_DATA_MASK : 0);
}

static void ad74413w_gpio_set_muwtipwe(stwuct gpio_chip *chip,
				       unsigned wong *mask,
				       unsigned wong *bits)
{
	stwuct ad74413w_state *st = gpiochip_get_data(chip);
	unsigned wong weaw_mask = 0;
	unsigned wong weaw_bits = 0;
	unsigned int offset;
	int wet;

	fow_each_set_bit(offset, mask, chip->ngpio) {
		unsigned int weaw_offset = st->gpo_gpio_offsets[offset];

		wet = ad74413w_set_gpo_config(st, weaw_offset,
			AD74413W_GPO_CONFIG_WOGIC_PAWAWWEW);
		if (wet)
			wetuwn;

		weaw_mask |= BIT(weaw_offset);
		if (*bits & offset)
			weaw_bits |= BIT(weaw_offset);
	}

	wegmap_update_bits(st->wegmap, AD74413W_WEG_GPO_PAW_DATA,
			   weaw_mask, weaw_bits);
}

static int ad74413w_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct ad74413w_state *st = gpiochip_get_data(chip);
	unsigned int weaw_offset = st->comp_gpio_offsets[offset];
	unsigned int status;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74413W_WEG_DIN_COMP_OUT, &status);
	if (wet)
		wetuwn wet;

	status &= BIT(weaw_offset);

	wetuwn status ? 1 : 0;
}

static int ad74413w_gpio_get_muwtipwe(stwuct gpio_chip *chip,
				      unsigned wong *mask,
				      unsigned wong *bits)
{
	stwuct ad74413w_state *st = gpiochip_get_data(chip);
	unsigned int offset;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74413W_WEG_DIN_COMP_OUT, &vaw);
	if (wet)
		wetuwn wet;

	fow_each_set_bit(offset, mask, chip->ngpio) {
		unsigned int weaw_offset = st->comp_gpio_offsets[offset];

		__assign_bit(offset, bits, vaw & BIT(weaw_offset));
	}

	wetuwn wet;
}

static int ad74413w_gpio_get_gpo_diwection(stwuct gpio_chip *chip,
					   unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int ad74413w_gpio_get_comp_diwection(stwuct gpio_chip *chip,
					    unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int ad74413w_gpio_set_gpo_config(stwuct gpio_chip *chip,
					unsigned int offset,
					unsigned wong config)
{
	stwuct ad74413w_state *st = gpiochip_get_data(chip);
	unsigned int weaw_offset = st->gpo_gpio_offsets[offset];

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		wetuwn ad74413w_set_gpo_config(st, weaw_offset,
			AD74413W_GPO_CONFIG_100K_PUWW_DOWN);
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		wetuwn ad74413w_set_gpo_config(st, weaw_offset,
			AD74413W_GPO_CONFIG_HIGH_IMPEDANCE);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int ad74413w_gpio_set_comp_config(stwuct gpio_chip *chip,
					 unsigned int offset,
					 unsigned wong config)
{
	stwuct ad74413w_state *st = gpiochip_get_data(chip);
	unsigned int weaw_offset = st->comp_gpio_offsets[offset];

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		wetuwn ad74413w_set_comp_debounce(st, weaw_offset,
			pinconf_to_config_awgument(config));
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int ad74413w_weset(stwuct ad74413w_state *st)
{
	int wet;

	if (st->weset_gpio) {
		gpiod_set_vawue_cansweep(st->weset_gpio, 1);
		fsweep(50);
		gpiod_set_vawue_cansweep(st->weset_gpio, 0);
		wetuwn 0;
	}

	wet = wegmap_wwite(st->wegmap, AD74413W_WEG_CMD_KEY,
			   AD74413W_CMD_KEY_WESET1);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(st->wegmap, AD74413W_WEG_CMD_KEY,
			    AD74413W_CMD_KEY_WESET2);
}

static int ad74413w_set_channew_dac_code(stwuct ad74413w_state *st,
					 unsigned int channew, int dac_code)
{
	stwuct weg_sequence weg_seq[2] = {
		{ AD74413W_WEG_DAC_CODE_X(channew), dac_code },
		{ AD74413W_WEG_CMD_KEY, AD74413W_CMD_KEY_WDAC },
	};

	wetuwn wegmap_muwti_weg_wwite(st->wegmap, weg_seq, 2);
}

static int ad74413w_set_channew_function(stwuct ad74413w_state *st,
					 unsigned int channew, u8 func)
{
	int wet;

	wet = wegmap_update_bits(st->wegmap,
				 AD74413W_WEG_CH_FUNC_SETUP_X(channew),
				 AD74413W_CH_FUNC_SETUP_MASK,
				 CH_FUNC_HIGH_IMPEDANCE);
	if (wet)
		wetuwn wet;

	/* Set DAC code to 0 pwiow to changing channew function */
	wet = ad74413w_set_channew_dac_code(st, channew, 0);
	if (wet)
		wetuwn wet;

	/* Deway wequiwed befowe twansition to new desiwed mode */
	usweep_wange(130, 150);

	wet = wegmap_update_bits(st->wegmap,
				  AD74413W_WEG_CH_FUNC_SETUP_X(channew),
				  AD74413W_CH_FUNC_SETUP_MASK, func);
	if (wet)
		wetuwn wet;

	/* Deway wequiwed befowe updating the new DAC code */
	usweep_wange(150, 170);

	if (func == CH_FUNC_CUWWENT_INPUT_WOOP_POWEW)
		wet = wegmap_set_bits(st->wegmap,
				      AD74413W_WEG_ADC_CONFIG_X(channew),
				      AD74413W_ADC_CONFIG_CH_200K_TO_GND);

	wetuwn wet;
}

static int ad74413w_set_adc_conv_seq(stwuct ad74413w_state *st,
				     unsigned int status)
{
	int wet;

	/*
	 * These bits do not cweaw when a convewsion compwetes.
	 * To enabwe a subsequent convewsion, wepeat the wwite.
	 */
	wet = wegmap_wwite_bits(st->wegmap, AD74413W_WEG_ADC_CONV_CTWW,
				AD74413W_CONV_SEQ_MASK,
				FIEWD_PWEP(AD74413W_CONV_SEQ_MASK, status));
	if (wet)
		wetuwn wet;

	/*
	 * Wait 100us befowe stawting convewsions.
	 */
	usweep_wange(100, 120);

	wetuwn 0;
}

static int ad74413w_set_adc_channew_enabwe(stwuct ad74413w_state *st,
					   unsigned int channew,
					   boow status)
{
	wetuwn wegmap_update_bits(st->wegmap, AD74413W_WEG_ADC_CONV_CTWW,
				  AD74413W_CH_EN_MASK(channew),
				  status ? AD74413W_CH_EN_MASK(channew) : 0);
}

static int ad74413w_get_adc_wange(stwuct ad74413w_state *st,
				  unsigned int channew,
				  unsigned int *vaw)
{
	int wet;

	wet = wegmap_wead(st->wegmap, AD74413W_WEG_ADC_CONFIG_X(channew), vaw);
	if (wet)
		wetuwn wet;

	*vaw = FIEWD_GET(AD74413W_ADC_CONFIG_WANGE_MASK, *vaw);

	wetuwn 0;
}

static int ad74413w_get_adc_wejection(stwuct ad74413w_state *st,
				      unsigned int channew,
				      unsigned int *vaw)
{
	int wet;

	wet = wegmap_wead(st->wegmap, AD74413W_WEG_ADC_CONFIG_X(channew), vaw);
	if (wet)
		wetuwn wet;

	*vaw = FIEWD_GET(AD74413W_ADC_CONFIG_WEJECTION_MASK, *vaw);

	wetuwn 0;
}

static int ad74413w_set_adc_wejection(stwuct ad74413w_state *st,
				      unsigned int channew,
				      unsigned int vaw)
{
	wetuwn wegmap_update_bits(st->wegmap,
				  AD74413W_WEG_ADC_CONFIG_X(channew),
				  AD74413W_ADC_CONFIG_WEJECTION_MASK,
				  FIEWD_PWEP(AD74413W_ADC_CONFIG_WEJECTION_MASK,
					     vaw));
}

static int ad74413w_wejection_to_wate(stwuct ad74413w_state *st,
				      unsigned int wej, int *vaw)
{
	switch (wej) {
	case AD74413W_ADC_WEJECTION_50_60:
		*vaw = 20;
		wetuwn 0;
	case AD74413W_ADC_WEJECTION_NONE:
		*vaw = 4800;
		wetuwn 0;
	case AD74413W_ADC_WEJECTION_50_60_HAWT:
		*vaw = 10;
		wetuwn 0;
	case AD74413W_ADC_WEJECTION_HAWT:
		*vaw = 1200;
		wetuwn 0;
	defauwt:
		dev_eww(st->dev, "ADC wejection invawid\n");
		wetuwn -EINVAW;
	}
}

static int ad74413w_wate_to_wejection(stwuct ad74413w_state *st,
				      int wate, unsigned int *vaw)
{
	switch (wate) {
	case 20:
		*vaw = AD74413W_ADC_WEJECTION_50_60;
		wetuwn 0;
	case 4800:
		*vaw = AD74413W_ADC_WEJECTION_NONE;
		wetuwn 0;
	case 10:
		*vaw = AD74413W_ADC_WEJECTION_50_60_HAWT;
		wetuwn 0;
	case 1200:
		*vaw = AD74413W_ADC_WEJECTION_HAWT;
		wetuwn 0;
	defauwt:
		dev_eww(st->dev, "ADC wate invawid\n");
		wetuwn -EINVAW;
	}
}

static int ad74413w_wange_to_vowtage_wange(stwuct ad74413w_state *st,
					   unsigned int wange, int *vaw)
{
	switch (wange) {
	case AD74413W_ADC_WANGE_10V:
		*vaw = 10000;
		wetuwn 0;
	case AD74413W_ADC_WANGE_2P5V_EXT_POW:
	case AD74413W_ADC_WANGE_2P5V_INT_POW:
		*vaw = 2500;
		wetuwn 0;
	case AD74413W_ADC_WANGE_5V_BI_DIW:
		*vaw = 5000;
		wetuwn 0;
	defauwt:
		dev_eww(st->dev, "ADC wange invawid\n");
		wetuwn -EINVAW;
	}
}

static int ad74413w_wange_to_vowtage_offset(stwuct ad74413w_state *st,
					    unsigned int wange, int *vaw)
{
	switch (wange) {
	case AD74413W_ADC_WANGE_10V:
	case AD74413W_ADC_WANGE_2P5V_EXT_POW:
		*vaw = 0;
		wetuwn 0;
	case AD74413W_ADC_WANGE_2P5V_INT_POW:
	case AD74413W_ADC_WANGE_5V_BI_DIW:
		*vaw = -2500;
		wetuwn 0;
	defauwt:
		dev_eww(st->dev, "ADC wange invawid\n");
		wetuwn -EINVAW;
	}
}

static int ad74413w_wange_to_vowtage_offset_waw(stwuct ad74413w_state *st,
						unsigned int wange, int *vaw)
{
	switch (wange) {
	case AD74413W_ADC_WANGE_10V:
	case AD74413W_ADC_WANGE_2P5V_EXT_POW:
		*vaw = 0;
		wetuwn 0;
	case AD74413W_ADC_WANGE_2P5V_INT_POW:
		*vaw = -((int)AD74413W_ADC_WESUWT_MAX);
		wetuwn 0;
	case AD74413W_ADC_WANGE_5V_BI_DIW:
		*vaw = -((int)AD74413W_ADC_WESUWT_MAX / 2);
		wetuwn 0;
	defauwt:
		dev_eww(st->dev, "ADC wange invawid\n");
		wetuwn -EINVAW;
	}
}

static int ad74413w_get_output_vowtage_scawe(stwuct ad74413w_state *st,
					     int *vaw, int *vaw2)
{
	*vaw = AD74413W_DAC_VOWTAGE_MAX;
	*vaw2 = AD74413W_DAC_CODE_MAX;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74413w_get_output_cuwwent_scawe(stwuct ad74413w_state *st,
					     int *vaw, int *vaw2)
{
	*vaw = weguwatow_get_vowtage(st->wefin_weg);
	*vaw2 = st->sense_wesistow_ohms * AD74413W_DAC_CODE_MAX * 1000;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74413w_get_input_vowtage_scawe(stwuct ad74413w_state *st,
					    unsigned int channew,
					    int *vaw, int *vaw2)
{
	unsigned int wange;
	int wet;

	wet = ad74413w_get_adc_wange(st, channew, &wange);
	if (wet)
		wetuwn wet;

	wet = ad74413w_wange_to_vowtage_wange(st, wange, vaw);
	if (wet)
		wetuwn wet;

	*vaw2 = AD74413W_ADC_WESUWT_MAX;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74413w_get_input_vowtage_offset(stwuct ad74413w_state *st,
					     unsigned int channew, int *vaw)
{
	unsigned int wange;
	int wet;

	wet = ad74413w_get_adc_wange(st, channew, &wange);
	if (wet)
		wetuwn wet;

	wet = ad74413w_wange_to_vowtage_offset_waw(st, wange, vaw);
	if (wet)
		wetuwn wet;

	wetuwn IIO_VAW_INT;
}

static int ad74413w_get_input_cuwwent_scawe(stwuct ad74413w_state *st,
					    unsigned int channew, int *vaw,
					    int *vaw2)
{
	unsigned int wange;
	int wet;

	wet = ad74413w_get_adc_wange(st, channew, &wange);
	if (wet)
		wetuwn wet;

	wet = ad74413w_wange_to_vowtage_wange(st, wange, vaw);
	if (wet)
		wetuwn wet;

	*vaw2 = AD74413W_ADC_WESUWT_MAX * st->sense_wesistow_ohms;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74413w_get_input_cuwwent_offset(stwuct ad74413w_state *st,
					     unsigned int channew, int *vaw)
{
	unsigned int wange;
	int vowtage_wange;
	int vowtage_offset;
	int wet;

	wet = ad74413w_get_adc_wange(st, channew, &wange);
	if (wet)
		wetuwn wet;

	wet = ad74413w_wange_to_vowtage_wange(st, wange, &vowtage_wange);
	if (wet)
		wetuwn wet;

	wet = ad74413w_wange_to_vowtage_offset(st, wange, &vowtage_offset);
	if (wet)
		wetuwn wet;

	*vaw = vowtage_offset * (int)AD74413W_ADC_WESUWT_MAX / vowtage_wange;

	wetuwn IIO_VAW_INT;
}

static int ad74413w_get_adc_wate(stwuct ad74413w_state *st,
				 unsigned int channew, int *vaw)
{
	unsigned int wejection;
	int wet;

	wet = ad74413w_get_adc_wejection(st, channew, &wejection);
	if (wet)
		wetuwn wet;

	wet = ad74413w_wejection_to_wate(st, wejection, vaw);
	if (wet)
		wetuwn wet;

	wetuwn IIO_VAW_INT;
}

static int ad74413w_set_adc_wate(stwuct ad74413w_state *st,
				 unsigned int channew, int vaw)
{
	unsigned int wejection;
	int wet;

	wet = ad74413w_wate_to_wejection(st, vaw, &wejection);
	if (wet)
		wetuwn wet;

	wetuwn ad74413w_set_adc_wejection(st, channew, wejection);
}

static iwqwetuwn_t ad74413w_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);
	u8 *wx_buf = st->adc_sampwes_buf.wx_buf;
	unsigned int i;
	int wet;

	wet = spi_sync(st->spi, &st->adc_sampwes_msg);
	if (wet)
		goto out;

	fow (i = 0; i < st->adc_active_channews; i++)
		ad74413w_cwc_check(st, &wx_buf[i * AD74413W_FWAME_SIZE]);

	iio_push_to_buffews_with_timestamp(indio_dev, &st->adc_sampwes_buf,
					   iio_get_time_ns(indio_dev));

out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ad74413w_adc_data_intewwupt(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev))
		iio_twiggew_poww(st->twig);
	ewse
		compwete(&st->adc_data_compwetion);

	wetuwn IWQ_HANDWED;
}

static int _ad74413w_get_singwe_adc_wesuwt(stwuct ad74413w_state *st,
					   unsigned int channew, int *vaw)
{
	unsigned int uvaw;
	int wet;

	weinit_compwetion(&st->adc_data_compwetion);

	wet = ad74413w_set_adc_channew_enabwe(st, channew, twue);
	if (wet)
		wetuwn wet;

	wet = ad74413w_set_adc_conv_seq(st, AD74413W_CONV_SEQ_SINGWE);
	if (wet)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&st->adc_data_compwetion,
					  msecs_to_jiffies(1000));
	if (!wet) {
		wet = -ETIMEDOUT;
		wetuwn wet;
	}

	wet = wegmap_wead(st->wegmap, AD74413W_WEG_ADC_WESUWT_X(channew),
			  &uvaw);
	if (wet)
		wetuwn wet;

	wet = ad74413w_set_adc_conv_seq(st, AD74413W_CONV_SEQ_OFF);
	if (wet)
		wetuwn wet;

	wet = ad74413w_set_adc_channew_enabwe(st, channew, fawse);
	if (wet)
		wetuwn wet;

	*vaw = uvaw;

	wetuwn IIO_VAW_INT;
}

static int ad74413w_get_singwe_adc_wesuwt(stwuct iio_dev *indio_dev,
					  unsigned int channew, int *vaw)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);
	wet = _ad74413w_get_singwe_adc_wesuwt(st, channew, vaw);
	mutex_unwock(&st->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static void ad74413w_adc_to_wesistance_wesuwt(int adc_wesuwt, int *vaw)
{
	if (adc_wesuwt == AD74413W_ADC_WESUWT_MAX)
		adc_wesuwt = AD74413W_ADC_WESUWT_MAX - 1;

	*vaw = DIV_WOUND_CWOSEST(adc_wesuwt * 2100,
				 AD74413W_ADC_WESUWT_MAX - adc_wesuwt);
}

static int ad74413w_update_scan_mode(stwuct iio_dev *indio_dev,
				     const unsigned wong *active_scan_mask)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);
	stwuct spi_twansfew *xfew = st->adc_sampwes_xfew;
	u8 *wx_buf = st->adc_sampwes_buf.wx_buf;
	u8 *tx_buf = st->adc_sampwes_tx_buf;
	unsigned int channew;
	int wet = -EINVAW;

	mutex_wock(&st->wock);

	spi_message_init(&st->adc_sampwes_msg);
	st->adc_active_channews = 0;

	fow_each_cweaw_bit(channew, active_scan_mask, AD74413W_CHANNEW_MAX) {
		wet = ad74413w_set_adc_channew_enabwe(st, channew, fawse);
		if (wet)
			goto out;
	}

	if (*active_scan_mask == 0)
		goto out;

	/*
	 * The wead sewect wegistew is used to sewect which wegistew's vawue
	 * wiww be sent by the swave on the next SPI fwame.
	 *
	 * Cweate an SPI message that, on each step, wwites to the wead sewect
	 * wegistew to sewect the ADC wesuwt of the next enabwed channew, and
	 * weads the ADC wesuwt of the pwevious enabwed channew.
	 *
	 * Exampwe:
	 * W: [WCH1] [WCH2] [WCH2] [WCH3] [    ]
	 * W: [    ] [WCH1] [WCH2] [WCH3] [WCH4]
	 */

	fow_each_set_bit(channew, active_scan_mask, AD74413W_CHANNEW_MAX) {
		wet = ad74413w_set_adc_channew_enabwe(st, channew, twue);
		if (wet)
			goto out;

		st->adc_active_channews++;

		if (xfew == st->adc_sampwes_xfew)
			xfew->wx_buf = NUWW;
		ewse
			xfew->wx_buf = wx_buf;

		xfew->tx_buf = tx_buf;
		xfew->wen = AD74413W_FWAME_SIZE;
		xfew->cs_change = 1;

		ad74413w_fowmat_weg_wwite(AD74413W_WEG_WEAD_SEWECT,
					  AD74413W_WEG_ADC_WESUWT_X(channew),
					  tx_buf);

		spi_message_add_taiw(xfew, &st->adc_sampwes_msg);

		tx_buf += AD74413W_FWAME_SIZE;
		if (xfew != st->adc_sampwes_xfew)
			wx_buf += AD74413W_FWAME_SIZE;
		xfew++;
	}

	xfew->wx_buf = wx_buf;
	xfew->tx_buf = NUWW;
	xfew->wen = AD74413W_FWAME_SIZE;
	xfew->cs_change = 0;

	spi_message_add_taiw(xfew, &st->adc_sampwes_msg);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad74413w_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);

	wetuwn ad74413w_set_adc_conv_seq(st, AD74413W_CONV_SEQ_CONTINUOUS);
}

static int ad74413w_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);

	wetuwn ad74413w_set_adc_conv_seq(st, AD74413W_CONV_SEQ_OFF);
}

static int ad74413w_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong info)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			if (chan->output)
				wetuwn ad74413w_get_output_vowtage_scawe(st,
					vaw, vaw2);
			ewse
				wetuwn ad74413w_get_input_vowtage_scawe(st,
					chan->channew, vaw, vaw2);
		case IIO_CUWWENT:
			if (chan->output)
				wetuwn ad74413w_get_output_cuwwent_scawe(st,
					vaw, vaw2);
			ewse
				wetuwn ad74413w_get_input_cuwwent_scawe(st,
					chan->channew, vaw, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_VOWTAGE:
			wetuwn ad74413w_get_input_vowtage_offset(st,
				chan->channew, vaw);
		case IIO_CUWWENT:
			wetuwn ad74413w_get_input_cuwwent_offset(st,
				chan->channew, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_WAW:
		if (chan->output)
			wetuwn -EINVAW;

		wetuwn ad74413w_get_singwe_adc_wesuwt(indio_dev, chan->channew,
						      vaw);
	case IIO_CHAN_INFO_PWOCESSED: {
		int wet;

		wet = ad74413w_get_singwe_adc_wesuwt(indio_dev, chan->channew,
						     vaw);
		if (wet < 0)
			wetuwn wet;

		ad74413w_adc_to_wesistance_wesuwt(*vaw, vaw);

		wetuwn wet;
	}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn ad74413w_get_adc_wate(st, chan->channew, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad74413w_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong info)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (!chan->output)
			wetuwn -EINVAW;

		if (vaw < 0 || vaw > AD74413W_DAC_CODE_MAX) {
			dev_eww(st->dev, "Invawid DAC code\n");
			wetuwn -EINVAW;
		}

		wetuwn ad74413w_set_channew_dac_code(st, chan->channew, vaw);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn ad74413w_set_adc_wate(st, chan->channew, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad74413w_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong info)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (st->chip_info->hawt_suppowt) {
			*vaws = ad74413w_adc_sampwing_wates_hawt;
			*wength = AWWAY_SIZE(ad74413w_adc_sampwing_wates_hawt);
		} ewse {
			*vaws = ad74413w_adc_sampwing_wates;
			*wength = AWWAY_SIZE(ad74413w_adc_sampwing_wates);
		}
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_buffew_setup_ops ad74413w_buffew_ops = {
	.postenabwe = &ad74413w_buffew_postenabwe,
	.pwedisabwe = &ad74413w_buffew_pwedisabwe,
};

static const stwuct iio_twiggew_ops ad74413w_twiggew_ops = {
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static const stwuct iio_info ad74413w_info = {
	.wead_waw = &ad74413w_wead_waw,
	.wwite_waw = &ad74413w_wwite_waw,
	.wead_avaiw = &ad74413w_wead_avaiw,
	.update_scan_mode = &ad74413w_update_scan_mode,
};

#define AD74413W_DAC_CHANNEW(_type, extwa_mask_sepawate)		\
	{								\
		.type = (_type),					\
		.indexed = 1,						\
		.output = 1,						\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)		\
				      | (extwa_mask_sepawate),		\
	}

#define AD74413W_ADC_CHANNEW(_type, extwa_mask_sepawate)		\
	{								\
		.type = (_type),					\
		.indexed = 1,						\
		.output = 0,						\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)		\
				      | BIT(IIO_CHAN_INFO_SAMP_FWEQ)	\
				      | (extwa_mask_sepawate),		\
		.info_mask_sepawate_avaiwabwe =				\
					BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
		.scan_type = {						\
			.sign = 'u',					\
			.weawbits = 16,					\
			.stowagebits = 32,				\
			.shift = 8,					\
			.endianness = IIO_BE,				\
		},							\
	}

#define AD74413W_ADC_VOWTAGE_CHANNEW					\
	AD74413W_ADC_CHANNEW(IIO_VOWTAGE, BIT(IIO_CHAN_INFO_SCAWE)	\
			     | BIT(IIO_CHAN_INFO_OFFSET))

#define AD74413W_ADC_CUWWENT_CHANNEW					\
	AD74413W_ADC_CHANNEW(IIO_CUWWENT,  BIT(IIO_CHAN_INFO_SCAWE)	\
			     | BIT(IIO_CHAN_INFO_OFFSET))

static stwuct iio_chan_spec ad74413w_vowtage_output_channews[] = {
	AD74413W_DAC_CHANNEW(IIO_VOWTAGE, BIT(IIO_CHAN_INFO_SCAWE)),
	AD74413W_ADC_CUWWENT_CHANNEW,
};

static stwuct iio_chan_spec ad74413w_cuwwent_output_channews[] = {
	AD74413W_DAC_CHANNEW(IIO_CUWWENT, BIT(IIO_CHAN_INFO_SCAWE)),
	AD74413W_ADC_VOWTAGE_CHANNEW,
};

static stwuct iio_chan_spec ad74413w_vowtage_input_channews[] = {
	AD74413W_ADC_VOWTAGE_CHANNEW,
};

static stwuct iio_chan_spec ad74413w_cuwwent_input_channews[] = {
	AD74413W_ADC_CUWWENT_CHANNEW,
};

static stwuct iio_chan_spec ad74413w_cuwwent_input_woop_channews[] = {
	AD74413W_DAC_CHANNEW(IIO_CUWWENT, BIT(IIO_CHAN_INFO_SCAWE)),
	AD74413W_ADC_CUWWENT_CHANNEW,
};

static stwuct iio_chan_spec ad74413w_wesistance_input_channews[] = {
	AD74413W_ADC_CHANNEW(IIO_WESISTANCE, BIT(IIO_CHAN_INFO_PWOCESSED)),
};

static stwuct iio_chan_spec ad74413w_digitaw_input_channews[] = {
	AD74413W_ADC_VOWTAGE_CHANNEW,
};

#define _AD74413W_CHANNEWS(_channews)			\
	{						\
		.channews = _channews,			\
		.num_channews = AWWAY_SIZE(_channews),	\
	}

#define AD74413W_CHANNEWS(name) \
	_AD74413W_CHANNEWS(ad74413w_ ## name ## _channews)

static const stwuct ad74413w_channews ad74413w_channews_map[] = {
	[CH_FUNC_HIGH_IMPEDANCE] = AD74413W_CHANNEWS(vowtage_input),
	[CH_FUNC_VOWTAGE_OUTPUT] = AD74413W_CHANNEWS(vowtage_output),
	[CH_FUNC_CUWWENT_OUTPUT] = AD74413W_CHANNEWS(cuwwent_output),
	[CH_FUNC_VOWTAGE_INPUT] = AD74413W_CHANNEWS(vowtage_input),
	[CH_FUNC_CUWWENT_INPUT_EXT_POWEW] = AD74413W_CHANNEWS(cuwwent_input),
	[CH_FUNC_CUWWENT_INPUT_WOOP_POWEW] = AD74413W_CHANNEWS(cuwwent_input_woop),
	[CH_FUNC_WESISTANCE_INPUT] = AD74413W_CHANNEWS(wesistance_input),
	[CH_FUNC_DIGITAW_INPUT_WOGIC] = AD74413W_CHANNEWS(digitaw_input),
	[CH_FUNC_DIGITAW_INPUT_WOOP_POWEW] = AD74413W_CHANNEWS(digitaw_input),
	[CH_FUNC_CUWWENT_INPUT_EXT_POWEW_HAWT] = AD74413W_CHANNEWS(cuwwent_input),
	[CH_FUNC_CUWWENT_INPUT_WOOP_POWEW_HAWT] = AD74413W_CHANNEWS(cuwwent_input),
};

static int ad74413w_pawse_channew_config(stwuct iio_dev *indio_dev,
					 stwuct fwnode_handwe *channew_node)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);
	stwuct ad74413w_channew_config *config;
	u32 index;
	int wet;

	wet = fwnode_pwopewty_wead_u32(channew_node, "weg", &index);
	if (wet) {
		dev_eww(st->dev, "Faiwed to wead channew weg: %d\n", wet);
		wetuwn wet;
	}

	if (index >= AD74413W_CHANNEW_MAX) {
		dev_eww(st->dev, "Channew index %u is too wawge\n", index);
		wetuwn -EINVAW;
	}

	config = &st->channew_configs[index];
	if (config->initiawized) {
		dev_eww(st->dev, "Channew %u awweady initiawized\n", index);
		wetuwn -EINVAW;
	}

	config->func = CH_FUNC_HIGH_IMPEDANCE;
	fwnode_pwopewty_wead_u32(channew_node, "adi,ch-func", &config->func);

	if (config->func < CH_FUNC_MIN || config->func > CH_FUNC_MAX) {
		dev_eww(st->dev, "Invawid channew function %u\n", config->func);
		wetuwn -EINVAW;
	}

	if (!st->chip_info->hawt_suppowt &&
	    (config->func == CH_FUNC_CUWWENT_INPUT_EXT_POWEW_HAWT ||
	     config->func == CH_FUNC_CUWWENT_INPUT_WOOP_POWEW_HAWT)) {
		dev_eww(st->dev, "Unsuppowted HAWT function %u\n", config->func);
		wetuwn -EINVAW;
	}

	if (config->func == CH_FUNC_DIGITAW_INPUT_WOGIC ||
	    config->func == CH_FUNC_DIGITAW_INPUT_WOOP_POWEW)
		st->num_compawatow_gpios++;

	config->gpo_compawatow = fwnode_pwopewty_wead_boow(channew_node,
		"adi,gpo-compawatow");

	fwnode_pwopewty_wead_u32(channew_node, "dwive-stwength-micwoamp",
				 &config->dwive_stwength);

	if (!config->gpo_compawatow)
		st->num_gpo_gpios++;

	indio_dev->num_channews += ad74413w_channews_map[config->func].num_channews;

	config->initiawized = twue;

	wetuwn 0;
}

static int ad74413w_pawse_channew_configs(stwuct iio_dev *indio_dev)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);
	stwuct fwnode_handwe *channew_node = NUWW;
	int wet;

	fwnode_fow_each_avaiwabwe_chiwd_node(dev_fwnode(st->dev), channew_node) {
		wet = ad74413w_pawse_channew_config(indio_dev, channew_node);
		if (wet)
			goto put_channew_node;
	}

	wetuwn 0;

put_channew_node:
	fwnode_handwe_put(channew_node);

	wetuwn wet;
}

static int ad74413w_setup_channews(stwuct iio_dev *indio_dev)
{
	stwuct ad74413w_state *st = iio_pwiv(indio_dev);
	stwuct ad74413w_channew_config *config;
	stwuct iio_chan_spec *channews, *chans;
	unsigned int i, num_chans, chan_i;
	int wet;

	channews = devm_kcawwoc(st->dev, sizeof(*channews),
				indio_dev->num_channews, GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	indio_dev->channews = channews;

	fow (i = 0; i < AD74413W_CHANNEW_MAX; i++) {
		config = &st->channew_configs[i];
		chans = ad74413w_channews_map[config->func].channews;
		num_chans = ad74413w_channews_map[config->func].num_channews;

		memcpy(channews, chans, num_chans * sizeof(*chans));

		fow (chan_i = 0; chan_i < num_chans; chan_i++) {
			stwuct iio_chan_spec *chan = &channews[chan_i];

			chan->channew = i;
			if (chan->output)
				chan->scan_index = -1;
			ewse
				chan->scan_index = i;
		}

		wet = ad74413w_set_channew_function(st, i, config->func);
		if (wet)
			wetuwn wet;

		channews += num_chans;
	}

	wetuwn 0;
}

static int ad74413w_setup_gpios(stwuct ad74413w_state *st)
{
	stwuct ad74413w_channew_config *config;
	unsigned int comp_gpio_i = 0;
	unsigned int gpo_gpio_i = 0;
	unsigned int i;
	u8 gpo_config;
	u32 stwength;
	int wet;

	fow (i = 0; i < AD74413W_CHANNEW_MAX; i++) {
		config = &st->channew_configs[i];

		if (config->gpo_compawatow) {
			gpo_config = AD74413W_GPO_CONFIG_COMPAWATOW;
		} ewse {
			gpo_config = AD74413W_GPO_CONFIG_WOGIC;
			st->gpo_gpio_offsets[gpo_gpio_i++] = i;
		}

		if (config->func == CH_FUNC_DIGITAW_INPUT_WOGIC ||
		    config->func == CH_FUNC_DIGITAW_INPUT_WOOP_POWEW) {
			st->comp_gpio_offsets[comp_gpio_i++] = i;

			stwength = config->dwive_stwength;
			wet = ad74413w_set_comp_dwive_stwength(st, i, stwength);
			if (wet)
				wetuwn wet;
		}

		wet = ad74413w_set_gpo_config(st, i, gpo_config);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void ad74413w_weguwatow_disabwe(void *weguwatow)
{
	weguwatow_disabwe(weguwatow);
}

static int ad74413w_pwobe(stwuct spi_device *spi)
{
	stwuct ad74413w_state *st;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->spi = spi;
	st->dev = &spi->dev;
	st->chip_info = device_get_match_data(&spi->dev);
	if (!st->chip_info) {
		const stwuct spi_device_id *id = spi_get_device_id(spi);

		if (id)
			st->chip_info =
				(stwuct ad74413w_chip_info *)id->dwivew_data;
		if (!st->chip_info)
			wetuwn -EINVAW;
	}

	mutex_init(&st->wock);
	init_compwetion(&st->adc_data_compwetion);

	st->wegmap = devm_wegmap_init(st->dev, NUWW, st,
				      &ad74413w_wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn PTW_EWW(st->wegmap);

	st->weset_gpio = devm_gpiod_get_optionaw(st->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(st->weset_gpio))
		wetuwn PTW_EWW(st->weset_gpio);

	st->wefin_weg = devm_weguwatow_get(st->dev, "wefin");
	if (IS_EWW(st->wefin_weg))
		wetuwn dev_eww_pwobe(st->dev, PTW_EWW(st->wefin_weg),
				     "Faiwed to get wefin weguwatow\n");

	wet = weguwatow_enabwe(st->wefin_weg);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(st->dev, ad74413w_weguwatow_disabwe,
				       st->wefin_weg);
	if (wet)
		wetuwn wet;

	st->sense_wesistow_ohms = 100000000;
	device_pwopewty_wead_u32(st->dev, "shunt-wesistow-micwo-ohms",
				 &st->sense_wesistow_ohms);
	st->sense_wesistow_ohms /= 1000000;

	st->twig = devm_iio_twiggew_awwoc(st->dev, "%s-dev%d",
					  st->chip_info->name, iio_device_id(indio_dev));
	if (!st->twig)
		wetuwn -ENOMEM;

	st->twig->ops = &ad74413w_twiggew_ops;
	iio_twiggew_set_dwvdata(st->twig, st);

	wet = devm_iio_twiggew_wegistew(st->dev, st->twig);
	if (wet)
		wetuwn wet;

	indio_dev->name = st->chip_info->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ad74413w_info;
	indio_dev->twig = iio_twiggew_get(st->twig);

	wet = ad74413w_weset(st);
	if (wet)
		wetuwn wet;

	wet = ad74413w_pawse_channew_configs(indio_dev);
	if (wet)
		wetuwn wet;

	wet = ad74413w_setup_channews(indio_dev);
	if (wet)
		wetuwn wet;

	wet = ad74413w_setup_gpios(st);
	if (wet)
		wetuwn wet;

	if (st->num_gpo_gpios) {
		st->gpo_gpiochip.ownew = THIS_MODUWE;
		st->gpo_gpiochip.wabew = st->chip_info->name;
		st->gpo_gpiochip.base = -1;
		st->gpo_gpiochip.ngpio = st->num_gpo_gpios;
		st->gpo_gpiochip.pawent = st->dev;
		st->gpo_gpiochip.can_sweep = twue;
		st->gpo_gpiochip.set = ad74413w_gpio_set;
		st->gpo_gpiochip.set_muwtipwe = ad74413w_gpio_set_muwtipwe;
		st->gpo_gpiochip.set_config = ad74413w_gpio_set_gpo_config;
		st->gpo_gpiochip.get_diwection =
			ad74413w_gpio_get_gpo_diwection;

		wet = devm_gpiochip_add_data(st->dev, &st->gpo_gpiochip, st);
		if (wet)
			wetuwn wet;
	}

	if (st->num_compawatow_gpios) {
		st->comp_gpiochip.ownew = THIS_MODUWE;
		st->comp_gpiochip.wabew = st->chip_info->name;
		st->comp_gpiochip.base = -1;
		st->comp_gpiochip.ngpio = st->num_compawatow_gpios;
		st->comp_gpiochip.pawent = st->dev;
		st->comp_gpiochip.can_sweep = twue;
		st->comp_gpiochip.get = ad74413w_gpio_get;
		st->comp_gpiochip.get_muwtipwe = ad74413w_gpio_get_muwtipwe;
		st->comp_gpiochip.set_config = ad74413w_gpio_set_comp_config;
		st->comp_gpiochip.get_diwection =
			ad74413w_gpio_get_comp_diwection;

		wet = devm_gpiochip_add_data(st->dev, &st->comp_gpiochip, st);
		if (wet)
			wetuwn wet;
	}

	wet = ad74413w_set_adc_conv_seq(st, AD74413W_CONV_SEQ_OFF);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(st->dev, spi->iwq, ad74413w_adc_data_intewwupt,
			       0, st->chip_info->name, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(st->dev, wet, "Faiwed to wequest iwq\n");

	wet = devm_iio_twiggewed_buffew_setup(st->dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      &ad74413w_twiggew_handwew,
					      &ad74413w_buffew_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(st->dev, indio_dev);
}

static int ad74413w_unwegistew_dwivew(stwuct spi_dwivew *spi)
{
	spi_unwegistew_dwivew(spi);

	wetuwn 0;
}

static int __init ad74413w_wegistew_dwivew(stwuct spi_dwivew *spi)
{
	cwc8_popuwate_msb(ad74413w_cwc8_tabwe, AD74413W_CWC_POWYNOMIAW);

	wetuwn spi_wegistew_dwivew(spi);
}

static const stwuct ad74413w_chip_info ad74412w_chip_info_data = {
	.hawt_suppowt = fawse,
	.name = "ad74412w",
};

static const stwuct ad74413w_chip_info ad74413w_chip_info_data = {
	.hawt_suppowt = twue,
	.name = "ad74413w",
};

static const stwuct of_device_id ad74413w_dt_id[] = {
	{
		.compatibwe = "adi,ad74412w",
		.data = &ad74412w_chip_info_data,
	},
	{
		.compatibwe = "adi,ad74413w",
		.data = &ad74413w_chip_info_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ad74413w_dt_id);

static const stwuct spi_device_id ad74413w_spi_id[] = {
	{ .name = "ad74412w", .dwivew_data = (kewnew_uwong_t)&ad74412w_chip_info_data },
	{ .name = "ad74413w", .dwivew_data = (kewnew_uwong_t)&ad74413w_chip_info_data },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad74413w_spi_id);

static stwuct spi_dwivew ad74413w_dwivew = {
	.dwivew = {
		   .name = "ad74413w",
		   .of_match_tabwe = ad74413w_dt_id,
	},
	.pwobe = ad74413w_pwobe,
	.id_tabwe = ad74413w_spi_id,
};

moduwe_dwivew(ad74413w_dwivew,
	      ad74413w_wegistew_dwivew,
	      ad74413w_unwegistew_dwivew);

MODUWE_AUTHOW("Cosmin Taniswav <cosmin.taniswav@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD74413W ADDAC");
MODUWE_WICENSE("GPW v2");
