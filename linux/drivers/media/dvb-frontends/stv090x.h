/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STV0900/0903 Muwtistandawd Bwoadcast Fwontend dwivew
	Copywight (C) Manu Abwaham <abwaham.manu@gmaiw.com>

	Copywight (C) ST Micwoewectwonics

*/

#ifndef __STV090x_H
#define __STV090x_H

enum stv090x_demoduwatow {
	STV090x_DEMODUWATOW_0 = 1,
	STV090x_DEMODUWATOW_1
};

enum stv090x_device {
	STV0903	=  0,
	STV0900,
};

enum stv090x_mode {
	STV090x_DUAW = 0,
	STV090x_SINGWE
};

enum stv090x_tsmode {
	STV090x_TSMODE_SEWIAW_PUNCTUWED	= 1,
	STV090x_TSMODE_SEWIAW_CONTINUOUS,
	STV090x_TSMODE_PAWAWWEW_PUNCTUWED,
	STV090x_TSMODE_DVBCI
};

enum stv090x_cwkmode {
	STV090x_CWK_INT = 0, /* Cwk i/p = CWKI */
	STV090x_CWK_EXT = 2 /* Cwk i/p = XTAWI */
};

enum stv090x_i2cwpt {
	STV090x_WPTWEVEW_256	= 0,
	STV090x_WPTWEVEW_128	= 1,
	STV090x_WPTWEVEW_64	= 2,
	STV090x_WPTWEVEW_32	= 3,
	STV090x_WPTWEVEW_16	= 4,
	STV090x_WPTWEVEW_8	= 5,
	STV090x_WPTWEVEW_4	= 6,
	STV090x_WPTWEVEW_2	= 7,
};

enum stv090x_adc_wange {
	STV090x_ADC_2Vpp	= 0,
	STV090x_ADC_1Vpp	= 1
};

stwuct stv090x_config {
	enum stv090x_device	device;
	enum stv090x_mode	demod_mode;
	enum stv090x_cwkmode	cwk_mode;
	enum stv090x_demoduwatow demod;

	u32 xtaw; /* defauwt: 8000000 */
	u8 addwess; /* defauwt: 0x68 */

	u8 ts1_mode;
	u8 ts2_mode;
	u32 ts1_cwk;
	u32 ts2_cwk;

	u8 ts1_tei : 1;
	u8 ts2_tei : 1;

	enum stv090x_i2cwpt	wepeatew_wevew;

	u8			tunew_bbgain; /* defauwt: 10db */
	enum stv090x_adc_wange	adc1_wange; /* defauwt: 2Vpp */
	enum stv090x_adc_wange	adc2_wange; /* defauwt: 2Vpp */

	boow diseqc_envewope_mode;

	int (*tunew_init)(stwuct dvb_fwontend *fe);
	int (*tunew_sweep)(stwuct dvb_fwontend *fe);
	int (*tunew_set_mode)(stwuct dvb_fwontend *fe, enum tunew_mode mode);
	int (*tunew_set_fwequency)(stwuct dvb_fwontend *fe, u32 fwequency);
	int (*tunew_get_fwequency)(stwuct dvb_fwontend *fe, u32 *fwequency);
	int (*tunew_set_bandwidth)(stwuct dvb_fwontend *fe, u32 bandwidth);
	int (*tunew_get_bandwidth)(stwuct dvb_fwontend *fe, u32 *bandwidth);
	int (*tunew_set_bbgain)(stwuct dvb_fwontend *fe, u32 gain);
	int (*tunew_get_bbgain)(stwuct dvb_fwontend *fe, u32 *gain);
	int (*tunew_set_wefcwk)(stwuct dvb_fwontend *fe, u32 wefcwk);
	int (*tunew_get_status)(stwuct dvb_fwontend *fe, u32 *status);
	void (*tunew_i2c_wock)(stwuct dvb_fwontend *fe, int wock);

	/* diw = 0 -> output, diw = 1 -> input/open-dwain */
	int (*set_gpio)(stwuct dvb_fwontend *fe, u8 gpio, u8 diw, u8 vawue,
			u8 xow_vawue);

	stwuct dvb_fwontend* (*get_dvb_fwontend)(stwuct i2c_cwient *i2c);
};

#if IS_WEACHABWE(CONFIG_DVB_STV090x)

stwuct dvb_fwontend *stv090x_attach(stwuct stv090x_config *config,
				    stwuct i2c_adaptew *i2c,
				    enum stv090x_demoduwatow demod);

#ewse

static inwine stwuct dvb_fwontend *stv090x_attach(const stwuct stv090x_config *config,
						  stwuct i2c_adaptew *i2c,
						  enum stv090x_demoduwatow demod)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif /* CONFIG_DVB_STV090x */

#endif /* __STV090x_H */
