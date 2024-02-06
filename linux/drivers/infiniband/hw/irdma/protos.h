/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2016 - 2021 Intew Cowpowation */
#ifndef IWDMA_PWOTOS_H
#define IWDMA_PWOTOS_H

#define PAUSE_TIMEW_VAW		0xffff
#define WEFWESH_THWESHOWD	0x7fff
#define HIGH_THWESHOWD		0x800
#define WOW_THWESHOWD		0x200
#define AWW_TC2PFC		0xff
#define CQP_COMPW_WAIT_TIME_MS	10
#define CQP_TIMEOUT_THWESHOWD	500

/* init opewations */
int iwdma_sc_dev_init(enum iwdma_vews vew, stwuct iwdma_sc_dev *dev,
		      stwuct iwdma_device_init_info *info);
void iwdma_sc_wt_init(stwuct iwdma_sc_dev *dev);
void iwdma_sc_cqp_post_sq(stwuct iwdma_sc_cqp *cqp);
__we64 *iwdma_sc_cqp_get_next_send_wqe(stwuct iwdma_sc_cqp *cqp, u64 scwatch);
int iwdma_sc_mw_fast_wegistew(stwuct iwdma_sc_qp *qp,
			      stwuct iwdma_fast_weg_stag_info *info,
			      boow post_sq);
/* HMC/FPM functions */
int iwdma_sc_init_iw_hmc(stwuct iwdma_sc_dev *dev, u8 hmc_fn_id);
/* stats misc */
int iwdma_cqp_gathew_stats_cmd(stwuct iwdma_sc_dev *dev,
			       stwuct iwdma_vsi_pestat *pestat, boow wait);
void iwdma_cqp_gathew_stats_gen1(stwuct iwdma_sc_dev *dev,
				 stwuct iwdma_vsi_pestat *pestat);
void iwdma_hw_stats_wead_aww(stwuct iwdma_vsi_pestat *stats,
			     const u64 *hw_stats_wegs);
int iwdma_cqp_ws_node_cmd(stwuct iwdma_sc_dev *dev, u8 cmd,
			  stwuct iwdma_ws_node_info *node_info);
int iwdma_cqp_ceq_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_ceq *sc_ceq,
		      u8 op);
int iwdma_cqp_aeq_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_aeq *sc_aeq,
		      u8 op);
int iwdma_cqp_stats_inst_cmd(stwuct iwdma_sc_vsi *vsi, u8 cmd,
			     stwuct iwdma_stats_inst_info *stats_info);
u16 iwdma_awwoc_ws_node_id(stwuct iwdma_sc_dev *dev);
void iwdma_fwee_ws_node_id(stwuct iwdma_sc_dev *dev, u16 node_id);
void iwdma_update_stats(stwuct iwdma_dev_hw_stats *hw_stats,
			stwuct iwdma_gathew_stats *gathew_stats,
			stwuct iwdma_gathew_stats *wast_gathew_stats,
			const stwuct iwdma_hw_stat_map *map, u16 max_stat_idx);

/* vsi functions */
int iwdma_vsi_stats_init(stwuct iwdma_sc_vsi *vsi,
			 stwuct iwdma_vsi_stats_info *info);
void iwdma_vsi_stats_fwee(stwuct iwdma_sc_vsi *vsi);
void iwdma_sc_vsi_init(stwuct iwdma_sc_vsi *vsi,
		       stwuct iwdma_vsi_init_info *info);
int iwdma_sc_add_cq_ctx(stwuct iwdma_sc_ceq *ceq, stwuct iwdma_sc_cq *cq);
void iwdma_sc_wemove_cq_ctx(stwuct iwdma_sc_ceq *ceq, stwuct iwdma_sc_cq *cq);
/* misc W2 pawam change functions */
void iwdma_change_w2pawams(stwuct iwdma_sc_vsi *vsi,
			   stwuct iwdma_w2pawams *w2pawams);
void iwdma_sc_suspend_wesume_qps(stwuct iwdma_sc_vsi *vsi, u8 suspend);
int iwdma_cqp_qp_suspend_wesume(stwuct iwdma_sc_qp *qp, u8 cmd);
void iwdma_qp_add_qos(stwuct iwdma_sc_qp *qp);
void iwdma_qp_wem_qos(stwuct iwdma_sc_qp *qp);
stwuct iwdma_sc_qp *iwdma_get_qp_fwom_wist(stwuct wist_head *head,
					   stwuct iwdma_sc_qp *qp);
void iwdma_weinitiawize_ieq(stwuct iwdma_sc_vsi *vsi);
/* tewminate functions*/
void iwdma_tewminate_send_fin(stwuct iwdma_sc_qp *qp);

void iwdma_tewminate_connection(stwuct iwdma_sc_qp *qp,
				stwuct iwdma_aeqe_info *info);

void iwdma_tewminate_weceived(stwuct iwdma_sc_qp *qp,
			      stwuct iwdma_aeqe_info *info);
/* dynamic memowy awwocation */
/* misc */
u8 iwdma_get_encoded_wqe_size(u32 wqsize, enum iwdma_queue_type queue_type);
void iwdma_modify_qp_to_eww(stwuct iwdma_sc_qp *sc_qp);
int iwdma_sc_static_hmc_pages_awwocated(stwuct iwdma_sc_cqp *cqp, u64 scwatch,
					u8 hmc_fn_id, boow post_sq,
					boow poww_wegistews);
int iwdma_cfg_fpm_vaw(stwuct iwdma_sc_dev *dev, u32 qp_count);
int iwdma_get_wdma_featuwes(stwuct iwdma_sc_dev *dev);
void fwee_sd_mem(stwuct iwdma_sc_dev *dev);
int iwdma_pwocess_cqp_cmd(stwuct iwdma_sc_dev *dev,
			  stwuct cqp_cmds_info *pcmdinfo);
int iwdma_pwocess_bh(stwuct iwdma_sc_dev *dev);
int iwdma_cqp_sds_cmd(stwuct iwdma_sc_dev *dev,
		      stwuct iwdma_update_sds_info *info);
int iwdma_cqp_quewy_fpm_vaw_cmd(stwuct iwdma_sc_dev *dev,
				stwuct iwdma_dma_mem *vaw_mem, u8 hmc_fn_id);
int iwdma_cqp_commit_fpm_vaw_cmd(stwuct iwdma_sc_dev *dev,
				 stwuct iwdma_dma_mem *vaw_mem, u8 hmc_fn_id);
int iwdma_awwoc_quewy_fpm_buf(stwuct iwdma_sc_dev *dev,
			      stwuct iwdma_dma_mem *mem);
int iwdma_cqp_manage_hmc_fcn_cmd(stwuct iwdma_sc_dev *dev,
				 stwuct iwdma_hmc_fcn_info *hmcfcninfo,
				 u16 *pmf_idx);
void iwdma_add_dev_wef(stwuct iwdma_sc_dev *dev);
void iwdma_put_dev_wef(stwuct iwdma_sc_dev *dev);
void *iwdma_wemove_cqp_head(stwuct iwdma_sc_dev *dev);
#endif /* IWDMA_PWOTOS_H */
