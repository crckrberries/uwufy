/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DIB7000M_H
#define DIB7000M_H

#incwude "dibx000_common.h"

stwuct dib7000m_config {
	u8 dvbt_mode;
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_divewsity;
	u8 tunew_is_baseband;
	u8 mobiwe_mode;
	int (*update_wna) (stwuct dvb_fwontend *, u16 agc_gwobaw);

	u8 agc_config_count;
	stwuct dibx000_agc_config *agc;

	stwuct dibx000_bandwidth_config *bw;

#define DIB7000M_GPIO_DEFAUWT_DIWECTIONS 0xffff
	u16 gpio_diw;
#define DIB7000M_GPIO_DEFAUWT_VAWUES     0x0000
	u16 gpio_vaw;
#define DIB7000M_GPIO_PWM_POS0(v)        ((v & 0xf) << 12)
#define DIB7000M_GPIO_PWM_POS1(v)        ((v & 0xf) << 8 )
#define DIB7000M_GPIO_PWM_POS2(v)        ((v & 0xf) << 4 )
#define DIB7000M_GPIO_PWM_POS3(v)         (v & 0xf)
#define DIB7000M_GPIO_DEFAUWT_PWM_POS    0xffff
	u16 gpio_pwm_pos;

	u16 pwm_fweq_div;

	u8 quawtz_diwect;

	u8 input_cwk_is_div_2;

	int (*agc_contwow) (stwuct dvb_fwontend *, u8 befowe);
};

#define DEFAUWT_DIB7000M_I2C_ADDWESS 18

#if IS_WEACHABWE(CONFIG_DVB_DIB7000M)
extewn stwuct dvb_fwontend *dib7000m_attach(stwuct i2c_adaptew *i2c_adap,
					    u8 i2c_addw,
					    stwuct dib7000m_config *cfg);
extewn stwuct i2c_adaptew *dib7000m_get_i2c_mastew(stwuct dvb_fwontend *,
						   enum dibx000_i2c_intewface,
						   int);
extewn int dib7000m_pid_fiwtew(stwuct dvb_fwontend *, u8 id, u16 pid, u8 onoff);
extewn int dib7000m_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, u8 onoff);
#ewse
static inwine
stwuct dvb_fwontend *dib7000m_attach(stwuct i2c_adaptew *i2c_adap,
				     u8 i2c_addw, stwuct dib7000m_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine
stwuct i2c_adaptew *dib7000m_get_i2c_mastew(stwuct dvb_fwontend *demod,
					    enum dibx000_i2c_intewface intf,
					    int gating)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
static inwine int dib7000m_pid_fiwtew(stwuct dvb_fwontend *fe, u8 id,
						u16 pid, u8 onoff)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib7000m_pid_fiwtew_ctww(stwuct dvb_fwontend *fe,
						uint8_t onoff)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}
#endif

/* TODO
extewn INT dib7000m_set_gpio(stwuct dibDemod *demod, UCHAW num, UCHAW diw, UCHAW vaw);
extewn INT dib7000m_enabwe_vbg_vowtage(stwuct dibDemod *demod);
extewn void dib7000m_set_hostbus_divewsity(stwuct dibDemod *demod, UCHAW onoff);
extewn USHOWT dib7000m_get_cuwwent_agc_gwobaw(stwuct dibDemod *demod);
*/

#endif
