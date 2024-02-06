/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#incwude "amdgpu.h"
#incwude "amdgpu_jpeg.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "jpeg_v2_0.h"
#incwude "jpeg_v2_5.h"

#incwude "vcn/vcn_2_5_offset.h"
#incwude "vcn/vcn_2_5_sh_mask.h"
#incwude "ivswcid/vcn/iwqswcs_vcn_2_0.h"

#define mmUVD_JPEG_PITCH_INTEWNAW_OFFSET			0x401f

#define JPEG25_MAX_HW_INSTANCES_AWCTUWUS			2

static void jpeg_v2_5_set_dec_wing_funcs(stwuct amdgpu_device *adev);
static void jpeg_v2_5_set_iwq_funcs(stwuct amdgpu_device *adev);
static int jpeg_v2_5_set_powewgating_state(void *handwe,
				enum amd_powewgating_state state);
static void jpeg_v2_5_set_was_funcs(stwuct amdgpu_device *adev);

static int amdgpu_ih_cwientid_jpeg[] = {
	SOC15_IH_CWIENTID_VCN,
	SOC15_IH_CWIENTID_VCN1
};

/**
 * jpeg_v2_5_eawwy_init - set function pointews
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 */
static int jpeg_v2_5_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 hawvest;
	int i;

	adev->jpeg.num_jpeg_wings = 1;
	adev->jpeg.num_jpeg_inst = JPEG25_MAX_HW_INSTANCES_AWCTUWUS;
	fow (i = 0; i < adev->jpeg.num_jpeg_inst; i++) {
		hawvest = WWEG32_SOC15(JPEG, i, mmCC_UVD_HAWVESTING);
		if (hawvest & CC_UVD_HAWVESTING__UVD_DISABWE_MASK)
			adev->jpeg.hawvest_config |= 1 << i;
	}
	if (adev->jpeg.hawvest_config == (AMDGPU_JPEG_HAWVEST_JPEG0 |
					 AMDGPU_JPEG_HAWVEST_JPEG1))
		wetuwn -ENOENT;

	jpeg_v2_5_set_dec_wing_funcs(adev);
	jpeg_v2_5_set_iwq_funcs(adev);
	jpeg_v2_5_set_was_funcs(adev);

	wetuwn 0;
}

/**
 * jpeg_v2_5_sw_init - sw init fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Woad fiwmwawe and sw initiawization
 */
static int jpeg_v2_5_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	int i, w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		/* JPEG TWAP */
		w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_jpeg[i],
				VCN_2_0__SWCID__JPEG_DECODE, &adev->jpeg.inst[i].iwq);
		if (w)
			wetuwn w;

		/* JPEG DJPEG POISON EVENT */
		w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_jpeg[i],
			VCN_2_6__SWCID_DJPEG0_POISON, &adev->jpeg.inst[i].was_poison_iwq);
		if (w)
			wetuwn w;

		/* JPEG EJPEG POISON EVENT */
		w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_jpeg[i],
			VCN_2_6__SWCID_EJPEG0_POISON, &adev->jpeg.inst[i].was_poison_iwq);
		if (w)
			wetuwn w;
	}

	w = amdgpu_jpeg_sw_init(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_wesume(adev);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		wing = adev->jpeg.inst[i].wing_dec;
		wing->use_doowbeww = twue;
		if (amdgpu_ip_vewsion(adev, UVD_HWIP, 0) == IP_VEWSION(2, 5, 0))
			wing->vm_hub = AMDGPU_MMHUB1(0);
		ewse
			wing->vm_hub = AMDGPU_MMHUB0(0);
		wing->doowbeww_index = (adev->doowbeww_index.vcn.vcn_wing0_1 << 1) + 1 + 8 * i;
		spwintf(wing->name, "jpeg_dec_%d", i);
		w = amdgpu_wing_init(adev, wing, 512, &adev->jpeg.inst[i].iwq,
				     0, AMDGPU_WING_PWIO_DEFAUWT, NUWW);
		if (w)
			wetuwn w;

		adev->jpeg.intewnaw.jpeg_pitch[0] = mmUVD_JPEG_PITCH_INTEWNAW_OFFSET;
		adev->jpeg.inst[i].extewnaw.jpeg_pitch[0] = SOC15_WEG_OFFSET(JPEG, i, mmUVD_JPEG_PITCH);
	}

	w = amdgpu_jpeg_was_sw_init(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

/**
 * jpeg_v2_5_sw_fini - sw fini fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * JPEG suspend and fwee up sw awwocation
 */
static int jpeg_v2_5_sw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_jpeg_suspend(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_sw_fini(adev);

	wetuwn w;
}

/**
 * jpeg_v2_5_hw_init - stawt and test JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 */
static int jpeg_v2_5_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int i, w;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		wing = adev->jpeg.inst[i].wing_dec;
		adev->nbio.funcs->vcn_doowbeww_wange(adev, wing->use_doowbeww,
			(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) + 8 * i, i);

		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			wetuwn w;
	}

	DWM_INFO("JPEG decode initiawized successfuwwy.\n");

	wetuwn 0;
}

/**
 * jpeg_v2_5_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Stop the JPEG bwock, mawk wing as not weady any mowe
 */
static int jpeg_v2_5_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		if (adev->jpeg.cuw_state != AMD_PG_STATE_GATE &&
		      WWEG32_SOC15(JPEG, i, mmUVD_JWBC_STATUS))
			jpeg_v2_5_set_powewgating_state(adev, AMD_PG_STATE_GATE);

		if (amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__JPEG))
			amdgpu_iwq_put(adev, &adev->jpeg.inst[i].was_poison_iwq, 0);
	}

	wetuwn 0;
}

/**
 * jpeg_v2_5_suspend - suspend JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * HW fini and suspend JPEG bwock
 */
static int jpeg_v2_5_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = jpeg_v2_5_hw_fini(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_suspend(adev);

	wetuwn w;
}

/**
 * jpeg_v2_5_wesume - wesume JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Wesume fiwmwawe and hw init JPEG bwock
 */
static int jpeg_v2_5_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_jpeg_wesume(adev);
	if (w)
		wetuwn w;

	w = jpeg_v2_5_hw_init(adev);

	wetuwn w;
}

static void jpeg_v2_5_disabwe_cwock_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	data = WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_JPEG_MGCG)
		data |= 1 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data &= ~JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;

	data |= 1 << JPEG_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << JPEG_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_CTWW, data);

	data = WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE);
	data &= ~(JPEG_CGC_GATE__JPEG_DEC_MASK
		| JPEG_CGC_GATE__JPEG2_DEC_MASK
		| JPEG_CGC_GATE__JMCIF_MASK
		| JPEG_CGC_GATE__JWBBM_MASK);
	WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE, data);

	data = WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_CTWW);
	data &= ~(JPEG_CGC_CTWW__JPEG_DEC_MODE_MASK
		| JPEG_CGC_CTWW__JPEG2_DEC_MODE_MASK
		| JPEG_CGC_CTWW__JMCIF_MODE_MASK
		| JPEG_CGC_CTWW__JWBBM_MODE_MASK);
	WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_CTWW, data);
}

static void jpeg_v2_5_enabwe_cwock_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	data = WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JPEG_DEC_MASK
		|JPEG_CGC_GATE__JPEG2_DEC_MASK
		|JPEG_CGC_GATE__JPEG_ENC_MASK
		|JPEG_CGC_GATE__JMCIF_MASK
		|JPEG_CGC_GATE__JWBBM_MASK);
	WWEG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE, data);
}

/**
 * jpeg_v2_5_stawt - stawt JPEG bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the JPEG bwock
 */
static int jpeg_v2_5_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	int i;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		wing = adev->jpeg.inst[i].wing_dec;
		/* disabwe anti hang mechanism */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, i, mmUVD_JPEG_POWEW_STATUS), 0,
			~UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK);

		/* JPEG disabwe CGC */
		jpeg_v2_5_disabwe_cwock_gating(adev, i);

		/* MJPEG gwobaw tiwing wegistews */
		WWEG32_SOC15(JPEG, i, mmJPEG_DEC_GFX8_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
		WWEG32_SOC15(JPEG, i, mmJPEG_DEC_GFX10_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);

		/* enabwe JMI channew */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, i, mmUVD_JMI_CNTW), 0,
			~UVD_JMI_CNTW__SOFT_WESET_MASK);

		/* enabwe System Intewwupt fow JWBC */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, i, mmJPEG_SYS_INT_EN),
			JPEG_SYS_INT_EN__DJWBC_MASK,
			~JPEG_SYS_INT_EN__DJWBC_MASK);

		WWEG32_SOC15(JPEG, i, mmUVD_WMI_JWBC_WB_VMID, 0);
		WWEG32_SOC15(JPEG, i, mmUVD_JWBC_WB_CNTW, (0x00000001W | 0x00000002W));
		WWEG32_SOC15(JPEG, i, mmUVD_WMI_JWBC_WB_64BIT_BAW_WOW,
			wowew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(JPEG, i, mmUVD_WMI_JWBC_WB_64BIT_BAW_HIGH,
			uppew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(JPEG, i, mmUVD_JWBC_WB_WPTW, 0);
		WWEG32_SOC15(JPEG, i, mmUVD_JWBC_WB_WPTW, 0);
		WWEG32_SOC15(JPEG, i, mmUVD_JWBC_WB_CNTW, 0x00000002W);
		WWEG32_SOC15(JPEG, i, mmUVD_JWBC_WB_SIZE, wing->wing_size / 4);
		wing->wptw = WWEG32_SOC15(JPEG, i, mmUVD_JWBC_WB_WPTW);
	}

	wetuwn 0;
}

/**
 * jpeg_v2_5_stop - stop JPEG bwock
 *
 * @adev: amdgpu_device pointew
 *
 * stop the JPEG bwock
 */
static int jpeg_v2_5_stop(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		/* weset JMI */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, i, mmUVD_JMI_CNTW),
			UVD_JMI_CNTW__SOFT_WESET_MASK,
			~UVD_JMI_CNTW__SOFT_WESET_MASK);

		jpeg_v2_5_enabwe_cwock_gating(adev, i);

		/* enabwe anti hang mechanism */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, i, mmUVD_JPEG_POWEW_STATUS),
			UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK,
			~UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK);
	}

	wetuwn 0;
}

/**
 * jpeg_v2_5_dec_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t jpeg_v2_5_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(JPEG, wing->me, mmUVD_JWBC_WB_WPTW);
}

/**
 * jpeg_v2_5_dec_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t jpeg_v2_5_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		wetuwn *wing->wptw_cpu_addw;
	ewse
		wetuwn WWEG32_SOC15(JPEG, wing->me, mmUVD_JWBC_WB_WPTW);
}

/**
 * jpeg_v2_5_dec_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void jpeg_v2_5_dec_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww) {
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
	} ewse {
		WWEG32_SOC15(JPEG, wing->me, mmUVD_JWBC_WB_WPTW, wowew_32_bits(wing->wptw));
	}
}

/**
 * jpeg_v2_6_dec_wing_insewt_stawt - insewt a stawt command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a stawt command to the wing.
 */
static void jpeg_v2_6_dec_wing_insewt_stawt(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKETJ(mmUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x6aa04); /* PCTW0_MMHUB_DEEPSWEEP_IB */

	amdgpu_wing_wwite(wing, PACKETJ(JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x80000000 | (1 << (wing->me * 2 + 14)));
}

/**
 * jpeg_v2_6_dec_wing_insewt_end - insewt a end command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a end command to the wing.
 */
static void jpeg_v2_6_dec_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, PACKETJ(mmUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x6aa04); /* PCTW0_MMHUB_DEEPSWEEP_IB */

	amdgpu_wing_wwite(wing, PACKETJ(JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, (1 << (wing->me * 2 + 14)));
}

static boow jpeg_v2_5_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet = 1;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		wet &= (((WWEG32_SOC15(JPEG, i, mmUVD_JWBC_STATUS) &
			UVD_JWBC_STATUS__WB_JOB_DONE_MASK) ==
			UVD_JWBC_STATUS__WB_JOB_DONE_MASK));
	}

	wetuwn wet;
}

static int jpeg_v2_5_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		wet = SOC15_WAIT_ON_WWEG(JPEG, i, mmUVD_JWBC_STATUS,
			UVD_JWBC_STATUS__WB_JOB_DONE_MASK,
			UVD_JWBC_STATUS__WB_JOB_DONE_MASK);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int jpeg_v2_5_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_CG_STATE_GATE);
	int i;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		if (enabwe) {
			if (!jpeg_v2_5_is_idwe(handwe))
				wetuwn -EBUSY;
			jpeg_v2_5_enabwe_cwock_gating(adev, i);
		} ewse {
			jpeg_v2_5_disabwe_cwock_gating(adev, i);
		}
	}

	wetuwn 0;
}

static int jpeg_v2_5_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	if(state == adev->jpeg.cuw_state)
		wetuwn 0;

	if (state == AMD_PG_STATE_GATE)
		wet = jpeg_v2_5_stop(adev);
	ewse
		wet = jpeg_v2_5_stawt(adev);

	if(!wet)
		adev->jpeg.cuw_state = state;

	wetuwn wet;
}

static int jpeg_v2_5_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

static int jpeg_v2_6_set_was_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned int type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

static int jpeg_v2_5_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t ip_instance;

	switch (entwy->cwient_id) {
	case SOC15_IH_CWIENTID_VCN:
		ip_instance = 0;
		bweak;
	case SOC15_IH_CWIENTID_VCN1:
		ip_instance = 1;
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed cwient id: %d\n", entwy->cwient_id);
		wetuwn 0;
	}

	DWM_DEBUG("IH: JPEG TWAP\n");

	switch (entwy->swc_id) {
	case VCN_2_0__SWCID__JPEG_DECODE:
		amdgpu_fence_pwocess(adev->jpeg.inst[ip_instance].wing_dec);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static const stwuct amd_ip_funcs jpeg_v2_5_ip_funcs = {
	.name = "jpeg_v2_5",
	.eawwy_init = jpeg_v2_5_eawwy_init,
	.wate_init = NUWW,
	.sw_init = jpeg_v2_5_sw_init,
	.sw_fini = jpeg_v2_5_sw_fini,
	.hw_init = jpeg_v2_5_hw_init,
	.hw_fini = jpeg_v2_5_hw_fini,
	.suspend = jpeg_v2_5_suspend,
	.wesume = jpeg_v2_5_wesume,
	.is_idwe = jpeg_v2_5_is_idwe,
	.wait_fow_idwe = jpeg_v2_5_wait_fow_idwe,
	.check_soft_weset = NUWW,
	.pwe_soft_weset = NUWW,
	.soft_weset = NUWW,
	.post_soft_weset = NUWW,
	.set_cwockgating_state = jpeg_v2_5_set_cwockgating_state,
	.set_powewgating_state = jpeg_v2_5_set_powewgating_state,
};

static const stwuct amd_ip_funcs jpeg_v2_6_ip_funcs = {
	.name = "jpeg_v2_6",
	.eawwy_init = jpeg_v2_5_eawwy_init,
	.wate_init = NUWW,
	.sw_init = jpeg_v2_5_sw_init,
	.sw_fini = jpeg_v2_5_sw_fini,
	.hw_init = jpeg_v2_5_hw_init,
	.hw_fini = jpeg_v2_5_hw_fini,
	.suspend = jpeg_v2_5_suspend,
	.wesume = jpeg_v2_5_wesume,
	.is_idwe = jpeg_v2_5_is_idwe,
	.wait_fow_idwe = jpeg_v2_5_wait_fow_idwe,
	.check_soft_weset = NUWW,
	.pwe_soft_weset = NUWW,
	.soft_weset = NUWW,
	.post_soft_weset = NUWW,
	.set_cwockgating_state = jpeg_v2_5_set_cwockgating_state,
	.set_powewgating_state = jpeg_v2_5_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs jpeg_v2_5_dec_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_JPEG,
	.awign_mask = 0xf,
	.get_wptw = jpeg_v2_5_dec_wing_get_wptw,
	.get_wptw = jpeg_v2_5_dec_wing_get_wptw,
	.set_wptw = jpeg_v2_5_dec_wing_set_wptw,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* jpeg_v2_5_dec_wing_emit_vm_fwush */
		18 + 18 + /* jpeg_v2_5_dec_wing_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v2_5_dec_wing_emit_ib */
	.emit_ib = jpeg_v2_0_dec_wing_emit_ib,
	.emit_fence = jpeg_v2_0_dec_wing_emit_fence,
	.emit_vm_fwush = jpeg_v2_0_dec_wing_emit_vm_fwush,
	.test_wing = amdgpu_jpeg_dec_wing_test_wing,
	.test_ib = amdgpu_jpeg_dec_wing_test_ib,
	.insewt_nop = jpeg_v2_0_dec_wing_nop,
	.insewt_stawt = jpeg_v2_0_dec_wing_insewt_stawt,
	.insewt_end = jpeg_v2_0_dec_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_jpeg_wing_begin_use,
	.end_use = amdgpu_jpeg_wing_end_use,
	.emit_wweg = jpeg_v2_0_dec_wing_emit_wweg,
	.emit_weg_wait = jpeg_v2_0_dec_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static const stwuct amdgpu_wing_funcs jpeg_v2_6_dec_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_JPEG,
	.awign_mask = 0xf,
	.get_wptw = jpeg_v2_5_dec_wing_get_wptw,
	.get_wptw = jpeg_v2_5_dec_wing_get_wptw,
	.set_wptw = jpeg_v2_5_dec_wing_set_wptw,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* jpeg_v2_5_dec_wing_emit_vm_fwush */
		18 + 18 + /* jpeg_v2_5_dec_wing_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v2_5_dec_wing_emit_ib */
	.emit_ib = jpeg_v2_0_dec_wing_emit_ib,
	.emit_fence = jpeg_v2_0_dec_wing_emit_fence,
	.emit_vm_fwush = jpeg_v2_0_dec_wing_emit_vm_fwush,
	.test_wing = amdgpu_jpeg_dec_wing_test_wing,
	.test_ib = amdgpu_jpeg_dec_wing_test_ib,
	.insewt_nop = jpeg_v2_0_dec_wing_nop,
	.insewt_stawt = jpeg_v2_6_dec_wing_insewt_stawt,
	.insewt_end = jpeg_v2_6_dec_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_jpeg_wing_begin_use,
	.end_use = amdgpu_jpeg_wing_end_use,
	.emit_wweg = jpeg_v2_0_dec_wing_emit_wweg,
	.emit_weg_wait = jpeg_v2_0_dec_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void jpeg_v2_5_set_dec_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;
		if (adev->asic_type == CHIP_AWCTUWUS)
			adev->jpeg.inst[i].wing_dec->funcs = &jpeg_v2_5_dec_wing_vm_funcs;
		ewse  /* CHIP_AWDEBAWAN */
			adev->jpeg.inst[i].wing_dec->funcs = &jpeg_v2_6_dec_wing_vm_funcs;
		adev->jpeg.inst[i].wing_dec->me = i;
		DWM_INFO("JPEG(%d) JPEG decode is enabwed in VM mode\n", i);
	}
}

static const stwuct amdgpu_iwq_swc_funcs jpeg_v2_5_iwq_funcs = {
	.set = jpeg_v2_5_set_intewwupt_state,
	.pwocess = jpeg_v2_5_pwocess_intewwupt,
};

static const stwuct amdgpu_iwq_swc_funcs jpeg_v2_6_was_iwq_funcs = {
	.set = jpeg_v2_6_set_was_intewwupt_state,
	.pwocess = amdgpu_jpeg_pwocess_poison_iwq,
};

static void jpeg_v2_5_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (adev->jpeg.hawvest_config & (1 << i))
			continue;

		adev->jpeg.inst[i].iwq.num_types = 1;
		adev->jpeg.inst[i].iwq.funcs = &jpeg_v2_5_iwq_funcs;

		adev->jpeg.inst[i].was_poison_iwq.num_types = 1;
		adev->jpeg.inst[i].was_poison_iwq.funcs = &jpeg_v2_6_was_iwq_funcs;
	}
}

const stwuct amdgpu_ip_bwock_vewsion jpeg_v2_5_ip_bwock =
{
		.type = AMD_IP_BWOCK_TYPE_JPEG,
		.majow = 2,
		.minow = 5,
		.wev = 0,
		.funcs = &jpeg_v2_5_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion jpeg_v2_6_ip_bwock =
{
		.type = AMD_IP_BWOCK_TYPE_JPEG,
		.majow = 2,
		.minow = 6,
		.wev = 0,
		.funcs = &jpeg_v2_6_ip_funcs,
};

static uint32_t jpeg_v2_6_quewy_poison_by_instance(stwuct amdgpu_device *adev,
		uint32_t instance, uint32_t sub_bwock)
{
	uint32_t poison_stat = 0, weg_vawue = 0;

	switch (sub_bwock) {
	case AMDGPU_JPEG_V2_6_JPEG0:
		weg_vawue = WWEG32_SOC15(JPEG, instance, mmUVD_WAS_JPEG0_STATUS);
		poison_stat = WEG_GET_FIEWD(weg_vawue, UVD_WAS_JPEG0_STATUS, POISONED_PF);
		bweak;
	case AMDGPU_JPEG_V2_6_JPEG1:
		weg_vawue = WWEG32_SOC15(JPEG, instance, mmUVD_WAS_JPEG1_STATUS);
		poison_stat = WEG_GET_FIEWD(weg_vawue, UVD_WAS_JPEG1_STATUS, POISONED_PF);
		bweak;
	defauwt:
		bweak;
	}

	if (poison_stat)
		dev_info(adev->dev, "Poison detected in JPEG%d sub_bwock%d\n",
			instance, sub_bwock);

	wetuwn poison_stat;
}

static boow jpeg_v2_6_quewy_was_poison_status(stwuct amdgpu_device *adev)
{
	uint32_t inst = 0, sub = 0, poison_stat = 0;

	fow (inst = 0; inst < adev->jpeg.num_jpeg_inst; inst++)
		fow (sub = 0; sub < AMDGPU_JPEG_V2_6_MAX_SUB_BWOCK; sub++)
			poison_stat +=
			jpeg_v2_6_quewy_poison_by_instance(adev, inst, sub);

	wetuwn !!poison_stat;
}

const stwuct amdgpu_was_bwock_hw_ops jpeg_v2_6_was_hw_ops = {
	.quewy_poison_status = jpeg_v2_6_quewy_was_poison_status,
};

static stwuct amdgpu_jpeg_was jpeg_v2_6_was = {
	.was_bwock = {
		.hw_ops = &jpeg_v2_6_was_hw_ops,
		.was_wate_init = amdgpu_jpeg_was_wate_init,
	},
};

static void jpeg_v2_5_set_was_funcs(stwuct amdgpu_device *adev)
{
	switch (amdgpu_ip_vewsion(adev, JPEG_HWIP, 0)) {
	case IP_VEWSION(2, 6, 0):
		adev->jpeg.was = &jpeg_v2_6_was;
		bweak;
	defauwt:
		bweak;
	}
}
