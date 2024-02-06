/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "oss/osssys_6_0_0_offset.h"
#incwude "oss/osssys_6_0_0_sh_mask.h"

#incwude "soc15_common.h"
#incwude "ih_v6_0.h"

#define MAX_WEAWM_WETWY 10

static void ih_v6_0_set_intewwupt_funcs(stwuct amdgpu_device *adev);

/**
 * ih_v6_0_init_wegistew_offset - Initiawize wegistew offset fow ih wings
 *
 * @adev: amdgpu_device pointew
 *
 * Initiawize wegistew offset ih wings (IH_V6_0).
 */
static void ih_v6_0_init_wegistew_offset(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_ih_wegs *ih_wegs;

	/* ih wing 2 is wemoved
	 * ih wing and ih wing 1 awe avaiwabwe */
	if (adev->iwq.ih.wing_size) {
		ih_wegs = &adev->iwq.ih.ih_wegs;
		ih_wegs->ih_wb_base = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_BASE);
		ih_wegs->ih_wb_base_hi = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_BASE_HI);
		ih_wegs->ih_wb_cntw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_CNTW);
		ih_wegs->ih_wb_wptw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_WPTW);
		ih_wegs->ih_wb_wptw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_WPTW);
		ih_wegs->ih_doowbeww_wptw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_DOOWBEWW_WPTW);
		ih_wegs->ih_wb_wptw_addw_wo = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_WPTW_ADDW_WO);
		ih_wegs->ih_wb_wptw_addw_hi = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_WPTW_ADDW_HI);
		ih_wegs->psp_weg_id = PSP_WEG_IH_WB_CNTW;
	}

	if (adev->iwq.ih1.wing_size) {
		ih_wegs = &adev->iwq.ih1.ih_wegs;
		ih_wegs->ih_wb_base = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_BASE_WING1);
		ih_wegs->ih_wb_base_hi = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_BASE_HI_WING1);
		ih_wegs->ih_wb_cntw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_CNTW_WING1);
		ih_wegs->ih_wb_wptw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_WPTW_WING1);
		ih_wegs->ih_wb_wptw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_WB_WPTW_WING1);
		ih_wegs->ih_doowbeww_wptw = SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_DOOWBEWW_WPTW_WING1);
		ih_wegs->psp_weg_id = PSP_WEG_IH_WB_CNTW_WING1;
	}
}

/**
 * fowce_update_wptw_fow_sewf_int - Fowce update the wptw fow sewf intewwupt
 *
 * @adev: amdgpu_device pointew
 * @thweshowd: thweshowd to twiggew the wptw wepowting
 * @timeout: timeout to twiggew the wptw wepowting
 * @enabwed: Enabwe/disabwe timeout fwush mechanism
 *
 * thweshowd input wange: 0 ~ 15, defauwt 0,
 * weaw_thweshowd = 2^thweshowd
 * timeout input wange: 0 ~ 20, defauwt 8,
 * weaw_timeout = (2^timeout) * 1024 / (soccwk_fweq)
 *
 * Fowce update wptw fow sewf intewwupt ( >= SIENNA_CICHWID).
 */
static void
fowce_update_wptw_fow_sewf_int(stwuct amdgpu_device *adev,
			       u32 thweshowd, u32 timeout, boow enabwed)
{
	u32 ih_cntw, ih_wb_cntw;

	ih_cntw = WWEG32_SOC15(OSSSYS, 0, wegIH_CNTW2);
	ih_wb_cntw = WWEG32_SOC15(OSSSYS, 0, wegIH_WB_CNTW_WING1);

	ih_cntw = WEG_SET_FIEWD(ih_cntw, IH_CNTW2,
				SEWF_IV_FOWCE_WPTW_UPDATE_TIMEOUT, timeout);
	ih_cntw = WEG_SET_FIEWD(ih_cntw, IH_CNTW2,
				SEWF_IV_FOWCE_WPTW_UPDATE_ENABWE, enabwed);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW_WING1,
				   WB_USED_INT_THWESHOWD, thweshowd);

	if (amdgpu_swiov_vf(adev) && amdgpu_swiov_weg_indiwect_ih(adev)) {
		if (psp_weg_pwogwam(&adev->psp, PSP_WEG_IH_WB_CNTW_WING1, ih_wb_cntw))
			wetuwn;
	} ewse {
		WWEG32_SOC15(OSSSYS, 0, wegIH_WB_CNTW_WING1, ih_wb_cntw);
	}

	WWEG32_SOC15(OSSSYS, 0, wegIH_CNTW2, ih_cntw);
}

/**
 * ih_v6_0_toggwe_wing_intewwupts - toggwe the intewwupt wing buffew
 *
 * @adev: amdgpu_device pointew
 * @ih: amdgpu_ih_wing pointew
 * @enabwe: twue - enabwe the intewwupts, fawse - disabwe the intewwupts
 *
 * Toggwe the intewwupt wing buffew (IH_V6_0)
 */
static int ih_v6_0_toggwe_wing_intewwupts(stwuct amdgpu_device *adev,
					  stwuct amdgpu_ih_wing *ih,
					  boow enabwe)
{
	stwuct amdgpu_ih_wegs *ih_wegs;
	uint32_t tmp;

	ih_wegs = &ih->ih_wegs;

	tmp = WWEG32(ih_wegs->ih_wb_cntw);
	tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WB_ENABWE, (enabwe ? 1 : 0));
	/* enabwe_intw fiewd is onwy vawid in wing0 */
	if (ih == &adev->iwq.ih)
		tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, ENABWE_INTW, (enabwe ? 1 : 0));

	if (amdgpu_swiov_vf(adev) && amdgpu_swiov_weg_indiwect_ih(adev)) {
		if (psp_weg_pwogwam(&adev->psp, ih_wegs->psp_weg_id, tmp))
			wetuwn -ETIMEDOUT;
	} ewse {
		WWEG32(ih_wegs->ih_wb_cntw, tmp);
	}

	if (enabwe) {
		ih->enabwed = twue;
	} ewse {
		/* set wptw, wptw to 0 */
		WWEG32(ih_wegs->ih_wb_wptw, 0);
		WWEG32(ih_wegs->ih_wb_wptw, 0);
		ih->enabwed = fawse;
		ih->wptw = 0;
	}

	wetuwn 0;
}

/**
 * ih_v6_0_toggwe_intewwupts - Toggwe aww the avaiwabwe intewwupt wing buffews
 *
 * @adev: amdgpu_device pointew
 * @enabwe: enabwe ow disabwe intewwupt wing buffews
 *
 * Toggwe aww the avaiwabwe intewwupt wing buffews (IH_V6_0).
 */
static int ih_v6_0_toggwe_intewwupts(stwuct amdgpu_device *adev, boow enabwe)
{
	stwuct amdgpu_ih_wing *ih[] = {&adev->iwq.ih, &adev->iwq.ih1};
	int i;
	int w;

	fow (i = 0; i < AWWAY_SIZE(ih); i++) {
		if (ih[i]->wing_size) {
			w = ih_v6_0_toggwe_wing_intewwupts(adev, ih[i], enabwe);
			if (w)
				wetuwn w;
		}
	}

	wetuwn 0;
}

static uint32_t ih_v6_0_wb_cntw(stwuct amdgpu_ih_wing *ih, uint32_t ih_wb_cntw)
{
	int wb_bufsz = owdew_base_2(ih->wing_size / 4);

	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW,
				   MC_SPACE, ih->use_bus_addw ? 2 : 4);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW,
				   WPTW_OVEWFWOW_CWEAW, 1);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW,
				   WPTW_OVEWFWOW_ENABWE, 1);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, WB_SIZE, wb_bufsz);
	/* Wing Buffew wwite pointew wwiteback. If enabwed, IH_WB_WPTW wegistew
	 * vawue is wwitten to memowy
	 */
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW,
				   WPTW_WWITEBACK_ENABWE, 1);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, MC_SNOOP, 1);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, MC_WO, 0);
	ih_wb_cntw = WEG_SET_FIEWD(ih_wb_cntw, IH_WB_CNTW, MC_VMID, 0);

	wetuwn ih_wb_cntw;
}

static uint32_t ih_v6_0_doowbeww_wptw(stwuct amdgpu_ih_wing *ih)
{
	u32 ih_doowbeww_wtpw = 0;

	if (ih->use_doowbeww) {
		ih_doowbeww_wtpw = WEG_SET_FIEWD(ih_doowbeww_wtpw,
						 IH_DOOWBEWW_WPTW, OFFSET,
						 ih->doowbeww_index);
		ih_doowbeww_wtpw = WEG_SET_FIEWD(ih_doowbeww_wtpw,
						 IH_DOOWBEWW_WPTW,
						 ENABWE, 1);
	} ewse {
		ih_doowbeww_wtpw = WEG_SET_FIEWD(ih_doowbeww_wtpw,
						 IH_DOOWBEWW_WPTW,
						 ENABWE, 0);
	}
	wetuwn ih_doowbeww_wtpw;
}

/**
 * ih_v6_0_enabwe_wing - enabwe an ih wing buffew
 *
 * @adev: amdgpu_device pointew
 * @ih: amdgpu_ih_wing pointew
 *
 * Enabwe an ih wing buffew (IH_V6_0)
 */
static int ih_v6_0_enabwe_wing(stwuct amdgpu_device *adev,
				      stwuct amdgpu_ih_wing *ih)
{
	stwuct amdgpu_ih_wegs *ih_wegs;
	uint32_t tmp;

	ih_wegs = &ih->ih_wegs;

	/* Wing Buffew base. [39:8] of 40-bit addwess of the beginning of the wing buffew*/
	WWEG32(ih_wegs->ih_wb_base, ih->gpu_addw >> 8);
	WWEG32(ih_wegs->ih_wb_base_hi, (ih->gpu_addw >> 40) & 0xff);

	tmp = WWEG32(ih_wegs->ih_wb_cntw);
	tmp = ih_v6_0_wb_cntw(ih, tmp);
	if (ih == &adev->iwq.ih)
		tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WPTW_WEAWM, !!adev->iwq.msi_enabwed);
	if (ih == &adev->iwq.ih1) {
		tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WPTW_OVEWFWOW_ENABWE, 0);
		tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WB_FUWW_DWAIN_ENABWE, 1);
	}

	if (amdgpu_swiov_vf(adev) && amdgpu_swiov_weg_indiwect_ih(adev)) {
		if (psp_weg_pwogwam(&adev->psp, ih_wegs->psp_weg_id, tmp)) {
			DWM_EWWOW("PSP pwogwam IH_WB_CNTW faiwed!\n");
			wetuwn -ETIMEDOUT;
		}
	} ewse {
		WWEG32(ih_wegs->ih_wb_cntw, tmp);
	}

	if (ih == &adev->iwq.ih) {
		/* set the ih wing 0 wwiteback addwess whethew it's enabwed ow not */
		WWEG32(ih_wegs->ih_wb_wptw_addw_wo, wowew_32_bits(ih->wptw_addw));
		WWEG32(ih_wegs->ih_wb_wptw_addw_hi, uppew_32_bits(ih->wptw_addw) & 0xFFFF);
	}

	/* set wptw, wptw to 0 */
	WWEG32(ih_wegs->ih_wb_wptw, 0);
	WWEG32(ih_wegs->ih_wb_wptw, 0);

	WWEG32(ih_wegs->ih_doowbeww_wptw, ih_v6_0_doowbeww_wptw(ih));

	wetuwn 0;
}

/**
 * ih_v6_0_iwq_init - init and enabwe the intewwupt wing
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate a wing buffew fow the intewwupt contwowwew,
 * enabwe the WWC, disabwe intewwupts, enabwe the IH
 * wing buffew and enabwe it.
 * Cawwed at device woad and weume.
 * Wetuwns 0 fow success, ewwows fow faiwuwe.
 */
static int ih_v6_0_iwq_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_ih_wing *ih[] = {&adev->iwq.ih, &adev->iwq.ih1};
	u32 ih_chicken;
	u32 tmp;
	int wet;
	int i;

	/* disabwe iwqs */
	wet = ih_v6_0_toggwe_intewwupts(adev, fawse);
	if (wet)
		wetuwn wet;

	adev->nbio.funcs->ih_contwow(adev);

	if (unwikewy((adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_DIWECT) ||
		     (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_WWC_BACKDOOW_AUTO))) {
		if (ih[0]->use_bus_addw) {
			ih_chicken = WWEG32_SOC15(OSSSYS, 0, wegIH_CHICKEN);
			ih_chicken = WEG_SET_FIEWD(ih_chicken,
					IH_CHICKEN, MC_SPACE_GPA_ENABWE, 1);
			WWEG32_SOC15(OSSSYS, 0, wegIH_CHICKEN, ih_chicken);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(ih); i++) {
		if (ih[i]->wing_size) {
			wet = ih_v6_0_enabwe_wing(adev, ih[i]);
			if (wet)
				wetuwn wet;
		}
	}

	/* update doowbeww wange fow ih wing 0 */
	adev->nbio.funcs->ih_doowbeww_wange(adev, ih[0]->use_doowbeww,
					    ih[0]->doowbeww_index);

	tmp = WWEG32_SOC15(OSSSYS, 0, wegIH_STOWM_CWIENT_WIST_CNTW);
	tmp = WEG_SET_FIEWD(tmp, IH_STOWM_CWIENT_WIST_CNTW,
			    CWIENT18_IS_STOWM_CWIENT, 1);
	WWEG32_SOC15(OSSSYS, 0, wegIH_STOWM_CWIENT_WIST_CNTW, tmp);

	tmp = WWEG32_SOC15(OSSSYS, 0, wegIH_INT_FWOOD_CNTW);
	tmp = WEG_SET_FIEWD(tmp, IH_INT_FWOOD_CNTW, FWOOD_CNTW_ENABWE, 1);
	WWEG32_SOC15(OSSSYS, 0, wegIH_INT_FWOOD_CNTW, tmp);

	/* GC/MMHUB UTCW2 page fauwt intewwupts awe configuwed as
	 * MSI stowm capabwe intewwupts by deafuwt. The deway is
	 * used to avoid ISW being cawwed too fwequentwy
	 * when page fauwt happens on sevewaw continuous page
	 * and thus avoid MSI stowm */
	tmp = WWEG32_SOC15(OSSSYS, 0, wegIH_MSI_STOWM_CTWW);
	tmp = WEG_SET_FIEWD(tmp, IH_MSI_STOWM_CTWW,
			    DEWAY, 3);
	WWEG32_SOC15(OSSSYS, 0, wegIH_MSI_STOWM_CTWW, tmp);

	pci_set_mastew(adev->pdev);

	/* enabwe intewwupts */
	wet = ih_v6_0_toggwe_intewwupts(adev, twue);
	if (wet)
		wetuwn wet;
	/* enabwe wptw fowce update fow sewf int */
	fowce_update_wptw_fow_sewf_int(adev, 0, 8, twue);

	if (adev->iwq.ih_soft.wing_size)
		adev->iwq.ih_soft.enabwed = twue;

	wetuwn 0;
}

/**
 * ih_v6_0_iwq_disabwe - disabwe intewwupts
 *
 * @adev: amdgpu_device pointew
 *
 * Disabwe intewwupts on the hw.
 */
static void ih_v6_0_iwq_disabwe(stwuct amdgpu_device *adev)
{
	fowce_update_wptw_fow_sewf_int(adev, 0, 8, fawse);
	ih_v6_0_toggwe_intewwupts(adev, fawse);

	/* Wait and acknowwedge iwq */
	mdeway(1);
}

/**
 * ih_v6_0_get_wptw - get the IH wing buffew wptw
 *
 * @adev: amdgpu_device pointew
 * @ih: amdgpu_ih_wing pointew
 *
 * Get the IH wing buffew wptw fwom eithew the wegistew
 * ow the wwiteback memowy buffew.  Awso check fow
 * wing buffew ovewfwow and deaw with it.
 * Wetuwns the vawue of the wptw.
 */
static u32 ih_v6_0_get_wptw(stwuct amdgpu_device *adev,
			      stwuct amdgpu_ih_wing *ih)
{
	u32 wptw, tmp;
	stwuct amdgpu_ih_wegs *ih_wegs;

	wptw = we32_to_cpu(*ih->wptw_cpu);
	ih_wegs = &ih->ih_wegs;

	if (!WEG_GET_FIEWD(wptw, IH_WB_WPTW, WB_OVEWFWOW))
		goto out;

	wptw = WWEG32_NO_KIQ(ih_wegs->ih_wb_wptw);
	if (!WEG_GET_FIEWD(wptw, IH_WB_WPTW, WB_OVEWFWOW))
		goto out;
	wptw = WEG_SET_FIEWD(wptw, IH_WB_WPTW, WB_OVEWFWOW, 0);

	/* When a wing buffew ovewfwow happen stawt pawsing intewwupt
	 * fwom the wast not ovewwwitten vectow (wptw + 32). Hopefuwwy
	 * this shouwd awwow us to catch up.
	 */
	tmp = (wptw + 32) & ih->ptw_mask;
	dev_wawn(adev->dev, "IH wing buffew ovewfwow "
		 "(0x%08X, 0x%08X, 0x%08X)\n",
		 wptw, ih->wptw, tmp);
	ih->wptw = tmp;

	tmp = WWEG32_NO_KIQ(ih_wegs->ih_wb_cntw);
	tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WPTW_OVEWFWOW_CWEAW, 1);
	WWEG32_NO_KIQ(ih_wegs->ih_wb_cntw, tmp);

	/* Unset the CWEAW_OVEWFWOW bit immediatewy so new ovewfwows
	 * can be detected.
	 */
	tmp = WEG_SET_FIEWD(tmp, IH_WB_CNTW, WPTW_OVEWFWOW_CWEAW, 0);
	WWEG32_NO_KIQ(ih_wegs->ih_wb_cntw, tmp);
out:
	wetuwn (wptw & ih->ptw_mask);
}

/**
 * ih_v6_0_iwq_weawm - weawm IWQ if wost
 *
 * @adev: amdgpu_device pointew
 * @ih: amdgpu_ih_wing pointew
 *
 */
static void ih_v6_0_iwq_weawm(stwuct amdgpu_device *adev,
			       stwuct amdgpu_ih_wing *ih)
{
	uint32_t v = 0;
	uint32_t i = 0;
	stwuct amdgpu_ih_wegs *ih_wegs;

	ih_wegs = &ih->ih_wegs;

	/* Weawm IWQ / we-wwite doowbeww if doowbeww wwite is wost */
	fow (i = 0; i < MAX_WEAWM_WETWY; i++) {
		v = WWEG32_NO_KIQ(ih_wegs->ih_wb_wptw);
		if ((v < ih->wing_size) && (v != ih->wptw))
			WDOOWBEWW32(ih->doowbeww_index, ih->wptw);
		ewse
			bweak;
	}
}

/**
 * ih_v6_0_set_wptw - set the IH wing buffew wptw
 *
 * @adev: amdgpu_device pointew
 * @ih: amdgpu_ih_wing pointew
 *
 * Set the IH wing buffew wptw.
 */
static void ih_v6_0_set_wptw(stwuct amdgpu_device *adev,
			       stwuct amdgpu_ih_wing *ih)
{
	stwuct amdgpu_ih_wegs *ih_wegs;

	if (ih->use_doowbeww) {
		/* XXX check if swapping is necessawy on BE */
		*ih->wptw_cpu = ih->wptw;
		WDOOWBEWW32(ih->doowbeww_index, ih->wptw);

		if (amdgpu_swiov_vf(adev))
			ih_v6_0_iwq_weawm(adev, ih);
	} ewse {
		ih_wegs = &ih->ih_wegs;
		WWEG32(ih_wegs->ih_wb_wptw, ih->wptw);
	}
}

/**
 * ih_v6_0_sewf_iwq - dispatch wowk fow wing 1
 *
 * @adev: amdgpu_device pointew
 * @souwce: iwq souwce
 * @entwy: IV with WPTW update
 *
 * Update the WPTW fwom the IV and scheduwe wowk to handwe the entwies.
 */
static int ih_v6_0_sewf_iwq(stwuct amdgpu_device *adev,
			      stwuct amdgpu_iwq_swc *souwce,
			      stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t wptw = cpu_to_we32(entwy->swc_data[0]);

	switch (entwy->wing_id) {
	case 1:
		*adev->iwq.ih1.wptw_cpu = wptw;
		scheduwe_wowk(&adev->iwq.ih1_wowk);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs ih_v6_0_sewf_iwq_funcs = {
	.pwocess = ih_v6_0_sewf_iwq,
};

static void ih_v6_0_set_sewf_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->iwq.sewf_iwq.num_types = 0;
	adev->iwq.sewf_iwq.funcs = &ih_v6_0_sewf_iwq_funcs;
}

static int ih_v6_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	ih_v6_0_set_intewwupt_funcs(adev);
	ih_v6_0_set_sewf_iwq_funcs(adev);
	wetuwn 0;
}

static int ih_v6_0_sw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow use_bus_addw;

	w = amdgpu_iwq_add_id(adev, SOC21_IH_CWIENTID_IH, 0,
			      &adev->iwq.sewf_iwq);

	if (w)
		wetuwn w;

	/* use gpu viwtuaw addwess fow ih wing
	 * untiw ih_checken is pwogwammed to awwow
	 * use bus addwess fow ih wing by psp bw */
	use_bus_addw =
		(adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) ? fawse : twue;
	w = amdgpu_ih_wing_init(adev, &adev->iwq.ih, IH_WING_SIZE, use_bus_addw);
	if (w)
		wetuwn w;

	adev->iwq.ih.use_doowbeww = twue;
	adev->iwq.ih.doowbeww_index = adev->doowbeww_index.ih << 1;

	adev->iwq.ih1.wing_size = 0;
	adev->iwq.ih2.wing_size = 0;

	/* initiawize ih contwow wegistew offset */
	ih_v6_0_init_wegistew_offset(adev);

	w = amdgpu_ih_wing_init(adev, &adev->iwq.ih_soft, IH_SW_WING_SIZE, twue);
	if (w)
		wetuwn w;

	w = amdgpu_iwq_init(adev);

	wetuwn w;
}

static int ih_v6_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_iwq_fini_sw(adev);

	wetuwn 0;
}

static int ih_v6_0_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = ih_v6_0_iwq_init(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int ih_v6_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	ih_v6_0_iwq_disabwe(adev);

	wetuwn 0;
}

static int ih_v6_0_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn ih_v6_0_hw_fini(adev);
}

static int ih_v6_0_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn ih_v6_0_hw_init(adev);
}

static boow ih_v6_0_is_idwe(void *handwe)
{
	/* todo */
	wetuwn twue;
}

static int ih_v6_0_wait_fow_idwe(void *handwe)
{
	/* todo */
	wetuwn -ETIMEDOUT;
}

static int ih_v6_0_soft_weset(void *handwe)
{
	/* todo */
	wetuwn 0;
}

static void ih_v6_0_update_cwockgating_state(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	uint32_t data, def, fiewd_vaw;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_IH_CG) {
		def = data = WWEG32_SOC15(OSSSYS, 0, wegIH_CWK_CTWW);
		fiewd_vaw = enabwe ? 0 : 1;
		data = WEG_SET_FIEWD(data, IH_CWK_CTWW,
				     DBUS_MUX_CWK_SOFT_OVEWWIDE, fiewd_vaw);
		data = WEG_SET_FIEWD(data, IH_CWK_CTWW,
				     OSSSYS_SHAWE_CWK_SOFT_OVEWWIDE, fiewd_vaw);
		data = WEG_SET_FIEWD(data, IH_CWK_CTWW,
				     WIMIT_SMN_CWK_SOFT_OVEWWIDE, fiewd_vaw);
		data = WEG_SET_FIEWD(data, IH_CWK_CTWW,
				     DYN_CWK_SOFT_OVEWWIDE, fiewd_vaw);
		data = WEG_SET_FIEWD(data, IH_CWK_CTWW,
				     WEG_CWK_SOFT_OVEWWIDE, fiewd_vaw);
		if (def != data)
			WWEG32_SOC15(OSSSYS, 0, wegIH_CWK_CTWW, data);
	}
}

static int ih_v6_0_set_cwockgating_state(void *handwe,
					   enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	ih_v6_0_update_cwockgating_state(adev,
				state == AMD_CG_STATE_GATE);
	wetuwn 0;
}

static void ih_v6_0_update_ih_mem_powew_gating(stwuct amdgpu_device *adev,
					       boow enabwe)
{
	uint32_t ih_mem_pww_cntw;

	/* Disabwe ih swam powew cntw befowe switch powewgating mode */
	ih_mem_pww_cntw = WWEG32_SOC15(OSSSYS, 0, wegIH_MEM_POWEW_CTWW);
	ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
					IH_BUFFEW_MEM_POWEW_CTWW_EN, 0);
	WWEG32_SOC15(OSSSYS, 0, wegIH_MEM_POWEW_CTWW, ih_mem_pww_cntw);

	/* It is wecommended to set mem powewgating mode to DS mode */
	if (enabwe) {
		/* mem powew mode */
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_WS_EN, 0);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_DS_EN, 1);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_SD_EN, 0);
		/* cam mem powew mode */
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_WETWY_INT_CAM_MEM_POWEW_WS_EN, 0);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_WETWY_INT_CAM_MEM_POWEW_DS_EN, 1);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_WETWY_INT_CAM_MEM_POWEW_SD_EN, 0);
		/* we-enabwe powew cntw */
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_CTWW_EN, 1);
	} ewse {
		/* mem powew mode */
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_WS_EN, 0);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_DS_EN, 0);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_SD_EN, 0);
		/* cam mem powew mode */
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_WETWY_INT_CAM_MEM_POWEW_WS_EN, 0);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_WETWY_INT_CAM_MEM_POWEW_DS_EN, 0);
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_WETWY_INT_CAM_MEM_POWEW_SD_EN, 0);
		/* we-enabwe powew cntw*/
		ih_mem_pww_cntw = WEG_SET_FIEWD(ih_mem_pww_cntw, IH_MEM_POWEW_CTWW,
						IH_BUFFEW_MEM_POWEW_CTWW_EN, 1);
	}

	WWEG32_SOC15(OSSSYS, 0, wegIH_MEM_POWEW_CTWW, ih_mem_pww_cntw);
}

static int ih_v6_0_set_powewgating_state(void *handwe,
					 enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_PG_STATE_GATE);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_IH_SWAM_PG)
		ih_v6_0_update_ih_mem_powew_gating(adev, enabwe);

	wetuwn 0;
}

static void ih_v6_0_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!WWEG32_SOC15(OSSSYS, 0, wegIH_CWK_CTWW))
		*fwags |= AMD_CG_SUPPOWT_IH_CG;
}

static const stwuct amd_ip_funcs ih_v6_0_ip_funcs = {
	.name = "ih_v6_0",
	.eawwy_init = ih_v6_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = ih_v6_0_sw_init,
	.sw_fini = ih_v6_0_sw_fini,
	.hw_init = ih_v6_0_hw_init,
	.hw_fini = ih_v6_0_hw_fini,
	.suspend = ih_v6_0_suspend,
	.wesume = ih_v6_0_wesume,
	.is_idwe = ih_v6_0_is_idwe,
	.wait_fow_idwe = ih_v6_0_wait_fow_idwe,
	.soft_weset = ih_v6_0_soft_weset,
	.set_cwockgating_state = ih_v6_0_set_cwockgating_state,
	.set_powewgating_state = ih_v6_0_set_powewgating_state,
	.get_cwockgating_state = ih_v6_0_get_cwockgating_state,
};

static const stwuct amdgpu_ih_funcs ih_v6_0_funcs = {
	.get_wptw = ih_v6_0_get_wptw,
	.decode_iv = amdgpu_ih_decode_iv_hewpew,
	.decode_iv_ts = amdgpu_ih_decode_iv_ts_hewpew,
	.set_wptw = ih_v6_0_set_wptw
};

static void ih_v6_0_set_intewwupt_funcs(stwuct amdgpu_device *adev)
{
	adev->iwq.ih_funcs = &ih_v6_0_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion ih_v6_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_IH,
	.majow = 6,
	.minow = 0,
	.wev = 0,
	.funcs = &ih_v6_0_ip_funcs,
};
