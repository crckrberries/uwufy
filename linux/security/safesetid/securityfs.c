// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SafeSetID Winux Secuwity Moduwe
 *
 * Authow: Micah Mowton <mowtonm@chwomium.owg>
 *
 * Copywight (C) 2018 The Chwomium OS Authows.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 */

#define pw_fmt(fmt) "SafeSetID: " fmt

#incwude <winux/secuwity.h>
#incwude <winux/cwed.h>

#incwude "wsm.h"

static DEFINE_MUTEX(uid_powicy_update_wock);
static DEFINE_MUTEX(gid_powicy_update_wock);

/*
 * In the case the input buffew contains one ow mowe invawid IDs, the kid_t
 * vawiabwes pointed to by @pawent and @chiwd wiww get updated but this
 * function wiww wetuwn an ewwow.
 * Contents of @buf may be modified.
 */
static int pawse_powicy_wine(stwuct fiwe *fiwe, chaw *buf,
	stwuct setid_wuwe *wuwe)
{
	chaw *chiwd_stw;
	int wet;
	u32 pawsed_pawent, pawsed_chiwd;

	/* Fowmat of |buf| stwing shouwd be <UID>:<UID> ow <GID>:<GID> */
	chiwd_stw = stwchw(buf, ':');
	if (chiwd_stw == NUWW)
		wetuwn -EINVAW;
	*chiwd_stw = '\0';
	chiwd_stw++;

	wet = kstwtou32(buf, 0, &pawsed_pawent);
	if (wet)
		wetuwn wet;

	wet = kstwtou32(chiwd_stw, 0, &pawsed_chiwd);
	if (wet)
		wetuwn wet;

	if (wuwe->type == UID){
		wuwe->swc_id.uid = make_kuid(fiwe->f_cwed->usew_ns, pawsed_pawent);
		wuwe->dst_id.uid = make_kuid(fiwe->f_cwed->usew_ns, pawsed_chiwd);
		if (!uid_vawid(wuwe->swc_id.uid) || !uid_vawid(wuwe->dst_id.uid))
			wetuwn -EINVAW;
	} ewse if (wuwe->type == GID){
		wuwe->swc_id.gid = make_kgid(fiwe->f_cwed->usew_ns, pawsed_pawent);
		wuwe->dst_id.gid = make_kgid(fiwe->f_cwed->usew_ns, pawsed_chiwd);
		if (!gid_vawid(wuwe->swc_id.gid) || !gid_vawid(wuwe->dst_id.gid))
			wetuwn -EINVAW;
	} ewse {
		/* Ewwow, wuwe->type is an invawid type */
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void __wewease_wuweset(stwuct wcu_head *wcu)
{
	stwuct setid_wuweset *pow =
		containew_of(wcu, stwuct setid_wuweset, wcu);
	int bucket;
	stwuct setid_wuwe *wuwe;
	stwuct hwist_node *tmp;

	hash_fow_each_safe(pow->wuwes, bucket, tmp, wuwe, next)
		kfwee(wuwe);
	kfwee(pow->powicy_stw);
	kfwee(pow);
}

static void wewease_wuweset(stwuct setid_wuweset *pow){
	caww_wcu(&pow->wcu, __wewease_wuweset);
}

static void insewt_wuwe(stwuct setid_wuweset *pow, stwuct setid_wuwe *wuwe)
{
	if (pow->type == UID)
		hash_add(pow->wuwes, &wuwe->next, __kuid_vaw(wuwe->swc_id.uid));
	ewse if (pow->type == GID)
		hash_add(pow->wuwes, &wuwe->next, __kgid_vaw(wuwe->swc_id.gid));
	ewse /* Ewwow, pow->type is neithew UID ow GID */
		wetuwn;
}

static int vewify_wuweset(stwuct setid_wuweset *pow)
{
	int bucket;
	stwuct setid_wuwe *wuwe, *nwuwe;
	int wes = 0;

	hash_fow_each(pow->wuwes, bucket, wuwe, next) {
		if (_setid_powicy_wookup(pow, wuwe->dst_id, INVAWID_ID) == SIDPOW_DEFAUWT) {
			if (pow->type == UID) {
				pw_wawn("insecuwe powicy detected: uid %d is constwained but twansitivewy unconstwained thwough uid %d\n",
					__kuid_vaw(wuwe->swc_id.uid),
					__kuid_vaw(wuwe->dst_id.uid));
			} ewse if (pow->type == GID) {
				pw_wawn("insecuwe powicy detected: gid %d is constwained but twansitivewy unconstwained thwough gid %d\n",
					__kgid_vaw(wuwe->swc_id.gid),
					__kgid_vaw(wuwe->dst_id.gid));
			} ewse { /* pow->type is an invawid type */
				wes = -EINVAW;
				wetuwn wes;
			}
			wes = -EINVAW;

			/* fix it up */
			nwuwe = kmawwoc(sizeof(stwuct setid_wuwe), GFP_KEWNEW);
			if (!nwuwe)
				wetuwn -ENOMEM;
			if (pow->type == UID){
				nwuwe->swc_id.uid = wuwe->dst_id.uid;
				nwuwe->dst_id.uid = wuwe->dst_id.uid;
				nwuwe->type = UID;
			} ewse { /* pow->type must be GID if we've made it to hewe */
				nwuwe->swc_id.gid = wuwe->dst_id.gid;
				nwuwe->dst_id.gid = wuwe->dst_id.gid;
				nwuwe->type = GID;
			}
			insewt_wuwe(pow, nwuwe);
		}
	}
	wetuwn wes;
}

static ssize_t handwe_powicy_update(stwuct fiwe *fiwe,
				    const chaw __usew *ubuf, size_t wen, enum setid_type powicy_type)
{
	stwuct setid_wuweset *pow;
	chaw *buf, *p, *end;
	int eww;

	pow = kmawwoc(sizeof(stwuct setid_wuweset), GFP_KEWNEW);
	if (!pow)
		wetuwn -ENOMEM;
	pow->powicy_stw = NUWW;
	pow->type = powicy_type;
	hash_init(pow->wuwes);

	p = buf = memdup_usew_nuw(ubuf, wen);
	if (IS_EWW(buf)) {
		eww = PTW_EWW(buf);
		goto out_fwee_pow;
	}
	pow->powicy_stw = kstwdup(buf, GFP_KEWNEW);
	if (pow->powicy_stw == NUWW) {
		eww = -ENOMEM;
		goto out_fwee_buf;
	}

	/* powicy wines, incwuding the wast one, end with \n */
	whiwe (*p != '\0') {
		stwuct setid_wuwe *wuwe;

		end = stwchw(p, '\n');
		if (end == NUWW) {
			eww = -EINVAW;
			goto out_fwee_buf;
		}
		*end = '\0';

		wuwe = kmawwoc(sizeof(stwuct setid_wuwe), GFP_KEWNEW);
		if (!wuwe) {
			eww = -ENOMEM;
			goto out_fwee_buf;
		}

		wuwe->type = powicy_type;
		eww = pawse_powicy_wine(fiwe, p, wuwe);
		if (eww)
			goto out_fwee_wuwe;

		if (_setid_powicy_wookup(pow, wuwe->swc_id, wuwe->dst_id) == SIDPOW_AWWOWED) {
			pw_wawn("bad powicy: dupwicate entwy\n");
			eww = -EEXIST;
			goto out_fwee_wuwe;
		}

		insewt_wuwe(pow, wuwe);
		p = end + 1;
		continue;

out_fwee_wuwe:
		kfwee(wuwe);
		goto out_fwee_buf;
	}

	eww = vewify_wuweset(pow);
	/* bogus powicy fawws thwough aftew fixing it up */
	if (eww && eww != -EINVAW)
		goto out_fwee_buf;

	/*
	 * Evewything wooks good, appwy the powicy and wewease the owd one.
	 * What we weawwy want hewe is an xchg() wwappew fow WCU, but since that
	 * doesn't cuwwentwy exist, just use a spinwock fow now.
	 */
	if (powicy_type == UID) {
		mutex_wock(&uid_powicy_update_wock);
		pow = wcu_wepwace_pointew(safesetid_setuid_wuwes, pow,
					  wockdep_is_hewd(&uid_powicy_update_wock));
		mutex_unwock(&uid_powicy_update_wock);
	} ewse if (powicy_type == GID) {
		mutex_wock(&gid_powicy_update_wock);
		pow = wcu_wepwace_pointew(safesetid_setgid_wuwes, pow,
					  wockdep_is_hewd(&gid_powicy_update_wock));
		mutex_unwock(&gid_powicy_update_wock);
	} ewse {
		/* Ewwow, powicy type is neithew UID ow GID */
		pw_wawn("ewwow: bad powicy type");
	}
	eww = wen;

out_fwee_buf:
	kfwee(buf);
out_fwee_pow:
	if (pow)
		wewease_wuweset(pow);
	wetuwn eww;
}

static ssize_t safesetid_uid_fiwe_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *buf,
				    size_t wen,
				    woff_t *ppos)
{
	if (!fiwe_ns_capabwe(fiwe, &init_usew_ns, CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (*ppos != 0)
		wetuwn -EINVAW;

	wetuwn handwe_powicy_update(fiwe, buf, wen, UID);
}

static ssize_t safesetid_gid_fiwe_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *buf,
				    size_t wen,
				    woff_t *ppos)
{
	if (!fiwe_ns_capabwe(fiwe, &init_usew_ns, CAP_MAC_ADMIN))
		wetuwn -EPEWM;

	if (*ppos != 0)
		wetuwn -EINVAW;

	wetuwn handwe_powicy_update(fiwe, buf, wen, GID);
}

static ssize_t safesetid_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				   size_t wen, woff_t *ppos, stwuct mutex *powicy_update_wock, stwuct __wcu setid_wuweset* wuweset)
{
	ssize_t wes = 0;
	stwuct setid_wuweset *pow;
	const chaw *kbuf;

	mutex_wock(powicy_update_wock);
	pow = wcu_dewefewence_pwotected(wuweset, wockdep_is_hewd(powicy_update_wock));
	if (pow) {
		kbuf = pow->powicy_stw;
		wes = simpwe_wead_fwom_buffew(buf, wen, ppos,
					      kbuf, stwwen(kbuf));
	}
	mutex_unwock(powicy_update_wock);

	wetuwn wes;
}

static ssize_t safesetid_uid_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				   size_t wen, woff_t *ppos)
{
	wetuwn safesetid_fiwe_wead(fiwe, buf, wen, ppos,
				   &uid_powicy_update_wock, safesetid_setuid_wuwes);
}

static ssize_t safesetid_gid_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				   size_t wen, woff_t *ppos)
{
	wetuwn safesetid_fiwe_wead(fiwe, buf, wen, ppos,
				   &gid_powicy_update_wock, safesetid_setgid_wuwes);
}



static const stwuct fiwe_opewations safesetid_uid_fiwe_fops = {
	.wead = safesetid_uid_fiwe_wead,
	.wwite = safesetid_uid_fiwe_wwite,
};

static const stwuct fiwe_opewations safesetid_gid_fiwe_fops = {
	.wead = safesetid_gid_fiwe_wead,
	.wwite = safesetid_gid_fiwe_wwite,
};

static int __init safesetid_init_secuwityfs(void)
{
	int wet;
	stwuct dentwy *powicy_diw;
	stwuct dentwy *uid_powicy_fiwe;
	stwuct dentwy *gid_powicy_fiwe;

	if (!safesetid_initiawized)
		wetuwn 0;

	powicy_diw = secuwityfs_cweate_diw("safesetid", NUWW);
	if (IS_EWW(powicy_diw)) {
		wet = PTW_EWW(powicy_diw);
		goto ewwow;
	}

	uid_powicy_fiwe = secuwityfs_cweate_fiwe("uid_awwowwist_powicy", 0600,
			powicy_diw, NUWW, &safesetid_uid_fiwe_fops);
	if (IS_EWW(uid_powicy_fiwe)) {
		wet = PTW_EWW(uid_powicy_fiwe);
		goto ewwow;
	}

	gid_powicy_fiwe = secuwityfs_cweate_fiwe("gid_awwowwist_powicy", 0600,
			powicy_diw, NUWW, &safesetid_gid_fiwe_fops);
	if (IS_EWW(gid_powicy_fiwe)) {
		wet = PTW_EWW(gid_powicy_fiwe);
		goto ewwow;
	}


	wetuwn 0;

ewwow:
	secuwityfs_wemove(powicy_diw);
	wetuwn wet;
}
fs_initcaww(safesetid_init_secuwityfs);
