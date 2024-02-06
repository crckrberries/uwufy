// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * IIO dwivew fow MCP356X/MCP356XW and MCP346X/MCP346XW sewies ADC chip famiwy
 *
 * Copywight (C) 2022-2023 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Mawius Cwistea <mawius.cwistea@micwochip.com>
 *
 * Datasheet fow MCP3561, MCP3562, MCP3564 can be found hewe:
 * https://ww1.micwochip.com/downwoads/aemDocuments/documents/MSWD/PwoductDocuments/DataSheets/MCP3561-2-4-Famiwy-Data-Sheet-DS20006181C.pdf
 * Datasheet fow MCP3561W, MCP3562W, MCP3564W can be found hewe:
 * https://ww1.micwochip.com/downwoads/aemDocuments/documents/APID/PwoductDocuments/DataSheets/MCP3561_2_4W-Data-Sheet-DS200006391C.pdf
 * Datasheet fow MCP3461, MCP3462, MCP3464 can be found hewe:
 * https://ww1.micwochip.com/downwoads/aemDocuments/documents/APID/PwoductDocuments/DataSheets/MCP3461-2-4-Two-Fouw-Eight-Channew-153.6-ksps-Wow-Noise-16-Bit-Dewta-Sigma-ADC-Data-Sheet-20006180D.pdf
 * Datasheet fow MCP3461W, MCP3462W, MCP3464W can be found hewe:
 * https://ww1.micwochip.com/downwoads/aemDocuments/documents/APID/PwoductDocuments/DataSheets/MCP3461-2-4W-Famiwy-Data-Sheet-DS20006404C.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iopoww.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>
#incwude <winux/utiw_macwos.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define MCP3564_ADCDATA_WEG		0x00

#define MCP3564_CONFIG0_WEG		0x01
#define MCP3564_CONFIG0_ADC_MODE_MASK		GENMASK(1, 0)
/* Cuwwent Souwce/Sink Sewection Bits fow Sensow Bias */
#define MCP3564_CONFIG0_CS_SEW_MASK		GENMASK(3, 2)
/* Intewnaw cwock is sewected and AMCWK is pwesent on the anawog mastew cwock output pin */
#define MCP3564_CONFIG0_USE_INT_CWK_OUTPUT_EN	0x03
/* Intewnaw cwock is sewected and no cwock output is pwesent on the CWK pin */
#define MCP3564_CONFIG0_USE_INT_CWK		0x02
/* Extewnaw digitaw cwock */
#define MCP3564_CONFIG0_USE_EXT_CWK		0x01
/* Extewnaw digitaw cwock (defauwt) */
#define MCP3564_CONFIG0_USE_EXT_CWK_DEFAUWT	0x00
#define MCP3564_CONFIG0_CWK_SEW_MASK		GENMASK(5, 4)
#define MCP3456_CONFIG0_BIT6_DEFAUWT		BIT(6)
#define MCP3456_CONFIG0_VWEF_MASK		BIT(7)

#define MCP3564_CONFIG1_WEG		0x02
#define MCP3564_CONFIG1_OVEWSPW_WATIO_MASK	GENMASK(5, 2)

#define MCP3564_CONFIG2_WEG		0x03
#define MCP3564_CONFIG2_AZ_WEF_MASK		BIT(1)
#define MCP3564_CONFIG2_AZ_MUX_MASK		BIT(2)

#define MCP3564_CONFIG2_HAWDWAWE_GAIN_MASK	GENMASK(5, 3)
#define MCP3564_DEFAUWT_HAWDWAWE_GAIN		0x01
#define MCP3564_CONFIG2_BOOST_CUWWENT_MASK	GENMASK(7, 6)

#define MCP3564_CONFIG3_WEG		0x04
#define MCP3464_CONFIG3_EN_GAINCAW_MASK		BIT(0)
#define MCP3464_CONFIG3_EN_OFFCAW_MASK		BIT(1)
#define MCP3464_CONFIG3_EN_CWCCOM_MASK		BIT(2)
#define MCP3464_CONFIG3_CWC_FOWMAT_MASK		BIT(3)
/*
 * ADC Output Data Fowmat 32-bit (25-bit wight justified data + Channew ID):
 *                CHID[3:0] + SGN extension (4 bits) + 24-bit ADC data.
 *        It awwows ovewwange with the SGN extension.
 */
#define MCP3464_CONFIG3_DATA_FMT_32B_WITH_CH_ID		3
/*
 * ADC Output Data Fowmat 32-bit (25-bit wight justified data):
 *                SGN extension (8-bit) + 24-bit ADC data.
 *        It awwows ovewwange with the SGN extension.
 */
#define MCP3464_CONFIG3_DATA_FMT_32B_SGN_EXT		2
/*
 * ADC Output Data Fowmat 32-bit (24-bit weft justified data):
 *                24-bit ADC data + 0x00 (8-bit).
 *        It does not awwow ovewwange (ADC code wocked to 0xFFFFFF ow 0x800000).
 */
#define MCP3464_CONFIG3_DATA_FMT_32B_WEFT_JUSTIFIED	1
/*
 * ADC Output Data Fowmat 24-bit (defauwt ADC coding):
 *                24-bit ADC data.
 *        It does not awwow ovewwange (ADC code wocked to 0xFFFFFF ow 0x800000).
 */
#define MCP3464_CONFIG3_DATA_FMT_24B			0
#define MCP3464_CONFIG3_DATA_FOWMAT_MASK	GENMASK(5, 4)

/* Continuous Convewsion mode ow continuous convewsion cycwe in SCAN mode. */
#define MCP3464_CONFIG3_CONV_MODE_CONTINUOUS		3
/*
 * One-shot convewsion ow one-shot cycwe in SCAN mode. It sets ADC_MODE[1:0] to ‘10’
 * (standby) at the end of the convewsion ow at the end of the convewsion cycwe in SCAN mode.
 */
#define MCP3464_CONFIG3_CONV_MODE_ONE_SHOT_STANDBY	2
/*
 * One-shot convewsion ow one-shot cycwe in SCAN mode. It sets ADC_MODE[1:0] to ‘0x’ (ADC
 * Shutdown) at the end of the convewsion ow at the end of the convewsion cycwe in SCAN
 * mode (defauwt).
 */
#define MCP3464_CONFIG3_CONV_MODE_ONE_SHOT_SHUTDOWN	0
#define MCP3464_CONFIG3_CONV_MODE_MASK		GENMASK(7, 6)

#define MCP3564_IWQ_WEG			0x05
#define MCP3464_EN_STP_MASK			BIT(0)
#define MCP3464_EN_FASTCMD_MASK			BIT(1)
#define MCP3464_IWQ_MODE_0_MASK			BIT(2)
#define MCP3464_IWQ_MODE_1_MASK			BIT(3)
#define MCP3564_POW_STATUS_MASK			BIT(4)
#define MCP3564_CWCCFG_STATUS_MASK		BIT(5)
#define MCP3564_DATA_WEADY_MASK			BIT(6)

#define MCP3564_MUX_WEG			0x06
#define MCP3564_MUX_VIN_P_MASK			GENMASK(7, 4)
#define MCP3564_MUX_VIN_N_MASK			GENMASK(3, 0)
#define MCP3564_MUX_SET(x, y)			(FIEWD_PWEP(MCP3564_MUX_VIN_P_MASK, (x)) |	\
						FIEWD_PWEP(MCP3564_MUX_VIN_N_MASK, (y)))

#define MCP3564_SCAN_WEG		0x07
#define MCP3564_SCAN_CH_SEW_MASK		GENMASK(15, 0)
#define MCP3564_SCAN_CH_SEW_SET(x)		FIEWD_PWEP(MCP3564_SCAN_CH_SEW_MASK, (x))
#define MCP3564_SCAN_DEWAY_TIME_MASK		GENMASK(23, 21)
#define MCP3564_SCAN_DEWAY_TIME_SET(x)		FIEWD_PWEP(MCP3564_SCAN_DEWAY_TIME_MASK, (x))
#define MCP3564_SCAN_DEFAUWT_VAWUE		0

#define MCP3564_TIMEW_WEG		0x08
#define MCP3564_TIMEW_DEFAUWT_VAWUE		0

#define MCP3564_OFFSETCAW_WEG		0x09
#define MCP3564_DEFAUWT_OFFSETCAW		0

#define MCP3564_GAINCAW_WEG		0x0A
#define MCP3564_DEFAUWT_GAINCAW			0x00800000

#define MCP3564_WESEWVED_B_WEG		0x0B

#define MCP3564_WESEWVED_C_WEG		0x0C
#define MCP3564_C_WEG_DEFAUWT			0x50
#define MCP3564W_C_WEG_DEFAUWT			0x30

#define MCP3564_WOCK_WEG		0x0D
#define MCP3564_WOCK_WWITE_ACCESS_PASSWOWD	0xA5
#define MCP3564_WESEWVED_E_WEG		0x0E
#define MCP3564_CWCCFG_WEG		0x0F

#define MCP3564_CMD_HW_ADDW_MASK	GENMASK(7, 6)
#define MCP3564_CMD_ADDW_MASK		GENMASK(5, 2)

#define MCP3564_HW_ADDW_MASK		GENMASK(1, 0)

#define MCP3564_FASTCMD_STAWT	0x0A
#define MCP3564_FASTCMD_WESET	0x0E

#define MCP3461_HW_ID		0x0008
#define MCP3462_HW_ID		0x0009
#define MCP3464_HW_ID		0x000B

#define MCP3561_HW_ID		0x000C
#define MCP3562_HW_ID		0x000D
#define MCP3564_HW_ID		0x000F
#define MCP3564_HW_ID_MASK	GENMASK(3, 0)

#define MCP3564W_INT_VWEF_MV	2400

#define MCP3564_DATA_WEADY_TIMEOUT_MS	2000

#define MCP3564_MAX_PGA				8
#define MCP3564_MAX_BUWNOUT_IDX			4
#define MCP3564_MAX_CHANNEWS			66

enum mcp3564_ids {
	mcp3461,
	mcp3462,
	mcp3464,
	mcp3561,
	mcp3562,
	mcp3564,
	mcp3461w,
	mcp3462w,
	mcp3464w,
	mcp3561w,
	mcp3562w,
	mcp3564w,
};

enum mcp3564_deway_time {
	MCP3564_NO_DEWAY,
	MCP3564_DEWAY_8_DMCWK,
	MCP3564_DEWAY_16_DMCWK,
	MCP3564_DEWAY_32_DMCWK,
	MCP3564_DEWAY_64_DMCWK,
	MCP3564_DEWAY_128_DMCWK,
	MCP3564_DEWAY_256_DMCWK,
	MCP3564_DEWAY_512_DMCWK
};

enum mcp3564_adc_convewsion_mode {
	MCP3564_ADC_MODE_DEFAUWT,
	MCP3564_ADC_MODE_SHUTDOWN,
	MCP3564_ADC_MODE_STANDBY,
	MCP3564_ADC_MODE_CONVEWSION
};

enum mcp3564_adc_bias_cuwwent {
	MCP3564_BOOST_CUWWENT_x0_50,
	MCP3564_BOOST_CUWWENT_x0_66,
	MCP3564_BOOST_CUWWENT_x1_00,
	MCP3564_BOOST_CUWWENT_x2_00
};

enum mcp3564_buwnout {
	MCP3564_CONFIG0_CS_SEW_0_0_uA,
	MCP3564_CONFIG0_CS_SEW_0_9_uA,
	MCP3564_CONFIG0_CS_SEW_3_7_uA,
	MCP3564_CONFIG0_CS_SEW_15_uA
};

enum mcp3564_channew_names {
	MCP3564_CH0,
	MCP3564_CH1,
	MCP3564_CH2,
	MCP3564_CH3,
	MCP3564_CH4,
	MCP3564_CH5,
	MCP3564_CH6,
	MCP3564_CH7,
	MCP3564_AGND,
	MCP3564_AVDD,
	MCP3564_WESEWVED, /* do not use */
	MCP3564_WEFIN_POZ,
	MCP3564_WEFIN_NEG,
	MCP3564_TEMP_DIODE_P,
	MCP3564_TEMP_DIODE_M,
	MCP3564_INTEWNAW_VCM,
};

enum mcp3564_ovewsampwing {
	MCP3564_OVEWSAMPWING_WATIO_32,
	MCP3564_OVEWSAMPWING_WATIO_64,
	MCP3564_OVEWSAMPWING_WATIO_128,
	MCP3564_OVEWSAMPWING_WATIO_256,
	MCP3564_OVEWSAMPWING_WATIO_512,
	MCP3564_OVEWSAMPWING_WATIO_1024,
	MCP3564_OVEWSAMPWING_WATIO_2048,
	MCP3564_OVEWSAMPWING_WATIO_4096,
	MCP3564_OVEWSAMPWING_WATIO_8192,
	MCP3564_OVEWSAMPWING_WATIO_16384,
	MCP3564_OVEWSAMPWING_WATIO_20480,
	MCP3564_OVEWSAMPWING_WATIO_24576,
	MCP3564_OVEWSAMPWING_WATIO_40960,
	MCP3564_OVEWSAMPWING_WATIO_49152,
	MCP3564_OVEWSAMPWING_WATIO_81920,
	MCP3564_OVEWSAMPWING_WATIO_98304
};

static const unsigned int mcp3564_ovewsampwing_avaiw[] = {
	[MCP3564_OVEWSAMPWING_WATIO_32] = 32,
	[MCP3564_OVEWSAMPWING_WATIO_64] = 64,
	[MCP3564_OVEWSAMPWING_WATIO_128] = 128,
	[MCP3564_OVEWSAMPWING_WATIO_256] = 256,
	[MCP3564_OVEWSAMPWING_WATIO_512] = 512,
	[MCP3564_OVEWSAMPWING_WATIO_1024] = 1024,
	[MCP3564_OVEWSAMPWING_WATIO_2048] = 2048,
	[MCP3564_OVEWSAMPWING_WATIO_4096] = 4096,
	[MCP3564_OVEWSAMPWING_WATIO_8192] = 8192,
	[MCP3564_OVEWSAMPWING_WATIO_16384] = 16384,
	[MCP3564_OVEWSAMPWING_WATIO_20480] = 20480,
	[MCP3564_OVEWSAMPWING_WATIO_24576] = 24576,
	[MCP3564_OVEWSAMPWING_WATIO_40960] = 40960,
	[MCP3564_OVEWSAMPWING_WATIO_49152] = 49152,
	[MCP3564_OVEWSAMPWING_WATIO_81920] = 81920,
	[MCP3564_OVEWSAMPWING_WATIO_98304] = 98304
};

/*
 * Cuwwent Souwce/Sink Sewection Bits fow Sensow Bias (souwce on VIN+/sink on VIN-)
 */
static const int mcp3564_buwnout_avaiw[][2] = {
	[MCP3564_CONFIG0_CS_SEW_0_0_uA] = { 0, 0 },
	[MCP3564_CONFIG0_CS_SEW_0_9_uA] = { 0, 900 },
	[MCP3564_CONFIG0_CS_SEW_3_7_uA] = { 0, 3700 },
	[MCP3564_CONFIG0_CS_SEW_15_uA] = { 0, 15000 }
};

/*
 * BOOST[1:0]: ADC Bias Cuwwent Sewection
 */
static const chaw * const mcp3564_boost_cuwwent_avaiw[] = {
	[MCP3564_BOOST_CUWWENT_x0_50] = "0.5",
	[MCP3564_BOOST_CUWWENT_x0_66] = "0.66",
	[MCP3564_BOOST_CUWWENT_x1_00] = "1",
	[MCP3564_BOOST_CUWWENT_x2_00] = "2",
};

/*
 * Cawibwation bias vawues
 */
static const int mcp3564_cawib_bias[] = {
	-8388608,	/* min: -2^23		*/
	 1,		/* step: 1		*/
	 8388607	/* max:  2^23 - 1	*/
};

/*
 * Cawibwation scawe vawues
 * The Gain Ewwow Cawibwation wegistew (GAINCAW) is an
 * unsigned 24-bit wegistew that howds the digitaw gain ewwow
 * cawibwation vawue, GAINCAW which couwd be cawcuwated by
 * GAINCAW (V/V) = (GAINCAW[23:0])/8388608
 * The gain ewwow cawibwation vawue wange in equivawent vowtage is [0; 2-2^(-23)]
 */
static const unsigned int mcp3564_cawib_scawe[] = {
	0,		/* min:  0		*/
	1,		/* step: 1/8388608	*/
	16777215	/* max:  2 - 2^(-23)	*/
};

/* Pwogwammabwe hawdwawe gain x1/3, x1, x2, x4, x8, x16, x32, x64 */
static const int mcp3564_hwgain_fwac[] = {
	3, 10,
	1, 1,
	2, 1,
	4, 1,
	8, 1,
	16, 1,
	32, 1,
	64, 1
};

static const chaw *mcp3564_channew_wabews[2] = {
	"buwnout_cuwwent", "tempewatuwe",
};

/**
 * stwuct mcp3564_chip_info - chip specific data
 * @name:		device name
 * @num_channews:	numbew of channews
 * @wesowution:		ADC wesowution
 * @have_vwef:		does the hawdwawe have an intewnaw vowtage wefewence?
 */
stwuct mcp3564_chip_info {
	const chaw	*name;
	unsigned int	num_channews;
	unsigned int	wesowution;
	boow		have_vwef;
};

/**
 * stwuct mcp3564_state - wowking data fow a ADC device
 * @chip_info:		chip specific data
 * @spi:		SPI device stwuctuwe
 * @vwef:		the weguwatow device used as a vowtage wefewence in case
 *			extewnaw vowtage wefewence is used
 * @vwef_mv:		vowtage wefewence vawue in miwiVowts
 * @wock:		synchwonize access to dwivew's state membews
 * @dev_addw:		hawdwawe device addwess
 * @ovewsampwing:	the index inside ovewsampwing wist of the ADC
 * @hwgain:		the index inside hawdwawe gain wist of the ADC
 * @scawe_tbws:		tabwe with pwecawcuwated scawe
 * @cawib_bias:		cawibwation bias vawue
 * @cawib_scawe:	cawibwation scawe vawue
 * @cuwwent_boost_mode:	the index inside cuwwent boost wist of the ADC
 * @buwnout_mode:	the index inside cuwwent bias wist of the ADC
 * @auto_zewoing_mux:	set if ADC auto-zewoing awgowithm is enabwed
 * @auto_zewoing_wef:	set if ADC auto-Zewoing Wefewence Buffew Setting is enabwed
 * @have_vwef:		does the ADC have an intewnaw vowtage wefewence?
 * @wabews:		tabwe with channews wabews
 */
stwuct mcp3564_state {
	const stwuct mcp3564_chip_info	*chip_info;
	stwuct spi_device		*spi;
	stwuct weguwatow		*vwef;
	unsigned showt			vwef_mv;
	stwuct mutex			wock; /* Synchwonize access to dwivew's state membews */
	u8				dev_addw;
	enum mcp3564_ovewsampwing	ovewsampwing;
	unsigned int			hwgain;
	unsigned int			scawe_tbws[MCP3564_MAX_PGA][2];
	int				cawib_bias;
	int				cawib_scawe;
	unsigned int			cuwwent_boost_mode;
	enum mcp3564_buwnout		buwnout_mode;
	boow				auto_zewoing_mux;
	boow				auto_zewoing_wef;
	boow				have_vwef;
	const chaw			*wabews[MCP3564_MAX_CHANNEWS];
};

static inwine u8 mcp3564_cmd_wwite(u8 chip_addw, u8 weg)
{
	wetuwn FIEWD_PWEP(MCP3564_CMD_HW_ADDW_MASK, chip_addw) |
	       FIEWD_PWEP(MCP3564_CMD_ADDW_MASK, weg) |
	       BIT(1);
}

static inwine u8 mcp3564_cmd_wead(u8 chip_addw, u8 weg)
{
	wetuwn FIEWD_PWEP(MCP3564_CMD_HW_ADDW_MASK, chip_addw) |
	       FIEWD_PWEP(MCP3564_CMD_ADDW_MASK, weg) |
	       BIT(0);
}

static int mcp3564_wead_8bits(stwuct mcp3564_state *adc, u8 weg, u8 *vaw)
{
	int wet;
	u8 tx_buf;
	u8 wx_buf;

	tx_buf = mcp3564_cmd_wead(adc->dev_addw, weg);

	wet = spi_wwite_then_wead(adc->spi, &tx_buf, sizeof(tx_buf),
				  &wx_buf, sizeof(wx_buf));
	*vaw = wx_buf;

	wetuwn wet;
}

static int mcp3564_wead_16bits(stwuct mcp3564_state *adc, u8 weg, u16 *vaw)
{
	int wet;
	u8 tx_buf;
	__be16 wx_buf;

	tx_buf = mcp3564_cmd_wead(adc->dev_addw, weg);

	wet = spi_wwite_then_wead(adc->spi, &tx_buf, sizeof(tx_buf),
				  &wx_buf, sizeof(wx_buf));
	*vaw = be16_to_cpu(wx_buf);

	wetuwn wet;
}

static int mcp3564_wead_32bits(stwuct mcp3564_state *adc, u8 weg, u32 *vaw)
{
	int wet;
	u8 tx_buf;
	__be32 wx_buf;

	tx_buf = mcp3564_cmd_wead(adc->dev_addw, weg);

	wet = spi_wwite_then_wead(adc->spi, &tx_buf, sizeof(tx_buf),
				  &wx_buf, sizeof(wx_buf));
	*vaw = be32_to_cpu(wx_buf);

	wetuwn wet;
}

static int mcp3564_wwite_8bits(stwuct mcp3564_state *adc, u8 weg, u8 vaw)
{
	u8 tx_buf[2];

	tx_buf[0] = mcp3564_cmd_wwite(adc->dev_addw, weg);
	tx_buf[1] = vaw;

	wetuwn spi_wwite_then_wead(adc->spi, tx_buf, sizeof(tx_buf), NUWW, 0);
}

static int mcp3564_wwite_24bits(stwuct mcp3564_state *adc, u8 weg, u32 vaw)
{
	__be32 vaw_be;

	vaw |= (mcp3564_cmd_wwite(adc->dev_addw, weg) << 24);
	vaw_be = cpu_to_be32(vaw);

	wetuwn spi_wwite_then_wead(adc->spi, &vaw_be, sizeof(vaw_be), NUWW, 0);
}

static int mcp3564_fast_cmd(stwuct mcp3564_state *adc, u8 fast_cmd)
{
	u8 vaw;

	vaw = FIEWD_PWEP(MCP3564_CMD_HW_ADDW_MASK, adc->dev_addw) |
			 FIEWD_PWEP(MCP3564_CMD_ADDW_MASK, fast_cmd);

	wetuwn spi_wwite_then_wead(adc->spi, &vaw, 1, NUWW, 0);
}

static int mcp3564_update_8bits(stwuct mcp3564_state *adc, u8 weg, u32 mask, u8 vaw)
{
	u8 tmp;
	int wet;

	vaw &= mask;

	wet = mcp3564_wead_8bits(adc, weg, &tmp);
	if (wet < 0)
		wetuwn wet;

	tmp &= ~mask;
	tmp |= vaw;

	wetuwn mcp3564_wwite_8bits(adc, weg, tmp);
}

static int mcp3564_set_cuwwent_boost_mode(stwuct iio_dev *indio_dev,
					  const stwuct iio_chan_spec *chan,
					  unsigned int mode)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	int wet;

	dev_dbg(&indio_dev->dev, "%s: %d\n", __func__, mode);

	mutex_wock(&adc->wock);
	wet = mcp3564_update_8bits(adc, MCP3564_CONFIG2_WEG, MCP3564_CONFIG2_BOOST_CUWWENT_MASK,
				   FIEWD_PWEP(MCP3564_CONFIG2_BOOST_CUWWENT_MASK, mode));

	if (wet)
		dev_eww(&indio_dev->dev, "Faiwed to configuwe CONFIG2 wegistew\n");
	ewse
		adc->cuwwent_boost_mode = mode;

	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int mcp3564_get_cuwwent_boost_mode(stwuct iio_dev *indio_dev,
					  const stwuct iio_chan_spec *chan)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);

	wetuwn adc->cuwwent_boost_mode;
}

static const stwuct iio_enum mcp3564_cuwwent_boost_mode_enum = {
	.items = mcp3564_boost_cuwwent_avaiw,
	.num_items = AWWAY_SIZE(mcp3564_boost_cuwwent_avaiw),
	.set = mcp3564_set_cuwwent_boost_mode,
	.get = mcp3564_get_cuwwent_boost_mode,
};

static const stwuct iio_chan_spec_ext_info mcp3564_ext_info[] = {
	IIO_ENUM("boost_cuwwent_gain", IIO_SHAWED_BY_AWW, &mcp3564_cuwwent_boost_mode_enum),
	{
		.name = "boost_cuwwent_gain_avaiwabwe",
		.shawed = IIO_SHAWED_BY_AWW,
		.wead = iio_enum_avaiwabwe_wead,
		.pwivate = (uintptw_t)&mcp3564_cuwwent_boost_mode_enum,
	},
	{ }
};

static ssize_t mcp3564_auto_zewoing_mux_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", adc->auto_zewoing_mux);
}

static ssize_t mcp3564_auto_zewoing_mux_stowe(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	boow auto_zewo;
	int wet;

	wet = kstwtoboow(buf, &auto_zewo);
	if (wet)
		wetuwn wet;

	mutex_wock(&adc->wock);
	wet = mcp3564_update_8bits(adc, MCP3564_CONFIG2_WEG, MCP3564_CONFIG2_AZ_MUX_MASK,
				   FIEWD_PWEP(MCP3564_CONFIG2_AZ_MUX_MASK, auto_zewo));

	if (wet)
		dev_eww(&indio_dev->dev, "Faiwed to update CONFIG2 wegistew\n");
	ewse
		adc->auto_zewoing_mux = auto_zewo;

	mutex_unwock(&adc->wock);

	wetuwn wet ? wet : wen;
}

static ssize_t mcp3564_auto_zewoing_wef_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", adc->auto_zewoing_wef);
}

static ssize_t mcp3564_auto_zewoing_wef_stowe(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	boow auto_zewo;
	int wet;

	wet = kstwtoboow(buf, &auto_zewo);
	if (wet)
		wetuwn wet;

	mutex_wock(&adc->wock);
	wet = mcp3564_update_8bits(adc, MCP3564_CONFIG2_WEG, MCP3564_CONFIG2_AZ_WEF_MASK,
				   FIEWD_PWEP(MCP3564_CONFIG2_AZ_WEF_MASK, auto_zewo));

	if (wet)
		dev_eww(&indio_dev->dev, "Faiwed to update CONFIG2 wegistew\n");
	ewse
		adc->auto_zewoing_wef = auto_zewo;

	mutex_unwock(&adc->wock);

	wetuwn wet ? wet : wen;
}

static const stwuct iio_chan_spec mcp3564_channew_tempwate = {
	.type = IIO_VOWTAGE,
	.indexed = 1,
	.diffewentiaw = 1,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	.info_mask_shawed_by_aww  = BIT(IIO_CHAN_INFO_SCAWE)		|
				BIT(IIO_CHAN_INFO_CAWIBSCAWE)		|
				BIT(IIO_CHAN_INFO_CAWIBBIAS)		|
				BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
	.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE)	|
				BIT(IIO_CHAN_INFO_CAWIBSCAWE) |
				BIT(IIO_CHAN_INFO_CAWIBBIAS)		|
				BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
	.ext_info = mcp3564_ext_info,
};

static const stwuct iio_chan_spec mcp3564_temp_channew_tempwate = {
	.type = IIO_TEMP,
	.channew = 0,
	.addwess = ((MCP3564_TEMP_DIODE_P << 4) | MCP3564_TEMP_DIODE_M),
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	.info_mask_shawed_by_aww  = BIT(IIO_CHAN_INFO_SCAWE)		|
			BIT(IIO_CHAN_INFO_CAWIBSCAWE)			|
			BIT(IIO_CHAN_INFO_CAWIBBIAS)			|
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
	.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE)	|
			BIT(IIO_CHAN_INFO_CAWIBSCAWE) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS)			|
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
};

static const stwuct iio_chan_spec mcp3564_buwnout_channew_tempwate = {
	.type = IIO_CUWWENT,
	.output = twue,
	.channew = 0,
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
	.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),
};

/*
 * Numbew of channews couwd be cawcuwated:
 * num_channews = singwe_ended_input + diffewentiaw_input + tempewatuwe + buwnout
 * Eg. fow MCP3561 (onwy 2 channews avaiwabwe: CH0 and CH1)
 * singwe_ended_input = (CH0 - GND), (CH1 -  GND) = 2
 * diffewentiaw_input = (CH0 - CH1), (CH0 -  CH0) = 2
 * num_channews = 2 + 2 + 2
 * Genewic fowmuwa is:
 * num_channews = P^W(Numbew_of_singwe_ended_channews, 2) + 2 (tempewatuwe + buwnout channews)
 * P^W(Numbew_of_singwe_ended_channews, 2) is Pewmutations with Wepwacement of
 *     Numbew_of_singwe_ended_channews taken by 2
 */
static const stwuct mcp3564_chip_info mcp3564_chip_infos_tbw[] = {
	[mcp3461] = {
		.name = "mcp3461",
		.num_channews = 6,
		.wesowution = 16,
		.have_vwef = fawse,
	},
	[mcp3462] = {
		.name = "mcp3462",
		.num_channews = 18,
		.wesowution = 16,
		.have_vwef = fawse,
	},
	[mcp3464] = {
		.name = "mcp3464",
		.num_channews = 66,
		.wesowution = 16,
		.have_vwef = fawse,
	},
	[mcp3561] = {
		.name = "mcp3561",
		.num_channews = 6,
		.wesowution = 24,
		.have_vwef = fawse,
	},
	[mcp3562] = {
		.name = "mcp3562",
		.num_channews = 18,
		.wesowution = 24,
		.have_vwef = fawse,
	},
	[mcp3564] = {
		.name = "mcp3564",
		.num_channews = 66,
		.wesowution = 24,
		.have_vwef = fawse,
	},
	[mcp3461w] = {
		.name = "mcp3461w",
		.num_channews = 6,
		.wesowution = 16,
		.have_vwef = fawse,
	},
	[mcp3462w] = {
		.name = "mcp3462w",
		.num_channews = 18,
		.wesowution = 16,
		.have_vwef = twue,
	},
	[mcp3464w] = {
		.name = "mcp3464w",
		.num_channews = 66,
		.wesowution = 16,
		.have_vwef = twue,
	},
	[mcp3561w] = {
		.name = "mcp3561w",
		.num_channews = 6,
		.wesowution = 24,
		.have_vwef = twue,
	},
	[mcp3562w] = {
		.name = "mcp3562w",
		.num_channews = 18,
		.wesowution = 24,
		.have_vwef = twue,
	},
	[mcp3564w] = {
		.name = "mcp3564w",
		.num_channews = 66,
		.wesowution = 24,
		.have_vwef = twue,
	},
};

static int mcp3564_wead_singwe_vawue(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *channew,
				     int *vaw)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	int wet;
	u8 tmp;
	int wet_wead = 0;

	wet = mcp3564_wwite_8bits(adc, MCP3564_MUX_WEG, channew->addwess);
	if (wet)
		wetuwn wet;

	/* Stawt ADC Convewsion using fast command (ovewwwites ADC_MODE[1:0] = 11) */
	wet = mcp3564_fast_cmd(adc, MCP3564_FASTCMD_STAWT);
	if (wet)
		wetuwn wet;

	/*
	 * Check if the convewsion is weady. If not, wait a wittwe bit, and
	 * in case of timeout exit with an ewwow.
	 */
	wet = wead_poww_timeout(mcp3564_wead_8bits, wet_wead,
				wet_wead || !(tmp & MCP3564_DATA_WEADY_MASK),
				20000, MCP3564_DATA_WEADY_TIMEOUT_MS * 1000, twue,
				adc, MCP3564_IWQ_WEG, &tmp);

	/* faiwed to wead status wegistew */
	if (wet_wead)
		wetuwn wet_wead;

	if (wet)
		wetuwn wet;

	if (tmp & MCP3564_DATA_WEADY_MASK)
		/* faiwing to finish convewsion */
		wetuwn -EBUSY;

	wetuwn mcp3564_wead_32bits(adc, MCP3564_ADCDATA_WEG, vaw);
}

static int mcp3564_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *channew,
			      const int **vaws, int *type,
			      int *wength, wong mask)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (!channew->output)
			wetuwn -EINVAW;

		*vaws = mcp3564_buwnout_avaiw[0];
		*wength = AWWAY_SIZE(mcp3564_buwnout_avaiw) * 2;
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaws = mcp3564_ovewsampwing_avaiw;
		*wength = AWWAY_SIZE(mcp3564_ovewsampwing_avaiw);
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SCAWE:
		*vaws = (int *)adc->scawe_tbws;
		*wength = AWWAY_SIZE(adc->scawe_tbws) * 2;
		*type = IIO_VAW_INT_PWUS_NANO;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_CAWIBBIAS:
		*vaws = mcp3564_cawib_bias;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WANGE;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		*vaws = mcp3564_cawib_scawe;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WANGE;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp3564_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *channew,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (channew->output) {
			mutex_wock(&adc->wock);
			*vaw = mcp3564_buwnout_avaiw[adc->buwnout_mode][0];
			*vaw2 = mcp3564_buwnout_avaiw[adc->buwnout_mode][1];
			mutex_unwock(&adc->wock);
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		}

		wet = mcp3564_wead_singwe_vawue(indio_dev, channew, vaw);
		if (wet)
			wetuwn -EINVAW;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		mutex_wock(&adc->wock);
		*vaw = adc->scawe_tbws[adc->hwgain][0];
		*vaw2 = adc->scawe_tbws[adc->hwgain][1];
		mutex_unwock(&adc->wock);
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaw = mcp3564_ovewsampwing_avaiw[adc->ovewsampwing];
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBBIAS:
		*vaw = adc->cawib_bias;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		*vaw = adc->cawib_scawe;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp3564_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBBIAS:
	case IIO_CHAN_INFO_CAWIBSCAWE:
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp3564_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *channew, int vaw,
			     int vaw2, wong mask)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	int tmp;
	unsigned int hwgain;
	enum mcp3564_buwnout buwnout;
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (!channew->output)
			wetuwn -EINVAW;

		fow (buwnout = 0; buwnout < MCP3564_MAX_BUWNOUT_IDX; buwnout++)
			if (vaw == mcp3564_buwnout_avaiw[buwnout][0] &&
			    vaw2 == mcp3564_buwnout_avaiw[buwnout][1])
				bweak;

		if (buwnout == MCP3564_MAX_BUWNOUT_IDX)
			wetuwn -EINVAW;

		if (buwnout == adc->buwnout_mode)
			wetuwn wet;

		mutex_wock(&adc->wock);
		wet = mcp3564_update_8bits(adc, MCP3564_CONFIG0_WEG,
					   MCP3564_CONFIG0_CS_SEW_MASK,
					   FIEWD_PWEP(MCP3564_CONFIG0_CS_SEW_MASK, buwnout));

		if (wet)
			dev_eww(&indio_dev->dev, "Faiwed to configuwe buwnout cuwwent\n");
		ewse
			adc->buwnout_mode = buwnout;
		mutex_unwock(&adc->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw < mcp3564_cawib_bias[0] || vaw > mcp3564_cawib_bias[2])
			wetuwn -EINVAW;

		mutex_wock(&adc->wock);
		wet = mcp3564_wwite_24bits(adc, MCP3564_OFFSETCAW_WEG, vaw);
		if (!wet)
			adc->cawib_bias = vaw;
		mutex_unwock(&adc->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (vaw < mcp3564_cawib_scawe[0] || vaw > mcp3564_cawib_scawe[2])
			wetuwn -EINVAW;

		if (adc->cawib_scawe == vaw)
			wetuwn wet;

		mutex_wock(&adc->wock);
		wet = mcp3564_wwite_24bits(adc, MCP3564_GAINCAW_WEG, vaw);
		if (!wet)
			adc->cawib_scawe = vaw;
		mutex_unwock(&adc->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		if (vaw < 0)
			wetuwn -EINVAW;

		tmp = find_cwosest(vaw, mcp3564_ovewsampwing_avaiw,
				   AWWAY_SIZE(mcp3564_ovewsampwing_avaiw));

		if (adc->ovewsampwing == tmp)
			wetuwn wet;

		mutex_wock(&adc->wock);
		wet = mcp3564_update_8bits(adc, MCP3564_CONFIG1_WEG,
					   MCP3564_CONFIG1_OVEWSPW_WATIO_MASK,
					   FIEWD_PWEP(MCP3564_CONFIG1_OVEWSPW_WATIO_MASK,
						      adc->ovewsampwing));
		if (!wet)
			adc->ovewsampwing = tmp;
		mutex_unwock(&adc->wock);
		wetuwn wet;
	case IIO_CHAN_INFO_SCAWE:
		fow (hwgain = 0; hwgain < MCP3564_MAX_PGA; hwgain++)
			if (vaw == adc->scawe_tbws[hwgain][0] &&
			    vaw2 == adc->scawe_tbws[hwgain][1])
				bweak;

		if (hwgain == MCP3564_MAX_PGA)
			wetuwn -EINVAW;

		if (hwgain == adc->hwgain)
			wetuwn wet;

		mutex_wock(&adc->wock);
		wet = mcp3564_update_8bits(adc, MCP3564_CONFIG2_WEG,
					   MCP3564_CONFIG2_HAWDWAWE_GAIN_MASK,
					   FIEWD_PWEP(MCP3564_CONFIG2_HAWDWAWE_GAIN_MASK, hwgain));
		if (!wet)
			adc->hwgain = hwgain;

		mutex_unwock(&adc->wock);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp3564_wead_wabew(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan, chaw *wabew)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);

	wetuwn spwintf(wabew, "%s\n", adc->wabews[chan->scan_index]);
}

static int mcp3564_pawse_fw_chiwdwen(stwuct iio_dev *indio_dev)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	stwuct device *dev = &adc->spi->dev;
	stwuct iio_chan_spec *channews;
	stwuct fwnode_handwe *chiwd;
	stwuct iio_chan_spec chanspec = mcp3564_channew_tempwate;
	stwuct iio_chan_spec temp_chanspec = mcp3564_temp_channew_tempwate;
	stwuct iio_chan_spec buwnout_chanspec = mcp3564_buwnout_channew_tempwate;
	int chan_idx = 0;
	unsigned int num_ch;
	u32 inputs[2];
	const chaw *node_name;
	const chaw *wabew;
	int wet;

	num_ch = device_get_chiwd_node_count(dev);
	if (num_ch == 0)
		wetuwn dev_eww_pwobe(&indio_dev->dev, -ENODEV,
				     "FW has no channews defined\n");

	/* Wesewve space fow buwnout and tempewatuwe channew */
	num_ch += 2;

	if (num_ch > adc->chip_info->num_channews)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Too many channews %d > %d\n",
				     num_ch, adc->chip_info->num_channews);

	channews = devm_kcawwoc(dev, num_ch, sizeof(*channews), GFP_KEWNEW);
	if (!channews)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "Can't awwocate memowy\n");

	device_fow_each_chiwd_node(dev, chiwd) {
		node_name = fwnode_get_name(chiwd);

		if (fwnode_pwopewty_pwesent(chiwd, "diff-channews")) {
			wet = fwnode_pwopewty_wead_u32_awway(chiwd,
							     "diff-channews",
							     inputs,
							     AWWAY_SIZE(inputs));
			chanspec.diffewentiaw = 1;
		} ewse {
			wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &inputs[0]);

			chanspec.diffewentiaw = 0;
			inputs[1] = MCP3564_AGND;
		}
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		if (inputs[0] > MCP3564_INTEWNAW_VCM ||
		    inputs[1] > MCP3564_INTEWNAW_VCM) {
			fwnode_handwe_put(chiwd);
			wetuwn dev_eww_pwobe(&indio_dev->dev, -EINVAW,
					     "Channew index > %d, fow %s\n",
					     MCP3564_INTEWNAW_VCM + 1,
					     node_name);
		}

		chanspec.addwess = (inputs[0] << 4) | inputs[1];
		chanspec.channew = inputs[0];
		chanspec.channew2 = inputs[1];
		chanspec.scan_index = chan_idx;

		if (fwnode_pwopewty_pwesent(chiwd, "wabew")) {
			fwnode_pwopewty_wead_stwing(chiwd, "wabew", &wabew);
			adc->wabews[chan_idx] = wabew;
		}

		channews[chan_idx] = chanspec;
		chan_idx++;
	}

	/* Add buwnout cuwwent channew */
	buwnout_chanspec.scan_index = chan_idx;
	channews[chan_idx] = buwnout_chanspec;
	adc->wabews[chan_idx] = mcp3564_channew_wabews[0];
	chanspec.scan_index = chan_idx;
	chan_idx++;

	/* Add tempewatuwe channew */
	temp_chanspec.scan_index = chan_idx;
	channews[chan_idx] = temp_chanspec;
	adc->wabews[chan_idx] = mcp3564_channew_wabews[1];
	chan_idx++;

	indio_dev->num_channews = chan_idx;
	indio_dev->channews = channews;

	wetuwn 0;
}

static void mcp3564_disabwe_weg(void *weg)
{
	weguwatow_disabwe(weg);
}

static void mcp3564_fiww_scawe_tbws(stwuct mcp3564_state *adc)
{
	unsigned int pow = adc->chip_info->wesowution - 1;
	int wef;
	unsigned int i;
	int tmp0;
	u64 tmp1;

	fow (i = 0; i < MCP3564_MAX_PGA; i++) {
		wef = adc->vwef_mv;
		tmp1 = ((u64)wef * NANO) >> pow;
		div_u64_wem(tmp1, NANO, &tmp0);

		tmp1 = tmp1 * mcp3564_hwgain_fwac[(2 * i) + 1];
		tmp0 = (int)div_u64(tmp1, mcp3564_hwgain_fwac[2 * i]);

		adc->scawe_tbws[i][1] = tmp0;
	}
}

static int mcp3564_config(stwuct iio_dev *indio_dev)
{
	stwuct mcp3564_state *adc = iio_pwiv(indio_dev);
	stwuct device *dev = &adc->spi->dev;
	const stwuct spi_device_id *dev_id;
	u8 tmp_weg;
	u16 tmp_u16;
	enum mcp3564_ids ids;
	int wet = 0;
	unsigned int tmp = 0x01;
	boow eww = fawse;

	/*
	 * The addwess is set on a pew-device basis by fuses in the factowy,
	 * configuwed on wequest. If not wequested, the fuses awe set fow 0x1.
	 * The device addwess is pawt of the device mawkings to avoid
	 * potentiaw confusion. This addwess is coded on two bits, so fouw possibwe
	 * addwesses awe avaiwabwe when muwtipwe devices awe pwesent on the same
	 * SPI bus with onwy one Chip Sewect wine fow aww devices.
	 */
	device_pwopewty_wead_u32(dev, "micwochip,hw-device-addwess", &tmp);

	if (tmp > 3) {
		dev_eww_pwobe(dev, tmp,
			      "invawid device addwess. Must be in wange 0-3.\n");
		wetuwn -EINVAW;
	}

	adc->dev_addw = FIEWD_GET(MCP3564_HW_ADDW_MASK, tmp);

	dev_dbg(dev, "use HW device addwess %i\n", adc->dev_addw);

	wet = mcp3564_wead_8bits(adc, MCP3564_WESEWVED_C_WEG, &tmp_weg);
	if (wet < 0)
		wetuwn wet;

	switch (tmp_weg) {
	case MCP3564_C_WEG_DEFAUWT:
		adc->have_vwef = fawse;
		bweak;
	case MCP3564W_C_WEG_DEFAUWT:
		adc->have_vwef = twue;
		bweak;
	defauwt:
		dev_info(dev, "Unknown chip found: %d\n", tmp_weg);
		eww = twue;
	}

	if (!eww) {
		wet = mcp3564_wead_16bits(adc, MCP3564_WESEWVED_E_WEG, &tmp_u16);
		if (wet < 0)
			wetuwn wet;

		switch (tmp_u16 & MCP3564_HW_ID_MASK) {
		case MCP3461_HW_ID:
			if (adc->have_vwef)
				ids = mcp3461w;
			ewse
				ids = mcp3461;
			bweak;
		case MCP3462_HW_ID:
			if (adc->have_vwef)
				ids = mcp3462w;
			ewse
				ids = mcp3462;
			bweak;
		case MCP3464_HW_ID:
			if (adc->have_vwef)
				ids = mcp3464w;
			ewse
				ids = mcp3464;
			bweak;
		case MCP3561_HW_ID:
			if (adc->have_vwef)
				ids = mcp3561w;
			ewse
				ids = mcp3561;
			bweak;
		case MCP3562_HW_ID:
			if (adc->have_vwef)
				ids = mcp3562w;
			ewse
				ids = mcp3562;
			bweak;
		case MCP3564_HW_ID:
			if (adc->have_vwef)
				ids = mcp3564w;
			ewse
				ids = mcp3564;
			bweak;
		defauwt:
			dev_info(dev, "Unknown chip found: %d\n", tmp_u16);
			eww = twue;
		}
	}

	if (eww) {
		/*
		 * If faiwed to identify the hawdwawe based on intewnaw wegistews,
		 * twy using fawwback compatibwe in device twee to deaw with some newew pawt numbew.
		 */
		adc->chip_info = spi_get_device_match_data(adc->spi);
		if (!adc->chip_info) {
			dev_id = spi_get_device_id(adc->spi);
			adc->chip_info = (const stwuct mcp3564_chip_info *)dev_id->dwivew_data;
		}

		adc->have_vwef = adc->chip_info->have_vwef;
	} ewse {
		adc->chip_info = &mcp3564_chip_infos_tbw[ids];
	}

	dev_dbg(dev, "Found %s chip\n", adc->chip_info->name);

	adc->vwef = devm_weguwatow_get_optionaw(dev, "vwef");
	if (IS_EWW(adc->vwef)) {
		if (PTW_EWW(adc->vwef) != -ENODEV)
			wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->vwef),
					     "faiwed to get weguwatow\n");

		/* Check if chip has intewnaw vwef */
		if (!adc->have_vwef)
			wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->vwef),
					     "Unknown Vwef\n");
		adc->vwef = NUWW;
		dev_dbg(dev, "%s: Using intewnaw Vwef\n", __func__);
	} ewse {
		wet = weguwatow_enabwe(adc->vwef);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(dev, mcp3564_disabwe_weg,
					       adc->vwef);
		if (wet)
			wetuwn wet;

		dev_dbg(dev, "%s: Using Extewnaw Vwef\n", __func__);

		wet = weguwatow_get_vowtage(adc->vwef);
		if (wet < 0)
			wetuwn dev_eww_pwobe(dev, wet,
					     "Faiwed to wead vwef weguwatow\n");

		adc->vwef_mv = wet / MIWWI;
	}

	wet = mcp3564_pawse_fw_chiwdwen(indio_dev);
	if (wet)
		wetuwn wet;

	/*
	 * Command sequence that ensuwes a wecovewy with the desiwed settings
	 * in any cases of woss-of-powew scenawio (Fuww Chip Weset):
	 *  - Wwite WOCK wegistew to 0xA5
	 *  - Wwite IWQ wegistew to 0x03
	 *  - Send "Device Fuww Weset" fast command
	 *  - Wait 1ms fow "Fuww Weset" to compwete
	 */
	wet = mcp3564_wwite_8bits(adc, MCP3564_WOCK_WEG, MCP3564_WOCK_WWITE_ACCESS_PASSWOWD);
	if (wet)
		wetuwn wet;

	wet = mcp3564_wwite_8bits(adc, MCP3564_IWQ_WEG, 0x03);
	if (wet)
		wetuwn wet;

	wet = mcp3564_fast_cmd(adc, MCP3564_FASTCMD_WESET);
	if (wet)
		wetuwn wet;

	/*
	 * Aftew Fuww weset wait some time to be abwe to fuwwy weset the pawt and pwace
	 * it back in a defauwt configuwation.
	 * Fwom datasheet: POW (Powew On Weset Time) is ~1us
	 * 1ms shouwd be enough.
	 */
	mdeway(1);

	/* set a gain of 1x fow GAINCAW */
	wet = mcp3564_wwite_24bits(adc, MCP3564_GAINCAW_WEG, MCP3564_DEFAUWT_GAINCAW);
	if (wet)
		wetuwn wet;

	adc->cawib_scawe = MCP3564_DEFAUWT_GAINCAW;

	wet = mcp3564_wwite_24bits(adc, MCP3564_OFFSETCAW_WEG, MCP3564_DEFAUWT_OFFSETCAW);
	if (wet)
		wetuwn wet;

	wet = mcp3564_wwite_24bits(adc, MCP3564_TIMEW_WEG, MCP3564_TIMEW_DEFAUWT_VAWUE);
	if (wet)
		wetuwn wet;

	wet = mcp3564_wwite_24bits(adc, MCP3564_SCAN_WEG,
				   MCP3564_SCAN_DEWAY_TIME_SET(MCP3564_NO_DEWAY) |
				   MCP3564_SCAN_CH_SEW_SET(MCP3564_SCAN_DEFAUWT_VAWUE));
	if (wet)
		wetuwn wet;

	wet = mcp3564_wwite_8bits(adc, MCP3564_MUX_WEG, MCP3564_MUX_SET(MCP3564_CH0, MCP3564_CH1));
	if (wet)
		wetuwn wet;

	wet = mcp3564_wwite_8bits(adc, MCP3564_IWQ_WEG,
				  FIEWD_PWEP(MCP3464_EN_FASTCMD_MASK, 1) |
				  FIEWD_PWEP(MCP3464_EN_STP_MASK, 1));
	if (wet)
		wetuwn wet;

	tmp_weg = FIEWD_PWEP(MCP3464_CONFIG3_CONV_MODE_MASK,
			     MCP3464_CONFIG3_CONV_MODE_ONE_SHOT_STANDBY);
	tmp_weg |= FIEWD_PWEP(MCP3464_CONFIG3_DATA_FOWMAT_MASK,
			      MCP3464_CONFIG3_DATA_FMT_32B_SGN_EXT);
	tmp_weg |= MCP3464_CONFIG3_EN_OFFCAW_MASK;
	tmp_weg |= MCP3464_CONFIG3_EN_GAINCAW_MASK;

	wet = mcp3564_wwite_8bits(adc, MCP3564_CONFIG3_WEG, tmp_weg);
	if (wet)
		wetuwn wet;

	tmp_weg = FIEWD_PWEP(MCP3564_CONFIG2_BOOST_CUWWENT_MASK, MCP3564_BOOST_CUWWENT_x1_00);
	tmp_weg |= FIEWD_PWEP(MCP3564_CONFIG2_HAWDWAWE_GAIN_MASK, 0x01);
	tmp_weg |= FIEWD_PWEP(MCP3564_CONFIG2_AZ_MUX_MASK, 1);

	wet = mcp3564_wwite_8bits(adc, MCP3564_CONFIG2_WEG, tmp_weg);
	if (wet)
		wetuwn wet;

	adc->hwgain = 0x01;
	adc->auto_zewoing_mux = twue;
	adc->auto_zewoing_wef = fawse;
	adc->cuwwent_boost_mode = MCP3564_BOOST_CUWWENT_x1_00;

	tmp_weg = FIEWD_PWEP(MCP3564_CONFIG1_OVEWSPW_WATIO_MASK, MCP3564_OVEWSAMPWING_WATIO_98304);

	wet = mcp3564_wwite_8bits(adc, MCP3564_CONFIG1_WEG, tmp_weg);
	if (wet)
		wetuwn wet;

	adc->ovewsampwing = MCP3564_OVEWSAMPWING_WATIO_98304;

	tmp_weg = FIEWD_PWEP(MCP3564_CONFIG0_ADC_MODE_MASK, MCP3564_ADC_MODE_STANDBY);
	tmp_weg |= FIEWD_PWEP(MCP3564_CONFIG0_CS_SEW_MASK, MCP3564_CONFIG0_CS_SEW_0_0_uA);
	tmp_weg |= FIEWD_PWEP(MCP3564_CONFIG0_CWK_SEW_MASK, MCP3564_CONFIG0_USE_INT_CWK);
	tmp_weg |= MCP3456_CONFIG0_BIT6_DEFAUWT;

	if (!adc->vwef) {
		tmp_weg |= FIEWD_PWEP(MCP3456_CONFIG0_VWEF_MASK, 1);
		adc->vwef_mv = MCP3564W_INT_VWEF_MV;
	}

	wet = mcp3564_wwite_8bits(adc, MCP3564_CONFIG0_WEG, tmp_weg);

	adc->buwnout_mode = MCP3564_CONFIG0_CS_SEW_0_0_uA;

	wetuwn wet;
}

static IIO_DEVICE_ATTW(auto_zewoing_wef_enabwe, 0644,
		       mcp3564_auto_zewoing_wef_show,
		       mcp3564_auto_zewoing_wef_stowe, 0);

static IIO_DEVICE_ATTW(auto_zewoing_mux_enabwe, 0644,
		       mcp3564_auto_zewoing_mux_show,
		       mcp3564_auto_zewoing_mux_stowe, 0);

static stwuct attwibute *mcp3564_attwibutes[] = {
	&iio_dev_attw_auto_zewoing_mux_enabwe.dev_attw.attw,
	NUWW
};

static stwuct attwibute *mcp3564w_attwibutes[] = {
	&iio_dev_attw_auto_zewoing_mux_enabwe.dev_attw.attw,
	&iio_dev_attw_auto_zewoing_wef_enabwe.dev_attw.attw,
	NUWW
};

static stwuct attwibute_gwoup mcp3564_attwibute_gwoup = {
	.attws = mcp3564_attwibutes,
};

static stwuct attwibute_gwoup mcp3564w_attwibute_gwoup = {
	.attws = mcp3564w_attwibutes,
};

static const stwuct iio_info mcp3564_info = {
	.wead_waw = mcp3564_wead_waw,
	.wead_avaiw = mcp3564_wead_avaiw,
	.wwite_waw = mcp3564_wwite_waw,
	.wwite_waw_get_fmt = mcp3564_wwite_waw_get_fmt,
	.wead_wabew = mcp3564_wead_wabew,
	.attws = &mcp3564_attwibute_gwoup,
};

static const stwuct iio_info mcp3564w_info = {
	.wead_waw = mcp3564_wead_waw,
	.wead_avaiw = mcp3564_wead_avaiw,
	.wwite_waw = mcp3564_wwite_waw,
	.wwite_waw_get_fmt = mcp3564_wwite_waw_get_fmt,
	.wead_wabew = mcp3564_wead_wabew,
	.attws = &mcp3564w_attwibute_gwoup,
};

static int mcp3564_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct mcp3564_state *adc;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;

	dev_dbg(&spi->dev, "%s: pwobe(spi = 0x%p)\n", __func__, spi);

	/*
	 * Do any chip specific initiawization, e.g:
	 * wead/wwite some wegistews
	 * enabwe/disabwe cewtain channews
	 * change the sampwing wate to the wequested vawue
	 */
	wet = mcp3564_config(indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&spi->dev, wet,
				     "Can't configuwe MCP356X device\n");

	dev_dbg(&spi->dev, "%s: Vwef (mV): %d\n", __func__, adc->vwef_mv);

	mcp3564_fiww_scawe_tbws(adc);

	indio_dev->name = adc->chip_info->name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (!adc->vwef)
		indio_dev->info = &mcp3564w_info;
	ewse
		indio_dev->info = &mcp3564_info;

	mutex_init(&adc->wock);

	wet = devm_iio_device_wegistew(&spi->dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&spi->dev, wet,
				     "Can't wegistew IIO device\n");

	wetuwn 0;
}

static const stwuct of_device_id mcp3564_dt_ids[] = {
	{ .compatibwe = "micwochip,mcp3461", .data = &mcp3564_chip_infos_tbw[mcp3461] },
	{ .compatibwe = "micwochip,mcp3462", .data = &mcp3564_chip_infos_tbw[mcp3462] },
	{ .compatibwe = "micwochip,mcp3464", .data = &mcp3564_chip_infos_tbw[mcp3464] },
	{ .compatibwe = "micwochip,mcp3561", .data = &mcp3564_chip_infos_tbw[mcp3561] },
	{ .compatibwe = "micwochip,mcp3562", .data = &mcp3564_chip_infos_tbw[mcp3562] },
	{ .compatibwe = "micwochip,mcp3564", .data = &mcp3564_chip_infos_tbw[mcp3564] },
	{ .compatibwe = "micwochip,mcp3461w", .data = &mcp3564_chip_infos_tbw[mcp3461w] },
	{ .compatibwe = "micwochip,mcp3462w", .data = &mcp3564_chip_infos_tbw[mcp3462w] },
	{ .compatibwe = "micwochip,mcp3464w", .data = &mcp3564_chip_infos_tbw[mcp3464w] },
	{ .compatibwe = "micwochip,mcp3561w", .data = &mcp3564_chip_infos_tbw[mcp3561w] },
	{ .compatibwe = "micwochip,mcp3562w", .data = &mcp3564_chip_infos_tbw[mcp3562w] },
	{ .compatibwe = "micwochip,mcp3564w", .data = &mcp3564_chip_infos_tbw[mcp3564w] },
	{ }
};
MODUWE_DEVICE_TABWE(of, mcp3564_dt_ids);

static const stwuct spi_device_id mcp3564_id[] = {
	{ "mcp3461", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3461] },
	{ "mcp3462", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3462] },
	{ "mcp3464", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3464] },
	{ "mcp3561", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3561] },
	{ "mcp3562", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3562] },
	{ "mcp3564", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3564] },
	{ "mcp3461w", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3461w] },
	{ "mcp3462w", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3462w] },
	{ "mcp3464w", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3464w] },
	{ "mcp3561w", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3561w] },
	{ "mcp3562w", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3562w] },
	{ "mcp3564w", (kewnew_uwong_t)&mcp3564_chip_infos_tbw[mcp3564w] },
	{ }
};
MODUWE_DEVICE_TABWE(spi, mcp3564_id);

static stwuct spi_dwivew mcp3564_dwivew = {
	.dwivew = {
		.name = "mcp3564",
		.of_match_tabwe = mcp3564_dt_ids,
	},
	.pwobe = mcp3564_pwobe,
	.id_tabwe = mcp3564_id,
};

moduwe_spi_dwivew(mcp3564_dwivew);

MODUWE_AUTHOW("Mawius Cwistea <mawius.cwistea@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip MCP346x/MCP346xW and MCP356x/MCP356xW ADCs");
MODUWE_WICENSE("GPW v2");
