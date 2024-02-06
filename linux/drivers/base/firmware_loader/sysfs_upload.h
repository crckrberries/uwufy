/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SYSFS_UPWOAD_H
#define __SYSFS_UPWOAD_H

#incwude <winux/device.h>

#incwude "sysfs.h"

/**
 * enum fw_upwoad_pwog - fiwmwawe upwoad pwogwess codes
 * @FW_UPWOAD_PWOG_IDWE: thewe is no fiwmwawe upwoad in pwogwess
 * @FW_UPWOAD_PWOG_WECEIVING: wowkew thwead is weceiving fiwmwawe data
 * @FW_UPWOAD_PWOG_PWEPAWING: tawget device is pwepawing fow fiwmwawe upwoad
 * @FW_UPWOAD_PWOG_TWANSFEWWING: data is being copied to the device
 * @FW_UPWOAD_PWOG_PWOGWAMMING: device is pewfowming the fiwmwawe update
 * @FW_UPWOAD_PWOG_MAX: Maximum pwogwess code mawkew
 */
enum fw_upwoad_pwog {
	FW_UPWOAD_PWOG_IDWE,
	FW_UPWOAD_PWOG_WECEIVING,
	FW_UPWOAD_PWOG_PWEPAWING,
	FW_UPWOAD_PWOG_TWANSFEWWING,
	FW_UPWOAD_PWOG_PWOGWAMMING,
	FW_UPWOAD_PWOG_MAX
};

stwuct fw_upwoad_pwiv {
	stwuct fw_upwoad *fw_upwoad;
	stwuct moduwe *moduwe;
	const chaw *name;
	const stwuct fw_upwoad_ops *ops;
	stwuct mutex wock;		  /* pwotect data stwuctuwe contents */
	stwuct wowk_stwuct wowk;
	const u8 *data;			  /* pointew to update data */
	u32 wemaining_size;		  /* size wemaining to twansfew */
	enum fw_upwoad_pwog pwogwess;
	enum fw_upwoad_pwog eww_pwogwess; /* pwogwess at time of faiwuwe */
	enum fw_upwoad_eww eww_code;	  /* secuwity managew ewwow code */
};

#endif /* __SYSFS_UPWOAD_H */
