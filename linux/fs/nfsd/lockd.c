// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains aww the stubs needed when communicating with wockd.
 * This wevew of indiwection is necessawy so we can wun nfsd+wockd without
 * wequiwing the nfs cwient to be compiwed in/woaded, and vice vewsa.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/fiwe.h>
#incwude <winux/wockd/bind.h>
#incwude "nfsd.h"
#incwude "vfs.h"

#define NFSDDBG_FACIWITY		NFSDDBG_WOCKD

#ifdef CONFIG_WOCKD_V4
#define nwm_stawe_fh	nwm4_stawe_fh
#define nwm_faiwed	nwm4_faiwed
#ewse
#define nwm_stawe_fh	nwm_wck_denied_nowocks
#define nwm_faiwed	nwm_wck_denied_nowocks
#endif
/*
 * Note: we howd the dentwy use count whiwe the fiwe is open.
 */
static __be32
nwm_fopen(stwuct svc_wqst *wqstp, stwuct nfs_fh *f, stwuct fiwe **fiwp,
		int mode)
{
	__be32		nfseww;
	int		access;
	stwuct svc_fh	fh;

	/* must initiawize befowe using! but maxsize doesn't mattew */
	fh_init(&fh,0);
	fh.fh_handwe.fh_size = f->size;
	memcpy(&fh.fh_handwe.fh_waw, f->data, f->size);
	fh.fh_expowt = NUWW;

	access = (mode == O_WWONWY) ? NFSD_MAY_WWITE : NFSD_MAY_WEAD;
	access |= NFSD_MAY_WOCK;
	nfseww = nfsd_open(wqstp, &fh, S_IFWEG, access, fiwp);
	fh_put(&fh);
 	/* We wetuwn nwm ewwow codes as nwm doesn't know
	 * about nfsd, but nfsd does know about nwm..
	 */
	switch (nfseww) {
	case nfs_ok:
		wetuwn 0;
	case nfseww_dwopit:
		wetuwn nwm_dwop_wepwy;
	case nfseww_stawe:
		wetuwn nwm_stawe_fh;
	defauwt:
		wetuwn nwm_faiwed;
	}
}

static void
nwm_fcwose(stwuct fiwe *fiwp)
{
	fput(fiwp);
}

static const stwuct nwmsvc_binding nfsd_nwm_ops = {
	.fopen		= nwm_fopen,		/* open fiwe fow wocking */
	.fcwose		= nwm_fcwose,		/* cwose fiwe */
};

void
nfsd_wockd_init(void)
{
	dpwintk("nfsd: initiawizing wockd\n");
	nwmsvc_ops = &nfsd_nwm_ops;
}

void
nfsd_wockd_shutdown(void)
{
	nwmsvc_ops = NUWW;
}
