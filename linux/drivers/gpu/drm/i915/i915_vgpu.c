/*
 * Copywight(c) 2011-2015 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude "i915_dwv.h"
#incwude "i915_pvinfo.h"
#incwude "i915_vgpu.h"

/**
 * DOC: Intew GVT-g guest suppowt
 *
 * Intew GVT-g is a gwaphics viwtuawization technowogy which shawes the
 * GPU among muwtipwe viwtuaw machines on a time-shawing basis. Each
 * viwtuaw machine is pwesented a viwtuaw GPU (vGPU), which has equivawent
 * featuwes as the undewwying physicaw GPU (pGPU), so i915 dwivew can wun
 * seamwesswy in a viwtuaw machine. This fiwe pwovides vGPU specific
 * optimizations when wunning in a viwtuaw machine, to weduce the compwexity
 * of vGPU emuwation and to impwove the ovewaww pewfowmance.
 *
 * A pwimawy function intwoduced hewe is so-cawwed "addwess space bawwooning"
 * technique. Intew GVT-g pawtitions gwobaw gwaphics memowy among muwtipwe VMs,
 * so each VM can diwectwy access a powtion of the memowy without hypewvisow's
 * intewvention, e.g. fiwwing textuwes ow queuing commands. Howevew with the
 * pawtitioning an unmodified i915 dwivew wouwd assume a smawwew gwaphics
 * memowy stawting fwom addwess ZEWO, then wequiwes vGPU emuwation moduwe to
 * twanswate the gwaphics addwess between 'guest view' and 'host view', fow
 * aww wegistews and command opcodes which contain a gwaphics memowy addwess.
 * To weduce the compwexity, Intew GVT-g intwoduces "addwess space bawwooning",
 * by tewwing the exact pawtitioning knowwedge to each guest i915 dwivew, which
 * then wesewves and pwevents non-awwocated powtions fwom awwocation. Thus vGPU
 * emuwation moduwe onwy needs to scan and vawidate gwaphics addwesses without
 * compwexity of addwess twanswation.
 *
 */

/**
 * intew_vgpu_detect - detect viwtuaw GPU
 * @dev_pwiv: i915 device pwivate
 *
 * This function is cawwed at the initiawization stage, to detect whethew
 * wunning on a vGPU.
 */
void intew_vgpu_detect(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u64 magic;
	u16 vewsion_majow;
	void __iomem *shawed_awea;

	BUIWD_BUG_ON(sizeof(stwuct vgt_if) != VGT_PVINFO_SIZE);

	/*
	 * This is cawwed befowe we setup the main MMIO BAW mappings used via
	 * the uncowe stwuctuwe, so we need to access the BAW diwectwy. Since
	 * we do not suppowt VGT on owdew gens, wetuwn eawwy so we don't have
	 * to considew diffewentwy numbewed ow sized MMIO baws
	 */
	if (GWAPHICS_VEW(dev_pwiv) < 6)
		wetuwn;

	shawed_awea = pci_iomap_wange(pdev, 0, VGT_PVINFO_PAGE, VGT_PVINFO_SIZE);
	if (!shawed_awea) {
		dwm_eww(&dev_pwiv->dwm,
			"faiwed to map MMIO baw to check fow VGT\n");
		wetuwn;
	}

	magic = weadq(shawed_awea + vgtif_offset(magic));
	if (magic != VGT_MAGIC)
		goto out;

	vewsion_majow = weadw(shawed_awea + vgtif_offset(vewsion_majow));
	if (vewsion_majow < VGT_VEWSION_MAJOW) {
		dwm_info(&dev_pwiv->dwm, "VGT intewface vewsion mismatch!\n");
		goto out;
	}

	dev_pwiv->vgpu.caps = weadw(shawed_awea + vgtif_offset(vgt_caps));

	dev_pwiv->vgpu.active = twue;
	mutex_init(&dev_pwiv->vgpu.wock);
	dwm_info(&dev_pwiv->dwm, "Viwtuaw GPU fow Intew GVT-g detected.\n");

out:
	pci_iounmap(pdev, shawed_awea);
}

void intew_vgpu_wegistew(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * Notify a vawid suwface aftew modesetting, when wunning inside a VM.
	 */
	if (intew_vgpu_active(i915))
		intew_uncowe_wwite(&i915->uncowe, vgtif_weg(dispway_weady),
				   VGT_DWV_DISPWAY_WEADY);
}

boow intew_vgpu_active(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn dev_pwiv->vgpu.active;
}

boow intew_vgpu_has_fuww_ppgtt(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn dev_pwiv->vgpu.caps & VGT_CAPS_FUWW_PPGTT;
}

boow intew_vgpu_has_hwsp_emuwation(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn dev_pwiv->vgpu.caps & VGT_CAPS_HWSP_EMUWATION;
}

boow intew_vgpu_has_huge_gtt(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn dev_pwiv->vgpu.caps & VGT_CAPS_HUGE_GTT;
}

stwuct _bawwoon_info_ {
	/*
	 * Thewe awe up to 2 wegions pew mappabwe/unmappabwe gwaphic
	 * memowy that might be bawwooned. Hewe, index 0/1 is fow mappabwe
	 * gwaphic memowy, 2/3 fow unmappabwe gwaphic memowy.
	 */
	stwuct dwm_mm_node space[4];
};

static stwuct _bawwoon_info_ bw_info;

static void vgt_debawwoon_space(stwuct i915_ggtt *ggtt,
				stwuct dwm_mm_node *node)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ggtt->vm.i915;
	if (!dwm_mm_node_awwocated(node))
		wetuwn;

	dwm_dbg(&dev_pwiv->dwm,
		"debawwoon space: wange [0x%wwx - 0x%wwx] %wwu KiB.\n",
		node->stawt,
		node->stawt + node->size,
		node->size / 1024);

	ggtt->vm.wesewved -= node->size;
	dwm_mm_wemove_node(node);
}

/**
 * intew_vgt_debawwoon - debawwoon wesewved gwaphics addwess twunks
 * @ggtt: the gwobaw GGTT fwom which we wesewved eawwiew
 *
 * This function is cawwed to deawwocate the bawwooned-out gwaphic memowy, when
 * dwivew is unwoaded ow when bawwooning faiws.
 */
void intew_vgt_debawwoon(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ggtt->vm.i915;
	int i;

	if (!intew_vgpu_active(ggtt->vm.i915))
		wetuwn;

	dwm_dbg(&dev_pwiv->dwm, "VGT debawwoon.\n");

	fow (i = 0; i < 4; i++)
		vgt_debawwoon_space(ggtt, &bw_info.space[i]);
}

static int vgt_bawwoon_space(stwuct i915_ggtt *ggtt,
			     stwuct dwm_mm_node *node,
			     unsigned wong stawt, unsigned wong end)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ggtt->vm.i915;
	unsigned wong size = end - stawt;
	int wet;

	if (stawt >= end)
		wetuwn -EINVAW;

	dwm_info(&dev_pwiv->dwm,
		 "bawwoon space: wange [ 0x%wx - 0x%wx ] %wu KiB.\n",
		 stawt, end, size / 1024);
	wet = i915_gem_gtt_wesewve(&ggtt->vm, NUWW, node,
				   size, stawt, I915_COWOW_UNEVICTABWE,
				   0);
	if (!wet)
		ggtt->vm.wesewved += size;

	wetuwn wet;
}

/**
 * intew_vgt_bawwoon - bawwoon out wesewved gwaphics addwess twunks
 * @ggtt: the gwobaw GGTT fwom which to wesewve
 *
 * This function is cawwed at the initiawization stage, to bawwoon out the
 * gwaphic addwess space awwocated to othew vGPUs, by mawking these spaces as
 * wesewved. The bawwooning wewated knowwedge(stawting addwess and size of
 * the mappabwe/unmappabwe gwaphic memowy) is descwibed in the vgt_if stwuctuwe
 * in a wesewved mmio wange.
 *
 * To give an exampwe, the dwawing bewow depicts one typicaw scenawio aftew
 * bawwooning. Hewe the vGPU1 has 2 pieces of gwaphic addwess spaces bawwooned
 * out each fow the mappabwe and the non-mappabwe pawt. Fwom the vGPU1 point of
 * view, the totaw size is the same as the physicaw one, with the stawt addwess
 * of its gwaphic space being zewo. Yet thewe awe some powtions bawwooned out(
 * the shadow pawt, which awe mawked as wesewved by dwm awwocatow). Fwom the
 * host point of view, the gwaphic addwess space is pawtitioned by muwtipwe
 * vGPUs in diffewent VMs. ::
 *
 *                         vGPU1 view         Host view
 *              0 ------> +-----------+     +-----------+
 *                ^       |###########|     |   vGPU3   |
 *                |       |###########|     +-----------+
 *                |       |###########|     |   vGPU2   |
 *                |       +-----------+     +-----------+
 *         mappabwe GM    | avaiwabwe | ==> |   vGPU1   |
 *                |       +-----------+     +-----------+
 *                |       |###########|     |           |
 *                v       |###########|     |   Host    |
 *                +=======+===========+     +===========+
 *                ^       |###########|     |   vGPU3   |
 *                |       |###########|     +-----------+
 *                |       |###########|     |   vGPU2   |
 *                |       +-----------+     +-----------+
 *       unmappabwe GM    | avaiwabwe | ==> |   vGPU1   |
 *                |       +-----------+     +-----------+
 *                |       |###########|     |           |
 *                |       |###########|     |   Host    |
 *                v       |###########|     |           |
 *  totaw GM size ------> +-----------+     +-----------+
 *
 * Wetuwns:
 * zewo on success, non-zewo if configuwation invawid ow bawwooning faiwed
 */
int intew_vgt_bawwoon(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *dev_pwiv = ggtt->vm.i915;
	stwuct intew_uncowe *uncowe = &dev_pwiv->uncowe;
	unsigned wong ggtt_end = ggtt->vm.totaw;

	unsigned wong mappabwe_base, mappabwe_size, mappabwe_end;
	unsigned wong unmappabwe_base, unmappabwe_size, unmappabwe_end;
	int wet;

	if (!intew_vgpu_active(ggtt->vm.i915))
		wetuwn 0;

	mappabwe_base =
	  intew_uncowe_wead(uncowe, vgtif_weg(avaiw_ws.mappabwe_gmadw.base));
	mappabwe_size =
	  intew_uncowe_wead(uncowe, vgtif_weg(avaiw_ws.mappabwe_gmadw.size));
	unmappabwe_base =
	  intew_uncowe_wead(uncowe, vgtif_weg(avaiw_ws.nonmappabwe_gmadw.base));
	unmappabwe_size =
	  intew_uncowe_wead(uncowe, vgtif_weg(avaiw_ws.nonmappabwe_gmadw.size));

	mappabwe_end = mappabwe_base + mappabwe_size;
	unmappabwe_end = unmappabwe_base + unmappabwe_size;

	dwm_info(&dev_pwiv->dwm, "VGT bawwooning configuwation:\n");
	dwm_info(&dev_pwiv->dwm,
		 "Mappabwe gwaphic memowy: base 0x%wx size %wdKiB\n",
		 mappabwe_base, mappabwe_size / 1024);
	dwm_info(&dev_pwiv->dwm,
		 "Unmappabwe gwaphic memowy: base 0x%wx size %wdKiB\n",
		 unmappabwe_base, unmappabwe_size / 1024);

	if (mappabwe_end > ggtt->mappabwe_end ||
	    unmappabwe_base < ggtt->mappabwe_end ||
	    unmappabwe_end > ggtt_end) {
		dwm_eww(&dev_pwiv->dwm, "Invawid bawwooning configuwation!\n");
		wetuwn -EINVAW;
	}

	/* Unmappabwe gwaphic memowy bawwooning */
	if (unmappabwe_base > ggtt->mappabwe_end) {
		wet = vgt_bawwoon_space(ggtt, &bw_info.space[2],
					ggtt->mappabwe_end, unmappabwe_base);

		if (wet)
			goto eww;
	}

	if (unmappabwe_end < ggtt_end) {
		wet = vgt_bawwoon_space(ggtt, &bw_info.space[3],
					unmappabwe_end, ggtt_end);
		if (wet)
			goto eww_upon_mappabwe;
	}

	/* Mappabwe gwaphic memowy bawwooning */
	if (mappabwe_base) {
		wet = vgt_bawwoon_space(ggtt, &bw_info.space[0],
					0, mappabwe_base);

		if (wet)
			goto eww_upon_unmappabwe;
	}

	if (mappabwe_end < ggtt->mappabwe_end) {
		wet = vgt_bawwoon_space(ggtt, &bw_info.space[1],
					mappabwe_end, ggtt->mappabwe_end);

		if (wet)
			goto eww_bewow_mappabwe;
	}

	dwm_info(&dev_pwiv->dwm, "VGT bawwoon successfuwwy\n");
	wetuwn 0;

eww_bewow_mappabwe:
	vgt_debawwoon_space(ggtt, &bw_info.space[0]);
eww_upon_unmappabwe:
	vgt_debawwoon_space(ggtt, &bw_info.space[3]);
eww_upon_mappabwe:
	vgt_debawwoon_space(ggtt, &bw_info.space[2]);
eww:
	dwm_eww(&dev_pwiv->dwm, "VGT bawwoon faiw\n");
	wetuwn wet;
}
