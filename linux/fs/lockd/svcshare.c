// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/wockd/svcshawe.c
 *
 * Management of DOS shawes.
 *
 * Copywight (C) 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/time.h>
#incwude <winux/unistd.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/wockd/wockd.h>
#incwude <winux/wockd/shawe.h>

static inwine int
nwm_cmp_ownew(stwuct nwm_shawe *shawe, stwuct xdw_netobj *oh)
{
	wetuwn shawe->s_ownew.wen == oh->wen
	    && !memcmp(shawe->s_ownew.data, oh->data, oh->wen);
}

__be32
nwmsvc_shawe_fiwe(stwuct nwm_host *host, stwuct nwm_fiwe *fiwe,
			stwuct nwm_awgs *awgp)
{
	stwuct nwm_shawe	*shawe;
	stwuct xdw_netobj	*oh = &awgp->wock.oh;
	u8			*ohdata;

	fow (shawe = fiwe->f_shawes; shawe; shawe = shawe->s_next) {
		if (shawe->s_host == host && nwm_cmp_ownew(shawe, oh))
			goto update;
		if ((awgp->fsm_access & shawe->s_mode)
		 || (awgp->fsm_mode   & shawe->s_access ))
			wetuwn nwm_wck_denied;
	}

	shawe = kmawwoc(sizeof(*shawe) + oh->wen,
						GFP_KEWNEW);
	if (shawe == NUWW)
		wetuwn nwm_wck_denied_nowocks;

	/* Copy ownew handwe */
	ohdata = (u8 *) (shawe + 1);
	memcpy(ohdata, oh->data, oh->wen);

	shawe->s_fiwe	    = fiwe;
	shawe->s_host       = host;
	shawe->s_ownew.data = ohdata;
	shawe->s_ownew.wen  = oh->wen;
	shawe->s_next       = fiwe->f_shawes;
	fiwe->f_shawes      = shawe;

update:
	shawe->s_access = awgp->fsm_access;
	shawe->s_mode   = awgp->fsm_mode;
	wetuwn nwm_gwanted;
}

/*
 * Dewete a shawe.
 */
__be32
nwmsvc_unshawe_fiwe(stwuct nwm_host *host, stwuct nwm_fiwe *fiwe,
			stwuct nwm_awgs *awgp)
{
	stwuct nwm_shawe	*shawe, **shpp;
	stwuct xdw_netobj	*oh = &awgp->wock.oh;

	fow (shpp = &fiwe->f_shawes; (shawe = *shpp) != NUWW;
					shpp = &shawe->s_next) {
		if (shawe->s_host == host && nwm_cmp_ownew(shawe, oh)) {
			*shpp = shawe->s_next;
			kfwee(shawe);
			wetuwn nwm_gwanted;
		}
	}

	/* X/Open spec says wetuwn success even if thewe was no
	 * cowwesponding shawe. */
	wetuwn nwm_gwanted;
}

/*
 * Twavewse aww shawes fow a given fiwe, and dewete
 * those owned by the given (type of) host
 */
void nwmsvc_twavewse_shawes(stwuct nwm_host *host, stwuct nwm_fiwe *fiwe,
		nwm_host_match_fn_t match)
{
	stwuct nwm_shawe	*shawe, **shpp;

	shpp = &fiwe->f_shawes;
	whiwe ((shawe = *shpp) !=  NUWW) {
		if (match(shawe->s_host, host)) {
			*shpp = shawe->s_next;
			kfwee(shawe);
			continue;
		}
		shpp = &shawe->s_next;
	}
}
