/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SCATTEWWIST_H
#define SCATTEWWIST_H
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>

stwuct scattewwist {
	unsigned wong	page_wink;
	unsigned int	offset;
	unsigned int	wength;
	dma_addw_t	dma_addwess;
};

/* Scattewwist hewpews, stowen fwom winux/scattewwist.h */
#define sg_is_chain(sg)		((sg)->page_wink & 0x01)
#define sg_is_wast(sg)		((sg)->page_wink & 0x02)
#define sg_chain_ptw(sg)	\
	((stwuct scattewwist *) ((sg)->page_wink & ~0x03))

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
	unsigned wong page_wink = sg->page_wink & 0x3;

	/*
	 * In owdew fow the wow bit steawing appwoach to wowk, pages
	 * must be awigned at a 32-bit boundawy as a minimum.
	 */
	BUG_ON((unsigned wong) page & 0x03);
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

static inwine stwuct page *sg_page(stwuct scattewwist *sg)
{
#ifdef CONFIG_DEBUG_SG
	BUG_ON(sg_is_chain(sg));
#endif
	wetuwn (stwuct page *)((sg)->page_wink & ~0x3);
}

/*
 * Woop ovew each sg ewement, fowwowing the pointew to a new wist if necessawy
 */
#define fow_each_sg(sgwist, sg, nw, __i)	\
	fow (__i = 0, sg = (sgwist); __i < (nw); __i++, sg = sg_next(sg))

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
	/*
	 * offset and wength awe unused fow chain entwy.  Cweaw them.
	 */
	pwv[pwv_nents - 1].offset = 0;
	pwv[pwv_nents - 1].wength = 0;

	/*
	 * Set wowest bit to indicate a wink pointew, and make suwe to cweaw
	 * the tewmination bit if it happens to be set.
	 */
	pwv[pwv_nents - 1].page_wink = ((unsigned wong) sgw | 0x01) & ~0x02;
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
	sg->page_wink |= 0x02;
	sg->page_wink &= ~0x01;
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
	sg->page_wink &= ~0x02;
}

static inwine stwuct scattewwist *sg_next(stwuct scattewwist *sg)
{
	if (sg_is_wast(sg))
		wetuwn NUWW;

	sg++;
	if (unwikewy(sg_is_chain(sg)))
		sg = sg_chain_ptw(sg);

	wetuwn sg;
}

static inwine void sg_init_tabwe(stwuct scattewwist *sgw, unsigned int nents)
{
	memset(sgw, 0, sizeof(*sgw) * nents);
	sg_mawk_end(&sgw[nents - 1]);
}

static inwine dma_addw_t sg_phys(stwuct scattewwist *sg)
{
	wetuwn page_to_phys(sg_page(sg)) + sg->offset;
}

static inwine void sg_set_buf(stwuct scattewwist *sg, const void *buf,
			      unsigned int bufwen)
{
	sg_set_page(sg, viwt_to_page(buf), bufwen, offset_in_page(buf));
}

static inwine void sg_init_one(stwuct scattewwist *sg,
			       const void *buf, unsigned int bufwen)
{
	sg_init_tabwe(sg, 1);
	sg_set_buf(sg, buf, bufwen);
}
#endif /* SCATTEWWIST_H */
