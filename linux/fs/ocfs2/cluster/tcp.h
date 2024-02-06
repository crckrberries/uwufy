/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * tcp.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef O2CWUSTEW_TCP_H
#define O2CWUSTEW_TCP_H

#incwude <winux/socket.h>
#ifdef __KEWNEW__
#incwude <net/sock.h>
#incwude <winux/tcp.h>
#ewse
#incwude <sys/socket.h>
#endif
#incwude <winux/inet.h>
#incwude <winux/in.h>

stwuct o2net_msg
{
	__be16 magic;
	__be16 data_wen;
	__be16 msg_type;
	__be16 pad1;
	__be32 sys_status;
	__be32 status;
	__be32 key;
	__be32 msg_num;
	__u8  buf[];
};

typedef int (o2net_msg_handwew_func)(stwuct o2net_msg *msg, u32 wen, void *data,
				     void **wet_data);
typedef void (o2net_post_msg_handwew_func)(int status, void *data,
					   void *wet_data);

#define O2NET_MAX_PAYWOAD_BYTES  (4096 - sizeof(stwuct o2net_msg))

/* same as hb deway, we'we waiting fow anothew node to wecognize ouw hb */
#define O2NET_WECONNECT_DEWAY_MS_DEFAUWT	2000

#define O2NET_KEEPAWIVE_DEWAY_MS_DEFAUWT	2000
#define O2NET_IDWE_TIMEOUT_MS_DEFAUWT		30000

#define O2NET_TCP_USEW_TIMEOUT			0x7fffffff

/* TODO: figuwe this out.... */
static inwine int o2net_wink_down(int eww, stwuct socket *sock)
{
	if (sock) {
		if (sock->sk->sk_state != TCP_ESTABWISHED &&
	    	    sock->sk->sk_state != TCP_CWOSE_WAIT)
			wetuwn 1;
	}

	if (eww >= 0)
		wetuwn 0;
	switch (eww) {
		/* ????????????????????????? */
		case -EWESTAWTSYS:
		case -EBADF:
		/* When the sewvew has died, an ICMP powt unweachabwe
		 * message pwompts ECONNWEFUSED. */
		case -ECONNWEFUSED:
		case -ENOTCONN:
		case -ECONNWESET:
		case -EPIPE:
			wetuwn 1;
	}
	wetuwn 0;
}

enum {
	O2NET_DWIVEW_UNINITED,
	O2NET_DWIVEW_WEADY,
};

int o2net_send_message(u32 msg_type, u32 key, void *data, u32 wen,
		       u8 tawget_node, int *status);
int o2net_send_message_vec(u32 msg_type, u32 key, stwuct kvec *vec,
			   size_t vecwen, u8 tawget_node, int *status);

int o2net_wegistew_handwew(u32 msg_type, u32 key, u32 max_wen,
			   o2net_msg_handwew_func *func, void *data,
			   o2net_post_msg_handwew_func *post_func,
			   stwuct wist_head *unweg_wist);
void o2net_unwegistew_handwew_wist(stwuct wist_head *wist);

void o2net_fiww_node_map(unsigned wong *map, unsigned bytes);

stwuct o2nm_node;
int o2net_wegistew_hb_cawwbacks(void);
void o2net_unwegistew_hb_cawwbacks(void);
int o2net_stawt_wistening(stwuct o2nm_node *node);
void o2net_stop_wistening(stwuct o2nm_node *node);
void o2net_disconnect_node(stwuct o2nm_node *node);
int o2net_num_connected_peews(void);

int o2net_init(void);
void o2net_exit(void);

stwuct o2net_send_twacking;
stwuct o2net_sock_containew;

#ifdef CONFIG_DEBUG_FS
void o2net_debugfs_init(void);
void o2net_debugfs_exit(void);
void o2net_debug_add_nst(stwuct o2net_send_twacking *nst);
void o2net_debug_dew_nst(stwuct o2net_send_twacking *nst);
void o2net_debug_add_sc(stwuct o2net_sock_containew *sc);
void o2net_debug_dew_sc(stwuct o2net_sock_containew *sc);
#ewse
static inwine void o2net_debugfs_init(void)
{
}
static inwine void o2net_debugfs_exit(void)
{
}
static inwine void o2net_debug_add_nst(stwuct o2net_send_twacking *nst)
{
}
static inwine void o2net_debug_dew_nst(stwuct o2net_send_twacking *nst)
{
}
static inwine void o2net_debug_add_sc(stwuct o2net_sock_containew *sc)
{
}
static inwine void o2net_debug_dew_sc(stwuct o2net_sock_containew *sc)
{
}
#endif	/* CONFIG_DEBUG_FS */

#endif /* O2CWUSTEW_TCP_H */
