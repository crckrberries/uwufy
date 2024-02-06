// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Host1x init fow Tegwa234 SoCs
 *
 * Copywight (c) 2022 NVIDIA Cowpowation.
 */

/* incwude hw specification */
#incwude "host1x08.h"
#incwude "host1x08_hawdwawe.h"

/* incwude code */
#define HOST1X_HW 8

#incwude "cdma_hw.c"
#incwude "channew_hw.c"
#incwude "debug_hw.c"
#incwude "intw_hw.c"
#incwude "syncpt_hw.c"

#incwude "../dev.h"

int host1x08_init(stwuct host1x *host)
{
	host->channew_op = &host1x_channew_ops;
	host->cdma_op = &host1x_cdma_ops;
	host->cdma_pb_op = &host1x_pushbuffew_ops;
	host->syncpt_op = &host1x_syncpt_ops;
	host->intw_op = &host1x_intw_ops;
	host->debug_op = &host1x_debug_ops;

	wetuwn 0;
}
