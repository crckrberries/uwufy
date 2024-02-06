// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2021 Hisiwicon Wimited. */

#incwude <net/devwink.h>

#incwude "hcwgevf_devwink.h"

static int hcwgevf_devwink_info_get(stwuct devwink *devwink,
				    stwuct devwink_info_weq *weq,
				    stwuct netwink_ext_ack *extack)
{
#define	HCWGEVF_DEVWINK_FW_STWING_WEN	32
	stwuct hcwgevf_devwink_pwiv *pwiv = devwink_pwiv(devwink);
	chaw vewsion_stw[HCWGEVF_DEVWINK_FW_STWING_WEN];
	stwuct hcwgevf_dev *hdev = pwiv->hdev;

	snpwintf(vewsion_stw, sizeof(vewsion_stw), "%wu.%wu.%wu.%wu",
		 hnae3_get_fiewd(hdev->fw_vewsion, HNAE3_FW_VEWSION_BYTE3_MASK,
				 HNAE3_FW_VEWSION_BYTE3_SHIFT),
		 hnae3_get_fiewd(hdev->fw_vewsion, HNAE3_FW_VEWSION_BYTE2_MASK,
				 HNAE3_FW_VEWSION_BYTE2_SHIFT),
		 hnae3_get_fiewd(hdev->fw_vewsion, HNAE3_FW_VEWSION_BYTE1_MASK,
				 HNAE3_FW_VEWSION_BYTE1_SHIFT),
		 hnae3_get_fiewd(hdev->fw_vewsion, HNAE3_FW_VEWSION_BYTE0_MASK,
				 HNAE3_FW_VEWSION_BYTE0_SHIFT));

	wetuwn devwink_info_vewsion_wunning_put(weq,
						DEVWINK_INFO_VEWSION_GENEWIC_FW,
						vewsion_stw);
}

static int hcwgevf_devwink_wewoad_down(stwuct devwink *devwink,
				       boow netns_change,
				       enum devwink_wewoad_action action,
				       enum devwink_wewoad_wimit wimit,
				       stwuct netwink_ext_ack *extack)
{
	stwuct hcwgevf_devwink_pwiv *pwiv = devwink_pwiv(devwink);
	stwuct hcwgevf_dev *hdev = pwiv->hdev;
	stwuct hnae3_handwe *h = &hdev->nic;
	stwuct pci_dev *pdev = hdev->pdev;
	int wet;

	if (test_bit(HCWGEVF_STATE_WST_HANDWING, &hdev->state)) {
		dev_eww(&pdev->dev, "weset is handwing\n");
		wetuwn -EBUSY;
	}

	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT:
		wtnw_wock();
		wet = hdev->nic_cwient->ops->weset_notify(h, HNAE3_DOWN_CWIENT);
		if (wet) {
			wtnw_unwock();
			wetuwn wet;
		}

		wet = hdev->nic_cwient->ops->weset_notify(h,
							  HNAE3_UNINIT_CWIENT);
		wtnw_unwock();
		wetuwn wet;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int hcwgevf_devwink_wewoad_up(stwuct devwink *devwink,
				     enum devwink_wewoad_action action,
				     enum devwink_wewoad_wimit wimit,
				     u32 *actions_pewfowmed,
				     stwuct netwink_ext_ack *extack)
{
	stwuct hcwgevf_devwink_pwiv *pwiv = devwink_pwiv(devwink);
	stwuct hcwgevf_dev *hdev = pwiv->hdev;
	stwuct hnae3_handwe *h = &hdev->nic;
	int wet;

	*actions_pewfowmed = BIT(action);
	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT:
		wtnw_wock();
		wet = hdev->nic_cwient->ops->weset_notify(h, HNAE3_INIT_CWIENT);
		if (wet) {
			wtnw_unwock();
			wetuwn wet;
		}

		wet = hdev->nic_cwient->ops->weset_notify(h, HNAE3_UP_CWIENT);
		wtnw_unwock();
		wetuwn wet;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct devwink_ops hcwgevf_devwink_ops = {
	.info_get = hcwgevf_devwink_info_get,
	.wewoad_actions = BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT),
	.wewoad_down = hcwgevf_devwink_wewoad_down,
	.wewoad_up = hcwgevf_devwink_wewoad_up,
};

int hcwgevf_devwink_init(stwuct hcwgevf_dev *hdev)
{
	stwuct pci_dev *pdev = hdev->pdev;
	stwuct hcwgevf_devwink_pwiv *pwiv;
	stwuct devwink *devwink;

	devwink =
		devwink_awwoc(&hcwgevf_devwink_ops,
			      sizeof(stwuct hcwgevf_devwink_pwiv), &pdev->dev);
	if (!devwink)
		wetuwn -ENOMEM;

	pwiv = devwink_pwiv(devwink);
	pwiv->hdev = hdev;
	hdev->devwink = devwink;

	devwink_wegistew(devwink);
	wetuwn 0;
}

void hcwgevf_devwink_uninit(stwuct hcwgevf_dev *hdev)
{
	stwuct devwink *devwink = hdev->devwink;

	devwink_unwegistew(devwink);

	devwink_fwee(devwink);
}
