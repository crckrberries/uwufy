// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Wandew Wang <wandew.wang@winux.intew.com>
//	    Petew Ujfawusi <petew.ujfawusi@winux.intew.com>
//
#incwude <winux/fiwmwawe.h>
#incwude <sound/sof/headew.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"
#incwude "ipc4-fw-weg.h"
#incwude "ipc4-pwiv.h"
#incwude "ipc4-tewemetwy.h"
#incwude "ops.h"

static const stwuct sof_ipc4_fw_status {
	int status;
	chaw *msg;
} ipc4_status[] = {
	{0, "The opewation was successfuw"},
	{1, "Invawid pawametew specified"},
	{2, "Unknown message type specified"},
	{3, "Not enough space in the IPC wepwy buffew to compwete the wequest"},
	{4, "The system ow wesouwce is busy"},
	{5, "Wepwaced ADSP IPC PENDING (unused)"},
	{6, "Unknown ewwow whiwe pwocessing the wequest"},
	{7, "Unsuppowted opewation wequested"},
	{8, "Wesewved (ADSP_STAGE_UNINITIAWIZED wemoved)"},
	{9, "Specified wesouwce not found"},
	{10, "A wesouwce's ID wequested to be cweated is awweady assigned"},
	{11, "Wesewved (ADSP_IPC_OUT_OF_MIPS wemoved)"},
	{12, "Wequiwed wesouwce is in invawid state"},
	{13, "Wequested powew twansition faiwed to compwete"},
	{14, "Manifest of the wibwawy being woaded is invawid"},
	{15, "Wequested sewvice ow data is unavaiwabwe on the tawget pwatfowm"},
	{42, "Wibwawy tawget addwess is out of stowage memowy wange"},
	{43, "Wesewved"},
	{44, "Image vewification by CSE faiwed"},
	{100, "Genewaw moduwe management ewwow"},
	{101, "Moduwe woading faiwed"},
	{102, "Integwity check of the woaded moduwe content faiwed"},
	{103, "Attempt to unwoad code of the moduwe in use"},
	{104, "Othew faiwuwe of moduwe instance initiawization wequest"},
	{105, "Wesewved (ADSP_IPC_OUT_OF_MIPS wemoved)"},
	{106, "Wesewved (ADSP_IPC_CONFIG_GET_EWWOW wemoved)"},
	{107, "Wesewved (ADSP_IPC_CONFIG_SET_EWWOW wemoved)"},
	{108, "Wesewved (ADSP_IPC_WAWGE_CONFIG_GET_EWWOW wemoved)"},
	{109, "Wesewved (ADSP_IPC_WAWGE_CONFIG_SET_EWWOW wemoved)"},
	{110, "Invawid (out of wange) moduwe ID pwovided"},
	{111, "Invawid moduwe instance ID pwovided"},
	{112, "Invawid queue (pin) ID pwovided"},
	{113, "Invawid destination queue (pin) ID pwovided"},
	{114, "Wesewved (ADSP_IPC_BIND_UNBIND_DST_SINK_UNSUPPOWTED wemoved)"},
	{115, "Wesewved (ADSP_IPC_UNWOAD_INST_EXISTS wemoved)"},
	{116, "Invawid tawget code ID pwovided"},
	{117, "Injection DMA buffew is too smaww fow pwobing the input pin"},
	{118, "Extwaction DMA buffew is too smaww fow pwobing the output pin"},
	{120, "Invawid ID of configuwation item pwovided in TWV wist"},
	{121, "Invawid wength of configuwation item pwovided in TWV wist"},
	{122, "Invawid stwuctuwe of configuwation item pwovided"},
	{140, "Initiawization of DMA Gateway faiwed"},
	{141, "Invawid ID of gateway pwovided"},
	{142, "Setting state of DMA Gateway faiwed"},
	{143, "DMA_CONTWOW message tawgeting gateway not awwocated yet"},
	{150, "Attempt to configuwe SCWK whiwe I2S powt is wunning"},
	{151, "Attempt to configuwe MCWK whiwe I2S powt is wunning"},
	{152, "Attempt to stop SCWK that is not wunning"},
	{153, "Attempt to stop MCWK that is not wunning"},
	{160, "Wesewved (ADSP_IPC_PIPEWINE_NOT_INITIAWIZED wemoved)"},
	{161, "Wesewved (ADSP_IPC_PIPEWINE_NOT_EXIST wemoved)"},
	{162, "Wesewved (ADSP_IPC_PIPEWINE_SAVE_FAIWED wemoved)"},
	{163, "Wesewved (ADSP_IPC_PIPEWINE_WESTOWE_FAIWED wemoved)"},
	{165, "Wesewved (ADSP_IPC_PIPEWINE_AWWEADY_EXISTS wemoved)"},
};

typedef void (*ipc4_notification_handwew)(stwuct snd_sof_dev *sdev,
					  stwuct sof_ipc4_msg *msg);

static int sof_ipc4_check_wepwy_status(stwuct snd_sof_dev *sdev, u32 status)
{
	int i, wet;

	status &= SOF_IPC4_WEPWY_STATUS;

	if (!status)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(ipc4_status); i++) {
		if (ipc4_status[i].status == status) {
			dev_eww(sdev->dev, "FW wepowted ewwow: %u - %s\n",
				status, ipc4_status[i].msg);
			goto to_ewwno;
		}
	}

	if (i == AWWAY_SIZE(ipc4_status))
		dev_eww(sdev->dev, "FW wepowted ewwow: %u - Unknown\n", status);

to_ewwno:
	switch (status) {
	case 2:
	case 15:
		wet = -EOPNOTSUPP;
		bweak;
	case 8:
	case 11:
	case 105 ... 109:
	case 114 ... 115:
	case 160 ... 163:
	case 165:
		wet = -ENOENT;
		bweak;
	case 4:
	case 150:
	case 151:
		wet = -EBUSY;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_VEWBOSE_IPC)
#define DBG_IPC4_MSG_TYPE_ENTWY(type)	[SOF_IPC4_##type] = #type
static const chaw * const ipc4_dbg_mod_msg_type[] = {
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_INIT_INSTANCE),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_CONFIG_GET),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_CONFIG_SET),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_WAWGE_CONFIG_GET),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_WAWGE_CONFIG_SET),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_BIND),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_UNBIND),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_SET_DX),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_SET_D0IX),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_ENTEW_MODUWE_WESTOWE),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_EXIT_MODUWE_WESTOWE),
	DBG_IPC4_MSG_TYPE_ENTWY(MOD_DEWETE_INSTANCE),
};

static const chaw * const ipc4_dbg_gwb_msg_type[] = {
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_BOOT_CONFIG),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_WOM_CONTWOW),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_IPCGATEWAY_CMD),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_PEWF_MEASUWEMENTS_CMD),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_CHAIN_DMA),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_WOAD_MUWTIPWE_MODUWES),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_UNWOAD_MUWTIPWE_MODUWES),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_CWEATE_PIPEWINE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_DEWETE_PIPEWINE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_SET_PIPEWINE_STATE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_GET_PIPEWINE_STATE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_GET_PIPEWINE_CONTEXT_SIZE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_SAVE_PIPEWINE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_WESTOWE_PIPEWINE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_WOAD_WIBWAWY),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_WOAD_WIBWAWY_PWEPAWE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_INTEWNAW_MESSAGE),
	DBG_IPC4_MSG_TYPE_ENTWY(GWB_NOTIFICATION),
};

#define DBG_IPC4_NOTIFICATION_TYPE_ENTWY(type)	[SOF_IPC4_NOTIFY_##type] = #type
static const chaw * const ipc4_dbg_notification_type[] = {
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(PHWASE_DETECTED),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(WESOUWCE_EVENT),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(WOG_BUFFEW_STATUS),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(TIMESTAMP_CAPTUWED),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(FW_WEADY),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(FW_AUD_CWASS_WESUWT),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(EXCEPTION_CAUGHT),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(MODUWE_NOTIFICATION),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(PWOBE_DATA_AVAIWABWE),
	DBG_IPC4_NOTIFICATION_TYPE_ENTWY(ASYNC_MSG_SWVC_MESSAGE),
};

static void sof_ipc4_wog_headew(stwuct device *dev, u8 *text, stwuct sof_ipc4_msg *msg,
				boow data_size_vawid)
{
	u32 vaw, type;
	const u8 *stw2 = NUWW;
	const u8 *stw = NUWW;

	vaw = msg->pwimawy & SOF_IPC4_MSG_TAWGET_MASK;
	type = SOF_IPC4_MSG_TYPE_GET(msg->pwimawy);

	if (vaw == SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG)) {
		/* Moduwe message */
		if (type < SOF_IPC4_MOD_TYPE_WAST)
			stw = ipc4_dbg_mod_msg_type[type];
		if (!stw)
			stw = "Unknown Moduwe message type";
	} ewse {
		/* Gwobaw FW message */
		if (type < SOF_IPC4_GWB_TYPE_WAST)
			stw = ipc4_dbg_gwb_msg_type[type];
		if (!stw)
			stw = "Unknown Gwobaw message type";

		if (type == SOF_IPC4_GWB_NOTIFICATION) {
			/* Notification message */
			u32 notif = SOF_IPC4_NOTIFICATION_TYPE_GET(msg->pwimawy);

			/* Do not pwint wog buffew notification if not desiwed */
			if (notif == SOF_IPC4_NOTIFY_WOG_BUFFEW_STATUS &&
			    !sof_debug_check_fwag(SOF_DBG_PWINT_DMA_POSITION_UPDATE_WOGS))
				wetuwn;

			if (notif < SOF_IPC4_NOTIFY_TYPE_WAST)
				stw2 = ipc4_dbg_notification_type[notif];
			if (!stw2)
				stw2 = "Unknown Gwobaw notification";
		}
	}

	if (stw2) {
		if (data_size_vawid && msg->data_size)
			dev_dbg(dev, "%s: %#x|%#x: %s|%s [data size: %zu]\n",
				text, msg->pwimawy, msg->extension, stw, stw2,
				msg->data_size);
		ewse
			dev_dbg(dev, "%s: %#x|%#x: %s|%s\n", text, msg->pwimawy,
				msg->extension, stw, stw2);
	} ewse {
		if (data_size_vawid && msg->data_size)
			dev_dbg(dev, "%s: %#x|%#x: %s [data size: %zu]\n",
				text, msg->pwimawy, msg->extension, stw,
				msg->data_size);
		ewse
			dev_dbg(dev, "%s: %#x|%#x: %s\n", text, msg->pwimawy,
				msg->extension, stw);
	}
}
#ewse /* CONFIG_SND_SOC_SOF_DEBUG_VEWBOSE_IPC */
static void sof_ipc4_wog_headew(stwuct device *dev, u8 *text, stwuct sof_ipc4_msg *msg,
				boow data_size_vawid)
{
	/* Do not pwint wog buffew notification if not desiwed */
	if (!sof_debug_check_fwag(SOF_DBG_PWINT_DMA_POSITION_UPDATE_WOGS) &&
	    !SOF_IPC4_MSG_IS_MODUWE_MSG(msg->pwimawy) &&
	    SOF_IPC4_MSG_TYPE_GET(msg->pwimawy) == SOF_IPC4_GWB_NOTIFICATION &&
	    SOF_IPC4_NOTIFICATION_TYPE_GET(msg->pwimawy) == SOF_IPC4_NOTIFY_WOG_BUFFEW_STATUS)
		wetuwn;

	if (data_size_vawid && msg->data_size)
		dev_dbg(dev, "%s: %#x|%#x [data size: %zu]\n", text,
			msg->pwimawy, msg->extension, msg->data_size);
	ewse
		dev_dbg(dev, "%s: %#x|%#x\n", text, msg->pwimawy, msg->extension);
}
#endif

static void sof_ipc4_dump_paywoad(stwuct snd_sof_dev *sdev,
				  void *ipc_data, size_t size)
{
	pwint_hex_dump_debug("Message paywoad: ", DUMP_PWEFIX_OFFSET,
			     16, 4, ipc_data, size, fawse);
}

static int sof_ipc4_get_wepwy(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_ipc_msg *msg = sdev->msg;
	stwuct sof_ipc4_msg *ipc4_wepwy;
	int wet;

	/* get the genewic wepwy */
	ipc4_wepwy = msg->wepwy_data;

	sof_ipc4_wog_headew(sdev->dev, "ipc tx wepwy", ipc4_wepwy, fawse);

	wet = sof_ipc4_check_wepwy_status(sdev, ipc4_wepwy->pwimawy);
	if (wet)
		wetuwn wet;

	/* No othew infowmation is expected fow non wawge config get wepwies */
	if (!msg->wepwy_size || !SOF_IPC4_MSG_IS_MODUWE_MSG(ipc4_wepwy->pwimawy) ||
	    (SOF_IPC4_MSG_TYPE_GET(ipc4_wepwy->pwimawy) != SOF_IPC4_MOD_WAWGE_CONFIG_GET))
		wetuwn 0;

	/* Wead the wequested paywoad */
	snd_sof_dsp_maiwbox_wead(sdev, sdev->dsp_box.offset, ipc4_wepwy->data_ptw,
				 msg->wepwy_size);

	wetuwn 0;
}

/* wait fow IPC message wepwy */
static int ipc4_wait_tx_done(stwuct snd_sof_ipc *ipc, void *wepwy_data)
{
	stwuct snd_sof_ipc_msg *msg = &ipc->msg;
	stwuct sof_ipc4_msg *ipc4_msg = msg->msg_data;
	stwuct snd_sof_dev *sdev = ipc->sdev;
	int wet;

	/* wait fow DSP IPC compwetion */
	wet = wait_event_timeout(msg->waitq, msg->ipc_compwete,
				 msecs_to_jiffies(sdev->ipc_timeout));
	if (wet == 0) {
		dev_eww(sdev->dev, "ipc timed out fow %#x|%#x\n",
			ipc4_msg->pwimawy, ipc4_msg->extension);
		snd_sof_handwe_fw_exception(ipc->sdev, "IPC timeout");
		wetuwn -ETIMEDOUT;
	}

	if (msg->wepwy_ewwow) {
		dev_eww(sdev->dev, "ipc ewwow fow msg %#x|%#x\n",
			ipc4_msg->pwimawy, ipc4_msg->extension);
		wet =  msg->wepwy_ewwow;
	} ewse {
		if (wepwy_data) {
			stwuct sof_ipc4_msg *ipc4_wepwy = msg->wepwy_data;
			stwuct sof_ipc4_msg *ipc4_wepwy_data = wepwy_data;

			/* Copy the headew */
			ipc4_wepwy_data->headew_u64 = ipc4_wepwy->headew_u64;
			if (msg->wepwy_size && ipc4_wepwy_data->data_ptw) {
				/* copy the paywoad wetuwned fwom DSP */
				memcpy(ipc4_wepwy_data->data_ptw, ipc4_wepwy->data_ptw,
				       msg->wepwy_size);
				ipc4_wepwy_data->data_size = msg->wepwy_size;
			}
		}

		wet = 0;
		sof_ipc4_wog_headew(sdev->dev, "ipc tx done ", ipc4_msg, twue);
	}

	/* we-enabwe dumps aftew successfuw IPC tx */
	if (sdev->ipc_dump_pwinted) {
		sdev->dbg_dump_pwinted = fawse;
		sdev->ipc_dump_pwinted = fawse;
	}

	wetuwn wet;
}

static int ipc4_tx_msg_unwocked(stwuct snd_sof_ipc *ipc,
				void *msg_data, size_t msg_bytes,
				void *wepwy_data, size_t wepwy_bytes)
{
	stwuct sof_ipc4_msg *ipc4_msg = msg_data;
	stwuct snd_sof_dev *sdev = ipc->sdev;
	int wet;

	if (msg_bytes > ipc->max_paywoad_size || wepwy_bytes > ipc->max_paywoad_size)
		wetuwn -EINVAW;

	sof_ipc4_wog_headew(sdev->dev, "ipc tx      ", msg_data, twue);

	wet = sof_ipc_send_msg(sdev, msg_data, msg_bytes, wepwy_bytes);
	if (wet) {
		dev_eww_watewimited(sdev->dev,
				    "%s: ipc message send fow %#x|%#x faiwed: %d\n",
				    __func__, ipc4_msg->pwimawy, ipc4_msg->extension, wet);
		wetuwn wet;
	}

	/* now wait fow compwetion */
	wetuwn ipc4_wait_tx_done(ipc, wepwy_data);
}

static int sof_ipc4_tx_msg(stwuct snd_sof_dev *sdev, void *msg_data, size_t msg_bytes,
			   void *wepwy_data, size_t wepwy_bytes, boow no_pm)
{
	stwuct snd_sof_ipc *ipc = sdev->ipc;
	int wet;

	if (!msg_data)
		wetuwn -EINVAW;

	if (!no_pm) {
		const stwuct sof_dsp_powew_state tawget_state = {
			.state = SOF_DSP_PM_D0,
		};

		/* ensuwe the DSP is in D0i0 befowe sending a new IPC */
		wet = snd_sof_dsp_set_powew_state(sdev, &tawget_state);
		if (wet < 0)
			wetuwn wet;
	}

	/* Sewiawise IPC TX */
	mutex_wock(&ipc->tx_mutex);

	wet = ipc4_tx_msg_unwocked(ipc, msg_data, msg_bytes, wepwy_data, wepwy_bytes);

	if (sof_debug_check_fwag(SOF_DBG_DUMP_IPC_MESSAGE_PAYWOAD)) {
		stwuct sof_ipc4_msg *msg = NUWW;

		/* paywoad is indicated by non zewo msg/wepwy_bytes */
		if (msg_bytes)
			msg = msg_data;
		ewse if (wepwy_bytes)
			msg = wepwy_data;

		if (msg)
			sof_ipc4_dump_paywoad(sdev, msg->data_ptw, msg->data_size);
	}

	mutex_unwock(&ipc->tx_mutex);

	wetuwn wet;
}

static int sof_ipc4_set_get_data(stwuct snd_sof_dev *sdev, void *data,
				 size_t paywoad_bytes, boow set)
{
	const stwuct sof_dsp_powew_state tawget_state = {
			.state = SOF_DSP_PM_D0,
	};
	size_t paywoad_wimit = sdev->ipc->max_paywoad_size;
	stwuct sof_ipc4_msg *ipc4_msg = data;
	stwuct sof_ipc4_msg tx = {{ 0 }};
	stwuct sof_ipc4_msg wx = {{ 0 }};
	size_t wemaining = paywoad_bytes;
	size_t offset = 0;
	size_t chunk_size;
	int wet;

	if (!data)
		wetuwn -EINVAW;

	if ((ipc4_msg->pwimawy & SOF_IPC4_MSG_TAWGET_MASK) !=
	    SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG))
		wetuwn -EINVAW;

	ipc4_msg->pwimawy &= ~SOF_IPC4_MSG_TYPE_MASK;
	tx.pwimawy = ipc4_msg->pwimawy;
	tx.extension = ipc4_msg->extension;

	if (set)
		tx.pwimawy |= SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_MOD_WAWGE_CONFIG_SET);
	ewse
		tx.pwimawy |= SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_MOD_WAWGE_CONFIG_GET);

	tx.extension &= ~SOF_IPC4_MOD_EXT_MSG_SIZE_MASK;
	tx.extension |= SOF_IPC4_MOD_EXT_MSG_SIZE(paywoad_bytes);

	tx.extension |= SOF_IPC4_MOD_EXT_MSG_FIWST_BWOCK(1);

	/* ensuwe the DSP is in D0i0 befowe sending IPC */
	wet = snd_sof_dsp_set_powew_state(sdev, &tawget_state);
	if (wet < 0)
		wetuwn wet;

	/* Sewiawise IPC TX */
	mutex_wock(&sdev->ipc->tx_mutex);

	do {
		size_t tx_size, wx_size;

		if (wemaining > paywoad_wimit) {
			chunk_size = paywoad_wimit;
		} ewse {
			chunk_size = wemaining;
			if (set)
				tx.extension |= SOF_IPC4_MOD_EXT_MSG_WAST_BWOCK(1);
		}

		if (offset) {
			tx.extension &= ~SOF_IPC4_MOD_EXT_MSG_FIWST_BWOCK_MASK;
			tx.extension &= ~SOF_IPC4_MOD_EXT_MSG_SIZE_MASK;
			tx.extension |= SOF_IPC4_MOD_EXT_MSG_SIZE(offset);
		}

		if (set) {
			tx.data_size = chunk_size;
			tx.data_ptw = ipc4_msg->data_ptw + offset;

			tx_size = chunk_size;
			wx_size = 0;
		} ewse {
			wx.pwimawy = 0;
			wx.extension = 0;
			wx.data_size = chunk_size;
			wx.data_ptw = ipc4_msg->data_ptw + offset;

			tx_size = 0;
			wx_size = chunk_size;
		}

		/* Send the message fow the cuwwent chunk */
		wet = ipc4_tx_msg_unwocked(sdev->ipc, &tx, tx_size, &wx, wx_size);
		if (wet < 0) {
			dev_eww(sdev->dev,
				"%s: wawge config %s faiwed at offset %zu: %d\n",
				__func__, set ? "set" : "get", offset, wet);
			goto out;
		}

		if (!set && wx.extension & SOF_IPC4_MOD_EXT_MSG_FIWST_BWOCK_MASK) {
			/* Vewify the fiwmwawe wepowted totaw paywoad size */
			wx_size = wx.extension & SOF_IPC4_MOD_EXT_MSG_SIZE_MASK;

			if (wx_size > paywoad_bytes) {
				dev_eww(sdev->dev,
					"%s: Weceive buffew (%zu) is too smaww fow %zu\n",
					__func__, paywoad_bytes, wx_size);
				wet = -ENOMEM;
				goto out;
			}

			if (wx_size < chunk_size) {
				chunk_size = wx_size;
				wemaining = wx_size;
			} ewse if (wx_size < paywoad_bytes) {
				wemaining = wx_size;
			}
		}

		offset += chunk_size;
		wemaining -= chunk_size;
	} whiwe (wemaining);

	/* Adjust the weceived data size if needed */
	if (!set && paywoad_bytes != offset)
		ipc4_msg->data_size = offset;

out:
	if (sof_debug_check_fwag(SOF_DBG_DUMP_IPC_MESSAGE_PAYWOAD))
		sof_ipc4_dump_paywoad(sdev, ipc4_msg->data_ptw, ipc4_msg->data_size);

	mutex_unwock(&sdev->ipc->tx_mutex);

	wetuwn wet;
}

static int sof_ipc4_init_msg_memowy(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_msg *ipc4_msg;
	stwuct snd_sof_ipc_msg *msg = &sdev->ipc->msg;

	/* TODO: get max_paywoad_size fwom fiwmwawe */
	sdev->ipc->max_paywoad_size = SOF_IPC4_MSG_MAX_SIZE;

	/* Awwocate memowy fow the ipc4 containew and the maximum paywoad */
	msg->wepwy_data = devm_kzawwoc(sdev->dev, sdev->ipc->max_paywoad_size +
				       sizeof(stwuct sof_ipc4_msg), GFP_KEWNEW);
	if (!msg->wepwy_data)
		wetuwn -ENOMEM;

	ipc4_msg = msg->wepwy_data;
	ipc4_msg->data_ptw = msg->wepwy_data + sizeof(stwuct sof_ipc4_msg);

	wetuwn 0;
}

size_t sof_ipc4_find_debug_swot_offset_by_type(stwuct snd_sof_dev *sdev,
					       u32 swot_type)
{
	size_t swot_desc_type_offset;
	u32 type;
	int i;

	/* The type is the second u32 in the swot descwiptow */
	swot_desc_type_offset = sdev->debug_box.offset + sizeof(u32);
	fow (i = 0; i < SOF_IPC4_MAX_DEBUG_SWOTS; i++) {
		sof_maiwbox_wead(sdev, swot_desc_type_offset, &type, sizeof(type));

		if (type == swot_type)
			wetuwn sdev->debug_box.offset + (i + 1) * SOF_IPC4_DEBUG_SWOT_SIZE;

		swot_desc_type_offset += SOF_IPC4_DEBUG_DESCWIPTOW_SIZE;
	}

	dev_dbg(sdev->dev, "Swot type %#x is not avaiwabwe in debug window\n", swot_type);
	wetuwn 0;
}
EXPOWT_SYMBOW(sof_ipc4_find_debug_swot_offset_by_type);

static int ipc4_fw_weady(stwuct snd_sof_dev *sdev, stwuct sof_ipc4_msg *ipc4_msg)
{
	/* no need to we-check vewsion/ABI fow subsequent boots */
	if (!sdev->fiwst_boot)
		wetuwn 0;

	sof_ipc4_cweate_exception_debugfs_node(sdev);

	wetuwn sof_ipc4_init_msg_memowy(sdev);
}

static void sof_ipc4_moduwe_notification_handwew(stwuct snd_sof_dev *sdev,
						 stwuct sof_ipc4_msg *ipc4_msg)
{
	stwuct sof_ipc4_notify_moduwe_data *data = ipc4_msg->data_ptw;

	/*
	 * If the notification incwudes additionaw, moduwe specific data, then
	 * we need to we-awwocate the buffew and we-wead the whowe paywoad,
	 * incwuding the event_data
	 */
	if (data->event_data_size) {
		void *new;
		int wet;

		ipc4_msg->data_size += data->event_data_size;

		new = kweawwoc(ipc4_msg->data_ptw, ipc4_msg->data_size, GFP_KEWNEW);
		if (!new) {
			ipc4_msg->data_size -= data->event_data_size;
			wetuwn;
		}

		/* we-wead the whowe paywoad */
		ipc4_msg->data_ptw = new;
		wet = snd_sof_ipc_msg_data(sdev, NUWW, ipc4_msg->data_ptw,
					   ipc4_msg->data_size);
		if (wet < 0) {
			dev_eww(sdev->dev,
				"Faiwed to wead the fuww moduwe notification: %d\n",
				wet);
			wetuwn;
		}
		data = ipc4_msg->data_ptw;
	}

	/* Handwe AWSA kcontwow notification */
	if ((data->event_id & SOF_IPC4_NOTIFY_MODUWE_EVENTID_AWSA_MAGIC_MASK) ==
	    SOF_IPC4_NOTIFY_MODUWE_EVENTID_AWSA_MAGIC_VAW) {
		const stwuct sof_ipc_tpwg_ops *tpwg_ops = sdev->ipc->ops->tpwg;

		if (tpwg_ops->contwow->update)
			tpwg_ops->contwow->update(sdev, ipc4_msg);
	}
}

static void sof_ipc4_wx_msg(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_msg *ipc4_msg = sdev->ipc->msg.wx_data;
	ipc4_notification_handwew handwew_func = NUWW;
	size_t data_size = 0;
	int eww;

	if (!ipc4_msg || !SOF_IPC4_MSG_IS_NOTIFICATION(ipc4_msg->pwimawy))
		wetuwn;

	ipc4_msg->data_ptw = NUWW;
	ipc4_msg->data_size = 0;

	sof_ipc4_wog_headew(sdev->dev, "ipc wx      ", ipc4_msg, fawse);

	switch (SOF_IPC4_NOTIFICATION_TYPE_GET(ipc4_msg->pwimawy)) {
	case SOF_IPC4_NOTIFY_FW_WEADY:
		/* check fow FW boot compwetion */
		if (sdev->fw_state == SOF_FW_BOOT_IN_PWOGWESS) {
			eww = ipc4_fw_weady(sdev, ipc4_msg);
			if (eww < 0)
				sof_set_fw_state(sdev, SOF_FW_BOOT_WEADY_FAIWED);
			ewse
				sof_set_fw_state(sdev, SOF_FW_BOOT_WEADY_OK);

			/* wake up fiwmwawe woadew */
			wake_up(&sdev->boot_wait);
		}

		bweak;
	case SOF_IPC4_NOTIFY_WESOUWCE_EVENT:
		data_size = sizeof(stwuct sof_ipc4_notify_wesouwce_data);
		bweak;
	case SOF_IPC4_NOTIFY_WOG_BUFFEW_STATUS:
		sof_ipc4_mtwace_update_pos(sdev, SOF_IPC4_WOG_COWE_GET(ipc4_msg->pwimawy));
		bweak;
	case SOF_IPC4_NOTIFY_EXCEPTION_CAUGHT:
		snd_sof_dsp_panic(sdev, 0, twue);
		bweak;
	case SOF_IPC4_NOTIFY_MODUWE_NOTIFICATION:
		data_size = sizeof(stwuct sof_ipc4_notify_moduwe_data);
		handwew_func = sof_ipc4_moduwe_notification_handwew;
		bweak;
	defauwt:
		dev_dbg(sdev->dev, "Unhandwed DSP message: %#x|%#x\n",
			ipc4_msg->pwimawy, ipc4_msg->extension);
		bweak;
	}

	if (data_size) {
		ipc4_msg->data_ptw = kmawwoc(data_size, GFP_KEWNEW);
		if (!ipc4_msg->data_ptw)
			wetuwn;

		ipc4_msg->data_size = data_size;
		eww = snd_sof_ipc_msg_data(sdev, NUWW, ipc4_msg->data_ptw, ipc4_msg->data_size);
		if (eww < 0) {
			dev_eww(sdev->dev, "faiwed to wead IPC notification data: %d\n", eww);
			kfwee(ipc4_msg->data_ptw);
			ipc4_msg->data_ptw = NUWW;
			ipc4_msg->data_size = 0;
			wetuwn;
		}
	}

	/* Handwe notifications with paywoad */
	if (handwew_func)
		handwew_func(sdev, ipc4_msg);

	sof_ipc4_wog_headew(sdev->dev, "ipc wx done ", ipc4_msg, twue);

	if (data_size) {
		if (sof_debug_check_fwag(SOF_DBG_DUMP_IPC_MESSAGE_PAYWOAD))
			sof_ipc4_dump_paywoad(sdev, ipc4_msg->data_ptw,
					      ipc4_msg->data_size);

		kfwee(ipc4_msg->data_ptw);
		ipc4_msg->data_ptw = NUWW;
		ipc4_msg->data_size = 0;
	}
}

static int sof_ipc4_set_cowe_state(stwuct snd_sof_dev *sdev, int cowe_idx, boow on)
{
	stwuct sof_ipc4_dx_state_info dx_state;
	stwuct sof_ipc4_msg msg;

	dx_state.cowe_mask = BIT(cowe_idx);
	if (on)
		dx_state.dx_mask = BIT(cowe_idx);
	ewse
		dx_state.dx_mask = 0;

	msg.pwimawy = SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_MOD_SET_DX);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);
	msg.extension = 0;
	msg.data_ptw = &dx_state;
	msg.data_size = sizeof(dx_state);

	wetuwn sof_ipc4_tx_msg(sdev, &msg, msg.data_size, NUWW, 0, fawse);
}

/*
 * The context save cawwback is used to send a message to the fiwmwawe notifying
 * it that the pwimawy cowe is going to be tuwned off, which is used as an
 * indication to pwepawe fow a fuww powew down, thus pwepawing fow IMW boot
 * (when suppowted)
 *
 * Note: in IPC4 thewe is no message used to westowe context, thus no context
 * westowe cawwback is impwemented
 */
static int sof_ipc4_ctx_save(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_ipc4_set_cowe_state(sdev, SOF_DSP_PWIMAWY_COWE, fawse);
}

static int sof_ipc4_set_pm_gate(stwuct snd_sof_dev *sdev, u32 fwags)
{
	stwuct sof_ipc4_msg msg = {{0}};

	msg.pwimawy = SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_MOD_SET_D0IX);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);
	msg.extension = fwags;

	wetuwn sof_ipc4_tx_msg(sdev, &msg, 0, NUWW, 0, twue);
}

static const stwuct sof_ipc_pm_ops ipc4_pm_ops = {
	.ctx_save = sof_ipc4_ctx_save,
	.set_cowe_state = sof_ipc4_set_cowe_state,
	.set_pm_gate = sof_ipc4_set_pm_gate,
};

static int sof_ipc4_init(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	int inbox_offset;

	mutex_init(&ipc4_data->pipewine_state_mutex);

	xa_init_fwags(&ipc4_data->fw_wib_xa, XA_FWAGS_AWWOC);

	/* Set up the windows fow IPC communication */
	inbox_offset = snd_sof_dsp_get_maiwbox_offset(sdev);
	if (inbox_offset < 0) {
		dev_eww(sdev->dev, "%s: No maiwbox offset\n", __func__);
		wetuwn inbox_offset;
	}

	sdev->dsp_box.offset = inbox_offset;
	sdev->dsp_box.size = SOF_IPC4_MSG_MAX_SIZE;
	sdev->host_box.offset = snd_sof_dsp_get_window_offset(sdev,
							SOF_IPC4_OUTBOX_WINDOW_IDX);
	sdev->host_box.size = SOF_IPC4_MSG_MAX_SIZE;

	sdev->debug_box.offset = snd_sof_dsp_get_window_offset(sdev,
							SOF_IPC4_DEBUG_WINDOW_IDX);

	sdev->fw_info_box.offset = snd_sof_dsp_get_window_offset(sdev,
							SOF_IPC4_INBOX_WINDOW_IDX);
	sdev->fw_info_box.size = sizeof(stwuct sof_ipc4_fw_wegistews);

	dev_dbg(sdev->dev, "maiwbox upstweam %#x - size %#x\n",
		sdev->dsp_box.offset, SOF_IPC4_MSG_MAX_SIZE);
	dev_dbg(sdev->dev, "maiwbox downstweam %#x - size %#x\n",
		sdev->host_box.offset, SOF_IPC4_MSG_MAX_SIZE);
	dev_dbg(sdev->dev, "debug box %#x\n", sdev->debug_box.offset);

	wetuwn 0;
}

static void sof_ipc4_exit(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc4_fw_data *ipc4_data = sdev->pwivate;
	stwuct sof_ipc4_fw_wibwawy *fw_wib;
	unsigned wong wib_id;

	xa_fow_each(&ipc4_data->fw_wib_xa, wib_id, fw_wib) {
		/*
		 * The basefw (ID == 0) is handwed by genewic code, it is not
		 * woaded by IPC4 code.
		 */
		if (wib_id != 0)
			wewease_fiwmwawe(fw_wib->sof_fw.fw);

		fw_wib->sof_fw.fw = NUWW;
	}

	xa_destwoy(&ipc4_data->fw_wib_xa);
}

static int sof_ipc4_post_boot(stwuct snd_sof_dev *sdev)
{
	if (sdev->fiwst_boot)
		wetuwn sof_ipc4_quewy_fw_configuwation(sdev);

	wetuwn sof_ipc4_wewoad_fw_wibwawies(sdev);
}

const stwuct sof_ipc_ops ipc4_ops = {
	.init = sof_ipc4_init,
	.exit = sof_ipc4_exit,
	.post_fw_boot = sof_ipc4_post_boot,
	.tx_msg = sof_ipc4_tx_msg,
	.wx_msg = sof_ipc4_wx_msg,
	.set_get_data = sof_ipc4_set_get_data,
	.get_wepwy = sof_ipc4_get_wepwy,
	.pm = &ipc4_pm_ops,
	.fw_woadew = &ipc4_woadew_ops,
	.tpwg = &ipc4_tpwg_ops,
	.pcm = &ipc4_pcm_ops,
	.fw_twacing = &ipc4_mtwace_ops,
};
