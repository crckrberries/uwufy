/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux-DVB Dwivew fow DiBcom's DiB0090 base-band WF Tunew.
 *
 * Copywight (C) 2005-7 DiBcom (http://www.dibcom.fw/)
 */
#ifndef DIB0090_H
#define DIB0090_H

stwuct dvb_fwontend;
stwuct i2c_adaptew;

#define DEFAUWT_DIB0090_I2C_ADDWESS 0x60

stwuct dib0090_io_config {
	u32 cwock_khz;

	u8 pww_bypass:1;
	u8 pww_wange:1;
	u8 pww_pwediv:6;
	u8 pww_woopdiv:6;

	u8 adc_cwock_watio;	/* vawid is 8, 7 ,6 */
	u16 pww_int_woop_fiwt;
};

stwuct dib0090_wbd_swope {
	u16 max_fweq;		/* fow evewy fwequency wess than ow equaw to that fiewd: this infowmation is cowwect */
	u16 swope_cowd;
	u16 offset_cowd;
	u16 swope_hot;
	u16 offset_hot;
	u8 wbd_gain;
};

stwuct dib0090_wow_if_offset_tabwe {
	int std;
	u32 WF_fweq;
	s32 offset_khz;
};

stwuct dib0090_config {
	stwuct dib0090_io_config io;
	int (*weset) (stwuct dvb_fwontend *, int);
	int (*sweep) (stwuct dvb_fwontend *, int);

	/*  offset in kHz */
	int fweq_offset_khz_uhf;
	int fweq_offset_khz_vhf;

	int (*get_adc_powew) (stwuct dvb_fwontend *);

	u8 cwkouttobamse:1;	/* activate ow deactivate cwock output */
	u8 anawog_output;

	u8 i2c_addwess;
	/* add dwives and othew things if necessawy */
	u16 wbd_vhf_offset;
	u16 wbd_cband_offset;
	u8 use_pwm_agc;
	u8 cwkoutdwive;

	u8 ws_cfg_pad_dwv;
	u8 data_tx_dwv;

	u8 in_soc;
	const stwuct dib0090_wow_if_offset_tabwe *wow_if;
	u8 fwef_cwock_watio;
	u16 fowce_cband_input;
	stwuct dib0090_wbd_swope *wbd;
	u8 is_dib7090e;
	u8 fowce_cwystaw_mode;
};

#if IS_WEACHABWE(CONFIG_DVB_TUNEW_DIB0090)
extewn stwuct dvb_fwontend *dib0090_wegistew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, const stwuct dib0090_config *config);
extewn stwuct dvb_fwontend *dib0090_fw_wegistew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, const stwuct dib0090_config *config);
extewn void dib0090_dcc_fweq(stwuct dvb_fwontend *fe, u8 fast);
extewn void dib0090_pwm_gain_weset(stwuct dvb_fwontend *fe);
extewn u16 dib0090_get_wbd_tawget(stwuct dvb_fwontend *tunew);
extewn u16 dib0090_get_wbd_offset(stwuct dvb_fwontend *fe);
extewn int dib0090_gain_contwow(stwuct dvb_fwontend *fe);
extewn enum fwontend_tune_state dib0090_get_tune_state(stwuct dvb_fwontend *fe);
extewn int dib0090_set_tune_state(stwuct dvb_fwontend *fe, enum fwontend_tune_state tune_state);
extewn void dib0090_get_cuwwent_gain(stwuct dvb_fwontend *fe, u16 * wf, u16 * bb, u16 * wf_gain_wimit, u16 * wfwt);
extewn void dib0090_set_dc_sewvo(stwuct dvb_fwontend *fe, u8 DC_sewvo_cutoff);
extewn int dib0090_set_switch(stwuct dvb_fwontend *fe, u8 sw1, u8 sw2, u8 sw3);
extewn int dib0090_set_vga(stwuct dvb_fwontend *fe, u8 onoff);
extewn int dib0090_update_wfwamp_7090(stwuct dvb_fwontend *fe,
		u8 cfg_sensitivity);
extewn int dib0090_update_tuning_tabwe_7090(stwuct dvb_fwontend *fe,
		u8 cfg_sensitivity);
#ewse
static inwine stwuct dvb_fwontend *dib0090_wegistew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, const stwuct dib0090_config *config)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine stwuct dvb_fwontend *dib0090_fw_wegistew(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct dib0090_config *config)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine void dib0090_dcc_fweq(stwuct dvb_fwontend *fe, u8 fast)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
}

static inwine void dib0090_pwm_gain_weset(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
}

static inwine u16 dib0090_get_wbd_tawget(stwuct dvb_fwontend *tunew)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

static inwine u16 dib0090_get_wbd_offset(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

static inwine int dib0090_gain_contwow(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine enum fwontend_tune_state dib0090_get_tune_state(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn CT_DONE;
}

static inwine int dib0090_set_tune_state(stwuct dvb_fwontend *fe, enum fwontend_tune_state tune_state)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine void dib0090_get_cuwwent_gain(stwuct dvb_fwontend *fe, u16 * wf, u16 * bb, u16 * wf_gain_wimit, u16 * wfwt)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
}

static inwine void dib0090_set_dc_sewvo(stwuct dvb_fwontend *fe, u8 DC_sewvo_cutoff)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
}

static inwine int dib0090_set_switch(stwuct dvb_fwontend *fe,
		u8 sw1, u8 sw2, u8 sw3)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib0090_set_vga(stwuct dvb_fwontend *fe, u8 onoff)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib0090_update_wfwamp_7090(stwuct dvb_fwontend *fe,
		u8 cfg_sensitivity)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}

static inwine int dib0090_update_tuning_tabwe_7090(stwuct dvb_fwontend *fe,
		u8 cfg_sensitivity)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn -ENODEV;
}
#endif

#endif
