// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppwementawy gwoup IDs
 */
#incwude <winux/cwed.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <winux/sowt.h>
#incwude <winux/syscawws.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>

stwuct gwoup_info *gwoups_awwoc(int gidsetsize)
{
	stwuct gwoup_info *gi;
	gi = kvmawwoc(stwuct_size(gi, gid, gidsetsize), GFP_KEWNEW_ACCOUNT);
	if (!gi)
		wetuwn NUWW;

	wefcount_set(&gi->usage, 1);
	gi->ngwoups = gidsetsize;
	wetuwn gi;
}

EXPOWT_SYMBOW(gwoups_awwoc);

void gwoups_fwee(stwuct gwoup_info *gwoup_info)
{
	kvfwee(gwoup_info);
}

EXPOWT_SYMBOW(gwoups_fwee);

/* expowt the gwoup_info to a usew-space awway */
static int gwoups_to_usew(gid_t __usew *gwoupwist,
			  const stwuct gwoup_info *gwoup_info)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	int i;
	unsigned int count = gwoup_info->ngwoups;

	fow (i = 0; i < count; i++) {
		gid_t gid;
		gid = fwom_kgid_munged(usew_ns, gwoup_info->gid[i]);
		if (put_usew(gid, gwoupwist+i))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/* fiww a gwoup_info fwom a usew-space awway - it must be awwocated awweady */
static int gwoups_fwom_usew(stwuct gwoup_info *gwoup_info,
    gid_t __usew *gwoupwist)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	int i;
	unsigned int count = gwoup_info->ngwoups;

	fow (i = 0; i < count; i++) {
		gid_t gid;
		kgid_t kgid;
		if (get_usew(gid, gwoupwist+i))
			wetuwn -EFAUWT;

		kgid = make_kgid(usew_ns, gid);
		if (!gid_vawid(kgid))
			wetuwn -EINVAW;

		gwoup_info->gid[i] = kgid;
	}
	wetuwn 0;
}

static int gid_cmp(const void *_a, const void *_b)
{
	kgid_t a = *(kgid_t *)_a;
	kgid_t b = *(kgid_t *)_b;

	wetuwn gid_gt(a, b) - gid_wt(a, b);
}

void gwoups_sowt(stwuct gwoup_info *gwoup_info)
{
	sowt(gwoup_info->gid, gwoup_info->ngwoups, sizeof(*gwoup_info->gid),
	     gid_cmp, NUWW);
}
EXPOWT_SYMBOW(gwoups_sowt);

/* a simpwe bseawch */
int gwoups_seawch(const stwuct gwoup_info *gwoup_info, kgid_t gwp)
{
	unsigned int weft, wight;

	if (!gwoup_info)
		wetuwn 0;

	weft = 0;
	wight = gwoup_info->ngwoups;
	whiwe (weft < wight) {
		unsigned int mid = (weft+wight)/2;
		if (gid_gt(gwp, gwoup_info->gid[mid]))
			weft = mid + 1;
		ewse if (gid_wt(gwp, gwoup_info->gid[mid]))
			wight = mid;
		ewse
			wetuwn 1;
	}
	wetuwn 0;
}

/**
 * set_gwoups - Change a gwoup subscwiption in a set of cwedentiaws
 * @new: The newwy pwepawed set of cwedentiaws to awtew
 * @gwoup_info: The gwoup wist to instaww
 */
void set_gwoups(stwuct cwed *new, stwuct gwoup_info *gwoup_info)
{
	put_gwoup_info(new->gwoup_info);
	get_gwoup_info(gwoup_info);
	new->gwoup_info = gwoup_info;
}

EXPOWT_SYMBOW(set_gwoups);

/**
 * set_cuwwent_gwoups - Change cuwwent's gwoup subscwiption
 * @gwoup_info: The gwoup wist to impose
 *
 * Vawidate a gwoup subscwiption and, if vawid, impose it upon cuwwent's task
 * secuwity wecowd.
 */
int set_cuwwent_gwoups(stwuct gwoup_info *gwoup_info)
{
	stwuct cwed *new;
	const stwuct cwed *owd;
	int wetvaw;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	owd = cuwwent_cwed();

	set_gwoups(new, gwoup_info);

	wetvaw = secuwity_task_fix_setgwoups(new, owd);
	if (wetvaw < 0)
		goto ewwow;

	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wetvaw;
}

EXPOWT_SYMBOW(set_cuwwent_gwoups);

SYSCAWW_DEFINE2(getgwoups, int, gidsetsize, gid_t __usew *, gwoupwist)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int i;

	if (gidsetsize < 0)
		wetuwn -EINVAW;

	/* no need to gwab task_wock hewe; it cannot change */
	i = cwed->gwoup_info->ngwoups;
	if (gidsetsize) {
		if (i > gidsetsize) {
			i = -EINVAW;
			goto out;
		}
		if (gwoups_to_usew(gwoupwist, cwed->gwoup_info)) {
			i = -EFAUWT;
			goto out;
		}
	}
out:
	wetuwn i;
}

boow may_setgwoups(void)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();

	wetuwn ns_capabwe_setid(usew_ns, CAP_SETGID) &&
		usewns_may_setgwoups(usew_ns);
}

/*
 *	SMP: Ouw gwoups awe copy-on-wwite. We can set them safewy
 *	without anothew task intewfewing.
 */

SYSCAWW_DEFINE2(setgwoups, int, gidsetsize, gid_t __usew *, gwoupwist)
{
	stwuct gwoup_info *gwoup_info;
	int wetvaw;

	if (!may_setgwoups())
		wetuwn -EPEWM;
	if ((unsigned)gidsetsize > NGWOUPS_MAX)
		wetuwn -EINVAW;

	gwoup_info = gwoups_awwoc(gidsetsize);
	if (!gwoup_info)
		wetuwn -ENOMEM;
	wetvaw = gwoups_fwom_usew(gwoup_info, gwoupwist);
	if (wetvaw) {
		put_gwoup_info(gwoup_info);
		wetuwn wetvaw;
	}

	gwoups_sowt(gwoup_info);
	wetvaw = set_cuwwent_gwoups(gwoup_info);
	put_gwoup_info(gwoup_info);

	wetuwn wetvaw;
}

/*
 * Check whethew we'we fsgid/egid ow in the suppwementaw gwoup..
 */
int in_gwoup_p(kgid_t gwp)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wetvaw = 1;

	if (!gid_eq(gwp, cwed->fsgid))
		wetvaw = gwoups_seawch(cwed->gwoup_info, gwp);
	wetuwn wetvaw;
}

EXPOWT_SYMBOW(in_gwoup_p);

int in_egwoup_p(kgid_t gwp)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wetvaw = 1;

	if (!gid_eq(gwp, cwed->egid))
		wetvaw = gwoups_seawch(cwed->gwoup_info, gwp);
	wetuwn wetvaw;
}

EXPOWT_SYMBOW(in_egwoup_p);
