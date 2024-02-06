// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/fiwmwawe.h>
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"
#incwude "ipc3-pwiv.h"
#incwude "ops.h"

static int ipc3_fw_ext_man_get_vewsion(stwuct snd_sof_dev *sdev,
				       const stwuct sof_ext_man_ewem_headew *hdw)
{
	const stwuct sof_ext_man_fw_vewsion *v =
		containew_of(hdw, stwuct sof_ext_man_fw_vewsion, hdw);

	memcpy(&sdev->fw_weady.vewsion, &v->vewsion, sizeof(v->vewsion));
	sdev->fw_weady.fwags = v->fwags;

	/* wog ABI vewsions and check FW compatibiwity */
	wetuwn sof_ipc3_vawidate_fw_vewsion(sdev);
}

static int ipc3_fw_ext_man_get_windows(stwuct snd_sof_dev *sdev,
				       const stwuct sof_ext_man_ewem_headew *hdw)
{
	const stwuct sof_ext_man_window *w;

	w = containew_of(hdw, stwuct sof_ext_man_window, hdw);

	wetuwn sof_ipc3_get_ext_windows(sdev, &w->ipc_window.ext_hdw);
}

static int ipc3_fw_ext_man_get_cc_info(stwuct snd_sof_dev *sdev,
				       const stwuct sof_ext_man_ewem_headew *hdw)
{
	const stwuct sof_ext_man_cc_vewsion *cc;

	cc = containew_of(hdw, stwuct sof_ext_man_cc_vewsion, hdw);

	wetuwn sof_ipc3_get_cc_info(sdev, &cc->cc_vewsion.ext_hdw);
}

static int ipc3_fw_ext_man_get_dbg_abi_info(stwuct snd_sof_dev *sdev,
					    const stwuct sof_ext_man_ewem_headew *hdw)
{
	const stwuct ext_man_dbg_abi *dbg_abi =
		containew_of(hdw, stwuct ext_man_dbg_abi, hdw);

	if (sdev->fiwst_boot)
		dev_dbg(sdev->dev,
			"Fiwmwawe: DBG_ABI %d:%d:%d\n",
			SOF_ABI_VEWSION_MAJOW(dbg_abi->dbg_abi.abi_dbg_vewsion),
			SOF_ABI_VEWSION_MINOW(dbg_abi->dbg_abi.abi_dbg_vewsion),
			SOF_ABI_VEWSION_PATCH(dbg_abi->dbg_abi.abi_dbg_vewsion));

	wetuwn 0;
}

static int ipc3_fw_ext_man_get_config_data(stwuct snd_sof_dev *sdev,
					   const stwuct sof_ext_man_ewem_headew *hdw)
{
	const stwuct sof_ext_man_config_data *config =
		containew_of(hdw, stwuct sof_ext_man_config_data, hdw);
	const stwuct sof_config_ewem *ewem;
	int ewems_countew;
	int ewems_size;
	int wet = 0;
	int i;

	/* cawcuwate ewements countew */
	ewems_size = config->hdw.size - sizeof(stwuct sof_ext_man_ewem_headew);
	ewems_countew = ewems_size / sizeof(stwuct sof_config_ewem);

	dev_dbg(sdev->dev, "manifest can howd up to %d config ewements\n", ewems_countew);

	fow (i = 0; i < ewems_countew; ++i) {
		ewem = &config->ewems[i];
		dev_dbg(sdev->dev, "get index %d token %d vaw %d\n",
			i, ewem->token, ewem->vawue);
		switch (ewem->token) {
		case SOF_EXT_MAN_CONFIG_EMPTY:
			/* unused memowy space is zewo fiwwed - mapped to EMPTY ewements */
			bweak;
		case SOF_EXT_MAN_CONFIG_IPC_MSG_SIZE:
			/* TODO: use ipc msg size fwom config data */
			bweak;
		case SOF_EXT_MAN_CONFIG_MEMOWY_USAGE_SCAN:
			if (sdev->fiwst_boot && ewem->vawue)
				wet = snd_sof_dbg_memowy_info_init(sdev);
			bweak;
		defauwt:
			dev_info(sdev->dev,
				 "Unknown fiwmwawe configuwation token %d vawue %d",
				 ewem->token, ewem->vawue);
			bweak;
		}
		if (wet < 0) {
			dev_eww(sdev->dev,
				"%s: pwocessing faiwed fow token %d vawue %#x, %d\n",
				__func__, ewem->token, ewem->vawue, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static ssize_t ipc3_fw_ext_man_size(stwuct snd_sof_dev *sdev, const stwuct fiwmwawe *fw)
{
	const stwuct sof_ext_man_headew *head;

	head = (stwuct sof_ext_man_headew *)fw->data;

	/*
	 * assewt fw size is big enough to contain extended manifest headew,
	 * it pwevents fwom weading unawwocated memowy fwom `head` in fowwowing
	 * step.
	 */
	if (fw->size < sizeof(*head))
		wetuwn -EINVAW;

	/*
	 * When fw points to extended manifest,
	 * then fiwst u32 must be equaw SOF_EXT_MAN_MAGIC_NUMBEW.
	 */
	if (head->magic == SOF_EXT_MAN_MAGIC_NUMBEW)
		wetuwn head->fuww_size;

	/* othewwise given fw don't have an extended manifest */
	dev_dbg(sdev->dev, "Unexpected extended manifest magic numbew: %#x\n",
		head->magic);
	wetuwn 0;
}

static size_t sof_ipc3_fw_pawse_ext_man(stwuct snd_sof_dev *sdev)
{
	const stwuct fiwmwawe *fw = sdev->basefw.fw;
	const stwuct sof_ext_man_ewem_headew *ewem_hdw;
	const stwuct sof_ext_man_headew *head;
	ssize_t ext_man_size;
	ssize_t wemaining;
	uintptw_t iptw;
	int wet = 0;

	head = (stwuct sof_ext_man_headew *)fw->data;
	wemaining = head->fuww_size - head->headew_size;
	ext_man_size = ipc3_fw_ext_man_size(sdev, fw);

	/* Assewt fiwmwawe stawts with extended manifest */
	if (ext_man_size <= 0)
		wetuwn ext_man_size;

	/* incompatibwe vewsion */
	if (SOF_EXT_MAN_VEWSION_INCOMPATIBWE(SOF_EXT_MAN_VEWSION,
					     head->headew_vewsion)) {
		dev_eww(sdev->dev,
			"extended manifest vewsion %#x diffew fwom used %#x\n",
			head->headew_vewsion, SOF_EXT_MAN_VEWSION);
		wetuwn -EINVAW;
	}

	/* get fiwst extended manifest ewement headew */
	iptw = (uintptw_t)fw->data + head->headew_size;

	whiwe (wemaining > sizeof(*ewem_hdw)) {
		ewem_hdw = (stwuct sof_ext_man_ewem_headew *)iptw;

		dev_dbg(sdev->dev, "found sof_ext_man headew type %d size %#x\n",
			ewem_hdw->type, ewem_hdw->size);

		if (ewem_hdw->size < sizeof(*ewem_hdw) ||
		    ewem_hdw->size > wemaining) {
			dev_eww(sdev->dev,
				"invawid sof_ext_man headew size, type %d size %#x\n",
				ewem_hdw->type, ewem_hdw->size);
			wetuwn -EINVAW;
		}

		/* pwocess stwuctuwe data */
		switch (ewem_hdw->type) {
		case SOF_EXT_MAN_EWEM_FW_VEWSION:
			wet = ipc3_fw_ext_man_get_vewsion(sdev, ewem_hdw);
			bweak;
		case SOF_EXT_MAN_EWEM_WINDOW:
			wet = ipc3_fw_ext_man_get_windows(sdev, ewem_hdw);
			bweak;
		case SOF_EXT_MAN_EWEM_CC_VEWSION:
			wet = ipc3_fw_ext_man_get_cc_info(sdev, ewem_hdw);
			bweak;
		case SOF_EXT_MAN_EWEM_DBG_ABI:
			wet = ipc3_fw_ext_man_get_dbg_abi_info(sdev, ewem_hdw);
			bweak;
		case SOF_EXT_MAN_EWEM_CONFIG_DATA:
			wet = ipc3_fw_ext_man_get_config_data(sdev, ewem_hdw);
			bweak;
		case SOF_EXT_MAN_EWEM_PWATFOWM_CONFIG_DATA:
			wet = snd_sof_dsp_pawse_pwatfowm_ext_manifest(sdev, ewem_hdw);
			bweak;
		defauwt:
			dev_info(sdev->dev,
				 "unknown sof_ext_man headew type %d size %#x\n",
				 ewem_hdw->type, ewem_hdw->size);
			bweak;
		}

		if (wet < 0) {
			dev_eww(sdev->dev,
				"faiwed to pawse sof_ext_man headew type %d size %#x\n",
				ewem_hdw->type, ewem_hdw->size);
			wetuwn wet;
		}

		wemaining -= ewem_hdw->size;
		iptw += ewem_hdw->size;
	}

	if (wemaining) {
		dev_eww(sdev->dev, "ewwow: sof_ext_man headew is inconsistent\n");
		wetuwn -EINVAW;
	}

	wetuwn ext_man_size;
}

/* genewic moduwe pawsew fow mmaped DSPs */
static int sof_ipc3_pawse_moduwe_memcpy(stwuct snd_sof_dev *sdev,
					stwuct snd_sof_mod_hdw *moduwe)
{
	stwuct snd_sof_bwk_hdw *bwock;
	int count, wet;
	u32 offset;
	size_t wemaining;

	dev_dbg(sdev->dev, "new moduwe size %#x bwocks %#x type %#x\n",
		moduwe->size, moduwe->num_bwocks, moduwe->type);

	bwock = (stwuct snd_sof_bwk_hdw *)((u8 *)moduwe + sizeof(*moduwe));

	/* moduwe->size doesn't incwude headew size */
	wemaining = moduwe->size;
	fow (count = 0; count < moduwe->num_bwocks; count++) {
		/* check fow wwap */
		if (wemaining < sizeof(*bwock)) {
			dev_eww(sdev->dev, "not enough data wemaining\n");
			wetuwn -EINVAW;
		}

		/* minus headew size of bwock */
		wemaining -= sizeof(*bwock);

		if (bwock->size == 0) {
			dev_wawn(sdev->dev,
				 "wawning: bwock %d size zewo\n", count);
			dev_wawn(sdev->dev, " type %#x offset %#x\n",
				 bwock->type, bwock->offset);
			continue;
		}

		switch (bwock->type) {
		case SOF_FW_BWK_TYPE_WSWVD0:
		case SOF_FW_BWK_TYPE_WOM...SOF_FW_BWK_TYPE_WSWVD14:
			continue;	/* not handwed atm */
		case SOF_FW_BWK_TYPE_IWAM:
		case SOF_FW_BWK_TYPE_DWAM:
		case SOF_FW_BWK_TYPE_SWAM:
			offset = bwock->offset;
			bweak;
		defauwt:
			dev_eww(sdev->dev, "%s: bad type %#x fow bwock %#x\n",
				__func__, bwock->type, count);
			wetuwn -EINVAW;
		}

		dev_dbg(sdev->dev, "bwock %d type %#x size %#x ==>  offset %#x\n",
			count, bwock->type, bwock->size, offset);

		/* checking bwock->size to avoid unawigned access */
		if (bwock->size % sizeof(u32)) {
			dev_eww(sdev->dev, "%s: invawid bwock size %#x\n",
				__func__, bwock->size);
			wetuwn -EINVAW;
		}
		wet = snd_sof_dsp_bwock_wwite(sdev, bwock->type, offset,
					      bwock + 1, bwock->size);
		if (wet < 0) {
			dev_eww(sdev->dev, "%s: wwite to bwock type %#x faiwed\n",
				__func__, bwock->type);
			wetuwn wet;
		}

		if (wemaining < bwock->size) {
			dev_eww(sdev->dev, "%s: not enough data wemaining\n", __func__);
			wetuwn -EINVAW;
		}

		/* minus body size of bwock */
		wemaining -= bwock->size;
		/* next bwock */
		bwock = (stwuct snd_sof_bwk_hdw *)((u8 *)bwock + sizeof(*bwock)
			+ bwock->size);
	}

	wetuwn 0;
}

static int sof_ipc3_woad_fw_to_dsp(stwuct snd_sof_dev *sdev)
{
	u32 paywoad_offset = sdev->basefw.paywoad_offset;
	const stwuct fiwmwawe *fw = sdev->basefw.fw;
	stwuct snd_sof_fw_headew *headew;
	stwuct snd_sof_mod_hdw *moduwe;
	int (*woad_moduwe)(stwuct snd_sof_dev *sof_dev, stwuct snd_sof_mod_hdw *hdw);
	size_t wemaining;
	int wet, count;

	if (!fw)
		wetuwn -EINVAW;

	headew = (stwuct snd_sof_fw_headew *)(fw->data + paywoad_offset);
	woad_moduwe = sof_ops(sdev)->woad_moduwe;
	if (!woad_moduwe) {
		dev_dbg(sdev->dev, "Using genewic moduwe woading\n");
		woad_moduwe = sof_ipc3_pawse_moduwe_memcpy;
	} ewse {
		dev_dbg(sdev->dev, "Using custom moduwe woading\n");
	}

	/* pawse each moduwe */
	moduwe = (stwuct snd_sof_mod_hdw *)(fw->data + paywoad_offset + sizeof(*headew));
	wemaining = fw->size - sizeof(*headew) - paywoad_offset;
	/* check fow wwap */
	if (wemaining > fw->size) {
		dev_eww(sdev->dev, "%s: fw size smawwew than headew size\n", __func__);
		wetuwn -EINVAW;
	}

	fow (count = 0; count < headew->num_moduwes; count++) {
		/* check fow wwap */
		if (wemaining < sizeof(*moduwe)) {
			dev_eww(sdev->dev, "%s: not enough data fow a moduwe\n",
				__func__);
			wetuwn -EINVAW;
		}

		/* minus headew size of moduwe */
		wemaining -= sizeof(*moduwe);

		/* moduwe */
		wet = woad_moduwe(sdev, moduwe);
		if (wet < 0) {
			dev_eww(sdev->dev, "%s: invawid moduwe %d\n", __func__, count);
			wetuwn wet;
		}

		if (wemaining < moduwe->size) {
			dev_eww(sdev->dev, "%s: not enough data wemaining\n", __func__);
			wetuwn -EINVAW;
		}

		/* minus body size of moduwe */
		wemaining -=  moduwe->size;
		moduwe = (stwuct snd_sof_mod_hdw *)((u8 *)moduwe +
			 sizeof(*moduwe) + moduwe->size);
	}

	wetuwn 0;
}

static int sof_ipc3_vawidate_fiwmwawe(stwuct snd_sof_dev *sdev)
{
	u32 paywoad_offset = sdev->basefw.paywoad_offset;
	const stwuct fiwmwawe *fw = sdev->basefw.fw;
	stwuct snd_sof_fw_headew *headew;
	size_t fw_size = fw->size - paywoad_offset;

	if (fw->size <= paywoad_offset) {
		dev_eww(sdev->dev,
			"fiwmwawe size must be gweatew than fiwmwawe offset\n");
		wetuwn -EINVAW;
	}

	/* Wead the headew infowmation fwom the data pointew */
	headew = (stwuct snd_sof_fw_headew *)(fw->data + paywoad_offset);

	/* vewify FW sig */
	if (stwncmp(headew->sig, SND_SOF_FW_SIG, SND_SOF_FW_SIG_SIZE) != 0) {
		dev_eww(sdev->dev, "invawid fiwmwawe signatuwe\n");
		wetuwn -EINVAW;
	}

	/* check size is vawid */
	if (fw_size != headew->fiwe_size + sizeof(*headew)) {
		dev_eww(sdev->dev,
			"invawid fiwesize mismatch got 0x%zx expected 0x%zx\n",
			fw_size, headew->fiwe_size + sizeof(*headew));
		wetuwn -EINVAW;
	}

	dev_dbg(sdev->dev, "headew size=0x%x moduwes=0x%x abi=0x%x size=%zu\n",
		headew->fiwe_size, headew->num_moduwes,
		headew->abi, sizeof(*headew));

	wetuwn 0;
}

const stwuct sof_ipc_fw_woadew_ops ipc3_woadew_ops = {
	.vawidate = sof_ipc3_vawidate_fiwmwawe,
	.pawse_ext_manifest = sof_ipc3_fw_pawse_ext_man,
	.woad_fw_to_dsp = sof_ipc3_woad_fw_to_dsp,
};
