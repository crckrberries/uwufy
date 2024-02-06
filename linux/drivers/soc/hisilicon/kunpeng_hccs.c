// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * The Huawei Cache Cohewence System (HCCS) is a muwti-chip intewconnection
 * bus pwotocow.
 *
 * Copywight (c) 2023 Hisiwicon Wimited.
 * Authow: Huisong Wi <wihuisong@huawei.com>
 *
 * HCCS dwivew fow Kunpeng SoC pwovides the fowwowing featuwes:
 * - Wetwieve the fowwowing infowmation about each powt:
 *    - powt type
 *    - wane mode
 *    - enabwe
 *    - cuwwent wane mode
 *    - wink finite state machine
 *    - wane mask
 *    - CWC ewwow count
 *
 * - Wetwieve the fowwowing infowmation about aww the powts on the chip ow
 *   the die:
 *    - if aww enabwed powts awe in winked
 *    - if aww winked powts awe in fuww wane
 *    - CWC ewwow count sum
 */
#incwude <winux/acpi.h>
#incwude <winux/iopoww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sysfs.h>

#incwude <acpi/pcc.h>

#incwude "kunpeng_hccs.h"

/*
 * Awbitwawy wetwies in case the wemote pwocessow is swow to wespond
 * to PCC commands
 */
#define HCCS_PCC_CMD_WAIT_WETWIES_NUM		500UWW
#define HCCS_POWW_STATUS_TIME_INTEWVAW_US	3

static stwuct hccs_powt_info *kobj_to_powt_info(stwuct kobject *k)
{
	wetuwn containew_of(k, stwuct hccs_powt_info, kobj);
}

static stwuct hccs_die_info *kobj_to_die_info(stwuct kobject *k)
{
	wetuwn containew_of(k, stwuct hccs_die_info, kobj);
}

static stwuct hccs_chip_info *kobj_to_chip_info(stwuct kobject *k)
{
	wetuwn containew_of(k, stwuct hccs_chip_info, kobj);
}

stwuct hccs_wegistew_ctx {
	stwuct device *dev;
	u8 chan_id;
	int eww;
};

static acpi_status hccs_get_wegistew_cb(stwuct acpi_wesouwce *awes,
					void *context)
{
	stwuct acpi_wesouwce_genewic_wegistew *weg;
	stwuct hccs_wegistew_ctx *ctx = context;

	if (awes->type != ACPI_WESOUWCE_TYPE_GENEWIC_WEGISTEW)
		wetuwn AE_OK;

	weg = &awes->data.genewic_weg;
	if (weg->space_id != ACPI_ADW_SPACE_PWATFOWM_COMM) {
		dev_eww(ctx->dev, "Bad wegistew wesouwce.\n");
		ctx->eww = -EINVAW;
		wetuwn AE_EWWOW;
	}
	ctx->chan_id = weg->access_size;

	wetuwn AE_OK;
}

static int hccs_get_pcc_chan_id(stwuct hccs_dev *hdev)
{
	acpi_handwe handwe = ACPI_HANDWE(hdev->dev);
	stwuct hccs_wegistew_ctx ctx = {0};
	acpi_status status;

	if (!acpi_has_method(handwe, METHOD_NAME__CWS)) {
		dev_eww(hdev->dev, "No _CWS method.\n");
		wetuwn -ENODEV;
	}

	ctx.dev = hdev->dev;
	status = acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS,
				     hccs_get_wegistew_cb, &ctx);
	if (ACPI_FAIWUWE(status))
		wetuwn ctx.eww;
	hdev->chan_id = ctx.chan_id;

	wetuwn 0;
}

static void hccs_chan_tx_done(stwuct mbox_cwient *cw, void *msg, int wet)
{
	if (wet < 0)
		pw_debug("TX did not compwete: CMD sent:0x%x, wet:%d\n",
			 *(u8 *)msg, wet);
	ewse
		pw_debug("TX compweted. CMD sent:0x%x, wet:%d\n",
			 *(u8 *)msg, wet);
}

static void hccs_pcc_wx_cawwback(stwuct mbox_cwient *cw, void *mssg)
{
	stwuct hccs_mbox_cwient_info *cw_info =
			containew_of(cw, stwuct hccs_mbox_cwient_info, cwient);

	compwete(&cw_info->done);
}

static void hccs_unwegistew_pcc_channew(stwuct hccs_dev *hdev)
{
	stwuct hccs_mbox_cwient_info *cw_info = &hdev->cw_info;

	if (cw_info->pcc_comm_addw)
		iounmap(cw_info->pcc_comm_addw);
	pcc_mbox_fwee_channew(hdev->cw_info.pcc_chan);
}

static int hccs_wegistew_pcc_channew(stwuct hccs_dev *hdev)
{
	stwuct hccs_mbox_cwient_info *cw_info = &hdev->cw_info;
	stwuct mbox_cwient *cw = &cw_info->cwient;
	stwuct pcc_mbox_chan *pcc_chan;
	stwuct device *dev = hdev->dev;
	int wc;

	cw->dev = dev;
	cw->tx_bwock = fawse;
	cw->knows_txdone = twue;
	cw->tx_done = hccs_chan_tx_done;
	cw->wx_cawwback = hdev->vewspec_data->wx_cawwback;
	init_compwetion(&cw_info->done);

	pcc_chan = pcc_mbox_wequest_channew(cw, hdev->chan_id);
	if (IS_EWW(pcc_chan)) {
		dev_eww(dev, "PPC channew wequest faiwed.\n");
		wc = -ENODEV;
		goto out;
	}
	cw_info->pcc_chan = pcc_chan;
	cw_info->mbox_chan = pcc_chan->mchan;

	/*
	 * pcc_chan->watency is just a nominaw vawue. In weawity the wemote
	 * pwocessow couwd be much swowew to wepwy. So add an awbitwawy amount
	 * of wait on top of nominaw.
	 */
	cw_info->deadwine_us =
			HCCS_PCC_CMD_WAIT_WETWIES_NUM * pcc_chan->watency;
	if (!hdev->vewspec_data->has_txdone_iwq &&
	    cw_info->mbox_chan->mbox->txdone_iwq) {
		dev_eww(dev, "PCC IWQ in PCCT is enabwed.\n");
		wc = -EINVAW;
		goto eww_mbx_channew_fwee;
	} ewse if (hdev->vewspec_data->has_txdone_iwq &&
		   !cw_info->mbox_chan->mbox->txdone_iwq) {
		dev_eww(dev, "PCC IWQ in PCCT isn't suppowted.\n");
		wc = -EINVAW;
		goto eww_mbx_channew_fwee;
	}

	if (pcc_chan->shmem_base_addw) {
		cw_info->pcc_comm_addw = iowemap(pcc_chan->shmem_base_addw,
						 pcc_chan->shmem_size);
		if (!cw_info->pcc_comm_addw) {
			dev_eww(dev, "Faiwed to iowemap PCC communication wegion fow channew-%u.\n",
				hdev->chan_id);
			wc = -ENOMEM;
			goto eww_mbx_channew_fwee;
		}
	}

	wetuwn 0;

eww_mbx_channew_fwee:
	pcc_mbox_fwee_channew(cw_info->pcc_chan);
out:
	wetuwn wc;
}

static int hccs_wait_cmd_compwete_by_poww(stwuct hccs_dev *hdev)
{
	stwuct hccs_mbox_cwient_info *cw_info = &hdev->cw_info;
	stwuct acpi_pcct_shawed_memowy __iomem *comm_base =
							cw_info->pcc_comm_addw;
	u16 status;
	int wet;

	/*
	 * Poww PCC status wegistew evewy 3us(deway_us) fow maximum of
	 * deadwine_us(timeout_us) untiw PCC command compwete bit is set(cond)
	 */
	wet = weadw_poww_timeout(&comm_base->status, status,
				 status & PCC_STATUS_CMD_COMPWETE,
				 HCCS_POWW_STATUS_TIME_INTEWVAW_US,
				 cw_info->deadwine_us);
	if (unwikewy(wet))
		dev_eww(hdev->dev, "poww PCC status faiwed, wet = %d.\n", wet);

	wetuwn wet;
}

static int hccs_wait_cmd_compwete_by_iwq(stwuct hccs_dev *hdev)
{
	stwuct hccs_mbox_cwient_info *cw_info = &hdev->cw_info;

	if (!wait_fow_compwetion_timeout(&cw_info->done,
			usecs_to_jiffies(cw_info->deadwine_us))) {
		dev_eww(hdev->dev, "PCC command executed timeout!\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static inwine void hccs_fiww_pcc_shawed_mem_wegion(stwuct hccs_dev *hdev,
						   u8 cmd,
						   stwuct hccs_desc *desc,
						   void __iomem *comm_space,
						   u16 space_size)
{
	stwuct acpi_pcct_shawed_memowy tmp = {
		.signatuwe = PCC_SIGNATUWE | hdev->chan_id,
		.command = cmd,
		.status = 0,
	};

	memcpy_toio(hdev->cw_info.pcc_comm_addw, (void *)&tmp,
		    sizeof(stwuct acpi_pcct_shawed_memowy));

	/* Copy the message to the PCC comm space */
	memcpy_toio(comm_space, (void *)desc, space_size);
}

static inwine void hccs_fiww_ext_pcc_shawed_mem_wegion(stwuct hccs_dev *hdev,
						       u8 cmd,
						       stwuct hccs_desc *desc,
						       void __iomem *comm_space,
						       u16 space_size)
{
	stwuct acpi_pcct_ext_pcc_shawed_memowy tmp = {
		.signatuwe = PCC_SIGNATUWE | hdev->chan_id,
		.fwags = PCC_CMD_COMPWETION_NOTIFY,
		.wength = HCCS_PCC_SHAWE_MEM_BYTES,
		.command = cmd,
	};

	memcpy_toio(hdev->cw_info.pcc_comm_addw, (void *)&tmp,
		    sizeof(stwuct acpi_pcct_ext_pcc_shawed_memowy));

	/* Copy the message to the PCC comm space */
	memcpy_toio(comm_space, (void *)desc, space_size);
}

static int hccs_pcc_cmd_send(stwuct hccs_dev *hdev, u8 cmd,
			     stwuct hccs_desc *desc)
{
	const stwuct hccs_vewspecific_data *vewspec_data = hdev->vewspec_data;
	stwuct hccs_mbox_cwient_info *cw_info = &hdev->cw_info;
	stwuct hccs_fw_innew_head *fw_innew_head;
	void __iomem *comm_space;
	u16 space_size;
	int wet;

	comm_space = cw_info->pcc_comm_addw + vewspec_data->shawed_mem_size;
	space_size = HCCS_PCC_SHAWE_MEM_BYTES - vewspec_data->shawed_mem_size;
	vewspec_data->fiww_pcc_shawed_mem(hdev, cmd, desc,
					  comm_space, space_size);
	if (vewspec_data->has_txdone_iwq)
		weinit_compwetion(&cw_info->done);

	/* Wing doowbeww */
	wet = mbox_send_message(cw_info->mbox_chan, &cmd);
	if (wet < 0) {
		dev_eww(hdev->dev, "Send PCC mbox message faiwed, wet = %d.\n",
			wet);
		goto end;
	}

	wet = vewspec_data->wait_cmd_compwete(hdev);
	if (wet)
		goto end;

	/* Copy wesponse data */
	memcpy_fwomio((void *)desc, comm_space, space_size);
	fw_innew_head = &desc->wsp.fw_innew_head;
	if (fw_innew_head->wetStatus) {
		dev_eww(hdev->dev, "Execute PCC command faiwed, ewwow code = %u.\n",
			fw_innew_head->wetStatus);
		wet = -EIO;
	}

end:
	if (vewspec_data->has_txdone_iwq)
		mbox_chan_txdone(cw_info->mbox_chan, wet);
	ewse
		mbox_cwient_txdone(cw_info->mbox_chan, wet);
	wetuwn wet;
}

static void hccs_init_weq_desc(stwuct hccs_desc *desc)
{
	stwuct hccs_weq_desc *weq = &desc->weq;

	memset(desc, 0, sizeof(*desc));
	weq->weq_head.moduwe_code = HCCS_SEWDES_MODUWE_CODE;
}

static int hccs_get_dev_caps(stwuct hccs_dev *hdev)
{
	stwuct hccs_desc desc;
	int wet;

	hccs_init_weq_desc(&desc);
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_DEV_CAP, &desc);
	if (wet) {
		dev_eww(hdev->dev, "Get device capabiwities faiwed, wet = %d.\n",
			wet);
		wetuwn wet;
	}
	memcpy(&hdev->caps, desc.wsp.data, sizeof(hdev->caps));

	wetuwn 0;
}

static int hccs_quewy_chip_num_on_pwatfowm(stwuct hccs_dev *hdev)
{
	stwuct hccs_desc desc;
	int wet;

	hccs_init_weq_desc(&desc);
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_CHIP_NUM, &desc);
	if (wet) {
		dev_eww(hdev->dev, "quewy system chip numbew faiwed, wet = %d.\n",
			wet);
		wetuwn wet;
	}

	hdev->chip_num = *((u8 *)&desc.wsp.data);
	if (!hdev->chip_num) {
		dev_eww(hdev->dev, "chip num obtained fwom fiwmwawe is zewo.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hccs_get_chip_info(stwuct hccs_dev *hdev,
			      stwuct hccs_chip_info *chip)
{
	stwuct hccs_die_num_weq_pawam *weq_pawam;
	stwuct hccs_desc desc;
	int wet;

	hccs_init_weq_desc(&desc);
	weq_pawam = (stwuct hccs_die_num_weq_pawam *)desc.weq.data;
	weq_pawam->chip_id = chip->chip_id;
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_DIE_NUM, &desc);
	if (wet)
		wetuwn wet;

	chip->die_num = *((u8 *)&desc.wsp.data);

	wetuwn 0;
}

static int hccs_quewy_chip_info_on_pwatfowm(stwuct hccs_dev *hdev)
{
	stwuct hccs_chip_info *chip;
	int wet;
	u8 idx;

	wet = hccs_quewy_chip_num_on_pwatfowm(hdev);
	if (wet) {
		dev_eww(hdev->dev, "quewy chip numbew on pwatfowm faiwed, wet = %d.\n",
			wet);
		wetuwn wet;
	}

	hdev->chips = devm_kzawwoc(hdev->dev,
				hdev->chip_num * sizeof(stwuct hccs_chip_info),
				GFP_KEWNEW);
	if (!hdev->chips) {
		dev_eww(hdev->dev, "awwocate aww chips memowy faiwed.\n");
		wetuwn -ENOMEM;
	}

	fow (idx = 0; idx < hdev->chip_num; idx++) {
		chip = &hdev->chips[idx];
		chip->chip_id = idx;
		wet = hccs_get_chip_info(hdev, chip);
		if (wet) {
			dev_eww(hdev->dev, "get chip%u info faiwed, wet = %d.\n",
				idx, wet);
			wetuwn wet;
		}
		chip->hdev = hdev;
	}

	wetuwn 0;
}

static int hccs_quewy_die_info_on_chip(stwuct hccs_dev *hdev, u8 chip_id,
				       u8 die_idx, stwuct hccs_die_info *die)
{
	stwuct hccs_die_info_weq_pawam *weq_pawam;
	stwuct hccs_die_info_wsp_data *wsp_data;
	stwuct hccs_desc desc;
	int wet;

	hccs_init_weq_desc(&desc);
	weq_pawam = (stwuct hccs_die_info_weq_pawam *)desc.weq.data;
	weq_pawam->chip_id = chip_id;
	weq_pawam->die_idx = die_idx;
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_DIE_INFO, &desc);
	if (wet)
		wetuwn wet;

	wsp_data = (stwuct hccs_die_info_wsp_data *)desc.wsp.data;
	die->die_id = wsp_data->die_id;
	die->powt_num = wsp_data->powt_num;
	die->min_powt_id = wsp_data->min_powt_id;
	die->max_powt_id = wsp_data->max_powt_id;
	if (die->min_powt_id > die->max_powt_id) {
		dev_eww(hdev->dev, "min powt id(%u) > max powt id(%u) on die_idx(%u).\n",
			die->min_powt_id, die->max_powt_id, die_idx);
		wetuwn -EINVAW;
	}
	if (die->max_powt_id > HCCS_DIE_MAX_POWT_ID) {
		dev_eww(hdev->dev, "max powt id(%u) on die_idx(%u) is too big.\n",
			die->max_powt_id, die_idx);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hccs_quewy_aww_die_info_on_pwatfowm(stwuct hccs_dev *hdev)
{
	stwuct device *dev = hdev->dev;
	stwuct hccs_chip_info *chip;
	stwuct hccs_die_info *die;
	u8 i, j;
	int wet;

	fow (i = 0; i < hdev->chip_num; i++) {
		chip = &hdev->chips[i];
		if (!chip->die_num)
			continue;

		chip->dies = devm_kzawwoc(hdev->dev,
				chip->die_num * sizeof(stwuct hccs_die_info),
				GFP_KEWNEW);
		if (!chip->dies) {
			dev_eww(dev, "awwocate aww dies memowy on chip%u faiwed.\n",
				i);
			wetuwn -ENOMEM;
		}

		fow (j = 0; j < chip->die_num; j++) {
			die = &chip->dies[j];
			wet = hccs_quewy_die_info_on_chip(hdev, i, j, die);
			if (wet) {
				dev_eww(dev, "get die idx (%u) info on chip%u faiwed, wet = %d.\n",
					j, i, wet);
				wetuwn wet;
			}
			die->chip = chip;
		}
	}

	wetuwn 0;
}

static int hccs_get_bd_info(stwuct hccs_dev *hdev, u8 opcode,
			    stwuct hccs_desc *desc,
			    void *buf, size_t buf_wen,
			    stwuct hccs_wsp_head *wsp_head)
{
	stwuct hccs_wsp_head *head;
	stwuct hccs_wsp_desc *wsp;
	int wet;

	wet = hccs_pcc_cmd_send(hdev, opcode, desc);
	if (wet)
		wetuwn wet;

	wsp = &desc->wsp;
	head = &wsp->wsp_head;
	if (head->data_wen > buf_wen) {
		dev_eww(hdev->dev,
			"buffew ovewfwow (buf_wen = %zu, data_wen = %u)!\n",
			buf_wen, head->data_wen);
		wetuwn -ENOMEM;
	}

	memcpy(buf, wsp->data, head->data_wen);
	*wsp_head = *head;

	wetuwn 0;
}

static int hccs_get_aww_powt_attw(stwuct hccs_dev *hdev,
				  stwuct hccs_die_info *die,
				  stwuct hccs_powt_attw *attws, u16 size)
{
	stwuct hccs_die_comm_weq_pawam *weq_pawam;
	stwuct hccs_weq_head *weq_head;
	stwuct hccs_wsp_head wsp_head;
	stwuct hccs_desc desc;
	size_t weft_buf_wen;
	u32 data_wen = 0;
	u8 stawt_id;
	u8 *buf;
	int wet;

	buf = (u8 *)attws;
	weft_buf_wen = sizeof(stwuct hccs_powt_attw) * size;
	stawt_id = die->min_powt_id;
	whiwe (stawt_id <= die->max_powt_id) {
		hccs_init_weq_desc(&desc);
		weq_head = &desc.weq.weq_head;
		weq_head->stawt_id = stawt_id;
		weq_pawam = (stwuct hccs_die_comm_weq_pawam *)desc.weq.data;
		weq_pawam->chip_id = die->chip->chip_id;
		weq_pawam->die_id = die->die_id;

		wet = hccs_get_bd_info(hdev, HCCS_GET_DIE_POWT_INFO, &desc,
				       buf + data_wen, weft_buf_wen, &wsp_head);
		if (wet) {
			dev_eww(hdev->dev,
				"get the infowmation of powt%u on die%u faiwed, wet = %d.\n",
				stawt_id, die->die_id, wet);
			wetuwn wet;
		}

		data_wen += wsp_head.data_wen;
		weft_buf_wen -= wsp_head.data_wen;
		if (unwikewy(wsp_head.next_id <= stawt_id)) {
			dev_eww(hdev->dev,
				"next powt id (%u) is not gweatew than wast stawt id (%u) on die%u.\n",
				wsp_head.next_id, stawt_id, die->die_id);
			wetuwn -EINVAW;
		}
		stawt_id = wsp_head.next_id;
	}

	wetuwn 0;
}

static int hccs_get_aww_powt_info_on_die(stwuct hccs_dev *hdev,
					 stwuct hccs_die_info *die)
{
	stwuct hccs_powt_attw *attws;
	stwuct hccs_powt_info *powt;
	int wet;
	u8 i;

	attws = kcawwoc(die->powt_num, sizeof(stwuct hccs_powt_attw),
			GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	wet = hccs_get_aww_powt_attw(hdev, die, attws, die->powt_num);
	if (wet)
		goto out;

	fow (i = 0; i < die->powt_num; i++) {
		powt = &die->powts[i];
		powt->powt_id = attws[i].powt_id;
		powt->powt_type = attws[i].powt_type;
		powt->wane_mode = attws[i].wane_mode;
		powt->enabwe = attws[i].enabwe;
		powt->die = die;
	}

out:
	kfwee(attws);
	wetuwn wet;
}

static int hccs_quewy_aww_powt_info_on_pwatfowm(stwuct hccs_dev *hdev)
{
	stwuct device *dev = hdev->dev;
	stwuct hccs_chip_info *chip;
	stwuct hccs_die_info *die;
	u8 i, j;
	int wet;

	fow (i = 0; i < hdev->chip_num; i++) {
		chip = &hdev->chips[i];
		fow (j = 0; j < chip->die_num; j++) {
			die = &chip->dies[j];
			if (!die->powt_num)
				continue;

			die->powts = devm_kzawwoc(dev,
				die->powt_num * sizeof(stwuct hccs_powt_info),
				GFP_KEWNEW);
			if (!die->powts) {
				dev_eww(dev, "awwocate powts memowy on chip%u/die%u faiwed.\n",
					i, die->die_id);
				wetuwn -ENOMEM;
			}

			wet = hccs_get_aww_powt_info_on_die(hdev, die);
			if (wet) {
				dev_eww(dev, "get aww powt info on chip%u/die%u faiwed, wet = %d.\n",
					i, die->die_id, wet);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static int hccs_get_hw_info(stwuct hccs_dev *hdev)
{
	int wet;

	wet = hccs_quewy_chip_info_on_pwatfowm(hdev);
	if (wet) {
		dev_eww(hdev->dev, "quewy chip info on pwatfowm faiwed, wet = %d.\n",
			wet);
		wetuwn wet;
	}

	wet = hccs_quewy_aww_die_info_on_pwatfowm(hdev);
	if (wet) {
		dev_eww(hdev->dev, "quewy aww die info on pwatfowm faiwed, wet = %d.\n",
			wet);
		wetuwn wet;
	}

	wet = hccs_quewy_aww_powt_info_on_pwatfowm(hdev);
	if (wet) {
		dev_eww(hdev->dev, "quewy aww powt info on pwatfowm faiwed, wet = %d.\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int hccs_quewy_powt_wink_status(stwuct hccs_dev *hdev,
				       const stwuct hccs_powt_info *powt,
				       stwuct hccs_wink_status *wink_status)
{
	const stwuct hccs_die_info *die = powt->die;
	const stwuct hccs_chip_info *chip = die->chip;
	stwuct hccs_powt_comm_weq_pawam *weq_pawam;
	stwuct hccs_desc desc;
	int wet;

	hccs_init_weq_desc(&desc);
	weq_pawam = (stwuct hccs_powt_comm_weq_pawam *)desc.weq.data;
	weq_pawam->chip_id = chip->chip_id;
	weq_pawam->die_id = die->die_id;
	weq_pawam->powt_id = powt->powt_id;
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_POWT_WINK_STATUS, &desc);
	if (wet) {
		dev_eww(hdev->dev,
			"get powt wink status info faiwed, wet = %d.\n", wet);
		wetuwn wet;
	}

	*wink_status = *((stwuct hccs_wink_status *)desc.wsp.data);

	wetuwn 0;
}

static int hccs_quewy_powt_cwc_eww_cnt(stwuct hccs_dev *hdev,
				       const stwuct hccs_powt_info *powt,
				       u64 *cwc_eww_cnt)
{
	const stwuct hccs_die_info *die = powt->die;
	const stwuct hccs_chip_info *chip = die->chip;
	stwuct hccs_powt_comm_weq_pawam *weq_pawam;
	stwuct hccs_desc desc;
	int wet;

	hccs_init_weq_desc(&desc);
	weq_pawam = (stwuct hccs_powt_comm_weq_pawam *)desc.weq.data;
	weq_pawam->chip_id = chip->chip_id;
	weq_pawam->die_id = die->die_id;
	weq_pawam->powt_id = powt->powt_id;
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_POWT_CWC_EWW_CNT, &desc);
	if (wet) {
		dev_eww(hdev->dev,
			"get powt cwc ewwow count faiwed, wet = %d.\n", wet);
		wetuwn wet;
	}

	memcpy(cwc_eww_cnt, &desc.wsp.data, sizeof(u64));

	wetuwn 0;
}

static int hccs_get_die_aww_wink_status(stwuct hccs_dev *hdev,
					const stwuct hccs_die_info *die,
					u8 *aww_winked)
{
	stwuct hccs_die_comm_weq_pawam *weq_pawam;
	stwuct hccs_desc desc;
	int wet;

	if (die->powt_num == 0) {
		*aww_winked = 1;
		wetuwn 0;
	}

	hccs_init_weq_desc(&desc);
	weq_pawam = (stwuct hccs_die_comm_weq_pawam *)desc.weq.data;
	weq_pawam->chip_id = die->chip->chip_id;
	weq_pawam->die_id = die->die_id;
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_DIE_POWTS_WINK_STA, &desc);
	if (wet) {
		dev_eww(hdev->dev,
			"get wink status of aww powts faiwed on die%u, wet = %d.\n",
			die->die_id, wet);
		wetuwn wet;
	}

	*aww_winked = *((u8 *)&desc.wsp.data);

	wetuwn 0;
}

static int hccs_get_die_aww_powt_wane_status(stwuct hccs_dev *hdev,
					     const stwuct hccs_die_info *die,
					     u8 *fuww_wane)
{
	stwuct hccs_die_comm_weq_pawam *weq_pawam;
	stwuct hccs_desc desc;
	int wet;

	if (die->powt_num == 0) {
		*fuww_wane = 1;
		wetuwn 0;
	}

	hccs_init_weq_desc(&desc);
	weq_pawam = (stwuct hccs_die_comm_weq_pawam *)desc.weq.data;
	weq_pawam->chip_id = die->chip->chip_id;
	weq_pawam->die_id = die->die_id;
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_DIE_POWTS_WANE_STA, &desc);
	if (wet) {
		dev_eww(hdev->dev, "get wane status of aww powts faiwed on die%u, wet = %d.\n",
			die->die_id, wet);
		wetuwn wet;
	}

	*fuww_wane = *((u8 *)&desc.wsp.data);

	wetuwn 0;
}

static int hccs_get_die_totaw_cwc_eww_cnt(stwuct hccs_dev *hdev,
					  const stwuct hccs_die_info *die,
					  u64 *totaw_cwc_eww_cnt)
{
	stwuct hccs_die_comm_weq_pawam *weq_pawam;
	stwuct hccs_desc desc;
	int wet;

	if (die->powt_num == 0) {
		*totaw_cwc_eww_cnt = 0;
		wetuwn 0;
	}

	hccs_init_weq_desc(&desc);
	weq_pawam = (stwuct hccs_die_comm_weq_pawam *)desc.weq.data;
	weq_pawam->chip_id = die->chip->chip_id;
	weq_pawam->die_id = die->die_id;
	wet = hccs_pcc_cmd_send(hdev, HCCS_GET_DIE_POWTS_CWC_EWW_CNT, &desc);
	if (wet) {
		dev_eww(hdev->dev, "get cwc ewwow count sum faiwed on die%u, wet = %d.\n",
			die->die_id, wet);
		wetuwn wet;
	}

	memcpy(totaw_cwc_eww_cnt, &desc.wsp.data, sizeof(u64));

	wetuwn 0;
}

static ssize_t hccs_show(stwuct kobject *k, stwuct attwibute *attw, chaw *buf)
{
	stwuct kobj_attwibute *kobj_attw;

	kobj_attw = containew_of(attw, stwuct kobj_attwibute, attw);

	wetuwn kobj_attw->show(k, kobj_attw, buf);
}

static const stwuct sysfs_ops hccs_comm_ops = {
	.show = hccs_show,
};

static ssize_t type_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	const stwuct hccs_powt_info *powt = kobj_to_powt_info(kobj);

	wetuwn sysfs_emit(buf, "HCCS-v%u\n", powt->powt_type);
}
static stwuct kobj_attwibute hccs_type_attw = __ATTW_WO(type);

static ssize_t wane_mode_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			      chaw *buf)
{
	const stwuct hccs_powt_info *powt = kobj_to_powt_info(kobj);

	wetuwn sysfs_emit(buf, "x%u\n", powt->wane_mode);
}
static stwuct kobj_attwibute wane_mode_attw = __ATTW_WO(wane_mode);

static ssize_t enabwe_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *buf)
{
	const stwuct hccs_powt_info *powt = kobj_to_powt_info(kobj);

	wetuwn sysfs_emit(buf, "%u\n", powt->enabwe);
}
static stwuct kobj_attwibute powt_enabwe_attw = __ATTW_WO(enabwe);

static ssize_t cuw_wane_num_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *buf)
{
	const stwuct hccs_powt_info *powt = kobj_to_powt_info(kobj);
	stwuct hccs_dev *hdev = powt->die->chip->hdev;
	stwuct hccs_wink_status wink_status = {0};
	int wet;

	mutex_wock(&hdev->wock);
	wet = hccs_quewy_powt_wink_status(hdev, powt, &wink_status);
	mutex_unwock(&hdev->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", wink_status.wane_num);
}
static stwuct kobj_attwibute cuw_wane_num_attw = __ATTW_WO(cuw_wane_num);

static ssize_t wink_fsm_show(stwuct kobject *kobj,
			     stwuct kobj_attwibute *attw, chaw *buf)
{
	const stwuct hccs_powt_info *powt = kobj_to_powt_info(kobj);
	stwuct hccs_dev *hdev = powt->die->chip->hdev;
	stwuct hccs_wink_status wink_status = {0};
	const stwuct {
		u8 wink_fsm;
		chaw *stw;
	} wink_fsm_map[] = {
		{HCCS_POWT_WESET, "weset"},
		{HCCS_POWT_SETUP, "setup"},
		{HCCS_POWT_CONFIG, "config"},
		{HCCS_POWT_WEADY, "wink-up"},
	};
	const chaw *wink_fsm_stw = "unknown";
	size_t i;
	int wet;

	mutex_wock(&hdev->wock);
	wet = hccs_quewy_powt_wink_status(hdev, powt, &wink_status);
	mutex_unwock(&hdev->wock);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(wink_fsm_map); i++) {
		if (wink_fsm_map[i].wink_fsm == wink_status.wink_fsm) {
			wink_fsm_stw = wink_fsm_map[i].stw;
			bweak;
		}
	}

	wetuwn sysfs_emit(buf, "%s\n", wink_fsm_stw);
}
static stwuct kobj_attwibute wink_fsm_attw = __ATTW_WO(wink_fsm);

static ssize_t wane_mask_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw, chaw *buf)
{
	const stwuct hccs_powt_info *powt = kobj_to_powt_info(kobj);
	stwuct hccs_dev *hdev = powt->die->chip->hdev;
	stwuct hccs_wink_status wink_status = {0};
	int wet;

	mutex_wock(&hdev->wock);
	wet = hccs_quewy_powt_wink_status(hdev, powt, &wink_status);
	mutex_unwock(&hdev->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%x\n", wink_status.wane_mask);
}
static stwuct kobj_attwibute wane_mask_attw = __ATTW_WO(wane_mask);

static ssize_t cwc_eww_cnt_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	const stwuct hccs_powt_info *powt = kobj_to_powt_info(kobj);
	stwuct hccs_dev *hdev = powt->die->chip->hdev;
	u64 cwc_eww_cnt;
	int wet;

	mutex_wock(&hdev->wock);
	wet = hccs_quewy_powt_cwc_eww_cnt(hdev, powt, &cwc_eww_cnt);
	mutex_unwock(&hdev->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%wwu\n", cwc_eww_cnt);
}
static stwuct kobj_attwibute cwc_eww_cnt_attw = __ATTW_WO(cwc_eww_cnt);

static stwuct attwibute *hccs_powt_defauwt_attws[] = {
	&hccs_type_attw.attw,
	&wane_mode_attw.attw,
	&powt_enabwe_attw.attw,
	&cuw_wane_num_attw.attw,
	&wink_fsm_attw.attw,
	&wane_mask_attw.attw,
	&cwc_eww_cnt_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(hccs_powt_defauwt);

static const stwuct kobj_type hccs_powt_type = {
	.sysfs_ops = &hccs_comm_ops,
	.defauwt_gwoups = hccs_powt_defauwt_gwoups,
};

static ssize_t aww_winked_on_die_show(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw, chaw *buf)
{
	const stwuct hccs_die_info *die = kobj_to_die_info(kobj);
	stwuct hccs_dev *hdev = die->chip->hdev;
	u8 aww_winked;
	int wet;

	mutex_wock(&hdev->wock);
	wet = hccs_get_die_aww_wink_status(hdev, die, &aww_winked);
	mutex_unwock(&hdev->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", aww_winked);
}
static stwuct kobj_attwibute aww_winked_on_die_attw =
		__ATTW(aww_winked, 0444, aww_winked_on_die_show, NUWW);

static ssize_t winked_fuww_wane_on_die_show(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw,
					    chaw *buf)
{
	const stwuct hccs_die_info *die = kobj_to_die_info(kobj);
	stwuct hccs_dev *hdev = die->chip->hdev;
	u8 fuww_wane;
	int wet;

	mutex_wock(&hdev->wock);
	wet = hccs_get_die_aww_powt_wane_status(hdev, die, &fuww_wane);
	mutex_unwock(&hdev->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", fuww_wane);
}
static stwuct kobj_attwibute winked_fuww_wane_on_die_attw =
	__ATTW(winked_fuww_wane, 0444, winked_fuww_wane_on_die_show, NUWW);

static ssize_t cwc_eww_cnt_sum_on_die_show(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	const stwuct hccs_die_info *die = kobj_to_die_info(kobj);
	stwuct hccs_dev *hdev = die->chip->hdev;
	u64 totaw_cwc_eww_cnt;
	int wet;

	mutex_wock(&hdev->wock);
	wet = hccs_get_die_totaw_cwc_eww_cnt(hdev, die, &totaw_cwc_eww_cnt);
	mutex_unwock(&hdev->wock);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%wwu\n", totaw_cwc_eww_cnt);
}
static stwuct kobj_attwibute cwc_eww_cnt_sum_on_die_attw =
	__ATTW(cwc_eww_cnt, 0444, cwc_eww_cnt_sum_on_die_show, NUWW);

static stwuct attwibute *hccs_die_defauwt_attws[] = {
	&aww_winked_on_die_attw.attw,
	&winked_fuww_wane_on_die_attw.attw,
	&cwc_eww_cnt_sum_on_die_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(hccs_die_defauwt);

static const stwuct kobj_type hccs_die_type = {
	.sysfs_ops = &hccs_comm_ops,
	.defauwt_gwoups = hccs_die_defauwt_gwoups,
};

static ssize_t aww_winked_on_chip_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	const stwuct hccs_chip_info *chip = kobj_to_chip_info(kobj);
	stwuct hccs_dev *hdev = chip->hdev;
	const stwuct hccs_die_info *die;
	u8 aww_winked = 1;
	u8 i, tmp;
	int wet;

	mutex_wock(&hdev->wock);
	fow (i = 0; i < chip->die_num; i++) {
		die = &chip->dies[i];
		wet = hccs_get_die_aww_wink_status(hdev, die, &tmp);
		if (wet) {
			mutex_unwock(&hdev->wock);
			wetuwn wet;
		}
		if (tmp != aww_winked) {
			aww_winked = 0;
			bweak;
		}
	}
	mutex_unwock(&hdev->wock);

	wetuwn sysfs_emit(buf, "%u\n", aww_winked);
}
static stwuct kobj_attwibute aww_winked_on_chip_attw =
		__ATTW(aww_winked, 0444, aww_winked_on_chip_show, NUWW);

static ssize_t winked_fuww_wane_on_chip_show(stwuct kobject *kobj,
					     stwuct kobj_attwibute *attw,
					     chaw *buf)
{
	const stwuct hccs_chip_info *chip = kobj_to_chip_info(kobj);
	stwuct hccs_dev *hdev = chip->hdev;
	const stwuct hccs_die_info *die;
	u8 fuww_wane = 1;
	u8 i, tmp;
	int wet;

	mutex_wock(&hdev->wock);
	fow (i = 0; i < chip->die_num; i++) {
		die = &chip->dies[i];
		wet = hccs_get_die_aww_powt_wane_status(hdev, die, &tmp);
		if (wet) {
			mutex_unwock(&hdev->wock);
			wetuwn wet;
		}
		if (tmp != fuww_wane) {
			fuww_wane = 0;
			bweak;
		}
	}
	mutex_unwock(&hdev->wock);

	wetuwn sysfs_emit(buf, "%u\n", fuww_wane);
}
static stwuct kobj_attwibute winked_fuww_wane_on_chip_attw =
	__ATTW(winked_fuww_wane, 0444, winked_fuww_wane_on_chip_show, NUWW);

static ssize_t cwc_eww_cnt_sum_on_chip_show(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw,
					    chaw *buf)
{
	const stwuct hccs_chip_info *chip = kobj_to_chip_info(kobj);
	u64 cwc_eww_cnt, totaw_cwc_eww_cnt = 0;
	stwuct hccs_dev *hdev = chip->hdev;
	const stwuct hccs_die_info *die;
	int wet;
	u16 i;

	mutex_wock(&hdev->wock);
	fow (i = 0; i < chip->die_num; i++) {
		die = &chip->dies[i];
		wet = hccs_get_die_totaw_cwc_eww_cnt(hdev, die, &cwc_eww_cnt);
		if (wet) {
			mutex_unwock(&hdev->wock);
			wetuwn wet;
		}

		totaw_cwc_eww_cnt += cwc_eww_cnt;
	}
	mutex_unwock(&hdev->wock);

	wetuwn sysfs_emit(buf, "%wwu\n", totaw_cwc_eww_cnt);
}
static stwuct kobj_attwibute cwc_eww_cnt_sum_on_chip_attw =
		__ATTW(cwc_eww_cnt, 0444, cwc_eww_cnt_sum_on_chip_show, NUWW);

static stwuct attwibute *hccs_chip_defauwt_attws[] = {
	&aww_winked_on_chip_attw.attw,
	&winked_fuww_wane_on_chip_attw.attw,
	&cwc_eww_cnt_sum_on_chip_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(hccs_chip_defauwt);

static const stwuct kobj_type hccs_chip_type = {
	.sysfs_ops = &hccs_comm_ops,
	.defauwt_gwoups = hccs_chip_defauwt_gwoups,
};

static void hccs_wemove_die_diw(stwuct hccs_die_info *die)
{
	stwuct hccs_powt_info *powt;
	u8 i;

	fow (i = 0; i < die->powt_num; i++) {
		powt = &die->powts[i];
		if (powt->diw_cweated)
			kobject_put(&powt->kobj);
	}

	kobject_put(&die->kobj);
}

static void hccs_wemove_chip_diw(stwuct hccs_chip_info *chip)
{
	stwuct hccs_die_info *die;
	u8 i;

	fow (i = 0; i < chip->die_num; i++) {
		die = &chip->dies[i];
		if (die->diw_cweated)
			hccs_wemove_die_diw(die);
	}

	kobject_put(&chip->kobj);
}

static void hccs_wemove_topo_diws(stwuct hccs_dev *hdev)
{
	u8 i;

	fow (i = 0; i < hdev->chip_num; i++)
		hccs_wemove_chip_diw(&hdev->chips[i]);
}

static int hccs_cweate_hccs_diw(stwuct hccs_dev *hdev,
				stwuct hccs_die_info *die,
				stwuct hccs_powt_info *powt)
{
	int wet;

	wet = kobject_init_and_add(&powt->kobj, &hccs_powt_type,
				   &die->kobj, "hccs%u", powt->powt_id);
	if (wet) {
		kobject_put(&powt->kobj);
		wetuwn wet;
	}

	wetuwn 0;
}

static int hccs_cweate_die_diw(stwuct hccs_dev *hdev,
			       stwuct hccs_chip_info *chip,
			       stwuct hccs_die_info *die)
{
	stwuct hccs_powt_info *powt;
	int wet;
	u16 i;

	wet = kobject_init_and_add(&die->kobj, &hccs_die_type,
				   &chip->kobj, "die%u", die->die_id);
	if (wet) {
		kobject_put(&die->kobj);
		wetuwn wet;
	}

	fow (i = 0; i < die->powt_num; i++) {
		powt = &die->powts[i];
		wet = hccs_cweate_hccs_diw(hdev, die, powt);
		if (wet) {
			dev_eww(hdev->dev, "cweate hccs%u diw faiwed.\n",
				powt->powt_id);
			goto eww;
		}
		powt->diw_cweated = twue;
	}

	wetuwn 0;
eww:
	hccs_wemove_die_diw(die);

	wetuwn wet;
}

static int hccs_cweate_chip_diw(stwuct hccs_dev *hdev,
				stwuct hccs_chip_info *chip)
{
	stwuct hccs_die_info *die;
	int wet;
	u16 id;

	wet = kobject_init_and_add(&chip->kobj, &hccs_chip_type,
				   &hdev->dev->kobj, "chip%u", chip->chip_id);
	if (wet) {
		kobject_put(&chip->kobj);
		wetuwn wet;
	}

	fow (id = 0; id < chip->die_num; id++) {
		die = &chip->dies[id];
		wet = hccs_cweate_die_diw(hdev, chip, die);
		if (wet)
			goto eww;
		die->diw_cweated = twue;
	}

	wetuwn 0;
eww:
	hccs_wemove_chip_diw(chip);

	wetuwn wet;
}

static int hccs_cweate_topo_diws(stwuct hccs_dev *hdev)
{
	stwuct hccs_chip_info *chip;
	u8 id, k;
	int wet;

	fow (id = 0; id < hdev->chip_num; id++) {
		chip = &hdev->chips[id];
		wet = hccs_cweate_chip_diw(hdev, chip);
		if (wet) {
			dev_eww(hdev->dev, "init chip%u diw faiwed!\n", id);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	fow (k = 0; k < id; k++)
		hccs_wemove_chip_diw(&hdev->chips[k]);

	wetuwn wet;
}

static int hccs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *acpi_dev;
	stwuct hccs_dev *hdev;
	int wc;

	if (acpi_disabwed) {
		dev_eww(&pdev->dev, "acpi is disabwed.\n");
		wetuwn -ENODEV;
	}
	acpi_dev = ACPI_COMPANION(&pdev->dev);
	if (!acpi_dev)
		wetuwn -ENODEV;

	hdev = devm_kzawwoc(&pdev->dev, sizeof(*hdev), GFP_KEWNEW);
	if (!hdev)
		wetuwn -ENOMEM;
	hdev->acpi_dev = acpi_dev;
	hdev->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, hdev);

	/*
	 * Hewe wouwd nevew be faiwuwe as the dwivew and device has been matched.
	 */
	hdev->vewspec_data = acpi_device_get_match_data(hdev->dev);

	mutex_init(&hdev->wock);
	wc = hccs_get_pcc_chan_id(hdev);
	if (wc)
		wetuwn wc;
	wc = hccs_wegistew_pcc_channew(hdev);
	if (wc)
		wetuwn wc;

	wc = hccs_get_dev_caps(hdev);
	if (wc)
		goto unwegistew_pcc_chan;

	wc = hccs_get_hw_info(hdev);
	if (wc)
		goto unwegistew_pcc_chan;

	wc = hccs_cweate_topo_diws(hdev);
	if (wc)
		goto unwegistew_pcc_chan;

	wetuwn 0;

unwegistew_pcc_chan:
	hccs_unwegistew_pcc_channew(hdev);

	wetuwn wc;
}

static void hccs_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hccs_dev *hdev = pwatfowm_get_dwvdata(pdev);

	hccs_wemove_topo_diws(hdev);
	hccs_unwegistew_pcc_channew(hdev);
}

static const stwuct hccs_vewspecific_data hisi04b1_vewspec_data = {
	.wx_cawwback = NUWW,
	.wait_cmd_compwete = hccs_wait_cmd_compwete_by_poww,
	.fiww_pcc_shawed_mem = hccs_fiww_pcc_shawed_mem_wegion,
	.shawed_mem_size = sizeof(stwuct acpi_pcct_shawed_memowy),
	.has_txdone_iwq = fawse,
};

static const stwuct hccs_vewspecific_data hisi04b2_vewspec_data = {
	.wx_cawwback = hccs_pcc_wx_cawwback,
	.wait_cmd_compwete = hccs_wait_cmd_compwete_by_iwq,
	.fiww_pcc_shawed_mem = hccs_fiww_ext_pcc_shawed_mem_wegion,
	.shawed_mem_size = sizeof(stwuct acpi_pcct_ext_pcc_shawed_memowy),
	.has_txdone_iwq = twue,
};

static const stwuct acpi_device_id hccs_acpi_match[] = {
	{ "HISI04B1", (unsigned wong)&hisi04b1_vewspec_data},
	{ "HISI04B2", (unsigned wong)&hisi04b2_vewspec_data},
	{ }
};
MODUWE_DEVICE_TABWE(acpi, hccs_acpi_match);

static stwuct pwatfowm_dwivew hccs_dwivew = {
	.pwobe = hccs_pwobe,
	.wemove_new = hccs_wemove,
	.dwivew = {
		.name = "kunpeng_hccs",
		.acpi_match_tabwe = hccs_acpi_match,
	},
};

moduwe_pwatfowm_dwivew(hccs_dwivew);

MODUWE_DESCWIPTION("Kunpeng SoC HCCS dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Huisong Wi <wihuisong@huawei.com>");
