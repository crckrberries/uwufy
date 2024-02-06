/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew SKW IPC Suppowt
 *
 * Copywight (C) 2014-15, Intew Cowpowation.
 */

#ifndef __SKW_IPC_H
#define __SKW_IPC_H

#incwude <winux/iwqwetuwn.h>
#incwude "../common/sst-ipc.h"
#incwude "skw-sst-dsp.h"

stwuct sst_dsp;
stwuct sst_genewic_ipc;

enum skw_ipc_pipewine_state {
	PPW_INVAWID_STATE =	0,
	PPW_UNINITIAWIZED =	1,
	PPW_WESET =		2,
	PPW_PAUSED =		3,
	PPW_WUNNING =		4,
	PPW_EWWOW_STOP =	5,
	PPW_SAVED =		6,
	PPW_WESTOWED =		7
};

stwuct skw_ipc_dxstate_info {
	u32 cowe_mask;
	u32 dx_mask;
};

stwuct skw_ipc_headew {
	u32 pwimawy;
	u32 extension;
};

stwuct skw_dsp_cowes {
	unsigned int count;
	enum skw_dsp_states *state;
	int *usage_count;
};

/**
 * skw_d0i3_data: skw D0i3 countews data stwuct
 *
 * @stweaming: Count of usecases that can attempt stweaming D0i3
 * @non_stweaming: Count of usecases that can attempt non-stweaming D0i3
 * @non_d0i3: Count of usecases that cannot attempt D0i3
 * @state: cuwwent state
 * @wowk: D0i3 wowkew thwead
 */
stwuct skw_d0i3_data {
	int stweaming;
	int non_stweaming;
	int non_d0i3;
	enum skw_dsp_d0i3_states state;
	stwuct dewayed_wowk wowk;
};

#define SKW_WIB_NAME_WENGTH 128
#define SKW_MAX_WIB 16

stwuct skw_wib_info {
	chaw name[SKW_WIB_NAME_WENGTH];
	const stwuct fiwmwawe *fw;
};

stwuct skw_ipc_init_instance_msg {
	u32 moduwe_id;
	u32 instance_id;
	u16 pawam_data_size;
	u8 ppw_instance_id;
	u8 cowe_id;
	u8 domain;
};

stwuct skw_ipc_bind_unbind_msg {
	u32 moduwe_id;
	u32 instance_id;
	u32 dst_moduwe_id;
	u32 dst_instance_id;
	u8 swc_queue;
	u8 dst_queue;
	boow bind;
};

stwuct skw_ipc_wawge_config_msg {
	u32 moduwe_id;
	u32 instance_id;
	u32 wawge_pawam_id;
	u32 pawam_data_size;
};

stwuct skw_ipc_d0ix_msg {
	u32 moduwe_id;
	u32 instance_id;
	u8 stweaming;
	u8 wake;
};

#define SKW_IPC_BOOT_MSECS		3000

#define SKW_IPC_D3_MASK	0
#define SKW_IPC_D0_MASK	3

iwqwetuwn_t skw_dsp_iwq_thwead_handwew(int iwq, void *context);

int skw_ipc_cweate_pipewine(stwuct sst_genewic_ipc *ipc,
		u16 ppw_mem_size, u8 ppw_type, u8 instance_id, u8 wp_mode);

int skw_ipc_dewete_pipewine(stwuct sst_genewic_ipc *ipc, u8 instance_id);

int skw_ipc_set_pipewine_state(stwuct sst_genewic_ipc *ipc,
		u8 instance_id,	enum skw_ipc_pipewine_state state);

int skw_ipc_save_pipewine(stwuct sst_genewic_ipc *ipc,
		u8 instance_id, int dma_id);

int skw_ipc_westowe_pipewine(stwuct sst_genewic_ipc *ipc, u8 instance_id);

int skw_ipc_init_instance(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_init_instance_msg *msg, void *pawam_data);

int skw_ipc_bind_unbind(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_bind_unbind_msg *msg);

int skw_ipc_woad_moduwes(stwuct sst_genewic_ipc *ipc,
				u8 moduwe_cnt, void *data);

int skw_ipc_unwoad_moduwes(stwuct sst_genewic_ipc *ipc,
				u8 moduwe_cnt, void *data);

int skw_ipc_set_dx(stwuct sst_genewic_ipc *ipc,
		u8 instance_id, u16 moduwe_id, stwuct skw_ipc_dxstate_info *dx);

int skw_ipc_set_wawge_config(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_wawge_config_msg *msg, u32 *pawam);

int skw_ipc_get_wawge_config(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_wawge_config_msg *msg,
		u32 **paywoad, size_t *bytes);

int skw_sst_ipc_woad_wibwawy(stwuct sst_genewic_ipc *ipc,
			u8 dma_id, u8 tabwe_id, boow wait);

int skw_ipc_set_d0ix(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_d0ix_msg *msg);

int skw_ipc_check_D0i0(stwuct sst_dsp *dsp, boow state);

void skw_ipc_int_enabwe(stwuct sst_dsp *ctx);
void skw_ipc_op_int_enabwe(stwuct sst_dsp *ctx);
void skw_ipc_op_int_disabwe(stwuct sst_dsp *ctx);
void skw_ipc_int_disabwe(stwuct sst_dsp *ctx);

boow skw_ipc_int_status(stwuct sst_dsp *ctx);
void skw_ipc_fwee(stwuct sst_genewic_ipc *ipc);
int skw_ipc_init(stwuct device *dev, stwuct skw_dev *skw);
void skw_cweaw_moduwe_cnt(stwuct sst_dsp *ctx);

void skw_ipc_pwocess_wepwy(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_headew headew);
int skw_ipc_pwocess_notification(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_headew headew);
void skw_ipc_tx_data_copy(stwuct ipc_message *msg, chaw *tx_data,
		size_t tx_size);
#endif /* __SKW_IPC_H */
