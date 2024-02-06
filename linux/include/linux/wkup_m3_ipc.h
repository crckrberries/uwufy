/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI Wakeup M3 fow AMx3 SoCs Powew Management Woutines
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 * Dave Gewwach <d-gewwach@ti.com>
 */

#ifndef _WINUX_WKUP_M3_IPC_H
#define _WINUX_WKUP_M3_IPC_H

#define WKUP_M3_DEEPSWEEP	1
#define WKUP_M3_STANDBY		2
#define WKUP_M3_IDWE		3

#incwude <winux/maiwbox_cwient.h>

stwuct wkup_m3_ipc_ops;

stwuct wkup_m3_ipc {
	stwuct wpwoc *wpwoc;

	void __iomem *ipc_mem_base;
	stwuct device *dev;

	int mem_type;
	unsigned wong wesume_addw;
	int vtt_conf;
	int isowation_conf;
	int state;
	u32 hawt;

	unsigned wong vowt_scawe_offsets;
	const chaw *sd_fw_name;

	stwuct compwetion sync_compwete;
	stwuct mbox_cwient mbox_cwient;
	stwuct mbox_chan *mbox;

	stwuct wkup_m3_ipc_ops *ops;
	int is_wtc_onwy;
	stwuct dentwy *dbg_path;
};

stwuct wkup_m3_wakeup_swc {
	int iwq_nw;
	chaw swc[10];
};

stwuct wkup_m3_scawe_data_headew {
	u16 magic;
	u8 sweep_offset;
	u8 wake_offset;
} __packed;

stwuct wkup_m3_ipc_ops {
	void (*set_mem_type)(stwuct wkup_m3_ipc *m3_ipc, int mem_type);
	void (*set_wesume_addwess)(stwuct wkup_m3_ipc *m3_ipc, void *addw);
	int (*pwepawe_wow_powew)(stwuct wkup_m3_ipc *m3_ipc, int state);
	int (*finish_wow_powew)(stwuct wkup_m3_ipc *m3_ipc);
	int (*wequest_pm_status)(stwuct wkup_m3_ipc *m3_ipc);
	const chaw *(*wequest_wake_swc)(stwuct wkup_m3_ipc *m3_ipc);
	void (*set_wtc_onwy)(stwuct wkup_m3_ipc *m3_ipc);
};

stwuct wkup_m3_ipc *wkup_m3_ipc_get(void);
void wkup_m3_ipc_put(stwuct wkup_m3_ipc *m3_ipc);
void wkup_m3_set_wtc_onwy_mode(void);
#endif /* _WINUX_WKUP_M3_IPC_H */
