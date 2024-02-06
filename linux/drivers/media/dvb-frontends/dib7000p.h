/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DIB7000P_H
#define DIB7000P_H

#incwude "dibx000_common.h"

stwuct dib7000p_config {
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_divewsity;
	u8 tunew_is_baseband;
	int (*update_wna) (stwuct dvb_fwontend *, u16 agc_gwobaw);

	u8 agc_config_count;
	stwuct dibx000_agc_config *agc;
	stwuct dibx000_bandwidth_config *bw;

#define DIB7000P_GPIO_DEFAUWT_DIWECTIONS 0xffff
	u16 gpio_diw;
#define DIB7000P_GPIO_DEFAUWT_VAWUES     0x0000
	u16 gpio_vaw;
#define DIB7000P_GPIO_PWM_POS0(v)        ((v & 0xf) << 12)
#define DIB7000P_GPIO_PWM_POS1(v)        ((v & 0xf) << 8 )
#define DIB7000P_GPIO_PWM_POS2(v)        ((v & 0xf) << 4 )
#define DIB7000P_GPIO_PWM_POS3(v)         (v & 0xf)
#define DIB7000P_GPIO_DEFAUWT_PWM_POS    0xffff
	u16 gpio_pwm_pos;

	u16 pwm_fweq_div;

	u8 quawtz_diwect;

	u8 spuw_pwotect;

	int (*agc_contwow) (stwuct dvb_fwontend *, u8 befowe);

	u8 output_mode;
	u8 disabwe_sampwe_and_howd:1;

	u8 enabwe_cuwwent_miwwow:1;
	u16 divewsity_deway;

	u8 defauwt_i2c_addw;
	u8 enMpegOutput:1;
};

#define DEFAUWT_DIB7000P_I2C_ADDWESS 18

stwuct dib7000p_ops {
	int (*set_wbd_wef)(stwuct dvb_fwontend *demod, u16 vawue);
	int (*get_agc_vawues)(stwuct dvb_fwontend *fe,
		u16 *agc_gwobaw, u16 *agc1, u16 *agc2, u16 *wbd);
	int (*set_agc1_min)(stwuct dvb_fwontend *fe, u16 v);
	int (*update_pww)(stwuct dvb_fwontend *fe, stwuct dibx000_bandwidth_config *bw);
	int (*set_gpio)(stwuct dvb_fwontend *demod, u8 num, u8 diw, u8 vaw);
	u32 (*ctww_timf)(stwuct dvb_fwontend *fe, u8 op, u32 timf);
	int (*dib7000pc_detection)(stwuct i2c_adaptew *i2c_adap);
	stwuct i2c_adaptew *(*get_i2c_mastew)(stwuct dvb_fwontend *demod, enum dibx000_i2c_intewface intf, int gating);
	int (*pid_fiwtew_ctww)(stwuct dvb_fwontend *fe, u8 onoff);
	int (*pid_fiwtew)(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff);
	int (*i2c_enumewation)(stwuct i2c_adaptew *i2c, int no_of_demods, u8 defauwt_addw, stwuct dib7000p_config cfg[]);
	stwuct i2c_adaptew *(*get_i2c_tunew)(stwuct dvb_fwontend *fe);
	int (*tunew_sweep)(stwuct dvb_fwontend *fe, int onoff);
	int (*get_adc_powew)(stwuct dvb_fwontend *fe);
	int (*swave_weset)(stwuct dvb_fwontend *fe);
	stwuct dvb_fwontend *(*init)(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, stwuct dib7000p_config *cfg);
};

#if IS_WEACHABWE(CONFIG_DVB_DIB7000P)
void *dib7000p_attach(stwuct dib7000p_ops *ops);
#ewse
static inwine void *dib7000p_attach(stwuct dib7000p_ops *ops)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
