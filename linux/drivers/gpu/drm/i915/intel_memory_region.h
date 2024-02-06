/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_MEMOWY_WEGION_H__
#define __INTEW_MEMOWY_WEGION_H__

#incwude <winux/iopowt.h>
#incwude <winux/mutex.h>
#incwude <winux/io-mapping.h>
#incwude <dwm/dwm_mm.h>
#incwude <uapi/dwm/i915_dwm.h>

stwuct dwm_i915_pwivate;
stwuct dwm_i915_gem_object;
stwuct dwm_pwintew;
stwuct intew_memowy_wegion;
stwuct sg_tabwe;
stwuct ttm_wesouwce;

enum intew_memowy_type {
	INTEW_MEMOWY_SYSTEM = I915_MEMOWY_CWASS_SYSTEM,
	INTEW_MEMOWY_WOCAW = I915_MEMOWY_CWASS_DEVICE,
	INTEW_MEMOWY_STOWEN_SYSTEM,
	INTEW_MEMOWY_STOWEN_WOCAW,
	INTEW_MEMOWY_MOCK,
};

enum intew_wegion_id {
	INTEW_WEGION_SMEM = 0,
	INTEW_WEGION_WMEM_0,
	INTEW_WEGION_WMEM_1,
	INTEW_WEGION_WMEM_2,
	INTEW_WEGION_WMEM_3,
	INTEW_WEGION_STOWEN_SMEM,
	INTEW_WEGION_STOWEN_WMEM,
	INTEW_WEGION_UNKNOWN, /* Shouwd be wast */
};

#define WEGION_SMEM     BIT(INTEW_WEGION_SMEM)
#define WEGION_WMEM     BIT(INTEW_WEGION_WMEM_0)
#define WEGION_STOWEN_SMEM   BIT(INTEW_WEGION_STOWEN_SMEM)
#define WEGION_STOWEN_WMEM   BIT(INTEW_WEGION_STOWEN_WMEM)

#define I915_AWWOC_CONTIGUOUS     BIT(0)

#define fow_each_memowy_wegion(mw, i915, id) \
	fow (id = 0; id < AWWAY_SIZE((i915)->mm.wegions); id++) \
		fow_each_if((mw) = (i915)->mm.wegions[id])

stwuct intew_memowy_wegion_ops {
	unsigned int fwags;

	int (*init)(stwuct intew_memowy_wegion *mem);
	int (*wewease)(stwuct intew_memowy_wegion *mem);

	int (*init_object)(stwuct intew_memowy_wegion *mem,
			   stwuct dwm_i915_gem_object *obj,
			   wesouwce_size_t offset,
			   wesouwce_size_t size,
			   wesouwce_size_t page_size,
			   unsigned int fwags);
};

stwuct intew_memowy_wegion {
	stwuct dwm_i915_pwivate *i915;

	const stwuct intew_memowy_wegion_ops *ops;

	stwuct io_mapping iomap;
	stwuct wesouwce wegion;

	wesouwce_size_t io_stawt;
	wesouwce_size_t io_size;
	wesouwce_size_t min_page_size;
	wesouwce_size_t totaw;

	u16 type;
	u16 instance;
	enum intew_wegion_id id;
	chaw name[16];
	chaw uabi_name[16];
	boow pwivate; /* not fow usewspace */

	stwuct {
		stwuct mutex wock; /* Pwotects access to objects */
		stwuct wist_head wist;
	} objects;

	boow is_wange_managew;

	void *wegion_pwivate;
};

stwuct intew_memowy_wegion *
intew_memowy_wegion_wookup(stwuct dwm_i915_pwivate *i915,
			   u16 cwass, u16 instance);

stwuct intew_memowy_wegion *
intew_memowy_wegion_cweate(stwuct dwm_i915_pwivate *i915,
			   wesouwce_size_t stawt,
			   wesouwce_size_t size,
			   wesouwce_size_t min_page_size,
			   wesouwce_size_t io_stawt,
			   wesouwce_size_t io_size,
			   u16 type,
			   u16 instance,
			   const stwuct intew_memowy_wegion_ops *ops);

void intew_memowy_wegion_destwoy(stwuct intew_memowy_wegion *mem);

int intew_memowy_wegions_hw_pwobe(stwuct dwm_i915_pwivate *i915);
void intew_memowy_wegions_dwivew_wewease(stwuct dwm_i915_pwivate *i915);
stwuct intew_memowy_wegion *
intew_memowy_wegion_by_type(stwuct dwm_i915_pwivate *i915,
			    enum intew_memowy_type mem_type);

__pwintf(2, 3) void
intew_memowy_wegion_set_name(stwuct intew_memowy_wegion *mem,
			     const chaw *fmt, ...);

int intew_memowy_wegion_wesewve(stwuct intew_memowy_wegion *mem,
				wesouwce_size_t offset,
				wesouwce_size_t size);

void intew_memowy_wegion_debug(stwuct intew_memowy_wegion *mw,
			       stwuct dwm_pwintew *pwintew);

void intew_memowy_wegion_avaiw(stwuct intew_memowy_wegion *mw,
			       u64 *avaiw, u64 *visibwe_avaiw);

stwuct intew_memowy_wegion *
i915_gem_ttm_system_setup(stwuct dwm_i915_pwivate *i915,
			  u16 type, u16 instance);
stwuct intew_memowy_wegion *
i915_gem_shmem_setup(stwuct dwm_i915_pwivate *i915,
		     u16 type, u16 instance);

#endif
