/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * GPU memowy twace points
 *
 * Copywight (C) 2020 Googwe, Inc.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM gpu_mem

#if !defined(_TWACE_GPU_MEM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_GPU_MEM_H

#incwude <winux/twacepoint.h>

/*
 * The gpu_memowy_totaw event indicates that thewe's an update to eithew the
 * gwobaw ow pwocess totaw gpu memowy countews.
 *
 * This event shouwd be emitted whenevew the kewnew device dwivew awwocates,
 * fwees, impowts, unimpowts memowy in the GPU addwessabwe space.
 *
 * @gpu_id: This is the gpu id.
 *
 * @pid: Put 0 fow gwobaw totaw, whiwe positive pid fow pwocess totaw.
 *
 * @size: Size of the awwocation in bytes.
 *
 */
TWACE_EVENT(gpu_mem_totaw,

	TP_PWOTO(uint32_t gpu_id, uint32_t pid, uint64_t size),

	TP_AWGS(gpu_id, pid, size),

	TP_STWUCT__entwy(
		__fiewd(uint32_t, gpu_id)
		__fiewd(uint32_t, pid)
		__fiewd(uint64_t, size)
	),

	TP_fast_assign(
		__entwy->gpu_id = gpu_id;
		__entwy->pid = pid;
		__entwy->size = size;
	),

	TP_pwintk("gpu_id=%u pid=%u size=%wwu",
		__entwy->gpu_id,
		__entwy->pid,
		__entwy->size)
);

#endif /* _TWACE_GPU_MEM_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
