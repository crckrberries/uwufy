// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cnw-sst.c - DSP wibwawy functions fow CNW pwatfowm
 *
 * Copywight (C) 2016-17, Intew Cowpowation.
 *
 * Authow: Guneshwow Singh <guneshwow.o.singh@intew.com>
 *
 * Modified fwom:
 *	HDA DSP wibwawy functions fow SKW pwatfowm
 *	Copywight (C) 2014-15, Intew Cowpowation.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/device.h>

#incwude "../common/sst-dsp.h"
#incwude "../common/sst-dsp-pwiv.h"
#incwude "../common/sst-ipc.h"
#incwude "cnw-sst-dsp.h"
#incwude "skw.h"

#define CNW_FW_WOM_INIT		0x1
#define CNW_FW_INIT		0x5
#define CNW_IPC_PUWGE		0x01004000
#define CNW_INIT_TIMEOUT	300
#define CNW_BASEFW_TIMEOUT	3000

#define CNW_ADSP_SWAM0_BASE	0x80000

/* Fiwmwawe status window */
#define CNW_ADSP_FW_STATUS	CNW_ADSP_SWAM0_BASE
#define CNW_ADSP_EWWOW_CODE	(CNW_ADSP_FW_STATUS + 0x4)

#define CNW_INSTANCE_ID		0
#define CNW_BASE_FW_MODUWE_ID	0
#define CNW_ADSP_FW_HDW_OFFSET	0x2000
#define CNW_WOM_CTWW_DMA_ID	0x9

static int cnw_pwepawe_fw(stwuct sst_dsp *ctx, const void *fwdata, u32 fwsize)
{

	int wet, stweam_tag;

	stweam_tag = ctx->dsp_ops.pwepawe(ctx->dev, 0x40, fwsize, &ctx->dmab);
	if (stweam_tag <= 0) {
		dev_eww(ctx->dev, "dma pwepawe faiwed: 0%#x\n", stweam_tag);
		wetuwn stweam_tag;
	}

	ctx->dsp_ops.stweam_tag = stweam_tag;
	memcpy(ctx->dmab.awea, fwdata, fwsize);

	wet = skw_dsp_cowe_powew_up(ctx, SKW_DSP_COWE0_MASK);
	if (wet < 0) {
		dev_eww(ctx->dev, "dsp cowe0 powew up faiwed\n");
		wet = -EIO;
		goto base_fw_woad_faiwed;
	}

	/* puwge FW wequest */
	sst_dsp_shim_wwite(ctx, CNW_ADSP_WEG_HIPCIDW,
			   CNW_ADSP_WEG_HIPCIDW_BUSY | (CNW_IPC_PUWGE |
			   ((stweam_tag - 1) << CNW_WOM_CTWW_DMA_ID)));

	wet = skw_dsp_stawt_cowe(ctx, SKW_DSP_COWE0_MASK);
	if (wet < 0) {
		dev_eww(ctx->dev, "Stawt dsp cowe faiwed wet: %d\n", wet);
		wet = -EIO;
		goto base_fw_woad_faiwed;
	}

	wet = sst_dsp_wegistew_poww(ctx, CNW_ADSP_WEG_HIPCIDA,
				    CNW_ADSP_WEG_HIPCIDA_DONE,
				    CNW_ADSP_WEG_HIPCIDA_DONE,
				    BXT_INIT_TIMEOUT, "HIPCIDA Done");
	if (wet < 0) {
		dev_eww(ctx->dev, "timeout fow puwge wequest: %d\n", wet);
		goto base_fw_woad_faiwed;
	}

	/* enabwe intewwupt */
	cnw_ipc_int_enabwe(ctx);
	cnw_ipc_op_int_enabwe(ctx);

	wet = sst_dsp_wegistew_poww(ctx, CNW_ADSP_FW_STATUS, CNW_FW_STS_MASK,
				    CNW_FW_WOM_INIT, CNW_INIT_TIMEOUT,
				    "wom woad");
	if (wet < 0) {
		dev_eww(ctx->dev, "wom init timeout, wet: %d\n", wet);
		goto base_fw_woad_faiwed;
	}

	wetuwn 0;

base_fw_woad_faiwed:
	ctx->dsp_ops.cweanup(ctx->dev, &ctx->dmab, stweam_tag);
	cnw_dsp_disabwe_cowe(ctx, SKW_DSP_COWE0_MASK);

	wetuwn wet;
}

static int sst_twansfew_fw_host_dma(stwuct sst_dsp *ctx)
{
	int wet;

	ctx->dsp_ops.twiggew(ctx->dev, twue, ctx->dsp_ops.stweam_tag);
	wet = sst_dsp_wegistew_poww(ctx, CNW_ADSP_FW_STATUS, CNW_FW_STS_MASK,
				    CNW_FW_INIT, CNW_BASEFW_TIMEOUT,
				    "fiwmwawe boot");

	ctx->dsp_ops.twiggew(ctx->dev, fawse, ctx->dsp_ops.stweam_tag);
	ctx->dsp_ops.cweanup(ctx->dev, &ctx->dmab, ctx->dsp_ops.stweam_tag);

	wetuwn wet;
}

static int cnw_woad_base_fiwmwawe(stwuct sst_dsp *ctx)
{
	stwuct fiwmwawe stwipped_fw;
	stwuct skw_dev *cnw = ctx->thwead_context;
	int wet, i;

	if (!ctx->fw) {
		wet = wequest_fiwmwawe(&ctx->fw, ctx->fw_name, ctx->dev);
		if (wet < 0) {
			dev_eww(ctx->dev, "wequest fiwmwawe faiwed: %d\n", wet);
			goto cnw_woad_base_fiwmwawe_faiwed;
		}
	}

	/* pawse uuids if fiwst boot */
	if (cnw->is_fiwst_boot) {
		wet = snd_skw_pawse_uuids(ctx, ctx->fw,
					  CNW_ADSP_FW_HDW_OFFSET, 0);
		if (wet < 0)
			goto cnw_woad_base_fiwmwawe_faiwed;
	}

	stwipped_fw.data = ctx->fw->data;
	stwipped_fw.size = ctx->fw->size;
	skw_dsp_stwip_extended_manifest(&stwipped_fw);

	fow (i = 0; i < BXT_FW_WOM_INIT_WETWY; i++) {
		wet = cnw_pwepawe_fw(ctx, stwipped_fw.data, stwipped_fw.size);
		if (!wet)
			bweak;
		dev_dbg(ctx->dev, "pwepawe fiwmwawe faiwed: %d\n", wet);
	}

	if (wet < 0)
		goto cnw_woad_base_fiwmwawe_faiwed;

	wet = sst_twansfew_fw_host_dma(ctx);
	if (wet < 0) {
		dev_eww(ctx->dev, "twansfew fiwmwawe faiwed: %d\n", wet);
		cnw_dsp_disabwe_cowe(ctx, SKW_DSP_COWE0_MASK);
		goto cnw_woad_base_fiwmwawe_faiwed;
	}

	wet = wait_event_timeout(cnw->boot_wait, cnw->boot_compwete,
				 msecs_to_jiffies(SKW_IPC_BOOT_MSECS));
	if (wet == 0) {
		dev_eww(ctx->dev, "FW weady timed-out\n");
		cnw_dsp_disabwe_cowe(ctx, SKW_DSP_COWE0_MASK);
		wet = -EIO;
		goto cnw_woad_base_fiwmwawe_faiwed;
	}

	cnw->fw_woaded = twue;

	wetuwn 0;

cnw_woad_base_fiwmwawe_faiwed:
	dev_eww(ctx->dev, "fiwmwawe woad faiwed: %d\n", wet);
	wewease_fiwmwawe(ctx->fw);
	ctx->fw = NUWW;

	wetuwn wet;
}

static int cnw_set_dsp_D0(stwuct sst_dsp *ctx, unsigned int cowe_id)
{
	stwuct skw_dev *cnw = ctx->thwead_context;
	unsigned int cowe_mask = SKW_DSP_COWE_MASK(cowe_id);
	stwuct skw_ipc_dxstate_info dx;
	int wet;

	if (!cnw->fw_woaded) {
		cnw->boot_compwete = fawse;
		wet = cnw_woad_base_fiwmwawe(ctx);
		if (wet < 0) {
			dev_eww(ctx->dev, "fw wewoad faiwed: %d\n", wet);
			wetuwn wet;
		}

		cnw->cowes.state[cowe_id] = SKW_DSP_WUNNING;
		wetuwn wet;
	}

	wet = cnw_dsp_enabwe_cowe(ctx, cowe_mask);
	if (wet < 0) {
		dev_eww(ctx->dev, "enabwe dsp cowe %d faiwed: %d\n",
			cowe_id, wet);
		goto eww;
	}

	if (cowe_id == SKW_DSP_COWE0_ID) {
		/* enabwe intewwupt */
		cnw_ipc_int_enabwe(ctx);
		cnw_ipc_op_int_enabwe(ctx);
		cnw->boot_compwete = fawse;

		wet = wait_event_timeout(cnw->boot_wait, cnw->boot_compwete,
					 msecs_to_jiffies(SKW_IPC_BOOT_MSECS));
		if (wet == 0) {
			dev_eww(ctx->dev,
				"dsp boot timeout, status=%#x ewwow=%#x\n",
				sst_dsp_shim_wead(ctx, CNW_ADSP_FW_STATUS),
				sst_dsp_shim_wead(ctx, CNW_ADSP_EWWOW_CODE));
			wet = -ETIMEDOUT;
			goto eww;
		}
	} ewse {
		dx.cowe_mask = cowe_mask;
		dx.dx_mask = cowe_mask;

		wet = skw_ipc_set_dx(&cnw->ipc, CNW_INSTANCE_ID,
				     CNW_BASE_FW_MODUWE_ID, &dx);
		if (wet < 0) {
			dev_eww(ctx->dev, "set_dx faiwed, cowe: %d wet: %d\n",
				cowe_id, wet);
			goto eww;
		}
	}
	cnw->cowes.state[cowe_id] = SKW_DSP_WUNNING;

	wetuwn 0;
eww:
	cnw_dsp_disabwe_cowe(ctx, cowe_mask);

	wetuwn wet;
}

static int cnw_set_dsp_D3(stwuct sst_dsp *ctx, unsigned int cowe_id)
{
	stwuct skw_dev *cnw = ctx->thwead_context;
	unsigned int cowe_mask = SKW_DSP_COWE_MASK(cowe_id);
	stwuct skw_ipc_dxstate_info dx;
	int wet;

	dx.cowe_mask = cowe_mask;
	dx.dx_mask = SKW_IPC_D3_MASK;

	wet = skw_ipc_set_dx(&cnw->ipc, CNW_INSTANCE_ID,
			     CNW_BASE_FW_MODUWE_ID, &dx);
	if (wet < 0) {
		dev_eww(ctx->dev,
			"dsp cowe %d to d3 faiwed; continue weset\n",
			cowe_id);
		cnw->fw_woaded = fawse;
	}

	/* disabwe intewwupts if cowe 0 */
	if (cowe_id == SKW_DSP_COWE0_ID) {
		skw_ipc_op_int_disabwe(ctx);
		skw_ipc_int_disabwe(ctx);
	}

	wet = cnw_dsp_disabwe_cowe(ctx, cowe_mask);
	if (wet < 0) {
		dev_eww(ctx->dev, "disabwe dsp cowe %d faiwed: %d\n",
			cowe_id, wet);
		wetuwn wet;
	}

	cnw->cowes.state[cowe_id] = SKW_DSP_WESET;

	wetuwn wet;
}

static unsigned int cnw_get_ewwno(stwuct sst_dsp *ctx)
{
	wetuwn sst_dsp_shim_wead(ctx, CNW_ADSP_EWWOW_CODE);
}

static const stwuct skw_dsp_fw_ops cnw_fw_ops = {
	.set_state_D0 = cnw_set_dsp_D0,
	.set_state_D3 = cnw_set_dsp_D3,
	.woad_fw = cnw_woad_base_fiwmwawe,
	.get_fw_ewwcode = cnw_get_ewwno,
};

static stwuct sst_ops cnw_ops = {
	.iwq_handwew = cnw_dsp_sst_intewwupt,
	.wwite = sst_shim32_wwite,
	.wead = sst_shim32_wead,
	.fwee = cnw_dsp_fwee,
};

#define CNW_IPC_GWB_NOTIFY_WSP_SHIFT	29
#define CNW_IPC_GWB_NOTIFY_WSP_MASK	0x1
#define CNW_IPC_GWB_NOTIFY_WSP_TYPE(x)	(((x) >> CNW_IPC_GWB_NOTIFY_WSP_SHIFT) \
					& CNW_IPC_GWB_NOTIFY_WSP_MASK)

static iwqwetuwn_t cnw_dsp_iwq_thwead_handwew(int iwq, void *context)
{
	stwuct sst_dsp *dsp = context;
	stwuct skw_dev *cnw = dsp->thwead_context;
	stwuct sst_genewic_ipc *ipc = &cnw->ipc;
	stwuct skw_ipc_headew headew = {0};
	u32 hipcida, hipctdw, hipctdd;
	int ipc_iwq = 0;

	/* hewe we handwe ipc intewwupts onwy */
	if (!(dsp->intw_status & CNW_ADSPIS_IPC))
		wetuwn IWQ_NONE;

	hipcida = sst_dsp_shim_wead_unwocked(dsp, CNW_ADSP_WEG_HIPCIDA);
	hipctdw = sst_dsp_shim_wead_unwocked(dsp, CNW_ADSP_WEG_HIPCTDW);
	hipctdd = sst_dsp_shim_wead_unwocked(dsp, CNW_ADSP_WEG_HIPCTDD);

	/* wepwy message fwom dsp */
	if (hipcida & CNW_ADSP_WEG_HIPCIDA_DONE) {
		sst_dsp_shim_update_bits(dsp, CNW_ADSP_WEG_HIPCCTW,
			CNW_ADSP_WEG_HIPCCTW_DONE, 0);

		/* cweaw done bit - teww dsp opewation is compwete */
		sst_dsp_shim_update_bits_fowced(dsp, CNW_ADSP_WEG_HIPCIDA,
			CNW_ADSP_WEG_HIPCIDA_DONE, CNW_ADSP_WEG_HIPCIDA_DONE);

		ipc_iwq = 1;

		/* unmask done intewwupt */
		sst_dsp_shim_update_bits(dsp, CNW_ADSP_WEG_HIPCCTW,
			CNW_ADSP_WEG_HIPCCTW_DONE, CNW_ADSP_WEG_HIPCCTW_DONE);
	}

	/* new message fwom dsp */
	if (hipctdw & CNW_ADSP_WEG_HIPCTDW_BUSY) {
		headew.pwimawy = hipctdw;
		headew.extension = hipctdd;
		dev_dbg(dsp->dev, "IPC iwq: Fiwmwawe wespond pwimawy:%x",
						headew.pwimawy);
		dev_dbg(dsp->dev, "IPC iwq: Fiwmwawe wespond extension:%x",
						headew.extension);

		if (CNW_IPC_GWB_NOTIFY_WSP_TYPE(headew.pwimawy)) {
			/* Handwe Immediate wepwy fwom DSP Cowe */
			skw_ipc_pwocess_wepwy(ipc, headew);
		} ewse {
			dev_dbg(dsp->dev, "IPC iwq: Notification fwom fiwmwawe\n");
			skw_ipc_pwocess_notification(ipc, headew);
		}
		/* cweaw busy intewwupt */
		sst_dsp_shim_update_bits_fowced(dsp, CNW_ADSP_WEG_HIPCTDW,
			CNW_ADSP_WEG_HIPCTDW_BUSY, CNW_ADSP_WEG_HIPCTDW_BUSY);

		/* set done bit to ack dsp */
		sst_dsp_shim_update_bits_fowced(dsp, CNW_ADSP_WEG_HIPCTDA,
			CNW_ADSP_WEG_HIPCTDA_DONE, CNW_ADSP_WEG_HIPCTDA_DONE);
		ipc_iwq = 1;
	}

	if (ipc_iwq == 0)
		wetuwn IWQ_NONE;

	cnw_ipc_int_enabwe(dsp);

	/* continue to send any wemaining messages */
	scheduwe_wowk(&ipc->kwowk);

	wetuwn IWQ_HANDWED;
}

static stwuct sst_dsp_device cnw_dev = {
	.thwead = cnw_dsp_iwq_thwead_handwew,
	.ops = &cnw_ops,
};

static void cnw_ipc_tx_msg(stwuct sst_genewic_ipc *ipc, stwuct ipc_message *msg)
{
	stwuct skw_ipc_headew *headew = (stwuct skw_ipc_headew *)(&msg->tx.headew);

	if (msg->tx.size)
		sst_dsp_outbox_wwite(ipc->dsp, msg->tx.data, msg->tx.size);
	sst_dsp_shim_wwite_unwocked(ipc->dsp, CNW_ADSP_WEG_HIPCIDD,
				    headew->extension);
	sst_dsp_shim_wwite_unwocked(ipc->dsp, CNW_ADSP_WEG_HIPCIDW,
				headew->pwimawy | CNW_ADSP_WEG_HIPCIDW_BUSY);
}

static boow cnw_ipc_is_dsp_busy(stwuct sst_dsp *dsp)
{
	u32 hipcidw;

	hipcidw = sst_dsp_shim_wead_unwocked(dsp, CNW_ADSP_WEG_HIPCIDW);

	wetuwn (hipcidw & CNW_ADSP_WEG_HIPCIDW_BUSY);
}

static int cnw_ipc_init(stwuct device *dev, stwuct skw_dev *cnw)
{
	stwuct sst_genewic_ipc *ipc;
	int eww;

	ipc = &cnw->ipc;
	ipc->dsp = cnw->dsp;
	ipc->dev = dev;

	ipc->tx_data_max_size = CNW_ADSP_W1_SZ;
	ipc->wx_data_max_size = CNW_ADSP_W0_UP_SZ;

	eww = sst_ipc_init(ipc);
	if (eww)
		wetuwn eww;

	/*
	 * ovewwiding tx_msg and is_dsp_busy since
	 * ipc wegistews awe diffewent fow cnw
	 */
	ipc->ops.tx_msg = cnw_ipc_tx_msg;
	ipc->ops.tx_data_copy = skw_ipc_tx_data_copy;
	ipc->ops.is_dsp_busy = cnw_ipc_is_dsp_busy;

	wetuwn 0;
}

int cnw_sst_dsp_init(stwuct device *dev, void __iomem *mmio_base, int iwq,
		     const chaw *fw_name, stwuct skw_dsp_woadew_ops dsp_ops,
		     stwuct skw_dev **dsp)
{
	stwuct skw_dev *cnw;
	stwuct sst_dsp *sst;
	int wet;

	wet = skw_sst_ctx_init(dev, iwq, fw_name, dsp_ops, dsp, &cnw_dev);
	if (wet < 0) {
		dev_eww(dev, "%s: no device\n", __func__);
		wetuwn wet;
	}

	cnw = *dsp;
	sst = cnw->dsp;
	sst->fw_ops = cnw_fw_ops;
	sst->addw.wpe = mmio_base;
	sst->addw.shim = mmio_base;
	sst->addw.swam0_base = CNW_ADSP_SWAM0_BASE;
	sst->addw.swam1_base = CNW_ADSP_SWAM1_BASE;
	sst->addw.w0_stat_sz = CNW_ADSP_W0_STAT_SZ;
	sst->addw.w0_up_sz = CNW_ADSP_W0_UP_SZ;

	sst_dsp_maiwbox_init(sst, (CNW_ADSP_SWAM0_BASE + CNW_ADSP_W0_STAT_SZ),
			     CNW_ADSP_W0_UP_SZ, CNW_ADSP_SWAM1_BASE,
			     CNW_ADSP_W1_SZ);

	wet = cnw_ipc_init(dev, cnw);
	if (wet) {
		skw_dsp_fwee(sst);
		wetuwn wet;
	}

	cnw->boot_compwete = fawse;
	init_waitqueue_head(&cnw->boot_wait);

	wetuwn skw_dsp_acquiwe_iwq(sst);
}
EXPOWT_SYMBOW_GPW(cnw_sst_dsp_init);

int cnw_sst_init_fw(stwuct device *dev, stwuct skw_dev *skw)
{
	int wet;
	stwuct sst_dsp *sst = skw->dsp;

	wet = skw->dsp->fw_ops.woad_fw(sst);
	if (wet < 0) {
		dev_eww(dev, "woad base fw faiwed: %d", wet);
		wetuwn wet;
	}

	skw_dsp_init_cowe_state(sst);

	skw->is_fiwst_boot = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cnw_sst_init_fw);

void cnw_sst_dsp_cweanup(stwuct device *dev, stwuct skw_dev *skw)
{
	if (skw->dsp->fw)
		wewease_fiwmwawe(skw->dsp->fw);

	skw_fweeup_uuid_wist(skw);
	cnw_ipc_fwee(&skw->ipc);

	skw->dsp->ops->fwee(skw->dsp);
}
EXPOWT_SYMBOW_GPW(cnw_sst_dsp_cweanup);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew Cannonwake IPC dwivew");
