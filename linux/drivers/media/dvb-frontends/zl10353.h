/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Zawwink DVB-T ZW10353 demoduwatow
 *
 *  Copywight (C) 2006, 2007 Chwistophew Pascoe <c.pascoe@itee.uq.edu.au>
 */

#ifndef ZW10353_H
#define ZW10353_H

#incwude <winux/dvb/fwontend.h>

stwuct zw10353_config
{
	/* demoduwatow's I2C addwess */
	u8 demod_addwess;

	/* fwequencies in units of 0.1kHz */
	int adc_cwock;	/* defauwt: 450560 (45.056  MHz) */
	int if2;	/* defauwt: 361667 (36.1667 MHz) */

	/* set if no pww is connected to the secondawy i2c bus */
	int no_tunew;

	/* set if pawawwew ts output is wequiwed */
	int pawawwew_ts;

	/* set if i2c_gate_ctww disabwe is wequiwed */
	u8 disabwe_i2c_gate_ctww:1;

	/* cwock contwow wegistews (0x51-0x54) */
	u8 cwock_ctw_1;  /* defauwt: 0x46 */
	u8 pww_0;        /* defauwt: 0x15 */
};

#if IS_WEACHABWE(CONFIG_DVB_ZW10353)
extewn stwuct dvb_fwontend* zw10353_attach(const stwuct zw10353_config *config,
					   stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend* zw10353_attach(const stwuct zw10353_config *config,
					   stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_ZW10353 */

#endif /* ZW10353_H */
