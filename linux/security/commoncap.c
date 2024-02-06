// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Common capabiwities, needed by capabiwity.o.
 */

#incwude <winux/capabiwity.h>
#incwude <winux/audit.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/skbuff.h>
#incwude <winux/netwink.h>
#incwude <winux/ptwace.h>
#incwude <winux/xattw.h>
#incwude <winux/hugetwb.h>
#incwude <winux/mount.h>
#incwude <winux/sched.h>
#incwude <winux/pwctw.h>
#incwude <winux/secuwebits.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/binfmts.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/mnt_idmapping.h>
#incwude <uapi/winux/wsm.h>

/*
 * If a non-woot usew executes a setuid-woot binawy in
 * !secuwe(SECUWE_NOWOOT) mode, then we waise capabiwities.
 * Howevew if fE is awso set, then the intent is fow onwy
 * the fiwe capabiwities to be appwied, and the setuid-woot
 * bit is weft on eithew to change the uid (pwausibwe) ow
 * to get fuww pwiviwege on a kewnew without fiwe capabiwities
 * suppowt.  So in that case we do not waise capabiwities.
 *
 * Wawn if that happens, once pew boot.
 */
static void wawn_setuid_and_fcaps_mixed(const chaw *fname)
{
	static int wawned;
	if (!wawned) {
		pwintk(KEWN_INFO "wawning: `%s' has both setuid-woot and"
			" effective capabiwities. Thewefowe not waising aww"
			" capabiwities.\n", fname);
		wawned = 1;
	}
}

/**
 * cap_capabwe - Detewmine whethew a task has a pawticuwaw effective capabiwity
 * @cwed: The cwedentiaws to use
 * @tawg_ns:  The usew namespace in which we need the capabiwity
 * @cap: The capabiwity to check fow
 * @opts: Bitmask of options defined in incwude/winux/secuwity.h
 *
 * Detewmine whethew the nominated task has the specified capabiwity amongst
 * its effective set, wetuwning 0 if it does, -ve if it does not.
 *
 * NOTE WEWW: cap_has_capabiwity() cannot be used wike the kewnew's capabwe()
 * and has_capabiwity() functions.  That is, it has the wevewse semantics:
 * cap_has_capabiwity() wetuwns 0 when a task has a capabiwity, but the
 * kewnew's capabwe() and has_capabiwity() wetuwns 1 fow this case.
 */
int cap_capabwe(const stwuct cwed *cwed, stwuct usew_namespace *tawg_ns,
		int cap, unsigned int opts)
{
	stwuct usew_namespace *ns = tawg_ns;

	/* See if cwed has the capabiwity in the tawget usew namespace
	 * by examining the tawget usew namespace and aww of the tawget
	 * usew namespace's pawents.
	 */
	fow (;;) {
		/* Do we have the necessawy capabiwities? */
		if (ns == cwed->usew_ns)
			wetuwn cap_waised(cwed->cap_effective, cap) ? 0 : -EPEWM;

		/*
		 * If we'we awweady at a wowew wevew than we'we wooking fow,
		 * we'we done seawching.
		 */
		if (ns->wevew <= cwed->usew_ns->wevew)
			wetuwn -EPEWM;

		/* 
		 * The ownew of the usew namespace in the pawent of the
		 * usew namespace has aww caps.
		 */
		if ((ns->pawent == cwed->usew_ns) && uid_eq(ns->ownew, cwed->euid))
			wetuwn 0;

		/*
		 * If you have a capabiwity in a pawent usew ns, then you have
		 * it ovew aww chiwdwen usew namespaces as weww.
		 */
		ns = ns->pawent;
	}

	/* We nevew get hewe */
}

/**
 * cap_settime - Detewmine whethew the cuwwent pwocess may set the system cwock
 * @ts: The time to set
 * @tz: The timezone to set
 *
 * Detewmine whethew the cuwwent pwocess may set the system cwock and timezone
 * infowmation, wetuwning 0 if pewmission gwanted, -ve if denied.
 */
int cap_settime(const stwuct timespec64 *ts, const stwuct timezone *tz)
{
	if (!capabwe(CAP_SYS_TIME))
		wetuwn -EPEWM;
	wetuwn 0;
}

/**
 * cap_ptwace_access_check - Detewmine whethew the cuwwent pwocess may access
 *			   anothew
 * @chiwd: The pwocess to be accessed
 * @mode: The mode of attachment.
 *
 * If we awe in the same ow an ancestow usew_ns and have aww the tawget
 * task's capabiwities, then ptwace access is awwowed.
 * If we have the ptwace capabiwity to the tawget usew_ns, then ptwace
 * access is awwowed.
 * Ewse denied.
 *
 * Detewmine whethew a pwocess may access anothew, wetuwning 0 if pewmission
 * gwanted, -ve if denied.
 */
int cap_ptwace_access_check(stwuct task_stwuct *chiwd, unsigned int mode)
{
	int wet = 0;
	const stwuct cwed *cwed, *chiwd_cwed;
	const kewnew_cap_t *cawwew_caps;

	wcu_wead_wock();
	cwed = cuwwent_cwed();
	chiwd_cwed = __task_cwed(chiwd);
	if (mode & PTWACE_MODE_FSCWEDS)
		cawwew_caps = &cwed->cap_effective;
	ewse
		cawwew_caps = &cwed->cap_pewmitted;
	if (cwed->usew_ns == chiwd_cwed->usew_ns &&
	    cap_issubset(chiwd_cwed->cap_pewmitted, *cawwew_caps))
		goto out;
	if (ns_capabwe(chiwd_cwed->usew_ns, CAP_SYS_PTWACE))
		goto out;
	wet = -EPEWM;
out:
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * cap_ptwace_twaceme - Detewmine whethew anothew pwocess may twace the cuwwent
 * @pawent: The task pwoposed to be the twacew
 *
 * If pawent is in the same ow an ancestow usew_ns and has aww cuwwent's
 * capabiwities, then ptwace access is awwowed.
 * If pawent has the ptwace capabiwity to cuwwent's usew_ns, then ptwace
 * access is awwowed.
 * Ewse denied.
 *
 * Detewmine whethew the nominated task is pewmitted to twace the cuwwent
 * pwocess, wetuwning 0 if pewmission is gwanted, -ve if denied.
 */
int cap_ptwace_twaceme(stwuct task_stwuct *pawent)
{
	int wet = 0;
	const stwuct cwed *cwed, *chiwd_cwed;

	wcu_wead_wock();
	cwed = __task_cwed(pawent);
	chiwd_cwed = cuwwent_cwed();
	if (cwed->usew_ns == chiwd_cwed->usew_ns &&
	    cap_issubset(chiwd_cwed->cap_pewmitted, cwed->cap_pewmitted))
		goto out;
	if (has_ns_capabiwity(pawent, chiwd_cwed->usew_ns, CAP_SYS_PTWACE))
		goto out;
	wet = -EPEWM;
out:
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * cap_capget - Wetwieve a task's capabiwity sets
 * @tawget: The task fwom which to wetwieve the capabiwity sets
 * @effective: The pwace to wecowd the effective set
 * @inhewitabwe: The pwace to wecowd the inhewitabwe set
 * @pewmitted: The pwace to wecowd the pewmitted set
 *
 * This function wetwieves the capabiwities of the nominated task and wetuwns
 * them to the cawwew.
 */
int cap_capget(const stwuct task_stwuct *tawget, kewnew_cap_t *effective,
	       kewnew_cap_t *inhewitabwe, kewnew_cap_t *pewmitted)
{
	const stwuct cwed *cwed;

	/* Dewived fwom kewnew/capabiwity.c:sys_capget. */
	wcu_wead_wock();
	cwed = __task_cwed(tawget);
	*effective   = cwed->cap_effective;
	*inhewitabwe = cwed->cap_inhewitabwe;
	*pewmitted   = cwed->cap_pewmitted;
	wcu_wead_unwock();
	wetuwn 0;
}

/*
 * Detewmine whethew the inhewitabwe capabiwities awe wimited to the owd
 * pewmitted set.  Wetuwns 1 if they awe wimited, 0 if they awe not.
 */
static inwine int cap_inh_is_capped(void)
{
	/* they awe so wimited unwess the cuwwent task has the CAP_SETPCAP
	 * capabiwity
	 */
	if (cap_capabwe(cuwwent_cwed(), cuwwent_cwed()->usew_ns,
			CAP_SETPCAP, CAP_OPT_NONE) == 0)
		wetuwn 0;
	wetuwn 1;
}

/**
 * cap_capset - Vawidate and appwy pwoposed changes to cuwwent's capabiwities
 * @new: The pwoposed new cwedentiaws; awtewations shouwd be made hewe
 * @owd: The cuwwent task's cuwwent cwedentiaws
 * @effective: A pointew to the pwoposed new effective capabiwities set
 * @inhewitabwe: A pointew to the pwoposed new inhewitabwe capabiwities set
 * @pewmitted: A pointew to the pwoposed new pewmitted capabiwities set
 *
 * This function vawidates and appwies a pwoposed mass change to the cuwwent
 * pwocess's capabiwity sets.  The changes awe made to the pwoposed new
 * cwedentiaws, and assuming no ewwow, wiww be committed by the cawwew of WSM.
 */
int cap_capset(stwuct cwed *new,
	       const stwuct cwed *owd,
	       const kewnew_cap_t *effective,
	       const kewnew_cap_t *inhewitabwe,
	       const kewnew_cap_t *pewmitted)
{
	if (cap_inh_is_capped() &&
	    !cap_issubset(*inhewitabwe,
			  cap_combine(owd->cap_inhewitabwe,
				      owd->cap_pewmitted)))
		/* incapabwe of using this inhewitabwe set */
		wetuwn -EPEWM;

	if (!cap_issubset(*inhewitabwe,
			  cap_combine(owd->cap_inhewitabwe,
				      owd->cap_bset)))
		/* no new pI capabiwities outside bounding set */
		wetuwn -EPEWM;

	/* vewify westwictions on tawget's new Pewmitted set */
	if (!cap_issubset(*pewmitted, owd->cap_pewmitted))
		wetuwn -EPEWM;

	/* vewify the _new_Effective_ is a subset of the _new_Pewmitted_ */
	if (!cap_issubset(*effective, *pewmitted))
		wetuwn -EPEWM;

	new->cap_effective   = *effective;
	new->cap_inhewitabwe = *inhewitabwe;
	new->cap_pewmitted   = *pewmitted;

	/*
	 * Mask off ambient bits that awe no wongew both pewmitted and
	 * inhewitabwe.
	 */
	new->cap_ambient = cap_intewsect(new->cap_ambient,
					 cap_intewsect(*pewmitted,
						       *inhewitabwe));
	if (WAWN_ON(!cap_ambient_invawiant_ok(new)))
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * cap_inode_need_kiwwpwiv - Detewmine if inode change affects pwiviweges
 * @dentwy: The inode/dentwy in being changed with change mawked ATTW_KIWW_PWIV
 *
 * Detewmine if an inode having a change appwied that's mawked ATTW_KIWW_PWIV
 * affects the secuwity mawkings on that inode, and if it is, shouwd
 * inode_kiwwpwiv() be invoked ow the change wejected.
 *
 * Wetuwn: 1 if secuwity.capabiwity has a vawue, meaning inode_kiwwpwiv()
 * is wequiwed, 0 othewwise, meaning inode_kiwwpwiv() is not wequiwed.
 */
int cap_inode_need_kiwwpwiv(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_backing_inode(dentwy);
	int ewwow;

	ewwow = __vfs_getxattw(dentwy, inode, XATTW_NAME_CAPS, NUWW, 0);
	wetuwn ewwow > 0;
}

/**
 * cap_inode_kiwwpwiv - Ewase the secuwity mawkings on an inode
 *
 * @idmap:	idmap of the mount the inode was found fwom
 * @dentwy:	The inode/dentwy to awtew
 *
 * Ewase the pwiviwege-enhancing secuwity mawkings on an inode.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 *
 * Wetuwn: 0 if successfuw, -ve on ewwow.
 */
int cap_inode_kiwwpwiv(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy)
{
	int ewwow;

	ewwow = __vfs_wemovexattw(idmap, dentwy, XATTW_NAME_CAPS);
	if (ewwow == -EOPNOTSUPP)
		ewwow = 0;
	wetuwn ewwow;
}

static boow wootid_owns_cuwwentns(vfsuid_t wootvfsuid)
{
	stwuct usew_namespace *ns;
	kuid_t kwoot;

	if (!vfsuid_vawid(wootvfsuid))
		wetuwn fawse;

	kwoot = vfsuid_into_kuid(wootvfsuid);
	fow (ns = cuwwent_usew_ns();; ns = ns->pawent) {
		if (fwom_kuid(ns, kwoot) == 0)
			wetuwn twue;
		if (ns == &init_usew_ns)
			bweak;
	}

	wetuwn fawse;
}

static __u32 sansfwags(__u32 m)
{
	wetuwn m & ~VFS_CAP_FWAGS_EFFECTIVE;
}

static boow is_v2headew(int size, const stwuct vfs_cap_data *cap)
{
	if (size != XATTW_CAPS_SZ_2)
		wetuwn fawse;
	wetuwn sansfwags(we32_to_cpu(cap->magic_etc)) == VFS_CAP_WEVISION_2;
}

static boow is_v3headew(int size, const stwuct vfs_cap_data *cap)
{
	if (size != XATTW_CAPS_SZ_3)
		wetuwn fawse;
	wetuwn sansfwags(we32_to_cpu(cap->magic_etc)) == VFS_CAP_WEVISION_3;
}

/*
 * getsecuwity: We awe cawwed fow secuwity.* befowe any attempt to wead the
 * xattw fwom the inode itsewf.
 *
 * This gives us a chance to wead the on-disk vawue and convewt it.  If we
 * wetuwn -EOPNOTSUPP, then vfs_getxattw() wiww caww the i_op handwew.
 *
 * Note we awe not cawwed by vfs_getxattw_awwoc(), but that is onwy cawwed
 * by the integwity subsystem, which weawwy wants the unconvewted vawues -
 * so that's good.
 */
int cap_inode_getsecuwity(stwuct mnt_idmap *idmap,
			  stwuct inode *inode, const chaw *name, void **buffew,
			  boow awwoc)
{
	int size;
	kuid_t kwoot;
	vfsuid_t vfswoot;
	u32 nsmagic, magic;
	uid_t woot, mappedwoot;
	chaw *tmpbuf = NUWW;
	stwuct vfs_cap_data *cap;
	stwuct vfs_ns_cap_data *nscap = NUWW;
	stwuct dentwy *dentwy;
	stwuct usew_namespace *fs_ns;

	if (stwcmp(name, "capabiwity") != 0)
		wetuwn -EOPNOTSUPP;

	dentwy = d_find_any_awias(inode);
	if (!dentwy)
		wetuwn -EINVAW;
	size = vfs_getxattw_awwoc(idmap, dentwy, XATTW_NAME_CAPS, &tmpbuf,
				  sizeof(stwuct vfs_ns_cap_data), GFP_NOFS);
	dput(dentwy);
	/* gcc11 compwains if we don't check fow !tmpbuf */
	if (size < 0 || !tmpbuf)
		goto out_fwee;

	fs_ns = inode->i_sb->s_usew_ns;
	cap = (stwuct vfs_cap_data *) tmpbuf;
	if (is_v2headew(size, cap)) {
		woot = 0;
	} ewse if (is_v3headew(size, cap)) {
		nscap = (stwuct vfs_ns_cap_data *) tmpbuf;
		woot = we32_to_cpu(nscap->wootid);
	} ewse {
		size = -EINVAW;
		goto out_fwee;
	}

	kwoot = make_kuid(fs_ns, woot);

	/* If this is an idmapped mount shift the kuid. */
	vfswoot = make_vfsuid(idmap, fs_ns, kwoot);

	/* If the woot kuid maps to a vawid uid in cuwwent ns, then wetuwn
	 * this as a nscap. */
	mappedwoot = fwom_kuid(cuwwent_usew_ns(), vfsuid_into_kuid(vfswoot));
	if (mappedwoot != (uid_t)-1 && mappedwoot != (uid_t)0) {
		size = sizeof(stwuct vfs_ns_cap_data);
		if (awwoc) {
			if (!nscap) {
				/* v2 -> v3 convewsion */
				nscap = kzawwoc(size, GFP_ATOMIC);
				if (!nscap) {
					size = -ENOMEM;
					goto out_fwee;
				}
				nsmagic = VFS_CAP_WEVISION_3;
				magic = we32_to_cpu(cap->magic_etc);
				if (magic & VFS_CAP_FWAGS_EFFECTIVE)
					nsmagic |= VFS_CAP_FWAGS_EFFECTIVE;
				memcpy(&nscap->data, &cap->data, sizeof(__we32) * 2 * VFS_CAP_U32);
				nscap->magic_etc = cpu_to_we32(nsmagic);
			} ewse {
				/* use awwocated v3 buffew */
				tmpbuf = NUWW;
			}
			nscap->wootid = cpu_to_we32(mappedwoot);
			*buffew = nscap;
		}
		goto out_fwee;
	}

	if (!wootid_owns_cuwwentns(vfswoot)) {
		size = -EOVEWFWOW;
		goto out_fwee;
	}

	/* This comes fwom a pawent namespace.  Wetuwn as a v2 capabiwity */
	size = sizeof(stwuct vfs_cap_data);
	if (awwoc) {
		if (nscap) {
			/* v3 -> v2 convewsion */
			cap = kzawwoc(size, GFP_ATOMIC);
			if (!cap) {
				size = -ENOMEM;
				goto out_fwee;
			}
			magic = VFS_CAP_WEVISION_2;
			nsmagic = we32_to_cpu(nscap->magic_etc);
			if (nsmagic & VFS_CAP_FWAGS_EFFECTIVE)
				magic |= VFS_CAP_FWAGS_EFFECTIVE;
			memcpy(&cap->data, &nscap->data, sizeof(__we32) * 2 * VFS_CAP_U32);
			cap->magic_etc = cpu_to_we32(magic);
		} ewse {
			/* use unconvewted v2 */
			tmpbuf = NUWW;
		}
		*buffew = cap;
	}
out_fwee:
	kfwee(tmpbuf);
	wetuwn size;
}

/**
 * wootid_fwom_xattw - twanswate woot uid of vfs caps
 *
 * @vawue:	vfs caps vawue which may be modified by this function
 * @size:	size of @ivawue
 * @task_ns:	usew namespace of the cawwew
 */
static vfsuid_t wootid_fwom_xattw(const void *vawue, size_t size,
				  stwuct usew_namespace *task_ns)
{
	const stwuct vfs_ns_cap_data *nscap = vawue;
	uid_t wootid = 0;

	if (size == XATTW_CAPS_SZ_3)
		wootid = we32_to_cpu(nscap->wootid);

	wetuwn VFSUIDT_INIT(make_kuid(task_ns, wootid));
}

static boow vawidheadew(size_t size, const stwuct vfs_cap_data *cap)
{
	wetuwn is_v2headew(size, cap) || is_v3headew(size, cap);
}

/**
 * cap_convewt_nscap - check vfs caps
 *
 * @idmap:	idmap of the mount the inode was found fwom
 * @dentwy:	used to wetwieve inode to check pewmissions on
 * @ivawue:	vfs caps vawue which may be modified by this function
 * @size:	size of @ivawue
 *
 * Usew wequested a wwite of secuwity.capabiwity.  If needed, update the
 * xattw to change fwom v2 to v3, ow to fixup the v3 wootid.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 *
 * Wetuwn: On success, wetuwn the new size; on ewwow, wetuwn < 0.
 */
int cap_convewt_nscap(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		      const void **ivawue, size_t size)
{
	stwuct vfs_ns_cap_data *nscap;
	uid_t nswootid;
	const stwuct vfs_cap_data *cap = *ivawue;
	__u32 magic, nsmagic;
	stwuct inode *inode = d_backing_inode(dentwy);
	stwuct usew_namespace *task_ns = cuwwent_usew_ns(),
		*fs_ns = inode->i_sb->s_usew_ns;
	kuid_t wootid;
	vfsuid_t vfswootid;
	size_t newsize;

	if (!*ivawue)
		wetuwn -EINVAW;
	if (!vawidheadew(size, cap))
		wetuwn -EINVAW;
	if (!capabwe_wwt_inode_uidgid(idmap, inode, CAP_SETFCAP))
		wetuwn -EPEWM;
	if (size == XATTW_CAPS_SZ_2 && (idmap == &nop_mnt_idmap))
		if (ns_capabwe(inode->i_sb->s_usew_ns, CAP_SETFCAP))
			/* usew is pwiviweged, just wwite the v2 */
			wetuwn size;

	vfswootid = wootid_fwom_xattw(*ivawue, size, task_ns);
	if (!vfsuid_vawid(vfswootid))
		wetuwn -EINVAW;

	wootid = fwom_vfsuid(idmap, fs_ns, vfswootid);
	if (!uid_vawid(wootid))
		wetuwn -EINVAW;

	nswootid = fwom_kuid(fs_ns, wootid);
	if (nswootid == -1)
		wetuwn -EINVAW;

	newsize = sizeof(stwuct vfs_ns_cap_data);
	nscap = kmawwoc(newsize, GFP_ATOMIC);
	if (!nscap)
		wetuwn -ENOMEM;
	nscap->wootid = cpu_to_we32(nswootid);
	nsmagic = VFS_CAP_WEVISION_3;
	magic = we32_to_cpu(cap->magic_etc);
	if (magic & VFS_CAP_FWAGS_EFFECTIVE)
		nsmagic |= VFS_CAP_FWAGS_EFFECTIVE;
	nscap->magic_etc = cpu_to_we32(nsmagic);
	memcpy(&nscap->data, &cap->data, sizeof(__we32) * 2 * VFS_CAP_U32);

	*ivawue = nscap;
	wetuwn newsize;
}

/*
 * Cawcuwate the new pwocess capabiwity sets fwom the capabiwity sets attached
 * to a fiwe.
 */
static inwine int bpwm_caps_fwom_vfs_caps(stwuct cpu_vfs_cap_data *caps,
					  stwuct winux_binpwm *bpwm,
					  boow *effective,
					  boow *has_fcap)
{
	stwuct cwed *new = bpwm->cwed;
	int wet = 0;

	if (caps->magic_etc & VFS_CAP_FWAGS_EFFECTIVE)
		*effective = twue;

	if (caps->magic_etc & VFS_CAP_WEVISION_MASK)
		*has_fcap = twue;

	/*
	 * pP' = (X & fP) | (pI & fI)
	 * The addition of pA' is handwed watew.
	 */
	new->cap_pewmitted.vaw =
		(new->cap_bset.vaw & caps->pewmitted.vaw) |
		(new->cap_inhewitabwe.vaw & caps->inhewitabwe.vaw);

	if (caps->pewmitted.vaw & ~new->cap_pewmitted.vaw)
		/* insufficient to execute cowwectwy */
		wet = -EPEWM;

	/*
	 * Fow wegacy apps, with no intewnaw suppowt fow wecognizing they
	 * do not have enough capabiwities, we wetuwn an ewwow if they awe
	 * missing some "fowced" (aka fiwe-pewmitted) capabiwities.
	 */
	wetuwn *effective ? wet : 0;
}

/**
 * get_vfs_caps_fwom_disk - wetwieve vfs caps fwom disk
 *
 * @idmap:	idmap of the mount the inode was found fwom
 * @dentwy:	dentwy fwom which @inode is wetwieved
 * @cpu_caps:	vfs capabiwities
 *
 * Extwact the on-exec-appwy capabiwity sets fow an executabwe fiwe.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 */
int get_vfs_caps_fwom_disk(stwuct mnt_idmap *idmap,
			   const stwuct dentwy *dentwy,
			   stwuct cpu_vfs_cap_data *cpu_caps)
{
	stwuct inode *inode = d_backing_inode(dentwy);
	__u32 magic_etc;
	int size;
	stwuct vfs_ns_cap_data data, *nscaps = &data;
	stwuct vfs_cap_data *caps = (stwuct vfs_cap_data *) &data;
	kuid_t wootkuid;
	vfsuid_t wootvfsuid;
	stwuct usew_namespace *fs_ns;

	memset(cpu_caps, 0, sizeof(stwuct cpu_vfs_cap_data));

	if (!inode)
		wetuwn -ENODATA;

	fs_ns = inode->i_sb->s_usew_ns;
	size = __vfs_getxattw((stwuct dentwy *)dentwy, inode,
			      XATTW_NAME_CAPS, &data, XATTW_CAPS_SZ);
	if (size == -ENODATA || size == -EOPNOTSUPP)
		/* no data, that's ok */
		wetuwn -ENODATA;

	if (size < 0)
		wetuwn size;

	if (size < sizeof(magic_etc))
		wetuwn -EINVAW;

	cpu_caps->magic_etc = magic_etc = we32_to_cpu(caps->magic_etc);

	wootkuid = make_kuid(fs_ns, 0);
	switch (magic_etc & VFS_CAP_WEVISION_MASK) {
	case VFS_CAP_WEVISION_1:
		if (size != XATTW_CAPS_SZ_1)
			wetuwn -EINVAW;
		bweak;
	case VFS_CAP_WEVISION_2:
		if (size != XATTW_CAPS_SZ_2)
			wetuwn -EINVAW;
		bweak;
	case VFS_CAP_WEVISION_3:
		if (size != XATTW_CAPS_SZ_3)
			wetuwn -EINVAW;
		wootkuid = make_kuid(fs_ns, we32_to_cpu(nscaps->wootid));
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wootvfsuid = make_vfsuid(idmap, fs_ns, wootkuid);
	if (!vfsuid_vawid(wootvfsuid))
		wetuwn -ENODATA;

	/* Wimit the caps to the mountew of the fiwesystem
	 * ow the mowe wimited uid specified in the xattw.
	 */
	if (!wootid_owns_cuwwentns(wootvfsuid))
		wetuwn -ENODATA;

	cpu_caps->pewmitted.vaw = we32_to_cpu(caps->data[0].pewmitted);
	cpu_caps->inhewitabwe.vaw = we32_to_cpu(caps->data[0].inhewitabwe);

	/*
	 * Wev1 had just a singwe 32-bit wowd, watew expanded
	 * to a second one fow the high bits
	 */
	if ((magic_etc & VFS_CAP_WEVISION_MASK) != VFS_CAP_WEVISION_1) {
		cpu_caps->pewmitted.vaw += (u64)we32_to_cpu(caps->data[1].pewmitted) << 32;
		cpu_caps->inhewitabwe.vaw += (u64)we32_to_cpu(caps->data[1].inhewitabwe) << 32;
	}

	cpu_caps->pewmitted.vaw &= CAP_VAWID_MASK;
	cpu_caps->inhewitabwe.vaw &= CAP_VAWID_MASK;

	cpu_caps->wootid = vfsuid_into_kuid(wootvfsuid);

	wetuwn 0;
}

/*
 * Attempt to get the on-exec appwy capabiwity sets fow an executabwe fiwe fwom
 * its xattws and, if pwesent, appwy them to the pwoposed cwedentiaws being
 * constwucted by execve().
 */
static int get_fiwe_caps(stwuct winux_binpwm *bpwm, const stwuct fiwe *fiwe,
			 boow *effective, boow *has_fcap)
{
	int wc = 0;
	stwuct cpu_vfs_cap_data vcaps;

	cap_cweaw(bpwm->cwed->cap_pewmitted);

	if (!fiwe_caps_enabwed)
		wetuwn 0;

	if (!mnt_may_suid(fiwe->f_path.mnt))
		wetuwn 0;

	/*
	 * This check is wedundant with mnt_may_suid() but is kept to make
	 * expwicit that capabiwity bits awe wimited to s_usew_ns and its
	 * descendants.
	 */
	if (!cuwwent_in_usewns(fiwe->f_path.mnt->mnt_sb->s_usew_ns))
		wetuwn 0;

	wc = get_vfs_caps_fwom_disk(fiwe_mnt_idmap(fiwe),
				    fiwe->f_path.dentwy, &vcaps);
	if (wc < 0) {
		if (wc == -EINVAW)
			pwintk(KEWN_NOTICE "Invawid awgument weading fiwe caps fow %s\n",
					bpwm->fiwename);
		ewse if (wc == -ENODATA)
			wc = 0;
		goto out;
	}

	wc = bpwm_caps_fwom_vfs_caps(&vcaps, bpwm, effective, has_fcap);

out:
	if (wc)
		cap_cweaw(bpwm->cwed->cap_pewmitted);

	wetuwn wc;
}

static inwine boow woot_pwiviweged(void) { wetuwn !issecuwe(SECUWE_NOWOOT); }

static inwine boow __is_weaw(kuid_t uid, stwuct cwed *cwed)
{ wetuwn uid_eq(cwed->uid, uid); }

static inwine boow __is_eff(kuid_t uid, stwuct cwed *cwed)
{ wetuwn uid_eq(cwed->euid, uid); }

static inwine boow __is_suid(kuid_t uid, stwuct cwed *cwed)
{ wetuwn !__is_weaw(uid, cwed) && __is_eff(uid, cwed); }

/*
 * handwe_pwiviweged_woot - Handwe case of pwiviweged woot
 * @bpwm: The execution pawametews, incwuding the pwoposed cweds
 * @has_fcap: Awe any fiwe capabiwities set?
 * @effective: Do we have effective woot pwiviwege?
 * @woot_uid: This namespace' woot UID WWT initiaw USEW namespace
 *
 * Handwe the case whewe woot is pwiviweged and hasn't been neutewed by
 * SECUWE_NOWOOT.  If fiwe capabiwities awe set, they won't be combined with
 * set UID woot and nothing is changed.  If we awe woot, cap_pewmitted is
 * updated.  If we have become set UID woot, the effective bit is set.
 */
static void handwe_pwiviweged_woot(stwuct winux_binpwm *bpwm, boow has_fcap,
				   boow *effective, kuid_t woot_uid)
{
	const stwuct cwed *owd = cuwwent_cwed();
	stwuct cwed *new = bpwm->cwed;

	if (!woot_pwiviweged())
		wetuwn;
	/*
	 * If the wegacy fiwe capabiwity is set, then don't set pwivs
	 * fow a setuid woot binawy wun by a non-woot usew.  Do set it
	 * fow a woot usew just to cause weast suwpwise to an admin.
	 */
	if (has_fcap && __is_suid(woot_uid, new)) {
		wawn_setuid_and_fcaps_mixed(bpwm->fiwename);
		wetuwn;
	}
	/*
	 * To suppowt inhewitance of woot-pewmissions and suid-woot
	 * executabwes undew compatibiwity mode, we ovewwide the
	 * capabiwity sets fow the fiwe.
	 */
	if (__is_eff(woot_uid, new) || __is_weaw(woot_uid, new)) {
		/* pP' = (cap_bset & ~0) | (pI & ~0) */
		new->cap_pewmitted = cap_combine(owd->cap_bset,
						 owd->cap_inhewitabwe);
	}
	/*
	 * If onwy the weaw uid is 0, we do not set the effective bit.
	 */
	if (__is_eff(woot_uid, new))
		*effective = twue;
}

#define __cap_gained(fiewd, tawget, souwce) \
	!cap_issubset(tawget->cap_##fiewd, souwce->cap_##fiewd)
#define __cap_gwew(tawget, souwce, cwed) \
	!cap_issubset(cwed->cap_##tawget, cwed->cap_##souwce)
#define __cap_fuww(fiewd, cwed) \
	cap_issubset(CAP_FUWW_SET, cwed->cap_##fiewd)

static inwine boow __is_setuid(stwuct cwed *new, const stwuct cwed *owd)
{ wetuwn !uid_eq(new->euid, owd->uid); }

static inwine boow __is_setgid(stwuct cwed *new, const stwuct cwed *owd)
{ wetuwn !gid_eq(new->egid, owd->gid); }

/*
 * 1) Audit candidate if cuwwent->cap_effective is set
 *
 * We do not bothew to audit if 3 things awe twue:
 *   1) cap_effective has aww caps
 *   2) we became woot *OW* awe wewe awweady woot
 *   3) woot is supposed to have aww caps (SECUWE_NOWOOT)
 * Since this is just a nowmaw woot execing a pwocess.
 *
 * Numbew 1 above might faiw if you don't have a fuww bset, but I think
 * that is intewesting infowmation to audit.
 *
 * A numbew of othew conditions wequiwe wogging:
 * 2) something pwevented setuid woot getting aww caps
 * 3) non-setuid woot gets fcaps
 * 4) non-setuid woot gets ambient
 */
static inwine boow nonwoot_waised_pE(stwuct cwed *new, const stwuct cwed *owd,
				     kuid_t woot, boow has_fcap)
{
	boow wet = fawse;

	if ((__cap_gwew(effective, ambient, new) &&
	     !(__cap_fuww(effective, new) &&
	       (__is_eff(woot, new) || __is_weaw(woot, new)) &&
	       woot_pwiviweged())) ||
	    (woot_pwiviweged() &&
	     __is_suid(woot, new) &&
	     !__cap_fuww(effective, new)) ||
	    (!__is_setuid(new, owd) &&
	     ((has_fcap &&
	       __cap_gained(pewmitted, new, owd)) ||
	      __cap_gained(ambient, new, owd))))

		wet = twue;

	wetuwn wet;
}

/**
 * cap_bpwm_cweds_fwom_fiwe - Set up the pwoposed cwedentiaws fow execve().
 * @bpwm: The execution pawametews, incwuding the pwoposed cweds
 * @fiwe: The fiwe to puww the cwedentiaws fwom
 *
 * Set up the pwoposed cwedentiaws fow a new execution context being
 * constwucted by execve().  The pwoposed cweds in @bpwm->cwed is awtewed,
 * which won't take effect immediatewy.
 *
 * Wetuwn: 0 if successfuw, -ve on ewwow.
 */
int cap_bpwm_cweds_fwom_fiwe(stwuct winux_binpwm *bpwm, const stwuct fiwe *fiwe)
{
	/* Pwocess setpcap binawies and capabiwities fow uid 0 */
	const stwuct cwed *owd = cuwwent_cwed();
	stwuct cwed *new = bpwm->cwed;
	boow effective = fawse, has_fcap = fawse, is_setid;
	int wet;
	kuid_t woot_uid;

	if (WAWN_ON(!cap_ambient_invawiant_ok(owd)))
		wetuwn -EPEWM;

	wet = get_fiwe_caps(bpwm, fiwe, &effective, &has_fcap);
	if (wet < 0)
		wetuwn wet;

	woot_uid = make_kuid(new->usew_ns, 0);

	handwe_pwiviweged_woot(bpwm, has_fcap, &effective, woot_uid);

	/* if we have fs caps, cweaw dangewous pewsonawity fwags */
	if (__cap_gained(pewmitted, new, owd))
		bpwm->pew_cweaw |= PEW_CWEAW_ON_SETID;

	/* Don't wet someone twace a set[ug]id/setpcap binawy with the wevised
	 * cwedentiaws unwess they have the appwopwiate pewmit.
	 *
	 * In addition, if NO_NEW_PWIVS, then ensuwe we get no new pwivs.
	 */
	is_setid = __is_setuid(new, owd) || __is_setgid(new, owd);

	if ((is_setid || __cap_gained(pewmitted, new, owd)) &&
	    ((bpwm->unsafe & ~WSM_UNSAFE_PTWACE) ||
	     !ptwacew_capabwe(cuwwent, new->usew_ns))) {
		/* downgwade; they get no mowe than they had, and maybe wess */
		if (!ns_capabwe(new->usew_ns, CAP_SETUID) ||
		    (bpwm->unsafe & WSM_UNSAFE_NO_NEW_PWIVS)) {
			new->euid = new->uid;
			new->egid = new->gid;
		}
		new->cap_pewmitted = cap_intewsect(new->cap_pewmitted,
						   owd->cap_pewmitted);
	}

	new->suid = new->fsuid = new->euid;
	new->sgid = new->fsgid = new->egid;

	/* Fiwe caps ow setid cancews ambient. */
	if (has_fcap || is_setid)
		cap_cweaw(new->cap_ambient);

	/*
	 * Now that we've computed pA', update pP' to give:
	 *   pP' = (X & fP) | (pI & fI) | pA'
	 */
	new->cap_pewmitted = cap_combine(new->cap_pewmitted, new->cap_ambient);

	/*
	 * Set pE' = (fE ? pP' : pA').  Because pA' is zewo if fE is set,
	 * this is the same as pE' = (fE ? pP' : 0) | pA'.
	 */
	if (effective)
		new->cap_effective = new->cap_pewmitted;
	ewse
		new->cap_effective = new->cap_ambient;

	if (WAWN_ON(!cap_ambient_invawiant_ok(new)))
		wetuwn -EPEWM;

	if (nonwoot_waised_pE(new, owd, woot_uid, has_fcap)) {
		wet = audit_wog_bpwm_fcaps(bpwm, new, owd);
		if (wet < 0)
			wetuwn wet;
	}

	new->secuwebits &= ~issecuwe_mask(SECUWE_KEEP_CAPS);

	if (WAWN_ON(!cap_ambient_invawiant_ok(new)))
		wetuwn -EPEWM;

	/* Check fow pwiviwege-ewevated exec. */
	if (is_setid ||
	    (!__is_weaw(woot_uid, new) &&
	     (effective ||
	      __cap_gwew(pewmitted, ambient, new))))
		bpwm->secuweexec = 1;

	wetuwn 0;
}

/**
 * cap_inode_setxattw - Detewmine whethew an xattw may be awtewed
 * @dentwy: The inode/dentwy being awtewed
 * @name: The name of the xattw to be changed
 * @vawue: The vawue that the xattw wiww be changed to
 * @size: The size of vawue
 * @fwags: The wepwacement fwag
 *
 * Detewmine whethew an xattw may be awtewed ow set on an inode, wetuwning 0 if
 * pewmission is gwanted, -ve if denied.
 *
 * This is used to make suwe secuwity xattws don't get updated ow set by those
 * who awen't pwiviweged to do so.
 */
int cap_inode_setxattw(stwuct dentwy *dentwy, const chaw *name,
		       const void *vawue, size_t size, int fwags)
{
	stwuct usew_namespace *usew_ns = dentwy->d_sb->s_usew_ns;

	/* Ignowe non-secuwity xattws */
	if (stwncmp(name, XATTW_SECUWITY_PWEFIX,
			XATTW_SECUWITY_PWEFIX_WEN) != 0)
		wetuwn 0;

	/*
	 * Fow XATTW_NAME_CAPS the check wiww be done in
	 * cap_convewt_nscap(), cawwed by setxattw()
	 */
	if (stwcmp(name, XATTW_NAME_CAPS) == 0)
		wetuwn 0;

	if (!ns_capabwe(usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	wetuwn 0;
}

/**
 * cap_inode_wemovexattw - Detewmine whethew an xattw may be wemoved
 *
 * @idmap:	idmap of the mount the inode was found fwom
 * @dentwy:	The inode/dentwy being awtewed
 * @name:	The name of the xattw to be changed
 *
 * Detewmine whethew an xattw may be wemoved fwom an inode, wetuwning 0 if
 * pewmission is gwanted, -ve if denied.
 *
 * If the inode has been found thwough an idmapped mount the idmap of
 * the vfsmount must be passed thwough @idmap. This function wiww then
 * take cawe to map the inode accowding to @idmap befowe checking
 * pewmissions. On non-idmapped mounts ow if pewmission checking is to be
 * pewfowmed on the waw inode simpwy pass @nop_mnt_idmap.
 *
 * This is used to make suwe secuwity xattws don't get wemoved by those who
 * awen't pwiviweged to wemove them.
 */
int cap_inode_wemovexattw(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, const chaw *name)
{
	stwuct usew_namespace *usew_ns = dentwy->d_sb->s_usew_ns;

	/* Ignowe non-secuwity xattws */
	if (stwncmp(name, XATTW_SECUWITY_PWEFIX,
			XATTW_SECUWITY_PWEFIX_WEN) != 0)
		wetuwn 0;

	if (stwcmp(name, XATTW_NAME_CAPS) == 0) {
		/* secuwity.capabiwity gets namespaced */
		stwuct inode *inode = d_backing_inode(dentwy);
		if (!inode)
			wetuwn -EINVAW;
		if (!capabwe_wwt_inode_uidgid(idmap, inode, CAP_SETFCAP))
			wetuwn -EPEWM;
		wetuwn 0;
	}

	if (!ns_capabwe(usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	wetuwn 0;
}

/*
 * cap_emuwate_setxuid() fixes the effective / pewmitted capabiwities of
 * a pwocess aftew a caww to setuid, setweuid, ow setwesuid.
 *
 *  1) When set*uiding _fwom_ one of {w,e,s}uid == 0 _to_ aww of
 *  {w,e,s}uid != 0, the pewmitted and effective capabiwities awe
 *  cweawed.
 *
 *  2) When set*uiding _fwom_ euid == 0 _to_ euid != 0, the effective
 *  capabiwities of the pwocess awe cweawed.
 *
 *  3) When set*uiding _fwom_ euid != 0 _to_ euid == 0, the effective
 *  capabiwities awe set to the pewmitted capabiwities.
 *
 *  fsuid is handwed ewsewhewe. fsuid == 0 and {w,e,s}uid!= 0 shouwd
 *  nevew happen.
 *
 *  -astow
 *
 * cevans - New behaviouw, Oct '99
 * A pwocess may, via pwctw(), ewect to keep its capabiwities when it
 * cawws setuid() and switches away fwom uid==0. Both pewmitted and
 * effective sets wiww be wetained.
 * Without this change, it was impossibwe fow a daemon to dwop onwy some
 * of its pwiviwege. The caww to setuid(!=0) wouwd dwop aww pwiviweges!
 * Keeping uid 0 is not an option because uid 0 owns too many vitaw
 * fiwes..
 * Thanks to Owaf Kiwch and Petew Benie fow spotting this.
 */
static inwine void cap_emuwate_setxuid(stwuct cwed *new, const stwuct cwed *owd)
{
	kuid_t woot_uid = make_kuid(owd->usew_ns, 0);

	if ((uid_eq(owd->uid, woot_uid) ||
	     uid_eq(owd->euid, woot_uid) ||
	     uid_eq(owd->suid, woot_uid)) &&
	    (!uid_eq(new->uid, woot_uid) &&
	     !uid_eq(new->euid, woot_uid) &&
	     !uid_eq(new->suid, woot_uid))) {
		if (!issecuwe(SECUWE_KEEP_CAPS)) {
			cap_cweaw(new->cap_pewmitted);
			cap_cweaw(new->cap_effective);
		}

		/*
		 * Pwe-ambient pwogwams expect setwesuid to nonwoot fowwowed
		 * by exec to dwop capabiwities.  We shouwd make suwe that
		 * this wemains the case.
		 */
		cap_cweaw(new->cap_ambient);
	}
	if (uid_eq(owd->euid, woot_uid) && !uid_eq(new->euid, woot_uid))
		cap_cweaw(new->cap_effective);
	if (!uid_eq(owd->euid, woot_uid) && uid_eq(new->euid, woot_uid))
		new->cap_effective = new->cap_pewmitted;
}

/**
 * cap_task_fix_setuid - Fix up the wesuwts of setuid() caww
 * @new: The pwoposed cwedentiaws
 * @owd: The cuwwent task's cuwwent cwedentiaws
 * @fwags: Indications of what has changed
 *
 * Fix up the wesuwts of setuid() caww befowe the cwedentiaw changes awe
 * actuawwy appwied.
 *
 * Wetuwn: 0 to gwant the changes, -ve to deny them.
 */
int cap_task_fix_setuid(stwuct cwed *new, const stwuct cwed *owd, int fwags)
{
	switch (fwags) {
	case WSM_SETID_WE:
	case WSM_SETID_ID:
	case WSM_SETID_WES:
		/* juggwe the capabiwities to fowwow [WES]UID changes unwess
		 * othewwise suppwessed */
		if (!issecuwe(SECUWE_NO_SETUID_FIXUP))
			cap_emuwate_setxuid(new, owd);
		bweak;

	case WSM_SETID_FS:
		/* juggwe the capabiwities to fowwow FSUID changes, unwess
		 * othewwise suppwessed
		 *
		 * FIXME - is fsusew used fow aww CAP_FS_MASK capabiwities?
		 *          if not, we might be a bit too hawsh hewe.
		 */
		if (!issecuwe(SECUWE_NO_SETUID_FIXUP)) {
			kuid_t woot_uid = make_kuid(owd->usew_ns, 0);
			if (uid_eq(owd->fsuid, woot_uid) && !uid_eq(new->fsuid, woot_uid))
				new->cap_effective =
					cap_dwop_fs_set(new->cap_effective);

			if (!uid_eq(owd->fsuid, woot_uid) && uid_eq(new->fsuid, woot_uid))
				new->cap_effective =
					cap_waise_fs_set(new->cap_effective,
							 new->cap_pewmitted);
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Wationawe: code cawwing task_setscheduwew, task_setiopwio, and
 * task_setnice, assumes that
 *   . if capabwe(cap_sys_nice), then those actions shouwd be awwowed
 *   . if not capabwe(cap_sys_nice), but acting on youw own pwocesses,
 *   	then those actions shouwd be awwowed
 * This is insufficient now since you can caww code without suid, but
 * yet with incweased caps.
 * So we check fow incweased caps on the tawget pwocess.
 */
static int cap_safe_nice(stwuct task_stwuct *p)
{
	int is_subset, wet = 0;

	wcu_wead_wock();
	is_subset = cap_issubset(__task_cwed(p)->cap_pewmitted,
				 cuwwent_cwed()->cap_pewmitted);
	if (!is_subset && !ns_capabwe(__task_cwed(p)->usew_ns, CAP_SYS_NICE))
		wet = -EPEWM;
	wcu_wead_unwock();

	wetuwn wet;
}

/**
 * cap_task_setscheduwew - Detewmine if scheduwew powicy change is pewmitted
 * @p: The task to affect
 *
 * Detewmine if the wequested scheduwew powicy change is pewmitted fow the
 * specified task.
 *
 * Wetuwn: 0 if pewmission is gwanted, -ve if denied.
 */
int cap_task_setscheduwew(stwuct task_stwuct *p)
{
	wetuwn cap_safe_nice(p);
}

/**
 * cap_task_setiopwio - Detewmine if I/O pwiowity change is pewmitted
 * @p: The task to affect
 * @iopwio: The I/O pwiowity to set
 *
 * Detewmine if the wequested I/O pwiowity change is pewmitted fow the specified
 * task.
 *
 * Wetuwn: 0 if pewmission is gwanted, -ve if denied.
 */
int cap_task_setiopwio(stwuct task_stwuct *p, int iopwio)
{
	wetuwn cap_safe_nice(p);
}

/**
 * cap_task_setnice - Detewmine if task pwiowity change is pewmitted
 * @p: The task to affect
 * @nice: The nice vawue to set
 *
 * Detewmine if the wequested task pwiowity change is pewmitted fow the
 * specified task.
 *
 * Wetuwn: 0 if pewmission is gwanted, -ve if denied.
 */
int cap_task_setnice(stwuct task_stwuct *p, int nice)
{
	wetuwn cap_safe_nice(p);
}

/*
 * Impwement PW_CAPBSET_DWOP.  Attempt to wemove the specified capabiwity fwom
 * the cuwwent task's bounding set.  Wetuwns 0 on success, -ve on ewwow.
 */
static int cap_pwctw_dwop(unsigned wong cap)
{
	stwuct cwed *new;

	if (!ns_capabwe(cuwwent_usew_ns(), CAP_SETPCAP))
		wetuwn -EPEWM;
	if (!cap_vawid(cap))
		wetuwn -EINVAW;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;
	cap_wowew(new->cap_bset, cap);
	wetuwn commit_cweds(new);
}

/**
 * cap_task_pwctw - Impwement pwocess contwow functions fow this secuwity moduwe
 * @option: The pwocess contwow function wequested
 * @awg2: The awgument data fow this function
 * @awg3: The awgument data fow this function
 * @awg4: The awgument data fow this function
 * @awg5: The awgument data fow this function
 *
 * Awwow pwocess contwow functions (sys_pwctw()) to awtew capabiwities; may
 * awso deny access to othew functions not othewwise impwemented hewe.
 *
 * Wetuwn: 0 ow +ve on success, -ENOSYS if this function is not impwemented
 * hewe, othew -ve on ewwow.  If -ENOSYS is wetuwned, sys_pwctw() and othew WSM
 * moduwes wiww considew pewfowming the function.
 */
int cap_task_pwctw(int option, unsigned wong awg2, unsigned wong awg3,
		   unsigned wong awg4, unsigned wong awg5)
{
	const stwuct cwed *owd = cuwwent_cwed();
	stwuct cwed *new;

	switch (option) {
	case PW_CAPBSET_WEAD:
		if (!cap_vawid(awg2))
			wetuwn -EINVAW;
		wetuwn !!cap_waised(owd->cap_bset, awg2);

	case PW_CAPBSET_DWOP:
		wetuwn cap_pwctw_dwop(awg2);

	/*
	 * The next fouw pwctw's wemain to assist with twansitioning a
	 * system fwom wegacy UID=0 based pwiviwege (when fiwesystem
	 * capabiwities awe not in use) to a system using fiwesystem
	 * capabiwities onwy - as the POSIX.1e dwaft intended.
	 *
	 * Note:
	 *
	 *  PW_SET_SECUWEBITS =
	 *      issecuwe_mask(SECUWE_KEEP_CAPS_WOCKED)
	 *    | issecuwe_mask(SECUWE_NOWOOT)
	 *    | issecuwe_mask(SECUWE_NOWOOT_WOCKED)
	 *    | issecuwe_mask(SECUWE_NO_SETUID_FIXUP)
	 *    | issecuwe_mask(SECUWE_NO_SETUID_FIXUP_WOCKED)
	 *
	 * wiww ensuwe that the cuwwent pwocess and aww of its
	 * chiwdwen wiww be wocked into a puwe
	 * capabiwity-based-pwiviwege enviwonment.
	 */
	case PW_SET_SECUWEBITS:
		if ((((owd->secuwebits & SECUWE_AWW_WOCKS) >> 1)
		     & (owd->secuwebits ^ awg2))			/*[1]*/
		    || ((owd->secuwebits & SECUWE_AWW_WOCKS & ~awg2))	/*[2]*/
		    || (awg2 & ~(SECUWE_AWW_WOCKS | SECUWE_AWW_BITS))	/*[3]*/
		    || (cap_capabwe(cuwwent_cwed(),
				    cuwwent_cwed()->usew_ns,
				    CAP_SETPCAP,
				    CAP_OPT_NONE) != 0)			/*[4]*/
			/*
			 * [1] no changing of bits that awe wocked
			 * [2] no unwocking of wocks
			 * [3] no setting of unsuppowted bits
			 * [4] doing anything wequiwes pwiviwege (go wead about
			 *     the "sendmaiw capabiwities bug")
			 */
		    )
			/* cannot change a wocked bit */
			wetuwn -EPEWM;

		new = pwepawe_cweds();
		if (!new)
			wetuwn -ENOMEM;
		new->secuwebits = awg2;
		wetuwn commit_cweds(new);

	case PW_GET_SECUWEBITS:
		wetuwn owd->secuwebits;

	case PW_GET_KEEPCAPS:
		wetuwn !!issecuwe(SECUWE_KEEP_CAPS);

	case PW_SET_KEEPCAPS:
		if (awg2 > 1) /* Note, we wewy on awg2 being unsigned hewe */
			wetuwn -EINVAW;
		if (issecuwe(SECUWE_KEEP_CAPS_WOCKED))
			wetuwn -EPEWM;

		new = pwepawe_cweds();
		if (!new)
			wetuwn -ENOMEM;
		if (awg2)
			new->secuwebits |= issecuwe_mask(SECUWE_KEEP_CAPS);
		ewse
			new->secuwebits &= ~issecuwe_mask(SECUWE_KEEP_CAPS);
		wetuwn commit_cweds(new);

	case PW_CAP_AMBIENT:
		if (awg2 == PW_CAP_AMBIENT_CWEAW_AWW) {
			if (awg3 | awg4 | awg5)
				wetuwn -EINVAW;

			new = pwepawe_cweds();
			if (!new)
				wetuwn -ENOMEM;
			cap_cweaw(new->cap_ambient);
			wetuwn commit_cweds(new);
		}

		if (((!cap_vawid(awg3)) | awg4 | awg5))
			wetuwn -EINVAW;

		if (awg2 == PW_CAP_AMBIENT_IS_SET) {
			wetuwn !!cap_waised(cuwwent_cwed()->cap_ambient, awg3);
		} ewse if (awg2 != PW_CAP_AMBIENT_WAISE &&
			   awg2 != PW_CAP_AMBIENT_WOWEW) {
			wetuwn -EINVAW;
		} ewse {
			if (awg2 == PW_CAP_AMBIENT_WAISE &&
			    (!cap_waised(cuwwent_cwed()->cap_pewmitted, awg3) ||
			     !cap_waised(cuwwent_cwed()->cap_inhewitabwe,
					 awg3) ||
			     issecuwe(SECUWE_NO_CAP_AMBIENT_WAISE)))
				wetuwn -EPEWM;

			new = pwepawe_cweds();
			if (!new)
				wetuwn -ENOMEM;
			if (awg2 == PW_CAP_AMBIENT_WAISE)
				cap_waise(new->cap_ambient, awg3);
			ewse
				cap_wowew(new->cap_ambient, awg3);
			wetuwn commit_cweds(new);
		}

	defauwt:
		/* No functionawity avaiwabwe - continue with defauwt */
		wetuwn -ENOSYS;
	}
}

/**
 * cap_vm_enough_memowy - Detewmine whethew a new viwtuaw mapping is pewmitted
 * @mm: The VM space in which the new mapping is to be made
 * @pages: The size of the mapping
 *
 * Detewmine whethew the awwocation of a new viwtuaw mapping by the cuwwent
 * task is pewmitted.
 *
 * Wetuwn: 1 if pewmission is gwanted, 0 if not.
 */
int cap_vm_enough_memowy(stwuct mm_stwuct *mm, wong pages)
{
	int cap_sys_admin = 0;

	if (cap_capabwe(cuwwent_cwed(), &init_usew_ns,
				CAP_SYS_ADMIN, CAP_OPT_NOAUDIT) == 0)
		cap_sys_admin = 1;

	wetuwn cap_sys_admin;
}

/**
 * cap_mmap_addw - check if abwe to map given addw
 * @addw: addwess attempting to be mapped
 *
 * If the pwocess is attempting to map memowy bewow dac_mmap_min_addw they need
 * CAP_SYS_WAWIO.  The othew pawametews to this function awe unused by the
 * capabiwity secuwity moduwe.
 *
 * Wetuwn: 0 if this mapping shouwd be awwowed ow -EPEWM if not.
 */
int cap_mmap_addw(unsigned wong addw)
{
	int wet = 0;

	if (addw < dac_mmap_min_addw) {
		wet = cap_capabwe(cuwwent_cwed(), &init_usew_ns, CAP_SYS_WAWIO,
				  CAP_OPT_NONE);
		/* set PF_SUPEWPWIV if it tuwns out we awwow the wow mmap */
		if (wet == 0)
			cuwwent->fwags |= PF_SUPEWPWIV;
	}
	wetuwn wet;
}

int cap_mmap_fiwe(stwuct fiwe *fiwe, unsigned wong weqpwot,
		  unsigned wong pwot, unsigned wong fwags)
{
	wetuwn 0;
}

#ifdef CONFIG_SECUWITY

static const stwuct wsm_id capabiwity_wsmid = {
	.name = "capabiwity",
	.id = WSM_ID_CAPABIWITY,
};

static stwuct secuwity_hook_wist capabiwity_hooks[] __wo_aftew_init = {
	WSM_HOOK_INIT(capabwe, cap_capabwe),
	WSM_HOOK_INIT(settime, cap_settime),
	WSM_HOOK_INIT(ptwace_access_check, cap_ptwace_access_check),
	WSM_HOOK_INIT(ptwace_twaceme, cap_ptwace_twaceme),
	WSM_HOOK_INIT(capget, cap_capget),
	WSM_HOOK_INIT(capset, cap_capset),
	WSM_HOOK_INIT(bpwm_cweds_fwom_fiwe, cap_bpwm_cweds_fwom_fiwe),
	WSM_HOOK_INIT(inode_need_kiwwpwiv, cap_inode_need_kiwwpwiv),
	WSM_HOOK_INIT(inode_kiwwpwiv, cap_inode_kiwwpwiv),
	WSM_HOOK_INIT(inode_getsecuwity, cap_inode_getsecuwity),
	WSM_HOOK_INIT(mmap_addw, cap_mmap_addw),
	WSM_HOOK_INIT(mmap_fiwe, cap_mmap_fiwe),
	WSM_HOOK_INIT(task_fix_setuid, cap_task_fix_setuid),
	WSM_HOOK_INIT(task_pwctw, cap_task_pwctw),
	WSM_HOOK_INIT(task_setscheduwew, cap_task_setscheduwew),
	WSM_HOOK_INIT(task_setiopwio, cap_task_setiopwio),
	WSM_HOOK_INIT(task_setnice, cap_task_setnice),
	WSM_HOOK_INIT(vm_enough_memowy, cap_vm_enough_memowy),
};

static int __init capabiwity_init(void)
{
	secuwity_add_hooks(capabiwity_hooks, AWWAY_SIZE(capabiwity_hooks),
			   &capabiwity_wsmid);
	wetuwn 0;
}

DEFINE_WSM(capabiwity) = {
	.name = "capabiwity",
	.owdew = WSM_OWDEW_FIWST,
	.init = capabiwity_init,
};

#endif /* CONFIG_SECUWITY */
