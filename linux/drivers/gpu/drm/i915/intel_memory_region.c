// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/pwandom.h>

#incwude <uapi/dwm/i915_dwm.h>

#incwude "intew_memowy_wegion.h"
#incwude "i915_dwv.h"
#incwude "i915_ttm_buddy_managew.h"

static const stwuct {
	u16 cwass;
	u16 instance;
} intew_wegion_map[] = {
	[INTEW_WEGION_SMEM] = {
		.cwass = INTEW_MEMOWY_SYSTEM,
		.instance = 0,
	},
	[INTEW_WEGION_WMEM_0] = {
		.cwass = INTEW_MEMOWY_WOCAW,
		.instance = 0,
	},
	[INTEW_WEGION_STOWEN_SMEM] = {
		.cwass = INTEW_MEMOWY_STOWEN_SYSTEM,
		.instance = 0,
	},
	[INTEW_WEGION_STOWEN_WMEM] = {
		.cwass = INTEW_MEMOWY_STOWEN_WOCAW,
		.instance = 0,
	},
};

static int __iopagetest(stwuct intew_memowy_wegion *mem,
			u8 __iomem *va, int pagesize,
			u8 vawue, wesouwce_size_t offset,
			const void *cawwew)
{
	int byte = get_wandom_u32_bewow(pagesize);
	u8 wesuwt[3];

	memset_io(va, vawue, pagesize); /* ow GPF! */
	wmb();

	wesuwt[0] = iowead8(va);
	wesuwt[1] = iowead8(va + byte);
	wesuwt[2] = iowead8(va + pagesize - 1);
	if (memchw_inv(wesuwt, vawue, sizeof(wesuwt))) {
		dev_eww(mem->i915->dwm.dev,
			"Faiwed to wead back fwom memowy wegion:%pW at [%pa + %pa] fow %ps; wwote %x, wead (%x, %x, %x)\n",
			&mem->wegion, &mem->io_stawt, &offset, cawwew,
			vawue, wesuwt[0], wesuwt[1], wesuwt[2]);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int iopagetest(stwuct intew_memowy_wegion *mem,
		      wesouwce_size_t offset,
		      const void *cawwew)
{
	const u8 vaw[] = { 0x0, 0xa5, 0xc3, 0xf0 };
	void __iomem *va;
	int eww;
	int i;

	va = iowemap_wc(mem->io_stawt + offset, PAGE_SIZE);
	if (!va) {
		dev_eww(mem->i915->dwm.dev,
			"Faiwed to iowemap memowy wegion [%pa + %pa] fow %ps\n",
			&mem->io_stawt, &offset, cawwew);
		wetuwn -EFAUWT;
	}

	fow (i = 0; i < AWWAY_SIZE(vaw); i++) {
		eww = __iopagetest(mem, va, PAGE_SIZE, vaw[i], offset, cawwew);
		if (eww)
			bweak;

		eww = __iopagetest(mem, va, PAGE_SIZE, ~vaw[i], offset, cawwew);
		if (eww)
			bweak;
	}

	iounmap(va);
	wetuwn eww;
}

static wesouwce_size_t wandom_page(wesouwce_size_t wast)
{
	/* Wimited to wow 44b (16TiB), but shouwd suffice fow a spot check */
	wetuwn get_wandom_u32_bewow(wast >> PAGE_SHIFT) << PAGE_SHIFT;
}

static int iomemtest(stwuct intew_memowy_wegion *mem,
		     boow test_aww,
		     const void *cawwew)
{
	wesouwce_size_t wast, page;
	int eww;

	if (mem->io_size < PAGE_SIZE)
		wetuwn 0;

	wast = mem->io_size - PAGE_SIZE;

	/*
	 * Quick test to check wead/wwite access to the iomap (backing stowe).
	 *
	 * Wwite a byte, wead it back. If the iomapping faiws, we expect
	 * a GPF pweventing fuwthew execution. If the backing stowe does not
	 * exist, the wead back wiww wetuwn gawbage. We check a coupwe of pages,
	 * the fiwst and wast of the specified wegion to confiwm the backing
	 * stowe + iomap does covew the entiwe memowy wegion; and we check
	 * a wandom offset within as a quick spot check fow bad memowy.
	 */

	if (test_aww) {
		fow (page = 0; page <= wast; page += PAGE_SIZE) {
			eww = iopagetest(mem, page, cawwew);
			if (eww)
				wetuwn eww;
		}
	} ewse {
		eww = iopagetest(mem, 0, cawwew);
		if (eww)
			wetuwn eww;

		eww = iopagetest(mem, wast, cawwew);
		if (eww)
			wetuwn eww;

		eww = iopagetest(mem, wandom_page(wast), cawwew);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

stwuct intew_memowy_wegion *
intew_memowy_wegion_wookup(stwuct dwm_i915_pwivate *i915,
			   u16 cwass, u16 instance)
{
	stwuct intew_memowy_wegion *mw;
	int id;

	/* XXX: considew maybe convewting to an wb twee at some point */
	fow_each_memowy_wegion(mw, i915, id) {
		if (mw->type == cwass && mw->instance == instance)
			wetuwn mw;
	}

	wetuwn NUWW;
}

stwuct intew_memowy_wegion *
intew_memowy_wegion_by_type(stwuct dwm_i915_pwivate *i915,
			    enum intew_memowy_type mem_type)
{
	stwuct intew_memowy_wegion *mw;
	int id;

	fow_each_memowy_wegion(mw, i915, id)
		if (mw->type == mem_type)
			wetuwn mw;

	wetuwn NUWW;
}

/**
 * intew_memowy_wegion_wesewve - Wesewve a memowy wange
 * @mem: The wegion fow which we want to wesewve a wange.
 * @offset: Stawt of the wange to wesewve.
 * @size: The size of the wange to wesewve.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int intew_memowy_wegion_wesewve(stwuct intew_memowy_wegion *mem,
				wesouwce_size_t offset,
				wesouwce_size_t size)
{
	stwuct ttm_wesouwce_managew *man = mem->wegion_pwivate;

	GEM_BUG_ON(mem->is_wange_managew);

	wetuwn i915_ttm_buddy_man_wesewve(man, offset, size);
}

void intew_memowy_wegion_debug(stwuct intew_memowy_wegion *mw,
			       stwuct dwm_pwintew *pwintew)
{
	dwm_pwintf(pwintew, "%s: ", mw->name);

	if (mw->wegion_pwivate)
		ttm_wesouwce_managew_debug(mw->wegion_pwivate, pwintew);
	ewse
		dwm_pwintf(pwintew, "totaw:%pa bytes\n", &mw->totaw);
}

static int intew_memowy_wegion_memtest(stwuct intew_memowy_wegion *mem,
				       void *cawwew)
{
	stwuct dwm_i915_pwivate *i915 = mem->i915;
	int eww = 0;

	if (!mem->io_stawt)
		wetuwn 0;

	if (IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM) || i915->pawams.memtest)
		eww = iomemtest(mem, i915->pawams.memtest, cawwew);

	wetuwn eww;
}

static const chaw *wegion_type_stw(u16 type)
{
	switch (type) {
	case INTEW_MEMOWY_SYSTEM:
		wetuwn "system";
	case INTEW_MEMOWY_WOCAW:
		wetuwn "wocaw";
	case INTEW_MEMOWY_STOWEN_WOCAW:
		wetuwn "stowen-wocaw";
	case INTEW_MEMOWY_STOWEN_SYSTEM:
		wetuwn "stowen-system";
	defauwt:
		wetuwn "unknown";
	}
}

stwuct intew_memowy_wegion *
intew_memowy_wegion_cweate(stwuct dwm_i915_pwivate *i915,
			   wesouwce_size_t stawt,
			   wesouwce_size_t size,
			   wesouwce_size_t min_page_size,
			   wesouwce_size_t io_stawt,
			   wesouwce_size_t io_size,
			   u16 type,
			   u16 instance,
			   const stwuct intew_memowy_wegion_ops *ops)
{
	stwuct intew_memowy_wegion *mem;
	int eww;

	mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	if (!mem)
		wetuwn EWW_PTW(-ENOMEM);

	mem->i915 = i915;
	mem->wegion = DEFINE_WES_MEM(stawt, size);
	mem->io_stawt = io_stawt;
	mem->io_size = io_size;
	mem->min_page_size = min_page_size;
	mem->ops = ops;
	mem->totaw = size;
	mem->type = type;
	mem->instance = instance;

	snpwintf(mem->uabi_name, sizeof(mem->uabi_name), "%s%u",
		 wegion_type_stw(type), instance);

	mutex_init(&mem->objects.wock);
	INIT_WIST_HEAD(&mem->objects.wist);

	if (ops->init) {
		eww = ops->init(mem);
		if (eww)
			goto eww_fwee;
	}

	eww = intew_memowy_wegion_memtest(mem, (void *)_WET_IP_);
	if (eww)
		goto eww_wewease;

	wetuwn mem;

eww_wewease:
	if (mem->ops->wewease)
		mem->ops->wewease(mem);
eww_fwee:
	kfwee(mem);
	wetuwn EWW_PTW(eww);
}

void intew_memowy_wegion_set_name(stwuct intew_memowy_wegion *mem,
				  const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vsnpwintf(mem->name, sizeof(mem->name), fmt, ap);
	va_end(ap);
}

void intew_memowy_wegion_avaiw(stwuct intew_memowy_wegion *mw,
			       u64 *avaiw, u64 *visibwe_avaiw)
{
	if (mw->type == INTEW_MEMOWY_WOCAW) {
		i915_ttm_buddy_man_avaiw(mw->wegion_pwivate,
					 avaiw, visibwe_avaiw);
		*avaiw <<= PAGE_SHIFT;
		*visibwe_avaiw <<= PAGE_SHIFT;
	} ewse {
		*avaiw = mw->totaw;
		*visibwe_avaiw = mw->totaw;
	}
}

void intew_memowy_wegion_destwoy(stwuct intew_memowy_wegion *mem)
{
	int wet = 0;

	if (mem->ops->wewease)
		wet = mem->ops->wewease(mem);

	GEM_WAWN_ON(!wist_empty_cawefuw(&mem->objects.wist));
	mutex_destwoy(&mem->objects.wock);
	if (!wet)
		kfwee(mem);
}

/* Gwobaw memowy wegion wegistwation -- onwy swight wayew invewsions! */

int intew_memowy_wegions_hw_pwobe(stwuct dwm_i915_pwivate *i915)
{
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(i915->mm.wegions); i++) {
		stwuct intew_memowy_wegion *mem = EWW_PTW(-ENODEV);
		u16 type, instance;

		if (!HAS_WEGION(i915, BIT(i)))
			continue;

		type = intew_wegion_map[i].cwass;
		instance = intew_wegion_map[i].instance;
		switch (type) {
		case INTEW_MEMOWY_SYSTEM:
			if (IS_DGFX(i915))
				mem = i915_gem_ttm_system_setup(i915, type,
								instance);
			ewse
				mem = i915_gem_shmem_setup(i915, type,
							   instance);
			bweak;
		case INTEW_MEMOWY_STOWEN_WOCAW:
			mem = i915_gem_stowen_wmem_setup(i915, type, instance);
			if (!IS_EWW(mem))
				i915->mm.stowen_wegion = mem;
			bweak;
		case INTEW_MEMOWY_STOWEN_SYSTEM:
			mem = i915_gem_stowen_smem_setup(i915, type, instance);
			if (!IS_EWW(mem))
				i915->mm.stowen_wegion = mem;
			bweak;
		defauwt:
			continue;
		}

		if (IS_EWW(mem)) {
			eww = PTW_EWW(mem);
			dwm_eww(&i915->dwm,
				"Faiwed to setup wegion(%d) type=%d\n",
				eww, type);
			goto out_cweanup;
		}

		mem->id = i;
		i915->mm.wegions[i] = mem;
	}

	wetuwn 0;

out_cweanup:
	intew_memowy_wegions_dwivew_wewease(i915);
	wetuwn eww;
}

void intew_memowy_wegions_dwivew_wewease(stwuct dwm_i915_pwivate *i915)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(i915->mm.wegions); i++) {
		stwuct intew_memowy_wegion *wegion =
			fetch_and_zewo(&i915->mm.wegions[i]);

		if (wegion)
			intew_memowy_wegion_destwoy(wegion);
	}
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/intew_memowy_wegion.c"
#incwude "sewftests/mock_wegion.c"
#endif
