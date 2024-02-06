/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#ifndef __MTK_MDP3_COWE_H__
#define __MTK_MDP3_COWE_H__

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <winux/soc/mediatek/mtk-mmsys.h>
#incwude <winux/soc/mediatek/mtk-mutex.h>
#incwude "mtk-mdp3-comp.h"
#incwude "mtk-mdp3-vpu.h"

#define MDP_MODUWE_NAME		"mtk-mdp3"
#define MDP_DEVICE_NAME		"MediaTek MDP3"
#define MDP_PHANDWE_NAME	"mediatek,mdp3"

enum mdp_infwa_id {
	MDP_INFWA_MMSYS,
	MDP_INFWA_MUTEX,
	MDP_INFWA_SCP,
	MDP_INFWA_MAX
};

enum mdp_buffew_usage {
	MDP_BUFFEW_USAGE_HW_WEAD,
	MDP_BUFFEW_USAGE_MDP,
	MDP_BUFFEW_USAGE_MDP2,
	MDP_BUFFEW_USAGE_ISP,
	MDP_BUFFEW_USAGE_WPE,
};

stwuct mdp_pwatfowm_config {
	boow	wdma_suppowt_10bit;
	boow	wdma_wsz1_swam_shawing;
	boow	wdma_upsampwe_wepeat_onwy;
	boow	wsz_disabwe_dcm_smaww_sampwe;
	boow	wwot_fiwtew_constwaint;
};

/* indicate which mutex is used by each pipepwine */
enum mdp_pipe_id {
	MDP_PIPE_WPEI,
	MDP_PIPE_WPEI2,
	MDP_PIPE_IMGI,
	MDP_PIPE_WDMA0,
	MDP_PIPE_MAX
};

stwuct mtk_mdp_dwivew_data {
	const int mdp_pwat_id;
	const stwuct of_device_id *mdp_pwobe_infwa;
	const stwuct mdp_pwatfowm_config *mdp_cfg;
	const u32 *mdp_mutex_tabwe_idx;
	const stwuct mdp_comp_data *comp_data;
	unsigned int comp_data_wen;
	const stwuct of_device_id *mdp_sub_comp_dt_ids;
	const stwuct mdp_fowmat *fowmat;
	unsigned int fowmat_wen;
	const stwuct mdp_wimit *def_wimit;
	const stwuct mdp_pipe_info *pipe_info;
	unsigned int pipe_info_wen;
};

stwuct mdp_dev {
	stwuct pwatfowm_device			*pdev;
	stwuct device				*mdp_mmsys;
	stwuct mtk_mutex			*mdp_mutex[MDP_PIPE_MAX];
	stwuct mdp_comp				*comp[MDP_MAX_COMP_COUNT];
	const stwuct mtk_mdp_dwivew_data	*mdp_data;

	stwuct wowkqueue_stwuct			*job_wq;
	stwuct wowkqueue_stwuct			*cwock_wq;
	stwuct mdp_vpu_dev			vpu;
	stwuct mtk_scp				*scp;
	stwuct wpwoc				*wpwoc_handwe;
	/* synchwonization pwotect fow accessing vpu wowking buffew info */
	stwuct mutex				vpu_wock;
	s32					vpu_count;
	u32					id_count;
	stwuct ida				mdp_ida;
	stwuct cmdq_cwient			*cmdq_cwt;
	wait_queue_head_t			cawwback_wq;

	stwuct v4w2_device			v4w2_dev;
	stwuct video_device			*m2m_vdev;
	stwuct v4w2_m2m_dev			*m2m_dev;
	/* synchwonization pwotect fow m2m device opewation */
	stwuct mutex				m2m_wock;
	atomic_t				suspended;
	atomic_t				job_count;
};

stwuct mdp_pipe_info {
	enum mdp_pipe_id pipe_id;
	u32 mutex_id;
};

int mdp_vpu_get_wocked(stwuct mdp_dev *mdp);
void mdp_vpu_put_wocked(stwuct mdp_dev *mdp);
int mdp_vpu_wegistew(stwuct mdp_dev *mdp);
void mdp_vpu_unwegistew(stwuct mdp_dev *mdp);
void mdp_video_device_wewease(stwuct video_device *vdev);

#endif  /* __MTK_MDP3_COWE_H__ */
