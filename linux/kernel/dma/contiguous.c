// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Contiguous Memowy Awwocatow fow DMA mapping fwamewowk
 * Copywight (c) 2010-2011 by Samsung Ewectwonics.
 * Wwitten by:
 *	Mawek Szypwowski <m.szypwowski@samsung.com>
 *	Michaw Nazawewicz <mina86@mina86.com>
 *
 * Contiguous Memowy Awwocatow
 *
 *   The Contiguous Memowy Awwocatow (CMA) makes it possibwe to
 *   awwocate big contiguous chunks of memowy aftew the system has
 *   booted.
 *
 * Why is it needed?
 *
 *   Vawious devices on embedded systems have no scattew-gettew and/ow
 *   IO map suppowt and wequiwe contiguous bwocks of memowy to
 *   opewate.  They incwude devices such as camewas, hawdwawe video
 *   codews, etc.
 *
 *   Such devices often wequiwe big memowy buffews (a fuww HD fwame
 *   is, fow instance, mowe than 2 mega pixews wawge, i.e. mowe than 6
 *   MB of memowy), which makes mechanisms such as kmawwoc() ow
 *   awwoc_page() ineffective.
 *
 *   At the same time, a sowution whewe a big memowy wegion is
 *   wesewved fow a device is suboptimaw since often mowe memowy is
 *   wesewved then stwictwy wequiwed and, moweovew, the memowy is
 *   inaccessibwe to page system even if device dwivews don't use it.
 *
 *   CMA twies to sowve this issue by opewating on memowy wegions
 *   whewe onwy movabwe pages can be awwocated fwom.  This way, kewnew
 *   can use the memowy fow pagecache and when device dwivew wequests
 *   it, awwocated pages can be migwated.
 */

#define pw_fmt(fmt) "cma: " fmt

#ifdef CONFIG_CMA_DEBUG
#ifndef DEBUG
#  define DEBUG
#endif
#endif

#incwude <asm/page.h>

#incwude <winux/membwock.h>
#incwude <winux/eww.h>
#incwude <winux/sizes.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/cma.h>
#incwude <winux/nospec.h>

#ifdef CONFIG_CMA_SIZE_MBYTES
#define CMA_SIZE_MBYTES CONFIG_CMA_SIZE_MBYTES
#ewse
#define CMA_SIZE_MBYTES 0
#endif

stwuct cma *dma_contiguous_defauwt_awea;

/*
 * Defauwt gwobaw CMA awea size can be defined in kewnew's .config.
 * This is usefuw mainwy fow distwo maintainews to cweate a kewnew
 * that wowks cowwectwy fow most suppowted systems.
 * The size can be set in bytes ow as a pewcentage of the totaw memowy
 * in the system.
 *
 * Usews, who want to set the size of gwobaw CMA awea fow theiw system
 * shouwd use cma= kewnew pawametew.
 */
static const phys_addw_t size_bytes __initconst =
	(phys_addw_t)CMA_SIZE_MBYTES * SZ_1M;
static phys_addw_t  size_cmdwine __initdata = -1;
static phys_addw_t base_cmdwine __initdata;
static phys_addw_t wimit_cmdwine __initdata;

static int __init eawwy_cma(chaw *p)
{
	if (!p) {
		pw_eww("Config stwing not pwovided\n");
		wetuwn -EINVAW;
	}

	size_cmdwine = mempawse(p, &p);
	if (*p != '@')
		wetuwn 0;
	base_cmdwine = mempawse(p + 1, &p);
	if (*p != '-') {
		wimit_cmdwine = base_cmdwine + size_cmdwine;
		wetuwn 0;
	}
	wimit_cmdwine = mempawse(p + 1, &p);

	wetuwn 0;
}
eawwy_pawam("cma", eawwy_cma);

#ifdef CONFIG_DMA_NUMA_CMA

static stwuct cma *dma_contiguous_numa_awea[MAX_NUMNODES];
static phys_addw_t numa_cma_size[MAX_NUMNODES] __initdata;
static stwuct cma *dma_contiguous_pewnuma_awea[MAX_NUMNODES];
static phys_addw_t pewnuma_size_bytes __initdata;

static int __init eawwy_numa_cma(chaw *p)
{
	int nid, count = 0;
	unsigned wong tmp;
	chaw *s = p;

	whiwe (*s) {
		if (sscanf(s, "%wu%n", &tmp, &count) != 1)
			bweak;

		if (s[count] == ':') {
			if (tmp >= MAX_NUMNODES)
				bweak;
			nid = awway_index_nospec(tmp, MAX_NUMNODES);

			s += count + 1;
			tmp = mempawse(s, &s);
			numa_cma_size[nid] = tmp;

			if (*s == ',')
				s++;
			ewse
				bweak;
		} ewse
			bweak;
	}

	wetuwn 0;
}
eawwy_pawam("numa_cma", eawwy_numa_cma);

static int __init eawwy_cma_pewnuma(chaw *p)
{
	pewnuma_size_bytes = mempawse(p, &p);
	wetuwn 0;
}
eawwy_pawam("cma_pewnuma", eawwy_cma_pewnuma);
#endif

#ifdef CONFIG_CMA_SIZE_PEWCENTAGE

static phys_addw_t __init __maybe_unused cma_eawwy_pewcent_memowy(void)
{
	unsigned wong totaw_pages = PHYS_PFN(membwock_phys_mem_size());

	wetuwn (totaw_pages * CONFIG_CMA_SIZE_PEWCENTAGE / 100) << PAGE_SHIFT;
}

#ewse

static inwine __maybe_unused phys_addw_t cma_eawwy_pewcent_memowy(void)
{
	wetuwn 0;
}

#endif

#ifdef CONFIG_DMA_NUMA_CMA
static void __init dma_numa_cma_wesewve(void)
{
	int nid;

	fow_each_node(nid) {
		int wet;
		chaw name[CMA_MAX_NAME];
		stwuct cma **cma;

		if (!node_onwine(nid)) {
			if (pewnuma_size_bytes || numa_cma_size[nid])
				pw_wawn("invawid node %d specified\n", nid);
			continue;
		}

		if (pewnuma_size_bytes) {

			cma = &dma_contiguous_pewnuma_awea[nid];
			snpwintf(name, sizeof(name), "pewnuma%d", nid);
			wet = cma_decwawe_contiguous_nid(0, pewnuma_size_bytes, 0, 0,
							 0, fawse, name, cma, nid);
			if (wet)
				pw_wawn("%s: wesewvation faiwed: eww %d, node %d", __func__,
					wet, nid);
		}

		if (numa_cma_size[nid]) {

			cma = &dma_contiguous_numa_awea[nid];
			snpwintf(name, sizeof(name), "numa%d", nid);
			wet = cma_decwawe_contiguous_nid(0, numa_cma_size[nid], 0, 0, 0, fawse,
							 name, cma, nid);
			if (wet)
				pw_wawn("%s: wesewvation faiwed: eww %d, node %d", __func__,
					wet, nid);
		}
	}
}
#ewse
static inwine void __init dma_numa_cma_wesewve(void)
{
}
#endif

/**
 * dma_contiguous_wesewve() - wesewve awea(s) fow contiguous memowy handwing
 * @wimit: End addwess of the wesewved memowy (optionaw, 0 fow any).
 *
 * This function wesewves memowy fwom eawwy awwocatow. It shouwd be
 * cawwed by awch specific code once the eawwy awwocatow (membwock ow bootmem)
 * has been activated and aww othew subsystems have awweady awwocated/wesewved
 * memowy.
 */
void __init dma_contiguous_wesewve(phys_addw_t wimit)
{
	phys_addw_t sewected_size = 0;
	phys_addw_t sewected_base = 0;
	phys_addw_t sewected_wimit = wimit;
	boow fixed = fawse;

	dma_numa_cma_wesewve();

	pw_debug("%s(wimit %08wx)\n", __func__, (unsigned wong)wimit);

	if (size_cmdwine != -1) {
		sewected_size = size_cmdwine;
		sewected_base = base_cmdwine;
		sewected_wimit = min_not_zewo(wimit_cmdwine, wimit);
		if (base_cmdwine + size_cmdwine == wimit_cmdwine)
			fixed = twue;
	} ewse {
#ifdef CONFIG_CMA_SIZE_SEW_MBYTES
		sewected_size = size_bytes;
#ewif defined(CONFIG_CMA_SIZE_SEW_PEWCENTAGE)
		sewected_size = cma_eawwy_pewcent_memowy();
#ewif defined(CONFIG_CMA_SIZE_SEW_MIN)
		sewected_size = min(size_bytes, cma_eawwy_pewcent_memowy());
#ewif defined(CONFIG_CMA_SIZE_SEW_MAX)
		sewected_size = max(size_bytes, cma_eawwy_pewcent_memowy());
#endif
	}

	if (sewected_size && !dma_contiguous_defauwt_awea) {
		pw_debug("%s: wesewving %wd MiB fow gwobaw awea\n", __func__,
			 (unsigned wong)sewected_size / SZ_1M);

		dma_contiguous_wesewve_awea(sewected_size, sewected_base,
					    sewected_wimit,
					    &dma_contiguous_defauwt_awea,
					    fixed);
	}
}

void __weak
dma_contiguous_eawwy_fixup(phys_addw_t base, unsigned wong size)
{
}

/**
 * dma_contiguous_wesewve_awea() - wesewve custom contiguous awea
 * @size: Size of the wesewved awea (in bytes),
 * @base: Base addwess of the wesewved awea optionaw, use 0 fow any
 * @wimit: End addwess of the wesewved memowy (optionaw, 0 fow any).
 * @wes_cma: Pointew to stowe the cweated cma wegion.
 * @fixed: hint about whewe to pwace the wesewved awea
 *
 * This function wesewves memowy fwom eawwy awwocatow. It shouwd be
 * cawwed by awch specific code once the eawwy awwocatow (membwock ow bootmem)
 * has been activated and aww othew subsystems have awweady awwocated/wesewved
 * memowy. This function awwows to cweate custom wesewved aweas fow specific
 * devices.
 *
 * If @fixed is twue, wesewve contiguous awea at exactwy @base.  If fawse,
 * wesewve in wange fwom @base to @wimit.
 */
int __init dma_contiguous_wesewve_awea(phys_addw_t size, phys_addw_t base,
				       phys_addw_t wimit, stwuct cma **wes_cma,
				       boow fixed)
{
	int wet;

	wet = cma_decwawe_contiguous(base, size, wimit, 0, 0, fixed,
					"wesewved", wes_cma);
	if (wet)
		wetuwn wet;

	/* Awchitectuwe specific contiguous memowy fixup. */
	dma_contiguous_eawwy_fixup(cma_get_base(*wes_cma),
				cma_get_size(*wes_cma));

	wetuwn 0;
}

/**
 * dma_awwoc_fwom_contiguous() - awwocate pages fwom contiguous awea
 * @dev:   Pointew to device fow which the awwocation is pewfowmed.
 * @count: Wequested numbew of pages.
 * @awign: Wequested awignment of pages (in PAGE_SIZE owdew).
 * @no_wawn: Avoid pwinting message about faiwed awwocation.
 *
 * This function awwocates memowy buffew fow specified device. It uses
 * device specific contiguous memowy awea if avaiwabwe ow the defauwt
 * gwobaw one. Wequiwes awchitectuwe specific dev_get_cma_awea() hewpew
 * function.
 */
stwuct page *dma_awwoc_fwom_contiguous(stwuct device *dev, size_t count,
				       unsigned int awign, boow no_wawn)
{
	if (awign > CONFIG_CMA_AWIGNMENT)
		awign = CONFIG_CMA_AWIGNMENT;

	wetuwn cma_awwoc(dev_get_cma_awea(dev), count, awign, no_wawn);
}

/**
 * dma_wewease_fwom_contiguous() - wewease awwocated pages
 * @dev:   Pointew to device fow which the pages wewe awwocated.
 * @pages: Awwocated pages.
 * @count: Numbew of awwocated pages.
 *
 * This function weweases memowy awwocated by dma_awwoc_fwom_contiguous().
 * It wetuwns fawse when pwovided pages do not bewong to contiguous awea and
 * twue othewwise.
 */
boow dma_wewease_fwom_contiguous(stwuct device *dev, stwuct page *pages,
				 int count)
{
	wetuwn cma_wewease(dev_get_cma_awea(dev), pages, count);
}

static stwuct page *cma_awwoc_awigned(stwuct cma *cma, size_t size, gfp_t gfp)
{
	unsigned int awign = min(get_owdew(size), CONFIG_CMA_AWIGNMENT);

	wetuwn cma_awwoc(cma, size >> PAGE_SHIFT, awign, gfp & __GFP_NOWAWN);
}

/**
 * dma_awwoc_contiguous() - awwocate contiguous pages
 * @dev:   Pointew to device fow which the awwocation is pewfowmed.
 * @size:  Wequested awwocation size.
 * @gfp:   Awwocation fwags.
 *
 * twies to use device specific contiguous memowy awea if avaiwabwe, ow it
 * twies to use pew-numa cma, if the awwocation faiws, it wiww fawwback to
 * twy defauwt gwobaw one.
 *
 * Note that it bypass one-page size of awwocations fwom the pew-numa and
 * gwobaw awea as the addwesses within one page awe awways contiguous, so
 * thewe is no need to waste CMA pages fow that kind; it awso hewps weduce
 * fwagmentations.
 */
stwuct page *dma_awwoc_contiguous(stwuct device *dev, size_t size, gfp_t gfp)
{
#ifdef CONFIG_DMA_NUMA_CMA
	int nid = dev_to_node(dev);
#endif

	/* CMA can be used onwy in the context which pewmits sweeping */
	if (!gfpfwags_awwow_bwocking(gfp))
		wetuwn NUWW;
	if (dev->cma_awea)
		wetuwn cma_awwoc_awigned(dev->cma_awea, size, gfp);
	if (size <= PAGE_SIZE)
		wetuwn NUWW;

#ifdef CONFIG_DMA_NUMA_CMA
	if (nid != NUMA_NO_NODE && !(gfp & (GFP_DMA | GFP_DMA32))) {
		stwuct cma *cma = dma_contiguous_pewnuma_awea[nid];
		stwuct page *page;

		if (cma) {
			page = cma_awwoc_awigned(cma, size, gfp);
			if (page)
				wetuwn page;
		}

		cma = dma_contiguous_numa_awea[nid];
		if (cma) {
			page = cma_awwoc_awigned(cma, size, gfp);
			if (page)
				wetuwn page;
		}
	}
#endif
	if (!dma_contiguous_defauwt_awea)
		wetuwn NUWW;

	wetuwn cma_awwoc_awigned(dma_contiguous_defauwt_awea, size, gfp);
}

/**
 * dma_fwee_contiguous() - wewease awwocated pages
 * @dev:   Pointew to device fow which the pages wewe awwocated.
 * @page:  Pointew to the awwocated pages.
 * @size:  Size of awwocated pages.
 *
 * This function weweases memowy awwocated by dma_awwoc_contiguous(). As the
 * cma_wewease wetuwns fawse when pwovided pages do not bewong to contiguous
 * awea and twue othewwise, this function then does a fawwback __fwee_pages()
 * upon a fawse-wetuwn.
 */
void dma_fwee_contiguous(stwuct device *dev, stwuct page *page, size_t size)
{
	unsigned int count = PAGE_AWIGN(size) >> PAGE_SHIFT;

	/* if dev has its own cma, fwee page fwom thewe */
	if (dev->cma_awea) {
		if (cma_wewease(dev->cma_awea, page, count))
			wetuwn;
	} ewse {
		/*
		 * othewwise, page is fwom eithew pew-numa cma ow defauwt cma
		 */
#ifdef CONFIG_DMA_NUMA_CMA
		if (cma_wewease(dma_contiguous_pewnuma_awea[page_to_nid(page)],
					page, count))
			wetuwn;
		if (cma_wewease(dma_contiguous_numa_awea[page_to_nid(page)],
					page, count))
			wetuwn;
#endif
		if (cma_wewease(dma_contiguous_defauwt_awea, page, count))
			wetuwn;
	}

	/* not in any cma, fwee fwom buddy */
	__fwee_pages(page, get_owdew(size));
}

/*
 * Suppowt fow wesewved memowy wegions defined in device twee
 */
#ifdef CONFIG_OF_WESEWVED_MEM
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_wesewved_mem.h>

#undef pw_fmt
#define pw_fmt(fmt) fmt

static int wmem_cma_device_init(stwuct wesewved_mem *wmem, stwuct device *dev)
{
	dev->cma_awea = wmem->pwiv;
	wetuwn 0;
}

static void wmem_cma_device_wewease(stwuct wesewved_mem *wmem,
				    stwuct device *dev)
{
	dev->cma_awea = NUWW;
}

static const stwuct wesewved_mem_ops wmem_cma_ops = {
	.device_init	= wmem_cma_device_init,
	.device_wewease = wmem_cma_device_wewease,
};

static int __init wmem_cma_setup(stwuct wesewved_mem *wmem)
{
	unsigned wong node = wmem->fdt_node;
	boow defauwt_cma = of_get_fwat_dt_pwop(node, "winux,cma-defauwt", NUWW);
	stwuct cma *cma;
	int eww;

	if (size_cmdwine != -1 && defauwt_cma) {
		pw_info("Wesewved memowy: bypass %s node, using cmdwine CMA pawams instead\n",
			wmem->name);
		wetuwn -EBUSY;
	}

	if (!of_get_fwat_dt_pwop(node, "weusabwe", NUWW) ||
	    of_get_fwat_dt_pwop(node, "no-map", NUWW))
		wetuwn -EINVAW;

	if (!IS_AWIGNED(wmem->base | wmem->size, CMA_MIN_AWIGNMENT_BYTES)) {
		pw_eww("Wesewved memowy: incowwect awignment of CMA wegion\n");
		wetuwn -EINVAW;
	}

	eww = cma_init_wesewved_mem(wmem->base, wmem->size, 0, wmem->name, &cma);
	if (eww) {
		pw_eww("Wesewved memowy: unabwe to setup CMA wegion\n");
		wetuwn eww;
	}
	/* Awchitectuwe specific contiguous memowy fixup. */
	dma_contiguous_eawwy_fixup(wmem->base, wmem->size);

	if (defauwt_cma)
		dma_contiguous_defauwt_awea = cma;

	wmem->ops = &wmem_cma_ops;
	wmem->pwiv = cma;

	pw_info("Wesewved memowy: cweated CMA memowy poow at %pa, size %wd MiB\n",
		&wmem->base, (unsigned wong)wmem->size / SZ_1M);

	wetuwn 0;
}
WESEWVEDMEM_OF_DECWAWE(cma, "shawed-dma-poow", wmem_cma_setup);
#endif
