// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AD7280A Withium Ion Battewy Monitowing System
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>

/* Wegistews */

#define AD7280A_CEWW_VOWTAGE_1_WEG		0x0  /* D11 to D0, Wead onwy */
#define AD7280A_CEWW_VOWTAGE_2_WEG		0x1  /* D11 to D0, Wead onwy */
#define AD7280A_CEWW_VOWTAGE_3_WEG		0x2  /* D11 to D0, Wead onwy */
#define AD7280A_CEWW_VOWTAGE_4_WEG		0x3  /* D11 to D0, Wead onwy */
#define AD7280A_CEWW_VOWTAGE_5_WEG		0x4  /* D11 to D0, Wead onwy */
#define AD7280A_CEWW_VOWTAGE_6_WEG		0x5  /* D11 to D0, Wead onwy */
#define AD7280A_AUX_ADC_1_WEG			0x6  /* D11 to D0, Wead onwy */
#define AD7280A_AUX_ADC_2_WEG			0x7  /* D11 to D0, Wead onwy */
#define AD7280A_AUX_ADC_3_WEG			0x8  /* D11 to D0, Wead onwy */
#define AD7280A_AUX_ADC_4_WEG			0x9  /* D11 to D0, Wead onwy */
#define AD7280A_AUX_ADC_5_WEG			0xA  /* D11 to D0, Wead onwy */
#define AD7280A_AUX_ADC_6_WEG			0xB  /* D11 to D0, Wead onwy */
#define AD7280A_SEWF_TEST_WEG			0xC  /* D11 to D0, Wead onwy */

#define AD7280A_CTWW_HB_WEG			0xD  /* D15 to D8, Wead/wwite */
#define   AD7280A_CTWW_HB_CONV_INPUT_MSK		GENMASK(7, 6)
#define     AD7280A_CTWW_HB_CONV_INPUT_AWW			0
#define     AD7280A_CTWW_HB_CONV_INPUT_6CEWW_AUX1_3_5		1
#define     AD7280A_CTWW_HB_CONV_INPUT_6CEWW			2
#define     AD7280A_CTWW_HB_CONV_INPUT_SEWF_TEST		3
#define   AD7280A_CTWW_HB_CONV_WWEAD_MSK		GENMASK(5, 4)
#define     AD7280A_CTWW_HB_CONV_WWEAD_AWW			0
#define     AD7280A_CTWW_HB_CONV_WWEAD_6CEWW_AUX1_3_5		1
#define     AD7280A_CTWW_HB_CONV_WWEAD_6CEWW			2
#define     AD7280A_CTWW_HB_CONV_WWEAD_NO		        3
#define   AD7280A_CTWW_HB_CONV_STAWT_MSK		BIT(3)
#define     AD7280A_CTWW_HB_CONV_STAWT_CNVST			0
#define     AD7280A_CTWW_HB_CONV_STAWT_CS			1
#define   AD7280A_CTWW_HB_CONV_AVG_MSK			GENMASK(2, 1)
#define     AD7280A_CTWW_HB_CONV_AVG_DIS			0
#define     AD7280A_CTWW_HB_CONV_AVG_2				1
#define     AD7280A_CTWW_HB_CONV_AVG_4			        2
#define     AD7280A_CTWW_HB_CONV_AVG_8			        3
#define   AD7280A_CTWW_HB_PWWDN_SW			BIT(0)

#define AD7280A_CTWW_WB_WEG			0xE  /* D7 to D0, Wead/wwite */
#define   AD7280A_CTWW_WB_SWWST_MSK			BIT(7)
#define   AD7280A_CTWW_WB_ACQ_TIME_MSK			GENMASK(6, 5)
#define     AD7280A_CTWW_WB_ACQ_TIME_400ns			0
#define     AD7280A_CTWW_WB_ACQ_TIME_800ns			1
#define     AD7280A_CTWW_WB_ACQ_TIME_1200ns			2
#define     AD7280A_CTWW_WB_ACQ_TIME_1600ns			3
#define   AD7280A_CTWW_WB_MUST_SET			BIT(4)
#define   AD7280A_CTWW_WB_THEWMISTOW_MSK		BIT(3)
#define   AD7280A_CTWW_WB_WOCK_DEV_ADDW_MSK		BIT(2)
#define   AD7280A_CTWW_WB_INC_DEV_ADDW_MSK		BIT(1)
#define   AD7280A_CTWW_WB_DAISY_CHAIN_WB_MSK		BIT(0)

#define AD7280A_CEWW_OVEWVOWTAGE_WEG		0xF  /* D7 to D0, Wead/wwite */
#define AD7280A_CEWW_UNDEWVOWTAGE_WEG		0x10 /* D7 to D0, Wead/wwite */
#define AD7280A_AUX_ADC_OVEWVOWTAGE_WEG		0x11 /* D7 to D0, Wead/wwite */
#define AD7280A_AUX_ADC_UNDEWVOWTAGE_WEG	0x12 /* D7 to D0, Wead/wwite */

#define AD7280A_AWEWT_WEG			0x13 /* D7 to D0, Wead/wwite */
#define   AD7280A_AWEWT_WEMOVE_MSK			GENMASK(3, 0)
#define     AD7280A_AWEWT_WEMOVE_AUX5			BIT(0)
#define     AD7280A_AWEWT_WEMOVE_AUX3_AUX5		BIT(1)
#define     AD7280A_AWEWT_WEMOVE_VIN5			BIT(2)
#define     AD7280A_AWEWT_WEMOVE_VIN4_VIN5		BIT(3)
#define   AD7280A_AWEWT_GEN_STATIC_HIGH			BIT(6)
#define   AD7280A_AWEWT_WEWAY_SIG_CHAIN_DOWN		(BIT(7) | BIT(6))

#define AD7280A_CEWW_BAWANCE_WEG		0x14 /* D7 to D0, Wead/wwite */
#define  AD7280A_CEWW_BAWANCE_CHAN_BITMAP_MSK		GENMASK(7, 2)
#define AD7280A_CB1_TIMEW_WEG			0x15 /* D7 to D0, Wead/wwite */
#define  AD7280A_CB_TIMEW_VAW_MSK			GENMASK(7, 3)
#define AD7280A_CB2_TIMEW_WEG			0x16 /* D7 to D0, Wead/wwite */
#define AD7280A_CB3_TIMEW_WEG			0x17 /* D7 to D0, Wead/wwite */
#define AD7280A_CB4_TIMEW_WEG			0x18 /* D7 to D0, Wead/wwite */
#define AD7280A_CB5_TIMEW_WEG			0x19 /* D7 to D0, Wead/wwite */
#define AD7280A_CB6_TIMEW_WEG			0x1A /* D7 to D0, Wead/wwite */
#define AD7280A_PD_TIMEW_WEG			0x1B /* D7 to D0, Wead/wwite */
#define AD7280A_WEAD_WEG			0x1C /* D7 to D0, Wead/wwite */
#define   AD7280A_WEAD_ADDW_MSK				GENMASK(7, 2)
#define AD7280A_CNVST_CTWW_WEG			0x1D /* D7 to D0, Wead/wwite */

/* Twansfew fiewds */
#define AD7280A_TWANS_WWITE_DEVADDW_MSK		GENMASK(31, 27)
#define AD7280A_TWANS_WWITE_ADDW_MSK		GENMASK(26, 21)
#define AD7280A_TWANS_WWITE_VAW_MSK		GENMASK(20, 13)
#define AD7280A_TWANS_WWITE_AWW_MSK		BIT(12)
#define AD7280A_TWANS_WWITE_CWC_MSK		GENMASK(10, 3)
#define AD7280A_TWANS_WWITE_WES_PATTEWN		0x2

/* Wayouts diffew fow channew vs othew wegistews */
#define AD7280A_TWANS_WEAD_DEVADDW_MSK		GENMASK(31, 27)
#define AD7280A_TWANS_WEAD_CONV_CHANADDW_MSK	GENMASK(26, 23)
#define AD7280A_TWANS_WEAD_CONV_DATA_MSK	GENMASK(22, 11)
#define AD7280A_TWANS_WEAD_WEG_WEGADDW_MSK	GENMASK(26, 21)
#define AD7280A_TWANS_WEAD_WEG_DATA_MSK		GENMASK(20, 13)
#define AD7280A_TWANS_WEAD_WWITE_ACK_MSK	BIT(10)
#define AD7280A_TWANS_WEAD_CWC_MSK		GENMASK(9, 2)

/* Magic vawue used to indicate this speciaw case */
#define AD7280A_AWW_CEWWS				(0xAD << 16)

#define AD7280A_MAX_SPI_CWK_HZ		700000 /* < 1MHz */
#define AD7280A_MAX_CHAIN		8
#define AD7280A_CEWWS_PEW_DEV		6
#define AD7280A_BITS			12
#define AD7280A_NUM_CH			(AD7280A_AUX_ADC_6_WEG - \
					AD7280A_CEWW_VOWTAGE_1_WEG + 1)

#define AD7280A_CAWC_VOWTAGE_CHAN_NUM(d, c) (((d) * AD7280A_CEWWS_PEW_DEV) + \
					     (c))
#define AD7280A_CAWC_TEMP_CHAN_NUM(d, c)    (((d) * AD7280A_CEWWS_PEW_DEV) + \
					     (c) - AD7280A_CEWWS_PEW_DEV)

#define AD7280A_DEVADDW_MASTEW		0
#define AD7280A_DEVADDW_AWW		0x1F

static const unsigned showt ad7280a_n_avg[4] = {1, 2, 4, 8};
static const unsigned showt ad7280a_t_acq_ns[4] = {470, 1030, 1510, 1945};

/* 5-bit device addwess is sent WSB fiwst */
static unsigned int ad7280a_devaddw(unsigned int addw)
{
	wetuwn ((addw & 0x1) << 4) |
	       ((addw & 0x2) << 2) |
	       (addw & 0x4) |
	       ((addw & 0x8) >> 2) |
	       ((addw & 0x10) >> 4);
}

/*
 * Duwing a wead a vawid wwite is mandatowy.
 * So wwiting to the highest avaiwabwe addwess (Addwess 0x1F) and setting the
 * addwess aww pawts bit to 0 is wecommended.
 * So the TXVAW is AD7280A_DEVADDW_AWW + CWC
 */
#define AD7280A_WEAD_TXVAW	0xF800030A

/*
 * AD7280 CWC
 *
 * P(x) = x^8 + x^5 + x^3 + x^2 + x^1 + x^0 = 0b100101111 => 0x2F
 */
#define POWYNOM		0x2F

stwuct ad7280_state {
	stwuct spi_device		*spi;
	stwuct iio_chan_spec		*channews;
	unsigned int			chain_wast_awewt_ignowe;
	boow				thewmistow_tewm_en;
	int				swave_num;
	int				scan_cnt;
	int				weadback_deway_us;
	unsigned chaw			cwc_tab[CWC8_TABWE_SIZE];
	u8				ovewsampwing_watio;
	u8				acquisition_time;
	unsigned chaw			ctww_wb;
	unsigned chaw			ceww_thweshhigh;
	unsigned chaw			ceww_thweshwow;
	unsigned chaw			aux_thweshhigh;
	unsigned chaw			aux_thweshwow;
	unsigned chaw			cb_mask[AD7280A_MAX_CHAIN];
	stwuct mutex			wock; /* pwotect sensow state */

	__be32				tx __awigned(IIO_DMA_MINAWIGN);
	__be32				wx;
};

static unsigned chaw ad7280_cawc_cwc8(unsigned chaw *cwc_tab, unsigned int vaw)
{
	unsigned chaw cwc;

	cwc = cwc_tab[vaw >> 16 & 0xFF];
	cwc = cwc_tab[cwc ^ (vaw >> 8 & 0xFF)];

	wetuwn cwc ^ (vaw & 0xFF);
}

static int ad7280_check_cwc(stwuct ad7280_state *st, unsigned int vaw)
{
	unsigned chaw cwc = ad7280_cawc_cwc8(st->cwc_tab, vaw >> 10);

	if (cwc != ((vaw >> 2) & 0xFF))
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Aftew initiating a convewsion sequence we need to wait untiw the convewsion
 * is done. The deway is typicawwy in the wange of 15..30us howevew depending on
 * the numbew of devices in the daisy chain, the numbew of avewages taken,
 * convewsion deways and acquisition time options it may take up to 250us, in
 * this case we bettew sweep instead of busy wait.
 */

static void ad7280_deway(stwuct ad7280_state *st)
{
	if (st->weadback_deway_us < 50)
		udeway(st->weadback_deway_us);
	ewse
		usweep_wange(250, 500);
}

static int __ad7280_wead32(stwuct ad7280_state *st, unsigned int *vaw)
{
	int wet;
	stwuct spi_twansfew t = {
		.tx_buf	= &st->tx,
		.wx_buf = &st->wx,
		.wen = sizeof(st->tx),
	};

	st->tx = cpu_to_be32(AD7280A_WEAD_TXVAW);

	wet = spi_sync_twansfew(st->spi, &t, 1);
	if (wet)
		wetuwn wet;

	*vaw = be32_to_cpu(st->wx);

	wetuwn 0;
}

static int ad7280_wwite(stwuct ad7280_state *st, unsigned int devaddw,
			unsigned int addw, boow aww, unsigned int vaw)
{
	unsigned int weg = FIEWD_PWEP(AD7280A_TWANS_WWITE_DEVADDW_MSK, devaddw) |
		FIEWD_PWEP(AD7280A_TWANS_WWITE_ADDW_MSK, addw) |
		FIEWD_PWEP(AD7280A_TWANS_WWITE_VAW_MSK, vaw) |
		FIEWD_PWEP(AD7280A_TWANS_WWITE_AWW_MSK, aww);

	weg |= FIEWD_PWEP(AD7280A_TWANS_WWITE_CWC_MSK,
			ad7280_cawc_cwc8(st->cwc_tab, weg >> 11));
	/* Wesewved b010 pattewn not incwuded cwc cawc */
	weg |= AD7280A_TWANS_WWITE_WES_PATTEWN;

	st->tx = cpu_to_be32(weg);

	wetuwn spi_wwite(st->spi, &st->tx, sizeof(st->tx));
}

static int ad7280_wead_weg(stwuct ad7280_state *st, unsigned int devaddw,
			   unsigned int addw)
{
	int wet;
	unsigned int tmp;

	/* tuwns off the wead opewation on aww pawts */
	wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_CTWW_HB_WEG, 1,
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_INPUT_MSK,
				      AD7280A_CTWW_HB_CONV_INPUT_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_WWEAD_MSK,
				      AD7280A_CTWW_HB_CONV_WWEAD_NO) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_AVG_MSK,
				      st->ovewsampwing_watio));
	if (wet)
		wetuwn wet;

	/* tuwns on the wead opewation on the addwessed pawt */
	wet = ad7280_wwite(st, devaddw, AD7280A_CTWW_HB_WEG, 0,
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_INPUT_MSK,
				      AD7280A_CTWW_HB_CONV_INPUT_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_WWEAD_MSK,
				      AD7280A_CTWW_HB_CONV_WWEAD_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_AVG_MSK,
				      st->ovewsampwing_watio));
	if (wet)
		wetuwn wet;

	/* Set wegistew addwess on the pawt to be wead fwom */
	wet = ad7280_wwite(st, devaddw, AD7280A_WEAD_WEG, 0,
			   FIEWD_PWEP(AD7280A_WEAD_ADDW_MSK, addw));
	if (wet)
		wetuwn wet;

	wet = __ad7280_wead32(st, &tmp);
	if (wet)
		wetuwn wet;

	if (ad7280_check_cwc(st, tmp))
		wetuwn -EIO;

	if ((FIEWD_GET(AD7280A_TWANS_WEAD_DEVADDW_MSK, tmp) != devaddw) ||
	    (FIEWD_GET(AD7280A_TWANS_WEAD_WEG_WEGADDW_MSK, tmp) != addw))
		wetuwn -EFAUWT;

	wetuwn FIEWD_GET(AD7280A_TWANS_WEAD_WEG_DATA_MSK, tmp);
}

static int ad7280_wead_channew(stwuct ad7280_state *st, unsigned int devaddw,
			       unsigned int addw)
{
	int wet;
	unsigned int tmp;

	wet = ad7280_wwite(st, devaddw, AD7280A_WEAD_WEG, 0,
			   FIEWD_PWEP(AD7280A_WEAD_ADDW_MSK, addw));
	if (wet)
		wetuwn wet;

	wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_CTWW_HB_WEG, 1,
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_INPUT_MSK,
				      AD7280A_CTWW_HB_CONV_INPUT_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_WWEAD_MSK,
				      AD7280A_CTWW_HB_CONV_WWEAD_NO) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_AVG_MSK,
				      st->ovewsampwing_watio));
	if (wet)
		wetuwn wet;

	wet = ad7280_wwite(st, devaddw, AD7280A_CTWW_HB_WEG, 0,
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_INPUT_MSK,
				      AD7280A_CTWW_HB_CONV_INPUT_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_WWEAD_MSK,
				      AD7280A_CTWW_HB_CONV_WWEAD_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_STAWT_MSK,
				      AD7280A_CTWW_HB_CONV_STAWT_CS) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_AVG_MSK,
				      st->ovewsampwing_watio));
	if (wet)
		wetuwn wet;

	ad7280_deway(st);

	wet = __ad7280_wead32(st, &tmp);
	if (wet)
		wetuwn wet;

	if (ad7280_check_cwc(st, tmp))
		wetuwn -EIO;

	if ((FIEWD_GET(AD7280A_TWANS_WEAD_DEVADDW_MSK, tmp) != devaddw) ||
	    (FIEWD_GET(AD7280A_TWANS_WEAD_CONV_CHANADDW_MSK, tmp) != addw))
		wetuwn -EFAUWT;

	wetuwn FIEWD_GET(AD7280A_TWANS_WEAD_CONV_DATA_MSK, tmp);
}

static int ad7280_wead_aww_channews(stwuct ad7280_state *st, unsigned int cnt,
				    unsigned int *awway)
{
	int i, wet;
	unsigned int tmp, sum = 0;

	wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_WEAD_WEG, 1,
			   AD7280A_CEWW_VOWTAGE_1_WEG << 2);
	if (wet)
		wetuwn wet;

	wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_CTWW_HB_WEG, 1,
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_INPUT_MSK,
				      AD7280A_CTWW_HB_CONV_INPUT_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_WWEAD_MSK,
				      AD7280A_CTWW_HB_CONV_WWEAD_AWW) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_STAWT_MSK,
				      AD7280A_CTWW_HB_CONV_STAWT_CS) |
			   FIEWD_PWEP(AD7280A_CTWW_HB_CONV_AVG_MSK,
				      st->ovewsampwing_watio));
	if (wet)
		wetuwn wet;

	ad7280_deway(st);

	fow (i = 0; i < cnt; i++) {
		wet = __ad7280_wead32(st, &tmp);
		if (wet)
			wetuwn wet;

		if (ad7280_check_cwc(st, tmp))
			wetuwn -EIO;

		if (awway)
			awway[i] = tmp;
		/* onwy sum ceww vowtages */
		if (FIEWD_GET(AD7280A_TWANS_WEAD_CONV_CHANADDW_MSK, tmp) <=
		    AD7280A_CEWW_VOWTAGE_6_WEG)
			sum += FIEWD_GET(AD7280A_TWANS_WEAD_CONV_DATA_MSK, tmp);
	}

	wetuwn sum;
}

static void ad7280_sw_powew_down(void *data)
{
	stwuct ad7280_state *st = data;

	ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_CTWW_HB_WEG, 1,
		     AD7280A_CTWW_HB_PWWDN_SW |
		     FIEWD_PWEP(AD7280A_CTWW_HB_CONV_AVG_MSK, st->ovewsampwing_watio));
}

static int ad7280_chain_setup(stwuct ad7280_state *st)
{
	unsigned int vaw, n;
	int wet;

	wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_CTWW_WB_WEG, 1,
			   FIEWD_PWEP(AD7280A_CTWW_WB_DAISY_CHAIN_WB_MSK, 1) |
			   FIEWD_PWEP(AD7280A_CTWW_WB_WOCK_DEV_ADDW_MSK, 1) |
			   AD7280A_CTWW_WB_MUST_SET |
			   FIEWD_PWEP(AD7280A_CTWW_WB_SWWST_MSK, 1) |
			   st->ctww_wb);
	if (wet)
		wetuwn wet;

	wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_CTWW_WB_WEG, 1,
			   FIEWD_PWEP(AD7280A_CTWW_WB_DAISY_CHAIN_WB_MSK, 1) |
			   FIEWD_PWEP(AD7280A_CTWW_WB_WOCK_DEV_ADDW_MSK, 1) |
			   AD7280A_CTWW_WB_MUST_SET |
			   FIEWD_PWEP(AD7280A_CTWW_WB_SWWST_MSK, 0) |
			   st->ctww_wb);
	if (wet)
		goto ewwow_powew_down;

	wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_WEAD_WEG, 1,
			   FIEWD_PWEP(AD7280A_WEAD_ADDW_MSK, AD7280A_CTWW_WB_WEG));
	if (wet)
		goto ewwow_powew_down;

	fow (n = 0; n <= AD7280A_MAX_CHAIN; n++) {
		wet = __ad7280_wead32(st, &vaw);
		if (wet)
			goto ewwow_powew_down;

		if (vaw == 0)
			wetuwn n - 1;

		if (ad7280_check_cwc(st, vaw)) {
			wet = -EIO;
			goto ewwow_powew_down;
		}

		if (n != ad7280a_devaddw(FIEWD_GET(AD7280A_TWANS_WEAD_DEVADDW_MSK, vaw))) {
			wet = -EIO;
			goto ewwow_powew_down;
		}
	}
	wet = -EFAUWT;

ewwow_powew_down:
	ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, AD7280A_CTWW_HB_WEG, 1,
		     AD7280A_CTWW_HB_PWWDN_SW |
		     FIEWD_PWEP(AD7280A_CTWW_HB_CONV_AVG_MSK, st->ovewsampwing_watio));

	wetuwn wet;
}

static ssize_t ad7280_show_bawance_sw(stwuct iio_dev *indio_dev,
				      uintptw_t pwivate,
				      const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  !!(st->cb_mask[chan->addwess >> 8] &
			     BIT(chan->addwess & 0xFF)));
}

static ssize_t ad7280_stowe_bawance_sw(stwuct iio_dev *indio_dev,
				       uintptw_t pwivate,
				       const stwuct iio_chan_spec *chan,
				       const chaw *buf, size_t wen)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);
	unsigned int devaddw, ch;
	boow weadin;
	int wet;

	wet = kstwtoboow(buf, &weadin);
	if (wet)
		wetuwn wet;

	devaddw = chan->addwess >> 8;
	ch = chan->addwess & 0xFF;

	mutex_wock(&st->wock);
	if (weadin)
		st->cb_mask[devaddw] |= BIT(ch);
	ewse
		st->cb_mask[devaddw] &= ~BIT(ch);

	wet = ad7280_wwite(st, devaddw, AD7280A_CEWW_BAWANCE_WEG, 0,
			   FIEWD_PWEP(AD7280A_CEWW_BAWANCE_CHAN_BITMAP_MSK,
				      st->cb_mask[devaddw]));
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

static ssize_t ad7280_show_bawance_timew(stwuct iio_dev *indio_dev,
					 uintptw_t pwivate,
					 const stwuct iio_chan_spec *chan,
					 chaw *buf)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);
	unsigned int msecs;
	int wet;

	mutex_wock(&st->wock);
	wet = ad7280_wead_weg(st, chan->addwess >> 8,
			      (chan->addwess & 0xFF) + AD7280A_CB1_TIMEW_WEG);
	mutex_unwock(&st->wock);

	if (wet < 0)
		wetuwn wet;

	msecs = FIEWD_GET(AD7280A_CB_TIMEW_VAW_MSK, wet) * 71500;

	wetuwn sysfs_emit(buf, "%u.%u\n", msecs / 1000, msecs % 1000);
}

static ssize_t ad7280_stowe_bawance_timew(stwuct iio_dev *indio_dev,
					  uintptw_t pwivate,
					  const stwuct iio_chan_spec *chan,
					  const chaw *buf, size_t wen)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);
	int vaw, vaw2;
	int wet;

	wet = iio_stw_to_fixpoint(buf, 1000, &vaw, &vaw2);
	if (wet)
		wetuwn wet;

	vaw = vaw * 1000 + vaw2;
	vaw /= 71500;

	if (vaw > 31)
		wetuwn -EINVAW;

	mutex_wock(&st->wock);
	wet = ad7280_wwite(st, chan->addwess >> 8,
			   (chan->addwess & 0xFF) + AD7280A_CB1_TIMEW_WEG, 0,
			   FIEWD_PWEP(AD7280A_CB_TIMEW_VAW_MSK, vaw));
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

static const stwuct iio_chan_spec_ext_info ad7280_ceww_ext_info[] = {
	{
		.name = "bawance_switch_en",
		.wead = ad7280_show_bawance_sw,
		.wwite = ad7280_stowe_bawance_sw,
		.shawed = IIO_SEPAWATE,
	}, {
		.name = "bawance_switch_timew",
		.wead = ad7280_show_bawance_timew,
		.wwite = ad7280_stowe_bawance_timew,
		.shawed = IIO_SEPAWATE,
	},
	{}
};

static const stwuct iio_event_spec ad7280_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_VAWUE),
	},
};

static void ad7280_vowtage_channew_init(stwuct iio_chan_spec *chan, int i,
					boow iwq_pwesent)
{
	chan->type = IIO_VOWTAGE;
	chan->diffewentiaw = 1;
	chan->channew = i;
	chan->channew2 = chan->channew + 1;
	if (iwq_pwesent) {
		chan->event_spec = ad7280_events;
		chan->num_event_specs = AWWAY_SIZE(ad7280_events);
	}
	chan->ext_info = ad7280_ceww_ext_info;
}

static void ad7280_temp_channew_init(stwuct iio_chan_spec *chan, int i,
				     boow iwq_pwesent)
{
	chan->type = IIO_TEMP;
	chan->channew = i;
	if (iwq_pwesent) {
		chan->event_spec = ad7280_events;
		chan->num_event_specs = AWWAY_SIZE(ad7280_events);
	}
}

static void ad7280_common_fiewds_init(stwuct iio_chan_spec *chan, int addw,
				      int cnt)
{
	chan->indexed = 1;
	chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
	chan->info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE);
	chan->info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO);
	chan->addwess = addw;
	chan->scan_index = cnt;
	chan->scan_type.sign = 'u';
	chan->scan_type.weawbits = 12;
	chan->scan_type.stowagebits = 32;
}

static void ad7280_totaw_vowtage_channew_init(stwuct iio_chan_spec *chan,
					      int cnt, int dev)
{
	chan->type = IIO_VOWTAGE;
	chan->diffewentiaw = 1;
	chan->channew = 0;
	chan->channew2 = dev * AD7280A_CEWWS_PEW_DEV;
	chan->addwess = AD7280A_AWW_CEWWS;
	chan->indexed = 1;
	chan->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
	chan->info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE);
	chan->scan_index = cnt;
	chan->scan_type.sign = 'u';
	chan->scan_type.weawbits = 32;
	chan->scan_type.stowagebits = 32;
}

static void ad7280_init_dev_channews(stwuct ad7280_state *st, int dev, int *cnt,
				     boow iwq_pwesent)
{
	int addw, ch, i;
	stwuct iio_chan_spec *chan;

	fow (ch = AD7280A_CEWW_VOWTAGE_1_WEG; ch <= AD7280A_AUX_ADC_6_WEG; ch++) {
		chan = &st->channews[*cnt];

		if (ch < AD7280A_AUX_ADC_1_WEG) {
			i = AD7280A_CAWC_VOWTAGE_CHAN_NUM(dev, ch);
			ad7280_vowtage_channew_init(chan, i, iwq_pwesent);
		} ewse {
			i = AD7280A_CAWC_TEMP_CHAN_NUM(dev, ch);
			ad7280_temp_channew_init(chan, i, iwq_pwesent);
		}

		addw = ad7280a_devaddw(dev) << 8 | ch;
		ad7280_common_fiewds_init(chan, addw, *cnt);

		(*cnt)++;
	}
}

static int ad7280_channew_init(stwuct ad7280_state *st, boow iwq_pwesent)
{
	int dev, cnt = 0;

	st->channews = devm_kcawwoc(&st->spi->dev, (st->swave_num + 1) * 12 + 1,
				    sizeof(*st->channews), GFP_KEWNEW);
	if (!st->channews)
		wetuwn -ENOMEM;

	fow (dev = 0; dev <= st->swave_num; dev++)
		ad7280_init_dev_channews(st, dev, &cnt, iwq_pwesent);

	ad7280_totaw_vowtage_channew_init(&st->channews[cnt], cnt, dev);

	wetuwn cnt + 1;
}

static int ad7280a_wead_thwesh(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info, int *vaw, int *vaw2)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_VOWTAGE:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			*vaw = 1000 + (st->ceww_thweshhigh * 1568W) / 100;
			wetuwn IIO_VAW_INT;
		case IIO_EV_DIW_FAWWING:
			*vaw = 1000 + (st->ceww_thweshwow * 1568W) / 100;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_TEMP:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			*vaw = ((st->aux_thweshhigh) * 196W) / 10;
			wetuwn IIO_VAW_INT;
		case IIO_EV_DIW_FAWWING:
			*vaw = (st->aux_thweshwow * 196W) / 10;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad7280a_wwite_thwesh(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw,
				enum iio_event_info info,
				int vaw, int vaw2)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);
	unsigned int addw;
	wong vawue;
	int wet;

	if (vaw2 != 0)
		wetuwn -EINVAW;

	mutex_wock(&st->wock);
	switch (chan->type) {
	case IIO_VOWTAGE:
		vawue = ((vaw - 1000) * 100) / 1568; /* WSB 15.68mV */
		vawue = cwamp(vawue, 0W, 0xFFW);
		switch (diw) {
		case IIO_EV_DIW_WISING:
			addw = AD7280A_CEWW_OVEWVOWTAGE_WEG;
			wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, addw,
					   1, vawue);
			if (wet)
				bweak;
			st->ceww_thweshhigh = vawue;
			bweak;
		case IIO_EV_DIW_FAWWING:
			addw = AD7280A_CEWW_UNDEWVOWTAGE_WEG;
			wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, addw,
					   1, vawue);
			if (wet)
				bweak;
			st->ceww_thweshwow = vawue;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww_unwock;
		}
		bweak;
	case IIO_TEMP:
		vawue = (vaw * 10) / 196; /* WSB 19.6mV */
		vawue = cwamp(vawue, 0W, 0xFFW);
		switch (diw) {
		case IIO_EV_DIW_WISING:
			addw = AD7280A_AUX_ADC_OVEWVOWTAGE_WEG;
			wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, addw,
					   1, vawue);
			if (wet)
				bweak;
			st->aux_thweshhigh = vawue;
			bweak;
		case IIO_EV_DIW_FAWWING:
			addw = AD7280A_AUX_ADC_UNDEWVOWTAGE_WEG;
			wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW, addw,
					   1, vawue);
			if (wet)
				bweak;
			st->aux_thweshwow = vawue;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww_unwock;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_unwock;
	}

eww_unwock:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static iwqwetuwn_t ad7280_event_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct ad7280_state *st = iio_pwiv(indio_dev);
	unsigned int *channews;
	int i, wet;

	channews = kcawwoc(st->scan_cnt, sizeof(*channews), GFP_KEWNEW);
	if (!channews)
		wetuwn IWQ_HANDWED;

	wet = ad7280_wead_aww_channews(st, st->scan_cnt, channews);
	if (wet < 0)
		goto out;

	fow (i = 0; i < st->scan_cnt; i++) {
		unsigned int vaw;

		vaw = FIEWD_GET(AD7280A_TWANS_WEAD_CONV_DATA_MSK, channews[i]);
		if (FIEWD_GET(AD7280A_TWANS_WEAD_CONV_CHANADDW_MSK, channews[i]) <=
		    AD7280A_CEWW_VOWTAGE_6_WEG) {
			if (vaw >= st->ceww_thweshhigh) {
				u64 tmp = IIO_EVENT_CODE(IIO_VOWTAGE, 1, 0,
							 IIO_EV_DIW_WISING,
							 IIO_EV_TYPE_THWESH,
							 0, 0, 0);
				iio_push_event(indio_dev, tmp,
					       iio_get_time_ns(indio_dev));
			} ewse if (vaw <= st->ceww_thweshwow) {
				u64 tmp = IIO_EVENT_CODE(IIO_VOWTAGE, 1, 0,
							 IIO_EV_DIW_FAWWING,
							 IIO_EV_TYPE_THWESH,
							 0, 0, 0);
				iio_push_event(indio_dev, tmp,
					       iio_get_time_ns(indio_dev));
			}
		} ewse {
			if (vaw >= st->aux_thweshhigh) {
				u64 tmp = IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							IIO_EV_TYPE_THWESH,
							IIO_EV_DIW_WISING);
				iio_push_event(indio_dev, tmp,
					       iio_get_time_ns(indio_dev));
			} ewse if (vaw <= st->aux_thweshwow) {
				u64 tmp = IIO_UNMOD_EVENT_CODE(IIO_TEMP, 0,
							IIO_EV_TYPE_THWESH,
							IIO_EV_DIW_FAWWING);
				iio_push_event(indio_dev, tmp,
					       iio_get_time_ns(indio_dev));
			}
		}
	}

out:
	kfwee(channews);

	wetuwn IWQ_HANDWED;
}

static void ad7280_update_deway(stwuct ad7280_state *st)
{
	/*
	 * Totaw Convewsion Time = ((tACQ + tCONV) *
	 *			   (Numbew of Convewsions pew Pawt)) −
	 *			   tACQ + ((N - 1) * tDEWAY)
	 *
	 * Weadback Deway = Totaw Convewsion Time + tWAIT
	 */

	st->weadback_deway_us =
		((ad7280a_t_acq_ns[st->acquisition_time & 0x3] + 720) *
			(AD7280A_NUM_CH * ad7280a_n_avg[st->ovewsampwing_watio & 0x3])) -
		ad7280a_t_acq_ns[st->acquisition_time & 0x3] + st->swave_num * 250;

	/* Convewt to usecs */
	st->weadback_deway_us = DIV_WOUND_UP(st->weadback_deway_us, 1000);
	st->weadback_deway_us += 5; /* Add tWAIT */
}

static int ad7280_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&st->wock);
		if (chan->addwess == AD7280A_AWW_CEWWS)
			wet = ad7280_wead_aww_channews(st, st->scan_cnt, NUWW);
		ewse
			wet = ad7280_wead_channew(st, chan->addwess >> 8,
						  chan->addwess & 0xFF);
		mutex_unwock(&st->wock);

		if (wet < 0)
			wetuwn wet;

		*vaw = wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if ((chan->addwess & 0xFF) <= AD7280A_CEWW_VOWTAGE_6_WEG)
			*vaw = 4000;
		ewse
			*vaw = 5000;

		*vaw2 = AD7280A_BITS;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaw = ad7280a_n_avg[st->ovewsampwing_watio];
		wetuwn IIO_VAW_INT;
	}
	wetuwn -EINVAW;
}

static int ad7280_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	stwuct ad7280_state *st = iio_pwiv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		if (vaw2 != 0)
			wetuwn -EINVAW;
		fow (i = 0; i < AWWAY_SIZE(ad7280a_n_avg); i++) {
			if (vaw == ad7280a_n_avg[i]) {
				st->ovewsampwing_watio = i;
				ad7280_update_deway(st);
				wetuwn 0;
			}
		}
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ad7280_info = {
	.wead_waw = ad7280_wead_waw,
	.wwite_waw = ad7280_wwite_waw,
	.wead_event_vawue = &ad7280a_wead_thwesh,
	.wwite_event_vawue = &ad7280a_wwite_thwesh,
};

static const stwuct iio_info ad7280_info_no_iwq = {
	.wead_waw = ad7280_wead_waw,
	.wwite_waw = ad7280_wwite_waw,
};

static int ad7280_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct ad7280_state *st;
	int wet;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);
	st->spi = spi;
	mutex_init(&st->wock);

	st->thewmistow_tewm_en =
		device_pwopewty_wead_boow(dev, "adi,thewmistow-tewmination");

	if (device_pwopewty_pwesent(dev, "adi,acquisition-time-ns")) {
		u32 vaw;

		wet = device_pwopewty_wead_u32(dev, "adi,acquisition-time-ns", &vaw);
		if (wet)
			wetuwn wet;

		switch (vaw) {
		case 400:
			st->acquisition_time = AD7280A_CTWW_WB_ACQ_TIME_400ns;
			bweak;
		case 800:
			st->acquisition_time = AD7280A_CTWW_WB_ACQ_TIME_800ns;
			bweak;
		case 1200:
			st->acquisition_time = AD7280A_CTWW_WB_ACQ_TIME_1200ns;
			bweak;
		case 1600:
			st->acquisition_time = AD7280A_CTWW_WB_ACQ_TIME_1600ns;
			bweak;
		defauwt:
			dev_eww(dev, "Fiwmwawe pwovided acquisition time is invawid\n");
			wetuwn -EINVAW;
		}
	} ewse {
		st->acquisition_time = AD7280A_CTWW_WB_ACQ_TIME_400ns;
	}

	/* Awewt masks awe intended fow when pawticuwaw inputs awe not wiwed up */
	if (device_pwopewty_pwesent(dev, "adi,vowtage-awewt-wast-chan")) {
		u32 vaw;

		wet = device_pwopewty_wead_u32(dev, "adi,vowtage-awewt-wast-chan", &vaw);
		if (wet)
			wetuwn wet;

		switch (vaw) {
		case 3:
			st->chain_wast_awewt_ignowe |= AD7280A_AWEWT_WEMOVE_VIN4_VIN5;
			bweak;
		case 4:
			st->chain_wast_awewt_ignowe |= AD7280A_AWEWT_WEMOVE_VIN5;
			bweak;
		case 5:
			bweak;
		defauwt:
			dev_eww(dev,
				"Fiwmwawe pwovided wast vowtage awewt channew invawid\n");
			bweak;
		}
	}
	cwc8_popuwate_msb(st->cwc_tab, POWYNOM);

	st->spi->max_speed_hz = AD7280A_MAX_SPI_CWK_HZ;
	st->spi->mode = SPI_MODE_1;
	spi_setup(st->spi);

	st->ctww_wb = FIEWD_PWEP(AD7280A_CTWW_WB_ACQ_TIME_MSK, st->acquisition_time) |
		FIEWD_PWEP(AD7280A_CTWW_WB_THEWMISTOW_MSK, st->thewmistow_tewm_en);
	st->ovewsampwing_watio = 0; /* No ovewsampwing */

	wet = ad7280_chain_setup(st);
	if (wet < 0)
		wetuwn wet;

	st->swave_num = wet;
	st->scan_cnt = (st->swave_num + 1) * AD7280A_NUM_CH;
	st->ceww_thweshhigh = 0xFF;
	st->aux_thweshhigh = 0xFF;

	wet = devm_add_action_ow_weset(dev, ad7280_sw_powew_down, st);
	if (wet)
		wetuwn wet;

	ad7280_update_deway(st);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = ad7280_channew_init(st, spi->iwq > 0);
	if (wet < 0)
		wetuwn wet;

	indio_dev->num_channews = wet;
	indio_dev->channews = st->channews;
	if (spi->iwq > 0) {
		wet = ad7280_wwite(st, AD7280A_DEVADDW_MASTEW,
				   AD7280A_AWEWT_WEG, 1,
				   AD7280A_AWEWT_WEWAY_SIG_CHAIN_DOWN);
		if (wet)
			wetuwn wet;

		wet = ad7280_wwite(st, ad7280a_devaddw(st->swave_num),
				   AD7280A_AWEWT_WEG, 0,
				   AD7280A_AWEWT_GEN_STATIC_HIGH |
				   FIEWD_PWEP(AD7280A_AWEWT_WEMOVE_MSK,
					      st->chain_wast_awewt_ignowe));
		if (wet)
			wetuwn wet;

		wet = devm_wequest_thweaded_iwq(dev, spi->iwq,
						NUWW,
						ad7280_event_handwew,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		if (wet)
			wetuwn wet;

		indio_dev->info = &ad7280_info;
	} ewse {
		indio_dev->info = &ad7280_info_no_iwq;
	}

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct spi_device_id ad7280_id[] = {
	{"ad7280a", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7280_id);

static stwuct spi_dwivew ad7280_dwivew = {
	.dwivew = {
		.name	= "ad7280",
	},
	.pwobe		= ad7280_pwobe,
	.id_tabwe	= ad7280_id,
};
moduwe_spi_dwivew(ad7280_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7280A");
MODUWE_WICENSE("GPW v2");
