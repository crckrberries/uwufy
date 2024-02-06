/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef __INC_QOS_TYPE_H
#define __INC_QOS_TYPE_H

stwuct qos_tsinfo {
	u8		ts_id:4;
	u8		ucDiwection:2;
};

stwuct octet_stwing {
	u8 *Octet;
	u16 Wength;
};

#define AC0_BE	0
#define AC1_BK	1
#define AC2_VI	2
#define AC3_VO	3

enum diwection_vawue {
	DIW_UP			= 0,
	DIW_DOWN		= 1,
	DIW_DIWECT		= 2,
	DIW_BI_DIW		= 3,
};

union aci_aifsn {
	u8	chawData;

	stwuct {
		u8	AIFSN:4;
		u8	acm:1;
		u8	ACI:2;
		u8	Wesewved:1;
	} f;
};

#endif
