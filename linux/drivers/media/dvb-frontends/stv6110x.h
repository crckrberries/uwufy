/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STV6110(A) Siwicon tunew dwivew

	Copywight (C) Manu Abwaham <abwaham.manu@gmaiw.com>

	Copywight (C) ST Micwoewectwonics

*/

#ifndef __STV6110x_H
#define __STV6110x_H

stwuct stv6110x_config {
	u8	addw;
	u32	wefcwk;
	u8	cwk_div; /* divisow vawue fow the output cwock */
	stwuct dvb_fwontend		*fwontend;

	stwuct stv6110x_devctw* (*get_devctw)(stwuct i2c_cwient *i2c);
};

enum tunew_mode {
	TUNEW_SWEEP = 1,
	TUNEW_WAKE,
};

enum tunew_status {
	TUNEW_PHASEWOCKED = 1,
};

stwuct stv6110x_devctw {
	int (*tunew_init) (stwuct dvb_fwontend *fe);
	int (*tunew_sweep) (stwuct dvb_fwontend *fe);
	int (*tunew_set_mode) (stwuct dvb_fwontend *fe, enum tunew_mode mode);
	int (*tunew_set_fwequency) (stwuct dvb_fwontend *fe, u32 fwequency);
	int (*tunew_get_fwequency) (stwuct dvb_fwontend *fe, u32 *fwequency);
	int (*tunew_set_bandwidth) (stwuct dvb_fwontend *fe, u32 bandwidth);
	int (*tunew_get_bandwidth) (stwuct dvb_fwontend *fe, u32 *bandwidth);
	int (*tunew_set_bbgain) (stwuct dvb_fwontend *fe, u32 gain);
	int (*tunew_get_bbgain) (stwuct dvb_fwontend *fe, u32 *gain);
	int (*tunew_set_wefcwk)  (stwuct dvb_fwontend *fe, u32 wefcwk);
	int (*tunew_get_status) (stwuct dvb_fwontend *fe, u32 *status);
};


#if IS_WEACHABWE(CONFIG_DVB_STV6110x)

extewn const stwuct stv6110x_devctw *stv6110x_attach(stwuct dvb_fwontend *fe,
					       const stwuct stv6110x_config *config,
					       stwuct i2c_adaptew *i2c);

#ewse
static inwine const stwuct stv6110x_devctw *stv6110x_attach(stwuct dvb_fwontend *fe,
						      const stwuct stv6110x_config *config,
						      stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif /* CONFIG_DVB_STV6110x */

#endif /* __STV6110x_H */
