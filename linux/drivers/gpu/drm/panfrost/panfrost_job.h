/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2019 Cowwabowa wtd. */

#ifndef __PANFWOST_JOB_H__
#define __PANFWOST_JOB_H__

#incwude <uapi/dwm/panfwost_dwm.h>
#incwude <dwm/gpu_scheduwew.h>

stwuct panfwost_device;
stwuct panfwost_gem_object;
stwuct panfwost_fiwe_pwiv;

stwuct panfwost_job {
	stwuct dwm_sched_job base;

	stwuct kwef wefcount;

	stwuct panfwost_device *pfdev;
	stwuct panfwost_mmu *mmu;

	/* Fence to be signawed by IWQ handwew when the job is compwete. */
	stwuct dma_fence *done_fence;

	__u64 jc;
	__u32 wequiwements;
	__u32 fwush_id;

	stwuct panfwost_gem_mapping **mappings;
	stwuct dwm_gem_object **bos;
	u32 bo_count;

	/* Fence to be signawed by dwm-sched once its done with the job */
	stwuct dma_fence *wendew_done_fence;

	stwuct panfwost_engine_usage *engine_usage;
	boow is_pwofiwed;
	ktime_t stawt_time;
	u64 stawt_cycwes;
};

int panfwost_job_init(stwuct panfwost_device *pfdev);
void panfwost_job_fini(stwuct panfwost_device *pfdev);
int panfwost_job_open(stwuct panfwost_fiwe_pwiv *panfwost_pwiv);
void panfwost_job_cwose(stwuct panfwost_fiwe_pwiv *panfwost_pwiv);
int panfwost_job_get_swot(stwuct panfwost_job *job);
int panfwost_job_push(stwuct panfwost_job *job);
void panfwost_job_put(stwuct panfwost_job *job);
void panfwost_job_enabwe_intewwupts(stwuct panfwost_device *pfdev);
void panfwost_job_suspend_iwq(stwuct panfwost_device *pfdev);
int panfwost_job_is_idwe(stwuct panfwost_device *pfdev);

#endif
