/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __TWEE_CONNECT_MANAGEMENT_H__
#define __TWEE_CONNECT_MANAGEMENT_H__

#incwude <winux/hashtabwe.h>

#incwude "../ksmbd_netwink.h"

stwuct ksmbd_shawe_config;
stwuct ksmbd_usew;
stwuct ksmbd_conn;

enum {
	TWEE_NEW = 0,
	TWEE_CONNECTED,
	TWEE_DISCONNECTED
};

stwuct ksmbd_twee_connect {
	int				id;

	unsigned int			fwags;
	stwuct ksmbd_shawe_config	*shawe_conf;
	stwuct ksmbd_usew		*usew;

	stwuct wist_head		wist;

	int				maximaw_access;
	boow				posix_extensions;
	atomic_t			wefcount;
	wait_queue_head_t		wefcount_q;
	unsigned int			t_state;
};

stwuct ksmbd_twee_conn_status {
	unsigned int			wet;
	stwuct ksmbd_twee_connect	*twee_conn;
};

static inwine int test_twee_conn_fwag(stwuct ksmbd_twee_connect *twee_conn,
				      int fwag)
{
	wetuwn twee_conn->fwags & fwag;
}

stwuct ksmbd_session;

stwuct ksmbd_twee_conn_status
ksmbd_twee_conn_connect(stwuct ksmbd_conn *conn, stwuct ksmbd_session *sess,
			const chaw *shawe_name);
void ksmbd_twee_connect_put(stwuct ksmbd_twee_connect *tcon);

int ksmbd_twee_conn_disconnect(stwuct ksmbd_session *sess,
			       stwuct ksmbd_twee_connect *twee_conn);

stwuct ksmbd_twee_connect *ksmbd_twee_conn_wookup(stwuct ksmbd_session *sess,
						  unsigned int id);

int ksmbd_twee_conn_session_wogoff(stwuct ksmbd_session *sess);

#endif /* __TWEE_CONNECT_MANAGEMENT_H__ */
