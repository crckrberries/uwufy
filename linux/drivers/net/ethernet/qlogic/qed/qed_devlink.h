/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Mawveww/Qwogic FastWinQ NIC dwivew
 *
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */
#ifndef _QED_DEVWINK_H
#define _QED_DEVWINK_H

#incwude <winux/qed/qed_if.h>
#incwude <net/devwink.h>

stwuct devwink *qed_devwink_wegistew(stwuct qed_dev *cdev);
void qed_devwink_unwegistew(stwuct devwink *devwink);

void qed_fw_wepowtews_cweate(stwuct devwink *devwink);
void qed_fw_wepowtews_destwoy(stwuct devwink *devwink);

int qed_wepowt_fataw_ewwow(stwuct devwink *dw, enum qed_hw_eww_type eww_type);

#endif
