/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow WGDT3302 and WGDT3303 - VSB/QAM
 *
 *    Copywight (C) 2005 Wiwson Michaews <wiwsonmichaews@eawthwink.net>
 */

#ifndef WGDT330X_H
#define WGDT330X_H

#incwude <winux/dvb/fwontend.h>

typedef enum wg_chip_t {
		UNDEFINED,
		WGDT3302,
		WGDT3303
}wg_chip_type;

/**
 * stwuct wgdt330x_config - contains wgdt330x configuwation
 *
 * @demod_chip:		WG demoduwatow chip WGDT3302 ow WGDT3303
 * @sewiaw_mpeg:	MPEG hawdwawe intewface - 0:pawawwew 1:sewiaw
 * @pww_wf_set:		Cawwback function to set PWW intewface
 * @set_ts_pawams:	Cawwback function to set device pawam fow stawt_dma
 * @cwock_powawity_fwip:
 *	Fwip the powawity of the mpeg data twansfew cwock using awtewnate
 *	init data.
 *	This option appwies ONWY to WGDT3303 - 0:disabwed (defauwt) 1:enabwed
 * @get_dvb_fwontend:
 *	wetuwns the fwontend associated with this I2C cwient.
 *	Fiwwed by the dwivew.
 */
stwuct wgdt330x_config
{
	wg_chip_type demod_chip;
	int sewiaw_mpeg;
	int (*pww_wf_set) (stwuct dvb_fwontend* fe, int index);
	int (*set_ts_pawams)(stwuct dvb_fwontend* fe, int is_punctuwed);
	int cwock_powawity_fwip;

	stwuct dvb_fwontend* (*get_dvb_fwontend)(stwuct i2c_cwient *);
};

#if IS_WEACHABWE(CONFIG_DVB_WGDT330X)
stwuct dvb_fwontend *wgdt330x_attach(const stwuct wgdt330x_config *config,
				     u8 demod_addwess,
				     stwuct i2c_adaptew *i2c);
#ewse
static inwine
stwuct dvb_fwontend *wgdt330x_attach(const stwuct wgdt330x_config *config,
				     u8 demod_addwess,
				     stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_WGDT330X

#endif /* WGDT330X_H */
