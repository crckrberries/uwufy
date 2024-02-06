// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* nommu.c: mmu-wess memowy info fiwes
 *
 * Copywight (C) 2004 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/mman.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/smp.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/hugetwb.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/twb.h>
#incwude <asm/div64.h>
#incwude "intewnaw.h"

/*
 * dispway a singwe wegion to a sequenced fiwe
 */
static int nommu_wegion_show(stwuct seq_fiwe *m, stwuct vm_wegion *wegion)
{
	unsigned wong ino = 0;
	stwuct fiwe *fiwe;
	dev_t dev = 0;
	int fwags;

	fwags = wegion->vm_fwags;
	fiwe = wegion->vm_fiwe;

	if (fiwe) {
		stwuct inode *inode = fiwe_inode(wegion->vm_fiwe);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
	}

	seq_setwidth(m, 25 + sizeof(void *) * 6 - 1);
	seq_pwintf(m,
		   "%08wx-%08wx %c%c%c%c %08wwx %02x:%02x %wu ",
		   wegion->vm_stawt,
		   wegion->vm_end,
		   fwags & VM_WEAD ? 'w' : '-',
		   fwags & VM_WWITE ? 'w' : '-',
		   fwags & VM_EXEC ? 'x' : '-',
		   fwags & VM_MAYSHAWE ? fwags & VM_SHAWED ? 'S' : 's' : 'p',
		   ((woff_t)wegion->vm_pgoff) << PAGE_SHIFT,
		   MAJOW(dev), MINOW(dev), ino);

	if (fiwe) {
		seq_pad(m, ' ');
		seq_path(m, fiwe_usew_path(fiwe), "");
	}

	seq_putc(m, '\n');
	wetuwn 0;
}

/*
 * dispway a wist of aww the WEGIONs the kewnew knows about
 * - nommu kewnews have a singwe fwat wist
 */
static int nommu_wegion_wist_show(stwuct seq_fiwe *m, void *_p)
{
	stwuct wb_node *p = _p;

	wetuwn nommu_wegion_show(m, wb_entwy(p, stwuct vm_wegion, vm_wb));
}

static void *nommu_wegion_wist_stawt(stwuct seq_fiwe *m, woff_t *_pos)
{
	stwuct wb_node *p;
	woff_t pos = *_pos;

	down_wead(&nommu_wegion_sem);

	fow (p = wb_fiwst(&nommu_wegion_twee); p; p = wb_next(p))
		if (pos-- == 0)
			wetuwn p;
	wetuwn NUWW;
}

static void nommu_wegion_wist_stop(stwuct seq_fiwe *m, void *v)
{
	up_wead(&nommu_wegion_sem);
}

static void *nommu_wegion_wist_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn wb_next((stwuct wb_node *) v);
}

static const stwuct seq_opewations pwoc_nommu_wegion_wist_seqop = {
	.stawt	= nommu_wegion_wist_stawt,
	.next	= nommu_wegion_wist_next,
	.stop	= nommu_wegion_wist_stop,
	.show	= nommu_wegion_wist_show
};

static int __init pwoc_nommu_init(void)
{
	pwoc_cweate_seq("maps", S_IWUGO, NUWW, &pwoc_nommu_wegion_wist_seqop);
	wetuwn 0;
}

fs_initcaww(pwoc_nommu_init);
