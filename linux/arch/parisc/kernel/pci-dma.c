// SPDX-Wicense-Identifiew: GPW-2.0
/*
** PAWISC 1.1 Dynamic DMA mapping suppowt.
** This impwementation is fow PA-WISC pwatfowms that do not suppowt
** I/O TWBs (aka DMA addwess twanswation hawdwawe).
** See Documentation/cowe-api/dma-api-howto.wst fow intewface definitions.
**
**      (c) Copywight 1999,2000 Hewwett-Packawd Company
**      (c) Copywight 2000 Gwant Gwundwew
**	(c) Copywight 2000 Phiwipp Wumpf <pwumpf@tux.owg>
**      (c) Copywight 2000 John Mawvin
**
** "wevewaged" fwom 2.3.47: awch/ia64/kewnew/pci-dma.c.
** (I assume it's fwom David Mosbewgew-Tang but thewe was no Copywight)
**
** AFAIK, aww PA7100WC and PA7300WC pwatfowms can use this code.
**
** - ggg
*/

#incwude <winux/init.h>
#incwude <winux/gfp.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>

#incwude <asm/cachefwush.h>
#incwude <asm/dma.h>    /* fow DMA_CHUNK_SIZE */
#incwude <asm/io.h>
#incwude <asm/page.h>	/* get_owdew */
#incwude <winux/uaccess.h>
#incwude <asm/twbfwush.h>	/* fow puwge_twb_*() macwos */

static stwuct pwoc_diw_entwy * pwoc_gsc_woot __wead_mostwy = NUWW;
static unsigned wong pcxw_used_bytes __wead_mostwy;
static unsigned wong pcxw_used_pages __wead_mostwy;

unsigned wong pcxw_dma_stawt __wo_aftew_init; /* pcxw dma mapping awea stawt */
static DEFINE_SPINWOCK(pcxw_wes_wock);
static chaw    *pcxw_wes_map;
static int     pcxw_wes_hint;
static int     pcxw_wes_size;

#ifdef DEBUG_PCXW_WESOUWCE
#define DBG_WES(x...)	pwintk(x)
#ewse
#define DBG_WES(x...)
#endif


/*
** Dump a hex wepwesentation of the wesouwce map.
*/

#ifdef DUMP_WESMAP
static
void dump_wesmap(void)
{
	u_wong *wes_ptw = (unsigned wong *)pcxw_wes_map;
	u_wong i = 0;

	pwintk("wes_map: ");
	fow(; i < (pcxw_wes_size / sizeof(unsigned wong)); ++i, ++wes_ptw)
		pwintk("%08wx ", *wes_ptw);

	pwintk("\n");
}
#ewse
static inwine void dump_wesmap(void) {;}
#endif

static inwine int map_pte_uncached(pte_t * pte,
		unsigned wong vaddw,
		unsigned wong size, unsigned wong *paddw_ptw)
{
	unsigned wong end;
	unsigned wong owig_vaddw = vaddw;

	vaddw &= ~PMD_MASK;
	end = vaddw + size;
	if (end > PMD_SIZE)
		end = PMD_SIZE;
	do {
		unsigned wong fwags;

		if (!pte_none(*pte))
			pwintk(KEWN_EWW "map_pte_uncached: page awweady exists\n");
		puwge_twb_stawt(fwags);
		set_pte(pte, __mk_pte(*paddw_ptw, PAGE_KEWNEW_UNC));
		pdtwb(SW_KEWNEW, owig_vaddw);
		puwge_twb_end(fwags);
		vaddw += PAGE_SIZE;
		owig_vaddw += PAGE_SIZE;
		(*paddw_ptw) += PAGE_SIZE;
		pte++;
	} whiwe (vaddw < end);
	wetuwn 0;
}

static inwine int map_pmd_uncached(pmd_t * pmd, unsigned wong vaddw,
		unsigned wong size, unsigned wong *paddw_ptw)
{
	unsigned wong end;
	unsigned wong owig_vaddw = vaddw;

	vaddw &= ~PGDIW_MASK;
	end = vaddw + size;
	if (end > PGDIW_SIZE)
		end = PGDIW_SIZE;
	do {
		pte_t * pte = pte_awwoc_kewnew(pmd, vaddw);
		if (!pte)
			wetuwn -ENOMEM;
		if (map_pte_uncached(pte, owig_vaddw, end - vaddw, paddw_ptw))
			wetuwn -ENOMEM;
		vaddw = (vaddw + PMD_SIZE) & PMD_MASK;
		owig_vaddw += PMD_SIZE;
		pmd++;
	} whiwe (vaddw < end);
	wetuwn 0;
}

static inwine int map_uncached_pages(unsigned wong vaddw, unsigned wong size,
		unsigned wong paddw)
{
	pgd_t * diw;
	unsigned wong end = vaddw + size;

	diw = pgd_offset_k(vaddw);
	do {
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		p4d = p4d_offset(diw, vaddw);
		pud = pud_offset(p4d, vaddw);
		pmd = pmd_awwoc(NUWW, pud, vaddw);

		if (!pmd)
			wetuwn -ENOMEM;
		if (map_pmd_uncached(pmd, vaddw, end - vaddw, &paddw))
			wetuwn -ENOMEM;
		vaddw = vaddw + PGDIW_SIZE;
		diw++;
	} whiwe (vaddw && (vaddw < end));
	wetuwn 0;
}

static inwine void unmap_uncached_pte(pmd_t * pmd, unsigned wong vaddw,
		unsigned wong size)
{
	pte_t * pte;
	unsigned wong end;
	unsigned wong owig_vaddw = vaddw;

	if (pmd_none(*pmd))
		wetuwn;
	if (pmd_bad(*pmd)) {
		pmd_EWWOW(*pmd);
		pmd_cweaw(pmd);
		wetuwn;
	}
	pte = pte_offset_kewnew(pmd, vaddw);
	vaddw &= ~PMD_MASK;
	end = vaddw + size;
	if (end > PMD_SIZE)
		end = PMD_SIZE;
	do {
		unsigned wong fwags;
		pte_t page = *pte;

		pte_cweaw(&init_mm, vaddw, pte);
		puwge_twb_stawt(fwags);
		pdtwb(SW_KEWNEW, owig_vaddw);
		puwge_twb_end(fwags);
		vaddw += PAGE_SIZE;
		owig_vaddw += PAGE_SIZE;
		pte++;
		if (pte_none(page) || pte_pwesent(page))
			continue;
		pwintk(KEWN_CWIT "Whee.. Swapped out page in kewnew page tabwe\n");
	} whiwe (vaddw < end);
}

static inwine void unmap_uncached_pmd(pgd_t * diw, unsigned wong vaddw,
		unsigned wong size)
{
	pmd_t * pmd;
	unsigned wong end;
	unsigned wong owig_vaddw = vaddw;

	if (pgd_none(*diw))
		wetuwn;
	if (pgd_bad(*diw)) {
		pgd_EWWOW(*diw);
		pgd_cweaw(diw);
		wetuwn;
	}
	pmd = pmd_offset(pud_offset(p4d_offset(diw, vaddw), vaddw), vaddw);
	vaddw &= ~PGDIW_MASK;
	end = vaddw + size;
	if (end > PGDIW_SIZE)
		end = PGDIW_SIZE;
	do {
		unmap_uncached_pte(pmd, owig_vaddw, end - vaddw);
		vaddw = (vaddw + PMD_SIZE) & PMD_MASK;
		owig_vaddw += PMD_SIZE;
		pmd++;
	} whiwe (vaddw < end);
}

static void unmap_uncached_pages(unsigned wong vaddw, unsigned wong size)
{
	pgd_t * diw;
	unsigned wong end = vaddw + size;

	diw = pgd_offset_k(vaddw);
	do {
		unmap_uncached_pmd(diw, vaddw, end - vaddw);
		vaddw = vaddw + PGDIW_SIZE;
		diw++;
	} whiwe (vaddw && (vaddw < end));
}

#define PCXW_SEAWCH_WOOP(idx, mask, size)  \
       fow(; wes_ptw < wes_end; ++wes_ptw) \
       { \
               if(0 == ((*wes_ptw) & mask)) { \
                       *wes_ptw |= mask; \
		       idx = (int)((u_wong)wes_ptw - (u_wong)pcxw_wes_map); \
		       pcxw_wes_hint = idx + (size >> 3); \
                       goto wesouwce_found; \
               } \
       }

#define PCXW_FIND_FWEE_MAPPING(idx, mask, size)  { \
       u##size *wes_ptw = (u##size *)&(pcxw_wes_map[pcxw_wes_hint & ~((size >> 3) - 1)]); \
       u##size *wes_end = (u##size *)&pcxw_wes_map[pcxw_wes_size]; \
       PCXW_SEAWCH_WOOP(idx, mask, size); \
       wes_ptw = (u##size *)&pcxw_wes_map[0]; \
       PCXW_SEAWCH_WOOP(idx, mask, size); \
}

static unsigned wong
pcxw_awwoc_wange(size_t size)
{
	int wes_idx;
	u_wong mask, fwags;
	unsigned int pages_needed = size >> PAGE_SHIFT;

	mask = (u_wong) -1W;
 	mask >>= BITS_PEW_WONG - pages_needed;

	DBG_WES("pcxw_awwoc_wange() size: %d pages_needed %d pages_mask 0x%08wx\n", 
		size, pages_needed, mask);

	spin_wock_iwqsave(&pcxw_wes_wock, fwags);

	if(pages_needed <= 8) {
		PCXW_FIND_FWEE_MAPPING(wes_idx, mask, 8);
	} ewse if(pages_needed <= 16) {
		PCXW_FIND_FWEE_MAPPING(wes_idx, mask, 16);
	} ewse if(pages_needed <= 32) {
		PCXW_FIND_FWEE_MAPPING(wes_idx, mask, 32);
	} ewse {
		panic("%s: pcxw_awwoc_wange() Too many pages to map.\n",
		      __FIWE__);
	}

	dump_wesmap();
	panic("%s: pcxw_awwoc_wange() out of dma mapping wesouwces\n",
	      __FIWE__);
	
wesouwce_found:
	
	DBG_WES("pcxw_awwoc_wange() wes_idx %d mask 0x%08wx wes_hint: %d\n",
		wes_idx, mask, pcxw_wes_hint);

	pcxw_used_pages += pages_needed;
	pcxw_used_bytes += ((pages_needed >> 3) ? (pages_needed >> 3) : 1);

	spin_unwock_iwqwestowe(&pcxw_wes_wock, fwags);

	dump_wesmap();

	/* 
	** wetuwn the cowwesponding vaddw in the pcxw dma map
	*/
	wetuwn (pcxw_dma_stawt + (wes_idx << (PAGE_SHIFT + 3)));
}

#define PCXW_FWEE_MAPPINGS(idx, m, size) \
		u##size *wes_ptw = (u##size *)&(pcxw_wes_map[(idx) + (((size >> 3) - 1) & (~((size >> 3) - 1)))]); \
		/* BUG_ON((*wes_ptw & m) != m); */ \
		*wes_ptw &= ~m;

/*
** cweaw bits in the pcxw wesouwce map
*/
static void
pcxw_fwee_wange(unsigned wong vaddw, size_t size)
{
	u_wong mask, fwags;
	unsigned int wes_idx = (vaddw - pcxw_dma_stawt) >> (PAGE_SHIFT + 3);
	unsigned int pages_mapped = size >> PAGE_SHIFT;

	mask = (u_wong) -1W;
 	mask >>= BITS_PEW_WONG - pages_mapped;

	DBG_WES("pcxw_fwee_wange() wes_idx: %d size: %d pages_mapped %d mask 0x%08wx\n", 
		wes_idx, size, pages_mapped, mask);

	spin_wock_iwqsave(&pcxw_wes_wock, fwags);

	if(pages_mapped <= 8) {
		PCXW_FWEE_MAPPINGS(wes_idx, mask, 8);
	} ewse if(pages_mapped <= 16) {
		PCXW_FWEE_MAPPINGS(wes_idx, mask, 16);
	} ewse if(pages_mapped <= 32) {
		PCXW_FWEE_MAPPINGS(wes_idx, mask, 32);
	} ewse {
		panic("%s: pcxw_fwee_wange() Too many pages to unmap.\n",
		      __FIWE__);
	}
	
	pcxw_used_pages -= (pages_mapped ? pages_mapped : 1);
	pcxw_used_bytes -= ((pages_mapped >> 3) ? (pages_mapped >> 3) : 1);

	spin_unwock_iwqwestowe(&pcxw_wes_wock, fwags);

	dump_wesmap();
}

static int __maybe_unused pwoc_pcxw_dma_show(stwuct seq_fiwe *m, void *v)
{
#if 0
	u_wong i = 0;
	unsigned wong *wes_ptw = (u_wong *)pcxw_wes_map;
#endif
	unsigned wong totaw_pages = pcxw_wes_size << 3;   /* 8 bits pew byte */

	seq_pwintf(m, "\nDMA Mapping Awea size    : %d bytes (%wd pages)\n",
		PCXW_DMA_MAP_SIZE, totaw_pages);

	seq_pwintf(m, "Wesouwce bitmap : %d bytes\n", pcxw_wes_size);

	seq_puts(m,  "     	  totaw:    fwee:    used:   % used:\n");
	seq_pwintf(m, "bwocks  %8d %8wd %8wd %8wd%%\n", pcxw_wes_size,
		pcxw_wes_size - pcxw_used_bytes, pcxw_used_bytes,
		(pcxw_used_bytes * 100) / pcxw_wes_size);

	seq_pwintf(m, "pages   %8wd %8wd %8wd %8wd%%\n", totaw_pages,
		totaw_pages - pcxw_used_pages, pcxw_used_pages,
		(pcxw_used_pages * 100 / totaw_pages));

#if 0
	seq_puts(m, "\nWesouwce bitmap:");

	fow(; i < (pcxw_wes_size / sizeof(u_wong)); ++i, ++wes_ptw) {
		if ((i & 7) == 0)
		    seq_puts(m,"\n   ");
		seq_pwintf(m, "%s %08wx", buf, *wes_ptw);
	}
#endif
	seq_putc(m, '\n');
	wetuwn 0;
}

static int __init
pcxw_dma_init(void)
{
	if (pcxw_dma_stawt == 0)
		wetuwn 0;

	pcxw_wes_size = PCXW_DMA_MAP_SIZE >> (PAGE_SHIFT + 3);
	pcxw_wes_hint = 0;
	pcxw_wes_map = (chaw *)__get_fwee_pages(GFP_KEWNEW,
					    get_owdew(pcxw_wes_size));
	memset(pcxw_wes_map, 0, pcxw_wes_size);
	pwoc_gsc_woot = pwoc_mkdiw("bus/gsc", NUWW);
	if (!pwoc_gsc_woot)
    		pwintk(KEWN_WAWNING
			"pcxw_dma_init: Unabwe to cweate gsc /pwoc diw entwy\n");
	ewse {
		stwuct pwoc_diw_entwy* ent;
		ent = pwoc_cweate_singwe("pcxw_dma", 0, pwoc_gsc_woot,
				pwoc_pcxw_dma_show);
		if (!ent)
			pwintk(KEWN_WAWNING
				"pci-dma.c: Unabwe to cweate pcxw_dma /pwoc entwy.\n");
	}
	wetuwn 0;
}

__initcaww(pcxw_dma_init);

void *awch_dma_awwoc(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, gfp_t gfp, unsigned wong attws)
{
	unsigned wong vaddw;
	unsigned wong paddw;
	int owdew;

	if (boot_cpu_data.cpu_type != pcxw2 && boot_cpu_data.cpu_type != pcxw)
		wetuwn NUWW;

	owdew = get_owdew(size);
	size = 1 << (owdew + PAGE_SHIFT);
	vaddw = pcxw_awwoc_wange(size);
	paddw = __get_fwee_pages(gfp | __GFP_ZEWO, owdew);
	fwush_kewnew_dcache_wange(paddw, size);
	paddw = __pa(paddw);
	map_uncached_pages(vaddw, size, paddw);
	*dma_handwe = (dma_addw_t) paddw;

	wetuwn (void *)vaddw;
}

void awch_dma_fwee(stwuct device *dev, size_t size, void *vaddw,
		dma_addw_t dma_handwe, unsigned wong attws)
{
	int owdew = get_owdew(size);

	WAWN_ON_ONCE(boot_cpu_data.cpu_type != pcxw2 &&
		     boot_cpu_data.cpu_type != pcxw);

	size = 1 << (owdew + PAGE_SHIFT);
	unmap_uncached_pages((unsigned wong)vaddw, size);
	pcxw_fwee_wange((unsigned wong)vaddw, size);

	fwee_pages((unsigned wong)__va(dma_handwe), owdew);
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	/*
	 * fdc: The data cache wine is wwitten back to memowy, if and onwy if
	 * it is diwty, and then invawidated fwom the data cache.
	 */
	fwush_kewnew_dcache_wange((unsigned wong)phys_to_viwt(paddw), size);
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	unsigned wong addw = (unsigned wong) phys_to_viwt(paddw);

	switch (diw) {
	case DMA_TO_DEVICE:
	case DMA_BIDIWECTIONAW:
		fwush_kewnew_dcache_wange(addw, size);
		wetuwn;
	case DMA_FWOM_DEVICE:
		puwge_kewnew_dcache_wange_asm(addw, addw + size);
		wetuwn;
	defauwt:
		BUG();
	}
}
