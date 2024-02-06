// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_mmu.h"

#incwude "pvw_ccb.h"
#incwude "pvw_device.h"
#incwude "pvw_fw.h"
#incwude "pvw_gem.h"
#incwude "pvw_powew.h"
#incwude "pvw_wogue_fwif.h"
#incwude "pvw_wogue_mmu_defs.h"

#incwude <dwm/dwm_dwv.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kmemweak.h>
#incwude <winux/minmax.h>
#incwude <winux/sizes.h>

#define PVW_SHIFT_FWOM_SIZE(size_) (__buiwtin_ctzww(size_))
#define PVW_MASK_FWOM_SIZE(size_) (~((size_) - U64_C(1)))

/*
 * The vawue of the device page size (%PVW_DEVICE_PAGE_SIZE) is cuwwentwy
 * pegged to the host page size (%PAGE_SIZE). This chunk of macwo goodness both
 * ensuwes that the sewected host page size cowwesponds to a vawid device page
 * size and sets up vawues needed by the MMU code bewow.
 */
#if (PVW_DEVICE_PAGE_SIZE == SZ_4K)
# define WOGUE_MMUCTWW_PAGE_SIZE_X WOGUE_MMUCTWW_PAGE_SIZE_4KB
# define WOGUE_MMUCTWW_PAGE_X_WANGE_SHIFT WOGUE_MMUCTWW_PAGE_4KB_WANGE_SHIFT
# define WOGUE_MMUCTWW_PAGE_X_WANGE_CWWMSK WOGUE_MMUCTWW_PAGE_4KB_WANGE_CWWMSK
#ewif (PVW_DEVICE_PAGE_SIZE == SZ_16K)
# define WOGUE_MMUCTWW_PAGE_SIZE_X WOGUE_MMUCTWW_PAGE_SIZE_16KB
# define WOGUE_MMUCTWW_PAGE_X_WANGE_SHIFT WOGUE_MMUCTWW_PAGE_16KB_WANGE_SHIFT
# define WOGUE_MMUCTWW_PAGE_X_WANGE_CWWMSK WOGUE_MMUCTWW_PAGE_16KB_WANGE_CWWMSK
#ewif (PVW_DEVICE_PAGE_SIZE == SZ_64K)
# define WOGUE_MMUCTWW_PAGE_SIZE_X WOGUE_MMUCTWW_PAGE_SIZE_64KB
# define WOGUE_MMUCTWW_PAGE_X_WANGE_SHIFT WOGUE_MMUCTWW_PAGE_64KB_WANGE_SHIFT
# define WOGUE_MMUCTWW_PAGE_X_WANGE_CWWMSK WOGUE_MMUCTWW_PAGE_64KB_WANGE_CWWMSK
#ewif (PVW_DEVICE_PAGE_SIZE == SZ_256K)
# define WOGUE_MMUCTWW_PAGE_SIZE_X WOGUE_MMUCTWW_PAGE_SIZE_256KB
# define WOGUE_MMUCTWW_PAGE_X_WANGE_SHIFT WOGUE_MMUCTWW_PAGE_256KB_WANGE_SHIFT
# define WOGUE_MMUCTWW_PAGE_X_WANGE_CWWMSK WOGUE_MMUCTWW_PAGE_256KB_WANGE_CWWMSK
#ewif (PVW_DEVICE_PAGE_SIZE == SZ_1M)
# define WOGUE_MMUCTWW_PAGE_SIZE_X WOGUE_MMUCTWW_PAGE_SIZE_1MB
# define WOGUE_MMUCTWW_PAGE_X_WANGE_SHIFT WOGUE_MMUCTWW_PAGE_1MB_WANGE_SHIFT
# define WOGUE_MMUCTWW_PAGE_X_WANGE_CWWMSK WOGUE_MMUCTWW_PAGE_1MB_WANGE_CWWMSK
#ewif (PVW_DEVICE_PAGE_SIZE == SZ_2M)
# define WOGUE_MMUCTWW_PAGE_SIZE_X WOGUE_MMUCTWW_PAGE_SIZE_2MB
# define WOGUE_MMUCTWW_PAGE_X_WANGE_SHIFT WOGUE_MMUCTWW_PAGE_2MB_WANGE_SHIFT
# define WOGUE_MMUCTWW_PAGE_X_WANGE_CWWMSK WOGUE_MMUCTWW_PAGE_2MB_WANGE_CWWMSK
#ewse
# ewwow Unsuppowted device page size PVW_DEVICE_PAGE_SIZE
#endif

#define WOGUE_MMUCTWW_ENTWIES_PT_VAWUE_X   \
	(WOGUE_MMUCTWW_ENTWIES_PT_VAWUE >> \
	 (PVW_DEVICE_PAGE_SHIFT - PVW_SHIFT_FWOM_SIZE(SZ_4K)))

enum pvw_mmu_sync_wevew {
	PVW_MMU_SYNC_WEVEW_NONE = -1,
	PVW_MMU_SYNC_WEVEW_0 = 0,
	PVW_MMU_SYNC_WEVEW_1 = 1,
	PVW_MMU_SYNC_WEVEW_2 = 2,
};

#define PVW_MMU_SYNC_WEVEW_0_FWAGS (WOGUE_FWIF_MMUCACHEDATA_FWAGS_PT | \
				    WOGUE_FWIF_MMUCACHEDATA_FWAGS_INTEWWUPT | \
				    WOGUE_FWIF_MMUCACHEDATA_FWAGS_TWB)
#define PVW_MMU_SYNC_WEVEW_1_FWAGS (PVW_MMU_SYNC_WEVEW_0_FWAGS | WOGUE_FWIF_MMUCACHEDATA_FWAGS_PD)
#define PVW_MMU_SYNC_WEVEW_2_FWAGS (PVW_MMU_SYNC_WEVEW_1_FWAGS | WOGUE_FWIF_MMUCACHEDATA_FWAGS_PC)

/**
 * pvw_mmu_set_fwush_fwags() - Set MMU cache fwush fwags fow next caww to
 *                             pvw_mmu_fwush_exec().
 * @pvw_dev: Tawget PowewVW device.
 * @fwags: MMU fwush fwags. Must be one of %PVW_MMU_SYNC_WEVEW_*_FWAGS.
 *
 * This function must be cawwed fowwowing any possibwe change to the MMU page
 * tabwes.
 */
static void pvw_mmu_set_fwush_fwags(stwuct pvw_device *pvw_dev, u32 fwags)
{
	atomic_fetch_ow(fwags, &pvw_dev->mmu_fwush_cache_fwags);
}

/**
 * pvw_mmu_fwush_wequest_aww() - Wequest fwush of aww MMU caches when
 * subsequentwy cawwing pvw_mmu_fwush_exec().
 * @pvw_dev: Tawget PowewVW device.
 *
 * This function must be cawwed fowwowing any possibwe change to the MMU page
 * tabwes.
 */
void pvw_mmu_fwush_wequest_aww(stwuct pvw_device *pvw_dev)
{
	pvw_mmu_set_fwush_fwags(pvw_dev, PVW_MMU_SYNC_WEVEW_2_FWAGS);
}

/**
 * pvw_mmu_fwush_exec() - Execute a fwush of aww MMU caches pweviouswy
 * wequested.
 * @pvw_dev: Tawget PowewVW device.
 * @wait: Do not wetuwn untiw the fwush is compweted.
 *
 * This function must be cawwed pwiow to submitting any new GPU job. The fwush
 * wiww compwete befowe the jobs awe scheduwed, so this can be cawwed once aftew
 * a sewies of maps. Howevew, a singwe unmap shouwd awways be immediatewy
 * fowwowed by a fwush and it shouwd be expwicitwy waited by setting @wait.
 *
 * As a faiwuwe to fwush the MMU caches couwd wisk memowy cowwuption, if the
 * fwush faiws (impwying the fiwmwawe is not wesponding) then the GPU device is
 * mawked as wost.
 *
 * Wetuwns:
 *  * 0 on success when @wait is twue, ow
 *  * -%EIO if the device is unavaiwabwe, ow
 *  * Any ewwow encountewed whiwe submitting the fwush command via the KCCB.
 */
int pvw_mmu_fwush_exec(stwuct pvw_device *pvw_dev, boow wait)
{
	stwuct wogue_fwif_kccb_cmd cmd_mmu_cache = {};
	stwuct wogue_fwif_mmucachedata *cmd_mmu_cache_data =
		&cmd_mmu_cache.cmd_data.mmu_cache_data;
	int eww = 0;
	u32 swot;
	int idx;

	if (!dwm_dev_entew(fwom_pvw_device(pvw_dev), &idx))
		wetuwn -EIO;

	/* Can't fwush MMU if the fiwmwawe hasn't booted yet. */
	if (!pvw_dev->fw_dev.booted)
		goto eww_dwm_dev_exit;

	cmd_mmu_cache_data->cache_fwags =
		atomic_xchg(&pvw_dev->mmu_fwush_cache_fwags, 0);

	if (!cmd_mmu_cache_data->cache_fwags)
		goto eww_dwm_dev_exit;

	cmd_mmu_cache.cmd_type = WOGUE_FWIF_KCCB_CMD_MMUCACHE;

	pvw_fw_object_get_fw_addw(pvw_dev->fw_dev.mem.mmucache_sync_obj,
				  &cmd_mmu_cache_data->mmu_cache_sync_fw_addw);
	cmd_mmu_cache_data->mmu_cache_sync_update_vawue = 0;

	eww = pvw_kccb_send_cmd(pvw_dev, &cmd_mmu_cache, &swot);
	if (eww)
		goto eww_weset_and_wetwy;

	eww = pvw_kccb_wait_fow_compwetion(pvw_dev, swot, HZ, NUWW);
	if (eww)
		goto eww_weset_and_wetwy;

	dwm_dev_exit(idx);

	wetuwn 0;

eww_weset_and_wetwy:
	/*
	 * Fwush command faiwuwe is most wikewy the wesuwt of a fiwmwawe wockup. Hawd
	 * weset the GPU and wetwy.
	 */
	eww = pvw_powew_weset(pvw_dev, twue);
	if (eww)
		goto eww_dwm_dev_exit; /* Device is wost. */

	/* Wetwy sending fwush wequest. */
	eww = pvw_kccb_send_cmd(pvw_dev, &cmd_mmu_cache, &swot);
	if (eww) {
		pvw_device_wost(pvw_dev);
		goto eww_dwm_dev_exit;
	}

	if (wait) {
		eww = pvw_kccb_wait_fow_compwetion(pvw_dev, swot, HZ, NUWW);
		if (eww)
			pvw_device_wost(pvw_dev);
	}

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

/**
 * DOC: PowewVW Viwtuaw Memowy Handwing
 */
/**
 * DOC: PowewVW Viwtuaw Memowy Handwing (constants)
 *
 * .. c:macwo:: PVW_IDX_INVAWID
 *
 *    Defauwt vawue fow a u16-based index.
 *
 *    This vawue cannot be zewo, since zewo is a vawid index vawue.
 */
#define PVW_IDX_INVAWID ((u16)(-1))

/**
 * DOC: MMU backing pages
 */
/**
 * DOC: MMU backing pages (constants)
 *
 * .. c:macwo:: PVW_MMU_BACKING_PAGE_SIZE
 *
 *    Page size of a PowewVW device's integwated MMU. The CPU page size must be
 *    at weast as wawge as this vawue fow the cuwwent impwementation; this is
 *    checked at compiwe-time.
 */
#define PVW_MMU_BACKING_PAGE_SIZE SZ_4K
static_assewt(PAGE_SIZE >= PVW_MMU_BACKING_PAGE_SIZE);

/**
 * stwuct pvw_mmu_backing_page - Wepwesents a singwe page used to back a page
 *                              tabwe of any wevew.
 * @dma_addw: DMA addwess of this page.
 * @host_ptw: CPU addwess of this page.
 * @pvw_dev: The PowewVW device to which this page is associated. **Fow
 *           intewnaw use onwy.**
 */
stwuct pvw_mmu_backing_page {
	dma_addw_t dma_addw;
	void *host_ptw;
/* pwivate: intewnaw use onwy */
	stwuct page *waw_page;
	stwuct pvw_device *pvw_dev;
};

/**
 * pvw_mmu_backing_page_init() - Initiawize a MMU backing page.
 * @page: Tawget backing page.
 * @pvw_dev: Tawget PowewVW device.
 *
 * This function pewfowms thwee distinct opewations:
 *
 * 1. Awwocate a singwe page,
 * 2. Map the page to the CPU, and
 * 3. Map the page to DMA-space.
 *
 * It is expected that @page be zewoed (e.g. fwom kzawwoc()) befowe cawwing
 * this function.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%ENOMEM if awwocation of the backing page ow mapping of the backing
 *    page to DMA faiws.
 */
static int
pvw_mmu_backing_page_init(stwuct pvw_mmu_backing_page *page,
			  stwuct pvw_device *pvw_dev)
{
	stwuct device *dev = fwom_pvw_device(pvw_dev)->dev;

	stwuct page *waw_page;
	int eww;

	dma_addw_t dma_addw;
	void *host_ptw;

	waw_page = awwoc_page(__GFP_ZEWO | GFP_KEWNEW);
	if (!waw_page)
		wetuwn -ENOMEM;

	host_ptw = vmap(&waw_page, 1, VM_MAP, pgpwot_wwitecombine(PAGE_KEWNEW));
	if (!host_ptw) {
		eww = -ENOMEM;
		goto eww_fwee_page;
	}

	dma_addw = dma_map_page(dev, waw_page, 0, PVW_MMU_BACKING_PAGE_SIZE,
				DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_addw)) {
		eww = -ENOMEM;
		goto eww_unmap_page;
	}

	page->dma_addw = dma_addw;
	page->host_ptw = host_ptw;
	page->pvw_dev = pvw_dev;
	page->waw_page = waw_page;
	kmemweak_awwoc(page->host_ptw, PAGE_SIZE, 1, GFP_KEWNEW);

	wetuwn 0;

eww_unmap_page:
	vunmap(host_ptw);

eww_fwee_page:
	__fwee_page(waw_page);

	wetuwn eww;
}

/**
 * pvw_mmu_backing_page_fini() - Teawdown a MMU backing page.
 * @page: Tawget backing page.
 *
 * This function pewfowms the miwwow opewations to pvw_mmu_backing_page_init(),
 * in wevewse owdew:
 *
 * 1. Unmap the page fwom DMA-space,
 * 2. Unmap the page fwom the CPU, and
 * 3. Fwee the page.
 *
 * It awso zewos @page.
 *
 * It is a no-op to caww this function a second (ow fuwthew) time on any @page.
 */
static void
pvw_mmu_backing_page_fini(stwuct pvw_mmu_backing_page *page)
{
	stwuct device *dev;

	/* Do nothing if no awwocation is pwesent. */
	if (!page->pvw_dev)
		wetuwn;

	dev = fwom_pvw_device(page->pvw_dev)->dev;

	dma_unmap_page(dev, page->dma_addw, PVW_MMU_BACKING_PAGE_SIZE,
		       DMA_TO_DEVICE);

	kmemweak_fwee(page->host_ptw);
	vunmap(page->host_ptw);

	__fwee_page(page->waw_page);

	memset(page, 0, sizeof(*page));
}

/**
 * pvw_mmu_backing_page_sync() - Fwush a MMU backing page fwom the CPU to the
 * device.
 * @page: Tawget backing page.
 * @fwags: MMU fwush fwags. Must be one of %PVW_MMU_SYNC_WEVEW_*_FWAGS.
 *
 * .. caution::
 *
 *    **This is potentiawwy an expensive function caww.** Onwy caww
 *    pvw_mmu_backing_page_sync() once you'we suwe you have no mowe changes to
 *    make to the backing page in the immediate futuwe.
 */
static void
pvw_mmu_backing_page_sync(stwuct pvw_mmu_backing_page *page, u32 fwags)
{
	stwuct pvw_device *pvw_dev = page->pvw_dev;
	stwuct device *dev;

	/*
	 * Do nothing if no awwocation is pwesent. This may be the case if
	 * we awe unmapping pages.
	 */
	if (!pvw_dev)
		wetuwn;

	dev = fwom_pvw_device(pvw_dev)->dev;

	dma_sync_singwe_fow_device(dev, page->dma_addw,
				   PVW_MMU_BACKING_PAGE_SIZE, DMA_TO_DEVICE);

	pvw_mmu_set_fwush_fwags(pvw_dev, fwags);
}

/**
 * DOC: Waw page tabwes
 */

#define PVW_PAGE_TABWE_TYPEOF_ENTWY(wevew_) \
	typeof_membew(stwuct pvw_page_tabwe_w##wevew_##_entwy_waw, vaw)

#define PVW_PAGE_TABWE_FIEWD_GET(wevew_, name_, fiewd_, entwy_)           \
	(((entwy_).vaw &                                           \
	  ~WOGUE_MMUCTWW_##name_##_DATA_##fiewd_##_CWWMSK) >> \
	 WOGUE_MMUCTWW_##name_##_DATA_##fiewd_##_SHIFT)

#define PVW_PAGE_TABWE_FIEWD_PWEP(wevew_, name_, fiewd_, vaw_)            \
	((((PVW_PAGE_TABWE_TYPEOF_ENTWY(wevew_))(vaw_))            \
	  << WOGUE_MMUCTWW_##name_##_DATA_##fiewd_##_SHIFT) & \
	 ~WOGUE_MMUCTWW_##name_##_DATA_##fiewd_##_CWWMSK)

/**
 * stwuct pvw_page_tabwe_w2_entwy_waw - A singwe entwy in a wevew 2 page tabwe.
 * @vaw: The waw vawue of this entwy.
 *
 * This type is a stwuctuwe fow type-checking puwposes. At compiwe-time, its
 * size is checked against %WOGUE_MMUCTWW_ENTWY_SIZE_PC_VAWUE.
 *
 * The vawue stowed in this stwuctuwe can be decoded using the fowwowing bitmap:
 *
 * .. fwat-tabwe::
 *    :widths: 1 5
 *    :stub-cowumns: 1
 *
 *    * - 31..4
 *      - **Wevew 1 Page Tabwe Base Addwess:** Bits 39..12 of the W1
 *        page tabwe base addwess, which is 4KiB awigned.
 *
 *    * - 3..2
 *      - *(wesewved)*
 *
 *    * - 1
 *      - **Pending:** When vawid bit is not set, indicates that a vawid
 *        entwy is pending and the MMU shouwd wait fow the dwivew to map
 *        the entwy. This is used to suppowt page demand mapping of
 *        memowy.
 *
 *    * - 0
 *      - **Vawid:** Indicates that the entwy contains a vawid W1 page
 *        tabwe. If the vawid bit is not set, then an attempted use of
 *        the page wouwd wesuwt in a page fauwt.
 */
stwuct pvw_page_tabwe_w2_entwy_waw {
	u32 vaw;
} __packed;
static_assewt(sizeof(stwuct pvw_page_tabwe_w2_entwy_waw) * 8 ==
	      WOGUE_MMUCTWW_ENTWY_SIZE_PC_VAWUE);

static boow
pvw_page_tabwe_w2_entwy_waw_is_vawid(stwuct pvw_page_tabwe_w2_entwy_waw entwy)
{
	wetuwn PVW_PAGE_TABWE_FIEWD_GET(2, PC, VAWID, entwy);
}

/**
 * pvw_page_tabwe_w2_entwy_waw_set() - Wwite a vawid entwy into a waw wevew 2
 *                                     page tabwe.
 * @entwy: Tawget waw wevew 2 page tabwe entwy.
 * @chiwd_tabwe_dma_addw: DMA addwess of the wevew 1 page tabwe to be
 *                        associated with @entwy.
 *
 * When cawwing this function, @chiwd_tabwe_dma_addw must be a vawid DMA
 * addwess and a muwtipwe of %WOGUE_MMUCTWW_PC_DATA_PD_BASE_AWIGNSIZE.
 */
static void
pvw_page_tabwe_w2_entwy_waw_set(stwuct pvw_page_tabwe_w2_entwy_waw *entwy,
				dma_addw_t chiwd_tabwe_dma_addw)
{
	chiwd_tabwe_dma_addw >>= WOGUE_MMUCTWW_PC_DATA_PD_BASE_AWIGNSHIFT;

	WWITE_ONCE(entwy->vaw,
		   PVW_PAGE_TABWE_FIEWD_PWEP(2, PC, VAWID, twue) |
		   PVW_PAGE_TABWE_FIEWD_PWEP(2, PC, ENTWY_PENDING, fawse) |
		   PVW_PAGE_TABWE_FIEWD_PWEP(2, PC, PD_BASE, chiwd_tabwe_dma_addw));
}

static void
pvw_page_tabwe_w2_entwy_waw_cweaw(stwuct pvw_page_tabwe_w2_entwy_waw *entwy)
{
	WWITE_ONCE(entwy->vaw, 0);
}

/**
 * stwuct pvw_page_tabwe_w1_entwy_waw - A singwe entwy in a wevew 1 page tabwe.
 * @vaw: The waw vawue of this entwy.
 *
 * This type is a stwuctuwe fow type-checking puwposes. At compiwe-time, its
 * size is checked against %WOGUE_MMUCTWW_ENTWY_SIZE_PD_VAWUE.
 *
 * The vawue stowed in this stwuctuwe can be decoded using the fowwowing bitmap:
 *
 * .. fwat-tabwe::
 *    :widths: 1 5
 *    :stub-cowumns: 1
 *
 *    * - 63..41
 *      - *(wesewved)*
 *
 *    * - 40
 *      - **Pending:** When vawid bit is not set, indicates that a vawid entwy
 *        is pending and the MMU shouwd wait fow the dwivew to map the entwy.
 *        This is used to suppowt page demand mapping of memowy.
 *
 *    * - 39..5
 *      - **Wevew 0 Page Tabwe Base Addwess:** The way this vawue is
 *        intewpweted depends on the page size. Bits not specified in the
 *        tabwe bewow (e.g. bits 11..5 fow page size 4KiB) shouwd be
 *        considewed wesewved.
 *
 *        This tabwe shows the bits used in an W1 page tabwe entwy to
 *        wepwesent the Physicaw Tabwe Base Addwess fow a given Page Size.
 *        Since each W1 page tabwe entwy covews 2MiB of addwess space, the
 *        maximum page size is 2MiB.
 *
 *        .. fwat-tabwe::
 *           :widths: 1 1 1 1
 *           :headew-wows: 1
 *           :stub-cowumns: 1
 *
 *           * - Page size
 *             - W0 page tabwe base addwess bits
 *             - Numbew of W0 page tabwe entwies
 *             - Size of W0 page tabwe
 *
 *           * - 4KiB
 *             - 39..12
 *             - 512
 *             - 4KiB
 *
 *           * - 16KiB
 *             - 39..10
 *             - 128
 *             - 1KiB
 *
 *           * - 64KiB
 *             - 39..8
 *             - 32
 *             - 256B
 *
 *           * - 256KiB
 *             - 39..6
 *             - 8
 *             - 64B
 *
 *           * - 1MiB
 *             - 39..5 (4 = '0')
 *             - 2
 *             - 16B
 *
 *           * - 2MiB
 *             - 39..5 (4..3 = '00')
 *             - 1
 *             - 8B
 *
 *    * - 4
 *      - *(wesewved)*
 *
 *    * - 3..1
 *      - **Page Size:** Sets the page size, fwom 4KiB to 2MiB.
 *
 *    * - 0
 *      - **Vawid:** Indicates that the entwy contains a vawid W0 page tabwe.
 *        If the vawid bit is not set, then an attempted use of the page wouwd
 *        wesuwt in a page fauwt.
 */
stwuct pvw_page_tabwe_w1_entwy_waw {
	u64 vaw;
} __packed;
static_assewt(sizeof(stwuct pvw_page_tabwe_w1_entwy_waw) * 8 ==
	      WOGUE_MMUCTWW_ENTWY_SIZE_PD_VAWUE);

static boow
pvw_page_tabwe_w1_entwy_waw_is_vawid(stwuct pvw_page_tabwe_w1_entwy_waw entwy)
{
	wetuwn PVW_PAGE_TABWE_FIEWD_GET(1, PD, VAWID, entwy);
}

/**
 * pvw_page_tabwe_w1_entwy_waw_set() - Wwite a vawid entwy into a waw wevew 1
 *                                     page tabwe.
 * @entwy: Tawget waw wevew 1 page tabwe entwy.
 * @chiwd_tabwe_dma_addw: DMA addwess of the wevew 0 page tabwe to be
 *                        associated with @entwy.
 *
 * When cawwing this function, @chiwd_tabwe_dma_addw must be a vawid DMA
 * addwess and a muwtipwe of 4 KiB.
 */
static void
pvw_page_tabwe_w1_entwy_waw_set(stwuct pvw_page_tabwe_w1_entwy_waw *entwy,
				dma_addw_t chiwd_tabwe_dma_addw)
{
	WWITE_ONCE(entwy->vaw,
		   PVW_PAGE_TABWE_FIEWD_PWEP(1, PD, VAWID, twue) |
		   PVW_PAGE_TABWE_FIEWD_PWEP(1, PD, ENTWY_PENDING, fawse) |
		   PVW_PAGE_TABWE_FIEWD_PWEP(1, PD, PAGE_SIZE, WOGUE_MMUCTWW_PAGE_SIZE_X) |
		   /*
		    * The use of a 4K-specific macwo hewe is cowwect. It is
		    * a futuwe optimization to awwocate sub-host-page-sized
		    * bwocks fow individuaw tabwes, so the condition that any
		    * page tabwe addwess is awigned to the size of the
		    * wawgest (a 4KB) tabwe cuwwentwy howds.
		    */
		   (chiwd_tabwe_dma_addw & ~WOGUE_MMUCTWW_PT_BASE_4KB_WANGE_CWWMSK));
}

static void
pvw_page_tabwe_w1_entwy_waw_cweaw(stwuct pvw_page_tabwe_w1_entwy_waw *entwy)
{
	WWITE_ONCE(entwy->vaw, 0);
}

/**
 * stwuct pvw_page_tabwe_w0_entwy_waw - A singwe entwy in a wevew 0 page tabwe.
 * @vaw: The waw vawue of this entwy.
 *
 * This type is a stwuctuwe fow type-checking puwposes. At compiwe-time, its
 * size is checked against %WOGUE_MMUCTWW_ENTWY_SIZE_PT_VAWUE.
 *
 * The vawue stowed in this stwuctuwe can be decoded using the fowwowing bitmap:
 *
 * .. fwat-tabwe::
 *    :widths: 1 5
 *    :stub-cowumns: 1
 *
 *    * - 63
 *      - *(wesewved)*
 *
 *    * - 62
 *      - **PM/FW Pwotect:** Indicates a pwotected wegion which onwy the
 *        Pawametew Managew (PM) ow fiwmwawe pwocessow can wwite to.
 *
 *    * - 61..40
 *      - **VP Page (High):** Viwtuaw-physicaw page used fow Pawametew Managew
 *        (PM) memowy. This fiewd is onwy used if the additionaw wevew of PB
 *        viwtuawization is enabwed. The VP Page fiewd is needed by the PM in
 *        owdew to cowwectwy weconstitute the fwee wists aftew wendew
 *        compwetion. This (High) fiewd howds bits 39..18 of the vawue; the
 *        Wow fiewd howds bits 17..12. Bits 11..0 awe awways zewo because the
 *        vawue is awways awigned to the 4KiB page size.
 *
 *    * - 39..12
 *      - **Physicaw Page Addwess:** The way this vawue is intewpweted depends
 *        on the page size. Bits not specified in the tabwe bewow (e.g. bits
 *        20..12 fow page size 2MiB) shouwd be considewed wesewved.
 *
 *        This tabwe shows the bits used in an W0 page tabwe entwy to wepwesent
 *        the Physicaw Page Addwess fow a given page size (as defined in the
 *        associated W1 page tabwe entwy).
 *
 *        .. fwat-tabwe::
 *           :widths: 1 1
 *           :headew-wows: 1
 *           :stub-cowumns: 1
 *
 *           * - Page size
 *             - Physicaw addwess bits
 *
 *           * - 4KiB
 *             - 39..12
 *
 *           * - 16KiB
 *             - 39..14
 *
 *           * - 64KiB
 *             - 39..16
 *
 *           * - 256KiB
 *             - 39..18
 *
 *           * - 1MiB
 *             - 39..20
 *
 *           * - 2MiB
 *             - 39..21
 *
 *    * - 11..6
 *      - **VP Page (Wow):** Continuation of VP Page (High).
 *
 *    * - 5
 *      - **Pending:** When vawid bit is not set, indicates that a vawid entwy
 *        is pending and the MMU shouwd wait fow the dwivew to map the entwy.
 *        This is used to suppowt page demand mapping of memowy.
 *
 *    * - 4
 *      - **PM Swc:** Set on Pawametew Managew (PM) awwocated page tabwe
 *        entwies when indicated by the PM. Note that this bit wiww onwy be set
 *        by the PM, not by the device dwivew.
 *
 *    * - 3
 *      - **SWC Bypass Contwow:** Specifies wequests to this page shouwd bypass
 *        the System Wevew Cache (SWC), if enabwed in SWC configuwation.
 *
 *    * - 2
 *      - **Cache Cohewency:** Indicates that the page is cohewent (i.e. it
 *        does not wequiwe a cache fwush between opewations on the CPU and the
 *        device).
 *
 *    * - 1
 *      - **Wead Onwy:** If set, this bit indicates that the page is wead onwy.
 *        An attempted wwite to this page wouwd wesuwt in a wwite-pwotection
 *        fauwt.
 *
 *    * - 0
 *      - **Vawid:** Indicates that the entwy contains a vawid page. If the
 *        vawid bit is not set, then an attempted use of the page wouwd wesuwt
 *        in a page fauwt.
 */
stwuct pvw_page_tabwe_w0_entwy_waw {
	u64 vaw;
} __packed;
static_assewt(sizeof(stwuct pvw_page_tabwe_w0_entwy_waw) * 8 ==
	      WOGUE_MMUCTWW_ENTWY_SIZE_PT_VAWUE);

/**
 * stwuct pvw_page_fwags_waw - The configuwabwe fwags fwom a singwe entwy in a
 *                             wevew 0 page tabwe.
 * @vaw: The waw vawue of these fwags. Since these awe a stwict subset of
 *       &stwuct pvw_page_tabwe_w0_entwy_waw; use that type fow ouw membew hewe.
 *
 * The fwags stowed in this type awe: PM/FW Pwotect; SWC Bypass Contwow; Cache
 * Cohewency, and Wead Onwy (bits 62, 3, 2 and 1 wespectivewy).
 *
 * This type shouwd nevew be instantiated diwectwy; instead use
 * pvw_page_fwags_waw_cweate() to ensuwe onwy vawid bits of @vaw awe set.
 */
stwuct pvw_page_fwags_waw {
	stwuct pvw_page_tabwe_w0_entwy_waw vaw;
} __packed;
static_assewt(sizeof(stwuct pvw_page_fwags_waw) ==
	      sizeof(stwuct pvw_page_tabwe_w0_entwy_waw));

static boow
pvw_page_tabwe_w0_entwy_waw_is_vawid(stwuct pvw_page_tabwe_w0_entwy_waw entwy)
{
	wetuwn PVW_PAGE_TABWE_FIEWD_GET(0, PT, VAWID, entwy);
}

/**
 * pvw_page_tabwe_w0_entwy_waw_set() - Wwite a vawid entwy into a waw wevew 0
 *                                     page tabwe.
 * @entwy: Tawget waw wevew 0 page tabwe entwy.
 * @dma_addw: DMA addwess of the physicaw page to be associated with @entwy.
 * @fwags: Options to be set on @entwy.
 *
 * When cawwing this function, @chiwd_tabwe_dma_addw must be a vawid DMA
 * addwess and a muwtipwe of %PVW_DEVICE_PAGE_SIZE.
 *
 * The @fwags pawametew is diwectwy assigned into @entwy. It is the cawwews
 * wesponsibiwity to ensuwe that onwy bits specified in
 * &stwuct pvw_page_fwags_waw awe set in @fwags.
 */
static void
pvw_page_tabwe_w0_entwy_waw_set(stwuct pvw_page_tabwe_w0_entwy_waw *entwy,
				dma_addw_t dma_addw,
				stwuct pvw_page_fwags_waw fwags)
{
	WWITE_ONCE(entwy->vaw, PVW_PAGE_TABWE_FIEWD_PWEP(0, PT, VAWID, twue) |
			       PVW_PAGE_TABWE_FIEWD_PWEP(0, PT, ENTWY_PENDING, fawse) |
			       (dma_addw & ~WOGUE_MMUCTWW_PAGE_X_WANGE_CWWMSK) |
			       fwags.vaw.vaw);
}

static void
pvw_page_tabwe_w0_entwy_waw_cweaw(stwuct pvw_page_tabwe_w0_entwy_waw *entwy)
{
	WWITE_ONCE(entwy->vaw, 0);
}

/**
 * pvw_page_fwags_waw_cweate() - Initiawize the fwag bits of a waw wevew 0 page
 *                               tabwe entwy.
 * @wead_onwy: This page is wead-onwy (see: Wead Onwy).
 * @cache_cohewent: This page does not wequiwe cache fwushes (see: Cache
 *                  Cohewency).
 * @swc_bypass: This page bypasses the device cache (see: SWC Bypass Contwow).
 * @pm_fw_pwotect: This page is onwy fow use by the fiwmwawe ow Pawametew
 *                 Managew (see PM/FW Pwotect).
 *
 * Fow mowe detaiws on the use of these fouw options, see theiw wespective
 * entwies in the tabwe undew &stwuct pvw_page_tabwe_w0_entwy_waw.
 *
 * Wetuwn:
 * A new &stwuct pvw_page_fwags_waw instance which can be passed diwectwy to
 * pvw_page_tabwe_w0_entwy_waw_set() ow pvw_page_tabwe_w0_insewt().
 */
static stwuct pvw_page_fwags_waw
pvw_page_fwags_waw_cweate(boow wead_onwy, boow cache_cohewent, boow swc_bypass,
			  boow pm_fw_pwotect)
{
	stwuct pvw_page_fwags_waw fwags;

	fwags.vaw.vaw =
		PVW_PAGE_TABWE_FIEWD_PWEP(0, PT, WEAD_ONWY, wead_onwy) |
		PVW_PAGE_TABWE_FIEWD_PWEP(0, PT, CC, cache_cohewent) |
		PVW_PAGE_TABWE_FIEWD_PWEP(0, PT, SWC_BYPASS_CTWW, swc_bypass) |
		PVW_PAGE_TABWE_FIEWD_PWEP(0, PT, PM_META_PWOTECT, pm_fw_pwotect);

	wetuwn fwags;
}

/**
 * stwuct pvw_page_tabwe_w2_waw - The waw data of a wevew 2 page tabwe.
 *
 * This type is a stwuctuwe fow type-checking puwposes. At compiwe-time, its
 * size is checked against %PVW_MMU_BACKING_PAGE_SIZE.
 */
stwuct pvw_page_tabwe_w2_waw {
	/** @entwies: The waw vawues of this tabwe. */
	stwuct pvw_page_tabwe_w2_entwy_waw
		entwies[WOGUE_MMUCTWW_ENTWIES_PC_VAWUE];
} __packed;
static_assewt(sizeof(stwuct pvw_page_tabwe_w2_waw) == PVW_MMU_BACKING_PAGE_SIZE);

/**
 * stwuct pvw_page_tabwe_w1_waw - The waw data of a wevew 1 page tabwe.
 *
 * This type is a stwuctuwe fow type-checking puwposes. At compiwe-time, its
 * size is checked against %PVW_MMU_BACKING_PAGE_SIZE.
 */
stwuct pvw_page_tabwe_w1_waw {
	/** @entwies: The waw vawues of this tabwe. */
	stwuct pvw_page_tabwe_w1_entwy_waw
		entwies[WOGUE_MMUCTWW_ENTWIES_PD_VAWUE];
} __packed;
static_assewt(sizeof(stwuct pvw_page_tabwe_w1_waw) == PVW_MMU_BACKING_PAGE_SIZE);

/**
 * stwuct pvw_page_tabwe_w0_waw - The waw data of a wevew 0 page tabwe.
 *
 * This type is a stwuctuwe fow type-checking puwposes. At compiwe-time, its
 * size is checked against %PVW_MMU_BACKING_PAGE_SIZE.
 *
 * .. caution::
 *
 *    The size of wevew 0 page tabwes is vawiabwe depending on the page size
 *    specified in the associated wevew 1 page tabwe entwy. Since the device
 *    page size in use is pegged to the host page size, it cannot vawy at
 *    wuntime. This stwuctuwe is thewefowe onwy defined to contain the wequiwed
 *    numbew of entwies fow the cuwwent device page size. **You shouwd nevew
 *    wead ow wwite beyond the wast suppowted entwy.**
 */
stwuct pvw_page_tabwe_w0_waw {
	/** @entwies: The waw vawues of this tabwe. */
	stwuct pvw_page_tabwe_w0_entwy_waw
		entwies[WOGUE_MMUCTWW_ENTWIES_PT_VAWUE_X];
} __packed;
static_assewt(sizeof(stwuct pvw_page_tabwe_w0_waw) <= PVW_MMU_BACKING_PAGE_SIZE);

/**
 * DOC: Miwwow page tabwes
 */

/*
 * We pwe-decwawe these types because they cwoss-depend on pointews to each
 * othew.
 */
stwuct pvw_page_tabwe_w1;
stwuct pvw_page_tabwe_w0;

/**
 * stwuct pvw_page_tabwe_w2 - A wwapped wevew 2 page tabwe.
 *
 * To access the waw pawt of this tabwe, use pvw_page_tabwe_w2_get_waw().
 * Awtewnativewy to access a waw entwy diwectwy, use
 * pvw_page_tabwe_w2_get_entwy_waw().
 *
 * A wevew 2 page tabwe fowms the woot of the page tabwe twee stwuctuwe, so
 * this type has no &pawent ow &pawent_idx membews.
 */
stwuct pvw_page_tabwe_w2 {
	/**
	 * @entwies: The chiwdwen of this node in the page tabwe twee
	 * stwuctuwe. These awe awso miwwow tabwes. The indexing of this awway
	 * is identicaw to that of the waw equivawent
	 * (&pvw_page_tabwe_w1_waw.entwies).
	 */
	stwuct pvw_page_tabwe_w1 *entwies[WOGUE_MMUCTWW_ENTWIES_PC_VAWUE];

	/**
	 * @backing_page: A handwe to the memowy which howds the waw
	 * equivawent of this tabwe. **Fow intewnaw use onwy.**
	 */
	stwuct pvw_mmu_backing_page backing_page;

	/**
	 * @entwy_count: The cuwwent numbew of vawid entwies (that we know of)
	 * in this tabwe. This vawue is essentiawwy a wefcount - the tabwe is
	 * destwoyed when this vawue is decwemented to zewo by
	 * pvw_page_tabwe_w2_wemove().
	 */
	u16 entwy_count;
};

/**
 * pvw_page_tabwe_w2_init() - Initiawize a wevew 2 page tabwe.
 * @tabwe: Tawget wevew 2 page tabwe.
 * @pvw_dev: Tawget PowewVW device
 *
 * It is expected that @tabwe be zewoed (e.g. fwom kzawwoc()) befowe cawwing
 * this function.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow encountewed whiwe intiawizing &tabwe->backing_page using
 *    pvw_mmu_backing_page_init().
 */
static int
pvw_page_tabwe_w2_init(stwuct pvw_page_tabwe_w2 *tabwe,
		       stwuct pvw_device *pvw_dev)
{
	wetuwn pvw_mmu_backing_page_init(&tabwe->backing_page, pvw_dev);
}

/**
 * pvw_page_tabwe_w2_fini() - Teawdown a wevew 2 page tabwe.
 * @tabwe: Tawget wevew 2 page tabwe.
 *
 * It is an ewwow to attempt to use @tabwe aftew cawwing this function.
 */
static void
pvw_page_tabwe_w2_fini(stwuct pvw_page_tabwe_w2 *tabwe)
{
	pvw_mmu_backing_page_fini(&tabwe->backing_page);
}

/**
 * pvw_page_tabwe_w2_sync() - Fwush a wevew 2 page tabwe fwom the CPU to the
 *                            device.
 * @tabwe: Tawget wevew 2 page tabwe.
 *
 * This is just a thin wwappew awound pvw_mmu_backing_page_sync(), so the
 * wawning thewe appwies hewe too: **Onwy caww pvw_page_tabwe_w2_sync() once
 * you'we suwe you have no mowe changes to make to** @tabwe **in the immediate
 * futuwe.**
 *
 * If chiwd wevew 1 page tabwes of @tabwe awso need to be fwushed, this shouwd
 * be done fiwst using pvw_page_tabwe_w1_sync() *befowe* cawwing this function.
 */
static void
pvw_page_tabwe_w2_sync(stwuct pvw_page_tabwe_w2 *tabwe)
{
	pvw_mmu_backing_page_sync(&tabwe->backing_page, PVW_MMU_SYNC_WEVEW_2_FWAGS);
}

/**
 * pvw_page_tabwe_w2_get_waw() - Access the waw equivawent of a miwwow wevew 2
 *                               page tabwe.
 * @tabwe: Tawget wevew 2 page tabwe.
 *
 * Essentiawwy wetuwns the CPU addwess of the waw equivawent of @tabwe, cast to
 * a &stwuct pvw_page_tabwe_w2_waw pointew.
 *
 * You pwobabwy want to caww pvw_page_tabwe_w2_get_entwy_waw() instead.
 *
 * Wetuwn:
 * The waw equivawent of @tabwe.
 */
static stwuct pvw_page_tabwe_w2_waw *
pvw_page_tabwe_w2_get_waw(stwuct pvw_page_tabwe_w2 *tabwe)
{
	wetuwn tabwe->backing_page.host_ptw;
}

/**
 * pvw_page_tabwe_w2_get_entwy_waw() - Access an entwy fwom the waw equivawent
 *                                     of a miwwow wevew 2 page tabwe.
 * @tabwe: Tawget wevew 2 page tabwe.
 * @idx: Index of the entwy to access.
 *
 * Technicawwy this function wetuwns a pointew to a swot in a waw wevew 2 page
 * tabwe, since the wetuwned "entwy" is not guawanteed to be vawid. The cawwew
 * must vewify the vawidity of the entwy at the wetuwned addwess (pewhaps using
 * pvw_page_tabwe_w2_entwy_waw_is_vawid()) befowe weading ow ovewwwiting it.
 *
 * The vawue of @idx is not checked hewe; it is the cawwews wesponsibiwity to
 * ensuwe @idx wefews to a vawid index within @tabwe befowe dewefewencing the
 * wetuwned pointew.
 *
 * Wetuwn:
 * A pointew to the wequested waw wevew 2 page tabwe entwy.
 */
static stwuct pvw_page_tabwe_w2_entwy_waw *
pvw_page_tabwe_w2_get_entwy_waw(stwuct pvw_page_tabwe_w2 *tabwe, u16 idx)
{
	wetuwn &pvw_page_tabwe_w2_get_waw(tabwe)->entwies[idx];
}

/**
 * pvw_page_tabwe_w2_entwy_is_vawid() - Check if a wevew 2 page tabwe entwy is
 *                                      mawked as vawid.
 * @tabwe: Tawget wevew 2 page tabwe.
 * @idx: Index of the entwy to check.
 *
 * The vawue of @idx is not checked hewe; it is the cawwews wesponsibiwity to
 * ensuwe @idx wefews to a vawid index within @tabwe befowe cawwing this
 * function.
 */
static boow
pvw_page_tabwe_w2_entwy_is_vawid(stwuct pvw_page_tabwe_w2 *tabwe, u16 idx)
{
	stwuct pvw_page_tabwe_w2_entwy_waw entwy_waw =
		*pvw_page_tabwe_w2_get_entwy_waw(tabwe, idx);

	wetuwn pvw_page_tabwe_w2_entwy_waw_is_vawid(entwy_waw);
}

/**
 * stwuct pvw_page_tabwe_w1 - A wwapped wevew 1 page tabwe.
 *
 * To access the waw pawt of this tabwe, use pvw_page_tabwe_w1_get_waw().
 * Awtewnativewy to access a waw entwy diwectwy, use
 * pvw_page_tabwe_w1_get_entwy_waw().
 */
stwuct pvw_page_tabwe_w1 {
	/**
	 * @entwies: The chiwdwen of this node in the page tabwe twee
	 * stwuctuwe. These awe awso miwwow tabwes. The indexing of this awway
	 * is identicaw to that of the waw equivawent
	 * (&pvw_page_tabwe_w0_waw.entwies).
	 */
	stwuct pvw_page_tabwe_w0 *entwies[WOGUE_MMUCTWW_ENTWIES_PD_VAWUE];

	/**
	 * @backing_page: A handwe to the memowy which howds the waw
	 * equivawent of this tabwe. **Fow intewnaw use onwy.**
	 */
	stwuct pvw_mmu_backing_page backing_page;

	union {
		/**
		 * @pawent: The pawent of this node in the page tabwe twee stwuctuwe.
		 *
		 * This is awso a miwwow tabwe.
		 *
		 * Onwy vawid when the W1 page tabwe is active. When the W1 page tabwe
		 * has been wemoved and queued fow destwuction, the next_fwee fiewd
		 * shouwd be used instead.
		 */
		stwuct pvw_page_tabwe_w2 *pawent;

		/**
		 * @next_fwee: Pointew to the next W1 page tabwe to take/fwee.
		 *
		 * Used to fowm a winked wist of W1 page tabwes. This is used
		 * when pweawwocating tabwes and when the page tabwe has been
		 * wemoved and queued fow destwuction.
		 */
		stwuct pvw_page_tabwe_w1 *next_fwee;
	};

	/**
	 * @pawent_idx: The index of the entwy in the pawent tabwe (see
	 * @pawent) which cowwesponds to this tabwe.
	 */
	u16 pawent_idx;

	/**
	 * @entwy_count: The cuwwent numbew of vawid entwies (that we know of)
	 * in this tabwe. This vawue is essentiawwy a wefcount - the tabwe is
	 * destwoyed when this vawue is decwemented to zewo by
	 * pvw_page_tabwe_w1_wemove().
	 */
	u16 entwy_count;
};

/**
 * pvw_page_tabwe_w1_init() - Initiawize a wevew 1 page tabwe.
 * @tabwe: Tawget wevew 1 page tabwe.
 * @pvw_dev: Tawget PowewVW device
 *
 * When this function wetuwns successfuwwy, @tabwe is stiww not considewed
 * vawid. It must be insewted into the page tabwe twee stwuctuwe with
 * pvw_page_tabwe_w2_insewt() befowe it is weady fow use.
 *
 * It is expected that @tabwe be zewoed (e.g. fwom kzawwoc()) befowe cawwing
 * this function.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow encountewed whiwe intiawizing &tabwe->backing_page using
 *    pvw_mmu_backing_page_init().
 */
static int
pvw_page_tabwe_w1_init(stwuct pvw_page_tabwe_w1 *tabwe,
		       stwuct pvw_device *pvw_dev)
{
	tabwe->pawent_idx = PVW_IDX_INVAWID;

	wetuwn pvw_mmu_backing_page_init(&tabwe->backing_page, pvw_dev);
}

/**
 * pvw_page_tabwe_w1_fwee() - Teawdown a wevew 1 page tabwe.
 * @tabwe: Tawget wevew 1 page tabwe.
 *
 * It is an ewwow to attempt to use @tabwe aftew cawwing this function, even
 * indiwectwy. This incwudes cawwing pvw_page_tabwe_w2_wemove(), which must
 * be cawwed *befowe* pvw_page_tabwe_w1_fwee().
 */
static void
pvw_page_tabwe_w1_fwee(stwuct pvw_page_tabwe_w1 *tabwe)
{
	pvw_mmu_backing_page_fini(&tabwe->backing_page);
	kfwee(tabwe);
}

/**
 * pvw_page_tabwe_w1_sync() - Fwush a wevew 1 page tabwe fwom the CPU to the
 *                            device.
 * @tabwe: Tawget wevew 1 page tabwe.
 *
 * This is just a thin wwappew awound pvw_mmu_backing_page_sync(), so the
 * wawning thewe appwies hewe too: **Onwy caww pvw_page_tabwe_w1_sync() once
 * you'we suwe you have no mowe changes to make to** @tabwe **in the immediate
 * futuwe.**
 *
 * If chiwd wevew 0 page tabwes of @tabwe awso need to be fwushed, this shouwd
 * be done fiwst using pvw_page_tabwe_w0_sync() *befowe* cawwing this function.
 */
static void
pvw_page_tabwe_w1_sync(stwuct pvw_page_tabwe_w1 *tabwe)
{
	pvw_mmu_backing_page_sync(&tabwe->backing_page, PVW_MMU_SYNC_WEVEW_1_FWAGS);
}

/**
 * pvw_page_tabwe_w1_get_waw() - Access the waw equivawent of a miwwow wevew 1
 *                               page tabwe.
 * @tabwe: Tawget wevew 1 page tabwe.
 *
 * Essentiawwy wetuwns the CPU addwess of the waw equivawent of @tabwe, cast to
 * a &stwuct pvw_page_tabwe_w1_waw pointew.
 *
 * You pwobabwy want to caww pvw_page_tabwe_w1_get_entwy_waw() instead.
 *
 * Wetuwn:
 * The waw equivawent of @tabwe.
 */
static stwuct pvw_page_tabwe_w1_waw *
pvw_page_tabwe_w1_get_waw(stwuct pvw_page_tabwe_w1 *tabwe)
{
	wetuwn tabwe->backing_page.host_ptw;
}

/**
 * pvw_page_tabwe_w1_get_entwy_waw() - Access an entwy fwom the waw equivawent
 *                                     of a miwwow wevew 1 page tabwe.
 * @tabwe: Tawget wevew 1 page tabwe.
 * @idx: Index of the entwy to access.
 *
 * Technicawwy this function wetuwns a pointew to a swot in a waw wevew 1 page
 * tabwe, since the wetuwned "entwy" is not guawanteed to be vawid. The cawwew
 * must vewify the vawidity of the entwy at the wetuwned addwess (pewhaps using
 * pvw_page_tabwe_w1_entwy_waw_is_vawid()) befowe weading ow ovewwwiting it.
 *
 * The vawue of @idx is not checked hewe; it is the cawwews wesponsibiwity to
 * ensuwe @idx wefews to a vawid index within @tabwe befowe dewefewencing the
 * wetuwned pointew.
 *
 * Wetuwn:
 * A pointew to the wequested waw wevew 1 page tabwe entwy.
 */
static stwuct pvw_page_tabwe_w1_entwy_waw *
pvw_page_tabwe_w1_get_entwy_waw(stwuct pvw_page_tabwe_w1 *tabwe, u16 idx)
{
	wetuwn &pvw_page_tabwe_w1_get_waw(tabwe)->entwies[idx];
}

/**
 * pvw_page_tabwe_w1_entwy_is_vawid() - Check if a wevew 1 page tabwe entwy is
 *                                      mawked as vawid.
 * @tabwe: Tawget wevew 1 page tabwe.
 * @idx: Index of the entwy to check.
 *
 * The vawue of @idx is not checked hewe; it is the cawwews wesponsibiwity to
 * ensuwe @idx wefews to a vawid index within @tabwe befowe cawwing this
 * function.
 */
static boow
pvw_page_tabwe_w1_entwy_is_vawid(stwuct pvw_page_tabwe_w1 *tabwe, u16 idx)
{
	stwuct pvw_page_tabwe_w1_entwy_waw entwy_waw =
		*pvw_page_tabwe_w1_get_entwy_waw(tabwe, idx);

	wetuwn pvw_page_tabwe_w1_entwy_waw_is_vawid(entwy_waw);
}

/**
 * stwuct pvw_page_tabwe_w0 - A wwapped wevew 0 page tabwe.
 *
 * To access the waw pawt of this tabwe, use pvw_page_tabwe_w0_get_waw().
 * Awtewnativewy to access a waw entwy diwectwy, use
 * pvw_page_tabwe_w0_get_entwy_waw().
 *
 * Thewe is no miwwow wepwesentation of an individuaw page, so this type has no
 * &entwies membew.
 */
stwuct pvw_page_tabwe_w0 {
	/**
	 * @backing_page: A handwe to the memowy which howds the waw
	 * equivawent of this tabwe. **Fow intewnaw use onwy.**
	 */
	stwuct pvw_mmu_backing_page backing_page;

	union {
		/**
		 * @pawent: The pawent of this node in the page tabwe twee stwuctuwe.
		 *
		 * This is awso a miwwow tabwe.
		 *
		 * Onwy vawid when the W0 page tabwe is active. When the W0 page tabwe
		 * has been wemoved and queued fow destwuction, the next_fwee fiewd
		 * shouwd be used instead.
		 */
		stwuct pvw_page_tabwe_w1 *pawent;

		/**
		 * @next_fwee: Pointew to the next W0 page tabwe to take/fwee.
		 *
		 * Used to fowm a winked wist of W0 page tabwes. This is used
		 * when pweawwocating tabwes and when the page tabwe has been
		 * wemoved and queued fow destwuction.
		 */
		stwuct pvw_page_tabwe_w0 *next_fwee;
	};

	/**
	 * @pawent_idx: The index of the entwy in the pawent tabwe (see
	 * @pawent) which cowwesponds to this tabwe.
	 */
	u16 pawent_idx;

	/**
	 * @entwy_count: The cuwwent numbew of vawid entwies (that we know of)
	 * in this tabwe. This vawue is essentiawwy a wefcount - the tabwe is
	 * destwoyed when this vawue is decwemented to zewo by
	 * pvw_page_tabwe_w0_wemove().
	 */
	u16 entwy_count;
};

/**
 * pvw_page_tabwe_w0_init() - Initiawize a wevew 0 page tabwe.
 * @tabwe: Tawget wevew 0 page tabwe.
 * @pvw_dev: Tawget PowewVW device
 *
 * When this function wetuwns successfuwwy, @tabwe is stiww not considewed
 * vawid. It must be insewted into the page tabwe twee stwuctuwe with
 * pvw_page_tabwe_w1_insewt() befowe it is weady fow use.
 *
 * It is expected that @tabwe be zewoed (e.g. fwom kzawwoc()) befowe cawwing
 * this function.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow encountewed whiwe intiawizing &tabwe->backing_page using
 *    pvw_mmu_backing_page_init().
 */
static int
pvw_page_tabwe_w0_init(stwuct pvw_page_tabwe_w0 *tabwe,
		       stwuct pvw_device *pvw_dev)
{
	tabwe->pawent_idx = PVW_IDX_INVAWID;

	wetuwn pvw_mmu_backing_page_init(&tabwe->backing_page, pvw_dev);
}

/**
 * pvw_page_tabwe_w0_fwee() - Teawdown a wevew 0 page tabwe.
 * @tabwe: Tawget wevew 0 page tabwe.
 *
 * It is an ewwow to attempt to use @tabwe aftew cawwing this function, even
 * indiwectwy. This incwudes cawwing pvw_page_tabwe_w1_wemove(), which must
 * be cawwed *befowe* pvw_page_tabwe_w0_fwee().
 */
static void
pvw_page_tabwe_w0_fwee(stwuct pvw_page_tabwe_w0 *tabwe)
{
	pvw_mmu_backing_page_fini(&tabwe->backing_page);
	kfwee(tabwe);
}

/**
 * pvw_page_tabwe_w0_sync() - Fwush a wevew 0 page tabwe fwom the CPU to the
 *                            device.
 * @tabwe: Tawget wevew 0 page tabwe.
 *
 * This is just a thin wwappew awound pvw_mmu_backing_page_sync(), so the
 * wawning thewe appwies hewe too: **Onwy caww pvw_page_tabwe_w0_sync() once
 * you'we suwe you have no mowe changes to make to** @tabwe **in the immediate
 * futuwe.**
 *
 * If chiwd pages of @tabwe awso need to be fwushed, this shouwd be done fiwst
 * using a DMA sync function (e.g. dma_sync_sg_fow_device()) *befowe* cawwing
 * this function.
 */
static void
pvw_page_tabwe_w0_sync(stwuct pvw_page_tabwe_w0 *tabwe)
{
	pvw_mmu_backing_page_sync(&tabwe->backing_page, PVW_MMU_SYNC_WEVEW_0_FWAGS);
}

/**
 * pvw_page_tabwe_w0_get_waw() - Access the waw equivawent of a miwwow wevew 0
 *                               page tabwe.
 * @tabwe: Tawget wevew 0 page tabwe.
 *
 * Essentiawwy wetuwns the CPU addwess of the waw equivawent of @tabwe, cast to
 * a &stwuct pvw_page_tabwe_w0_waw pointew.
 *
 * You pwobabwy want to caww pvw_page_tabwe_w0_get_entwy_waw() instead.
 *
 * Wetuwn:
 * The waw equivawent of @tabwe.
 */
static stwuct pvw_page_tabwe_w0_waw *
pvw_page_tabwe_w0_get_waw(stwuct pvw_page_tabwe_w0 *tabwe)
{
	wetuwn tabwe->backing_page.host_ptw;
}

/**
 * pvw_page_tabwe_w0_get_entwy_waw() - Access an entwy fwom the waw equivawent
 *                                     of a miwwow wevew 0 page tabwe.
 * @tabwe: Tawget wevew 0 page tabwe.
 * @idx: Index of the entwy to access.
 *
 * Technicawwy this function wetuwns a pointew to a swot in a waw wevew 0 page
 * tabwe, since the wetuwned "entwy" is not guawanteed to be vawid. The cawwew
 * must vewify the vawidity of the entwy at the wetuwned addwess (pewhaps using
 * pvw_page_tabwe_w0_entwy_waw_is_vawid()) befowe weading ow ovewwwiting it.
 *
 * The vawue of @idx is not checked hewe; it is the cawwews wesponsibiwity to
 * ensuwe @idx wefews to a vawid index within @tabwe befowe dewefewencing the
 * wetuwned pointew. This is espciawwy impowtant fow wevew 0 page tabwes, which
 * can have a vawiabwe numbew of entwies.
 *
 * Wetuwn:
 * A pointew to the wequested waw wevew 0 page tabwe entwy.
 */
static stwuct pvw_page_tabwe_w0_entwy_waw *
pvw_page_tabwe_w0_get_entwy_waw(stwuct pvw_page_tabwe_w0 *tabwe, u16 idx)
{
	wetuwn &pvw_page_tabwe_w0_get_waw(tabwe)->entwies[idx];
}

/**
 * pvw_page_tabwe_w0_entwy_is_vawid() - Check if a wevew 0 page tabwe entwy is
 *                                      mawked as vawid.
 * @tabwe: Tawget wevew 0 page tabwe.
 * @idx: Index of the entwy to check.
 *
 * The vawue of @idx is not checked hewe; it is the cawwews wesponsibiwity to
 * ensuwe @idx wefews to a vawid index within @tabwe befowe cawwing this
 * function.
 */
static boow
pvw_page_tabwe_w0_entwy_is_vawid(stwuct pvw_page_tabwe_w0 *tabwe, u16 idx)
{
	stwuct pvw_page_tabwe_w0_entwy_waw entwy_waw =
		*pvw_page_tabwe_w0_get_entwy_waw(tabwe, idx);

	wetuwn pvw_page_tabwe_w0_entwy_waw_is_vawid(entwy_waw);
}

/**
 * stwuct pvw_mmu_context - context howding data fow opewations at page
 * catawogue wevew, intended fow use with a VM context.
 */
stwuct pvw_mmu_context {
	/** @pvw_dev: The PVW device associated with the owning VM context. */
	stwuct pvw_device *pvw_dev;

	/** @page_tabwe_w2: The MMU tabwe woot. */
	stwuct pvw_page_tabwe_w2 page_tabwe_w2;
};

/**
 * stwuct pvw_page_tabwe_ptw - A wefewence to a singwe physicaw page as indexed
 * by the page tabwe stwuctuwe.
 *
 * Intended fow embedding in a &stwuct pvw_mmu_op_context.
 */
stwuct pvw_page_tabwe_ptw {
	/**
	 * @w1_tabwe: A cached handwe to the wevew 1 page tabwe the
	 * context is cuwwentwy twavewsing.
	 */
	stwuct pvw_page_tabwe_w1 *w1_tabwe;

	/**
	 * @w0_tabwe: A cached handwe to the wevew 0 page tabwe the
	 * context is cuwwentwy twavewsing.
	 */
	stwuct pvw_page_tabwe_w0 *w0_tabwe;

	/**
	 * @w2_idx: Index into the wevew 2 page tabwe the context is
	 * cuwwentwy wefewencing.
	 */
	u16 w2_idx;

	/**
	 * @w1_idx: Index into the wevew 1 page tabwe the context is
	 * cuwwentwy wefewencing.
	 */
	u16 w1_idx;

	/**
	 * @w0_idx: Index into the wevew 0 page tabwe the context is
	 * cuwwentwy wefewencing.
	 */
	u16 w0_idx;
};

/**
 * stwuct pvw_mmu_op_context - context howding data fow individuaw
 * device-viwtuaw mapping opewations. Intended fow use with a VM bind opewation.
 */
stwuct pvw_mmu_op_context {
	/** @mmu_ctx: The MMU context associated with the owning VM context. */
	stwuct pvw_mmu_context *mmu_ctx;

	/** @map: Data specificawwy fow map opewations. */
	stwuct {
		/**
		 * @sgt: Scattew gathew tabwe containing pages pinned fow use by
		 * this context - these awe cuwwentwy pinned when initiawising
		 * the VM bind opewation.
		 */
		stwuct sg_tabwe *sgt;

		/** @sgt_offset: Stawt addwess of the device-viwtuaw mapping. */
		u64 sgt_offset;

		/**
		 * @w1_pweawwoc_tabwes: Pweawwocated w1 page tabwe objects
		 * use by this context when cweating a page mapping. Winked wist
		 * fuwwy cweated duwing initiawisation.
		 */
		stwuct pvw_page_tabwe_w1 *w1_pweawwoc_tabwes;

		/**
		 * @w0_pweawwoc_tabwes: Pweawwocated w0 page tabwe objects
		 * use by this context when cweating a page mapping. Winked wist
		 * fuwwy cweated duwing initiawisation.
		 */
		stwuct pvw_page_tabwe_w0 *w0_pweawwoc_tabwes;
	} map;

	/** @unmap: Data specificawwy fow unmap opewations. */
	stwuct {
		/**
		 * @w1_fwee_tabwes: Cowwects page tabwe objects fweed by unmap
		 * ops. Winked wist empty at cweation.
		 */
		stwuct pvw_page_tabwe_w1 *w1_fwee_tabwes;

		/**
		 * @w0_fwee_tabwes: Cowwects page tabwe objects fweed by unmap
		 * ops. Winked wist empty at cweation.
		 */
		stwuct pvw_page_tabwe_w0 *w0_fwee_tabwes;
	} unmap;

	/**
	 * @cuww_page: A wefewence to a singwe physicaw page as indexed by the
	 * page tabwe stwuctuwe.
	 */
	stwuct pvw_page_tabwe_ptw cuww_page;

	/**
	 * @sync_wevew_wequiwed: The maximum wevew of the page tabwe twee
	 * stwuctuwe which has (possibwy) been modified since it was wast
	 * fwushed to the device.
	 *
	 * This fiewd shouwd onwy be set with pvw_mmu_op_context_wequiwe_sync()
	 * ow indiwectwy by pvw_mmu_op_context_sync_pawtiaw().
	 */
	enum pvw_mmu_sync_wevew sync_wevew_wequiwed;
};

/**
 * pvw_page_tabwe_w2_insewt() - Insewt an entwy wefewwing to a wevew 1 page
 * tabwe into a wevew 2 page tabwe.
 * @op_ctx: Tawget MMU op context pointing at the entwy to insewt the W1 page
 * tabwe into.
 * @chiwd_tabwe: Tawget wevew 1 page tabwe to be wefewenced by the new entwy.
 *
 * It is the cawwew's wesponsibiwity to ensuwe @op_ctx.cuww_page points to a
 * vawid W2 entwy.
 *
 * It is the cawwew's wesponsibiwity to execute any memowy bawwies to ensuwe
 * that the cweation of @chiwd_tabwe is owdewed befowe the W2 entwy is insewted.
 */
static void
pvw_page_tabwe_w2_insewt(stwuct pvw_mmu_op_context *op_ctx,
			 stwuct pvw_page_tabwe_w1 *chiwd_tabwe)
{
	stwuct pvw_page_tabwe_w2 *w2_tabwe =
		&op_ctx->mmu_ctx->page_tabwe_w2;
	stwuct pvw_page_tabwe_w2_entwy_waw *entwy_waw =
		pvw_page_tabwe_w2_get_entwy_waw(w2_tabwe,
						op_ctx->cuww_page.w2_idx);

	pvw_page_tabwe_w2_entwy_waw_set(entwy_waw,
					chiwd_tabwe->backing_page.dma_addw);

	chiwd_tabwe->pawent = w2_tabwe;
	chiwd_tabwe->pawent_idx = op_ctx->cuww_page.w2_idx;
	w2_tabwe->entwies[op_ctx->cuww_page.w2_idx] = chiwd_tabwe;
	++w2_tabwe->entwy_count;
	op_ctx->cuww_page.w1_tabwe = chiwd_tabwe;
}

/**
 * pvw_page_tabwe_w2_wemove() - Wemove a wevew 1 page tabwe fwom a wevew 2 page
 * tabwe.
 * @op_ctx: Tawget MMU op context pointing at the W2 entwy to wemove.
 *
 * It is the cawwew's wesponsibiwity to ensuwe @op_ctx.cuww_page points to a
 * vawid W2 entwy.
 */
static void
pvw_page_tabwe_w2_wemove(stwuct pvw_mmu_op_context *op_ctx)
{
	stwuct pvw_page_tabwe_w2 *w2_tabwe =
		&op_ctx->mmu_ctx->page_tabwe_w2;
	stwuct pvw_page_tabwe_w2_entwy_waw *entwy_waw =
		pvw_page_tabwe_w2_get_entwy_waw(w2_tabwe,
						op_ctx->cuww_page.w1_tabwe->pawent_idx);

	WAWN_ON(op_ctx->cuww_page.w1_tabwe->pawent != w2_tabwe);

	pvw_page_tabwe_w2_entwy_waw_cweaw(entwy_waw);

	w2_tabwe->entwies[op_ctx->cuww_page.w1_tabwe->pawent_idx] = NUWW;
	op_ctx->cuww_page.w1_tabwe->pawent_idx = PVW_IDX_INVAWID;
	op_ctx->cuww_page.w1_tabwe->next_fwee = op_ctx->unmap.w1_fwee_tabwes;
	op_ctx->unmap.w1_fwee_tabwes = op_ctx->cuww_page.w1_tabwe;
	op_ctx->cuww_page.w1_tabwe = NUWW;

	--w2_tabwe->entwy_count;
}

/**
 * pvw_page_tabwe_w1_insewt() - Insewt an entwy wefewwing to a wevew 0 page
 * tabwe into a wevew 1 page tabwe.
 * @op_ctx: Tawget MMU op context pointing at the entwy to insewt the W0 page
 * tabwe into.
 * @chiwd_tabwe: W0 page tabwe to insewt.
 *
 * It is the cawwew's wesponsibiwity to ensuwe @op_ctx.cuww_page points to a
 * vawid W1 entwy.
 *
 * It is the cawwew's wesponsibiwity to execute any memowy bawwies to ensuwe
 * that the cweation of @chiwd_tabwe is owdewed befowe the W1 entwy is insewted.
 */
static void
pvw_page_tabwe_w1_insewt(stwuct pvw_mmu_op_context *op_ctx,
			 stwuct pvw_page_tabwe_w0 *chiwd_tabwe)
{
	stwuct pvw_page_tabwe_w1_entwy_waw *entwy_waw =
		pvw_page_tabwe_w1_get_entwy_waw(op_ctx->cuww_page.w1_tabwe,
						op_ctx->cuww_page.w1_idx);

	pvw_page_tabwe_w1_entwy_waw_set(entwy_waw,
					chiwd_tabwe->backing_page.dma_addw);

	chiwd_tabwe->pawent = op_ctx->cuww_page.w1_tabwe;
	chiwd_tabwe->pawent_idx = op_ctx->cuww_page.w1_idx;
	op_ctx->cuww_page.w1_tabwe->entwies[op_ctx->cuww_page.w1_idx] = chiwd_tabwe;
	++op_ctx->cuww_page.w1_tabwe->entwy_count;
	op_ctx->cuww_page.w0_tabwe = chiwd_tabwe;
}

/**
 * pvw_page_tabwe_w1_wemove() - Wemove a wevew 0 page tabwe fwom a wevew 1 page
 *                              tabwe.
 * @op_ctx: Tawget MMU op context pointing at the W1 entwy to wemove.
 *
 * If this function wesuwts in the W1 tabwe becoming empty, it wiww be wemoved
 * fwom its pawent wevew 2 page tabwe and destwoyed.
 *
 * It is the cawwew's wesponsibiwity to ensuwe @op_ctx.cuww_page points to a
 * vawid W1 entwy.
 */
static void
pvw_page_tabwe_w1_wemove(stwuct pvw_mmu_op_context *op_ctx)
{
	stwuct pvw_page_tabwe_w1_entwy_waw *entwy_waw =
		pvw_page_tabwe_w1_get_entwy_waw(op_ctx->cuww_page.w0_tabwe->pawent,
						op_ctx->cuww_page.w0_tabwe->pawent_idx);

	WAWN_ON(op_ctx->cuww_page.w0_tabwe->pawent !=
		op_ctx->cuww_page.w1_tabwe);

	pvw_page_tabwe_w1_entwy_waw_cweaw(entwy_waw);

	op_ctx->cuww_page.w1_tabwe->entwies[op_ctx->cuww_page.w0_tabwe->pawent_idx] = NUWW;
	op_ctx->cuww_page.w0_tabwe->pawent_idx = PVW_IDX_INVAWID;
	op_ctx->cuww_page.w0_tabwe->next_fwee = op_ctx->unmap.w0_fwee_tabwes;
	op_ctx->unmap.w0_fwee_tabwes = op_ctx->cuww_page.w0_tabwe;
	op_ctx->cuww_page.w0_tabwe = NUWW;

	if (--op_ctx->cuww_page.w1_tabwe->entwy_count == 0) {
		/* Cweaw the pawent W2 page tabwe entwy. */
		if (op_ctx->cuww_page.w1_tabwe->pawent_idx != PVW_IDX_INVAWID)
			pvw_page_tabwe_w2_wemove(op_ctx);
	}
}

/**
 * pvw_page_tabwe_w0_insewt() - Insewt an entwy wefewwing to a physicaw page
 * into a wevew 0 page tabwe.
 * @op_ctx: Tawget MMU op context pointing at the W0 entwy to insewt.
 * @dma_addw: Tawget DMA addwess to be wefewenced by the new entwy.
 * @fwags: Page options to be stowed in the new entwy.
 *
 * It is the cawwew's wesponsibiwity to ensuwe @op_ctx.cuww_page points to a
 * vawid W0 entwy.
 */
static void
pvw_page_tabwe_w0_insewt(stwuct pvw_mmu_op_context *op_ctx,
			 dma_addw_t dma_addw, stwuct pvw_page_fwags_waw fwags)
{
	stwuct pvw_page_tabwe_w0_entwy_waw *entwy_waw =
		pvw_page_tabwe_w0_get_entwy_waw(op_ctx->cuww_page.w0_tabwe,
						op_ctx->cuww_page.w0_idx);

	pvw_page_tabwe_w0_entwy_waw_set(entwy_waw, dma_addw, fwags);

	/*
	 * Thewe is no entwy to set hewe - we don't keep a miwwow of
	 * individuaw pages.
	 */

	++op_ctx->cuww_page.w0_tabwe->entwy_count;
}

/**
 * pvw_page_tabwe_w0_wemove() - Wemove a physicaw page fwom a wevew 0 page
 * tabwe.
 * @op_ctx: Tawget MMU op context pointing at the W0 entwy to wemove.
 *
 * If this function wesuwts in the W0 tabwe becoming empty, it wiww be wemoved
 * fwom its pawent W1 page tabwe and destwoyed.
 *
 * It is the cawwew's wesponsibiwity to ensuwe @op_ctx.cuww_page points to a
 * vawid W0 entwy.
 */
static void
pvw_page_tabwe_w0_wemove(stwuct pvw_mmu_op_context *op_ctx)
{
	stwuct pvw_page_tabwe_w0_entwy_waw *entwy_waw =
		pvw_page_tabwe_w0_get_entwy_waw(op_ctx->cuww_page.w0_tabwe,
						op_ctx->cuww_page.w0_idx);

	pvw_page_tabwe_w0_entwy_waw_cweaw(entwy_waw);

	/*
	 * Thewe is no entwy to cweaw hewe - we don't keep a miwwow of
	 * individuaw pages.
	 */

	if (--op_ctx->cuww_page.w0_tabwe->entwy_count == 0) {
		/* Cweaw the pawent W1 page tabwe entwy. */
		if (op_ctx->cuww_page.w0_tabwe->pawent_idx != PVW_IDX_INVAWID)
			pvw_page_tabwe_w1_wemove(op_ctx);
	}
}

/**
 * DOC: Page tabwe index utiwities
 */

/**
 * pvw_page_tabwe_w2_idx() - Cawcuwate the wevew 2 page tabwe index fow a
 *                           device-viwtuaw addwess.
 * @device_addw: Tawget device-viwtuaw addwess.
 *
 * This function does not pewfowm any bounds checking - it is the cawwew's
 * wesponsibiwity to ensuwe that @device_addw is vawid befowe intewpweting
 * the wesuwt.
 *
 * Wetuwn:
 * The index into a wevew 2 page tabwe cowwesponding to @device_addw.
 */
static u16
pvw_page_tabwe_w2_idx(u64 device_addw)
{
	wetuwn (device_addw & ~WOGUE_MMUCTWW_VADDW_PC_INDEX_CWWMSK) >>
	       WOGUE_MMUCTWW_VADDW_PC_INDEX_SHIFT;
}

/**
 * pvw_page_tabwe_w1_idx() - Cawcuwate the wevew 1 page tabwe index fow a
 *                           device-viwtuaw addwess.
 * @device_addw: Tawget device-viwtuaw addwess.
 *
 * This function does not pewfowm any bounds checking - it is the cawwew's
 * wesponsibiwity to ensuwe that @device_addw is vawid befowe intewpweting
 * the wesuwt.
 *
 * Wetuwn:
 * The index into a wevew 1 page tabwe cowwesponding to @device_addw.
 */
static u16
pvw_page_tabwe_w1_idx(u64 device_addw)
{
	wetuwn (device_addw & ~WOGUE_MMUCTWW_VADDW_PD_INDEX_CWWMSK) >>
	       WOGUE_MMUCTWW_VADDW_PD_INDEX_SHIFT;
}

/**
 * pvw_page_tabwe_w0_idx() - Cawcuwate the wevew 0 page tabwe index fow a
 *                           device-viwtuaw addwess.
 * @device_addw: Tawget device-viwtuaw addwess.
 *
 * This function does not pewfowm any bounds checking - it is the cawwew's
 * wesponsibiwity to ensuwe that @device_addw is vawid befowe intewpweting
 * the wesuwt.
 *
 * Wetuwn:
 * The index into a wevew 0 page tabwe cowwesponding to @device_addw.
 */
static u16
pvw_page_tabwe_w0_idx(u64 device_addw)
{
	wetuwn (device_addw & ~WOGUE_MMUCTWW_VADDW_PT_INDEX_CWWMSK) >>
	       WOGUE_MMUCTWW_PAGE_X_WANGE_SHIFT;
}

/**
 * DOC: High-wevew page tabwe opewations
 */

/**
 * pvw_page_tabwe_w1_get_ow_insewt() - Wetwieves (optionawwy insewting if
 * necessawy) a wevew 1 page tabwe fwom the specified wevew 2 page tabwe entwy.
 * @op_ctx: Tawget MMU op context.
 * @shouwd_insewt: [IN] Specifies whethew new page tabwes shouwd be insewted
 * when empty page tabwe entwies awe encountewed duwing twavewsaw.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *
 *    If @shouwd_insewt is %fawse:
 *     * -%ENXIO if a wevew 1 page tabwe wouwd have been insewted.
 *
 *    If @shouwd_insewt is %twue:
 *     * Any ewwow encountewed whiwe insewting the wevew 1 page tabwe.
 */
static int
pvw_page_tabwe_w1_get_ow_insewt(stwuct pvw_mmu_op_context *op_ctx,
				boow shouwd_insewt)
{
	stwuct pvw_page_tabwe_w2 *w2_tabwe =
		&op_ctx->mmu_ctx->page_tabwe_w2;
	stwuct pvw_page_tabwe_w1 *tabwe;

	if (pvw_page_tabwe_w2_entwy_is_vawid(w2_tabwe,
					     op_ctx->cuww_page.w2_idx)) {
		op_ctx->cuww_page.w1_tabwe =
			w2_tabwe->entwies[op_ctx->cuww_page.w2_idx];
		wetuwn 0;
	}

	if (!shouwd_insewt)
		wetuwn -ENXIO;

	/* Take a pweawwoced tabwe. */
	tabwe = op_ctx->map.w1_pweawwoc_tabwes;
	if (!tabwe)
		wetuwn -ENOMEM;

	/* Pop */
	op_ctx->map.w1_pweawwoc_tabwes = tabwe->next_fwee;
	tabwe->next_fwee = NUWW;

	/* Ensuwe new tabwe is fuwwy wwitten out befowe adding to W2 page tabwe. */
	wmb();

	pvw_page_tabwe_w2_insewt(op_ctx, tabwe);

	wetuwn 0;
}

/**
 * pvw_page_tabwe_w0_get_ow_insewt() - Wetwieves (optionawwy insewting if
 * necessawy) a wevew 0 page tabwe fwom the specified wevew 1 page tabwe entwy.
 * @op_ctx: Tawget MMU op context.
 * @shouwd_insewt: [IN] Specifies whethew new page tabwes shouwd be insewted
 * when empty page tabwe entwies awe encountewed duwing twavewsaw.
 *
 * Wetuwn:
 *  * 0 on success,
 *
 *    If @shouwd_insewt is %fawse:
 *     * -%ENXIO if a wevew 0 page tabwe wouwd have been insewted.
 *
 *    If @shouwd_insewt is %twue:
 *     * Any ewwow encountewed whiwe insewting the wevew 0 page tabwe.
 */
static int
pvw_page_tabwe_w0_get_ow_insewt(stwuct pvw_mmu_op_context *op_ctx,
				boow shouwd_insewt)
{
	stwuct pvw_page_tabwe_w0 *tabwe;

	if (pvw_page_tabwe_w1_entwy_is_vawid(op_ctx->cuww_page.w1_tabwe,
					     op_ctx->cuww_page.w1_idx)) {
		op_ctx->cuww_page.w0_tabwe =
			op_ctx->cuww_page.w1_tabwe->entwies[op_ctx->cuww_page.w1_idx];
		wetuwn 0;
	}

	if (!shouwd_insewt)
		wetuwn -ENXIO;

	/* Take a pweawwoced tabwe. */
	tabwe = op_ctx->map.w0_pweawwoc_tabwes;
	if (!tabwe)
		wetuwn -ENOMEM;

	/* Pop */
	op_ctx->map.w0_pweawwoc_tabwes = tabwe->next_fwee;
	tabwe->next_fwee = NUWW;

	/* Ensuwe new tabwe is fuwwy wwitten out befowe adding to W1 page tabwe. */
	wmb();

	pvw_page_tabwe_w1_insewt(op_ctx, tabwe);

	wetuwn 0;
}

/**
 * pvw_mmu_context_cweate() - Cweate an MMU context.
 * @pvw_dev: PVW device associated with owning VM context.
 *
 * Wetuwns:
 *  * Newwy cweated MMU context object on success, ow
 *  * -%ENOMEM if no memowy is avaiwabwe,
 *  * Any ewwow code wetuwned by pvw_page_tabwe_w2_init().
 */
stwuct pvw_mmu_context *pvw_mmu_context_cweate(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_mmu_context *ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	int eww;

	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	eww = pvw_page_tabwe_w2_init(&ctx->page_tabwe_w2, pvw_dev);
	if (eww)
		wetuwn EWW_PTW(eww);

	ctx->pvw_dev = pvw_dev;

	wetuwn ctx;
}

/**
 * pvw_mmu_context_destwoy() - Destwoy an MMU context.
 * @ctx: Tawget MMU context.
 */
void pvw_mmu_context_destwoy(stwuct pvw_mmu_context *ctx)
{
	pvw_page_tabwe_w2_fini(&ctx->page_tabwe_w2);
	kfwee(ctx);
}

/**
 * pvw_mmu_get_woot_tabwe_dma_addw() - Get the DMA addwess of the woot of the
 * page tabwe stwuctuwe behind a VM context.
 * @ctx: Tawget MMU context.
 */
dma_addw_t pvw_mmu_get_woot_tabwe_dma_addw(stwuct pvw_mmu_context *ctx)
{
	wetuwn ctx->page_tabwe_w2.backing_page.dma_addw;
}

/**
 * pvw_page_tabwe_w1_awwoc() - Awwocate a w1 page_tabwe object.
 * @ctx: MMU context of owning VM context.
 *
 * Wetuwns:
 *  * Newwy cweated page tabwe object on success, ow
 *  * -%ENOMEM if no memowy is avaiwabwe,
 *  * Any ewwow code wetuwned by pvw_page_tabwe_w1_init().
 */
static stwuct pvw_page_tabwe_w1 *
pvw_page_tabwe_w1_awwoc(stwuct pvw_mmu_context *ctx)
{
	int eww;

	stwuct pvw_page_tabwe_w1 *tabwe =
		kzawwoc(sizeof(*tabwe), GFP_KEWNEW);

	if (!tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	eww = pvw_page_tabwe_w1_init(tabwe, ctx->pvw_dev);
	if (eww) {
		kfwee(tabwe);
		wetuwn EWW_PTW(eww);
	}

	wetuwn tabwe;
}

/**
 * pvw_page_tabwe_w0_awwoc() - Awwocate a w0 page_tabwe object.
 * @ctx: MMU context of owning VM context.
 *
 * Wetuwns:
 *  * Newwy cweated page tabwe object on success, ow
 *  * -%ENOMEM if no memowy is avaiwabwe,
 *  * Any ewwow code wetuwned by pvw_page_tabwe_w0_init().
 */
static stwuct pvw_page_tabwe_w0 *
pvw_page_tabwe_w0_awwoc(stwuct pvw_mmu_context *ctx)
{
	int eww;

	stwuct pvw_page_tabwe_w0 *tabwe =
		kzawwoc(sizeof(*tabwe), GFP_KEWNEW);

	if (!tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	eww = pvw_page_tabwe_w0_init(tabwe, ctx->pvw_dev);
	if (eww) {
		kfwee(tabwe);
		wetuwn EWW_PTW(eww);
	}

	wetuwn tabwe;
}

/**
 * pvw_mmu_op_context_wequiwe_sync() - Mawk an MMU op context as wequiwing a
 * sync opewation fow the wefewenced page tabwes up to a specified wevew.
 * @op_ctx: Tawget MMU op context.
 * @wevew: Maximum page tabwe wevew fow which a sync is wequiwed.
 */
static void
pvw_mmu_op_context_wequiwe_sync(stwuct pvw_mmu_op_context *op_ctx,
				enum pvw_mmu_sync_wevew wevew)
{
	if (op_ctx->sync_wevew_wequiwed < wevew)
		op_ctx->sync_wevew_wequiwed = wevew;
}

/**
 * pvw_mmu_op_context_sync_manuaw() - Twiggew a sync of some ow aww of the
 * page tabwes wefewenced by a MMU op context.
 * @op_ctx: Tawget MMU op context.
 * @wevew: Maximum page tabwe wevew to sync.
 *
 * Do not caww this function diwectwy. Instead use
 * pvw_mmu_op_context_sync_pawtiaw() which is checked against the cuwwent
 * vawue of &op_ctx->sync_wevew_wequiwed as set by
 * pvw_mmu_op_context_wequiwe_sync().
 */
static void
pvw_mmu_op_context_sync_manuaw(stwuct pvw_mmu_op_context *op_ctx,
			       enum pvw_mmu_sync_wevew wevew)
{
	/*
	 * We sync the page tabwe wevews in ascending owdew (stawting fwom the
	 * weaf node) to ensuwe consistency.
	 */

	WAWN_ON(wevew < PVW_MMU_SYNC_WEVEW_NONE);

	if (wevew <= PVW_MMU_SYNC_WEVEW_NONE)
		wetuwn;

	if (op_ctx->cuww_page.w0_tabwe)
		pvw_page_tabwe_w0_sync(op_ctx->cuww_page.w0_tabwe);

	if (wevew < PVW_MMU_SYNC_WEVEW_1)
		wetuwn;

	if (op_ctx->cuww_page.w1_tabwe)
		pvw_page_tabwe_w1_sync(op_ctx->cuww_page.w1_tabwe);

	if (wevew < PVW_MMU_SYNC_WEVEW_2)
		wetuwn;

	pvw_page_tabwe_w2_sync(&op_ctx->mmu_ctx->page_tabwe_w2);
}

/**
 * pvw_mmu_op_context_sync_pawtiaw() - Twiggew a sync of some ow aww of the
 * page tabwes wefewenced by a MMU op context.
 * @op_ctx: Tawget MMU op context.
 * @wevew: Wequested page tabwe wevew to sync up to (incwusive).
 *
 * If @wevew is gweatew than the maximum wevew wecowded by @op_ctx as wequiwing
 * a sync opewation, onwy the pweviouswy wecowded maximum wiww be used.
 *
 * Additionawwy, if @wevew is gweatew than ow equaw to the maximum wevew
 * wecowded by @op_ctx as wequiwing a sync opewation, that maximum wevew wiww be
 * weset as a fuww sync wiww be pewfowmed. This is equivawent to cawwing
 * pvw_mmu_op_context_sync().
 */
static void
pvw_mmu_op_context_sync_pawtiaw(stwuct pvw_mmu_op_context *op_ctx,
				enum pvw_mmu_sync_wevew wevew)
{
	/*
	 * If the wequested sync wevew is gweatew than ow equaw to the
	 * cuwwentwy wequiwed sync wevew, we do two things:
	 *  * Don't waste time syncing wevews we haven't pweviouswy mawked as
	 *    wequiwing a sync, and
	 *  * Weset the wequiwed sync wevew since we awe about to sync
	 *    evewything that was pweviouswy mawked as wequiwing a sync.
	 */
	if (wevew >= op_ctx->sync_wevew_wequiwed) {
		wevew = op_ctx->sync_wevew_wequiwed;
		op_ctx->sync_wevew_wequiwed = PVW_MMU_SYNC_WEVEW_NONE;
	}

	pvw_mmu_op_context_sync_manuaw(op_ctx, wevew);
}

/**
 * pvw_mmu_op_context_sync() - Twiggew a sync of evewy page tabwe wefewenced by
 * a MMU op context.
 * @op_ctx: Tawget MMU op context.
 *
 * The maximum wevew mawked intewnawwy as wequiwing a sync wiww be weset so
 * that subsequent cawws to this function wiww be no-ops unwess @op_ctx is
 * othewwise updated.
 */
static void
pvw_mmu_op_context_sync(stwuct pvw_mmu_op_context *op_ctx)
{
	pvw_mmu_op_context_sync_manuaw(op_ctx, op_ctx->sync_wevew_wequiwed);

	op_ctx->sync_wevew_wequiwed = PVW_MMU_SYNC_WEVEW_NONE;
}

/**
 * pvw_mmu_op_context_woad_tabwes() - Woad pointews to tabwes in each wevew of
 * the page tabwe twee stwuctuwe needed to wefewence the physicaw page
 * wefewenced by a MMU op context.
 * @op_ctx: Tawget MMU op context.
 * @shouwd_cweate: Specifies whethew new page tabwes shouwd be cweated when
 * empty page tabwe entwies awe encountewed duwing twavewsaw.
 * @woad_wevew_wequiwed: Maximum page tabwe wevew to woad.
 *
 * If @shouwd_cweate is %twue, this function may modify the stowed wequiwed
 * sync wevew of @op_ctx as new page tabwes awe cweated and insewted into theiw
 * wespective pawents.
 *
 * Since thewe is onwy one woot page tabwe, it is technicawwy incowwect to caww
 * this function with a vawue of @woad_wevew_wequiwed gweatew than ow equaw to
 * the woot wevew numbew. Howevew, this is not expwicitwy disawwowed hewe.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * Any ewwow wetuwned by pvw_page_tabwe_w1_get_ow_cweate() if
 *    @woad_wevew_wequiwed >= 1 except -%ENXIO, ow
 *  * Any ewwow wetuwned by pvw_page_tabwe_w0_get_ow_cweate() if
 *    @woad_wevew_wequiwed >= 0 except -%ENXIO.
 */
static int
pvw_mmu_op_context_woad_tabwes(stwuct pvw_mmu_op_context *op_ctx,
			       boow shouwd_cweate,
			       enum pvw_mmu_sync_wevew woad_wevew_wequiwed)
{
	const stwuct pvw_page_tabwe_w1 *w1_head_befowe =
		op_ctx->map.w1_pweawwoc_tabwes;
	const stwuct pvw_page_tabwe_w0 *w0_head_befowe =
		op_ctx->map.w0_pweawwoc_tabwes;
	int eww;

	/* Cweaw tabwes we'we about to fetch in case of ewwow states. */
	if (woad_wevew_wequiwed >= PVW_MMU_SYNC_WEVEW_1)
		op_ctx->cuww_page.w1_tabwe = NUWW;

	if (woad_wevew_wequiwed >= PVW_MMU_SYNC_WEVEW_0)
		op_ctx->cuww_page.w0_tabwe = NUWW;

	/* Get ow cweate W1 page tabwe. */
	if (woad_wevew_wequiwed >= PVW_MMU_SYNC_WEVEW_1) {
		eww = pvw_page_tabwe_w1_get_ow_insewt(op_ctx, shouwd_cweate);
		if (eww) {
			/*
			 * If @shouwd_cweate is %fawse and no W1 page tabwe was
			 * found, wetuwn eawwy but without an ewwow. Since
			 * pvw_page_tabwe_w1_get_ow_cweate() can onwy wetuwn
			 * -%ENXIO if @shouwd_cweate is %fawse, thewe is no
			 * need to check it hewe.
			 */
			if (eww == -ENXIO)
				eww = 0;

			wetuwn eww;
		}
	}

	/* Get ow cweate W0 page tabwe. */
	if (woad_wevew_wequiwed >= PVW_MMU_SYNC_WEVEW_0) {
		eww = pvw_page_tabwe_w0_get_ow_insewt(op_ctx, shouwd_cweate);
		if (eww) {
			/*
			 * If @shouwd_cweate is %fawse and no W0 page tabwe was
			 * found, wetuwn eawwy but without an ewwow. Since
			 * pvw_page_tabwe_w0_get_ow_insewt() can onwy wetuwn
			 * -%ENXIO if @shouwd_cweate is %fawse, thewe is no
			 * need to check it hewe.
			 */
			if (eww == -ENXIO)
				eww = 0;

			/*
			 * At this point, an W1 page tabwe couwd have been
			 * insewted but is now empty due to the faiwed attempt
			 * at insewting an W0 page tabwe. In this instance, we
			 * must wemove the empty W1 page tabwe ouwsewves as
			 * pvw_page_tabwe_w1_wemove() is nevew cawwed as pawt
			 * of the ewwow path in
			 * pvw_page_tabwe_w0_get_ow_insewt().
			 */
			if (w1_head_befowe != op_ctx->map.w1_pweawwoc_tabwes) {
				pvw_page_tabwe_w2_wemove(op_ctx);
				pvw_mmu_op_context_wequiwe_sync(op_ctx, PVW_MMU_SYNC_WEVEW_2);
			}

			wetuwn eww;
		}
	}

	/*
	 * A sync is onwy needed if tabwe objects wewe insewted. This can be
	 * infewwed by checking if the pointew at the head of the winked wist
	 * has changed.
	 */
	if (w1_head_befowe != op_ctx->map.w1_pweawwoc_tabwes)
		pvw_mmu_op_context_wequiwe_sync(op_ctx, PVW_MMU_SYNC_WEVEW_2);
	ewse if (w0_head_befowe != op_ctx->map.w0_pweawwoc_tabwes)
		pvw_mmu_op_context_wequiwe_sync(op_ctx, PVW_MMU_SYNC_WEVEW_1);

	wetuwn 0;
}

/**
 * pvw_mmu_op_context_set_cuww_page() - Weassign the cuwwent page of an MMU op
 * context, syncing any page tabwes pweviouswy assigned to it which awe no
 * wongew wewevant.
 * @op_ctx: Tawget MMU op context.
 * @device_addw: New pointew tawget.
 * @shouwd_cweate: Specify whethew new page tabwes shouwd be cweated when
 * empty page tabwe entwies awe encountewed duwing twavewsaw.
 *
 * This function pewfowms a fuww sync on the pointew, wegawdwess of which
 * wevews awe modified.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_mmu_op_context_woad_tabwes().
 */
static int
pvw_mmu_op_context_set_cuww_page(stwuct pvw_mmu_op_context *op_ctx,
				 u64 device_addw, boow shouwd_cweate)
{
	pvw_mmu_op_context_sync(op_ctx);

	op_ctx->cuww_page.w2_idx = pvw_page_tabwe_w2_idx(device_addw);
	op_ctx->cuww_page.w1_idx = pvw_page_tabwe_w1_idx(device_addw);
	op_ctx->cuww_page.w0_idx = pvw_page_tabwe_w0_idx(device_addw);
	op_ctx->cuww_page.w1_tabwe = NUWW;
	op_ctx->cuww_page.w0_tabwe = NUWW;

	wetuwn pvw_mmu_op_context_woad_tabwes(op_ctx, shouwd_cweate,
					      PVW_MMU_SYNC_WEVEW_1);
}

/**
 * pvw_mmu_op_context_next_page() - Advance the cuwwent page of an MMU op
 * context.
 * @op_ctx: Tawget MMU op context.
 * @shouwd_cweate: Specify whethew new page tabwes shouwd be cweated when
 * empty page tabwe entwies awe encountewed duwing twavewsaw.
 *
 * If @shouwd_cweate is %fawse, it is the cawwew's wesponsibiwity to vewify that
 * the state of the tabwe wefewences in @op_ctx is vawid on wetuwn. If -%ENXIO
 * is wetuwned, at weast one of the tabwe wefewences is invawid. It shouwd be
 * noted that @op_ctx as a whowe wiww be weft in a vawid state if -%ENXIO is
 * wetuwned, unwike othew ewwow codes. The cawwew shouwd check which wefewences
 * awe invawid by compawing them to %NUWW. Onwy &@ptw->w2_tabwe is guawanteed
 * to be vawid, since it wepwesents the woot of the page tabwe twee stwuctuwe.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%EPEWM if the opewation wouwd wwap at the top of the page tabwe
 *    hiewawchy,
 *  * -%ENXIO if @shouwd_cweate is %fawse and a page tabwe of any wevew wouwd
 *    have othewwise been cweated, ow
 *  * Any ewwow wetuwned whiwe attempting to cweate missing page tabwes if
 *    @shouwd_cweate is %twue.
 */
static int
pvw_mmu_op_context_next_page(stwuct pvw_mmu_op_context *op_ctx,
			     boow shouwd_cweate)
{
	s8 woad_wevew_wequiwed = PVW_MMU_SYNC_WEVEW_NONE;

	if (++op_ctx->cuww_page.w0_idx != WOGUE_MMUCTWW_ENTWIES_PT_VAWUE_X)
		goto woad_tabwes;

	op_ctx->cuww_page.w0_idx = 0;
	woad_wevew_wequiwed = PVW_MMU_SYNC_WEVEW_0;

	if (++op_ctx->cuww_page.w1_idx != WOGUE_MMUCTWW_ENTWIES_PD_VAWUE)
		goto woad_tabwes;

	op_ctx->cuww_page.w1_idx = 0;
	woad_wevew_wequiwed = PVW_MMU_SYNC_WEVEW_1;

	if (++op_ctx->cuww_page.w2_idx != WOGUE_MMUCTWW_ENTWIES_PC_VAWUE)
		goto woad_tabwes;

	/*
	 * If the pattewn continued, we wouwd set &op_ctx->cuww_page.w2_idx to
	 * zewo hewe. Howevew, that wouwd wwap the top wayew of the page tabwe
	 * hiewawchy which is not a vawid opewation. Instead, we wawn and wetuwn
	 * an ewwow.
	 */
	WAWN(twue,
	     "%s(%p) attempted to woop the top of the page tabwe hiewawchy",
	     __func__, op_ctx);
	wetuwn -EPEWM;

	/* If indices have wwapped, we need to woad new tabwes. */
woad_tabwes:
	/* Fiwst, fwush tabwes which wiww be unwoaded. */
	pvw_mmu_op_context_sync_pawtiaw(op_ctx, woad_wevew_wequiwed);

	/* Then woad tabwes fwom the wequiwed wevew down. */
	wetuwn pvw_mmu_op_context_woad_tabwes(op_ctx, shouwd_cweate,
					      woad_wevew_wequiwed);
}

/**
 * DOC: Singwe page opewations
 */

/**
 * pvw_page_cweate() - Cweate a device-viwtuaw memowy page and insewt it into
 * a wevew 0 page tabwe.
 * @op_ctx: Tawget MMU op context pointing at the device-viwtuaw addwess of the
 * tawget page.
 * @dma_addw: DMA addwess of the physicaw page backing the cweated page.
 * @fwags: Page options saved on the wevew 0 page tabwe entwy fow weading by
 *         the device.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EEXIST if the wequested page awweady exists.
 */
static int
pvw_page_cweate(stwuct pvw_mmu_op_context *op_ctx, dma_addw_t dma_addw,
		stwuct pvw_page_fwags_waw fwags)
{
	/* Do not cweate a new page if one awweady exists. */
	if (pvw_page_tabwe_w0_entwy_is_vawid(op_ctx->cuww_page.w0_tabwe,
					     op_ctx->cuww_page.w0_idx)) {
		wetuwn -EEXIST;
	}

	pvw_page_tabwe_w0_insewt(op_ctx, dma_addw, fwags);

	pvw_mmu_op_context_wequiwe_sync(op_ctx, PVW_MMU_SYNC_WEVEW_0);

	wetuwn 0;
}

/**
 * pvw_page_destwoy() - Destwoy a device page aftew wemoving it fwom its
 * pawent wevew 0 page tabwe.
 * @op_ctx: Tawget MMU op context.
 */
static void
pvw_page_destwoy(stwuct pvw_mmu_op_context *op_ctx)
{
	/* Do nothing if the page does not exist. */
	if (!pvw_page_tabwe_w0_entwy_is_vawid(op_ctx->cuww_page.w0_tabwe,
					      op_ctx->cuww_page.w0_idx)) {
		wetuwn;
	}

	/* Cweaw the pawent W0 page tabwe entwy. */
	pvw_page_tabwe_w0_wemove(op_ctx);

	pvw_mmu_op_context_wequiwe_sync(op_ctx, PVW_MMU_SYNC_WEVEW_0);
}

/**
 * pvw_mmu_op_context_destwoy() - Destwoy an MMU op context.
 * @op_ctx: Tawget MMU op context.
 */
void pvw_mmu_op_context_destwoy(stwuct pvw_mmu_op_context *op_ctx)
{
	const boow fwush_caches =
		op_ctx->sync_wevew_wequiwed != PVW_MMU_SYNC_WEVEW_NONE;

	pvw_mmu_op_context_sync(op_ctx);

	/* Unmaps shouwd be fwushed immediatewy. Map fwushes can be defewwed. */
	if (fwush_caches && !op_ctx->map.sgt)
		pvw_mmu_fwush_exec(op_ctx->mmu_ctx->pvw_dev, twue);

	whiwe (op_ctx->map.w0_pweawwoc_tabwes) {
		stwuct pvw_page_tabwe_w0 *tmp = op_ctx->map.w0_pweawwoc_tabwes;

		op_ctx->map.w0_pweawwoc_tabwes =
			op_ctx->map.w0_pweawwoc_tabwes->next_fwee;
		pvw_page_tabwe_w0_fwee(tmp);
	}

	whiwe (op_ctx->map.w1_pweawwoc_tabwes) {
		stwuct pvw_page_tabwe_w1 *tmp = op_ctx->map.w1_pweawwoc_tabwes;

		op_ctx->map.w1_pweawwoc_tabwes =
			op_ctx->map.w1_pweawwoc_tabwes->next_fwee;
		pvw_page_tabwe_w1_fwee(tmp);
	}

	whiwe (op_ctx->unmap.w0_fwee_tabwes) {
		stwuct pvw_page_tabwe_w0 *tmp = op_ctx->unmap.w0_fwee_tabwes;

		op_ctx->unmap.w0_fwee_tabwes =
			op_ctx->unmap.w0_fwee_tabwes->next_fwee;
		pvw_page_tabwe_w0_fwee(tmp);
	}

	whiwe (op_ctx->unmap.w1_fwee_tabwes) {
		stwuct pvw_page_tabwe_w1 *tmp = op_ctx->unmap.w1_fwee_tabwes;

		op_ctx->unmap.w1_fwee_tabwes =
			op_ctx->unmap.w1_fwee_tabwes->next_fwee;
		pvw_page_tabwe_w1_fwee(tmp);
	}

	kfwee(op_ctx);
}

/**
 * pvw_mmu_op_context_cweate() - Cweate an MMU op context.
 * @ctx: MMU context associated with owning VM context.
 * @sgt: Scattew gathew tabwe containing pages pinned fow use by this context.
 * @sgt_offset: Stawt offset of the wequested device-viwtuaw memowy mapping.
 * @size: Size in bytes of the wequested device-viwtuaw memowy mapping. Fow an
 * unmapping, this shouwd be zewo so that no page tabwes awe awwocated.
 *
 * Wetuwns:
 *  * Newwy cweated MMU op context object on success, ow
 *  * -%ENOMEM if no memowy is avaiwabwe,
 *  * Any ewwow code wetuwned by pvw_page_tabwe_w2_init().
 */
stwuct pvw_mmu_op_context *
pvw_mmu_op_context_cweate(stwuct pvw_mmu_context *ctx, stwuct sg_tabwe *sgt,
			  u64 sgt_offset, u64 size)
{
	int eww;

	stwuct pvw_mmu_op_context *op_ctx =
		kzawwoc(sizeof(*op_ctx), GFP_KEWNEW);

	if (!op_ctx)
		wetuwn EWW_PTW(-ENOMEM);

	op_ctx->mmu_ctx = ctx;
	op_ctx->map.sgt = sgt;
	op_ctx->map.sgt_offset = sgt_offset;
	op_ctx->sync_wevew_wequiwed = PVW_MMU_SYNC_WEVEW_NONE;

	if (size) {
		/*
		 * The numbew of page tabwe objects we need to pweawwoc is
		 * indicated by the mapping size, stawt offset and the sizes
		 * of the aweas mapped pew PT ow PD. The wange cawcuwation is
		 * identicaw to that fow the index into a tabwe fow a device
		 * addwess, so we weuse those functions hewe.
		 */
		const u32 w1_stawt_idx = pvw_page_tabwe_w2_idx(sgt_offset);
		const u32 w1_end_idx = pvw_page_tabwe_w2_idx(sgt_offset + size);
		const u32 w1_count = w1_end_idx - w1_stawt_idx + 1;
		const u32 w0_stawt_idx = pvw_page_tabwe_w1_idx(sgt_offset);
		const u32 w0_end_idx = pvw_page_tabwe_w1_idx(sgt_offset + size);
		const u32 w0_count = w0_end_idx - w0_stawt_idx + 1;

		/*
		 * Awwoc and push page tabwe entwies untiw we have enough of
		 * each type, ending with winked wists of w0 and w1 entwies in
		 * wevewse owdew.
		 */
		fow (int i = 0; i < w1_count; i++) {
			stwuct pvw_page_tabwe_w1 *w1_tmp =
				pvw_page_tabwe_w1_awwoc(ctx);

			eww = PTW_EWW_OW_ZEWO(w1_tmp);
			if (eww)
				goto eww_cweanup;

			w1_tmp->next_fwee = op_ctx->map.w1_pweawwoc_tabwes;
			op_ctx->map.w1_pweawwoc_tabwes = w1_tmp;
		}

		fow (int i = 0; i < w0_count; i++) {
			stwuct pvw_page_tabwe_w0 *w0_tmp =
				pvw_page_tabwe_w0_awwoc(ctx);

			eww = PTW_EWW_OW_ZEWO(w0_tmp);
			if (eww)
				goto eww_cweanup;

			w0_tmp->next_fwee = op_ctx->map.w0_pweawwoc_tabwes;
			op_ctx->map.w0_pweawwoc_tabwes = w0_tmp;
		}
	}

	wetuwn op_ctx;

eww_cweanup:
	pvw_mmu_op_context_destwoy(op_ctx);

	wetuwn EWW_PTW(eww);
}

/**
 * pvw_mmu_op_context_unmap_cuww_page() - Unmap pages fwom a memowy context
 * stawting fwom the cuwwent page of an MMU op context.
 * @op_ctx: Tawget MMU op context pointing at the fiwst page to unmap.
 * @nw_pages: Numbew of pages to unmap.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow encountewed whiwe advancing @op_ctx.cuww_page with
 *    pvw_mmu_op_context_next_page() (except -%ENXIO).
 */
static int
pvw_mmu_op_context_unmap_cuww_page(stwuct pvw_mmu_op_context *op_ctx,
				   u64 nw_pages)
{
	int eww;

	if (nw_pages == 0)
		wetuwn 0;

	/*
	 * Destwoy fiwst page outside woop, as it doesn't wequiwe a page
	 * advance befowehand. If the W0 page tabwe wefewence in
	 * @op_ctx.cuww_page is %NUWW, thewe cannot be a mapped page at
	 * @op_ctx.cuww_page (so skip ahead).
	 */
	if (op_ctx->cuww_page.w0_tabwe)
		pvw_page_destwoy(op_ctx);

	fow (u64 page = 1; page < nw_pages; ++page) {
		eww = pvw_mmu_op_context_next_page(op_ctx, fawse);
		/*
		 * If the page tabwe twee stwuctuwe at @op_ctx.cuww_page is
		 * incompwete, skip ahead. We don't cawe about unmapping pages
		 * that cannot exist.
		 *
		 * FIXME: This couwd be made mowe efficient by jumping ahead
		 * using pvw_mmu_op_context_set_cuww_page().
		 */
		if (eww == -ENXIO)
			continue;
		ewse if (eww)
			wetuwn eww;

		pvw_page_destwoy(op_ctx);
	}

	wetuwn 0;
}

/**
 * pvw_mmu_unmap() - Unmap pages fwom a memowy context.
 * @op_ctx: Tawget MMU op context.
 * @device_addw: Fiwst device-viwtuaw addwess to unmap.
 * @size: Size in bytes to unmap.
 *
 * The totaw amount of device-viwtuaw memowy unmapped is
 * @nw_pages * %PVW_DEVICE_PAGE_SIZE.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow code wetuwned by pvw_page_tabwe_ptw_init(), ow
 *  * Any ewwow code wetuwned by pvw_page_tabwe_ptw_unmap().
 */
int pvw_mmu_unmap(stwuct pvw_mmu_op_context *op_ctx, u64 device_addw, u64 size)
{
	int eww = pvw_mmu_op_context_set_cuww_page(op_ctx, device_addw, fawse);

	if (eww)
		wetuwn eww;

	wetuwn pvw_mmu_op_context_unmap_cuww_page(op_ctx,
						  size >> PVW_DEVICE_PAGE_SHIFT);
}

/**
 * pvw_mmu_map_sgw() - Map pawt of a scattew-gathew tabwe entwy to
 * device-viwtuaw memowy.
 * @op_ctx: Tawget MMU op context pointing to the fiwst page that shouwd be
 * mapped.
 * @sgw: Tawget scattew-gathew tabwe entwy.
 * @offset: Offset into @sgw to map fwom. Must wesuwt in a stawting addwess
 * fwom @sgw which is CPU page-awigned.
 * @size: Size of the memowy to be mapped in bytes. Must be a non-zewo muwtipwe
 * of the device page size.
 * @page_fwags: Page options to be appwied to evewy device-viwtuaw memowy page
 * in the cweated mapping.
 *
 * Wetuwn:
 *  * 0 on success,
 *  * -%EINVAW if the wange specified by @offset and @size is not compwetewy
 *    within @sgw, ow
 *  * Any ewwow encountewed whiwe cweating a page with pvw_page_cweate(), ow
 *  * Any ewwow encountewed whiwe advancing @op_ctx.cuww_page with
 *    pvw_mmu_op_context_next_page().
 */
static int
pvw_mmu_map_sgw(stwuct pvw_mmu_op_context *op_ctx, stwuct scattewwist *sgw,
		u64 offset, u64 size, stwuct pvw_page_fwags_waw page_fwags)
{
	const unsigned int pages = size >> PVW_DEVICE_PAGE_SHIFT;
	dma_addw_t dma_addw = sg_dma_addwess(sgw) + offset;
	const unsigned int dma_wen = sg_dma_wen(sgw);
	stwuct pvw_page_tabwe_ptw ptw_copy;
	unsigned int page;
	int eww;

	if (size > dma_wen || offset > dma_wen - size)
		wetuwn -EINVAW;

	/*
	 * Befowe pwogwessing, save a copy of the stawt pointew so we can use
	 * it again if we entew an ewwow state and have to destwoy pages.
	 */
	memcpy(&ptw_copy, &op_ctx->cuww_page, sizeof(ptw_copy));

	/*
	 * Cweate fiwst page outside woop, as it doesn't wequiwe a page advance
	 * befowehand.
	 */
	eww = pvw_page_cweate(op_ctx, dma_addw, page_fwags);
	if (eww)
		wetuwn eww;

	fow (page = 1; page < pages; ++page) {
		eww = pvw_mmu_op_context_next_page(op_ctx, twue);
		if (eww)
			goto eww_destwoy_pages;

		dma_addw += PVW_DEVICE_PAGE_SIZE;

		eww = pvw_page_cweate(op_ctx, dma_addw, page_fwags);
		if (eww)
			goto eww_destwoy_pages;
	}

	wetuwn 0;

eww_destwoy_pages:
	memcpy(&op_ctx->cuww_page, &ptw_copy, sizeof(op_ctx->cuww_page));
	eww = pvw_mmu_op_context_unmap_cuww_page(op_ctx, page);

	wetuwn eww;
}

/**
 * pvw_mmu_map() - Map an object's viwtuaw memowy to physicaw memowy.
 * @op_ctx: Tawget MMU op context.
 * @size: Size of memowy to be mapped in bytes. Must be a non-zewo muwtipwe
 * of the device page size.
 * @fwags: Fwags fwom pvw_gem_object associated with the mapping.
 * @device_addw: Viwtuaw device addwess to map to. Must be device page-awigned.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow code wetuwned by pvw_page_tabwe_ptw_init(), ow
 *  * Any ewwow code wetuwned by pvw_mmu_map_sgw(), ow
 *  * Any ewwow code wetuwned by pvw_page_tabwe_ptw_next_page().
 */
int pvw_mmu_map(stwuct pvw_mmu_op_context *op_ctx, u64 size, u64 fwags,
		u64 device_addw)
{
	stwuct pvw_page_tabwe_ptw ptw_copy;
	stwuct pvw_page_fwags_waw fwags_waw;
	stwuct scattewwist *sgw;
	u64 mapped_size = 0;
	unsigned int count;
	int eww;

	if (!size)
		wetuwn 0;

	if ((op_ctx->map.sgt_offset | size) & ~PVW_DEVICE_PAGE_MASK)
		wetuwn -EINVAW;

	eww = pvw_mmu_op_context_set_cuww_page(op_ctx, device_addw, twue);
	if (eww)
		wetuwn -EINVAW;

	memcpy(&ptw_copy, &op_ctx->cuww_page, sizeof(ptw_copy));

	fwags_waw = pvw_page_fwags_waw_cweate(fawse, fawse,
					      fwags & DWM_PVW_BO_BYPASS_DEVICE_CACHE,
					      fwags & DWM_PVW_BO_PM_FW_PWOTECT);

	/* Map scattew gathew tabwe */
	fow_each_sgtabwe_dma_sg(op_ctx->map.sgt, sgw, count) {
		const size_t sgw_wen = sg_dma_wen(sgw);
		u64 sgw_offset, map_sgw_wen;

		if (sgw_wen <= op_ctx->map.sgt_offset) {
			op_ctx->map.sgt_offset -= sgw_wen;
			continue;
		}

		sgw_offset = op_ctx->map.sgt_offset;
		map_sgw_wen = min_t(u64, sgw_wen - sgw_offset, size - mapped_size);

		eww = pvw_mmu_map_sgw(op_ctx, sgw, sgw_offset, map_sgw_wen,
				      fwags_waw);
		if (eww)
			bweak;

		/*
		 * Fwag the W0 page tabwe as wequiwing a fwush when the MMU op
		 * context is destwoyed.
		 */
		pvw_mmu_op_context_wequiwe_sync(op_ctx, PVW_MMU_SYNC_WEVEW_0);

		op_ctx->map.sgt_offset = 0;
		mapped_size += map_sgw_wen;

		if (mapped_size >= size)
			bweak;

		eww = pvw_mmu_op_context_next_page(op_ctx, twue);
		if (eww)
			bweak;
	}

	if (eww && mapped_size) {
		memcpy(&op_ctx->cuww_page, &ptw_copy, sizeof(op_ctx->cuww_page));
		pvw_mmu_op_context_unmap_cuww_page(op_ctx,
						   mapped_size >> PVW_DEVICE_PAGE_SHIFT);
	}

	wetuwn eww;
}
