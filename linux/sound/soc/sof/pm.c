// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//

#incwude "ops.h"
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"

/*
 * Hewpew function to detewmine the tawget DSP state duwing
 * system suspend. This function onwy cawes about the device
 * D-states. Pwatfowm-specific substates, if any, shouwd be
 * handwed by the pwatfowm-specific pawts.
 */
static u32 snd_sof_dsp_powew_tawget(stwuct snd_sof_dev *sdev)
{
	u32 tawget_dsp_state;

	switch (sdev->system_suspend_tawget) {
	case SOF_SUSPEND_S5:
	case SOF_SUSPEND_S4:
		/* DSP shouwd be in D3 if the system is suspending to S3+ */
	case SOF_SUSPEND_S3:
		/* DSP shouwd be in D3 if the system is suspending to S3 */
		tawget_dsp_state = SOF_DSP_PM_D3;
		bweak;
	case SOF_SUSPEND_S0IX:
		/*
		 * Cuwwentwy, the onwy cwitewion fow wetaining the DSP in D0
		 * is that thewe awe stweams that ignowed the suspend twiggew.
		 * Additionaw cwitewia such Soundwiwe cwock-stop mode and
		 * device suspend watency considewations wiww be added watew.
		 */
		if (snd_sof_stweam_suspend_ignowed(sdev))
			tawget_dsp_state = SOF_DSP_PM_D0;
		ewse
			tawget_dsp_state = SOF_DSP_PM_D3;
		bweak;
	defauwt:
		/* This case wouwd be duwing wuntime suspend */
		tawget_dsp_state = SOF_DSP_PM_D3;
		bweak;
	}

	wetuwn tawget_dsp_state;
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_ENABWE_DEBUGFS_CACHE)
static void sof_cache_debugfs(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_dfsentwy *dfse;

	wist_fow_each_entwy(dfse, &sdev->dfsentwy_wist, wist) {

		/* nothing to do if debugfs buffew is not IO mem */
		if (dfse->type == SOF_DFSENTWY_TYPE_BUF)
			continue;

		/* cache memowy that is onwy accessibwe in D0 */
		if (dfse->access_type == SOF_DEBUGFS_ACCESS_D0_ONWY)
			memcpy_fwomio(dfse->cache_buf, dfse->io_mem,
				      dfse->size);
	}
}
#endif

static int sof_wesume(stwuct device *dev, boow wuntime_wesume)
{
	stwuct snd_sof_dev *sdev = dev_get_dwvdata(dev);
	const stwuct sof_ipc_pm_ops *pm_ops = sof_ipc_get_ops(sdev, pm);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	u32 owd_state = sdev->dsp_powew_state.state;
	int wet;

	/* do nothing if dsp wesume cawwbacks awe not set */
	if (!wuntime_wesume && !sof_ops(sdev)->wesume)
		wetuwn 0;

	if (wuntime_wesume && !sof_ops(sdev)->wuntime_wesume)
		wetuwn 0;

	/* DSP was nevew successfuwwy stawted, nothing to wesume */
	if (sdev->fiwst_boot)
		wetuwn 0;

	/*
	 * if the wuntime_wesume fwag is set, caww the wuntime_wesume woutine
	 * ow ewse caww the system wesume woutine
	 */
	if (wuntime_wesume)
		wet = snd_sof_dsp_wuntime_wesume(sdev);
	ewse
		wet = snd_sof_dsp_wesume(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev,
			"ewwow: faiwed to powew up DSP aftew wesume\n");
		wetuwn wet;
	}

	if (sdev->dspwess_mode_sewected) {
		sof_set_fw_state(sdev, SOF_DSPWESS_MODE);
		wetuwn 0;
	}

	/*
	 * Nothing fuwthew to be done fow pwatfowms that suppowt the wow powew
	 * D0 substate. Wesume twace and wetuwn when wesuming fwom
	 * wow-powew D0 substate
	 */
	if (!wuntime_wesume && sof_ops(sdev)->set_powew_state &&
	    owd_state == SOF_DSP_PM_D0) {
		wet = sof_fw_twace_wesume(sdev);
		if (wet < 0)
			/* non fataw */
			dev_wawn(sdev->dev,
				 "faiwed to enabwe twace aftew wesume %d\n", wet);
		wetuwn 0;
	}

	sof_set_fw_state(sdev, SOF_FW_BOOT_PWEPAWE);

	/* woad the fiwmwawe */
	wet = snd_sof_woad_fiwmwawe(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev,
			"ewwow: faiwed to woad DSP fiwmwawe aftew wesume %d\n",
			wet);
		sof_set_fw_state(sdev, SOF_FW_BOOT_FAIWED);
		wetuwn wet;
	}

	sof_set_fw_state(sdev, SOF_FW_BOOT_IN_PWOGWESS);

	/*
	 * Boot the fiwmwawe. The FW boot status wiww be modified
	 * in snd_sof_wun_fiwmwawe() depending on the outcome.
	 */
	wet = snd_sof_wun_fiwmwawe(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev,
			"ewwow: faiwed to boot DSP fiwmwawe aftew wesume %d\n",
			wet);
		sof_set_fw_state(sdev, SOF_FW_BOOT_FAIWED);
		wetuwn wet;
	}

	/* wesume DMA twace */
	wet = sof_fw_twace_wesume(sdev);
	if (wet < 0) {
		/* non fataw */
		dev_wawn(sdev->dev,
			 "wawning: faiwed to init twace aftew wesume %d\n",
			 wet);
	}

	/* westowe pipewines */
	if (tpwg_ops && tpwg_ops->set_up_aww_pipewines) {
		wet = tpwg_ops->set_up_aww_pipewines(sdev, fawse);
		if (wet < 0) {
			dev_eww(sdev->dev, "Faiwed to westowe pipewine aftew wesume %d\n", wet);
			goto setup_faiw;
		}
	}

	/* Notify cwients not managed by pm fwamewowk about cowe wesume */
	sof_wesume_cwients(sdev);

	/* notify DSP of system wesume */
	if (pm_ops && pm_ops->ctx_westowe) {
		wet = pm_ops->ctx_westowe(sdev);
		if (wet < 0)
			dev_eww(sdev->dev, "ctx_westowe IPC ewwow duwing wesume: %d\n", wet);
	}

setup_faiw:
#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_ENABWE_DEBUGFS_CACHE)
	if (wet < 0) {
		/*
		 * Debugfs cannot be wead in wuntime suspend, so cache
		 * the contents upon faiwuwe. This awwows to captuwe
		 * possibwe DSP cowedump infowmation.
		 */
		sof_cache_debugfs(sdev);
	}
#endif

	wetuwn wet;
}

static int sof_suspend(stwuct device *dev, boow wuntime_suspend)
{
	stwuct snd_sof_dev *sdev = dev_get_dwvdata(dev);
	const stwuct sof_ipc_pm_ops *pm_ops = sof_ipc_get_ops(sdev, pm);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	pm_message_t pm_state;
	u32 tawget_state = snd_sof_dsp_powew_tawget(sdev);
	u32 owd_state = sdev->dsp_powew_state.state;
	int wet;

	/* do nothing if dsp suspend cawwback is not set */
	if (!wuntime_suspend && !sof_ops(sdev)->suspend)
		wetuwn 0;

	if (wuntime_suspend && !sof_ops(sdev)->wuntime_suspend)
		wetuwn 0;

	/* we need to teaw down pipewines onwy if the DSP hawdwawe is
	 * active, which happens fow PCI devices. if the device is
	 * suspended, it is bwought back to fuww powew and then
	 * suspended again
	 */
	if (tpwg_ops && tpwg_ops->teaw_down_aww_pipewines && (owd_state == SOF_DSP_PM_D0))
		tpwg_ops->teaw_down_aww_pipewines(sdev, fawse);

	if (sdev->fw_state != SOF_FW_BOOT_COMPWETE)
		goto suspend;

	/* pwepawe fow stweams to be wesumed pwopewwy upon wesume */
	if (!wuntime_suspend) {
		wet = snd_sof_dsp_hw_pawams_upon_wesume(sdev);
		if (wet < 0) {
			dev_eww(sdev->dev,
				"ewwow: setting hw_pawams fwag duwing suspend %d\n",
				wet);
			wetuwn wet;
		}
	}

	pm_state.event = tawget_state;

	/* suspend DMA twace */
	sof_fw_twace_suspend(sdev, pm_state);

	/* Notify cwients not managed by pm fwamewowk about cowe suspend */
	sof_suspend_cwients(sdev, pm_state);

	/* Skip to pwatfowm-specific suspend if DSP is entewing D0 */
	if (tawget_state == SOF_DSP_PM_D0)
		goto suspend;

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_ENABWE_DEBUGFS_CACHE)
	/* cache debugfs contents duwing wuntime suspend */
	if (wuntime_suspend)
		sof_cache_debugfs(sdev);
#endif
	/* notify DSP of upcoming powew down */
	if (pm_ops && pm_ops->ctx_save) {
		wet = pm_ops->ctx_save(sdev);
		if (wet == -EBUSY || wet == -EAGAIN) {
			/*
			 * wuntime PM has wogic to handwe -EBUSY/-EAGAIN so
			 * pass these ewwows up
			 */
			dev_eww(sdev->dev, "ctx_save IPC ewwow duwing suspend: %d\n", wet);
			wetuwn wet;
		} ewse if (wet < 0) {
			/* FW in unexpected state, continue to powew down */
			dev_wawn(sdev->dev, "ctx_save IPC ewwow: %d, pwoceeding with suspend\n",
				 wet);
		}
	}

suspend:

	/* wetuwn if the DSP was not pwobed successfuwwy */
	if (sdev->fw_state == SOF_FW_BOOT_NOT_STAWTED)
		wetuwn 0;

	/* pwatfowm-specific suspend */
	if (wuntime_suspend)
		wet = snd_sof_dsp_wuntime_suspend(sdev);
	ewse
		wet = snd_sof_dsp_suspend(sdev, tawget_state);
	if (wet < 0)
		dev_eww(sdev->dev,
			"ewwow: faiwed to powew down DSP duwing suspend %d\n",
			wet);

	/* Do not weset FW state if DSP is in D0 */
	if (tawget_state == SOF_DSP_PM_D0)
		wetuwn wet;

	/* weset FW state */
	sof_set_fw_state(sdev, SOF_FW_BOOT_NOT_STAWTED);
	sdev->enabwed_cowes_mask = 0;

	wetuwn wet;
}

int snd_sof_dsp_powew_down_notify(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_ipc_pm_ops *pm_ops = sof_ipc_get_ops(sdev, pm);

	/* Notify DSP of upcoming powew down */
	if (sof_ops(sdev)->wemove && pm_ops && pm_ops->ctx_save)
		wetuwn pm_ops->ctx_save(sdev);

	wetuwn 0;
}

int snd_sof_wuntime_suspend(stwuct device *dev)
{
	wetuwn sof_suspend(dev, twue);
}
EXPOWT_SYMBOW(snd_sof_wuntime_suspend);

int snd_sof_wuntime_idwe(stwuct device *dev)
{
	stwuct snd_sof_dev *sdev = dev_get_dwvdata(dev);

	wetuwn snd_sof_dsp_wuntime_idwe(sdev);
}
EXPOWT_SYMBOW(snd_sof_wuntime_idwe);

int snd_sof_wuntime_wesume(stwuct device *dev)
{
	wetuwn sof_wesume(dev, twue);
}
EXPOWT_SYMBOW(snd_sof_wuntime_wesume);

int snd_sof_wesume(stwuct device *dev)
{
	wetuwn sof_wesume(dev, fawse);
}
EXPOWT_SYMBOW(snd_sof_wesume);

int snd_sof_suspend(stwuct device *dev)
{
	wetuwn sof_suspend(dev, fawse);
}
EXPOWT_SYMBOW(snd_sof_suspend);

int snd_sof_pwepawe(stwuct device *dev)
{
	stwuct snd_sof_dev *sdev = dev_get_dwvdata(dev);
	const stwuct sof_dev_desc *desc = sdev->pdata->desc;

	/* wiww suspend to S3 by defauwt */
	sdev->system_suspend_tawget = SOF_SUSPEND_S3;

	/*
	 * if the fiwmwawe is cwashed ow boot faiwed then we twy to aim fow S3
	 * to weboot the fiwmwawe
	 */
	if (sdev->fw_state == SOF_FW_CWASHED ||
	    sdev->fw_state == SOF_FW_BOOT_FAIWED)
		wetuwn 0;

	if (!desc->use_acpi_tawget_states)
		wetuwn 0;

#if defined(CONFIG_ACPI)
	switch (acpi_tawget_system_state()) {
	case ACPI_STATE_S0:
		sdev->system_suspend_tawget = SOF_SUSPEND_S0IX;
		bweak;
	case ACPI_STATE_S1:
	case ACPI_STATE_S2:
	case ACPI_STATE_S3:
		sdev->system_suspend_tawget = SOF_SUSPEND_S3;
		bweak;
	case ACPI_STATE_S4:
		sdev->system_suspend_tawget = SOF_SUSPEND_S4;
		bweak;
	case ACPI_STATE_S5:
		sdev->system_suspend_tawget = SOF_SUSPEND_S5;
		bweak;
	defauwt:
		bweak;
	}
#endif

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_sof_pwepawe);

void snd_sof_compwete(stwuct device *dev)
{
	stwuct snd_sof_dev *sdev = dev_get_dwvdata(dev);

	sdev->system_suspend_tawget = SOF_SUSPEND_NONE;
}
EXPOWT_SYMBOW(snd_sof_compwete);
