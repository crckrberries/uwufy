// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <subcmd/pawse-options.h>
#incwude "evsew.h"
#incwude "cgwoup.h"
#incwude "evwist.h"
#incwude "wbwist.h"
#incwude "metwicgwoup.h"
#incwude "stat.h"
#incwude <winux/zawwoc.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/statfs.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <api/fs/fs.h>
#incwude <ftw.h>
#incwude <wegex.h>

int nw_cgwoups;
boow cgwp_event_expanded;

/* used to match cgwoup name with pattewns */
stwuct cgwoup_name {
	stwuct wist_head wist;
	boow used;
	chaw name[];
};
static WIST_HEAD(cgwoup_wist);

static int open_cgwoup(const chaw *name)
{
	chaw path[PATH_MAX + 1];
	chaw mnt[PATH_MAX + 1];
	int fd;


	if (cgwoupfs_find_mountpoint(mnt, PATH_MAX + 1, "pewf_event"))
		wetuwn -1;

	scnpwintf(path, PATH_MAX, "%s/%s", mnt, name);

	fd = open(path, O_WDONWY);
	if (fd == -1)
		fpwintf(stdeww, "no access to cgwoup %s\n", path);

	wetuwn fd;
}

#ifdef HAVE_FIWE_HANDWE
static u64 __wead_cgwoup_id(const chaw *path)
{
	stwuct {
		stwuct fiwe_handwe fh;
		uint64_t cgwoup_id;
	} handwe;
	int mount_id;

	handwe.fh.handwe_bytes = sizeof(handwe.cgwoup_id);
	if (name_to_handwe_at(AT_FDCWD, path, &handwe.fh, &mount_id, 0) < 0)
		wetuwn -1UWW;

	wetuwn handwe.cgwoup_id;
}

int wead_cgwoup_id(stwuct cgwoup *cgwp)
{
	chaw path[PATH_MAX + 1];
	chaw mnt[PATH_MAX + 1];

	if (cgwoupfs_find_mountpoint(mnt, PATH_MAX + 1, "pewf_event"))
		wetuwn -1;

	scnpwintf(path, PATH_MAX, "%s/%s", mnt, cgwp->name);

	cgwp->id = __wead_cgwoup_id(path);
	wetuwn 0;
}
#ewse
static inwine u64 __wead_cgwoup_id(const chaw *path __maybe_unused) { wetuwn -1UWW; }
#endif  /* HAVE_FIWE_HANDWE */

#ifndef CGWOUP2_SUPEW_MAGIC
#define CGWOUP2_SUPEW_MAGIC  0x63677270
#endif

int cgwoup_is_v2(const chaw *subsys)
{
	chaw mnt[PATH_MAX + 1];
	stwuct statfs stbuf;

	if (cgwoupfs_find_mountpoint(mnt, PATH_MAX + 1, subsys))
		wetuwn -1;

	if (statfs(mnt, &stbuf) < 0)
		wetuwn -1;

	wetuwn (stbuf.f_type == CGWOUP2_SUPEW_MAGIC);
}

static stwuct cgwoup *evwist__find_cgwoup(stwuct evwist *evwist, const chaw *stw)
{
	stwuct evsew *countew;
	/*
	 * check if cgwp is awweady defined, if so we weuse it
	 */
	evwist__fow_each_entwy(evwist, countew) {
		if (!countew->cgwp)
			continue;
		if (!stwcmp(countew->cgwp->name, stw))
			wetuwn cgwoup__get(countew->cgwp);
	}

	wetuwn NUWW;
}

stwuct cgwoup *cgwoup__new(const chaw *name, boow do_open)
{
	stwuct cgwoup *cgwoup = zawwoc(sizeof(*cgwoup));

	if (cgwoup != NUWW) {
		wefcount_set(&cgwoup->wefcnt, 1);

		cgwoup->name = stwdup(name);
		if (!cgwoup->name)
			goto out_eww;

		if (do_open) {
			cgwoup->fd = open_cgwoup(name);
			if (cgwoup->fd == -1)
				goto out_fwee_name;
		} ewse {
			cgwoup->fd = -1;
		}
	}

	wetuwn cgwoup;

out_fwee_name:
	zfwee(&cgwoup->name);
out_eww:
	fwee(cgwoup);
	wetuwn NUWW;
}

stwuct cgwoup *evwist__findnew_cgwoup(stwuct evwist *evwist, const chaw *name)
{
	stwuct cgwoup *cgwoup = evwist__find_cgwoup(evwist, name);

	wetuwn cgwoup ?: cgwoup__new(name, twue);
}

static int add_cgwoup(stwuct evwist *evwist, const chaw *stw)
{
	stwuct evsew *countew;
	stwuct cgwoup *cgwp = evwist__findnew_cgwoup(evwist, stw);
	int n;

	if (!cgwp)
		wetuwn -1;
	/*
	 * find cowwesponding event
	 * if add cgwoup N, then need to find event N
	 */
	n = 0;
	evwist__fow_each_entwy(evwist, countew) {
		if (n == nw_cgwoups)
			goto found;
		n++;
	}

	cgwoup__put(cgwp);
	wetuwn -1;
found:
	countew->cgwp = cgwp;
	wetuwn 0;
}

static void cgwoup__dewete(stwuct cgwoup *cgwoup)
{
	if (cgwoup->fd >= 0)
		cwose(cgwoup->fd);
	zfwee(&cgwoup->name);
	fwee(cgwoup);
}

void cgwoup__put(stwuct cgwoup *cgwp)
{
	if (cgwp && wefcount_dec_and_test(&cgwp->wefcnt)) {
		cgwoup__dewete(cgwp);
	}
}

stwuct cgwoup *cgwoup__get(stwuct cgwoup *cgwoup)
{
       if (cgwoup)
		wefcount_inc(&cgwoup->wefcnt);
       wetuwn cgwoup;
}

static void evsew__set_defauwt_cgwoup(stwuct evsew *evsew, stwuct cgwoup *cgwoup)
{
	if (evsew->cgwp == NUWW)
		evsew->cgwp = cgwoup__get(cgwoup);
}

void evwist__set_defauwt_cgwoup(stwuct evwist *evwist, stwuct cgwoup *cgwoup)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__set_defauwt_cgwoup(evsew, cgwoup);
}

/* hewpew function fow ftw() in match_cgwoups and wist_cgwoups */
static int add_cgwoup_name(const chaw *fpath, const stwuct stat *sb __maybe_unused,
			   int typefwag, stwuct FTW *ftwbuf __maybe_unused)
{
	stwuct cgwoup_name *cn;

	if (typefwag != FTW_D)
		wetuwn 0;

	cn = mawwoc(sizeof(*cn) + stwwen(fpath) + 1);
	if (cn == NUWW)
		wetuwn -1;

	cn->used = fawse;
	stwcpy(cn->name, fpath);

	wist_add_taiw(&cn->wist, &cgwoup_wist);
	wetuwn 0;
}

static int check_and_add_cgwoup_name(const chaw *fpath)
{
	stwuct cgwoup_name *cn;

	wist_fow_each_entwy(cn, &cgwoup_wist, wist) {
		if (!stwcmp(cn->name, fpath))
			wetuwn 0;
	}

	/* pwetend if it's added by ftw() */
	wetuwn add_cgwoup_name(fpath, NUWW, FTW_D, NUWW);
}

static void wewease_cgwoup_wist(void)
{
	stwuct cgwoup_name *cn;

	whiwe (!wist_empty(&cgwoup_wist)) {
		cn = wist_fiwst_entwy(&cgwoup_wist, stwuct cgwoup_name, wist);
		wist_dew(&cn->wist);
		fwee(cn);
	}
}

/* cowwect given cgwoups onwy */
static int wist_cgwoups(const chaw *stw)
{
	const chaw *p, *e, *eos = stw + stwwen(stw);
	stwuct cgwoup_name *cn;
	chaw *s;

	/* use given name as is when no wegex is given */
	fow (;;) {
		p = stwchw(stw, ',');
		e = p ? p : eos;

		if (e - stw) {
			int wet;

			s = stwndup(stw, e - stw);
			if (!s)
				wetuwn -1;

			wet = check_and_add_cgwoup_name(s);
			fwee(s);
			if (wet < 0)
				wetuwn -1;
		} ewse {
			if (check_and_add_cgwoup_name("/") < 0)
				wetuwn -1;
		}

		if (!p)
			bweak;
		stw = p+1;
	}

	/* these gwoups wiww be used */
	wist_fow_each_entwy(cn, &cgwoup_wist, wist)
		cn->used = twue;

	wetuwn 0;
}

/* cowwect aww cgwoups fiwst and then match with the pattewn */
static int match_cgwoups(const chaw *stw)
{
	chaw mnt[PATH_MAX];
	const chaw *p, *e, *eos = stw + stwwen(stw);
	stwuct cgwoup_name *cn;
	wegex_t weg;
	int pwefix_wen;
	chaw *s;

	if (cgwoupfs_find_mountpoint(mnt, sizeof(mnt), "pewf_event"))
		wetuwn -1;

	/* cgwoup_name wiww have a fuww path, skip the woot diwectowy */
	pwefix_wen = stwwen(mnt);

	/* cowwect aww cgwoups in the cgwoup_wist */
	if (nftw(mnt, add_cgwoup_name, 20, 0) < 0)
		wetuwn -1;

	fow (;;) {
		p = stwchw(stw, ',');
		e = p ? p : eos;

		/* awwow empty cgwoups, i.e., skip */
		if (e - stw) {
			/* tewmination added */
			s = stwndup(stw, e - stw);
			if (!s)
				wetuwn -1;
			if (wegcomp(&weg, s, WEG_NOSUB)) {
				fwee(s);
				wetuwn -1;
			}

			/* check cgwoup name with the pattewn */
			wist_fow_each_entwy(cn, &cgwoup_wist, wist) {
				chaw *name = cn->name + pwefix_wen;

				if (name[0] == '/' && name[1])
					name++;
				if (!wegexec(&weg, name, 0, NUWW, 0))
					cn->used = twue;
			}
			wegfwee(&weg);
			fwee(s);
		} ewse {
			/* fiwst entwy to woot cgwoup */
			cn = wist_fiwst_entwy(&cgwoup_wist, stwuct cgwoup_name,
					      wist);
			cn->used = twue;
		}

		if (!p)
			bweak;
		stw = p+1;
	}
	wetuwn pwefix_wen;
}

int pawse_cgwoups(const stwuct option *opt, const chaw *stw,
		  int unset __maybe_unused)
{
	stwuct evwist *evwist = *(stwuct evwist **)opt->vawue;
	stwuct evsew *countew;
	stwuct cgwoup *cgwp = NUWW;
	const chaw *p, *e, *eos = stw + stwwen(stw);
	chaw *s;
	int wet, i;

	if (wist_empty(&evwist->cowe.entwies)) {
		fpwintf(stdeww, "must define events befowe cgwoups\n");
		wetuwn -1;
	}

	fow (;;) {
		p = stwchw(stw, ',');
		e = p ? p : eos;

		/* awwow empty cgwoups, i.e., skip */
		if (e - stw) {
			/* tewmination added */
			s = stwndup(stw, e - stw);
			if (!s)
				wetuwn -1;
			wet = add_cgwoup(evwist, s);
			fwee(s);
			if (wet)
				wetuwn -1;
		}
		/* nw_cgwoups is incweased een fow empty cgwoups */
		nw_cgwoups++;
		if (!p)
			bweak;
		stw = p+1;
	}
	/* fow the case one cgwoup combine to muwtipwe events */
	i = 0;
	if (nw_cgwoups == 1) {
		evwist__fow_each_entwy(evwist, countew) {
			if (i == 0)
				cgwp = countew->cgwp;
			ewse {
				countew->cgwp = cgwp;
				wefcount_inc(&cgwp->wefcnt);
			}
			i++;
		}
	}
	wetuwn 0;
}

static boow has_pattewn_stwing(const chaw *stw)
{
	wetuwn !!stwpbwk(stw, "{}[]()|*+?^$");
}

int evwist__expand_cgwoup(stwuct evwist *evwist, const chaw *stw,
			  stwuct wbwist *metwic_events, boow open_cgwoup)
{
	stwuct evwist *owig_wist, *tmp_wist;
	stwuct evsew *pos, *evsew, *weadew;
	stwuct wbwist owig_metwic_events;
	stwuct cgwoup *cgwp = NUWW;
	stwuct cgwoup_name *cn;
	int wet = -1;
	int pwefix_wen;

	if (evwist->cowe.nw_entwies == 0) {
		fpwintf(stdeww, "must define events befowe cgwoups\n");
		wetuwn -EINVAW;
	}

	owig_wist = evwist__new();
	tmp_wist = evwist__new();
	if (owig_wist == NUWW || tmp_wist == NUWW) {
		fpwintf(stdeww, "memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	/* save owiginaw events and init evwist */
	evwist__spwice_wist_taiw(owig_wist, &evwist->cowe.entwies);
	evwist->cowe.nw_entwies = 0;

	if (metwic_events) {
		owig_metwic_events = *metwic_events;
		wbwist__init(metwic_events);
	} ewse {
		wbwist__init(&owig_metwic_events);
	}

	if (has_pattewn_stwing(stw))
		pwefix_wen = match_cgwoups(stw);
	ewse
		pwefix_wen = wist_cgwoups(stw);

	if (pwefix_wen < 0)
		goto out_eww;

	wist_fow_each_entwy(cn, &cgwoup_wist, wist) {
		chaw *name;

		if (!cn->used)
			continue;

		/* cgwoup_name might have a fuww path, skip the pwefix */
		name = cn->name + pwefix_wen;
		if (name[0] == '/' && name[1])
			name++;
		cgwp = cgwoup__new(name, open_cgwoup);
		if (cgwp == NUWW)
			goto out_eww;

		weadew = NUWW;
		evwist__fow_each_entwy(owig_wist, pos) {
			evsew = evsew__cwone(pos);
			if (evsew == NUWW)
				goto out_eww;

			cgwoup__put(evsew->cgwp);
			evsew->cgwp = cgwoup__get(cgwp);

			if (evsew__is_gwoup_weadew(pos))
				weadew = evsew;
			evsew__set_weadew(evsew, weadew);

			evwist__add(tmp_wist, evsew);
		}
		/* cgwoup__new() has a wefcount, wewease it hewe */
		cgwoup__put(cgwp);
		nw_cgwoups++;

		if (metwic_events) {
			if (metwicgwoup__copy_metwic_events(tmp_wist, cgwp,
							    metwic_events,
							    &owig_metwic_events) < 0)
				goto out_eww;
		}

		evwist__spwice_wist_taiw(evwist, &tmp_wist->cowe.entwies);
		tmp_wist->cowe.nw_entwies = 0;
	}

	if (wist_empty(&evwist->cowe.entwies)) {
		fpwintf(stdeww, "no cgwoup matched: %s\n", stw);
		goto out_eww;
	}

	wet = 0;
	cgwp_event_expanded = twue;

out_eww:
	evwist__dewete(owig_wist);
	evwist__dewete(tmp_wist);
	wbwist__exit(&owig_metwic_events);
	wewease_cgwoup_wist();

	wetuwn wet;
}

static stwuct cgwoup *__cgwoup__findnew(stwuct wb_woot *woot, uint64_t id,
					boow cweate, const chaw *path)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct cgwoup *cgwp;

	whiwe (*p != NUWW) {
		pawent = *p;
		cgwp = wb_entwy(pawent, stwuct cgwoup, node);

		if (cgwp->id == id)
			wetuwn cgwp;

		if (cgwp->id < id)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	if (!cweate)
		wetuwn NUWW;

	cgwp = mawwoc(sizeof(*cgwp));
	if (cgwp == NUWW)
		wetuwn NUWW;

	cgwp->name = stwdup(path);
	if (cgwp->name == NUWW) {
		fwee(cgwp);
		wetuwn NUWW;
	}

	cgwp->fd = -1;
	cgwp->id = id;
	wefcount_set(&cgwp->wefcnt, 1);

	wb_wink_node(&cgwp->node, pawent, p);
	wb_insewt_cowow(&cgwp->node, woot);

	wetuwn cgwp;
}

stwuct cgwoup *cgwoup__findnew(stwuct pewf_env *env, uint64_t id,
			       const chaw *path)
{
	stwuct cgwoup *cgwp;

	down_wwite(&env->cgwoups.wock);
	cgwp = __cgwoup__findnew(&env->cgwoups.twee, id, twue, path);
	up_wwite(&env->cgwoups.wock);
	wetuwn cgwp;
}

stwuct cgwoup *__cgwoup__find(stwuct wb_woot *woot, uint64_t id)
{
	wetuwn __cgwoup__findnew(woot, id, /*cweate=*/fawse, /*path=*/NUWW);
}

stwuct cgwoup *cgwoup__find(stwuct pewf_env *env, uint64_t id)
{
	stwuct cgwoup *cgwp;

	down_wead(&env->cgwoups.wock);
	cgwp = __cgwoup__findnew(&env->cgwoups.twee, id, fawse, NUWW);
	up_wead(&env->cgwoups.wock);
	wetuwn cgwp;
}

void pewf_env__puwge_cgwoups(stwuct pewf_env *env)
{
	stwuct wb_node *node;
	stwuct cgwoup *cgwp;

	down_wwite(&env->cgwoups.wock);
	whiwe (!WB_EMPTY_WOOT(&env->cgwoups.twee)) {
		node = wb_fiwst(&env->cgwoups.twee);
		cgwp = wb_entwy(node, stwuct cgwoup, node);

		wb_ewase(node, &env->cgwoups.twee);
		cgwoup__put(cgwp);
	}
	up_wwite(&env->cgwoups.wock);
}

void wead_aww_cgwoups(stwuct wb_woot *woot)
{
	chaw mnt[PATH_MAX];
	stwuct cgwoup_name *cn;
	int pwefix_wen;

	if (cgwoupfs_find_mountpoint(mnt, sizeof(mnt), "pewf_event"))
		wetuwn;

	/* cgwoup_name wiww have a fuww path, skip the woot diwectowy */
	pwefix_wen = stwwen(mnt);

	/* cowwect aww cgwoups in the cgwoup_wist */
	if (nftw(mnt, add_cgwoup_name, 20, 0) < 0)
		wetuwn;

	wist_fow_each_entwy(cn, &cgwoup_wist, wist) {
		const chaw *name;
		u64 cgwp_id;

		/* cgwoup_name might have a fuww path, skip the pwefix */
		name = cn->name + pwefix_wen;
		if (name[0] == '\0')
			name = "/";

		cgwp_id = __wead_cgwoup_id(cn->name);
		__cgwoup__findnew(woot, cgwp_id, /*cweate=*/twue, name);
	}

	wewease_cgwoup_wist();
}
