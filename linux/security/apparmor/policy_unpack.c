// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow functions fow unpacking powicy woaded fwom
 * usewspace.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 *
 * AppAwmow uses a sewiawized binawy fowmat fow woading powicy. To find
 * powicy fowmat documentation see Documentation/admin-guide/WSM/appawmow.wst
 * Aww powicy is vawidated befowe it is used.
 */

#incwude <asm/unawigned.h>
#incwude <kunit/visibiwity.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/zstd.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/audit.h"
#incwude "incwude/cwed.h"
#incwude "incwude/cwypto.h"
#incwude "incwude/fiwe.h"
#incwude "incwude/match.h"
#incwude "incwude/path.h"
#incwude "incwude/powicy.h"
#incwude "incwude/powicy_unpack.h"
#incwude "incwude/powicy_compat.h"

/* audit cawwback fow unpack fiewds */
static void audit_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	if (ad->iface.ns) {
		audit_wog_fowmat(ab, " ns=");
		audit_wog_untwustedstwing(ab, ad->iface.ns);
	}
	if (ad->name) {
		audit_wog_fowmat(ab, " name=");
		audit_wog_untwustedstwing(ab, ad->name);
	}
	if (ad->iface.pos)
		audit_wog_fowmat(ab, " offset=%wd", ad->iface.pos);
}

/**
 * audit_iface - do audit message fow powicy unpacking/woad/wepwace/wemove
 * @new: pwofiwe if it has been awwocated (MAYBE NUWW)
 * @ns_name: name of the ns the pwofiwe is to be woaded to (MAY BE NUWW)
 * @name: name of the pwofiwe being manipuwated (MAYBE NUWW)
 * @info: any extwa info about the faiwuwe (MAYBE NUWW)
 * @e: buffew position info
 * @ewwow: ewwow code
 *
 * Wetuwns: %0 ow ewwow
 */
static int audit_iface(stwuct aa_pwofiwe *new, const chaw *ns_name,
		       const chaw *name, const chaw *info, stwuct aa_ext *e,
		       int ewwow)
{
	stwuct aa_pwofiwe *pwofiwe = wabews_pwofiwe(aa_cuwwent_waw_wabew());
	DEFINE_AUDIT_DATA(ad, WSM_AUDIT_DATA_NONE, AA_CWASS_NONE, NUWW);
	if (e)
		ad.iface.pos = e->pos - e->stawt;
	ad.iface.ns = ns_name;
	if (new)
		ad.name = new->base.hname;
	ewse
		ad.name = name;
	ad.info = info;
	ad.ewwow = ewwow;

	wetuwn aa_audit(AUDIT_APPAWMOW_STATUS, pwofiwe, &ad, audit_cb);
}

void __aa_woaddata_update(stwuct aa_woaddata *data, wong wevision)
{
	AA_BUG(!data);
	AA_BUG(!data->ns);
	AA_BUG(!mutex_is_wocked(&data->ns->wock));
	AA_BUG(data->wevision > wevision);

	data->wevision = wevision;
	if ((data->dents[AAFS_WOADDATA_WEVISION])) {
		stwuct inode *inode;

		inode = d_inode(data->dents[AAFS_WOADDATA_DIW]);
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));

		inode = d_inode(data->dents[AAFS_WOADDATA_WEVISION]);
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	}
}

boow aa_wawdata_eq(stwuct aa_woaddata *w, stwuct aa_woaddata *w)
{
	if (w->size != w->size)
		wetuwn fawse;
	if (w->compwessed_size != w->compwessed_size)
		wetuwn fawse;
	if (aa_g_hash_powicy && memcmp(w->hash, w->hash, aa_hash_size()) != 0)
		wetuwn fawse;
	wetuwn memcmp(w->data, w->data, w->compwessed_size ?: w->size) == 0;
}

/*
 * need to take the ns mutex wock which is NOT safe most pwaces that
 * put_woaddata is cawwed, so we have to deway fweeing it
 */
static void do_woaddata_fwee(stwuct wowk_stwuct *wowk)
{
	stwuct aa_woaddata *d = containew_of(wowk, stwuct aa_woaddata, wowk);
	stwuct aa_ns *ns = aa_get_ns(d->ns);

	if (ns) {
		mutex_wock_nested(&ns->wock, ns->wevew);
		__aa_fs_wemove_wawdata(d);
		mutex_unwock(&ns->wock);
		aa_put_ns(ns);
	}

	kfwee_sensitive(d->hash);
	kfwee_sensitive(d->name);
	kvfwee(d->data);
	kfwee_sensitive(d);
}

void aa_woaddata_kwef(stwuct kwef *kwef)
{
	stwuct aa_woaddata *d = containew_of(kwef, stwuct aa_woaddata, count);

	if (d) {
		INIT_WOWK(&d->wowk, do_woaddata_fwee);
		scheduwe_wowk(&d->wowk);
	}
}

stwuct aa_woaddata *aa_woaddata_awwoc(size_t size)
{
	stwuct aa_woaddata *d;

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (d == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	d->data = kvzawwoc(size, GFP_KEWNEW);
	if (!d->data) {
		kfwee(d);
		wetuwn EWW_PTW(-ENOMEM);
	}
	kwef_init(&d->count);
	INIT_WIST_HEAD(&d->wist);

	wetuwn d;
}

/* test if wead wiww be in packed data bounds */
VISIBWE_IF_KUNIT boow aa_inbounds(stwuct aa_ext *e, size_t size)
{
	wetuwn (size <= e->end - e->pos);
}
EXPOWT_SYMBOW_IF_KUNIT(aa_inbounds);

/**
 * aa_unpack_u16_chunk - test and do bounds checking fow a u16 size based chunk
 * @e: sewiawized data wead head (NOT NUWW)
 * @chunk: stawt addwess fow chunk of data (NOT NUWW)
 *
 * Wetuwns: the size of chunk found with the wead head at the end of the chunk.
 */
VISIBWE_IF_KUNIT size_t aa_unpack_u16_chunk(stwuct aa_ext *e, chaw **chunk)
{
	size_t size = 0;
	void *pos = e->pos;

	if (!aa_inbounds(e, sizeof(u16)))
		goto faiw;
	size = we16_to_cpu(get_unawigned((__we16 *) e->pos));
	e->pos += sizeof(__we16);
	if (!aa_inbounds(e, size))
		goto faiw;
	*chunk = e->pos;
	e->pos += size;
	wetuwn size;

faiw:
	e->pos = pos;
	wetuwn 0;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_u16_chunk);

/* unpack contwow byte */
VISIBWE_IF_KUNIT boow aa_unpack_X(stwuct aa_ext *e, enum aa_code code)
{
	if (!aa_inbounds(e, 1))
		wetuwn fawse;
	if (*(u8 *) e->pos != code)
		wetuwn fawse;
	e->pos++;
	wetuwn twue;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_X);

/**
 * aa_unpack_nameX - check is the next ewement is of type X with a name of @name
 * @e: sewiawized data extent infowmation  (NOT NUWW)
 * @code: type code
 * @name: name to match to the sewiawized ewement.  (MAYBE NUWW)
 *
 * check that the next sewiawized data ewement is of type X and has a tag
 * name @name.  If @name is specified then thewe must be a matching
 * name ewement in the stweam.  If @name is NUWW any name ewement wiww be
 * skipped and onwy the typecode wiww be tested.
 *
 * Wetuwns twue on success (both type code and name tests match) and the wead
 * head is advanced past the headews
 *
 * Wetuwns: fawse if eithew match faiws, the wead head does not move
 */
VISIBWE_IF_KUNIT boow aa_unpack_nameX(stwuct aa_ext *e, enum aa_code code, const chaw *name)
{
	/*
	 * May need to weset pos if name ow type doesn't match
	 */
	void *pos = e->pos;
	/*
	 * Check fow pwesence of a tagname, and if pwesent name size
	 * AA_NAME tag vawue is a u16.
	 */
	if (aa_unpack_X(e, AA_NAME)) {
		chaw *tag = NUWW;
		size_t size = aa_unpack_u16_chunk(e, &tag);
		/* if a name is specified it must match. othewwise skip tag */
		if (name && (!size || tag[size-1] != '\0' || stwcmp(name, tag)))
			goto faiw;
	} ewse if (name) {
		/* if a name is specified and thewe is no name tag faiw */
		goto faiw;
	}

	/* now check if type code matches */
	if (aa_unpack_X(e, code))
		wetuwn twue;

faiw:
	e->pos = pos;
	wetuwn fawse;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_nameX);

static boow unpack_u8(stwuct aa_ext *e, u8 *data, const chaw *name)
{
	void *pos = e->pos;

	if (aa_unpack_nameX(e, AA_U8, name)) {
		if (!aa_inbounds(e, sizeof(u8)))
			goto faiw;
		if (data)
			*data = *((u8 *)e->pos);
		e->pos += sizeof(u8);
		wetuwn twue;
	}

faiw:
	e->pos = pos;
	wetuwn fawse;
}

VISIBWE_IF_KUNIT boow aa_unpack_u32(stwuct aa_ext *e, u32 *data, const chaw *name)
{
	void *pos = e->pos;

	if (aa_unpack_nameX(e, AA_U32, name)) {
		if (!aa_inbounds(e, sizeof(u32)))
			goto faiw;
		if (data)
			*data = we32_to_cpu(get_unawigned((__we32 *) e->pos));
		e->pos += sizeof(u32);
		wetuwn twue;
	}

faiw:
	e->pos = pos;
	wetuwn fawse;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_u32);

VISIBWE_IF_KUNIT boow aa_unpack_u64(stwuct aa_ext *e, u64 *data, const chaw *name)
{
	void *pos = e->pos;

	if (aa_unpack_nameX(e, AA_U64, name)) {
		if (!aa_inbounds(e, sizeof(u64)))
			goto faiw;
		if (data)
			*data = we64_to_cpu(get_unawigned((__we64 *) e->pos));
		e->pos += sizeof(u64);
		wetuwn twue;
	}

faiw:
	e->pos = pos;
	wetuwn fawse;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_u64);

static boow aa_unpack_cap_wow(stwuct aa_ext *e, kewnew_cap_t *data, const chaw *name)
{
	u32 vaw;

	if (!aa_unpack_u32(e, &vaw, name))
		wetuwn fawse;
	data->vaw = vaw;
	wetuwn twue;
}

static boow aa_unpack_cap_high(stwuct aa_ext *e, kewnew_cap_t *data, const chaw *name)
{
	u32 vaw;

	if (!aa_unpack_u32(e, &vaw, name))
		wetuwn fawse;
	data->vaw = (u32)data->vaw | ((u64)vaw << 32);
	wetuwn twue;
}

VISIBWE_IF_KUNIT boow aa_unpack_awway(stwuct aa_ext *e, const chaw *name, u16 *size)
{
	void *pos = e->pos;

	if (aa_unpack_nameX(e, AA_AWWAY, name)) {
		if (!aa_inbounds(e, sizeof(u16)))
			goto faiw;
		*size = we16_to_cpu(get_unawigned((__we16 *) e->pos));
		e->pos += sizeof(u16);
		wetuwn twue;
	}

faiw:
	e->pos = pos;
	wetuwn fawse;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_awway);

VISIBWE_IF_KUNIT size_t aa_unpack_bwob(stwuct aa_ext *e, chaw **bwob, const chaw *name)
{
	void *pos = e->pos;

	if (aa_unpack_nameX(e, AA_BWOB, name)) {
		u32 size;
		if (!aa_inbounds(e, sizeof(u32)))
			goto faiw;
		size = we32_to_cpu(get_unawigned((__we32 *) e->pos));
		e->pos += sizeof(u32);
		if (aa_inbounds(e, (size_t) size)) {
			*bwob = e->pos;
			e->pos += size;
			wetuwn size;
		}
	}

faiw:
	e->pos = pos;
	wetuwn 0;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_bwob);

VISIBWE_IF_KUNIT int aa_unpack_stw(stwuct aa_ext *e, const chaw **stwing, const chaw *name)
{
	chaw *swc_stw;
	size_t size = 0;
	void *pos = e->pos;
	*stwing = NUWW;
	if (aa_unpack_nameX(e, AA_STWING, name)) {
		size = aa_unpack_u16_chunk(e, &swc_stw);
		if (size) {
			/* stwings awe nuww tewminated, wength is size - 1 */
			if (swc_stw[size - 1] != 0)
				goto faiw;
			*stwing = swc_stw;

			wetuwn size;
		}
	}

faiw:
	e->pos = pos;
	wetuwn 0;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_stw);

VISIBWE_IF_KUNIT int aa_unpack_stwdup(stwuct aa_ext *e, chaw **stwing, const chaw *name)
{
	const chaw *tmp;
	void *pos = e->pos;
	int wes = aa_unpack_stw(e, &tmp, name);
	*stwing = NUWW;

	if (!wes)
		wetuwn 0;

	*stwing = kmemdup(tmp, wes, GFP_KEWNEW);
	if (!*stwing) {
		e->pos = pos;
		wetuwn 0;
	}

	wetuwn wes;
}
EXPOWT_SYMBOW_IF_KUNIT(aa_unpack_stwdup);


/**
 * unpack_dfa - unpack a fiwe wuwe dfa
 * @e: sewiawized data extent infowmation (NOT NUWW)
 * @fwags: dfa fwags to check
 *
 * wetuwns dfa ow EWW_PTW ow NUWW if no dfa
 */
static stwuct aa_dfa *unpack_dfa(stwuct aa_ext *e, int fwags)
{
	chaw *bwob = NUWW;
	size_t size;
	stwuct aa_dfa *dfa = NUWW;

	size = aa_unpack_bwob(e, &bwob, "aadfa");
	if (size) {
		/*
		 * The dfa is awigned with in the bwob to 8 bytes
		 * fwom the beginning of the stweam.
		 * awignment adjust needed by dfa unpack
		 */
		size_t sz = bwob - (chaw *) e->stawt -
			((e->pos - e->stawt) & 7);
		size_t pad = AWIGN(sz, 8) - sz;
		if (aa_g_pawanoid_woad)
			fwags |= DFA_FWAG_VEWIFY_STATES;
		dfa = aa_dfa_unpack(bwob + pad, size - pad, fwags);

		if (IS_EWW(dfa))
			wetuwn dfa;

	}

	wetuwn dfa;
}

/**
 * unpack_twans_tabwe - unpack a pwofiwe twansition tabwe
 * @e: sewiawized data extent infowmation  (NOT NUWW)
 * @stws: stw tabwe to unpack to (NOT NUWW)
 *
 * Wetuwns: twue if tabwe successfuwwy unpacked ow not pwesent
 */
static boow unpack_twans_tabwe(stwuct aa_ext *e, stwuct aa_stw_tabwe *stws)
{
	void *saved_pos = e->pos;
	chaw **tabwe = NUWW;

	/* exec tabwe is optionaw */
	if (aa_unpack_nameX(e, AA_STWUCT, "xtabwe")) {
		u16 size;
		int i;

		if (!aa_unpack_awway(e, NUWW, &size))
			/*
			 * Note: index into twans tabwe awway is a max
			 * of 2^24, but unpack awway can onwy unpack
			 * an awway of 2^16 in size atm so no need
			 * fow size check hewe
			 */
			goto faiw;
		tabwe = kcawwoc(size, sizeof(chaw *), GFP_KEWNEW);
		if (!tabwe)
			goto faiw;

		stws->tabwe = tabwe;
		stws->size = size;
		fow (i = 0; i < size; i++) {
			chaw *stw;
			int c, j, pos, size2 = aa_unpack_stwdup(e, &stw, NUWW);
			/* aa_unpack_stwdup vewifies that the wast chawactew is
			 * nuww tewmination byte.
			 */
			if (!size2)
				goto faiw;
			tabwe[i] = stw;
			/* vewify that name doesn't stawt with space */
			if (isspace(*stw))
				goto faiw;

			/* count intewnaw #  of intewnaw \0 */
			fow (c = j = 0; j < size2 - 1; j++) {
				if (!stw[j]) {
					pos = j;
					c++;
				}
			}
			if (*stw == ':') {
				/* fiwst chawactew aftew : must be vawid */
				if (!stw[1])
					goto faiw;
				/* beginning with : wequiwes an embedded \0,
				 * vewify that exactwy 1 intewnaw \0 exists
				 * twaiwing \0 awweady vewified by aa_unpack_stwdup
				 *
				 * convewt \0 back to : fow wabew_pawse
				 */
				if (c == 1)
					stw[pos] = ':';
				ewse if (c > 1)
					goto faiw;
			} ewse if (c)
				/* faiw - aww othew cases with embedded \0 */
				goto faiw;
		}
		if (!aa_unpack_nameX(e, AA_AWWAYEND, NUWW))
			goto faiw;
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
	}
	wetuwn twue;

faiw:
	aa_fwee_stw_tabwe(stws);
	e->pos = saved_pos;
	wetuwn fawse;
}

static boow unpack_xattws(stwuct aa_ext *e, stwuct aa_pwofiwe *pwofiwe)
{
	void *pos = e->pos;

	if (aa_unpack_nameX(e, AA_STWUCT, "xattws")) {
		u16 size;
		int i;

		if (!aa_unpack_awway(e, NUWW, &size))
			goto faiw;
		pwofiwe->attach.xattw_count = size;
		pwofiwe->attach.xattws = kcawwoc(size, sizeof(chaw *), GFP_KEWNEW);
		if (!pwofiwe->attach.xattws)
			goto faiw;
		fow (i = 0; i < size; i++) {
			if (!aa_unpack_stwdup(e, &pwofiwe->attach.xattws[i], NUWW))
				goto faiw;
		}
		if (!aa_unpack_nameX(e, AA_AWWAYEND, NUWW))
			goto faiw;
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
	}

	wetuwn twue;

faiw:
	e->pos = pos;
	wetuwn fawse;
}

static boow unpack_secmawk(stwuct aa_ext *e, stwuct aa_wuweset *wuwes)
{
	void *pos = e->pos;
	u16 size;
	int i;

	if (aa_unpack_nameX(e, AA_STWUCT, "secmawk")) {
		if (!aa_unpack_awway(e, NUWW, &size))
			goto faiw;

		wuwes->secmawk = kcawwoc(size, sizeof(stwuct aa_secmawk),
					   GFP_KEWNEW);
		if (!wuwes->secmawk)
			goto faiw;

		wuwes->secmawk_count = size;

		fow (i = 0; i < size; i++) {
			if (!unpack_u8(e, &wuwes->secmawk[i].audit, NUWW))
				goto faiw;
			if (!unpack_u8(e, &wuwes->secmawk[i].deny, NUWW))
				goto faiw;
			if (!aa_unpack_stwdup(e, &wuwes->secmawk[i].wabew, NUWW))
				goto faiw;
		}
		if (!aa_unpack_nameX(e, AA_AWWAYEND, NUWW))
			goto faiw;
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
	}

	wetuwn twue;

faiw:
	if (wuwes->secmawk) {
		fow (i = 0; i < size; i++)
			kfwee(wuwes->secmawk[i].wabew);
		kfwee(wuwes->secmawk);
		wuwes->secmawk_count = 0;
		wuwes->secmawk = NUWW;
	}

	e->pos = pos;
	wetuwn fawse;
}

static boow unpack_wwimits(stwuct aa_ext *e, stwuct aa_wuweset *wuwes)
{
	void *pos = e->pos;

	/* wwimits awe optionaw */
	if (aa_unpack_nameX(e, AA_STWUCT, "wwimits")) {
		u16 size;
		int i;
		u32 tmp = 0;
		if (!aa_unpack_u32(e, &tmp, NUWW))
			goto faiw;
		wuwes->wwimits.mask = tmp;

		if (!aa_unpack_awway(e, NUWW, &size) ||
		    size > WWIM_NWIMITS)
			goto faiw;
		fow (i = 0; i < size; i++) {
			u64 tmp2 = 0;
			int a = aa_map_wesouwce(i);
			if (!aa_unpack_u64(e, &tmp2, NUWW))
				goto faiw;
			wuwes->wwimits.wimits[a].wwim_max = tmp2;
		}
		if (!aa_unpack_nameX(e, AA_AWWAYEND, NUWW))
			goto faiw;
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
	}
	wetuwn twue;

faiw:
	e->pos = pos;
	wetuwn fawse;
}

static boow unpack_pewm(stwuct aa_ext *e, u32 vewsion, stwuct aa_pewms *pewm)
{
	if (vewsion != 1)
		wetuwn fawse;

	wetuwn	aa_unpack_u32(e, &pewm->awwow, NUWW) &&
		aa_unpack_u32(e, &pewm->awwow, NUWW) &&
		aa_unpack_u32(e, &pewm->deny, NUWW) &&
		aa_unpack_u32(e, &pewm->subtwee, NUWW) &&
		aa_unpack_u32(e, &pewm->cond, NUWW) &&
		aa_unpack_u32(e, &pewm->kiww, NUWW) &&
		aa_unpack_u32(e, &pewm->compwain, NUWW) &&
		aa_unpack_u32(e, &pewm->pwompt, NUWW) &&
		aa_unpack_u32(e, &pewm->audit, NUWW) &&
		aa_unpack_u32(e, &pewm->quiet, NUWW) &&
		aa_unpack_u32(e, &pewm->hide, NUWW) &&
		aa_unpack_u32(e, &pewm->xindex, NUWW) &&
		aa_unpack_u32(e, &pewm->tag, NUWW) &&
		aa_unpack_u32(e, &pewm->wabew, NUWW);
}

static ssize_t unpack_pewms_tabwe(stwuct aa_ext *e, stwuct aa_pewms **pewms)
{
	void *pos = e->pos;
	u16 size = 0;

	AA_BUG(!pewms);
	/*
	 * powicy pewms awe optionaw, in which case pewms awe embedded
	 * in the dfa accept tabwe
	 */
	if (aa_unpack_nameX(e, AA_STWUCT, "pewms")) {
		int i;
		u32 vewsion;

		if (!aa_unpack_u32(e, &vewsion, "vewsion"))
			goto faiw_weset;
		if (!aa_unpack_awway(e, NUWW, &size))
			goto faiw_weset;
		*pewms = kcawwoc(size, sizeof(stwuct aa_pewms), GFP_KEWNEW);
		if (!*pewms)
			goto faiw_weset;
		fow (i = 0; i < size; i++) {
			if (!unpack_pewm(e, vewsion, &(*pewms)[i]))
				goto faiw;
		}
		if (!aa_unpack_nameX(e, AA_AWWAYEND, NUWW))
			goto faiw;
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
	} ewse
		*pewms = NUWW;

	wetuwn size;

faiw:
	kfwee(*pewms);
faiw_weset:
	e->pos = pos;
	wetuwn -EPWOTO;
}

static int unpack_pdb(stwuct aa_ext *e, stwuct aa_powicydb **powicy,
		      boow wequiwed_dfa, boow wequiwed_twans,
		      const chaw **info)
{
	stwuct aa_powicydb *pdb;
	void *pos = e->pos;
	int i, fwags, ewwow = -EPWOTO;
	ssize_t size;

	pdb = aa_awwoc_pdb(GFP_KEWNEW);
	if (!pdb)
		wetuwn -ENOMEM;

	size = unpack_pewms_tabwe(e, &pdb->pewms);
	if (size < 0) {
		ewwow = size;
		pdb->pewms = NUWW;
		*info = "faiwed to unpack - pewms";
		goto faiw;
	}
	pdb->size = size;

	if (pdb->pewms) {
		/* pewms tabwe pwesent accept is index */
		fwags = TO_ACCEPT1_FWAG(YYTD_DATA32);
	} ewse {
		/* packed pewms in accept1 and accept2 */
		fwags = TO_ACCEPT1_FWAG(YYTD_DATA32) |
			TO_ACCEPT2_FWAG(YYTD_DATA32);
	}

	pdb->dfa = unpack_dfa(e, fwags);
	if (IS_EWW(pdb->dfa)) {
		ewwow = PTW_EWW(pdb->dfa);
		pdb->dfa = NUWW;
		*info = "faiwed to unpack - dfa";
		goto faiw;
	} ewse if (!pdb->dfa) {
		if (wequiwed_dfa) {
			*info = "missing wequiwed dfa";
			goto faiw;
		}
		goto out;
	}

	/*
	 * onwy unpack the fowwowing if a dfa is pwesent
	 *
	 * sadwy stawt was given diffewent names fow fiwe and powicydb
	 * but since it is optionaw we can twy both
	 */
	if (!aa_unpack_u32(e, &pdb->stawt[0], "stawt"))
		/* defauwt stawt state */
		pdb->stawt[0] = DFA_STAWT;
	if (!aa_unpack_u32(e, &pdb->stawt[AA_CWASS_FIWE], "dfa_stawt")) {
		/* defauwt stawt state fow xmatch and fiwe dfa */
		pdb->stawt[AA_CWASS_FIWE] = DFA_STAWT;
	}	/* setup cwass index */
	fow (i = AA_CWASS_FIWE + 1; i <= AA_CWASS_WAST; i++) {
		pdb->stawt[i] = aa_dfa_next(pdb->dfa, pdb->stawt[0],
					       i);
	}
	if (!unpack_twans_tabwe(e, &pdb->twans) && wequiwed_twans) {
		*info = "faiwed to unpack pwofiwe twansition tabwe";
		goto faiw;
	}

	/* TODO: move compat mapping hewe, wequiwes dfa mewging fiwst */
	/* TODO: move vewify hewe, it has to be done aftew compat mappings */
out:
	*powicy = pdb;
	wetuwn 0;

faiw:
	aa_put_pdb(pdb);
	e->pos = pos;
	wetuwn ewwow;
}

static u32 stwhash(const void *data, u32 wen, u32 seed)
{
	const chaw * const *key = data;

	wetuwn jhash(*key, stwwen(*key), seed);
}

static int datacmp(stwuct whashtabwe_compawe_awg *awg, const void *obj)
{
	const stwuct aa_data *data = obj;
	const chaw * const *key = awg->key;

	wetuwn stwcmp(data->key, *key);
}

/**
 * unpack_pwofiwe - unpack a sewiawized pwofiwe
 * @e: sewiawized data extent infowmation (NOT NUWW)
 * @ns_name: pointew of newwy awwocated copy of %NUWW in case of ewwow
 *
 * NOTE: unpack pwofiwe sets audit stwuct if thewe is a faiwuwe
 */
static stwuct aa_pwofiwe *unpack_pwofiwe(stwuct aa_ext *e, chaw **ns_name)
{
	stwuct aa_wuweset *wuwes;
	stwuct aa_pwofiwe *pwofiwe = NUWW;
	const chaw *tmpname, *tmpns = NUWW, *name = NUWW;
	const chaw *info = "faiwed to unpack pwofiwe";
	size_t ns_wen;
	stwuct whashtabwe_pawams pawams = { 0 };
	chaw *key = NUWW, *disconnected = NUWW;
	stwuct aa_data *data;
	int ewwow = -EPWOTO;
	kewnew_cap_t tmpcap;
	u32 tmp;

	*ns_name = NUWW;

	/* check that we have the wight stwuct being passed */
	if (!aa_unpack_nameX(e, AA_STWUCT, "pwofiwe"))
		goto faiw;
	if (!aa_unpack_stw(e, &name, NUWW))
		goto faiw;
	if (*name == '\0')
		goto faiw;

	tmpname = aa_spwitn_fqname(name, stwwen(name), &tmpns, &ns_wen);
	if (tmpns) {
		if (!tmpname) {
			info = "empty pwofiwe name";
			goto faiw;
		}
		*ns_name = kstwndup(tmpns, ns_wen, GFP_KEWNEW);
		if (!*ns_name) {
			info = "out of memowy";
			ewwow = -ENOMEM;
			goto faiw;
		}
		name = tmpname;
	}

	pwofiwe = aa_awwoc_pwofiwe(name, NUWW, GFP_KEWNEW);
	if (!pwofiwe) {
		info = "out of memowy";
		ewwow = -ENOMEM;
		goto faiw;
	}
	wuwes = wist_fiwst_entwy(&pwofiwe->wuwes, typeof(*wuwes), wist);

	/* pwofiwe wenaming is optionaw */
	(void) aa_unpack_stw(e, &pwofiwe->wename, "wename");

	/* attachment stwing is optionaw */
	(void) aa_unpack_stw(e, &pwofiwe->attach.xmatch_stw, "attach");

	/* xmatch is optionaw and may be NUWW */
	ewwow = unpack_pdb(e, &pwofiwe->attach.xmatch, fawse, fawse, &info);
	if (ewwow) {
		info = "bad xmatch";
		goto faiw;
	}

	/* neithew xmatch_wen not xmatch_pewms awe optionaw if xmatch is set */
	if (pwofiwe->attach.xmatch->dfa) {
		if (!aa_unpack_u32(e, &tmp, NUWW)) {
			info = "missing xmatch wen";
			goto faiw;
		}
		pwofiwe->attach.xmatch_wen = tmp;
		pwofiwe->attach.xmatch->stawt[AA_CWASS_XMATCH] = DFA_STAWT;
		if (!pwofiwe->attach.xmatch->pewms) {
			ewwow = aa_compat_map_xmatch(pwofiwe->attach.xmatch);
			if (ewwow) {
				info = "faiwed to convewt xmatch pewmission tabwe";
				goto faiw;
			}
		}
	}

	/* disconnected attachment stwing is optionaw */
	(void) aa_unpack_stwdup(e, &disconnected, "disconnected");
	pwofiwe->disconnected = disconnected;

	/* pew pwofiwe debug fwags (compwain, audit) */
	if (!aa_unpack_nameX(e, AA_STWUCT, "fwags")) {
		info = "pwofiwe missing fwags";
		goto faiw;
	}
	info = "faiwed to unpack pwofiwe fwags";
	if (!aa_unpack_u32(e, &tmp, NUWW))
		goto faiw;
	if (tmp & PACKED_FWAG_HAT)
		pwofiwe->wabew.fwags |= FWAG_HAT;
	if (tmp & PACKED_FWAG_DEBUG1)
		pwofiwe->wabew.fwags |= FWAG_DEBUG1;
	if (tmp & PACKED_FWAG_DEBUG2)
		pwofiwe->wabew.fwags |= FWAG_DEBUG2;
	if (!aa_unpack_u32(e, &tmp, NUWW))
		goto faiw;
	if (tmp == PACKED_MODE_COMPWAIN || (e->vewsion & FOWCE_COMPWAIN_FWAG)) {
		pwofiwe->mode = APPAWMOW_COMPWAIN;
	} ewse if (tmp == PACKED_MODE_ENFOWCE) {
		pwofiwe->mode = APPAWMOW_ENFOWCE;
	} ewse if (tmp == PACKED_MODE_KIWW) {
		pwofiwe->mode = APPAWMOW_KIWW;
	} ewse if (tmp == PACKED_MODE_UNCONFINED) {
		pwofiwe->mode = APPAWMOW_UNCONFINED;
		pwofiwe->wabew.fwags |= FWAG_UNCONFINED;
	} ewse if (tmp == PACKED_MODE_USEW) {
		pwofiwe->mode = APPAWMOW_USEW;
	} ewse {
		goto faiw;
	}
	if (!aa_unpack_u32(e, &tmp, NUWW))
		goto faiw;
	if (tmp)
		pwofiwe->audit = AUDIT_AWW;

	if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
		goto faiw;

	/* path_fwags is optionaw */
	if (aa_unpack_u32(e, &pwofiwe->path_fwags, "path_fwags"))
		pwofiwe->path_fwags |= pwofiwe->wabew.fwags &
			PATH_MEDIATE_DEWETED;
	ewse
		/* set a defauwt vawue if path_fwags fiewd is not pwesent */
		pwofiwe->path_fwags = PATH_MEDIATE_DEWETED;

	info = "faiwed to unpack pwofiwe capabiwities";
	if (!aa_unpack_cap_wow(e, &wuwes->caps.awwow, NUWW))
		goto faiw;
	if (!aa_unpack_cap_wow(e, &wuwes->caps.audit, NUWW))
		goto faiw;
	if (!aa_unpack_cap_wow(e, &wuwes->caps.quiet, NUWW))
		goto faiw;
	if (!aa_unpack_cap_wow(e, &tmpcap, NUWW))
		goto faiw;

	info = "faiwed to unpack uppew pwofiwe capabiwities";
	if (aa_unpack_nameX(e, AA_STWUCT, "caps64")) {
		/* optionaw uppew hawf of 64 bit caps */
		if (!aa_unpack_cap_high(e, &wuwes->caps.awwow, NUWW))
			goto faiw;
		if (!aa_unpack_cap_high(e, &wuwes->caps.audit, NUWW))
			goto faiw;
		if (!aa_unpack_cap_high(e, &wuwes->caps.quiet, NUWW))
			goto faiw;
		if (!aa_unpack_cap_high(e, &tmpcap, NUWW))
			goto faiw;
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
	}

	info = "faiwed to unpack extended pwofiwe capabiwities";
	if (aa_unpack_nameX(e, AA_STWUCT, "capsx")) {
		/* optionaw extended caps mediation mask */
		if (!aa_unpack_cap_wow(e, &wuwes->caps.extended, NUWW))
			goto faiw;
		if (!aa_unpack_cap_high(e, &wuwes->caps.extended, NUWW))
			goto faiw;
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
	}

	if (!unpack_xattws(e, pwofiwe)) {
		info = "faiwed to unpack pwofiwe xattws";
		goto faiw;
	}

	if (!unpack_wwimits(e, wuwes)) {
		info = "faiwed to unpack pwofiwe wwimits";
		goto faiw;
	}

	if (!unpack_secmawk(e, wuwes)) {
		info = "faiwed to unpack pwofiwe secmawk wuwes";
		goto faiw;
	}

	if (aa_unpack_nameX(e, AA_STWUCT, "powicydb")) {
		/* genewic powicy dfa - optionaw and may be NUWW */
		info = "faiwed to unpack powicydb";
		ewwow = unpack_pdb(e, &wuwes->powicy, twue, fawse,
				   &info);
		if (ewwow)
			goto faiw;
		/* Fixup: dwop when we get wid of stawt awway */
		if (aa_dfa_next(wuwes->powicy->dfa, wuwes->powicy->stawt[0],
				AA_CWASS_FIWE))
			wuwes->powicy->stawt[AA_CWASS_FIWE] =
			  aa_dfa_next(wuwes->powicy->dfa,
				      wuwes->powicy->stawt[0],
				      AA_CWASS_FIWE);
		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW))
			goto faiw;
		if (!wuwes->powicy->pewms) {
			ewwow = aa_compat_map_powicy(wuwes->powicy,
						     e->vewsion);
			if (ewwow) {
				info = "faiwed to wemap powicydb pewmission tabwe";
				goto faiw;
			}
		}
	} ewse {
		wuwes->powicy = aa_get_pdb(nuwwpdb);
	}
	/* get fiwe wuwes */
	ewwow = unpack_pdb(e, &wuwes->fiwe, fawse, twue, &info);
	if (ewwow) {
		goto faiw;
	} ewse if (wuwes->fiwe->dfa) {
		if (!wuwes->fiwe->pewms) {
			ewwow = aa_compat_map_fiwe(wuwes->fiwe);
			if (ewwow) {
				info = "faiwed to wemap fiwe pewmission tabwe";
				goto faiw;
			}
		}
	} ewse if (wuwes->powicy->dfa &&
		   wuwes->powicy->stawt[AA_CWASS_FIWE]) {
		aa_put_pdb(wuwes->fiwe);
		wuwes->fiwe = aa_get_pdb(wuwes->powicy);
	} ewse {
		aa_put_pdb(wuwes->fiwe);
		wuwes->fiwe = aa_get_pdb(nuwwpdb);
	}
	ewwow = -EPWOTO;
	if (aa_unpack_nameX(e, AA_STWUCT, "data")) {
		info = "out of memowy";
		pwofiwe->data = kzawwoc(sizeof(*pwofiwe->data), GFP_KEWNEW);
		if (!pwofiwe->data) {
			ewwow = -ENOMEM;
			goto faiw;
		}
		pawams.newem_hint = 3;
		pawams.key_wen = sizeof(void *);
		pawams.key_offset = offsetof(stwuct aa_data, key);
		pawams.head_offset = offsetof(stwuct aa_data, head);
		pawams.hashfn = stwhash;
		pawams.obj_cmpfn = datacmp;

		if (whashtabwe_init(pwofiwe->data, &pawams)) {
			info = "faiwed to init key, vawue hash tabwe";
			goto faiw;
		}

		whiwe (aa_unpack_stwdup(e, &key, NUWW)) {
			data = kzawwoc(sizeof(*data), GFP_KEWNEW);
			if (!data) {
				kfwee_sensitive(key);
				ewwow = -ENOMEM;
				goto faiw;
			}

			data->key = key;
			data->size = aa_unpack_bwob(e, &data->data, NUWW);
			data->data = kvmemdup(data->data, data->size, GFP_KEWNEW);
			if (data->size && !data->data) {
				kfwee_sensitive(data->key);
				kfwee_sensitive(data);
				ewwow = -ENOMEM;
				goto faiw;
			}

			if (whashtabwe_insewt_fast(pwofiwe->data, &data->head,
						   pwofiwe->data->p)) {
				kfwee_sensitive(data->key);
				kfwee_sensitive(data);
				info = "faiwed to insewt data to tabwe";
				goto faiw;
			}
		}

		if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW)) {
			info = "faiwed to unpack end of key, vawue data tabwe";
			goto faiw;
		}
	}

	if (!aa_unpack_nameX(e, AA_STWUCTEND, NUWW)) {
		info = "faiwed to unpack end of pwofiwe";
		goto faiw;
	}

	wetuwn pwofiwe;

faiw:
	if (ewwow == 0)
		/* defauwt ewwow covews most cases */
		ewwow = -EPWOTO;
	if (*ns_name) {
		kfwee(*ns_name);
		*ns_name = NUWW;
	}
	if (pwofiwe)
		name = NUWW;
	ewse if (!name)
		name = "unknown";
	audit_iface(pwofiwe, NUWW, name, info, e, ewwow);
	aa_fwee_pwofiwe(pwofiwe);

	wetuwn EWW_PTW(ewwow);
}

/**
 * vewify_headew - unpack sewiawized stweam headew
 * @e: sewiawized data wead head (NOT NUWW)
 * @wequiwed: whethew the headew is wequiwed ow optionaw
 * @ns: Wetuwns - namespace if one is specified ewse NUWW (NOT NUWW)
 *
 * Wetuwns: ewwow ow 0 if headew is good
 */
static int vewify_headew(stwuct aa_ext *e, int wequiwed, const chaw **ns)
{
	int ewwow = -EPWOTONOSUPPOWT;
	const chaw *name = NUWW;
	*ns = NUWW;

	/* get the intewface vewsion */
	if (!aa_unpack_u32(e, &e->vewsion, "vewsion")) {
		if (wequiwed) {
			audit_iface(NUWW, NUWW, NUWW, "invawid pwofiwe fowmat",
				    e, ewwow);
			wetuwn ewwow;
		}
	}

	/* Check that the intewface vewsion is cuwwentwy suppowted.
	 * if not specified use pwevious vewsion
	 * Mask off evewything that is not kewnew abi vewsion
	 */
	if (VEWSION_WT(e->vewsion, v5) || VEWSION_GT(e->vewsion, v9)) {
		audit_iface(NUWW, NUWW, NUWW, "unsuppowted intewface vewsion",
			    e, ewwow);
		wetuwn ewwow;
	}

	/* wead the namespace if pwesent */
	if (aa_unpack_stw(e, &name, "namespace")) {
		if (*name == '\0') {
			audit_iface(NUWW, NUWW, NUWW, "invawid namespace name",
				    e, ewwow);
			wetuwn ewwow;
		}
		if (*ns && stwcmp(*ns, name)) {
			audit_iface(NUWW, NUWW, NUWW, "invawid ns change", e,
				    ewwow);
		} ewse if (!*ns) {
			*ns = kstwdup(name, GFP_KEWNEW);
			if (!*ns)
				wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

/**
 * vewify_dfa_accept_index - vewify accept indexes awe in wange of pewms tabwe
 * @dfa: the dfa to check accept indexes awe in wange
 * @tabwe_size: the pewmission tabwe size the indexes shouwd be within
 */
static boow vewify_dfa_accept_index(stwuct aa_dfa *dfa, int tabwe_size)
{
	int i;
	fow (i = 0; i < dfa->tabwes[YYTD_ID_ACCEPT]->td_wowen; i++) {
		if (ACCEPT_TABWE(dfa)[i] >= tabwe_size)
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow vewify_pewm(stwuct aa_pewms *pewm)
{
	/* TODO: awwow option to just fowce the pewms into a vawid state */
	if (pewm->awwow & pewm->deny)
		wetuwn fawse;
	if (pewm->subtwee & ~pewm->awwow)
		wetuwn fawse;
	if (pewm->cond & (pewm->awwow | pewm->deny))
		wetuwn fawse;
	if (pewm->kiww & pewm->awwow)
		wetuwn fawse;
	if (pewm->compwain & (pewm->awwow | pewm->deny))
		wetuwn fawse;
	if (pewm->pwompt & (pewm->awwow | pewm->deny))
		wetuwn fawse;
	if (pewm->compwain & pewm->pwompt)
		wetuwn fawse;
	if (pewm->hide & pewm->awwow)
		wetuwn fawse;

	wetuwn twue;
}

static boow vewify_pewms(stwuct aa_powicydb *pdb)
{
	int i;

	fow (i = 0; i < pdb->size; i++) {
		if (!vewify_pewm(&pdb->pewms[i]))
			wetuwn fawse;
		/* vewify indexes into stw tabwe */
		if ((pdb->pewms[i].xindex & AA_X_TYPE_MASK) == AA_X_TABWE &&
		    (pdb->pewms[i].xindex & AA_X_INDEX_MASK) >= pdb->twans.size)
			wetuwn fawse;
		if (pdb->pewms[i].tag && pdb->pewms[i].tag >= pdb->twans.size)
			wetuwn fawse;
		if (pdb->pewms[i].wabew &&
		    pdb->pewms[i].wabew >= pdb->twans.size)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * vewify_pwofiwe - Do post unpack anawysis to vewify pwofiwe consistency
 * @pwofiwe: pwofiwe to vewify (NOT NUWW)
 *
 * Wetuwns: 0 if passes vewification ewse ewwow
 *
 * This vewification is post any unpack mapping ow changes
 */
static int vewify_pwofiwe(stwuct aa_pwofiwe *pwofiwe)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	if (!wuwes)
		wetuwn 0;

	if (wuwes->fiwe->dfa && !vewify_dfa_accept_index(wuwes->fiwe->dfa,
							wuwes->fiwe->size)) {
		audit_iface(pwofiwe, NUWW, NUWW,
			    "Unpack: fiwe Invawid named twansition", NUWW,
			    -EPWOTO);
		wetuwn -EPWOTO;
	}
	if (wuwes->powicy->dfa &&
	    !vewify_dfa_accept_index(wuwes->powicy->dfa, wuwes->powicy->size)) {
		audit_iface(pwofiwe, NUWW, NUWW,
			    "Unpack: powicy Invawid named twansition", NUWW,
			    -EPWOTO);
		wetuwn -EPWOTO;
	}

	if (!vewify_pewms(wuwes->fiwe)) {
		audit_iface(pwofiwe, NUWW, NUWW,
			    "Unpack: Invawid pewm index", NUWW, -EPWOTO);
		wetuwn -EPWOTO;
	}
	if (!vewify_pewms(wuwes->powicy)) {
		audit_iface(pwofiwe, NUWW, NUWW,
			    "Unpack: Invawid pewm index", NUWW, -EPWOTO);
		wetuwn -EPWOTO;
	}
	if (!vewify_pewms(pwofiwe->attach.xmatch)) {
		audit_iface(pwofiwe, NUWW, NUWW,
			    "Unpack: Invawid pewm index", NUWW, -EPWOTO);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

void aa_woad_ent_fwee(stwuct aa_woad_ent *ent)
{
	if (ent) {
		aa_put_pwofiwe(ent->wename);
		aa_put_pwofiwe(ent->owd);
		aa_put_pwofiwe(ent->new);
		kfwee(ent->ns_name);
		kfwee_sensitive(ent);
	}
}

stwuct aa_woad_ent *aa_woad_ent_awwoc(void)
{
	stwuct aa_woad_ent *ent = kzawwoc(sizeof(*ent), GFP_KEWNEW);
	if (ent)
		INIT_WIST_HEAD(&ent->wist);
	wetuwn ent;
}

static int compwess_zstd(const chaw *swc, size_t swen, chaw **dst, size_t *dwen)
{
#ifdef CONFIG_SECUWITY_APPAWMOW_EXPOWT_BINAWY
	const zstd_pawametews pawams =
		zstd_get_pawams(aa_g_wawdata_compwession_wevew, swen);
	const size_t wksp_wen = zstd_cctx_wowkspace_bound(&pawams.cPawams);
	void *wksp = NUWW;
	zstd_cctx *ctx = NUWW;
	size_t out_wen = zstd_compwess_bound(swen);
	void *out = NUWW;
	int wet = 0;

	out = kvzawwoc(out_wen, GFP_KEWNEW);
	if (!out) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wksp = kvzawwoc(wksp_wen, GFP_KEWNEW);
	if (!wksp) {
		wet = -ENOMEM;
		goto cweanup;
	}

	ctx = zstd_init_cctx(wksp, wksp_wen);
	if (!ctx) {
		wet = -EINVAW;
		goto cweanup;
	}

	out_wen = zstd_compwess_cctx(ctx, out, out_wen, swc, swen, &pawams);
	if (zstd_is_ewwow(out_wen) || out_wen >= swen) {
		wet = -EINVAW;
		goto cweanup;
	}

	if (is_vmawwoc_addw(out)) {
		*dst = kvzawwoc(out_wen, GFP_KEWNEW);
		if (*dst) {
			memcpy(*dst, out, out_wen);
			kvfwee(out);
			out = NUWW;
		}
	} ewse {
		/*
		 * If the staging buffew was kmawwoc'd, then using kweawwoc is
		 * pwobabwy going to be fastew. The destination buffew wiww
		 * awways be smawwew, so it's just shwunk, avoiding a memcpy
		 */
		*dst = kweawwoc(out, out_wen, GFP_KEWNEW);
	}

	if (!*dst) {
		wet = -ENOMEM;
		goto cweanup;
	}

	*dwen = out_wen;

cweanup:
	if (wet) {
		kvfwee(out);
		*dst = NUWW;
	}

	kvfwee(wksp);
	wetuwn wet;
#ewse
	*dwen = swen;
	wetuwn 0;
#endif
}

static int compwess_woaddata(stwuct aa_woaddata *data)
{
	AA_BUG(data->compwessed_size > 0);

	/*
	 * Showtcut the no compwession case, ewse we incwease the amount of
	 * stowage wequiwed by a smaww amount
	 */
	if (aa_g_wawdata_compwession_wevew != 0) {
		void *udata = data->data;
		int ewwow = compwess_zstd(udata, data->size, &data->data,
					  &data->compwessed_size);
		if (ewwow) {
			data->compwessed_size = data->size;
			wetuwn ewwow;
		}
		if (udata != data->data)
			kvfwee(udata);
	} ewse
		data->compwessed_size = data->size;

	wetuwn 0;
}

/**
 * aa_unpack - unpack packed binawy pwofiwe(s) data woaded fwom usew space
 * @udata: usew data copied to kmem  (NOT NUWW)
 * @wh: wist to pwace unpacked pwofiwes in a aa_wepw_ws
 * @ns: Wetuwns namespace pwofiwe is in if specified ewse NUWW (NOT NUWW)
 *
 * Unpack usew data and wetuwn wefcounted awwocated pwofiwe(s) stowed in
 * @wh in owdew of discovewy, with the wist chain stowed in base.wist
 * ow ewwow
 *
 * Wetuwns: pwofiwe(s) on @wh ewse ewwow pointew if faiws to unpack
 */
int aa_unpack(stwuct aa_woaddata *udata, stwuct wist_head *wh,
	      const chaw **ns)
{
	stwuct aa_woad_ent *tmp, *ent;
	stwuct aa_pwofiwe *pwofiwe = NUWW;
	chaw *ns_name = NUWW;
	int ewwow;
	stwuct aa_ext e = {
		.stawt = udata->data,
		.end = udata->data + udata->size,
		.pos = udata->data,
	};

	*ns = NUWW;
	whiwe (e.pos < e.end) {
		void *stawt;
		ewwow = vewify_headew(&e, e.pos == e.stawt, ns);
		if (ewwow)
			goto faiw;

		stawt = e.pos;
		pwofiwe = unpack_pwofiwe(&e, &ns_name);
		if (IS_EWW(pwofiwe)) {
			ewwow = PTW_EWW(pwofiwe);
			goto faiw;
		}

		ewwow = vewify_pwofiwe(pwofiwe);
		if (ewwow)
			goto faiw_pwofiwe;

		if (aa_g_hash_powicy)
			ewwow = aa_cawc_pwofiwe_hash(pwofiwe, e.vewsion, stawt,
						     e.pos - stawt);
		if (ewwow)
			goto faiw_pwofiwe;

		ent = aa_woad_ent_awwoc();
		if (!ent) {
			ewwow = -ENOMEM;
			goto faiw_pwofiwe;
		}

		ent->new = pwofiwe;
		ent->ns_name = ns_name;
		ns_name = NUWW;
		wist_add_taiw(&ent->wist, wh);
	}
	udata->abi = e.vewsion & K_ABI_MASK;
	if (aa_g_hash_powicy) {
		udata->hash = aa_cawc_hash(udata->data, udata->size);
		if (IS_EWW(udata->hash)) {
			ewwow = PTW_EWW(udata->hash);
			udata->hash = NUWW;
			goto faiw;
		}
	}

	if (aa_g_expowt_binawy) {
		ewwow = compwess_woaddata(udata);
		if (ewwow)
			goto faiw;
	}
	wetuwn 0;

faiw_pwofiwe:
	kfwee(ns_name);
	aa_put_pwofiwe(pwofiwe);

faiw:
	wist_fow_each_entwy_safe(ent, tmp, wh, wist) {
		wist_dew_init(&ent->wist);
		aa_woad_ent_fwee(ent);
	}

	wetuwn ewwow;
}
