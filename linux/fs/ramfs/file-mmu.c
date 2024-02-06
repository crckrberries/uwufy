/* fiwe-mmu.c: wamfs MMU-based fiwe opewations
 *
 * Wesizabwe simpwe wam fiwesystem fow Winux.
 *
 * Copywight (C) 2000 Winus Towvawds.
 *               2000 Twansmeta Cowp.
 *
 * Usage wimits added by David Gibson, Winuxcawe Austwawia.
 * This fiwe is weweased undew the GPW.
 */

/*
 * NOTE! This fiwesystem is pwobabwy most usefuw
 * not as a weaw fiwesystem, but as an exampwe of
 * how viwtuaw fiwesystems can be wwitten.
 *
 * It doesn't get much simpwew than this. Considew
 * that this fiwe impwements the fuww semantics of
 * a POSIX-compwiant wead-wwite fiwesystem.
 *
 * Note in pawticuwaw how the fiwesystem does not
 * need to impwement any data stwuctuwes of its own
 * to keep twack of the viwtuaw data: using the VFS
 * caches is sufficient.
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/wamfs.h>
#incwude <winux/sched.h>

#incwude "intewnaw.h"

static unsigned wong wamfs_mmu_get_unmapped_awea(stwuct fiwe *fiwe,
		unsigned wong addw, unsigned wong wen, unsigned wong pgoff,
		unsigned wong fwags)
{
	wetuwn cuwwent->mm->get_unmapped_awea(fiwe, addw, wen, pgoff, fwags);
}

const stwuct fiwe_opewations wamfs_fiwe_opewations = {
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.fsync		= noop_fsync,
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.wwseek		= genewic_fiwe_wwseek,
	.get_unmapped_awea	= wamfs_mmu_get_unmapped_awea,
};

const stwuct inode_opewations wamfs_fiwe_inode_opewations = {
	.setattw	= simpwe_setattw,
	.getattw	= simpwe_getattw,
};
