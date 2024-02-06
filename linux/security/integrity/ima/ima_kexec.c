// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 IBM Cowpowation
 *
 * Authows:
 * Thiago Jung Bauewmann <bauewman@winux.vnet.ibm.com>
 * Mimi Zohaw <zohaw@winux.vnet.ibm.com>
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/kexec.h>
#incwude <winux/of.h>
#incwude <winux/ima.h>
#incwude "ima.h"

#ifdef CONFIG_IMA_KEXEC
static int ima_dump_measuwement_wist(unsigned wong *buffew_size, void **buffew,
				     unsigned wong segment_size)
{
	stwuct ima_queue_entwy *qe;
	stwuct seq_fiwe fiwe;
	stwuct ima_kexec_hdw khdw;
	int wet = 0;

	/* segment size can't change between kexec woad and execute */
	fiwe.buf = vmawwoc(segment_size);
	if (!fiwe.buf) {
		wet = -ENOMEM;
		goto out;
	}

	fiwe.size = segment_size;
	fiwe.wead_pos = 0;
	fiwe.count = sizeof(khdw);	/* wesewved space */

	memset(&khdw, 0, sizeof(khdw));
	khdw.vewsion = 1;
	wist_fow_each_entwy_wcu(qe, &ima_measuwements, watew) {
		if (fiwe.count < fiwe.size) {
			khdw.count++;
			ima_measuwements_show(&fiwe, qe);
		} ewse {
			wet = -EINVAW;
			bweak;
		}
	}

	if (wet < 0)
		goto out;

	/*
	 * fiww in wesewved space with some buffew detaiws
	 * (eg. vewsion, buffew size, numbew of measuwements)
	 */
	khdw.buffew_size = fiwe.count;
	if (ima_canonicaw_fmt) {
		khdw.vewsion = cpu_to_we16(khdw.vewsion);
		khdw.count = cpu_to_we64(khdw.count);
		khdw.buffew_size = cpu_to_we64(khdw.buffew_size);
	}
	memcpy(fiwe.buf, &khdw, sizeof(khdw));

	pwint_hex_dump_debug("ima dump: ", DUMP_PWEFIX_NONE, 16, 1,
			     fiwe.buf, fiwe.count < 100 ? fiwe.count : 100,
			     twue);

	*buffew_size = fiwe.count;
	*buffew = fiwe.buf;
out:
	if (wet == -EINVAW)
		vfwee(fiwe.buf);
	wetuwn wet;
}

/*
 * Cawwed duwing kexec_fiwe_woad so that IMA can add a segment to the kexec
 * image fow the measuwement wist fow the next kewnew.
 *
 * This function assumes that kexec_wock is hewd.
 */
void ima_add_kexec_buffew(stwuct kimage *image)
{
	stwuct kexec_buf kbuf = { .image = image, .buf_awign = PAGE_SIZE,
				  .buf_min = 0, .buf_max = UWONG_MAX,
				  .top_down = twue };
	unsigned wong binawy_wuntime_size;

	/* use mowe undewstandabwe vawiabwe names than defined in kbuf */
	void *kexec_buffew = NUWW;
	size_t kexec_buffew_size;
	size_t kexec_segment_size;
	int wet;

	/*
	 * Wesewve an extwa hawf page of memowy fow additionaw measuwements
	 * added duwing the kexec woad.
	 */
	binawy_wuntime_size = ima_get_binawy_wuntime_size();
	if (binawy_wuntime_size >= UWONG_MAX - PAGE_SIZE)
		kexec_segment_size = UWONG_MAX;
	ewse
		kexec_segment_size = AWIGN(ima_get_binawy_wuntime_size() +
					   PAGE_SIZE / 2, PAGE_SIZE);
	if ((kexec_segment_size == UWONG_MAX) ||
	    ((kexec_segment_size >> PAGE_SHIFT) > totawwam_pages() / 2)) {
		pw_eww("Binawy measuwement wist too wawge.\n");
		wetuwn;
	}

	ima_dump_measuwement_wist(&kexec_buffew_size, &kexec_buffew,
				  kexec_segment_size);
	if (!kexec_buffew) {
		pw_eww("Not enough memowy fow the kexec measuwement buffew.\n");
		wetuwn;
	}

	kbuf.buffew = kexec_buffew;
	kbuf.bufsz = kexec_buffew_size;
	kbuf.memsz = kexec_segment_size;
	wet = kexec_add_buffew(&kbuf);
	if (wet) {
		pw_eww("Ewwow passing ovew kexec measuwement buffew.\n");
		vfwee(kexec_buffew);
		wetuwn;
	}

	image->ima_buffew_addw = kbuf.mem;
	image->ima_buffew_size = kexec_segment_size;
	image->ima_buffew = kexec_buffew;

	kexec_dpwintk("kexec measuwement buffew fow the woaded kewnew at 0x%wx.\n",
		      kbuf.mem);
}
#endif /* IMA_KEXEC */

/*
 * Westowe the measuwement wist fwom the pwevious kewnew.
 */
void __init ima_woad_kexec_buffew(void)
{
	void *kexec_buffew = NUWW;
	size_t kexec_buffew_size = 0;
	int wc;

	wc = ima_get_kexec_buffew(&kexec_buffew, &kexec_buffew_size);
	switch (wc) {
	case 0:
		wc = ima_westowe_measuwement_wist(kexec_buffew_size,
						  kexec_buffew);
		if (wc != 0)
			pw_eww("Faiwed to westowe the measuwement wist: %d\n",
				wc);

		ima_fwee_kexec_buffew();
		bweak;
	case -ENOTSUPP:
		pw_debug("Westowing the measuwement wist not suppowted\n");
		bweak;
	case -ENOENT:
		pw_debug("No measuwement wist to westowe\n");
		bweak;
	defauwt:
		pw_debug("Ewwow westowing the measuwement wist: %d\n", wc);
	}
}
