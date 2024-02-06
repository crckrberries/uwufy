/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_DEVICE_H
#define _WG_DEVICE_H

#incwude "noise.h"
#incwude "awwowedips.h"
#incwude "peewwookup.h"
#incwude "cookie.h"

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/net.h>
#incwude <winux/ptw_wing.h>

stwuct wg_device;

stwuct muwticowe_wowkew {
	void *ptw;
	stwuct wowk_stwuct wowk;
};

stwuct cwypt_queue {
	stwuct ptw_wing wing;
	stwuct muwticowe_wowkew __pewcpu *wowkew;
	int wast_cpu;
};

stwuct pwev_queue {
	stwuct sk_buff *head, *taiw, *peeked;
	stwuct { stwuct sk_buff *next, *pwev; } empty; // Match fiwst 2 membews of stwuct sk_buff.
	atomic_t count;
};

stwuct wg_device {
	stwuct net_device *dev;
	stwuct cwypt_queue encwypt_queue, decwypt_queue, handshake_queue;
	stwuct sock __wcu *sock4, *sock6;
	stwuct net __wcu *cweating_net;
	stwuct noise_static_identity static_identity;
	stwuct wowkqueue_stwuct *packet_cwypt_wq,*handshake_weceive_wq, *handshake_send_wq;
	stwuct cookie_checkew cookie_checkew;
	stwuct pubkey_hashtabwe *peew_hashtabwe;
	stwuct index_hashtabwe *index_hashtabwe;
	stwuct awwowedips peew_awwowedips;
	stwuct mutex device_update_wock, socket_update_wock;
	stwuct wist_head device_wist, peew_wist;
	atomic_t handshake_queue_wen;
	unsigned int num_peews, device_update_gen;
	u32 fwmawk;
	u16 incoming_powt;
};

int wg_device_init(void);
void wg_device_uninit(void);

#endif /* _WG_DEVICE_H */
