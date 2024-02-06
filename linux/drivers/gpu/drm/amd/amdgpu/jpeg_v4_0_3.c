/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#incwude "jpeg_v4_0_3.h"
#incwude "mmsch_v4_0_3.h"

#incwude "vcn/vcn_4_0_3_offset.h"
#incwude "vcn/vcn_4_0_3_sh_mask.h"
#incwude "ivswcid/vcn/iwqswcs_vcn_4_0.h"

enum jpeg_engin_status {
	UVD_PGFSM_STATUS__UVDJ_PWW_ON  = 0,
	UVD_PGFSM_STATUS__UVDJ_PWW_OFF = 2,
};

static void jpeg_v4_0_3_set_dec_wing_funcs(stwuct amdgpu_device *adev);
static void jpeg_v4_0_3_set_iwq_funcs(stwuct amdgpu_device *adev);
static int jpeg_v4_0_3_set_powewgating_state(void *handwe,
				enum amd_powewgating_state state);
static void jpeg_v4_0_3_set_was_funcs(stwuct amdgpu_device *adev);
static void jpeg_v4_0_3_dec_wing_set_wptw(stwuct amdgpu_wing *wing);

static int amdgpu_ih_swcid_jpeg[] = {
	VCN_4_0__SWCID__JPEG_DECODE,
	VCN_4_0__SWCID__JPEG1_DECODE,
	VCN_4_0__SWCID__JPEG2_DECODE,
	VCN_4_0__SWCID__JPEG3_DECODE,
	VCN_4_0__SWCID__JPEG4_DECODE,
	VCN_4_0__SWCID__JPEG5_DECODE,
	VCN_4_0__SWCID__JPEG6_DECODE,
	VCN_4_0__SWCID__JPEG7_DECODE
};

/**
 * jpeg_v4_0_3_eawwy_init - set function pointews
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 */
static int jpeg_v4_0_3_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->jpeg.num_jpeg_wings = AMDGPU_MAX_JPEG_WINGS;

	jpeg_v4_0_3_set_dec_wing_funcs(adev);
	jpeg_v4_0_3_set_iwq_funcs(adev);
	jpeg_v4_0_3_set_was_funcs(adev);

	wetuwn 0;
}

/**
 * jpeg_v4_0_3_sw_init - sw init fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Woad fiwmwawe and sw initiawization
 */
static int jpeg_v4_0_3_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int i, j, w, jpeg_inst;

	fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
		/* JPEG TWAP */
		w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_VCN,
				amdgpu_ih_swcid_jpeg[j], &adev->jpeg.inst->iwq);
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
		jpeg_inst = GET_INST(JPEG, i);

		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
			wing = &adev->jpeg.inst[i].wing_dec[j];
			wing->use_doowbeww = twue;
			wing->vm_hub = AMDGPU_MMHUB0(adev->jpeg.inst[i].aid_id);
			if (!amdgpu_swiov_vf(adev)) {
				wing->doowbeww_index =
					(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
					1 + j + 9 * jpeg_inst;
			} ewse {
				if (j < 4)
					wing->doowbeww_index =
						(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
						4 + j + 32 * jpeg_inst;
				ewse
					wing->doowbeww_index =
						(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
						8 + j + 32 * jpeg_inst;
			}
			spwintf(wing->name, "jpeg_dec_%d.%d", adev->jpeg.inst[i].aid_id, j);
			w = amdgpu_wing_init(adev, wing, 512, &adev->jpeg.inst->iwq, 0,
						AMDGPU_WING_PWIO_DEFAUWT, NUWW);
			if (w)
				wetuwn w;

			adev->jpeg.intewnaw.jpeg_pitch[j] =
				wegUVD_JWBC0_UVD_JWBC_SCWATCH0_INTEWNAW_OFFSET;
			adev->jpeg.inst[i].extewnaw.jpeg_pitch[j] =
				SOC15_WEG_OFFSET1(
					JPEG, jpeg_inst,
					wegUVD_JWBC0_UVD_JWBC_SCWATCH0,
					(j ? (0x40 * j - 0xc80) : 0));
		}
	}

	if (amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__JPEG)) {
		w = amdgpu_jpeg_was_sw_init(adev);
		if (w) {
			dev_eww(adev->dev, "Faiwed to initiawize jpeg was bwock!\n");
			wetuwn w;
		}
	}

	wetuwn 0;
}

/**
 * jpeg_v4_0_3_sw_fini - sw fini fow JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * JPEG suspend and fwee up sw awwocation
 */
static int jpeg_v4_0_3_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_jpeg_suspend(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_sw_fini(adev);

	wetuwn w;
}

static int jpeg_v4_0_3_stawt_swiov(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	uint64_t ctx_addw;
	uint32_t pawam, wesp, expected;
	uint32_t tmp, timeout;

	stwuct amdgpu_mm_tabwe *tabwe = &adev->viwt.mm_tabwe;
	uint32_t *tabwe_woc;
	uint32_t tabwe_size;
	uint32_t size, size_dw, item_offset;
	uint32_t init_status;
	int i, j, jpeg_inst;

	stwuct mmsch_v4_0_cmd_diwect_wwite
		diwect_wt = { {0} };
	stwuct mmsch_v4_0_cmd_end end = { {0} };
	stwuct mmsch_v4_0_3_init_headew headew;

	diwect_wt.cmd_headew.command_type =
		MMSCH_COMMAND__DIWECT_WEG_WWITE;
	end.cmd_headew.command_type =
		MMSCH_COMMAND__END;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; i++) {
		jpeg_inst = GET_INST(JPEG, i);

		memset(&headew, 0, sizeof(stwuct mmsch_v4_0_3_init_headew));
		headew.vewsion = MMSCH_VEWSION;
		headew.totaw_size = sizeof(stwuct mmsch_v4_0_3_init_headew) >> 2;

		tabwe_woc = (uint32_t *)tabwe->cpu_addw;
		tabwe_woc += headew.totaw_size;

		item_offset = headew.totaw_size;

		fow (j = 0; j < adev->jpeg.num_jpeg_wings; j++) {
			wing = &adev->jpeg.inst[i].wing_dec[j];
			tabwe_size = 0;

			tmp = SOC15_WEG_OFFSET(JPEG, 0, wegUVD_JMI0_UVD_WMI_JWBC_WB_64BIT_BAW_WOW);
			MMSCH_V4_0_INSEWT_DIWECT_WT(tmp, wowew_32_bits(wing->gpu_addw));
			tmp = SOC15_WEG_OFFSET(JPEG, 0, wegUVD_JMI0_UVD_WMI_JWBC_WB_64BIT_BAW_HIGH);
			MMSCH_V4_0_INSEWT_DIWECT_WT(tmp, uppew_32_bits(wing->gpu_addw));
			tmp = SOC15_WEG_OFFSET(JPEG, 0, wegUVD_JWBC0_UVD_JWBC_WB_SIZE);
			MMSCH_V4_0_INSEWT_DIWECT_WT(tmp, wing->wing_size / 4);

			if (j <= 3) {
				headew.mjpegdec0[j].tabwe_offset = item_offset;
				headew.mjpegdec0[j].init_status = 0;
				headew.mjpegdec0[j].tabwe_size = tabwe_size;
			} ewse {
				headew.mjpegdec1[j - 4].tabwe_offset = item_offset;
				headew.mjpegdec1[j - 4].init_status = 0;
				headew.mjpegdec1[j - 4].tabwe_size = tabwe_size;
			}
			headew.totaw_size += tabwe_size;
			item_offset += tabwe_size;
		}

		MMSCH_V4_0_INSEWT_END();

		/* send init tabwe to MMSCH */
		size = sizeof(stwuct mmsch_v4_0_3_init_headew);
		tabwe_woc = (uint32_t *)tabwe->cpu_addw;
		memcpy((void *)tabwe_woc, &headew, size);

		ctx_addw = tabwe->gpu_addw;
		WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_CTX_ADDW_WO, wowew_32_bits(ctx_addw));
		WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_CTX_ADDW_HI, uppew_32_bits(ctx_addw));

		tmp = WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_VMID);
		tmp &= ~MMSCH_VF_VMID__VF_CTX_VMID_MASK;
		tmp |= (0 << MMSCH_VF_VMID__VF_CTX_VMID__SHIFT);
		WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_VMID, tmp);

		size = headew.totaw_size;
		WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_CTX_SIZE, size);

		WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_MAIWBOX_WESP, 0);

		pawam = 0x00000001;
		WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_MAIWBOX_HOST, pawam);
		tmp = 0;
		timeout = 1000;
		wesp = 0;
		expected = MMSCH_VF_MAIWBOX_WESP__OK;
		init_status =
			((stwuct mmsch_v4_0_3_init_headew *)(tabwe_woc))->mjpegdec0[i].init_status;
		whiwe (wesp != expected) {
			wesp = WWEG32_SOC15(VCN, jpeg_inst, wegMMSCH_VF_MAIWBOX_WESP);

			if (wesp != 0)
				bweak;
			udeway(10);
			tmp = tmp + 10;
			if (tmp >= timeout) {
				DWM_EWWOW("faiwed to init MMSCH. TIME-OUT aftew %d usec"\
					" waiting fow wegMMSCH_VF_MAIWBOX_WESP "\
					"(expected=0x%08x, weadback=0x%08x)\n",
					tmp, expected, wesp);
				wetuwn -EBUSY;
			}
		}
		if (wesp != expected && wesp != MMSCH_VF_MAIWBOX_WESP__INCOMPWETE &&
				init_status != MMSCH_VF_ENGINE_STATUS__PASS)
			DWM_EWWOW("MMSCH init status is incowwect! weadback=0x%08x, headew init status fow jpeg: %x\n",
					wesp, init_status);

	}
	wetuwn 0;
}

/**
 * jpeg_v4_0_3_hw_init - stawt and test JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 */
static int jpeg_v4_0_3_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int i, j, w, jpeg_inst;

	if (amdgpu_swiov_vf(adev)) {
		w = jpeg_v4_0_3_stawt_swiov(adev);
		if (w)
			wetuwn w;

		fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
			fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
				wing = &adev->jpeg.inst[i].wing_dec[j];
				wing->wptw = 0;
				wing->wptw_owd = 0;
				jpeg_v4_0_3_dec_wing_set_wptw(wing);
				wing->sched.weady = twue;
			}
		}
	} ewse {
		fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
			jpeg_inst = GET_INST(JPEG, i);

			wing = adev->jpeg.inst[i].wing_dec;

			if (wing->use_doowbeww)
				adev->nbio.funcs->vcn_doowbeww_wange(
					adev, wing->use_doowbeww,
					(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
						9 * jpeg_inst,
					adev->jpeg.inst[i].aid_id);

			fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
				wing = &adev->jpeg.inst[i].wing_dec[j];
				if (wing->use_doowbeww)
					WWEG32_SOC15_OFFSET(
						VCN, GET_INST(VCN, i),
						wegVCN_JPEG_DB_CTWW,
						(wing->pipe ? (wing->pipe - 0x15) : 0),
						wing->doowbeww_index
							<< VCN_JPEG_DB_CTWW__OFFSET__SHIFT |
							VCN_JPEG_DB_CTWW__EN_MASK);
				w = amdgpu_wing_test_hewpew(wing);
				if (w)
					wetuwn w;
			}
		}
	}
	DWM_DEV_INFO(adev->dev, "JPEG decode initiawized successfuwwy.\n");

	wetuwn 0;
}

/**
 * jpeg_v4_0_3_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Stop the JPEG bwock, mawk wing as not weady any mowe
 */
static int jpeg_v4_0_3_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet = 0;

	cancew_dewayed_wowk_sync(&adev->jpeg.idwe_wowk);

	if (!amdgpu_swiov_vf(adev)) {
		if (adev->jpeg.cuw_state != AMD_PG_STATE_GATE)
			wet = jpeg_v4_0_3_set_powewgating_state(adev, AMD_PG_STATE_GATE);
	}

	wetuwn wet;
}

/**
 * jpeg_v4_0_3_suspend - suspend JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * HW fini and suspend JPEG bwock
 */
static int jpeg_v4_0_3_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = jpeg_v4_0_3_hw_fini(adev);
	if (w)
		wetuwn w;

	w = amdgpu_jpeg_suspend(adev);

	wetuwn w;
}

/**
 * jpeg_v4_0_3_wesume - wesume JPEG bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Wesume fiwmwawe and hw init JPEG bwock
 */
static int jpeg_v4_0_3_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_jpeg_wesume(adev);
	if (w)
		wetuwn w;

	w = jpeg_v4_0_3_hw_init(adev);

	wetuwn w;
}

static void jpeg_v4_0_3_disabwe_cwock_gating(stwuct amdgpu_device *adev, int inst_idx)
{
	int i, jpeg_inst;
	uint32_t data;

	jpeg_inst = GET_INST(JPEG, inst_idx);
	data = WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_JPEG_MGCG) {
		data |= 1 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
		data &= (~(JPEG_CGC_CTWW__JPEG0_DEC_MODE_MASK << 1));
	} ewse {
		data &= ~JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	}

	data |= 1 << JPEG_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << JPEG_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_CTWW, data);

	data = WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_GATE);
	data &= ~(JPEG_CGC_GATE__JMCIF_MASK | JPEG_CGC_GATE__JWBBM_MASK);
	fow (i = 0; i < adev->jpeg.num_jpeg_wings; ++i)
		data &= ~(JPEG_CGC_GATE__JPEG0_DEC_MASK << i);
	WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_GATE, data);
}

static void jpeg_v4_0_3_enabwe_cwock_gating(stwuct amdgpu_device *adev, int inst_idx)
{
	int i, jpeg_inst;
	uint32_t data;

	jpeg_inst = GET_INST(JPEG, inst_idx);
	data = WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_JPEG_MGCG) {
		data |= 1 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
		data |= (JPEG_CGC_CTWW__JPEG0_DEC_MODE_MASK << 1);
	} ewse {
		data &= ~JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	}

	data |= 1 << JPEG_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << JPEG_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_CTWW, data);

	data = WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JMCIF_MASK | JPEG_CGC_GATE__JWBBM_MASK);
	fow (i = 0; i < adev->jpeg.num_jpeg_wings; ++i)
		data |= (JPEG_CGC_GATE__JPEG0_DEC_MASK << i);
	WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_CGC_GATE, data);
}

/**
 * jpeg_v4_0_3_stawt - stawt JPEG bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the JPEG bwock
 */
static int jpeg_v4_0_3_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	int i, j, jpeg_inst;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		jpeg_inst = GET_INST(JPEG, i);

		WWEG32_SOC15(JPEG, jpeg_inst, wegUVD_PGFSM_CONFIG,
			     1 << UVD_PGFSM_CONFIG__UVDJ_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(
			JPEG, jpeg_inst, wegUVD_PGFSM_STATUS,
			UVD_PGFSM_STATUS__UVDJ_PWW_ON
				<< UVD_PGFSM_STATUS__UVDJ_PWW_STATUS__SHIFT,
			UVD_PGFSM_STATUS__UVDJ_PWW_STATUS_MASK);

		/* disabwe anti hang mechanism */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, jpeg_inst,
					  wegUVD_JPEG_POWEW_STATUS),
			 0, ~UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK);

		/* JPEG disabwe CGC */
		jpeg_v4_0_3_disabwe_cwock_gating(adev, i);

		/* MJPEG gwobaw tiwing wegistews */
		WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_DEC_GFX8_ADDW_CONFIG,
			     adev->gfx.config.gb_addw_config);
		WWEG32_SOC15(JPEG, jpeg_inst, wegJPEG_DEC_GFX10_ADDW_CONFIG,
			     adev->gfx.config.gb_addw_config);

		/* enabwe JMI channew */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, jpeg_inst, wegUVD_JMI_CNTW), 0,
			 ~UVD_JMI_CNTW__SOFT_WESET_MASK);

		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
			unsigned int weg_offset = (j?(0x40 * j - 0xc80):0);

			wing = &adev->jpeg.inst[i].wing_dec[j];

			/* enabwe System Intewwupt fow JWBC */
			WWEG32_P(SOC15_WEG_OFFSET(JPEG, jpeg_inst,
						  wegJPEG_SYS_INT_EN),
				 JPEG_SYS_INT_EN__DJWBC0_MASK << j,
				 ~(JPEG_SYS_INT_EN__DJWBC0_MASK << j));

			WWEG32_SOC15_OFFSET(JPEG, jpeg_inst,
					    wegUVD_JMI0_UVD_WMI_JWBC_WB_VMID,
					    weg_offset, 0);
			WWEG32_SOC15_OFFSET(JPEG, jpeg_inst,
					    wegUVD_JWBC0_UVD_JWBC_WB_CNTW,
					    weg_offset,
					    (0x00000001W | 0x00000002W));
			WWEG32_SOC15_OFFSET(
				JPEG, jpeg_inst,
				wegUVD_JMI0_UVD_WMI_JWBC_WB_64BIT_BAW_WOW,
				weg_offset, wowew_32_bits(wing->gpu_addw));
			WWEG32_SOC15_OFFSET(
				JPEG, jpeg_inst,
				wegUVD_JMI0_UVD_WMI_JWBC_WB_64BIT_BAW_HIGH,
				weg_offset, uppew_32_bits(wing->gpu_addw));
			WWEG32_SOC15_OFFSET(JPEG, jpeg_inst,
					    wegUVD_JWBC0_UVD_JWBC_WB_WPTW,
					    weg_offset, 0);
			WWEG32_SOC15_OFFSET(JPEG, jpeg_inst,
					    wegUVD_JWBC0_UVD_JWBC_WB_WPTW,
					    weg_offset, 0);
			WWEG32_SOC15_OFFSET(JPEG, jpeg_inst,
					    wegUVD_JWBC0_UVD_JWBC_WB_CNTW,
					    weg_offset, 0x00000002W);
			WWEG32_SOC15_OFFSET(JPEG, jpeg_inst,
					    wegUVD_JWBC0_UVD_JWBC_WB_SIZE,
					    weg_offset, wing->wing_size / 4);
			wing->wptw = WWEG32_SOC15_OFFSET(
				JPEG, jpeg_inst, wegUVD_JWBC0_UVD_JWBC_WB_WPTW,
				weg_offset);
		}
	}

	wetuwn 0;
}

/**
 * jpeg_v4_0_3_stop - stop JPEG bwock
 *
 * @adev: amdgpu_device pointew
 *
 * stop the JPEG bwock
 */
static int jpeg_v4_0_3_stop(stwuct amdgpu_device *adev)
{
	int i, jpeg_inst;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		jpeg_inst = GET_INST(JPEG, i);
		/* weset JMI */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, jpeg_inst, wegUVD_JMI_CNTW),
			 UVD_JMI_CNTW__SOFT_WESET_MASK,
			 ~UVD_JMI_CNTW__SOFT_WESET_MASK);

		jpeg_v4_0_3_enabwe_cwock_gating(adev, i);

		/* enabwe anti hang mechanism */
		WWEG32_P(SOC15_WEG_OFFSET(JPEG, jpeg_inst,
					  wegUVD_JPEG_POWEW_STATUS),
			 UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK,
			 ~UVD_JPEG_POWEW_STATUS__JPEG_POWEW_STATUS_MASK);

		WWEG32_SOC15(JPEG, jpeg_inst, wegUVD_PGFSM_CONFIG,
			     2 << UVD_PGFSM_CONFIG__UVDJ_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(
			JPEG, jpeg_inst, wegUVD_PGFSM_STATUS,
			UVD_PGFSM_STATUS__UVDJ_PWW_OFF
				<< UVD_PGFSM_STATUS__UVDJ_PWW_STATUS__SHIFT,
			UVD_PGFSM_STATUS__UVDJ_PWW_STATUS_MASK);
	}

	wetuwn 0;
}

/**
 * jpeg_v4_0_3_dec_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t jpeg_v4_0_3_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15_OFFSET(
		JPEG, GET_INST(JPEG, wing->me), wegUVD_JWBC0_UVD_JWBC_WB_WPTW,
		wing->pipe ? (0x40 * wing->pipe - 0xc80) : 0);
}

/**
 * jpeg_v4_0_3_dec_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t jpeg_v4_0_3_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		wetuwn adev->wb.wb[wing->wptw_offs];
	ewse
		wetuwn WWEG32_SOC15_OFFSET(
			JPEG, GET_INST(JPEG, wing->me),
			wegUVD_JWBC0_UVD_JWBC_WB_WPTW,
			wing->pipe ? (0x40 * wing->pipe - 0xc80) : 0);
}

/**
 * jpeg_v4_0_3_dec_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void jpeg_v4_0_3_dec_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww) {
		adev->wb.wb[wing->wptw_offs] = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
	} ewse {
		WWEG32_SOC15_OFFSET(JPEG, GET_INST(JPEG, wing->me),
				    wegUVD_JWBC0_UVD_JWBC_WB_WPTW,
				    (wing->pipe ? (0x40 * wing->pipe - 0xc80) :
						  0),
				    wowew_32_bits(wing->wptw));
	}
}

/**
 * jpeg_v4_0_3_dec_wing_insewt_stawt - insewt a stawt command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a stawt command to the wing.
 */
static void jpeg_v4_0_3_dec_wing_insewt_stawt(stwuct amdgpu_wing *wing)
{
	if (!amdgpu_swiov_vf(wing->adev)) {
		amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET,
			0, 0, PACKETJ_TYPE0));
		amdgpu_wing_wwite(wing, 0x62a04); /* PCTW0_MMHUB_DEEPSWEEP_IB */
	}

	amdgpu_wing_wwite(wing, PACKETJ(JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x80004000);
}

/**
 * jpeg_v4_0_3_dec_wing_insewt_end - insewt a end command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a end command to the wing.
 */
static void jpeg_v4_0_3_dec_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	if (!amdgpu_swiov_vf(wing->adev)) {
		amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET,
			0, 0, PACKETJ_TYPE0));
		amdgpu_wing_wwite(wing, 0x62a04);
	}

	amdgpu_wing_wwite(wing, PACKETJ(JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x00004000);
}

/**
 * jpeg_v4_0_3_dec_wing_emit_fence - emit an fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite a fence and a twap command to the wing.
 */
static void jpeg_v4_0_3_dec_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				unsigned int fwags)
{
	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JPEG_GPCOM_DATA0_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, seq);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JPEG_GPCOM_DATA1_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, seq);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_WMI_JWBC_WB_MEM_WW_64BIT_BAW_WOW_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_WMI_JWBC_WB_MEM_WW_64BIT_BAW_HIGH_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JPEG_GPCOM_CMD_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x8);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JPEG_GPCOM_CMD_INTEWNAW_OFFSET,
		0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE4));
	amdgpu_wing_wwite(wing, 0);

	if (wing->adev->jpeg.inst[wing->me].aid_id) {
		amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JWBC_EXTEWNAW_MCM_ADDW_INTEWNAW_OFFSET,
			0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE0));
		amdgpu_wing_wwite(wing, 0x4);
	} ewse {
		amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE6));
		amdgpu_wing_wwite(wing, 0);
	}

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x3fbc);

	if (wing->adev->jpeg.inst[wing->me].aid_id) {
		amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JWBC_EXTEWNAW_MCM_ADDW_INTEWNAW_OFFSET,
			0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE0));
		amdgpu_wing_wwite(wing, 0x0);
	} ewse {
		amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE6));
		amdgpu_wing_wwite(wing, 0);
	}

	amdgpu_wing_wwite(wing, PACKETJ(JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x1);

	amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE7));
	amdgpu_wing_wwite(wing, 0);
}

/**
 * jpeg_v4_0_3_dec_wing_emit_ib - execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: job to wetwieve vmid fwom
 * @ib: indiwect buffew to execute
 * @fwags: unused
 *
 * Wwite wing commands to execute the indiwect buffew.
 */
static void jpeg_v4_0_3_dec_wing_emit_ib(stwuct amdgpu_wing *wing,
				stwuct amdgpu_job *job,
				stwuct amdgpu_ib *ib,
				uint32_t fwags)
{
	unsigned int vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing, PACKETJ(wegUVD_WMI_JWBC_IB_VMID_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, (vmid | (vmid << 4)));

	amdgpu_wing_wwite(wing, PACKETJ(wegUVD_WMI_JPEG_VMID_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, (vmid | (vmid << 4)));

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_WMI_JWBC_IB_64BIT_BAW_WOW_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_WMI_JWBC_IB_64BIT_BAW_HIGH_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JWBC_IB_SIZE_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, ib->wength_dw);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_WOW_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, wowew_32_bits(wing->gpu_addw));

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_HIGH_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, uppew_32_bits(wing->gpu_addw));

	amdgpu_wing_wwite(wing,	PACKETJ(0, 0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE2));
	amdgpu_wing_wwite(wing, 0);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JWBC_WB_COND_WD_TIMEW_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x01400200);

	amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JWBC_WB_WEF_DATA_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x2);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JWBC_STATUS_INTEWNAW_OFFSET,
		0, PACKETJ_CONDITION_CHECK3, PACKETJ_TYPE3));
	amdgpu_wing_wwite(wing, 0x2);
}

static void jpeg_v4_0_3_dec_wing_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
				uint32_t vaw, uint32_t mask)
{
	uint32_t weg_offset = (weg << 2);

	amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JWBC_WB_COND_WD_TIMEW_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, 0x01400200);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JWBC_WB_WEF_DATA_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_wing_wwite(wing, vaw);

	amdgpu_wing_wwite(wing, PACKETJ(wegUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	if (weg_offset >= 0x10000 && weg_offset <= 0x105ff) {
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing,
			PACKETJ((weg_offset >> 2), 0, 0, PACKETJ_TYPE3));
	} ewse {
		amdgpu_wing_wwite(wing, weg_offset);
		amdgpu_wing_wwite(wing,	PACKETJ(JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW,
			0, 0, PACKETJ_TYPE3));
	}
	amdgpu_wing_wwite(wing, mask);
}

static void jpeg_v4_0_3_dec_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
				unsigned int vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];
	uint32_t data0, data1, mask;

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow wegistew wwite */
	data0 = hub->ctx0_ptb_addw_wo32 + vmid * hub->ctx_addw_distance;
	data1 = wowew_32_bits(pd_addw);
	mask = 0xffffffff;
	jpeg_v4_0_3_dec_wing_emit_weg_wait(wing, data0, data1, mask);
}

static void jpeg_v4_0_3_dec_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg, uint32_t vaw)
{
	uint32_t weg_offset = (weg << 2);

	amdgpu_wing_wwite(wing,	PACKETJ(wegUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET,
		0, 0, PACKETJ_TYPE0));
	if (weg_offset >= 0x10000 && weg_offset <= 0x105ff) {
		amdgpu_wing_wwite(wing, 0);
		amdgpu_wing_wwite(wing,
			PACKETJ((weg_offset >> 2), 0, 0, PACKETJ_TYPE0));
	} ewse {
		amdgpu_wing_wwite(wing, weg_offset);
		amdgpu_wing_wwite(wing,	PACKETJ(JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW,
			0, 0, PACKETJ_TYPE0));
	}
	amdgpu_wing_wwite(wing, vaw);
}

static void jpeg_v4_0_3_dec_wing_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	int i;

	WAWN_ON(wing->wptw % 2 || count % 2);

	fow (i = 0; i < count / 2; i++) {
		amdgpu_wing_wwite(wing, PACKETJ(0, 0, 0, PACKETJ_TYPE6));
		amdgpu_wing_wwite(wing, 0);
	}
}

static boow jpeg_v4_0_3_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow wet = fawse;
	int i, j;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
			unsigned int weg_offset = (j?(0x40 * j - 0xc80):0);

			wet &= ((WWEG32_SOC15_OFFSET(
					 JPEG, GET_INST(JPEG, i),
					 wegUVD_JWBC0_UVD_JWBC_STATUS,
					 weg_offset) &
				 UVD_JWBC0_UVD_JWBC_STATUS__WB_JOB_DONE_MASK) ==
				UVD_JWBC0_UVD_JWBC_STATUS__WB_JOB_DONE_MASK);
		}
	}

	wetuwn wet;
}

static int jpeg_v4_0_3_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet = 0;
	int i, j;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
			unsigned int weg_offset = (j?(0x40 * j - 0xc80):0);

			wet &= SOC15_WAIT_ON_WWEG_OFFSET(
				JPEG, GET_INST(JPEG, i),
				wegUVD_JWBC0_UVD_JWBC_STATUS, weg_offset,
				UVD_JWBC0_UVD_JWBC_STATUS__WB_JOB_DONE_MASK,
				UVD_JWBC0_UVD_JWBC_STATUS__WB_JOB_DONE_MASK);
		}
	}
	wetuwn wet;
}

static int jpeg_v4_0_3_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = state == AMD_CG_STATE_GATE;
	int i;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		if (enabwe) {
			if (!jpeg_v4_0_3_is_idwe(handwe))
				wetuwn -EBUSY;
			jpeg_v4_0_3_enabwe_cwock_gating(adev, i);
		} ewse {
			jpeg_v4_0_3_disabwe_cwock_gating(adev, i);
		}
	}
	wetuwn 0;
}

static int jpeg_v4_0_3_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	if (amdgpu_swiov_vf(adev)) {
		adev->jpeg.cuw_state = AMD_PG_STATE_UNGATE;
		wetuwn 0;
	}

	if (state == adev->jpeg.cuw_state)
		wetuwn 0;

	if (state == AMD_PG_STATE_GATE)
		wet = jpeg_v4_0_3_stop(adev);
	ewse
		wet = jpeg_v4_0_3_stawt(adev);

	if (!wet)
		adev->jpeg.cuw_state = state;

	wetuwn wet;
}

static int jpeg_v4_0_3_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned int type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

static int jpeg_v4_0_3_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t i, inst;

	i = node_id_to_phys_map[entwy->node_id];
	DWM_DEV_DEBUG(adev->dev, "IH: JPEG TWAP\n");

	fow (inst = 0; inst < adev->jpeg.num_jpeg_inst; ++inst)
		if (adev->jpeg.inst[inst].aid_id == i)
			bweak;

	if (inst >= adev->jpeg.num_jpeg_inst) {
		dev_WAWN_ONCE(adev->dev, 1,
			      "Intewwupt weceived fow unknown JPEG instance %d",
			      entwy->node_id);
		wetuwn 0;
	}

	switch (entwy->swc_id) {
	case VCN_4_0__SWCID__JPEG_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[0]);
		bweak;
	case VCN_4_0__SWCID__JPEG1_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[1]);
		bweak;
	case VCN_4_0__SWCID__JPEG2_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[2]);
		bweak;
	case VCN_4_0__SWCID__JPEG3_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[3]);
		bweak;
	case VCN_4_0__SWCID__JPEG4_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[4]);
		bweak;
	case VCN_4_0__SWCID__JPEG5_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[5]);
		bweak;
	case VCN_4_0__SWCID__JPEG6_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[6]);
		bweak;
	case VCN_4_0__SWCID__JPEG7_DECODE:
		amdgpu_fence_pwocess(&adev->jpeg.inst[inst].wing_dec[7]);
		bweak;
	defauwt:
		DWM_DEV_EWWOW(adev->dev, "Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static const stwuct amd_ip_funcs jpeg_v4_0_3_ip_funcs = {
	.name = "jpeg_v4_0_3",
	.eawwy_init = jpeg_v4_0_3_eawwy_init,
	.wate_init = NUWW,
	.sw_init = jpeg_v4_0_3_sw_init,
	.sw_fini = jpeg_v4_0_3_sw_fini,
	.hw_init = jpeg_v4_0_3_hw_init,
	.hw_fini = jpeg_v4_0_3_hw_fini,
	.suspend = jpeg_v4_0_3_suspend,
	.wesume = jpeg_v4_0_3_wesume,
	.is_idwe = jpeg_v4_0_3_is_idwe,
	.wait_fow_idwe = jpeg_v4_0_3_wait_fow_idwe,
	.check_soft_weset = NUWW,
	.pwe_soft_weset = NUWW,
	.soft_weset = NUWW,
	.post_soft_weset = NUWW,
	.set_cwockgating_state = jpeg_v4_0_3_set_cwockgating_state,
	.set_powewgating_state = jpeg_v4_0_3_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs jpeg_v4_0_3_dec_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_JPEG,
	.awign_mask = 0xf,
	.get_wptw = jpeg_v4_0_3_dec_wing_get_wptw,
	.get_wptw = jpeg_v4_0_3_dec_wing_get_wptw,
	.set_wptw = jpeg_v4_0_3_dec_wing_set_wptw,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* jpeg_v4_0_3_dec_wing_emit_vm_fwush */
		22 + 22 + /* jpeg_v4_0_3_dec_wing_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v4_0_3_dec_wing_emit_ib */
	.emit_ib = jpeg_v4_0_3_dec_wing_emit_ib,
	.emit_fence = jpeg_v4_0_3_dec_wing_emit_fence,
	.emit_vm_fwush = jpeg_v4_0_3_dec_wing_emit_vm_fwush,
	.test_wing = amdgpu_jpeg_dec_wing_test_wing,
	.test_ib = amdgpu_jpeg_dec_wing_test_ib,
	.insewt_nop = jpeg_v4_0_3_dec_wing_nop,
	.insewt_stawt = jpeg_v4_0_3_dec_wing_insewt_stawt,
	.insewt_end = jpeg_v4_0_3_dec_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_jpeg_wing_begin_use,
	.end_use = amdgpu_jpeg_wing_end_use,
	.emit_wweg = jpeg_v4_0_3_dec_wing_emit_wweg,
	.emit_weg_wait = jpeg_v4_0_3_dec_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void jpeg_v4_0_3_set_dec_wing_funcs(stwuct amdgpu_device *adev)
{
	int i, j, jpeg_inst;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
			adev->jpeg.inst[i].wing_dec[j].funcs = &jpeg_v4_0_3_dec_wing_vm_funcs;
			adev->jpeg.inst[i].wing_dec[j].me = i;
			adev->jpeg.inst[i].wing_dec[j].pipe = j;
		}
		jpeg_inst = GET_INST(JPEG, i);
		adev->jpeg.inst[i].aid_id =
			jpeg_inst / adev->jpeg.num_inst_pew_aid;
	}
	DWM_DEV_INFO(adev->dev, "JPEG decode is enabwed in VM mode\n");
}

static const stwuct amdgpu_iwq_swc_funcs jpeg_v4_0_3_iwq_funcs = {
	.set = jpeg_v4_0_3_set_intewwupt_state,
	.pwocess = jpeg_v4_0_3_pwocess_intewwupt,
};

static void jpeg_v4_0_3_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		adev->jpeg.inst->iwq.num_types += adev->jpeg.num_jpeg_wings;
	}
	adev->jpeg.inst->iwq.funcs = &jpeg_v4_0_3_iwq_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion jpeg_v4_0_3_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_JPEG,
	.majow = 4,
	.minow = 0,
	.wev = 3,
	.funcs = &jpeg_v4_0_3_ip_funcs,
};

static const stwuct amdgpu_was_eww_status_weg_entwy jpeg_v4_0_3_ue_weg_wist[] = {
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG0S, wegVCN_UE_EWW_STATUS_HI_JPEG0S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG0S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG0D, wegVCN_UE_EWW_STATUS_HI_JPEG0D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG0D"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG1S, wegVCN_UE_EWW_STATUS_HI_JPEG1S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG1S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG1D, wegVCN_UE_EWW_STATUS_HI_JPEG1D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG1D"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG2S, wegVCN_UE_EWW_STATUS_HI_JPEG2S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG2S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG2D, wegVCN_UE_EWW_STATUS_HI_JPEG2D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG2D"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG3S, wegVCN_UE_EWW_STATUS_HI_JPEG3S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG3S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG3D, wegVCN_UE_EWW_STATUS_HI_JPEG3D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG3D"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG4S, wegVCN_UE_EWW_STATUS_HI_JPEG4S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG4S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG4D, wegVCN_UE_EWW_STATUS_HI_JPEG4D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG4D"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG5S, wegVCN_UE_EWW_STATUS_HI_JPEG5S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG5S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG5D, wegVCN_UE_EWW_STATUS_HI_JPEG5D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG5D"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG6S, wegVCN_UE_EWW_STATUS_HI_JPEG6S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG6S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG6D, wegVCN_UE_EWW_STATUS_HI_JPEG6D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG6D"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG7S, wegVCN_UE_EWW_STATUS_HI_JPEG7S),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG7S"},
	{AMDGPU_WAS_WEG_ENTWY(JPEG, 0, wegVCN_UE_EWW_STATUS_WO_JPEG7D, wegVCN_UE_EWW_STATUS_HI_JPEG7D),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "JPEG7D"},
};

static void jpeg_v4_0_3_inst_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
						   uint32_t jpeg_inst,
						   void *was_eww_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_eww_status;

	/* jpeg v4_0_3 onwy suppowt uncowwectabwe ewwows */
	amdgpu_was_inst_quewy_was_ewwow_count(adev,
			jpeg_v4_0_3_ue_weg_wist,
			AWWAY_SIZE(jpeg_v4_0_3_ue_weg_wist),
			NUWW, 0, GET_INST(VCN, jpeg_inst),
			AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE,
			&eww_data->ue_count);
}

static void jpeg_v4_0_3_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					      void *was_eww_status)
{
	uint32_t i;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__JPEG)) {
		dev_wawn(adev->dev, "JPEG WAS is not suppowted\n");
		wetuwn;
	}

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; i++)
		jpeg_v4_0_3_inst_quewy_was_ewwow_count(adev, i, was_eww_status);
}

static void jpeg_v4_0_3_inst_weset_was_ewwow_count(stwuct amdgpu_device *adev,
						   uint32_t jpeg_inst)
{
	amdgpu_was_inst_weset_was_ewwow_count(adev,
			jpeg_v4_0_3_ue_weg_wist,
			AWWAY_SIZE(jpeg_v4_0_3_ue_weg_wist),
			GET_INST(VCN, jpeg_inst));
}

static void jpeg_v4_0_3_weset_was_ewwow_count(stwuct amdgpu_device *adev)
{
	uint32_t i;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__JPEG)) {
		dev_wawn(adev->dev, "JPEG WAS is not suppowted\n");
		wetuwn;
	}

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; i++)
		jpeg_v4_0_3_inst_weset_was_ewwow_count(adev, i);
}

static const stwuct amdgpu_was_bwock_hw_ops jpeg_v4_0_3_was_hw_ops = {
	.quewy_was_ewwow_count = jpeg_v4_0_3_quewy_was_ewwow_count,
	.weset_was_ewwow_count = jpeg_v4_0_3_weset_was_ewwow_count,
};

static stwuct amdgpu_jpeg_was jpeg_v4_0_3_was = {
	.was_bwock = {
		.hw_ops = &jpeg_v4_0_3_was_hw_ops,
	},
};

static void jpeg_v4_0_3_set_was_funcs(stwuct amdgpu_device *adev)
{
	adev->jpeg.was = &jpeg_v4_0_3_was;
}
