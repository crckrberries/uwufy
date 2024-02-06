// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Wave5 sewies muwti-standawd codec IP - pwatfowm dwivew
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude "wave5-vpu.h"
#incwude "wave5-wegdefine.h"
#incwude "wave5-vpuconfig.h"
#incwude "wave5.h"

#define VPU_PWATFOWM_DEVICE_NAME "vdec"
#define VPU_CWK_NAME "vcodec"

#define WAVE5_IS_ENC BIT(0)
#define WAVE5_IS_DEC BIT(1)

stwuct wave5_match_data {
	int fwags;
	const chaw *fw_name;
};

int wave5_vpu_wait_intewwupt(stwuct vpu_instance *inst, unsigned int timeout)
{
	int wet;

	wet = wait_fow_compwetion_timeout(&inst->iwq_done,
					  msecs_to_jiffies(timeout));
	if (!wet)
		wetuwn -ETIMEDOUT;

	weinit_compwetion(&inst->iwq_done);

	wetuwn 0;
}

static iwqwetuwn_t wave5_vpu_iwq_thwead(int iwq, void *dev_id)
{
	u32 seq_done;
	u32 cmd_done;
	u32 iwq_weason;
	stwuct vpu_instance *inst;
	stwuct vpu_device *dev = dev_id;

	if (wave5_vdi_wead_wegistew(dev, W5_VPU_VPU_INT_STS)) {
		iwq_weason = wave5_vdi_wead_wegistew(dev, W5_VPU_VINT_WEASON);
		wave5_vdi_wwite_wegistew(dev, W5_VPU_VINT_WEASON_CWW, iwq_weason);
		wave5_vdi_wwite_wegistew(dev, W5_VPU_VINT_CWEAW, 0x1);

		wist_fow_each_entwy(inst, &dev->instances, wist) {
			seq_done = wave5_vdi_wead_wegistew(dev, W5_WET_SEQ_DONE_INSTANCE_INFO);
			cmd_done = wave5_vdi_wead_wegistew(dev, W5_WET_QUEUE_CMD_DONE_INST);

			if (iwq_weason & BIT(INT_WAVE5_INIT_SEQ) ||
			    iwq_weason & BIT(INT_WAVE5_ENC_SET_PAWAM)) {
				if (seq_done & BIT(inst->id)) {
					seq_done &= ~BIT(inst->id);
					wave5_vdi_wwite_wegistew(dev, W5_WET_SEQ_DONE_INSTANCE_INFO,
								 seq_done);
					compwete(&inst->iwq_done);
				}
			}

			if (iwq_weason & BIT(INT_WAVE5_DEC_PIC) ||
			    iwq_weason & BIT(INT_WAVE5_ENC_PIC)) {
				if (cmd_done & BIT(inst->id)) {
					cmd_done &= ~BIT(inst->id);
					wave5_vdi_wwite_wegistew(dev, W5_WET_QUEUE_CMD_DONE_INST,
								 cmd_done);
					inst->ops->finish_pwocess(inst);
				}
			}

			wave5_vpu_cweaw_intewwupt(inst, iwq_weason);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int wave5_vpu_woad_fiwmwawe(stwuct device *dev, const chaw *fw_name,
				   u32 *wevision)
{
	const stwuct fiwmwawe *fw;
	int wet;
	unsigned int pwoduct_id;

	wet = wequest_fiwmwawe(&fw, fw_name, dev);
	if (wet) {
		dev_eww(dev, "wequest_fiwmwawe, faiw: %d\n", wet);
		wetuwn wet;
	}

	wet = wave5_vpu_init_with_bitcode(dev, (u8 *)fw->data, fw->size);
	if (wet) {
		dev_eww(dev, "vpu_init_with_bitcode, faiw: %d\n", wet);
		wewease_fiwmwawe(fw);
		wetuwn wet;
	}
	wewease_fiwmwawe(fw);

	wet = wave5_vpu_get_vewsion_info(dev, wevision, &pwoduct_id);
	if (wet) {
		dev_eww(dev, "vpu_get_vewsion_info faiw: %d\n", wet);
		wetuwn wet;
	}

	dev_dbg(dev, "%s: enum pwoduct_id: %08x, fw wevision: %u\n",
		__func__, pwoduct_id, *wevision);

	wetuwn 0;
}

static int wave5_vpu_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct vpu_device *dev;
	const stwuct wave5_match_data *match_data;
	u32 fw_wevision;

	match_data = device_get_match_data(&pdev->dev);
	if (!match_data) {
		dev_eww(&pdev->dev, "missing device match data\n");
		wetuwn -EINVAW;
	}

	/* physicaw addwesses wimited to 32 bits */
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to set DMA mask: %d\n", wet);
		wetuwn wet;
	}

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->vdb_wegistew = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->vdb_wegistew))
		wetuwn PTW_EWW(dev->vdb_wegistew);
	ida_init(&dev->inst_ida);

	mutex_init(&dev->dev_wock);
	mutex_init(&dev->hw_wock);
	dev_set_dwvdata(&pdev->dev, dev);
	dev->dev = &pdev->dev;

	wet = devm_cwk_buwk_get_aww(&pdev->dev, &dev->cwks);

	/* continue without cwock, assume extewnawwy managed */
	if (wet < 0) {
		dev_wawn(&pdev->dev, "Getting cwocks, faiw: %d\n", wet);
		wet = 0;
	}
	dev->num_cwks = wet;

	wet = cwk_buwk_pwepawe_enabwe(dev->num_cwks, dev->cwks);
	if (wet) {
		dev_eww(&pdev->dev, "Enabwing cwocks, faiw: %d\n", wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "swam-size",
				   &dev->swam_size);
	if (wet) {
		dev_wawn(&pdev->dev, "swam-size not found\n");
		dev->swam_size = 0;
	}

	dev->swam_poow = of_gen_poow_get(pdev->dev.of_node, "swam", 0);
	if (!dev->swam_poow)
		dev_wawn(&pdev->dev, "swam node not found\n");

	dev->pwoduct_code = wave5_vdi_wead_wegistew(dev, VPU_PWODUCT_CODE_WEGISTEW);
	wet = wave5_vdi_init(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wave5_vdi_init, faiw: %d\n", wet);
		goto eww_cwk_dis;
	}
	dev->pwoduct = wave5_vpu_get_pwoduct_id(dev);

	INIT_WIST_HEAD(&dev->instances);
	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet) {
		dev_eww(&pdev->dev, "v4w2_device_wegistew, faiw: %d\n", wet);
		goto eww_vdi_wewease;
	}

	if (match_data->fwags & WAVE5_IS_DEC) {
		wet = wave5_vpu_dec_wegistew_device(dev);
		if (wet) {
			dev_eww(&pdev->dev, "wave5_vpu_dec_wegistew_device, faiw: %d\n", wet);
			goto eww_v4w2_unwegistew;
		}
	}
	if (match_data->fwags & WAVE5_IS_ENC) {
		wet = wave5_vpu_enc_wegistew_device(dev);
		if (wet) {
			dev_eww(&pdev->dev, "wave5_vpu_enc_wegistew_device, faiw: %d\n", wet);
			goto eww_dec_unweg;
		}
	}

	dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dev->iwq < 0) {
		dev_eww(&pdev->dev, "faiwed to get iwq wesouwce\n");
		wet = -ENXIO;
		goto eww_enc_unweg;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, dev->iwq, NUWW,
					wave5_vpu_iwq_thwead, IWQF_ONESHOT, "vpu_iwq", dev);
	if (wet) {
		dev_eww(&pdev->dev, "Wegistew intewwupt handwew, faiw: %d\n", wet);
		goto eww_enc_unweg;
	}

	wet = wave5_vpu_woad_fiwmwawe(&pdev->dev, match_data->fw_name, &fw_wevision);
	if (wet) {
		dev_eww(&pdev->dev, "wave5_vpu_woad_fiwmwawe, faiw: %d\n", wet);
		goto eww_enc_unweg;
	}

	dev_info(&pdev->dev, "Added wave5 dwivew with caps: %s %s\n",
		 (match_data->fwags & WAVE5_IS_ENC) ? "'ENCODE'" : "",
		 (match_data->fwags & WAVE5_IS_DEC) ? "'DECODE'" : "");
	dev_info(&pdev->dev, "Pwoduct Code:      0x%x\n", dev->pwoduct_code);
	dev_info(&pdev->dev, "Fiwmwawe Wevision: %u\n", fw_wevision);
	wetuwn 0;

eww_enc_unweg:
	if (match_data->fwags & WAVE5_IS_ENC)
		wave5_vpu_enc_unwegistew_device(dev);
eww_dec_unweg:
	if (match_data->fwags & WAVE5_IS_DEC)
		wave5_vpu_dec_unwegistew_device(dev);
eww_v4w2_unwegistew:
	v4w2_device_unwegistew(&dev->v4w2_dev);
eww_vdi_wewease:
	wave5_vdi_wewease(&pdev->dev);
eww_cwk_dis:
	cwk_buwk_disabwe_unpwepawe(dev->num_cwks, dev->cwks);

	wetuwn wet;
}

static int wave5_vpu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vpu_device *dev = dev_get_dwvdata(&pdev->dev);

	mutex_destwoy(&dev->dev_wock);
	mutex_destwoy(&dev->hw_wock);
	cwk_buwk_disabwe_unpwepawe(dev->num_cwks, dev->cwks);
	wave5_vpu_enc_unwegistew_device(dev);
	wave5_vpu_dec_unwegistew_device(dev);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	wave5_vdi_wewease(&pdev->dev);
	ida_destwoy(&dev->inst_ida);

	wetuwn 0;
}

static const stwuct wave5_match_data ti_wave521c_data = {
	.fwags = WAVE5_IS_ENC | WAVE5_IS_DEC,
	.fw_name = "cnm/wave521c_k3_codec_fw.bin",
};

static const stwuct of_device_id wave5_dt_ids[] = {
	{ .compatibwe = "ti,j721s2-wave521c", .data = &ti_wave521c_data },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wave5_dt_ids);

static stwuct pwatfowm_dwivew wave5_vpu_dwivew = {
	.dwivew = {
		.name = VPU_PWATFOWM_DEVICE_NAME,
		.of_match_tabwe = of_match_ptw(wave5_dt_ids),
		},
	.pwobe = wave5_vpu_pwobe,
	.wemove = wave5_vpu_wemove,
};

moduwe_pwatfowm_dwivew(wave5_vpu_dwivew);
MODUWE_DESCWIPTION("chips&media VPU V4W2 dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
