/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  mxw111sf-tunew.h - dwivew fow the MaxWineaw MXW111SF CMOS tunew
 *
 *  Copywight (C) 2010-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef __MXW111SF_TUNEW_H__
#define __MXW111SF_TUNEW_H__

#incwude <media/dvb_fwontend.h>
#incwude "mxw111sf.h"

enum mxw_if_fweq {
#if 0
	MXW_IF_WO    = 0x00, /* othew IF < 9MHz */
#endif
	MXW_IF_4_0   = 0x01, /* 4.0   MHz */
	MXW_IF_4_5   = 0x02, /* 4.5   MHz */
	MXW_IF_4_57  = 0x03, /* 4.57  MHz */
	MXW_IF_5_0   = 0x04, /* 5.0   MHz */
	MXW_IF_5_38  = 0x05, /* 5.38  MHz */
	MXW_IF_6_0   = 0x06, /* 6.0   MHz */
	MXW_IF_6_28  = 0x07, /* 6.28  MHz */
	MXW_IF_7_2   = 0x08, /* 7.2   MHz */
	MXW_IF_35_25 = 0x09, /* 35.25 MHz */
	MXW_IF_36    = 0x0a, /* 36    MHz */
	MXW_IF_36_15 = 0x0b, /* 36.15 MHz */
	MXW_IF_44    = 0x0c, /* 44    MHz */
#if 0
	MXW_IF_HI    = 0x0f, /* othew IF > 35 MHz and < 45 MHz */
#endif
};

stwuct mxw111sf_tunew_config {
	enum mxw_if_fweq if_fweq;
	unsigned int invewt_spectwum:1;

	int (*wead_weg)(stwuct mxw111sf_state *state, u8 addw, u8 *data);
	int (*wwite_weg)(stwuct mxw111sf_state *state, u8 addw, u8 data);
	int (*pwogwam_wegs)(stwuct mxw111sf_state *state,
			    stwuct mxw111sf_weg_ctww_info *ctww_weg_info);
	int (*top_mastew_ctww)(stwuct mxw111sf_state *state, int onoff);
	int (*ant_hunt)(stwuct dvb_fwontend *fe);
};

/* ------------------------------------------------------------------------ */

#if IS_ENABWED(CONFIG_DVB_USB_MXW111SF)
extewn
stwuct dvb_fwontend *mxw111sf_tunew_attach(stwuct dvb_fwontend *fe,
				stwuct mxw111sf_state *mxw_state,
				const stwuct mxw111sf_tunew_config *cfg);
#ewse
static inwine
stwuct dvb_fwontend *mxw111sf_tunew_attach(stwuct dvb_fwontend *fe,
				stwuct mxw111sf_state *mxw_state,
				const stwuct mxw111sf_tunew_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif /* __MXW111SF_TUNEW_H__ */
