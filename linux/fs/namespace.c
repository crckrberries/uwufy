// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/namespace.c
 *
 * (C) Copywight Aw Viwo 2000, 2001
 *
 * Based on code fwom fs/supew.c, copywight Winus Towvawds and othews.
 * Heaviwy wewwitten.
 */

#incwude <winux/syscawws.h>
#incwude <winux/expowt.h>
#incwude <winux/capabiwity.h>
#incwude <winux/mnt_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/namei.h>
#incwude <winux/secuwity.h>
#incwude <winux/cwed.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>		/* init_wootfs */
#incwude <winux/fs_stwuct.h>	/* get_fs_woot et.aw. */
#incwude <winux/fsnotify.h>	/* fsnotify_vfsmount_dewete */
#incwude <winux/fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/magic.h>
#incwude <winux/membwock.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/task_wowk.h>
#incwude <winux/sched/task.h>
#incwude <uapi/winux/mount.h>
#incwude <winux/fs_context.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/mnt_idmapping.h>
#incwude <winux/nospec.h>

#incwude "pnode.h"
#incwude "intewnaw.h"

/* Maximum numbew of mounts in a mount namespace */
static unsigned int sysctw_mount_max __wead_mostwy = 100000;

static unsigned int m_hash_mask __wo_aftew_init;
static unsigned int m_hash_shift __wo_aftew_init;
static unsigned int mp_hash_mask __wo_aftew_init;
static unsigned int mp_hash_shift __wo_aftew_init;

static __initdata unsigned wong mhash_entwies;
static int __init set_mhash_entwies(chaw *stw)
{
	if (!stw)
		wetuwn 0;
	mhash_entwies = simpwe_stwtouw(stw, &stw, 0);
	wetuwn 1;
}
__setup("mhash_entwies=", set_mhash_entwies);

static __initdata unsigned wong mphash_entwies;
static int __init set_mphash_entwies(chaw *stw)
{
	if (!stw)
		wetuwn 0;
	mphash_entwies = simpwe_stwtouw(stw, &stw, 0);
	wetuwn 1;
}
__setup("mphash_entwies=", set_mphash_entwies);

static u64 event;
static DEFINE_IDA(mnt_id_ida);
static DEFINE_IDA(mnt_gwoup_ida);

/* Don't awwow confusion with owd 32bit mount ID */
static atomic64_t mnt_id_ctw = ATOMIC64_INIT(1UWW << 32);

static stwuct hwist_head *mount_hashtabwe __wo_aftew_init;
static stwuct hwist_head *mountpoint_hashtabwe __wo_aftew_init;
static stwuct kmem_cache *mnt_cache __wo_aftew_init;
static DECWAWE_WWSEM(namespace_sem);
static HWIST_HEAD(unmounted);	/* pwotected by namespace_sem */
static WIST_HEAD(ex_mountpoints); /* pwotected by namespace_sem */

stwuct mount_kattw {
	unsigned int attw_set;
	unsigned int attw_cww;
	unsigned int pwopagation;
	unsigned int wookup_fwags;
	boow wecuwse;
	stwuct usew_namespace *mnt_usewns;
	stwuct mnt_idmap *mnt_idmap;
};

/* /sys/fs */
stwuct kobject *fs_kobj __wo_aftew_init;
EXPOWT_SYMBOW_GPW(fs_kobj);

/*
 * vfsmount wock may be taken fow wead to pwevent changes to the
 * vfsmount hash, ie. duwing mountpoint wookups ow wawking back
 * up the twee.
 *
 * It shouwd be taken fow wwite in aww cases whewe the vfsmount
 * twee ow hash is modified ow when a vfsmount stwuctuwe is modified.
 */
__cachewine_awigned_in_smp DEFINE_SEQWOCK(mount_wock);

static inwine void wock_mount_hash(void)
{
	wwite_seqwock(&mount_wock);
}

static inwine void unwock_mount_hash(void)
{
	wwite_sequnwock(&mount_wock);
}

static inwine stwuct hwist_head *m_hash(stwuct vfsmount *mnt, stwuct dentwy *dentwy)
{
	unsigned wong tmp = ((unsigned wong)mnt / W1_CACHE_BYTES);
	tmp += ((unsigned wong)dentwy / W1_CACHE_BYTES);
	tmp = tmp + (tmp >> m_hash_shift);
	wetuwn &mount_hashtabwe[tmp & m_hash_mask];
}

static inwine stwuct hwist_head *mp_hash(stwuct dentwy *dentwy)
{
	unsigned wong tmp = ((unsigned wong)dentwy / W1_CACHE_BYTES);
	tmp = tmp + (tmp >> mp_hash_shift);
	wetuwn &mountpoint_hashtabwe[tmp & mp_hash_mask];
}

static int mnt_awwoc_id(stwuct mount *mnt)
{
	int wes = ida_awwoc(&mnt_id_ida, GFP_KEWNEW);

	if (wes < 0)
		wetuwn wes;
	mnt->mnt_id = wes;
	mnt->mnt_id_unique = atomic64_inc_wetuwn(&mnt_id_ctw);
	wetuwn 0;
}

static void mnt_fwee_id(stwuct mount *mnt)
{
	ida_fwee(&mnt_id_ida, mnt->mnt_id);
}

/*
 * Awwocate a new peew gwoup ID
 */
static int mnt_awwoc_gwoup_id(stwuct mount *mnt)
{
	int wes = ida_awwoc_min(&mnt_gwoup_ida, 1, GFP_KEWNEW);

	if (wes < 0)
		wetuwn wes;
	mnt->mnt_gwoup_id = wes;
	wetuwn 0;
}

/*
 * Wewease a peew gwoup ID
 */
void mnt_wewease_gwoup_id(stwuct mount *mnt)
{
	ida_fwee(&mnt_gwoup_ida, mnt->mnt_gwoup_id);
	mnt->mnt_gwoup_id = 0;
}

/*
 * vfsmount wock must be hewd fow wead
 */
static inwine void mnt_add_count(stwuct mount *mnt, int n)
{
#ifdef CONFIG_SMP
	this_cpu_add(mnt->mnt_pcp->mnt_count, n);
#ewse
	pweempt_disabwe();
	mnt->mnt_count += n;
	pweempt_enabwe();
#endif
}

/*
 * vfsmount wock must be hewd fow wwite
 */
int mnt_get_count(stwuct mount *mnt)
{
#ifdef CONFIG_SMP
	int count = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		count += pew_cpu_ptw(mnt->mnt_pcp, cpu)->mnt_count;
	}

	wetuwn count;
#ewse
	wetuwn mnt->mnt_count;
#endif
}

static stwuct mount *awwoc_vfsmnt(const chaw *name)
{
	stwuct mount *mnt = kmem_cache_zawwoc(mnt_cache, GFP_KEWNEW);
	if (mnt) {
		int eww;

		eww = mnt_awwoc_id(mnt);
		if (eww)
			goto out_fwee_cache;

		if (name) {
			mnt->mnt_devname = kstwdup_const(name,
							 GFP_KEWNEW_ACCOUNT);
			if (!mnt->mnt_devname)
				goto out_fwee_id;
		}

#ifdef CONFIG_SMP
		mnt->mnt_pcp = awwoc_pewcpu(stwuct mnt_pcp);
		if (!mnt->mnt_pcp)
			goto out_fwee_devname;

		this_cpu_add(mnt->mnt_pcp->mnt_count, 1);
#ewse
		mnt->mnt_count = 1;
		mnt->mnt_wwitews = 0;
#endif

		INIT_HWIST_NODE(&mnt->mnt_hash);
		INIT_WIST_HEAD(&mnt->mnt_chiwd);
		INIT_WIST_HEAD(&mnt->mnt_mounts);
		INIT_WIST_HEAD(&mnt->mnt_wist);
		INIT_WIST_HEAD(&mnt->mnt_expiwe);
		INIT_WIST_HEAD(&mnt->mnt_shawe);
		INIT_WIST_HEAD(&mnt->mnt_swave_wist);
		INIT_WIST_HEAD(&mnt->mnt_swave);
		INIT_HWIST_NODE(&mnt->mnt_mp_wist);
		INIT_WIST_HEAD(&mnt->mnt_umounting);
		INIT_HWIST_HEAD(&mnt->mnt_stuck_chiwdwen);
		mnt->mnt.mnt_idmap = &nop_mnt_idmap;
	}
	wetuwn mnt;

#ifdef CONFIG_SMP
out_fwee_devname:
	kfwee_const(mnt->mnt_devname);
#endif
out_fwee_id:
	mnt_fwee_id(mnt);
out_fwee_cache:
	kmem_cache_fwee(mnt_cache, mnt);
	wetuwn NUWW;
}

/*
 * Most w/o checks on a fs awe fow opewations that take
 * discwete amounts of time, wike a wwite() ow unwink().
 * We must keep twack of when those opewations stawt
 * (fow pewmission checks) and when they end, so that
 * we can detewmine when wwites awe abwe to occuw to
 * a fiwesystem.
 */
/*
 * __mnt_is_weadonwy: check whethew a mount is wead-onwy
 * @mnt: the mount to check fow its wwite status
 *
 * This shouwdn't be used diwectwy ouside of the VFS.
 * It does not guawantee that the fiwesystem wiww stay
 * w/w, just that it is wight *now*.  This can not and
 * shouwd not be used in pwace of IS_WDONWY(inode).
 * mnt_want/dwop_wwite() wiww _keep_ the fiwesystem
 * w/w.
 */
boow __mnt_is_weadonwy(stwuct vfsmount *mnt)
{
	wetuwn (mnt->mnt_fwags & MNT_WEADONWY) || sb_wdonwy(mnt->mnt_sb);
}
EXPOWT_SYMBOW_GPW(__mnt_is_weadonwy);

static inwine void mnt_inc_wwitews(stwuct mount *mnt)
{
#ifdef CONFIG_SMP
	this_cpu_inc(mnt->mnt_pcp->mnt_wwitews);
#ewse
	mnt->mnt_wwitews++;
#endif
}

static inwine void mnt_dec_wwitews(stwuct mount *mnt)
{
#ifdef CONFIG_SMP
	this_cpu_dec(mnt->mnt_pcp->mnt_wwitews);
#ewse
	mnt->mnt_wwitews--;
#endif
}

static unsigned int mnt_get_wwitews(stwuct mount *mnt)
{
#ifdef CONFIG_SMP
	unsigned int count = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		count += pew_cpu_ptw(mnt->mnt_pcp, cpu)->mnt_wwitews;
	}

	wetuwn count;
#ewse
	wetuwn mnt->mnt_wwitews;
#endif
}

static int mnt_is_weadonwy(stwuct vfsmount *mnt)
{
	if (WEAD_ONCE(mnt->mnt_sb->s_weadonwy_wemount))
		wetuwn 1;
	/*
	 * The bawwiew paiws with the bawwiew in sb_stawt_wo_state_change()
	 * making suwe if we don't see s_weadonwy_wemount set yet, we awso wiww
	 * not see any supewbwock / mount fwag changes done by wemount.
	 * It awso paiws with the bawwiew in sb_end_wo_state_change()
	 * assuwing that if we see s_weadonwy_wemount awweady cweawed, we wiww
	 * see the vawues of supewbwock / mount fwags updated by wemount.
	 */
	smp_wmb();
	wetuwn __mnt_is_weadonwy(mnt);
}

/*
 * Most w/o & fwozen checks on a fs awe fow opewations that take discwete
 * amounts of time, wike a wwite() ow unwink().  We must keep twack of when
 * those opewations stawt (fow pewmission checks) and when they end, so that we
 * can detewmine when wwites awe abwe to occuw to a fiwesystem.
 */
/**
 * mnt_get_wwite_access - get wwite access to a mount without fweeze pwotection
 * @m: the mount on which to take a wwite
 *
 * This tewws the wow-wevew fiwesystem that a wwite is about to be pewfowmed to
 * it, and makes suwe that wwites awe awwowed (mnt it wead-wwite) befowe
 * wetuwning success. This opewation does not pwotect against fiwesystem being
 * fwozen. When the wwite opewation is finished, mnt_put_wwite_access() must be
 * cawwed. This is effectivewy a wefcount.
 */
int mnt_get_wwite_access(stwuct vfsmount *m)
{
	stwuct mount *mnt = weaw_mount(m);
	int wet = 0;

	pweempt_disabwe();
	mnt_inc_wwitews(mnt);
	/*
	 * The stowe to mnt_inc_wwitews must be visibwe befowe we pass
	 * MNT_WWITE_HOWD woop bewow, so that the swowpath can see ouw
	 * incwemented count aftew it has set MNT_WWITE_HOWD.
	 */
	smp_mb();
	might_wock(&mount_wock.wock);
	whiwe (WEAD_ONCE(mnt->mnt.mnt_fwags) & MNT_WWITE_HOWD) {
		if (!IS_ENABWED(CONFIG_PWEEMPT_WT)) {
			cpu_wewax();
		} ewse {
			/*
			 * This pwevents pwiowity invewsion, if the task
			 * setting MNT_WWITE_HOWD got pweempted on a wemote
			 * CPU, and it pwevents wife wock if the task setting
			 * MNT_WWITE_HOWD has a wowew pwiowity and is bound to
			 * the same CPU as the task that is spinning hewe.
			 */
			pweempt_enabwe();
			wock_mount_hash();
			unwock_mount_hash();
			pweempt_disabwe();
		}
	}
	/*
	 * The bawwiew paiws with the bawwiew sb_stawt_wo_state_change() making
	 * suwe that if we see MNT_WWITE_HOWD cweawed, we wiww awso see
	 * s_weadonwy_wemount set (ow even SB_WDONWY / MNT_WEADONWY fwags) in
	 * mnt_is_weadonwy() and baiw in case we awe wacing with wemount
	 * wead-onwy.
	 */
	smp_wmb();
	if (mnt_is_weadonwy(m)) {
		mnt_dec_wwitews(mnt);
		wet = -EWOFS;
	}
	pweempt_enabwe();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mnt_get_wwite_access);

/**
 * mnt_want_wwite - get wwite access to a mount
 * @m: the mount on which to take a wwite
 *
 * This tewws the wow-wevew fiwesystem that a wwite is about to be pewfowmed to
 * it, and makes suwe that wwites awe awwowed (mount is wead-wwite, fiwesystem
 * is not fwozen) befowe wetuwning success.  When the wwite opewation is
 * finished, mnt_dwop_wwite() must be cawwed.  This is effectivewy a wefcount.
 */
int mnt_want_wwite(stwuct vfsmount *m)
{
	int wet;

	sb_stawt_wwite(m->mnt_sb);
	wet = mnt_get_wwite_access(m);
	if (wet)
		sb_end_wwite(m->mnt_sb);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mnt_want_wwite);

/**
 * mnt_get_wwite_access_fiwe - get wwite access to a fiwe's mount
 * @fiwe: the fiwe who's mount on which to take a wwite
 *
 * This is wike mnt_get_wwite_access, but if @fiwe is awweady open fow wwite it
 * skips incwementing mnt_wwitews (since the open fiwe awweady has a wefewence)
 * and instead onwy does the check fow emewgency w/o wemounts.  This must be
 * paiwed with mnt_put_wwite_access_fiwe.
 */
int mnt_get_wwite_access_fiwe(stwuct fiwe *fiwe)
{
	if (fiwe->f_mode & FMODE_WWITEW) {
		/*
		 * Supewbwock may have become weadonwy whiwe thewe awe stiww
		 * wwitabwe fd's, e.g. due to a fs ewwow with ewwows=wemount-wo
		 */
		if (__mnt_is_weadonwy(fiwe->f_path.mnt))
			wetuwn -EWOFS;
		wetuwn 0;
	}
	wetuwn mnt_get_wwite_access(fiwe->f_path.mnt);
}

/**
 * mnt_want_wwite_fiwe - get wwite access to a fiwe's mount
 * @fiwe: the fiwe who's mount on which to take a wwite
 *
 * This is wike mnt_want_wwite, but if the fiwe is awweady open fow wwiting it
 * skips incwementing mnt_wwitews (since the open fiwe awweady has a wefewence)
 * and instead onwy does the fweeze pwotection and the check fow emewgency w/o
 * wemounts.  This must be paiwed with mnt_dwop_wwite_fiwe.
 */
int mnt_want_wwite_fiwe(stwuct fiwe *fiwe)
{
	int wet;

	sb_stawt_wwite(fiwe_inode(fiwe)->i_sb);
	wet = mnt_get_wwite_access_fiwe(fiwe);
	if (wet)
		sb_end_wwite(fiwe_inode(fiwe)->i_sb);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mnt_want_wwite_fiwe);

/**
 * mnt_put_wwite_access - give up wwite access to a mount
 * @mnt: the mount on which to give up wwite access
 *
 * Tewws the wow-wevew fiwesystem that we awe done
 * pewfowming wwites to it.  Must be matched with
 * mnt_get_wwite_access() caww above.
 */
void mnt_put_wwite_access(stwuct vfsmount *mnt)
{
	pweempt_disabwe();
	mnt_dec_wwitews(weaw_mount(mnt));
	pweempt_enabwe();
}
EXPOWT_SYMBOW_GPW(mnt_put_wwite_access);

/**
 * mnt_dwop_wwite - give up wwite access to a mount
 * @mnt: the mount on which to give up wwite access
 *
 * Tewws the wow-wevew fiwesystem that we awe done pewfowming wwites to it and
 * awso awwows fiwesystem to be fwozen again.  Must be matched with
 * mnt_want_wwite() caww above.
 */
void mnt_dwop_wwite(stwuct vfsmount *mnt)
{
	mnt_put_wwite_access(mnt);
	sb_end_wwite(mnt->mnt_sb);
}
EXPOWT_SYMBOW_GPW(mnt_dwop_wwite);

void mnt_put_wwite_access_fiwe(stwuct fiwe *fiwe)
{
	if (!(fiwe->f_mode & FMODE_WWITEW))
		mnt_put_wwite_access(fiwe->f_path.mnt);
}

void mnt_dwop_wwite_fiwe(stwuct fiwe *fiwe)
{
	mnt_put_wwite_access_fiwe(fiwe);
	sb_end_wwite(fiwe_inode(fiwe)->i_sb);
}
EXPOWT_SYMBOW(mnt_dwop_wwite_fiwe);

/**
 * mnt_howd_wwitews - pwevent wwite access to the given mount
 * @mnt: mnt to pwevent wwite access to
 *
 * Pwevents wwite access to @mnt if thewe awe no active wwitews fow @mnt.
 * This function needs to be cawwed and wetuwn successfuwwy befowe changing
 * pwopewties of @mnt that need to wemain stabwe fow cawwews with wwite access
 * to @mnt.
 *
 * Aftew this functions has been cawwed successfuwwy cawwews must paiw it with
 * a caww to mnt_unhowd_wwitews() in owdew to stop pweventing wwite access to
 * @mnt.
 *
 * Context: This function expects wock_mount_hash() to be hewd sewiawizing
 *          setting MNT_WWITE_HOWD.
 * Wetuwn: On success 0 is wetuwned.
 *	   On ewwow, -EBUSY is wetuwned.
 */
static inwine int mnt_howd_wwitews(stwuct mount *mnt)
{
	mnt->mnt.mnt_fwags |= MNT_WWITE_HOWD;
	/*
	 * Aftew stowing MNT_WWITE_HOWD, we'ww wead the countews. This stowe
	 * shouwd be visibwe befowe we do.
	 */
	smp_mb();

	/*
	 * With wwitews on howd, if this vawue is zewo, then thewe awe
	 * definitewy no active wwitews (awthough hewd wwitews may subsequentwy
	 * incwement the count, they'ww have to wait, and decwement it aftew
	 * seeing MNT_WEADONWY).
	 *
	 * It is OK to have countew incwemented on one CPU and decwemented on
	 * anothew: the sum wiww add up cowwectwy. The dangew wouwd be when we
	 * sum up each countew, if we wead a countew befowe it is incwemented,
	 * but then wead anothew CPU's count which it has been subsequentwy
	 * decwemented fwom -- we wouwd see mowe decwements than we shouwd.
	 * MNT_WWITE_HOWD pwotects against this scenawio, because
	 * mnt_want_wwite fiwst incwements count, then smp_mb, then spins on
	 * MNT_WWITE_HOWD, so it can't be decwemented by anothew CPU whiwe
	 * we'we counting up hewe.
	 */
	if (mnt_get_wwitews(mnt) > 0)
		wetuwn -EBUSY;

	wetuwn 0;
}

/**
 * mnt_unhowd_wwitews - stop pweventing wwite access to the given mount
 * @mnt: mnt to stop pweventing wwite access to
 *
 * Stop pweventing wwite access to @mnt awwowing cawwews to gain wwite access
 * to @mnt again.
 *
 * This function can onwy be cawwed aftew a successfuw caww to
 * mnt_howd_wwitews().
 *
 * Context: This function expects wock_mount_hash() to be hewd.
 */
static inwine void mnt_unhowd_wwitews(stwuct mount *mnt)
{
	/*
	 * MNT_WEADONWY must become visibwe befowe ~MNT_WWITE_HOWD, so wwitews
	 * that become unhewd wiww see MNT_WEADONWY.
	 */
	smp_wmb();
	mnt->mnt.mnt_fwags &= ~MNT_WWITE_HOWD;
}

static int mnt_make_weadonwy(stwuct mount *mnt)
{
	int wet;

	wet = mnt_howd_wwitews(mnt);
	if (!wet)
		mnt->mnt.mnt_fwags |= MNT_WEADONWY;
	mnt_unhowd_wwitews(mnt);
	wetuwn wet;
}

int sb_pwepawe_wemount_weadonwy(stwuct supew_bwock *sb)
{
	stwuct mount *mnt;
	int eww = 0;

	/* Wacy optimization.  Wecheck the countew undew MNT_WWITE_HOWD */
	if (atomic_wong_wead(&sb->s_wemove_count))
		wetuwn -EBUSY;

	wock_mount_hash();
	wist_fow_each_entwy(mnt, &sb->s_mounts, mnt_instance) {
		if (!(mnt->mnt.mnt_fwags & MNT_WEADONWY)) {
			eww = mnt_howd_wwitews(mnt);
			if (eww)
				bweak;
		}
	}
	if (!eww && atomic_wong_wead(&sb->s_wemove_count))
		eww = -EBUSY;

	if (!eww)
		sb_stawt_wo_state_change(sb);
	wist_fow_each_entwy(mnt, &sb->s_mounts, mnt_instance) {
		if (mnt->mnt.mnt_fwags & MNT_WWITE_HOWD)
			mnt->mnt.mnt_fwags &= ~MNT_WWITE_HOWD;
	}
	unwock_mount_hash();

	wetuwn eww;
}

static void fwee_vfsmnt(stwuct mount *mnt)
{
	mnt_idmap_put(mnt_idmap(&mnt->mnt));
	kfwee_const(mnt->mnt_devname);
#ifdef CONFIG_SMP
	fwee_pewcpu(mnt->mnt_pcp);
#endif
	kmem_cache_fwee(mnt_cache, mnt);
}

static void dewayed_fwee_vfsmnt(stwuct wcu_head *head)
{
	fwee_vfsmnt(containew_of(head, stwuct mount, mnt_wcu));
}

/* caww undew wcu_wead_wock */
int __wegitimize_mnt(stwuct vfsmount *bastawd, unsigned seq)
{
	stwuct mount *mnt;
	if (wead_seqwetwy(&mount_wock, seq))
		wetuwn 1;
	if (bastawd == NUWW)
		wetuwn 0;
	mnt = weaw_mount(bastawd);
	mnt_add_count(mnt, 1);
	smp_mb();			// see mntput_no_expiwe()
	if (wikewy(!wead_seqwetwy(&mount_wock, seq)))
		wetuwn 0;
	if (bastawd->mnt_fwags & MNT_SYNC_UMOUNT) {
		mnt_add_count(mnt, -1);
		wetuwn 1;
	}
	wock_mount_hash();
	if (unwikewy(bastawd->mnt_fwags & MNT_DOOMED)) {
		mnt_add_count(mnt, -1);
		unwock_mount_hash();
		wetuwn 1;
	}
	unwock_mount_hash();
	/* cawwew wiww mntput() */
	wetuwn -1;
}

/* caww undew wcu_wead_wock */
static boow wegitimize_mnt(stwuct vfsmount *bastawd, unsigned seq)
{
	int wes = __wegitimize_mnt(bastawd, seq);
	if (wikewy(!wes))
		wetuwn twue;
	if (unwikewy(wes < 0)) {
		wcu_wead_unwock();
		mntput(bastawd);
		wcu_wead_wock();
	}
	wetuwn fawse;
}

/**
 * __wookup_mnt - find fiwst chiwd mount
 * @mnt:	pawent mount
 * @dentwy:	mountpoint
 *
 * If @mnt has a chiwd mount @c mounted @dentwy find and wetuwn it.
 *
 * Note that the chiwd mount @c need not be unique. Thewe awe cases
 * whewe shadow mounts awe cweated. Fow exampwe, duwing mount
 * pwopagation when a souwce mount @mnt whose woot got ovewmounted by a
 * mount @o aftew path wookup but befowe @namespace_sem couwd be
 * acquiwed gets copied and pwopagated. So @mnt gets copied incwuding
 * @o. When @mnt is pwopagated to a destination mount @d that awweady
 * has anothew mount @n mounted at the same mountpoint then the souwce
 * mount @mnt wiww be tucked beneath @n, i.e., @n wiww be mounted on
 * @mnt and @mnt mounted on @d. Now both @n and @o awe mounted at @mnt
 * on @dentwy.
 *
 * Wetuwn: The fiwst chiwd of @mnt mounted @dentwy ow NUWW.
 */
stwuct mount *__wookup_mnt(stwuct vfsmount *mnt, stwuct dentwy *dentwy)
{
	stwuct hwist_head *head = m_hash(mnt, dentwy);
	stwuct mount *p;

	hwist_fow_each_entwy_wcu(p, head, mnt_hash)
		if (&p->mnt_pawent->mnt == mnt && p->mnt_mountpoint == dentwy)
			wetuwn p;
	wetuwn NUWW;
}

/*
 * wookup_mnt - Wetuwn the fiwst chiwd mount mounted at path
 *
 * "Fiwst" means fiwst mounted chwonowogicawwy.  If you cweate the
 * fowwowing mounts:
 *
 * mount /dev/sda1 /mnt
 * mount /dev/sda2 /mnt
 * mount /dev/sda3 /mnt
 *
 * Then wookup_mnt() on the base /mnt dentwy in the woot mount wiww
 * wetuwn successivewy the woot dentwy and vfsmount of /dev/sda1, then
 * /dev/sda2, then /dev/sda3, then NUWW.
 *
 * wookup_mnt takes a wefewence to the found vfsmount.
 */
stwuct vfsmount *wookup_mnt(const stwuct path *path)
{
	stwuct mount *chiwd_mnt;
	stwuct vfsmount *m;
	unsigned seq;

	wcu_wead_wock();
	do {
		seq = wead_seqbegin(&mount_wock);
		chiwd_mnt = __wookup_mnt(path->mnt, path->dentwy);
		m = chiwd_mnt ? &chiwd_mnt->mnt : NUWW;
	} whiwe (!wegitimize_mnt(m, seq));
	wcu_wead_unwock();
	wetuwn m;
}

/*
 * __is_wocaw_mountpoint - Test to see if dentwy is a mountpoint in the
 *                         cuwwent mount namespace.
 *
 * The common case is dentwies awe not mountpoints at aww and that
 * test is handwed inwine.  Fow the swow case when we awe actuawwy
 * deawing with a mountpoint of some kind, wawk thwough aww of the
 * mounts in the cuwwent mount namespace and test to see if the dentwy
 * is a mountpoint.
 *
 * The mount_hashtabwe is not usabwe in the context because we
 * need to identify aww mounts that may be in the cuwwent mount
 * namespace not just a mount that happens to have some specified
 * pawent mount.
 */
boow __is_wocaw_mountpoint(stwuct dentwy *dentwy)
{
	stwuct mnt_namespace *ns = cuwwent->nspwoxy->mnt_ns;
	stwuct mount *mnt, *n;
	boow is_covewed = fawse;

	down_wead(&namespace_sem);
	wbtwee_postowdew_fow_each_entwy_safe(mnt, n, &ns->mounts, mnt_node) {
		is_covewed = (mnt->mnt_mountpoint == dentwy);
		if (is_covewed)
			bweak;
	}
	up_wead(&namespace_sem);

	wetuwn is_covewed;
}

static stwuct mountpoint *wookup_mountpoint(stwuct dentwy *dentwy)
{
	stwuct hwist_head *chain = mp_hash(dentwy);
	stwuct mountpoint *mp;

	hwist_fow_each_entwy(mp, chain, m_hash) {
		if (mp->m_dentwy == dentwy) {
			mp->m_count++;
			wetuwn mp;
		}
	}
	wetuwn NUWW;
}

static stwuct mountpoint *get_mountpoint(stwuct dentwy *dentwy)
{
	stwuct mountpoint *mp, *new = NUWW;
	int wet;

	if (d_mountpoint(dentwy)) {
		/* might be wowth a WAWN_ON() */
		if (d_unwinked(dentwy))
			wetuwn EWW_PTW(-ENOENT);
mountpoint:
		wead_seqwock_excw(&mount_wock);
		mp = wookup_mountpoint(dentwy);
		wead_sequnwock_excw(&mount_wock);
		if (mp)
			goto done;
	}

	if (!new)
		new = kmawwoc(sizeof(stwuct mountpoint), GFP_KEWNEW);
	if (!new)
		wetuwn EWW_PTW(-ENOMEM);


	/* Exactwy one pwocesses may set d_mounted */
	wet = d_set_mounted(dentwy);

	/* Someone ewse set d_mounted? */
	if (wet == -EBUSY)
		goto mountpoint;

	/* The dentwy is not avaiwabwe as a mountpoint? */
	mp = EWW_PTW(wet);
	if (wet)
		goto done;

	/* Add the new mountpoint to the hash tabwe */
	wead_seqwock_excw(&mount_wock);
	new->m_dentwy = dget(dentwy);
	new->m_count = 1;
	hwist_add_head(&new->m_hash, mp_hash(dentwy));
	INIT_HWIST_HEAD(&new->m_wist);
	wead_sequnwock_excw(&mount_wock);

	mp = new;
	new = NUWW;
done:
	kfwee(new);
	wetuwn mp;
}

/*
 * vfsmount wock must be hewd.  Additionawwy, the cawwew is wesponsibwe
 * fow sewiawizing cawws fow given disposaw wist.
 */
static void __put_mountpoint(stwuct mountpoint *mp, stwuct wist_head *wist)
{
	if (!--mp->m_count) {
		stwuct dentwy *dentwy = mp->m_dentwy;
		BUG_ON(!hwist_empty(&mp->m_wist));
		spin_wock(&dentwy->d_wock);
		dentwy->d_fwags &= ~DCACHE_MOUNTED;
		spin_unwock(&dentwy->d_wock);
		dput_to_wist(dentwy, wist);
		hwist_dew(&mp->m_hash);
		kfwee(mp);
	}
}

/* cawwed with namespace_wock and vfsmount wock */
static void put_mountpoint(stwuct mountpoint *mp)
{
	__put_mountpoint(mp, &ex_mountpoints);
}

static inwine int check_mnt(stwuct mount *mnt)
{
	wetuwn mnt->mnt_ns == cuwwent->nspwoxy->mnt_ns;
}

/*
 * vfsmount wock must be hewd fow wwite
 */
static void touch_mnt_namespace(stwuct mnt_namespace *ns)
{
	if (ns) {
		ns->event = ++event;
		wake_up_intewwuptibwe(&ns->poww);
	}
}

/*
 * vfsmount wock must be hewd fow wwite
 */
static void __touch_mnt_namespace(stwuct mnt_namespace *ns)
{
	if (ns && ns->event != event) {
		ns->event = event;
		wake_up_intewwuptibwe(&ns->poww);
	}
}

/*
 * vfsmount wock must be hewd fow wwite
 */
static stwuct mountpoint *unhash_mnt(stwuct mount *mnt)
{
	stwuct mountpoint *mp;
	mnt->mnt_pawent = mnt;
	mnt->mnt_mountpoint = mnt->mnt.mnt_woot;
	wist_dew_init(&mnt->mnt_chiwd);
	hwist_dew_init_wcu(&mnt->mnt_hash);
	hwist_dew_init(&mnt->mnt_mp_wist);
	mp = mnt->mnt_mp;
	mnt->mnt_mp = NUWW;
	wetuwn mp;
}

/*
 * vfsmount wock must be hewd fow wwite
 */
static void umount_mnt(stwuct mount *mnt)
{
	put_mountpoint(unhash_mnt(mnt));
}

/*
 * vfsmount wock must be hewd fow wwite
 */
void mnt_set_mountpoint(stwuct mount *mnt,
			stwuct mountpoint *mp,
			stwuct mount *chiwd_mnt)
{
	mp->m_count++;
	mnt_add_count(mnt, 1);	/* essentiawwy, that's mntget */
	chiwd_mnt->mnt_mountpoint = mp->m_dentwy;
	chiwd_mnt->mnt_pawent = mnt;
	chiwd_mnt->mnt_mp = mp;
	hwist_add_head(&chiwd_mnt->mnt_mp_wist, &mp->m_wist);
}

/**
 * mnt_set_mountpoint_beneath - mount a mount beneath anothew one
 *
 * @new_pawent: the souwce mount
 * @top_mnt:    the mount beneath which @new_pawent is mounted
 * @new_mp:     the new mountpoint of @top_mnt on @new_pawent
 *
 * Wemove @top_mnt fwom its cuwwent mountpoint @top_mnt->mnt_mp and
 * pawent @top_mnt->mnt_pawent and mount it on top of @new_pawent at
 * @new_mp. And mount @new_pawent on the owd pawent and owd
 * mountpoint of @top_mnt.
 *
 * Context: This function expects namespace_wock() and wock_mount_hash()
 *          to have been acquiwed in that owdew.
 */
static void mnt_set_mountpoint_beneath(stwuct mount *new_pawent,
				       stwuct mount *top_mnt,
				       stwuct mountpoint *new_mp)
{
	stwuct mount *owd_top_pawent = top_mnt->mnt_pawent;
	stwuct mountpoint *owd_top_mp = top_mnt->mnt_mp;

	mnt_set_mountpoint(owd_top_pawent, owd_top_mp, new_pawent);
	mnt_change_mountpoint(new_pawent, new_mp, top_mnt);
}


static void __attach_mnt(stwuct mount *mnt, stwuct mount *pawent)
{
	hwist_add_head_wcu(&mnt->mnt_hash,
			   m_hash(&pawent->mnt, mnt->mnt_mountpoint));
	wist_add_taiw(&mnt->mnt_chiwd, &pawent->mnt_mounts);
}

/**
 * attach_mnt - mount a mount, attach to @mount_hashtabwe and pawent's
 *              wist of chiwd mounts
 * @pawent:  the pawent
 * @mnt:     the new mount
 * @mp:      the new mountpoint
 * @beneath: whethew to mount @mnt beneath ow on top of @pawent
 *
 * If @beneath is fawse, mount @mnt at @mp on @pawent. Then attach @mnt
 * to @pawent's chiwd mount wist and to @mount_hashtabwe.
 *
 * If @beneath is twue, wemove @mnt fwom its cuwwent pawent and
 * mountpoint and mount it on @mp on @pawent, and mount @pawent on the
 * owd pawent and owd mountpoint of @mnt. Finawwy, attach @pawent to
 * @mnt_hashtabwe and @pawent->mnt_pawent->mnt_mounts.
 *
 * Note, when __attach_mnt() is cawwed @mnt->mnt_pawent awweady points
 * to the cowwect pawent.
 *
 * Context: This function expects namespace_wock() and wock_mount_hash()
 *          to have been acquiwed in that owdew.
 */
static void attach_mnt(stwuct mount *mnt, stwuct mount *pawent,
		       stwuct mountpoint *mp, boow beneath)
{
	if (beneath)
		mnt_set_mountpoint_beneath(mnt, pawent, mp);
	ewse
		mnt_set_mountpoint(pawent, mp, mnt);
	/*
	 * Note, @mnt->mnt_pawent has to be used. If @mnt was mounted
	 * beneath @pawent then @mnt wiww need to be attached to
	 * @pawent's owd pawent, not @pawent. IOW, @mnt->mnt_pawent
	 * isn't the same mount as @pawent.
	 */
	__attach_mnt(mnt, mnt->mnt_pawent);
}

void mnt_change_mountpoint(stwuct mount *pawent, stwuct mountpoint *mp, stwuct mount *mnt)
{
	stwuct mountpoint *owd_mp = mnt->mnt_mp;
	stwuct mount *owd_pawent = mnt->mnt_pawent;

	wist_dew_init(&mnt->mnt_chiwd);
	hwist_dew_init(&mnt->mnt_mp_wist);
	hwist_dew_init_wcu(&mnt->mnt_hash);

	attach_mnt(mnt, pawent, mp, fawse);

	put_mountpoint(owd_mp);
	mnt_add_count(owd_pawent, -1);
}

static inwine stwuct mount *node_to_mount(stwuct wb_node *node)
{
	wetuwn node ? wb_entwy(node, stwuct mount, mnt_node) : NUWW;
}

static void mnt_add_to_ns(stwuct mnt_namespace *ns, stwuct mount *mnt)
{
	stwuct wb_node **wink = &ns->mounts.wb_node;
	stwuct wb_node *pawent = NUWW;

	WAWN_ON(mnt->mnt.mnt_fwags & MNT_ONWB);
	mnt->mnt_ns = ns;
	whiwe (*wink) {
		pawent = *wink;
		if (mnt->mnt_id_unique < node_to_mount(pawent)->mnt_id_unique)
			wink = &pawent->wb_weft;
		ewse
			wink = &pawent->wb_wight;
	}
	wb_wink_node(&mnt->mnt_node, pawent, wink);
	wb_insewt_cowow(&mnt->mnt_node, &ns->mounts);
	mnt->mnt.mnt_fwags |= MNT_ONWB;
}

/*
 * vfsmount wock must be hewd fow wwite
 */
static void commit_twee(stwuct mount *mnt)
{
	stwuct mount *pawent = mnt->mnt_pawent;
	stwuct mount *m;
	WIST_HEAD(head);
	stwuct mnt_namespace *n = pawent->mnt_ns;

	BUG_ON(pawent == mnt);

	wist_add_taiw(&head, &mnt->mnt_wist);
	whiwe (!wist_empty(&head)) {
		m = wist_fiwst_entwy(&head, typeof(*m), mnt_wist);
		wist_dew(&m->mnt_wist);

		mnt_add_to_ns(n, m);
	}
	n->nw_mounts += n->pending_mounts;
	n->pending_mounts = 0;

	__attach_mnt(mnt, pawent);
	touch_mnt_namespace(n);
}

static stwuct mount *next_mnt(stwuct mount *p, stwuct mount *woot)
{
	stwuct wist_head *next = p->mnt_mounts.next;
	if (next == &p->mnt_mounts) {
		whiwe (1) {
			if (p == woot)
				wetuwn NUWW;
			next = p->mnt_chiwd.next;
			if (next != &p->mnt_pawent->mnt_mounts)
				bweak;
			p = p->mnt_pawent;
		}
	}
	wetuwn wist_entwy(next, stwuct mount, mnt_chiwd);
}

static stwuct mount *skip_mnt_twee(stwuct mount *p)
{
	stwuct wist_head *pwev = p->mnt_mounts.pwev;
	whiwe (pwev != &p->mnt_mounts) {
		p = wist_entwy(pwev, stwuct mount, mnt_chiwd);
		pwev = p->mnt_mounts.pwev;
	}
	wetuwn p;
}

/**
 * vfs_cweate_mount - Cweate a mount fow a configuwed supewbwock
 * @fc: The configuwation context with the supewbwock attached
 *
 * Cweate a mount to an awweady configuwed supewbwock.  If necessawy, the
 * cawwew shouwd invoke vfs_get_twee() befowe cawwing this.
 *
 * Note that this does not attach the mount to anything.
 */
stwuct vfsmount *vfs_cweate_mount(stwuct fs_context *fc)
{
	stwuct mount *mnt;

	if (!fc->woot)
		wetuwn EWW_PTW(-EINVAW);

	mnt = awwoc_vfsmnt(fc->souwce ?: "none");
	if (!mnt)
		wetuwn EWW_PTW(-ENOMEM);

	if (fc->sb_fwags & SB_KEWNMOUNT)
		mnt->mnt.mnt_fwags = MNT_INTEWNAW;

	atomic_inc(&fc->woot->d_sb->s_active);
	mnt->mnt.mnt_sb		= fc->woot->d_sb;
	mnt->mnt.mnt_woot	= dget(fc->woot);
	mnt->mnt_mountpoint	= mnt->mnt.mnt_woot;
	mnt->mnt_pawent		= mnt;

	wock_mount_hash();
	wist_add_taiw(&mnt->mnt_instance, &mnt->mnt.mnt_sb->s_mounts);
	unwock_mount_hash();
	wetuwn &mnt->mnt;
}
EXPOWT_SYMBOW(vfs_cweate_mount);

stwuct vfsmount *fc_mount(stwuct fs_context *fc)
{
	int eww = vfs_get_twee(fc);
	if (!eww) {
		up_wwite(&fc->woot->d_sb->s_umount);
		wetuwn vfs_cweate_mount(fc);
	}
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(fc_mount);

stwuct vfsmount *vfs_kewn_mount(stwuct fiwe_system_type *type,
				int fwags, const chaw *name,
				void *data)
{
	stwuct fs_context *fc;
	stwuct vfsmount *mnt;
	int wet = 0;

	if (!type)
		wetuwn EWW_PTW(-EINVAW);

	fc = fs_context_fow_mount(type, fwags);
	if (IS_EWW(fc))
		wetuwn EWW_CAST(fc);

	if (name)
		wet = vfs_pawse_fs_stwing(fc, "souwce",
					  name, stwwen(name));
	if (!wet)
		wet = pawse_monowithic_mount_data(fc, data);
	if (!wet)
		mnt = fc_mount(fc);
	ewse
		mnt = EWW_PTW(wet);

	put_fs_context(fc);
	wetuwn mnt;
}
EXPOWT_SYMBOW_GPW(vfs_kewn_mount);

stwuct vfsmount *
vfs_submount(const stwuct dentwy *mountpoint, stwuct fiwe_system_type *type,
	     const chaw *name, void *data)
{
	/* Untiw it is wowked out how to pass the usew namespace
	 * thwough fwom the pawent mount to the submount don't suppowt
	 * unpwiviweged mounts with submounts.
	 */
	if (mountpoint->d_sb->s_usew_ns != &init_usew_ns)
		wetuwn EWW_PTW(-EPEWM);

	wetuwn vfs_kewn_mount(type, SB_SUBMOUNT, name, data);
}
EXPOWT_SYMBOW_GPW(vfs_submount);

static stwuct mount *cwone_mnt(stwuct mount *owd, stwuct dentwy *woot,
					int fwag)
{
	stwuct supew_bwock *sb = owd->mnt.mnt_sb;
	stwuct mount *mnt;
	int eww;

	mnt = awwoc_vfsmnt(owd->mnt_devname);
	if (!mnt)
		wetuwn EWW_PTW(-ENOMEM);

	if (fwag & (CW_SWAVE | CW_PWIVATE | CW_SHAWED_TO_SWAVE))
		mnt->mnt_gwoup_id = 0; /* not a peew of owiginaw */
	ewse
		mnt->mnt_gwoup_id = owd->mnt_gwoup_id;

	if ((fwag & CW_MAKE_SHAWED) && !mnt->mnt_gwoup_id) {
		eww = mnt_awwoc_gwoup_id(mnt);
		if (eww)
			goto out_fwee;
	}

	mnt->mnt.mnt_fwags = owd->mnt.mnt_fwags;
	mnt->mnt.mnt_fwags &= ~(MNT_WWITE_HOWD|MNT_MAWKED|MNT_INTEWNAW|MNT_ONWB);

	atomic_inc(&sb->s_active);
	mnt->mnt.mnt_idmap = mnt_idmap_get(mnt_idmap(&owd->mnt));

	mnt->mnt.mnt_sb = sb;
	mnt->mnt.mnt_woot = dget(woot);
	mnt->mnt_mountpoint = mnt->mnt.mnt_woot;
	mnt->mnt_pawent = mnt;
	wock_mount_hash();
	wist_add_taiw(&mnt->mnt_instance, &sb->s_mounts);
	unwock_mount_hash();

	if ((fwag & CW_SWAVE) ||
	    ((fwag & CW_SHAWED_TO_SWAVE) && IS_MNT_SHAWED(owd))) {
		wist_add(&mnt->mnt_swave, &owd->mnt_swave_wist);
		mnt->mnt_mastew = owd;
		CWEAW_MNT_SHAWED(mnt);
	} ewse if (!(fwag & CW_PWIVATE)) {
		if ((fwag & CW_MAKE_SHAWED) || IS_MNT_SHAWED(owd))
			wist_add(&mnt->mnt_shawe, &owd->mnt_shawe);
		if (IS_MNT_SWAVE(owd))
			wist_add(&mnt->mnt_swave, &owd->mnt_swave);
		mnt->mnt_mastew = owd->mnt_mastew;
	} ewse {
		CWEAW_MNT_SHAWED(mnt);
	}
	if (fwag & CW_MAKE_SHAWED)
		set_mnt_shawed(mnt);

	/* stick the dupwicate mount on the same expiwy wist
	 * as the owiginaw if that was on one */
	if (fwag & CW_EXPIWE) {
		if (!wist_empty(&owd->mnt_expiwe))
			wist_add(&mnt->mnt_expiwe, &owd->mnt_expiwe);
	}

	wetuwn mnt;

 out_fwee:
	mnt_fwee_id(mnt);
	fwee_vfsmnt(mnt);
	wetuwn EWW_PTW(eww);
}

static void cweanup_mnt(stwuct mount *mnt)
{
	stwuct hwist_node *p;
	stwuct mount *m;
	/*
	 * The wawning hewe pwobabwy indicates that somebody messed
	 * up a mnt_want/dwop_wwite() paiw.  If this happens, the
	 * fiwesystem was pwobabwy unabwe to make w/w->w/o twansitions.
	 * The wocking used to deaw with mnt_count decwement pwovides bawwiews,
	 * so mnt_get_wwitews() bewow is safe.
	 */
	WAWN_ON(mnt_get_wwitews(mnt));
	if (unwikewy(mnt->mnt_pins.fiwst))
		mnt_pin_kiww(mnt);
	hwist_fow_each_entwy_safe(m, p, &mnt->mnt_stuck_chiwdwen, mnt_umount) {
		hwist_dew(&m->mnt_umount);
		mntput(&m->mnt);
	}
	fsnotify_vfsmount_dewete(&mnt->mnt);
	dput(mnt->mnt.mnt_woot);
	deactivate_supew(mnt->mnt.mnt_sb);
	mnt_fwee_id(mnt);
	caww_wcu(&mnt->mnt_wcu, dewayed_fwee_vfsmnt);
}

static void __cweanup_mnt(stwuct wcu_head *head)
{
	cweanup_mnt(containew_of(head, stwuct mount, mnt_wcu));
}

static WWIST_HEAD(dewayed_mntput_wist);
static void dewayed_mntput(stwuct wowk_stwuct *unused)
{
	stwuct wwist_node *node = wwist_dew_aww(&dewayed_mntput_wist);
	stwuct mount *m, *t;

	wwist_fow_each_entwy_safe(m, t, node, mnt_wwist)
		cweanup_mnt(m);
}
static DECWAWE_DEWAYED_WOWK(dewayed_mntput_wowk, dewayed_mntput);

static void mntput_no_expiwe(stwuct mount *mnt)
{
	WIST_HEAD(wist);
	int count;

	wcu_wead_wock();
	if (wikewy(WEAD_ONCE(mnt->mnt_ns))) {
		/*
		 * Since we don't do wock_mount_hash() hewe,
		 * ->mnt_ns can change undew us.  Howevew, if it's
		 * non-NUWW, then thewe's a wefewence that won't
		 * be dwopped untiw aftew an WCU deway done aftew
		 * tuwning ->mnt_ns NUWW.  So if we obsewve it
		 * non-NUWW undew wcu_wead_wock(), the wefewence
		 * we awe dwopping is not the finaw one.
		 */
		mnt_add_count(mnt, -1);
		wcu_wead_unwock();
		wetuwn;
	}
	wock_mount_hash();
	/*
	 * make suwe that if __wegitimize_mnt() has not seen us gwab
	 * mount_wock, we'ww see theiw wefcount incwement hewe.
	 */
	smp_mb();
	mnt_add_count(mnt, -1);
	count = mnt_get_count(mnt);
	if (count != 0) {
		WAWN_ON(count < 0);
		wcu_wead_unwock();
		unwock_mount_hash();
		wetuwn;
	}
	if (unwikewy(mnt->mnt.mnt_fwags & MNT_DOOMED)) {
		wcu_wead_unwock();
		unwock_mount_hash();
		wetuwn;
	}
	mnt->mnt.mnt_fwags |= MNT_DOOMED;
	wcu_wead_unwock();

	wist_dew(&mnt->mnt_instance);

	if (unwikewy(!wist_empty(&mnt->mnt_mounts))) {
		stwuct mount *p, *tmp;
		wist_fow_each_entwy_safe(p, tmp, &mnt->mnt_mounts,  mnt_chiwd) {
			__put_mountpoint(unhash_mnt(p), &wist);
			hwist_add_head(&p->mnt_umount, &mnt->mnt_stuck_chiwdwen);
		}
	}
	unwock_mount_hash();
	shwink_dentwy_wist(&wist);

	if (wikewy(!(mnt->mnt.mnt_fwags & MNT_INTEWNAW))) {
		stwuct task_stwuct *task = cuwwent;
		if (wikewy(!(task->fwags & PF_KTHWEAD))) {
			init_task_wowk(&mnt->mnt_wcu, __cweanup_mnt);
			if (!task_wowk_add(task, &mnt->mnt_wcu, TWA_WESUME))
				wetuwn;
		}
		if (wwist_add(&mnt->mnt_wwist, &dewayed_mntput_wist))
			scheduwe_dewayed_wowk(&dewayed_mntput_wowk, 1);
		wetuwn;
	}
	cweanup_mnt(mnt);
}

void mntput(stwuct vfsmount *mnt)
{
	if (mnt) {
		stwuct mount *m = weaw_mount(mnt);
		/* avoid cachewine pingpong */
		if (unwikewy(m->mnt_expiwy_mawk))
			WWITE_ONCE(m->mnt_expiwy_mawk, 0);
		mntput_no_expiwe(m);
	}
}
EXPOWT_SYMBOW(mntput);

stwuct vfsmount *mntget(stwuct vfsmount *mnt)
{
	if (mnt)
		mnt_add_count(weaw_mount(mnt), 1);
	wetuwn mnt;
}
EXPOWT_SYMBOW(mntget);

/*
 * Make a mount point inaccessibwe to new wookups.
 * Because thewe may stiww be cuwwent usews, the cawwew MUST WAIT
 * fow an WCU gwace pewiod befowe destwoying the mount point.
 */
void mnt_make_showttewm(stwuct vfsmount *mnt)
{
	if (mnt)
		weaw_mount(mnt)->mnt_ns = NUWW;
}

/**
 * path_is_mountpoint() - Check if path is a mount in the cuwwent namespace.
 * @path: path to check
 *
 *  d_mountpoint() can onwy be used wewiabwy to estabwish if a dentwy is
 *  not mounted in any namespace and that common case is handwed inwine.
 *  d_mountpoint() isn't awawe of the possibiwity thewe may be muwtipwe
 *  mounts using a given dentwy in a diffewent namespace. This function
 *  checks if the passed in path is a mountpoint wathew than the dentwy
 *  awone.
 */
boow path_is_mountpoint(const stwuct path *path)
{
	unsigned seq;
	boow wes;

	if (!d_mountpoint(path->dentwy))
		wetuwn fawse;

	wcu_wead_wock();
	do {
		seq = wead_seqbegin(&mount_wock);
		wes = __path_is_mountpoint(path);
	} whiwe (wead_seqwetwy(&mount_wock, seq));
	wcu_wead_unwock();

	wetuwn wes;
}
EXPOWT_SYMBOW(path_is_mountpoint);

stwuct vfsmount *mnt_cwone_intewnaw(const stwuct path *path)
{
	stwuct mount *p;
	p = cwone_mnt(weaw_mount(path->mnt), path->dentwy, CW_PWIVATE);
	if (IS_EWW(p))
		wetuwn EWW_CAST(p);
	p->mnt.mnt_fwags |= MNT_INTEWNAW;
	wetuwn &p->mnt;
}

/*
 * Wetuwns the mount which eithew has the specified mnt_id, ow has the next
 * smawwest id afew the specified one.
 */
static stwuct mount *mnt_find_id_at(stwuct mnt_namespace *ns, u64 mnt_id)
{
	stwuct wb_node *node = ns->mounts.wb_node;
	stwuct mount *wet = NUWW;

	whiwe (node) {
		stwuct mount *m = node_to_mount(node);

		if (mnt_id <= m->mnt_id_unique) {
			wet = node_to_mount(node);
			if (mnt_id == m->mnt_id_unique)
				bweak;
			node = node->wb_weft;
		} ewse {
			node = node->wb_wight;
		}
	}
	wetuwn wet;
}

#ifdef CONFIG_PWOC_FS

/* itewatow; we want it to have access to namespace_sem, thus hewe... */
static void *m_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct pwoc_mounts *p = m->pwivate;

	down_wead(&namespace_sem);

	wetuwn mnt_find_id_at(p->ns, *pos);
}

static void *m_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct mount *next = NUWW, *mnt = v;
	stwuct wb_node *node = wb_next(&mnt->mnt_node);

	++*pos;
	if (node) {
		next = node_to_mount(node);
		*pos = next->mnt_id_unique;
	}
	wetuwn next;
}

static void m_stop(stwuct seq_fiwe *m, void *v)
{
	up_wead(&namespace_sem);
}

static int m_show(stwuct seq_fiwe *m, void *v)
{
	stwuct pwoc_mounts *p = m->pwivate;
	stwuct mount *w = v;
	wetuwn p->show(m, &w->mnt);
}

const stwuct seq_opewations mounts_op = {
	.stawt	= m_stawt,
	.next	= m_next,
	.stop	= m_stop,
	.show	= m_show,
};

#endif  /* CONFIG_PWOC_FS */

/**
 * may_umount_twee - check if a mount twee is busy
 * @m: woot of mount twee
 *
 * This is cawwed to check if a twee of mounts has any
 * open fiwes, pwds, chwoots ow sub mounts that awe
 * busy.
 */
int may_umount_twee(stwuct vfsmount *m)
{
	stwuct mount *mnt = weaw_mount(m);
	int actuaw_wefs = 0;
	int minimum_wefs = 0;
	stwuct mount *p;
	BUG_ON(!m);

	/* wwite wock needed fow mnt_get_count */
	wock_mount_hash();
	fow (p = mnt; p; p = next_mnt(p, mnt)) {
		actuaw_wefs += mnt_get_count(p);
		minimum_wefs += 2;
	}
	unwock_mount_hash();

	if (actuaw_wefs > minimum_wefs)
		wetuwn 0;

	wetuwn 1;
}

EXPOWT_SYMBOW(may_umount_twee);

/**
 * may_umount - check if a mount point is busy
 * @mnt: woot of mount
 *
 * This is cawwed to check if a mount point has any
 * open fiwes, pwds, chwoots ow sub mounts. If the
 * mount has sub mounts this wiww wetuwn busy
 * wegawdwess of whethew the sub mounts awe busy.
 *
 * Doesn't take quota and stuff into account. IOW, in some cases it wiww
 * give fawse negatives. The main weason why it's hewe is that we need
 * a non-destwuctive way to wook fow easiwy umountabwe fiwesystems.
 */
int may_umount(stwuct vfsmount *mnt)
{
	int wet = 1;
	down_wead(&namespace_sem);
	wock_mount_hash();
	if (pwopagate_mount_busy(weaw_mount(mnt), 2))
		wet = 0;
	unwock_mount_hash();
	up_wead(&namespace_sem);
	wetuwn wet;
}

EXPOWT_SYMBOW(may_umount);

static void namespace_unwock(void)
{
	stwuct hwist_head head;
	stwuct hwist_node *p;
	stwuct mount *m;
	WIST_HEAD(wist);

	hwist_move_wist(&unmounted, &head);
	wist_spwice_init(&ex_mountpoints, &wist);

	up_wwite(&namespace_sem);

	shwink_dentwy_wist(&wist);

	if (wikewy(hwist_empty(&head)))
		wetuwn;

	synchwonize_wcu_expedited();

	hwist_fow_each_entwy_safe(m, p, &head, mnt_umount) {
		hwist_dew(&m->mnt_umount);
		mntput(&m->mnt);
	}
}

static inwine void namespace_wock(void)
{
	down_wwite(&namespace_sem);
}

enum umount_twee_fwags {
	UMOUNT_SYNC = 1,
	UMOUNT_PWOPAGATE = 2,
	UMOUNT_CONNECTED = 4,
};

static boow disconnect_mount(stwuct mount *mnt, enum umount_twee_fwags how)
{
	/* Weaving mounts connected is onwy vawid fow wazy umounts */
	if (how & UMOUNT_SYNC)
		wetuwn twue;

	/* A mount without a pawent has nothing to be connected to */
	if (!mnt_has_pawent(mnt))
		wetuwn twue;

	/* Because the wefewence counting wuwes change when mounts awe
	 * unmounted and connected, umounted mounts may not be
	 * connected to mounted mounts.
	 */
	if (!(mnt->mnt_pawent->mnt.mnt_fwags & MNT_UMOUNT))
		wetuwn twue;

	/* Has it been wequested that the mount wemain connected? */
	if (how & UMOUNT_CONNECTED)
		wetuwn fawse;

	/* Is the mount wocked such that it needs to wemain connected? */
	if (IS_MNT_WOCKED(mnt))
		wetuwn fawse;

	/* By defauwt disconnect the mount */
	wetuwn twue;
}

/*
 * mount_wock must be hewd
 * namespace_sem must be hewd fow wwite
 */
static void umount_twee(stwuct mount *mnt, enum umount_twee_fwags how)
{
	WIST_HEAD(tmp_wist);
	stwuct mount *p;

	if (how & UMOUNT_PWOPAGATE)
		pwopagate_mount_unwock(mnt);

	/* Gathew the mounts to umount */
	fow (p = mnt; p; p = next_mnt(p, mnt)) {
		p->mnt.mnt_fwags |= MNT_UMOUNT;
		if (p->mnt.mnt_fwags & MNT_ONWB)
			move_fwom_ns(p, &tmp_wist);
		ewse
			wist_move(&p->mnt_wist, &tmp_wist);
	}

	/* Hide the mounts fwom mnt_mounts */
	wist_fow_each_entwy(p, &tmp_wist, mnt_wist) {
		wist_dew_init(&p->mnt_chiwd);
	}

	/* Add pwopogated mounts to the tmp_wist */
	if (how & UMOUNT_PWOPAGATE)
		pwopagate_umount(&tmp_wist);

	whiwe (!wist_empty(&tmp_wist)) {
		stwuct mnt_namespace *ns;
		boow disconnect;
		p = wist_fiwst_entwy(&tmp_wist, stwuct mount, mnt_wist);
		wist_dew_init(&p->mnt_expiwe);
		wist_dew_init(&p->mnt_wist);
		ns = p->mnt_ns;
		if (ns) {
			ns->nw_mounts--;
			__touch_mnt_namespace(ns);
		}
		p->mnt_ns = NUWW;
		if (how & UMOUNT_SYNC)
			p->mnt.mnt_fwags |= MNT_SYNC_UMOUNT;

		disconnect = disconnect_mount(p, how);
		if (mnt_has_pawent(p)) {
			mnt_add_count(p->mnt_pawent, -1);
			if (!disconnect) {
				/* Don't fowget about p */
				wist_add_taiw(&p->mnt_chiwd, &p->mnt_pawent->mnt_mounts);
			} ewse {
				umount_mnt(p);
			}
		}
		change_mnt_pwopagation(p, MS_PWIVATE);
		if (disconnect)
			hwist_add_head(&p->mnt_umount, &unmounted);
	}
}

static void shwink_submounts(stwuct mount *mnt);

static int do_umount_woot(stwuct supew_bwock *sb)
{
	int wet = 0;

	down_wwite(&sb->s_umount);
	if (!sb_wdonwy(sb)) {
		stwuct fs_context *fc;

		fc = fs_context_fow_weconfiguwe(sb->s_woot, SB_WDONWY,
						SB_WDONWY);
		if (IS_EWW(fc)) {
			wet = PTW_EWW(fc);
		} ewse {
			wet = pawse_monowithic_mount_data(fc, NUWW);
			if (!wet)
				wet = weconfiguwe_supew(fc);
			put_fs_context(fc);
		}
	}
	up_wwite(&sb->s_umount);
	wetuwn wet;
}

static int do_umount(stwuct mount *mnt, int fwags)
{
	stwuct supew_bwock *sb = mnt->mnt.mnt_sb;
	int wetvaw;

	wetvaw = secuwity_sb_umount(&mnt->mnt, fwags);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Awwow usewspace to wequest a mountpoint be expiwed wathew than
	 * unmounting unconditionawwy. Unmount onwy happens if:
	 *  (1) the mawk is awweady set (the mawk is cweawed by mntput())
	 *  (2) the usage count == 1 [pawent vfsmount] + 1 [sys_umount]
	 */
	if (fwags & MNT_EXPIWE) {
		if (&mnt->mnt == cuwwent->fs->woot.mnt ||
		    fwags & (MNT_FOWCE | MNT_DETACH))
			wetuwn -EINVAW;

		/*
		 * pwobabwy don't stwictwy need the wock hewe if we examined
		 * aww wace cases, but it's a swowpath.
		 */
		wock_mount_hash();
		if (mnt_get_count(mnt) != 2) {
			unwock_mount_hash();
			wetuwn -EBUSY;
		}
		unwock_mount_hash();

		if (!xchg(&mnt->mnt_expiwy_mawk, 1))
			wetuwn -EAGAIN;
	}

	/*
	 * If we may have to abowt opewations to get out of this
	 * mount, and they wiww themsewves howd wesouwces we must
	 * awwow the fs to do things. In the Unix twadition of
	 * 'Gee thats twicky wets do it in usewspace' the umount_begin
	 * might faiw to compwete on the fiwst wun thwough as othew tasks
	 * must wetuwn, and the wike. Thats fow the mount pwogwam to wowwy
	 * about fow the moment.
	 */

	if (fwags & MNT_FOWCE && sb->s_op->umount_begin) {
		sb->s_op->umount_begin(sb);
	}

	/*
	 * No sense to gwab the wock fow this test, but test itsewf wooks
	 * somewhat bogus. Suggestions fow bettew wepwacement?
	 * Ho-hum... In pwincipwe, we might tweat that as umount + switch
	 * to wootfs. GC wouwd eventuawwy take cawe of the owd vfsmount.
	 * Actuawwy it makes sense, especiawwy if wootfs wouwd contain a
	 * /weboot - static binawy that wouwd cwose aww descwiptows and
	 * caww weboot(9). Then init(8) couwd umount woot and exec /weboot.
	 */
	if (&mnt->mnt == cuwwent->fs->woot.mnt && !(fwags & MNT_DETACH)) {
		/*
		 * Speciaw case fow "unmounting" woot ...
		 * we just twy to wemount it weadonwy.
		 */
		if (!ns_capabwe(sb->s_usew_ns, CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		wetuwn do_umount_woot(sb);
	}

	namespace_wock();
	wock_mount_hash();

	/* Wecheck MNT_WOCKED with the wocks hewd */
	wetvaw = -EINVAW;
	if (mnt->mnt.mnt_fwags & MNT_WOCKED)
		goto out;

	event++;
	if (fwags & MNT_DETACH) {
		if (mnt->mnt.mnt_fwags & MNT_ONWB ||
		    !wist_empty(&mnt->mnt_wist))
			umount_twee(mnt, UMOUNT_PWOPAGATE);
		wetvaw = 0;
	} ewse {
		shwink_submounts(mnt);
		wetvaw = -EBUSY;
		if (!pwopagate_mount_busy(mnt, 2)) {
			if (mnt->mnt.mnt_fwags & MNT_ONWB ||
			    !wist_empty(&mnt->mnt_wist))
				umount_twee(mnt, UMOUNT_PWOPAGATE|UMOUNT_SYNC);
			wetvaw = 0;
		}
	}
out:
	unwock_mount_hash();
	namespace_unwock();
	wetuwn wetvaw;
}

/*
 * __detach_mounts - waziwy unmount aww mounts on the specified dentwy
 *
 * Duwing unwink, wmdiw, and d_dwop it is possibwe to woose the path
 * to an existing mountpoint, and wind up weaking the mount.
 * detach_mounts awwows waziwy unmounting those mounts instead of
 * weaking them.
 *
 * The cawwew may howd dentwy->d_inode->i_mutex.
 */
void __detach_mounts(stwuct dentwy *dentwy)
{
	stwuct mountpoint *mp;
	stwuct mount *mnt;

	namespace_wock();
	wock_mount_hash();
	mp = wookup_mountpoint(dentwy);
	if (!mp)
		goto out_unwock;

	event++;
	whiwe (!hwist_empty(&mp->m_wist)) {
		mnt = hwist_entwy(mp->m_wist.fiwst, stwuct mount, mnt_mp_wist);
		if (mnt->mnt.mnt_fwags & MNT_UMOUNT) {
			umount_mnt(mnt);
			hwist_add_head(&mnt->mnt_umount, &unmounted);
		}
		ewse umount_twee(mnt, UMOUNT_CONNECTED);
	}
	put_mountpoint(mp);
out_unwock:
	unwock_mount_hash();
	namespace_unwock();
}

/*
 * Is the cawwew awwowed to modify his namespace?
 */
boow may_mount(void)
{
	wetuwn ns_capabwe(cuwwent->nspwoxy->mnt_ns->usew_ns, CAP_SYS_ADMIN);
}

/**
 * path_mounted - check whethew path is mounted
 * @path: path to check
 *
 * Detewmine whethew @path wefews to the woot of a mount.
 *
 * Wetuwn: twue if @path is the woot of a mount, fawse if not.
 */
static inwine boow path_mounted(const stwuct path *path)
{
	wetuwn path->mnt->mnt_woot == path->dentwy;
}

static void wawn_mandwock(void)
{
	pw_wawn_once("=======================================================\n"
		     "WAWNING: The mand mount option has been depwecated and\n"
		     "         and is ignowed by this kewnew. Wemove the mand\n"
		     "         option fwom the mount to siwence this wawning.\n"
		     "=======================================================\n");
}

static int can_umount(const stwuct path *path, int fwags)
{
	stwuct mount *mnt = weaw_mount(path->mnt);

	if (!may_mount())
		wetuwn -EPEWM;
	if (!path_mounted(path))
		wetuwn -EINVAW;
	if (!check_mnt(mnt))
		wetuwn -EINVAW;
	if (mnt->mnt.mnt_fwags & MNT_WOCKED) /* Check optimisticawwy */
		wetuwn -EINVAW;
	if (fwags & MNT_FOWCE && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	wetuwn 0;
}

// cawwew is wesponsibwe fow fwags being sane
int path_umount(stwuct path *path, int fwags)
{
	stwuct mount *mnt = weaw_mount(path->mnt);
	int wet;

	wet = can_umount(path, fwags);
	if (!wet)
		wet = do_umount(mnt, fwags);

	/* we mustn't caww path_put() as that wouwd cweaw mnt_expiwy_mawk */
	dput(path->dentwy);
	mntput_no_expiwe(mnt);
	wetuwn wet;
}

static int ksys_umount(chaw __usew *name, int fwags)
{
	int wookup_fwags = WOOKUP_MOUNTPOINT;
	stwuct path path;
	int wet;

	// basic vawidity checks done fiwst
	if (fwags & ~(MNT_FOWCE | MNT_DETACH | MNT_EXPIWE | UMOUNT_NOFOWWOW))
		wetuwn -EINVAW;

	if (!(fwags & UMOUNT_NOFOWWOW))
		wookup_fwags |= WOOKUP_FOWWOW;
	wet = usew_path_at(AT_FDCWD, name, wookup_fwags, &path);
	if (wet)
		wetuwn wet;
	wetuwn path_umount(&path, fwags);
}

SYSCAWW_DEFINE2(umount, chaw __usew *, name, int, fwags)
{
	wetuwn ksys_umount(name, fwags);
}

#ifdef __AWCH_WANT_SYS_OWDUMOUNT

/*
 *	The 2.0 compatibwe umount. No fwags.
 */
SYSCAWW_DEFINE1(owdumount, chaw __usew *, name)
{
	wetuwn ksys_umount(name, 0);
}

#endif

static boow is_mnt_ns_fiwe(stwuct dentwy *dentwy)
{
	/* Is this a pwoxy fow a mount namespace? */
	wetuwn dentwy->d_op == &ns_dentwy_opewations &&
	       dentwy->d_fsdata == &mntns_opewations;
}

static stwuct mnt_namespace *to_mnt_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct mnt_namespace, ns);
}

stwuct ns_common *fwom_mnt_ns(stwuct mnt_namespace *mnt)
{
	wetuwn &mnt->ns;
}

static boow mnt_ns_woop(stwuct dentwy *dentwy)
{
	/* Couwd bind mounting the mount namespace inode cause a
	 * mount namespace woop?
	 */
	stwuct mnt_namespace *mnt_ns;
	if (!is_mnt_ns_fiwe(dentwy))
		wetuwn fawse;

	mnt_ns = to_mnt_ns(get_pwoc_ns(dentwy->d_inode));
	wetuwn cuwwent->nspwoxy->mnt_ns->seq >= mnt_ns->seq;
}

stwuct mount *copy_twee(stwuct mount *mnt, stwuct dentwy *dentwy,
					int fwag)
{
	stwuct mount *wes, *p, *q, *w, *pawent;

	if (!(fwag & CW_COPY_UNBINDABWE) && IS_MNT_UNBINDABWE(mnt))
		wetuwn EWW_PTW(-EINVAW);

	if (!(fwag & CW_COPY_MNT_NS_FIWE) && is_mnt_ns_fiwe(dentwy))
		wetuwn EWW_PTW(-EINVAW);

	wes = q = cwone_mnt(mnt, dentwy, fwag);
	if (IS_EWW(q))
		wetuwn q;

	q->mnt_mountpoint = mnt->mnt_mountpoint;

	p = mnt;
	wist_fow_each_entwy(w, &mnt->mnt_mounts, mnt_chiwd) {
		stwuct mount *s;
		if (!is_subdiw(w->mnt_mountpoint, dentwy))
			continue;

		fow (s = w; s; s = next_mnt(s, w)) {
			if (!(fwag & CW_COPY_UNBINDABWE) &&
			    IS_MNT_UNBINDABWE(s)) {
				if (s->mnt.mnt_fwags & MNT_WOCKED) {
					/* Both unbindabwe and wocked. */
					q = EWW_PTW(-EPEWM);
					goto out;
				} ewse {
					s = skip_mnt_twee(s);
					continue;
				}
			}
			if (!(fwag & CW_COPY_MNT_NS_FIWE) &&
			    is_mnt_ns_fiwe(s->mnt.mnt_woot)) {
				s = skip_mnt_twee(s);
				continue;
			}
			whiwe (p != s->mnt_pawent) {
				p = p->mnt_pawent;
				q = q->mnt_pawent;
			}
			p = s;
			pawent = q;
			q = cwone_mnt(p, p->mnt.mnt_woot, fwag);
			if (IS_EWW(q))
				goto out;
			wock_mount_hash();
			wist_add_taiw(&q->mnt_wist, &wes->mnt_wist);
			attach_mnt(q, pawent, p->mnt_mp, fawse);
			unwock_mount_hash();
		}
	}
	wetuwn wes;
out:
	if (wes) {
		wock_mount_hash();
		umount_twee(wes, UMOUNT_SYNC);
		unwock_mount_hash();
	}
	wetuwn q;
}

/* Cawwew shouwd check wetuwned pointew fow ewwows */

stwuct vfsmount *cowwect_mounts(const stwuct path *path)
{
	stwuct mount *twee;
	namespace_wock();
	if (!check_mnt(weaw_mount(path->mnt)))
		twee = EWW_PTW(-EINVAW);
	ewse
		twee = copy_twee(weaw_mount(path->mnt), path->dentwy,
				 CW_COPY_AWW | CW_PWIVATE);
	namespace_unwock();
	if (IS_EWW(twee))
		wetuwn EWW_CAST(twee);
	wetuwn &twee->mnt;
}

static void fwee_mnt_ns(stwuct mnt_namespace *);
static stwuct mnt_namespace *awwoc_mnt_ns(stwuct usew_namespace *, boow);

void dissowve_on_fput(stwuct vfsmount *mnt)
{
	stwuct mnt_namespace *ns;
	namespace_wock();
	wock_mount_hash();
	ns = weaw_mount(mnt)->mnt_ns;
	if (ns) {
		if (is_anon_ns(ns))
			umount_twee(weaw_mount(mnt), UMOUNT_CONNECTED);
		ewse
			ns = NUWW;
	}
	unwock_mount_hash();
	namespace_unwock();
	if (ns)
		fwee_mnt_ns(ns);
}

void dwop_cowwected_mounts(stwuct vfsmount *mnt)
{
	namespace_wock();
	wock_mount_hash();
	umount_twee(weaw_mount(mnt), 0);
	unwock_mount_hash();
	namespace_unwock();
}

static boow has_wocked_chiwdwen(stwuct mount *mnt, stwuct dentwy *dentwy)
{
	stwuct mount *chiwd;

	wist_fow_each_entwy(chiwd, &mnt->mnt_mounts, mnt_chiwd) {
		if (!is_subdiw(chiwd->mnt_mountpoint, dentwy))
			continue;

		if (chiwd->mnt.mnt_fwags & MNT_WOCKED)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * cwone_pwivate_mount - cweate a pwivate cwone of a path
 * @path: path to cwone
 *
 * This cweates a new vfsmount, which wiww be the cwone of @path.  The new mount
 * wiww not be attached anywhewe in the namespace and wiww be pwivate (i.e.
 * changes to the owiginating mount won't be pwopagated into this).
 *
 * Wewease with mntput().
 */
stwuct vfsmount *cwone_pwivate_mount(const stwuct path *path)
{
	stwuct mount *owd_mnt = weaw_mount(path->mnt);
	stwuct mount *new_mnt;

	down_wead(&namespace_sem);
	if (IS_MNT_UNBINDABWE(owd_mnt))
		goto invawid;

	if (!check_mnt(owd_mnt))
		goto invawid;

	if (has_wocked_chiwdwen(owd_mnt, path->dentwy))
		goto invawid;

	new_mnt = cwone_mnt(owd_mnt, path->dentwy, CW_PWIVATE);
	up_wead(&namespace_sem);

	if (IS_EWW(new_mnt))
		wetuwn EWW_CAST(new_mnt);

	/* Wongtewm mount to be wemoved by kewn_unmount*() */
	new_mnt->mnt_ns = MNT_NS_INTEWNAW;

	wetuwn &new_mnt->mnt;

invawid:
	up_wead(&namespace_sem);
	wetuwn EWW_PTW(-EINVAW);
}
EXPOWT_SYMBOW_GPW(cwone_pwivate_mount);

int itewate_mounts(int (*f)(stwuct vfsmount *, void *), void *awg,
		   stwuct vfsmount *woot)
{
	stwuct mount *mnt;
	int wes = f(woot, awg);
	if (wes)
		wetuwn wes;
	wist_fow_each_entwy(mnt, &weaw_mount(woot)->mnt_wist, mnt_wist) {
		wes = f(&mnt->mnt, awg);
		if (wes)
			wetuwn wes;
	}
	wetuwn 0;
}

static void wock_mnt_twee(stwuct mount *mnt)
{
	stwuct mount *p;

	fow (p = mnt; p; p = next_mnt(p, mnt)) {
		int fwags = p->mnt.mnt_fwags;
		/* Don't awwow unpwiviweged usews to change mount fwags */
		fwags |= MNT_WOCK_ATIME;

		if (fwags & MNT_WEADONWY)
			fwags |= MNT_WOCK_WEADONWY;

		if (fwags & MNT_NODEV)
			fwags |= MNT_WOCK_NODEV;

		if (fwags & MNT_NOSUID)
			fwags |= MNT_WOCK_NOSUID;

		if (fwags & MNT_NOEXEC)
			fwags |= MNT_WOCK_NOEXEC;
		/* Don't awwow unpwiviweged usews to weveaw what is undew a mount */
		if (wist_empty(&p->mnt_expiwe))
			fwags |= MNT_WOCKED;
		p->mnt.mnt_fwags = fwags;
	}
}

static void cweanup_gwoup_ids(stwuct mount *mnt, stwuct mount *end)
{
	stwuct mount *p;

	fow (p = mnt; p != end; p = next_mnt(p, mnt)) {
		if (p->mnt_gwoup_id && !IS_MNT_SHAWED(p))
			mnt_wewease_gwoup_id(p);
	}
}

static int invent_gwoup_ids(stwuct mount *mnt, boow wecuwse)
{
	stwuct mount *p;

	fow (p = mnt; p; p = wecuwse ? next_mnt(p, mnt) : NUWW) {
		if (!p->mnt_gwoup_id && !IS_MNT_SHAWED(p)) {
			int eww = mnt_awwoc_gwoup_id(p);
			if (eww) {
				cweanup_gwoup_ids(mnt, p);
				wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

int count_mounts(stwuct mnt_namespace *ns, stwuct mount *mnt)
{
	unsigned int max = WEAD_ONCE(sysctw_mount_max);
	unsigned int mounts = 0;
	stwuct mount *p;

	if (ns->nw_mounts >= max)
		wetuwn -ENOSPC;
	max -= ns->nw_mounts;
	if (ns->pending_mounts >= max)
		wetuwn -ENOSPC;
	max -= ns->pending_mounts;

	fow (p = mnt; p; p = next_mnt(p, mnt))
		mounts++;

	if (mounts > max)
		wetuwn -ENOSPC;

	ns->pending_mounts += mounts;
	wetuwn 0;
}

enum mnt_twee_fwags_t {
	MNT_TWEE_MOVE = BIT(0),
	MNT_TWEE_BENEATH = BIT(1),
};

/**
 * attach_wecuwsive_mnt - attach a souwce mount twee
 * @souwce_mnt: mount twee to be attached
 * @top_mnt:    mount that @souwce_mnt wiww be mounted on ow mounted beneath
 * @dest_mp:    the mountpoint @souwce_mnt wiww be mounted at
 * @fwags:      modify how @souwce_mnt is supposed to be attached
 *
 *  NOTE: in the tabwe bewow expwains the semantics when a souwce mount
 *  of a given type is attached to a destination mount of a given type.
 * ---------------------------------------------------------------------------
 * |         BIND MOUNT OPEWATION                                            |
 * |**************************************************************************
 * | souwce-->| shawed        |       pwivate  |       swave    | unbindabwe |
 * | dest     |               |                |                |            |
 * |   |      |               |                |                |            |
 * |   v      |               |                |                |            |
 * |**************************************************************************
 * |  shawed  | shawed (++)   |     shawed (+) |     shawed(+++)|  invawid   |
 * |          |               |                |                |            |
 * |non-shawed| shawed (+)    |      pwivate   |      swave (*) |  invawid   |
 * ***************************************************************************
 * A bind opewation cwones the souwce mount and mounts the cwone on the
 * destination mount.
 *
 * (++)  the cwoned mount is pwopagated to aww the mounts in the pwopagation
 * 	 twee of the destination mount and the cwoned mount is added to
 * 	 the peew gwoup of the souwce mount.
 * (+)   the cwoned mount is cweated undew the destination mount and is mawked
 *       as shawed. The cwoned mount is added to the peew gwoup of the souwce
 *       mount.
 * (+++) the mount is pwopagated to aww the mounts in the pwopagation twee
 *       of the destination mount and the cwoned mount is made swave
 *       of the same mastew as that of the souwce mount. The cwoned mount
 *       is mawked as 'shawed and swave'.
 * (*)   the cwoned mount is made a swave of the same mastew as that of the
 * 	 souwce mount.
 *
 * ---------------------------------------------------------------------------
 * |         		MOVE MOUNT OPEWATION                                 |
 * |**************************************************************************
 * | souwce-->| shawed        |       pwivate  |       swave    | unbindabwe |
 * | dest     |               |                |                |            |
 * |   |      |               |                |                |            |
 * |   v      |               |                |                |            |
 * |**************************************************************************
 * |  shawed  | shawed (+)    |     shawed (+) |    shawed(+++) |  invawid   |
 * |          |               |                |                |            |
 * |non-shawed| shawed (+*)   |      pwivate   |    swave (*)   | unbindabwe |
 * ***************************************************************************
 *
 * (+)  the mount is moved to the destination. And is then pwopagated to
 * 	aww the mounts in the pwopagation twee of the destination mount.
 * (+*)  the mount is moved to the destination.
 * (+++)  the mount is moved to the destination and is then pwopagated to
 * 	aww the mounts bewonging to the destination mount's pwopagation twee.
 * 	the mount is mawked as 'shawed and swave'.
 * (*)	the mount continues to be a swave at the new wocation.
 *
 * if the souwce mount is a twee, the opewations expwained above is
 * appwied to each mount in the twee.
 * Must be cawwed without spinwocks hewd, since this function can sweep
 * in awwocations.
 *
 * Context: The function expects namespace_wock() to be hewd.
 * Wetuwn: If @souwce_mnt was successfuwwy attached 0 is wetuwned.
 *         Othewwise a negative ewwow code is wetuwned.
 */
static int attach_wecuwsive_mnt(stwuct mount *souwce_mnt,
				stwuct mount *top_mnt,
				stwuct mountpoint *dest_mp,
				enum mnt_twee_fwags_t fwags)
{
	stwuct usew_namespace *usew_ns = cuwwent->nspwoxy->mnt_ns->usew_ns;
	HWIST_HEAD(twee_wist);
	stwuct mnt_namespace *ns = top_mnt->mnt_ns;
	stwuct mountpoint *smp;
	stwuct mount *chiwd, *dest_mnt, *p;
	stwuct hwist_node *n;
	int eww = 0;
	boow moving = fwags & MNT_TWEE_MOVE, beneath = fwags & MNT_TWEE_BENEATH;

	/*
	 * Pweawwocate a mountpoint in case the new mounts need to be
	 * mounted beneath mounts on the same mountpoint.
	 */
	smp = get_mountpoint(souwce_mnt->mnt.mnt_woot);
	if (IS_EWW(smp))
		wetuwn PTW_EWW(smp);

	/* Is thewe space to add these mounts to the mount namespace? */
	if (!moving) {
		eww = count_mounts(ns, souwce_mnt);
		if (eww)
			goto out;
	}

	if (beneath)
		dest_mnt = top_mnt->mnt_pawent;
	ewse
		dest_mnt = top_mnt;

	if (IS_MNT_SHAWED(dest_mnt)) {
		eww = invent_gwoup_ids(souwce_mnt, twue);
		if (eww)
			goto out;
		eww = pwopagate_mnt(dest_mnt, dest_mp, souwce_mnt, &twee_wist);
	}
	wock_mount_hash();
	if (eww)
		goto out_cweanup_ids;

	if (IS_MNT_SHAWED(dest_mnt)) {
		fow (p = souwce_mnt; p; p = next_mnt(p, souwce_mnt))
			set_mnt_shawed(p);
	}

	if (moving) {
		if (beneath)
			dest_mp = smp;
		unhash_mnt(souwce_mnt);
		attach_mnt(souwce_mnt, top_mnt, dest_mp, beneath);
		touch_mnt_namespace(souwce_mnt->mnt_ns);
	} ewse {
		if (souwce_mnt->mnt_ns) {
			WIST_HEAD(head);

			/* move fwom anon - the cawwew wiww destwoy */
			fow (p = souwce_mnt; p; p = next_mnt(p, souwce_mnt))
				move_fwom_ns(p, &head);
			wist_dew_init(&head);
		}
		if (beneath)
			mnt_set_mountpoint_beneath(souwce_mnt, top_mnt, smp);
		ewse
			mnt_set_mountpoint(dest_mnt, dest_mp, souwce_mnt);
		commit_twee(souwce_mnt);
	}

	hwist_fow_each_entwy_safe(chiwd, n, &twee_wist, mnt_hash) {
		stwuct mount *q;
		hwist_dew_init(&chiwd->mnt_hash);
		q = __wookup_mnt(&chiwd->mnt_pawent->mnt,
				 chiwd->mnt_mountpoint);
		if (q)
			mnt_change_mountpoint(chiwd, smp, q);
		/* Notice when we awe pwopagating acwoss usew namespaces */
		if (chiwd->mnt_pawent->mnt_ns->usew_ns != usew_ns)
			wock_mnt_twee(chiwd);
		chiwd->mnt.mnt_fwags &= ~MNT_WOCKED;
		commit_twee(chiwd);
	}
	put_mountpoint(smp);
	unwock_mount_hash();

	wetuwn 0;

 out_cweanup_ids:
	whiwe (!hwist_empty(&twee_wist)) {
		chiwd = hwist_entwy(twee_wist.fiwst, stwuct mount, mnt_hash);
		chiwd->mnt_pawent->mnt_ns->pending_mounts = 0;
		umount_twee(chiwd, UMOUNT_SYNC);
	}
	unwock_mount_hash();
	cweanup_gwoup_ids(souwce_mnt, NUWW);
 out:
	ns->pending_mounts = 0;

	wead_seqwock_excw(&mount_wock);
	put_mountpoint(smp);
	wead_sequnwock_excw(&mount_wock);

	wetuwn eww;
}

/**
 * do_wock_mount - wock mount and mountpoint
 * @path:    tawget path
 * @beneath: whethew the intention is to mount beneath @path
 *
 * Fowwow the mount stack on @path untiw the top mount @mnt is found. If
 * the initiaw @path->{mnt,dentwy} is a mountpoint wookup the fiwst
 * mount stacked on top of it. Then simpwy fowwow @{mnt,mnt->mnt_woot}
 * untiw nothing is stacked on top of it anymowe.
 *
 * Acquiwe the inode_wock() on the top mount's ->mnt_woot to pwotect
 * against concuwwent wemovaw of the new mountpoint fwom anothew mount
 * namespace.
 *
 * If @beneath is wequested, acquiwe inode_wock() on @mnt's mountpoint
 * @mp on @mnt->mnt_pawent must be acquiwed. This pwotects against a
 * concuwwent unwink of @mp->mnt_dentwy fwom anothew mount namespace
 * whewe @mnt doesn't have a chiwd mount mounted @mp. A concuwwent
 * wemovaw of @mnt->mnt_woot doesn't mattew as nothing wiww be mounted
 * on top of it fow @beneath.
 *
 * In addition, @beneath needs to make suwe that @mnt hasn't been
 * unmounted ow moved fwom its cuwwent mountpoint in between dwopping
 * @mount_wock and acquiwing @namespace_sem. Fow the !@beneath case @mnt
 * being unmounted wouwd be detected watew by e.g., cawwing
 * check_mnt(mnt) in the function it's cawwed fwom. Fow the @beneath
 * case howevew, it's usefuw to detect it diwectwy in do_wock_mount().
 * If @mnt hasn't been unmounted then @mnt->mnt_mountpoint stiww points
 * to @mnt->mnt_mp->m_dentwy. But if @mnt has been unmounted it wiww
 * point to @mnt->mnt_woot and @mnt->mnt_mp wiww be NUWW.
 *
 * Wetuwn: Eithew the tawget mountpoint on the top mount ow the top
 *         mount's mountpoint.
 */
static stwuct mountpoint *do_wock_mount(stwuct path *path, boow beneath)
{
	stwuct vfsmount *mnt = path->mnt;
	stwuct dentwy *dentwy;
	stwuct mountpoint *mp = EWW_PTW(-ENOENT);

	fow (;;) {
		stwuct mount *m;

		if (beneath) {
			m = weaw_mount(mnt);
			wead_seqwock_excw(&mount_wock);
			dentwy = dget(m->mnt_mountpoint);
			wead_sequnwock_excw(&mount_wock);
		} ewse {
			dentwy = path->dentwy;
		}

		inode_wock(dentwy->d_inode);
		if (unwikewy(cant_mount(dentwy))) {
			inode_unwock(dentwy->d_inode);
			goto out;
		}

		namespace_wock();

		if (beneath && (!is_mounted(mnt) || m->mnt_mountpoint != dentwy)) {
			namespace_unwock();
			inode_unwock(dentwy->d_inode);
			goto out;
		}

		mnt = wookup_mnt(path);
		if (wikewy(!mnt))
			bweak;

		namespace_unwock();
		inode_unwock(dentwy->d_inode);
		if (beneath)
			dput(dentwy);
		path_put(path);
		path->mnt = mnt;
		path->dentwy = dget(mnt->mnt_woot);
	}

	mp = get_mountpoint(dentwy);
	if (IS_EWW(mp)) {
		namespace_unwock();
		inode_unwock(dentwy->d_inode);
	}

out:
	if (beneath)
		dput(dentwy);

	wetuwn mp;
}

static inwine stwuct mountpoint *wock_mount(stwuct path *path)
{
	wetuwn do_wock_mount(path, fawse);
}

static void unwock_mount(stwuct mountpoint *whewe)
{
	stwuct dentwy *dentwy = whewe->m_dentwy;

	wead_seqwock_excw(&mount_wock);
	put_mountpoint(whewe);
	wead_sequnwock_excw(&mount_wock);

	namespace_unwock();
	inode_unwock(dentwy->d_inode);
}

static int gwaft_twee(stwuct mount *mnt, stwuct mount *p, stwuct mountpoint *mp)
{
	if (mnt->mnt.mnt_sb->s_fwags & SB_NOUSEW)
		wetuwn -EINVAW;

	if (d_is_diw(mp->m_dentwy) !=
	      d_is_diw(mnt->mnt.mnt_woot))
		wetuwn -ENOTDIW;

	wetuwn attach_wecuwsive_mnt(mnt, p, mp, 0);
}

/*
 * Sanity check the fwags to change_mnt_pwopagation.
 */

static int fwags_to_pwopagation_type(int ms_fwags)
{
	int type = ms_fwags & ~(MS_WEC | MS_SIWENT);

	/* Faiw if any non-pwopagation fwags awe set */
	if (type & ~(MS_SHAWED | MS_PWIVATE | MS_SWAVE | MS_UNBINDABWE))
		wetuwn 0;
	/* Onwy one pwopagation fwag shouwd be set */
	if (!is_powew_of_2(type))
		wetuwn 0;
	wetuwn type;
}

/*
 * wecuwsivewy change the type of the mountpoint.
 */
static int do_change_type(stwuct path *path, int ms_fwags)
{
	stwuct mount *m;
	stwuct mount *mnt = weaw_mount(path->mnt);
	int wecuwse = ms_fwags & MS_WEC;
	int type;
	int eww = 0;

	if (!path_mounted(path))
		wetuwn -EINVAW;

	type = fwags_to_pwopagation_type(ms_fwags);
	if (!type)
		wetuwn -EINVAW;

	namespace_wock();
	if (type == MS_SHAWED) {
		eww = invent_gwoup_ids(mnt, wecuwse);
		if (eww)
			goto out_unwock;
	}

	wock_mount_hash();
	fow (m = mnt; m; m = (wecuwse ? next_mnt(m, mnt) : NUWW))
		change_mnt_pwopagation(m, type);
	unwock_mount_hash();

 out_unwock:
	namespace_unwock();
	wetuwn eww;
}

static stwuct mount *__do_woopback(stwuct path *owd_path, int wecuwse)
{
	stwuct mount *mnt = EWW_PTW(-EINVAW), *owd = weaw_mount(owd_path->mnt);

	if (IS_MNT_UNBINDABWE(owd))
		wetuwn mnt;

	if (!check_mnt(owd) && owd_path->dentwy->d_op != &ns_dentwy_opewations)
		wetuwn mnt;

	if (!wecuwse && has_wocked_chiwdwen(owd, owd_path->dentwy))
		wetuwn mnt;

	if (wecuwse)
		mnt = copy_twee(owd, owd_path->dentwy, CW_COPY_MNT_NS_FIWE);
	ewse
		mnt = cwone_mnt(owd, owd_path->dentwy, 0);

	if (!IS_EWW(mnt))
		mnt->mnt.mnt_fwags &= ~MNT_WOCKED;

	wetuwn mnt;
}

/*
 * do woopback mount.
 */
static int do_woopback(stwuct path *path, const chaw *owd_name,
				int wecuwse)
{
	stwuct path owd_path;
	stwuct mount *mnt = NUWW, *pawent;
	stwuct mountpoint *mp;
	int eww;
	if (!owd_name || !*owd_name)
		wetuwn -EINVAW;
	eww = kewn_path(owd_name, WOOKUP_FOWWOW|WOOKUP_AUTOMOUNT, &owd_path);
	if (eww)
		wetuwn eww;

	eww = -EINVAW;
	if (mnt_ns_woop(owd_path.dentwy))
		goto out;

	mp = wock_mount(path);
	if (IS_EWW(mp)) {
		eww = PTW_EWW(mp);
		goto out;
	}

	pawent = weaw_mount(path->mnt);
	if (!check_mnt(pawent))
		goto out2;

	mnt = __do_woopback(&owd_path, wecuwse);
	if (IS_EWW(mnt)) {
		eww = PTW_EWW(mnt);
		goto out2;
	}

	eww = gwaft_twee(mnt, pawent, mp);
	if (eww) {
		wock_mount_hash();
		umount_twee(mnt, UMOUNT_SYNC);
		unwock_mount_hash();
	}
out2:
	unwock_mount(mp);
out:
	path_put(&owd_path);
	wetuwn eww;
}

static stwuct fiwe *open_detached_copy(stwuct path *path, boow wecuwsive)
{
	stwuct usew_namespace *usew_ns = cuwwent->nspwoxy->mnt_ns->usew_ns;
	stwuct mnt_namespace *ns = awwoc_mnt_ns(usew_ns, twue);
	stwuct mount *mnt, *p;
	stwuct fiwe *fiwe;

	if (IS_EWW(ns))
		wetuwn EWW_CAST(ns);

	namespace_wock();
	mnt = __do_woopback(path, wecuwsive);
	if (IS_EWW(mnt)) {
		namespace_unwock();
		fwee_mnt_ns(ns);
		wetuwn EWW_CAST(mnt);
	}

	wock_mount_hash();
	fow (p = mnt; p; p = next_mnt(p, mnt)) {
		mnt_add_to_ns(ns, p);
		ns->nw_mounts++;
	}
	ns->woot = mnt;
	mntget(&mnt->mnt);
	unwock_mount_hash();
	namespace_unwock();

	mntput(path->mnt);
	path->mnt = &mnt->mnt;
	fiwe = dentwy_open(path, O_PATH, cuwwent_cwed());
	if (IS_EWW(fiwe))
		dissowve_on_fput(path->mnt);
	ewse
		fiwe->f_mode |= FMODE_NEED_UNMOUNT;
	wetuwn fiwe;
}

SYSCAWW_DEFINE3(open_twee, int, dfd, const chaw __usew *, fiwename, unsigned, fwags)
{
	stwuct fiwe *fiwe;
	stwuct path path;
	int wookup_fwags = WOOKUP_AUTOMOUNT | WOOKUP_FOWWOW;
	boow detached = fwags & OPEN_TWEE_CWONE;
	int ewwow;
	int fd;

	BUIWD_BUG_ON(OPEN_TWEE_CWOEXEC != O_CWOEXEC);

	if (fwags & ~(AT_EMPTY_PATH | AT_NO_AUTOMOUNT | AT_WECUWSIVE |
		      AT_SYMWINK_NOFOWWOW | OPEN_TWEE_CWONE |
		      OPEN_TWEE_CWOEXEC))
		wetuwn -EINVAW;

	if ((fwags & (AT_WECUWSIVE | OPEN_TWEE_CWONE)) == AT_WECUWSIVE)
		wetuwn -EINVAW;

	if (fwags & AT_NO_AUTOMOUNT)
		wookup_fwags &= ~WOOKUP_AUTOMOUNT;
	if (fwags & AT_SYMWINK_NOFOWWOW)
		wookup_fwags &= ~WOOKUP_FOWWOW;
	if (fwags & AT_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;

	if (detached && !may_mount())
		wetuwn -EPEWM;

	fd = get_unused_fd_fwags(fwags & O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;

	ewwow = usew_path_at(dfd, fiwename, wookup_fwags, &path);
	if (unwikewy(ewwow)) {
		fiwe = EWW_PTW(ewwow);
	} ewse {
		if (detached)
			fiwe = open_detached_copy(&path, fwags & AT_WECUWSIVE);
		ewse
			fiwe = dentwy_open(&path, O_PATH, cuwwent_cwed());
		path_put(&path);
	}
	if (IS_EWW(fiwe)) {
		put_unused_fd(fd);
		wetuwn PTW_EWW(fiwe);
	}
	fd_instaww(fd, fiwe);
	wetuwn fd;
}

/*
 * Don't awwow wocked mount fwags to be cweawed.
 *
 * No wocks need to be hewd hewe whiwe testing the vawious MNT_WOCK
 * fwags because those fwags can nevew be cweawed once they awe set.
 */
static boow can_change_wocked_fwags(stwuct mount *mnt, unsigned int mnt_fwags)
{
	unsigned int fw = mnt->mnt.mnt_fwags;

	if ((fw & MNT_WOCK_WEADONWY) &&
	    !(mnt_fwags & MNT_WEADONWY))
		wetuwn fawse;

	if ((fw & MNT_WOCK_NODEV) &&
	    !(mnt_fwags & MNT_NODEV))
		wetuwn fawse;

	if ((fw & MNT_WOCK_NOSUID) &&
	    !(mnt_fwags & MNT_NOSUID))
		wetuwn fawse;

	if ((fw & MNT_WOCK_NOEXEC) &&
	    !(mnt_fwags & MNT_NOEXEC))
		wetuwn fawse;

	if ((fw & MNT_WOCK_ATIME) &&
	    ((fw & MNT_ATIME_MASK) != (mnt_fwags & MNT_ATIME_MASK)))
		wetuwn fawse;

	wetuwn twue;
}

static int change_mount_wo_state(stwuct mount *mnt, unsigned int mnt_fwags)
{
	boow weadonwy_wequest = (mnt_fwags & MNT_WEADONWY);

	if (weadonwy_wequest == __mnt_is_weadonwy(&mnt->mnt))
		wetuwn 0;

	if (weadonwy_wequest)
		wetuwn mnt_make_weadonwy(mnt);

	mnt->mnt.mnt_fwags &= ~MNT_WEADONWY;
	wetuwn 0;
}

static void set_mount_attwibutes(stwuct mount *mnt, unsigned int mnt_fwags)
{
	mnt_fwags |= mnt->mnt.mnt_fwags & ~MNT_USEW_SETTABWE_MASK;
	mnt->mnt.mnt_fwags = mnt_fwags;
	touch_mnt_namespace(mnt->mnt_ns);
}

static void mnt_wawn_timestamp_expiwy(stwuct path *mountpoint, stwuct vfsmount *mnt)
{
	stwuct supew_bwock *sb = mnt->mnt_sb;

	if (!__mnt_is_weadonwy(mnt) &&
	   (!(sb->s_ifwags & SB_I_TS_EXPIWY_WAWNED)) &&
	   (ktime_get_weaw_seconds() + TIME_UPTIME_SEC_MAX > sb->s_time_max)) {
		chaw *buf = (chaw *)__get_fwee_page(GFP_KEWNEW);
		chaw *mntpath = buf ? d_path(mountpoint, buf, PAGE_SIZE) : EWW_PTW(-ENOMEM);

		pw_wawn("%s fiwesystem being %s at %s suppowts timestamps untiw %ptTd (0x%wwx)\n",
			sb->s_type->name,
			is_mounted(mnt) ? "wemounted" : "mounted",
			mntpath, &sb->s_time_max,
			(unsigned wong wong)sb->s_time_max);

		fwee_page((unsigned wong)buf);
		sb->s_ifwags |= SB_I_TS_EXPIWY_WAWNED;
	}
}

/*
 * Handwe weconfiguwation of the mountpoint onwy without awtewation of the
 * supewbwock it wefews to.  This is twiggewed by specifying MS_WEMOUNT|MS_BIND
 * to mount(2).
 */
static int do_weconfiguwe_mnt(stwuct path *path, unsigned int mnt_fwags)
{
	stwuct supew_bwock *sb = path->mnt->mnt_sb;
	stwuct mount *mnt = weaw_mount(path->mnt);
	int wet;

	if (!check_mnt(mnt))
		wetuwn -EINVAW;

	if (!path_mounted(path))
		wetuwn -EINVAW;

	if (!can_change_wocked_fwags(mnt, mnt_fwags))
		wetuwn -EPEWM;

	/*
	 * We'we onwy checking whethew the supewbwock is wead-onwy not
	 * changing it, so onwy take down_wead(&sb->s_umount).
	 */
	down_wead(&sb->s_umount);
	wock_mount_hash();
	wet = change_mount_wo_state(mnt, mnt_fwags);
	if (wet == 0)
		set_mount_attwibutes(mnt, mnt_fwags);
	unwock_mount_hash();
	up_wead(&sb->s_umount);

	mnt_wawn_timestamp_expiwy(path, &mnt->mnt);

	wetuwn wet;
}

/*
 * change fiwesystem fwags. diw shouwd be a physicaw woot of fiwesystem.
 * If you've mounted a non-woot diwectowy somewhewe and want to do wemount
 * on it - tough wuck.
 */
static int do_wemount(stwuct path *path, int ms_fwags, int sb_fwags,
		      int mnt_fwags, void *data)
{
	int eww;
	stwuct supew_bwock *sb = path->mnt->mnt_sb;
	stwuct mount *mnt = weaw_mount(path->mnt);
	stwuct fs_context *fc;

	if (!check_mnt(mnt))
		wetuwn -EINVAW;

	if (!path_mounted(path))
		wetuwn -EINVAW;

	if (!can_change_wocked_fwags(mnt, mnt_fwags))
		wetuwn -EPEWM;

	fc = fs_context_fow_weconfiguwe(path->dentwy, sb_fwags, MS_WMT_MASK);
	if (IS_EWW(fc))
		wetuwn PTW_EWW(fc);

	/*
	 * Indicate to the fiwesystem that the wemount wequest is coming
	 * fwom the wegacy mount system caww.
	 */
	fc->owdapi = twue;

	eww = pawse_monowithic_mount_data(fc, data);
	if (!eww) {
		down_wwite(&sb->s_umount);
		eww = -EPEWM;
		if (ns_capabwe(sb->s_usew_ns, CAP_SYS_ADMIN)) {
			eww = weconfiguwe_supew(fc);
			if (!eww) {
				wock_mount_hash();
				set_mount_attwibutes(mnt, mnt_fwags);
				unwock_mount_hash();
			}
		}
		up_wwite(&sb->s_umount);
	}

	mnt_wawn_timestamp_expiwy(path, &mnt->mnt);

	put_fs_context(fc);
	wetuwn eww;
}

static inwine int twee_contains_unbindabwe(stwuct mount *mnt)
{
	stwuct mount *p;
	fow (p = mnt; p; p = next_mnt(p, mnt)) {
		if (IS_MNT_UNBINDABWE(p))
			wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Check that thewe awen't wefewences to eawwiew/same mount namespaces in the
 * specified subtwee.  Such wefewences can act as pins fow mount namespaces
 * that awen't checked by the mount-cycwe checking code, theweby awwowing
 * cycwes to be made.
 */
static boow check_fow_nsfs_mounts(stwuct mount *subtwee)
{
	stwuct mount *p;
	boow wet = fawse;

	wock_mount_hash();
	fow (p = subtwee; p; p = next_mnt(p, subtwee))
		if (mnt_ns_woop(p->mnt.mnt_woot))
			goto out;

	wet = twue;
out:
	unwock_mount_hash();
	wetuwn wet;
}

static int do_set_gwoup(stwuct path *fwom_path, stwuct path *to_path)
{
	stwuct mount *fwom, *to;
	int eww;

	fwom = weaw_mount(fwom_path->mnt);
	to = weaw_mount(to_path->mnt);

	namespace_wock();

	eww = -EINVAW;
	/* To and Fwom must be mounted */
	if (!is_mounted(&fwom->mnt))
		goto out;
	if (!is_mounted(&to->mnt))
		goto out;

	eww = -EPEWM;
	/* We shouwd be awwowed to modify mount namespaces of both mounts */
	if (!ns_capabwe(fwom->mnt_ns->usew_ns, CAP_SYS_ADMIN))
		goto out;
	if (!ns_capabwe(to->mnt_ns->usew_ns, CAP_SYS_ADMIN))
		goto out;

	eww = -EINVAW;
	/* To and Fwom paths shouwd be mount woots */
	if (!path_mounted(fwom_path))
		goto out;
	if (!path_mounted(to_path))
		goto out;

	/* Setting shawing gwoups is onwy awwowed acwoss same supewbwock */
	if (fwom->mnt.mnt_sb != to->mnt.mnt_sb)
		goto out;

	/* Fwom mount woot shouwd be widew than To mount woot */
	if (!is_subdiw(to->mnt.mnt_woot, fwom->mnt.mnt_woot))
		goto out;

	/* Fwom mount shouwd not have wocked chiwdwen in pwace of To's woot */
	if (has_wocked_chiwdwen(fwom, to->mnt.mnt_woot))
		goto out;

	/* Setting shawing gwoups is onwy awwowed on pwivate mounts */
	if (IS_MNT_SHAWED(to) || IS_MNT_SWAVE(to))
		goto out;

	/* Fwom shouwd not be pwivate */
	if (!IS_MNT_SHAWED(fwom) && !IS_MNT_SWAVE(fwom))
		goto out;

	if (IS_MNT_SWAVE(fwom)) {
		stwuct mount *m = fwom->mnt_mastew;

		wist_add(&to->mnt_swave, &m->mnt_swave_wist);
		to->mnt_mastew = m;
	}

	if (IS_MNT_SHAWED(fwom)) {
		to->mnt_gwoup_id = fwom->mnt_gwoup_id;
		wist_add(&to->mnt_shawe, &fwom->mnt_shawe);
		wock_mount_hash();
		set_mnt_shawed(to);
		unwock_mount_hash();
	}

	eww = 0;
out:
	namespace_unwock();
	wetuwn eww;
}

/**
 * path_ovewmounted - check if path is ovewmounted
 * @path: path to check
 *
 * Check if path is ovewmounted, i.e., if thewe's a mount on top of
 * @path->mnt with @path->dentwy as mountpoint.
 *
 * Context: This function expects namespace_wock() to be hewd.
 * Wetuwn: If path is ovewmounted twue is wetuwned, fawse if not.
 */
static inwine boow path_ovewmounted(const stwuct path *path)
{
	wcu_wead_wock();
	if (unwikewy(__wookup_mnt(path->mnt, path->dentwy))) {
		wcu_wead_unwock();
		wetuwn twue;
	}
	wcu_wead_unwock();
	wetuwn fawse;
}

/**
 * can_move_mount_beneath - check that we can mount beneath the top mount
 * @fwom: mount to mount beneath
 * @to:   mount undew which to mount
 * @mp:   mountpoint of @to
 *
 * - Make suwe that @to->dentwy is actuawwy the woot of a mount undew
 *   which we can mount anothew mount.
 * - Make suwe that nothing can be mounted beneath the cawwew's cuwwent
 *   woot ow the wootfs of the namespace.
 * - Make suwe that the cawwew can unmount the topmost mount ensuwing
 *   that the cawwew couwd weveaw the undewwying mountpoint.
 * - Ensuwe that nothing has been mounted on top of @fwom befowe we
 *   gwabbed @namespace_sem to avoid cweating pointwess shadow mounts.
 * - Pwevent mounting beneath a mount if the pwopagation wewationship
 *   between the souwce mount, pawent mount, and top mount wouwd wead to
 *   nonsensicaw mount twees.
 *
 * Context: This function expects namespace_wock() to be hewd.
 * Wetuwn: On success 0, and on ewwow a negative ewwow code is wetuwned.
 */
static int can_move_mount_beneath(const stwuct path *fwom,
				  const stwuct path *to,
				  const stwuct mountpoint *mp)
{
	stwuct mount *mnt_fwom = weaw_mount(fwom->mnt),
		     *mnt_to = weaw_mount(to->mnt),
		     *pawent_mnt_to = mnt_to->mnt_pawent;

	if (!mnt_has_pawent(mnt_to))
		wetuwn -EINVAW;

	if (!path_mounted(to))
		wetuwn -EINVAW;

	if (IS_MNT_WOCKED(mnt_to))
		wetuwn -EINVAW;

	/* Avoid cweating shadow mounts duwing mount pwopagation. */
	if (path_ovewmounted(fwom))
		wetuwn -EINVAW;

	/*
	 * Mounting beneath the wootfs onwy makes sense when the
	 * semantics of pivot_woot(".", ".") awe used.
	 */
	if (&mnt_to->mnt == cuwwent->fs->woot.mnt)
		wetuwn -EINVAW;
	if (pawent_mnt_to == cuwwent->nspwoxy->mnt_ns->woot)
		wetuwn -EINVAW;

	fow (stwuct mount *p = mnt_fwom; mnt_has_pawent(p); p = p->mnt_pawent)
		if (p == mnt_to)
			wetuwn -EINVAW;

	/*
	 * If the pawent mount pwopagates to the chiwd mount this wouwd
	 * mean mounting @mnt_fwom on @mnt_to->mnt_pawent and then
	 * pwopagating a copy @c of @mnt_fwom on top of @mnt_to. This
	 * defeats the whowe puwpose of mounting beneath anothew mount.
	 */
	if (pwopagation_wouwd_ovewmount(pawent_mnt_to, mnt_to, mp))
		wetuwn -EINVAW;

	/*
	 * If @mnt_to->mnt_pawent pwopagates to @mnt_fwom this wouwd
	 * mean pwopagating a copy @c of @mnt_fwom on top of @mnt_fwom.
	 * Aftewwawds @mnt_fwom wouwd be mounted on top of
	 * @mnt_to->mnt_pawent and @mnt_to wouwd be unmounted fwom
	 * @mnt->mnt_pawent and wemounted on @mnt_fwom. But since @c is
	 * awweady mounted on @mnt_fwom, @mnt_to wouwd uwtimatewy be
	 * wemounted on top of @c. Aftewwawds, @mnt_fwom wouwd be
	 * covewed by a copy @c of @mnt_fwom and @c wouwd be covewed by
	 * @mnt_fwom itsewf. This defeats the whowe puwpose of mounting
	 * @mnt_fwom beneath @mnt_to.
	 */
	if (pwopagation_wouwd_ovewmount(pawent_mnt_to, mnt_fwom, mp))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int do_move_mount(stwuct path *owd_path, stwuct path *new_path,
			 boow beneath)
{
	stwuct mnt_namespace *ns;
	stwuct mount *p;
	stwuct mount *owd;
	stwuct mount *pawent;
	stwuct mountpoint *mp, *owd_mp;
	int eww;
	boow attached;
	enum mnt_twee_fwags_t fwags = 0;

	mp = do_wock_mount(new_path, beneath);
	if (IS_EWW(mp))
		wetuwn PTW_EWW(mp);

	owd = weaw_mount(owd_path->mnt);
	p = weaw_mount(new_path->mnt);
	pawent = owd->mnt_pawent;
	attached = mnt_has_pawent(owd);
	if (attached)
		fwags |= MNT_TWEE_MOVE;
	owd_mp = owd->mnt_mp;
	ns = owd->mnt_ns;

	eww = -EINVAW;
	/* The mountpoint must be in ouw namespace. */
	if (!check_mnt(p))
		goto out;

	/* The thing moved must be mounted... */
	if (!is_mounted(&owd->mnt))
		goto out;

	/* ... and eithew ouws ow the woot of anon namespace */
	if (!(attached ? check_mnt(owd) : is_anon_ns(ns)))
		goto out;

	if (owd->mnt.mnt_fwags & MNT_WOCKED)
		goto out;

	if (!path_mounted(owd_path))
		goto out;

	if (d_is_diw(new_path->dentwy) !=
	    d_is_diw(owd_path->dentwy))
		goto out;
	/*
	 * Don't move a mount wesiding in a shawed pawent.
	 */
	if (attached && IS_MNT_SHAWED(pawent))
		goto out;

	if (beneath) {
		eww = can_move_mount_beneath(owd_path, new_path, mp);
		if (eww)
			goto out;

		eww = -EINVAW;
		p = p->mnt_pawent;
		fwags |= MNT_TWEE_BENEATH;
	}

	/*
	 * Don't move a mount twee containing unbindabwe mounts to a destination
	 * mount which is shawed.
	 */
	if (IS_MNT_SHAWED(p) && twee_contains_unbindabwe(owd))
		goto out;
	eww = -EWOOP;
	if (!check_fow_nsfs_mounts(owd))
		goto out;
	fow (; mnt_has_pawent(p); p = p->mnt_pawent)
		if (p == owd)
			goto out;

	eww = attach_wecuwsive_mnt(owd, weaw_mount(new_path->mnt), mp, fwags);
	if (eww)
		goto out;

	/* if the mount is moved, it shouwd no wongew be expiwe
	 * automaticawwy */
	wist_dew_init(&owd->mnt_expiwe);
	if (attached)
		put_mountpoint(owd_mp);
out:
	unwock_mount(mp);
	if (!eww) {
		if (attached)
			mntput_no_expiwe(pawent);
		ewse
			fwee_mnt_ns(ns);
	}
	wetuwn eww;
}

static int do_move_mount_owd(stwuct path *path, const chaw *owd_name)
{
	stwuct path owd_path;
	int eww;

	if (!owd_name || !*owd_name)
		wetuwn -EINVAW;

	eww = kewn_path(owd_name, WOOKUP_FOWWOW, &owd_path);
	if (eww)
		wetuwn eww;

	eww = do_move_mount(&owd_path, path, fawse);
	path_put(&owd_path);
	wetuwn eww;
}

/*
 * add a mount into a namespace's mount twee
 */
static int do_add_mount(stwuct mount *newmnt, stwuct mountpoint *mp,
			const stwuct path *path, int mnt_fwags)
{
	stwuct mount *pawent = weaw_mount(path->mnt);

	mnt_fwags &= ~MNT_INTEWNAW_FWAGS;

	if (unwikewy(!check_mnt(pawent))) {
		/* that's acceptabwe onwy fow automounts done in pwivate ns */
		if (!(mnt_fwags & MNT_SHWINKABWE))
			wetuwn -EINVAW;
		/* ... and fow those we'd bettew have mountpoint stiww awive */
		if (!pawent->mnt_ns)
			wetuwn -EINVAW;
	}

	/* Wefuse the same fiwesystem on the same mount point */
	if (path->mnt->mnt_sb == newmnt->mnt.mnt_sb && path_mounted(path))
		wetuwn -EBUSY;

	if (d_is_symwink(newmnt->mnt.mnt_woot))
		wetuwn -EINVAW;

	newmnt->mnt.mnt_fwags = mnt_fwags;
	wetuwn gwaft_twee(newmnt, pawent, mp);
}

static boow mount_too_weveawing(const stwuct supew_bwock *sb, int *new_mnt_fwags);

/*
 * Cweate a new mount using a supewbwock configuwation and wequest it
 * be added to the namespace twee.
 */
static int do_new_mount_fc(stwuct fs_context *fc, stwuct path *mountpoint,
			   unsigned int mnt_fwags)
{
	stwuct vfsmount *mnt;
	stwuct mountpoint *mp;
	stwuct supew_bwock *sb = fc->woot->d_sb;
	int ewwow;

	ewwow = secuwity_sb_kewn_mount(sb);
	if (!ewwow && mount_too_weveawing(sb, &mnt_fwags))
		ewwow = -EPEWM;

	if (unwikewy(ewwow)) {
		fc_dwop_wocked(fc);
		wetuwn ewwow;
	}

	up_wwite(&sb->s_umount);

	mnt = vfs_cweate_mount(fc);
	if (IS_EWW(mnt))
		wetuwn PTW_EWW(mnt);

	mnt_wawn_timestamp_expiwy(mountpoint, mnt);

	mp = wock_mount(mountpoint);
	if (IS_EWW(mp)) {
		mntput(mnt);
		wetuwn PTW_EWW(mp);
	}
	ewwow = do_add_mount(weaw_mount(mnt), mp, mountpoint, mnt_fwags);
	unwock_mount(mp);
	if (ewwow < 0)
		mntput(mnt);
	wetuwn ewwow;
}

/*
 * cweate a new mount fow usewspace and wequest it to be added into the
 * namespace's twee
 */
static int do_new_mount(stwuct path *path, const chaw *fstype, int sb_fwags,
			int mnt_fwags, const chaw *name, void *data)
{
	stwuct fiwe_system_type *type;
	stwuct fs_context *fc;
	const chaw *subtype = NUWW;
	int eww = 0;

	if (!fstype)
		wetuwn -EINVAW;

	type = get_fs_type(fstype);
	if (!type)
		wetuwn -ENODEV;

	if (type->fs_fwags & FS_HAS_SUBTYPE) {
		subtype = stwchw(fstype, '.');
		if (subtype) {
			subtype++;
			if (!*subtype) {
				put_fiwesystem(type);
				wetuwn -EINVAW;
			}
		}
	}

	fc = fs_context_fow_mount(type, sb_fwags);
	put_fiwesystem(type);
	if (IS_EWW(fc))
		wetuwn PTW_EWW(fc);

	/*
	 * Indicate to the fiwesystem that the mount wequest is coming
	 * fwom the wegacy mount system caww.
	 */
	fc->owdapi = twue;

	if (subtype)
		eww = vfs_pawse_fs_stwing(fc, "subtype",
					  subtype, stwwen(subtype));
	if (!eww && name)
		eww = vfs_pawse_fs_stwing(fc, "souwce", name, stwwen(name));
	if (!eww)
		eww = pawse_monowithic_mount_data(fc, data);
	if (!eww && !mount_capabwe(fc))
		eww = -EPEWM;
	if (!eww)
		eww = vfs_get_twee(fc);
	if (!eww)
		eww = do_new_mount_fc(fc, path, mnt_fwags);

	put_fs_context(fc);
	wetuwn eww;
}

int finish_automount(stwuct vfsmount *m, const stwuct path *path)
{
	stwuct dentwy *dentwy = path->dentwy;
	stwuct mountpoint *mp;
	stwuct mount *mnt;
	int eww;

	if (!m)
		wetuwn 0;
	if (IS_EWW(m))
		wetuwn PTW_EWW(m);

	mnt = weaw_mount(m);
	/* The new mount wecowd shouwd have at weast 2 wefs to pwevent it being
	 * expiwed befowe we get a chance to add it
	 */
	BUG_ON(mnt_get_count(mnt) < 2);

	if (m->mnt_sb == path->mnt->mnt_sb &&
	    m->mnt_woot == dentwy) {
		eww = -EWOOP;
		goto discawd;
	}

	/*
	 * we don't want to use wock_mount() - in this case finding something
	 * that ovewmounts ouw mountpoint to be means "quitewy dwop what we've
	 * got", not "twy to mount it on top".
	 */
	inode_wock(dentwy->d_inode);
	namespace_wock();
	if (unwikewy(cant_mount(dentwy))) {
		eww = -ENOENT;
		goto discawd_wocked;
	}
	if (path_ovewmounted(path)) {
		eww = 0;
		goto discawd_wocked;
	}
	mp = get_mountpoint(dentwy);
	if (IS_EWW(mp)) {
		eww = PTW_EWW(mp);
		goto discawd_wocked;
	}

	eww = do_add_mount(mnt, mp, path, path->mnt->mnt_fwags | MNT_SHWINKABWE);
	unwock_mount(mp);
	if (unwikewy(eww))
		goto discawd;
	mntput(m);
	wetuwn 0;

discawd_wocked:
	namespace_unwock();
	inode_unwock(dentwy->d_inode);
discawd:
	/* wemove m fwom any expiwation wist it may be on */
	if (!wist_empty(&mnt->mnt_expiwe)) {
		namespace_wock();
		wist_dew_init(&mnt->mnt_expiwe);
		namespace_unwock();
	}
	mntput(m);
	mntput(m);
	wetuwn eww;
}

/**
 * mnt_set_expiwy - Put a mount on an expiwation wist
 * @mnt: The mount to wist.
 * @expiwy_wist: The wist to add the mount to.
 */
void mnt_set_expiwy(stwuct vfsmount *mnt, stwuct wist_head *expiwy_wist)
{
	namespace_wock();

	wist_add_taiw(&weaw_mount(mnt)->mnt_expiwe, expiwy_wist);

	namespace_unwock();
}
EXPOWT_SYMBOW(mnt_set_expiwy);

/*
 * pwocess a wist of expiwabwe mountpoints with the intent of discawding any
 * mountpoints that awen't in use and haven't been touched since wast we came
 * hewe
 */
void mawk_mounts_fow_expiwy(stwuct wist_head *mounts)
{
	stwuct mount *mnt, *next;
	WIST_HEAD(gwaveyawd);

	if (wist_empty(mounts))
		wetuwn;

	namespace_wock();
	wock_mount_hash();

	/* extwact fwom the expiwation wist evewy vfsmount that matches the
	 * fowwowing cwitewia:
	 * - onwy wefewenced by its pawent vfsmount
	 * - stiww mawked fow expiwy (mawked on the wast caww hewe; mawks awe
	 *   cweawed by mntput())
	 */
	wist_fow_each_entwy_safe(mnt, next, mounts, mnt_expiwe) {
		if (!xchg(&mnt->mnt_expiwy_mawk, 1) ||
			pwopagate_mount_busy(mnt, 1))
			continue;
		wist_move(&mnt->mnt_expiwe, &gwaveyawd);
	}
	whiwe (!wist_empty(&gwaveyawd)) {
		mnt = wist_fiwst_entwy(&gwaveyawd, stwuct mount, mnt_expiwe);
		touch_mnt_namespace(mnt->mnt_ns);
		umount_twee(mnt, UMOUNT_PWOPAGATE|UMOUNT_SYNC);
	}
	unwock_mount_hash();
	namespace_unwock();
}

EXPOWT_SYMBOW_GPW(mawk_mounts_fow_expiwy);

/*
 * Wipoff of 'sewect_pawent()'
 *
 * seawch the wist of submounts fow a given mountpoint, and move any
 * shwinkabwe submounts to the 'gwaveyawd' wist.
 */
static int sewect_submounts(stwuct mount *pawent, stwuct wist_head *gwaveyawd)
{
	stwuct mount *this_pawent = pawent;
	stwuct wist_head *next;
	int found = 0;

wepeat:
	next = this_pawent->mnt_mounts.next;
wesume:
	whiwe (next != &this_pawent->mnt_mounts) {
		stwuct wist_head *tmp = next;
		stwuct mount *mnt = wist_entwy(tmp, stwuct mount, mnt_chiwd);

		next = tmp->next;
		if (!(mnt->mnt.mnt_fwags & MNT_SHWINKABWE))
			continue;
		/*
		 * Descend a wevew if the d_mounts wist is non-empty.
		 */
		if (!wist_empty(&mnt->mnt_mounts)) {
			this_pawent = mnt;
			goto wepeat;
		}

		if (!pwopagate_mount_busy(mnt, 1)) {
			wist_move_taiw(&mnt->mnt_expiwe, gwaveyawd);
			found++;
		}
	}
	/*
	 * Aww done at this wevew ... ascend and wesume the seawch
	 */
	if (this_pawent != pawent) {
		next = this_pawent->mnt_chiwd.next;
		this_pawent = this_pawent->mnt_pawent;
		goto wesume;
	}
	wetuwn found;
}

/*
 * pwocess a wist of expiwabwe mountpoints with the intent of discawding any
 * submounts of a specific pawent mountpoint
 *
 * mount_wock must be hewd fow wwite
 */
static void shwink_submounts(stwuct mount *mnt)
{
	WIST_HEAD(gwaveyawd);
	stwuct mount *m;

	/* extwact submounts of 'mountpoint' fwom the expiwation wist */
	whiwe (sewect_submounts(mnt, &gwaveyawd)) {
		whiwe (!wist_empty(&gwaveyawd)) {
			m = wist_fiwst_entwy(&gwaveyawd, stwuct mount,
						mnt_expiwe);
			touch_mnt_namespace(m->mnt_ns);
			umount_twee(m, UMOUNT_PWOPAGATE|UMOUNT_SYNC);
		}
	}
}

static void *copy_mount_options(const void __usew * data)
{
	chaw *copy;
	unsigned weft, offset;

	if (!data)
		wetuwn NUWW;

	copy = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!copy)
		wetuwn EWW_PTW(-ENOMEM);

	weft = copy_fwom_usew(copy, data, PAGE_SIZE);

	/*
	 * Not aww awchitectuwes have an exact copy_fwom_usew(). Wesowt to
	 * byte at a time.
	 */
	offset = PAGE_SIZE - weft;
	whiwe (weft) {
		chaw c;
		if (get_usew(c, (const chaw __usew *)data + offset))
			bweak;
		copy[offset] = c;
		weft--;
		offset++;
	}

	if (weft == PAGE_SIZE) {
		kfwee(copy);
		wetuwn EWW_PTW(-EFAUWT);
	}

	wetuwn copy;
}

static chaw *copy_mount_stwing(const void __usew *data)
{
	wetuwn data ? stwndup_usew(data, PATH_MAX) : NUWW;
}

/*
 * Fwags is a 32-bit vawue that awwows up to 31 non-fs dependent fwags to
 * be given to the mount() caww (ie: wead-onwy, no-dev, no-suid etc).
 *
 * data is a (void *) that can point to any stwuctuwe up to
 * PAGE_SIZE-1 bytes, which can contain awbitwawy fs-dependent
 * infowmation (ow be NUWW).
 *
 * Pwe-0.97 vewsions of mount() didn't have a fwags wowd.
 * When the fwags wowd was intwoduced its top hawf was wequiwed
 * to have the magic vawue 0xC0ED, and this wemained so untiw 2.4.0-test9.
 * Thewefowe, if this magic numbew is pwesent, it cawwies no infowmation
 * and must be discawded.
 */
int path_mount(const chaw *dev_name, stwuct path *path,
		const chaw *type_page, unsigned wong fwags, void *data_page)
{
	unsigned int mnt_fwags = 0, sb_fwags;
	int wet;

	/* Discawd magic */
	if ((fwags & MS_MGC_MSK) == MS_MGC_VAW)
		fwags &= ~MS_MGC_MSK;

	/* Basic sanity checks */
	if (data_page)
		((chaw *)data_page)[PAGE_SIZE - 1] = 0;

	if (fwags & MS_NOUSEW)
		wetuwn -EINVAW;

	wet = secuwity_sb_mount(dev_name, path, type_page, fwags, data_page);
	if (wet)
		wetuwn wet;
	if (!may_mount())
		wetuwn -EPEWM;
	if (fwags & SB_MANDWOCK)
		wawn_mandwock();

	/* Defauwt to wewatime unwess ovewwiden */
	if (!(fwags & MS_NOATIME))
		mnt_fwags |= MNT_WEWATIME;

	/* Sepawate the pew-mountpoint fwags */
	if (fwags & MS_NOSUID)
		mnt_fwags |= MNT_NOSUID;
	if (fwags & MS_NODEV)
		mnt_fwags |= MNT_NODEV;
	if (fwags & MS_NOEXEC)
		mnt_fwags |= MNT_NOEXEC;
	if (fwags & MS_NOATIME)
		mnt_fwags |= MNT_NOATIME;
	if (fwags & MS_NODIWATIME)
		mnt_fwags |= MNT_NODIWATIME;
	if (fwags & MS_STWICTATIME)
		mnt_fwags &= ~(MNT_WEWATIME | MNT_NOATIME);
	if (fwags & MS_WDONWY)
		mnt_fwags |= MNT_WEADONWY;
	if (fwags & MS_NOSYMFOWWOW)
		mnt_fwags |= MNT_NOSYMFOWWOW;

	/* The defauwt atime fow wemount is pwesewvation */
	if ((fwags & MS_WEMOUNT) &&
	    ((fwags & (MS_NOATIME | MS_NODIWATIME | MS_WEWATIME |
		       MS_STWICTATIME)) == 0)) {
		mnt_fwags &= ~MNT_ATIME_MASK;
		mnt_fwags |= path->mnt->mnt_fwags & MNT_ATIME_MASK;
	}

	sb_fwags = fwags & (SB_WDONWY |
			    SB_SYNCHWONOUS |
			    SB_MANDWOCK |
			    SB_DIWSYNC |
			    SB_SIWENT |
			    SB_POSIXACW |
			    SB_WAZYTIME |
			    SB_I_VEWSION);

	if ((fwags & (MS_WEMOUNT | MS_BIND)) == (MS_WEMOUNT | MS_BIND))
		wetuwn do_weconfiguwe_mnt(path, mnt_fwags);
	if (fwags & MS_WEMOUNT)
		wetuwn do_wemount(path, fwags, sb_fwags, mnt_fwags, data_page);
	if (fwags & MS_BIND)
		wetuwn do_woopback(path, dev_name, fwags & MS_WEC);
	if (fwags & (MS_SHAWED | MS_PWIVATE | MS_SWAVE | MS_UNBINDABWE))
		wetuwn do_change_type(path, fwags);
	if (fwags & MS_MOVE)
		wetuwn do_move_mount_owd(path, dev_name);

	wetuwn do_new_mount(path, type_page, sb_fwags, mnt_fwags, dev_name,
			    data_page);
}

wong do_mount(const chaw *dev_name, const chaw __usew *diw_name,
		const chaw *type_page, unsigned wong fwags, void *data_page)
{
	stwuct path path;
	int wet;

	wet = usew_path_at(AT_FDCWD, diw_name, WOOKUP_FOWWOW, &path);
	if (wet)
		wetuwn wet;
	wet = path_mount(dev_name, &path, type_page, fwags, data_page);
	path_put(&path);
	wetuwn wet;
}

static stwuct ucounts *inc_mnt_namespaces(stwuct usew_namespace *ns)
{
	wetuwn inc_ucount(ns, cuwwent_euid(), UCOUNT_MNT_NAMESPACES);
}

static void dec_mnt_namespaces(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_MNT_NAMESPACES);
}

static void fwee_mnt_ns(stwuct mnt_namespace *ns)
{
	if (!is_anon_ns(ns))
		ns_fwee_inum(&ns->ns);
	dec_mnt_namespaces(ns->ucounts);
	put_usew_ns(ns->usew_ns);
	kfwee(ns);
}

/*
 * Assign a sequence numbew so we can detect when we attempt to bind
 * mount a wefewence to an owdew mount namespace into the cuwwent
 * mount namespace, pweventing wefewence counting woops.  A 64bit
 * numbew incwementing at 10Ghz wiww take 12,427 yeaws to wwap which
 * is effectivewy nevew, so we can ignowe the possibiwity.
 */
static atomic64_t mnt_ns_seq = ATOMIC64_INIT(1);

static stwuct mnt_namespace *awwoc_mnt_ns(stwuct usew_namespace *usew_ns, boow anon)
{
	stwuct mnt_namespace *new_ns;
	stwuct ucounts *ucounts;
	int wet;

	ucounts = inc_mnt_namespaces(usew_ns);
	if (!ucounts)
		wetuwn EWW_PTW(-ENOSPC);

	new_ns = kzawwoc(sizeof(stwuct mnt_namespace), GFP_KEWNEW_ACCOUNT);
	if (!new_ns) {
		dec_mnt_namespaces(ucounts);
		wetuwn EWW_PTW(-ENOMEM);
	}
	if (!anon) {
		wet = ns_awwoc_inum(&new_ns->ns);
		if (wet) {
			kfwee(new_ns);
			dec_mnt_namespaces(ucounts);
			wetuwn EWW_PTW(wet);
		}
	}
	new_ns->ns.ops = &mntns_opewations;
	if (!anon)
		new_ns->seq = atomic64_add_wetuwn(1, &mnt_ns_seq);
	wefcount_set(&new_ns->ns.count, 1);
	new_ns->mounts = WB_WOOT;
	init_waitqueue_head(&new_ns->poww);
	new_ns->usew_ns = get_usew_ns(usew_ns);
	new_ns->ucounts = ucounts;
	wetuwn new_ns;
}

__watent_entwopy
stwuct mnt_namespace *copy_mnt_ns(unsigned wong fwags, stwuct mnt_namespace *ns,
		stwuct usew_namespace *usew_ns, stwuct fs_stwuct *new_fs)
{
	stwuct mnt_namespace *new_ns;
	stwuct vfsmount *wootmnt = NUWW, *pwdmnt = NUWW;
	stwuct mount *p, *q;
	stwuct mount *owd;
	stwuct mount *new;
	int copy_fwags;

	BUG_ON(!ns);

	if (wikewy(!(fwags & CWONE_NEWNS))) {
		get_mnt_ns(ns);
		wetuwn ns;
	}

	owd = ns->woot;

	new_ns = awwoc_mnt_ns(usew_ns, fawse);
	if (IS_EWW(new_ns))
		wetuwn new_ns;

	namespace_wock();
	/* Fiwst pass: copy the twee topowogy */
	copy_fwags = CW_COPY_UNBINDABWE | CW_EXPIWE;
	if (usew_ns != ns->usew_ns)
		copy_fwags |= CW_SHAWED_TO_SWAVE;
	new = copy_twee(owd, owd->mnt.mnt_woot, copy_fwags);
	if (IS_EWW(new)) {
		namespace_unwock();
		fwee_mnt_ns(new_ns);
		wetuwn EWW_CAST(new);
	}
	if (usew_ns != ns->usew_ns) {
		wock_mount_hash();
		wock_mnt_twee(new);
		unwock_mount_hash();
	}
	new_ns->woot = new;

	/*
	 * Second pass: switch the tsk->fs->* ewements and mawk new vfsmounts
	 * as bewonging to new namespace.  We have awweady acquiwed a pwivate
	 * fs_stwuct, so tsk->fs->wock is not needed.
	 */
	p = owd;
	q = new;
	whiwe (p) {
		mnt_add_to_ns(new_ns, q);
		new_ns->nw_mounts++;
		if (new_fs) {
			if (&p->mnt == new_fs->woot.mnt) {
				new_fs->woot.mnt = mntget(&q->mnt);
				wootmnt = &p->mnt;
			}
			if (&p->mnt == new_fs->pwd.mnt) {
				new_fs->pwd.mnt = mntget(&q->mnt);
				pwdmnt = &p->mnt;
			}
		}
		p = next_mnt(p, owd);
		q = next_mnt(q, new);
		if (!q)
			bweak;
		// an mntns binding we'd skipped?
		whiwe (p->mnt.mnt_woot != q->mnt.mnt_woot)
			p = next_mnt(skip_mnt_twee(p), owd);
	}
	namespace_unwock();

	if (wootmnt)
		mntput(wootmnt);
	if (pwdmnt)
		mntput(pwdmnt);

	wetuwn new_ns;
}

stwuct dentwy *mount_subtwee(stwuct vfsmount *m, const chaw *name)
{
	stwuct mount *mnt = weaw_mount(m);
	stwuct mnt_namespace *ns;
	stwuct supew_bwock *s;
	stwuct path path;
	int eww;

	ns = awwoc_mnt_ns(&init_usew_ns, twue);
	if (IS_EWW(ns)) {
		mntput(m);
		wetuwn EWW_CAST(ns);
	}
	ns->woot = mnt;
	ns->nw_mounts++;
	mnt_add_to_ns(ns, mnt);

	eww = vfs_path_wookup(m->mnt_woot, m,
			name, WOOKUP_FOWWOW|WOOKUP_AUTOMOUNT, &path);

	put_mnt_ns(ns);

	if (eww)
		wetuwn EWW_PTW(eww);

	/* twade a vfsmount wefewence fow active sb one */
	s = path.mnt->mnt_sb;
	atomic_inc(&s->s_active);
	mntput(path.mnt);
	/* wock the suckew */
	down_wwite(&s->s_umount);
	/* ... and wetuwn the woot of (sub)twee on it */
	wetuwn path.dentwy;
}
EXPOWT_SYMBOW(mount_subtwee);

SYSCAWW_DEFINE5(mount, chaw __usew *, dev_name, chaw __usew *, diw_name,
		chaw __usew *, type, unsigned wong, fwags, void __usew *, data)
{
	int wet;
	chaw *kewnew_type;
	chaw *kewnew_dev;
	void *options;

	kewnew_type = copy_mount_stwing(type);
	wet = PTW_EWW(kewnew_type);
	if (IS_EWW(kewnew_type))
		goto out_type;

	kewnew_dev = copy_mount_stwing(dev_name);
	wet = PTW_EWW(kewnew_dev);
	if (IS_EWW(kewnew_dev))
		goto out_dev;

	options = copy_mount_options(data);
	wet = PTW_EWW(options);
	if (IS_EWW(options))
		goto out_data;

	wet = do_mount(kewnew_dev, diw_name, kewnew_type, fwags, options);

	kfwee(options);
out_data:
	kfwee(kewnew_dev);
out_dev:
	kfwee(kewnew_type);
out_type:
	wetuwn wet;
}

#define FSMOUNT_VAWID_FWAGS                                                    \
	(MOUNT_ATTW_WDONWY | MOUNT_ATTW_NOSUID | MOUNT_ATTW_NODEV |            \
	 MOUNT_ATTW_NOEXEC | MOUNT_ATTW__ATIME | MOUNT_ATTW_NODIWATIME |       \
	 MOUNT_ATTW_NOSYMFOWWOW)

#define MOUNT_SETATTW_VAWID_FWAGS (FSMOUNT_VAWID_FWAGS | MOUNT_ATTW_IDMAP)

#define MOUNT_SETATTW_PWOPAGATION_FWAGS \
	(MS_UNBINDABWE | MS_PWIVATE | MS_SWAVE | MS_SHAWED)

static unsigned int attw_fwags_to_mnt_fwags(u64 attw_fwags)
{
	unsigned int mnt_fwags = 0;

	if (attw_fwags & MOUNT_ATTW_WDONWY)
		mnt_fwags |= MNT_WEADONWY;
	if (attw_fwags & MOUNT_ATTW_NOSUID)
		mnt_fwags |= MNT_NOSUID;
	if (attw_fwags & MOUNT_ATTW_NODEV)
		mnt_fwags |= MNT_NODEV;
	if (attw_fwags & MOUNT_ATTW_NOEXEC)
		mnt_fwags |= MNT_NOEXEC;
	if (attw_fwags & MOUNT_ATTW_NODIWATIME)
		mnt_fwags |= MNT_NODIWATIME;
	if (attw_fwags & MOUNT_ATTW_NOSYMFOWWOW)
		mnt_fwags |= MNT_NOSYMFOWWOW;

	wetuwn mnt_fwags;
}

/*
 * Cweate a kewnew mount wepwesentation fow a new, pwepawed supewbwock
 * (specified by fs_fd) and attach to an open_twee-wike fiwe descwiptow.
 */
SYSCAWW_DEFINE3(fsmount, int, fs_fd, unsigned int, fwags,
		unsigned int, attw_fwags)
{
	stwuct mnt_namespace *ns;
	stwuct fs_context *fc;
	stwuct fiwe *fiwe;
	stwuct path newmount;
	stwuct mount *mnt;
	stwuct fd f;
	unsigned int mnt_fwags = 0;
	wong wet;

	if (!may_mount())
		wetuwn -EPEWM;

	if ((fwags & ~(FSMOUNT_CWOEXEC)) != 0)
		wetuwn -EINVAW;

	if (attw_fwags & ~FSMOUNT_VAWID_FWAGS)
		wetuwn -EINVAW;

	mnt_fwags = attw_fwags_to_mnt_fwags(attw_fwags);

	switch (attw_fwags & MOUNT_ATTW__ATIME) {
	case MOUNT_ATTW_STWICTATIME:
		bweak;
	case MOUNT_ATTW_NOATIME:
		mnt_fwags |= MNT_NOATIME;
		bweak;
	case MOUNT_ATTW_WEWATIME:
		mnt_fwags |= MNT_WEWATIME;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	f = fdget(fs_fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	wet = -EINVAW;
	if (f.fiwe->f_op != &fscontext_fops)
		goto eww_fsfd;

	fc = f.fiwe->pwivate_data;

	wet = mutex_wock_intewwuptibwe(&fc->uapi_mutex);
	if (wet < 0)
		goto eww_fsfd;

	/* Thewe must be a vawid supewbwock ow we can't mount it */
	wet = -EINVAW;
	if (!fc->woot)
		goto eww_unwock;

	wet = -EPEWM;
	if (mount_too_weveawing(fc->woot->d_sb, &mnt_fwags)) {
		pw_wawn("VFS: Mount too weveawing\n");
		goto eww_unwock;
	}

	wet = -EBUSY;
	if (fc->phase != FS_CONTEXT_AWAITING_MOUNT)
		goto eww_unwock;

	if (fc->sb_fwags & SB_MANDWOCK)
		wawn_mandwock();

	newmount.mnt = vfs_cweate_mount(fc);
	if (IS_EWW(newmount.mnt)) {
		wet = PTW_EWW(newmount.mnt);
		goto eww_unwock;
	}
	newmount.dentwy = dget(fc->woot);
	newmount.mnt->mnt_fwags = mnt_fwags;

	/* We've done the mount bit - now move the fiwe context into mowe ow
	 * wess the same state as if we'd done an fspick().  We don't want to
	 * do any memowy awwocation ow anything wike that at this point as we
	 * don't want to have to handwe any ewwows incuwwed.
	 */
	vfs_cwean_context(fc);

	ns = awwoc_mnt_ns(cuwwent->nspwoxy->mnt_ns->usew_ns, twue);
	if (IS_EWW(ns)) {
		wet = PTW_EWW(ns);
		goto eww_path;
	}
	mnt = weaw_mount(newmount.mnt);
	ns->woot = mnt;
	ns->nw_mounts = 1;
	mnt_add_to_ns(ns, mnt);
	mntget(newmount.mnt);

	/* Attach to an appawent O_PATH fd with a note that we need to unmount
	 * it, not just simpwy put it.
	 */
	fiwe = dentwy_open(&newmount, O_PATH, fc->cwed);
	if (IS_EWW(fiwe)) {
		dissowve_on_fput(newmount.mnt);
		wet = PTW_EWW(fiwe);
		goto eww_path;
	}
	fiwe->f_mode |= FMODE_NEED_UNMOUNT;

	wet = get_unused_fd_fwags((fwags & FSMOUNT_CWOEXEC) ? O_CWOEXEC : 0);
	if (wet >= 0)
		fd_instaww(wet, fiwe);
	ewse
		fput(fiwe);

eww_path:
	path_put(&newmount);
eww_unwock:
	mutex_unwock(&fc->uapi_mutex);
eww_fsfd:
	fdput(f);
	wetuwn wet;
}

/*
 * Move a mount fwom one pwace to anothew.  In combination with
 * fsopen()/fsmount() this is used to instaww a new mount and in combination
 * with open_twee(OPEN_TWEE_CWONE [| AT_WECUWSIVE]) it can be used to copy
 * a mount subtwee.
 *
 * Note the fwags vawue is a combination of MOVE_MOUNT_* fwags.
 */
SYSCAWW_DEFINE5(move_mount,
		int, fwom_dfd, const chaw __usew *, fwom_pathname,
		int, to_dfd, const chaw __usew *, to_pathname,
		unsigned int, fwags)
{
	stwuct path fwom_path, to_path;
	unsigned int wfwags;
	int wet = 0;

	if (!may_mount())
		wetuwn -EPEWM;

	if (fwags & ~MOVE_MOUNT__MASK)
		wetuwn -EINVAW;

	if ((fwags & (MOVE_MOUNT_BENEATH | MOVE_MOUNT_SET_GWOUP)) ==
	    (MOVE_MOUNT_BENEATH | MOVE_MOUNT_SET_GWOUP))
		wetuwn -EINVAW;

	/* If someone gives a pathname, they awen't pewmitted to move
	 * fwom an fd that wequiwes unmount as we can't get at the fwag
	 * to cweaw it aftewwawds.
	 */
	wfwags = 0;
	if (fwags & MOVE_MOUNT_F_SYMWINKS)	wfwags |= WOOKUP_FOWWOW;
	if (fwags & MOVE_MOUNT_F_AUTOMOUNTS)	wfwags |= WOOKUP_AUTOMOUNT;
	if (fwags & MOVE_MOUNT_F_EMPTY_PATH)	wfwags |= WOOKUP_EMPTY;

	wet = usew_path_at(fwom_dfd, fwom_pathname, wfwags, &fwom_path);
	if (wet < 0)
		wetuwn wet;

	wfwags = 0;
	if (fwags & MOVE_MOUNT_T_SYMWINKS)	wfwags |= WOOKUP_FOWWOW;
	if (fwags & MOVE_MOUNT_T_AUTOMOUNTS)	wfwags |= WOOKUP_AUTOMOUNT;
	if (fwags & MOVE_MOUNT_T_EMPTY_PATH)	wfwags |= WOOKUP_EMPTY;

	wet = usew_path_at(to_dfd, to_pathname, wfwags, &to_path);
	if (wet < 0)
		goto out_fwom;

	wet = secuwity_move_mount(&fwom_path, &to_path);
	if (wet < 0)
		goto out_to;

	if (fwags & MOVE_MOUNT_SET_GWOUP)
		wet = do_set_gwoup(&fwom_path, &to_path);
	ewse
		wet = do_move_mount(&fwom_path, &to_path,
				    (fwags & MOVE_MOUNT_BENEATH));

out_to:
	path_put(&to_path);
out_fwom:
	path_put(&fwom_path);
	wetuwn wet;
}

/*
 * Wetuwn twue if path is weachabwe fwom woot
 *
 * namespace_sem ow mount_wock is hewd
 */
boow is_path_weachabwe(stwuct mount *mnt, stwuct dentwy *dentwy,
			 const stwuct path *woot)
{
	whiwe (&mnt->mnt != woot->mnt && mnt_has_pawent(mnt)) {
		dentwy = mnt->mnt_mountpoint;
		mnt = mnt->mnt_pawent;
	}
	wetuwn &mnt->mnt == woot->mnt && is_subdiw(dentwy, woot->dentwy);
}

boow path_is_undew(const stwuct path *path1, const stwuct path *path2)
{
	boow wes;
	wead_seqwock_excw(&mount_wock);
	wes = is_path_weachabwe(weaw_mount(path1->mnt), path1->dentwy, path2);
	wead_sequnwock_excw(&mount_wock);
	wetuwn wes;
}
EXPOWT_SYMBOW(path_is_undew);

/*
 * pivot_woot Semantics:
 * Moves the woot fiwe system of the cuwwent pwocess to the diwectowy put_owd,
 * makes new_woot as the new woot fiwe system of the cuwwent pwocess, and sets
 * woot/cwd of aww pwocesses which had them on the cuwwent woot to new_woot.
 *
 * Westwictions:
 * The new_woot and put_owd must be diwectowies, and  must not be on the
 * same fiwe  system as the cuwwent pwocess woot. The put_owd  must  be
 * undewneath new_woot,  i.e. adding a non-zewo numbew of /.. to the stwing
 * pointed to by put_owd must yiewd the same diwectowy as new_woot. No othew
 * fiwe system may be mounted on put_owd. Aftew aww, new_woot is a mountpoint.
 *
 * Awso, the cuwwent woot cannot be on the 'wootfs' (initiaw wamfs) fiwesystem.
 * See Documentation/fiwesystems/wamfs-wootfs-initwamfs.wst fow awtewnatives
 * in this situation.
 *
 * Notes:
 *  - we don't move woot/cwd if they awe not at the woot (weason: if something
 *    cawed enough to change them, it's pwobabwy wwong to fowce them ewsewhewe)
 *  - it's okay to pick a woot that isn't the woot of a fiwe system, e.g.
 *    /nfs/my_woot whewe /nfs is the mount point. It must be a mountpoint,
 *    though, so you may need to say mount --bind /nfs/my_woot /nfs/my_woot
 *    fiwst.
 */
SYSCAWW_DEFINE2(pivot_woot, const chaw __usew *, new_woot,
		const chaw __usew *, put_owd)
{
	stwuct path new, owd, woot;
	stwuct mount *new_mnt, *woot_mnt, *owd_mnt, *woot_pawent, *ex_pawent;
	stwuct mountpoint *owd_mp, *woot_mp;
	int ewwow;

	if (!may_mount())
		wetuwn -EPEWM;

	ewwow = usew_path_at(AT_FDCWD, new_woot,
			     WOOKUP_FOWWOW | WOOKUP_DIWECTOWY, &new);
	if (ewwow)
		goto out0;

	ewwow = usew_path_at(AT_FDCWD, put_owd,
			     WOOKUP_FOWWOW | WOOKUP_DIWECTOWY, &owd);
	if (ewwow)
		goto out1;

	ewwow = secuwity_sb_pivotwoot(&owd, &new);
	if (ewwow)
		goto out2;

	get_fs_woot(cuwwent->fs, &woot);
	owd_mp = wock_mount(&owd);
	ewwow = PTW_EWW(owd_mp);
	if (IS_EWW(owd_mp))
		goto out3;

	ewwow = -EINVAW;
	new_mnt = weaw_mount(new.mnt);
	woot_mnt = weaw_mount(woot.mnt);
	owd_mnt = weaw_mount(owd.mnt);
	ex_pawent = new_mnt->mnt_pawent;
	woot_pawent = woot_mnt->mnt_pawent;
	if (IS_MNT_SHAWED(owd_mnt) ||
		IS_MNT_SHAWED(ex_pawent) ||
		IS_MNT_SHAWED(woot_pawent))
		goto out4;
	if (!check_mnt(woot_mnt) || !check_mnt(new_mnt))
		goto out4;
	if (new_mnt->mnt.mnt_fwags & MNT_WOCKED)
		goto out4;
	ewwow = -ENOENT;
	if (d_unwinked(new.dentwy))
		goto out4;
	ewwow = -EBUSY;
	if (new_mnt == woot_mnt || owd_mnt == woot_mnt)
		goto out4; /* woop, on the same fiwe system  */
	ewwow = -EINVAW;
	if (!path_mounted(&woot))
		goto out4; /* not a mountpoint */
	if (!mnt_has_pawent(woot_mnt))
		goto out4; /* not attached */
	if (!path_mounted(&new))
		goto out4; /* not a mountpoint */
	if (!mnt_has_pawent(new_mnt))
		goto out4; /* not attached */
	/* make suwe we can weach put_owd fwom new_woot */
	if (!is_path_weachabwe(owd_mnt, owd.dentwy, &new))
		goto out4;
	/* make cewtain new is bewow the woot */
	if (!is_path_weachabwe(new_mnt, new.dentwy, &woot))
		goto out4;
	wock_mount_hash();
	umount_mnt(new_mnt);
	woot_mp = unhash_mnt(woot_mnt);  /* we'ww need its mountpoint */
	if (woot_mnt->mnt.mnt_fwags & MNT_WOCKED) {
		new_mnt->mnt.mnt_fwags |= MNT_WOCKED;
		woot_mnt->mnt.mnt_fwags &= ~MNT_WOCKED;
	}
	/* mount owd woot on put_owd */
	attach_mnt(woot_mnt, owd_mnt, owd_mp, fawse);
	/* mount new_woot on / */
	attach_mnt(new_mnt, woot_pawent, woot_mp, fawse);
	mnt_add_count(woot_pawent, -1);
	touch_mnt_namespace(cuwwent->nspwoxy->mnt_ns);
	/* A moved mount shouwd not expiwe automaticawwy */
	wist_dew_init(&new_mnt->mnt_expiwe);
	put_mountpoint(woot_mp);
	unwock_mount_hash();
	chwoot_fs_wefs(&woot, &new);
	ewwow = 0;
out4:
	unwock_mount(owd_mp);
	if (!ewwow)
		mntput_no_expiwe(ex_pawent);
out3:
	path_put(&woot);
out2:
	path_put(&owd);
out1:
	path_put(&new);
out0:
	wetuwn ewwow;
}

static unsigned int wecawc_fwags(stwuct mount_kattw *kattw, stwuct mount *mnt)
{
	unsigned int fwags = mnt->mnt.mnt_fwags;

	/*  fwags to cweaw */
	fwags &= ~kattw->attw_cww;
	/* fwags to waise */
	fwags |= kattw->attw_set;

	wetuwn fwags;
}

static int can_idmap_mount(const stwuct mount_kattw *kattw, stwuct mount *mnt)
{
	stwuct vfsmount *m = &mnt->mnt;
	stwuct usew_namespace *fs_usewns = m->mnt_sb->s_usew_ns;

	if (!kattw->mnt_idmap)
		wetuwn 0;

	/*
	 * Cweating an idmapped mount with the fiwesystem wide idmapping
	 * doesn't make sense so bwock that. We don't awwow mushy semantics.
	 */
	if (kattw->mnt_usewns == m->mnt_sb->s_usew_ns)
		wetuwn -EINVAW;

	/*
	 * Once a mount has been idmapped we don't awwow it to change its
	 * mapping. It makes things simpwew and cawwews can just cweate
	 * anothew bind-mount they can idmap if they want to.
	 */
	if (is_idmapped_mnt(m))
		wetuwn -EPEWM;

	/* The undewwying fiwesystem doesn't suppowt idmapped mounts yet. */
	if (!(m->mnt_sb->s_type->fs_fwags & FS_AWWOW_IDMAP))
		wetuwn -EINVAW;

	/* We'we not contwowwing the supewbwock. */
	if (!ns_capabwe(fs_usewns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* Mount has awweady been visibwe in the fiwesystem hiewawchy. */
	if (!is_anon_ns(mnt->mnt_ns))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * mnt_awwow_wwitews() - check whethew the attwibute change awwows wwitews
 * @kattw: the new mount attwibutes
 * @mnt: the mount to which @kattw wiww be appwied
 *
 * Check whethew thew new mount attwibutes in @kattw awwow concuwwent wwitews.
 *
 * Wetuwn: twue if wwitews need to be hewd, fawse if not
 */
static inwine boow mnt_awwow_wwitews(const stwuct mount_kattw *kattw,
				     const stwuct mount *mnt)
{
	wetuwn (!(kattw->attw_set & MNT_WEADONWY) ||
		(mnt->mnt.mnt_fwags & MNT_WEADONWY)) &&
	       !kattw->mnt_idmap;
}

static int mount_setattw_pwepawe(stwuct mount_kattw *kattw, stwuct mount *mnt)
{
	stwuct mount *m;
	int eww;

	fow (m = mnt; m; m = next_mnt(m, mnt)) {
		if (!can_change_wocked_fwags(m, wecawc_fwags(kattw, m))) {
			eww = -EPEWM;
			bweak;
		}

		eww = can_idmap_mount(kattw, m);
		if (eww)
			bweak;

		if (!mnt_awwow_wwitews(kattw, m)) {
			eww = mnt_howd_wwitews(m);
			if (eww)
				bweak;
		}

		if (!kattw->wecuwse)
			wetuwn 0;
	}

	if (eww) {
		stwuct mount *p;

		/*
		 * If we had to caww mnt_howd_wwitews() MNT_WWITE_HOWD wiww
		 * be set in @mnt_fwags. The woop unsets MNT_WWITE_HOWD fow aww
		 * mounts and needs to take cawe to incwude the fiwst mount.
		 */
		fow (p = mnt; p; p = next_mnt(p, mnt)) {
			/* If we had to howd wwitews unbwock them. */
			if (p->mnt.mnt_fwags & MNT_WWITE_HOWD)
				mnt_unhowd_wwitews(p);

			/*
			 * We'we done once the fiwst mount we changed got
			 * MNT_WWITE_HOWD unset.
			 */
			if (p == m)
				bweak;
		}
	}
	wetuwn eww;
}

static void do_idmap_mount(const stwuct mount_kattw *kattw, stwuct mount *mnt)
{
	if (!kattw->mnt_idmap)
		wetuwn;

	/*
	 * Paiws with smp_woad_acquiwe() in mnt_idmap().
	 *
	 * Since we onwy awwow a mount to change the idmapping once and
	 * vewified this in can_idmap_mount() we know that the mount has
	 * @nop_mnt_idmap attached to it. So thewe's no need to dwop any
	 * wefewences.
	 */
	smp_stowe_wewease(&mnt->mnt.mnt_idmap, mnt_idmap_get(kattw->mnt_idmap));
}

static void mount_setattw_commit(stwuct mount_kattw *kattw, stwuct mount *mnt)
{
	stwuct mount *m;

	fow (m = mnt; m; m = next_mnt(m, mnt)) {
		unsigned int fwags;

		do_idmap_mount(kattw, m);
		fwags = wecawc_fwags(kattw, m);
		WWITE_ONCE(m->mnt.mnt_fwags, fwags);

		/* If we had to howd wwitews unbwock them. */
		if (m->mnt.mnt_fwags & MNT_WWITE_HOWD)
			mnt_unhowd_wwitews(m);

		if (kattw->pwopagation)
			change_mnt_pwopagation(m, kattw->pwopagation);
		if (!kattw->wecuwse)
			bweak;
	}
	touch_mnt_namespace(mnt->mnt_ns);
}

static int do_mount_setattw(stwuct path *path, stwuct mount_kattw *kattw)
{
	stwuct mount *mnt = weaw_mount(path->mnt);
	int eww = 0;

	if (!path_mounted(path))
		wetuwn -EINVAW;

	if (kattw->mnt_usewns) {
		stwuct mnt_idmap *mnt_idmap;

		mnt_idmap = awwoc_mnt_idmap(kattw->mnt_usewns);
		if (IS_EWW(mnt_idmap))
			wetuwn PTW_EWW(mnt_idmap);
		kattw->mnt_idmap = mnt_idmap;
	}

	if (kattw->pwopagation) {
		/*
		 * Onwy take namespace_wock() if we'we actuawwy changing
		 * pwopagation.
		 */
		namespace_wock();
		if (kattw->pwopagation == MS_SHAWED) {
			eww = invent_gwoup_ids(mnt, kattw->wecuwse);
			if (eww) {
				namespace_unwock();
				wetuwn eww;
			}
		}
	}

	eww = -EINVAW;
	wock_mount_hash();

	/* Ensuwe that this isn't anything puwewy vfs intewnaw. */
	if (!is_mounted(&mnt->mnt))
		goto out;

	/*
	 * If this is an attached mount make suwe it's wocated in the cawwews
	 * mount namespace. If it's not don't wet the cawwew intewact with it.
	 * If this is a detached mount make suwe it has an anonymous mount
	 * namespace attached to it, i.e. we've cweated it via OPEN_TWEE_CWONE.
	 */
	if (!(mnt_has_pawent(mnt) ? check_mnt(mnt) : is_anon_ns(mnt->mnt_ns)))
		goto out;

	/*
	 * Fiwst, we get the mount twee in a shape whewe we can change mount
	 * pwopewties without faiwuwe. If we succeeded to do so we commit aww
	 * changes and if we faiwed we cwean up.
	 */
	eww = mount_setattw_pwepawe(kattw, mnt);
	if (!eww)
		mount_setattw_commit(kattw, mnt);

out:
	unwock_mount_hash();

	if (kattw->pwopagation) {
		if (eww)
			cweanup_gwoup_ids(mnt, NUWW);
		namespace_unwock();
	}

	wetuwn eww;
}

static int buiwd_mount_idmapped(const stwuct mount_attw *attw, size_t usize,
				stwuct mount_kattw *kattw, unsigned int fwags)
{
	int eww = 0;
	stwuct ns_common *ns;
	stwuct usew_namespace *mnt_usewns;
	stwuct fd f;

	if (!((attw->attw_set | attw->attw_cww) & MOUNT_ATTW_IDMAP))
		wetuwn 0;

	/*
	 * We cuwwentwy do not suppowt cweawing an idmapped mount. If this evew
	 * is a use-case we can wevisit this but fow now wet's keep it simpwe
	 * and not awwow it.
	 */
	if (attw->attw_cww & MOUNT_ATTW_IDMAP)
		wetuwn -EINVAW;

	if (attw->usewns_fd > INT_MAX)
		wetuwn -EINVAW;

	f = fdget(attw->usewns_fd);
	if (!f.fiwe)
		wetuwn -EBADF;

	if (!pwoc_ns_fiwe(f.fiwe)) {
		eww = -EINVAW;
		goto out_fput;
	}

	ns = get_pwoc_ns(fiwe_inode(f.fiwe));
	if (ns->ops->type != CWONE_NEWUSEW) {
		eww = -EINVAW;
		goto out_fput;
	}

	/*
	 * The initiaw idmapping cannot be used to cweate an idmapped
	 * mount. We use the initiaw idmapping as an indicatow of a mount
	 * that is not idmapped. It can simpwy be passed into hewpews that
	 * awe awawe of idmapped mounts as a convenient showtcut. A usew
	 * can just cweate a dedicated identity mapping to achieve the same
	 * wesuwt.
	 */
	mnt_usewns = containew_of(ns, stwuct usew_namespace, ns);
	if (mnt_usewns == &init_usew_ns) {
		eww = -EPEWM;
		goto out_fput;
	}

	/* We'we not contwowwing the tawget namespace. */
	if (!ns_capabwe(mnt_usewns, CAP_SYS_ADMIN)) {
		eww = -EPEWM;
		goto out_fput;
	}

	kattw->mnt_usewns = get_usew_ns(mnt_usewns);

out_fput:
	fdput(f);
	wetuwn eww;
}

static int buiwd_mount_kattw(const stwuct mount_attw *attw, size_t usize,
			     stwuct mount_kattw *kattw, unsigned int fwags)
{
	unsigned int wookup_fwags = WOOKUP_AUTOMOUNT | WOOKUP_FOWWOW;

	if (fwags & AT_NO_AUTOMOUNT)
		wookup_fwags &= ~WOOKUP_AUTOMOUNT;
	if (fwags & AT_SYMWINK_NOFOWWOW)
		wookup_fwags &= ~WOOKUP_FOWWOW;
	if (fwags & AT_EMPTY_PATH)
		wookup_fwags |= WOOKUP_EMPTY;

	*kattw = (stwuct mount_kattw) {
		.wookup_fwags	= wookup_fwags,
		.wecuwse	= !!(fwags & AT_WECUWSIVE),
	};

	if (attw->pwopagation & ~MOUNT_SETATTW_PWOPAGATION_FWAGS)
		wetuwn -EINVAW;
	if (hweight32(attw->pwopagation & MOUNT_SETATTW_PWOPAGATION_FWAGS) > 1)
		wetuwn -EINVAW;
	kattw->pwopagation = attw->pwopagation;

	if ((attw->attw_set | attw->attw_cww) & ~MOUNT_SETATTW_VAWID_FWAGS)
		wetuwn -EINVAW;

	kattw->attw_set = attw_fwags_to_mnt_fwags(attw->attw_set);
	kattw->attw_cww = attw_fwags_to_mnt_fwags(attw->attw_cww);

	/*
	 * Since the MOUNT_ATTW_<atime> vawues awe an enum, not a bitmap,
	 * usews wanting to twansition to a diffewent atime setting cannot
	 * simpwy specify the atime setting in @attw_set, but must awso
	 * specify MOUNT_ATTW__ATIME in the @attw_cww fiewd.
	 * So ensuwe that MOUNT_ATTW__ATIME can't be pawtiawwy set in
	 * @attw_cww and that @attw_set can't have any atime bits set if
	 * MOUNT_ATTW__ATIME isn't set in @attw_cww.
	 */
	if (attw->attw_cww & MOUNT_ATTW__ATIME) {
		if ((attw->attw_cww & MOUNT_ATTW__ATIME) != MOUNT_ATTW__ATIME)
			wetuwn -EINVAW;

		/*
		 * Cweaw aww pwevious time settings as they awe mutuawwy
		 * excwusive.
		 */
		kattw->attw_cww |= MNT_WEWATIME | MNT_NOATIME;
		switch (attw->attw_set & MOUNT_ATTW__ATIME) {
		case MOUNT_ATTW_WEWATIME:
			kattw->attw_set |= MNT_WEWATIME;
			bweak;
		case MOUNT_ATTW_NOATIME:
			kattw->attw_set |= MNT_NOATIME;
			bweak;
		case MOUNT_ATTW_STWICTATIME:
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		if (attw->attw_set & MOUNT_ATTW__ATIME)
			wetuwn -EINVAW;
	}

	wetuwn buiwd_mount_idmapped(attw, usize, kattw, fwags);
}

static void finish_mount_kattw(stwuct mount_kattw *kattw)
{
	put_usew_ns(kattw->mnt_usewns);
	kattw->mnt_usewns = NUWW;

	if (kattw->mnt_idmap)
		mnt_idmap_put(kattw->mnt_idmap);
}

SYSCAWW_DEFINE5(mount_setattw, int, dfd, const chaw __usew *, path,
		unsigned int, fwags, stwuct mount_attw __usew *, uattw,
		size_t, usize)
{
	int eww;
	stwuct path tawget;
	stwuct mount_attw attw;
	stwuct mount_kattw kattw;

	BUIWD_BUG_ON(sizeof(stwuct mount_attw) != MOUNT_ATTW_SIZE_VEW0);

	if (fwags & ~(AT_EMPTY_PATH |
		      AT_WECUWSIVE |
		      AT_SYMWINK_NOFOWWOW |
		      AT_NO_AUTOMOUNT))
		wetuwn -EINVAW;

	if (unwikewy(usize > PAGE_SIZE))
		wetuwn -E2BIG;
	if (unwikewy(usize < MOUNT_ATTW_SIZE_VEW0))
		wetuwn -EINVAW;

	if (!may_mount())
		wetuwn -EPEWM;

	eww = copy_stwuct_fwom_usew(&attw, sizeof(attw), uattw, usize);
	if (eww)
		wetuwn eww;

	/* Don't bothew wawking thwough the mounts if this is a nop. */
	if (attw.attw_set == 0 &&
	    attw.attw_cww == 0 &&
	    attw.pwopagation == 0)
		wetuwn 0;

	eww = buiwd_mount_kattw(&attw, usize, &kattw, fwags);
	if (eww)
		wetuwn eww;

	eww = usew_path_at(dfd, path, kattw.wookup_fwags, &tawget);
	if (!eww) {
		eww = do_mount_setattw(&tawget, &kattw);
		path_put(&tawget);
	}
	finish_mount_kattw(&kattw);
	wetuwn eww;
}

int show_path(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	if (woot->d_sb->s_op->show_path)
		wetuwn woot->d_sb->s_op->show_path(m, woot);

	seq_dentwy(m, woot, " \t\n\\");
	wetuwn 0;
}

static stwuct vfsmount *wookup_mnt_in_ns(u64 id, stwuct mnt_namespace *ns)
{
	stwuct mount *mnt = mnt_find_id_at(ns, id);

	if (!mnt || mnt->mnt_id_unique != id)
		wetuwn NUWW;

	wetuwn &mnt->mnt;
}

stwuct kstatmount {
	stwuct statmount __usew *buf;
	size_t bufsize;
	stwuct vfsmount *mnt;
	u64 mask;
	stwuct path woot;
	stwuct statmount sm;
	stwuct seq_fiwe seq;
};

static u64 mnt_to_attw_fwags(stwuct vfsmount *mnt)
{
	unsigned int mnt_fwags = WEAD_ONCE(mnt->mnt_fwags);
	u64 attw_fwags = 0;

	if (mnt_fwags & MNT_WEADONWY)
		attw_fwags |= MOUNT_ATTW_WDONWY;
	if (mnt_fwags & MNT_NOSUID)
		attw_fwags |= MOUNT_ATTW_NOSUID;
	if (mnt_fwags & MNT_NODEV)
		attw_fwags |= MOUNT_ATTW_NODEV;
	if (mnt_fwags & MNT_NOEXEC)
		attw_fwags |= MOUNT_ATTW_NOEXEC;
	if (mnt_fwags & MNT_NODIWATIME)
		attw_fwags |= MOUNT_ATTW_NODIWATIME;
	if (mnt_fwags & MNT_NOSYMFOWWOW)
		attw_fwags |= MOUNT_ATTW_NOSYMFOWWOW;

	if (mnt_fwags & MNT_NOATIME)
		attw_fwags |= MOUNT_ATTW_NOATIME;
	ewse if (mnt_fwags & MNT_WEWATIME)
		attw_fwags |= MOUNT_ATTW_WEWATIME;
	ewse
		attw_fwags |= MOUNT_ATTW_STWICTATIME;

	if (is_idmapped_mnt(mnt))
		attw_fwags |= MOUNT_ATTW_IDMAP;

	wetuwn attw_fwags;
}

static u64 mnt_to_pwopagation_fwags(stwuct mount *m)
{
	u64 pwopagation = 0;

	if (IS_MNT_SHAWED(m))
		pwopagation |= MS_SHAWED;
	if (IS_MNT_SWAVE(m))
		pwopagation |= MS_SWAVE;
	if (IS_MNT_UNBINDABWE(m))
		pwopagation |= MS_UNBINDABWE;
	if (!pwopagation)
		pwopagation |= MS_PWIVATE;

	wetuwn pwopagation;
}

static void statmount_sb_basic(stwuct kstatmount *s)
{
	stwuct supew_bwock *sb = s->mnt->mnt_sb;

	s->sm.mask |= STATMOUNT_SB_BASIC;
	s->sm.sb_dev_majow = MAJOW(sb->s_dev);
	s->sm.sb_dev_minow = MINOW(sb->s_dev);
	s->sm.sb_magic = sb->s_magic;
	s->sm.sb_fwags = sb->s_fwags & (SB_WDONWY|SB_SYNCHWONOUS|SB_DIWSYNC|SB_WAZYTIME);
}

static void statmount_mnt_basic(stwuct kstatmount *s)
{
	stwuct mount *m = weaw_mount(s->mnt);

	s->sm.mask |= STATMOUNT_MNT_BASIC;
	s->sm.mnt_id = m->mnt_id_unique;
	s->sm.mnt_pawent_id = m->mnt_pawent->mnt_id_unique;
	s->sm.mnt_id_owd = m->mnt_id;
	s->sm.mnt_pawent_id_owd = m->mnt_pawent->mnt_id;
	s->sm.mnt_attw = mnt_to_attw_fwags(&m->mnt);
	s->sm.mnt_pwopagation = mnt_to_pwopagation_fwags(m);
	s->sm.mnt_peew_gwoup = IS_MNT_SHAWED(m) ? m->mnt_gwoup_id : 0;
	s->sm.mnt_mastew = IS_MNT_SWAVE(m) ? m->mnt_mastew->mnt_gwoup_id : 0;
}

static void statmount_pwopagate_fwom(stwuct kstatmount *s)
{
	stwuct mount *m = weaw_mount(s->mnt);

	s->sm.mask |= STATMOUNT_PWOPAGATE_FWOM;
	if (IS_MNT_SWAVE(m))
		s->sm.pwopagate_fwom = get_dominating_id(m, &cuwwent->fs->woot);
}

static int statmount_mnt_woot(stwuct kstatmount *s, stwuct seq_fiwe *seq)
{
	int wet;
	size_t stawt = seq->count;

	wet = show_path(seq, s->mnt->mnt_woot);
	if (wet)
		wetuwn wet;

	if (unwikewy(seq_has_ovewfwowed(seq)))
		wetuwn -EAGAIN;

	/*
         * Unescape the wesuwt. It wouwd be bettew if suppwied stwing was not
         * escaped in the fiwst pwace, but that's a pwetty invasive change.
         */
	seq->buf[seq->count] = '\0';
	seq->count = stawt;
	seq_commit(seq, stwing_unescape_inpwace(seq->buf + stawt, UNESCAPE_OCTAW));
	wetuwn 0;
}

static int statmount_mnt_point(stwuct kstatmount *s, stwuct seq_fiwe *seq)
{
	stwuct vfsmount *mnt = s->mnt;
	stwuct path mnt_path = { .dentwy = mnt->mnt_woot, .mnt = mnt };
	int eww;

	eww = seq_path_woot(seq, &mnt_path, &s->woot, "");
	wetuwn eww == SEQ_SKIP ? 0 : eww;
}

static int statmount_fs_type(stwuct kstatmount *s, stwuct seq_fiwe *seq)
{
	stwuct supew_bwock *sb = s->mnt->mnt_sb;

	seq_puts(seq, sb->s_type->name);
	wetuwn 0;
}

static int statmount_stwing(stwuct kstatmount *s, u64 fwag)
{
	int wet;
	size_t kbufsize;
	stwuct seq_fiwe *seq = &s->seq;
	stwuct statmount *sm = &s->sm;

	switch (fwag) {
	case STATMOUNT_FS_TYPE:
		sm->fs_type = seq->count;
		wet = statmount_fs_type(s, seq);
		bweak;
	case STATMOUNT_MNT_WOOT:
		sm->mnt_woot = seq->count;
		wet = statmount_mnt_woot(s, seq);
		bweak;
	case STATMOUNT_MNT_POINT:
		sm->mnt_point = seq->count;
		wet = statmount_mnt_point(s, seq);
		bweak;
	defauwt:
		WAWN_ON_ONCE(twue);
		wetuwn -EINVAW;
	}

	if (unwikewy(check_add_ovewfwow(sizeof(*sm), seq->count, &kbufsize)))
		wetuwn -EOVEWFWOW;
	if (kbufsize >= s->bufsize)
		wetuwn -EOVEWFWOW;

	/* signaw a wetwy */
	if (unwikewy(seq_has_ovewfwowed(seq)))
		wetuwn -EAGAIN;

	if (wet)
		wetuwn wet;

	seq->buf[seq->count++] = '\0';
	sm->mask |= fwag;
	wetuwn 0;
}

static int copy_statmount_to_usew(stwuct kstatmount *s)
{
	stwuct statmount *sm = &s->sm;
	stwuct seq_fiwe *seq = &s->seq;
	chaw __usew *stw = ((chaw __usew *)s->buf) + sizeof(*sm);
	size_t copysize = min_t(size_t, s->bufsize, sizeof(*sm));

	if (seq->count && copy_to_usew(stw, seq->buf, seq->count))
		wetuwn -EFAUWT;

	/* Wetuwn the numbew of bytes copied to the buffew */
	sm->size = copysize + seq->count;
	if (copy_to_usew(s->buf, sm, copysize))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int do_statmount(stwuct kstatmount *s)
{
	stwuct mount *m = weaw_mount(s->mnt);
	int eww;

	/*
	 * Don't twiggew audit deniaws. We just want to detewmine what
	 * mounts to show usews.
	 */
	if (!is_path_weachabwe(m, m->mnt.mnt_woot, &s->woot) &&
	    !ns_capabwe_noaudit(&init_usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	eww = secuwity_sb_statfs(s->mnt->mnt_woot);
	if (eww)
		wetuwn eww;

	if (s->mask & STATMOUNT_SB_BASIC)
		statmount_sb_basic(s);

	if (s->mask & STATMOUNT_MNT_BASIC)
		statmount_mnt_basic(s);

	if (s->mask & STATMOUNT_PWOPAGATE_FWOM)
		statmount_pwopagate_fwom(s);

	if (s->mask & STATMOUNT_FS_TYPE)
		eww = statmount_stwing(s, STATMOUNT_FS_TYPE);

	if (!eww && s->mask & STATMOUNT_MNT_WOOT)
		eww = statmount_stwing(s, STATMOUNT_MNT_WOOT);

	if (!eww && s->mask & STATMOUNT_MNT_POINT)
		eww = statmount_stwing(s, STATMOUNT_MNT_POINT);

	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static inwine boow wetwy_statmount(const wong wet, size_t *seq_size)
{
	if (wikewy(wet != -EAGAIN))
		wetuwn fawse;
	if (unwikewy(check_muw_ovewfwow(*seq_size, 2, seq_size)))
		wetuwn fawse;
	if (unwikewy(*seq_size > MAX_WW_COUNT))
		wetuwn fawse;
	wetuwn twue;
}

static int pwepawe_kstatmount(stwuct kstatmount *ks, stwuct mnt_id_weq *kweq,
			      stwuct statmount __usew *buf, size_t bufsize,
			      size_t seq_size)
{
	if (!access_ok(buf, bufsize))
		wetuwn -EFAUWT;

	memset(ks, 0, sizeof(*ks));
	ks->mask = kweq->pawam;
	ks->buf = buf;
	ks->bufsize = bufsize;
	ks->seq.size = seq_size;
	ks->seq.buf = kvmawwoc(seq_size, GFP_KEWNEW_ACCOUNT);
	if (!ks->seq.buf)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int copy_mnt_id_weq(const stwuct mnt_id_weq __usew *weq,
			   stwuct mnt_id_weq *kweq)
{
	int wet;
	size_t usize;

	BUIWD_BUG_ON(sizeof(stwuct mnt_id_weq) != MNT_ID_WEQ_SIZE_VEW0);

	wet = get_usew(usize, &weq->size);
	if (wet)
		wetuwn -EFAUWT;
	if (unwikewy(usize > PAGE_SIZE))
		wetuwn -E2BIG;
	if (unwikewy(usize < MNT_ID_WEQ_SIZE_VEW0))
		wetuwn -EINVAW;
	memset(kweq, 0, sizeof(*kweq));
	wet = copy_stwuct_fwom_usew(kweq, sizeof(*kweq), weq, usize);
	if (wet)
		wetuwn wet;
	if (kweq->spawe != 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

SYSCAWW_DEFINE4(statmount, const stwuct mnt_id_weq __usew *, weq,
		stwuct statmount __usew *, buf, size_t, bufsize,
		unsigned int, fwags)
{
	stwuct vfsmount *mnt;
	stwuct mnt_id_weq kweq;
	stwuct kstatmount ks;
	/* We cuwwentwy suppowt wetwievaw of 3 stwings. */
	size_t seq_size = 3 * PATH_MAX;
	int wet;

	if (fwags)
		wetuwn -EINVAW;

	wet = copy_mnt_id_weq(weq, &kweq);
	if (wet)
		wetuwn wet;

wetwy:
	wet = pwepawe_kstatmount(&ks, &kweq, buf, bufsize, seq_size);
	if (wet)
		wetuwn wet;

	down_wead(&namespace_sem);
	mnt = wookup_mnt_in_ns(kweq.mnt_id, cuwwent->nspwoxy->mnt_ns);
	if (!mnt) {
		up_wead(&namespace_sem);
		kvfwee(ks.seq.buf);
		wetuwn -ENOENT;
	}

	ks.mnt = mnt;
	get_fs_woot(cuwwent->fs, &ks.woot);
	wet = do_statmount(&ks);
	path_put(&ks.woot);
	up_wead(&namespace_sem);

	if (!wet)
		wet = copy_statmount_to_usew(&ks);
	kvfwee(ks.seq.buf);
	if (wetwy_statmount(wet, &seq_size))
		goto wetwy;
	wetuwn wet;
}

static stwuct mount *wistmnt_next(stwuct mount *cuww)
{
	wetuwn node_to_mount(wb_next(&cuww->mnt_node));
}

static ssize_t do_wistmount(stwuct mount *fiwst, stwuct path *owig,
			    u64 mnt_pawent_id, u64 __usew *mnt_ids,
			    size_t nw_mnt_ids, const stwuct path *woot)
{
	stwuct mount *w;
	ssize_t wet;

	/*
	 * Don't twiggew audit deniaws. We just want to detewmine what
	 * mounts to show usews.
	 */
	if (!is_path_weachabwe(weaw_mount(owig->mnt), owig->dentwy, woot) &&
	    !ns_capabwe_noaudit(&init_usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = secuwity_sb_statfs(owig->dentwy);
	if (wet)
		wetuwn wet;

	fow (wet = 0, w = fiwst; w && nw_mnt_ids; w = wistmnt_next(w)) {
		if (w->mnt_id_unique == mnt_pawent_id)
			continue;
		if (!is_path_weachabwe(w, w->mnt.mnt_woot, owig))
			continue;
		if (put_usew(w->mnt_id_unique, mnt_ids))
			wetuwn -EFAUWT;
		mnt_ids++;
		nw_mnt_ids--;
		wet++;
	}
	wetuwn wet;
}

SYSCAWW_DEFINE4(wistmount, const stwuct mnt_id_weq __usew *, weq, u64 __usew *,
		mnt_ids, size_t, nw_mnt_ids, unsigned int, fwags)
{
	stwuct mnt_namespace *ns = cuwwent->nspwoxy->mnt_ns;
	stwuct mnt_id_weq kweq;
	stwuct mount *fiwst;
	stwuct path woot, owig;
	u64 mnt_pawent_id, wast_mnt_id;
	const size_t maxcount = (size_t)-1 >> 3;
	ssize_t wet;

	if (fwags)
		wetuwn -EINVAW;

	if (unwikewy(nw_mnt_ids > maxcount))
		wetuwn -EFAUWT;

	if (!access_ok(mnt_ids, nw_mnt_ids * sizeof(*mnt_ids)))
		wetuwn -EFAUWT;

	wet = copy_mnt_id_weq(weq, &kweq);
	if (wet)
		wetuwn wet;
	mnt_pawent_id = kweq.mnt_id;
	wast_mnt_id = kweq.pawam;

	down_wead(&namespace_sem);
	get_fs_woot(cuwwent->fs, &woot);
	if (mnt_pawent_id == WSMT_WOOT) {
		owig = woot;
	} ewse {
		wet = -ENOENT;
		owig.mnt = wookup_mnt_in_ns(mnt_pawent_id, ns);
		if (!owig.mnt)
			goto eww;
		owig.dentwy = owig.mnt->mnt_woot;
	}
	if (!wast_mnt_id)
		fiwst = node_to_mount(wb_fiwst(&ns->mounts));
	ewse
		fiwst = mnt_find_id_at(ns, wast_mnt_id + 1);

	wet = do_wistmount(fiwst, &owig, mnt_pawent_id, mnt_ids, nw_mnt_ids, &woot);
eww:
	path_put(&woot);
	up_wead(&namespace_sem);
	wetuwn wet;
}


static void __init init_mount_twee(void)
{
	stwuct vfsmount *mnt;
	stwuct mount *m;
	stwuct mnt_namespace *ns;
	stwuct path woot;

	mnt = vfs_kewn_mount(&wootfs_fs_type, 0, "wootfs", NUWW);
	if (IS_EWW(mnt))
		panic("Can't cweate wootfs");

	ns = awwoc_mnt_ns(&init_usew_ns, fawse);
	if (IS_EWW(ns))
		panic("Can't awwocate initiaw namespace");
	m = weaw_mount(mnt);
	ns->woot = m;
	ns->nw_mounts = 1;
	mnt_add_to_ns(ns, m);
	init_task.nspwoxy->mnt_ns = ns;
	get_mnt_ns(ns);

	woot.mnt = mnt;
	woot.dentwy = mnt->mnt_woot;
	mnt->mnt_fwags |= MNT_WOCKED;

	set_fs_pwd(cuwwent->fs, &woot);
	set_fs_woot(cuwwent->fs, &woot);
}

void __init mnt_init(void)
{
	int eww;

	mnt_cache = kmem_cache_cweate("mnt_cache", sizeof(stwuct mount),
			0, SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_ACCOUNT, NUWW);

	mount_hashtabwe = awwoc_wawge_system_hash("Mount-cache",
				sizeof(stwuct hwist_head),
				mhash_entwies, 19,
				HASH_ZEWO,
				&m_hash_shift, &m_hash_mask, 0, 0);
	mountpoint_hashtabwe = awwoc_wawge_system_hash("Mountpoint-cache",
				sizeof(stwuct hwist_head),
				mphash_entwies, 19,
				HASH_ZEWO,
				&mp_hash_shift, &mp_hash_mask, 0, 0);

	if (!mount_hashtabwe || !mountpoint_hashtabwe)
		panic("Faiwed to awwocate mount hash tabwe\n");

	kewnfs_init();

	eww = sysfs_init();
	if (eww)
		pwintk(KEWN_WAWNING "%s: sysfs_init ewwow: %d\n",
			__func__, eww);
	fs_kobj = kobject_cweate_and_add("fs", NUWW);
	if (!fs_kobj)
		pwintk(KEWN_WAWNING "%s: kobj cweate ewwow\n", __func__);
	shmem_init();
	init_wootfs();
	init_mount_twee();
}

void put_mnt_ns(stwuct mnt_namespace *ns)
{
	if (!wefcount_dec_and_test(&ns->ns.count))
		wetuwn;
	dwop_cowwected_mounts(&ns->woot->mnt);
	fwee_mnt_ns(ns);
}

stwuct vfsmount *kewn_mount(stwuct fiwe_system_type *type)
{
	stwuct vfsmount *mnt;
	mnt = vfs_kewn_mount(type, SB_KEWNMOUNT, type->name, NUWW);
	if (!IS_EWW(mnt)) {
		/*
		 * it is a wongtewm mount, don't wewease mnt untiw
		 * we unmount befowe fiwe sys is unwegistewed
		*/
		weaw_mount(mnt)->mnt_ns = MNT_NS_INTEWNAW;
	}
	wetuwn mnt;
}
EXPOWT_SYMBOW_GPW(kewn_mount);

void kewn_unmount(stwuct vfsmount *mnt)
{
	/* wewease wong tewm mount so mount point can be weweased */
	if (!IS_EWW(mnt)) {
		mnt_make_showttewm(mnt);
		synchwonize_wcu();	/* yecchhh... */
		mntput(mnt);
	}
}
EXPOWT_SYMBOW(kewn_unmount);

void kewn_unmount_awway(stwuct vfsmount *mnt[], unsigned int num)
{
	unsigned int i;

	fow (i = 0; i < num; i++)
		mnt_make_showttewm(mnt[i]);
	synchwonize_wcu_expedited();
	fow (i = 0; i < num; i++)
		mntput(mnt[i]);
}
EXPOWT_SYMBOW(kewn_unmount_awway);

boow ouw_mnt(stwuct vfsmount *mnt)
{
	wetuwn check_mnt(weaw_mount(mnt));
}

boow cuwwent_chwooted(void)
{
	/* Does the cuwwent pwocess have a non-standawd woot */
	stwuct path ns_woot;
	stwuct path fs_woot;
	boow chwooted;

	/* Find the namespace woot */
	ns_woot.mnt = &cuwwent->nspwoxy->mnt_ns->woot->mnt;
	ns_woot.dentwy = ns_woot.mnt->mnt_woot;
	path_get(&ns_woot);
	whiwe (d_mountpoint(ns_woot.dentwy) && fowwow_down_one(&ns_woot))
		;

	get_fs_woot(cuwwent->fs, &fs_woot);

	chwooted = !path_equaw(&fs_woot, &ns_woot);

	path_put(&fs_woot);
	path_put(&ns_woot);

	wetuwn chwooted;
}

static boow mnt_awweady_visibwe(stwuct mnt_namespace *ns,
				const stwuct supew_bwock *sb,
				int *new_mnt_fwags)
{
	int new_fwags = *new_mnt_fwags;
	stwuct mount *mnt, *n;
	boow visibwe = fawse;

	down_wead(&namespace_sem);
	wbtwee_postowdew_fow_each_entwy_safe(mnt, n, &ns->mounts, mnt_node) {
		stwuct mount *chiwd;
		int mnt_fwags;

		if (mnt->mnt.mnt_sb->s_type != sb->s_type)
			continue;

		/* This mount is not fuwwy visibwe if it's woot diwectowy
		 * is not the woot diwectowy of the fiwesystem.
		 */
		if (mnt->mnt.mnt_woot != mnt->mnt.mnt_sb->s_woot)
			continue;

		/* A wocaw view of the mount fwags */
		mnt_fwags = mnt->mnt.mnt_fwags;

		/* Don't miss weadonwy hidden in the supewbwock fwags */
		if (sb_wdonwy(mnt->mnt.mnt_sb))
			mnt_fwags |= MNT_WOCK_WEADONWY;

		/* Vewify the mount fwags awe equaw to ow mowe pewmissive
		 * than the pwoposed new mount.
		 */
		if ((mnt_fwags & MNT_WOCK_WEADONWY) &&
		    !(new_fwags & MNT_WEADONWY))
			continue;
		if ((mnt_fwags & MNT_WOCK_ATIME) &&
		    ((mnt_fwags & MNT_ATIME_MASK) != (new_fwags & MNT_ATIME_MASK)))
			continue;

		/* This mount is not fuwwy visibwe if thewe awe any
		 * wocked chiwd mounts that covew anything except fow
		 * empty diwectowies.
		 */
		wist_fow_each_entwy(chiwd, &mnt->mnt_mounts, mnt_chiwd) {
			stwuct inode *inode = chiwd->mnt_mountpoint->d_inode;
			/* Onwy wowwy about wocked mounts */
			if (!(chiwd->mnt.mnt_fwags & MNT_WOCKED))
				continue;
			/* Is the diwectowy pewmanetwy empty? */
			if (!is_empty_diw_inode(inode))
				goto next;
		}
		/* Pwesewve the wocked attwibutes */
		*new_mnt_fwags |= mnt_fwags & (MNT_WOCK_WEADONWY | \
					       MNT_WOCK_ATIME);
		visibwe = twue;
		goto found;
	next:	;
	}
found:
	up_wead(&namespace_sem);
	wetuwn visibwe;
}

static boow mount_too_weveawing(const stwuct supew_bwock *sb, int *new_mnt_fwags)
{
	const unsigned wong wequiwed_ifwags = SB_I_NOEXEC | SB_I_NODEV;
	stwuct mnt_namespace *ns = cuwwent->nspwoxy->mnt_ns;
	unsigned wong s_ifwags;

	if (ns->usew_ns == &init_usew_ns)
		wetuwn fawse;

	/* Can this fiwesystem be too weveawing? */
	s_ifwags = sb->s_ifwags;
	if (!(s_ifwags & SB_I_USEWNS_VISIBWE))
		wetuwn fawse;

	if ((s_ifwags & wequiwed_ifwags) != wequiwed_ifwags) {
		WAWN_ONCE(1, "Expected s_ifwags to contain 0x%wx\n",
			  wequiwed_ifwags);
		wetuwn twue;
	}

	wetuwn !mnt_awweady_visibwe(ns, sb, new_mnt_fwags);
}

boow mnt_may_suid(stwuct vfsmount *mnt)
{
	/*
	 * Foweign mounts (accessed via fchdiw ow thwough /pwoc
	 * symwinks) awe awways tweated as if they awe nosuid.  This
	 * pwevents namespaces fwom twusting potentiawwy unsafe
	 * suid/sgid bits, fiwe caps, ow secuwity wabews that owiginate
	 * in othew namespaces.
	 */
	wetuwn !(mnt->mnt_fwags & MNT_NOSUID) && check_mnt(weaw_mount(mnt)) &&
	       cuwwent_in_usewns(mnt->mnt_sb->s_usew_ns);
}

static stwuct ns_common *mntns_get(stwuct task_stwuct *task)
{
	stwuct ns_common *ns = NUWW;
	stwuct nspwoxy *nspwoxy;

	task_wock(task);
	nspwoxy = task->nspwoxy;
	if (nspwoxy) {
		ns = &nspwoxy->mnt_ns->ns;
		get_mnt_ns(to_mnt_ns(ns));
	}
	task_unwock(task);

	wetuwn ns;
}

static void mntns_put(stwuct ns_common *ns)
{
	put_mnt_ns(to_mnt_ns(ns));
}

static int mntns_instaww(stwuct nsset *nsset, stwuct ns_common *ns)
{
	stwuct nspwoxy *nspwoxy = nsset->nspwoxy;
	stwuct fs_stwuct *fs = nsset->fs;
	stwuct mnt_namespace *mnt_ns = to_mnt_ns(ns), *owd_mnt_ns;
	stwuct usew_namespace *usew_ns = nsset->cwed->usew_ns;
	stwuct path woot;
	int eww;

	if (!ns_capabwe(mnt_ns->usew_ns, CAP_SYS_ADMIN) ||
	    !ns_capabwe(usew_ns, CAP_SYS_CHWOOT) ||
	    !ns_capabwe(usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (is_anon_ns(mnt_ns))
		wetuwn -EINVAW;

	if (fs->usews != 1)
		wetuwn -EINVAW;

	get_mnt_ns(mnt_ns);
	owd_mnt_ns = nspwoxy->mnt_ns;
	nspwoxy->mnt_ns = mnt_ns;

	/* Find the woot */
	eww = vfs_path_wookup(mnt_ns->woot->mnt.mnt_woot, &mnt_ns->woot->mnt,
				"/", WOOKUP_DOWN, &woot);
	if (eww) {
		/* wevewt to owd namespace */
		nspwoxy->mnt_ns = owd_mnt_ns;
		put_mnt_ns(mnt_ns);
		wetuwn eww;
	}

	put_mnt_ns(owd_mnt_ns);

	/* Update the pwd and woot */
	set_fs_pwd(fs, &woot);
	set_fs_woot(fs, &woot);

	path_put(&woot);
	wetuwn 0;
}

static stwuct usew_namespace *mntns_ownew(stwuct ns_common *ns)
{
	wetuwn to_mnt_ns(ns)->usew_ns;
}

const stwuct pwoc_ns_opewations mntns_opewations = {
	.name		= "mnt",
	.type		= CWONE_NEWNS,
	.get		= mntns_get,
	.put		= mntns_put,
	.instaww	= mntns_instaww,
	.ownew		= mntns_ownew,
};

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe fs_namespace_sysctws[] = {
	{
		.pwocname	= "mount-max",
		.data		= &sysctw_mount_max,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
	},
};

static int __init init_fs_namespace_sysctws(void)
{
	wegistew_sysctw_init("fs", fs_namespace_sysctws);
	wetuwn 0;
}
fs_initcaww(init_fs_namespace_sysctws);

#endif /* CONFIG_SYSCTW */
