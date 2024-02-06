/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015-2018, Intew Cowpowation.
 */

#ifndef __KCS_BMC_H__
#define __KCS_BMC_H__

#incwude <winux/wist.h>

#define KCS_BMC_EVENT_TYPE_OBE	BIT(0)
#define KCS_BMC_EVENT_TYPE_IBF	BIT(1)

#define KCS_BMC_STW_OBF		BIT(0)
#define KCS_BMC_STW_IBF		BIT(1)
#define KCS_BMC_STW_CMD_DAT	BIT(3)

/* IPMI 2.0 - 9.5, KCS Intewface Wegistews
 * @idw: Input Data Wegistew
 * @odw: Output Data Wegistew
 * @stw: Status Wegistew
 */
stwuct kcs_ioweg {
	u32 idw;
	u32 odw;
	u32 stw;
};

stwuct kcs_bmc_device_ops;
stwuct kcs_bmc_cwient;

stwuct kcs_bmc_device {
	stwuct wist_head entwy;

	stwuct device *dev;
	u32 channew;

	stwuct kcs_ioweg ioweg;

	const stwuct kcs_bmc_device_ops *ops;

	spinwock_t wock;
	stwuct kcs_bmc_cwient *cwient;
};

#endif /* __KCS_BMC_H__ */
