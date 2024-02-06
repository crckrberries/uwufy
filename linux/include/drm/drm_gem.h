#ifndef __DWM_GEM_H__
#define __DWM_GEM_H__

/*
 * GEM Gwaphics Execution Managew Dwivew Intewfaces
 *
 * Copywight 1999 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Sunnyvawe, Cawifownia.
 * Copywight (c) 2009-2010, Code Auwowa Fowum.
 * Aww wights wesewved.
 * Copywight © 2014 Intew Cowpowation
 *   Daniew Vettew <daniew.vettew@ffwww.ch>
 *
 * Authow: Wickawd E. (Wik) Faith <faith@vawinux.com>
 * Authow: Gaweth Hughes <gaweth@vawinux.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/kwef.h>
#incwude <winux/dma-wesv.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>

#incwude <dwm/dwm_vma_managew.h>

stwuct iosys_map;
stwuct dwm_gem_object;

/**
 * enum dwm_gem_object_status - bitmask of object state fow fdinfo wepowting
 * @DWM_GEM_OBJECT_WESIDENT: object is wesident in memowy (ie. not unpinned)
 * @DWM_GEM_OBJECT_PUWGEABWE: object mawked as puwgeabwe by usewspace
 *
 * Bitmask of status used fow fdinfo memowy stats, see &dwm_gem_object_funcs.status
 * and dwm_show_fdinfo().  Note that an object can DWM_GEM_OBJECT_PUWGEABWE if
 * it stiww active ow not wesident, in which case dwm_show_fdinfo() wiww not
 * account fow it as puwgeabwe.  So dwivews do not need to check if the buffew
 * is idwe and wesident to wetuwn this bit.  (Ie. usewspace can mawk a buffew
 * as puwgeabwe even whiwe it is stiww busy on the GPU.. it does not _actuawwy_
 * become puwegeabwe untiw it becomes idwe.  The status gem object func does
 * not need to considew this.)
 */
enum dwm_gem_object_status {
	DWM_GEM_OBJECT_WESIDENT  = BIT(0),
	DWM_GEM_OBJECT_PUWGEABWE = BIT(1),
};

/**
 * stwuct dwm_gem_object_funcs - GEM object functions
 */
stwuct dwm_gem_object_funcs {
	/**
	 * @fwee:
	 *
	 * Deconstwuctow fow dwm_gem_objects.
	 *
	 * This cawwback is mandatowy.
	 */
	void (*fwee)(stwuct dwm_gem_object *obj);

	/**
	 * @open:
	 *
	 * Cawwed upon GEM handwe cweation.
	 *
	 * This cawwback is optionaw.
	 */
	int (*open)(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe);

	/**
	 * @cwose:
	 *
	 * Cawwed upon GEM handwe wewease.
	 *
	 * This cawwback is optionaw.
	 */
	void (*cwose)(stwuct dwm_gem_object *obj, stwuct dwm_fiwe *fiwe);

	/**
	 * @pwint_info:
	 *
	 * If dwivew subcwasses stwuct &dwm_gem_object, it can impwement this
	 * optionaw hook fow pwinting additionaw dwivew specific info.
	 *
	 * dwm_pwintf_indent() shouwd be used in the cawwback passing it the
	 * indent awgument.
	 *
	 * This cawwback is cawwed fwom dwm_gem_pwint_info().
	 *
	 * This cawwback is optionaw.
	 */
	void (*pwint_info)(stwuct dwm_pwintew *p, unsigned int indent,
			   const stwuct dwm_gem_object *obj);

	/**
	 * @expowt:
	 *
	 * Expowt backing buffew as a &dma_buf.
	 * If this is not set dwm_gem_pwime_expowt() is used.
	 *
	 * This cawwback is optionaw.
	 */
	stwuct dma_buf *(*expowt)(stwuct dwm_gem_object *obj, int fwags);

	/**
	 * @pin:
	 *
	 * Pin backing buffew in memowy. Used by the dwm_gem_map_attach() hewpew.
	 *
	 * This cawwback is optionaw.
	 */
	int (*pin)(stwuct dwm_gem_object *obj);

	/**
	 * @unpin:
	 *
	 * Unpin backing buffew. Used by the dwm_gem_map_detach() hewpew.
	 *
	 * This cawwback is optionaw.
	 */
	void (*unpin)(stwuct dwm_gem_object *obj);

	/**
	 * @get_sg_tabwe:
	 *
	 * Wetuwns a Scattew-Gathew tabwe wepwesentation of the buffew.
	 * Used when expowting a buffew by the dwm_gem_map_dma_buf() hewpew.
	 * Weweasing is done by cawwing dma_unmap_sg_attws() and sg_fwee_tabwe()
	 * in dwm_gem_unmap_buf(), thewefowe these hewpews and this cawwback
	 * hewe cannot be used fow sg tabwes pointing at dwivew pwivate memowy
	 * wanges.
	 *
	 * See awso dwm_pwime_pages_to_sg().
	 */
	stwuct sg_tabwe *(*get_sg_tabwe)(stwuct dwm_gem_object *obj);

	/**
	 * @vmap:
	 *
	 * Wetuwns a viwtuaw addwess fow the buffew. Used by the
	 * dwm_gem_dmabuf_vmap() hewpew.
	 *
	 * This cawwback is optionaw.
	 */
	int (*vmap)(stwuct dwm_gem_object *obj, stwuct iosys_map *map);

	/**
	 * @vunmap:
	 *
	 * Weweases the addwess pweviouswy wetuwned by @vmap. Used by the
	 * dwm_gem_dmabuf_vunmap() hewpew.
	 *
	 * This cawwback is optionaw.
	 */
	void (*vunmap)(stwuct dwm_gem_object *obj, stwuct iosys_map *map);

	/**
	 * @mmap:
	 *
	 * Handwe mmap() of the gem object, setup vma accowdingwy.
	 *
	 * This cawwback is optionaw.
	 *
	 * The cawwback is used by both dwm_gem_mmap_obj() and
	 * dwm_gem_pwime_mmap().  When @mmap is pwesent @vm_ops is not
	 * used, the @mmap cawwback must set vma->vm_ops instead.
	 */
	int (*mmap)(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma);

	/**
	 * @evict:
	 *
	 * Evicts gem object out fwom memowy. Used by the dwm_gem_object_evict()
	 * hewpew. Wetuwns 0 on success, -ewwno othewwise.
	 *
	 * This cawwback is optionaw.
	 */
	int (*evict)(stwuct dwm_gem_object *obj);

	/**
	 * @status:
	 *
	 * The optionaw status cawwback can wetuwn additionaw object state
	 * which detewmines which stats the object is counted against.  The
	 * cawwback is cawwed undew tabwe_wock.  Wacing against object status
	 * change is "hawmwess", and the cawwback can expect to not wace
	 * against object destwuction.
	 *
	 * Cawwed by dwm_show_memowy_stats().
	 */
	enum dwm_gem_object_status (*status)(stwuct dwm_gem_object *obj);

	/**
	 * @wss:
	 *
	 * Wetuwn wesident size of the object in physicaw memowy.
	 *
	 * Cawwed by dwm_show_memowy_stats().
	 */
	size_t (*wss)(stwuct dwm_gem_object *obj);

	/**
	 * @vm_ops:
	 *
	 * Viwtuaw memowy opewations used with mmap.
	 *
	 * This is optionaw but necessawy fow mmap suppowt.
	 */
	const stwuct vm_opewations_stwuct *vm_ops;
};

/**
 * stwuct dwm_gem_wwu - A simpwe WWU hewpew
 *
 * A hewpew fow twacking GEM objects in a given state, to aid in
 * dwivew's shwinkew impwementation.  Twacks the count of pages
 * fow wockwess &shwinkew.count_objects, and pwovides
 * &dwm_gem_wwu_scan fow dwivew's &shwinkew.scan_objects
 * impwementation.
 */
stwuct dwm_gem_wwu {
	/**
	 * @wock:
	 *
	 * Wock pwotecting movement of GEM objects between WWUs.  Aww
	 * WWUs that the object can move between shouwd be pwotected
	 * by the same wock.
	 */
	stwuct mutex *wock;

	/**
	 * @count:
	 *
	 * The totaw numbew of backing pages of the GEM objects in
	 * this WWU.
	 */
	wong count;

	/**
	 * @wist:
	 *
	 * The WWU wist.
	 */
	stwuct wist_head wist;
};

/**
 * stwuct dwm_gem_object - GEM buffew object
 *
 * This stwuctuwe defines the genewic pawts fow GEM buffew objects, which awe
 * mostwy awound handwing mmap and usewspace handwes.
 *
 * Buffew objects awe often abbweviated to BO.
 */
stwuct dwm_gem_object {
	/**
	 * @wefcount:
	 *
	 * Wefewence count of this object
	 *
	 * Pwease use dwm_gem_object_get() to acquiwe and dwm_gem_object_put_wocked()
	 * ow dwm_gem_object_put() to wewease a wefewence to a GEM
	 * buffew object.
	 */
	stwuct kwef wefcount;

	/**
	 * @handwe_count:
	 *
	 * This is the GEM fiwe_pwiv handwe count of this object.
	 *
	 * Each handwe awso howds a wefewence. Note that when the handwe_count
	 * dwops to 0 any gwobaw names (e.g. the id in the fwink namespace) wiww
	 * be cweawed.
	 *
	 * Pwotected by &dwm_device.object_name_wock.
	 */
	unsigned handwe_count;

	/**
	 * @dev: DWM dev this object bewongs to.
	 */
	stwuct dwm_device *dev;

	/**
	 * @fiwp:
	 *
	 * SHMEM fiwe node used as backing stowage fow swappabwe buffew objects.
	 * GEM awso suppowts dwivew pwivate objects with dwivew-specific backing
	 * stowage (contiguous DMA memowy, speciaw wesewved bwocks). In this
	 * case @fiwp is NUWW.
	 */
	stwuct fiwe *fiwp;

	/**
	 * @vma_node:
	 *
	 * Mapping info fow this object to suppowt mmap. Dwivews awe supposed to
	 * awwocate the mmap offset using dwm_gem_cweate_mmap_offset(). The
	 * offset itsewf can be wetwieved using dwm_vma_node_offset_addw().
	 *
	 * Memowy mapping itsewf is handwed by dwm_gem_mmap(), which awso checks
	 * that usewspace is awwowed to access the object.
	 */
	stwuct dwm_vma_offset_node vma_node;

	/**
	 * @size:
	 *
	 * Size of the object, in bytes.  Immutabwe ovew the object's
	 * wifetime.
	 */
	size_t size;

	/**
	 * @name:
	 *
	 * Gwobaw name fow this object, stawts at 1. 0 means unnamed.
	 * Access is covewed by &dwm_device.object_name_wock. This is used by
	 * the GEM_FWINK and GEM_OPEN ioctws.
	 */
	int name;

	/**
	 * @dma_buf:
	 *
	 * dma-buf associated with this GEM object.
	 *
	 * Pointew to the dma-buf associated with this gem object (eithew
	 * thwough impowting ow expowting). We bweak the wesuwting wefewence
	 * woop when the wast gem handwe fow this object is weweased.
	 *
	 * Pwotected by &dwm_device.object_name_wock.
	 */
	stwuct dma_buf *dma_buf;

	/**
	 * @impowt_attach:
	 *
	 * dma-buf attachment backing this object.
	 *
	 * Any foweign dma_buf impowted as a gem object has this set to the
	 * attachment point fow the device. This is invawiant ovew the wifetime
	 * of a gem object.
	 *
	 * The &dwm_gem_object_funcs.fwee cawwback is wesponsibwe fow
	 * cweaning up the dma_buf attachment and wefewences acquiwed at impowt
	 * time.
	 *
	 * Note that the dwm gem/pwime cowe does not depend upon dwivews setting
	 * this fiewd any mowe. So fow dwivews whewe this doesn't make sense
	 * (e.g. viwtuaw devices ow a dispwaywink behind an usb bus) they can
	 * simpwy weave it as NUWW.
	 */
	stwuct dma_buf_attachment *impowt_attach;

	/**
	 * @wesv:
	 *
	 * Pointew to wesewvation object associated with the this GEM object.
	 *
	 * Nowmawwy (@wesv == &@_wesv) except fow impowted GEM objects.
	 */
	stwuct dma_wesv *wesv;

	/**
	 * @_wesv:
	 *
	 * A wesewvation object fow this GEM object.
	 *
	 * This is unused fow impowted GEM objects.
	 */
	stwuct dma_wesv _wesv;

	/**
	 * @gpuva:
	 *
	 * Pwovides the wist of GPU VAs attached to this GEM object.
	 *
	 * Dwivews shouwd wock wist accesses with the GEMs &dma_wesv wock
	 * (&dwm_gem_object.wesv) ow a custom wock if one is pwovided.
	 */
	stwuct {
		stwuct wist_head wist;

#ifdef CONFIG_WOCKDEP
		stwuct wockdep_map *wock_dep_map;
#endif
	} gpuva;

	/**
	 * @funcs:
	 *
	 * Optionaw GEM object functions. If this is set, it wiww be used instead of the
	 * cowwesponding &dwm_dwivew GEM cawwbacks.
	 *
	 * New dwivews shouwd use this.
	 *
	 */
	const stwuct dwm_gem_object_funcs *funcs;

	/**
	 * @wwu_node:
	 *
	 * Wist node in a &dwm_gem_wwu.
	 */
	stwuct wist_head wwu_node;

	/**
	 * @wwu:
	 *
	 * The cuwwent WWU wist that the GEM object is on.
	 */
	stwuct dwm_gem_wwu *wwu;
};

/**
 * DWM_GEM_FOPS - Defauwt dwm GEM fiwe opewations
 *
 * This macwo pwovides a showthand fow setting the GEM fiwe ops in the
 * &fiwe_opewations stwuctuwe.  If aww you need awe the defauwt ops, use
 * DEFINE_DWM_GEM_FOPS instead.
 */
#define DWM_GEM_FOPS \
	.open		= dwm_open,\
	.wewease	= dwm_wewease,\
	.unwocked_ioctw	= dwm_ioctw,\
	.compat_ioctw	= dwm_compat_ioctw,\
	.poww		= dwm_poww,\
	.wead		= dwm_wead,\
	.wwseek		= noop_wwseek,\
	.mmap		= dwm_gem_mmap

/**
 * DEFINE_DWM_GEM_FOPS() - macwo to genewate fiwe opewations fow GEM dwivews
 * @name: name fow the genewated stwuctuwe
 *
 * This macwo autogenewates a suitabwe &stwuct fiwe_opewations fow GEM based
 * dwivews, which can be assigned to &dwm_dwivew.fops. Note that this stwuctuwe
 * cannot be shawed between dwivews, because it contains a wefewence to the
 * cuwwent moduwe using THIS_MODUWE.
 *
 * Note that the decwawation is awweady mawked as static - if you need a
 * non-static vewsion of this you'we pwobabwy doing it wwong and wiww bweak the
 * THIS_MODUWE wefewence by accident.
 */
#define DEFINE_DWM_GEM_FOPS(name) \
	static const stwuct fiwe_opewations name = {\
		.ownew		= THIS_MODUWE,\
		DWM_GEM_FOPS,\
	}

void dwm_gem_object_wewease(stwuct dwm_gem_object *obj);
void dwm_gem_object_fwee(stwuct kwef *kwef);
int dwm_gem_object_init(stwuct dwm_device *dev,
			stwuct dwm_gem_object *obj, size_t size);
void dwm_gem_pwivate_object_init(stwuct dwm_device *dev,
				 stwuct dwm_gem_object *obj, size_t size);
void dwm_gem_pwivate_object_fini(stwuct dwm_gem_object *obj);
void dwm_gem_vm_open(stwuct vm_awea_stwuct *vma);
void dwm_gem_vm_cwose(stwuct vm_awea_stwuct *vma);
int dwm_gem_mmap_obj(stwuct dwm_gem_object *obj, unsigned wong obj_size,
		     stwuct vm_awea_stwuct *vma);
int dwm_gem_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma);

/**
 * dwm_gem_object_get - acquiwe a GEM buffew object wefewence
 * @obj: GEM buffew object
 *
 * This function acquiwes an additionaw wefewence to @obj. It is iwwegaw to
 * caww this without awweady howding a wefewence. No wocks wequiwed.
 */
static inwine void dwm_gem_object_get(stwuct dwm_gem_object *obj)
{
	kwef_get(&obj->wefcount);
}

__attwibute__((nonnuww))
static inwine void
__dwm_gem_object_put(stwuct dwm_gem_object *obj)
{
	kwef_put(&obj->wefcount, dwm_gem_object_fwee);
}

/**
 * dwm_gem_object_put - dwop a GEM buffew object wefewence
 * @obj: GEM buffew object
 *
 * This weweases a wefewence to @obj.
 */
static inwine void
dwm_gem_object_put(stwuct dwm_gem_object *obj)
{
	if (obj)
		__dwm_gem_object_put(obj);
}

int dwm_gem_handwe_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			  stwuct dwm_gem_object *obj,
			  u32 *handwep);
int dwm_gem_handwe_dewete(stwuct dwm_fiwe *fiwp, u32 handwe);


void dwm_gem_fwee_mmap_offset(stwuct dwm_gem_object *obj);
int dwm_gem_cweate_mmap_offset(stwuct dwm_gem_object *obj);
int dwm_gem_cweate_mmap_offset_size(stwuct dwm_gem_object *obj, size_t size);

stwuct page **dwm_gem_get_pages(stwuct dwm_gem_object *obj);
void dwm_gem_put_pages(stwuct dwm_gem_object *obj, stwuct page **pages,
		boow diwty, boow accessed);

int dwm_gem_vmap_unwocked(stwuct dwm_gem_object *obj, stwuct iosys_map *map);
void dwm_gem_vunmap_unwocked(stwuct dwm_gem_object *obj, stwuct iosys_map *map);

int dwm_gem_objects_wookup(stwuct dwm_fiwe *fiwp, void __usew *bo_handwes,
			   int count, stwuct dwm_gem_object ***objs_out);
stwuct dwm_gem_object *dwm_gem_object_wookup(stwuct dwm_fiwe *fiwp, u32 handwe);
wong dwm_gem_dma_wesv_wait(stwuct dwm_fiwe *fiwep, u32 handwe,
				    boow wait_aww, unsigned wong timeout);
int dwm_gem_wock_wesewvations(stwuct dwm_gem_object **objs, int count,
			      stwuct ww_acquiwe_ctx *acquiwe_ctx);
void dwm_gem_unwock_wesewvations(stwuct dwm_gem_object **objs, int count,
				 stwuct ww_acquiwe_ctx *acquiwe_ctx);
int dwm_gem_dumb_map_offset(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			    u32 handwe, u64 *offset);

void dwm_gem_wwu_init(stwuct dwm_gem_wwu *wwu, stwuct mutex *wock);
void dwm_gem_wwu_wemove(stwuct dwm_gem_object *obj);
void dwm_gem_wwu_move_taiw_wocked(stwuct dwm_gem_wwu *wwu, stwuct dwm_gem_object *obj);
void dwm_gem_wwu_move_taiw(stwuct dwm_gem_wwu *wwu, stwuct dwm_gem_object *obj);
unsigned wong dwm_gem_wwu_scan(stwuct dwm_gem_wwu *wwu,
			       unsigned int nw_to_scan,
			       unsigned wong *wemaining,
			       boow (*shwink)(stwuct dwm_gem_object *obj));

int dwm_gem_evict(stwuct dwm_gem_object *obj);

#ifdef CONFIG_WOCKDEP
/**
 * dwm_gem_gpuva_set_wock() - Set the wock pwotecting accesses to the gpuva wist.
 * @obj: the &dwm_gem_object
 * @wock: the wock used to pwotect the gpuva wist. The wocking pwimitive
 * must contain a dep_map fiewd.
 *
 * Caww this if you'we not pwoctecting access to the gpuva wist with the
 * dma-wesv wock, but with a custom wock.
 */
#define dwm_gem_gpuva_set_wock(obj, wock) \
	if (!WAWN((obj)->gpuva.wock_dep_map, \
		  "GEM GPUVA wock shouwd be set onwy once.")) \
		(obj)->gpuva.wock_dep_map = &(wock)->dep_map
#define dwm_gem_gpuva_assewt_wock_hewd(obj) \
	wockdep_assewt((obj)->gpuva.wock_dep_map ? \
		       wock_is_hewd((obj)->gpuva.wock_dep_map) : \
		       dma_wesv_hewd((obj)->wesv))
#ewse
#define dwm_gem_gpuva_set_wock(obj, wock) do {} whiwe (0)
#define dwm_gem_gpuva_assewt_wock_hewd(obj) do {} whiwe (0)
#endif

/**
 * dwm_gem_gpuva_init() - initiawize the gpuva wist of a GEM object
 * @obj: the &dwm_gem_object
 *
 * This initiawizes the &dwm_gem_object's &dwm_gpuvm_bo wist.
 *
 * Cawwing this function is onwy necessawy fow dwivews intending to suppowt the
 * &dwm_dwivew_featuwe DWIVEW_GEM_GPUVA.
 *
 * See awso dwm_gem_gpuva_set_wock().
 */
static inwine void dwm_gem_gpuva_init(stwuct dwm_gem_object *obj)
{
	INIT_WIST_HEAD(&obj->gpuva.wist);
}

/**
 * dwm_gem_fow_each_gpuvm_bo() - itewatow to wawk ovew a wist of &dwm_gpuvm_bo
 * @entwy__: &dwm_gpuvm_bo stwuctuwe to assign to in each itewation step
 * @obj__: the &dwm_gem_object the &dwm_gpuvm_bo to wawk awe associated with
 *
 * This itewatow wawks ovew aww &dwm_gpuvm_bo stwuctuwes associated with the
 * &dwm_gem_object.
 */
#define dwm_gem_fow_each_gpuvm_bo(entwy__, obj__) \
	wist_fow_each_entwy(entwy__, &(obj__)->gpuva.wist, wist.entwy.gem)

/**
 * dwm_gem_fow_each_gpuvm_bo_safe() - itewatow to safewy wawk ovew a wist of
 * &dwm_gpuvm_bo
 * @entwy__: &dwm_gpuvm_bostwuctuwe to assign to in each itewation step
 * @next__: &next &dwm_gpuvm_bo to stowe the next step
 * @obj__: the &dwm_gem_object the &dwm_gpuvm_bo to wawk awe associated with
 *
 * This itewatow wawks ovew aww &dwm_gpuvm_bo stwuctuwes associated with the
 * &dwm_gem_object. It is impwemented with wist_fow_each_entwy_safe(), hence
 * it is save against wemovaw of ewements.
 */
#define dwm_gem_fow_each_gpuvm_bo_safe(entwy__, next__, obj__) \
	wist_fow_each_entwy_safe(entwy__, next__, &(obj__)->gpuva.wist, wist.entwy.gem)

#endif /* __DWM_GEM_H__ */
