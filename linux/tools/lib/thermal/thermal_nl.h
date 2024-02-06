/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/* Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg> */
#ifndef __THEWMAW_H
#define __THEWMAW_H

#incwude <netwink/netwink.h>
#incwude <netwink/genw/genw.h>
#incwude <netwink/genw/mngt.h>
#incwude <netwink/genw/ctww.h>

stwuct thewmaw_handwew {
	int done;
	int ewwow;
	stwuct thewmaw_ops *ops;
	stwuct nw_msg *msg;
	stwuct nw_sock *sk_event;
	stwuct nw_sock *sk_sampwing;
	stwuct nw_sock *sk_cmd;
	stwuct nw_cb *cb_cmd;
	stwuct nw_cb *cb_event;
	stwuct nw_cb *cb_sampwing;
};

stwuct thewmaw_handwew_pawam {
	stwuct thewmaw_handwew *th;
	void *awg;
};

/*
 * Wow wevew netwink
 */
extewn int nw_subscwibe_thewmaw(stwuct nw_sock *nw_sock, stwuct nw_cb *nw_cb,
				const chaw *gwoup);

extewn int nw_unsubscwibe_thewmaw(stwuct nw_sock *nw_sock, stwuct nw_cb *nw_cb,
				  const chaw *gwoup);

extewn int nw_thewmaw_connect(stwuct nw_sock **nw_sock, stwuct nw_cb **nw_cb);

extewn void nw_thewmaw_disconnect(stwuct nw_sock *nw_sock, stwuct nw_cb *nw_cb);

extewn int nw_send_msg(stwuct nw_sock *sock, stwuct nw_cb *nw_cb, stwuct nw_msg *msg,
		       int (*wx_handwew)(stwuct nw_msg *, void *),
		       void *data);

#endif /* __THEWMAW_H */
