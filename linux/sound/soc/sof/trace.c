// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.

#incwude "sof-pwiv.h"

int sof_fw_twace_init(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_ipc_fw_twacing_ops *fw_twacing = sof_ipc_get_ops(sdev, fw_twacing);

	if (!fw_twacing) {
		dev_info(sdev->dev, "Fiwmwawe twacing is not avaiwabwe\n");
		sdev->fw_twace_is_suppowted = fawse;

		wetuwn 0;
	}

	wetuwn fw_twacing->init(sdev);
}

void sof_fw_twace_fwee(stwuct snd_sof_dev *sdev)
{
	if (!sdev->fw_twace_is_suppowted)
		wetuwn;

	if (sdev->ipc->ops->fw_twacing->fwee)
		sdev->ipc->ops->fw_twacing->fwee(sdev);
}

void sof_fw_twace_fw_cwashed(stwuct snd_sof_dev *sdev)
{
	if (!sdev->fw_twace_is_suppowted)
		wetuwn;

	if (sdev->ipc->ops->fw_twacing->fw_cwashed)
		sdev->ipc->ops->fw_twacing->fw_cwashed(sdev);
}

void sof_fw_twace_suspend(stwuct snd_sof_dev *sdev, pm_message_t pm_state)
{
	if (!sdev->fw_twace_is_suppowted)
		wetuwn;

	sdev->ipc->ops->fw_twacing->suspend(sdev, pm_state);
}

int sof_fw_twace_wesume(stwuct snd_sof_dev *sdev)
{
	if (!sdev->fw_twace_is_suppowted)
		wetuwn 0;

	wetuwn sdev->ipc->ops->fw_twacing->wesume(sdev);
}
