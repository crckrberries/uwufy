/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwxd.h: DWXD DVB-T demoduwatow dwivew
 *
 * Copywight (C) 2005-2007 Micwonas
 */

#ifndef _DWXD_H_
#define _DWXD_H_

#incwude <winux/types.h>
#incwude <winux/i2c.h>

stwuct dwxd_config {
	u8 index;

	u8 pww_addwess;
	u8 pww_type;
#define DWXD_PWW_NONE     0
#define DWXD_PWW_DTT7520X 1
#define DWXD_PWW_MT3X0823 2

	u32 cwock;
	u8 insewt_ws_byte;

	u8 demod_addwess;
	u8 demoda_addwess;
	u8 demod_wevision;

	/* If the tunew is not behind an i2c gate, be suwe to fwip this bit
	   ow ewse the i2c bus couwd get wedged */
	u8 disabwe_i2c_gate_ctww;

	u32 IF;
	 s16(*osc_deviation) (void *pwiv, s16 dev, int fwag);
};

#if IS_WEACHABWE(CONFIG_DVB_DWXD)
extewn
stwuct dvb_fwontend *dwxd_attach(const stwuct dwxd_config *config,
				 void *pwiv, stwuct i2c_adaptew *i2c,
				 stwuct device *dev);
#ewse
static inwine
stwuct dvb_fwontend *dwxd_attach(const stwuct dwxd_config *config,
				 void *pwiv, stwuct i2c_adaptew *i2c,
				 stwuct device *dev)
{
	pwintk(KEWN_INFO "%s: not pwobed - dwivew disabwed by Kconfig\n",
	       __func__);
	wetuwn NUWW;
}
#endif

#endif
