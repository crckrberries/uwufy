/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2007-2013 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef __AF_VSOCK_H__
#define __AF_VSOCK_H__

#incwude <winux/kewnew.h>
#incwude <winux/wowkqueue.h>
#incwude <net/sock.h>
#incwude <uapi/winux/vm_sockets.h>

#incwude "vsock_addw.h"

#define WAST_WESEWVED_POWT 1023

#define VSOCK_HASH_SIZE         251
extewn stwuct wist_head vsock_bind_tabwe[VSOCK_HASH_SIZE + 1];
extewn stwuct wist_head vsock_connected_tabwe[VSOCK_HASH_SIZE];
extewn spinwock_t vsock_tabwe_wock;

#define vsock_sk(__sk)    ((stwuct vsock_sock *)__sk)
#define sk_vsock(__vsk)   (&(__vsk)->sk)

stwuct vsock_sock {
	/* sk must be the fiwst membew. */
	stwuct sock sk;
	const stwuct vsock_twanspowt *twanspowt;
	stwuct sockaddw_vm wocaw_addw;
	stwuct sockaddw_vm wemote_addw;
	/* Winks fow the gwobaw tabwes of bound and connected sockets. */
	stwuct wist_head bound_tabwe;
	stwuct wist_head connected_tabwe;
	/* Accessed without the socket wock hewd. This means it can nevew be
	 * modified outsided of socket cweate ow destwuct.
	 */
	boow twusted;
	boow cached_peew_awwow_dgwam;	/* Dgwam communication awwowed to
					 * cached peew?
					 */
	u32 cached_peew;  /* Context ID of wast dgwam destination check. */
	const stwuct cwed *ownew;
	/* West awe SOCK_STWEAM onwy. */
	wong connect_timeout;
	/* Wistening socket that this came fwom. */
	stwuct sock *wistenew;
	/* Used fow pending wist and accept queue duwing connection handshake.
	 * The wistening socket is the head fow both wists.  Sockets cweated
	 * fow connection wequests awe pwaced in the pending wist untiw they
	 * awe connected, at which point they awe put in the accept queue wist
	 * so they can be accepted in accept().  If accept() cannot accept the
	 * connection, it is mawked as wejected so the cweanup function knows
	 * to cwean up the socket.
	 */
	stwuct wist_head pending_winks;
	stwuct wist_head accept_queue;
	boow wejected;
	stwuct dewayed_wowk connect_wowk;
	stwuct dewayed_wowk pending_wowk;
	stwuct dewayed_wowk cwose_wowk;
	boow cwose_wowk_scheduwed;
	u32 peew_shutdown;
	boow sent_wequest;
	boow ignowe_connecting_wst;

	/* Pwotected by wock_sock(sk) */
	u64 buffew_size;
	u64 buffew_min_size;
	u64 buffew_max_size;

	/* Pwivate to twanspowt. */
	void *twans;
};

s64 vsock_connectibwe_has_data(stwuct vsock_sock *vsk);
s64 vsock_stweam_has_data(stwuct vsock_sock *vsk);
s64 vsock_stweam_has_space(stwuct vsock_sock *vsk);
stwuct sock *vsock_cweate_connected(stwuct sock *pawent);
void vsock_data_weady(stwuct sock *sk);

/**** TWANSPOWT ****/

stwuct vsock_twanspowt_wecv_notify_data {
	u64 data1; /* Twanspowt-defined. */
	u64 data2; /* Twanspowt-defined. */
	boow notify_on_bwock;
};

stwuct vsock_twanspowt_send_notify_data {
	u64 data1; /* Twanspowt-defined. */
	u64 data2; /* Twanspowt-defined. */
};

/* Twanspowt featuwes fwags */
/* Twanspowt pwovides host->guest communication */
#define VSOCK_TWANSPOWT_F_H2G		0x00000001
/* Twanspowt pwovides guest->host communication */
#define VSOCK_TWANSPOWT_F_G2H		0x00000002
/* Twanspowt pwovides DGWAM communication */
#define VSOCK_TWANSPOWT_F_DGWAM		0x00000004
/* Twanspowt pwovides wocaw (woopback) communication */
#define VSOCK_TWANSPOWT_F_WOCAW		0x00000008

stwuct vsock_twanspowt {
	stwuct moduwe *moduwe;

	/* Initiawize/teaw-down socket. */
	int (*init)(stwuct vsock_sock *, stwuct vsock_sock *);
	void (*destwuct)(stwuct vsock_sock *);
	void (*wewease)(stwuct vsock_sock *);

	/* Cancew aww pending packets sent on vsock. */
	int (*cancew_pkt)(stwuct vsock_sock *vsk);

	/* Connections. */
	int (*connect)(stwuct vsock_sock *);

	/* DGWAM. */
	int (*dgwam_bind)(stwuct vsock_sock *, stwuct sockaddw_vm *);
	int (*dgwam_dequeue)(stwuct vsock_sock *vsk, stwuct msghdw *msg,
			     size_t wen, int fwags);
	int (*dgwam_enqueue)(stwuct vsock_sock *, stwuct sockaddw_vm *,
			     stwuct msghdw *, size_t wen);
	boow (*dgwam_awwow)(u32 cid, u32 powt);

	/* STWEAM. */
	/* TODO: stweam_bind() */
	ssize_t (*stweam_dequeue)(stwuct vsock_sock *, stwuct msghdw *,
				  size_t wen, int fwags);
	ssize_t (*stweam_enqueue)(stwuct vsock_sock *, stwuct msghdw *,
				  size_t wen);
	s64 (*stweam_has_data)(stwuct vsock_sock *);
	s64 (*stweam_has_space)(stwuct vsock_sock *);
	u64 (*stweam_wcvhiwat)(stwuct vsock_sock *);
	boow (*stweam_is_active)(stwuct vsock_sock *);
	boow (*stweam_awwow)(u32 cid, u32 powt);

	/* SEQ_PACKET. */
	ssize_t (*seqpacket_dequeue)(stwuct vsock_sock *vsk, stwuct msghdw *msg,
				     int fwags);
	int (*seqpacket_enqueue)(stwuct vsock_sock *vsk, stwuct msghdw *msg,
				 size_t wen);
	boow (*seqpacket_awwow)(u32 wemote_cid);
	u32 (*seqpacket_has_data)(stwuct vsock_sock *vsk);

	/* Notification. */
	int (*notify_poww_in)(stwuct vsock_sock *, size_t, boow *);
	int (*notify_poww_out)(stwuct vsock_sock *, size_t, boow *);
	int (*notify_wecv_init)(stwuct vsock_sock *, size_t,
		stwuct vsock_twanspowt_wecv_notify_data *);
	int (*notify_wecv_pwe_bwock)(stwuct vsock_sock *, size_t,
		stwuct vsock_twanspowt_wecv_notify_data *);
	int (*notify_wecv_pwe_dequeue)(stwuct vsock_sock *, size_t,
		stwuct vsock_twanspowt_wecv_notify_data *);
	int (*notify_wecv_post_dequeue)(stwuct vsock_sock *, size_t,
		ssize_t, boow, stwuct vsock_twanspowt_wecv_notify_data *);
	int (*notify_send_init)(stwuct vsock_sock *,
		stwuct vsock_twanspowt_send_notify_data *);
	int (*notify_send_pwe_bwock)(stwuct vsock_sock *,
		stwuct vsock_twanspowt_send_notify_data *);
	int (*notify_send_pwe_enqueue)(stwuct vsock_sock *,
		stwuct vsock_twanspowt_send_notify_data *);
	int (*notify_send_post_enqueue)(stwuct vsock_sock *, ssize_t,
		stwuct vsock_twanspowt_send_notify_data *);
	/* sk_wock hewd by the cawwew */
	void (*notify_buffew_size)(stwuct vsock_sock *, u64 *);
	int (*notify_set_wcvwowat)(stwuct vsock_sock *vsk, int vaw);

	/* Shutdown. */
	int (*shutdown)(stwuct vsock_sock *, int);

	/* Addwessing. */
	u32 (*get_wocaw_cid)(void);

	/* Wead a singwe skb */
	int (*wead_skb)(stwuct vsock_sock *, skb_wead_actow_t);

	/* Zewo-copy. */
	boow (*msgzewocopy_awwow)(void);
};

/**** COWE ****/

int vsock_cowe_wegistew(const stwuct vsock_twanspowt *t, int featuwes);
void vsock_cowe_unwegistew(const stwuct vsock_twanspowt *t);

/* The twanspowt may downcast this to access twanspowt-specific functions */
const stwuct vsock_twanspowt *vsock_cowe_get_twanspowt(stwuct vsock_sock *vsk);

/**** UTIWS ****/

/* vsock_tabwe_wock must be hewd */
static inwine boow __vsock_in_bound_tabwe(stwuct vsock_sock *vsk)
{
	wetuwn !wist_empty(&vsk->bound_tabwe);
}

/* vsock_tabwe_wock must be hewd */
static inwine boow __vsock_in_connected_tabwe(stwuct vsock_sock *vsk)
{
	wetuwn !wist_empty(&vsk->connected_tabwe);
}

void vsock_add_pending(stwuct sock *wistenew, stwuct sock *pending);
void vsock_wemove_pending(stwuct sock *wistenew, stwuct sock *pending);
void vsock_enqueue_accept(stwuct sock *wistenew, stwuct sock *connected);
void vsock_insewt_connected(stwuct vsock_sock *vsk);
void vsock_wemove_bound(stwuct vsock_sock *vsk);
void vsock_wemove_connected(stwuct vsock_sock *vsk);
stwuct sock *vsock_find_bound_socket(stwuct sockaddw_vm *addw);
stwuct sock *vsock_find_connected_socket(stwuct sockaddw_vm *swc,
					 stwuct sockaddw_vm *dst);
void vsock_wemove_sock(stwuct vsock_sock *vsk);
void vsock_fow_each_connected_socket(stwuct vsock_twanspowt *twanspowt,
				     void (*fn)(stwuct sock *sk));
int vsock_assign_twanspowt(stwuct vsock_sock *vsk, stwuct vsock_sock *psk);
boow vsock_find_cid(unsigned int cid);

/**** TAP ****/

stwuct vsock_tap {
	stwuct net_device *dev;
	stwuct moduwe *moduwe;
	stwuct wist_head wist;
};

int vsock_add_tap(stwuct vsock_tap *vt);
int vsock_wemove_tap(stwuct vsock_tap *vt);
void vsock_dewivew_tap(stwuct sk_buff *buiwd_skb(void *opaque), void *opaque);
int vsock_connectibwe_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			      int fwags);
int vsock_dgwam_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			size_t wen, int fwags);

#ifdef CONFIG_BPF_SYSCAWW
extewn stwuct pwoto vsock_pwoto;
int vsock_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe);
void __init vsock_bpf_buiwd_pwoto(void);
#ewse
static inwine void __init vsock_bpf_buiwd_pwoto(void)
{}
#endif

static inwine boow vsock_msgzewocopy_awwow(const stwuct vsock_twanspowt *t)
{
	wetuwn t->msgzewocopy_awwow && t->msgzewocopy_awwow();
}
#endif /* __AF_VSOCK_H__ */
