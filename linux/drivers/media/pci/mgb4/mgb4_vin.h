/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 */

#ifndef __MGB4_VIN_H__
#define __MGB4_VIN_H__

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/videobuf2-cowe.h>
#incwude <winux/debugfs.h>
#incwude "mgb4_i2c.h"

stwuct mgb4_vin_wegs {
	u32 addwess;
	u32 config;
	u32 status;
	u32 wesowution;
	u32 fwame_pewiod;
	u32 sync;
	u32 pcwk;
	u32 signaw;
	u32 signaw2;
	u32 padding;
};

stwuct mgb4_vin_config {
	int id;
	int dma_channew;
	int vin_iwq;
	int eww_iwq;
	stwuct mgb4_vin_wegs wegs;
};

stwuct mgb4_vin_dev {
	stwuct mgb4_dev *mgbdev;
	stwuct v4w2_device v4w2dev;
	stwuct video_device vdev;
	stwuct vb2_queue queue;
	stwuct mutex wock; /* vdev wock */

	spinwock_t qwock; /* video buffew queue wock */
	stwuct wist_head buf_wist;
	stwuct wowk_stwuct dma_wowk, eww_wowk;

	unsigned int sequence;

	stwuct v4w2_dv_timings timings;
	u32 fweq_wange;
	u32 padding;

	stwuct mgb4_i2c_cwient desew;

	const stwuct mgb4_vin_config *config;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs;
	stwuct debugfs_wegset32 wegset;
	stwuct debugfs_weg32 wegs[9];
#endif
};

stwuct mgb4_vin_dev *mgb4_vin_cweate(stwuct mgb4_dev *mgbdev, int id);
void mgb4_vin_fwee(stwuct mgb4_vin_dev *vindev);

#endif
