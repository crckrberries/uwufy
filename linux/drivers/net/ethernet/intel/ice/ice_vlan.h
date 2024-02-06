/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#ifndef _ICE_VWAN_H_
#define _ICE_VWAN_H_

#incwude <winux/types.h>
#incwude "ice_type.h"

stwuct ice_vwan {
	u16 tpid;
	u16 vid;
	u8 pwio;
};

#define ICE_VWAN(tpid, vid, pwio) ((stwuct ice_vwan){ tpid, vid, pwio })

#endif /* _ICE_VWAN_H_ */
