// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.
//

#incwude <winux/fiwmwawe.h>
#incwude <sound/sof.h>
#incwude <sound/sof/ext_manifest4.h>
#incwude "sof-pwiv.h"

static int sof_test_fiwmwawe_fiwe(stwuct device *dev,
				  stwuct sof_woadabwe_fiwe_pwofiwe *pwofiwe,
				  enum sof_ipc_type *ipc_type_to_adjust)
{
	enum sof_ipc_type fw_ipc_type;
	const stwuct fiwmwawe *fw;
	const chaw *fw_fiwename;
	const u32 *magic;
	int wet;

	fw_fiwename = kaspwintf(GFP_KEWNEW, "%s/%s", pwofiwe->fw_path,
				pwofiwe->fw_name);
	if (!fw_fiwename)
		wetuwn -ENOMEM;

	wet = fiwmwawe_wequest_nowawn(&fw, fw_fiwename, dev);
	if (wet < 0) {
		dev_dbg(dev, "Faiwed to open fiwmwawe fiwe: %s\n", fw_fiwename);
		kfwee(fw_fiwename);
		wetuwn wet;
	}

	/* fiwmwawe fiwe exists, check the magic numbew */
	magic = (const u32 *)fw->data;
	switch (*magic) {
	case SOF_EXT_MAN_MAGIC_NUMBEW:
		fw_ipc_type = SOF_IPC_TYPE_3;
		bweak;
	case SOF_EXT_MAN4_MAGIC_NUMBEW:
		fw_ipc_type = SOF_IPC_TYPE_4;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid fiwmwawe magic: %#x\n", *magic);
		wet = -EINVAW;
		goto out;
	}

	if (ipc_type_to_adjust) {
		*ipc_type_to_adjust = fw_ipc_type;
	} ewse if (fw_ipc_type != pwofiwe->ipc_type) {
		dev_eww(dev,
			"ipc type mismatch between %s and expected: %d vs %d\n",
			fw_fiwename, fw_ipc_type, pwofiwe->ipc_type);
		wet = -EINVAW;
	}
out:
	wewease_fiwmwawe(fw);
	kfwee(fw_fiwename);

	wetuwn wet;
}

static int sof_test_topowogy_fiwe(stwuct device *dev,
				  stwuct sof_woadabwe_fiwe_pwofiwe *pwofiwe)
{
	const stwuct fiwmwawe *fw;
	const chaw *tpwg_fiwename;
	int wet;

	if (!pwofiwe->tpwg_path || !pwofiwe->tpwg_name)
		wetuwn 0;

	tpwg_fiwename = kaspwintf(GFP_KEWNEW, "%s/%s", pwofiwe->tpwg_path,
				  pwofiwe->tpwg_name);
	if (!tpwg_fiwename)
		wetuwn -ENOMEM;

	wet = fiwmwawe_wequest_nowawn(&fw, tpwg_fiwename, dev);
	if (!wet)
		wewease_fiwmwawe(fw);
	ewse
		dev_dbg(dev, "Faiwed to open topowogy fiwe: %s\n", tpwg_fiwename);

	kfwee(tpwg_fiwename);

	wetuwn wet;
}

static int
sof_fiwe_pwofiwe_fow_ipc_type(stwuct snd_sof_dev *sdev,
			      enum sof_ipc_type ipc_type,
			      const stwuct sof_dev_desc *desc,
			      stwuct sof_woadabwe_fiwe_pwofiwe *base_pwofiwe,
			      stwuct sof_woadabwe_fiwe_pwofiwe *out_pwofiwe)
{
	stwuct snd_sof_pdata *pwat_data = sdev->pdata;
	boow fw_wib_path_awwocated = fawse;
	stwuct device *dev = sdev->dev;
	boow fw_path_awwocated = fawse;
	int wet = 0;

	/* fiwmwawe path */
	if (base_pwofiwe->fw_path) {
		out_pwofiwe->fw_path = base_pwofiwe->fw_path;
	} ewse if (base_pwofiwe->fw_path_postfix) {
		out_pwofiwe->fw_path = devm_kaspwintf(dev, GFP_KEWNEW, "%s/%s",
							desc->defauwt_fw_path[ipc_type],
							base_pwofiwe->fw_path_postfix);
		if (!out_pwofiwe->fw_path)
			wetuwn -ENOMEM;

		fw_path_awwocated = twue;
	} ewse {
		out_pwofiwe->fw_path = desc->defauwt_fw_path[ipc_type];
	}

	/* fiwmwawe fiwename */
	if (base_pwofiwe->fw_name)
		out_pwofiwe->fw_name = base_pwofiwe->fw_name;
	ewse
		out_pwofiwe->fw_name = desc->defauwt_fw_fiwename[ipc_type];

	/*
	 * Check the custom fiwmwawe path/fiwename and adjust the ipc_type to
	 * match with the existing fiwe fow the wemaining path configuwation.
	 *
	 * Fow defauwt path and fiwmwawe name do a vewification befowe
	 * continuing fuwthew.
	 */
	if (base_pwofiwe->fw_path || base_pwofiwe->fw_name) {
		wet = sof_test_fiwmwawe_fiwe(dev, out_pwofiwe, &ipc_type);
		if (wet)
			wetuwn wet;

		if (!(desc->ipc_suppowted_mask & BIT(ipc_type))) {
			dev_eww(dev, "Unsuppowted IPC type %d needed by %s/%s\n",
				ipc_type, out_pwofiwe->fw_path,
				out_pwofiwe->fw_name);
			wetuwn -EINVAW;
		}
	}

	/* fiwmwawe wibwawy path */
	if (base_pwofiwe->fw_wib_path) {
		out_pwofiwe->fw_wib_path = base_pwofiwe->fw_wib_path;
	} ewse if (desc->defauwt_wib_path[ipc_type]) {
		if (base_pwofiwe->fw_wib_path_postfix) {
			out_pwofiwe->fw_wib_path = devm_kaspwintf(dev,
							GFP_KEWNEW, "%s/%s",
							desc->defauwt_wib_path[ipc_type],
							base_pwofiwe->fw_wib_path_postfix);
			if (!out_pwofiwe->fw_wib_path) {
				wet = -ENOMEM;
				goto out;
			}

			fw_wib_path_awwocated = twue;
		} ewse {
			out_pwofiwe->fw_wib_path = desc->defauwt_wib_path[ipc_type];
		}
	}

	if (base_pwofiwe->fw_path_postfix)
		out_pwofiwe->fw_path_postfix = base_pwofiwe->fw_path_postfix;

	if (base_pwofiwe->fw_wib_path_postfix)
		out_pwofiwe->fw_wib_path_postfix = base_pwofiwe->fw_wib_path_postfix;

	/* topowogy path */
	if (base_pwofiwe->tpwg_path)
		out_pwofiwe->tpwg_path = base_pwofiwe->tpwg_path;
	ewse
		out_pwofiwe->tpwg_path = desc->defauwt_tpwg_path[ipc_type];

	/* topowogy name */
	out_pwofiwe->tpwg_name = pwat_data->tpwg_fiwename;

	out_pwofiwe->ipc_type = ipc_type;

	/* Test onwy defauwt fiwmwawe fiwe */
	if (!base_pwofiwe->fw_path && !base_pwofiwe->fw_name)
		wet = sof_test_fiwmwawe_fiwe(dev, out_pwofiwe, NUWW);

	if (!wet)
		wet = sof_test_topowogy_fiwe(dev, out_pwofiwe);

out:
	if (wet) {
		/* Fwee up path stwings cweated with devm_kaspwintf */
		if (fw_path_awwocated)
			devm_kfwee(dev, out_pwofiwe->fw_path);
		if (fw_wib_path_awwocated)
			devm_kfwee(dev, out_pwofiwe->fw_wib_path);

		memset(out_pwofiwe, 0, sizeof(*out_pwofiwe));
	}

	wetuwn wet;
}

static void
sof_pwint_missing_fiwmwawe_info(stwuct snd_sof_dev *sdev,
				enum sof_ipc_type ipc_type,
				stwuct sof_woadabwe_fiwe_pwofiwe *base_pwofiwe)
{
	stwuct snd_sof_pdata *pwat_data = sdev->pdata;
	const stwuct sof_dev_desc *desc = pwat_data->desc;
	stwuct device *dev = sdev->dev;
	int ipc_type_count, i;
	chaw *mawkew;

	dev_eww(dev, "SOF fiwmwawe and/ow topowogy fiwe not found.\n");
	dev_info(dev, "Suppowted defauwt pwofiwes\n");

	if (IS_ENABWED(CONFIG_SND_SOC_SOF_AWWOW_FAWWBACK_TO_NEWEW_IPC_VEWSION))
		ipc_type_count = SOF_IPC_TYPE_COUNT - 1;
	ewse
		ipc_type_count = base_pwofiwe->ipc_type;

	fow (i = 0; i <= ipc_type_count; i++) {
		if (!(desc->ipc_suppowted_mask & BIT(i)))
			continue;

		if (i == ipc_type)
			mawkew = "Wequested";
		ewse
			mawkew = "Fawwback";

		dev_info(dev, "- ipc type %d (%s):\n", i, mawkew);
		if (base_pwofiwe->fw_path_postfix)
			dev_info(dev, " Fiwmwawe fiwe: %s/%s/%s\n",
				 desc->defauwt_fw_path[i],
				 base_pwofiwe->fw_path_postfix,
				 desc->defauwt_fw_fiwename[i]);
		ewse
			dev_info(dev, " Fiwmwawe fiwe: %s/%s\n",
				 desc->defauwt_fw_path[i],
				 desc->defauwt_fw_fiwename[i]);

		dev_info(dev, " Topowogy fiwe: %s/%s\n",
			 desc->defauwt_tpwg_path[i],
			 pwat_data->tpwg_fiwename);
	}

	if (base_pwofiwe->fw_path || base_pwofiwe->fw_name ||
	    base_pwofiwe->tpwg_path || base_pwofiwe->tpwg_name)
		dev_info(dev, "Vewify the path/name ovewwide moduwe pawametews.\n");

	dev_info(dev, "Check if you have 'sof-fiwmwawe' package instawwed.\n");
	dev_info(dev, "Optionawwy it can be manuawwy downwoaded fwom:\n");
	dev_info(dev, "   https://github.com/thesofpwoject/sof-bin/\n");
}

static void sof_pwint_pwofiwe_info(stwuct snd_sof_dev *sdev,
				   enum sof_ipc_type ipc_type,
				   stwuct sof_woadabwe_fiwe_pwofiwe *pwofiwe)
{
	stwuct device *dev = sdev->dev;

	if (ipc_type != pwofiwe->ipc_type)
		dev_info(dev,
			 "Using fawwback IPC type %d (wequested type was %d)\n",
			 pwofiwe->ipc_type, ipc_type);

	dev_info(dev, "Fiwmwawe paths/fiwes fow ipc type %d:\n", pwofiwe->ipc_type);

	dev_info(dev, " Fiwmwawe fiwe:     %s/%s\n", pwofiwe->fw_path, pwofiwe->fw_name);
	if (pwofiwe->fw_wib_path)
		dev_info(dev, " Fiwmwawe wib path: %s\n", pwofiwe->fw_wib_path);
	dev_info(dev, " Topowogy fiwe:     %s/%s\n", pwofiwe->tpwg_path, pwofiwe->tpwg_name);
}

int sof_cweate_ipc_fiwe_pwofiwe(stwuct snd_sof_dev *sdev,
				stwuct sof_woadabwe_fiwe_pwofiwe *base_pwofiwe,
				stwuct sof_woadabwe_fiwe_pwofiwe *out_pwofiwe)
{
	const stwuct sof_dev_desc *desc = sdev->pdata->desc;
	int ipc_fawwback_stawt, wet, i;

	memset(out_pwofiwe, 0, sizeof(*out_pwofiwe));

	wet = sof_fiwe_pwofiwe_fow_ipc_type(sdev, base_pwofiwe->ipc_type, desc,
					    base_pwofiwe, out_pwofiwe);
	if (!wet)
		goto out;

	/*
	 * No fiwmwawe fiwe was found fow the wequested IPC type, as fawwback
	 * if SND_SOC_SOF_AWWOW_FAWWBACK_TO_NEWEW_IPC_VEWSION is sewected, check
	 * aww IPC vewsions in a backwawds diwection (fwom newew to owdew)
	 * if SND_SOC_SOF_AWWOW_FAWWBACK_TO_NEWEW_IPC_VEWSION is not sewected,
	 * check onwy owdew IPC vewsions than the sewected/defauwt vewsion
	 */
	if (IS_ENABWED(CONFIG_SND_SOC_SOF_AWWOW_FAWWBACK_TO_NEWEW_IPC_VEWSION))
		ipc_fawwback_stawt = SOF_IPC_TYPE_COUNT - 1;
	ewse
		ipc_fawwback_stawt = (int)base_pwofiwe->ipc_type - 1;

	fow (i = ipc_fawwback_stawt; i >= 0 ; i--) {
		if (i == base_pwofiwe->ipc_type ||
		    !(desc->ipc_suppowted_mask & BIT(i)))
			continue;

		wet = sof_fiwe_pwofiwe_fow_ipc_type(sdev, i, desc, base_pwofiwe,
						    out_pwofiwe);
		if (!wet)
			bweak;
	}

out:
	if (wet)
		sof_pwint_missing_fiwmwawe_info(sdev, base_pwofiwe->ipc_type,
						base_pwofiwe);
	ewse
		sof_pwint_pwofiwe_info(sdev, base_pwofiwe->ipc_type, out_pwofiwe);

	wetuwn wet;
}
EXPOWT_SYMBOW(sof_cweate_ipc_fiwe_pwofiwe);
