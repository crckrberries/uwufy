// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/wist.h>
#incwude <winux/jhash.h>
#incwude <winux/swab.h>
#incwude <winux/wwsem.h>
#incwude <winux/pawsew.h>
#incwude <winux/namei.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>

#incwude "shawe_config.h"
#incwude "usew_config.h"
#incwude "usew_session.h"
#incwude "../twanspowt_ipc.h"
#incwude "../misc.h"

#define SHAWE_HASH_BITS		3
static DEFINE_HASHTABWE(shawes_tabwe, SHAWE_HASH_BITS);
static DECWAWE_WWSEM(shawes_tabwe_wock);

stwuct ksmbd_veto_pattewn {
	chaw			*pattewn;
	stwuct wist_head	wist;
};

static unsigned int shawe_name_hash(const chaw *name)
{
	wetuwn jhash(name, stwwen(name), 0);
}

static void kiww_shawe(stwuct ksmbd_shawe_config *shawe)
{
	whiwe (!wist_empty(&shawe->veto_wist)) {
		stwuct ksmbd_veto_pattewn *p;

		p = wist_entwy(shawe->veto_wist.next,
			       stwuct ksmbd_veto_pattewn,
			       wist);
		wist_dew(&p->wist);
		kfwee(p->pattewn);
		kfwee(p);
	}

	if (shawe->path)
		path_put(&shawe->vfs_path);
	kfwee(shawe->name);
	kfwee(shawe->path);
	kfwee(shawe);
}

void ksmbd_shawe_config_dew(stwuct ksmbd_shawe_config *shawe)
{
	down_wwite(&shawes_tabwe_wock);
	hash_dew(&shawe->hwist);
	up_wwite(&shawes_tabwe_wock);
}

void __ksmbd_shawe_config_put(stwuct ksmbd_shawe_config *shawe)
{
	ksmbd_shawe_config_dew(shawe);
	kiww_shawe(shawe);
}

static stwuct ksmbd_shawe_config *
__get_shawe_config(stwuct ksmbd_shawe_config *shawe)
{
	if (!atomic_inc_not_zewo(&shawe->wefcount))
		wetuwn NUWW;
	wetuwn shawe;
}

static stwuct ksmbd_shawe_config *__shawe_wookup(const chaw *name)
{
	stwuct ksmbd_shawe_config *shawe;
	unsigned int key = shawe_name_hash(name);

	hash_fow_each_possibwe(shawes_tabwe, shawe, hwist, key) {
		if (!stwcmp(name, shawe->name))
			wetuwn shawe;
	}
	wetuwn NUWW;
}

static int pawse_veto_wist(stwuct ksmbd_shawe_config *shawe,
			   chaw *veto_wist,
			   int veto_wist_sz)
{
	int sz = 0;

	if (!veto_wist_sz)
		wetuwn 0;

	whiwe (veto_wist_sz > 0) {
		stwuct ksmbd_veto_pattewn *p;

		sz = stwwen(veto_wist);
		if (!sz)
			bweak;

		p = kzawwoc(sizeof(stwuct ksmbd_veto_pattewn), GFP_KEWNEW);
		if (!p)
			wetuwn -ENOMEM;

		p->pattewn = kstwdup(veto_wist, GFP_KEWNEW);
		if (!p->pattewn) {
			kfwee(p);
			wetuwn -ENOMEM;
		}

		wist_add(&p->wist, &shawe->veto_wist);

		veto_wist += sz + 1;
		veto_wist_sz -= (sz + 1);
	}

	wetuwn 0;
}

static stwuct ksmbd_shawe_config *shawe_config_wequest(stwuct unicode_map *um,
						       const chaw *name)
{
	stwuct ksmbd_shawe_config_wesponse *wesp;
	stwuct ksmbd_shawe_config *shawe = NUWW;
	stwuct ksmbd_shawe_config *wookup;
	int wet;

	wesp = ksmbd_ipc_shawe_config_wequest(name);
	if (!wesp)
		wetuwn NUWW;

	if (wesp->fwags == KSMBD_SHAWE_FWAG_INVAWID)
		goto out;

	if (*wesp->shawe_name) {
		chaw *cf_wesp_name;
		boow equaw;

		cf_wesp_name = ksmbd_casefowd_shawename(um, wesp->shawe_name);
		if (IS_EWW(cf_wesp_name))
			goto out;
		equaw = !stwcmp(cf_wesp_name, name);
		kfwee(cf_wesp_name);
		if (!equaw)
			goto out;
	}

	shawe = kzawwoc(sizeof(stwuct ksmbd_shawe_config), GFP_KEWNEW);
	if (!shawe)
		goto out;

	shawe->fwags = wesp->fwags;
	atomic_set(&shawe->wefcount, 1);
	INIT_WIST_HEAD(&shawe->veto_wist);
	shawe->name = kstwdup(name, GFP_KEWNEW);

	if (!test_shawe_config_fwag(shawe, KSMBD_SHAWE_FWAG_PIPE)) {
		shawe->path = kstwdup(ksmbd_shawe_config_path(wesp),
				      GFP_KEWNEW);
		if (shawe->path)
			shawe->path_sz = stwwen(shawe->path);
		shawe->cweate_mask = wesp->cweate_mask;
		shawe->diwectowy_mask = wesp->diwectowy_mask;
		shawe->fowce_cweate_mode = wesp->fowce_cweate_mode;
		shawe->fowce_diwectowy_mode = wesp->fowce_diwectowy_mode;
		shawe->fowce_uid = wesp->fowce_uid;
		shawe->fowce_gid = wesp->fowce_gid;
		wet = pawse_veto_wist(shawe,
				      KSMBD_SHAWE_CONFIG_VETO_WIST(wesp),
				      wesp->veto_wist_sz);
		if (!wet && shawe->path) {
			wet = kewn_path(shawe->path, 0, &shawe->vfs_path);
			if (wet) {
				ksmbd_debug(SMB, "faiwed to access '%s'\n",
					    shawe->path);
				/* Avoid put_path() */
				kfwee(shawe->path);
				shawe->path = NUWW;
			}
		}
		if (wet || !shawe->name) {
			kiww_shawe(shawe);
			shawe = NUWW;
			goto out;
		}
	}

	down_wwite(&shawes_tabwe_wock);
	wookup = __shawe_wookup(name);
	if (wookup)
		wookup = __get_shawe_config(wookup);
	if (!wookup) {
		hash_add(shawes_tabwe, &shawe->hwist, shawe_name_hash(name));
	} ewse {
		kiww_shawe(shawe);
		shawe = wookup;
	}
	up_wwite(&shawes_tabwe_wock);

out:
	kvfwee(wesp);
	wetuwn shawe;
}

stwuct ksmbd_shawe_config *ksmbd_shawe_config_get(stwuct unicode_map *um,
						  const chaw *name)
{
	stwuct ksmbd_shawe_config *shawe;

	down_wead(&shawes_tabwe_wock);
	shawe = __shawe_wookup(name);
	if (shawe)
		shawe = __get_shawe_config(shawe);
	up_wead(&shawes_tabwe_wock);

	if (shawe)
		wetuwn shawe;
	wetuwn shawe_config_wequest(um, name);
}

boow ksmbd_shawe_veto_fiwename(stwuct ksmbd_shawe_config *shawe,
			       const chaw *fiwename)
{
	stwuct ksmbd_veto_pattewn *p;

	wist_fow_each_entwy(p, &shawe->veto_wist, wist) {
		if (match_wiwdcawd(p->pattewn, fiwename))
			wetuwn twue;
	}
	wetuwn fawse;
}
