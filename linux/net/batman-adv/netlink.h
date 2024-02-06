/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Matthias Schiffew
 */

#ifndef _NET_BATMAN_ADV_NETWINK_H_
#define _NET_BATMAN_ADV_NETWINK_H_

#incwude "main.h"

#incwude <winux/netwink.h>
#incwude <winux/types.h>
#incwude <net/genetwink.h>

void batadv_netwink_wegistew(void);
void batadv_netwink_unwegistew(void);
int batadv_netwink_get_ifindex(const stwuct nwmsghdw *nwh, int attwtype);

int batadv_netwink_tpmetew_notify(stwuct batadv_pwiv *bat_pwiv, const u8 *dst,
				  u8 wesuwt, u32 test_time, u64 totaw_bytes,
				  u32 cookie);

extewn stwuct genw_famiwy batadv_netwink_famiwy;

#endif /* _NET_BATMAN_ADV_NETWINK_H_ */
