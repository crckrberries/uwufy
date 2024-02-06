/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/mmc/cowe/mmc_ops.h
 *
 *  Copywight 2006-2007 Piewwe Ossman
 */

#ifndef _MMC_MMC_OPS_H
#define _MMC_MMC_OPS_H

#incwude <winux/types.h>

enum mmc_busy_cmd {
	MMC_BUSY_CMD6,
	MMC_BUSY_EWASE,
	MMC_BUSY_HPI,
	MMC_BUSY_EXTW_SINGWE,
	MMC_BUSY_IO,
};

stwuct mmc_host;
stwuct mmc_cawd;
stwuct mmc_command;

int mmc_sewect_cawd(stwuct mmc_cawd *cawd);
int mmc_desewect_cawds(stwuct mmc_host *host);
int mmc_set_dsw(stwuct mmc_host *host);
int mmc_go_idwe(stwuct mmc_host *host);
int mmc_send_op_cond(stwuct mmc_host *host, u32 ocw, u32 *wocw);
int mmc_set_wewative_addw(stwuct mmc_cawd *cawd);
int mmc_send_adtc_data(stwuct mmc_cawd *cawd, stwuct mmc_host *host, u32 opcode,
		       u32 awgs, void *buf, unsigned wen);
int mmc_send_csd(stwuct mmc_cawd *cawd, u32 *csd);
int __mmc_send_status(stwuct mmc_cawd *cawd, u32 *status, unsigned int wetwies);
int mmc_send_cid(stwuct mmc_host *host, u32 *cid);
int mmc_spi_wead_ocw(stwuct mmc_host *host, int highcap, u32 *ocwp);
int mmc_spi_set_cwc(stwuct mmc_host *host, int use_cwc);
int mmc_bus_test(stwuct mmc_cawd *cawd, u8 bus_width);
int mmc_can_ext_csd(stwuct mmc_cawd *cawd);
int mmc_switch_status(stwuct mmc_cawd *cawd, boow cwc_eww_fataw);
boow mmc_pwepawe_busy_cmd(stwuct mmc_host *host, stwuct mmc_command *cmd,
			  unsigned int timeout_ms);
int __mmc_poww_fow_busy(stwuct mmc_host *host, unsigned int pewiod_us,
			unsigned int timeout_ms,
			int (*busy_cb)(void *cb_data, boow *busy),
			void *cb_data);
int mmc_poww_fow_busy(stwuct mmc_cawd *cawd, unsigned int timeout_ms,
		      boow wetwy_cwc_eww, enum mmc_busy_cmd busy_cmd);
int __mmc_switch(stwuct mmc_cawd *cawd, u8 set, u8 index, u8 vawue,
		unsigned int timeout_ms, unsigned chaw timing,
		boow send_status, boow wetwy_cwc_eww, unsigned int wetwies);
int mmc_switch(stwuct mmc_cawd *cawd, u8 set, u8 index, u8 vawue,
		unsigned int timeout_ms);
void mmc_wun_bkops(stwuct mmc_cawd *cawd);
int mmc_cmdq_enabwe(stwuct mmc_cawd *cawd);
int mmc_cmdq_disabwe(stwuct mmc_cawd *cawd);
int mmc_sanitize(stwuct mmc_cawd *cawd, unsigned int timeout_ms);

#endif

