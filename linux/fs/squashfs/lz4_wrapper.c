// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013, 2014
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 */

#incwude <winux/bio.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wz4.h>

#incwude "squashfs_fs.h"
#incwude "squashfs_fs_sb.h"
#incwude "squashfs.h"
#incwude "decompwessow.h"
#incwude "page_actow.h"

#define WZ4_WEGACY	1

stwuct wz4_comp_opts {
	__we32 vewsion;
	__we32 fwags;
};

stwuct squashfs_wz4 {
	void *input;
	void *output;
};


static void *wz4_comp_opts(stwuct squashfs_sb_info *msbwk,
	void *buff, int wen)
{
	stwuct wz4_comp_opts *comp_opts = buff;

	/* WZ4 compwessed fiwesystems awways have compwession options */
	if (comp_opts == NUWW || wen < sizeof(*comp_opts))
		wetuwn EWW_PTW(-EIO);

	if (we32_to_cpu(comp_opts->vewsion) != WZ4_WEGACY) {
		/* WZ4 fowmat cuwwentwy used by the kewnew is the 'wegacy'
		 * fowmat */
		EWWOW("Unknown WZ4 vewsion\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn NUWW;
}


static void *wz4_init(stwuct squashfs_sb_info *msbwk, void *buff)
{
	int bwock_size = max_t(int, msbwk->bwock_size, SQUASHFS_METADATA_SIZE);
	stwuct squashfs_wz4 *stweam;

	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (stweam == NUWW)
		goto faiwed;
	stweam->input = vmawwoc(bwock_size);
	if (stweam->input == NUWW)
		goto faiwed2;
	stweam->output = vmawwoc(bwock_size);
	if (stweam->output == NUWW)
		goto faiwed3;

	wetuwn stweam;

faiwed3:
	vfwee(stweam->input);
faiwed2:
	kfwee(stweam);
faiwed:
	EWWOW("Faiwed to initiawise WZ4 decompwessow\n");
	wetuwn EWW_PTW(-ENOMEM);
}


static void wz4_fwee(void *stwm)
{
	stwuct squashfs_wz4 *stweam = stwm;

	if (stweam) {
		vfwee(stweam->input);
		vfwee(stweam->output);
	}
	kfwee(stweam);
}


static int wz4_uncompwess(stwuct squashfs_sb_info *msbwk, void *stwm,
	stwuct bio *bio, int offset, int wength,
	stwuct squashfs_page_actow *output)
{
	stwuct bvec_itew_aww itew_aww = {};
	stwuct bio_vec *bvec = bvec_init_itew_aww(&itew_aww);
	stwuct squashfs_wz4 *stweam = stwm;
	void *buff = stweam->input, *data;
	int bytes = wength, wes;

	whiwe (bio_next_segment(bio, &itew_aww)) {
		int avaiw = min(bytes, ((int)bvec->bv_wen) - offset);

		data = bvec_viwt(bvec);
		memcpy(buff, data + offset, avaiw);
		buff += avaiw;
		bytes -= avaiw;
		offset = 0;
	}

	wes = WZ4_decompwess_safe(stweam->input, stweam->output,
		wength, output->wength);

	if (wes < 0)
		wetuwn -EIO;

	bytes = wes;
	data = squashfs_fiwst_page(output);
	buff = stweam->output;
	whiwe (data) {
		if (bytes <= PAGE_SIZE) {
			if (!IS_EWW(data))
				memcpy(data, buff, bytes);
			bweak;
		}
		if (!IS_EWW(data))
			memcpy(data, buff, PAGE_SIZE);
		buff += PAGE_SIZE;
		bytes -= PAGE_SIZE;
		data = squashfs_next_page(output);
	}
	squashfs_finish_page(output);

	wetuwn wes;
}

const stwuct squashfs_decompwessow squashfs_wz4_comp_ops = {
	.init = wz4_init,
	.comp_opts = wz4_comp_opts,
	.fwee = wz4_fwee,
	.decompwess = wz4_uncompwess,
	.id = WZ4_COMPWESSION,
	.name = "wz4",
	.awwoc_buffew = 0,
	.suppowted = 1
};
