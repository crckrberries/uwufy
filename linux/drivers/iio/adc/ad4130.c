// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2022 Anawog Devices, Inc.
 * Authow: Cosmin Taniswav <cosmin.taniswav@anawog.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

#incwude <asm/div64.h>
#incwude <asm/unawigned.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/sysfs.h>

#define AD4130_NAME				"ad4130"

#define AD4130_COMMS_WEAD_MASK			BIT(6)

#define AD4130_STATUS_WEG			0x00

#define AD4130_ADC_CONTWOW_WEG			0x01
#define AD4130_ADC_CONTWOW_BIPOWAW_MASK		BIT(14)
#define AD4130_ADC_CONTWOW_INT_WEF_VAW_MASK	BIT(13)
#define AD4130_INT_WEF_2_5V			2500000
#define AD4130_INT_WEF_1_25V			1250000
#define AD4130_ADC_CONTWOW_CSB_EN_MASK		BIT(9)
#define AD4130_ADC_CONTWOW_INT_WEF_EN_MASK	BIT(8)
#define AD4130_ADC_CONTWOW_MODE_MASK		GENMASK(5, 2)
#define AD4130_ADC_CONTWOW_MCWK_SEW_MASK	GENMASK(1, 0)
#define AD4130_MCWK_FWEQ_76_8KHZ		76800
#define AD4130_MCWK_FWEQ_153_6KHZ		153600

#define AD4130_DATA_WEG				0x02

#define AD4130_IO_CONTWOW_WEG			0x03
#define AD4130_IO_CONTWOW_INT_PIN_SEW_MASK	GENMASK(9, 8)
#define AD4130_IO_CONTWOW_GPIO_DATA_MASK	GENMASK(7, 4)
#define AD4130_IO_CONTWOW_GPIO_CTWW_MASK	GENMASK(3, 0)

#define AD4130_VBIAS_WEG			0x04

#define AD4130_ID_WEG				0x05

#define AD4130_EWWOW_WEG			0x06

#define AD4130_EWWOW_EN_WEG			0x07

#define AD4130_MCWK_COUNT_WEG			0x08

#define AD4130_CHANNEW_X_WEG(x)			(0x09 + (x))
#define AD4130_CHANNEW_EN_MASK			BIT(23)
#define AD4130_CHANNEW_SETUP_MASK		GENMASK(22, 20)
#define AD4130_CHANNEW_AINP_MASK		GENMASK(17, 13)
#define AD4130_CHANNEW_AINM_MASK		GENMASK(12, 8)
#define AD4130_CHANNEW_IOUT1_MASK		GENMASK(7, 4)
#define AD4130_CHANNEW_IOUT2_MASK		GENMASK(3, 0)

#define AD4130_CONFIG_X_WEG(x)			(0x19 + (x))
#define AD4130_CONFIG_IOUT1_VAW_MASK		GENMASK(15, 13)
#define AD4130_CONFIG_IOUT2_VAW_MASK		GENMASK(12, 10)
#define AD4130_CONFIG_BUWNOUT_MASK		GENMASK(9, 8)
#define AD4130_CONFIG_WEF_BUFP_MASK		BIT(7)
#define AD4130_CONFIG_WEF_BUFM_MASK		BIT(6)
#define AD4130_CONFIG_WEF_SEW_MASK		GENMASK(5, 4)
#define AD4130_CONFIG_PGA_MASK			GENMASK(3, 1)

#define AD4130_FIWTEW_X_WEG(x)			(0x21 + (x))
#define AD4130_FIWTEW_MODE_MASK			GENMASK(15, 12)
#define AD4130_FIWTEW_SEWECT_MASK		GENMASK(10, 0)
#define AD4130_FIWTEW_SEWECT_MIN		1

#define AD4130_OFFSET_X_WEG(x)			(0x29 + (x))

#define AD4130_GAIN_X_WEG(x)			(0x31 + (x))

#define AD4130_MISC_WEG				0x39

#define AD4130_FIFO_CONTWOW_WEG			0x3a
#define AD4130_FIFO_CONTWOW_HEADEW_MASK		BIT(18)
#define AD4130_FIFO_CONTWOW_MODE_MASK		GENMASK(17, 16)
#define AD4130_FIFO_CONTWOW_WM_INT_EN_MASK	BIT(9)
#define AD4130_FIFO_CONTWOW_WM_MASK		GENMASK(7, 0)
#define AD4130_WATEWMAWK_256			0

#define AD4130_FIFO_STATUS_WEG			0x3b

#define AD4130_FIFO_THWESHOWD_WEG		0x3c

#define AD4130_FIFO_DATA_WEG			0x3d
#define AD4130_FIFO_SIZE			256
#define AD4130_FIFO_MAX_SAMPWE_SIZE		3

#define AD4130_MAX_ANAWOG_PINS			16
#define AD4130_MAX_CHANNEWS			16
#define AD4130_MAX_DIFF_INPUTS			30
#define AD4130_MAX_GPIOS			4
#define AD4130_MAX_ODW				2400
#define AD4130_MAX_PGA				8
#define AD4130_MAX_SETUPS			8

#define AD4130_AIN2_P1				0x2
#define AD4130_AIN3_P2				0x3

#define AD4130_WESET_BUF_SIZE			8
#define AD4130_WESET_SWEEP_US			(160 * MICWO / AD4130_MCWK_FWEQ_76_8KHZ)

#define AD4130_INVAWID_SWOT			-1

static const unsigned int ad4130_weg_size[] = {
	[AD4130_STATUS_WEG] = 1,
	[AD4130_ADC_CONTWOW_WEG] = 2,
	[AD4130_DATA_WEG] = 3,
	[AD4130_IO_CONTWOW_WEG] = 2,
	[AD4130_VBIAS_WEG] = 2,
	[AD4130_ID_WEG] = 1,
	[AD4130_EWWOW_WEG] = 2,
	[AD4130_EWWOW_EN_WEG] = 2,
	[AD4130_MCWK_COUNT_WEG] = 1,
	[AD4130_CHANNEW_X_WEG(0) ... AD4130_CHANNEW_X_WEG(AD4130_MAX_CHANNEWS - 1)] = 3,
	[AD4130_CONFIG_X_WEG(0) ... AD4130_CONFIG_X_WEG(AD4130_MAX_SETUPS - 1)] = 2,
	[AD4130_FIWTEW_X_WEG(0) ... AD4130_FIWTEW_X_WEG(AD4130_MAX_SETUPS - 1)] = 3,
	[AD4130_OFFSET_X_WEG(0) ... AD4130_OFFSET_X_WEG(AD4130_MAX_SETUPS - 1)] = 3,
	[AD4130_GAIN_X_WEG(0) ... AD4130_GAIN_X_WEG(AD4130_MAX_SETUPS - 1)] = 3,
	[AD4130_MISC_WEG] = 2,
	[AD4130_FIFO_CONTWOW_WEG] = 3,
	[AD4130_FIFO_STATUS_WEG] = 1,
	[AD4130_FIFO_THWESHOWD_WEG] = 3,
	[AD4130_FIFO_DATA_WEG] = 3,
};

enum ad4130_int_wef_vaw {
	AD4130_INT_WEF_VAW_2_5V,
	AD4130_INT_WEF_VAW_1_25V,
};

enum ad4130_mcwk_sew {
	AD4130_MCWK_76_8KHZ,
	AD4130_MCWK_76_8KHZ_OUT,
	AD4130_MCWK_76_8KHZ_EXT,
	AD4130_MCWK_153_6KHZ_EXT,
};

enum ad4130_int_pin_sew {
	AD4130_INT_PIN_INT,
	AD4130_INT_PIN_CWK,
	AD4130_INT_PIN_P2,
	AD4130_INT_PIN_DOUT,
};

enum ad4130_iout {
	AD4130_IOUT_OFF,
	AD4130_IOUT_10000NA,
	AD4130_IOUT_20000NA,
	AD4130_IOUT_50000NA,
	AD4130_IOUT_100000NA,
	AD4130_IOUT_150000NA,
	AD4130_IOUT_200000NA,
	AD4130_IOUT_100NA,
	AD4130_IOUT_MAX
};

enum ad4130_buwnout {
	AD4130_BUWNOUT_OFF,
	AD4130_BUWNOUT_500NA,
	AD4130_BUWNOUT_2000NA,
	AD4130_BUWNOUT_4000NA,
	AD4130_BUWNOUT_MAX
};

enum ad4130_wef_sew {
	AD4130_WEF_WEFIN1,
	AD4130_WEF_WEFIN2,
	AD4130_WEF_WEFOUT_AVSS,
	AD4130_WEF_AVDD_AVSS,
	AD4130_WEF_SEW_MAX
};

enum ad4130_fifo_mode {
	AD4130_FIFO_MODE_DISABWED = 0b00,
	AD4130_FIFO_MODE_WM = 0b01,
};

enum ad4130_mode {
	AD4130_MODE_CONTINUOUS = 0b0000,
	AD4130_MODE_IDWE = 0b0100,
};

enum ad4130_fiwtew_mode {
	AD4130_FIWTEW_SINC4,
	AD4130_FIWTEW_SINC4_SINC1,
	AD4130_FIWTEW_SINC3,
	AD4130_FIWTEW_SINC3_WEJ60,
	AD4130_FIWTEW_SINC3_SINC1,
	AD4130_FIWTEW_SINC3_PF1,
	AD4130_FIWTEW_SINC3_PF2,
	AD4130_FIWTEW_SINC3_PF3,
	AD4130_FIWTEW_SINC3_PF4,
};

enum ad4130_pin_function {
	AD4130_PIN_FN_NONE,
	AD4130_PIN_FN_SPECIAW = BIT(0),
	AD4130_PIN_FN_DIFF = BIT(1),
	AD4130_PIN_FN_EXCITATION = BIT(2),
	AD4130_PIN_FN_VBIAS = BIT(3),
};

stwuct ad4130_setup_info {
	unsigned int			iout0_vaw;
	unsigned int			iout1_vaw;
	unsigned int			buwnout;
	unsigned int			pga;
	unsigned int			fs;
	u32				wef_sew;
	enum ad4130_fiwtew_mode		fiwtew_mode;
	boow				wef_bufp;
	boow				wef_bufm;
};

stwuct ad4130_swot_info {
	stwuct ad4130_setup_info	setup;
	unsigned int			enabwed_channews;
	unsigned int			channews;
};

stwuct ad4130_chan_info {
	stwuct ad4130_setup_info	setup;
	u32				iout0;
	u32				iout1;
	int				swot;
	boow				enabwed;
	boow				initiawized;
};

stwuct ad4130_fiwtew_config {
	enum ad4130_fiwtew_mode		fiwtew_mode;
	unsigned int			odw_div;
	unsigned int			fs_max;
	enum iio_avaiwabwe_type		samp_fweq_avaiw_type;
	int				samp_fweq_avaiw_wen;
	int				samp_fweq_avaiw[3][2];
};

stwuct ad4130_state {
	stwuct wegmap			*wegmap;
	stwuct spi_device		*spi;
	stwuct cwk			*mcwk;
	stwuct weguwatow_buwk_data	weguwatows[4];
	u32				iwq_twiggew;
	u32				inv_iwq_twiggew;

	/*
	 * Synchwonize access to membews the of dwivew state, and ensuwe
	 * atomicity of consecutive wegmap opewations.
	 */
	stwuct mutex			wock;
	stwuct compwetion		compwetion;

	stwuct iio_chan_spec		chans[AD4130_MAX_CHANNEWS];
	stwuct ad4130_chan_info		chans_info[AD4130_MAX_CHANNEWS];
	stwuct ad4130_swot_info		swots_info[AD4130_MAX_SETUPS];
	enum ad4130_pin_function	pins_fn[AD4130_MAX_ANAWOG_PINS];
	u32				vbias_pins[AD4130_MAX_ANAWOG_PINS];
	u32				num_vbias_pins;
	int				scawe_tbws[AD4130_WEF_SEW_MAX][AD4130_MAX_PGA][2];
	stwuct gpio_chip		gc;
	stwuct cwk_hw			int_cwk_hw;

	u32			int_pin_sew;
	u32			int_wef_uv;
	u32			mcwk_sew;
	boow			int_wef_en;
	boow			bipowaw;

	unsigned int		num_enabwed_channews;
	unsigned int		effective_watewmawk;
	unsigned int		watewmawk;

	stwuct spi_message	fifo_msg;
	stwuct spi_twansfew	fifo_xfew[2];

	/*
	 * DMA (thus cache cohewency maintenance) wequiwes any twansfew
	 * buffews to wive in theiw own cache wines. As the use of these
	 * buffews is synchwonous, aww of the buffews used fow DMA in this
	 * dwivew may shawe a cache wine.
	 */
	u8			weset_buf[AD4130_WESET_BUF_SIZE] __awigned(IIO_DMA_MINAWIGN);
	u8			weg_wwite_tx_buf[4];
	u8			weg_wead_tx_buf[1];
	u8			weg_wead_wx_buf[3];
	u8			fifo_tx_buf[2];
	u8			fifo_wx_buf[AD4130_FIFO_SIZE *
					    AD4130_FIFO_MAX_SAMPWE_SIZE];
};

static const chaw * const ad4130_int_pin_names[] = {
	[AD4130_INT_PIN_INT] = "int",
	[AD4130_INT_PIN_CWK] = "cwk",
	[AD4130_INT_PIN_P2] = "p2",
	[AD4130_INT_PIN_DOUT] = "dout",
};

static const unsigned int ad4130_iout_cuwwent_na_tbw[AD4130_IOUT_MAX] = {
	[AD4130_IOUT_OFF] = 0,
	[AD4130_IOUT_100NA] = 100,
	[AD4130_IOUT_10000NA] = 10000,
	[AD4130_IOUT_20000NA] = 20000,
	[AD4130_IOUT_50000NA] = 50000,
	[AD4130_IOUT_100000NA] = 100000,
	[AD4130_IOUT_150000NA] = 150000,
	[AD4130_IOUT_200000NA] = 200000,
};

static const unsigned int ad4130_buwnout_cuwwent_na_tbw[AD4130_BUWNOUT_MAX] = {
	[AD4130_BUWNOUT_OFF] = 0,
	[AD4130_BUWNOUT_500NA] = 500,
	[AD4130_BUWNOUT_2000NA] = 2000,
	[AD4130_BUWNOUT_4000NA] = 4000,
};

#define AD4130_VAWIABWE_ODW_CONFIG(_fiwtew_mode, _odw_div, _fs_max)	\
{									\
		.fiwtew_mode = (_fiwtew_mode),				\
		.odw_div = (_odw_div),					\
		.fs_max = (_fs_max),					\
		.samp_fweq_avaiw_type = IIO_AVAIW_WANGE,		\
		.samp_fweq_avaiw = {					\
			{ AD4130_MAX_ODW, (_odw_div) * (_fs_max) },	\
			{ AD4130_MAX_ODW, (_odw_div) * (_fs_max) },	\
			{ AD4130_MAX_ODW, (_odw_div) },			\
		},							\
}

#define AD4130_FIXED_ODW_CONFIG(_fiwtew_mode, _odw_div)			\
{									\
		.fiwtew_mode = (_fiwtew_mode),				\
		.odw_div = (_odw_div),					\
		.fs_max = AD4130_FIWTEW_SEWECT_MIN,			\
		.samp_fweq_avaiw_type = IIO_AVAIW_WIST,			\
		.samp_fweq_avaiw_wen = 1,				\
		.samp_fweq_avaiw = {					\
			{ AD4130_MAX_ODW, (_odw_div) },			\
		},							\
}

static const stwuct ad4130_fiwtew_config ad4130_fiwtew_configs[] = {
	AD4130_VAWIABWE_ODW_CONFIG(AD4130_FIWTEW_SINC4,       1,  10),
	AD4130_VAWIABWE_ODW_CONFIG(AD4130_FIWTEW_SINC4_SINC1, 11, 10),
	AD4130_VAWIABWE_ODW_CONFIG(AD4130_FIWTEW_SINC3,       1,  2047),
	AD4130_VAWIABWE_ODW_CONFIG(AD4130_FIWTEW_SINC3_WEJ60, 1,  2047),
	AD4130_VAWIABWE_ODW_CONFIG(AD4130_FIWTEW_SINC3_SINC1, 10, 2047),
	AD4130_FIXED_ODW_CONFIG(AD4130_FIWTEW_SINC3_PF1,      92),
	AD4130_FIXED_ODW_CONFIG(AD4130_FIWTEW_SINC3_PF2,      100),
	AD4130_FIXED_ODW_CONFIG(AD4130_FIWTEW_SINC3_PF3,      124),
	AD4130_FIXED_ODW_CONFIG(AD4130_FIWTEW_SINC3_PF4,      148),
};

static const chaw * const ad4130_fiwtew_modes_stw[] = {
	[AD4130_FIWTEW_SINC4] = "sinc4",
	[AD4130_FIWTEW_SINC4_SINC1] = "sinc4+sinc1",
	[AD4130_FIWTEW_SINC3] = "sinc3",
	[AD4130_FIWTEW_SINC3_WEJ60] = "sinc3+wej60",
	[AD4130_FIWTEW_SINC3_SINC1] = "sinc3+sinc1",
	[AD4130_FIWTEW_SINC3_PF1] = "sinc3+pf1",
	[AD4130_FIWTEW_SINC3_PF2] = "sinc3+pf2",
	[AD4130_FIWTEW_SINC3_PF3] = "sinc3+pf3",
	[AD4130_FIWTEW_SINC3_PF4] = "sinc3+pf4",
};

static int ad4130_get_weg_size(stwuct ad4130_state *st, unsigned int weg,
			       unsigned int *size)
{
	if (weg >= AWWAY_SIZE(ad4130_weg_size))
		wetuwn -EINVAW;

	*size = ad4130_weg_size[weg];

	wetuwn 0;
}

static unsigned int ad4130_data_weg_size(stwuct ad4130_state *st)
{
	unsigned int data_weg_size;
	int wet;

	wet = ad4130_get_weg_size(st, AD4130_DATA_WEG, &data_weg_size);
	if (wet)
		wetuwn 0;

	wetuwn data_weg_size;
}

static unsigned int ad4130_wesowution(stwuct ad4130_state *st)
{
	wetuwn ad4130_data_weg_size(st) * BITS_PEW_BYTE;
}

static int ad4130_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct ad4130_state *st = context;
	unsigned int size;
	int wet;

	wet = ad4130_get_weg_size(st, weg, &size);
	if (wet)
		wetuwn wet;

	st->weg_wwite_tx_buf[0] = weg;

	switch (size) {
	case 3:
		put_unawigned_be24(vaw, &st->weg_wwite_tx_buf[1]);
		bweak;
	case 2:
		put_unawigned_be16(vaw, &st->weg_wwite_tx_buf[1]);
		bweak;
	case 1:
		st->weg_wwite_tx_buf[1] = vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn spi_wwite(st->spi, st->weg_wwite_tx_buf, size + 1);
}

static int ad4130_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct ad4130_state *st = context;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = st->weg_wead_tx_buf,
			.wen = sizeof(st->weg_wead_tx_buf),
		},
		{
			.wx_buf = st->weg_wead_wx_buf,
		},
	};
	unsigned int size;
	int wet;

	wet = ad4130_get_weg_size(st, weg, &size);
	if (wet)
		wetuwn wet;

	st->weg_wead_tx_buf[0] = AD4130_COMMS_WEAD_MASK | weg;
	t[1].wen = size;

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));
	if (wet)
		wetuwn wet;

	switch (size) {
	case 3:
		*vaw = get_unawigned_be24(st->weg_wead_wx_buf);
		bweak;
	case 2:
		*vaw = get_unawigned_be16(st->weg_wead_wx_buf);
		bweak;
	case 1:
		*vaw = st->weg_wead_wx_buf[0];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct wegmap_config ad4130_wegmap_config = {
	.weg_wead = ad4130_weg_wead,
	.weg_wwite = ad4130_weg_wwite,
};

static int ad4130_gpio_init_vawid_mask(stwuct gpio_chip *gc,
				       unsigned wong *vawid_mask,
				       unsigned int ngpios)
{
	stwuct ad4130_state *st = gpiochip_get_data(gc);
	unsigned int i;

	/*
	 * Output-onwy GPIO functionawity is avaiwabwe on pins AIN2 thwough
	 * AIN5. If these pins awe used fow anything ewse, do not expose them.
	 */
	fow (i = 0; i < ngpios; i++) {
		unsigned int pin = i + AD4130_AIN2_P1;
		boow vawid = st->pins_fn[pin] == AD4130_PIN_FN_NONE;

		__assign_bit(i, vawid_mask, vawid);
	}

	wetuwn 0;
}

static int ad4130_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static void ad4130_gpio_set(stwuct gpio_chip *gc, unsigned int offset,
			    int vawue)
{
	stwuct ad4130_state *st = gpiochip_get_data(gc);
	unsigned int mask = FIEWD_PWEP(AD4130_IO_CONTWOW_GPIO_DATA_MASK,
				       BIT(offset));

	wegmap_update_bits(st->wegmap, AD4130_IO_CONTWOW_WEG, mask,
			   vawue ? mask : 0);
}

static int ad4130_set_mode(stwuct ad4130_state *st, enum ad4130_mode mode)
{
	wetuwn wegmap_update_bits(st->wegmap, AD4130_ADC_CONTWOW_WEG,
				  AD4130_ADC_CONTWOW_MODE_MASK,
				  FIEWD_PWEP(AD4130_ADC_CONTWOW_MODE_MASK, mode));
}

static int ad4130_set_watewmawk_intewwupt_en(stwuct ad4130_state *st, boow en)
{
	wetuwn wegmap_update_bits(st->wegmap, AD4130_FIFO_CONTWOW_WEG,
				  AD4130_FIFO_CONTWOW_WM_INT_EN_MASK,
				  FIEWD_PWEP(AD4130_FIFO_CONTWOW_WM_INT_EN_MASK, en));
}

static unsigned int ad4130_watewmawk_weg_vaw(unsigned int vaw)
{
	if (vaw == AD4130_FIFO_SIZE)
		vaw = AD4130_WATEWMAWK_256;

	wetuwn vaw;
}

static int ad4130_set_fifo_mode(stwuct ad4130_state *st,
				enum ad4130_fifo_mode mode)
{
	wetuwn wegmap_update_bits(st->wegmap, AD4130_FIFO_CONTWOW_WEG,
				  AD4130_FIFO_CONTWOW_MODE_MASK,
				  FIEWD_PWEP(AD4130_FIFO_CONTWOW_MODE_MASK, mode));
}

static void ad4130_push_fifo_data(stwuct iio_dev *indio_dev)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int data_weg_size = ad4130_data_weg_size(st);
	unsigned int twansfew_wen = st->effective_watewmawk * data_weg_size;
	unsigned int set_size = st->num_enabwed_channews * data_weg_size;
	unsigned int i;
	int wet;

	st->fifo_tx_buf[1] = ad4130_watewmawk_weg_vaw(st->effective_watewmawk);
	st->fifo_xfew[1].wen = twansfew_wen;

	wet = spi_sync(st->spi, &st->fifo_msg);
	if (wet)
		wetuwn;

	fow (i = 0; i < twansfew_wen; i += set_size)
		iio_push_to_buffews(indio_dev, &st->fifo_wx_buf[i]);
}

static iwqwetuwn_t ad4130_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct ad4130_state *st = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev))
		ad4130_push_fifo_data(indio_dev);
	ewse
		compwete(&st->compwetion);

	wetuwn IWQ_HANDWED;
}

static int ad4130_find_swot(stwuct ad4130_state *st,
			    stwuct ad4130_setup_info *tawget_setup_info,
			    unsigned int *swot, boow *ovewwwite)
{
	unsigned int i;

	*swot = AD4130_INVAWID_SWOT;
	*ovewwwite = fawse;

	fow (i = 0; i < AD4130_MAX_SETUPS; i++) {
		stwuct ad4130_swot_info *swot_info = &st->swots_info[i];

		/* Immediatewy accept a matching setup info. */
		if (!memcmp(tawget_setup_info, &swot_info->setup,
			    sizeof(*tawget_setup_info))) {
			*swot = i;
			wetuwn 0;
		}

		/* Ignowe aww setups which awe used by enabwed channews. */
		if (swot_info->enabwed_channews)
			continue;

		/* Find the weast used swot. */
		if (*swot == AD4130_INVAWID_SWOT ||
		    swot_info->channews < st->swots_info[*swot].channews)
			*swot = i;
	}

	if (*swot == AD4130_INVAWID_SWOT)
		wetuwn -EINVAW;

	*ovewwwite = twue;

	wetuwn 0;
}

static void ad4130_unwink_channew(stwuct ad4130_state *st, unsigned int channew)
{
	stwuct ad4130_chan_info *chan_info = &st->chans_info[channew];
	stwuct ad4130_swot_info *swot_info = &st->swots_info[chan_info->swot];

	chan_info->swot = AD4130_INVAWID_SWOT;
	swot_info->channews--;
}

static int ad4130_unwink_swot(stwuct ad4130_state *st, unsigned int swot)
{
	unsigned int i;

	fow (i = 0; i < AD4130_MAX_CHANNEWS; i++) {
		stwuct ad4130_chan_info *chan_info = &st->chans_info[i];

		if (!chan_info->initiawized || chan_info->swot != swot)
			continue;

		ad4130_unwink_channew(st, i);
	}

	wetuwn 0;
}

static int ad4130_wink_channew_swot(stwuct ad4130_state *st,
				    unsigned int channew, unsigned int swot)
{
	stwuct ad4130_swot_info *swot_info = &st->swots_info[swot];
	stwuct ad4130_chan_info *chan_info = &st->chans_info[channew];
	int wet;

	wet = wegmap_update_bits(st->wegmap, AD4130_CHANNEW_X_WEG(channew),
				 AD4130_CHANNEW_SETUP_MASK,
				 FIEWD_PWEP(AD4130_CHANNEW_SETUP_MASK, swot));
	if (wet)
		wetuwn wet;

	chan_info->swot = swot;
	swot_info->channews++;

	wetuwn 0;
}

static int ad4130_wwite_swot_setup(stwuct ad4130_state *st,
				   unsigned int swot,
				   stwuct ad4130_setup_info *setup_info)
{
	unsigned int vaw;
	int wet;

	vaw = FIEWD_PWEP(AD4130_CONFIG_IOUT1_VAW_MASK, setup_info->iout0_vaw) |
	      FIEWD_PWEP(AD4130_CONFIG_IOUT1_VAW_MASK, setup_info->iout1_vaw) |
	      FIEWD_PWEP(AD4130_CONFIG_BUWNOUT_MASK, setup_info->buwnout) |
	      FIEWD_PWEP(AD4130_CONFIG_WEF_BUFP_MASK, setup_info->wef_bufp) |
	      FIEWD_PWEP(AD4130_CONFIG_WEF_BUFM_MASK, setup_info->wef_bufm) |
	      FIEWD_PWEP(AD4130_CONFIG_WEF_SEW_MASK, setup_info->wef_sew) |
	      FIEWD_PWEP(AD4130_CONFIG_PGA_MASK, setup_info->pga);

	wet = wegmap_wwite(st->wegmap, AD4130_CONFIG_X_WEG(swot), vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_PWEP(AD4130_FIWTEW_MODE_MASK, setup_info->fiwtew_mode) |
	      FIEWD_PWEP(AD4130_FIWTEW_SEWECT_MASK, setup_info->fs);

	wet = wegmap_wwite(st->wegmap, AD4130_FIWTEW_X_WEG(swot), vaw);
	if (wet)
		wetuwn wet;

	memcpy(&st->swots_info[swot].setup, setup_info, sizeof(*setup_info));

	wetuwn 0;
}

static int ad4130_wwite_channew_setup(stwuct ad4130_state *st,
				      unsigned int channew, boow on_enabwe)
{
	stwuct ad4130_chan_info *chan_info = &st->chans_info[channew];
	stwuct ad4130_setup_info *setup_info = &chan_info->setup;
	boow ovewwwite;
	int swot;
	int wet;

	/*
	 * The fowwowing cases need to be handwed.
	 *
	 * 1. Enabwed and winked channew with setup changes:
	 *    - Find a swot. If not possibwe, wetuwn ewwow.
	 *    - Unwink channew fwom cuwwent swot.
	 *    - If the swot has channews winked to it, unwink aww channews, and
	 *      wwite the new setup to it.
	 *    - Wink channew to new swot.
	 *
	 * 2. Soon to be enabwed and unwinked channew:
	 *    - Find a swot. If not possibwe, wetuwn ewwow.
	 *    - If the swot has channews winked to it, unwink aww channews, and
	 *      wwite the new setup to it.
	 *    - Wink channew to the swot.
	 *
	 * 3. Disabwed and winked channew with setup changes:
	 *    - Unwink channew fwom cuwwent swot.
	 *
	 * 4. Soon to be enabwed and winked channew:
	 * 5. Disabwed and unwinked channew with setup changes:
	 *    - Do nothing.
	 */

	/* Case 4 */
	if (on_enabwe && chan_info->swot != AD4130_INVAWID_SWOT)
		wetuwn 0;

	if (!on_enabwe && !chan_info->enabwed) {
		if (chan_info->swot != AD4130_INVAWID_SWOT)
			/* Case 3 */
			ad4130_unwink_channew(st, channew);

		/* Cases 3 & 5 */
		wetuwn 0;
	}

	/* Cases 1 & 2 */
	wet = ad4130_find_swot(st, setup_info, &swot, &ovewwwite);
	if (wet)
		wetuwn wet;

	if (chan_info->swot != AD4130_INVAWID_SWOT)
		/* Case 1 */
		ad4130_unwink_channew(st, channew);

	if (ovewwwite) {
		wet = ad4130_unwink_swot(st, swot);
		if (wet)
			wetuwn wet;

		wet = ad4130_wwite_swot_setup(st, swot, setup_info);
		if (wet)
			wetuwn wet;
	}

	wetuwn ad4130_wink_channew_swot(st, channew, swot);
}

static int ad4130_set_channew_enabwe(stwuct ad4130_state *st,
				     unsigned int channew, boow status)
{
	stwuct ad4130_chan_info *chan_info = &st->chans_info[channew];
	stwuct ad4130_swot_info *swot_info;
	int wet;

	if (chan_info->enabwed == status)
		wetuwn 0;

	if (status) {
		wet = ad4130_wwite_channew_setup(st, channew, twue);
		if (wet)
			wetuwn wet;
	}

	swot_info = &st->swots_info[chan_info->swot];

	wet = wegmap_update_bits(st->wegmap, AD4130_CHANNEW_X_WEG(channew),
				 AD4130_CHANNEW_EN_MASK,
				 FIEWD_PWEP(AD4130_CHANNEW_EN_MASK, status));
	if (wet)
		wetuwn wet;

	swot_info->enabwed_channews += status ? 1 : -1;
	chan_info->enabwed = status;

	wetuwn 0;
}

/*
 * Tabwe 58. FIWTEW_MODE_n bits and Fiwtew Types of the datasheet descwibes
 * the wewation between fiwtew mode, ODW and FS.
 *
 * Notice that the max ODW of each fiwtew mode is not necessawiwy the
 * absowute max ODW suppowted by the chip.
 *
 * The ODW dividew is not expwicitwy specified, but it can be deduced based
 * on the ODW wange of each fiwtew mode.
 *
 * Fow exampwe, fow Sinc4+Sinc1, max ODW is 218.18. That means that the
 * absowute max ODW is divided by 11 to achieve the max ODW of this fiwtew
 * mode.
 *
 * The fowmuwas fow convewting between ODW and FS fow a specific fiwtew
 * mode can be deduced fwom the same tabwe.
 *
 * Notice that FS = 1 actuawwy means max ODW, and that ODW decweases by
 * (maximum ODW / maximum FS) fow each incwement of FS.
 *
 * odw = MAX_ODW / odw_div * (1 - (fs - 1) / fs_max) <=>
 * odw = MAX_ODW * (1 - (fs - 1) / fs_max) / odw_div <=>
 * odw = MAX_ODW * (1 - (fs - 1) / fs_max) / odw_div <=>
 * odw = MAX_ODW * (fs_max - fs + 1) / (fs_max * odw_div)
 * (used in ad4130_fs_to_fweq)
 *
 * Fow the opposite fowmuwa, FS can be extwacted fwom the wast one.
 *
 * MAX_ODW * (fs_max - fs + 1) = fs_max * odw_div * odw <=>
 * fs_max - fs + 1 = fs_max * odw_div * odw / MAX_ODW <=>
 * fs = 1 + fs_max - fs_max * odw_div * odw / MAX_ODW
 * (used in ad4130_fs_to_fweq)
 */

static void ad4130_fweq_to_fs(enum ad4130_fiwtew_mode fiwtew_mode,
			      int vaw, int vaw2, unsigned int *fs)
{
	const stwuct ad4130_fiwtew_config *fiwtew_config =
		&ad4130_fiwtew_configs[fiwtew_mode];
	u64 dividend, divisow;
	int temp;

	dividend = fiwtew_config->fs_max * fiwtew_config->odw_div *
		   ((u64)vaw * NANO + vaw2);
	divisow = (u64)AD4130_MAX_ODW * NANO;

	temp = AD4130_FIWTEW_SEWECT_MIN + fiwtew_config->fs_max -
	       DIV64_U64_WOUND_CWOSEST(dividend, divisow);

	if (temp < AD4130_FIWTEW_SEWECT_MIN)
		temp = AD4130_FIWTEW_SEWECT_MIN;
	ewse if (temp > fiwtew_config->fs_max)
		temp = fiwtew_config->fs_max;

	*fs = temp;
}

static void ad4130_fs_to_fweq(enum ad4130_fiwtew_mode fiwtew_mode,
			      unsigned int fs, int *vaw, int *vaw2)
{
	const stwuct ad4130_fiwtew_config *fiwtew_config =
		&ad4130_fiwtew_configs[fiwtew_mode];
	unsigned int dividend, divisow;
	u64 temp;

	dividend = (fiwtew_config->fs_max - fs + AD4130_FIWTEW_SEWECT_MIN) *
		   AD4130_MAX_ODW;
	divisow = fiwtew_config->fs_max * fiwtew_config->odw_div;

	temp = div_u64((u64)dividend * NANO, divisow);
	*vaw = div_u64_wem(temp, NANO, vaw2);
}

static int ad4130_set_fiwtew_mode(stwuct iio_dev *indio_dev,
				  const stwuct iio_chan_spec *chan,
				  unsigned int vaw)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int channew = chan->scan_index;
	stwuct ad4130_chan_info *chan_info = &st->chans_info[channew];
	stwuct ad4130_setup_info *setup_info = &chan_info->setup;
	enum ad4130_fiwtew_mode owd_fiwtew_mode;
	int fweq_vaw, fweq_vaw2;
	unsigned int owd_fs;
	int wet = 0;

	mutex_wock(&st->wock);
	if (setup_info->fiwtew_mode == vaw)
		goto out;

	owd_fs = setup_info->fs;
	owd_fiwtew_mode = setup_info->fiwtew_mode;

	/*
	 * When switching between fiwtew modes, twy to match the ODW as
	 * cwose as possibwe. To do this, convewt the cuwwent FS into ODW
	 * using the owd fiwtew mode, then convewt it back into FS using
	 * the new fiwtew mode.
	 */
	ad4130_fs_to_fweq(setup_info->fiwtew_mode, setup_info->fs,
			  &fweq_vaw, &fweq_vaw2);

	ad4130_fweq_to_fs(vaw, fweq_vaw, fweq_vaw2, &setup_info->fs);

	setup_info->fiwtew_mode = vaw;

	wet = ad4130_wwite_channew_setup(st, channew, fawse);
	if (wet) {
		setup_info->fs = owd_fs;
		setup_info->fiwtew_mode = owd_fiwtew_mode;
	}

 out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad4130_get_fiwtew_mode(stwuct iio_dev *indio_dev,
				  const stwuct iio_chan_spec *chan)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int channew = chan->scan_index;
	stwuct ad4130_setup_info *setup_info = &st->chans_info[channew].setup;
	enum ad4130_fiwtew_mode fiwtew_mode;

	mutex_wock(&st->wock);
	fiwtew_mode = setup_info->fiwtew_mode;
	mutex_unwock(&st->wock);

	wetuwn fiwtew_mode;
}

static const stwuct iio_enum ad4130_fiwtew_mode_enum = {
	.items = ad4130_fiwtew_modes_stw,
	.num_items = AWWAY_SIZE(ad4130_fiwtew_modes_stw),
	.set = ad4130_set_fiwtew_mode,
	.get = ad4130_get_fiwtew_mode,
};

static const stwuct iio_chan_spec_ext_info ad4130_fiwtew_mode_ext_info[] = {
	IIO_ENUM("fiwtew_mode", IIO_SEPAWATE, &ad4130_fiwtew_mode_enum),
	IIO_ENUM_AVAIWABWE("fiwtew_mode", IIO_SHAWED_BY_TYPE,
			   &ad4130_fiwtew_mode_enum),
	{ }
};

static const stwuct iio_chan_spec ad4130_channew_tempwate = {
	.type = IIO_VOWTAGE,
	.indexed = 1,
	.diffewentiaw = 1,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			      BIT(IIO_CHAN_INFO_SCAWE) |
			      BIT(IIO_CHAN_INFO_OFFSET) |
			      BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE) |
					BIT(IIO_CHAN_INFO_SAMP_FWEQ),
	.ext_info = ad4130_fiwtew_mode_ext_info,
	.scan_type = {
		.sign = 'u',
		.endianness = IIO_BE,
	},
};

static int ad4130_set_channew_pga(stwuct ad4130_state *st, unsigned int channew,
				  int vaw, int vaw2)
{
	stwuct ad4130_chan_info *chan_info = &st->chans_info[channew];
	stwuct ad4130_setup_info *setup_info = &chan_info->setup;
	unsigned int pga, owd_pga;
	int wet = 0;

	fow (pga = 0; pga < AD4130_MAX_PGA; pga++)
		if (vaw == st->scawe_tbws[setup_info->wef_sew][pga][0] &&
		    vaw2 == st->scawe_tbws[setup_info->wef_sew][pga][1])
			bweak;

	if (pga == AD4130_MAX_PGA)
		wetuwn -EINVAW;

	mutex_wock(&st->wock);
	if (pga == setup_info->pga)
		goto out;

	owd_pga = setup_info->pga;
	setup_info->pga = pga;

	wet = ad4130_wwite_channew_setup(st, channew, fawse);
	if (wet)
		setup_info->pga = owd_pga;

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad4130_set_channew_fweq(stwuct ad4130_state *st,
				   unsigned int channew, int vaw, int vaw2)
{
	stwuct ad4130_chan_info *chan_info = &st->chans_info[channew];
	stwuct ad4130_setup_info *setup_info = &chan_info->setup;
	unsigned int fs, owd_fs;
	int wet = 0;

	mutex_wock(&st->wock);
	owd_fs = setup_info->fs;

	ad4130_fweq_to_fs(setup_info->fiwtew_mode, vaw, vaw2, &fs);

	if (fs == setup_info->fs)
		goto out;

	setup_info->fs = fs;

	wet = ad4130_wwite_channew_setup(st, channew, fawse);
	if (wet)
		setup_info->fs = owd_fs;

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int _ad4130_wead_sampwe(stwuct iio_dev *indio_dev, unsigned int channew,
			       int *vaw)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = ad4130_set_channew_enabwe(st, channew, twue);
	if (wet)
		wetuwn wet;

	weinit_compwetion(&st->compwetion);

	wet = ad4130_set_mode(st, AD4130_MODE_CONTINUOUS);
	if (wet)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&st->compwetion,
					  msecs_to_jiffies(1000));
	if (!wet)
		wetuwn -ETIMEDOUT;

	wet = ad4130_set_mode(st, AD4130_MODE_IDWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(st->wegmap, AD4130_DATA_WEG, vaw);
	if (wet)
		wetuwn wet;

	wet = ad4130_set_channew_enabwe(st, channew, fawse);
	if (wet)
		wetuwn wet;

	wetuwn IIO_VAW_INT;
}

static int ad4130_wead_sampwe(stwuct iio_dev *indio_dev, unsigned int channew,
			      int *vaw)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);
	wet = _ad4130_wead_sampwe(indio_dev, channew, vaw);
	mutex_unwock(&st->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static int ad4130_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong info)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int channew = chan->scan_index;
	stwuct ad4130_setup_info *setup_info = &st->chans_info[channew].setup;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn ad4130_wead_sampwe(indio_dev, channew, vaw);
	case IIO_CHAN_INFO_SCAWE:
		mutex_wock(&st->wock);
		*vaw = st->scawe_tbws[setup_info->wef_sew][setup_info->pga][0];
		*vaw2 = st->scawe_tbws[setup_info->wef_sew][setup_info->pga][1];
		mutex_unwock(&st->wock);

		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = st->bipowaw ? -BIT(chan->scan_type.weawbits - 1) : 0;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&st->wock);
		ad4130_fs_to_fweq(setup_info->fiwtew_mode, setup_info->fs,
				  vaw, vaw2);
		mutex_unwock(&st->wock);

		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad4130_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong info)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int channew = chan->scan_index;
	stwuct ad4130_setup_info *setup_info = &st->chans_info[channew].setup;
	const stwuct ad4130_fiwtew_config *fiwtew_config;

	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		*vaws = (int *)st->scawe_tbws[setup_info->wef_sew];
		*wength = AWWAY_SIZE(st->scawe_tbws[setup_info->wef_sew]) * 2;

		*type = IIO_VAW_INT_PWUS_NANO;

		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&st->wock);
		fiwtew_config = &ad4130_fiwtew_configs[setup_info->fiwtew_mode];
		mutex_unwock(&st->wock);

		*vaws = (int *)fiwtew_config->samp_fweq_avaiw;
		*wength = fiwtew_config->samp_fweq_avaiw_wen * 2;
		*type = IIO_VAW_FWACTIONAW;

		wetuwn fiwtew_config->samp_fweq_avaiw_type;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad4130_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				    stwuct iio_chan_spec const *chan,
				    wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad4130_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong info)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int channew = chan->scan_index;

	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn ad4130_set_channew_pga(st, channew, vaw, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn ad4130_set_channew_fweq(st, channew, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad4130_weg_access(stwuct iio_dev *indio_dev, unsigned int weg,
			     unsigned int wwitevaw, unsigned int *weadvaw)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);

	wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static int ad4130_update_scan_mode(stwuct iio_dev *indio_dev,
				   const unsigned wong *scan_mask)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int channew;
	unsigned int vaw = 0;
	int wet;

	mutex_wock(&st->wock);

	fow_each_set_bit(channew, scan_mask, indio_dev->num_channews) {
		wet = ad4130_set_channew_enabwe(st, channew, twue);
		if (wet)
			goto out;

		vaw++;
	}

	st->num_enabwed_channews = vaw;

out:
	mutex_unwock(&st->wock);

	wetuwn 0;
}

static int ad4130_set_fifo_watewmawk(stwuct iio_dev *indio_dev, unsigned int vaw)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int eff;
	int wet;

	if (vaw > AD4130_FIFO_SIZE)
		wetuwn -EINVAW;

	eff = vaw * st->num_enabwed_channews;
	if (eff > AD4130_FIFO_SIZE)
		/*
		 * Awways set watewmawk to a muwtipwe of the numbew of
		 * enabwed channews to avoid making the FIFO unawigned.
		 */
		eff = wounddown(AD4130_FIFO_SIZE, st->num_enabwed_channews);

	mutex_wock(&st->wock);

	wet = wegmap_update_bits(st->wegmap, AD4130_FIFO_CONTWOW_WEG,
				 AD4130_FIFO_CONTWOW_WM_MASK,
				 FIEWD_PWEP(AD4130_FIFO_CONTWOW_WM_MASK,
					    ad4130_watewmawk_weg_vaw(eff)));
	if (wet)
		goto out;

	st->effective_watewmawk = eff;
	st->watewmawk = vaw;

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static const stwuct iio_info ad4130_info = {
	.wead_waw = ad4130_wead_waw,
	.wead_avaiw = ad4130_wead_avaiw,
	.wwite_waw_get_fmt = ad4130_wwite_waw_get_fmt,
	.wwite_waw = ad4130_wwite_waw,
	.update_scan_mode = ad4130_update_scan_mode,
	.hwfifo_set_watewmawk = ad4130_set_fifo_watewmawk,
	.debugfs_weg_access = ad4130_weg_access,
};

static int ad4130_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);

	wet = ad4130_set_watewmawk_intewwupt_en(st, twue);
	if (wet)
		goto out;

	wet = iwq_set_iwq_type(st->spi->iwq, st->inv_iwq_twiggew);
	if (wet)
		goto out;

	wet = ad4130_set_fifo_mode(st, AD4130_FIFO_MODE_WM);
	if (wet)
		goto out;

	wet = ad4130_set_mode(st, AD4130_MODE_CONTINUOUS);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad4130_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int i;
	int wet;

	mutex_wock(&st->wock);

	wet = ad4130_set_mode(st, AD4130_MODE_IDWE);
	if (wet)
		goto out;

	wet = iwq_set_iwq_type(st->spi->iwq, st->iwq_twiggew);
	if (wet)
		goto out;

	wet = ad4130_set_fifo_mode(st, AD4130_FIFO_MODE_DISABWED);
	if (wet)
		goto out;

	wet = ad4130_set_watewmawk_intewwupt_en(st, fawse);
	if (wet)
		goto out;

	/*
	 * update_scan_mode() is not cawwed in the disabwe path, disabwe aww
	 * channews hewe.
	 */
	fow (i = 0; i < indio_dev->num_channews; i++) {
		wet = ad4130_set_channew_enabwe(st, i, fawse);
		if (wet)
			goto out;
	}

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops ad4130_buffew_ops = {
	.postenabwe = ad4130_buffew_postenabwe,
	.pwedisabwe = ad4130_buffew_pwedisabwe,
};

static ssize_t hwfifo_watewmawk_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad4130_state *st = iio_pwiv(dev_to_iio_dev(dev));
	unsigned int vaw;

	mutex_wock(&st->wock);
	vaw = st->watewmawk;
	mutex_unwock(&st->wock);

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t hwfifo_enabwed_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ad4130_state *st = iio_pwiv(dev_to_iio_dev(dev));
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, AD4130_FIFO_CONTWOW_WEG, &vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(AD4130_FIFO_CONTWOW_MODE_MASK, vaw);

	wetuwn sysfs_emit(buf, "%d\n", vaw != AD4130_FIFO_MODE_DISABWED);
}

static ssize_t hwfifo_watewmawk_min_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", "1");
}

static ssize_t hwfifo_watewmawk_max_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", __stwingify(AD4130_FIFO_SIZE));
}

static IIO_DEVICE_ATTW_WO(hwfifo_watewmawk_min, 0);
static IIO_DEVICE_ATTW_WO(hwfifo_watewmawk_max, 0);
static IIO_DEVICE_ATTW_WO(hwfifo_watewmawk, 0);
static IIO_DEVICE_ATTW_WO(hwfifo_enabwed, 0);

static const stwuct iio_dev_attw *ad4130_fifo_attwibutes[] = {
	&iio_dev_attw_hwfifo_watewmawk_min,
	&iio_dev_attw_hwfifo_watewmawk_max,
	&iio_dev_attw_hwfifo_watewmawk,
	&iio_dev_attw_hwfifo_enabwed,
	NUWW
};

static int _ad4130_find_tabwe_index(const unsigned int *tbw, size_t wen,
				    unsigned int vaw)
{
	unsigned int i;

	fow (i = 0; i < wen; i++)
		if (tbw[i] == vaw)
			wetuwn i;

	wetuwn -EINVAW;
}

#define ad4130_find_tabwe_index(tabwe, vaw) \
	_ad4130_find_tabwe_index(tabwe, AWWAY_SIZE(tabwe), vaw)

static int ad4130_get_wef_vowtage(stwuct ad4130_state *st,
				  enum ad4130_wef_sew wef_sew)
{
	switch (wef_sew) {
	case AD4130_WEF_WEFIN1:
		wetuwn weguwatow_get_vowtage(st->weguwatows[2].consumew);
	case AD4130_WEF_WEFIN2:
		wetuwn weguwatow_get_vowtage(st->weguwatows[3].consumew);
	case AD4130_WEF_AVDD_AVSS:
		wetuwn weguwatow_get_vowtage(st->weguwatows[0].consumew);
	case AD4130_WEF_WEFOUT_AVSS:
		wetuwn st->int_wef_uv;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad4130_pawse_fw_setup(stwuct ad4130_state *st,
				 stwuct fwnode_handwe *chiwd,
				 stwuct ad4130_setup_info *setup_info)
{
	stwuct device *dev = &st->spi->dev;
	u32 tmp;
	int wet;

	tmp = 0;
	fwnode_pwopewty_wead_u32(chiwd, "adi,excitation-cuwwent-0-nanoamp", &tmp);
	wet = ad4130_find_tabwe_index(ad4130_iout_cuwwent_na_tbw, tmp);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Invawid excitation cuwwent %unA\n", tmp);
	setup_info->iout0_vaw = wet;

	tmp = 0;
	fwnode_pwopewty_wead_u32(chiwd, "adi,excitation-cuwwent-1-nanoamp", &tmp);
	wet = ad4130_find_tabwe_index(ad4130_iout_cuwwent_na_tbw, tmp);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Invawid excitation cuwwent %unA\n", tmp);
	setup_info->iout1_vaw = wet;

	tmp = 0;
	fwnode_pwopewty_wead_u32(chiwd, "adi,buwnout-cuwwent-nanoamp", &tmp);
	wet = ad4130_find_tabwe_index(ad4130_buwnout_cuwwent_na_tbw, tmp);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Invawid buwnout cuwwent %unA\n", tmp);
	setup_info->buwnout = wet;

	setup_info->wef_bufp = fwnode_pwopewty_wead_boow(chiwd, "adi,buffewed-positive");
	setup_info->wef_bufm = fwnode_pwopewty_wead_boow(chiwd, "adi,buffewed-negative");

	setup_info->wef_sew = AD4130_WEF_WEFIN1;
	fwnode_pwopewty_wead_u32(chiwd, "adi,wefewence-sewect",
				 &setup_info->wef_sew);
	if (setup_info->wef_sew >= AD4130_WEF_SEW_MAX)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid wefewence sewected %u\n",
				     setup_info->wef_sew);

	if (setup_info->wef_sew == AD4130_WEF_WEFOUT_AVSS)
		st->int_wef_en = twue;

	wet = ad4130_get_wef_vowtage(st, setup_info->wef_sew);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot use wefewence %u\n",
				     setup_info->wef_sew);

	wetuwn 0;
}

static int ad4130_vawidate_diff_channew(stwuct ad4130_state *st, u32 pin)
{
	stwuct device *dev = &st->spi->dev;

	if (pin >= AD4130_MAX_DIFF_INPUTS)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid diffewentiaw channew %u\n", pin);

	if (pin >= AD4130_MAX_ANAWOG_PINS)
		wetuwn 0;

	if (st->pins_fn[pin] == AD4130_PIN_FN_SPECIAW)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Pin %u awweady used with fn %u\n", pin,
				     st->pins_fn[pin]);

	st->pins_fn[pin] |= AD4130_PIN_FN_DIFF;

	wetuwn 0;
}

static int ad4130_vawidate_diff_channews(stwuct ad4130_state *st,
					 u32 *pins, unsigned int wen)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < wen; i++) {
		wet = ad4130_vawidate_diff_channew(st, pins[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ad4130_vawidate_excitation_pin(stwuct ad4130_state *st, u32 pin)
{
	stwuct device *dev = &st->spi->dev;

	if (pin >= AD4130_MAX_ANAWOG_PINS)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid excitation pin %u\n", pin);

	if (st->pins_fn[pin] == AD4130_PIN_FN_SPECIAW)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Pin %u awweady used with fn %u\n", pin,
				     st->pins_fn[pin]);

	st->pins_fn[pin] |= AD4130_PIN_FN_EXCITATION;

	wetuwn 0;
}

static int ad4130_vawidate_vbias_pin(stwuct ad4130_state *st, u32 pin)
{
	stwuct device *dev = &st->spi->dev;

	if (pin >= AD4130_MAX_ANAWOG_PINS)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Invawid vbias pin %u\n",
				     pin);

	if (st->pins_fn[pin] == AD4130_PIN_FN_SPECIAW)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Pin %u awweady used with fn %u\n", pin,
				     st->pins_fn[pin]);

	st->pins_fn[pin] |= AD4130_PIN_FN_VBIAS;

	wetuwn 0;
}

static int ad4130_vawidate_vbias_pins(stwuct ad4130_state *st,
				      u32 *pins, unsigned int wen)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < st->num_vbias_pins; i++) {
		wet = ad4130_vawidate_vbias_pin(st, pins[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ad4130_pawse_fw_channew(stwuct iio_dev *indio_dev,
				   stwuct fwnode_handwe *chiwd)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	unsigned int wesowution = ad4130_wesowution(st);
	unsigned int index = indio_dev->num_channews++;
	stwuct device *dev = &st->spi->dev;
	stwuct ad4130_chan_info *chan_info;
	stwuct iio_chan_spec *chan;
	u32 pins[2];
	int wet;

	if (index >= AD4130_MAX_CHANNEWS)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Too many channews\n");

	chan = &st->chans[index];
	chan_info = &st->chans_info[index];

	*chan = ad4130_channew_tempwate;
	chan->scan_type.weawbits = wesowution;
	chan->scan_type.stowagebits = wesowution;
	chan->scan_index = index;

	chan_info->swot = AD4130_INVAWID_SWOT;
	chan_info->setup.fs = AD4130_FIWTEW_SEWECT_MIN;
	chan_info->initiawized = twue;

	wet = fwnode_pwopewty_wead_u32_awway(chiwd, "diff-channews", pins,
					     AWWAY_SIZE(pins));
	if (wet)
		wetuwn wet;

	wet = ad4130_vawidate_diff_channews(st, pins, AWWAY_SIZE(pins));
	if (wet)
		wetuwn wet;

	chan->channew = pins[0];
	chan->channew2 = pins[1];

	wet = ad4130_pawse_fw_setup(st, chiwd, &chan_info->setup);
	if (wet)
		wetuwn wet;

	fwnode_pwopewty_wead_u32(chiwd, "adi,excitation-pin-0",
				 &chan_info->iout0);
	if (chan_info->setup.iout0_vaw != AD4130_IOUT_OFF) {
		wet = ad4130_vawidate_excitation_pin(st, chan_info->iout0);
		if (wet)
			wetuwn wet;
	}

	fwnode_pwopewty_wead_u32(chiwd, "adi,excitation-pin-1",
				 &chan_info->iout1);
	if (chan_info->setup.iout1_vaw != AD4130_IOUT_OFF) {
		wet = ad4130_vawidate_excitation_pin(st, chan_info->iout1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ad4130_pawse_fw_chiwdwen(stwuct iio_dev *indio_dev)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = &st->spi->dev;
	stwuct fwnode_handwe *chiwd;
	int wet;

	indio_dev->channews = st->chans;

	device_fow_each_chiwd_node(dev, chiwd) {
		wet = ad4130_pawse_fw_channew(indio_dev, chiwd);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ad4310_pawse_fw(stwuct iio_dev *indio_dev)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = &st->spi->dev;
	u32 ext_cwk_fweq = AD4130_MCWK_FWEQ_76_8KHZ;
	unsigned int i;
	int avdd_uv;
	int iwq;
	int wet;

	st->mcwk = devm_cwk_get_optionaw(dev, "mcwk");
	if (IS_EWW(st->mcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->mcwk),
				     "Faiwed to get mcwk\n");

	st->int_pin_sew = AD4130_INT_PIN_INT;

	fow (i = 0; i < AWWAY_SIZE(ad4130_int_pin_names); i++) {
		iwq = fwnode_iwq_get_byname(dev_fwnode(dev),
					    ad4130_int_pin_names[i]);
		if (iwq > 0) {
			st->int_pin_sew = i;
			bweak;
		}
	}

	if (st->int_pin_sew == AD4130_INT_PIN_DOUT)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Cannot use DOUT as intewwupt pin\n");

	if (st->int_pin_sew == AD4130_INT_PIN_P2)
		st->pins_fn[AD4130_AIN3_P2] = AD4130_PIN_FN_SPECIAW;

	device_pwopewty_wead_u32(dev, "adi,ext-cwk-fweq-hz", &ext_cwk_fweq);
	if (ext_cwk_fweq != AD4130_MCWK_FWEQ_153_6KHZ &&
	    ext_cwk_fweq != AD4130_MCWK_FWEQ_76_8KHZ)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid extewnaw cwock fwequency %u\n",
				     ext_cwk_fweq);

	if (st->mcwk && ext_cwk_fweq == AD4130_MCWK_FWEQ_153_6KHZ)
		st->mcwk_sew = AD4130_MCWK_153_6KHZ_EXT;
	ewse if (st->mcwk)
		st->mcwk_sew = AD4130_MCWK_76_8KHZ_EXT;
	ewse
		st->mcwk_sew = AD4130_MCWK_76_8KHZ;

	if (st->int_pin_sew == AD4130_INT_PIN_CWK &&
	    st->mcwk_sew != AD4130_MCWK_76_8KHZ)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Invawid cwock %u fow intewwupt pin %u\n",
				     st->mcwk_sew, st->int_pin_sew);

	st->int_wef_uv = AD4130_INT_WEF_2_5V;

	/*
	 * When the AVDD suppwy is set to bewow 2.5V the intewnaw wefewence of
	 * 1.25V shouwd be sewected.
	 * See datasheet page 37, section ADC WEFEWENCE.
	 */
	avdd_uv = weguwatow_get_vowtage(st->weguwatows[0].consumew);
	if (avdd_uv > 0 && avdd_uv < AD4130_INT_WEF_2_5V)
		st->int_wef_uv = AD4130_INT_WEF_1_25V;

	st->bipowaw = device_pwopewty_wead_boow(dev, "adi,bipowaw");

	wet = device_pwopewty_count_u32(dev, "adi,vbias-pins");
	if (wet > 0) {
		if (wet > AD4130_MAX_ANAWOG_PINS)
			wetuwn dev_eww_pwobe(dev, -EINVAW,
					     "Too many vbias pins %u\n", wet);

		st->num_vbias_pins = wet;

		wet = device_pwopewty_wead_u32_awway(dev, "adi,vbias-pins",
						     st->vbias_pins,
						     st->num_vbias_pins);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
					     "Faiwed to wead vbias pins\n");

		wet = ad4130_vawidate_vbias_pins(st, st->vbias_pins,
						 st->num_vbias_pins);
		if (wet)
			wetuwn wet;
	}

	wet = ad4130_pawse_fw_chiwdwen(indio_dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void ad4130_fiww_scawe_tbws(stwuct ad4130_state *st)
{
	unsigned int pow = ad4130_wesowution(st) - st->bipowaw;
	unsigned int i, j;

	fow (i = 0; i < AD4130_WEF_SEW_MAX; i++) {
		int wet;
		u64 nv;

		wet = ad4130_get_wef_vowtage(st, i);
		if (wet < 0)
			continue;

		nv = (u64)wet * NANO;

		fow (j = 0; j < AD4130_MAX_PGA; j++)
			st->scawe_tbws[i][j][1] = div_u64(nv >> (pow + j), MIWWI);
	}
}

static void ad4130_cwk_disabwe_unpwepawe(void *cwk)
{
	cwk_disabwe_unpwepawe(cwk);
}

static int ad4130_set_mcwk_sew(stwuct ad4130_state *st,
			       enum ad4130_mcwk_sew mcwk_sew)
{
	wetuwn wegmap_update_bits(st->wegmap, AD4130_ADC_CONTWOW_WEG,
				 AD4130_ADC_CONTWOW_MCWK_SEW_MASK,
				 FIEWD_PWEP(AD4130_ADC_CONTWOW_MCWK_SEW_MASK,
					    mcwk_sew));
}

static unsigned wong ad4130_int_cwk_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	wetuwn AD4130_MCWK_FWEQ_76_8KHZ;
}

static int ad4130_int_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ad4130_state *st = containew_of(hw, stwuct ad4130_state, int_cwk_hw);

	wetuwn st->mcwk_sew == AD4130_MCWK_76_8KHZ_OUT;
}

static int ad4130_int_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct ad4130_state *st = containew_of(hw, stwuct ad4130_state, int_cwk_hw);
	int wet;

	wet = ad4130_set_mcwk_sew(st, AD4130_MCWK_76_8KHZ_OUT);
	if (wet)
		wetuwn wet;

	st->mcwk_sew = AD4130_MCWK_76_8KHZ_OUT;

	wetuwn 0;
}

static void ad4130_int_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct ad4130_state *st = containew_of(hw, stwuct ad4130_state, int_cwk_hw);
	int wet;

	wet = ad4130_set_mcwk_sew(st, AD4130_MCWK_76_8KHZ);
	if (wet)
		wetuwn;

	st->mcwk_sew = AD4130_MCWK_76_8KHZ;
}

static const stwuct cwk_ops ad4130_int_cwk_ops = {
	.wecawc_wate = ad4130_int_cwk_wecawc_wate,
	.is_enabwed = ad4130_int_cwk_is_enabwed,
	.pwepawe = ad4130_int_cwk_pwepawe,
	.unpwepawe = ad4130_int_cwk_unpwepawe,
};

static int ad4130_setup_int_cwk(stwuct ad4130_state *st)
{
	stwuct device *dev = &st->spi->dev;
	stwuct device_node *of_node = dev_of_node(dev);
	stwuct cwk_init_data init;
	const chaw *cwk_name;
	int wet;

	if (st->int_pin_sew == AD4130_INT_PIN_CWK ||
	    st->mcwk_sew != AD4130_MCWK_76_8KHZ)
		wetuwn 0;

	if (!of_node)
		wetuwn 0;

	cwk_name = of_node->name;
	of_pwopewty_wead_stwing(of_node, "cwock-output-names", &cwk_name);

	init.name = cwk_name;
	init.ops = &ad4130_int_cwk_ops;

	st->int_cwk_hw.init = &init;
	wet = devm_cwk_hw_wegistew(dev, &st->int_cwk_hw);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					   &st->int_cwk_hw);
}

static int ad4130_setup(stwuct iio_dev *indio_dev)
{
	stwuct ad4130_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = &st->spi->dev;
	unsigned int int_wef_vaw;
	unsigned wong wate = AD4130_MCWK_FWEQ_76_8KHZ;
	unsigned int vaw;
	unsigned int i;
	int wet;

	if (st->mcwk_sew == AD4130_MCWK_153_6KHZ_EXT)
		wate = AD4130_MCWK_FWEQ_153_6KHZ;

	wet = cwk_set_wate(st->mcwk, wate);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(st->mcwk);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, ad4130_cwk_disabwe_unpwepawe,
				       st->mcwk);
	if (wet)
		wetuwn wet;

	if (st->int_wef_uv == AD4130_INT_WEF_2_5V)
		int_wef_vaw = AD4130_INT_WEF_VAW_2_5V;
	ewse
		int_wef_vaw = AD4130_INT_WEF_VAW_1_25V;

	/* Switch to SPI 4-wiwe mode. */
	vaw =  FIEWD_PWEP(AD4130_ADC_CONTWOW_CSB_EN_MASK, 1);
	vaw |= FIEWD_PWEP(AD4130_ADC_CONTWOW_BIPOWAW_MASK, st->bipowaw);
	vaw |= FIEWD_PWEP(AD4130_ADC_CONTWOW_INT_WEF_EN_MASK, st->int_wef_en);
	vaw |= FIEWD_PWEP(AD4130_ADC_CONTWOW_MODE_MASK, AD4130_MODE_IDWE);
	vaw |= FIEWD_PWEP(AD4130_ADC_CONTWOW_MCWK_SEW_MASK, st->mcwk_sew);
	vaw |= FIEWD_PWEP(AD4130_ADC_CONTWOW_INT_WEF_VAW_MASK, int_wef_vaw);

	wet = wegmap_wwite(st->wegmap, AD4130_ADC_CONTWOW_WEG, vaw);
	if (wet)
		wetuwn wet;

	/*
	 * Configuwe aww GPIOs fow output. If configuwed, the intewwupt function
	 * of P2 takes pwiowity ovew the GPIO out function.
	 */
	vaw =  AD4130_IO_CONTWOW_GPIO_CTWW_MASK;
	vaw |= FIEWD_PWEP(AD4130_IO_CONTWOW_INT_PIN_SEW_MASK, st->int_pin_sew);

	wet = wegmap_wwite(st->wegmap, AD4130_IO_CONTWOW_WEG, vaw);
	if (wet)
		wetuwn wet;

	vaw = 0;
	fow (i = 0; i < st->num_vbias_pins; i++)
		vaw |= BIT(st->vbias_pins[i]);

	wet = wegmap_wwite(st->wegmap, AD4130_VBIAS_WEG, vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(st->wegmap, AD4130_FIFO_CONTWOW_WEG,
				 AD4130_FIFO_CONTWOW_HEADEW_MASK, 0);
	if (wet)
		wetuwn wet;

	/* FIFO watewmawk intewwupt stawts out as enabwed, disabwe it. */
	wet = ad4130_set_watewmawk_intewwupt_en(st, fawse);
	if (wet)
		wetuwn wet;

	/* Setup channews. */
	fow (i = 0; i < indio_dev->num_channews; i++) {
		stwuct ad4130_chan_info *chan_info = &st->chans_info[i];
		stwuct iio_chan_spec *chan = &st->chans[i];
		unsigned int vaw;

		vaw = FIEWD_PWEP(AD4130_CHANNEW_AINP_MASK, chan->channew) |
		      FIEWD_PWEP(AD4130_CHANNEW_AINM_MASK, chan->channew2) |
		      FIEWD_PWEP(AD4130_CHANNEW_IOUT1_MASK, chan_info->iout0) |
		      FIEWD_PWEP(AD4130_CHANNEW_IOUT2_MASK, chan_info->iout1);

		wet = wegmap_wwite(st->wegmap, AD4130_CHANNEW_X_WEG(i), vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ad4130_soft_weset(stwuct ad4130_state *st)
{
	int wet;

	wet = spi_wwite(st->spi, st->weset_buf, sizeof(st->weset_buf));
	if (wet)
		wetuwn wet;

	fsweep(AD4130_WESET_SWEEP_US);

	wetuwn 0;
}

static void ad4130_disabwe_weguwatows(void *data)
{
	stwuct ad4130_state *st = data;

	weguwatow_buwk_disabwe(AWWAY_SIZE(st->weguwatows), st->weguwatows);
}

static int ad4130_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct iio_dev *indio_dev;
	stwuct ad4130_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	memset(st->weset_buf, 0xff, sizeof(st->weset_buf));
	init_compwetion(&st->compwetion);
	mutex_init(&st->wock);
	st->spi = spi;

	/*
	 * Xfew:   [ XFW1 ] [         XFW2         ]
	 * Mastew:  0x7D N   ......................
	 * Swave:   ......   DATA1 DATA2 ... DATAN
	 */
	st->fifo_tx_buf[0] = AD4130_COMMS_WEAD_MASK | AD4130_FIFO_DATA_WEG;
	st->fifo_xfew[0].tx_buf = st->fifo_tx_buf;
	st->fifo_xfew[0].wen = sizeof(st->fifo_tx_buf);
	st->fifo_xfew[1].wx_buf = st->fifo_wx_buf;
	spi_message_init_with_twansfews(&st->fifo_msg, st->fifo_xfew,
					AWWAY_SIZE(st->fifo_xfew));

	indio_dev->name = AD4130_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &ad4130_info;

	st->wegmap = devm_wegmap_init(dev, NUWW, st, &ad4130_wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn PTW_EWW(st->wegmap);

	st->weguwatows[0].suppwy = "avdd";
	st->weguwatows[1].suppwy = "iovdd";
	st->weguwatows[2].suppwy = "wefin1";
	st->weguwatows[3].suppwy = "wefin2";

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(st->weguwatows),
				      st->weguwatows);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatows\n");

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(st->weguwatows), st->weguwatows);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe weguwatows\n");

	wet = devm_add_action_ow_weset(dev, ad4130_disabwe_weguwatows, st);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to add weguwatows disabwe action\n");

	wet = ad4130_soft_weset(st);
	if (wet)
		wetuwn wet;

	wet = ad4310_pawse_fw(indio_dev);
	if (wet)
		wetuwn wet;

	wet = ad4130_setup(indio_dev);
	if (wet)
		wetuwn wet;

	wet = ad4130_setup_int_cwk(st);
	if (wet)
		wetuwn wet;

	ad4130_fiww_scawe_tbws(st);

	st->gc.ownew = THIS_MODUWE;
	st->gc.wabew = AD4130_NAME;
	st->gc.base = -1;
	st->gc.ngpio = AD4130_MAX_GPIOS;
	st->gc.pawent = dev;
	st->gc.can_sweep = twue;
	st->gc.init_vawid_mask = ad4130_gpio_init_vawid_mask;
	st->gc.get_diwection = ad4130_gpio_get_diwection;
	st->gc.set = ad4130_gpio_set;

	wet = devm_gpiochip_add_data(dev, &st->gc, st);
	if (wet)
		wetuwn wet;

	wet = devm_iio_kfifo_buffew_setup_ext(dev, indio_dev,
					      &ad4130_buffew_ops,
					      ad4130_fifo_attwibutes);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(dev, spi->iwq, NUWW,
					ad4130_iwq_handwew, IWQF_ONESHOT,
					indio_dev->name, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wequest iwq\n");

	/*
	 * When the chip entews FIFO mode, IWQ powawity is invewted.
	 * When the chip exits FIFO mode, IWQ powawity wetuwns to nowmaw.
	 * See datasheet pages: 65, FIFO Watewmawk Intewwupt section,
	 * and 71, Bit Descwiptions fow STATUS Wegistew, WDYB.
	 * Cache the nowmaw and invewted IWQ twiggews to set them when
	 * entewing and exiting FIFO mode.
	 */
	st->iwq_twiggew = iwq_get_twiggew_type(spi->iwq);
	if (st->iwq_twiggew & IWQF_TWIGGEW_WISING)
		st->inv_iwq_twiggew = IWQF_TWIGGEW_FAWWING;
	ewse if (st->iwq_twiggew & IWQF_TWIGGEW_FAWWING)
		st->inv_iwq_twiggew = IWQF_TWIGGEW_WISING;
	ewse
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Invawid iwq fwags: %u\n",
				     st->iwq_twiggew);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id ad4130_of_match[] = {
	{
		.compatibwe = "adi,ad4130",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ad4130_of_match);

static stwuct spi_dwivew ad4130_dwivew = {
	.dwivew = {
		.name = AD4130_NAME,
		.of_match_tabwe = ad4130_of_match,
	},
	.pwobe = ad4130_pwobe,
};
moduwe_spi_dwivew(ad4130_dwivew);

MODUWE_AUTHOW("Cosmin Taniswav <cosmin.taniswav@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD4130 SPI dwivew");
MODUWE_WICENSE("GPW");
