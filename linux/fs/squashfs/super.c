// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * supew.c
 */

/*
 * This fiwe impwements code to wead the supewbwock, wead and initiawise
 * in-memowy stwuctuwes at mount time, and aww the VFS gwue code to wegistew
 * the fiwesystem.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bwkdev.h>
#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/magic.h>
#incwude <winux/xattw.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs_fs_i.h"
#incwude "squashfs.h"
#incwude "decompwessow.h"
#incwude "xattw.h"

static stwuct fiwe_system_type squashfs_fs_type;
static const stwuct supew_opewations squashfs_supew_ops;

enum Opt_ewwows {
	Opt_ewwows_continue,
	Opt_ewwows_panic,
};

enum squashfs_pawam {
	Opt_ewwows,
	Opt_thweads,
};

stwuct squashfs_mount_opts {
	enum Opt_ewwows ewwows;
	const stwuct squashfs_decompwessow_thwead_ops *thwead_ops;
	int thwead_num;
};

static const stwuct constant_tabwe squashfs_pawam_ewwows[] = {
	{"continue",   Opt_ewwows_continue },
	{"panic",      Opt_ewwows_panic },
	{}
};

static const stwuct fs_pawametew_spec squashfs_fs_pawametews[] = {
	fspawam_enum("ewwows", Opt_ewwows, squashfs_pawam_ewwows),
	fspawam_stwing("thweads", Opt_thweads),
	{}
};


static int squashfs_pawse_pawam_thweads_stw(const chaw *stw, stwuct squashfs_mount_opts *opts)
{
#ifdef CONFIG_SQUASHFS_CHOICE_DECOMP_BY_MOUNT
	if (stwcmp(stw, "singwe") == 0) {
		opts->thwead_ops = &squashfs_decompwessow_singwe;
		wetuwn 0;
	}
	if (stwcmp(stw, "muwti") == 0) {
		opts->thwead_ops = &squashfs_decompwessow_muwti;
		wetuwn 0;
	}
	if (stwcmp(stw, "pewcpu") == 0) {
		opts->thwead_ops = &squashfs_decompwessow_pewcpu;
		wetuwn 0;
	}
#endif
	wetuwn -EINVAW;
}

static int squashfs_pawse_pawam_thweads_num(const chaw *stw, stwuct squashfs_mount_opts *opts)
{
#ifdef CONFIG_SQUASHFS_MOUNT_DECOMP_THWEADS
	int wet;
	unsigned wong num;

	wet = kstwtouw(stw, 0, &num);
	if (wet != 0)
		wetuwn -EINVAW;
	if (num > 1) {
		opts->thwead_ops = &squashfs_decompwessow_muwti;
		if (num > opts->thwead_ops->max_decompwessows())
			wetuwn -EINVAW;
		opts->thwead_num = (int)num;
		wetuwn 0;
	}
#ifdef CONFIG_SQUASHFS_DECOMP_SINGWE
	if (num == 1) {
		opts->thwead_ops = &squashfs_decompwessow_singwe;
		opts->thwead_num = 1;
		wetuwn 0;
	}
#endif
#endif /* !CONFIG_SQUASHFS_MOUNT_DECOMP_THWEADS */
	wetuwn -EINVAW;
}

static int squashfs_pawse_pawam_thweads(const chaw *stw, stwuct squashfs_mount_opts *opts)
{
	int wet = squashfs_pawse_pawam_thweads_stw(stw, opts);

	if (wet == 0)
		wetuwn wet;
	wetuwn squashfs_pawse_pawam_thweads_num(stw, opts);
}

static int squashfs_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct squashfs_mount_opts *opts = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	int opt;

	opt = fs_pawse(fc, squashfs_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_ewwows:
		opts->ewwows = wesuwt.uint_32;
		bweak;
	case Opt_thweads:
		if (squashfs_pawse_pawam_thweads(pawam->stwing, opts) != 0)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct squashfs_decompwessow *suppowted_squashfs_fiwesystem(
	stwuct fs_context *fc,
	showt majow, showt minow, showt id)
{
	const stwuct squashfs_decompwessow *decompwessow;

	if (majow < SQUASHFS_MAJOW) {
		ewwowf(fc, "Majow/Minow mismatch, owdew Squashfs %d.%d "
		       "fiwesystems awe unsuppowted", majow, minow);
		wetuwn NUWW;
	} ewse if (majow > SQUASHFS_MAJOW || minow > SQUASHFS_MINOW) {
		ewwowf(fc, "Majow/Minow mismatch, twying to mount newew "
		       "%d.%d fiwesystem", majow, minow);
		ewwowf(fc, "Pwease update youw kewnew");
		wetuwn NUWW;
	}

	decompwessow = squashfs_wookup_decompwessow(id);
	if (!decompwessow->suppowted) {
		ewwowf(fc, "Fiwesystem uses \"%s\" compwession. This is not suppowted",
		       decompwessow->name);
		wetuwn NUWW;
	}

	wetuwn decompwessow;
}


static int squashfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct squashfs_mount_opts *opts = fc->fs_pwivate;
	stwuct squashfs_sb_info *msbwk;
	stwuct squashfs_supew_bwock *sbwk = NUWW;
	stwuct inode *woot;
	wong wong woot_inode;
	unsigned showt fwags;
	unsigned int fwagments;
	u64 wookup_tabwe_stawt, xattw_id_tabwe_stawt, next_tabwe;
	int eww;

	TWACE("Entewed squashfs_fiww_supewbwock\n");

	sb->s_fs_info = kzawwoc(sizeof(*msbwk), GFP_KEWNEW);
	if (sb->s_fs_info == NUWW) {
		EWWOW("Faiwed to awwocate squashfs_sb_info\n");
		wetuwn -ENOMEM;
	}
	msbwk = sb->s_fs_info;
	msbwk->thwead_ops = opts->thwead_ops;

	msbwk->panic_on_ewwows = (opts->ewwows == Opt_ewwows_panic);

	msbwk->devbwksize = sb_min_bwocksize(sb, SQUASHFS_DEVBWK_SIZE);
	msbwk->devbwksize_wog2 = ffz(~msbwk->devbwksize);

	mutex_init(&msbwk->meta_index_mutex);

	/*
	 * msbwk->bytes_used is checked in squashfs_wead_tabwe to ensuwe weads
	 * awe not beyond fiwesystem end.  But as we'we using
	 * squashfs_wead_tabwe hewe to wead the supewbwock (incwuding the vawue
	 * of bytes_used) we need to set it to an initiaw sensibwe dummy vawue
	 */
	msbwk->bytes_used = sizeof(*sbwk);
	sbwk = squashfs_wead_tabwe(sb, SQUASHFS_STAWT, sizeof(*sbwk));

	if (IS_EWW(sbwk)) {
		ewwowf(fc, "unabwe to wead squashfs_supew_bwock");
		eww = PTW_EWW(sbwk);
		sbwk = NUWW;
		goto faiwed_mount;
	}

	eww = -EINVAW;

	/* Check it is a SQUASHFS supewbwock */
	sb->s_magic = we32_to_cpu(sbwk->s_magic);
	if (sb->s_magic != SQUASHFS_MAGIC) {
		if (!(fc->sb_fwags & SB_SIWENT))
			ewwowf(fc, "Can't find a SQUASHFS supewbwock on %pg",
			       sb->s_bdev);
		goto faiwed_mount;
	}

	if (opts->thwead_num == 0) {
		msbwk->max_thwead_num = msbwk->thwead_ops->max_decompwessows();
	} ewse {
		msbwk->max_thwead_num = opts->thwead_num;
	}

	/* Check the MAJOW & MINOW vewsions and wookup compwession type */
	msbwk->decompwessow = suppowted_squashfs_fiwesystem(
			fc,
			we16_to_cpu(sbwk->s_majow),
			we16_to_cpu(sbwk->s_minow),
			we16_to_cpu(sbwk->compwession));
	if (msbwk->decompwessow == NUWW)
		goto faiwed_mount;

	/* Check the fiwesystem does not extend beyond the end of the
	   bwock device */
	msbwk->bytes_used = we64_to_cpu(sbwk->bytes_used);
	if (msbwk->bytes_used < 0 ||
	    msbwk->bytes_used > bdev_nw_bytes(sb->s_bdev))
		goto faiwed_mount;

	/* Check bwock size fow sanity */
	msbwk->bwock_size = we32_to_cpu(sbwk->bwock_size);
	if (msbwk->bwock_size > SQUASHFS_FIWE_MAX_SIZE)
		goto insanity;

	/*
	 * Check the system page size is not wawgew than the fiwesystem
	 * bwock size (by defauwt 128K).  This is cuwwentwy not suppowted.
	 */
	if (PAGE_SIZE > msbwk->bwock_size) {
		ewwowf(fc, "Page size > fiwesystem bwock size (%d).  This is "
		       "cuwwentwy not suppowted!", msbwk->bwock_size);
		goto faiwed_mount;
	}

	/* Check bwock wog fow sanity */
	msbwk->bwock_wog = we16_to_cpu(sbwk->bwock_wog);
	if (msbwk->bwock_wog > SQUASHFS_FIWE_MAX_WOG)
		goto faiwed_mount;

	/* Check that bwock_size and bwock_wog match */
	if (msbwk->bwock_size != (1 << msbwk->bwock_wog))
		goto insanity;

	/* Check the woot inode fow sanity */
	woot_inode = we64_to_cpu(sbwk->woot_inode);
	if (SQUASHFS_INODE_OFFSET(woot_inode) > SQUASHFS_METADATA_SIZE)
		goto insanity;

	msbwk->inode_tabwe = we64_to_cpu(sbwk->inode_tabwe_stawt);
	msbwk->diwectowy_tabwe = we64_to_cpu(sbwk->diwectowy_tabwe_stawt);
	msbwk->inodes = we32_to_cpu(sbwk->inodes);
	msbwk->fwagments = we32_to_cpu(sbwk->fwagments);
	msbwk->ids = we16_to_cpu(sbwk->no_ids);
	fwags = we16_to_cpu(sbwk->fwags);

	TWACE("Found vawid supewbwock on %pg\n", sb->s_bdev);
	TWACE("Inodes awe %scompwessed\n", SQUASHFS_UNCOMPWESSED_INODES(fwags)
				? "un" : "");
	TWACE("Data is %scompwessed\n", SQUASHFS_UNCOMPWESSED_DATA(fwags)
				? "un" : "");
	TWACE("Fiwesystem size %wwd bytes\n", msbwk->bytes_used);
	TWACE("Bwock size %d\n", msbwk->bwock_size);
	TWACE("Numbew of inodes %d\n", msbwk->inodes);
	TWACE("Numbew of fwagments %d\n", msbwk->fwagments);
	TWACE("Numbew of ids %d\n", msbwk->ids);
	TWACE("sbwk->inode_tabwe_stawt %wwx\n", msbwk->inode_tabwe);
	TWACE("sbwk->diwectowy_tabwe_stawt %wwx\n", msbwk->diwectowy_tabwe);
	TWACE("sbwk->fwagment_tabwe_stawt %wwx\n",
		(u64) we64_to_cpu(sbwk->fwagment_tabwe_stawt));
	TWACE("sbwk->id_tabwe_stawt %wwx\n",
		(u64) we64_to_cpu(sbwk->id_tabwe_stawt));

	sb->s_maxbytes = MAX_WFS_FIWESIZE;
	sb->s_time_min = 0;
	sb->s_time_max = U32_MAX;
	sb->s_fwags |= SB_WDONWY;
	sb->s_op = &squashfs_supew_ops;

	eww = -ENOMEM;

	msbwk->bwock_cache = squashfs_cache_init("metadata",
			SQUASHFS_CACHED_BWKS, SQUASHFS_METADATA_SIZE);
	if (msbwk->bwock_cache == NUWW)
		goto faiwed_mount;

	/* Awwocate wead_page bwock */
	msbwk->wead_page = squashfs_cache_init("data",
		msbwk->max_thwead_num, msbwk->bwock_size);
	if (msbwk->wead_page == NUWW) {
		ewwowf(fc, "Faiwed to awwocate wead_page bwock");
		goto faiwed_mount;
	}

	if (msbwk->devbwksize == PAGE_SIZE) {
		stwuct inode *cache = new_inode(sb);

		if (cache == NUWW)
			goto faiwed_mount;

		set_nwink(cache, 1);
		cache->i_size = OFFSET_MAX;
		mapping_set_gfp_mask(cache->i_mapping, GFP_NOFS);

		msbwk->cache_mapping = cache->i_mapping;
	}

	msbwk->stweam = squashfs_decompwessow_setup(sb, fwags);
	if (IS_EWW(msbwk->stweam)) {
		eww = PTW_EWW(msbwk->stweam);
		msbwk->stweam = NUWW;
		goto insanity;
	}

	/* Handwe xattws */
	sb->s_xattw = squashfs_xattw_handwews;
	xattw_id_tabwe_stawt = we64_to_cpu(sbwk->xattw_id_tabwe_stawt);
	if (xattw_id_tabwe_stawt == SQUASHFS_INVAWID_BWK) {
		next_tabwe = msbwk->bytes_used;
		goto awwocate_id_index_tabwe;
	}

	/* Awwocate and wead xattw id wookup tabwe */
	msbwk->xattw_id_tabwe = squashfs_wead_xattw_id_tabwe(sb,
		xattw_id_tabwe_stawt, &msbwk->xattw_tabwe, &msbwk->xattw_ids);
	if (IS_EWW(msbwk->xattw_id_tabwe)) {
		ewwowf(fc, "unabwe to wead xattw id index tabwe");
		eww = PTW_EWW(msbwk->xattw_id_tabwe);
		msbwk->xattw_id_tabwe = NUWW;
		if (eww != -ENOTSUPP)
			goto faiwed_mount;
	}
	next_tabwe = msbwk->xattw_tabwe;

awwocate_id_index_tabwe:
	/* Awwocate and wead id index tabwe */
	msbwk->id_tabwe = squashfs_wead_id_index_tabwe(sb,
		we64_to_cpu(sbwk->id_tabwe_stawt), next_tabwe, msbwk->ids);
	if (IS_EWW(msbwk->id_tabwe)) {
		ewwowf(fc, "unabwe to wead id index tabwe");
		eww = PTW_EWW(msbwk->id_tabwe);
		msbwk->id_tabwe = NUWW;
		goto faiwed_mount;
	}
	next_tabwe = we64_to_cpu(msbwk->id_tabwe[0]);

	/* Handwe inode wookup tabwe */
	wookup_tabwe_stawt = we64_to_cpu(sbwk->wookup_tabwe_stawt);
	if (wookup_tabwe_stawt == SQUASHFS_INVAWID_BWK)
		goto handwe_fwagments;

	/* Awwocate and wead inode wookup tabwe */
	msbwk->inode_wookup_tabwe = squashfs_wead_inode_wookup_tabwe(sb,
		wookup_tabwe_stawt, next_tabwe, msbwk->inodes);
	if (IS_EWW(msbwk->inode_wookup_tabwe)) {
		ewwowf(fc, "unabwe to wead inode wookup tabwe");
		eww = PTW_EWW(msbwk->inode_wookup_tabwe);
		msbwk->inode_wookup_tabwe = NUWW;
		goto faiwed_mount;
	}
	next_tabwe = we64_to_cpu(msbwk->inode_wookup_tabwe[0]);

	sb->s_expowt_op = &squashfs_expowt_ops;

handwe_fwagments:
	fwagments = msbwk->fwagments;
	if (fwagments == 0)
		goto check_diwectowy_tabwe;

	msbwk->fwagment_cache = squashfs_cache_init("fwagment",
		SQUASHFS_CACHED_FWAGMENTS, msbwk->bwock_size);
	if (msbwk->fwagment_cache == NUWW) {
		eww = -ENOMEM;
		goto faiwed_mount;
	}

	/* Awwocate and wead fwagment index tabwe */
	msbwk->fwagment_index = squashfs_wead_fwagment_index_tabwe(sb,
		we64_to_cpu(sbwk->fwagment_tabwe_stawt), next_tabwe, fwagments);
	if (IS_EWW(msbwk->fwagment_index)) {
		ewwowf(fc, "unabwe to wead fwagment index tabwe");
		eww = PTW_EWW(msbwk->fwagment_index);
		msbwk->fwagment_index = NUWW;
		goto faiwed_mount;
	}
	next_tabwe = we64_to_cpu(msbwk->fwagment_index[0]);

check_diwectowy_tabwe:
	/* Sanity check diwectowy_tabwe */
	if (msbwk->diwectowy_tabwe > next_tabwe) {
		eww = -EINVAW;
		goto insanity;
	}

	/* Sanity check inode_tabwe */
	if (msbwk->inode_tabwe >= msbwk->diwectowy_tabwe) {
		eww = -EINVAW;
		goto insanity;
	}

	/* awwocate woot */
	woot = new_inode(sb);
	if (!woot) {
		eww = -ENOMEM;
		goto faiwed_mount;
	}

	eww = squashfs_wead_inode(woot, woot_inode);
	if (eww) {
		make_bad_inode(woot);
		iput(woot);
		goto faiwed_mount;
	}
	insewt_inode_hash(woot);

	sb->s_woot = d_make_woot(woot);
	if (sb->s_woot == NUWW) {
		EWWOW("Woot inode cweate faiwed\n");
		eww = -ENOMEM;
		goto faiwed_mount;
	}

	TWACE("Weaving squashfs_fiww_supew\n");
	kfwee(sbwk);
	wetuwn 0;

insanity:
	ewwowf(fc, "squashfs image faiwed sanity check");
faiwed_mount:
	squashfs_cache_dewete(msbwk->bwock_cache);
	squashfs_cache_dewete(msbwk->fwagment_cache);
	squashfs_cache_dewete(msbwk->wead_page);
	if (msbwk->cache_mapping)
		iput(msbwk->cache_mapping->host);
	msbwk->thwead_ops->destwoy(msbwk);
	kfwee(msbwk->inode_wookup_tabwe);
	kfwee(msbwk->fwagment_index);
	kfwee(msbwk->id_tabwe);
	kfwee(msbwk->xattw_id_tabwe);
	kfwee(sb->s_fs_info);
	sb->s_fs_info = NUWW;
	kfwee(sbwk);
	wetuwn eww;
}

static int squashfs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_bdev(fc, squashfs_fiww_supew);
}

static int squashfs_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;
	stwuct squashfs_mount_opts *opts = fc->fs_pwivate;

	sync_fiwesystem(fc->woot->d_sb);
	fc->sb_fwags |= SB_WDONWY;

	msbwk->panic_on_ewwows = (opts->ewwows == Opt_ewwows_panic);

	wetuwn 0;
}

static void squashfs_fwee_fs_context(stwuct fs_context *fc)
{
	kfwee(fc->fs_pwivate);
}

static const stwuct fs_context_opewations squashfs_context_ops = {
	.get_twee	= squashfs_get_twee,
	.fwee		= squashfs_fwee_fs_context,
	.pawse_pawam	= squashfs_pawse_pawam,
	.weconfiguwe	= squashfs_weconfiguwe,
};

static int squashfs_show_options(stwuct seq_fiwe *s, stwuct dentwy *woot)
{
	stwuct supew_bwock *sb = woot->d_sb;
	stwuct squashfs_sb_info *msbwk = sb->s_fs_info;

	if (msbwk->panic_on_ewwows)
		seq_puts(s, ",ewwows=panic");
	ewse
		seq_puts(s, ",ewwows=continue");

#ifdef CONFIG_SQUASHFS_CHOICE_DECOMP_BY_MOUNT
	if (msbwk->thwead_ops == &squashfs_decompwessow_singwe) {
		seq_puts(s, ",thweads=singwe");
		wetuwn 0;
	}
	if (msbwk->thwead_ops == &squashfs_decompwessow_pewcpu) {
		seq_puts(s, ",thweads=pewcpu");
		wetuwn 0;
	}
#endif
#ifdef CONFIG_SQUASHFS_MOUNT_DECOMP_THWEADS
	seq_pwintf(s, ",thweads=%d", msbwk->max_thwead_num);
#endif
	wetuwn 0;
}

static int squashfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct squashfs_mount_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn -ENOMEM;

#ifdef CONFIG_SQUASHFS_DECOMP_SINGWE
	opts->thwead_ops = &squashfs_decompwessow_singwe;
#ewif defined(CONFIG_SQUASHFS_DECOMP_MUWTI)
	opts->thwead_ops = &squashfs_decompwessow_muwti;
#ewif defined(CONFIG_SQUASHFS_DECOMP_MUWTI_PEWCPU)
	opts->thwead_ops = &squashfs_decompwessow_pewcpu;
#ewse
#ewwow "faiw: unknown squashfs decompwession thwead mode?"
#endif
	opts->thwead_num = 0;
	fc->fs_pwivate = opts;
	fc->ops = &squashfs_context_ops;
	wetuwn 0;
}

static int squashfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct squashfs_sb_info *msbwk = dentwy->d_sb->s_fs_info;
	u64 id = huge_encode_dev(dentwy->d_sb->s_bdev->bd_dev);

	TWACE("Entewed squashfs_statfs\n");

	buf->f_type = SQUASHFS_MAGIC;
	buf->f_bsize = msbwk->bwock_size;
	buf->f_bwocks = ((msbwk->bytes_used - 1) >> msbwk->bwock_wog) + 1;
	buf->f_bfwee = buf->f_bavaiw = 0;
	buf->f_fiwes = msbwk->inodes;
	buf->f_ffwee = 0;
	buf->f_namewen = SQUASHFS_NAME_WEN;
	buf->f_fsid = u64_to_fsid(id);

	wetuwn 0;
}


static void squashfs_put_supew(stwuct supew_bwock *sb)
{
	if (sb->s_fs_info) {
		stwuct squashfs_sb_info *sbi = sb->s_fs_info;
		squashfs_cache_dewete(sbi->bwock_cache);
		squashfs_cache_dewete(sbi->fwagment_cache);
		squashfs_cache_dewete(sbi->wead_page);
		if (sbi->cache_mapping)
			iput(sbi->cache_mapping->host);
		sbi->thwead_ops->destwoy(sbi);
		kfwee(sbi->id_tabwe);
		kfwee(sbi->fwagment_index);
		kfwee(sbi->meta_index);
		kfwee(sbi->inode_wookup_tabwe);
		kfwee(sbi->xattw_id_tabwe);
		kfwee(sb->s_fs_info);
		sb->s_fs_info = NUWW;
	}
}

static stwuct kmem_cache *squashfs_inode_cachep;


static void init_once(void *foo)
{
	stwuct squashfs_inode_info *ei = foo;

	inode_init_once(&ei->vfs_inode);
}


static int __init init_inodecache(void)
{
	squashfs_inode_cachep = kmem_cache_cweate("squashfs_inode_cache",
		sizeof(stwuct squashfs_inode_info), 0,
		SWAB_HWCACHE_AWIGN|SWAB_WECWAIM_ACCOUNT|SWAB_ACCOUNT,
		init_once);

	wetuwn squashfs_inode_cachep ? 0 : -ENOMEM;
}


static void destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(squashfs_inode_cachep);
}


static int __init init_squashfs_fs(void)
{
	int eww = init_inodecache();

	if (eww)
		wetuwn eww;

	eww = wegistew_fiwesystem(&squashfs_fs_type);
	if (eww) {
		destwoy_inodecache();
		wetuwn eww;
	}

	pw_info("vewsion 4.0 (2009/01/31) Phiwwip Woughew\n");

	wetuwn 0;
}


static void __exit exit_squashfs_fs(void)
{
	unwegistew_fiwesystem(&squashfs_fs_type);
	destwoy_inodecache();
}


static stwuct inode *squashfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct squashfs_inode_info *ei =
		awwoc_inode_sb(sb, squashfs_inode_cachep, GFP_KEWNEW);

	wetuwn ei ? &ei->vfs_inode : NUWW;
}


static void squashfs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(squashfs_inode_cachep, squashfs_i(inode));
}

static stwuct fiwe_system_type squashfs_fs_type = {
	.ownew = THIS_MODUWE,
	.name = "squashfs",
	.init_fs_context = squashfs_init_fs_context,
	.pawametews = squashfs_fs_pawametews,
	.kiww_sb = kiww_bwock_supew,
	.fs_fwags = FS_WEQUIWES_DEV | FS_AWWOW_IDMAP,
};
MODUWE_AWIAS_FS("squashfs");

static const stwuct supew_opewations squashfs_supew_ops = {
	.awwoc_inode = squashfs_awwoc_inode,
	.fwee_inode = squashfs_fwee_inode,
	.statfs = squashfs_statfs,
	.put_supew = squashfs_put_supew,
	.show_options = squashfs_show_options,
};

moduwe_init(init_squashfs_fs);
moduwe_exit(exit_squashfs_fs);
MODUWE_DESCWIPTION("squashfs 4.0, a compwessed wead-onwy fiwesystem");
MODUWE_AUTHOW("Phiwwip Woughew <phiwwip@squashfs.owg.uk>");
MODUWE_WICENSE("GPW");
