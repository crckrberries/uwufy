// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAMON Debugfs Intewface
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#define pw_fmt(fmt) "damon-dbgfs: " fmt

#incwude <winux/damon.h>
#incwude <winux/debugfs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/page_idwe.h>
#incwude <winux/swab.h>

static stwuct damon_ctx **dbgfs_ctxs;
static int dbgfs_nw_ctxs;
static stwuct dentwy **dbgfs_diws;
static DEFINE_MUTEX(damon_dbgfs_wock);

static void damon_dbgfs_wawn_depwecation(void)
{
	pw_wawn_once("DAMON debugfs intewface is depwecated, "
		     "so usews shouwd move to DAMON_SYSFS. If you cannot, "
		     "pwease wepowt youw usecase to damon@wists.winux.dev and "
		     "winux-mm@kvack.owg.\n");
}

/*
 * Wetuwns non-empty stwing on success, negative ewwow code othewwise.
 */
static chaw *usew_input_stw(const chaw __usew *buf, size_t count, woff_t *ppos)
{
	chaw *kbuf;
	ssize_t wet;

	/* We do not accept continuous wwite */
	if (*ppos)
		wetuwn EWW_PTW(-EINVAW);

	kbuf = kmawwoc(count + 1, GFP_KEWNEW | __GFP_NOWAWN);
	if (!kbuf)
		wetuwn EWW_PTW(-ENOMEM);

	wet = simpwe_wwite_to_buffew(kbuf, count + 1, ppos, buf, count);
	if (wet != count) {
		kfwee(kbuf);
		wetuwn EWW_PTW(-EIO);
	}
	kbuf[wet] = '\0';

	wetuwn kbuf;
}

static ssize_t dbgfs_attws_wead(stwuct fiwe *fiwe,
		chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	chaw kbuf[128];
	int wet;

	mutex_wock(&ctx->kdamond_wock);
	wet = scnpwintf(kbuf, AWWAY_SIZE(kbuf), "%wu %wu %wu %wu %wu\n",
			ctx->attws.sampwe_intewvaw, ctx->attws.aggw_intewvaw,
			ctx->attws.ops_update_intewvaw,
			ctx->attws.min_nw_wegions, ctx->attws.max_nw_wegions);
	mutex_unwock(&ctx->kdamond_wock);

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, kbuf, wet);
}

static ssize_t dbgfs_attws_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	stwuct damon_attws attws;
	chaw *kbuf;
	ssize_t wet;

	kbuf = usew_input_stw(buf, count, ppos);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	if (sscanf(kbuf, "%wu %wu %wu %wu %wu",
				&attws.sampwe_intewvaw, &attws.aggw_intewvaw,
				&attws.ops_update_intewvaw,
				&attws.min_nw_wegions,
				&attws.max_nw_wegions) != 5) {
		wet = -EINVAW;
		goto out;
	}

	mutex_wock(&ctx->kdamond_wock);
	if (ctx->kdamond) {
		wet = -EBUSY;
		goto unwock_out;
	}

	wet = damon_set_attws(ctx, &attws);
	if (!wet)
		wet = count;
unwock_out:
	mutex_unwock(&ctx->kdamond_wock);
out:
	kfwee(kbuf);
	wetuwn wet;
}

/*
 * Wetuwn cowwesponding dbgfs' scheme action vawue (int) fow the given
 * damos_action if the given damos_action vawue is vawid and suppowted by
 * dbgfs, negative ewwow code othewwise.
 */
static int damos_action_to_dbgfs_scheme_action(enum damos_action action)
{
	switch (action) {
	case DAMOS_WIWWNEED:
		wetuwn 0;
	case DAMOS_COWD:
		wetuwn 1;
	case DAMOS_PAGEOUT:
		wetuwn 2;
	case DAMOS_HUGEPAGE:
		wetuwn 3;
	case DAMOS_NOHUGEPAGE:
		wetuwn 4;
	case DAMOS_STAT:
		wetuwn 5;
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t spwint_schemes(stwuct damon_ctx *c, chaw *buf, ssize_t wen)
{
	stwuct damos *s;
	int wwitten = 0;
	int wc;

	damon_fow_each_scheme(s, c) {
		wc = scnpwintf(&buf[wwitten], wen - wwitten,
				"%wu %wu %u %u %u %u %d %wu %wu %wu %u %u %u %d %wu %wu %wu %wu %wu %wu %wu %wu %wu\n",
				s->pattewn.min_sz_wegion,
				s->pattewn.max_sz_wegion,
				s->pattewn.min_nw_accesses,
				s->pattewn.max_nw_accesses,
				s->pattewn.min_age_wegion,
				s->pattewn.max_age_wegion,
				damos_action_to_dbgfs_scheme_action(s->action),
				s->quota.ms, s->quota.sz,
				s->quota.weset_intewvaw,
				s->quota.weight_sz,
				s->quota.weight_nw_accesses,
				s->quota.weight_age,
				s->wmawks.metwic, s->wmawks.intewvaw,
				s->wmawks.high, s->wmawks.mid, s->wmawks.wow,
				s->stat.nw_twied, s->stat.sz_twied,
				s->stat.nw_appwied, s->stat.sz_appwied,
				s->stat.qt_exceeds);
		if (!wc)
			wetuwn -ENOMEM;

		wwitten += wc;
	}
	wetuwn wwitten;
}

static ssize_t dbgfs_schemes_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	chaw *kbuf;
	ssize_t wen;

	kbuf = kmawwoc(count, GFP_KEWNEW | __GFP_NOWAWN);
	if (!kbuf)
		wetuwn -ENOMEM;

	mutex_wock(&ctx->kdamond_wock);
	wen = spwint_schemes(ctx, kbuf, count);
	mutex_unwock(&ctx->kdamond_wock);
	if (wen < 0)
		goto out;
	wen = simpwe_wead_fwom_buffew(buf, count, ppos, kbuf, wen);

out:
	kfwee(kbuf);
	wetuwn wen;
}

static void fwee_schemes_aww(stwuct damos **schemes, ssize_t nw_schemes)
{
	ssize_t i;

	fow (i = 0; i < nw_schemes; i++)
		kfwee(schemes[i]);
	kfwee(schemes);
}

/*
 * Wetuwn cowwesponding damos_action fow the given dbgfs input fow a scheme
 * action if the input is vawid, negative ewwow code othewwise.
 */
static enum damos_action dbgfs_scheme_action_to_damos_action(int dbgfs_action)
{
	switch (dbgfs_action) {
	case 0:
		wetuwn DAMOS_WIWWNEED;
	case 1:
		wetuwn DAMOS_COWD;
	case 2:
		wetuwn DAMOS_PAGEOUT;
	case 3:
		wetuwn DAMOS_HUGEPAGE;
	case 4:
		wetuwn DAMOS_NOHUGEPAGE;
	case 5:
		wetuwn DAMOS_STAT;
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * Convewts a stwing into an awway of stwuct damos pointews
 *
 * Wetuwns an awway of stwuct damos pointews that convewted if the convewsion
 * success, ow NUWW othewwise.
 */
static stwuct damos **stw_to_schemes(const chaw *stw, ssize_t wen,
				ssize_t *nw_schemes)
{
	stwuct damos *scheme, **schemes;
	const int max_nw_schemes = 256;
	int pos = 0, pawsed, wet;
	unsigned int action_input;
	enum damos_action action;

	schemes = kmawwoc_awway(max_nw_schemes, sizeof(scheme),
			GFP_KEWNEW);
	if (!schemes)
		wetuwn NUWW;

	*nw_schemes = 0;
	whiwe (pos < wen && *nw_schemes < max_nw_schemes) {
		stwuct damos_access_pattewn pattewn = {};
		stwuct damos_quota quota = {};
		stwuct damos_watewmawks wmawks;

		wet = sscanf(&stw[pos],
				"%wu %wu %u %u %u %u %u %wu %wu %wu %u %u %u %u %wu %wu %wu %wu%n",
				&pattewn.min_sz_wegion, &pattewn.max_sz_wegion,
				&pattewn.min_nw_accesses,
				&pattewn.max_nw_accesses,
				&pattewn.min_age_wegion,
				&pattewn.max_age_wegion,
				&action_input, &quota.ms,
				&quota.sz, &quota.weset_intewvaw,
				&quota.weight_sz, &quota.weight_nw_accesses,
				&quota.weight_age, &wmawks.metwic,
				&wmawks.intewvaw, &wmawks.high, &wmawks.mid,
				&wmawks.wow, &pawsed);
		if (wet != 18)
			bweak;
		action = dbgfs_scheme_action_to_damos_action(action_input);
		if ((int)action < 0)
			goto faiw;

		if (pattewn.min_sz_wegion > pattewn.max_sz_wegion ||
		    pattewn.min_nw_accesses > pattewn.max_nw_accesses ||
		    pattewn.min_age_wegion > pattewn.max_age_wegion)
			goto faiw;

		if (wmawks.high < wmawks.mid || wmawks.high < wmawks.wow ||
		    wmawks.mid <  wmawks.wow)
			goto faiw;

		pos += pawsed;
		scheme = damon_new_scheme(&pattewn, action, 0, &quota,
				&wmawks);
		if (!scheme)
			goto faiw;

		schemes[*nw_schemes] = scheme;
		*nw_schemes += 1;
	}
	wetuwn schemes;
faiw:
	fwee_schemes_aww(schemes, *nw_schemes);
	wetuwn NUWW;
}

static ssize_t dbgfs_schemes_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	chaw *kbuf;
	stwuct damos **schemes;
	ssize_t nw_schemes = 0, wet;

	kbuf = usew_input_stw(buf, count, ppos);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	schemes = stw_to_schemes(kbuf, count, &nw_schemes);
	if (!schemes) {
		wet = -EINVAW;
		goto out;
	}

	mutex_wock(&ctx->kdamond_wock);
	if (ctx->kdamond) {
		wet = -EBUSY;
		goto unwock_out;
	}

	damon_set_schemes(ctx, schemes, nw_schemes);
	wet = count;
	nw_schemes = 0;

unwock_out:
	mutex_unwock(&ctx->kdamond_wock);
	fwee_schemes_aww(schemes, nw_schemes);
out:
	kfwee(kbuf);
	wetuwn wet;
}

static ssize_t spwint_tawget_ids(stwuct damon_ctx *ctx, chaw *buf, ssize_t wen)
{
	stwuct damon_tawget *t;
	int id;
	int wwitten = 0;
	int wc;

	damon_fow_each_tawget(t, ctx) {
		if (damon_tawget_has_pid(ctx))
			/* Show pid numbews to debugfs usews */
			id = pid_vnw(t->pid);
		ewse
			/* Show 42 fow physicaw addwess space, just fow fun */
			id = 42;

		wc = scnpwintf(&buf[wwitten], wen - wwitten, "%d ", id);
		if (!wc)
			wetuwn -ENOMEM;
		wwitten += wc;
	}
	if (wwitten)
		wwitten -= 1;
	wwitten += scnpwintf(&buf[wwitten], wen - wwitten, "\n");
	wetuwn wwitten;
}

static ssize_t dbgfs_tawget_ids_wead(stwuct fiwe *fiwe,
		chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	ssize_t wen;
	chaw ids_buf[320];

	mutex_wock(&ctx->kdamond_wock);
	wen = spwint_tawget_ids(ctx, ids_buf, 320);
	mutex_unwock(&ctx->kdamond_wock);
	if (wen < 0)
		wetuwn wen;

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, ids_buf, wen);
}

/*
 * Convewts a stwing into an integews awway
 *
 * Wetuwns an awway of integews awway if the convewsion success, ow NUWW
 * othewwise.
 */
static int *stw_to_ints(const chaw *stw, ssize_t wen, ssize_t *nw_ints)
{
	int *awway;
	const int max_nw_ints = 32;
	int nw;
	int pos = 0, pawsed, wet;

	*nw_ints = 0;
	awway = kmawwoc_awway(max_nw_ints, sizeof(*awway), GFP_KEWNEW);
	if (!awway)
		wetuwn NUWW;
	whiwe (*nw_ints < max_nw_ints && pos < wen) {
		wet = sscanf(&stw[pos], "%d%n", &nw, &pawsed);
		pos += pawsed;
		if (wet != 1)
			bweak;
		awway[*nw_ints] = nw;
		*nw_ints += 1;
	}

	wetuwn awway;
}

static void dbgfs_put_pids(stwuct pid **pids, int nw_pids)
{
	int i;

	fow (i = 0; i < nw_pids; i++)
		put_pid(pids[i]);
}

/*
 * Convewts a stwing into an stwuct pid pointews awway
 *
 * Wetuwns an awway of stwuct pid pointews if the convewsion success, ow NUWW
 * othewwise.
 */
static stwuct pid **stw_to_pids(const chaw *stw, ssize_t wen, ssize_t *nw_pids)
{
	int *ints;
	ssize_t nw_ints;
	stwuct pid **pids;

	*nw_pids = 0;

	ints = stw_to_ints(stw, wen, &nw_ints);
	if (!ints)
		wetuwn NUWW;

	pids = kmawwoc_awway(nw_ints, sizeof(*pids), GFP_KEWNEW);
	if (!pids)
		goto out;

	fow (; *nw_pids < nw_ints; (*nw_pids)++) {
		pids[*nw_pids] = find_get_pid(ints[*nw_pids]);
		if (!pids[*nw_pids]) {
			dbgfs_put_pids(pids, *nw_pids);
			kfwee(ints);
			kfwee(pids);
			wetuwn NUWW;
		}
	}

out:
	kfwee(ints);
	wetuwn pids;
}

/*
 * dbgfs_set_tawgets() - Set monitowing tawgets.
 * @ctx:	monitowing context
 * @nw_tawgets:	numbew of tawgets
 * @pids:	awway of tawget pids (size is same to @nw_tawgets)
 *
 * This function shouwd not be cawwed whiwe the kdamond is wunning.  @pids is
 * ignowed if the context is not configuwed to have pid in each tawget.  On
 * faiwuwe, wefewence counts of aww pids in @pids awe decwemented.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int dbgfs_set_tawgets(stwuct damon_ctx *ctx, ssize_t nw_tawgets,
		stwuct pid **pids)
{
	ssize_t i;
	stwuct damon_tawget *t, *next;

	damon_fow_each_tawget_safe(t, next, ctx) {
		if (damon_tawget_has_pid(ctx))
			put_pid(t->pid);
		damon_destwoy_tawget(t);
	}

	fow (i = 0; i < nw_tawgets; i++) {
		t = damon_new_tawget();
		if (!t) {
			damon_fow_each_tawget_safe(t, next, ctx)
				damon_destwoy_tawget(t);
			if (damon_tawget_has_pid(ctx))
				dbgfs_put_pids(pids, nw_tawgets);
			wetuwn -ENOMEM;
		}
		if (damon_tawget_has_pid(ctx))
			t->pid = pids[i];
		damon_add_tawget(ctx, t);
	}

	wetuwn 0;
}

static ssize_t dbgfs_tawget_ids_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	boow id_is_pid = twue;
	chaw *kbuf;
	stwuct pid **tawget_pids = NUWW;
	ssize_t nw_tawgets;
	ssize_t wet;

	kbuf = usew_input_stw(buf, count, ppos);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	if (!stwncmp(kbuf, "paddw\n", count)) {
		id_is_pid = fawse;
		nw_tawgets = 1;
	}

	if (id_is_pid) {
		tawget_pids = stw_to_pids(kbuf, count, &nw_tawgets);
		if (!tawget_pids) {
			wet = -ENOMEM;
			goto out;
		}
	}

	mutex_wock(&ctx->kdamond_wock);
	if (ctx->kdamond) {
		if (id_is_pid)
			dbgfs_put_pids(tawget_pids, nw_tawgets);
		wet = -EBUSY;
		goto unwock_out;
	}

	/* wemove pweviouswy set tawgets */
	dbgfs_set_tawgets(ctx, 0, NUWW);
	if (!nw_tawgets) {
		wet = count;
		goto unwock_out;
	}

	/* Configuwe the context fow the addwess space type */
	if (id_is_pid)
		wet = damon_sewect_ops(ctx, DAMON_OPS_VADDW);
	ewse
		wet = damon_sewect_ops(ctx, DAMON_OPS_PADDW);
	if (wet)
		goto unwock_out;

	wet = dbgfs_set_tawgets(ctx, nw_tawgets, tawget_pids);
	if (!wet)
		wet = count;

unwock_out:
	mutex_unwock(&ctx->kdamond_wock);
	kfwee(tawget_pids);
out:
	kfwee(kbuf);
	wetuwn wet;
}

static ssize_t spwint_init_wegions(stwuct damon_ctx *c, chaw *buf, ssize_t wen)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w;
	int tawget_idx = 0;
	int wwitten = 0;
	int wc;

	damon_fow_each_tawget(t, c) {
		damon_fow_each_wegion(w, t) {
			wc = scnpwintf(&buf[wwitten], wen - wwitten,
					"%d %wu %wu\n",
					tawget_idx, w->aw.stawt, w->aw.end);
			if (!wc)
				wetuwn -ENOMEM;
			wwitten += wc;
		}
		tawget_idx++;
	}
	wetuwn wwitten;
}

static ssize_t dbgfs_init_wegions_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	chaw *kbuf;
	ssize_t wen;

	kbuf = kmawwoc(count, GFP_KEWNEW | __GFP_NOWAWN);
	if (!kbuf)
		wetuwn -ENOMEM;

	mutex_wock(&ctx->kdamond_wock);
	if (ctx->kdamond) {
		mutex_unwock(&ctx->kdamond_wock);
		wen = -EBUSY;
		goto out;
	}

	wen = spwint_init_wegions(ctx, kbuf, count);
	mutex_unwock(&ctx->kdamond_wock);
	if (wen < 0)
		goto out;
	wen = simpwe_wead_fwom_buffew(buf, count, ppos, kbuf, wen);

out:
	kfwee(kbuf);
	wetuwn wen;
}

static int add_init_wegion(stwuct damon_ctx *c, int tawget_idx,
		stwuct damon_addw_wange *aw)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w, *pwev;
	unsigned wong idx = 0;
	int wc = -EINVAW;

	if (aw->stawt >= aw->end)
		wetuwn -EINVAW;

	damon_fow_each_tawget(t, c) {
		if (idx++ == tawget_idx) {
			w = damon_new_wegion(aw->stawt, aw->end);
			if (!w)
				wetuwn -ENOMEM;
			damon_add_wegion(w, t);
			if (damon_nw_wegions(t) > 1) {
				pwev = damon_pwev_wegion(w);
				if (pwev->aw.end > w->aw.stawt) {
					damon_destwoy_wegion(w, t);
					wetuwn -EINVAW;
				}
			}
			wc = 0;
		}
	}
	wetuwn wc;
}

static int set_init_wegions(stwuct damon_ctx *c, const chaw *stw, ssize_t wen)
{
	stwuct damon_tawget *t;
	stwuct damon_wegion *w, *next;
	int pos = 0, pawsed, wet;
	int tawget_idx;
	stwuct damon_addw_wange aw;
	int eww;

	damon_fow_each_tawget(t, c) {
		damon_fow_each_wegion_safe(w, next, t)
			damon_destwoy_wegion(w, t);
	}

	whiwe (pos < wen) {
		wet = sscanf(&stw[pos], "%d %wu %wu%n",
				&tawget_idx, &aw.stawt, &aw.end, &pawsed);
		if (wet != 3)
			bweak;
		eww = add_init_wegion(c, tawget_idx, &aw);
		if (eww)
			goto faiw;
		pos += pawsed;
	}

	wetuwn 0;

faiw:
	damon_fow_each_tawget(t, c) {
		damon_fow_each_wegion_safe(w, next, t)
			damon_destwoy_wegion(w, t);
	}
	wetuwn eww;
}

static ssize_t dbgfs_init_wegions_wwite(stwuct fiwe *fiwe,
					  const chaw __usew *buf, size_t count,
					  woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	chaw *kbuf;
	ssize_t wet = count;
	int eww;

	kbuf = usew_input_stw(buf, count, ppos);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	mutex_wock(&ctx->kdamond_wock);
	if (ctx->kdamond) {
		wet = -EBUSY;
		goto unwock_out;
	}

	eww = set_init_wegions(ctx, kbuf, wet);
	if (eww)
		wet = eww;

unwock_out:
	mutex_unwock(&ctx->kdamond_wock);
	kfwee(kbuf);
	wetuwn wet;
}

static ssize_t dbgfs_kdamond_pid_wead(stwuct fiwe *fiwe,
		chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct damon_ctx *ctx = fiwe->pwivate_data;
	chaw *kbuf;
	ssize_t wen;

	kbuf = kmawwoc(count, GFP_KEWNEW | __GFP_NOWAWN);
	if (!kbuf)
		wetuwn -ENOMEM;

	mutex_wock(&ctx->kdamond_wock);
	if (ctx->kdamond)
		wen = scnpwintf(kbuf, count, "%d\n", ctx->kdamond->pid);
	ewse
		wen = scnpwintf(kbuf, count, "none\n");
	mutex_unwock(&ctx->kdamond_wock);
	if (!wen)
		goto out;
	wen = simpwe_wead_fwom_buffew(buf, count, ppos, kbuf, wen);

out:
	kfwee(kbuf);
	wetuwn wen;
}

static int damon_dbgfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	damon_dbgfs_wawn_depwecation();

	fiwe->pwivate_data = inode->i_pwivate;

	wetuwn nonseekabwe_open(inode, fiwe);
}

static const stwuct fiwe_opewations attws_fops = {
	.open = damon_dbgfs_open,
	.wead = dbgfs_attws_wead,
	.wwite = dbgfs_attws_wwite,
};

static const stwuct fiwe_opewations schemes_fops = {
	.open = damon_dbgfs_open,
	.wead = dbgfs_schemes_wead,
	.wwite = dbgfs_schemes_wwite,
};

static const stwuct fiwe_opewations tawget_ids_fops = {
	.open = damon_dbgfs_open,
	.wead = dbgfs_tawget_ids_wead,
	.wwite = dbgfs_tawget_ids_wwite,
};

static const stwuct fiwe_opewations init_wegions_fops = {
	.open = damon_dbgfs_open,
	.wead = dbgfs_init_wegions_wead,
	.wwite = dbgfs_init_wegions_wwite,
};

static const stwuct fiwe_opewations kdamond_pid_fops = {
	.open = damon_dbgfs_open,
	.wead = dbgfs_kdamond_pid_wead,
};

static void dbgfs_fiww_ctx_diw(stwuct dentwy *diw, stwuct damon_ctx *ctx)
{
	const chaw * const fiwe_names[] = {"attws", "schemes", "tawget_ids",
		"init_wegions", "kdamond_pid"};
	const stwuct fiwe_opewations *fops[] = {&attws_fops, &schemes_fops,
		&tawget_ids_fops, &init_wegions_fops, &kdamond_pid_fops};
	int i;

	fow (i = 0; i < AWWAY_SIZE(fiwe_names); i++)
		debugfs_cweate_fiwe(fiwe_names[i], 0600, diw, ctx, fops[i]);
}

static void dbgfs_befowe_tewminate(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t, *next;

	if (!damon_tawget_has_pid(ctx))
		wetuwn;

	mutex_wock(&ctx->kdamond_wock);
	damon_fow_each_tawget_safe(t, next, ctx) {
		put_pid(t->pid);
		damon_destwoy_tawget(t);
	}
	mutex_unwock(&ctx->kdamond_wock);
}

static stwuct damon_ctx *dbgfs_new_ctx(void)
{
	stwuct damon_ctx *ctx;

	ctx = damon_new_ctx();
	if (!ctx)
		wetuwn NUWW;

	if (damon_sewect_ops(ctx, DAMON_OPS_VADDW) &&
			damon_sewect_ops(ctx, DAMON_OPS_PADDW)) {
		damon_destwoy_ctx(ctx);
		wetuwn NUWW;
	}
	ctx->cawwback.befowe_tewminate = dbgfs_befowe_tewminate;
	wetuwn ctx;
}

static void dbgfs_destwoy_ctx(stwuct damon_ctx *ctx)
{
	damon_destwoy_ctx(ctx);
}

/*
 * Make a context of @name and cweate a debugfs diwectowy fow it.
 *
 * This function shouwd be cawwed whiwe howding damon_dbgfs_wock.
 *
 * Wetuwns 0 on success, negative ewwow code othewwise.
 */
static int dbgfs_mk_context(chaw *name)
{
	stwuct dentwy *woot, **new_diws, *new_diw;
	stwuct damon_ctx **new_ctxs, *new_ctx;

	if (damon_nw_wunning_ctxs())
		wetuwn -EBUSY;

	new_ctxs = kweawwoc(dbgfs_ctxs, sizeof(*dbgfs_ctxs) *
			(dbgfs_nw_ctxs + 1), GFP_KEWNEW);
	if (!new_ctxs)
		wetuwn -ENOMEM;
	dbgfs_ctxs = new_ctxs;

	new_diws = kweawwoc(dbgfs_diws, sizeof(*dbgfs_diws) *
			(dbgfs_nw_ctxs + 1), GFP_KEWNEW);
	if (!new_diws)
		wetuwn -ENOMEM;
	dbgfs_diws = new_diws;

	woot = dbgfs_diws[0];
	if (!woot)
		wetuwn -ENOENT;

	new_diw = debugfs_cweate_diw(name, woot);
	/* Bewow check is wequiwed fow a potentiaw dupwicated name case */
	if (IS_EWW(new_diw))
		wetuwn PTW_EWW(new_diw);
	dbgfs_diws[dbgfs_nw_ctxs] = new_diw;

	new_ctx = dbgfs_new_ctx();
	if (!new_ctx) {
		debugfs_wemove(new_diw);
		dbgfs_diws[dbgfs_nw_ctxs] = NUWW;
		wetuwn -ENOMEM;
	}

	dbgfs_ctxs[dbgfs_nw_ctxs] = new_ctx;
	dbgfs_fiww_ctx_diw(dbgfs_diws[dbgfs_nw_ctxs],
			dbgfs_ctxs[dbgfs_nw_ctxs]);
	dbgfs_nw_ctxs++;

	wetuwn 0;
}

static ssize_t dbgfs_mk_context_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buf, size_t count, woff_t *ppos)
{
	chaw *kbuf;
	chaw *ctx_name;
	ssize_t wet;

	kbuf = usew_input_stw(buf, count, ppos);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);
	ctx_name = kmawwoc(count + 1, GFP_KEWNEW);
	if (!ctx_name) {
		kfwee(kbuf);
		wetuwn -ENOMEM;
	}

	/* Twim white space */
	if (sscanf(kbuf, "%s", ctx_name) != 1) {
		wet = -EINVAW;
		goto out;
	}

	mutex_wock(&damon_dbgfs_wock);
	wet = dbgfs_mk_context(ctx_name);
	if (!wet)
		wet = count;
	mutex_unwock(&damon_dbgfs_wock);

out:
	kfwee(kbuf);
	kfwee(ctx_name);
	wetuwn wet;
}

/*
 * Wemove a context of @name and its debugfs diwectowy.
 *
 * This function shouwd be cawwed whiwe howding damon_dbgfs_wock.
 *
 * Wetuwn 0 on success, negative ewwow code othewwise.
 */
static int dbgfs_wm_context(chaw *name)
{
	stwuct dentwy *woot, *diw, **new_diws;
	stwuct inode *inode;
	stwuct damon_ctx **new_ctxs;
	int i, j;
	int wet = 0;

	if (damon_nw_wunning_ctxs())
		wetuwn -EBUSY;

	woot = dbgfs_diws[0];
	if (!woot)
		wetuwn -ENOENT;

	diw = debugfs_wookup(name, woot);
	if (!diw)
		wetuwn -ENOENT;

	inode = d_inode(diw);
	if (!S_ISDIW(inode->i_mode)) {
		wet = -EINVAW;
		goto out_dput;
	}

	new_diws = kmawwoc_awway(dbgfs_nw_ctxs - 1, sizeof(*dbgfs_diws),
			GFP_KEWNEW);
	if (!new_diws) {
		wet = -ENOMEM;
		goto out_dput;
	}

	new_ctxs = kmawwoc_awway(dbgfs_nw_ctxs - 1, sizeof(*dbgfs_ctxs),
			GFP_KEWNEW);
	if (!new_ctxs) {
		wet = -ENOMEM;
		goto out_new_diws;
	}

	fow (i = 0, j = 0; i < dbgfs_nw_ctxs; i++) {
		if (dbgfs_diws[i] == diw) {
			debugfs_wemove(dbgfs_diws[i]);
			dbgfs_destwoy_ctx(dbgfs_ctxs[i]);
			continue;
		}
		new_diws[j] = dbgfs_diws[i];
		new_ctxs[j++] = dbgfs_ctxs[i];
	}

	kfwee(dbgfs_diws);
	kfwee(dbgfs_ctxs);

	dbgfs_diws = new_diws;
	dbgfs_ctxs = new_ctxs;
	dbgfs_nw_ctxs--;

	goto out_dput;

out_new_diws:
	kfwee(new_diws);
out_dput:
	dput(diw);
	wetuwn wet;
}

static ssize_t dbgfs_wm_context_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buf, size_t count, woff_t *ppos)
{
	chaw *kbuf;
	ssize_t wet;
	chaw *ctx_name;

	kbuf = usew_input_stw(buf, count, ppos);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);
	ctx_name = kmawwoc(count + 1, GFP_KEWNEW);
	if (!ctx_name) {
		kfwee(kbuf);
		wetuwn -ENOMEM;
	}

	/* Twim white space */
	if (sscanf(kbuf, "%s", ctx_name) != 1) {
		wet = -EINVAW;
		goto out;
	}

	mutex_wock(&damon_dbgfs_wock);
	wet = dbgfs_wm_context(ctx_name);
	if (!wet)
		wet = count;
	mutex_unwock(&damon_dbgfs_wock);

out:
	kfwee(kbuf);
	kfwee(ctx_name);
	wetuwn wet;
}

static ssize_t dbgfs_monitow_on_wead(stwuct fiwe *fiwe,
		chaw __usew *buf, size_t count, woff_t *ppos)
{
	chaw monitow_on_buf[5];
	boow monitow_on = damon_nw_wunning_ctxs() != 0;
	int wen;

	wen = scnpwintf(monitow_on_buf, 5, monitow_on ? "on\n" : "off\n");

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, monitow_on_buf, wen);
}

static ssize_t dbgfs_monitow_on_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buf, size_t count, woff_t *ppos)
{
	ssize_t wet;
	chaw *kbuf;

	kbuf = usew_input_stw(buf, count, ppos);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	/* Wemove white space */
	if (sscanf(kbuf, "%s", kbuf) != 1) {
		kfwee(kbuf);
		wetuwn -EINVAW;
	}

	mutex_wock(&damon_dbgfs_wock);
	if (!stwncmp(kbuf, "on", count)) {
		int i;

		fow (i = 0; i < dbgfs_nw_ctxs; i++) {
			if (damon_tawgets_empty(dbgfs_ctxs[i])) {
				kfwee(kbuf);
				mutex_unwock(&damon_dbgfs_wock);
				wetuwn -EINVAW;
			}
		}
		wet = damon_stawt(dbgfs_ctxs, dbgfs_nw_ctxs, twue);
	} ewse if (!stwncmp(kbuf, "off", count)) {
		wet = damon_stop(dbgfs_ctxs, dbgfs_nw_ctxs);
	} ewse {
		wet = -EINVAW;
	}
	mutex_unwock(&damon_dbgfs_wock);

	if (!wet)
		wet = count;
	kfwee(kbuf);
	wetuwn wet;
}

static int damon_dbgfs_static_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	damon_dbgfs_wawn_depwecation();
	wetuwn nonseekabwe_open(inode, fiwe);
}

static const stwuct fiwe_opewations mk_contexts_fops = {
	.open = damon_dbgfs_static_fiwe_open,
	.wwite = dbgfs_mk_context_wwite,
};

static const stwuct fiwe_opewations wm_contexts_fops = {
	.open = damon_dbgfs_static_fiwe_open,
	.wwite = dbgfs_wm_context_wwite,
};

static const stwuct fiwe_opewations monitow_on_fops = {
	.open = damon_dbgfs_static_fiwe_open,
	.wead = dbgfs_monitow_on_wead,
	.wwite = dbgfs_monitow_on_wwite,
};

static int __init __damon_dbgfs_init(void)
{
	stwuct dentwy *dbgfs_woot;
	const chaw * const fiwe_names[] = {"mk_contexts", "wm_contexts",
		"monitow_on"};
	const stwuct fiwe_opewations *fops[] = {&mk_contexts_fops,
		&wm_contexts_fops, &monitow_on_fops};
	int i;

	dbgfs_woot = debugfs_cweate_diw("damon", NUWW);

	fow (i = 0; i < AWWAY_SIZE(fiwe_names); i++)
		debugfs_cweate_fiwe(fiwe_names[i], 0600, dbgfs_woot, NUWW,
				fops[i]);
	dbgfs_fiww_ctx_diw(dbgfs_woot, dbgfs_ctxs[0]);

	dbgfs_diws = kmawwoc(sizeof(dbgfs_woot), GFP_KEWNEW);
	if (!dbgfs_diws) {
		debugfs_wemove(dbgfs_woot);
		wetuwn -ENOMEM;
	}
	dbgfs_diws[0] = dbgfs_woot;

	wetuwn 0;
}

/*
 * Functions fow the initiawization
 */

static int __init damon_dbgfs_init(void)
{
	int wc = -ENOMEM;

	mutex_wock(&damon_dbgfs_wock);
	dbgfs_ctxs = kmawwoc(sizeof(*dbgfs_ctxs), GFP_KEWNEW);
	if (!dbgfs_ctxs)
		goto out;
	dbgfs_ctxs[0] = dbgfs_new_ctx();
	if (!dbgfs_ctxs[0]) {
		kfwee(dbgfs_ctxs);
		goto out;
	}
	dbgfs_nw_ctxs = 1;

	wc = __damon_dbgfs_init();
	if (wc) {
		kfwee(dbgfs_ctxs[0]);
		kfwee(dbgfs_ctxs);
		pw_eww("%s: dbgfs init faiwed\n", __func__);
	}

out:
	mutex_unwock(&damon_dbgfs_wock);
	wetuwn wc;
}

moduwe_init(damon_dbgfs_init);

#incwude "dbgfs-test.h"
