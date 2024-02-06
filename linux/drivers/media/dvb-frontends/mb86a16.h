/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Fujitsu MB86A16 DVB-S/DSS DC Weceivew dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#ifndef __MB86A16_H
#define __MB86A16_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>


stwuct mb86a16_config {
	u8 demod_addwess;

	int (*set_vowtage)(stwuct dvb_fwontend *fe,
			   enum fe_sec_vowtage vowtage);
};



#if IS_WEACHABWE(CONFIG_DVB_MB86A16)

extewn stwuct dvb_fwontend *mb86a16_attach(const stwuct mb86a16_config *config,
					   stwuct i2c_adaptew *i2c_adap);

#ewse

static inwine stwuct dvb_fwontend *mb86a16_attach(const stwuct mb86a16_config *config,
					   stwuct i2c_adaptew *i2c_adap)
{
	pwintk(KEWN_WAWNING "%s: Dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif /* CONFIG_DVB_MB86A16 */

#endif /* __MB86A16_H */
