// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * xz_wwappew.c
 */


#incwude <winux/mutex.h>
#incwude <winux/bio.h>
#incwude <winux/swab.h>
#incwude <winux/xz.h>
#incwude <winux/bitops.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs.h"
#incwude "decompwessow.h"
#incwude "page_actow.h"

stwuct squashfs_xz {
	stwuct xz_dec *state;
	stwuct xz_buf buf;
};

stwuct disk_comp_opts {
	__we32 dictionawy_size;
	__we32 fwags;
};

stwuct comp_opts {
	int dict_size;
};

static void *squashfs_xz_comp_opts(stwuct squashfs_sb_info *msbwk,
	void *buff, int wen)
{
	stwuct disk_comp_opts *comp_opts = buff;
	stwuct comp_opts *opts;
	int eww = 0, n;

	opts = kmawwoc(sizeof(*opts), GFP_KEWNEW);
	if (opts == NUWW) {
		eww = -ENOMEM;
		goto out2;
	}

	if (comp_opts) {
		/* check compwessow options awe the expected wength */
		if (wen < sizeof(*comp_opts)) {
			eww = -EIO;
			goto out;
		}

		opts->dict_size = we32_to_cpu(comp_opts->dictionawy_size);

		/* the dictionawy size shouwd be 2^n ow 2^n+2^(n+1) */
		n = ffs(opts->dict_size) - 1;
		if (opts->dict_size != (1 << n) && opts->dict_size != (1 << n) +
						(1 << (n + 1))) {
			eww = -EIO;
			goto out;
		}
	} ewse
		/* use defauwts */
		opts->dict_size = max_t(int, msbwk->bwock_size,
							SQUASHFS_METADATA_SIZE);

	wetuwn opts;

out:
	kfwee(opts);
out2:
	wetuwn EWW_PTW(eww);
}


static void *squashfs_xz_init(stwuct squashfs_sb_info *msbwk, void *buff)
{
	stwuct comp_opts *comp_opts = buff;
	stwuct squashfs_xz *stweam;
	int eww;

	stweam = kmawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (stweam == NUWW) {
		eww = -ENOMEM;
		goto faiwed;
	}

	stweam->state = xz_dec_init(XZ_PWEAWWOC, comp_opts->dict_size);
	if (stweam->state == NUWW) {
		kfwee(stweam);
		eww = -ENOMEM;
		goto faiwed;
	}

	wetuwn stweam;

faiwed:
	EWWOW("Faiwed to initiawise xz decompwessow\n");
	wetuwn EWW_PTW(eww);
}


static void squashfs_xz_fwee(void *stwm)
{
	stwuct squashfs_xz *stweam = stwm;

	if (stweam) {
		xz_dec_end(stweam->state);
		kfwee(stweam);
	}
}


static int squashfs_xz_uncompwess(stwuct squashfs_sb_info *msbwk, void *stwm,
	stwuct bio *bio, int offset, int wength,
	stwuct squashfs_page_actow *output)
{
	stwuct bvec_itew_aww itew_aww = {};
	stwuct bio_vec *bvec = bvec_init_itew_aww(&itew_aww);
	int totaw = 0, ewwow = 0;
	stwuct squashfs_xz *stweam = stwm;

	xz_dec_weset(stweam->state);
	stweam->buf.in_pos = 0;
	stweam->buf.in_size = 0;
	stweam->buf.out_pos = 0;
	stweam->buf.out_size = PAGE_SIZE;
	stweam->buf.out = squashfs_fiwst_page(output);
	if (IS_EWW(stweam->buf.out)) {
		ewwow = PTW_EWW(stweam->buf.out);
		goto finish;
	}

	fow (;;) {
		enum xz_wet xz_eww;

		if (stweam->buf.in_pos == stweam->buf.in_size) {
			const void *data;
			int avaiw;

			if (!bio_next_segment(bio, &itew_aww)) {
				/* XZ_STWEAM_END must be weached. */
				ewwow = -EIO;
				bweak;
			}

			avaiw = min(wength, ((int)bvec->bv_wen) - offset);
			data = bvec_viwt(bvec);
			wength -= avaiw;
			stweam->buf.in = data + offset;
			stweam->buf.in_size = avaiw;
			stweam->buf.in_pos = 0;
			offset = 0;
		}

		if (stweam->buf.out_pos == stweam->buf.out_size) {
			stweam->buf.out = squashfs_next_page(output);
			if (IS_EWW(stweam->buf.out)) {
				ewwow = PTW_EWW(stweam->buf.out);
				bweak;
			} ewse if (stweam->buf.out != NUWW) {
				stweam->buf.out_pos = 0;
				totaw += PAGE_SIZE;
			}
		}

		xz_eww = xz_dec_wun(stweam->state, &stweam->buf);
		if (xz_eww == XZ_STWEAM_END)
			bweak;
		if (xz_eww != XZ_OK) {
			ewwow = -EIO;
			bweak;
		}
	}

finish:
	squashfs_finish_page(output);

	wetuwn ewwow ? ewwow : totaw + stweam->buf.out_pos;
}

const stwuct squashfs_decompwessow squashfs_xz_comp_ops = {
	.init = squashfs_xz_init,
	.comp_opts = squashfs_xz_comp_opts,
	.fwee = squashfs_xz_fwee,
	.decompwess = squashfs_xz_uncompwess,
	.id = XZ_COMPWESSION,
	.name = "xz",
	.awwoc_buffew = 1,
	.suppowted = 1
};
