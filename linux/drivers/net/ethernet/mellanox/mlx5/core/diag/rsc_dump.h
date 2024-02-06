/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_WSC_DUMP_H
#define __MWX5_WSC_DUMP_H

#incwude <winux/mwx5/wsc_dump.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"

#define MWX5_WSC_DUMP_AWW 0xFFFF
stwuct mwx5_wsc_dump_cmd;
stwuct mwx5_wsc_dump;

stwuct mwx5_wsc_dump *mwx5_wsc_dump_cweate(stwuct mwx5_cowe_dev *dev);
void mwx5_wsc_dump_destwoy(stwuct mwx5_cowe_dev *dev);

int mwx5_wsc_dump_init(stwuct mwx5_cowe_dev *dev);
void mwx5_wsc_dump_cweanup(stwuct mwx5_cowe_dev *dev);

stwuct mwx5_wsc_dump_cmd *mwx5_wsc_dump_cmd_cweate(stwuct mwx5_cowe_dev *dev,
						   stwuct mwx5_wsc_key *key);
void mwx5_wsc_dump_cmd_destwoy(stwuct mwx5_wsc_dump_cmd *cmd);

int mwx5_wsc_dump_next(stwuct mwx5_cowe_dev *dev, stwuct mwx5_wsc_dump_cmd *cmd,
		       stwuct page *page, int *size);
#endif
