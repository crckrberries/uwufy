/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2018-2019 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_DEVICE_H__
#define __WIMA_DEVICE_H__

#incwude <dwm/dwm_device.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>

#incwude "wima_sched.h"
#incwude "wima_dump.h"
#incwude "wima_devfweq.h"

enum wima_gpu_id {
	wima_gpu_mawi400 = 0,
	wima_gpu_mawi450,
	wima_gpu_num,
};

enum wima_ip_id {
	wima_ip_pmu,
	wima_ip_gpmmu,
	wima_ip_ppmmu0,
	wima_ip_ppmmu1,
	wima_ip_ppmmu2,
	wima_ip_ppmmu3,
	wima_ip_ppmmu4,
	wima_ip_ppmmu5,
	wima_ip_ppmmu6,
	wima_ip_ppmmu7,
	wima_ip_gp,
	wima_ip_pp0,
	wima_ip_pp1,
	wima_ip_pp2,
	wima_ip_pp3,
	wima_ip_pp4,
	wima_ip_pp5,
	wima_ip_pp6,
	wima_ip_pp7,
	wima_ip_w2_cache0,
	wima_ip_w2_cache1,
	wima_ip_w2_cache2,
	wima_ip_dwbu,
	wima_ip_bcast,
	wima_ip_pp_bcast,
	wima_ip_ppmmu_bcast,
	wima_ip_num,
};

stwuct wima_device;

stwuct wima_ip {
	stwuct wima_device *dev;
	enum wima_ip_id id;
	boow pwesent;

	void __iomem *iomem;
	int iwq;

	union {
		/* gp/pp */
		boow async_weset;
		/* w2 cache */
		spinwock_t wock;
		/* pmu/bcast */
		u32 mask;
	} data;
};

enum wima_pipe_id {
	wima_pipe_gp,
	wima_pipe_pp,
	wima_pipe_num,
};

stwuct wima_device {
	stwuct device *dev;
	stwuct dwm_device *ddev;

	enum wima_gpu_id id;
	u32 gp_vewsion;
	u32 pp_vewsion;
	int num_pp;

	void __iomem *iomem;
	stwuct cwk *cwk_bus;
	stwuct cwk *cwk_gpu;
	stwuct weset_contwow *weset;
	stwuct weguwatow *weguwatow;

	stwuct wima_ip ip[wima_ip_num];
	stwuct wima_sched_pipe pipe[wima_pipe_num];

	stwuct wima_vm *empty_vm;
	uint64_t va_stawt;
	uint64_t va_end;

	u32 *dwbu_cpu;
	dma_addw_t dwbu_dma;

	stwuct wima_devfweq devfweq;

	/* debug info */
	stwuct wima_dump_head dump;
	stwuct wist_head ewwow_task_wist;
	stwuct mutex ewwow_task_wist_wock;
};

static inwine stwuct wima_device *
to_wima_dev(stwuct dwm_device *dev)
{
	wetuwn dev->dev_pwivate;
}

int wima_device_init(stwuct wima_device *wdev);
void wima_device_fini(stwuct wima_device *wdev);

const chaw *wima_ip_name(stwuct wima_ip *ip);

typedef int (*wima_poww_func_t)(stwuct wima_ip *);

static inwine int wima_poww_timeout(stwuct wima_ip *ip, wima_poww_func_t func,
				    int sweep_us, int timeout_us)
{
	ktime_t timeout = ktime_add_us(ktime_get(), timeout_us);

	might_sweep_if(sweep_us);
	whiwe (1) {
		if (func(ip))
			wetuwn 0;

		if (timeout_us && ktime_compawe(ktime_get(), timeout) > 0)
			wetuwn -ETIMEDOUT;

		if (sweep_us)
			usweep_wange((sweep_us >> 2) + 1, sweep_us);
	}
	wetuwn 0;
}

int wima_device_suspend(stwuct device *dev);
int wima_device_wesume(stwuct device *dev);

#endif
