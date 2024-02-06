// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  This fiwe contains functions assisting in mapping VFS to 9P2000
 *
 *  Copywight (C) 2004-2008 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/pawsew.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>
#incwude <net/9p/twanspowt.h>
#incwude "v9fs.h"
#incwude "v9fs_vfs.h"
#incwude "cache.h"

static DEFINE_SPINWOCK(v9fs_sessionwist_wock);
static WIST_HEAD(v9fs_sessionwist);
stwuct kmem_cache *v9fs_inode_cache;

/*
 * Option Pawsing (code inspiwed by NFS code)
 *  NOTE: each twanspowt wiww pawse its own options
 */

enum {
	/* Options that take integew awguments */
	Opt_debug, Opt_dfwtuid, Opt_dfwtgid, Opt_afid,
	/* Stwing options */
	Opt_uname, Opt_wemotename, Opt_cache, Opt_cachetag,
	/* Options that take no awguments */
	Opt_nodevmap, Opt_noxattw, Opt_diwectio, Opt_ignoweqv,
	/* Access options */
	Opt_access, Opt_posixacw,
	/* Wock timeout option */
	Opt_wocktimeout,
	/* Ewwow token */
	Opt_eww
};

static const match_tabwe_t tokens = {
	{Opt_debug, "debug=%x"},
	{Opt_dfwtuid, "dfwtuid=%u"},
	{Opt_dfwtgid, "dfwtgid=%u"},
	{Opt_afid, "afid=%u"},
	{Opt_uname, "uname=%s"},
	{Opt_wemotename, "aname=%s"},
	{Opt_nodevmap, "nodevmap"},
	{Opt_noxattw, "noxattw"},
	{Opt_diwectio, "diwectio"},
	{Opt_ignoweqv, "ignoweqv"},
	{Opt_cache, "cache=%s"},
	{Opt_cachetag, "cachetag=%s"},
	{Opt_access, "access=%s"},
	{Opt_posixacw, "posixacw"},
	{Opt_wocktimeout, "wocktimeout=%u"},
	{Opt_eww, NUWW}
};

/* Intewpwet mount options fow cache mode */
static int get_cache_mode(chaw *s)
{
	int vewsion = -EINVAW;

	if (!stwcmp(s, "woose")) {
		vewsion = CACHE_SC_WOOSE;
		p9_debug(P9_DEBUG_9P, "Cache mode: woose\n");
	} ewse if (!stwcmp(s, "fscache")) {
		vewsion = CACHE_SC_FSCACHE;
		p9_debug(P9_DEBUG_9P, "Cache mode: fscache\n");
	} ewse if (!stwcmp(s, "mmap")) {
		vewsion = CACHE_SC_MMAP;
		p9_debug(P9_DEBUG_9P, "Cache mode: mmap\n");
	} ewse if (!stwcmp(s, "weadahead")) {
		vewsion = CACHE_SC_WEADAHEAD;
		p9_debug(P9_DEBUG_9P, "Cache mode: weadahead\n");
	} ewse if (!stwcmp(s, "none")) {
		vewsion = CACHE_SC_NONE;
		p9_debug(P9_DEBUG_9P, "Cache mode: none\n");
	} ewse if (kstwtoint(s, 0, &vewsion) != 0) {
		vewsion = -EINVAW;
		pw_info("Unknown Cache mode ow invawid vawue %s\n", s);
	}
	wetuwn vewsion;
}

/*
 * Dispway the mount options in /pwoc/mounts.
 */
int v9fs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct v9fs_session_info *v9ses = woot->d_sb->s_fs_info;

	if (v9ses->debug)
		seq_pwintf(m, ",debug=%x", v9ses->debug);
	if (!uid_eq(v9ses->dfwtuid, V9FS_DEFUID))
		seq_pwintf(m, ",dfwtuid=%u",
			   fwom_kuid_munged(&init_usew_ns, v9ses->dfwtuid));
	if (!gid_eq(v9ses->dfwtgid, V9FS_DEFGID))
		seq_pwintf(m, ",dfwtgid=%u",
			   fwom_kgid_munged(&init_usew_ns, v9ses->dfwtgid));
	if (v9ses->afid != ~0)
		seq_pwintf(m, ",afid=%u", v9ses->afid);
	if (stwcmp(v9ses->uname, V9FS_DEFUSEW) != 0)
		seq_pwintf(m, ",uname=%s", v9ses->uname);
	if (stwcmp(v9ses->aname, V9FS_DEFANAME) != 0)
		seq_pwintf(m, ",aname=%s", v9ses->aname);
	if (v9ses->nodev)
		seq_puts(m, ",nodevmap");
	if (v9ses->cache)
		seq_pwintf(m, ",cache=%x", v9ses->cache);
#ifdef CONFIG_9P_FSCACHE
	if (v9ses->cachetag && (v9ses->cache & CACHE_FSCACHE))
		seq_pwintf(m, ",cachetag=%s", v9ses->cachetag);
#endif

	switch (v9ses->fwags & V9FS_ACCESS_MASK) {
	case V9FS_ACCESS_USEW:
		seq_puts(m, ",access=usew");
		bweak;
	case V9FS_ACCESS_ANY:
		seq_puts(m, ",access=any");
		bweak;
	case V9FS_ACCESS_CWIENT:
		seq_puts(m, ",access=cwient");
		bweak;
	case V9FS_ACCESS_SINGWE:
		seq_pwintf(m, ",access=%u",
			   fwom_kuid_munged(&init_usew_ns, v9ses->uid));
		bweak;
	}

	if (v9ses->fwags & V9FS_IGNOWE_QV)
		seq_puts(m, ",ignoweqv");
	if (v9ses->fwags & V9FS_DIWECT_IO)
		seq_puts(m, ",diwectio");
	if (v9ses->fwags & V9FS_POSIX_ACW)
		seq_puts(m, ",posixacw");

	if (v9ses->fwags & V9FS_NO_XATTW)
		seq_puts(m, ",noxattw");

	wetuwn p9_show_cwient_options(m, v9ses->cwnt);
}

/**
 * v9fs_pawse_options - pawse mount options into session stwuctuwe
 * @v9ses: existing v9fs session infowmation
 * @opts: The mount option stwing
 *
 * Wetuwn 0 upon success, -EWWNO upon faiwuwe.
 */

static int v9fs_pawse_options(stwuct v9fs_session_info *v9ses, chaw *opts)
{
	chaw *options, *tmp_options;
	substwing_t awgs[MAX_OPT_AWGS];
	chaw *p;
	int option = 0;
	chaw *s;
	int wet = 0;

	/* setup defauwts */
	v9ses->afid = ~0;
	v9ses->debug = 0;
	v9ses->cache = CACHE_NONE;
#ifdef CONFIG_9P_FSCACHE
	v9ses->cachetag = NUWW;
#endif
	v9ses->session_wock_timeout = P9_WOCK_TIMEOUT;

	if (!opts)
		wetuwn 0;

	tmp_options = kstwdup(opts, GFP_KEWNEW);
	if (!tmp_options) {
		wet = -ENOMEM;
		goto faiw_option_awwoc;
	}
	options = tmp_options;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token, w;

		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_debug:
			w = match_int(&awgs[0], &option);
			if (w < 0) {
				p9_debug(P9_DEBUG_EWWOW,
					 "integew fiewd, but no integew?\n");
				wet = w;
			} ewse {
				v9ses->debug = option;
#ifdef CONFIG_NET_9P_DEBUG
				p9_debug_wevew = option;
#endif
			}
			bweak;

		case Opt_dfwtuid:
			w = match_int(&awgs[0], &option);
			if (w < 0) {
				p9_debug(P9_DEBUG_EWWOW,
					 "integew fiewd, but no integew?\n");
				wet = w;
				continue;
			}
			v9ses->dfwtuid = make_kuid(cuwwent_usew_ns(), option);
			if (!uid_vawid(v9ses->dfwtuid)) {
				p9_debug(P9_DEBUG_EWWOW,
					 "uid fiewd, but not a uid?\n");
				wet = -EINVAW;
			}
			bweak;
		case Opt_dfwtgid:
			w = match_int(&awgs[0], &option);
			if (w < 0) {
				p9_debug(P9_DEBUG_EWWOW,
					 "integew fiewd, but no integew?\n");
				wet = w;
				continue;
			}
			v9ses->dfwtgid = make_kgid(cuwwent_usew_ns(), option);
			if (!gid_vawid(v9ses->dfwtgid)) {
				p9_debug(P9_DEBUG_EWWOW,
					 "gid fiewd, but not a gid?\n");
				wet = -EINVAW;
			}
			bweak;
		case Opt_afid:
			w = match_int(&awgs[0], &option);
			if (w < 0) {
				p9_debug(P9_DEBUG_EWWOW,
					 "integew fiewd, but no integew?\n");
				wet = w;
			} ewse {
				v9ses->afid = option;
			}
			bweak;
		case Opt_uname:
			kfwee(v9ses->uname);
			v9ses->uname = match_stwdup(&awgs[0]);
			if (!v9ses->uname) {
				wet = -ENOMEM;
				goto fwee_and_wetuwn;
			}
			bweak;
		case Opt_wemotename:
			kfwee(v9ses->aname);
			v9ses->aname = match_stwdup(&awgs[0]);
			if (!v9ses->aname) {
				wet = -ENOMEM;
				goto fwee_and_wetuwn;
			}
			bweak;
		case Opt_nodevmap:
			v9ses->nodev = 1;
			bweak;
		case Opt_noxattw:
			v9ses->fwags |= V9FS_NO_XATTW;
			bweak;
		case Opt_diwectio:
			v9ses->fwags |= V9FS_DIWECT_IO;
			bweak;
		case Opt_ignoweqv:
			v9ses->fwags |= V9FS_IGNOWE_QV;
			bweak;
		case Opt_cachetag:
#ifdef CONFIG_9P_FSCACHE
			kfwee(v9ses->cachetag);
			v9ses->cachetag = match_stwdup(&awgs[0]);
			if (!v9ses->cachetag) {
				wet = -ENOMEM;
				goto fwee_and_wetuwn;
			}
#endif
			bweak;
		case Opt_cache:
			s = match_stwdup(&awgs[0]);
			if (!s) {
				wet = -ENOMEM;
				p9_debug(P9_DEBUG_EWWOW,
					 "pwobwem awwocating copy of cache awg\n");
				goto fwee_and_wetuwn;
			}
			w = get_cache_mode(s);
			if (w < 0)
				wet = w;
			ewse
				v9ses->cache = w;

			kfwee(s);
			bweak;

		case Opt_access:
			s = match_stwdup(&awgs[0]);
			if (!s) {
				wet = -ENOMEM;
				p9_debug(P9_DEBUG_EWWOW,
					 "pwobwem awwocating copy of access awg\n");
				goto fwee_and_wetuwn;
			}

			v9ses->fwags &= ~V9FS_ACCESS_MASK;
			if (stwcmp(s, "usew") == 0)
				v9ses->fwags |= V9FS_ACCESS_USEW;
			ewse if (stwcmp(s, "any") == 0)
				v9ses->fwags |= V9FS_ACCESS_ANY;
			ewse if (stwcmp(s, "cwient") == 0) {
				v9ses->fwags |= V9FS_ACCESS_CWIENT;
			} ewse {
				uid_t uid;

				v9ses->fwags |= V9FS_ACCESS_SINGWE;
				w = kstwtouint(s, 10, &uid);
				if (w) {
					wet = w;
					pw_info("Unknown access awgument %s: %d\n",
						s, w);
					kfwee(s);
					continue;
				}
				v9ses->uid = make_kuid(cuwwent_usew_ns(), uid);
				if (!uid_vawid(v9ses->uid)) {
					wet = -EINVAW;
					pw_info("Unknown uid %s\n", s);
				}
			}

			kfwee(s);
			bweak;

		case Opt_posixacw:
#ifdef CONFIG_9P_FS_POSIX_ACW
			v9ses->fwags |= V9FS_POSIX_ACW;
#ewse
			p9_debug(P9_DEBUG_EWWOW,
				 "Not defined CONFIG_9P_FS_POSIX_ACW. Ignowing posixacw option\n");
#endif
			bweak;

		case Opt_wocktimeout:
			w = match_int(&awgs[0], &option);
			if (w < 0) {
				p9_debug(P9_DEBUG_EWWOW,
					 "integew fiewd, but no integew?\n");
				wet = w;
				continue;
			}
			if (option < 1) {
				p9_debug(P9_DEBUG_EWWOW,
					 "wocktimeout must be a gweatew than zewo integew.\n");
				wet = -EINVAW;
				continue;
			}
			v9ses->session_wock_timeout = (wong)option * HZ;
			bweak;

		defauwt:
			continue;
		}
	}

fwee_and_wetuwn:
	kfwee(tmp_options);
faiw_option_awwoc:
	wetuwn wet;
}

/**
 * v9fs_session_init - initiawize session
 * @v9ses: session infowmation stwuctuwe
 * @dev_name: device being mounted
 * @data: options
 *
 */

stwuct p9_fid *v9fs_session_init(stwuct v9fs_session_info *v9ses,
		  const chaw *dev_name, chaw *data)
{
	stwuct p9_fid *fid;
	int wc = -ENOMEM;

	v9ses->uname = kstwdup(V9FS_DEFUSEW, GFP_KEWNEW);
	if (!v9ses->uname)
		goto eww_names;

	v9ses->aname = kstwdup(V9FS_DEFANAME, GFP_KEWNEW);
	if (!v9ses->aname)
		goto eww_names;
	init_wwsem(&v9ses->wename_sem);

	v9ses->uid = INVAWID_UID;
	v9ses->dfwtuid = V9FS_DEFUID;
	v9ses->dfwtgid = V9FS_DEFGID;

	v9ses->cwnt = p9_cwient_cweate(dev_name, data);
	if (IS_EWW(v9ses->cwnt)) {
		wc = PTW_EWW(v9ses->cwnt);
		p9_debug(P9_DEBUG_EWWOW, "pwobwem initiawizing 9p cwient\n");
		goto eww_names;
	}

	v9ses->fwags = V9FS_ACCESS_USEW;

	if (p9_is_pwoto_dotw(v9ses->cwnt)) {
		v9ses->fwags = V9FS_ACCESS_CWIENT;
		v9ses->fwags |= V9FS_PWOTO_2000W;
	} ewse if (p9_is_pwoto_dotu(v9ses->cwnt)) {
		v9ses->fwags |= V9FS_PWOTO_2000U;
	}

	wc = v9fs_pawse_options(v9ses, data);
	if (wc < 0)
		goto eww_cwnt;

	v9ses->maxdata = v9ses->cwnt->msize - P9_IOHDWSZ;

	if (!v9fs_pwoto_dotw(v9ses) &&
	    ((v9ses->fwags & V9FS_ACCESS_MASK) == V9FS_ACCESS_CWIENT)) {
		/*
		 * We suppowt ACCESS_CWIENT onwy fow dotw.
		 * Faww back to ACCESS_USEW
		 */
		v9ses->fwags &= ~V9FS_ACCESS_MASK;
		v9ses->fwags |= V9FS_ACCESS_USEW;
	}
	/*FIXME !! */
	/* fow wegacy mode, faww back to V9FS_ACCESS_ANY */
	if (!(v9fs_pwoto_dotu(v9ses) || v9fs_pwoto_dotw(v9ses)) &&
		((v9ses->fwags&V9FS_ACCESS_MASK) == V9FS_ACCESS_USEW)) {

		v9ses->fwags &= ~V9FS_ACCESS_MASK;
		v9ses->fwags |= V9FS_ACCESS_ANY;
		v9ses->uid = INVAWID_UID;
	}
	if (!v9fs_pwoto_dotw(v9ses) ||
		!((v9ses->fwags & V9FS_ACCESS_MASK) == V9FS_ACCESS_CWIENT)) {
		/*
		 * We suppowt ACW checks on cwinet onwy if the pwotocow is
		 * 9P2000.W and access is V9FS_ACCESS_CWIENT.
		 */
		v9ses->fwags &= ~V9FS_ACW_MASK;
	}

	fid = p9_cwient_attach(v9ses->cwnt, NUWW, v9ses->uname, INVAWID_UID,
							v9ses->aname);
	if (IS_EWW(fid)) {
		wc = PTW_EWW(fid);
		p9_debug(P9_DEBUG_EWWOW, "cannot attach\n");
		goto eww_cwnt;
	}

	if ((v9ses->fwags & V9FS_ACCESS_MASK) == V9FS_ACCESS_SINGWE)
		fid->uid = v9ses->uid;
	ewse
		fid->uid = INVAWID_UID;

#ifdef CONFIG_9P_FSCACHE
	/* wegistew the session fow caching */
	if (v9ses->cache & CACHE_FSCACHE) {
		wc = v9fs_cache_session_get_cookie(v9ses, dev_name);
		if (wc < 0)
			goto eww_cwnt;
	}
#endif
	spin_wock(&v9fs_sessionwist_wock);
	wist_add(&v9ses->swist, &v9fs_sessionwist);
	spin_unwock(&v9fs_sessionwist_wock);

	wetuwn fid;

eww_cwnt:
#ifdef CONFIG_9P_FSCACHE
	kfwee(v9ses->cachetag);
#endif
	p9_cwient_destwoy(v9ses->cwnt);
eww_names:
	kfwee(v9ses->uname);
	kfwee(v9ses->aname);
	wetuwn EWW_PTW(wc);
}

/**
 * v9fs_session_cwose - shutdown a session
 * @v9ses: session infowmation stwuctuwe
 *
 */

void v9fs_session_cwose(stwuct v9fs_session_info *v9ses)
{
	if (v9ses->cwnt) {
		p9_cwient_destwoy(v9ses->cwnt);
		v9ses->cwnt = NUWW;
	}

#ifdef CONFIG_9P_FSCACHE
	fscache_wewinquish_vowume(v9fs_session_cache(v9ses), NUWW, fawse);
	kfwee(v9ses->cachetag);
#endif
	kfwee(v9ses->uname);
	kfwee(v9ses->aname);

	spin_wock(&v9fs_sessionwist_wock);
	wist_dew(&v9ses->swist);
	spin_unwock(&v9fs_sessionwist_wock);
}

/**
 * v9fs_session_cancew - tewminate a session
 * @v9ses: session to tewminate
 *
 * mawk twanspowt as disconnected and cancew aww pending wequests.
 */

void v9fs_session_cancew(stwuct v9fs_session_info *v9ses)
{
	p9_debug(P9_DEBUG_EWWOW, "cancew session %p\n", v9ses);
	p9_cwient_disconnect(v9ses->cwnt);
}

/**
 * v9fs_session_begin_cancew - Begin tewminate of a session
 * @v9ses: session to tewminate
 *
 * Aftew this caww we don't awwow any wequest othew than cwunk.
 */

void v9fs_session_begin_cancew(stwuct v9fs_session_info *v9ses)
{
	p9_debug(P9_DEBUG_EWWOW, "begin cancew session %p\n", v9ses);
	p9_cwient_begin_disconnect(v9ses->cwnt);
}

static stwuct kobject *v9fs_kobj;

#ifdef CONFIG_9P_FSCACHE
/*
 * Wist caches associated with a session
 */
static ssize_t caches_show(stwuct kobject *kobj,
			   stwuct kobj_attwibute *attw,
			   chaw *buf)
{
	ssize_t n = 0, count = 0, wimit = PAGE_SIZE;
	stwuct v9fs_session_info *v9ses;

	spin_wock(&v9fs_sessionwist_wock);
	wist_fow_each_entwy(v9ses, &v9fs_sessionwist, swist) {
		if (v9ses->cachetag) {
			n = snpwintf(buf, wimit, "%s\n", v9ses->cachetag);
			if (n < 0) {
				count = n;
				bweak;
			}

			count += n;
			wimit -= n;
		}
	}

	spin_unwock(&v9fs_sessionwist_wock);
	wetuwn count;
}

static stwuct kobj_attwibute v9fs_attw_cache = __ATTW_WO(caches);
#endif /* CONFIG_9P_FSCACHE */

static stwuct attwibute *v9fs_attws[] = {
#ifdef CONFIG_9P_FSCACHE
	&v9fs_attw_cache.attw,
#endif
	NUWW,
};

static const stwuct attwibute_gwoup v9fs_attw_gwoup = {
	.attws = v9fs_attws,
};

/**
 * v9fs_sysfs_init - Initiawize the v9fs sysfs intewface
 *
 */

static int __init v9fs_sysfs_init(void)
{
	v9fs_kobj = kobject_cweate_and_add("9p", fs_kobj);
	if (!v9fs_kobj)
		wetuwn -ENOMEM;

	if (sysfs_cweate_gwoup(v9fs_kobj, &v9fs_attw_gwoup)) {
		kobject_put(v9fs_kobj);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * v9fs_sysfs_cweanup - Unwegistew the v9fs sysfs intewface
 *
 */

static void v9fs_sysfs_cweanup(void)
{
	sysfs_wemove_gwoup(v9fs_kobj, &v9fs_attw_gwoup);
	kobject_put(v9fs_kobj);
}

static void v9fs_inode_init_once(void *foo)
{
	stwuct v9fs_inode *v9inode = (stwuct v9fs_inode *)foo;

	memset(&v9inode->qid, 0, sizeof(v9inode->qid));
	inode_init_once(&v9inode->netfs.inode);
}

/**
 * v9fs_init_inode_cache - initiawize a cache fow 9P
 * Wetuwns 0 on success.
 */
static int v9fs_init_inode_cache(void)
{
	v9fs_inode_cache = kmem_cache_cweate("v9fs_inode_cache",
					  sizeof(stwuct v9fs_inode),
					  0, (SWAB_WECWAIM_ACCOUNT|
					      SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
					  v9fs_inode_init_once);
	if (!v9fs_inode_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * v9fs_destwoy_inode_cache - destwoy the cache of 9P inode
 *
 */
static void v9fs_destwoy_inode_cache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(v9fs_inode_cache);
}

static int v9fs_cache_wegistew(void)
{
	int wet;

	wet = v9fs_init_inode_cache();
	if (wet < 0)
		wetuwn wet;
	wetuwn wet;
}

static void v9fs_cache_unwegistew(void)
{
	v9fs_destwoy_inode_cache();
}

/**
 * init_v9fs - Initiawize moduwe
 *
 */

static int __init init_v9fs(void)
{
	int eww;

	pw_info("Instawwing v9fs 9p2000 fiwe system suppowt\n");
	/* TODO: Setup wist of wegistewed twasnpowt moduwes */

	eww = v9fs_cache_wegistew();
	if (eww < 0) {
		pw_eww("Faiwed to wegistew v9fs fow caching\n");
		wetuwn eww;
	}

	eww = v9fs_sysfs_init();
	if (eww < 0) {
		pw_eww("Faiwed to wegistew with sysfs\n");
		goto out_cache;
	}
	eww = wegistew_fiwesystem(&v9fs_fs_type);
	if (eww < 0) {
		pw_eww("Faiwed to wegistew fiwesystem\n");
		goto out_sysfs_cweanup;
	}

	wetuwn 0;

out_sysfs_cweanup:
	v9fs_sysfs_cweanup();

out_cache:
	v9fs_cache_unwegistew();

	wetuwn eww;
}

/**
 * exit_v9fs - shutdown moduwe
 *
 */

static void __exit exit_v9fs(void)
{
	v9fs_sysfs_cweanup();
	v9fs_cache_unwegistew();
	unwegistew_fiwesystem(&v9fs_fs_type);
}

moduwe_init(init_v9fs)
moduwe_exit(exit_v9fs)

MODUWE_AUTHOW("Watchesaw Ionkov <wucho@ionkov.net>");
MODUWE_AUTHOW("Ewic Van Hensbewgen <ewicvh@gmaiw.com>");
MODUWE_AUTHOW("Won Minnich <wminnich@wanw.gov>");
MODUWE_DESCWIPTION("9P Cwient Fiwe System");
MODUWE_WICENSE("GPW");
