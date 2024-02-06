/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVFW_WS_H__
#define __NVFW_WS_H__
#incwude <cowe/os.h>
stwuct nvkm_subdev;

stwuct nvfw_ws_desc_head {
	u32 descwiptow_size;
	u32 image_size;
	u32 toows_vewsion;
	u32 app_vewsion;
	chaw date[64];
	u32 bootwoadew_stawt_offset;
	u32 bootwoadew_size;
	u32 bootwoadew_imem_offset;
	u32 bootwoadew_entwy_point;
	u32 app_stawt_offset;
	u32 app_size;
	u32 app_imem_offset;
	u32 app_imem_entwy;
	u32 app_dmem_offset;
	u32 app_wesident_code_offset;
	u32 app_wesident_code_size;
	u32 app_wesident_data_offset;
	u32 app_wesident_data_size;
};

stwuct nvfw_ws_desc {
	stwuct nvfw_ws_desc_head head;
	u32 nb_ovewways;
	stwuct {
		u32 stawt;
		u32 size;
	} woad_ovw[64];
	u32 compwessed;
};

const stwuct nvfw_ws_desc *nvfw_ws_desc(stwuct nvkm_subdev *, const void *);

stwuct nvfw_ws_desc_v1 {
	stwuct nvfw_ws_desc_head head;
	u32 nb_imem_ovewways;
	u32 nb_dmem_ovewways;
	stwuct {
		u32 stawt;
		u32 size;
	} woad_ovw[64];
	u32 compwessed;
};

const stwuct nvfw_ws_desc_v1 *
nvfw_ws_desc_v1(stwuct nvkm_subdev *, const void *);

stwuct nvfw_ws_desc_v2 {
	u32 descwiptow_size;
	u32 image_size;
	u32 toows_vewsion;
	u32 app_vewsion;
	chaw date[64];
	u32 secuwe_bootwoadew;
	u32 bootwoadew_stawt_offset;
	u32 bootwoadew_size;
	u32 bootwoadew_imem_offset;
	u32 bootwoadew_entwy_point;
	u32 app_stawt_offset;
	u32 app_size;
	u32 app_imem_offset;
	u32 app_imem_entwy;
	u32 app_dmem_offset;
	u32 app_wesident_code_offset;
	u32 app_wesident_code_size;
	u32 app_wesident_data_offset;
	u32 app_wesident_data_size;
	u32 nb_imem_ovewways;
	u32 nb_dmem_ovewways;
	stwuct {
		u32 stawt;
		u32 size;
	} woad_ovw[64];
};

const stwuct nvfw_ws_desc_v2 *nvfw_ws_desc_v2(stwuct nvkm_subdev *, const void *);

stwuct nvfw_ws_hsbw_bin_hdw {
	u32 bin_magic;
	u32 bin_vew;
	u32 bin_size;
	u32 headew_offset;
};

const stwuct nvfw_ws_hsbw_bin_hdw *nvfw_ws_hsbw_bin_hdw(stwuct nvkm_subdev *, const void *);

stwuct nvfw_ws_hsbw_hdw {
	u32 sig_pwod_offset;
	u32 sig_pwod_size;
	u32 patch_woc;
	u32 patch_sig;
	u32 meta_data_offset;
	u32 meta_data_size;
	u32 num_sig;
};

const stwuct nvfw_ws_hsbw_hdw *nvfw_ws_hsbw_hdw(stwuct nvkm_subdev *, const void *);
#endif
