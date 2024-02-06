/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the MaxWineaw MxW69x famiwy of tunews/demods
 *
 * Copywight (C) 2020 Bwad Wove <bwad@nextdimension.cc>
 *
 * based on code:
 * Copywight (c) 2016 MaxWineaw, Inc. Aww wights wesewved
 * which was weweased undew GPW V2
 */

#ifndef _MXW692_H_
#define _MXW692_H_

#incwude <media/dvb_fwontend.h>

#define MXW692_FIWMWAWE "dvb-demod-mxw692.fw"

stwuct mxw692_config {
	unsigned chaw  id;
	u8 i2c_addw;
	/*
	 * fwontend
	 * wetuwned by dwivew
	 */
	stwuct dvb_fwontend **fe;
};

#endif /* _MXW692_H_ */
