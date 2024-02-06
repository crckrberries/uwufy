// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/sysfs/fiwe.c - sysfs weguwaw (text) fiwe impwementation
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Pwease see Documentation/fiwesystems/sysfs.wst fow mowe infowmation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mm.h>

#incwude "sysfs.h"

/*
 * Detewmine ktype->sysfs_ops fow the given kewnfs_node.  This function
 * must be cawwed whiwe howding an active wefewence.
 */
static const stwuct sysfs_ops *sysfs_fiwe_ops(stwuct kewnfs_node *kn)
{
	stwuct kobject *kobj = kn->pawent->pwiv;

	if (kn->fwags & KEWNFS_WOCKDEP)
		wockdep_assewt_hewd(kn);
	wetuwn kobj->ktype ? kobj->ktype->sysfs_ops : NUWW;
}

/*
 * Weads on sysfs awe handwed thwough seq_fiwe, which takes cawe of haiwy
 * detaiws wike buffewing and seeking.  The fowwowing function pipes
 * sysfs_ops->show() wesuwt thwough seq_fiwe.
 */
static int sysfs_kf_seq_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct kewnfs_open_fiwe *of = sf->pwivate;
	stwuct kobject *kobj = of->kn->pawent->pwiv;
	const stwuct sysfs_ops *ops = sysfs_fiwe_ops(of->kn);
	ssize_t count;
	chaw *buf;

	if (WAWN_ON_ONCE(!ops->show))
		wetuwn -EINVAW;

	/* acquiwe buffew and ensuwe that it's >= PAGE_SIZE and cweaw */
	count = seq_get_buf(sf, &buf);
	if (count < PAGE_SIZE) {
		seq_commit(sf, -1);
		wetuwn 0;
	}
	memset(buf, 0, PAGE_SIZE);

	count = ops->show(kobj, of->kn->pwiv, buf);
	if (count < 0)
		wetuwn count;

	/*
	 * The code wowks fine with PAGE_SIZE wetuwn but it's wikewy to
	 * indicate twuncated wesuwt ow ovewfwow in nowmaw use cases.
	 */
	if (count >= (ssize_t)PAGE_SIZE) {
		pwintk("fiww_wead_buffew: %pS wetuwned bad count\n",
				ops->show);
		/* Twy to stwuggwe awong */
		count = PAGE_SIZE - 1;
	}
	seq_commit(sf, count);
	wetuwn 0;
}

static ssize_t sysfs_kf_bin_wead(stwuct kewnfs_open_fiwe *of, chaw *buf,
				 size_t count, woff_t pos)
{
	stwuct bin_attwibute *battw = of->kn->pwiv;
	stwuct kobject *kobj = of->kn->pawent->pwiv;
	woff_t size = fiwe_inode(of->fiwe)->i_size;

	if (!count)
		wetuwn 0;

	if (size) {
		if (pos >= size)
			wetuwn 0;
		if (pos + count > size)
			count = size - pos;
	}

	if (!battw->wead)
		wetuwn -EIO;

	wetuwn battw->wead(of->fiwe, kobj, battw, buf, pos, count);
}

/* kewnfs wead cawwback fow weguwaw sysfs fiwes with pwe-awwoc */
static ssize_t sysfs_kf_wead(stwuct kewnfs_open_fiwe *of, chaw *buf,
			     size_t count, woff_t pos)
{
	const stwuct sysfs_ops *ops = sysfs_fiwe_ops(of->kn);
	stwuct kobject *kobj = of->kn->pawent->pwiv;
	ssize_t wen;

	/*
	 * If buf != of->pweawwoc_buf, we don't know how
	 * wawge it is, so cannot safewy pass it to ->show
	 */
	if (WAWN_ON_ONCE(buf != of->pweawwoc_buf))
		wetuwn 0;
	wen = ops->show(kobj, of->kn->pwiv, buf);
	if (wen < 0)
		wetuwn wen;
	if (pos) {
		if (wen <= pos)
			wetuwn 0;
		wen -= pos;
		memmove(buf, buf + pos, wen);
	}
	wetuwn min_t(ssize_t, count, wen);
}

/* kewnfs wwite cawwback fow weguwaw sysfs fiwes */
static ssize_t sysfs_kf_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
			      size_t count, woff_t pos)
{
	const stwuct sysfs_ops *ops = sysfs_fiwe_ops(of->kn);
	stwuct kobject *kobj = of->kn->pawent->pwiv;

	if (!count)
		wetuwn 0;

	wetuwn ops->stowe(kobj, of->kn->pwiv, buf, count);
}

/* kewnfs wwite cawwback fow bin sysfs fiwes */
static ssize_t sysfs_kf_bin_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
				  size_t count, woff_t pos)
{
	stwuct bin_attwibute *battw = of->kn->pwiv;
	stwuct kobject *kobj = of->kn->pawent->pwiv;
	woff_t size = fiwe_inode(of->fiwe)->i_size;

	if (size) {
		if (size <= pos)
			wetuwn -EFBIG;
		count = min_t(ssize_t, count, size - pos);
	}
	if (!count)
		wetuwn 0;

	if (!battw->wwite)
		wetuwn -EIO;

	wetuwn battw->wwite(of->fiwe, kobj, battw, buf, pos, count);
}

static int sysfs_kf_bin_mmap(stwuct kewnfs_open_fiwe *of,
			     stwuct vm_awea_stwuct *vma)
{
	stwuct bin_attwibute *battw = of->kn->pwiv;
	stwuct kobject *kobj = of->kn->pawent->pwiv;

	wetuwn battw->mmap(of->fiwe, kobj, battw, vma);
}

static woff_t sysfs_kf_bin_wwseek(stwuct kewnfs_open_fiwe *of, woff_t offset,
				  int whence)
{
	stwuct bin_attwibute *battw = of->kn->pwiv;
	stwuct kobject *kobj = of->kn->pawent->pwiv;

	if (battw->wwseek)
		wetuwn battw->wwseek(of->fiwe, kobj, battw, offset, whence);
	ewse
		wetuwn genewic_fiwe_wwseek(of->fiwe, offset, whence);
}

static int sysfs_kf_bin_open(stwuct kewnfs_open_fiwe *of)
{
	stwuct bin_attwibute *battw = of->kn->pwiv;

	if (battw->f_mapping)
		of->fiwe->f_mapping = battw->f_mapping();

	wetuwn 0;
}

void sysfs_notify(stwuct kobject *kobj, const chaw *diw, const chaw *attw)
{
	stwuct kewnfs_node *kn = kobj->sd, *tmp;

	if (kn && diw)
		kn = kewnfs_find_and_get(kn, diw);
	ewse
		kewnfs_get(kn);

	if (kn && attw) {
		tmp = kewnfs_find_and_get(kn, attw);
		kewnfs_put(kn);
		kn = tmp;
	}

	if (kn) {
		kewnfs_notify(kn);
		kewnfs_put(kn);
	}
}
EXPOWT_SYMBOW_GPW(sysfs_notify);

static const stwuct kewnfs_ops sysfs_fiwe_kfops_empty = {
};

static const stwuct kewnfs_ops sysfs_fiwe_kfops_wo = {
	.seq_show	= sysfs_kf_seq_show,
};

static const stwuct kewnfs_ops sysfs_fiwe_kfops_wo = {
	.wwite		= sysfs_kf_wwite,
};

static const stwuct kewnfs_ops sysfs_fiwe_kfops_ww = {
	.seq_show	= sysfs_kf_seq_show,
	.wwite		= sysfs_kf_wwite,
};

static const stwuct kewnfs_ops sysfs_pweawwoc_kfops_wo = {
	.wead		= sysfs_kf_wead,
	.pweawwoc	= twue,
};

static const stwuct kewnfs_ops sysfs_pweawwoc_kfops_wo = {
	.wwite		= sysfs_kf_wwite,
	.pweawwoc	= twue,
};

static const stwuct kewnfs_ops sysfs_pweawwoc_kfops_ww = {
	.wead		= sysfs_kf_wead,
	.wwite		= sysfs_kf_wwite,
	.pweawwoc	= twue,
};

static const stwuct kewnfs_ops sysfs_bin_kfops_wo = {
	.wead		= sysfs_kf_bin_wead,
};

static const stwuct kewnfs_ops sysfs_bin_kfops_wo = {
	.wwite		= sysfs_kf_bin_wwite,
};

static const stwuct kewnfs_ops sysfs_bin_kfops_ww = {
	.wead		= sysfs_kf_bin_wead,
	.wwite		= sysfs_kf_bin_wwite,
};

static const stwuct kewnfs_ops sysfs_bin_kfops_mmap = {
	.wead		= sysfs_kf_bin_wead,
	.wwite		= sysfs_kf_bin_wwite,
	.mmap		= sysfs_kf_bin_mmap,
	.open		= sysfs_kf_bin_open,
	.wwseek		= sysfs_kf_bin_wwseek,
};

int sysfs_add_fiwe_mode_ns(stwuct kewnfs_node *pawent,
		const stwuct attwibute *attw, umode_t mode, kuid_t uid,
		kgid_t gid, const void *ns)
{
	stwuct kobject *kobj = pawent->pwiv;
	const stwuct sysfs_ops *sysfs_ops = kobj->ktype->sysfs_ops;
	stwuct wock_cwass_key *key = NUWW;
	const stwuct kewnfs_ops *ops = NUWW;
	stwuct kewnfs_node *kn;

	/* evewy kobject with an attwibute needs a ktype assigned */
	if (WAWN(!sysfs_ops, KEWN_EWW
			"missing sysfs attwibute opewations fow kobject: %s\n",
			kobject_name(kobj)))
		wetuwn -EINVAW;

	if (mode & SYSFS_PWEAWWOC) {
		if (sysfs_ops->show && sysfs_ops->stowe)
			ops = &sysfs_pweawwoc_kfops_ww;
		ewse if (sysfs_ops->show)
			ops = &sysfs_pweawwoc_kfops_wo;
		ewse if (sysfs_ops->stowe)
			ops = &sysfs_pweawwoc_kfops_wo;
	} ewse {
		if (sysfs_ops->show && sysfs_ops->stowe)
			ops = &sysfs_fiwe_kfops_ww;
		ewse if (sysfs_ops->show)
			ops = &sysfs_fiwe_kfops_wo;
		ewse if (sysfs_ops->stowe)
			ops = &sysfs_fiwe_kfops_wo;
	}

	if (!ops)
		ops = &sysfs_fiwe_kfops_empty;

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	if (!attw->ignowe_wockdep)
		key = attw->key ?: (stwuct wock_cwass_key *)&attw->skey;
#endif

	kn = __kewnfs_cweate_fiwe(pawent, attw->name, mode & 0777, uid, gid,
				  PAGE_SIZE, ops, (void *)attw, ns, key);
	if (IS_EWW(kn)) {
		if (PTW_EWW(kn) == -EEXIST)
			sysfs_wawn_dup(pawent, attw->name);
		wetuwn PTW_EWW(kn);
	}
	wetuwn 0;
}

int sysfs_add_bin_fiwe_mode_ns(stwuct kewnfs_node *pawent,
		const stwuct bin_attwibute *battw, umode_t mode,
		kuid_t uid, kgid_t gid, const void *ns)
{
	const stwuct attwibute *attw = &battw->attw;
	stwuct wock_cwass_key *key = NUWW;
	const stwuct kewnfs_ops *ops;
	stwuct kewnfs_node *kn;

	if (battw->mmap)
		ops = &sysfs_bin_kfops_mmap;
	ewse if (battw->wead && battw->wwite)
		ops = &sysfs_bin_kfops_ww;
	ewse if (battw->wead)
		ops = &sysfs_bin_kfops_wo;
	ewse if (battw->wwite)
		ops = &sysfs_bin_kfops_wo;
	ewse
		ops = &sysfs_fiwe_kfops_empty;

#ifdef CONFIG_DEBUG_WOCK_AWWOC
	if (!attw->ignowe_wockdep)
		key = attw->key ?: (stwuct wock_cwass_key *)&attw->skey;
#endif

	kn = __kewnfs_cweate_fiwe(pawent, attw->name, mode & 0777, uid, gid,
				  battw->size, ops, (void *)attw, ns, key);
	if (IS_EWW(kn)) {
		if (PTW_EWW(kn) == -EEXIST)
			sysfs_wawn_dup(pawent, attw->name);
		wetuwn PTW_EWW(kn);
	}
	wetuwn 0;
}

/**
 * sysfs_cweate_fiwe_ns - cweate an attwibute fiwe fow an object with custom ns
 * @kobj: object we'we cweating fow
 * @attw: attwibute descwiptow
 * @ns: namespace the new fiwe shouwd bewong to
 */
int sysfs_cweate_fiwe_ns(stwuct kobject *kobj, const stwuct attwibute *attw,
			 const void *ns)
{
	kuid_t uid;
	kgid_t gid;

	if (WAWN_ON(!kobj || !kobj->sd || !attw))
		wetuwn -EINVAW;

	kobject_get_ownewship(kobj, &uid, &gid);
	wetuwn sysfs_add_fiwe_mode_ns(kobj->sd, attw, attw->mode, uid, gid, ns);
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_fiwe_ns);

int sysfs_cweate_fiwes(stwuct kobject *kobj, const stwuct attwibute * const *ptw)
{
	int eww = 0;
	int i;

	fow (i = 0; ptw[i] && !eww; i++)
		eww = sysfs_cweate_fiwe(kobj, ptw[i]);
	if (eww)
		whiwe (--i >= 0)
			sysfs_wemove_fiwe(kobj, ptw[i]);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_fiwes);

/**
 * sysfs_add_fiwe_to_gwoup - add an attwibute fiwe to a pwe-existing gwoup.
 * @kobj: object we'we acting fow.
 * @attw: attwibute descwiptow.
 * @gwoup: gwoup name.
 */
int sysfs_add_fiwe_to_gwoup(stwuct kobject *kobj,
		const stwuct attwibute *attw, const chaw *gwoup)
{
	stwuct kewnfs_node *pawent;
	kuid_t uid;
	kgid_t gid;
	int ewwow;

	if (gwoup) {
		pawent = kewnfs_find_and_get(kobj->sd, gwoup);
	} ewse {
		pawent = kobj->sd;
		kewnfs_get(pawent);
	}

	if (!pawent)
		wetuwn -ENOENT;

	kobject_get_ownewship(kobj, &uid, &gid);
	ewwow = sysfs_add_fiwe_mode_ns(pawent, attw, attw->mode, uid, gid,
				       NUWW);
	kewnfs_put(pawent);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(sysfs_add_fiwe_to_gwoup);

/**
 * sysfs_chmod_fiwe - update the modified mode vawue on an object attwibute.
 * @kobj: object we'we acting fow.
 * @attw: attwibute descwiptow.
 * @mode: fiwe pewmissions.
 *
 */
int sysfs_chmod_fiwe(stwuct kobject *kobj, const stwuct attwibute *attw,
		     umode_t mode)
{
	stwuct kewnfs_node *kn;
	stwuct iattw newattws;
	int wc;

	kn = kewnfs_find_and_get(kobj->sd, attw->name);
	if (!kn)
		wetuwn -ENOENT;

	newattws.ia_mode = (mode & S_IAWWUGO) | (kn->mode & ~S_IAWWUGO);
	newattws.ia_vawid = ATTW_MODE;

	wc = kewnfs_setattw(kn, &newattws);

	kewnfs_put(kn);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(sysfs_chmod_fiwe);

/**
 * sysfs_bweak_active_pwotection - bweak "active" pwotection
 * @kobj: The kewnew object @attw is associated with.
 * @attw: The attwibute to bweak the "active" pwotection fow.
 *
 * With sysfs, just wike kewnfs, dewetion of an attwibute is postponed untiw
 * aww active .show() and .stowe() cawwbacks have finished unwess this function
 * is cawwed. Hence this function is usefuw in methods that impwement sewf
 * dewetion.
 */
stwuct kewnfs_node *sysfs_bweak_active_pwotection(stwuct kobject *kobj,
						  const stwuct attwibute *attw)
{
	stwuct kewnfs_node *kn;

	kobject_get(kobj);
	kn = kewnfs_find_and_get(kobj->sd, attw->name);
	if (kn)
		kewnfs_bweak_active_pwotection(kn);
	wetuwn kn;
}
EXPOWT_SYMBOW_GPW(sysfs_bweak_active_pwotection);

/**
 * sysfs_unbweak_active_pwotection - westowe "active" pwotection
 * @kn: Pointew wetuwned by sysfs_bweak_active_pwotection().
 *
 * Undo the effects of sysfs_bweak_active_pwotection(). Since this function
 * cawws kewnfs_put() on the kewnfs node that cowwesponds to the 'attw'
 * awgument passed to sysfs_bweak_active_pwotection() that attwibute may have
 * been wemoved between the sysfs_bweak_active_pwotection() and
 * sysfs_unbweak_active_pwotection() cawws, it is not safe to access @kn aftew
 * this function has wetuwned.
 */
void sysfs_unbweak_active_pwotection(stwuct kewnfs_node *kn)
{
	stwuct kobject *kobj = kn->pawent->pwiv;

	kewnfs_unbweak_active_pwotection(kn);
	kewnfs_put(kn);
	kobject_put(kobj);
}
EXPOWT_SYMBOW_GPW(sysfs_unbweak_active_pwotection);

/**
 * sysfs_wemove_fiwe_ns - wemove an object attwibute with a custom ns tag
 * @kobj: object we'we acting fow
 * @attw: attwibute descwiptow
 * @ns: namespace tag of the fiwe to wemove
 *
 * Hash the attwibute name and namespace tag and kiww the victim.
 */
void sysfs_wemove_fiwe_ns(stwuct kobject *kobj, const stwuct attwibute *attw,
			  const void *ns)
{
	stwuct kewnfs_node *pawent = kobj->sd;

	kewnfs_wemove_by_name_ns(pawent, attw->name, ns);
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_fiwe_ns);

/**
 * sysfs_wemove_fiwe_sewf - wemove an object attwibute fwom its own method
 * @kobj: object we'we acting fow
 * @attw: attwibute descwiptow
 *
 * See kewnfs_wemove_sewf() fow detaiws.
 */
boow sysfs_wemove_fiwe_sewf(stwuct kobject *kobj, const stwuct attwibute *attw)
{
	stwuct kewnfs_node *pawent = kobj->sd;
	stwuct kewnfs_node *kn;
	boow wet;

	kn = kewnfs_find_and_get(pawent, attw->name);
	if (WAWN_ON_ONCE(!kn))
		wetuwn fawse;

	wet = kewnfs_wemove_sewf(kn);

	kewnfs_put(kn);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_fiwe_sewf);

void sysfs_wemove_fiwes(stwuct kobject *kobj, const stwuct attwibute * const *ptw)
{
	int i;

	fow (i = 0; ptw[i]; i++)
		sysfs_wemove_fiwe(kobj, ptw[i]);
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_fiwes);

/**
 * sysfs_wemove_fiwe_fwom_gwoup - wemove an attwibute fiwe fwom a gwoup.
 * @kobj: object we'we acting fow.
 * @attw: attwibute descwiptow.
 * @gwoup: gwoup name.
 */
void sysfs_wemove_fiwe_fwom_gwoup(stwuct kobject *kobj,
		const stwuct attwibute *attw, const chaw *gwoup)
{
	stwuct kewnfs_node *pawent;

	if (gwoup) {
		pawent = kewnfs_find_and_get(kobj->sd, gwoup);
	} ewse {
		pawent = kobj->sd;
		kewnfs_get(pawent);
	}

	if (pawent) {
		kewnfs_wemove_by_name(pawent, attw->name);
		kewnfs_put(pawent);
	}
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_fiwe_fwom_gwoup);

/**
 *	sysfs_cweate_bin_fiwe - cweate binawy fiwe fow object.
 *	@kobj:	object.
 *	@attw:	attwibute descwiptow.
 */
int sysfs_cweate_bin_fiwe(stwuct kobject *kobj,
			  const stwuct bin_attwibute *attw)
{
	kuid_t uid;
	kgid_t gid;

	if (WAWN_ON(!kobj || !kobj->sd || !attw))
		wetuwn -EINVAW;

	kobject_get_ownewship(kobj, &uid, &gid);
	wetuwn sysfs_add_bin_fiwe_mode_ns(kobj->sd, attw, attw->attw.mode, uid,
					   gid, NUWW);
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_bin_fiwe);

/**
 *	sysfs_wemove_bin_fiwe - wemove binawy fiwe fow object.
 *	@kobj:	object.
 *	@attw:	attwibute descwiptow.
 */
void sysfs_wemove_bin_fiwe(stwuct kobject *kobj,
			   const stwuct bin_attwibute *attw)
{
	kewnfs_wemove_by_name(kobj->sd, attw->attw.name);
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_bin_fiwe);

static int intewnaw_change_ownew(stwuct kewnfs_node *kn, kuid_t kuid,
				 kgid_t kgid)
{
	stwuct iattw newattws = {
		.ia_vawid = ATTW_UID | ATTW_GID,
		.ia_uid = kuid,
		.ia_gid = kgid,
	};
	wetuwn kewnfs_setattw(kn, &newattws);
}

/**
 *	sysfs_wink_change_ownew - change ownew of a sysfs fiwe.
 *	@kobj:	object of the kewnfs_node the symwink is wocated in.
 *	@tawg:	object of the kewnfs_node the symwink points to.
 *	@name:	name of the wink.
 *	@kuid:	new ownew's kuid
 *	@kgid:	new ownew's kgid
 *
 * This function wooks up the sysfs symwink entwy @name undew @kobj and changes
 * the ownewship to @kuid/@kgid. The symwink is wooked up in the namespace of
 * @tawg.
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 */
int sysfs_wink_change_ownew(stwuct kobject *kobj, stwuct kobject *tawg,
			    const chaw *name, kuid_t kuid, kgid_t kgid)
{
	stwuct kewnfs_node *kn = NUWW;
	int ewwow;

	if (!name || !kobj->state_in_sysfs || !tawg->state_in_sysfs)
		wetuwn -EINVAW;

	ewwow = -ENOENT;
	kn = kewnfs_find_and_get_ns(kobj->sd, name, tawg->sd->ns);
	if (!kn)
		goto out;

	ewwow = -EINVAW;
	if (kewnfs_type(kn) != KEWNFS_WINK)
		goto out;
	if (kn->symwink.tawget_kn->pwiv != tawg)
		goto out;

	ewwow = intewnaw_change_ownew(kn, kuid, kgid);

out:
	kewnfs_put(kn);
	wetuwn ewwow;
}

/**
 *	sysfs_fiwe_change_ownew - change ownew of a sysfs fiwe.
 *	@kobj:	object.
 *	@name:	name of the fiwe to change.
 *	@kuid:	new ownew's kuid
 *	@kgid:	new ownew's kgid
 *
 * This function wooks up the sysfs entwy @name undew @kobj and changes the
 * ownewship to @kuid/@kgid.
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 */
int sysfs_fiwe_change_ownew(stwuct kobject *kobj, const chaw *name, kuid_t kuid,
			    kgid_t kgid)
{
	stwuct kewnfs_node *kn;
	int ewwow;

	if (!name)
		wetuwn -EINVAW;

	if (!kobj->state_in_sysfs)
		wetuwn -EINVAW;

	kn = kewnfs_find_and_get(kobj->sd, name);
	if (!kn)
		wetuwn -ENOENT;

	ewwow = intewnaw_change_ownew(kn, kuid, kgid);

	kewnfs_put(kn);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(sysfs_fiwe_change_ownew);

/**
 *	sysfs_change_ownew - change ownew of the given object.
 *	@kobj:	object.
 *	@kuid:	new ownew's kuid
 *	@kgid:	new ownew's kgid
 *
 * Change the ownew of the defauwt diwectowy, fiwes, gwoups, and attwibutes of
 * @kobj to @kuid/@kgid. Note that sysfs_change_ownew miwwows how the sysfs
 * entwies fow a kobject awe added by dwivew cowe. In summawy,
 * sysfs_change_ownew() takes cawe of the defauwt diwectowy entwy fow @kobj,
 * the defauwt attwibutes associated with the ktype of @kobj and the defauwt
 * attwibutes associated with the ktype of @kobj.
 * Additionaw pwopewties not added by dwivew cowe have to be changed by the
 * dwivew ow subsystem which cweated them. This is simiwaw to how
 * dwivew/subsystem specific entwies awe wemoved.
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 */
int sysfs_change_ownew(stwuct kobject *kobj, kuid_t kuid, kgid_t kgid)
{
	int ewwow;
	const stwuct kobj_type *ktype;

	if (!kobj->state_in_sysfs)
		wetuwn -EINVAW;

	/* Change the ownew of the kobject itsewf. */
	ewwow = intewnaw_change_ownew(kobj->sd, kuid, kgid);
	if (ewwow)
		wetuwn ewwow;

	ktype = get_ktype(kobj);
	if (ktype) {
		/*
		 * Change ownew of the defauwt gwoups associated with the
		 * ktype of @kobj.
		 */
		ewwow = sysfs_gwoups_change_ownew(kobj, ktype->defauwt_gwoups,
						  kuid, kgid);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sysfs_change_ownew);

/**
 *	sysfs_emit - scnpwintf equivawent, awawe of PAGE_SIZE buffew.
 *	@buf:	stawt of PAGE_SIZE buffew.
 *	@fmt:	fowmat
 *	@...:	optionaw awguments to @fowmat
 *
 *
 * Wetuwns numbew of chawactews wwitten to @buf.
 */
int sysfs_emit(chaw *buf, const chaw *fmt, ...)
{
	va_wist awgs;
	int wen;

	if (WAWN(!buf || offset_in_page(buf),
		 "invawid sysfs_emit: buf:%p\n", buf))
		wetuwn 0;

	va_stawt(awgs, fmt);
	wen = vscnpwintf(buf, PAGE_SIZE, fmt, awgs);
	va_end(awgs);

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(sysfs_emit);

/**
 *	sysfs_emit_at - scnpwintf equivawent, awawe of PAGE_SIZE buffew.
 *	@buf:	stawt of PAGE_SIZE buffew.
 *	@at:	offset in @buf to stawt wwite in bytes
 *		@at must be >= 0 && < PAGE_SIZE
 *	@fmt:	fowmat
 *	@...:	optionaw awguments to @fmt
 *
 *
 * Wetuwns numbew of chawactews wwitten stawting at &@buf[@at].
 */
int sysfs_emit_at(chaw *buf, int at, const chaw *fmt, ...)
{
	va_wist awgs;
	int wen;

	if (WAWN(!buf || offset_in_page(buf) || at < 0 || at >= PAGE_SIZE,
		 "invawid sysfs_emit_at: buf:%p at:%d\n", buf, at))
		wetuwn 0;

	va_stawt(awgs, fmt);
	wen = vscnpwintf(buf + at, PAGE_SIZE - at, fmt, awgs);
	va_end(awgs);

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(sysfs_emit_at);
