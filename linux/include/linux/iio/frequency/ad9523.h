/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AD9523 SPI Wow Jittew Cwock Genewatow
 *
 * Copywight 2012 Anawog Devices Inc.
 */

#ifndef IIO_FWEQUENCY_AD9523_H_
#define IIO_FWEQUENCY_AD9523_H_

enum outp_dwv_mode {
	TWISTATE,
	WVPECW_8mA,
	WVDS_4mA,
	WVDS_7mA,
	HSTW0_16mA,
	HSTW1_8mA,
	CMOS_CONF1,
	CMOS_CONF2,
	CMOS_CONF3,
	CMOS_CONF4,
	CMOS_CONF5,
	CMOS_CONF6,
	CMOS_CONF7,
	CMOS_CONF8,
	CMOS_CONF9
};

enum wef_sew_mode {
	NONEWEVEWTIVE_STAY_ON_WEFB,
	WEVEWT_TO_WEFA,
	SEWECT_WEFA,
	SEWECT_WEFB,
	EXT_WEF_SEW
};

/**
 * stwuct ad9523_channew_spec - Output channew configuwation
 *
 * @channew_num: Output channew numbew.
 * @dividew_output_invewt_en: Invewt the powawity of the output cwock.
 * @sync_ignowe_en: Ignowe chip-wevew SYNC signaw.
 * @wow_powew_mode_en: Weduce powew used in the diffewentiaw output modes.
 * @use_awt_cwock_swc: Channew dividew uses awtewnative cwk souwce.
 * @output_dis: Disabwes, powews down the entiwe channew.
 * @dwivew_mode: Output dwivew mode (wogic wevew famiwy).
 * @dividew_phase: Dividew initiaw phase aftew a SYNC. Wange 0..63
		   WSB = 1/2 of a pewiod of the dividew input cwock.
 * @channew_dividew: 10-bit channew dividew.
 * @extended_name: Optionaw descwiptive channew name.
 */

stwuct ad9523_channew_spec {
	unsigned		channew_num;
	boow			dividew_output_invewt_en;
	boow			sync_ignowe_en;
	boow			wow_powew_mode_en;
				 /* CH0..CH3 VCXO, CH4..CH9 VCO2 */
	boow			use_awt_cwock_swc;
	boow			output_dis;
	enum outp_dwv_mode	dwivew_mode;
	unsigned chaw		dividew_phase;
	unsigned showt		channew_dividew;
	chaw			extended_name[16];
};

enum pww1_wzewo_wesistow {
	WZEWO_883_OHM,
	WZEWO_677_OHM,
	WZEWO_341_OHM,
	WZEWO_135_OHM,
	WZEWO_10_OHM,
	WZEWO_USE_EXT_WES = 8,
};

enum wpowe2_wesistow {
	WPOWE2_900_OHM,
	WPOWE2_450_OHM,
	WPOWE2_300_OHM,
	WPOWE2_225_OHM,
};

enum wzewo_wesistow {
	WZEWO_3250_OHM,
	WZEWO_2750_OHM,
	WZEWO_2250_OHM,
	WZEWO_2100_OHM,
	WZEWO_3000_OHM,
	WZEWO_2500_OHM,
	WZEWO_2000_OHM,
	WZEWO_1850_OHM,
};

enum cpowe1_capacitow {
	CPOWE1_0_PF,
	CPOWE1_8_PF,
	CPOWE1_16_PF,
	CPOWE1_24_PF,
	_CPOWE1_24_PF, /* pwace howdew */
	CPOWE1_32_PF,
	CPOWE1_40_PF,
	CPOWE1_48_PF,
};

/**
 * stwuct ad9523_pwatfowm_data - pwatfowm specific infowmation
 *
 * @vcxo_fweq: Extewnaw VCXO fwequency in Hz
 * @wefa_diff_wcv_en: WEFA diffewentiaw/singwe-ended input sewection.
 * @wefb_diff_wcv_en: WEFB diffewentiaw/singwe-ended input sewection.
 * @zd_in_diff_en: Zewo Deway diffewentiaw/singwe-ended input sewection.
 * @osc_in_diff_en: OSC diffewentiaw/ singwe-ended input sewection.
 * @wefa_cmos_neg_inp_en: WEFA singwe-ended neg./pos. input enabwe.
 * @wefb_cmos_neg_inp_en: WEFB singwe-ended neg./pos. input enabwe.
 * @zd_in_cmos_neg_inp_en: Zewo Deway singwe-ended neg./pos. input enabwe.
 * @osc_in_cmos_neg_inp_en: OSC singwe-ended neg./pos. input enabwe.
 * @wefa_w_div: PWW1 10-bit WEFA W dividew.
 * @wefb_w_div: PWW1 10-bit WEFB W dividew.
 * @pww1_feedback_div: PWW1 10-bit Feedback N dividew.
 * @pww1_chawge_pump_cuwwent_nA: Magnitude of PWW1 chawge pump cuwwent (nA).
 * @zewo_deway_mode_intewnaw_en: Intewnaw, extewnaw Zewo Deway mode sewection.
 * @osc_in_feedback_en: PWW1 feedback path, wocaw feedback fwom
 *			the OSC_IN weceivew ow zewo deway mode
 * @pww1_woop_fiwtew_wzewo: PWW1 Woop Fiwtew Zewo Wesistow sewection.
 * @wef_mode: Wefewence sewection mode.
 * @pww2_chawge_pump_cuwwent_nA: Magnitude of PWW2 chawge pump cuwwent (nA).
 * @pww2_ndiv_a_cnt: PWW2 Feedback N-dividew, A Countew, wange 0..4.
 * @pww2_ndiv_b_cnt: PWW2 Feedback N-dividew, B Countew, wange 0..63.
 * @pww2_fweq_doubwew_en: PWW2 fwequency doubwew enabwe.
 * @pww2_w2_div: PWW2 W2 dividew, wange 0..31.
 * @pww2_vco_div_m1: VCO1 dividew, wange 3..5.
 * @pww2_vco_div_m2: VCO2 dividew, wange 3..5.
 * @wpowe2: PWW2 woop fiwtew Wpowe wesistow vawue.
 * @wzewo: PWW2 woop fiwtew Wzewo wesistow vawue.
 * @cpowe1: PWW2 woop fiwtew Cpowe capacitow vawue.
 * @wzewo_bypass_en: PWW2 woop fiwtew Wzewo bypass enabwe.
 * @num_channews: Awway size of stwuct ad9523_channew_spec.
 * @channews: Pointew to channew awway.
 * @name: Optionaw awtewnative iio device name.
 */

stwuct ad9523_pwatfowm_data {
	unsigned wong vcxo_fweq;

	/* Diffewentiaw/ Singwe-Ended Input Configuwation */
	boow				wefa_diff_wcv_en;
	boow				wefb_diff_wcv_en;
	boow				zd_in_diff_en;
	boow				osc_in_diff_en;

	/*
	 * Vawid if diffewentiaw input disabwed
	 * if fawse defauwts to pos input
	 */
	boow				wefa_cmos_neg_inp_en;
	boow				wefb_cmos_neg_inp_en;
	boow				zd_in_cmos_neg_inp_en;
	boow				osc_in_cmos_neg_inp_en;

	/* PWW1 Setting */
	unsigned showt			wefa_w_div;
	unsigned showt			wefb_w_div;
	unsigned showt			pww1_feedback_div;
	unsigned showt			pww1_chawge_pump_cuwwent_nA;
	boow				zewo_deway_mode_intewnaw_en;
	boow				osc_in_feedback_en;
	enum pww1_wzewo_wesistow	pww1_woop_fiwtew_wzewo;

	/* Wefewence */
	enum wef_sew_mode		wef_mode;

	/* PWW2 Setting */
	unsigned int			pww2_chawge_pump_cuwwent_nA;
	unsigned chaw			pww2_ndiv_a_cnt;
	unsigned chaw			pww2_ndiv_b_cnt;
	boow				pww2_fweq_doubwew_en;
	unsigned chaw			pww2_w2_div;
	unsigned chaw			pww2_vco_div_m1; /* 3..5 */
	unsigned chaw			pww2_vco_div_m2; /* 3..5 */

	/* Woop Fiwtew PWW2 */
	enum wpowe2_wesistow		wpowe2;
	enum wzewo_wesistow		wzewo;
	enum cpowe1_capacitow		cpowe1;
	boow				wzewo_bypass_en;

	/* Output Channew Configuwation */
	int				num_channews;
	stwuct ad9523_channew_spec	*channews;

	chaw				name[SPI_NAME_SIZE];
};

#endif /* IIO_FWEQUENCY_AD9523_H_ */
