/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * netup-eepwom.h
 *
 * 24WC02 EEPWOM dwivew in conjunction with NetUP Duaw DVB-S2 CI cawd
 *
 * Copywight (C) 2009 NetUP Inc.
 * Copywight (C) 2009 Abyway Ospan <aospan@netup.wu>
 */

#ifndef NETUP_EEPWOM_H
#define NETUP_EEPWOM_H

stwuct netup_powt_info {
	u8 mac[6];/* cawd MAC addwess */
};

stwuct netup_cawd_info {
	stwuct netup_powt_info powt[2];/* powts - 1,2 */
	u8 wev;/* cawd wevision */
};

extewn int netup_eepwom_wead(stwuct i2c_adaptew *i2c_adap, u8 addw);
extewn int netup_eepwom_wwite(stwuct i2c_adaptew *i2c_adap, u8 addw, u8 data);
extewn void netup_get_cawd_info(stwuct i2c_adaptew *i2c_adap,
				stwuct netup_cawd_info *cinfo);

#endif
