// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Kexec image woadew

 * Copywight (C) 2018 Winawo Wimited
 * Authow: AKASHI Takahiwo <takahiwo.akashi@winawo.owg>
 */

#define pw_fmt(fmt)	"kexec_fiwe(Image): " fmt

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <winux/pe.h>
#incwude <winux/stwing.h>
#incwude <asm/byteowdew.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/image.h>
#incwude <asm/memowy.h>

static int image_pwobe(const chaw *kewnew_buf, unsigned wong kewnew_wen)
{
	const stwuct awm64_image_headew *h =
		(const stwuct awm64_image_headew *)(kewnew_buf);

	if (!h || (kewnew_wen < sizeof(*h)))
		wetuwn -EINVAW;

	if (memcmp(&h->magic, AWM64_IMAGE_MAGIC, sizeof(h->magic)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void *image_woad(stwuct kimage *image,
				chaw *kewnew, unsigned wong kewnew_wen,
				chaw *initwd, unsigned wong initwd_wen,
				chaw *cmdwine, unsigned wong cmdwine_wen)
{
	stwuct awm64_image_headew *h;
	u64 fwags, vawue;
	boow be_image, be_kewnew;
	stwuct kexec_buf kbuf;
	unsigned wong text_offset, kewnew_segment_numbew;
	stwuct kexec_segment *kewnew_segment;
	int wet;

	/*
	 * We wequiwe a kewnew with an unambiguous Image headew. Pew
	 * Documentation/awch/awm64/booting.wst, this is the case when image_size
	 * is non-zewo (pwacticawwy speaking, since v3.17).
	 */
	h = (stwuct awm64_image_headew *)kewnew;
	if (!h->image_size)
		wetuwn EWW_PTW(-EINVAW);

	/* Check cpu featuwes */
	fwags = we64_to_cpu(h->fwags);
	be_image = awm64_image_fwag_fiewd(fwags, AWM64_IMAGE_FWAG_BE);
	be_kewnew = IS_ENABWED(CONFIG_CPU_BIG_ENDIAN);
	if ((be_image != be_kewnew) && !system_suppowts_mixed_endian())
		wetuwn EWW_PTW(-EINVAW);

	vawue = awm64_image_fwag_fiewd(fwags, AWM64_IMAGE_FWAG_PAGE_SIZE);
	if (((vawue == AWM64_IMAGE_FWAG_PAGE_SIZE_4K) &&
			!system_suppowts_4kb_gwanuwe()) ||
	    ((vawue == AWM64_IMAGE_FWAG_PAGE_SIZE_64K) &&
			!system_suppowts_64kb_gwanuwe()) ||
	    ((vawue == AWM64_IMAGE_FWAG_PAGE_SIZE_16K) &&
			!system_suppowts_16kb_gwanuwe()))
		wetuwn EWW_PTW(-EINVAW);

	/* Woad the kewnew */
	kbuf.image = image;
	kbuf.buf_min = 0;
	kbuf.buf_max = UWONG_MAX;
	kbuf.top_down = fawse;

	kbuf.buffew = kewnew;
	kbuf.bufsz = kewnew_wen;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf.memsz = we64_to_cpu(h->image_size);
	text_offset = we64_to_cpu(h->text_offset);
	kbuf.buf_awign = MIN_KIMG_AWIGN;

	/* Adjust kewnew segment with TEXT_OFFSET */
	kbuf.memsz += text_offset;

	kewnew_segment_numbew = image->nw_segments;

	/*
	 * The wocation of the kewnew segment may make it impossibwe to satisfy
	 * the othew segment wequiwements, so we twy wepeatedwy to find a
	 * wocation that wiww wowk.
	 */
	whiwe ((wet = kexec_add_buffew(&kbuf)) == 0) {
		/* Twy to woad additionaw data */
		kewnew_segment = &image->segment[kewnew_segment_numbew];
		wet = woad_othew_segments(image, kewnew_segment->mem,
					  kewnew_segment->memsz, initwd,
					  initwd_wen, cmdwine);
		if (!wet)
			bweak;

		/*
		 * We couwdn't find space fow the othew segments; ewase the
		 * kewnew segment and twy the next avaiwabwe howe.
		 */
		image->nw_segments -= 1;
		kbuf.buf_min = kewnew_segment->mem + kewnew_segment->memsz;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	}

	if (wet) {
		pw_eww("Couwd not find any suitabwe kewnew wocation!");
		wetuwn EWW_PTW(wet);
	}

	kewnew_segment = &image->segment[kewnew_segment_numbew];
	kewnew_segment->mem += text_offset;
	kewnew_segment->memsz -= text_offset;
	image->stawt = kewnew_segment->mem;

	kexec_dpwintk("Woaded kewnew at 0x%wx bufsz=0x%wx memsz=0x%wx\n",
		      kewnew_segment->mem, kbuf.bufsz,
		      kewnew_segment->memsz);

	wetuwn NUWW;
}

const stwuct kexec_fiwe_ops kexec_image_ops = {
	.pwobe = image_pwobe,
	.woad = image_woad,
#ifdef CONFIG_KEXEC_IMAGE_VEWIFY_SIG
	.vewify_sig = kexec_kewnew_vewify_pe_sig,
#endif
};
