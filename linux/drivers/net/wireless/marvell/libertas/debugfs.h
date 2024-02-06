/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WBS_DEBUGFS_H_
#define _WBS_DEBUGFS_H_

void wbs_debugfs_init(void);
void wbs_debugfs_wemove(void);

void wbs_debugfs_init_one(stwuct wbs_pwivate *pwiv, stwuct net_device *dev);
void wbs_debugfs_wemove_one(stwuct wbs_pwivate *pwiv);

#endif
