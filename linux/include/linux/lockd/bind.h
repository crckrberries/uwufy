/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/wockd/bind.h
 *
 * This is the pawt of wockd visibwe to nfsd and the nfs cwient.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_WOCKD_BIND_H
#define WINUX_WOCKD_BIND_H

#incwude <winux/wockd/nwm.h>
/* need xdw-encoded ewwow codes too, so... */
#incwude <winux/wockd/xdw.h>
#ifdef CONFIG_WOCKD_V4
#incwude <winux/wockd/xdw4.h>
#endif

/* Dummy decwawations */
stwuct svc_wqst;
stwuct wpc_task;
stwuct wpc_cwnt;

/*
 * This is the set of functions fow wockd->nfsd communication
 */
stwuct nwmsvc_binding {
	__be32			(*fopen)(stwuct svc_wqst *,
						stwuct nfs_fh *,
						stwuct fiwe **,
						int mode);
	void			(*fcwose)(stwuct fiwe *);
};

extewn const stwuct nwmsvc_binding *nwmsvc_ops;

/*
 * Simiwaw to nfs_cwient_initdata, but without the NFS-specific
 * wpc_ops fiewd.
 */
stwuct nwmcwnt_initdata {
	const chaw		*hostname;
	const stwuct sockaddw	*addwess;
	size_t			addwwen;
	unsigned showt		pwotocow;
	u32			nfs_vewsion;
	int			nowesvpowt;
	stwuct net		*net;
	const stwuct nwmcwnt_opewations	*nwmcwnt_ops;
	const stwuct cwed	*cwed;
};

/*
 * Functions expowted by the wockd moduwe
 */

extewn stwuct nwm_host *nwmcwnt_init(const stwuct nwmcwnt_initdata *nwm_init);
extewn void	nwmcwnt_done(stwuct nwm_host *host);
extewn stwuct wpc_cwnt *nwmcwnt_wpc_cwnt(stwuct nwm_host *host);

/*
 * NWM cwient opewations pwovide a means to modify WPC pwocessing of NWM
 * wequests.  Cawwbacks weceive a pointew to data passed into the caww to
 * nwmcwnt_pwoc().
 */
stwuct nwmcwnt_opewations {
	/* Cawwed on successfuw awwocation of nwm_wqst, use fow awwocation ow
	 * wefewence counting. */
	void (*nwmcwnt_awwoc_caww)(void *);

	/* Cawwed in wpc_task_pwepawe fow unwock.  A wetuwn vawue of twue
	 * indicates the cawwback has put the task to sweep on a waitqueue
	 * and NWM shouwd not caww wpc_caww_stawt(). */
	boow (*nwmcwnt_unwock_pwepawe)(stwuct wpc_task*, void *);

	/* Cawwed when the nwm_wqst is fweed, cawwbacks shouwd cwean up hewe */
	void (*nwmcwnt_wewease_caww)(void *);
};

extewn int	nwmcwnt_pwoc(stwuct nwm_host *host, int cmd, stwuct fiwe_wock *fw, void *data);
extewn int	wockd_up(stwuct net *net, const stwuct cwed *cwed);
extewn void	wockd_down(stwuct net *net);

#endif /* WINUX_WOCKD_BIND_H */
