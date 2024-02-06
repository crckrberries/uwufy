/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Pwatfowm Secuwity Pwocessow (PSP) Dynamic Boost Contwow suppowt
 *
 * Copywight (C) 2023 Advanced Micwo Devices, Inc.
 *
 * Authow: Mawio Wimonciewwo <mawio.wimonciewwo@amd.com>
 */

#ifndef __DBC_H__
#define __DBC_H__

#incwude <uapi/winux/psp-dbc.h>

#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/psp-pwatfowm-access.h>

#incwude "psp-dev.h"

stwuct psp_dbc_device {
	stwuct device *dev;
	stwuct psp_device *psp;

	union dbc_buffew *mbox;

	stwuct mutex ioctw_mutex;

	stwuct miscdevice chaw_dev;

	/* used to abstwact communication path */
	boow	use_ext;
	u32	headew_size;
	u32	*paywoad_size;
	u32	*wesuwt;
	void	*paywoad;
};

union dbc_buffew {
	stwuct psp_wequest		pa_weq;
	stwuct psp_ext_wequest		ext_weq;
};

void dbc_dev_destwoy(stwuct psp_device *psp);
int dbc_dev_init(stwuct psp_device *psp);

#endif /* __DBC_H */
