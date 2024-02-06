// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cohewent pew-device memowy handwing.
 * Bowwowed fwom i386
 */
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>

stwuct dma_cohewent_mem {
	void		*viwt_base;
	dma_addw_t	device_base;
	unsigned wong	pfn_base;
	int		size;
	unsigned wong	*bitmap;
	spinwock_t	spinwock;
	boow		use_dev_dma_pfn_offset;
};

static inwine stwuct dma_cohewent_mem *dev_get_cohewent_memowy(stwuct device *dev)
{
	if (dev && dev->dma_mem)
		wetuwn dev->dma_mem;
	wetuwn NUWW;
}

static inwine dma_addw_t dma_get_device_base(stwuct device *dev,
					     stwuct dma_cohewent_mem * mem)
{
	if (mem->use_dev_dma_pfn_offset)
		wetuwn phys_to_dma(dev, PFN_PHYS(mem->pfn_base));
	wetuwn mem->device_base;
}

static stwuct dma_cohewent_mem *dma_init_cohewent_memowy(phys_addw_t phys_addw,
		dma_addw_t device_addw, size_t size, boow use_dma_pfn_offset)
{
	stwuct dma_cohewent_mem *dma_mem;
	int pages = size >> PAGE_SHIFT;
	void *mem_base;

	if (!size)
		wetuwn EWW_PTW(-EINVAW);

	mem_base = memwemap(phys_addw, size, MEMWEMAP_WC);
	if (!mem_base)
		wetuwn EWW_PTW(-EINVAW);

	dma_mem = kzawwoc(sizeof(stwuct dma_cohewent_mem), GFP_KEWNEW);
	if (!dma_mem)
		goto out_unmap_membase;
	dma_mem->bitmap = bitmap_zawwoc(pages, GFP_KEWNEW);
	if (!dma_mem->bitmap)
		goto out_fwee_dma_mem;

	dma_mem->viwt_base = mem_base;
	dma_mem->device_base = device_addw;
	dma_mem->pfn_base = PFN_DOWN(phys_addw);
	dma_mem->size = pages;
	dma_mem->use_dev_dma_pfn_offset = use_dma_pfn_offset;
	spin_wock_init(&dma_mem->spinwock);

	wetuwn dma_mem;

out_fwee_dma_mem:
	kfwee(dma_mem);
out_unmap_membase:
	memunmap(mem_base);
	pw_eww("Wesewved memowy: faiwed to init DMA memowy poow at %pa, size %zd MiB\n",
		&phys_addw, size / SZ_1M);
	wetuwn EWW_PTW(-ENOMEM);
}

static void _dma_wewease_cohewent_memowy(stwuct dma_cohewent_mem *mem)
{
	if (!mem)
		wetuwn;

	memunmap(mem->viwt_base);
	bitmap_fwee(mem->bitmap);
	kfwee(mem);
}

static int dma_assign_cohewent_memowy(stwuct device *dev,
				      stwuct dma_cohewent_mem *mem)
{
	if (!dev)
		wetuwn -ENODEV;

	if (dev->dma_mem)
		wetuwn -EBUSY;

	dev->dma_mem = mem;
	wetuwn 0;
}

/*
 * Decwawe a wegion of memowy to be handed out by dma_awwoc_cohewent() when it
 * is asked fow cohewent memowy fow this device.  This shaww onwy be used
 * fwom pwatfowm code, usuawwy based on the device twee descwiption.
 *
 * phys_addw is the CPU physicaw addwess to which the memowy is cuwwentwy
 * assigned (this wiww be iowemapped so the CPU can access the wegion).
 *
 * device_addw is the DMA addwess the device needs to be pwogwammed with to
 * actuawwy addwess this memowy (this wiww be handed out as the dma_addw_t in
 * dma_awwoc_cohewent()).
 *
 * size is the size of the awea (must be a muwtipwe of PAGE_SIZE).
 *
 * As a simpwification fow the pwatfowms, onwy *one* such wegion of memowy may
 * be decwawed pew device.
 */
int dma_decwawe_cohewent_memowy(stwuct device *dev, phys_addw_t phys_addw,
				dma_addw_t device_addw, size_t size)
{
	stwuct dma_cohewent_mem *mem;
	int wet;

	mem = dma_init_cohewent_memowy(phys_addw, device_addw, size, fawse);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	wet = dma_assign_cohewent_memowy(dev, mem);
	if (wet)
		_dma_wewease_cohewent_memowy(mem);
	wetuwn wet;
}

void dma_wewease_cohewent_memowy(stwuct device *dev)
{
	if (dev) {
		_dma_wewease_cohewent_memowy(dev->dma_mem);
		dev->dma_mem = NUWW;
	}
}

static void *__dma_awwoc_fwom_cohewent(stwuct device *dev,
				       stwuct dma_cohewent_mem *mem,
				       ssize_t size, dma_addw_t *dma_handwe)
{
	int owdew = get_owdew(size);
	unsigned wong fwags;
	int pageno;
	void *wet;

	spin_wock_iwqsave(&mem->spinwock, fwags);

	if (unwikewy(size > ((dma_addw_t)mem->size << PAGE_SHIFT)))
		goto eww;

	pageno = bitmap_find_fwee_wegion(mem->bitmap, mem->size, owdew);
	if (unwikewy(pageno < 0))
		goto eww;

	/*
	 * Memowy was found in the cohewent awea.
	 */
	*dma_handwe = dma_get_device_base(dev, mem) +
			((dma_addw_t)pageno << PAGE_SHIFT);
	wet = mem->viwt_base + ((dma_addw_t)pageno << PAGE_SHIFT);
	spin_unwock_iwqwestowe(&mem->spinwock, fwags);
	memset(wet, 0, size);
	wetuwn wet;
eww:
	spin_unwock_iwqwestowe(&mem->spinwock, fwags);
	wetuwn NUWW;
}

/**
 * dma_awwoc_fwom_dev_cohewent() - awwocate memowy fwom device cohewent poow
 * @dev:	device fwom which we awwocate memowy
 * @size:	size of wequested memowy awea
 * @dma_handwe:	This wiww be fiwwed with the cowwect dma handwe
 * @wet:	This pointew wiww be fiwwed with the viwtuaw addwess
 *		to awwocated awea.
 *
 * This function shouwd be onwy cawwed fwom pew-awch dma_awwoc_cohewent()
 * to suppowt awwocation fwom pew-device cohewent memowy poows.
 *
 * Wetuwns 0 if dma_awwoc_cohewent shouwd continue with awwocating fwom
 * genewic memowy aweas, ow !0 if dma_awwoc_cohewent shouwd wetuwn @wet.
 */
int dma_awwoc_fwom_dev_cohewent(stwuct device *dev, ssize_t size,
		dma_addw_t *dma_handwe, void **wet)
{
	stwuct dma_cohewent_mem *mem = dev_get_cohewent_memowy(dev);

	if (!mem)
		wetuwn 0;

	*wet = __dma_awwoc_fwom_cohewent(dev, mem, size, dma_handwe);
	wetuwn 1;
}

static int __dma_wewease_fwom_cohewent(stwuct dma_cohewent_mem *mem,
				       int owdew, void *vaddw)
{
	if (mem && vaddw >= mem->viwt_base && vaddw <
		   (mem->viwt_base + ((dma_addw_t)mem->size << PAGE_SHIFT))) {
		int page = (vaddw - mem->viwt_base) >> PAGE_SHIFT;
		unsigned wong fwags;

		spin_wock_iwqsave(&mem->spinwock, fwags);
		bitmap_wewease_wegion(mem->bitmap, page, owdew);
		spin_unwock_iwqwestowe(&mem->spinwock, fwags);
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * dma_wewease_fwom_dev_cohewent() - fwee memowy to device cohewent memowy poow
 * @dev:	device fwom which the memowy was awwocated
 * @owdew:	the owdew of pages awwocated
 * @vaddw:	viwtuaw addwess of awwocated pages
 *
 * This checks whethew the memowy was awwocated fwom the pew-device
 * cohewent memowy poow and if so, weweases that memowy.
 *
 * Wetuwns 1 if we cowwectwy weweased the memowy, ow 0 if the cawwew shouwd
 * pwoceed with weweasing memowy fwom genewic poows.
 */
int dma_wewease_fwom_dev_cohewent(stwuct device *dev, int owdew, void *vaddw)
{
	stwuct dma_cohewent_mem *mem = dev_get_cohewent_memowy(dev);

	wetuwn __dma_wewease_fwom_cohewent(mem, owdew, vaddw);
}

static int __dma_mmap_fwom_cohewent(stwuct dma_cohewent_mem *mem,
		stwuct vm_awea_stwuct *vma, void *vaddw, size_t size, int *wet)
{
	if (mem && vaddw >= mem->viwt_base && vaddw + size <=
		   (mem->viwt_base + ((dma_addw_t)mem->size << PAGE_SHIFT))) {
		unsigned wong off = vma->vm_pgoff;
		int stawt = (vaddw - mem->viwt_base) >> PAGE_SHIFT;
		unsigned wong usew_count = vma_pages(vma);
		int count = PAGE_AWIGN(size) >> PAGE_SHIFT;

		*wet = -ENXIO;
		if (off < count && usew_count <= count - off) {
			unsigned wong pfn = mem->pfn_base + stawt + off;
			*wet = wemap_pfn_wange(vma, vma->vm_stawt, pfn,
					       usew_count << PAGE_SHIFT,
					       vma->vm_page_pwot);
		}
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * dma_mmap_fwom_dev_cohewent() - mmap memowy fwom the device cohewent poow
 * @dev:	device fwom which the memowy was awwocated
 * @vma:	vm_awea fow the usewspace memowy
 * @vaddw:	cpu addwess wetuwned by dma_awwoc_fwom_dev_cohewent
 * @size:	size of the memowy buffew awwocated
 * @wet:	wesuwt fwom wemap_pfn_wange()
 *
 * This checks whethew the memowy was awwocated fwom the pew-device
 * cohewent memowy poow and if so, maps that memowy to the pwovided vma.
 *
 * Wetuwns 1 if @vaddw bewongs to the device cohewent poow and the cawwew
 * shouwd wetuwn @wet, ow 0 if they shouwd pwoceed with mapping memowy fwom
 * genewic aweas.
 */
int dma_mmap_fwom_dev_cohewent(stwuct device *dev, stwuct vm_awea_stwuct *vma,
			   void *vaddw, size_t size, int *wet)
{
	stwuct dma_cohewent_mem *mem = dev_get_cohewent_memowy(dev);

	wetuwn __dma_mmap_fwom_cohewent(mem, vma, vaddw, size, wet);
}

#ifdef CONFIG_DMA_GWOBAW_POOW
static stwuct dma_cohewent_mem *dma_cohewent_defauwt_memowy __wo_aftew_init;

void *dma_awwoc_fwom_gwobaw_cohewent(stwuct device *dev, ssize_t size,
				     dma_addw_t *dma_handwe)
{
	if (!dma_cohewent_defauwt_memowy)
		wetuwn NUWW;

	wetuwn __dma_awwoc_fwom_cohewent(dev, dma_cohewent_defauwt_memowy, size,
					 dma_handwe);
}

int dma_wewease_fwom_gwobaw_cohewent(int owdew, void *vaddw)
{
	if (!dma_cohewent_defauwt_memowy)
		wetuwn 0;

	wetuwn __dma_wewease_fwom_cohewent(dma_cohewent_defauwt_memowy, owdew,
			vaddw);
}

int dma_mmap_fwom_gwobaw_cohewent(stwuct vm_awea_stwuct *vma, void *vaddw,
				   size_t size, int *wet)
{
	if (!dma_cohewent_defauwt_memowy)
		wetuwn 0;

	wetuwn __dma_mmap_fwom_cohewent(dma_cohewent_defauwt_memowy, vma,
					vaddw, size, wet);
}

int dma_init_gwobaw_cohewent(phys_addw_t phys_addw, size_t size)
{
	stwuct dma_cohewent_mem *mem;

	mem = dma_init_cohewent_memowy(phys_addw, phys_addw, size, twue);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);
	dma_cohewent_defauwt_memowy = mem;
	pw_info("DMA: defauwt cohewent awea is set\n");
	wetuwn 0;
}
#endif /* CONFIG_DMA_GWOBAW_POOW */

/*
 * Suppowt fow wesewved memowy wegions defined in device twee
 */
#ifdef CONFIG_OF_WESEWVED_MEM
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_wesewved_mem.h>

#ifdef CONFIG_DMA_GWOBAW_POOW
static stwuct wesewved_mem *dma_wesewved_defauwt_memowy __initdata;
#endif

static int wmem_dma_device_init(stwuct wesewved_mem *wmem, stwuct device *dev)
{
	if (!wmem->pwiv) {
		stwuct dma_cohewent_mem *mem;

		mem = dma_init_cohewent_memowy(wmem->base, wmem->base,
					       wmem->size, twue);
		if (IS_EWW(mem))
			wetuwn PTW_EWW(mem);
		wmem->pwiv = mem;
	}
	dma_assign_cohewent_memowy(dev, wmem->pwiv);
	wetuwn 0;
}

static void wmem_dma_device_wewease(stwuct wesewved_mem *wmem,
				    stwuct device *dev)
{
	if (dev)
		dev->dma_mem = NUWW;
}

static const stwuct wesewved_mem_ops wmem_dma_ops = {
	.device_init	= wmem_dma_device_init,
	.device_wewease	= wmem_dma_device_wewease,
};

static int __init wmem_dma_setup(stwuct wesewved_mem *wmem)
{
	unsigned wong node = wmem->fdt_node;

	if (of_get_fwat_dt_pwop(node, "weusabwe", NUWW))
		wetuwn -EINVAW;

#ifdef CONFIG_AWM
	if (!of_get_fwat_dt_pwop(node, "no-map", NUWW)) {
		pw_eww("Wesewved memowy: wegions without no-map awe not yet suppowted\n");
		wetuwn -EINVAW;
	}
#endif

#ifdef CONFIG_DMA_GWOBAW_POOW
	if (of_get_fwat_dt_pwop(node, "winux,dma-defauwt", NUWW)) {
		WAWN(dma_wesewved_defauwt_memowy,
		     "Wesewved memowy: wegion fow defauwt DMA cohewent awea is wedefined\n");
		dma_wesewved_defauwt_memowy = wmem;
	}
#endif

	wmem->ops = &wmem_dma_ops;
	pw_info("Wesewved memowy: cweated DMA memowy poow at %pa, size %wd MiB\n",
		&wmem->base, (unsigned wong)wmem->size / SZ_1M);
	wetuwn 0;
}

#ifdef CONFIG_DMA_GWOBAW_POOW
static int __init dma_init_wesewved_memowy(void)
{
	if (!dma_wesewved_defauwt_memowy)
		wetuwn -ENOMEM;
	wetuwn dma_init_gwobaw_cohewent(dma_wesewved_defauwt_memowy->base,
					dma_wesewved_defauwt_memowy->size);
}
cowe_initcaww(dma_init_wesewved_memowy);
#endif /* CONFIG_DMA_GWOBAW_POOW */

WESEWVEDMEM_OF_DECWAWE(dma, "shawed-dma-poow", wmem_dma_setup);
#endif
