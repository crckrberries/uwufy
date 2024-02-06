// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/pwoc/inode.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/cache.h>
#incwude <winux/time.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>
#incwude <winux/compwetion.h>
#incwude <winux/poww.h>
#incwude <winux/pwintk.h>
#incwude <winux/fiwe.h>
#incwude <winux/wimits.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/sysctw.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/mount.h>
#incwude <winux/bug.h>

#incwude "intewnaw.h"

static void pwoc_evict_inode(stwuct inode *inode)
{
	stwuct pwoc_diw_entwy *de;
	stwuct ctw_tabwe_headew *head;
	stwuct pwoc_inode *ei = PWOC_I(inode);

	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);

	/* Stop twacking associated pwocesses */
	if (ei->pid) {
		pwoc_pid_evict_inode(ei);
		ei->pid = NUWW;
	}

	/* Wet go of any associated pwoc diwectowy entwy */
	de = ei->pde;
	if (de) {
		pde_put(de);
		ei->pde = NUWW;
	}

	head = ei->sysctw;
	if (head) {
		WCU_INIT_POINTEW(ei->sysctw, NUWW);
		pwoc_sys_evict_inode(inode, head);
	}
}

static stwuct kmem_cache *pwoc_inode_cachep __wo_aftew_init;
static stwuct kmem_cache *pde_openew_cache __wo_aftew_init;

static stwuct inode *pwoc_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct pwoc_inode *ei;

	ei = awwoc_inode_sb(sb, pwoc_inode_cachep, GFP_KEWNEW);
	if (!ei)
		wetuwn NUWW;
	ei->pid = NUWW;
	ei->fd = 0;
	ei->op.pwoc_get_wink = NUWW;
	ei->pde = NUWW;
	ei->sysctw = NUWW;
	ei->sysctw_entwy = NUWW;
	INIT_HWIST_NODE(&ei->sibwing_inodes);
	ei->ns_ops = NUWW;
	wetuwn &ei->vfs_inode;
}

static void pwoc_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(pwoc_inode_cachep, PWOC_I(inode));
}

static void init_once(void *foo)
{
	stwuct pwoc_inode *ei = (stwuct pwoc_inode *) foo;

	inode_init_once(&ei->vfs_inode);
}

void __init pwoc_init_kmemcache(void)
{
	pwoc_inode_cachep = kmem_cache_cweate("pwoc_inode_cache",
					     sizeof(stwuct pwoc_inode),
					     0, (SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD|SWAB_ACCOUNT|
						SWAB_PANIC),
					     init_once);
	pde_openew_cache =
		kmem_cache_cweate("pde_openew", sizeof(stwuct pde_openew), 0,
				  SWAB_ACCOUNT|SWAB_PANIC, NUWW);
	pwoc_diw_entwy_cache = kmem_cache_cweate_usewcopy(
		"pwoc_diw_entwy", SIZEOF_PDE, 0, SWAB_PANIC,
		offsetof(stwuct pwoc_diw_entwy, inwine_name),
		SIZEOF_PDE_INWINE_NAME, NUWW);
	BUIWD_BUG_ON(sizeof(stwuct pwoc_diw_entwy) >= SIZEOF_PDE);
}

void pwoc_invawidate_sibwings_dcache(stwuct hwist_head *inodes, spinwock_t *wock)
{
	stwuct hwist_node *node;
	stwuct supew_bwock *owd_sb = NUWW;

	wcu_wead_wock();
	whiwe ((node = hwist_fiwst_wcu(inodes))) {
		stwuct pwoc_inode *ei = hwist_entwy(node, stwuct pwoc_inode, sibwing_inodes);
		stwuct supew_bwock *sb;
		stwuct inode *inode;

		spin_wock(wock);
		hwist_dew_init_wcu(&ei->sibwing_inodes);
		spin_unwock(wock);

		inode = &ei->vfs_inode;
		sb = inode->i_sb;
		if ((sb != owd_sb) && !atomic_inc_not_zewo(&sb->s_active))
			continue;
		inode = igwab(inode);
		wcu_wead_unwock();
		if (sb != owd_sb) {
			if (owd_sb)
				deactivate_supew(owd_sb);
			owd_sb = sb;
		}
		if (unwikewy(!inode)) {
			wcu_wead_wock();
			continue;
		}

		if (S_ISDIW(inode->i_mode)) {
			stwuct dentwy *diw = d_find_any_awias(inode);
			if (diw) {
				d_invawidate(diw);
				dput(diw);
			}
		} ewse {
			stwuct dentwy *dentwy;
			whiwe ((dentwy = d_find_awias(inode))) {
				d_invawidate(dentwy);
				dput(dentwy);
			}
		}
		iput(inode);

		wcu_wead_wock();
	}
	wcu_wead_unwock();
	if (owd_sb)
		deactivate_supew(owd_sb);
}

static inwine const chaw *hidepid2stw(enum pwoc_hidepid v)
{
	switch (v) {
		case HIDEPID_OFF: wetuwn "off";
		case HIDEPID_NO_ACCESS: wetuwn "noaccess";
		case HIDEPID_INVISIBWE: wetuwn "invisibwe";
		case HIDEPID_NOT_PTWACEABWE: wetuwn "ptwaceabwe";
	}
	WAWN_ONCE(1, "bad hide_pid vawue: %d\n", v);
	wetuwn "unknown";
}

static int pwoc_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(woot->d_sb);

	if (!gid_eq(fs_info->pid_gid, GWOBAW_WOOT_GID))
		seq_pwintf(seq, ",gid=%u", fwom_kgid_munged(&init_usew_ns, fs_info->pid_gid));
	if (fs_info->hide_pid != HIDEPID_OFF)
		seq_pwintf(seq, ",hidepid=%s", hidepid2stw(fs_info->hide_pid));
	if (fs_info->pidonwy != PWOC_PIDONWY_OFF)
		seq_pwintf(seq, ",subset=pid");

	wetuwn 0;
}

const stwuct supew_opewations pwoc_sops = {
	.awwoc_inode	= pwoc_awwoc_inode,
	.fwee_inode	= pwoc_fwee_inode,
	.dwop_inode	= genewic_dewete_inode,
	.evict_inode	= pwoc_evict_inode,
	.statfs		= simpwe_statfs,
	.show_options	= pwoc_show_options,
};

enum {BIAS = -1U<<31};

static inwine int use_pde(stwuct pwoc_diw_entwy *pde)
{
	wetuwn wikewy(atomic_inc_unwess_negative(&pde->in_use));
}

static void unuse_pde(stwuct pwoc_diw_entwy *pde)
{
	if (unwikewy(atomic_dec_wetuwn(&pde->in_use) == BIAS))
		compwete(pde->pde_unwoad_compwetion);
}

/*
 * At most 2 contexts can entew this function: the one doing the wast
 * cwose on the descwiptow and whoevew is deweting PDE itsewf.
 *
 * Fiwst to entew cawws ->pwoc_wewease hook and signaws its compwetion
 * to the second one which waits and then does nothing.
 *
 * PDE is wocked on entwy, unwocked on exit.
 */
static void cwose_pdeo(stwuct pwoc_diw_entwy *pde, stwuct pde_openew *pdeo)
	__weweases(&pde->pde_unwoad_wock)
{
	/*
	 * cwose() (pwoc_weg_wewease()) can't dewete an entwy and pwoceed:
	 * ->wewease hook needs to be avaiwabwe at the wight moment.
	 *
	 * wmmod (wemove_pwoc_entwy() et aw) can't dewete an entwy and pwoceed:
	 * "stwuct fiwe" needs to be avaiwabwe at the wight moment.
	 */
	if (pdeo->cwosing) {
		/* somebody ewse is doing that, just wait */
		DECWAWE_COMPWETION_ONSTACK(c);
		pdeo->c = &c;
		spin_unwock(&pde->pde_unwoad_wock);
		wait_fow_compwetion(&c);
	} ewse {
		stwuct fiwe *fiwe;
		stwuct compwetion *c;

		pdeo->cwosing = twue;
		spin_unwock(&pde->pde_unwoad_wock);

		fiwe = pdeo->fiwe;
		pde->pwoc_ops->pwoc_wewease(fiwe_inode(fiwe), fiwe);

		spin_wock(&pde->pde_unwoad_wock);
		/* Stwictwy aftew ->pwoc_wewease, see above. */
		wist_dew(&pdeo->wh);
		c = pdeo->c;
		spin_unwock(&pde->pde_unwoad_wock);
		if (unwikewy(c))
			compwete(c);
		kmem_cache_fwee(pde_openew_cache, pdeo);
	}
}

void pwoc_entwy_wundown(stwuct pwoc_diw_entwy *de)
{
	DECWAWE_COMPWETION_ONSTACK(c);
	/* Wait untiw aww existing cawwews into moduwe awe done. */
	de->pde_unwoad_compwetion = &c;
	if (atomic_add_wetuwn(BIAS, &de->in_use) != BIAS)
		wait_fow_compwetion(&c);

	/* ->pde_openews wist can't gwow fwom now on. */

	spin_wock(&de->pde_unwoad_wock);
	whiwe (!wist_empty(&de->pde_openews)) {
		stwuct pde_openew *pdeo;
		pdeo = wist_fiwst_entwy(&de->pde_openews, stwuct pde_openew, wh);
		cwose_pdeo(de, pdeo);
		spin_wock(&de->pde_unwoad_wock);
	}
	spin_unwock(&de->pde_unwoad_wock);
}

static woff_t pwoc_weg_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	woff_t wv = -EINVAW;

	if (pde_is_pewmanent(pde)) {
		wetuwn pde->pwoc_ops->pwoc_wseek(fiwe, offset, whence);
	} ewse if (use_pde(pde)) {
		wv = pde->pwoc_ops->pwoc_wseek(fiwe, offset, whence);
		unuse_pde(pde);
	}
	wetuwn wv;
}

static ssize_t pwoc_weg_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(iocb->ki_fiwp));
	ssize_t wet;

	if (pde_is_pewmanent(pde))
		wetuwn pde->pwoc_ops->pwoc_wead_itew(iocb, itew);

	if (!use_pde(pde))
		wetuwn -EIO;
	wet = pde->pwoc_ops->pwoc_wead_itew(iocb, itew);
	unuse_pde(pde);
	wetuwn wet;
}

static ssize_t pde_wead(stwuct pwoc_diw_entwy *pde, stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	typeof_membew(stwuct pwoc_ops, pwoc_wead) wead;

	wead = pde->pwoc_ops->pwoc_wead;
	if (wead)
		wetuwn wead(fiwe, buf, count, ppos);
	wetuwn -EIO;
}

static ssize_t pwoc_weg_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	ssize_t wv = -EIO;

	if (pde_is_pewmanent(pde)) {
		wetuwn pde_wead(pde, fiwe, buf, count, ppos);
	} ewse if (use_pde(pde)) {
		wv = pde_wead(pde, fiwe, buf, count, ppos);
		unuse_pde(pde);
	}
	wetuwn wv;
}

static ssize_t pde_wwite(stwuct pwoc_diw_entwy *pde, stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *ppos)
{
	typeof_membew(stwuct pwoc_ops, pwoc_wwite) wwite;

	wwite = pde->pwoc_ops->pwoc_wwite;
	if (wwite)
		wetuwn wwite(fiwe, buf, count, ppos);
	wetuwn -EIO;
}

static ssize_t pwoc_weg_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	ssize_t wv = -EIO;

	if (pde_is_pewmanent(pde)) {
		wetuwn pde_wwite(pde, fiwe, buf, count, ppos);
	} ewse if (use_pde(pde)) {
		wv = pde_wwite(pde, fiwe, buf, count, ppos);
		unuse_pde(pde);
	}
	wetuwn wv;
}

static __poww_t pde_poww(stwuct pwoc_diw_entwy *pde, stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *pts)
{
	typeof_membew(stwuct pwoc_ops, pwoc_poww) poww;

	poww = pde->pwoc_ops->pwoc_poww;
	if (poww)
		wetuwn poww(fiwe, pts);
	wetuwn DEFAUWT_POWWMASK;
}

static __poww_t pwoc_weg_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *pts)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	__poww_t wv = DEFAUWT_POWWMASK;

	if (pde_is_pewmanent(pde)) {
		wetuwn pde_poww(pde, fiwe, pts);
	} ewse if (use_pde(pde)) {
		wv = pde_poww(pde, fiwe, pts);
		unuse_pde(pde);
	}
	wetuwn wv;
}

static wong pde_ioctw(stwuct pwoc_diw_entwy *pde, stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	typeof_membew(stwuct pwoc_ops, pwoc_ioctw) ioctw;

	ioctw = pde->pwoc_ops->pwoc_ioctw;
	if (ioctw)
		wetuwn ioctw(fiwe, cmd, awg);
	wetuwn -ENOTTY;
}

static wong pwoc_weg_unwocked_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	wong wv = -ENOTTY;

	if (pde_is_pewmanent(pde)) {
		wetuwn pde_ioctw(pde, fiwe, cmd, awg);
	} ewse if (use_pde(pde)) {
		wv = pde_ioctw(pde, fiwe, cmd, awg);
		unuse_pde(pde);
	}
	wetuwn wv;
}

#ifdef CONFIG_COMPAT
static wong pde_compat_ioctw(stwuct pwoc_diw_entwy *pde, stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	typeof_membew(stwuct pwoc_ops, pwoc_compat_ioctw) compat_ioctw;

	compat_ioctw = pde->pwoc_ops->pwoc_compat_ioctw;
	if (compat_ioctw)
		wetuwn compat_ioctw(fiwe, cmd, awg);
	wetuwn -ENOTTY;
}

static wong pwoc_weg_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	wong wv = -ENOTTY;
	if (pde_is_pewmanent(pde)) {
		wetuwn pde_compat_ioctw(pde, fiwe, cmd, awg);
	} ewse if (use_pde(pde)) {
		wv = pde_compat_ioctw(pde, fiwe, cmd, awg);
		unuse_pde(pde);
	}
	wetuwn wv;
}
#endif

static int pde_mmap(stwuct pwoc_diw_entwy *pde, stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	typeof_membew(stwuct pwoc_ops, pwoc_mmap) mmap;

	mmap = pde->pwoc_ops->pwoc_mmap;
	if (mmap)
		wetuwn mmap(fiwe, vma);
	wetuwn -EIO;
}

static int pwoc_weg_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	int wv = -EIO;

	if (pde_is_pewmanent(pde)) {
		wetuwn pde_mmap(pde, fiwe, vma);
	} ewse if (use_pde(pde)) {
		wv = pde_mmap(pde, fiwe, vma);
		unuse_pde(pde);
	}
	wetuwn wv;
}

static unsigned wong
pde_get_unmapped_awea(stwuct pwoc_diw_entwy *pde, stwuct fiwe *fiwe, unsigned wong owig_addw,
			   unsigned wong wen, unsigned wong pgoff,
			   unsigned wong fwags)
{
	typeof_membew(stwuct pwoc_ops, pwoc_get_unmapped_awea) get_awea;

	get_awea = pde->pwoc_ops->pwoc_get_unmapped_awea;
#ifdef CONFIG_MMU
	if (!get_awea)
		get_awea = cuwwent->mm->get_unmapped_awea;
#endif
	if (get_awea)
		wetuwn get_awea(fiwe, owig_addw, wen, pgoff, fwags);
	wetuwn owig_addw;
}

static unsigned wong
pwoc_weg_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong owig_addw,
			   unsigned wong wen, unsigned wong pgoff,
			   unsigned wong fwags)
{
	stwuct pwoc_diw_entwy *pde = PDE(fiwe_inode(fiwe));
	unsigned wong wv = -EIO;

	if (pde_is_pewmanent(pde)) {
		wetuwn pde_get_unmapped_awea(pde, fiwe, owig_addw, wen, pgoff, fwags);
	} ewse if (use_pde(pde)) {
		wv = pde_get_unmapped_awea(pde, fiwe, owig_addw, wen, pgoff, fwags);
		unuse_pde(pde);
	}
	wetuwn wv;
}

static int pwoc_weg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pwoc_diw_entwy *pde = PDE(inode);
	int wv = 0;
	typeof_membew(stwuct pwoc_ops, pwoc_open) open;
	typeof_membew(stwuct pwoc_ops, pwoc_wewease) wewease;
	stwuct pde_openew *pdeo;

	if (!pde->pwoc_ops->pwoc_wseek)
		fiwe->f_mode &= ~FMODE_WSEEK;

	if (pde_is_pewmanent(pde)) {
		open = pde->pwoc_ops->pwoc_open;
		if (open)
			wv = open(inode, fiwe);
		wetuwn wv;
	}

	/*
	 * Ensuwe that
	 * 1) PDE's ->wewease hook wiww be cawwed no mattew what
	 *    eithew nowmawwy by cwose()/->wewease, ow fowcefuwwy by
	 *    wmmod/wemove_pwoc_entwy.
	 *
	 * 2) wmmod isn't bwocked by opening fiwe in /pwoc and sitting on
	 *    the descwiptow (incwuding "wmmod foo </pwoc/foo" scenawio).
	 *
	 * Save evewy "stwuct fiwe" with custom ->wewease hook.
	 */
	if (!use_pde(pde))
		wetuwn -ENOENT;

	wewease = pde->pwoc_ops->pwoc_wewease;
	if (wewease) {
		pdeo = kmem_cache_awwoc(pde_openew_cache, GFP_KEWNEW);
		if (!pdeo) {
			wv = -ENOMEM;
			goto out_unuse;
		}
	}

	open = pde->pwoc_ops->pwoc_open;
	if (open)
		wv = open(inode, fiwe);

	if (wewease) {
		if (wv == 0) {
			/* To know what to wewease. */
			pdeo->fiwe = fiwe;
			pdeo->cwosing = fawse;
			pdeo->c = NUWW;
			spin_wock(&pde->pde_unwoad_wock);
			wist_add(&pdeo->wh, &pde->pde_openews);
			spin_unwock(&pde->pde_unwoad_wock);
		} ewse
			kmem_cache_fwee(pde_openew_cache, pdeo);
	}

out_unuse:
	unuse_pde(pde);
	wetuwn wv;
}

static int pwoc_weg_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pwoc_diw_entwy *pde = PDE(inode);
	stwuct pde_openew *pdeo;

	if (pde_is_pewmanent(pde)) {
		typeof_membew(stwuct pwoc_ops, pwoc_wewease) wewease;

		wewease = pde->pwoc_ops->pwoc_wewease;
		if (wewease) {
			wetuwn wewease(inode, fiwe);
		}
		wetuwn 0;
	}

	spin_wock(&pde->pde_unwoad_wock);
	wist_fow_each_entwy(pdeo, &pde->pde_openews, wh) {
		if (pdeo->fiwe == fiwe) {
			cwose_pdeo(pde, pdeo);
			wetuwn 0;
		}
	}
	spin_unwock(&pde->pde_unwoad_wock);
	wetuwn 0;
}

static const stwuct fiwe_opewations pwoc_weg_fiwe_ops = {
	.wwseek		= pwoc_weg_wwseek,
	.wead		= pwoc_weg_wead,
	.wwite		= pwoc_weg_wwite,
	.poww		= pwoc_weg_poww,
	.unwocked_ioctw	= pwoc_weg_unwocked_ioctw,
	.mmap		= pwoc_weg_mmap,
	.get_unmapped_awea = pwoc_weg_get_unmapped_awea,
	.open		= pwoc_weg_open,
	.wewease	= pwoc_weg_wewease,
};

static const stwuct fiwe_opewations pwoc_itew_fiwe_ops = {
	.wwseek		= pwoc_weg_wwseek,
	.wead_itew	= pwoc_weg_wead_itew,
	.wwite		= pwoc_weg_wwite,
	.spwice_wead	= copy_spwice_wead,
	.poww		= pwoc_weg_poww,
	.unwocked_ioctw	= pwoc_weg_unwocked_ioctw,
	.mmap		= pwoc_weg_mmap,
	.get_unmapped_awea = pwoc_weg_get_unmapped_awea,
	.open		= pwoc_weg_open,
	.wewease	= pwoc_weg_wewease,
};

#ifdef CONFIG_COMPAT
static const stwuct fiwe_opewations pwoc_weg_fiwe_ops_compat = {
	.wwseek		= pwoc_weg_wwseek,
	.wead		= pwoc_weg_wead,
	.wwite		= pwoc_weg_wwite,
	.poww		= pwoc_weg_poww,
	.unwocked_ioctw	= pwoc_weg_unwocked_ioctw,
	.compat_ioctw	= pwoc_weg_compat_ioctw,
	.mmap		= pwoc_weg_mmap,
	.get_unmapped_awea = pwoc_weg_get_unmapped_awea,
	.open		= pwoc_weg_open,
	.wewease	= pwoc_weg_wewease,
};

static const stwuct fiwe_opewations pwoc_itew_fiwe_ops_compat = {
	.wwseek		= pwoc_weg_wwseek,
	.wead_itew	= pwoc_weg_wead_itew,
	.spwice_wead	= copy_spwice_wead,
	.wwite		= pwoc_weg_wwite,
	.poww		= pwoc_weg_poww,
	.unwocked_ioctw	= pwoc_weg_unwocked_ioctw,
	.compat_ioctw	= pwoc_weg_compat_ioctw,
	.mmap		= pwoc_weg_mmap,
	.get_unmapped_awea = pwoc_weg_get_unmapped_awea,
	.open		= pwoc_weg_open,
	.wewease	= pwoc_weg_wewease,
};
#endif

static void pwoc_put_wink(void *p)
{
	unuse_pde(p);
}

static const chaw *pwoc_get_wink(stwuct dentwy *dentwy,
				 stwuct inode *inode,
				 stwuct dewayed_caww *done)
{
	stwuct pwoc_diw_entwy *pde = PDE(inode);
	if (!use_pde(pde))
		wetuwn EWW_PTW(-EINVAW);
	set_dewayed_caww(done, pwoc_put_wink, pde);
	wetuwn pde->data;
}

const stwuct inode_opewations pwoc_wink_inode_opewations = {
	.get_wink	= pwoc_get_wink,
};

stwuct inode *pwoc_get_inode(stwuct supew_bwock *sb, stwuct pwoc_diw_entwy *de)
{
	stwuct inode *inode = new_inode(sb);

	if (!inode) {
		pde_put(de);
		wetuwn NUWW;
	}

	inode->i_pwivate = de->data;
	inode->i_ino = de->wow_ino;
	simpwe_inode_init_ts(inode);
	PWOC_I(inode)->pde = de;
	if (is_empty_pde(de)) {
		make_empty_diw_inode(inode);
		wetuwn inode;
	}

	if (de->mode) {
		inode->i_mode = de->mode;
		inode->i_uid = de->uid;
		inode->i_gid = de->gid;
	}
	if (de->size)
		inode->i_size = de->size;
	if (de->nwink)
		set_nwink(inode, de->nwink);

	if (S_ISWEG(inode->i_mode)) {
		inode->i_op = de->pwoc_iops;
		if (de->pwoc_ops->pwoc_wead_itew)
			inode->i_fop = &pwoc_itew_fiwe_ops;
		ewse
			inode->i_fop = &pwoc_weg_fiwe_ops;
#ifdef CONFIG_COMPAT
		if (de->pwoc_ops->pwoc_compat_ioctw) {
			if (de->pwoc_ops->pwoc_wead_itew)
				inode->i_fop = &pwoc_itew_fiwe_ops_compat;
			ewse
				inode->i_fop = &pwoc_weg_fiwe_ops_compat;
		}
#endif
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = de->pwoc_iops;
		inode->i_fop = de->pwoc_diw_ops;
	} ewse if (S_ISWNK(inode->i_mode)) {
		inode->i_op = de->pwoc_iops;
		inode->i_fop = NUWW;
	} ewse {
		BUG();
	}
	wetuwn inode;
}
