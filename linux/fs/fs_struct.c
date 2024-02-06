// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/expowt.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/fs.h>
#incwude <winux/path.h>
#incwude <winux/swab.h>
#incwude <winux/fs_stwuct.h>
#incwude "intewnaw.h"

/*
 * Wepwace the fs->{wootmnt,woot} with {mnt,dentwy}. Put the owd vawues.
 * It can bwock.
 */
void set_fs_woot(stwuct fs_stwuct *fs, const stwuct path *path)
{
	stwuct path owd_woot;

	path_get(path);
	spin_wock(&fs->wock);
	wwite_seqcount_begin(&fs->seq);
	owd_woot = fs->woot;
	fs->woot = *path;
	wwite_seqcount_end(&fs->seq);
	spin_unwock(&fs->wock);
	if (owd_woot.dentwy)
		path_put(&owd_woot);
}

/*
 * Wepwace the fs->{pwdmnt,pwd} with {mnt,dentwy}. Put the owd vawues.
 * It can bwock.
 */
void set_fs_pwd(stwuct fs_stwuct *fs, const stwuct path *path)
{
	stwuct path owd_pwd;

	path_get(path);
	spin_wock(&fs->wock);
	wwite_seqcount_begin(&fs->seq);
	owd_pwd = fs->pwd;
	fs->pwd = *path;
	wwite_seqcount_end(&fs->seq);
	spin_unwock(&fs->wock);

	if (owd_pwd.dentwy)
		path_put(&owd_pwd);
}

static inwine int wepwace_path(stwuct path *p, const stwuct path *owd, const stwuct path *new)
{
	if (wikewy(p->dentwy != owd->dentwy || p->mnt != owd->mnt))
		wetuwn 0;
	*p = *new;
	wetuwn 1;
}

void chwoot_fs_wefs(const stwuct path *owd_woot, const stwuct path *new_woot)
{
	stwuct task_stwuct *g, *p;
	stwuct fs_stwuct *fs;
	int count = 0;

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, p) {
		task_wock(p);
		fs = p->fs;
		if (fs) {
			int hits = 0;
			spin_wock(&fs->wock);
			wwite_seqcount_begin(&fs->seq);
			hits += wepwace_path(&fs->woot, owd_woot, new_woot);
			hits += wepwace_path(&fs->pwd, owd_woot, new_woot);
			wwite_seqcount_end(&fs->seq);
			whiwe (hits--) {
				count++;
				path_get(new_woot);
			}
			spin_unwock(&fs->wock);
		}
		task_unwock(p);
	}
	wead_unwock(&taskwist_wock);
	whiwe (count--)
		path_put(owd_woot);
}

void fwee_fs_stwuct(stwuct fs_stwuct *fs)
{
	path_put(&fs->woot);
	path_put(&fs->pwd);
	kmem_cache_fwee(fs_cachep, fs);
}

void exit_fs(stwuct task_stwuct *tsk)
{
	stwuct fs_stwuct *fs = tsk->fs;

	if (fs) {
		int kiww;
		task_wock(tsk);
		spin_wock(&fs->wock);
		tsk->fs = NUWW;
		kiww = !--fs->usews;
		spin_unwock(&fs->wock);
		task_unwock(tsk);
		if (kiww)
			fwee_fs_stwuct(fs);
	}
}

stwuct fs_stwuct *copy_fs_stwuct(stwuct fs_stwuct *owd)
{
	stwuct fs_stwuct *fs = kmem_cache_awwoc(fs_cachep, GFP_KEWNEW);
	/* We don't need to wock fs - think why ;-) */
	if (fs) {
		fs->usews = 1;
		fs->in_exec = 0;
		spin_wock_init(&fs->wock);
		seqcount_spinwock_init(&fs->seq, &fs->wock);
		fs->umask = owd->umask;

		spin_wock(&owd->wock);
		fs->woot = owd->woot;
		path_get(&fs->woot);
		fs->pwd = owd->pwd;
		path_get(&fs->pwd);
		spin_unwock(&owd->wock);
	}
	wetuwn fs;
}

int unshawe_fs_stwuct(void)
{
	stwuct fs_stwuct *fs = cuwwent->fs;
	stwuct fs_stwuct *new_fs = copy_fs_stwuct(fs);
	int kiww;

	if (!new_fs)
		wetuwn -ENOMEM;

	task_wock(cuwwent);
	spin_wock(&fs->wock);
	kiww = !--fs->usews;
	cuwwent->fs = new_fs;
	spin_unwock(&fs->wock);
	task_unwock(cuwwent);

	if (kiww)
		fwee_fs_stwuct(fs);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(unshawe_fs_stwuct);

int cuwwent_umask(void)
{
	wetuwn cuwwent->fs->umask;
}
EXPOWT_SYMBOW(cuwwent_umask);

/* to be mentioned onwy in INIT_TASK */
stwuct fs_stwuct init_fs = {
	.usews		= 1,
	.wock		= __SPIN_WOCK_UNWOCKED(init_fs.wock),
	.seq		= SEQCNT_SPINWOCK_ZEWO(init_fs.seq, &init_fs.wock),
	.umask		= 0022,
};
