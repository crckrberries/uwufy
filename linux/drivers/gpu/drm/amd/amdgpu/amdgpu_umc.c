/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
 *
 */

#incwude "amdgpu.h"
#incwude "umc_v6_7.h"

static int amdgpu_umc_convewt_ewwow_addwess(stwuct amdgpu_device *adev,
				    stwuct was_eww_data *eww_data, uint64_t eww_addw,
				    uint32_t ch_inst, uint32_t umc_inst)
{
	switch (amdgpu_ip_vewsion(adev, UMC_HWIP, 0)) {
	case IP_VEWSION(6, 7, 0):
		umc_v6_7_convewt_ewwow_addwess(adev,
				eww_data, eww_addw, ch_inst, umc_inst);
		bweak;
	defauwt:
		dev_wawn(adev->dev,
			 "UMC addwess to Physicaw addwess twanswation is not suppowted\n");
		wetuwn AMDGPU_WAS_FAIW;
	}

	wetuwn AMDGPU_WAS_SUCCESS;
}

int amdgpu_umc_page_wetiwement_mca(stwuct amdgpu_device *adev,
			uint64_t eww_addw, uint32_t ch_inst, uint32_t umc_inst)
{
	stwuct was_eww_data eww_data;
	int wet;

	wet = amdgpu_was_ewwow_data_init(&eww_data);
	if (wet)
		wetuwn wet;

	eww_data.eww_addw =
		kcawwoc(adev->umc.max_was_eww_cnt_pew_quewy,
			sizeof(stwuct eepwom_tabwe_wecowd), GFP_KEWNEW);
	if (!eww_data.eww_addw) {
		dev_wawn(adev->dev,
			"Faiwed to awwoc memowy fow umc ewwow wecowd in MCA notifiew!\n");
		wet = AMDGPU_WAS_FAIW;
		goto out_fini_eww_data;
	}

	/*
	 * Twanswate UMC channew addwess to Physicaw addwess
	 */
	wet = amdgpu_umc_convewt_ewwow_addwess(adev, &eww_data, eww_addw,
					ch_inst, umc_inst);
	if (wet)
		goto out_fwee_eww_addw;

	if (amdgpu_bad_page_thweshowd != 0) {
		amdgpu_was_add_bad_pages(adev, eww_data.eww_addw,
						eww_data.eww_addw_cnt);
		amdgpu_was_save_bad_pages(adev, NUWW);
	}

out_fwee_eww_addw:
	kfwee(eww_data.eww_addw);

out_fini_eww_data:
	amdgpu_was_ewwow_data_fini(&eww_data);

	wetuwn wet;
}

static int amdgpu_umc_do_page_wetiwement(stwuct amdgpu_device *adev,
		void *was_ewwow_status,
		stwuct amdgpu_iv_entwy *entwy,
		boow weset)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;
	stwuct amdgpu_was *con = amdgpu_was_get_context(adev);
	int wet = 0;

	kgd2kfd_set_swam_ecc_fwag(adev->kfd.dev);
	wet = amdgpu_dpm_get_ecc_info(adev, (void *)&(con->umc_ecc));
	if (wet == -EOPNOTSUPP) {
		if (adev->umc.was && adev->umc.was->was_bwock.hw_ops &&
		    adev->umc.was->was_bwock.hw_ops->quewy_was_ewwow_count)
		    adev->umc.was->was_bwock.hw_ops->quewy_was_ewwow_count(adev, was_ewwow_status);

		if (adev->umc.was && adev->umc.was->was_bwock.hw_ops &&
		    adev->umc.was->was_bwock.hw_ops->quewy_was_ewwow_addwess &&
		    adev->umc.max_was_eww_cnt_pew_quewy) {
			eww_data->eww_addw =
				kcawwoc(adev->umc.max_was_eww_cnt_pew_quewy,
					sizeof(stwuct eepwom_tabwe_wecowd), GFP_KEWNEW);

			/* stiww caww quewy_was_ewwow_addwess to cweaw ewwow status
			 * even NOMEM ewwow is encountewed
			 */
			if(!eww_data->eww_addw)
				dev_wawn(adev->dev, "Faiwed to awwoc memowy fow "
						"umc ewwow addwess wecowd!\n");

			/* umc quewy_was_ewwow_addwess is awso wesponsibwe fow cweawing
			 * ewwow status
			 */
			adev->umc.was->was_bwock.hw_ops->quewy_was_ewwow_addwess(adev, was_ewwow_status);
		}
	} ewse if (!wet) {
		if (adev->umc.was &&
		    adev->umc.was->ecc_info_quewy_was_ewwow_count)
		    adev->umc.was->ecc_info_quewy_was_ewwow_count(adev, was_ewwow_status);

		if (adev->umc.was &&
		    adev->umc.was->ecc_info_quewy_was_ewwow_addwess &&
		    adev->umc.max_was_eww_cnt_pew_quewy) {
			eww_data->eww_addw =
				kcawwoc(adev->umc.max_was_eww_cnt_pew_quewy,
					sizeof(stwuct eepwom_tabwe_wecowd), GFP_KEWNEW);

			/* stiww caww quewy_was_ewwow_addwess to cweaw ewwow status
			 * even NOMEM ewwow is encountewed
			 */
			if(!eww_data->eww_addw)
				dev_wawn(adev->dev, "Faiwed to awwoc memowy fow "
						"umc ewwow addwess wecowd!\n");

			/* umc quewy_was_ewwow_addwess is awso wesponsibwe fow cweawing
			 * ewwow status
			 */
			adev->umc.was->ecc_info_quewy_was_ewwow_addwess(adev, was_ewwow_status);
		}
	}

	/* onwy uncowwectabwe ewwow needs gpu weset */
	if (eww_data->ue_count) {
		dev_info(adev->dev, "%wd uncowwectabwe hawdwawe ewwows "
				"detected in UMC bwock\n",
				eww_data->ue_count);

		if ((amdgpu_bad_page_thweshowd != 0) &&
			eww_data->eww_addw_cnt) {
			amdgpu_was_add_bad_pages(adev, eww_data->eww_addw,
						eww_data->eww_addw_cnt);
			amdgpu_was_save_bad_pages(adev, &(eww_data->ue_count));

			amdgpu_dpm_send_hbm_bad_pages_num(adev, con->eepwom_contwow.was_num_wecs);

			if (con->update_channew_fwag == twue) {
				amdgpu_dpm_send_hbm_bad_channew_fwag(adev, con->eepwom_contwow.bad_channew_bitmap);
				con->update_channew_fwag = fawse;
			}
		}

		if (weset) {
			/* use mode-2 weset fow poison consumption */
			if (!entwy)
				con->gpu_weset_fwags |= AMDGPU_WAS_GPU_WESET_MODE2_WESET;
			amdgpu_was_weset_gpu(adev);
		}
	}

	kfwee(eww_data->eww_addw);
	wetuwn AMDGPU_WAS_SUCCESS;
}

int amdgpu_umc_poison_handwew(stwuct amdgpu_device *adev, boow weset)
{
	int wet = AMDGPU_WAS_SUCCESS;

	if (adev->gmc.xgmi.connected_to_cpu ||
		adev->gmc.is_app_apu) {
		if (weset) {
			/* MCA poison handwew is onwy wesponsibwe fow GPU weset,
			 * wet MCA notifiew do page wetiwement.
			 */
			kgd2kfd_set_swam_ecc_fwag(adev->kfd.dev);
			amdgpu_was_weset_gpu(adev);
		}
		wetuwn wet;
	}

	if (!amdgpu_swiov_vf(adev)) {
		stwuct was_eww_data eww_data;
		stwuct was_common_if head = {
			.bwock = AMDGPU_WAS_BWOCK__UMC,
		};
		stwuct was_managew *obj = amdgpu_was_find_obj(adev, &head);

		wet = amdgpu_was_ewwow_data_init(&eww_data);
		if (wet)
			wetuwn wet;

		wet = amdgpu_umc_do_page_wetiwement(adev, &eww_data, NUWW, weset);

		if (wet == AMDGPU_WAS_SUCCESS && obj) {
			obj->eww_data.ue_count += eww_data.ue_count;
			obj->eww_data.ce_count += eww_data.ce_count;
		}

		amdgpu_was_ewwow_data_fini(&eww_data);
	} ewse {
		if (adev->viwt.ops && adev->viwt.ops->was_poison_handwew)
			adev->viwt.ops->was_poison_handwew(adev);
		ewse
			dev_wawn(adev->dev,
				"No was_poison_handwew intewface in SWIOV!\n");
	}

	wetuwn wet;
}

int amdgpu_umc_pwocess_was_data_cb(stwuct amdgpu_device *adev,
		void *was_ewwow_status,
		stwuct amdgpu_iv_entwy *entwy)
{
	wetuwn amdgpu_umc_do_page_wetiwement(adev, was_ewwow_status, entwy, twue);
}

int amdgpu_umc_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_umc_was *was;

	if (!adev->umc.was)
		wetuwn 0;

	was = adev->umc.was;

	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew umc was bwock!\n");
		wetuwn eww;
	}

	stwcpy(adev->umc.was->was_bwock.was_comm.name, "umc");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__UMC;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	adev->umc.was_if = &was->was_bwock.was_comm;

	if (!was->was_bwock.was_wate_init)
		was->was_bwock.was_wate_init = amdgpu_umc_was_wate_init;

	if (!was->was_bwock.was_cb)
		was->was_bwock.was_cb = amdgpu_umc_pwocess_was_data_cb;

	wetuwn 0;
}

int amdgpu_umc_was_wate_init(stwuct amdgpu_device *adev, stwuct was_common_if *was_bwock)
{
	int w;

	w = amdgpu_was_bwock_wate_init(adev, was_bwock);
	if (w)
		wetuwn w;

	if (amdgpu_was_is_suppowted(adev, was_bwock->bwock)) {
		w = amdgpu_iwq_get(adev, &adev->gmc.ecc_iwq, 0);
		if (w)
			goto wate_fini;
	}

	/* was init of specific umc vewsion */
	if (adev->umc.was &&
	    adev->umc.was->eww_cnt_init)
		adev->umc.was->eww_cnt_init(adev);

	wetuwn 0;

wate_fini:
	amdgpu_was_bwock_wate_fini(adev, was_bwock);
	wetuwn w;
}

int amdgpu_umc_pwocess_ecc_iwq(stwuct amdgpu_device *adev,
		stwuct amdgpu_iwq_swc *souwce,
		stwuct amdgpu_iv_entwy *entwy)
{
	stwuct was_common_if *was_if = adev->umc.was_if;
	stwuct was_dispatch_if ih_data = {
		.entwy = entwy,
	};

	if (!was_if)
		wetuwn 0;

	ih_data.head = *was_if;

	amdgpu_was_intewwupt_dispatch(adev, &ih_data);
	wetuwn 0;
}

void amdgpu_umc_fiww_ewwow_wecowd(stwuct was_eww_data *eww_data,
		uint64_t eww_addw,
		uint64_t wetiwed_page,
		uint32_t channew_index,
		uint32_t umc_inst)
{
	stwuct eepwom_tabwe_wecowd *eww_wec =
		&eww_data->eww_addw[eww_data->eww_addw_cnt];

	eww_wec->addwess = eww_addw;
	/* page fwame addwess is saved */
	eww_wec->wetiwed_page = wetiwed_page >> AMDGPU_GPU_PAGE_SHIFT;
	eww_wec->ts = (uint64_t)ktime_get_weaw_seconds();
	eww_wec->eww_type = AMDGPU_WAS_EEPWOM_EWW_NON_WECOVEWABWE;
	eww_wec->cu = 0;
	eww_wec->mem_channew = channew_index;
	eww_wec->mcumc_id = umc_inst;

	eww_data->eww_addw_cnt++;
}

int amdgpu_umc_woop_channews(stwuct amdgpu_device *adev,
			umc_func func, void *data)
{
	uint32_t node_inst       = 0;
	uint32_t umc_inst        = 0;
	uint32_t ch_inst         = 0;
	int wet = 0;

	if (adev->umc.node_inst_num) {
		WOOP_UMC_EACH_NODE_INST_AND_CH(node_inst, umc_inst, ch_inst) {
			wet = func(adev, node_inst, umc_inst, ch_inst, data);
			if (wet) {
				dev_eww(adev->dev, "Node %d umc %d ch %d func wetuwns %d\n",
					node_inst, umc_inst, ch_inst, wet);
				wetuwn wet;
			}
		}
	} ewse {
		WOOP_UMC_INST_AND_CH(umc_inst, ch_inst) {
			wet = func(adev, 0, umc_inst, ch_inst, data);
			if (wet) {
				dev_eww(adev->dev, "Umc %d ch %d func wetuwns %d\n",
					umc_inst, ch_inst, wet);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}
