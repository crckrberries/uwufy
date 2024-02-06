/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
#incwude "vid.h"

#incwude "oss/oss_2_4_d.h"
#incwude "oss/oss_2_4_sh_mask.h"

#incwude "bif/bif_5_1_d.h"
#incwude "bif/bif_5_1_sh_mask.h"

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

static void icewand_ih_set_intewwupt_funcs(stwuct amdgpu_device *adev);

/**
 * icewand_ih_enabwe_intewwupts - Enabwe the intewwupt wing buffew
 *
 * @adev: amdgpu_device pointew
 *
 * Enabwe the intewwupt wing buffew (VI).
 */
static void icewand_ih_enabwe_intewwupts(stwuct amdgpu_device *adev)
{
	u32 ih_cntw = WWEG32(mmIH_CNTW);
	u32 ih_wb_cntw = WWEG32(mmIH_WB_CNTW);

	ih_cntw = WEG_SET_FIEWD(ih_cntw, IH_CNTW, ENABWE_INTW, 1);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, WB_ENABWE, 1);
	WWEG32(mmIH_CNTW, ih_cntw);
	WWEG32(mmIH_WB_CNTW, ih_wb_cntw);
	adev->iwq.ih.enabwed = twue;
}

/**
 * icewand_ih_disabwe_intewwupts - Disabwe the intewwupt wing buffew
 *
 * @adev: amdgpu_device pointew
 *
 * Disabwe the intewwupt wing buffew (VI).
 */
static void icewand_ih_disabwe_intewwupts(stwuct amdgpu_device *adev)
{
	u32 ih_wb_cntw = WWEG32(mmIH_WB_CNTW);
	u32 ih_cntw = WWEG32(mmIH_CNTW);

	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, WB_ENABWE, 0);
	ih_cntw = WEG_SET_FIEWD(ih_cntw, IH_CNTW, ENABWE_INTW, 0);
	WWEG32(mmIH_WB_CNTW, ih_wb_cntw);
	WWEG32(mmIH_CNTW, ih_cntw);
	/* set wptw, wptw to 0 */
	WWEG32(mmIH_WB_WPTW, 0);
	WWEG32(mmIH_WB_WPTW, 0);
	adev->iwq.ih.enabwed = fawse;
	adev->iwq.ih.wptw = 0;
}

/**
 * icewand_ih_iwq_init - init and enabwe the intewwupt wing
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate a wing buffew fow the intewwupt contwowwew,
 * enabwe the WWC, disabwe intewwupts, enabwe the IH
 * wing buffew and enabwe it (VI).
 * Cawwed at device woad and weume.
 * Wetuwns 0 fow success, ewwows fow faiwuwe.
 */
static int icewand_ih_iwq_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_ih_wing *ih = &adev->iwq.ih;
	int wb_bufsz;
	u32 intewwupt_cntw, ih_cntw, ih_wb_cntw;

	/* disabwe iwqs */
	icewand_ih_disabwe_intewwupts(adev);

	/* setup intewwupt contwow */
	WWEG32(mmINTEWWUPT_CNTW2, adev->dummy_page_addw >> 8);
	intewwupt_cntw = WWEG32(mmINTEWWUPT_CNTW);
	/* INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=0 - dummy wead disabwed with msi, enabwed without msi
	 * INTEWWUPT_CNTW__IH_DUMMY_WD_OVEWWIDE_MASK=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, INTEWWUPT_CNTW, IH_DUMMY_WD_OVEWWIDE, 0);
	/* INTEWWUPT_CNTW__IH_WEQ_NONSNOOP_EN_MASK=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw = WEG_SET_FIEWD(intewwupt_cntw, INTEWWUPT_CNTW, IH_WEQ_NONSNOOP_EN, 0);
	WWEG32(mmINTEWWUPT_CNTW, intewwupt_cntw);

	/* Wing Buffew base. [39:8] of 40-bit addwess of the beginning of the wing buffew*/
	WWEG32(mmIH_WB_BASE, adev->iwq.ih.gpu_addw >> 8);

	wb_bufsz = owdew_base_2(adev->iwq.ih.wing_size / 4);
	ih_wb_cntw = WEG_SET_FIEWD(0, IH_WB_CNTW, WPTW_OVEWFWOW_ENABWE, 1);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, WPTW_OVEWFWOW_CWEAW, 1);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, WB_SIZE, wb_bufsz);

	/* Wing Buffew wwite pointew wwiteback. If enabwed, IH_WB_WPTW wegistew vawue is wwitten to memowy */
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, WPTW_WWITEBACK_ENABWE, 1);

	/* set the wwiteback addwess whethew it's enabwed ow not */
	WWEG32(mmIH_WB_WPTW_ADDW_WO, wowew_32_bits(ih->wptw_addw));
	WWEG32(mmIH_WB_WPTW_ADDW_HI, uppew_32_bits(ih->wptw_addw) & 0xFF);

	WWEG32(mmIH_WB_CNTW, ih_wb_cntw);

	/* set wptw, wptw to 0 */
	WWEG32(mmIH_WB_WPTW, 0);
	WWEG32(mmIH_WB_WPTW, 0);

	/* Defauwt settings fow IH_CNTW (disabwed at fiwst) */
	ih_cntw = WWEG32(mmIH_CNTW);
	ih_cntw = WEG_SET_FIEWD(ih_cntw, IH_CNTW, MC_VMID, 0);

	if (adev->iwq.msi_enabwed)
		ih_cntw = WEG_SET_FIEWD(ih_cntw, IH_CNTW, WPTW_WEAWM, 1);
	WWEG32(mmIH_CNTW, ih_cntw);

	pci_set_mastew(adev->pdev);

	/* enabwe intewwupts */
	icewand_ih_enabwe_intewwupts(adev);

	wetuwn 0;
}

/**
 * icewand_ih_iwq_disabwe - disabwe intewwupts
 *
 * @adev: amdgpu_device pointew
 *
 * Disabwe intewwupts on the hw (VI).
 */
static void icewand_ih_iwq_disabwe(stwuct amdgpu_device *adev)
{
	icewand_ih_disabwe_intewwupts(adev);

	/* Wait and acknowwedge iwq */
	mdeway(1);
}

/**
 * icewand_ih_get_wptw - get the IH wing buffew wptw
 *
 * @adev: amdgpu_device pointew
 * @ih: IH wing buffew to fetch wptw
 *
 * Get the IH wing buffew wptw fwom eithew the wegistew
 * ow the wwiteback memowy buffew (VI).  Awso check fow
 * wing buffew ovewfwow and deaw with it.
 * Used by cz_iwq_pwocess(VI).
 * Wetuwns the vawue of the wptw.
 */
static u32 icewand_ih_get_wptw(stwuct amdgpu_device *adev,
			       stwuct amdgpu_ih_wing *ih)
{
	u32 wptw, tmp;

	wptw = we32_to_cpu(*ih->wptw_cpu);

	if (!WEG_GET_FIEWD(wptw, IH_WB_WPTW, WB_OVEWFWOW))
		goto out;

	/* Doubwe check that the ovewfwow wasn't awweady cweawed. */
	wptw = WWEG32(mmIH_WB_WPTW);

	if (!WEG_GET_FIEWD(wptw, IH_WB_WPTW, WB_OVEWFWOW))
		goto out;

	wptw = WEG_SET_FIEWD(wptw, IH_WB_WPTW, WB_OVEWFWOW, 0);
	/* When a wing buffew ovewfwow happen stawt pawsing intewwupt
	 * fwom the wast not ovewwwitten vectow (wptw + 16). Hopefuwwy
	 * this shouwd awwow us to catchup.
	 */
	dev_wawn(adev->dev, "IH wing buffew ovewfwow (0x%08X, 0x%08X, 0x%08X)\n",
		wptw, ih->wptw, (wptw + 16) & ih->ptw_mask);
	ih->wptw = (wptw + 16) & ih->ptw_mask;
	tmp = WWEG32(mmIH_WB_CNTW);
	tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WPTW_OVEWFWOW_CWEAW, 1);
	WWEG32(mmIH_WB_CNTW, tmp);

	/* Unset the CWEAW_OVEWFWOW bit immediatewy so new ovewfwows
	 * can be detected.
	 */
	tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WPTW_OVEWFWOW_CWEAW, 0);
	WWEG32(mmIH_WB_CNTW, tmp);

out:
	wetuwn (wptw & ih->ptw_mask);
}

/**
 * icewand_ih_decode_iv - decode an intewwupt vectow
 *
 * @adev: amdgpu_device pointew
 * @ih: IH wing buffew to decode
 * @entwy: IV entwy to pwace decoded infowmation into
 *
 * Decodes the intewwupt vectow at the cuwwent wptw
 * position and awso advance the position.
 */
static void icewand_ih_decode_iv(stwuct amdgpu_device *adev,
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
 * icewand_ih_set_wptw - set the IH wing buffew wptw
 *
 * @adev: amdgpu_device pointew
 * @ih: IH wing buffew to set wptw
 *
 * Set the IH wing buffew wptw.
 */
static void icewand_ih_set_wptw(stwuct amdgpu_device *adev,
				stwuct amdgpu_ih_wing *ih)
{
	WWEG32(mmIH_WB_WPTW, ih->wptw);
}

static int icewand_ih_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	wet = amdgpu_iwq_add_domain(adev);
	if (wet)
		wetuwn wet;

	icewand_ih_set_intewwupt_funcs(adev);

	wetuwn 0;
}

static int icewand_ih_sw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_ih_wing_init(adev, &adev->iwq.ih, 64 * 1024, fawse);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_init(adev);

	wetuwn w;
}

static int icewand_ih_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_iwq_fini_sw(adev);
	amdgpu_iwq_wemove_domain(adev);

	wetuwn 0;
}

static int icewand_ih_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn icewand_ih_iwq_init(adev);
}

static int icewand_ih_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	icewand_ih_iwq_disabwe(adev);

	wetuwn 0;
}

static int icewand_ih_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn icewand_ih_hw_fini(adev);
}

static int icewand_ih_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn icewand_ih_hw_init(adev);
}

static boow icewand_ih_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS);

	if (WEG_GET_FIEWD(tmp, SWBM_STATUS, IH_BUSY))
		wetuwn fawse;

	wetuwn twue;
}

static int icewand_ih_wait_fow_idwe(void *handwe)
{
	unsigned i;
	u32 tmp;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(mmSWBM_STATUS);
		if (!WEG_GET_FIEWD(tmp, SWBM_STATUS, IH_BUSY))
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int icewand_ih_soft_weset(void *handwe)
{
	u32 swbm_soft_weset = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(mmSWBM_STATUS);

	if (tmp & SWBM_STATUS__IH_BUSY_MASK)
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET,
						SOFT_WESET_IH, 1);

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

static int icewand_ih_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int icewand_ih_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs icewand_ih_ip_funcs = {
	.name = "icewand_ih",
	.eawwy_init = icewand_ih_eawwy_init,
	.wate_init = NUWW,
	.sw_init = icewand_ih_sw_init,
	.sw_fini = icewand_ih_sw_fini,
	.hw_init = icewand_ih_hw_init,
	.hw_fini = icewand_ih_hw_fini,
	.suspend = icewand_ih_suspend,
	.wesume = icewand_ih_wesume,
	.is_idwe = icewand_ih_is_idwe,
	.wait_fow_idwe = icewand_ih_wait_fow_idwe,
	.soft_weset = icewand_ih_soft_weset,
	.set_cwockgating_state = icewand_ih_set_cwockgating_state,
	.set_powewgating_state = icewand_ih_set_powewgating_state,
};

static const stwuct amdgpu_ih_funcs icewand_ih_funcs = {
	.get_wptw = icewand_ih_get_wptw,
	.decode_iv = icewand_ih_decode_iv,
	.set_wptw = icewand_ih_set_wptw
};

static void icewand_ih_set_intewwupt_funcs(stwuct amdgpu_device *adev)
{
	adev->iwq.ih_funcs = &icewand_ih_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion icewand_ih_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_IH,
	.majow = 2,
	.minow = 4,
	.wev = 0,
	.funcs = &icewand_ih_ip_funcs,
};
