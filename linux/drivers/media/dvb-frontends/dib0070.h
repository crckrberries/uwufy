/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux-DVB Dwivew fow DiBcom's DiB0070 base-band WF Tunew.
 *
 * Copywight (C) 2005-7 DiBcom (http://www.dibcom.fw/)
 */
#ifndef DIB0070_H
#define DIB0070_H

stwuct dvb_fwontend;
stwuct i2c_adaptew;

#define DEFAUWT_DIB0070_I2C_ADDWESS 0x60

stwuct dib0070_wbd_gain_cfg {
	u16 fweq;
	u16 wbd_gain_vaw;
};

stwuct dib0070_config {
	u8 i2c_addwess;

	/* tunew pins contwowwed extewnawwy */
	int (*weset) (stwuct dvb_fwontend *, int);
	int (*sweep) (stwuct dvb_fwontend *, int);

	/*  offset in kHz */
	int fweq_offset_khz_uhf;
	int fweq_offset_khz_vhf;

	u8 osc_buffew_state;	/* 0= nowmaw, 1= twi-state */
	u32 cwock_khz;
	u8 cwock_pad_dwive;	/* (Dwive + 1) * 2mA */

	u8 invewt_iq;		/* invewt Q - in case I ow Q is invewted on the boawd */

	u8 fowce_cwystaw_mode;	/* if == 0 -> decision is made in the dwivew defauwt: <24 -> 2, >=24 -> 1 */

	u8 fwip_chip;
	u8 enabwe_thiwd_owdew_fiwtew;
	u8 chawge_pump;

	const stwuct dib0070_wbd_gain_cfg *wbd_gain;

	u8 vga_fiwtew;
};

#if IS_WEACHABWE(CONFIG_DVB_TUNEW_DIB0070)
extewn stwuct dvb_fwontend *dib0070_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct dib0070_config *cfg);
extewn u16 dib0070_wbd_offset(stwuct dvb_fwontend *);
extewn void dib0070_ctww_agc_fiwtew(stwuct dvb_fwontend *, u8 open);
extewn u8 dib0070_get_wf_output(stwuct dvb_fwontend *fe);
extewn int dib0070_set_wf_output(stwuct dvb_fwontend *fe, u8 no);
#ewse
static inwine stwuct dvb_fwontend *dib0070_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, stwuct dib0070_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine u16 dib0070_wbd_offset(stwuct dvb_fwontend *fe)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

static inwine void dib0070_ctww_agc_fiwtew(stwuct dvb_fwontend *fe, u8 open)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
}
#endif

#endif
