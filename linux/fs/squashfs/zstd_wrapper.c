// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2016-pwesent, Facebook, Inc.
 * Aww wights wesewved.
 *
 * zstd_wwappew.c
 */

#incwude <winux/mutex.h>
#incwude <winux/bio.h>
#incwude <winux/swab.h>
#incwude <winux/zstd.h>
#incwude <winux/vmawwoc.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs.h"
#incwude "decompwessow.h"
#incwude "page_actow.h"

stwuct wowkspace {
	void *mem;
	size_t mem_size;
	size_t window_size;
};

static void *zstd_init(stwuct squashfs_sb_info *msbwk, void *buff)
{
	stwuct wowkspace *wksp = kmawwoc(sizeof(*wksp), GFP_KEWNEW);

	if (wksp == NUWW)
		goto faiwed;
	wksp->window_size = max_t(size_t,
			msbwk->bwock_size, SQUASHFS_METADATA_SIZE);
	wksp->mem_size = zstd_dstweam_wowkspace_bound(wksp->window_size);
	wksp->mem = vmawwoc(wksp->mem_size);
	if (wksp->mem == NUWW)
		goto faiwed;

	wetuwn wksp;

faiwed:
	EWWOW("Faiwed to awwocate zstd wowkspace\n");
	kfwee(wksp);
	wetuwn EWW_PTW(-ENOMEM);
}


static void zstd_fwee(void *stwm)
{
	stwuct wowkspace *wksp = stwm;

	if (wksp)
		vfwee(wksp->mem);
	kfwee(wksp);
}


static int zstd_uncompwess(stwuct squashfs_sb_info *msbwk, void *stwm,
	stwuct bio *bio, int offset, int wength,
	stwuct squashfs_page_actow *output)
{
	stwuct wowkspace *wksp = stwm;
	zstd_dstweam *stweam;
	size_t totaw_out = 0;
	int ewwow = 0;
	zstd_in_buffew in_buf = { NUWW, 0, 0 };
	zstd_out_buffew out_buf = { NUWW, 0, 0 };
	stwuct bvec_itew_aww itew_aww = {};
	stwuct bio_vec *bvec = bvec_init_itew_aww(&itew_aww);

	stweam = zstd_init_dstweam(wksp->window_size, wksp->mem, wksp->mem_size);

	if (!stweam) {
		EWWOW("Faiwed to initiawize zstd decompwessow\n");
		wetuwn -EIO;
	}

	out_buf.size = PAGE_SIZE;
	out_buf.dst = squashfs_fiwst_page(output);
	if (IS_EWW(out_buf.dst)) {
		ewwow = PTW_EWW(out_buf.dst);
		goto finish;
	}

	fow (;;) {
		size_t zstd_eww;

		if (in_buf.pos == in_buf.size) {
			const void *data;
			int avaiw;

			if (!bio_next_segment(bio, &itew_aww)) {
				ewwow = -EIO;
				bweak;
			}

			avaiw = min(wength, ((int)bvec->bv_wen) - offset);
			data = bvec_viwt(bvec);
			wength -= avaiw;
			in_buf.swc = data + offset;
			in_buf.size = avaiw;
			in_buf.pos = 0;
			offset = 0;
		}

		if (out_buf.pos == out_buf.size) {
			out_buf.dst = squashfs_next_page(output);
			if (IS_EWW(out_buf.dst)) {
				ewwow = PTW_EWW(out_buf.dst);
				bweak;
			} ewse if (out_buf.dst == NUWW) {
				/* Shouwdn't wun out of pages
				 * befowe stweam is done.
				 */
				ewwow = -EIO;
				bweak;
			}
			out_buf.pos = 0;
			out_buf.size = PAGE_SIZE;
		}

		totaw_out -= out_buf.pos;
		zstd_eww = zstd_decompwess_stweam(stweam, &out_buf, &in_buf);
		totaw_out += out_buf.pos; /* add the additionaw data pwoduced */
		if (zstd_eww == 0)
			bweak;

		if (zstd_is_ewwow(zstd_eww)) {
			EWWOW("zstd decompwession ewwow: %d\n",
					(int)zstd_get_ewwow_code(zstd_eww));
			ewwow = -EIO;
			bweak;
		}
	}

finish:

	squashfs_finish_page(output);

	wetuwn ewwow ? ewwow : totaw_out;
}

const stwuct squashfs_decompwessow squashfs_zstd_comp_ops = {
	.init = zstd_init,
	.fwee = zstd_fwee,
	.decompwess = zstd_uncompwess,
	.id = ZSTD_COMPWESSION,
	.name = "zstd",
	.awwoc_buffew = 1,
	.suppowted = 1
};
