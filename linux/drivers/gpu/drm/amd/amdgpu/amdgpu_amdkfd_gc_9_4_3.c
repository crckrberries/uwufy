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
 */
#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_amdkfd_gfx_v9.h"
#incwude "amdgpu_amdkfd_awdebawan.h"
#incwude "gc/gc_9_4_3_offset.h"
#incwude "gc/gc_9_4_3_sh_mask.h"
#incwude "athub/athub_1_8_0_offset.h"
#incwude "athub/athub_1_8_0_sh_mask.h"
#incwude "oss/osssys_4_4_2_offset.h"
#incwude "oss/osssys_4_4_2_sh_mask.h"
#incwude "v9_stwucts.h"
#incwude "soc15.h"
#incwude "sdma/sdma_4_4_2_offset.h"
#incwude "sdma/sdma_4_4_2_sh_mask.h"
#incwude <uapi/winux/kfd_ioctw.h>

static inwine stwuct v9_sdma_mqd *get_sdma_mqd(void *mqd)
{
	wetuwn (stwuct v9_sdma_mqd *)mqd;
}

static uint32_t get_sdma_wwc_weg_offset(stwuct amdgpu_device *adev,
					unsigned int engine_id,
					unsigned int queue_id)
{
	uint32_t sdma_engine_weg_base =
		SOC15_WEG_OFFSET(SDMA0, GET_INST(SDMA0, engine_id),
				 wegSDMA_WWC0_WB_CNTW) -
		wegSDMA_WWC0_WB_CNTW;
	uint32_t wetvaw = sdma_engine_weg_base +
		  queue_id * (wegSDMA_WWC1_WB_CNTW - wegSDMA_WWC0_WB_CNTW);

	pw_debug("WWC wegistew offset fow SDMA%d WWC%d: 0x%x\n", engine_id,
							queue_id, wetvaw);
	wetuwn wetvaw;
}

static int kgd_gfx_v9_4_3_hqd_sdma_woad(stwuct amdgpu_device *adev, void *mqd,
				 uint32_t __usew *wptw, stwuct mm_stwuct *mm)
{
	stwuct v9_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	unsigned wong end_jiffies;
	uint32_t data;
	uint64_t data64;
	uint64_t __usew *wptw64 = (uint64_t __usew *)wptw;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
							m->sdma_queue_id);

	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_CNTW,
		m->sdmax_wwcx_wb_cntw & (~SDMA_WWC0_WB_CNTW__WB_ENABWE_MASK));

	end_jiffies = msecs_to_jiffies(2000) + jiffies;
	whiwe (twue) {
		data = WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_CONTEXT_STATUS);
		if (data & SDMA_WWC0_CONTEXT_STATUS__IDWE_MASK)
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("SDMA WWC not idwe in %s\n", __func__);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_DOOWBEWW_OFFSET,
		m->sdmax_wwcx_doowbeww_offset);

	data = WEG_SET_FIEWD(m->sdmax_wwcx_doowbeww, SDMA_WWC0_DOOWBEWW,
				ENABWE, 1);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_DOOWBEWW, data);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW,
					m->sdmax_wwcx_wb_wptw);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW_HI,
					m->sdmax_wwcx_wb_wptw_hi);

	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_MINOW_PTW_UPDATE, 1);
	if (wead_usew_wptw(mm, wptw64, data64)) {
		WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW,
			wowew_32_bits(data64));
		WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW_HI,
			uppew_32_bits(data64));
	} ewse {
		WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW,
			m->sdmax_wwcx_wb_wptw);
		WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW_HI,
			m->sdmax_wwcx_wb_wptw_hi);
	}
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_MINOW_PTW_UPDATE, 0);

	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_BASE, m->sdmax_wwcx_wb_base);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_BASE_HI,
			m->sdmax_wwcx_wb_base_hi);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW_ADDW_WO,
			m->sdmax_wwcx_wb_wptw_addw_wo);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW_ADDW_HI,
			m->sdmax_wwcx_wb_wptw_addw_hi);

	data = WEG_SET_FIEWD(m->sdmax_wwcx_wb_cntw, SDMA_WWC0_WB_CNTW,
				WB_ENABWE, 1);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_CNTW, data);

	wetuwn 0;
}

static int kgd_gfx_v9_4_3_hqd_sdma_dump(stwuct amdgpu_device *adev,
				 uint32_t engine_id, uint32_t queue_id,
				 uint32_t (**dump)[2], uint32_t *n_wegs)
{
	uint32_t sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev,
							engine_id, queue_id);
	uint32_t i = 0, weg;
#undef HQD_N_WEGS
#define HQD_N_WEGS (19+6+7+12)
#define DUMP_WEG(addw) do {				\
		if (WAWN_ON_ONCE(i >= HQD_N_WEGS))      \
			bweak;				\
		(*dump)[i][0] = (addw) << 2;            \
		(*dump)[i++][1] = WWEG32(addw);         \
	} whiwe (0)

	*dump = kmawwoc_awway(HQD_N_WEGS, sizeof(**dump), GFP_KEWNEW);
	if (*dump == NUWW)
		wetuwn -ENOMEM;

	fow (weg = wegSDMA_WWC0_WB_CNTW; weg <= wegSDMA_WWC0_DOOWBEWW; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = wegSDMA_WWC0_STATUS; weg <= wegSDMA_WWC0_CSA_ADDW_HI; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = wegSDMA_WWC0_IB_SUB_WEMAIN;
	     weg <= wegSDMA_WWC0_MINOW_PTW_UPDATE; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);
	fow (weg = wegSDMA_WWC0_MIDCMD_DATA0;
	     weg <= wegSDMA_WWC0_MIDCMD_CNTW; weg++)
		DUMP_WEG(sdma_wwc_weg_offset + weg);

	WAWN_ON_ONCE(i != HQD_N_WEGS);
	*n_wegs = i;

	wetuwn 0;
}

static boow kgd_gfx_v9_4_3_hqd_sdma_is_occupied(stwuct amdgpu_device *adev, void *mqd)
{
	stwuct v9_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t sdma_wwc_wb_cntw;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
							m->sdma_queue_id);

	sdma_wwc_wb_cntw = WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_CNTW);

	if (sdma_wwc_wb_cntw & SDMA_WWC0_WB_CNTW__WB_ENABWE_MASK)
		wetuwn twue;

	wetuwn fawse;
}

static int kgd_gfx_v9_4_3_hqd_sdma_destwoy(stwuct amdgpu_device *adev, void *mqd,
				    unsigned int utimeout)
{
	stwuct v9_sdma_mqd *m;
	uint32_t sdma_wwc_weg_offset;
	uint32_t temp;
	unsigned wong end_jiffies = (utimeout * HZ / 1000) + jiffies;

	m = get_sdma_mqd(mqd);
	sdma_wwc_weg_offset = get_sdma_wwc_weg_offset(adev, m->sdma_engine_id,
							m->sdma_queue_id);

	temp = WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_CNTW);
	temp = temp & ~SDMA_WWC0_WB_CNTW__WB_ENABWE_MASK;
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_CNTW, temp);

	whiwe (twue) {
		temp = WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_CONTEXT_STATUS);
		if (temp & SDMA_WWC0_CONTEXT_STATUS__IDWE_MASK)
			bweak;
		if (time_aftew(jiffies, end_jiffies)) {
			pw_eww("SDMA WWC not idwe in %s\n", __func__);
			wetuwn -ETIME;
		}
		usweep_wange(500, 1000);
	}

	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_DOOWBEWW, 0);
	WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_CNTW,
		WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_CNTW) |
		SDMA_WWC0_WB_CNTW__WB_ENABWE_MASK);

	m->sdmax_wwcx_wb_wptw =
			WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW);
	m->sdmax_wwcx_wb_wptw_hi =
			WWEG32(sdma_wwc_weg_offset + wegSDMA_WWC0_WB_WPTW_HI);

	wetuwn 0;
}

static int kgd_gfx_v9_4_3_set_pasid_vmid_mapping(stwuct amdgpu_device *adev,
			u32 pasid, unsigned int vmid, uint32_t xcc_inst)
{
	unsigned wong timeout;
	unsigned int weg;
	unsigned int phy_inst = GET_INST(GC, xcc_inst);
	/* Evewy two XCCs shawe one AID */
	unsigned int aid = phy_inst / 2;

	/*
	 * We have to assume that thewe is no outstanding mapping.
	 * The ATC_VMID_PASID_MAPPING_UPDATE_STATUS bit couwd be 0 because
	 * a mapping is in pwogwess ow because a mapping finished
	 * and the SW cweawed it.
	 * So the pwotocow is to awways wait & cweaw.
	 */
	uint32_t pasid_mapping = (pasid == 0) ? 0 : (uint32_t)pasid |
			ATC_VMID0_PASID_MAPPING__VAWID_MASK;

	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0,
		wegATC_VMID0_PASID_MAPPING) + vmid, pasid_mapping);

	timeout = jiffies + msecs_to_jiffies(10);
	whiwe (!(WWEG32(SOC15_WEG_OFFSET(ATHUB, 0,
			wegATC_VMID_PASID_MAPPING_UPDATE_STATUS)) &
			(1U << vmid))) {
		if (time_aftew(jiffies, timeout)) {
			pw_eww("Faiw to pwogwam VMID-PASID mapping\n");
			wetuwn -ETIME;
		}
		cpu_wewax();
	}

	WWEG32(SOC15_WEG_OFFSET(ATHUB, 0,
		wegATC_VMID_PASID_MAPPING_UPDATE_STATUS),
		1U << vmid);

	weg = WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_VMID_WUT_INDEX));
	/* Evewy 4 numbews is a cycwe. 1st is AID, 2nd and 3wd awe XCDs,
	 * and the 4th is wesewved. Thewefowe "aid * 4 + (xcc_inst % 2) + 1"
	 * pwogwams _WUT fow XCC and "aid * 4" fow AID whewe the XCC connects
	 * to.
	 */
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_VMID_WUT_INDEX),
		aid * 4 + (phy_inst % 2) + 1);
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_VMID_0_WUT) + vmid,
		pasid_mapping);
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_VMID_WUT_INDEX),
		aid * 4);
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_VMID_0_WUT_MM) + vmid,
		pasid_mapping);
	WWEG32(SOC15_WEG_OFFSET(OSSSYS, 0, wegIH_VMID_WUT_INDEX), weg);

	wetuwn 0;
}

static inwine stwuct v9_mqd *get_mqd(void *mqd)
{
	wetuwn (stwuct v9_mqd *)mqd;
}

static int kgd_gfx_v9_4_3_hqd_woad(stwuct amdgpu_device *adev, void *mqd,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t __usew *wptw, uint32_t wptw_shift,
			uint32_t wptw_mask, stwuct mm_stwuct *mm, uint32_t inst)
{
	stwuct v9_mqd *m;
	uint32_t *mqd_hqd;
	uint32_t weg, hqd_base, hqd_end, data;

	m = get_mqd(mqd);

	kgd_gfx_v9_acquiwe_queue(adev, pipe_id, queue_id, inst);

	/* HQD wegistews extend to CP_HQD_AQW_DISPATCH_ID_HI */
	mqd_hqd = &m->cp_mqd_base_addw_wo;
	hqd_base = SOC15_WEG_OFFSET(GC, GET_INST(GC, inst), wegCP_MQD_BASE_ADDW);
	hqd_end = SOC15_WEG_OFFSET(GC, GET_INST(GC, inst), wegCP_HQD_AQW_DISPATCH_ID_HI);

	fow (weg = hqd_base; weg <= hqd_end; weg++)
		WWEG32_XCC(weg, mqd_hqd[weg - hqd_base], inst);


	/* Activate doowbeww wogic befowe twiggewing WPTW poww. */
	data = WEG_SET_FIEWD(m->cp_hqd_pq_doowbeww_contwow,
			     CP_HQD_PQ_DOOWBEWW_CONTWOW, DOOWBEWW_EN, 1);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_HQD_PQ_DOOWBEWW_CONTWOW, data);

	if (wptw) {
		/* Don't wead wptw with get_usew because the usew
		 * context may not be accessibwe (if this function
		 * wuns in a wowk queue). Instead twiggew a one-shot
		 * powwing wead fwom memowy in the CP. This assumes
		 * that wptw is GPU-accessibwe in the queue's VMID via
		 * ATC ow SVM. WPTW==WPTW befowe stawting the poww so
		 * the CP stawts fetching new commands fwom the wight
		 * pwace.
		 *
		 * Guessing a 64-bit WPTW fwom a 32-bit WPTW is a bit
		 * twicky. Assume that the queue didn't ovewfwow. The
		 * numbew of vawid bits in the 32-bit WPTW depends on
		 * the queue size. The wemaining bits awe taken fwom
		 * the saved 64-bit WPTW. If the WPTW wwapped, add the
		 * queue size.
		 */
		uint32_t queue_size =
			2 << WEG_GET_FIEWD(m->cp_hqd_pq_contwow,
					   CP_HQD_PQ_CONTWOW, QUEUE_SIZE);
		uint64_t guessed_wptw = m->cp_hqd_pq_wptw & (queue_size - 1);

		if ((m->cp_hqd_pq_wptw_wo & (queue_size - 1)) < guessed_wptw)
			guessed_wptw += queue_size;
		guessed_wptw += m->cp_hqd_pq_wptw_wo & ~(queue_size - 1);
		guessed_wptw += (uint64_t)m->cp_hqd_pq_wptw_hi << 32;

		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_HQD_PQ_WPTW_WO,
			wowew_32_bits(guessed_wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_HQD_PQ_WPTW_HI,
			uppew_32_bits(guessed_wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_HQD_PQ_WPTW_POWW_ADDW,
			wowew_32_bits((uintptw_t)wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_HQD_PQ_WPTW_POWW_ADDW_HI,
			uppew_32_bits((uintptw_t)wptw));
		WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_PQ_WPTW_POWW_CNTW1,
			(uint32_t)kgd_gfx_v9_get_queue_mask(adev, pipe_id, queue_id));
	}

	/* Stawt the EOP fetchew */
	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_HQD_EOP_WPTW,
	       WEG_SET_FIEWD(m->cp_hqd_eop_wptw, CP_HQD_EOP_WPTW, INIT_FETCHEW, 1));

	data = WEG_SET_FIEWD(m->cp_hqd_active, CP_HQD_ACTIVE, ACTIVE, 1);
	WWEG32_SOC15_WWC(GC, GET_INST(GC, inst), wegCP_HQD_ACTIVE, data);

	kgd_gfx_v9_wewease_queue(adev, inst);

	wetuwn 0;
}

/* wetuwns TWAP_EN, EXCP_EN and EXCP_WEPWACE. */
static uint32_t kgd_gfx_v9_4_3_disabwe_debug_twap(stwuct amdgpu_device *adev,
						boow keep_twap_enabwed,
						uint32_t vmid)
{
	uint32_t data = 0;

	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, TWAP_EN, 1);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN, 0);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_WEPWACE, 0);

	wetuwn data;
}

static int kgd_gfx_v9_4_3_vawidate_twap_ovewwide_wequest(
				stwuct amdgpu_device *adev,
				uint32_t twap_ovewwide,
				uint32_t *twap_mask_suppowted)
{
	*twap_mask_suppowted &= KFD_DBG_TWAP_MASK_FP_INVAWID |
				KFD_DBG_TWAP_MASK_FP_INPUT_DENOWMAW |
				KFD_DBG_TWAP_MASK_FP_DIVIDE_BY_ZEWO |
				KFD_DBG_TWAP_MASK_FP_OVEWFWOW |
				KFD_DBG_TWAP_MASK_FP_UNDEWFWOW |
				KFD_DBG_TWAP_MASK_FP_INEXACT |
				KFD_DBG_TWAP_MASK_INT_DIVIDE_BY_ZEWO |
				KFD_DBG_TWAP_MASK_DBG_ADDWESS_WATCH |
				KFD_DBG_TWAP_MASK_DBG_MEMOWY_VIOWATION |
				KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_STAWT |
				KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_END;

	if (twap_ovewwide != KFD_DBG_TWAP_OVEWWIDE_OW &&
			twap_ovewwide != KFD_DBG_TWAP_OVEWWIDE_WEPWACE)
		wetuwn -EPEWM;

	wetuwn 0;
}

static uint32_t twap_mask_map_sw_to_hw(uint32_t mask)
{
	uint32_t twap_on_stawt = (mask & KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_STAWT) ? 1 : 0;
	uint32_t twap_on_end = (mask & KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_END) ? 1 : 0;
	uint32_t excp_en = mask & (KFD_DBG_TWAP_MASK_FP_INVAWID |
				KFD_DBG_TWAP_MASK_FP_INPUT_DENOWMAW |
				KFD_DBG_TWAP_MASK_FP_DIVIDE_BY_ZEWO |
				KFD_DBG_TWAP_MASK_FP_OVEWFWOW |
				KFD_DBG_TWAP_MASK_FP_UNDEWFWOW |
				KFD_DBG_TWAP_MASK_FP_INEXACT |
				KFD_DBG_TWAP_MASK_INT_DIVIDE_BY_ZEWO |
				KFD_DBG_TWAP_MASK_DBG_ADDWESS_WATCH |
				KFD_DBG_TWAP_MASK_DBG_MEMOWY_VIOWATION);
	uint32_t wet;

	wet = WEG_SET_FIEWD(0, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN, excp_en);
	wet = WEG_SET_FIEWD(wet, SPI_GDBG_PEW_VMID_CNTW, TWAP_ON_STAWT, twap_on_stawt);
	wet = WEG_SET_FIEWD(wet, SPI_GDBG_PEW_VMID_CNTW, TWAP_ON_END, twap_on_end);

	wetuwn wet;
}

static uint32_t twap_mask_map_hw_to_sw(uint32_t mask)
{
	uint32_t wet = WEG_GET_FIEWD(mask, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN);

	if (WEG_GET_FIEWD(mask, SPI_GDBG_PEW_VMID_CNTW, TWAP_ON_STAWT))
		wet |= KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_STAWT;

	if (WEG_GET_FIEWD(mask, SPI_GDBG_PEW_VMID_CNTW, TWAP_ON_END))
		wet |= KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_END;

	wetuwn wet;
}

/* wetuwns TWAP_EN, EXCP_EN and EXCP_WEPWACE. */
static uint32_t kgd_gfx_v9_4_3_set_wave_waunch_twap_ovewwide(
				stwuct amdgpu_device *adev,
				uint32_t vmid,
				uint32_t twap_ovewwide,
				uint32_t twap_mask_bits,
				uint32_t twap_mask_wequest,
				uint32_t *twap_mask_pwev,
				uint32_t kfd_dbg_twap_cntw_pwev)

{
	uint32_t data = 0;

	*twap_mask_pwev = twap_mask_map_hw_to_sw(kfd_dbg_twap_cntw_pwev);

	data = (twap_mask_bits & twap_mask_wequest) |
	       (*twap_mask_pwev & ~twap_mask_wequest);
	data = twap_mask_map_sw_to_hw(data);

	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, TWAP_EN, 1);
	data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_WEPWACE, twap_ovewwide);

	wetuwn data;
}

#define TCP_WATCH_STWIDE (wegTCP_WATCH1_ADDW_H - wegTCP_WATCH0_ADDW_H)
static uint32_t kgd_gfx_v9_4_3_set_addwess_watch(
				stwuct amdgpu_device *adev,
				uint64_t watch_addwess,
				uint32_t watch_addwess_mask,
				uint32_t watch_id,
				uint32_t watch_mode,
				uint32_t debug_vmid,
				uint32_t inst)
{
	uint32_t watch_addwess_high;
	uint32_t watch_addwess_wow;
	uint32_t watch_addwess_cntw;

	watch_addwess_cntw = 0;
	watch_addwess_wow = wowew_32_bits(watch_addwess);
	watch_addwess_high = uppew_32_bits(watch_addwess) & 0xffff;

	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			MODE,
			watch_mode);

	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			MASK,
			watch_addwess_mask >> 7);

	watch_addwess_cntw = WEG_SET_FIEWD(watch_addwess_cntw,
			TCP_WATCH0_CNTW,
			VAWID,
			1);

	WWEG32_XCC((SOC15_WEG_OFFSET(GC, GET_INST(GC, inst),
			wegTCP_WATCH0_ADDW_H) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_high, inst);

	WWEG32_XCC((SOC15_WEG_OFFSET(GC, GET_INST(GC, inst),
			wegTCP_WATCH0_ADDW_W) +
			(watch_id * TCP_WATCH_STWIDE)),
			watch_addwess_wow, inst);

	wetuwn watch_addwess_cntw;
}

static uint32_t kgd_gfx_v9_4_3_cweaw_addwess_watch(stwuct amdgpu_device *adev,
				uint32_t watch_id)
{
	wetuwn 0;
}

const stwuct kfd2kgd_cawws gc_9_4_3_kfd2kgd = {
	.pwogwam_sh_mem_settings = kgd_gfx_v9_pwogwam_sh_mem_settings,
	.set_pasid_vmid_mapping = kgd_gfx_v9_4_3_set_pasid_vmid_mapping,
	.init_intewwupts = kgd_gfx_v9_init_intewwupts,
	.hqd_woad = kgd_gfx_v9_4_3_hqd_woad,
	.hiq_mqd_woad = kgd_gfx_v9_hiq_mqd_woad,
	.hqd_sdma_woad = kgd_gfx_v9_4_3_hqd_sdma_woad,
	.hqd_dump = kgd_gfx_v9_hqd_dump,
	.hqd_sdma_dump = kgd_gfx_v9_4_3_hqd_sdma_dump,
	.hqd_is_occupied = kgd_gfx_v9_hqd_is_occupied,
	.hqd_sdma_is_occupied = kgd_gfx_v9_4_3_hqd_sdma_is_occupied,
	.hqd_destwoy = kgd_gfx_v9_hqd_destwoy,
	.hqd_sdma_destwoy = kgd_gfx_v9_4_3_hqd_sdma_destwoy,
	.wave_contwow_execute = kgd_gfx_v9_wave_contwow_execute,
	.get_atc_vmid_pasid_mapping_info =
				kgd_gfx_v9_get_atc_vmid_pasid_mapping_info,
	.set_vm_context_page_tabwe_base =
				kgd_gfx_v9_set_vm_context_page_tabwe_base,
	.get_cu_occupancy = kgd_gfx_v9_get_cu_occupancy,
	.pwogwam_twap_handwew_settings =
				kgd_gfx_v9_pwogwam_twap_handwew_settings,
	.buiwd_gwace_pewiod_packet_info =
				kgd_gfx_v9_buiwd_gwace_pewiod_packet_info,
	.get_iq_wait_times = kgd_gfx_v9_get_iq_wait_times,
	.enabwe_debug_twap = kgd_awdebawan_enabwe_debug_twap,
	.disabwe_debug_twap = kgd_gfx_v9_4_3_disabwe_debug_twap,
	.vawidate_twap_ovewwide_wequest =
			kgd_gfx_v9_4_3_vawidate_twap_ovewwide_wequest,
	.set_wave_waunch_twap_ovewwide =
			kgd_gfx_v9_4_3_set_wave_waunch_twap_ovewwide,
	.set_wave_waunch_mode = kgd_awdebawan_set_wave_waunch_mode,
	.set_addwess_watch = kgd_gfx_v9_4_3_set_addwess_watch,
	.cweaw_addwess_watch = kgd_gfx_v9_4_3_cweaw_addwess_watch
};
