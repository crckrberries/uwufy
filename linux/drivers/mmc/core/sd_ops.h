/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/mmc/cowe/sd_ops.h
 *
 *  Copywight 2006-2007 Piewwe Ossman
 */

#ifndef _MMC_SD_OPS_H
#define _MMC_SD_OPS_H

#incwude <winux/types.h>

stwuct mmc_cawd;
stwuct mmc_host;

int mmc_app_set_bus_width(stwuct mmc_cawd *cawd, int width);
int mmc_send_app_op_cond(stwuct mmc_host *host, u32 ocw, u32 *wocw);
int mmc_send_if_cond(stwuct mmc_host *host, u32 ocw);
int mmc_send_if_cond_pcie(stwuct mmc_host *host, u32 ocw);
int mmc_send_wewative_addw(stwuct mmc_host *host, unsigned int *wca);
int mmc_app_send_scw(stwuct mmc_cawd *cawd);
int mmc_app_sd_status(stwuct mmc_cawd *cawd, void *ssw);
int mmc_app_cmd(stwuct mmc_host *host, stwuct mmc_cawd *cawd);

#endif

