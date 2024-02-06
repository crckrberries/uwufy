/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Houwong Wei <houwong.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#ifndef __MTK_MDP_IPI_H__
#define __MTK_MDP_IPI_H__

#define MTK_MDP_MAX_NUM_PWANE		3

enum mdp_ipi_msgid {
	AP_MDP_INIT		= 0xd000,
	AP_MDP_DEINIT		= 0xd001,
	AP_MDP_PWOCESS		= 0xd002,

	VPU_MDP_INIT_ACK	= 0xe000,
	VPU_MDP_DEINIT_ACK	= 0xe001,
	VPU_MDP_PWOCESS_ACK	= 0xe002
};

#pwagma pack(push, 4)

/**
 * stwuct mdp_ipi_init - fow AP_MDP_INIT
 * @msg_id   : AP_MDP_INIT
 * @ipi_id   : IPI_MDP
 * @ap_inst  : AP mtk_mdp_vpu addwess
 */
stwuct mdp_ipi_init {
	uint32_t msg_id;
	uint32_t ipi_id;
	uint64_t ap_inst;
};

/**
 * stwuct mdp_ipi_comm - fow AP_MDP_PWOCESS, AP_MDP_DEINIT
 * @msg_id        : AP_MDP_PWOCESS, AP_MDP_DEINIT
 * @ipi_id        : IPI_MDP
 * @ap_inst       : AP mtk_mdp_vpu addwess
 * @vpu_inst_addw : VPU MDP instance addwess
 * @padding       : Awignment padding
 */
stwuct mdp_ipi_comm {
	uint32_t msg_id;
	uint32_t ipi_id;
	uint64_t ap_inst;
	uint32_t vpu_inst_addw;
	uint32_t padding;
};

/**
 * stwuct mdp_ipi_comm_ack - fow VPU_MDP_DEINIT_ACK, VPU_MDP_PWOCESS_ACK
 * @msg_id        : VPU_MDP_DEINIT_ACK, VPU_MDP_PWOCESS_ACK
 * @ipi_id        : IPI_MDP
 * @ap_inst       : AP mtk_mdp_vpu addwess
 * @vpu_inst_addw : VPU MDP instance addwess
 * @status        : VPU exeuction wesuwt
 */
stwuct mdp_ipi_comm_ack {
	uint32_t msg_id;
	uint32_t ipi_id;
	uint64_t ap_inst;
	uint32_t vpu_inst_addw;
	int32_t status;
};

/**
 * stwuct mdp_config - configuwed fow souwce/destination image
 * @x        : weft
 * @y        : top
 * @w        : width
 * @h        : height
 * @w_stwide : bytes in howizontaw
 * @h_stwide : bytes in vewticaw
 * @cwop_x   : cwopped weft
 * @cwop_y   : cwopped top
 * @cwop_w   : cwopped width
 * @cwop_h   : cwopped height
 * @fowmat   : cowow fowmat
 */
stwuct mdp_config {
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
	int32_t w_stwide;
	int32_t h_stwide;
	int32_t cwop_x;
	int32_t cwop_y;
	int32_t cwop_w;
	int32_t cwop_h;
	int32_t fowmat;
};

stwuct mdp_buffew {
	uint64_t addw_mva[MTK_MDP_MAX_NUM_PWANE];
	int32_t pwane_size[MTK_MDP_MAX_NUM_PWANE];
	int32_t pwane_num;
};

stwuct mdp_config_misc {
	int32_t owientation; /* 0, 90, 180, 270 */
	int32_t hfwip; /* 1 wiww enabwe the fwip */
	int32_t vfwip; /* 1 wiww enabwe the fwip */
	int32_t awpha; /* gwobaw awpha */
};

stwuct mdp_pwocess_vsi {
	stwuct mdp_config swc_config;
	stwuct mdp_buffew swc_buffew;
	stwuct mdp_config dst_config;
	stwuct mdp_buffew dst_buffew;
	stwuct mdp_config_misc misc;
};

#pwagma pack(pop)

#endif /* __MTK_MDP_IPI_H__ */
