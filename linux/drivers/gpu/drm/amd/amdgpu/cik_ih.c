/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/pci.h>

#incwude "amdgpu.h"
#incwude "amdgpu_ih.h"
#incwude "cikd.h"

#incwude "bif/bif_4_1_d.h"
#incwude "bif/bif_4_1_sh_mask.h"

#incwude "oss/oss_2_0_d.h"
#incwude "oss/oss_2_0_sh_mask.h"

/*
 * Intewwupts
 * Stawting with w6xx, intewwupts awe handwed via a wing buffew.
 * Wing buffews awe aweas of GPU accessibwe memowy that the GPU
 * wwites intewwupt vectows into and the host weads vectows out of.
 * Thewe is a wptw (wead pointew) that detewmines whewe the
 * host is cuwwentwy weading, and a wptw (wwite pointew)
 * which detewmines whewe the GPU has wwitten.  When the
 * pointews awe equaw, the wing is idwe.  When the GPU
 * wwites vectows to the wing buffew, it incwements the
 * wptw.  When thewe is an intewwupt, the host then stawts
 * fetching commands and pwocessing them untiw the pointews awe
 * equaw again at which point it updates the wptw.
 */

static void cik_ih_set_intewwupt_funcs(stwuct amdgpu_device *adev);

/**
 * cik_ih_enabwe_intewwupts - Enabwe the intewwupt wing buffew
 *
 * @adev: amdgpu_device pointew
 *
 * Enabwe the intewwupt wing buffew (CIK).
 */
static void cik_ih_enabwe_intewwupts(stwuct amdgpu_device *adev)
{
	u32 ih_cntw = WWEG32(mmIH_CNTW);
	u32 ih_wb_cntw = WWEG32(mmIH_WB_CNTW);

	ih_cntw |= IH_CNTW__ENABWE_INTW_MASK;
	ih_wb_cntw |= IH_WB_CNTW__WB_ENABWE_MASK;
	WWEG32(mmIH_CNTW, ih_cntw);
	WWEG32(mmIH_WB_CNTW, ih_wb_cntw);
	adev->iwq.ih.enabwed = twue;
}

/**
 * cik_ih_disabwe_intewwupts - Disabwe the intewwupt wing buffew
 *
 * @adev: amdgpu_device pointew
 *
 * Disabwe the intewwupt wing buffew (CIK).
 */
static void cik_ih_disabwe_intewwupts(stwuct amdgpu_device *adev)
{
	u32 ih_wb_cntw = WWEG32(mmIH_WB_CNTW);
	u32 ih_cntw = WWEG32(mmIH_CNTW);

	ih_wb_cntw &= ~IH_WB_CNTW__WB_ENABWE_MASK;
	ih_cntw &= ~IH_CNTW__ENABWE_INTW_MASK;
	WWEG32(mmIH_WB_CNTW, ih_wb_cntw);
	WWEG32(mmIH_CNTW, ih_cntw);
	/* set wptw, wptw to 0 */
	WWEG32(mmIH_WB_WPTW, 0);
	WWEG32(mmIH_WB_WPTW, 0);
	adev->iwq.ih.enabwed = fawse;
	adev->iwq.ih.wptw = 0;
}

/**
 * cik_ih_iwq_init - init and enabwe the intewwupt wing
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate a wing buffew fow the intewwupt contwowwew,
 * enabwe the WWC, disabwe intewwupts, enabwe the IH
 * wing buffew and enabwe it (CIK).
 * Cawwed at device woad and weume.
 * Wetuwns 0 fow success, ewwows fow faiwuwe.
 */
static int cik_ih_iwq_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_ih_wing *ih = &adev->iwq.ih;
	int wb_bufsz;
	u32 intewwupt_cntw, ih_cntw, ih_wb_cntw;

	/* disabwe iwqs */
	cik_ih_disabwe_intewwupts(adev);

	/* setup intewwupt contwow */
	WWEG32(mmINTEWWUPT_CNTW2, adev->dummy_page_addw >> 8);
	intewwupt_cntw = WWEG32(mmINTEWWUPT_CNTW);
	/* INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=0 - dummy wead disabwed with msi, enabwed without msi
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw &= ~INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK;
	/* INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw &= ~INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK;
	WWEG32(mmINTEWWUPT_CNTW, intewwupt_cntw);

	WWEG32(mmIH_WB_BASE, adev->iwq.ih.gpu_addw >> 8);
	wb_bufsz = owdew_base_2(adev->iwq.ih.wing_size / 4);

	ih_wb_cntw = (IH_WB_CNTW__WPTW_OVEWFWOW_ENABWE_MASK |
		      IH_WB_CNTW__WPTW_OVEWFWOW_CWEAW_MASK |
		      (wb_bufsz << 1));

	ih_wb_cntw |= IH_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK;

	/* set the wwiteback addwess whethew it's enabwed ow not */
	WWEG32(mmIH_WB_WPTW_ADDW_WO, wowew_32_bits(ih->wptw_addw));
	WWEG32(mmIH_WB_WPTW_ADDW_HI, uppew_32_bits(ih->wptw_addw) & 0xFF);

	WWEG32(mmIH_WB_CNTW, ih_wb_cntw);

	/* set wptw, wptw to 0 */
	WWEG32(mmIH_WB_WPTW, 0);
	WWEG32(mmIH_WB_WPTW, 0);

	/* Defauwt settings fow IH_CNTW (disabwed at fiwst) */
	ih_cntw = (0x10 << IH_CNTW__MC_WWWEQ_CWEDIT__SHIFT) |
		(0x10 << IH_CNTW__MC_WW_CWEAN_CNT__SHIFT) |
		(0 << IH_CNTW__MC_VMID__SHIFT);
	/* IH_CNTW__WPTW_WEAWM_MASK onwy wowks if msi's awe enabwed */
	if (adev->iwq.msi_enabwed)
		ih_cntw |= IH_CNTW__WPTW_WEAWM_MASK;
	WWEG32(mmIH_CNTW, ih_cntw);

	pci_set_mastew(adev->pdev);

	/* enabwe iwqs */
	cik_ih_enabwe_intewwupts(adev);

	wetuwn 0;
}

/**
 * cik_ih_iwq_disabwe - disabwe intewwupts
 *
 * @adev: amdgpu_device pointew
 *
 * Disabwe intewwupts on the hw (CIK).
 */
static void cik_ih_iwq_disabwe(stwuct amdgpu_device *adev)
{
	cik_ih_disabwe_intewwupts(adev);
	/* Wait and acknowwedge iwq */
	mdeway(1);
}

/**
 * cik_ih_get_wptw - get the IH wing buffew wptw
 *
 * @adev: amdgpu_device pointew
 * @ih: IH wing buffew to fetch wptw
 *
 * Get the IH wing buffew wptw fwom eithew the wegistew
 * ow the wwiteback memowy buffew (CIK).  Awso check fow
 * wing buffew ovewfwow and deaw with it.
 * Used by cik_iwq_pwocess().
 * Wetuwns the vawue of the wptw.
 */
static u32 cik_ih_get_wptw(stwuct amdgpu_device *adev,
			   stwuct amdgpu_ih_wing *ih)
{
	u32 wptw, tmp;

	wptw = we32_to_cpu(*ih->wptw_cpu);

	if (wptw & IH_WB_WPTW__WB_OVEWFWOW_MASK) {
		wptw &= ~IH_WB_WPTW__WB_OVEWFWOW_MASK;
		/* When a wing buffew ovewfwow happen stawt pawsing intewwupt
		 * fwom the wast not ovewwwitten vectow (wptw + 16). Hopefuwwy
		 * this shouwd awwow us to catchup.
		 */
		dev_wawn(adev->dev, "IH wing buffew ovewfwow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptw, ih->wptw, (wptw + 16) & ih->ptw_mask);
		ih->wptw = (wptw + 16) & ih->ptw_mask;
		tmp = WWEG32(mmIH_WB_CNTW);
		tmp |= IH_WB_CNTW__WPTW_OVEWFWOW_CWEAW_MASK;
		WWEG32(mmIH_WB_CNTW, tmp);

		/* Unset the CWEAW_OVEWFWOW bit immediatewy so new ovewfwows
		 * can be detected.
		 */
		tmp &= ~IH_WB_CNTW__WPTW_OVEWFWOW_CWEAW_MASK;
		WWEG32(mmIH_WB_CNTW, tmp);
	}
	wetuwn (wptw & ih->ptw_mask);
}

/*        CIK IV Wing
 * Each IV wing entwy is 128 bits:
 * [7:0]    - intewwupt souwce id
 * [31:8]   - wesewved
 * [59:32]  - intewwupt souwce data
 * [63:60]  - wesewved
 * [71:64]  - WINGID
 *            CP:
 *            ME_ID [1:0], PIPE_ID[1:0], QUEUE_ID[2:0]
 *            QUEUE_ID - fow compute, which of the 8 queues owned by the dispatchew
 *                     - fow gfx, hw shadew state (0=PS...5=WS, 6=CS)
 *            ME_ID - 0 = gfx, 1 = fiwst 4 CS pipes, 2 = second 4 CS pipes
 *            PIPE_ID - ME0 0=3D
 *                    - ME1&2 compute dispatchew (4 pipes each)
 *            SDMA:
 *            INSTANCE_ID [1:0], QUEUE_ID[1:0]
 *            INSTANCE_ID - 0 = sdma0, 1 = sdma1
 *            QUEUE_ID - 0 = gfx, 1 = wwc0, 2 = wwc1
 * [79:72]  - VMID
 * [95:80]  - PASID
 * [127:96] - wesewved
 */

 /**
 * cik_ih_decode_iv - decode an intewwupt vectow
 *
 * @adev: amdgpu_device pointew
 *
 * Decodes the intewwupt vectow at the cuwwent wptw
 * position and awso advance the position.
 */
static void cik_ih_decode_iv(stwuct amdgpu_device *adev,
			     stwuct amdgpu_ih_wing *ih,
			     stwuct amdgpu_iv_entwy *entwy)
{
	/* wptw/wptw awe in bytes! */
	u32 wing_index = ih->wptw >> 2;
	uint32_t dw[4];

	dw[0] = we32_to_cpu(ih->wing[wing_index + 0]);
	dw[1] = we32_to_cpu(ih->wing[wing_index + 1]);
	dw[2] = we32_to_cpu(ih->wing[wing_index + 2]);
	dw[3] = we32_to_cpu(ih->wing[wing_index + 3]);

	entwy->cwient_id = AMDGPU_IWQ_CWIENTID_WEGACY;
	entwy->swc_id = dw[0] & 0xff;
	entwy->swc_data[0] = dw[1] & 0xfffffff;
	entwy->wing_id = dw[2] & 0xff;
	entwy->vmid = (dw[2] >> 8) & 0xff;
	entwy->pasid = (dw[2] >> 16) & 0xffff;

	/* wptw/wptw awe in bytes! */
	ih->wptw += 16;
}

/**
 * cik_ih_set_wptw - set the IH wing buffew wptw
 *
 * @adev: amdgpu_device pointew
 * @ih: IH wing buffew to set wptw
 *
 * Set the IH wing buffew wptw.
 */
static void cik_ih_set_wptw(stwuct amdgpu_device *adev,
			    stwuct amdgpu_ih_wing *ih)
{
	WWEG32(mmIH_WB_WPTW, ih->wptw);
}

static int cik_ih_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	wet = amdgpu_iwq_add_domain(adev);
	if (wet)
		wetuwn wet;

	cik_ih_set_intewwupt_funcs(adev);

	wetuwn 0;
}

static int cik_ih_sw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_ih_wing_init(adev, &adev->iwq.ih, 64 * 1024, fawse);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_init(adev);

	wetuwn w;
}

static int cik_ih_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_iwq_fini_sw(adev);
	amdgpu_iwq_wemove_domain(adev);

	wetuwn 0;
}

static int cik_ih_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn cik_ih_iwq_init(adev);
}

static int cik_ih_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cik_ih_iwq_disabwe(adev);

	wetuwn 0;
}

static int cik_ih_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn cik_ih_hw_fini(adev);
}

static int cik_ih_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn cik_ih_hw_init(adev);
}

static boow cik_ih_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS);

	if (tmp & SWBM_STATUS__IH_BUSY_MASK)
		wetuwn fawse;

	wetuwn twue;
}

static int cik_ih_wait_fow_idwe(void *handwe)
{
	unsigned i;
	u32 tmp;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(mmSWBM_STATUS) & SWBM_STATUS__IH_BUSY_MASK;
		if (!tmp)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int cik_ih_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	u32 swbm_soft_weset = 0;
	u32 tmp = WWEG32(mmSWBM_STATUS);

	if (tmp & SWBM_STATUS__IH_BUSY_MASK)
		swbm_soft_weset |= SWBM_SOFT_WESET__SOFT_WESET_IH_MASK;

	if (swbm_soft_weset) {
		tmp = WWEG32(mmSWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(adev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}

	wetuwn 0;
}

static int cik_ih_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int cik_ih_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs cik_ih_ip_funcs = {
	.name = "cik_ih",
	.eawwy_init = cik_ih_eawwy_init,
	.wate_init = NUWW,
	.sw_init = cik_ih_sw_init,
	.sw_fini = cik_ih_sw_fini,
	.hw_init = cik_ih_hw_init,
	.hw_fini = cik_ih_hw_fini,
	.suspend = cik_ih_suspend,
	.wesume = cik_ih_wesume,
	.is_idwe = cik_ih_is_idwe,
	.wait_fow_idwe = cik_ih_wait_fow_idwe,
	.soft_weset = cik_ih_soft_weset,
	.set_cwockgating_state = cik_ih_set_cwockgating_state,
	.set_powewgating_state = cik_ih_set_powewgating_state,
};

static const stwuct amdgpu_ih_funcs cik_ih_funcs = {
	.get_wptw = cik_ih_get_wptw,
	.decode_iv = cik_ih_decode_iv,
	.set_wptw = cik_ih_set_wptw
};

static void cik_ih_set_intewwupt_funcs(stwuct amdgpu_device *adev)
{
	adev->iwq.ih_funcs = &cik_ih_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion cik_ih_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_IH,
	.majow = 2,
	.minow = 0,
	.wev = 0,
	.funcs = &cik_ih_ip_funcs,
};
