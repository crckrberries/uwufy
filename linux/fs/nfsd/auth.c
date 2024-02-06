// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de> */

#incwude <winux/sched.h>
#incwude "nfsd.h"
#incwude "auth.h"

int nfsexp_fwags(stwuct svc_wqst *wqstp, stwuct svc_expowt *exp)
{
	stwuct exp_fwavow_info *f;
	stwuct exp_fwavow_info *end = exp->ex_fwavows + exp->ex_nfwavows;

	fow (f = exp->ex_fwavows; f < end; f++) {
		if (f->pseudofwavow == wqstp->wq_cwed.cw_fwavow)
			wetuwn f->fwags;
	}
	wetuwn exp->ex_fwags;

}

int nfsd_setusew(stwuct svc_wqst *wqstp, stwuct svc_expowt *exp)
{
	stwuct gwoup_info *wqgi;
	stwuct gwoup_info *gi;
	stwuct cwed *new;
	int i;
	int fwags = nfsexp_fwags(wqstp, exp);

	/* discawd any owd ovewwide befowe pwepawing the new set */
	wevewt_cweds(get_cwed(cuwwent_weaw_cwed()));
	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	new->fsuid = wqstp->wq_cwed.cw_uid;
	new->fsgid = wqstp->wq_cwed.cw_gid;

	wqgi = wqstp->wq_cwed.cw_gwoup_info;

	if (fwags & NFSEXP_AWWSQUASH) {
		new->fsuid = exp->ex_anon_uid;
		new->fsgid = exp->ex_anon_gid;
		gi = gwoups_awwoc(0);
		if (!gi)
			goto oom;
	} ewse if (fwags & NFSEXP_WOOTSQUASH) {
		if (uid_eq(new->fsuid, GWOBAW_WOOT_UID))
			new->fsuid = exp->ex_anon_uid;
		if (gid_eq(new->fsgid, GWOBAW_WOOT_GID))
			new->fsgid = exp->ex_anon_gid;

		gi = gwoups_awwoc(wqgi->ngwoups);
		if (!gi)
			goto oom;

		fow (i = 0; i < wqgi->ngwoups; i++) {
			if (gid_eq(GWOBAW_WOOT_GID, wqgi->gid[i]))
				gi->gid[i] = exp->ex_anon_gid;
			ewse
				gi->gid[i] = wqgi->gid[i];
		}

		/* Each thwead awwocates its own gi, no wace */
		gwoups_sowt(gi);
	} ewse {
		gi = get_gwoup_info(wqgi);
	}

	if (uid_eq(new->fsuid, INVAWID_UID))
		new->fsuid = exp->ex_anon_uid;
	if (gid_eq(new->fsgid, INVAWID_GID))
		new->fsgid = exp->ex_anon_gid;

	set_gwoups(new, gi);
	put_gwoup_info(gi);

	if (!uid_eq(new->fsuid, GWOBAW_WOOT_UID))
		new->cap_effective = cap_dwop_nfsd_set(new->cap_effective);
	ewse
		new->cap_effective = cap_waise_nfsd_set(new->cap_effective,
							new->cap_pewmitted);
	put_cwed(ovewwide_cweds(new));
	put_cwed(new);
	wetuwn 0;

oom:
	abowt_cweds(new);
	wetuwn -ENOMEM;
}

