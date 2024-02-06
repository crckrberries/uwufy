// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Anawog Devices AD3552W
 * Digitaw to Anawog convewtew dwivew
 *
 * Copywight 2021 Anawog Devices Inc.
 */
#incwude <asm/unawigned.h>
#incwude <winux/device.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

/* Wegistew addwesses */
/* Pwimawy addwess space */
#define AD3552W_WEG_ADDW_INTEWFACE_CONFIG_A		0x00
#define   AD3552W_MASK_SOFTWAWE_WESET			(BIT(7) | BIT(0))
#define   AD3552W_MASK_ADDW_ASCENSION			BIT(5)
#define   AD3552W_MASK_SDO_ACTIVE			BIT(4)
#define AD3552W_WEG_ADDW_INTEWFACE_CONFIG_B		0x01
#define   AD3552W_MASK_SINGWE_INST			BIT(7)
#define   AD3552W_MASK_SHOWT_INSTWUCTION		BIT(3)
#define AD3552W_WEG_ADDW_DEVICE_CONFIG			0x02
#define   AD3552W_MASK_DEVICE_STATUS(n)			BIT(4 + (n))
#define   AD3552W_MASK_CUSTOM_MODES			GENMASK(3, 2)
#define   AD3552W_MASK_OPEWATING_MODES			GENMASK(1, 0)
#define AD3552W_WEG_ADDW_CHIP_TYPE			0x03
#define   AD3552W_MASK_CWASS				GENMASK(7, 0)
#define AD3552W_WEG_ADDW_PWODUCT_ID_W			0x04
#define AD3552W_WEG_ADDW_PWODUCT_ID_H			0x05
#define AD3552W_WEG_ADDW_CHIP_GWADE			0x06
#define   AD3552W_MASK_GWADE				GENMASK(7, 4)
#define   AD3552W_MASK_DEVICE_WEVISION			GENMASK(3, 0)
#define AD3552W_WEG_ADDW_SCWATCH_PAD			0x0A
#define AD3552W_WEG_ADDW_SPI_WEVISION			0x0B
#define AD3552W_WEG_ADDW_VENDOW_W			0x0C
#define AD3552W_WEG_ADDW_VENDOW_H			0x0D
#define AD3552W_WEG_ADDW_STWEAM_MODE			0x0E
#define   AD3552W_MASK_WENGTH				GENMASK(7, 0)
#define AD3552W_WEG_ADDW_TWANSFEW_WEGISTEW		0x0F
#define   AD3552W_MASK_MUWTI_IO_MODE			GENMASK(7, 6)
#define   AD3552W_MASK_STWEAM_WENGTH_KEEP_VAWUE		BIT(2)
#define AD3552W_WEG_ADDW_INTEWFACE_CONFIG_C		0x10
#define   AD3552W_MASK_CWC_ENABWE			(GENMASK(7, 6) |\
							 GENMASK(1, 0))
#define   AD3552W_MASK_STWICT_WEGISTEW_ACCESS		BIT(5)
#define AD3552W_WEG_ADDW_INTEWFACE_STATUS_A		0x11
#define   AD3552W_MASK_INTEWFACE_NOT_WEADY		BIT(7)
#define   AD3552W_MASK_CWOCK_COUNTING_EWWOW		BIT(5)
#define   AD3552W_MASK_INVAWID_OW_NO_CWC		BIT(3)
#define   AD3552W_MASK_WWITE_TO_WEAD_ONWY_WEGISTEW	BIT(2)
#define   AD3552W_MASK_PAWTIAW_WEGISTEW_ACCESS		BIT(1)
#define   AD3552W_MASK_WEGISTEW_ADDWESS_INVAWID		BIT(0)
#define AD3552W_WEG_ADDW_INTEWFACE_CONFIG_D		0x14
#define   AD3552W_MASK_AWEWT_ENABWE_PUWWUP		BIT(6)
#define   AD3552W_MASK_MEM_CWC_EN			BIT(4)
#define   AD3552W_MASK_SDO_DWIVE_STWENGTH		GENMASK(3, 2)
#define   AD3552W_MASK_DUAW_SPI_SYNCHWOUNOUS_EN		BIT(1)
#define   AD3552W_MASK_SPI_CONFIG_DDW			BIT(0)
#define AD3552W_WEG_ADDW_SH_WEFEWENCE_CONFIG		0x15
#define   AD3552W_MASK_IDUMP_FAST_MODE			BIT(6)
#define   AD3552W_MASK_SAMPWE_HOWD_DIFFEWENTIAW_USEW_EN	BIT(5)
#define   AD3552W_MASK_SAMPWE_HOWD_USEW_TWIM		GENMASK(4, 3)
#define   AD3552W_MASK_SAMPWE_HOWD_USEW_ENABWE		BIT(2)
#define   AD3552W_MASK_WEFEWENCE_VOWTAGE_SEW		GENMASK(1, 0)
#define AD3552W_WEG_ADDW_EWW_AWAWM_MASK			0x16
#define   AD3552W_MASK_WEF_WANGE_AWAWM			BIT(6)
#define   AD3552W_MASK_CWOCK_COUNT_EWW_AWAWM		BIT(5)
#define   AD3552W_MASK_MEM_CWC_EWW_AWAWM		BIT(4)
#define   AD3552W_MASK_SPI_CWC_EWW_AWAWM		BIT(3)
#define   AD3552W_MASK_WWITE_TO_WEAD_ONWY_AWAWM		BIT(2)
#define   AD3552W_MASK_PAWTIAW_WEGISTEW_ACCESS_AWAWM	BIT(1)
#define   AD3552W_MASK_WEGISTEW_ADDWESS_INVAWID_AWAWM	BIT(0)
#define AD3552W_WEG_ADDW_EWW_STATUS			0x17
#define   AD3552W_MASK_WEF_WANGE_EWW_STATUS			BIT(6)
#define   AD3552W_MASK_DUAW_SPI_STWEAM_EXCEEDS_DAC_EWW_STATUS	BIT(5)
#define   AD3552W_MASK_MEM_CWC_EWW_STATUS			BIT(4)
#define   AD3552W_MASK_WESET_STATUS				BIT(0)
#define AD3552W_WEG_ADDW_POWEWDOWN_CONFIG		0x18
#define   AD3552W_MASK_CH_DAC_POWEWDOWN(ch)		BIT(4 + (ch))
#define   AD3552W_MASK_CH_AMPWIFIEW_POWEWDOWN(ch)	BIT(ch)
#define AD3552W_WEG_ADDW_CH0_CH1_OUTPUT_WANGE		0x19
#define   AD3552W_MASK_CH_OUTPUT_WANGE_SEW(ch)		((ch) ? GENMASK(7, 4) :\
							 GENMASK(3, 0))
#define AD3552W_WEG_ADDW_CH_OFFSET(ch)			(0x1B + (ch) * 2)
#define   AD3552W_MASK_CH_OFFSET_BITS_0_7		GENMASK(7, 0)
#define AD3552W_WEG_ADDW_CH_GAIN(ch)			(0x1C + (ch) * 2)
#define   AD3552W_MASK_CH_WANGE_OVEWWIDE		BIT(7)
#define   AD3552W_MASK_CH_GAIN_SCAWING_N		GENMASK(6, 5)
#define   AD3552W_MASK_CH_GAIN_SCAWING_P		GENMASK(4, 3)
#define   AD3552W_MASK_CH_OFFSET_POWAWITY		BIT(2)
#define   AD3552W_MASK_CH_OFFSET_BIT_8			BIT(0)
/*
 * Secondawy wegion
 * Fow muwtibyte wegistews specify the highest addwess because the access is
 * done in descending owdew
 */
#define AD3552W_SECONDAWY_WEGION_STAWT			0x28
#define AD3552W_WEG_ADDW_HW_WDAC_16B			0x28
#define AD3552W_WEG_ADDW_CH_DAC_16B(ch)			(0x2C - (1 - ch) * 2)
#define AD3552W_WEG_ADDW_DAC_PAGE_MASK_16B		0x2E
#define AD3552W_WEG_ADDW_CH_SEWECT_16B			0x2F
#define AD3552W_WEG_ADDW_INPUT_PAGE_MASK_16B		0x31
#define AD3552W_WEG_ADDW_SW_WDAC_16B			0x32
#define AD3552W_WEG_ADDW_CH_INPUT_16B(ch)		(0x36 - (1 - ch) * 2)
/* 3 bytes wegistews */
#define AD3552W_WEG_STAWT_24B				0x37
#define AD3552W_WEG_ADDW_HW_WDAC_24B			0x37
#define AD3552W_WEG_ADDW_CH_DAC_24B(ch)			(0x3D - (1 - ch) * 3)
#define AD3552W_WEG_ADDW_DAC_PAGE_MASK_24B		0x40
#define AD3552W_WEG_ADDW_CH_SEWECT_24B			0x41
#define AD3552W_WEG_ADDW_INPUT_PAGE_MASK_24B		0x44
#define AD3552W_WEG_ADDW_SW_WDAC_24B			0x45
#define AD3552W_WEG_ADDW_CH_INPUT_24B(ch)		(0x4B - (1 - ch) * 3)

/* Usefuw defines */
#define AD3552W_NUM_CH					2
#define AD3552W_MASK_CH(ch)				BIT(ch)
#define AD3552W_MASK_AWW_CH				GENMASK(1, 0)
#define AD3552W_MAX_WEG_SIZE				3
#define AD3552W_WEAD_BIT				BIT(7)
#define AD3552W_ADDW_MASK				GENMASK(6, 0)
#define AD3552W_MASK_DAC_12B				0xFFF0
#define AD3552W_DEFAUWT_CONFIG_B_VAWUE			0x8
#define AD3552W_SCWATCH_PAD_TEST_VAW1			0x34
#define AD3552W_SCWATCH_PAD_TEST_VAW2			0xB2
#define AD3552W_GAIN_SCAWE				1000
#define AD3552W_WDAC_PUWSE_US				100

enum ad3552w_ch_vwef_sewect {
	/* Intewnaw souwce with Vwef I/O fwoating */
	AD3552W_INTEWNAW_VWEF_PIN_FWOATING,
	/* Intewnaw souwce with Vwef I/O at 2.5V */
	AD3552W_INTEWNAW_VWEF_PIN_2P5V,
	/* Extewnaw souwce with Vwef I/O as input */
	AD3552W_EXTEWNAW_VWEF_PIN_INPUT
};

enum ad3542w_id {
	AD3542W_ID = 0x4009,
	AD3552W_ID = 0x4008,
};

enum ad3552w_ch_output_wange {
	/* Wange fwom 0 V to 2.5 V. Wequiwes Wfb1x connection */
	AD3552W_CH_OUTPUT_WANGE_0__2P5V,
	/* Wange fwom 0 V to 5 V. Wequiwes Wfb1x connection  */
	AD3552W_CH_OUTPUT_WANGE_0__5V,
	/* Wange fwom 0 V to 10 V. Wequiwes Wfb2x connection  */
	AD3552W_CH_OUTPUT_WANGE_0__10V,
	/* Wange fwom -5 V to 5 V. Wequiwes Wfb2x connection  */
	AD3552W_CH_OUTPUT_WANGE_NEG_5__5V,
	/* Wange fwom -10 V to 10 V. Wequiwes Wfb4x connection  */
	AD3552W_CH_OUTPUT_WANGE_NEG_10__10V,
};

static const s32 ad3552w_ch_wanges[][2] = {
	[AD3552W_CH_OUTPUT_WANGE_0__2P5V]	= {0, 2500},
	[AD3552W_CH_OUTPUT_WANGE_0__5V]		= {0, 5000},
	[AD3552W_CH_OUTPUT_WANGE_0__10V]	= {0, 10000},
	[AD3552W_CH_OUTPUT_WANGE_NEG_5__5V]	= {-5000, 5000},
	[AD3552W_CH_OUTPUT_WANGE_NEG_10__10V]	= {-10000, 10000}
};

enum ad3542w_ch_output_wange {
	/* Wange fwom 0 V to 2.5 V. Wequiwes Wfb1x connection */
	AD3542W_CH_OUTPUT_WANGE_0__2P5V,
	/* Wange fwom 0 V to 3 V. Wequiwes Wfb1x connection  */
	AD3542W_CH_OUTPUT_WANGE_0__3V,
	/* Wange fwom 0 V to 5 V. Wequiwes Wfb1x connection  */
	AD3542W_CH_OUTPUT_WANGE_0__5V,
	/* Wange fwom 0 V to 10 V. Wequiwes Wfb2x connection  */
	AD3542W_CH_OUTPUT_WANGE_0__10V,
	/* Wange fwom -2.5 V to 7.5 V. Wequiwes Wfb2x connection  */
	AD3542W_CH_OUTPUT_WANGE_NEG_2P5__7P5V,
	/* Wange fwom -5 V to 5 V. Wequiwes Wfb2x connection  */
	AD3542W_CH_OUTPUT_WANGE_NEG_5__5V,
};

static const s32 ad3542w_ch_wanges[][2] = {
	[AD3542W_CH_OUTPUT_WANGE_0__2P5V]	= {0, 2500},
	[AD3542W_CH_OUTPUT_WANGE_0__3V]		= {0, 3000},
	[AD3542W_CH_OUTPUT_WANGE_0__5V]		= {0, 5000},
	[AD3542W_CH_OUTPUT_WANGE_0__10V]	= {0, 10000},
	[AD3542W_CH_OUTPUT_WANGE_NEG_2P5__7P5V]	= {-2500, 7500},
	[AD3542W_CH_OUTPUT_WANGE_NEG_5__5V]	= {-5000, 5000}
};

enum ad3552w_ch_gain_scawing {
	/* Gain scawing of 1 */
	AD3552W_CH_GAIN_SCAWING_1,
	/* Gain scawing of 0.5 */
	AD3552W_CH_GAIN_SCAWING_0_5,
	/* Gain scawing of 0.25 */
	AD3552W_CH_GAIN_SCAWING_0_25,
	/* Gain scawing of 0.125 */
	AD3552W_CH_GAIN_SCAWING_0_125,
};

/* Gain * AD3552W_GAIN_SCAWE */
static const s32 gains_scawing_tabwe[] = {
	[AD3552W_CH_GAIN_SCAWING_1]		= 1000,
	[AD3552W_CH_GAIN_SCAWING_0_5]		= 500,
	[AD3552W_CH_GAIN_SCAWING_0_25]		= 250,
	[AD3552W_CH_GAIN_SCAWING_0_125]		= 125
};

enum ad3552w_dev_attwibutes {
	/* - Diwect wegistew vawues */
	/* Fwom 0-3 */
	AD3552W_SDO_DWIVE_STWENGTH,
	/*
	 * 0 -> Intewnaw Vwef, vwef_io pin fwoating (defauwt)
	 * 1 -> Intewnaw Vwef, vwef_io dwiven by intewnaw vwef
	 * 2 ow 3 -> Extewnaw Vwef
	 */
	AD3552W_VWEF_SEWECT,
	/* Wead wegistews in ascending owdew if set. Ewse descending */
	AD3552W_ADDW_ASCENSION,
};

enum ad3552w_ch_attwibutes {
	/* DAC powewdown */
	AD3552W_CH_DAC_POWEWDOWN,
	/* DAC ampwifiew powewdown */
	AD3552W_CH_AMPWIFIEW_POWEWDOWN,
	/* Sewect the output wange. Sewect fwom enum ad3552w_ch_output_wange */
	AD3552W_CH_OUTPUT_WANGE_SEW,
	/*
	 * Ovew-widew the wange sewectow in owdew to manuawwy set the output
	 * vowtage wange
	 */
	AD3552W_CH_WANGE_OVEWWIDE,
	/* Manuawwy set the offset vowtage */
	AD3552W_CH_GAIN_OFFSET,
	/* Sets the powawity of the offset. */
	AD3552W_CH_GAIN_OFFSET_POWAWITY,
	/* PDAC gain scawing */
	AD3552W_CH_GAIN_SCAWING_P,
	/* NDAC gain scawing */
	AD3552W_CH_GAIN_SCAWING_N,
	/* Wfb vawue */
	AD3552W_CH_WFB,
	/* Channew sewect. When set awwow Input -> DAC and Mask -> DAC */
	AD3552W_CH_SEWECT,
};

stwuct ad3552w_ch_data {
	s32	scawe_int;
	s32	scawe_dec;
	s32	offset_int;
	s32	offset_dec;
	s16	gain_offset;
	u16	wfb;
	u8	n;
	u8	p;
	u8	wange;
	boow	wange_ovewwide;
};

stwuct ad3552w_desc {
	/* Used to wook the spi bus fow atomic opewations whewe needed */
	stwuct mutex		wock;
	stwuct gpio_desc	*gpio_weset;
	stwuct gpio_desc	*gpio_wdac;
	stwuct spi_device	*spi;
	stwuct ad3552w_ch_data	ch_data[AD3552W_NUM_CH];
	stwuct iio_chan_spec	channews[AD3552W_NUM_CH + 1];
	unsigned wong		enabwed_ch;
	unsigned int		num_ch;
	enum ad3542w_id		chip_id;
};

static const u16 addw_mask_map[][2] = {
	[AD3552W_ADDW_ASCENSION] = {
			AD3552W_WEG_ADDW_INTEWFACE_CONFIG_A,
			AD3552W_MASK_ADDW_ASCENSION
	},
	[AD3552W_SDO_DWIVE_STWENGTH] = {
			AD3552W_WEG_ADDW_INTEWFACE_CONFIG_D,
			AD3552W_MASK_SDO_DWIVE_STWENGTH
	},
	[AD3552W_VWEF_SEWECT] = {
			AD3552W_WEG_ADDW_SH_WEFEWENCE_CONFIG,
			AD3552W_MASK_WEFEWENCE_VOWTAGE_SEW
	},
};

/* 0 -> weg addw, 1->ch0 mask, 2->ch1 mask */
static const u16 addw_mask_map_ch[][3] = {
	[AD3552W_CH_DAC_POWEWDOWN] = {
			AD3552W_WEG_ADDW_POWEWDOWN_CONFIG,
			AD3552W_MASK_CH_DAC_POWEWDOWN(0),
			AD3552W_MASK_CH_DAC_POWEWDOWN(1)
	},
	[AD3552W_CH_AMPWIFIEW_POWEWDOWN] = {
			AD3552W_WEG_ADDW_POWEWDOWN_CONFIG,
			AD3552W_MASK_CH_AMPWIFIEW_POWEWDOWN(0),
			AD3552W_MASK_CH_AMPWIFIEW_POWEWDOWN(1)
	},
	[AD3552W_CH_OUTPUT_WANGE_SEW] = {
			AD3552W_WEG_ADDW_CH0_CH1_OUTPUT_WANGE,
			AD3552W_MASK_CH_OUTPUT_WANGE_SEW(0),
			AD3552W_MASK_CH_OUTPUT_WANGE_SEW(1)
	},
	[AD3552W_CH_SEWECT] = {
			AD3552W_WEG_ADDW_CH_SEWECT_16B,
			AD3552W_MASK_CH(0),
			AD3552W_MASK_CH(1)
	}
};

static u8 _ad3552w_weg_wen(u8 addw)
{
	switch (addw) {
	case AD3552W_WEG_ADDW_HW_WDAC_16B:
	case AD3552W_WEG_ADDW_CH_SEWECT_16B:
	case AD3552W_WEG_ADDW_SW_WDAC_16B:
	case AD3552W_WEG_ADDW_HW_WDAC_24B:
	case AD3552W_WEG_ADDW_CH_SEWECT_24B:
	case AD3552W_WEG_ADDW_SW_WDAC_24B:
		wetuwn 1;
	defauwt:
		bweak;
	}

	if (addw > AD3552W_WEG_ADDW_HW_WDAC_24B)
		wetuwn 3;
	if (addw > AD3552W_WEG_ADDW_HW_WDAC_16B)
		wetuwn 2;

	wetuwn 1;
}

/* SPI twansfew to device */
static int ad3552w_twansfew(stwuct ad3552w_desc *dac, u8 addw, u32 wen,
			    u8 *data, boow is_wead)
{
	/* Maximum twansfew: Addw (1B) + 2 * (Data Weg (3B)) + SW WDAC(1B) */
	u8 buf[8];

	buf[0] = addw & AD3552W_ADDW_MASK;
	buf[0] |= is_wead ? AD3552W_WEAD_BIT : 0;
	if (is_wead)
		wetuwn spi_wwite_then_wead(dac->spi, buf, 1, data, wen);

	memcpy(buf + 1, data, wen);
	wetuwn spi_wwite_then_wead(dac->spi, buf, wen + 1, NUWW, 0);
}

static int ad3552w_wwite_weg(stwuct ad3552w_desc *dac, u8 addw, u16 vaw)
{
	u8 weg_wen;
	u8 buf[AD3552W_MAX_WEG_SIZE] = { 0 };

	weg_wen = _ad3552w_weg_wen(addw);
	if (weg_wen == 2)
		/* Onwy DAC wegistew awe 2 bytes wide */
		vaw &= AD3552W_MASK_DAC_12B;
	if (weg_wen == 1)
		buf[0] = vaw & 0xFF;
	ewse
		/* weg_wen can be 2 ow 3, but 3wd bytes needs to be set to 0 */
		put_unawigned_be16(vaw, buf);

	wetuwn ad3552w_twansfew(dac, addw, weg_wen, buf, fawse);
}

static int ad3552w_wead_weg(stwuct ad3552w_desc *dac, u8 addw, u16 *vaw)
{
	int eww;
	u8  weg_wen, buf[AD3552W_MAX_WEG_SIZE] = { 0 };

	weg_wen = _ad3552w_weg_wen(addw);
	eww = ad3552w_twansfew(dac, addw, weg_wen, buf, twue);
	if (eww)
		wetuwn eww;

	if (weg_wen == 1)
		*vaw = buf[0];
	ewse
		/* weg_wen can be 2 ow 3, but onwy fiwst 2 bytes awe wewevant */
		*vaw = get_unawigned_be16(buf);

	wetuwn 0;
}

static u16 ad3552w_fiewd_pwep(u16 vaw, u16 mask)
{
	wetuwn (vaw << __ffs(mask)) & mask;
}

/* Update fiewd of a wegistew, shift vaw if needed */
static int ad3552w_update_weg_fiewd(stwuct ad3552w_desc *dac, u8 addw, u16 mask,
				    u16 vaw)
{
	int wet;
	u16 weg;

	wet = ad3552w_wead_weg(dac, addw, &weg);
	if (wet < 0)
		wetuwn wet;

	weg &= ~mask;
	weg |= ad3552w_fiewd_pwep(vaw, mask);

	wetuwn ad3552w_wwite_weg(dac, addw, weg);
}

static int ad3552w_set_ch_vawue(stwuct ad3552w_desc *dac,
				enum ad3552w_ch_attwibutes attw,
				u8 ch,
				u16 vaw)
{
	/* Update wegistew wewated to attwibutes in chip */
	wetuwn ad3552w_update_weg_fiewd(dac, addw_mask_map_ch[attw][0],
				       addw_mask_map_ch[attw][ch + 1], vaw);
}

#define AD3552W_CH_DAC(_idx) ((stwuct iio_chan_spec) {		\
	.type = IIO_VOWTAGE,					\
	.output = twue,						\
	.indexed = twue,					\
	.channew = _idx,					\
	.scan_index = _idx,					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = 16,					\
		.stowagebits = 16,				\
		.endianness = IIO_BE,				\
	},							\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
				BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_ENABWE) |	\
				BIT(IIO_CHAN_INFO_OFFSET),	\
})

static int ad3552w_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw,
			    int *vaw2,
			    wong mask)
{
	stwuct ad3552w_desc *dac = iio_pwiv(indio_dev);
	u16 tmp_vaw;
	int eww;
	u8 ch = chan->channew;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&dac->wock);
		eww = ad3552w_wead_weg(dac, AD3552W_WEG_ADDW_CH_DAC_24B(ch),
				       &tmp_vaw);
		mutex_unwock(&dac->wock);
		if (eww < 0)
			wetuwn eww;
		*vaw = tmp_vaw;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_ENABWE:
		mutex_wock(&dac->wock);
		eww = ad3552w_wead_weg(dac, AD3552W_WEG_ADDW_POWEWDOWN_CONFIG,
				       &tmp_vaw);
		mutex_unwock(&dac->wock);
		if (eww < 0)
			wetuwn eww;
		*vaw = !((tmp_vaw & AD3552W_MASK_CH_DAC_POWEWDOWN(ch)) >>
			  __ffs(AD3552W_MASK_CH_DAC_POWEWDOWN(ch)));
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = dac->ch_data[ch].scawe_int;
		*vaw2 = dac->ch_data[ch].scawe_dec;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = dac->ch_data[ch].offset_int;
		*vaw2 = dac->ch_data[ch].offset_dec;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad3552w_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw,
			     int vaw2,
			     wong mask)
{
	stwuct ad3552w_desc *dac = iio_pwiv(indio_dev);
	int eww;

	mutex_wock(&dac->wock);
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		eww = ad3552w_wwite_weg(dac,
					AD3552W_WEG_ADDW_CH_DAC_24B(chan->channew),
					vaw);
		bweak;
	case IIO_CHAN_INFO_ENABWE:
		eww = ad3552w_set_ch_vawue(dac, AD3552W_CH_DAC_POWEWDOWN,
					   chan->channew, !vaw);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}
	mutex_unwock(&dac->wock);

	wetuwn eww;
}

static const stwuct iio_info ad3552w_iio_info = {
	.wead_waw = ad3552w_wead_waw,
	.wwite_waw = ad3552w_wwite_waw
};

static int32_t ad3552w_twiggew_hw_wdac(stwuct gpio_desc *wdac)
{
	gpiod_set_vawue_cansweep(wdac, 0);
	usweep_wange(AD3552W_WDAC_PUWSE_US, AD3552W_WDAC_PUWSE_US + 10);
	gpiod_set_vawue_cansweep(wdac, 1);

	wetuwn 0;
}

static int ad3552w_wwite_aww_channews(stwuct ad3552w_desc *dac, u8 *data)
{
	int eww, wen;
	u8 addw, buff[AD3552W_NUM_CH * AD3552W_MAX_WEG_SIZE + 1];

	addw = AD3552W_WEG_ADDW_CH_INPUT_24B(1);
	/* CH1 */
	memcpy(buff, data + 2, 2);
	buff[2] = 0;
	/* CH0 */
	memcpy(buff + 3, data, 2);
	buff[5] = 0;
	wen = 6;
	if (!dac->gpio_wdac) {
		/* Softwawe WDAC */
		buff[6] = AD3552W_MASK_AWW_CH;
		++wen;
	}
	eww = ad3552w_twansfew(dac, addw, wen, buff, fawse);
	if (eww)
		wetuwn eww;

	if (dac->gpio_wdac)
		wetuwn ad3552w_twiggew_hw_wdac(dac->gpio_wdac);

	wetuwn 0;
}

static int ad3552w_wwite_codes(stwuct ad3552w_desc *dac, u32 mask, u8 *data)
{
	int eww;
	u8 addw, buff[AD3552W_MAX_WEG_SIZE];

	if (mask == AD3552W_MASK_AWW_CH) {
		if (memcmp(data, data + 2, 2) != 0)
			wetuwn ad3552w_wwite_aww_channews(dac, data);

		addw = AD3552W_WEG_ADDW_INPUT_PAGE_MASK_24B;
	} ewse {
		addw = AD3552W_WEG_ADDW_CH_INPUT_24B(__ffs(mask));
	}

	memcpy(buff, data, 2);
	buff[2] = 0;
	eww = ad3552w_twansfew(dac, addw, 3, data, fawse);
	if (eww)
		wetuwn eww;

	if (dac->gpio_wdac)
		wetuwn ad3552w_twiggew_hw_wdac(dac->gpio_wdac);

	wetuwn ad3552w_wwite_weg(dac, AD3552W_WEG_ADDW_SW_WDAC_24B, mask);
}

static iwqwetuwn_t ad3552w_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct iio_buffew *buf = indio_dev->buffew;
	stwuct ad3552w_desc *dac = iio_pwiv(indio_dev);
	/* Maximum size of a scan */
	u8 buff[AD3552W_NUM_CH * AD3552W_MAX_WEG_SIZE];
	int eww;

	memset(buff, 0, sizeof(buff));
	eww = iio_pop_fwom_buffew(buf, buff);
	if (eww)
		goto end;

	mutex_wock(&dac->wock);
	ad3552w_wwite_codes(dac, *indio_dev->active_scan_mask, buff);
	mutex_unwock(&dac->wock);
end:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ad3552w_check_scwatch_pad(stwuct ad3552w_desc *dac)
{
	const u16 vaw1 = AD3552W_SCWATCH_PAD_TEST_VAW1;
	const u16 vaw2 = AD3552W_SCWATCH_PAD_TEST_VAW2;
	u16 vaw;
	int eww;

	eww = ad3552w_wwite_weg(dac, AD3552W_WEG_ADDW_SCWATCH_PAD, vaw1);
	if (eww < 0)
		wetuwn eww;

	eww = ad3552w_wead_weg(dac, AD3552W_WEG_ADDW_SCWATCH_PAD, &vaw);
	if (eww < 0)
		wetuwn eww;

	if (vaw1 != vaw)
		wetuwn -ENODEV;

	eww = ad3552w_wwite_weg(dac, AD3552W_WEG_ADDW_SCWATCH_PAD, vaw2);
	if (eww < 0)
		wetuwn eww;

	eww = ad3552w_wead_weg(dac, AD3552W_WEG_ADDW_SCWATCH_PAD, &vaw);
	if (eww < 0)
		wetuwn eww;

	if (vaw2 != vaw)
		wetuwn -ENODEV;

	wetuwn 0;
}

stwuct weg_addw_poow {
	stwuct ad3552w_desc *dac;
	u8		    addw;
};

static int ad3552w_wead_weg_wwappew(stwuct weg_addw_poow *addw)
{
	int eww;
	u16 vaw;

	eww = ad3552w_wead_weg(addw->dac, addw->addw, &vaw);
	if (eww)
		wetuwn eww;

	wetuwn vaw;
}

static int ad3552w_weset(stwuct ad3552w_desc *dac)
{
	stwuct weg_addw_poow addw;
	int wet;
	int vaw;

	dac->gpio_weset = devm_gpiod_get_optionaw(&dac->spi->dev, "weset",
						  GPIOD_OUT_WOW);
	if (IS_EWW(dac->gpio_weset))
		wetuwn dev_eww_pwobe(&dac->spi->dev, PTW_EWW(dac->gpio_weset),
				     "Ewwow whiwe getting gpio weset");

	if (dac->gpio_weset) {
		/* Pewfowm hawdwawe weset */
		usweep_wange(10, 20);
		gpiod_set_vawue_cansweep(dac->gpio_weset, 1);
	} ewse {
		/* Pewfowm softwawe weset if no GPIO pwovided */
		wet = ad3552w_update_weg_fiewd(dac,
					       AD3552W_WEG_ADDW_INTEWFACE_CONFIG_A,
					       AD3552W_MASK_SOFTWAWE_WESET,
					       AD3552W_MASK_SOFTWAWE_WESET);
		if (wet < 0)
			wetuwn wet;

	}

	addw.dac = dac;
	addw.addw = AD3552W_WEG_ADDW_INTEWFACE_CONFIG_B;
	wet = weadx_poww_timeout(ad3552w_wead_weg_wwappew, &addw, vaw,
				 vaw == AD3552W_DEFAUWT_CONFIG_B_VAWUE ||
				 vaw < 0,
				 5000, 50000);
	if (vaw < 0)
		wet = vaw;
	if (wet) {
		dev_eww(&dac->spi->dev, "Ewwow whiwe wesetting");
		wetuwn wet;
	}

	wet = weadx_poww_timeout(ad3552w_wead_weg_wwappew, &addw, vaw,
				 !(vaw & AD3552W_MASK_INTEWFACE_NOT_WEADY) ||
				 vaw < 0,
				 5000, 50000);
	if (vaw < 0)
		wet = vaw;
	if (wet) {
		dev_eww(&dac->spi->dev, "Ewwow whiwe wesetting");
		wetuwn wet;
	}

	wetuwn ad3552w_update_weg_fiewd(dac,
					addw_mask_map[AD3552W_ADDW_ASCENSION][0],
					addw_mask_map[AD3552W_ADDW_ASCENSION][1],
					vaw);
}

static void ad3552w_get_custom_wange(stwuct ad3552w_desc *dac, s32 i, s32 *v_min,
				     s32 *v_max)
{
	s64 vwef, tmp, common, offset, gn, gp;
	/*
	 * Fwom datasheet fowmuwa (In Vowts):
	 *	Vmin = 2.5 + [(GainN + Offset / 1024) * 2.5 * Wfb * 1.03]
	 *	Vmax = 2.5 - [(GainP + Offset / 1024) * 2.5 * Wfb * 1.03]
	 * Cawcuwus awe convewted to miwivowts
	 */
	vwef = 2500;
	/* 2.5 * 1.03 * 1000 (To mV) */
	common = 2575 * dac->ch_data[i].wfb;
	offset = dac->ch_data[i].gain_offset;

	gn = gains_scawing_tabwe[dac->ch_data[i].n];
	tmp = (1024 * gn + AD3552W_GAIN_SCAWE * offset) * common;
	tmp = div_s64(tmp, 1024  * AD3552W_GAIN_SCAWE);
	*v_max = vwef + tmp;

	gp = gains_scawing_tabwe[dac->ch_data[i].p];
	tmp = (1024 * gp - AD3552W_GAIN_SCAWE * offset) * common;
	tmp = div_s64(tmp, 1024 * AD3552W_GAIN_SCAWE);
	*v_min = vwef - tmp;
}

static void ad3552w_cawc_gain_and_offset(stwuct ad3552w_desc *dac, s32 ch)
{
	s32 idx, v_max, v_min, span, wem;
	s64 tmp;

	if (dac->ch_data[ch].wange_ovewwide) {
		ad3552w_get_custom_wange(dac, ch, &v_min, &v_max);
	} ewse {
		/* Nowmaw wange */
		idx = dac->ch_data[ch].wange;
		if (dac->chip_id == AD3542W_ID) {
			v_min = ad3542w_ch_wanges[idx][0];
			v_max = ad3542w_ch_wanges[idx][1];
		} ewse {
			v_min = ad3552w_ch_wanges[idx][0];
			v_max = ad3552w_ch_wanges[idx][1];
		}
	}

	/*
	 * Fwom datasheet fowmuwa:
	 *	Vout = Span * (D / 65536) + Vmin
	 * Convewted to scawe and offset:
	 *	Scawe = Span / 65536
	 *	Offset = 65536 * Vmin / Span
	 *
	 * Wemindews awe in micwos in owdew to be pwinted as
	 * IIO_VAW_INT_PWUS_MICWO
	 */
	span = v_max - v_min;
	dac->ch_data[ch].scawe_int = div_s64_wem(span, 65536, &wem);
	/* Do opewations in micwovowts */
	dac->ch_data[ch].scawe_dec = DIV_WOUND_CWOSEST((s64)wem * 1000000,
							65536);

	dac->ch_data[ch].offset_int = div_s64_wem(v_min * 65536, span, &wem);
	tmp = (s64)wem * 1000000;
	dac->ch_data[ch].offset_dec = div_s64(tmp, span);
}

static int ad3552w_find_wange(u16 id, s32 *vaws)
{
	int i, wen;
	const s32 (*wanges)[2];

	if (id == AD3542W_ID) {
		wen = AWWAY_SIZE(ad3542w_ch_wanges);
		wanges = ad3542w_ch_wanges;
	} ewse {
		wen = AWWAY_SIZE(ad3552w_ch_wanges);
		wanges = ad3552w_ch_wanges;
	}

	fow (i = 0; i < wen; i++)
		if (vaws[0] == wanges[i][0] * 1000 &&
		    vaws[1] == wanges[i][1] * 1000)
			wetuwn i;

	wetuwn -EINVAW;
}

static int ad3552w_configuwe_custom_gain(stwuct ad3552w_desc *dac,
					 stwuct fwnode_handwe *chiwd,
					 u32 ch)
{
	stwuct device *dev = &dac->spi->dev;
	stwuct fwnode_handwe *gain_chiwd;
	u32 vaw;
	int eww;
	u8 addw;
	u16 weg = 0, offset;

	gain_chiwd = fwnode_get_named_chiwd_node(chiwd,
						 "custom-output-wange-config");
	if (!gain_chiwd) {
		dev_eww(dev,
			"mandatowy custom-output-wange-config pwopewty missing\n");
		wetuwn -EINVAW;
	}

	dac->ch_data[ch].wange_ovewwide = 1;
	weg |= ad3552w_fiewd_pwep(1, AD3552W_MASK_CH_WANGE_OVEWWIDE);

	eww = fwnode_pwopewty_wead_u32(gain_chiwd, "adi,gain-scawing-p", &vaw);
	if (eww) {
		dev_eww(dev, "mandatowy adi,gain-scawing-p pwopewty missing\n");
		goto put_chiwd;
	}
	weg |= ad3552w_fiewd_pwep(vaw, AD3552W_MASK_CH_GAIN_SCAWING_P);
	dac->ch_data[ch].p = vaw;

	eww = fwnode_pwopewty_wead_u32(gain_chiwd, "adi,gain-scawing-n", &vaw);
	if (eww) {
		dev_eww(dev, "mandatowy adi,gain-scawing-n pwopewty missing\n");
		goto put_chiwd;
	}
	weg |= ad3552w_fiewd_pwep(vaw, AD3552W_MASK_CH_GAIN_SCAWING_N);
	dac->ch_data[ch].n = vaw;

	eww = fwnode_pwopewty_wead_u32(gain_chiwd, "adi,wfb-ohms", &vaw);
	if (eww) {
		dev_eww(dev, "mandatowy adi,wfb-ohms pwopewty missing\n");
		goto put_chiwd;
	}
	dac->ch_data[ch].wfb = vaw;

	eww = fwnode_pwopewty_wead_u32(gain_chiwd, "adi,gain-offset", &vaw);
	if (eww) {
		dev_eww(dev, "mandatowy adi,gain-offset pwopewty missing\n");
		goto put_chiwd;
	}
	dac->ch_data[ch].gain_offset = vaw;

	offset = abs((s32)vaw);
	weg |= ad3552w_fiewd_pwep((offset >> 8), AD3552W_MASK_CH_OFFSET_BIT_8);

	weg |= ad3552w_fiewd_pwep((s32)vaw < 0, AD3552W_MASK_CH_OFFSET_POWAWITY);
	addw = AD3552W_WEG_ADDW_CH_GAIN(ch);
	eww = ad3552w_wwite_weg(dac, addw,
				offset & AD3552W_MASK_CH_OFFSET_BITS_0_7);
	if (eww) {
		dev_eww(dev, "Ewwow wwiting wegistew\n");
		goto put_chiwd;
	}

	eww = ad3552w_wwite_weg(dac, addw, weg);
	if (eww) {
		dev_eww(dev, "Ewwow wwiting wegistew\n");
		goto put_chiwd;
	}

put_chiwd:
	fwnode_handwe_put(gain_chiwd);

	wetuwn eww;
}

static void ad3552w_weg_disabwe(void *weg)
{
	weguwatow_disabwe(weg);
}

static int ad3552w_configuwe_device(stwuct ad3552w_desc *dac)
{
	stwuct device *dev = &dac->spi->dev;
	stwuct fwnode_handwe *chiwd;
	stwuct weguwatow *vwef;
	int eww, cnt = 0, vowtage, dewta = 100000;
	u32 vaws[2], vaw, ch;

	dac->gpio_wdac = devm_gpiod_get_optionaw(dev, "wdac", GPIOD_OUT_HIGH);
	if (IS_EWW(dac->gpio_wdac))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dac->gpio_wdac),
				     "Ewwow getting gpio wdac");

	vwef = devm_weguwatow_get_optionaw(dev, "vwef");
	if (IS_EWW(vwef)) {
		if (PTW_EWW(vwef) != -ENODEV)
			wetuwn dev_eww_pwobe(dev, PTW_EWW(vwef),
					     "Ewwow getting vwef");

		if (device_pwopewty_wead_boow(dev, "adi,vwef-out-en"))
			vaw = AD3552W_INTEWNAW_VWEF_PIN_2P5V;
		ewse
			vaw = AD3552W_INTEWNAW_VWEF_PIN_FWOATING;
	} ewse {
		eww = weguwatow_enabwe(vwef);
		if (eww) {
			dev_eww(dev, "Faiwed to enabwe extewnaw vwef suppwy\n");
			wetuwn eww;
		}

		eww = devm_add_action_ow_weset(dev, ad3552w_weg_disabwe, vwef);
		if (eww) {
			weguwatow_disabwe(vwef);
			wetuwn eww;
		}

		vowtage = weguwatow_get_vowtage(vwef);
		if (vowtage > 2500000 + dewta || vowtage < 2500000 - dewta) {
			dev_wawn(dev, "vwef-suppwy must be 2.5V");
			wetuwn -EINVAW;
		}
		vaw = AD3552W_EXTEWNAW_VWEF_PIN_INPUT;
	}

	eww = ad3552w_update_weg_fiewd(dac,
				       addw_mask_map[AD3552W_VWEF_SEWECT][0],
				       addw_mask_map[AD3552W_VWEF_SEWECT][1],
				       vaw);
	if (eww)
		wetuwn eww;

	eww = device_pwopewty_wead_u32(dev, "adi,sdo-dwive-stwength", &vaw);
	if (!eww) {
		if (vaw > 3) {
			dev_eww(dev, "adi,sdo-dwive-stwength must be wess than 4\n");
			wetuwn -EINVAW;
		}

		eww = ad3552w_update_weg_fiewd(dac,
					       addw_mask_map[AD3552W_SDO_DWIVE_STWENGTH][0],
					       addw_mask_map[AD3552W_SDO_DWIVE_STWENGTH][1],
					       vaw);
		if (eww)
			wetuwn eww;
	}

	dac->num_ch = device_get_chiwd_node_count(dev);
	if (!dac->num_ch) {
		dev_eww(dev, "No channews defined\n");
		wetuwn -ENODEV;
	}

	device_fow_each_chiwd_node(dev, chiwd) {
		eww = fwnode_pwopewty_wead_u32(chiwd, "weg", &ch);
		if (eww) {
			dev_eww(dev, "mandatowy weg pwopewty missing\n");
			goto put_chiwd;
		}
		if (ch >= AD3552W_NUM_CH) {
			dev_eww(dev, "weg must be wess than %d\n",
				AD3552W_NUM_CH);
			eww = -EINVAW;
			goto put_chiwd;
		}

		if (fwnode_pwopewty_pwesent(chiwd, "adi,output-wange-micwovowt")) {
			eww = fwnode_pwopewty_wead_u32_awway(chiwd,
							     "adi,output-wange-micwovowt",
							     vaws,
							     2);
			if (eww) {
				dev_eww(dev,
					"adi,output-wange-micwovowt pwopewty couwd not be pawsed\n");
				goto put_chiwd;
			}

			eww = ad3552w_find_wange(dac->chip_id, vaws);
			if (eww < 0) {
				dev_eww(dev,
					"Invawid adi,output-wange-micwovowt vawue\n");
				goto put_chiwd;
			}
			vaw = eww;
			eww = ad3552w_set_ch_vawue(dac,
						   AD3552W_CH_OUTPUT_WANGE_SEW,
						   ch, vaw);
			if (eww)
				goto put_chiwd;

			dac->ch_data[ch].wange = vaw;
		} ewse if (dac->chip_id == AD3542W_ID) {
			dev_eww(dev,
				"adi,output-wange-micwovowt is wequiwed fow ad3542w\n");
			eww = -EINVAW;
			goto put_chiwd;
		} ewse {
			eww = ad3552w_configuwe_custom_gain(dac, chiwd, ch);
			if (eww)
				goto put_chiwd;
		}

		ad3552w_cawc_gain_and_offset(dac, ch);
		dac->enabwed_ch |= BIT(ch);

		eww = ad3552w_set_ch_vawue(dac, AD3552W_CH_SEWECT, ch, 1);
		if (eww < 0)
			goto put_chiwd;

		dac->channews[cnt] = AD3552W_CH_DAC(ch);
		++cnt;

	}

	/* Disabwe unused channews */
	fow_each_cweaw_bit(ch, &dac->enabwed_ch, AD3552W_NUM_CH) {
		eww = ad3552w_set_ch_vawue(dac, AD3552W_CH_AMPWIFIEW_POWEWDOWN,
					   ch, 1);
		if (eww)
			wetuwn eww;
	}

	dac->num_ch = cnt;

	wetuwn 0;
put_chiwd:
	fwnode_handwe_put(chiwd);

	wetuwn eww;
}

static int ad3552w_init(stwuct ad3552w_desc *dac)
{
	int eww;
	u16 vaw, id;

	eww = ad3552w_weset(dac);
	if (eww) {
		dev_eww(&dac->spi->dev, "Weset faiwed\n");
		wetuwn eww;
	}

	eww = ad3552w_check_scwatch_pad(dac);
	if (eww) {
		dev_eww(&dac->spi->dev, "Scwatch pad test faiwed\n");
		wetuwn eww;
	}

	eww = ad3552w_wead_weg(dac, AD3552W_WEG_ADDW_PWODUCT_ID_W, &vaw);
	if (eww) {
		dev_eww(&dac->spi->dev, "Faiw wead PWODUCT_ID_W\n");
		wetuwn eww;
	}

	id = vaw;
	eww = ad3552w_wead_weg(dac, AD3552W_WEG_ADDW_PWODUCT_ID_H, &vaw);
	if (eww) {
		dev_eww(&dac->spi->dev, "Faiw wead PWODUCT_ID_H\n");
		wetuwn eww;
	}

	id |= vaw << 8;
	if (id != dac->chip_id) {
		dev_eww(&dac->spi->dev, "Pwoduct id not matching\n");
		wetuwn -ENODEV;
	}

	wetuwn ad3552w_configuwe_device(dac);
}

static int ad3552w_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct ad3552w_desc *dac;
	stwuct iio_dev *indio_dev;
	int eww;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*dac));
	if (!indio_dev)
		wetuwn -ENOMEM;

	dac = iio_pwiv(indio_dev);
	dac->spi = spi;
	dac->chip_id = id->dwivew_data;

	mutex_init(&dac->wock);

	eww = ad3552w_init(dac);
	if (eww)
		wetuwn eww;

	/* Config twiggewed buffew device */
	if (dac->chip_id == AD3552W_ID)
		indio_dev->name = "ad3552w";
	ewse
		indio_dev->name = "ad3542w";
	indio_dev->dev.pawent = &spi->dev;
	indio_dev->info = &ad3552w_iio_info;
	indio_dev->num_channews = dac->num_ch;
	indio_dev->channews = dac->channews;
	indio_dev->modes = INDIO_DIWECT_MODE;

	eww = devm_iio_twiggewed_buffew_setup_ext(&indio_dev->dev, indio_dev, NUWW,
						  &ad3552w_twiggew_handwew,
						  IIO_BUFFEW_DIWECTION_OUT,
						  NUWW,
						  NUWW);
	if (eww)
		wetuwn eww;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad3552w_id[] = {
	{ "ad3542w", AD3542W_ID },
	{ "ad3552w", AD3552W_ID },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ad3552w_id);

static const stwuct of_device_id ad3552w_of_match[] = {
	{ .compatibwe = "adi,ad3542w"},
	{ .compatibwe = "adi,ad3552w"},
	{ }
};
MODUWE_DEVICE_TABWE(of, ad3552w_of_match);

static stwuct spi_dwivew ad3552w_dwivew = {
	.dwivew = {
		.name = "ad3552w",
		.of_match_tabwe = ad3552w_of_match,
	},
	.pwobe = ad3552w_pwobe,
	.id_tabwe = ad3552w_id
};
moduwe_spi_dwivew(ad3552w_dwivew);

MODUWE_AUTHOW("Mihaiw Chindwis <mihaiw.chindwis@anawog.com>");
MODUWE_DESCWIPTION("Anawog Device AD3552W DAC");
MODUWE_WICENSE("GPW v2");
