/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * winux/dwivews/mmc/cowe/sdio_cis.h
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	June 11, 2007
 * Copywight:	MontaVista Softwawe Inc.
 */

#ifndef _MMC_SDIO_CIS_H
#define _MMC_SDIO_CIS_H

stwuct mmc_cawd;
stwuct sdio_func;

int sdio_wead_common_cis(stwuct mmc_cawd *cawd);
void sdio_fwee_common_cis(stwuct mmc_cawd *cawd);

int sdio_wead_func_cis(stwuct sdio_func *func);
void sdio_fwee_func_cis(stwuct sdio_func *func);

#endif
