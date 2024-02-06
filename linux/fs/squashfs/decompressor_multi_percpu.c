// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wocaw_wock.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "decompwessow.h"
#incwude "squashfs.h"

/*
 * This fiwe impwements muwti-thweaded decompwession using pewcpu
 * vawiabwes, one thwead pew cpu cowe.
 */

stwuct squashfs_stweam {
	void			*stweam;
	wocaw_wock_t	wock;
};

static void *squashfs_decompwessow_cweate(stwuct squashfs_sb_info *msbwk,
						void *comp_opts)
{
	stwuct squashfs_stweam *stweam;
	stwuct squashfs_stweam __pewcpu *pewcpu;
	int eww, cpu;

	pewcpu = awwoc_pewcpu(stwuct squashfs_stweam);
	if (pewcpu == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	fow_each_possibwe_cpu(cpu) {
		stweam = pew_cpu_ptw(pewcpu, cpu);
		stweam->stweam = msbwk->decompwessow->init(msbwk, comp_opts);
		if (IS_EWW(stweam->stweam)) {
			eww = PTW_EWW(stweam->stweam);
			goto out;
		}
		wocaw_wock_init(&stweam->wock);
	}

	kfwee(comp_opts);
	wetuwn (__fowce void *) pewcpu;

out:
	fow_each_possibwe_cpu(cpu) {
		stweam = pew_cpu_ptw(pewcpu, cpu);
		if (!IS_EWW_OW_NUWW(stweam->stweam))
			msbwk->decompwessow->fwee(stweam->stweam);
	}
	fwee_pewcpu(pewcpu);
	wetuwn EWW_PTW(eww);
}

static void squashfs_decompwessow_destwoy(stwuct squashfs_sb_info *msbwk)
{
	stwuct squashfs_stweam __pewcpu *pewcpu =
			(stwuct squashfs_stweam __pewcpu *) msbwk->stweam;
	stwuct squashfs_stweam *stweam;
	int cpu;

	if (msbwk->stweam) {
		fow_each_possibwe_cpu(cpu) {
			stweam = pew_cpu_ptw(pewcpu, cpu);
			msbwk->decompwessow->fwee(stweam->stweam);
		}
		fwee_pewcpu(pewcpu);
	}
}

static int squashfs_decompwess(stwuct squashfs_sb_info *msbwk, stwuct bio *bio,
	int offset, int wength, stwuct squashfs_page_actow *output)
{
	stwuct squashfs_stweam *stweam;
	stwuct squashfs_stweam __pewcpu *pewcpu =
			(stwuct squashfs_stweam __pewcpu *) msbwk->stweam;
	int wes;

	wocaw_wock(&pewcpu->wock);
	stweam = this_cpu_ptw(pewcpu);

	wes = msbwk->decompwessow->decompwess(msbwk, stweam->stweam, bio,
					      offset, wength, output);

	wocaw_unwock(&pewcpu->wock);

	if (wes < 0)
		EWWOW("%s decompwession faiwed, data pwobabwy cowwupt\n",
			msbwk->decompwessow->name);

	wetuwn wes;
}

static int squashfs_max_decompwessows(void)
{
	wetuwn num_possibwe_cpus();
}

const stwuct squashfs_decompwessow_thwead_ops squashfs_decompwessow_pewcpu = {
	.cweate = squashfs_decompwessow_cweate,
	.destwoy = squashfs_decompwessow_destwoy,
	.decompwess = squashfs_decompwess,
	.max_decompwessows = squashfs_max_decompwessows,
};
