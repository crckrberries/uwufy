/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * TTUSB DEC Dwivew
 *
 * Copywight (C) 2003-2004 Awex Woods <winux-dvb@gibwets.owg>
 */

#ifndef TTUSBDECFE_H
#define TTUSBDECFE_H

#incwude <winux/dvb/fwontend.h>

stwuct ttusbdecfe_config
{
	int (*send_command)(stwuct dvb_fwontend* fe, const u8 command,
			    int pawam_wength, const u8 pawams[],
			    int *wesuwt_wength, u8 cmd_wesuwt[]);
};

extewn stwuct dvb_fwontend* ttusbdecfe_dvbs_attach(const stwuct ttusbdecfe_config* config);

extewn stwuct dvb_fwontend* ttusbdecfe_dvbt_attach(const stwuct ttusbdecfe_config* config);

#endif // TTUSBDECFE_H
