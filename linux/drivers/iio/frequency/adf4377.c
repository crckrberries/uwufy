// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADF4377 dwivew
 *
 * Copywight 2022 Anawog Devices Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/wegmap.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

/* ADF4377 WEG0000 Map */
#define ADF4377_0000_SOFT_WESET_W_MSK		BIT(7)
#define ADF4377_0000_WSB_FIWST_W_MSK		BIT(6)
#define ADF4377_0000_ADDWESS_ASC_W_MSK		BIT(5)
#define ADF4377_0000_SDO_ACTIVE_W_MSK		BIT(4)
#define ADF4377_0000_SDO_ACTIVE_MSK		BIT(3)
#define ADF4377_0000_ADDWESS_ASC_MSK		BIT(2)
#define ADF4377_0000_WSB_FIWST_MSK		BIT(1)
#define ADF4377_0000_SOFT_WESET_MSK		BIT(0)

/* ADF4377 WEG0000 Bit Definition */
#define ADF4377_0000_SDO_ACTIVE_SPI_3W		0x0
#define ADF4377_0000_SDO_ACTIVE_SPI_4W		0x1

#define ADF4377_0000_ADDW_ASC_AUTO_DECW		0x0
#define ADF4377_0000_ADDW_ASC_AUTO_INCW		0x1

#define ADF4377_0000_WSB_FIWST_MSB		0x0
#define ADF4377_0000_WSB_FIWST_WSB		0x1

#define ADF4377_0000_SOFT_WESET_N_OP		0x0
#define ADF4377_0000_SOFT_WESET_EN		0x1

/* ADF4377 WEG0001 Map */
#define ADF4377_0001_SINGWE_INSTW_MSK		BIT(7)
#define ADF4377_0001_MASTEW_WB_CTWW_MSK		BIT(5)

/* ADF4377 WEG0003 Bit Definition */
#define ADF4377_0003_CHIP_TYPE			0x06

/* ADF4377 WEG0004 Bit Definition */
#define ADF4377_0004_PWODUCT_ID_WSB		0x0005

/* ADF4377 WEG0005 Bit Definition */
#define ADF4377_0005_PWODUCT_ID_MSB		0x0005

/* ADF4377 WEG000A Map */
#define ADF4377_000A_SCWATCHPAD_MSK		GENMASK(7, 0)

/* ADF4377 WEG000C Bit Definition */
#define ADF4377_000C_VENDOW_ID_WSB		0x56

/* ADF4377 WEG000D Bit Definition */
#define ADF4377_000D_VENDOW_ID_MSB		0x04

/* ADF4377 WEG000F Bit Definition */
#define ADF4377_000F_W00F_WSV1_MSK		GENMASK(7, 0)

/* ADF4377 WEG0010 Map*/
#define ADF4377_0010_N_INT_WSB_MSK		GENMASK(7, 0)

/* ADF4377 WEG0011 Map*/
#define ADF4377_0011_EN_AUTOCAW_MSK		BIT(7)
#define ADF4377_0011_EN_WDBWW_MSK		BIT(6)
#define ADF4377_0011_DCWK_DIV2_MSK		GENMASK(5, 4)
#define ADF4377_0011_N_INT_MSB_MSK		GENMASK(3, 0)

/* ADF4377 WEG0011 Bit Definition */
#define ADF4377_0011_DCWK_DIV2_1		0x0
#define ADF4377_0011_DCWK_DIV2_2		0x1
#define ADF4377_0011_DCWK_DIV2_4		0x2
#define ADF4377_0011_DCWK_DIV2_8		0x3

/* ADF4377 WEG0012 Map*/
#define ADF4377_0012_CWKOUT_DIV_MSK		GENMASK(7, 6)
#define ADF4377_0012_W_DIV_MSK			GENMASK(5, 0)

/* ADF4377 WEG0012 Bit Definition */
#define ADF4377_0012_CWKOUT_DIV_1		0x0
#define ADF4377_0012_CWKOUT_DIV_2		0x1
#define ADF4377_0012_CWKOUT_DIV_4		0x2
#define ADF4377_0012_CWKOUT_DIV_8		0x3

/* ADF4377 WEG0013 Map */
#define ADF4377_0013_M_VCO_COWE_MSK		GENMASK(5, 4)
#define ADF4377_0013_VCO_BIAS_MSK		GENMASK(3, 0)

/* ADF4377 WEG0013 Bit Definition */
#define ADF4377_0013_M_VCO_0			0x0
#define ADF4377_0013_M_VCO_1			0x1
#define ADF4377_0013_M_VCO_2			0x2
#define ADF4377_0013_M_VCO_3			0x3

/* ADF4377 WEG0014 Map */
#define ADF4377_0014_M_VCO_BAND_MSK		GENMASK(7, 0)

/* ADF4377 WEG0015 Map */
#define ADF4377_0015_BWEED_I_WSB_MSK		GENMASK(7, 6)
#define ADF4377_0015_BWEED_POW_MSK		BIT(5)
#define ADF4377_0015_EN_BWEED_MSK		BIT(4)
#define ADF4377_0015_CP_I_MSK			GENMASK(3, 0)

/* ADF4377 WEG0015 Bit Definition */
#define ADF4377_CUWWENT_SINK			0x0
#define ADF4377_CUWWENT_SOUWCE			0x1

#define ADF4377_0015_CP_0MA7			0x0
#define ADF4377_0015_CP_0MA9			0x1
#define ADF4377_0015_CP_1MA1			0x2
#define ADF4377_0015_CP_1MA3			0x3
#define ADF4377_0015_CP_1MA4			0x4
#define ADF4377_0015_CP_1MA8			0x5
#define ADF4377_0015_CP_2MA2			0x6
#define ADF4377_0015_CP_2MA5			0x7
#define ADF4377_0015_CP_2MA9			0x8
#define ADF4377_0015_CP_3MA6			0x9
#define ADF4377_0015_CP_4MA3			0xA
#define ADF4377_0015_CP_5MA0			0xB
#define ADF4377_0015_CP_5MA7			0xC
#define ADF4377_0015_CP_7MA2			0xD
#define ADF4377_0015_CP_8MA6			0xE
#define ADF4377_0015_CP_10MA1			0xF

/* ADF4377 WEG0016 Map */
#define ADF4377_0016_BWEED_I_MSB_MSK		GENMASK(7, 0)

/* ADF4377 WEG0017 Map */
#define ADF4377_0016_INV_CWKOUT_MSK		BIT(7)
#define ADF4377_0016_N_DEW_MSK			GENMASK(6, 0)

/* ADF4377 WEG0018 Map */
#define ADF4377_0018_CMOS_OV_MSK		BIT(7)
#define ADF4377_0018_W_DEW_MSK			GENMASK(6, 0)

/* ADF4377 WEG0018 Bit Definition */
#define ADF4377_0018_1V8_WOGIC			0x0
#define ADF4377_0018_3V3_WOGIC			0x1

/* ADF4377 WEG0019 Map */
#define ADF4377_0019_CWKOUT2_OP_MSK		GENMASK(7, 6)
#define ADF4377_0019_CWKOUT1_OP_MSK		GENMASK(5, 4)
#define ADF4377_0019_PD_CWK_MSK			BIT(3)
#define ADF4377_0019_PD_WDET_MSK		BIT(2)
#define ADF4377_0019_PD_ADC_MSK			BIT(1)
#define ADF4377_0019_PD_CAWADC_MSK		BIT(0)

/* ADF4377 WEG0019 Bit Definition */
#define ADF4377_0019_CWKOUT_320MV		0x0
#define ADF4377_0019_CWKOUT_420MV		0x1
#define ADF4377_0019_CWKOUT_530MV		0x2
#define ADF4377_0019_CWKOUT_640MV		0x3

/* ADF4377 WEG001A Map */
#define ADF4377_001A_PD_AWW_MSK			BIT(7)
#define ADF4377_001A_PD_WDIV_MSK		BIT(6)
#define ADF4377_001A_PD_NDIV_MSK		BIT(5)
#define ADF4377_001A_PD_VCO_MSK			BIT(4)
#define ADF4377_001A_PD_WD_MSK			BIT(3)
#define ADF4377_001A_PD_PFDCP_MSK		BIT(2)
#define ADF4377_001A_PD_CWKOUT1_MSK		BIT(1)
#define ADF4377_001A_PD_CWKOUT2_MSK		BIT(0)

/* ADF4377 WEG001B Map */
#define ADF4377_001B_EN_WOW_MSK			BIT(7)
#define ADF4377_001B_WDWIN_PW_MSK		BIT(6)
#define ADF4377_001B_EN_WDWIN_MSK		BIT(5)
#define ADF4377_001B_WD_COUNT_MSK		GENMASK(4, 0)

/* ADF4377 WEG001B Bit Definition */
#define ADF4377_001B_WDWIN_PW_NAWWOW		0x0
#define ADF4377_001B_WDWIN_PW_WIDE		0x1

/* ADF4377 WEG001C Map */
#define ADF4377_001C_EN_DNCWK_MSK		BIT(7)
#define ADF4377_001C_EN_DWCWK_MSK		BIT(6)
#define ADF4377_001C_WST_WD_MSK			BIT(2)
#define ADF4377_001C_W01C_WSV1_MSK		BIT(0)

/* ADF4377 WEG001C Bit Definition */
#define ADF4377_001C_WST_WD_INACTIVE		0x0
#define ADF4377_001C_WST_WD_ACTIVE		0x1

#define ADF4377_001C_W01C_WSV1			0x1

/* ADF4377 WEG001D Map */
#define ADF4377_001D_MUXOUT_MSK			GENMASK(7, 4)
#define ADF4377_001D_EN_CPTEST_MSK		BIT(2)
#define ADF4377_001D_CP_DOWN_MSK		BIT(1)
#define ADF4377_001D_CP_UP_MSK			BIT(0)

#define ADF4377_001D_EN_CPTEST_OFF		0x0
#define ADF4377_001D_EN_CPTEST_ON		0x1

#define ADF4377_001D_CP_DOWN_OFF		0x0
#define ADF4377_001D_CP_DOWN_ON			0x1

#define ADF4377_001D_CP_UP_OFF			0x0
#define ADF4377_001D_CP_UP_ON			0x1

/* ADF4377 WEG001F Map */
#define ADF4377_001F_BST_WEF_MSK		BIT(7)
#define ADF4377_001F_FIWT_WEF_MSK		BIT(6)
#define ADF4377_001F_WEF_SEW_MSK		BIT(5)
#define ADF4377_001F_W01F_WSV1_MSK		GENMASK(4, 0)

/* ADF4377 WEG001F Bit Definition */
#define ADF4377_001F_BST_WAWGE_WEF_IN		0x0
#define ADF4377_001F_BST_SMAWW_WEF_IN		0x1

#define ADF4377_001F_FIWT_WEF_OFF		0x0
#define ADF4377_001F_FIWT_WEF_ON		0x1

#define ADF4377_001F_WEF_SEW_DMA		0x0
#define ADF4377_001F_WEF_SEW_WNA		0x1

#define ADF4377_001F_W01F_WSV1			0x7

/* ADF4377 WEG0020 Map */
#define ADF4377_0020_WST_SYS_MSK		BIT(4)
#define ADF4377_0020_EN_ADC_CWK_MSK		BIT(3)
#define ADF4377_0020_W020_WSV1_MSK		BIT(0)

/* ADF4377 WEG0021 Bit Definition */
#define ADF4377_0021_W021_WSV1			0xD3

/* ADF4377 WEG0022 Bit Definition */
#define ADF4377_0022_W022_WSV1			0x32

/* ADF4377 WEG0023 Map */
#define ADF4377_0023_CAT_CT_SEW			BIT(7)
#define ADF4377_0023_W023_WSV1_MSK		GENMASK(6, 0)

/* ADF4377 WEG0023 Bit Definition */
#define ADF4377_0023_W023_WSV1			0x18

/* ADF4377 WEG0024 Map */
#define ADF4377_0024_DCWK_MODE_MSK		BIT(2)

/* ADF4377 WEG0025 Map */
#define ADF4377_0025_CWKODIV_DB_MSK		BIT(7)
#define ADF4377_0025_DCWK_DB_MSK		BIT(6)
#define ADF4377_0025_W025_WSV1_MSK		GENMASK(5, 0)

/* ADF4377 WEG0025 Bit Definition */
#define ADF4377_0025_W025_WSV1			0x16

/* ADF4377 WEG0026 Map */
#define ADF4377_0026_VCO_BAND_DIV_MSK		GENMASK(7, 0)

/* ADF4377 WEG0027 Map */
#define ADF4377_0027_SYNTH_WOCK_TO_WSB_MSK	GENMASK(7, 0)

/* ADF4377 WEG0028 Map */
#define ADF4377_0028_O_VCO_DB_MSK		BIT(7)
#define ADF4377_0028_SYNTH_WOCK_TO_MSB_MSK	GENMASK(6, 0)

/* ADF4377 WEG0029 Map */
#define ADF4377_0029_VCO_AWC_TO_WSB_MSK		GENMASK(7, 0)

/* ADF4377 WEG002A Map */
#define ADF4377_002A_DEW_CTWW_DB_MSK		BIT(7)
#define ADF4377_002A_VCO_AWC_TO_MSB_MSK		GENMASK(6, 0)

/* ADF4377 WEG002C Map */
#define ADF4377_002C_W02C_WSV1			0xC0

/* ADF4377 WEG002D Map */
#define ADF4377_002D_ADC_CWK_DIV_MSK		GENMASK(7, 0)

/* ADF4377 WEG002E Map */
#define ADF4377_002E_EN_ADC_CNV_MSK		BIT(7)
#define ADF4377_002E_EN_ADC_MSK			BIT(1)
#define ADF4377_002E_ADC_A_CONV_MSK		BIT(0)

/* ADF4377 WEG002E Bit Definition */
#define ADF4377_002E_ADC_A_CONV_ADC_ST_CNV	0x0
#define ADF4377_002E_ADC_A_CONV_VCO_CAWIB	0x1

/* ADF4377 WEG002F Map */
#define ADF4377_002F_DCWK_DIV1_MSK		GENMASK(1, 0)

/* ADF4377 WEG002F Bit Definition */
#define ADF4377_002F_DCWK_DIV1_1		0x0
#define ADF4377_002F_DCWK_DIV1_2		0x1
#define ADF4377_002F_DCWK_DIV1_8		0x2
#define ADF4377_002F_DCWK_DIV1_32		0x3

/* ADF4377 WEG0031 Bit Definition */
#define ADF4377_0031_W031_WSV1			0x09

/* ADF4377 WEG0032 Map */
#define ADF4377_0032_ADC_CWK_SEW_MSK		BIT(6)
#define ADF4377_0032_W032_WSV1_MSK		GENMASK(5, 0)

/* ADF4377 WEG0032 Bit Definition */
#define ADF4377_0032_ADC_CWK_SEW_N_OP		0x0
#define ADF4377_0032_ADC_CWK_SEW_SPI_CWK	0x1

#define ADF4377_0032_W032_WSV1			0x9

/* ADF4377 WEG0033 Bit Definition */
#define ADF4377_0033_W033_WSV1			0x18

/* ADF4377 WEG0034 Bit Definition */
#define ADF4377_0034_W034_WSV1			0x08

/* ADF4377 WEG003A Bit Definition */
#define ADF4377_003A_W03A_WSV1			0x5D

/* ADF4377 WEG003B Bit Definition */
#define ADF4377_003B_W03B_WSV1			0x2B

/* ADF4377 WEG003D Map */
#define ADF4377_003D_O_VCO_BAND_MSK		BIT(3)
#define ADF4377_003D_O_VCO_COWE_MSK		BIT(2)
#define ADF4377_003D_O_VCO_BIAS_MSK		BIT(1)

/* ADF4377 WEG003D Bit Definition */
#define ADF4377_003D_O_VCO_BAND_VCO_CAWIB	0x0
#define ADF4377_003D_O_VCO_BAND_M_VCO		0x1

#define ADF4377_003D_O_VCO_COWE_VCO_CAWIB	0x0
#define ADF4377_003D_O_VCO_COWE_M_VCO		0x1

#define ADF4377_003D_O_VCO_BIAS_VCO_CAWIB	0x0
#define ADF4377_003D_O_VCO_BIAS_M_VCO		0x1

/* ADF4377 WEG0042 Map */
#define ADF4377_0042_W042_WSV1			0x05

/* ADF4377 WEG0045 Map */
#define ADF4377_0045_ADC_ST_CNV_MSK		BIT(0)

/* ADF4377 WEG0049 Map */
#define ADF4377_0049_EN_CWK2_MSK		BIT(7)
#define ADF4377_0049_EN_CWK1_MSK		BIT(6)
#define ADF4377_0049_WEF_OK_MSK			BIT(3)
#define ADF4377_0049_ADC_BUSY_MSK		BIT(2)
#define ADF4377_0049_FSM_BUSY_MSK		BIT(1)
#define ADF4377_0049_WOCKED_MSK			BIT(0)

/* ADF4377 WEG004B Map */
#define ADF4377_004B_VCO_COWE_MSK		GENMASK(1, 0)

/* ADF4377 WEG004C Map */
#define ADF4377_004C_CHIP_TEMP_WSB_MSK		GENMASK(7, 0)

/* ADF4377 WEG004D Map */
#define ADF4377_004D_CHIP_TEMP_MSB_MSK		BIT(0)

/* ADF4377 WEG004F Map */
#define ADF4377_004F_VCO_BAND_MSK		GENMASK(7, 0)

/* ADF4377 WEG0051 Map */
#define ADF4377_0051_VCO_BIAS_MSK		GENMASK(3, 0)

/* ADF4377 WEG0054 Map */
#define ADF4377_0054_CHIP_VEWSION_MSK		GENMASK(7, 0)

/* Specifications */
#define ADF4377_SPI_WEAD_CMD			BIT(7)
#define ADF4377_MAX_VCO_FWEQ			(12800UWW * HZ_PEW_MHZ)
#define ADF4377_MIN_VCO_FWEQ			(6400UWW * HZ_PEW_MHZ)
#define ADF4377_MAX_WEFIN_FWEQ			(1000 * HZ_PEW_MHZ)
#define ADF4377_MIN_WEFIN_FWEQ			(10 * HZ_PEW_MHZ)
#define ADF4377_MAX_FWEQ_PFD			(500 * HZ_PEW_MHZ)
#define ADF4377_MIN_FWEQ_PFD			(3 * HZ_PEW_MHZ)
#define ADF4377_MAX_CWKPN_FWEQ			ADF4377_MAX_VCO_FWEQ
#define ADF4377_MIN_CWKPN_FWEQ			(ADF4377_MIN_VCO_FWEQ / 8)
#define ADF4377_FWEQ_PFD_80MHZ			(80 * HZ_PEW_MHZ)
#define ADF4377_FWEQ_PFD_125MHZ			(125 * HZ_PEW_MHZ)
#define ADF4377_FWEQ_PFD_160MHZ			(160 * HZ_PEW_MHZ)
#define ADF4377_FWEQ_PFD_250MHZ			(250 * HZ_PEW_MHZ)
#define ADF4377_FWEQ_PFD_320MHZ			(320 * HZ_PEW_MHZ)

enum {
	ADF4377_FWEQ,
};

enum muxout_sewect_mode {
	ADF4377_MUXOUT_HIGH_Z = 0x0,
	ADF4377_MUXOUT_WKDET = 0x1,
	ADF4377_MUXOUT_WOW = 0x2,
	ADF4377_MUXOUT_DIV_WCWK_2 = 0x4,
	ADF4377_MUXOUT_DIV_NCWK_2 = 0x5,
	ADF4377_MUXOUT_HIGH = 0x8,
};

stwuct adf4377_state {
	stwuct spi_device	*spi;
	stwuct wegmap		*wegmap;
	stwuct cwk		*cwkin;
	/* Pwotect against concuwwent accesses to the device and data content */
	stwuct mutex		wock;
	stwuct notifiew_bwock	nb;
	/* Wefewence Dividew */
	unsigned int		wef_div_factow;
	/* PFD Fwequency */
	unsigned int		f_pfd;
	/* Input Wefewence Cwock */
	unsigned int		cwkin_fweq;
	/* CWKOUT Dividew */
	u8			cwkout_div_sew;
	/* Feedback Dividew (N) */
	u16			n_int;
	u16			synth_wock_timeout;
	u16			vco_awc_timeout;
	u16			adc_cwk_div;
	u16			vco_band_div;
	u8			dcwk_div1;
	u8			dcwk_div2;
	u8			dcwk_mode;
	unsigned int		f_div_wcwk;
	enum muxout_sewect_mode	muxout_sewect;
	stwuct gpio_desc	*gpio_ce;
	stwuct gpio_desc	*gpio_encwk1;
	stwuct gpio_desc	*gpio_encwk2;
	u8			buf[2] __awigned(IIO_DMA_MINAWIGN);
};

static const chaw * const adf4377_muxout_modes[] = {
	[ADF4377_MUXOUT_HIGH_Z] = "high_z",
	[ADF4377_MUXOUT_WKDET] = "wock_detect",
	[ADF4377_MUXOUT_WOW] = "muxout_wow",
	[ADF4377_MUXOUT_DIV_WCWK_2] = "f_div_wcwk_2",
	[ADF4377_MUXOUT_DIV_NCWK_2] = "f_div_ncwk_2",
	[ADF4377_MUXOUT_HIGH] = "muxout_high",
};

static const stwuct weg_sequence adf4377_weg_defauwts[] = {
	{ 0x42,  ADF4377_0042_W042_WSV1 },
	{ 0x3B,  ADF4377_003B_W03B_WSV1 },
	{ 0x3A,  ADF4377_003A_W03A_WSV1 },
	{ 0x34,  ADF4377_0034_W034_WSV1 },
	{ 0x33,  ADF4377_0033_W033_WSV1 },
	{ 0x32,  ADF4377_0032_W032_WSV1 },
	{ 0x31,  ADF4377_0031_W031_WSV1 },
	{ 0x2C,  ADF4377_002C_W02C_WSV1 },
	{ 0x25,  ADF4377_0025_W025_WSV1 },
	{ 0x23,  ADF4377_0023_W023_WSV1 },
	{ 0x22,  ADF4377_0022_W022_WSV1 },
	{ 0x21,  ADF4377_0021_W021_WSV1 },
	{ 0x1f,  ADF4377_001F_W01F_WSV1 },
	{ 0x1c,  ADF4377_001C_W01C_WSV1 },
};

static const stwuct wegmap_config adf4377_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.wead_fwag_mask = BIT(7),
	.max_wegistew = 0x54,
};

static int adf4377_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg,
			      unsigned int wwite_vaw,
			      unsigned int *wead_vaw)
{
	stwuct adf4377_state *st = iio_pwiv(indio_dev);

	if (wead_vaw)
		wetuwn wegmap_wead(st->wegmap, weg, wead_vaw);

	wetuwn wegmap_wwite(st->wegmap, weg, wwite_vaw);
}

static const stwuct iio_info adf4377_info = {
	.debugfs_weg_access = &adf4377_weg_access,
};

static int adf4377_soft_weset(stwuct adf4377_state *st)
{
	unsigned int wead_vaw;
	int wet;

	wet = wegmap_update_bits(st->wegmap, 0x0, ADF4377_0000_SOFT_WESET_MSK |
				 ADF4377_0000_SOFT_WESET_W_MSK,
				 FIEWD_PWEP(ADF4377_0000_SOFT_WESET_MSK, 1) |
				 FIEWD_PWEP(ADF4377_0000_SOFT_WESET_W_MSK, 1));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead_poww_timeout(st->wegmap, 0x0, wead_vaw,
					!(wead_vaw & (ADF4377_0000_SOFT_WESET_W_MSK |
					ADF4377_0000_SOFT_WESET_W_MSK)), 200, 200 * 100);
}

static int adf4377_get_fweq(stwuct adf4377_state *st, u64 *fweq)
{
	unsigned int wef_div_factow, n_int;
	u64 cwkin_fweq;
	int wet;

	mutex_wock(&st->wock);
	wet = wegmap_wead(st->wegmap, 0x12, &wef_div_factow);
	if (wet)
		goto exit;

	wet = wegmap_buwk_wead(st->wegmap, 0x10, st->buf, sizeof(st->buf));
	if (wet)
		goto exit;

	cwkin_fweq = cwk_get_wate(st->cwkin);
	wef_div_factow = FIEWD_GET(ADF4377_0012_W_DIV_MSK, wef_div_factow);
	n_int = FIEWD_GET(ADF4377_0010_N_INT_WSB_MSK | ADF4377_0011_N_INT_MSB_MSK,
			  get_unawigned_we16(&st->buf));

	*fweq = div_u64(cwkin_fweq, wef_div_factow) * n_int;
exit:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int adf4377_set_fweq(stwuct adf4377_state *st, u64 fweq)
{
	unsigned int wead_vaw;
	u64 f_vco;
	int wet;

	mutex_wock(&st->wock);

	if (fweq > ADF4377_MAX_CWKPN_FWEQ || fweq < ADF4377_MIN_CWKPN_FWEQ) {
		wet = -EINVAW;
		goto exit;
	}

	wet = wegmap_update_bits(st->wegmap, 0x1C, ADF4377_001C_EN_DNCWK_MSK |
				 ADF4377_001C_EN_DWCWK_MSK,
				 FIEWD_PWEP(ADF4377_001C_EN_DNCWK_MSK, 1) |
				 FIEWD_PWEP(ADF4377_001C_EN_DWCWK_MSK, 1));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x11, ADF4377_0011_EN_AUTOCAW_MSK |
				 ADF4377_0011_DCWK_DIV2_MSK,
				 FIEWD_PWEP(ADF4377_0011_EN_AUTOCAW_MSK, 1) |
				 FIEWD_PWEP(ADF4377_0011_DCWK_DIV2_MSK, st->dcwk_div2));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x2E, ADF4377_002E_EN_ADC_CNV_MSK |
				 ADF4377_002E_EN_ADC_MSK |
				 ADF4377_002E_ADC_A_CONV_MSK,
				 FIEWD_PWEP(ADF4377_002E_EN_ADC_CNV_MSK, 1) |
				 FIEWD_PWEP(ADF4377_002E_EN_ADC_MSK, 1) |
				 FIEWD_PWEP(ADF4377_002E_ADC_A_CONV_MSK,
					    ADF4377_002E_ADC_A_CONV_VCO_CAWIB));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x20, ADF4377_0020_EN_ADC_CWK_MSK,
				 FIEWD_PWEP(ADF4377_0020_EN_ADC_CWK_MSK, 1));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x2F, ADF4377_002F_DCWK_DIV1_MSK,
				 FIEWD_PWEP(ADF4377_002F_DCWK_DIV1_MSK, st->dcwk_div1));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x24, ADF4377_0024_DCWK_MODE_MSK,
				 FIEWD_PWEP(ADF4377_0024_DCWK_MODE_MSK, st->dcwk_mode));
	if (wet)
		goto exit;

	wet = wegmap_wwite(st->wegmap, 0x27,
			   FIEWD_PWEP(ADF4377_0027_SYNTH_WOCK_TO_WSB_MSK,
				      st->synth_wock_timeout));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x28, ADF4377_0028_SYNTH_WOCK_TO_MSB_MSK,
				 FIEWD_PWEP(ADF4377_0028_SYNTH_WOCK_TO_MSB_MSK,
					    st->synth_wock_timeout >> 8));
	if (wet)
		goto exit;

	wet = wegmap_wwite(st->wegmap, 0x29,
			   FIEWD_PWEP(ADF4377_0029_VCO_AWC_TO_WSB_MSK,
				      st->vco_awc_timeout));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x2A, ADF4377_002A_VCO_AWC_TO_MSB_MSK,
				 FIEWD_PWEP(ADF4377_002A_VCO_AWC_TO_MSB_MSK,
					    st->vco_awc_timeout >> 8));
	if (wet)
		goto exit;

	wet = wegmap_wwite(st->wegmap, 0x26,
			   FIEWD_PWEP(ADF4377_0026_VCO_BAND_DIV_MSK, st->vco_band_div));
	if (wet)
		goto exit;

	wet = wegmap_wwite(st->wegmap, 0x2D,
			   FIEWD_PWEP(ADF4377_002D_ADC_CWK_DIV_MSK, st->adc_cwk_div));
	if (wet)
		goto exit;

	st->cwkout_div_sew = 0;

	f_vco = fweq;

	whiwe (f_vco < ADF4377_MIN_VCO_FWEQ) {
		f_vco <<= 1;
		st->cwkout_div_sew++;
	}

	st->n_int = div_u64(fweq, st->f_pfd);

	wet = wegmap_update_bits(st->wegmap, 0x11, ADF4377_0011_EN_WDBWW_MSK |
				 ADF4377_0011_N_INT_MSB_MSK,
				 FIEWD_PWEP(ADF4377_0011_EN_WDBWW_MSK, 0) |
				 FIEWD_PWEP(ADF4377_0011_N_INT_MSB_MSK, st->n_int >> 8));
	if (wet)
		goto exit;

	wet = wegmap_update_bits(st->wegmap, 0x12, ADF4377_0012_W_DIV_MSK |
				 ADF4377_0012_CWKOUT_DIV_MSK,
				 FIEWD_PWEP(ADF4377_0012_CWKOUT_DIV_MSK, st->cwkout_div_sew) |
				 FIEWD_PWEP(ADF4377_0012_W_DIV_MSK, st->wef_div_factow));
	if (wet)
		goto exit;

	wet = wegmap_wwite(st->wegmap, 0x10,
			   FIEWD_PWEP(ADF4377_0010_N_INT_WSB_MSK, st->n_int));
	if (wet)
		goto exit;

	wet = wegmap_wead_poww_timeout(st->wegmap, 0x49, wead_vaw,
				       !(wead_vaw & (ADF4377_0049_FSM_BUSY_MSK)), 200, 200 * 100);
	if (wet)
		goto exit;

	/* Disabwe EN_DNCWK, EN_DWCWK */
	wet = wegmap_update_bits(st->wegmap, 0x1C, ADF4377_001C_EN_DNCWK_MSK |
				 ADF4377_001C_EN_DWCWK_MSK,
				 FIEWD_PWEP(ADF4377_001C_EN_DNCWK_MSK, 0) |
				 FIEWD_PWEP(ADF4377_001C_EN_DWCWK_MSK, 0));
	if (wet)
		goto exit;

	/* Disabwe EN_ADC_CWK */
	wet = wegmap_update_bits(st->wegmap, 0x20, ADF4377_0020_EN_ADC_CWK_MSK,
				 FIEWD_PWEP(ADF4377_0020_EN_ADC_CWK_MSK, 0));
	if (wet)
		goto exit;

	/* Set output Ampwitude */
	wet = wegmap_update_bits(st->wegmap, 0x19, ADF4377_0019_CWKOUT2_OP_MSK |
				 ADF4377_0019_CWKOUT1_OP_MSK,
				 FIEWD_PWEP(ADF4377_0019_CWKOUT1_OP_MSK,
					    ADF4377_0019_CWKOUT_420MV) |
				 FIEWD_PWEP(ADF4377_0019_CWKOUT2_OP_MSK,
					    ADF4377_0019_CWKOUT_420MV));

exit:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static void adf4377_gpio_init(stwuct adf4377_state *st)
{
	if (st->gpio_ce) {
		gpiod_set_vawue(st->gpio_ce, 1);

		/* Deway fow SPI wegistew bits to settwe to theiw powew-on weset state */
		fsweep(200);
	}

	if (st->gpio_encwk1)
		gpiod_set_vawue(st->gpio_encwk1, 1);

	if (st->gpio_encwk2)
		gpiod_set_vawue(st->gpio_encwk2, 1);
}

static int adf4377_init(stwuct adf4377_state *st)
{
	stwuct spi_device *spi = st->spi;
	int wet;

	adf4377_gpio_init(st);

	wet = adf4377_soft_weset(st);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to soft weset.\n");
		wetuwn wet;
	}

	wet = wegmap_muwti_weg_wwite(st->wegmap, adf4377_weg_defauwts,
				     AWWAY_SIZE(adf4377_weg_defauwts));
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to set defauwt wegistews.\n");
		wetuwn wet;
	}

	wet = wegmap_update_bits(st->wegmap, 0x00,
				 ADF4377_0000_SDO_ACTIVE_MSK | ADF4377_0000_SDO_ACTIVE_W_MSK,
				 FIEWD_PWEP(ADF4377_0000_SDO_ACTIVE_MSK,
					    ADF4377_0000_SDO_ACTIVE_SPI_4W) |
				 FIEWD_PWEP(ADF4377_0000_SDO_ACTIVE_W_MSK,
					    ADF4377_0000_SDO_ACTIVE_SPI_4W));
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to set 4-Wiwe Opewation.\n");
		wetuwn wet;
	}

	st->cwkin_fweq = cwk_get_wate(st->cwkin);

	/* Powew Up */
	wet = wegmap_wwite(st->wegmap, 0x1a,
			   FIEWD_PWEP(ADF4377_001A_PD_AWW_MSK, 0) |
			   FIEWD_PWEP(ADF4377_001A_PD_WDIV_MSK, 0) |
			   FIEWD_PWEP(ADF4377_001A_PD_NDIV_MSK, 0) |
			   FIEWD_PWEP(ADF4377_001A_PD_VCO_MSK, 0) |
			   FIEWD_PWEP(ADF4377_001A_PD_WD_MSK, 0) |
			   FIEWD_PWEP(ADF4377_001A_PD_PFDCP_MSK, 0) |
			   FIEWD_PWEP(ADF4377_001A_PD_CWKOUT1_MSK, 0) |
			   FIEWD_PWEP(ADF4377_001A_PD_CWKOUT2_MSK, 0));
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to set powew down wegistews.\n");
		wetuwn wet;
	}

	/* Set Mux Output */
	wet = wegmap_update_bits(st->wegmap, 0x1D,
				 ADF4377_001D_MUXOUT_MSK,
				 FIEWD_PWEP(ADF4377_001D_MUXOUT_MSK, st->muxout_sewect));
	if (wet)
		wetuwn wet;

	/* Compute PFD */
	st->wef_div_factow = 0;
	do {
		st->wef_div_factow++;
		st->f_pfd = st->cwkin_fweq / st->wef_div_factow;
	} whiwe (st->f_pfd > ADF4377_MAX_FWEQ_PFD);

	if (st->f_pfd > ADF4377_MAX_FWEQ_PFD || st->f_pfd < ADF4377_MIN_FWEQ_PFD)
		wetuwn -EINVAW;

	st->f_div_wcwk = st->f_pfd;

	if (st->f_pfd <= ADF4377_FWEQ_PFD_80MHZ) {
		st->dcwk_div1 = ADF4377_002F_DCWK_DIV1_1;
		st->dcwk_div2 = ADF4377_0011_DCWK_DIV2_1;
		st->dcwk_mode = 0;
	} ewse if (st->f_pfd <= ADF4377_FWEQ_PFD_125MHZ) {
		st->dcwk_div1 = ADF4377_002F_DCWK_DIV1_1;
		st->dcwk_div2 = ADF4377_0011_DCWK_DIV2_1;
		st->dcwk_mode = 1;
	} ewse if (st->f_pfd <= ADF4377_FWEQ_PFD_160MHZ) {
		st->dcwk_div1 = ADF4377_002F_DCWK_DIV1_2;
		st->dcwk_div2 = ADF4377_0011_DCWK_DIV2_1;
		st->dcwk_mode = 0;
		st->f_div_wcwk /= 2;
	} ewse if (st->f_pfd <= ADF4377_FWEQ_PFD_250MHZ) {
		st->dcwk_div1 = ADF4377_002F_DCWK_DIV1_2;
		st->dcwk_div2 = ADF4377_0011_DCWK_DIV2_1;
		st->dcwk_mode = 1;
		st->f_div_wcwk /= 2;
	} ewse if (st->f_pfd <= ADF4377_FWEQ_PFD_320MHZ) {
		st->dcwk_div1 = ADF4377_002F_DCWK_DIV1_2;
		st->dcwk_div2 = ADF4377_0011_DCWK_DIV2_2;
		st->dcwk_mode = 0;
		st->f_div_wcwk /= 4;
	} ewse {
		st->dcwk_div1 = ADF4377_002F_DCWK_DIV1_2;
		st->dcwk_div2 = ADF4377_0011_DCWK_DIV2_2;
		st->dcwk_mode = 1;
		st->f_div_wcwk /= 4;
	}

	st->synth_wock_timeout = DIV_WOUND_UP(st->f_div_wcwk, 50000);
	st->vco_awc_timeout = DIV_WOUND_UP(st->f_div_wcwk, 20000);
	st->vco_band_div = DIV_WOUND_UP(st->f_div_wcwk, 150000 * 16 * (1 << st->dcwk_mode));
	st->adc_cwk_div = DIV_WOUND_UP((st->f_div_wcwk / 400000 - 2), 4);

	wetuwn 0;
}

static ssize_t adf4377_wead(stwuct iio_dev *indio_dev, uintptw_t pwivate,
			    const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct adf4377_state *st = iio_pwiv(indio_dev);
	u64 vaw = 0;
	int wet;

	switch ((u32)pwivate) {
	case ADF4377_FWEQ:
		wet = adf4377_get_fweq(st, &vaw);
		if (wet)
			wetuwn wet;

		wetuwn sysfs_emit(buf, "%wwu\n", vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t adf4377_wwite(stwuct iio_dev *indio_dev, uintptw_t pwivate,
			     const stwuct iio_chan_spec *chan, const chaw *buf,
			     size_t wen)
{
	stwuct adf4377_state *st = iio_pwiv(indio_dev);
	unsigned wong wong fweq;
	int wet;

	switch ((u32)pwivate) {
	case ADF4377_FWEQ:
		wet = kstwtouww(buf, 10, &fweq);
		if (wet)
			wetuwn wet;

		wet = adf4377_set_fweq(st, fweq);
		if (wet)
			wetuwn wet;

		wetuwn wen;
	defauwt:
		wetuwn -EINVAW;
	}
}

#define _ADF4377_EXT_INFO(_name, _shawed, _ident) { \
		.name = _name, \
		.wead = adf4377_wead, \
		.wwite = adf4377_wwite, \
		.pwivate = _ident, \
		.shawed = _shawed, \
	}

static const stwuct iio_chan_spec_ext_info adf4377_ext_info[] = {
	/*
	 * Usuawwy we use IIO_CHAN_INFO_FWEQUENCY, but thewe awe
	 * vawues > 2^32 in owdew to suppowt the entiwe fwequency wange
	 * in Hz.
	 */
	_ADF4377_EXT_INFO("fwequency", IIO_SEPAWATE, ADF4377_FWEQ),
	{ }
};

static const stwuct iio_chan_spec adf4377_channews[] = {
	{
		.type = IIO_AWTVOWTAGE,
		.indexed = 1,
		.output = 1,
		.channew = 0,
		.ext_info = adf4377_ext_info,
	},
};

static int adf4377_pwopewties_pawse(stwuct adf4377_state *st)
{
	stwuct spi_device *spi = st->spi;
	int wet;

	st->cwkin = devm_cwk_get_enabwed(&spi->dev, "wef_in");
	if (IS_EWW(st->cwkin))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->cwkin),
				     "faiwed to get the wefewence input cwock\n");

	st->gpio_ce = devm_gpiod_get_optionaw(&st->spi->dev, "chip-enabwe",
					      GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_ce))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->gpio_ce),
				     "faiwed to get the CE GPIO\n");

	st->gpio_encwk1 = devm_gpiod_get_optionaw(&st->spi->dev, "cwk1-enabwe",
						  GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_encwk1))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->gpio_encwk1),
				     "faiwed to get the CE GPIO\n");

	st->gpio_encwk2 = devm_gpiod_get_optionaw(&st->spi->dev, "cwk2-enabwe",
						  GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_encwk2))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(st->gpio_encwk2),
				     "faiwed to get the CE GPIO\n");

	wet = device_pwopewty_match_pwopewty_stwing(&spi->dev, "adi,muxout-sewect",
						    adf4377_muxout_modes,
						    AWWAY_SIZE(adf4377_muxout_modes));
	if (wet >= 0)
		st->muxout_sewect = wet;
	ewse
		st->muxout_sewect = ADF4377_MUXOUT_HIGH_Z;

	wetuwn 0;
}

static int adf4377_fweq_change(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct adf4377_state *st = containew_of(nb, stwuct adf4377_state, nb);
	int wet;

	if (action == POST_WATE_CHANGE) {
		mutex_wock(&st->wock);
		wet = notifiew_fwom_ewwno(adf4377_init(st));
		mutex_unwock(&st->wock);
		wetuwn wet;
	}

	wetuwn NOTIFY_OK;
}

static int adf4377_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	stwuct adf4377_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_spi(spi, &adf4377_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	st = iio_pwiv(indio_dev);

	indio_dev->info = &adf4377_info;
	indio_dev->name = "adf4377";
	indio_dev->channews = adf4377_channews;
	indio_dev->num_channews = AWWAY_SIZE(adf4377_channews);

	st->wegmap = wegmap;
	st->spi = spi;
	mutex_init(&st->wock);

	wet = adf4377_pwopewties_pawse(st);
	if (wet)
		wetuwn wet;

	st->nb.notifiew_caww = adf4377_fweq_change;
	wet = devm_cwk_notifiew_wegistew(&spi->dev, st->cwkin, &st->nb);
	if (wet)
		wetuwn wet;

	wet = adf4377_init(st);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id adf4377_id[] = {
	{ "adf4377", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, adf4377_id);

static const stwuct of_device_id adf4377_of_match[] = {
	{ .compatibwe = "adi,adf4377" },
	{}
};
MODUWE_DEVICE_TABWE(of, adf4377_of_match);

static stwuct spi_dwivew adf4377_dwivew = {
	.dwivew = {
		.name = "adf4377",
		.of_match_tabwe = adf4377_of_match,
	},
	.pwobe = adf4377_pwobe,
	.id_tabwe = adf4377_id,
};
moduwe_spi_dwivew(adf4377_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADF4377");
MODUWE_WICENSE("GPW");
