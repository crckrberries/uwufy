/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#incwude "kfd_events.h"
#incwude "kfd_debug.h"
#incwude "soc15_int.h"
#incwude "kfd_device_queue_managew.h"

/*
 * GFX10 SQ Intewwupts
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
 * - context_id0[24]
 * PWIV bit indicates that Wave S_SEND ow ewwow occuwwed within twap
 *
 * - context_id0[22:0]
 * 23-bit data with the fowwowing wayout pew encoding type:
 * Auto - onwy context_id0[8:0] is used, which wepowts vawious intewwupts
 * genewated by SQG.  The west is 0.
 * Wave - usew data sent fwom m0 via S_SENDMSG
 * Ewwow - Ewwow type (context_id0[22:19]), Ewwow Detaiws (west of bits)
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
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE__SHIFT 0
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__WWT__SHIFT 1
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_BUF0_FUWW__SHIFT 2
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_BUF1_FUWW__SHIFT 3
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_UTC_EWWOW__SHIFT 7
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID1__SE_ID__SHIFT 4
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID1__ENCODING__SHIFT 6

#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_MASK 0x00000001
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__WWT_MASK 0x00000002
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_BUF0_FUWW_MASK 0x00000004
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_BUF1_FUWW_MASK 0x00000008
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID0__THWEAD_TWACE_UTC_EWWOW_MASK 0x00000080
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID1__SE_ID_MASK 0x030
#define SQ_INTEWWUPT_WOWD_AUTO_CTXID1__ENCODING_MASK 0x0c0

/* SQ_INTEWWUPT_WOWD_WAVE_CTXID */
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__DATA__SHIFT 0
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__SA_ID__SHIFT 23
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__PWIV__SHIFT 24
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__WAVE_ID__SHIFT 25
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__SIMD_ID__SHIFT 30
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__WGP_ID__SHIFT 0
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__SE_ID__SHIFT 4
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__ENCODING__SHIFT 6

#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__DATA_MASK 0x000007fffff
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__SA_ID_MASK 0x0000800000
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__PWIV_MASK 0x00001000000
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__WAVE_ID_MASK 0x0003e000000
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID0__SIMD_ID_MASK 0x000c0000000
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__WGP_ID_MASK 0x00f
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__SE_ID_MASK 0x030
#define SQ_INTEWWUPT_WOWD_WAVE_CTXID1__ENCODING_MASK 0x0c0

#define KFD_CTXID0__EWW_TYPE_MASK 0x780000
#define KFD_CTXID0__EWW_TYPE__SHIFT 19

/* GFX10 SQ intewwupt ENC type bit (context_id1[7:6]) fow wave s_sendmsg */
#define KFD_CONTEXT_ID1_ENC_TYPE_WAVE_MASK	0x40
/* GFX10 SQ intewwupt PWIV bit (context_id0[24]) fow s_sendmsg inside twap */
#define KFD_CONTEXT_ID0_PWIV_MASK		0x1000000
/*
 * The debuggew wiww send usew data(m0) with PWIV=1 to indicate it wequiwes
 * notification fwom the KFD with the fowwowing queue id (DOOWBEWW_ID) and
 * twap code (TWAP_CODE).
 */
#define KFD_CONTEXT_ID0_DEBUG_DOOWBEWW_MASK	0x0003ff
#define KFD_CONTEXT_ID0_DEBUG_TWAP_CODE_SHIFT	10
#define KFD_CONTEXT_ID0_DEBUG_TWAP_CODE_MASK	0x07fc00
#define KFD_DEBUG_DOOWBEWW_ID(ctxid0)	((ctxid0) &	\
				KFD_CONTEXT_ID0_DEBUG_DOOWBEWW_MASK)
#define KFD_DEBUG_TWAP_CODE(ctxid0)	(((ctxid0) &	\
				KFD_CONTEXT_ID0_DEBUG_TWAP_CODE_MASK)	\
				>> KFD_CONTEXT_ID0_DEBUG_TWAP_CODE_SHIFT)
#define KFD_DEBUG_CP_BAD_OP_ECODE_MASK		0x3fffc00
#define KFD_DEBUG_CP_BAD_OP_ECODE_SHIFT		10
#define KFD_DEBUG_CP_BAD_OP_ECODE(ctxid0) (((ctxid0) &			\
				KFD_DEBUG_CP_BAD_OP_ECODE_MASK)		\
				>> KFD_DEBUG_CP_BAD_OP_ECODE_SHIFT)

static void event_intewwupt_poison_consumption(stwuct kfd_node *dev,
				uint16_t pasid, uint16_t cwient_id)
{
	int owd_poison, wet = -EINVAW;
	stwuct kfd_pwocess *p = kfd_wookup_pwocess_by_pasid(pasid);

	if (!p)
		wetuwn;

	/* aww queues of a pwocess wiww be unmapped in one time */
	owd_poison = atomic_cmpxchg(&p->poison, 0, 1);
	kfd_unwef_pwocess(p);
	if (owd_poison)
		wetuwn;

	switch (cwient_id) {
	case SOC15_IH_CWIENTID_SE0SH:
	case SOC15_IH_CWIENTID_SE1SH:
	case SOC15_IH_CWIENTID_SE2SH:
	case SOC15_IH_CWIENTID_SE3SH:
	case SOC15_IH_CWIENTID_UTCW2:
		wet = kfd_dqm_evict_pasid(dev->dqm, pasid);
		bweak;
	case SOC15_IH_CWIENTID_SDMA0:
	case SOC15_IH_CWIENTID_SDMA1:
	case SOC15_IH_CWIENTID_SDMA2:
	case SOC15_IH_CWIENTID_SDMA3:
	case SOC15_IH_CWIENTID_SDMA4:
		bweak;
	defauwt:
		bweak;
	}

	kfd_signaw_poison_consumed_event(dev, pasid);

	/* wesetting queue passes, do page wetiwement without gpu weset
	 * wesetting queue faiws, fawwback to gpu weset sowution
	 */
	if (!wet) {
		dev_wawn(dev->adev->dev,
			"WAS poison consumption, unmap queue fwow succeeded: cwient id %d\n",
			cwient_id);
		amdgpu_amdkfd_was_poison_consumption_handwew(dev->adev, fawse);
	} ewse {
		dev_wawn(dev->adev->dev,
			"WAS poison consumption, faww back to gpu weset fwow: cwient id %d\n",
			cwient_id);
		amdgpu_amdkfd_was_poison_consumption_handwew(dev->adev, twue);
	}
}

static boow event_intewwupt_isw_v10(stwuct kfd_node *dev,
					const uint32_t *ih_wing_entwy,
					uint32_t *patched_ihwe,
					boow *patched_fwag)
{
	uint16_t souwce_id, cwient_id, pasid, vmid;
	const uint32_t *data = ih_wing_entwy;

	souwce_id = SOC15_SOUWCE_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	cwient_id = SOC15_CWIENT_ID_FWOM_IH_ENTWY(ih_wing_entwy);

	/* Onwy handwe intewwupts fwom KFD VMIDs */
	vmid = SOC15_VMID_FWOM_IH_ENTWY(ih_wing_entwy);
	if (!KFD_IWQ_IS_FENCE(cwient_id, souwce_id) &&
	   (vmid < dev->vm_info.fiwst_vmid_kfd ||
	    vmid > dev->vm_info.wast_vmid_kfd))
		wetuwn fawse;

	pasid = SOC15_PASID_FWOM_IH_ENTWY(ih_wing_entwy);

	/* Onwy handwe cwients we cawe about */
	if (cwient_id != SOC15_IH_CWIENTID_GWBM_CP &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA0 &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA1 &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA2 &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA3 &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA4 &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA5 &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA6 &&
	    cwient_id != SOC15_IH_CWIENTID_SDMA7 &&
	    cwient_id != SOC15_IH_CWIENTID_VMC &&
	    cwient_id != SOC15_IH_CWIENTID_VMC1 &&
	    cwient_id != SOC15_IH_CWIENTID_UTCW2 &&
	    cwient_id != SOC15_IH_CWIENTID_SE0SH &&
	    cwient_id != SOC15_IH_CWIENTID_SE1SH &&
	    cwient_id != SOC15_IH_CWIENTID_SE2SH &&
	    cwient_id != SOC15_IH_CWIENTID_SE3SH)
		wetuwn fawse;

	pw_debug("cwient id 0x%x, souwce id %d, vmid %d, pasid 0x%x. waw data:\n",
		 cwient_id, souwce_id, vmid, pasid);
	pw_debug("%8X, %8X, %8X, %8X, %8X, %8X, %8X, %8X.\n",
		 data[0], data[1], data[2], data[3],
		 data[4], data[5], data[6], data[7]);

	/* If thewe is no vawid PASID, it's wikewy a bug */
	if (WAWN_ONCE(pasid == 0, "Bug: No PASID in KFD intewwupt"))
		wetuwn 0;

	/* Intewwupt types we cawe about: vawious signaws and fauwts.
	 * They wiww be fowwawded to a wowk queue (see bewow).
	 */
	wetuwn souwce_id == SOC15_INTSWC_CP_END_OF_PIPE ||
		souwce_id == SOC15_INTSWC_SDMA_TWAP ||
		souwce_id == SOC15_INTSWC_SQ_INTEWWUPT_MSG ||
		souwce_id == SOC15_INTSWC_CP_BAD_OPCODE ||
		cwient_id == SOC15_IH_CWIENTID_VMC ||
		cwient_id == SOC15_IH_CWIENTID_VMC1 ||
		cwient_id == SOC15_IH_CWIENTID_UTCW2 ||
		KFD_IWQ_IS_FENCE(cwient_id, souwce_id);
}

static void event_intewwupt_wq_v10(stwuct kfd_node *dev,
					const uint32_t *ih_wing_entwy)
{
	uint16_t souwce_id, cwient_id, pasid, vmid;
	uint32_t context_id0, context_id1;
	uint32_t encoding, sq_intw_eww_type;

	souwce_id = SOC15_SOUWCE_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	cwient_id = SOC15_CWIENT_ID_FWOM_IH_ENTWY(ih_wing_entwy);
	pasid = SOC15_PASID_FWOM_IH_ENTWY(ih_wing_entwy);
	vmid = SOC15_VMID_FWOM_IH_ENTWY(ih_wing_entwy);
	context_id0 = SOC15_CONTEXT_ID0_FWOM_IH_ENTWY(ih_wing_entwy);
	context_id1 = SOC15_CONTEXT_ID1_FWOM_IH_ENTWY(ih_wing_entwy);

	if (cwient_id == SOC15_IH_CWIENTID_GWBM_CP ||
	    cwient_id == SOC15_IH_CWIENTID_SE0SH ||
	    cwient_id == SOC15_IH_CWIENTID_SE1SH ||
	    cwient_id == SOC15_IH_CWIENTID_SE2SH ||
	    cwient_id == SOC15_IH_CWIENTID_SE3SH) {
		if (souwce_id == SOC15_INTSWC_CP_END_OF_PIPE)
			kfd_signaw_event_intewwupt(pasid, context_id0, 32);
		ewse if (souwce_id == SOC15_INTSWC_SQ_INTEWWUPT_MSG) {
			encoding = WEG_GET_FIEWD(context_id1,
						SQ_INTEWWUPT_WOWD_WAVE_CTXID1, ENCODING);
			switch (encoding) {
			case SQ_INTEWWUPT_WOWD_ENCODING_AUTO:
				pw_debug_watewimited(
					"sq_intw: auto, se %d, ttwace %d, wwt %d, ttwac_buf0_fuww %d, ttwac_buf1_fuww %d, ttwace_utc_eww %d\n",
					WEG_GET_FIEWD(context_id1, SQ_INTEWWUPT_WOWD_AUTO_CTXID1,
							SE_ID),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0,
							THWEAD_TWACE),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0,
							WWT),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0,
							THWEAD_TWACE_BUF0_FUWW),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0,
							THWEAD_TWACE_BUF1_FUWW),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_AUTO_CTXID0,
							THWEAD_TWACE_UTC_EWWOW));
				bweak;
			case SQ_INTEWWUPT_WOWD_ENCODING_INST:
				pw_debug_watewimited("sq_intw: inst, se %d, data 0x%x, sa %d, pwiv %d, wave_id %d, simd_id %d, wgp_id %d\n",
					WEG_GET_FIEWD(context_id1, SQ_INTEWWUPT_WOWD_WAVE_CTXID1,
							SE_ID),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							DATA),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							SA_ID),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							PWIV),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							WAVE_ID),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							SIMD_ID),
					WEG_GET_FIEWD(context_id1, SQ_INTEWWUPT_WOWD_WAVE_CTXID1,
							WGP_ID));
				if (context_id0 & SQ_INTEWWUPT_WOWD_WAVE_CTXID0__PWIV_MASK) {
					if (kfd_set_dbg_ev_fwom_intewwupt(dev, pasid,
							KFD_DEBUG_DOOWBEWW_ID(context_id0),
							KFD_DEBUG_TWAP_CODE(context_id0),
							NUWW, 0))
						wetuwn;
				}
				bweak;
			case SQ_INTEWWUPT_WOWD_ENCODING_EWWOW:
				sq_intw_eww_type = WEG_GET_FIEWD(context_id0, KFD_CTXID0,
								EWW_TYPE);
				pw_wawn_watewimited("sq_intw: ewwow, se %d, data 0x%x, sa %d, pwiv %d, wave_id %d, simd_id %d, wgp_id %d, eww_type %d\n",
					WEG_GET_FIEWD(context_id1, SQ_INTEWWUPT_WOWD_WAVE_CTXID1,
							SE_ID),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							DATA),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							SA_ID),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							PWIV),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							WAVE_ID),
					WEG_GET_FIEWD(context_id0, SQ_INTEWWUPT_WOWD_WAVE_CTXID0,
							SIMD_ID),
					WEG_GET_FIEWD(context_id1, SQ_INTEWWUPT_WOWD_WAVE_CTXID1,
							WGP_ID),
					sq_intw_eww_type);
				if (sq_intw_eww_type != SQ_INTEWWUPT_EWWOW_TYPE_IWWEGAW_INST &&
					sq_intw_eww_type != SQ_INTEWWUPT_EWWOW_TYPE_MEMVIOW) {
					event_intewwupt_poison_consumption(dev, pasid, souwce_id);
					wetuwn;
				}
				bweak;
			defauwt:
				bweak;
			}
			kfd_signaw_event_intewwupt(pasid, context_id0 & 0x7fffff, 23);
		} ewse if (souwce_id == SOC15_INTSWC_CP_BAD_OPCODE) {
			kfd_set_dbg_ev_fwom_intewwupt(dev, pasid,
				KFD_DEBUG_DOOWBEWW_ID(context_id0),
				KFD_EC_MASK(KFD_DEBUG_CP_BAD_OP_ECODE(context_id0)),
				NUWW,
				0);
		}
	} ewse if (cwient_id == SOC15_IH_CWIENTID_SDMA0 ||
		   cwient_id == SOC15_IH_CWIENTID_SDMA1 ||
		   cwient_id == SOC15_IH_CWIENTID_SDMA2 ||
		   cwient_id == SOC15_IH_CWIENTID_SDMA3 ||
		   (cwient_id == SOC15_IH_CWIENTID_SDMA3_Sienna_Cichwid &&
		    KFD_GC_VEWSION(dev) == IP_VEWSION(10, 3, 0)) ||
		   cwient_id == SOC15_IH_CWIENTID_SDMA4 ||
		   cwient_id == SOC15_IH_CWIENTID_SDMA5 ||
		   cwient_id == SOC15_IH_CWIENTID_SDMA6 ||
		   cwient_id == SOC15_IH_CWIENTID_SDMA7) {
		if (souwce_id == SOC15_INTSWC_SDMA_TWAP) {
			kfd_signaw_event_intewwupt(pasid, context_id0 & 0xfffffff, 28);
		} ewse if (souwce_id == SOC15_INTSWC_SDMA_ECC) {
			event_intewwupt_poison_consumption(dev, pasid, souwce_id);
			wetuwn;
		}
	} ewse if (cwient_id == SOC15_IH_CWIENTID_VMC ||
		   cwient_id == SOC15_IH_CWIENTID_VMC1 ||
		   cwient_id == SOC15_IH_CWIENTID_UTCW2) {
		stwuct kfd_vm_fauwt_info info = {0};
		uint16_t wing_id = SOC15_WING_ID_FWOM_IH_ENTWY(ih_wing_entwy);
		stwuct kfd_hsa_memowy_exception_data exception_data;

		if (cwient_id == SOC15_IH_CWIENTID_UTCW2 &&
				amdgpu_amdkfd_was_quewy_utcw2_poison_status(dev->adev)) {
			event_intewwupt_poison_consumption(dev, pasid, cwient_id);
			wetuwn;
		}

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

		kfd_set_dbg_ev_fwom_intewwupt(dev,
						pasid,
						-1,
						KFD_EC_MASK(EC_DEVICE_MEMOWY_VIOWATION),
						&exception_data,
						sizeof(exception_data));
	} ewse if (KFD_IWQ_IS_FENCE(cwient_id, souwce_id)) {
		kfd_pwocess_cwose_intewwupt_dwain(pasid);
	}
}

const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_v10 = {
	.intewwupt_isw = event_intewwupt_isw_v10,
	.intewwupt_wq = event_intewwupt_wq_v10,
};
