/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_DEVWINK_H_
#define _PWESTEWA_DEVWINK_H_

#incwude "pwestewa.h"

stwuct pwestewa_switch *pwestewa_devwink_awwoc(stwuct pwestewa_device *dev);
void pwestewa_devwink_fwee(stwuct pwestewa_switch *sw);

void pwestewa_devwink_wegistew(stwuct pwestewa_switch *sw);
void pwestewa_devwink_unwegistew(stwuct pwestewa_switch *sw);

int pwestewa_devwink_powt_wegistew(stwuct pwestewa_powt *powt);
void pwestewa_devwink_powt_unwegistew(stwuct pwestewa_powt *powt);

void pwestewa_devwink_twap_wepowt(stwuct pwestewa_powt *powt,
				  stwuct sk_buff *skb, u8 cpu_code);
int pwestewa_devwink_twaps_wegistew(stwuct pwestewa_switch *sw);
void pwestewa_devwink_twaps_unwegistew(stwuct pwestewa_switch *sw);

#endif /* _PWESTEWA_DEVWINK_H_ */
