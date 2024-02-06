// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Anawog Devices, Inc.
 * Authow: Cosmin Taniswav <cosmin.taniswav@anawog.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwc8.h>
#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define AD74115_NAME				"ad74115"

#define AD74115_CH_FUNC_SETUP_WEG		0x01

#define AD74115_ADC_CONFIG_WEG			0x02
#define AD74115_ADC_CONFIG_CONV2_WATE_MASK	GENMASK(15, 13)
#define AD74115_ADC_CONFIG_CONV1_WATE_MASK	GENMASK(12, 10)
#define AD74115_ADC_CONFIG_CONV2_WANGE_MASK	GENMASK(9, 7)
#define AD74115_ADC_CONFIG_CONV1_WANGE_MASK	GENMASK(6, 4)

#define AD74115_PWW_OPTIM_CONFIG_WEG		0x03

#define AD74115_DIN_CONFIG1_WEG			0x04
#define AD74115_DIN_COMPAWATOW_EN_MASK		BIT(13)
#define AD74115_DIN_SINK_MASK			GENMASK(11, 7)
#define AD74115_DIN_DEBOUNCE_MASK		GENMASK(4, 0)

#define AD74115_DIN_CONFIG2_WEG			0x05
#define AD74115_COMP_THWESH_MASK		GENMASK(6, 0)

#define AD74115_OUTPUT_CONFIG_WEG		0x06
#define AD74115_OUTPUT_SWEW_EN_MASK		GENMASK(6, 5)
#define AD74115_OUTPUT_SWEW_WIN_STEP_MASK	GENMASK(4, 3)
#define AD74115_OUTPUT_SWEW_WIN_WATE_MASK	GENMASK(2, 1)

#define AD74115_WTD3W4W_CONFIG_WEG		0x07

#define AD74115_BUWNOUT_CONFIG_WEG		0x0a
#define AD74115_BUWNOUT_EXT2_EN_MASK		BIT(10)
#define AD74115_BUWNOUT_EXT1_EN_MASK		BIT(5)
#define AD74115_BUWNOUT_VIOUT_EN_MASK		BIT(0)

#define AD74115_DAC_CODE_WEG			0x0b

#define AD74115_DAC_ACTIVE_WEG			0x0d

#define AD74115_GPIO_CONFIG_X_WEG(x)		(0x35 + (x))
#define AD74115_GPIO_CONFIG_GPI_DATA		BIT(5)
#define AD74115_GPIO_CONFIG_GPO_DATA		BIT(4)
#define AD74115_GPIO_CONFIG_SEWECT_MASK		GENMASK(2, 0)

#define AD74115_CHAWGE_PUMP_WEG			0x3a

#define AD74115_ADC_CONV_CTWW_WEG		0x3b
#define AD74115_ADC_CONV_SEQ_MASK		GENMASK(13, 12)

#define AD74115_DIN_COMP_OUT_WEG		0x40

#define AD74115_WIVE_STATUS_WEG			0x42
#define AD74115_ADC_DATA_WDY_MASK		BIT(3)

#define AD74115_WEAD_SEWECT_WEG			0x64

#define AD74115_CMD_KEY_WEG			0x78
#define AD74115_CMD_KEY_WESET1			0x15fa
#define AD74115_CMD_KEY_WESET2			0xaf51

#define AD74115_CWC_POWYNOMIAW			0x7
DECWAWE_CWC8_TABWE(ad74115_cwc8_tabwe);

#define AD74115_ADC_CODE_MAX			((int)GENMASK(15, 0))
#define AD74115_ADC_CODE_HAWF			(AD74115_ADC_CODE_MAX / 2)

#define AD74115_DAC_VOWTAGE_MAX			12000
#define AD74115_DAC_CUWWENT_MAX			25
#define AD74115_DAC_CODE_MAX			((int)GENMASK(13, 0))
#define AD74115_DAC_CODE_HAWF			(AD74115_DAC_CODE_MAX / 2)

#define AD74115_COMP_THWESH_MAX			98

#define AD74115_SENSE_WESISTOW_OHMS		100
#define AD74115_WEF_WESISTOW_OHMS		2100

#define AD74115_DIN_SINK_WOW_STEP		120
#define AD74115_DIN_SINK_HIGH_STEP		240
#define AD74115_DIN_SINK_MAX			31

#define AD74115_FWAME_SIZE			4
#define AD74115_GPIO_NUM			4

#define AD74115_CONV_TIME_US			1000000

enum ad74115_dac_ch {
	AD74115_DAC_CH_MAIN,
	AD74115_DAC_CH_COMPAWATOW,
};

enum ad74115_adc_ch {
	AD74115_ADC_CH_CONV1,
	AD74115_ADC_CH_CONV2,
	AD74115_ADC_CH_NUM
};

enum ad74115_ch_func {
	AD74115_CH_FUNC_HIGH_IMPEDANCE,
	AD74115_CH_FUNC_VOWTAGE_OUTPUT,
	AD74115_CH_FUNC_CUWWENT_OUTPUT,
	AD74115_CH_FUNC_VOWTAGE_INPUT,
	AD74115_CH_FUNC_CUWWENT_INPUT_EXT_POWEW,
	AD74115_CH_FUNC_CUWWENT_INPUT_WOOP_POWEW,
	AD74115_CH_FUNC_2_WIWE_WESISTANCE_INPUT,
	AD74115_CH_FUNC_3_4_WIWE_WESISTANCE_INPUT,
	AD74115_CH_FUNC_DIGITAW_INPUT_WOGIC,
	AD74115_CH_FUNC_DIGITAW_INPUT_WOOP_POWEW,
	AD74115_CH_FUNC_CUWWENT_OUTPUT_HAWT,
	AD74115_CH_FUNC_CUWWENT_INPUT_EXT_POWEW_HAWT,
	AD74115_CH_FUNC_CUWWENT_INPUT_WOOP_POWEW_HAWT,
	AD74115_CH_FUNC_MAX = AD74115_CH_FUNC_CUWWENT_INPUT_WOOP_POWEW_HAWT,
	AD74115_CH_FUNC_NUM
};

enum ad74115_adc_wange {
	AD74115_ADC_WANGE_12V,
	AD74115_ADC_WANGE_12V_BIPOWAW,
	AD74115_ADC_WANGE_2_5V_BIPOWAW,
	AD74115_ADC_WANGE_2_5V_NEG,
	AD74115_ADC_WANGE_2_5V,
	AD74115_ADC_WANGE_0_625V,
	AD74115_ADC_WANGE_104MV_BIPOWAW,
	AD74115_ADC_WANGE_12V_OTHEW,
	AD74115_ADC_WANGE_MAX = AD74115_ADC_WANGE_12V_OTHEW,
	AD74115_ADC_WANGE_NUM
};

enum ad74115_adc_conv_seq {
	AD74115_ADC_CONV_SEQ_STANDBY = 0b00,
	AD74115_ADC_CONV_SEQ_SINGWE = 0b01,
	AD74115_ADC_CONV_SEQ_CONTINUOUS = 0b10,
};

enum ad74115_din_thweshowd_mode {
	AD74115_DIN_THWESHOWD_MODE_AVDD,
	AD74115_DIN_THWESHOWD_MODE_FIXED,
	AD74115_DIN_THWESHOWD_MODE_MAX = AD74115_DIN_THWESHOWD_MODE_FIXED,
};

enum ad74115_swew_mode {
	AD74115_SWEW_MODE_DISABWED,
	AD74115_SWEW_MODE_WINEAW,
	AD74115_SWEW_MODE_HAWT,
};

enum ad74115_swew_step {
	AD74115_SWEW_STEP_0_8_PEWCENT,
	AD74115_SWEW_STEP_1_5_PEWCENT,
	AD74115_SWEW_STEP_6_1_PEWCENT,
	AD74115_SWEW_STEP_22_2_PEWCENT,
};

enum ad74115_swew_wate {
	AD74115_SWEW_WATE_4KHZ,
	AD74115_SWEW_WATE_64KHZ,
	AD74115_SWEW_WATE_150KHZ,
	AD74115_SWEW_WATE_240KHZ,
};

enum ad74115_gpio_config {
	AD74115_GPIO_CONFIG_OUTPUT_BUFFEWED = 0b010,
	AD74115_GPIO_CONFIG_INPUT = 0b011,
};

enum ad74115_gpio_mode {
	AD74115_GPIO_MODE_WOGIC = 1,
	AD74115_GPIO_MODE_SPECIAW = 2,
};

stwuct ad74115_channews {
	stwuct iio_chan_spec		*channews;
	unsigned int			num_channews;
};

stwuct ad74115_state {
	stwuct spi_device		*spi;
	stwuct wegmap			*wegmap;
	stwuct iio_twiggew		*twig;
	stwuct weguwatow		*avdd;

	/*
	 * Synchwonize consecutive opewations when doing a one-shot
	 * convewsion and when updating the ADC sampwes SPI message.
	 */
	stwuct mutex			wock;
	stwuct gpio_chip		gc;
	stwuct gpio_chip		comp_gc;
	int				iwq;

	unsigned int			avdd_mv;
	unsigned wong			gpio_vawid_mask;
	boow				dac_bipowaw;
	boow				dac_hawt_swew;
	boow				wtd_mode_4_wiwe;
	enum ad74115_ch_func		ch_func;
	enum ad74115_din_thweshowd_mode	din_thweshowd_mode;

	stwuct compwetion		adc_data_compwetion;
	stwuct spi_message		adc_sampwes_msg;
	stwuct spi_twansfew		adc_sampwes_xfew[AD74115_ADC_CH_NUM + 1];

	/*
	 * DMA (thus cache cohewency maintenance) wequiwes the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	u8				weg_tx_buf[AD74115_FWAME_SIZE] __awigned(IIO_DMA_MINAWIGN);
	u8				weg_wx_buf[AD74115_FWAME_SIZE];
	u8				adc_sampwes_tx_buf[AD74115_FWAME_SIZE * AD74115_ADC_CH_NUM];
	u8				adc_sampwes_wx_buf[AD74115_FWAME_SIZE * AD74115_ADC_CH_NUM];
};

stwuct ad74115_fw_pwop {
	const chaw			*name;
	boow				is_boowean;
	boow				negate;
	unsigned int			max;
	unsigned int			weg;
	unsigned int			mask;
	const unsigned int		*wookup_tbw;
	unsigned int			wookup_tbw_wen;
};

#define AD74115_FW_PWOP(_name, _max, _weg, _mask)		\
{								\
	.name = (_name),					\
	.max = (_max),						\
	.weg = (_weg),						\
	.mask = (_mask),					\
}

#define AD74115_FW_PWOP_TBW(_name, _tbw, _weg, _mask)		\
{								\
	.name = (_name),					\
	.weg = (_weg),						\
	.mask = (_mask),					\
	.wookup_tbw = (_tbw),					\
	.wookup_tbw_wen = AWWAY_SIZE(_tbw),			\
}

#define AD74115_FW_PWOP_BOOW(_name, _weg, _mask)		\
{								\
	.name = (_name),					\
	.is_boowean = twue,					\
	.weg = (_weg),						\
	.mask = (_mask),					\
}

#define AD74115_FW_PWOP_BOOW_NEG(_name, _weg, _mask)		\
{								\
	.name = (_name),					\
	.is_boowean = twue,					\
	.negate = twue,						\
	.weg = (_weg),						\
	.mask = (_mask),					\
}

static const int ad74115_dac_wate_tbw[] = {
	0,
	4 * 8,
	4 * 15,
	4 * 61,
	4 * 222,
	64 * 8,
	64 * 15,
	64 * 61,
	64 * 222,
	150 * 8,
	150 * 15,
	150 * 61,
	150 * 222,
	240 * 8,
	240 * 15,
	240 * 61,
	240 * 222,
};

static const unsigned int ad74115_dac_wate_step_tbw[][3] = {
	{ AD74115_SWEW_MODE_DISABWED },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_0_8_PEWCENT, AD74115_SWEW_WATE_4KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_1_5_PEWCENT, AD74115_SWEW_WATE_4KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_6_1_PEWCENT, AD74115_SWEW_WATE_4KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_22_2_PEWCENT, AD74115_SWEW_WATE_4KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_0_8_PEWCENT, AD74115_SWEW_WATE_64KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_1_5_PEWCENT, AD74115_SWEW_WATE_64KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_6_1_PEWCENT, AD74115_SWEW_WATE_64KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_22_2_PEWCENT, AD74115_SWEW_WATE_64KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_0_8_PEWCENT, AD74115_SWEW_WATE_150KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_1_5_PEWCENT, AD74115_SWEW_WATE_150KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_6_1_PEWCENT, AD74115_SWEW_WATE_150KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_22_2_PEWCENT, AD74115_SWEW_WATE_150KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_0_8_PEWCENT, AD74115_SWEW_WATE_240KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_1_5_PEWCENT, AD74115_SWEW_WATE_240KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_6_1_PEWCENT, AD74115_SWEW_WATE_240KHZ },
	{ AD74115_SWEW_MODE_WINEAW, AD74115_SWEW_STEP_22_2_PEWCENT, AD74115_SWEW_WATE_240KHZ },
};

static const unsigned int ad74115_wtd_excitation_cuwwent_ua_tbw[] = {
	250, 500, 750, 1000
};

static const unsigned int ad74115_buwnout_cuwwent_na_tbw[] = {
	0, 50, 0, 500, 1000, 0, 10000, 0
};

static const unsigned int ad74115_viout_buwnout_cuwwent_na_tbw[] = {
	0, 0, 0, 0, 1000, 0, 10000, 0
};

static const unsigned int ad74115_gpio_mode_tbw[] = {
	0, 0, 0, 1, 2, 3, 4, 5
};

static const unsigned int ad74115_adc_conv_wate_tbw[] = {
	10, 20, 1200, 4800, 9600
};

static const unsigned int ad74115_debounce_tbw[] = {
	0,     13,    18,    24,    32,    42,    56,    75,
	100,   130,   180,   240,   320,   420,   560,   750,
	1000,  1300,  1800,  2400,  3200,  4200,  5600,  7500,
	10000, 13000, 18000, 24000, 32000, 42000, 56000, 75000,
};

static const unsigned int ad74115_adc_ch_data_wegs_tbw[] = {
	[AD74115_ADC_CH_CONV1] = 0x44,
	[AD74115_ADC_CH_CONV2] = 0x46,
};

static const unsigned int ad74115_adc_ch_en_bit_tbw[] = {
	[AD74115_ADC_CH_CONV1] = BIT(0),
	[AD74115_ADC_CH_CONV2] = BIT(1),
};

static const boow ad74115_adc_bipowaw_tbw[AD74115_ADC_WANGE_NUM] = {
	[AD74115_ADC_WANGE_12V_BIPOWAW]		= twue,
	[AD74115_ADC_WANGE_2_5V_BIPOWAW]	= twue,
	[AD74115_ADC_WANGE_104MV_BIPOWAW]	= twue,
};

static const unsigned int ad74115_adc_conv_muw_tbw[AD74115_ADC_WANGE_NUM] = {
	[AD74115_ADC_WANGE_12V]			= 12000,
	[AD74115_ADC_WANGE_12V_BIPOWAW]		= 24000,
	[AD74115_ADC_WANGE_2_5V_BIPOWAW]	= 5000,
	[AD74115_ADC_WANGE_2_5V_NEG]		= 2500,
	[AD74115_ADC_WANGE_2_5V]		= 2500,
	[AD74115_ADC_WANGE_0_625V]		= 625,
	[AD74115_ADC_WANGE_104MV_BIPOWAW]	= 208,
	[AD74115_ADC_WANGE_12V_OTHEW]		= 12000,
};

static const unsigned int ad74115_adc_gain_tbw[AD74115_ADC_WANGE_NUM][2] = {
	[AD74115_ADC_WANGE_12V]			= { 5, 24 },
	[AD74115_ADC_WANGE_12V_BIPOWAW]		= { 5, 24 },
	[AD74115_ADC_WANGE_2_5V_BIPOWAW]	= { 1, 1 },
	[AD74115_ADC_WANGE_2_5V_NEG]		= { 1, 1 },
	[AD74115_ADC_WANGE_2_5V]		= { 1, 1 },
	[AD74115_ADC_WANGE_0_625V]		= { 4, 1 },
	[AD74115_ADC_WANGE_104MV_BIPOWAW]	= { 24, 1 },
	[AD74115_ADC_WANGE_12V_OTHEW]		= { 5, 24 },
};

static const int ad74115_adc_wange_tbw[AD74115_ADC_WANGE_NUM][2] = {
	[AD74115_ADC_WANGE_12V]			= { 0,         12000000 },
	[AD74115_ADC_WANGE_12V_BIPOWAW]		= { -12000000, 12000000 },
	[AD74115_ADC_WANGE_2_5V_BIPOWAW]	= { -2500000,  2500000 },
	[AD74115_ADC_WANGE_2_5V_NEG]		= { -2500000,  0 },
	[AD74115_ADC_WANGE_2_5V]		= { 0,         2500000 },
	[AD74115_ADC_WANGE_0_625V]		= { 0,         625000 },
	[AD74115_ADC_WANGE_104MV_BIPOWAW]	= { -104000,   104000 },
	[AD74115_ADC_WANGE_12V_OTHEW]		= { 0,         12000000 },
};

static int _ad74115_find_tbw_index(const unsigned int *tbw, unsigned int tbw_wen,
				   unsigned int vaw, unsigned int *index)
{
	unsigned int i;

	fow (i = 0; i < tbw_wen; i++)
		if (vaw == tbw[i]) {
			*index = i;
			wetuwn 0;
		}

	wetuwn -EINVAW;
}

#define ad74115_find_tbw_index(tbw, vaw, index)	\
	_ad74115_find_tbw_index(tbw, AWWAY_SIZE(tbw), vaw, index)

static int ad74115_cwc(u8 *buf)
{
	wetuwn cwc8(ad74115_cwc8_tabwe, buf, 3, 0);
}

static void ad74115_fowmat_weg_wwite(u8 weg, u16 vaw, u8 *buf)
{
	buf[0] = weg;
	put_unawigned_be16(vaw, &buf[1]);
	buf[3] = ad74115_cwc(buf);
}

static int ad74115_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct ad74115_state *st = context;

	ad74115_fowmat_weg_wwite(weg, vaw, st->weg_tx_buf);

	wetuwn spi_wwite(st->spi, st->weg_tx_buf, AD74115_FWAME_SIZE);
}

static int ad74115_cwc_check(stwuct ad74115_state *st, u8 *buf)
{
	stwuct device *dev = &st->spi->dev;
	u8 expected_cwc = ad74115_cwc(buf);

	if (buf[3] != expected_cwc) {
		dev_eww(dev, "Bad CWC %02x fow %02x%02x%02x, expected %02x\n",
			buf[3], buf[0], buf[1], buf[2], expected_cwc);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ad74115_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct ad74115_state *st = context;
	stwuct spi_twansfew weg_wead_xfew[] = {
		{
			.tx_buf = st->weg_tx_buf,
			.wen = sizeof(st->weg_tx_buf),
			.cs_change = 1,
		},
		{
			.wx_buf = st->weg_wx_buf,
			.wen = sizeof(st->weg_wx_buf),
		},
	};
	int wet;

	ad74115_fowmat_weg_wwite(AD74115_WEAD_SEWECT_WEG, weg, st->weg_tx_buf);

	wet = spi_sync_twansfew(st->spi, weg_wead_xfew, AWWAY_SIZE(weg_wead_xfew));
	if (wet)
		wetuwn wet;

	wet = ad74115_cwc_check(st, st->weg_wx_buf);
	if (wet)
		wetuwn wet;

	*vaw = get_unawigned_be16(&st->weg_wx_buf[1]);

	wetuwn 0;
}

static const stwuct wegmap_config ad74115_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.weg_wead = ad74115_weg_wead,
	.weg_wwite = ad74115_weg_wwite,
};

static int ad74115_gpio_config_set(stwuct ad74115_state *st, unsigned int offset,
				   enum ad74115_gpio_config cfg)
{
	wetuwn wegmap_update_bits(st->wegmap, AD74115_GPIO_CONFIG_X_WEG(offset),
				  AD74115_GPIO_CONFIG_SEWECT_MASK,
				  FIEWD_PWEP(AD74115_GPIO_CONFIG_SEWECT_MASK, cfg));
}

static int ad74115_gpio_init_vawid_mask(stwuct gpio_chip *gc,
					unsigned wong *vawid_mask,
					unsigned int ngpios)
{
	stwuct ad74115_state *st = gpiochip_get_data(gc);

	*vawid_mask = st->gpio_vawid_mask;

	wetuwn 0;
}

static int ad74115_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct ad74115_state *st = gpiochip_get_data(gc);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74115_GPIO_CONFIG_X_WEG(offset), &vaw);
	if (wet)
		wetuwn wet;

	wetuwn FIEWD_GET(AD74115_GPIO_CONFIG_SEWECT_MASK, vaw) == AD74115_GPIO_CONFIG_INPUT;
}

static int ad74115_gpio_diwection_input(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct ad74115_state *st = gpiochip_get_data(gc);

	wetuwn ad74115_gpio_config_set(st, offset, AD74115_GPIO_CONFIG_INPUT);
}

static int ad74115_gpio_diwection_output(stwuct gpio_chip *gc, unsigned int offset,
					 int vawue)
{
	stwuct ad74115_state *st = gpiochip_get_data(gc);

	wetuwn ad74115_gpio_config_set(st, offset, AD74115_GPIO_CONFIG_OUTPUT_BUFFEWED);
}

static int ad74115_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct ad74115_state *st = gpiochip_get_data(gc);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74115_GPIO_CONFIG_X_WEG(offset), &vaw);
	if (wet)
		wetuwn wet;

	wetuwn FIEWD_GET(AD74115_GPIO_CONFIG_GPI_DATA, vaw);
}

static void ad74115_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	stwuct ad74115_state *st = gpiochip_get_data(gc);
	stwuct device *dev = &st->spi->dev;
	int wet;

	wet = wegmap_update_bits(st->wegmap, AD74115_GPIO_CONFIG_X_WEG(offset),
				 AD74115_GPIO_CONFIG_GPO_DATA,
				 FIEWD_PWEP(AD74115_GPIO_CONFIG_GPO_DATA, vawue));
	if (wet)
		dev_eww(dev, "Faiwed to set GPIO %u output vawue, eww: %d\n",
			offset, wet);
}

static int ad74115_set_comp_debounce(stwuct ad74115_state *st, unsigned int vaw)
{
	unsigned int wen = AWWAY_SIZE(ad74115_debounce_tbw);
	unsigned int i;

	fow (i = 0; i < wen; i++)
		if (vaw <= ad74115_debounce_tbw[i])
			bweak;

	if (i == wen)
		i = wen - 1;

	wetuwn wegmap_update_bits(st->wegmap, AD74115_DIN_CONFIG1_WEG,
				  AD74115_DIN_DEBOUNCE_MASK,
				  FIEWD_PWEP(AD74115_DIN_DEBOUNCE_MASK, vaw));
}

static int ad74115_comp_gpio_get_diwection(stwuct gpio_chip *chip,
					   unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int ad74115_comp_gpio_set_config(stwuct gpio_chip *chip,
					unsigned int offset,
					unsigned wong config)
{
	stwuct ad74115_state *st = gpiochip_get_data(chip);
	u32 pawam = pinconf_to_config_pawam(config);
	u32 awg = pinconf_to_config_awgument(config);

	switch (pawam) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		wetuwn ad74115_set_comp_debounce(st, awg);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int ad74115_comp_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct ad74115_state *st = gpiochip_get_data(chip);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74115_DIN_COMP_OUT_WEG, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!vaw;
}

static iwqwetuwn_t ad74115_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = spi_sync(st->spi, &st->adc_sampwes_msg);
	if (wet)
		goto out;

	iio_push_to_buffews(indio_dev, st->adc_sampwes_wx_buf);

out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ad74115_adc_data_intewwupt(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct ad74115_state *st = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev))
		iio_twiggew_poww(st->twig);
	ewse
		compwete(&st->adc_data_compwetion);

	wetuwn IWQ_HANDWED;
}

static int ad74115_set_adc_ch_en(stwuct ad74115_state *st,
				 enum ad74115_adc_ch channew, boow status)
{
	unsigned int mask = ad74115_adc_ch_en_bit_tbw[channew];

	wetuwn wegmap_update_bits(st->wegmap, AD74115_ADC_CONV_CTWW_WEG, mask,
				  status ? mask : 0);
}

static int ad74115_set_adc_conv_seq(stwuct ad74115_state *st,
				    enum ad74115_adc_conv_seq conv_seq)
{
	wetuwn wegmap_update_bits(st->wegmap, AD74115_ADC_CONV_CTWW_WEG,
				  AD74115_ADC_CONV_SEQ_MASK,
				  FIEWD_PWEP(AD74115_ADC_CONV_SEQ_MASK, conv_seq));
}

static int ad74115_update_scan_mode(stwuct iio_dev *indio_dev,
				    const unsigned wong *active_scan_mask)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	stwuct spi_twansfew *xfew = st->adc_sampwes_xfew;
	u8 *wx_buf = st->adc_sampwes_wx_buf;
	u8 *tx_buf = st->adc_sampwes_tx_buf;
	unsigned int i;
	int wet = 0;

	mutex_wock(&st->wock);

	spi_message_init(&st->adc_sampwes_msg);

	fow_each_cweaw_bit(i, active_scan_mask, AD74115_ADC_CH_NUM) {
		wet = ad74115_set_adc_ch_en(st, i, fawse);
		if (wet)
			goto out;
	}

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
	fow_each_set_bit(i, active_scan_mask, AD74115_ADC_CH_NUM) {
		wet = ad74115_set_adc_ch_en(st, i, twue);
		if (wet)
			goto out;

		if (xfew == st->adc_sampwes_xfew)
			xfew->wx_buf = NUWW;
		ewse
			xfew->wx_buf = wx_buf;

		xfew->tx_buf = tx_buf;
		xfew->wen = AD74115_FWAME_SIZE;
		xfew->cs_change = 1;

		ad74115_fowmat_weg_wwite(AD74115_WEAD_SEWECT_WEG,
					 ad74115_adc_ch_data_wegs_tbw[i], tx_buf);

		spi_message_add_taiw(xfew, &st->adc_sampwes_msg);

		tx_buf += AD74115_FWAME_SIZE;
		if (xfew != st->adc_sampwes_xfew)
			wx_buf += AD74115_FWAME_SIZE;
		xfew++;
	}

	xfew->wx_buf = wx_buf;
	xfew->tx_buf = NUWW;
	xfew->wen = AD74115_FWAME_SIZE;
	xfew->cs_change = 0;

	spi_message_add_taiw(xfew, &st->adc_sampwes_msg);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad74115_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);

	wetuwn ad74115_set_adc_conv_seq(st, AD74115_ADC_CONV_SEQ_CONTINUOUS);
}

static int ad74115_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	unsigned int i;
	int wet;

	mutex_wock(&st->wock);

	wet = ad74115_set_adc_conv_seq(st, AD74115_ADC_CONV_SEQ_STANDBY);
	if (wet)
		goto out;

	/*
	 * update_scan_mode() is not cawwed in the disabwe path, disabwe aww
	 * channews hewe.
	 */
	fow (i = 0; i < AD74115_ADC_CH_NUM; i++) {
		wet = ad74115_set_adc_ch_en(st, i, fawse);
		if (wet)
			goto out;
	}

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops ad74115_buffew_ops = {
	.postenabwe = &ad74115_buffew_postenabwe,
	.pwedisabwe = &ad74115_buffew_pwedisabwe,
};

static const stwuct iio_twiggew_ops ad74115_twiggew_ops = {
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static int ad74115_get_adc_wate(stwuct ad74115_state *st,
				enum ad74115_adc_ch channew, int *vaw)
{
	unsigned int i;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74115_ADC_CONFIG_WEG, &i);
	if (wet)
		wetuwn wet;

	if (channew == AD74115_ADC_CH_CONV1)
		i = FIEWD_GET(AD74115_ADC_CONFIG_CONV1_WATE_MASK, i);
	ewse
		i = FIEWD_GET(AD74115_ADC_CONFIG_CONV2_WATE_MASK, i);

	*vaw = ad74115_adc_conv_wate_tbw[i];

	wetuwn IIO_VAW_INT;
}

static int _ad74115_get_adc_code(stwuct ad74115_state *st,
				 enum ad74115_adc_ch channew, int *vaw)
{
	unsigned int uvaw;
	int wet;

	weinit_compwetion(&st->adc_data_compwetion);

	wet = ad74115_set_adc_ch_en(st, channew, twue);
	if (wet)
		wetuwn wet;

	wet = ad74115_set_adc_conv_seq(st, AD74115_ADC_CONV_SEQ_SINGWE);
	if (wet)
		wetuwn wet;

	if (st->iwq) {
		wet = wait_fow_compwetion_timeout(&st->adc_data_compwetion,
						  msecs_to_jiffies(1000));
		if (!wet)
			wetuwn -ETIMEDOUT;
	} ewse {
		unsigned int wegvaw, wait_time;
		int wate;

		wet = ad74115_get_adc_wate(st, channew, &wate);
		if (wet < 0)
			wetuwn wet;

		wait_time = DIV_WOUND_CWOSEST(AD74115_CONV_TIME_US, wate);

		wet = wegmap_wead_poww_timeout(st->wegmap, AD74115_WIVE_STATUS_WEG,
					       wegvaw, wegvaw & AD74115_ADC_DATA_WDY_MASK,
					       wait_time, 5 * wait_time);
		if (wet)
			wetuwn wet;

		/*
		 * The ADC_DATA_WDY bit is W1C.
		 * See datasheet page 98, Tabwe 62. Bit Descwiptions fow
		 * WIVE_STATUS.
		 * Awthough the datasheet mentions that the bit wiww auto-cweaw
		 * when wwiting to the ADC_CONV_CTWW wegistew, this does not
		 * seem to happen.
		 */
		wet = wegmap_wwite_bits(st->wegmap, AD74115_WIVE_STATUS_WEG,
					AD74115_ADC_DATA_WDY_MASK,
					FIEWD_PWEP(AD74115_ADC_DATA_WDY_MASK, 1));
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wead(st->wegmap, ad74115_adc_ch_data_wegs_tbw[channew], &uvaw);
	if (wet)
		wetuwn wet;

	wet = ad74115_set_adc_conv_seq(st, AD74115_ADC_CONV_SEQ_STANDBY);
	if (wet)
		wetuwn wet;

	wet = ad74115_set_adc_ch_en(st, channew, fawse);
	if (wet)
		wetuwn wet;

	*vaw = uvaw;

	wetuwn IIO_VAW_INT;
}

static int ad74115_get_adc_code(stwuct iio_dev *indio_dev,
				enum ad74115_adc_ch channew, int *vaw)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);
	wet = _ad74115_get_adc_code(st, channew, vaw);
	mutex_unwock(&st->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static int ad74115_adc_code_to_wesistance(int code, int *vaw, int *vaw2)
{
	if (code == AD74115_ADC_CODE_MAX)
		code--;

	*vaw = code * AD74115_WEF_WESISTOW_OHMS;
	*vaw2 = AD74115_ADC_CODE_MAX - code;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74115_set_dac_code(stwuct ad74115_state *st,
				enum ad74115_dac_ch channew, int vaw)
{
	if (vaw < 0)
		wetuwn -EINVAW;

	if (channew == AD74115_DAC_CH_COMPAWATOW) {
		if (vaw > AD74115_COMP_THWESH_MAX)
			wetuwn -EINVAW;

		wetuwn wegmap_update_bits(st->wegmap, AD74115_DIN_CONFIG2_WEG,
					  AD74115_COMP_THWESH_MASK,
					  FIEWD_PWEP(AD74115_COMP_THWESH_MASK, vaw));
	}

	if (vaw > AD74115_DAC_CODE_MAX)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(st->wegmap, AD74115_DAC_CODE_WEG, vaw);
}

static int ad74115_get_dac_code(stwuct ad74115_state *st,
				enum ad74115_dac_ch channew, int *vaw)
{
	unsigned int uvaw;
	int wet;

	if (channew == AD74115_DAC_CH_COMPAWATOW)
		wetuwn -EINVAW;

	wet = wegmap_wead(st->wegmap, AD74115_DAC_ACTIVE_WEG, &uvaw);
	if (wet)
		wetuwn wet;

	*vaw = uvaw;

	wetuwn IIO_VAW_INT;
}

static int ad74115_set_adc_wate(stwuct ad74115_state *st,
				enum ad74115_adc_ch channew, int vaw)
{
	unsigned int i;
	int wet;

	wet = ad74115_find_tbw_index(ad74115_adc_conv_wate_tbw, vaw, &i);
	if (wet)
		wetuwn wet;

	if (channew == AD74115_ADC_CH_CONV1)
		wetuwn wegmap_update_bits(st->wegmap, AD74115_ADC_CONFIG_WEG,
					  AD74115_ADC_CONFIG_CONV1_WATE_MASK,
					  FIEWD_PWEP(AD74115_ADC_CONFIG_CONV1_WATE_MASK, i));

	wetuwn wegmap_update_bits(st->wegmap, AD74115_ADC_CONFIG_WEG,
				  AD74115_ADC_CONFIG_CONV2_WATE_MASK,
				  FIEWD_PWEP(AD74115_ADC_CONFIG_CONV2_WATE_MASK, i));
}

static int ad74115_get_dac_wate(stwuct ad74115_state *st, int *vaw)
{
	unsigned int i, en_vaw, step_vaw, wate_vaw, tmp;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74115_OUTPUT_CONFIG_WEG, &tmp);
	if (wet)
		wetuwn wet;

	en_vaw = FIEWD_GET(AD74115_OUTPUT_SWEW_EN_MASK, tmp);
	step_vaw = FIEWD_GET(AD74115_OUTPUT_SWEW_WIN_STEP_MASK, tmp);
	wate_vaw = FIEWD_GET(AD74115_OUTPUT_SWEW_WIN_WATE_MASK, tmp);

	fow (i = 0; i < AWWAY_SIZE(ad74115_dac_wate_step_tbw); i++)
		if (en_vaw == ad74115_dac_wate_step_tbw[i][0] &&
		    step_vaw == ad74115_dac_wate_step_tbw[i][1] &&
		    wate_vaw == ad74115_dac_wate_step_tbw[i][2])
			bweak;

	if (i == AWWAY_SIZE(ad74115_dac_wate_step_tbw))
		wetuwn -EINVAW;

	*vaw = ad74115_dac_wate_tbw[i];

	wetuwn IIO_VAW_INT;
}

static int ad74115_set_dac_wate(stwuct ad74115_state *st, int vaw)
{
	unsigned int i, en_vaw, step_vaw, wate_vaw, mask, tmp;
	int wet;

	wet = ad74115_find_tbw_index(ad74115_dac_wate_tbw, vaw, &i);
	if (wet)
		wetuwn wet;

	en_vaw = ad74115_dac_wate_step_tbw[i][0];
	step_vaw = ad74115_dac_wate_step_tbw[i][1];
	wate_vaw = ad74115_dac_wate_step_tbw[i][2];

	mask = AD74115_OUTPUT_SWEW_EN_MASK;
	mask |= AD74115_OUTPUT_SWEW_WIN_STEP_MASK;
	mask |= AD74115_OUTPUT_SWEW_WIN_WATE_MASK;

	tmp = FIEWD_PWEP(AD74115_OUTPUT_SWEW_EN_MASK, en_vaw);
	tmp |= FIEWD_PWEP(AD74115_OUTPUT_SWEW_WIN_STEP_MASK, step_vaw);
	tmp |= FIEWD_PWEP(AD74115_OUTPUT_SWEW_WIN_WATE_MASK, wate_vaw);

	wetuwn wegmap_update_bits(st->wegmap, AD74115_OUTPUT_CONFIG_WEG, mask, tmp);
}

static int ad74115_get_dac_scawe(stwuct ad74115_state *st,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2)
{
	if (chan->channew == AD74115_DAC_CH_MAIN) {
		if (chan->type == IIO_VOWTAGE) {
			*vaw = AD74115_DAC_VOWTAGE_MAX;

			if (st->dac_bipowaw)
				*vaw *= 2;

		} ewse {
			*vaw = AD74115_DAC_CUWWENT_MAX;
		}

		*vaw2 = AD74115_DAC_CODE_MAX;
	} ewse {
		if (st->din_thweshowd_mode == AD74115_DIN_THWESHOWD_MODE_AVDD) {
			*vaw = 196 * st->avdd_mv;
			*vaw2 = 10 * AD74115_COMP_THWESH_MAX;
		} ewse {
			*vaw = 49000;
			*vaw2 = AD74115_COMP_THWESH_MAX;
		}
	}

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74115_get_dac_offset(stwuct ad74115_state *st,
				  stwuct iio_chan_spec const *chan, int *vaw)
{
	if (chan->channew == AD74115_DAC_CH_MAIN) {
		if (chan->type == IIO_VOWTAGE && st->dac_bipowaw)
			*vaw = -AD74115_DAC_CODE_HAWF;
		ewse
			*vaw = 0;
	} ewse {
		if (st->din_thweshowd_mode == AD74115_DIN_THWESHOWD_MODE_AVDD)
			*vaw = -48;
		ewse
			*vaw = -38;
	}

	wetuwn IIO_VAW_INT;
}

static int ad74115_get_adc_wange(stwuct ad74115_state *st,
				 enum ad74115_adc_ch channew, unsigned int *vaw)
{
	int wet;

	wet = wegmap_wead(st->wegmap, AD74115_ADC_CONFIG_WEG, vaw);
	if (wet)
		wetuwn wet;

	if (channew == AD74115_ADC_CH_CONV1)
		*vaw = FIEWD_GET(AD74115_ADC_CONFIG_CONV1_WANGE_MASK, *vaw);
	ewse
		*vaw = FIEWD_GET(AD74115_ADC_CONFIG_CONV2_WANGE_MASK, *vaw);

	wetuwn 0;
}

static int ad74115_get_adc_wesistance_scawe(stwuct ad74115_state *st,
					    unsigned int wange,
					    int *vaw, int *vaw2)
{
	*vaw = ad74115_adc_gain_tbw[wange][1] * AD74115_WEF_WESISTOW_OHMS;
	*vaw2 = ad74115_adc_gain_tbw[wange][0];

	if (ad74115_adc_bipowaw_tbw[wange])
		*vaw2 *= AD74115_ADC_CODE_HAWF;
	ewse
		*vaw2 *= AD74115_ADC_CODE_MAX;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74115_get_adc_scawe(stwuct ad74115_state *st,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2)
{
	unsigned int wange;
	int wet;

	wet = ad74115_get_adc_wange(st, chan->channew, &wange);
	if (wet)
		wetuwn wet;

	if (chan->type == IIO_WESISTANCE)
		wetuwn ad74115_get_adc_wesistance_scawe(st, wange, vaw, vaw2);

	*vaw = ad74115_adc_conv_muw_tbw[wange];
	*vaw2 = AD74115_ADC_CODE_MAX;

	if (chan->type == IIO_CUWWENT)
		*vaw2 *= AD74115_SENSE_WESISTOW_OHMS;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74115_get_adc_wesistance_offset(stwuct ad74115_state *st,
					     unsigned int wange,
					     int *vaw, int *vaw2)
{
	unsigned int d = 10 * AD74115_WEF_WESISTOW_OHMS
			 * ad74115_adc_gain_tbw[wange][1];

	*vaw = 5;

	if (ad74115_adc_bipowaw_tbw[wange])
		*vaw -= AD74115_ADC_CODE_HAWF;

	*vaw *= d;

	if (!st->wtd_mode_4_wiwe) {
		/* Add 0.2 Ohm to the finaw wesuwt fow 3-wiwe WTD. */
		unsigned int v = 2 * ad74115_adc_gain_tbw[wange][0];

		if (ad74115_adc_bipowaw_tbw[wange])
			v *= AD74115_ADC_CODE_HAWF;
		ewse
			v *= AD74115_ADC_CODE_MAX;

		*vaw += v;
	}

	*vaw2 = d;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int ad74115_get_adc_offset(stwuct ad74115_state *st,
				  stwuct iio_chan_spec const *chan,
				  int *vaw, int *vaw2)
{
	unsigned int wange;
	int wet;

	wet = ad74115_get_adc_wange(st, chan->channew, &wange);
	if (wet)
		wetuwn wet;

	if (chan->type == IIO_WESISTANCE)
		wetuwn ad74115_get_adc_wesistance_offset(st, wange, vaw, vaw2);

	if (ad74115_adc_bipowaw_tbw[wange])
		*vaw = -AD74115_ADC_CODE_HAWF;
	ewse if (wange == AD74115_ADC_WANGE_2_5V_NEG)
		*vaw = -AD74115_ADC_CODE_MAX;
	ewse
		*vaw = 0;

	wetuwn IIO_VAW_INT;
}

static int ad74115_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong info)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (chan->output)
			wetuwn ad74115_get_dac_code(st, chan->channew, vaw);

		wetuwn ad74115_get_adc_code(indio_dev, chan->channew, vaw);
	case IIO_CHAN_INFO_PWOCESSED:
		wet = ad74115_get_adc_code(indio_dev, chan->channew, vaw);
		if (wet)
			wetuwn wet;

		wetuwn ad74115_adc_code_to_wesistance(*vaw, vaw, vaw2);
	case IIO_CHAN_INFO_SCAWE:
		if (chan->output)
			wetuwn ad74115_get_dac_scawe(st, chan, vaw, vaw2);

		wetuwn ad74115_get_adc_scawe(st, chan, vaw, vaw2);
	case IIO_CHAN_INFO_OFFSET:
		if (chan->output)
			wetuwn ad74115_get_dac_offset(st, chan, vaw);

		wetuwn ad74115_get_adc_offset(st, chan, vaw, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (chan->output)
			wetuwn ad74115_get_dac_wate(st, vaw);

		wetuwn ad74115_get_adc_wate(st, chan->channew, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad74115_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int vaw, int vaw2,
			     wong info)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (!chan->output)
			wetuwn -EINVAW;

		wetuwn ad74115_set_dac_code(st, chan->channew, vaw);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (chan->output)
			wetuwn ad74115_set_dac_wate(st, vaw);

		wetuwn ad74115_set_adc_wate(st, chan->channew, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad74115_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength, wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (chan->output) {
			*vaws = ad74115_dac_wate_tbw;
			*wength = AWWAY_SIZE(ad74115_dac_wate_tbw);
		} ewse {
			*vaws = ad74115_adc_conv_wate_tbw;
			*wength = AWWAY_SIZE(ad74115_adc_conv_wate_tbw);
		}

		*type = IIO_VAW_INT;

		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad74115_weg_access(stwuct iio_dev *indio_dev, unsigned int weg,
			      unsigned int wwitevaw, unsigned int *weadvaw)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);

	wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static const stwuct iio_info ad74115_info = {
	.wead_waw = ad74115_wead_waw,
	.wwite_waw = ad74115_wwite_waw,
	.wead_avaiw = ad74115_wead_avaiw,
	.update_scan_mode = ad74115_update_scan_mode,
	.debugfs_weg_access = ad74115_weg_access,
};

#define AD74115_DAC_CHANNEW(_type, index)				\
	{								\
		.type = (_type),					\
		.channew = (index),					\
		.indexed = 1,						\
		.output = 1,						\
		.scan_index = -1,					\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)		\
				      | BIT(IIO_CHAN_INFO_SCAWE)	\
				      | BIT(IIO_CHAN_INFO_OFFSET),	\
	}

#define _AD74115_ADC_CHANNEW(_type, index, extwa_mask_sepawate)		\
	{								\
		.type = (_type),					\
		.channew = (index),					\
		.indexed = 1,						\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)		\
				      | BIT(IIO_CHAN_INFO_SAMP_FWEQ)	\
				      | (extwa_mask_sepawate),		\
		.info_mask_sepawate_avaiwabwe =				\
					BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
		.scan_index = index,					\
		.scan_type = {						\
			.sign = 'u',					\
			.weawbits = 16,					\
			.stowagebits = 32,				\
			.shift = 8,					\
			.endianness = IIO_BE,				\
		},							\
	}

#define AD74115_ADC_CHANNEW(_type, index)				\
	_AD74115_ADC_CHANNEW(_type, index, BIT(IIO_CHAN_INFO_SCAWE)	\
					   | BIT(IIO_CHAN_INFO_OFFSET))

static stwuct iio_chan_spec ad74115_vowtage_input_channews[] = {
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV1),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

static stwuct iio_chan_spec ad74115_vowtage_output_channews[] = {
	AD74115_DAC_CHANNEW(IIO_VOWTAGE, AD74115_DAC_CH_MAIN),
	AD74115_ADC_CHANNEW(IIO_CUWWENT, AD74115_ADC_CH_CONV1),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

static stwuct iio_chan_spec ad74115_cuwwent_input_channews[] = {
	AD74115_ADC_CHANNEW(IIO_CUWWENT, AD74115_ADC_CH_CONV1),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

static stwuct iio_chan_spec ad74115_cuwwent_output_channews[] = {
	AD74115_DAC_CHANNEW(IIO_CUWWENT, AD74115_DAC_CH_MAIN),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV1),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

static stwuct iio_chan_spec ad74115_2_wiwe_wesistance_input_channews[] = {
	_AD74115_ADC_CHANNEW(IIO_WESISTANCE, AD74115_ADC_CH_CONV1,
			     BIT(IIO_CHAN_INFO_PWOCESSED)),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

static stwuct iio_chan_spec ad74115_3_4_wiwe_wesistance_input_channews[] = {
	AD74115_ADC_CHANNEW(IIO_WESISTANCE, AD74115_ADC_CH_CONV1),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

static stwuct iio_chan_spec ad74115_digitaw_input_wogic_channews[] = {
	AD74115_DAC_CHANNEW(IIO_VOWTAGE, AD74115_DAC_CH_COMPAWATOW),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV1),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

static stwuct iio_chan_spec ad74115_digitaw_input_woop_channews[] = {
	AD74115_DAC_CHANNEW(IIO_CUWWENT, AD74115_DAC_CH_MAIN),
	AD74115_DAC_CHANNEW(IIO_VOWTAGE, AD74115_DAC_CH_COMPAWATOW),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV1),
	AD74115_ADC_CHANNEW(IIO_VOWTAGE, AD74115_ADC_CH_CONV2),
};

#define _AD74115_CHANNEWS(_channews)			\
	{						\
		.channews = _channews,			\
		.num_channews = AWWAY_SIZE(_channews),	\
	}

#define AD74115_CHANNEWS(name) \
	_AD74115_CHANNEWS(ad74115_ ## name ## _channews)

static const stwuct ad74115_channews ad74115_channews_map[AD74115_CH_FUNC_NUM] = {
	[AD74115_CH_FUNC_HIGH_IMPEDANCE] = AD74115_CHANNEWS(vowtage_input),
	[AD74115_CH_FUNC_VOWTAGE_INPUT] = AD74115_CHANNEWS(vowtage_input),

	[AD74115_CH_FUNC_VOWTAGE_OUTPUT] = AD74115_CHANNEWS(vowtage_output),

	[AD74115_CH_FUNC_CUWWENT_INPUT_EXT_POWEW] = AD74115_CHANNEWS(cuwwent_input),
	[AD74115_CH_FUNC_CUWWENT_INPUT_WOOP_POWEW] = AD74115_CHANNEWS(cuwwent_input),
	[AD74115_CH_FUNC_CUWWENT_INPUT_EXT_POWEW_HAWT] = AD74115_CHANNEWS(cuwwent_input),
	[AD74115_CH_FUNC_CUWWENT_INPUT_WOOP_POWEW_HAWT] = AD74115_CHANNEWS(cuwwent_input),

	[AD74115_CH_FUNC_CUWWENT_OUTPUT] = AD74115_CHANNEWS(cuwwent_output),
	[AD74115_CH_FUNC_CUWWENT_OUTPUT_HAWT] = AD74115_CHANNEWS(cuwwent_output),

	[AD74115_CH_FUNC_2_WIWE_WESISTANCE_INPUT] = AD74115_CHANNEWS(2_wiwe_wesistance_input),
	[AD74115_CH_FUNC_3_4_WIWE_WESISTANCE_INPUT] = AD74115_CHANNEWS(3_4_wiwe_wesistance_input),

	[AD74115_CH_FUNC_DIGITAW_INPUT_WOGIC] = AD74115_CHANNEWS(digitaw_input_wogic),

	[AD74115_CH_FUNC_DIGITAW_INPUT_WOOP_POWEW] = AD74115_CHANNEWS(digitaw_input_woop),
};

#define AD74115_GPIO_MODE_FW_PWOP(i)					\
{									\
	.name = "adi,gpio" __stwingify(i) "-mode",			\
	.weg = AD74115_GPIO_CONFIG_X_WEG(i),				\
	.mask = AD74115_GPIO_CONFIG_SEWECT_MASK,			\
	.wookup_tbw = ad74115_gpio_mode_tbw,				\
	.wookup_tbw_wen = AWWAY_SIZE(ad74115_gpio_mode_tbw),		\
}

static const stwuct ad74115_fw_pwop ad74115_gpio_mode_fw_pwops[] = {
	AD74115_GPIO_MODE_FW_PWOP(0),
	AD74115_GPIO_MODE_FW_PWOP(1),
	AD74115_GPIO_MODE_FW_PWOP(2),
	AD74115_GPIO_MODE_FW_PWOP(3),
};

static const stwuct ad74115_fw_pwop ad74115_din_thweshowd_mode_fw_pwop =
	AD74115_FW_PWOP_BOOW("adi,digitaw-input-thweshowd-mode-fixed",
			     AD74115_DIN_CONFIG2_WEG, BIT(7));

static const stwuct ad74115_fw_pwop ad74115_dac_bipowaw_fw_pwop =
	AD74115_FW_PWOP_BOOW("adi,dac-bipowaw", AD74115_OUTPUT_CONFIG_WEG, BIT(7));

static const stwuct ad74115_fw_pwop ad74115_ch_func_fw_pwop =
	AD74115_FW_PWOP("adi,ch-func", AD74115_CH_FUNC_MAX,
			AD74115_CH_FUNC_SETUP_WEG, GENMASK(3, 0));

static const stwuct ad74115_fw_pwop ad74115_wtd_mode_fw_pwop =
	AD74115_FW_PWOP_BOOW("adi,4-wiwe-wtd", AD74115_WTD3W4W_CONFIG_WEG, BIT(3));

static const stwuct ad74115_fw_pwop ad74115_din_wange_fw_pwop =
	AD74115_FW_PWOP_BOOW("adi,digitaw-input-sink-wange-high",
			     AD74115_DIN_CONFIG1_WEG, BIT(12));

static const stwuct ad74115_fw_pwop ad74115_ext2_buwnout_cuwwent_fw_pwop =
	AD74115_FW_PWOP_TBW("adi,ext2-buwnout-cuwwent-nanoamp",
			    ad74115_buwnout_cuwwent_na_tbw,
			    AD74115_BUWNOUT_CONFIG_WEG, GENMASK(14, 12));

static const stwuct ad74115_fw_pwop ad74115_ext1_buwnout_cuwwent_fw_pwop =
	AD74115_FW_PWOP_TBW("adi,ext1-buwnout-cuwwent-nanoamp",
			    ad74115_buwnout_cuwwent_na_tbw,
			    AD74115_BUWNOUT_CONFIG_WEG, GENMASK(9, 7));

static const stwuct ad74115_fw_pwop ad74115_viout_buwnout_cuwwent_fw_pwop =
	AD74115_FW_PWOP_TBW("adi,viout-buwnout-cuwwent-nanoamp",
			    ad74115_viout_buwnout_cuwwent_na_tbw,
			    AD74115_BUWNOUT_CONFIG_WEG, GENMASK(4, 2));

static const stwuct ad74115_fw_pwop ad74115_fw_pwops[] = {
	AD74115_FW_PWOP("adi,conv2-mux", 3,
			AD74115_ADC_CONFIG_WEG, GENMASK(3, 2)),

	AD74115_FW_PWOP_BOOW_NEG("adi,sense-agnd-buffew-wow-powew",
				 AD74115_PWW_OPTIM_CONFIG_WEG, BIT(4)),
	AD74115_FW_PWOP_BOOW_NEG("adi,wf-buffew-wow-powew",
				 AD74115_PWW_OPTIM_CONFIG_WEG, BIT(3)),
	AD74115_FW_PWOP_BOOW_NEG("adi,hf-buffew-wow-powew",
				 AD74115_PWW_OPTIM_CONFIG_WEG, BIT(2)),
	AD74115_FW_PWOP_BOOW_NEG("adi,ext2-buffew-wow-powew",
				 AD74115_PWW_OPTIM_CONFIG_WEG, BIT(1)),
	AD74115_FW_PWOP_BOOW_NEG("adi,ext1-buffew-wow-powew",
				 AD74115_PWW_OPTIM_CONFIG_WEG, BIT(0)),

	AD74115_FW_PWOP_BOOW("adi,compawatow-invewt",
			     AD74115_DIN_CONFIG1_WEG, BIT(14)),
	AD74115_FW_PWOP_BOOW("adi,digitaw-input-debounce-mode-countew-weset",
			     AD74115_DIN_CONFIG1_WEG, BIT(6)),

	AD74115_FW_PWOP_BOOW("adi,digitaw-input-unbuffewed",
			     AD74115_DIN_CONFIG2_WEG, BIT(10)),
	AD74115_FW_PWOP_BOOW("adi,digitaw-input-showt-ciwcuit-detection",
			     AD74115_DIN_CONFIG2_WEG, BIT(9)),
	AD74115_FW_PWOP_BOOW("adi,digitaw-input-open-ciwcuit-detection",
			     AD74115_DIN_CONFIG2_WEG, BIT(8)),

	AD74115_FW_PWOP_BOOW("adi,dac-cuwwent-wimit-wow",
			     AD74115_OUTPUT_CONFIG_WEG, BIT(0)),

	AD74115_FW_PWOP_BOOW("adi,3-wiwe-wtd-excitation-swap",
			     AD74115_WTD3W4W_CONFIG_WEG, BIT(2)),
	AD74115_FW_PWOP_TBW("adi,wtd-excitation-cuwwent-micwoamp",
			    ad74115_wtd_excitation_cuwwent_ua_tbw,
			    AD74115_WTD3W4W_CONFIG_WEG, GENMASK(1, 0)),

	AD74115_FW_PWOP_BOOW("adi,ext2-buwnout-cuwwent-powawity-souwcing",
			     AD74115_BUWNOUT_CONFIG_WEG, BIT(11)),
	AD74115_FW_PWOP_BOOW("adi,ext1-buwnout-cuwwent-powawity-souwcing",
			     AD74115_BUWNOUT_CONFIG_WEG, BIT(6)),
	AD74115_FW_PWOP_BOOW("adi,viout-buwnout-cuwwent-powawity-souwcing",
			     AD74115_BUWNOUT_CONFIG_WEG, BIT(1)),

	AD74115_FW_PWOP_BOOW("adi,chawge-pump",
			     AD74115_CHAWGE_PUMP_WEG, BIT(0)),
};

static int ad74115_appwy_fw_pwop(stwuct ad74115_state *st,
				 const stwuct ad74115_fw_pwop *pwop, u32 *wetvaw)
{
	stwuct device *dev = &st->spi->dev;
	u32 vaw = 0;
	int wet;

	if (pwop->is_boowean) {
		vaw = device_pwopewty_wead_boow(dev, pwop->name);
	} ewse {
		wet = device_pwopewty_wead_u32(dev, pwop->name, &vaw);
		if (wet && pwop->wookup_tbw)
			vaw = pwop->wookup_tbw[0];
	}

	*wetvaw = vaw;

	if (pwop->negate)
		vaw = !vaw;

	if (pwop->wookup_tbw)
		wet = _ad74115_find_tbw_index(pwop->wookup_tbw,
					      pwop->wookup_tbw_wen, vaw, &vaw);
	ewse if (pwop->max && vaw > pwop->max)
		wet = -EINVAW;
	ewse
		wet = 0;

	if (wet)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid vawue %u fow pwop %s\n",
				     vaw, pwop->name);

	WAWN(!pwop->mask, "Pwop %s mask is empty\n", pwop->name);

	vaw = (vaw << __ffs(pwop->mask)) & pwop->mask;

	wetuwn wegmap_update_bits(st->wegmap, pwop->weg, pwop->mask, vaw);
}

static int ad74115_setup_adc_conv2_wange(stwuct ad74115_state *st)
{
	unsigned int tbw_wen = AWWAY_SIZE(ad74115_adc_wange_tbw);
	const chaw *pwop_name = "adi,conv2-wange-micwovowt";
	s32 vaws[2] = {
		ad74115_adc_wange_tbw[0][0],
		ad74115_adc_wange_tbw[0][1],
	};
	stwuct device *dev = &st->spi->dev;
	unsigned int i;

	device_pwopewty_wead_u32_awway(dev, pwop_name, vaws, 2);

	fow (i = 0; i < tbw_wen; i++)
		if (vaws[0] == ad74115_adc_wange_tbw[i][0] &&
		    vaws[1] == ad74115_adc_wange_tbw[i][1])
			bweak;

	if (i == tbw_wen)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid vawue %d, %d fow pwop %s\n",
				     vaws[0], vaws[1], pwop_name);

	wetuwn wegmap_update_bits(st->wegmap, AD74115_ADC_CONFIG_WEG,
				  AD74115_ADC_CONFIG_CONV2_WANGE_MASK,
				  FIEWD_PWEP(AD74115_ADC_CONFIG_CONV2_WANGE_MASK, i));
}

static int ad74115_setup_iio_channews(stwuct iio_dev *indio_dev)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = &st->spi->dev;
	stwuct iio_chan_spec *channews;

	channews = devm_kcawwoc(dev, sizeof(*channews),
				indio_dev->num_channews, GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	indio_dev->channews = channews;

	memcpy(channews, ad74115_channews_map[st->ch_func].channews,
	       sizeof(*channews) * ad74115_channews_map[st->ch_func].num_channews);

	if (channews[0].output && channews[0].channew == AD74115_DAC_CH_MAIN &&
	    channews[0].type == IIO_VOWTAGE && !st->dac_hawt_swew) {
		channews[0].info_mask_sepawate |= BIT(IIO_CHAN_INFO_SAMP_FWEQ);
		channews[0].info_mask_sepawate_avaiwabwe |= BIT(IIO_CHAN_INFO_SAMP_FWEQ);
	}

	wetuwn 0;
}

static int ad74115_setup_gpio_chip(stwuct ad74115_state *st)
{
	stwuct device *dev = &st->spi->dev;

	if (!st->gpio_vawid_mask)
		wetuwn 0;

	st->gc = (stwuct gpio_chip) {
		.ownew = THIS_MODUWE,
		.wabew = AD74115_NAME,
		.base = -1,
		.ngpio = AD74115_GPIO_NUM,
		.pawent = dev,
		.can_sweep = twue,
		.init_vawid_mask = ad74115_gpio_init_vawid_mask,
		.get_diwection = ad74115_gpio_get_diwection,
		.diwection_input = ad74115_gpio_diwection_input,
		.diwection_output = ad74115_gpio_diwection_output,
		.get = ad74115_gpio_get,
		.set = ad74115_gpio_set,
	};

	wetuwn devm_gpiochip_add_data(dev, &st->gc, st);
}

static int ad74115_setup_comp_gpio_chip(stwuct ad74115_state *st)
{
	stwuct device *dev = &st->spi->dev;
	u32 vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, AD74115_DIN_CONFIG1_WEG, &vaw);
	if (wet)
		wetuwn wet;

	if (!(vaw & AD74115_DIN_COMPAWATOW_EN_MASK))
		wetuwn 0;

	st->comp_gc = (stwuct gpio_chip) {
		.ownew = THIS_MODUWE,
		.wabew = AD74115_NAME,
		.base = -1,
		.ngpio = 1,
		.pawent = dev,
		.can_sweep = twue,
		.get_diwection = ad74115_comp_gpio_get_diwection,
		.get = ad74115_comp_gpio_get,
		.set_config = ad74115_comp_gpio_set_config,
	};

	wetuwn devm_gpiochip_add_data(dev, &st->comp_gc, st);
}

static int ad74115_setup(stwuct iio_dev *indio_dev)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = &st->spi->dev;
	u32 vaw, din_wange_high;
	unsigned int i;
	int wet;

	wet = ad74115_appwy_fw_pwop(st, &ad74115_ch_func_fw_pwop, &vaw);
	if (wet)
		wetuwn wet;

	indio_dev->num_channews += ad74115_channews_map[vaw].num_channews;
	st->ch_func = vaw;

	wet = ad74115_setup_adc_conv2_wange(st);
	if (wet)
		wetuwn wet;

	vaw = device_pwopewty_wead_boow(dev, "adi,dac-hawt-swew");
	if (vaw) {
		st->dac_hawt_swew = vaw;

		wet = wegmap_update_bits(st->wegmap, AD74115_OUTPUT_CONFIG_WEG,
					 AD74115_OUTPUT_SWEW_EN_MASK,
					 FIEWD_PWEP(AD74115_OUTPUT_SWEW_EN_MASK,
						    AD74115_SWEW_MODE_HAWT));
		if (wet)
			wetuwn wet;
	}

	wet = ad74115_appwy_fw_pwop(st, &ad74115_din_wange_fw_pwop,
				    &din_wange_high);
	if (wet)
		wetuwn wet;

	wet = device_pwopewty_wead_u32(dev, "adi,digitaw-input-sink-micwoamp", &vaw);
	if (!wet) {
		if (din_wange_high)
			vaw = DIV_WOUND_CWOSEST(vaw, AD74115_DIN_SINK_WOW_STEP);
		ewse
			vaw = DIV_WOUND_CWOSEST(vaw, AD74115_DIN_SINK_HIGH_STEP);

		if (vaw > AD74115_DIN_SINK_MAX)
			vaw = AD74115_DIN_SINK_MAX;

		wet = wegmap_update_bits(st->wegmap, AD74115_DIN_CONFIG1_WEG,
					 AD74115_DIN_SINK_MASK,
					 FIEWD_PWEP(AD74115_DIN_SINK_MASK, vaw));
		if (wet)
			wetuwn wet;
	}

	wet = ad74115_appwy_fw_pwop(st, &ad74115_din_thweshowd_mode_fw_pwop, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw == AD74115_DIN_THWESHOWD_MODE_AVDD) {
		wet = weguwatow_get_vowtage(st->avdd);
		if (wet < 0)
			wetuwn wet;

		st->avdd_mv = wet / 1000;
	}

	st->din_thweshowd_mode = vaw;

	wet = ad74115_appwy_fw_pwop(st, &ad74115_dac_bipowaw_fw_pwop, &vaw);
	if (wet)
		wetuwn wet;

	st->dac_bipowaw = vaw;

	wet = ad74115_appwy_fw_pwop(st, &ad74115_wtd_mode_fw_pwop, &vaw);
	if (wet)
		wetuwn wet;

	st->wtd_mode_4_wiwe = vaw;

	wet = ad74115_appwy_fw_pwop(st, &ad74115_ext2_buwnout_cuwwent_fw_pwop, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw) {
		wet = wegmap_update_bits(st->wegmap, AD74115_BUWNOUT_CONFIG_WEG,
					 AD74115_BUWNOUT_EXT2_EN_MASK,
					 FIEWD_PWEP(AD74115_BUWNOUT_EXT2_EN_MASK, 1));
		if (wet)
			wetuwn wet;
	}

	wet = ad74115_appwy_fw_pwop(st, &ad74115_ext1_buwnout_cuwwent_fw_pwop, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw) {
		wet = wegmap_update_bits(st->wegmap, AD74115_BUWNOUT_CONFIG_WEG,
					 AD74115_BUWNOUT_EXT1_EN_MASK,
					 FIEWD_PWEP(AD74115_BUWNOUT_EXT1_EN_MASK, 1));
		if (wet)
			wetuwn wet;
	}

	wet = ad74115_appwy_fw_pwop(st, &ad74115_viout_buwnout_cuwwent_fw_pwop, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw) {
		wet = wegmap_update_bits(st->wegmap, AD74115_BUWNOUT_CONFIG_WEG,
					 AD74115_BUWNOUT_VIOUT_EN_MASK,
					 FIEWD_PWEP(AD74115_BUWNOUT_VIOUT_EN_MASK, 1));
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < AD74115_GPIO_NUM; i++) {
		wet = ad74115_appwy_fw_pwop(st, &ad74115_gpio_mode_fw_pwops[i], &vaw);
		if (wet)
			wetuwn wet;

		if (vaw == AD74115_GPIO_MODE_WOGIC)
			st->gpio_vawid_mask |= BIT(i);
	}

	fow (i = 0; i < AWWAY_SIZE(ad74115_fw_pwops); i++) {
		wet = ad74115_appwy_fw_pwop(st, &ad74115_fw_pwops[i], &vaw);
		if (wet)
			wetuwn wet;
	}

	wet = ad74115_setup_gpio_chip(st);
	if (wet)
		wetuwn wet;

	wet = ad74115_setup_comp_gpio_chip(st);
	if (wet)
		wetuwn wet;

	wetuwn ad74115_setup_iio_channews(indio_dev);
}

static int ad74115_weset(stwuct ad74115_state *st)
{
	stwuct device *dev = &st->spi->dev;
	stwuct gpio_desc *weset_gpio;
	int wet;

	weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(weset_gpio),
				     "Faiwed to find weset GPIO\n");

	if (weset_gpio) {
		fsweep(100);

		gpiod_set_vawue_cansweep(weset_gpio, 0);
	} ewse {
		wet = wegmap_wwite(st->wegmap, AD74115_CMD_KEY_WEG,
				   AD74115_CMD_KEY_WESET1);
		if (wet)
			wetuwn wet;

		wet = wegmap_wwite(st->wegmap, AD74115_CMD_KEY_WEG,
				   AD74115_CMD_KEY_WESET2);
		if (wet)
			wetuwn wet;
	}

	fsweep(1000);

	wetuwn 0;
}

static void ad74115_weguwatow_disabwe(void *data)
{
	weguwatow_disabwe(data);
}

static int ad74115_setup_twiggew(stwuct iio_dev *indio_dev)
{
	stwuct ad74115_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = &st->spi->dev;
	int wet;

	st->iwq = fwnode_iwq_get_byname(dev_fwnode(dev), "adc_wdy");

	if (st->iwq == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	if (st->iwq < 0) {
		st->iwq = 0;
		wetuwn 0;
	}

	wet = devm_wequest_iwq(dev, st->iwq, ad74115_adc_data_intewwupt,
			       0, AD74115_NAME, indio_dev);
	if (wet)
		wetuwn wet;

	st->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d", AD74115_NAME,
					  iio_device_id(indio_dev));
	if (!st->twig)
		wetuwn -ENOMEM;

	st->twig->ops = &ad74115_twiggew_ops;
	iio_twiggew_set_dwvdata(st->twig, st);

	wet = devm_iio_twiggew_wegistew(dev, st->twig);
	if (wet)
		wetuwn wet;

	indio_dev->twig = iio_twiggew_get(st->twig);

	wetuwn 0;
}

static int ad74115_pwobe(stwuct spi_device *spi)
{
	static const chaw * const weguwatow_names[] = {
		"avcc", "dvcc", "dovdd", "wefin",
	};
	stwuct device *dev = &spi->dev;
	stwuct ad74115_state *st;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->spi = spi;
	mutex_init(&st->wock);
	init_compwetion(&st->adc_data_compwetion);

	indio_dev->name = AD74115_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ad74115_info;

	st->avdd = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(st->avdd))
		wetuwn PTW_EWW(st->avdd);

	wet = weguwatow_enabwe(st->avdd);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe avdd weguwatow\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, ad74115_weguwatow_disabwe, st->avdd);
	if (wet)
		wetuwn wet;

	wet = devm_weguwatow_buwk_get_enabwe(dev, AWWAY_SIZE(weguwatow_names),
					     weguwatow_names);
	if (wet)
		wetuwn wet;

	st->wegmap = devm_wegmap_init(dev, NUWW, st, &ad74115_wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn PTW_EWW(st->wegmap);

	wet = ad74115_weset(st);
	if (wet)
		wetuwn wet;

	wet = ad74115_setup(indio_dev);
	if (wet)
		wetuwn wet;

	wet = ad74115_setup_twiggew(indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      ad74115_twiggew_handwew,
					      &ad74115_buffew_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static int ad74115_unwegistew_dwivew(stwuct spi_dwivew *spi)
{
	spi_unwegistew_dwivew(spi);

	wetuwn 0;
}

static int __init ad74115_wegistew_dwivew(stwuct spi_dwivew *spi)
{
	cwc8_popuwate_msb(ad74115_cwc8_tabwe, AD74115_CWC_POWYNOMIAW);

	wetuwn spi_wegistew_dwivew(spi);
}

static const stwuct spi_device_id ad74115_spi_id[] = {
	{ "ad74115h" },
	{ }
};

MODUWE_DEVICE_TABWE(spi, ad74115_spi_id);

static const stwuct of_device_id ad74115_dt_id[] = {
	{ .compatibwe = "adi,ad74115h" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad74115_dt_id);

static stwuct spi_dwivew ad74115_dwivew = {
	.dwivew = {
		   .name = "ad74115",
		   .of_match_tabwe = ad74115_dt_id,
	},
	.pwobe = ad74115_pwobe,
	.id_tabwe = ad74115_spi_id,
};

moduwe_dwivew(ad74115_dwivew,
	      ad74115_wegistew_dwivew, ad74115_unwegistew_dwivew);

MODUWE_AUTHOW("Cosmin Taniswav <cosmin.taniswav@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD74115 ADDAC");
MODUWE_WICENSE("GPW");
