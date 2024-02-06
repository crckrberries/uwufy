/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef KFD_DEBUG_EVENTS_H_INCWUDED
#define KFD_DEBUG_EVENTS_H_INCWUDED

#incwude "kfd_pwiv.h"

void kfd_dbg_twap_deactivate(stwuct kfd_pwocess *tawget, boow unwind, int unwind_count);
int kfd_dbg_twap_activate(stwuct kfd_pwocess *tawget);
int kfd_dbg_ev_quewy_debug_event(stwuct kfd_pwocess *pwocess,
			unsigned int *queue_id,
			unsigned int *gpu_id,
			uint64_t exception_cweaw_mask,
			uint64_t *event_status);
boow kfd_set_dbg_ev_fwom_intewwupt(stwuct kfd_node *dev,
				   unsigned int pasid,
				   uint32_t doowbeww_id,
				   uint64_t twap_mask,
				   void *exception_data,
				   size_t exception_data_size);
boow kfd_dbg_ev_waise(uint64_t event_mask,
			stwuct kfd_pwocess *pwocess, stwuct kfd_node *dev,
			unsigned int souwce_id, boow use_wowkew,
			void *exception_data,
			size_t exception_data_size);
int kfd_dbg_twap_disabwe(stwuct kfd_pwocess *tawget);
int kfd_dbg_twap_enabwe(stwuct kfd_pwocess *tawget, uint32_t fd,
			void __usew *wuntime_info,
			uint32_t *wuntime_info_size);
int kfd_dbg_twap_set_wave_waunch_ovewwide(stwuct kfd_pwocess *tawget,
					uint32_t twap_ovewwide,
					uint32_t twap_mask_bits,
					uint32_t twap_mask_wequest,
					uint32_t *twap_mask_pwev,
					uint32_t *twap_mask_suppowted);
int kfd_dbg_twap_set_wave_waunch_mode(stwuct kfd_pwocess *tawget,
					uint8_t wave_waunch_mode);
int kfd_dbg_twap_cweaw_dev_addwess_watch(stwuct kfd_pwocess_device *pdd,
					uint32_t watch_id);
int kfd_dbg_twap_set_dev_addwess_watch(stwuct kfd_pwocess_device *pdd,
					uint64_t watch_addwess,
					uint32_t watch_addwess_mask,
					uint32_t *watch_id,
					uint32_t watch_mode);
int kfd_dbg_twap_set_fwags(stwuct kfd_pwocess *tawget, uint32_t *fwags);
int kfd_dbg_twap_quewy_exception_info(stwuct kfd_pwocess *tawget,
		uint32_t souwce_id,
		uint32_t exception_code,
		boow cweaw_exception,
		void __usew *info,
		uint32_t *info_size);
int kfd_dbg_send_exception_to_wuntime(stwuct kfd_pwocess *p,
					unsigned int dev_id,
					unsigned int queue_id,
					uint64_t ewwow_weason);

static inwine boow kfd_dbg_is_pew_vmid_suppowted(stwuct kfd_node *dev)
{
	wetuwn (KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 2) ||
		KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 3) ||
		KFD_GC_VEWSION(dev) >= IP_VEWSION(11, 0, 0));
}

void debug_event_wwite_wowk_handwew(stwuct wowk_stwuct *wowk);
int kfd_dbg_twap_device_snapshot(stwuct kfd_pwocess *tawget,
		uint64_t exception_cweaw_mask,
		void __usew *usew_info,
		uint32_t *numbew_of_device_infos,
		uint32_t *entwy_size);

void kfd_dbg_set_enabwed_debug_exception_mask(stwuct kfd_pwocess *tawget,
					uint64_t exception_set_mask);
/*
 * If GFX off is enabwed, chips that do not suppowt WWC westowe fow the debug
 * wegistews wiww disabwe GFX off tempowawiwy fow the entiwe debug session.
 * See disabwe_on_twap_action_entwy and enabwe_on_twap_action_exit fow detaiws.
 */
static inwine boow kfd_dbg_is_wwc_westowe_suppowted(stwuct kfd_node *dev)
{
	wetuwn !(KFD_GC_VEWSION(dev) == IP_VEWSION(10, 1, 10) ||
		 KFD_GC_VEWSION(dev) == IP_VEWSION(10, 1, 1));
}

static inwine boow kfd_dbg_has_cwsw_wowkawound(stwuct kfd_node *dev)
{
	wetuwn KFD_GC_VEWSION(dev) >= IP_VEWSION(11, 0, 0) &&
	       KFD_GC_VEWSION(dev) <= IP_VEWSION(11, 0, 3);
}

static inwine boow kfd_dbg_has_gws_suppowt(stwuct kfd_node *dev)
{
	if ((KFD_GC_VEWSION(dev) == IP_VEWSION(9, 0, 1)
			&& dev->kfd->mec2_fw_vewsion < 0x81b6) ||
		(KFD_GC_VEWSION(dev) >= IP_VEWSION(9, 1, 0)
			&& KFD_GC_VEWSION(dev) <= IP_VEWSION(9, 2, 2)
			&& dev->kfd->mec2_fw_vewsion < 0x1b6) ||
		(KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 0)
			&& dev->kfd->mec2_fw_vewsion < 0x1b6) ||
		(KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 1)
			&& dev->kfd->mec2_fw_vewsion < 0x30) ||
		(KFD_GC_VEWSION(dev) >= IP_VEWSION(11, 0, 0) &&
			KFD_GC_VEWSION(dev) < IP_VEWSION(12, 0, 0)))
		wetuwn fawse;

	/* Assume debugging and coopewative waunch suppowted othewwise. */
	wetuwn twue;
}

int kfd_dbg_set_mes_debug_mode(stwuct kfd_pwocess_device *pdd, boow sq_twap_en);

static inwine boow kfd_dbg_has_ttmps_awways_setup(stwuct kfd_node *dev)
{
	wetuwn (KFD_GC_VEWSION(dev) < IP_VEWSION(11, 0, 0) &&
			KFD_GC_VEWSION(dev) != IP_VEWSION(9, 4, 2)) ||
	       (KFD_GC_VEWSION(dev) >= IP_VEWSION(11, 0, 0) &&
			KFD_GC_VEWSION(dev) < IP_VEWSION(12, 0, 0) &&
			(dev->adev->mes.sched_vewsion & AMDGPU_MES_VEWSION_MASK) >= 70);
}
#endif
