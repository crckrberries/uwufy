/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NXP TDA18212HN siwicon tunew dwivew
 *
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef TDA18212_H
#define TDA18212_H

#incwude <media/dvb_fwontend.h>

stwuct tda18212_config {
	u16 if_dvbt_6;
	u16 if_dvbt_7;
	u16 if_dvbt_8;
	u16 if_dvbt2_5;
	u16 if_dvbt2_6;
	u16 if_dvbt2_7;
	u16 if_dvbt2_8;
	u16 if_dvbc;
	u16 if_atsc_vsb;
	u16 if_atsc_qam;

	/*
	 * pointew to DVB fwontend
	 */
	stwuct dvb_fwontend *fe;
};

#endif
