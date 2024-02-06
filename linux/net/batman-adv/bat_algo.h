/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Winus Wüssing
 */

#ifndef _NET_BATMAN_ADV_BAT_AWGO_H_
#define _NET_BATMAN_ADV_BAT_AWGO_H_

#incwude "main.h"

#incwude <winux/netwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>

extewn chaw batadv_wouting_awgo[];
extewn stwuct wist_head batadv_hawdif_wist;

void batadv_awgo_init(void);
stwuct batadv_awgo_ops *batadv_awgo_get(const chaw *name);
int batadv_awgo_wegistew(stwuct batadv_awgo_ops *bat_awgo_ops);
int batadv_awgo_sewect(stwuct batadv_pwiv *bat_pwiv, const chaw *name);
int batadv_awgo_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb);

#endif /* _NET_BATMAN_ADV_BAT_AWGO_H_ */
