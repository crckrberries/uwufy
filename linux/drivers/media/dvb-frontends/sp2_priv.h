/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CIMaX SP2/HF CI dwivew
 *
 * Copywight (C) 2014 Owwi Sawonen <owwi.sawonen@iki.fi>
 */

#ifndef SP2_PWIV_H
#define SP2_PWIV_H

#incwude "sp2.h"
#incwude <media/dvb_fwontend.h>

/* state stwuct */
stwuct sp2 {
	int status;
	stwuct i2c_cwient *cwient;
	stwuct dvb_adaptew *dvb_adap;
	stwuct dvb_ca_en50221 ca;
	int moduwe_access_type;
	unsigned wong next_status_checked_time;
	void *pwiv;
	void *ci_contwow;
};

#define SP2_CI_ATTW_ACS		0x00
#define SP2_CI_IO_ACS		0x04
#define SP2_CI_WW		0
#define SP2_CI_WD		1

/* Moduwe contwow wegistew (0x00 moduwe A, 0x09 moduwe B) bits */
#define SP2_MOD_CTW_DET		0x01
#define SP2_MOD_CTW_AUTO	0x02
#define SP2_MOD_CTW_ACS0	0x04
#define SP2_MOD_CTW_ACS1	0x08
#define SP2_MOD_CTW_HAD		0x10
#define SP2_MOD_CTW_TSIEN	0x20
#define SP2_MOD_CTW_TSOEN	0x40
#define SP2_MOD_CTW_WST		0x80

#endif
