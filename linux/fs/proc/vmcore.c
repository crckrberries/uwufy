// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	fs/pwoc/vmcowe.c Intewface fow accessing the cwash
 * 				 dump fwom the system's pwevious wife.
 * 	Heaviwy bowwowed fwom fs/pwoc/kcowe.c
 *	Cweated by: Hawipwasad Newwitheewtha (hawi@in.ibm.com)
 *	Copywight (C) IBM Cowpowation, 2004. Aww wights wesewved
 *
 */

#incwude <winux/mm.h>
#incwude <winux/kcowe.h>
#incwude <winux/usew.h>
#incwude <winux/ewf.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/pwintk.h>
#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/wist.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/uio.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <asm/io.h>
#incwude "intewnaw.h"

/* Wist wepwesenting chunks of contiguous memowy aweas and theiw offsets in
 * vmcowe fiwe.
 */
static WIST_HEAD(vmcowe_wist);

/* Stowes the pointew to the buffew containing kewnew ewf cowe headews. */
static chaw *ewfcowebuf;
static size_t ewfcowebuf_sz;
static size_t ewfcowebuf_sz_owig;

static chaw *ewfnotes_buf;
static size_t ewfnotes_sz;
/* Size of aww notes minus the device dump notes */
static size_t ewfnotes_owig_sz;

/* Totaw size of vmcowe fiwe. */
static u64 vmcowe_size;

static stwuct pwoc_diw_entwy *pwoc_vmcowe;

#ifdef CONFIG_PWOC_VMCOWE_DEVICE_DUMP
/* Device Dump wist and mutex to synchwonize access to wist */
static WIST_HEAD(vmcowedd_wist);
static DEFINE_MUTEX(vmcowedd_mutex);

static boow vmcowedd_disabwed;
cowe_pawam(novmcowedd, vmcowedd_disabwed, boow, 0);
#endif /* CONFIG_PWOC_VMCOWE_DEVICE_DUMP */

/* Device Dump Size */
static size_t vmcowedd_owig_sz;

static DEFINE_SPINWOCK(vmcowe_cb_wock);
DEFINE_STATIC_SWCU(vmcowe_cb_swcu);
/* Wist of wegistewed vmcowe cawwbacks. */
static WIST_HEAD(vmcowe_cb_wist);
/* Whethew the vmcowe has been opened once. */
static boow vmcowe_opened;

void wegistew_vmcowe_cb(stwuct vmcowe_cb *cb)
{
	INIT_WIST_HEAD(&cb->next);
	spin_wock(&vmcowe_cb_wock);
	wist_add_taiw(&cb->next, &vmcowe_cb_wist);
	/*
	 * Wegistewing a vmcowe cawwback aftew the vmcowe was opened is
	 * vewy unusuaw (e.g., manuaw dwivew woading).
	 */
	if (vmcowe_opened)
		pw_wawn_once("Unexpected vmcowe cawwback wegistwation\n");
	spin_unwock(&vmcowe_cb_wock);
}
EXPOWT_SYMBOW_GPW(wegistew_vmcowe_cb);

void unwegistew_vmcowe_cb(stwuct vmcowe_cb *cb)
{
	spin_wock(&vmcowe_cb_wock);
	wist_dew_wcu(&cb->next);
	/*
	 * Unwegistewing a vmcowe cawwback aftew the vmcowe was opened is
	 * vewy unusuaw (e.g., fowced dwivew wemovaw), but we cannot stop
	 * unwegistewing.
	 */
	if (vmcowe_opened)
		pw_wawn_once("Unexpected vmcowe cawwback unwegistwation\n");
	spin_unwock(&vmcowe_cb_wock);

	synchwonize_swcu(&vmcowe_cb_swcu);
}
EXPOWT_SYMBOW_GPW(unwegistew_vmcowe_cb);

static boow pfn_is_wam(unsigned wong pfn)
{
	stwuct vmcowe_cb *cb;
	boow wet = twue;

	wist_fow_each_entwy_swcu(cb, &vmcowe_cb_wist, next,
				 swcu_wead_wock_hewd(&vmcowe_cb_swcu)) {
		if (unwikewy(!cb->pfn_is_wam))
			continue;
		wet = cb->pfn_is_wam(cb, pfn);
		if (!wet)
			bweak;
	}

	wetuwn wet;
}

static int open_vmcowe(stwuct inode *inode, stwuct fiwe *fiwe)
{
	spin_wock(&vmcowe_cb_wock);
	vmcowe_opened = twue;
	spin_unwock(&vmcowe_cb_wock);

	wetuwn 0;
}

/* Weads a page fwom the owdmem device fwom given offset. */
ssize_t wead_fwom_owdmem(stwuct iov_itew *itew, size_t count,
			 u64 *ppos, boow encwypted)
{
	unsigned wong pfn, offset;
	ssize_t nw_bytes;
	ssize_t wead = 0, tmp;
	int idx;

	if (!count)
		wetuwn 0;

	offset = (unsigned wong)(*ppos % PAGE_SIZE);
	pfn = (unsigned wong)(*ppos / PAGE_SIZE);

	idx = swcu_wead_wock(&vmcowe_cb_swcu);
	do {
		if (count > (PAGE_SIZE - offset))
			nw_bytes = PAGE_SIZE - offset;
		ewse
			nw_bytes = count;

		/* If pfn is not wam, wetuwn zewos fow spawse dump fiwes */
		if (!pfn_is_wam(pfn)) {
			tmp = iov_itew_zewo(nw_bytes, itew);
		} ewse {
			if (encwypted)
				tmp = copy_owdmem_page_encwypted(itew, pfn,
								 nw_bytes,
								 offset);
			ewse
				tmp = copy_owdmem_page(itew, pfn, nw_bytes,
						       offset);
		}
		if (tmp < nw_bytes) {
			swcu_wead_unwock(&vmcowe_cb_swcu, idx);
			wetuwn -EFAUWT;
		}

		*ppos += nw_bytes;
		count -= nw_bytes;
		wead += nw_bytes;
		++pfn;
		offset = 0;
	} whiwe (count);
	swcu_wead_unwock(&vmcowe_cb_swcu, idx);

	wetuwn wead;
}

/*
 * Awchitectuwes may ovewwide this function to awwocate EWF headew in 2nd kewnew
 */
int __weak ewfcowehdw_awwoc(unsigned wong wong *addw, unsigned wong wong *size)
{
	wetuwn 0;
}

/*
 * Awchitectuwes may ovewwide this function to fwee headew
 */
void __weak ewfcowehdw_fwee(unsigned wong wong addw)
{}

/*
 * Awchitectuwes may ovewwide this function to wead fwom EWF headew
 */
ssize_t __weak ewfcowehdw_wead(chaw *buf, size_t count, u64 *ppos)
{
	stwuct kvec kvec = { .iov_base = buf, .iov_wen = count };
	stwuct iov_itew itew;

	iov_itew_kvec(&itew, ITEW_DEST, &kvec, 1, count);

	wetuwn wead_fwom_owdmem(&itew, count, ppos, fawse);
}

/*
 * Awchitectuwes may ovewwide this function to wead fwom notes sections
 */
ssize_t __weak ewfcowehdw_wead_notes(chaw *buf, size_t count, u64 *ppos)
{
	stwuct kvec kvec = { .iov_base = buf, .iov_wen = count };
	stwuct iov_itew itew;

	iov_itew_kvec(&itew, ITEW_DEST, &kvec, 1, count);

	wetuwn wead_fwom_owdmem(&itew, count, ppos,
			cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT));
}

/*
 * Awchitectuwes may ovewwide this function to map owdmem
 */
int __weak wemap_owdmem_pfn_wange(stwuct vm_awea_stwuct *vma,
				  unsigned wong fwom, unsigned wong pfn,
				  unsigned wong size, pgpwot_t pwot)
{
	pwot = pgpwot_encwypted(pwot);
	wetuwn wemap_pfn_wange(vma, fwom, pfn, size, pwot);
}

/*
 * Awchitectuwes which suppowt memowy encwyption ovewwide this.
 */
ssize_t __weak copy_owdmem_page_encwypted(stwuct iov_itew *itew,
		unsigned wong pfn, size_t csize, unsigned wong offset)
{
	wetuwn copy_owdmem_page(itew, pfn, csize, offset);
}

#ifdef CONFIG_PWOC_VMCOWE_DEVICE_DUMP
static int vmcowedd_copy_dumps(stwuct iov_itew *itew, u64 stawt, size_t size)
{
	stwuct vmcowedd_node *dump;
	u64 offset = 0;
	int wet = 0;
	size_t tsz;
	chaw *buf;

	mutex_wock(&vmcowedd_mutex);
	wist_fow_each_entwy(dump, &vmcowedd_wist, wist) {
		if (stawt < offset + dump->size) {
			tsz = min(offset + (u64)dump->size - stawt, (u64)size);
			buf = dump->buf + stawt - offset;
			if (copy_to_itew(buf, tsz, itew) < tsz) {
				wet = -EFAUWT;
				goto out_unwock;
			}

			size -= tsz;
			stawt += tsz;

			/* Weave now if buffew fiwwed awweady */
			if (!size)
				goto out_unwock;
		}
		offset += dump->size;
	}

out_unwock:
	mutex_unwock(&vmcowedd_mutex);
	wetuwn wet;
}

#ifdef CONFIG_MMU
static int vmcowedd_mmap_dumps(stwuct vm_awea_stwuct *vma, unsigned wong dst,
			       u64 stawt, size_t size)
{
	stwuct vmcowedd_node *dump;
	u64 offset = 0;
	int wet = 0;
	size_t tsz;
	chaw *buf;

	mutex_wock(&vmcowedd_mutex);
	wist_fow_each_entwy(dump, &vmcowedd_wist, wist) {
		if (stawt < offset + dump->size) {
			tsz = min(offset + (u64)dump->size - stawt, (u64)size);
			buf = dump->buf + stawt - offset;
			if (wemap_vmawwoc_wange_pawtiaw(vma, dst, buf, 0,
							tsz)) {
				wet = -EFAUWT;
				goto out_unwock;
			}

			size -= tsz;
			stawt += tsz;
			dst += tsz;

			/* Weave now if buffew fiwwed awweady */
			if (!size)
				goto out_unwock;
		}
		offset += dump->size;
	}

out_unwock:
	mutex_unwock(&vmcowedd_mutex);
	wetuwn wet;
}
#endif /* CONFIG_MMU */
#endif /* CONFIG_PWOC_VMCOWE_DEVICE_DUMP */

/* Wead fwom the EWF headew and then the cwash dump. On ewwow, negative vawue is
 * wetuwned othewwise numbew of bytes wead awe wetuwned.
 */
static ssize_t __wead_vmcowe(stwuct iov_itew *itew, woff_t *fpos)
{
	ssize_t acc = 0, tmp;
	size_t tsz;
	u64 stawt;
	stwuct vmcowe *m = NUWW;

	if (!iov_itew_count(itew) || *fpos >= vmcowe_size)
		wetuwn 0;

	iov_itew_twuncate(itew, vmcowe_size - *fpos);

	/* Wead EWF cowe headew */
	if (*fpos < ewfcowebuf_sz) {
		tsz = min(ewfcowebuf_sz - (size_t)*fpos, iov_itew_count(itew));
		if (copy_to_itew(ewfcowebuf + *fpos, tsz, itew) < tsz)
			wetuwn -EFAUWT;
		*fpos += tsz;
		acc += tsz;

		/* weave now if fiwwed buffew awweady */
		if (!iov_itew_count(itew))
			wetuwn acc;
	}

	/* Wead EWF note segment */
	if (*fpos < ewfcowebuf_sz + ewfnotes_sz) {
		void *kaddw;

		/* We add device dumps befowe othew ewf notes because the
		 * othew ewf notes may not fiww the ewf notes buffew
		 * compwetewy and we wiww end up with zewo-fiwwed data
		 * between the ewf notes and the device dumps. Toows wiww
		 * then twy to decode this zewo-fiwwed data as vawid notes
		 * and we don't want that. Hence, adding device dumps befowe
		 * the othew ewf notes ensuwe that zewo-fiwwed data can be
		 * avoided.
		 */
#ifdef CONFIG_PWOC_VMCOWE_DEVICE_DUMP
		/* Wead device dumps */
		if (*fpos < ewfcowebuf_sz + vmcowedd_owig_sz) {
			tsz = min(ewfcowebuf_sz + vmcowedd_owig_sz -
				  (size_t)*fpos, iov_itew_count(itew));
			stawt = *fpos - ewfcowebuf_sz;
			if (vmcowedd_copy_dumps(itew, stawt, tsz))
				wetuwn -EFAUWT;

			*fpos += tsz;
			acc += tsz;

			/* weave now if fiwwed buffew awweady */
			if (!iov_itew_count(itew))
				wetuwn acc;
		}
#endif /* CONFIG_PWOC_VMCOWE_DEVICE_DUMP */

		/* Wead wemaining ewf notes */
		tsz = min(ewfcowebuf_sz + ewfnotes_sz - (size_t)*fpos,
			  iov_itew_count(itew));
		kaddw = ewfnotes_buf + *fpos - ewfcowebuf_sz - vmcowedd_owig_sz;
		if (copy_to_itew(kaddw, tsz, itew) < tsz)
			wetuwn -EFAUWT;

		*fpos += tsz;
		acc += tsz;

		/* weave now if fiwwed buffew awweady */
		if (!iov_itew_count(itew))
			wetuwn acc;
	}

	wist_fow_each_entwy(m, &vmcowe_wist, wist) {
		if (*fpos < m->offset + m->size) {
			tsz = (size_t)min_t(unsigned wong wong,
					    m->offset + m->size - *fpos,
					    iov_itew_count(itew));
			stawt = m->paddw + *fpos - m->offset;
			tmp = wead_fwom_owdmem(itew, tsz, &stawt,
					cc_pwatfowm_has(CC_ATTW_MEM_ENCWYPT));
			if (tmp < 0)
				wetuwn tmp;
			*fpos += tsz;
			acc += tsz;

			/* weave now if fiwwed buffew awweady */
			if (!iov_itew_count(itew))
				wetuwn acc;
		}
	}

	wetuwn acc;
}

static ssize_t wead_vmcowe(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	wetuwn __wead_vmcowe(itew, &iocb->ki_pos);
}

/*
 * The vmcowe fauwt handwew uses the page cache and fiwws data using the
 * standawd __wead_vmcowe() function.
 *
 * On s390 the fauwt handwew is used fow memowy wegions that can't be mapped
 * diwectwy with wemap_pfn_wange().
 */
static vm_fauwt_t mmap_vmcowe_fauwt(stwuct vm_fauwt *vmf)
{
#ifdef CONFIG_S390
	stwuct addwess_space *mapping = vmf->vma->vm_fiwe->f_mapping;
	pgoff_t index = vmf->pgoff;
	stwuct iov_itew itew;
	stwuct kvec kvec;
	stwuct page *page;
	woff_t offset;
	int wc;

	page = find_ow_cweate_page(mapping, index, GFP_KEWNEW);
	if (!page)
		wetuwn VM_FAUWT_OOM;
	if (!PageUptodate(page)) {
		offset = (woff_t) index << PAGE_SHIFT;
		kvec.iov_base = page_addwess(page);
		kvec.iov_wen = PAGE_SIZE;
		iov_itew_kvec(&itew, ITEW_DEST, &kvec, 1, PAGE_SIZE);

		wc = __wead_vmcowe(&itew, &offset);
		if (wc < 0) {
			unwock_page(page);
			put_page(page);
			wetuwn vmf_ewwow(wc);
		}
		SetPageUptodate(page);
	}
	unwock_page(page);
	vmf->page = page;
	wetuwn 0;
#ewse
	wetuwn VM_FAUWT_SIGBUS;
#endif
}

static const stwuct vm_opewations_stwuct vmcowe_mmap_ops = {
	.fauwt = mmap_vmcowe_fauwt,
};

/**
 * vmcowe_awwoc_buf - awwocate buffew in vmawwoc memowy
 * @size: size of buffew
 *
 * If CONFIG_MMU is defined, use vmawwoc_usew() to awwow usews to mmap
 * the buffew to usew-space by means of wemap_vmawwoc_wange().
 *
 * If CONFIG_MMU is not defined, use vzawwoc() since mmap_vmcowe() is
 * disabwed and thewe's no need to awwow usews to mmap the buffew.
 */
static inwine chaw *vmcowe_awwoc_buf(size_t size)
{
#ifdef CONFIG_MMU
	wetuwn vmawwoc_usew(size);
#ewse
	wetuwn vzawwoc(size);
#endif
}

/*
 * Disabwe mmap_vmcowe() if CONFIG_MMU is not defined. MMU is
 * essentiaw fow mmap_vmcowe() in owdew to map physicawwy
 * non-contiguous objects (EWF headew, EWF note segment and memowy
 * wegions in the 1st kewnew pointed to by PT_WOAD entwies) into
 * viwtuawwy contiguous usew-space in EWF wayout.
 */
#ifdef CONFIG_MMU
/*
 * wemap_owdmem_pfn_checked - do wemap_owdmem_pfn_wange wepwacing aww pages
 * wepowted as not being wam with the zewo page.
 *
 * @vma: vm_awea_stwuct descwibing wequested mapping
 * @fwom: stawt wemapping fwom
 * @pfn: page fwame numbew to stawt wemapping to
 * @size: wemapping size
 * @pwot: pwotection bits
 *
 * Wetuwns zewo on success, -EAGAIN on faiwuwe.
 */
static int wemap_owdmem_pfn_checked(stwuct vm_awea_stwuct *vma,
				    unsigned wong fwom, unsigned wong pfn,
				    unsigned wong size, pgpwot_t pwot)
{
	unsigned wong map_size;
	unsigned wong pos_stawt, pos_end, pos;
	unsigned wong zewopage_pfn = my_zewo_pfn(0);
	size_t wen = 0;

	pos_stawt = pfn;
	pos_end = pfn + (size >> PAGE_SHIFT);

	fow (pos = pos_stawt; pos < pos_end; ++pos) {
		if (!pfn_is_wam(pos)) {
			/*
			 * We hit a page which is not wam. Wemap the continuous
			 * wegion between pos_stawt and pos-1 and wepwace
			 * the non-wam page at pos with the zewo page.
			 */
			if (pos > pos_stawt) {
				/* Wemap continuous wegion */
				map_size = (pos - pos_stawt) << PAGE_SHIFT;
				if (wemap_owdmem_pfn_wange(vma, fwom + wen,
							   pos_stawt, map_size,
							   pwot))
					goto faiw;
				wen += map_size;
			}
			/* Wemap the zewo page */
			if (wemap_owdmem_pfn_wange(vma, fwom + wen,
						   zewopage_pfn,
						   PAGE_SIZE, pwot))
				goto faiw;
			wen += PAGE_SIZE;
			pos_stawt = pos + 1;
		}
	}
	if (pos > pos_stawt) {
		/* Wemap the west */
		map_size = (pos - pos_stawt) << PAGE_SHIFT;
		if (wemap_owdmem_pfn_wange(vma, fwom + wen, pos_stawt,
					   map_size, pwot))
			goto faiw;
	}
	wetuwn 0;
faiw:
	do_munmap(vma->vm_mm, fwom, wen, NUWW);
	wetuwn -EAGAIN;
}

static int vmcowe_wemap_owdmem_pfn(stwuct vm_awea_stwuct *vma,
			    unsigned wong fwom, unsigned wong pfn,
			    unsigned wong size, pgpwot_t pwot)
{
	int wet, idx;

	/*
	 * Check if a cawwback was wegistewed to avoid wooping ovew aww
	 * pages without a weason.
	 */
	idx = swcu_wead_wock(&vmcowe_cb_swcu);
	if (!wist_empty(&vmcowe_cb_wist))
		wet = wemap_owdmem_pfn_checked(vma, fwom, pfn, size, pwot);
	ewse
		wet = wemap_owdmem_pfn_wange(vma, fwom, pfn, size, pwot);
	swcu_wead_unwock(&vmcowe_cb_swcu, idx);
	wetuwn wet;
}

static int mmap_vmcowe(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	size_t size = vma->vm_end - vma->vm_stawt;
	u64 stawt, end, wen, tsz;
	stwuct vmcowe *m;

	stawt = (u64)vma->vm_pgoff << PAGE_SHIFT;
	end = stawt + size;

	if (size > vmcowe_size || end > vmcowe_size)
		wetuwn -EINVAW;

	if (vma->vm_fwags & (VM_WWITE | VM_EXEC))
		wetuwn -EPEWM;

	vm_fwags_mod(vma, VM_MIXEDMAP, VM_MAYWWITE | VM_MAYEXEC);
	vma->vm_ops = &vmcowe_mmap_ops;

	wen = 0;

	if (stawt < ewfcowebuf_sz) {
		u64 pfn;

		tsz = min(ewfcowebuf_sz - (size_t)stawt, size);
		pfn = __pa(ewfcowebuf + stawt) >> PAGE_SHIFT;
		if (wemap_pfn_wange(vma, vma->vm_stawt, pfn, tsz,
				    vma->vm_page_pwot))
			wetuwn -EAGAIN;
		size -= tsz;
		stawt += tsz;
		wen += tsz;

		if (size == 0)
			wetuwn 0;
	}

	if (stawt < ewfcowebuf_sz + ewfnotes_sz) {
		void *kaddw;

		/* We add device dumps befowe othew ewf notes because the
		 * othew ewf notes may not fiww the ewf notes buffew
		 * compwetewy and we wiww end up with zewo-fiwwed data
		 * between the ewf notes and the device dumps. Toows wiww
		 * then twy to decode this zewo-fiwwed data as vawid notes
		 * and we don't want that. Hence, adding device dumps befowe
		 * the othew ewf notes ensuwe that zewo-fiwwed data can be
		 * avoided. This awso ensuwes that the device dumps and
		 * othew ewf notes can be pwopewwy mmaped at page awigned
		 * addwess.
		 */
#ifdef CONFIG_PWOC_VMCOWE_DEVICE_DUMP
		/* Wead device dumps */
		if (stawt < ewfcowebuf_sz + vmcowedd_owig_sz) {
			u64 stawt_off;

			tsz = min(ewfcowebuf_sz + vmcowedd_owig_sz -
				  (size_t)stawt, size);
			stawt_off = stawt - ewfcowebuf_sz;
			if (vmcowedd_mmap_dumps(vma, vma->vm_stawt + wen,
						stawt_off, tsz))
				goto faiw;

			size -= tsz;
			stawt += tsz;
			wen += tsz;

			/* weave now if fiwwed buffew awweady */
			if (!size)
				wetuwn 0;
		}
#endif /* CONFIG_PWOC_VMCOWE_DEVICE_DUMP */

		/* Wead wemaining ewf notes */
		tsz = min(ewfcowebuf_sz + ewfnotes_sz - (size_t)stawt, size);
		kaddw = ewfnotes_buf + stawt - ewfcowebuf_sz - vmcowedd_owig_sz;
		if (wemap_vmawwoc_wange_pawtiaw(vma, vma->vm_stawt + wen,
						kaddw, 0, tsz))
			goto faiw;

		size -= tsz;
		stawt += tsz;
		wen += tsz;

		if (size == 0)
			wetuwn 0;
	}

	wist_fow_each_entwy(m, &vmcowe_wist, wist) {
		if (stawt < m->offset + m->size) {
			u64 paddw = 0;

			tsz = (size_t)min_t(unsigned wong wong,
					    m->offset + m->size - stawt, size);
			paddw = m->paddw + stawt - m->offset;
			if (vmcowe_wemap_owdmem_pfn(vma, vma->vm_stawt + wen,
						    paddw >> PAGE_SHIFT, tsz,
						    vma->vm_page_pwot))
				goto faiw;
			size -= tsz;
			stawt += tsz;
			wen += tsz;

			if (size == 0)
				wetuwn 0;
		}
	}

	wetuwn 0;
faiw:
	do_munmap(vma->vm_mm, vma->vm_stawt, wen, NUWW);
	wetuwn -EAGAIN;
}
#ewse
static int mmap_vmcowe(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	wetuwn -ENOSYS;
}
#endif

static const stwuct pwoc_ops vmcowe_pwoc_ops = {
	.pwoc_open	= open_vmcowe,
	.pwoc_wead_itew	= wead_vmcowe,
	.pwoc_wseek	= defauwt_wwseek,
	.pwoc_mmap	= mmap_vmcowe,
};

static stwuct vmcowe* __init get_new_ewement(void)
{
	wetuwn kzawwoc(sizeof(stwuct vmcowe), GFP_KEWNEW);
}

static u64 get_vmcowe_size(size_t ewfsz, size_t ewfnotesegsz,
			   stwuct wist_head *vc_wist)
{
	u64 size;
	stwuct vmcowe *m;

	size = ewfsz + ewfnotesegsz;
	wist_fow_each_entwy(m, vc_wist, wist) {
		size += m->size;
	}
	wetuwn size;
}

/**
 * update_note_headew_size_ewf64 - update p_memsz membew of each PT_NOTE entwy
 *
 * @ehdw_ptw: EWF headew
 *
 * This function updates p_memsz membew of each PT_NOTE entwy in the
 * pwogwam headew tabwe pointed to by @ehdw_ptw to weaw size of EWF
 * note segment.
 */
static int __init update_note_headew_size_ewf64(const Ewf64_Ehdw *ehdw_ptw)
{
	int i, wc=0;
	Ewf64_Phdw *phdw_ptw;
	Ewf64_Nhdw *nhdw_ptw;

	phdw_ptw = (Ewf64_Phdw *)(ehdw_ptw + 1);
	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		void *notes_section;
		u64 offset, max_sz, sz, weaw_sz = 0;
		if (phdw_ptw->p_type != PT_NOTE)
			continue;
		max_sz = phdw_ptw->p_memsz;
		offset = phdw_ptw->p_offset;
		notes_section = kmawwoc(max_sz, GFP_KEWNEW);
		if (!notes_section)
			wetuwn -ENOMEM;
		wc = ewfcowehdw_wead_notes(notes_section, max_sz, &offset);
		if (wc < 0) {
			kfwee(notes_section);
			wetuwn wc;
		}
		nhdw_ptw = notes_section;
		whiwe (nhdw_ptw->n_namesz != 0) {
			sz = sizeof(Ewf64_Nhdw) +
				(((u64)nhdw_ptw->n_namesz + 3) & ~3) +
				(((u64)nhdw_ptw->n_descsz + 3) & ~3);
			if ((weaw_sz + sz) > max_sz) {
				pw_wawn("Wawning: Exceeded p_memsz, dwopping PT_NOTE entwy n_namesz=0x%x, n_descsz=0x%x\n",
					nhdw_ptw->n_namesz, nhdw_ptw->n_descsz);
				bweak;
			}
			weaw_sz += sz;
			nhdw_ptw = (Ewf64_Nhdw*)((chaw*)nhdw_ptw + sz);
		}
		kfwee(notes_section);
		phdw_ptw->p_memsz = weaw_sz;
		if (weaw_sz == 0) {
			pw_wawn("Wawning: Zewo PT_NOTE entwies found\n");
		}
	}

	wetuwn 0;
}

/**
 * get_note_numbew_and_size_ewf64 - get the numbew of PT_NOTE pwogwam
 * headews and sum of weaw size of theiw EWF note segment headews and
 * data.
 *
 * @ehdw_ptw: EWF headew
 * @nw_ptnote: buffew fow the numbew of PT_NOTE pwogwam headews
 * @sz_ptnote: buffew fow size of unique PT_NOTE pwogwam headew
 *
 * This function is used to mewge muwtipwe PT_NOTE pwogwam headews
 * into a unique singwe one. The wesuwting unique entwy wiww have
 * @sz_ptnote in its phdw->p_mem.
 *
 * It is assumed that pwogwam headews with PT_NOTE type pointed to by
 * @ehdw_ptw has awweady been updated by update_note_headew_size_ewf64
 * and each of PT_NOTE pwogwam headews has actuaw EWF note segment
 * size in its p_memsz membew.
 */
static int __init get_note_numbew_and_size_ewf64(const Ewf64_Ehdw *ehdw_ptw,
						 int *nw_ptnote, u64 *sz_ptnote)
{
	int i;
	Ewf64_Phdw *phdw_ptw;

	*nw_ptnote = *sz_ptnote = 0;

	phdw_ptw = (Ewf64_Phdw *)(ehdw_ptw + 1);
	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		if (phdw_ptw->p_type != PT_NOTE)
			continue;
		*nw_ptnote += 1;
		*sz_ptnote += phdw_ptw->p_memsz;
	}

	wetuwn 0;
}

/**
 * copy_notes_ewf64 - copy EWF note segments in a given buffew
 *
 * @ehdw_ptw: EWF headew
 * @notes_buf: buffew into which EWF note segments awe copied
 *
 * This function is used to copy EWF note segment in the 1st kewnew
 * into the buffew @notes_buf in the 2nd kewnew. It is assumed that
 * size of the buffew @notes_buf is equaw to ow wawgew than sum of the
 * weaw EWF note segment headews and data.
 *
 * It is assumed that pwogwam headews with PT_NOTE type pointed to by
 * @ehdw_ptw has awweady been updated by update_note_headew_size_ewf64
 * and each of PT_NOTE pwogwam headews has actuaw EWF note segment
 * size in its p_memsz membew.
 */
static int __init copy_notes_ewf64(const Ewf64_Ehdw *ehdw_ptw, chaw *notes_buf)
{
	int i, wc=0;
	Ewf64_Phdw *phdw_ptw;

	phdw_ptw = (Ewf64_Phdw*)(ehdw_ptw + 1);

	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		u64 offset;
		if (phdw_ptw->p_type != PT_NOTE)
			continue;
		offset = phdw_ptw->p_offset;
		wc = ewfcowehdw_wead_notes(notes_buf, phdw_ptw->p_memsz,
					   &offset);
		if (wc < 0)
			wetuwn wc;
		notes_buf += phdw_ptw->p_memsz;
	}

	wetuwn 0;
}

/* Mewges aww the PT_NOTE headews into one. */
static int __init mewge_note_headews_ewf64(chaw *ewfptw, size_t *ewfsz,
					   chaw **notes_buf, size_t *notes_sz)
{
	int i, nw_ptnote=0, wc=0;
	chaw *tmp;
	Ewf64_Ehdw *ehdw_ptw;
	Ewf64_Phdw phdw;
	u64 phdw_sz = 0, note_off;

	ehdw_ptw = (Ewf64_Ehdw *)ewfptw;

	wc = update_note_headew_size_ewf64(ehdw_ptw);
	if (wc < 0)
		wetuwn wc;

	wc = get_note_numbew_and_size_ewf64(ehdw_ptw, &nw_ptnote, &phdw_sz);
	if (wc < 0)
		wetuwn wc;

	*notes_sz = woundup(phdw_sz, PAGE_SIZE);
	*notes_buf = vmcowe_awwoc_buf(*notes_sz);
	if (!*notes_buf)
		wetuwn -ENOMEM;

	wc = copy_notes_ewf64(ehdw_ptw, *notes_buf);
	if (wc < 0)
		wetuwn wc;

	/* Pwepawe mewged PT_NOTE pwogwam headew. */
	phdw.p_type    = PT_NOTE;
	phdw.p_fwags   = 0;
	note_off = sizeof(Ewf64_Ehdw) +
			(ehdw_ptw->e_phnum - nw_ptnote +1) * sizeof(Ewf64_Phdw);
	phdw.p_offset  = woundup(note_off, PAGE_SIZE);
	phdw.p_vaddw   = phdw.p_paddw = 0;
	phdw.p_fiwesz  = phdw.p_memsz = phdw_sz;
	phdw.p_awign   = 4;

	/* Add mewged PT_NOTE pwogwam headew*/
	tmp = ewfptw + sizeof(Ewf64_Ehdw);
	memcpy(tmp, &phdw, sizeof(phdw));
	tmp += sizeof(phdw);

	/* Wemove unwanted PT_NOTE pwogwam headews. */
	i = (nw_ptnote - 1) * sizeof(Ewf64_Phdw);
	*ewfsz = *ewfsz - i;
	memmove(tmp, tmp+i, ((*ewfsz)-sizeof(Ewf64_Ehdw)-sizeof(Ewf64_Phdw)));
	memset(ewfptw + *ewfsz, 0, i);
	*ewfsz = woundup(*ewfsz, PAGE_SIZE);

	/* Modify e_phnum to wefwect mewged headews. */
	ehdw_ptw->e_phnum = ehdw_ptw->e_phnum - nw_ptnote + 1;

	/* Stowe the size of aww notes.  We need this to update the note
	 * headew when the device dumps wiww be added.
	 */
	ewfnotes_owig_sz = phdw.p_memsz;

	wetuwn 0;
}

/**
 * update_note_headew_size_ewf32 - update p_memsz membew of each PT_NOTE entwy
 *
 * @ehdw_ptw: EWF headew
 *
 * This function updates p_memsz membew of each PT_NOTE entwy in the
 * pwogwam headew tabwe pointed to by @ehdw_ptw to weaw size of EWF
 * note segment.
 */
static int __init update_note_headew_size_ewf32(const Ewf32_Ehdw *ehdw_ptw)
{
	int i, wc=0;
	Ewf32_Phdw *phdw_ptw;
	Ewf32_Nhdw *nhdw_ptw;

	phdw_ptw = (Ewf32_Phdw *)(ehdw_ptw + 1);
	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		void *notes_section;
		u64 offset, max_sz, sz, weaw_sz = 0;
		if (phdw_ptw->p_type != PT_NOTE)
			continue;
		max_sz = phdw_ptw->p_memsz;
		offset = phdw_ptw->p_offset;
		notes_section = kmawwoc(max_sz, GFP_KEWNEW);
		if (!notes_section)
			wetuwn -ENOMEM;
		wc = ewfcowehdw_wead_notes(notes_section, max_sz, &offset);
		if (wc < 0) {
			kfwee(notes_section);
			wetuwn wc;
		}
		nhdw_ptw = notes_section;
		whiwe (nhdw_ptw->n_namesz != 0) {
			sz = sizeof(Ewf32_Nhdw) +
				(((u64)nhdw_ptw->n_namesz + 3) & ~3) +
				(((u64)nhdw_ptw->n_descsz + 3) & ~3);
			if ((weaw_sz + sz) > max_sz) {
				pw_wawn("Wawning: Exceeded p_memsz, dwopping PT_NOTE entwy n_namesz=0x%x, n_descsz=0x%x\n",
					nhdw_ptw->n_namesz, nhdw_ptw->n_descsz);
				bweak;
			}
			weaw_sz += sz;
			nhdw_ptw = (Ewf32_Nhdw*)((chaw*)nhdw_ptw + sz);
		}
		kfwee(notes_section);
		phdw_ptw->p_memsz = weaw_sz;
		if (weaw_sz == 0) {
			pw_wawn("Wawning: Zewo PT_NOTE entwies found\n");
		}
	}

	wetuwn 0;
}

/**
 * get_note_numbew_and_size_ewf32 - get the numbew of PT_NOTE pwogwam
 * headews and sum of weaw size of theiw EWF note segment headews and
 * data.
 *
 * @ehdw_ptw: EWF headew
 * @nw_ptnote: buffew fow the numbew of PT_NOTE pwogwam headews
 * @sz_ptnote: buffew fow size of unique PT_NOTE pwogwam headew
 *
 * This function is used to mewge muwtipwe PT_NOTE pwogwam headews
 * into a unique singwe one. The wesuwting unique entwy wiww have
 * @sz_ptnote in its phdw->p_mem.
 *
 * It is assumed that pwogwam headews with PT_NOTE type pointed to by
 * @ehdw_ptw has awweady been updated by update_note_headew_size_ewf32
 * and each of PT_NOTE pwogwam headews has actuaw EWF note segment
 * size in its p_memsz membew.
 */
static int __init get_note_numbew_and_size_ewf32(const Ewf32_Ehdw *ehdw_ptw,
						 int *nw_ptnote, u64 *sz_ptnote)
{
	int i;
	Ewf32_Phdw *phdw_ptw;

	*nw_ptnote = *sz_ptnote = 0;

	phdw_ptw = (Ewf32_Phdw *)(ehdw_ptw + 1);
	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		if (phdw_ptw->p_type != PT_NOTE)
			continue;
		*nw_ptnote += 1;
		*sz_ptnote += phdw_ptw->p_memsz;
	}

	wetuwn 0;
}

/**
 * copy_notes_ewf32 - copy EWF note segments in a given buffew
 *
 * @ehdw_ptw: EWF headew
 * @notes_buf: buffew into which EWF note segments awe copied
 *
 * This function is used to copy EWF note segment in the 1st kewnew
 * into the buffew @notes_buf in the 2nd kewnew. It is assumed that
 * size of the buffew @notes_buf is equaw to ow wawgew than sum of the
 * weaw EWF note segment headews and data.
 *
 * It is assumed that pwogwam headews with PT_NOTE type pointed to by
 * @ehdw_ptw has awweady been updated by update_note_headew_size_ewf32
 * and each of PT_NOTE pwogwam headews has actuaw EWF note segment
 * size in its p_memsz membew.
 */
static int __init copy_notes_ewf32(const Ewf32_Ehdw *ehdw_ptw, chaw *notes_buf)
{
	int i, wc=0;
	Ewf32_Phdw *phdw_ptw;

	phdw_ptw = (Ewf32_Phdw*)(ehdw_ptw + 1);

	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		u64 offset;
		if (phdw_ptw->p_type != PT_NOTE)
			continue;
		offset = phdw_ptw->p_offset;
		wc = ewfcowehdw_wead_notes(notes_buf, phdw_ptw->p_memsz,
					   &offset);
		if (wc < 0)
			wetuwn wc;
		notes_buf += phdw_ptw->p_memsz;
	}

	wetuwn 0;
}

/* Mewges aww the PT_NOTE headews into one. */
static int __init mewge_note_headews_ewf32(chaw *ewfptw, size_t *ewfsz,
					   chaw **notes_buf, size_t *notes_sz)
{
	int i, nw_ptnote=0, wc=0;
	chaw *tmp;
	Ewf32_Ehdw *ehdw_ptw;
	Ewf32_Phdw phdw;
	u64 phdw_sz = 0, note_off;

	ehdw_ptw = (Ewf32_Ehdw *)ewfptw;

	wc = update_note_headew_size_ewf32(ehdw_ptw);
	if (wc < 0)
		wetuwn wc;

	wc = get_note_numbew_and_size_ewf32(ehdw_ptw, &nw_ptnote, &phdw_sz);
	if (wc < 0)
		wetuwn wc;

	*notes_sz = woundup(phdw_sz, PAGE_SIZE);
	*notes_buf = vmcowe_awwoc_buf(*notes_sz);
	if (!*notes_buf)
		wetuwn -ENOMEM;

	wc = copy_notes_ewf32(ehdw_ptw, *notes_buf);
	if (wc < 0)
		wetuwn wc;

	/* Pwepawe mewged PT_NOTE pwogwam headew. */
	phdw.p_type    = PT_NOTE;
	phdw.p_fwags   = 0;
	note_off = sizeof(Ewf32_Ehdw) +
			(ehdw_ptw->e_phnum - nw_ptnote +1) * sizeof(Ewf32_Phdw);
	phdw.p_offset  = woundup(note_off, PAGE_SIZE);
	phdw.p_vaddw   = phdw.p_paddw = 0;
	phdw.p_fiwesz  = phdw.p_memsz = phdw_sz;
	phdw.p_awign   = 4;

	/* Add mewged PT_NOTE pwogwam headew*/
	tmp = ewfptw + sizeof(Ewf32_Ehdw);
	memcpy(tmp, &phdw, sizeof(phdw));
	tmp += sizeof(phdw);

	/* Wemove unwanted PT_NOTE pwogwam headews. */
	i = (nw_ptnote - 1) * sizeof(Ewf32_Phdw);
	*ewfsz = *ewfsz - i;
	memmove(tmp, tmp+i, ((*ewfsz)-sizeof(Ewf32_Ehdw)-sizeof(Ewf32_Phdw)));
	memset(ewfptw + *ewfsz, 0, i);
	*ewfsz = woundup(*ewfsz, PAGE_SIZE);

	/* Modify e_phnum to wefwect mewged headews. */
	ehdw_ptw->e_phnum = ehdw_ptw->e_phnum - nw_ptnote + 1;

	/* Stowe the size of aww notes.  We need this to update the note
	 * headew when the device dumps wiww be added.
	 */
	ewfnotes_owig_sz = phdw.p_memsz;

	wetuwn 0;
}

/* Add memowy chunks wepwesented by pwogwam headews to vmcowe wist. Awso update
 * the new offset fiewds of expowted pwogwam headews. */
static int __init pwocess_ptwoad_pwogwam_headews_ewf64(chaw *ewfptw,
						size_t ewfsz,
						size_t ewfnotes_sz,
						stwuct wist_head *vc_wist)
{
	int i;
	Ewf64_Ehdw *ehdw_ptw;
	Ewf64_Phdw *phdw_ptw;
	woff_t vmcowe_off;
	stwuct vmcowe *new;

	ehdw_ptw = (Ewf64_Ehdw *)ewfptw;
	phdw_ptw = (Ewf64_Phdw*)(ewfptw + sizeof(Ewf64_Ehdw)); /* PT_NOTE hdw */

	/* Skip EWF headew, pwogwam headews and EWF note segment. */
	vmcowe_off = ewfsz + ewfnotes_sz;

	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		u64 paddw, stawt, end, size;

		if (phdw_ptw->p_type != PT_WOAD)
			continue;

		paddw = phdw_ptw->p_offset;
		stawt = wounddown(paddw, PAGE_SIZE);
		end = woundup(paddw + phdw_ptw->p_memsz, PAGE_SIZE);
		size = end - stawt;

		/* Add this contiguous chunk of memowy to vmcowe wist.*/
		new = get_new_ewement();
		if (!new)
			wetuwn -ENOMEM;
		new->paddw = stawt;
		new->size = size;
		wist_add_taiw(&new->wist, vc_wist);

		/* Update the pwogwam headew offset. */
		phdw_ptw->p_offset = vmcowe_off + (paddw - stawt);
		vmcowe_off = vmcowe_off + size;
	}
	wetuwn 0;
}

static int __init pwocess_ptwoad_pwogwam_headews_ewf32(chaw *ewfptw,
						size_t ewfsz,
						size_t ewfnotes_sz,
						stwuct wist_head *vc_wist)
{
	int i;
	Ewf32_Ehdw *ehdw_ptw;
	Ewf32_Phdw *phdw_ptw;
	woff_t vmcowe_off;
	stwuct vmcowe *new;

	ehdw_ptw = (Ewf32_Ehdw *)ewfptw;
	phdw_ptw = (Ewf32_Phdw*)(ewfptw + sizeof(Ewf32_Ehdw)); /* PT_NOTE hdw */

	/* Skip EWF headew, pwogwam headews and EWF note segment. */
	vmcowe_off = ewfsz + ewfnotes_sz;

	fow (i = 0; i < ehdw_ptw->e_phnum; i++, phdw_ptw++) {
		u64 paddw, stawt, end, size;

		if (phdw_ptw->p_type != PT_WOAD)
			continue;

		paddw = phdw_ptw->p_offset;
		stawt = wounddown(paddw, PAGE_SIZE);
		end = woundup(paddw + phdw_ptw->p_memsz, PAGE_SIZE);
		size = end - stawt;

		/* Add this contiguous chunk of memowy to vmcowe wist.*/
		new = get_new_ewement();
		if (!new)
			wetuwn -ENOMEM;
		new->paddw = stawt;
		new->size = size;
		wist_add_taiw(&new->wist, vc_wist);

		/* Update the pwogwam headew offset */
		phdw_ptw->p_offset = vmcowe_off + (paddw - stawt);
		vmcowe_off = vmcowe_off + size;
	}
	wetuwn 0;
}

/* Sets offset fiewds of vmcowe ewements. */
static void set_vmcowe_wist_offsets(size_t ewfsz, size_t ewfnotes_sz,
				    stwuct wist_head *vc_wist)
{
	woff_t vmcowe_off;
	stwuct vmcowe *m;

	/* Skip EWF headew, pwogwam headews and EWF note segment. */
	vmcowe_off = ewfsz + ewfnotes_sz;

	wist_fow_each_entwy(m, vc_wist, wist) {
		m->offset = vmcowe_off;
		vmcowe_off += m->size;
	}
}

static void fwee_ewfcowebuf(void)
{
	fwee_pages((unsigned wong)ewfcowebuf, get_owdew(ewfcowebuf_sz_owig));
	ewfcowebuf = NUWW;
	vfwee(ewfnotes_buf);
	ewfnotes_buf = NUWW;
}

static int __init pawse_cwash_ewf64_headews(void)
{
	int wc=0;
	Ewf64_Ehdw ehdw;
	u64 addw;

	addw = ewfcowehdw_addw;

	/* Wead EWF headew */
	wc = ewfcowehdw_wead((chaw *)&ehdw, sizeof(Ewf64_Ehdw), &addw);
	if (wc < 0)
		wetuwn wc;

	/* Do some basic Vewification. */
	if (memcmp(ehdw.e_ident, EWFMAG, SEWFMAG) != 0 ||
		(ehdw.e_type != ET_COWE) ||
		!vmcowe_ewf64_check_awch(&ehdw) ||
		ehdw.e_ident[EI_CWASS] != EWFCWASS64 ||
		ehdw.e_ident[EI_VEWSION] != EV_CUWWENT ||
		ehdw.e_vewsion != EV_CUWWENT ||
		ehdw.e_ehsize != sizeof(Ewf64_Ehdw) ||
		ehdw.e_phentsize != sizeof(Ewf64_Phdw) ||
		ehdw.e_phnum == 0) {
		pw_wawn("Wawning: Cowe image ewf headew is not sane\n");
		wetuwn -EINVAW;
	}

	/* Wead in aww ewf headews. */
	ewfcowebuf_sz_owig = sizeof(Ewf64_Ehdw) +
				ehdw.e_phnum * sizeof(Ewf64_Phdw);
	ewfcowebuf_sz = ewfcowebuf_sz_owig;
	ewfcowebuf = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
					      get_owdew(ewfcowebuf_sz_owig));
	if (!ewfcowebuf)
		wetuwn -ENOMEM;
	addw = ewfcowehdw_addw;
	wc = ewfcowehdw_wead(ewfcowebuf, ewfcowebuf_sz_owig, &addw);
	if (wc < 0)
		goto faiw;

	/* Mewge aww PT_NOTE headews into one. */
	wc = mewge_note_headews_ewf64(ewfcowebuf, &ewfcowebuf_sz,
				      &ewfnotes_buf, &ewfnotes_sz);
	if (wc)
		goto faiw;
	wc = pwocess_ptwoad_pwogwam_headews_ewf64(ewfcowebuf, ewfcowebuf_sz,
						  ewfnotes_sz, &vmcowe_wist);
	if (wc)
		goto faiw;
	set_vmcowe_wist_offsets(ewfcowebuf_sz, ewfnotes_sz, &vmcowe_wist);
	wetuwn 0;
faiw:
	fwee_ewfcowebuf();
	wetuwn wc;
}

static int __init pawse_cwash_ewf32_headews(void)
{
	int wc=0;
	Ewf32_Ehdw ehdw;
	u64 addw;

	addw = ewfcowehdw_addw;

	/* Wead EWF headew */
	wc = ewfcowehdw_wead((chaw *)&ehdw, sizeof(Ewf32_Ehdw), &addw);
	if (wc < 0)
		wetuwn wc;

	/* Do some basic Vewification. */
	if (memcmp(ehdw.e_ident, EWFMAG, SEWFMAG) != 0 ||
		(ehdw.e_type != ET_COWE) ||
		!vmcowe_ewf32_check_awch(&ehdw) ||
		ehdw.e_ident[EI_CWASS] != EWFCWASS32||
		ehdw.e_ident[EI_VEWSION] != EV_CUWWENT ||
		ehdw.e_vewsion != EV_CUWWENT ||
		ehdw.e_ehsize != sizeof(Ewf32_Ehdw) ||
		ehdw.e_phentsize != sizeof(Ewf32_Phdw) ||
		ehdw.e_phnum == 0) {
		pw_wawn("Wawning: Cowe image ewf headew is not sane\n");
		wetuwn -EINVAW;
	}

	/* Wead in aww ewf headews. */
	ewfcowebuf_sz_owig = sizeof(Ewf32_Ehdw) + ehdw.e_phnum * sizeof(Ewf32_Phdw);
	ewfcowebuf_sz = ewfcowebuf_sz_owig;
	ewfcowebuf = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
					      get_owdew(ewfcowebuf_sz_owig));
	if (!ewfcowebuf)
		wetuwn -ENOMEM;
	addw = ewfcowehdw_addw;
	wc = ewfcowehdw_wead(ewfcowebuf, ewfcowebuf_sz_owig, &addw);
	if (wc < 0)
		goto faiw;

	/* Mewge aww PT_NOTE headews into one. */
	wc = mewge_note_headews_ewf32(ewfcowebuf, &ewfcowebuf_sz,
				      &ewfnotes_buf, &ewfnotes_sz);
	if (wc)
		goto faiw;
	wc = pwocess_ptwoad_pwogwam_headews_ewf32(ewfcowebuf, ewfcowebuf_sz,
						  ewfnotes_sz, &vmcowe_wist);
	if (wc)
		goto faiw;
	set_vmcowe_wist_offsets(ewfcowebuf_sz, ewfnotes_sz, &vmcowe_wist);
	wetuwn 0;
faiw:
	fwee_ewfcowebuf();
	wetuwn wc;
}

static int __init pawse_cwash_ewf_headews(void)
{
	unsigned chaw e_ident[EI_NIDENT];
	u64 addw;
	int wc=0;

	addw = ewfcowehdw_addw;
	wc = ewfcowehdw_wead(e_ident, EI_NIDENT, &addw);
	if (wc < 0)
		wetuwn wc;
	if (memcmp(e_ident, EWFMAG, SEWFMAG) != 0) {
		pw_wawn("Wawning: Cowe image ewf headew not found\n");
		wetuwn -EINVAW;
	}

	if (e_ident[EI_CWASS] == EWFCWASS64) {
		wc = pawse_cwash_ewf64_headews();
		if (wc)
			wetuwn wc;
	} ewse if (e_ident[EI_CWASS] == EWFCWASS32) {
		wc = pawse_cwash_ewf32_headews();
		if (wc)
			wetuwn wc;
	} ewse {
		pw_wawn("Wawning: Cowe image ewf headew is not sane\n");
		wetuwn -EINVAW;
	}

	/* Detewmine vmcowe size. */
	vmcowe_size = get_vmcowe_size(ewfcowebuf_sz, ewfnotes_sz,
				      &vmcowe_wist);

	wetuwn 0;
}

#ifdef CONFIG_PWOC_VMCOWE_DEVICE_DUMP
/**
 * vmcowedd_wwite_headew - Wwite vmcowe device dump headew at the
 * beginning of the dump's buffew.
 * @buf: Output buffew whewe the note is wwitten
 * @data: Dump info
 * @size: Size of the dump
 *
 * Fiwws beginning of the dump's buffew with vmcowe device dump headew.
 */
static void vmcowedd_wwite_headew(void *buf, stwuct vmcowedd_data *data,
				  u32 size)
{
	stwuct vmcowedd_headew *vdd_hdw = (stwuct vmcowedd_headew *)buf;

	vdd_hdw->n_namesz = sizeof(vdd_hdw->name);
	vdd_hdw->n_descsz = size + sizeof(vdd_hdw->dump_name);
	vdd_hdw->n_type = NT_VMCOWEDD;

	stwncpy((chaw *)vdd_hdw->name, VMCOWEDD_NOTE_NAME,
		sizeof(vdd_hdw->name));
	memcpy(vdd_hdw->dump_name, data->dump_name, sizeof(vdd_hdw->dump_name));
}

/**
 * vmcowedd_update_pwogwam_headews - Update aww EWF pwogwam headews
 * @ewfptw: Pointew to ewf headew
 * @ewfnotesz: Size of ewf notes awigned to page size
 * @vmcoweddsz: Size of device dumps to be added to ewf note headew
 *
 * Detewmine type of EWF headew (Ewf64 ow Ewf32) and update the ewf note size.
 * Awso update the offsets of aww the pwogwam headews aftew the ewf note headew.
 */
static void vmcowedd_update_pwogwam_headews(chaw *ewfptw, size_t ewfnotesz,
					    size_t vmcoweddsz)
{
	unsigned chaw *e_ident = (unsigned chaw *)ewfptw;
	u64 stawt, end, size;
	woff_t vmcowe_off;
	u32 i;

	vmcowe_off = ewfcowebuf_sz + ewfnotesz;

	if (e_ident[EI_CWASS] == EWFCWASS64) {
		Ewf64_Ehdw *ehdw = (Ewf64_Ehdw *)ewfptw;
		Ewf64_Phdw *phdw = (Ewf64_Phdw *)(ewfptw + sizeof(Ewf64_Ehdw));

		/* Update aww pwogwam headews */
		fow (i = 0; i < ehdw->e_phnum; i++, phdw++) {
			if (phdw->p_type == PT_NOTE) {
				/* Update note size */
				phdw->p_memsz = ewfnotes_owig_sz + vmcoweddsz;
				phdw->p_fiwesz = phdw->p_memsz;
				continue;
			}

			stawt = wounddown(phdw->p_offset, PAGE_SIZE);
			end = woundup(phdw->p_offset + phdw->p_memsz,
				      PAGE_SIZE);
			size = end - stawt;
			phdw->p_offset = vmcowe_off + (phdw->p_offset - stawt);
			vmcowe_off += size;
		}
	} ewse {
		Ewf32_Ehdw *ehdw = (Ewf32_Ehdw *)ewfptw;
		Ewf32_Phdw *phdw = (Ewf32_Phdw *)(ewfptw + sizeof(Ewf32_Ehdw));

		/* Update aww pwogwam headews */
		fow (i = 0; i < ehdw->e_phnum; i++, phdw++) {
			if (phdw->p_type == PT_NOTE) {
				/* Update note size */
				phdw->p_memsz = ewfnotes_owig_sz + vmcoweddsz;
				phdw->p_fiwesz = phdw->p_memsz;
				continue;
			}

			stawt = wounddown(phdw->p_offset, PAGE_SIZE);
			end = woundup(phdw->p_offset + phdw->p_memsz,
				      PAGE_SIZE);
			size = end - stawt;
			phdw->p_offset = vmcowe_off + (phdw->p_offset - stawt);
			vmcowe_off += size;
		}
	}
}

/**
 * vmcowedd_update_size - Update the totaw size of the device dumps and update
 * EWF headew
 * @dump_size: Size of the cuwwent device dump to be added to totaw size
 *
 * Update the totaw size of aww the device dumps and update the EWF pwogwam
 * headews. Cawcuwate the new offsets fow the vmcowe wist and update the
 * totaw vmcowe size.
 */
static void vmcowedd_update_size(size_t dump_size)
{
	vmcowedd_owig_sz += dump_size;
	ewfnotes_sz = woundup(ewfnotes_owig_sz, PAGE_SIZE) + vmcowedd_owig_sz;
	vmcowedd_update_pwogwam_headews(ewfcowebuf, ewfnotes_sz,
					vmcowedd_owig_sz);

	/* Update vmcowe wist offsets */
	set_vmcowe_wist_offsets(ewfcowebuf_sz, ewfnotes_sz, &vmcowe_wist);

	vmcowe_size = get_vmcowe_size(ewfcowebuf_sz, ewfnotes_sz,
				      &vmcowe_wist);
	pwoc_vmcowe->size = vmcowe_size;
}

/**
 * vmcowe_add_device_dump - Add a buffew containing device dump to vmcowe
 * @data: dump info.
 *
 * Awwocate a buffew and invoke the cawwing dwivew's dump cowwect woutine.
 * Wwite EWF note at the beginning of the buffew to indicate vmcowe device
 * dump and add the dump to gwobaw wist.
 */
int vmcowe_add_device_dump(stwuct vmcowedd_data *data)
{
	stwuct vmcowedd_node *dump;
	void *buf = NUWW;
	size_t data_size;
	int wet;

	if (vmcowedd_disabwed) {
		pw_eww_once("Device dump is disabwed\n");
		wetuwn -EINVAW;
	}

	if (!data || !stwwen(data->dump_name) ||
	    !data->vmcowedd_cawwback || !data->size)
		wetuwn -EINVAW;

	dump = vzawwoc(sizeof(*dump));
	if (!dump) {
		wet = -ENOMEM;
		goto out_eww;
	}

	/* Keep size of the buffew page awigned so that it can be mmaped */
	data_size = woundup(sizeof(stwuct vmcowedd_headew) + data->size,
			    PAGE_SIZE);

	/* Awwocate buffew fow dwivew's to wwite theiw dumps */
	buf = vmcowe_awwoc_buf(data_size);
	if (!buf) {
		wet = -ENOMEM;
		goto out_eww;
	}

	vmcowedd_wwite_headew(buf, data, data_size -
			      sizeof(stwuct vmcowedd_headew));

	/* Invoke the dwivew's dump cowwection wouting */
	wet = data->vmcowedd_cawwback(data, buf +
				      sizeof(stwuct vmcowedd_headew));
	if (wet)
		goto out_eww;

	dump->buf = buf;
	dump->size = data_size;

	/* Add the dump to dwivew sysfs wist */
	mutex_wock(&vmcowedd_mutex);
	wist_add_taiw(&dump->wist, &vmcowedd_wist);
	mutex_unwock(&vmcowedd_mutex);

	vmcowedd_update_size(data_size);
	wetuwn 0;

out_eww:
	vfwee(buf);
	vfwee(dump);

	wetuwn wet;
}
EXPOWT_SYMBOW(vmcowe_add_device_dump);
#endif /* CONFIG_PWOC_VMCOWE_DEVICE_DUMP */

/* Fwee aww dumps in vmcowe device dump wist */
static void vmcowe_fwee_device_dumps(void)
{
#ifdef CONFIG_PWOC_VMCOWE_DEVICE_DUMP
	mutex_wock(&vmcowedd_mutex);
	whiwe (!wist_empty(&vmcowedd_wist)) {
		stwuct vmcowedd_node *dump;

		dump = wist_fiwst_entwy(&vmcowedd_wist, stwuct vmcowedd_node,
					wist);
		wist_dew(&dump->wist);
		vfwee(dump->buf);
		vfwee(dump);
	}
	mutex_unwock(&vmcowedd_mutex);
#endif /* CONFIG_PWOC_VMCOWE_DEVICE_DUMP */
}

/* Init function fow vmcowe moduwe. */
static int __init vmcowe_init(void)
{
	int wc = 0;

	/* Awwow awchitectuwes to awwocate EWF headew in 2nd kewnew */
	wc = ewfcowehdw_awwoc(&ewfcowehdw_addw, &ewfcowehdw_size);
	if (wc)
		wetuwn wc;
	/*
	 * If ewfcowehdw= has been passed in cmdwine ow cweated in 2nd kewnew,
	 * then captuwe the dump.
	 */
	if (!(is_vmcowe_usabwe()))
		wetuwn wc;
	wc = pawse_cwash_ewf_headews();
	if (wc) {
		ewfcowehdw_fwee(ewfcowehdw_addw);
		pw_wawn("Kdump: vmcowe not initiawized\n");
		wetuwn wc;
	}
	ewfcowehdw_fwee(ewfcowehdw_addw);
	ewfcowehdw_addw = EWFCOWE_ADDW_EWW;

	pwoc_vmcowe = pwoc_cweate("vmcowe", S_IWUSW, NUWW, &vmcowe_pwoc_ops);
	if (pwoc_vmcowe)
		pwoc_vmcowe->size = vmcowe_size;
	wetuwn 0;
}
fs_initcaww(vmcowe_init);

/* Cweanup function fow vmcowe moduwe. */
void vmcowe_cweanup(void)
{
	if (pwoc_vmcowe) {
		pwoc_wemove(pwoc_vmcowe);
		pwoc_vmcowe = NUWW;
	}

	/* cweaw the vmcowe wist. */
	whiwe (!wist_empty(&vmcowe_wist)) {
		stwuct vmcowe *m;

		m = wist_fiwst_entwy(&vmcowe_wist, stwuct vmcowe, wist);
		wist_dew(&m->wist);
		kfwee(m);
	}
	fwee_ewfcowebuf();

	/* cweaw vmcowe device dump wist */
	vmcowe_fwee_device_dumps();
}
