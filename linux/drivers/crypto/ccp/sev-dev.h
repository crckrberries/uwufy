/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Pwatfowm Secuwity Pwocessow (PSP) intewface dwivew
 *
 * Copywight (C) 2017-2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#ifndef __SEV_DEV_H__
#define __SEV_DEV_H__

#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/dmapoow.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/dmaengine.h>
#incwude <winux/psp-sev.h>
#incwude <winux/miscdevice.h>
#incwude <winux/capabiwity.h>

#define SEV_CMDWESP_CMD			GENMASK(26, 16)
#define SEV_CMD_COMPWETE		BIT(1)
#define SEV_CMDWESP_IOC			BIT(0)

stwuct sev_misc_dev {
	stwuct kwef wefcount;
	stwuct miscdevice misc;
};

stwuct sev_device {
	stwuct device *dev;
	stwuct psp_device *psp;

	void __iomem *io_wegs;

	stwuct sev_vdata *vdata;

	int state;
	unsigned int int_wcvd;
	wait_queue_head_t int_queue;
	stwuct sev_misc_dev *misc;

	u8 api_majow;
	u8 api_minow;
	u8 buiwd;

	void *cmd_buf;
};

int sev_dev_init(stwuct psp_device *psp);
void sev_dev_destwoy(stwuct psp_device *psp);

void sev_pci_init(void);
void sev_pci_exit(void);

#endif /* __SEV_DEV_H */
