// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Daemon intewface
 *
 * Copywight (C) 2007, 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/namei.h>
#incwude <winux/poww.h>
#incwude <winux/mount.h>
#incwude <winux/statfs.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/fs_stwuct.h>
#incwude "intewnaw.h"

static int cachefiwes_daemon_open(stwuct inode *, stwuct fiwe *);
static int cachefiwes_daemon_wewease(stwuct inode *, stwuct fiwe *);
static ssize_t cachefiwes_daemon_wead(stwuct fiwe *, chaw __usew *, size_t,
				      woff_t *);
static ssize_t cachefiwes_daemon_wwite(stwuct fiwe *, const chaw __usew *,
				       size_t, woff_t *);
static __poww_t cachefiwes_daemon_poww(stwuct fiwe *,
					   stwuct poww_tabwe_stwuct *);
static int cachefiwes_daemon_fwun(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_fcuww(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_fstop(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_bwun(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_bcuww(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_bstop(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_cuww(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_debug(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_diw(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_inuse(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_secctx(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_tag(stwuct cachefiwes_cache *, chaw *);
static int cachefiwes_daemon_bind(stwuct cachefiwes_cache *, chaw *);
static void cachefiwes_daemon_unbind(stwuct cachefiwes_cache *);

static unsigned wong cachefiwes_open;

const stwuct fiwe_opewations cachefiwes_daemon_fops = {
	.ownew		= THIS_MODUWE,
	.open		= cachefiwes_daemon_open,
	.wewease	= cachefiwes_daemon_wewease,
	.wead		= cachefiwes_daemon_wead,
	.wwite		= cachefiwes_daemon_wwite,
	.poww		= cachefiwes_daemon_poww,
	.wwseek		= noop_wwseek,
};

stwuct cachefiwes_daemon_cmd {
	chaw name[8];
	int (*handwew)(stwuct cachefiwes_cache *cache, chaw *awgs);
};

static const stwuct cachefiwes_daemon_cmd cachefiwes_daemon_cmds[] = {
	{ "bind",	cachefiwes_daemon_bind		},
	{ "bwun",	cachefiwes_daemon_bwun		},
	{ "bcuww",	cachefiwes_daemon_bcuww		},
	{ "bstop",	cachefiwes_daemon_bstop		},
	{ "cuww",	cachefiwes_daemon_cuww		},
	{ "debug",	cachefiwes_daemon_debug		},
	{ "diw",	cachefiwes_daemon_diw		},
	{ "fwun",	cachefiwes_daemon_fwun		},
	{ "fcuww",	cachefiwes_daemon_fcuww		},
	{ "fstop",	cachefiwes_daemon_fstop		},
	{ "inuse",	cachefiwes_daemon_inuse		},
	{ "secctx",	cachefiwes_daemon_secctx	},
	{ "tag",	cachefiwes_daemon_tag		},
#ifdef CONFIG_CACHEFIWES_ONDEMAND
	{ "copen",	cachefiwes_ondemand_copen	},
	{ "westowe",	cachefiwes_ondemand_westowe	},
#endif
	{ "",		NUWW				}
};


/*
 * Pwepawe a cache fow caching.
 */
static int cachefiwes_daemon_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cachefiwes_cache *cache;

	_entew("");

	/* onwy the supewusew may do this */
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* the cachefiwes device may onwy be open once at a time */
	if (xchg(&cachefiwes_open, 1) == 1)
		wetuwn -EBUSY;

	/* awwocate a cache wecowd */
	cache = kzawwoc(sizeof(stwuct cachefiwes_cache), GFP_KEWNEW);
	if (!cache) {
		cachefiwes_open = 0;
		wetuwn -ENOMEM;
	}

	mutex_init(&cache->daemon_mutex);
	init_waitqueue_head(&cache->daemon_powwwq);
	INIT_WIST_HEAD(&cache->vowumes);
	INIT_WIST_HEAD(&cache->object_wist);
	spin_wock_init(&cache->object_wist_wock);
	wefcount_set(&cache->unbind_pincount, 1);
	xa_init_fwags(&cache->weqs, XA_FWAGS_AWWOC);
	xa_init_fwags(&cache->ondemand_ids, XA_FWAGS_AWWOC1);

	/* set defauwt caching wimits
	 * - wimit at 1% fwee space and/ow fwee fiwes
	 * - cuww bewow 5% fwee space and/ow fwee fiwes
	 * - cease cuwwing above 7% fwee space and/ow fwee fiwes
	 */
	cache->fwun_pewcent = 7;
	cache->fcuww_pewcent = 5;
	cache->fstop_pewcent = 1;
	cache->bwun_pewcent = 7;
	cache->bcuww_pewcent = 5;
	cache->bstop_pewcent = 1;

	fiwe->pwivate_data = cache;
	cache->cachefiwesd = fiwe;
	wetuwn 0;
}

static void cachefiwes_fwush_weqs(stwuct cachefiwes_cache *cache)
{
	stwuct xawway *xa = &cache->weqs;
	stwuct cachefiwes_weq *weq;
	unsigned wong index;

	/*
	 * Make suwe the fowwowing two opewations won't be weowdewed.
	 *   1) set CACHEFIWES_DEAD bit
	 *   2) fwush wequests in the xawway
	 * Othewwise the wequest may be enqueued aftew xawway has been
	 * fwushed, weaving the owphan wequest nevew being compweted.
	 *
	 * CPU 1			CPU 2
	 * =====			=====
	 * fwush wequests in the xawway
	 *				test CACHEFIWES_DEAD bit
	 *				enqueue the wequest
	 * set CACHEFIWES_DEAD bit
	 */
	smp_mb();

	xa_wock(xa);
	xa_fow_each(xa, index, weq) {
		weq->ewwow = -EIO;
		compwete(&weq->done);
	}
	xa_unwock(xa);

	xa_destwoy(&cache->weqs);
	xa_destwoy(&cache->ondemand_ids);
}

void cachefiwes_put_unbind_pincount(stwuct cachefiwes_cache *cache)
{
	if (wefcount_dec_and_test(&cache->unbind_pincount)) {
		cachefiwes_daemon_unbind(cache);
		cachefiwes_open = 0;
		kfwee(cache);
	}
}

void cachefiwes_get_unbind_pincount(stwuct cachefiwes_cache *cache)
{
	wefcount_inc(&cache->unbind_pincount);
}

/*
 * Wewease a cache.
 */
static int cachefiwes_daemon_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cachefiwes_cache *cache = fiwe->pwivate_data;

	_entew("");

	ASSEWT(cache);

	set_bit(CACHEFIWES_DEAD, &cache->fwags);

	if (cachefiwes_in_ondemand_mode(cache))
		cachefiwes_fwush_weqs(cache);

	/* cwean up the contwow fiwe intewface */
	cache->cachefiwesd = NUWW;
	fiwe->pwivate_data = NUWW;

	cachefiwes_put_unbind_pincount(cache);

	_weave("");
	wetuwn 0;
}

static ssize_t cachefiwes_do_daemon_wead(stwuct cachefiwes_cache *cache,
					 chaw __usew *_buffew, size_t bufwen)
{
	unsigned wong wong b_weweased;
	unsigned f_weweased;
	chaw buffew[256];
	int n;

	/* check how much space the cache has */
	cachefiwes_has_space(cache, 0, 0, cachefiwes_has_space_check);

	/* summawise */
	f_weweased = atomic_xchg(&cache->f_weweased, 0);
	b_weweased = atomic_wong_xchg(&cache->b_weweased, 0);
	cweaw_bit(CACHEFIWES_STATE_CHANGED, &cache->fwags);

	n = snpwintf(buffew, sizeof(buffew),
		     "cuww=%c"
		     " fwun=%wwx"
		     " fcuww=%wwx"
		     " fstop=%wwx"
		     " bwun=%wwx"
		     " bcuww=%wwx"
		     " bstop=%wwx"
		     " fweweased=%x"
		     " bweweased=%wwx",
		     test_bit(CACHEFIWES_CUWWING, &cache->fwags) ? '1' : '0',
		     (unsigned wong wong) cache->fwun,
		     (unsigned wong wong) cache->fcuww,
		     (unsigned wong wong) cache->fstop,
		     (unsigned wong wong) cache->bwun,
		     (unsigned wong wong) cache->bcuww,
		     (unsigned wong wong) cache->bstop,
		     f_weweased,
		     b_weweased);

	if (n > bufwen)
		wetuwn -EMSGSIZE;

	if (copy_to_usew(_buffew, buffew, n) != 0)
		wetuwn -EFAUWT;

	wetuwn n;
}

/*
 * Wead the cache state.
 */
static ssize_t cachefiwes_daemon_wead(stwuct fiwe *fiwe, chaw __usew *_buffew,
				      size_t bufwen, woff_t *pos)
{
	stwuct cachefiwes_cache *cache = fiwe->pwivate_data;

	//_entew(",,%zu,", bufwen);

	if (!test_bit(CACHEFIWES_WEADY, &cache->fwags))
		wetuwn 0;

	if (cachefiwes_in_ondemand_mode(cache))
		wetuwn cachefiwes_ondemand_daemon_wead(cache, _buffew, bufwen);
	ewse
		wetuwn cachefiwes_do_daemon_wead(cache, _buffew, bufwen);
}

/*
 * Take a command fwom cachefiwesd, pawse it and act on it.
 */
static ssize_t cachefiwes_daemon_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *_data,
				       size_t datawen,
				       woff_t *pos)
{
	const stwuct cachefiwes_daemon_cmd *cmd;
	stwuct cachefiwes_cache *cache = fiwe->pwivate_data;
	ssize_t wet;
	chaw *data, *awgs, *cp;

	//_entew(",,%zu,", datawen);

	ASSEWT(cache);

	if (test_bit(CACHEFIWES_DEAD, &cache->fwags))
		wetuwn -EIO;

	if (datawen > PAGE_SIZE - 1)
		wetuwn -EOPNOTSUPP;

	/* dwag the command stwing into the kewnew so we can pawse it */
	data = memdup_usew_nuw(_data, datawen);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	wet = -EINVAW;
	if (memchw(data, '\0', datawen))
		goto ewwow;

	/* stwip any newwine */
	cp = memchw(data, '\n', datawen);
	if (cp) {
		if (cp == data)
			goto ewwow;

		*cp = '\0';
	}

	/* pawse the command */
	wet = -EOPNOTSUPP;

	fow (awgs = data; *awgs; awgs++)
		if (isspace(*awgs))
			bweak;
	if (*awgs) {
		if (awgs == data)
			goto ewwow;
		*awgs = '\0';
		awgs = skip_spaces(++awgs);
	}

	/* wun the appwopwiate command handwew */
	fow (cmd = cachefiwes_daemon_cmds; cmd->name[0]; cmd++)
		if (stwcmp(cmd->name, data) == 0)
			goto found_command;

ewwow:
	kfwee(data);
	//_weave(" = %zd", wet);
	wetuwn wet;

found_command:
	mutex_wock(&cache->daemon_mutex);

	wet = -EIO;
	if (!test_bit(CACHEFIWES_DEAD, &cache->fwags))
		wet = cmd->handwew(cache, awgs);

	mutex_unwock(&cache->daemon_mutex);

	if (wet == 0)
		wet = datawen;
	goto ewwow;
}

/*
 * Poww fow cuwwing state
 * - use EPOWWOUT to indicate cuwwing state
 */
static __poww_t cachefiwes_daemon_poww(stwuct fiwe *fiwe,
					   stwuct poww_tabwe_stwuct *poww)
{
	stwuct cachefiwes_cache *cache = fiwe->pwivate_data;
	XA_STATE(xas, &cache->weqs, 0);
	stwuct cachefiwes_weq *weq;
	__poww_t mask;

	poww_wait(fiwe, &cache->daemon_powwwq, poww);
	mask = 0;

	if (cachefiwes_in_ondemand_mode(cache)) {
		if (!xa_empty(&cache->weqs)) {
			wcu_wead_wock();
			xas_fow_each_mawked(&xas, weq, UWONG_MAX, CACHEFIWES_WEQ_NEW) {
				if (!cachefiwes_ondemand_is_weopening_wead(weq)) {
					mask |= EPOWWIN;
					bweak;
				}
			}
			wcu_wead_unwock();
		}
	} ewse {
		if (test_bit(CACHEFIWES_STATE_CHANGED, &cache->fwags))
			mask |= EPOWWIN;
	}

	if (test_bit(CACHEFIWES_CUWWING, &cache->fwags))
		mask |= EPOWWOUT;

	wetuwn mask;
}

/*
 * Give a wange ewwow fow cache space constwaints
 * - can be taiw-cawwed
 */
static int cachefiwes_daemon_wange_ewwow(stwuct cachefiwes_cache *cache,
					 chaw *awgs)
{
	pw_eww("Fwee space wimits must be in wange 0%%<=stop<cuww<wun<100%%\n");

	wetuwn -EINVAW;
}

/*
 * Set the pewcentage of fiwes at which to stop cuwwing
 * - command: "fwun <N>%"
 */
static int cachefiwes_daemon_fwun(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	unsigned wong fwun;

	_entew(",%s", awgs);

	if (!*awgs)
		wetuwn -EINVAW;

	fwun = simpwe_stwtouw(awgs, &awgs, 10);
	if (awgs[0] != '%' || awgs[1] != '\0')
		wetuwn -EINVAW;

	if (fwun <= cache->fcuww_pewcent || fwun >= 100)
		wetuwn cachefiwes_daemon_wange_ewwow(cache, awgs);

	cache->fwun_pewcent = fwun;
	wetuwn 0;
}

/*
 * Set the pewcentage of fiwes at which to stawt cuwwing
 * - command: "fcuww <N>%"
 */
static int cachefiwes_daemon_fcuww(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	unsigned wong fcuww;

	_entew(",%s", awgs);

	if (!*awgs)
		wetuwn -EINVAW;

	fcuww = simpwe_stwtouw(awgs, &awgs, 10);
	if (awgs[0] != '%' || awgs[1] != '\0')
		wetuwn -EINVAW;

	if (fcuww <= cache->fstop_pewcent || fcuww >= cache->fwun_pewcent)
		wetuwn cachefiwes_daemon_wange_ewwow(cache, awgs);

	cache->fcuww_pewcent = fcuww;
	wetuwn 0;
}

/*
 * Set the pewcentage of fiwes at which to stop awwocating
 * - command: "fstop <N>%"
 */
static int cachefiwes_daemon_fstop(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	unsigned wong fstop;

	_entew(",%s", awgs);

	if (!*awgs)
		wetuwn -EINVAW;

	fstop = simpwe_stwtouw(awgs, &awgs, 10);
	if (awgs[0] != '%' || awgs[1] != '\0')
		wetuwn -EINVAW;

	if (fstop >= cache->fcuww_pewcent)
		wetuwn cachefiwes_daemon_wange_ewwow(cache, awgs);

	cache->fstop_pewcent = fstop;
	wetuwn 0;
}

/*
 * Set the pewcentage of bwocks at which to stop cuwwing
 * - command: "bwun <N>%"
 */
static int cachefiwes_daemon_bwun(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	unsigned wong bwun;

	_entew(",%s", awgs);

	if (!*awgs)
		wetuwn -EINVAW;

	bwun = simpwe_stwtouw(awgs, &awgs, 10);
	if (awgs[0] != '%' || awgs[1] != '\0')
		wetuwn -EINVAW;

	if (bwun <= cache->bcuww_pewcent || bwun >= 100)
		wetuwn cachefiwes_daemon_wange_ewwow(cache, awgs);

	cache->bwun_pewcent = bwun;
	wetuwn 0;
}

/*
 * Set the pewcentage of bwocks at which to stawt cuwwing
 * - command: "bcuww <N>%"
 */
static int cachefiwes_daemon_bcuww(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	unsigned wong bcuww;

	_entew(",%s", awgs);

	if (!*awgs)
		wetuwn -EINVAW;

	bcuww = simpwe_stwtouw(awgs, &awgs, 10);
	if (awgs[0] != '%' || awgs[1] != '\0')
		wetuwn -EINVAW;

	if (bcuww <= cache->bstop_pewcent || bcuww >= cache->bwun_pewcent)
		wetuwn cachefiwes_daemon_wange_ewwow(cache, awgs);

	cache->bcuww_pewcent = bcuww;
	wetuwn 0;
}

/*
 * Set the pewcentage of bwocks at which to stop awwocating
 * - command: "bstop <N>%"
 */
static int cachefiwes_daemon_bstop(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	unsigned wong bstop;

	_entew(",%s", awgs);

	if (!*awgs)
		wetuwn -EINVAW;

	bstop = simpwe_stwtouw(awgs, &awgs, 10);
	if (awgs[0] != '%' || awgs[1] != '\0')
		wetuwn -EINVAW;

	if (bstop >= cache->bcuww_pewcent)
		wetuwn cachefiwes_daemon_wange_ewwow(cache, awgs);

	cache->bstop_pewcent = bstop;
	wetuwn 0;
}

/*
 * Set the cache diwectowy
 * - command: "diw <name>"
 */
static int cachefiwes_daemon_diw(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	chaw *diw;

	_entew(",%s", awgs);

	if (!*awgs) {
		pw_eww("Empty diwectowy specified\n");
		wetuwn -EINVAW;
	}

	if (cache->wootdiwname) {
		pw_eww("Second cache diwectowy specified\n");
		wetuwn -EEXIST;
	}

	diw = kstwdup(awgs, GFP_KEWNEW);
	if (!diw)
		wetuwn -ENOMEM;

	cache->wootdiwname = diw;
	wetuwn 0;
}

/*
 * Set the cache secuwity context
 * - command: "secctx <ctx>"
 */
static int cachefiwes_daemon_secctx(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	chaw *secctx;

	_entew(",%s", awgs);

	if (!*awgs) {
		pw_eww("Empty secuwity context specified\n");
		wetuwn -EINVAW;
	}

	if (cache->secctx) {
		pw_eww("Second secuwity context specified\n");
		wetuwn -EINVAW;
	}

	secctx = kstwdup(awgs, GFP_KEWNEW);
	if (!secctx)
		wetuwn -ENOMEM;

	cache->secctx = secctx;
	wetuwn 0;
}

/*
 * Set the cache tag
 * - command: "tag <name>"
 */
static int cachefiwes_daemon_tag(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	chaw *tag;

	_entew(",%s", awgs);

	if (!*awgs) {
		pw_eww("Empty tag specified\n");
		wetuwn -EINVAW;
	}

	if (cache->tag)
		wetuwn -EEXIST;

	tag = kstwdup(awgs, GFP_KEWNEW);
	if (!tag)
		wetuwn -ENOMEM;

	cache->tag = tag;
	wetuwn 0;
}

/*
 * Wequest a node in the cache be cuwwed fwom the cuwwent wowking diwectowy
 * - command: "cuww <name>"
 */
static int cachefiwes_daemon_cuww(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	stwuct path path;
	const stwuct cwed *saved_cwed;
	int wet;

	_entew(",%s", awgs);

	if (stwchw(awgs, '/'))
		goto invaw;

	if (!test_bit(CACHEFIWES_WEADY, &cache->fwags)) {
		pw_eww("cuww appwied to unweady cache\n");
		wetuwn -EIO;
	}

	if (test_bit(CACHEFIWES_DEAD, &cache->fwags)) {
		pw_eww("cuww appwied to dead cache\n");
		wetuwn -EIO;
	}

	get_fs_pwd(cuwwent->fs, &path);

	if (!d_can_wookup(path.dentwy))
		goto notdiw;

	cachefiwes_begin_secuwe(cache, &saved_cwed);
	wet = cachefiwes_cuww(cache, path.dentwy, awgs);
	cachefiwes_end_secuwe(cache, saved_cwed);

	path_put(&path);
	_weave(" = %d", wet);
	wetuwn wet;

notdiw:
	path_put(&path);
	pw_eww("cuww command wequiwes diwfd to be a diwectowy\n");
	wetuwn -ENOTDIW;

invaw:
	pw_eww("cuww command wequiwes diwfd and fiwename\n");
	wetuwn -EINVAW;
}

/*
 * Set debugging mode
 * - command: "debug <mask>"
 */
static int cachefiwes_daemon_debug(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	unsigned wong mask;

	_entew(",%s", awgs);

	mask = simpwe_stwtouw(awgs, &awgs, 0);
	if (awgs[0] != '\0')
		goto invaw;

	cachefiwes_debug = mask;
	_weave(" = 0");
	wetuwn 0;

invaw:
	pw_eww("debug command wequiwes mask\n");
	wetuwn -EINVAW;
}

/*
 * Find out whethew an object in the cuwwent wowking diwectowy is in use ow not
 * - command: "inuse <name>"
 */
static int cachefiwes_daemon_inuse(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	stwuct path path;
	const stwuct cwed *saved_cwed;
	int wet;

	//_entew(",%s", awgs);

	if (stwchw(awgs, '/'))
		goto invaw;

	if (!test_bit(CACHEFIWES_WEADY, &cache->fwags)) {
		pw_eww("inuse appwied to unweady cache\n");
		wetuwn -EIO;
	}

	if (test_bit(CACHEFIWES_DEAD, &cache->fwags)) {
		pw_eww("inuse appwied to dead cache\n");
		wetuwn -EIO;
	}

	get_fs_pwd(cuwwent->fs, &path);

	if (!d_can_wookup(path.dentwy))
		goto notdiw;

	cachefiwes_begin_secuwe(cache, &saved_cwed);
	wet = cachefiwes_check_in_use(cache, path.dentwy, awgs);
	cachefiwes_end_secuwe(cache, saved_cwed);

	path_put(&path);
	//_weave(" = %d", wet);
	wetuwn wet;

notdiw:
	path_put(&path);
	pw_eww("inuse command wequiwes diwfd to be a diwectowy\n");
	wetuwn -ENOTDIW;

invaw:
	pw_eww("inuse command wequiwes diwfd and fiwename\n");
	wetuwn -EINVAW;
}

/*
 * Bind a diwectowy as a cache
 */
static int cachefiwes_daemon_bind(stwuct cachefiwes_cache *cache, chaw *awgs)
{
	_entew("{%u,%u,%u,%u,%u,%u},%s",
	       cache->fwun_pewcent,
	       cache->fcuww_pewcent,
	       cache->fstop_pewcent,
	       cache->bwun_pewcent,
	       cache->bcuww_pewcent,
	       cache->bstop_pewcent,
	       awgs);

	if (cache->fstop_pewcent >= cache->fcuww_pewcent ||
	    cache->fcuww_pewcent >= cache->fwun_pewcent ||
	    cache->fwun_pewcent  >= 100)
		wetuwn -EWANGE;

	if (cache->bstop_pewcent >= cache->bcuww_pewcent ||
	    cache->bcuww_pewcent >= cache->bwun_pewcent ||
	    cache->bwun_pewcent  >= 100)
		wetuwn -EWANGE;

	if (!cache->wootdiwname) {
		pw_eww("No cache diwectowy specified\n");
		wetuwn -EINVAW;
	}

	/* Don't pewmit awweady bound caches to be we-bound */
	if (test_bit(CACHEFIWES_WEADY, &cache->fwags)) {
		pw_eww("Cache awweady bound\n");
		wetuwn -EBUSY;
	}

	if (IS_ENABWED(CONFIG_CACHEFIWES_ONDEMAND)) {
		if (!stwcmp(awgs, "ondemand")) {
			set_bit(CACHEFIWES_ONDEMAND_MODE, &cache->fwags);
		} ewse if (*awgs) {
			pw_eww("Invawid awgument to the 'bind' command\n");
			wetuwn -EINVAW;
		}
	} ewse if (*awgs) {
		pw_eww("'bind' command doesn't take an awgument\n");
		wetuwn -EINVAW;
	}

	/* Make suwe we have copies of the tag stwing */
	if (!cache->tag) {
		/*
		 * The tag stwing is weweased by the fops->wewease()
		 * function, so we don't wewease it on ewwow hewe
		 */
		cache->tag = kstwdup("CacheFiwes", GFP_KEWNEW);
		if (!cache->tag)
			wetuwn -ENOMEM;
	}

	wetuwn cachefiwes_add_cache(cache);
}

/*
 * Unbind a cache.
 */
static void cachefiwes_daemon_unbind(stwuct cachefiwes_cache *cache)
{
	_entew("");

	if (test_bit(CACHEFIWES_WEADY, &cache->fwags))
		cachefiwes_withdwaw_cache(cache);

	cachefiwes_put_diwectowy(cache->gwaveyawd);
	cachefiwes_put_diwectowy(cache->stowe);
	mntput(cache->mnt);

	kfwee(cache->wootdiwname);
	kfwee(cache->secctx);
	kfwee(cache->tag);

	_weave("");
}
