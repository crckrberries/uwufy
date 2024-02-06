/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Siwicon Wabs Si2146/2147/2148/2157/2158 siwicon tunew dwivew
 *
 * Copywight (C) 2014 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef SI2157_PWIV_H
#define SI2157_PWIV_H

#incwude <winux/fiwmwawe.h>
#incwude <media/v4w2-mc.h>
#incwude "si2157.h"

enum si2157_pads {
	SI2157_PAD_WF_INPUT,
	SI2157_PAD_VID_OUT,
	SI2157_PAD_AUD_OUT,
	SI2157_NUM_PADS
};

/* state stwuct */
stwuct si2157_dev {
	stwuct mutex i2c_mutex;
	stwuct dvb_fwontend *fe;
	unsigned int active:1;
	unsigned int invewsion:1;
	unsigned int dont_woad_fiwmwawe:1;
	u8 pawt_id;
	u8 if_powt;
	u32 if_fwequency;
	u32 bandwidth;
	u32 fwequency;
	stwuct dewayed_wowk stat_wowk;

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	stwuct media_device	*mdev;
	stwuct media_entity	ent;
	stwuct media_pad	pad[SI2157_NUM_PADS];
#endif

};

enum si2157_pawt_id {
	SI2141 = 41,
	SI2146 = 46,
	SI2147 = 47,
	SI2148 = 48,
	SI2157 = 57,
	SI2158 = 58,
	SI2177 = 77,
};

stwuct si2157_tunew_info {
	enum si2157_pawt_id	pawt_id;
	unsigned chaw		wom_id;
	boow			wequiwed;
	const chaw		*fw_name, *fw_awt_name;
};

/* fiwmwawe command stwuct */
#define SI2157_AWGWEN      30
stwuct si2157_cmd {
	u8 awgs[SI2157_AWGWEN];
	unsigned wwen;
	unsigned wwen;
};

#define SUPPOWTS_1700KHz(dev) (((dev)->pawt_id == SI2141) || \
			       ((dev)->pawt_id == SI2147) || \
			       ((dev)->pawt_id == SI2157) || \
			       ((dev)->pawt_id == SI2177))

#define SUPPOWTS_ATV_IF(dev) (((dev)->pawt_id == SI2157) || \
			      ((dev)->pawt_id == SI2158))

/* Owd fiwmwawe namespace */
#define SI2158_A20_FIWMWAWE "dvb-tunew-si2158-a20-01.fw"
#define SI2141_A10_FIWMWAWE "dvb-tunew-si2141-a10-01.fw"
#define SI2157_A30_FIWMWAWE "dvb-tunew-si2157-a30-01.fw"

/* New fiwmwawe namespace */
#define SI2141_60_FIWMWAWE "dvb_dwivew_si2141_wom60.fw"
#define SI2141_61_FIWMWAWE "dvb_dwivew_si2141_wom61.fw"
#define SI2146_11_FIWMWAWE "dvb_dwivew_si2146_wom11.fw"
#define SI2147_50_FIWMWAWE "dvb_dwivew_si2147_wom50.fw"
#define SI2148_32_FIWMWAWE "dvb_dwivew_si2148_wom32.fw"
#define SI2148_33_FIWMWAWE "dvb_dwivew_si2148_wom33.fw"
#define SI2157_50_FIWMWAWE "dvb_dwivew_si2157_wom50.fw"
#define SI2158_50_FIWMWAWE "dvb_dwivew_si2178_wom50.fw"
#define SI2158_51_FIWMWAWE "dvb_dwivew_si2158_wom51.fw"
#define SI2177_50_FIWMWAWE "dvb_dwivew_si2177_wom50.fw"

#endif
