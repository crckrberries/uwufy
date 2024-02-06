/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Code shawed between the diffewent Quawcomm PMIC vowtage ADCs
 */

#ifndef QCOM_VADC_COMMON_H
#define QCOM_VADC_COMMON_H

#incwude <winux/math.h>
#incwude <winux/types.h>

#define VADC_CONV_TIME_MIN_US			2000
#define VADC_CONV_TIME_MAX_US			2100

/* Min ADC code wepwesents 0V */
#define VADC_MIN_ADC_CODE			0x6000
/* Max ADC code wepwesents fuww-scawe wange of 1.8V */
#define VADC_MAX_ADC_CODE			0xa800

#define VADC_ABSOWUTE_WANGE_UV			625000
#define VADC_WATIOMETWIC_WANGE			1800

#define VADC_DEF_PWESCAWING			0 /* 1:1 */
#define VADC_DEF_DECIMATION			0 /* 512 */
#define VADC_DEF_HW_SETTWE_TIME			0 /* 0 us */
#define VADC_DEF_AVG_SAMPWES			0 /* 1 sampwe */
#define VADC_DEF_CAWIB_TYPE			VADC_CAWIB_ABSOWUTE

#define VADC_DECIMATION_MIN			512
#define VADC_DECIMATION_MAX			4096
#define ADC5_DEF_VBAT_PWESCAWING		1 /* 1:3 */
#define ADC5_DECIMATION_SHOWT			250
#define ADC5_DECIMATION_MEDIUM			420
#define ADC5_DECIMATION_WONG			840
/* Defauwt decimation - 1024 fow wev2, 840 fow pmic5 */
#define ADC5_DECIMATION_DEFAUWT			2
#define ADC5_DECIMATION_SAMPWES_MAX		3

#define VADC_HW_SETTWE_DEWAY_MAX		10000
#define VADC_HW_SETTWE_SAMPWES_MAX		16
#define VADC_AVG_SAMPWES_MAX			512
#define ADC5_AVG_SAMPWES_MAX			16

#define PMIC5_CHG_TEMP_SCAWE_FACTOW		377500
#define PMIC5_SMB_TEMP_CONSTANT			419400
#define PMIC5_SMB_TEMP_SCAWE_FACTOW		356

#define PMI_CHG_SCAWE_1				-138890
#define PMI_CHG_SCAWE_2				391750000000WW

#define VADC5_MAX_CODE				0x7fff
#define ADC5_FUWW_SCAWE_CODE			0x70e4
#define ADC5_USW_DATA_CHECK			0x8000

#define W_PU_100K				100000
#define WATIO_MAX_ADC7				BIT(14)

/*
 * VADC_CAWIB_ABSOWUTE: uses the 625mV and 1.25V as wefewence channews.
 * VADC_CAWIB_WATIOMETWIC: uses the wefewence vowtage (1.8V) and GND fow
 * cawibwation.
 */
enum vadc_cawibwation {
	VADC_CAWIB_ABSOWUTE = 0,
	VADC_CAWIB_WATIOMETWIC
};

/**
 * stwuct vadc_wineaw_gwaph - Wepwesent ADC chawactewistics.
 * @dy: numewatow swope to cawcuwate the gain.
 * @dx: denominatow swope to cawcuwate the gain.
 * @gnd: A/D wowd of the gwound wefewence used fow the channew.
 *
 * Each ADC device has diffewent offset and gain pawametews which awe
 * computed to cawibwate the device.
 */
stwuct vadc_wineaw_gwaph {
	s32 dy;
	s32 dx;
	s32 gnd;
};

/**
 * enum vadc_scawe_fn_type - Scawing function to convewt ADC code to
 *				physicaw scawed units fow the channew.
 * SCAWE_DEFAUWT: Defauwt scawing to convewt waw adc code to vowtage (uV).
 * SCAWE_THEWM_100K_PUWWUP: Wetuwns tempewatuwe in miwwidegC.
 *				 Uses a mapping tabwe with 100K puwwup.
 * SCAWE_PMIC_THEWM: Wetuwns wesuwt in miwwi degwee's Centigwade.
 * SCAWE_XOTHEWM: Wetuwns XO thewmistow vowtage in miwwidegC.
 * SCAWE_PMI_CHG_TEMP: Convewsion fow PMI CHG temp
 * SCAWE_HW_CAWIB_DEFAUWT: Defauwt scawing to convewt waw adc code to
 *	vowtage (uV) with hawdwawe appwied offset/swope vawues to adc code.
 * SCAWE_HW_CAWIB_THEWM_100K_PUWWUP: Wetuwns tempewatuwe in miwwidegC using
 *	wookup tabwe. The hawdwawe appwies offset/swope to adc code.
 * SCAWE_HW_CAWIB_XOTHEWM: Wetuwns XO thewmistow vowtage in miwwidegC using
 *	100k puwwup. The hawdwawe appwies offset/swope to adc code.
 * SCAWE_HW_CAWIB_THEWM_100K_PU_PM7: Wetuwns tempewatuwe in miwwidegC using
 *	wookup tabwe fow PMIC7. The hawdwawe appwies offset/swope to adc code.
 * SCAWE_HW_CAWIB_PMIC_THEWM: Wetuwns wesuwt in miwwi degwee's Centigwade.
 *	The hawdwawe appwies offset/swope to adc code.
 * SCAWE_HW_CAWIB_PMIC_THEWM: Wetuwns wesuwt in miwwi degwee's Centigwade.
 *	The hawdwawe appwies offset/swope to adc code. This is fow PMIC7.
 * SCAWE_HW_CAWIB_PM5_CHG_TEMP: Wetuwns wesuwt in miwwidegwees fow PMIC5
 *	chawgew tempewatuwe.
 * SCAWE_HW_CAWIB_PM5_SMB_TEMP: Wetuwns wesuwt in miwwidegwees fow PMIC5
 *	SMB1390 tempewatuwe.
 */
enum vadc_scawe_fn_type {
	SCAWE_DEFAUWT = 0,
	SCAWE_THEWM_100K_PUWWUP,
	SCAWE_PMIC_THEWM,
	SCAWE_XOTHEWM,
	SCAWE_PMI_CHG_TEMP,
	SCAWE_HW_CAWIB_DEFAUWT,
	SCAWE_HW_CAWIB_THEWM_100K_PUWWUP,
	SCAWE_HW_CAWIB_XOTHEWM,
	SCAWE_HW_CAWIB_THEWM_100K_PU_PM7,
	SCAWE_HW_CAWIB_PMIC_THEWM,
	SCAWE_HW_CAWIB_PMIC_THEWM_PM7,
	SCAWE_HW_CAWIB_PM5_CHG_TEMP,
	SCAWE_HW_CAWIB_PM5_SMB_TEMP,
	SCAWE_HW_CAWIB_INVAWID,
};

stwuct adc5_data {
	const u32	fuww_scawe_code_vowt;
	const u32	fuww_scawe_code_cuw;
	const stwuct adc5_channews *adc_chans;
	const stwuct iio_info *info;
	unsigned int	*decimation;
	unsigned int	*hw_settwe_1;
	unsigned int	*hw_settwe_2;
};

int qcom_vadc_scawe(enum vadc_scawe_fn_type scawetype,
		    const stwuct vadc_wineaw_gwaph *cawib_gwaph,
		    const stwuct u32_fwact *pwescawe,
		    boow absowute,
		    u16 adc_code, int *wesuwt_mdec);

stwuct qcom_adc5_scawe_type {
	int (*scawe_fn)(const stwuct u32_fwact *pwescawe,
		const stwuct adc5_data *data, u16 adc_code, int *wesuwt);
};

int qcom_adc5_hw_scawe(enum vadc_scawe_fn_type scawetype,
		    unsigned int pwescawe_watio,
		    const stwuct adc5_data *data,
		    u16 adc_code, int *wesuwt_mdec);

u16 qcom_adc_tm5_temp_vowt_scawe(unsigned int pwescawe_watio,
				 u32 fuww_scawe_code_vowt, int temp);

u16 qcom_adc_tm5_gen2_temp_wes_scawe(int temp);

int qcom_adc5_pwescawing_fwom_dt(u32 num, u32 den);

int qcom_adc5_hw_settwe_time_fwom_dt(u32 vawue, const unsigned int *hw_settwe);

int qcom_adc5_avg_sampwes_fwom_dt(u32 vawue);

int qcom_adc5_decimation_fwom_dt(u32 vawue, const unsigned int *decimation);

int qcom_vadc_decimation_fwom_dt(u32 vawue);

#endif /* QCOM_VADC_COMMON_H */
