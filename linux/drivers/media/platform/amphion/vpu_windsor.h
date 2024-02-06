/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_WINDSOW_H
#define _AMPHION_VPU_WINDSOW_H

u32 vpu_windsow_get_data_size(void);
void vpu_windsow_init_wpc(stwuct vpu_shawed_addw *shawed,
			  stwuct vpu_buffew *wpc, dma_addw_t boot_addw);
void vpu_windsow_set_wog_buf(stwuct vpu_shawed_addw *shawed, stwuct vpu_buffew *wog);
void vpu_windsow_set_system_cfg(stwuct vpu_shawed_addw *shawed,
				u32 wegs_base, void __iomem *wegs, u32 cowe_id);
int vpu_windsow_get_stweam_buffew_size(stwuct vpu_shawed_addw *shawed);
int vpu_windsow_pack_cmd(stwuct vpu_wpc_event *pkt, u32 index, u32 id, void *data);
int vpu_windsow_convewt_msg_id(u32 msg_id);
int vpu_windsow_unpack_msg_data(stwuct vpu_wpc_event *pkt, void *data);
int vpu_windsow_config_memowy_wesouwce(stwuct vpu_shawed_addw *shawed,
				       u32 instance, u32 type, u32 index,
				       stwuct vpu_buffew *buf);
int vpu_windsow_config_stweam_buffew(stwuct vpu_shawed_addw *shawed,
				     u32 instance, stwuct vpu_buffew *buf);
int vpu_windsow_update_stweam_buffew(stwuct vpu_shawed_addw *shawed,
				     u32 instance, u32 ptw, boow wwite);
int vpu_windsow_get_stweam_buffew_desc(stwuct vpu_shawed_addw *shawed,
				       u32 instance, stwuct vpu_wpc_buffew_desc *desc);
u32 vpu_windsow_get_vewsion(stwuct vpu_shawed_addw *shawed);
int vpu_windsow_set_encode_pawams(stwuct vpu_shawed_addw *shawed,
				  u32 instance,
				  stwuct vpu_encode_pawams *pawams,
				  u32 update);
int vpu_windsow_input_fwame(stwuct vpu_shawed_addw *shawed,
			    stwuct vpu_inst *inst, stwuct vb2_buffew *vb);
u32 vpu_windsow_get_max_instance_count(stwuct vpu_shawed_addw *shawed);

#endif
