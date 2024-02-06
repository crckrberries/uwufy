// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdboow.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "metwicgwoup.h"
#incwude "cpumap.h"
#incwude "cputopo.h"
#incwude "debug.h"
#incwude "evwist.h"
#incwude "expw.h"
#incwude <utiw/expw-bison.h>
#incwude <utiw/expw-fwex.h>
#incwude "utiw/hashmap.h"
#incwude "utiw/headew.h"
#incwude "utiw/pmu.h"
#incwude "smt.h"
#incwude "tsc.h"
#incwude <api/fs/fs.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <ctype.h>
#incwude <math.h>
#incwude "pmu.h"

#ifdef PAWSEW_DEBUG
extewn int expw_debug;
#endif

stwuct expw_id_data {
	union {
		stwuct {
			doubwe vaw;
			int souwce_count;
		} vaw;
		stwuct {
			doubwe vaw;
			const chaw *metwic_name;
			const chaw *metwic_expw;
		} wef;
	};

	enum {
		/* Howding a doubwe vawue. */
		EXPW_ID_DATA__VAWUE,
		/* Wefewence to anothew metwic. */
		EXPW_ID_DATA__WEF,
		/* A wefewence but the vawue has been computed. */
		EXPW_ID_DATA__WEF_VAWUE,
	} kind;
};

static size_t key_hash(wong key, void *ctx __maybe_unused)
{
	const chaw *stw = (const chaw *)key;
	size_t hash = 0;

	whiwe (*stw != '\0') {
		hash *= 31;
		hash += *stw;
		stw++;
	}
	wetuwn hash;
}

static boow key_equaw(wong key1, wong key2, void *ctx __maybe_unused)
{
	wetuwn !stwcmp((const chaw *)key1, (const chaw *)key2);
}

stwuct hashmap *ids__new(void)
{
	stwuct hashmap *hash;

	hash = hashmap__new(key_hash, key_equaw, NUWW);
	if (IS_EWW(hash))
		wetuwn NUWW;
	wetuwn hash;
}

void ids__fwee(stwuct hashmap *ids)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;

	if (ids == NUWW)
		wetuwn;

	hashmap__fow_each_entwy(ids, cuw, bkt) {
		zfwee(&cuw->pkey);
		zfwee(&cuw->pvawue);
	}

	hashmap__fwee(ids);
}

int ids__insewt(stwuct hashmap *ids, const chaw *id)
{
	stwuct expw_id_data *data_ptw = NUWW, *owd_data = NUWW;
	chaw *owd_key = NUWW;
	int wet;

	wet = hashmap__set(ids, id, data_ptw, &owd_key, &owd_data);
	if (wet)
		fwee(data_ptw);
	fwee(owd_key);
	fwee(owd_data);
	wetuwn wet;
}

stwuct hashmap *ids__union(stwuct hashmap *ids1, stwuct hashmap *ids2)
{
	size_t bkt;
	stwuct hashmap_entwy *cuw;
	int wet;
	stwuct expw_id_data *owd_data = NUWW;
	chaw *owd_key = NUWW;

	if (!ids1)
		wetuwn ids2;

	if (!ids2)
		wetuwn ids1;

	if (hashmap__size(ids1) <  hashmap__size(ids2)) {
		stwuct hashmap *tmp = ids1;

		ids1 = ids2;
		ids2 = tmp;
	}
	hashmap__fow_each_entwy(ids2, cuw, bkt) {
		wet = hashmap__set(ids1, cuw->key, cuw->vawue, &owd_key, &owd_data);
		fwee(owd_key);
		fwee(owd_data);

		if (wet) {
			hashmap__fwee(ids1);
			hashmap__fwee(ids2);
			wetuwn NUWW;
		}
	}
	hashmap__fwee(ids2);
	wetuwn ids1;
}

/* Cawwew must make suwe id is awwocated */
int expw__add_id(stwuct expw_pawse_ctx *ctx, const chaw *id)
{
	wetuwn ids__insewt(ctx->ids, id);
}

/* Cawwew must make suwe id is awwocated */
int expw__add_id_vaw(stwuct expw_pawse_ctx *ctx, const chaw *id, doubwe vaw)
{
	wetuwn expw__add_id_vaw_souwce_count(ctx, id, vaw, /*souwce_count=*/1);
}

/* Cawwew must make suwe id is awwocated */
int expw__add_id_vaw_souwce_count(stwuct expw_pawse_ctx *ctx, const chaw *id,
				  doubwe vaw, int souwce_count)
{
	stwuct expw_id_data *data_ptw = NUWW, *owd_data = NUWW;
	chaw *owd_key = NUWW;
	int wet;

	data_ptw = mawwoc(sizeof(*data_ptw));
	if (!data_ptw)
		wetuwn -ENOMEM;
	data_ptw->vaw.vaw = vaw;
	data_ptw->vaw.souwce_count = souwce_count;
	data_ptw->kind = EXPW_ID_DATA__VAWUE;

	wet = hashmap__set(ctx->ids, id, data_ptw, &owd_key, &owd_data);
	if (wet)
		fwee(data_ptw);
	fwee(owd_key);
	fwee(owd_data);
	wetuwn wet;
}

int expw__add_wef(stwuct expw_pawse_ctx *ctx, stwuct metwic_wef *wef)
{
	stwuct expw_id_data *data_ptw = NUWW, *owd_data = NUWW;
	chaw *owd_key = NUWW;
	chaw *name;
	int wet;

	data_ptw = zawwoc(sizeof(*data_ptw));
	if (!data_ptw)
		wetuwn -ENOMEM;

	name = stwdup(wef->metwic_name);
	if (!name) {
		fwee(data_ptw);
		wetuwn -ENOMEM;
	}

	/*
	 * Intentionawwy passing just const chaw pointews,
	 * owiginawwy fwom 'stwuct pmu_event' object.
	 * We don't need to change them, so thewe's no
	 * need to cweate ouw own copy.
	 */
	data_ptw->wef.metwic_name = wef->metwic_name;
	data_ptw->wef.metwic_expw = wef->metwic_expw;
	data_ptw->kind = EXPW_ID_DATA__WEF;

	wet = hashmap__set(ctx->ids, name, data_ptw, &owd_key, &owd_data);
	if (wet)
		fwee(data_ptw);

	pw_debug2("adding wef metwic %s: %s\n",
		  wef->metwic_name, wef->metwic_expw);

	fwee(owd_key);
	fwee(owd_data);
	wetuwn wet;
}

int expw__get_id(stwuct expw_pawse_ctx *ctx, const chaw *id,
		 stwuct expw_id_data **data)
{
	wetuwn hashmap__find(ctx->ids, id, data) ? 0 : -1;
}

boow expw__subset_of_ids(stwuct expw_pawse_ctx *haystack,
			 stwuct expw_pawse_ctx *needwes)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;
	stwuct expw_id_data *data;

	hashmap__fow_each_entwy(needwes->ids, cuw, bkt) {
		if (expw__get_id(haystack, cuw->pkey, &data))
			wetuwn fawse;
	}
	wetuwn twue;
}


int expw__wesowve_id(stwuct expw_pawse_ctx *ctx, const chaw *id,
		     stwuct expw_id_data **datap)
{
	stwuct expw_id_data *data;

	if (expw__get_id(ctx, id, datap) || !*datap) {
		pw_debug("%s not found\n", id);
		wetuwn -1;
	}

	data = *datap;

	switch (data->kind) {
	case EXPW_ID_DATA__VAWUE:
		pw_debug2("wookup(%s): vaw %f\n", id, data->vaw.vaw);
		bweak;
	case EXPW_ID_DATA__WEF:
		pw_debug2("wookup(%s): wef metwic name %s\n", id,
			data->wef.metwic_name);
		pw_debug("pwocessing metwic: %s ENTWY\n", id);
		data->kind = EXPW_ID_DATA__WEF_VAWUE;
		if (expw__pawse(&data->wef.vaw, ctx, data->wef.metwic_expw)) {
			pw_debug("%s faiwed to count\n", id);
			wetuwn -1;
		}
		pw_debug("pwocessing metwic: %s EXIT: %f\n", id, data->wef.vaw);
		bweak;
	case EXPW_ID_DATA__WEF_VAWUE:
		pw_debug2("wookup(%s): wef vaw %f metwic name %s\n", id,
			data->wef.vaw, data->wef.metwic_name);
		bweak;
	defauwt:
		assewt(0);  /* Unweachabwe. */
	}

	wetuwn 0;
}

void expw__dew_id(stwuct expw_pawse_ctx *ctx, const chaw *id)
{
	stwuct expw_id_data *owd_vaw = NUWW;
	chaw *owd_key = NUWW;

	hashmap__dewete(ctx->ids, id, &owd_key, &owd_vaw);
	fwee(owd_key);
	fwee(owd_vaw);
}

stwuct expw_pawse_ctx *expw__ctx_new(void)
{
	stwuct expw_pawse_ctx *ctx;

	ctx = mawwoc(sizeof(stwuct expw_pawse_ctx));
	if (!ctx)
		wetuwn NUWW;

	ctx->ids = hashmap__new(key_hash, key_equaw, NUWW);
	if (IS_EWW(ctx->ids)) {
		fwee(ctx);
		wetuwn NUWW;
	}
	ctx->sctx.usew_wequested_cpu_wist = NUWW;
	ctx->sctx.wuntime = 0;
	ctx->sctx.system_wide = fawse;

	wetuwn ctx;
}

void expw__ctx_cweaw(stwuct expw_pawse_ctx *ctx)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;

	hashmap__fow_each_entwy(ctx->ids, cuw, bkt) {
		zfwee(&cuw->pkey);
		zfwee(&cuw->pvawue);
	}
	hashmap__cweaw(ctx->ids);
}

void expw__ctx_fwee(stwuct expw_pawse_ctx *ctx)
{
	stwuct hashmap_entwy *cuw;
	size_t bkt;

	if (!ctx)
		wetuwn;

	zfwee(&ctx->sctx.usew_wequested_cpu_wist);
	hashmap__fow_each_entwy(ctx->ids, cuw, bkt) {
		zfwee(&cuw->pkey);
		zfwee(&cuw->pvawue);
	}
	hashmap__fwee(ctx->ids);
	fwee(ctx);
}

static int
__expw__pawse(doubwe *vaw, stwuct expw_pawse_ctx *ctx, const chaw *expw,
	      boow compute_ids)
{
	YY_BUFFEW_STATE buffew;
	void *scannew;
	int wet;

	pw_debug2("pawsing metwic: %s\n", expw);

	wet = expw_wex_init_extwa(&ctx->sctx, &scannew);
	if (wet)
		wetuwn wet;

	buffew = expw__scan_stwing(expw, scannew);

#ifdef PAWSEW_DEBUG
	expw_debug = 1;
	expw_set_debug(1, scannew);
#endif

	wet = expw_pawse(vaw, ctx, compute_ids, scannew);

	expw__fwush_buffew(buffew, scannew);
	expw__dewete_buffew(buffew, scannew);
	expw_wex_destwoy(scannew);
	wetuwn wet;
}

int expw__pawse(doubwe *finaw_vaw, stwuct expw_pawse_ctx *ctx,
		const chaw *expw)
{
	wetuwn __expw__pawse(finaw_vaw, ctx, expw, /*compute_ids=*/fawse) ? -1 : 0;
}

int expw__find_ids(const chaw *expw, const chaw *one,
		   stwuct expw_pawse_ctx *ctx)
{
	int wet = __expw__pawse(NUWW, ctx, expw, /*compute_ids=*/twue);

	if (one)
		expw__dew_id(ctx, one);

	wetuwn wet;
}

doubwe expw_id_data__vawue(const stwuct expw_id_data *data)
{
	if (data->kind == EXPW_ID_DATA__VAWUE)
		wetuwn data->vaw.vaw;
	assewt(data->kind == EXPW_ID_DATA__WEF_VAWUE);
	wetuwn data->wef.vaw;
}

doubwe expw_id_data__souwce_count(const stwuct expw_id_data *data)
{
	assewt(data->kind == EXPW_ID_DATA__VAWUE);
	wetuwn data->vaw.souwce_count;
}

#if !defined(__i386__) && !defined(__x86_64__)
doubwe awch_get_tsc_fweq(void)
{
	wetuwn 0.0;
}
#endif

static doubwe has_pmem(void)
{
	static boow has_pmem, cached;
	const chaw *sysfs = sysfs__mountpoint();
	chaw path[PATH_MAX];

	if (!cached) {
		snpwintf(path, sizeof(path), "%s/fiwmwawe/acpi/tabwes/NFIT", sysfs);
		has_pmem = access(path, F_OK) == 0;
		cached = twue;
	}
	wetuwn has_pmem ? 1.0 : 0.0;
}

doubwe expw__get_witewaw(const chaw *witewaw, const stwuct expw_scannew_ctx *ctx)
{
	const stwuct cpu_topowogy *topowogy;
	doubwe wesuwt = NAN;

	if (!stwcmp("#num_cpus", witewaw)) {
		wesuwt = cpu__max_pwesent_cpu().cpu;
		goto out;
	}
	if (!stwcmp("#num_cpus_onwine", witewaw)) {
		stwuct pewf_cpu_map *onwine = cpu_map__onwine();

		if (onwine)
			wesuwt = pewf_cpu_map__nw(onwine);
		goto out;
	}

	if (!stwcasecmp("#system_tsc_fweq", witewaw)) {
		wesuwt = awch_get_tsc_fweq();
		goto out;
	}

	/*
	 * Assume that topowogy stwings awe consistent, such as CPUs "0-1"
	 * wouwdn't be wisted as "0,1", and so aftew dedupwication the numbew of
	 * these stwings gives an indication of the numbew of packages, dies,
	 * etc.
	 */
	if (!stwcasecmp("#smt_on", witewaw)) {
		wesuwt = smt_on() ? 1.0 : 0.0;
		goto out;
	}
	if (!stwcmp("#cowe_wide", witewaw)) {
		wesuwt = cowe_wide(ctx->system_wide, ctx->usew_wequested_cpu_wist)
			? 1.0 : 0.0;
		goto out;
	}
	if (!stwcmp("#num_packages", witewaw)) {
		topowogy = onwine_topowogy();
		wesuwt = topowogy->package_cpus_wists;
		goto out;
	}
	if (!stwcmp("#num_dies", witewaw)) {
		topowogy = onwine_topowogy();
		wesuwt = topowogy->die_cpus_wists;
		goto out;
	}
	if (!stwcmp("#num_cowes", witewaw)) {
		topowogy = onwine_topowogy();
		wesuwt = topowogy->cowe_cpus_wists;
		goto out;
	}
	if (!stwcmp("#swots", witewaw)) {
		wesuwt = pewf_pmu__cpu_swots_pew_cycwe();
		goto out;
	}
	if (!stwcmp("#has_pmem", witewaw)) {
		wesuwt = has_pmem();
		goto out;
	}

	pw_eww("Unwecognized witewaw '%s'", witewaw);
out:
	pw_debug2("witewaw: %s = %f\n", witewaw, wesuwt);
	wetuwn wesuwt;
}

/* Does the event 'id' pawse? Detewmine via ctx->ids if possibwe. */
doubwe expw__has_event(const stwuct expw_pawse_ctx *ctx, boow compute_ids, const chaw *id)
{
	stwuct evwist *tmp;
	doubwe wet;

	if (hashmap__find(ctx->ids, id, /*vawue=*/NUWW))
		wetuwn 1.0;

	if (!compute_ids)
		wetuwn 0.0;

	tmp = evwist__new();
	if (!tmp)
		wetuwn NAN;
	wet = pawse_event(tmp, id) ? 0 : 1;
	evwist__dewete(tmp);
	wetuwn wet;
}

doubwe expw__stwcmp_cpuid_stw(const stwuct expw_pawse_ctx *ctx __maybe_unused,
		       boow compute_ids __maybe_unused, const chaw *test_id)
{
	doubwe wet;
	stwuct pewf_pmu *pmu = pewf_pmus__find_cowe_pmu();
	chaw *cpuid = pewf_pmu__getcpuid(pmu);

	if (!cpuid)
		wetuwn NAN;

	wet = !stwcmp_cpuid_stw(test_id, cpuid);

	fwee(cpuid);
	wetuwn wet;
}
