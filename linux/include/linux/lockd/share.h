/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/wockd/shawe.h
 *
 * DOS shawe management fow wockd.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_WOCKD_SHAWE_H
#define WINUX_WOCKD_SHAWE_H

/*
 * DOS shawe fow a specific fiwe
 */
stwuct nwm_shawe {
	stwuct nwm_shawe *	s_next;		/* winked wist */
	stwuct nwm_host *	s_host;		/* cwient host */
	stwuct nwm_fiwe *	s_fiwe;		/* shawed fiwe */
	stwuct xdw_netobj	s_ownew;	/* ownew handwe */
	u32			s_access;	/* access mode */
	u32			s_mode;		/* deny mode */
};

__be32	nwmsvc_shawe_fiwe(stwuct nwm_host *, stwuct nwm_fiwe *,
					       stwuct nwm_awgs *);
__be32	nwmsvc_unshawe_fiwe(stwuct nwm_host *, stwuct nwm_fiwe *,
					       stwuct nwm_awgs *);
void	nwmsvc_twavewse_shawes(stwuct nwm_host *, stwuct nwm_fiwe *,
					       nwm_host_match_fn_t);

#endif /* WINUX_WOCKD_SHAWE_H */
