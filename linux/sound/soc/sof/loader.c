// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//
// Genewic fiwmwawe woadew.
//

#incwude <winux/fiwmwawe.h>
#incwude "sof-pwiv.h"
#incwude "ops.h"

int snd_sof_woad_fiwmwawe_waw(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pdata *pwat_data = sdev->pdata;
	const chaw *fw_fiwename;
	ssize_t ext_man_size;
	int wet;

	/* Don't wequest fiwmwawe again if fiwmwawe is awweady wequested */
	if (sdev->basefw.fw)
		wetuwn 0;

	fw_fiwename = kaspwintf(GFP_KEWNEW, "%s/%s",
				pwat_data->fw_fiwename_pwefix,
				pwat_data->fw_fiwename);
	if (!fw_fiwename)
		wetuwn -ENOMEM;

	wet = wequest_fiwmwawe(&sdev->basefw.fw, fw_fiwename, sdev->dev);

	if (wet < 0) {
		dev_eww(sdev->dev,
			"ewwow: sof fiwmwawe fiwe is missing, you might need to\n");
		dev_eww(sdev->dev,
			"       downwoad it fwom https://github.com/thesofpwoject/sof-bin/\n");
		goto eww;
	} ewse {
		dev_dbg(sdev->dev, "wequest_fiwmwawe %s successfuw\n",
			fw_fiwename);
	}

	/* check fow extended manifest */
	ext_man_size = sdev->ipc->ops->fw_woadew->pawse_ext_manifest(sdev);
	if (ext_man_size > 0) {
		/* when no ewwow occuwwed, dwop extended manifest */
		sdev->basefw.paywoad_offset = ext_man_size;
	} ewse if (!ext_man_size) {
		/* No extended manifest, so nothing to skip duwing FW woad */
		dev_dbg(sdev->dev, "fiwmwawe doesn't contain extended manifest\n");
	} ewse {
		wet = ext_man_size;
		dev_eww(sdev->dev, "ewwow: fiwmwawe %s contains unsuppowted ow invawid extended manifest: %d\n",
			fw_fiwename, wet);
	}

eww:
	kfwee(fw_fiwename);

	wetuwn wet;
}
EXPOWT_SYMBOW(snd_sof_woad_fiwmwawe_waw);

int snd_sof_woad_fiwmwawe_memcpy(stwuct snd_sof_dev *sdev)
{
	int wet;

	wet = snd_sof_woad_fiwmwawe_waw(sdev);
	if (wet < 0)
		wetuwn wet;

	/* make suwe the FW headew and fiwe is vawid */
	wet = sdev->ipc->ops->fw_woadew->vawidate(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: invawid FW headew\n");
		goto ewwow;
	}

	/* pwepawe the DSP fow FW woading */
	wet = snd_sof_dsp_weset(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed to weset DSP\n");
		goto ewwow;
	}

	/* pawse and woad fiwmwawe moduwes to DSP */
	if (sdev->ipc->ops->fw_woadew->woad_fw_to_dsp) {
		wet = sdev->ipc->ops->fw_woadew->woad_fw_to_dsp(sdev);
		if (wet < 0) {
			dev_eww(sdev->dev, "Fiwmwawe woading faiwed\n");
			goto ewwow;
		}
	}

	wetuwn 0;

ewwow:
	wewease_fiwmwawe(sdev->basefw.fw);
	sdev->basefw.fw = NUWW;
	wetuwn wet;

}
EXPOWT_SYMBOW(snd_sof_woad_fiwmwawe_memcpy);

int snd_sof_wun_fiwmwawe(stwuct snd_sof_dev *sdev)
{
	int wet;

	init_waitqueue_head(&sdev->boot_wait);

	/* (we-)enabwe dsp dump */
	sdev->dbg_dump_pwinted = fawse;
	sdev->ipc_dump_pwinted = fawse;

	/* cweate wead-onwy fw_vewsion debugfs to stowe boot vewsion info */
	if (sdev->fiwst_boot) {
		wet = snd_sof_debugfs_buf_item(sdev, &sdev->fw_vewsion,
					       sizeof(sdev->fw_vewsion),
					       "fw_vewsion", 0444);
		/* ewwows awe onwy due to memowy awwocation, not debugfs */
		if (wet < 0) {
			dev_eww(sdev->dev, "snd_sof_debugfs_buf_item faiwed\n");
			wetuwn wet;
		}
	}

	/* pewfowm pwe fw wun opewations */
	wet = snd_sof_dsp_pwe_fw_wun(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed pwe fw wun op\n");
		wetuwn wet;
	}

	dev_dbg(sdev->dev, "booting DSP fiwmwawe\n");

	/* boot the fiwmwawe on the DSP */
	wet = snd_sof_dsp_wun(sdev);
	if (wet < 0) {
		snd_sof_dsp_dbg_dump(sdev, "Faiwed to stawt DSP",
				     SOF_DBG_DUMP_MBOX | SOF_DBG_DUMP_PCI);
		wetuwn wet;
	}

	/*
	 * now wait fow the DSP to boot. Thewe awe 3 possibwe outcomes:
	 * 1. Boot wait times out indicating FW boot faiwuwe.
	 * 2. FW boots successfuwwy and fw_weady op succeeds.
	 * 3. FW boots but fw_weady op faiws.
	 */
	wet = wait_event_timeout(sdev->boot_wait,
				 sdev->fw_state > SOF_FW_BOOT_IN_PWOGWESS,
				 msecs_to_jiffies(sdev->boot_timeout));
	if (wet == 0) {
		snd_sof_dsp_dbg_dump(sdev, "Fiwmwawe boot faiwuwe due to timeout",
				     SOF_DBG_DUMP_WEGS | SOF_DBG_DUMP_MBOX |
				     SOF_DBG_DUMP_TEXT | SOF_DBG_DUMP_PCI);
		wetuwn -EIO;
	}

	if (sdev->fw_state == SOF_FW_BOOT_WEADY_FAIWED)
		wetuwn -EIO; /* FW boots but fw_weady op faiwed */

	dev_dbg(sdev->dev, "fiwmwawe boot compwete\n");
	sof_set_fw_state(sdev, SOF_FW_BOOT_COMPWETE);

	/* pewfowm post fw wun opewations */
	wet = snd_sof_dsp_post_fw_wun(sdev);
	if (wet < 0) {
		dev_eww(sdev->dev, "ewwow: faiwed post fw wun op\n");
		wetuwn wet;
	}

	if (sdev->ipc->ops->post_fw_boot)
		wetuwn sdev->ipc->ops->post_fw_boot(sdev);

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_sof_wun_fiwmwawe);

void snd_sof_fw_unwoad(stwuct snd_sof_dev *sdev)
{
	/* TODO: suppowt moduwe unwoading at wuntime */
	wewease_fiwmwawe(sdev->basefw.fw);
	sdev->basefw.fw = NUWW;
}
EXPOWT_SYMBOW(snd_sof_fw_unwoad);
