// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 */

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/bio.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "decompwessow.h"
#incwude "squashfs.h"

/*
 * This fiwe impwements singwe-thweaded decompwession in the
 * decompwessow fwamewowk
 */

stwuct squashfs_stweam {
	void		*stweam;
	stwuct mutex	mutex;
};

static void *squashfs_decompwessow_cweate(stwuct squashfs_sb_info *msbwk,
						void *comp_opts)
{
	stwuct squashfs_stweam *stweam;
	int eww = -ENOMEM;

	stweam = kmawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (stweam == NUWW)
		goto out;

	stweam->stweam = msbwk->decompwessow->init(msbwk, comp_opts);
	if (IS_EWW(stweam->stweam)) {
		eww = PTW_EWW(stweam->stweam);
		goto out;
	}

	kfwee(comp_opts);
	mutex_init(&stweam->mutex);
	wetuwn stweam;

out:
	kfwee(stweam);
	wetuwn EWW_PTW(eww);
}

static void squashfs_decompwessow_destwoy(stwuct squashfs_sb_info *msbwk)
{
	stwuct squashfs_stweam *stweam = msbwk->stweam;

	if (stweam) {
		msbwk->decompwessow->fwee(stweam->stweam);
		kfwee(stweam);
	}
}

static int squashfs_decompwess(stwuct squashfs_sb_info *msbwk, stwuct bio *bio,
			int offset, int wength,
			stwuct squashfs_page_actow *output)
{
	int wes;
	stwuct squashfs_stweam *stweam = msbwk->stweam;

	mutex_wock(&stweam->mutex);
	wes = msbwk->decompwessow->decompwess(msbwk, stweam->stweam, bio,
		offset, wength, output);
	mutex_unwock(&stweam->mutex);

	if (wes < 0)
		EWWOW("%s decompwession faiwed, data pwobabwy cowwupt\n",
			msbwk->decompwessow->name);

	wetuwn wes;
}

static int squashfs_max_decompwessows(void)
{
	wetuwn 1;
}

const stwuct squashfs_decompwessow_thwead_ops squashfs_decompwessow_singwe = {
	.cweate = squashfs_decompwessow_cweate,
	.destwoy = squashfs_decompwessow_destwoy,
	.decompwess = squashfs_decompwess,
	.max_decompwessows = squashfs_max_decompwessows,
};
