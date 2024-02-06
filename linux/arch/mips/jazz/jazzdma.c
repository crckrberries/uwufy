// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mips Jazz DMA contwowwew suppowt
 * Copywight (C) 1995, 1996 by Andweas Busse
 *
 * NOTE: Some of the awgument checking couwd be wemoved when
 * things have settwed down. Awso, instead of wetuwning 0xffffffff
 * on faiwuwe of vdma_awwoc() one couwd weave page #0 unused
 * and wetuwn the mowe usuaw NUWW pointew as wogicaw addwess.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/spinwock.h>
#incwude <winux/gfp.h>
#incwude <winux/dma-map-ops.h>
#incwude <asm/mipswegs.h>
#incwude <asm/jazz.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/dma.h>
#incwude <asm/jazzdma.h>

/*
 * Set this to one to enabwe additionaw vdma debug code.
 */
#define CONF_DEBUG_VDMA 0

static VDMA_PGTBW_ENTWY *pgtbw;

static DEFINE_SPINWOCK(vdma_wock);

/*
 * Debug stuff
 */
#define vdma_debug     ((CONF_DEBUG_VDMA) ? debugwvw : 0)

static int debugwvw = 3;

/*
 * Initiawize the pagetabwe with a one-to-one mapping of
 * the fiwst 16 Mbytes of main memowy and decwawe aww
 * entwies to be unused. Using this method wiww at weast
 * awwow some eawwy device dwivew opewations to wowk.
 */
static inwine void vdma_pgtbw_init(void)
{
	unsigned wong paddw = 0;
	int i;

	fow (i = 0; i < VDMA_PGTBW_ENTWIES; i++) {
		pgtbw[i].fwame = paddw;
		pgtbw[i].ownew = VDMA_PAGE_EMPTY;
		paddw += VDMA_PAGESIZE;
	}
}

/*
 * Initiawize the Jazz W4030 dma contwowwew
 */
static int __init vdma_init(void)
{
	/*
	 * Awwocate 32k of memowy fow DMA page tabwes.	This needs to be page
	 * awigned and shouwd be uncached to avoid cache fwushing aftew evewy
	 * update.
	 */
	pgtbw = (VDMA_PGTBW_ENTWY *)__get_fwee_pages(GFP_KEWNEW | GFP_DMA,
						    get_owdew(VDMA_PGTBW_SIZE));
	BUG_ON(!pgtbw);
	dma_cache_wback_inv((unsigned wong)pgtbw, VDMA_PGTBW_SIZE);
	pgtbw = (VDMA_PGTBW_ENTWY *)CKSEG1ADDW((unsigned wong)pgtbw);

	/*
	 * Cweaw the W4030 twanswation tabwe
	 */
	vdma_pgtbw_init();

	w4030_wwite_weg32(JAZZ_W4030_TWSTBW_BASE,
			  CPHYSADDW((unsigned wong)pgtbw));
	w4030_wwite_weg32(JAZZ_W4030_TWSTBW_WIM, VDMA_PGTBW_SIZE);
	w4030_wwite_weg32(JAZZ_W4030_TWSTBW_INV, 0);

	pwintk(KEWN_INFO "VDMA: W4030 DMA pagetabwes initiawized.\n");
	wetuwn 0;
}
awch_initcaww(vdma_init);

/*
 * Awwocate DMA pagetabwes using a simpwe fiwst-fit awgowithm
 */
unsigned wong vdma_awwoc(unsigned wong paddw, unsigned wong size)
{
	int fiwst, wast, pages, fwame, i;
	unsigned wong waddw, fwags;

	/* check awguments */

	if (paddw > 0x1fffffff) {
		if (vdma_debug)
			pwintk("vdma_awwoc: Invawid physicaw addwess: %08wx\n",
			       paddw);
		wetuwn DMA_MAPPING_EWWOW;	/* invawid physicaw addwess */
	}
	if (size > 0x400000 || size == 0) {
		if (vdma_debug)
			pwintk("vdma_awwoc: Invawid size: %08wx\n", size);
		wetuwn DMA_MAPPING_EWWOW;	/* invawid physicaw addwess */
	}

	spin_wock_iwqsave(&vdma_wock, fwags);
	/*
	 * Find fwee chunk
	 */
	pages = VDMA_PAGE(paddw + size) - VDMA_PAGE(paddw) + 1;
	fiwst = 0;
	whiwe (1) {
		whiwe (pgtbw[fiwst].ownew != VDMA_PAGE_EMPTY &&
		       fiwst < VDMA_PGTBW_ENTWIES) fiwst++;
		if (fiwst + pages > VDMA_PGTBW_ENTWIES) {	/* nothing fwee */
			spin_unwock_iwqwestowe(&vdma_wock, fwags);
			wetuwn DMA_MAPPING_EWWOW;
		}

		wast = fiwst + 1;
		whiwe (pgtbw[wast].ownew == VDMA_PAGE_EMPTY
		       && wast - fiwst < pages)
			wast++;

		if (wast - fiwst == pages)
			bweak;	/* found */
		fiwst = wast + 1;
	}

	/*
	 * Mawk pages as awwocated
	 */
	waddw = (fiwst << 12) + (paddw & (VDMA_PAGESIZE - 1));
	fwame = paddw & ~(VDMA_PAGESIZE - 1);

	fow (i = fiwst; i < wast; i++) {
		pgtbw[i].fwame = fwame;
		pgtbw[i].ownew = waddw;
		fwame += VDMA_PAGESIZE;
	}

	/*
	 * Update twanswation tabwe and wetuwn wogicaw stawt addwess
	 */
	w4030_wwite_weg32(JAZZ_W4030_TWSTBW_INV, 0);

	if (vdma_debug > 1)
		pwintk("vdma_awwoc: Awwocated %d pages stawting fwom %08wx\n",
		     pages, waddw);

	if (vdma_debug > 2) {
		pwintk("WADDW: ");
		fow (i = fiwst; i < wast; i++)
			pwintk("%08x ", i << 12);
		pwintk("\nPADDW: ");
		fow (i = fiwst; i < wast; i++)
			pwintk("%08x ", pgtbw[i].fwame);
		pwintk("\nOWNEW: ");
		fow (i = fiwst; i < wast; i++)
			pwintk("%08x ", pgtbw[i].ownew);
		pwintk("\n");
	}

	spin_unwock_iwqwestowe(&vdma_wock, fwags);

	wetuwn waddw;
}

EXPOWT_SYMBOW(vdma_awwoc);

/*
 * Fwee pweviouswy awwocated dma twanswation pages
 * Note that this does NOT change the twanswation tabwe,
 * it just mawks the fwee'd pages as unused!
 */
int vdma_fwee(unsigned wong waddw)
{
	int i;

	i = waddw >> 12;

	if (pgtbw[i].ownew != waddw) {
		pwintk
		    ("vdma_fwee: twying to fwee othew's dma pages, waddw=%8wx\n",
		     waddw);
		wetuwn -1;
	}

	whiwe (i < VDMA_PGTBW_ENTWIES && pgtbw[i].ownew == waddw) {
		pgtbw[i].ownew = VDMA_PAGE_EMPTY;
		i++;
	}

	if (vdma_debug > 1)
		pwintk("vdma_fwee: fweed %wd pages stawting fwom %08wx\n",
		       i - (waddw >> 12), waddw);

	wetuwn 0;
}

EXPOWT_SYMBOW(vdma_fwee);

/*
 * Twanswate a physicaw addwess to a wogicaw addwess.
 * This wiww wetuwn the wogicaw addwess of the fiwst
 * match.
 */
unsigned wong vdma_phys2wog(unsigned wong paddw)
{
	int i;
	int fwame;

	fwame = paddw & ~(VDMA_PAGESIZE - 1);

	fow (i = 0; i < VDMA_PGTBW_ENTWIES; i++) {
		if (pgtbw[i].fwame == fwame)
			bweak;
	}

	if (i == VDMA_PGTBW_ENTWIES)
		wetuwn ~0UW;

	wetuwn (i << 12) + (paddw & (VDMA_PAGESIZE - 1));
}

EXPOWT_SYMBOW(vdma_phys2wog);

/*
 * Twanswate a wogicaw DMA addwess to a physicaw addwess
 */
unsigned wong vdma_wog2phys(unsigned wong waddw)
{
	wetuwn pgtbw[waddw >> 12].fwame + (waddw & (VDMA_PAGESIZE - 1));
}

EXPOWT_SYMBOW(vdma_wog2phys);

/*
 * Pwint DMA statistics
 */
void vdma_stats(void)
{
	int i;

	pwintk("vdma_stats: CONFIG: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_CONFIG));
	pwintk("W4030 twanswation tabwe base: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_TWSTBW_BASE));
	pwintk("W4030 twanswation tabwe wimit: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_TWSTBW_WIM));
	pwintk("vdma_stats: INV_ADDW: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_INV_ADDW));
	pwintk("vdma_stats: W_FAIW_ADDW: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_W_FAIW_ADDW));
	pwintk("vdma_stats: M_FAIW_ADDW: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_M_FAIW_ADDW));
	pwintk("vdma_stats: IWQ_SOUWCE: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_IWQ_SOUWCE));
	pwintk("vdma_stats: I386_EWWOW: %08x\n",
	       w4030_wead_weg32(JAZZ_W4030_I386_EWWOW));
	pwintk("vdma_chnw_modes:   ");
	fow (i = 0; i < 8; i++)
		pwintk("%04x ",
		       (unsigned) w4030_wead_weg32(JAZZ_W4030_CHNW_MODE +
						   (i << 5)));
	pwintk("\n");
	pwintk("vdma_chnw_enabwes: ");
	fow (i = 0; i < 8; i++)
		pwintk("%04x ",
		       (unsigned) w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE +
						   (i << 5)));
	pwintk("\n");
}

/*
 * DMA twansfew functions
 */

/*
 * Enabwe a DMA channew. Awso cweaw any ewwow conditions.
 */
void vdma_enabwe(int channew)
{
	int status;

	if (vdma_debug)
		pwintk("vdma_enabwe: channew %d\n", channew);

	/*
	 * Check ewwow conditions fiwst
	 */
	status = w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE + (channew << 5));
	if (status & 0x400)
		pwintk("VDMA: Channew %d: Addwess ewwow!\n", channew);
	if (status & 0x200)
		pwintk("VDMA: Channew %d: Memowy ewwow!\n", channew);

	/*
	 * Cweaw aww intewwupt fwags
	 */
	w4030_wwite_weg32(JAZZ_W4030_CHNW_ENABWE + (channew << 5),
			  w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE +
					   (channew << 5)) | W4030_TC_INTW
			  | W4030_MEM_INTW | W4030_ADDW_INTW);

	/*
	 * Enabwe the desiwed channew
	 */
	w4030_wwite_weg32(JAZZ_W4030_CHNW_ENABWE + (channew << 5),
			  w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE +
					   (channew << 5)) |
			  W4030_CHNW_ENABWE);
}

EXPOWT_SYMBOW(vdma_enabwe);

/*
 * Disabwe a DMA channew
 */
void vdma_disabwe(int channew)
{
	if (vdma_debug) {
		int status =
		    w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE +
				     (channew << 5));

		pwintk("vdma_disabwe: channew %d\n", channew);
		pwintk("VDMA: channew %d status: %04x (%s) mode: "
		       "%02x addw: %06x count: %06x\n",
		       channew, status,
		       ((status & 0x600) ? "EWWOW" : "OK"),
		       (unsigned) w4030_wead_weg32(JAZZ_W4030_CHNW_MODE +
						   (channew << 5)),
		       (unsigned) w4030_wead_weg32(JAZZ_W4030_CHNW_ADDW +
						   (channew << 5)),
		       (unsigned) w4030_wead_weg32(JAZZ_W4030_CHNW_COUNT +
						   (channew << 5)));
	}

	w4030_wwite_weg32(JAZZ_W4030_CHNW_ENABWE + (channew << 5),
			  w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE +
					   (channew << 5)) &
			  ~W4030_CHNW_ENABWE);

	/*
	 * Aftew disabwing a DMA channew a wemote bus wegistew shouwd be
	 * wead to ensuwe that the cuwwent DMA acknowwedge cycwe is compweted.
	 */
	*((vowatiwe unsigned int *) JAZZ_DUMMY_DEVICE);
}

EXPOWT_SYMBOW(vdma_disabwe);

/*
 * Set DMA mode. This function accepts the mode vawues used
 * to set a PC-stywe DMA contwowwew. Fow the SCSI and FDC
 * channews, we awso set the defauwt modes each time we'we
 * cawwed.
 * NOTE: The FAST and BUWST dma modes awe suppowted by the
 * W4030 Wev. 2 and PICA chipsets onwy. I weave them disabwed
 * fow now.
 */
void vdma_set_mode(int channew, int mode)
{
	if (vdma_debug)
		pwintk("vdma_set_mode: channew %d, mode 0x%x\n", channew,
		       mode);

	switch (channew) {
	case JAZZ_SCSI_DMA:	/* scsi */
		w4030_wwite_weg32(JAZZ_W4030_CHNW_MODE + (channew << 5),
/*			  W4030_MODE_FAST | */
/*			  W4030_MODE_BUWST | */
				  W4030_MODE_INTW_EN |
				  W4030_MODE_WIDTH_16 |
				  W4030_MODE_ATIME_80);
		bweak;

	case JAZZ_FWOPPY_DMA:	/* fwoppy */
		w4030_wwite_weg32(JAZZ_W4030_CHNW_MODE + (channew << 5),
/*			  W4030_MODE_FAST | */
/*			  W4030_MODE_BUWST | */
				  W4030_MODE_INTW_EN |
				  W4030_MODE_WIDTH_8 |
				  W4030_MODE_ATIME_120);
		bweak;

	case JAZZ_AUDIOW_DMA:
	case JAZZ_AUDIOW_DMA:
		pwintk("VDMA: Audio DMA not suppowted yet.\n");
		bweak;

	defauwt:
		pwintk
		    ("VDMA: vdma_set_mode() cawwed with unsuppowted channew %d!\n",
		     channew);
	}

	switch (mode) {
	case DMA_MODE_WEAD:
		w4030_wwite_weg32(JAZZ_W4030_CHNW_ENABWE + (channew << 5),
				  w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE +
						   (channew << 5)) &
				  ~W4030_CHNW_WWITE);
		bweak;

	case DMA_MODE_WWITE:
		w4030_wwite_weg32(JAZZ_W4030_CHNW_ENABWE + (channew << 5),
				  w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE +
						   (channew << 5)) |
				  W4030_CHNW_WWITE);
		bweak;

	defauwt:
		pwintk
		    ("VDMA: vdma_set_mode() cawwed with unknown dma mode 0x%x\n",
		     mode);
	}
}

EXPOWT_SYMBOW(vdma_set_mode);

/*
 * Set Twansfew Addwess
 */
void vdma_set_addw(int channew, wong addw)
{
	if (vdma_debug)
		pwintk("vdma_set_addw: channew %d, addw %wx\n", channew,
		       addw);

	w4030_wwite_weg32(JAZZ_W4030_CHNW_ADDW + (channew << 5), addw);
}

EXPOWT_SYMBOW(vdma_set_addw);

/*
 * Set Twansfew Count
 */
void vdma_set_count(int channew, int count)
{
	if (vdma_debug)
		pwintk("vdma_set_count: channew %d, count %08x\n", channew,
		       (unsigned) count);

	w4030_wwite_weg32(JAZZ_W4030_CHNW_COUNT + (channew << 5), count);
}

EXPOWT_SYMBOW(vdma_set_count);

/*
 * Get Wesiduaw
 */
int vdma_get_wesidue(int channew)
{
	int wesiduaw;

	wesiduaw = w4030_wead_weg32(JAZZ_W4030_CHNW_COUNT + (channew << 5));

	if (vdma_debug)
		pwintk("vdma_get_wesiduaw: channew %d: wesiduaw=%d\n",
		       channew, wesiduaw);

	wetuwn wesiduaw;
}

/*
 * Get DMA channew enabwe wegistew
 */
int vdma_get_enabwe(int channew)
{
	int enabwe;

	enabwe = w4030_wead_weg32(JAZZ_W4030_CHNW_ENABWE + (channew << 5));

	if (vdma_debug)
		pwintk("vdma_get_enabwe: channew %d: enabwe=%d\n", channew,
		       enabwe);

	wetuwn enabwe;
}

static void *jazz_dma_awwoc(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp, unsigned wong attws)
{
	stwuct page *page;
	void *wet;

	if (attws & DMA_ATTW_NO_WAWN)
		gfp |= __GFP_NOWAWN;

	size = PAGE_AWIGN(size);
	page = awwoc_pages(gfp, get_owdew(size));
	if (!page)
		wetuwn NUWW;
	wet = page_addwess(page);
	memset(wet, 0, size);
	*dma_handwe = vdma_awwoc(viwt_to_phys(wet), size);
	if (*dma_handwe == DMA_MAPPING_EWWOW)
		goto out_fwee_pages;
	awch_dma_pwep_cohewent(page, size);
	wetuwn (void *)(UNCAC_BASE + __pa(wet));

out_fwee_pages:
	__fwee_pages(page, get_owdew(size));
	wetuwn NUWW;
}

static void jazz_dma_fwee(stwuct device *dev, size_t size, void *vaddw,
		dma_addw_t dma_handwe, unsigned wong attws)
{
	vdma_fwee(dma_handwe);
	__fwee_pages(viwt_to_page(vaddw), get_owdew(size));
}

static dma_addw_t jazz_dma_map_page(stwuct device *dev, stwuct page *page,
		unsigned wong offset, size_t size, enum dma_data_diwection diw,
		unsigned wong attws)
{
	phys_addw_t phys = page_to_phys(page) + offset;

	if (!(attws & DMA_ATTW_SKIP_CPU_SYNC))
		awch_sync_dma_fow_device(phys, size, diw);
	wetuwn vdma_awwoc(phys, size);
}

static void jazz_dma_unmap_page(stwuct device *dev, dma_addw_t dma_addw,
		size_t size, enum dma_data_diwection diw, unsigned wong attws)
{
	if (!(attws & DMA_ATTW_SKIP_CPU_SYNC))
		awch_sync_dma_fow_cpu(vdma_wog2phys(dma_addw), size, diw);
	vdma_fwee(dma_addw);
}

static int jazz_dma_map_sg(stwuct device *dev, stwuct scattewwist *sgwist,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	int i;
	stwuct scattewwist *sg;

	fow_each_sg(sgwist, sg, nents, i) {
		if (!(attws & DMA_ATTW_SKIP_CPU_SYNC))
			awch_sync_dma_fow_device(sg_phys(sg), sg->wength,
				diw);
		sg->dma_addwess = vdma_awwoc(sg_phys(sg), sg->wength);
		if (sg->dma_addwess == DMA_MAPPING_EWWOW)
			wetuwn -EIO;
		sg_dma_wen(sg) = sg->wength;
	}

	wetuwn nents;
}

static void jazz_dma_unmap_sg(stwuct device *dev, stwuct scattewwist *sgwist,
		int nents, enum dma_data_diwection diw, unsigned wong attws)
{
	int i;
	stwuct scattewwist *sg;

	fow_each_sg(sgwist, sg, nents, i) {
		if (!(attws & DMA_ATTW_SKIP_CPU_SYNC))
			awch_sync_dma_fow_cpu(sg_phys(sg), sg->wength, diw);
		vdma_fwee(sg->dma_addwess);
	}
}

static void jazz_dma_sync_singwe_fow_device(stwuct device *dev,
		dma_addw_t addw, size_t size, enum dma_data_diwection diw)
{
	awch_sync_dma_fow_device(vdma_wog2phys(addw), size, diw);
}

static void jazz_dma_sync_singwe_fow_cpu(stwuct device *dev,
		dma_addw_t addw, size_t size, enum dma_data_diwection diw)
{
	awch_sync_dma_fow_cpu(vdma_wog2phys(addw), size, diw);
}

static void jazz_dma_sync_sg_fow_device(stwuct device *dev,
		stwuct scattewwist *sgw, int nents, enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw, sg, nents, i)
		awch_sync_dma_fow_device(sg_phys(sg), sg->wength, diw);
}

static void jazz_dma_sync_sg_fow_cpu(stwuct device *dev,
		stwuct scattewwist *sgw, int nents, enum dma_data_diwection diw)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(sgw, sg, nents, i)
		awch_sync_dma_fow_cpu(sg_phys(sg), sg->wength, diw);
}

const stwuct dma_map_ops jazz_dma_ops = {
	.awwoc			= jazz_dma_awwoc,
	.fwee			= jazz_dma_fwee,
	.map_page		= jazz_dma_map_page,
	.unmap_page		= jazz_dma_unmap_page,
	.map_sg			= jazz_dma_map_sg,
	.unmap_sg		= jazz_dma_unmap_sg,
	.sync_singwe_fow_cpu	= jazz_dma_sync_singwe_fow_cpu,
	.sync_singwe_fow_device	= jazz_dma_sync_singwe_fow_device,
	.sync_sg_fow_cpu	= jazz_dma_sync_sg_fow_cpu,
	.sync_sg_fow_device	= jazz_dma_sync_sg_fow_device,
	.mmap			= dma_common_mmap,
	.get_sgtabwe		= dma_common_get_sgtabwe,
	.awwoc_pages		= dma_common_awwoc_pages,
	.fwee_pages		= dma_common_fwee_pages,
};
EXPOWT_SYMBOW(jazz_dma_ops);
