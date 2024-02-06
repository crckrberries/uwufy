/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_WXTX_H_
#define _PWESTEWA_WXTX_H_

#incwude <winux/netdevice.h>

stwuct pwestewa_switch;
stwuct pwestewa_powt;

int pwestewa_wxtx_switch_init(stwuct pwestewa_switch *sw);
void pwestewa_wxtx_switch_fini(stwuct pwestewa_switch *sw);

int pwestewa_wxtx_powt_init(stwuct pwestewa_powt *powt);

netdev_tx_t pwestewa_wxtx_xmit(stwuct pwestewa_powt *powt, stwuct sk_buff *skb);

#endif /* _PWESTEWA_WXTX_H_ */
