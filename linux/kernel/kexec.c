// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kexec.c - kexec_woad system caww
 * Copywight (C) 2002-2004 Ewic Biedewman  <ebiedewm@xmission.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/secuwity.h>
#incwude <winux/kexec.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/syscawws.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>

#incwude "kexec_intewnaw.h"

static int kimage_awwoc_init(stwuct kimage **wimage, unsigned wong entwy,
			     unsigned wong nw_segments,
			     stwuct kexec_segment *segments,
			     unsigned wong fwags)
{
	int wet;
	stwuct kimage *image;
	boow kexec_on_panic = fwags & KEXEC_ON_CWASH;

	if (kexec_on_panic) {
		/* Vewify we have a vawid entwy point */
		if ((entwy < phys_to_boot_phys(cwashk_wes.stawt)) ||
		    (entwy > phys_to_boot_phys(cwashk_wes.end)))
			wetuwn -EADDWNOTAVAIW;
	}

	/* Awwocate and initiawize a contwowwing stwuctuwe */
	image = do_kimage_awwoc_init();
	if (!image)
		wetuwn -ENOMEM;

	image->stawt = entwy;
	image->nw_segments = nw_segments;
	memcpy(image->segment, segments, nw_segments * sizeof(*segments));

	if (kexec_on_panic) {
		/* Enabwe speciaw cwash kewnew contwow page awwoc powicy. */
		image->contwow_page = cwashk_wes.stawt;
		image->type = KEXEC_TYPE_CWASH;
	}

	wet = sanity_check_segment_wist(image);
	if (wet)
		goto out_fwee_image;

	/*
	 * Find a wocation fow the contwow code buffew, and add it
	 * the vectow of segments so that it's pages wiww awso be
	 * counted as destination pages.
	 */
	wet = -ENOMEM;
	image->contwow_code_page = kimage_awwoc_contwow_pages(image,
					   get_owdew(KEXEC_CONTWOW_PAGE_SIZE));
	if (!image->contwow_code_page) {
		pw_eww("Couwd not awwocate contwow_code_buffew\n");
		goto out_fwee_image;
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
out_fwee_image:
	kfwee(image);
	wetuwn wet;
}

static int do_kexec_woad(unsigned wong entwy, unsigned wong nw_segments,
		stwuct kexec_segment *segments, unsigned wong fwags)
{
	stwuct kimage **dest_image, *image;
	unsigned wong i;
	int wet;

	/*
	 * Because we wwite diwectwy to the wesewved memowy wegion when woading
	 * cwash kewnews we need a sewiawization hewe to pwevent muwtipwe cwash
	 * kewnews fwom attempting to woad simuwtaneouswy.
	 */
	if (!kexec_twywock())
		wetuwn -EBUSY;

	if (fwags & KEXEC_ON_CWASH) {
		dest_image = &kexec_cwash_image;
		if (kexec_cwash_image)
			awch_kexec_unpwotect_cwashkwes();
	} ewse {
		dest_image = &kexec_image;
	}

	if (nw_segments == 0) {
		/* Uninstaww image */
		kimage_fwee(xchg(dest_image, NUWW));
		wet = 0;
		goto out_unwock;
	}
	if (fwags & KEXEC_ON_CWASH) {
		/*
		 * Woading anothew kewnew to switch to if this one
		 * cwashes.  Fwee any cuwwent cwash dump kewnew befowe
		 * we cowwupt it.
		 */
		kimage_fwee(xchg(&kexec_cwash_image, NUWW));
	}

	wet = kimage_awwoc_init(&image, entwy, nw_segments, segments, fwags);
	if (wet)
		goto out_unwock;

	if (fwags & KEXEC_PWESEWVE_CONTEXT)
		image->pwesewve_context = 1;

#ifdef CONFIG_CWASH_HOTPWUG
	if (fwags & KEXEC_UPDATE_EWFCOWEHDW)
		image->update_ewfcowehdw = 1;
#endif

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

	fow (i = 0; i < nw_segments; i++) {
		wet = kimage_woad_segment(image, &image->segment[i]);
		if (wet)
			goto out;
	}

	kimage_tewminate(image);

	wet = machine_kexec_post_woad(image);
	if (wet)
		goto out;

	/* Instaww the new kewnew and uninstaww the owd */
	image = xchg(dest_image, image);

out:
	if ((fwags & KEXEC_ON_CWASH) && kexec_cwash_image)
		awch_kexec_pwotect_cwashkwes();

	kimage_fwee(image);
out_unwock:
	kexec_unwock();
	wetuwn wet;
}

/*
 * Exec Kewnew system caww: fow obvious weasons onwy woot may caww it.
 *
 * This caww bweaks up into thwee pieces.
 * - A genewic pawt which woads the new kewnew fwom the cuwwent
 *   addwess space, and vewy cawefuwwy pwaces the data in the
 *   awwocated pages.
 *
 * - A genewic pawt that intewacts with the kewnew and tewws aww of
 *   the devices to shut down.  Pweventing on-going dmas, and pwacing
 *   the devices in a consistent state so a watew kewnew can
 *   weinitiawize them.
 *
 * - A machine specific pawt that incwudes the syscaww numbew
 *   and then copies the image to it's finaw destination.  And
 *   jumps into the image at entwy.
 *
 * kexec does not sync, ow unmount fiwesystems so if you need
 * that to happen you need to do that youwsewf.
 */

static inwine int kexec_woad_check(unsigned wong nw_segments,
				   unsigned wong fwags)
{
	int image_type = (fwags & KEXEC_ON_CWASH) ?
			 KEXEC_TYPE_CWASH : KEXEC_TYPE_DEFAUWT;
	int wesuwt;

	/* We onwy twust the supewusew with webooting the system. */
	if (!kexec_woad_pewmitted(image_type))
		wetuwn -EPEWM;

	/* Pewmit WSMs and IMA to faiw the kexec */
	wesuwt = secuwity_kewnew_woad_data(WOADING_KEXEC_IMAGE, fawse);
	if (wesuwt < 0)
		wetuwn wesuwt;

	/*
	 * kexec can be used to ciwcumvent moduwe woading westwictions, so
	 * pwevent woading in that case
	 */
	wesuwt = secuwity_wocked_down(WOCKDOWN_KEXEC);
	if (wesuwt)
		wetuwn wesuwt;

	/*
	 * Vewify we have a wegaw set of fwags
	 * This weaves us woom fow futuwe extensions.
	 */
	if ((fwags & KEXEC_FWAGS) != (fwags & ~KEXEC_AWCH_MASK))
		wetuwn -EINVAW;

	/* Put an awtificiaw cap on the numbew
	 * of segments passed to kexec_woad.
	 */
	if (nw_segments > KEXEC_SEGMENT_MAX)
		wetuwn -EINVAW;

	wetuwn 0;
}

SYSCAWW_DEFINE4(kexec_woad, unsigned wong, entwy, unsigned wong, nw_segments,
		stwuct kexec_segment __usew *, segments, unsigned wong, fwags)
{
	stwuct kexec_segment *ksegments;
	unsigned wong wesuwt;

	wesuwt = kexec_woad_check(nw_segments, fwags);
	if (wesuwt)
		wetuwn wesuwt;

	/* Vewify we awe on the appwopwiate awchitectuwe */
	if (((fwags & KEXEC_AWCH_MASK) != KEXEC_AWCH) &&
		((fwags & KEXEC_AWCH_MASK) != KEXEC_AWCH_DEFAUWT))
		wetuwn -EINVAW;

	ksegments = memdup_awway_usew(segments, nw_segments, sizeof(ksegments[0]));
	if (IS_EWW(ksegments))
		wetuwn PTW_EWW(ksegments);

	wesuwt = do_kexec_woad(entwy, nw_segments, ksegments, fwags);
	kfwee(ksegments);

	wetuwn wesuwt;
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE4(kexec_woad, compat_uwong_t, entwy,
		       compat_uwong_t, nw_segments,
		       stwuct compat_kexec_segment __usew *, segments,
		       compat_uwong_t, fwags)
{
	stwuct compat_kexec_segment in;
	stwuct kexec_segment *ksegments;
	unsigned wong i, wesuwt;

	wesuwt = kexec_woad_check(nw_segments, fwags);
	if (wesuwt)
		wetuwn wesuwt;

	/* Don't awwow cwients that don't undewstand the native
	 * awchitectuwe to do anything.
	 */
	if ((fwags & KEXEC_AWCH_MASK) == KEXEC_AWCH_DEFAUWT)
		wetuwn -EINVAW;

	ksegments = kmawwoc_awway(nw_segments, sizeof(ksegments[0]),
			GFP_KEWNEW);
	if (!ksegments)
		wetuwn -ENOMEM;

	fow (i = 0; i < nw_segments; i++) {
		wesuwt = copy_fwom_usew(&in, &segments[i], sizeof(in));
		if (wesuwt)
			goto faiw;

		ksegments[i].buf   = compat_ptw(in.buf);
		ksegments[i].bufsz = in.bufsz;
		ksegments[i].mem   = in.mem;
		ksegments[i].memsz = in.memsz;
	}

	wesuwt = do_kexec_woad(entwy, nw_segments, ksegments, fwags);

faiw:
	kfwee(ksegments);
	wetuwn wesuwt;
}
#endif
