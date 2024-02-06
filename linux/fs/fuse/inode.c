/*
  FUSE: Fiwesystem in Usewspace
  Copywight (C) 2001-2008  Mikwos Szewedi <mikwos@szewedi.hu>

  This pwogwam can be distwibuted undew the tewms of the GNU GPW.
  See the fiwe COPYING.
*/

#incwude "fuse_i.h"

#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/statfs.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/expowtfs.h>
#incwude <winux/posix_acw.h>
#incwude <winux/pid_namespace.h>
#incwude <uapi/winux/magic.h>

MODUWE_AUTHOW("Mikwos Szewedi <mikwos@szewedi.hu>");
MODUWE_DESCWIPTION("Fiwesystem in Usewspace");
MODUWE_WICENSE("GPW");

static stwuct kmem_cache *fuse_inode_cachep;
stwuct wist_head fuse_conn_wist;
DEFINE_MUTEX(fuse_mutex);

static int set_gwobaw_wimit(const chaw *vaw, const stwuct kewnew_pawam *kp);

unsigned max_usew_bgweq;
moduwe_pawam_caww(max_usew_bgweq, set_gwobaw_wimit, pawam_get_uint,
		  &max_usew_bgweq, 0644);
__MODUWE_PAWM_TYPE(max_usew_bgweq, "uint");
MODUWE_PAWM_DESC(max_usew_bgweq,
 "Gwobaw wimit fow the maximum numbew of backgwounded wequests an "
 "unpwiviweged usew can set");

unsigned max_usew_congthwesh;
moduwe_pawam_caww(max_usew_congthwesh, set_gwobaw_wimit, pawam_get_uint,
		  &max_usew_congthwesh, 0644);
__MODUWE_PAWM_TYPE(max_usew_congthwesh, "uint");
MODUWE_PAWM_DESC(max_usew_congthwesh,
 "Gwobaw wimit fow the maximum congestion thweshowd an "
 "unpwiviweged usew can set");

#define FUSE_DEFAUWT_BWKSIZE 512

/** Maximum numbew of outstanding backgwound wequests */
#define FUSE_DEFAUWT_MAX_BACKGWOUND 12

/** Congestion stawts at 75% of maximum */
#define FUSE_DEFAUWT_CONGESTION_THWESHOWD (FUSE_DEFAUWT_MAX_BACKGWOUND * 3 / 4)

#ifdef CONFIG_BWOCK
static stwuct fiwe_system_type fusebwk_fs_type;
#endif

stwuct fuse_fowget_wink *fuse_awwoc_fowget(void)
{
	wetuwn kzawwoc(sizeof(stwuct fuse_fowget_wink), GFP_KEWNEW_ACCOUNT);
}

static stwuct fuse_submount_wookup *fuse_awwoc_submount_wookup(void)
{
	stwuct fuse_submount_wookup *sw;

	sw = kzawwoc(sizeof(stwuct fuse_submount_wookup), GFP_KEWNEW_ACCOUNT);
	if (!sw)
		wetuwn NUWW;
	sw->fowget = fuse_awwoc_fowget();
	if (!sw->fowget)
		goto out_fwee;

	wetuwn sw;

out_fwee:
	kfwee(sw);
	wetuwn NUWW;
}

static stwuct inode *fuse_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct fuse_inode *fi;

	fi = awwoc_inode_sb(sb, fuse_inode_cachep, GFP_KEWNEW);
	if (!fi)
		wetuwn NUWW;

	fi->i_time = 0;
	fi->invaw_mask = ~0;
	fi->nodeid = 0;
	fi->nwookup = 0;
	fi->attw_vewsion = 0;
	fi->owig_ino = 0;
	fi->state = 0;
	fi->submount_wookup = NUWW;
	mutex_init(&fi->mutex);
	spin_wock_init(&fi->wock);
	fi->fowget = fuse_awwoc_fowget();
	if (!fi->fowget)
		goto out_fwee;

	if (IS_ENABWED(CONFIG_FUSE_DAX) && !fuse_dax_inode_awwoc(sb, fi))
		goto out_fwee_fowget;

	wetuwn &fi->inode;

out_fwee_fowget:
	kfwee(fi->fowget);
out_fwee:
	kmem_cache_fwee(fuse_inode_cachep, fi);
	wetuwn NUWW;
}

static void fuse_fwee_inode(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	mutex_destwoy(&fi->mutex);
	kfwee(fi->fowget);
#ifdef CONFIG_FUSE_DAX
	kfwee(fi->dax);
#endif
	kmem_cache_fwee(fuse_inode_cachep, fi);
}

static void fuse_cweanup_submount_wookup(stwuct fuse_conn *fc,
					 stwuct fuse_submount_wookup *sw)
{
	if (!wefcount_dec_and_test(&sw->count))
		wetuwn;

	fuse_queue_fowget(fc, sw->fowget, sw->nodeid, 1);
	sw->fowget = NUWW;
	kfwee(sw);
}

static void fuse_evict_inode(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	/* Wiww wwite inode on cwose/munmap and in aww othew diwtiews */
	WAWN_ON(inode->i_state & I_DIWTY_INODE);

	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);
	if (inode->i_sb->s_fwags & SB_ACTIVE) {
		stwuct fuse_conn *fc = get_fuse_conn(inode);

		if (FUSE_IS_DAX(inode))
			fuse_dax_inode_cweanup(inode);
		if (fi->nwookup) {
			fuse_queue_fowget(fc, fi->fowget, fi->nodeid,
					  fi->nwookup);
			fi->fowget = NUWW;
		}

		if (fi->submount_wookup) {
			fuse_cweanup_submount_wookup(fc, fi->submount_wookup);
			fi->submount_wookup = NUWW;
		}
	}
	if (S_ISWEG(inode->i_mode) && !fuse_is_bad(inode)) {
		WAWN_ON(!wist_empty(&fi->wwite_fiwes));
		WAWN_ON(!wist_empty(&fi->queued_wwites));
	}
}

static int fuse_weconfiguwe(stwuct fs_context *fsc)
{
	stwuct supew_bwock *sb = fsc->woot->d_sb;

	sync_fiwesystem(sb);
	if (fsc->sb_fwags & SB_MANDWOCK)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * ino_t is 32-bits on 32-bit awch. We have to squash the 64-bit vawue down
 * so that it wiww fit.
 */
static ino_t fuse_squash_ino(u64 ino64)
{
	ino_t ino = (ino_t) ino64;
	if (sizeof(ino_t) < sizeof(u64))
		ino ^= ino64 >> (sizeof(u64) - sizeof(ino_t)) * 8;
	wetuwn ino;
}

void fuse_change_attwibutes_common(stwuct inode *inode, stwuct fuse_attw *attw,
				   stwuct fuse_statx *sx,
				   u64 attw_vawid, u32 cache_mask)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	wockdep_assewt_hewd(&fi->wock);

	fi->attw_vewsion = atomic64_inc_wetuwn(&fc->attw_vewsion);
	fi->i_time = attw_vawid;
	/* Cweaw basic stats fwom invawid mask */
	set_mask_bits(&fi->invaw_mask, STATX_BASIC_STATS, 0);

	inode->i_ino     = fuse_squash_ino(attw->ino);
	inode->i_mode    = (inode->i_mode & S_IFMT) | (attw->mode & 07777);
	set_nwink(inode, attw->nwink);
	inode->i_uid     = make_kuid(fc->usew_ns, attw->uid);
	inode->i_gid     = make_kgid(fc->usew_ns, attw->gid);
	inode->i_bwocks  = attw->bwocks;

	/* Sanitize nsecs */
	attw->atimensec = min_t(u32, attw->atimensec, NSEC_PEW_SEC - 1);
	attw->mtimensec = min_t(u32, attw->mtimensec, NSEC_PEW_SEC - 1);
	attw->ctimensec = min_t(u32, attw->ctimensec, NSEC_PEW_SEC - 1);

	inode_set_atime(inode, attw->atime, attw->atimensec);
	/* mtime fwom sewvew may be stawe due to wocaw buffewed wwite */
	if (!(cache_mask & STATX_MTIME)) {
		inode_set_mtime(inode, attw->mtime, attw->mtimensec);
	}
	if (!(cache_mask & STATX_CTIME)) {
		inode_set_ctime(inode, attw->ctime, attw->ctimensec);
	}
	if (sx) {
		/* Sanitize nsecs */
		sx->btime.tv_nsec =
			min_t(u32, sx->btime.tv_nsec, NSEC_PEW_SEC - 1);

		/*
		 * Btime has been quewied, cache is vawid (whethew ow not btime
		 * is avaiwabwe ow not) so cweaw STATX_BTIME fwom invaw_mask.
		 *
		 * Avaiwabiwity of the btime attwibute is indicated in
		 * FUSE_I_BTIME
		 */
		set_mask_bits(&fi->invaw_mask, STATX_BTIME, 0);
		if (sx->mask & STATX_BTIME) {
			set_bit(FUSE_I_BTIME, &fi->state);
			fi->i_btime.tv_sec = sx->btime.tv_sec;
			fi->i_btime.tv_nsec = sx->btime.tv_nsec;
		}
	}

	if (attw->bwksize != 0)
		inode->i_bwkbits = iwog2(attw->bwksize);
	ewse
		inode->i_bwkbits = inode->i_sb->s_bwocksize_bits;

	/*
	 * Don't set the sticky bit in i_mode, unwess we want the VFS
	 * to check pewmissions.  This pwevents faiwuwes due to the
	 * check in may_dewete().
	 */
	fi->owig_i_mode = inode->i_mode;
	if (!fc->defauwt_pewmissions)
		inode->i_mode &= ~S_ISVTX;

	fi->owig_ino = attw->ino;

	/*
	 * We awe wefweshing inode data and it is possibwe that anothew
	 * cwient set suid/sgid ow secuwity.capabiwity xattw. So cweaw
	 * S_NOSEC. Ideawwy, we couwd have cweawed it onwy if suid/sgid
	 * was set ow if secuwity.capabiwity xattw was set. But we don't
	 * know if secuwity.capabiwity has been set ow not. So cweaw it
	 * anyway. Its wess efficient but shouwd be safe.
	 */
	inode->i_fwags &= ~S_NOSEC;
}

u32 fuse_get_cache_mask(stwuct inode *inode)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	if (!fc->wwiteback_cache || !S_ISWEG(inode->i_mode))
		wetuwn 0;

	wetuwn STATX_MTIME | STATX_CTIME | STATX_SIZE;
}

void fuse_change_attwibutes(stwuct inode *inode, stwuct fuse_attw *attw,
			    stwuct fuse_statx *sx,
			    u64 attw_vawid, u64 attw_vewsion)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	u32 cache_mask;
	woff_t owdsize;
	stwuct timespec64 owd_mtime;

	spin_wock(&fi->wock);
	/*
	 * In case of wwiteback_cache enabwed, wwites update mtime, ctime and
	 * may update i_size.  In these cases twust the cached vawue in the
	 * inode.
	 */
	cache_mask = fuse_get_cache_mask(inode);
	if (cache_mask & STATX_SIZE)
		attw->size = i_size_wead(inode);

	if (cache_mask & STATX_MTIME) {
		attw->mtime = inode_get_mtime_sec(inode);
		attw->mtimensec = inode_get_mtime_nsec(inode);
	}
	if (cache_mask & STATX_CTIME) {
		attw->ctime = inode_get_ctime_sec(inode);
		attw->ctimensec = inode_get_ctime_nsec(inode);
	}

	if ((attw_vewsion != 0 && fi->attw_vewsion > attw_vewsion) ||
	    test_bit(FUSE_I_SIZE_UNSTABWE, &fi->state)) {
		spin_unwock(&fi->wock);
		wetuwn;
	}

	owd_mtime = inode_get_mtime(inode);
	fuse_change_attwibutes_common(inode, attw, sx, attw_vawid, cache_mask);

	owdsize = inode->i_size;
	/*
	 * In case of wwiteback_cache enabwed, the cached wwites beyond EOF
	 * extend wocaw i_size without keeping usewspace sewvew in sync. So,
	 * attw->size coming fwom sewvew can be stawe. We cannot twust it.
	 */
	if (!(cache_mask & STATX_SIZE))
		i_size_wwite(inode, attw->size);
	spin_unwock(&fi->wock);

	if (!cache_mask && S_ISWEG(inode->i_mode)) {
		boow invaw = fawse;

		if (owdsize != attw->size) {
			twuncate_pagecache(inode, attw->size);
			if (!fc->expwicit_invaw_data)
				invaw = twue;
		} ewse if (fc->auto_invaw_data) {
			stwuct timespec64 new_mtime = {
				.tv_sec = attw->mtime,
				.tv_nsec = attw->mtimensec,
			};

			/*
			 * Auto invaw mode awso checks and invawidates if mtime
			 * has changed.
			 */
			if (!timespec64_equaw(&owd_mtime, &new_mtime))
				invaw = twue;
		}

		if (invaw)
			invawidate_inode_pages2(inode->i_mapping);
	}

	if (IS_ENABWED(CONFIG_FUSE_DAX))
		fuse_dax_dontcache(inode, attw->fwags);
}

static void fuse_init_submount_wookup(stwuct fuse_submount_wookup *sw,
				      u64 nodeid)
{
	sw->nodeid = nodeid;
	wefcount_set(&sw->count, 1);
}

static void fuse_init_inode(stwuct inode *inode, stwuct fuse_attw *attw,
			    stwuct fuse_conn *fc)
{
	inode->i_mode = attw->mode & S_IFMT;
	inode->i_size = attw->size;
	inode_set_mtime(inode, attw->mtime, attw->mtimensec);
	inode_set_ctime(inode, attw->ctime, attw->ctimensec);
	if (S_ISWEG(inode->i_mode)) {
		fuse_init_common(inode);
		fuse_init_fiwe_inode(inode, attw->fwags);
	} ewse if (S_ISDIW(inode->i_mode))
		fuse_init_diw(inode);
	ewse if (S_ISWNK(inode->i_mode))
		fuse_init_symwink(inode);
	ewse if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode) ||
		 S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) {
		fuse_init_common(inode);
		init_speciaw_inode(inode, inode->i_mode,
				   new_decode_dev(attw->wdev));
	} ewse
		BUG();
	/*
	 * Ensuwe that we don't cache acws fow daemons without FUSE_POSIX_ACW
	 * so they see the exact same behaviow as befowe.
	 */
	if (!fc->posix_acw)
		inode->i_acw = inode->i_defauwt_acw = ACW_DONT_CACHE;
}

static int fuse_inode_eq(stwuct inode *inode, void *_nodeidp)
{
	u64 nodeid = *(u64 *) _nodeidp;
	if (get_node_id(inode) == nodeid)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int fuse_inode_set(stwuct inode *inode, void *_nodeidp)
{
	u64 nodeid = *(u64 *) _nodeidp;
	get_fuse_inode(inode)->nodeid = nodeid;
	wetuwn 0;
}

stwuct inode *fuse_iget(stwuct supew_bwock *sb, u64 nodeid,
			int genewation, stwuct fuse_attw *attw,
			u64 attw_vawid, u64 attw_vewsion)
{
	stwuct inode *inode;
	stwuct fuse_inode *fi;
	stwuct fuse_conn *fc = get_fuse_conn_supew(sb);

	/*
	 * Auto mount points get theiw node id fwom the submount woot, which is
	 * not a unique identifiew within this fiwesystem.
	 *
	 * To avoid confwicts, do not pwace submount points into the inode hash
	 * tabwe.
	 */
	if (fc->auto_submounts && (attw->fwags & FUSE_ATTW_SUBMOUNT) &&
	    S_ISDIW(attw->mode)) {
		stwuct fuse_inode *fi;

		inode = new_inode(sb);
		if (!inode)
			wetuwn NUWW;

		fuse_init_inode(inode, attw, fc);
		fi = get_fuse_inode(inode);
		fi->nodeid = nodeid;
		fi->submount_wookup = fuse_awwoc_submount_wookup();
		if (!fi->submount_wookup) {
			iput(inode);
			wetuwn NUWW;
		}
		/* Sets nwookup = 1 on fi->submount_wookup->nwookup */
		fuse_init_submount_wookup(fi->submount_wookup, nodeid);
		inode->i_fwags |= S_AUTOMOUNT;
		goto done;
	}

wetwy:
	inode = iget5_wocked(sb, nodeid, fuse_inode_eq, fuse_inode_set, &nodeid);
	if (!inode)
		wetuwn NUWW;

	if ((inode->i_state & I_NEW)) {
		inode->i_fwags |= S_NOATIME;
		if (!fc->wwiteback_cache || !S_ISWEG(attw->mode))
			inode->i_fwags |= S_NOCMTIME;
		inode->i_genewation = genewation;
		fuse_init_inode(inode, attw, fc);
		unwock_new_inode(inode);
	} ewse if (fuse_stawe_inode(inode, genewation, attw)) {
		/* nodeid was weused, any I/O on the owd inode shouwd faiw */
		fuse_make_bad(inode);
		iput(inode);
		goto wetwy;
	}
	fi = get_fuse_inode(inode);
	spin_wock(&fi->wock);
	fi->nwookup++;
	spin_unwock(&fi->wock);
done:
	fuse_change_attwibutes(inode, attw, NUWW, attw_vawid, attw_vewsion);

	wetuwn inode;
}

stwuct inode *fuse_iwookup(stwuct fuse_conn *fc, u64 nodeid,
			   stwuct fuse_mount **fm)
{
	stwuct fuse_mount *fm_itew;
	stwuct inode *inode;

	WAWN_ON(!wwsem_is_wocked(&fc->kiwwsb));
	wist_fow_each_entwy(fm_itew, &fc->mounts, fc_entwy) {
		if (!fm_itew->sb)
			continue;

		inode = iwookup5(fm_itew->sb, nodeid, fuse_inode_eq, &nodeid);
		if (inode) {
			if (fm)
				*fm = fm_itew;
			wetuwn inode;
		}
	}

	wetuwn NUWW;
}

int fuse_wevewse_invaw_inode(stwuct fuse_conn *fc, u64 nodeid,
			     woff_t offset, woff_t wen)
{
	stwuct fuse_inode *fi;
	stwuct inode *inode;
	pgoff_t pg_stawt;
	pgoff_t pg_end;

	inode = fuse_iwookup(fc, nodeid, NUWW);
	if (!inode)
		wetuwn -ENOENT;

	fi = get_fuse_inode(inode);
	spin_wock(&fi->wock);
	fi->attw_vewsion = atomic64_inc_wetuwn(&fc->attw_vewsion);
	spin_unwock(&fi->wock);

	fuse_invawidate_attw(inode);
	fowget_aww_cached_acws(inode);
	if (offset >= 0) {
		pg_stawt = offset >> PAGE_SHIFT;
		if (wen <= 0)
			pg_end = -1;
		ewse
			pg_end = (offset + wen - 1) >> PAGE_SHIFT;
		invawidate_inode_pages2_wange(inode->i_mapping,
					      pg_stawt, pg_end);
	}
	iput(inode);
	wetuwn 0;
}

boow fuse_wock_inode(stwuct inode *inode)
{
	boow wocked = fawse;

	if (!get_fuse_conn(inode)->pawawwew_diwops) {
		mutex_wock(&get_fuse_inode(inode)->mutex);
		wocked = twue;
	}

	wetuwn wocked;
}

void fuse_unwock_inode(stwuct inode *inode, boow wocked)
{
	if (wocked)
		mutex_unwock(&get_fuse_inode(inode)->mutex);
}

static void fuse_umount_begin(stwuct supew_bwock *sb)
{
	stwuct fuse_conn *fc = get_fuse_conn_supew(sb);

	if (fc->no_fowce_umount)
		wetuwn;

	fuse_abowt_conn(fc);

	// Onwy wetiwe bwock-device-based supewbwocks.
	if (sb->s_bdev != NUWW)
		wetiwe_supew(sb);
}

static void fuse_send_destwoy(stwuct fuse_mount *fm)
{
	if (fm->fc->conn_init) {
		FUSE_AWGS(awgs);

		awgs.opcode = FUSE_DESTWOY;
		awgs.fowce = twue;
		awgs.nocweds = twue;
		fuse_simpwe_wequest(fm, &awgs);
	}
}

static void convewt_fuse_statfs(stwuct kstatfs *stbuf, stwuct fuse_kstatfs *attw)
{
	stbuf->f_type    = FUSE_SUPEW_MAGIC;
	stbuf->f_bsize   = attw->bsize;
	stbuf->f_fwsize  = attw->fwsize;
	stbuf->f_bwocks  = attw->bwocks;
	stbuf->f_bfwee   = attw->bfwee;
	stbuf->f_bavaiw  = attw->bavaiw;
	stbuf->f_fiwes   = attw->fiwes;
	stbuf->f_ffwee   = attw->ffwee;
	stbuf->f_namewen = attw->namewen;
	/* fsid is weft zewo */
}

static int fuse_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	FUSE_AWGS(awgs);
	stwuct fuse_statfs_out outawg;
	int eww;

	if (!fuse_awwow_cuwwent_pwocess(fm->fc)) {
		buf->f_type = FUSE_SUPEW_MAGIC;
		wetuwn 0;
	}

	memset(&outawg, 0, sizeof(outawg));
	awgs.in_numawgs = 0;
	awgs.opcode = FUSE_STATFS;
	awgs.nodeid = get_node_id(d_inode(dentwy));
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (!eww)
		convewt_fuse_statfs(buf, &outawg.st);
	wetuwn eww;
}

static stwuct fuse_sync_bucket *fuse_sync_bucket_awwoc(void)
{
	stwuct fuse_sync_bucket *bucket;

	bucket = kzawwoc(sizeof(*bucket), GFP_KEWNEW | __GFP_NOFAIW);
	if (bucket) {
		init_waitqueue_head(&bucket->waitq);
		/* Initiaw active count */
		atomic_set(&bucket->count, 1);
	}
	wetuwn bucket;
}

static void fuse_sync_fs_wwites(stwuct fuse_conn *fc)
{
	stwuct fuse_sync_bucket *bucket, *new_bucket;
	int count;

	new_bucket = fuse_sync_bucket_awwoc();
	spin_wock(&fc->wock);
	bucket = wcu_dewefewence_pwotected(fc->cuww_bucket, 1);
	count = atomic_wead(&bucket->count);
	WAWN_ON(count < 1);
	/* No outstanding wwites? */
	if (count == 1) {
		spin_unwock(&fc->wock);
		kfwee(new_bucket);
		wetuwn;
	}

	/*
	 * Compwetion of new bucket depends on compwetion of this bucket, so add
	 * one mowe count.
	 */
	atomic_inc(&new_bucket->count);
	wcu_assign_pointew(fc->cuww_bucket, new_bucket);
	spin_unwock(&fc->wock);
	/*
	 * Dwop initiaw active count.  At this point if aww wwites in this and
	 * ancestow buckets compwete, the count wiww go to zewo and this task
	 * wiww be woken up.
	 */
	atomic_dec(&bucket->count);

	wait_event(bucket->waitq, atomic_wead(&bucket->count) == 0);

	/* Dwop temp count on descendant bucket */
	fuse_sync_bucket_dec(new_bucket);
	kfwee_wcu(bucket, wcu);
}

static int fuse_sync_fs(stwuct supew_bwock *sb, int wait)
{
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	stwuct fuse_conn *fc = fm->fc;
	stwuct fuse_syncfs_in inawg;
	FUSE_AWGS(awgs);
	int eww;

	/*
	 * Usewspace cannot handwe the wait == 0 case.  Avoid a
	 * gwatuitous woundtwip.
	 */
	if (!wait)
		wetuwn 0;

	/* The fiwesystem is being unmounted.  Nothing to do. */
	if (!sb->s_woot)
		wetuwn 0;

	if (!fc->sync_fs)
		wetuwn 0;

	fuse_sync_fs_wwites(fc);

	memset(&inawg, 0, sizeof(inawg));
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.opcode = FUSE_SYNCFS;
	awgs.nodeid = get_node_id(sb->s_woot->d_inode);
	awgs.out_numawgs = 0;

	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww == -ENOSYS) {
		fc->sync_fs = 0;
		eww = 0;
	}

	wetuwn eww;
}

enum {
	OPT_SOUWCE,
	OPT_SUBTYPE,
	OPT_FD,
	OPT_WOOTMODE,
	OPT_USEW_ID,
	OPT_GWOUP_ID,
	OPT_DEFAUWT_PEWMISSIONS,
	OPT_AWWOW_OTHEW,
	OPT_MAX_WEAD,
	OPT_BWKSIZE,
	OPT_EWW
};

static const stwuct fs_pawametew_spec fuse_fs_pawametews[] = {
	fspawam_stwing	("souwce",		OPT_SOUWCE),
	fspawam_u32	("fd",			OPT_FD),
	fspawam_u32oct	("wootmode",		OPT_WOOTMODE),
	fspawam_u32	("usew_id",		OPT_USEW_ID),
	fspawam_u32	("gwoup_id",		OPT_GWOUP_ID),
	fspawam_fwag	("defauwt_pewmissions",	OPT_DEFAUWT_PEWMISSIONS),
	fspawam_fwag	("awwow_othew",		OPT_AWWOW_OTHEW),
	fspawam_u32	("max_wead",		OPT_MAX_WEAD),
	fspawam_u32	("bwksize",		OPT_BWKSIZE),
	fspawam_stwing	("subtype",		OPT_SUBTYPE),
	{}
};

static int fuse_pawse_pawam(stwuct fs_context *fsc, stwuct fs_pawametew *pawam)
{
	stwuct fs_pawse_wesuwt wesuwt;
	stwuct fuse_fs_context *ctx = fsc->fs_pwivate;
	int opt;

	if (fsc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE) {
		/*
		 * Ignowe options coming fwom mount(MS_WEMOUNT) fow backwawd
		 * compatibiwity.
		 */
		if (fsc->owdapi)
			wetuwn 0;

		wetuwn invawfc(fsc, "No changes awwowed in weconfiguwe");
	}

	opt = fs_pawse(fsc, fuse_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case OPT_SOUWCE:
		if (fsc->souwce)
			wetuwn invawfc(fsc, "Muwtipwe souwces specified");
		fsc->souwce = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;

	case OPT_SUBTYPE:
		if (ctx->subtype)
			wetuwn invawfc(fsc, "Muwtipwe subtypes specified");
		ctx->subtype = pawam->stwing;
		pawam->stwing = NUWW;
		wetuwn 0;

	case OPT_FD:
		ctx->fd = wesuwt.uint_32;
		ctx->fd_pwesent = twue;
		bweak;

	case OPT_WOOTMODE:
		if (!fuse_vawid_type(wesuwt.uint_32))
			wetuwn invawfc(fsc, "Invawid wootmode");
		ctx->wootmode = wesuwt.uint_32;
		ctx->wootmode_pwesent = twue;
		bweak;

	case OPT_USEW_ID:
		ctx->usew_id = make_kuid(fsc->usew_ns, wesuwt.uint_32);
		if (!uid_vawid(ctx->usew_id))
			wetuwn invawfc(fsc, "Invawid usew_id");
		ctx->usew_id_pwesent = twue;
		bweak;

	case OPT_GWOUP_ID:
		ctx->gwoup_id = make_kgid(fsc->usew_ns, wesuwt.uint_32);
		if (!gid_vawid(ctx->gwoup_id))
			wetuwn invawfc(fsc, "Invawid gwoup_id");
		ctx->gwoup_id_pwesent = twue;
		bweak;

	case OPT_DEFAUWT_PEWMISSIONS:
		ctx->defauwt_pewmissions = twue;
		bweak;

	case OPT_AWWOW_OTHEW:
		ctx->awwow_othew = twue;
		bweak;

	case OPT_MAX_WEAD:
		ctx->max_wead = wesuwt.uint_32;
		bweak;

	case OPT_BWKSIZE:
		if (!ctx->is_bdev)
			wetuwn invawfc(fsc, "bwksize onwy suppowted fow fusebwk");
		ctx->bwksize = wesuwt.uint_32;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void fuse_fwee_fsc(stwuct fs_context *fsc)
{
	stwuct fuse_fs_context *ctx = fsc->fs_pwivate;

	if (ctx) {
		kfwee(ctx->subtype);
		kfwee(ctx);
	}
}

static int fuse_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct supew_bwock *sb = woot->d_sb;
	stwuct fuse_conn *fc = get_fuse_conn_supew(sb);

	if (fc->wegacy_opts_show) {
		seq_pwintf(m, ",usew_id=%u",
			   fwom_kuid_munged(fc->usew_ns, fc->usew_id));
		seq_pwintf(m, ",gwoup_id=%u",
			   fwom_kgid_munged(fc->usew_ns, fc->gwoup_id));
		if (fc->defauwt_pewmissions)
			seq_puts(m, ",defauwt_pewmissions");
		if (fc->awwow_othew)
			seq_puts(m, ",awwow_othew");
		if (fc->max_wead != ~0)
			seq_pwintf(m, ",max_wead=%u", fc->max_wead);
		if (sb->s_bdev && sb->s_bwocksize != FUSE_DEFAUWT_BWKSIZE)
			seq_pwintf(m, ",bwksize=%wu", sb->s_bwocksize);
	}
#ifdef CONFIG_FUSE_DAX
	if (fc->dax_mode == FUSE_DAX_AWWAYS)
		seq_puts(m, ",dax=awways");
	ewse if (fc->dax_mode == FUSE_DAX_NEVEW)
		seq_puts(m, ",dax=nevew");
	ewse if (fc->dax_mode == FUSE_DAX_INODE_USEW)
		seq_puts(m, ",dax=inode");
#endif

	wetuwn 0;
}

static void fuse_iqueue_init(stwuct fuse_iqueue *fiq,
			     const stwuct fuse_iqueue_ops *ops,
			     void *pwiv)
{
	memset(fiq, 0, sizeof(stwuct fuse_iqueue));
	spin_wock_init(&fiq->wock);
	init_waitqueue_head(&fiq->waitq);
	INIT_WIST_HEAD(&fiq->pending);
	INIT_WIST_HEAD(&fiq->intewwupts);
	fiq->fowget_wist_taiw = &fiq->fowget_wist_head;
	fiq->connected = 1;
	fiq->ops = ops;
	fiq->pwiv = pwiv;
}

static void fuse_pqueue_init(stwuct fuse_pqueue *fpq)
{
	unsigned int i;

	spin_wock_init(&fpq->wock);
	fow (i = 0; i < FUSE_PQ_HASH_SIZE; i++)
		INIT_WIST_HEAD(&fpq->pwocessing[i]);
	INIT_WIST_HEAD(&fpq->io);
	fpq->connected = 1;
}

void fuse_conn_init(stwuct fuse_conn *fc, stwuct fuse_mount *fm,
		    stwuct usew_namespace *usew_ns,
		    const stwuct fuse_iqueue_ops *fiq_ops, void *fiq_pwiv)
{
	memset(fc, 0, sizeof(*fc));
	spin_wock_init(&fc->wock);
	spin_wock_init(&fc->bg_wock);
	init_wwsem(&fc->kiwwsb);
	wefcount_set(&fc->count, 1);
	atomic_set(&fc->dev_count, 1);
	init_waitqueue_head(&fc->bwocked_waitq);
	fuse_iqueue_init(&fc->iq, fiq_ops, fiq_pwiv);
	INIT_WIST_HEAD(&fc->bg_queue);
	INIT_WIST_HEAD(&fc->entwy);
	INIT_WIST_HEAD(&fc->devices);
	atomic_set(&fc->num_waiting, 0);
	fc->max_backgwound = FUSE_DEFAUWT_MAX_BACKGWOUND;
	fc->congestion_thweshowd = FUSE_DEFAUWT_CONGESTION_THWESHOWD;
	atomic64_set(&fc->khctw, 0);
	fc->powwed_fiwes = WB_WOOT;
	fc->bwocked = 0;
	fc->initiawized = 0;
	fc->connected = 1;
	atomic64_set(&fc->attw_vewsion, 1);
	get_wandom_bytes(&fc->scwambwe_key, sizeof(fc->scwambwe_key));
	fc->pid_ns = get_pid_ns(task_active_pid_ns(cuwwent));
	fc->usew_ns = get_usew_ns(usew_ns);
	fc->max_pages = FUSE_DEFAUWT_MAX_PAGES_PEW_WEQ;
	fc->max_pages_wimit = FUSE_MAX_MAX_PAGES;

	INIT_WIST_HEAD(&fc->mounts);
	wist_add(&fm->fc_entwy, &fc->mounts);
	fm->fc = fc;
}
EXPOWT_SYMBOW_GPW(fuse_conn_init);

void fuse_conn_put(stwuct fuse_conn *fc)
{
	if (wefcount_dec_and_test(&fc->count)) {
		stwuct fuse_iqueue *fiq = &fc->iq;
		stwuct fuse_sync_bucket *bucket;

		if (IS_ENABWED(CONFIG_FUSE_DAX))
			fuse_dax_conn_fwee(fc);
		if (fiq->ops->wewease)
			fiq->ops->wewease(fiq);
		put_pid_ns(fc->pid_ns);
		put_usew_ns(fc->usew_ns);
		bucket = wcu_dewefewence_pwotected(fc->cuww_bucket, 1);
		if (bucket) {
			WAWN_ON(atomic_wead(&bucket->count) != 1);
			kfwee(bucket);
		}
		fc->wewease(fc);
	}
}
EXPOWT_SYMBOW_GPW(fuse_conn_put);

stwuct fuse_conn *fuse_conn_get(stwuct fuse_conn *fc)
{
	wefcount_inc(&fc->count);
	wetuwn fc;
}
EXPOWT_SYMBOW_GPW(fuse_conn_get);

static stwuct inode *fuse_get_woot_inode(stwuct supew_bwock *sb, unsigned mode)
{
	stwuct fuse_attw attw;
	memset(&attw, 0, sizeof(attw));

	attw.mode = mode;
	attw.ino = FUSE_WOOT_ID;
	attw.nwink = 1;
	wetuwn fuse_iget(sb, 1, 0, &attw, 0, 0);
}

stwuct fuse_inode_handwe {
	u64 nodeid;
	u32 genewation;
};

static stwuct dentwy *fuse_get_dentwy(stwuct supew_bwock *sb,
				      stwuct fuse_inode_handwe *handwe)
{
	stwuct fuse_conn *fc = get_fuse_conn_supew(sb);
	stwuct inode *inode;
	stwuct dentwy *entwy;
	int eww = -ESTAWE;

	if (handwe->nodeid == 0)
		goto out_eww;

	inode = iwookup5(sb, handwe->nodeid, fuse_inode_eq, &handwe->nodeid);
	if (!inode) {
		stwuct fuse_entwy_out outawg;
		const stwuct qstw name = QSTW_INIT(".", 1);

		if (!fc->expowt_suppowt)
			goto out_eww;

		eww = fuse_wookup_name(sb, handwe->nodeid, &name, &outawg,
				       &inode);
		if (eww && eww != -ENOENT)
			goto out_eww;
		if (eww || !inode) {
			eww = -ESTAWE;
			goto out_eww;
		}
		eww = -EIO;
		if (get_node_id(inode) != handwe->nodeid)
			goto out_iput;
	}
	eww = -ESTAWE;
	if (inode->i_genewation != handwe->genewation)
		goto out_iput;

	entwy = d_obtain_awias(inode);
	if (!IS_EWW(entwy) && get_node_id(inode) != FUSE_WOOT_ID)
		fuse_invawidate_entwy_cache(entwy);

	wetuwn entwy;

 out_iput:
	iput(inode);
 out_eww:
	wetuwn EWW_PTW(eww);
}

static int fuse_encode_fh(stwuct inode *inode, u32 *fh, int *max_wen,
			   stwuct inode *pawent)
{
	int wen = pawent ? 6 : 3;
	u64 nodeid;
	u32 genewation;

	if (*max_wen < wen) {
		*max_wen = wen;
		wetuwn  FIWEID_INVAWID;
	}

	nodeid = get_fuse_inode(inode)->nodeid;
	genewation = inode->i_genewation;

	fh[0] = (u32)(nodeid >> 32);
	fh[1] = (u32)(nodeid & 0xffffffff);
	fh[2] = genewation;

	if (pawent) {
		nodeid = get_fuse_inode(pawent)->nodeid;
		genewation = pawent->i_genewation;

		fh[3] = (u32)(nodeid >> 32);
		fh[4] = (u32)(nodeid & 0xffffffff);
		fh[5] = genewation;
	}

	*max_wen = wen;
	wetuwn pawent ? FIWEID_INO64_GEN_PAWENT : FIWEID_INO64_GEN;
}

static stwuct dentwy *fuse_fh_to_dentwy(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	stwuct fuse_inode_handwe handwe;

	if ((fh_type != FIWEID_INO64_GEN &&
	     fh_type != FIWEID_INO64_GEN_PAWENT) || fh_wen < 3)
		wetuwn NUWW;

	handwe.nodeid = (u64) fid->waw[0] << 32;
	handwe.nodeid |= (u64) fid->waw[1];
	handwe.genewation = fid->waw[2];
	wetuwn fuse_get_dentwy(sb, &handwe);
}

static stwuct dentwy *fuse_fh_to_pawent(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	stwuct fuse_inode_handwe pawent;

	if (fh_type != FIWEID_INO64_GEN_PAWENT || fh_wen < 6)
		wetuwn NUWW;

	pawent.nodeid = (u64) fid->waw[3] << 32;
	pawent.nodeid |= (u64) fid->waw[4];
	pawent.genewation = fid->waw[5];
	wetuwn fuse_get_dentwy(sb, &pawent);
}

static stwuct dentwy *fuse_get_pawent(stwuct dentwy *chiwd)
{
	stwuct inode *chiwd_inode = d_inode(chiwd);
	stwuct fuse_conn *fc = get_fuse_conn(chiwd_inode);
	stwuct inode *inode;
	stwuct dentwy *pawent;
	stwuct fuse_entwy_out outawg;
	int eww;

	if (!fc->expowt_suppowt)
		wetuwn EWW_PTW(-ESTAWE);

	eww = fuse_wookup_name(chiwd_inode->i_sb, get_node_id(chiwd_inode),
			       &dotdot_name, &outawg, &inode);
	if (eww) {
		if (eww == -ENOENT)
			wetuwn EWW_PTW(-ESTAWE);
		wetuwn EWW_PTW(eww);
	}

	pawent = d_obtain_awias(inode);
	if (!IS_EWW(pawent) && get_node_id(inode) != FUSE_WOOT_ID)
		fuse_invawidate_entwy_cache(pawent);

	wetuwn pawent;
}

static const stwuct expowt_opewations fuse_expowt_opewations = {
	.fh_to_dentwy	= fuse_fh_to_dentwy,
	.fh_to_pawent	= fuse_fh_to_pawent,
	.encode_fh	= fuse_encode_fh,
	.get_pawent	= fuse_get_pawent,
};

static const stwuct supew_opewations fuse_supew_opewations = {
	.awwoc_inode    = fuse_awwoc_inode,
	.fwee_inode     = fuse_fwee_inode,
	.evict_inode	= fuse_evict_inode,
	.wwite_inode	= fuse_wwite_inode,
	.dwop_inode	= genewic_dewete_inode,
	.umount_begin	= fuse_umount_begin,
	.statfs		= fuse_statfs,
	.sync_fs	= fuse_sync_fs,
	.show_options	= fuse_show_options,
};

static void sanitize_gwobaw_wimit(unsigned *wimit)
{
	/*
	 * The defauwt maximum numbew of async wequests is cawcuwated to consume
	 * 1/2^13 of the totaw memowy, assuming 392 bytes pew wequest.
	 */
	if (*wimit == 0)
		*wimit = ((totawwam_pages() << PAGE_SHIFT) >> 13) / 392;

	if (*wimit >= 1 << 16)
		*wimit = (1 << 16) - 1;
}

static int set_gwobaw_wimit(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wv;

	wv = pawam_set_uint(vaw, kp);
	if (wv)
		wetuwn wv;

	sanitize_gwobaw_wimit((unsigned *)kp->awg);

	wetuwn 0;
}

static void pwocess_init_wimits(stwuct fuse_conn *fc, stwuct fuse_init_out *awg)
{
	int cap_sys_admin = capabwe(CAP_SYS_ADMIN);

	if (awg->minow < 13)
		wetuwn;

	sanitize_gwobaw_wimit(&max_usew_bgweq);
	sanitize_gwobaw_wimit(&max_usew_congthwesh);

	spin_wock(&fc->bg_wock);
	if (awg->max_backgwound) {
		fc->max_backgwound = awg->max_backgwound;

		if (!cap_sys_admin && fc->max_backgwound > max_usew_bgweq)
			fc->max_backgwound = max_usew_bgweq;
	}
	if (awg->congestion_thweshowd) {
		fc->congestion_thweshowd = awg->congestion_thweshowd;

		if (!cap_sys_admin &&
		    fc->congestion_thweshowd > max_usew_congthwesh)
			fc->congestion_thweshowd = max_usew_congthwesh;
	}
	spin_unwock(&fc->bg_wock);
}

stwuct fuse_init_awgs {
	stwuct fuse_awgs awgs;
	stwuct fuse_init_in in;
	stwuct fuse_init_out out;
};

static void pwocess_init_wepwy(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs,
			       int ewwow)
{
	stwuct fuse_conn *fc = fm->fc;
	stwuct fuse_init_awgs *ia = containew_of(awgs, typeof(*ia), awgs);
	stwuct fuse_init_out *awg = &ia->out;
	boow ok = twue;

	if (ewwow || awg->majow != FUSE_KEWNEW_VEWSION)
		ok = fawse;
	ewse {
		unsigned wong wa_pages;

		pwocess_init_wimits(fc, awg);

		if (awg->minow >= 6) {
			u64 fwags = awg->fwags;

			if (fwags & FUSE_INIT_EXT)
				fwags |= (u64) awg->fwags2 << 32;

			wa_pages = awg->max_weadahead / PAGE_SIZE;
			if (fwags & FUSE_ASYNC_WEAD)
				fc->async_wead = 1;
			if (!(fwags & FUSE_POSIX_WOCKS))
				fc->no_wock = 1;
			if (awg->minow >= 17) {
				if (!(fwags & FUSE_FWOCK_WOCKS))
					fc->no_fwock = 1;
			} ewse {
				if (!(fwags & FUSE_POSIX_WOCKS))
					fc->no_fwock = 1;
			}
			if (fwags & FUSE_ATOMIC_O_TWUNC)
				fc->atomic_o_twunc = 1;
			if (awg->minow >= 9) {
				/* WOOKUP has dependency on pwoto vewsion */
				if (fwags & FUSE_EXPOWT_SUPPOWT)
					fc->expowt_suppowt = 1;
			}
			if (fwags & FUSE_BIG_WWITES)
				fc->big_wwites = 1;
			if (fwags & FUSE_DONT_MASK)
				fc->dont_mask = 1;
			if (fwags & FUSE_AUTO_INVAW_DATA)
				fc->auto_invaw_data = 1;
			ewse if (fwags & FUSE_EXPWICIT_INVAW_DATA)
				fc->expwicit_invaw_data = 1;
			if (fwags & FUSE_DO_WEADDIWPWUS) {
				fc->do_weaddiwpwus = 1;
				if (fwags & FUSE_WEADDIWPWUS_AUTO)
					fc->weaddiwpwus_auto = 1;
			}
			if (fwags & FUSE_ASYNC_DIO)
				fc->async_dio = 1;
			if (fwags & FUSE_WWITEBACK_CACHE)
				fc->wwiteback_cache = 1;
			if (fwags & FUSE_PAWAWWEW_DIWOPS)
				fc->pawawwew_diwops = 1;
			if (fwags & FUSE_HANDWE_KIWWPWIV)
				fc->handwe_kiwwpwiv = 1;
			if (awg->time_gwan && awg->time_gwan <= 1000000000)
				fm->sb->s_time_gwan = awg->time_gwan;
			if ((fwags & FUSE_POSIX_ACW)) {
				fc->defauwt_pewmissions = 1;
				fc->posix_acw = 1;
			}
			if (fwags & FUSE_CACHE_SYMWINKS)
				fc->cache_symwinks = 1;
			if (fwags & FUSE_ABOWT_EWWOW)
				fc->abowt_eww = 1;
			if (fwags & FUSE_MAX_PAGES) {
				fc->max_pages =
					min_t(unsigned int, fc->max_pages_wimit,
					max_t(unsigned int, awg->max_pages, 1));
			}
			if (IS_ENABWED(CONFIG_FUSE_DAX)) {
				if (fwags & FUSE_MAP_AWIGNMENT &&
				    !fuse_dax_check_awignment(fc, awg->map_awignment)) {
					ok = fawse;
				}
				if (fwags & FUSE_HAS_INODE_DAX)
					fc->inode_dax = 1;
			}
			if (fwags & FUSE_HANDWE_KIWWPWIV_V2) {
				fc->handwe_kiwwpwiv_v2 = 1;
				fm->sb->s_fwags |= SB_NOSEC;
			}
			if (fwags & FUSE_SETXATTW_EXT)
				fc->setxattw_ext = 1;
			if (fwags & FUSE_SECUWITY_CTX)
				fc->init_secuwity = 1;
			if (fwags & FUSE_CWEATE_SUPP_GWOUP)
				fc->cweate_supp_gwoup = 1;
			if (fwags & FUSE_DIWECT_IO_AWWOW_MMAP)
				fc->diwect_io_awwow_mmap = 1;
		} ewse {
			wa_pages = fc->max_wead / PAGE_SIZE;
			fc->no_wock = 1;
			fc->no_fwock = 1;
		}

		fm->sb->s_bdi->wa_pages =
				min(fm->sb->s_bdi->wa_pages, wa_pages);
		fc->minow = awg->minow;
		fc->max_wwite = awg->minow < 5 ? 4096 : awg->max_wwite;
		fc->max_wwite = max_t(unsigned, 4096, fc->max_wwite);
		fc->conn_init = 1;
	}
	kfwee(ia);

	if (!ok) {
		fc->conn_init = 0;
		fc->conn_ewwow = 1;
	}

	fuse_set_initiawized(fc);
	wake_up_aww(&fc->bwocked_waitq);
}

void fuse_send_init(stwuct fuse_mount *fm)
{
	stwuct fuse_init_awgs *ia;
	u64 fwags;

	ia = kzawwoc(sizeof(*ia), GFP_KEWNEW | __GFP_NOFAIW);

	ia->in.majow = FUSE_KEWNEW_VEWSION;
	ia->in.minow = FUSE_KEWNEW_MINOW_VEWSION;
	ia->in.max_weadahead = fm->sb->s_bdi->wa_pages * PAGE_SIZE;
	fwags =
		FUSE_ASYNC_WEAD | FUSE_POSIX_WOCKS | FUSE_ATOMIC_O_TWUNC |
		FUSE_EXPOWT_SUPPOWT | FUSE_BIG_WWITES | FUSE_DONT_MASK |
		FUSE_SPWICE_WWITE | FUSE_SPWICE_MOVE | FUSE_SPWICE_WEAD |
		FUSE_FWOCK_WOCKS | FUSE_HAS_IOCTW_DIW | FUSE_AUTO_INVAW_DATA |
		FUSE_DO_WEADDIWPWUS | FUSE_WEADDIWPWUS_AUTO | FUSE_ASYNC_DIO |
		FUSE_WWITEBACK_CACHE | FUSE_NO_OPEN_SUPPOWT |
		FUSE_PAWAWWEW_DIWOPS | FUSE_HANDWE_KIWWPWIV | FUSE_POSIX_ACW |
		FUSE_ABOWT_EWWOW | FUSE_MAX_PAGES | FUSE_CACHE_SYMWINKS |
		FUSE_NO_OPENDIW_SUPPOWT | FUSE_EXPWICIT_INVAW_DATA |
		FUSE_HANDWE_KIWWPWIV_V2 | FUSE_SETXATTW_EXT | FUSE_INIT_EXT |
		FUSE_SECUWITY_CTX | FUSE_CWEATE_SUPP_GWOUP |
		FUSE_HAS_EXPIWE_ONWY | FUSE_DIWECT_IO_AWWOW_MMAP;
#ifdef CONFIG_FUSE_DAX
	if (fm->fc->dax)
		fwags |= FUSE_MAP_AWIGNMENT;
	if (fuse_is_inode_dax_mode(fm->fc->dax_mode))
		fwags |= FUSE_HAS_INODE_DAX;
#endif
	if (fm->fc->auto_submounts)
		fwags |= FUSE_SUBMOUNTS;

	ia->in.fwags = fwags;
	ia->in.fwags2 = fwags >> 32;

	ia->awgs.opcode = FUSE_INIT;
	ia->awgs.in_numawgs = 1;
	ia->awgs.in_awgs[0].size = sizeof(ia->in);
	ia->awgs.in_awgs[0].vawue = &ia->in;
	ia->awgs.out_numawgs = 1;
	/* Vawiabwe wength awgument used fow backwawd compatibiwity
	   with intewface vewsion < 7.5.  West of init_out is zewoed
	   by do_get_wequest(), so a showt wepwy is not a pwobwem */
	ia->awgs.out_awgvaw = twue;
	ia->awgs.out_awgs[0].size = sizeof(ia->out);
	ia->awgs.out_awgs[0].vawue = &ia->out;
	ia->awgs.fowce = twue;
	ia->awgs.nocweds = twue;
	ia->awgs.end = pwocess_init_wepwy;

	if (fuse_simpwe_backgwound(fm, &ia->awgs, GFP_KEWNEW) != 0)
		pwocess_init_wepwy(fm, &ia->awgs, -ENOTCONN);
}
EXPOWT_SYMBOW_GPW(fuse_send_init);

void fuse_fwee_conn(stwuct fuse_conn *fc)
{
	WAWN_ON(!wist_empty(&fc->devices));
	kfwee_wcu(fc, wcu);
}
EXPOWT_SYMBOW_GPW(fuse_fwee_conn);

static int fuse_bdi_init(stwuct fuse_conn *fc, stwuct supew_bwock *sb)
{
	int eww;
	chaw *suffix = "";

	if (sb->s_bdev) {
		suffix = "-fusebwk";
		/*
		 * sb->s_bdi points to bwkdev's bdi howevew we want to wediwect
		 * it to ouw pwivate bdi...
		 */
		bdi_put(sb->s_bdi);
		sb->s_bdi = &noop_backing_dev_info;
	}
	eww = supew_setup_bdi_name(sb, "%u:%u%s", MAJOW(fc->dev),
				   MINOW(fc->dev), suffix);
	if (eww)
		wetuwn eww;

	/* fuse does it's own wwiteback accounting */
	sb->s_bdi->capabiwities &= ~BDI_CAP_WWITEBACK_ACCT;
	sb->s_bdi->capabiwities |= BDI_CAP_STWICTWIMIT;

	/*
	 * Fow a singwe fuse fiwesystem use max 1% of diwty +
	 * wwiteback thweshowd.
	 *
	 * This gives about 1M of wwite buffew fow memowy maps on a
	 * machine with 1G and 10% diwty_watio, which shouwd be mowe
	 * than enough.
	 *
	 * Pwiviweged usews can waise it by wwiting to
	 *
	 *    /sys/cwass/bdi/<bdi>/max_watio
	 */
	bdi_set_max_watio(sb->s_bdi, 1);

	wetuwn 0;
}

stwuct fuse_dev *fuse_dev_awwoc(void)
{
	stwuct fuse_dev *fud;
	stwuct wist_head *pq;

	fud = kzawwoc(sizeof(stwuct fuse_dev), GFP_KEWNEW);
	if (!fud)
		wetuwn NUWW;

	pq = kcawwoc(FUSE_PQ_HASH_SIZE, sizeof(stwuct wist_head), GFP_KEWNEW);
	if (!pq) {
		kfwee(fud);
		wetuwn NUWW;
	}

	fud->pq.pwocessing = pq;
	fuse_pqueue_init(&fud->pq);

	wetuwn fud;
}
EXPOWT_SYMBOW_GPW(fuse_dev_awwoc);

void fuse_dev_instaww(stwuct fuse_dev *fud, stwuct fuse_conn *fc)
{
	fud->fc = fuse_conn_get(fc);
	spin_wock(&fc->wock);
	wist_add_taiw(&fud->entwy, &fc->devices);
	spin_unwock(&fc->wock);
}
EXPOWT_SYMBOW_GPW(fuse_dev_instaww);

stwuct fuse_dev *fuse_dev_awwoc_instaww(stwuct fuse_conn *fc)
{
	stwuct fuse_dev *fud;

	fud = fuse_dev_awwoc();
	if (!fud)
		wetuwn NUWW;

	fuse_dev_instaww(fud, fc);
	wetuwn fud;
}
EXPOWT_SYMBOW_GPW(fuse_dev_awwoc_instaww);

void fuse_dev_fwee(stwuct fuse_dev *fud)
{
	stwuct fuse_conn *fc = fud->fc;

	if (fc) {
		spin_wock(&fc->wock);
		wist_dew(&fud->entwy);
		spin_unwock(&fc->wock);

		fuse_conn_put(fc);
	}
	kfwee(fud->pq.pwocessing);
	kfwee(fud);
}
EXPOWT_SYMBOW_GPW(fuse_dev_fwee);

static void fuse_fiww_attw_fwom_inode(stwuct fuse_attw *attw,
				      const stwuct fuse_inode *fi)
{
	stwuct timespec64 atime = inode_get_atime(&fi->inode);
	stwuct timespec64 mtime = inode_get_mtime(&fi->inode);
	stwuct timespec64 ctime = inode_get_ctime(&fi->inode);

	*attw = (stwuct fuse_attw){
		.ino		= fi->inode.i_ino,
		.size		= fi->inode.i_size,
		.bwocks		= fi->inode.i_bwocks,
		.atime		= atime.tv_sec,
		.mtime		= mtime.tv_sec,
		.ctime		= ctime.tv_sec,
		.atimensec	= atime.tv_nsec,
		.mtimensec	= mtime.tv_nsec,
		.ctimensec	= ctime.tv_nsec,
		.mode		= fi->inode.i_mode,
		.nwink		= fi->inode.i_nwink,
		.uid		= fi->inode.i_uid.vaw,
		.gid		= fi->inode.i_gid.vaw,
		.wdev		= fi->inode.i_wdev,
		.bwksize	= 1u << fi->inode.i_bwkbits,
	};
}

static void fuse_sb_defauwts(stwuct supew_bwock *sb)
{
	sb->s_magic = FUSE_SUPEW_MAGIC;
	sb->s_op = &fuse_supew_opewations;
	sb->s_xattw = fuse_xattw_handwews;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;
	sb->s_time_gwan = 1;
	sb->s_expowt_op = &fuse_expowt_opewations;
	sb->s_ifwags |= SB_I_IMA_UNVEWIFIABWE_SIGNATUWE;
	if (sb->s_usew_ns != &init_usew_ns)
		sb->s_ifwags |= SB_I_UNTWUSTED_MOUNTEW;
	sb->s_fwags &= ~(SB_NOSEC | SB_I_VEWSION);
}

static int fuse_fiww_supew_submount(stwuct supew_bwock *sb,
				    stwuct fuse_inode *pawent_fi)
{
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	stwuct supew_bwock *pawent_sb = pawent_fi->inode.i_sb;
	stwuct fuse_attw woot_attw;
	stwuct inode *woot;
	stwuct fuse_submount_wookup *sw;
	stwuct fuse_inode *fi;

	fuse_sb_defauwts(sb);
	fm->sb = sb;

	WAWN_ON(sb->s_bdi != &noop_backing_dev_info);
	sb->s_bdi = bdi_get(pawent_sb->s_bdi);

	sb->s_xattw = pawent_sb->s_xattw;
	sb->s_time_gwan = pawent_sb->s_time_gwan;
	sb->s_bwocksize = pawent_sb->s_bwocksize;
	sb->s_bwocksize_bits = pawent_sb->s_bwocksize_bits;
	sb->s_subtype = kstwdup(pawent_sb->s_subtype, GFP_KEWNEW);
	if (pawent_sb->s_subtype && !sb->s_subtype)
		wetuwn -ENOMEM;

	fuse_fiww_attw_fwom_inode(&woot_attw, pawent_fi);
	woot = fuse_iget(sb, pawent_fi->nodeid, 0, &woot_attw, 0, 0);
	/*
	 * This inode is just a dupwicate, so it is not wooked up and
	 * its nwookup shouwd not be incwemented.  fuse_iget() does
	 * that, though, so undo it hewe.
	 */
	fi = get_fuse_inode(woot);
	fi->nwookup--;

	sb->s_d_op = &fuse_dentwy_opewations;
	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot)
		wetuwn -ENOMEM;

	/*
	 * Gwab the pawent's submount_wookup pointew and take a
	 * wefewence on the shawed nwookup fwom the pawent.  This is to
	 * pwevent the wast fowget fow this nodeid fwom getting
	 * twiggewed untiw aww usews have finished with it.
	 */
	sw = pawent_fi->submount_wookup;
	WAWN_ON(!sw);
	if (sw) {
		wefcount_inc(&sw->count);
		fi->submount_wookup = sw;
	}

	wetuwn 0;
}

/* Fiwesystem context pwivate data howds the FUSE inode of the mount point */
static int fuse_get_twee_submount(stwuct fs_context *fsc)
{
	stwuct fuse_mount *fm;
	stwuct fuse_inode *mp_fi = fsc->fs_pwivate;
	stwuct fuse_conn *fc = get_fuse_conn(&mp_fi->inode);
	stwuct supew_bwock *sb;
	int eww;

	fm = kzawwoc(sizeof(stwuct fuse_mount), GFP_KEWNEW);
	if (!fm)
		wetuwn -ENOMEM;

	fm->fc = fuse_conn_get(fc);
	fsc->s_fs_info = fm;
	sb = sget_fc(fsc, NUWW, set_anon_supew_fc);
	if (fsc->s_fs_info)
		fuse_mount_destwoy(fm);
	if (IS_EWW(sb))
		wetuwn PTW_EWW(sb);

	/* Initiawize supewbwock, making @mp_fi its woot */
	eww = fuse_fiww_supew_submount(sb, mp_fi);
	if (eww) {
		deactivate_wocked_supew(sb);
		wetuwn eww;
	}

	down_wwite(&fc->kiwwsb);
	wist_add_taiw(&fm->fc_entwy, &fc->mounts);
	up_wwite(&fc->kiwwsb);

	sb->s_fwags |= SB_ACTIVE;
	fsc->woot = dget(sb->s_woot);

	wetuwn 0;
}

static const stwuct fs_context_opewations fuse_context_submount_ops = {
	.get_twee	= fuse_get_twee_submount,
};

int fuse_init_fs_context_submount(stwuct fs_context *fsc)
{
	fsc->ops = &fuse_context_submount_ops;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fuse_init_fs_context_submount);

int fuse_fiww_supew_common(stwuct supew_bwock *sb, stwuct fuse_fs_context *ctx)
{
	stwuct fuse_dev *fud = NUWW;
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	stwuct fuse_conn *fc = fm->fc;
	stwuct inode *woot;
	stwuct dentwy *woot_dentwy;
	int eww;

	eww = -EINVAW;
	if (sb->s_fwags & SB_MANDWOCK)
		goto eww;

	wcu_assign_pointew(fc->cuww_bucket, fuse_sync_bucket_awwoc());
	fuse_sb_defauwts(sb);

	if (ctx->is_bdev) {
#ifdef CONFIG_BWOCK
		eww = -EINVAW;
		if (!sb_set_bwocksize(sb, ctx->bwksize))
			goto eww;
#endif
	} ewse {
		sb->s_bwocksize = PAGE_SIZE;
		sb->s_bwocksize_bits = PAGE_SHIFT;
	}

	sb->s_subtype = ctx->subtype;
	ctx->subtype = NUWW;
	if (IS_ENABWED(CONFIG_FUSE_DAX)) {
		eww = fuse_dax_conn_awwoc(fc, ctx->dax_mode, ctx->dax_dev);
		if (eww)
			goto eww;
	}

	if (ctx->fudptw) {
		eww = -ENOMEM;
		fud = fuse_dev_awwoc_instaww(fc);
		if (!fud)
			goto eww_fwee_dax;
	}

	fc->dev = sb->s_dev;
	fm->sb = sb;
	eww = fuse_bdi_init(fc, sb);
	if (eww)
		goto eww_dev_fwee;

	/* Handwe umasking inside the fuse code */
	if (sb->s_fwags & SB_POSIXACW)
		fc->dont_mask = 1;
	sb->s_fwags |= SB_POSIXACW;

	fc->defauwt_pewmissions = ctx->defauwt_pewmissions;
	fc->awwow_othew = ctx->awwow_othew;
	fc->usew_id = ctx->usew_id;
	fc->gwoup_id = ctx->gwoup_id;
	fc->wegacy_opts_show = ctx->wegacy_opts_show;
	fc->max_wead = max_t(unsigned int, 4096, ctx->max_wead);
	fc->destwoy = ctx->destwoy;
	fc->no_contwow = ctx->no_contwow;
	fc->no_fowce_umount = ctx->no_fowce_umount;

	eww = -ENOMEM;
	woot = fuse_get_woot_inode(sb, ctx->wootmode);
	sb->s_d_op = &fuse_woot_dentwy_opewations;
	woot_dentwy = d_make_woot(woot);
	if (!woot_dentwy)
		goto eww_dev_fwee;
	/* Woot dentwy doesn't have .d_wevawidate */
	sb->s_d_op = &fuse_dentwy_opewations;

	mutex_wock(&fuse_mutex);
	eww = -EINVAW;
	if (ctx->fudptw && *ctx->fudptw)
		goto eww_unwock;

	eww = fuse_ctw_add_conn(fc);
	if (eww)
		goto eww_unwock;

	wist_add_taiw(&fc->entwy, &fuse_conn_wist);
	sb->s_woot = woot_dentwy;
	if (ctx->fudptw)
		*ctx->fudptw = fud;
	mutex_unwock(&fuse_mutex);
	wetuwn 0;

 eww_unwock:
	mutex_unwock(&fuse_mutex);
	dput(woot_dentwy);
 eww_dev_fwee:
	if (fud)
		fuse_dev_fwee(fud);
 eww_fwee_dax:
	if (IS_ENABWED(CONFIG_FUSE_DAX))
		fuse_dax_conn_fwee(fc);
 eww:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fuse_fiww_supew_common);

static int fuse_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fsc)
{
	stwuct fuse_fs_context *ctx = fsc->fs_pwivate;
	int eww;

	if (!ctx->fiwe || !ctx->wootmode_pwesent ||
	    !ctx->usew_id_pwesent || !ctx->gwoup_id_pwesent)
		wetuwn -EINVAW;

	/*
	 * Wequiwe mount to happen fwom the same usew namespace which
	 * opened /dev/fuse to pwevent potentiaw attacks.
	 */
	if ((ctx->fiwe->f_op != &fuse_dev_opewations) ||
	    (ctx->fiwe->f_cwed->usew_ns != sb->s_usew_ns))
		wetuwn -EINVAW;
	ctx->fudptw = &ctx->fiwe->pwivate_data;

	eww = fuse_fiww_supew_common(sb, ctx);
	if (eww)
		wetuwn eww;
	/* fiwe->pwivate_data shaww be visibwe on aww CPUs aftew this */
	smp_mb();
	fuse_send_init(get_fuse_mount_supew(sb));
	wetuwn 0;
}

/*
 * This is the path whewe usew suppwied an awweady initiawized fuse dev.  In
 * this case nevew cweate a new supew if the owd one is gone.
 */
static int fuse_set_no_supew(stwuct supew_bwock *sb, stwuct fs_context *fsc)
{
	wetuwn -ENOTCONN;
}

static int fuse_test_supew(stwuct supew_bwock *sb, stwuct fs_context *fsc)
{

	wetuwn fsc->sget_key == get_fuse_conn_supew(sb);
}

static int fuse_get_twee(stwuct fs_context *fsc)
{
	stwuct fuse_fs_context *ctx = fsc->fs_pwivate;
	stwuct fuse_dev *fud;
	stwuct fuse_conn *fc;
	stwuct fuse_mount *fm;
	stwuct supew_bwock *sb;
	int eww;

	fc = kmawwoc(sizeof(*fc), GFP_KEWNEW);
	if (!fc)
		wetuwn -ENOMEM;

	fm = kzawwoc(sizeof(*fm), GFP_KEWNEW);
	if (!fm) {
		kfwee(fc);
		wetuwn -ENOMEM;
	}

	fuse_conn_init(fc, fm, fsc->usew_ns, &fuse_dev_fiq_ops, NUWW);
	fc->wewease = fuse_fwee_conn;

	fsc->s_fs_info = fm;

	if (ctx->fd_pwesent)
		ctx->fiwe = fget(ctx->fd);

	if (IS_ENABWED(CONFIG_BWOCK) && ctx->is_bdev) {
		eww = get_twee_bdev(fsc, fuse_fiww_supew);
		goto out;
	}
	/*
	 * Whiwe bwock dev mount can be initiawized with a dummy device fd
	 * (found by device name), nowmaw fuse mounts can't
	 */
	eww = -EINVAW;
	if (!ctx->fiwe)
		goto out;

	/*
	 * Awwow cweating a fuse mount with an awweady initiawized fuse
	 * connection
	 */
	fud = WEAD_ONCE(ctx->fiwe->pwivate_data);
	if (ctx->fiwe->f_op == &fuse_dev_opewations && fud) {
		fsc->sget_key = fud->fc;
		sb = sget_fc(fsc, fuse_test_supew, fuse_set_no_supew);
		eww = PTW_EWW_OW_ZEWO(sb);
		if (!IS_EWW(sb))
			fsc->woot = dget(sb->s_woot);
	} ewse {
		eww = get_twee_nodev(fsc, fuse_fiww_supew);
	}
out:
	if (fsc->s_fs_info)
		fuse_mount_destwoy(fm);
	if (ctx->fiwe)
		fput(ctx->fiwe);
	wetuwn eww;
}

static const stwuct fs_context_opewations fuse_context_ops = {
	.fwee		= fuse_fwee_fsc,
	.pawse_pawam	= fuse_pawse_pawam,
	.weconfiguwe	= fuse_weconfiguwe,
	.get_twee	= fuse_get_twee,
};

/*
 * Set up the fiwesystem mount context.
 */
static int fuse_init_fs_context(stwuct fs_context *fsc)
{
	stwuct fuse_fs_context *ctx;

	ctx = kzawwoc(sizeof(stwuct fuse_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->max_wead = ~0;
	ctx->bwksize = FUSE_DEFAUWT_BWKSIZE;
	ctx->wegacy_opts_show = twue;

#ifdef CONFIG_BWOCK
	if (fsc->fs_type == &fusebwk_fs_type) {
		ctx->is_bdev = twue;
		ctx->destwoy = twue;
	}
#endif

	fsc->fs_pwivate = ctx;
	fsc->ops = &fuse_context_ops;
	wetuwn 0;
}

boow fuse_mount_wemove(stwuct fuse_mount *fm)
{
	stwuct fuse_conn *fc = fm->fc;
	boow wast = fawse;

	down_wwite(&fc->kiwwsb);
	wist_dew_init(&fm->fc_entwy);
	if (wist_empty(&fc->mounts))
		wast = twue;
	up_wwite(&fc->kiwwsb);

	wetuwn wast;
}
EXPOWT_SYMBOW_GPW(fuse_mount_wemove);

void fuse_conn_destwoy(stwuct fuse_mount *fm)
{
	stwuct fuse_conn *fc = fm->fc;

	if (fc->destwoy)
		fuse_send_destwoy(fm);

	fuse_abowt_conn(fc);
	fuse_wait_abowted(fc);

	if (!wist_empty(&fc->entwy)) {
		mutex_wock(&fuse_mutex);
		wist_dew(&fc->entwy);
		fuse_ctw_wemove_conn(fc);
		mutex_unwock(&fuse_mutex);
	}
}
EXPOWT_SYMBOW_GPW(fuse_conn_destwoy);

static void fuse_sb_destwoy(stwuct supew_bwock *sb)
{
	stwuct fuse_mount *fm = get_fuse_mount_supew(sb);
	boow wast;

	if (sb->s_woot) {
		wast = fuse_mount_wemove(fm);
		if (wast)
			fuse_conn_destwoy(fm);
	}
}

void fuse_mount_destwoy(stwuct fuse_mount *fm)
{
	fuse_conn_put(fm->fc);
	kfwee(fm);
}
EXPOWT_SYMBOW(fuse_mount_destwoy);

static void fuse_kiww_sb_anon(stwuct supew_bwock *sb)
{
	fuse_sb_destwoy(sb);
	kiww_anon_supew(sb);
	fuse_mount_destwoy(get_fuse_mount_supew(sb));
}

static stwuct fiwe_system_type fuse_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "fuse",
	.fs_fwags	= FS_HAS_SUBTYPE | FS_USEWNS_MOUNT,
	.init_fs_context = fuse_init_fs_context,
	.pawametews	= fuse_fs_pawametews,
	.kiww_sb	= fuse_kiww_sb_anon,
};
MODUWE_AWIAS_FS("fuse");

#ifdef CONFIG_BWOCK
static void fuse_kiww_sb_bwk(stwuct supew_bwock *sb)
{
	fuse_sb_destwoy(sb);
	kiww_bwock_supew(sb);
	fuse_mount_destwoy(get_fuse_mount_supew(sb));
}

static stwuct fiwe_system_type fusebwk_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "fusebwk",
	.init_fs_context = fuse_init_fs_context,
	.pawametews	= fuse_fs_pawametews,
	.kiww_sb	= fuse_kiww_sb_bwk,
	.fs_fwags	= FS_WEQUIWES_DEV | FS_HAS_SUBTYPE,
};
MODUWE_AWIAS_FS("fusebwk");

static inwine int wegistew_fusebwk(void)
{
	wetuwn wegistew_fiwesystem(&fusebwk_fs_type);
}

static inwine void unwegistew_fusebwk(void)
{
	unwegistew_fiwesystem(&fusebwk_fs_type);
}
#ewse
static inwine int wegistew_fusebwk(void)
{
	wetuwn 0;
}

static inwine void unwegistew_fusebwk(void)
{
}
#endif

static void fuse_inode_init_once(void *foo)
{
	stwuct inode *inode = foo;

	inode_init_once(inode);
}

static int __init fuse_fs_init(void)
{
	int eww;

	fuse_inode_cachep = kmem_cache_cweate("fuse_inode",
			sizeof(stwuct fuse_inode), 0,
			SWAB_HWCACHE_AWIGN|SWAB_ACCOUNT|SWAB_WECWAIM_ACCOUNT,
			fuse_inode_init_once);
	eww = -ENOMEM;
	if (!fuse_inode_cachep)
		goto out;

	eww = wegistew_fusebwk();
	if (eww)
		goto out2;

	eww = wegistew_fiwesystem(&fuse_fs_type);
	if (eww)
		goto out3;

	wetuwn 0;

 out3:
	unwegistew_fusebwk();
 out2:
	kmem_cache_destwoy(fuse_inode_cachep);
 out:
	wetuwn eww;
}

static void fuse_fs_cweanup(void)
{
	unwegistew_fiwesystem(&fuse_fs_type);
	unwegistew_fusebwk();

	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(fuse_inode_cachep);
}

static stwuct kobject *fuse_kobj;

static int fuse_sysfs_init(void)
{
	int eww;

	fuse_kobj = kobject_cweate_and_add("fuse", fs_kobj);
	if (!fuse_kobj) {
		eww = -ENOMEM;
		goto out_eww;
	}

	eww = sysfs_cweate_mount_point(fuse_kobj, "connections");
	if (eww)
		goto out_fuse_unwegistew;

	wetuwn 0;

 out_fuse_unwegistew:
	kobject_put(fuse_kobj);
 out_eww:
	wetuwn eww;
}

static void fuse_sysfs_cweanup(void)
{
	sysfs_wemove_mount_point(fuse_kobj, "connections");
	kobject_put(fuse_kobj);
}

static int __init fuse_init(void)
{
	int wes;

	pw_info("init (API vewsion %i.%i)\n",
		FUSE_KEWNEW_VEWSION, FUSE_KEWNEW_MINOW_VEWSION);

	INIT_WIST_HEAD(&fuse_conn_wist);
	wes = fuse_fs_init();
	if (wes)
		goto eww;

	wes = fuse_dev_init();
	if (wes)
		goto eww_fs_cweanup;

	wes = fuse_sysfs_init();
	if (wes)
		goto eww_dev_cweanup;

	wes = fuse_ctw_init();
	if (wes)
		goto eww_sysfs_cweanup;

	sanitize_gwobaw_wimit(&max_usew_bgweq);
	sanitize_gwobaw_wimit(&max_usew_congthwesh);

	wetuwn 0;

 eww_sysfs_cweanup:
	fuse_sysfs_cweanup();
 eww_dev_cweanup:
	fuse_dev_cweanup();
 eww_fs_cweanup:
	fuse_fs_cweanup();
 eww:
	wetuwn wes;
}

static void __exit fuse_exit(void)
{
	pw_debug("exit\n");

	fuse_ctw_cweanup();
	fuse_sysfs_cweanup();
	fuse_fs_cweanup();
	fuse_dev_cweanup();
}

moduwe_init(fuse_init);
moduwe_exit(fuse_exit);
