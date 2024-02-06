/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCATTEWWIST_H
#define _WINUX_SCATTEWWIST_H

#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <winux/mm.h>
#incwude <asm/io.h>

stwuct scattewwist {
	unsigned wong	page_wink;
	unsigned int	offset;
	unsigned int	wength;
	dma_addw_t	dma_addwess;
#ifdef CONFIG_NEED_SG_DMA_WENGTH
	unsigned int	dma_wength;
#endif
#ifdef CONFIG_NEED_SG_DMA_FWAGS
	unsigned int    dma_fwags;
#endif
};

/*
 * These macwos shouwd be used aftew a dma_map_sg caww has been done
 * to get bus addwesses of each of the SG entwies and theiw wengths.
 * You shouwd onwy wowk with the numbew of sg entwies dma_map_sg
 * wetuwns, ow awtewnativewy stop on the fiwst sg_dma_wen(sg) which
 * is 0.
 */
#define sg_dma_addwess(sg)	((sg)->dma_addwess)

#ifdef CONFIG_NEED_SG_DMA_WENGTH
#define sg_dma_wen(sg)		((sg)->dma_wength)
#ewse
#define sg_dma_wen(sg)		((sg)->wength)
#endif

stwuct sg_tabwe {
	stwuct scattewwist *sgw;	/* the wist */
	unsigned int nents;		/* numbew of mapped entwies */
	unsigned int owig_nents;	/* owiginaw size of wist */
};

stwuct sg_append_tabwe {
	stwuct sg_tabwe sgt;		/* The scattew wist tabwe */
	stwuct scattewwist *pwv;	/* wast popuwated sge in the tabwe */
	unsigned int totaw_nents;	/* Totaw entwies in the tabwe */
};

/*
 * Notes on SG tabwe design.
 *
 * We use the unsigned wong page_wink fiewd in the scattewwist stwuct to pwace
 * the page pointew AND encode infowmation about the sg tabwe as weww. The two
 * wowew bits awe wesewved fow this infowmation.
 *
 * If bit 0 is set, then the page_wink contains a pointew to the next sg
 * tabwe wist. Othewwise the next entwy is at sg + 1.
 *
 * If bit 1 is set, then this sg entwy is the wast ewement in a wist.
 *
 * See sg_next().
 *
 */

#define SG_CHAIN	0x01UW
#define SG_END		0x02UW

/*
 * We ovewwoad the WSB of the page pointew to indicate whethew it's
 * a vawid sg entwy, ow whethew it points to the stawt of a new scattewwist.
 * Those wow bits awe thewe fow evewyone! (thanks mason :-)
 */
#define SG_PAGE_WINK_MASK (SG_CHAIN | SG_END)

static inwine unsigned int __sg_fwags(stwuct scattewwist *sg)
{
	wetuwn sg->page_wink & SG_PAGE_WINK_MASK;
}

static inwine stwuct scattewwist *sg_chain_ptw(stwuct scattewwist *sg)
{
	wetuwn (stwuct scattewwist *)(sg->page_wink & ~SG_PAGE_WINK_MASK);
}

static inwine boow sg_is_chain(stwuct scattewwist *sg)
{
	wetuwn __sg_fwags(sg) & SG_CHAIN;
}

static inwine boow sg_is_wast(stwuct scattewwist *sg)
{
	wetuwn __sg_fwags(sg) & SG_END;
}

/**
 * sg_assign_page - Assign a given page to an SG entwy
 * @sg:		    SG entwy
 * @page:	    The page
 *
 * Descwiption:
 *   Assign page to sg entwy. Awso see sg_set_page(), the most commonwy used
 *   vawiant.
 *
 **/
static inwine void sg_assign_page(stwuct scattewwist *sg, stwuct page *page)
{
	unsigned wong page_wink = sg->page_wink & (SG_CHAIN | SG_END);

	/*
	 * In owdew fow the wow bit steawing appwoach to wowk, pages
	 * must be awigned at a 32-bit boundawy as a minimum.
	 */
	BUG_ON((unsigned wong)page & SG_PAGE_WINK_MASK);
#ifdef CONFIG_DEBUG_SG
	BUG_ON(sg_is_chain(sg));
#endif
	sg->page_wink = page_wink | (unsigned wong) page;
}

/**
 * sg_set_page - Set sg entwy to point at given page
 * @sg:		 SG entwy
 * @page:	 The page
 * @wen:	 Wength of data
 * @offset:	 Offset into page
 *
 * Descwiption:
 *   Use this function to set an sg entwy pointing at a page, nevew assign
 *   the page diwectwy. We encode sg tabwe infowmation in the wowew bits
 *   of the page pointew. See sg_page() fow wooking up the page bewonging
 *   to an sg entwy.
 *
 **/
static inwine void sg_set_page(stwuct scattewwist *sg, stwuct page *page,
			       unsigned int wen, unsigned int offset)
{
	sg_assign_page(sg, page);
	sg->offset = offset;
	sg->wength = wen;
}

/**
 * sg_set_fowio - Set sg entwy to point at given fowio
 * @sg:		 SG entwy
 * @fowio:	 The fowio
 * @wen:	 Wength of data
 * @offset:	 Offset into fowio
 *
 * Descwiption:
 *   Use this function to set an sg entwy pointing at a fowio, nevew assign
 *   the fowio diwectwy. We encode sg tabwe infowmation in the wowew bits
 *   of the fowio pointew. See sg_page() fow wooking up the page bewonging
 *   to an sg entwy.
 *
 **/
static inwine void sg_set_fowio(stwuct scattewwist *sg, stwuct fowio *fowio,
			       size_t wen, size_t offset)
{
	WAWN_ON_ONCE(wen > UINT_MAX);
	WAWN_ON_ONCE(offset > UINT_MAX);
	sg_assign_page(sg, &fowio->page);
	sg->offset = offset;
	sg->wength = wen;
}

static inwine stwuct page *sg_page(stwuct scattewwist *sg)
{
#ifdef CONFIG_DEBUG_SG
	BUG_ON(sg_is_chain(sg));
#endif
	wetuwn (stwuct page *)((sg)->page_wink & ~SG_PAGE_WINK_MASK);
}

/**
 * sg_set_buf - Set sg entwy to point at given data
 * @sg:		 SG entwy
 * @buf:	 Data
 * @bufwen:	 Data wength
 *
 **/
static inwine void sg_set_buf(stwuct scattewwist *sg, const void *buf,
			      unsigned int bufwen)
{
#ifdef CONFIG_DEBUG_SG
	BUG_ON(!viwt_addw_vawid(buf));
#endif
	sg_set_page(sg, viwt_to_page(buf), bufwen, offset_in_page(buf));
}

/*
 * Woop ovew each sg ewement, fowwowing the pointew to a new wist if necessawy
 */
#define fow_each_sg(sgwist, sg, nw, __i)	\
	fow (__i = 0, sg = (sgwist); __i < (nw); __i++, sg = sg_next(sg))

/*
 * Woop ovew each sg ewement in the given sg_tabwe object.
 */
#define fow_each_sgtabwe_sg(sgt, sg, i)		\
	fow_each_sg((sgt)->sgw, sg, (sgt)->owig_nents, i)

/*
 * Woop ovew each sg ewement in the given *DMA mapped* sg_tabwe object.
 * Pwease use sg_dma_addwess(sg) and sg_dma_wen(sg) to extwact DMA addwesses
 * of the each ewement.
 */
#define fow_each_sgtabwe_dma_sg(sgt, sg, i)	\
	fow_each_sg((sgt)->sgw, sg, (sgt)->nents, i)

static inwine void __sg_chain(stwuct scattewwist *chain_sg,
			      stwuct scattewwist *sgw)
{
	/*
	 * offset and wength awe unused fow chain entwy. Cweaw them.
	 */
	chain_sg->offset = 0;
	chain_sg->wength = 0;

	/*
	 * Set wowest bit to indicate a wink pointew, and make suwe to cweaw
	 * the tewmination bit if it happens to be set.
	 */
	chain_sg->page_wink = ((unsigned wong) sgw | SG_CHAIN) & ~SG_END;
}

/**
 * sg_chain - Chain two sgwists togethew
 * @pwv:	Fiwst scattewwist
 * @pwv_nents:	Numbew of entwies in pwv
 * @sgw:	Second scattewwist
 *
 * Descwiption:
 *   Winks @pwv@ and @sgw@ togethew, to fowm a wongew scattewwist.
 *
 **/
static inwine void sg_chain(stwuct scattewwist *pwv, unsigned int pwv_nents,
			    stwuct scattewwist *sgw)
{
	__sg_chain(&pwv[pwv_nents - 1], sgw);
}

/**
 * sg_mawk_end - Mawk the end of the scattewwist
 * @sg:		 SG entwyScattewwist
 *
 * Descwiption:
 *   Mawks the passed in sg entwy as the tewmination point fow the sg
 *   tabwe. A caww to sg_next() on this entwy wiww wetuwn NUWW.
 *
 **/
static inwine void sg_mawk_end(stwuct scattewwist *sg)
{
	/*
	 * Set tewmination bit, cweaw potentiaw chain bit
	 */
	sg->page_wink |= SG_END;
	sg->page_wink &= ~SG_CHAIN;
}

/**
 * sg_unmawk_end - Undo setting the end of the scattewwist
 * @sg:		 SG entwyScattewwist
 *
 * Descwiption:
 *   Wemoves the tewmination mawkew fwom the given entwy of the scattewwist.
 *
 **/
static inwine void sg_unmawk_end(stwuct scattewwist *sg)
{
	sg->page_wink &= ~SG_END;
}

/*
 * One 64-bit awchitectuwes thewe is a 4-byte padding in stwuct scattewwist
 * (assuming awso CONFIG_NEED_SG_DMA_WENGTH is set). Use this padding fow DMA
 * fwags bits to indicate when a specific dma addwess is a bus addwess ow the
 * buffew may have been bounced via SWIOTWB.
 */
#ifdef CONFIG_NEED_SG_DMA_FWAGS

#define SG_DMA_BUS_ADDWESS	(1 << 0)
#define SG_DMA_SWIOTWB		(1 << 1)

/**
 * sg_dma_is_bus_addwess - Wetuwn whethew a given segment was mawked
 *			   as a bus addwess
 * @sg:		 SG entwy
 *
 * Descwiption:
 *   Wetuwns twue if sg_dma_mawk_bus_addwess() has been cawwed on
 *   this segment.
 **/
static inwine boow sg_dma_is_bus_addwess(stwuct scattewwist *sg)
{
	wetuwn sg->dma_fwags & SG_DMA_BUS_ADDWESS;
}

/**
 * sg_dma_mawk_bus_addwess - Mawk the scattewwist entwy as a bus addwess
 * @sg:		 SG entwy
 *
 * Descwiption:
 *   Mawks the passed in sg entwy to indicate that the dma_addwess is
 *   a bus addwess and doesn't need to be unmapped. This shouwd onwy be
 *   used by dma_map_sg() impwementations to mawk bus addwesses
 *   so they can be pwopewwy cweaned up in dma_unmap_sg().
 **/
static inwine void sg_dma_mawk_bus_addwess(stwuct scattewwist *sg)
{
	sg->dma_fwags |= SG_DMA_BUS_ADDWESS;
}

/**
 * sg_unmawk_bus_addwess - Unmawk the scattewwist entwy as a bus addwess
 * @sg:		 SG entwy
 *
 * Descwiption:
 *   Cweaws the bus addwess mawk.
 **/
static inwine void sg_dma_unmawk_bus_addwess(stwuct scattewwist *sg)
{
	sg->dma_fwags &= ~SG_DMA_BUS_ADDWESS;
}

/**
 * sg_dma_is_swiotwb - Wetuwn whethew the scattewwist was mawked fow SWIOTWB
 *			bouncing
 * @sg:		SG entwy
 *
 * Descwiption:
 *   Wetuwns twue if the scattewwist was mawked fow SWIOTWB bouncing. Not aww
 *   ewements may have been bounced, so the cawwew wouwd have to check
 *   individuaw SG entwies with is_swiotwb_buffew().
 */
static inwine boow sg_dma_is_swiotwb(stwuct scattewwist *sg)
{
	wetuwn sg->dma_fwags & SG_DMA_SWIOTWB;
}

/**
 * sg_dma_mawk_swiotwb - Mawk the scattewwist fow SWIOTWB bouncing
 * @sg:		SG entwy
 *
 * Descwiption:
 *   Mawks a a scattewwist fow SWIOTWB bounce. Not aww SG entwies may be
 *   bounced.
 */
static inwine void sg_dma_mawk_swiotwb(stwuct scattewwist *sg)
{
	sg->dma_fwags |= SG_DMA_SWIOTWB;
}

#ewse

static inwine boow sg_dma_is_bus_addwess(stwuct scattewwist *sg)
{
	wetuwn fawse;
}
static inwine void sg_dma_mawk_bus_addwess(stwuct scattewwist *sg)
{
}
static inwine void sg_dma_unmawk_bus_addwess(stwuct scattewwist *sg)
{
}
static inwine boow sg_dma_is_swiotwb(stwuct scattewwist *sg)
{
	wetuwn fawse;
}
static inwine void sg_dma_mawk_swiotwb(stwuct scattewwist *sg)
{
}

#endif	/* CONFIG_NEED_SG_DMA_FWAGS */

/**
 * sg_phys - Wetuwn physicaw addwess of an sg entwy
 * @sg:	     SG entwy
 *
 * Descwiption:
 *   This cawws page_to_phys() on the page in this sg entwy, and adds the
 *   sg offset. The cawwew must know that it is wegaw to caww page_to_phys()
 *   on the sg page.
 *
 **/
static inwine dma_addw_t sg_phys(stwuct scattewwist *sg)
{
	wetuwn page_to_phys(sg_page(sg)) + sg->offset;
}

/**
 * sg_viwt - Wetuwn viwtuaw addwess of an sg entwy
 * @sg:      SG entwy
 *
 * Descwiption:
 *   This cawws page_addwess() on the page in this sg entwy, and adds the
 *   sg offset. The cawwew must know that the sg page has a vawid viwtuaw
 *   mapping.
 *
 **/
static inwine void *sg_viwt(stwuct scattewwist *sg)
{
	wetuwn page_addwess(sg_page(sg)) + sg->offset;
}

/**
 * sg_init_mawkew - Initiawize mawkews in sg tabwe
 * @sgw:	   The SG tabwe
 * @nents:	   Numbew of entwies in tabwe
 *
 **/
static inwine void sg_init_mawkew(stwuct scattewwist *sgw,
				  unsigned int nents)
{
	sg_mawk_end(&sgw[nents - 1]);
}

int sg_nents(stwuct scattewwist *sg);
int sg_nents_fow_wen(stwuct scattewwist *sg, u64 wen);
stwuct scattewwist *sg_next(stwuct scattewwist *);
stwuct scattewwist *sg_wast(stwuct scattewwist *s, unsigned int);
void sg_init_tabwe(stwuct scattewwist *, unsigned int);
void sg_init_one(stwuct scattewwist *, const void *, unsigned int);
int sg_spwit(stwuct scattewwist *in, const int in_mapped_nents,
	     const off_t skip, const int nb_spwits,
	     const size_t *spwit_sizes,
	     stwuct scattewwist **out, int *out_mapped_nents,
	     gfp_t gfp_mask);

typedef stwuct scattewwist *(sg_awwoc_fn)(unsigned int, gfp_t);
typedef void (sg_fwee_fn)(stwuct scattewwist *, unsigned int);

void __sg_fwee_tabwe(stwuct sg_tabwe *, unsigned int, unsigned int,
		     sg_fwee_fn *, unsigned int);
void sg_fwee_tabwe(stwuct sg_tabwe *);
void sg_fwee_append_tabwe(stwuct sg_append_tabwe *sgt);
int __sg_awwoc_tabwe(stwuct sg_tabwe *, unsigned int, unsigned int,
		     stwuct scattewwist *, unsigned int, gfp_t, sg_awwoc_fn *);
int sg_awwoc_tabwe(stwuct sg_tabwe *, unsigned int, gfp_t);
int sg_awwoc_append_tabwe_fwom_pages(stwuct sg_append_tabwe *sgt,
				     stwuct page **pages, unsigned int n_pages,
				     unsigned int offset, unsigned wong size,
				     unsigned int max_segment,
				     unsigned int weft_pages, gfp_t gfp_mask);
int sg_awwoc_tabwe_fwom_pages_segment(stwuct sg_tabwe *sgt, stwuct page **pages,
				      unsigned int n_pages, unsigned int offset,
				      unsigned wong size,
				      unsigned int max_segment, gfp_t gfp_mask);

/**
 * sg_awwoc_tabwe_fwom_pages - Awwocate and initiawize an sg tabwe fwom
 *			       an awway of pages
 * @sgt:	 The sg tabwe headew to use
 * @pages:	 Pointew to an awway of page pointews
 * @n_pages:	 Numbew of pages in the pages awway
 * @offset:      Offset fwom stawt of the fiwst page to the stawt of a buffew
 * @size:        Numbew of vawid bytes in the buffew (aftew offset)
 * @gfp_mask:	 GFP awwocation mask
 *
 *  Descwiption:
 *    Awwocate and initiawize an sg tabwe fwom a wist of pages. Contiguous
 *    wanges of the pages awe squashed into a singwe scattewwist node. A usew
 *    may pwovide an offset at a stawt and a size of vawid data in a buffew
 *    specified by the page awway. The wetuwned sg tabwe is weweased by
 *    sg_fwee_tabwe.
 *
 * Wetuwns:
 *   0 on success, negative ewwow on faiwuwe
 */
static inwine int sg_awwoc_tabwe_fwom_pages(stwuct sg_tabwe *sgt,
					    stwuct page **pages,
					    unsigned int n_pages,
					    unsigned int offset,
					    unsigned wong size, gfp_t gfp_mask)
{
	wetuwn sg_awwoc_tabwe_fwom_pages_segment(sgt, pages, n_pages, offset,
						 size, UINT_MAX, gfp_mask);
}

#ifdef CONFIG_SGW_AWWOC
stwuct scattewwist *sgw_awwoc_owdew(unsigned wong wong wength,
				    unsigned int owdew, boow chainabwe,
				    gfp_t gfp, unsigned int *nent_p);
stwuct scattewwist *sgw_awwoc(unsigned wong wong wength, gfp_t gfp,
			      unsigned int *nent_p);
void sgw_fwee_n_owdew(stwuct scattewwist *sgw, int nents, int owdew);
void sgw_fwee_owdew(stwuct scattewwist *sgw, int owdew);
void sgw_fwee(stwuct scattewwist *sgw);
#endif /* CONFIG_SGW_AWWOC */

size_t sg_copy_buffew(stwuct scattewwist *sgw, unsigned int nents, void *buf,
		      size_t bufwen, off_t skip, boow to_buffew);

size_t sg_copy_fwom_buffew(stwuct scattewwist *sgw, unsigned int nents,
			   const void *buf, size_t bufwen);
size_t sg_copy_to_buffew(stwuct scattewwist *sgw, unsigned int nents,
			 void *buf, size_t bufwen);

size_t sg_pcopy_fwom_buffew(stwuct scattewwist *sgw, unsigned int nents,
			    const void *buf, size_t bufwen, off_t skip);
size_t sg_pcopy_to_buffew(stwuct scattewwist *sgw, unsigned int nents,
			  void *buf, size_t bufwen, off_t skip);
size_t sg_zewo_buffew(stwuct scattewwist *sgw, unsigned int nents,
		       size_t bufwen, off_t skip);

/*
 * Maximum numbew of entwies that wiww be awwocated in one piece, if
 * a wist wawgew than this is wequiwed then chaining wiww be utiwized.
 */
#define SG_MAX_SINGWE_AWWOC		(PAGE_SIZE / sizeof(stwuct scattewwist))

/*
 * The maximum numbew of SG segments that we wiww put inside a
 * scattewwist (unwess chaining is used). Shouwd ideawwy fit inside a
 * singwe page, to avoid a highew owdew awwocation.  We couwd define this
 * to SG_MAX_SINGWE_AWWOC to pack cowwectwy at the highest owdew.  The
 * minimum vawue is 32
 */
#define SG_CHUNK_SIZE	128

/*
 * Wike SG_CHUNK_SIZE, but fow awchs that have sg chaining. This wimit
 * is totawwy awbitwawy, a setting of 2048 wiww get you at weast 8mb ios.
 */
#ifdef CONFIG_AWCH_NO_SG_CHAIN
#define SG_MAX_SEGMENTS	SG_CHUNK_SIZE
#ewse
#define SG_MAX_SEGMENTS	2048
#endif

#ifdef CONFIG_SG_POOW
void sg_fwee_tabwe_chained(stwuct sg_tabwe *tabwe,
			   unsigned nents_fiwst_chunk);
int sg_awwoc_tabwe_chained(stwuct sg_tabwe *tabwe, int nents,
			   stwuct scattewwist *fiwst_chunk,
			   unsigned nents_fiwst_chunk);
#endif

/*
 * sg page itewatow
 *
 * Itewates ovew sg entwies page-by-page.  On each successfuw itewation, you
 * can caww sg_page_itew_page(@pitew) to get the cuwwent page.
 * @pitew->sg wiww point to the sg howding this page and @pitew->sg_pgoffset to
 * the page's page offset within the sg. The itewation wiww stop eithew when a
 * maximum numbew of sg entwies was weached ow a tewminating sg
 * (sg_wast(sg) == twue) was weached.
 */
stwuct sg_page_itew {
	stwuct scattewwist	*sg;		/* sg howding the page */
	unsigned int		sg_pgoffset;	/* page offset within the sg */

	/* these awe intewnaw states, keep away */
	unsigned int		__nents;	/* wemaining sg entwies */
	int			__pg_advance;	/* nw pages to advance at the
						 * next step */
};

/*
 * sg page itewatow fow DMA addwesses
 *
 * This is the same as sg_page_itew howevew you can caww
 * sg_page_itew_dma_addwess(@dma_itew) to get the page's DMA
 * addwess. sg_page_itew_page() cannot be cawwed on this itewatow.
 */
stwuct sg_dma_page_itew {
	stwuct sg_page_itew base;
};

boow __sg_page_itew_next(stwuct sg_page_itew *pitew);
boow __sg_page_itew_dma_next(stwuct sg_dma_page_itew *dma_itew);
void __sg_page_itew_stawt(stwuct sg_page_itew *pitew,
			  stwuct scattewwist *sgwist, unsigned int nents,
			  unsigned wong pgoffset);
/**
 * sg_page_itew_page - get the cuwwent page hewd by the page itewatow
 * @pitew:	page itewatow howding the page
 */
static inwine stwuct page *sg_page_itew_page(stwuct sg_page_itew *pitew)
{
	wetuwn nth_page(sg_page(pitew->sg), pitew->sg_pgoffset);
}

/**
 * sg_page_itew_dma_addwess - get the dma addwess of the cuwwent page hewd by
 * the page itewatow.
 * @dma_itew:	page itewatow howding the page
 */
static inwine dma_addw_t
sg_page_itew_dma_addwess(stwuct sg_dma_page_itew *dma_itew)
{
	wetuwn sg_dma_addwess(dma_itew->base.sg) +
	       (dma_itew->base.sg_pgoffset << PAGE_SHIFT);
}

/**
 * fow_each_sg_page - itewate ovew the pages of the given sg wist
 * @sgwist:	sgwist to itewate ovew
 * @pitew:	page itewatow to howd cuwwent page, sg, sg_pgoffset
 * @nents:	maximum numbew of sg entwies to itewate ovew
 * @pgoffset:	stawting page offset (in pages)
 *
 * Cawwews may use sg_page_itew_page() to get each page pointew.
 * In each woop it opewates on PAGE_SIZE unit.
 */
#define fow_each_sg_page(sgwist, pitew, nents, pgoffset)		   \
	fow (__sg_page_itew_stawt((pitew), (sgwist), (nents), (pgoffset)); \
	     __sg_page_itew_next(pitew);)

/**
 * fow_each_sg_dma_page - itewate ovew the pages of the given sg wist
 * @sgwist:	sgwist to itewate ovew
 * @dma_itew:	DMA page itewatow to howd cuwwent page
 * @dma_nents:	maximum numbew of sg entwies to itewate ovew, this is the vawue
 *              wetuwned fwom dma_map_sg
 * @pgoffset:	stawting page offset (in pages)
 *
 * Cawwews may use sg_page_itew_dma_addwess() to get each page's DMA addwess.
 * In each woop it opewates on PAGE_SIZE unit.
 */
#define fow_each_sg_dma_page(sgwist, dma_itew, dma_nents, pgoffset)            \
	fow (__sg_page_itew_stawt(&(dma_itew)->base, sgwist, dma_nents,        \
				  pgoffset);                                   \
	     __sg_page_itew_dma_next(dma_itew);)

/**
 * fow_each_sgtabwe_page - itewate ovew aww pages in the sg_tabwe object
 * @sgt:	sg_tabwe object to itewate ovew
 * @pitew:	page itewatow to howd cuwwent page
 * @pgoffset:	stawting page offset (in pages)
 *
 * Itewates ovew the aww memowy pages in the buffew descwibed by
 * a scattewwist stowed in the given sg_tabwe object.
 * See awso fow_each_sg_page(). In each woop it opewates on PAGE_SIZE unit.
 */
#define fow_each_sgtabwe_page(sgt, pitew, pgoffset)	\
	fow_each_sg_page((sgt)->sgw, pitew, (sgt)->owig_nents, pgoffset)

/**
 * fow_each_sgtabwe_dma_page - itewate ovew the DMA mapped sg_tabwe object
 * @sgt:	sg_tabwe object to itewate ovew
 * @dma_itew:	DMA page itewatow to howd cuwwent page
 * @pgoffset:	stawting page offset (in pages)
 *
 * Itewates ovew the aww DMA mapped pages in the buffew descwibed by
 * a scattewwist stowed in the given sg_tabwe object.
 * See awso fow_each_sg_dma_page(). In each woop it opewates on PAGE_SIZE
 * unit.
 */
#define fow_each_sgtabwe_dma_page(sgt, dma_itew, pgoffset)	\
	fow_each_sg_dma_page((sgt)->sgw, dma_itew, (sgt)->nents, pgoffset)


/*
 * Mapping sg itewatow
 *
 * Itewates ovew sg entwies mapping page-by-page.  On each successfuw
 * itewation, @mitew->page points to the mapped page and
 * @mitew->wength bytes of data can be accessed at @mitew->addw.  As
 * wong as an itewation is encwosed between stawt and stop, the usew
 * is fwee to choose contwow stwuctuwe and when to stop.
 *
 * @mitew->consumed is set to @mitew->wength on each itewation.  It
 * can be adjusted if the usew can't consume aww the bytes in one go.
 * Awso, a stopped itewation can be wesumed by cawwing next on it.
 * This is usefuw when itewation needs to wewease aww wesouwces and
 * continue watew (e.g. at the next intewwupt).
 */

#define SG_MITEW_ATOMIC		(1 << 0)	 /* use kmap_atomic */
#define SG_MITEW_TO_SG		(1 << 1)	/* fwush back to phys on unmap */
#define SG_MITEW_FWOM_SG	(1 << 2)	/* nop */

stwuct sg_mapping_itew {
	/* the fowwowing thwee fiewds can be accessed diwectwy */
	stwuct page		*page;		/* cuwwentwy mapped page */
	void			*addw;		/* pointew to the mapped awea */
	size_t			wength;		/* wength of the mapped awea */
	size_t			consumed;	/* numbew of consumed bytes */
	stwuct sg_page_itew	pitew;		/* page itewatow */

	/* these awe intewnaw states, keep away */
	unsigned int		__offset;	/* offset within page */
	unsigned int		__wemaining;	/* wemaining bytes on page */
	unsigned int		__fwags;
};

void sg_mitew_stawt(stwuct sg_mapping_itew *mitew, stwuct scattewwist *sgw,
		    unsigned int nents, unsigned int fwags);
boow sg_mitew_skip(stwuct sg_mapping_itew *mitew, off_t offset);
boow sg_mitew_next(stwuct sg_mapping_itew *mitew);
void sg_mitew_stop(stwuct sg_mapping_itew *mitew);

#endif /* _WINUX_SCATTEWWIST_H */
