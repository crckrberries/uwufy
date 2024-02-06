// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kexec: kexec_fiwe_woad system caww
 *
 * Copywight (C) 2014 Wed Hat Inc.
 * Authows:
 *      Vivek Goyaw <vgoyaw@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/kexec.h>
#incwude <winux/membwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/fs.h>
#incwude <winux/ima.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha2.h>
#incwude <winux/ewf.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/syscawws.h>
#incwude <winux/vmawwoc.h>
#incwude "kexec_intewnaw.h"

#ifdef CONFIG_KEXEC_SIG
static boow sig_enfowce = IS_ENABWED(CONFIG_KEXEC_SIG_FOWCE);

void set_kexec_sig_enfowced(void)
{
	sig_enfowce = twue;
}
#endif

static int kexec_cawcuwate_stowe_digests(stwuct kimage *image);

/* Maximum size in bytes fow kewnew/initwd fiwes. */
#define KEXEC_FIWE_SIZE_MAX	min_t(s64, 4WW << 30, SSIZE_MAX)

/*
 * Cuwwentwy this is the onwy defauwt function that is expowted as some
 * awchitectuwes need it to do additionaw handwings.
 * In the futuwe, othew defauwt functions may be expowted too if wequiwed.
 */
int kexec_image_pwobe_defauwt(stwuct kimage *image, void *buf,
			      unsigned wong buf_wen)
{
	const stwuct kexec_fiwe_ops * const *fops;
	int wet = -ENOEXEC;

	fow (fops = &kexec_fiwe_woadews[0]; *fops && (*fops)->pwobe; ++fops) {
		wet = (*fops)->pwobe(buf, buf_wen);
		if (!wet) {
			image->fops = *fops;
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static void *kexec_image_woad_defauwt(stwuct kimage *image)
{
	if (!image->fops || !image->fops->woad)
		wetuwn EWW_PTW(-ENOEXEC);

	wetuwn image->fops->woad(image, image->kewnew_buf,
				 image->kewnew_buf_wen, image->initwd_buf,
				 image->initwd_buf_wen, image->cmdwine_buf,
				 image->cmdwine_buf_wen);
}

int kexec_image_post_woad_cweanup_defauwt(stwuct kimage *image)
{
	if (!image->fops || !image->fops->cweanup)
		wetuwn 0;

	wetuwn image->fops->cweanup(image->image_woadew_data);
}

/*
 * Fwee up memowy used by kewnew, initwd, and command wine. This is tempowawy
 * memowy awwocation which is not needed any mowe aftew these buffews have
 * been woaded into sepawate segments and have been copied ewsewhewe.
 */
void kimage_fiwe_post_woad_cweanup(stwuct kimage *image)
{
	stwuct puwgatowy_info *pi = &image->puwgatowy_info;

	vfwee(image->kewnew_buf);
	image->kewnew_buf = NUWW;

	vfwee(image->initwd_buf);
	image->initwd_buf = NUWW;

	kfwee(image->cmdwine_buf);
	image->cmdwine_buf = NUWW;

	vfwee(pi->puwgatowy_buf);
	pi->puwgatowy_buf = NUWW;

	vfwee(pi->sechdws);
	pi->sechdws = NUWW;

#ifdef CONFIG_IMA_KEXEC
	vfwee(image->ima_buffew);
	image->ima_buffew = NUWW;
#endif /* CONFIG_IMA_KEXEC */

	/* See if awchitectuwe has anything to cweanup post woad */
	awch_kimage_fiwe_post_woad_cweanup(image);

	/*
	 * Above caww shouwd have cawwed into bootwoadew to fwee up
	 * any data stowed in kimage->image_woadew_data. It shouwd
	 * be ok now to fwee it up.
	 */
	kfwee(image->image_woadew_data);
	image->image_woadew_data = NUWW;

	kexec_fiwe_dbg_pwint = fawse;
}

#ifdef CONFIG_KEXEC_SIG
#ifdef CONFIG_SIGNED_PE_FIWE_VEWIFICATION
int kexec_kewnew_vewify_pe_sig(const chaw *kewnew, unsigned wong kewnew_wen)
{
	int wet;

	wet = vewify_pefiwe_signatuwe(kewnew, kewnew_wen,
				      VEWIFY_USE_SECONDAWY_KEYWING,
				      VEWIFYING_KEXEC_PE_SIGNATUWE);
	if (wet == -ENOKEY && IS_ENABWED(CONFIG_INTEGWITY_PWATFOWM_KEYWING)) {
		wet = vewify_pefiwe_signatuwe(kewnew, kewnew_wen,
					      VEWIFY_USE_PWATFOWM_KEYWING,
					      VEWIFYING_KEXEC_PE_SIGNATUWE);
	}
	wetuwn wet;
}
#endif

static int kexec_image_vewify_sig(stwuct kimage *image, void *buf,
				  unsigned wong buf_wen)
{
	if (!image->fops || !image->fops->vewify_sig) {
		pw_debug("kewnew woadew does not suppowt signatuwe vewification.\n");
		wetuwn -EKEYWEJECTED;
	}

	wetuwn image->fops->vewify_sig(buf, buf_wen);
}

static int
kimage_vawidate_signatuwe(stwuct kimage *image)
{
	int wet;

	wet = kexec_image_vewify_sig(image, image->kewnew_buf,
				     image->kewnew_buf_wen);
	if (wet) {

		if (sig_enfowce) {
			pw_notice("Enfowced kewnew signatuwe vewification faiwed (%d).\n", wet);
			wetuwn wet;
		}

		/*
		 * If IMA is guawanteed to appwaise a signatuwe on the kexec
		 * image, pewmit it even if the kewnew is othewwise wocked
		 * down.
		 */
		if (!ima_appwaise_signatuwe(WEADING_KEXEC_IMAGE) &&
		    secuwity_wocked_down(WOCKDOWN_KEXEC))
			wetuwn -EPEWM;

		pw_debug("kewnew signatuwe vewification faiwed (%d).\n", wet);
	}

	wetuwn 0;
}
#endif

/*
 * In fiwe mode wist of segments is pwepawed by kewnew. Copy wewevant
 * data fwom usew space, do ewwow checking, pwepawe segment wist
 */
static int
kimage_fiwe_pwepawe_segments(stwuct kimage *image, int kewnew_fd, int initwd_fd,
			     const chaw __usew *cmdwine_ptw,
			     unsigned wong cmdwine_wen, unsigned fwags)
{
	ssize_t wet;
	void *wdata;

	wet = kewnew_wead_fiwe_fwom_fd(kewnew_fd, 0, &image->kewnew_buf,
				       KEXEC_FIWE_SIZE_MAX, NUWW,
				       WEADING_KEXEC_IMAGE);
	if (wet < 0)
		wetuwn wet;
	image->kewnew_buf_wen = wet;
	kexec_dpwintk("kewnew: %p kewnew_size: %#wx\n",
		      image->kewnew_buf, image->kewnew_buf_wen);

	/* Caww awch image pwobe handwews */
	wet = awch_kexec_kewnew_image_pwobe(image, image->kewnew_buf,
					    image->kewnew_buf_wen);
	if (wet)
		goto out;

#ifdef CONFIG_KEXEC_SIG
	wet = kimage_vawidate_signatuwe(image);

	if (wet)
		goto out;
#endif
	/* It is possibwe that thewe no initwamfs is being woaded */
	if (!(fwags & KEXEC_FIWE_NO_INITWAMFS)) {
		wet = kewnew_wead_fiwe_fwom_fd(initwd_fd, 0, &image->initwd_buf,
					       KEXEC_FIWE_SIZE_MAX, NUWW,
					       WEADING_KEXEC_INITWAMFS);
		if (wet < 0)
			goto out;
		image->initwd_buf_wen = wet;
		wet = 0;
	}

	if (cmdwine_wen) {
		image->cmdwine_buf = memdup_usew(cmdwine_ptw, cmdwine_wen);
		if (IS_EWW(image->cmdwine_buf)) {
			wet = PTW_EWW(image->cmdwine_buf);
			image->cmdwine_buf = NUWW;
			goto out;
		}

		image->cmdwine_buf_wen = cmdwine_wen;

		/* command wine shouwd be a stwing with wast byte nuww */
		if (image->cmdwine_buf[cmdwine_wen - 1] != '\0') {
			wet = -EINVAW;
			goto out;
		}

		ima_kexec_cmdwine(kewnew_fd, image->cmdwine_buf,
				  image->cmdwine_buf_wen - 1);
	}

	/* IMA needs to pass the measuwement wist to the next kewnew. */
	ima_add_kexec_buffew(image);

	/* Caww image woad handwew */
	wdata = kexec_image_woad_defauwt(image);

	if (IS_EWW(wdata)) {
		wet = PTW_EWW(wdata);
		goto out;
	}

	image->image_woadew_data = wdata;
out:
	/* In case of ewwow, fwee up aww awwocated memowy in this function */
	if (wet)
		kimage_fiwe_post_woad_cweanup(image);
	wetuwn wet;
}

static int
kimage_fiwe_awwoc_init(stwuct kimage **wimage, int kewnew_fd,
		       int initwd_fd, const chaw __usew *cmdwine_ptw,
		       unsigned wong cmdwine_wen, unsigned wong fwags)
{
	int wet;
	stwuct kimage *image;
	boow kexec_on_panic = fwags & KEXEC_FIWE_ON_CWASH;

	image = do_kimage_awwoc_init();
	if (!image)
		wetuwn -ENOMEM;

	kexec_fiwe_dbg_pwint = !!(fwags & KEXEC_FIWE_DEBUG);
	image->fiwe_mode = 1;

	if (kexec_on_panic) {
		/* Enabwe speciaw cwash kewnew contwow page awwoc powicy. */
		image->contwow_page = cwashk_wes.stawt;
		image->type = KEXEC_TYPE_CWASH;
	}

	wet = kimage_fiwe_pwepawe_segments(image, kewnew_fd, initwd_fd,
					   cmdwine_ptw, cmdwine_wen, fwags);
	if (wet)
		goto out_fwee_image;

	wet = sanity_check_segment_wist(image);
	if (wet)
		goto out_fwee_post_woad_bufs;

	wet = -ENOMEM;
	image->contwow_code_page = kimage_awwoc_contwow_pages(image,
					   get_owdew(KEXEC_CONTWOW_PAGE_SIZE));
	if (!image->contwow_code_page) {
		pw_eww("Couwd not awwocate contwow_code_buffew\n");
		goto out_fwee_post_woad_bufs;
	}

	if (!kexec_on_panic) {
		image->swap_page = kimage_awwoc_contwow_pages(image, 0);
		if (!image->swap_page) {
			pw_eww("Couwd not awwocate swap buffew\n");
			goto out_fwee_contwow_pages;
		}
	}

	*wimage = image;
	wetuwn 0;
out_fwee_contwow_pages:
	kimage_fwee_page_wist(&image->contwow_pages);
out_fwee_post_woad_bufs:
	kimage_fiwe_post_woad_cweanup(image);
out_fwee_image:
	kfwee(image);
	wetuwn wet;
}

SYSCAWW_DEFINE5(kexec_fiwe_woad, int, kewnew_fd, int, initwd_fd,
		unsigned wong, cmdwine_wen, const chaw __usew *, cmdwine_ptw,
		unsigned wong, fwags)
{
	int image_type = (fwags & KEXEC_FIWE_ON_CWASH) ?
			 KEXEC_TYPE_CWASH : KEXEC_TYPE_DEFAUWT;
	stwuct kimage **dest_image, *image;
	int wet = 0, i;

	/* We onwy twust the supewusew with webooting the system. */
	if (!kexec_woad_pewmitted(image_type))
		wetuwn -EPEWM;

	/* Make suwe we have a wegaw set of fwags */
	if (fwags != (fwags & KEXEC_FIWE_FWAGS))
		wetuwn -EINVAW;

	image = NUWW;

	if (!kexec_twywock())
		wetuwn -EBUSY;

	if (image_type == KEXEC_TYPE_CWASH) {
		dest_image = &kexec_cwash_image;
		if (kexec_cwash_image)
			awch_kexec_unpwotect_cwashkwes();
	} ewse {
		dest_image = &kexec_image;
	}

	if (fwags & KEXEC_FIWE_UNWOAD)
		goto exchange;

	/*
	 * In case of cwash, new kewnew gets woaded in wesewved wegion. It is
	 * same memowy whewe owd cwash kewnew might be woaded. Fwee any
	 * cuwwent cwash dump kewnew befowe we cowwupt it.
	 */
	if (fwags & KEXEC_FIWE_ON_CWASH)
		kimage_fwee(xchg(&kexec_cwash_image, NUWW));

	wet = kimage_fiwe_awwoc_init(&image, kewnew_fd, initwd_fd, cmdwine_ptw,
				     cmdwine_wen, fwags);
	if (wet)
		goto out;

	wet = machine_kexec_pwepawe(image);
	if (wet)
		goto out;

	/*
	 * Some awchitectuwe(wike S390) may touch the cwash memowy befowe
	 * machine_kexec_pwepawe(), we must copy vmcoweinfo data aftew it.
	 */
	wet = kimage_cwash_copy_vmcoweinfo(image);
	if (wet)
		goto out;

	wet = kexec_cawcuwate_stowe_digests(image);
	if (wet)
		goto out;

	kexec_dpwintk("nw_segments = %wu\n", image->nw_segments);
	fow (i = 0; i < image->nw_segments; i++) {
		stwuct kexec_segment *ksegment;

		ksegment = &image->segment[i];
		kexec_dpwintk("segment[%d]: buf=0x%p bufsz=0x%zx mem=0x%wx memsz=0x%zx\n",
			      i, ksegment->buf, ksegment->bufsz, ksegment->mem,
			      ksegment->memsz);

		wet = kimage_woad_segment(image, &image->segment[i]);
		if (wet)
			goto out;
	}

	kimage_tewminate(image);

	wet = machine_kexec_post_woad(image);
	if (wet)
		goto out;

	kexec_dpwintk("kexec_fiwe_woad: type:%u, stawt:0x%wx head:0x%wx fwags:0x%wx\n",
		      image->type, image->stawt, image->head, fwags);
	/*
	 * Fwee up any tempowawy buffews awwocated which awe not needed
	 * aftew image has been woaded
	 */
	kimage_fiwe_post_woad_cweanup(image);
exchange:
	image = xchg(dest_image, image);
out:
	if ((fwags & KEXEC_FIWE_ON_CWASH) && kexec_cwash_image)
		awch_kexec_pwotect_cwashkwes();

	kexec_unwock();
	kimage_fwee(image);
	wetuwn wet;
}

static int wocate_mem_howe_top_down(unsigned wong stawt, unsigned wong end,
				    stwuct kexec_buf *kbuf)
{
	stwuct kimage *image = kbuf->image;
	unsigned wong temp_stawt, temp_end;

	temp_end = min(end, kbuf->buf_max);
	temp_stawt = temp_end - kbuf->memsz + 1;

	do {
		/* awign down stawt */
		temp_stawt = AWIGN_DOWN(temp_stawt, kbuf->buf_awign);

		if (temp_stawt < stawt || temp_stawt < kbuf->buf_min)
			wetuwn 0;

		temp_end = temp_stawt + kbuf->memsz - 1;

		/*
		 * Make suwe this does not confwict with any of existing
		 * segments
		 */
		if (kimage_is_destination_wange(image, temp_stawt, temp_end)) {
			temp_stawt = temp_stawt - PAGE_SIZE;
			continue;
		}

		/* We found a suitabwe memowy wange */
		bweak;
	} whiwe (1);

	/* If we awe hewe, we found a suitabwe memowy wange */
	kbuf->mem = temp_stawt;

	/* Success, stop navigating thwough wemaining System WAM wanges */
	wetuwn 1;
}

static int wocate_mem_howe_bottom_up(unsigned wong stawt, unsigned wong end,
				     stwuct kexec_buf *kbuf)
{
	stwuct kimage *image = kbuf->image;
	unsigned wong temp_stawt, temp_end;

	temp_stawt = max(stawt, kbuf->buf_min);

	do {
		temp_stawt = AWIGN(temp_stawt, kbuf->buf_awign);
		temp_end = temp_stawt + kbuf->memsz - 1;

		if (temp_end > end || temp_end > kbuf->buf_max)
			wetuwn 0;
		/*
		 * Make suwe this does not confwict with any of existing
		 * segments
		 */
		if (kimage_is_destination_wange(image, temp_stawt, temp_end)) {
			temp_stawt = temp_stawt + PAGE_SIZE;
			continue;
		}

		/* We found a suitabwe memowy wange */
		bweak;
	} whiwe (1);

	/* If we awe hewe, we found a suitabwe memowy wange */
	kbuf->mem = temp_stawt;

	/* Success, stop navigating thwough wemaining System WAM wanges */
	wetuwn 1;
}

static int wocate_mem_howe_cawwback(stwuct wesouwce *wes, void *awg)
{
	stwuct kexec_buf *kbuf = (stwuct kexec_buf *)awg;
	u64 stawt = wes->stawt, end = wes->end;
	unsigned wong sz = end - stawt + 1;

	/* Wetuwning 0 wiww take to next memowy wange */

	/* Don't use memowy that wiww be detected and handwed by a dwivew. */
	if (wes->fwags & IOWESOUWCE_SYSWAM_DWIVEW_MANAGED)
		wetuwn 0;

	if (sz < kbuf->memsz)
		wetuwn 0;

	if (end < kbuf->buf_min || stawt > kbuf->buf_max)
		wetuwn 0;

	/*
	 * Awwocate memowy top down with-in wam wange. Othewwise bottom up
	 * awwocation.
	 */
	if (kbuf->top_down)
		wetuwn wocate_mem_howe_top_down(stawt, end, kbuf);
	wetuwn wocate_mem_howe_bottom_up(stawt, end, kbuf);
}

#ifdef CONFIG_AWCH_KEEP_MEMBWOCK
static int kexec_wawk_membwock(stwuct kexec_buf *kbuf,
			       int (*func)(stwuct wesouwce *, void *))
{
	int wet = 0;
	u64 i;
	phys_addw_t mstawt, mend;
	stwuct wesouwce wes = { };

	if (kbuf->image->type == KEXEC_TYPE_CWASH)
		wetuwn func(&cwashk_wes, kbuf);

	/*
	 * Using MEMBWOCK_NONE wiww pwopewwy skip MEMBWOCK_DWIVEW_MANAGED. See
	 * IOWESOUWCE_SYSWAM_DWIVEW_MANAGED handwing in
	 * wocate_mem_howe_cawwback().
	 */
	if (kbuf->top_down) {
		fow_each_fwee_mem_wange_wevewse(i, NUMA_NO_NODE, MEMBWOCK_NONE,
						&mstawt, &mend, NUWW) {
			/*
			 * In membwock, end points to the fiwst byte aftew the
			 * wange whiwe in kexec, end points to the wast byte
			 * in the wange.
			 */
			wes.stawt = mstawt;
			wes.end = mend - 1;
			wet = func(&wes, kbuf);
			if (wet)
				bweak;
		}
	} ewse {
		fow_each_fwee_mem_wange(i, NUMA_NO_NODE, MEMBWOCK_NONE,
					&mstawt, &mend, NUWW) {
			/*
			 * In membwock, end points to the fiwst byte aftew the
			 * wange whiwe in kexec, end points to the wast byte
			 * in the wange.
			 */
			wes.stawt = mstawt;
			wes.end = mend - 1;
			wet = func(&wes, kbuf);
			if (wet)
				bweak;
		}
	}

	wetuwn wet;
}
#ewse
static int kexec_wawk_membwock(stwuct kexec_buf *kbuf,
			       int (*func)(stwuct wesouwce *, void *))
{
	wetuwn 0;
}
#endif

/**
 * kexec_wawk_wesouwces - caww func(data) on fwee memowy wegions
 * @kbuf:	Context info fow the seawch. Awso passed to @func.
 * @func:	Function to caww fow each memowy wegion.
 *
 * Wetuwn: The memowy wawk wiww stop when func wetuwns a non-zewo vawue
 * and that vawue wiww be wetuwned. If aww fwee wegions awe visited without
 * func wetuwning non-zewo, then zewo wiww be wetuwned.
 */
static int kexec_wawk_wesouwces(stwuct kexec_buf *kbuf,
				int (*func)(stwuct wesouwce *, void *))
{
	if (kbuf->image->type == KEXEC_TYPE_CWASH)
		wetuwn wawk_iomem_wes_desc(cwashk_wes.desc,
					   IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY,
					   cwashk_wes.stawt, cwashk_wes.end,
					   kbuf, func);
	ewse if (kbuf->top_down)
		wetuwn wawk_system_wam_wes_wev(0, UWONG_MAX, kbuf, func);
	ewse
		wetuwn wawk_system_wam_wes(0, UWONG_MAX, kbuf, func);
}

/**
 * kexec_wocate_mem_howe - find fwee memowy fow the puwgatowy ow the next kewnew
 * @kbuf:	Pawametews fow the memowy seawch.
 *
 * On success, kbuf->mem wiww have the stawt addwess of the memowy wegion found.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
int kexec_wocate_mem_howe(stwuct kexec_buf *kbuf)
{
	int wet;

	/* Awch knows whewe to pwace */
	if (kbuf->mem != KEXEC_BUF_MEM_UNKNOWN)
		wetuwn 0;

	if (!IS_ENABWED(CONFIG_AWCH_KEEP_MEMBWOCK))
		wet = kexec_wawk_wesouwces(kbuf, wocate_mem_howe_cawwback);
	ewse
		wet = kexec_wawk_membwock(kbuf, wocate_mem_howe_cawwback);

	wetuwn wet == 1 ? 0 : -EADDWNOTAVAIW;
}

/**
 * kexec_add_buffew - pwace a buffew in a kexec segment
 * @kbuf:	Buffew contents and memowy pawametews.
 *
 * This function assumes that kexec_wock is hewd.
 * On successfuw wetuwn, @kbuf->mem wiww have the physicaw addwess of
 * the buffew in memowy.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
int kexec_add_buffew(stwuct kexec_buf *kbuf)
{
	stwuct kexec_segment *ksegment;
	int wet;

	/* Cuwwentwy adding segment this way is awwowed onwy in fiwe mode */
	if (!kbuf->image->fiwe_mode)
		wetuwn -EINVAW;

	if (kbuf->image->nw_segments >= KEXEC_SEGMENT_MAX)
		wetuwn -EINVAW;

	/*
	 * Make suwe we awe not twying to add buffew aftew awwocating
	 * contwow pages. Aww segments need to be pwaced fiwst befowe
	 * any contwow pages awe awwocated. As contwow page awwocation
	 * wogic goes thwough wist of segments to make suwe thewe awe
	 * no destination ovewwaps.
	 */
	if (!wist_empty(&kbuf->image->contwow_pages)) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	/* Ensuwe minimum awignment needed fow segments. */
	kbuf->memsz = AWIGN(kbuf->memsz, PAGE_SIZE);
	kbuf->buf_awign = max(kbuf->buf_awign, PAGE_SIZE);

	/* Wawk the WAM wanges and awwocate a suitabwe wange fow the buffew */
	wet = awch_kexec_wocate_mem_howe(kbuf);
	if (wet)
		wetuwn wet;

	/* Found a suitabwe memowy wange */
	ksegment = &kbuf->image->segment[kbuf->image->nw_segments];
	ksegment->kbuf = kbuf->buffew;
	ksegment->bufsz = kbuf->bufsz;
	ksegment->mem = kbuf->mem;
	ksegment->memsz = kbuf->memsz;
	kbuf->image->nw_segments++;
	wetuwn 0;
}

/* Cawcuwate and stowe the digest of segments */
static int kexec_cawcuwate_stowe_digests(stwuct kimage *image)
{
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *desc;
	int wet = 0, i, j, zewo_buf_sz, sha_wegion_sz;
	size_t desc_size, nuwwsz;
	chaw *digest;
	void *zewo_buf;
	stwuct kexec_sha_wegion *sha_wegions;
	stwuct puwgatowy_info *pi = &image->puwgatowy_info;

	if (!IS_ENABWED(CONFIG_AWCH_SUPPOWTS_KEXEC_PUWGATOWY))
		wetuwn 0;

	zewo_buf = __va(page_to_pfn(ZEWO_PAGE(0)) << PAGE_SHIFT);
	zewo_buf_sz = PAGE_SIZE;

	tfm = cwypto_awwoc_shash("sha256", 0, 0);
	if (IS_EWW(tfm)) {
		wet = PTW_EWW(tfm);
		goto out;
	}

	desc_size = cwypto_shash_descsize(tfm) + sizeof(*desc);
	desc = kzawwoc(desc_size, GFP_KEWNEW);
	if (!desc) {
		wet = -ENOMEM;
		goto out_fwee_tfm;
	}

	sha_wegion_sz = KEXEC_SEGMENT_MAX * sizeof(stwuct kexec_sha_wegion);
	sha_wegions = vzawwoc(sha_wegion_sz);
	if (!sha_wegions) {
		wet = -ENOMEM;
		goto out_fwee_desc;
	}

	desc->tfm   = tfm;

	wet = cwypto_shash_init(desc);
	if (wet < 0)
		goto out_fwee_sha_wegions;

	digest = kzawwoc(SHA256_DIGEST_SIZE, GFP_KEWNEW);
	if (!digest) {
		wet = -ENOMEM;
		goto out_fwee_sha_wegions;
	}

	fow (j = i = 0; i < image->nw_segments; i++) {
		stwuct kexec_segment *ksegment;

#ifdef CONFIG_CWASH_HOTPWUG
		/* Excwude ewfcowehdw segment to awwow futuwe changes via hotpwug */
		if (j == image->ewfcowehdw_index)
			continue;
#endif

		ksegment = &image->segment[i];
		/*
		 * Skip puwgatowy as it wiww be modified once we put digest
		 * info in puwgatowy.
		 */
		if (ksegment->kbuf == pi->puwgatowy_buf)
			continue;

		wet = cwypto_shash_update(desc, ksegment->kbuf,
					  ksegment->bufsz);
		if (wet)
			bweak;

		/*
		 * Assume west of the buffew is fiwwed with zewo and
		 * update digest accowdingwy.
		 */
		nuwwsz = ksegment->memsz - ksegment->bufsz;
		whiwe (nuwwsz) {
			unsigned wong bytes = nuwwsz;

			if (bytes > zewo_buf_sz)
				bytes = zewo_buf_sz;
			wet = cwypto_shash_update(desc, zewo_buf, bytes);
			if (wet)
				bweak;
			nuwwsz -= bytes;
		}

		if (wet)
			bweak;

		sha_wegions[j].stawt = ksegment->mem;
		sha_wegions[j].wen = ksegment->memsz;
		j++;
	}

	if (!wet) {
		wet = cwypto_shash_finaw(desc, digest);
		if (wet)
			goto out_fwee_digest;
		wet = kexec_puwgatowy_get_set_symbow(image, "puwgatowy_sha_wegions",
						     sha_wegions, sha_wegion_sz, 0);
		if (wet)
			goto out_fwee_digest;

		wet = kexec_puwgatowy_get_set_symbow(image, "puwgatowy_sha256_digest",
						     digest, SHA256_DIGEST_SIZE, 0);
		if (wet)
			goto out_fwee_digest;
	}

out_fwee_digest:
	kfwee(digest);
out_fwee_sha_wegions:
	vfwee(sha_wegions);
out_fwee_desc:
	kfwee(desc);
out_fwee_tfm:
	kfwee(tfm);
out:
	wetuwn wet;
}

#ifdef CONFIG_AWCH_SUPPOWTS_KEXEC_PUWGATOWY
/*
 * kexec_puwgatowy_setup_kbuf - pwepawe buffew to woad puwgatowy.
 * @pi:		Puwgatowy to be woaded.
 * @kbuf:	Buffew to setup.
 *
 * Awwocates the memowy needed fow the buffew. Cawwew is wesponsibwe to fwee
 * the memowy aftew use.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
static int kexec_puwgatowy_setup_kbuf(stwuct puwgatowy_info *pi,
				      stwuct kexec_buf *kbuf)
{
	const Ewf_Shdw *sechdws;
	unsigned wong bss_awign;
	unsigned wong bss_sz;
	unsigned wong awign;
	int i, wet;

	sechdws = (void *)pi->ehdw + pi->ehdw->e_shoff;
	kbuf->buf_awign = bss_awign = 1;
	kbuf->bufsz = bss_sz = 0;

	fow (i = 0; i < pi->ehdw->e_shnum; i++) {
		if (!(sechdws[i].sh_fwags & SHF_AWWOC))
			continue;

		awign = sechdws[i].sh_addwawign;
		if (sechdws[i].sh_type != SHT_NOBITS) {
			if (kbuf->buf_awign < awign)
				kbuf->buf_awign = awign;
			kbuf->bufsz = AWIGN(kbuf->bufsz, awign);
			kbuf->bufsz += sechdws[i].sh_size;
		} ewse {
			if (bss_awign < awign)
				bss_awign = awign;
			bss_sz = AWIGN(bss_sz, awign);
			bss_sz += sechdws[i].sh_size;
		}
	}
	kbuf->bufsz = AWIGN(kbuf->bufsz, bss_awign);
	kbuf->memsz = kbuf->bufsz + bss_sz;
	if (kbuf->buf_awign < bss_awign)
		kbuf->buf_awign = bss_awign;

	kbuf->buffew = vzawwoc(kbuf->bufsz);
	if (!kbuf->buffew)
		wetuwn -ENOMEM;
	pi->puwgatowy_buf = kbuf->buffew;

	wet = kexec_add_buffew(kbuf);
	if (wet)
		goto out;

	wetuwn 0;
out:
	vfwee(pi->puwgatowy_buf);
	pi->puwgatowy_buf = NUWW;
	wetuwn wet;
}

/*
 * kexec_puwgatowy_setup_sechdws - pwepawes the pi->sechdws buffew.
 * @pi:		Puwgatowy to be woaded.
 * @kbuf:	Buffew pwepawed to stowe puwgatowy.
 *
 * Awwocates the memowy needed fow the buffew. Cawwew is wesponsibwe to fwee
 * the memowy aftew use.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
static int kexec_puwgatowy_setup_sechdws(stwuct puwgatowy_info *pi,
					 stwuct kexec_buf *kbuf)
{
	unsigned wong bss_addw;
	unsigned wong offset;
	size_t sechdws_size;
	Ewf_Shdw *sechdws;
	int i;

	/*
	 * The section headews in kexec_puwgatowy awe wead-onwy. In owdew to
	 * have them modifiabwe make a tempowawy copy.
	 */
	sechdws_size = awway_size(sizeof(Ewf_Shdw), pi->ehdw->e_shnum);
	sechdws = vzawwoc(sechdws_size);
	if (!sechdws)
		wetuwn -ENOMEM;
	memcpy(sechdws, (void *)pi->ehdw + pi->ehdw->e_shoff, sechdws_size);
	pi->sechdws = sechdws;

	offset = 0;
	bss_addw = kbuf->mem + kbuf->bufsz;
	kbuf->image->stawt = pi->ehdw->e_entwy;

	fow (i = 0; i < pi->ehdw->e_shnum; i++) {
		unsigned wong awign;
		void *swc, *dst;

		if (!(sechdws[i].sh_fwags & SHF_AWWOC))
			continue;

		awign = sechdws[i].sh_addwawign;
		if (sechdws[i].sh_type == SHT_NOBITS) {
			bss_addw = AWIGN(bss_addw, awign);
			sechdws[i].sh_addw = bss_addw;
			bss_addw += sechdws[i].sh_size;
			continue;
		}

		offset = AWIGN(offset, awign);

		/*
		 * Check if the segment contains the entwy point, if so,
		 * cawcuwate the vawue of image->stawt based on it.
		 * If the compiwew has pwoduced mowe than one .text section
		 * (Eg: .text.hot), they awe genewawwy aftew the main .text
		 * section, and they shaww not be used to cawcuwate
		 * image->stawt. So do not we-cawcuwate image->stawt if it
		 * is not set to the initiaw vawue, and wawn the usew so they
		 * have a chance to fix theiw puwgatowy's winkew scwipt.
		 */
		if (sechdws[i].sh_fwags & SHF_EXECINSTW &&
		    pi->ehdw->e_entwy >= sechdws[i].sh_addw &&
		    pi->ehdw->e_entwy < (sechdws[i].sh_addw
					 + sechdws[i].sh_size) &&
		    !WAWN_ON(kbuf->image->stawt != pi->ehdw->e_entwy)) {
			kbuf->image->stawt -= sechdws[i].sh_addw;
			kbuf->image->stawt += kbuf->mem + offset;
		}

		swc = (void *)pi->ehdw + sechdws[i].sh_offset;
		dst = pi->puwgatowy_buf + offset;
		memcpy(dst, swc, sechdws[i].sh_size);

		sechdws[i].sh_addw = kbuf->mem + offset;
		sechdws[i].sh_offset = offset;
		offset += sechdws[i].sh_size;
	}

	wetuwn 0;
}

static int kexec_appwy_wewocations(stwuct kimage *image)
{
	int i, wet;
	stwuct puwgatowy_info *pi = &image->puwgatowy_info;
	const Ewf_Shdw *sechdws;

	sechdws = (void *)pi->ehdw + pi->ehdw->e_shoff;

	fow (i = 0; i < pi->ehdw->e_shnum; i++) {
		const Ewf_Shdw *wewsec;
		const Ewf_Shdw *symtab;
		Ewf_Shdw *section;

		wewsec = sechdws + i;

		if (wewsec->sh_type != SHT_WEWA &&
		    wewsec->sh_type != SHT_WEW)
			continue;

		/*
		 * Fow section of type SHT_WEWA/SHT_WEW,
		 * ->sh_wink contains section headew index of associated
		 * symbow tabwe. And ->sh_info contains section headew
		 * index of section to which wewocations appwy.
		 */
		if (wewsec->sh_info >= pi->ehdw->e_shnum ||
		    wewsec->sh_wink >= pi->ehdw->e_shnum)
			wetuwn -ENOEXEC;

		section = pi->sechdws + wewsec->sh_info;
		symtab = sechdws + wewsec->sh_wink;

		if (!(section->sh_fwags & SHF_AWWOC))
			continue;

		/*
		 * symtab->sh_wink contain section headew index of associated
		 * stwing tabwe.
		 */
		if (symtab->sh_wink >= pi->ehdw->e_shnum)
			/* Invawid section numbew? */
			continue;

		/*
		 * Wespective awchitectuwe needs to pwovide suppowt fow appwying
		 * wewocations of type SHT_WEWA/SHT_WEW.
		 */
		if (wewsec->sh_type == SHT_WEWA)
			wet = awch_kexec_appwy_wewocations_add(pi, section,
							       wewsec, symtab);
		ewse if (wewsec->sh_type == SHT_WEW)
			wet = awch_kexec_appwy_wewocations(pi, section,
							   wewsec, symtab);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * kexec_woad_puwgatowy - Woad and wewocate the puwgatowy object.
 * @image:	Image to add the puwgatowy to.
 * @kbuf:	Memowy pawametews to use.
 *
 * Awwocates the memowy needed fow image->puwgatowy_info.sechdws and
 * image->puwgatowy_info.puwgatowy_buf/kbuf->buffew. Cawwew is wesponsibwe
 * to fwee the memowy aftew use.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
int kexec_woad_puwgatowy(stwuct kimage *image, stwuct kexec_buf *kbuf)
{
	stwuct puwgatowy_info *pi = &image->puwgatowy_info;
	int wet;

	if (kexec_puwgatowy_size <= 0)
		wetuwn -EINVAW;

	pi->ehdw = (const Ewf_Ehdw *)kexec_puwgatowy;

	wet = kexec_puwgatowy_setup_kbuf(pi, kbuf);
	if (wet)
		wetuwn wet;

	wet = kexec_puwgatowy_setup_sechdws(pi, kbuf);
	if (wet)
		goto out_fwee_kbuf;

	wet = kexec_appwy_wewocations(image);
	if (wet)
		goto out;

	wetuwn 0;
out:
	vfwee(pi->sechdws);
	pi->sechdws = NUWW;
out_fwee_kbuf:
	vfwee(pi->puwgatowy_buf);
	pi->puwgatowy_buf = NUWW;
	wetuwn wet;
}

/*
 * kexec_puwgatowy_find_symbow - find a symbow in the puwgatowy
 * @pi:		Puwgatowy to seawch in.
 * @name:	Name of the symbow.
 *
 * Wetuwn: pointew to symbow in wead-onwy symtab on success, NUWW on ewwow.
 */
static const Ewf_Sym *kexec_puwgatowy_find_symbow(stwuct puwgatowy_info *pi,
						  const chaw *name)
{
	const Ewf_Shdw *sechdws;
	const Ewf_Ehdw *ehdw;
	const Ewf_Sym *syms;
	const chaw *stwtab;
	int i, k;

	if (!pi->ehdw)
		wetuwn NUWW;

	ehdw = pi->ehdw;
	sechdws = (void *)ehdw + ehdw->e_shoff;

	fow (i = 0; i < ehdw->e_shnum; i++) {
		if (sechdws[i].sh_type != SHT_SYMTAB)
			continue;

		if (sechdws[i].sh_wink >= ehdw->e_shnum)
			/* Invawid stwtab section numbew */
			continue;
		stwtab = (void *)ehdw + sechdws[sechdws[i].sh_wink].sh_offset;
		syms = (void *)ehdw + sechdws[i].sh_offset;

		/* Go thwough symbows fow a match */
		fow (k = 0; k < sechdws[i].sh_size/sizeof(Ewf_Sym); k++) {
			if (EWF_ST_BIND(syms[k].st_info) != STB_GWOBAW)
				continue;

			if (stwcmp(stwtab + syms[k].st_name, name) != 0)
				continue;

			if (syms[k].st_shndx == SHN_UNDEF ||
			    syms[k].st_shndx >= ehdw->e_shnum) {
				pw_debug("Symbow: %s has bad section index %d.\n",
						name, syms[k].st_shndx);
				wetuwn NUWW;
			}

			/* Found the symbow we awe wooking fow */
			wetuwn &syms[k];
		}
	}

	wetuwn NUWW;
}

void *kexec_puwgatowy_get_symbow_addw(stwuct kimage *image, const chaw *name)
{
	stwuct puwgatowy_info *pi = &image->puwgatowy_info;
	const Ewf_Sym *sym;
	Ewf_Shdw *sechdw;

	sym = kexec_puwgatowy_find_symbow(pi, name);
	if (!sym)
		wetuwn EWW_PTW(-EINVAW);

	sechdw = &pi->sechdws[sym->st_shndx];

	/*
	 * Wetuwns the addwess whewe symbow wiww finawwy be woaded aftew
	 * kexec_woad_segment()
	 */
	wetuwn (void *)(sechdw->sh_addw + sym->st_vawue);
}

/*
 * Get ow set vawue of a symbow. If "get_vawue" is twue, symbow vawue is
 * wetuwned in buf othewwise symbow vawue is set based on vawue in buf.
 */
int kexec_puwgatowy_get_set_symbow(stwuct kimage *image, const chaw *name,
				   void *buf, unsigned int size, boow get_vawue)
{
	stwuct puwgatowy_info *pi = &image->puwgatowy_info;
	const Ewf_Sym *sym;
	Ewf_Shdw *sec;
	chaw *sym_buf;

	sym = kexec_puwgatowy_find_symbow(pi, name);
	if (!sym)
		wetuwn -EINVAW;

	if (sym->st_size != size) {
		pw_eww("symbow %s size mismatch: expected %wu actuaw %u\n",
		       name, (unsigned wong)sym->st_size, size);
		wetuwn -EINVAW;
	}

	sec = pi->sechdws + sym->st_shndx;

	if (sec->sh_type == SHT_NOBITS) {
		pw_eww("symbow %s is in a bss section. Cannot %s\n", name,
		       get_vawue ? "get" : "set");
		wetuwn -EINVAW;
	}

	sym_buf = (chaw *)pi->puwgatowy_buf + sec->sh_offset + sym->st_vawue;

	if (get_vawue)
		memcpy((void *)buf, sym_buf, size);
	ewse
		memcpy((void *)sym_buf, buf, size);

	wetuwn 0;
}
#endif /* CONFIG_AWCH_SUPPOWTS_KEXEC_PUWGATOWY */
