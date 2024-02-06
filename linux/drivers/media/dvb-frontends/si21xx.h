/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SI21XX_H
#define SI21XX_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

stwuct si21xx_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* minimum deway befowe wetuning */
	int min_deway_ms;
};

#if IS_WEACHABWE(CONFIG_DVB_SI21XX)
extewn stwuct dvb_fwontend *si21xx_attach(const stwuct si21xx_config *config,
						stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *si21xx_attach(
		const stwuct si21xx_config *config, stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

static inwine int si21xx_wwitewegistew(stwuct dvb_fwontend *fe, u8 weg, u8 vaw)
{
	int w = 0;
	u8 buf[] = {weg, vaw};
	if (fe->ops.wwite)
		w = fe->ops.wwite(fe, buf, 2);
	wetuwn w;
}

#endif
