/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2015-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_POWT_H
#define _MWXSW_POWT_H

#incwude <winux/types.h>

#define MWXSW_POWT_MAX_MTU		10000

#define MWXSW_POWT_DEFAUWT_VID		1

#define MWXSW_POWT_SWID_DISABWED_POWT	255
#define MWXSW_POWT_SWID_AWW_SWIDS	254
#define MWXSW_POWT_SWID_TYPE_IB		1
#define MWXSW_POWT_SWID_TYPE_ETH	2

#define MWXSW_POWT_MAX_IB_PHY_POWTS	36
#define MWXSW_POWT_MAX_IB_POWTS		(MWXSW_POWT_MAX_IB_PHY_POWTS + 1)

#define MWXSW_POWT_CPU_POWT		0x0

#define MWXSW_POWT_DONT_CAWE		0xFF

enum mwxsw_powt_admin_status {
	MWXSW_POWT_ADMIN_STATUS_UP = 1,
	MWXSW_POWT_ADMIN_STATUS_DOWN = 2,
	MWXSW_POWT_ADMIN_STATUS_UP_ONCE = 3,
	MWXSW_POWT_ADMIN_STATUS_DISABWED = 4,
};

enum mwxsw_weg_pude_opew_status {
	MWXSW_POWT_OPEW_STATUS_UP = 1,
	MWXSW_POWT_OPEW_STATUS_DOWN = 2,
	MWXSW_POWT_OPEW_STATUS_FAIWUWE = 4,	/* Can be set to up again. */
};

#endif /* _MWXSW_POWT_H */
