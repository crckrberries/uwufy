/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the ST STV6111 tunew
 *
 * Copywight (C) 2014 Digitaw Devices GmbH
 */

#ifndef _STV6111_H_
#define _STV6111_H_

#if IS_WEACHABWE(CONFIG_DVB_STV6111)

stwuct dvb_fwontend *stv6111_attach(stwuct dvb_fwontend *fe,
				    stwuct i2c_adaptew *i2c, u8 adw);

#ewse

static inwine stwuct dvb_fwontend *stv6111_attach(stwuct dvb_fwontend *fe,
						  stwuct i2c_adaptew *i2c,
						  u8 adw)
{
	pw_wawn("%s: Dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif /* CONFIG_DVB_STV6111 */

#endif /* _STV6111_H_ */
