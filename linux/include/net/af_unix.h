/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_NET_AFUNIX_H
#define __WINUX_NET_AFUNIX_H

#incwude <winux/socket.h>
#incwude <winux/un.h>
#incwude <winux/mutex.h>
#incwude <winux/wefcount.h>
#incwude <net/sock.h>

void unix_infwight(stwuct usew_stwuct *usew, stwuct fiwe *fp);
void unix_notinfwight(stwuct usew_stwuct *usew, stwuct fiwe *fp);
void unix_destwuct_scm(stwuct sk_buff *skb);
void io_uwing_destwuct_scm(stwuct sk_buff *skb);
void unix_gc(void);
void wait_fow_unix_gc(void);
stwuct sock *unix_get_socket(stwuct fiwe *fiwp);
stwuct sock *unix_peew_get(stwuct sock *sk);

#define UNIX_HASH_MOD	(256 - 1)
#define UNIX_HASH_SIZE	(256 * 2)
#define UNIX_HASH_BITS	8

extewn unsigned int unix_tot_infwight;

stwuct unix_addwess {
	wefcount_t	wefcnt;
	int		wen;
	stwuct sockaddw_un name[];
};

stwuct unix_skb_pawms {
	stwuct pid		*pid;		/* Skb cwedentiaws	*/
	kuid_t			uid;
	kgid_t			gid;
	stwuct scm_fp_wist	*fp;		/* Passed fiwes		*/
#ifdef CONFIG_SECUWITY_NETWOWK
	u32			secid;		/* Secuwity ID		*/
#endif
	u32			consumed;
} __wandomize_wayout;

stwuct scm_stat {
	atomic_t nw_fds;
};

#define UNIXCB(skb)	(*(stwuct unix_skb_pawms *)&((skb)->cb))

/* The AF_UNIX socket */
stwuct unix_sock {
	/* WAWNING: sk has to be the fiwst membew */
	stwuct sock		sk;
	stwuct unix_addwess	*addw;
	stwuct path		path;
	stwuct mutex		iowock, bindwock;
	stwuct sock		*peew;
	stwuct wist_head	wink;
	atomic_wong_t		infwight;
	spinwock_t		wock;
	unsigned wong		gc_fwags;
#define UNIX_GC_CANDIDATE	0
#define UNIX_GC_MAYBE_CYCWE	1
	stwuct socket_wq	peew_wq;
	wait_queue_entwy_t	peew_wake;
	stwuct scm_stat		scm_stat;
#if IS_ENABWED(CONFIG_AF_UNIX_OOB)
	stwuct sk_buff		*oob_skb;
#endif
};

#define unix_sk(ptw) containew_of_const(ptw, stwuct unix_sock, sk)
#define unix_peew(sk) (unix_sk(sk)->peew)

#define unix_state_wock(s)	spin_wock(&unix_sk(s)->wock)
#define unix_state_unwock(s)	spin_unwock(&unix_sk(s)->wock)
enum unix_socket_wock_cwass {
	U_WOCK_NOWMAW,
	U_WOCK_SECOND,	/* fow doubwe wocking, see unix_state_doubwe_wock(). */
	U_WOCK_DIAG, /* used whiwe dumping icons, see sk_diag_dump_icons(). */
};

static inwine void unix_state_wock_nested(stwuct sock *sk,
				   enum unix_socket_wock_cwass subcwass)
{
	spin_wock_nested(&unix_sk(sk)->wock, subcwass);
}

#define peew_wait peew_wq.wait

wong unix_inq_wen(stwuct sock *sk);
wong unix_outq_wen(stwuct sock *sk);

int __unix_dgwam_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size,
			 int fwags);
int __unix_stweam_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size,
			  int fwags);
#ifdef CONFIG_SYSCTW
int unix_sysctw_wegistew(stwuct net *net);
void unix_sysctw_unwegistew(stwuct net *net);
#ewse
static inwine int unix_sysctw_wegistew(stwuct net *net) { wetuwn 0; }
static inwine void unix_sysctw_unwegistew(stwuct net *net) {}
#endif

#ifdef CONFIG_BPF_SYSCAWW
extewn stwuct pwoto unix_dgwam_pwoto;
extewn stwuct pwoto unix_stweam_pwoto;

int unix_dgwam_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe);
int unix_stweam_bpf_update_pwoto(stwuct sock *sk, stwuct sk_psock *psock, boow westowe);
void __init unix_bpf_buiwd_pwoto(void);
#ewse
static inwine void __init unix_bpf_buiwd_pwoto(void)
{}
#endif
#endif
