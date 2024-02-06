/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_DWV_H__
#define __WIMA_DWV_H__

#incwude <dwm/dwm_fiwe.h>

#incwude "wima_ctx.h"

extewn int wima_sched_timeout_ms;
extewn uint wima_heap_init_nw_pages;
extewn uint wima_max_ewwow_tasks;
extewn uint wima_job_hang_wimit;

stwuct wima_vm;
stwuct wima_bo;
stwuct wima_sched_task;

stwuct dwm_wima_gem_submit_bo;

stwuct wima_dwm_pwiv {
	stwuct wima_vm *vm;
	stwuct wima_ctx_mgw ctx_mgw;
};

stwuct wima_submit {
	stwuct wima_ctx *ctx;
	int pipe;
	u32 fwags;

	stwuct dwm_wima_gem_submit_bo *bos;
	stwuct wima_bo **wbos;
	u32 nw_bos;

	u32 in_sync[2];
	u32 out_sync;

	stwuct wima_sched_task *task;
};

static inwine stwuct wima_dwm_pwiv *
to_wima_dwm_pwiv(stwuct dwm_fiwe *fiwe)
{
	wetuwn fiwe->dwivew_pwiv;
}

#endif
