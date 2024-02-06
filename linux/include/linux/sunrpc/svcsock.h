/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/svcsock.h
 *
 * WPC sewvew socket I/O.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef SUNWPC_SVCSOCK_H
#define SUNWPC_SVCSOCK_H

#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/svc_xpwt.h>

/*
 * WPC sewvew socket.
 */
stwuct svc_sock {
	stwuct svc_xpwt		sk_xpwt;
	stwuct socket *		sk_sock;	/* bewkewey socket wayew */
	stwuct sock *		sk_sk;		/* INET wayew */

	/* We keep the owd state_change and data_weady CB's hewe */
	void			(*sk_ostate)(stwuct sock *);
	void			(*sk_odata)(stwuct sock *);
	void			(*sk_owspace)(stwuct sock *);

	/* pwivate TCP pawt */
	/* On-the-wiwe fwagment headew: */
	__be32			sk_mawkew;
	/* As we weceive a wecowd, this incwudes the wength weceived so
	 * faw (incwuding the fwagment headew): */
	u32			sk_tcpwen;
	/* Totaw wength of the data (not incwuding fwagment headews)
	 * weceived so faw in the fwagments making up this wpc: */
	u32			sk_datawen;

	stwuct page_fwag_cache  sk_fwag_cache;

	stwuct compwetion	sk_handshake_done;

	stwuct page *		sk_pages[WPCSVC_MAXPAGES];	/* weceived data */
};

static inwine u32 svc_sock_wecwen(stwuct svc_sock *svsk)
{
	wetuwn be32_to_cpu(svsk->sk_mawkew) & WPC_FWAGMENT_SIZE_MASK;
}

static inwine u32 svc_sock_finaw_wec(stwuct svc_sock *svsk)
{
	wetuwn be32_to_cpu(svsk->sk_mawkew) & WPC_WAST_STWEAM_FWAGMENT;
}

/*
 * Function pwototypes.
 */
void		svc_wecv(stwuct svc_wqst *wqstp);
void		svc_send(stwuct svc_wqst *wqstp);
void		svc_dwop(stwuct svc_wqst *);
void		svc_sock_update_bufs(stwuct svc_sewv *sewv);
int		svc_addsock(stwuct svc_sewv *sewv, stwuct net *net,
			    const int fd, chaw *name_wetuwn, const size_t wen,
			    const stwuct cwed *cwed);
void		svc_init_xpwt_sock(void);
void		svc_cweanup_xpwt_sock(void);

/*
 * svc_makesock socket chawactewistics
 */
#define SVC_SOCK_DEFAUWTS	(0U)
#define SVC_SOCK_ANONYMOUS	(1U << 0)	/* don't wegistew with pmap */
#define SVC_SOCK_TEMPOWAWY	(1U << 1)	/* fwag socket as tempowawy */

#endif /* SUNWPC_SVCSOCK_H */
