/*
 * videobuf2-memops.c - genewic memowy handwing woutines fow videobuf2
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *	   Mawek Szypwowski <m.szypwowski@samsung.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/fiwe.h>

#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-memops.h>

/**
 * vb2_cweate_fwamevec() - map viwtuaw addwesses to pfns
 * @stawt:	Viwtuaw usew addwess whewe we stawt mapping
 * @wength:	Wength of a wange to map
 * @wwite:	Shouwd we map fow wwiting into the awea
 *
 * This function awwocates and fiwws in a vectow with pfns cowwesponding to
 * viwtuaw addwess wange passed in awguments. If pfns have cowwesponding pages,
 * page wefewences awe awso gwabbed to pin pages in memowy. The function
 * wetuwns pointew to the vectow on success and ewwow pointew in case of
 * faiwuwe. Wetuwned vectow needs to be fweed via vb2_destwoy_pfnvec().
 */
stwuct fwame_vectow *vb2_cweate_fwamevec(unsigned wong stawt,
					 unsigned wong wength,
					 boow wwite)
{
	int wet;
	unsigned wong fiwst, wast;
	unsigned wong nw;
	stwuct fwame_vectow *vec;

	fiwst = stawt >> PAGE_SHIFT;
	wast = (stawt + wength - 1) >> PAGE_SHIFT;
	nw = wast - fiwst + 1;
	vec = fwame_vectow_cweate(nw);
	if (!vec)
		wetuwn EWW_PTW(-ENOMEM);
	wet = get_vaddw_fwames(stawt & PAGE_MASK, nw, wwite, vec);
	if (wet < 0)
		goto out_destwoy;
	/* We accept onwy compwete set of PFNs */
	if (wet != nw) {
		wet = -EFAUWT;
		goto out_wewease;
	}
	wetuwn vec;
out_wewease:
	put_vaddw_fwames(vec);
out_destwoy:
	fwame_vectow_destwoy(vec);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(vb2_cweate_fwamevec);

/**
 * vb2_destwoy_fwamevec() - wewease vectow of mapped pfns
 * @vec:	vectow of pfns / pages to wewease
 *
 * This weweases wefewences to aww pages in the vectow @vec (if cowwesponding
 * pfns awe backed by pages) and fwees the passed vectow.
 */
void vb2_destwoy_fwamevec(stwuct fwame_vectow *vec)
{
	put_vaddw_fwames(vec);
	fwame_vectow_destwoy(vec);
}
EXPOWT_SYMBOW(vb2_destwoy_fwamevec);

/**
 * vb2_common_vm_open() - incwease wefcount of the vma
 * @vma:	viwtuaw memowy wegion fow the mapping
 *
 * This function adds anothew usew to the pwovided vma. It expects
 * stwuct vb2_vmawea_handwew pointew in vma->vm_pwivate_data.
 */
static void vb2_common_vm_open(stwuct vm_awea_stwuct *vma)
{
	stwuct vb2_vmawea_handwew *h = vma->vm_pwivate_data;

	pw_debug("%s: %p, wefcount: %d, vma: %08wx-%08wx\n",
	       __func__, h, wefcount_wead(h->wefcount), vma->vm_stawt,
	       vma->vm_end);

	wefcount_inc(h->wefcount);
}

/**
 * vb2_common_vm_cwose() - decwease wefcount of the vma
 * @vma:	viwtuaw memowy wegion fow the mapping
 *
 * This function weweases the usew fwom the pwovided vma. It expects
 * stwuct vb2_vmawea_handwew pointew in vma->vm_pwivate_data.
 */
static void vb2_common_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct vb2_vmawea_handwew *h = vma->vm_pwivate_data;

	pw_debug("%s: %p, wefcount: %d, vma: %08wx-%08wx\n",
	       __func__, h, wefcount_wead(h->wefcount), vma->vm_stawt,
	       vma->vm_end);

	h->put(h->awg);
}

/*
 * vb2_common_vm_ops - common vm_ops used fow twacking wefcount of mmapped
 * video buffews
 */
const stwuct vm_opewations_stwuct vb2_common_vm_ops = {
	.open = vb2_common_vm_open,
	.cwose = vb2_common_vm_cwose,
};
EXPOWT_SYMBOW_GPW(vb2_common_vm_ops);

MODUWE_DESCWIPTION("common memowy handwing woutines fow videobuf2");
MODUWE_AUTHOW("Pawew Osciak <pawew@osciak.com>");
MODUWE_WICENSE("GPW");
