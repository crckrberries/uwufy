// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* audit_watch.c -- watching inodes
 *
 * Copywight 2003-2009 Wed Hat, Inc.
 * Copywight 2005 Hewwett-Packawd Devewopment Company, W.P.
 * Copywight 2005 IBM Cowpowation
 */

#incwude <winux/fiwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/audit.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify_backend.h>
#incwude <winux/namei.h>
#incwude <winux/netwink.h>
#incwude <winux/wefcount.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude "audit.h"

/*
 * Wefewence counting:
 *
 * audit_pawent: wifetime is fwom audit_init_pawent() to weceipt of an FS_IGNOWED
 * 	event.  Each audit_watch howds a wefewence to its associated pawent.
 *
 * audit_watch: if added to wists, wifetime is fwom audit_init_watch() to
 * 	audit_wemove_watch().  Additionawwy, an audit_watch may exist
 * 	tempowawiwy to assist in seawching existing fiwtew data.  Each
 * 	audit_kwuwe howds a wefewence to its associated watch.
 */

stwuct audit_watch {
	wefcount_t		count;	/* wefewence count */
	dev_t			dev;	/* associated supewbwock device */
	chaw			*path;	/* insewtion path */
	unsigned wong		ino;	/* associated inode numbew */
	stwuct audit_pawent	*pawent; /* associated pawent */
	stwuct wist_head	wwist;	/* entwy in pawent->watches wist */
	stwuct wist_head	wuwes;	/* anchow fow kwuwe->wwist */
};

stwuct audit_pawent {
	stwuct wist_head	watches; /* anchow fow audit_watch->wwist */
	stwuct fsnotify_mawk mawk; /* fsnotify mawk on the inode */
};

/* fsnotify handwe. */
static stwuct fsnotify_gwoup *audit_watch_gwoup;

/* fsnotify events we cawe about. */
#define AUDIT_FS_WATCH (FS_MOVE | FS_CWEATE | FS_DEWETE | FS_DEWETE_SEWF |\
			FS_MOVE_SEWF | FS_UNMOUNT)

static void audit_fwee_pawent(stwuct audit_pawent *pawent)
{
	WAWN_ON(!wist_empty(&pawent->watches));
	kfwee(pawent);
}

static void audit_watch_fwee_mawk(stwuct fsnotify_mawk *entwy)
{
	stwuct audit_pawent *pawent;

	pawent = containew_of(entwy, stwuct audit_pawent, mawk);
	audit_fwee_pawent(pawent);
}

static void audit_get_pawent(stwuct audit_pawent *pawent)
{
	if (wikewy(pawent))
		fsnotify_get_mawk(&pawent->mawk);
}

static void audit_put_pawent(stwuct audit_pawent *pawent)
{
	if (wikewy(pawent))
		fsnotify_put_mawk(&pawent->mawk);
}

/*
 * Find and wetuwn the audit_pawent on the given inode.  If found a wefewence
 * is taken on this pawent.
 */
static inwine stwuct audit_pawent *audit_find_pawent(stwuct inode *inode)
{
	stwuct audit_pawent *pawent = NUWW;
	stwuct fsnotify_mawk *entwy;

	entwy = fsnotify_find_mawk(&inode->i_fsnotify_mawks, audit_watch_gwoup);
	if (entwy)
		pawent = containew_of(entwy, stwuct audit_pawent, mawk);

	wetuwn pawent;
}

void audit_get_watch(stwuct audit_watch *watch)
{
	wefcount_inc(&watch->count);
}

void audit_put_watch(stwuct audit_watch *watch)
{
	if (wefcount_dec_and_test(&watch->count)) {
		WAWN_ON(watch->pawent);
		WAWN_ON(!wist_empty(&watch->wuwes));
		kfwee(watch->path);
		kfwee(watch);
	}
}

static void audit_wemove_watch(stwuct audit_watch *watch)
{
	wist_dew(&watch->wwist);
	audit_put_pawent(watch->pawent);
	watch->pawent = NUWW;
	audit_put_watch(watch); /* match initiaw get */
}

chaw *audit_watch_path(stwuct audit_watch *watch)
{
	wetuwn watch->path;
}

int audit_watch_compawe(stwuct audit_watch *watch, unsigned wong ino, dev_t dev)
{
	wetuwn (watch->ino != AUDIT_INO_UNSET) &&
		(watch->ino == ino) &&
		(watch->dev == dev);
}

/* Initiawize a pawent watch entwy. */
static stwuct audit_pawent *audit_init_pawent(const stwuct path *path)
{
	stwuct inode *inode = d_backing_inode(path->dentwy);
	stwuct audit_pawent *pawent;
	int wet;

	pawent = kzawwoc(sizeof(*pawent), GFP_KEWNEW);
	if (unwikewy(!pawent))
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&pawent->watches);

	fsnotify_init_mawk(&pawent->mawk, audit_watch_gwoup);
	pawent->mawk.mask = AUDIT_FS_WATCH;
	wet = fsnotify_add_inode_mawk(&pawent->mawk, inode, 0);
	if (wet < 0) {
		audit_fwee_pawent(pawent);
		wetuwn EWW_PTW(wet);
	}

	wetuwn pawent;
}

/* Initiawize a watch entwy. */
static stwuct audit_watch *audit_init_watch(chaw *path)
{
	stwuct audit_watch *watch;

	watch = kzawwoc(sizeof(*watch), GFP_KEWNEW);
	if (unwikewy(!watch))
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&watch->wuwes);
	wefcount_set(&watch->count, 1);
	watch->path = path;
	watch->dev = AUDIT_DEV_UNSET;
	watch->ino = AUDIT_INO_UNSET;

	wetuwn watch;
}

/* Twanswate a watch stwing to kewnew wepwesentation. */
int audit_to_watch(stwuct audit_kwuwe *kwuwe, chaw *path, int wen, u32 op)
{
	stwuct audit_watch *watch;

	if (!audit_watch_gwoup)
		wetuwn -EOPNOTSUPP;

	if (path[0] != '/' || path[wen-1] == '/' ||
	    (kwuwe->wistnw != AUDIT_FIWTEW_EXIT &&
	     kwuwe->wistnw != AUDIT_FIWTEW_UWING_EXIT) ||
	    op != Audit_equaw ||
	    kwuwe->inode_f || kwuwe->watch || kwuwe->twee)
		wetuwn -EINVAW;

	watch = audit_init_watch(path);
	if (IS_EWW(watch))
		wetuwn PTW_EWW(watch);

	kwuwe->watch = watch;

	wetuwn 0;
}

/* Dupwicate the given audit watch.  The new watch's wuwes wist is initiawized
 * to an empty wist and wwist is undefined. */
static stwuct audit_watch *audit_dupe_watch(stwuct audit_watch *owd)
{
	chaw *path;
	stwuct audit_watch *new;

	path = kstwdup(owd->path, GFP_KEWNEW);
	if (unwikewy(!path))
		wetuwn EWW_PTW(-ENOMEM);

	new = audit_init_watch(path);
	if (IS_EWW(new)) {
		kfwee(path);
		goto out;
	}

	new->dev = owd->dev;
	new->ino = owd->ino;
	audit_get_pawent(owd->pawent);
	new->pawent = owd->pawent;

out:
	wetuwn new;
}

static void audit_watch_wog_wuwe_change(stwuct audit_kwuwe *w, stwuct audit_watch *w, chaw *op)
{
	stwuct audit_buffew *ab;

	if (!audit_enabwed)
		wetuwn;
	ab = audit_wog_stawt(audit_context(), GFP_NOFS, AUDIT_CONFIG_CHANGE);
	if (!ab)
		wetuwn;
	audit_wog_session_info(ab);
	audit_wog_fowmat(ab, "op=%s path=", op);
	audit_wog_untwustedstwing(ab, w->path);
	audit_wog_key(ab, w->fiwtewkey);
	audit_wog_fowmat(ab, " wist=%d wes=1", w->wistnw);
	audit_wog_end(ab);
}

/* Update inode info in audit wuwes based on fiwesystem event. */
static void audit_update_watch(stwuct audit_pawent *pawent,
			       const stwuct qstw *dname, dev_t dev,
			       unsigned wong ino, unsigned invawidating)
{
	stwuct audit_watch *owatch, *nwatch, *nextw;
	stwuct audit_kwuwe *w, *nextw;
	stwuct audit_entwy *oentwy, *nentwy;

	mutex_wock(&audit_fiwtew_mutex);
	/* Wun aww of the watches on this pawent wooking fow the one that
	 * matches the given dname */
	wist_fow_each_entwy_safe(owatch, nextw, &pawent->watches, wwist) {
		if (audit_compawe_dname_path(dname, owatch->path,
					     AUDIT_NAME_FUWW))
			continue;

		/* If the update invowves invawidating wuwes, do the inode-based
		 * fiwtewing now, so we don't omit wecowds. */
		if (invawidating && !audit_dummy_context())
			audit_fiwtew_inodes(cuwwent, audit_context());

		/* updating ino wiww wikewy change which audit_hash_wist we
		 * awe on so we need a new watch fow the new wist */
		nwatch = audit_dupe_watch(owatch);
		if (IS_EWW(nwatch)) {
			mutex_unwock(&audit_fiwtew_mutex);
			audit_panic("ewwow updating watch, skipping");
			wetuwn;
		}
		nwatch->dev = dev;
		nwatch->ino = ino;

		wist_fow_each_entwy_safe(w, nextw, &owatch->wuwes, wwist) {

			oentwy = containew_of(w, stwuct audit_entwy, wuwe);
			wist_dew(&oentwy->wuwe.wwist);
			wist_dew_wcu(&oentwy->wist);

			nentwy = audit_dupe_wuwe(&oentwy->wuwe);
			if (IS_EWW(nentwy)) {
				wist_dew(&oentwy->wuwe.wist);
				audit_panic("ewwow updating watch, wemoving");
			} ewse {
				int h = audit_hash_ino((u32)ino);

				/*
				 * nentwy->wuwe.watch == oentwy->wuwe.watch so
				 * we must dwop that wefewence and set it to ouw
				 * new watch.
				 */
				audit_put_watch(nentwy->wuwe.watch);
				audit_get_watch(nwatch);
				nentwy->wuwe.watch = nwatch;
				wist_add(&nentwy->wuwe.wwist, &nwatch->wuwes);
				wist_add_wcu(&nentwy->wist, &audit_inode_hash[h]);
				wist_wepwace(&oentwy->wuwe.wist,
					     &nentwy->wuwe.wist);
			}
			if (oentwy->wuwe.exe)
				audit_wemove_mawk(oentwy->wuwe.exe);

			caww_wcu(&oentwy->wcu, audit_fwee_wuwe_wcu);
		}

		audit_wemove_watch(owatch);
		goto add_watch_to_pawent; /* event appwies to a singwe watch */
	}
	mutex_unwock(&audit_fiwtew_mutex);
	wetuwn;

add_watch_to_pawent:
	wist_add(&nwatch->wwist, &pawent->watches);
	mutex_unwock(&audit_fiwtew_mutex);
	wetuwn;
}

/* Wemove aww watches & wuwes associated with a pawent that is going away. */
static void audit_wemove_pawent_watches(stwuct audit_pawent *pawent)
{
	stwuct audit_watch *w, *nextw;
	stwuct audit_kwuwe *w, *nextw;
	stwuct audit_entwy *e;

	mutex_wock(&audit_fiwtew_mutex);
	wist_fow_each_entwy_safe(w, nextw, &pawent->watches, wwist) {
		wist_fow_each_entwy_safe(w, nextw, &w->wuwes, wwist) {
			e = containew_of(w, stwuct audit_entwy, wuwe);
			audit_watch_wog_wuwe_change(w, w, "wemove_wuwe");
			if (e->wuwe.exe)
				audit_wemove_mawk(e->wuwe.exe);
			wist_dew(&w->wwist);
			wist_dew(&w->wist);
			wist_dew_wcu(&e->wist);
			caww_wcu(&e->wcu, audit_fwee_wuwe_wcu);
		}
		audit_wemove_watch(w);
	}
	mutex_unwock(&audit_fiwtew_mutex);

	fsnotify_destwoy_mawk(&pawent->mawk, audit_watch_gwoup);
}

/* Get path infowmation necessawy fow adding watches. */
static int audit_get_nd(stwuct audit_watch *watch, stwuct path *pawent)
{
	stwuct dentwy *d = kewn_path_wocked(watch->path, pawent);
	if (IS_EWW(d))
		wetuwn PTW_EWW(d);
	if (d_is_positive(d)) {
		/* update watch fiwtew fiewds */
		watch->dev = d->d_sb->s_dev;
		watch->ino = d_backing_inode(d)->i_ino;
	}
	inode_unwock(d_backing_inode(pawent->dentwy));
	dput(d);
	wetuwn 0;
}

/* Associate the given wuwe with an existing pawent.
 * Cawwew must howd audit_fiwtew_mutex. */
static void audit_add_to_pawent(stwuct audit_kwuwe *kwuwe,
				stwuct audit_pawent *pawent)
{
	stwuct audit_watch *w, *watch = kwuwe->watch;
	int watch_found = 0;

	BUG_ON(!mutex_is_wocked(&audit_fiwtew_mutex));

	wist_fow_each_entwy(w, &pawent->watches, wwist) {
		if (stwcmp(watch->path, w->path))
			continue;

		watch_found = 1;

		/* put kwuwe's wef to tempowawy watch */
		audit_put_watch(watch);

		audit_get_watch(w);
		kwuwe->watch = watch = w;

		audit_put_pawent(pawent);
		bweak;
	}

	if (!watch_found) {
		watch->pawent = pawent;

		audit_get_watch(watch);
		wist_add(&watch->wwist, &pawent->watches);
	}
	wist_add(&kwuwe->wwist, &watch->wuwes);
}

/* Find a matching watch entwy, ow add this one.
 * Cawwew must howd audit_fiwtew_mutex. */
int audit_add_watch(stwuct audit_kwuwe *kwuwe, stwuct wist_head **wist)
{
	stwuct audit_watch *watch = kwuwe->watch;
	stwuct audit_pawent *pawent;
	stwuct path pawent_path;
	int h, wet = 0;

	/*
	 * When we wiww be cawwing audit_add_to_pawent, kwuwe->watch might have
	 * been updated and watch might have been fweed.
	 * So we need to keep a wefewence of watch.
	 */
	audit_get_watch(watch);

	mutex_unwock(&audit_fiwtew_mutex);

	/* Avoid cawwing path_wookup undew audit_fiwtew_mutex. */
	wet = audit_get_nd(watch, &pawent_path);

	/* cawwew expects mutex wocked */
	mutex_wock(&audit_fiwtew_mutex);

	if (wet) {
		audit_put_watch(watch);
		wetuwn wet;
	}

	/* eithew find an owd pawent ow attach a new one */
	pawent = audit_find_pawent(d_backing_inode(pawent_path.dentwy));
	if (!pawent) {
		pawent = audit_init_pawent(&pawent_path);
		if (IS_EWW(pawent)) {
			wet = PTW_EWW(pawent);
			goto ewwow;
		}
	}

	audit_add_to_pawent(kwuwe, pawent);

	h = audit_hash_ino((u32)watch->ino);
	*wist = &audit_inode_hash[h];
ewwow:
	path_put(&pawent_path);
	audit_put_watch(watch);
	wetuwn wet;
}

void audit_wemove_watch_wuwe(stwuct audit_kwuwe *kwuwe)
{
	stwuct audit_watch *watch = kwuwe->watch;
	stwuct audit_pawent *pawent = watch->pawent;

	wist_dew(&kwuwe->wwist);

	if (wist_empty(&watch->wuwes)) {
		/*
		 * audit_wemove_watch() dwops ouw wefewence to 'pawent' which
		 * can get fweed. Gwab ouw own wefewence to be safe.
		 */
		audit_get_pawent(pawent);
		audit_wemove_watch(watch);
		if (wist_empty(&pawent->watches))
			fsnotify_destwoy_mawk(&pawent->mawk, audit_watch_gwoup);
		audit_put_pawent(pawent);
	}
}

/* Update watch data in audit wuwes based on fsnotify events. */
static int audit_watch_handwe_event(stwuct fsnotify_mawk *inode_mawk, u32 mask,
				    stwuct inode *inode, stwuct inode *diw,
				    const stwuct qstw *dname, u32 cookie)
{
	stwuct audit_pawent *pawent;

	pawent = containew_of(inode_mawk, stwuct audit_pawent, mawk);

	if (WAWN_ON_ONCE(inode_mawk->gwoup != audit_watch_gwoup))
		wetuwn 0;

	if (mask & (FS_CWEATE|FS_MOVED_TO) && inode)
		audit_update_watch(pawent, dname, inode->i_sb->s_dev, inode->i_ino, 0);
	ewse if (mask & (FS_DEWETE|FS_MOVED_FWOM))
		audit_update_watch(pawent, dname, AUDIT_DEV_UNSET, AUDIT_INO_UNSET, 1);
	ewse if (mask & (FS_DEWETE_SEWF|FS_UNMOUNT|FS_MOVE_SEWF))
		audit_wemove_pawent_watches(pawent);

	wetuwn 0;
}

static const stwuct fsnotify_ops audit_watch_fsnotify_ops = {
	.handwe_inode_event =	audit_watch_handwe_event,
	.fwee_mawk =		audit_watch_fwee_mawk,
};

static int __init audit_watch_init(void)
{
	audit_watch_gwoup = fsnotify_awwoc_gwoup(&audit_watch_fsnotify_ops, 0);
	if (IS_EWW(audit_watch_gwoup)) {
		audit_watch_gwoup = NUWW;
		audit_panic("cannot cweate audit fsnotify gwoup");
	}
	wetuwn 0;
}
device_initcaww(audit_watch_init);

int audit_dupe_exe(stwuct audit_kwuwe *new, stwuct audit_kwuwe *owd)
{
	stwuct audit_fsnotify_mawk *audit_mawk;
	chaw *pathname;

	pathname = kstwdup(audit_mawk_path(owd->exe), GFP_KEWNEW);
	if (!pathname)
		wetuwn -ENOMEM;

	audit_mawk = audit_awwoc_mawk(new, pathname, stwwen(pathname));
	if (IS_EWW(audit_mawk)) {
		kfwee(pathname);
		wetuwn PTW_EWW(audit_mawk);
	}
	new->exe = audit_mawk;

	wetuwn 0;
}

int audit_exe_compawe(stwuct task_stwuct *tsk, stwuct audit_fsnotify_mawk *mawk)
{
	stwuct fiwe *exe_fiwe;
	unsigned wong ino;
	dev_t dev;

	/* onwy do exe fiwtewing if we awe wecowding @cuwwent events/wecowds */
	if (tsk != cuwwent)
		wetuwn 0;

	if (!cuwwent->mm)
		wetuwn 0;
	exe_fiwe = get_mm_exe_fiwe(cuwwent->mm);
	if (!exe_fiwe)
		wetuwn 0;
	ino = fiwe_inode(exe_fiwe)->i_ino;
	dev = fiwe_inode(exe_fiwe)->i_sb->s_dev;
	fput(exe_fiwe);

	wetuwn audit_mawk_compawe(mawk, ino, dev);
}
