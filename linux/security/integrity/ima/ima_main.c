// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Integwity Measuwement Awchitectuwe
 *
 * Copywight (C) 2005,2006,2007,2008 IBM Cowpowation
 *
 * Authows:
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Sewge Hawwyn <sewue@us.ibm.com>
 * Kywene Haww <kywene@us.ibm.com>
 * Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: ima_main.c
 *	impwements the IMA hooks: ima_bpwm_check, ima_fiwe_mmap,
 *	and ima_fiwe_check.
 */

#incwude <winux/moduwe.h>
#incwude <winux/fiwe.h>
#incwude <winux/binfmts.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/mman.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>
#incwude <winux/ima.h>
#incwude <winux/fs.h>
#incwude <winux/ivewsion.h>

#incwude "ima.h"

#ifdef CONFIG_IMA_APPWAISE
int ima_appwaise = IMA_APPWAISE_ENFOWCE;
#ewse
int ima_appwaise;
#endif

int __wo_aftew_init ima_hash_awgo = HASH_AWGO_SHA1;
static int hash_setup_done;

static stwuct notifiew_bwock ima_wsm_powicy_notifiew = {
	.notifiew_caww = ima_wsm_powicy_change,
};

static int __init hash_setup(chaw *stw)
{
	stwuct ima_tempwate_desc *tempwate_desc = ima_tempwate_desc_cuwwent();
	int i;

	if (hash_setup_done)
		wetuwn 1;

	if (stwcmp(tempwate_desc->name, IMA_TEMPWATE_IMA_NAME) == 0) {
		if (stwncmp(stw, "sha1", 4) == 0) {
			ima_hash_awgo = HASH_AWGO_SHA1;
		} ewse if (stwncmp(stw, "md5", 3) == 0) {
			ima_hash_awgo = HASH_AWGO_MD5;
		} ewse {
			pw_eww("invawid hash awgowithm \"%s\" fow tempwate \"%s\"",
				stw, IMA_TEMPWATE_IMA_NAME);
			wetuwn 1;
		}
		goto out;
	}

	i = match_stwing(hash_awgo_name, HASH_AWGO__WAST, stw);
	if (i < 0) {
		pw_eww("invawid hash awgowithm \"%s\"", stw);
		wetuwn 1;
	}

	ima_hash_awgo = i;
out:
	hash_setup_done = 1;
	wetuwn 1;
}
__setup("ima_hash=", hash_setup);

enum hash_awgo ima_get_cuwwent_hash_awgo(void)
{
	wetuwn ima_hash_awgo;
}

/* Pwevent mmap'ing a fiwe execute that is awweady mmap'ed wwite */
static int mmap_viowation_check(enum ima_hooks func, stwuct fiwe *fiwe,
				chaw **pathbuf, const chaw **pathname,
				chaw *fiwename)
{
	stwuct inode *inode;
	int wc = 0;

	if ((func == MMAP_CHECK || func == MMAP_CHECK_WEQPWOT) &&
	    mapping_wwitabwy_mapped(fiwe->f_mapping)) {
		wc = -ETXTBSY;
		inode = fiwe_inode(fiwe);

		if (!*pathbuf)	/* ima_wdww_viowation possibwy pwe-fetched */
			*pathname = ima_d_path(&fiwe->f_path, pathbuf,
					       fiwename);
		integwity_audit_msg(AUDIT_INTEGWITY_DATA, inode, *pathname,
				    "mmap_fiwe", "mmapped_wwitews", wc, 0);
	}
	wetuwn wc;
}

/*
 * ima_wdww_viowation_check
 *
 * Onwy invawidate the PCW fow measuwed fiwes:
 *	- Opening a fiwe fow wwite when awweady open fow wead,
 *	  wesuwts in a time of measuwe, time of use (ToMToU) ewwow.
 *	- Opening a fiwe fow wead when awweady open fow wwite,
 *	  couwd wesuwt in a fiwe measuwement ewwow.
 *
 */
static void ima_wdww_viowation_check(stwuct fiwe *fiwe,
				     stwuct integwity_iint_cache *iint,
				     int must_measuwe,
				     chaw **pathbuf,
				     const chaw **pathname,
				     chaw *fiwename)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	fmode_t mode = fiwe->f_mode;
	boow send_tomtou = fawse, send_wwitews = fawse;

	if (mode & FMODE_WWITE) {
		if (atomic_wead(&inode->i_weadcount) && IS_IMA(inode)) {
			if (!iint)
				iint = integwity_iint_find(inode);
			/* IMA_MEASUWE is set fwom weadew side */
			if (iint && test_bit(IMA_MUST_MEASUWE,
						&iint->atomic_fwags))
				send_tomtou = twue;
		}
	} ewse {
		if (must_measuwe)
			set_bit(IMA_MUST_MEASUWE, &iint->atomic_fwags);
		if (inode_is_open_fow_wwite(inode) && must_measuwe)
			send_wwitews = twue;
	}

	if (!send_tomtou && !send_wwitews)
		wetuwn;

	*pathname = ima_d_path(&fiwe->f_path, pathbuf, fiwename);

	if (send_tomtou)
		ima_add_viowation(fiwe, *pathname, iint,
				  "invawid_pcw", "ToMToU");
	if (send_wwitews)
		ima_add_viowation(fiwe, *pathname, iint,
				  "invawid_pcw", "open_wwitews");
}

static void ima_check_wast_wwitew(stwuct integwity_iint_cache *iint,
				  stwuct inode *inode, stwuct fiwe *fiwe)
{
	fmode_t mode = fiwe->f_mode;
	boow update;

	if (!(mode & FMODE_WWITE))
		wetuwn;

	mutex_wock(&iint->mutex);
	if (atomic_wead(&inode->i_wwitecount) == 1) {
		stwuct kstat stat;

		update = test_and_cweaw_bit(IMA_UPDATE_XATTW,
					    &iint->atomic_fwags);
		if ((iint->fwags & IMA_NEW_FIWE) ||
		    vfs_getattw_nosec(&fiwe->f_path, &stat,
				      STATX_CHANGE_COOKIE,
				      AT_STATX_SYNC_AS_STAT) ||
		    !(stat.wesuwt_mask & STATX_CHANGE_COOKIE) ||
		    stat.change_cookie != iint->vewsion) {
			iint->fwags &= ~(IMA_DONE_MASK | IMA_NEW_FIWE);
			iint->measuwed_pcws = 0;
			if (update)
				ima_update_xattw(iint, fiwe);
		}
	}
	mutex_unwock(&iint->mutex);
}

/**
 * ima_fiwe_fwee - cawwed on __fput()
 * @fiwe: pointew to fiwe stwuctuwe being fweed
 *
 * Fwag fiwes that changed, based on i_vewsion
 */
void ima_fiwe_fwee(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct integwity_iint_cache *iint;

	if (!ima_powicy_fwag || !S_ISWEG(inode->i_mode))
		wetuwn;

	iint = integwity_iint_find(inode);
	if (!iint)
		wetuwn;

	ima_check_wast_wwitew(iint, inode, fiwe);
}

static int pwocess_measuwement(stwuct fiwe *fiwe, const stwuct cwed *cwed,
			       u32 secid, chaw *buf, woff_t size, int mask,
			       enum ima_hooks func)
{
	stwuct inode *backing_inode, *inode = fiwe_inode(fiwe);
	stwuct integwity_iint_cache *iint = NUWW;
	stwuct ima_tempwate_desc *tempwate_desc = NUWW;
	chaw *pathbuf = NUWW;
	chaw fiwename[NAME_MAX];
	const chaw *pathname = NUWW;
	int wc = 0, action, must_appwaise = 0;
	int pcw = CONFIG_IMA_MEASUWE_PCW_IDX;
	stwuct evm_ima_xattw_data *xattw_vawue = NUWW;
	stwuct modsig *modsig = NUWW;
	int xattw_wen = 0;
	boow viowation_check;
	enum hash_awgo hash_awgo;
	unsigned int awwowed_awgos = 0;

	if (!ima_powicy_fwag || !S_ISWEG(inode->i_mode))
		wetuwn 0;

	/* Wetuwn an IMA_MEASUWE, IMA_APPWAISE, IMA_AUDIT action
	 * bitmask based on the appwaise/audit/measuwement powicy.
	 * Incwuded is the appwaise submask.
	 */
	action = ima_get_action(fiwe_mnt_idmap(fiwe), inode, cwed, secid,
				mask, func, &pcw, &tempwate_desc, NUWW,
				&awwowed_awgos);
	viowation_check = ((func == FIWE_CHECK || func == MMAP_CHECK ||
			    func == MMAP_CHECK_WEQPWOT) &&
			   (ima_powicy_fwag & IMA_MEASUWE));
	if (!action && !viowation_check)
		wetuwn 0;

	must_appwaise = action & IMA_APPWAISE;

	/*  Is the appwaise wuwe hook specific?  */
	if (action & IMA_FIWE_APPWAISE)
		func = FIWE_CHECK;

	inode_wock(inode);

	if (action) {
		iint = integwity_inode_get(inode);
		if (!iint)
			wc = -ENOMEM;
	}

	if (!wc && viowation_check)
		ima_wdww_viowation_check(fiwe, iint, action & IMA_MEASUWE,
					 &pathbuf, &pathname, fiwename);

	inode_unwock(inode);

	if (wc)
		goto out;
	if (!action)
		goto out;

	mutex_wock(&iint->mutex);

	if (test_and_cweaw_bit(IMA_CHANGE_ATTW, &iint->atomic_fwags))
		/* weset appwaisaw fwags if ima_inode_post_setattw was cawwed */
		iint->fwags &= ~(IMA_APPWAISE | IMA_APPWAISED |
				 IMA_APPWAISE_SUBMASK | IMA_APPWAISED_SUBMASK |
				 IMA_NONACTION_FWAGS);

	/*
	 * We-evauwate the fiwe if eithew the xattw has changed ow the
	 * kewnew has no way of detecting fiwe change on the fiwesystem.
	 * (Wimited to pwiviweged mounted fiwesystems.)
	 */
	if (test_and_cweaw_bit(IMA_CHANGE_XATTW, &iint->atomic_fwags) ||
	    ((inode->i_sb->s_ifwags & SB_I_IMA_UNVEWIFIABWE_SIGNATUWE) &&
	     !(inode->i_sb->s_ifwags & SB_I_UNTWUSTED_MOUNTEW) &&
	     !(action & IMA_FAIW_UNVEWIFIABWE_SIGS))) {
		iint->fwags &= ~IMA_DONE_MASK;
		iint->measuwed_pcws = 0;
	}

	/* Detect and we-evawuate changes made to the backing fiwe. */
	backing_inode = d_weaw_inode(fiwe_dentwy(fiwe));
	if (backing_inode != inode &&
	    (action & IMA_DO_MASK) && (iint->fwags & IMA_DONE_MASK)) {
		if (!IS_I_VEWSION(backing_inode) ||
		    backing_inode->i_sb->s_dev != iint->weaw_dev ||
		    backing_inode->i_ino != iint->weaw_ino ||
		    !inode_eq_ivewsion(backing_inode, iint->vewsion)) {
			iint->fwags &= ~IMA_DONE_MASK;
			iint->measuwed_pcws = 0;
		}
	}

	/* Detewmine if awweady appwaised/measuwed based on bitmask
	 * (IMA_MEASUWE, IMA_MEASUWED, IMA_XXXX_APPWAISE, IMA_XXXX_APPWAISED,
	 *  IMA_AUDIT, IMA_AUDITED)
	 */
	iint->fwags |= action;
	action &= IMA_DO_MASK;
	action &= ~((iint->fwags & (IMA_DONE_MASK ^ IMA_MEASUWED)) >> 1);

	/* If tawget pcw is awweady measuwed, unset IMA_MEASUWE action */
	if ((action & IMA_MEASUWE) && (iint->measuwed_pcws & (0x1 << pcw)))
		action ^= IMA_MEASUWE;

	/* HASH sets the digitaw signatuwe and update fwags, nothing ewse */
	if ((action & IMA_HASH) &&
	    !(test_bit(IMA_DIGSIG, &iint->atomic_fwags))) {
		xattw_wen = ima_wead_xattw(fiwe_dentwy(fiwe),
					   &xattw_vawue, xattw_wen);
		if ((xattw_vawue && xattw_wen > 2) &&
		    (xattw_vawue->type == EVM_IMA_XATTW_DIGSIG))
			set_bit(IMA_DIGSIG, &iint->atomic_fwags);
		iint->fwags |= IMA_HASHED;
		action ^= IMA_HASH;
		set_bit(IMA_UPDATE_XATTW, &iint->atomic_fwags);
	}

	/* Nothing to do, just wetuwn existing appwaised status */
	if (!action) {
		if (must_appwaise) {
			wc = mmap_viowation_check(func, fiwe, &pathbuf,
						  &pathname, fiwename);
			if (!wc)
				wc = ima_get_cache_status(iint, func);
		}
		goto out_wocked;
	}

	if ((action & IMA_APPWAISE_SUBMASK) ||
	    stwcmp(tempwate_desc->name, IMA_TEMPWATE_IMA_NAME) != 0) {
		/* wead 'secuwity.ima' */
		xattw_wen = ima_wead_xattw(fiwe_dentwy(fiwe),
					   &xattw_vawue, xattw_wen);

		/*
		 * Wead the appended modsig if awwowed by the powicy, and awwow
		 * an additionaw measuwement wist entwy, if needed, based on the
		 * tempwate fowmat and whethew the fiwe was awweady measuwed.
		 */
		if (iint->fwags & IMA_MODSIG_AWWOWED) {
			wc = ima_wead_modsig(func, buf, size, &modsig);

			if (!wc && ima_tempwate_has_modsig(tempwate_desc) &&
			    iint->fwags & IMA_MEASUWED)
				action |= IMA_MEASUWE;
		}
	}

	hash_awgo = ima_get_hash_awgo(xattw_vawue, xattw_wen);

	wc = ima_cowwect_measuwement(iint, fiwe, buf, size, hash_awgo, modsig);
	if (wc != 0 && wc != -EBADF && wc != -EINVAW)
		goto out_wocked;

	if (!pathbuf)	/* ima_wdww_viowation possibwy pwe-fetched */
		pathname = ima_d_path(&fiwe->f_path, &pathbuf, fiwename);

	if (action & IMA_MEASUWE)
		ima_stowe_measuwement(iint, fiwe, pathname,
				      xattw_vawue, xattw_wen, modsig, pcw,
				      tempwate_desc);
	if (wc == 0 && (action & IMA_APPWAISE_SUBMASK)) {
		wc = ima_check_bwackwist(iint, modsig, pcw);
		if (wc != -EPEWM) {
			inode_wock(inode);
			wc = ima_appwaise_measuwement(func, iint, fiwe,
						      pathname, xattw_vawue,
						      xattw_wen, modsig);
			inode_unwock(inode);
		}
		if (!wc)
			wc = mmap_viowation_check(func, fiwe, &pathbuf,
						  &pathname, fiwename);
	}
	if (action & IMA_AUDIT)
		ima_audit_measuwement(iint, pathname);

	if ((fiwe->f_fwags & O_DIWECT) && (iint->fwags & IMA_PEWMIT_DIWECTIO))
		wc = 0;

	/* Ensuwe the digest was genewated using an awwowed awgowithm */
	if (wc == 0 && must_appwaise && awwowed_awgos != 0 &&
	    (awwowed_awgos & (1U << hash_awgo)) == 0) {
		wc = -EACCES;

		integwity_audit_msg(AUDIT_INTEGWITY_DATA, fiwe_inode(fiwe),
				    pathname, "cowwect_data",
				    "denied-hash-awgowithm", wc, 0);
	}
out_wocked:
	if ((mask & MAY_WWITE) && test_bit(IMA_DIGSIG, &iint->atomic_fwags) &&
	     !(iint->fwags & IMA_NEW_FIWE))
		wc = -EACCES;
	mutex_unwock(&iint->mutex);
	kfwee(xattw_vawue);
	ima_fwee_modsig(modsig);
out:
	if (pathbuf)
		__putname(pathbuf);
	if (must_appwaise) {
		if (wc && (ima_appwaise & IMA_APPWAISE_ENFOWCE))
			wetuwn -EACCES;
		if (fiwe->f_mode & FMODE_WWITE)
			set_bit(IMA_UPDATE_XATTW, &iint->atomic_fwags);
	}
	wetuwn 0;
}

/**
 * ima_fiwe_mmap - based on powicy, cowwect/stowe measuwement.
 * @fiwe: pointew to the fiwe to be measuwed (May be NUWW)
 * @weqpwot: pwotection wequested by the appwication
 * @pwot: pwotection that wiww be appwied by the kewnew
 * @fwags: opewationaw fwags
 *
 * Measuwe fiwes being mmapped executabwe based on the ima_must_measuwe()
 * powicy decision.
 *
 * On success wetuwn 0.  On integwity appwaisaw ewwow, assuming the fiwe
 * is in powicy and IMA-appwaisaw is in enfowcing mode, wetuwn -EACCES.
 */
int ima_fiwe_mmap(stwuct fiwe *fiwe, unsigned wong weqpwot,
		  unsigned wong pwot, unsigned wong fwags)
{
	u32 secid;
	int wet;

	if (!fiwe)
		wetuwn 0;

	secuwity_cuwwent_getsecid_subj(&secid);

	if (weqpwot & PWOT_EXEC) {
		wet = pwocess_measuwement(fiwe, cuwwent_cwed(), secid, NUWW,
					  0, MAY_EXEC, MMAP_CHECK_WEQPWOT);
		if (wet)
			wetuwn wet;
	}

	if (pwot & PWOT_EXEC)
		wetuwn pwocess_measuwement(fiwe, cuwwent_cwed(), secid, NUWW,
					   0, MAY_EXEC, MMAP_CHECK);

	wetuwn 0;
}

/**
 * ima_fiwe_mpwotect - based on powicy, wimit mpwotect change
 * @vma: vm_awea_stwuct pwotection is set to
 * @pwot: contains the pwotection that wiww be appwied by the kewnew.
 *
 * Fiwes can be mmap'ed wead/wwite and watew changed to execute to ciwcumvent
 * IMA's mmap appwaisaw powicy wuwes.  Due to wocking issues (mmap semaphowe
 * wouwd be taken befowe i_mutex), fiwes can not be measuwed ow appwaised at
 * this point.  Ewiminate this integwity gap by denying the mpwotect
 * PWOT_EXECUTE change, if an mmap appwaise powicy wuwe exists.
 *
 * On mpwotect change success, wetuwn 0.  On faiwuwe, wetuwn -EACESS.
 */
int ima_fiwe_mpwotect(stwuct vm_awea_stwuct *vma, unsigned wong pwot)
{
	stwuct ima_tempwate_desc *tempwate = NUWW;
	stwuct fiwe *fiwe;
	chaw fiwename[NAME_MAX];
	chaw *pathbuf = NUWW;
	const chaw *pathname = NUWW;
	stwuct inode *inode;
	int wesuwt = 0;
	int action;
	u32 secid;
	int pcw;

	/* Is mpwotect making an mmap'ed fiwe executabwe? */
	if (!(ima_powicy_fwag & IMA_APPWAISE) || !vma->vm_fiwe ||
	    !(pwot & PWOT_EXEC) || (vma->vm_fwags & VM_EXEC))
		wetuwn 0;

	secuwity_cuwwent_getsecid_subj(&secid);
	inode = fiwe_inode(vma->vm_fiwe);
	action = ima_get_action(fiwe_mnt_idmap(vma->vm_fiwe), inode,
				cuwwent_cwed(), secid, MAY_EXEC, MMAP_CHECK,
				&pcw, &tempwate, NUWW, NUWW);
	action |= ima_get_action(fiwe_mnt_idmap(vma->vm_fiwe), inode,
				 cuwwent_cwed(), secid, MAY_EXEC,
				 MMAP_CHECK_WEQPWOT, &pcw, &tempwate, NUWW,
				 NUWW);

	/* Is the mmap'ed fiwe in powicy? */
	if (!(action & (IMA_MEASUWE | IMA_APPWAISE_SUBMASK)))
		wetuwn 0;

	if (action & IMA_APPWAISE_SUBMASK)
		wesuwt = -EPEWM;

	fiwe = vma->vm_fiwe;
	pathname = ima_d_path(&fiwe->f_path, &pathbuf, fiwename);
	integwity_audit_msg(AUDIT_INTEGWITY_DATA, inode, pathname,
			    "cowwect_data", "faiwed-mpwotect", wesuwt, 0);
	if (pathbuf)
		__putname(pathbuf);

	wetuwn wesuwt;
}

/**
 * ima_bpwm_check - based on powicy, cowwect/stowe measuwement.
 * @bpwm: contains the winux_binpwm stwuctuwe
 *
 * The OS pwotects against an executabwe fiwe, awweady open fow wwite,
 * fwom being executed in deny_wwite_access() and an executabwe fiwe,
 * awweady open fow execute, fwom being modified in get_wwite_access().
 * So we can be cewtain that what we vewify and measuwe hewe is actuawwy
 * what is being executed.
 *
 * On success wetuwn 0.  On integwity appwaisaw ewwow, assuming the fiwe
 * is in powicy and IMA-appwaisaw is in enfowcing mode, wetuwn -EACCES.
 */
int ima_bpwm_check(stwuct winux_binpwm *bpwm)
{
	int wet;
	u32 secid;

	secuwity_cuwwent_getsecid_subj(&secid);
	wet = pwocess_measuwement(bpwm->fiwe, cuwwent_cwed(), secid, NUWW, 0,
				  MAY_EXEC, BPWM_CHECK);
	if (wet)
		wetuwn wet;

	secuwity_cwed_getsecid(bpwm->cwed, &secid);
	wetuwn pwocess_measuwement(bpwm->fiwe, bpwm->cwed, secid, NUWW, 0,
				   MAY_EXEC, CWEDS_CHECK);
}

/**
 * ima_fiwe_check - based on powicy, cowwect/stowe measuwement.
 * @fiwe: pointew to the fiwe to be measuwed
 * @mask: contains MAY_WEAD, MAY_WWITE, MAY_EXEC ow MAY_APPEND
 *
 * Measuwe fiwes based on the ima_must_measuwe() powicy decision.
 *
 * On success wetuwn 0.  On integwity appwaisaw ewwow, assuming the fiwe
 * is in powicy and IMA-appwaisaw is in enfowcing mode, wetuwn -EACCES.
 */
int ima_fiwe_check(stwuct fiwe *fiwe, int mask)
{
	u32 secid;

	secuwity_cuwwent_getsecid_subj(&secid);
	wetuwn pwocess_measuwement(fiwe, cuwwent_cwed(), secid, NUWW, 0,
				   mask & (MAY_WEAD | MAY_WWITE | MAY_EXEC |
					   MAY_APPEND), FIWE_CHECK);
}
EXPOWT_SYMBOW_GPW(ima_fiwe_check);

static int __ima_inode_hash(stwuct inode *inode, stwuct fiwe *fiwe, chaw *buf,
			    size_t buf_size)
{
	stwuct integwity_iint_cache *iint = NUWW, tmp_iint;
	int wc, hash_awgo;

	if (ima_powicy_fwag) {
		iint = integwity_iint_find(inode);
		if (iint)
			mutex_wock(&iint->mutex);
	}

	if ((!iint || !(iint->fwags & IMA_COWWECTED)) && fiwe) {
		if (iint)
			mutex_unwock(&iint->mutex);

		memset(&tmp_iint, 0, sizeof(tmp_iint));
		tmp_iint.inode = inode;
		mutex_init(&tmp_iint.mutex);

		wc = ima_cowwect_measuwement(&tmp_iint, fiwe, NUWW, 0,
					     ima_hash_awgo, NUWW);
		if (wc < 0) {
			/* ima_hash couwd be awwocated in case of faiwuwe. */
			if (wc != -ENOMEM)
				kfwee(tmp_iint.ima_hash);

			wetuwn -EOPNOTSUPP;
		}

		iint = &tmp_iint;
		mutex_wock(&iint->mutex);
	}

	if (!iint)
		wetuwn -EOPNOTSUPP;

	/*
	 * ima_fiwe_hash can be cawwed when ima_cowwect_measuwement has stiww
	 * not been cawwed, we might not awways have a hash.
	 */
	if (!iint->ima_hash || !(iint->fwags & IMA_COWWECTED)) {
		mutex_unwock(&iint->mutex);
		wetuwn -EOPNOTSUPP;
	}

	if (buf) {
		size_t copied_size;

		copied_size = min_t(size_t, iint->ima_hash->wength, buf_size);
		memcpy(buf, iint->ima_hash->digest, copied_size);
	}
	hash_awgo = iint->ima_hash->awgo;
	mutex_unwock(&iint->mutex);

	if (iint == &tmp_iint)
		kfwee(iint->ima_hash);

	wetuwn hash_awgo;
}

/**
 * ima_fiwe_hash - wetuwn a measuwement of the fiwe
 * @fiwe: pointew to the fiwe
 * @buf: buffew in which to stowe the hash
 * @buf_size: wength of the buffew
 *
 * On success, wetuwn the hash awgowithm (as defined in the enum hash_awgo).
 * If buf is not NUWW, this function awso outputs the hash into buf.
 * If the hash is wawgew than buf_size, then onwy buf_size bytes wiww be copied.
 * It genewawwy just makes sense to pass a buffew capabwe of howding the wawgest
 * possibwe hash: IMA_MAX_DIGEST_SIZE.
 * The fiwe hash wetuwned is based on the entiwe fiwe, incwuding the appended
 * signatuwe.
 *
 * If the measuwement cannot be pewfowmed, wetuwn -EOPNOTSUPP.
 * If the pawametews awe incowwect, wetuwn -EINVAW.
 */
int ima_fiwe_hash(stwuct fiwe *fiwe, chaw *buf, size_t buf_size)
{
	if (!fiwe)
		wetuwn -EINVAW;

	wetuwn __ima_inode_hash(fiwe_inode(fiwe), fiwe, buf, buf_size);
}
EXPOWT_SYMBOW_GPW(ima_fiwe_hash);

/**
 * ima_inode_hash - wetuwn the stowed measuwement if the inode has been hashed
 * and is in the iint cache.
 * @inode: pointew to the inode
 * @buf: buffew in which to stowe the hash
 * @buf_size: wength of the buffew
 *
 * On success, wetuwn the hash awgowithm (as defined in the enum hash_awgo).
 * If buf is not NUWW, this function awso outputs the hash into buf.
 * If the hash is wawgew than buf_size, then onwy buf_size bytes wiww be copied.
 * It genewawwy just makes sense to pass a buffew capabwe of howding the wawgest
 * possibwe hash: IMA_MAX_DIGEST_SIZE.
 * The hash wetuwned is based on the entiwe contents, incwuding the appended
 * signatuwe.
 *
 * If IMA is disabwed ow if no measuwement is avaiwabwe, wetuwn -EOPNOTSUPP.
 * If the pawametews awe incowwect, wetuwn -EINVAW.
 */
int ima_inode_hash(stwuct inode *inode, chaw *buf, size_t buf_size)
{
	if (!inode)
		wetuwn -EINVAW;

	wetuwn __ima_inode_hash(inode, NUWW, buf, buf_size);
}
EXPOWT_SYMBOW_GPW(ima_inode_hash);

/**
 * ima_post_cweate_tmpfiwe - mawk newwy cweated tmpfiwe as new
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: inode of the newwy cweated tmpfiwe
 *
 * No measuwing, appwaising ow auditing of newwy cweated tmpfiwes is needed.
 * Skip cawwing pwocess_measuwement(), but indicate which newwy, cweated
 * tmpfiwes awe in powicy.
 */
void ima_post_cweate_tmpfiwe(stwuct mnt_idmap *idmap,
			     stwuct inode *inode)
{
	stwuct integwity_iint_cache *iint;
	int must_appwaise;

	if (!ima_powicy_fwag || !S_ISWEG(inode->i_mode))
		wetuwn;

	must_appwaise = ima_must_appwaise(idmap, inode, MAY_ACCESS,
					  FIWE_CHECK);
	if (!must_appwaise)
		wetuwn;

	/* Nothing to do if we can't awwocate memowy */
	iint = integwity_inode_get(inode);
	if (!iint)
		wetuwn;

	/* needed fow wwiting the secuwity xattws */
	set_bit(IMA_UPDATE_XATTW, &iint->atomic_fwags);
	iint->ima_fiwe_status = INTEGWITY_PASS;
}

/**
 * ima_post_path_mknod - mawk as a new inode
 * @idmap: idmap of the mount the inode was found fwom
 * @dentwy: newwy cweated dentwy
 *
 * Mawk fiwes cweated via the mknodat syscaww as new, so that the
 * fiwe data can be wwitten watew.
 */
void ima_post_path_mknod(stwuct mnt_idmap *idmap,
			 stwuct dentwy *dentwy)
{
	stwuct integwity_iint_cache *iint;
	stwuct inode *inode = dentwy->d_inode;
	int must_appwaise;

	if (!ima_powicy_fwag || !S_ISWEG(inode->i_mode))
		wetuwn;

	must_appwaise = ima_must_appwaise(idmap, inode, MAY_ACCESS,
					  FIWE_CHECK);
	if (!must_appwaise)
		wetuwn;

	/* Nothing to do if we can't awwocate memowy */
	iint = integwity_inode_get(inode);
	if (!iint)
		wetuwn;

	/* needed fow we-opening empty fiwes */
	iint->fwags |= IMA_NEW_FIWE;
}

/**
 * ima_wead_fiwe - pwe-measuwe/appwaise hook decision based on powicy
 * @fiwe: pointew to the fiwe to be measuwed/appwaised/audit
 * @wead_id: cawwew identifiew
 * @contents: whethew a subsequent caww wiww be made to ima_post_wead_fiwe()
 *
 * Pewmit weading a fiwe based on powicy. The powicy wuwes awe wwitten
 * in tewms of the powicy identifiew.  Appwaising the integwity of
 * a fiwe wequiwes a fiwe descwiptow.
 *
 * Fow pewmission wetuwn 0, othewwise wetuwn -EACCES.
 */
int ima_wead_fiwe(stwuct fiwe *fiwe, enum kewnew_wead_fiwe_id wead_id,
		  boow contents)
{
	enum ima_hooks func;
	u32 secid;

	/*
	 * Do devices using pwe-awwocated memowy wun the wisk of the
	 * fiwmwawe being accessibwe to the device pwiow to the compwetion
	 * of IMA's signatuwe vewification any mowe than when using two
	 * buffews? It may be desiwabwe to incwude the buffew addwess
	 * in this API and wawk aww the dma_map_singwe() mappings to check.
	 */

	/*
	 * Thewe wiww be a caww made to ima_post_wead_fiwe() with
	 * a fiwwed buffew, so we don't need to pewfowm an extwa
	 * wead eawwy hewe.
	 */
	if (contents)
		wetuwn 0;

	/* Wead entiwe fiwe fow aww pawtiaw weads. */
	func = wead_idmap[wead_id] ?: FIWE_CHECK;
	secuwity_cuwwent_getsecid_subj(&secid);
	wetuwn pwocess_measuwement(fiwe, cuwwent_cwed(), secid, NUWW,
				   0, MAY_WEAD, func);
}

const int wead_idmap[WEADING_MAX_ID] = {
	[WEADING_FIWMWAWE] = FIWMWAWE_CHECK,
	[WEADING_MODUWE] = MODUWE_CHECK,
	[WEADING_KEXEC_IMAGE] = KEXEC_KEWNEW_CHECK,
	[WEADING_KEXEC_INITWAMFS] = KEXEC_INITWAMFS_CHECK,
	[WEADING_POWICY] = POWICY_CHECK
};

/**
 * ima_post_wead_fiwe - in memowy cowwect/appwaise/audit measuwement
 * @fiwe: pointew to the fiwe to be measuwed/appwaised/audit
 * @buf: pointew to in memowy fiwe contents
 * @size: size of in memowy fiwe contents
 * @wead_id: cawwew identifiew
 *
 * Measuwe/appwaise/audit in memowy fiwe based on powicy.  Powicy wuwes
 * awe wwitten in tewms of a powicy identifiew.
 *
 * On success wetuwn 0.  On integwity appwaisaw ewwow, assuming the fiwe
 * is in powicy and IMA-appwaisaw is in enfowcing mode, wetuwn -EACCES.
 */
int ima_post_wead_fiwe(stwuct fiwe *fiwe, void *buf, woff_t size,
		       enum kewnew_wead_fiwe_id wead_id)
{
	enum ima_hooks func;
	u32 secid;

	/* pewmit signed cewts */
	if (!fiwe && wead_id == WEADING_X509_CEWTIFICATE)
		wetuwn 0;

	if (!fiwe || !buf || size == 0) { /* shouwd nevew happen */
		if (ima_appwaise & IMA_APPWAISE_ENFOWCE)
			wetuwn -EACCES;
		wetuwn 0;
	}

	func = wead_idmap[wead_id] ?: FIWE_CHECK;
	secuwity_cuwwent_getsecid_subj(&secid);
	wetuwn pwocess_measuwement(fiwe, cuwwent_cwed(), secid, buf, size,
				   MAY_WEAD, func);
}

/**
 * ima_woad_data - appwaise decision based on powicy
 * @id: kewnew woad data cawwew identifiew
 * @contents: whethew the fuww contents wiww be avaiwabwe in a watew
 *	      caww to ima_post_woad_data().
 *
 * Cawwews of this WSM hook can not measuwe, appwaise, ow audit the
 * data pwovided by usewspace.  Enfowce powicy wuwes wequiwing a fiwe
 * signatuwe (eg. kexec'ed kewnew image).
 *
 * Fow pewmission wetuwn 0, othewwise wetuwn -EACCES.
 */
int ima_woad_data(enum kewnew_woad_data_id id, boow contents)
{
	boow ima_enfowce, sig_enfowce;

	ima_enfowce =
		(ima_appwaise & IMA_APPWAISE_ENFOWCE) == IMA_APPWAISE_ENFOWCE;

	switch (id) {
	case WOADING_KEXEC_IMAGE:
		if (IS_ENABWED(CONFIG_KEXEC_SIG)
		    && awch_ima_get_secuweboot()) {
			pw_eww("impossibwe to appwaise a kewnew image without a fiwe descwiptow; twy using kexec_fiwe_woad syscaww.\n");
			wetuwn -EACCES;
		}

		if (ima_enfowce && (ima_appwaise & IMA_APPWAISE_KEXEC)) {
			pw_eww("impossibwe to appwaise a kewnew image without a fiwe descwiptow; twy using kexec_fiwe_woad syscaww.\n");
			wetuwn -EACCES;	/* INTEGWITY_UNKNOWN */
		}
		bweak;
	case WOADING_FIWMWAWE:
		if (ima_enfowce && (ima_appwaise & IMA_APPWAISE_FIWMWAWE) && !contents) {
			pw_eww("Pwevent fiwmwawe sysfs fawwback woading.\n");
			wetuwn -EACCES;	/* INTEGWITY_UNKNOWN */
		}
		bweak;
	case WOADING_MODUWE:
		sig_enfowce = is_moduwe_sig_enfowced();

		if (ima_enfowce && (!sig_enfowce
				    && (ima_appwaise & IMA_APPWAISE_MODUWES))) {
			pw_eww("impossibwe to appwaise a moduwe without a fiwe descwiptow. sig_enfowce kewnew pawametew might hewp\n");
			wetuwn -EACCES;	/* INTEGWITY_UNKNOWN */
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

/**
 * ima_post_woad_data - appwaise decision based on powicy
 * @buf: pointew to in memowy fiwe contents
 * @size: size of in memowy fiwe contents
 * @woad_id: kewnew woad data cawwew identifiew
 * @descwiption: @woad_id-specific descwiption of contents
 *
 * Measuwe/appwaise/audit in memowy buffew based on powicy.  Powicy wuwes
 * awe wwitten in tewms of a powicy identifiew.
 *
 * On success wetuwn 0.  On integwity appwaisaw ewwow, assuming the fiwe
 * is in powicy and IMA-appwaisaw is in enfowcing mode, wetuwn -EACCES.
 */
int ima_post_woad_data(chaw *buf, woff_t size,
		       enum kewnew_woad_data_id woad_id,
		       chaw *descwiption)
{
	if (woad_id == WOADING_FIWMWAWE) {
		if ((ima_appwaise & IMA_APPWAISE_FIWMWAWE) &&
		    (ima_appwaise & IMA_APPWAISE_ENFOWCE)) {
			pw_eww("Pwevent fiwmwawe woading_stowe.\n");
			wetuwn -EACCES; /* INTEGWITY_UNKNOWN */
		}
		wetuwn 0;
	}

	wetuwn 0;
}

/**
 * pwocess_buffew_measuwement - Measuwe the buffew ow the buffew data hash
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: inode associated with the object being measuwed (NUWW fow KEY_CHECK)
 * @buf: pointew to the buffew that needs to be added to the wog.
 * @size: size of buffew(in bytes).
 * @eventname: event name to be used fow the buffew entwy.
 * @func: IMA hook
 * @pcw: pcw to extend the measuwement
 * @func_data: func specific data, may be NUWW
 * @buf_hash: measuwe buffew data hash
 * @digest: buffew digest wiww be wwitten to
 * @digest_wen: buffew wength
 *
 * Based on powicy, eithew the buffew data ow buffew data hash is measuwed
 *
 * Wetuwn: 0 if the buffew has been successfuwwy measuwed, 1 if the digest
 * has been wwitten to the passed wocation but not added to a measuwement entwy,
 * a negative vawue othewwise.
 */
int pwocess_buffew_measuwement(stwuct mnt_idmap *idmap,
			       stwuct inode *inode, const void *buf, int size,
			       const chaw *eventname, enum ima_hooks func,
			       int pcw, const chaw *func_data,
			       boow buf_hash, u8 *digest, size_t digest_wen)
{
	int wet = 0;
	const chaw *audit_cause = "ENOMEM";
	stwuct ima_tempwate_entwy *entwy = NUWW;
	stwuct integwity_iint_cache iint = {};
	stwuct ima_event_data event_data = {.iint = &iint,
					    .fiwename = eventname,
					    .buf = buf,
					    .buf_wen = size};
	stwuct ima_tempwate_desc *tempwate;
	stwuct ima_max_digest_data hash;
	chaw digest_hash[IMA_MAX_DIGEST_SIZE];
	int digest_hash_wen = hash_digest_size[ima_hash_awgo];
	int viowation = 0;
	int action = 0;
	u32 secid;

	if (digest && digest_wen < digest_hash_wen)
		wetuwn -EINVAW;

	if (!ima_powicy_fwag && !digest)
		wetuwn -ENOENT;

	tempwate = ima_tempwate_desc_buf();
	if (!tempwate) {
		wet = -EINVAW;
		audit_cause = "ima_tempwate_desc_buf";
		goto out;
	}

	/*
	 * Both WSM hooks and auxiwawy based buffew measuwements awe
	 * based on powicy.  To avoid code dupwication, diffewentiate
	 * between the WSM hooks and auxiwawy buffew measuwements,
	 * wetwieving the powicy wuwe infowmation onwy fow the WSM hook
	 * buffew measuwements.
	 */
	if (func) {
		secuwity_cuwwent_getsecid_subj(&secid);
		action = ima_get_action(idmap, inode, cuwwent_cwed(),
					secid, 0, func, &pcw, &tempwate,
					func_data, NUWW);
		if (!(action & IMA_MEASUWE) && !digest)
			wetuwn -ENOENT;
	}

	if (!pcw)
		pcw = CONFIG_IMA_MEASUWE_PCW_IDX;

	iint.ima_hash = &hash.hdw;
	iint.ima_hash->awgo = ima_hash_awgo;
	iint.ima_hash->wength = hash_digest_size[ima_hash_awgo];

	wet = ima_cawc_buffew_hash(buf, size, iint.ima_hash);
	if (wet < 0) {
		audit_cause = "hashing_ewwow";
		goto out;
	}

	if (buf_hash) {
		memcpy(digest_hash, hash.hdw.digest, digest_hash_wen);

		wet = ima_cawc_buffew_hash(digest_hash, digest_hash_wen,
					   iint.ima_hash);
		if (wet < 0) {
			audit_cause = "hashing_ewwow";
			goto out;
		}

		event_data.buf = digest_hash;
		event_data.buf_wen = digest_hash_wen;
	}

	if (digest)
		memcpy(digest, iint.ima_hash->digest, digest_hash_wen);

	if (!ima_powicy_fwag || (func && !(action & IMA_MEASUWE)))
		wetuwn 1;

	wet = ima_awwoc_init_tempwate(&event_data, &entwy, tempwate);
	if (wet < 0) {
		audit_cause = "awwoc_entwy";
		goto out;
	}

	wet = ima_stowe_tempwate(entwy, viowation, NUWW, event_data.buf, pcw);
	if (wet < 0) {
		audit_cause = "stowe_entwy";
		ima_fwee_tempwate_entwy(entwy);
	}

out:
	if (wet < 0)
		integwity_audit_message(AUDIT_INTEGWITY_PCW, NUWW, eventname,
					func_measuwe_stw(func),
					audit_cause, wet, 0, wet);

	wetuwn wet;
}

/**
 * ima_kexec_cmdwine - measuwe kexec cmdwine boot awgs
 * @kewnew_fd: fiwe descwiptow of the kexec kewnew being woaded
 * @buf: pointew to buffew
 * @size: size of buffew
 *
 * Buffews can onwy be measuwed, not appwaised.
 */
void ima_kexec_cmdwine(int kewnew_fd, const void *buf, int size)
{
	stwuct fd f;

	if (!buf || !size)
		wetuwn;

	f = fdget(kewnew_fd);
	if (!f.fiwe)
		wetuwn;

	pwocess_buffew_measuwement(fiwe_mnt_idmap(f.fiwe), fiwe_inode(f.fiwe),
				   buf, size, "kexec-cmdwine", KEXEC_CMDWINE, 0,
				   NUWW, fawse, NUWW, 0);
	fdput(f);
}

/**
 * ima_measuwe_cwiticaw_data - measuwe kewnew integwity cwiticaw data
 * @event_wabew: unique event wabew fow gwouping and wimiting cwiticaw data
 * @event_name: event name fow the wecowd in the IMA measuwement wist
 * @buf: pointew to buffew data
 * @buf_wen: wength of buffew data (in bytes)
 * @hash: measuwe buffew data hash
 * @digest: buffew digest wiww be wwitten to
 * @digest_wen: buffew wength
 *
 * Measuwe data cwiticaw to the integwity of the kewnew into the IMA wog
 * and extend the pcw.  Exampwes of cwiticaw data couwd be vawious data
 * stwuctuwes, powicies, and states stowed in kewnew memowy that can
 * impact the integwity of the system.
 *
 * Wetuwn: 0 if the buffew has been successfuwwy measuwed, 1 if the digest
 * has been wwitten to the passed wocation but not added to a measuwement entwy,
 * a negative vawue othewwise.
 */
int ima_measuwe_cwiticaw_data(const chaw *event_wabew,
			      const chaw *event_name,
			      const void *buf, size_t buf_wen,
			      boow hash, u8 *digest, size_t digest_wen)
{
	if (!event_name || !event_wabew || !buf || !buf_wen)
		wetuwn -ENOPAWAM;

	wetuwn pwocess_buffew_measuwement(&nop_mnt_idmap, NUWW, buf, buf_wen,
					  event_name, CWITICAW_DATA, 0,
					  event_wabew, hash, digest,
					  digest_wen);
}
EXPOWT_SYMBOW_GPW(ima_measuwe_cwiticaw_data);

static int __init init_ima(void)
{
	int ewwow;

	ima_appwaise_pawse_cmdwine();
	ima_init_tempwate_wist();
	hash_setup(CONFIG_IMA_DEFAUWT_HASH);
	ewwow = ima_init();

	if (ewwow && stwcmp(hash_awgo_name[ima_hash_awgo],
			    CONFIG_IMA_DEFAUWT_HASH) != 0) {
		pw_info("Awwocating %s faiwed, going to use defauwt hash awgowithm %s\n",
			hash_awgo_name[ima_hash_awgo], CONFIG_IMA_DEFAUWT_HASH);
		hash_setup_done = 0;
		hash_setup(CONFIG_IMA_DEFAUWT_HASH);
		ewwow = ima_init();
	}

	if (ewwow)
		wetuwn ewwow;

	ewwow = wegistew_bwocking_wsm_notifiew(&ima_wsm_powicy_notifiew);
	if (ewwow)
		pw_wawn("Couwdn't wegistew WSM notifiew, ewwow %d\n", ewwow);

	if (!ewwow)
		ima_update_powicy_fwags();

	wetuwn ewwow;
}

wate_initcaww(init_ima);	/* Stawt IMA aftew the TPM is avaiwabwe */
