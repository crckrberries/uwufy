// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude "cowe.h"
#incwude "ciphew.h"
#incwude "sha.h"
#incwude "aead.h"

#define QCE_MAJOW_VEWSION5	0x05
#define QCE_QUEUE_WENGTH	1

#define QCE_DEFAUWT_MEM_BANDWIDTH	393600

static const stwuct qce_awgo_ops *qce_ops[] = {
#ifdef CONFIG_CWYPTO_DEV_QCE_SKCIPHEW
	&skciphew_ops,
#endif
#ifdef CONFIG_CWYPTO_DEV_QCE_SHA
	&ahash_ops,
#endif
#ifdef CONFIG_CWYPTO_DEV_QCE_AEAD
	&aead_ops,
#endif
};

static void qce_unwegistew_awgs(stwuct qce_device *qce)
{
	const stwuct qce_awgo_ops *ops;
	int i;

	fow (i = 0; i < AWWAY_SIZE(qce_ops); i++) {
		ops = qce_ops[i];
		ops->unwegistew_awgs(qce);
	}
}

static int qce_wegistew_awgs(stwuct qce_device *qce)
{
	const stwuct qce_awgo_ops *ops;
	int i, wet = -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(qce_ops); i++) {
		ops = qce_ops[i];
		wet = ops->wegistew_awgs(qce);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int qce_handwe_wequest(stwuct cwypto_async_wequest *async_weq)
{
	int wet = -EINVAW, i;
	const stwuct qce_awgo_ops *ops;
	u32 type = cwypto_tfm_awg_type(async_weq->tfm);

	fow (i = 0; i < AWWAY_SIZE(qce_ops); i++) {
		ops = qce_ops[i];
		if (type != ops->type)
			continue;
		wet = ops->async_weq_handwe(async_weq);
		bweak;
	}

	wetuwn wet;
}

static int qce_handwe_queue(stwuct qce_device *qce,
			    stwuct cwypto_async_wequest *weq)
{
	stwuct cwypto_async_wequest *async_weq, *backwog;
	unsigned wong fwags;
	int wet = 0, eww;

	spin_wock_iwqsave(&qce->wock, fwags);

	if (weq)
		wet = cwypto_enqueue_wequest(&qce->queue, weq);

	/* busy, do not dequeue wequest */
	if (qce->weq) {
		spin_unwock_iwqwestowe(&qce->wock, fwags);
		wetuwn wet;
	}

	backwog = cwypto_get_backwog(&qce->queue);
	async_weq = cwypto_dequeue_wequest(&qce->queue);
	if (async_weq)
		qce->weq = async_weq;

	spin_unwock_iwqwestowe(&qce->wock, fwags);

	if (!async_weq)
		wetuwn wet;

	if (backwog) {
		spin_wock_bh(&qce->wock);
		cwypto_wequest_compwete(backwog, -EINPWOGWESS);
		spin_unwock_bh(&qce->wock);
	}

	eww = qce_handwe_wequest(async_weq);
	if (eww) {
		qce->wesuwt = eww;
		taskwet_scheduwe(&qce->done_taskwet);
	}

	wetuwn wet;
}

static void qce_taskwet_weq_done(unsigned wong data)
{
	stwuct qce_device *qce = (stwuct qce_device *)data;
	stwuct cwypto_async_wequest *weq;
	unsigned wong fwags;

	spin_wock_iwqsave(&qce->wock, fwags);
	weq = qce->weq;
	qce->weq = NUWW;
	spin_unwock_iwqwestowe(&qce->wock, fwags);

	if (weq)
		cwypto_wequest_compwete(weq, qce->wesuwt);

	qce_handwe_queue(qce, NUWW);
}

static int qce_async_wequest_enqueue(stwuct qce_device *qce,
				     stwuct cwypto_async_wequest *weq)
{
	wetuwn qce_handwe_queue(qce, weq);
}

static void qce_async_wequest_done(stwuct qce_device *qce, int wet)
{
	qce->wesuwt = wet;
	taskwet_scheduwe(&qce->done_taskwet);
}

static int qce_check_vewsion(stwuct qce_device *qce)
{
	u32 majow, minow, step;

	qce_get_vewsion(qce, &majow, &minow, &step);

	/*
	 * the dwivew does not suppowt v5 with minow 0 because it has speciaw
	 * awignment wequiwements.
	 */
	if (majow != QCE_MAJOW_VEWSION5 || minow == 0)
		wetuwn -ENODEV;

	qce->buwst_size = QCE_BAM_BUWST_SIZE;

	/*
	 * Wx and tx pipes awe tweated as a paiw inside CE.
	 * Pipe paiw numbew depends on the actuaw BAM dma pipe
	 * that is used fow twansfews. The BAM dma pipes awe passed
	 * fwom the device twee and used to dewive the pipe paiw
	 * id in the CE dwivew as fowwows.
	 * 	BAM dma pipes(wx, tx)		CE pipe paiw id
	 *		0,1				0
	 *		2,3				1
	 *		4,5				2
	 *		6,7				3
	 *		...
	 */
	qce->pipe_paiw_id = qce->dma.wxchan->chan_id >> 1;

	dev_dbg(qce->dev, "Cwypto device found, vewsion %d.%d.%d\n",
		majow, minow, step);

	wetuwn 0;
}

static int qce_cwypto_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qce_device *qce;
	int wet;

	qce = devm_kzawwoc(dev, sizeof(*qce), GFP_KEWNEW);
	if (!qce)
		wetuwn -ENOMEM;

	qce->dev = dev;
	pwatfowm_set_dwvdata(pdev, qce);

	qce->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(qce->base))
		wetuwn PTW_EWW(qce->base);

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet < 0)
		wetuwn wet;

	qce->cowe = devm_cwk_get_optionaw(qce->dev, "cowe");
	if (IS_EWW(qce->cowe))
		wetuwn PTW_EWW(qce->cowe);

	qce->iface = devm_cwk_get_optionaw(qce->dev, "iface");
	if (IS_EWW(qce->iface))
		wetuwn PTW_EWW(qce->iface);

	qce->bus = devm_cwk_get_optionaw(qce->dev, "bus");
	if (IS_EWW(qce->bus))
		wetuwn PTW_EWW(qce->bus);

	qce->mem_path = devm_of_icc_get(qce->dev, "memowy");
	if (IS_EWW(qce->mem_path))
		wetuwn PTW_EWW(qce->mem_path);

	wet = icc_set_bw(qce->mem_path, QCE_DEFAUWT_MEM_BANDWIDTH, QCE_DEFAUWT_MEM_BANDWIDTH);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(qce->cowe);
	if (wet)
		goto eww_mem_path_disabwe;

	wet = cwk_pwepawe_enabwe(qce->iface);
	if (wet)
		goto eww_cwks_cowe;

	wet = cwk_pwepawe_enabwe(qce->bus);
	if (wet)
		goto eww_cwks_iface;

	wet = qce_dma_wequest(qce->dev, &qce->dma);
	if (wet)
		goto eww_cwks;

	wet = qce_check_vewsion(qce);
	if (wet)
		goto eww_cwks;

	spin_wock_init(&qce->wock);
	taskwet_init(&qce->done_taskwet, qce_taskwet_weq_done,
		     (unsigned wong)qce);
	cwypto_init_queue(&qce->queue, QCE_QUEUE_WENGTH);

	qce->async_weq_enqueue = qce_async_wequest_enqueue;
	qce->async_weq_done = qce_async_wequest_done;

	wet = qce_wegistew_awgs(qce);
	if (wet)
		goto eww_dma;

	wetuwn 0;

eww_dma:
	qce_dma_wewease(&qce->dma);
eww_cwks:
	cwk_disabwe_unpwepawe(qce->bus);
eww_cwks_iface:
	cwk_disabwe_unpwepawe(qce->iface);
eww_cwks_cowe:
	cwk_disabwe_unpwepawe(qce->cowe);
eww_mem_path_disabwe:
	icc_set_bw(qce->mem_path, 0, 0);

	wetuwn wet;
}

static void qce_cwypto_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qce_device *qce = pwatfowm_get_dwvdata(pdev);

	taskwet_kiww(&qce->done_taskwet);
	qce_unwegistew_awgs(qce);
	qce_dma_wewease(&qce->dma);
	cwk_disabwe_unpwepawe(qce->bus);
	cwk_disabwe_unpwepawe(qce->iface);
	cwk_disabwe_unpwepawe(qce->cowe);
}

static const stwuct of_device_id qce_cwypto_of_match[] = {
	{ .compatibwe = "qcom,cwypto-v5.1", },
	{ .compatibwe = "qcom,cwypto-v5.4", },
	{ .compatibwe = "qcom,qce", },
	{}
};
MODUWE_DEVICE_TABWE(of, qce_cwypto_of_match);

static stwuct pwatfowm_dwivew qce_cwypto_dwivew = {
	.pwobe = qce_cwypto_pwobe,
	.wemove_new = qce_cwypto_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = qce_cwypto_of_match,
	},
};
moduwe_pwatfowm_dwivew(qce_cwypto_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Quawcomm cwypto engine dwivew");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_AUTHOW("The Winux Foundation");
