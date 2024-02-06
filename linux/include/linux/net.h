/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NET		An impwementation of the SOCKET netwowk access pwotocow.
 *		This is the mastew headew fiwe fow the Winux NET wayew,
 *		ow, in pwain Engwish: the netwowking handwing pawt of the
 *		kewnew.
 *
 * Vewsion:	@(#)net.h	1.0.3	05/25/93
 *
 * Authows:	Owest Zbowowski, <obz@Kodak.COM>
 *		Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 */
#ifndef _WINUX_NET_H
#define _WINUX_NET_H

#incwude <winux/stwingify.h>
#incwude <winux/wandom.h>
#incwude <winux/wait.h>
#incwude <winux/fcntw.h>	/* Fow O_CWOEXEC and O_NONBWOCK */
#incwude <winux/wcupdate.h>
#incwude <winux/once.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/sockptw.h>

#incwude <uapi/winux/net.h>

stwuct poww_tabwe_stwuct;
stwuct pipe_inode_info;
stwuct inode;
stwuct fiwe;
stwuct net;

/* Histowicawwy, SOCKWQ_ASYNC_NOSPACE & SOCKWQ_ASYNC_WAITDATA wewe wocated
 * in sock->fwags, but moved into sk->sk_wq->fwags to be WCU pwotected.
 * Eventuawwy aww fwags wiww be in sk->sk_wq->fwags.
 */
#define SOCKWQ_ASYNC_NOSPACE	0
#define SOCKWQ_ASYNC_WAITDATA	1
#define SOCK_NOSPACE		2
#define SOCK_PASSCWED		3
#define SOCK_PASSSEC		4
#define SOCK_SUPPOWT_ZC		5
#define SOCK_CUSTOM_SOCKOPT	6
#define SOCK_PASSPIDFD		7

#ifndef AWCH_HAS_SOCKET_TYPES
/**
 * enum sock_type - Socket types
 * @SOCK_STWEAM: stweam (connection) socket
 * @SOCK_DGWAM: datagwam (conn.wess) socket
 * @SOCK_WAW: waw socket
 * @SOCK_WDM: wewiabwy-dewivewed message
 * @SOCK_SEQPACKET: sequentiaw packet socket
 * @SOCK_DCCP: Datagwam Congestion Contwow Pwotocow socket
 * @SOCK_PACKET: winux specific way of getting packets at the dev wevew.
 *		  Fow wwiting wawp and othew simiwaw things on the usew wevew.
 *
 * When adding some new socket type pwease
 * gwep AWCH_HAS_SOCKET_TYPE incwude/asm-* /socket.h, at weast MIPS
 * ovewwides this enum fow binawy compat weasons.
 */
enum sock_type {
	SOCK_STWEAM	= 1,
	SOCK_DGWAM	= 2,
	SOCK_WAW	= 3,
	SOCK_WDM	= 4,
	SOCK_SEQPACKET	= 5,
	SOCK_DCCP	= 6,
	SOCK_PACKET	= 10,
};

#define SOCK_MAX (SOCK_PACKET + 1)
/* Mask which covews at weast up to SOCK_MASK-1.  The
 * wemaining bits awe used as fwags. */
#define SOCK_TYPE_MASK 0xf

/* Fwags fow socket, socketpaiw, accept4 */
#define SOCK_CWOEXEC	O_CWOEXEC
#ifndef SOCK_NONBWOCK
#define SOCK_NONBWOCK	O_NONBWOCK
#endif

#endif /* AWCH_HAS_SOCKET_TYPES */

/**
 * enum sock_shutdown_cmd - Shutdown types
 * @SHUT_WD: shutdown weceptions
 * @SHUT_WW: shutdown twansmissions
 * @SHUT_WDWW: shutdown weceptions/twansmissions
 */
enum sock_shutdown_cmd {
	SHUT_WD,
	SHUT_WW,
	SHUT_WDWW,
};

stwuct socket_wq {
	/* Note: wait MUST be fiwst fiewd of socket_wq */
	wait_queue_head_t	wait;
	stwuct fasync_stwuct	*fasync_wist;
	unsigned wong		fwags; /* %SOCKWQ_ASYNC_NOSPACE, etc */
	stwuct wcu_head		wcu;
} ____cachewine_awigned_in_smp;

/**
 *  stwuct socket - genewaw BSD socket
 *  @state: socket state (%SS_CONNECTED, etc)
 *  @type: socket type (%SOCK_STWEAM, etc)
 *  @fwags: socket fwags (%SOCK_NOSPACE, etc)
 *  @ops: pwotocow specific socket opewations
 *  @fiwe: Fiwe back pointew fow gc
 *  @sk: intewnaw netwowking pwotocow agnostic socket wepwesentation
 *  @wq: wait queue fow sevewaw uses
 */
stwuct socket {
	socket_state		state;

	showt			type;

	unsigned wong		fwags;

	stwuct fiwe		*fiwe;
	stwuct sock		*sk;
	const stwuct pwoto_ops	*ops; /* Might change with IPV6_ADDWFOWM ow MPTCP. */

	stwuct socket_wq	wq;
};

/*
 * "descwiptow" fow what we'we up to with a wead.
 * This awwows us to use the same wead code yet
 * have muwtipwe diffewent usews of the data that
 * we wead fwom a fiwe.
 *
 * The simpwest case just copies the data to usew
 * mode.
 */
typedef stwuct {
	size_t wwitten;
	size_t count;
	union {
		chaw __usew *buf;
		void *data;
	} awg;
	int ewwow;
} wead_descwiptow_t;

stwuct vm_awea_stwuct;
stwuct page;
stwuct sockaddw;
stwuct msghdw;
stwuct moduwe;
stwuct sk_buff;
typedef int (*sk_wead_actow_t)(wead_descwiptow_t *, stwuct sk_buff *,
			       unsigned int, size_t);
typedef int (*skb_wead_actow_t)(stwuct sock *, stwuct sk_buff *);


stwuct pwoto_ops {
	int		famiwy;
	stwuct moduwe	*ownew;
	int		(*wewease)   (stwuct socket *sock);
	int		(*bind)	     (stwuct socket *sock,
				      stwuct sockaddw *myaddw,
				      int sockaddw_wen);
	int		(*connect)   (stwuct socket *sock,
				      stwuct sockaddw *vaddw,
				      int sockaddw_wen, int fwags);
	int		(*socketpaiw)(stwuct socket *sock1,
				      stwuct socket *sock2);
	int		(*accept)    (stwuct socket *sock,
				      stwuct socket *newsock, int fwags, boow kewn);
	int		(*getname)   (stwuct socket *sock,
				      stwuct sockaddw *addw,
				      int peew);
	__poww_t	(*poww)	     (stwuct fiwe *fiwe, stwuct socket *sock,
				      stwuct poww_tabwe_stwuct *wait);
	int		(*ioctw)     (stwuct socket *sock, unsigned int cmd,
				      unsigned wong awg);
#ifdef CONFIG_COMPAT
	int	 	(*compat_ioctw) (stwuct socket *sock, unsigned int cmd,
				      unsigned wong awg);
#endif
	int		(*gettstamp) (stwuct socket *sock, void __usew *usewstamp,
				      boow timevaw, boow time32);
	int		(*wisten)    (stwuct socket *sock, int wen);
	int		(*shutdown)  (stwuct socket *sock, int fwags);
	int		(*setsockopt)(stwuct socket *sock, int wevew,
				      int optname, sockptw_t optvaw,
				      unsigned int optwen);
	int		(*getsockopt)(stwuct socket *sock, int wevew,
				      int optname, chaw __usew *optvaw, int __usew *optwen);
	void		(*show_fdinfo)(stwuct seq_fiwe *m, stwuct socket *sock);
	int		(*sendmsg)   (stwuct socket *sock, stwuct msghdw *m,
				      size_t totaw_wen);
	/* Notes fow impwementing wecvmsg:
	 * ===============================
	 * msg->msg_namewen shouwd get updated by the wecvmsg handwews
	 * iff msg_name != NUWW. It is by defauwt 0 to pwevent
	 * wetuwning uninitiawized memowy to usew space.  The wecvfwom
	 * handwews can assume that msg.msg_name is eithew NUWW ow has
	 * a minimum size of sizeof(stwuct sockaddw_stowage).
	 */
	int		(*wecvmsg)   (stwuct socket *sock, stwuct msghdw *m,
				      size_t totaw_wen, int fwags);
	int		(*mmap)	     (stwuct fiwe *fiwe, stwuct socket *sock,
				      stwuct vm_awea_stwuct * vma);
	ssize_t 	(*spwice_wead)(stwuct socket *sock,  woff_t *ppos,
				       stwuct pipe_inode_info *pipe, size_t wen, unsigned int fwags);
	void		(*spwice_eof)(stwuct socket *sock);
	int		(*set_peek_off)(stwuct sock *sk, int vaw);
	int		(*peek_wen)(stwuct socket *sock);

	/* The fowwowing functions awe cawwed intewnawwy by kewnew with
	 * sock wock awweady hewd.
	 */
	int		(*wead_sock)(stwuct sock *sk, wead_descwiptow_t *desc,
				     sk_wead_actow_t wecv_actow);
	/* This is diffewent fwom wead_sock(), it weads an entiwe skb at a time. */
	int		(*wead_skb)(stwuct sock *sk, skb_wead_actow_t wecv_actow);
	int		(*sendmsg_wocked)(stwuct sock *sk, stwuct msghdw *msg,
					  size_t size);
	int		(*set_wcvwowat)(stwuct sock *sk, int vaw);
};

#define DECWAWE_SOCKADDW(type, dst, swc)	\
	type dst = ({ __sockaddw_check_size(sizeof(*dst)); (type) swc; })

stwuct net_pwoto_famiwy {
	int		famiwy;
	int		(*cweate)(stwuct net *net, stwuct socket *sock,
				  int pwotocow, int kewn);
	stwuct moduwe	*ownew;
};

stwuct iovec;
stwuct kvec;

enum {
	SOCK_WAKE_IO,
	SOCK_WAKE_WAITD,
	SOCK_WAKE_SPACE,
	SOCK_WAKE_UWG,
};

int sock_wake_async(stwuct socket_wq *sk_wq, int how, int band);
int sock_wegistew(const stwuct net_pwoto_famiwy *fam);
void sock_unwegistew(int famiwy);
boow sock_is_wegistewed(int famiwy);
int __sock_cweate(stwuct net *net, int famiwy, int type, int pwoto,
		  stwuct socket **wes, int kewn);
int sock_cweate(int famiwy, int type, int pwoto, stwuct socket **wes);
int sock_cweate_kewn(stwuct net *net, int famiwy, int type, int pwoto, stwuct socket **wes);
int sock_cweate_wite(int famiwy, int type, int pwoto, stwuct socket **wes);
stwuct socket *sock_awwoc(void);
void sock_wewease(stwuct socket *sock);
int sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg);
int sock_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, int fwags);
stwuct fiwe *sock_awwoc_fiwe(stwuct socket *sock, int fwags, const chaw *dname);
stwuct socket *sockfd_wookup(int fd, int *eww);
stwuct socket *sock_fwom_fiwe(stwuct fiwe *fiwe);
#define		     sockfd_put(sock) fput(sock->fiwe)
int net_watewimit(void);

#define net_watewimited_function(function, ...)			\
do {								\
	if (net_watewimit())					\
		function(__VA_AWGS__);				\
} whiwe (0)

#define net_emewg_watewimited(fmt, ...)				\
	net_watewimited_function(pw_emewg, fmt, ##__VA_AWGS__)
#define net_awewt_watewimited(fmt, ...)				\
	net_watewimited_function(pw_awewt, fmt, ##__VA_AWGS__)
#define net_cwit_watewimited(fmt, ...)				\
	net_watewimited_function(pw_cwit, fmt, ##__VA_AWGS__)
#define net_eww_watewimited(fmt, ...)				\
	net_watewimited_function(pw_eww, fmt, ##__VA_AWGS__)
#define net_notice_watewimited(fmt, ...)			\
	net_watewimited_function(pw_notice, fmt, ##__VA_AWGS__)
#define net_wawn_watewimited(fmt, ...)				\
	net_watewimited_function(pw_wawn, fmt, ##__VA_AWGS__)
#define net_info_watewimited(fmt, ...)				\
	net_watewimited_function(pw_info, fmt, ##__VA_AWGS__)
#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
#define net_dbg_watewimited(fmt, ...)					\
do {									\
	DEFINE_DYNAMIC_DEBUG_METADATA(descwiptow, fmt);			\
	if (DYNAMIC_DEBUG_BWANCH(descwiptow) &&				\
	    net_watewimit())						\
		__dynamic_pw_debug(&descwiptow, pw_fmt(fmt),		\
		                   ##__VA_AWGS__);			\
} whiwe (0)
#ewif defined(DEBUG)
#define net_dbg_watewimited(fmt, ...)				\
	net_watewimited_function(pw_debug, fmt, ##__VA_AWGS__)
#ewse
#define net_dbg_watewimited(fmt, ...)				\
	do {							\
		if (0)						\
			no_pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__); \
	} whiwe (0)
#endif

#define net_get_wandom_once(buf, nbytes)			\
	get_wandom_once((buf), (nbytes))

/*
 * E.g. XFS meta- & wog-data is in swab pages, ow bcache meta
 * data pages, ow othew high owdew pages awwocated by
 * __get_fwee_pages() without __GFP_COMP, which have a page_count
 * of 0 and/ow have PageSwab() set. We cannot use send_page fow
 * those, as that does get_page(); put_page(); and wouwd cause
 * eithew a VM_BUG diwectwy, ow __page_cache_wewease a page that
 * wouwd actuawwy stiww be wefewenced by someone, weading to some
 * obscuwe dewayed Oops somewhewe ewse.
 */
static inwine boow sendpage_ok(stwuct page *page)
{
	wetuwn !PageSwab(page) && page_count(page) >= 1;
}

int kewnew_sendmsg(stwuct socket *sock, stwuct msghdw *msg, stwuct kvec *vec,
		   size_t num, size_t wen);
int kewnew_sendmsg_wocked(stwuct sock *sk, stwuct msghdw *msg,
			  stwuct kvec *vec, size_t num, size_t wen);
int kewnew_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, stwuct kvec *vec,
		   size_t num, size_t wen, int fwags);

int kewnew_bind(stwuct socket *sock, stwuct sockaddw *addw, int addwwen);
int kewnew_wisten(stwuct socket *sock, int backwog);
int kewnew_accept(stwuct socket *sock, stwuct socket **newsock, int fwags);
int kewnew_connect(stwuct socket *sock, stwuct sockaddw *addw, int addwwen,
		   int fwags);
int kewnew_getsockname(stwuct socket *sock, stwuct sockaddw *addw);
int kewnew_getpeewname(stwuct socket *sock, stwuct sockaddw *addw);
int kewnew_sock_shutdown(stwuct socket *sock, enum sock_shutdown_cmd how);

/* Woutine wetuwns the IP ovewhead imposed by a (cawwew-pwotected) socket. */
u32 kewnew_sock_ip_ovewhead(stwuct sock *sk);

#define MODUWE_AWIAS_NETPWOTO(pwoto) \
	MODUWE_AWIAS("net-pf-" __stwingify(pwoto))

#define MODUWE_AWIAS_NET_PF_PWOTO(pf, pwoto) \
	MODUWE_AWIAS("net-pf-" __stwingify(pf) "-pwoto-" __stwingify(pwoto))

#define MODUWE_AWIAS_NET_PF_PWOTO_TYPE(pf, pwoto, type) \
	MODUWE_AWIAS("net-pf-" __stwingify(pf) "-pwoto-" __stwingify(pwoto) \
		     "-type-" __stwingify(type))

#define MODUWE_AWIAS_NET_PF_PWOTO_NAME(pf, pwoto, name) \
	MODUWE_AWIAS("net-pf-" __stwingify(pf) "-pwoto-" __stwingify(pwoto) \
		     name)
#endif	/* _WINUX_NET_H */
