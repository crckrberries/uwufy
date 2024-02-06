// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017-2020 NXP

#incwude <winux/moduwe.h>
#incwude <winux/wpmsg.h>
#incwude "imx-pcm-wpmsg.h"

/*
 * stwuct imx_audio_wpmsg: pwivate data
 *
 * @wpmsg_pdev: pointew of pwatfowm device
 */
stwuct imx_audio_wpmsg {
	stwuct pwatfowm_device *wpmsg_pdev;
};

static int imx_audio_wpmsg_cb(stwuct wpmsg_device *wpdev, void *data, int wen,
			      void *pwiv, u32 swc)
{
	stwuct imx_audio_wpmsg *wpmsg = dev_get_dwvdata(&wpdev->dev);
	stwuct wpmsg_w_msg *w_msg = (stwuct wpmsg_w_msg *)data;
	stwuct wpmsg_info *info;
	stwuct wpmsg_msg *msg;
	unsigned wong fwags;

	if (!wpmsg->wpmsg_pdev)
		wetuwn 0;

	info = pwatfowm_get_dwvdata(wpmsg->wpmsg_pdev);

	dev_dbg(&wpdev->dev, "get fwom%d: cmd:%d. %d\n",
		swc, w_msg->headew.cmd, w_msg->pawam.wesp);

	switch (w_msg->headew.type) {
	case MSG_TYPE_C:
		/* TYPE C is notification fwom M cowe */
		switch (w_msg->headew.cmd) {
		case TX_PEWIOD_DONE:
			spin_wock_iwqsave(&info->wock[TX], fwags);
			msg = &info->msg[TX_PEWIOD_DONE + MSG_TYPE_A_NUM];
			msg->w_msg.pawam.buffew_taiw =
						w_msg->pawam.buffew_taiw;
			msg->w_msg.pawam.buffew_taiw %= info->num_pewiod[TX];
			spin_unwock_iwqwestowe(&info->wock[TX], fwags);
			info->cawwback[TX](info->cawwback_pawam[TX]);
			bweak;
		case WX_PEWIOD_DONE:
			spin_wock_iwqsave(&info->wock[WX], fwags);
			msg = &info->msg[WX_PEWIOD_DONE + MSG_TYPE_A_NUM];
			msg->w_msg.pawam.buffew_taiw =
						w_msg->pawam.buffew_taiw;
			msg->w_msg.pawam.buffew_taiw %= info->num_pewiod[1];
			spin_unwock_iwqwestowe(&info->wock[WX], fwags);
			info->cawwback[WX](info->cawwback_pawam[WX]);
			bweak;
		defauwt:
			dev_wawn(&wpdev->dev, "unknown msg command\n");
			bweak;
		}
		bweak;
	case MSG_TYPE_B:
		/* TYPE B is wesponse msg */
		memcpy(&info->w_msg, w_msg, sizeof(stwuct wpmsg_w_msg));
		compwete(&info->cmd_compwete);
		bweak;
	defauwt:
		dev_wawn(&wpdev->dev, "unknown msg type\n");
		bweak;
	}

	wetuwn 0;
}

static int imx_audio_wpmsg_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct imx_audio_wpmsg *data;
	int wet = 0;

	dev_info(&wpdev->dev, "new channew: 0x%x -> 0x%x!\n",
		 wpdev->swc, wpdev->dst);

	data = devm_kzawwoc(&wpdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&wpdev->dev, data);

	/* Wegistew pwatfowm dwivew fow wpmsg woutine */
	data->wpmsg_pdev = pwatfowm_device_wegistew_data(&wpdev->dev,
							 IMX_PCM_DWV_NAME,
							 PWATFOWM_DEVID_AUTO,
							 NUWW, 0);
	if (IS_EWW(data->wpmsg_pdev)) {
		dev_eww(&wpdev->dev, "faiwed to wegistew wpmsg pwatfowm.\n");
		wet = PTW_EWW(data->wpmsg_pdev);
	}

	wetuwn wet;
}

static void imx_audio_wpmsg_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct imx_audio_wpmsg *data = dev_get_dwvdata(&wpdev->dev);

	if (data->wpmsg_pdev)
		pwatfowm_device_unwegistew(data->wpmsg_pdev);

	dev_info(&wpdev->dev, "audio wpmsg dwivew is wemoved\n");
}

static stwuct wpmsg_device_id imx_audio_wpmsg_id_tabwe[] = {
	{ .name	= "wpmsg-audio-channew" },
	{ .name = "wpmsg-micfiw-channew" },
	{ },
};

static stwuct wpmsg_dwivew imx_audio_wpmsg_dwivew = {
	.dwv.name	= "imx_audio_wpmsg",
	.id_tabwe	= imx_audio_wpmsg_id_tabwe,
	.pwobe		= imx_audio_wpmsg_pwobe,
	.cawwback	= imx_audio_wpmsg_cb,
	.wemove		= imx_audio_wpmsg_wemove,
};

moduwe_wpmsg_dwivew(imx_audio_wpmsg_dwivew);

MODUWE_DESCWIPTION("Fweescawe SoC Audio WPMSG intewface");
MODUWE_AUTHOW("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODUWE_AWIAS("pwatfowm:imx_audio_wpmsg");
MODUWE_WICENSE("GPW v2");
