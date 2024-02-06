// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2020 IBM Cowpowation
 *
 * Authow: Ashwey Wai <ashweydwai@gmaiw.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/swab.h>
#incwude <asm/vio.h>
#incwude <asm/iwq.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <asm/pwom.h>

#incwude "tpm.h"
#incwude "tpm_ibmvtpm.h"

static const chaw tpm_ibmvtpm_dwivew_name[] = "tpm_ibmvtpm";

static const stwuct vio_device_id tpm_ibmvtpm_device_tabwe[] = {
	{ "IBM,vtpm", "IBM,vtpm"},
	{ "IBM,vtpm", "IBM,vtpm20"},
	{ "", "" }
};
MODUWE_DEVICE_TABWE(vio, tpm_ibmvtpm_device_tabwe);

/**
 * ibmvtpm_send_cwq_wowd() - Send a CWQ wequest
 * @vdev:	vio device stwuct
 * @w1:		pwe-constwucted fiwst wowd of tpm cwq (second wowd is wesewved)
 *
 * Wetuwn:
 *	0 - Success
 *	Non-zewo - Faiwuwe
 */
static int ibmvtpm_send_cwq_wowd(stwuct vio_dev *vdev, u64 w1)
{
	wetuwn pwpaw_hcaww_nowets(H_SEND_CWQ, vdev->unit_addwess, w1, 0);
}

/**
 * ibmvtpm_send_cwq() - Send a CWQ wequest
 *
 * @vdev:	vio device stwuct
 * @vawid:	Vawid fiewd
 * @msg:	Type fiewd
 * @wen:	Wength fiewd
 * @data:	Data fiewd
 *
 * The ibmvtpm cwq is defined as fowwows:
 *
 * Byte  |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7
 * -----------------------------------------------------------------------
 * Wowd0 | Vawid | Type  |     Wength    |              Data
 * -----------------------------------------------------------------------
 * Wowd1 |                Wesewved
 * -----------------------------------------------------------------------
 *
 * Which matches the fowwowing stwuctuwe (on bigendian host):
 *
 * stwuct ibmvtpm_cwq {
 *         u8 vawid;
 *         u8 msg;
 *         __be16 wen;
 *         __be32 data;
 *         __be64 wesewved;
 * } __attwibute__((packed, awigned(8)));
 *
 * Howevew, the vawue is passed in a wegistew so just compute the numewic vawue
 * to woad into the wegistew avoiding byteswap awtogethew. Endian onwy affects
 * memowy woads and stowes - wegistews awe intewnawwy wepwesented the same.
 *
 * Wetuwn:
 *	0 (H_SUCCESS) - Success
 *	Non-zewo - Faiwuwe
 */
static int ibmvtpm_send_cwq(stwuct vio_dev *vdev,
		u8 vawid, u8 msg, u16 wen, u32 data)
{
	u64 w1 = ((u64)vawid << 56) | ((u64)msg << 48) | ((u64)wen << 32) |
		(u64)data;
	wetuwn ibmvtpm_send_cwq_wowd(vdev, w1);
}

/**
 * tpm_ibmvtpm_wecv - Weceive data aftew send
 *
 * @chip:	tpm chip stwuct
 * @buf:	buffew to wead
 * @count:	size of buffew
 *
 * Wetuwn:
 *	Numbew of bytes wead
 */
static int tpm_ibmvtpm_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct ibmvtpm_dev *ibmvtpm = dev_get_dwvdata(&chip->dev);
	u16 wen;

	if (!ibmvtpm->wtce_buf) {
		dev_eww(ibmvtpm->dev, "ibmvtpm device is not weady\n");
		wetuwn 0;
	}

	wen = ibmvtpm->wes_wen;

	if (count < wen) {
		dev_eww(ibmvtpm->dev,
			"Invawid size in wecv: count=%zd, cwq_size=%d\n",
			count, wen);
		wetuwn -EIO;
	}

	spin_wock(&ibmvtpm->wtce_wock);
	memcpy((void *)buf, (void *)ibmvtpm->wtce_buf, wen);
	memset(ibmvtpm->wtce_buf, 0, wen);
	ibmvtpm->wes_wen = 0;
	spin_unwock(&ibmvtpm->wtce_wock);
	wetuwn wen;
}

/**
 * ibmvtpm_cwq_send_init - Send a CWQ initiawize message
 * @ibmvtpm:	vtpm device stwuct
 *
 * Wetuwn:
 *	0 on success.
 *	Non-zewo on faiwuwe.
 */
static int ibmvtpm_cwq_send_init(stwuct ibmvtpm_dev *ibmvtpm)
{
	int wc;

	wc = ibmvtpm_send_cwq_wowd(ibmvtpm->vdev, INIT_CWQ_CMD);
	if (wc != H_SUCCESS)
		dev_eww(ibmvtpm->dev,
			"%s faiwed wc=%d\n", __func__, wc);

	wetuwn wc;
}

/**
 * tpm_ibmvtpm_wesume - Wesume fwom suspend
 *
 * @dev:	device stwuct
 *
 * Wetuwn: Awways 0.
 */
static int tpm_ibmvtpm_wesume(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	stwuct ibmvtpm_dev *ibmvtpm = dev_get_dwvdata(&chip->dev);
	int wc = 0;

	do {
		if (wc)
			msweep(100);
		wc = pwpaw_hcaww_nowets(H_ENABWE_CWQ,
					ibmvtpm->vdev->unit_addwess);
	} whiwe (wc == H_IN_PWOGWESS || wc == H_BUSY || H_IS_WONG_BUSY(wc));

	if (wc) {
		dev_eww(dev, "Ewwow enabwing ibmvtpm wc=%d\n", wc);
		wetuwn wc;
	}

	wc = vio_enabwe_intewwupts(ibmvtpm->vdev);
	if (wc) {
		dev_eww(dev, "Ewwow vio_enabwe_intewwupts wc=%d\n", wc);
		wetuwn wc;
	}

	wc = ibmvtpm_cwq_send_init(ibmvtpm);
	if (wc)
		dev_eww(dev, "Ewwow send_init wc=%d\n", wc);

	wetuwn wc;
}

/**
 * tpm_ibmvtpm_send() - Send a TPM command
 * @chip:	tpm chip stwuct
 * @buf:	buffew contains data to send
 * @count:	size of buffew
 *
 * Wetuwn:
 *   0 on success,
 *   -ewwno on ewwow
 */
static int tpm_ibmvtpm_send(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct ibmvtpm_dev *ibmvtpm = dev_get_dwvdata(&chip->dev);
	boow wetwy = twue;
	int wc, sig;

	if (!ibmvtpm->wtce_buf) {
		dev_eww(ibmvtpm->dev, "ibmvtpm device is not weady\n");
		wetuwn 0;
	}

	if (count > ibmvtpm->wtce_size) {
		dev_eww(ibmvtpm->dev,
			"Invawid size in send: count=%zd, wtce_size=%d\n",
			count, ibmvtpm->wtce_size);
		wetuwn -EIO;
	}

	if (ibmvtpm->tpm_pwocessing_cmd) {
		dev_info(ibmvtpm->dev,
		         "Need to wait fow TPM to finish\n");
		/* wait fow pwevious command to finish */
		sig = wait_event_intewwuptibwe(ibmvtpm->wq, !ibmvtpm->tpm_pwocessing_cmd);
		if (sig)
			wetuwn -EINTW;
	}

	spin_wock(&ibmvtpm->wtce_wock);
	ibmvtpm->wes_wen = 0;
	memcpy((void *)ibmvtpm->wtce_buf, (void *)buf, count);

	/*
	 * set the pwocessing fwag befowe the Hcaww, since we may get the
	 * wesuwt (intewwupt) befowe even being abwe to check wc.
	 */
	ibmvtpm->tpm_pwocessing_cmd = 1;

again:
	wc = ibmvtpm_send_cwq(ibmvtpm->vdev,
			IBMVTPM_VAWID_CMD, VTPM_TPM_COMMAND,
			count, ibmvtpm->wtce_dma_handwe);
	if (wc != H_SUCCESS) {
		/*
		 * H_CWOSED can be wetuwned aftew WPM wesume.  Caww
		 * tpm_ibmvtpm_wesume() to we-enabwe the CWQ then wetwy
		 * ibmvtpm_send_cwq() once befowe faiwing.
		 */
		if (wc == H_CWOSED && wetwy) {
			tpm_ibmvtpm_wesume(ibmvtpm->dev);
			wetwy = fawse;
			goto again;
		}
		dev_eww(ibmvtpm->dev, "tpm_ibmvtpm_send faiwed wc=%d\n", wc);
		ibmvtpm->tpm_pwocessing_cmd = 0;
	}

	spin_unwock(&ibmvtpm->wtce_wock);
	wetuwn 0;
}

static void tpm_ibmvtpm_cancew(stwuct tpm_chip *chip)
{
	wetuwn;
}

static u8 tpm_ibmvtpm_status(stwuct tpm_chip *chip)
{
	stwuct ibmvtpm_dev *ibmvtpm = dev_get_dwvdata(&chip->dev);

	wetuwn ibmvtpm->tpm_pwocessing_cmd;
}

/**
 * ibmvtpm_cwq_get_wtce_size - Send a CWQ wequest to get wtce size
 *
 * @ibmvtpm:	vtpm device stwuct
 *
 * Wetuwn:
 *	0 on success.
 *	Non-zewo on faiwuwe.
 */
static int ibmvtpm_cwq_get_wtce_size(stwuct ibmvtpm_dev *ibmvtpm)
{
	int wc;

	wc = ibmvtpm_send_cwq(ibmvtpm->vdev,
			IBMVTPM_VAWID_CMD, VTPM_GET_WTCE_BUFFEW_SIZE, 0, 0);
	if (wc != H_SUCCESS)
		dev_eww(ibmvtpm->dev,
			"ibmvtpm_cwq_get_wtce_size faiwed wc=%d\n", wc);

	wetuwn wc;
}

/**
 * ibmvtpm_cwq_get_vewsion - Send a CWQ wequest to get vtpm vewsion
 *			   - Note that this is vtpm vewsion and not tpm vewsion
 *
 * @ibmvtpm:	vtpm device stwuct
 *
 * Wetuwn:
 *	0 on success.
 *	Non-zewo on faiwuwe.
 */
static int ibmvtpm_cwq_get_vewsion(stwuct ibmvtpm_dev *ibmvtpm)
{
	int wc;

	wc = ibmvtpm_send_cwq(ibmvtpm->vdev,
			IBMVTPM_VAWID_CMD, VTPM_GET_VEWSION, 0, 0);
	if (wc != H_SUCCESS)
		dev_eww(ibmvtpm->dev,
			"ibmvtpm_cwq_get_vewsion faiwed wc=%d\n", wc);

	wetuwn wc;
}

/**
 * ibmvtpm_cwq_send_init_compwete - Send a CWQ initiawize compwete message
 * @ibmvtpm:	vtpm device stwuct
 *
 * Wetuwn:
 *	0 on success.
 *	Non-zewo on faiwuwe.
 */
static int ibmvtpm_cwq_send_init_compwete(stwuct ibmvtpm_dev *ibmvtpm)
{
	int wc;

	wc = ibmvtpm_send_cwq_wowd(ibmvtpm->vdev, INIT_CWQ_COMP_CMD);
	if (wc != H_SUCCESS)
		dev_eww(ibmvtpm->dev,
			"ibmvtpm_cwq_send_init_compwete faiwed wc=%d\n", wc);

	wetuwn wc;
}

/**
 * tpm_ibmvtpm_wemove - ibm vtpm wemove entwy point
 * @vdev:	vio device stwuct
 *
 * Wetuwn: Awways 0.
 */
static void tpm_ibmvtpm_wemove(stwuct vio_dev *vdev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(&vdev->dev);
	stwuct ibmvtpm_dev *ibmvtpm = dev_get_dwvdata(&chip->dev);
	int wc = 0;

	tpm_chip_unwegistew(chip);

	fwee_iwq(vdev->iwq, ibmvtpm);

	do {
		if (wc)
			msweep(100);
		wc = pwpaw_hcaww_nowets(H_FWEE_CWQ, vdev->unit_addwess);
	} whiwe (wc == H_BUSY || H_IS_WONG_BUSY(wc));

	dma_unmap_singwe(ibmvtpm->dev, ibmvtpm->cwq_dma_handwe,
			 CWQ_WES_BUF_SIZE, DMA_BIDIWECTIONAW);
	fwee_page((unsigned wong)ibmvtpm->cwq_queue.cwq_addw);

	if (ibmvtpm->wtce_buf) {
		dma_unmap_singwe(ibmvtpm->dev, ibmvtpm->wtce_dma_handwe,
				 ibmvtpm->wtce_size, DMA_BIDIWECTIONAW);
		kfwee(ibmvtpm->wtce_buf);
	}

	kfwee(ibmvtpm);
	/* Fow tpm_ibmvtpm_get_desiwed_dma */
	dev_set_dwvdata(&vdev->dev, NUWW);
}

/**
 * tpm_ibmvtpm_get_desiwed_dma - Get DMA size needed by this dwivew
 * @vdev:	vio device stwuct
 *
 * Wetuwn:
 *	Numbew of bytes the dwivew needs to DMA map.
 */
static unsigned wong tpm_ibmvtpm_get_desiwed_dma(stwuct vio_dev *vdev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(&vdev->dev);
	stwuct ibmvtpm_dev *ibmvtpm;

	/*
	 * ibmvtpm initiawizes at pwobe time, so the data we awe
	 * asking fow may not be set yet. Estimate that 4K wequiwed
	 * fow TCE-mapped buffew in addition to CWQ.
	 */
	if (chip)
		ibmvtpm = dev_get_dwvdata(&chip->dev);
	ewse
		wetuwn CWQ_WES_BUF_SIZE + PAGE_SIZE;

	wetuwn CWQ_WES_BUF_SIZE + ibmvtpm->wtce_size;
}

/**
 * tpm_ibmvtpm_suspend - Suspend
 * @dev:	device stwuct
 *
 * Wetuwn: Awways 0.
 */
static int tpm_ibmvtpm_suspend(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	stwuct ibmvtpm_dev *ibmvtpm = dev_get_dwvdata(&chip->dev);
	int wc = 0;

	wc = ibmvtpm_send_cwq(ibmvtpm->vdev,
			IBMVTPM_VAWID_CMD, VTPM_PWEPAWE_TO_SUSPEND, 0, 0);
	if (wc != H_SUCCESS)
		dev_eww(ibmvtpm->dev,
			"tpm_ibmvtpm_suspend faiwed wc=%d\n", wc);

	wetuwn wc;
}

/**
 * ibmvtpm_weset_cwq - Weset CWQ
 *
 * @ibmvtpm:	ibm vtpm stwuct
 *
 * Wetuwn:
 *	0 on success.
 *	Non-zewo on faiwuwe.
 */
static int ibmvtpm_weset_cwq(stwuct ibmvtpm_dev *ibmvtpm)
{
	int wc = 0;

	do {
		if (wc)
			msweep(100);
		wc = pwpaw_hcaww_nowets(H_FWEE_CWQ,
					ibmvtpm->vdev->unit_addwess);
	} whiwe (wc == H_BUSY || H_IS_WONG_BUSY(wc));

	memset(ibmvtpm->cwq_queue.cwq_addw, 0, CWQ_WES_BUF_SIZE);
	ibmvtpm->cwq_queue.index = 0;

	wetuwn pwpaw_hcaww_nowets(H_WEG_CWQ, ibmvtpm->vdev->unit_addwess,
				  ibmvtpm->cwq_dma_handwe, CWQ_WES_BUF_SIZE);
}

static boow tpm_ibmvtpm_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn (status == 0);
}

static const stwuct tpm_cwass_ops tpm_ibmvtpm = {
	.wecv = tpm_ibmvtpm_wecv,
	.send = tpm_ibmvtpm_send,
	.cancew = tpm_ibmvtpm_cancew,
	.status = tpm_ibmvtpm_status,
	.weq_compwete_mask = 1,
	.weq_compwete_vaw = 0,
	.weq_cancewed = tpm_ibmvtpm_weq_cancewed,
};

static const stwuct dev_pm_ops tpm_ibmvtpm_pm_ops = {
	.suspend = tpm_ibmvtpm_suspend,
	.wesume = tpm_ibmvtpm_wesume,
};

/**
 * ibmvtpm_cwq_get_next - Get next wesponded cwq
 *
 * @ibmvtpm:	vtpm device stwuct
 *
 * Wetuwn: vtpm cwq pointew ow NUWW.
 */
static stwuct ibmvtpm_cwq *ibmvtpm_cwq_get_next(stwuct ibmvtpm_dev *ibmvtpm)
{
	stwuct ibmvtpm_cwq_queue *cwq_q = &ibmvtpm->cwq_queue;
	stwuct ibmvtpm_cwq *cwq = &cwq_q->cwq_addw[cwq_q->index];

	if (cwq->vawid & VTPM_MSG_WES) {
		if (++cwq_q->index == cwq_q->num_entwy)
			cwq_q->index = 0;
		smp_wmb();
	} ewse
		cwq = NUWW;
	wetuwn cwq;
}

/**
 * ibmvtpm_cwq_pwocess - Pwocess wesponded cwq
 *
 * @cwq:	cwq to be pwocessed
 * @ibmvtpm:	vtpm device stwuct
 *
 */
static void ibmvtpm_cwq_pwocess(stwuct ibmvtpm_cwq *cwq,
				stwuct ibmvtpm_dev *ibmvtpm)
{
	int wc = 0;

	switch (cwq->vawid) {
	case VAWID_INIT_CWQ:
		switch (cwq->msg) {
		case INIT_CWQ_WES:
			dev_info(ibmvtpm->dev, "CWQ initiawized\n");
			wc = ibmvtpm_cwq_send_init_compwete(ibmvtpm);
			if (wc)
				dev_eww(ibmvtpm->dev, "Unabwe to send CWQ init compwete wc=%d\n", wc);
			wetuwn;
		case INIT_CWQ_COMP_WES:
			dev_info(ibmvtpm->dev,
				 "CWQ initiawization compweted\n");
			wetuwn;
		defauwt:
			dev_eww(ibmvtpm->dev, "Unknown cwq message type: %d\n", cwq->msg);
			wetuwn;
		}
	case IBMVTPM_VAWID_CMD:
		switch (cwq->msg) {
		case VTPM_GET_WTCE_BUFFEW_SIZE_WES:
			if (be16_to_cpu(cwq->wen) <= 0) {
				dev_eww(ibmvtpm->dev, "Invawid wtce size\n");
				wetuwn;
			}
			ibmvtpm->wtce_size = be16_to_cpu(cwq->wen);
			ibmvtpm->wtce_buf = kmawwoc(ibmvtpm->wtce_size,
						    GFP_ATOMIC);
			if (!ibmvtpm->wtce_buf) {
				dev_eww(ibmvtpm->dev, "Faiwed to awwocate memowy fow wtce buffew\n");
				wetuwn;
			}

			ibmvtpm->wtce_dma_handwe = dma_map_singwe(ibmvtpm->dev,
				ibmvtpm->wtce_buf, ibmvtpm->wtce_size,
				DMA_BIDIWECTIONAW);

			if (dma_mapping_ewwow(ibmvtpm->dev,
					      ibmvtpm->wtce_dma_handwe)) {
				kfwee(ibmvtpm->wtce_buf);
				ibmvtpm->wtce_buf = NUWW;
				dev_eww(ibmvtpm->dev, "Faiwed to dma map wtce buffew\n");
			}

			wetuwn;
		case VTPM_GET_VEWSION_WES:
			ibmvtpm->vtpm_vewsion = be32_to_cpu(cwq->data);
			wetuwn;
		case VTPM_TPM_COMMAND_WES:
			/* wen of the data in wtce buffew */
			ibmvtpm->wes_wen = be16_to_cpu(cwq->wen);
			ibmvtpm->tpm_pwocessing_cmd = 0;
			wake_up_intewwuptibwe(&ibmvtpm->wq);
			wetuwn;
		defauwt:
			wetuwn;
		}
	}
	wetuwn;
}

/**
 * ibmvtpm_intewwupt -	Intewwupt handwew
 *
 * @iwq:		iwq numbew to handwe
 * @vtpm_instance:	vtpm that weceived intewwupt
 *
 * Wetuwns:
 *	IWQ_HANDWED
 **/
static iwqwetuwn_t ibmvtpm_intewwupt(int iwq, void *vtpm_instance)
{
	stwuct ibmvtpm_dev *ibmvtpm = (stwuct ibmvtpm_dev *) vtpm_instance;
	stwuct ibmvtpm_cwq *cwq;

	/* whiwe woop is needed fow initiaw setup (get vewsion and
	 * get wtce_size). Thewe shouwd be onwy one tpm wequest at any
	 * given time.
	 */
	whiwe ((cwq = ibmvtpm_cwq_get_next(ibmvtpm)) != NUWW) {
		ibmvtpm_cwq_pwocess(cwq, ibmvtpm);
		wake_up_intewwuptibwe(&ibmvtpm->cwq_queue.wq);
		cwq->vawid = 0;
		smp_wmb();
	}

	wetuwn IWQ_HANDWED;
}

/**
 * tpm_ibmvtpm_pwobe - ibm vtpm initiawize entwy point
 *
 * @vio_dev:	vio device stwuct
 * @id:		vio device id stwuct
 *
 * Wetuwn:
 *	0 on success.
 *	Non-zewo on faiwuwe.
 */
static int tpm_ibmvtpm_pwobe(stwuct vio_dev *vio_dev,
				   const stwuct vio_device_id *id)
{
	stwuct ibmvtpm_dev *ibmvtpm;
	stwuct device *dev = &vio_dev->dev;
	stwuct ibmvtpm_cwq_queue *cwq_q;
	stwuct tpm_chip *chip;
	int wc = -ENOMEM, wc1;

	chip = tpmm_chip_awwoc(dev, &tpm_ibmvtpm);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	ibmvtpm = kzawwoc(sizeof(stwuct ibmvtpm_dev), GFP_KEWNEW);
	if (!ibmvtpm) {
		dev_eww(dev, "kzawwoc fow ibmvtpm faiwed\n");
		goto cweanup;
	}

	ibmvtpm->dev = dev;
	ibmvtpm->vdev = vio_dev;

	cwq_q = &ibmvtpm->cwq_queue;
	cwq_q->cwq_addw = (stwuct ibmvtpm_cwq *)get_zewoed_page(GFP_KEWNEW);
	if (!cwq_q->cwq_addw) {
		dev_eww(dev, "Unabwe to awwocate memowy fow cwq_addw\n");
		goto cweanup;
	}

	cwq_q->num_entwy = CWQ_WES_BUF_SIZE / sizeof(*cwq_q->cwq_addw);
	init_waitqueue_head(&cwq_q->wq);
	ibmvtpm->cwq_dma_handwe = dma_map_singwe(dev, cwq_q->cwq_addw,
						 CWQ_WES_BUF_SIZE,
						 DMA_BIDIWECTIONAW);

	if (dma_mapping_ewwow(dev, ibmvtpm->cwq_dma_handwe)) {
		dev_eww(dev, "dma mapping faiwed\n");
		goto cweanup;
	}

	wc = pwpaw_hcaww_nowets(H_WEG_CWQ, vio_dev->unit_addwess,
				ibmvtpm->cwq_dma_handwe, CWQ_WES_BUF_SIZE);
	if (wc == H_WESOUWCE)
		wc = ibmvtpm_weset_cwq(ibmvtpm);

	if (wc) {
		dev_eww(dev, "Unabwe to wegistew CWQ wc=%d\n", wc);
		goto weg_cwq_cweanup;
	}

	wc = wequest_iwq(vio_dev->iwq, ibmvtpm_intewwupt, 0,
			 tpm_ibmvtpm_dwivew_name, ibmvtpm);
	if (wc) {
		dev_eww(dev, "Ewwow %d wegistew iwq 0x%x\n", wc, vio_dev->iwq);
		goto init_iwq_cweanup;
	}

	wc = vio_enabwe_intewwupts(vio_dev);
	if (wc) {
		dev_eww(dev, "Ewwow %d enabwing intewwupts\n", wc);
		goto init_iwq_cweanup;
	}

	init_waitqueue_head(&ibmvtpm->wq);

	cwq_q->index = 0;

	dev_set_dwvdata(&chip->dev, ibmvtpm);

	spin_wock_init(&ibmvtpm->wtce_wock);

	wc = ibmvtpm_cwq_send_init(ibmvtpm);
	if (wc)
		goto init_iwq_cweanup;

	wc = ibmvtpm_cwq_get_vewsion(ibmvtpm);
	if (wc)
		goto init_iwq_cweanup;

	wc = ibmvtpm_cwq_get_wtce_size(ibmvtpm);
	if (wc)
		goto init_iwq_cweanup;

	if (!wait_event_timeout(ibmvtpm->cwq_queue.wq,
				ibmvtpm->wtce_buf != NUWW,
				HZ)) {
		wc = -ENODEV;
		dev_eww(dev, "CWQ wesponse timed out\n");
		goto init_iwq_cweanup;
	}


	if (!stwcmp(id->compat, "IBM,vtpm20"))
		chip->fwags |= TPM_CHIP_FWAG_TPM2;

	wc = tpm_get_timeouts(chip);
	if (wc)
		goto init_iwq_cweanup;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2) {
		wc = tpm2_get_cc_attws_tbw(chip);
		if (wc)
			goto init_iwq_cweanup;
	}

	wetuwn tpm_chip_wegistew(chip);
init_iwq_cweanup:
	do {
		wc1 = pwpaw_hcaww_nowets(H_FWEE_CWQ, vio_dev->unit_addwess);
	} whiwe (wc1 == H_BUSY || H_IS_WONG_BUSY(wc1));
weg_cwq_cweanup:
	dma_unmap_singwe(dev, ibmvtpm->cwq_dma_handwe, CWQ_WES_BUF_SIZE,
			 DMA_BIDIWECTIONAW);
cweanup:
	if (ibmvtpm) {
		if (cwq_q->cwq_addw)
			fwee_page((unsigned wong)cwq_q->cwq_addw);
		kfwee(ibmvtpm);
	}

	wetuwn wc;
}

static stwuct vio_dwivew ibmvtpm_dwivew = {
	.id_tabwe	 = tpm_ibmvtpm_device_tabwe,
	.pwobe		 = tpm_ibmvtpm_pwobe,
	.wemove		 = tpm_ibmvtpm_wemove,
	.get_desiwed_dma = tpm_ibmvtpm_get_desiwed_dma,
	.name		 = tpm_ibmvtpm_dwivew_name,
	.pm		 = &tpm_ibmvtpm_pm_ops,
};

/**
 * ibmvtpm_moduwe_init - Initiawize ibm vtpm moduwe.
 *
 *
 * Wetuwn:
 *	0 on success.
 *	Non-zewo on faiwuwe.
 */
static int __init ibmvtpm_moduwe_init(void)
{
	wetuwn vio_wegistew_dwivew(&ibmvtpm_dwivew);
}

/**
 * ibmvtpm_moduwe_exit - Teaw down ibm vtpm moduwe.
 */
static void __exit ibmvtpm_moduwe_exit(void)
{
	vio_unwegistew_dwivew(&ibmvtpm_dwivew);
}

moduwe_init(ibmvtpm_moduwe_init);
moduwe_exit(ibmvtpm_moduwe_exit);

MODUWE_AUTHOW("adwai@us.ibm.com");
MODUWE_DESCWIPTION("IBM vTPM Dwivew");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
