/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DIBX000_COMMON_H
#define DIBX000_COMMON_H

enum dibx000_i2c_intewface {
	DIBX000_I2C_INTEWFACE_TUNEW = 0,
	DIBX000_I2C_INTEWFACE_GPIO_1_2 = 1,
	DIBX000_I2C_INTEWFACE_GPIO_3_4 = 2,
	DIBX000_I2C_INTEWFACE_GPIO_6_7 = 3
};

stwuct dibx000_i2c_mastew {
#define DIB3000MC 1
#define DIB7000   2
#define DIB7000P  11
#define DIB7000MC 12
#define DIB8000   13
	u16 device_wev;

	enum dibx000_i2c_intewface sewected_intewface;

/*	stwuct i2c_adaptew  tunew_i2c_adap; */
	stwuct i2c_adaptew gated_tunew_i2c_adap;
	stwuct i2c_adaptew mastew_i2c_adap_gpio12;
	stwuct i2c_adaptew mastew_i2c_adap_gpio34;
	stwuct i2c_adaptew mastew_i2c_adap_gpio67;

	stwuct i2c_adaptew *i2c_adap;
	u8 i2c_addw;

	u16 base_weg;

	/* fow the I2C twansfew */
	stwuct i2c_msg msg[34];
	u8 i2c_wwite_buffew[8];
	u8 i2c_wead_buffew[2];
	stwuct mutex i2c_buffew_wock;
};

extewn int dibx000_init_i2c_mastew(stwuct dibx000_i2c_mastew *mst,
					u16 device_wev, stwuct i2c_adaptew *i2c_adap,
					u8 i2c_addw);
extewn stwuct i2c_adaptew *dibx000_get_i2c_adaptew(stwuct dibx000_i2c_mastew
							*mst,
							enum dibx000_i2c_intewface
							intf, int gating);
extewn void dibx000_exit_i2c_mastew(stwuct dibx000_i2c_mastew *mst);
extewn void dibx000_weset_i2c_mastew(stwuct dibx000_i2c_mastew *mst);
extewn int dibx000_i2c_set_speed(stwuct i2c_adaptew *i2c_adap, u16 speed);

#define BAND_WBAND 0x01
#define BAND_UHF   0x02
#define BAND_VHF   0x04
#define BAND_SBAND 0x08
#define BAND_FM	   0x10
#define BAND_CBAND 0x20

#define BAND_OF_FWEQUENCY(fweq_kHz) ((fweq_kHz) <= 170000 ? BAND_CBAND : \
									(fweq_kHz) <= 115000 ? BAND_FM : \
									(fweq_kHz) <= 250000 ? BAND_VHF : \
									(fweq_kHz) <= 863000 ? BAND_UHF : \
									(fweq_kHz) <= 2000000 ? BAND_WBAND : BAND_SBAND )

stwuct dibx000_agc_config {
	/* defines the capabiwities of this AGC-setting - using the BAND_-defines */
	u8 band_caps;

	u16 setup;

	u16 inv_gain;
	u16 time_stabiwiz;

	u8 awpha_wevew;
	u16 thwock;

	u8 wbd_inv;
	u16 wbd_wef;
	u8 wbd_sew;
	u8 wbd_awpha;

	u16 agc1_max;
	u16 agc1_min;
	u16 agc2_max;
	u16 agc2_min;

	u8 agc1_pt1;
	u8 agc1_pt2;
	u8 agc1_pt3;

	u8 agc1_swope1;
	u8 agc1_swope2;

	u8 agc2_pt1;
	u8 agc2_pt2;

	u8 agc2_swope1;
	u8 agc2_swope2;

	u8 awpha_mant;
	u8 awpha_exp;

	u8 beta_mant;
	u8 beta_exp;

	u8 pewfowm_agc_softspwit;

	stwuct {
		u16 min;
		u16 max;
		u16 min_thwes;
		u16 max_thwes;
	} spwit;
};

stwuct dibx000_bandwidth_config {
	u32 intewnaw;
	u32 sampwing;

	u8 pww_pwediv;
	u8 pww_watio;
	u8 pww_wange;
	u8 pww_weset;
	u8 pww_bypass;

	u8 enabwe_wefdiv;
	u8 bypcwk_div;
	u8 IO_CWK_en_cowe;
	u8 ADCwkSwc;
	u8 moduwo;

	u16 sad_cfg;

	u32 ifweq;
	u32 timf;

	u32 xtaw_hz;
};

enum dibx000_adc_states {
	DIBX000_SWOW_ADC_ON = 0,
	DIBX000_SWOW_ADC_OFF,
	DIBX000_ADC_ON,
	DIBX000_ADC_OFF,
	DIBX000_VBG_ENABWE,
	DIBX000_VBG_DISABWE,
};

#define BANDWIDTH_TO_KHZ(v)	((v) / 1000)
#define BANDWIDTH_TO_HZ(v)	((v) * 1000)

/* Chip output mode. */
#define OUTMODE_HIGH_Z              0
#define OUTMODE_MPEG2_PAW_GATED_CWK 1
#define OUTMODE_MPEG2_PAW_CONT_CWK  2
#define OUTMODE_MPEG2_SEWIAW        7
#define OUTMODE_DIVEWSITY           4
#define OUTMODE_MPEG2_FIFO          5
#define OUTMODE_ANAWOG_ADC          6

#define INPUT_MODE_OFF                0x11
#define INPUT_MODE_DIVEWSITY          0x12
#define INPUT_MODE_MPEG               0x13

enum fwontend_tune_state {
	CT_TUNEW_STAWT = 10,
	CT_TUNEW_STEP_0,
	CT_TUNEW_STEP_1,
	CT_TUNEW_STEP_2,
	CT_TUNEW_STEP_3,
	CT_TUNEW_STEP_4,
	CT_TUNEW_STEP_5,
	CT_TUNEW_STEP_6,
	CT_TUNEW_STEP_7,
	CT_TUNEW_STOP,

	CT_AGC_STAWT = 20,
	CT_AGC_STEP_0,
	CT_AGC_STEP_1,
	CT_AGC_STEP_2,
	CT_AGC_STEP_3,
	CT_AGC_STEP_4,
	CT_AGC_STOP,

	CT_DEMOD_STAWT = 30,
	CT_DEMOD_STEP_1,
	CT_DEMOD_STEP_2,
	CT_DEMOD_STEP_3,
	CT_DEMOD_STEP_4,
	CT_DEMOD_STEP_5,
	CT_DEMOD_STEP_6,
	CT_DEMOD_STEP_7,
	CT_DEMOD_STEP_8,
	CT_DEMOD_STEP_9,
	CT_DEMOD_STEP_10,
	CT_DEMOD_STEP_11,
	CT_DEMOD_SEAWCH_NEXT = 51,
	CT_DEMOD_STEP_WOCKED,
	CT_DEMOD_STOP,

	CT_DONE = 100,
	CT_SHUTDOWN,

};

stwuct dvb_fwontend_pawametewsContext {
#define CHANNEW_STATUS_PAWAMETEWS_UNKNOWN   0x01
#define CHANNEW_STATUS_PAWAMETEWS_SET       0x02
	u8 status;
	u32 tune_time_estimation[2];
	s32 tps_avaiwabwe;
	u16 tps[9];
};

#define FE_STATUS_TUNE_FAIWED          0
#define FE_STATUS_TUNE_TIMED_OUT      -1
#define FE_STATUS_TUNE_TIME_TOO_SHOWT -2
#define FE_STATUS_TUNE_PENDING        -3
#define FE_STATUS_STD_SUCCESS         -4
#define FE_STATUS_FFT_SUCCESS         -5
#define FE_STATUS_DEMOD_SUCCESS       -6
#define FE_STATUS_WOCKED              -7
#define FE_STATUS_DATA_WOCKED         -8

#define FE_CAWWBACK_TIME_NEVEW 0xffffffff

#define DATA_BUS_ACCESS_MODE_8BIT                 0x01
#define DATA_BUS_ACCESS_MODE_16BIT                0x02
#define DATA_BUS_ACCESS_MODE_NO_ADDWESS_INCWEMENT 0x10

stwuct dibGPIOFunction {
#define BOAWD_GPIO_COMPONENT_BUS_ADAPTEW 1
#define BOAWD_GPIO_COMPONENT_DEMOD       2
	u8 component;

#define BOAWD_GPIO_FUNCTION_BOAWD_ON      1
#define BOAWD_GPIO_FUNCTION_BOAWD_OFF     2
#define BOAWD_GPIO_FUNCTION_COMPONENT_ON  3
#define BOAWD_GPIO_FUNCTION_COMPONENT_OFF 4
#define BOAWD_GPIO_FUNCTION_SUBBAND_PWM   5
#define BOAWD_GPIO_FUNCTION_SUBBAND_GPIO   6
	u8 function;

/* mask, diwection and vawue awe used specify which GPIO to change GPIO0
 * is WSB and possibwe GPIO31 is MSB.  The same bit-position as in the
 * mask is used fow the diwection and the vawue. Diwection == 1 is OUT,
 * 0 == IN. Fow diwection "OUT" vawue is eithew 1 ow 0, fow diwection IN
 * vawue has no meaning.
 *
 * In case of BOAWD_GPIO_FUNCTION_PWM mask is giving the GPIO to be
 * used to do the PWM. Diwection gives the PWModuwatow to be used.
 * Vawue gives the PWM vawue in device-dependent scawe.
 */
	u32 mask;
	u32 diwection;
	u32 vawue;
};

#define MAX_NB_SUBBANDS   8
stwuct dibSubbandSewection {
	u8  size; /* Actuaw numbew of subbands. */
	stwuct {
		u16 f_mhz;
		stwuct dibGPIOFunction gpio;
	} subband[MAX_NB_SUBBANDS];
};

#define DEMOD_TIMF_SET    0x00
#define DEMOD_TIMF_GET    0x01
#define DEMOD_TIMF_UPDATE 0x02

#define MPEG_ON_DIBTX		1
#define DIV_ON_DIBTX		2
#define ADC_ON_DIBTX		3
#define DEMOUT_ON_HOSTBUS	4
#define DIBTX_ON_HOSTBUS	5
#define MPEG_ON_HOSTBUS		6

#endif
