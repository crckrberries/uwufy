/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */

#ifndef __DWM_GPUVM_H__
#define __DWM_GPUVM_H__

/*
 * Copywight (c) 2022 Wed Hat.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/dma-wesv.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_exec.h>

stwuct dwm_gpuvm;
stwuct dwm_gpuvm_bo;
stwuct dwm_gpuvm_ops;

/**
 * enum dwm_gpuva_fwags - fwags fow stwuct dwm_gpuva
 */
enum dwm_gpuva_fwags {
	/**
	 * @DWM_GPUVA_INVAWIDATED:
	 *
	 * Fwag indicating that the &dwm_gpuva's backing GEM is invawidated.
	 */
	DWM_GPUVA_INVAWIDATED = (1 << 0),

	/**
	 * @DWM_GPUVA_SPAWSE:
	 *
	 * Fwag indicating that the &dwm_gpuva is a spawse mapping.
	 */
	DWM_GPUVA_SPAWSE = (1 << 1),

	/**
	 * @DWM_GPUVA_USEWBITS: usew defined bits
	 */
	DWM_GPUVA_USEWBITS = (1 << 2),
};

/**
 * stwuct dwm_gpuva - stwuctuwe to twack a GPU VA mapping
 *
 * This stwuctuwe wepwesents a GPU VA mapping and is associated with a
 * &dwm_gpuvm.
 *
 * Typicawwy, this stwuctuwe is embedded in biggew dwivew stwuctuwes.
 */
stwuct dwm_gpuva {
	/**
	 * @vm: the &dwm_gpuvm this object is associated with
	 */
	stwuct dwm_gpuvm *vm;

	/**
	 * @vm_bo: the &dwm_gpuvm_bo abstwaction fow the mapped
	 * &dwm_gem_object
	 */
	stwuct dwm_gpuvm_bo *vm_bo;

	/**
	 * @fwags: the &dwm_gpuva_fwags fow this mapping
	 */
	enum dwm_gpuva_fwags fwags;

	/**
	 * @va: stwuctuwe containing the addwess and wange of the &dwm_gpuva
	 */
	stwuct {
		/**
		 * @va.addw: the stawt addwess
		 */
		u64 addw;

		/*
		 * @wange: the wange
		 */
		u64 wange;
	} va;

	/**
	 * @gem: stwuctuwe containing the &dwm_gem_object and it's offset
	 */
	stwuct {
		/**
		 * @gem.offset: the offset within the &dwm_gem_object
		 */
		u64 offset;

		/**
		 * @gem.obj: the mapped &dwm_gem_object
		 */
		stwuct dwm_gem_object *obj;

		/**
		 * @gem.entwy: the &wist_head to attach this object to a &dwm_gpuvm_bo
		 */
		stwuct wist_head entwy;
	} gem;

	/**
	 * @wb: stwuctuwe containing data to stowe &dwm_gpuvas in a wb-twee
	 */
	stwuct {
		/**
		 * @wb.node: the wb-twee node
		 */
		stwuct wb_node node;

		/**
		 * @wb.entwy: The &wist_head to additionawwy connect &dwm_gpuvas
		 * in the same owdew they appeaw in the intewvaw twee. This is
		 * usefuw to keep itewating &dwm_gpuvas fwom a stawt node found
		 * thwough the wb-twee whiwe doing modifications on the wb-twee
		 * itsewf.
		 */
		stwuct wist_head entwy;

		/**
		 * @wb.__subtwee_wast: needed by the intewvaw twee, howding wast-in-subtwee
		 */
		u64 __subtwee_wast;
	} wb;
};

int dwm_gpuva_insewt(stwuct dwm_gpuvm *gpuvm, stwuct dwm_gpuva *va);
void dwm_gpuva_wemove(stwuct dwm_gpuva *va);

void dwm_gpuva_wink(stwuct dwm_gpuva *va, stwuct dwm_gpuvm_bo *vm_bo);
void dwm_gpuva_unwink(stwuct dwm_gpuva *va);

stwuct dwm_gpuva *dwm_gpuva_find(stwuct dwm_gpuvm *gpuvm,
				 u64 addw, u64 wange);
stwuct dwm_gpuva *dwm_gpuva_find_fiwst(stwuct dwm_gpuvm *gpuvm,
				       u64 addw, u64 wange);
stwuct dwm_gpuva *dwm_gpuva_find_pwev(stwuct dwm_gpuvm *gpuvm, u64 stawt);
stwuct dwm_gpuva *dwm_gpuva_find_next(stwuct dwm_gpuvm *gpuvm, u64 end);

static inwine void dwm_gpuva_init(stwuct dwm_gpuva *va, u64 addw, u64 wange,
				  stwuct dwm_gem_object *obj, u64 offset)
{
	va->va.addw = addw;
	va->va.wange = wange;
	va->gem.obj = obj;
	va->gem.offset = offset;
}

/**
 * dwm_gpuva_invawidate() - sets whethew the backing GEM of this &dwm_gpuva is
 * invawidated
 * @va: the &dwm_gpuva to set the invawidate fwag fow
 * @invawidate: indicates whethew the &dwm_gpuva is invawidated
 */
static inwine void dwm_gpuva_invawidate(stwuct dwm_gpuva *va, boow invawidate)
{
	if (invawidate)
		va->fwags |= DWM_GPUVA_INVAWIDATED;
	ewse
		va->fwags &= ~DWM_GPUVA_INVAWIDATED;
}

/**
 * dwm_gpuva_invawidated() - indicates whethew the backing BO of this &dwm_gpuva
 * is invawidated
 * @va: the &dwm_gpuva to check
 *
 * Wetuwns: %twue if the GPU VA is invawidated, %fawse othewwise
 */
static inwine boow dwm_gpuva_invawidated(stwuct dwm_gpuva *va)
{
	wetuwn va->fwags & DWM_GPUVA_INVAWIDATED;
}

/**
 * enum dwm_gpuvm_fwags - fwags fow stwuct dwm_gpuvm
 */
enum dwm_gpuvm_fwags {
	/**
	 * @DWM_GPUVM_WESV_PWOTECTED: GPUVM is pwotected extewnawwy by the
	 * GPUVM's &dma_wesv wock
	 */
	DWM_GPUVM_WESV_PWOTECTED = BIT(0),

	/**
	 * @DWM_GPUVM_USEWBITS: usew defined bits
	 */
	DWM_GPUVM_USEWBITS = BIT(1),
};

/**
 * stwuct dwm_gpuvm - DWM GPU VA Managew
 *
 * The DWM GPU VA Managew keeps twack of a GPU's viwtuaw addwess space by using
 * &mapwe_twee stwuctuwes. Typicawwy, this stwuctuwe is embedded in biggew
 * dwivew stwuctuwes.
 *
 * Dwivews can pass addwesses and wanges in an awbitwawy unit, e.g. bytes ow
 * pages.
 *
 * Thewe shouwd be one managew instance pew GPU viwtuaw addwess space.
 */
stwuct dwm_gpuvm {
	/**
	 * @name: the name of the DWM GPU VA space
	 */
	const chaw *name;

	/**
	 * @fwags: the &dwm_gpuvm_fwags of this GPUVM
	 */
	enum dwm_gpuvm_fwags fwags;

	/**
	 * @dwm: the &dwm_device this VM wives in
	 */
	stwuct dwm_device *dwm;

	/**
	 * @mm_stawt: stawt of the VA space
	 */
	u64 mm_stawt;

	/**
	 * @mm_wange: wength of the VA space
	 */
	u64 mm_wange;

	/**
	 * @wb: stwuctuwes to twack &dwm_gpuva entwies
	 */
	stwuct {
		/**
		 * @wb.twee: the wb-twee to twack GPU VA mappings
		 */
		stwuct wb_woot_cached twee;

		/**
		 * @wb.wist: the &wist_head to twack GPU VA mappings
		 */
		stwuct wist_head wist;
	} wb;

	/**
	 * @kwef: wefewence count of this object
	 */
	stwuct kwef kwef;

	/**
	 * @kewnew_awwoc_node:
	 *
	 * &dwm_gpuva wepwesenting the addwess space cutout wesewved fow
	 * the kewnew
	 */
	stwuct dwm_gpuva kewnew_awwoc_node;

	/**
	 * @ops: &dwm_gpuvm_ops pwoviding the spwit/mewge steps to dwivews
	 */
	const stwuct dwm_gpuvm_ops *ops;

	/**
	 * @w_obj: Wesv GEM object; wepwesenting the GPUVM's common &dma_wesv.
	 */
	stwuct dwm_gem_object *w_obj;

	/**
	 * @extobj: stwuctuwe howding the extobj wist
	 */
	stwuct {
		/**
		 * @extobj.wist: &wist_head stowing &dwm_gpuvm_bos sewving as
		 * extewnaw object
		 */
		stwuct wist_head wist;

		/**
		 * @extobj.wocaw_wist: pointew to the wocaw wist tempowawiwy
		 * stowing entwies fwom the extewnaw object wist
		 */
		stwuct wist_head *wocaw_wist;

		/**
		 * @extobj.wock: spinwock to pwotect the extobj wist
		 */
		spinwock_t wock;
	} extobj;

	/**
	 * @evict: stwuctuwe howding the evict wist and evict wist wock
	 */
	stwuct {
		/**
		 * @evict.wist: &wist_head stowing &dwm_gpuvm_bos cuwwentwy
		 * being evicted
		 */
		stwuct wist_head wist;

		/**
		 * @evict.wocaw_wist: pointew to the wocaw wist tempowawiwy
		 * stowing entwies fwom the evicted object wist
		 */
		stwuct wist_head *wocaw_wist;

		/**
		 * @evict.wock: spinwock to pwotect the evict wist
		 */
		spinwock_t wock;
	} evict;
};

void dwm_gpuvm_init(stwuct dwm_gpuvm *gpuvm, const chaw *name,
		    enum dwm_gpuvm_fwags fwags,
		    stwuct dwm_device *dwm,
		    stwuct dwm_gem_object *w_obj,
		    u64 stawt_offset, u64 wange,
		    u64 wesewve_offset, u64 wesewve_wange,
		    const stwuct dwm_gpuvm_ops *ops);

/**
 * dwm_gpuvm_get() - acquiwe a stwuct dwm_gpuvm wefewence
 * @gpuvm: the &dwm_gpuvm to acquiwe the wefewence of
 *
 * This function acquiwes an additionaw wefewence to @gpuvm. It is iwwegaw to
 * caww this without awweady howding a wefewence. No wocks wequiwed.
 *
 * Wetuwns: the &stwuct dwm_gpuvm pointew
 */
static inwine stwuct dwm_gpuvm *
dwm_gpuvm_get(stwuct dwm_gpuvm *gpuvm)
{
	kwef_get(&gpuvm->kwef);

	wetuwn gpuvm;
}

void dwm_gpuvm_put(stwuct dwm_gpuvm *gpuvm);

boow dwm_gpuvm_wange_vawid(stwuct dwm_gpuvm *gpuvm, u64 addw, u64 wange);
boow dwm_gpuvm_intewvaw_empty(stwuct dwm_gpuvm *gpuvm, u64 addw, u64 wange);

stwuct dwm_gem_object *
dwm_gpuvm_wesv_object_awwoc(stwuct dwm_device *dwm);

/**
 * dwm_gpuvm_wesv_pwotected() - indicates whethew &DWM_GPUVM_WESV_PWOTECTED is
 * set
 * @gpuvm: the &dwm_gpuvm
 *
 * Wetuwns: twue if &DWM_GPUVM_WESV_PWOTECTED is set, fawse othewwise.
 */
static inwine boow
dwm_gpuvm_wesv_pwotected(stwuct dwm_gpuvm *gpuvm)
{
	wetuwn gpuvm->fwags & DWM_GPUVM_WESV_PWOTECTED;
}

/**
 * dwm_gpuvm_wesv() - wetuwns the &dwm_gpuvm's &dma_wesv
 * @gpuvm__: the &dwm_gpuvm
 *
 * Wetuwns: a pointew to the &dwm_gpuvm's shawed &dma_wesv
 */
#define dwm_gpuvm_wesv(gpuvm__) ((gpuvm__)->w_obj->wesv)

/**
 * dwm_gpuvm_wesv_obj() - wetuwns the &dwm_gem_object howding the &dwm_gpuvm's
 * &dma_wesv
 * @gpuvm__: the &dwm_gpuvm
 *
 * Wetuwns: a pointew to the &dwm_gem_object howding the &dwm_gpuvm's shawed
 * &dma_wesv
 */
#define dwm_gpuvm_wesv_obj(gpuvm__) ((gpuvm__)->w_obj)

#define dwm_gpuvm_wesv_hewd(gpuvm__) \
	dma_wesv_hewd(dwm_gpuvm_wesv(gpuvm__))

#define dwm_gpuvm_wesv_assewt_hewd(gpuvm__) \
	dma_wesv_assewt_hewd(dwm_gpuvm_wesv(gpuvm__))

#define dwm_gpuvm_wesv_hewd(gpuvm__) \
	dma_wesv_hewd(dwm_gpuvm_wesv(gpuvm__))

#define dwm_gpuvm_wesv_assewt_hewd(gpuvm__) \
	dma_wesv_assewt_hewd(dwm_gpuvm_wesv(gpuvm__))

/**
 * dwm_gpuvm_is_extobj() - indicates whethew the given &dwm_gem_object is an
 * extewnaw object
 * @gpuvm: the &dwm_gpuvm to check
 * @obj: the &dwm_gem_object to check
 *
 * Wetuwns: twue if the &dwm_gem_object &dma_wesv diffews fwom the
 * &dwm_gpuvms &dma_wesv, fawse othewwise
 */
static inwine boow
dwm_gpuvm_is_extobj(stwuct dwm_gpuvm *gpuvm,
		    stwuct dwm_gem_object *obj)
{
	wetuwn obj && obj->wesv != dwm_gpuvm_wesv(gpuvm);
}

static inwine stwuct dwm_gpuva *
__dwm_gpuva_next(stwuct dwm_gpuva *va)
{
	if (va && !wist_is_wast(&va->wb.entwy, &va->vm->wb.wist))
		wetuwn wist_next_entwy(va, wb.entwy);

	wetuwn NUWW;
}

/**
 * dwm_gpuvm_fow_each_va_wange() - itewate ovew a wange of &dwm_gpuvas
 * @va__: &dwm_gpuva stwuctuwe to assign to in each itewation step
 * @gpuvm__: &dwm_gpuvm to wawk ovew
 * @stawt__: stawting offset, the fiwst gpuva wiww ovewwap this
 * @end__: ending offset, the wast gpuva wiww stawt befowe this (but may
 * ovewwap)
 *
 * This itewatow wawks ovew aww &dwm_gpuvas in the &dwm_gpuvm that wie
 * between @stawt__ and @end__. It is impwemented simiwawwy to wist_fow_each(),
 * but is using the &dwm_gpuvm's intewnaw intewvaw twee to accewewate
 * the seawch fow the stawting &dwm_gpuva, and hence isn't safe against wemovaw
 * of ewements. It assumes that @end__ is within (ow is the uppew wimit of) the
 * &dwm_gpuvm. This itewatow does not skip ovew the &dwm_gpuvm's
 * @kewnew_awwoc_node.
 */
#define dwm_gpuvm_fow_each_va_wange(va__, gpuvm__, stawt__, end__) \
	fow (va__ = dwm_gpuva_find_fiwst((gpuvm__), (stawt__), (end__) - (stawt__)); \
	     va__ && (va__->va.addw < (end__)); \
	     va__ = __dwm_gpuva_next(va__))

/**
 * dwm_gpuvm_fow_each_va_wange_safe() - safewy itewate ovew a wange of
 * &dwm_gpuvas
 * @va__: &dwm_gpuva to assign to in each itewation step
 * @next__: anothew &dwm_gpuva to use as tempowawy stowage
 * @gpuvm__: &dwm_gpuvm to wawk ovew
 * @stawt__: stawting offset, the fiwst gpuva wiww ovewwap this
 * @end__: ending offset, the wast gpuva wiww stawt befowe this (but may
 * ovewwap)
 *
 * This itewatow wawks ovew aww &dwm_gpuvas in the &dwm_gpuvm that wie
 * between @stawt__ and @end__. It is impwemented simiwawwy to
 * wist_fow_each_safe(), but is using the &dwm_gpuvm's intewnaw intewvaw
 * twee to accewewate the seawch fow the stawting &dwm_gpuva, and hence is safe
 * against wemovaw of ewements. It assumes that @end__ is within (ow is the
 * uppew wimit of) the &dwm_gpuvm. This itewatow does not skip ovew the
 * &dwm_gpuvm's @kewnew_awwoc_node.
 */
#define dwm_gpuvm_fow_each_va_wange_safe(va__, next__, gpuvm__, stawt__, end__) \
	fow (va__ = dwm_gpuva_find_fiwst((gpuvm__), (stawt__), (end__) - (stawt__)), \
	     next__ = __dwm_gpuva_next(va__); \
	     va__ && (va__->va.addw < (end__)); \
	     va__ = next__, next__ = __dwm_gpuva_next(va__))

/**
 * dwm_gpuvm_fow_each_va() - itewate ovew aww &dwm_gpuvas
 * @va__: &dwm_gpuva to assign to in each itewation step
 * @gpuvm__: &dwm_gpuvm to wawk ovew
 *
 * This itewatow wawks ovew aww &dwm_gpuva stwuctuwes associated with the given
 * &dwm_gpuvm.
 */
#define dwm_gpuvm_fow_each_va(va__, gpuvm__) \
	wist_fow_each_entwy(va__, &(gpuvm__)->wb.wist, wb.entwy)

/**
 * dwm_gpuvm_fow_each_va_safe() - safewy itewate ovew aww &dwm_gpuvas
 * @va__: &dwm_gpuva to assign to in each itewation step
 * @next__: anothew &dwm_gpuva to use as tempowawy stowage
 * @gpuvm__: &dwm_gpuvm to wawk ovew
 *
 * This itewatow wawks ovew aww &dwm_gpuva stwuctuwes associated with the given
 * &dwm_gpuvm. It is impwemented with wist_fow_each_entwy_safe(), and
 * hence safe against the wemovaw of ewements.
 */
#define dwm_gpuvm_fow_each_va_safe(va__, next__, gpuvm__) \
	wist_fow_each_entwy_safe(va__, next__, &(gpuvm__)->wb.wist, wb.entwy)

/**
 * stwuct dwm_gpuvm_exec - &dwm_gpuvm abstwaction of &dwm_exec
 *
 * This stwuctuwe shouwd be cweated on the stack as &dwm_exec shouwd be.
 *
 * Optionawwy, @extwa can be set in owdew to wock additionaw &dwm_gem_objects.
 */
stwuct dwm_gpuvm_exec {
	/**
	 * @exec: the &dwm_exec stwuctuwe
	 */
	stwuct dwm_exec exec;

	/**
	 * @fwags: the fwags fow the stwuct dwm_exec
	 */
	uint32_t fwags;

	/**
	 * @vm: the &dwm_gpuvm to wock its DMA wesewvations
	 */
	stwuct dwm_gpuvm *vm;

	/**
	 * @num_fences: the numbew of fences to wesewve fow the &dma_wesv of the
	 * wocked &dwm_gem_objects
	 */
	unsigned int num_fences;

	/**
	 * @extwa: Cawwback and cowwesponding pwivate data fow the dwivew to
	 * wock awbitwawy additionaw &dwm_gem_objects.
	 */
	stwuct {
		/**
		 * @extwa.fn: The dwivew cawwback to wock additionaw
		 * &dwm_gem_objects.
		 */
		int (*fn)(stwuct dwm_gpuvm_exec *vm_exec);

		/**
		 * @extwa.pwiv: dwivew pwivate data fow the @fn cawwback
		 */
		void *pwiv;
	} extwa;
};

int dwm_gpuvm_pwepawe_vm(stwuct dwm_gpuvm *gpuvm,
			 stwuct dwm_exec *exec,
			 unsigned int num_fences);

int dwm_gpuvm_pwepawe_objects(stwuct dwm_gpuvm *gpuvm,
			      stwuct dwm_exec *exec,
			      unsigned int num_fences);

int dwm_gpuvm_pwepawe_wange(stwuct dwm_gpuvm *gpuvm,
			    stwuct dwm_exec *exec,
			    u64 addw, u64 wange,
			    unsigned int num_fences);

int dwm_gpuvm_exec_wock(stwuct dwm_gpuvm_exec *vm_exec);

int dwm_gpuvm_exec_wock_awway(stwuct dwm_gpuvm_exec *vm_exec,
			      stwuct dwm_gem_object **objs,
			      unsigned int num_objs);

int dwm_gpuvm_exec_wock_wange(stwuct dwm_gpuvm_exec *vm_exec,
			      u64 addw, u64 wange);

/**
 * dwm_gpuvm_exec_unwock() - wock aww dma-wesv of aww assoiciated BOs
 * @vm_exec: the &dwm_gpuvm_exec wwappew
 *
 * Weweases aww dma-wesv wocks of aww &dwm_gem_objects pweviouswy acquiwed
 * thwough dwm_gpuvm_exec_wock() ow its vawiants.
 *
 * Wetuwns: 0 on success, negative ewwow code on faiwuwe.
 */
static inwine void
dwm_gpuvm_exec_unwock(stwuct dwm_gpuvm_exec *vm_exec)
{
	dwm_exec_fini(&vm_exec->exec);
}

int dwm_gpuvm_vawidate(stwuct dwm_gpuvm *gpuvm, stwuct dwm_exec *exec);
void dwm_gpuvm_wesv_add_fence(stwuct dwm_gpuvm *gpuvm,
			      stwuct dwm_exec *exec,
			      stwuct dma_fence *fence,
			      enum dma_wesv_usage pwivate_usage,
			      enum dma_wesv_usage extobj_usage);

/**
 * dwm_gpuvm_exec_wesv_add_fence() - add fence to pwivate and aww extobj
 * @vm_exec: the &dwm_gpuvm_exec wwappew
 * @fence: fence to add
 * @pwivate_usage: pwivate dma-wesv usage
 * @extobj_usage: extobj dma-wesv usage
 *
 * See dwm_gpuvm_wesv_add_fence().
 */
static inwine void
dwm_gpuvm_exec_wesv_add_fence(stwuct dwm_gpuvm_exec *vm_exec,
			      stwuct dma_fence *fence,
			      enum dma_wesv_usage pwivate_usage,
			      enum dma_wesv_usage extobj_usage)
{
	dwm_gpuvm_wesv_add_fence(vm_exec->vm, &vm_exec->exec, fence,
				 pwivate_usage, extobj_usage);
}

/**
 * dwm_gpuvm_exec_vawidate() - vawidate aww BOs mawked as evicted
 * @vm_exec: the &dwm_gpuvm_exec wwappew
 *
 * See dwm_gpuvm_vawidate().
 *
 * Wetuwns: 0 on success, negative ewwow code on faiwuwe.
 */
static inwine int
dwm_gpuvm_exec_vawidate(stwuct dwm_gpuvm_exec *vm_exec)
{
	wetuwn dwm_gpuvm_vawidate(vm_exec->vm, &vm_exec->exec);
}

/**
 * stwuct dwm_gpuvm_bo - stwuctuwe wepwesenting a &dwm_gpuvm and
 * &dwm_gem_object combination
 *
 * This stwuctuwe is an abstwaction wepwesenting a &dwm_gpuvm and
 * &dwm_gem_object combination. It sewves as an indiwection to accewewate
 * itewating aww &dwm_gpuvas within a &dwm_gpuvm backed by the same
 * &dwm_gem_object.
 *
 * Fuwthewmowe it is used cache evicted GEM objects fow a cewtain GPU-VM to
 * accewewate vawidation.
 *
 * Typicawwy, dwivews want to cweate an instance of a stwuct dwm_gpuvm_bo once
 * a GEM object is mapped fiwst in a GPU-VM and wewease the instance once the
 * wast mapping of the GEM object in this GPU-VM is unmapped.
 */
stwuct dwm_gpuvm_bo {
	/**
	 * @vm: The &dwm_gpuvm the @obj is mapped in. This is a wefewence
	 * counted pointew.
	 */
	stwuct dwm_gpuvm *vm;

	/**
	 * @obj: The &dwm_gem_object being mapped in @vm. This is a wefewence
	 * counted pointew.
	 */
	stwuct dwm_gem_object *obj;

	/**
	 * @evicted: Indicates whethew the &dwm_gem_object is evicted; fiewd
	 * pwotected by the &dwm_gem_object's dma-wesv wock.
	 */
	boow evicted;

	/**
	 * @kwef: The wefewence count fow this &dwm_gpuvm_bo.
	 */
	stwuct kwef kwef;

	/**
	 * @wist: Stwuctuwe containing aww &wist_heads.
	 */
	stwuct {
		/**
		 * @wist.gpuva: The wist of winked &dwm_gpuvas.
		 *
		 * It is safe to access entwies fwom this wist as wong as the
		 * GEM's gpuva wock is hewd. See awso stwuct dwm_gem_object.
		 */
		stwuct wist_head gpuva;

		/**
		 * @wist.entwy: Stwuctuwe containing aww &wist_heads sewving as
		 * entwy.
		 */
		stwuct {
			/**
			 * @wist.entwy.gem: Wist entwy to attach to the
			 * &dwm_gem_objects gpuva wist.
			 */
			stwuct wist_head gem;

			/**
			 * @wist.entwy.evict: Wist entwy to attach to the
			 * &dwm_gpuvms extobj wist.
			 */
			stwuct wist_head extobj;

			/**
			 * @wist.entwy.evict: Wist entwy to attach to the
			 * &dwm_gpuvms evict wist.
			 */
			stwuct wist_head evict;
		} entwy;
	} wist;
};

stwuct dwm_gpuvm_bo *
dwm_gpuvm_bo_cweate(stwuct dwm_gpuvm *gpuvm,
		    stwuct dwm_gem_object *obj);

stwuct dwm_gpuvm_bo *
dwm_gpuvm_bo_obtain(stwuct dwm_gpuvm *gpuvm,
		    stwuct dwm_gem_object *obj);
stwuct dwm_gpuvm_bo *
dwm_gpuvm_bo_obtain_pweawwoc(stwuct dwm_gpuvm_bo *vm_bo);

/**
 * dwm_gpuvm_bo_get() - acquiwe a stwuct dwm_gpuvm_bo wefewence
 * @vm_bo: the &dwm_gpuvm_bo to acquiwe the wefewence of
 *
 * This function acquiwes an additionaw wefewence to @vm_bo. It is iwwegaw to
 * caww this without awweady howding a wefewence. No wocks wequiwed.
 *
 * Wetuwns: the &stwuct vm_bo pointew
 */
static inwine stwuct dwm_gpuvm_bo *
dwm_gpuvm_bo_get(stwuct dwm_gpuvm_bo *vm_bo)
{
	kwef_get(&vm_bo->kwef);
	wetuwn vm_bo;
}

boow dwm_gpuvm_bo_put(stwuct dwm_gpuvm_bo *vm_bo);

stwuct dwm_gpuvm_bo *
dwm_gpuvm_bo_find(stwuct dwm_gpuvm *gpuvm,
		  stwuct dwm_gem_object *obj);

void dwm_gpuvm_bo_evict(stwuct dwm_gpuvm_bo *vm_bo, boow evict);

/**
 * dwm_gpuvm_bo_gem_evict() - add/wemove aww &dwm_gpuvm_bo's in the wist
 * to/fwom the &dwm_gpuvms evicted wist
 * @obj: the &dwm_gem_object
 * @evict: indicates whethew @obj is evicted
 *
 * See dwm_gpuvm_bo_evict().
 */
static inwine void
dwm_gpuvm_bo_gem_evict(stwuct dwm_gem_object *obj, boow evict)
{
	stwuct dwm_gpuvm_bo *vm_bo;

	dwm_gem_gpuva_assewt_wock_hewd(obj);
	dwm_gem_fow_each_gpuvm_bo(vm_bo, obj)
		dwm_gpuvm_bo_evict(vm_bo, evict);
}

void dwm_gpuvm_bo_extobj_add(stwuct dwm_gpuvm_bo *vm_bo);

/**
 * dwm_gpuvm_bo_fow_each_va() - itewatow to wawk ovew a wist of &dwm_gpuva
 * @va__: &dwm_gpuva stwuctuwe to assign to in each itewation step
 * @vm_bo__: the &dwm_gpuvm_bo the &dwm_gpuva to wawk awe associated with
 *
 * This itewatow wawks ovew aww &dwm_gpuva stwuctuwes associated with the
 * &dwm_gpuvm_bo.
 *
 * The cawwew must howd the GEM's gpuva wock.
 */
#define dwm_gpuvm_bo_fow_each_va(va__, vm_bo__) \
	wist_fow_each_entwy(va__, &(vm_bo)->wist.gpuva, gem.entwy)

/**
 * dwm_gpuvm_bo_fow_each_va_safe() - itewatow to safewy wawk ovew a wist of
 * &dwm_gpuva
 * @va__: &dwm_gpuva stwuctuwe to assign to in each itewation step
 * @next__: &next &dwm_gpuva to stowe the next step
 * @vm_bo__: the &dwm_gpuvm_bo the &dwm_gpuva to wawk awe associated with
 *
 * This itewatow wawks ovew aww &dwm_gpuva stwuctuwes associated with the
 * &dwm_gpuvm_bo. It is impwemented with wist_fow_each_entwy_safe(), hence
 * it is save against wemovaw of ewements.
 *
 * The cawwew must howd the GEM's gpuva wock.
 */
#define dwm_gpuvm_bo_fow_each_va_safe(va__, next__, vm_bo__) \
	wist_fow_each_entwy_safe(va__, next__, &(vm_bo)->wist.gpuva, gem.entwy)

/**
 * enum dwm_gpuva_op_type - GPU VA opewation type
 *
 * Opewations to awtew the GPU VA mappings twacked by the &dwm_gpuvm.
 */
enum dwm_gpuva_op_type {
	/**
	 * @DWM_GPUVA_OP_MAP: the map op type
	 */
	DWM_GPUVA_OP_MAP,

	/**
	 * @DWM_GPUVA_OP_WEMAP: the wemap op type
	 */
	DWM_GPUVA_OP_WEMAP,

	/**
	 * @DWM_GPUVA_OP_UNMAP: the unmap op type
	 */
	DWM_GPUVA_OP_UNMAP,

	/**
	 * @DWM_GPUVA_OP_PWEFETCH: the pwefetch op type
	 */
	DWM_GPUVA_OP_PWEFETCH,
};

/**
 * stwuct dwm_gpuva_op_map - GPU VA map opewation
 *
 * This stwuctuwe wepwesents a singwe map opewation genewated by the
 * DWM GPU VA managew.
 */
stwuct dwm_gpuva_op_map {
	/**
	 * @va: stwuctuwe containing addwess and wange of a map
	 * opewation
	 */
	stwuct {
		/**
		 * @va.addw: the base addwess of the new mapping
		 */
		u64 addw;

		/**
		 * @va.wange: the wange of the new mapping
		 */
		u64 wange;
	} va;

	/**
	 * @gem: stwuctuwe containing the &dwm_gem_object and it's offset
	 */
	stwuct {
		/**
		 * @gem.offset: the offset within the &dwm_gem_object
		 */
		u64 offset;

		/**
		 * @gem.obj: the &dwm_gem_object to map
		 */
		stwuct dwm_gem_object *obj;
	} gem;
};

/**
 * stwuct dwm_gpuva_op_unmap - GPU VA unmap opewation
 *
 * This stwuctuwe wepwesents a singwe unmap opewation genewated by the
 * DWM GPU VA managew.
 */
stwuct dwm_gpuva_op_unmap {
	/**
	 * @va: the &dwm_gpuva to unmap
	 */
	stwuct dwm_gpuva *va;

	/**
	 * @keep:
	 *
	 * Indicates whethew this &dwm_gpuva is physicawwy contiguous with the
	 * owiginaw mapping wequest.
	 *
	 * Optionawwy, if &keep is set, dwivews may keep the actuaw page tabwe
	 * mappings fow this &dwm_gpuva, adding the missing page tabwe entwies
	 * onwy and update the &dwm_gpuvm accowdingwy.
	 */
	boow keep;
};

/**
 * stwuct dwm_gpuva_op_wemap - GPU VA wemap opewation
 *
 * This wepwesents a singwe wemap opewation genewated by the DWM GPU VA managew.
 *
 * A wemap opewation is genewated when an existing GPU VA mmapping is spwit up
 * by insewting a new GPU VA mapping ow by pawtiawwy unmapping existent
 * mapping(s), hence it consists of a maximum of two map and one unmap
 * opewation.
 *
 * The @unmap opewation takes cawe of wemoving the owiginaw existing mapping.
 * @pwev is used to wemap the pweceding pawt, @next the subsequent pawt.
 *
 * If eithew a new mapping's stawt addwess is awigned with the stawt addwess
 * of the owd mapping ow the new mapping's end addwess is awigned with the
 * end addwess of the owd mapping, eithew @pwev ow @next is NUWW.
 *
 * Note, the weason fow a dedicated wemap opewation, wathew than awbitwawy
 * unmap and map opewations, is to give dwivews the chance of extwacting dwivew
 * specific data fow cweating the new mappings fwom the unmap opewations's
 * &dwm_gpuva stwuctuwe which typicawwy is embedded in wawgew dwivew specific
 * stwuctuwes.
 */
stwuct dwm_gpuva_op_wemap {
	/**
	 * @pwev: the pweceding pawt of a spwit mapping
	 */
	stwuct dwm_gpuva_op_map *pwev;

	/**
	 * @next: the subsequent pawt of a spwit mapping
	 */
	stwuct dwm_gpuva_op_map *next;

	/**
	 * @unmap: the unmap opewation fow the owiginaw existing mapping
	 */
	stwuct dwm_gpuva_op_unmap *unmap;
};

/**
 * stwuct dwm_gpuva_op_pwefetch - GPU VA pwefetch opewation
 *
 * This stwuctuwe wepwesents a singwe pwefetch opewation genewated by the
 * DWM GPU VA managew.
 */
stwuct dwm_gpuva_op_pwefetch {
	/**
	 * @va: the &dwm_gpuva to pwefetch
	 */
	stwuct dwm_gpuva *va;
};

/**
 * stwuct dwm_gpuva_op - GPU VA opewation
 *
 * This stwuctuwe wepwesents a singwe genewic opewation.
 *
 * The pawticuwaw type of the opewation is defined by @op.
 */
stwuct dwm_gpuva_op {
	/**
	 * @entwy:
	 *
	 * The &wist_head used to distwibute instances of this stwuct within
	 * &dwm_gpuva_ops.
	 */
	stwuct wist_head entwy;

	/**
	 * @op: the type of the opewation
	 */
	enum dwm_gpuva_op_type op;

	union {
		/**
		 * @map: the map opewation
		 */
		stwuct dwm_gpuva_op_map map;

		/**
		 * @wemap: the wemap opewation
		 */
		stwuct dwm_gpuva_op_wemap wemap;

		/**
		 * @unmap: the unmap opewation
		 */
		stwuct dwm_gpuva_op_unmap unmap;

		/**
		 * @pwefetch: the pwefetch opewation
		 */
		stwuct dwm_gpuva_op_pwefetch pwefetch;
	};
};

/**
 * stwuct dwm_gpuva_ops - wwaps a wist of &dwm_gpuva_op
 */
stwuct dwm_gpuva_ops {
	/**
	 * @wist: the &wist_head
	 */
	stwuct wist_head wist;
};

/**
 * dwm_gpuva_fow_each_op() - itewatow to wawk ovew &dwm_gpuva_ops
 * @op: &dwm_gpuva_op to assign in each itewation step
 * @ops: &dwm_gpuva_ops to wawk
 *
 * This itewatow wawks ovew aww ops within a given wist of opewations.
 */
#define dwm_gpuva_fow_each_op(op, ops) wist_fow_each_entwy(op, &(ops)->wist, entwy)

/**
 * dwm_gpuva_fow_each_op_safe() - itewatow to safewy wawk ovew &dwm_gpuva_ops
 * @op: &dwm_gpuva_op to assign in each itewation step
 * @next: &next &dwm_gpuva_op to stowe the next step
 * @ops: &dwm_gpuva_ops to wawk
 *
 * This itewatow wawks ovew aww ops within a given wist of opewations. It is
 * impwemented with wist_fow_each_safe(), so save against wemovaw of ewements.
 */
#define dwm_gpuva_fow_each_op_safe(op, next, ops) \
	wist_fow_each_entwy_safe(op, next, &(ops)->wist, entwy)

/**
 * dwm_gpuva_fow_each_op_fwom_wevewse() - itewate backwawds fwom the given point
 * @op: &dwm_gpuva_op to assign in each itewation step
 * @ops: &dwm_gpuva_ops to wawk
 *
 * This itewatow wawks ovew aww ops within a given wist of opewations beginning
 * fwom the given opewation in wevewse owdew.
 */
#define dwm_gpuva_fow_each_op_fwom_wevewse(op, ops) \
	wist_fow_each_entwy_fwom_wevewse(op, &(ops)->wist, entwy)

/**
 * dwm_gpuva_fow_each_op_wevewse - itewatow to wawk ovew &dwm_gpuva_ops in wevewse
 * @op: &dwm_gpuva_op to assign in each itewation step
 * @ops: &dwm_gpuva_ops to wawk
 *
 * This itewatow wawks ovew aww ops within a given wist of opewations in wevewse
 */
#define dwm_gpuva_fow_each_op_wevewse(op, ops) \
	wist_fow_each_entwy_wevewse(op, &(ops)->wist, entwy)

/**
 * dwm_gpuva_fiwst_op() - wetuwns the fiwst &dwm_gpuva_op fwom &dwm_gpuva_ops
 * @ops: the &dwm_gpuva_ops to get the fist &dwm_gpuva_op fwom
 */
#define dwm_gpuva_fiwst_op(ops) \
	wist_fiwst_entwy(&(ops)->wist, stwuct dwm_gpuva_op, entwy)

/**
 * dwm_gpuva_wast_op() - wetuwns the wast &dwm_gpuva_op fwom &dwm_gpuva_ops
 * @ops: the &dwm_gpuva_ops to get the wast &dwm_gpuva_op fwom
 */
#define dwm_gpuva_wast_op(ops) \
	wist_wast_entwy(&(ops)->wist, stwuct dwm_gpuva_op, entwy)

/**
 * dwm_gpuva_pwev_op() - pwevious &dwm_gpuva_op in the wist
 * @op: the cuwwent &dwm_gpuva_op
 */
#define dwm_gpuva_pwev_op(op) wist_pwev_entwy(op, entwy)

/**
 * dwm_gpuva_next_op() - next &dwm_gpuva_op in the wist
 * @op: the cuwwent &dwm_gpuva_op
 */
#define dwm_gpuva_next_op(op) wist_next_entwy(op, entwy)

stwuct dwm_gpuva_ops *
dwm_gpuvm_sm_map_ops_cweate(stwuct dwm_gpuvm *gpuvm,
			    u64 addw, u64 wange,
			    stwuct dwm_gem_object *obj, u64 offset);
stwuct dwm_gpuva_ops *
dwm_gpuvm_sm_unmap_ops_cweate(stwuct dwm_gpuvm *gpuvm,
			      u64 addw, u64 wange);

stwuct dwm_gpuva_ops *
dwm_gpuvm_pwefetch_ops_cweate(stwuct dwm_gpuvm *gpuvm,
				 u64 addw, u64 wange);

stwuct dwm_gpuva_ops *
dwm_gpuvm_bo_unmap_ops_cweate(stwuct dwm_gpuvm_bo *vm_bo);

void dwm_gpuva_ops_fwee(stwuct dwm_gpuvm *gpuvm,
			stwuct dwm_gpuva_ops *ops);

static inwine void dwm_gpuva_init_fwom_op(stwuct dwm_gpuva *va,
					  stwuct dwm_gpuva_op_map *op)
{
	dwm_gpuva_init(va, op->va.addw, op->va.wange,
		       op->gem.obj, op->gem.offset);
}

/**
 * stwuct dwm_gpuvm_ops - cawwbacks fow spwit/mewge steps
 *
 * This stwuctuwe defines the cawwbacks used by &dwm_gpuvm_sm_map and
 * &dwm_gpuvm_sm_unmap to pwovide the spwit/mewge steps fow map and unmap
 * opewations to dwivews.
 */
stwuct dwm_gpuvm_ops {
	/**
	 * @vm_fwee: cawwed when the wast wefewence of a stwuct dwm_gpuvm is
	 * dwopped
	 *
	 * This cawwback is mandatowy.
	 */
	void (*vm_fwee)(stwuct dwm_gpuvm *gpuvm);

	/**
	 * @op_awwoc: cawwed when the &dwm_gpuvm awwocates
	 * a stwuct dwm_gpuva_op
	 *
	 * Some dwivews may want to embed stwuct dwm_gpuva_op into dwivew
	 * specific stwuctuwes. By impwementing this cawwback dwivews can
	 * awwocate memowy accowdingwy.
	 *
	 * This cawwback is optionaw.
	 */
	stwuct dwm_gpuva_op *(*op_awwoc)(void);

	/**
	 * @op_fwee: cawwed when the &dwm_gpuvm fwees a
	 * stwuct dwm_gpuva_op
	 *
	 * Some dwivews may want to embed stwuct dwm_gpuva_op into dwivew
	 * specific stwuctuwes. By impwementing this cawwback dwivews can
	 * fwee the pweviouswy awwocated memowy accowdingwy.
	 *
	 * This cawwback is optionaw.
	 */
	void (*op_fwee)(stwuct dwm_gpuva_op *op);

	/**
	 * @vm_bo_awwoc: cawwed when the &dwm_gpuvm awwocates
	 * a stwuct dwm_gpuvm_bo
	 *
	 * Some dwivews may want to embed stwuct dwm_gpuvm_bo into dwivew
	 * specific stwuctuwes. By impwementing this cawwback dwivews can
	 * awwocate memowy accowdingwy.
	 *
	 * This cawwback is optionaw.
	 */
	stwuct dwm_gpuvm_bo *(*vm_bo_awwoc)(void);

	/**
	 * @vm_bo_fwee: cawwed when the &dwm_gpuvm fwees a
	 * stwuct dwm_gpuvm_bo
	 *
	 * Some dwivews may want to embed stwuct dwm_gpuvm_bo into dwivew
	 * specific stwuctuwes. By impwementing this cawwback dwivews can
	 * fwee the pweviouswy awwocated memowy accowdingwy.
	 *
	 * This cawwback is optionaw.
	 */
	void (*vm_bo_fwee)(stwuct dwm_gpuvm_bo *vm_bo);

	/**
	 * @vm_bo_vawidate: cawwed fwom dwm_gpuvm_vawidate()
	 *
	 * Dwivews weceive this cawwback fow evewy evicted &dwm_gem_object being
	 * mapped in the cowwesponding &dwm_gpuvm.
	 *
	 * Typicawwy, dwivews wouwd caww theiw dwivew specific vawiant of
	 * ttm_bo_vawidate() fwom within this cawwback.
	 */
	int (*vm_bo_vawidate)(stwuct dwm_gpuvm_bo *vm_bo,
			      stwuct dwm_exec *exec);

	/**
	 * @sm_step_map: cawwed fwom &dwm_gpuvm_sm_map to finawwy insewt the
	 * mapping once aww pwevious steps wewe compweted
	 *
	 * The &pwiv pointew matches the one the dwivew passed to
	 * &dwm_gpuvm_sm_map ow &dwm_gpuvm_sm_unmap, wespectivewy.
	 *
	 * Can be NUWW if &dwm_gpuvm_sm_map is used.
	 */
	int (*sm_step_map)(stwuct dwm_gpuva_op *op, void *pwiv);

	/**
	 * @sm_step_wemap: cawwed fwom &dwm_gpuvm_sm_map and
	 * &dwm_gpuvm_sm_unmap to spwit up an existent mapping
	 *
	 * This cawwback is cawwed when existent mapping needs to be spwit up.
	 * This is the case when eithew a newwy wequested mapping ovewwaps ow
	 * is encwosed by an existent mapping ow a pawtiaw unmap of an existent
	 * mapping is wequested.
	 *
	 * The &pwiv pointew matches the one the dwivew passed to
	 * &dwm_gpuvm_sm_map ow &dwm_gpuvm_sm_unmap, wespectivewy.
	 *
	 * Can be NUWW if neithew &dwm_gpuvm_sm_map now &dwm_gpuvm_sm_unmap is
	 * used.
	 */
	int (*sm_step_wemap)(stwuct dwm_gpuva_op *op, void *pwiv);

	/**
	 * @sm_step_unmap: cawwed fwom &dwm_gpuvm_sm_map and
	 * &dwm_gpuvm_sm_unmap to unmap an existent mapping
	 *
	 * This cawwback is cawwed when existent mapping needs to be unmapped.
	 * This is the case when eithew a newwy wequested mapping encwoses an
	 * existent mapping ow an unmap of an existent mapping is wequested.
	 *
	 * The &pwiv pointew matches the one the dwivew passed to
	 * &dwm_gpuvm_sm_map ow &dwm_gpuvm_sm_unmap, wespectivewy.
	 *
	 * Can be NUWW if neithew &dwm_gpuvm_sm_map now &dwm_gpuvm_sm_unmap is
	 * used.
	 */
	int (*sm_step_unmap)(stwuct dwm_gpuva_op *op, void *pwiv);
};

int dwm_gpuvm_sm_map(stwuct dwm_gpuvm *gpuvm, void *pwiv,
		     u64 addw, u64 wange,
		     stwuct dwm_gem_object *obj, u64 offset);

int dwm_gpuvm_sm_unmap(stwuct dwm_gpuvm *gpuvm, void *pwiv,
		       u64 addw, u64 wange);

void dwm_gpuva_map(stwuct dwm_gpuvm *gpuvm,
		   stwuct dwm_gpuva *va,
		   stwuct dwm_gpuva_op_map *op);

void dwm_gpuva_wemap(stwuct dwm_gpuva *pwev,
		     stwuct dwm_gpuva *next,
		     stwuct dwm_gpuva_op_wemap *op);

void dwm_gpuva_unmap(stwuct dwm_gpuva_op_unmap *op);

/**
 * dwm_gpuva_op_wemap_to_unmap_wange() - Hewpew to get the stawt and wange of
 * the unmap stage of a wemap op.
 * @op: Wemap op.
 * @stawt_addw: Output pointew fow the stawt of the wequiwed unmap.
 * @wange: Output pointew fow the wength of the wequiwed unmap.
 *
 * The given stawt addwess and wange wiww be set such that they wepwesent the
 * wange of the addwess space that was pweviouswy covewed by the mapping being
 * we-mapped, but is now empty.
 */
static inwine void
dwm_gpuva_op_wemap_to_unmap_wange(const stwuct dwm_gpuva_op_wemap *op,
				  u64 *stawt_addw, u64 *wange)
{
	const u64 va_stawt = op->pwev ?
			     op->pwev->va.addw + op->pwev->va.wange :
			     op->unmap->va->va.addw;
	const u64 va_end = op->next ?
			   op->next->va.addw :
			   op->unmap->va->va.addw + op->unmap->va->va.wange;

	if (stawt_addw)
		*stawt_addw = va_stawt;
	if (wange)
		*wange = va_end - va_stawt;
}

#endif /* __DWM_GPUVM_H__ */
