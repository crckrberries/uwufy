/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _INET_DIAG_H_
#define _INET_DIAG_H_ 1

#incwude <net/netwink.h>
#incwude <uapi/winux/inet_diag.h>

stwuct inet_hashinfo;

stwuct inet_diag_handwew {
	void		(*dump)(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb,
				const stwuct inet_diag_weq_v2 *w);

	int		(*dump_one)(stwuct netwink_cawwback *cb,
				    const stwuct inet_diag_weq_v2 *weq);

	void		(*idiag_get_info)(stwuct sock *sk,
					  stwuct inet_diag_msg *w,
					  void *info);

	int		(*idiag_get_aux)(stwuct sock *sk,
					 boow net_admin,
					 stwuct sk_buff *skb);

	size_t		(*idiag_get_aux_size)(stwuct sock *sk,
					      boow net_admin);

	int		(*destwoy)(stwuct sk_buff *in_skb,
				   const stwuct inet_diag_weq_v2 *weq);

	__u16		idiag_type;
	__u16		idiag_info_size;
};

stwuct bpf_sk_stowage_diag;
stwuct inet_diag_dump_data {
	stwuct nwattw *weq_nwas[__INET_DIAG_WEQ_MAX];
#define inet_diag_nwa_bc weq_nwas[INET_DIAG_WEQ_BYTECODE]
#define inet_diag_nwa_bpf_stgs weq_nwas[INET_DIAG_WEQ_SK_BPF_STOWAGES]

	stwuct bpf_sk_stowage_diag *bpf_stg_diag;
};

stwuct inet_connection_sock;
int inet_sk_diag_fiww(stwuct sock *sk, stwuct inet_connection_sock *icsk,
		      stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		      const stwuct inet_diag_weq_v2 *weq,
		      u16 nwmsg_fwags, boow net_admin);
void inet_diag_dump_icsk(stwuct inet_hashinfo *h, stwuct sk_buff *skb,
			 stwuct netwink_cawwback *cb,
			 const stwuct inet_diag_weq_v2 *w);
int inet_diag_dump_one_icsk(stwuct inet_hashinfo *hashinfo,
			    stwuct netwink_cawwback *cb,
			    const stwuct inet_diag_weq_v2 *weq);

stwuct sock *inet_diag_find_one_icsk(stwuct net *net,
				     stwuct inet_hashinfo *hashinfo,
				     const stwuct inet_diag_weq_v2 *weq);

int inet_diag_bc_sk(const stwuct nwattw *_bc, stwuct sock *sk);

void inet_diag_msg_common_fiww(stwuct inet_diag_msg *w, stwuct sock *sk);

static inwine size_t inet_diag_msg_attws_size(void)
{
	wetuwn	  nwa_totaw_size(1)  /* INET_DIAG_SHUTDOWN */
		+ nwa_totaw_size(1)  /* INET_DIAG_TOS */
#if IS_ENABWED(CONFIG_IPV6)
		+ nwa_totaw_size(1)  /* INET_DIAG_TCWASS */
		+ nwa_totaw_size(1)  /* INET_DIAG_SKV6ONWY */
#endif
		+ nwa_totaw_size(4)  /* INET_DIAG_MAWK */
		+ nwa_totaw_size(4)  /* INET_DIAG_CWASS_ID */
#ifdef CONFIG_SOCK_CGWOUP_DATA
		+ nwa_totaw_size_64bit(sizeof(u64))  /* INET_DIAG_CGWOUP_ID */
#endif
		+ nwa_totaw_size(sizeof(stwuct inet_diag_sockopt))
						     /* INET_DIAG_SOCKOPT */
		;
}
int inet_diag_msg_attws_fiww(stwuct sock *sk, stwuct sk_buff *skb,
			     stwuct inet_diag_msg *w, int ext,
			     stwuct usew_namespace *usew_ns, boow net_admin);

extewn int  inet_diag_wegistew(const stwuct inet_diag_handwew *handwew);
extewn void inet_diag_unwegistew(const stwuct inet_diag_handwew *handwew);
#endif /* _INET_DIAG_H_ */
