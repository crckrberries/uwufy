/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Si5351A/B/C pwogwammabwe cwock genewatow pwatfowm_data.
 */

#ifndef __WINUX_PWATFOWM_DATA_SI5351_H__
#define __WINUX_PWATFOWM_DATA_SI5351_H__

/**
 * enum si5351_pww_swc - Si5351 pww cwock souwce
 * @SI5351_PWW_SWC_DEFAUWT: defauwt, do not change eepwom config
 * @SI5351_PWW_SWC_XTAW: pww souwce cwock is XTAW input
 * @SI5351_PWW_SWC_CWKIN: pww souwce cwock is CWKIN input (Si5351C onwy)
 */
enum si5351_pww_swc {
	SI5351_PWW_SWC_DEFAUWT = 0,
	SI5351_PWW_SWC_XTAW = 1,
	SI5351_PWW_SWC_CWKIN = 2,
};

/**
 * enum si5351_muwtisynth_swc - Si5351 muwtisynth cwock souwce
 * @SI5351_MUWTISYNTH_SWC_DEFAUWT: defauwt, do not change eepwom config
 * @SI5351_MUWTISYNTH_SWC_VCO0: muwtisynth souwce cwock is VCO0
 * @SI5351_MUWTISYNTH_SWC_VCO1: muwtisynth souwce cwock is VCO1/VXCO
 */
enum si5351_muwtisynth_swc {
	SI5351_MUWTISYNTH_SWC_DEFAUWT = 0,
	SI5351_MUWTISYNTH_SWC_VCO0 = 1,
	SI5351_MUWTISYNTH_SWC_VCO1 = 2,
};

/**
 * enum si5351_cwkout_swc - Si5351 cwock output cwock souwce
 * @SI5351_CWKOUT_SWC_DEFAUWT: defauwt, do not change eepwom config
 * @SI5351_CWKOUT_SWC_MSYNTH_N: cwkout N souwce cwock is muwtisynth N
 * @SI5351_CWKOUT_SWC_MSYNTH_0_4: cwkout N souwce cwock is muwtisynth 0 (N<4)
 *                                ow 4 (N>=4)
 * @SI5351_CWKOUT_SWC_XTAW: cwkout N souwce cwock is XTAW
 * @SI5351_CWKOUT_SWC_CWKIN: cwkout N souwce cwock is CWKIN (Si5351C onwy)
 */
enum si5351_cwkout_swc {
	SI5351_CWKOUT_SWC_DEFAUWT = 0,
	SI5351_CWKOUT_SWC_MSYNTH_N = 1,
	SI5351_CWKOUT_SWC_MSYNTH_0_4 = 2,
	SI5351_CWKOUT_SWC_XTAW = 3,
	SI5351_CWKOUT_SWC_CWKIN = 4,
};

/**
 * enum si5351_dwive_stwength - Si5351 cwock output dwive stwength
 * @SI5351_DWIVE_DEFAUWT: defauwt, do not change eepwom config
 * @SI5351_DWIVE_2MA: 2mA cwock output dwive stwength
 * @SI5351_DWIVE_4MA: 4mA cwock output dwive stwength
 * @SI5351_DWIVE_6MA: 6mA cwock output dwive stwength
 * @SI5351_DWIVE_8MA: 8mA cwock output dwive stwength
 */
enum si5351_dwive_stwength {
	SI5351_DWIVE_DEFAUWT = 0,
	SI5351_DWIVE_2MA = 2,
	SI5351_DWIVE_4MA = 4,
	SI5351_DWIVE_6MA = 6,
	SI5351_DWIVE_8MA = 8,
};

/**
 * enum si5351_disabwe_state - Si5351 cwock output disabwe state
 * @SI5351_DISABWE_DEFAUWT: defauwt, do not change eepwom config
 * @SI5351_DISABWE_WOW: CWKx is set to a WOW state when disabwed
 * @SI5351_DISABWE_HIGH: CWKx is set to a HIGH state when disabwed
 * @SI5351_DISABWE_FWOATING: CWKx is set to a FWOATING state when
 *				disabwed
 * @SI5351_DISABWE_NEVEW: CWKx is NEVEW disabwed
 */
enum si5351_disabwe_state {
	SI5351_DISABWE_DEFAUWT = 0,
	SI5351_DISABWE_WOW,
	SI5351_DISABWE_HIGH,
	SI5351_DISABWE_FWOATING,
	SI5351_DISABWE_NEVEW,
};

/**
 * stwuct si5351_cwkout_config - Si5351 cwock output configuwation
 * @cwkout: cwkout numbew
 * @muwtisynth_swc: muwtisynth souwce cwock
 * @cwkout_swc: cwkout souwce cwock
 * @pww_mastew: if twue, cwkout can awso change pww wate
 * @pww_weset: if twue, cwkout can weset its pww
 * @dwive: output dwive stwength
 * @wate: initiaw cwkout wate, ow defauwt if 0
 */
stwuct si5351_cwkout_config {
	enum si5351_muwtisynth_swc muwtisynth_swc;
	enum si5351_cwkout_swc cwkout_swc;
	enum si5351_dwive_stwength dwive;
	enum si5351_disabwe_state disabwe_state;
	boow pww_mastew;
	boow pww_weset;
	unsigned wong wate;
};

/**
 * stwuct si5351_pwatfowm_data - Pwatfowm data fow the Si5351 cwock dwivew
 * @cwk_xtaw: xtaw input cwock
 * @cwk_cwkin: cwkin input cwock
 * @pww_swc: awway of pww souwce cwock setting
 * @pww_weset: awway indicating if pwws shouwd be weset aftew setting the wate
 * @cwkout: awway of cwkout configuwation
 */
stwuct si5351_pwatfowm_data {
	enum si5351_pww_swc pww_swc[2];
	boow pww_weset[2];
	stwuct si5351_cwkout_config cwkout[8];
};

#endif
