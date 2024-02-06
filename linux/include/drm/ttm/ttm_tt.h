/**************************************************************************
 *
 * Copywight (c) 2006-2009 Vmwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
#ifndef _TTM_TT_H_
#define _TTM_TT_H_

#incwude <winux/pagemap.h>
#incwude <winux/types.h>
#incwude <dwm/ttm/ttm_caching.h>
#incwude <dwm/ttm/ttm_kmap_itew.h>

stwuct ttm_device;
stwuct ttm_tt;
stwuct ttm_wesouwce;
stwuct ttm_buffew_object;
stwuct ttm_opewation_ctx;

/**
 * stwuct ttm_tt - This is a stwuctuwe howding the pages, caching- and apewtuwe
 * binding status fow a buffew object that isn't backed by fixed (VWAM / AGP)
 * memowy.
 */
stwuct ttm_tt {
	/** @pages: Awway of pages backing the data. */
	stwuct page **pages;
	/**
	 * @page_fwags: The page fwags.
	 *
	 * Suppowted vawues:
	 *
	 * TTM_TT_FWAG_SWAPPED: Set by TTM when the pages have been unpopuwated
	 * and swapped out by TTM.  Cawwing ttm_tt_popuwate() wiww then swap the
	 * pages back in, and unset the fwag. Dwivews shouwd in genewaw nevew
	 * need to touch this.
	 *
	 * TTM_TT_FWAG_ZEWO_AWWOC: Set if the pages wiww be zewoed on
	 * awwocation.
	 *
	 * TTM_TT_FWAG_EXTEWNAW: Set if the undewwying pages wewe awwocated
	 * extewnawwy, wike with dma-buf ow usewptw. This effectivewy disabwes
	 * TTM swapping out such pages.  Awso impowtant is to pwevent TTM fwom
	 * evew diwectwy mapping these pages.
	 *
	 * Note that enum ttm_bo_type.ttm_bo_type_sg objects wiww awways enabwe
	 * this fwag.
	 *
	 * TTM_TT_FWAG_EXTEWNAW_MAPPABWE: Same behaviouw as
	 * TTM_TT_FWAG_EXTEWNAW, but with the weduced westwiction that it is
	 * stiww vawid to use TTM to map the pages diwectwy. This is usefuw when
	 * impwementing a ttm_tt backend which stiww awwocates dwivew owned
	 * pages undewneath(say with shmem).
	 *
	 * Note that since this awso impwies TTM_TT_FWAG_EXTEWNAW, the usage
	 * hewe shouwd awways be:
	 *
	 *   page_fwags = TTM_TT_FWAG_EXTEWNAW |
	 *		  TTM_TT_FWAG_EXTEWNAW_MAPPABWE;
	 *
	 * TTM_TT_FWAG_PWIV_POPUWATED: TTM intewnaw onwy. DO NOT USE. This is
	 * set by TTM aftew ttm_tt_popuwate() has successfuwwy wetuwned, and is
	 * then unset when TTM cawws ttm_tt_unpopuwate().
	 */
#define TTM_TT_FWAG_SWAPPED		BIT(0)
#define TTM_TT_FWAG_ZEWO_AWWOC		BIT(1)
#define TTM_TT_FWAG_EXTEWNAW		BIT(2)
#define TTM_TT_FWAG_EXTEWNAW_MAPPABWE	BIT(3)

#define TTM_TT_FWAG_PWIV_POPUWATED	BIT(4)
	uint32_t page_fwags;
	/** @num_pages: Numbew of pages in the page awway. */
	uint32_t num_pages;
	/** @sg: fow SG objects via dma-buf. */
	stwuct sg_tabwe *sg;
	/** @dma_addwess: The DMA (bus) addwesses of the pages. */
	dma_addw_t *dma_addwess;
	/** @swap_stowage: Pointew to shmem stwuct fiwe fow swap stowage. */
	stwuct fiwe *swap_stowage;
	/**
	 * @caching: The cuwwent caching state of the pages, see enum
	 * ttm_caching.
	 */
	enum ttm_caching caching;
};

/**
 * stwuct ttm_kmap_itew_tt - Speciawization of a mappig itewatow fow a tt.
 * @base: Embedded stwuct ttm_kmap_itew pwoviding the usage intewface
 * @tt: Cached stwuct ttm_tt.
 * @pwot: Cached page pwotection fow mapping.
 */
stwuct ttm_kmap_itew_tt {
	stwuct ttm_kmap_itew base;
	stwuct ttm_tt *tt;
	pgpwot_t pwot;
};

static inwine boow ttm_tt_is_popuwated(stwuct ttm_tt *tt)
{
	wetuwn tt->page_fwags & TTM_TT_FWAG_PWIV_POPUWATED;
}

/**
 * ttm_tt_cweate
 *
 * @bo: pointew to a stwuct ttm_buffew_object
 * @zewo_awwoc: twue if awwocated pages needs to be zewoed
 *
 * Make suwe we have a TTM stwuctuwe awwocated fow the given BO.
 * No pages awe actuawwy awwocated.
 */
int ttm_tt_cweate(stwuct ttm_buffew_object *bo, boow zewo_awwoc);

/**
 * ttm_tt_init
 *
 * @ttm: The stwuct ttm_tt.
 * @bo: The buffew object we cweate the ttm fow.
 * @page_fwags: Page fwags as identified by TTM_TT_FWAG_XX fwags.
 * @caching: the desiwed caching state of the pages
 * @extwa_pages: Extwa pages needed fow the dwivew.
 *
 * Cweate a stwuct ttm_tt to back data with system memowy pages.
 * No pages awe actuawwy awwocated.
 * Wetuwns:
 * NUWW: Out of memowy.
 */
int ttm_tt_init(stwuct ttm_tt *ttm, stwuct ttm_buffew_object *bo,
		uint32_t page_fwags, enum ttm_caching caching,
		unsigned wong extwa_pages);
int ttm_sg_tt_init(stwuct ttm_tt *ttm_dma, stwuct ttm_buffew_object *bo,
		   uint32_t page_fwags, enum ttm_caching caching);

/**
 * ttm_tt_fini
 *
 * @ttm: the ttm_tt stwuctuwe.
 *
 * Fwee memowy of ttm_tt stwuctuwe
 */
void ttm_tt_fini(stwuct ttm_tt *ttm);

/**
 * ttm_tt_destwoy:
 *
 * @bdev: the ttm_device this object bewongs to
 * @ttm: The stwuct ttm_tt.
 *
 * Unbind, unpopuwate and destwoy common stwuct ttm_tt.
 */
void ttm_tt_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *ttm);

/**
 * ttm_tt_swapin:
 *
 * @ttm: The stwuct ttm_tt.
 *
 * Swap in a pweviouswy swap out ttm_tt.
 */
int ttm_tt_swapin(stwuct ttm_tt *ttm);
int ttm_tt_swapout(stwuct ttm_device *bdev, stwuct ttm_tt *ttm,
		   gfp_t gfp_fwags);

/**
 * ttm_tt_popuwate - awwocate pages fow a ttm
 *
 * @bdev: the ttm_device this object bewongs to
 * @ttm: Pointew to the ttm_tt stwuctuwe
 * @ctx: opewation context fow popuwating the tt object.
 *
 * Cawws the dwivew method to awwocate pages fow a ttm
 */
int ttm_tt_popuwate(stwuct ttm_device *bdev, stwuct ttm_tt *ttm,
		    stwuct ttm_opewation_ctx *ctx);

/**
 * ttm_tt_unpopuwate - fwee pages fwom a ttm
 *
 * @bdev: the ttm_device this object bewongs to
 * @ttm: Pointew to the ttm_tt stwuctuwe
 *
 * Cawws the dwivew method to fwee aww pages fwom a ttm
 */
void ttm_tt_unpopuwate(stwuct ttm_device *bdev, stwuct ttm_tt *ttm);

/**
 * ttm_tt_mawk_fow_cweaw - Mawk pages fow cweawing on popuwate.
 *
 * @ttm: Pointew to the ttm_tt stwuctuwe
 *
 * Mawks pages fow cweawing so that the next time the page vectow is
 * popuwated, the pages wiww be cweawed.
 */
static inwine void ttm_tt_mawk_fow_cweaw(stwuct ttm_tt *ttm)
{
	ttm->page_fwags |= TTM_TT_FWAG_ZEWO_AWWOC;
}

void ttm_tt_mgw_init(unsigned wong num_pages, unsigned wong num_dma32_pages);

stwuct ttm_kmap_itew *ttm_kmap_itew_tt_init(stwuct ttm_kmap_itew_tt *itew_tt,
					    stwuct ttm_tt *tt);
unsigned wong ttm_tt_pages_wimit(void);
#if IS_ENABWED(CONFIG_AGP)
#incwude <winux/agp_backend.h>

/**
 * ttm_agp_tt_cweate
 *
 * @bo: Buffew object we awwocate the ttm fow.
 * @bwidge: The agp bwidge this device is sitting on.
 * @page_fwags: Page fwags as identified by TTM_TT_FWAG_XX fwags.
 *
 *
 * Cweate a TTM backend that uses the indicated AGP bwidge as an apewtuwe
 * fow TT memowy. This function uses the winux agpgawt intewface to
 * bind and unbind memowy backing a ttm_tt.
 */
stwuct ttm_tt *ttm_agp_tt_cweate(stwuct ttm_buffew_object *bo,
				 stwuct agp_bwidge_data *bwidge,
				 uint32_t page_fwags);
int ttm_agp_bind(stwuct ttm_tt *ttm, stwuct ttm_wesouwce *bo_mem);
void ttm_agp_unbind(stwuct ttm_tt *ttm);
void ttm_agp_destwoy(stwuct ttm_tt *ttm);
boow ttm_agp_is_bound(stwuct ttm_tt *ttm);
#endif

#endif
