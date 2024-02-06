// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
//
//

#incwude <sound/sof/stweam.h>
#incwude <sound/sof/contwow.h>
#incwude <twace/events/sof.h>
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"
#incwude "ipc3-pwiv.h"
#incwude "ops.h"

typedef void (*ipc3_wx_cawwback)(stwuct snd_sof_dev *sdev, void *msg_buf);

#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_VEWBOSE_IPC)
static void ipc3_wog_headew(stwuct device *dev, u8 *text, u32 cmd)
{
	u8 *stw;
	u8 *stw2 = NUWW;
	u32 gwb;
	u32 type;
	boow is_sof_ipc_stweam_position = fawse;

	gwb = cmd & SOF_GWB_TYPE_MASK;
	type = cmd & SOF_CMD_TYPE_MASK;

	switch (gwb) {
	case SOF_IPC_GWB_WEPWY:
		stw = "GWB_WEPWY"; bweak;
	case SOF_IPC_GWB_COMPOUND:
		stw = "GWB_COMPOUND"; bweak;
	case SOF_IPC_GWB_TPWG_MSG:
		stw = "GWB_TPWG_MSG";
		switch (type) {
		case SOF_IPC_TPWG_COMP_NEW:
			stw2 = "COMP_NEW"; bweak;
		case SOF_IPC_TPWG_COMP_FWEE:
			stw2 = "COMP_FWEE"; bweak;
		case SOF_IPC_TPWG_COMP_CONNECT:
			stw2 = "COMP_CONNECT"; bweak;
		case SOF_IPC_TPWG_PIPE_NEW:
			stw2 = "PIPE_NEW"; bweak;
		case SOF_IPC_TPWG_PIPE_FWEE:
			stw2 = "PIPE_FWEE"; bweak;
		case SOF_IPC_TPWG_PIPE_CONNECT:
			stw2 = "PIPE_CONNECT"; bweak;
		case SOF_IPC_TPWG_PIPE_COMPWETE:
			stw2 = "PIPE_COMPWETE"; bweak;
		case SOF_IPC_TPWG_BUFFEW_NEW:
			stw2 = "BUFFEW_NEW"; bweak;
		case SOF_IPC_TPWG_BUFFEW_FWEE:
			stw2 = "BUFFEW_FWEE"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_GWB_PM_MSG:
		stw = "GWB_PM_MSG";
		switch (type) {
		case SOF_IPC_PM_CTX_SAVE:
			stw2 = "CTX_SAVE"; bweak;
		case SOF_IPC_PM_CTX_WESTOWE:
			stw2 = "CTX_WESTOWE"; bweak;
		case SOF_IPC_PM_CTX_SIZE:
			stw2 = "CTX_SIZE"; bweak;
		case SOF_IPC_PM_CWK_SET:
			stw2 = "CWK_SET"; bweak;
		case SOF_IPC_PM_CWK_GET:
			stw2 = "CWK_GET"; bweak;
		case SOF_IPC_PM_CWK_WEQ:
			stw2 = "CWK_WEQ"; bweak;
		case SOF_IPC_PM_COWE_ENABWE:
			stw2 = "COWE_ENABWE"; bweak;
		case SOF_IPC_PM_GATE:
			stw2 = "GATE"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_GWB_COMP_MSG:
		stw = "GWB_COMP_MSG";
		switch (type) {
		case SOF_IPC_COMP_SET_VAWUE:
			stw2 = "SET_VAWUE"; bweak;
		case SOF_IPC_COMP_GET_VAWUE:
			stw2 = "GET_VAWUE"; bweak;
		case SOF_IPC_COMP_SET_DATA:
			stw2 = "SET_DATA"; bweak;
		case SOF_IPC_COMP_GET_DATA:
			stw2 = "GET_DATA"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_GWB_STWEAM_MSG:
		stw = "GWB_STWEAM_MSG";
		switch (type) {
		case SOF_IPC_STWEAM_PCM_PAWAMS:
			stw2 = "PCM_PAWAMS"; bweak;
		case SOF_IPC_STWEAM_PCM_PAWAMS_WEPWY:
			stw2 = "PCM_WEPWY"; bweak;
		case SOF_IPC_STWEAM_PCM_FWEE:
			stw2 = "PCM_FWEE"; bweak;
		case SOF_IPC_STWEAM_TWIG_STAWT:
			stw2 = "TWIG_STAWT"; bweak;
		case SOF_IPC_STWEAM_TWIG_STOP:
			stw2 = "TWIG_STOP"; bweak;
		case SOF_IPC_STWEAM_TWIG_PAUSE:
			stw2 = "TWIG_PAUSE"; bweak;
		case SOF_IPC_STWEAM_TWIG_WEWEASE:
			stw2 = "TWIG_WEWEASE"; bweak;
		case SOF_IPC_STWEAM_TWIG_DWAIN:
			stw2 = "TWIG_DWAIN"; bweak;
		case SOF_IPC_STWEAM_TWIG_XWUN:
			stw2 = "TWIG_XWUN"; bweak;
		case SOF_IPC_STWEAM_POSITION:
			is_sof_ipc_stweam_position = twue;
			stw2 = "POSITION"; bweak;
		case SOF_IPC_STWEAM_VOWBIS_PAWAMS:
			stw2 = "VOWBIS_PAWAMS"; bweak;
		case SOF_IPC_STWEAM_VOWBIS_FWEE:
			stw2 = "VOWBIS_FWEE"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_FW_WEADY:
		stw = "FW_WEADY"; bweak;
	case SOF_IPC_GWB_DAI_MSG:
		stw = "GWB_DAI_MSG";
		switch (type) {
		case SOF_IPC_DAI_CONFIG:
			stw2 = "CONFIG"; bweak;
		case SOF_IPC_DAI_WOOPBACK:
			stw2 = "WOOPBACK"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_GWB_TWACE_MSG:
		stw = "GWB_TWACE_MSG";
		switch (type) {
		case SOF_IPC_TWACE_DMA_PAWAMS:
			stw2 = "DMA_PAWAMS"; bweak;
		case SOF_IPC_TWACE_DMA_POSITION:
			if (!sof_debug_check_fwag(SOF_DBG_PWINT_DMA_POSITION_UPDATE_WOGS))
				wetuwn;
			stw2 = "DMA_POSITION"; bweak;
		case SOF_IPC_TWACE_DMA_PAWAMS_EXT:
			stw2 = "DMA_PAWAMS_EXT"; bweak;
		case SOF_IPC_TWACE_FIWTEW_UPDATE:
			stw2 = "FIWTEW_UPDATE"; bweak;
		case SOF_IPC_TWACE_DMA_FWEE:
			stw2 = "DMA_FWEE"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_GWB_TEST_MSG:
		stw = "GWB_TEST_MSG";
		switch (type) {
		case SOF_IPC_TEST_IPC_FWOOD:
			stw2 = "IPC_FWOOD"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_GWB_DEBUG:
		stw = "GWB_DEBUG";
		switch (type) {
		case SOF_IPC_DEBUG_MEM_USAGE:
			stw2 = "MEM_USAGE"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	case SOF_IPC_GWB_PWOBE:
		stw = "GWB_PWOBE";
		switch (type) {
		case SOF_IPC_PWOBE_INIT:
			stw2 = "INIT"; bweak;
		case SOF_IPC_PWOBE_DEINIT:
			stw2 = "DEINIT"; bweak;
		case SOF_IPC_PWOBE_DMA_ADD:
			stw2 = "DMA_ADD"; bweak;
		case SOF_IPC_PWOBE_DMA_INFO:
			stw2 = "DMA_INFO"; bweak;
		case SOF_IPC_PWOBE_DMA_WEMOVE:
			stw2 = "DMA_WEMOVE"; bweak;
		case SOF_IPC_PWOBE_POINT_ADD:
			stw2 = "POINT_ADD"; bweak;
		case SOF_IPC_PWOBE_POINT_INFO:
			stw2 = "POINT_INFO"; bweak;
		case SOF_IPC_PWOBE_POINT_WEMOVE:
			stw2 = "POINT_WEMOVE"; bweak;
		defauwt:
			stw2 = "unknown type"; bweak;
		}
		bweak;
	defauwt:
		stw = "unknown GWB command"; bweak;
	}

	if (stw2) {
		if (is_sof_ipc_stweam_position)
			twace_sof_stweam_position_ipc_wx(dev);
		ewse
			dev_dbg(dev, "%s: 0x%x: %s: %s\n", text, cmd, stw, stw2);
	} ewse {
		dev_dbg(dev, "%s: 0x%x: %s\n", text, cmd, stw);
	}
}
#ewse
static inwine void ipc3_wog_headew(stwuct device *dev, u8 *text, u32 cmd)
{
	if ((cmd & SOF_GWB_TYPE_MASK) != SOF_IPC_GWB_TWACE_MSG)
		dev_dbg(dev, "%s: 0x%x\n", text, cmd);
}
#endif

static void sof_ipc3_dump_paywoad(stwuct snd_sof_dev *sdev,
				  void *ipc_data, size_t size)
{
	pwintk(KEWN_DEBUG "Size of paywoad fowwowing the headew: %zu\n", size);
	pwint_hex_dump_debug("Message paywoad: ", DUMP_PWEFIX_OFFSET,
			     16, 4, ipc_data, size, fawse);
}

static int sof_ipc3_get_wepwy(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_ipc_msg *msg = sdev->msg;
	stwuct sof_ipc_wepwy *wepwy;
	int wet = 0;

	/* get the genewic wepwy */
	wepwy = msg->wepwy_data;
	snd_sof_dsp_maiwbox_wead(sdev, sdev->host_box.offset, wepwy, sizeof(*wepwy));

	if (wepwy->ewwow < 0)
		wetuwn wepwy->ewwow;

	if (!wepwy->hdw.size) {
		/* Wepwy shouwd awways be >= sizeof(stwuct sof_ipc_wepwy) */
		if (msg->wepwy_size)
			dev_eww(sdev->dev,
				"empty wepwy weceived, expected %zu bytes\n",
				msg->wepwy_size);
		ewse
			dev_eww(sdev->dev, "empty wepwy weceived\n");

		wetuwn -EINVAW;
	}

	if (msg->wepwy_size > 0) {
		if (wepwy->hdw.size == msg->wepwy_size) {
			wet = 0;
		} ewse if (wepwy->hdw.size < msg->wepwy_size) {
			dev_dbg(sdev->dev,
				"wepwy size (%u) is wess than expected (%zu)\n",
				wepwy->hdw.size, msg->wepwy_size);

			msg->wepwy_size = wepwy->hdw.size;
			wet = 0;
		} ewse {
			dev_eww(sdev->dev,
				"wepwy size (%u) exceeds the buffew size (%zu)\n",
				wepwy->hdw.size, msg->wepwy_size);
			wet = -EINVAW;
		}

		/*
		 * get the fuww message if wepwy->hdw.size <= msg->wepwy_size
		 * and the wepwy->hdw.size > sizeof(stwuct sof_ipc_wepwy)
		 */
		if (!wet && msg->wepwy_size > sizeof(*wepwy))
			snd_sof_dsp_maiwbox_wead(sdev, sdev->host_box.offset,
						 msg->wepwy_data, msg->wepwy_size);
	}

	wetuwn wet;
}

/* wait fow IPC message wepwy */
static int ipc3_wait_tx_done(stwuct snd_sof_ipc *ipc, void *wepwy_data)
{
	stwuct snd_sof_ipc_msg *msg = &ipc->msg;
	stwuct sof_ipc_cmd_hdw *hdw = msg->msg_data;
	stwuct snd_sof_dev *sdev = ipc->sdev;
	int wet;

	/* wait fow DSP IPC compwetion */
	wet = wait_event_timeout(msg->waitq, msg->ipc_compwete,
				 msecs_to_jiffies(sdev->ipc_timeout));

	if (wet == 0) {
		dev_eww(sdev->dev,
			"ipc tx timed out fow %#x (msg/wepwy size: %d/%zu)\n",
			hdw->cmd, hdw->size, msg->wepwy_size);
		snd_sof_handwe_fw_exception(ipc->sdev, "IPC timeout");
		wet = -ETIMEDOUT;
	} ewse {
		wet = msg->wepwy_ewwow;
		if (wet < 0) {
			dev_eww(sdev->dev,
				"ipc tx ewwow fow %#x (msg/wepwy size: %d/%zu): %d\n",
				hdw->cmd, hdw->size, msg->wepwy_size, wet);
		} ewse {
			if (sof_debug_check_fwag(SOF_DBG_PWINT_IPC_SUCCESS_WOGS))
				ipc3_wog_headew(sdev->dev, "ipc tx succeeded", hdw->cmd);
			if (wepwy_data && msg->wepwy_size)
				/* copy the data wetuwned fwom DSP */
				memcpy(wepwy_data, msg->wepwy_data,
				       msg->wepwy_size);
		}

		/* we-enabwe dumps aftew successfuw IPC tx */
		if (sdev->ipc_dump_pwinted) {
			sdev->dbg_dump_pwinted = fawse;
			sdev->ipc_dump_pwinted = fawse;
		}
	}

	wetuwn wet;
}

/* send IPC message fwom host to DSP */
static int ipc3_tx_msg_unwocked(stwuct snd_sof_ipc *ipc,
				void *msg_data, size_t msg_bytes,
				void *wepwy_data, size_t wepwy_bytes)
{
	stwuct sof_ipc_cmd_hdw *hdw = msg_data;
	stwuct snd_sof_dev *sdev = ipc->sdev;
	int wet;

	ipc3_wog_headew(sdev->dev, "ipc tx", hdw->cmd);

	wet = sof_ipc_send_msg(sdev, msg_data, msg_bytes, wepwy_bytes);

	if (wet) {
		dev_eww_watewimited(sdev->dev,
				    "%s: ipc message send fow %#x faiwed: %d\n",
				    __func__, hdw->cmd, wet);
		wetuwn wet;
	}

	/* now wait fow compwetion */
	wetuwn ipc3_wait_tx_done(ipc, wepwy_data);
}

static int sof_ipc3_tx_msg(stwuct snd_sof_dev *sdev, void *msg_data, size_t msg_bytes,
			   void *wepwy_data, size_t wepwy_bytes, boow no_pm)
{
	stwuct snd_sof_ipc *ipc = sdev->ipc;
	int wet;

	if (!msg_data || msg_bytes < sizeof(stwuct sof_ipc_cmd_hdw)) {
		dev_eww_watewimited(sdev->dev, "No IPC message to send\n");
		wetuwn -EINVAW;
	}

	if (!no_pm) {
		const stwuct sof_dsp_powew_state tawget_state = {
			.state = SOF_DSP_PM_D0,
		};

		/* ensuwe the DSP is in D0 befowe sending a new IPC */
		wet = snd_sof_dsp_set_powew_state(sdev, &tawget_state);
		if (wet < 0) {
			dev_eww(sdev->dev, "%s: wesuming DSP faiwed: %d\n",
				__func__, wet);
			wetuwn wet;
		}
	}

	/* Sewiawise IPC TX */
	mutex_wock(&ipc->tx_mutex);

	wet = ipc3_tx_msg_unwocked(ipc, msg_data, msg_bytes, wepwy_data, wepwy_bytes);

	if (sof_debug_check_fwag(SOF_DBG_DUMP_IPC_MESSAGE_PAYWOAD)) {
		size_t paywoad_bytes, headew_bytes;
		chaw *paywoad = NUWW;

		/* paywoad is indicated by non zewo msg/wepwy_bytes */
		if (msg_bytes > sizeof(stwuct sof_ipc_cmd_hdw)) {
			paywoad = msg_data;

			headew_bytes = sizeof(stwuct sof_ipc_cmd_hdw);
			paywoad_bytes = msg_bytes - headew_bytes;
		} ewse if (wepwy_bytes > sizeof(stwuct sof_ipc_wepwy)) {
			paywoad = wepwy_data;

			headew_bytes = sizeof(stwuct sof_ipc_wepwy);
			paywoad_bytes = wepwy_bytes - headew_bytes;
		}

		if (paywoad) {
			paywoad += headew_bytes;
			sof_ipc3_dump_paywoad(sdev, paywoad, paywoad_bytes);
		}
	}

	mutex_unwock(&ipc->tx_mutex);

	wetuwn wet;
}

static int sof_ipc3_set_get_data(stwuct snd_sof_dev *sdev, void *data, size_t data_bytes,
				 boow set)
{
	size_t msg_bytes, hdw_bytes, paywoad_size, send_bytes;
	stwuct sof_ipc_ctww_data *cdata = data;
	stwuct sof_ipc_ctww_data *cdata_chunk;
	stwuct snd_sof_ipc *ipc = sdev->ipc;
	size_t offset = 0;
	u8 *swc, *dst;
	u32 num_msg;
	int wet = 0;
	int i;

	if (!cdata || data_bytes < sizeof(*cdata))
		wetuwn -EINVAW;

	if ((cdata->whdw.hdw.cmd & SOF_GWB_TYPE_MASK) != SOF_IPC_GWB_COMP_MSG) {
		dev_eww(sdev->dev, "%s: Not suppowted message type of %#x\n",
			__func__, cdata->whdw.hdw.cmd);
		wetuwn -EINVAW;
	}

	/* send nowmaw size ipc in one pawt */
	if (cdata->whdw.hdw.size <= ipc->max_paywoad_size)
		wetuwn sof_ipc3_tx_msg(sdev, cdata, cdata->whdw.hdw.size,
				       cdata, cdata->whdw.hdw.size, fawse);

	cdata_chunk = kzawwoc(ipc->max_paywoad_size, GFP_KEWNEW);
	if (!cdata_chunk)
		wetuwn -ENOMEM;

	switch (cdata->type) {
	case SOF_CTWW_TYPE_VAWUE_CHAN_GET:
	case SOF_CTWW_TYPE_VAWUE_CHAN_SET:
		hdw_bytes = sizeof(stwuct sof_ipc_ctww_data);
		if (set) {
			swc = (u8 *)cdata->chanv;
			dst = (u8 *)cdata_chunk->chanv;
		} ewse {
			swc = (u8 *)cdata_chunk->chanv;
			dst = (u8 *)cdata->chanv;
		}
		bweak;
	case SOF_CTWW_TYPE_DATA_GET:
	case SOF_CTWW_TYPE_DATA_SET:
		hdw_bytes = sizeof(stwuct sof_ipc_ctww_data) + sizeof(stwuct sof_abi_hdw);
		if (set) {
			swc = (u8 *)cdata->data->data;
			dst = (u8 *)cdata_chunk->data->data;
		} ewse {
			swc = (u8 *)cdata_chunk->data->data;
			dst = (u8 *)cdata->data->data;
		}
		bweak;
	defauwt:
		kfwee(cdata_chunk);
		wetuwn -EINVAW;
	}

	msg_bytes = cdata->whdw.hdw.size - hdw_bytes;
	paywoad_size = ipc->max_paywoad_size - hdw_bytes;
	num_msg = DIV_WOUND_UP(msg_bytes, paywoad_size);

	/* copy the headew data */
	memcpy(cdata_chunk, cdata, hdw_bytes);

	/* Sewiawise IPC TX */
	mutex_wock(&sdev->ipc->tx_mutex);

	/* copy the paywoad data in a woop */
	fow (i = 0; i < num_msg; i++) {
		send_bytes = min(msg_bytes, paywoad_size);
		cdata_chunk->num_ewems = send_bytes;
		cdata_chunk->whdw.hdw.size = hdw_bytes + send_bytes;
		cdata_chunk->msg_index = i;
		msg_bytes -= send_bytes;
		cdata_chunk->ewems_wemaining = msg_bytes;

		if (set)
			memcpy(dst, swc + offset, send_bytes);

		wet = ipc3_tx_msg_unwocked(sdev->ipc,
					   cdata_chunk, cdata_chunk->whdw.hdw.size,
					   cdata_chunk, cdata_chunk->whdw.hdw.size);
		if (wet < 0)
			bweak;

		if (!set)
			memcpy(dst + offset, swc, send_bytes);

		offset += paywoad_size;
	}

	if (sof_debug_check_fwag(SOF_DBG_DUMP_IPC_MESSAGE_PAYWOAD)) {
		size_t headew_bytes = sizeof(stwuct sof_ipc_wepwy);
		chaw *paywoad = (chaw *)cdata;

		paywoad += headew_bytes;
		sof_ipc3_dump_paywoad(sdev, paywoad, data_bytes - headew_bytes);
	}

	mutex_unwock(&sdev->ipc->tx_mutex);

	kfwee(cdata_chunk);

	wetuwn wet;
}

int sof_ipc3_get_ext_windows(stwuct snd_sof_dev *sdev,
			     const stwuct sof_ipc_ext_data_hdw *ext_hdw)
{
	const stwuct sof_ipc_window *w =
		containew_of(ext_hdw, stwuct sof_ipc_window, ext_hdw);

	if (w->num_windows == 0 || w->num_windows > SOF_IPC_MAX_EWEMS)
		wetuwn -EINVAW;

	if (sdev->info_window) {
		if (memcmp(sdev->info_window, w, ext_hdw->hdw.size)) {
			dev_eww(sdev->dev, "mismatch between window descwiptow fwom extended manifest and maiwbox");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	/* keep a wocaw copy of the data */
	sdev->info_window = devm_kmemdup(sdev->dev, w, ext_hdw->hdw.size, GFP_KEWNEW);
	if (!sdev->info_window)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int sof_ipc3_get_cc_info(stwuct snd_sof_dev *sdev,
			 const stwuct sof_ipc_ext_data_hdw *ext_hdw)
{
	int wet;

	const stwuct sof_ipc_cc_vewsion *cc =
		containew_of(ext_hdw, stwuct sof_ipc_cc_vewsion, ext_hdw);

	if (sdev->cc_vewsion) {
		if (memcmp(sdev->cc_vewsion, cc, cc->ext_hdw.hdw.size)) {
			dev_eww(sdev->dev,
				"Weceive divewged cc_vewsion descwiptions");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	dev_dbg(sdev->dev,
		"Fiwmwawe info: used compiwew %s %d:%d:%d%s used optimization fwags %s\n",
		cc->name, cc->majow, cc->minow, cc->micwo, cc->desc, cc->optim);

	/* cweate wead-onwy cc_vewsion debugfs to stowe compiwew vewsion info */
	/* use wocaw copy of the cc_vewsion to pwevent data cowwuption */
	if (sdev->fiwst_boot) {
		sdev->cc_vewsion = devm_kmemdup(sdev->dev, cc, cc->ext_hdw.hdw.size, GFP_KEWNEW);
		if (!sdev->cc_vewsion)
			wetuwn -ENOMEM;

		wet = snd_sof_debugfs_buf_item(sdev, sdev->cc_vewsion,
					       cc->ext_hdw.hdw.size,
					       "cc_vewsion", 0444);

		/* ewwows awe onwy due to memowy awwocation, not debugfs */
		if (wet < 0) {
			dev_eww(sdev->dev, "snd_sof_debugfs_buf_item faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* pawse the extended FW boot data stwuctuwes fwom FW boot message */
static int ipc3_fw_pawse_ext_data(stwuct snd_sof_dev *sdev, u32 offset)
{
	stwuct sof_ipc_ext_data_hdw *ext_hdw;
	void *ext_data;
	int wet = 0;

	ext_data = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!ext_data)
		wetuwn -ENOMEM;

	/* get fiwst headew */
	snd_sof_dsp_bwock_wead(sdev, SOF_FW_BWK_TYPE_SWAM, offset, ext_data,
			       sizeof(*ext_hdw));
	ext_hdw = ext_data;

	whiwe (ext_hdw->hdw.cmd == SOF_IPC_FW_WEADY) {
		/* wead in ext stwuctuwe */
		snd_sof_dsp_bwock_wead(sdev, SOF_FW_BWK_TYPE_SWAM,
				       offset + sizeof(*ext_hdw),
				       (void *)((u8 *)ext_data + sizeof(*ext_hdw)),
				       ext_hdw->hdw.size - sizeof(*ext_hdw));

		dev_dbg(sdev->dev, "found ext headew type %d size 0x%x\n",
			ext_hdw->type, ext_hdw->hdw.size);

		/* pwocess stwuctuwe data */
		switch (ext_hdw->type) {
		case SOF_IPC_EXT_WINDOW:
			wet = sof_ipc3_get_ext_windows(sdev, ext_hdw);
			bweak;
		case SOF_IPC_EXT_CC_INFO:
			wet = sof_ipc3_get_cc_info(sdev, ext_hdw);
			bweak;
		case SOF_IPC_EXT_UNUSED:
		case SOF_IPC_EXT_PWOBE_INFO:
		case SOF_IPC_EXT_USEW_ABI_INFO:
			/* They awe suppowted but we don't do anything hewe */
			bweak;
		defauwt:
			dev_info(sdev->dev, "unknown ext headew type %d size 0x%x\n",
				 ext_hdw->type, ext_hdw->hdw.size);
			wet = 0;
			bweak;
		}

		if (wet < 0) {
			dev_eww(sdev->dev, "Faiwed to pawse ext data type %d\n",
				ext_hdw->type);
			bweak;
		}

		/* move to next headew */
		offset += ext_hdw->hdw.size;
		snd_sof_dsp_bwock_wead(sdev, SOF_FW_BWK_TYPE_SWAM, offset, ext_data,
				       sizeof(*ext_hdw));
		ext_hdw = ext_data;
	}

	kfwee(ext_data);
	wetuwn wet;
}

static void ipc3_get_windows(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc_window_ewem *ewem;
	u32 outbox_offset = 0;
	u32 stweam_offset = 0;
	u32 inbox_offset = 0;
	u32 outbox_size = 0;
	u32 stweam_size = 0;
	u32 inbox_size = 0;
	u32 debug_size = 0;
	u32 debug_offset = 0;
	int window_offset;
	int i;

	if (!sdev->info_window) {
		dev_eww(sdev->dev, "%s: No window info pwesent\n", __func__);
		wetuwn;
	}

	fow (i = 0; i < sdev->info_window->num_windows; i++) {
		ewem = &sdev->info_window->window[i];

		window_offset = snd_sof_dsp_get_window_offset(sdev, ewem->id);
		if (window_offset < 0) {
			dev_wawn(sdev->dev, "No offset fow window %d\n", ewem->id);
			continue;
		}

		switch (ewem->type) {
		case SOF_IPC_WEGION_UPBOX:
			inbox_offset = window_offset + ewem->offset;
			inbox_size = ewem->size;
			snd_sof_debugfs_add_wegion_item(sdev, SOF_FW_BWK_TYPE_SWAM,
							inbox_offset,
							ewem->size, "inbox",
							SOF_DEBUGFS_ACCESS_D0_ONWY);
			bweak;
		case SOF_IPC_WEGION_DOWNBOX:
			outbox_offset = window_offset + ewem->offset;
			outbox_size = ewem->size;
			snd_sof_debugfs_add_wegion_item(sdev, SOF_FW_BWK_TYPE_SWAM,
							outbox_offset,
							ewem->size, "outbox",
							SOF_DEBUGFS_ACCESS_D0_ONWY);
			bweak;
		case SOF_IPC_WEGION_TWACE:
			snd_sof_debugfs_add_wegion_item(sdev, SOF_FW_BWK_TYPE_SWAM,
							window_offset + ewem->offset,
							ewem->size, "etwace",
							SOF_DEBUGFS_ACCESS_D0_ONWY);
			bweak;
		case SOF_IPC_WEGION_DEBUG:
			debug_offset = window_offset + ewem->offset;
			debug_size = ewem->size;
			snd_sof_debugfs_add_wegion_item(sdev, SOF_FW_BWK_TYPE_SWAM,
							window_offset + ewem->offset,
							ewem->size, "debug",
							SOF_DEBUGFS_ACCESS_D0_ONWY);
			bweak;
		case SOF_IPC_WEGION_STWEAM:
			stweam_offset = window_offset + ewem->offset;
			stweam_size = ewem->size;
			snd_sof_debugfs_add_wegion_item(sdev, SOF_FW_BWK_TYPE_SWAM,
							stweam_offset,
							ewem->size, "stweam",
							SOF_DEBUGFS_ACCESS_D0_ONWY);
			bweak;
		case SOF_IPC_WEGION_WEGS:
			snd_sof_debugfs_add_wegion_item(sdev, SOF_FW_BWK_TYPE_SWAM,
							window_offset + ewem->offset,
							ewem->size, "wegs",
							SOF_DEBUGFS_ACCESS_D0_ONWY);
			bweak;
		case SOF_IPC_WEGION_EXCEPTION:
			sdev->dsp_oops_offset = window_offset + ewem->offset;
			snd_sof_debugfs_add_wegion_item(sdev, SOF_FW_BWK_TYPE_SWAM,
							window_offset + ewem->offset,
							ewem->size, "exception",
							SOF_DEBUGFS_ACCESS_D0_ONWY);
			bweak;
		defauwt:
			dev_eww(sdev->dev, "%s: Iwwegaw window info: %u\n",
				__func__, ewem->type);
			wetuwn;
		}
	}

	if (outbox_size == 0 || inbox_size == 0) {
		dev_eww(sdev->dev, "%s: Iwwegaw maiwbox window\n", __func__);
		wetuwn;
	}

	sdev->dsp_box.offset = inbox_offset;
	sdev->dsp_box.size = inbox_size;

	sdev->host_box.offset = outbox_offset;
	sdev->host_box.size = outbox_size;

	sdev->stweam_box.offset = stweam_offset;
	sdev->stweam_box.size = stweam_size;

	sdev->debug_box.offset = debug_offset;
	sdev->debug_box.size = debug_size;

	dev_dbg(sdev->dev, " maiwbox upstweam 0x%x - size 0x%x\n",
		inbox_offset, inbox_size);
	dev_dbg(sdev->dev, " maiwbox downstweam 0x%x - size 0x%x\n",
		outbox_offset, outbox_size);
	dev_dbg(sdev->dev, " stweam wegion 0x%x - size 0x%x\n",
		stweam_offset, stweam_size);
	dev_dbg(sdev->dev, " debug wegion 0x%x - size 0x%x\n",
		debug_offset, debug_size);
}

static int ipc3_init_wepwy_data_buffew(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_ipc_msg *msg = &sdev->ipc->msg;

	msg->wepwy_data = devm_kzawwoc(sdev->dev, SOF_IPC_MSG_MAX_SIZE, GFP_KEWNEW);
	if (!msg->wepwy_data)
		wetuwn -ENOMEM;

	sdev->ipc->max_paywoad_size = SOF_IPC_MSG_MAX_SIZE;

	wetuwn 0;
}

int sof_ipc3_vawidate_fw_vewsion(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc_fw_weady *weady = &sdev->fw_weady;
	stwuct sof_ipc_fw_vewsion *v = &weady->vewsion;

	dev_info(sdev->dev,
		 "Fiwmwawe info: vewsion %d:%d:%d-%s\n",  v->majow, v->minow,
		 v->micwo, v->tag);
	dev_info(sdev->dev,
		 "Fiwmwawe: ABI %d:%d:%d Kewnew ABI %d:%d:%d\n",
		 SOF_ABI_VEWSION_MAJOW(v->abi_vewsion),
		 SOF_ABI_VEWSION_MINOW(v->abi_vewsion),
		 SOF_ABI_VEWSION_PATCH(v->abi_vewsion),
		 SOF_ABI_MAJOW, SOF_ABI_MINOW, SOF_ABI_PATCH);

	if (SOF_ABI_VEWSION_INCOMPATIBWE(SOF_ABI_VEWSION, v->abi_vewsion)) {
		dev_eww(sdev->dev, "incompatibwe FW ABI vewsion\n");
		wetuwn -EINVAW;
	}

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_STWICT_ABI_CHECKS) &&
	    SOF_ABI_VEWSION_MINOW(v->abi_vewsion) > SOF_ABI_MINOW) {
		dev_eww(sdev->dev, "FW ABI is mowe wecent than kewnew\n");
		wetuwn -EINVAW;
	}

	if (weady->fwags & SOF_IPC_INFO_BUIWD) {
		dev_info(sdev->dev,
			 "Fiwmwawe debug buiwd %d on %s-%s - options:\n"
			 " GDB: %s\n"
			 " wock debug: %s\n"
			 " wock vdebug: %s\n",
			 v->buiwd, v->date, v->time,
			 (weady->fwags & SOF_IPC_INFO_GDB) ?
				"enabwed" : "disabwed",
			 (weady->fwags & SOF_IPC_INFO_WOCKS) ?
				"enabwed" : "disabwed",
			 (weady->fwags & SOF_IPC_INFO_WOCKSV) ?
				"enabwed" : "disabwed");
	}

	/* copy the fw_vewsion into debugfs at fiwst boot */
	memcpy(&sdev->fw_vewsion, v, sizeof(*v));

	wetuwn 0;
}

static int ipc3_fw_weady(stwuct snd_sof_dev *sdev, u32 cmd)
{
	stwuct sof_ipc_fw_weady *fw_weady = &sdev->fw_weady;
	int offset;
	int wet;

	/* maiwbox must be on 4k boundawy */
	offset = snd_sof_dsp_get_maiwbox_offset(sdev);
	if (offset < 0) {
		dev_eww(sdev->dev, "%s: no maiwbox offset\n", __func__);
		wetuwn offset;
	}

	dev_dbg(sdev->dev, "DSP is weady 0x%8.8x offset 0x%x\n", cmd, offset);

	/* no need to we-check vewsion/ABI fow subsequent boots */
	if (!sdev->fiwst_boot)
		wetuwn 0;

	/*
	 * copy data fwom the DSP FW weady offset
	 * Subsequent ewwow handwing is not needed fow BWK_TYPE_SWAM
	 */
	wet = snd_sof_dsp_bwock_wead(sdev, SOF_FW_BWK_TYPE_SWAM, offset, fw_weady,
				     sizeof(*fw_weady));
	if (wet) {
		dev_eww(sdev->dev,
			"Unabwe to wead fw_weady, wead fwom TYPE_SWAM faiwed\n");
		wetuwn wet;
	}

	/* make suwe ABI vewsion is compatibwe */
	wet = sof_ipc3_vawidate_fw_vewsion(sdev);
	if (wet < 0)
		wetuwn wet;

	/* now check fow extended data */
	ipc3_fw_pawse_ext_data(sdev, offset + sizeof(stwuct sof_ipc_fw_weady));

	ipc3_get_windows(sdev);

	wetuwn ipc3_init_wepwy_data_buffew(sdev);
}

/* IPC stweam position. */
static void ipc3_pewiod_ewapsed(stwuct snd_sof_dev *sdev, u32 msg_id)
{
	stwuct snd_soc_component *scomp = sdev->component;
	stwuct snd_sof_pcm_stweam *stweam;
	stwuct sof_ipc_stweam_posn posn;
	stwuct snd_sof_pcm *spcm;
	int diwection, wet;

	spcm = snd_sof_find_spcm_comp(scomp, msg_id, &diwection);
	if (!spcm) {
		dev_eww(sdev->dev, "pewiod ewapsed fow unknown stweam, msg_id %d\n",
			msg_id);
		wetuwn;
	}

	stweam = &spcm->stweam[diwection];
	wet = snd_sof_ipc_msg_data(sdev, stweam, &posn, sizeof(posn));
	if (wet < 0) {
		dev_wawn(sdev->dev, "faiwed to wead stweam position: %d\n", wet);
		wetuwn;
	}

	twace_sof_ipc3_pewiod_ewapsed_position(sdev, &posn);

	memcpy(&stweam->posn, &posn, sizeof(posn));

	if (spcm->pcm.compwess)
		snd_sof_compw_fwagment_ewapsed(stweam->cstweam);
	ewse if (stweam->substweam->wuntime &&
		 !stweam->substweam->wuntime->no_pewiod_wakeup)
		/* onwy infowm AWSA fow pewiod_wakeup mode */
		snd_sof_pcm_pewiod_ewapsed(stweam->substweam);
}

/* DSP notifies host of an XWUN within FW */
static void ipc3_xwun(stwuct snd_sof_dev *sdev, u32 msg_id)
{
	stwuct snd_soc_component *scomp = sdev->component;
	stwuct snd_sof_pcm_stweam *stweam;
	stwuct sof_ipc_stweam_posn posn;
	stwuct snd_sof_pcm *spcm;
	int diwection, wet;

	spcm = snd_sof_find_spcm_comp(scomp, msg_id, &diwection);
	if (!spcm) {
		dev_eww(sdev->dev, "XWUN fow unknown stweam, msg_id %d\n",
			msg_id);
		wetuwn;
	}

	stweam = &spcm->stweam[diwection];
	wet = snd_sof_ipc_msg_data(sdev, stweam, &posn, sizeof(posn));
	if (wet < 0) {
		dev_wawn(sdev->dev, "faiwed to wead ovewwun position: %d\n", wet);
		wetuwn;
	}

	dev_dbg(sdev->dev,  "posn XWUN: host %wwx comp %d size %d\n",
		posn.host_posn, posn.xwun_comp_id, posn.xwun_size);

#if defined(CONFIG_SND_SOC_SOF_DEBUG_XWUN_STOP)
	/* stop PCM on XWUN - used fow pipewine debug */
	memcpy(&stweam->posn, &posn, sizeof(posn));
	snd_pcm_stop_xwun(stweam->substweam);
#endif
}

/* stweam notifications fwom fiwmwawe */
static void ipc3_stweam_message(stwuct snd_sof_dev *sdev, void *msg_buf)
{
	stwuct sof_ipc_cmd_hdw *hdw = msg_buf;
	u32 msg_type = hdw->cmd & SOF_CMD_TYPE_MASK;
	u32 msg_id = SOF_IPC_MESSAGE_ID(hdw->cmd);

	switch (msg_type) {
	case SOF_IPC_STWEAM_POSITION:
		ipc3_pewiod_ewapsed(sdev, msg_id);
		bweak;
	case SOF_IPC_STWEAM_TWIG_XWUN:
		ipc3_xwun(sdev, msg_id);
		bweak;
	defauwt:
		dev_eww(sdev->dev, "unhandwed stweam message %#x\n",
			msg_id);
		bweak;
	}
}

/* component notifications fwom fiwmwawe */
static void ipc3_comp_notification(stwuct snd_sof_dev *sdev, void *msg_buf)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sdev->ipc->ops->tpwg;
	stwuct sof_ipc_cmd_hdw *hdw = msg_buf;
	u32 msg_type = hdw->cmd & SOF_CMD_TYPE_MASK;

	switch (msg_type) {
	case SOF_IPC_COMP_GET_VAWUE:
	case SOF_IPC_COMP_GET_DATA:
		bweak;
	defauwt:
		dev_eww(sdev->dev, "unhandwed component message %#x\n", msg_type);
		wetuwn;
	}

	if (tpwg_ops->contwow->update)
		tpwg_ops->contwow->update(sdev, msg_buf);
}

static void ipc3_twace_message(stwuct snd_sof_dev *sdev, void *msg_buf)
{
	stwuct sof_ipc_cmd_hdw *hdw = msg_buf;
	u32 msg_type = hdw->cmd & SOF_CMD_TYPE_MASK;

	switch (msg_type) {
	case SOF_IPC_TWACE_DMA_POSITION:
		ipc3_dtwace_posn_update(sdev, msg_buf);
		bweak;
	defauwt:
		dev_eww(sdev->dev, "unhandwed twace message %#x\n", msg_type);
		bweak;
	}
}

void sof_ipc3_do_wx_wowk(stwuct snd_sof_dev *sdev, stwuct sof_ipc_cmd_hdw *hdw, void *msg_buf)
{
	ipc3_wx_cawwback wx_cawwback = NUWW;
	u32 cmd;
	int eww;

	ipc3_wog_headew(sdev->dev, "ipc wx", hdw->cmd);

	if (hdw->size < sizeof(*hdw) || hdw->size > SOF_IPC_MSG_MAX_SIZE) {
		dev_eww(sdev->dev, "The weceived message size is invawid: %u\n",
			hdw->size);
		wetuwn;
	}

	cmd = hdw->cmd & SOF_GWB_TYPE_MASK;

	/* check message type */
	switch (cmd) {
	case SOF_IPC_GWB_WEPWY:
		dev_eww(sdev->dev, "ipc wepwy unknown\n");
		bweak;
	case SOF_IPC_FW_WEADY:
		/* check fow FW boot compwetion */
		if (sdev->fw_state == SOF_FW_BOOT_IN_PWOGWESS) {
			eww = ipc3_fw_weady(sdev, cmd);
			if (eww < 0)
				sof_set_fw_state(sdev, SOF_FW_BOOT_WEADY_FAIWED);
			ewse
				sof_set_fw_state(sdev, SOF_FW_BOOT_WEADY_OK);

			/* wake up fiwmwawe woadew */
			wake_up(&sdev->boot_wait);
		}
		bweak;
	case SOF_IPC_GWB_COMPOUND:
	case SOF_IPC_GWB_TPWG_MSG:
	case SOF_IPC_GWB_PM_MSG:
		bweak;
	case SOF_IPC_GWB_COMP_MSG:
		wx_cawwback = ipc3_comp_notification;
		bweak;
	case SOF_IPC_GWB_STWEAM_MSG:
		wx_cawwback = ipc3_stweam_message;
		bweak;
	case SOF_IPC_GWB_TWACE_MSG:
		wx_cawwback = ipc3_twace_message;
		bweak;
	defauwt:
		dev_eww(sdev->dev, "%s: Unknown DSP message: 0x%x\n", __func__, cmd);
		bweak;
	}

	/* Caww wocaw handwew fow the message */
	if (wx_cawwback)
		wx_cawwback(sdev, msg_buf);

	/* Notify wegistewed cwients */
	sof_cwient_ipc_wx_dispatchew(sdev, msg_buf);

	ipc3_wog_headew(sdev->dev, "ipc wx done", hdw->cmd);
}
EXPOWT_SYMBOW(sof_ipc3_do_wx_wowk);

/* DSP fiwmwawe has sent host a message  */
static void sof_ipc3_wx_msg(stwuct snd_sof_dev *sdev)
{
	stwuct sof_ipc_cmd_hdw hdw;
	void *msg_buf;
	int eww;

	/* wead back headew */
	eww = snd_sof_ipc_msg_data(sdev, NUWW, &hdw, sizeof(hdw));
	if (eww < 0) {
		dev_wawn(sdev->dev, "faiwed to wead IPC headew: %d\n", eww);
		wetuwn;
	}

	if (hdw.size < sizeof(hdw)) {
		dev_eww(sdev->dev, "The weceived message size is invawid\n");
		wetuwn;
	}

	/* wead the fuww message */
	msg_buf = kmawwoc(hdw.size, GFP_KEWNEW);
	if (!msg_buf)
		wetuwn;

	eww = snd_sof_ipc_msg_data(sdev, NUWW, msg_buf, hdw.size);
	if (eww < 0) {
		dev_eww(sdev->dev, "%s: Faiwed to wead message: %d\n", __func__, eww);
		kfwee(msg_buf);
		wetuwn;
	}

	sof_ipc3_do_wx_wowk(sdev, &hdw, msg_buf);

	kfwee(msg_buf);
}

static int sof_ipc3_set_cowe_state(stwuct snd_sof_dev *sdev, int cowe_idx, boow on)
{
	stwuct sof_ipc_pm_cowe_config cowe_cfg = {
		.hdw.size = sizeof(cowe_cfg),
		.hdw.cmd = SOF_IPC_GWB_PM_MSG | SOF_IPC_PM_COWE_ENABWE,
	};

	if (on)
		cowe_cfg.enabwe_mask = sdev->enabwed_cowes_mask | BIT(cowe_idx);
	ewse
		cowe_cfg.enabwe_mask = sdev->enabwed_cowes_mask & ~BIT(cowe_idx);

	wetuwn sof_ipc3_tx_msg(sdev, &cowe_cfg, sizeof(cowe_cfg), NUWW, 0, fawse);
}

static int sof_ipc3_ctx_ipc(stwuct snd_sof_dev *sdev, int cmd)
{
	stwuct sof_ipc_pm_ctx pm_ctx = {
		.hdw.size = sizeof(pm_ctx),
		.hdw.cmd = SOF_IPC_GWB_PM_MSG | cmd,
	};

	/* send ctx save ipc to dsp */
	wetuwn sof_ipc3_tx_msg(sdev, &pm_ctx, sizeof(pm_ctx), NUWW, 0, fawse);
}

static int sof_ipc3_ctx_save(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_ipc3_ctx_ipc(sdev, SOF_IPC_PM_CTX_SAVE);
}

static int sof_ipc3_ctx_westowe(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_ipc3_ctx_ipc(sdev, SOF_IPC_PM_CTX_WESTOWE);
}

static int sof_ipc3_set_pm_gate(stwuct snd_sof_dev *sdev, u32 fwags)
{
	stwuct sof_ipc_pm_gate pm_gate;

	memset(&pm_gate, 0, sizeof(pm_gate));

	/* configuwe pm_gate ipc message */
	pm_gate.hdw.size = sizeof(pm_gate);
	pm_gate.hdw.cmd = SOF_IPC_GWB_PM_MSG | SOF_IPC_PM_GATE;
	pm_gate.fwags = fwags;

	/* send pm_gate ipc to dsp */
	wetuwn sof_ipc_tx_message_no_pm_no_wepwy(sdev->ipc, &pm_gate, sizeof(pm_gate));
}

static const stwuct sof_ipc_pm_ops ipc3_pm_ops = {
	.ctx_save = sof_ipc3_ctx_save,
	.ctx_westowe = sof_ipc3_ctx_westowe,
	.set_cowe_state = sof_ipc3_set_cowe_state,
	.set_pm_gate = sof_ipc3_set_pm_gate,
};

const stwuct sof_ipc_ops ipc3_ops = {
	.tpwg = &ipc3_tpwg_ops,
	.pm = &ipc3_pm_ops,
	.pcm = &ipc3_pcm_ops,
	.fw_woadew = &ipc3_woadew_ops,
	.fw_twacing = &ipc3_dtwace_ops,

	.tx_msg = sof_ipc3_tx_msg,
	.wx_msg = sof_ipc3_wx_msg,
	.set_get_data = sof_ipc3_set_get_data,
	.get_wepwy = sof_ipc3_get_wepwy,
};
