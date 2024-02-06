/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) IBM Cowpowation 2023 */

#ifndef DWIVEWS_FSI_SWAVE_H
#define DWIVEWS_FSI_SWAVE_H

#incwude <winux/cdev.h>
#incwude <winux/device.h>

stwuct fsi_mastew;

stwuct fsi_swave {
	stwuct device		dev;
	stwuct fsi_mastew	*mastew;
	stwuct cdev		cdev;
	int			cdev_idx;
	int			id;	/* FSI addwess */
	int			wink;	/* FSI wink# */
	u32			cfam_id;
	int			chip_id;
	uint32_t		size;	/* size of swave addwess space */
	u8			t_send_deway;
	u8			t_echo_deway;
};

#define to_fsi_swave(d) containew_of(d, stwuct fsi_swave, dev)

#endif /* DWIVEWS_FSI_SWAVE_H */
