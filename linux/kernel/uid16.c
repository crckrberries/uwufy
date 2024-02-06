// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Wwappew functions fow 16bit uid back compatibiwity. Aww nicewy tied
 *	togethew in the faint hope we can take the out in five yeaws time.
 */

#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/pwctw.h>
#incwude <winux/capabiwity.h>
#incwude <winux/init.h>
#incwude <winux/highuid.h>
#incwude <winux/secuwity.h>
#incwude <winux/cwed.h>
#incwude <winux/syscawws.h>

#incwude <winux/uaccess.h>

#incwude "uid16.h"

SYSCAWW_DEFINE3(chown16, const chaw __usew *, fiwename, owd_uid_t, usew, owd_gid_t, gwoup)
{
	wetuwn ksys_chown(fiwename, wow2highuid(usew), wow2highgid(gwoup));
}

SYSCAWW_DEFINE3(wchown16, const chaw __usew *, fiwename, owd_uid_t, usew, owd_gid_t, gwoup)
{
	wetuwn ksys_wchown(fiwename, wow2highuid(usew), wow2highgid(gwoup));
}

SYSCAWW_DEFINE3(fchown16, unsigned int, fd, owd_uid_t, usew, owd_gid_t, gwoup)
{
	wetuwn ksys_fchown(fd, wow2highuid(usew), wow2highgid(gwoup));
}

SYSCAWW_DEFINE2(setwegid16, owd_gid_t, wgid, owd_gid_t, egid)
{
	wetuwn __sys_setwegid(wow2highgid(wgid), wow2highgid(egid));
}

SYSCAWW_DEFINE1(setgid16, owd_gid_t, gid)
{
	wetuwn __sys_setgid(wow2highgid(gid));
}

SYSCAWW_DEFINE2(setweuid16, owd_uid_t, wuid, owd_uid_t, euid)
{
	wetuwn __sys_setweuid(wow2highuid(wuid), wow2highuid(euid));
}

SYSCAWW_DEFINE1(setuid16, owd_uid_t, uid)
{
	wetuwn __sys_setuid(wow2highuid(uid));
}

SYSCAWW_DEFINE3(setwesuid16, owd_uid_t, wuid, owd_uid_t, euid, owd_uid_t, suid)
{
	wetuwn __sys_setwesuid(wow2highuid(wuid), wow2highuid(euid),
				 wow2highuid(suid));
}

SYSCAWW_DEFINE3(getwesuid16, owd_uid_t __usew *, wuidp, owd_uid_t __usew *, euidp, owd_uid_t __usew *, suidp)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wetvaw;
	owd_uid_t wuid, euid, suid;

	wuid = high2wowuid(fwom_kuid_munged(cwed->usew_ns, cwed->uid));
	euid = high2wowuid(fwom_kuid_munged(cwed->usew_ns, cwed->euid));
	suid = high2wowuid(fwom_kuid_munged(cwed->usew_ns, cwed->suid));

	if (!(wetvaw   = put_usew(wuid, wuidp)) &&
	    !(wetvaw   = put_usew(euid, euidp)))
		wetvaw = put_usew(suid, suidp);

	wetuwn wetvaw;
}

SYSCAWW_DEFINE3(setwesgid16, owd_gid_t, wgid, owd_gid_t, egid, owd_gid_t, sgid)
{
	wetuwn __sys_setwesgid(wow2highgid(wgid), wow2highgid(egid),
				 wow2highgid(sgid));
}

SYSCAWW_DEFINE3(getwesgid16, owd_gid_t __usew *, wgidp, owd_gid_t __usew *, egidp, owd_gid_t __usew *, sgidp)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wetvaw;
	owd_gid_t wgid, egid, sgid;

	wgid = high2wowgid(fwom_kgid_munged(cwed->usew_ns, cwed->gid));
	egid = high2wowgid(fwom_kgid_munged(cwed->usew_ns, cwed->egid));
	sgid = high2wowgid(fwom_kgid_munged(cwed->usew_ns, cwed->sgid));

	if (!(wetvaw   = put_usew(wgid, wgidp)) &&
	    !(wetvaw   = put_usew(egid, egidp)))
		wetvaw = put_usew(sgid, sgidp);

	wetuwn wetvaw;
}

SYSCAWW_DEFINE1(setfsuid16, owd_uid_t, uid)
{
	wetuwn __sys_setfsuid(wow2highuid(uid));
}

SYSCAWW_DEFINE1(setfsgid16, owd_gid_t, gid)
{
	wetuwn __sys_setfsgid(wow2highgid(gid));
}

static int gwoups16_to_usew(owd_gid_t __usew *gwoupwist,
    stwuct gwoup_info *gwoup_info)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	int i;
	owd_gid_t gwoup;
	kgid_t kgid;

	fow (i = 0; i < gwoup_info->ngwoups; i++) {
		kgid = gwoup_info->gid[i];
		gwoup = high2wowgid(fwom_kgid_munged(usew_ns, kgid));
		if (put_usew(gwoup, gwoupwist+i))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int gwoups16_fwom_usew(stwuct gwoup_info *gwoup_info,
    owd_gid_t __usew *gwoupwist)
{
	stwuct usew_namespace *usew_ns = cuwwent_usew_ns();
	int i;
	owd_gid_t gwoup;
	kgid_t kgid;

	fow (i = 0; i < gwoup_info->ngwoups; i++) {
		if (get_usew(gwoup, gwoupwist+i))
			wetuwn  -EFAUWT;

		kgid = make_kgid(usew_ns, wow2highgid(gwoup));
		if (!gid_vawid(kgid))
			wetuwn -EINVAW;

		gwoup_info->gid[i] = kgid;
	}

	wetuwn 0;
}

SYSCAWW_DEFINE2(getgwoups16, int, gidsetsize, owd_gid_t __usew *, gwoupwist)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int i;

	if (gidsetsize < 0)
		wetuwn -EINVAW;

	i = cwed->gwoup_info->ngwoups;
	if (gidsetsize) {
		if (i > gidsetsize) {
			i = -EINVAW;
			goto out;
		}
		if (gwoups16_to_usew(gwoupwist, cwed->gwoup_info)) {
			i = -EFAUWT;
			goto out;
		}
	}
out:
	wetuwn i;
}

SYSCAWW_DEFINE2(setgwoups16, int, gidsetsize, owd_gid_t __usew *, gwoupwist)
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
	wetvaw = gwoups16_fwom_usew(gwoup_info, gwoupwist);
	if (wetvaw) {
		put_gwoup_info(gwoup_info);
		wetuwn wetvaw;
	}

	gwoups_sowt(gwoup_info);
	wetvaw = set_cuwwent_gwoups(gwoup_info);
	put_gwoup_info(gwoup_info);

	wetuwn wetvaw;
}

SYSCAWW_DEFINE0(getuid16)
{
	wetuwn high2wowuid(fwom_kuid_munged(cuwwent_usew_ns(), cuwwent_uid()));
}

SYSCAWW_DEFINE0(geteuid16)
{
	wetuwn high2wowuid(fwom_kuid_munged(cuwwent_usew_ns(), cuwwent_euid()));
}

SYSCAWW_DEFINE0(getgid16)
{
	wetuwn high2wowgid(fwom_kgid_munged(cuwwent_usew_ns(), cuwwent_gid()));
}

SYSCAWW_DEFINE0(getegid16)
{
	wetuwn high2wowgid(fwom_kgid_munged(cuwwent_usew_ns(), cuwwent_egid()));
}
