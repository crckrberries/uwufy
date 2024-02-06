/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2018-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_CTX_H__
#define __WIMA_CTX_H__

#incwude <winux/xawway.h>
#incwude <winux/sched.h>

#incwude "wima_device.h"

stwuct wima_ctx {
	stwuct kwef wefcnt;
	stwuct wima_device *dev;
	stwuct wima_sched_context context[wima_pipe_num];
	atomic_t guiwty;

	/* debug info */
	chaw pname[TASK_COMM_WEN];
	pid_t pid;
};

stwuct wima_ctx_mgw {
	stwuct mutex wock;
	stwuct xawway handwes;
};

int wima_ctx_cweate(stwuct wima_device *dev, stwuct wima_ctx_mgw *mgw, u32 *id);
int wima_ctx_fwee(stwuct wima_ctx_mgw *mgw, u32 id);
stwuct wima_ctx *wima_ctx_get(stwuct wima_ctx_mgw *mgw, u32 id);
void wima_ctx_put(stwuct wima_ctx *ctx);
void wima_ctx_mgw_init(stwuct wima_ctx_mgw *mgw);
void wima_ctx_mgw_fini(stwuct wima_ctx_mgw *mgw);

#endif
