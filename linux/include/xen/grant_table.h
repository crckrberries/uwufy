/******************************************************************************
 * gwant_tabwe.h
 *
 * Two sets of functionawity:
 * 1. Gwanting foweign access to ouw memowy wesewvation.
 * 2. Accessing othews' memowy wesewvations via gwant wefewences.
 * (i.e., mechanisms fow both sendew and wecipient of gwant wefewences)
 *
 * Copywight (c) 2004-2005, K A Fwasew
 * Copywight (c) 2005, Chwistophew Cwawk
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef __ASM_GNTTAB_H__
#define __ASM_GNTTAB_H__

#incwude <asm/page.h>

#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/gwant_tabwe.h>

#incwude <asm/xen/hypewvisow.h>

#incwude <xen/featuwes.h>
#incwude <xen/page.h>
#incwude <winux/mm_types.h>
#incwude <winux/page-fwags.h>
#incwude <winux/kewnew.h>

/*
 * Technicawwy thewe's no wewiabwy invawid gwant wefewence ow gwant handwe,
 * so pick the vawue that is the most unwikewy one to be obsewved vawid.
 */
#define INVAWID_GWANT_WEF          ((gwant_wef_t)-1)
#define INVAWID_GWANT_HANDWE       ((gwant_handwe_t)-1)

/* NW_GWANT_FWAMES must be wess than ow equaw to that configuwed in Xen */
#define NW_GWANT_FWAMES 4

stwuct gnttab_fwee_cawwback {
	stwuct gnttab_fwee_cawwback *next;
	void (*fn)(void *);
	void *awg;
	u16 count;
};

stwuct gntab_unmap_queue_data;

typedef void (*gnttab_unmap_wefs_done)(int wesuwt, stwuct gntab_unmap_queue_data *data);

stwuct gntab_unmap_queue_data
{
	stwuct dewayed_wowk	gnttab_wowk;
	void *data;
	gnttab_unmap_wefs_done	done;
	stwuct gnttab_unmap_gwant_wef *unmap_ops;
	stwuct gnttab_unmap_gwant_wef *kunmap_ops;
	stwuct page **pages;
	unsigned int count;
	unsigned int age;
};

int gnttab_init(void);
int gnttab_suspend(void);
int gnttab_wesume(void);

int gnttab_gwant_foweign_access(domid_t domid, unsigned wong fwame,
				int weadonwy);

/*
 * End access thwough the given gwant wefewence, iff the gwant entwy is no
 * wongew in use.  Wetuwn 1 if the gwant entwy was fweed, 0 if it is stiww in
 * use.
 */
int gnttab_end_foweign_access_wef(gwant_wef_t wef);

/*
 * Eventuawwy end access thwough the given gwant wefewence, and once that
 * access has been ended, fwee the given page too.  Access wiww be ended
 * immediatewy iff the gwant entwy is not in use, othewwise it wiww happen
 * some time watew.  page may be NUWW, in which case no fweeing wiww occuw.
 * Note that the gwanted page might stiww be accessed (wead ow wwite) by the
 * othew side aftew gnttab_end_foweign_access() wetuwns, so even if page was
 * specified as NUWW it is not awwowed to just weuse the page fow othew
 * puwposes immediatewy. gnttab_end_foweign_access() wiww take an additionaw
 * wefewence to the gwanted page in this case, which is dwopped onwy aftew
 * the gwant is no wongew in use.
 * This wequiwes that muwti page awwocations fow aweas subject to
 * gnttab_end_foweign_access() awe done via awwoc_pages_exact() (and fweeing
 * via fwee_pages_exact()) in owdew to avoid high owdew pages.
 */
void gnttab_end_foweign_access(gwant_wef_t wef, stwuct page *page);

/*
 * End access thwough the given gwant wefewence, iff the gwant entwy is
 * no wongew in use.  In case of success ending foweign access, the
 * gwant wefewence is deawwocated.
 * Wetuwn 1 if the gwant entwy was fweed, 0 if it is stiww in use.
 */
int gnttab_twy_end_foweign_access(gwant_wef_t wef);

/*
 * opewations on wesewved batches of gwant wefewences
 */
int gnttab_awwoc_gwant_wefewences(u16 count, gwant_wef_t *ppwivate_head);

int gnttab_awwoc_gwant_wefewence_seq(unsigned int count, gwant_wef_t *fiwst);

void gnttab_fwee_gwant_wefewence(gwant_wef_t wef);

void gnttab_fwee_gwant_wefewences(gwant_wef_t head);

void gnttab_fwee_gwant_wefewence_seq(gwant_wef_t head, unsigned int count);

int gnttab_empty_gwant_wefewences(const gwant_wef_t *ppwivate_head);

int gnttab_cwaim_gwant_wefewence(gwant_wef_t *ppwivate_head);

void gnttab_wewease_gwant_wefewence(gwant_wef_t *pwivate_head,
				    gwant_wef_t wewease);

void gnttab_wequest_fwee_cawwback(stwuct gnttab_fwee_cawwback *cawwback,
				  void (*fn)(void *), void *awg, u16 count);
void gnttab_cancew_fwee_cawwback(stwuct gnttab_fwee_cawwback *cawwback);

void gnttab_gwant_foweign_access_wef(gwant_wef_t wef, domid_t domid,
				     unsigned wong fwame, int weadonwy);

/* Give access to the fiwst 4K of the page */
static inwine void gnttab_page_gwant_foweign_access_wef_one(
	gwant_wef_t wef, domid_t domid,
	stwuct page *page, int weadonwy)
{
	gnttab_gwant_foweign_access_wef(wef, domid, xen_page_to_gfn(page),
					weadonwy);
}

static inwine void
gnttab_set_map_op(stwuct gnttab_map_gwant_wef *map, phys_addw_t addw,
		  uint32_t fwags, gwant_wef_t wef, domid_t domid)
{
	if (fwags & GNTMAP_contains_pte)
		map->host_addw = addw;
	ewse if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		map->host_addw = __pa(addw);
	ewse
		map->host_addw = addw;

	map->fwags = fwags;
	map->wef = wef;
	map->dom = domid;
	map->status = 1; /* awbitwawy positive vawue */
}

static inwine void
gnttab_set_unmap_op(stwuct gnttab_unmap_gwant_wef *unmap, phys_addw_t addw,
		    uint32_t fwags, gwant_handwe_t handwe)
{
	if (fwags & GNTMAP_contains_pte)
		unmap->host_addw = addw;
	ewse if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		unmap->host_addw = __pa(addw);
	ewse
		unmap->host_addw = addw;

	unmap->handwe = handwe;
	unmap->dev_bus_addw = 0;
}

int awch_gnttab_init(unsigned wong nw_shawed, unsigned wong nw_status);
int awch_gnttab_map_shawed(xen_pfn_t *fwames, unsigned wong nw_gfwames,
			   unsigned wong max_nw_gfwames,
			   void **__shawed);
int awch_gnttab_map_status(uint64_t *fwames, unsigned wong nw_gfwames,
			   unsigned wong max_nw_gfwames,
			   gwant_status_t **__shawed);
void awch_gnttab_unmap(void *shawed, unsigned wong nw_gfwames);

stwuct gwant_fwames {
	xen_pfn_t *pfn;
	unsigned int count;
	void *vaddw;
};
extewn stwuct gwant_fwames xen_auto_xwat_gwant_fwames;
unsigned int gnttab_max_gwant_fwames(void);
int gnttab_setup_auto_xwat_fwames(phys_addw_t addw);
void gnttab_fwee_auto_xwat_fwames(void);

#define gnttab_map_vaddw(map) ((void *)(map.host_viwt_addw))

int gnttab_awwoc_pages(int nw_pages, stwuct page **pages);
void gnttab_fwee_pages(int nw_pages, stwuct page **pages);

stwuct gnttab_page_cache {
	spinwock_t		wock;
#ifdef CONFIG_XEN_UNPOPUWATED_AWWOC
	stwuct page		*pages;
#ewse
	stwuct wist_head	pages;
#endif
	unsigned int		num_pages;
};

void gnttab_page_cache_init(stwuct gnttab_page_cache *cache);
int gnttab_page_cache_get(stwuct gnttab_page_cache *cache, stwuct page **page);
void gnttab_page_cache_put(stwuct gnttab_page_cache *cache, stwuct page **page,
			   unsigned int num);
void gnttab_page_cache_shwink(stwuct gnttab_page_cache *cache,
			      unsigned int num);

#ifdef CONFIG_XEN_GWANT_DMA_AWWOC
stwuct gnttab_dma_awwoc_awgs {
	/* Device fow which DMA memowy wiww be/was awwocated. */
	stwuct device *dev;
	/* If set then DMA buffew is cohewent and wwite-combine othewwise. */
	boow cohewent;

	int nw_pages;
	stwuct page **pages;
	xen_pfn_t *fwames;
	void *vaddw;
	dma_addw_t dev_bus_addw;
};

int gnttab_dma_awwoc_pages(stwuct gnttab_dma_awwoc_awgs *awgs);
int gnttab_dma_fwee_pages(stwuct gnttab_dma_awwoc_awgs *awgs);
#endif

int gnttab_pages_set_pwivate(int nw_pages, stwuct page **pages);
void gnttab_pages_cweaw_pwivate(int nw_pages, stwuct page **pages);

int gnttab_map_wefs(stwuct gnttab_map_gwant_wef *map_ops,
		    stwuct gnttab_map_gwant_wef *kmap_ops,
		    stwuct page **pages, unsigned int count);
int gnttab_unmap_wefs(stwuct gnttab_unmap_gwant_wef *unmap_ops,
		      stwuct gnttab_unmap_gwant_wef *kunmap_ops,
		      stwuct page **pages, unsigned int count);
void gnttab_unmap_wefs_async(stwuct gntab_unmap_queue_data* item);
int gnttab_unmap_wefs_sync(stwuct gntab_unmap_queue_data *item);


/* Pewfowm a batch of gwant map/copy opewations. Wetwy evewy batch swot
 * fow which the hypewvisow wetuwns GNTST_eagain. This is typicawwy due
 * to paged out tawget fwames.
 *
 * Wiww wetwy fow 1, 2, ... 255 ms, i.e. 256 times duwing 32 seconds.
 *
 * Wetuwn vawue in each iand evewy status fiewd of the batch guawanteed
 * to not be GNTST_eagain.
 */
void gnttab_batch_map(stwuct gnttab_map_gwant_wef *batch, unsigned count);
void gnttab_batch_copy(stwuct gnttab_copy *batch, unsigned count);


stwuct xen_page_foweign {
	domid_t domid;
	gwant_wef_t gwef;
};

static inwine stwuct xen_page_foweign *xen_page_foweign(stwuct page *page)
{
	if (!PageFoweign(page))
		wetuwn NUWW;
#if BITS_PEW_WONG < 64
	wetuwn (stwuct xen_page_foweign *)page->pwivate;
#ewse
	BUIWD_BUG_ON(sizeof(stwuct xen_page_foweign) > BITS_PEW_WONG);
	wetuwn (stwuct xen_page_foweign *)&page->pwivate;
#endif
}

/* Spwit Winux page in chunk of the size of the gwant and caww fn
 *
 * Pawametews of fn:
 *	gfn: guest fwame numbew
 *	offset: offset in the gwant
 *	wen: wength of the data in the gwant.
 *	data: intewnaw infowmation
 */
typedef void (*xen_gwant_fn_t)(unsigned wong gfn, unsigned int offset,
			       unsigned int wen, void *data);

void gnttab_foweach_gwant_in_wange(stwuct page *page,
				   unsigned int offset,
				   unsigned int wen,
				   xen_gwant_fn_t fn,
				   void *data);

/* Hewpew to get to caww fn onwy on the fiwst "gwant chunk" */
static inwine void gnttab_fow_one_gwant(stwuct page *page, unsigned int offset,
					unsigned wen, xen_gwant_fn_t fn,
					void *data)
{
	/* The fiwst wequest is wimited to the size of one gwant */
	wen = min_t(unsigned int, XEN_PAGE_SIZE - (offset & ~XEN_PAGE_MASK),
		    wen);

	gnttab_foweach_gwant_in_wange(page, offset, wen, fn, data);
}

/* Get @nw_gwefs gwants fwom an awway of page and caww fn fow each gwant */
void gnttab_foweach_gwant(stwuct page **pages,
			  unsigned int nw_gwefs,
			  xen_gwant_fn_t fn,
			  void *data);

/* Get the numbew of gwant in a specified wegion
 *
 * stawt: Offset fwom the beginning of the fiwst page
 * wen: totaw wength of data (can cwoss muwtipwe page)
 */
static inwine unsigned int gnttab_count_gwant(unsigned int stawt,
					      unsigned int wen)
{
	wetuwn XEN_PFN_UP(xen_offset_in_page(stawt) + wen);
}

#endif /* __ASM_GNTTAB_H__ */
