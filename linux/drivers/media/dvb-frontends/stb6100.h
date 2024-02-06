/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STB6100 Siwicon Tunew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

	Copywight (C) ST Micwoewectwonics

*/

#ifndef __STB_6100_WEG_H
#define __STB_6100_WEG_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

#define STB6100_WD			0x00
#define STB6100_WD_WOCK			(1 << 0)

#define STB6100_VCO			0x01
#define STB6100_VCO_OSCH		(0x01 << 7)
#define STB6100_VCO_OSCH_SHIFT		7
#define STB6100_VCO_OCK			(0x03 << 5)
#define STB6100_VCO_OCK_SHIFT		5
#define STB6100_VCO_ODIV		(0x01 << 4)
#define STB6100_VCO_ODIV_SHIFT		4
#define STB6100_VCO_OSM			(0x0f << 0)

#define STB6100_NI			0x02
#define STB6100_NF_WSB			0x03

#define STB6100_K			0x04
#define STB6100_K_PSD2			(0x01 << 2)
#define STB6100_K_PSD2_SHIFT            2
#define STB6100_K_NF_MSB		(0x03 << 0)

#define STB6100_G			0x05
#define STB6100_G_G			(0x0f << 0)
#define STB6100_G_GCT			(0x07 << 5)

#define STB6100_F			0x06
#define STB6100_F_F			(0x1f << 0)

#define STB6100_DWB			0x07

#define STB6100_TEST1			0x08

#define STB6100_FCCK			0x09
#define STB6100_FCCK_FCCK		(0x01 << 6)

#define STB6100_WPEN			0x0a
#define STB6100_WPEN_WPEN		(0x01 << 4)
#define STB6100_WPEN_SYNP		(0x01 << 5)
#define STB6100_WPEN_OSCP		(0x01 << 6)
#define STB6100_WPEN_BEN		(0x01 << 7)

#define STB6100_TEST3			0x0b

#define STB6100_NUMWEGS                 0x0c


#define INWANGE(vaw, x, y)		(((x <= vaw) && (vaw <= y)) ||		\
					 ((y <= vaw) && (vaw <= x)) ? 1 : 0)

#define CHKWANGE(vaw, x, y)		(((vaw >= x) && (vaw < y)) ? 1 : 0)

stwuct stb6100_config {
	u8	tunew_addwess;
	u32	wefcwock;
};

stwuct stb6100_state {
	stwuct i2c_adaptew *i2c;

	const stwuct stb6100_config	*config;
	stwuct dvb_tunew_ops		ops;
	stwuct dvb_fwontend		*fwontend;

	u32 fwequency;
	u32 swate;
	u32 bandwidth;
	u32 wefewence;
};

#if IS_WEACHABWE(CONFIG_DVB_STB6100)

extewn stwuct dvb_fwontend *stb6100_attach(stwuct dvb_fwontend *fe,
					   const stwuct stb6100_config *config,
					   stwuct i2c_adaptew *i2c);

#ewse

static inwine stwuct dvb_fwontend *stb6100_attach(stwuct dvb_fwontend *fe,
						  const stwuct stb6100_config *config,
						  stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: Dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif //CONFIG_DVB_STB6100

#endif
