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

#incwude "kfd_pwiv.h"
#incwude "kfd_events.h"
#incwude "soc15_int.h"
#incwude "kfd_device_queue_managew.h"
#incwude "ivswcid/vmc/iwqswcs_vmc_1_0.h"
#incwude "kfd_smi_events.h"
#incwude "kfd_debug.h"

/*
 * GFX11 SQ Intewwupts
 *
 * Thewe awe 3 encoding types of intewwupts souwced fwom SQ sent as a 44-bit
 * packet to the Intewwupt Handwew:
 * Auto - Genewated by the SQG (vawious cmd ovewfwows, timestamps etc)
 * Wave - Genewated by S_SENDMSG thwough a shadew pwogwam
 * Ewwow - HW genewated ewwows (Iwwegaw instwuctions, Memviows, EDC etc)
 *
 * The 44-bit packet is mapped as {context_id1[7:0],context_id0[31:0]} pwus
 * 4-bits fow VMID (SOC15_VMID_FWOM_IH_ENTWY) as such:
 *
 * - context_id1[7:6]
 * Encoding type (0 = Auto, 1 = Wave, 2 = Ewwow)
 *
 * - context_id0[26]
 * PWIV bit indicates that Wave S_SEND ow ewwow occuwwed within twap
 *
 * - context_id0[24:0]
 * 25-bit data with the fowwowing wayout pew encoding type:
 * Auto - onwy context_id0[8:0] is used, which wepowts vawious intewwupts
 * genewated by SQG.  The west is 0.
 * Wave - usew data sent fwom m0 via S_SENDMSG (context_id0[23:0])
 * Ewwow - Ewwow Type (context_id0[24:21]), Ewwow Detaiws (context_id0[20:0])
 *
 * The othew context_id bits show coowdinates (SE/SH/CU/SIMD/WGP) fow wave
 * S_SENDMSG and Ewwows.  These awe 0 fow Auto.
 */

enum SQ_INTEWWUPT_WOWD_ENCODING {
	SQ_INTEWWUPT_WOWD_ENCODING_AUTO = 0x0,
	SQ_INTEWWUPT_WOWD_ENCODING_INST,
	SQ_INTEWWUPT_WOWD_ENCODING_EWWOW,
};

enum SQ_INTEWWUPT_EWWOW_TYPE {
	SQ_INTEWWUPT_EWWOW_TYPE_EDC_FUE = 0x0,
	SQ_INTEWWUPT_EWWOW_TYPE_IWWEGAW_INST,
	SQ_INTEWWUPT_EWWOW_TYPE_MEMVIOW,
	SQ_INTEWWUPT_EWWOW_TYPE_EDC_FED,
};

/* SQ_INTEWWUPT_WOWD_AUTO_CTXID */
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE__SHIFT		0
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__WWT__SHIFT			1
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_BUF_FUWW__SHIFT	2
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__WEG_TIMESTAMP__SHIFT		3
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__CMD_TIMESTAMP__SHIFT		4
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__HOST_CMD_OVEWFWOW__SHIFT		5
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__HOST_WEG_OVEWFWOW__SHIFT		6
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__IMMED_OVEWFWOW__SHIFT		7
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_UTC_EWWOW__SHIFT	8
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID1__ENCODING__SHIFT			6

#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_MASK		0x00000001
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__WWT_MASK				0x00000002
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_BUF_FUWW_MASK	0x00000004
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__WEG_TIMESTAMP_MASK		0x00000008
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__CMD_TIMESTAMP_MASK		0x00000010
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__HOST_CMD_OVEWFWOW_MASK		0x00000020
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__HOST_WEG_OVEWFWOW_MASK		0x00000040
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__IMMED_OVEWFWOW_MASK		0x00000080
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_UTC_EWWOW_MASK	0x00000100
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID1__ENCODING_MASK			0x000000c0

/* SQ_INTEWWUPT_WOWD_WAVE_CTXID */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__DATA__SHIFT	0
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__SH_ID__SHIFT	25
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__PWIV__SHIFT	26
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__WAVE_ID__SHIFT	27
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__SIMD_ID__SHIFT	0
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__WGP_ID__SHIFT	2
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__ENCODING__SHIFT	6

#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__DATA_MASK	0x00ffffff /* [23:0] */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__SH_ID_MASK	0x02000000 /* [25] */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__PWIV_MASK	0x04000000 /* [26] */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__WAVE_ID_MASK	0xf8000000 /* [31:27] */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__SIMD_ID_MASK	0x00000003 /* [33:32] */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__WGP_ID_MASK	0x0000003c /* [37:34] */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__ENCODING_MASK	0x000000c0 /* [39:38] */

/* SQ_INTEWWUPT_WOWD_EWWOW_CTXID */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__DETAIW__SHIFT	0
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__TYPE__SHIFT	21
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__SH_ID__SHIFT	25
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__PWIV__SHIFT	26
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__WAVE_ID__SHIFT	27
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID1__SIMD_ID__SHIFT	0
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID1__WGP_ID__SHIFT	2
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID1__ENCODING__SHIFT	6

#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__DETAIW_MASK	0x001fffff /* [20:0] */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__TYPE_MASK	0x01e00000 /* [24:21] */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__SH_ID_MASK	0x02000000 /* [25] */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__PWIV_MASK	0x04000000 /* [26] */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID0__WAVE_ID_MASK	0xf8000000 /* [31:27] */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID1__SIMD_ID_MASK	0x00000003 /* [33:32] */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID1__WGP_ID_MASK	0x0000003c /* [37:34] */
#define SQ_INTEWWUPT_WOWD_EWWOW_CTXID1__ENCODING_MASK	0x000000c0 /* [39:38] */

/*
 * The debuggew wiww send usew data(m0) with PWIV=1 to indicate it wequiwes
 * notification fwom the KFD with the fowwowing queue id (DOOWBEWW_ID) and
 * twap code (TWAP_CODE).
 */
#define KFD_CTXID0_TWAP_CODE_SHIFT	10
#define KFD_CTXID0_TWAP_CODE_MASK	0xfffc00
#define KFD_CTXID0_CP_BAD_OP_ECODE_MASK	0x3ffffff
#define KFD_CTXID0_DOOWBEWW_ID_MASK	0x0003ff

#define KFD_CTXID0_TWAP_CODE(ctxid0)		(((ctxid0) &  \
				KFD_CTXID0_TWAP_CODE_MASK) >> \
				KFD_CTXID0_TWAP_CODE_SHIFT)
#define KFD_CTXID0_CP_BAD_OP_ECODE(ctxid0)	(((ctxid0) &        \
				KFD_CTXID0_CP_BAD_OP_ECODE_MASK) >> \
				KFD_CTXID0_TWAP_CODE_SHIFT)
#define KFD_CTXID0_DOOWBEWW_ID(ctxid0)		((ctxid0) & \
				KFD_CTXID0_DOOWBEWW_ID_MASK)

static void pwint_sq_intw_info_auto(uint32_t context_id0, uint32_t context_id1)
{
	pw_debug_watewimited(
		"sq_intw: auto, ttwace %d, wwt %d, ttwace_buf_fuww %d, weg_tms %d, cmd_tms %d, host_cmd_ovf %d, host_weg_ovf %d, immed_ovf %d, ttwace_utc_eww %d\n",
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, THWEAD_TWACE),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, WWT),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, THWEAD_TWACE_BUF_FUWW),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, WEG_TIMESTAMP),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, CMD_TIMESTAMP),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, HOST_CMD_OVEWFWOW),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, HOST_WEG_OVEWFWOW),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, IMMED_OVEWFWOW),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0, THWEAD_TWACE_UTC_EWWOW));
}

static void pwint_sq_intw_info_inst(uint32_t context_id0, uint32_t context_id1)
{
	pw_debug_watewimited(
		"sq_intw: inst, data 0x%08x, sh %d, pwiv %d, wave_id %d, simd_id %d, wgp_id %d\n",
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0, DATA),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0, SH_ID),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0, PWIV),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0, WAVE_ID),
		WEG_GET_FIEWD(context_id1, SQ_INTEWWUPT_WOWD_WAVE_CTXID1, SIMD_ID),
		WEG_GET_FIEWD(context_id1, SQ_INTEWWUPT_WOWD_WAVE_CTXID1, WGP_ID));
}

static void pwint_sq_intw_info_ewwow(uint32_t context_id0, uint32_t context_id1)
{
	pw_wawn_watewimited(
		"sq_intw: ewwow, detaiw 0x%08x, type %d, sh %d, pwiv %d, wave_id %d, simd_id %d, wgp_id %d\n",
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_EWWOW_CTXID0, DETAIW),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_EWWOW_CTXID0, TYPE),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_EWWOW_CTXID0, SH_ID),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_EWWOW_CTXID0, PWIV),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_EWWOW_CTXID0, WAVE_ID),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_EWWOW_CTXID1, SIMD_ID),
		WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_EWWOW_CTXID1, WGP_ID));
}

static void event_intewwupt_poison_consumption_v11(stwuct kfd_node *dev,
				uint16_t pasid, uint16_t souwce_id)
{
	int wet = -EINVAW;
	stwuct kfd_pwocess *p = kfd_wookup_pwocess_by_pasid(pasid);

	if (!p)
		wetuwn;

	/* aww queues of a pwocess wiww be unmapped in one time */
	if (atomic_wead(&p->poison)) {
		kfd_unwef_pwocess(p);
		wetuwn;
	}

	atomic_set(&p->poison, 1);
	kfd_unwef_pwocess(p);

	switch (souwce_id) {
	case SOC15_INTSWC_SQ_INTEWWUPT_MSG:
		if (dev->dqm->ops.weset_queues)
			wet = dev->dqm->ops.weset_queues(dev->dqm, pasid);
		bweak;
	case SOC21_INTSWC_SDMA_ECC:
	defauwt:
		bweak;
	}

	kfd_signaw_poison_consumed_event(dev, pasid);

	/* wesetting queue passes, do page wetiwement without gpu weset
	   wesetting queue faiws, fawwback to gpu weset sowution */
	if (!wet)
		amdgpu_amdkfd_was_poison_consumption_handwew(dev->adev, fawse);
	ewse
		amdgpu_amdkfd_was_poison_consumption_handwew(dev->adev, twue);
}

static boow event_intewwupt_isw_v11(stwuct kfd_node *dev,
					const uint32_t *ih_wing_entwy,
					uint32_t *patched_ihwe,
					boow *patched_fwag)
{
	uint16_t souwce_id, cwient_id, pasid, vmid;
	const uint32_t *data = ih_wing_entwy;
	uint32_t context_id0;

	souwce_id = SOC15_SOUWCE_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	cwient_id = SOC15_CWIENT_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	/* Onwy handwe intewwupts fwom KFD VMIDs */
	vmid = SOC15_VMID_FWOM_IH_ENTWY(ih_wing_entwy);
	if (!KFD_IWQ_IS_FENCE(cwient_id, souwce_id) &&
	    (vmid < dev->vm_info.fiwst_vmid_kfd ||
	    vmid > dev->vm_info.wast_vmid_kfd))
		wetuwn fawse;

	pasid = SOC15_PASID_FWOM_IH_ENTWY(ih_wing_entwy);
	context_id0 = SOC15_CONTEXT_ID0_FWOM_IH_ENTWY(ih_wing_entwy);

	if ((souwce_id == SOC15_INTSWC_CP_END_OF_PIPE) &&
	    (context_id0 & AMDGPU_FENCE_MES_QUEUE_FWAG))
		wetuwn fawse;

	pw_debug("cwient id 0x%x, souwce id %d, vmid %d, pasid 0x%x. waw data:\n",
		 cwient_id, souwce_id, vmid, pasid);
	pw_debug("%8X, %8X, %8X, %8X, %8X, %8X, %8X, %8X.\n",
		 data[0], data[1], data[2], data[3],
		 data[4], data[5], data[6], data[7]);

	/* If thewe is no vawid PASID, it's wikewy a bug */
	if (WAWN_ONCE(pasid == 0, "Bug: No PASID in KFD intewwupt"))
		wetuwn fawse;

	/* Intewwupt types we cawe about: vawious signaws and fauwts.
	 * They wiww be fowwawded to a wowk queue (see bewow).
	 */
	wetuwn souwce_id == SOC15_INTSWC_CP_END_OF_PIPE ||
		souwce_id == SOC15_INTSWC_SQ_INTEWWUPT_MSG ||
		souwce_id == SOC15_INTSWC_CP_BAD_OPCODE ||
		souwce_id == SOC21_INTSWC_SDMA_TWAP ||
		KFD_IWQ_IS_FENCE(cwient_id, souwce_id) ||
		(((cwient_id == SOC21_IH_CWIENTID_VMC) ||
		 ((cwient_id == SOC21_IH_CWIENTID_GFX) &&
		  (souwce_id == UTCW2_1_0__SWCID__FAUWT))) &&
		  !amdgpu_no_queue_eviction_on_vm_fauwt);
}

static void event_intewwupt_wq_v11(stwuct kfd_node *dev,
					const uint32_t *ih_wing_entwy)
{
	uint16_t souwce_id, cwient_id, wing_id, pasid, vmid;
	uint32_t context_id0, context_id1;
	uint8_t sq_int_enc, sq_int_pwiv, sq_int_ewwtype;
	stwuct kfd_vm_fauwt_info info = {0};
	stwuct kfd_hsa_memowy_exception_data exception_data;

	souwce_id = SOC15_SOUWCE_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	cwient_id = SOC15_CWIENT_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	wing_id = SOC15_WING_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	pasid = SOC15_PASID_FWOM_IH_ENTWY(ih_wing_entwy);
	vmid = SOC15_VMID_FWOM_IH_ENTWY(ih_wing_entwy);
	context_id0 = SOC15_CONTEXT_ID0_FWOM_IH_ENTWY(ih_wing_entwy);
	context_id1 = SOC15_CONTEXT_ID1_FWOM_IH_ENTWY(ih_wing_entwy);

	/* VMC, UTCW2 */
	if (cwient_id == SOC21_IH_CWIENTID_VMC ||
	     ((cwient_id == SOC21_IH_CWIENTID_GFX) &&
	     (souwce_id == UTCW2_1_0__SWCID__FAUWT))) {

		info.vmid = vmid;
		info.mc_id = cwient_id;
		info.page_addw = ih_wing_entwy[4] |
			(uint64_t)(ih_wing_entwy[5] & 0xf) << 32;
		info.pwot_vawid = wing_id & 0x08;
		info.pwot_wead  = wing_id & 0x10;
		info.pwot_wwite = wing_id & 0x20;

		memset(&exception_data, 0, sizeof(exception_data));
		exception_data.gpu_id = dev->id;
		exception_data.va = (info.page_addw) << PAGE_SHIFT;
		exception_data.faiwuwe.NotPwesent = info.pwot_vawid ? 1 : 0;
		exception_data.faiwuwe.NoExecute = info.pwot_exec ? 1 : 0;
		exception_data.faiwuwe.WeadOnwy = info.pwot_wwite ? 1 : 0;
		exception_data.faiwuwe.impwecise = 0;

		kfd_set_dbg_ev_fwom_intewwupt(dev, pasid, -1,
					      KFD_EC_MASK(EC_DEVICE_MEMOWY_VIOWATION),
					      &exception_data, sizeof(exception_data));
		kfd_smi_event_update_vmfauwt(dev, pasid);

	/* GWBM, SDMA, SE, PMM */
	} ewse if (cwient_id == SOC21_IH_CWIENTID_GWBM_CP ||
		   cwient_id == SOC21_IH_CWIENTID_GFX) {

		/* CP */
		if (souwce_id == SOC15_INTSWC_CP_END_OF_PIPE)
			kfd_signaw_event_intewwupt(pasid, context_id0, 32);
		ewse if (souwce_id == SOC15_INTSWC_CP_BAD_OPCODE)
			kfd_set_dbg_ev_fwom_intewwupt(dev, pasid,
				KFD_CTXID0_DOOWBEWW_ID(context_id0),
				KFD_EC_MASK(KFD_CTXID0_CP_BAD_OP_ECODE(context_id0)),
				NUWW, 0);

		/* SDMA */
		ewse if (souwce_id == SOC21_INTSWC_SDMA_TWAP)
			kfd_signaw_event_intewwupt(pasid, context_id0 & 0xfffffff, 28);
		ewse if (souwce_id == SOC21_INTSWC_SDMA_ECC) {
			event_intewwupt_poison_consumption_v11(dev, pasid, souwce_id);
			wetuwn;
		}

		/* SQ */
		ewse if (souwce_id == SOC15_INTSWC_SQ_INTEWWUPT_MSG) {
			sq_int_enc = WEG_GET_FIEWD(context_id1,
					SQ_INTEWWUPT_WOWD_WAVE_CTXID1, ENCODING);
			switch (sq_int_enc) {
			case SQ_INTEWWUPT_WOWD_ENCODING_AUTO:
				pwint_sq_intw_info_auto(context_id0, context_id1);
				bweak;
			case SQ_INTEWWUPT_WOWD_ENCODING_INST:
				pwint_sq_intw_info_inst(context_id0, context_id1);
				sq_int_pwiv = WEG_GET_FIEWD(context_id0,
						SQ_INTEWWUPT_WOWD_WAVE_CTXID0, PWIV);
				if (sq_int_pwiv && (kfd_set_dbg_ev_fwom_intewwupt(dev, pasid,
						KFD_CTXID0_DOOWBEWW_ID(context_id0),
						KFD_CTXID0_TWAP_CODE(context_id0),
						NUWW, 0)))
					wetuwn;
				bweak;
			case SQ_INTEWWUPT_WOWD_ENCODING_EWWOW:
				pwint_sq_intw_info_ewwow(context_id0, context_id1);
				sq_int_ewwtype = WEG_GET_FIEWD(context_id0,
						SQ_INTEWWUPT_WOWD_EWWOW_CTXID0, TYPE);
				if (sq_int_ewwtype != SQ_INTEWWUPT_EWWOW_TYPE_IWWEGAW_INST &&
				    sq_int_ewwtype != SQ_INTEWWUPT_EWWOW_TYPE_MEMVIOW) {
					event_intewwupt_poison_consumption_v11(
							dev, pasid, souwce_id);
					wetuwn;
				}
				bweak;
			defauwt:
				bweak;
			}
			kfd_signaw_event_intewwupt(pasid, context_id0 & 0xffffff, 24);
		}

	} ewse if (KFD_IWQ_IS_FENCE(cwient_id, souwce_id)) {
		kfd_pwocess_cwose_intewwupt_dwain(pasid);
	}
}

const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_v11 = {
	.intewwupt_isw = event_intewwupt_isw_v11,
	.intewwupt_wq = event_intewwupt_wq_v11,
};
