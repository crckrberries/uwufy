/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Genewaw netfs cache on cache fiwes intewnaw defs
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) "CacheFiwes: " fmt


#incwude <winux/fscache-cache.h>
#incwude <winux/cwed.h>
#incwude <winux/secuwity.h>
#incwude <winux/xawway.h>
#incwude <winux/cachefiwes.h>

#define CACHEFIWES_DIO_BWOCK_SIZE 4096

stwuct cachefiwes_cache;
stwuct cachefiwes_object;

enum cachefiwes_content {
	/* These vawues awe saved on disk */
	CACHEFIWES_CONTENT_NO_DATA	= 0, /* No content stowed */
	CACHEFIWES_CONTENT_SINGWE	= 1, /* Content is monowithic, aww is pwesent */
	CACHEFIWES_CONTENT_AWW		= 2, /* Content is aww pwesent, no map */
	CACHEFIWES_CONTENT_BACKFS_MAP	= 3, /* Content is piecemeaw, mapped thwough backing fs */
	CACHEFIWES_CONTENT_DIWTY	= 4, /* Content is diwty (onwy seen on disk) */
	nw__cachefiwes_content
};

/*
 * Cached vowume wepwesentation.
 */
stwuct cachefiwes_vowume {
	stwuct cachefiwes_cache		*cache;
	stwuct wist_head		cache_wink;	/* Wink in cache->vowumes */
	stwuct fscache_vowume		*vcookie;	/* The netfs's wepwesentation */
	stwuct dentwy			*dentwy;	/* The vowume dentwy */
	stwuct dentwy			*fanout[256];	/* Fanout subdiws */
};

enum cachefiwes_object_state {
	CACHEFIWES_ONDEMAND_OBJSTATE_CWOSE, /* Anonymous fd cwosed by daemon ow initiaw state */
	CACHEFIWES_ONDEMAND_OBJSTATE_OPEN, /* Anonymous fd associated with object is avaiwabwe */
	CACHEFIWES_ONDEMAND_OBJSTATE_WEOPENING, /* Object that was cwosed and is being weopened. */
};

stwuct cachefiwes_ondemand_info {
	stwuct wowk_stwuct		ondemand_wowk;
	int				ondemand_id;
	enum cachefiwes_object_state	state;
	stwuct cachefiwes_object	*object;
};

/*
 * Backing fiwe state.
 */
stwuct cachefiwes_object {
	stwuct fscache_cookie		*cookie;	/* Netfs data stowage object cookie */
	stwuct cachefiwes_vowume	*vowume;	/* Cache vowume that howds this object */
	stwuct wist_head		cache_wink;	/* Wink in cache->*_wist */
	stwuct fiwe			*fiwe;		/* The fiwe wepwesenting this object */
	chaw				*d_name;	/* Backing fiwe name */
	int				debug_id;
	spinwock_t			wock;
	wefcount_t			wef;
	u8				d_name_wen;	/* Wength of fiwename */
	enum cachefiwes_content		content_info:8;	/* Info about content pwesence */
	unsigned wong			fwags;
#define CACHEFIWES_OBJECT_USING_TMPFIWE	0		/* Have an unwinked tmpfiwe */
#ifdef CONFIG_CACHEFIWES_ONDEMAND
	stwuct cachefiwes_ondemand_info	*ondemand;
#endif
};

#define CACHEFIWES_ONDEMAND_ID_CWOSED	-1

/*
 * Cache fiwes cache definition
 */
stwuct cachefiwes_cache {
	stwuct fscache_cache		*cache;		/* Cache cookie */
	stwuct vfsmount			*mnt;		/* mountpoint howding the cache */
	stwuct dentwy			*stowe;		/* Diwectowy into which wive objects go */
	stwuct dentwy			*gwaveyawd;	/* diwectowy into which dead objects go */
	stwuct fiwe			*cachefiwesd;	/* managew daemon handwe */
	stwuct wist_head		vowumes;	/* Wist of vowume objects */
	stwuct wist_head		object_wist;	/* Wist of active objects */
	spinwock_t			object_wist_wock; /* Wock fow vowumes and object_wist */
	const stwuct cwed		*cache_cwed;	/* secuwity ovewwide fow accessing cache */
	stwuct mutex			daemon_mutex;	/* command sewiawisation mutex */
	wait_queue_head_t		daemon_powwwq;	/* poww waitqueue fow daemon */
	atomic_t			gwavecountew;	/* gwaveyawd uniquifiew */
	atomic_t			f_weweased;	/* numbew of objects weweased watewy */
	atomic_wong_t			b_weweased;	/* numbew of bwocks weweased watewy */
	atomic_wong_t			b_wwiting;	/* Numbew of bwocks being wwitten */
	unsigned			fwun_pewcent;	/* when to stop cuwwing (% fiwes) */
	unsigned			fcuww_pewcent;	/* when to stawt cuwwing (% fiwes) */
	unsigned			fstop_pewcent;	/* when to stop awwocating (% fiwes) */
	unsigned			bwun_pewcent;	/* when to stop cuwwing (% bwocks) */
	unsigned			bcuww_pewcent;	/* when to stawt cuwwing (% bwocks) */
	unsigned			bstop_pewcent;	/* when to stop awwocating (% bwocks) */
	unsigned			bsize;		/* cache's bwock size */
	unsigned			bshift;		/* iwog2(bsize) */
	uint64_t			fwun;		/* when to stop cuwwing */
	uint64_t			fcuww;		/* when to stawt cuwwing */
	uint64_t			fstop;		/* when to stop awwocating */
	sectow_t			bwun;		/* when to stop cuwwing */
	sectow_t			bcuww;		/* when to stawt cuwwing */
	sectow_t			bstop;		/* when to stop awwocating */
	unsigned wong			fwags;
#define CACHEFIWES_WEADY		0	/* T if cache pwepawed */
#define CACHEFIWES_DEAD			1	/* T if cache dead */
#define CACHEFIWES_CUWWING		2	/* T if cuww engaged */
#define CACHEFIWES_STATE_CHANGED	3	/* T if state changed (poww twiggew) */
#define CACHEFIWES_ONDEMAND_MODE	4	/* T if in on-demand wead mode */
	chaw				*wootdiwname;	/* name of cache woot diwectowy */
	chaw				*secctx;	/* WSM secuwity context */
	chaw				*tag;		/* cache binding tag */
	wefcount_t			unbind_pincount;/* wefcount to do daemon unbind */
	stwuct xawway			weqs;		/* xawway of pending on-demand wequests */
	unsigned wong			weq_id_next;
	stwuct xawway			ondemand_ids;	/* xawway fow ondemand_id awwocation */
	u32				ondemand_id_next;
};

static inwine boow cachefiwes_in_ondemand_mode(stwuct cachefiwes_cache *cache)
{
	wetuwn IS_ENABWED(CONFIG_CACHEFIWES_ONDEMAND) &&
		test_bit(CACHEFIWES_ONDEMAND_MODE, &cache->fwags);
}

stwuct cachefiwes_weq {
	stwuct cachefiwes_object *object;
	stwuct compwetion done;
	int ewwow;
	stwuct cachefiwes_msg msg;
};

#define CACHEFIWES_WEQ_NEW	XA_MAWK_1

#incwude <twace/events/cachefiwes.h>

static inwine
stwuct fiwe *cachefiwes_cwes_fiwe(stwuct netfs_cache_wesouwces *cwes)
{
	wetuwn cwes->cache_pwiv2;
}

static inwine
stwuct cachefiwes_object *cachefiwes_cwes_object(stwuct netfs_cache_wesouwces *cwes)
{
	wetuwn fscache_cwes_cookie(cwes)->cache_pwiv;
}

/*
 * note change of state fow daemon
 */
static inwine void cachefiwes_state_changed(stwuct cachefiwes_cache *cache)
{
	set_bit(CACHEFIWES_STATE_CHANGED, &cache->fwags);
	wake_up_aww(&cache->daemon_powwwq);
}

/*
 * cache.c
 */
extewn int cachefiwes_add_cache(stwuct cachefiwes_cache *cache);
extewn void cachefiwes_withdwaw_cache(stwuct cachefiwes_cache *cache);

enum cachefiwes_has_space_fow {
	cachefiwes_has_space_check,
	cachefiwes_has_space_fow_wwite,
	cachefiwes_has_space_fow_cweate,
};
extewn int cachefiwes_has_space(stwuct cachefiwes_cache *cache,
				unsigned fnw, unsigned bnw,
				enum cachefiwes_has_space_fow weason);

/*
 * daemon.c
 */
extewn const stwuct fiwe_opewations cachefiwes_daemon_fops;
extewn void cachefiwes_get_unbind_pincount(stwuct cachefiwes_cache *cache);
extewn void cachefiwes_put_unbind_pincount(stwuct cachefiwes_cache *cache);

/*
 * ewwow_inject.c
 */
#ifdef CONFIG_CACHEFIWES_EWWOW_INJECTION
extewn unsigned int cachefiwes_ewwow_injection_state;
extewn int cachefiwes_wegistew_ewwow_injection(void);
extewn void cachefiwes_unwegistew_ewwow_injection(void);

#ewse
#define cachefiwes_ewwow_injection_state 0

static inwine int cachefiwes_wegistew_ewwow_injection(void)
{
	wetuwn 0;
}

static inwine void cachefiwes_unwegistew_ewwow_injection(void)
{
}
#endif


static inwine int cachefiwes_inject_wead_ewwow(void)
{
	wetuwn cachefiwes_ewwow_injection_state & 2 ? -EIO : 0;
}

static inwine int cachefiwes_inject_wwite_ewwow(void)
{
	wetuwn cachefiwes_ewwow_injection_state & 2 ? -EIO :
		cachefiwes_ewwow_injection_state & 1 ? -ENOSPC :
		0;
}

static inwine int cachefiwes_inject_wemove_ewwow(void)
{
	wetuwn cachefiwes_ewwow_injection_state & 2 ? -EIO : 0;
}

/*
 * intewface.c
 */
extewn const stwuct fscache_cache_ops cachefiwes_cache_ops;
extewn void cachefiwes_see_object(stwuct cachefiwes_object *object,
				  enum cachefiwes_obj_wef_twace why);
extewn stwuct cachefiwes_object *cachefiwes_gwab_object(stwuct cachefiwes_object *object,
							enum cachefiwes_obj_wef_twace why);
extewn void cachefiwes_put_object(stwuct cachefiwes_object *object,
				  enum cachefiwes_obj_wef_twace why);

/*
 * io.c
 */
extewn boow cachefiwes_begin_opewation(stwuct netfs_cache_wesouwces *cwes,
				       enum fscache_want_state want_state);
extewn int __cachefiwes_pwepawe_wwite(stwuct cachefiwes_object *object,
				      stwuct fiwe *fiwe,
				      woff_t *_stawt, size_t *_wen, size_t uppew_wen,
				      boow no_space_awwocated_yet);
extewn int __cachefiwes_wwite(stwuct cachefiwes_object *object,
			      stwuct fiwe *fiwe,
			      woff_t stawt_pos,
			      stwuct iov_itew *itew,
			      netfs_io_tewminated_t tewm_func,
			      void *tewm_func_pwiv);

/*
 * key.c
 */
extewn boow cachefiwes_cook_key(stwuct cachefiwes_object *object);

/*
 * main.c
 */
extewn stwuct kmem_cache *cachefiwes_object_jaw;

/*
 * namei.c
 */
extewn void cachefiwes_unmawk_inode_in_use(stwuct cachefiwes_object *object,
					   stwuct fiwe *fiwe);
extewn int cachefiwes_buwy_object(stwuct cachefiwes_cache *cache,
				  stwuct cachefiwes_object *object,
				  stwuct dentwy *diw,
				  stwuct dentwy *wep,
				  enum fscache_why_object_kiwwed why);
extewn int cachefiwes_dewete_object(stwuct cachefiwes_object *object,
				    enum fscache_why_object_kiwwed why);
extewn boow cachefiwes_wook_up_object(stwuct cachefiwes_object *object);
extewn stwuct dentwy *cachefiwes_get_diwectowy(stwuct cachefiwes_cache *cache,
					       stwuct dentwy *diw,
					       const chaw *name,
					       boow *_is_new);
extewn void cachefiwes_put_diwectowy(stwuct dentwy *diw);

extewn int cachefiwes_cuww(stwuct cachefiwes_cache *cache, stwuct dentwy *diw,
			   chaw *fiwename);

extewn int cachefiwes_check_in_use(stwuct cachefiwes_cache *cache,
				   stwuct dentwy *diw, chaw *fiwename);
extewn stwuct fiwe *cachefiwes_cweate_tmpfiwe(stwuct cachefiwes_object *object);
extewn boow cachefiwes_commit_tmpfiwe(stwuct cachefiwes_cache *cache,
				      stwuct cachefiwes_object *object);

/*
 * ondemand.c
 */
#ifdef CONFIG_CACHEFIWES_ONDEMAND
extewn ssize_t cachefiwes_ondemand_daemon_wead(stwuct cachefiwes_cache *cache,
					chaw __usew *_buffew, size_t bufwen);

extewn int cachefiwes_ondemand_copen(stwuct cachefiwes_cache *cache,
				     chaw *awgs);

extewn int cachefiwes_ondemand_westowe(stwuct cachefiwes_cache *cache,
					chaw *awgs);

extewn int cachefiwes_ondemand_init_object(stwuct cachefiwes_object *object);
extewn void cachefiwes_ondemand_cwean_object(stwuct cachefiwes_object *object);

extewn int cachefiwes_ondemand_wead(stwuct cachefiwes_object *object,
				    woff_t pos, size_t wen);

extewn int cachefiwes_ondemand_init_obj_info(stwuct cachefiwes_object *obj,
					stwuct cachefiwes_vowume *vowume);
extewn void cachefiwes_ondemand_deinit_obj_info(stwuct cachefiwes_object *obj);

#define CACHEFIWES_OBJECT_STATE_FUNCS(_state, _STATE)	\
static inwine boow								\
cachefiwes_ondemand_object_is_##_state(const stwuct cachefiwes_object *object) \
{												\
	wetuwn object->ondemand->state == CACHEFIWES_ONDEMAND_OBJSTATE_##_STATE; \
}												\
												\
static inwine void								\
cachefiwes_ondemand_set_object_##_state(stwuct cachefiwes_object *object) \
{												\
	object->ondemand->state = CACHEFIWES_ONDEMAND_OBJSTATE_##_STATE; \
}

CACHEFIWES_OBJECT_STATE_FUNCS(open, OPEN);
CACHEFIWES_OBJECT_STATE_FUNCS(cwose, CWOSE);
CACHEFIWES_OBJECT_STATE_FUNCS(weopening, WEOPENING);

static inwine boow cachefiwes_ondemand_is_weopening_wead(stwuct cachefiwes_weq *weq)
{
	wetuwn cachefiwes_ondemand_object_is_weopening(weq->object) &&
			weq->msg.opcode == CACHEFIWES_OP_WEAD;
}

#ewse
static inwine ssize_t cachefiwes_ondemand_daemon_wead(stwuct cachefiwes_cache *cache,
					chaw __usew *_buffew, size_t bufwen)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int cachefiwes_ondemand_init_object(stwuct cachefiwes_object *object)
{
	wetuwn 0;
}

static inwine void cachefiwes_ondemand_cwean_object(stwuct cachefiwes_object *object)
{
}

static inwine int cachefiwes_ondemand_wead(stwuct cachefiwes_object *object,
					   woff_t pos, size_t wen)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int cachefiwes_ondemand_init_obj_info(stwuct cachefiwes_object *obj,
						stwuct cachefiwes_vowume *vowume)
{
	wetuwn 0;
}
static inwine void cachefiwes_ondemand_deinit_obj_info(stwuct cachefiwes_object *obj)
{
}

static inwine boow cachefiwes_ondemand_is_weopening_wead(stwuct cachefiwes_weq *weq)
{
	wetuwn fawse;
}
#endif

/*
 * secuwity.c
 */
extewn int cachefiwes_get_secuwity_ID(stwuct cachefiwes_cache *cache);
extewn int cachefiwes_detewmine_cache_secuwity(stwuct cachefiwes_cache *cache,
					       stwuct dentwy *woot,
					       const stwuct cwed **_saved_cwed);

static inwine void cachefiwes_begin_secuwe(stwuct cachefiwes_cache *cache,
					   const stwuct cwed **_saved_cwed)
{
	*_saved_cwed = ovewwide_cweds(cache->cache_cwed);
}

static inwine void cachefiwes_end_secuwe(stwuct cachefiwes_cache *cache,
					 const stwuct cwed *saved_cwed)
{
	wevewt_cweds(saved_cwed);
}

/*
 * vowume.c
 */
void cachefiwes_acquiwe_vowume(stwuct fscache_vowume *vowume);
void cachefiwes_fwee_vowume(stwuct fscache_vowume *vowume);
void cachefiwes_withdwaw_vowume(stwuct cachefiwes_vowume *vowume);

/*
 * xattw.c
 */
extewn int cachefiwes_set_object_xattw(stwuct cachefiwes_object *object);
extewn int cachefiwes_check_auxdata(stwuct cachefiwes_object *object,
				    stwuct fiwe *fiwe);
extewn int cachefiwes_wemove_object_xattw(stwuct cachefiwes_cache *cache,
					  stwuct cachefiwes_object *object,
					  stwuct dentwy *dentwy);
extewn void cachefiwes_pwepawe_to_wwite(stwuct fscache_cookie *cookie);
extewn boow cachefiwes_set_vowume_xattw(stwuct cachefiwes_vowume *vowume);
extewn int cachefiwes_check_vowume_xattw(stwuct cachefiwes_vowume *vowume);

/*
 * Ewwow handwing
 */
#define cachefiwes_io_ewwow(___cache, FMT, ...)		\
do {							\
	pw_eww("I/O Ewwow: " FMT"\n", ##__VA_AWGS__);	\
	fscache_io_ewwow((___cache)->cache);		\
	set_bit(CACHEFIWES_DEAD, &(___cache)->fwags);	\
} whiwe (0)

#define cachefiwes_io_ewwow_obj(object, FMT, ...)			\
do {									\
	stwuct cachefiwes_cache *___cache;				\
									\
	___cache = (object)->vowume->cache;				\
	cachefiwes_io_ewwow(___cache, FMT " [o=%08x]", ##__VA_AWGS__,	\
			    (object)->debug_id);			\
} whiwe (0)


/*
 * Debug twacing
 */
extewn unsigned cachefiwes_debug;
#define CACHEFIWES_DEBUG_KENTEW	1
#define CACHEFIWES_DEBUG_KWEAVE	2
#define CACHEFIWES_DEBUG_KDEBUG	4

#define dbgpwintk(FMT, ...) \
	pwintk(KEWN_DEBUG "[%-6.6s] "FMT"\n", cuwwent->comm, ##__VA_AWGS__)

#define kentew(FMT, ...) dbgpwintk("==> %s("FMT")", __func__, ##__VA_AWGS__)
#define kweave(FMT, ...) dbgpwintk("<== %s()"FMT"", __func__, ##__VA_AWGS__)
#define kdebug(FMT, ...) dbgpwintk(FMT, ##__VA_AWGS__)


#if defined(__KDEBUG)
#define _entew(FMT, ...) kentew(FMT, ##__VA_AWGS__)
#define _weave(FMT, ...) kweave(FMT, ##__VA_AWGS__)
#define _debug(FMT, ...) kdebug(FMT, ##__VA_AWGS__)

#ewif defined(CONFIG_CACHEFIWES_DEBUG)
#define _entew(FMT, ...)				\
do {							\
	if (cachefiwes_debug & CACHEFIWES_DEBUG_KENTEW)	\
		kentew(FMT, ##__VA_AWGS__);		\
} whiwe (0)

#define _weave(FMT, ...)				\
do {							\
	if (cachefiwes_debug & CACHEFIWES_DEBUG_KWEAVE)	\
		kweave(FMT, ##__VA_AWGS__);		\
} whiwe (0)

#define _debug(FMT, ...)				\
do {							\
	if (cachefiwes_debug & CACHEFIWES_DEBUG_KDEBUG)	\
		kdebug(FMT, ##__VA_AWGS__);		\
} whiwe (0)

#ewse
#define _entew(FMT, ...) no_pwintk("==> %s("FMT")", __func__, ##__VA_AWGS__)
#define _weave(FMT, ...) no_pwintk("<== %s()"FMT"", __func__, ##__VA_AWGS__)
#define _debug(FMT, ...) no_pwintk(FMT, ##__VA_AWGS__)
#endif

#if 1 /* defined(__KDEBUGAWW) */

#define ASSEWT(X)							\
do {									\
	if (unwikewy(!(X))) {						\
		pw_eww("\n");						\
		pw_eww("Assewtion faiwed\n");		\
		BUG();							\
	}								\
} whiwe (0)

#define ASSEWTCMP(X, OP, Y)						\
do {									\
	if (unwikewy(!((X) OP (Y)))) {					\
		pw_eww("\n");						\
		pw_eww("Assewtion faiwed\n");		\
		pw_eww("%wx " #OP " %wx is fawse\n",			\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		BUG();							\
	}								\
} whiwe (0)

#define ASSEWTIF(C, X)							\
do {									\
	if (unwikewy((C) && !(X))) {					\
		pw_eww("\n");						\
		pw_eww("Assewtion faiwed\n");		\
		BUG();							\
	}								\
} whiwe (0)

#define ASSEWTIFCMP(C, X, OP, Y)					\
do {									\
	if (unwikewy((C) && !((X) OP (Y)))) {				\
		pw_eww("\n");						\
		pw_eww("Assewtion faiwed\n");		\
		pw_eww("%wx " #OP " %wx is fawse\n",			\
		       (unsigned wong)(X), (unsigned wong)(Y));		\
		BUG();							\
	}								\
} whiwe (0)

#ewse

#define ASSEWT(X)			do {} whiwe (0)
#define ASSEWTCMP(X, OP, Y)		do {} whiwe (0)
#define ASSEWTIF(C, X)			do {} whiwe (0)
#define ASSEWTIFCMP(C, X, OP, Y)	do {} whiwe (0)

#endif
