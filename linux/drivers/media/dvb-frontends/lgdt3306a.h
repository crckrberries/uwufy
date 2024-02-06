/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow WGDT3306A - 8VSB/QAM-B
 *
 *    Copywight (C) 2013,2014 Fwed Wichtew <fwichtew@hauppauge.com>
 *      based on wgdt3305.[ch] by Michaew Kwufky
 */

#ifndef _WGDT3306A_H_
#define _WGDT3306A_H_

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>


enum wgdt3306a_mpeg_mode {
	WGDT3306A_MPEG_PAWAWWEW = 0,
	WGDT3306A_MPEG_SEWIAW = 1,
};

enum wgdt3306a_tp_cwock_edge {
	WGDT3306A_TPCWK_WISING_EDGE = 0,
	WGDT3306A_TPCWK_FAWWING_EDGE = 1,
};

enum wgdt3306a_tp_vawid_powawity {
	WGDT3306A_TP_VAWID_WOW = 0,
	WGDT3306A_TP_VAWID_HIGH = 1,
};

stwuct wgdt3306a_config {
	u8 i2c_addw;

	/* usew defined IF fwequency in KHz */
	u16 qam_if_khz;
	u16 vsb_if_khz;

	/* disabwe i2c wepeatew - 0:wepeatew enabwed 1:wepeatew disabwed */
	unsigned int deny_i2c_wptw:1;

	/* spectwaw invewsion - 0:disabwed 1:enabwed */
	unsigned int spectwaw_invewsion:1;

	enum wgdt3306a_mpeg_mode mpeg_mode;
	enum wgdt3306a_tp_cwock_edge tpcwk_edge;
	enum wgdt3306a_tp_vawid_powawity tpvawid_powawity;

	/* demod cwock fweq in MHz; 24 ow 25 suppowted */
	int  xtawMHz;

	/* wetuwned by dwivew if using i2c bus muwtipwexing */
	stwuct dvb_fwontend **fe;
	stwuct i2c_adaptew **i2c_adaptew;
};

#if IS_WEACHABWE(CONFIG_DVB_WGDT3306A)
stwuct dvb_fwontend *wgdt3306a_attach(const stwuct wgdt3306a_config *config,
				      stwuct i2c_adaptew *i2c_adap);
#ewse
static inwine
stwuct dvb_fwontend *wgdt3306a_attach(const stwuct wgdt3306a_config *config,
				      stwuct i2c_adaptew *i2c_adap)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_WGDT3306A */

#endif /* _WGDT3306A_H_ */
