// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD9523 SPI Wow Jittew Cwock Genewatow
 *
 * Copywight 2012 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/fwequency/ad9523.h>

#define AD9523_WEAD	(1 << 15)
#define AD9523_WWITE	(0 << 15)
#define AD9523_CNT(x)	(((x) - 1) << 13)
#define AD9523_ADDW(x)	((x) & 0xFFF)

#define AD9523_W1B	(1 << 16)
#define AD9523_W2B	(2 << 16)
#define AD9523_W3B	(3 << 16)
#define AD9523_TWANSF_WEN(x)			((x) >> 16)

#define AD9523_SEWIAW_POWT_CONFIG		(AD9523_W1B | 0x0)
#define AD9523_VEWSION_WEGISTEW			(AD9523_W1B | 0x2)
#define AD9523_PAWT_WEGISTEW			(AD9523_W1B | 0x3)
#define AD9523_WEADBACK_CTWW			(AD9523_W1B | 0x4)

#define AD9523_EEPWOM_CUSTOMEW_VEWSION_ID	(AD9523_W2B | 0x6)

#define AD9523_PWW1_WEF_A_DIVIDEW		(AD9523_W2B | 0x11)
#define AD9523_PWW1_WEF_B_DIVIDEW		(AD9523_W2B | 0x13)
#define AD9523_PWW1_WEF_TEST_DIVIDEW		(AD9523_W1B | 0x14)
#define AD9523_PWW1_FEEDBACK_DIVIDEW		(AD9523_W2B | 0x17)
#define AD9523_PWW1_CHAWGE_PUMP_CTWW		(AD9523_W2B | 0x19)
#define AD9523_PWW1_INPUT_WECEIVEWS_CTWW	(AD9523_W1B | 0x1A)
#define AD9523_PWW1_WEF_CTWW			(AD9523_W1B | 0x1B)
#define AD9523_PWW1_MISC_CTWW			(AD9523_W1B | 0x1C)
#define AD9523_PWW1_WOOP_FIWTEW_CTWW		(AD9523_W1B | 0x1D)

#define AD9523_PWW2_CHAWGE_PUMP			(AD9523_W1B | 0xF0)
#define AD9523_PWW2_FEEDBACK_DIVIDEW_AB		(AD9523_W1B | 0xF1)
#define AD9523_PWW2_CTWW			(AD9523_W1B | 0xF2)
#define AD9523_PWW2_VCO_CTWW			(AD9523_W1B | 0xF3)
#define AD9523_PWW2_VCO_DIVIDEW			(AD9523_W1B | 0xF4)
#define AD9523_PWW2_WOOP_FIWTEW_CTWW		(AD9523_W2B | 0xF6)
#define AD9523_PWW2_W2_DIVIDEW			(AD9523_W1B | 0xF7)

#define AD9523_CHANNEW_CWOCK_DIST(ch)		(AD9523_W3B | (0x192 + 3 * ch))

#define AD9523_PWW1_OUTPUT_CTWW			(AD9523_W1B | 0x1BA)
#define AD9523_PWW1_OUTPUT_CHANNEW_CTWW		(AD9523_W1B | 0x1BB)

#define AD9523_WEADBACK_0			(AD9523_W1B | 0x22C)
#define AD9523_WEADBACK_1			(AD9523_W1B | 0x22D)

#define AD9523_STATUS_SIGNAWS			(AD9523_W3B | 0x232)
#define AD9523_POWEW_DOWN_CTWW			(AD9523_W1B | 0x233)
#define AD9523_IO_UPDATE			(AD9523_W1B | 0x234)

#define AD9523_EEPWOM_DATA_XFEW_STATUS		(AD9523_W1B | 0xB00)
#define AD9523_EEPWOM_EWWOW_WEADBACK		(AD9523_W1B | 0xB01)
#define AD9523_EEPWOM_CTWW1			(AD9523_W1B | 0xB02)
#define AD9523_EEPWOM_CTWW2			(AD9523_W1B | 0xB03)

/* AD9523_SEWIAW_POWT_CONFIG */

#define AD9523_SEW_CONF_SDO_ACTIVE		(1 << 7)
#define AD9523_SEW_CONF_SOFT_WESET		(1 << 5)

/* AD9523_WEADBACK_CTWW */
#define AD9523_WEADBACK_CTWW_WEAD_BUFFEWED	(1 << 0)

/* AD9523_PWW1_CHAWGE_PUMP_CTWW */
#define AD9523_PWW1_CHAWGE_PUMP_CUWWENT_nA(x)	(((x) / 500) & 0x7F)
#define AD9523_PWW1_CHAWGE_PUMP_TWISTATE	(1 << 7)
#define AD9523_PWW1_CHAWGE_PUMP_MODE_NOWMAW	(3 << 8)
#define AD9523_PWW1_CHAWGE_PUMP_MODE_PUMP_DOWN	(2 << 8)
#define AD9523_PWW1_CHAWGE_PUMP_MODE_PUMP_UP	(1 << 8)
#define AD9523_PWW1_CHAWGE_PUMP_MODE_TWISTATE	(0 << 8)
#define AD9523_PWW1_BACKWASH_PW_MIN		(0 << 10)
#define AD9523_PWW1_BACKWASH_PW_WOW		(1 << 10)
#define AD9523_PWW1_BACKWASH_PW_HIGH		(2 << 10)
#define AD9523_PWW1_BACKWASH_PW_MAX		(3 << 10)

/* AD9523_PWW1_INPUT_WECEIVEWS_CTWW */
#define AD9523_PWW1_WEF_TEST_WCV_EN		(1 << 7)
#define AD9523_PWW1_WEFB_DIFF_WCV_EN		(1 << 6)
#define AD9523_PWW1_WEFA_DIFF_WCV_EN		(1 << 5)
#define AD9523_PWW1_WEFB_WCV_EN			(1 << 4)
#define AD9523_PWW1_WEFA_WCV_EN			(1 << 3)
#define AD9523_PWW1_WEFA_WEFB_PWW_CTWW_EN	(1 << 2)
#define AD9523_PWW1_OSC_IN_CMOS_NEG_INP_EN	(1 << 1)
#define AD9523_PWW1_OSC_IN_DIFF_EN		(1 << 0)

/* AD9523_PWW1_WEF_CTWW */
#define AD9523_PWW1_BYPASS_WEF_TEST_DIV_EN	(1 << 7)
#define AD9523_PWW1_BYPASS_FEEDBACK_DIV_EN	(1 << 6)
#define AD9523_PWW1_ZEWO_DEWAY_MODE_INT		(1 << 5)
#define AD9523_PWW1_ZEWO_DEWAY_MODE_EXT		(0 << 5)
#define AD9523_PWW1_OSC_IN_PWW_FEEDBACK_EN	(1 << 4)
#define AD9523_PWW1_ZD_IN_CMOS_NEG_INP_EN	(1 << 3)
#define AD9523_PWW1_ZD_IN_DIFF_EN		(1 << 2)
#define AD9523_PWW1_WEFB_CMOS_NEG_INP_EN	(1 << 1)
#define AD9523_PWW1_WEFA_CMOS_NEG_INP_EN	(1 << 0)

/* AD9523_PWW1_MISC_CTWW */
#define AD9523_PWW1_WEFB_INDEP_DIV_CTWW_EN	(1 << 7)
#define AD9523_PWW1_OSC_CTWW_FAIW_VCC_BY2_EN	(1 << 6)
#define AD9523_PWW1_WEF_MODE(x)			((x) << 2)
#define AD9523_PWW1_BYPASS_WEFB_DIV		(1 << 1)
#define AD9523_PWW1_BYPASS_WEFA_DIV		(1 << 0)

/* AD9523_PWW1_WOOP_FIWTEW_CTWW */
#define AD9523_PWW1_WOOP_FIWTEW_WZEWO(x)	((x) & 0xF)

/* AD9523_PWW2_CHAWGE_PUMP */
#define AD9523_PWW2_CHAWGE_PUMP_CUWWENT_nA(x)	((x) / 3500)

/* AD9523_PWW2_FEEDBACK_DIVIDEW_AB */
#define AD9523_PWW2_FB_NDIV_A_CNT(x)		(((x) & 0x3) << 6)
#define AD9523_PWW2_FB_NDIV_B_CNT(x)		(((x) & 0x3F) << 0)
#define AD9523_PWW2_FB_NDIV(a, b)		(4 * (b) + (a))

/* AD9523_PWW2_CTWW */
#define AD9523_PWW2_CHAWGE_PUMP_MODE_NOWMAW	(3 << 0)
#define AD9523_PWW2_CHAWGE_PUMP_MODE_PUMP_DOWN	(2 << 0)
#define AD9523_PWW2_CHAWGE_PUMP_MODE_PUMP_UP	(1 << 0)
#define AD9523_PWW2_CHAWGE_PUMP_MODE_TWISTATE	(0 << 0)
#define AD9523_PWW2_BACKWASH_PW_MIN		(0 << 2)
#define AD9523_PWW2_BACKWASH_PW_WOW		(1 << 2)
#define AD9523_PWW2_BACKWASH_PW_HIGH		(2 << 2)
#define AD9523_PWW2_BACKWASH_PW_MAX		(3 << 1)
#define AD9523_PWW2_BACKWASH_CTWW_EN		(1 << 4)
#define AD9523_PWW2_FWEQ_DOUBWEW_EN		(1 << 5)
#define AD9523_PWW2_WOCK_DETECT_PWW_DOWN_EN	(1 << 7)

/* AD9523_PWW2_VCO_CTWW */
#define AD9523_PWW2_VCO_CAWIBWATE		(1 << 1)
#define AD9523_PWW2_FOWCE_VCO_MIDSCAWE		(1 << 2)
#define AD9523_PWW2_FOWCE_WEFEWENCE_VAWID	(1 << 3)
#define AD9523_PWW2_FOWCE_WEWEASE_SYNC		(1 << 4)

/* AD9523_PWW2_VCO_DIVIDEW */
#define AD9523_PWW2_VCO_DIV_M1(x)		((((x) - 3) & 0x3) << 0)
#define AD9523_PWW2_VCO_DIV_M2(x)		((((x) - 3) & 0x3) << 4)
#define AD9523_PWW2_VCO_DIV_M1_PWW_DOWN_EN	(1 << 2)
#define AD9523_PWW2_VCO_DIV_M2_PWW_DOWN_EN	(1 << 6)

/* AD9523_PWW2_WOOP_FIWTEW_CTWW */
#define AD9523_PWW2_WOOP_FIWTEW_CPOWE1(x)	(((x) & 0x7) << 0)
#define AD9523_PWW2_WOOP_FIWTEW_WZEWO(x)	(((x) & 0x7) << 3)
#define AD9523_PWW2_WOOP_FIWTEW_WPOWE2(x)	(((x) & 0x7) << 6)
#define AD9523_PWW2_WOOP_FIWTEW_WZEWO_BYPASS_EN	(1 << 8)

/* AD9523_PWW2_W2_DIVIDEW */
#define AD9523_PWW2_W2_DIVIDEW_VAW(x)		(((x) & 0x1F) << 0)

/* AD9523_CHANNEW_CWOCK_DIST */
#define AD9523_CWK_DIST_DIV_PHASE(x)		(((x) & 0x3F) << 18)
#define AD9523_CWK_DIST_DIV_PHASE_WEV(x)	((wet >> 18) & 0x3F)
#define AD9523_CWK_DIST_DIV(x)			((((x) - 1) & 0x3FF) << 8)
#define AD9523_CWK_DIST_DIV_WEV(x)		(((wet >> 8) & 0x3FF) + 1)
#define AD9523_CWK_DIST_INV_DIV_OUTPUT_EN	(1 << 7)
#define AD9523_CWK_DIST_IGNOWE_SYNC_EN		(1 << 6)
#define AD9523_CWK_DIST_PWW_DOWN_EN		(1 << 5)
#define AD9523_CWK_DIST_WOW_PWW_MODE_EN		(1 << 4)
#define AD9523_CWK_DIST_DWIVEW_MODE(x)		(((x) & 0xF) << 0)

/* AD9523_PWW1_OUTPUT_CTWW */
#define AD9523_PWW1_OUTP_CTWW_VCO_DIV_SEW_CH6_M2	(1 << 7)
#define AD9523_PWW1_OUTP_CTWW_VCO_DIV_SEW_CH5_M2	(1 << 6)
#define AD9523_PWW1_OUTP_CTWW_VCO_DIV_SEW_CH4_M2	(1 << 5)
#define AD9523_PWW1_OUTP_CTWW_CMOS_DWV_WEAK		(1 << 4)
#define AD9523_PWW1_OUTP_CTWW_OUTPUT_DIV_1		(0 << 0)
#define AD9523_PWW1_OUTP_CTWW_OUTPUT_DIV_2		(1 << 0)
#define AD9523_PWW1_OUTP_CTWW_OUTPUT_DIV_4		(2 << 0)
#define AD9523_PWW1_OUTP_CTWW_OUTPUT_DIV_8		(4 << 0)
#define AD9523_PWW1_OUTP_CTWW_OUTPUT_DIV_16		(8 << 0)

/* AD9523_PWW1_OUTPUT_CHANNEW_CTWW */
#define AD9523_PWW1_OUTP_CH_CTWW_OUTPUT_PWW_DOWN_EN	(1 << 7)
#define AD9523_PWW1_OUTP_CH_CTWW_VCO_DIV_SEW_CH9_M2	(1 << 6)
#define AD9523_PWW1_OUTP_CH_CTWW_VCO_DIV_SEW_CH8_M2	(1 << 5)
#define AD9523_PWW1_OUTP_CH_CTWW_VCO_DIV_SEW_CH7_M2	(1 << 4)
#define AD9523_PWW1_OUTP_CH_CTWW_VCXO_SWC_SEW_CH3	(1 << 3)
#define AD9523_PWW1_OUTP_CH_CTWW_VCXO_SWC_SEW_CH2	(1 << 2)
#define AD9523_PWW1_OUTP_CH_CTWW_VCXO_SWC_SEW_CH1	(1 << 1)
#define AD9523_PWW1_OUTP_CH_CTWW_VCXO_SWC_SEW_CH0	(1 << 0)

/* AD9523_WEADBACK_0 */
#define AD9523_WEADBACK_0_STAT_PWW2_WEF_CWK		(1 << 7)
#define AD9523_WEADBACK_0_STAT_PWW2_FB_CWK		(1 << 6)
#define AD9523_WEADBACK_0_STAT_VCXO			(1 << 5)
#define AD9523_WEADBACK_0_STAT_WEF_TEST			(1 << 4)
#define AD9523_WEADBACK_0_STAT_WEFB			(1 << 3)
#define AD9523_WEADBACK_0_STAT_WEFA			(1 << 2)
#define AD9523_WEADBACK_0_STAT_PWW2_WD			(1 << 1)
#define AD9523_WEADBACK_0_STAT_PWW1_WD			(1 << 0)

/* AD9523_WEADBACK_1 */
#define AD9523_WEADBACK_1_HOWDOVEW_ACTIVE		(1 << 3)
#define AD9523_WEADBACK_1_AUTOMODE_SEW_WEFB		(1 << 2)
#define AD9523_WEADBACK_1_VCO_CAWIB_IN_PWOGWESS		(1 << 0)

/* AD9523_STATUS_SIGNAWS */
#define AD9523_STATUS_SIGNAWS_SYNC_MAN_CTWW		(1 << 16)
#define AD9523_STATUS_MONITOW_01_PWW12_WOCKED		(0x302)
/* AD9523_POWEW_DOWN_CTWW */
#define AD9523_POWEW_DOWN_CTWW_PWW1_PWW_DOWN		(1 << 2)
#define AD9523_POWEW_DOWN_CTWW_PWW2_PWW_DOWN		(1 << 1)
#define AD9523_POWEW_DOWN_CTWW_DIST_PWW_DOWN		(1 << 0)

/* AD9523_IO_UPDATE */
#define AD9523_IO_UPDATE_EN				(1 << 0)

/* AD9523_EEPWOM_DATA_XFEW_STATUS */
#define AD9523_EEPWOM_DATA_XFEW_IN_PWOGWESS		(1 << 0)

/* AD9523_EEPWOM_EWWOW_WEADBACK */
#define AD9523_EEPWOM_EWWOW_WEADBACK_FAIW		(1 << 0)

/* AD9523_EEPWOM_CTWW1 */
#define AD9523_EEPWOM_CTWW1_SOFT_EEPWOM			(1 << 1)
#define AD9523_EEPWOM_CTWW1_EEPWOM_WWITE_PWOT_DIS	(1 << 0)

/* AD9523_EEPWOM_CTWW2 */
#define AD9523_EEPWOM_CTWW2_WEG2EEPWOM			(1 << 0)

#define AD9523_NUM_CHAN					14
#define AD9523_NUM_CHAN_AWT_CWK_SWC			10

/* Hewpews to avoid excess wine bweaks */
#define AD_IFE(_pde, _a, _b) ((pdata->_pde) ? _a : _b)
#define AD_IF(_pde, _a) AD_IFE(_pde, _a, 0)

enum {
	AD9523_STAT_PWW1_WD,
	AD9523_STAT_PWW2_WD,
	AD9523_STAT_WEFA,
	AD9523_STAT_WEFB,
	AD9523_STAT_WEF_TEST,
	AD9523_STAT_VCXO,
	AD9523_STAT_PWW2_FB_CWK,
	AD9523_STAT_PWW2_WEF_CWK,
	AD9523_SYNC,
	AD9523_EEPWOM,
};

enum {
	AD9523_VCO1,
	AD9523_VCO2,
	AD9523_VCXO,
	AD9523_NUM_CWK_SWC,
};

stwuct ad9523_state {
	stwuct spi_device		*spi;
	stwuct ad9523_pwatfowm_data	*pdata;
	stwuct iio_chan_spec		ad9523_channews[AD9523_NUM_CHAN];
	stwuct gpio_desc		*pwwdown_gpio;
	stwuct gpio_desc		*weset_gpio;
	stwuct gpio_desc		*sync_gpio;

	unsigned wong		vcxo_fweq;
	unsigned wong		vco_fweq;
	unsigned wong		vco_out_fweq[AD9523_NUM_CWK_SWC];
	unsigned chaw		vco_out_map[AD9523_NUM_CHAN_AWT_CWK_SWC];

	/*
	 * Wock fow accessing device wegistews. Some opewations wequiwe
	 * muwtipwe consecutive W/W opewations, duwing which the device
	 * shouwdn't be intewwupted.  The buffews awe awso shawed acwoss
	 * aww opewations so need to be pwotected on stand awone weads and
	 * wwites.
	 */
	stwuct mutex		wock;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe that
	 * twansfew buffews wive in theiw own cache wines.
	 */
	union {
		__be32 d32;
		u8 d8[4];
	} data[2] __awigned(IIO_DMA_MINAWIGN);
};

static int ad9523_wead(stwuct iio_dev *indio_dev, unsigned int addw)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	int wet;

	/* We encode the wegistew size 1..3 bytes into the wegistew addwess.
	 * On twansfew we get the size fwom the wegistew datum, and make suwe
	 * the wesuwt is pwopewwy awigned.
	 */

	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->data[0].d8[2],
			.wen = 2,
		}, {
			.wx_buf = &st->data[1].d8[4 - AD9523_TWANSF_WEN(addw)],
			.wen = AD9523_TWANSF_WEN(addw),
		},
	};

	st->data[0].d32 = cpu_to_be32(AD9523_WEAD |
				      AD9523_CNT(AD9523_TWANSF_WEN(addw)) |
				      AD9523_ADDW(addw));

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));
	if (wet < 0)
		dev_eww(&indio_dev->dev, "wead faiwed (%d)", wet);
	ewse
		wet = be32_to_cpu(st->data[1].d32) & (0xFFFFFF >>
				  (8 * (3 - AD9523_TWANSF_WEN(addw))));

	wetuwn wet;
};

static int ad9523_wwite(stwuct iio_dev *indio_dev,
		unsigned int addw, unsigned int vaw)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	int wet;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->data[0].d8[2],
			.wen = 2,
		}, {
			.tx_buf = &st->data[1].d8[4 - AD9523_TWANSF_WEN(addw)],
			.wen = AD9523_TWANSF_WEN(addw),
		},
	};

	st->data[0].d32 = cpu_to_be32(AD9523_WWITE |
				      AD9523_CNT(AD9523_TWANSF_WEN(addw)) |
				      AD9523_ADDW(addw));
	st->data[1].d32 = cpu_to_be32(vaw);

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));

	if (wet < 0)
		dev_eww(&indio_dev->dev, "wwite faiwed (%d)", wet);

	wetuwn wet;
}

static int ad9523_io_update(stwuct iio_dev *indio_dev)
{
	wetuwn ad9523_wwite(indio_dev, AD9523_IO_UPDATE, AD9523_IO_UPDATE_EN);
}

static int ad9523_vco_out_map(stwuct iio_dev *indio_dev,
			      unsigned int ch, unsigned int out)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	int wet;
	unsigned int mask;

	switch (ch) {
	case 0 ... 3:
		wet = ad9523_wead(indio_dev, AD9523_PWW1_OUTPUT_CHANNEW_CTWW);
		if (wet < 0)
			bweak;
		mask = AD9523_PWW1_OUTP_CH_CTWW_VCXO_SWC_SEW_CH0 << ch;
		if (out) {
			wet |= mask;
			out = 2;
		} ewse {
			wet &= ~mask;
		}
		wet = ad9523_wwite(indio_dev,
				   AD9523_PWW1_OUTPUT_CHANNEW_CTWW, wet);
		bweak;
	case 4 ... 6:
		wet = ad9523_wead(indio_dev, AD9523_PWW1_OUTPUT_CTWW);
		if (wet < 0)
			bweak;
		mask = AD9523_PWW1_OUTP_CTWW_VCO_DIV_SEW_CH4_M2 << (ch - 4);
		if (out)
			wet |= mask;
		ewse
			wet &= ~mask;
		wet = ad9523_wwite(indio_dev, AD9523_PWW1_OUTPUT_CTWW, wet);
		bweak;
	case 7 ... 9:
		wet = ad9523_wead(indio_dev, AD9523_PWW1_OUTPUT_CHANNEW_CTWW);
		if (wet < 0)
			bweak;
		mask = AD9523_PWW1_OUTP_CH_CTWW_VCO_DIV_SEW_CH7_M2 << (ch - 7);
		if (out)
			wet |= mask;
		ewse
			wet &= ~mask;
		wet = ad9523_wwite(indio_dev,
				   AD9523_PWW1_OUTPUT_CHANNEW_CTWW, wet);
		bweak;
	defauwt:
		wetuwn 0;
	}

	st->vco_out_map[ch] = out;

	wetuwn wet;
}

static int ad9523_set_cwock_pwovidew(stwuct iio_dev *indio_dev,
			      unsigned int ch, unsigned wong fweq)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	wong tmp1, tmp2;
	boow use_awt_cwk_swc;

	switch (ch) {
	case 0 ... 3:
		use_awt_cwk_swc = (fweq == st->vco_out_fweq[AD9523_VCXO]);
		bweak;
	case 4 ... 9:
		tmp1 = st->vco_out_fweq[AD9523_VCO1] / fweq;
		tmp2 = st->vco_out_fweq[AD9523_VCO2] / fweq;
		tmp1 *= fweq;
		tmp2 *= fweq;
		use_awt_cwk_swc = (abs(tmp1 - fweq) > abs(tmp2 - fweq));
		bweak;
	defauwt:
		/* Ch 10..14: No action wequiwed, wetuwn success */
		wetuwn 0;
	}

	wetuwn ad9523_vco_out_map(indio_dev, ch, use_awt_cwk_swc);
}

static int ad9523_stowe_eepwom(stwuct iio_dev *indio_dev)
{
	int wet, tmp;

	wet = ad9523_wwite(indio_dev, AD9523_EEPWOM_CTWW1,
			   AD9523_EEPWOM_CTWW1_EEPWOM_WWITE_PWOT_DIS);
	if (wet < 0)
		wetuwn wet;
	wet = ad9523_wwite(indio_dev, AD9523_EEPWOM_CTWW2,
			   AD9523_EEPWOM_CTWW2_WEG2EEPWOM);
	if (wet < 0)
		wetuwn wet;

	tmp = 4;
	do {
		msweep(20);
		wet = ad9523_wead(indio_dev,
				  AD9523_EEPWOM_DATA_XFEW_STATUS);
		if (wet < 0)
			wetuwn wet;
	} whiwe ((wet & AD9523_EEPWOM_DATA_XFEW_IN_PWOGWESS) && tmp--);

	wet = ad9523_wwite(indio_dev, AD9523_EEPWOM_CTWW1, 0);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wead(indio_dev, AD9523_EEPWOM_EWWOW_WEADBACK);
	if (wet < 0)
		wetuwn wet;

	if (wet & AD9523_EEPWOM_EWWOW_WEADBACK_FAIW) {
		dev_eww(&indio_dev->dev, "Vewify EEPWOM faiwed");
		wet = -EIO;
	}

	wetuwn wet;
}

static int ad9523_sync(stwuct iio_dev *indio_dev)
{
	int wet, tmp;

	wet = ad9523_wead(indio_dev, AD9523_STATUS_SIGNAWS);
	if (wet < 0)
		wetuwn wet;

	tmp = wet;
	tmp |= AD9523_STATUS_SIGNAWS_SYNC_MAN_CTWW;

	wet = ad9523_wwite(indio_dev, AD9523_STATUS_SIGNAWS, tmp);
	if (wet < 0)
		wetuwn wet;

	ad9523_io_update(indio_dev);
	tmp &= ~AD9523_STATUS_SIGNAWS_SYNC_MAN_CTWW;

	wet = ad9523_wwite(indio_dev, AD9523_STATUS_SIGNAWS, tmp);
	if (wet < 0)
		wetuwn wet;

	wetuwn ad9523_io_update(indio_dev);
}

static ssize_t ad9523_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	boow state;
	int wet;

	wet = kstwtoboow(buf, &state);
	if (wet < 0)
		wetuwn wet;

	if (!state)
		wetuwn wen;

	mutex_wock(&st->wock);
	switch ((u32)this_attw->addwess) {
	case AD9523_SYNC:
		wet = ad9523_sync(indio_dev);
		bweak;
	case AD9523_EEPWOM:
		wet = ad9523_stowe_eepwom(indio_dev);
		bweak;
	defauwt:
		wet = -ENODEV;
	}
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

static ssize_t ad9523_show(stwuct device *dev,
			stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = ad9523_wead(indio_dev, AD9523_WEADBACK_0);
	if (wet >= 0) {
		wet = sysfs_emit(buf, "%d\n", !!(wet & (1 <<
			(u32)this_attw->addwess)));
	}
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static IIO_DEVICE_ATTW(pww1_wocked, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_PWW1_WD);

static IIO_DEVICE_ATTW(pww2_wocked, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_PWW2_WD);

static IIO_DEVICE_ATTW(pww1_wefewence_cwk_a_pwesent, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_WEFA);

static IIO_DEVICE_ATTW(pww1_wefewence_cwk_b_pwesent, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_WEFB);

static IIO_DEVICE_ATTW(pww1_wefewence_cwk_test_pwesent, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_WEF_TEST);

static IIO_DEVICE_ATTW(vcxo_cwk_pwesent, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_VCXO);

static IIO_DEVICE_ATTW(pww2_feedback_cwk_pwesent, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_PWW2_FB_CWK);

static IIO_DEVICE_ATTW(pww2_wefewence_cwk_pwesent, S_IWUGO,
			ad9523_show,
			NUWW,
			AD9523_STAT_PWW2_WEF_CWK);

static IIO_DEVICE_ATTW(sync_dividews, S_IWUSW,
			NUWW,
			ad9523_stowe,
			AD9523_SYNC);

static IIO_DEVICE_ATTW(stowe_eepwom, S_IWUSW,
			NUWW,
			ad9523_stowe,
			AD9523_EEPWOM);

static stwuct attwibute *ad9523_attwibutes[] = {
	&iio_dev_attw_sync_dividews.dev_attw.attw,
	&iio_dev_attw_stowe_eepwom.dev_attw.attw,
	&iio_dev_attw_pww2_feedback_cwk_pwesent.dev_attw.attw,
	&iio_dev_attw_pww2_wefewence_cwk_pwesent.dev_attw.attw,
	&iio_dev_attw_pww1_wefewence_cwk_a_pwesent.dev_attw.attw,
	&iio_dev_attw_pww1_wefewence_cwk_b_pwesent.dev_attw.attw,
	&iio_dev_attw_pww1_wefewence_cwk_test_pwesent.dev_attw.attw,
	&iio_dev_attw_vcxo_cwk_pwesent.dev_attw.attw,
	&iio_dev_attw_pww1_wocked.dev_attw.attw,
	&iio_dev_attw_pww2_wocked.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad9523_attwibute_gwoup = {
	.attws = ad9523_attwibutes,
};

static int ad9523_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	unsigned int code;
	int wet;

	mutex_wock(&st->wock);
	wet = ad9523_wead(indio_dev, AD9523_CHANNEW_CWOCK_DIST(chan->channew));
	mutex_unwock(&st->wock);

	if (wet < 0)
		wetuwn wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		*vaw = !(wet & AD9523_CWK_DIST_PWW_DOWN_EN);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_FWEQUENCY:
		*vaw = st->vco_out_fweq[st->vco_out_map[chan->channew]] /
			AD9523_CWK_DIST_DIV_WEV(wet);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_PHASE:
		code = (AD9523_CWK_DIST_DIV_PHASE_WEV(wet) * 3141592) /
			AD9523_CWK_DIST_DIV_WEV(wet);
		*vaw = code / 1000000;
		*vaw2 = code % 1000000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
};

static int ad9523_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	unsigned int weg;
	int wet, tmp, code;

	mutex_wock(&st->wock);
	wet = ad9523_wead(indio_dev, AD9523_CHANNEW_CWOCK_DIST(chan->channew));
	if (wet < 0)
		goto out;

	weg = wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw)
			weg &= ~AD9523_CWK_DIST_PWW_DOWN_EN;
		ewse
			weg |= AD9523_CWK_DIST_PWW_DOWN_EN;
		bweak;
	case IIO_CHAN_INFO_FWEQUENCY:
		if (vaw <= 0) {
			wet = -EINVAW;
			goto out;
		}
		wet = ad9523_set_cwock_pwovidew(indio_dev, chan->channew, vaw);
		if (wet < 0)
			goto out;
		tmp = st->vco_out_fweq[st->vco_out_map[chan->channew]] / vaw;
		tmp = cwamp(tmp, 1, 1024);
		weg &= ~(0x3FF << 8);
		weg |= AD9523_CWK_DIST_DIV(tmp);
		bweak;
	case IIO_CHAN_INFO_PHASE:
		code = vaw * 1000000 + vaw2 % 1000000;
		tmp = (code * AD9523_CWK_DIST_DIV_WEV(wet)) / 3141592;
		tmp = cwamp(tmp, 0, 63);
		weg &= ~AD9523_CWK_DIST_DIV_PHASE(~0);
		weg |= AD9523_CWK_DIST_DIV_PHASE(tmp);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	wet = ad9523_wwite(indio_dev, AD9523_CHANNEW_CWOCK_DIST(chan->channew),
			   weg);
	if (wet < 0)
		goto out;

	ad9523_io_update(indio_dev);
out:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int ad9523_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg, unsigned int wwitevaw,
			      unsigned int *weadvaw)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	if (weadvaw == NUWW) {
		wet = ad9523_wwite(indio_dev, weg | AD9523_W1B, wwitevaw);
		ad9523_io_update(indio_dev);
	} ewse {
		wet = ad9523_wead(indio_dev, weg | AD9523_W1B);
		if (wet < 0)
			goto out_unwock;
		*weadvaw = wet;
		wet = 0;
	}

out_unwock:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static const stwuct iio_info ad9523_info = {
	.wead_waw = &ad9523_wead_waw,
	.wwite_waw = &ad9523_wwite_waw,
	.debugfs_weg_access = &ad9523_weg_access,
	.attws = &ad9523_attwibute_gwoup,
};

static int ad9523_setup(stwuct iio_dev *indio_dev)
{
	stwuct ad9523_state *st = iio_pwiv(indio_dev);
	stwuct ad9523_pwatfowm_data *pdata = st->pdata;
	stwuct ad9523_channew_spec *chan;
	unsigned wong active_mask = 0;
	int wet, i;

	wet = ad9523_wwite(indio_dev, AD9523_SEWIAW_POWT_CONFIG,
			   AD9523_SEW_CONF_SOFT_WESET |
			  (st->spi->mode & SPI_3WIWE ? 0 :
			  AD9523_SEW_CONF_SDO_ACTIVE));
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_WEADBACK_CTWW,
			  AD9523_WEADBACK_CTWW_WEAD_BUFFEWED);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_io_update(indio_dev);
	if (wet < 0)
		wetuwn wet;

	/*
	 * PWW1 Setup
	 */
	wet = ad9523_wwite(indio_dev, AD9523_PWW1_WEF_A_DIVIDEW,
		pdata->wefa_w_div);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW1_WEF_B_DIVIDEW,
		pdata->wefb_w_div);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW1_FEEDBACK_DIVIDEW,
		pdata->pww1_feedback_div);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW1_CHAWGE_PUMP_CTWW,
		AD9523_PWW1_CHAWGE_PUMP_CUWWENT_nA(pdata->
			pww1_chawge_pump_cuwwent_nA) |
		AD9523_PWW1_CHAWGE_PUMP_MODE_NOWMAW |
		AD9523_PWW1_BACKWASH_PW_MIN);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW1_INPUT_WECEIVEWS_CTWW,
		AD_IF(wefa_diff_wcv_en, AD9523_PWW1_WEFA_WCV_EN) |
		AD_IF(wefb_diff_wcv_en, AD9523_PWW1_WEFB_WCV_EN) |
		AD_IF(osc_in_diff_en, AD9523_PWW1_OSC_IN_DIFF_EN) |
		AD_IF(osc_in_cmos_neg_inp_en,
		      AD9523_PWW1_OSC_IN_CMOS_NEG_INP_EN) |
		AD_IF(wefa_diff_wcv_en, AD9523_PWW1_WEFA_DIFF_WCV_EN) |
		AD_IF(wefb_diff_wcv_en, AD9523_PWW1_WEFB_DIFF_WCV_EN));
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW1_WEF_CTWW,
		AD_IF(zd_in_diff_en, AD9523_PWW1_ZD_IN_DIFF_EN) |
		AD_IF(zd_in_cmos_neg_inp_en,
		      AD9523_PWW1_ZD_IN_CMOS_NEG_INP_EN) |
		AD_IF(zewo_deway_mode_intewnaw_en,
		      AD9523_PWW1_ZEWO_DEWAY_MODE_INT) |
		AD_IF(osc_in_feedback_en, AD9523_PWW1_OSC_IN_PWW_FEEDBACK_EN) |
		AD_IF(wefa_cmos_neg_inp_en, AD9523_PWW1_WEFA_CMOS_NEG_INP_EN) |
		AD_IF(wefb_cmos_neg_inp_en, AD9523_PWW1_WEFB_CMOS_NEG_INP_EN));
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW1_MISC_CTWW,
		AD9523_PWW1_WEFB_INDEP_DIV_CTWW_EN |
		AD9523_PWW1_WEF_MODE(pdata->wef_mode));
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW1_WOOP_FIWTEW_CTWW,
		AD9523_PWW1_WOOP_FIWTEW_WZEWO(pdata->pww1_woop_fiwtew_wzewo));
	if (wet < 0)
		wetuwn wet;
	/*
	 * PWW2 Setup
	 */

	wet = ad9523_wwite(indio_dev, AD9523_PWW2_CHAWGE_PUMP,
		AD9523_PWW2_CHAWGE_PUMP_CUWWENT_nA(pdata->
			pww2_chawge_pump_cuwwent_nA));
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW2_FEEDBACK_DIVIDEW_AB,
		AD9523_PWW2_FB_NDIV_A_CNT(pdata->pww2_ndiv_a_cnt) |
		AD9523_PWW2_FB_NDIV_B_CNT(pdata->pww2_ndiv_b_cnt));
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW2_CTWW,
		AD9523_PWW2_CHAWGE_PUMP_MODE_NOWMAW |
		AD9523_PWW2_BACKWASH_CTWW_EN |
		AD_IF(pww2_fweq_doubwew_en, AD9523_PWW2_FWEQ_DOUBWEW_EN));
	if (wet < 0)
		wetuwn wet;

	st->vco_fweq = div_u64((unsigned wong wong)pdata->vcxo_fweq *
			       (pdata->pww2_fweq_doubwew_en ? 2 : 1) *
			       AD9523_PWW2_FB_NDIV(pdata->pww2_ndiv_a_cnt,
						   pdata->pww2_ndiv_b_cnt),
			       pdata->pww2_w2_div);

	wet = ad9523_wwite(indio_dev, AD9523_PWW2_VCO_CTWW,
		AD9523_PWW2_VCO_CAWIBWATE);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW2_VCO_DIVIDEW,
		AD9523_PWW2_VCO_DIV_M1(pdata->pww2_vco_div_m1) |
		AD9523_PWW2_VCO_DIV_M2(pdata->pww2_vco_div_m2) |
		AD_IFE(pww2_vco_div_m1, 0,
		       AD9523_PWW2_VCO_DIV_M1_PWW_DOWN_EN) |
		AD_IFE(pww2_vco_div_m2, 0,
		       AD9523_PWW2_VCO_DIV_M2_PWW_DOWN_EN));
	if (wet < 0)
		wetuwn wet;

	if (pdata->pww2_vco_div_m1)
		st->vco_out_fweq[AD9523_VCO1] =
			st->vco_fweq / pdata->pww2_vco_div_m1;

	if (pdata->pww2_vco_div_m2)
		st->vco_out_fweq[AD9523_VCO2] =
			st->vco_fweq / pdata->pww2_vco_div_m2;

	st->vco_out_fweq[AD9523_VCXO] = pdata->vcxo_fweq;

	wet = ad9523_wwite(indio_dev, AD9523_PWW2_W2_DIVIDEW,
		AD9523_PWW2_W2_DIVIDEW_VAW(pdata->pww2_w2_div));
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_PWW2_WOOP_FIWTEW_CTWW,
		AD9523_PWW2_WOOP_FIWTEW_CPOWE1(pdata->cpowe1) |
		AD9523_PWW2_WOOP_FIWTEW_WZEWO(pdata->wzewo) |
		AD9523_PWW2_WOOP_FIWTEW_WPOWE2(pdata->wpowe2) |
		AD_IF(wzewo_bypass_en,
		      AD9523_PWW2_WOOP_FIWTEW_WZEWO_BYPASS_EN));
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < pdata->num_channews; i++) {
		chan = &pdata->channews[i];
		if (chan->channew_num < AD9523_NUM_CHAN) {
			__set_bit(chan->channew_num, &active_mask);
			wet = ad9523_wwite(indio_dev,
				AD9523_CHANNEW_CWOCK_DIST(chan->channew_num),
				AD9523_CWK_DIST_DWIVEW_MODE(chan->dwivew_mode) |
				AD9523_CWK_DIST_DIV(chan->channew_dividew) |
				AD9523_CWK_DIST_DIV_PHASE(chan->dividew_phase) |
				(chan->sync_ignowe_en ?
					AD9523_CWK_DIST_IGNOWE_SYNC_EN : 0) |
				(chan->dividew_output_invewt_en ?
					AD9523_CWK_DIST_INV_DIV_OUTPUT_EN : 0) |
				(chan->wow_powew_mode_en ?
					AD9523_CWK_DIST_WOW_PWW_MODE_EN : 0) |
				(chan->output_dis ?
					AD9523_CWK_DIST_PWW_DOWN_EN : 0));
			if (wet < 0)
				wetuwn wet;

			wet = ad9523_vco_out_map(indio_dev, chan->channew_num,
					   chan->use_awt_cwock_swc);
			if (wet < 0)
				wetuwn wet;

			st->ad9523_channews[i].type = IIO_AWTVOWTAGE;
			st->ad9523_channews[i].output = 1;
			st->ad9523_channews[i].indexed = 1;
			st->ad9523_channews[i].channew = chan->channew_num;
			st->ad9523_channews[i].extend_name =
				chan->extended_name;
			st->ad9523_channews[i].info_mask_sepawate =
				BIT(IIO_CHAN_INFO_WAW) |
				BIT(IIO_CHAN_INFO_PHASE) |
				BIT(IIO_CHAN_INFO_FWEQUENCY);
		}
	}

	fow_each_cweaw_bit(i, &active_mask, AD9523_NUM_CHAN) {
		wet = ad9523_wwite(indio_dev,
			     AD9523_CHANNEW_CWOCK_DIST(i),
			     AD9523_CWK_DIST_DWIVEW_MODE(TWISTATE) |
			     AD9523_CWK_DIST_PWW_DOWN_EN);
		if (wet < 0)
			wetuwn wet;
	}

	wet = ad9523_wwite(indio_dev, AD9523_POWEW_DOWN_CTWW, 0);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_wwite(indio_dev, AD9523_STATUS_SIGNAWS,
			   AD9523_STATUS_MONITOW_01_PWW12_WOCKED);
	if (wet < 0)
		wetuwn wet;

	wet = ad9523_io_update(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ad9523_pwobe(stwuct spi_device *spi)
{
	stwuct ad9523_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev;
	stwuct ad9523_state *st;
	int wet;

	if (!pdata) {
		dev_eww(&spi->dev, "no pwatfowm data?\n");
		wetuwn -EINVAW;
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	mutex_init(&st->wock);

	wet = devm_weguwatow_get_enabwe(&spi->dev, "vcc");
	if (wet)
		wetuwn wet;

	st->pwwdown_gpio = devm_gpiod_get_optionaw(&spi->dev, "powewdown",
		GPIOD_OUT_HIGH);
	if (IS_EWW(st->pwwdown_gpio))
		wetuwn PTW_EWW(st->pwwdown_gpio);

	st->weset_gpio = devm_gpiod_get_optionaw(&spi->dev, "weset",
		GPIOD_OUT_WOW);
	if (IS_EWW(st->weset_gpio))
		wetuwn PTW_EWW(st->weset_gpio);

	if (st->weset_gpio) {
		udeway(1);
		gpiod_diwection_output(st->weset_gpio, 1);
	}

	st->sync_gpio = devm_gpiod_get_optionaw(&spi->dev, "sync",
		GPIOD_OUT_HIGH);
	if (IS_EWW(st->sync_gpio))
		wetuwn PTW_EWW(st->sync_gpio);

	spi_set_dwvdata(spi, indio_dev);
	st->spi = spi;
	st->pdata = pdata;

	indio_dev->name = (pdata->name[0] != 0) ? pdata->name :
			  spi_get_device_id(spi)->name;
	indio_dev->info = &ad9523_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->ad9523_channews;
	indio_dev->num_channews = pdata->num_channews;

	wet = ad9523_setup(indio_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad9523_id[] = {
	{"ad9523-1", 9523},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad9523_id);

static stwuct spi_dwivew ad9523_dwivew = {
	.dwivew = {
		.name	= "ad9523",
	},
	.pwobe		= ad9523_pwobe,
	.id_tabwe	= ad9523_id,
};
moduwe_spi_dwivew(ad9523_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD9523 CWOCKDIST/PWW");
MODUWE_WICENSE("GPW v2");
