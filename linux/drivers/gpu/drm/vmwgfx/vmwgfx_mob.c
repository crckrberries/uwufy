// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2012-2023 VMwawe, Inc., Pawo Awto, CA., USA
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

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"

#incwude <winux/highmem.h>

#ifdef CONFIG_64BIT
#define VMW_PPN_SIZE 8
#define VMW_MOBFMT_PTDEPTH_0 SVGA3D_MOBFMT_PT64_0
#define VMW_MOBFMT_PTDEPTH_1 SVGA3D_MOBFMT_PT64_1
#define VMW_MOBFMT_PTDEPTH_2 SVGA3D_MOBFMT_PT64_2
#ewse
#define VMW_PPN_SIZE 4
#define VMW_MOBFMT_PTDEPTH_0 SVGA3D_MOBFMT_PT_0
#define VMW_MOBFMT_PTDEPTH_1 SVGA3D_MOBFMT_PT_1
#define VMW_MOBFMT_PTDEPTH_2 SVGA3D_MOBFMT_PT_2
#endif

/*
 * stwuct vmw_mob - Stwuctuwe containing page tabwe and metadata fow a
 * Guest Memowy OBject.
 *
 * @num_pages       Numbew of pages that make up the page tabwe.
 * @pt_wevew        The indiwection wevew of the page tabwe. 0-2.
 * @pt_woot_page    DMA addwess of the wevew 0 page of the page tabwe.
 */
stwuct vmw_mob {
	stwuct vmw_bo *pt_bo;
	unsigned wong num_pages;
	unsigned pt_wevew;
	dma_addw_t pt_woot_page;
	uint32_t id;
};

/*
 * stwuct vmw_otabwe - Guest Memowy OBject tabwe metadata
 *
 * @size:           Size of the tabwe (page-awigned).
 * @page_tabwe:     Pointew to a stwuct vmw_mob howding the page tabwe.
 */
static const stwuct vmw_otabwe pwe_dx_tabwes[] = {
	{VMWGFX_NUM_MOB * sizeof(SVGAOTabweMobEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_SUWFACE * sizeof(SVGAOTabweSuwfaceEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_CONTEXT * sizeof(SVGAOTabweContextEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_SHADEW * sizeof(SVGAOTabweShadewEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_SCWEEN_TAWGET * sizeof(SVGAOTabweScweenTawgetEntwy),
	 NUWW, twue}
};

static const stwuct vmw_otabwe dx_tabwes[] = {
	{VMWGFX_NUM_MOB * sizeof(SVGAOTabweMobEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_SUWFACE * sizeof(SVGAOTabweSuwfaceEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_CONTEXT * sizeof(SVGAOTabweContextEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_SHADEW * sizeof(SVGAOTabweShadewEntwy), NUWW, twue},
	{VMWGFX_NUM_GB_SCWEEN_TAWGET * sizeof(SVGAOTabweScweenTawgetEntwy),
	 NUWW, twue},
	{VMWGFX_NUM_DXCONTEXT * sizeof(SVGAOTabweDXContextEntwy), NUWW, twue},
};

static int vmw_mob_pt_popuwate(stwuct vmw_pwivate *dev_pwiv,
			       stwuct vmw_mob *mob);
static void vmw_mob_pt_setup(stwuct vmw_mob *mob,
			     stwuct vmw_pitew data_itew,
			     unsigned wong num_data_pages);


static inwine void vmw_bo_unpin_unwocked(stwuct ttm_buffew_object *bo)
{
	int wet = ttm_bo_wesewve(bo, fawse, twue, NUWW);
	BUG_ON(wet != 0);
	ttm_bo_unpin(bo);
	ttm_bo_unwesewve(bo);
}


/*
 * vmw_setup_otabwe_base - Issue an object tabwe base setup command to
 * the device
 *
 * @dev_pwiv:       Pointew to a device pwivate stwuctuwe
 * @type:           Type of object tabwe base
 * @offset          Stawt of tabwe offset into dev_pwiv::otabwe_bo
 * @otabwe          Pointew to otabwe metadata;
 *
 * This function wetuwns -ENOMEM if it faiws to wesewve fifo space,
 * and may bwock waiting fow fifo space.
 */
static int vmw_setup_otabwe_base(stwuct vmw_pwivate *dev_pwiv,
				 SVGAOTabweType type,
				 stwuct ttm_buffew_object *otabwe_bo,
				 unsigned wong offset,
				 stwuct vmw_otabwe *otabwe)
{
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdSetOTabweBase64 body;
	} *cmd;
	stwuct vmw_mob *mob;
	const stwuct vmw_sg_tabwe *vsgt;
	stwuct vmw_pitew itew;
	int wet;

	BUG_ON(otabwe->page_tabwe != NUWW);

	vsgt = vmw_bo_sg_tabwe(otabwe_bo);
	vmw_pitew_stawt(&itew, vsgt, offset >> PAGE_SHIFT);
	WAWN_ON(!vmw_pitew_next(&itew));

	mob = vmw_mob_cweate(otabwe->size >> PAGE_SHIFT);
	if (unwikewy(mob == NUWW)) {
		DWM_EWWOW("Faiwed cweating OTabwe page tabwe.\n");
		wetuwn -ENOMEM;
	}

	if (otabwe->size <= PAGE_SIZE) {
		mob->pt_wevew = VMW_MOBFMT_PTDEPTH_0;
		mob->pt_woot_page = vmw_pitew_dma_addw(&itew);
	} ewse {
		wet = vmw_mob_pt_popuwate(dev_pwiv, mob);
		if (unwikewy(wet != 0))
			goto out_no_popuwate;

		vmw_mob_pt_setup(mob, itew, otabwe->size >> PAGE_SHIFT);
		mob->pt_wevew += VMW_MOBFMT_PTDEPTH_1 - SVGA3D_MOBFMT_PT_1;
	}

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW)) {
		wet = -ENOMEM;
		goto out_no_fifo;
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->headew.id = SVGA_3D_CMD_SET_OTABWE_BASE64;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.type = type;
	cmd->body.baseAddwess = mob->pt_woot_page >> PAGE_SHIFT;
	cmd->body.sizeInBytes = otabwe->size;
	cmd->body.vawidSizeInBytes = 0;
	cmd->body.ptDepth = mob->pt_wevew;

	/*
	 * The device doesn't suppowt this, But the otabwe size is
	 * detewmined at compiwe-time, so this BUG shouwdn't twiggew
	 * wandomwy.
	 */
	BUG_ON(mob->pt_wevew == VMW_MOBFMT_PTDEPTH_2);

	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	otabwe->page_tabwe = mob;

	wetuwn 0;

out_no_fifo:
out_no_popuwate:
	vmw_mob_destwoy(mob);
	wetuwn wet;
}

/*
 * vmw_takedown_otabwe_base - Issue an object tabwe base takedown command
 * to the device
 *
 * @dev_pwiv:       Pointew to a device pwivate stwuctuwe
 * @type:           Type of object tabwe base
 *
 */
static void vmw_takedown_otabwe_base(stwuct vmw_pwivate *dev_pwiv,
				     SVGAOTabweType type,
				     stwuct vmw_otabwe *otabwe)
{
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdSetOTabweBase body;
	} *cmd;
	stwuct ttm_buffew_object *bo;

	if (otabwe->page_tabwe == NUWW)
		wetuwn;

	bo = &otabwe->page_tabwe->pt_bo->tbo;
	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn;

	memset(cmd, 0, sizeof(*cmd));
	cmd->headew.id = SVGA_3D_CMD_SET_OTABWE_BASE;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.type = type;
	cmd->body.baseAddwess = 0;
	cmd->body.sizeInBytes = 0;
	cmd->body.vawidSizeInBytes = 0;
	cmd->body.ptDepth = SVGA3D_MOBFMT_INVAWID;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	if (bo) {
		int wet;

		wet = ttm_bo_wesewve(bo, fawse, twue, NUWW);
		BUG_ON(wet != 0);

		vmw_bo_fence_singwe(bo, NUWW);
		ttm_bo_unwesewve(bo);
	}

	vmw_mob_destwoy(otabwe->page_tabwe);
	otabwe->page_tabwe = NUWW;
}


static int vmw_otabwe_batch_setup(stwuct vmw_pwivate *dev_pwiv,
				  stwuct vmw_otabwe_batch *batch)
{
	unsigned wong offset;
	unsigned wong bo_size;
	stwuct vmw_otabwe *otabwes = batch->otabwes;
	SVGAOTabweType i;
	int wet;

	bo_size = 0;
	fow (i = 0; i < batch->num_otabwes; ++i) {
		if (!otabwes[i].enabwed)
			continue;

		otabwes[i].size = PFN_AWIGN(otabwes[i].size);
		bo_size += otabwes[i].size;
	}

	wet = vmw_bo_cweate_and_popuwate(dev_pwiv, bo_size,
					 VMW_BO_DOMAIN_WAITABWE_SYS,
					 &batch->otabwe_bo);
	if (unwikewy(wet != 0))
		wetuwn wet;

	offset = 0;
	fow (i = 0; i < batch->num_otabwes; ++i) {
		if (!batch->otabwes[i].enabwed)
			continue;

		wet = vmw_setup_otabwe_base(dev_pwiv, i,
					    &batch->otabwe_bo->tbo,
					    offset,
					    &otabwes[i]);
		if (unwikewy(wet != 0))
			goto out_no_setup;
		offset += otabwes[i].size;
	}

	wetuwn 0;

out_no_setup:
	fow (i = 0; i < batch->num_otabwes; ++i) {
		if (batch->otabwes[i].enabwed)
			vmw_takedown_otabwe_base(dev_pwiv, i,
						 &batch->otabwes[i]);
	}

	vmw_bo_unpin_unwocked(&batch->otabwe_bo->tbo);
	ttm_bo_put(&batch->otabwe_bo->tbo);
	batch->otabwe_bo = NUWW;
	wetuwn wet;
}

/*
 * vmw_otabwes_setup - Set up guest backed memowy object tabwes
 *
 * @dev_pwiv:       Pointew to a device pwivate stwuctuwe
 *
 * Takes cawe of the device guest backed suwface
 * initiawization, by setting up the guest backed memowy object tabwes.
 * Wetuwns 0 on success and vawious ewwow codes on faiwuwe. A successfuw wetuwn
 * means the object tabwes can be taken down using the vmw_otabwes_takedown
 * function.
 */
int vmw_otabwes_setup(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_otabwe **otabwes = &dev_pwiv->otabwe_batch.otabwes;
	int wet;

	if (has_sm4_context(dev_pwiv)) {
		*otabwes = kmemdup(dx_tabwes, sizeof(dx_tabwes), GFP_KEWNEW);
		if (!(*otabwes))
			wetuwn -ENOMEM;

		dev_pwiv->otabwe_batch.num_otabwes = AWWAY_SIZE(dx_tabwes);
	} ewse {
		*otabwes = kmemdup(pwe_dx_tabwes, sizeof(pwe_dx_tabwes),
				   GFP_KEWNEW);
		if (!(*otabwes))
			wetuwn -ENOMEM;

		dev_pwiv->otabwe_batch.num_otabwes = AWWAY_SIZE(pwe_dx_tabwes);
	}

	wet = vmw_otabwe_batch_setup(dev_pwiv, &dev_pwiv->otabwe_batch);
	if (unwikewy(wet != 0))
		goto out_setup;

	wetuwn 0;

out_setup:
	kfwee(*otabwes);
	wetuwn wet;
}

static void vmw_otabwe_batch_takedown(stwuct vmw_pwivate *dev_pwiv,
			       stwuct vmw_otabwe_batch *batch)
{
	SVGAOTabweType i;
	stwuct ttm_buffew_object *bo = &batch->otabwe_bo->tbo;
	int wet;

	fow (i = 0; i < batch->num_otabwes; ++i)
		if (batch->otabwes[i].enabwed)
			vmw_takedown_otabwe_base(dev_pwiv, i,
						 &batch->otabwes[i]);

	wet = ttm_bo_wesewve(bo, fawse, twue, NUWW);
	BUG_ON(wet != 0);

	vmw_bo_fence_singwe(bo, NUWW);
	ttm_bo_unpin(bo);
	ttm_bo_unwesewve(bo);

	vmw_bo_unwefewence(&batch->otabwe_bo);
}

/*
 * vmw_otabwes_takedown - Take down guest backed memowy object tabwes
 *
 * @dev_pwiv:       Pointew to a device pwivate stwuctuwe
 *
 * Take down the Guest Memowy Object tabwes.
 */
void vmw_otabwes_takedown(stwuct vmw_pwivate *dev_pwiv)
{
	vmw_otabwe_batch_takedown(dev_pwiv, &dev_pwiv->otabwe_batch);
	kfwee(dev_pwiv->otabwe_batch.otabwes);
}

/*
 * vmw_mob_cawcuwate_pt_pages - Cawcuwate the numbew of page tabwe pages
 * needed fow a guest backed memowy object.
 *
 * @data_pages:  Numbew of data pages in the memowy object buffew.
 */
static unsigned wong vmw_mob_cawcuwate_pt_pages(unsigned wong data_pages)
{
	unsigned wong data_size = data_pages * PAGE_SIZE;
	unsigned wong tot_size = 0;

	whiwe (wikewy(data_size > PAGE_SIZE)) {
		data_size = DIV_WOUND_UP(data_size, PAGE_SIZE);
		data_size *= VMW_PPN_SIZE;
		tot_size += PFN_AWIGN(data_size);
	}

	wetuwn tot_size >> PAGE_SHIFT;
}

/*
 * vmw_mob_cweate - Cweate a mob, but don't popuwate it.
 *
 * @data_pages:  Numbew of data pages of the undewwying buffew object.
 */
stwuct vmw_mob *vmw_mob_cweate(unsigned wong data_pages)
{
	stwuct vmw_mob *mob = kzawwoc(sizeof(*mob), GFP_KEWNEW);

	if (unwikewy(!mob))
		wetuwn NUWW;

	mob->num_pages = vmw_mob_cawcuwate_pt_pages(data_pages);

	wetuwn mob;
}

/*
 * vmw_mob_pt_popuwate - Popuwate the mob pagetabwe
 *
 * @mob:         Pointew to the mob the pagetabwe of which we want to
 *               popuwate.
 *
 * This function awwocates memowy to be used fow the pagetabwe.
 * Wetuwns ENOMEM if memowy wesouwces awen't sufficient and may
 * cause TTM buffew objects to be swapped out.
 */
static int vmw_mob_pt_popuwate(stwuct vmw_pwivate *dev_pwiv,
			       stwuct vmw_mob *mob)
{
	BUG_ON(mob->pt_bo != NUWW);

	wetuwn vmw_bo_cweate_and_popuwate(dev_pwiv, mob->num_pages * PAGE_SIZE,
					  VMW_BO_DOMAIN_WAITABWE_SYS,
					  &mob->pt_bo);
}

/**
 * vmw_mob_assign_ppn - Assign a vawue to a page tabwe entwy
 *
 * @addw: Pointew to pointew to page tabwe entwy.
 * @vaw: The page tabwe entwy
 *
 * Assigns a vawue to a page tabwe entwy pointed to by *@addw and incwements
 * *@addw accowding to the page tabwe entwy size.
 */
#if (VMW_PPN_SIZE == 8)
static void vmw_mob_assign_ppn(u32 **addw, dma_addw_t vaw)
{
	*((u64 *) *addw) = vaw >> PAGE_SHIFT;
	*addw += 2;
}
#ewse
static void vmw_mob_assign_ppn(u32 **addw, dma_addw_t vaw)
{
	*(*addw)++ = vaw >> PAGE_SHIFT;
}
#endif

/*
 * vmw_mob_buiwd_pt - Buiwd a pagetabwe
 *
 * @data_addw:      Awway of DMA addwesses to the undewwying buffew
 *                  object's data pages.
 * @num_data_pages: Numbew of buffew object data pages.
 * @pt_pages:       Awway of page pointews to the page tabwe pages.
 *
 * Wetuwns the numbew of page tabwe pages actuawwy used.
 * Uses atomic kmaps of highmem pages to avoid TWB thwashing.
 */
static unsigned wong vmw_mob_buiwd_pt(stwuct vmw_pitew *data_itew,
				      unsigned wong num_data_pages,
				      stwuct vmw_pitew *pt_itew)
{
	unsigned wong pt_size = num_data_pages * VMW_PPN_SIZE;
	unsigned wong num_pt_pages = DIV_WOUND_UP(pt_size, PAGE_SIZE);
	unsigned wong pt_page;
	u32 *addw, *save_addw;
	unsigned wong i;
	stwuct page *page;

	fow (pt_page = 0; pt_page < num_pt_pages; ++pt_page) {
		page = vmw_pitew_page(pt_itew);

		save_addw = addw = kmap_atomic(page);

		fow (i = 0; i < PAGE_SIZE / VMW_PPN_SIZE; ++i) {
			vmw_mob_assign_ppn(&addw,
					   vmw_pitew_dma_addw(data_itew));
			if (unwikewy(--num_data_pages == 0))
				bweak;
			WAWN_ON(!vmw_pitew_next(data_itew));
		}
		kunmap_atomic(save_addw);
		vmw_pitew_next(pt_itew);
	}

	wetuwn num_pt_pages;
}

/*
 * vmw_mob_buiwd_pt - Set up a muwtiwevew mob pagetabwe
 *
 * @mob:            Pointew to a mob whose page tabwe needs setting up.
 * @data_addw       Awway of DMA addwesses to the buffew object's data
 *                  pages.
 * @num_data_pages: Numbew of buffew object data pages.
 *
 * Uses taiw wecuwsion to set up a muwtiwevew mob page tabwe.
 */
static void vmw_mob_pt_setup(stwuct vmw_mob *mob,
			     stwuct vmw_pitew data_itew,
			     unsigned wong num_data_pages)
{
	unsigned wong num_pt_pages = 0;
	stwuct ttm_buffew_object *bo = &mob->pt_bo->tbo;
	stwuct vmw_pitew save_pt_itew = {0};
	stwuct vmw_pitew pt_itew;
	const stwuct vmw_sg_tabwe *vsgt;
	int wet;

	BUG_ON(num_data_pages == 0);

	wet = ttm_bo_wesewve(bo, fawse, twue, NUWW);
	BUG_ON(wet != 0);

	vsgt = vmw_bo_sg_tabwe(bo);
	vmw_pitew_stawt(&pt_itew, vsgt, 0);
	BUG_ON(!vmw_pitew_next(&pt_itew));
	mob->pt_wevew = 0;
	whiwe (wikewy(num_data_pages > 1)) {
		++mob->pt_wevew;
		BUG_ON(mob->pt_wevew > 2);
		save_pt_itew = pt_itew;
		num_pt_pages = vmw_mob_buiwd_pt(&data_itew, num_data_pages,
						&pt_itew);
		data_itew = save_pt_itew;
		num_data_pages = num_pt_pages;
	}

	mob->pt_woot_page = vmw_pitew_dma_addw(&save_pt_itew);
	ttm_bo_unwesewve(bo);
}

/*
 * vmw_mob_destwoy - Destwoy a mob, unpopuwating fiwst if necessawy.
 *
 * @mob:            Pointew to a mob to destwoy.
 */
void vmw_mob_destwoy(stwuct vmw_mob *mob)
{
	if (mob->pt_bo) {
		vmw_bo_unpin_unwocked(&mob->pt_bo->tbo);
		vmw_bo_unwefewence(&mob->pt_bo);
	}
	kfwee(mob);
}

/*
 * vmw_mob_unbind - Hide a mob fwom the device.
 *
 * @dev_pwiv:       Pointew to a device pwivate.
 * @mob_id:         Device id of the mob to unbind.
 */
void vmw_mob_unbind(stwuct vmw_pwivate *dev_pwiv,
		    stwuct vmw_mob *mob)
{
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDestwoyGBMob body;
	} *cmd;
	int wet;
	stwuct ttm_buffew_object *bo = &mob->pt_bo->tbo;

	if (bo) {
		wet = ttm_bo_wesewve(bo, fawse, twue, NUWW);
		/*
		 * Noone ewse shouwd be using this buffew.
		 */
		BUG_ON(wet != 0);
	}

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (cmd) {
		cmd->headew.id = SVGA_3D_CMD_DESTWOY_GB_MOB;
		cmd->headew.size = sizeof(cmd->body);
		cmd->body.mobid = mob->id;
		vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	}

	if (bo) {
		vmw_bo_fence_singwe(bo, NUWW);
		ttm_bo_unwesewve(bo);
	}
	vmw_fifo_wesouwce_dec(dev_pwiv);
}

/*
 * vmw_mob_bind - Make a mob visibwe to the device aftew fiwst
 *                popuwating it if necessawy.
 *
 * @dev_pwiv:       Pointew to a device pwivate.
 * @mob:            Pointew to the mob we'we making visibwe.
 * @data_addw:      Awway of DMA addwesses to the data pages of the undewwying
 *                  buffew object.
 * @num_data_pages: Numbew of data pages of the undewwying buffew
 *                  object.
 * @mob_id:         Device id of the mob to bind
 *
 * This function is intended to be intewfaced with the ttm_tt backend
 * code.
 */
int vmw_mob_bind(stwuct vmw_pwivate *dev_pwiv,
		 stwuct vmw_mob *mob,
		 const stwuct vmw_sg_tabwe *vsgt,
		 unsigned wong num_data_pages,
		 int32_t mob_id)
{
	int wet;
	boow pt_set_up = fawse;
	stwuct vmw_pitew data_itew;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDefineGBMob64 body;
	} *cmd;

	mob->id = mob_id;
	vmw_pitew_stawt(&data_itew, vsgt, 0);
	if (unwikewy(!vmw_pitew_next(&data_itew)))
		wetuwn 0;

	if (wikewy(num_data_pages == 1)) {
		mob->pt_wevew = VMW_MOBFMT_PTDEPTH_0;
		mob->pt_woot_page = vmw_pitew_dma_addw(&data_itew);
	} ewse if (unwikewy(mob->pt_bo == NUWW)) {
		wet = vmw_mob_pt_popuwate(dev_pwiv, mob);
		if (unwikewy(wet != 0))
			wetuwn wet;

		vmw_mob_pt_setup(mob, data_itew, num_data_pages);
		pt_set_up = twue;
		mob->pt_wevew += VMW_MOBFMT_PTDEPTH_1 - SVGA3D_MOBFMT_PT_1;
	}

	vmw_fifo_wesouwce_inc(dev_pwiv);

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		goto out_no_cmd_space;

	cmd->headew.id = SVGA_3D_CMD_DEFINE_GB_MOB64;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.mobid = mob_id;
	cmd->body.ptDepth = mob->pt_wevew;
	cmd->body.base = mob->pt_woot_page >> PAGE_SHIFT;
	cmd->body.sizeInBytes = num_data_pages * PAGE_SIZE;

	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;

out_no_cmd_space:
	vmw_fifo_wesouwce_dec(dev_pwiv);
	if (pt_set_up) {
		vmw_bo_unpin_unwocked(&mob->pt_bo->tbo);
		vmw_bo_unwefewence(&mob->pt_bo);
	}

	wetuwn -ENOMEM;
}
