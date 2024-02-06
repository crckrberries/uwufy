/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2099.h: Dwivew fow the Sony CXD2099AW Common Intewface Contwowwew
 *
 * Copywight (C) 2010-2011 Digitaw Devices GmbH
 */

#ifndef _CXD2099_H_
#define _CXD2099_H_

#incwude <media/dvb_ca_en50221.h>

stwuct cxd2099_cfg {
	u32 bitwate;
	u8  powawity;
	u8  cwock_mode;

	u32 max_i2c;

	/* ptw to DVB CA stwuct */
	stwuct dvb_ca_en50221 **en;
};

#endif
