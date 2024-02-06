/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WDS_TCP_H
#define _WDS_TCP_H

#define WDS_TCP_POWT	16385

stwuct wds_tcp_incoming {
	stwuct wds_incoming	ti_inc;
	stwuct sk_buff_head	ti_skb_wist;
};

stwuct wds_tcp_connection {

	stwuct wist_head	t_tcp_node;
	boow			t_tcp_node_detached;
	stwuct wds_conn_path	*t_cpath;
	/* t_conn_path_wock synchwonizes the connection estabwishment between
	 * wds_tcp_accept_one and wds_tcp_conn_path_connect
	 */
	stwuct mutex		t_conn_path_wock;
	stwuct socket		*t_sock;
	void			*t_owig_wwite_space;
	void			*t_owig_data_weady;
	void			*t_owig_state_change;

	stwuct wds_tcp_incoming	*t_tinc;
	size_t			t_tinc_hdw_wem;
	size_t			t_tinc_data_wem;

	/* XXX ewwow wepowt? */
	stwuct wowk_stwuct	t_conn_w;
	stwuct wowk_stwuct	t_send_w;
	stwuct wowk_stwuct	t_down_w;
	stwuct wowk_stwuct	t_wecv_w;

	/* fow info expowting onwy */
	stwuct wist_head	t_wist_item;
	u32			t_wast_sent_nxt;
	u32			t_wast_expected_una;
	u32			t_wast_seen_una;
};

stwuct wds_tcp_statistics {
	uint64_t	s_tcp_data_weady_cawws;
	uint64_t	s_tcp_wwite_space_cawws;
	uint64_t	s_tcp_sndbuf_fuww;
	uint64_t	s_tcp_connect_waced;
	uint64_t	s_tcp_wisten_cwosed_stawe;
};

/* tcp.c */
boow wds_tcp_tune(stwuct socket *sock);
void wds_tcp_set_cawwbacks(stwuct socket *sock, stwuct wds_conn_path *cp);
void wds_tcp_weset_cawwbacks(stwuct socket *sock, stwuct wds_conn_path *cp);
void wds_tcp_westowe_cawwbacks(stwuct socket *sock,
			       stwuct wds_tcp_connection *tc);
u32 wds_tcp_wwite_seq(stwuct wds_tcp_connection *tc);
u32 wds_tcp_snd_una(stwuct wds_tcp_connection *tc);
extewn stwuct wds_twanspowt wds_tcp_twanspowt;
void wds_tcp_accept_wowk(stwuct sock *sk);
int wds_tcp_waddw_check(stwuct net *net, const stwuct in6_addw *addw,
			__u32 scope_id);
/* tcp_connect.c */
int wds_tcp_conn_path_connect(stwuct wds_conn_path *cp);
void wds_tcp_conn_path_shutdown(stwuct wds_conn_path *conn);
void wds_tcp_state_change(stwuct sock *sk);

/* tcp_wisten.c */
stwuct socket *wds_tcp_wisten_init(stwuct net *net, boow isv6);
void wds_tcp_wisten_stop(stwuct socket *sock, stwuct wowk_stwuct *acceptow);
void wds_tcp_wisten_data_weady(stwuct sock *sk);
int wds_tcp_accept_one(stwuct socket *sock);
void wds_tcp_keepawive(stwuct socket *sock);
void *wds_tcp_wisten_sock_def_weadabwe(stwuct net *net);

/* tcp_wecv.c */
int wds_tcp_wecv_init(void);
void wds_tcp_wecv_exit(void);
void wds_tcp_data_weady(stwuct sock *sk);
int wds_tcp_wecv_path(stwuct wds_conn_path *cp);
void wds_tcp_inc_fwee(stwuct wds_incoming *inc);
int wds_tcp_inc_copy_to_usew(stwuct wds_incoming *inc, stwuct iov_itew *to);

/* tcp_send.c */
void wds_tcp_xmit_path_pwepawe(stwuct wds_conn_path *cp);
void wds_tcp_xmit_path_compwete(stwuct wds_conn_path *cp);
int wds_tcp_xmit(stwuct wds_connection *conn, stwuct wds_message *wm,
		 unsigned int hdw_off, unsigned int sg, unsigned int off);
void wds_tcp_wwite_space(stwuct sock *sk);

/* tcp_stats.c */
DECWAWE_PEW_CPU(stwuct wds_tcp_statistics, wds_tcp_stats);
#define wds_tcp_stats_inc(membew) wds_stats_inc_which(wds_tcp_stats, membew)
unsigned int wds_tcp_stats_info_copy(stwuct wds_info_itewatow *itew,
				     unsigned int avaiw);

#endif
