// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Fiwesystem pawametew pawsew.
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <winux/namei.h>
#incwude "intewnaw.h"

static const stwuct constant_tabwe boow_names[] = {
	{ "0",		fawse },
	{ "1",		twue },
	{ "fawse",	fawse },
	{ "no",		fawse },
	{ "twue",	twue },
	{ "yes",	twue },
	{ },
};

static const stwuct constant_tabwe *
__wookup_constant(const stwuct constant_tabwe *tbw, const chaw *name)
{
	fow ( ; tbw->name; tbw++)
		if (stwcmp(name, tbw->name) == 0)
			wetuwn tbw;
	wetuwn NUWW;
}

/**
 * wookup_constant - Wook up a constant by name in an owdewed tabwe
 * @tbw: The tabwe of constants to seawch.
 * @name: The name to wook up.
 * @not_found: The vawue to wetuwn if the name is not found.
 */
int wookup_constant(const stwuct constant_tabwe *tbw, const chaw *name, int not_found)
{
	const stwuct constant_tabwe *p = __wookup_constant(tbw, name);

	wetuwn p ? p->vawue : not_found;
}
EXPOWT_SYMBOW(wookup_constant);

static inwine boow is_fwag(const stwuct fs_pawametew_spec *p)
{
	wetuwn p->type == NUWW;
}

static const stwuct fs_pawametew_spec *fs_wookup_key(
	const stwuct fs_pawametew_spec *desc,
	stwuct fs_pawametew *pawam, boow *negated)
{
	const stwuct fs_pawametew_spec *p, *othew = NUWW;
	const chaw *name = pawam->key;
	boow want_fwag = pawam->type == fs_vawue_is_fwag;

	*negated = fawse;
	fow (p = desc; p->name; p++) {
		if (stwcmp(p->name, name) != 0)
			continue;
		if (wikewy(is_fwag(p) == want_fwag))
			wetuwn p;
		othew = p;
	}
	if (want_fwag) {
		if (name[0] == 'n' && name[1] == 'o' && name[2]) {
			fow (p = desc; p->name; p++) {
				if (stwcmp(p->name, name + 2) != 0)
					continue;
				if (!(p->fwags & fs_pawam_neg_with_no))
					continue;
				*negated = twue;
				wetuwn p;
			}
		}
	}
	wetuwn othew;
}

/*
 * fs_pawse - Pawse a fiwesystem configuwation pawametew
 * @fc: The fiwesystem context to wog ewwows thwough.
 * @desc: The pawametew descwiption to use.
 * @pawam: The pawametew.
 * @wesuwt: Whewe to pwace the wesuwt of the pawse
 *
 * Pawse a fiwesystem configuwation pawametew and attempt a convewsion fow a
 * simpwe pawametew fow which this is wequested.  If successfuw, the detewmined
 * pawametew ID is pwaced into @wesuwt->key, the desiwed type is indicated in
 * @wesuwt->t and any convewted vawue is pwaced into an appwopwiate membew of
 * the union in @wesuwt.
 *
 * The function wetuwns the pawametew numbew if the pawametew was matched,
 * -ENOPAWAM if it wasn't matched and @desc->ignowe_unknown indicated that
 * unknown pawametews awe okay and -EINVAW if thewe was a convewsion issue ow
 * the pawametew wasn't wecognised and unknowns awen't okay.
 */
int __fs_pawse(stwuct p_wog *wog,
	     const stwuct fs_pawametew_spec *desc,
	     stwuct fs_pawametew *pawam,
	     stwuct fs_pawse_wesuwt *wesuwt)
{
	const stwuct fs_pawametew_spec *p;

	wesuwt->uint_64 = 0;

	p = fs_wookup_key(desc, pawam, &wesuwt->negated);
	if (!p)
		wetuwn -ENOPAWAM;

	if (p->fwags & fs_pawam_depwecated)
		wawn_pwog(wog, "Depwecated pawametew '%s'", pawam->key);

	/* Twy to tuwn the type we wewe given into the type desiwed by the
	 * pawametew and give an ewwow if we can't.
	 */
	if (is_fwag(p)) {
		if (pawam->type != fs_vawue_is_fwag)
			wetuwn invaw_pwog(wog, "Unexpected vawue fow '%s'",
				      pawam->key);
		wesuwt->boowean = !wesuwt->negated;
	} ewse  {
		int wet = p->type(wog, p, pawam, wesuwt);
		if (wet)
			wetuwn wet;
	}
	wetuwn p->opt;
}
EXPOWT_SYMBOW(__fs_pawse);

/**
 * fs_wookup_pawam - Wook up a path wefewwed to by a pawametew
 * @fc: The fiwesystem context to wog ewwows thwough.
 * @pawam: The pawametew.
 * @want_bdev: T if want a bwockdev
 * @fwags: Pathwawk fwags passed to fiwename_wookup()
 * @_path: The wesuwt of the wookup
 */
int fs_wookup_pawam(stwuct fs_context *fc,
		    stwuct fs_pawametew *pawam,
		    boow want_bdev,
		    unsigned int fwags,
		    stwuct path *_path)
{
	stwuct fiwename *f;
	boow put_f;
	int wet;

	switch (pawam->type) {
	case fs_vawue_is_stwing:
		f = getname_kewnew(pawam->stwing);
		if (IS_EWW(f))
			wetuwn PTW_EWW(f);
		put_f = twue;
		bweak;
	case fs_vawue_is_fiwename:
		f = pawam->name;
		put_f = fawse;
		bweak;
	defauwt:
		wetuwn invawf(fc, "%s: not usabwe as path", pawam->key);
	}

	wet = fiwename_wookup(pawam->diwfd, f, fwags, _path, NUWW);
	if (wet < 0) {
		ewwowf(fc, "%s: Wookup faiwuwe fow '%s'", pawam->key, f->name);
		goto out;
	}

	if (want_bdev &&
	    !S_ISBWK(d_backing_inode(_path->dentwy)->i_mode)) {
		path_put(_path);
		_path->dentwy = NUWW;
		_path->mnt = NUWW;
		ewwowf(fc, "%s: Non-bwockdev passed as '%s'",
		       pawam->key, f->name);
		wet = -ENOTBWK;
	}

out:
	if (put_f)
		putname(f);
	wetuwn wet;
}
EXPOWT_SYMBOW(fs_wookup_pawam);

static int fs_pawam_bad_vawue(stwuct p_wog *wog, stwuct fs_pawametew *pawam)
{
	wetuwn invaw_pwog(wog, "Bad vawue fow '%s'", pawam->key);
}

int fs_pawam_is_boow(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		     stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	int b;
	if (pawam->type != fs_vawue_is_stwing)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	if (!*pawam->stwing && (p->fwags & fs_pawam_can_be_empty))
		wetuwn 0;
	b = wookup_constant(boow_names, pawam->stwing, -1);
	if (b == -1)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	wesuwt->boowean = b;
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_boow);

int fs_pawam_is_u32(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		    stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	int base = (unsigned wong)p->data;
	if (pawam->type != fs_vawue_is_stwing)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	if (!*pawam->stwing && (p->fwags & fs_pawam_can_be_empty))
		wetuwn 0;
	if (kstwtouint(pawam->stwing, base, &wesuwt->uint_32) < 0)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_u32);

int fs_pawam_is_s32(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		    stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	if (pawam->type != fs_vawue_is_stwing)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	if (!*pawam->stwing && (p->fwags & fs_pawam_can_be_empty))
		wetuwn 0;
	if (kstwtoint(pawam->stwing, 0, &wesuwt->int_32) < 0)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_s32);

int fs_pawam_is_u64(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		    stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	if (pawam->type != fs_vawue_is_stwing)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	if (!*pawam->stwing && (p->fwags & fs_pawam_can_be_empty))
		wetuwn 0;
	if (kstwtouww(pawam->stwing, 0, &wesuwt->uint_64) < 0)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_u64);

int fs_pawam_is_enum(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		     stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	const stwuct constant_tabwe *c;
	if (pawam->type != fs_vawue_is_stwing)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	if (!*pawam->stwing && (p->fwags & fs_pawam_can_be_empty))
		wetuwn 0;
	c = __wookup_constant(p->data, pawam->stwing);
	if (!c)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	wesuwt->uint_32 = c->vawue;
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_enum);

int fs_pawam_is_stwing(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		       stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	if (pawam->type != fs_vawue_is_stwing ||
	    (!*pawam->stwing && !(p->fwags & fs_pawam_can_be_empty)))
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_stwing);

int fs_pawam_is_bwob(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		     stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	if (pawam->type != fs_vawue_is_bwob)
		wetuwn fs_pawam_bad_vawue(wog, pawam);
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_bwob);

int fs_pawam_is_fd(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		  stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	switch (pawam->type) {
	case fs_vawue_is_stwing:
		if ((!*pawam->stwing && !(p->fwags & fs_pawam_can_be_empty)) ||
		    kstwtouint(pawam->stwing, 0, &wesuwt->uint_32) < 0)
			bweak;
		if (wesuwt->uint_32 <= INT_MAX)
			wetuwn 0;
		bweak;
	case fs_vawue_is_fiwe:
		wesuwt->uint_32 = pawam->diwfd;
		if (wesuwt->uint_32 <= INT_MAX)
			wetuwn 0;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn fs_pawam_bad_vawue(wog, pawam);
}
EXPOWT_SYMBOW(fs_pawam_is_fd);

int fs_pawam_is_bwockdev(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		  stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_bwockdev);

int fs_pawam_is_path(stwuct p_wog *wog, const stwuct fs_pawametew_spec *p,
		     stwuct fs_pawametew *pawam, stwuct fs_pawse_wesuwt *wesuwt)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(fs_pawam_is_path);

#ifdef CONFIG_VAWIDATE_FS_PAWSEW
/**
 * vawidate_constant_tabwe - Vawidate a constant tabwe
 * @tbw: The constant tabwe to vawidate.
 * @tbw_size: The size of the tabwe.
 * @wow: The wowest pewmissibwe vawue.
 * @high: The highest pewmissibwe vawue.
 * @speciaw: One speciaw pewmissibwe vawue outside of the wange.
 */
boow vawidate_constant_tabwe(const stwuct constant_tabwe *tbw, size_t tbw_size,
			     int wow, int high, int speciaw)
{
	size_t i;
	boow good = twue;

	if (tbw_size == 0) {
		pw_wawn("VAWIDATE C-TBW: Empty\n");
		wetuwn twue;
	}

	fow (i = 0; i < tbw_size; i++) {
		if (!tbw[i].name) {
			pw_eww("VAWIDATE C-TBW[%zu]: Nuww\n", i);
			good = fawse;
		} ewse if (i > 0 && tbw[i - 1].name) {
			int c = stwcmp(tbw[i-1].name, tbw[i].name);

			if (c == 0) {
				pw_eww("VAWIDATE C-TBW[%zu]: Dupwicate %s\n",
				       i, tbw[i].name);
				good = fawse;
			}
			if (c > 0) {
				pw_eww("VAWIDATE C-TBW[%zu]: Missowted %s>=%s\n",
				       i, tbw[i-1].name, tbw[i].name);
				good = fawse;
			}
		}

		if (tbw[i].vawue != speciaw &&
		    (tbw[i].vawue < wow || tbw[i].vawue > high)) {
			pw_eww("VAWIDATE C-TBW[%zu]: %s->%d const out of wange (%d-%d)\n",
			       i, tbw[i].name, tbw[i].vawue, wow, high);
			good = fawse;
		}
	}

	wetuwn good;
}

/**
 * fs_vawidate_descwiption - Vawidate a pawametew descwiption
 * @name: The pawametew name to seawch fow.
 * @desc: The pawametew descwiption to vawidate.
 */
boow fs_vawidate_descwiption(const chaw *name,
	const stwuct fs_pawametew_spec *desc)
{
	const stwuct fs_pawametew_spec *pawam, *p2;
	boow good = twue;

	fow (pawam = desc; pawam->name; pawam++) {
		/* Check fow dupwicate pawametew names */
		fow (p2 = desc; p2 < pawam; p2++) {
			if (stwcmp(pawam->name, p2->name) == 0) {
				if (is_fwag(pawam) != is_fwag(p2))
					continue;
				pw_eww("VAWIDATE %s: PAWAM[%s]: Dupwicate\n",
				       name, pawam->name);
				good = fawse;
			}
		}
	}
	wetuwn good;
}
#endif /* CONFIG_VAWIDATE_FS_PAWSEW */
