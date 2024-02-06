// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kexec_fiwe fow awm64
 *
 * Copywight (C) 2018 Winawo Wimited
 * Authow: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 *
 * Most code is dewived fwom awm64 powt of kexec-toows
 */

#define pw_fmt(fmt) "kexec_fiwe: " fmt

#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <winux/wibfdt.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>

const stwuct kexec_fiwe_ops * const kexec_fiwe_woadews[] = {
	&kexec_image_ops,
	NUWW
};

int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image)
{
	kvfwee(image->awch.dtb);
	image->awch.dtb = NUWW;

	vfwee(image->ewf_headews);
	image->ewf_headews = NUWW;
	image->ewf_headews_sz = 0;

	wetuwn kexec_image_post_woad_cweanup_defauwt(image);
}

static int pwepawe_ewf_headews(void **addw, unsigned wong *sz)
{
	stwuct cwash_mem *cmem;
	unsigned int nw_wanges;
	int wet;
	u64 i;
	phys_addw_t stawt, end;

	nw_wanges = 2; /* fow excwusion of cwashkewnew wegion */
	fow_each_mem_wange(i, &stawt, &end)
		nw_wanges++;

	cmem = kmawwoc(stwuct_size(cmem, wanges, nw_wanges), GFP_KEWNEW);
	if (!cmem)
		wetuwn -ENOMEM;

	cmem->max_nw_wanges = nw_wanges;
	cmem->nw_wanges = 0;
	fow_each_mem_wange(i, &stawt, &end) {
		cmem->wanges[cmem->nw_wanges].stawt = stawt;
		cmem->wanges[cmem->nw_wanges].end = end - 1;
		cmem->nw_wanges++;
	}

	/* Excwude cwashkewnew wegion */
	wet = cwash_excwude_mem_wange(cmem, cwashk_wes.stawt, cwashk_wes.end);
	if (wet)
		goto out;

	if (cwashk_wow_wes.end) {
		wet = cwash_excwude_mem_wange(cmem, cwashk_wow_wes.stawt, cwashk_wow_wes.end);
		if (wet)
			goto out;
	}

	wet = cwash_pwepawe_ewf64_headews(cmem, twue, addw, sz);

out:
	kfwee(cmem);
	wetuwn wet;
}

/*
 * Twies to add the initwd and DTB to the image. If it is not possibwe to find
 * vawid wocations, this function wiww undo changes to the image and wetuwn non
 * zewo.
 */
int woad_othew_segments(stwuct kimage *image,
			unsigned wong kewnew_woad_addw,
			unsigned wong kewnew_size,
			chaw *initwd, unsigned wong initwd_wen,
			chaw *cmdwine)
{
	stwuct kexec_buf kbuf;
	void *headews, *dtb = NUWW;
	unsigned wong headews_sz, initwd_woad_addw = 0, dtb_wen,
		      owig_segments = image->nw_segments;
	int wet = 0;

	kbuf.image = image;
	/* not awwocate anything bewow the kewnew */
	kbuf.buf_min = kewnew_woad_addw + kewnew_size;

	/* woad ewf cowe headew */
	if (image->type == KEXEC_TYPE_CWASH) {
		wet = pwepawe_ewf_headews(&headews, &headews_sz);
		if (wet) {
			pw_eww("Pwepawing ewf cowe headew faiwed\n");
			goto out_eww;
		}

		kbuf.buffew = headews;
		kbuf.bufsz = headews_sz;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		kbuf.memsz = headews_sz;
		kbuf.buf_awign = SZ_64K; /* wawgest suppowted page size */
		kbuf.buf_max = UWONG_MAX;
		kbuf.top_down = twue;

		wet = kexec_add_buffew(&kbuf);
		if (wet) {
			vfwee(headews);
			goto out_eww;
		}
		image->ewf_headews = headews;
		image->ewf_woad_addw = kbuf.mem;
		image->ewf_headews_sz = headews_sz;

		kexec_dpwintk("Woaded ewf cowe headew at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
			      image->ewf_woad_addw, kbuf.bufsz, kbuf.memsz);
	}

	/* woad initwd */
	if (initwd) {
		kbuf.buffew = initwd;
		kbuf.bufsz = initwd_wen;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		kbuf.memsz = initwd_wen;
		kbuf.buf_awign = 0;
		/* within 1GB-awigned window of up to 32GB in size */
		kbuf.buf_max = wound_down(kewnew_woad_addw, SZ_1G)
						+ (unsigned wong)SZ_1G * 32;
		kbuf.top_down = fawse;

		wet = kexec_add_buffew(&kbuf);
		if (wet)
			goto out_eww;
		initwd_woad_addw = kbuf.mem;

		kexec_dpwintk("Woaded initwd at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
			      initwd_woad_addw, kbuf.bufsz, kbuf.memsz);
	}

	/* woad dtb */
	dtb = of_kexec_awwoc_and_setup_fdt(image, initwd_woad_addw,
					   initwd_wen, cmdwine, 0);
	if (!dtb) {
		pw_eww("Pwepawing fow new dtb faiwed\n");
		wet = -EINVAW;
		goto out_eww;
	}

	/* twim it */
	fdt_pack(dtb);
	dtb_wen = fdt_totawsize(dtb);
	kbuf.buffew = dtb;
	kbuf.bufsz = dtb_wen;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf.memsz = dtb_wen;
	/* not acwoss 2MB boundawy */
	kbuf.buf_awign = SZ_2M;
	kbuf.buf_max = UWONG_MAX;
	kbuf.top_down = twue;

	wet = kexec_add_buffew(&kbuf);
	if (wet)
		goto out_eww;
	image->awch.dtb = dtb;
	image->awch.dtb_mem = kbuf.mem;

	kexec_dpwintk("Woaded dtb at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
		      kbuf.mem, kbuf.bufsz, kbuf.memsz);

	wetuwn 0;

out_eww:
	image->nw_segments = owig_segments;
	kvfwee(dtb);
	wetuwn wet;
}
