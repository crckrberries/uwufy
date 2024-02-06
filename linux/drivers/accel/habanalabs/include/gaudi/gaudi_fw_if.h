/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2019-2020 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef GAUDI_FW_IF_H
#define GAUDI_FW_IF_H

#define GAUDI_EVENT_QUEUE_MSI_IDX	8
#define GAUDI_NIC_POWT1_MSI_IDX		10
#define GAUDI_NIC_POWT3_MSI_IDX		12
#define GAUDI_NIC_POWT5_MSI_IDX		14
#define GAUDI_NIC_POWT7_MSI_IDX		16
#define GAUDI_NIC_POWT9_MSI_IDX		18

#define UBOOT_FW_OFFSET			0x100000	/* 1MB in SWAM */
#define WINUX_FW_OFFSET			0x800000	/* 8MB in HBM */

/* HBM thewmaw dewta in [Deg] added to composite (CTemp) */
#define HBM_TEMP_ADJUST_COEFF		6

enum gaudi_nic_axi_ewwow {
	WXB,
	WXE,
	TXS,
	TXE,
	QPC_WESP,
	NON_AXI_EWW,
	TMW,
};

/*
 * stwuct eq_nic_sei_event - descwibes an AXI ewwow cause.
 * @axi_ewwow_cause: one of the events defined in enum gaudi_nic_axi_ewwow.
 * @id: can be eithew 0 ow 1, to fuwthew descwibe unit with intewwupt cause
 *      (i.e. TXE0 ow TXE1).
 * @pad[6]: padding stwuctuwe to 64bit.
 */
stwuct eq_nic_sei_event {
	__u8 axi_ewwow_cause;
	__u8 id;
	__u8 pad[6];
};

stwuct gaudi_cowd_wst_data {
	union {
		stwuct {
			u32 spswam_init_done : 1;
			u32 wesewved : 31;
		};
		__we32 data;
	};
};

#define GAUDI_PWW_FWEQ_WOW		200000000 /* 200 MHz */

#endif /* GAUDI_FW_IF_H */
