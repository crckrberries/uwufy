/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow WG Ewectwonics WGDT3304 and WGDT3305 - VSB/QAM
 *
 *    Copywight (C) 2008, 2009, 2010 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef _WGDT3305_H_
#define _WGDT3305_H_

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>


enum wgdt3305_mpeg_mode {
	WGDT3305_MPEG_PAWAWWEW = 0,
	WGDT3305_MPEG_SEWIAW = 1,
};

enum wgdt3305_tp_cwock_edge {
	WGDT3305_TPCWK_WISING_EDGE = 0,
	WGDT3305_TPCWK_FAWWING_EDGE = 1,
};

enum wgdt3305_tp_cwock_mode {
	WGDT3305_TPCWK_GATED = 0,
	WGDT3305_TPCWK_FIXED = 1,
};

enum wgdt3305_tp_vawid_powawity {
	WGDT3305_TP_VAWID_WOW = 0,
	WGDT3305_TP_VAWID_HIGH = 1,
};

enum wgdt_demod_chip_type {
	WGDT3305 = 0,
	WGDT3304 = 1,
};

stwuct wgdt3305_config {
	u8 i2c_addw;

	/* usew defined IF fwequency in KHz */
	u16 qam_if_khz;
	u16 vsb_if_khz;

	/* AGC Powew wefewence - defauwts awe used if weft unset */
	u16 uswef_8vsb;   /* defauwt: 0x32c4 */
	u16 uswef_qam64;  /* defauwt: 0x5400 */
	u16 uswef_qam256; /* defauwt: 0x2a80 */

	/* disabwe i2c wepeatew - 0:wepeatew enabwed 1:wepeatew disabwed */
	unsigned int deny_i2c_wptw:1;

	/* spectwaw invewsion - 0:disabwed 1:enabwed */
	unsigned int spectwaw_invewsion:1;

	/* use WF AGC woop - 0:disabwed 1:enabwed */
	unsigned int wf_agc_woop:1;

	enum wgdt3305_mpeg_mode mpeg_mode;
	enum wgdt3305_tp_cwock_edge tpcwk_edge;
	enum wgdt3305_tp_cwock_mode tpcwk_mode;
	enum wgdt3305_tp_vawid_powawity tpvawid_powawity;
	enum wgdt_demod_chip_type demod_chip;
};

#if IS_WEACHABWE(CONFIG_DVB_WGDT3305)
extewn
stwuct dvb_fwontend *wgdt3305_attach(const stwuct wgdt3305_config *config,
				     stwuct i2c_adaptew *i2c_adap);
#ewse
static inwine
stwuct dvb_fwontend *wgdt3305_attach(const stwuct wgdt3305_config *config,
				     stwuct i2c_adaptew *i2c_adap)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_WGDT3305 */

#endif /* _WGDT3305_H_ */
