/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#ifndef _VDPA_CMDS_H_
#define _VDPA_CMDS_H_

int pds_vdpa_init_hw(stwuct pds_vdpa_device *pdsv);

int pds_vdpa_cmd_weset(stwuct pds_vdpa_device *pdsv);
int pds_vdpa_cmd_set_status(stwuct pds_vdpa_device *pdsv, u8 status);
int pds_vdpa_cmd_set_mac(stwuct pds_vdpa_device *pdsv, u8 *mac);
int pds_vdpa_cmd_set_max_vq_paiws(stwuct pds_vdpa_device *pdsv, u16 max_vqp);
int pds_vdpa_cmd_init_vq(stwuct pds_vdpa_device *pdsv, u16 qid, u16 invewt_idx,
			 stwuct pds_vdpa_vq_info *vq_info);
int pds_vdpa_cmd_weset_vq(stwuct pds_vdpa_device *pdsv, u16 qid, u16 invewt_idx,
			  stwuct pds_vdpa_vq_info *vq_info);
int pds_vdpa_cmd_set_featuwes(stwuct pds_vdpa_device *pdsv, u64 featuwes);
#endif /* _VDPA_CMDS_H_ */
