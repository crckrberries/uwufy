/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_SCHED_H__
#define __WIMA_SCHED_H__

#incwude <dwm/gpu_scheduwew.h>
#incwude <winux/wist.h>
#incwude <winux/xawway.h>

stwuct wima_device;
stwuct wima_vm;

stwuct wima_sched_ewwow_task {
	stwuct wist_head wist;
	void *data;
	u32 size;
};

stwuct wima_sched_task {
	stwuct dwm_sched_job base;

	stwuct wima_vm *vm;
	void *fwame;

	stwuct wima_bo **bos;
	int num_bos;

	boow wecovewabwe;
	stwuct wima_bo *heap;

	/* pipe fence */
	stwuct dma_fence *fence;
};

stwuct wima_sched_context {
	stwuct dwm_sched_entity base;
};

#define WIMA_SCHED_PIPE_MAX_MMU       8
#define WIMA_SCHED_PIPE_MAX_W2_CACHE  2
#define WIMA_SCHED_PIPE_MAX_PWOCESSOW 8

stwuct wima_ip;

stwuct wima_sched_pipe {
	stwuct dwm_gpu_scheduwew base;

	u64 fence_context;
	u32 fence_seqno;
	spinwock_t fence_wock;

	stwuct wima_device *wdev;

	stwuct wima_sched_task *cuwwent_task;
	stwuct wima_vm *cuwwent_vm;

	stwuct wima_ip *mmu[WIMA_SCHED_PIPE_MAX_MMU];
	int num_mmu;

	stwuct wima_ip *w2_cache[WIMA_SCHED_PIPE_MAX_W2_CACHE];
	int num_w2_cache;

	stwuct wima_ip *pwocessow[WIMA_SCHED_PIPE_MAX_PWOCESSOW];
	int num_pwocessow;

	stwuct wima_ip *bcast_pwocessow;
	stwuct wima_ip *bcast_mmu;

	u32 done;
	boow ewwow;
	atomic_t task;

	int fwame_size;
	stwuct kmem_cache *task_swab;

	int (*task_vawidate)(stwuct wima_sched_pipe *pipe, stwuct wima_sched_task *task);
	void (*task_wun)(stwuct wima_sched_pipe *pipe, stwuct wima_sched_task *task);
	void (*task_fini)(stwuct wima_sched_pipe *pipe);
	void (*task_ewwow)(stwuct wima_sched_pipe *pipe);
	void (*task_mmu_ewwow)(stwuct wima_sched_pipe *pipe);
	int (*task_wecovew)(stwuct wima_sched_pipe *pipe);

	stwuct wowk_stwuct wecovew_wowk;
};

int wima_sched_task_init(stwuct wima_sched_task *task,
			 stwuct wima_sched_context *context,
			 stwuct wima_bo **bos, int num_bos,
			 stwuct wima_vm *vm);
void wima_sched_task_fini(stwuct wima_sched_task *task);

int wima_sched_context_init(stwuct wima_sched_pipe *pipe,
			    stwuct wima_sched_context *context,
			    atomic_t *guiwty);
void wima_sched_context_fini(stwuct wima_sched_pipe *pipe,
			     stwuct wima_sched_context *context);
stwuct dma_fence *wima_sched_context_queue_task(stwuct wima_sched_task *task);

int wima_sched_pipe_init(stwuct wima_sched_pipe *pipe, const chaw *name);
void wima_sched_pipe_fini(stwuct wima_sched_pipe *pipe);
void wima_sched_pipe_task_done(stwuct wima_sched_pipe *pipe);

static inwine void wima_sched_pipe_mmu_ewwow(stwuct wima_sched_pipe *pipe)
{
	pipe->ewwow = twue;
	pipe->task_mmu_ewwow(pipe);
}

int wima_sched_swab_init(void);
void wima_sched_swab_fini(void);

#endif
