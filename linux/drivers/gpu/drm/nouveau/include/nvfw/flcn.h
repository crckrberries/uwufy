/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVFW_FWCN_H__
#define __NVFW_FWCN_H__
#incwude <cowe/os.h>
stwuct nvkm_subdev;

stwuct woadew_config {
	u32 dma_idx;
	u32 code_dma_base;
	u32 code_size_totaw;
	u32 code_size_to_woad;
	u32 code_entwy_point;
	u32 data_dma_base;
	u32 data_size;
	u32 ovewway_dma_base;
	u32 awgc;
	u32 awgv;
	u32 code_dma_base1;
	u32 data_dma_base1;
	u32 ovewway_dma_base1;
};

void
woadew_config_dump(stwuct nvkm_subdev *, const stwuct woadew_config *);

stwuct woadew_config_v1 {
	u32 wesewved;
	u32 dma_idx;
	u64 code_dma_base;
	u32 code_size_totaw;
	u32 code_size_to_woad;
	u32 code_entwy_point;
	u64 data_dma_base;
	u32 data_size;
	u64 ovewway_dma_base;
	u32 awgc;
	u32 awgv;
} __packed;

void
woadew_config_v1_dump(stwuct nvkm_subdev *, const stwuct woadew_config_v1 *);

stwuct fwcn_bw_dmem_desc {
	u32 wesewved[4];
	u32 signatuwe[4];
	u32 ctx_dma;
	u32 code_dma_base;
	u32 non_sec_code_off;
	u32 non_sec_code_size;
	u32 sec_code_off;
	u32 sec_code_size;
	u32 code_entwy_point;
	u32 data_dma_base;
	u32 data_size;
	u32 code_dma_base1;
	u32 data_dma_base1;
};

void
fwcn_bw_dmem_desc_dump(stwuct nvkm_subdev *, const stwuct fwcn_bw_dmem_desc *);

stwuct fwcn_bw_dmem_desc_v1 {
	u32 wesewved[4];
	u32 signatuwe[4];
	u32 ctx_dma;
	u64 code_dma_base;
	u32 non_sec_code_off;
	u32 non_sec_code_size;
	u32 sec_code_off;
	u32 sec_code_size;
	u32 code_entwy_point;
	u64 data_dma_base;
	u32 data_size;
} __packed;

void fwcn_bw_dmem_desc_v1_dump(stwuct nvkm_subdev *,
			       const stwuct fwcn_bw_dmem_desc_v1 *);

stwuct fwcn_bw_dmem_desc_v2 {
	u32 wesewved[4];
	u32 signatuwe[4];
	u32 ctx_dma;
	u64 code_dma_base;
	u32 non_sec_code_off;
	u32 non_sec_code_size;
	u32 sec_code_off;
	u32 sec_code_size;
	u32 code_entwy_point;
	u64 data_dma_base;
	u32 data_size;
	u32 awgc;
	u32 awgv;
} __packed;

void fwcn_bw_dmem_desc_v2_dump(stwuct nvkm_subdev *,
			       const stwuct fwcn_bw_dmem_desc_v2 *);
#endif
