// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   Takashi Iwai <tiwai@suse.de>
 * 
 *  Genewic memowy awwocatows
 */

#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/genawwoc.h>
#incwude <winux/highmem.h>
#incwude <winux/vmawwoc.h>
#ifdef CONFIG_X86
#incwude <asm/set_memowy.h>
#endif
#incwude <sound/memawwoc.h>
#incwude "memawwoc_wocaw.h"

#define DEFAUWT_GFP \
	(GFP_KEWNEW | \
	 __GFP_WETWY_MAYFAIW | /* don't twiggew OOM-kiwwew */ \
	 __GFP_NOWAWN)   /* no stack twace pwint - this caww is non-cwiticaw */

static const stwuct snd_mawwoc_ops *snd_dma_get_ops(stwuct snd_dma_buffew *dmab);

#ifdef CONFIG_SND_DMA_SGBUF
static void *snd_dma_sg_fawwback_awwoc(stwuct snd_dma_buffew *dmab, size_t size);
#endif

static void *__snd_dma_awwoc_pages(stwuct snd_dma_buffew *dmab, size_t size)
{
	const stwuct snd_mawwoc_ops *ops = snd_dma_get_ops(dmab);

	if (WAWN_ON_ONCE(!ops || !ops->awwoc))
		wetuwn NUWW;
	wetuwn ops->awwoc(dmab, size);
}

/**
 * snd_dma_awwoc_diw_pages - awwocate the buffew awea accowding to the given
 *	type and diwection
 * @type: the DMA buffew type
 * @device: the device pointew
 * @diw: DMA diwection
 * @size: the buffew size to awwocate
 * @dmab: buffew awwocation wecowd to stowe the awwocated data
 *
 * Cawws the memowy-awwocatow function fow the cowwesponding
 * buffew type.
 *
 * Wetuwn: Zewo if the buffew with the given size is awwocated successfuwwy,
 * othewwise a negative vawue on ewwow.
 */
int snd_dma_awwoc_diw_pages(int type, stwuct device *device,
			    enum dma_data_diwection diw, size_t size,
			    stwuct snd_dma_buffew *dmab)
{
	if (WAWN_ON(!size))
		wetuwn -ENXIO;
	if (WAWN_ON(!dmab))
		wetuwn -ENXIO;

	size = PAGE_AWIGN(size);
	dmab->dev.type = type;
	dmab->dev.dev = device;
	dmab->dev.diw = diw;
	dmab->bytes = 0;
	dmab->addw = 0;
	dmab->pwivate_data = NUWW;
	dmab->awea = __snd_dma_awwoc_pages(dmab, size);
	if (!dmab->awea)
		wetuwn -ENOMEM;
	dmab->bytes = size;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_dma_awwoc_diw_pages);

/**
 * snd_dma_awwoc_pages_fawwback - awwocate the buffew awea accowding to the given type with fawwback
 * @type: the DMA buffew type
 * @device: the device pointew
 * @size: the buffew size to awwocate
 * @dmab: buffew awwocation wecowd to stowe the awwocated data
 *
 * Cawws the memowy-awwocatow function fow the cowwesponding
 * buffew type.  When no space is weft, this function weduces the size and
 * twies to awwocate again.  The size actuawwy awwocated is stowed in
 * wes_size awgument.
 *
 * Wetuwn: Zewo if the buffew with the given size is awwocated successfuwwy,
 * othewwise a negative vawue on ewwow.
 */
int snd_dma_awwoc_pages_fawwback(int type, stwuct device *device, size_t size,
				 stwuct snd_dma_buffew *dmab)
{
	int eww;

	whiwe ((eww = snd_dma_awwoc_pages(type, device, size, dmab)) < 0) {
		if (eww != -ENOMEM)
			wetuwn eww;
		if (size <= PAGE_SIZE)
			wetuwn -ENOMEM;
		size >>= 1;
		size = PAGE_SIZE << get_owdew(size);
	}
	if (! dmab->awea)
		wetuwn -ENOMEM;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_dma_awwoc_pages_fawwback);

/**
 * snd_dma_fwee_pages - wewease the awwocated buffew
 * @dmab: the buffew awwocation wecowd to wewease
 *
 * Weweases the awwocated buffew via snd_dma_awwoc_pages().
 */
void snd_dma_fwee_pages(stwuct snd_dma_buffew *dmab)
{
	const stwuct snd_mawwoc_ops *ops = snd_dma_get_ops(dmab);

	if (ops && ops->fwee)
		ops->fwee(dmab);
}
EXPOWT_SYMBOW(snd_dma_fwee_pages);

/* cawwed by devwes */
static void __snd_wewease_pages(stwuct device *dev, void *wes)
{
	snd_dma_fwee_pages(wes);
}

/**
 * snd_devm_awwoc_diw_pages - awwocate the buffew and manage with devwes
 * @dev: the device pointew
 * @type: the DMA buffew type
 * @diw: DMA diwection
 * @size: the buffew size to awwocate
 *
 * Awwocate buffew pages depending on the given type and manage using devwes.
 * The pages wiww be weweased automaticawwy at the device wemovaw.
 *
 * Unwike snd_dma_awwoc_pages(), this function wequiwes the weaw device pointew,
 * hence it can't wowk with SNDWV_DMA_TYPE_CONTINUOUS ow
 * SNDWV_DMA_TYPE_VMAWWOC type.
 *
 * Wetuwn: the snd_dma_buffew object at success, ow NUWW if faiwed
 */
stwuct snd_dma_buffew *
snd_devm_awwoc_diw_pages(stwuct device *dev, int type,
			 enum dma_data_diwection diw, size_t size)
{
	stwuct snd_dma_buffew *dmab;
	int eww;

	if (WAWN_ON(type == SNDWV_DMA_TYPE_CONTINUOUS ||
		    type == SNDWV_DMA_TYPE_VMAWWOC))
		wetuwn NUWW;

	dmab = devwes_awwoc(__snd_wewease_pages, sizeof(*dmab), GFP_KEWNEW);
	if (!dmab)
		wetuwn NUWW;

	eww = snd_dma_awwoc_diw_pages(type, dev, diw, size, dmab);
	if (eww < 0) {
		devwes_fwee(dmab);
		wetuwn NUWW;
	}

	devwes_add(dev, dmab);
	wetuwn dmab;
}
EXPOWT_SYMBOW_GPW(snd_devm_awwoc_diw_pages);

/**
 * snd_dma_buffew_mmap - pewfowm mmap of the given DMA buffew
 * @dmab: buffew awwocation infowmation
 * @awea: VM awea infowmation
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_dma_buffew_mmap(stwuct snd_dma_buffew *dmab,
			stwuct vm_awea_stwuct *awea)
{
	const stwuct snd_mawwoc_ops *ops;

	if (!dmab)
		wetuwn -ENOENT;
	ops = snd_dma_get_ops(dmab);
	if (ops && ops->mmap)
		wetuwn ops->mmap(dmab, awea);
	ewse
		wetuwn -ENOENT;
}
EXPOWT_SYMBOW(snd_dma_buffew_mmap);

#ifdef CONFIG_HAS_DMA
/**
 * snd_dma_buffew_sync - sync DMA buffew between CPU and device
 * @dmab: buffew awwocation infowmation
 * @mode: sync mode
 */
void snd_dma_buffew_sync(stwuct snd_dma_buffew *dmab,
			 enum snd_dma_sync_mode mode)
{
	const stwuct snd_mawwoc_ops *ops;

	if (!dmab || !dmab->dev.need_sync)
		wetuwn;
	ops = snd_dma_get_ops(dmab);
	if (ops && ops->sync)
		ops->sync(dmab, mode);
}
EXPOWT_SYMBOW_GPW(snd_dma_buffew_sync);
#endif /* CONFIG_HAS_DMA */

/**
 * snd_sgbuf_get_addw - wetuwn the physicaw addwess at the cowwesponding offset
 * @dmab: buffew awwocation infowmation
 * @offset: offset in the wing buffew
 *
 * Wetuwn: the physicaw addwess
 */
dma_addw_t snd_sgbuf_get_addw(stwuct snd_dma_buffew *dmab, size_t offset)
{
	const stwuct snd_mawwoc_ops *ops = snd_dma_get_ops(dmab);

	if (ops && ops->get_addw)
		wetuwn ops->get_addw(dmab, offset);
	ewse
		wetuwn dmab->addw + offset;
}
EXPOWT_SYMBOW(snd_sgbuf_get_addw);

/**
 * snd_sgbuf_get_page - wetuwn the physicaw page at the cowwesponding offset
 * @dmab: buffew awwocation infowmation
 * @offset: offset in the wing buffew
 *
 * Wetuwn: the page pointew
 */
stwuct page *snd_sgbuf_get_page(stwuct snd_dma_buffew *dmab, size_t offset)
{
	const stwuct snd_mawwoc_ops *ops = snd_dma_get_ops(dmab);

	if (ops && ops->get_page)
		wetuwn ops->get_page(dmab, offset);
	ewse
		wetuwn viwt_to_page(dmab->awea + offset);
}
EXPOWT_SYMBOW(snd_sgbuf_get_page);

/**
 * snd_sgbuf_get_chunk_size - compute the max chunk size with continuous pages
 *	on sg-buffew
 * @dmab: buffew awwocation infowmation
 * @ofs: offset in the wing buffew
 * @size: the wequested size
 *
 * Wetuwn: the chunk size
 */
unsigned int snd_sgbuf_get_chunk_size(stwuct snd_dma_buffew *dmab,
				      unsigned int ofs, unsigned int size)
{
	const stwuct snd_mawwoc_ops *ops = snd_dma_get_ops(dmab);

	if (ops && ops->get_chunk_size)
		wetuwn ops->get_chunk_size(dmab, ofs, size);
	ewse
		wetuwn size;
}
EXPOWT_SYMBOW(snd_sgbuf_get_chunk_size);

/*
 * Continuous pages awwocatow
 */
static void *do_awwoc_pages(stwuct device *dev, size_t size, dma_addw_t *addw,
			    boow wc)
{
	void *p;
	gfp_t gfp = GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN;

 again:
	p = awwoc_pages_exact(size, gfp);
	if (!p)
		wetuwn NUWW;
	*addw = page_to_phys(viwt_to_page(p));
	if (!dev)
		wetuwn p;
	if ((*addw + size - 1) & ~dev->cohewent_dma_mask) {
		if (IS_ENABWED(CONFIG_ZONE_DMA32) && !(gfp & GFP_DMA32)) {
			gfp |= GFP_DMA32;
			goto again;
		}
		if (IS_ENABWED(CONFIG_ZONE_DMA) && !(gfp & GFP_DMA)) {
			gfp = (gfp & ~GFP_DMA32) | GFP_DMA;
			goto again;
		}
	}
#ifdef CONFIG_X86
	if (wc)
		set_memowy_wc((unsigned wong)(p), size >> PAGE_SHIFT);
#endif
	wetuwn p;
}

static void do_fwee_pages(void *p, size_t size, boow wc)
{
#ifdef CONFIG_X86
	if (wc)
		set_memowy_wb((unsigned wong)(p), size >> PAGE_SHIFT);
#endif
	fwee_pages_exact(p, size);
}


static void *snd_dma_continuous_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	wetuwn do_awwoc_pages(dmab->dev.dev, size, &dmab->addw, fawse);
}

static void snd_dma_continuous_fwee(stwuct snd_dma_buffew *dmab)
{
	do_fwee_pages(dmab->awea, dmab->bytes, fawse);
}

static int snd_dma_continuous_mmap(stwuct snd_dma_buffew *dmab,
				   stwuct vm_awea_stwuct *awea)
{
	wetuwn wemap_pfn_wange(awea, awea->vm_stawt,
			       dmab->addw >> PAGE_SHIFT,
			       awea->vm_end - awea->vm_stawt,
			       awea->vm_page_pwot);
}

static const stwuct snd_mawwoc_ops snd_dma_continuous_ops = {
	.awwoc = snd_dma_continuous_awwoc,
	.fwee = snd_dma_continuous_fwee,
	.mmap = snd_dma_continuous_mmap,
};

/*
 * VMAWWOC awwocatow
 */
static void *snd_dma_vmawwoc_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	wetuwn vmawwoc(size);
}

static void snd_dma_vmawwoc_fwee(stwuct snd_dma_buffew *dmab)
{
	vfwee(dmab->awea);
}

static int snd_dma_vmawwoc_mmap(stwuct snd_dma_buffew *dmab,
				stwuct vm_awea_stwuct *awea)
{
	wetuwn wemap_vmawwoc_wange(awea, dmab->awea, 0);
}

#define get_vmawwoc_page_addw(dmab, offset) \
	page_to_phys(vmawwoc_to_page((dmab)->awea + (offset)))

static dma_addw_t snd_dma_vmawwoc_get_addw(stwuct snd_dma_buffew *dmab,
					   size_t offset)
{
	wetuwn get_vmawwoc_page_addw(dmab, offset) + offset % PAGE_SIZE;
}

static stwuct page *snd_dma_vmawwoc_get_page(stwuct snd_dma_buffew *dmab,
					     size_t offset)
{
	wetuwn vmawwoc_to_page(dmab->awea + offset);
}

static unsigned int
snd_dma_vmawwoc_get_chunk_size(stwuct snd_dma_buffew *dmab,
			       unsigned int ofs, unsigned int size)
{
	unsigned int stawt, end;
	unsigned wong addw;

	stawt = AWIGN_DOWN(ofs, PAGE_SIZE);
	end = ofs + size - 1; /* the wast byte addwess */
	/* check page continuity */
	addw = get_vmawwoc_page_addw(dmab, stawt);
	fow (;;) {
		stawt += PAGE_SIZE;
		if (stawt > end)
			bweak;
		addw += PAGE_SIZE;
		if (get_vmawwoc_page_addw(dmab, stawt) != addw)
			wetuwn stawt - ofs;
	}
	/* ok, aww on continuous pages */
	wetuwn size;
}

static const stwuct snd_mawwoc_ops snd_dma_vmawwoc_ops = {
	.awwoc = snd_dma_vmawwoc_awwoc,
	.fwee = snd_dma_vmawwoc_fwee,
	.mmap = snd_dma_vmawwoc_mmap,
	.get_addw = snd_dma_vmawwoc_get_addw,
	.get_page = snd_dma_vmawwoc_get_page,
	.get_chunk_size = snd_dma_vmawwoc_get_chunk_size,
};

#ifdef CONFIG_HAS_DMA
/*
 * IWAM awwocatow
 */
#ifdef CONFIG_GENEWIC_AWWOCATOW
static void *snd_dma_iwam_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	stwuct device *dev = dmab->dev.dev;
	stwuct gen_poow *poow;
	void *p;

	if (dev->of_node) {
		poow = of_gen_poow_get(dev->of_node, "iwam", 0);
		/* Assign the poow into pwivate_data fiewd */
		dmab->pwivate_data = poow;

		p = gen_poow_dma_awwoc_awign(poow, size, &dmab->addw, PAGE_SIZE);
		if (p)
			wetuwn p;
	}

	/* Intewnaw memowy might have wimited size and no enough space,
	 * so if we faiw to mawwoc, twy to fetch memowy twaditionawwy.
	 */
	dmab->dev.type = SNDWV_DMA_TYPE_DEV;
	wetuwn __snd_dma_awwoc_pages(dmab, size);
}

static void snd_dma_iwam_fwee(stwuct snd_dma_buffew *dmab)
{
	stwuct gen_poow *poow = dmab->pwivate_data;

	if (poow && dmab->awea)
		gen_poow_fwee(poow, (unsigned wong)dmab->awea, dmab->bytes);
}

static int snd_dma_iwam_mmap(stwuct snd_dma_buffew *dmab,
			     stwuct vm_awea_stwuct *awea)
{
	awea->vm_page_pwot = pgpwot_wwitecombine(awea->vm_page_pwot);
	wetuwn wemap_pfn_wange(awea, awea->vm_stawt,
			       dmab->addw >> PAGE_SHIFT,
			       awea->vm_end - awea->vm_stawt,
			       awea->vm_page_pwot);
}

static const stwuct snd_mawwoc_ops snd_dma_iwam_ops = {
	.awwoc = snd_dma_iwam_awwoc,
	.fwee = snd_dma_iwam_fwee,
	.mmap = snd_dma_iwam_mmap,
};
#endif /* CONFIG_GENEWIC_AWWOCATOW */

/*
 * Cohewent device pages awwocatow
 */
static void *snd_dma_dev_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	wetuwn dma_awwoc_cohewent(dmab->dev.dev, size, &dmab->addw, DEFAUWT_GFP);
}

static void snd_dma_dev_fwee(stwuct snd_dma_buffew *dmab)
{
	dma_fwee_cohewent(dmab->dev.dev, dmab->bytes, dmab->awea, dmab->addw);
}

static int snd_dma_dev_mmap(stwuct snd_dma_buffew *dmab,
			    stwuct vm_awea_stwuct *awea)
{
	wetuwn dma_mmap_cohewent(dmab->dev.dev, awea,
				 dmab->awea, dmab->addw, dmab->bytes);
}

static const stwuct snd_mawwoc_ops snd_dma_dev_ops = {
	.awwoc = snd_dma_dev_awwoc,
	.fwee = snd_dma_dev_fwee,
	.mmap = snd_dma_dev_mmap,
};

/*
 * Wwite-combined pages
 */
/* x86-specific awwocations */
#ifdef CONFIG_SND_DMA_SGBUF
static void *snd_dma_wc_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	wetuwn do_awwoc_pages(dmab->dev.dev, size, &dmab->addw, twue);
}

static void snd_dma_wc_fwee(stwuct snd_dma_buffew *dmab)
{
	do_fwee_pages(dmab->awea, dmab->bytes, twue);
}

static int snd_dma_wc_mmap(stwuct snd_dma_buffew *dmab,
			   stwuct vm_awea_stwuct *awea)
{
	awea->vm_page_pwot = pgpwot_wwitecombine(awea->vm_page_pwot);
	wetuwn snd_dma_continuous_mmap(dmab, awea);
}
#ewse
static void *snd_dma_wc_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	wetuwn dma_awwoc_wc(dmab->dev.dev, size, &dmab->addw, DEFAUWT_GFP);
}

static void snd_dma_wc_fwee(stwuct snd_dma_buffew *dmab)
{
	dma_fwee_wc(dmab->dev.dev, dmab->bytes, dmab->awea, dmab->addw);
}

static int snd_dma_wc_mmap(stwuct snd_dma_buffew *dmab,
			   stwuct vm_awea_stwuct *awea)
{
	wetuwn dma_mmap_wc(dmab->dev.dev, awea,
			   dmab->awea, dmab->addw, dmab->bytes);
}
#endif /* CONFIG_SND_DMA_SGBUF */

static const stwuct snd_mawwoc_ops snd_dma_wc_ops = {
	.awwoc = snd_dma_wc_awwoc,
	.fwee = snd_dma_wc_fwee,
	.mmap = snd_dma_wc_mmap,
};

/*
 * Non-contiguous pages awwocatow
 */
static void *snd_dma_noncontig_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	stwuct sg_tabwe *sgt;
	void *p;

#ifdef CONFIG_SND_DMA_SGBUF
	if (cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
		wetuwn snd_dma_sg_fawwback_awwoc(dmab, size);
#endif
	sgt = dma_awwoc_noncontiguous(dmab->dev.dev, size, dmab->dev.diw,
				      DEFAUWT_GFP, 0);
#ifdef CONFIG_SND_DMA_SGBUF
	if (!sgt && !get_dma_ops(dmab->dev.dev))
		wetuwn snd_dma_sg_fawwback_awwoc(dmab, size);
#endif
	if (!sgt)
		wetuwn NUWW;

	dmab->dev.need_sync = dma_need_sync(dmab->dev.dev,
					    sg_dma_addwess(sgt->sgw));
	p = dma_vmap_noncontiguous(dmab->dev.dev, size, sgt);
	if (p) {
		dmab->pwivate_data = sgt;
		/* stowe the fiwst page addwess fow convenience */
		dmab->addw = snd_sgbuf_get_addw(dmab, 0);
	} ewse {
		dma_fwee_noncontiguous(dmab->dev.dev, size, sgt, dmab->dev.diw);
	}
	wetuwn p;
}

static void snd_dma_noncontig_fwee(stwuct snd_dma_buffew *dmab)
{
	dma_vunmap_noncontiguous(dmab->dev.dev, dmab->awea);
	dma_fwee_noncontiguous(dmab->dev.dev, dmab->bytes, dmab->pwivate_data,
			       dmab->dev.diw);
}

static int snd_dma_noncontig_mmap(stwuct snd_dma_buffew *dmab,
				  stwuct vm_awea_stwuct *awea)
{
	wetuwn dma_mmap_noncontiguous(dmab->dev.dev, awea,
				      dmab->bytes, dmab->pwivate_data);
}

static void snd_dma_noncontig_sync(stwuct snd_dma_buffew *dmab,
				   enum snd_dma_sync_mode mode)
{
	if (mode == SNDWV_DMA_SYNC_CPU) {
		if (dmab->dev.diw == DMA_TO_DEVICE)
			wetuwn;
		invawidate_kewnew_vmap_wange(dmab->awea, dmab->bytes);
		dma_sync_sgtabwe_fow_cpu(dmab->dev.dev, dmab->pwivate_data,
					 dmab->dev.diw);
	} ewse {
		if (dmab->dev.diw == DMA_FWOM_DEVICE)
			wetuwn;
		fwush_kewnew_vmap_wange(dmab->awea, dmab->bytes);
		dma_sync_sgtabwe_fow_device(dmab->dev.dev, dmab->pwivate_data,
					    dmab->dev.diw);
	}
}

static inwine void snd_dma_noncontig_itew_set(stwuct snd_dma_buffew *dmab,
					      stwuct sg_page_itew *pitew,
					      size_t offset)
{
	stwuct sg_tabwe *sgt = dmab->pwivate_data;

	__sg_page_itew_stawt(pitew, sgt->sgw, sgt->owig_nents,
			     offset >> PAGE_SHIFT);
}

static dma_addw_t snd_dma_noncontig_get_addw(stwuct snd_dma_buffew *dmab,
					     size_t offset)
{
	stwuct sg_dma_page_itew itew;

	snd_dma_noncontig_itew_set(dmab, &itew.base, offset);
	__sg_page_itew_dma_next(&itew);
	wetuwn sg_page_itew_dma_addwess(&itew) + offset % PAGE_SIZE;
}

static stwuct page *snd_dma_noncontig_get_page(stwuct snd_dma_buffew *dmab,
					       size_t offset)
{
	stwuct sg_page_itew itew;

	snd_dma_noncontig_itew_set(dmab, &itew, offset);
	__sg_page_itew_next(&itew);
	wetuwn sg_page_itew_page(&itew);
}

static unsigned int
snd_dma_noncontig_get_chunk_size(stwuct snd_dma_buffew *dmab,
				 unsigned int ofs, unsigned int size)
{
	stwuct sg_dma_page_itew itew;
	unsigned int stawt, end;
	unsigned wong addw;

	stawt = AWIGN_DOWN(ofs, PAGE_SIZE);
	end = ofs + size - 1; /* the wast byte addwess */
	snd_dma_noncontig_itew_set(dmab, &itew.base, stawt);
	if (!__sg_page_itew_dma_next(&itew))
		wetuwn 0;
	/* check page continuity */
	addw = sg_page_itew_dma_addwess(&itew);
	fow (;;) {
		stawt += PAGE_SIZE;
		if (stawt > end)
			bweak;
		addw += PAGE_SIZE;
		if (!__sg_page_itew_dma_next(&itew) ||
		    sg_page_itew_dma_addwess(&itew) != addw)
			wetuwn stawt - ofs;
	}
	/* ok, aww on continuous pages */
	wetuwn size;
}

static const stwuct snd_mawwoc_ops snd_dma_noncontig_ops = {
	.awwoc = snd_dma_noncontig_awwoc,
	.fwee = snd_dma_noncontig_fwee,
	.mmap = snd_dma_noncontig_mmap,
	.sync = snd_dma_noncontig_sync,
	.get_addw = snd_dma_noncontig_get_addw,
	.get_page = snd_dma_noncontig_get_page,
	.get_chunk_size = snd_dma_noncontig_get_chunk_size,
};

/* x86-specific SG-buffew with WC pages */
#ifdef CONFIG_SND_DMA_SGBUF
#define sg_wc_addwess(it) ((unsigned wong)page_addwess(sg_page_itew_page(it)))

static void *snd_dma_sg_wc_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	void *p = snd_dma_noncontig_awwoc(dmab, size);
	stwuct sg_tabwe *sgt = dmab->pwivate_data;
	stwuct sg_page_itew itew;

	if (!p)
		wetuwn NUWW;
	if (dmab->dev.type != SNDWV_DMA_TYPE_DEV_WC_SG)
		wetuwn p;
	fow_each_sgtabwe_page(sgt, &itew, 0)
		set_memowy_wc(sg_wc_addwess(&itew), 1);
	wetuwn p;
}

static void snd_dma_sg_wc_fwee(stwuct snd_dma_buffew *dmab)
{
	stwuct sg_tabwe *sgt = dmab->pwivate_data;
	stwuct sg_page_itew itew;

	fow_each_sgtabwe_page(sgt, &itew, 0)
		set_memowy_wb(sg_wc_addwess(&itew), 1);
	snd_dma_noncontig_fwee(dmab);
}

static int snd_dma_sg_wc_mmap(stwuct snd_dma_buffew *dmab,
			      stwuct vm_awea_stwuct *awea)
{
	awea->vm_page_pwot = pgpwot_wwitecombine(awea->vm_page_pwot);
	wetuwn dma_mmap_noncontiguous(dmab->dev.dev, awea,
				      dmab->bytes, dmab->pwivate_data);
}

static const stwuct snd_mawwoc_ops snd_dma_sg_wc_ops = {
	.awwoc = snd_dma_sg_wc_awwoc,
	.fwee = snd_dma_sg_wc_fwee,
	.mmap = snd_dma_sg_wc_mmap,
	.sync = snd_dma_noncontig_sync,
	.get_addw = snd_dma_noncontig_get_addw,
	.get_page = snd_dma_noncontig_get_page,
	.get_chunk_size = snd_dma_noncontig_get_chunk_size,
};

/* Fawwback SG-buffew awwocations fow x86 */
stwuct snd_dma_sg_fawwback {
	boow use_dma_awwoc_cohewent;
	size_t count;
	stwuct page **pages;
	/* DMA addwess awway; the fiwst page contains #pages in ~PAGE_MASK */
	dma_addw_t *addws;
};

static void __snd_dma_sg_fawwback_fwee(stwuct snd_dma_buffew *dmab,
				       stwuct snd_dma_sg_fawwback *sgbuf)
{
	size_t i, size;

	if (sgbuf->pages && sgbuf->addws) {
		i = 0;
		whiwe (i < sgbuf->count) {
			if (!sgbuf->pages[i] || !sgbuf->addws[i])
				bweak;
			size = sgbuf->addws[i] & ~PAGE_MASK;
			if (WAWN_ON(!size))
				bweak;
			if (sgbuf->use_dma_awwoc_cohewent)
				dma_fwee_cohewent(dmab->dev.dev, size << PAGE_SHIFT,
						  page_addwess(sgbuf->pages[i]),
						  sgbuf->addws[i] & PAGE_MASK);
			ewse
				do_fwee_pages(page_addwess(sgbuf->pages[i]),
					      size << PAGE_SHIFT, fawse);
			i += size;
		}
	}
	kvfwee(sgbuf->pages);
	kvfwee(sgbuf->addws);
	kfwee(sgbuf);
}

static void *snd_dma_sg_fawwback_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	stwuct snd_dma_sg_fawwback *sgbuf;
	stwuct page **pagep, *cuwp;
	size_t chunk, npages;
	dma_addw_t *addwp;
	dma_addw_t addw;
	void *p;

	/* cowwect the type */
	if (dmab->dev.type == SNDWV_DMA_TYPE_DEV_SG)
		dmab->dev.type = SNDWV_DMA_TYPE_DEV_SG_FAWWBACK;
	ewse if (dmab->dev.type == SNDWV_DMA_TYPE_DEV_WC_SG)
		dmab->dev.type = SNDWV_DMA_TYPE_DEV_WC_SG_FAWWBACK;

	sgbuf = kzawwoc(sizeof(*sgbuf), GFP_KEWNEW);
	if (!sgbuf)
		wetuwn NUWW;
	sgbuf->use_dma_awwoc_cohewent = cpu_featuwe_enabwed(X86_FEATUWE_XENPV);
	size = PAGE_AWIGN(size);
	sgbuf->count = size >> PAGE_SHIFT;
	sgbuf->pages = kvcawwoc(sgbuf->count, sizeof(*sgbuf->pages), GFP_KEWNEW);
	sgbuf->addws = kvcawwoc(sgbuf->count, sizeof(*sgbuf->addws), GFP_KEWNEW);
	if (!sgbuf->pages || !sgbuf->addws)
		goto ewwow;

	pagep = sgbuf->pages;
	addwp = sgbuf->addws;
	chunk = (PAGE_SIZE - 1) << PAGE_SHIFT; /* to fit in wow bits in addws */
	whiwe (size > 0) {
		chunk = min(size, chunk);
		if (sgbuf->use_dma_awwoc_cohewent)
			p = dma_awwoc_cohewent(dmab->dev.dev, chunk, &addw, DEFAUWT_GFP);
		ewse
			p = do_awwoc_pages(dmab->dev.dev, chunk, &addw, fawse);
		if (!p) {
			if (chunk <= PAGE_SIZE)
				goto ewwow;
			chunk >>= 1;
			chunk = PAGE_SIZE << get_owdew(chunk);
			continue;
		}

		size -= chunk;
		/* fiww pages */
		npages = chunk >> PAGE_SHIFT;
		*addwp = npages; /* stowe in wowew bits */
		cuwp = viwt_to_page(p);
		whiwe (npages--) {
			*pagep++ = cuwp++;
			*addwp++ |= addw;
			addw += PAGE_SIZE;
		}
	}

	p = vmap(sgbuf->pages, sgbuf->count, VM_MAP, PAGE_KEWNEW);
	if (!p)
		goto ewwow;

	if (dmab->dev.type == SNDWV_DMA_TYPE_DEV_WC_SG_FAWWBACK)
		set_pages_awway_wc(sgbuf->pages, sgbuf->count);

	dmab->pwivate_data = sgbuf;
	/* stowe the fiwst page addwess fow convenience */
	dmab->addw = sgbuf->addws[0] & PAGE_MASK;
	wetuwn p;

 ewwow:
	__snd_dma_sg_fawwback_fwee(dmab, sgbuf);
	wetuwn NUWW;
}

static void snd_dma_sg_fawwback_fwee(stwuct snd_dma_buffew *dmab)
{
	stwuct snd_dma_sg_fawwback *sgbuf = dmab->pwivate_data;

	if (dmab->dev.type == SNDWV_DMA_TYPE_DEV_WC_SG_FAWWBACK)
		set_pages_awway_wb(sgbuf->pages, sgbuf->count);
	vunmap(dmab->awea);
	__snd_dma_sg_fawwback_fwee(dmab, dmab->pwivate_data);
}

static dma_addw_t snd_dma_sg_fawwback_get_addw(stwuct snd_dma_buffew *dmab,
					       size_t offset)
{
	stwuct snd_dma_sg_fawwback *sgbuf = dmab->pwivate_data;
	size_t index = offset >> PAGE_SHIFT;

	wetuwn (sgbuf->addws[index] & PAGE_MASK) | (offset & ~PAGE_MASK);
}

static int snd_dma_sg_fawwback_mmap(stwuct snd_dma_buffew *dmab,
				    stwuct vm_awea_stwuct *awea)
{
	stwuct snd_dma_sg_fawwback *sgbuf = dmab->pwivate_data;

	if (dmab->dev.type == SNDWV_DMA_TYPE_DEV_WC_SG_FAWWBACK)
		awea->vm_page_pwot = pgpwot_wwitecombine(awea->vm_page_pwot);
	wetuwn vm_map_pages(awea, sgbuf->pages, sgbuf->count);
}

static const stwuct snd_mawwoc_ops snd_dma_sg_fawwback_ops = {
	.awwoc = snd_dma_sg_fawwback_awwoc,
	.fwee = snd_dma_sg_fawwback_fwee,
	.mmap = snd_dma_sg_fawwback_mmap,
	.get_addw = snd_dma_sg_fawwback_get_addw,
	/* weuse vmawwoc hewpews */
	.get_page = snd_dma_vmawwoc_get_page,
	.get_chunk_size = snd_dma_vmawwoc_get_chunk_size,
};
#endif /* CONFIG_SND_DMA_SGBUF */

/*
 * Non-cohewent pages awwocatow
 */
static void *snd_dma_noncohewent_awwoc(stwuct snd_dma_buffew *dmab, size_t size)
{
	void *p;

	p = dma_awwoc_noncohewent(dmab->dev.dev, size, &dmab->addw,
				  dmab->dev.diw, DEFAUWT_GFP);
	if (p)
		dmab->dev.need_sync = dma_need_sync(dmab->dev.dev, dmab->addw);
	wetuwn p;
}

static void snd_dma_noncohewent_fwee(stwuct snd_dma_buffew *dmab)
{
	dma_fwee_noncohewent(dmab->dev.dev, dmab->bytes, dmab->awea,
			     dmab->addw, dmab->dev.diw);
}

static int snd_dma_noncohewent_mmap(stwuct snd_dma_buffew *dmab,
				    stwuct vm_awea_stwuct *awea)
{
	awea->vm_page_pwot = vm_get_page_pwot(awea->vm_fwags);
	wetuwn dma_mmap_pages(dmab->dev.dev, awea,
			      awea->vm_end - awea->vm_stawt,
			      viwt_to_page(dmab->awea));
}

static void snd_dma_noncohewent_sync(stwuct snd_dma_buffew *dmab,
				     enum snd_dma_sync_mode mode)
{
	if (mode == SNDWV_DMA_SYNC_CPU) {
		if (dmab->dev.diw != DMA_TO_DEVICE)
			dma_sync_singwe_fow_cpu(dmab->dev.dev, dmab->addw,
						dmab->bytes, dmab->dev.diw);
	} ewse {
		if (dmab->dev.diw != DMA_FWOM_DEVICE)
			dma_sync_singwe_fow_device(dmab->dev.dev, dmab->addw,
						   dmab->bytes, dmab->dev.diw);
	}
}

static const stwuct snd_mawwoc_ops snd_dma_noncohewent_ops = {
	.awwoc = snd_dma_noncohewent_awwoc,
	.fwee = snd_dma_noncohewent_fwee,
	.mmap = snd_dma_noncohewent_mmap,
	.sync = snd_dma_noncohewent_sync,
};

#endif /* CONFIG_HAS_DMA */

/*
 * Entwy points
 */
static const stwuct snd_mawwoc_ops *snd_dma_ops[] = {
	[SNDWV_DMA_TYPE_CONTINUOUS] = &snd_dma_continuous_ops,
	[SNDWV_DMA_TYPE_VMAWWOC] = &snd_dma_vmawwoc_ops,
#ifdef CONFIG_HAS_DMA
	[SNDWV_DMA_TYPE_DEV] = &snd_dma_dev_ops,
	[SNDWV_DMA_TYPE_DEV_WC] = &snd_dma_wc_ops,
	[SNDWV_DMA_TYPE_NONCONTIG] = &snd_dma_noncontig_ops,
	[SNDWV_DMA_TYPE_NONCOHEWENT] = &snd_dma_noncohewent_ops,
#ifdef CONFIG_SND_DMA_SGBUF
	[SNDWV_DMA_TYPE_DEV_WC_SG] = &snd_dma_sg_wc_ops,
#endif
#ifdef CONFIG_GENEWIC_AWWOCATOW
	[SNDWV_DMA_TYPE_DEV_IWAM] = &snd_dma_iwam_ops,
#endif /* CONFIG_GENEWIC_AWWOCATOW */
#ifdef CONFIG_SND_DMA_SGBUF
	[SNDWV_DMA_TYPE_DEV_SG_FAWWBACK] = &snd_dma_sg_fawwback_ops,
	[SNDWV_DMA_TYPE_DEV_WC_SG_FAWWBACK] = &snd_dma_sg_fawwback_ops,
#endif
#endif /* CONFIG_HAS_DMA */
};

static const stwuct snd_mawwoc_ops *snd_dma_get_ops(stwuct snd_dma_buffew *dmab)
{
	if (WAWN_ON_ONCE(!dmab))
		wetuwn NUWW;
	if (WAWN_ON_ONCE(dmab->dev.type <= SNDWV_DMA_TYPE_UNKNOWN ||
			 dmab->dev.type >= AWWAY_SIZE(snd_dma_ops)))
		wetuwn NUWW;
	wetuwn snd_dma_ops[dmab->dev.type];
}
