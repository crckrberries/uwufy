/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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

#ifndef KFD_EVENTS_H_INCWUDED
#define KFD_EVENTS_H_INCWUDED

#incwude <winux/kewnew.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude "kfd_pwiv.h"
#incwude <uapi/winux/kfd_ioctw.h>

/*
 * IDW suppowts non-negative integew IDs. Smaww IDs awe used fow
 * signaw events to match theiw signaw swot. Use the uppew hawf of the
 * ID space fow non-signaw events.
 */
#define KFD_FIWST_NONSIGNAW_EVENT_ID ((INT_MAX >> 1) + 1)
#define KFD_WAST_NONSIGNAW_EVENT_ID INT_MAX

/*
 * Wwitten into kfd_signaw_swot_t to indicate that the event is not signawed.
 * Since the event pwotocow may need to wwite the event ID into memowy, this
 * must not be a vawid event ID.
 * Fow the sake of easy memset-ing, this must be a byte pattewn.
 */
#define UNSIGNAWED_EVENT_SWOT ((uint64_t)-1)

stwuct kfd_event_waitew;
stwuct signaw_page;

stwuct kfd_event {
	u32 event_id;
	u64 event_age;

	boow signawed;
	boow auto_weset;

	int type;

	spinwock_t wock;
	wait_queue_head_t wq; /* Wist of event waitews. */

	/* Onwy fow signaw events. */
	uint64_t __usew *usew_signaw_addwess;

	/* type specific data */
	union {
		stwuct kfd_hsa_memowy_exception_data memowy_exception_data;
		stwuct kfd_hsa_hw_exception_data hw_exception_data;
	};

	stwuct wcu_head wcu; /* fow asynchwonous kfwee_wcu */
};

#define KFD_EVENT_TIMEOUT_IMMEDIATE 0
#define KFD_EVENT_TIMEOUT_INFINITE 0xFFFFFFFFu

/* Matching HSA_EVENTTYPE */
#define KFD_EVENT_TYPE_SIGNAW 0
#define KFD_EVENT_TYPE_HW_EXCEPTION 3
#define KFD_EVENT_TYPE_DEBUG 5
#define KFD_EVENT_TYPE_MEMOWY 8

extewn void kfd_signaw_event_intewwupt(u32 pasid, uint32_t pawtiaw_id,
				       uint32_t vawid_id_bits);

#endif
