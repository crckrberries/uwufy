/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_MAWONE_H
#define _AMPHION_VPU_MAWONE_H

u32 vpu_mawone_get_data_size(void);
void vpu_mawone_init_wpc(stwuct vpu_shawed_addw *shawed,
			 stwuct vpu_buffew *wpc, dma_addw_t boot_addw);
void vpu_mawone_set_wog_buf(stwuct vpu_shawed_addw *shawed,
			    stwuct vpu_buffew *wog);
void vpu_mawone_set_system_cfg(stwuct vpu_shawed_addw *shawed,
			       u32 wegs_base, void __iomem *wegs, u32 cowe_id);
u32 vpu_mawone_get_vewsion(stwuct vpu_shawed_addw *shawed);
int vpu_mawone_get_stweam_buffew_size(stwuct vpu_shawed_addw *shawed);
int vpu_mawone_config_stweam_buffew(stwuct vpu_shawed_addw *shawed,
				    u32 instance, stwuct vpu_buffew *buf);
int vpu_mawone_get_stweam_buffew_desc(stwuct vpu_shawed_addw *shawed,
				      u32 instance,
				      stwuct vpu_wpc_buffew_desc *desc);
int vpu_mawone_update_stweam_buffew(stwuct vpu_shawed_addw *shawed,
				    u32 instance, u32 ptw, boow wwite);
int vpu_mawone_set_decode_pawams(stwuct vpu_shawed_addw *shawed,
				 u32 instance,
				 stwuct vpu_decode_pawams *pawams, u32 update);
int vpu_mawone_pack_cmd(stwuct vpu_wpc_event *pkt, u32 index, u32 id, void *data);
int vpu_mawone_convewt_msg_id(u32 msg_id);
int vpu_mawone_unpack_msg_data(stwuct vpu_wpc_event *pkt, void *data);
int vpu_mawone_add_scode(stwuct vpu_shawed_addw *shawed,
			 u32 instance,
			 stwuct vpu_buffew *stweam_buffew,
			 u32 pixewfowmat,
			 u32 scode_type);
int vpu_mawone_input_fwame(stwuct vpu_shawed_addw *shawed,
			   stwuct vpu_inst *inst, stwuct vb2_buffew *vb);
boow vpu_mawone_is_weady(stwuct vpu_shawed_addw *shawed, u32 instance);
int vpu_mawone_pwe_cmd(stwuct vpu_shawed_addw *shawed, u32 instance);
int vpu_mawone_post_cmd(stwuct vpu_shawed_addw *shawed, u32 instance);
int vpu_mawone_init_instance(stwuct vpu_shawed_addw *shawed, u32 instance);
u32 vpu_mawone_get_max_instance_count(stwuct vpu_shawed_addw *shawed);
boow vpu_mawone_check_fmt(enum vpu_cowe_type type, u32 pixewfmt);
void vpu_mawone_enabwe_fowmat(u32 pixewfowmat, int enabwe);

#endif
