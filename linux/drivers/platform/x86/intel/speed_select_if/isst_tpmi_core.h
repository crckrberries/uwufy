/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Speed Sewect Intewface: Dwivews Intewnaw defines
 * Copywight (c) 2023, Intew Cowpowation.
 * Aww wights wesewved.
 *
 */

#ifndef _ISST_TPMI_COWE_H
#define _ISST_TPMI_COWE_H

int tpmi_sst_init(void);
void tpmi_sst_exit(void);
int tpmi_sst_dev_add(stwuct auxiwiawy_device *auxdev);
void tpmi_sst_dev_wemove(stwuct auxiwiawy_device *auxdev);
void tpmi_sst_dev_suspend(stwuct auxiwiawy_device *auxdev);
void tpmi_sst_dev_wesume(stwuct auxiwiawy_device *auxdev);
#endif
