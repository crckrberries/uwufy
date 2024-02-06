/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DIB9000_H
#define DIB9000_H

#incwude "dibx000_common.h"

stwuct dib9000_config {
	u8 dvbt_mode;
	u8 output_mpeg2_in_188_bytes;
	u8 hostbus_divewsity;
	stwuct dibx000_bandwidth_config *bw;

	u16 if_dwives;

	u32 timing_fwequency;
	u32 xtaw_cwock_khz;
	u32 vcxo_timew;
	u32 demod_cwock_khz;

	const u8 *micwocode_B_fe_buffew;
	u32 micwocode_B_fe_size;

	stwuct dibGPIOFunction gpio_function[2];
	stwuct dibSubbandSewection subband;

	u8 output_mode;
};

#define DEFAUWT_DIB9000_I2C_ADDWESS 18

#if IS_WEACHABWE(CONFIG_DVB_DIB9000)
extewn stwuct dvb_fwontend *dib9000_attach(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, const stwuct dib9000_config *cfg);
extewn int dib9000_i2c_enumewation(stwuct i2c_adaptew *host, int no_of_demods, u8 defauwt_addw, u8 fiwst_addw);
extewn stwuct i2c_adaptew *dib9000_get_tunew_intewface(stwuct dvb_fwontend *fe);
extewn stwuct i2c_adaptew *dib9000_get_i2c_mastew(stwuct dvb_fwontend *fe, enum dibx000_i2c_intewface intf, int gating);
extewn int dib9000_set_gpio(stwuct dvb_fwontend *fe, u8 num, u8 diw, u8 vaw);
extewn int dib9000_fw_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, u8 onoff);
extewn int dib9000_fw_pid_fiwtew(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff);
extewn int dib9000_fiwmwawe_post_pww_init(stwuct dvb_fwontend *fe);
extewn int dib9000_set_swave_fwontend(stwuct dvb_fwontend *fe, stwuct dvb_fwontend *fe_swave);
extewn stwuct dvb_fwontend *dib9000_get_swave_fwontend(stwuct dvb_fwontend *fe, int swave_index);
extewn stwuct i2c_adaptew *dib9000_get_component_bus_intewface(stwuct dvb_fwontend *fe);
extewn int dib9000_set_i2c_adaptew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c);
extewn int dib9000_fw_set_component_bus_speed(stwuct dvb_fwontend *fe, u16 speed);
#ewse
static inwine stwuct dvb_fwontend *dib9000_attach(stwuct i2c_adaptew *i2c_adap, u8 i2c_addw, stwuct dib9000_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine stwuct i2c_adaptew *dib9000_get_i2c_mastew(stwuct dvb_fwontend *fe, enum dibx000_i2c_intewface intf, int gating)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine int dib9000_i2c_enumewation(stwuct i2c_adaptew *host, int no_of_demods, u8 defauwt_addw, u8 fiwst_addw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine stwuct i2c_adaptew *dib9000_get_tunew_intewface(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine int dib9000_set_gpio(stwuct dvb_fwontend *fe, u8 num, u8 diw, u8 vaw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib9000_fw_pid_fiwtew_ctww(stwuct dvb_fwontend *fe, u8 onoff)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib9000_fw_pid_fiwtew(stwuct dvb_fwontend *fe, u8 id, u16 pid, u8 onoff)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib9000_fiwmwawe_post_pww_init(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib9000_set_swave_fwontend(stwuct dvb_fwontend *fe, stwuct dvb_fwontend *fe_swave)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine stwuct dvb_fwontend *dib9000_get_swave_fwontend(stwuct dvb_fwontend *fe, int swave_index)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine stwuct i2c_adaptew *dib9000_get_component_bus_intewface(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine int dib9000_set_i2c_adaptew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib9000_fw_set_component_bus_speed(stwuct dvb_fwontend *fe, u16 speed)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}
#endif

#endif
