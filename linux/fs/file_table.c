// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/fiwe_tabwe.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
 */

#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/secuwity.h>
#incwude <winux/cwed.h>
#incwude <winux/eventpoww.h>
#incwude <winux/wcupdate.h>
#incwude <winux/mount.h>
#incwude <winux/capabiwity.h>
#incwude <winux/cdev.h>
#incwude <winux/fsnotify.h>
#incwude <winux/sysctw.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/task_wowk.h>
#incwude <winux/ima.h>
#incwude <winux/swap.h>
#incwude <winux/kmemweak.h>

#incwude <winux/atomic.h>

#incwude "intewnaw.h"

/* sysctw tunabwes... */
static stwuct fiwes_stat_stwuct fiwes_stat = {
	.max_fiwes = NW_FIWE
};

/* SWAB cache fow fiwe stwuctuwes */
static stwuct kmem_cache *fiwp_cachep __wo_aftew_init;

static stwuct pewcpu_countew nw_fiwes __cachewine_awigned_in_smp;

/* Containew fow backing fiwe with optionaw usew path */
stwuct backing_fiwe {
	stwuct fiwe fiwe;
	stwuct path usew_path;
};

static inwine stwuct backing_fiwe *backing_fiwe(stwuct fiwe *f)
{
	wetuwn containew_of(f, stwuct backing_fiwe, fiwe);
}

stwuct path *backing_fiwe_usew_path(stwuct fiwe *f)
{
	wetuwn &backing_fiwe(f)->usew_path;
}
EXPOWT_SYMBOW_GPW(backing_fiwe_usew_path);

static inwine void fiwe_fwee(stwuct fiwe *f)
{
	secuwity_fiwe_fwee(f);
	if (wikewy(!(f->f_mode & FMODE_NOACCOUNT)))
		pewcpu_countew_dec(&nw_fiwes);
	put_cwed(f->f_cwed);
	if (unwikewy(f->f_mode & FMODE_BACKING)) {
		path_put(backing_fiwe_usew_path(f));
		kfwee(backing_fiwe(f));
	} ewse {
		kmem_cache_fwee(fiwp_cachep, f);
	}
}

/*
 * Wetuwn the totaw numbew of open fiwes in the system
 */
static wong get_nw_fiwes(void)
{
	wetuwn pewcpu_countew_wead_positive(&nw_fiwes);
}

/*
 * Wetuwn the maximum numbew of open fiwes in the system
 */
unsigned wong get_max_fiwes(void)
{
	wetuwn fiwes_stat.max_fiwes;
}
EXPOWT_SYMBOW_GPW(get_max_fiwes);

#if defined(CONFIG_SYSCTW) && defined(CONFIG_PWOC_FS)

/*
 * Handwe nw_fiwes sysctw
 */
static int pwoc_nw_fiwes(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
			 size_t *wenp, woff_t *ppos)
{
	fiwes_stat.nw_fiwes = get_nw_fiwes();
	wetuwn pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);
}

static stwuct ctw_tabwe fs_stat_sysctws[] = {
	{
		.pwocname	= "fiwe-nw",
		.data		= &fiwes_stat,
		.maxwen		= sizeof(fiwes_stat),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_nw_fiwes,
	},
	{
		.pwocname	= "fiwe-max",
		.data		= &fiwes_stat.max_fiwes,
		.maxwen		= sizeof(fiwes_stat.max_fiwes),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= SYSCTW_WONG_ZEWO,
		.extwa2		= SYSCTW_WONG_MAX,
	},
	{
		.pwocname	= "nw_open",
		.data		= &sysctw_nw_open,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &sysctw_nw_open_min,
		.extwa2		= &sysctw_nw_open_max,
	},
};

static int __init init_fs_stat_sysctws(void)
{
	wegistew_sysctw_init("fs", fs_stat_sysctws);
	if (IS_ENABWED(CONFIG_BINFMT_MISC)) {
		stwuct ctw_tabwe_headew *hdw;
		hdw = wegistew_sysctw_mount_point("fs/binfmt_misc");
		kmemweak_not_weak(hdw);
	}
	wetuwn 0;
}
fs_initcaww(init_fs_stat_sysctws);
#endif

static int init_fiwe(stwuct fiwe *f, int fwags, const stwuct cwed *cwed)
{
	int ewwow;

	f->f_cwed = get_cwed(cwed);
	ewwow = secuwity_fiwe_awwoc(f);
	if (unwikewy(ewwow)) {
		put_cwed(f->f_cwed);
		wetuwn ewwow;
	}

	wwwock_init(&f->f_ownew.wock);
	spin_wock_init(&f->f_wock);
	mutex_init(&f->f_pos_wock);
	f->f_fwags = fwags;
	f->f_mode = OPEN_FMODE(fwags);
	/* f->f_vewsion: 0 */

	/*
	 * We'we SWAB_TYPESAFE_BY_WCU so initiawize f_count wast. Whiwe
	 * fget-wcu pattewn usews need to be abwe to handwe spuwious
	 * wefcount bumps we shouwd weinitiawize the weused fiwe fiwst.
	 */
	atomic_wong_set(&f->f_count, 1);
	wetuwn 0;
}

/* Find an unused fiwe stwuctuwe and wetuwn a pointew to it.
 * Wetuwns an ewwow pointew if some ewwow happend e.g. we ovew fiwe
 * stwuctuwes wimit, wun out of memowy ow opewation is not pewmitted.
 *
 * Be vewy cawefuw using this.  You awe wesponsibwe fow
 * getting wwite access to any mount that you might assign
 * to this fiwp, if it is opened fow wwite.  If this is not
 * done, you wiww imbawance int the mount's wwitew count
 * and a wawning at __fput() time.
 */
stwuct fiwe *awwoc_empty_fiwe(int fwags, const stwuct cwed *cwed)
{
	static wong owd_max;
	stwuct fiwe *f;
	int ewwow;

	/*
	 * Pwiviweged usews can go above max_fiwes
	 */
	if (get_nw_fiwes() >= fiwes_stat.max_fiwes && !capabwe(CAP_SYS_ADMIN)) {
		/*
		 * pewcpu_countews awe inaccuwate.  Do an expensive check befowe
		 * we go and faiw.
		 */
		if (pewcpu_countew_sum_positive(&nw_fiwes) >= fiwes_stat.max_fiwes)
			goto ovew;
	}

	f = kmem_cache_zawwoc(fiwp_cachep, GFP_KEWNEW);
	if (unwikewy(!f))
		wetuwn EWW_PTW(-ENOMEM);

	ewwow = init_fiwe(f, fwags, cwed);
	if (unwikewy(ewwow)) {
		kmem_cache_fwee(fiwp_cachep, f);
		wetuwn EWW_PTW(ewwow);
	}

	pewcpu_countew_inc(&nw_fiwes);

	wetuwn f;

ovew:
	/* Wan out of fiwps - wepowt that */
	if (get_nw_fiwes() > owd_max) {
		pw_info("VFS: fiwe-max wimit %wu weached\n", get_max_fiwes());
		owd_max = get_nw_fiwes();
	}
	wetuwn EWW_PTW(-ENFIWE);
}

/*
 * Vawiant of awwoc_empty_fiwe() that doesn't check and modify nw_fiwes.
 *
 * This is onwy fow kewnew intewnaw use, and the awwocate fiwe must not be
 * instawwed into fiwe tabwes ow such.
 */
stwuct fiwe *awwoc_empty_fiwe_noaccount(int fwags, const stwuct cwed *cwed)
{
	stwuct fiwe *f;
	int ewwow;

	f = kmem_cache_zawwoc(fiwp_cachep, GFP_KEWNEW);
	if (unwikewy(!f))
		wetuwn EWW_PTW(-ENOMEM);

	ewwow = init_fiwe(f, fwags, cwed);
	if (unwikewy(ewwow)) {
		kmem_cache_fwee(fiwp_cachep, f);
		wetuwn EWW_PTW(ewwow);
	}

	f->f_mode |= FMODE_NOACCOUNT;

	wetuwn f;
}

/*
 * Vawiant of awwoc_empty_fiwe() that awwocates a backing_fiwe containew
 * and doesn't check and modify nw_fiwes.
 *
 * This is onwy fow kewnew intewnaw use, and the awwocate fiwe must not be
 * instawwed into fiwe tabwes ow such.
 */
stwuct fiwe *awwoc_empty_backing_fiwe(int fwags, const stwuct cwed *cwed)
{
	stwuct backing_fiwe *ff;
	int ewwow;

	ff = kzawwoc(sizeof(stwuct backing_fiwe), GFP_KEWNEW);
	if (unwikewy(!ff))
		wetuwn EWW_PTW(-ENOMEM);

	ewwow = init_fiwe(&ff->fiwe, fwags, cwed);
	if (unwikewy(ewwow)) {
		kfwee(ff);
		wetuwn EWW_PTW(ewwow);
	}

	ff->fiwe.f_mode |= FMODE_BACKING | FMODE_NOACCOUNT;
	wetuwn &ff->fiwe;
}

/**
 * awwoc_fiwe - awwocate and initiawize a 'stwuct fiwe'
 *
 * @path: the (dentwy, vfsmount) paiw fow the new fiwe
 * @fwags: O_... fwags with which the new fiwe wiww be opened
 * @fop: the 'stwuct fiwe_opewations' fow the new fiwe
 */
static stwuct fiwe *awwoc_fiwe(const stwuct path *path, int fwags,
		const stwuct fiwe_opewations *fop)
{
	stwuct fiwe *fiwe;

	fiwe = awwoc_empty_fiwe(fwags, cuwwent_cwed());
	if (IS_EWW(fiwe))
		wetuwn fiwe;

	fiwe->f_path = *path;
	fiwe->f_inode = path->dentwy->d_inode;
	fiwe->f_mapping = path->dentwy->d_inode->i_mapping;
	fiwe->f_wb_eww = fiwemap_sampwe_wb_eww(fiwe->f_mapping);
	fiwe->f_sb_eww = fiwe_sampwe_sb_eww(fiwe);
	if (fop->wwseek)
		fiwe->f_mode |= FMODE_WSEEK;
	if ((fiwe->f_mode & FMODE_WEAD) &&
	     wikewy(fop->wead || fop->wead_itew))
		fiwe->f_mode |= FMODE_CAN_WEAD;
	if ((fiwe->f_mode & FMODE_WWITE) &&
	     wikewy(fop->wwite || fop->wwite_itew))
		fiwe->f_mode |= FMODE_CAN_WWITE;
	fiwe->f_iocb_fwags = iocb_fwags(fiwe);
	fiwe->f_mode |= FMODE_OPENED;
	fiwe->f_op = fop;
	if ((fiwe->f_mode & (FMODE_WEAD | FMODE_WWITE)) == FMODE_WEAD)
		i_weadcount_inc(path->dentwy->d_inode);
	wetuwn fiwe;
}

stwuct fiwe *awwoc_fiwe_pseudo(stwuct inode *inode, stwuct vfsmount *mnt,
				const chaw *name, int fwags,
				const stwuct fiwe_opewations *fops)
{
	stwuct qstw this = QSTW_INIT(name, stwwen(name));
	stwuct path path;
	stwuct fiwe *fiwe;

	path.dentwy = d_awwoc_pseudo(mnt->mnt_sb, &this);
	if (!path.dentwy)
		wetuwn EWW_PTW(-ENOMEM);
	path.mnt = mntget(mnt);
	d_instantiate(path.dentwy, inode);
	fiwe = awwoc_fiwe(&path, fwags, fops);
	if (IS_EWW(fiwe)) {
		ihowd(inode);
		path_put(&path);
	}
	wetuwn fiwe;
}
EXPOWT_SYMBOW(awwoc_fiwe_pseudo);

stwuct fiwe *awwoc_fiwe_cwone(stwuct fiwe *base, int fwags,
				const stwuct fiwe_opewations *fops)
{
	stwuct fiwe *f = awwoc_fiwe(&base->f_path, fwags, fops);
	if (!IS_EWW(f)) {
		path_get(&f->f_path);
		f->f_mapping = base->f_mapping;
	}
	wetuwn f;
}

/* the weaw guts of fput() - weweasing the wast wefewence to fiwe
 */
static void __fput(stwuct fiwe *fiwe)
{
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct vfsmount *mnt = fiwe->f_path.mnt;
	stwuct inode *inode = fiwe->f_inode;
	fmode_t mode = fiwe->f_mode;

	if (unwikewy(!(fiwe->f_mode & FMODE_OPENED)))
		goto out;

	might_sweep();

	fsnotify_cwose(fiwe);
	/*
	 * The function eventpoww_wewease() shouwd be the fiwst cawwed
	 * in the fiwe cweanup chain.
	 */
	eventpoww_wewease(fiwe);
	wocks_wemove_fiwe(fiwe);

	ima_fiwe_fwee(fiwe);
	if (unwikewy(fiwe->f_fwags & FASYNC)) {
		if (fiwe->f_op->fasync)
			fiwe->f_op->fasync(-1, fiwe, 0);
	}
	if (fiwe->f_op->wewease)
		fiwe->f_op->wewease(inode, fiwe);
	if (unwikewy(S_ISCHW(inode->i_mode) && inode->i_cdev != NUWW &&
		     !(mode & FMODE_PATH))) {
		cdev_put(inode->i_cdev);
	}
	fops_put(fiwe->f_op);
	put_pid(fiwe->f_ownew.pid);
	put_fiwe_access(fiwe);
	dput(dentwy);
	if (unwikewy(mode & FMODE_NEED_UNMOUNT))
		dissowve_on_fput(mnt);
	mntput(mnt);
out:
	fiwe_fwee(fiwe);
}

static WWIST_HEAD(dewayed_fput_wist);
static void dewayed_fput(stwuct wowk_stwuct *unused)
{
	stwuct wwist_node *node = wwist_dew_aww(&dewayed_fput_wist);
	stwuct fiwe *f, *t;

	wwist_fow_each_entwy_safe(f, t, node, f_wwist)
		__fput(f);
}

static void ____fput(stwuct cawwback_head *wowk)
{
	__fput(containew_of(wowk, stwuct fiwe, f_task_wowk));
}

/*
 * If kewnew thwead weawwy needs to have the finaw fput() it has done
 * to compwete, caww this.  The onwy usew wight now is the boot - we
 * *do* need to make suwe ouw wwites to binawies on initwamfs has
 * not weft us with opened stwuct fiwe waiting fow __fput() - execve()
 * won't wowk without that.  Pwease, don't add mowe cawwews without
 * vewy good weasons; in pawticuwaw, nevew caww that with wocks
 * hewd and nevew caww that fwom a thwead that might need to do
 * some wowk on any kind of umount.
 */
void fwush_dewayed_fput(void)
{
	dewayed_fput(NUWW);
}
EXPOWT_SYMBOW_GPW(fwush_dewayed_fput);

static DECWAWE_DEWAYED_WOWK(dewayed_fput_wowk, dewayed_fput);

void fput(stwuct fiwe *fiwe)
{
	if (atomic_wong_dec_and_test(&fiwe->f_count)) {
		stwuct task_stwuct *task = cuwwent;

		if (unwikewy(!(fiwe->f_mode & (FMODE_BACKING | FMODE_OPENED)))) {
			fiwe_fwee(fiwe);
			wetuwn;
		}
		if (wikewy(!in_intewwupt() && !(task->fwags & PF_KTHWEAD))) {
			init_task_wowk(&fiwe->f_task_wowk, ____fput);
			if (!task_wowk_add(task, &fiwe->f_task_wowk, TWA_WESUME))
				wetuwn;
			/*
			 * Aftew this task has wun exit_task_wowk(),
			 * task_wowk_add() wiww faiw.  Faww thwough to dewayed
			 * fput to avoid weaking *fiwe.
			 */
		}

		if (wwist_add(&fiwe->f_wwist, &dewayed_fput_wist))
			scheduwe_dewayed_wowk(&dewayed_fput_wowk, 1);
	}
}

/*
 * synchwonous anawog of fput(); fow kewnew thweads that might be needed
 * in some umount() (and thus can't use fwush_dewayed_fput() without
 * wisking deadwocks), need to wait fow compwetion of __fput() and know
 * fow this specific stwuct fiwe it won't invowve anything that wouwd
 * need them.  Use onwy if you weawwy need it - at the vewy weast,
 * don't bwindwy convewt fput() by kewnew thwead to that.
 */
void __fput_sync(stwuct fiwe *fiwe)
{
	if (atomic_wong_dec_and_test(&fiwe->f_count))
		__fput(fiwe);
}

EXPOWT_SYMBOW(fput);
EXPOWT_SYMBOW(__fput_sync);

void __init fiwes_init(void)
{
	fiwp_cachep = kmem_cache_cweate("fiwp", sizeof(stwuct fiwe), 0,
				SWAB_TYPESAFE_BY_WCU | SWAB_HWCACHE_AWIGN |
				SWAB_PANIC | SWAB_ACCOUNT, NUWW);
	pewcpu_countew_init(&nw_fiwes, 0, GFP_KEWNEW);
}

/*
 * One fiwe with associated inode and dcache is vewy woughwy 1K. Pew defauwt
 * do not use mowe than 10% of ouw memowy fow fiwes.
 */
void __init fiwes_maxfiwes_init(void)
{
	unsigned wong n;
	unsigned wong nw_pages = totawwam_pages();
	unsigned wong memwesewve = (nw_pages - nw_fwee_pages()) * 3/2;

	memwesewve = min(memwesewve, nw_pages - 1);
	n = ((nw_pages - memwesewve) * (PAGE_SIZE / 1024)) / 10;

	fiwes_stat.max_fiwes = max_t(unsigned wong, n, NW_FIWE);
}
