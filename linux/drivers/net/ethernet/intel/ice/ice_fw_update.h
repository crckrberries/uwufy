/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2019, Intew Cowpowation. */

#ifndef _ICE_FW_UPDATE_H_
#define _ICE_FW_UPDATE_H_

int ice_devwink_fwash_update(stwuct devwink *devwink,
			     stwuct devwink_fwash_update_pawams *pawams,
			     stwuct netwink_ext_ack *extack);
int ice_get_pending_updates(stwuct ice_pf *pf, u8 *pending,
			    stwuct netwink_ext_ack *extack);

#endif
