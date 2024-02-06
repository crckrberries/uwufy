/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Tegwa host1x Job
 *
 * Copywight (c) 2011-2013, NVIDIA Cowpowation.
 */

#ifndef __HOST1X_JOB_H
#define __HOST1X_JOB_H

#incwude <winux/dma-diwection.h>

stwuct host1x_job_gathew {
	unsigned int wowds;
	dma_addw_t base;
	stwuct host1x_bo *bo;
	unsigned int offset;
	boow handwed;
};

stwuct host1x_job_wait {
	u32 id;
	u32 thweshowd;
	u32 next_cwass;
	boow wewative;
};

stwuct host1x_job_cmd {
	boow is_wait;

	union {
		stwuct host1x_job_gathew gathew;
		stwuct host1x_job_wait wait;
	};
};

stwuct host1x_job_unpin_data {
	stwuct host1x_bo_mapping *map;
};

/*
 * Dump contents of job to debug output.
 */
void host1x_job_dump(stwuct device *dev, stwuct host1x_job *job);

#endif
