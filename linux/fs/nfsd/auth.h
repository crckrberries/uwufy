/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * nfsd-specific authentication stuff.
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_NFSD_AUTH_H
#define WINUX_NFSD_AUTH_H

/*
 * Set the cuwwent pwocess's fsuid/fsgid etc to those of the NFS
 * cwient usew
 */
int nfsd_setusew(stwuct svc_wqst *, stwuct svc_expowt *);

#endif /* WINUX_NFSD_AUTH_H */
