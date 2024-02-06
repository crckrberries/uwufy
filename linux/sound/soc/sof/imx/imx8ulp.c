// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight 2021-2022 NXP
//
// Authow: Peng Zhang <peng.zhang_8@nxp.com>
//
// Hawdwawe intewface fow audio DSP on i.MX8UWP

#incwude <winux/awm-smccc.h>
#incwude <winux/cwk.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/fiwmwawe/imx/dsp.h>
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/svc/misc.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_wesewved_mem.h>

#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>

#incwude "../ops.h"
#incwude "../sof-of-dev.h"
#incwude "imx-common.h"

#define FSW_SIP_HIFI_XWDC	0xc200000e

/* SIM Domain wegistew */
#define SYSCTWW0		0x8
#define EXECUTE_BIT		BIT(13)
#define WESET_BIT		BIT(16)
#define HIFI4_CWK_BIT		BIT(17)
#define PB_CWK_BIT		BIT(18)
#define PWAT_CWK_BIT		BIT(19)
#define DEBUG_WOGIC_BIT		BIT(25)

#define MBOX_OFFSET		0x800000
#define MBOX_SIZE		0x1000

static stwuct cwk_buwk_data imx8uwp_dsp_cwks[] = {
	{ .id = "cowe" },
	{ .id = "ipg" },
	{ .id = "ocwam" },
	{ .id = "mu" },
};

stwuct imx8uwp_pwiv {
	stwuct device *dev;
	stwuct snd_sof_dev *sdev;

	/* DSP IPC handwew */
	stwuct imx_dsp_ipc *dsp_ipc;
	stwuct pwatfowm_device *ipc_dev;

	stwuct wegmap *wegmap;
	stwuct imx_cwocks *cwks;
};

static void imx8uwp_sim_wpav_stawt(stwuct imx8uwp_pwiv *pwiv)
{
	/* Contwows the HiFi4 DSP Weset: 1 in weset, 0 out of weset */
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, WESET_BIT, 0);

	/* Weset HiFi4 DSP Debug wogic: 1 debug weset, 0  out of weset*/
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, DEBUG_WOGIC_BIT, 0);

	/* Staww HIFI4 DSP Execution: 1 staww, 0 wun */
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, EXECUTE_BIT, 0);
}

static int imx8uwp_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn MBOX_OFFSET;
}

static int imx8uwp_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn MBOX_OFFSET;
}

static void imx8uwp_dsp_handwe_wepwy(stwuct imx_dsp_ipc *ipc)
{
	stwuct imx8uwp_pwiv *pwiv = imx_dsp_get_data(ipc);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->sdev->ipc_wock, fwags);

	snd_sof_ipc_pwocess_wepwy(pwiv->sdev, 0);

	spin_unwock_iwqwestowe(&pwiv->sdev->ipc_wock, fwags);
}

static void imx8uwp_dsp_handwe_wequest(stwuct imx_dsp_ipc *ipc)
{
	stwuct imx8uwp_pwiv *pwiv = imx_dsp_get_data(ipc);
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
	.handwe_wepwy		= imx8uwp_dsp_handwe_wepwy,
	.handwe_wequest		= imx8uwp_dsp_handwe_wequest,
};

static int imx8uwp_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg)
{
	stwuct imx8uwp_pwiv *pwiv = sdev->pdata->hw_pdata;

	sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	imx_dsp_wing_doowbeww(pwiv->dsp_ipc, 0);

	wetuwn 0;
}

static int imx8uwp_wun(stwuct snd_sof_dev *sdev)
{
	stwuct imx8uwp_pwiv *pwiv = sdev->pdata->hw_pdata;

	imx8uwp_sim_wpav_stawt(pwiv);

	wetuwn 0;
}

static int imx8uwp_weset(stwuct snd_sof_dev *sdev)
{
	stwuct imx8uwp_pwiv *pwiv = sdev->pdata->hw_pdata;
	stwuct awm_smccc_wes smc_wesouwce;

	/* HiFi4 Pwatfowm Cwock Enabwe: 1 enabwed, 0 disabwed */
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, PWAT_CWK_BIT, PWAT_CWK_BIT);

	/* HiFi4 PBCWK cwock enabwe: 1 enabwed, 0 disabwed */
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, PB_CWK_BIT, PB_CWK_BIT);

	/* HiFi4 Cwock Enabwe: 1 enabwed, 0 disabwed */
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, HIFI4_CWK_BIT, HIFI4_CWK_BIT);

	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, WESET_BIT, WESET_BIT);
	usweep_wange(1, 2);

	/* Staww HIFI4 DSP Execution: 1 staww, 0 not staww */
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, EXECUTE_BIT, EXECUTE_BIT);
	usweep_wange(1, 2);

	awm_smccc_smc(FSW_SIP_HIFI_XWDC, 0, 0, 0, 0, 0, 0, 0, &smc_wesouwce);

	wetuwn 0;
}

static int imx8uwp_pwobe(stwuct snd_sof_dev *sdev)
{
	stwuct pwatfowm_device *pdev =
		containew_of(sdev->dev, stwuct pwatfowm_device, dev);
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *wes_node;
	stwuct wesouwce *mmio;
	stwuct imx8uwp_pwiv *pwiv;
	stwuct wesouwce wes;
	u32 base, size;
	int wet = 0;

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

	/* System integwation moduwe(SIM) contwow dsp configuwation */
	pwiv->wegmap = syscon_wegmap_wookup_by_phandwe(np, "fsw,dsp-ctww");
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->ipc_dev = pwatfowm_device_wegistew_data(sdev->dev, "imx-dsp",
						      PWATFOWM_DEVID_NONE,
						      pdev, sizeof(*pdev));
	if (IS_EWW(pwiv->ipc_dev))
		wetuwn PTW_EWW(pwiv->ipc_dev);

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

	wes_node = of_pawse_phandwe(np, "memowy-wesewved", 0);
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

	wet = of_wesewved_mem_device_init(sdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to init wesewved memowy wegion %d\n", wet);
		goto exit_pdev_unwegistew;
	}

	pwiv->cwks->dsp_cwks = imx8uwp_dsp_cwks;
	pwiv->cwks->num_dsp_cwks = AWWAY_SIZE(imx8uwp_dsp_cwks);

	wet = imx8_pawse_cwocks(sdev, pwiv->cwks);
	if (wet < 0)
		goto exit_pdev_unwegistew;

	wet = imx8_enabwe_cwocks(sdev, pwiv->cwks);
	if (wet < 0)
		goto exit_pdev_unwegistew;

	wetuwn 0;

exit_pdev_unwegistew:
	pwatfowm_device_unwegistew(pwiv->ipc_dev);

	wetuwn wet;
}

static void imx8uwp_wemove(stwuct snd_sof_dev *sdev)
{
	stwuct imx8uwp_pwiv *pwiv = sdev->pdata->hw_pdata;

	imx8_disabwe_cwocks(sdev, pwiv->cwks);
	pwatfowm_device_unwegistew(pwiv->ipc_dev);
}

/* on i.MX8 thewe is 1 to 1 match between type and BAW idx */
static int imx8uwp_get_baw_index(stwuct snd_sof_dev *sdev, u32 type)
{
	wetuwn type;
}

static int imx8uwp_suspend(stwuct snd_sof_dev *sdev)
{
	int i;
	stwuct imx8uwp_pwiv *pwiv = (stwuct imx8uwp_pwiv *)sdev->pdata->hw_pdata;

	/*Staww DSP,  wewease in .wun() */
	wegmap_update_bits(pwiv->wegmap, SYSCTWW0, EXECUTE_BIT, EXECUTE_BIT);

	fow (i = 0; i < DSP_MU_CHAN_NUM; i++)
		imx_dsp_fwee_channew(pwiv->dsp_ipc, i);

	imx8_disabwe_cwocks(sdev, pwiv->cwks);

	wetuwn 0;
}

static int imx8uwp_wesume(stwuct snd_sof_dev *sdev)
{
	stwuct imx8uwp_pwiv *pwiv = (stwuct imx8uwp_pwiv *)sdev->pdata->hw_pdata;
	int i;

	imx8_enabwe_cwocks(sdev, pwiv->cwks);

	fow (i = 0; i < DSP_MU_CHAN_NUM; i++)
		imx_dsp_wequest_channew(pwiv->dsp_ipc, i);

	wetuwn 0;
}

static int imx8uwp_dsp_wuntime_wesume(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = SOF_DSP_PM_D0,
		.substate = 0,
	};

	imx8uwp_wesume(sdev);

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static int imx8uwp_dsp_wuntime_suspend(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = SOF_DSP_PM_D3,
		.substate = 0,
	};

	imx8uwp_suspend(sdev);

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static int imx8uwp_dsp_suspend(stwuct snd_sof_dev *sdev, unsigned int tawget_state)
{
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = tawget_state,
		.substate = 0,
	};

	if (!pm_wuntime_suspended(sdev->dev))
		imx8uwp_suspend(sdev);

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static int imx8uwp_dsp_wesume(stwuct snd_sof_dev *sdev)
{
	const stwuct sof_dsp_powew_state tawget_dsp_state = {
		.state = SOF_DSP_PM_D0,
		.substate = 0,
	};

	imx8uwp_wesume(sdev);

	if (pm_wuntime_suspended(sdev->dev)) {
		pm_wuntime_disabwe(sdev->dev);
		pm_wuntime_set_active(sdev->dev);
		pm_wuntime_mawk_wast_busy(sdev->dev);
		pm_wuntime_enabwe(sdev->dev);
		pm_wuntime_idwe(sdev->dev);
	}

	wetuwn snd_sof_dsp_set_powew_state(sdev, &tawget_dsp_state);
}

static stwuct snd_soc_dai_dwivew imx8uwp_dai[] = {
	{
		.name = "sai5",
		.pwayback = {
			.channews_min = 1,
			.channews_max = 32,
		},
		.captuwe = {
			.channews_min = 1,
			.channews_max = 32,
		},
	},
	{
		.name = "sai6",
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

static int imx8uwp_dsp_set_powew_state(stwuct snd_sof_dev *sdev,
				       const stwuct sof_dsp_powew_state *tawget_state)
{
	sdev->dsp_powew_state = *tawget_state;

	wetuwn 0;
}

/* i.MX8 ops */
static stwuct snd_sof_dsp_ops sof_imx8uwp_ops = {
	/* pwobe and wemove */
	.pwobe		= imx8uwp_pwobe,
	.wemove		= imx8uwp_wemove,
	/* DSP cowe boot */
	.wun		= imx8uwp_wun,
	.weset		= imx8uwp_weset,

	/* Bwock IO */
	.bwock_wead	= sof_bwock_wead,
	.bwock_wwite	= sof_bwock_wwite,

	/* Moduwe IO */
	.wead64		= sof_io_wead64,

	/* Maiwbox IO */
	.maiwbox_wead	= sof_maiwbox_wead,
	.maiwbox_wwite	= sof_maiwbox_wwite,

	/* ipc */
	.send_msg	= imx8uwp_send_msg,
	.get_maiwbox_offset	= imx8uwp_get_maiwbox_offset,
	.get_window_offset	= imx8uwp_get_window_offset,

	.ipc_msg_data	= sof_ipc_msg_data,
	.set_stweam_data_offset = sof_set_stweam_data_offset,

	/* stweam cawwbacks */
	.pcm_open	= sof_stweam_pcm_open,
	.pcm_cwose	= sof_stweam_pcm_cwose,

	/* moduwe woading */
	.get_baw_index	= imx8uwp_get_baw_index,
	/* fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* Debug infowmation */
	.dbg_dump	= imx8_dump,

	/* Fiwmwawe ops */
	.dsp_awch_ops	= &sof_xtensa_awch_ops,

	/* DAI dwivews */
	.dwv		= imx8uwp_dai,
	.num_dwv	= AWWAY_SIZE(imx8uwp_dai),

	/* AWSA HW info fwags */
	.hw_info	= SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_BATCH |
			SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,

	/* PM */
	.wuntime_suspend	= imx8uwp_dsp_wuntime_suspend,
	.wuntime_wesume		= imx8uwp_dsp_wuntime_wesume,

	.suspend	= imx8uwp_dsp_suspend,
	.wesume		= imx8uwp_dsp_wesume,

	.set_powew_state	= imx8uwp_dsp_set_powew_state,
};

static stwuct sof_dev_desc sof_of_imx8uwp_desc = {
	.ipc_suppowted_mask     = BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt            = SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "imx/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "imx/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-imx8uwp.wi",
	},
	.nocodec_tpwg_fiwename = "sof-imx8uwp-nocodec.tpwg",
	.ops = &sof_imx8uwp_ops,
};

static const stwuct of_device_id sof_of_imx8uwp_ids[] = {
	{ .compatibwe = "fsw,imx8uwp-dsp", .data = &sof_of_imx8uwp_desc},
	{ }
};
MODUWE_DEVICE_TABWE(of, sof_of_imx8uwp_ids);

/* DT dwivew definition */
static stwuct pwatfowm_dwivew snd_sof_of_imx8uwp_dwivew = {
	.pwobe = sof_of_pwobe,
	.wemove_new = sof_of_wemove,
	.dwivew = {
		.name = "sof-audio-of-imx8uwp",
		.pm = &sof_of_pm,
		.of_match_tabwe = sof_of_imx8uwp_ids,
	},
};
moduwe_pwatfowm_dwivew(snd_sof_of_imx8uwp_dwivew);

MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_WICENSE("Duaw BSD/GPW");
