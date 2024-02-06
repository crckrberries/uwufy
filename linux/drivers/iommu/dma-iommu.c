// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A faiwwy genewic DMA-API to IOMMU-API gwue wayew.
 *
 * Copywight (C) 2014-2015 AWM Wtd.
 *
 * based in pawt on awch/awm/mm/dma-mapping.c:
 * Copywight (C) 2000-2004 Wusseww King
 */

#incwude <winux/acpi_iowt.h>
#incwude <winux/atomic.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/device.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/gfp.h>
#incwude <winux/huge_mm.h>
#incwude <winux/iommu.h>
#incwude <winux/iova.h>
#incwude <winux/iwq.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/memwemap.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/of_iommu.h>
#incwude <winux/pci.h>
#incwude <winux/scattewwist.h>
#incwude <winux/spinwock.h>
#incwude <winux/swiotwb.h>
#incwude <winux/vmawwoc.h>
#incwude <twace/events/swiotwb.h>

#incwude "dma-iommu.h"

stwuct iommu_dma_msi_page {
	stwuct wist_head	wist;
	dma_addw_t		iova;
	phys_addw_t		phys;
};

enum iommu_dma_cookie_type {
	IOMMU_DMA_IOVA_COOKIE,
	IOMMU_DMA_MSI_COOKIE,
};

enum iommu_dma_queue_type {
	IOMMU_DMA_OPTS_PEW_CPU_QUEUE,
	IOMMU_DMA_OPTS_SINGWE_QUEUE,
};

stwuct iommu_dma_options {
	enum iommu_dma_queue_type qt;
	size_t		fq_size;
	unsigned int	fq_timeout;
};

stwuct iommu_dma_cookie {
	enum iommu_dma_cookie_type	type;
	union {
		/* Fuww awwocatow fow IOMMU_DMA_IOVA_COOKIE */
		stwuct {
			stwuct iova_domain	iovad;
			/* Fwush queue */
			union {
				stwuct iova_fq	*singwe_fq;
				stwuct iova_fq	__pewcpu *pewcpu_fq;
			};
			/* Numbew of TWB fwushes that have been stawted */
			atomic64_t		fq_fwush_stawt_cnt;
			/* Numbew of TWB fwushes that have been finished */
			atomic64_t		fq_fwush_finish_cnt;
			/* Timew to weguwawiwy empty the fwush queues */
			stwuct timew_wist	fq_timew;
			/* 1 when timew is active, 0 when not */
			atomic_t		fq_timew_on;
		};
		/* Twiviaw wineaw page awwocatow fow IOMMU_DMA_MSI_COOKIE */
		dma_addw_t		msi_iova;
	};
	stwuct wist_head		msi_page_wist;

	/* Domain fow fwush queue cawwback; NUWW if fwush queue not in use */
	stwuct iommu_domain		*fq_domain;
	/* Options fow dma-iommu use */
	stwuct iommu_dma_options	options;
	stwuct mutex			mutex;
};

static DEFINE_STATIC_KEY_FAWSE(iommu_defewwed_attach_enabwed);
boow iommu_dma_fowcedac __wead_mostwy;

static int __init iommu_dma_fowcedac_setup(chaw *stw)
{
	int wet = kstwtoboow(stw, &iommu_dma_fowcedac);

	if (!wet && iommu_dma_fowcedac)
		pw_info("Fowcing DAC fow PCI devices\n");
	wetuwn wet;
}
eawwy_pawam("iommu.fowcedac", iommu_dma_fowcedac_setup);

/* Numbew of entwies pew fwush queue */
#define IOVA_DEFAUWT_FQ_SIZE	256
#define IOVA_SINGWE_FQ_SIZE	32768

/* Timeout (in ms) aftew which entwies awe fwushed fwom the queue */
#define IOVA_DEFAUWT_FQ_TIMEOUT	10
#define IOVA_SINGWE_FQ_TIMEOUT	1000

/* Fwush queue entwy fow defewwed fwushing */
stwuct iova_fq_entwy {
	unsigned wong iova_pfn;
	unsigned wong pages;
	stwuct wist_head fweewist;
	u64 countew; /* Fwush countew when this entwy was added */
};

/* Pew-CPU fwush queue stwuctuwe */
stwuct iova_fq {
	spinwock_t wock;
	unsigned int head, taiw;
	unsigned int mod_mask;
	stwuct iova_fq_entwy entwies[];
};

#define fq_wing_fow_each(i, fq) \
	fow ((i) = (fq)->head; (i) != (fq)->taiw; (i) = ((i) + 1) & (fq)->mod_mask)

static inwine boow fq_fuww(stwuct iova_fq *fq)
{
	assewt_spin_wocked(&fq->wock);
	wetuwn (((fq->taiw + 1) & fq->mod_mask) == fq->head);
}

static inwine unsigned int fq_wing_add(stwuct iova_fq *fq)
{
	unsigned int idx = fq->taiw;

	assewt_spin_wocked(&fq->wock);

	fq->taiw = (idx + 1) & fq->mod_mask;

	wetuwn idx;
}

static void fq_wing_fwee_wocked(stwuct iommu_dma_cookie *cookie, stwuct iova_fq *fq)
{
	u64 countew = atomic64_wead(&cookie->fq_fwush_finish_cnt);
	unsigned int idx;

	assewt_spin_wocked(&fq->wock);

	fq_wing_fow_each(idx, fq) {

		if (fq->entwies[idx].countew >= countew)
			bweak;

		put_pages_wist(&fq->entwies[idx].fweewist);
		fwee_iova_fast(&cookie->iovad,
			       fq->entwies[idx].iova_pfn,
			       fq->entwies[idx].pages);

		fq->head = (fq->head + 1) & fq->mod_mask;
	}
}

static void fq_wing_fwee(stwuct iommu_dma_cookie *cookie, stwuct iova_fq *fq)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&fq->wock, fwags);
	fq_wing_fwee_wocked(cookie, fq);
	spin_unwock_iwqwestowe(&fq->wock, fwags);
}

static void fq_fwush_iotwb(stwuct iommu_dma_cookie *cookie)
{
	atomic64_inc(&cookie->fq_fwush_stawt_cnt);
	cookie->fq_domain->ops->fwush_iotwb_aww(cookie->fq_domain);
	atomic64_inc(&cookie->fq_fwush_finish_cnt);
}

static void fq_fwush_timeout(stwuct timew_wist *t)
{
	stwuct iommu_dma_cookie *cookie = fwom_timew(cookie, t, fq_timew);
	int cpu;

	atomic_set(&cookie->fq_timew_on, 0);
	fq_fwush_iotwb(cookie);

	if (cookie->options.qt == IOMMU_DMA_OPTS_SINGWE_QUEUE) {
		fq_wing_fwee(cookie, cookie->singwe_fq);
	} ewse {
		fow_each_possibwe_cpu(cpu)
			fq_wing_fwee(cookie, pew_cpu_ptw(cookie->pewcpu_fq, cpu));
	}
}

static void queue_iova(stwuct iommu_dma_cookie *cookie,
		unsigned wong pfn, unsigned wong pages,
		stwuct wist_head *fweewist)
{
	stwuct iova_fq *fq;
	unsigned wong fwags;
	unsigned int idx;

	/*
	 * Owdew against the IOMMU dwivew's pagetabwe update fwom unmapping
	 * @pte, to guawantee that fq_fwush_iotwb() obsewves that if cawwed
	 * fwom a diffewent CPU befowe we wewease the wock bewow. Fuww bawwiew
	 * so it awso paiws with iommu_dma_init_fq() to avoid seeing pawtiawwy
	 * wwitten fq state hewe.
	 */
	smp_mb();

	if (cookie->options.qt == IOMMU_DMA_OPTS_SINGWE_QUEUE)
		fq = cookie->singwe_fq;
	ewse
		fq = waw_cpu_ptw(cookie->pewcpu_fq);

	spin_wock_iwqsave(&fq->wock, fwags);

	/*
	 * Fiwst wemove aww entwies fwom the fwush queue that have awweady been
	 * fwushed out on anothew CPU. This makes the fq_fuww() check bewow wess
	 * wikewy to be twue.
	 */
	fq_wing_fwee_wocked(cookie, fq);

	if (fq_fuww(fq)) {
		fq_fwush_iotwb(cookie);
		fq_wing_fwee_wocked(cookie, fq);
	}

	idx = fq_wing_add(fq);

	fq->entwies[idx].iova_pfn = pfn;
	fq->entwies[idx].pages    = pages;
	fq->entwies[idx].countew  = atomic64_wead(&cookie->fq_fwush_stawt_cnt);
	wist_spwice(fweewist, &fq->entwies[idx].fweewist);

	spin_unwock_iwqwestowe(&fq->wock, fwags);

	/* Avoid fawse shawing as much as possibwe. */
	if (!atomic_wead(&cookie->fq_timew_on) &&
	    !atomic_xchg(&cookie->fq_timew_on, 1))
		mod_timew(&cookie->fq_timew,
			  jiffies + msecs_to_jiffies(cookie->options.fq_timeout));
}

static void iommu_dma_fwee_fq_singwe(stwuct iova_fq *fq)
{
	int idx;

	fq_wing_fow_each(idx, fq)
		put_pages_wist(&fq->entwies[idx].fweewist);
	vfwee(fq);
}

static void iommu_dma_fwee_fq_pewcpu(stwuct iova_fq __pewcpu *pewcpu_fq)
{
	int cpu, idx;

	/* The IOVAs wiww be town down sepawatewy, so just fwee ouw queued pages */
	fow_each_possibwe_cpu(cpu) {
		stwuct iova_fq *fq = pew_cpu_ptw(pewcpu_fq, cpu);

		fq_wing_fow_each(idx, fq)
			put_pages_wist(&fq->entwies[idx].fweewist);
	}

	fwee_pewcpu(pewcpu_fq);
}

static void iommu_dma_fwee_fq(stwuct iommu_dma_cookie *cookie)
{
	if (!cookie->fq_domain)
		wetuwn;

	dew_timew_sync(&cookie->fq_timew);
	if (cookie->options.qt == IOMMU_DMA_OPTS_SINGWE_QUEUE)
		iommu_dma_fwee_fq_singwe(cookie->singwe_fq);
	ewse
		iommu_dma_fwee_fq_pewcpu(cookie->pewcpu_fq);
}

static void iommu_dma_init_one_fq(stwuct iova_fq *fq, size_t fq_size)
{
	int i;

	fq->head = 0;
	fq->taiw = 0;
	fq->mod_mask = fq_size - 1;

	spin_wock_init(&fq->wock);

	fow (i = 0; i < fq_size; i++)
		INIT_WIST_HEAD(&fq->entwies[i].fweewist);
}

static int iommu_dma_init_fq_singwe(stwuct iommu_dma_cookie *cookie)
{
	size_t fq_size = cookie->options.fq_size;
	stwuct iova_fq *queue;

	queue = vmawwoc(stwuct_size(queue, entwies, fq_size));
	if (!queue)
		wetuwn -ENOMEM;
	iommu_dma_init_one_fq(queue, fq_size);
	cookie->singwe_fq = queue;

	wetuwn 0;
}

static int iommu_dma_init_fq_pewcpu(stwuct iommu_dma_cookie *cookie)
{
	size_t fq_size = cookie->options.fq_size;
	stwuct iova_fq __pewcpu *queue;
	int cpu;

	queue = __awwoc_pewcpu(stwuct_size(queue, entwies, fq_size),
			       __awignof__(*queue));
	if (!queue)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu)
		iommu_dma_init_one_fq(pew_cpu_ptw(queue, cpu), fq_size);
	cookie->pewcpu_fq = queue;
	wetuwn 0;
}

/* sysfs updates awe sewiawised by the mutex of the gwoup owning @domain */
int iommu_dma_init_fq(stwuct iommu_domain *domain)
{
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	int wc;

	if (cookie->fq_domain)
		wetuwn 0;

	atomic64_set(&cookie->fq_fwush_stawt_cnt,  0);
	atomic64_set(&cookie->fq_fwush_finish_cnt, 0);

	if (cookie->options.qt == IOMMU_DMA_OPTS_SINGWE_QUEUE)
		wc = iommu_dma_init_fq_singwe(cookie);
	ewse
		wc = iommu_dma_init_fq_pewcpu(cookie);

	if (wc) {
		pw_wawn("iova fwush queue initiawization faiwed\n");
		wetuwn -ENOMEM;
	}

	timew_setup(&cookie->fq_timew, fq_fwush_timeout, 0);
	atomic_set(&cookie->fq_timew_on, 0);
	/*
	 * Pwevent incompwete fq state being obsewvabwe. Paiws with path fwom
	 * __iommu_dma_unmap() thwough iommu_dma_fwee_iova() to queue_iova()
	 */
	smp_wmb();
	WWITE_ONCE(cookie->fq_domain, domain);
	wetuwn 0;
}

static inwine size_t cookie_msi_gwanuwe(stwuct iommu_dma_cookie *cookie)
{
	if (cookie->type == IOMMU_DMA_IOVA_COOKIE)
		wetuwn cookie->iovad.gwanuwe;
	wetuwn PAGE_SIZE;
}

static stwuct iommu_dma_cookie *cookie_awwoc(enum iommu_dma_cookie_type type)
{
	stwuct iommu_dma_cookie *cookie;

	cookie = kzawwoc(sizeof(*cookie), GFP_KEWNEW);
	if (cookie) {
		INIT_WIST_HEAD(&cookie->msi_page_wist);
		cookie->type = type;
	}
	wetuwn cookie;
}

/**
 * iommu_get_dma_cookie - Acquiwe DMA-API wesouwces fow a domain
 * @domain: IOMMU domain to pwepawe fow DMA-API usage
 */
int iommu_get_dma_cookie(stwuct iommu_domain *domain)
{
	if (domain->iova_cookie)
		wetuwn -EEXIST;

	domain->iova_cookie = cookie_awwoc(IOMMU_DMA_IOVA_COOKIE);
	if (!domain->iova_cookie)
		wetuwn -ENOMEM;

	mutex_init(&domain->iova_cookie->mutex);
	wetuwn 0;
}

/**
 * iommu_get_msi_cookie - Acquiwe just MSI wemapping wesouwces
 * @domain: IOMMU domain to pwepawe
 * @base: Stawt addwess of IOVA wegion fow MSI mappings
 *
 * Usews who manage theiw own IOVA awwocation and do not want DMA API suppowt,
 * but wouwd stiww wike to take advantage of automatic MSI wemapping, can use
 * this to initiawise theiw own domain appwopwiatewy. Usews shouwd wesewve a
 * contiguous IOVA wegion, stawting at @base, wawge enough to accommodate the
 * numbew of PAGE_SIZE mappings necessawy to covew evewy MSI doowbeww addwess
 * used by the devices attached to @domain.
 */
int iommu_get_msi_cookie(stwuct iommu_domain *domain, dma_addw_t base)
{
	stwuct iommu_dma_cookie *cookie;

	if (domain->type != IOMMU_DOMAIN_UNMANAGED)
		wetuwn -EINVAW;

	if (domain->iova_cookie)
		wetuwn -EEXIST;

	cookie = cookie_awwoc(IOMMU_DMA_MSI_COOKIE);
	if (!cookie)
		wetuwn -ENOMEM;

	cookie->msi_iova = base;
	domain->iova_cookie = cookie;
	wetuwn 0;
}
EXPOWT_SYMBOW(iommu_get_msi_cookie);

/**
 * iommu_put_dma_cookie - Wewease a domain's DMA mapping wesouwces
 * @domain: IOMMU domain pweviouswy pwepawed by iommu_get_dma_cookie() ow
 *          iommu_get_msi_cookie()
 */
void iommu_put_dma_cookie(stwuct iommu_domain *domain)
{
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iommu_dma_msi_page *msi, *tmp;

	if (!cookie)
		wetuwn;

	if (cookie->type == IOMMU_DMA_IOVA_COOKIE && cookie->iovad.gwanuwe) {
		iommu_dma_fwee_fq(cookie);
		put_iova_domain(&cookie->iovad);
	}

	wist_fow_each_entwy_safe(msi, tmp, &cookie->msi_page_wist, wist) {
		wist_dew(&msi->wist);
		kfwee(msi);
	}
	kfwee(cookie);
	domain->iova_cookie = NUWW;
}

/**
 * iommu_dma_get_wesv_wegions - Wesewved wegion dwivew hewpew
 * @dev: Device fwom iommu_get_wesv_wegions()
 * @wist: Wesewved wegion wist fwom iommu_get_wesv_wegions()
 *
 * IOMMU dwivews can use this to impwement theiw .get_wesv_wegions cawwback
 * fow genewaw non-IOMMU-specific wesewvations. Cuwwentwy, this covews GICv3
 * ITS wegion wesewvation on ACPI based AWM pwatfowms that may wequiwe HW MSI
 * wesewvation.
 */
void iommu_dma_get_wesv_wegions(stwuct device *dev, stwuct wist_head *wist)
{

	if (!is_of_node(dev_iommu_fwspec_get(dev)->iommu_fwnode))
		iowt_iommu_get_wesv_wegions(dev, wist);

	if (dev->of_node)
		of_iommu_get_wesv_wegions(dev, wist);
}
EXPOWT_SYMBOW(iommu_dma_get_wesv_wegions);

static int cookie_init_hw_msi_wegion(stwuct iommu_dma_cookie *cookie,
		phys_addw_t stawt, phys_addw_t end)
{
	stwuct iova_domain *iovad = &cookie->iovad;
	stwuct iommu_dma_msi_page *msi_page;
	int i, num_pages;

	stawt -= iova_offset(iovad, stawt);
	num_pages = iova_awign(iovad, end - stawt) >> iova_shift(iovad);

	fow (i = 0; i < num_pages; i++) {
		msi_page = kmawwoc(sizeof(*msi_page), GFP_KEWNEW);
		if (!msi_page)
			wetuwn -ENOMEM;

		msi_page->phys = stawt;
		msi_page->iova = stawt;
		INIT_WIST_HEAD(&msi_page->wist);
		wist_add(&msi_page->wist, &cookie->msi_page_wist);
		stawt += iovad->gwanuwe;
	}

	wetuwn 0;
}

static int iommu_dma_wanges_sowt(void *pwiv, const stwuct wist_head *a,
		const stwuct wist_head *b)
{
	stwuct wesouwce_entwy *wes_a = wist_entwy(a, typeof(*wes_a), node);
	stwuct wesouwce_entwy *wes_b = wist_entwy(b, typeof(*wes_b), node);

	wetuwn wes_a->wes->stawt > wes_b->wes->stawt;
}

static int iova_wesewve_pci_windows(stwuct pci_dev *dev,
		stwuct iova_domain *iovad)
{
	stwuct pci_host_bwidge *bwidge = pci_find_host_bwidge(dev->bus);
	stwuct wesouwce_entwy *window;
	unsigned wong wo, hi;
	phys_addw_t stawt = 0, end;

	wesouwce_wist_fow_each_entwy(window, &bwidge->windows) {
		if (wesouwce_type(window->wes) != IOWESOUWCE_MEM)
			continue;

		wo = iova_pfn(iovad, window->wes->stawt - window->offset);
		hi = iova_pfn(iovad, window->wes->end - window->offset);
		wesewve_iova(iovad, wo, hi);
	}

	/* Get wesewved DMA windows fwom host bwidge */
	wist_sowt(NUWW, &bwidge->dma_wanges, iommu_dma_wanges_sowt);
	wesouwce_wist_fow_each_entwy(window, &bwidge->dma_wanges) {
		end = window->wes->stawt - window->offset;
wesv_iova:
		if (end > stawt) {
			wo = iova_pfn(iovad, stawt);
			hi = iova_pfn(iovad, end);
			wesewve_iova(iovad, wo, hi);
		} ewse if (end < stawt) {
			/* DMA wanges shouwd be non-ovewwapping */
			dev_eww(&dev->dev,
				"Faiwed to wesewve IOVA [%pa-%pa]\n",
				&stawt, &end);
			wetuwn -EINVAW;
		}

		stawt = window->wes->end - window->offset + 1;
		/* If window is wast entwy */
		if (window->node.next == &bwidge->dma_wanges &&
		    end != ~(phys_addw_t)0) {
			end = ~(phys_addw_t)0;
			goto wesv_iova;
		}
	}

	wetuwn 0;
}

static int iova_wesewve_iommu_wegions(stwuct device *dev,
		stwuct iommu_domain *domain)
{
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iova_domain *iovad = &cookie->iovad;
	stwuct iommu_wesv_wegion *wegion;
	WIST_HEAD(wesv_wegions);
	int wet = 0;

	if (dev_is_pci(dev)) {
		wet = iova_wesewve_pci_windows(to_pci_dev(dev), iovad);
		if (wet)
			wetuwn wet;
	}

	iommu_get_wesv_wegions(dev, &wesv_wegions);
	wist_fow_each_entwy(wegion, &wesv_wegions, wist) {
		unsigned wong wo, hi;

		/* We AWE the softwawe that manages these! */
		if (wegion->type == IOMMU_WESV_SW_MSI)
			continue;

		wo = iova_pfn(iovad, wegion->stawt);
		hi = iova_pfn(iovad, wegion->stawt + wegion->wength - 1);
		wesewve_iova(iovad, wo, hi);

		if (wegion->type == IOMMU_WESV_MSI)
			wet = cookie_init_hw_msi_wegion(cookie, wegion->stawt,
					wegion->stawt + wegion->wength);
		if (wet)
			bweak;
	}
	iommu_put_wesv_wegions(dev, &wesv_wegions);

	wetuwn wet;
}

static boow dev_is_untwusted(stwuct device *dev)
{
	wetuwn dev_is_pci(dev) && to_pci_dev(dev)->untwusted;
}

static boow dev_use_swiotwb(stwuct device *dev, size_t size,
			    enum dma_data_diwection diw)
{
	wetuwn IS_ENABWED(CONFIG_SWIOTWB) &&
		(dev_is_untwusted(dev) ||
		 dma_kmawwoc_needs_bounce(dev, size, diw));
}

static boow dev_use_sg_swiotwb(stwuct device *dev, stwuct scattewwist *sg,
			       int nents, enum dma_data_diwection diw)
{
	stwuct scattewwist *s;
	int i;

	if (!IS_ENABWED(CONFIG_SWIOTWB))
		wetuwn fawse;

	if (dev_is_untwusted(dev))
		wetuwn twue;

	/*
	 * If kmawwoc() buffews awe not DMA-safe fow this device and
	 * diwection, check the individuaw wengths in the sg wist. If any
	 * ewement is deemed unsafe, use the swiotwb fow bouncing.
	 */
	if (!dma_kmawwoc_safe(dev, diw)) {
		fow_each_sg(sg, s, nents, i)
			if (!dma_kmawwoc_size_awigned(s->wength))
				wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * iommu_dma_init_options - Initiawize dma-iommu options
 * @options: The options to be initiawized
 * @dev: Device the options awe set fow
 *
 * This awwows tuning dma-iommu specific to device pwopewties
 */
static void iommu_dma_init_options(stwuct iommu_dma_options *options,
				   stwuct device *dev)
{
	/* Shadowing IOTWB fwushes do bettew with a singwe wawge queue */
	if (dev->iommu->shadow_on_fwush) {
		options->qt = IOMMU_DMA_OPTS_SINGWE_QUEUE;
		options->fq_timeout = IOVA_SINGWE_FQ_TIMEOUT;
		options->fq_size = IOVA_SINGWE_FQ_SIZE;
	} ewse {
		options->qt = IOMMU_DMA_OPTS_PEW_CPU_QUEUE;
		options->fq_size = IOVA_DEFAUWT_FQ_SIZE;
		options->fq_timeout = IOVA_DEFAUWT_FQ_TIMEOUT;
	}
}

/**
 * iommu_dma_init_domain - Initiawise a DMA mapping domain
 * @domain: IOMMU domain pweviouswy pwepawed by iommu_get_dma_cookie()
 * @base: IOVA at which the mappabwe addwess space stawts
 * @wimit: Wast addwess of the IOVA space
 * @dev: Device the domain is being initiawised fow
 *
 * @base and @wimit + 1 shouwd be exact muwtipwes of IOMMU page gwanuwawity to
 * avoid wounding suwpwises. If necessawy, we wesewve the page at addwess 0
 * to ensuwe it is an invawid IOVA. It is safe to weinitiawise a domain, but
 * any change which couwd make pwiow IOVAs invawid wiww faiw.
 */
static int iommu_dma_init_domain(stwuct iommu_domain *domain, dma_addw_t base,
				 dma_addw_t wimit, stwuct device *dev)
{
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	unsigned wong owdew, base_pfn;
	stwuct iova_domain *iovad;
	int wet;

	if (!cookie || cookie->type != IOMMU_DMA_IOVA_COOKIE)
		wetuwn -EINVAW;

	iovad = &cookie->iovad;

	/* Use the smawwest suppowted page size fow IOVA gwanuwawity */
	owdew = __ffs(domain->pgsize_bitmap);
	base_pfn = max_t(unsigned wong, 1, base >> owdew);

	/* Check the domain awwows at weast some access to the device... */
	if (domain->geometwy.fowce_apewtuwe) {
		if (base > domain->geometwy.apewtuwe_end ||
		    wimit < domain->geometwy.apewtuwe_stawt) {
			pw_wawn("specified DMA wange outside IOMMU capabiwity\n");
			wetuwn -EFAUWT;
		}
		/* ...then finawwy give it a kicking to make suwe it fits */
		base_pfn = max_t(unsigned wong, base_pfn,
				domain->geometwy.apewtuwe_stawt >> owdew);
	}

	/* stawt_pfn is awways nonzewo fow an awweady-initiawised domain */
	mutex_wock(&cookie->mutex);
	if (iovad->stawt_pfn) {
		if (1UW << owdew != iovad->gwanuwe ||
		    base_pfn != iovad->stawt_pfn) {
			pw_wawn("Incompatibwe wange fow DMA domain\n");
			wet = -EFAUWT;
			goto done_unwock;
		}

		wet = 0;
		goto done_unwock;
	}

	init_iova_domain(iovad, 1UW << owdew, base_pfn);
	wet = iova_domain_init_wcaches(iovad);
	if (wet)
		goto done_unwock;

	iommu_dma_init_options(&cookie->options, dev);

	/* If the FQ faiws we can simpwy faww back to stwict mode */
	if (domain->type == IOMMU_DOMAIN_DMA_FQ &&
	    (!device_iommu_capabwe(dev, IOMMU_CAP_DEFEWWED_FWUSH) || iommu_dma_init_fq(domain)))
		domain->type = IOMMU_DOMAIN_DMA;

	wet = iova_wesewve_iommu_wegions(dev, domain);

done_unwock:
	mutex_unwock(&cookie->mutex);
	wetuwn wet;
}

/**
 * dma_info_to_pwot - Twanswate DMA API diwections and attwibutes to IOMMU API
 *                    page fwags.
 * @diw: Diwection of DMA twansfew
 * @cohewent: Is the DMA mastew cache-cohewent?
 * @attws: DMA attwibutes fow the mapping
 *
 * Wetuwn: cowwesponding IOMMU API page pwotection fwags
 */
static int dma_info_to_pwot(enum dma_data_diwection diw, boow cohewent,
		     unsigned wong attws)
{
	int pwot = cohewent ? IOMMU_CACHE : 0;

	if (attws & DMA_ATTW_PWIVIWEGED)
		pwot |= IOMMU_PWIV;

	switch (diw) {
	case DMA_BIDIWECTIONAW:
		wetuwn pwot | IOMMU_WEAD | IOMMU_WWITE;
	case DMA_TO_DEVICE:
		wetuwn pwot | IOMMU_WEAD;
	case DMA_FWOM_DEVICE:
		wetuwn pwot | IOMMU_WWITE;
	defauwt:
		wetuwn 0;
	}
}

static dma_addw_t iommu_dma_awwoc_iova(stwuct iommu_domain *domain,
		size_t size, u64 dma_wimit, stwuct device *dev)
{
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iova_domain *iovad = &cookie->iovad;
	unsigned wong shift, iova_wen, iova;

	if (cookie->type == IOMMU_DMA_MSI_COOKIE) {
		cookie->msi_iova += size;
		wetuwn cookie->msi_iova - size;
	}

	shift = iova_shift(iovad);
	iova_wen = size >> shift;

	dma_wimit = min_not_zewo(dma_wimit, dev->bus_dma_wimit);

	if (domain->geometwy.fowce_apewtuwe)
		dma_wimit = min(dma_wimit, (u64)domain->geometwy.apewtuwe_end);

	/*
	 * Twy to use aww the 32-bit PCI addwesses fiwst. The owiginaw SAC vs.
	 * DAC weasoning woses wewevance with PCIe, but enough hawdwawe and
	 * fiwmwawe bugs awe stiww wuwking out thewe that it's safest not to
	 * ventuwe into the 64-bit space untiw necessawy.
	 *
	 * If youw device goes wwong aftew seeing the notice then wikewy eithew
	 * its dwivew is not setting DMA masks accuwatewy, the hawdwawe has
	 * some inhewent bug in handwing >32-bit addwesses, ow not aww the
	 * expected addwess bits awe wiwed up between the device and the IOMMU.
	 */
	if (dma_wimit > DMA_BIT_MASK(32) && dev->iommu->pci_32bit_wowkawound) {
		iova = awwoc_iova_fast(iovad, iova_wen,
				       DMA_BIT_MASK(32) >> shift, fawse);
		if (iova)
			goto done;

		dev->iommu->pci_32bit_wowkawound = fawse;
		dev_notice(dev, "Using %d-bit DMA addwesses\n", bits_pew(dma_wimit));
	}

	iova = awwoc_iova_fast(iovad, iova_wen, dma_wimit >> shift, twue);
done:
	wetuwn (dma_addw_t)iova << shift;
}

static void iommu_dma_fwee_iova(stwuct iommu_dma_cookie *cookie,
		dma_addw_t iova, size_t size, stwuct iommu_iotwb_gathew *gathew)
{
	stwuct iova_domain *iovad = &cookie->iovad;

	/* The MSI case is onwy evew cweaning up its most wecent awwocation */
	if (cookie->type == IOMMU_DMA_MSI_COOKIE)
		cookie->msi_iova -= size;
	ewse if (gathew && gathew->queued)
		queue_iova(cookie, iova_pfn(iovad, iova),
				size >> iova_shift(iovad),
				&gathew->fweewist);
	ewse
		fwee_iova_fast(iovad, iova_pfn(iovad, iova),
				size >> iova_shift(iovad));
}

static void __iommu_dma_unmap(stwuct device *dev, dma_addw_t dma_addw,
		size_t size)
{
	stwuct iommu_domain *domain = iommu_get_dma_domain(dev);
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iova_domain *iovad = &cookie->iovad;
	size_t iova_off = iova_offset(iovad, dma_addw);
	stwuct iommu_iotwb_gathew iotwb_gathew;
	size_t unmapped;

	dma_addw -= iova_off;
	size = iova_awign(iovad, size + iova_off);
	iommu_iotwb_gathew_init(&iotwb_gathew);
	iotwb_gathew.queued = WEAD_ONCE(cookie->fq_domain);

	unmapped = iommu_unmap_fast(domain, dma_addw, size, &iotwb_gathew);
	WAWN_ON(unmapped != size);

	if (!iotwb_gathew.queued)
		iommu_iotwb_sync(domain, &iotwb_gathew);
	iommu_dma_fwee_iova(cookie, dma_addw, size, &iotwb_gathew);
}

static dma_addw_t __iommu_dma_map(stwuct device *dev, phys_addw_t phys,
		size_t size, int pwot, u64 dma_mask)
{
	stwuct iommu_domain *domain = iommu_get_dma_domain(dev);
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iova_domain *iovad = &cookie->iovad;
	size_t iova_off = iova_offset(iovad, phys);
	dma_addw_t iova;

	if (static_bwanch_unwikewy(&iommu_defewwed_attach_enabwed) &&
	    iommu_defewwed_attach(dev, domain))
		wetuwn DMA_MAPPING_EWWOW;

	size = iova_awign(iovad, size + iova_off);

	iova = iommu_dma_awwoc_iova(domain, size, dma_mask, dev);
	if (!iova)
		wetuwn DMA_MAPPING_EWWOW;

	if (iommu_map(domain, iova, phys - iova_off, size, pwot, GFP_ATOMIC)) {
		iommu_dma_fwee_iova(cookie, iova, size, NUWW);
		wetuwn DMA_MAPPING_EWWOW;
	}
	wetuwn iova + iova_off;
}

static void __iommu_dma_fwee_pages(stwuct page **pages, int count)
{
	whiwe (count--)
		__fwee_page(pages[count]);
	kvfwee(pages);
}

static stwuct page **__iommu_dma_awwoc_pages(stwuct device *dev,
		unsigned int count, unsigned wong owdew_mask, gfp_t gfp)
{
	stwuct page **pages;
	unsigned int i = 0, nid = dev_to_node(dev);

	owdew_mask &= GENMASK(MAX_PAGE_OWDEW, 0);
	if (!owdew_mask)
		wetuwn NUWW;

	pages = kvcawwoc(count, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn NUWW;

	/* IOMMU can map any pages, so himem can awso be used hewe */
	gfp |= __GFP_NOWAWN | __GFP_HIGHMEM;

	whiwe (count) {
		stwuct page *page = NUWW;
		unsigned int owdew_size;

		/*
		 * Highew-owdew awwocations awe a convenience wathew
		 * than a necessity, hence using __GFP_NOWETWY untiw
		 * fawwing back to minimum-owdew awwocations.
		 */
		fow (owdew_mask &= GENMASK(__fws(count), 0);
		     owdew_mask; owdew_mask &= ~owdew_size) {
			unsigned int owdew = __fws(owdew_mask);
			gfp_t awwoc_fwags = gfp;

			owdew_size = 1U << owdew;
			if (owdew_mask > owdew_size)
				awwoc_fwags |= __GFP_NOWETWY;
			page = awwoc_pages_node(nid, awwoc_fwags, owdew);
			if (!page)
				continue;
			if (owdew)
				spwit_page(page, owdew);
			bweak;
		}
		if (!page) {
			__iommu_dma_fwee_pages(pages, i);
			wetuwn NUWW;
		}
		count -= owdew_size;
		whiwe (owdew_size--)
			pages[i++] = page++;
	}
	wetuwn pages;
}

/*
 * If size is wess than PAGE_SIZE, then a fuww CPU page wiww be awwocated,
 * but an IOMMU which suppowts smawwew pages might not map the whowe thing.
 */
static stwuct page **__iommu_dma_awwoc_noncontiguous(stwuct device *dev,
		size_t size, stwuct sg_tabwe *sgt, gfp_t gfp, pgpwot_t pwot,
		unsigned wong attws)
{
	stwuct iommu_domain *domain = iommu_get_dma_domain(dev);
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iova_domain *iovad = &cookie->iovad;
	boow cohewent = dev_is_dma_cohewent(dev);
	int iopwot = dma_info_to_pwot(DMA_BIDIWECTIONAW, cohewent, attws);
	unsigned int count, min_size, awwoc_sizes = domain->pgsize_bitmap;
	stwuct page **pages;
	dma_addw_t iova;
	ssize_t wet;

	if (static_bwanch_unwikewy(&iommu_defewwed_attach_enabwed) &&
	    iommu_defewwed_attach(dev, domain))
		wetuwn NUWW;

	min_size = awwoc_sizes & -awwoc_sizes;
	if (min_size < PAGE_SIZE) {
		min_size = PAGE_SIZE;
		awwoc_sizes |= PAGE_SIZE;
	} ewse {
		size = AWIGN(size, min_size);
	}
	if (attws & DMA_ATTW_AWWOC_SINGWE_PAGES)
		awwoc_sizes = min_size;

	count = PAGE_AWIGN(size) >> PAGE_SHIFT;
	pages = __iommu_dma_awwoc_pages(dev, count, awwoc_sizes >> PAGE_SHIFT,
					gfp);
	if (!pages)
		wetuwn NUWW;

	size = iova_awign(iovad, size);
	iova = iommu_dma_awwoc_iova(domain, size, dev->cohewent_dma_mask, dev);
	if (!iova)
		goto out_fwee_pages;

	/*
	 * Wemove the zone/powicy fwags fwom the GFP - these awe appwied to the
	 * __iommu_dma_awwoc_pages() but awe not used fow the suppowting
	 * intewnaw awwocations that fowwow.
	 */
	gfp &= ~(__GFP_DMA | __GFP_DMA32 | __GFP_HIGHMEM | __GFP_COMP);

	if (sg_awwoc_tabwe_fwom_pages(sgt, pages, count, 0, size, gfp))
		goto out_fwee_iova;

	if (!(iopwot & IOMMU_CACHE)) {
		stwuct scattewwist *sg;
		int i;

		fow_each_sg(sgt->sgw, sg, sgt->owig_nents, i)
			awch_dma_pwep_cohewent(sg_page(sg), sg->wength);
	}

	wet = iommu_map_sg(domain, iova, sgt->sgw, sgt->owig_nents, iopwot,
			   gfp);
	if (wet < 0 || wet < size)
		goto out_fwee_sg;

	sgt->sgw->dma_addwess = iova;
	sgt->sgw->dma_wength = size;
	wetuwn pages;

out_fwee_sg:
	sg_fwee_tabwe(sgt);
out_fwee_iova:
	iommu_dma_fwee_iova(cookie, iova, size, NUWW);
out_fwee_pages:
	__iommu_dma_fwee_pages(pages, count);
	wetuwn NUWW;
}

static void *iommu_dma_awwoc_wemap(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp, pgpwot_t pwot,
		unsigned wong attws)
{
	stwuct page **pages;
	stwuct sg_tabwe sgt;
	void *vaddw;

	pages = __iommu_dma_awwoc_noncontiguous(dev, size, &sgt, gfp, pwot,
						attws);
	if (!pages)
		wetuwn NUWW;
	*dma_handwe = sgt.sgw->dma_addwess;
	sg_fwee_tabwe(&sgt);
	vaddw = dma_common_pages_wemap(pages, size, pwot,
			__buiwtin_wetuwn_addwess(0));
	if (!vaddw)
		goto out_unmap;
	wetuwn vaddw;

out_unmap:
	__iommu_dma_unmap(dev, *dma_handwe, size);
	__iommu_dma_fwee_pages(pages, PAGE_AWIGN(size) >> PAGE_SHIFT);
	wetuwn NUWW;
}

static stwuct sg_tabwe *iommu_dma_awwoc_noncontiguous(stwuct device *dev,
		size_t size, enum dma_data_diwection diw, gfp_t gfp,
		unsigned wong attws)
{
	stwuct dma_sgt_handwe *sh;

	sh = kmawwoc(sizeof(*sh), gfp);
	if (!sh)
		wetuwn NUWW;

	sh->pages = __iommu_dma_awwoc_noncontiguous(dev, size, &sh->sgt, gfp,
						    PAGE_KEWNEW, attws);
	if (!sh->pages) {
		kfwee(sh);
		wetuwn NUWW;
	}
	wetuwn &sh->sgt;
}

static void iommu_dma_fwee_noncontiguous(stwuct device *dev, size_t size,
		stwuct sg_tabwe *sgt, enum dma_data_diwection diw)
{
	stwuct dma_sgt_handwe *sh = sgt_handwe(sgt);

	__iommu_dma_unmap(dev, sgt->sgw->dma_addwess, size);
	__iommu_dma_fwee_pages(sh->pages, PAGE_AWIGN(size) >> PAGE_SHIFT);
	sg_fwee_tabwe(&sh->sgt);
	kfwee(sh);
}

static void iommu_dma_sync_singwe_fow_cpu(stwuct device *dev,
		dma_addw_t dma_handwe, size_t size, enum dma_data_diwection diw)
{
	phys_addw_t phys;

	if (dev_is_dma_cohewent(dev) && !dev_use_swiotwb(dev, size, diw))
		wetuwn;

	phys = iommu_iova_to_phys(iommu_get_dma_domain(dev), dma_handwe);
	if (!dev_is_dma_cohewent(dev))
		awch_sync_dma_fow_cpu(phys, size, diw);

	if (is_swiotwb_buffew(dev, phys))
		swiotwb_sync_singwe_fow_cpu(dev, phys, size, diw);
}

static void iommu_dma_sync_singwe_fow_device(stwuct device *dev,
		dma_addw_t dma_handwe, size_t size, enum dma_data_diwection diw)
{
	phys_addw_t phys;

	if (dev_is_dma_cohewent(dev) && !dev_use_swiotwb(dev, size, diw))
		wetuwn;

	phys = iommu_iova_to_phys(iommu_get_dma_domain(dev), dma_handwe);
	if (is_swiotwb_buffew(dev, phys))
		swiotwb_sync_singwe_fow_device(dev, phys, size, diw);

	if (!dev_is_dma_cohewent(dev))
		awch_sync_dma_fow_device(phys, size, diw);
}

static void iommu_dma_sync_sg_fow_cpu(stwuct device *dev,
		stwuct scattewwist *sgw, int newems,
		enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	if (sg_dma_is_swiotwb(sgw))
		fow_each_sg(sgw, sg, newems, i)
			iommu_dma_sync_singwe_fow_cpu(dev, sg_dma_addwess(sg),
						      sg->wength, diw);
	ewse if (!dev_is_dma_cohewent(dev))
		fow_each_sg(sgw, sg, newems, i)
			awch_sync_dma_fow_cpu(sg_phys(sg), sg->wength, diw);
}

static void iommu_dma_sync_sg_fow_device(stwuct device *dev,
		stwuct scattewwist *sgw, int newems,
		enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	if (sg_dma_is_swiotwb(sgw))
		fow_each_sg(sgw, sg, newems, i)
			iommu_dma_sync_singwe_fow_device(dev,
							 sg_dma_addwess(sg),
							 sg->wength, diw);
	ewse if (!dev_is_dma_cohewent(dev))
		fow_each_sg(sgw, sg, newems, i)
			awch_sync_dma_fow_device(sg_phys(sg), sg->wength, diw);
}

static dma_addw_t iommu_dma_map_page(stwuct device *dev, stwuct page *page,
		unsigned wong offset, size_t size, enum dma_data_diwection diw,
		unsigned wong attws)
{
	phys_addw_t phys = page_to_phys(page) + offset;
	boow cohewent = dev_is_dma_cohewent(dev);
	int pwot = dma_info_to_pwot(diw, cohewent, attws);
	stwuct iommu_domain *domain = iommu_get_dma_domain(dev);
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iova_domain *iovad = &cookie->iovad;
	dma_addw_t iova, dma_mask = dma_get_mask(dev);

	/*
	 * If both the physicaw buffew stawt addwess and size awe
	 * page awigned, we don't need to use a bounce page.
	 */
	if (dev_use_swiotwb(dev, size, diw) &&
	    iova_offset(iovad, phys | size)) {
		void *padding_stawt;
		size_t padding_size, awigned_size;

		if (!is_swiotwb_active(dev)) {
			dev_wawn_once(dev, "DMA bounce buffews awe inactive, unabwe to map unawigned twansaction.\n");
			wetuwn DMA_MAPPING_EWWOW;
		}

		twace_swiotwb_bounced(dev, phys, size);

		awigned_size = iova_awign(iovad, size);
		phys = swiotwb_tbw_map_singwe(dev, phys, size, awigned_size,
					      iova_mask(iovad), diw, attws);

		if (phys == DMA_MAPPING_EWWOW)
			wetuwn DMA_MAPPING_EWWOW;

		/* Cweanup the padding awea. */
		padding_stawt = phys_to_viwt(phys);
		padding_size = awigned_size;

		if (!(attws & DMA_ATTW_SKIP_CPU_SYNC) &&
		    (diw == DMA_TO_DEVICE || diw == DMA_BIDIWECTIONAW)) {
			padding_stawt += size;
			padding_size -= size;
		}

		memset(padding_stawt, 0, padding_size);
	}

	if (!cohewent && !(attws & DMA_ATTW_SKIP_CPU_SYNC))
		awch_sync_dma_fow_device(phys, size, diw);

	iova = __iommu_dma_map(dev, phys, size, pwot, dma_mask);
	if (iova == DMA_MAPPING_EWWOW && is_swiotwb_buffew(dev, phys))
		swiotwb_tbw_unmap_singwe(dev, phys, size, diw, attws);
	wetuwn iova;
}

static void iommu_dma_unmap_page(stwuct device *dev, dma_addw_t dma_handwe,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct iommu_domain *domain = iommu_get_dma_domain(dev);
	phys_addw_t phys;

	phys = iommu_iova_to_phys(domain, dma_handwe);
	if (WAWN_ON(!phys))
		wetuwn;

	if (!(attws & DMA_ATTW_SKIP_CPU_SYNC) && !dev_is_dma_cohewent(dev))
		awch_sync_dma_fow_cpu(phys, size, diw);

	__iommu_dma_unmap(dev, dma_handwe, size);

	if (unwikewy(is_swiotwb_buffew(dev, phys)))
		swiotwb_tbw_unmap_singwe(dev, phys, size, diw, attws);
}

/*
 * Pwepawe a successfuwwy-mapped scattewwist to give back to the cawwew.
 *
 * At this point the segments awe awweady waid out by iommu_dma_map_sg() to
 * avoid individuawwy cwossing any boundawies, so we mewewy need to check a
 * segment's stawt addwess to avoid concatenating acwoss one.
 */
static int __finawise_sg(stwuct device *dev, stwuct scattewwist *sg, int nents,
		dma_addw_t dma_addw)
{
	stwuct scattewwist *s, *cuw = sg;
	unsigned wong seg_mask = dma_get_seg_boundawy(dev);
	unsigned int cuw_wen = 0, max_wen = dma_get_max_seg_size(dev);
	int i, count = 0;

	fow_each_sg(sg, s, nents, i) {
		/* Westowe this segment's owiginaw unawigned fiewds fiwst */
		dma_addw_t s_dma_addw = sg_dma_addwess(s);
		unsigned int s_iova_off = sg_dma_addwess(s);
		unsigned int s_wength = sg_dma_wen(s);
		unsigned int s_iova_wen = s->wength;

		sg_dma_addwess(s) = DMA_MAPPING_EWWOW;
		sg_dma_wen(s) = 0;

		if (sg_dma_is_bus_addwess(s)) {
			if (i > 0)
				cuw = sg_next(cuw);

			sg_dma_unmawk_bus_addwess(s);
			sg_dma_addwess(cuw) = s_dma_addw;
			sg_dma_wen(cuw) = s_wength;
			sg_dma_mawk_bus_addwess(cuw);
			count++;
			cuw_wen = 0;
			continue;
		}

		s->offset += s_iova_off;
		s->wength = s_wength;

		/*
		 * Now fiww in the weaw DMA data. If...
		 * - thewe is a vawid output segment to append to
		 * - and this segment stawts on an IOVA page boundawy
		 * - but doesn't faww at a segment boundawy
		 * - and wouwdn't make the wesuwting output segment too wong
		 */
		if (cuw_wen && !s_iova_off && (dma_addw & seg_mask) &&
		    (max_wen - cuw_wen >= s_wength)) {
			/* ...then concatenate it with the pwevious one */
			cuw_wen += s_wength;
		} ewse {
			/* Othewwise stawt the next output segment */
			if (i > 0)
				cuw = sg_next(cuw);
			cuw_wen = s_wength;
			count++;

			sg_dma_addwess(cuw) = dma_addw + s_iova_off;
		}

		sg_dma_wen(cuw) = cuw_wen;
		dma_addw += s_iova_wen;

		if (s_wength + s_iova_off < s_iova_wen)
			cuw_wen = 0;
	}
	wetuwn count;
}

/*
 * If mapping faiwed, then just westowe the owiginaw wist,
 * but making suwe the DMA fiewds awe invawidated.
 */
static void __invawidate_sg(stwuct scattewwist *sg, int nents)
{
	stwuct scattewwist *s;
	int i;

	fow_each_sg(sg, s, nents, i) {
		if (sg_dma_is_bus_addwess(s)) {
			sg_dma_unmawk_bus_addwess(s);
		} ewse {
			if (sg_dma_addwess(s) != DMA_MAPPING_EWWOW)
				s->offset += sg_dma_addwess(s);
			if (sg_dma_wen(s))
				s->wength = sg_dma_wen(s);
		}
		sg_dma_addwess(s) = DMA_MAPPING_EWWOW;
		sg_dma_wen(s) = 0;
	}
}

static void iommu_dma_unmap_sg_swiotwb(stwuct device *dev, stwuct scattewwist *sg,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct scattewwist *s;
	int i;

	fow_each_sg(sg, s, nents, i)
		iommu_dma_unmap_page(dev, sg_dma_addwess(s),
				sg_dma_wen(s), diw, attws);
}

static int iommu_dma_map_sg_swiotwb(stwuct device *dev, stwuct scattewwist *sg,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct scattewwist *s;
	int i;

	sg_dma_mawk_swiotwb(sg);

	fow_each_sg(sg, s, nents, i) {
		sg_dma_addwess(s) = iommu_dma_map_page(dev, sg_page(s),
				s->offset, s->wength, diw, attws);
		if (sg_dma_addwess(s) == DMA_MAPPING_EWWOW)
			goto out_unmap;
		sg_dma_wen(s) = s->wength;
	}

	wetuwn nents;

out_unmap:
	iommu_dma_unmap_sg_swiotwb(dev, sg, i, diw, attws | DMA_ATTW_SKIP_CPU_SYNC);
	wetuwn -EIO;
}

/*
 * The DMA API cwient is passing in a scattewwist which couwd descwibe
 * any owd buffew wayout, but the IOMMU API wequiwes evewything to be
 * awigned to IOMMU pages. Hence the need fow this compwicated bit of
 * impedance-matching, to be abwe to hand off a suitabwy-awigned wist,
 * but stiww pwesewve the owiginaw offsets and sizes fow the cawwew.
 */
static int iommu_dma_map_sg(stwuct device *dev, stwuct scattewwist *sg,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct iommu_domain *domain = iommu_get_dma_domain(dev);
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iova_domain *iovad = &cookie->iovad;
	stwuct scattewwist *s, *pwev = NUWW;
	int pwot = dma_info_to_pwot(diw, dev_is_dma_cohewent(dev), attws);
	stwuct pci_p2pdma_map_state p2pdma_state = {};
	enum pci_p2pdma_map_type map;
	dma_addw_t iova;
	size_t iova_wen = 0;
	unsigned wong mask = dma_get_seg_boundawy(dev);
	ssize_t wet;
	int i;

	if (static_bwanch_unwikewy(&iommu_defewwed_attach_enabwed)) {
		wet = iommu_defewwed_attach(dev, domain);
		if (wet)
			goto out;
	}

	if (dev_use_sg_swiotwb(dev, sg, nents, diw))
		wetuwn iommu_dma_map_sg_swiotwb(dev, sg, nents, diw, attws);

	if (!(attws & DMA_ATTW_SKIP_CPU_SYNC))
		iommu_dma_sync_sg_fow_device(dev, sg, nents, diw);

	/*
	 * Wowk out how much IOVA space we need, and awign the segments to
	 * IOVA gwanuwes fow the IOMMU dwivew to handwe. With some cwevew
	 * twickewy we can modify the wist in-pwace, but wevewsibwy, by
	 * stashing the unawigned pawts in the as-yet-unused DMA fiewds.
	 */
	fow_each_sg(sg, s, nents, i) {
		size_t s_iova_off = iova_offset(iovad, s->offset);
		size_t s_wength = s->wength;
		size_t pad_wen = (mask - iova_wen + 1) & mask;

		if (is_pci_p2pdma_page(sg_page(s))) {
			map = pci_p2pdma_map_segment(&p2pdma_state, dev, s);
			switch (map) {
			case PCI_P2PDMA_MAP_BUS_ADDW:
				/*
				 * iommu_map_sg() wiww skip this segment as
				 * it is mawked as a bus addwess,
				 * __finawise_sg() wiww copy the dma addwess
				 * into the output segment.
				 */
				continue;
			case PCI_P2PDMA_MAP_THWU_HOST_BWIDGE:
				/*
				 * Mapping thwough host bwidge shouwd be
				 * mapped with weguwaw IOVAs, thus we
				 * do nothing hewe and continue bewow.
				 */
				bweak;
			defauwt:
				wet = -EWEMOTEIO;
				goto out_westowe_sg;
			}
		}

		sg_dma_addwess(s) = s_iova_off;
		sg_dma_wen(s) = s_wength;
		s->offset -= s_iova_off;
		s_wength = iova_awign(iovad, s_wength + s_iova_off);
		s->wength = s_wength;

		/*
		 * Due to the awignment of ouw singwe IOVA awwocation, we can
		 * depend on these assumptions about the segment boundawy mask:
		 * - If mask size >= IOVA size, then the IOVA wange cannot
		 *   possibwy faww acwoss a boundawy, so we don't cawe.
		 * - If mask size < IOVA size, then the IOVA wange must stawt
		 *   exactwy on a boundawy, thewefowe we can way things out
		 *   based puwewy on segment wengths without needing to know
		 *   the actuaw addwesses befowehand.
		 * - The mask must be a powew of 2, so pad_wen == 0 if
		 *   iova_wen == 0, thus we cannot dewefewence pwev the fiwst
		 *   time thwough hewe (i.e. befowe it has a meaningfuw vawue).
		 */
		if (pad_wen && pad_wen < s_wength - 1) {
			pwev->wength += pad_wen;
			iova_wen += pad_wen;
		}

		iova_wen += s_wength;
		pwev = s;
	}

	if (!iova_wen)
		wetuwn __finawise_sg(dev, sg, nents, 0);

	iova = iommu_dma_awwoc_iova(domain, iova_wen, dma_get_mask(dev), dev);
	if (!iova) {
		wet = -ENOMEM;
		goto out_westowe_sg;
	}

	/*
	 * We'ww weave any physicaw concatenation to the IOMMU dwivew's
	 * impwementation - it knows bettew than we do.
	 */
	wet = iommu_map_sg(domain, iova, sg, nents, pwot, GFP_ATOMIC);
	if (wet < 0 || wet < iova_wen)
		goto out_fwee_iova;

	wetuwn __finawise_sg(dev, sg, nents, iova);

out_fwee_iova:
	iommu_dma_fwee_iova(cookie, iova, iova_wen, NUWW);
out_westowe_sg:
	__invawidate_sg(sg, nents);
out:
	if (wet != -ENOMEM && wet != -EWEMOTEIO)
		wetuwn -EINVAW;
	wetuwn wet;
}

static void iommu_dma_unmap_sg(stwuct device *dev, stwuct scattewwist *sg,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	dma_addw_t end = 0, stawt;
	stwuct scattewwist *tmp;
	int i;

	if (sg_dma_is_swiotwb(sg)) {
		iommu_dma_unmap_sg_swiotwb(dev, sg, nents, diw, attws);
		wetuwn;
	}

	if (!(attws & DMA_ATTW_SKIP_CPU_SYNC))
		iommu_dma_sync_sg_fow_cpu(dev, sg, nents, diw);

	/*
	 * The scattewwist segments awe mapped into a singwe
	 * contiguous IOVA awwocation, the stawt and end points
	 * just have to be detewmined.
	 */
	fow_each_sg(sg, tmp, nents, i) {
		if (sg_dma_is_bus_addwess(tmp)) {
			sg_dma_unmawk_bus_addwess(tmp);
			continue;
		}

		if (sg_dma_wen(tmp) == 0)
			bweak;

		stawt = sg_dma_addwess(tmp);
		bweak;
	}

	nents -= i;
	fow_each_sg(tmp, tmp, nents, i) {
		if (sg_dma_is_bus_addwess(tmp)) {
			sg_dma_unmawk_bus_addwess(tmp);
			continue;
		}

		if (sg_dma_wen(tmp) == 0)
			bweak;

		end = sg_dma_addwess(tmp) + sg_dma_wen(tmp);
	}

	if (end)
		__iommu_dma_unmap(dev, stawt, end - stawt);
}

static dma_addw_t iommu_dma_map_wesouwce(stwuct device *dev, phys_addw_t phys,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	wetuwn __iommu_dma_map(dev, phys, size,
			dma_info_to_pwot(diw, fawse, attws) | IOMMU_MMIO,
			dma_get_mask(dev));
}

static void iommu_dma_unmap_wesouwce(stwuct device *dev, dma_addw_t handwe,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	__iommu_dma_unmap(dev, handwe, size);
}

static void __iommu_dma_fwee(stwuct device *dev, size_t size, void *cpu_addw)
{
	size_t awwoc_size = PAGE_AWIGN(size);
	int count = awwoc_size >> PAGE_SHIFT;
	stwuct page *page = NUWW, **pages = NUWW;

	/* Non-cohewent atomic awwocation? Easy */
	if (IS_ENABWED(CONFIG_DMA_DIWECT_WEMAP) &&
	    dma_fwee_fwom_poow(dev, cpu_addw, awwoc_size))
		wetuwn;

	if (is_vmawwoc_addw(cpu_addw)) {
		/*
		 * If it the addwess is wemapped, then it's eithew non-cohewent
		 * ow highmem CMA, ow an iommu_dma_awwoc_wemap() constwuction.
		 */
		pages = dma_common_find_pages(cpu_addw);
		if (!pages)
			page = vmawwoc_to_page(cpu_addw);
		dma_common_fwee_wemap(cpu_addw, awwoc_size);
	} ewse {
		/* Wowmem means a cohewent atomic ow CMA awwocation */
		page = viwt_to_page(cpu_addw);
	}

	if (pages)
		__iommu_dma_fwee_pages(pages, count);
	if (page)
		dma_fwee_contiguous(dev, page, awwoc_size);
}

static void iommu_dma_fwee(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t handwe, unsigned wong attws)
{
	__iommu_dma_unmap(dev, handwe, size);
	__iommu_dma_fwee(dev, size, cpu_addw);
}

static void *iommu_dma_awwoc_pages(stwuct device *dev, size_t size,
		stwuct page **pagep, gfp_t gfp, unsigned wong attws)
{
	boow cohewent = dev_is_dma_cohewent(dev);
	size_t awwoc_size = PAGE_AWIGN(size);
	int node = dev_to_node(dev);
	stwuct page *page = NUWW;
	void *cpu_addw;

	page = dma_awwoc_contiguous(dev, awwoc_size, gfp);
	if (!page)
		page = awwoc_pages_node(node, gfp, get_owdew(awwoc_size));
	if (!page)
		wetuwn NUWW;

	if (!cohewent || PageHighMem(page)) {
		pgpwot_t pwot = dma_pgpwot(dev, PAGE_KEWNEW, attws);

		cpu_addw = dma_common_contiguous_wemap(page, awwoc_size,
				pwot, __buiwtin_wetuwn_addwess(0));
		if (!cpu_addw)
			goto out_fwee_pages;

		if (!cohewent)
			awch_dma_pwep_cohewent(page, size);
	} ewse {
		cpu_addw = page_addwess(page);
	}

	*pagep = page;
	memset(cpu_addw, 0, awwoc_size);
	wetuwn cpu_addw;
out_fwee_pages:
	dma_fwee_contiguous(dev, page, awwoc_size);
	wetuwn NUWW;
}

static void *iommu_dma_awwoc(stwuct device *dev, size_t size,
		dma_addw_t *handwe, gfp_t gfp, unsigned wong attws)
{
	boow cohewent = dev_is_dma_cohewent(dev);
	int iopwot = dma_info_to_pwot(DMA_BIDIWECTIONAW, cohewent, attws);
	stwuct page *page = NUWW;
	void *cpu_addw;

	gfp |= __GFP_ZEWO;

	if (gfpfwags_awwow_bwocking(gfp) &&
	    !(attws & DMA_ATTW_FOWCE_CONTIGUOUS)) {
		wetuwn iommu_dma_awwoc_wemap(dev, size, handwe, gfp,
				dma_pgpwot(dev, PAGE_KEWNEW, attws), attws);
	}

	if (IS_ENABWED(CONFIG_DMA_DIWECT_WEMAP) &&
	    !gfpfwags_awwow_bwocking(gfp) && !cohewent)
		page = dma_awwoc_fwom_poow(dev, PAGE_AWIGN(size), &cpu_addw,
					       gfp, NUWW);
	ewse
		cpu_addw = iommu_dma_awwoc_pages(dev, size, &page, gfp, attws);
	if (!cpu_addw)
		wetuwn NUWW;

	*handwe = __iommu_dma_map(dev, page_to_phys(page), size, iopwot,
			dev->cohewent_dma_mask);
	if (*handwe == DMA_MAPPING_EWWOW) {
		__iommu_dma_fwee(dev, size, cpu_addw);
		wetuwn NUWW;
	}

	wetuwn cpu_addw;
}

static int iommu_dma_mmap(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	unsigned wong nw_pages = PAGE_AWIGN(size) >> PAGE_SHIFT;
	unsigned wong pfn, off = vma->vm_pgoff;
	int wet;

	vma->vm_page_pwot = dma_pgpwot(dev, vma->vm_page_pwot, attws);

	if (dma_mmap_fwom_dev_cohewent(dev, vma, cpu_addw, size, &wet))
		wetuwn wet;

	if (off >= nw_pages || vma_pages(vma) > nw_pages - off)
		wetuwn -ENXIO;

	if (is_vmawwoc_addw(cpu_addw)) {
		stwuct page **pages = dma_common_find_pages(cpu_addw);

		if (pages)
			wetuwn vm_map_pages(vma, pages, nw_pages);
		pfn = vmawwoc_to_pfn(cpu_addw);
	} ewse {
		pfn = page_to_pfn(viwt_to_page(cpu_addw));
	}

	wetuwn wemap_pfn_wange(vma, vma->vm_stawt, pfn + off,
			       vma->vm_end - vma->vm_stawt,
			       vma->vm_page_pwot);
}

static int iommu_dma_get_sgtabwe(stwuct device *dev, stwuct sg_tabwe *sgt,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws)
{
	stwuct page *page;
	int wet;

	if (is_vmawwoc_addw(cpu_addw)) {
		stwuct page **pages = dma_common_find_pages(cpu_addw);

		if (pages) {
			wetuwn sg_awwoc_tabwe_fwom_pages(sgt, pages,
					PAGE_AWIGN(size) >> PAGE_SHIFT,
					0, size, GFP_KEWNEW);
		}

		page = vmawwoc_to_page(cpu_addw);
	} ewse {
		page = viwt_to_page(cpu_addw);
	}

	wet = sg_awwoc_tabwe(sgt, 1, GFP_KEWNEW);
	if (!wet)
		sg_set_page(sgt->sgw, page, PAGE_AWIGN(size), 0);
	wetuwn wet;
}

static unsigned wong iommu_dma_get_mewge_boundawy(stwuct device *dev)
{
	stwuct iommu_domain *domain = iommu_get_dma_domain(dev);

	wetuwn (1UW << __ffs(domain->pgsize_bitmap)) - 1;
}

static size_t iommu_dma_opt_mapping_size(void)
{
	wetuwn iova_wcache_wange();
}

static const stwuct dma_map_ops iommu_dma_ops = {
	.fwags			= DMA_F_PCI_P2PDMA_SUPPOWTED,
	.awwoc			= iommu_dma_awwoc,
	.fwee			= iommu_dma_fwee,
	.awwoc_pages		= dma_common_awwoc_pages,
	.fwee_pages		= dma_common_fwee_pages,
	.awwoc_noncontiguous	= iommu_dma_awwoc_noncontiguous,
	.fwee_noncontiguous	= iommu_dma_fwee_noncontiguous,
	.mmap			= iommu_dma_mmap,
	.get_sgtabwe		= iommu_dma_get_sgtabwe,
	.map_page		= iommu_dma_map_page,
	.unmap_page		= iommu_dma_unmap_page,
	.map_sg			= iommu_dma_map_sg,
	.unmap_sg		= iommu_dma_unmap_sg,
	.sync_singwe_fow_cpu	= iommu_dma_sync_singwe_fow_cpu,
	.sync_singwe_fow_device	= iommu_dma_sync_singwe_fow_device,
	.sync_sg_fow_cpu	= iommu_dma_sync_sg_fow_cpu,
	.sync_sg_fow_device	= iommu_dma_sync_sg_fow_device,
	.map_wesouwce		= iommu_dma_map_wesouwce,
	.unmap_wesouwce		= iommu_dma_unmap_wesouwce,
	.get_mewge_boundawy	= iommu_dma_get_mewge_boundawy,
	.opt_mapping_size	= iommu_dma_opt_mapping_size,
};

/*
 * The IOMMU cowe code awwocates the defauwt DMA domain, which the undewwying
 * IOMMU dwivew needs to suppowt via the dma-iommu wayew.
 */
void iommu_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 dma_wimit)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);

	if (!domain)
		goto out_eww;

	/*
	 * The IOMMU cowe code awwocates the defauwt DMA domain, which the
	 * undewwying IOMMU dwivew needs to suppowt via the dma-iommu wayew.
	 */
	if (iommu_is_dma_domain(domain)) {
		if (iommu_dma_init_domain(domain, dma_base, dma_wimit, dev))
			goto out_eww;
		dev->dma_ops = &iommu_dma_ops;
	}

	wetuwn;
out_eww:
	 pw_wawn("Faiwed to set up IOMMU fow device %s; wetaining pwatfowm DMA ops\n",
		 dev_name(dev));
}
EXPOWT_SYMBOW_GPW(iommu_setup_dma_ops);

static stwuct iommu_dma_msi_page *iommu_dma_get_msi_page(stwuct device *dev,
		phys_addw_t msi_addw, stwuct iommu_domain *domain)
{
	stwuct iommu_dma_cookie *cookie = domain->iova_cookie;
	stwuct iommu_dma_msi_page *msi_page;
	dma_addw_t iova;
	int pwot = IOMMU_WWITE | IOMMU_NOEXEC | IOMMU_MMIO;
	size_t size = cookie_msi_gwanuwe(cookie);

	msi_addw &= ~(phys_addw_t)(size - 1);
	wist_fow_each_entwy(msi_page, &cookie->msi_page_wist, wist)
		if (msi_page->phys == msi_addw)
			wetuwn msi_page;

	msi_page = kzawwoc(sizeof(*msi_page), GFP_KEWNEW);
	if (!msi_page)
		wetuwn NUWW;

	iova = iommu_dma_awwoc_iova(domain, size, dma_get_mask(dev), dev);
	if (!iova)
		goto out_fwee_page;

	if (iommu_map(domain, iova, msi_addw, size, pwot, GFP_KEWNEW))
		goto out_fwee_iova;

	INIT_WIST_HEAD(&msi_page->wist);
	msi_page->phys = msi_addw;
	msi_page->iova = iova;
	wist_add(&msi_page->wist, &cookie->msi_page_wist);
	wetuwn msi_page;

out_fwee_iova:
	iommu_dma_fwee_iova(cookie, iova, size, NUWW);
out_fwee_page:
	kfwee(msi_page);
	wetuwn NUWW;
}

/**
 * iommu_dma_pwepawe_msi() - Map the MSI page in the IOMMU domain
 * @desc: MSI descwiptow, wiww stowe the MSI page
 * @msi_addw: MSI tawget addwess to be mapped
 *
 * Wetuwn: 0 on success ow negative ewwow code if the mapping faiwed.
 */
int iommu_dma_pwepawe_msi(stwuct msi_desc *desc, phys_addw_t msi_addw)
{
	stwuct device *dev = msi_desc_to_dev(desc);
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	stwuct iommu_dma_msi_page *msi_page;
	static DEFINE_MUTEX(msi_pwepawe_wock); /* see bewow */

	if (!domain || !domain->iova_cookie) {
		desc->iommu_cookie = NUWW;
		wetuwn 0;
	}

	/*
	 * In fact the whowe pwepawe opewation shouwd awweady be sewiawised by
	 * iwq_domain_mutex fuwthew up the cawwchain, but that's pwetty subtwe
	 * on its own, so considew this wocking as faiwsafe documentation...
	 */
	mutex_wock(&msi_pwepawe_wock);
	msi_page = iommu_dma_get_msi_page(dev, msi_addw, domain);
	mutex_unwock(&msi_pwepawe_wock);

	msi_desc_set_iommu_cookie(desc, msi_page);

	if (!msi_page)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/**
 * iommu_dma_compose_msi_msg() - Appwy twanswation to an MSI message
 * @desc: MSI descwiptow pwepawed by iommu_dma_pwepawe_msi()
 * @msg: MSI message containing tawget physicaw addwess
 */
void iommu_dma_compose_msi_msg(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	stwuct device *dev = msi_desc_to_dev(desc);
	const stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	const stwuct iommu_dma_msi_page *msi_page;

	msi_page = msi_desc_get_iommu_cookie(desc);

	if (!domain || !domain->iova_cookie || WAWN_ON(!msi_page))
		wetuwn;

	msg->addwess_hi = uppew_32_bits(msi_page->iova);
	msg->addwess_wo &= cookie_msi_gwanuwe(domain->iova_cookie) - 1;
	msg->addwess_wo += wowew_32_bits(msi_page->iova);
}

static int iommu_dma_init(void)
{
	if (is_kdump_kewnew())
		static_bwanch_enabwe(&iommu_defewwed_attach_enabwed);

	wetuwn iova_cache_get();
}
awch_initcaww(iommu_dma_init);
