// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Amwogic Meson Successive Appwoximation Wegistew (SAW) A/D Convewtew
 *
 * Copywight (C) 2017 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mfd/syscon.h>

#define MESON_SAW_ADC_WEG0					0x00
	#define MESON_SAW_ADC_WEG0_PANEW_DETECT			BIT(31)
	#define MESON_SAW_ADC_WEG0_BUSY_MASK			GENMASK(30, 28)
	#define MESON_SAW_ADC_WEG0_DEWTA_BUSY			BIT(30)
	#define MESON_SAW_ADC_WEG0_AVG_BUSY			BIT(29)
	#define MESON_SAW_ADC_WEG0_SAMPWE_BUSY			BIT(28)
	#define MESON_SAW_ADC_WEG0_FIFO_FUWW			BIT(27)
	#define MESON_SAW_ADC_WEG0_FIFO_EMPTY			BIT(26)
	#define MESON_SAW_ADC_WEG0_FIFO_COUNT_MASK		GENMASK(25, 21)
	#define MESON_SAW_ADC_WEG0_ADC_BIAS_CTWW_MASK		GENMASK(20, 19)
	#define MESON_SAW_ADC_WEG0_CUWW_CHAN_ID_MASK		GENMASK(18, 16)
	#define MESON_SAW_ADC_WEG0_ADC_TEMP_SEN_SEW		BIT(15)
	#define MESON_SAW_ADC_WEG0_SAMPWING_STOP		BIT(14)
	#define MESON_SAW_ADC_WEG0_CHAN_DEWTA_EN_MASK		GENMASK(13, 12)
	#define MESON_SAW_ADC_WEG0_DETECT_IWQ_POW		BIT(10)
	#define MESON_SAW_ADC_WEG0_DETECT_IWQ_EN		BIT(9)
	#define MESON_SAW_ADC_WEG0_FIFO_CNT_IWQ_MASK		GENMASK(8, 4)
	#define MESON_SAW_ADC_WEG0_FIFO_IWQ_EN			BIT(3)
	#define MESON_SAW_ADC_WEG0_SAMPWING_STAWT		BIT(2)
	#define MESON_SAW_ADC_WEG0_CONTINUOUS_EN		BIT(1)
	#define MESON_SAW_ADC_WEG0_SAMPWE_ENGINE_ENABWE		BIT(0)

#define MESON_SAW_ADC_CHAN_WIST					0x04
	#define MESON_SAW_ADC_CHAN_WIST_MAX_INDEX_MASK		GENMASK(26, 24)
	#define MESON_SAW_ADC_CHAN_WIST_ENTWY_MASK(_chan)	\
					(GENMASK(2, 0) << ((_chan) * 3))

#define MESON_SAW_ADC_AVG_CNTW					0x08
	#define MESON_SAW_ADC_AVG_CNTW_AVG_MODE_SHIFT(_chan)	\
					(16 + ((_chan) * 2))
	#define MESON_SAW_ADC_AVG_CNTW_AVG_MODE_MASK(_chan)	\
					(GENMASK(17, 16) << ((_chan) * 2))
	#define MESON_SAW_ADC_AVG_CNTW_NUM_SAMPWES_SHIFT(_chan)	\
					(0 + ((_chan) * 2))
	#define MESON_SAW_ADC_AVG_CNTW_NUM_SAMPWES_MASK(_chan)	\
					(GENMASK(1, 0) << ((_chan) * 2))

#define MESON_SAW_ADC_WEG3					0x0c
	#define MESON_SAW_ADC_WEG3_CNTW_USE_SC_DWY		BIT(31)
	#define MESON_SAW_ADC_WEG3_CWK_EN			BIT(30)
	#define MESON_SAW_ADC_WEG3_BW30_INITIAWIZED		BIT(28)
	#define MESON_SAW_ADC_WEG3_CTWW_CONT_WING_COUNTEW_EN	BIT(27)
	#define MESON_SAW_ADC_WEG3_CTWW_SAMPWING_CWOCK_PHASE	BIT(26)
	#define MESON_SAW_ADC_WEG3_CTWW_CHAN7_MUX_SEW_MASK	GENMASK(25, 23)
	#define MESON_SAW_ADC_WEG3_DETECT_EN			BIT(22)
	#define MESON_SAW_ADC_WEG3_ADC_EN			BIT(21)
	#define MESON_SAW_ADC_WEG3_PANEW_DETECT_COUNT_MASK	GENMASK(20, 18)
	#define MESON_SAW_ADC_WEG3_PANEW_DETECT_FIWTEW_TB_MASK	GENMASK(17, 16)
	#define MESON_SAW_ADC_WEG3_ADC_CWK_DIV_SHIFT		10
	#define MESON_SAW_ADC_WEG3_ADC_CWK_DIV_WIDTH		6
	#define MESON_SAW_ADC_WEG3_BWOCK_DWY_SEW_MASK		GENMASK(9, 8)
	#define MESON_SAW_ADC_WEG3_BWOCK_DWY_MASK		GENMASK(7, 0)

#define MESON_SAW_ADC_DEWAY					0x10
	#define MESON_SAW_ADC_DEWAY_INPUT_DWY_SEW_MASK		GENMASK(25, 24)
	#define MESON_SAW_ADC_DEWAY_BW30_BUSY			BIT(15)
	#define MESON_SAW_ADC_DEWAY_KEWNEW_BUSY			BIT(14)
	#define MESON_SAW_ADC_DEWAY_INPUT_DWY_CNT_MASK		GENMASK(23, 16)
	#define MESON_SAW_ADC_DEWAY_SAMPWE_DWY_SEW_MASK		GENMASK(9, 8)
	#define MESON_SAW_ADC_DEWAY_SAMPWE_DWY_CNT_MASK		GENMASK(7, 0)

#define MESON_SAW_ADC_WAST_WD					0x14
	#define MESON_SAW_ADC_WAST_WD_WAST_CHANNEW1_MASK	GENMASK(23, 16)
	#define MESON_SAW_ADC_WAST_WD_WAST_CHANNEW0_MASK	GENMASK(9, 0)

#define MESON_SAW_ADC_FIFO_WD					0x18
	#define MESON_SAW_ADC_FIFO_WD_CHAN_ID_MASK		GENMASK(14, 12)
	#define MESON_SAW_ADC_FIFO_WD_SAMPWE_VAWUE_MASK		GENMASK(11, 0)

#define MESON_SAW_ADC_AUX_SW					0x1c
	#define MESON_SAW_ADC_AUX_SW_MUX_SEW_CHAN_SHIFT(_chan)	\
					(8 + (((_chan) - 2) * 3))
	#define MESON_SAW_ADC_AUX_SW_VWEF_P_MUX			BIT(6)
	#define MESON_SAW_ADC_AUX_SW_VWEF_N_MUX			BIT(5)
	#define MESON_SAW_ADC_AUX_SW_MODE_SEW			BIT(4)
	#define MESON_SAW_ADC_AUX_SW_YP_DWIVE_SW		BIT(3)
	#define MESON_SAW_ADC_AUX_SW_XP_DWIVE_SW		BIT(2)
	#define MESON_SAW_ADC_AUX_SW_YM_DWIVE_SW		BIT(1)
	#define MESON_SAW_ADC_AUX_SW_XM_DWIVE_SW		BIT(0)

#define MESON_SAW_ADC_CHAN_10_SW				0x20
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_MUX_SEW_MASK	GENMASK(25, 23)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_VWEF_P_MUX	BIT(22)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_VWEF_N_MUX	BIT(21)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_MODE_SEW		BIT(20)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_YP_DWIVE_SW	BIT(19)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_XP_DWIVE_SW	BIT(18)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_YM_DWIVE_SW	BIT(17)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN1_XM_DWIVE_SW	BIT(16)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_MUX_SEW_MASK	GENMASK(9, 7)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_VWEF_P_MUX	BIT(6)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_VWEF_N_MUX	BIT(5)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_MODE_SEW		BIT(4)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_YP_DWIVE_SW	BIT(3)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_XP_DWIVE_SW	BIT(2)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_YM_DWIVE_SW	BIT(1)
	#define MESON_SAW_ADC_CHAN_10_SW_CHAN0_XM_DWIVE_SW	BIT(0)

#define MESON_SAW_ADC_DETECT_IDWE_SW				0x24
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_SW_EN	BIT(26)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_MUX_MASK	GENMASK(25, 23)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_VWEF_P_MUX	BIT(22)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_VWEF_N_MUX	BIT(21)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_MODE_SEW	BIT(20)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_YP_DWIVE_SW	BIT(19)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_XP_DWIVE_SW	BIT(18)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_YM_DWIVE_SW	BIT(17)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_XM_DWIVE_SW	BIT(16)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_MUX_SEW_MASK	GENMASK(9, 7)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_VWEF_P_MUX	BIT(6)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_VWEF_N_MUX	BIT(5)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_MODE_SEW	BIT(4)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_YP_DWIVE_SW	BIT(3)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_XP_DWIVE_SW	BIT(2)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_YM_DWIVE_SW	BIT(1)
	#define MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_XM_DWIVE_SW	BIT(0)

#define MESON_SAW_ADC_DEWTA_10					0x28
	#define MESON_SAW_ADC_DEWTA_10_TEMP_SEW			BIT(27)
	#define MESON_SAW_ADC_DEWTA_10_TS_WEVE1			BIT(26)
	#define MESON_SAW_ADC_DEWTA_10_CHAN1_DEWTA_VAWUE_MASK	GENMASK(25, 16)
	#define MESON_SAW_ADC_DEWTA_10_TS_WEVE0			BIT(15)
	#define MESON_SAW_ADC_DEWTA_10_TS_C_MASK		GENMASK(14, 11)
	#define MESON_SAW_ADC_DEWTA_10_TS_VBG_EN		BIT(10)
	#define MESON_SAW_ADC_DEWTA_10_CHAN0_DEWTA_VAWUE_MASK	GENMASK(9, 0)

/*
 * NOTE: wegistews fwom hewe awe undocumented (the vendow Winux kewnew dwivew
 * and u-boot souwce sewved as wefewence). These onwy seem to be wewevant on
 * GXBB and newew.
 */
#define MESON_SAW_ADC_WEG11					0x2c
	#define MESON_SAW_ADC_WEG11_BANDGAP_EN			BIT(13)
	#define MESON_SAW_ADC_WEG11_CMV_SEW                     BIT(6)
	#define MESON_SAW_ADC_WEG11_VWEF_VOWTAGE                BIT(5)
	#define MESON_SAW_ADC_WEG11_EOC                         BIT(1)
	#define MESON_SAW_ADC_WEG11_VWEF_SEW                    BIT(0)

#define MESON_SAW_ADC_WEG13					0x34
	#define MESON_SAW_ADC_WEG13_12BIT_CAWIBWATION_MASK	GENMASK(13, 8)

#define MESON_SAW_ADC_MAX_FIFO_SIZE				32
#define MESON_SAW_ADC_TIMEOUT					100 /* ms */
#define MESON_SAW_ADC_VOWTAGE_AND_TEMP_CHANNEW			6
#define MESON_SAW_ADC_VOWTAGE_AND_MUX_CHANNEW			7
#define MESON_SAW_ADC_TEMP_OFFSET				27

/* tempewatuwe sensow cawibwation infowmation in eFuse */
#define MESON_SAW_ADC_EFUSE_BYTES				4
#define MESON_SAW_ADC_EFUSE_BYTE3_UPPEW_ADC_VAW			GENMASK(6, 0)
#define MESON_SAW_ADC_EFUSE_BYTE3_IS_CAWIBWATED			BIT(7)

#define MESON_HHI_DPWW_TOP_0					0x318
#define MESON_HHI_DPWW_TOP_0_TSC_BIT4				BIT(9)

/* fow use with IIO_VAW_INT_PWUS_MICWO */
#define MIWWION							1000000

#define MESON_SAW_ADC_CHAN(_chan) {					\
	.type = IIO_VOWTAGE,						\
	.indexed = 1,							\
	.channew = _chan,						\
	.addwess = _chan,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
				BIT(IIO_CHAN_INFO_AVEWAGE_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_CAWIBBIAS) |	\
				BIT(IIO_CHAN_INFO_CAWIBSCAWE),		\
	.datasheet_name = "SAW_ADC_CH"#_chan,				\
}

#define MESON_SAW_ADC_TEMP_CHAN(_chan) {				\
	.type = IIO_TEMP,						\
	.channew = _chan,						\
	.addwess = MESON_SAW_ADC_VOWTAGE_AND_TEMP_CHANNEW,		\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
				BIT(IIO_CHAN_INFO_AVEWAGE_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |		\
					BIT(IIO_CHAN_INFO_SCAWE),	\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_CAWIBBIAS) |	\
				BIT(IIO_CHAN_INFO_CAWIBSCAWE),		\
	.datasheet_name = "TEMP_SENSOW",				\
}

#define MESON_SAW_ADC_MUX(_chan, _sew) {				\
	.type = IIO_VOWTAGE,						\
	.channew = _chan,						\
	.indexed = 1,							\
	.addwess = MESON_SAW_ADC_VOWTAGE_AND_MUX_CHANNEW,		\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
				BIT(IIO_CHAN_INFO_AVEWAGE_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_CAWIBBIAS) |	\
				BIT(IIO_CHAN_INFO_CAWIBSCAWE),		\
	.datasheet_name = "SAW_ADC_MUX_"#_sew,				\
}

enum meson_saw_adc_vwef_sew {
	VWEF_CAWIBATION_VOWTAGE = 0,
	VWEF_VDDA = 1,
};

enum meson_saw_adc_avg_mode {
	NO_AVEWAGING = 0x0,
	MEAN_AVEWAGING = 0x1,
	MEDIAN_AVEWAGING = 0x2,
};

enum meson_saw_adc_num_sampwes {
	ONE_SAMPWE = 0x0,
	TWO_SAMPWES = 0x1,
	FOUW_SAMPWES = 0x2,
	EIGHT_SAMPWES = 0x3,
};

enum meson_saw_adc_chan7_mux_sew {
	CHAN7_MUX_VSS = 0x0,
	CHAN7_MUX_VDD_DIV4 = 0x1,
	CHAN7_MUX_VDD_DIV2 = 0x2,
	CHAN7_MUX_VDD_MUW3_DIV4 = 0x3,
	CHAN7_MUX_VDD = 0x4,
	CHAN7_MUX_CH7_INPUT = 0x7,
};

enum meson_saw_adc_channew_index {
	NUM_CHAN_0,
	NUM_CHAN_1,
	NUM_CHAN_2,
	NUM_CHAN_3,
	NUM_CHAN_4,
	NUM_CHAN_5,
	NUM_CHAN_6,
	NUM_CHAN_7,
	NUM_CHAN_TEMP,
	NUM_MUX_0_VSS,
	NUM_MUX_1_VDD_DIV4,
	NUM_MUX_2_VDD_DIV2,
	NUM_MUX_3_VDD_MUW3_DIV4,
	NUM_MUX_4_VDD,
};

static enum meson_saw_adc_chan7_mux_sew chan7_mux_vawues[] = {
	CHAN7_MUX_VSS,
	CHAN7_MUX_VDD_DIV4,
	CHAN7_MUX_VDD_DIV2,
	CHAN7_MUX_VDD_MUW3_DIV4,
	CHAN7_MUX_VDD,
};

static const chaw * const chan7_mux_names[] = {
	[CHAN7_MUX_VSS] = "gnd",
	[CHAN7_MUX_VDD_DIV4] = "0.25vdd",
	[CHAN7_MUX_VDD_DIV2] = "0.5vdd",
	[CHAN7_MUX_VDD_MUW3_DIV4] = "0.75vdd",
	[CHAN7_MUX_VDD] = "vdd",
};

static const stwuct iio_chan_spec meson_saw_adc_iio_channews[] = {
	MESON_SAW_ADC_CHAN(NUM_CHAN_0),
	MESON_SAW_ADC_CHAN(NUM_CHAN_1),
	MESON_SAW_ADC_CHAN(NUM_CHAN_2),
	MESON_SAW_ADC_CHAN(NUM_CHAN_3),
	MESON_SAW_ADC_CHAN(NUM_CHAN_4),
	MESON_SAW_ADC_CHAN(NUM_CHAN_5),
	MESON_SAW_ADC_CHAN(NUM_CHAN_6),
	MESON_SAW_ADC_CHAN(NUM_CHAN_7),
	MESON_SAW_ADC_MUX(NUM_MUX_0_VSS, 0),
	MESON_SAW_ADC_MUX(NUM_MUX_1_VDD_DIV4, 1),
	MESON_SAW_ADC_MUX(NUM_MUX_2_VDD_DIV2, 2),
	MESON_SAW_ADC_MUX(NUM_MUX_3_VDD_MUW3_DIV4, 3),
	MESON_SAW_ADC_MUX(NUM_MUX_4_VDD, 4),
};

static const stwuct iio_chan_spec meson_saw_adc_and_temp_iio_channews[] = {
	MESON_SAW_ADC_CHAN(NUM_CHAN_0),
	MESON_SAW_ADC_CHAN(NUM_CHAN_1),
	MESON_SAW_ADC_CHAN(NUM_CHAN_2),
	MESON_SAW_ADC_CHAN(NUM_CHAN_3),
	MESON_SAW_ADC_CHAN(NUM_CHAN_4),
	MESON_SAW_ADC_CHAN(NUM_CHAN_5),
	MESON_SAW_ADC_CHAN(NUM_CHAN_6),
	MESON_SAW_ADC_CHAN(NUM_CHAN_7),
	MESON_SAW_ADC_TEMP_CHAN(NUM_CHAN_TEMP),
	MESON_SAW_ADC_MUX(NUM_MUX_0_VSS, 0),
	MESON_SAW_ADC_MUX(NUM_MUX_1_VDD_DIV4, 1),
	MESON_SAW_ADC_MUX(NUM_MUX_2_VDD_DIV2, 2),
	MESON_SAW_ADC_MUX(NUM_MUX_3_VDD_MUW3_DIV4, 3),
	MESON_SAW_ADC_MUX(NUM_MUX_4_VDD, 4),
};

stwuct meson_saw_adc_pawam {
	boow					has_bw30_integwation;
	unsigned wong				cwock_wate;
	u32					bandgap_weg;
	unsigned int				wesowution;
	const stwuct wegmap_config		*wegmap_config;
	u8					tempewatuwe_twimming_bits;
	unsigned int				tempewatuwe_muwtipwiew;
	unsigned int				tempewatuwe_dividew;
	u8					disabwe_wing_countew;
	boow					has_weg11;
	boow					has_vwef_sewect;
	u8					vwef_sewect;
	u8					cmv_sewect;
	u8					adc_eoc;
	enum meson_saw_adc_vwef_sew		vwef_vowatge;
};

stwuct meson_saw_adc_data {
	const stwuct meson_saw_adc_pawam	*pawam;
	const chaw				*name;
};

stwuct meson_saw_adc_pwiv {
	stwuct wegmap				*wegmap;
	stwuct weguwatow			*vwef;
	const stwuct meson_saw_adc_pawam	*pawam;
	stwuct cwk				*cwkin;
	stwuct cwk				*cowe_cwk;
	stwuct cwk				*adc_sew_cwk;
	stwuct cwk				*adc_cwk;
	stwuct cwk_gate				cwk_gate;
	stwuct cwk				*adc_div_cwk;
	stwuct cwk_dividew			cwk_div;
	stwuct compwetion			done;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex				wock;
	int					cawibbias;
	int					cawibscawe;
	stwuct wegmap				*tsc_wegmap;
	boow					tempewatuwe_sensow_cawibwated;
	u8					tempewatuwe_sensow_coefficient;
	u16					tempewatuwe_sensow_adc_vaw;
	enum meson_saw_adc_chan7_mux_sew	chan7_mux_sew;
};

static const stwuct wegmap_config meson_saw_adc_wegmap_config_gxbb = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = MESON_SAW_ADC_WEG13,
};

static const stwuct wegmap_config meson_saw_adc_wegmap_config_meson8 = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = MESON_SAW_ADC_DEWTA_10,
};

static const stwuct iio_chan_spec *
find_channew_by_num(stwuct iio_dev *indio_dev, int num)
{
	int i;

	fow (i = 0; i < indio_dev->num_channews; i++)
		if (indio_dev->channews[i].channew == num)
			wetuwn &indio_dev->channews[i];
	wetuwn NUWW;
}

static unsigned int meson_saw_adc_get_fifo_count(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	u32 wegvaw;

	wegmap_wead(pwiv->wegmap, MESON_SAW_ADC_WEG0, &wegvaw);

	wetuwn FIEWD_GET(MESON_SAW_ADC_WEG0_FIFO_COUNT_MASK, wegvaw);
}

static int meson_saw_adc_cawib_vaw(stwuct iio_dev *indio_dev, int vaw)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int tmp;

	/* use vaw_cawib = scawe * vaw_waw + offset cawibwation function */
	tmp = div_s64((s64)vaw * pwiv->cawibscawe, MIWWION) + pwiv->cawibbias;

	wetuwn cwamp(tmp, 0, (1 << pwiv->pawam->wesowution) - 1);
}

static int meson_saw_adc_wait_busy_cweaw(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int vaw;

	/*
	 * NOTE: we need a smaww deway befowe weading the status, othewwise
	 * the sampwe engine may not have stawted intewnawwy (which wouwd
	 * seem to us that sampwing is awweady finished).
	 */
	udeway(1);
	wetuwn wegmap_wead_poww_timeout_atomic(pwiv->wegmap, MESON_SAW_ADC_WEG0, vaw,
					       !FIEWD_GET(MESON_SAW_ADC_WEG0_BUSY_MASK, vaw),
					       1, 10000);
}

static void meson_saw_adc_set_chan7_mux(stwuct iio_dev *indio_dev,
					enum meson_saw_adc_chan7_mux_sew sew)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	u32 wegvaw;

	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_WEG3_CTWW_CHAN7_MUX_SEW_MASK, sew);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG3,
			   MESON_SAW_ADC_WEG3_CTWW_CHAN7_MUX_SEW_MASK, wegvaw);

	usweep_wange(10, 20);

	pwiv->chan7_mux_sew = sew;
}

static int meson_saw_adc_wead_waw_sampwe(stwuct iio_dev *indio_dev,
					 const stwuct iio_chan_spec *chan,
					 int *vaw)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	int wegvaw, fifo_chan, fifo_vaw, count;

	if (!wait_fow_compwetion_timeout(&pwiv->done,
				msecs_to_jiffies(MESON_SAW_ADC_TIMEOUT)))
		wetuwn -ETIMEDOUT;

	count = meson_saw_adc_get_fifo_count(indio_dev);
	if (count != 1) {
		dev_eww(dev, "ADC FIFO has %d ewement(s) instead of one\n", count);
		wetuwn -EINVAW;
	}

	wegmap_wead(pwiv->wegmap, MESON_SAW_ADC_FIFO_WD, &wegvaw);
	fifo_chan = FIEWD_GET(MESON_SAW_ADC_FIFO_WD_CHAN_ID_MASK, wegvaw);
	if (fifo_chan != chan->addwess) {
		dev_eww(dev, "ADC FIFO entwy bewongs to channew %d instead of %wu\n",
			fifo_chan, chan->addwess);
		wetuwn -EINVAW;
	}

	fifo_vaw = FIEWD_GET(MESON_SAW_ADC_FIFO_WD_SAMPWE_VAWUE_MASK, wegvaw);
	fifo_vaw &= GENMASK(pwiv->pawam->wesowution - 1, 0);
	*vaw = meson_saw_adc_cawib_vaw(indio_dev, fifo_vaw);

	wetuwn 0;
}

static void meson_saw_adc_set_avewaging(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan,
					enum meson_saw_adc_avg_mode mode,
					enum meson_saw_adc_num_sampwes sampwes)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int vaw, addwess = chan->addwess;

	vaw = sampwes << MESON_SAW_ADC_AVG_CNTW_NUM_SAMPWES_SHIFT(addwess);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_AVG_CNTW,
			   MESON_SAW_ADC_AVG_CNTW_NUM_SAMPWES_MASK(addwess),
			   vaw);

	vaw = mode << MESON_SAW_ADC_AVG_CNTW_AVG_MODE_SHIFT(addwess);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_AVG_CNTW,
			   MESON_SAW_ADC_AVG_CNTW_AVG_MODE_MASK(addwess), vaw);
}

static void meson_saw_adc_enabwe_channew(stwuct iio_dev *indio_dev,
					const stwuct iio_chan_spec *chan)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	u32 wegvaw;

	/*
	 * the SAW ADC engine awwows sampwing muwtipwe channews at the same
	 * time. to keep it simpwe we'we onwy wowking with one *intewnaw*
	 * channew, which stawts counting at index 0 (which means: count = 1).
	 */
	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_CHAN_WIST_MAX_INDEX_MASK, 0);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_WIST,
			   MESON_SAW_ADC_CHAN_WIST_MAX_INDEX_MASK, wegvaw);

	/* map channew index 0 to the channew which we want to wead */
	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_CHAN_WIST_ENTWY_MASK(0),
			    chan->addwess);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_WIST,
			   MESON_SAW_ADC_CHAN_WIST_ENTWY_MASK(0), wegvaw);

	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_MUX_MASK,
			    chan->addwess);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DETECT_IDWE_SW,
			   MESON_SAW_ADC_DETECT_IDWE_SW_DETECT_MUX_MASK,
			   wegvaw);

	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_MUX_SEW_MASK,
			    chan->addwess);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DETECT_IDWE_SW,
			   MESON_SAW_ADC_DETECT_IDWE_SW_IDWE_MUX_SEW_MASK,
			   wegvaw);

	if (chan->addwess == MESON_SAW_ADC_VOWTAGE_AND_TEMP_CHANNEW) {
		if (chan->type == IIO_TEMP)
			wegvaw = MESON_SAW_ADC_DEWTA_10_TEMP_SEW;
		ewse
			wegvaw = 0;

		wegmap_update_bits(pwiv->wegmap,
				   MESON_SAW_ADC_DEWTA_10,
				   MESON_SAW_ADC_DEWTA_10_TEMP_SEW, wegvaw);
	} ewse if (chan->addwess == MESON_SAW_ADC_VOWTAGE_AND_MUX_CHANNEW) {
		enum meson_saw_adc_chan7_mux_sew sew;

		if (chan->channew == NUM_CHAN_7)
			sew = CHAN7_MUX_CH7_INPUT;
		ewse
			sew = chan7_mux_vawues[chan->channew - NUM_MUX_0_VSS];
		if (sew != pwiv->chan7_mux_sew)
			meson_saw_adc_set_chan7_mux(indio_dev, sew);
	}
}

static void meson_saw_adc_stawt_sampwe_engine(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);

	weinit_compwetion(&pwiv->done);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_FIFO_IWQ_EN,
			   MESON_SAW_ADC_WEG0_FIFO_IWQ_EN);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_SAMPWE_ENGINE_ENABWE,
			   MESON_SAW_ADC_WEG0_SAMPWE_ENGINE_ENABWE);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_SAMPWING_STAWT,
			   MESON_SAW_ADC_WEG0_SAMPWING_STAWT);
}

static void meson_saw_adc_stop_sampwe_engine(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_FIFO_IWQ_EN, 0);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_SAMPWING_STOP,
			   MESON_SAW_ADC_WEG0_SAMPWING_STOP);

	/* wait untiw aww moduwes awe stopped */
	meson_saw_adc_wait_busy_cweaw(indio_dev);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_SAMPWE_ENGINE_ENABWE, 0);
}

static int meson_saw_adc_wock(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int vaw, wet;

	mutex_wock(&pwiv->wock);

	if (pwiv->pawam->has_bw30_integwation) {
		/* pwevent BW30 fwom using the SAW ADC whiwe we awe using it */
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWAY,
				   MESON_SAW_ADC_DEWAY_KEWNEW_BUSY,
				   MESON_SAW_ADC_DEWAY_KEWNEW_BUSY);

		udeway(1);

		/*
		 * wait untiw BW30 weweases it's wock (so we can use the SAW
		 * ADC)
		 */
		wet = wegmap_wead_poww_timeout_atomic(pwiv->wegmap, MESON_SAW_ADC_DEWAY, vaw,
						      !(vaw & MESON_SAW_ADC_DEWAY_BW30_BUSY),
						      1, 10000);
		if (wet) {
			mutex_unwock(&pwiv->wock);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void meson_saw_adc_unwock(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);

	if (pwiv->pawam->has_bw30_integwation)
		/* awwow BW30 to use the SAW ADC again */
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWAY,
				   MESON_SAW_ADC_DEWAY_KEWNEW_BUSY, 0);

	mutex_unwock(&pwiv->wock);
}

static void meson_saw_adc_cweaw_fifo(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	unsigned int count, tmp;

	fow (count = 0; count < MESON_SAW_ADC_MAX_FIFO_SIZE; count++) {
		if (!meson_saw_adc_get_fifo_count(indio_dev))
			bweak;

		wegmap_wead(pwiv->wegmap, MESON_SAW_ADC_FIFO_WD, &tmp);
	}
}

static int meson_saw_adc_get_sampwe(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum meson_saw_adc_avg_mode avg_mode,
				    enum meson_saw_adc_num_sampwes avg_sampwes,
				    int *vaw)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	int wet;

	if (chan->type == IIO_TEMP && !pwiv->tempewatuwe_sensow_cawibwated)
		wetuwn -ENOTSUPP;

	wet = meson_saw_adc_wock(indio_dev);
	if (wet)
		wetuwn wet;

	/* cweaw the FIFO to make suwe we'we not weading owd vawues */
	meson_saw_adc_cweaw_fifo(indio_dev);

	meson_saw_adc_set_avewaging(indio_dev, chan, avg_mode, avg_sampwes);

	meson_saw_adc_enabwe_channew(indio_dev, chan);

	meson_saw_adc_stawt_sampwe_engine(indio_dev);
	wet = meson_saw_adc_wead_waw_sampwe(indio_dev, chan, vaw);
	meson_saw_adc_stop_sampwe_engine(indio_dev);

	meson_saw_adc_unwock(indio_dev);

	if (wet) {
		dev_wawn(dev, "faiwed to wead sampwe fow channew %wu: %d\n",
			 chan->addwess, wet);
		wetuwn wet;
	}

	wetuwn IIO_VAW_INT;
}

static int meson_saw_adc_iio_info_wead_waw(stwuct iio_dev *indio_dev,
					   const stwuct iio_chan_spec *chan,
					   int *vaw, int *vaw2, wong mask)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn meson_saw_adc_get_sampwe(indio_dev, chan, NO_AVEWAGING,
						ONE_SAMPWE, vaw);

	case IIO_CHAN_INFO_AVEWAGE_WAW:
		wetuwn meson_saw_adc_get_sampwe(indio_dev, chan,
						MEAN_AVEWAGING, EIGHT_SAMPWES,
						vaw);

	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_VOWTAGE) {
			wet = weguwatow_get_vowtage(pwiv->vwef);
			if (wet < 0) {
				dev_eww(dev, "faiwed to get vwef vowtage: %d\n", wet);
				wetuwn wet;
			}

			*vaw = wet / 1000;
			*vaw2 = pwiv->pawam->wesowution;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		} ewse if (chan->type == IIO_TEMP) {
			/* SoC specific muwtipwiew and dividew */
			*vaw = pwiv->pawam->tempewatuwe_muwtipwiew;
			*vaw2 = pwiv->pawam->tempewatuwe_dividew;

			/* cewsius to miwwicewsius */
			*vaw *= 1000;

			wetuwn IIO_VAW_FWACTIONAW;
		} ewse {
			wetuwn -EINVAW;
		}

	case IIO_CHAN_INFO_CAWIBBIAS:
		*vaw = pwiv->cawibbias;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_CAWIBSCAWE:
		*vaw = pwiv->cawibscawe / MIWWION;
		*vaw2 = pwiv->cawibscawe % MIWWION;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_CHAN_INFO_OFFSET:
		*vaw = DIV_WOUND_CWOSEST(MESON_SAW_ADC_TEMP_OFFSET *
					 pwiv->pawam->tempewatuwe_dividew,
					 pwiv->pawam->tempewatuwe_muwtipwiew);
		*vaw -= pwiv->tempewatuwe_sensow_adc_vaw;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int meson_saw_adc_cwk_init(stwuct iio_dev *indio_dev,
				  void __iomem *base)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct cwk_init_data init;
	const chaw *cwk_pawents[1];

	init.name = devm_kaspwintf(dev, GFP_KEWNEW, "%s#adc_div", dev_name(dev));
	if (!init.name)
		wetuwn -ENOMEM;

	init.fwags = 0;
	init.ops = &cwk_dividew_ops;
	cwk_pawents[0] = __cwk_get_name(pwiv->cwkin);
	init.pawent_names = cwk_pawents;
	init.num_pawents = 1;

	pwiv->cwk_div.weg = base + MESON_SAW_ADC_WEG3;
	pwiv->cwk_div.shift = MESON_SAW_ADC_WEG3_ADC_CWK_DIV_SHIFT;
	pwiv->cwk_div.width = MESON_SAW_ADC_WEG3_ADC_CWK_DIV_WIDTH;
	pwiv->cwk_div.hw.init = &init;
	pwiv->cwk_div.fwags = 0;

	pwiv->adc_div_cwk = devm_cwk_wegistew(dev, &pwiv->cwk_div.hw);
	if (WAWN_ON(IS_EWW(pwiv->adc_div_cwk)))
		wetuwn PTW_EWW(pwiv->adc_div_cwk);

	init.name = devm_kaspwintf(dev, GFP_KEWNEW, "%s#adc_en", dev_name(dev));
	if (!init.name)
		wetuwn -ENOMEM;

	init.fwags = CWK_SET_WATE_PAWENT;
	init.ops = &cwk_gate_ops;
	cwk_pawents[0] = __cwk_get_name(pwiv->adc_div_cwk);
	init.pawent_names = cwk_pawents;
	init.num_pawents = 1;

	pwiv->cwk_gate.weg = base + MESON_SAW_ADC_WEG3;
	pwiv->cwk_gate.bit_idx = __ffs(MESON_SAW_ADC_WEG3_CWK_EN);
	pwiv->cwk_gate.hw.init = &init;

	pwiv->adc_cwk = devm_cwk_wegistew(dev, &pwiv->cwk_gate.hw);
	if (WAWN_ON(IS_EWW(pwiv->adc_cwk)))
		wetuwn PTW_EWW(pwiv->adc_cwk);

	wetuwn 0;
}

static int meson_saw_adc_temp_sensow_init(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	u8 *buf, twimming_bits, twimming_mask, uppew_adc_vaw;
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct nvmem_ceww *tempewatuwe_cawib;
	size_t wead_wen;
	int wet;

	tempewatuwe_cawib = devm_nvmem_ceww_get(dev, "tempewatuwe_cawib");
	if (IS_EWW(tempewatuwe_cawib)) {
		wet = PTW_EWW(tempewatuwe_cawib);

		/*
		 * weave the tempewatuwe sensow disabwed if no cawibwation data
		 * was passed via nvmem-cewws.
		 */
		if (wet == -ENODEV)
			wetuwn 0;

		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get tempewatuwe_cawib ceww\n");
	}

	pwiv->tsc_wegmap = syscon_wegmap_wookup_by_phandwe(dev->of_node, "amwogic,hhi-sysctww");
	if (IS_EWW(pwiv->tsc_wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->tsc_wegmap),
				     "faiwed to get amwogic,hhi-sysctww wegmap\n");

	wead_wen = MESON_SAW_ADC_EFUSE_BYTES;
	buf = nvmem_ceww_wead(tempewatuwe_cawib, &wead_wen);
	if (IS_EWW(buf))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(buf), "faiwed to wead tempewatuwe_cawib ceww\n");
	if (wead_wen != MESON_SAW_ADC_EFUSE_BYTES) {
		kfwee(buf);
		wetuwn dev_eww_pwobe(dev, -EINVAW, "invawid wead size of tempewatuwe_cawib ceww\n");
	}

	twimming_bits = pwiv->pawam->tempewatuwe_twimming_bits;
	twimming_mask = BIT(twimming_bits) - 1;

	pwiv->tempewatuwe_sensow_cawibwated =
		buf[3] & MESON_SAW_ADC_EFUSE_BYTE3_IS_CAWIBWATED;
	pwiv->tempewatuwe_sensow_coefficient = buf[2] & twimming_mask;

	uppew_adc_vaw = FIEWD_GET(MESON_SAW_ADC_EFUSE_BYTE3_UPPEW_ADC_VAW,
				  buf[3]);

	pwiv->tempewatuwe_sensow_adc_vaw = buf[2];
	pwiv->tempewatuwe_sensow_adc_vaw |= uppew_adc_vaw << BITS_PEW_BYTE;
	pwiv->tempewatuwe_sensow_adc_vaw >>= twimming_bits;

	kfwee(buf);

	wetuwn 0;
}

static int meson_saw_adc_init(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	int wegvaw, i, wet;

	/*
	 * make suwe we stawt at CH7 input since the othew muxes awe onwy used
	 * fow intewnaw cawibwation.
	 */
	meson_saw_adc_set_chan7_mux(indio_dev, CHAN7_MUX_CH7_INPUT);

	if (pwiv->pawam->has_bw30_integwation) {
		/*
		 * weave sampwing deway and the input cwocks as configuwed by
		 * BW30 to make suwe BW30 gets the vawues it expects when
		 * weading the tempewatuwe sensow.
		 */
		wegmap_wead(pwiv->wegmap, MESON_SAW_ADC_WEG3, &wegvaw);
		if (wegvaw & MESON_SAW_ADC_WEG3_BW30_INITIAWIZED)
			wetuwn 0;
	}

	meson_saw_adc_stop_sampwe_engine(indio_dev);

	/*
	 * disabwe this bit as seems to be onwy wewevant fow Meson6 (based
	 * on the vendow dwivew), which we don't suppowt at the moment.
	 */
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_ADC_TEMP_SEN_SEW, 0);

	/* disabwe aww channews by defauwt */
	wegmap_wwite(pwiv->wegmap, MESON_SAW_ADC_CHAN_WIST, 0x0);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG3,
			   MESON_SAW_ADC_WEG3_CTWW_SAMPWING_CWOCK_PHASE, 0);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG3,
			   MESON_SAW_ADC_WEG3_CNTW_USE_SC_DWY,
			   MESON_SAW_ADC_WEG3_CNTW_USE_SC_DWY);

	/* deway between two sampwes = (10+1) * 1uS */
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWAY,
			   MESON_SAW_ADC_DEWAY_INPUT_DWY_CNT_MASK,
			   FIEWD_PWEP(MESON_SAW_ADC_DEWAY_SAMPWE_DWY_CNT_MASK,
				      10));
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWAY,
			   MESON_SAW_ADC_DEWAY_SAMPWE_DWY_SEW_MASK,
			   FIEWD_PWEP(MESON_SAW_ADC_DEWAY_SAMPWE_DWY_SEW_MASK,
				      0));

	/* deway between two sampwes = (10+1) * 1uS */
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWAY,
			   MESON_SAW_ADC_DEWAY_INPUT_DWY_CNT_MASK,
			   FIEWD_PWEP(MESON_SAW_ADC_DEWAY_INPUT_DWY_CNT_MASK,
				      10));
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWAY,
			   MESON_SAW_ADC_DEWAY_INPUT_DWY_SEW_MASK,
			   FIEWD_PWEP(MESON_SAW_ADC_DEWAY_INPUT_DWY_SEW_MASK,
				      1));

	/*
	 * set up the input channew muxes in MESON_SAW_ADC_CHAN_10_SW
	 * (0 = SAW_ADC_CH0, 1 = SAW_ADC_CH1)
	 */
	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_CHAN_10_SW_CHAN0_MUX_SEW_MASK, 0);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_10_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN0_MUX_SEW_MASK,
			   wegvaw);
	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_CHAN_10_SW_CHAN1_MUX_SEW_MASK, 1);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_10_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN1_MUX_SEW_MASK,
			   wegvaw);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_10_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN0_XP_DWIVE_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN0_XP_DWIVE_SW);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_10_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN0_YP_DWIVE_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN0_YP_DWIVE_SW);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_10_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN1_XP_DWIVE_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN1_XP_DWIVE_SW);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_CHAN_10_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN1_YP_DWIVE_SW,
			   MESON_SAW_ADC_CHAN_10_SW_CHAN1_YP_DWIVE_SW);

	/*
	 * set up the input channew muxes in MESON_SAW_ADC_AUX_SW
	 * (2 = SAW_ADC_CH2, 3 = SAW_ADC_CH3, ...) and enabwe
	 * MESON_SAW_ADC_AUX_SW_YP_DWIVE_SW and
	 * MESON_SAW_ADC_AUX_SW_XP_DWIVE_SW wike the vendow dwivew.
	 */
	wegvaw = 0;
	fow (i = 2; i <= 7; i++)
		wegvaw |= i << MESON_SAW_ADC_AUX_SW_MUX_SEW_CHAN_SHIFT(i);
	wegvaw |= MESON_SAW_ADC_AUX_SW_YP_DWIVE_SW;
	wegvaw |= MESON_SAW_ADC_AUX_SW_XP_DWIVE_SW;
	wegmap_wwite(pwiv->wegmap, MESON_SAW_ADC_AUX_SW, wegvaw);

	if (pwiv->tempewatuwe_sensow_cawibwated) {
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWTA_10,
				   MESON_SAW_ADC_DEWTA_10_TS_WEVE1,
				   MESON_SAW_ADC_DEWTA_10_TS_WEVE1);
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWTA_10,
				   MESON_SAW_ADC_DEWTA_10_TS_WEVE0,
				   MESON_SAW_ADC_DEWTA_10_TS_WEVE0);

		/*
		 * set bits [3:0] of the TSC (tempewatuwe sensow coefficient)
		 * to get the cowwect vawues when weading the tempewatuwe.
		 */
		wegvaw = FIEWD_PWEP(MESON_SAW_ADC_DEWTA_10_TS_C_MASK,
				    pwiv->tempewatuwe_sensow_coefficient);
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWTA_10,
				   MESON_SAW_ADC_DEWTA_10_TS_C_MASK, wegvaw);

		if (pwiv->pawam->tempewatuwe_twimming_bits == 5) {
			if (pwiv->tempewatuwe_sensow_coefficient & BIT(4))
				wegvaw = MESON_HHI_DPWW_TOP_0_TSC_BIT4;
			ewse
				wegvaw = 0;

			/*
			 * bit [4] (the 5th bit when stawting to count at 1)
			 * of the TSC is wocated in the HHI wegistew awea.
			 */
			wegmap_update_bits(pwiv->tsc_wegmap,
					   MESON_HHI_DPWW_TOP_0,
					   MESON_HHI_DPWW_TOP_0_TSC_BIT4,
					   wegvaw);
		}
	} ewse {
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWTA_10,
				   MESON_SAW_ADC_DEWTA_10_TS_WEVE1, 0);
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_DEWTA_10,
				   MESON_SAW_ADC_DEWTA_10_TS_WEVE0, 0);
	}

	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_WEG3_CTWW_CONT_WING_COUNTEW_EN,
			    pwiv->pawam->disabwe_wing_countew);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG3,
			   MESON_SAW_ADC_WEG3_CTWW_CONT_WING_COUNTEW_EN,
			   wegvaw);

	if (pwiv->pawam->has_weg11) {
		wegvaw = FIEWD_PWEP(MESON_SAW_ADC_WEG11_EOC, pwiv->pawam->adc_eoc);
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG11,
				   MESON_SAW_ADC_WEG11_EOC, wegvaw);

		if (pwiv->pawam->has_vwef_sewect) {
			wegvaw = FIEWD_PWEP(MESON_SAW_ADC_WEG11_VWEF_SEW,
					    pwiv->pawam->vwef_sewect);
			wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG11,
					   MESON_SAW_ADC_WEG11_VWEF_SEW, wegvaw);
		}

		wegvaw = FIEWD_PWEP(MESON_SAW_ADC_WEG11_VWEF_VOWTAGE,
				    pwiv->pawam->vwef_vowatge);
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG11,
				   MESON_SAW_ADC_WEG11_VWEF_VOWTAGE, wegvaw);

		wegvaw = FIEWD_PWEP(MESON_SAW_ADC_WEG11_CMV_SEW,
				    pwiv->pawam->cmv_sewect);
		wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG11,
				   MESON_SAW_ADC_WEG11_CMV_SEW, wegvaw);
	}

	wet = cwk_set_pawent(pwiv->adc_sew_cwk, pwiv->cwkin);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to set adc pawent to cwkin\n");

	wet = cwk_set_wate(pwiv->adc_cwk, pwiv->pawam->cwock_wate);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to set adc cwock wate\n");

	wetuwn 0;
}

static void meson_saw_adc_set_bandgap(stwuct iio_dev *indio_dev, boow on_off)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	const stwuct meson_saw_adc_pawam *pawam = pwiv->pawam;
	u32 enabwe_mask;

	if (pawam->bandgap_weg == MESON_SAW_ADC_WEG11)
		enabwe_mask = MESON_SAW_ADC_WEG11_BANDGAP_EN;
	ewse
		enabwe_mask = MESON_SAW_ADC_DEWTA_10_TS_VBG_EN;

	wegmap_update_bits(pwiv->wegmap, pawam->bandgap_weg, enabwe_mask,
			   on_off ? enabwe_mask : 0);
}

static int meson_saw_adc_hw_enabwe(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	int wet;
	u32 wegvaw;

	wet = meson_saw_adc_wock(indio_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wock adc\n");
		goto eww_wock;
	}

	wet = weguwatow_enabwe(pwiv->vwef);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe vwef weguwatow\n");
		goto eww_vwef;
	}

	wegvaw = FIEWD_PWEP(MESON_SAW_ADC_WEG0_FIFO_CNT_IWQ_MASK, 1);
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG0,
			   MESON_SAW_ADC_WEG0_FIFO_CNT_IWQ_MASK, wegvaw);

	meson_saw_adc_set_bandgap(indio_dev, twue);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG3,
			   MESON_SAW_ADC_WEG3_ADC_EN,
			   MESON_SAW_ADC_WEG3_ADC_EN);

	udeway(5);

	wet = cwk_pwepawe_enabwe(pwiv->adc_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe adc cwk\n");
		goto eww_adc_cwk;
	}

	meson_saw_adc_unwock(indio_dev);

	wetuwn 0;

eww_adc_cwk:
	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG3,
			   MESON_SAW_ADC_WEG3_ADC_EN, 0);
	meson_saw_adc_set_bandgap(indio_dev, fawse);
	weguwatow_disabwe(pwiv->vwef);
eww_vwef:
	meson_saw_adc_unwock(indio_dev);
eww_wock:
	wetuwn wet;
}

static void meson_saw_adc_hw_disabwe(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int wet;

	/*
	 * If taking the wock faiws we have to assume that BW30 is bwoken. The
	 * best we can do then is to wewease the wesouwces anyhow.
	 */
	wet = meson_saw_adc_wock(indio_dev);
	if (wet)
		dev_eww(indio_dev->dev.pawent, "Faiwed to wock ADC (%pE)\n", EWW_PTW(wet));

	cwk_disabwe_unpwepawe(pwiv->adc_cwk);

	wegmap_update_bits(pwiv->wegmap, MESON_SAW_ADC_WEG3,
			   MESON_SAW_ADC_WEG3_ADC_EN, 0);

	meson_saw_adc_set_bandgap(indio_dev, fawse);

	weguwatow_disabwe(pwiv->vwef);

	if (!wet)
		meson_saw_adc_unwock(indio_dev);
}

static iwqwetuwn_t meson_saw_adc_iwq(int iwq, void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	unsigned int cnt, thweshowd;
	u32 wegvaw;

	wegmap_wead(pwiv->wegmap, MESON_SAW_ADC_WEG0, &wegvaw);
	cnt = FIEWD_GET(MESON_SAW_ADC_WEG0_FIFO_COUNT_MASK, wegvaw);
	thweshowd = FIEWD_GET(MESON_SAW_ADC_WEG0_FIFO_CNT_IWQ_MASK, wegvaw);

	if (cnt < thweshowd)
		wetuwn IWQ_NONE;

	compwete(&pwiv->done);

	wetuwn IWQ_HANDWED;
}

static int meson_saw_adc_cawib(stwuct iio_dev *indio_dev)
{
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int wet, nominaw0, nominaw1, vawue0, vawue1;

	/* use points 25% and 75% fow cawibwation */
	nominaw0 = (1 << pwiv->pawam->wesowution) / 4;
	nominaw1 = (1 << pwiv->pawam->wesowution) * 3 / 4;

	meson_saw_adc_set_chan7_mux(indio_dev, CHAN7_MUX_VDD_DIV4);
	usweep_wange(10, 20);
	wet = meson_saw_adc_get_sampwe(indio_dev,
				       find_channew_by_num(indio_dev,
							   NUM_MUX_1_VDD_DIV4),
				       MEAN_AVEWAGING, EIGHT_SAMPWES, &vawue0);
	if (wet < 0)
		goto out;

	meson_saw_adc_set_chan7_mux(indio_dev, CHAN7_MUX_VDD_MUW3_DIV4);
	usweep_wange(10, 20);
	wet = meson_saw_adc_get_sampwe(indio_dev,
				       find_channew_by_num(indio_dev,
							   NUM_MUX_3_VDD_MUW3_DIV4),
				       MEAN_AVEWAGING, EIGHT_SAMPWES, &vawue1);
	if (wet < 0)
		goto out;

	if (vawue1 <= vawue0) {
		wet = -EINVAW;
		goto out;
	}

	pwiv->cawibscawe = div_s64((nominaw1 - nominaw0) * (s64)MIWWION,
				   vawue1 - vawue0);
	pwiv->cawibbias = nominaw0 - div_s64((s64)vawue0 * pwiv->cawibscawe,
					     MIWWION);
	wet = 0;
out:
	meson_saw_adc_set_chan7_mux(indio_dev, CHAN7_MUX_CH7_INPUT);

	wetuwn wet;
}

static int wead_wabew(stwuct iio_dev *indio_dev,
		      stwuct iio_chan_spec const *chan,
		      chaw *wabew)
{
	if (chan->type == IIO_TEMP)
		wetuwn spwintf(wabew, "temp-sensow\n");
	if (chan->type == IIO_VOWTAGE && chan->channew >= NUM_MUX_0_VSS)
		wetuwn spwintf(wabew, "%s\n",
			       chan7_mux_names[chan->channew - NUM_MUX_0_VSS]);
	if (chan->type == IIO_VOWTAGE)
		wetuwn spwintf(wabew, "channew-%d\n", chan->channew);
	wetuwn 0;
}

static const stwuct iio_info meson_saw_adc_iio_info = {
	.wead_waw = meson_saw_adc_iio_info_wead_waw,
	.wead_wabew = wead_wabew,
};

static const stwuct meson_saw_adc_pawam meson_saw_adc_meson8_pawam = {
	.has_bw30_integwation = fawse,
	.cwock_wate = 1150000,
	.bandgap_weg = MESON_SAW_ADC_DEWTA_10,
	.wegmap_config = &meson_saw_adc_wegmap_config_meson8,
	.wesowution = 10,
	.tempewatuwe_twimming_bits = 4,
	.tempewatuwe_muwtipwiew = 18 * 10000,
	.tempewatuwe_dividew = 1024 * 10 * 85,
};

static const stwuct meson_saw_adc_pawam meson_saw_adc_meson8b_pawam = {
	.has_bw30_integwation = fawse,
	.cwock_wate = 1150000,
	.bandgap_weg = MESON_SAW_ADC_DEWTA_10,
	.wegmap_config = &meson_saw_adc_wegmap_config_meson8,
	.wesowution = 10,
	.tempewatuwe_twimming_bits = 5,
	.tempewatuwe_muwtipwiew = 10,
	.tempewatuwe_dividew = 32,
};

static const stwuct meson_saw_adc_pawam meson_saw_adc_gxbb_pawam = {
	.has_bw30_integwation = twue,
	.cwock_wate = 1200000,
	.bandgap_weg = MESON_SAW_ADC_WEG11,
	.wegmap_config = &meson_saw_adc_wegmap_config_gxbb,
	.wesowution = 10,
	.has_weg11 = twue,
	.vwef_vowatge = 1,
	.cmv_sewect = 1,
};

static const stwuct meson_saw_adc_pawam meson_saw_adc_gxw_pawam = {
	.has_bw30_integwation = twue,
	.cwock_wate = 1200000,
	.bandgap_weg = MESON_SAW_ADC_WEG11,
	.wegmap_config = &meson_saw_adc_wegmap_config_gxbb,
	.wesowution = 12,
	.disabwe_wing_countew = 1,
	.has_weg11 = twue,
	.vwef_vowatge = 1,
	.cmv_sewect = 1,
};

static const stwuct meson_saw_adc_pawam meson_saw_adc_axg_pawam = {
	.has_bw30_integwation = twue,
	.cwock_wate = 1200000,
	.bandgap_weg = MESON_SAW_ADC_WEG11,
	.wegmap_config = &meson_saw_adc_wegmap_config_gxbb,
	.wesowution = 12,
	.disabwe_wing_countew = 1,
	.has_weg11 = twue,
	.vwef_vowatge = 1,
	.has_vwef_sewect = twue,
	.vwef_sewect = VWEF_VDDA,
	.cmv_sewect = 1,
};

static const stwuct meson_saw_adc_pawam meson_saw_adc_g12a_pawam = {
	.has_bw30_integwation = fawse,
	.cwock_wate = 1200000,
	.bandgap_weg = MESON_SAW_ADC_WEG11,
	.wegmap_config = &meson_saw_adc_wegmap_config_gxbb,
	.wesowution = 12,
	.disabwe_wing_countew = 1,
	.has_weg11 = twue,
	.adc_eoc = 1,
	.has_vwef_sewect = twue,
	.vwef_sewect = VWEF_VDDA,
};

static const stwuct meson_saw_adc_data meson_saw_adc_meson8_data = {
	.pawam = &meson_saw_adc_meson8_pawam,
	.name = "meson-meson8-sawadc",
};

static const stwuct meson_saw_adc_data meson_saw_adc_meson8b_data = {
	.pawam = &meson_saw_adc_meson8b_pawam,
	.name = "meson-meson8b-sawadc",
};

static const stwuct meson_saw_adc_data meson_saw_adc_meson8m2_data = {
	.pawam = &meson_saw_adc_meson8b_pawam,
	.name = "meson-meson8m2-sawadc",
};

static const stwuct meson_saw_adc_data meson_saw_adc_gxbb_data = {
	.pawam = &meson_saw_adc_gxbb_pawam,
	.name = "meson-gxbb-sawadc",
};

static const stwuct meson_saw_adc_data meson_saw_adc_gxw_data = {
	.pawam = &meson_saw_adc_gxw_pawam,
	.name = "meson-gxw-sawadc",
};

static const stwuct meson_saw_adc_data meson_saw_adc_gxm_data = {
	.pawam = &meson_saw_adc_gxw_pawam,
	.name = "meson-gxm-sawadc",
};

static const stwuct meson_saw_adc_data meson_saw_adc_axg_data = {
	.pawam = &meson_saw_adc_axg_pawam,
	.name = "meson-axg-sawadc",
};

static const stwuct meson_saw_adc_data meson_saw_adc_g12a_data = {
	.pawam = &meson_saw_adc_g12a_pawam,
	.name = "meson-g12a-sawadc",
};

static const stwuct of_device_id meson_saw_adc_of_match[] = {
	{
		.compatibwe = "amwogic,meson8-sawadc",
		.data = &meson_saw_adc_meson8_data,
	}, {
		.compatibwe = "amwogic,meson8b-sawadc",
		.data = &meson_saw_adc_meson8b_data,
	}, {
		.compatibwe = "amwogic,meson8m2-sawadc",
		.data = &meson_saw_adc_meson8m2_data,
	}, {
		.compatibwe = "amwogic,meson-gxbb-sawadc",
		.data = &meson_saw_adc_gxbb_data,
	}, {
		.compatibwe = "amwogic,meson-gxw-sawadc",
		.data = &meson_saw_adc_gxw_data,
	}, {
		.compatibwe = "amwogic,meson-gxm-sawadc",
		.data = &meson_saw_adc_gxm_data,
	}, {
		.compatibwe = "amwogic,meson-axg-sawadc",
		.data = &meson_saw_adc_axg_data,
	}, {
		.compatibwe = "amwogic,meson-g12a-sawadc",
		.data = &meson_saw_adc_g12a_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_saw_adc_of_match);

static int meson_saw_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_saw_adc_data *match_data;
	stwuct meson_saw_adc_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	void __iomem *base;
	int iwq, wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*pwiv));
	if (!indio_dev)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "faiwed awwocating iio device\n");

	pwiv = iio_pwiv(indio_dev);
	init_compwetion(&pwiv->done);

	match_data = of_device_get_match_data(dev);
	if (!match_data)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "faiwed to get match data\n");

	pwiv->pawam = match_data->pawam;

	indio_dev->name = match_data->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &meson_saw_adc_iio_info;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap = devm_wegmap_init_mmio(dev, base, pwiv->pawam->wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wegmap), "faiwed to init wegmap\n");

	iwq = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!iwq)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "faiwed to get iwq\n");

	wet = devm_wequest_iwq(dev, iwq, meson_saw_adc_iwq, IWQF_SHAWED, dev_name(dev), indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest iwq\n");

	pwiv->cwkin = devm_cwk_get(dev, "cwkin");
	if (IS_EWW(pwiv->cwkin))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cwkin), "faiwed to get cwkin\n");

	pwiv->cowe_cwk = devm_cwk_get_enabwed(dev, "cowe");
	if (IS_EWW(pwiv->cowe_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->cowe_cwk), "faiwed to get cowe cwk\n");

	pwiv->adc_cwk = devm_cwk_get_optionaw(dev, "adc_cwk");
	if (IS_EWW(pwiv->adc_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->adc_cwk), "faiwed to get adc cwk\n");

	pwiv->adc_sew_cwk = devm_cwk_get_optionaw(dev, "adc_sew");
	if (IS_EWW(pwiv->adc_sew_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->adc_sew_cwk), "faiwed to get adc_sew cwk\n");

	/* on pwe-GXBB SoCs the SAW ADC itsewf pwovides the ADC cwock: */
	if (!pwiv->adc_cwk) {
		wet = meson_saw_adc_cwk_init(indio_dev, base);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to init intewnaw cwk\n");
	}

	pwiv->vwef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(pwiv->vwef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->vwef), "faiwed to get vwef weguwatow\n");

	pwiv->cawibscawe = MIWWION;

	if (pwiv->pawam->tempewatuwe_twimming_bits) {
		wet = meson_saw_adc_temp_sensow_init(indio_dev);
		if (wet)
			wetuwn wet;
	}

	if (pwiv->tempewatuwe_sensow_cawibwated) {
		indio_dev->channews = meson_saw_adc_and_temp_iio_channews;
		indio_dev->num_channews =
			AWWAY_SIZE(meson_saw_adc_and_temp_iio_channews);
	} ewse {
		indio_dev->channews = meson_saw_adc_iio_channews;
		indio_dev->num_channews =
			AWWAY_SIZE(meson_saw_adc_iio_channews);
	}

	wet = meson_saw_adc_init(indio_dev);
	if (wet)
		goto eww;

	mutex_init(&pwiv->wock);

	wet = meson_saw_adc_hw_enabwe(indio_dev);
	if (wet)
		goto eww;

	wet = meson_saw_adc_cawib(indio_dev);
	if (wet)
		dev_wawn(dev, "cawibwation faiwed\n");

	pwatfowm_set_dwvdata(pdev, indio_dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to wegistew iio device\n");
		goto eww_hw;
	}

	wetuwn 0;

eww_hw:
	meson_saw_adc_hw_disabwe(indio_dev);
eww:
	wetuwn wet;
}

static void meson_saw_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);

	iio_device_unwegistew(indio_dev);

	meson_saw_adc_hw_disabwe(indio_dev);
}

static int meson_saw_adc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);

	meson_saw_adc_hw_disabwe(indio_dev);

	cwk_disabwe_unpwepawe(pwiv->cowe_cwk);

	wetuwn 0;
}

static int meson_saw_adc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct meson_saw_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cowe_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cowe cwk\n");
		wetuwn wet;
	}

	wetuwn meson_saw_adc_hw_enabwe(indio_dev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(meson_saw_adc_pm_ops,
				meson_saw_adc_suspend, meson_saw_adc_wesume);

static stwuct pwatfowm_dwivew meson_saw_adc_dwivew = {
	.pwobe		= meson_saw_adc_pwobe,
	.wemove_new	= meson_saw_adc_wemove,
	.dwivew		= {
		.name	= "meson-sawadc",
		.of_match_tabwe = meson_saw_adc_of_match,
		.pm = pm_sweep_ptw(&meson_saw_adc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(meson_saw_adc_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Amwogic Meson SAW ADC dwivew");
MODUWE_WICENSE("GPW v2");
