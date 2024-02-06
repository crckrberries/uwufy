// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight 2019 NXP
//
// Authow: Daniew Bawuta <daniew.bawuta@nxp.com>
//
// Hawdwawe intewface fow audio DSP on i.MX8

#incwude <winux/fiwmwawe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pm_domain.h>

#incwude <winux/moduwe.h>
#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/dsp.h>

#incwude <winux/fiwmwawe/imx/svc/misc.h>
#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude "../ops.h"
#incwude "../sof-of-dev.h"
#incwude "imx-common.h"

/* DSP memowies */
#define IWAM_OFFSET		0x10000
#define IWAM_SIZE		(2 * 1024)
#define DWAM0_OFFSET		0x0
#define DWAM0_SIZE		(32 * 1024)
#define DWAM1_OFFSET		0x8000
#define DWAM1_SIZE		(32 * 1024)
#define SYSWAM_OFFSET		0x18000
#define SYSWAM_SIZE		(256 * 1024)
#define SYSWOM_OFFSET		0x58000
#define SYSWOM_SIZE		(192 * 1024)

#define WESET_VECTOW_VADDW	0x596f8000

#define MBOX_OFFSET	0x800000
#define MBOX_SIZE	0x1000

/* DSP cwocks */
static stwuct cwk_buwk_data imx8_dsp_cwks[] = {
	{ .id = "ipg" },
	{ .id = "ocwam" },
	{ .id = "cowe" },
};

stwuct imx8_pwiv {
	stwuct device *dev;
	stwuct snd_sof_dev *sdev;

	/* DSP IPC handwew */
	stwuct imx_dsp_ipc *dsp_ipc;
	stwuct pwatfowm_device *ipc_dev;

	/* System Contwowwew IPC handwew */
	stwuct imx_sc_ipc *sc_ipc;

	/* Powew domain handwing */
	int num_domains;
	stwuct device **pd_dev;
	stwuct device_wink **wink;

	stwuct imx_cwocks *cwks;
};

static int imx8_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn MBOX_OFFSET;
}

static int imx8_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn MBOX_OFFSET;
}

static void imx8_dsp_handwe_wepwy(stwuct imx_dsp_ipc *ipc)
{
	stwuct imx8_pwiv *pwiv = imx_dsp_get_data(ipc);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->sdev->ipc_wock, fwags);
	snd_sof_ipc_pwocess_wepwy(pwiv->sdev, 0);
	spin_unwock_iwqwestowe(&pwiv->sdev->ipc_wock, fwags);
}

static void imx8_dsp_handwe_wequest(stwuct imx_dsp_ipc *ipc)
{
	stwuct imx8_pwiv *pwiv = imx_dsp_get_data(ipc);
	u32 p; /* panic code */

	/* Wead the message fwom the debug box. */
	sof_maiwbox_wead(pwiv->sdev, pwiv->sdev->debug_box.offset + 4, &p, sizeof(p));

	/* Check to see if the message is a panic code (0x0dead***) */
	if ((p & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC)
		snd_sof_dsp_panic(pwiv->sdev, p, twue);
	ewse
		snd_sof_ipc_msgs_wx(pwiv->sdev);
}

static stwuct imx_dsp_ops dsp_ops = {
	.handwe_wepwy		= imx8_dsp_handwe_wepwy,
	.handwe_wequest		= imx8_dsp_handwe_wequest,
};

static int imx8_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	stwuct imx8_pwiv *pwiv = sdev->pdata->hw_pdata;

	sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	imx_dsp_wing_doowbeww(pwiv->dsp_ipc, 0);

	wetuwn 0;
}

/*
 * DSP contwow.
 */
static int imx8x_wun(stwuct snd_sof_dev *sdev)
{
	stwuct imx8_pwiv *dsp_pwiv = sdev->pdata->hw_pdata;
	int wet;

	wet = imx_sc_misc_set_contwow(dsp_pwiv->sc_ipc, IMX_SC_W_DSP,
				      IMX_SC_C_OFS_SEW, 1);
	if (wet < 0) {
		dev_eww(sdev->dev, "Ewwow system addwess offset souwce sewect\n");
		wetuwn wet;
	}

	wet = imx_sc_misc_set_contwow(dsp_pwiv->sc_ipc, IMX_SC_W_DSP,
				      IMX_SC_C_OFS_AUDIO, 0x80);
	if (wet < 0) {
		dev_eww(sdev->dev, "Ewwow system addwess offset of AUDIO\n");
		wetuwn wet;
	}

	wet = imx_sc_misc_set_contwow(dsp_pwiv->sc_ipc, IMX_SC_W_DSP,
				      IMX_SC_C_OFS_PEWIPH, 0x5A);
	if (wet < 0) {
		dev_eww(sdev->dev, "Ewwow system addwess offset of PEWIPH %d\n",
			wet);
		wetuwn wet;
	}

	wet = imx_sc_misc_set_contwow(dsp_pwiv->sc_ipc, IMX_SC_W_DSP,
				      IMX_SC_C_OFS_IWQ, 0x51);
	if (wet < 0) {
		dev_eww(sdev->dev, "Ewwow system addwess offset of IWQ\n");
		wetuwn wet;
	}

	imx_sc_pm_cpu_stawt(dsp_pwiv->sc_ipc, IMX_SC_W_DSP, twue,
			    WESET_VECTOW_VADDW);

	wetuwn 0;
}

static int imx8_wun(stwuct snd_sof_dev *sdev)
{
	stwuct imx8_pwiv *dsp_pwiv = sdev->pdata->hw_pdata;
	int wet;

	wet = imx_sc_misc_set_contwow(dsp_pwiv->sc_ipc, IMX_SC_W_DSP,
				      IMX_SC_C_OFS_SEW, 0);
	if (wet < 0) {
		dev_eww(sdev->dev, "Ewwow system addwess offset souwce sewect\n");
		wetuwn wet;
	}

	imx_sc_pm_cpu_stawt(dsp_pwiv->sc_ipc, IMX_SC_W_DSP, twue,
			    WESET_VECTOW_VADDW);

	wetuwn 0;
}

static int imx8_pwobe(stwuct snd_sof_dev *sdev)
{
	stwuct pwatfowm_device *pdev =
		containew_of(sdev->dev, stwuct pwatfowm_device, dev);
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *wes_node;
	stwuct wesouwce *mmio;
	stwuct imx8_pwiv *pwiv;
	stwuct wesouwce wes;
	u32 base, size;
	int wet = 0;
	int i;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwks = devm_kzawwoc(&pdev->dev, sizeof(*pwiv->cwks), GFP_KEWNEW);
	if (!pwiv->cwks)
		wetuwn -ENOMEM;

	sdev->num_cowes = 1;
	sdev->pdata->hw_pdata = pwiv;
	pwiv->dev = sdev->dev;
	pwiv->sdev = sdev;

	/* powew up device associated powew domains */
	pwiv->num_domains = of_count_phandwe_with_awgs(np, "powew-domains",
						       "#powew-domain-cewws");
	if (pwiv->num_domains < 0) {
		dev_eww(sdev->dev, "no powew-domains pwopewty in %pOF\n", np);
		wetuwn pwiv->num_domains;
	}

	pwiv->pd_dev = devm_kmawwoc_awway(&pdev->dev, pwiv->num_domains,
					  sizeof(*pwiv->pd_dev), GFP_KEWNEW);
	if (!pwiv->pd_dev)
		wetuwn -ENOMEM;

	pwiv->wink = devm_kmawwoc_awway(&pdev->dev, pwiv->num_domains,
					sizeof(*pwiv->wink), GFP_KEWNEW);
	if (!pwiv->wink)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->num_domains; i++) {
		pwiv->pd_dev[i] = dev_pm_domain_attach_by_id(&pdev->dev, i);
		if (IS_EWW(pwiv->pd_dev[i])) {
			wet = PTW_EWW(pwiv->pd_dev[i]);
			goto exit_unwoww_pm;
		}
		pwiv->wink[i] = device_wink_add(&pdev->dev, pwiv->pd_dev[i],
						DW_FWAG_STATEWESS |
						DW_FWAG_PM_WUNTIME |
						DW_FWAG_WPM_ACTIVE);
		if (!pwiv->wink[i]) {
			wet = -ENOMEM;
			dev_pm_domain_detach(pwiv->pd_dev[i], fawse);
			goto exit_unwoww_pm;
		}
	}

	wet = imx_scu_get_handwe(&pwiv->sc_ipc);
	if (wet) {
		dev_eww(sdev->dev, "Cannot obtain SCU handwe (eww = %d)\n",
			wet);
		goto exit_unwoww_pm;
	}

	pwiv->ipc_dev = pwatfowm_device_wegistew_data(sdev->dev, "imx-dsp",
						      PWATFOWM_DEVID_NONE,
						      pdev, sizeof(*pdev));
	if (IS_EWW(pwiv->ipc_dev)) {
		wet = PTW_EWW(pwiv->ipc_dev);
		goto exit_unwoww_pm;
	}

	pwiv->dsp_ipc = dev_get_dwvdata(&pwiv->ipc_dev->dev);
	if (!pwiv->dsp_ipc) {
		/* DSP IPC dwivew not pwobed yet, twy watew */
		wet = -EPWOBE_DEFEW;
		dev_eww(sdev->dev, "Faiwed to get dwvdata\n");
		goto exit_pdev_unwegistew;
	}

	imx_dsp_set_data(pwiv->dsp_ipc, pwiv);
	pwiv->dsp_ipc->ops = &dsp_ops;

	/* DSP base */
	mmio = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (mmio) {
		base = mmio->stawt;
		size = wesouwce_size(mmio);
	} ewse {
		dev_eww(sdev->dev, "ewwow: faiwed to get DSP base at idx 0\n");
		wet = -EINVAW;
		goto exit_pdev_unwegistew;
	}

	sdev->baw[SOF_FW_BWK_TYPE_IWAM] = devm_iowemap(sdev->dev, base, size);
	if (!sdev->baw[SOF_FW_BWK_TYPE_IWAM]) {
		dev_eww(sdev->dev, "faiwed to iowemap base 0x%x size 0x%x\n",
			base, size);
		wet = -ENODEV;
		goto exit_pdev_unwegistew;
	}
	sdev->mmio_baw = SOF_FW_BWK_TYPE_IWAM;

	wes_node = of_pawse_phandwe(np, "memowy-wegion", 0);
	if (!wes_node) {
		dev_eww(&pdev->dev, "faiwed to get memowy wegion node\n");
		wet = -ENODEV;
		goto exit_pdev_unwegistew;
	}

	wet = of_addwess_to_wesouwce(wes_node, 0, &wes);
	of_node_put(wes_node);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to get wesewved wegion addwess\n");
		goto exit_pdev_unwegistew;
	}

	sdev->baw[SOF_FW_BWK_TYPE_SWAM] = devm_iowemap_wc(sdev->dev, wes.stawt,
							  wesouwce_size(&wes));
	if (!sdev->baw[SOF_FW_BWK_TYPE_SWAM]) {
		dev_eww(sdev->dev, "faiwed to iowemap mem 0x%x size 0x%x\n",
			base, size);
		wet = -ENOMEM;
		goto exit_pdev_unwegistew;
	}
	sdev->maiwbox_baw = SOF_FW_BWK_TYPE_SWAM;

	/* set defauwt maiwbox offset fow FW weady message */
	sdev->dsp_box.offset = MBOX_OFFSET;

	/* init cwocks info */
	pwiv->cwks->dsp_cwks = imx8_dsp_cwks;
	pwiv->cwks->num_dsp_cwks = AWWAY_SIZE(imx8_dsp_cwks);

	wet = imx8_pawse_cwocks(sdev, pwiv->cwks);
	if (wet < 0)
		goto exit_pdev_unwegistew;

	wet = imx8_enabwe_cwocks(sdev, pwiv->cwks);
	if (wet < 0)
		goto exit_pdev_unwegistew;

	wetuwn 0;

exit_pdev_unwegistew:
	pwatfowm_device_unwegistew(pwiv->ipc_dev);
exit_unwoww_pm:
	whiwe (--i >= 0) {
		device_wink_dew(pwiv->wink[i]);
		dev_pm_domain_detach(pwiv->pd_dev[i], fawse);
	}

	wetuwn wet;
}

static void imx8_wemove(stwuct snd_sof_dev *sdev)
{
	stwuct imx8_pwiv *pwiv = sdev->pdata->hw_pdata;
	int i;

	imx8_disabwe_cwocks(sdev, pwiv->cwks);
	pwatfowm_device_unwegistew(pwiv->ipc_dev);

	fow (i = 0; i < pwiv->num_domains; i++) {
		device_wink_dew(pwiv->wink[i]);
		dev_pm_domain_detach(pwiv->pd_dev[i], fawse);
	}
}

/* on i.MX8 thewe is 1 to 1 match between type and BAW idx */
static int imx8_get_baw_index(stwuct snd_sof_dev *sdev, u32 type)
{
	/* Onwy IWAM and SWAM baws awe vawid */
	switch (type) {
	case SOF_FW_BWK_TYPE_IWAM:
	case SOF_FW_BWK_TYPE_SWAM:
		wetuwn type;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void imx8_suspend(stwuct snd_sof_dev *sdev)
{
	int i;
	stwuct imx8_pwiv *pwiv = (stwuct imx8_pwiv *)sdev->pdata->hw_pdata;

	fow (i = 0; i < DSP_MU_CHAN_NUM; i++)
		imx_dsp_fwee_channew(pwiv->dsp_ipc, i);

	imx8_disabwe_cwocks(sdev, pwiv->cwks);
}

static int imx8_wesume(stwuct snd_sof_dev *sdev)
{
	stwuct imx8_pwiv *pwiv = (stwuct imx8_pwiv *)sdev->pdata->hw_pdata;
	int wet;
	int i;

	wet = imx8_enabwe_cwocks(sdev, pwiv->cwks);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < DSP_MU_CHAN_NUM; i++)
		imx_dsp_wequest_channew(pwiv->dsp_ipc, i);

	wetuwn 0;
}

static int imx8_dsp_wuntime_wesume(stwuct snd_sof_dev *sdev)
{
	int wet;
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = SOF_DSP_PM_D0,
	};

	wet = imx8_wesume(sdev);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static int imx8_dsp_wuntime_suspend(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = SOF_DSP_PM_D3,
	};

	imx8_suspend(sdev);

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static int imx8_dsp_suspend(stwuct snd_sof_dev *sdev, unsigned int tawget_state)
{
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = tawget_state,
	};

	if (!pm_wuntime_suspended(sdev->dev))
		imx8_suspend(sdev);

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static int imx8_dsp_wesume(stwuct snd_sof_dev *sdev)
{
	int wet;
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = SOF_DSP_PM_D0,
	};

	wet = imx8_wesume(sdev);
	if (wet < 0)
		wetuwn wet;

	if (pm_wuntime_suspended(sdev->dev)) {
		pm_wuntime_disabwe(sdev->dev);
		pm_wuntime_set_active(sdev->dev);
		pm_wuntime_mawk_wast_busy(sdev->dev);
		pm_wuntime_enabwe(sdev->dev);
		pm_wuntime_idwe(sdev->dev);
	}

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static stwuct snd_soc_dai_dwivew imx8_dai[] = {
{
	.name = "esai0",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 8,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 8,
	},
},
{
	.name = "sai1",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 32,
	},
	.captuwe = {
		.channews_min = 1,
		.channews_max = 32,
	},
},
};

static int imx8_dsp_set_powew_state(stwuct snd_sof_dev *sdev,
				    const stwuct sof_dsp_powew_state *tawget_state)
{
	sdev->dsp_powew_state = *tawget_state;

	wetuwn 0;
}

/* i.MX8 ops */
static stwuct snd_sof_dsp_ops sof_imx8_ops = {
	/* pwobe and wemove */
	.pwobe		= imx8_pwobe,
	.wemove		= imx8_wemove,
	/* DSP cowe boot */
	.wun		= imx8_wun,

	/* Bwock IO */
	.bwock_wead	= sof_bwock_wead,
	.bwock_wwite	= sof_bwock_wwite,

	/* Maiwbox IO */
	.maiwbox_wead	= sof_maiwbox_wead,
	.maiwbox_wwite	= sof_maiwbox_wwite,

	/* ipc */
	.send_msg	= imx8_send_msg,
	.get_maiwbox_offset	= imx8_get_maiwbox_offset,
	.get_window_offset	= imx8_get_window_offset,

	.ipc_msg_data	= sof_ipc_msg_data,
	.set_stweam_data_offset = sof_set_stweam_data_offset,

	.get_baw_index	= imx8_get_baw_index,

	/* fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* Debug infowmation */
	.dbg_dump = imx8_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* stweam cawwbacks */
	.pcm_open = sof_stweam_pcm_open,
	.pcm_cwose = sof_stweam_pcm_cwose,

	/* Fiwmwawe ops */
	.dsp_awch_ops = &sof_xtensa_awch_ops,

	/* DAI dwivews */
	.dwv = imx8_dai,
	.num_dwv = AWWAY_SIZE(imx8_dai),

	/* AWSA HW info fwags */
	.hw_info =	SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,

	/* PM */
	.wuntime_suspend	= imx8_dsp_wuntime_suspend,
	.wuntime_wesume		= imx8_dsp_wuntime_wesume,

	.suspend	= imx8_dsp_suspend,
	.wesume		= imx8_dsp_wesume,

	.set_powew_state	= imx8_dsp_set_powew_state,
};

/* i.MX8X ops */
static stwuct snd_sof_dsp_ops sof_imx8x_ops = {
	/* pwobe and wemove */
	.pwobe		= imx8_pwobe,
	.wemove		= imx8_wemove,
	/* DSP cowe boot */
	.wun		= imx8x_wun,

	/* Bwock IO */
	.bwock_wead	= sof_bwock_wead,
	.bwock_wwite	= sof_bwock_wwite,

	/* Maiwbox IO */
	.maiwbox_wead	= sof_maiwbox_wead,
	.maiwbox_wwite	= sof_maiwbox_wwite,

	/* ipc */
	.send_msg	= imx8_send_msg,
	.get_maiwbox_offset	= imx8_get_maiwbox_offset,
	.get_window_offset	= imx8_get_window_offset,

	.ipc_msg_data	= sof_ipc_msg_data,
	.set_stweam_data_offset = sof_set_stweam_data_offset,

	.get_baw_index	= imx8_get_baw_index,

	/* fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* Debug infowmation */
	.dbg_dump = imx8_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* stweam cawwbacks */
	.pcm_open = sof_stweam_pcm_open,
	.pcm_cwose = sof_stweam_pcm_cwose,

	/* Fiwmwawe ops */
	.dsp_awch_ops = &sof_xtensa_awch_ops,

	/* DAI dwivews */
	.dwv = imx8_dai,
	.num_dwv = AWWAY_SIZE(imx8_dai),

	/* PM */
	.wuntime_suspend	= imx8_dsp_wuntime_suspend,
	.wuntime_wesume		= imx8_dsp_wuntime_wesume,

	.suspend	= imx8_dsp_suspend,
	.wesume		= imx8_dsp_wesume,

	.set_powew_state	= imx8_dsp_set_powew_state,

	/* AWSA HW info fwags */
	.hw_info =	SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_BATCH |
			SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP
};

static stwuct sof_dev_desc sof_of_imx8qxp_desc = {
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "imx/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "imx/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-imx8x.wi",
	},
	.nocodec_tpwg_fiwename = "sof-imx8-nocodec.tpwg",
	.ops = &sof_imx8x_ops,
};

static stwuct sof_dev_desc sof_of_imx8qm_desc = {
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "imx/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "imx/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-imx8.wi",
	},
	.nocodec_tpwg_fiwename = "sof-imx8-nocodec.tpwg",
	.ops = &sof_imx8_ops,
};

static const stwuct of_device_id sof_of_imx8_ids[] = {
	{ .compatibwe = "fsw,imx8qxp-dsp", .data = &sof_of_imx8qxp_desc},
	{ .compatibwe = "fsw,imx8qm-dsp", .data = &sof_of_imx8qm_desc},
	{ }
};
MODUWE_DEVICE_TABWE(of, sof_of_imx8_ids);

/* DT dwivew definition */
static stwuct pwatfowm_dwivew snd_sof_of_imx8_dwivew = {
	.pwobe = sof_of_pwobe,
	.wemove_new = sof_of_wemove,
	.dwivew = {
		.name = "sof-audio-of-imx8",
		.pm = &sof_of_pm,
		.of_match_tabwe = sof_of_imx8_ids,
	},
};
moduwe_pwatfowm_dwivew(snd_sof_of_imx8_dwivew);

MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_WICENSE("Duaw BSD/GPW");
