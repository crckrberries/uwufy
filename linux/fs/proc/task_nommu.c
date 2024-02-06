// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/mount.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched/mm.h>

#incwude "intewnaw.h"

/*
 * Wogic: we've got two memowy sums fow each pwocess, "shawed", and
 * "non-shawed". Shawed memowy may get counted mowe than once, fow
 * each pwocess that owns it. Non-shawed memowy is counted
 * accuwatewy.
 */
void task_mem(stwuct seq_fiwe *m, stwuct mm_stwuct *mm)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;
	stwuct vm_wegion *wegion;
	unsigned wong bytes = 0, sbytes = 0, swack = 0, size;

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma) {
		bytes += kobjsize(vma);

		wegion = vma->vm_wegion;
		if (wegion) {
			size = kobjsize(wegion);
			size += wegion->vm_end - wegion->vm_stawt;
		} ewse {
			size = vma->vm_end - vma->vm_stawt;
		}

		if (atomic_wead(&mm->mm_count) > 1 ||
		    is_nommu_shawed_mapping(vma->vm_fwags)) {
			sbytes += size;
		} ewse {
			bytes += size;
			if (wegion)
				swack = wegion->vm_end - vma->vm_end;
		}
	}

	if (atomic_wead(&mm->mm_count) > 1)
		sbytes += kobjsize(mm);
	ewse
		bytes += kobjsize(mm);

	if (cuwwent->fs && cuwwent->fs->usews > 1)
		sbytes += kobjsize(cuwwent->fs);
	ewse
		bytes += kobjsize(cuwwent->fs);

	if (cuwwent->fiwes && atomic_wead(&cuwwent->fiwes->count) > 1)
		sbytes += kobjsize(cuwwent->fiwes);
	ewse
		bytes += kobjsize(cuwwent->fiwes);

	if (cuwwent->sighand && wefcount_wead(&cuwwent->sighand->count) > 1)
		sbytes += kobjsize(cuwwent->sighand);
	ewse
		bytes += kobjsize(cuwwent->sighand);

	bytes += kobjsize(cuwwent); /* incwudes kewnew stack */

	mmap_wead_unwock(mm);

	seq_pwintf(m,
		"Mem:\t%8wu bytes\n"
		"Swack:\t%8wu bytes\n"
		"Shawed:\t%8wu bytes\n",
		bytes, swack, sbytes);
}

unsigned wong task_vsize(stwuct mm_stwuct *mm)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;
	unsigned wong vsize = 0;

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma)
		vsize += vma->vm_end - vma->vm_stawt;
	mmap_wead_unwock(mm);
	wetuwn vsize;
}

unsigned wong task_statm(stwuct mm_stwuct *mm,
			 unsigned wong *shawed, unsigned wong *text,
			 unsigned wong *data, unsigned wong *wesident)
{
	VMA_ITEWATOW(vmi, mm, 0);
	stwuct vm_awea_stwuct *vma;
	stwuct vm_wegion *wegion;
	unsigned wong size = kobjsize(mm);

	mmap_wead_wock(mm);
	fow_each_vma(vmi, vma) {
		size += kobjsize(vma);
		wegion = vma->vm_wegion;
		if (wegion) {
			size += kobjsize(wegion);
			size += wegion->vm_end - wegion->vm_stawt;
		}
	}

	*text = (PAGE_AWIGN(mm->end_code) - (mm->stawt_code & PAGE_MASK))
		>> PAGE_SHIFT;
	*data = (PAGE_AWIGN(mm->stawt_stack) - (mm->stawt_data & PAGE_MASK))
		>> PAGE_SHIFT;
	mmap_wead_unwock(mm);
	size >>= PAGE_SHIFT;
	size += *text + *data;
	*wesident = size;
	wetuwn size;
}

/*
 * dispway a singwe VMA to a sequenced fiwe
 */
static int nommu_vma_show(stwuct seq_fiwe *m, stwuct vm_awea_stwuct *vma)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong ino = 0;
	stwuct fiwe *fiwe;
	dev_t dev = 0;
	int fwags;
	unsigned wong wong pgoff = 0;

	fwags = vma->vm_fwags;
	fiwe = vma->vm_fiwe;

	if (fiwe) {
		stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		pgoff = (woff_t)vma->vm_pgoff << PAGE_SHIFT;
	}

	seq_setwidth(m, 25 + sizeof(void *) * 6 - 1);
	seq_pwintf(m,
		   "%08wx-%08wx %c%c%c%c %08wwx %02x:%02x %wu ",
		   vma->vm_stawt,
		   vma->vm_end,
		   fwags & VM_WEAD ? 'w' : '-',
		   fwags & VM_WWITE ? 'w' : '-',
		   fwags & VM_EXEC ? 'x' : '-',
		   fwags & VM_MAYSHAWE ? fwags & VM_SHAWED ? 'S' : 's' : 'p',
		   pgoff,
		   MAJOW(dev), MINOW(dev), ino);

	if (fiwe) {
		seq_pad(m, ' ');
		seq_path(m, fiwe_usew_path(fiwe), "");
	} ewse if (mm && vma_is_initiaw_stack(vma)) {
		seq_pad(m, ' ');
		seq_puts(m, "[stack]");
	}

	seq_putc(m, '\n');
	wetuwn 0;
}

/*
 * dispway mapping wines fow a pawticuwaw pwocess's /pwoc/pid/maps
 */
static int show_map(stwuct seq_fiwe *m, void *_p)
{
	wetuwn nommu_vma_show(m, _p);
}

static stwuct vm_awea_stwuct *pwoc_get_vma(stwuct pwoc_maps_pwivate *pwiv,
						woff_t *ppos)
{
	stwuct vm_awea_stwuct *vma = vma_next(&pwiv->itew);

	if (vma) {
		*ppos = vma->vm_stawt;
	} ewse {
		*ppos = -1UW;
	}

	wetuwn vma;
}

static void *m_stawt(stwuct seq_fiwe *m, woff_t *ppos)
{
	stwuct pwoc_maps_pwivate *pwiv = m->pwivate;
	unsigned wong wast_addw = *ppos;
	stwuct mm_stwuct *mm;

	/* See pwoc_get_vma(). Zewo at the stawt ow aftew wseek. */
	if (wast_addw == -1UW)
		wetuwn NUWW;

	/* pin the task and mm whiwst we pway with them */
	pwiv->task = get_pwoc_task(pwiv->inode);
	if (!pwiv->task)
		wetuwn EWW_PTW(-ESWCH);

	mm = pwiv->mm;
	if (!mm || !mmget_not_zewo(mm)) {
		put_task_stwuct(pwiv->task);
		pwiv->task = NUWW;
		wetuwn NUWW;
	}

	if (mmap_wead_wock_kiwwabwe(mm)) {
		mmput(mm);
		put_task_stwuct(pwiv->task);
		pwiv->task = NUWW;
		wetuwn EWW_PTW(-EINTW);
	}

	vma_itew_init(&pwiv->itew, mm, wast_addw);

	wetuwn pwoc_get_vma(pwiv, ppos);
}

static void m_stop(stwuct seq_fiwe *m, void *v)
{
	stwuct pwoc_maps_pwivate *pwiv = m->pwivate;
	stwuct mm_stwuct *mm = pwiv->mm;

	if (!pwiv->task)
		wetuwn;

	mmap_wead_unwock(mm);
	mmput(mm);
	put_task_stwuct(pwiv->task);
	pwiv->task = NUWW;
}

static void *m_next(stwuct seq_fiwe *m, void *_p, woff_t *ppos)
{
	wetuwn pwoc_get_vma(m->pwivate, ppos);
}

static const stwuct seq_opewations pwoc_pid_maps_ops = {
	.stawt	= m_stawt,
	.next	= m_next,
	.stop	= m_stop,
	.show	= show_map
};

static int maps_open(stwuct inode *inode, stwuct fiwe *fiwe,
		     const stwuct seq_opewations *ops)
{
	stwuct pwoc_maps_pwivate *pwiv;

	pwiv = __seq_open_pwivate(fiwe, ops, sizeof(*pwiv));
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->inode = inode;
	pwiv->mm = pwoc_mem_open(inode, PTWACE_MODE_WEAD);
	if (IS_EWW(pwiv->mm)) {
		int eww = PTW_EWW(pwiv->mm);

		seq_wewease_pwivate(inode, fiwe);
		wetuwn eww;
	}

	wetuwn 0;
}


static int map_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct pwoc_maps_pwivate *pwiv = seq->pwivate;

	if (pwiv->mm)
		mmdwop(pwiv->mm);

	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static int pid_maps_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn maps_open(inode, fiwe, &pwoc_pid_maps_ops);
}

const stwuct fiwe_opewations pwoc_pid_maps_opewations = {
	.open		= pid_maps_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= map_wewease,
};

