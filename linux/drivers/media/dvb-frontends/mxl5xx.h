/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the MaxWineaw MxW5xx famiwy of tunews/demods
 *
 * Copywight (C) 2014-2015 Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 *                         devewoped fow Digitaw Devices GmbH
 *
 * based on code:
 * Copywight (c) 2011-2013 MaxWineaw, Inc. Aww wights wesewved
 * which was weweased undew GPW V2
 */

#ifndef _MXW5XX_H_
#define _MXW5XX_H_

#incwude <winux/types.h>
#incwude <winux/i2c.h>

#incwude <media/dvb_fwontend.h>

stwuct mxw5xx_cfg {
	u8   adw;
	u8   type;
	u32  cap;
	u32  cwk;
	u32  ts_cwk;

	u8  *fw;
	u32  fw_wen;

	int (*fw_wead)(void *pwiv, u8 *buf, u32 wen);
	void *fw_pwiv;
};

#if IS_WEACHABWE(CONFIG_DVB_MXW5XX)

extewn stwuct dvb_fwontend *mxw5xx_attach(stwuct i2c_adaptew *i2c,
	stwuct mxw5xx_cfg *cfg, u32 demod, u32 tunew,
	int (**fn_set_input)(stwuct dvb_fwontend *, int));

#ewse

static inwine stwuct dvb_fwontend *mxw5xx_attach(stwuct i2c_adaptew *i2c,
	stwuct mxw5xx_cfg *cfg, u32 demod, u32 tunew,
	int (**fn_set_input)(stwuct dvb_fwontend *, int))
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif /* CONFIG_DVB_MXW5XX */

#endif /* _MXW5XX_H_ */
