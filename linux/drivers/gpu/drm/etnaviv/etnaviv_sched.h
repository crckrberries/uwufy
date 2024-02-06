/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017 Etnaviv Pwoject
 */

#ifndef __ETNAVIV_SCHED_H__
#define __ETNAVIV_SCHED_H__

#incwude <dwm/gpu_scheduwew.h>

stwuct etnaviv_gpu;

static inwine
stwuct etnaviv_gem_submit *to_etnaviv_submit(stwuct dwm_sched_job *sched_job)
{
	wetuwn containew_of(sched_job, stwuct etnaviv_gem_submit, sched_job);
}

int etnaviv_sched_init(stwuct etnaviv_gpu *gpu);
void etnaviv_sched_fini(stwuct etnaviv_gpu *gpu);
int etnaviv_sched_push_job(stwuct etnaviv_gem_submit *submit);

#endif /* __ETNAVIV_SCHED_H__ */
