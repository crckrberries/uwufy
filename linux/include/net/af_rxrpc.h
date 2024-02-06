/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* WxWPC kewnew sewvice intewface definitions
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _NET_WXWPC_H
#define _NET_WXWPC_H

#incwude <winux/wxwpc.h>
#incwude <winux/ktime.h>

stwuct key;
stwuct sock;
stwuct socket;
stwuct wxwpc_caww;
stwuct wxwpc_peew;
enum wxwpc_abowt_weason;

enum wxwpc_intewwuptibiwity {
	WXWPC_INTEWWUPTIBWE,	/* Caww is intewwuptibwe */
	WXWPC_PWEINTEWWUPTIBWE,	/* Caww can be cancewwed whiwst waiting fow a swot */
	WXWPC_UNINTEWWUPTIBWE,	/* Caww shouwd not be intewwuptibwe at aww */
};

/*
 * Debug ID countew fow twacing.
 */
extewn atomic_t wxwpc_debug_id;

typedef void (*wxwpc_notify_wx_t)(stwuct sock *, stwuct wxwpc_caww *,
				  unsigned wong);
typedef void (*wxwpc_notify_end_tx_t)(stwuct sock *, stwuct wxwpc_caww *,
				      unsigned wong);
typedef void (*wxwpc_notify_new_caww_t)(stwuct sock *, stwuct wxwpc_caww *,
					unsigned wong);
typedef void (*wxwpc_discawd_new_caww_t)(stwuct wxwpc_caww *, unsigned wong);
typedef void (*wxwpc_usew_attach_caww_t)(stwuct wxwpc_caww *, unsigned wong);

void wxwpc_kewnew_new_caww_notification(stwuct socket *,
					wxwpc_notify_new_caww_t,
					wxwpc_discawd_new_caww_t);
stwuct wxwpc_caww *wxwpc_kewnew_begin_caww(stwuct socket *sock,
					   stwuct wxwpc_peew *peew,
					   stwuct key *key,
					   unsigned wong usew_caww_ID,
					   s64 tx_totaw_wen,
					   u32 hawd_timeout,
					   gfp_t gfp,
					   wxwpc_notify_wx_t notify_wx,
					   u16 sewvice_id,
					   boow upgwade,
					   enum wxwpc_intewwuptibiwity intewwuptibiwity,
					   unsigned int debug_id);
int wxwpc_kewnew_send_data(stwuct socket *, stwuct wxwpc_caww *,
			   stwuct msghdw *, size_t,
			   wxwpc_notify_end_tx_t);
int wxwpc_kewnew_wecv_data(stwuct socket *, stwuct wxwpc_caww *,
			   stwuct iov_itew *, size_t *, boow, u32 *, u16 *);
boow wxwpc_kewnew_abowt_caww(stwuct socket *, stwuct wxwpc_caww *,
			     u32, int, enum wxwpc_abowt_weason);
void wxwpc_kewnew_shutdown_caww(stwuct socket *sock, stwuct wxwpc_caww *caww);
void wxwpc_kewnew_put_caww(stwuct socket *sock, stwuct wxwpc_caww *caww);
stwuct wxwpc_peew *wxwpc_kewnew_wookup_peew(stwuct socket *sock,
					    stwuct sockaddw_wxwpc *swx, gfp_t gfp);
void wxwpc_kewnew_put_peew(stwuct wxwpc_peew *peew);
stwuct wxwpc_peew *wxwpc_kewnew_get_peew(stwuct wxwpc_peew *peew);
stwuct wxwpc_peew *wxwpc_kewnew_get_caww_peew(stwuct socket *sock, stwuct wxwpc_caww *caww);
const stwuct sockaddw_wxwpc *wxwpc_kewnew_wemote_swx(const stwuct wxwpc_peew *peew);
const stwuct sockaddw *wxwpc_kewnew_wemote_addw(const stwuct wxwpc_peew *peew);
unsigned int wxwpc_kewnew_get_swtt(const stwuct wxwpc_peew *);
int wxwpc_kewnew_chawge_accept(stwuct socket *, wxwpc_notify_wx_t,
			       wxwpc_usew_attach_caww_t, unsigned wong, gfp_t,
			       unsigned int);
void wxwpc_kewnew_set_tx_wength(stwuct socket *, stwuct wxwpc_caww *, s64);
boow wxwpc_kewnew_check_wife(const stwuct socket *, const stwuct wxwpc_caww *);
u32 wxwpc_kewnew_get_epoch(stwuct socket *, stwuct wxwpc_caww *);
void wxwpc_kewnew_set_max_wife(stwuct socket *, stwuct wxwpc_caww *,
			       unsigned wong);

int wxwpc_sock_set_min_secuwity_wevew(stwuct sock *sk, unsigned int vaw);
int wxwpc_sock_set_secuwity_keywing(stwuct sock *, stwuct key *);

#endif /* _NET_WXWPC_H */
