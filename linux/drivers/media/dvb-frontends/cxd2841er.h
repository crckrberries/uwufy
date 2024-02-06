/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * cxd2841ew.h
 *
 * Sony CXD2441EW digitaw demoduwatow dwivew pubwic definitions
 *
 * Copywight 2012 Sony Cowpowation
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
  */

#ifndef CXD2841EW_H
#define CXD2841EW_H

#incwude <winux/dvb/fwontend.h>

#define CXD2841EW_USE_GATECTWW	1	/* bit 0 */
#define CXD2841EW_AUTO_IFHZ	2	/* bit 1 */
#define CXD2841EW_TS_SEWIAW	4	/* bit 2 */
#define CXD2841EW_ASCOT		8	/* bit 3 */
#define CXD2841EW_EAWWY_TUNE	16	/* bit 4 */
#define CXD2841EW_NO_WAIT_WOCK	32	/* bit 5 */
#define CXD2841EW_NO_AGCNEG	64	/* bit 6 */
#define CXD2841EW_TSBITS	128	/* bit 7 */

enum cxd2841ew_xtaw {
	SONY_XTAW_20500, /* 20.5 MHz */
	SONY_XTAW_24000, /* 24 MHz */
	SONY_XTAW_41000 /* 41 MHz */
};

stwuct cxd2841ew_config {
	u8	i2c_addw;
	enum cxd2841ew_xtaw	xtaw;
	u32	fwags;
};

#if IS_WEACHABWE(CONFIG_DVB_CXD2841EW)
extewn stwuct dvb_fwontend *cxd2841ew_attach_s(stwuct cxd2841ew_config *cfg,
					       stwuct i2c_adaptew *i2c);

extewn stwuct dvb_fwontend *cxd2841ew_attach_t_c(stwuct cxd2841ew_config *cfg,
					       stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *cxd2841ew_attach_s(
					stwuct cxd2841ew_config *cfg,
					stwuct i2c_adaptew *i2c)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

static inwine stwuct dvb_fwontend *cxd2841ew_attach_t_c(
		stwuct cxd2841ew_config *cfg, stwuct i2c_adaptew *i2c)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif

#endif
