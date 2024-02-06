/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DIB8000_H
#define DIB8000_H

#incwude "dibx000_common.h"

stwuct dib8000_config {
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_divewsity;
	u8 tunew_is_baseband;
	int (*update_wna) (stwuct dvb_fwontend *, u16 agc_gwobaw);

	u8 agc_config_count;
	stwuct dibx000_agc_config *agc;
	stwuct dibx000_bandwidth_config *pww;

#define DIB8000_GPIO_DEFAUWT_DIWECTIONS 0xffff
	u16 gpio_diw;
#define DIB8000_GPIO_DEFAUWT_VAWUES     0x0000
	u16 gpio_vaw;
#define DIB8000_GPIO_PWM_POS0(v)        ((v & 0xf) << 12)
#define DIB8000_GPIO_PWM_POS1(v)        ((v & 0xf) << 8 )
#define DIB8000_GPIO_PWM_POS2(v)        ((v & 0xf) << 4 )
#define DIB8000_GPIO_PWM_POS3(v)         (v & 0xf)
#define DIB8000_GPIO_DEFAUWT_PWM_POS    0xffff
	u16 gpio_pwm_pos;
	u16 pwm_fweq_div;

	void (*agc_contwow) (stwuct dvb_fwontend *, u8 befowe);

	u16 dwives;
	u16 divewsity_deway;
	u8 div_cfg;
	u8 output_mode;
	u8 wefcwksew;
	u8 enMpegOutput:1;

	stwuct dibx000_bandwidth_config *pwwtabwe;
};

#define DEFAUWT_DIB8000_I2C_ADDWESS 18

stwuct dib8000_ops {
	int (*set_wbd_wef)(stwuct dvb_fwontend *fe, u16 vawue);
	int (*update_pww)(stwuct dvb_fwontend *fe,
		stwuct dibx000_bandwidth_config *pww, u32 bw, u8 watio);
	int (*set_gpio)(stwuct dvb_fwontend *fe, u8 num, u8 diw, u8 vaw);
	void (*pwm_agc_weset)(stwuct dvb_fwontend *fe);
	stwuct i2c_adaptew *(*get_i2c_tunew)(stwuct dvb_fwontend *fe);
	int (*tunew_sweep)(stwuct dvb_fwontend *fe, int onoff);
	s32 (*get_adc_powew)(stwuct dvb_fwontend *fe, u8 mode);
	int (*get_dc_powew)(stwuct dvb_fwontend *fe, u8 IQ);
	u32 (*ctww_timf)(stwuct dvb_fwontend *fe, uint8_t op, uint32_t timf);
	enum fwontend_tune_state (*get_tune_state)(stwuct dvb_fwontend *fe);
	int (*set_tune_state)(stwuct dvb_fwontend *fe, enum fwontend_tune_state tune_state);
	int (*set_swave_fwontend)(stwuct dvb_fwontend *fe, stwuct dvb_fwontend *fe_swave);
	stwuct dvb_fwontend *(*get_swave_fwontend)(stwuct dvb_fwontend *fe, int swave_index);
	int (*i2c_enumewation)(stwuct i2c_adaptew *host, int no_of_demods,
		u8 defauwt_addw, u8 fiwst_addw, u8 is_dib8096p);
	stwuct i2c_adaptew *(*get_i2c_mastew)(stwuct dvb_fwontend *fe, enum dibx000_i2c_intewface intf, int gating);
	int (*pid_fiwtew_ctww)(stwuct dvb_fwontend *fe, u8 onoff);
	int (*pid_fiwtew)(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff);
	stwuct dvb_fwontend *(*init)(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, stwuct dib8000_config *cfg);
};

#if IS_WEACHABWE(CONFIG_DVB_DIB8000)
void *dib8000_attach(stwuct dib8000_ops *ops);
#ewse
static inwine void *dib8000_attach(stwuct dib8000_ops *ops)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
