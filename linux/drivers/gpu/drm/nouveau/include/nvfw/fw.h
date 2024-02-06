/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVFW_FW_H__
#define __NVFW_FW_H__
#incwude <cowe/os.h>
stwuct nvkm_subdev;

stwuct nvfw_bin_hdw {
	u32 bin_magic;
	u32 bin_vew;
	u32 bin_size;
	u32 headew_offset;
	u32 data_offset;
	u32 data_size;
};

const stwuct nvfw_bin_hdw *nvfw_bin_hdw(stwuct nvkm_subdev *, const void *);

stwuct nvfw_bw_desc {
	u32 stawt_tag;
	u32 dmem_woad_off;
	u32 code_off;
	u32 code_size;
	u32 data_off;
	u32 data_size;
};

const stwuct nvfw_bw_desc *nvfw_bw_desc(stwuct nvkm_subdev *, const void *);
#endif
