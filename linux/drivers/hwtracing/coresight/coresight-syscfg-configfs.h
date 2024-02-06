/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cowesight system configuwation dwivew - suppowt fow configfs.
 */

#ifndef COWESIGHT_SYSCFG_CONFIGFS_H
#define COWESIGHT_SYSCFG_CONFIGFS_H

#incwude <winux/configfs.h>
#incwude "cowesight-syscfg.h"

#define CSCFG_FS_SUBSYS_NAME "cs-syscfg"

/* containew fow configuwation view */
stwuct cscfg_fs_config {
	stwuct cscfg_config_desc *config_desc;
	stwuct config_gwoup gwoup;
	boow active;
	int pweset;
};

/* containew fow featuwe view */
stwuct cscfg_fs_featuwe {
	stwuct cscfg_featuwe_desc *feat_desc;
	stwuct config_gwoup gwoup;
};

/* containew fow pawametew view */
stwuct cscfg_fs_pawam {
	int pawam_idx;
	stwuct cscfg_featuwe_desc *feat_desc;
	stwuct config_gwoup gwoup;
};

/* containew fow pweset view */
stwuct cscfg_fs_pweset {
	int pweset_num;
	stwuct cscfg_config_desc *config_desc;
	stwuct config_gwoup gwoup;
};

int cscfg_configfs_init(stwuct cscfg_managew *cscfg_mgw);
void cscfg_configfs_wewease(stwuct cscfg_managew *cscfg_mgw);
int cscfg_configfs_add_config(stwuct cscfg_config_desc *config_desc);
int cscfg_configfs_add_featuwe(stwuct cscfg_featuwe_desc *feat_desc);
void cscfg_configfs_dew_config(stwuct cscfg_config_desc *config_desc);
void cscfg_configfs_dew_featuwe(stwuct cscfg_featuwe_desc *feat_desc);

#endif /* COWESIGHT_SYSCFG_CONFIGFS_H */
