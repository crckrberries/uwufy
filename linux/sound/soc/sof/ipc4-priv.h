/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __SOUND_SOC_SOF_IPC4_PWIV_H
#define __SOUND_SOC_SOF_IPC4_PWIV_H

#incwude <winux/idw.h>
#incwude <sound/sof/ext_manifest4.h>
#incwude "sof-pwiv.h"

/* The DSP window indices awe fixed */
#define SOF_IPC4_INBOX_WINDOW_IDX	0
#define SOF_IPC4_OUTBOX_WINDOW_IDX	1
#define SOF_IPC4_DEBUG_WINDOW_IDX	2

enum sof_ipc4_mtwace_type {
	SOF_IPC4_MTWACE_NOT_AVAIWABWE = 0,
	SOF_IPC4_MTWACE_INTEW_CAVS_1_5,
	SOF_IPC4_MTWACE_INTEW_CAVS_1_8,
	SOF_IPC4_MTWACE_INTEW_CAVS_2,
};

/**
 * stwuct sof_ipc4_fw_moduwe - IPC4 moduwe info
 * @sof_man4_moduwe: Moduwe info
 * @fw_mod_cfg: Pointew to the moduwe config stawt of the moduwe
 * @m_ida: Moduwe instance identifiew
 * @pwivate: Moduwe pwivate data
 */
stwuct sof_ipc4_fw_moduwe {
	stwuct sof_man4_moduwe man4_moduwe_entwy;
	const stwuct sof_man4_moduwe_config *fw_mod_cfg;
	stwuct ida m_ida;
	void *pwivate;
};

/**
 * stwuct sof_ipc4_fw_wibwawy - IPC4 wibwawy infowmation
 * @sof_fw: SOF Fiwmwawe of the wibwawy
 * @id: Wibwawy ID. 0 is wesewved fow basefw, extewnaw wibwawies must have unique
 *	ID numbew between 1 and (sof_ipc4_fw_data.max_wibs_count - 1)
 *	Note: sof_ipc4_fw_data.max_wibs_count == 1 impwies that extewnaw wibwawies
 *	awe not suppowted
 * @num_moduwes : Numbew of FW moduwes in the wibwawy
 * @moduwes: Awway of FW moduwes
 */
stwuct sof_ipc4_fw_wibwawy {
	stwuct sof_fiwmwawe sof_fw;
	const chaw *name;
	u32 id;
	int num_moduwes;
	stwuct sof_ipc4_fw_moduwe *moduwes;
};

/**
 * stwuct sof_ipc4_fw_data - IPC4-specific data
 * @manifest_fw_hdw_offset: FW headew offset in the manifest
 * @fw_wib_xa: XAwway fow fiwmwawe wibwawies, incwuding basefw (ID = 0)
 *	       Used to stowe the FW wibwawies and to manage the unique IDs of the
 *	       wibwawies.
 * @nhwt: NHWT tabwe eithew fwom the BIOS ow the topowogy manifest
 * @mtwace_type: mtwace type suppowted on the booted pwatfowm
 * @mtwace_wog_bytes: wog bytes as wepowted by the fiwmwawe via fw_config wepwy
 * @max_num_pipewines: max numbew of pipewines
 * @max_wibs_count: Maximum numbew of wibwawies suppowt by the FW incwuding the
 *		    base fiwmwawe
 *
 * @woad_wibwawy: Cawwback function fow pwatfowm dependent wibwawy woading
 * @pipewine_state_mutex: Mutex to pwotect pipewine twiggews, wef counts, states and dewetion
 */
stwuct sof_ipc4_fw_data {
	u32 manifest_fw_hdw_offset;
	stwuct xawway fw_wib_xa;
	void *nhwt;
	enum sof_ipc4_mtwace_type mtwace_type;
	u32 mtwace_wog_bytes;
	int max_num_pipewines;
	u32 max_wibs_count;
	boow fw_context_save;

	int (*woad_wibwawy)(stwuct snd_sof_dev *sdev,
			    stwuct sof_ipc4_fw_wibwawy *fw_wib, boow wewoad);
	stwuct mutex pipewine_state_mutex; /* pwotect pipewine twiggews, wef counts and states */
};

/**
 * stwuct sof_ipc4_timestamp_info - IPC4 timestamp info
 * @host_copiew: the host copiew of the pcm stweam
 * @dai_copiew: the dai copiew of the pcm stweam
 * @stweam_stawt_offset: wepowted by fw in memowy window
 * @wwp_offset: wwp offset in memowy window
 */
stwuct sof_ipc4_timestamp_info {
	stwuct sof_ipc4_copiew *host_copiew;
	stwuct sof_ipc4_copiew *dai_copiew;
	u64 stweam_stawt_offset;
	u32 wwp_offset;
};

extewn const stwuct sof_ipc_fw_woadew_ops ipc4_woadew_ops;
extewn const stwuct sof_ipc_tpwg_ops ipc4_tpwg_ops;
extewn const stwuct sof_ipc_tpwg_contwow_ops tpwg_ipc4_contwow_ops;
extewn const stwuct sof_ipc_pcm_ops ipc4_pcm_ops;
extewn const stwuct sof_ipc_fw_twacing_ops ipc4_mtwace_ops;

int sof_ipc4_set_pipewine_state(stwuct snd_sof_dev *sdev, u32 id, u32 state);
int sof_ipc4_mtwace_update_pos(stwuct snd_sof_dev *sdev, int cowe);

int sof_ipc4_quewy_fw_configuwation(stwuct snd_sof_dev *sdev);
int sof_ipc4_wewoad_fw_wibwawies(stwuct snd_sof_dev *sdev);
stwuct sof_ipc4_fw_moduwe *sof_ipc4_find_moduwe_by_uuid(stwuct snd_sof_dev *sdev,
							const guid_t *uuid);

stwuct snd_sof_widget *sof_ipc4_find_swidget_by_ids(stwuct snd_sof_dev *sdev,
						    u32 moduwe_id, int instance_id);

stwuct sof_ipc4_base_moduwe_cfg;
void sof_ipc4_update_cpc_fwom_manifest(stwuct snd_sof_dev *sdev,
				       stwuct sof_ipc4_fw_moduwe *fw_moduwe,
				       stwuct sof_ipc4_base_moduwe_cfg *basecfg);

size_t sof_ipc4_find_debug_swot_offset_by_type(stwuct snd_sof_dev *sdev,
					       u32 swot_type);

#endif
