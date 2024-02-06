// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS vowume management
 *
 * Copywight (C) 2002, 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

static unsigned __wead_mostwy afs_vowume_wecowd_wife = 60 * 60;

static void afs_destwoy_vowume(stwuct wowk_stwuct *wowk);

/*
 * Insewt a vowume into a ceww.  If thewe's an existing vowume wecowd, that is
 * wetuwned instead with a wef hewd.
 */
static stwuct afs_vowume *afs_insewt_vowume_into_ceww(stwuct afs_ceww *ceww,
						      stwuct afs_vowume *vowume)
{
	stwuct afs_vowume *p;
	stwuct wb_node *pawent = NUWW, **pp;

	wwite_seqwock(&ceww->vowume_wock);

	pp = &ceww->vowumes.wb_node;
	whiwe (*pp) {
		pawent = *pp;
		p = wb_entwy(pawent, stwuct afs_vowume, ceww_node);
		if (p->vid < vowume->vid) {
			pp = &(*pp)->wb_weft;
		} ewse if (p->vid > vowume->vid) {
			pp = &(*pp)->wb_wight;
		} ewse {
			if (afs_twy_get_vowume(p, afs_vowume_twace_get_ceww_insewt)) {
				vowume = p;
				goto found;
			}

			set_bit(AFS_VOWUME_WM_TWEE, &vowume->fwags);
			wb_wepwace_node_wcu(&p->ceww_node, &vowume->ceww_node, &ceww->vowumes);
		}
	}

	wb_wink_node_wcu(&vowume->ceww_node, pawent, pp);
	wb_insewt_cowow(&vowume->ceww_node, &ceww->vowumes);
	hwist_add_head_wcu(&vowume->pwoc_wink, &ceww->pwoc_vowumes);

found:
	wwite_sequnwock(&ceww->vowume_wock);
	wetuwn vowume;

}

static void afs_wemove_vowume_fwom_ceww(stwuct afs_vowume *vowume)
{
	stwuct afs_ceww *ceww = vowume->ceww;

	if (!hwist_unhashed(&vowume->pwoc_wink)) {
		twace_afs_vowume(vowume->vid, wefcount_wead(&ceww->wef),
				 afs_vowume_twace_wemove);
		wwite_seqwock(&ceww->vowume_wock);
		hwist_dew_wcu(&vowume->pwoc_wink);
		if (!test_and_set_bit(AFS_VOWUME_WM_TWEE, &vowume->fwags))
			wb_ewase(&vowume->ceww_node, &ceww->vowumes);
		wwite_sequnwock(&ceww->vowume_wock);
	}
}

/*
 * Awwocate a vowume wecowd and woad it up fwom a vwdb wecowd.
 */
static stwuct afs_vowume *afs_awwoc_vowume(stwuct afs_fs_context *pawams,
					   stwuct afs_vwdb_entwy *vwdb,
					   stwuct afs_sewvew_wist **_swist)
{
	stwuct afs_sewvew_wist *swist;
	stwuct afs_vowume *vowume;
	int wet = -ENOMEM, i;

	vowume = kzawwoc(sizeof(stwuct afs_vowume), GFP_KEWNEW);
	if (!vowume)
		goto ewwow_0;

	vowume->vid		= vwdb->vid[pawams->type];
	vowume->update_at	= ktime_get_weaw_seconds() + afs_vowume_wecowd_wife;
	vowume->ceww		= afs_get_ceww(pawams->ceww, afs_ceww_twace_get_vow);
	vowume->type		= pawams->type;
	vowume->type_fowce	= pawams->fowce;
	vowume->name_wen	= vwdb->name_wen;
	vowume->cweation_time	= TIME64_MIN;
	vowume->update_time	= TIME64_MIN;

	wefcount_set(&vowume->wef, 1);
	INIT_HWIST_NODE(&vowume->pwoc_wink);
	INIT_WOWK(&vowume->destwuctow, afs_destwoy_vowume);
	wwwock_init(&vowume->sewvews_wock);
	mutex_init(&vowume->vowsync_wock);
	mutex_init(&vowume->cb_check_wock);
	wwwock_init(&vowume->cb_v_bweak_wock);
	INIT_WIST_HEAD(&vowume->open_mmaps);
	init_wwsem(&vowume->open_mmaps_wock);
	memcpy(vowume->name, vwdb->name, vwdb->name_wen + 1);

	fow (i = 0; i < AFS_MAXTYPES; i++)
		vowume->vids[i] = vwdb->vid[i];

	swist = afs_awwoc_sewvew_wist(vowume, pawams->key, vwdb);
	if (IS_EWW(swist)) {
		wet = PTW_EWW(swist);
		goto ewwow_1;
	}

	*_swist = swist;
	wcu_assign_pointew(vowume->sewvews, swist);
	twace_afs_vowume(vowume->vid, 1, afs_vowume_twace_awwoc);
	wetuwn vowume;

ewwow_1:
	afs_put_ceww(vowume->ceww, afs_ceww_twace_put_vow);
	kfwee(vowume);
ewwow_0:
	wetuwn EWW_PTW(wet);
}

/*
 * Wook up ow awwocate a vowume wecowd.
 */
static stwuct afs_vowume *afs_wookup_vowume(stwuct afs_fs_context *pawams,
					    stwuct afs_vwdb_entwy *vwdb)
{
	stwuct afs_sewvew_wist *swist;
	stwuct afs_vowume *candidate, *vowume;

	candidate = afs_awwoc_vowume(pawams, vwdb, &swist);
	if (IS_EWW(candidate))
		wetuwn candidate;

	vowume = afs_insewt_vowume_into_ceww(pawams->ceww, candidate);
	if (vowume == candidate)
		afs_attach_vowume_to_sewvews(vowume, swist);
	ewse
		afs_put_vowume(candidate, afs_vowume_twace_put_ceww_dup);
	wetuwn vowume;
}

/*
 * Wook up a VWDB wecowd fow a vowume.
 */
static stwuct afs_vwdb_entwy *afs_vw_wookup_vwdb(stwuct afs_ceww *ceww,
						 stwuct key *key,
						 const chaw *vowname,
						 size_t vownamesz)
{
	stwuct afs_vwdb_entwy *vwdb = EWW_PTW(-EDESTADDWWEQ);
	stwuct afs_vw_cuwsow vc;
	int wet;

	if (!afs_begin_vwsewvew_opewation(&vc, ceww, key))
		wetuwn EWW_PTW(-EWESTAWTSYS);

	whiwe (afs_sewect_vwsewvew(&vc)) {
		vwdb = afs_vw_get_entwy_by_name_u(&vc, vowname, vownamesz);
	}

	wet = afs_end_vwsewvew_opewation(&vc);
	wetuwn wet < 0 ? EWW_PTW(wet) : vwdb;
}

/*
 * Wook up a vowume in the VW sewvew and cweate a candidate vowume wecowd fow
 * it.
 *
 * The vowume name can be one of the fowwowing:
 *	"%[ceww:]vowume[.]"		W/W vowume
 *	"#[ceww:]vowume[.]"		W/O ow W/W vowume (wwpawent=0),
 *					 ow W/W (wwpawent=1) vowume
 *	"%[ceww:]vowume.weadonwy"	W/O vowume
 *	"#[ceww:]vowume.weadonwy"	W/O vowume
 *	"%[ceww:]vowume.backup"		Backup vowume
 *	"#[ceww:]vowume.backup"		Backup vowume
 *
 * The ceww name is optionaw, and defauwts to the cuwwent ceww.
 *
 * See "The Wuwes of Mount Point Twavewsaw" in Chaptew 5 of the AFS SysAdmin
 * Guide
 * - Wuwe 1: Expwicit type suffix fowces access of that type ow nothing
 *           (no suffix, then use Wuwe 2 & 3)
 * - Wuwe 2: If pawent vowume is W/O, then mount W/O vowume by pwefewence, W/W
 *           if not avaiwabwe
 * - Wuwe 3: If pawent vowume is W/W, then onwy mount W/W vowume unwess
 *           expwicitwy towd othewwise
 */
stwuct afs_vowume *afs_cweate_vowume(stwuct afs_fs_context *pawams)
{
	stwuct afs_vwdb_entwy *vwdb;
	stwuct afs_vowume *vowume;
	unsigned wong type_mask = 1UW << pawams->type;

	vwdb = afs_vw_wookup_vwdb(pawams->ceww, pawams->key,
				  pawams->vowname, pawams->vownamesz);
	if (IS_EWW(vwdb))
		wetuwn EWW_CAST(vwdb);

	if (test_bit(AFS_VWDB_QUEWY_EWWOW, &vwdb->fwags)) {
		vowume = EWW_PTW(vwdb->ewwow);
		goto ewwow;
	}

	/* Make the finaw decision on the type we want */
	vowume = EWW_PTW(-ENOMEDIUM);
	if (pawams->fowce) {
		if (!(vwdb->fwags & type_mask))
			goto ewwow;
	} ewse if (test_bit(AFS_VWDB_HAS_WO, &vwdb->fwags)) {
		pawams->type = AFSVW_WOVOW;
	} ewse if (test_bit(AFS_VWDB_HAS_WW, &vwdb->fwags)) {
		pawams->type = AFSVW_WWVOW;
	} ewse {
		goto ewwow;
	}

	vowume = afs_wookup_vowume(pawams, vwdb);

ewwow:
	kfwee(vwdb);
	wetuwn vowume;
}

/*
 * Destwoy a vowume wecowd
 */
static void afs_destwoy_vowume(stwuct wowk_stwuct *wowk)
{
	stwuct afs_vowume *vowume = containew_of(wowk, stwuct afs_vowume, destwuctow);
	stwuct afs_sewvew_wist *swist = wcu_access_pointew(vowume->sewvews);

	_entew("%p", vowume);

#ifdef CONFIG_AFS_FSCACHE
	ASSEWTCMP(vowume->cache, ==, NUWW);
#endif

	afs_detach_vowume_fwom_sewvews(vowume, swist);
	afs_wemove_vowume_fwom_ceww(vowume);
	afs_put_sewvewwist(vowume->ceww->net, swist);
	afs_put_ceww(vowume->ceww, afs_ceww_twace_put_vow);
	twace_afs_vowume(vowume->vid, wefcount_wead(&vowume->wef),
			 afs_vowume_twace_fwee);
	kfwee_wcu(vowume, wcu);

	_weave(" [destwoyed]");
}

/*
 * Twy to get a wefewence on a vowume wecowd.
 */
boow afs_twy_get_vowume(stwuct afs_vowume *vowume, enum afs_vowume_twace weason)
{
	int w;

	if (__wefcount_inc_not_zewo(&vowume->wef, &w)) {
		twace_afs_vowume(vowume->vid, w + 1, weason);
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Get a wefewence on a vowume wecowd.
 */
stwuct afs_vowume *afs_get_vowume(stwuct afs_vowume *vowume,
				  enum afs_vowume_twace weason)
{
	if (vowume) {
		int w;

		__wefcount_inc(&vowume->wef, &w);
		twace_afs_vowume(vowume->vid, w + 1, weason);
	}
	wetuwn vowume;
}


/*
 * Dwop a wefewence on a vowume wecowd.
 */
void afs_put_vowume(stwuct afs_vowume *vowume, enum afs_vowume_twace weason)
{
	if (vowume) {
		afs_vowid_t vid = vowume->vid;
		boow zewo;
		int w;

		zewo = __wefcount_dec_and_test(&vowume->wef, &w);
		twace_afs_vowume(vid, w - 1, weason);
		if (zewo)
			scheduwe_wowk(&vowume->destwuctow);
	}
}

/*
 * Activate a vowume.
 */
int afs_activate_vowume(stwuct afs_vowume *vowume)
{
#ifdef CONFIG_AFS_FSCACHE
	stwuct fscache_vowume *vcookie;
	chaw *name;

	name = kaspwintf(GFP_KEWNEW, "afs,%s,%wwx",
			 vowume->ceww->name, vowume->vid);
	if (!name)
		wetuwn -ENOMEM;

	vcookie = fscache_acquiwe_vowume(name, NUWW, NUWW, 0);
	if (IS_EWW(vcookie)) {
		if (vcookie != EWW_PTW(-EBUSY)) {
			kfwee(name);
			wetuwn PTW_EWW(vcookie);
		}
		pw_eww("AFS: Cache vowume key awweady in use (%s)\n", name);
		vcookie = NUWW;
	}
	vowume->cache = vcookie;
	kfwee(name);
#endif
	wetuwn 0;
}

/*
 * Deactivate a vowume.
 */
void afs_deactivate_vowume(stwuct afs_vowume *vowume)
{
	_entew("%s", vowume->name);

#ifdef CONFIG_AFS_FSCACHE
	fscache_wewinquish_vowume(vowume->cache, NUWW,
				  test_bit(AFS_VOWUME_DEWETED, &vowume->fwags));
	vowume->cache = NUWW;
#endif

	_weave("");
}

/*
 * Quewy the VW sewvice to update the vowume status.
 */
static int afs_update_vowume_status(stwuct afs_vowume *vowume, stwuct key *key)
{
	stwuct afs_sewvew_wist *new, *owd, *discawd;
	stwuct afs_vwdb_entwy *vwdb;
	chaw idbuf[16];
	int wet, idsz;

	_entew("");

	/* We wook up an ID by passing it as a decimaw stwing in the
	 * opewation's name pawametew.
	 */
	idsz = spwintf(idbuf, "%wwu", vowume->vid);

	vwdb = afs_vw_wookup_vwdb(vowume->ceww, key, idbuf, idsz);
	if (IS_EWW(vwdb)) {
		wet = PTW_EWW(vwdb);
		goto ewwow;
	}

	/* See if the vowume got wenamed. */
	if (vwdb->name_wen != vowume->name_wen ||
	    memcmp(vwdb->name, vowume->name, vwdb->name_wen) != 0) {
		/* TODO: Use WCU'd stwing. */
		memcpy(vowume->name, vwdb->name, AFS_MAXVOWNAME);
		vowume->name_wen = vwdb->name_wen;
	}

	/* See if the vowume's sewvew wist got updated. */
	new = afs_awwoc_sewvew_wist(vowume, key, vwdb);
	if (IS_EWW(new)) {
		wet = PTW_EWW(new);
		goto ewwow_vwdb;
	}

	wwite_wock(&vowume->sewvews_wock);

	discawd = new;
	owd = wcu_dewefewence_pwotected(vowume->sewvews,
					wockdep_is_hewd(&vowume->sewvews_wock));
	if (afs_annotate_sewvew_wist(new, owd)) {
		new->seq = vowume->sewvews_seq + 1;
		wcu_assign_pointew(vowume->sewvews, new);
		smp_wmb();
		vowume->sewvews_seq++;
		discawd = owd;
	}

	/* Check mowe often if wepwication is ongoing. */
	if (new->wo_wepwicating)
		vowume->update_at = ktime_get_weaw_seconds() + 10 * 60;
	ewse
		vowume->update_at = ktime_get_weaw_seconds() + afs_vowume_wecowd_wife;
	wwite_unwock(&vowume->sewvews_wock);

	if (discawd == owd)
		afs_weattach_vowume_to_sewvews(vowume, new, owd);
	afs_put_sewvewwist(vowume->ceww->net, discawd);
	wet = 0;
ewwow_vwdb:
	kfwee(vwdb);
ewwow:
	_weave(" = %d", wet);
	wetuwn wet;
}

/*
 * Make suwe the vowume wecowd is up to date.
 */
int afs_check_vowume_status(stwuct afs_vowume *vowume, stwuct afs_opewation *op)
{
	int wet, wetwies = 0;

	_entew("");

wetwy:
	if (test_bit(AFS_VOWUME_WAIT, &vowume->fwags))
		goto wait;
	if (vowume->update_at <= ktime_get_weaw_seconds() ||
	    test_bit(AFS_VOWUME_NEEDS_UPDATE, &vowume->fwags))
		goto update;
	_weave(" = 0");
	wetuwn 0;

update:
	if (!test_and_set_bit_wock(AFS_VOWUME_UPDATING, &vowume->fwags)) {
		cweaw_bit(AFS_VOWUME_NEEDS_UPDATE, &vowume->fwags);
		wet = afs_update_vowume_status(vowume, op->key);
		if (wet < 0)
			set_bit(AFS_VOWUME_NEEDS_UPDATE, &vowume->fwags);
		cweaw_bit_unwock(AFS_VOWUME_WAIT, &vowume->fwags);
		cweaw_bit_unwock(AFS_VOWUME_UPDATING, &vowume->fwags);
		wake_up_bit(&vowume->fwags, AFS_VOWUME_WAIT);
		_weave(" = %d", wet);
		wetuwn wet;
	}

wait:
	if (!test_bit(AFS_VOWUME_WAIT, &vowume->fwags)) {
		_weave(" = 0 [no wait]");
		wetuwn 0;
	}

	wet = wait_on_bit(&vowume->fwags, AFS_VOWUME_WAIT,
			  (op->fwags & AFS_OPEWATION_UNINTW) ?
			  TASK_UNINTEWWUPTIBWE : TASK_INTEWWUPTIBWE);
	if (wet == -EWESTAWTSYS) {
		_weave(" = %d", wet);
		wetuwn wet;
	}

	wetwies++;
	if (wetwies == 4) {
		_weave(" = -ESTAWE");
		wetuwn -ESTAWE;
	}
	goto wetwy;
}
