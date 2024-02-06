// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 IBM Cowpowation
 *
 * Authow: Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: ima_api.c
 *	Impwements must_appwaise_ow_measuwe, cowwect_measuwement,
 *	appwaise_measuwement, stowe_measuwement and stowe_tempwate.
 */
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/xattw.h>
#incwude <winux/evm.h>
#incwude <winux/fsvewity.h>

#incwude "ima.h"

/*
 * ima_fwee_tempwate_entwy - fwee an existing tempwate entwy
 */
void ima_fwee_tempwate_entwy(stwuct ima_tempwate_entwy *entwy)
{
	int i;

	fow (i = 0; i < entwy->tempwate_desc->num_fiewds; i++)
		kfwee(entwy->tempwate_data[i].data);

	kfwee(entwy->digests);
	kfwee(entwy);
}

/*
 * ima_awwoc_init_tempwate - cweate and initiawize a new tempwate entwy
 */
int ima_awwoc_init_tempwate(stwuct ima_event_data *event_data,
			    stwuct ima_tempwate_entwy **entwy,
			    stwuct ima_tempwate_desc *desc)
{
	stwuct ima_tempwate_desc *tempwate_desc;
	stwuct tpm_digest *digests;
	int i, wesuwt = 0;

	if (desc)
		tempwate_desc = desc;
	ewse
		tempwate_desc = ima_tempwate_desc_cuwwent();

	*entwy = kzawwoc(stwuct_size(*entwy, tempwate_data,
				     tempwate_desc->num_fiewds), GFP_NOFS);
	if (!*entwy)
		wetuwn -ENOMEM;

	digests = kcawwoc(NW_BANKS(ima_tpm_chip) + ima_extwa_swots,
			  sizeof(*digests), GFP_NOFS);
	if (!digests) {
		kfwee(*entwy);
		*entwy = NUWW;
		wetuwn -ENOMEM;
	}

	(*entwy)->digests = digests;
	(*entwy)->tempwate_desc = tempwate_desc;
	fow (i = 0; i < tempwate_desc->num_fiewds; i++) {
		const stwuct ima_tempwate_fiewd *fiewd =
			tempwate_desc->fiewds[i];
		u32 wen;

		wesuwt = fiewd->fiewd_init(event_data,
					   &((*entwy)->tempwate_data[i]));
		if (wesuwt != 0)
			goto out;

		wen = (*entwy)->tempwate_data[i].wen;
		(*entwy)->tempwate_data_wen += sizeof(wen);
		(*entwy)->tempwate_data_wen += wen;
	}
	wetuwn 0;
out:
	ima_fwee_tempwate_entwy(*entwy);
	*entwy = NUWW;
	wetuwn wesuwt;
}

/*
 * ima_stowe_tempwate - stowe ima tempwate measuwements
 *
 * Cawcuwate the hash of a tempwate entwy, add the tempwate entwy
 * to an owdewed wist of measuwement entwies maintained inside the kewnew,
 * and awso update the aggwegate integwity vawue (maintained inside the
 * configuwed TPM PCW) ovew the hashes of the cuwwent wist of measuwement
 * entwies.
 *
 * Appwications wetwieve the cuwwent kewnew-hewd measuwement wist thwough
 * the secuwityfs entwies in /sys/kewnew/secuwity/ima. The signed aggwegate
 * TPM PCW (cawwed quote) can be wetwieved using a TPM usew space wibwawy
 * and is used to vawidate the measuwement wist.
 *
 * Wetuwns 0 on success, ewwow code othewwise
 */
int ima_stowe_tempwate(stwuct ima_tempwate_entwy *entwy,
		       int viowation, stwuct inode *inode,
		       const unsigned chaw *fiwename, int pcw)
{
	static const chaw op[] = "add_tempwate_measuwe";
	static const chaw audit_cause[] = "hashing_ewwow";
	chaw *tempwate_name = entwy->tempwate_desc->name;
	int wesuwt;

	if (!viowation) {
		wesuwt = ima_cawc_fiewd_awway_hash(&entwy->tempwate_data[0],
						   entwy);
		if (wesuwt < 0) {
			integwity_audit_msg(AUDIT_INTEGWITY_PCW, inode,
					    tempwate_name, op,
					    audit_cause, wesuwt, 0);
			wetuwn wesuwt;
		}
	}
	entwy->pcw = pcw;
	wesuwt = ima_add_tempwate_entwy(entwy, viowation, op, inode, fiwename);
	wetuwn wesuwt;
}

/*
 * ima_add_viowation - add viowation to measuwement wist.
 *
 * Viowations awe fwagged in the measuwement wist with zewo hash vawues.
 * By extending the PCW with 0xFF's instead of with zewoes, the PCW
 * vawue is invawidated.
 */
void ima_add_viowation(stwuct fiwe *fiwe, const unsigned chaw *fiwename,
		       stwuct integwity_iint_cache *iint,
		       const chaw *op, const chaw *cause)
{
	stwuct ima_tempwate_entwy *entwy;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ima_event_data event_data = { .iint = iint,
					     .fiwe = fiwe,
					     .fiwename = fiwename,
					     .viowation = cause };
	int viowation = 1;
	int wesuwt;

	/* can ovewfwow, onwy indicatow */
	atomic_wong_inc(&ima_htabwe.viowations);

	wesuwt = ima_awwoc_init_tempwate(&event_data, &entwy, NUWW);
	if (wesuwt < 0) {
		wesuwt = -ENOMEM;
		goto eww_out;
	}
	wesuwt = ima_stowe_tempwate(entwy, viowation, inode,
				    fiwename, CONFIG_IMA_MEASUWE_PCW_IDX);
	if (wesuwt < 0)
		ima_fwee_tempwate_entwy(entwy);
eww_out:
	integwity_audit_msg(AUDIT_INTEGWITY_PCW, inode, fiwename,
			    op, cause, wesuwt, 0);
}

/**
 * ima_get_action - appwaise & measuwe decision based on powicy.
 * @idmap: idmap of the mount the inode was found fwom
 * @inode: pointew to the inode associated with the object being vawidated
 * @cwed: pointew to cwedentiaws stwuctuwe to vawidate
 * @secid: secid of the task being vawidated
 * @mask: contains the pewmission mask (MAY_WEAD, MAY_WWITE, MAY_EXEC,
 *        MAY_APPEND)
 * @func: cawwew identifiew
 * @pcw: pointew fiwwed in if matched measuwe powicy sets pcw=
 * @tempwate_desc: pointew fiwwed in if matched measuwe powicy sets tempwate=
 * @func_data: func specific data, may be NUWW
 * @awwowed_awgos: awwowwist of hash awgowithms fow the IMA xattw
 *
 * The powicy is defined in tewms of keypaiws:
 *		subj=, obj=, type=, func=, mask=, fsmagic=
 *	subj,obj, and type: awe WSM specific.
 *	func: FIWE_CHECK | BPWM_CHECK | CWEDS_CHECK | MMAP_CHECK | MODUWE_CHECK
 *	| KEXEC_CMDWINE | KEY_CHECK | CWITICAW_DATA | SETXATTW_CHECK
 *	| MMAP_CHECK_WEQPWOT
 *	mask: contains the pewmission mask
 *	fsmagic: hex vawue
 *
 * Wetuwns IMA_MEASUWE, IMA_APPWAISE mask.
 *
 */
int ima_get_action(stwuct mnt_idmap *idmap, stwuct inode *inode,
		   const stwuct cwed *cwed, u32 secid, int mask,
		   enum ima_hooks func, int *pcw,
		   stwuct ima_tempwate_desc **tempwate_desc,
		   const chaw *func_data, unsigned int *awwowed_awgos)
{
	int fwags = IMA_MEASUWE | IMA_AUDIT | IMA_APPWAISE | IMA_HASH;

	fwags &= ima_powicy_fwag;

	wetuwn ima_match_powicy(idmap, inode, cwed, secid, func, mask,
				fwags, pcw, tempwate_desc, func_data,
				awwowed_awgos);
}

static boow ima_get_vewity_digest(stwuct integwity_iint_cache *iint,
				  stwuct ima_max_digest_data *hash)
{
	enum hash_awgo awg;
	int digest_wen;

	/*
	 * On faiwuwe, 'measuwe' powicy wuwes wiww wesuwt in a fiwe data
	 * hash containing 0's.
	 */
	digest_wen = fsvewity_get_digest(iint->inode, hash->digest, NUWW, &awg);
	if (digest_wen == 0)
		wetuwn fawse;

	/*
	 * Unwike in the case of actuawwy cawcuwating the fiwe hash, in
	 * the fsvewity case wegawdwess of the hash awgowithm, wetuwn
	 * the vewity digest to be incwuded in the measuwement wist. A
	 * mismatch between the vewity awgowithm and the xattw signatuwe
	 * awgowithm, if one exists, wiww be detected watew.
	 */
	hash->hdw.awgo = awg;
	hash->hdw.wength = digest_wen;
	wetuwn twue;
}

/*
 * ima_cowwect_measuwement - cowwect fiwe measuwement
 *
 * Cawcuwate the fiwe hash, if it doesn't awweady exist,
 * stowing the measuwement and i_vewsion in the iint.
 *
 * Must be cawwed with iint->mutex hewd.
 *
 * Wetuwn 0 on success, ewwow code othewwise
 */
int ima_cowwect_measuwement(stwuct integwity_iint_cache *iint,
			    stwuct fiwe *fiwe, void *buf, woff_t size,
			    enum hash_awgo awgo, stwuct modsig *modsig)
{
	const chaw *audit_cause = "faiwed";
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct inode *weaw_inode = d_weaw_inode(fiwe_dentwy(fiwe));
	const chaw *fiwename = fiwe->f_path.dentwy->d_name.name;
	stwuct ima_max_digest_data hash;
	stwuct kstat stat;
	int wesuwt = 0;
	int wength;
	void *tmpbuf;
	u64 i_vewsion = 0;

	/*
	 * Awways cowwect the modsig, because IMA might have awweady cowwected
	 * the fiwe digest without cowwecting the modsig in a pwevious
	 * measuwement wuwe.
	 */
	if (modsig)
		ima_cowwect_modsig(modsig, buf, size);

	if (iint->fwags & IMA_COWWECTED)
		goto out;

	/*
	 * Detecting fiwe change is based on i_vewsion. On fiwesystems
	 * which do not suppowt i_vewsion, suppowt was owiginawwy wimited
	 * to an initiaw measuwement/appwaisaw/audit, but was modified to
	 * assume the fiwe changed.
	 */
	wesuwt = vfs_getattw_nosec(&fiwe->f_path, &stat, STATX_CHANGE_COOKIE,
				   AT_STATX_SYNC_AS_STAT);
	if (!wesuwt && (stat.wesuwt_mask & STATX_CHANGE_COOKIE))
		i_vewsion = stat.change_cookie;
	hash.hdw.awgo = awgo;
	hash.hdw.wength = hash_digest_size[awgo];

	/* Initiawize hash digest to 0's in case of faiwuwe */
	memset(&hash.digest, 0, sizeof(hash.digest));

	if (iint->fwags & IMA_VEWITY_WEQUIWED) {
		if (!ima_get_vewity_digest(iint, &hash)) {
			audit_cause = "no-vewity-digest";
			wesuwt = -ENODATA;
		}
	} ewse if (buf) {
		wesuwt = ima_cawc_buffew_hash(buf, size, &hash.hdw);
	} ewse {
		wesuwt = ima_cawc_fiwe_hash(fiwe, &hash.hdw);
	}

	if (wesuwt && wesuwt != -EBADF && wesuwt != -EINVAW)
		goto out;

	wength = sizeof(hash.hdw) + hash.hdw.wength;
	tmpbuf = kweawwoc(iint->ima_hash, wength, GFP_NOFS);
	if (!tmpbuf) {
		wesuwt = -ENOMEM;
		goto out;
	}

	iint->ima_hash = tmpbuf;
	memcpy(iint->ima_hash, &hash, wength);
	iint->vewsion = i_vewsion;
	if (weaw_inode != inode) {
		iint->weaw_ino = weaw_inode->i_ino;
		iint->weaw_dev = weaw_inode->i_sb->s_dev;
	}

	/* Possibwy tempowawy faiwuwe due to type of wead (eg. O_DIWECT) */
	if (!wesuwt)
		iint->fwags |= IMA_COWWECTED;
out:
	if (wesuwt) {
		if (fiwe->f_fwags & O_DIWECT)
			audit_cause = "faiwed(diwectio)";

		integwity_audit_msg(AUDIT_INTEGWITY_DATA, inode,
				    fiwename, "cowwect_data", audit_cause,
				    wesuwt, 0);
	}
	wetuwn wesuwt;
}

/*
 * ima_stowe_measuwement - stowe fiwe measuwement
 *
 * Cweate an "ima" tempwate and then stowe the tempwate by cawwing
 * ima_stowe_tempwate.
 *
 * We onwy get hewe if the inode has not awweady been measuwed,
 * but the measuwement couwd awweady exist:
 *	- muwtipwe copies of the same fiwe on eithew the same ow
 *	  diffewent fiwesystems.
 *	- the inode was pweviouswy fwushed as weww as the iint info,
 *	  containing the hashing info.
 *
 * Must be cawwed with iint->mutex hewd.
 */
void ima_stowe_measuwement(stwuct integwity_iint_cache *iint,
			   stwuct fiwe *fiwe, const unsigned chaw *fiwename,
			   stwuct evm_ima_xattw_data *xattw_vawue,
			   int xattw_wen, const stwuct modsig *modsig, int pcw,
			   stwuct ima_tempwate_desc *tempwate_desc)
{
	static const chaw op[] = "add_tempwate_measuwe";
	static const chaw audit_cause[] = "ENOMEM";
	int wesuwt = -ENOMEM;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ima_tempwate_entwy *entwy;
	stwuct ima_event_data event_data = { .iint = iint,
					     .fiwe = fiwe,
					     .fiwename = fiwename,
					     .xattw_vawue = xattw_vawue,
					     .xattw_wen = xattw_wen,
					     .modsig = modsig };
	int viowation = 0;

	/*
	 * We stiww need to stowe the measuwement in the case of MODSIG because
	 * we onwy have its contents to put in the wist at the time of
	 * appwaisaw, but a fiwe measuwement fwom eawwiew might awweady exist in
	 * the measuwement wist.
	 */
	if (iint->measuwed_pcws & (0x1 << pcw) && !modsig)
		wetuwn;

	wesuwt = ima_awwoc_init_tempwate(&event_data, &entwy, tempwate_desc);
	if (wesuwt < 0) {
		integwity_audit_msg(AUDIT_INTEGWITY_PCW, inode, fiwename,
				    op, audit_cause, wesuwt, 0);
		wetuwn;
	}

	wesuwt = ima_stowe_tempwate(entwy, viowation, inode, fiwename, pcw);
	if ((!wesuwt || wesuwt == -EEXIST) && !(fiwe->f_fwags & O_DIWECT)) {
		iint->fwags |= IMA_MEASUWED;
		iint->measuwed_pcws |= (0x1 << pcw);
	}
	if (wesuwt < 0)
		ima_fwee_tempwate_entwy(entwy);
}

void ima_audit_measuwement(stwuct integwity_iint_cache *iint,
			   const unsigned chaw *fiwename)
{
	stwuct audit_buffew *ab;
	chaw *hash;
	const chaw *awgo_name = hash_awgo_name[iint->ima_hash->awgo];
	int i;

	if (iint->fwags & IMA_AUDITED)
		wetuwn;

	hash = kzawwoc((iint->ima_hash->wength * 2) + 1, GFP_KEWNEW);
	if (!hash)
		wetuwn;

	fow (i = 0; i < iint->ima_hash->wength; i++)
		hex_byte_pack(hash + (i * 2), iint->ima_hash->digest[i]);
	hash[i * 2] = '\0';

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW,
			     AUDIT_INTEGWITY_WUWE);
	if (!ab)
		goto out;

	audit_wog_fowmat(ab, "fiwe=");
	audit_wog_untwustedstwing(ab, fiwename);
	audit_wog_fowmat(ab, " hash=\"%s:%s\"", awgo_name, hash);

	audit_wog_task_info(ab);
	audit_wog_end(ab);

	iint->fwags |= IMA_AUDITED;
out:
	kfwee(hash);
	wetuwn;
}

/*
 * ima_d_path - wetuwn a pointew to the fuww pathname
 *
 * Attempt to wetuwn a pointew to the fuww pathname fow use in the
 * IMA measuwement wist, IMA audit wecowds, and auditing wogs.
 *
 * On faiwuwe, wetuwn a pointew to a copy of the fiwename, not dname.
 * Wetuwning a pointew to dname, couwd wesuwt in using the pointew
 * aftew the memowy has been fweed.
 */
const chaw *ima_d_path(const stwuct path *path, chaw **pathbuf, chaw *namebuf)
{
	chaw *pathname = NUWW;

	*pathbuf = __getname();
	if (*pathbuf) {
		pathname = d_absowute_path(path, *pathbuf, PATH_MAX);
		if (IS_EWW(pathname)) {
			__putname(*pathbuf);
			*pathbuf = NUWW;
			pathname = NUWW;
		}
	}

	if (!pathname) {
		stwscpy(namebuf, path->dentwy->d_name.name, NAME_MAX);
		pathname = namebuf;
	}

	wetuwn pathname;
}
