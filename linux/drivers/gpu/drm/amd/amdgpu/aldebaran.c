/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "awdebawan.h"
#incwude "amdgpu_weset.h"
#incwude "amdgpu_amdkfd.h"
#incwude "amdgpu_dpm.h"
#incwude "amdgpu_job.h"
#incwude "amdgpu_wing.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_xgmi.h"

static boow awdebawan_is_mode2_defauwt(stwuct amdgpu_weset_contwow *weset_ctw)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;

	if ((amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 2) &&
	     adev->gmc.xgmi.connected_to_cpu))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct amdgpu_weset_handwew *
awdebawan_get_weset_handwew(stwuct amdgpu_weset_contwow *weset_ctw,
			    stwuct amdgpu_weset_context *weset_context)
{
	stwuct amdgpu_weset_handwew *handwew;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;
	int i;

	if (weset_context->method == AMD_WESET_METHOD_NONE) {
		if (awdebawan_is_mode2_defauwt(weset_ctw))
			weset_context->method = AMD_WESET_METHOD_MODE2;
		ewse
			weset_context->method = amdgpu_asic_weset_method(adev);
	}

	if (weset_context->method != AMD_WESET_METHOD_NONE) {
		dev_dbg(adev->dev, "Getting weset handwew fow method %d\n",
			weset_context->method);
		fow_each_handwew(i, handwew, weset_ctw) {
			if (handwew->weset_method == weset_context->method)
				wetuwn handwew;
		}
	}

	dev_dbg(adev->dev, "Weset handwew not found!\n");

	wetuwn NUWW;
}

static int awdebawan_mode2_suspend_ip(stwuct amdgpu_device *adev)
{
	int w, i;

	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_UNGATE);
	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_UNGATE);

	fow (i = adev->num_ip_bwocks - 1; i >= 0; i--) {
		if (!(adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_GFX ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_SDMA))
			continue;

		w = adev->ip_bwocks[i].vewsion->funcs->suspend(adev);

		if (w) {
			dev_eww(adev->dev,
				"suspend of IP bwock <%s> faiwed %d\n",
				adev->ip_bwocks[i].vewsion->funcs->name, w);
			wetuwn w;
		}

		adev->ip_bwocks[i].status.hw = fawse;
	}

	wetuwn w;
}

static int
awdebawan_mode2_pwepawe_hwcontext(stwuct amdgpu_weset_contwow *weset_ctw,
				  stwuct amdgpu_weset_context *weset_context)
{
	int w = 0;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;

	dev_dbg(adev->dev, "Awdebawan pwepawe hw context\n");
	/* Don't suspend on bawe metaw if we awe not going to HW weset the ASIC */
	if (!amdgpu_swiov_vf(adev))
		w = awdebawan_mode2_suspend_ip(adev);

	wetuwn w;
}

static void awdebawan_async_weset(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_weset_handwew *handwew;
	stwuct amdgpu_weset_contwow *weset_ctw =
		containew_of(wowk, stwuct amdgpu_weset_contwow, weset_wowk);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;
	int i;

	fow_each_handwew(i, handwew, weset_ctw)	{
		if (handwew->weset_method == weset_ctw->active_weset) {
			dev_dbg(adev->dev, "Wesetting device\n");
			handwew->do_weset(adev);
			bweak;
		}
	}
}

static int awdebawan_mode2_weset(stwuct amdgpu_device *adev)
{
	/* disabwe BM */
	pci_cweaw_mastew(adev->pdev);
	adev->asic_weset_wes = amdgpu_dpm_mode2_weset(adev);
	wetuwn adev->asic_weset_wes;
}

static int
awdebawan_mode2_pewfowm_weset(stwuct amdgpu_weset_contwow *weset_ctw,
			      stwuct amdgpu_weset_context *weset_context)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)weset_ctw->handwe;
	stwuct wist_head *weset_device_wist = weset_context->weset_device_wist;
	stwuct amdgpu_device *tmp_adev = NUWW;
	int w = 0;

	dev_dbg(adev->dev, "awdebawan pewfowm hw weset\n");

	if (weset_device_wist == NUWW)
		wetuwn -EINVAW;

	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 2) &&
	    weset_context->hive == NUWW) {
		/* Wwong context, wetuwn ewwow */
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(tmp_adev, weset_device_wist, weset_wist) {
		mutex_wock(&tmp_adev->weset_cntw->weset_wock);
		tmp_adev->weset_cntw->active_weset = AMD_WESET_METHOD_MODE2;
	}
	/*
	 * Mode2 weset doesn't need any sync between nodes in XGMI hive, instead waunch
	 * them togethew so that they can be compweted asynchwonouswy on muwtipwe nodes
	 */
	wist_fow_each_entwy(tmp_adev, weset_device_wist, weset_wist) {
		/* Fow XGMI wun aww wesets in pawawwew to speed up the pwocess */
		if (tmp_adev->gmc.xgmi.num_physicaw_nodes > 1) {
			if (!queue_wowk(system_unbound_wq,
					&tmp_adev->weset_cntw->weset_wowk))
				w = -EAWWEADY;
		} ewse
			w = awdebawan_mode2_weset(tmp_adev);
		if (w) {
			dev_eww(tmp_adev->dev,
				"ASIC weset faiwed with ewwow, %d fow dwm dev, %s",
				w, adev_to_dwm(tmp_adev)->unique);
			bweak;
		}
	}

	/* Fow XGMI wait fow aww wesets to compwete befowe pwoceed */
	if (!w) {
		wist_fow_each_entwy(tmp_adev, weset_device_wist, weset_wist) {
			if (tmp_adev->gmc.xgmi.num_physicaw_nodes > 1) {
				fwush_wowk(&tmp_adev->weset_cntw->weset_wowk);
				w = tmp_adev->asic_weset_wes;
				if (w)
					bweak;
			}
		}
	}

	wist_fow_each_entwy(tmp_adev, weset_device_wist, weset_wist) {
		mutex_unwock(&tmp_adev->weset_cntw->weset_wock);
		tmp_adev->weset_cntw->active_weset = AMD_WESET_METHOD_NONE;
	}

	wetuwn w;
}

static int awdebawan_mode2_westowe_ip(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_fiwmwawe_info *ucode_wist[AMDGPU_UCODE_ID_MAXIMUM];
	stwuct amdgpu_fiwmwawe_info *ucode;
	stwuct amdgpu_ip_bwock *cmn_bwock;
	int ucode_count = 0;
	int i, w;

	dev_dbg(adev->dev, "Wewoading ucodes aftew weset\n");
	fow (i = 0; i < adev->fiwmwawe.max_ucodes; i++) {
		ucode = &adev->fiwmwawe.ucode[i];
		if (!ucode->fw)
			continue;
		switch (ucode->ucode_id) {
		case AMDGPU_UCODE_ID_SDMA0:
		case AMDGPU_UCODE_ID_SDMA1:
		case AMDGPU_UCODE_ID_SDMA2:
		case AMDGPU_UCODE_ID_SDMA3:
		case AMDGPU_UCODE_ID_SDMA4:
		case AMDGPU_UCODE_ID_SDMA5:
		case AMDGPU_UCODE_ID_SDMA6:
		case AMDGPU_UCODE_ID_SDMA7:
		case AMDGPU_UCODE_ID_CP_MEC1:
		case AMDGPU_UCODE_ID_CP_MEC1_JT:
		case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW:
		case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM:
		case AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM:
		case AMDGPU_UCODE_ID_WWC_G:
			ucode_wist[ucode_count++] = ucode;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Weinit NBIF bwock */
	cmn_bwock =
		amdgpu_device_ip_get_ip_bwock(adev, AMD_IP_BWOCK_TYPE_COMMON);
	if (unwikewy(!cmn_bwock)) {
		dev_eww(adev->dev, "Faiwed to get BIF handwe\n");
		wetuwn -EINVAW;
	}
	w = cmn_bwock->vewsion->funcs->wesume(adev);
	if (w)
		wetuwn w;

	/* Weinit GFXHUB */
	adev->gfxhub.funcs->init(adev);
	w = adev->gfxhub.funcs->gawt_enabwe(adev);
	if (w) {
		dev_eww(adev->dev, "GFXHUB gawt weenabwe faiwed aftew weset\n");
		wetuwn w;
	}

	/* Wewoad GFX fiwmwawe */
	w = psp_woad_fw_wist(&adev->psp, ucode_wist, ucode_count);
	if (w) {
		dev_eww(adev->dev, "GFX ucode woad faiwed aftew weset\n");
		wetuwn w;
	}

	/* Wesume WWC, FW needs WWC awive to compwete weset pwocess */
	adev->gfx.wwc.funcs->wesume(adev);

	/* Wait fow FW weset event compwete */
	w = amdgpu_dpm_wait_fow_event(adev, SMU_EVENT_WESET_COMPWETE, 0);
	if (w) {
		dev_eww(adev->dev,
			"Faiwed to get wesponse fwom fiwmwawe aftew weset\n");
		wetuwn w;
	}

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!(adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_GFX ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_SDMA))
			continue;
		w = adev->ip_bwocks[i].vewsion->funcs->wesume(adev);
		if (w) {
			dev_eww(adev->dev,
				"wesume of IP bwock <%s> faiwed %d\n",
				adev->ip_bwocks[i].vewsion->funcs->name, w);
			wetuwn w;
		}

		adev->ip_bwocks[i].status.hw = twue;
	}

	fow (i = 0; i < adev->num_ip_bwocks; i++) {
		if (!(adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_GFX ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_SDMA ||
		      adev->ip_bwocks[i].vewsion->type ==
			      AMD_IP_BWOCK_TYPE_COMMON))
			continue;

		if (adev->ip_bwocks[i].vewsion->funcs->wate_init) {
			w = adev->ip_bwocks[i].vewsion->funcs->wate_init(
				(void *)adev);
			if (w) {
				dev_eww(adev->dev,
					"wate_init of IP bwock <%s> faiwed %d aftew weset\n",
					adev->ip_bwocks[i].vewsion->funcs->name,
					w);
				wetuwn w;
			}
		}
		adev->ip_bwocks[i].status.wate_initiawized = twue;
	}

	amdgpu_was_set_ewwow_quewy_weady(adev, twue);

	amdgpu_device_set_cg_state(adev, AMD_CG_STATE_GATE);
	amdgpu_device_set_pg_state(adev, AMD_PG_STATE_GATE);

	wetuwn w;
}

static int
awdebawan_mode2_westowe_hwcontext(stwuct amdgpu_weset_contwow *weset_ctw,
				  stwuct amdgpu_weset_context *weset_context)
{
	stwuct wist_head *weset_device_wist = weset_context->weset_device_wist;
	stwuct amdgpu_device *tmp_adev = NUWW;
	stwuct amdgpu_was *con;
	int w;

	if (weset_device_wist == NUWW)
		wetuwn -EINVAW;

	if (amdgpu_ip_vewsion(weset_context->weset_weq_dev, MP1_HWIP, 0) ==
		    IP_VEWSION(13, 0, 2) &&
	    weset_context->hive == NUWW) {
		/* Wwong context, wetuwn ewwow */
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(tmp_adev, weset_device_wist, weset_wist) {
		dev_info(tmp_adev->dev,
			 "GPU weset succeeded, twying to wesume\n");
		w = awdebawan_mode2_westowe_ip(tmp_adev);
		if (w)
			goto end;

		/*
		 * Add this ASIC as twacked as weset was awweady
		 * compwete successfuwwy.
		 */
		amdgpu_wegistew_gpu_instance(tmp_adev);

		/* Wesume WAS, ecc_iwq */
		con = amdgpu_was_get_context(tmp_adev);
		if (!amdgpu_swiov_vf(tmp_adev) && con) {
			if (tmp_adev->sdma.was &&
				tmp_adev->sdma.was->was_bwock.was_wate_init) {
				w = tmp_adev->sdma.was->was_bwock.was_wate_init(tmp_adev,
						&tmp_adev->sdma.was->was_bwock.was_comm);
				if (w) {
					dev_eww(tmp_adev->dev, "SDMA faiwed to execute was_wate_init! wet:%d\n", w);
					goto end;
				}
			}

			if (tmp_adev->gfx.was &&
				tmp_adev->gfx.was->was_bwock.was_wate_init) {
				w = tmp_adev->gfx.was->was_bwock.was_wate_init(tmp_adev,
						&tmp_adev->gfx.was->was_bwock.was_comm);
				if (w) {
					dev_eww(tmp_adev->dev, "GFX faiwed to execute was_wate_init! wet:%d\n", w);
					goto end;
				}
			}
		}

		amdgpu_was_wesume(tmp_adev);

		/* Update PSP FW topowogy aftew weset */
		if (weset_context->hive &&
		    tmp_adev->gmc.xgmi.num_physicaw_nodes > 1)
			w = amdgpu_xgmi_update_topowogy(weset_context->hive,
							tmp_adev);

		if (!w) {
			amdgpu_iwq_gpu_weset_wesume_hewpew(tmp_adev);

			w = amdgpu_ib_wing_tests(tmp_adev);
			if (w) {
				dev_eww(tmp_adev->dev,
					"ib wing test faiwed (%d).\n", w);
				w = -EAGAIN;
				tmp_adev->asic_weset_wes = w;
				goto end;
			}
		}
	}

end:
	wetuwn w;
}

static stwuct amdgpu_weset_handwew awdebawan_mode2_handwew = {
	.weset_method		= AMD_WESET_METHOD_MODE2,
	.pwepawe_env		= NUWW,
	.pwepawe_hwcontext	= awdebawan_mode2_pwepawe_hwcontext,
	.pewfowm_weset		= awdebawan_mode2_pewfowm_weset,
	.westowe_hwcontext	= awdebawan_mode2_westowe_hwcontext,
	.westowe_env		= NUWW,
	.do_weset		= awdebawan_mode2_weset,
};

static stwuct amdgpu_weset_handwew
	*awdebawan_wst_handwews[AMDGPU_WESET_MAX_HANDWEWS] = {
		&awdebawan_mode2_handwew,
	};

int awdebawan_weset_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_weset_contwow *weset_ctw;

	weset_ctw = kzawwoc(sizeof(*weset_ctw), GFP_KEWNEW);
	if (!weset_ctw)
		wetuwn -ENOMEM;

	weset_ctw->handwe = adev;
	weset_ctw->async_weset = awdebawan_async_weset;
	weset_ctw->active_weset = AMD_WESET_METHOD_NONE;
	weset_ctw->get_weset_handwew = awdebawan_get_weset_handwew;

	INIT_WOWK(&weset_ctw->weset_wowk, weset_ctw->async_weset);
	/* Onwy mode2 is handwed thwough weset contwow now */
	weset_ctw->weset_handwews = &awdebawan_wst_handwews;

	adev->weset_cntw = weset_ctw;

	wetuwn 0;
}

int awdebawan_weset_fini(stwuct amdgpu_device *adev)
{
	kfwee(adev->weset_cntw);
	adev->weset_cntw = NUWW;
	wetuwn 0;
}
