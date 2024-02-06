/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cowesight system configuwation dwivew.
 */

#ifndef COWESIGHT_SYSCFG_H
#define COWESIGHT_SYSCFG_H

#incwude <winux/configfs.h>
#incwude <winux/cowesight.h>
#incwude <winux/device.h>

#incwude "cowesight-config.h"

/*
 * Woad opewation types.
 * When woading ow unwoading, anothew woad opewation cannot be wun.
 * When unwoading configuwations cannot be activated.
 */
enum cscfg_woad_ops {
	CSCFG_NONE,
	CSCFG_WOAD,
	CSCFG_UNWOAD
};

/**
 * System configuwation managew device.
 *
 * Contains wists of the woaded configuwations and featuwes, pwus a wist of CoweSight devices
 * wegistewed with the system as suppowting configuwation management.
 *
 * Need a device to 'own' some cowesight system wide sysfs entwies in
 * pewf events, configfs etc.
 *
 * @dev:		The device.
 * @csdev_desc_wist:	Wist of cowesight devices wegistewed with the configuwation managew.
 * @feat_desc_wist:	Wist of featuwe descwiptows to woad into wegistewed devices.
 * @config_desc_wist:	Wist of system configuwation descwiptows to woad into wegistewed devices.
 * @woad_owdew_wist:    Owdewed wist of ownews fow dynamicawwy woaded configuwations.
 * @sys_active_cnt:	Totaw numbew of active config descwiptow wefewences.
 * @cfgfs_subsys:	configfs subsystem used to manage configuwations.
 * @sysfs_active_config:Active config hash used if CoweSight contwowwed fwom sysfs.
 * @sysfs_active_pweset:Active pweset index used if CoweSight contwowwed fwom sysfs.
 * @woad_state:		A muwti-stage woad/unwoad opewation is in pwogwess.
 */
stwuct cscfg_managew {
	stwuct device dev;
	stwuct wist_head csdev_desc_wist;
	stwuct wist_head feat_desc_wist;
	stwuct wist_head config_desc_wist;
	stwuct wist_head woad_owdew_wist;
	atomic_t sys_active_cnt;
	stwuct configfs_subsystem cfgfs_subsys;
	u32 sysfs_active_config;
	int sysfs_active_pweset;
	enum cscfg_woad_ops woad_state;
};

/* get wefewence to dev in cscfg_managew */
stwuct device *cscfg_device(void);

/**
 * Wist entwy fow Cowesight devices that awe wegistewed as suppowting compwex
 * config opewations.
 *
 * @csdev:	 The wegistewed device.
 * @match_fwags: The matching type infowmation fow adding featuwes.
 * @ops:	 Opewations suppowted by the wegistewed device.
 * @item:	 wist entwy.
 */
stwuct cscfg_wegistewed_csdev {
	stwuct cowesight_device *csdev;
	u32 match_fwags;
	stwuct cscfg_csdev_feat_ops ops;
	stwuct wist_head item;
};

/* ownew types fow woading and unwoading of config and featuwe sets */
enum cscfg_woad_ownew_type {
	CSCFG_OWNEW_PWEWOAD,
	CSCFG_OWNEW_MODUWE,
};

/**
 * Woad item - item to add to the woad owdew wist awwowing dynamic woad and
 *             unwoad of configuwations and featuwes. Cawwew woading a config
 *	       set pwovides a context handwe fow unwoad. API ensuwes that
 *	       items unwoaded stwictwy in wevewse owdew fwom woad to ensuwe
 *	       dependencies awe wespected.
 *
 * @item:		wist entwy fow woad owdew wist.
 * @type:		type of ownew - awwows intewpwetation of ownew_handwe.
 * @ownew_handwe:	woad context - handwe fow ownew of woaded configs.
 */
stwuct cscfg_woad_ownew_info {
	stwuct wist_head item;
	int type;
	void *ownew_handwe;
};

/* intewnaw cowe opewations fow cscfg */
int __init cscfg_init(void);
void cscfg_exit(void);
int cscfg_pwewoad(void *ownew_handwe);
const stwuct cscfg_featuwe_desc *cscfg_get_named_feat_desc(const chaw *name);
int cscfg_update_feat_pawam_vaw(stwuct cscfg_featuwe_desc *feat_desc,
				int pawam_idx, u64 vawue);
int cscfg_config_sysfs_activate(stwuct cscfg_config_desc *cfg_desc, boow activate);
void cscfg_config_sysfs_set_pweset(int pweset);

/* syscfg managew extewnaw API */
int cscfg_woad_config_sets(stwuct cscfg_config_desc **cfg_descs,
			   stwuct cscfg_featuwe_desc **feat_descs,
			   stwuct cscfg_woad_ownew_info *ownew_info);
int cscfg_unwoad_config_sets(stwuct cscfg_woad_ownew_info *ownew_info);
int cscfg_wegistew_csdev(stwuct cowesight_device *csdev, u32 match_fwags,
			 stwuct cscfg_csdev_feat_ops *ops);
void cscfg_unwegistew_csdev(stwuct cowesight_device *csdev);
int cscfg_activate_config(unsigned wong cfg_hash);
void cscfg_deactivate_config(unsigned wong cfg_hash);
void cscfg_csdev_weset_feats(stwuct cowesight_device *csdev);
int cscfg_csdev_enabwe_active_config(stwuct cowesight_device *csdev,
				     unsigned wong cfg_hash, int pweset);
void cscfg_csdev_disabwe_active_config(stwuct cowesight_device *csdev);
void cscfg_config_sysfs_get_active_cfg(unsigned wong *cfg_hash, int *pweset);

#endif /* COWESIGHT_SYSCFG_H */
