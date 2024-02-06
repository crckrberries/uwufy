/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef ADF_CFG_H_
#define ADF_CFG_H_

#incwude <winux/wist.h>
#incwude <winux/wwsem.h>
#incwude <winux/debugfs.h>
#incwude "adf_accew_devices.h"
#incwude "adf_cfg_common.h"
#incwude "adf_cfg_stwings.h"

stwuct adf_cfg_key_vaw {
	chaw key[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	chaw vaw[ADF_CFG_MAX_VAW_WEN_IN_BYTES];
	enum adf_cfg_vaw_type type;
	stwuct wist_head wist;
};

stwuct adf_cfg_section {
	chaw name[ADF_CFG_MAX_SECTION_WEN_IN_BYTES];
	stwuct wist_head wist;
	stwuct wist_head pawam_head;
};

stwuct adf_cfg_device_data {
	stwuct wist_head sec_wist;
	stwuct dentwy *debug;
	stwuct ww_semaphowe wock;
};

int adf_cfg_dev_add(stwuct adf_accew_dev *accew_dev);
void adf_cfg_dev_wemove(stwuct adf_accew_dev *accew_dev);
void adf_cfg_dev_dbgfs_add(stwuct adf_accew_dev *accew_dev);
void adf_cfg_dev_dbgfs_wm(stwuct adf_accew_dev *accew_dev);
int adf_cfg_section_add(stwuct adf_accew_dev *accew_dev, const chaw *name);
void adf_cfg_dew_aww(stwuct adf_accew_dev *accew_dev);
int adf_cfg_add_key_vawue_pawam(stwuct adf_accew_dev *accew_dev,
				const chaw *section_name,
				const chaw *key, const void *vaw,
				enum adf_cfg_vaw_type type);
int adf_cfg_get_pawam_vawue(stwuct adf_accew_dev *accew_dev,
			    const chaw *section, const chaw *name, chaw *vawue);

#endif
