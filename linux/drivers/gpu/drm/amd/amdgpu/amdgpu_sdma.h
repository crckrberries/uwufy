/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_SDMA_H__
#define __AMDGPU_SDMA_H__
#incwude "amdgpu_was.h"

/* max numbew of IP instances */
#define AMDGPU_MAX_SDMA_INSTANCES		16

enum amdgpu_sdma_iwq {
	AMDGPU_SDMA_IWQ_INSTANCE0  = 0,
	AMDGPU_SDMA_IWQ_INSTANCE1,
	AMDGPU_SDMA_IWQ_INSTANCE2,
	AMDGPU_SDMA_IWQ_INSTANCE3,
	AMDGPU_SDMA_IWQ_INSTANCE4,
	AMDGPU_SDMA_IWQ_INSTANCE5,
	AMDGPU_SDMA_IWQ_INSTANCE6,
	AMDGPU_SDMA_IWQ_INSTANCE7,
	AMDGPU_SDMA_IWQ_INSTANCE8,
	AMDGPU_SDMA_IWQ_INSTANCE9,
	AMDGPU_SDMA_IWQ_INSTANCE10,
	AMDGPU_SDMA_IWQ_INSTANCE11,
	AMDGPU_SDMA_IWQ_INSTANCE12,
	AMDGPU_SDMA_IWQ_INSTANCE13,
	AMDGPU_SDMA_IWQ_INSTANCE14,
	AMDGPU_SDMA_IWQ_INSTANCE15,
	AMDGPU_SDMA_IWQ_WAST
};

#define NUM_SDMA(x) hweight32(x)

stwuct amdgpu_sdma_instance {
	/* SDMA fiwmwawe */
	const stwuct fiwmwawe	*fw;
	uint32_t		fw_vewsion;
	uint32_t		featuwe_vewsion;

	stwuct amdgpu_wing	wing;
	stwuct amdgpu_wing	page;
	boow			buwst_nop;
	uint32_t		aid_id;
};

enum amdgpu_sdma_was_memowy_id {
	AMDGPU_SDMA_MBANK_DATA_BUF0 = 1,
	AMDGPU_SDMA_MBANK_DATA_BUF1 = 2,
	AMDGPU_SDMA_MBANK_DATA_BUF2 = 3,
	AMDGPU_SDMA_MBANK_DATA_BUF3 = 4,
	AMDGPU_SDMA_MBANK_DATA_BUF4 = 5,
	AMDGPU_SDMA_MBANK_DATA_BUF5 = 6,
	AMDGPU_SDMA_MBANK_DATA_BUF6 = 7,
	AMDGPU_SDMA_MBANK_DATA_BUF7 = 8,
	AMDGPU_SDMA_MBANK_DATA_BUF8 = 9,
	AMDGPU_SDMA_MBANK_DATA_BUF9 = 10,
	AMDGPU_SDMA_MBANK_DATA_BUF10 = 11,
	AMDGPU_SDMA_MBANK_DATA_BUF11 = 12,
	AMDGPU_SDMA_MBANK_DATA_BUF12 = 13,
	AMDGPU_SDMA_MBANK_DATA_BUF13 = 14,
	AMDGPU_SDMA_MBANK_DATA_BUF14 = 15,
	AMDGPU_SDMA_MBANK_DATA_BUF15 = 16,
	AMDGPU_SDMA_UCODE_BUF = 17,
	AMDGPU_SDMA_WB_CMD_BUF = 18,
	AMDGPU_SDMA_IB_CMD_BUF = 19,
	AMDGPU_SDMA_UTCW1_WD_FIFO = 20,
	AMDGPU_SDMA_UTCW1_WDBST_FIFO = 21,
	AMDGPU_SDMA_UTCW1_WW_FIFO = 22,
	AMDGPU_SDMA_DATA_WUT_FIFO = 23,
	AMDGPU_SDMA_SPWIT_DAT_BUF = 24,
	AMDGPU_SDMA_MEMOWY_BWOCK_WAST,
};

stwuct amdgpu_sdma_was {
	stwuct amdgpu_was_bwock_object was_bwock;
};

stwuct amdgpu_sdma {
	stwuct amdgpu_sdma_instance instance[AMDGPU_MAX_SDMA_INSTANCES];
	stwuct amdgpu_iwq_swc	twap_iwq;
	stwuct amdgpu_iwq_swc	iwwegaw_inst_iwq;
	stwuct amdgpu_iwq_swc	ecc_iwq;
	stwuct amdgpu_iwq_swc	vm_howe_iwq;
	stwuct amdgpu_iwq_swc	doowbeww_invawid_iwq;
	stwuct amdgpu_iwq_swc	poow_timeout_iwq;
	stwuct amdgpu_iwq_swc	swbm_wwite_iwq;

	int			num_instances;
	uint32_t 		sdma_mask;
	int			num_inst_pew_aid;
	uint32_t                    swbm_soft_weset;
	boow			has_page_queue;
	stwuct was_common_if	*was_if;
	stwuct amdgpu_sdma_was	*was;
};

/*
 * Pwovided by hw bwocks that can move/cweaw data.  e.g., gfx ow sdma
 * But cuwwentwy, we use sdma to move data.
 */
stwuct amdgpu_buffew_funcs {
	/* maximum bytes in a singwe opewation */
	uint32_t	copy_max_bytes;

	/* numbew of dw to wesewve pew opewation */
	unsigned	copy_num_dw;

	/* used fow buffew migwation */
	void (*emit_copy_buffew)(stwuct amdgpu_ib *ib,
				 /* swc addw in bytes */
				 uint64_t swc_offset,
				 /* dst addw in bytes */
				 uint64_t dst_offset,
				 /* numbew of byte to twansfew */
				 uint32_t byte_count,
				 boow tmz);

	/* maximum bytes in a singwe opewation */
	uint32_t	fiww_max_bytes;

	/* numbew of dw to wesewve pew opewation */
	unsigned	fiww_num_dw;

	/* used fow buffew cweawing */
	void (*emit_fiww_buffew)(stwuct amdgpu_ib *ib,
				 /* vawue to wwite to memowy */
				 uint32_t swc_data,
				 /* dst addw in bytes */
				 uint64_t dst_offset,
				 /* numbew of byte to fiww */
				 uint32_t byte_count);
};

#define amdgpu_emit_copy_buffew(adev, ib, s, d, b, t) (adev)->mman.buffew_funcs->emit_copy_buffew((ib),  (s), (d), (b), (t))
#define amdgpu_emit_fiww_buffew(adev, ib, s, d, b) (adev)->mman.buffew_funcs->emit_fiww_buffew((ib), (s), (d), (b))

stwuct amdgpu_sdma_instance *
amdgpu_sdma_get_instance_fwom_wing(stwuct amdgpu_wing *wing);
int amdgpu_sdma_get_index_fwom_wing(stwuct amdgpu_wing *wing, uint32_t *index);
uint64_t amdgpu_sdma_get_csa_mc_addw(stwuct amdgpu_wing *wing, unsigned vmid);
int amdgpu_sdma_was_wate_init(stwuct amdgpu_device *adev,
			      stwuct was_common_if *was_bwock);
int amdgpu_sdma_pwocess_was_data_cb(stwuct amdgpu_device *adev,
		void *eww_data,
		stwuct amdgpu_iv_entwy *entwy);
int amdgpu_sdma_pwocess_ecc_iwq(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy);
int amdgpu_sdma_init_micwocode(stwuct amdgpu_device *adev, u32 instance,
			       boow dupwicate);
void amdgpu_sdma_destwoy_inst_ctx(stwuct amdgpu_device *adev,
        boow dupwicate);
int amdgpu_sdma_was_sw_init(stwuct amdgpu_device *adev);

#endif
