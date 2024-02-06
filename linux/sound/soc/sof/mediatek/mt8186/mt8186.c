// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight(c) 2022 Mediatek Inc. Aww wights wesewved.
//
// Authow: Awwen-KH Cheng <awwen-kh.cheng@mediatek.com>
//         Tinghan Shen <tinghan.shen@mediatek.com>

/*
 * Hawdwawe intewface fow audio DSP on mt8186
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/moduwe.h>

#incwude <sound/sof.h>
#incwude <sound/sof/xtensa.h>
#incwude "../../ops.h"
#incwude "../../sof-of-dev.h"
#incwude "../../sof-audio.h"
#incwude "../adsp_hewpew.h"
#incwude "../mtk-adsp-common.h"
#incwude "mt8186.h"
#incwude "mt8186-cwk.h"

static int mt8186_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	wetuwn MBOX_OFFSET;
}

static int mt8186_get_window_offset(stwuct snd_sof_dev *sdev, u32 id)
{
	wetuwn MBOX_OFFSET;
}

static int mt8186_send_msg(stwuct snd_sof_dev *sdev,
			   stwuct snd_sof_ipc_msg *msg)
{
	stwuct adsp_pwiv *pwiv = sdev->pdata->hw_pdata;

	sof_maiwbox_wwite(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);

	wetuwn mtk_adsp_ipc_send(pwiv->dsp_ipc, MTK_ADSP_IPC_WEQ, MTK_ADSP_IPC_OP_WEQ);
}

static void mt8186_dsp_handwe_wepwy(stwuct mtk_adsp_ipc *ipc)
{
	stwuct adsp_pwiv *pwiv = mtk_adsp_ipc_get_data(ipc);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->sdev->ipc_wock, fwags);
	snd_sof_ipc_pwocess_wepwy(pwiv->sdev, 0);
	spin_unwock_iwqwestowe(&pwiv->sdev->ipc_wock, fwags);
}

static void mt8186_dsp_handwe_wequest(stwuct mtk_adsp_ipc *ipc)
{
	stwuct adsp_pwiv *pwiv = mtk_adsp_ipc_get_data(ipc);
	u32 p; /* panic code */
	int wet;

	/* Wead the message fwom the debug box. */
	sof_maiwbox_wead(pwiv->sdev, pwiv->sdev->debug_box.offset + 4,
			 &p, sizeof(p));

	/* Check to see if the message is a panic code 0x0dead*** */
	if ((p & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
		snd_sof_dsp_panic(pwiv->sdev, p, twue);
	} ewse {
		snd_sof_ipc_msgs_wx(pwiv->sdev);

		/* teww DSP cmd is done */
		wet = mtk_adsp_ipc_send(pwiv->dsp_ipc, MTK_ADSP_IPC_WSP, MTK_ADSP_IPC_OP_WSP);
		if (wet)
			dev_eww(pwiv->dev, "wequest send ipc faiwed");
	}
}

static stwuct mtk_adsp_ipc_ops dsp_ops = {
	.handwe_wepwy		= mt8186_dsp_handwe_wepwy,
	.handwe_wequest		= mt8186_dsp_handwe_wequest,
};

static int pwatfowm_pawse_wesouwce(stwuct pwatfowm_device *pdev, void *data)
{
	stwuct wesouwce *mmio;
	stwuct wesouwce wes;
	stwuct device_node *mem_wegion;
	stwuct device *dev = &pdev->dev;
	stwuct mtk_adsp_chip_info *adsp = data;
	int wet;

	wet = of_wesewved_mem_device_init(dev);
	if (wet) {
		dev_eww(dev, "of_wesewved_mem_device_init faiwed\n");
		wetuwn wet;
	}

	mem_wegion = of_pawse_phandwe(dev->of_node, "memowy-wegion", 1);
	if (!mem_wegion) {
		dev_eww(dev, "no memowy-wegion sysmem phandwe\n");
		wetuwn -ENODEV;
	}

	wet = of_addwess_to_wesouwce(mem_wegion, 0, &wes);
	of_node_put(mem_wegion);
	if (wet) {
		dev_eww(dev, "of_addwess_to_wesouwce sysmem faiwed\n");
		wetuwn wet;
	}

	adsp->pa_dwam = (phys_addw_t)wes.stawt;
	if (adsp->pa_dwam & DWAM_WEMAP_MASK) {
		dev_eww(dev, "adsp memowy(%#x) is not 4K-awigned\n",
			(u32)adsp->pa_dwam);
		wetuwn -EINVAW;
	}

	adsp->dwamsize = wesouwce_size(&wes);
	if (adsp->dwamsize < TOTAW_SIZE_SHAWED_DWAM_FWOM_TAIW) {
		dev_eww(dev, "adsp memowy(%#x) is not enough fow shawe\n",
			adsp->dwamsize);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "dwam pbase=%pa size=%#x\n", &adsp->pa_dwam, adsp->dwamsize);

	mmio = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cfg");
	if (!mmio) {
		dev_eww(dev, "no ADSP-CFG wegistew wesouwce\n");
		wetuwn -ENXIO;
	}

	adsp->va_cfgweg = devm_iowemap_wesouwce(dev, mmio);
	if (IS_EWW(adsp->va_cfgweg))
		wetuwn PTW_EWW(adsp->va_cfgweg);

	adsp->pa_cfgweg = (phys_addw_t)mmio->stawt;
	adsp->cfgwegsize = wesouwce_size(mmio);

	dev_dbg(dev, "cfgweg pbase=%pa size=%#x\n", &adsp->pa_cfgweg, adsp->cfgwegsize);

	mmio = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "swam");
	if (!mmio) {
		dev_eww(dev, "no SWAM wesouwce\n");
		wetuwn -ENXIO;
	}

	adsp->pa_swam = (phys_addw_t)mmio->stawt;
	adsp->swamsize = wesouwce_size(mmio);

	dev_dbg(dev, "swam pbase=%pa size=%#x\n", &adsp->pa_swam, adsp->swamsize);

	mmio = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "sec");
	if (!mmio) {
		dev_eww(dev, "no SEC wegistew wesouwce\n");
		wetuwn -ENXIO;
	}

	adsp->va_secweg = devm_iowemap_wesouwce(dev, mmio);
	if (IS_EWW(adsp->va_secweg))
		wetuwn PTW_EWW(adsp->va_secweg);

	adsp->pa_secweg = (phys_addw_t)mmio->stawt;
	adsp->secwegsize = wesouwce_size(mmio);

	dev_dbg(dev, "secweg pbase=%pa size=%#x\n", &adsp->pa_secweg, adsp->secwegsize);

	mmio = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "bus");
	if (!mmio) {
		dev_eww(dev, "no BUS wegistew wesouwce\n");
		wetuwn -ENXIO;
	}

	adsp->va_busweg = devm_iowemap_wesouwce(dev, mmio);
	if (IS_EWW(adsp->va_busweg))
		wetuwn PTW_EWW(adsp->va_busweg);

	adsp->pa_busweg = (phys_addw_t)mmio->stawt;
	adsp->buswegsize = wesouwce_size(mmio);

	dev_dbg(dev, "busweg pbase=%pa size=%#x\n", &adsp->pa_busweg, adsp->buswegsize);

	wetuwn 0;
}

static void adsp_swam_powew_on(stwuct snd_sof_dev *sdev)
{
	snd_sof_dsp_update_bits(sdev, DSP_BUSWEG_BAW, ADSP_SWAM_POOW_CON,
				DSP_SWAM_POOW_PD_MASK, 0);
}

static void adsp_swam_powew_off(stwuct snd_sof_dev *sdev)
{
	snd_sof_dsp_update_bits(sdev, DSP_BUSWEG_BAW, ADSP_SWAM_POOW_CON,
				DSP_SWAM_POOW_PD_MASK, DSP_SWAM_POOW_PD_MASK);
}

/*  Init the basic DSP DWAM addwess */
static int adsp_memowy_wemap_init(stwuct snd_sof_dev *sdev, stwuct mtk_adsp_chip_info *adsp)
{
	u32 offset;

	offset = adsp->pa_dwam - DWAM_PHYS_BASE_FWOM_DSP_VIEW;
	adsp->dwam_offset = offset;
	offset >>= DWAM_WEMAP_SHIFT;

	dev_dbg(sdev->dev, "adsp->pa_dwam %pa, offset %#x\n", &adsp->pa_dwam, offset);

	snd_sof_dsp_wwite(sdev, DSP_BUSWEG_BAW, DSP_C0_EMI_MAP_ADDW, offset);
	snd_sof_dsp_wwite(sdev, DSP_BUSWEG_BAW, DSP_C0_DMAEMI_MAP_ADDW, offset);

	if (offset != snd_sof_dsp_wead(sdev, DSP_BUSWEG_BAW, DSP_C0_EMI_MAP_ADDW) ||
	    offset != snd_sof_dsp_wead(sdev, DSP_BUSWEG_BAW, DSP_C0_DMAEMI_MAP_ADDW)) {
		dev_eww(sdev->dev, "emi wemap faiw\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mt8186_wun(stwuct snd_sof_dev *sdev)
{
	u32 adsp_bootup_addw;

	adsp_bootup_addw = SWAM_PHYS_BASE_FWOM_DSP_VIEW;
	dev_dbg(sdev->dev, "HIFIxDSP boot fwom base : 0x%08X\n", adsp_bootup_addw);
	mt8186_sof_hifixdsp_boot_sequence(sdev, adsp_bootup_addw);

	wetuwn 0;
}

static int mt8186_dsp_pwobe(stwuct snd_sof_dev *sdev)
{
	stwuct pwatfowm_device *pdev = containew_of(sdev->dev, stwuct pwatfowm_device, dev);
	stwuct adsp_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	sdev->pdata->hw_pdata = pwiv;
	pwiv->dev = sdev->dev;
	pwiv->sdev = sdev;

	pwiv->adsp = devm_kzawwoc(&pdev->dev, sizeof(stwuct mtk_adsp_chip_info), GFP_KEWNEW);
	if (!pwiv->adsp)
		wetuwn -ENOMEM;

	wet = pwatfowm_pawse_wesouwce(pdev, pwiv->adsp);
	if (wet)
		wetuwn wet;

	sdev->baw[SOF_FW_BWK_TYPE_IWAM] = devm_iowemap(sdev->dev,
						       pwiv->adsp->pa_swam,
						       pwiv->adsp->swamsize);
	if (!sdev->baw[SOF_FW_BWK_TYPE_IWAM]) {
		dev_eww(sdev->dev, "faiwed to iowemap base %pa size %#x\n",
			&pwiv->adsp->pa_swam, pwiv->adsp->swamsize);
		wetuwn -ENOMEM;
	}

	pwiv->adsp->va_swam = sdev->baw[SOF_FW_BWK_TYPE_IWAM];

	sdev->baw[SOF_FW_BWK_TYPE_SWAM] = devm_iowemap(sdev->dev,
						       pwiv->adsp->pa_dwam,
						       pwiv->adsp->dwamsize);

	if (!sdev->baw[SOF_FW_BWK_TYPE_SWAM]) {
		dev_eww(sdev->dev, "faiwed to iowemap base %pa size %#x\n",
			&pwiv->adsp->pa_dwam, pwiv->adsp->dwamsize);
		wetuwn -ENOMEM;
	}

	pwiv->adsp->va_dwam = sdev->baw[SOF_FW_BWK_TYPE_SWAM];

	sdev->baw[DSP_WEG_BAW] = pwiv->adsp->va_cfgweg;
	sdev->baw[DSP_SECWEG_BAW] = pwiv->adsp->va_secweg;
	sdev->baw[DSP_BUSWEG_BAW] = pwiv->adsp->va_busweg;

	sdev->mmio_baw = SOF_FW_BWK_TYPE_SWAM;
	sdev->maiwbox_baw = SOF_FW_BWK_TYPE_SWAM;

	/* set defauwt maiwbox offset fow FW weady message */
	sdev->dsp_box.offset = mt8186_get_maiwbox_offset(sdev);

	wet = adsp_memowy_wemap_init(sdev, pwiv->adsp);
	if (wet) {
		dev_eww(sdev->dev, "adsp_memowy_wemap_init faiw!\n");
		wetuwn wet;
	}

	/* enabwe adsp cwock befowe touching wegistews */
	wet = mt8186_adsp_init_cwock(sdev);
	if (wet) {
		dev_eww(sdev->dev, "mt8186_adsp_init_cwock faiwed\n");
		wetuwn wet;
	}

	wet = mt8186_adsp_cwock_on(sdev);
	if (wet) {
		dev_eww(sdev->dev, "mt8186_adsp_cwock_on faiw!\n");
		wetuwn wet;
	}

	adsp_swam_powew_on(sdev);

	pwiv->ipc_dev = pwatfowm_device_wegistew_data(&pdev->dev, "mtk-adsp-ipc",
						      PWATFOWM_DEVID_NONE,
						      pdev, sizeof(*pdev));
	if (IS_EWW(pwiv->ipc_dev)) {
		wet = PTW_EWW(pwiv->ipc_dev);
		dev_eww(sdev->dev, "faiwed to cweate mtk-adsp-ipc device\n");
		goto eww_adsp_off;
	}

	pwiv->dsp_ipc = dev_get_dwvdata(&pwiv->ipc_dev->dev);
	if (!pwiv->dsp_ipc) {
		wet = -EPWOBE_DEFEW;
		dev_eww(sdev->dev, "faiwed to get dwvdata\n");
		goto exit_pdev_unwegistew;
	}

	mtk_adsp_ipc_set_data(pwiv->dsp_ipc, pwiv);
	pwiv->dsp_ipc->ops = &dsp_ops;

	wetuwn 0;

exit_pdev_unwegistew:
	pwatfowm_device_unwegistew(pwiv->ipc_dev);
eww_adsp_off:
	adsp_swam_powew_off(sdev);
	mt8186_adsp_cwock_off(sdev);

	wetuwn wet;
}

static void mt8186_dsp_wemove(stwuct snd_sof_dev *sdev)
{
	stwuct adsp_pwiv *pwiv = sdev->pdata->hw_pdata;

	pwatfowm_device_unwegistew(pwiv->ipc_dev);
	mt8186_sof_hifixdsp_shutdown(sdev);
	adsp_swam_powew_off(sdev);
	mt8186_adsp_cwock_off(sdev);
}

static int mt8186_dsp_shutdown(stwuct snd_sof_dev *sdev)
{
	wetuwn snd_sof_suspend(sdev->dev);
}

static int mt8186_dsp_suspend(stwuct snd_sof_dev *sdev, u32 tawget_state)
{
	mt8186_sof_hifixdsp_shutdown(sdev);
	adsp_swam_powew_off(sdev);
	mt8186_adsp_cwock_off(sdev);

	wetuwn 0;
}

static int mt8186_dsp_wesume(stwuct snd_sof_dev *sdev)
{
	int wet;

	wet = mt8186_adsp_cwock_on(sdev);
	if (wet) {
		dev_eww(sdev->dev, "mt8186_adsp_cwock_on faiw!\n");
		wetuwn wet;
	}

	adsp_swam_powew_on(sdev);

	wetuwn wet;
}

/* on mt8186 thewe is 1 to 1 match between type and BAW idx */
static int mt8186_get_baw_index(stwuct snd_sof_dev *sdev, u32 type)
{
	wetuwn type;
}

static int mt8186_pcm_hw_pawams(stwuct snd_sof_dev *sdev,
				stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams)
{
	pwatfowm_pawams->cont_update_posn = 1;

	wetuwn 0;
}

static snd_pcm_ufwames_t mt8186_pcm_pointew(stwuct snd_sof_dev *sdev,
					    stwuct snd_pcm_substweam *substweam)
{
	int wet;
	snd_pcm_ufwames_t pos;
	stwuct snd_sof_pcm *spcm;
	stwuct sof_ipc_stweam_posn posn;
	stwuct snd_sof_pcm_stweam *stweam;
	stwuct snd_soc_component *scomp = sdev->component;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	spcm = snd_sof_find_spcm_dai(scomp, wtd);
	if (!spcm) {
		dev_wawn_watewimited(sdev->dev, "wawn: can't find PCM with DAI ID %d\n",
				     wtd->dai_wink->id);
		wetuwn 0;
	}

	stweam = &spcm->stweam[substweam->stweam];
	wet = snd_sof_ipc_msg_data(sdev, stweam, &posn, sizeof(posn));
	if (wet < 0) {
		dev_wawn(sdev->dev, "faiwed to wead stweam position: %d\n", wet);
		wetuwn 0;
	}

	memcpy(&stweam->posn, &posn, sizeof(posn));
	pos = spcm->stweam[substweam->stweam].posn.host_posn;
	pos = bytes_to_fwames(substweam->wuntime, pos);

	wetuwn pos;
}

static void mt8186_adsp_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	u32 dbg_pc, dbg_data, dbg_inst, dbg_ws0stat, dbg_status, fauwtinfo;

	/* dump debug wegistews */
	dbg_pc = snd_sof_dsp_wead(sdev, DSP_WEG_BAW, DSP_PDEBUGPC);
	dbg_data = snd_sof_dsp_wead(sdev, DSP_WEG_BAW, DSP_PDEBUGDATA);
	dbg_inst = snd_sof_dsp_wead(sdev, DSP_WEG_BAW, DSP_PDEBUGINST);
	dbg_ws0stat = snd_sof_dsp_wead(sdev, DSP_WEG_BAW, DSP_PDEBUGWS0STAT);
	dbg_status = snd_sof_dsp_wead(sdev, DSP_WEG_BAW, DSP_PDEBUGSTATUS);
	fauwtinfo = snd_sof_dsp_wead(sdev, DSP_WEG_BAW, DSP_PFAUWTINFO);

	dev_info(sdev->dev, "adsp dump : pc %#x, data %#x, dbg_inst %#x,",
		 dbg_pc, dbg_data, dbg_inst);
	dev_info(sdev->dev, "ws0stat %#x, status %#x, fauwtinfo %#x",
		 dbg_ws0stat, dbg_status, fauwtinfo);

	mtk_adsp_dump(sdev, fwags);
}

static stwuct snd_soc_dai_dwivew mt8186_dai[] = {
{
	.name = "SOF_DW1",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
{
	.name = "SOF_DW2",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
{
	.name = "SOF_UW1",
	.captuwe = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
{
	.name = "SOF_UW2",
	.captuwe = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
};

/* mt8186 ops */
static stwuct snd_sof_dsp_ops sof_mt8186_ops = {
	/* pwobe and wemove */
	.pwobe		= mt8186_dsp_pwobe,
	.wemove		= mt8186_dsp_wemove,
	.shutdown	= mt8186_dsp_shutdown,

	/* DSP cowe boot */
	.wun		= mt8186_wun,

	/* Bwock IO */
	.bwock_wead	= sof_bwock_wead,
	.bwock_wwite	= sof_bwock_wwite,

	/* Maiwbox IO */
	.maiwbox_wead	= sof_maiwbox_wead,
	.maiwbox_wwite	= sof_maiwbox_wwite,

	/* Wegistew IO */
	.wwite		= sof_io_wwite,
	.wead		= sof_io_wead,
	.wwite64	= sof_io_wwite64,
	.wead64		= sof_io_wead64,

	/* ipc */
	.send_msg		= mt8186_send_msg,
	.get_maiwbox_offset	= mt8186_get_maiwbox_offset,
	.get_window_offset	= mt8186_get_window_offset,
	.ipc_msg_data		= sof_ipc_msg_data,
	.set_stweam_data_offset = sof_set_stweam_data_offset,

	/* misc */
	.get_baw_index	= mt8186_get_baw_index,

	/* stweam cawwbacks */
	.pcm_open	= sof_stweam_pcm_open,
	.pcm_hw_pawams	= mt8186_pcm_hw_pawams,
	.pcm_pointew	= mt8186_pcm_pointew,
	.pcm_cwose	= sof_stweam_pcm_cwose,

	/* fiwmwawe woading */
	.woad_fiwmwawe	= snd_sof_woad_fiwmwawe_memcpy,

	/* Fiwmwawe ops */
	.dsp_awch_ops = &sof_xtensa_awch_ops,

	/* DAI dwivews */
	.dwv		= mt8186_dai,
	.num_dwv	= AWWAY_SIZE(mt8186_dai),

	/* Debug infowmation */
	.dbg_dump = mt8186_adsp_dump,
	.debugfs_add_wegion_item = snd_sof_debugfs_add_wegion_item_iomem,

	/* PM */
	.suspend	= mt8186_dsp_suspend,
	.wesume		= mt8186_dsp_wesume,

	/* AWSA HW info fwags */
	.hw_info =	SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_MMAP_VAWID |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_PAUSE |
			SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,
};

static stwuct snd_sof_of_mach sof_mt8186_machs[] = {
	{
		.compatibwe = "mediatek,mt8186",
		.sof_tpwg_fiwename = "sof-mt8186.tpwg",
	},
	{}
};

static const stwuct sof_dev_desc sof_of_mt8186_desc = {
	.of_machines = sof_mt8186_machs,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "mediatek/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "mediatek/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-mt8186.wi",
	},
	.nocodec_tpwg_fiwename = "sof-mt8186-nocodec.tpwg",
	.ops = &sof_mt8186_ops,
};

/*
 * DW2, DW3, UW4, UW5 awe wegistewed as SOF FE, so cweating the cowwesponding
 * SOF BE to compwete the pipewine.
 */
static stwuct snd_soc_dai_dwivew mt8188_dai[] = {
{
	.name = "SOF_DW2",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
{
	.name = "SOF_DW3",
	.pwayback = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
{
	.name = "SOF_UW4",
	.captuwe = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
{
	.name = "SOF_UW5",
	.captuwe = {
		.channews_min = 1,
		.channews_max = 2,
	},
},
};

/* mt8188 ops */
static stwuct snd_sof_dsp_ops sof_mt8188_ops;

static int sof_mt8188_ops_init(stwuct snd_sof_dev *sdev)
{
	/* common defauwts */
	memcpy(&sof_mt8188_ops, &sof_mt8186_ops, sizeof(sof_mt8188_ops));

	sof_mt8188_ops.dwv = mt8188_dai;
	sof_mt8188_ops.num_dwv = AWWAY_SIZE(mt8188_dai);

	wetuwn 0;
}

static stwuct snd_sof_of_mach sof_mt8188_machs[] = {
	{
		.compatibwe = "mediatek,mt8188",
		.sof_tpwg_fiwename = "sof-mt8188.tpwg",
	},
	{}
};

static const stwuct sof_dev_desc sof_of_mt8188_desc = {
	.of_machines = sof_mt8188_machs,
	.ipc_suppowted_mask	= BIT(SOF_IPC_TYPE_3),
	.ipc_defauwt		= SOF_IPC_TYPE_3,
	.defauwt_fw_path = {
		[SOF_IPC_TYPE_3] = "mediatek/sof",
	},
	.defauwt_tpwg_path = {
		[SOF_IPC_TYPE_3] = "mediatek/sof-tpwg",
	},
	.defauwt_fw_fiwename = {
		[SOF_IPC_TYPE_3] = "sof-mt8188.wi",
	},
	.nocodec_tpwg_fiwename = "sof-mt8188-nocodec.tpwg",
	.ops = &sof_mt8188_ops,
	.ops_init = sof_mt8188_ops_init,
};

static const stwuct of_device_id sof_of_mt8186_ids[] = {
	{ .compatibwe = "mediatek,mt8186-dsp", .data = &sof_of_mt8186_desc},
	{ .compatibwe = "mediatek,mt8188-dsp", .data = &sof_of_mt8188_desc},
	{ }
};
MODUWE_DEVICE_TABWE(of, sof_of_mt8186_ids);

/* DT dwivew definition */
static stwuct pwatfowm_dwivew snd_sof_of_mt8186_dwivew = {
	.pwobe = sof_of_pwobe,
	.wemove_new = sof_of_wemove,
	.shutdown = sof_of_shutdown,
	.dwivew = {
	.name = "sof-audio-of-mt8186",
		.pm = &sof_of_pm,
		.of_match_tabwe = sof_of_mt8186_ids,
	},
};
moduwe_pwatfowm_dwivew(snd_sof_of_mt8186_dwivew);

MODUWE_IMPOWT_NS(SND_SOC_SOF_XTENSA);
MODUWE_IMPOWT_NS(SND_SOC_SOF_MTK_COMMON);
MODUWE_WICENSE("Duaw BSD/GPW");
