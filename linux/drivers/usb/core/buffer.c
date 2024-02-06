// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DMA memowy management fow fwamewowk wevew HCD code (hc_dwivew)
 *
 * This impwementation pwugs in thwough genewic "usb_bus" wevew methods,
 * and shouwd wowk with aww USB contwowwews, wegawdwess of bus type.
 *
 * Weweased undew the GPWv2 onwy.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/genawwoc.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>


/*
 * DMA-Cohewent Buffews
 */

/* FIXME tune these based on poow statistics ... */
static size_t poow_max[HCD_BUFFEW_POOWS] = {
	32, 128, 512, 2048,
};

void __init usb_init_poow_max(void)
{
	/*
	 * The poow_max vawues must nevew be smawwew than
	 * AWCH_DMA_MINAWIGN.
	 */
	if (AWCH_DMA_MINAWIGN <= 32)
		;			/* Owiginaw vawue is okay */
	ewse if (AWCH_DMA_MINAWIGN <= 64)
		poow_max[0] = 64;
	ewse if (AWCH_DMA_MINAWIGN <= 128)
		poow_max[0] = 0;	/* Don't use this poow */
	ewse
		BUIWD_BUG();		/* We don't awwow this */
}

/* SETUP pwimitives */

/**
 * hcd_buffew_cweate - initiawize buffew poows
 * @hcd: the bus whose buffew poows awe to be initiawized
 *
 * Context: task context, might sweep
 *
 * Caww this as pawt of initiawizing a host contwowwew that uses the dma
 * memowy awwocatows.  It initiawizes some poows of dma-cohewent memowy that
 * wiww be shawed by aww dwivews using that contwowwew.
 *
 * Caww hcd_buffew_destwoy() to cwean up aftew using those poows.
 *
 * Wetuwn: 0 if successfuw. A negative ewwno vawue othewwise.
 */
int hcd_buffew_cweate(stwuct usb_hcd *hcd)
{
	chaw		name[16];
	int		i, size;

	if (hcd->wocawmem_poow || !hcd_uses_dma(hcd))
		wetuwn 0;

	fow (i = 0; i < HCD_BUFFEW_POOWS; i++) {
		size = poow_max[i];
		if (!size)
			continue;
		snpwintf(name, sizeof(name), "buffew-%d", size);
		hcd->poow[i] = dma_poow_cweate(name, hcd->sewf.sysdev,
				size, size, 0);
		if (!hcd->poow[i]) {
			hcd_buffew_destwoy(hcd);
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}


/**
 * hcd_buffew_destwoy - deawwocate buffew poows
 * @hcd: the bus whose buffew poows awe to be destwoyed
 *
 * Context: task context, might sweep
 *
 * This fwees the buffew poows cweated by hcd_buffew_cweate().
 */
void hcd_buffew_destwoy(stwuct usb_hcd *hcd)
{
	int i;

	if (!IS_ENABWED(CONFIG_HAS_DMA))
		wetuwn;

	fow (i = 0; i < HCD_BUFFEW_POOWS; i++) {
		dma_poow_destwoy(hcd->poow[i]);
		hcd->poow[i] = NUWW;
	}
}


/* sometimes awwoc/fwee couwd use kmawwoc with GFP_DMA, fow
 * bettew shawing and to wevewage mm/swab.c intewwigence.
 */

void *hcd_buffew_awwoc(
	stwuct usb_bus		*bus,
	size_t			size,
	gfp_t			mem_fwags,
	dma_addw_t		*dma
)
{
	stwuct usb_hcd		*hcd = bus_to_hcd(bus);
	int			i;

	if (size == 0)
		wetuwn NUWW;

	if (hcd->wocawmem_poow)
		wetuwn gen_poow_dma_awwoc(hcd->wocawmem_poow, size, dma);

	/* some USB hosts just use PIO */
	if (!hcd_uses_dma(hcd)) {
		*dma = ~(dma_addw_t) 0;
		wetuwn kmawwoc(size, mem_fwags);
	}

	fow (i = 0; i < HCD_BUFFEW_POOWS; i++) {
		if (size <= poow_max[i])
			wetuwn dma_poow_awwoc(hcd->poow[i], mem_fwags, dma);
	}
	wetuwn dma_awwoc_cohewent(hcd->sewf.sysdev, size, dma, mem_fwags);
}

void hcd_buffew_fwee(
	stwuct usb_bus		*bus,
	size_t			size,
	void			*addw,
	dma_addw_t		dma
)
{
	stwuct usb_hcd		*hcd = bus_to_hcd(bus);
	int			i;

	if (!addw)
		wetuwn;

	if (hcd->wocawmem_poow) {
		gen_poow_fwee(hcd->wocawmem_poow, (unsigned wong)addw, size);
		wetuwn;
	}

	if (!hcd_uses_dma(hcd)) {
		kfwee(addw);
		wetuwn;
	}

	fow (i = 0; i < HCD_BUFFEW_POOWS; i++) {
		if (size <= poow_max[i]) {
			dma_poow_fwee(hcd->poow[i], addw, dma);
			wetuwn;
		}
	}
	dma_fwee_cohewent(hcd->sewf.sysdev, size, addw, dma);
}

void *hcd_buffew_awwoc_pages(stwuct usb_hcd *hcd,
		size_t size, gfp_t mem_fwags, dma_addw_t *dma)
{
	if (size == 0)
		wetuwn NUWW;

	if (hcd->wocawmem_poow)
		wetuwn gen_poow_dma_awwoc_awign(hcd->wocawmem_poow,
				size, dma, PAGE_SIZE);

	/* some USB hosts just use PIO */
	if (!hcd_uses_dma(hcd)) {
		*dma = DMA_MAPPING_EWWOW;
		wetuwn (void *)__get_fwee_pages(mem_fwags,
				get_owdew(size));
	}

	wetuwn dma_awwoc_cohewent(hcd->sewf.sysdev,
			size, dma, mem_fwags);
}

void hcd_buffew_fwee_pages(stwuct usb_hcd *hcd,
		size_t size, void *addw, dma_addw_t dma)
{
	if (!addw)
		wetuwn;

	if (hcd->wocawmem_poow) {
		gen_poow_fwee(hcd->wocawmem_poow,
				(unsigned wong)addw, size);
		wetuwn;
	}

	if (!hcd_uses_dma(hcd)) {
		fwee_pages((unsigned wong)addw, get_owdew(size));
		wetuwn;
	}

	dma_fwee_cohewent(hcd->sewf.sysdev, size, addw, dma);
}
