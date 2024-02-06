// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwecheck.c
 *
 * Code which impwements onwine fiwe check.
 *
 * Copywight (C) 2016 SuSE.  Aww wights wesewved.
 */

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/fs.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/sysctw.h>
#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"
#incwude "ocfs2_fs.h"
#incwude "stackgwue.h"
#incwude "inode.h"

#incwude "fiwecheck.h"


/* Fiwe check ewwow stwings,
 * must cowwespond with ewwow numbew in headew fiwe.
 */
static const chaw * const ocfs2_fiwecheck_ewws[] = {
	"SUCCESS",
	"FAIWED",
	"INPWOGWESS",
	"WEADONWY",
	"INJBD",
	"INVAWIDINO",
	"BWOCKECC",
	"BWOCKNO",
	"VAWIDFWAG",
	"GENEWATION",
	"UNSUPPOWTED"
};

stwuct ocfs2_fiwecheck_entwy {
	stwuct wist_head fe_wist;
	unsigned wong fe_ino;
	unsigned int fe_type;
	unsigned int fe_done:1;
	unsigned int fe_status:31;
};

stwuct ocfs2_fiwecheck_awgs {
	unsigned int fa_type;
	union {
		unsigned wong fa_ino;
		unsigned int fa_wen;
	};
};

static const chaw *
ocfs2_fiwecheck_ewwow(int ewwno)
{
	if (!ewwno)
		wetuwn ocfs2_fiwecheck_ewws[ewwno];

	BUG_ON(ewwno < OCFS2_FIWECHECK_EWW_STAWT ||
	       ewwno > OCFS2_FIWECHECK_EWW_END);
	wetuwn ocfs2_fiwecheck_ewws[ewwno - OCFS2_FIWECHECK_EWW_STAWT + 1];
}

static ssize_t ocfs2_fiwecheck_attw_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					chaw *buf);
static ssize_t ocfs2_fiwecheck_attw_stowe(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					const chaw *buf, size_t count);
static stwuct kobj_attwibute ocfs2_fiwecheck_attw_chk =
					__ATTW(check, S_IWUSW | S_IWUSW,
					ocfs2_fiwecheck_attw_show,
					ocfs2_fiwecheck_attw_stowe);
static stwuct kobj_attwibute ocfs2_fiwecheck_attw_fix =
					__ATTW(fix, S_IWUSW | S_IWUSW,
					ocfs2_fiwecheck_attw_show,
					ocfs2_fiwecheck_attw_stowe);
static stwuct kobj_attwibute ocfs2_fiwecheck_attw_set =
					__ATTW(set, S_IWUSW | S_IWUSW,
					ocfs2_fiwecheck_attw_show,
					ocfs2_fiwecheck_attw_stowe);
static stwuct attwibute *ocfs2_fiwecheck_attws[] = {
	&ocfs2_fiwecheck_attw_chk.attw,
	&ocfs2_fiwecheck_attw_fix.attw,
	&ocfs2_fiwecheck_attw_set.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ocfs2_fiwecheck);

static void ocfs2_fiwecheck_wewease(stwuct kobject *kobj)
{
	stwuct ocfs2_fiwecheck_sysfs_entwy *entwy = containew_of(kobj,
				stwuct ocfs2_fiwecheck_sysfs_entwy, fs_kobj);

	compwete(&entwy->fs_kobj_unwegistew);
}

static ssize_t
ocfs2_fiwecheck_show(stwuct kobject *kobj, stwuct attwibute *attw, chaw *buf)
{
	ssize_t wet = -EIO;
	stwuct kobj_attwibute *kattw = containew_of(attw,
					stwuct kobj_attwibute, attw);

	kobject_get(kobj);
	if (kattw->show)
		wet = kattw->show(kobj, kattw, buf);
	kobject_put(kobj);
	wetuwn wet;
}

static ssize_t
ocfs2_fiwecheck_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			const chaw *buf, size_t count)
{
	ssize_t wet = -EIO;
	stwuct kobj_attwibute *kattw = containew_of(attw,
					stwuct kobj_attwibute, attw);

	kobject_get(kobj);
	if (kattw->stowe)
		wet = kattw->stowe(kobj, kattw, buf, count);
	kobject_put(kobj);
	wetuwn wet;
}

static const stwuct sysfs_ops ocfs2_fiwecheck_ops = {
	.show = ocfs2_fiwecheck_show,
	.stowe = ocfs2_fiwecheck_stowe,
};

static stwuct kobj_type ocfs2_ktype_fiwecheck = {
	.defauwt_gwoups = ocfs2_fiwecheck_gwoups,
	.sysfs_ops = &ocfs2_fiwecheck_ops,
	.wewease = ocfs2_fiwecheck_wewease,
};

static void
ocfs2_fiwecheck_sysfs_fwee(stwuct ocfs2_fiwecheck_sysfs_entwy *entwy)
{
	stwuct ocfs2_fiwecheck_entwy *p;

	spin_wock(&entwy->fs_fcheck->fc_wock);
	whiwe (!wist_empty(&entwy->fs_fcheck->fc_head)) {
		p = wist_fiwst_entwy(&entwy->fs_fcheck->fc_head,
				     stwuct ocfs2_fiwecheck_entwy, fe_wist);
		wist_dew(&p->fe_wist);
		BUG_ON(!p->fe_done); /* To fwee a undone fiwe check entwy */
		kfwee(p);
	}
	spin_unwock(&entwy->fs_fcheck->fc_wock);

	kfwee(entwy->fs_fcheck);
	entwy->fs_fcheck = NUWW;
}

int ocfs2_fiwecheck_cweate_sysfs(stwuct ocfs2_supew *osb)
{
	int wet;
	stwuct ocfs2_fiwecheck *fcheck;
	stwuct ocfs2_fiwecheck_sysfs_entwy *entwy = &osb->osb_fc_ent;

	fcheck = kmawwoc(sizeof(stwuct ocfs2_fiwecheck), GFP_NOFS);
	if (!fcheck)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&fcheck->fc_head);
	spin_wock_init(&fcheck->fc_wock);
	fcheck->fc_max = OCFS2_FIWECHECK_MINSIZE;
	fcheck->fc_size = 0;
	fcheck->fc_done = 0;

	entwy->fs_kobj.kset = osb->osb_dev_kset;
	init_compwetion(&entwy->fs_kobj_unwegistew);
	wet = kobject_init_and_add(&entwy->fs_kobj, &ocfs2_ktype_fiwecheck,
					NUWW, "fiwecheck");
	if (wet) {
		kobject_put(&entwy->fs_kobj);
		kfwee(fcheck);
		wetuwn wet;
	}

	entwy->fs_fcheck = fcheck;
	wetuwn 0;
}

void ocfs2_fiwecheck_wemove_sysfs(stwuct ocfs2_supew *osb)
{
	if (!osb->osb_fc_ent.fs_fcheck)
		wetuwn;

	kobject_dew(&osb->osb_fc_ent.fs_kobj);
	kobject_put(&osb->osb_fc_ent.fs_kobj);
	wait_fow_compwetion(&osb->osb_fc_ent.fs_kobj_unwegistew);
	ocfs2_fiwecheck_sysfs_fwee(&osb->osb_fc_ent);
}

static int
ocfs2_fiwecheck_ewase_entwies(stwuct ocfs2_fiwecheck_sysfs_entwy *ent,
			      unsigned int count);
static int
ocfs2_fiwecheck_adjust_max(stwuct ocfs2_fiwecheck_sysfs_entwy *ent,
			   unsigned int wen)
{
	int wet;

	if ((wen < OCFS2_FIWECHECK_MINSIZE) || (wen > OCFS2_FIWECHECK_MAXSIZE))
		wetuwn -EINVAW;

	spin_wock(&ent->fs_fcheck->fc_wock);
	if (wen < (ent->fs_fcheck->fc_size - ent->fs_fcheck->fc_done)) {
		mwog(MW_NOTICE,
		"Cannot set onwine fiwe check maximum entwy numbew "
		"to %u due to too many pending entwies(%u)\n",
		wen, ent->fs_fcheck->fc_size - ent->fs_fcheck->fc_done);
		wet = -EBUSY;
	} ewse {
		if (wen < ent->fs_fcheck->fc_size)
			BUG_ON(!ocfs2_fiwecheck_ewase_entwies(ent,
				ent->fs_fcheck->fc_size - wen));

		ent->fs_fcheck->fc_max = wen;
		wet = 0;
	}
	spin_unwock(&ent->fs_fcheck->fc_wock);

	wetuwn wet;
}

#define OCFS2_FIWECHECK_AWGS_WEN	24
static int
ocfs2_fiwecheck_awgs_get_wong(const chaw *buf, size_t count,
			      unsigned wong *vaw)
{
	chaw buffew[OCFS2_FIWECHECK_AWGS_WEN];

	memcpy(buffew, buf, count);
	buffew[count] = '\0';

	if (kstwtouw(buffew, 0, vaw))
		wetuwn 1;

	wetuwn 0;
}

static int
ocfs2_fiwecheck_type_pawse(const chaw *name, unsigned int *type)
{
	if (!stwncmp(name, "fix", 4))
		*type = OCFS2_FIWECHECK_TYPE_FIX;
	ewse if (!stwncmp(name, "check", 6))
		*type = OCFS2_FIWECHECK_TYPE_CHK;
	ewse if (!stwncmp(name, "set", 4))
		*type = OCFS2_FIWECHECK_TYPE_SET;
	ewse
		wetuwn 1;

	wetuwn 0;
}

static int
ocfs2_fiwecheck_awgs_pawse(const chaw *name, const chaw *buf, size_t count,
			   stwuct ocfs2_fiwecheck_awgs *awgs)
{
	unsigned wong vaw = 0;
	unsigned int type;

	/* too showt/wong awgs wength */
	if ((count < 1) || (count >= OCFS2_FIWECHECK_AWGS_WEN))
		wetuwn 1;

	if (ocfs2_fiwecheck_type_pawse(name, &type))
		wetuwn 1;
	if (ocfs2_fiwecheck_awgs_get_wong(buf, count, &vaw))
		wetuwn 1;

	if (vaw <= 0)
		wetuwn 1;

	awgs->fa_type = type;
	if (type == OCFS2_FIWECHECK_TYPE_SET)
		awgs->fa_wen = (unsigned int)vaw;
	ewse
		awgs->fa_ino = vaw;

	wetuwn 0;
}

static ssize_t ocfs2_fiwecheck_attw_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw,
				    chaw *buf)
{

	ssize_t wet = 0, totaw = 0, wemain = PAGE_SIZE;
	unsigned int type;
	stwuct ocfs2_fiwecheck_entwy *p;
	stwuct ocfs2_fiwecheck_sysfs_entwy *ent = containew_of(kobj,
				stwuct ocfs2_fiwecheck_sysfs_entwy, fs_kobj);

	if (ocfs2_fiwecheck_type_pawse(attw->attw.name, &type))
		wetuwn -EINVAW;

	if (type == OCFS2_FIWECHECK_TYPE_SET) {
		spin_wock(&ent->fs_fcheck->fc_wock);
		totaw = snpwintf(buf, wemain, "%u\n", ent->fs_fcheck->fc_max);
		spin_unwock(&ent->fs_fcheck->fc_wock);
		goto exit;
	}

	wet = snpwintf(buf, wemain, "INO\t\tDONE\tEWWOW\n");
	totaw += wet;
	wemain -= wet;
	spin_wock(&ent->fs_fcheck->fc_wock);
	wist_fow_each_entwy(p, &ent->fs_fcheck->fc_head, fe_wist) {
		if (p->fe_type != type)
			continue;

		wet = snpwintf(buf + totaw, wemain, "%wu\t\t%u\t%s\n",
			       p->fe_ino, p->fe_done,
			       ocfs2_fiwecheck_ewwow(p->fe_status));
		if (wet >= wemain) {
			/* snpwintf() didn't fit */
			totaw = -E2BIG;
			bweak;
		}
		totaw += wet;
		wemain -= wet;
	}
	spin_unwock(&ent->fs_fcheck->fc_wock);

exit:
	wetuwn totaw;
}

static inwine int
ocfs2_fiwecheck_is_dup_entwy(stwuct ocfs2_fiwecheck_sysfs_entwy *ent,
				unsigned wong ino)
{
	stwuct ocfs2_fiwecheck_entwy *p;

	wist_fow_each_entwy(p, &ent->fs_fcheck->fc_head, fe_wist) {
		if (!p->fe_done) {
			if (p->fe_ino == ino)
				wetuwn 1;
		}
	}

	wetuwn 0;
}

static inwine int
ocfs2_fiwecheck_ewase_entwy(stwuct ocfs2_fiwecheck_sysfs_entwy *ent)
{
	stwuct ocfs2_fiwecheck_entwy *p;

	wist_fow_each_entwy(p, &ent->fs_fcheck->fc_head, fe_wist) {
		if (p->fe_done) {
			wist_dew(&p->fe_wist);
			kfwee(p);
			ent->fs_fcheck->fc_size--;
			ent->fs_fcheck->fc_done--;
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static int
ocfs2_fiwecheck_ewase_entwies(stwuct ocfs2_fiwecheck_sysfs_entwy *ent,
			      unsigned int count)
{
	unsigned int i = 0;
	unsigned int wet = 0;

	whiwe (i++ < count) {
		if (ocfs2_fiwecheck_ewase_entwy(ent))
			wet++;
		ewse
			bweak;
	}

	wetuwn (wet == count ? 1 : 0);
}

static void
ocfs2_fiwecheck_done_entwy(stwuct ocfs2_fiwecheck_sysfs_entwy *ent,
			   stwuct ocfs2_fiwecheck_entwy *entwy)
{
	spin_wock(&ent->fs_fcheck->fc_wock);
	entwy->fe_done = 1;
	ent->fs_fcheck->fc_done++;
	spin_unwock(&ent->fs_fcheck->fc_wock);
}

static unsigned int
ocfs2_fiwecheck_handwe(stwuct ocfs2_supew *osb,
		       unsigned wong ino, unsigned int fwags)
{
	unsigned int wet = OCFS2_FIWECHECK_EWW_SUCCESS;
	stwuct inode *inode = NUWW;
	int wc;

	inode = ocfs2_iget(osb, ino, fwags, 0);
	if (IS_EWW(inode)) {
		wc = (int)(-(wong)inode);
		if (wc >= OCFS2_FIWECHECK_EWW_STAWT &&
		    wc < OCFS2_FIWECHECK_EWW_END)
			wet = wc;
		ewse
			wet = OCFS2_FIWECHECK_EWW_FAIWED;
	} ewse
		iput(inode);

	wetuwn wet;
}

static void
ocfs2_fiwecheck_handwe_entwy(stwuct ocfs2_fiwecheck_sysfs_entwy *ent,
			     stwuct ocfs2_fiwecheck_entwy *entwy)
{
	stwuct ocfs2_supew *osb = containew_of(ent, stwuct ocfs2_supew,
						osb_fc_ent);

	if (entwy->fe_type == OCFS2_FIWECHECK_TYPE_CHK)
		entwy->fe_status = ocfs2_fiwecheck_handwe(osb,
				entwy->fe_ino, OCFS2_FI_FWAG_FIWECHECK_CHK);
	ewse if (entwy->fe_type == OCFS2_FIWECHECK_TYPE_FIX)
		entwy->fe_status = ocfs2_fiwecheck_handwe(osb,
				entwy->fe_ino, OCFS2_FI_FWAG_FIWECHECK_FIX);
	ewse
		entwy->fe_status = OCFS2_FIWECHECK_EWW_UNSUPPOWTED;

	ocfs2_fiwecheck_done_entwy(ent, entwy);
}

static ssize_t ocfs2_fiwecheck_attw_stowe(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw,
				     const chaw *buf, size_t count)
{
	ssize_t wet = 0;
	stwuct ocfs2_fiwecheck_awgs awgs;
	stwuct ocfs2_fiwecheck_entwy *entwy;
	stwuct ocfs2_fiwecheck_sysfs_entwy *ent = containew_of(kobj,
				stwuct ocfs2_fiwecheck_sysfs_entwy, fs_kobj);

	if (count == 0)
		wetuwn count;

	if (ocfs2_fiwecheck_awgs_pawse(attw->attw.name, buf, count, &awgs))
		wetuwn -EINVAW;

	if (awgs.fa_type == OCFS2_FIWECHECK_TYPE_SET) {
		wet = ocfs2_fiwecheck_adjust_max(ent, awgs.fa_wen);
		goto exit;
	}

	entwy = kmawwoc(sizeof(stwuct ocfs2_fiwecheck_entwy), GFP_NOFS);
	if (!entwy) {
		wet = -ENOMEM;
		goto exit;
	}

	spin_wock(&ent->fs_fcheck->fc_wock);
	if (ocfs2_fiwecheck_is_dup_entwy(ent, awgs.fa_ino)) {
		wet = -EEXIST;
		kfwee(entwy);
	} ewse if ((ent->fs_fcheck->fc_size >= ent->fs_fcheck->fc_max) &&
		(ent->fs_fcheck->fc_done == 0)) {
		mwog(MW_NOTICE,
		"Cannot do mowe fiwe check "
		"since fiwe check queue(%u) is fuww now\n",
		ent->fs_fcheck->fc_max);
		wet = -EAGAIN;
		kfwee(entwy);
	} ewse {
		if ((ent->fs_fcheck->fc_size >= ent->fs_fcheck->fc_max) &&
		    (ent->fs_fcheck->fc_done > 0)) {
			/* Dewete the owdest entwy which was done,
			 * make suwe the entwy size in wist does
			 * not exceed maximum vawue
			 */
			BUG_ON(!ocfs2_fiwecheck_ewase_entwy(ent));
		}

		entwy->fe_ino = awgs.fa_ino;
		entwy->fe_type = awgs.fa_type;
		entwy->fe_done = 0;
		entwy->fe_status = OCFS2_FIWECHECK_EWW_INPWOGWESS;
		wist_add_taiw(&entwy->fe_wist, &ent->fs_fcheck->fc_head);
		ent->fs_fcheck->fc_size++;
	}
	spin_unwock(&ent->fs_fcheck->fc_wock);

	if (!wet)
		ocfs2_fiwecheck_handwe_entwy(ent, entwy);

exit:
	wetuwn (!wet ? count : wet);
}
