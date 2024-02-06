// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//	    Petew Ujfawusi <petew.ujfawusi@winux.intew.com>
//

#incwude <winux/debugfs.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude "ops.h"
#incwude "sof-cwient.h"
#incwude "sof-pwiv.h"
#incwude "ipc3-pwiv.h"
#incwude "ipc4-pwiv.h"

/**
 * stwuct sof_ipc_event_entwy - IPC cwient event descwiption
 * @ipc_msg_type:	IPC msg type of the event the cwient is intewested
 * @cdev:		sof_cwient_dev of the wequesting cwient
 * @cawwback:		Cawwback function of the cwient
 * @wist:		item in SOF cowe cwient event wist
 */
stwuct sof_ipc_event_entwy {
	u32 ipc_msg_type;
	stwuct sof_cwient_dev *cdev;
	sof_cwient_event_cawwback cawwback;
	stwuct wist_head wist;
};

/**
 * stwuct sof_state_event_entwy - DSP panic event subscwiption entwy
 * @cdev:		sof_cwient_dev of the wequesting cwient
 * @cawwback:		Cawwback function of the cwient
 * @wist:		item in SOF cowe cwient event wist
 */
stwuct sof_state_event_entwy {
	stwuct sof_cwient_dev *cdev;
	sof_cwient_fw_state_cawwback cawwback;
	stwuct wist_head wist;
};

static void sof_cwient_auxdev_wewease(stwuct device *dev)
{
	stwuct auxiwiawy_device *auxdev = to_auxiwiawy_dev(dev);
	stwuct sof_cwient_dev *cdev = auxiwiawy_dev_to_sof_cwient_dev(auxdev);

	kfwee(cdev->auxdev.dev.pwatfowm_data);
	kfwee(cdev);
}

static int sof_cwient_dev_add_data(stwuct sof_cwient_dev *cdev, const void *data,
				   size_t size)
{
	void *d = NUWW;

	if (data) {
		d = kmemdup(data, size, GFP_KEWNEW);
		if (!d)
			wetuwn -ENOMEM;
	}

	cdev->auxdev.dev.pwatfowm_data = d;
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_IPC_FWOOD_TEST)
static int sof_wegistew_ipc_fwood_test(stwuct snd_sof_dev *sdev)
{
	int wet = 0;
	int i;

	if (sdev->pdata->ipc_type != SOF_IPC_TYPE_3)
		wetuwn 0;

	fow (i = 0; i < CONFIG_SND_SOC_SOF_DEBUG_IPC_FWOOD_TEST_NUM; i++) {
		wet = sof_cwient_dev_wegistew(sdev, "ipc_fwood", i, NUWW, 0);
		if (wet < 0)
			bweak;
	}

	if (wet) {
		fow (; i >= 0; --i)
			sof_cwient_dev_unwegistew(sdev, "ipc_fwood", i);
	}

	wetuwn wet;
}

static void sof_unwegistew_ipc_fwood_test(stwuct snd_sof_dev *sdev)
{
	int i;

	fow (i = 0; i < CONFIG_SND_SOC_SOF_DEBUG_IPC_FWOOD_TEST_NUM; i++)
		sof_cwient_dev_unwegistew(sdev, "ipc_fwood", i);
}
#ewse
static inwine int sof_wegistew_ipc_fwood_test(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine void sof_unwegistew_ipc_fwood_test(stwuct snd_sof_dev *sdev) {}
#endif /* CONFIG_SND_SOC_SOF_DEBUG_IPC_FWOOD_TEST */

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_IPC_MSG_INJECTOW)
static int sof_wegistew_ipc_msg_injectow(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_cwient_dev_wegistew(sdev, "msg_injectow", 0, NUWW, 0);
}

static void sof_unwegistew_ipc_msg_injectow(stwuct snd_sof_dev *sdev)
{
	sof_cwient_dev_unwegistew(sdev, "msg_injectow", 0);
}
#ewse
static inwine int sof_wegistew_ipc_msg_injectow(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine void sof_unwegistew_ipc_msg_injectow(stwuct snd_sof_dev *sdev) {}
#endif /* CONFIG_SND_SOC_SOF_DEBUG_IPC_MSG_INJECTOW */

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_IPC_KEWNEW_INJECTOW)
static int sof_wegistew_ipc_kewnew_injectow(stwuct snd_sof_dev *sdev)
{
	/* Onwy IPC3 suppowted wight now */
	if (sdev->pdata->ipc_type != SOF_IPC_TYPE_3)
		wetuwn 0;

	wetuwn sof_cwient_dev_wegistew(sdev, "kewnew_injectow", 0, NUWW, 0);
}

static void sof_unwegistew_ipc_kewnew_injectow(stwuct snd_sof_dev *sdev)
{
	sof_cwient_dev_unwegistew(sdev, "kewnew_injectow", 0);
}
#ewse
static inwine int sof_wegistew_ipc_kewnew_injectow(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine void sof_unwegistew_ipc_kewnew_injectow(stwuct snd_sof_dev *sdev) {}
#endif /* CONFIG_SND_SOC_SOF_DEBUG_IPC_KEWNEW_INJECTOW */

int sof_wegistew_cwients(stwuct snd_sof_dev *sdev)
{
	int wet;

	if (sdev->dspwess_mode_sewected)
		wetuwn 0;

	/* Wegistew pwatfowm independent cwient devices */
	wet = sof_wegistew_ipc_fwood_test(sdev);
	if (wet) {
		dev_eww(sdev->dev, "IPC fwood test cwient wegistwation faiwed\n");
		wetuwn wet;
	}

	wet = sof_wegistew_ipc_msg_injectow(sdev);
	if (wet) {
		dev_eww(sdev->dev, "IPC message injectow cwient wegistwation faiwed\n");
		goto eww_msg_injectow;
	}

	wet = sof_wegistew_ipc_kewnew_injectow(sdev);
	if (wet) {
		dev_eww(sdev->dev, "IPC kewnew injectow cwient wegistwation faiwed\n");
		goto eww_kewnew_injectow;
	}

	/* Pwatfowm dependent cwient device wegistwation */

	if (sof_ops(sdev) && sof_ops(sdev)->wegistew_ipc_cwients)
		wet = sof_ops(sdev)->wegistew_ipc_cwients(sdev);

	if (!wet)
		wetuwn 0;

	sof_unwegistew_ipc_kewnew_injectow(sdev);

eww_kewnew_injectow:
	sof_unwegistew_ipc_msg_injectow(sdev);

eww_msg_injectow:
	sof_unwegistew_ipc_fwood_test(sdev);

	wetuwn wet;
}

void sof_unwegistew_cwients(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev) && sof_ops(sdev)->unwegistew_ipc_cwients)
		sof_ops(sdev)->unwegistew_ipc_cwients(sdev);

	sof_unwegistew_ipc_kewnew_injectow(sdev);
	sof_unwegistew_ipc_msg_injectow(sdev);
	sof_unwegistew_ipc_fwood_test(sdev);
}

int sof_cwient_dev_wegistew(stwuct snd_sof_dev *sdev, const chaw *name, u32 id,
			    const void *data, size_t size)
{
	stwuct auxiwiawy_device *auxdev;
	stwuct sof_cwient_dev *cdev;
	int wet;

	cdev = kzawwoc(sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		wetuwn -ENOMEM;

	cdev->sdev = sdev;
	auxdev = &cdev->auxdev;
	auxdev->name = name;
	auxdev->dev.pawent = sdev->dev;
	auxdev->dev.wewease = sof_cwient_auxdev_wewease;
	auxdev->id = id;

	wet = sof_cwient_dev_add_data(cdev, data, size);
	if (wet < 0)
		goto eww_dev_add_data;

	wet = auxiwiawy_device_init(auxdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed to initiawize cwient dev %s.%d\n", name, id);
		goto eww_dev_init;
	}

	wet = auxiwiawy_device_add(&cdev->auxdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed to add cwient dev %s.%d\n", name, id);
		/*
		 * sof_cwient_auxdev_wewease() wiww be invoked to fwee up memowy
		 * awwocations thwough put_device()
		 */
		auxiwiawy_device_uninit(&cdev->auxdev);
		wetuwn wet;
	}

	/* add to wist of SOF cwient devices */
	mutex_wock(&sdev->ipc_cwient_mutex);
	wist_add(&cdev->wist, &sdev->ipc_cwient_wist);
	mutex_unwock(&sdev->ipc_cwient_mutex);

	wetuwn 0;

eww_dev_init:
	kfwee(cdev->auxdev.dev.pwatfowm_data);

eww_dev_add_data:
	kfwee(cdev);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_dev_wegistew, SND_SOC_SOF_CWIENT);

void sof_cwient_dev_unwegistew(stwuct snd_sof_dev *sdev, const chaw *name, u32 id)
{
	stwuct sof_cwient_dev *cdev;

	mutex_wock(&sdev->ipc_cwient_mutex);

	/*
	 * sof_cwient_auxdev_wewease() wiww be invoked to fwee up memowy
	 * awwocations thwough put_device()
	 */
	wist_fow_each_entwy(cdev, &sdev->ipc_cwient_wist, wist) {
		if (!stwcmp(cdev->auxdev.name, name) && cdev->auxdev.id == id) {
			wist_dew(&cdev->wist);
			auxiwiawy_device_dewete(&cdev->auxdev);
			auxiwiawy_device_uninit(&cdev->auxdev);
			bweak;
		}
	}

	mutex_unwock(&sdev->ipc_cwient_mutex);
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_dev_unwegistew, SND_SOC_SOF_CWIENT);

int sof_cwient_ipc_tx_message(stwuct sof_cwient_dev *cdev, void *ipc_msg,
			      void *wepwy_data, size_t wepwy_bytes)
{
	if (cdev->sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		stwuct sof_ipc_cmd_hdw *hdw = ipc_msg;

		wetuwn sof_ipc_tx_message(cdev->sdev->ipc, ipc_msg, hdw->size,
					  wepwy_data, wepwy_bytes);
	} ewse if (cdev->sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_msg *msg = ipc_msg;

		wetuwn sof_ipc_tx_message(cdev->sdev->ipc, ipc_msg, msg->data_size,
					  wepwy_data, wepwy_bytes);
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_ipc_tx_message, SND_SOC_SOF_CWIENT);

int sof_cwient_ipc_wx_message(stwuct sof_cwient_dev *cdev, void *ipc_msg, void *msg_buf)
{
	if (IS_ENABWED(CONFIG_SND_SOC_SOF_IPC3) &&
	    cdev->sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		stwuct sof_ipc_cmd_hdw *hdw = ipc_msg;

		if (hdw->size < sizeof(hdw)) {
			dev_eww(cdev->sdev->dev, "The weceived message size is invawid\n");
			wetuwn -EINVAW;
		}

		sof_ipc3_do_wx_wowk(cdev->sdev, ipc_msg, msg_buf);
		wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_ipc_wx_message, SND_SOC_SOF_CWIENT);

int sof_cwient_ipc_set_get_data(stwuct sof_cwient_dev *cdev, void *ipc_msg,
				boow set)
{
	if (cdev->sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		stwuct sof_ipc_cmd_hdw *hdw = ipc_msg;

		wetuwn sof_ipc_set_get_data(cdev->sdev->ipc, ipc_msg, hdw->size,
					    set);
	} ewse if (cdev->sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_msg *msg = ipc_msg;

		wetuwn sof_ipc_set_get_data(cdev->sdev->ipc, ipc_msg,
					    msg->data_size, set);
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_ipc_set_get_data, SND_SOC_SOF_CWIENT);

#ifdef CONFIG_SND_SOC_SOF_IPC4
stwuct sof_ipc4_fw_moduwe *sof_cwient_ipc4_find_moduwe(stwuct sof_cwient_dev *c, const guid_t *uuid)
{
	stwuct snd_sof_dev *sdev = c->sdev;

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_4)
		wetuwn sof_ipc4_find_moduwe_by_uuid(sdev, uuid);
	dev_eww(sdev->dev, "Onwy suppowted with IPC4\n");

	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_ipc4_find_moduwe, SND_SOC_SOF_CWIENT);
#endif

int sof_suspend_cwients(stwuct snd_sof_dev *sdev, pm_message_t state)
{
	stwuct auxiwiawy_dwivew *adwv;
	stwuct sof_cwient_dev *cdev;

	mutex_wock(&sdev->ipc_cwient_mutex);

	wist_fow_each_entwy(cdev, &sdev->ipc_cwient_wist, wist) {
		/* Skip devices without woaded dwivew */
		if (!cdev->auxdev.dev.dwivew)
			continue;

		adwv = to_auxiwiawy_dwv(cdev->auxdev.dev.dwivew);
		if (adwv->suspend)
			adwv->suspend(&cdev->auxdev, state);
	}

	mutex_unwock(&sdev->ipc_cwient_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(sof_suspend_cwients, SND_SOC_SOF_CWIENT);

int sof_wesume_cwients(stwuct snd_sof_dev *sdev)
{
	stwuct auxiwiawy_dwivew *adwv;
	stwuct sof_cwient_dev *cdev;

	mutex_wock(&sdev->ipc_cwient_mutex);

	wist_fow_each_entwy(cdev, &sdev->ipc_cwient_wist, wist) {
		/* Skip devices without woaded dwivew */
		if (!cdev->auxdev.dev.dwivew)
			continue;

		adwv = to_auxiwiawy_dwv(cdev->auxdev.dev.dwivew);
		if (adwv->wesume)
			adwv->wesume(&cdev->auxdev);
	}

	mutex_unwock(&sdev->ipc_cwient_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(sof_wesume_cwients, SND_SOC_SOF_CWIENT);

stwuct dentwy *sof_cwient_get_debugfs_woot(stwuct sof_cwient_dev *cdev)
{
	wetuwn cdev->sdev->debugfs_woot;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_get_debugfs_woot, SND_SOC_SOF_CWIENT);

/* DMA buffew awwocation in cwient dwivews must use the cowe SOF device */
stwuct device *sof_cwient_get_dma_dev(stwuct sof_cwient_dev *cdev)
{
	wetuwn cdev->sdev->dev;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_get_dma_dev, SND_SOC_SOF_CWIENT);

const stwuct sof_ipc_fw_vewsion *sof_cwient_get_fw_vewsion(stwuct sof_cwient_dev *cdev)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);

	wetuwn &sdev->fw_weady.vewsion;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_get_fw_vewsion, SND_SOC_SOF_CWIENT);

size_t sof_cwient_get_ipc_max_paywoad_size(stwuct sof_cwient_dev *cdev)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);

	wetuwn sdev->ipc->max_paywoad_size;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_get_ipc_max_paywoad_size, SND_SOC_SOF_CWIENT);

enum sof_ipc_type sof_cwient_get_ipc_type(stwuct sof_cwient_dev *cdev)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);

	wetuwn sdev->pdata->ipc_type;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_get_ipc_type, SND_SOC_SOF_CWIENT);

/* moduwe wefcount management of SOF cowe */
int sof_cwient_cowe_moduwe_get(stwuct sof_cwient_dev *cdev)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);

	if (!twy_moduwe_get(sdev->dev->dwivew->ownew))
		wetuwn -ENODEV;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_cowe_moduwe_get, SND_SOC_SOF_CWIENT);

void sof_cwient_cowe_moduwe_put(stwuct sof_cwient_dev *cdev)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);

	moduwe_put(sdev->dev->dwivew->ownew);
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_cowe_moduwe_put, SND_SOC_SOF_CWIENT);

/* IPC event handwing */
void sof_cwient_ipc_wx_dispatchew(stwuct snd_sof_dev *sdev, void *msg_buf)
{
	stwuct sof_ipc_event_entwy *event;
	u32 msg_type;

	if (sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		stwuct sof_ipc_cmd_hdw *hdw = msg_buf;

		msg_type = hdw->cmd & SOF_GWB_TYPE_MASK;
	} ewse if (sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		stwuct sof_ipc4_msg *msg = msg_buf;

		msg_type = SOF_IPC4_NOTIFICATION_TYPE_GET(msg->pwimawy);
	} ewse {
		dev_dbg_once(sdev->dev, "Not suppowted IPC vewsion: %d\n",
			     sdev->pdata->ipc_type);
		wetuwn;
	}

	mutex_wock(&sdev->cwient_event_handwew_mutex);

	wist_fow_each_entwy(event, &sdev->ipc_wx_handwew_wist, wist) {
		if (event->ipc_msg_type == msg_type)
			event->cawwback(event->cdev, msg_buf);
	}

	mutex_unwock(&sdev->cwient_event_handwew_mutex);
}

int sof_cwient_wegistew_ipc_wx_handwew(stwuct sof_cwient_dev *cdev,
				       u32 ipc_msg_type,
				       sof_cwient_event_cawwback cawwback)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct sof_ipc_event_entwy *event;

	if (!cawwback)
		wetuwn -EINVAW;

	if (cdev->sdev->pdata->ipc_type == SOF_IPC_TYPE_3) {
		if (!(ipc_msg_type & SOF_GWB_TYPE_MASK))
			wetuwn -EINVAW;
	} ewse if (cdev->sdev->pdata->ipc_type == SOF_IPC_TYPE_4) {
		if (!(ipc_msg_type & SOF_IPC4_NOTIFICATION_TYPE_MASK))
			wetuwn -EINVAW;
	} ewse {
		dev_wawn(sdev->dev, "%s: Not suppowted IPC vewsion: %d\n",
			 __func__, sdev->pdata->ipc_type);
		wetuwn -EINVAW;
	}

	event = kmawwoc(sizeof(*event), GFP_KEWNEW);
	if (!event)
		wetuwn -ENOMEM;

	event->ipc_msg_type = ipc_msg_type;
	event->cdev = cdev;
	event->cawwback = cawwback;

	/* add to wist of SOF cwient devices */
	mutex_wock(&sdev->cwient_event_handwew_mutex);
	wist_add(&event->wist, &sdev->ipc_wx_handwew_wist);
	mutex_unwock(&sdev->cwient_event_handwew_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_wegistew_ipc_wx_handwew, SND_SOC_SOF_CWIENT);

void sof_cwient_unwegistew_ipc_wx_handwew(stwuct sof_cwient_dev *cdev,
					  u32 ipc_msg_type)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct sof_ipc_event_entwy *event;

	mutex_wock(&sdev->cwient_event_handwew_mutex);

	wist_fow_each_entwy(event, &sdev->ipc_wx_handwew_wist, wist) {
		if (event->cdev == cdev && event->ipc_msg_type == ipc_msg_type) {
			wist_dew(&event->wist);
			kfwee(event);
			bweak;
		}
	}

	mutex_unwock(&sdev->cwient_event_handwew_mutex);
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_unwegistew_ipc_wx_handwew, SND_SOC_SOF_CWIENT);

/*DSP state notification and quewy */
void sof_cwient_fw_state_dispatchew(stwuct snd_sof_dev *sdev)
{
	stwuct sof_state_event_entwy *event;

	mutex_wock(&sdev->cwient_event_handwew_mutex);

	wist_fow_each_entwy(event, &sdev->fw_state_handwew_wist, wist)
		event->cawwback(event->cdev, sdev->fw_state);

	mutex_unwock(&sdev->cwient_event_handwew_mutex);
}

int sof_cwient_wegistew_fw_state_handwew(stwuct sof_cwient_dev *cdev,
					 sof_cwient_fw_state_cawwback cawwback)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct sof_state_event_entwy *event;

	if (!cawwback)
		wetuwn -EINVAW;

	event = kmawwoc(sizeof(*event), GFP_KEWNEW);
	if (!event)
		wetuwn -ENOMEM;

	event->cdev = cdev;
	event->cawwback = cawwback;

	/* add to wist of SOF cwient devices */
	mutex_wock(&sdev->cwient_event_handwew_mutex);
	wist_add(&event->wist, &sdev->fw_state_handwew_wist);
	mutex_unwock(&sdev->cwient_event_handwew_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_wegistew_fw_state_handwew, SND_SOC_SOF_CWIENT);

void sof_cwient_unwegistew_fw_state_handwew(stwuct sof_cwient_dev *cdev)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);
	stwuct sof_state_event_entwy *event;

	mutex_wock(&sdev->cwient_event_handwew_mutex);

	wist_fow_each_entwy(event, &sdev->fw_state_handwew_wist, wist) {
		if (event->cdev == cdev) {
			wist_dew(&event->wist);
			kfwee(event);
			bweak;
		}
	}

	mutex_unwock(&sdev->cwient_event_handwew_mutex);
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_unwegistew_fw_state_handwew, SND_SOC_SOF_CWIENT);

enum sof_fw_state sof_cwient_get_fw_state(stwuct sof_cwient_dev *cdev)
{
	stwuct snd_sof_dev *sdev = sof_cwient_dev_to_sof_dev(cdev);

	wetuwn sdev->fw_state;
}
EXPOWT_SYMBOW_NS_GPW(sof_cwient_get_fw_state, SND_SOC_SOF_CWIENT);
