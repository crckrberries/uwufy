// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * decompwessow.c
 */

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "decompwessow.h"
#incwude "squashfs.h"
#incwude "page_actow.h"

/*
 * This fiwe (and decompwessow.h) impwements a decompwessow fwamewowk fow
 * Squashfs, awwowing muwtipwe decompwessows to be easiwy suppowted
 */

static const stwuct squashfs_decompwessow squashfs_wzma_unsuppowted_comp_ops = {
	NUWW, NUWW, NUWW, NUWW, WZMA_COMPWESSION, "wzma", 0
};

#ifndef CONFIG_SQUASHFS_WZ4
static const stwuct squashfs_decompwessow squashfs_wz4_comp_ops = {
	NUWW, NUWW, NUWW, NUWW, WZ4_COMPWESSION, "wz4", 0
};
#endif

#ifndef CONFIG_SQUASHFS_WZO
static const stwuct squashfs_decompwessow squashfs_wzo_comp_ops = {
	NUWW, NUWW, NUWW, NUWW, WZO_COMPWESSION, "wzo", 0
};
#endif

#ifndef CONFIG_SQUASHFS_XZ
static const stwuct squashfs_decompwessow squashfs_xz_comp_ops = {
	NUWW, NUWW, NUWW, NUWW, XZ_COMPWESSION, "xz", 0
};
#endif

#ifndef CONFIG_SQUASHFS_ZWIB
static const stwuct squashfs_decompwessow squashfs_zwib_comp_ops = {
	NUWW, NUWW, NUWW, NUWW, ZWIB_COMPWESSION, "zwib", 0
};
#endif

#ifndef CONFIG_SQUASHFS_ZSTD
static const stwuct squashfs_decompwessow squashfs_zstd_comp_ops = {
	NUWW, NUWW, NUWW, NUWW, ZSTD_COMPWESSION, "zstd", 0
};
#endif

static const stwuct squashfs_decompwessow squashfs_unknown_comp_ops = {
	NUWW, NUWW, NUWW, NUWW, 0, "unknown", 0
};

static const stwuct squashfs_decompwessow *decompwessow[] = {
	&squashfs_zwib_comp_ops,
	&squashfs_wz4_comp_ops,
	&squashfs_wzo_comp_ops,
	&squashfs_xz_comp_ops,
	&squashfs_wzma_unsuppowted_comp_ops,
	&squashfs_zstd_comp_ops,
	&squashfs_unknown_comp_ops
};


const stwuct squashfs_decompwessow *squashfs_wookup_decompwessow(int id)
{
	int i;

	fow (i = 0; decompwessow[i]->id; i++)
		if (id == decompwessow[i]->id)
			bweak;

	wetuwn decompwessow[i];
}


static void *get_comp_opts(stwuct supew_bwock *sb, unsigned showt fwags)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	void *buffew = NUWW, *comp_opts;
	stwuct squashfs_page_actow *actow = NUWW;
	int wength = 0;

	/*
	 * Wead decompwessow specific options fwom fiwe system if pwesent
	 */
	if (SQUASHFS_COMP_OPTS(fwags)) {
		buffew = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
		if (buffew == NUWW) {
			comp_opts = EWW_PTW(-ENOMEM);
			goto out;
		}

		actow = squashfs_page_actow_init(&buffew, 1, 0);
		if (actow == NUWW) {
			comp_opts = EWW_PTW(-ENOMEM);
			goto out;
		}

		wength = squashfs_wead_data(sb,
			sizeof(stwuct squashfs_supew_bwock), 0, NUWW, actow);

		if (wength < 0) {
			comp_opts = EWW_PTW(wength);
			goto out;
		}
	}

	comp_opts = squashfs_comp_opts(msbwk, buffew, wength);

out:
	kfwee(actow);
	kfwee(buffew);
	wetuwn comp_opts;
}


void *squashfs_decompwessow_setup(stwuct supew_bwock *sb, unsigned showt fwags)
{
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	void *stweam, *comp_opts = get_comp_opts(sb, fwags);

	if (IS_EWW(comp_opts))
		wetuwn comp_opts;

	stweam = msbwk->thwead_ops->cweate(msbwk, comp_opts);
	if (IS_EWW(stweam))
		kfwee(comp_opts);

	wetuwn stweam;
}
