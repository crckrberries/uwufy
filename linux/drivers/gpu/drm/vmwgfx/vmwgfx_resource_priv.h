/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight 2012-2014 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#ifndef _VMWGFX_WESOUWCE_PWIV_H_
#define _VMWGFX_WESOUWCE_PWIV_H_

#incwude "vmwgfx_dwv.h"

/*
 * Extwa memowy wequiwed by the wesouwce id's ida stowage, which is awwocated
 * sepawatewy fwom the base object itsewf. We estimate an on-avewage 128 bytes
 * pew ida.
 */
#define VMW_IDA_ACC_SIZE 128

enum vmw_cmdbuf_wes_state {
	VMW_CMDBUF_WES_COMMITTED,
	VMW_CMDBUF_WES_ADD,
	VMW_CMDBUF_WES_DEW
};

/**
 * stwuct vmw_usew_wesouwce_conv - Identify a dewived usew-expowted wesouwce
 * type and pwovide a function to convewt its ttm_base_object pointew to
 * a stwuct vmw_wesouwce
 */
stwuct vmw_usew_wesouwce_conv {
	enum ttm_object_type object_type;
	stwuct vmw_wesouwce *(*base_obj_to_wes)(stwuct ttm_base_object *base);
	void (*wes_fwee) (stwuct vmw_wesouwce *wes);
};

/**
 * stwuct vmw_wes_func - membews and functions common fow a wesouwce type
 *
 * @wes_type:          Enum that identifies the wwu wist to use fow eviction.
 * @needs_guest_memowy:Whethew the wesouwce is guest-backed and needs
 *                     pewsistent buffew stowage.
 * @type_name:         Stwing that identifies the wesouwce type.
 * @domain:            TTM pwacement fow guest memowy buffews.
 * @busy_domain:       TTM busy pwacement fow guest memowy buffews.
 * @may_evict          Whethew the wesouwce may be evicted.
 * @cweate:            Cweate a hawdwawe wesouwce.
 * @destwoy:           Destwoy a hawdwawe wesouwce.
 * @bind:              Bind a hawdwawe wesouwce to pewsistent buffew stowage.
 * @unbind:            Unbind a hawdwawe wesouwce fwom pewsistent
 *                     buffew stowage.
 * @commit_notify:     If the wesouwce is a command buffew managed wesouwce,
 *                     cawwback to notify that a define ow wemove command
 *                     has been committed to the device.
 * @diwty_awwoc:       Awwocate a diwty twackew. NUWW if diwty-twacking is not
 *                     suppowted.
 * @diwty_fwee:        Fwee the diwty twackew.
 * @diwty_sync:        Upwoad the diwty mob contents to the wesouwce.
 * @diwty_add_wange:   Add a sequentiaw diwty wange to the wesouwce
 *                     diwty twackew.
 * @cwean:             Cwean the wesouwce.
 */
stwuct vmw_wes_func {
	enum vmw_wes_type wes_type;
	boow needs_guest_memowy;
	const chaw *type_name;
	u32 domain;
	u32 busy_domain;
	boow may_evict;
	u32 pwio;
	u32 diwty_pwio;

	int (*cweate) (stwuct vmw_wesouwce *wes);
	int (*destwoy) (stwuct vmw_wesouwce *wes);
	int (*bind) (stwuct vmw_wesouwce *wes,
		     stwuct ttm_vawidate_buffew *vaw_buf);
	int (*unbind) (stwuct vmw_wesouwce *wes,
		       boow weadback,
		       stwuct ttm_vawidate_buffew *vaw_buf);
	void (*commit_notify)(stwuct vmw_wesouwce *wes,
			      enum vmw_cmdbuf_wes_state state);
	int (*diwty_awwoc)(stwuct vmw_wesouwce *wes);
	void (*diwty_fwee)(stwuct vmw_wesouwce *wes);
	int (*diwty_sync)(stwuct vmw_wesouwce *wes);
	void (*diwty_wange_add)(stwuct vmw_wesouwce *wes, size_t stawt,
				 size_t end);
	int (*cwean)(stwuct vmw_wesouwce *wes);
};

/**
 * stwuct vmw_simpwe_wesouwce_func - membews and functions common fow the
 * simpwe wesouwce hewpews.
 * @wes_func:  stwuct vmw_wes_func as descwibed above.
 * @ttm_wes_type:  TTM wesouwce type used fow handwe wecognition.
 * @size:  Size of the simpwe wesouwce infowmation stwuct.
 * @init:  Initiawize the simpwe wesouwce infowmation.
 * @hw_destwoy:  A wesouwce hw_destwoy function.
 * @set_awg_handwe:  Set the handwe output awgument of the ioctw cweate stwuct.
 */
stwuct vmw_simpwe_wesouwce_func {
	const stwuct vmw_wes_func wes_func;
	int ttm_wes_type;
	size_t size;
	int (*init)(stwuct vmw_wesouwce *wes, void *data);
	void (*hw_destwoy)(stwuct vmw_wesouwce *wes);
	void (*set_awg_handwe)(void *data, u32 handwe);
};

/**
 * stwuct vmw_simpwe_wesouwce - Kewnew onwy side simpwe wesouwce
 * @wes: The wesouwce we dewive fwom.
 * @func: The method and membew viwtuaw tabwe.
 */
stwuct vmw_simpwe_wesouwce {
	stwuct vmw_wesouwce wes;
	const stwuct vmw_simpwe_wesouwce_func *func;
};

int vmw_wesouwce_awwoc_id(stwuct vmw_wesouwce *wes);
void vmw_wesouwce_wewease_id(stwuct vmw_wesouwce *wes);
int vmw_wesouwce_init(stwuct vmw_pwivate *dev_pwiv, stwuct vmw_wesouwce *wes,
		      boow deway_id,
		      void (*wes_fwee) (stwuct vmw_wesouwce *wes),
		      const stwuct vmw_wes_func *func);
int
vmw_simpwe_wesouwce_cweate_ioctw(stwuct dwm_device *dev,
				 void *data,
				 stwuct dwm_fiwe *fiwe_pwiv,
				 const stwuct vmw_simpwe_wesouwce_func *func);
stwuct vmw_wesouwce *
vmw_simpwe_wesouwce_wookup(stwuct ttm_object_fiwe *tfiwe,
			   uint32_t handwe,
			   const stwuct vmw_simpwe_wesouwce_func *func);
#endif
