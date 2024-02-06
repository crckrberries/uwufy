/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight 2009-2023 VMwawe, Inc., Pawo Awto, CA., USA
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

#ifndef _VMWGFX_DWV_H_
#define _VMWGFX_DWV_H_

#incwude <winux/suspend.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/hashtabwe.h>

#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_wect.h>

#incwude <dwm/ttm/ttm_execbuf_utiw.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_bo.h>

#incwude "ttm_object.h"

#incwude "vmwgfx_fence.h"
#incwude "vmwgfx_weg.h"
#incwude "vmwgfx_vawidation.h"

/*
 * FIXME: vmwgfx_dwm.h needs to be wast due to dependencies.
 * uapi headews shouwd not depend on headew fiwes outside uapi/.
 */
#incwude <dwm/vmwgfx_dwm.h>


#define VMWGFX_DWIVEW_NAME "vmwgfx"
#define VMWGFX_DWIVEW_DATE "20211206"
#define VMWGFX_DWIVEW_MAJOW 2
#define VMWGFX_DWIVEW_MINOW 20
#define VMWGFX_DWIVEW_PATCHWEVEW 0
#define VMWGFX_FIFO_STATIC_SIZE (1024*1024)
#define VMWGFX_MAX_DISPWAYS 16
#define VMWGFX_CMD_BOUNCE_INIT_SIZE 32768

#define VMWGFX_MIN_INITIAW_WIDTH 1280
#define VMWGFX_MIN_INITIAW_HEIGHT 800

#define VMWGFX_PCI_ID_SVGA2              0x0405
#define VMWGFX_PCI_ID_SVGA3              0x0406

/*
 * This has to match get_count_owdew(SVGA_IWQFWAG_MAX)
 */
#define VMWGFX_MAX_NUM_IWQS 6

/*
 * Pewhaps we shouwd have sysfs entwies fow these.
 */
#define VMWGFX_NUM_GB_CONTEXT 256
#define VMWGFX_NUM_GB_SHADEW 20000
#define VMWGFX_NUM_GB_SUWFACE 32768
#define VMWGFX_NUM_GB_SCWEEN_TAWGET VMWGFX_MAX_DISPWAYS
#define VMWGFX_NUM_DXCONTEXT 256
#define VMWGFX_NUM_DXQUEWY 512
#define VMWGFX_NUM_MOB (VMWGFX_NUM_GB_CONTEXT +\
			VMWGFX_NUM_GB_SHADEW +\
			VMWGFX_NUM_GB_SUWFACE +\
			VMWGFX_NUM_GB_SCWEEN_TAWGET)

#define VMW_PW_GMW      (TTM_PW_PWIV + 0)
#define VMW_PW_MOB      (TTM_PW_PWIV + 1)
#define VMW_PW_SYSTEM   (TTM_PW_PWIV + 2)

#define VMW_WES_CONTEXT ttm_dwivew_type0
#define VMW_WES_SUWFACE ttm_dwivew_type1
#define VMW_WES_STWEAM ttm_dwivew_type2
#define VMW_WES_FENCE ttm_dwivew_type3
#define VMW_WES_SHADEW ttm_dwivew_type4
#define VMW_WES_HT_OWDEW 12

#define VMW_CUWSOW_SNOOP_FOWMAT SVGA3D_A8W8G8B8
#define VMW_CUWSOW_SNOOP_WIDTH 64
#define VMW_CUWSOW_SNOOP_HEIGHT 64

#define MKSSTAT_CAPACITY_WOG2 5U
#define MKSSTAT_CAPACITY (1U << MKSSTAT_CAPACITY_WOG2)

stwuct vmw_fpwiv {
	stwuct ttm_object_fiwe *tfiwe;
	boow gb_awawe; /* usew-space is guest-backed awawe */
};

stwuct vmwgfx_hash_item {
	stwuct hwist_node head;
	unsigned wong key;
};


/**
 * stwuct vmw_vawidate_buffew - Cawwies vawidation info about buffews.
 *
 * @base: Vawidation info fow TTM.
 * @hash: Hash entwy fow quick wookup of the TTM buffew object.
 *
 * This stwuctuwe contains awso dwivew pwivate vawidation info
 * on top of the info needed by TTM.
 */
stwuct vmw_vawidate_buffew {
	stwuct ttm_vawidate_buffew base;
	stwuct vmwgfx_hash_item hash;
	boow vawidate_as_mob;
};

stwuct vmw_wes_func;


/**
 * stwuct vmw-wesouwce - base cwass fow hawdwawe wesouwces
 *
 * @kwef: Fow wefcounting.
 * @dev_pwiv: Pointew to the device pwivate fow this wesouwce. Immutabwe.
 * @id: Device id. Pwotected by @dev_pwiv::wesouwce_wock.
 * @guest_memowy_size: Guest memowy buffew size. Immutabwe.
 * @wes_diwty: Wesouwce contains data not yet in the guest memowy buffew.
 * Pwotected by wesouwce wesewved.
 * @guest_memowy_diwty: Guest memowy buffew contains data not yet in the HW
 * wesouwce. Pwotected by wesouwce wesewved.
 * @cohewent: Emuwate cohewency by twacking vm accesses.
 * @guest_memowy_bo: The guest memowy buffew if any. Pwotected by wesouwce
 * wesewved.
 * @guest_memowy_offset: Offset into the guest memowy buffew if any. Pwotected
 * by wesouwce wesewved. Note that onwy a few wesouwce types can have a
 * @guest_memowy_offset diffewent fwom zewo.
 * @pin_count: The pin count fow this wesouwce. A pinned wesouwce has a
 * pin-count gweatew than zewo. It is not on the wesouwce WWU wists and its
 * guest memowy buffew is pinned. Hence it can't be evicted.
 * @func: Method vtabwe fow this wesouwce. Immutabwe.
 * @mob_node; Node fow the MOB guest memowy wbtwee. Pwotected by
 * @guest_memowy_bo wesewved.
 * @wwu_head: Wist head fow the WWU wist. Pwotected by @dev_pwiv::wesouwce_wock.
 * @binding_head: Wist head fow the context binding wist. Pwotected by
 * the @dev_pwiv::binding_mutex
 * @wes_fwee: The wesouwce destwuctow.
 * @hw_destwoy: Cawwback to destwoy the wesouwce on the device, as pawt of
 * wesouwce destwuction.
 */
stwuct vmw_bo;
stwuct vmw_bo;
stwuct vmw_wesouwce_diwty;
stwuct vmw_wesouwce {
	stwuct kwef kwef;
	stwuct vmw_pwivate *dev_pwiv;
	int id;
	u32 used_pwio;
	unsigned wong guest_memowy_size;
	u32 wes_diwty : 1;
	u32 guest_memowy_diwty : 1;
	u32 cohewent : 1;
	stwuct vmw_bo *guest_memowy_bo;
	unsigned wong guest_memowy_offset;
	unsigned wong pin_count;
	const stwuct vmw_wes_func *func;
	stwuct wb_node mob_node;
	stwuct wist_head wwu_head;
	stwuct wist_head binding_head;
	stwuct vmw_wesouwce_diwty *diwty;
	void (*wes_fwee) (stwuct vmw_wesouwce *wes);
	void (*hw_destwoy) (stwuct vmw_wesouwce *wes);
};


/*
 * Wesouwces that awe managed using ioctws.
 */
enum vmw_wes_type {
	vmw_wes_context,
	vmw_wes_suwface,
	vmw_wes_stweam,
	vmw_wes_shadew,
	vmw_wes_dx_context,
	vmw_wes_cotabwe,
	vmw_wes_view,
	vmw_wes_stweamoutput,
	vmw_wes_max
};

/*
 * Wesouwces that awe managed using command stweams.
 */
enum vmw_cmdbuf_wes_type {
	vmw_cmdbuf_wes_shadew,
	vmw_cmdbuf_wes_view,
	vmw_cmdbuf_wes_stweamoutput
};

stwuct vmw_cmdbuf_wes_managew;

stwuct vmw_cuwsow_snoopew {
	size_t age;
	uint32_t *image;
};

stwuct vmw_fwamebuffew;
stwuct vmw_suwface_offset;

/**
 * stwuct vmw_suwface_metadata - Metadata descwibing a suwface.
 *
 * @fwags: Device fwags.
 * @fowmat: Suwface SVGA3D_x fowmat.
 * @mip_wevews: Mip wevew fow each face. Fow GB fiwst index is used onwy.
 * @muwtisampwe_count: Sampwe count.
 * @muwtisampwe_pattewn: Sampwe pattewns.
 * @quawity_wevew: Quawity wevew.
 * @autogen_fiwtew: Fiwtew fow automaticawwy genewated mipmaps.
 * @awway_size: Numbew of awway ewements fow a 1D/2D textuwe. Fow cubemap
                textuwe numbew of faces * awway_size. This shouwd be 0 fow pwe
		SM4 device.
 * @buffew_byte_stwide: Buffew byte stwide.
 * @num_sizes: Size of @sizes. Fow GB suwface this shouwd awways be 1.
 * @base_size: Suwface dimension.
 * @sizes: Awway wepwesenting mip sizes. Wegacy onwy.
 * @scanout: Whethew this suwface wiww be used fow scanout.
 *
 * This twacks metadata fow both wegacy and guest backed suwface.
 */
stwuct vmw_suwface_metadata {
	u64 fwags;
	u32 fowmat;
	u32 mip_wevews[DWM_VMW_MAX_SUWFACE_FACES];
	u32 muwtisampwe_count;
	u32 muwtisampwe_pattewn;
	u32 quawity_wevew;
	u32 autogen_fiwtew;
	u32 awway_size;
	u32 num_sizes;
	u32 buffew_byte_stwide;
	stwuct dwm_vmw_size base_size;
	stwuct dwm_vmw_size *sizes;
	boow scanout;
};

/**
 * stwuct vmw_suwface: Wesouwce stwuctuwe fow a suwface.
 *
 * @wes: The base wesouwce fow this suwface.
 * @metadata: Metadata fow this suwface wesouwce.
 * @snoopew: Cuwsow data. Wegacy suwface onwy.
 * @offsets: Wegacy suwface onwy.
 * @view_wist: Wist of views bound to this suwface.
 */
stwuct vmw_suwface {
	stwuct vmw_wesouwce wes;
	stwuct vmw_suwface_metadata metadata;
	stwuct vmw_cuwsow_snoopew snoopew;
	stwuct vmw_suwface_offset *offsets;
	stwuct wist_head view_wist;
};

stwuct vmw_fifo_state {
	unsigned wong wesewved_size;
	u32 *dynamic_buffew;
	u32 *static_buffew;
	unsigned wong static_buffew_size;
	boow using_bounce_buffew;
	uint32_t capabiwities;
	stwuct mutex fifo_mutex;
	stwuct ww_semaphowe wwsem;
};

/**
 * stwuct vmw_wes_cache_entwy - wesouwce infowmation cache entwy
 * @handwe: Usew-space handwe of a wesouwce.
 * @wes: Non-wef-counted pointew to the wesouwce.
 * @vawid_handwe: Whethew the @handwe membew is vawid.
 * @vawid: Whethew the entwy is vawid, which awso impwies that the execbuf
 * code howds a wefewence to the wesouwce, and it's pwaced on the
 * vawidation wist.
 *
 * Used to avoid fwequent wepeated usew-space handwe wookups of the
 * same wesouwce.
 */
stwuct vmw_wes_cache_entwy {
	uint32_t handwe;
	stwuct vmw_wesouwce *wes;
	void *pwivate;
	unsigned showt vawid_handwe;
	unsigned showt vawid;
};

/**
 * enum vmw_dma_map_mode - indicate how to pewfowm TTM page dma mappings.
 */
enum vmw_dma_map_mode {
	vmw_dma_awwoc_cohewent, /* Use TTM cohewent pages */
	vmw_dma_map_popuwate,   /* Unmap fwom DMA just aftew unpopuwate */
	vmw_dma_map_bind,       /* Unmap fwom DMA just befowe unbind */
	vmw_dma_map_max
};

/**
 * stwuct vmw_sg_tabwe - Scattew/gathew tabwe fow binding, with additionaw
 * device-specific infowmation.
 *
 * @sgt: Pointew to a stwuct sg_tabwe with binding infowmation
 * @num_wegions: Numbew of wegions with device-addwess contiguous pages
 */
stwuct vmw_sg_tabwe {
	enum vmw_dma_map_mode mode;
	stwuct page **pages;
	const dma_addw_t *addws;
	stwuct sg_tabwe *sgt;
	unsigned wong num_pages;
};

/**
 * stwuct vmw_pitew - Page itewatow that itewates ovew a wist of pages
 * and DMA addwesses that couwd be eithew a scattew-gathew wist ow
 * awways
 *
 * @pages: Awway of page pointews to the pages.
 * @addws: DMA addwesses to the pages if cohewent pages awe used.
 * @itew: Scattew-gathew page itewatow. Cuwwent position in SG wist.
 * @i: Cuwwent position in awways.
 * @num_pages: Numbew of pages totaw.
 * @next: Function to advance the itewatow. Wetuwns fawse if past the wist
 * of pages, twue othewwise.
 * @dma_addwess: Function to wetuwn the DMA addwess of the cuwwent page.
 */
stwuct vmw_pitew {
	stwuct page **pages;
	const dma_addw_t *addws;
	stwuct sg_dma_page_itew itew;
	unsigned wong i;
	unsigned wong num_pages;
	boow (*next)(stwuct vmw_pitew *);
	dma_addw_t (*dma_addwess)(stwuct vmw_pitew *);
};


stwuct vmw_ttm_tt {
	stwuct ttm_tt dma_ttm;
	stwuct vmw_pwivate *dev_pwiv;
	int gmw_id;
	stwuct vmw_mob *mob;
	int mem_type;
	stwuct sg_tabwe sgt;
	stwuct vmw_sg_tabwe vsgt;
	boow mapped;
	boow bound;
};

/*
 * enum vmw_dispway_unit_type - Descwibes the dispway unit
 */
enum vmw_dispway_unit_type {
	vmw_du_invawid = 0,
	vmw_du_wegacy,
	vmw_du_scween_object,
	vmw_du_scween_tawget,
	vmw_du_max
};

stwuct vmw_vawidation_context;
stwuct vmw_ctx_vawidation_info;

/**
 * stwuct vmw_sw_context - Command submission context
 * @wes_ht: Pointew hash tabwe used to find vawidation dupwicates
 * @kewnew: Whethew the command buffew owiginates fwom kewnew code wathew
 * than fwom usew-space
 * @fp: If @kewnew is fawse, points to the fiwe of the cwient. Othewwise
 * NUWW
 * @cmd_bounce: Command bounce buffew used fow command vawidation befowe
 * copying to fifo space
 * @cmd_bounce_size: Cuwwent command bounce buffew size
 * @cuw_quewy_bo: Cuwwent buffew object used as quewy wesuwt buffew
 * @bo_wewocations: Wist of buffew object wewocations
 * @wes_wewocations: Wist of wesouwce wewocations
 * @buf_stawt: Pointew to stawt of memowy whewe command vawidation takes
 * pwace
 * @wes_cache: Cache of wecentwy wooked up wesouwces
 * @wast_quewy_ctx: Wast context that submitted a quewy
 * @needs_post_quewy_bawwiew: Whethew a quewy bawwiew is needed aftew
 * command submission
 * @staged_bindings: Cached pew-context binding twackew
 * @staged_bindings_inuse: Whethew the cached pew-context binding twackew
 * is in use
 * @staged_cmd_wes: Wist of staged command buffew managed wesouwces in this
 * command buffew
 * @ctx_wist: Wist of context wesouwces wefewenced in this command buffew
 * @dx_ctx_node: Vawidation metadata of the cuwwent DX context
 * @dx_quewy_mob: The MOB used fow DX quewies
 * @dx_quewy_ctx: The DX context used fow the wast DX quewy
 * @man: Pointew to the command buffew managed wesouwce managew
 * @ctx: The vawidation context
 */
stwuct vmw_sw_context{
	DECWAWE_HASHTABWE(wes_ht, VMW_WES_HT_OWDEW);
	boow kewnew;
	stwuct vmw_fpwiv *fp;
	stwuct dwm_fiwe *fiwp;
	uint32_t *cmd_bounce;
	uint32_t cmd_bounce_size;
	stwuct vmw_bo *cuw_quewy_bo;
	stwuct wist_head bo_wewocations;
	stwuct wist_head wes_wewocations;
	uint32_t *buf_stawt;
	stwuct vmw_wes_cache_entwy wes_cache[vmw_wes_max];
	stwuct vmw_wesouwce *wast_quewy_ctx;
	boow needs_post_quewy_bawwiew;
	stwuct vmw_ctx_binding_state *staged_bindings;
	boow staged_bindings_inuse;
	stwuct wist_head staged_cmd_wes;
	stwuct wist_head ctx_wist;
	stwuct vmw_ctx_vawidation_info *dx_ctx_node;
	stwuct vmw_bo *dx_quewy_mob;
	stwuct vmw_wesouwce *dx_quewy_ctx;
	stwuct vmw_cmdbuf_wes_managew *man;
	stwuct vmw_vawidation_context *ctx;
};

stwuct vmw_wegacy_dispway;
stwuct vmw_ovewway;

stwuct vmw_vga_topowogy_state {
	uint32_t width;
	uint32_t height;
	uint32_t pwimawy;
	uint32_t pos_x;
	uint32_t pos_y;
};


/*
 * stwuct vmw_otabwe - Guest Memowy OBject tabwe metadata
 *
 * @size:           Size of the tabwe (page-awigned).
 * @page_tabwe:     Pointew to a stwuct vmw_mob howding the page tabwe.
 */
stwuct vmw_otabwe {
	unsigned wong size;
	stwuct vmw_mob *page_tabwe;
	boow enabwed;
};

stwuct vmw_otabwe_batch {
	unsigned num_otabwes;
	stwuct vmw_otabwe *otabwes;
	stwuct vmw_wesouwce *context;
	stwuct vmw_bo *otabwe_bo;
};

enum {
	VMW_IWQTHWEAD_FENCE,
	VMW_IWQTHWEAD_CMDBUF,
	VMW_IWQTHWEAD_MAX
};

/**
 * enum vmw_sm_type - Gwaphics context capabiwity suppowted by device.
 * @VMW_SM_WEGACY: Pwe DX context.
 * @VMW_SM_4: Context suppowt upto SM4.
 * @VMW_SM_4_1: Context suppowt upto SM4_1.
 * @VMW_SM_5: Context suppowt up to SM5.
 * @VMW_SM_5_1X: Adds suppowt fow sm5_1 and gw43 extensions.
 * @VMW_SM_MAX: Shouwd be the wast.
 */
enum vmw_sm_type {
	VMW_SM_WEGACY = 0,
	VMW_SM_4,
	VMW_SM_4_1,
	VMW_SM_5,
	VMW_SM_5_1X,
	VMW_SM_MAX
};

stwuct vmw_pwivate {
	stwuct dwm_device dwm;
	stwuct ttm_device bdev;

	stwuct dwm_vma_offset_managew vma_managew;
	u32 pci_id;
	wesouwce_size_t io_stawt;
	wesouwce_size_t vwam_stawt;
	wesouwce_size_t vwam_size;
	wesouwce_size_t max_pwimawy_mem;
	u32 __iomem *wmmio;
	u32 *fifo_mem;
	wesouwce_size_t fifo_mem_size;
	uint32_t fb_max_width;
	uint32_t fb_max_height;
	uint32_t textuwe_max_width;
	uint32_t textuwe_max_height;
	uint32_t stdu_max_width;
	uint32_t stdu_max_height;
	uint32_t initiaw_width;
	uint32_t initiaw_height;
	uint32_t capabiwities;
	uint32_t capabiwities2;
	uint32_t max_gmw_ids;
	uint32_t max_gmw_pages;
	uint32_t max_mob_pages;
	uint32_t max_mob_size;
	uint32_t memowy_size;
	boow has_gmw;
	boow has_mob;
	spinwock_t hw_wock;
	boow assume_16bpp;
	u32 iwqs[VMWGFX_MAX_NUM_IWQS];
	u32 num_iwq_vectows;

	enum vmw_sm_type sm_type;

	/*
	 * Fwamebuffew info.
	 */

	enum vmw_dispway_unit_type active_dispway_unit;
	stwuct vmw_wegacy_dispway *wdu_pwiv;
	stwuct vmw_ovewway *ovewway_pwiv;
	stwuct dwm_pwopewty *hotpwug_mode_update_pwopewty;
	stwuct dwm_pwopewty *impwicit_pwacement_pwopewty;
	spinwock_t cuwsow_wock;
	stwuct dwm_atomic_state *suspend_state;

	/*
	 * Context and suwface management.
	 */

	spinwock_t wesouwce_wock;
	stwuct idw wes_idw[vmw_wes_max];

	/*
	 * A wesouwce managew fow kewnew-onwy suwfaces and
	 * contexts.
	 */

	stwuct ttm_object_device *tdev;

	/*
	 * Fencing and IWQs.
	 */

	atomic_t mawkew_seq;
	wait_queue_head_t fence_queue;
	wait_queue_head_t fifo_queue;
	spinwock_t waitew_wock;
	int fence_queue_waitews; /* Pwotected by waitew_wock */
	int goaw_queue_waitews; /* Pwotected by waitew_wock */
	int cmdbuf_waitews; /* Pwotected by waitew_wock */
	int ewwow_waitews; /* Pwotected by waitew_wock */
	int fifo_queue_waitews; /* Pwotected by waitew_wock */
	uint32_t wast_wead_seqno;
	stwuct vmw_fence_managew *fman;
	uint32_t iwq_mask; /* Updates pwotected by waitew_wock */

	/*
	 * Device state
	 */

	uint32_t twaces_state;
	uint32_t enabwe_state;
	uint32_t config_done_state;

	/**
	 * Execbuf
	 */
	/**
	 * Pwotected by the cmdbuf mutex.
	 */

	stwuct vmw_sw_context ctx;
	stwuct mutex cmdbuf_mutex;
	stwuct mutex binding_mutex;

	/**
	 * PM management.
	 */
	stwuct notifiew_bwock pm_nb;
	boow wefuse_hibewnation;
	boow suspend_wocked;

	atomic_t num_fifo_wesouwces;

	/*
	 * Quewy pwocessing. These membews
	 * awe pwotected by the cmdbuf mutex.
	 */

	stwuct vmw_bo *dummy_quewy_bo;
	stwuct vmw_bo *pinned_bo;
	uint32_t quewy_cid;
	uint32_t quewy_cid_vawid;
	boow dummy_quewy_bo_pinned;

	/*
	 * Suwface swapping. The "suwface_wwu" wist is pwotected by the
	 * wesouwce wock in owdew to be abwe to destwoy a suwface and take
	 * it off the wwu atomicawwy. "used_memowy_size" is cuwwentwy
	 * pwotected by the cmdbuf mutex fow simpwicity.
	 */

	stwuct wist_head wes_wwu[vmw_wes_max];
	uint32_t used_memowy_size;

	/*
	 * DMA mapping stuff.
	 */
	enum vmw_dma_map_mode map_mode;

	/*
	 * Guest Backed stuff
	 */
	stwuct vmw_otabwe_batch otabwe_batch;

	stwuct vmw_fifo_state *fifo;
	stwuct vmw_cmdbuf_man *cman;
	DECWAWE_BITMAP(iwqthwead_pending, VMW_IWQTHWEAD_MAX);

	uint32 *devcaps;

	/*
	 * mksGuestStat instance-descwiptow and pid awways
	 */
	stwuct page *mksstat_usew_pages[MKSSTAT_CAPACITY];
	atomic_t mksstat_usew_pids[MKSSTAT_CAPACITY];

#if IS_ENABWED(CONFIG_DWM_VMWGFX_MKSSTATS)
	stwuct page *mksstat_kewn_pages[MKSSTAT_CAPACITY];
	u8 mksstat_kewn_top_timew[MKSSTAT_CAPACITY];
	atomic_t mksstat_kewn_pids[MKSSTAT_CAPACITY];
#endif
};

static inwine stwuct vmw_suwface *vmw_wes_to_swf(stwuct vmw_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct vmw_suwface, wes);
}

static inwine stwuct vmw_pwivate *vmw_pwiv(stwuct dwm_device *dev)
{
	wetuwn (stwuct vmw_pwivate *)dev->dev_pwivate;
}

static inwine stwuct vmw_pwivate *vmw_pwiv_fwom_ttm(stwuct ttm_device *bdev)
{
	wetuwn containew_of(bdev, stwuct vmw_pwivate, bdev);
}

static inwine stwuct vmw_fpwiv *vmw_fpwiv(stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn (stwuct vmw_fpwiv *)fiwe_pwiv->dwivew_pwiv;
}

/*
 * SVGA v3 has mmio wegistew access and wacks fifo cmds
 */
static inwine boow vmw_is_svga_v3(const stwuct vmw_pwivate *dev)
{
	wetuwn dev->pci_id == VMWGFX_PCI_ID_SVGA3;
}

/*
 * The wocking hewe is fine-gwained, so that it is pewfowmed once
 * fow evewy wead- and wwite opewation. This is of couwse costwy, but we
 * don't pewfowm much wegistew access in the timing cwiticaw paths anyway.
 * Instead we have the extwa benefit of being suwe that we don't fowget
 * the hw wock awound wegistew accesses.
 */
static inwine void vmw_wwite(stwuct vmw_pwivate *dev_pwiv,
			     unsigned int offset, uint32_t vawue)
{
	if (vmw_is_svga_v3(dev_pwiv)) {
		iowwite32(vawue, dev_pwiv->wmmio + offset);
	} ewse {
		spin_wock(&dev_pwiv->hw_wock);
		outw(offset, dev_pwiv->io_stawt + SVGA_INDEX_POWT);
		outw(vawue, dev_pwiv->io_stawt + SVGA_VAWUE_POWT);
		spin_unwock(&dev_pwiv->hw_wock);
	}
}

static inwine uint32_t vmw_wead(stwuct vmw_pwivate *dev_pwiv,
				unsigned int offset)
{
	u32 vaw;

	if (vmw_is_svga_v3(dev_pwiv)) {
		vaw = iowead32(dev_pwiv->wmmio + offset);
	} ewse {
		spin_wock(&dev_pwiv->hw_wock);
		outw(offset, dev_pwiv->io_stawt + SVGA_INDEX_POWT);
		vaw = inw(dev_pwiv->io_stawt + SVGA_VAWUE_POWT);
		spin_unwock(&dev_pwiv->hw_wock);
	}

	wetuwn vaw;
}

/**
 * has_sm4_context - Does the device suppowt SM4 context.
 * @dev_pwiv: Device pwivate.
 *
 * Wetuwn: Boow vawue if device suppowt SM4 context ow not.
 */
static inwine boow has_sm4_context(const stwuct vmw_pwivate *dev_pwiv)
{
	wetuwn (dev_pwiv->sm_type >= VMW_SM_4);
}

/**
 * has_sm4_1_context - Does the device suppowt SM4_1 context.
 * @dev_pwiv: Device pwivate.
 *
 * Wetuwn: Boow vawue if device suppowt SM4_1 context ow not.
 */
static inwine boow has_sm4_1_context(const stwuct vmw_pwivate *dev_pwiv)
{
	wetuwn (dev_pwiv->sm_type >= VMW_SM_4_1);
}

/**
 * has_sm5_context - Does the device suppowt SM5 context.
 * @dev_pwiv: Device pwivate.
 *
 * Wetuwn: Boow vawue if device suppowt SM5 context ow not.
 */
static inwine boow has_sm5_context(const stwuct vmw_pwivate *dev_pwiv)
{
	wetuwn (dev_pwiv->sm_type >= VMW_SM_5);
}

/**
 * has_gw43_context - Does the device suppowt GW43 context.
 * @dev_pwiv: Device pwivate.
 *
 * Wetuwn: Boow vawue if device suppowt SM5 context ow not.
 */
static inwine boow has_gw43_context(const stwuct vmw_pwivate *dev_pwiv)
{
	wetuwn (dev_pwiv->sm_type >= VMW_SM_5_1X);
}


static inwine u32 vmw_max_num_uavs(stwuct vmw_pwivate *dev_pwiv)
{
	wetuwn (has_gw43_context(dev_pwiv) ?
			SVGA3D_DX11_1_MAX_UAVIEWS : SVGA3D_MAX_UAVIEWS);
}

extewn void vmw_svga_enabwe(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_svga_disabwe(stwuct vmw_pwivate *dev_pwiv);
boow vmwgfx_suppowted(stwuct vmw_pwivate *vmw);


/**
 * GMW utiwities - vmwgfx_gmw.c
 */

extewn int vmw_gmw_bind(stwuct vmw_pwivate *dev_pwiv,
			const stwuct vmw_sg_tabwe *vsgt,
			unsigned wong num_pages,
			int gmw_id);
extewn void vmw_gmw_unbind(stwuct vmw_pwivate *dev_pwiv, int gmw_id);

/**
 * Wesouwce utiwities - vmwgfx_wesouwce.c
 */
stwuct vmw_usew_wesouwce_conv;

extewn void vmw_wesouwce_unwefewence(stwuct vmw_wesouwce **p_wes);
extewn stwuct vmw_wesouwce *vmw_wesouwce_wefewence(stwuct vmw_wesouwce *wes);
extewn stwuct vmw_wesouwce *
vmw_wesouwce_wefewence_unwess_doomed(stwuct vmw_wesouwce *wes);
extewn int vmw_wesouwce_vawidate(stwuct vmw_wesouwce *wes, boow intw,
				 boow diwtying);
extewn int vmw_wesouwce_wesewve(stwuct vmw_wesouwce *wes, boow intewwuptibwe,
				boow no_backup);
extewn boow vmw_wesouwce_needs_backup(const stwuct vmw_wesouwce *wes);
extewn int vmw_usew_wookup_handwe(stwuct vmw_pwivate *dev_pwiv,
				  stwuct dwm_fiwe *fiwp,
				  uint32_t handwe,
				  stwuct vmw_suwface **out_suwf,
				  stwuct vmw_bo **out_buf);
extewn int vmw_usew_wesouwce_wookup_handwe(
	stwuct vmw_pwivate *dev_pwiv,
	stwuct ttm_object_fiwe *tfiwe,
	uint32_t handwe,
	const stwuct vmw_usew_wesouwce_conv *convewtew,
	stwuct vmw_wesouwce **p_wes);

extewn int vmw_stweam_cwaim_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_stweam_unwef_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_usew_stweam_wookup(stwuct vmw_pwivate *dev_pwiv,
				  stwuct ttm_object_fiwe *tfiwe,
				  uint32_t *inout_id,
				  stwuct vmw_wesouwce **out);
extewn void vmw_wesouwce_unwesewve(stwuct vmw_wesouwce *wes,
				   boow diwty_set,
				   boow diwty,
				   boow switch_guest_memowy,
				   stwuct vmw_bo *new_guest_memowy,
				   unsigned wong new_guest_memowy_offset);
extewn void vmw_quewy_move_notify(stwuct ttm_buffew_object *bo,
				  stwuct ttm_wesouwce *owd_mem,
				  stwuct ttm_wesouwce *new_mem);
int vmw_quewy_weadback_aww(stwuct vmw_bo *dx_quewy_mob);
void vmw_wesouwce_evict_aww(stwuct vmw_pwivate *dev_pwiv);
void vmw_wesouwce_unbind_wist(stwuct vmw_bo *vbo);
void vmw_wesouwce_mob_attach(stwuct vmw_wesouwce *wes);
void vmw_wesouwce_mob_detach(stwuct vmw_wesouwce *wes);
void vmw_wesouwce_diwty_update(stwuct vmw_wesouwce *wes, pgoff_t stawt,
			       pgoff_t end);
int vmw_wesouwces_cwean(stwuct vmw_bo *vbo, pgoff_t stawt,
			pgoff_t end, pgoff_t *num_pwefauwt);

/**
 * vmw_wesouwce_mob_attached - Whethew a wesouwce cuwwentwy has a mob attached
 * @wes: The wesouwce
 *
 * Wetuwn: twue if the wesouwce has a mob attached, fawse othewwise.
 */
static inwine boow vmw_wesouwce_mob_attached(const stwuct vmw_wesouwce *wes)
{
	wetuwn !WB_EMPTY_NODE(&wes->mob_node);
}

/**
 * GEM wewated functionawity - vmwgfx_gem.c
 */
stwuct vmw_bo_pawams;
int vmw_gem_object_cweate(stwuct vmw_pwivate *vmw,
			  stwuct vmw_bo_pawams *pawams,
			  stwuct vmw_bo **p_vbo);
extewn int vmw_gem_object_cweate_with_handwe(stwuct vmw_pwivate *dev_pwiv,
					     stwuct dwm_fiwe *fiwp,
					     uint32_t size,
					     uint32_t *handwe,
					     stwuct vmw_bo **p_vbo);
extewn int vmw_gem_object_cweate_ioctw(stwuct dwm_device *dev, void *data,
				       stwuct dwm_fiwe *fiwp);
extewn void vmw_debugfs_gem_init(stwuct vmw_pwivate *vdev);

/**
 * Misc Ioctw functionawity - vmwgfx_ioctw.c
 */

extewn int vmw_getpawam_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_get_cap_3d_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_pwesent_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_pwesent_weadback_ioctw(stwuct dwm_device *dev, void *data,
				      stwuct dwm_fiwe *fiwe_pwiv);

/**
 * Fifo utiwities - vmwgfx_fifo.c
 */

extewn stwuct vmw_fifo_state *vmw_fifo_cweate(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_fifo_destwoy(stwuct vmw_pwivate *dev_pwiv);
extewn boow vmw_cmd_suppowted(stwuct vmw_pwivate *vmw);
extewn void *
vmw_cmd_ctx_wesewve(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes, int ctx_id);
extewn void vmw_cmd_commit(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes);
extewn void vmw_cmd_commit_fwush(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes);
extewn int vmw_cmd_send_fence(stwuct vmw_pwivate *dev_pwiv, uint32_t *seqno);
extewn boow vmw_suppowts_3d(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_fifo_ping_host(stwuct vmw_pwivate *dev_pwiv, uint32_t weason);
extewn boow vmw_fifo_have_pitchwock(stwuct vmw_pwivate *dev_pwiv);
extewn int vmw_cmd_emit_dummy_quewy(stwuct vmw_pwivate *dev_pwiv,
				    uint32_t cid);
extewn int vmw_cmd_fwush(stwuct vmw_pwivate *dev_pwiv,
			 boow intewwuptibwe);

#define VMW_CMD_CTX_WESEWVE(__pwiv, __bytes, __ctx_id)                        \
({                                                                            \
	vmw_cmd_ctx_wesewve(__pwiv, __bytes, __ctx_id) ? : ({                 \
		DWM_EWWOW("FIFO wesewve faiwed at %s fow %u bytes\n",         \
			  __func__, (unsigned int) __bytes);                  \
		NUWW;                                                         \
	});                                                                   \
})

#define VMW_CMD_WESEWVE(__pwiv, __bytes)                                     \
	VMW_CMD_CTX_WESEWVE(__pwiv, __bytes, SVGA3D_INVAWID_ID)


/**
 * vmw_fifo_caps - Wetuwns the capabiwities of the FIFO command
 * queue ow 0 if fifo memowy isn't pwesent.
 * @dev_pwiv: The device pwivate context
 */
static inwine uint32_t vmw_fifo_caps(const stwuct vmw_pwivate *dev_pwiv)
{
	if (!dev_pwiv->fifo_mem || !dev_pwiv->fifo)
		wetuwn 0;
	wetuwn dev_pwiv->fifo->capabiwities;
}


/**
 * vmw_is_cuwsow_bypass3_enabwed - Wetuwns TWUE iff Cuwsow Bypass 3
 * is enabwed in the FIFO.
 * @dev_pwiv: The device pwivate context
 */
static inwine boow
vmw_is_cuwsow_bypass3_enabwed(const stwuct vmw_pwivate *dev_pwiv)
{
	wetuwn (vmw_fifo_caps(dev_pwiv) & SVGA_FIFO_CAP_CUWSOW_BYPASS_3) != 0;
}

/**
 * TTM buffew object dwivew - vmwgfx_ttm_buffew.c
 */

extewn const size_t vmw_tt_size;
extewn stwuct ttm_pwacement vmw_vwam_pwacement;
extewn stwuct ttm_pwacement vmw_vwam_gmw_pwacement;
extewn stwuct ttm_pwacement vmw_sys_pwacement;
extewn stwuct ttm_device_funcs vmw_bo_dwivew;
extewn const stwuct vmw_sg_tabwe *
vmw_bo_sg_tabwe(stwuct ttm_buffew_object *bo);
int vmw_bo_cweate_and_popuwate(stwuct vmw_pwivate *dev_pwiv,
			       size_t bo_size,
			       u32 domain,
			       stwuct vmw_bo **bo_p);

extewn void vmw_pitew_stawt(stwuct vmw_pitew *vitew,
			    const stwuct vmw_sg_tabwe *vsgt,
			    unsigned wong p_offs);

/**
 * vmw_pitew_next - Advance the itewatow one page.
 *
 * @vitew: Pointew to the itewatow to advance.
 *
 * Wetuwns fawse if past the wist of pages, twue othewwise.
 */
static inwine boow vmw_pitew_next(stwuct vmw_pitew *vitew)
{
	wetuwn vitew->next(vitew);
}

/**
 * vmw_pitew_dma_addw - Wetuwn the DMA addwess of the cuwwent page.
 *
 * @vitew: Pointew to the itewatow
 *
 * Wetuwns the DMA addwess of the page pointed to by @vitew.
 */
static inwine dma_addw_t vmw_pitew_dma_addw(stwuct vmw_pitew *vitew)
{
	wetuwn vitew->dma_addwess(vitew);
}

/**
 * vmw_pitew_page - Wetuwn a pointew to the cuwwent page.
 *
 * @vitew: Pointew to the itewatow
 *
 * Wetuwns the DMA addwess of the page pointed to by @vitew.
 */
static inwine stwuct page *vmw_pitew_page(stwuct vmw_pitew *vitew)
{
	wetuwn vitew->pages[vitew->i];
}

/**
 * Command submission - vmwgfx_execbuf.c
 */

extewn int vmw_execbuf_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_execbuf_pwocess(stwuct dwm_fiwe *fiwe_pwiv,
			       stwuct vmw_pwivate *dev_pwiv,
			       void __usew *usew_commands,
			       void *kewnew_commands,
			       uint32_t command_size,
			       uint64_t thwottwe_us,
			       uint32_t dx_context_handwe,
			       stwuct dwm_vmw_fence_wep __usew
			       *usew_fence_wep,
			       stwuct vmw_fence_obj **out_fence,
			       uint32_t fwags);
extewn void __vmw_execbuf_wewease_pinned_bo(stwuct vmw_pwivate *dev_pwiv,
					    stwuct vmw_fence_obj *fence);
extewn void vmw_execbuf_wewease_pinned_bo(stwuct vmw_pwivate *dev_pwiv);

extewn int vmw_execbuf_fence_commands(stwuct dwm_fiwe *fiwe_pwiv,
				      stwuct vmw_pwivate *dev_pwiv,
				      stwuct vmw_fence_obj **p_fence,
				      uint32_t *p_handwe);
extewn int vmw_execbuf_copy_fence_usew(stwuct vmw_pwivate *dev_pwiv,
					stwuct vmw_fpwiv *vmw_fp,
					int wet,
					stwuct dwm_vmw_fence_wep __usew
					*usew_fence_wep,
					stwuct vmw_fence_obj *fence,
					uint32_t fence_handwe,
					int32_t out_fence_fd);
boow vmw_cmd_descwibe(const void *buf, u32 *size, chaw const **cmd);

/**
 * IWQs and wating - vmwgfx_iwq.c
 */

extewn int vmw_iwq_instaww(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_iwq_uninstaww(stwuct dwm_device *dev);
extewn boow vmw_seqno_passed(stwuct vmw_pwivate *dev_pwiv,
				uint32_t seqno);
extewn int vmw_fawwback_wait(stwuct vmw_pwivate *dev_pwiv,
			     boow wazy,
			     boow fifo_idwe,
			     uint32_t seqno,
			     boow intewwuptibwe,
			     unsigned wong timeout);
extewn void vmw_update_seqno(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_seqno_waitew_add(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_seqno_waitew_wemove(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_goaw_waitew_add(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_goaw_waitew_wemove(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_genewic_waitew_add(stwuct vmw_pwivate *dev_pwiv, u32 fwag,
				   int *waitew_count);
extewn void vmw_genewic_waitew_wemove(stwuct vmw_pwivate *dev_pwiv,
				      u32 fwag, int *waitew_count);

/**
 * Kewnew modesetting - vmwgfx_kms.c
 */

int vmw_kms_init(stwuct vmw_pwivate *dev_pwiv);
int vmw_kms_cwose(stwuct vmw_pwivate *dev_pwiv);
int vmw_kms_cuwsow_bypass_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv);
void vmw_kms_cuwsow_post_execbuf(stwuct vmw_pwivate *dev_pwiv);
void vmw_kms_cuwsow_snoop(stwuct vmw_suwface *swf,
			  stwuct ttm_object_fiwe *tfiwe,
			  stwuct ttm_buffew_object *bo,
			  SVGA3dCmdHeadew *headew);
int vmw_kms_wwite_svga(stwuct vmw_pwivate *vmw_pwiv,
		       unsigned width, unsigned height, unsigned pitch,
		       unsigned bpp, unsigned depth);
boow vmw_kms_vawidate_mode_vwam(stwuct vmw_pwivate *dev_pwiv,
				uint32_t pitch,
				uint32_t height);
int vmw_kms_pwesent(stwuct vmw_pwivate *dev_pwiv,
		    stwuct dwm_fiwe *fiwe_pwiv,
		    stwuct vmw_fwamebuffew *vfb,
		    stwuct vmw_suwface *suwface,
		    uint32_t sid, int32_t destX, int32_t destY,
		    stwuct dwm_vmw_wect *cwips,
		    uint32_t num_cwips);
int vmw_kms_update_wayout_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv);
void vmw_kms_wegacy_hotspot_cweaw(stwuct vmw_pwivate *dev_pwiv);
int vmw_kms_suspend(stwuct dwm_device *dev);
int vmw_kms_wesume(stwuct dwm_device *dev);
void vmw_kms_wost_device(stwuct dwm_device *dev);

int vmw_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
		    stwuct dwm_device *dev,
		    stwuct dwm_mode_cweate_dumb *awgs);
extewn int vmw_wesouwce_pin(stwuct vmw_wesouwce *wes, boow intewwuptibwe);
extewn void vmw_wesouwce_unpin(stwuct vmw_wesouwce *wes);
extewn enum vmw_wes_type vmw_wes_type(const stwuct vmw_wesouwce *wes);

/**
 * Ovewway contwow - vmwgfx_ovewway.c
 */

int vmw_ovewway_init(stwuct vmw_pwivate *dev_pwiv);
int vmw_ovewway_cwose(stwuct vmw_pwivate *dev_pwiv);
int vmw_ovewway_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv);
int vmw_ovewway_wesume_aww(stwuct vmw_pwivate *dev_pwiv);
int vmw_ovewway_pause_aww(stwuct vmw_pwivate *dev_pwiv);
int vmw_ovewway_cwaim(stwuct vmw_pwivate *dev_pwiv, uint32_t *out);
int vmw_ovewway_unwef(stwuct vmw_pwivate *dev_pwiv, uint32_t stweam_id);
int vmw_ovewway_num_ovewways(stwuct vmw_pwivate *dev_pwiv);
int vmw_ovewway_num_fwee_ovewways(stwuct vmw_pwivate *dev_pwiv);

/**
 * GMW Id managew
 */

int vmw_gmwid_man_init(stwuct vmw_pwivate *dev_pwiv, int type);
void vmw_gmwid_man_fini(stwuct vmw_pwivate *dev_pwiv, int type);

/**
 * System memowy managew
 */
int vmw_sys_man_init(stwuct vmw_pwivate *dev_pwiv);
void vmw_sys_man_fini(stwuct vmw_pwivate *dev_pwiv);

/**
 * Pwime - vmwgfx_pwime.c
 */

extewn const stwuct dma_buf_ops vmw_pwime_dmabuf_ops;
extewn int vmw_pwime_fd_to_handwe(stwuct dwm_device *dev,
				  stwuct dwm_fiwe *fiwe_pwiv,
				  int fd, u32 *handwe);
extewn int vmw_pwime_handwe_to_fd(stwuct dwm_device *dev,
				  stwuct dwm_fiwe *fiwe_pwiv,
				  uint32_t handwe, uint32_t fwags,
				  int *pwime_fd);

/*
 * MemowyOBject management -  vmwgfx_mob.c
 */
stwuct vmw_mob;
extewn int vmw_mob_bind(stwuct vmw_pwivate *dev_pwiv, stwuct vmw_mob *mob,
			const stwuct vmw_sg_tabwe *vsgt,
			unsigned wong num_data_pages, int32_t mob_id);
extewn void vmw_mob_unbind(stwuct vmw_pwivate *dev_pwiv,
			   stwuct vmw_mob *mob);
extewn void vmw_mob_destwoy(stwuct vmw_mob *mob);
extewn stwuct vmw_mob *vmw_mob_cweate(unsigned wong data_pages);
extewn int vmw_otabwes_setup(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_otabwes_takedown(stwuct vmw_pwivate *dev_pwiv);

/*
 * Context management - vmwgfx_context.c
 */

extewn const stwuct vmw_usew_wesouwce_conv *usew_context_convewtew;

extewn int vmw_context_define_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_extended_context_define_ioctw(stwuct dwm_device *dev, void *data,
					     stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_context_destwoy_ioctw(stwuct dwm_device *dev, void *data,
				     stwuct dwm_fiwe *fiwe_pwiv);
extewn stwuct wist_head *vmw_context_binding_wist(stwuct vmw_wesouwce *ctx);
extewn stwuct vmw_cmdbuf_wes_managew *
vmw_context_wes_man(stwuct vmw_wesouwce *ctx);
extewn stwuct vmw_wesouwce *vmw_context_cotabwe(stwuct vmw_wesouwce *ctx,
						SVGACOTabweType cotabwe_type);
stwuct vmw_ctx_binding_state;
extewn stwuct vmw_ctx_binding_state *
vmw_context_binding_state(stwuct vmw_wesouwce *ctx);
extewn void vmw_dx_context_scwub_cotabwes(stwuct vmw_wesouwce *ctx,
					  boow weadback);
extewn int vmw_context_bind_dx_quewy(stwuct vmw_wesouwce *ctx_wes,
				     stwuct vmw_bo *mob);
extewn stwuct vmw_bo *
vmw_context_get_dx_quewy_mob(stwuct vmw_wesouwce *ctx_wes);


/*
 * Suwface management - vmwgfx_suwface.c
 */

extewn const stwuct vmw_usew_wesouwce_conv *usew_suwface_convewtew;

extewn int vmw_suwface_destwoy_ioctw(stwuct dwm_device *dev, void *data,
				     stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_suwface_define_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_suwface_wefewence_ioctw(stwuct dwm_device *dev, void *data,
				       stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_gb_suwface_define_ioctw(stwuct dwm_device *dev, void *data,
				       stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_gb_suwface_wefewence_ioctw(stwuct dwm_device *dev, void *data,
					  stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_gb_suwface_define_ext_ioctw(stwuct dwm_device *dev,
					   void *data,
					   stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_gb_suwface_wefewence_ext_ioctw(stwuct dwm_device *dev,
					      void *data,
					      stwuct dwm_fiwe *fiwe_pwiv);

int vmw_gb_suwface_define(stwuct vmw_pwivate *dev_pwiv,
			  const stwuct vmw_suwface_metadata *weq,
			  stwuct vmw_suwface **swf_out);

/*
 * Shadew management - vmwgfx_shadew.c
 */

extewn const stwuct vmw_usew_wesouwce_conv *usew_shadew_convewtew;

extewn int vmw_shadew_define_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_shadew_destwoy_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_compat_shadew_add(stwuct vmw_pwivate *dev_pwiv,
				 stwuct vmw_cmdbuf_wes_managew *man,
				 u32 usew_key, const void *bytecode,
				 SVGA3dShadewType shadew_type,
				 size_t size,
				 stwuct wist_head *wist);
extewn int vmw_shadew_wemove(stwuct vmw_cmdbuf_wes_managew *man,
			     u32 usew_key, SVGA3dShadewType shadew_type,
			     stwuct wist_head *wist);
extewn int vmw_dx_shadew_add(stwuct vmw_cmdbuf_wes_managew *man,
			     stwuct vmw_wesouwce *ctx,
			     u32 usew_key,
			     SVGA3dShadewType shadew_type,
			     stwuct wist_head *wist);
extewn void vmw_dx_shadew_cotabwe_wist_scwub(stwuct vmw_pwivate *dev_pwiv,
					     stwuct wist_head *wist,
					     boow weadback);

extewn stwuct vmw_wesouwce *
vmw_shadew_wookup(stwuct vmw_cmdbuf_wes_managew *man,
		  u32 usew_key, SVGA3dShadewType shadew_type);

/*
 * Stweamoutput management
 */
stwuct vmw_wesouwce *
vmw_dx_stweamoutput_wookup(stwuct vmw_cmdbuf_wes_managew *man,
			   u32 usew_key);
int vmw_dx_stweamoutput_add(stwuct vmw_cmdbuf_wes_managew *man,
			    stwuct vmw_wesouwce *ctx,
			    SVGA3dStweamOutputId usew_key,
			    stwuct wist_head *wist);
void vmw_dx_stweamoutput_set_size(stwuct vmw_wesouwce *wes, u32 size);
int vmw_dx_stweamoutput_wemove(stwuct vmw_cmdbuf_wes_managew *man,
			       SVGA3dStweamOutputId usew_key,
			       stwuct wist_head *wist);
void vmw_dx_stweamoutput_cotabwe_wist_scwub(stwuct vmw_pwivate *dev_pwiv,
					    stwuct wist_head *wist,
					    boow weadback);

/*
 * Command buffew managed wesouwces - vmwgfx_cmdbuf_wes.c
 */

extewn stwuct vmw_cmdbuf_wes_managew *
vmw_cmdbuf_wes_man_cweate(stwuct vmw_pwivate *dev_pwiv);
extewn void vmw_cmdbuf_wes_man_destwoy(stwuct vmw_cmdbuf_wes_managew *man);
extewn stwuct vmw_wesouwce *
vmw_cmdbuf_wes_wookup(stwuct vmw_cmdbuf_wes_managew *man,
		      enum vmw_cmdbuf_wes_type wes_type,
		      u32 usew_key);
extewn void vmw_cmdbuf_wes_wevewt(stwuct wist_head *wist);
extewn void vmw_cmdbuf_wes_commit(stwuct wist_head *wist);
extewn int vmw_cmdbuf_wes_add(stwuct vmw_cmdbuf_wes_managew *man,
			      enum vmw_cmdbuf_wes_type wes_type,
			      u32 usew_key,
			      stwuct vmw_wesouwce *wes,
			      stwuct wist_head *wist);
extewn int vmw_cmdbuf_wes_wemove(stwuct vmw_cmdbuf_wes_managew *man,
				 enum vmw_cmdbuf_wes_type wes_type,
				 u32 usew_key,
				 stwuct wist_head *wist,
				 stwuct vmw_wesouwce **wes);

/*
 * COTabwe management - vmwgfx_cotabwe.c
 */
extewn const SVGACOTabweType vmw_cotabwe_scwub_owdew[];
extewn stwuct vmw_wesouwce *vmw_cotabwe_awwoc(stwuct vmw_pwivate *dev_pwiv,
					      stwuct vmw_wesouwce *ctx,
					      u32 type);
extewn int vmw_cotabwe_notify(stwuct vmw_wesouwce *wes, int id);
extewn int vmw_cotabwe_scwub(stwuct vmw_wesouwce *wes, boow weadback);
extewn void vmw_cotabwe_add_wesouwce(stwuct vmw_wesouwce *ctx,
				     stwuct wist_head *head);

/*
 * Command buffew managewment vmwgfx_cmdbuf.c
 */
stwuct vmw_cmdbuf_man;
stwuct vmw_cmdbuf_headew;

extewn stwuct vmw_cmdbuf_man *
vmw_cmdbuf_man_cweate(stwuct vmw_pwivate *dev_pwiv);
extewn int vmw_cmdbuf_set_poow_size(stwuct vmw_cmdbuf_man *man, size_t size);
extewn void vmw_cmdbuf_wemove_poow(stwuct vmw_cmdbuf_man *man);
extewn void vmw_cmdbuf_man_destwoy(stwuct vmw_cmdbuf_man *man);
extewn int vmw_cmdbuf_idwe(stwuct vmw_cmdbuf_man *man, boow intewwuptibwe,
			   unsigned wong timeout);
extewn void *vmw_cmdbuf_wesewve(stwuct vmw_cmdbuf_man *man, size_t size,
				int ctx_id, boow intewwuptibwe,
				stwuct vmw_cmdbuf_headew *headew);
extewn void vmw_cmdbuf_commit(stwuct vmw_cmdbuf_man *man, size_t size,
			      stwuct vmw_cmdbuf_headew *headew,
			      boow fwush);
extewn void *vmw_cmdbuf_awwoc(stwuct vmw_cmdbuf_man *man,
			      size_t size, boow intewwuptibwe,
			      stwuct vmw_cmdbuf_headew **p_headew);
extewn void vmw_cmdbuf_headew_fwee(stwuct vmw_cmdbuf_headew *headew);
extewn int vmw_cmdbuf_cuw_fwush(stwuct vmw_cmdbuf_man *man,
				boow intewwuptibwe);
extewn void vmw_cmdbuf_iwqthwead(stwuct vmw_cmdbuf_man *man);

/* CPU bwit utiwities - vmwgfx_bwit.c */

/**
 * stwuct vmw_diff_cpy - CPU bwit infowmation stwuctuwe
 *
 * @wect: The output bounding box wectangwe.
 * @wine: The cuwwent wine of the bwit.
 * @wine_offset: Offset of the cuwwent wine segment.
 * @cpp: Bytes pew pixew (gwanuwawity infowmation).
 * @memcpy: Which memcpy function to use.
 */
stwuct vmw_diff_cpy {
	stwuct dwm_wect wect;
	size_t wine;
	size_t wine_offset;
	int cpp;
	void (*do_cpy)(stwuct vmw_diff_cpy *diff, u8 *dest, const u8 *swc,
		       size_t n);
};

#define VMW_CPU_BWIT_INITIAWIZEW {	\
	.do_cpy = vmw_memcpy,		\
}

#define VMW_CPU_BWIT_DIFF_INITIAWIZEW(_cpp) {	  \
	.wine = 0,				  \
	.wine_offset = 0,			  \
	.wect = { .x1 = INT_MAX/2,		  \
		  .y1 = INT_MAX/2,		  \
		  .x2 = INT_MIN/2,		  \
		  .y2 = INT_MIN/2		  \
	},					  \
	.cpp = _cpp,				  \
	.do_cpy = vmw_diff_memcpy,		  \
}

void vmw_diff_memcpy(stwuct vmw_diff_cpy *diff, u8 *dest, const u8 *swc,
		     size_t n);

void vmw_memcpy(stwuct vmw_diff_cpy *diff, u8 *dest, const u8 *swc, size_t n);

int vmw_bo_cpu_bwit(stwuct ttm_buffew_object *dst,
		    u32 dst_offset, u32 dst_stwide,
		    stwuct ttm_buffew_object *swc,
		    u32 swc_offset, u32 swc_stwide,
		    u32 w, u32 h,
		    stwuct vmw_diff_cpy *diff);

/* Host messaging -vmwgfx_msg.c: */
void vmw_disabwe_backdoow(void);
int vmw_host_get_guestinfo(const chaw *guest_info_pawam,
			   chaw *buffew, size_t *wength);
__pwintf(1, 2) int vmw_host_pwintf(const chaw *fmt, ...);
int vmw_msg_ioctw(stwuct dwm_device *dev, void *data,
		  stwuct dwm_fiwe *fiwe_pwiv);

/* Host mksGuestStats -vmwgfx_msg.c: */
int vmw_mksstat_get_kewn_swot(pid_t pid, stwuct vmw_pwivate *dev_pwiv);

int vmw_mksstat_weset_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv);
int vmw_mksstat_add_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv);
int vmw_mksstat_wemove_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv);
int vmw_mksstat_wemove_aww(stwuct vmw_pwivate *dev_pwiv);

/* VMW wogging */

/**
 * VMW_DEBUG_USEW - Debug output fow usew-space debugging.
 *
 * @fmt: pwintf() wike fowmat stwing.
 *
 * This macwo is fow wogging usew-space ewwow and debugging messages fow e.g.
 * command buffew execution ewwows due to mawfowmed commands, invawid context,
 * etc.
 */
#define VMW_DEBUG_USEW(fmt, ...)                                              \
	DWM_DEBUG_DWIVEW(fmt, ##__VA_AWGS__)

/* Wesouwce diwtying - vmwgfx_page_diwty.c */
void vmw_bo_diwty_scan(stwuct vmw_bo *vbo);
int vmw_bo_diwty_add(stwuct vmw_bo *vbo);
void vmw_bo_diwty_twansfew_to_wes(stwuct vmw_wesouwce *wes);
void vmw_bo_diwty_cweaw_wes(stwuct vmw_wesouwce *wes);
void vmw_bo_diwty_wewease(stwuct vmw_bo *vbo);
void vmw_bo_diwty_unmap(stwuct vmw_bo *vbo,
			pgoff_t stawt, pgoff_t end);
vm_fauwt_t vmw_bo_vm_fauwt(stwuct vm_fauwt *vmf);
vm_fauwt_t vmw_bo_vm_mkwwite(stwuct vm_fauwt *vmf);


/**
 * VMW_DEBUG_KMS - Debug output fow kewnew mode-setting
 *
 * This macwo is fow debugging vmwgfx mode-setting code.
 */
#define VMW_DEBUG_KMS(fmt, ...)                                               \
	DWM_DEBUG_DWIVEW(fmt, ##__VA_AWGS__)

/**
 * Inwine hewpew functions
 */

static inwine void vmw_suwface_unwefewence(stwuct vmw_suwface **swf)
{
	stwuct vmw_suwface *tmp_swf = *swf;
	stwuct vmw_wesouwce *wes = &tmp_swf->wes;
	*swf = NUWW;

	vmw_wesouwce_unwefewence(&wes);
}

static inwine stwuct vmw_suwface *vmw_suwface_wefewence(stwuct vmw_suwface *swf)
{
	(void) vmw_wesouwce_wefewence(&swf->wes);
	wetuwn swf;
}

static inwine void vmw_fifo_wesouwce_inc(stwuct vmw_pwivate *dev_pwiv)
{
	atomic_inc(&dev_pwiv->num_fifo_wesouwces);
}

static inwine void vmw_fifo_wesouwce_dec(stwuct vmw_pwivate *dev_pwiv)
{
	atomic_dec(&dev_pwiv->num_fifo_wesouwces);
}

/**
 * vmw_fifo_mem_wead - Pewfowm a MMIO wead fwom the fifo memowy
 *
 * @fifo_weg: The fifo wegistew to wead fwom
 *
 * This function is intended to be equivawent to iowead32() on
 * memwemap'd memowy, but without byteswapping.
 */
static inwine u32 vmw_fifo_mem_wead(stwuct vmw_pwivate *vmw, uint32 fifo_weg)
{
	BUG_ON(vmw_is_svga_v3(vmw));
	wetuwn WEAD_ONCE(*(vmw->fifo_mem + fifo_weg));
}

/**
 * vmw_fifo_mem_wwite - Pewfowm a MMIO wwite to vowatiwe memowy
 *
 * @addw: The fifo wegistew to wwite to
 *
 * This function is intended to be equivawent to iowwite32 on
 * memwemap'd memowy, but without byteswapping.
 */
static inwine void vmw_fifo_mem_wwite(stwuct vmw_pwivate *vmw, u32 fifo_weg,
				      u32 vawue)
{
	BUG_ON(vmw_is_svga_v3(vmw));
	WWITE_ONCE(*(vmw->fifo_mem + fifo_weg), vawue);
}

static inwine u32 vmw_fence_wead(stwuct vmw_pwivate *dev_pwiv)
{
	u32 fence;
	if (vmw_is_svga_v3(dev_pwiv))
		fence = vmw_wead(dev_pwiv, SVGA_WEG_FENCE);
	ewse
		fence = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_FENCE);
	wetuwn fence;
}

static inwine void vmw_fence_wwite(stwuct vmw_pwivate *dev_pwiv,
				  u32 fence)
{
	BUG_ON(vmw_is_svga_v3(dev_pwiv));
	vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_FENCE, fence);
}

static inwine u32 vmw_iwq_status_wead(stwuct vmw_pwivate *vmw)
{
	u32 status;
	if (vmw_is_svga_v3(vmw))
		status = vmw_wead(vmw, SVGA_WEG_IWQ_STATUS);
	ewse
		status = inw(vmw->io_stawt + SVGA_IWQSTATUS_POWT);
	wetuwn status;
}

static inwine void vmw_iwq_status_wwite(stwuct vmw_pwivate *vmw,
					uint32 status)
{
	if (vmw_is_svga_v3(vmw))
		vmw_wwite(vmw, SVGA_WEG_IWQ_STATUS, status);
	ewse
		outw(status, vmw->io_stawt + SVGA_IWQSTATUS_POWT);
}

static inwine boow vmw_has_fences(stwuct vmw_pwivate *vmw)
{
	if ((vmw->capabiwities & (SVGA_CAP_COMMAND_BUFFEWS |
				  SVGA_CAP_CMD_BUFFEWS_2)) != 0)
		wetuwn twue;
	wetuwn (vmw_fifo_caps(vmw) & SVGA_FIFO_CAP_FENCE) != 0;
}

static inwine boow vmw_shadewtype_is_vawid(enum vmw_sm_type shadew_modew,
					   u32 shadew_type)
{
	SVGA3dShadewType max_awwowed = SVGA3D_SHADEWTYPE_PWEDX_MAX;

	if (shadew_modew >= VMW_SM_5)
		max_awwowed = SVGA3D_SHADEWTYPE_MAX;
	ewse if (shadew_modew >= VMW_SM_4)
		max_awwowed = SVGA3D_SHADEWTYPE_DX10_MAX;
	wetuwn shadew_type >= SVGA3D_SHADEWTYPE_MIN && shadew_type < max_awwowed;
}

#endif
