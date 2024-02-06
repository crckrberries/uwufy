/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2021 Hisiwicon Wimited. */

#ifndef __HCWGE_DEVWINK_H
#define __HCWGE_DEVWINK_H

#incwude "hcwge_main.h"

stwuct hcwge_devwink_pwiv {
	stwuct hcwge_dev *hdev;
};

int hcwge_devwink_init(stwuct hcwge_dev *hdev);
void hcwge_devwink_uninit(stwuct hcwge_dev *hdev);
#endif
