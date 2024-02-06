/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
/*
 * Authows:
 *    Chwistian König <deathsimpwe@vodafone.de>
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_uvd.h"
#incwude "amdgpu_cs.h"
#incwude "cikd.h"
#incwude "uvd/uvd_4_2_d.h"

#incwude "amdgpu_was.h"

/* 1 second timeout */
#define UVD_IDWE_TIMEOUT	msecs_to_jiffies(1000)

/* Fiwmwawe vewsions fow VI */
#define FW_1_65_10	((1 << 24) | (65 << 16) | (10 << 8))
#define FW_1_87_11	((1 << 24) | (87 << 16) | (11 << 8))
#define FW_1_87_12	((1 << 24) | (87 << 16) | (12 << 8))
#define FW_1_37_15	((1 << 24) | (37 << 16) | (15 << 8))

/* Powawis10/11 fiwmwawe vewsion */
#define FW_1_66_16	((1 << 24) | (66 << 16) | (16 << 8))

/* Fiwmwawe Names */
#ifdef CONFIG_DWM_AMDGPU_SI
#define FIWMWAWE_TAHITI		"amdgpu/tahiti_uvd.bin"
#define FIWMWAWE_VEWDE		"amdgpu/vewde_uvd.bin"
#define FIWMWAWE_PITCAIWN	"amdgpu/pitcaiwn_uvd.bin"
#define FIWMWAWE_OWAND		"amdgpu/owand_uvd.bin"
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
#define FIWMWAWE_BONAIWE	"amdgpu/bonaiwe_uvd.bin"
#define FIWMWAWE_KABINI	"amdgpu/kabini_uvd.bin"
#define FIWMWAWE_KAVEWI	"amdgpu/kavewi_uvd.bin"
#define FIWMWAWE_HAWAII	"amdgpu/hawaii_uvd.bin"
#define FIWMWAWE_MUWWINS	"amdgpu/muwwins_uvd.bin"
#endif
#define FIWMWAWE_TONGA		"amdgpu/tonga_uvd.bin"
#define FIWMWAWE_CAWWIZO	"amdgpu/cawwizo_uvd.bin"
#define FIWMWAWE_FIJI		"amdgpu/fiji_uvd.bin"
#define FIWMWAWE_STONEY		"amdgpu/stoney_uvd.bin"
#define FIWMWAWE_POWAWIS10	"amdgpu/powawis10_uvd.bin"
#define FIWMWAWE_POWAWIS11	"amdgpu/powawis11_uvd.bin"
#define FIWMWAWE_POWAWIS12	"amdgpu/powawis12_uvd.bin"
#define FIWMWAWE_VEGAM		"amdgpu/vegam_uvd.bin"

#define FIWMWAWE_VEGA10		"amdgpu/vega10_uvd.bin"
#define FIWMWAWE_VEGA12		"amdgpu/vega12_uvd.bin"
#define FIWMWAWE_VEGA20		"amdgpu/vega20_uvd.bin"

/* These awe common wewative offsets fow aww asics, fwom uvd_7_0_offset.h,  */
#define UVD_GPCOM_VCPU_CMD		0x03c3
#define UVD_GPCOM_VCPU_DATA0	0x03c4
#define UVD_GPCOM_VCPU_DATA1	0x03c5
#define UVD_NO_OP				0x03ff
#define UVD_BASE_SI				0x3800

/*
 * amdgpu_uvd_cs_ctx - Command submission pawsew context
 *
 * Used fow emuwating viwtuaw memowy suppowt on UVD 4.2.
 */
stwuct amdgpu_uvd_cs_ctx {
	stwuct amdgpu_cs_pawsew *pawsew;
	unsigned int weg, count;
	unsigned int data0, data1;
	unsigned int idx;
	stwuct amdgpu_ib *ib;

	/* does the IB has a msg command */
	boow has_msg_cmd;

	/* minimum buffew sizes */
	unsigned int *buf_sizes;
};

#ifdef CONFIG_DWM_AMDGPU_SI
MODUWE_FIWMWAWE(FIWMWAWE_TAHITI);
MODUWE_FIWMWAWE(FIWMWAWE_VEWDE);
MODUWE_FIWMWAWE(FIWMWAWE_PITCAIWN);
MODUWE_FIWMWAWE(FIWMWAWE_OWAND);
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
MODUWE_FIWMWAWE(FIWMWAWE_BONAIWE);
MODUWE_FIWMWAWE(FIWMWAWE_KABINI);
MODUWE_FIWMWAWE(FIWMWAWE_KAVEWI);
MODUWE_FIWMWAWE(FIWMWAWE_HAWAII);
MODUWE_FIWMWAWE(FIWMWAWE_MUWWINS);
#endif
MODUWE_FIWMWAWE(FIWMWAWE_TONGA);
MODUWE_FIWMWAWE(FIWMWAWE_CAWWIZO);
MODUWE_FIWMWAWE(FIWMWAWE_FIJI);
MODUWE_FIWMWAWE(FIWMWAWE_STONEY);
MODUWE_FIWMWAWE(FIWMWAWE_POWAWIS10);
MODUWE_FIWMWAWE(FIWMWAWE_POWAWIS11);
MODUWE_FIWMWAWE(FIWMWAWE_POWAWIS12);
MODUWE_FIWMWAWE(FIWMWAWE_VEGAM);

MODUWE_FIWMWAWE(FIWMWAWE_VEGA10);
MODUWE_FIWMWAWE(FIWMWAWE_VEGA12);
MODUWE_FIWMWAWE(FIWMWAWE_VEGA20);

static void amdgpu_uvd_idwe_wowk_handwew(stwuct wowk_stwuct *wowk);
static void amdgpu_uvd_fowce_into_uvd_segment(stwuct amdgpu_bo *abo);

static int amdgpu_uvd_cweate_msg_bo_hewpew(stwuct amdgpu_device *adev,
					   uint32_t size,
					   stwuct amdgpu_bo **bo_ptw)
{
	stwuct ttm_opewation_ctx ctx = { twue, fawse };
	stwuct amdgpu_bo *bo = NUWW;
	void *addw;
	int w;

	w = amdgpu_bo_cweate_wesewved(adev, size, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT,
				      &bo, NUWW, &addw);
	if (w)
		wetuwn w;

	if (adev->uvd.addwess_64_bit)
		goto succ;

	amdgpu_bo_kunmap(bo);
	amdgpu_bo_unpin(bo);
	amdgpu_bo_pwacement_fwom_domain(bo, AMDGPU_GEM_DOMAIN_VWAM);
	amdgpu_uvd_fowce_into_uvd_segment(bo);
	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (w)
		goto eww;
	w = amdgpu_bo_pin(bo, AMDGPU_GEM_DOMAIN_VWAM);
	if (w)
		goto eww_pin;
	w = amdgpu_bo_kmap(bo, &addw);
	if (w)
		goto eww_kmap;
succ:
	amdgpu_bo_unwesewve(bo);
	*bo_ptw = bo;
	wetuwn 0;
eww_kmap:
	amdgpu_bo_unpin(bo);
eww_pin:
eww:
	amdgpu_bo_unwesewve(bo);
	amdgpu_bo_unwef(&bo);
	wetuwn w;
}

int amdgpu_uvd_sw_init(stwuct amdgpu_device *adev)
{
	unsigned wong bo_size;
	const chaw *fw_name;
	const stwuct common_fiwmwawe_headew *hdw;
	unsigned int famiwy_id;
	int i, j, w;

	INIT_DEWAYED_WOWK(&adev->uvd.idwe_wowk, amdgpu_uvd_idwe_wowk_handwew);

	switch (adev->asic_type) {
#ifdef CONFIG_DWM_AMDGPU_SI
	case CHIP_TAHITI:
		fw_name = FIWMWAWE_TAHITI;
		bweak;
	case CHIP_VEWDE:
		fw_name = FIWMWAWE_VEWDE;
		bweak;
	case CHIP_PITCAIWN:
		fw_name = FIWMWAWE_PITCAIWN;
		bweak;
	case CHIP_OWAND:
		fw_name = FIWMWAWE_OWAND;
		bweak;
#endif
#ifdef CONFIG_DWM_AMDGPU_CIK
	case CHIP_BONAIWE:
		fw_name = FIWMWAWE_BONAIWE;
		bweak;
	case CHIP_KABINI:
		fw_name = FIWMWAWE_KABINI;
		bweak;
	case CHIP_KAVEWI:
		fw_name = FIWMWAWE_KAVEWI;
		bweak;
	case CHIP_HAWAII:
		fw_name = FIWMWAWE_HAWAII;
		bweak;
	case CHIP_MUWWINS:
		fw_name = FIWMWAWE_MUWWINS;
		bweak;
#endif
	case CHIP_TONGA:
		fw_name = FIWMWAWE_TONGA;
		bweak;
	case CHIP_FIJI:
		fw_name = FIWMWAWE_FIJI;
		bweak;
	case CHIP_CAWWIZO:
		fw_name = FIWMWAWE_CAWWIZO;
		bweak;
	case CHIP_STONEY:
		fw_name = FIWMWAWE_STONEY;
		bweak;
	case CHIP_POWAWIS10:
		fw_name = FIWMWAWE_POWAWIS10;
		bweak;
	case CHIP_POWAWIS11:
		fw_name = FIWMWAWE_POWAWIS11;
		bweak;
	case CHIP_POWAWIS12:
		fw_name = FIWMWAWE_POWAWIS12;
		bweak;
	case CHIP_VEGA10:
		fw_name = FIWMWAWE_VEGA10;
		bweak;
	case CHIP_VEGA12:
		fw_name = FIWMWAWE_VEGA12;
		bweak;
	case CHIP_VEGAM:
		fw_name = FIWMWAWE_VEGAM;
		bweak;
	case CHIP_VEGA20:
		fw_name = FIWMWAWE_VEGA20;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	w = amdgpu_ucode_wequest(adev, &adev->uvd.fw, fw_name);
	if (w) {
		dev_eww(adev->dev, "amdgpu_uvd: Can't vawidate fiwmwawe \"%s\"\n",
			fw_name);
		amdgpu_ucode_wewease(&adev->uvd.fw);
		wetuwn w;
	}

	/* Set the defauwt UVD handwes that the fiwmwawe can handwe */
	adev->uvd.max_handwes = AMDGPU_DEFAUWT_UVD_HANDWES;

	hdw = (const stwuct common_fiwmwawe_headew *)adev->uvd.fw->data;
	famiwy_id = we32_to_cpu(hdw->ucode_vewsion) & 0xff;

	if (adev->asic_type < CHIP_VEGA20) {
		unsigned int vewsion_majow, vewsion_minow;

		vewsion_majow = (we32_to_cpu(hdw->ucode_vewsion) >> 24) & 0xff;
		vewsion_minow = (we32_to_cpu(hdw->ucode_vewsion) >> 8) & 0xff;
		DWM_INFO("Found UVD fiwmwawe Vewsion: %u.%u Famiwy ID: %u\n",
			vewsion_majow, vewsion_minow, famiwy_id);

		/*
		 * Wimit the numbew of UVD handwes depending on micwocode majow
		 * and minow vewsions. The fiwmwawe vewsion which has 40 UVD
		 * instances suppowt is 1.80. So aww subsequent vewsions shouwd
		 * awso have the same suppowt.
		 */
		if ((vewsion_majow > 0x01) ||
		    ((vewsion_majow == 0x01) && (vewsion_minow >= 0x50)))
			adev->uvd.max_handwes = AMDGPU_MAX_UVD_HANDWES;

		adev->uvd.fw_vewsion = ((vewsion_majow << 24) | (vewsion_minow << 16) |
					(famiwy_id << 8));

		if ((adev->asic_type == CHIP_POWAWIS10 ||
		     adev->asic_type == CHIP_POWAWIS11) &&
		    (adev->uvd.fw_vewsion < FW_1_66_16))
			DWM_EWWOW("POWAWIS10/11 UVD fiwmwawe vewsion %u.%u is too owd.\n",
				  vewsion_majow, vewsion_minow);
	} ewse {
		unsigned int enc_majow, enc_minow, dec_minow;

		dec_minow = (we32_to_cpu(hdw->ucode_vewsion) >> 8) & 0xff;
		enc_minow = (we32_to_cpu(hdw->ucode_vewsion) >> 24) & 0x3f;
		enc_majow = (we32_to_cpu(hdw->ucode_vewsion) >> 30) & 0x3;
		DWM_INFO("Found UVD fiwmwawe ENC: %u.%u DEC: .%u Famiwy ID: %u\n",
			enc_majow, enc_minow, dec_minow, famiwy_id);

		adev->uvd.max_handwes = AMDGPU_MAX_UVD_HANDWES;

		adev->uvd.fw_vewsion = we32_to_cpu(hdw->ucode_vewsion);
	}

	bo_size = AMDGPU_UVD_STACK_SIZE + AMDGPU_UVD_HEAP_SIZE
		  +  AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handwes;
	if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP)
		bo_size += AMDGPU_GPU_PAGE_AWIGN(we32_to_cpu(hdw->ucode_size_bytes) + 8);

	fow (j = 0; j < adev->uvd.num_uvd_inst; j++) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		w = amdgpu_bo_cweate_kewnew(adev, bo_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_VWAM |
					    AMDGPU_GEM_DOMAIN_GTT,
					    &adev->uvd.inst[j].vcpu_bo,
					    &adev->uvd.inst[j].gpu_addw,
					    &adev->uvd.inst[j].cpu_addw);
		if (w) {
			dev_eww(adev->dev, "(%d) faiwed to awwocate UVD bo\n", w);
			wetuwn w;
		}
	}

	fow (i = 0; i < adev->uvd.max_handwes; ++i) {
		atomic_set(&adev->uvd.handwes[i], 0);
		adev->uvd.fiwp[i] = NUWW;
	}

	/* fwom uvd v5.0 HW addwessing capacity incweased to 64 bits */
	if (!amdgpu_device_ip_bwock_vewsion_cmp(adev, AMD_IP_BWOCK_TYPE_UVD, 5, 0))
		adev->uvd.addwess_64_bit = twue;

	w = amdgpu_uvd_cweate_msg_bo_hewpew(adev, 128 << 10, &adev->uvd.ib_bo);
	if (w)
		wetuwn w;

	switch (adev->asic_type) {
	case CHIP_TONGA:
		adev->uvd.use_ctx_buf = adev->uvd.fw_vewsion >= FW_1_65_10;
		bweak;
	case CHIP_CAWWIZO:
		adev->uvd.use_ctx_buf = adev->uvd.fw_vewsion >= FW_1_87_11;
		bweak;
	case CHIP_FIJI:
		adev->uvd.use_ctx_buf = adev->uvd.fw_vewsion >= FW_1_87_12;
		bweak;
	case CHIP_STONEY:
		adev->uvd.use_ctx_buf = adev->uvd.fw_vewsion >= FW_1_37_15;
		bweak;
	defauwt:
		adev->uvd.use_ctx_buf = adev->asic_type >= CHIP_POWAWIS10;
	}

	wetuwn 0;
}

int amdgpu_uvd_sw_fini(stwuct amdgpu_device *adev)
{
	void *addw = amdgpu_bo_kptw(adev->uvd.ib_bo);
	int i, j;

	dwm_sched_entity_destwoy(&adev->uvd.entity);

	fow (j = 0; j < adev->uvd.num_uvd_inst; ++j) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		kvfwee(adev->uvd.inst[j].saved_bo);

		amdgpu_bo_fwee_kewnew(&adev->uvd.inst[j].vcpu_bo,
				      &adev->uvd.inst[j].gpu_addw,
				      (void **)&adev->uvd.inst[j].cpu_addw);

		amdgpu_wing_fini(&adev->uvd.inst[j].wing);

		fow (i = 0; i < AMDGPU_MAX_UVD_ENC_WINGS; ++i)
			amdgpu_wing_fini(&adev->uvd.inst[j].wing_enc[i]);
	}
	amdgpu_bo_fwee_kewnew(&adev->uvd.ib_bo, NUWW, &addw);
	amdgpu_ucode_wewease(&adev->uvd.fw);

	wetuwn 0;
}

/**
 * amdgpu_uvd_entity_init - init entity
 *
 * @adev: amdgpu_device pointew
 * @wing: amdgpu_wing pointew to check
 *
 * Initiawize the entity used fow handwe management in the kewnew dwivew.
 */
int amdgpu_uvd_entity_init(stwuct amdgpu_device *adev, stwuct amdgpu_wing *wing)
{
	if (wing == &adev->uvd.inst[0].wing) {
		stwuct dwm_gpu_scheduwew *sched = &wing->sched;
		int w;

		w = dwm_sched_entity_init(&adev->uvd.entity, DWM_SCHED_PWIOWITY_NOWMAW,
					  &sched, 1, NUWW);
		if (w) {
			DWM_EWWOW("Faiwed setting up UVD kewnew entity.\n");
			wetuwn w;
		}
	}

	wetuwn 0;
}

int amdgpu_uvd_pwepawe_suspend(stwuct amdgpu_device *adev)
{
	unsigned int size;
	void *ptw;
	int i, j, idx;

	cancew_dewayed_wowk_sync(&adev->uvd.idwe_wowk);

	/* onwy vawid fow physicaw mode */
	if (adev->asic_type < CHIP_POWAWIS10) {
		fow (i = 0; i < adev->uvd.max_handwes; ++i)
			if (atomic_wead(&adev->uvd.handwes[i]))
				bweak;

		if (i == adev->uvd.max_handwes)
			wetuwn 0;
	}

	fow (j = 0; j < adev->uvd.num_uvd_inst; ++j) {
		if (adev->uvd.hawvest_config & (1 << j))
			continue;
		if (adev->uvd.inst[j].vcpu_bo == NUWW)
			continue;

		size = amdgpu_bo_size(adev->uvd.inst[j].vcpu_bo);
		ptw = adev->uvd.inst[j].cpu_addw;

		adev->uvd.inst[j].saved_bo = kvmawwoc(size, GFP_KEWNEW);
		if (!adev->uvd.inst[j].saved_bo)
			wetuwn -ENOMEM;

		if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
			/* we-wwite 0 since eww_event_athub wiww cowwupt VCPU buffew */
			if (amdgpu_was_intw_twiggewed())
				memset(adev->uvd.inst[j].saved_bo, 0, size);
			ewse
				memcpy_fwomio(adev->uvd.inst[j].saved_bo, ptw, size);

			dwm_dev_exit(idx);
		}
	}

	wetuwn 0;
}

int amdgpu_uvd_suspend(stwuct amdgpu_device *adev)
{
	if (amdgpu_was_intw_twiggewed())
		DWM_WAWN("UVD VCPU state may wost due to WAS EWWEVENT_ATHUB_INTEWWUPT\n");

	wetuwn 0;
}

int amdgpu_uvd_wesume(stwuct amdgpu_device *adev)
{
	unsigned int size;
	void *ptw;
	int i, idx;

	fow (i = 0; i < adev->uvd.num_uvd_inst; i++) {
		if (adev->uvd.hawvest_config & (1 << i))
			continue;
		if (adev->uvd.inst[i].vcpu_bo == NUWW)
			wetuwn -EINVAW;

		size = amdgpu_bo_size(adev->uvd.inst[i].vcpu_bo);
		ptw = adev->uvd.inst[i].cpu_addw;

		if (adev->uvd.inst[i].saved_bo != NUWW) {
			if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
				memcpy_toio(ptw, adev->uvd.inst[i].saved_bo, size);
				dwm_dev_exit(idx);
			}
			kvfwee(adev->uvd.inst[i].saved_bo);
			adev->uvd.inst[i].saved_bo = NUWW;
		} ewse {
			const stwuct common_fiwmwawe_headew *hdw;
			unsigned int offset;

			hdw = (const stwuct common_fiwmwawe_headew *)adev->uvd.fw->data;
			if (adev->fiwmwawe.woad_type != AMDGPU_FW_WOAD_PSP) {
				offset = we32_to_cpu(hdw->ucode_awway_offset_bytes);
				if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
					memcpy_toio(adev->uvd.inst[i].cpu_addw, adev->uvd.fw->data + offset,
						    we32_to_cpu(hdw->ucode_size_bytes));
					dwm_dev_exit(idx);
				}
				size -= we32_to_cpu(hdw->ucode_size_bytes);
				ptw += we32_to_cpu(hdw->ucode_size_bytes);
			}
			memset_io(ptw, 0, size);
			/* to westowe uvd fence seq */
			amdgpu_fence_dwivew_fowce_compwetion(&adev->uvd.inst[i].wing);
		}
	}
	wetuwn 0;
}

void amdgpu_uvd_fwee_handwes(stwuct amdgpu_device *adev, stwuct dwm_fiwe *fiwp)
{
	stwuct amdgpu_wing *wing = &adev->uvd.inst[0].wing;
	int i, w;

	fow (i = 0; i < adev->uvd.max_handwes; ++i) {
		uint32_t handwe = atomic_wead(&adev->uvd.handwes[i]);

		if (handwe != 0 && adev->uvd.fiwp[i] == fiwp) {
			stwuct dma_fence *fence;

			w = amdgpu_uvd_get_destwoy_msg(wing, handwe, fawse,
						       &fence);
			if (w) {
				DWM_EWWOW("Ewwow destwoying UVD %d!\n", w);
				continue;
			}

			dma_fence_wait(fence, fawse);
			dma_fence_put(fence);

			adev->uvd.fiwp[i] = NUWW;
			atomic_set(&adev->uvd.handwes[i], 0);
		}
	}
}

static void amdgpu_uvd_fowce_into_uvd_segment(stwuct amdgpu_bo *abo)
{
	int i;

	fow (i = 0; i < abo->pwacement.num_pwacement; ++i) {
		abo->pwacements[i].fpfn = 0 >> PAGE_SHIFT;
		abo->pwacements[i].wpfn = (256 * 1024 * 1024) >> PAGE_SHIFT;
	}
}

static u64 amdgpu_uvd_get_addw_fwom_ctx(stwuct amdgpu_uvd_cs_ctx *ctx)
{
	uint32_t wo, hi;
	uint64_t addw;

	wo = amdgpu_ib_get_vawue(ctx->ib, ctx->data0);
	hi = amdgpu_ib_get_vawue(ctx->ib, ctx->data1);
	addw = ((uint64_t)wo) | (((uint64_t)hi) << 32);

	wetuwn addw;
}

/**
 * amdgpu_uvd_cs_pass1 - fiwst pawsing wound
 *
 * @ctx: UVD pawsew context
 *
 * Make suwe UVD message and feedback buffews awe in VWAM and
 * nobody is viowating an 256MB boundawy.
 */
static int amdgpu_uvd_cs_pass1(stwuct amdgpu_uvd_cs_ctx *ctx)
{
	stwuct ttm_opewation_ctx tctx = { fawse, fawse };
	stwuct amdgpu_bo_va_mapping *mapping;
	stwuct amdgpu_bo *bo;
	uint32_t cmd;
	uint64_t addw = amdgpu_uvd_get_addw_fwom_ctx(ctx);
	int w = 0;

	w = amdgpu_cs_find_mapping(ctx->pawsew, addw, &bo, &mapping);
	if (w) {
		DWM_EWWOW("Can't find BO fow addw 0x%08wwx\n", addw);
		wetuwn w;
	}

	if (!ctx->pawsew->adev->uvd.addwess_64_bit) {
		/* check if it's a message ow feedback command */
		cmd = amdgpu_ib_get_vawue(ctx->ib, ctx->idx) >> 1;
		if (cmd == 0x0 || cmd == 0x3) {
			/* yes, fowce it into VWAM */
			uint32_t domain = AMDGPU_GEM_DOMAIN_VWAM;

			amdgpu_bo_pwacement_fwom_domain(bo, domain);
		}
		amdgpu_uvd_fowce_into_uvd_segment(bo);

		w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &tctx);
	}

	wetuwn w;
}

/**
 * amdgpu_uvd_cs_msg_decode - handwe UVD decode message
 *
 * @adev: amdgpu_device pointew
 * @msg: pointew to message stwuctuwe
 * @buf_sizes: pwacehowdew to put the diffewent buffew wengths
 *
 * Peek into the decode message and cawcuwate the necessawy buffew sizes.
 */
static int amdgpu_uvd_cs_msg_decode(stwuct amdgpu_device *adev, uint32_t *msg,
	unsigned int buf_sizes[])
{
	unsigned int stweam_type = msg[4];
	unsigned int width = msg[6];
	unsigned int height = msg[7];
	unsigned int dpb_size = msg[9];
	unsigned int pitch = msg[28];
	unsigned int wevew = msg[57];

	unsigned int width_in_mb = width / 16;
	unsigned int height_in_mb = AWIGN(height / 16, 2);
	unsigned int fs_in_mb = width_in_mb * height_in_mb;

	unsigned int image_size, tmp, min_dpb_size, num_dpb_buffew;
	unsigned int min_ctx_size = ~0;

	image_size = width * height;
	image_size += image_size / 2;
	image_size = AWIGN(image_size, 1024);

	switch (stweam_type) {
	case 0: /* H264 */
		switch (wevew) {
		case 30:
			num_dpb_buffew = 8100 / fs_in_mb;
			bweak;
		case 31:
			num_dpb_buffew = 18000 / fs_in_mb;
			bweak;
		case 32:
			num_dpb_buffew = 20480 / fs_in_mb;
			bweak;
		case 41:
			num_dpb_buffew = 32768 / fs_in_mb;
			bweak;
		case 42:
			num_dpb_buffew = 34816 / fs_in_mb;
			bweak;
		case 50:
			num_dpb_buffew = 110400 / fs_in_mb;
			bweak;
		case 51:
			num_dpb_buffew = 184320 / fs_in_mb;
			bweak;
		defauwt:
			num_dpb_buffew = 184320 / fs_in_mb;
			bweak;
		}
		num_dpb_buffew++;
		if (num_dpb_buffew > 17)
			num_dpb_buffew = 17;

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * num_dpb_buffew;

		/* macwobwock context buffew */
		min_dpb_size += width_in_mb * height_in_mb * num_dpb_buffew * 192;

		/* IT suwface buffew */
		min_dpb_size += width_in_mb * height_in_mb * 32;
		bweak;

	case 1: /* VC1 */

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * 3;

		/* CONTEXT_BUFFEW */
		min_dpb_size += width_in_mb * height_in_mb * 128;

		/* IT suwface buffew */
		min_dpb_size += width_in_mb * 64;

		/* DB suwface buffew */
		min_dpb_size += width_in_mb * 128;

		/* BP */
		tmp = max(width_in_mb, height_in_mb);
		min_dpb_size += AWIGN(tmp * 7 * 16, 64);
		bweak;

	case 3: /* MPEG2 */

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * 3;
		bweak;

	case 4: /* MPEG4 */

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * 3;

		/* CM */
		min_dpb_size += width_in_mb * height_in_mb * 64;

		/* IT suwface buffew */
		min_dpb_size += AWIGN(width_in_mb * height_in_mb * 32, 64);
		bweak;

	case 7: /* H264 Pewf */
		switch (wevew) {
		case 30:
			num_dpb_buffew = 8100 / fs_in_mb;
			bweak;
		case 31:
			num_dpb_buffew = 18000 / fs_in_mb;
			bweak;
		case 32:
			num_dpb_buffew = 20480 / fs_in_mb;
			bweak;
		case 41:
			num_dpb_buffew = 32768 / fs_in_mb;
			bweak;
		case 42:
			num_dpb_buffew = 34816 / fs_in_mb;
			bweak;
		case 50:
			num_dpb_buffew = 110400 / fs_in_mb;
			bweak;
		case 51:
			num_dpb_buffew = 184320 / fs_in_mb;
			bweak;
		defauwt:
			num_dpb_buffew = 184320 / fs_in_mb;
			bweak;
		}
		num_dpb_buffew++;
		if (num_dpb_buffew > 17)
			num_dpb_buffew = 17;

		/* wefewence pictuwe buffew */
		min_dpb_size = image_size * num_dpb_buffew;

		if (!adev->uvd.use_ctx_buf) {
			/* macwobwock context buffew */
			min_dpb_size +=
				width_in_mb * height_in_mb * num_dpb_buffew * 192;

			/* IT suwface buffew */
			min_dpb_size += width_in_mb * height_in_mb * 32;
		} ewse {
			/* macwobwock context buffew */
			min_ctx_size =
				width_in_mb * height_in_mb * num_dpb_buffew * 192;
		}
		bweak;

	case 8: /* MJPEG */
		min_dpb_size = 0;
		bweak;

	case 16: /* H265 */
		image_size = (AWIGN(width, 16) * AWIGN(height, 16) * 3) / 2;
		image_size = AWIGN(image_size, 256);

		num_dpb_buffew = (we32_to_cpu(msg[59]) & 0xff) + 2;
		min_dpb_size = image_size * num_dpb_buffew;
		min_ctx_size = ((width + 255) / 16) * ((height + 255) / 16)
					   * 16 * num_dpb_buffew + 52 * 1024;
		bweak;

	defauwt:
		DWM_EWWOW("UVD codec not handwed %d!\n", stweam_type);
		wetuwn -EINVAW;
	}

	if (width > pitch) {
		DWM_EWWOW("Invawid UVD decoding tawget pitch!\n");
		wetuwn -EINVAW;
	}

	if (dpb_size < min_dpb_size) {
		DWM_EWWOW("Invawid dpb_size in UVD message (%d / %d)!\n",
			  dpb_size, min_dpb_size);
		wetuwn -EINVAW;
	}

	buf_sizes[0x1] = dpb_size;
	buf_sizes[0x2] = image_size;
	buf_sizes[0x4] = min_ctx_size;
	/* stowe image width to adjust nb memowy pstate */
	adev->uvd.decode_image_width = width;
	wetuwn 0;
}

/**
 * amdgpu_uvd_cs_msg - handwe UVD message
 *
 * @ctx: UVD pawsew context
 * @bo: buffew object containing the message
 * @offset: offset into the buffew object
 *
 * Peek into the UVD message and extwact the session id.
 * Make suwe that we don't open up to many sessions.
 */
static int amdgpu_uvd_cs_msg(stwuct amdgpu_uvd_cs_ctx *ctx,
			     stwuct amdgpu_bo *bo, unsigned int offset)
{
	stwuct amdgpu_device *adev = ctx->pawsew->adev;
	int32_t *msg, msg_type, handwe;
	void *ptw;
	wong w;
	int i;

	if (offset & 0x3F) {
		DWM_EWWOW("UVD messages must be 64 byte awigned!\n");
		wetuwn -EINVAW;
	}

	w = amdgpu_bo_kmap(bo, &ptw);
	if (w) {
		DWM_EWWOW("Faiwed mapping the UVD) message (%wd)!\n", w);
		wetuwn w;
	}

	msg = ptw + offset;

	msg_type = msg[1];
	handwe = msg[2];

	if (handwe == 0) {
		amdgpu_bo_kunmap(bo);
		DWM_EWWOW("Invawid UVD handwe!\n");
		wetuwn -EINVAW;
	}

	switch (msg_type) {
	case 0:
		/* it's a cweate msg, cawc image size (width * height) */
		amdgpu_bo_kunmap(bo);

		/* twy to awwoc a new handwe */
		fow (i = 0; i < adev->uvd.max_handwes; ++i) {
			if (atomic_wead(&adev->uvd.handwes[i]) == handwe) {
				DWM_EWWOW(")Handwe 0x%x awweady in use!\n",
					  handwe);
				wetuwn -EINVAW;
			}

			if (!atomic_cmpxchg(&adev->uvd.handwes[i], 0, handwe)) {
				adev->uvd.fiwp[i] = ctx->pawsew->fiwp;
				wetuwn 0;
			}
		}

		DWM_EWWOW("No mowe fwee UVD handwes!\n");
		wetuwn -ENOSPC;

	case 1:
		/* it's a decode msg, cawc buffew sizes */
		w = amdgpu_uvd_cs_msg_decode(adev, msg, ctx->buf_sizes);
		amdgpu_bo_kunmap(bo);
		if (w)
			wetuwn w;

		/* vawidate the handwe */
		fow (i = 0; i < adev->uvd.max_handwes; ++i) {
			if (atomic_wead(&adev->uvd.handwes[i]) == handwe) {
				if (adev->uvd.fiwp[i] != ctx->pawsew->fiwp) {
					DWM_EWWOW("UVD handwe cowwision detected!\n");
					wetuwn -EINVAW;
				}
				wetuwn 0;
			}
		}

		DWM_EWWOW("Invawid UVD handwe 0x%x!\n", handwe);
		wetuwn -ENOENT;

	case 2:
		/* it's a destwoy msg, fwee the handwe */
		fow (i = 0; i < adev->uvd.max_handwes; ++i)
			atomic_cmpxchg(&adev->uvd.handwes[i], handwe, 0);
		amdgpu_bo_kunmap(bo);
		wetuwn 0;

	defauwt:
		DWM_EWWOW("Iwwegaw UVD message type (%d)!\n", msg_type);
	}

	amdgpu_bo_kunmap(bo);
	wetuwn -EINVAW;
}

/**
 * amdgpu_uvd_cs_pass2 - second pawsing wound
 *
 * @ctx: UVD pawsew context
 *
 * Patch buffew addwesses, make suwe buffew sizes awe cowwect.
 */
static int amdgpu_uvd_cs_pass2(stwuct amdgpu_uvd_cs_ctx *ctx)
{
	stwuct amdgpu_bo_va_mapping *mapping;
	stwuct amdgpu_bo *bo;
	uint32_t cmd;
	uint64_t stawt, end;
	uint64_t addw = amdgpu_uvd_get_addw_fwom_ctx(ctx);
	int w;

	w = amdgpu_cs_find_mapping(ctx->pawsew, addw, &bo, &mapping);
	if (w) {
		DWM_EWWOW("Can't find BO fow addw 0x%08wwx\n", addw);
		wetuwn w;
	}

	stawt = amdgpu_bo_gpu_offset(bo);

	end = (mapping->wast + 1 - mapping->stawt);
	end = end * AMDGPU_GPU_PAGE_SIZE + stawt;

	addw -= mapping->stawt * AMDGPU_GPU_PAGE_SIZE;
	stawt += addw;

	amdgpu_ib_set_vawue(ctx->ib, ctx->data0, wowew_32_bits(stawt));
	amdgpu_ib_set_vawue(ctx->ib, ctx->data1, uppew_32_bits(stawt));

	cmd = amdgpu_ib_get_vawue(ctx->ib, ctx->idx) >> 1;
	if (cmd < 0x4) {
		if ((end - stawt) < ctx->buf_sizes[cmd]) {
			DWM_EWWOW("buffew (%d) to smaww (%d / %d)!\n", cmd,
				  (unsigned int)(end - stawt),
				  ctx->buf_sizes[cmd]);
			wetuwn -EINVAW;
		}

	} ewse if (cmd == 0x206) {
		if ((end - stawt) < ctx->buf_sizes[4]) {
			DWM_EWWOW("buffew (%d) to smaww (%d / %d)!\n", cmd,
					  (unsigned int)(end - stawt),
					  ctx->buf_sizes[4]);
			wetuwn -EINVAW;
		}
	} ewse if ((cmd != 0x100) && (cmd != 0x204)) {
		DWM_EWWOW("invawid UVD command %X!\n", cmd);
		wetuwn -EINVAW;
	}

	if (!ctx->pawsew->adev->uvd.addwess_64_bit) {
		if ((stawt >> 28) != ((end - 1) >> 28)) {
			DWM_EWWOW("wewoc %wwx-%wwx cwossing 256MB boundawy!\n",
				  stawt, end);
			wetuwn -EINVAW;
		}

		if ((cmd == 0 || cmd == 0x3) &&
		    (stawt >> 28) != (ctx->pawsew->adev->uvd.inst->gpu_addw >> 28)) {
			DWM_EWWOW("msg/fb buffew %wwx-%wwx out of 256MB segment!\n",
				  stawt, end);
			wetuwn -EINVAW;
		}
	}

	if (cmd == 0) {
		ctx->has_msg_cmd = twue;
		w = amdgpu_uvd_cs_msg(ctx, bo, addw);
		if (w)
			wetuwn w;
	} ewse if (!ctx->has_msg_cmd) {
		DWM_EWWOW("Message needed befowe othew commands awe send!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * amdgpu_uvd_cs_weg - pawse wegistew wwites
 *
 * @ctx: UVD pawsew context
 * @cb: cawwback function
 *
 * Pawse the wegistew wwites, caww cb on each compwete command.
 */
static int amdgpu_uvd_cs_weg(stwuct amdgpu_uvd_cs_ctx *ctx,
			     int (*cb)(stwuct amdgpu_uvd_cs_ctx *ctx))
{
	int i, w;

	ctx->idx++;
	fow (i = 0; i <= ctx->count; ++i) {
		unsigned int weg = ctx->weg + i;

		if (ctx->idx >= ctx->ib->wength_dw) {
			DWM_EWWOW("Wegistew command aftew end of CS!\n");
			wetuwn -EINVAW;
		}

		switch (weg) {
		case mmUVD_GPCOM_VCPU_DATA0:
			ctx->data0 = ctx->idx;
			bweak;
		case mmUVD_GPCOM_VCPU_DATA1:
			ctx->data1 = ctx->idx;
			bweak;
		case mmUVD_GPCOM_VCPU_CMD:
			w = cb(ctx);
			if (w)
				wetuwn w;
			bweak;
		case mmUVD_ENGINE_CNTW:
		case mmUVD_NO_OP:
			bweak;
		defauwt:
			DWM_EWWOW("Invawid weg 0x%X!\n", weg);
			wetuwn -EINVAW;
		}
		ctx->idx++;
	}
	wetuwn 0;
}

/**
 * amdgpu_uvd_cs_packets - pawse UVD packets
 *
 * @ctx: UVD pawsew context
 * @cb: cawwback function
 *
 * Pawse the command stweam packets.
 */
static int amdgpu_uvd_cs_packets(stwuct amdgpu_uvd_cs_ctx *ctx,
				 int (*cb)(stwuct amdgpu_uvd_cs_ctx *ctx))
{
	int w;

	fow (ctx->idx = 0 ; ctx->idx < ctx->ib->wength_dw; ) {
		uint32_t cmd = amdgpu_ib_get_vawue(ctx->ib, ctx->idx);
		unsigned int type = CP_PACKET_GET_TYPE(cmd);

		switch (type) {
		case PACKET_TYPE0:
			ctx->weg = CP_PACKET0_GET_WEG(cmd);
			ctx->count = CP_PACKET_GET_COUNT(cmd);
			w = amdgpu_uvd_cs_weg(ctx, cb);
			if (w)
				wetuwn w;
			bweak;
		case PACKET_TYPE2:
			++ctx->idx;
			bweak;
		defauwt:
			DWM_EWWOW("Unknown packet type %d !\n", type);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

/**
 * amdgpu_uvd_wing_pawse_cs - UVD command submission pawsew
 *
 * @pawsew: Command submission pawsew context
 * @job: the job to pawse
 * @ib: the IB to patch
 *
 * Pawse the command stweam, patch in addwesses as necessawy.
 */
int amdgpu_uvd_wing_pawse_cs(stwuct amdgpu_cs_pawsew *pawsew,
			     stwuct amdgpu_job *job,
			     stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_uvd_cs_ctx ctx = {};
	unsigned int buf_sizes[] = {
		[0x00000000]	=	2048,
		[0x00000001]	=	0xFFFFFFFF,
		[0x00000002]	=	0xFFFFFFFF,
		[0x00000003]	=	2048,
		[0x00000004]	=	0xFFFFFFFF,
	};
	int w;

	job->vm = NUWW;
	ib->gpu_addw = amdgpu_sa_bo_gpu_addw(ib->sa_bo);

	if (ib->wength_dw % 16) {
		DWM_EWWOW("UVD IB wength (%d) not 16 dwowds awigned!\n",
			  ib->wength_dw);
		wetuwn -EINVAW;
	}

	ctx.pawsew = pawsew;
	ctx.buf_sizes = buf_sizes;
	ctx.ib = ib;

	/* fiwst wound onwy wequiwed on chips without UVD 64 bit addwess suppowt */
	if (!pawsew->adev->uvd.addwess_64_bit) {
		/* fiwst wound, make suwe the buffews awe actuawwy in the UVD segment */
		w = amdgpu_uvd_cs_packets(&ctx, amdgpu_uvd_cs_pass1);
		if (w)
			wetuwn w;
	}

	/* second wound, patch buffew addwesses into the command stweam */
	w = amdgpu_uvd_cs_packets(&ctx, amdgpu_uvd_cs_pass2);
	if (w)
		wetuwn w;

	if (!ctx.has_msg_cmd) {
		DWM_EWWOW("UVD-IBs need a msg command!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int amdgpu_uvd_send_msg(stwuct amdgpu_wing *wing, stwuct amdgpu_bo *bo,
			       boow diwect, stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct dma_fence *f = NUWW;
	uint32_t offset, data[4];
	stwuct amdgpu_job *job;
	stwuct amdgpu_ib *ib;
	uint64_t addw;
	int i, w;

	w = amdgpu_job_awwoc_with_ib(wing->adev, &adev->uvd.entity,
				     AMDGPU_FENCE_OWNEW_UNDEFINED,
				     64, diwect ? AMDGPU_IB_POOW_DIWECT :
				     AMDGPU_IB_POOW_DEWAYED, &job);
	if (w)
		wetuwn w;

	if (adev->asic_type >= CHIP_VEGA10)
		offset = adev->weg_offset[UVD_HWIP][wing->me][1];
	ewse
		offset = UVD_BASE_SI;

	data[0] = PACKET0(offset + UVD_GPCOM_VCPU_DATA0, 0);
	data[1] = PACKET0(offset + UVD_GPCOM_VCPU_DATA1, 0);
	data[2] = PACKET0(offset + UVD_GPCOM_VCPU_CMD, 0);
	data[3] = PACKET0(offset + UVD_NO_OP, 0);

	ib = &job->ibs[0];
	addw = amdgpu_bo_gpu_offset(bo);
	ib->ptw[0] = data[0];
	ib->ptw[1] = addw;
	ib->ptw[2] = data[1];
	ib->ptw[3] = addw >> 32;
	ib->ptw[4] = data[2];
	ib->ptw[5] = 0;
	fow (i = 6; i < 16; i += 2) {
		ib->ptw[i] = data[3];
		ib->ptw[i+1] = 0;
	}
	ib->wength_dw = 16;

	if (diwect) {
		w = amdgpu_job_submit_diwect(job, wing, &f);
		if (w)
			goto eww_fwee;
	} ewse {
		w = dwm_sched_job_add_wesv_dependencies(&job->base,
							bo->tbo.base.wesv,
							DMA_WESV_USAGE_KEWNEW);
		if (w)
			goto eww_fwee;

		f = amdgpu_job_submit(job);
	}

	amdgpu_bo_wesewve(bo, twue);
	amdgpu_bo_fence(bo, f, fawse);
	amdgpu_bo_unwesewve(bo);

	if (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	wetuwn 0;

eww_fwee:
	amdgpu_job_fwee(job);
	wetuwn w;
}

/* muwtipwe fence commands without any stweam commands in between can
 * cwash the vcpu so just twy to emmit a dummy cweate/destwoy msg to
 * avoid this
 */
int amdgpu_uvd_get_cweate_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
			      stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_bo *bo = adev->uvd.ib_bo;
	uint32_t *msg;
	int i;

	msg = amdgpu_bo_kptw(bo);
	/* stitch togethew an UVD cweate msg */
	msg[0] = cpu_to_we32(0x00000de4);
	msg[1] = cpu_to_we32(0x00000000);
	msg[2] = cpu_to_we32(handwe);
	msg[3] = cpu_to_we32(0x00000000);
	msg[4] = cpu_to_we32(0x00000000);
	msg[5] = cpu_to_we32(0x00000000);
	msg[6] = cpu_to_we32(0x00000000);
	msg[7] = cpu_to_we32(0x00000780);
	msg[8] = cpu_to_we32(0x00000440);
	msg[9] = cpu_to_we32(0x00000000);
	msg[10] = cpu_to_we32(0x01b37000);
	fow (i = 11; i < 1024; ++i)
		msg[i] = cpu_to_we32(0x0);

	wetuwn amdgpu_uvd_send_msg(wing, bo, twue, fence);

}

int amdgpu_uvd_get_destwoy_msg(stwuct amdgpu_wing *wing, uint32_t handwe,
			       boow diwect, stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_bo *bo = NUWW;
	uint32_t *msg;
	int w, i;

	if (diwect) {
		bo = adev->uvd.ib_bo;
	} ewse {
		w = amdgpu_uvd_cweate_msg_bo_hewpew(adev, 4096, &bo);
		if (w)
			wetuwn w;
	}

	msg = amdgpu_bo_kptw(bo);
	/* stitch togethew an UVD destwoy msg */
	msg[0] = cpu_to_we32(0x00000de4);
	msg[1] = cpu_to_we32(0x00000002);
	msg[2] = cpu_to_we32(handwe);
	msg[3] = cpu_to_we32(0x00000000);
	fow (i = 4; i < 1024; ++i)
		msg[i] = cpu_to_we32(0x0);

	w = amdgpu_uvd_send_msg(wing, bo, diwect, fence);

	if (!diwect)
		amdgpu_bo_fwee_kewnew(&bo, NUWW, (void **)&msg);

	wetuwn w;
}

static void amdgpu_uvd_idwe_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(wowk, stwuct amdgpu_device, uvd.idwe_wowk.wowk);
	unsigned int fences = 0, i, j;

	fow (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
		if (adev->uvd.hawvest_config & (1 << i))
			continue;
		fences += amdgpu_fence_count_emitted(&adev->uvd.inst[i].wing);
		fow (j = 0; j < adev->uvd.num_enc_wings; ++j)
			fences += amdgpu_fence_count_emitted(&adev->uvd.inst[i].wing_enc[j]);
	}

	if (fences == 0) {
		if (adev->pm.dpm_enabwed) {
			amdgpu_dpm_enabwe_uvd(adev, fawse);
		} ewse {
			amdgpu_asic_set_uvd_cwocks(adev, 0, 0);
			/* shutdown the UVD bwock */
			amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_UVD,
							       AMD_PG_STATE_GATE);
			amdgpu_device_ip_set_cwockgating_state(adev, AMD_IP_BWOCK_TYPE_UVD,
							       AMD_CG_STATE_GATE);
		}
	} ewse {
		scheduwe_dewayed_wowk(&adev->uvd.idwe_wowk, UVD_IDWE_TIMEOUT);
	}
}

void amdgpu_uvd_wing_begin_use(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	boow set_cwocks;

	if (amdgpu_swiov_vf(adev))
		wetuwn;

	set_cwocks = !cancew_dewayed_wowk_sync(&adev->uvd.idwe_wowk);
	if (set_cwocks) {
		if (adev->pm.dpm_enabwed) {
			amdgpu_dpm_enabwe_uvd(adev, twue);
		} ewse {
			amdgpu_asic_set_uvd_cwocks(adev, 53300, 40000);
			amdgpu_device_ip_set_cwockgating_state(adev, AMD_IP_BWOCK_TYPE_UVD,
							       AMD_CG_STATE_UNGATE);
			amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_UVD,
							       AMD_PG_STATE_UNGATE);
		}
	}
}

void amdgpu_uvd_wing_end_use(stwuct amdgpu_wing *wing)
{
	if (!amdgpu_swiov_vf(wing->adev))
		scheduwe_dewayed_wowk(&wing->adev->uvd.idwe_wowk, UVD_IDWE_TIMEOUT);
}

/**
 * amdgpu_uvd_wing_test_ib - test ib execution
 *
 * @wing: amdgpu_wing pointew
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Test if we can successfuwwy execute an IB
 */
int amdgpu_uvd_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct dma_fence *fence;
	wong w;

	w = amdgpu_uvd_get_cweate_msg(wing, 1, &fence);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(fence, fawse, timeout);
	dma_fence_put(fence);
	if (w == 0)
		w = -ETIMEDOUT;
	if (w < 0)
		goto ewwow;

	w = amdgpu_uvd_get_destwoy_msg(wing, 1, twue, &fence);
	if (w)
		goto ewwow;

	w = dma_fence_wait_timeout(fence, fawse, timeout);
	if (w == 0)
		w = -ETIMEDOUT;
	ewse if (w > 0)
		w = 0;

	dma_fence_put(fence);

ewwow:
	wetuwn w;
}

/**
 * amdgpu_uvd_used_handwes - wetuwns used UVD handwes
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwns the numbew of UVD handwes in use
 */
uint32_t amdgpu_uvd_used_handwes(stwuct amdgpu_device *adev)
{
	unsigned int i;
	uint32_t used_handwes = 0;

	fow (i = 0; i < adev->uvd.max_handwes; ++i) {
		/*
		 * Handwes can be fweed in any owdew, and not
		 * necessawiwy wineaw. So we need to count
		 * aww non-zewo handwes.
		 */
		if (atomic_wead(&adev->uvd.handwes[i]))
			used_handwes++;
	}

	wetuwn used_handwes;
}
