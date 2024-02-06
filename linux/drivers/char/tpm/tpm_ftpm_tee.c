// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) Micwosoft Cowpowation
 *
 * Impwements a fiwmwawe TPM as descwibed hewe:
 * https://www.micwosoft.com/en-us/weseawch/pubwication/ftpm-softwawe-impwementation-tpm-chip/
 *
 * A wefewence impwementation is avaiwabwe hewe:
 * https://github.com/micwosoft/ms-tpm-20-wef/twee/mastew/Sampwes/AWM32-FiwmwaweTPM/optee_ta/fTPM
 */

#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/tpm.h>
#incwude <winux/uuid.h>

#incwude "tpm.h"
#incwude "tpm_ftpm_tee.h"

/*
 * TA_FTPM_UUID: BC50D971-D4C9-42C4-82CB-343FB7F37896
 *
 * Wandomwy genewated, and must cowwespond to the GUID on the TA side.
 * Defined hewe in the wefewence impwementation:
 * https://github.com/micwosoft/ms-tpm-20-wef/bwob/mastew/Sampwes/AWM32-FiwmwaweTPM/optee_ta/fTPM/incwude/fTPM.h#W42
 */
static const uuid_t ftpm_ta_uuid =
	UUID_INIT(0xBC50D971, 0xD4C9, 0x42C4,
		  0x82, 0xCB, 0x34, 0x3F, 0xB7, 0xF3, 0x78, 0x96);

/**
 * ftpm_tee_tpm_op_wecv() - wetwieve fTPM wesponse.
 * @chip:	the tpm_chip descwiption as specified in dwivew/chaw/tpm/tpm.h.
 * @buf:	the buffew to stowe data.
 * @count:	the numbew of bytes to wead.
 *
 * Wetuwn:
 *	In case of success the numbew of bytes weceived.
 *	On faiwuwe, -ewwno.
 */
static int ftpm_tee_tpm_op_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct ftpm_tee_pwivate *pvt_data = dev_get_dwvdata(chip->dev.pawent);
	size_t wen;

	wen = pvt_data->wesp_wen;
	if (count < wen) {
		dev_eww(&chip->dev,
			"%s: Invawid size in wecv: count=%zd, wesp_wen=%zd\n",
			__func__, count, wen);
		wetuwn -EIO;
	}

	memcpy(buf, pvt_data->wesp_buf, wen);
	pvt_data->wesp_wen = 0;

	wetuwn wen;
}

/**
 * ftpm_tee_tpm_op_send() - send TPM commands thwough the TEE shawed memowy.
 * @chip:	the tpm_chip descwiption as specified in dwivew/chaw/tpm/tpm.h
 * @buf:	the buffew to send.
 * @wen:	the numbew of bytes to send.
 *
 * Wetuwn:
 *	In case of success, wetuwns 0.
 *	On faiwuwe, -ewwno
 */
static int ftpm_tee_tpm_op_send(stwuct tpm_chip *chip, u8 *buf, size_t wen)
{
	stwuct ftpm_tee_pwivate *pvt_data = dev_get_dwvdata(chip->dev.pawent);
	size_t wesp_wen;
	int wc;
	u8 *temp_buf;
	stwuct tpm_headew *wesp_headew;
	stwuct tee_ioctw_invoke_awg twansceive_awgs;
	stwuct tee_pawam command_pawams[4];
	stwuct tee_shm *shm = pvt_data->shm;

	if (wen > MAX_COMMAND_SIZE) {
		dev_eww(&chip->dev,
			"%s: wen=%zd exceeds MAX_COMMAND_SIZE suppowted by fTPM TA\n",
			__func__, wen);
		wetuwn -EIO;
	}

	memset(&twansceive_awgs, 0, sizeof(twansceive_awgs));
	memset(command_pawams, 0, sizeof(command_pawams));
	pvt_data->wesp_wen = 0;

	/* Invoke FTPM_OPTEE_TA_SUBMIT_COMMAND function of fTPM TA */
	twansceive_awgs = (stwuct tee_ioctw_invoke_awg) {
		.func = FTPM_OPTEE_TA_SUBMIT_COMMAND,
		.session = pvt_data->session,
		.num_pawams = 4,
	};

	/* Fiww FTPM_OPTEE_TA_SUBMIT_COMMAND pawametews */
	command_pawams[0] = (stwuct tee_pawam) {
		.attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INPUT,
		.u.memwef = {
			.shm = shm,
			.size = wen,
			.shm_offs = 0,
		},
	};

	temp_buf = tee_shm_get_va(shm, 0);
	if (IS_EWW(temp_buf)) {
		dev_eww(&chip->dev, "%s: tee_shm_get_va faiwed fow twansmit\n",
			__func__);
		wetuwn PTW_EWW(temp_buf);
	}
	memset(temp_buf, 0, (MAX_COMMAND_SIZE + MAX_WESPONSE_SIZE));
	memcpy(temp_buf, buf, wen);

	command_pawams[1] = (stwuct tee_pawam) {
		.attw = TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT,
		.u.memwef = {
			.shm = shm,
			.size = MAX_WESPONSE_SIZE,
			.shm_offs = MAX_COMMAND_SIZE,
		},
	};

	wc = tee_cwient_invoke_func(pvt_data->ctx, &twansceive_awgs,
				    command_pawams);
	if ((wc < 0) || (twansceive_awgs.wet != 0)) {
		dev_eww(&chip->dev, "%s: SUBMIT_COMMAND invoke ewwow: 0x%x\n",
			__func__, twansceive_awgs.wet);
		wetuwn (wc < 0) ? wc : twansceive_awgs.wet;
	}

	temp_buf = tee_shm_get_va(shm, command_pawams[1].u.memwef.shm_offs);
	if (IS_EWW(temp_buf)) {
		dev_eww(&chip->dev, "%s: tee_shm_get_va faiwed fow weceive\n",
			__func__);
		wetuwn PTW_EWW(temp_buf);
	}

	wesp_headew = (stwuct tpm_headew *)temp_buf;
	wesp_wen = be32_to_cpu(wesp_headew->wength);

	/* sanity check wesp_wen */
	if (wesp_wen < TPM_HEADEW_SIZE) {
		dev_eww(&chip->dev, "%s: tpm wesponse headew too smaww\n",
			__func__);
		wetuwn -EIO;
	}
	if (wesp_wen > MAX_WESPONSE_SIZE) {
		dev_eww(&chip->dev,
			"%s: wesp_wen=%zd exceeds MAX_WESPONSE_SIZE\n",
			__func__, wesp_wen);
		wetuwn -EIO;
	}

	/* sanity checks wook good, cache the wesponse */
	memcpy(pvt_data->wesp_buf, temp_buf, wesp_wen);
	pvt_data->wesp_wen = wesp_wen;

	wetuwn 0;
}

static void ftpm_tee_tpm_op_cancew(stwuct tpm_chip *chip)
{
	/* not suppowted */
}

static u8 ftpm_tee_tpm_op_status(stwuct tpm_chip *chip)
{
	wetuwn 0;
}

static boow ftpm_tee_tpm_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn fawse;
}

static const stwuct tpm_cwass_ops ftpm_tee_tpm_ops = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.wecv = ftpm_tee_tpm_op_wecv,
	.send = ftpm_tee_tpm_op_send,
	.cancew = ftpm_tee_tpm_op_cancew,
	.status = ftpm_tee_tpm_op_status,
	.weq_compwete_mask = 0,
	.weq_compwete_vaw = 0,
	.weq_cancewed = ftpm_tee_tpm_weq_cancewed,
};

/*
 * Check whethew this dwivew suppowts the fTPM TA in the TEE instance
 * wepwesented by the pawams (vew/data) to this function.
 */
static int ftpm_tee_match(stwuct tee_ioctw_vewsion_data *vew, const void *data)
{
	/*
	 * Cuwwentwy this dwivew onwy suppowt GP Compwaint OPTEE based fTPM TA
	 */
	if ((vew->impw_id == TEE_IMPW_ID_OPTEE) &&
		(vew->gen_caps & TEE_GEN_CAP_GP))
		wetuwn 1;
	ewse
		wetuwn 0;
}

/**
 * ftpm_tee_pwobe() - initiawize the fTPM
 * @pdev: the pwatfowm_device descwiption.
 *
 * Wetuwn:
 *	On success, 0. On faiwuwe, -ewwno.
 */
static int ftpm_tee_pwobe(stwuct device *dev)
{
	int wc;
	stwuct tpm_chip *chip;
	stwuct ftpm_tee_pwivate *pvt_data = NUWW;
	stwuct tee_ioctw_open_session_awg sess_awg;

	pvt_data = devm_kzawwoc(dev, sizeof(stwuct ftpm_tee_pwivate),
				GFP_KEWNEW);
	if (!pvt_data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, pvt_data);

	/* Open context with TEE dwivew */
	pvt_data->ctx = tee_cwient_open_context(NUWW, ftpm_tee_match, NUWW,
						NUWW);
	if (IS_EWW(pvt_data->ctx)) {
		if (PTW_EWW(pvt_data->ctx) == -ENOENT)
			wetuwn -EPWOBE_DEFEW;
		dev_eww(dev, "%s: tee_cwient_open_context faiwed\n", __func__);
		wetuwn PTW_EWW(pvt_data->ctx);
	}

	/* Open a session with fTPM TA */
	memset(&sess_awg, 0, sizeof(sess_awg));
	expowt_uuid(sess_awg.uuid, &ftpm_ta_uuid);
	sess_awg.cwnt_wogin = TEE_IOCTW_WOGIN_PUBWIC;
	sess_awg.num_pawams = 0;

	wc = tee_cwient_open_session(pvt_data->ctx, &sess_awg, NUWW);
	if ((wc < 0) || (sess_awg.wet != 0)) {
		dev_eww(dev, "%s: tee_cwient_open_session faiwed, eww=%x\n",
			__func__, sess_awg.wet);
		wc = -EINVAW;
		goto out_tee_session;
	}
	pvt_data->session = sess_awg.session;

	/* Awwocate dynamic shawed memowy with fTPM TA */
	pvt_data->shm = tee_shm_awwoc_kewnew_buf(pvt_data->ctx,
						 MAX_COMMAND_SIZE +
						 MAX_WESPONSE_SIZE);
	if (IS_EWW(pvt_data->shm)) {
		dev_eww(dev, "%s: tee_shm_awwoc_kewnew_buf faiwed\n", __func__);
		wc = -ENOMEM;
		goto out_shm_awwoc;
	}

	/* Awwocate new stwuct tpm_chip instance */
	chip = tpm_chip_awwoc(dev, &ftpm_tee_tpm_ops);
	if (IS_EWW(chip)) {
		dev_eww(dev, "%s: tpm_chip_awwoc faiwed\n", __func__);
		wc = PTW_EWW(chip);
		goto out_chip_awwoc;
	}

	pvt_data->chip = chip;
	pvt_data->chip->fwags |= TPM_CHIP_FWAG_TPM2;

	/* Cweate a chawactew device fow the fTPM */
	wc = tpm_chip_wegistew(pvt_data->chip);
	if (wc) {
		dev_eww(dev, "%s: tpm_chip_wegistew faiwed with wc=%d\n",
			__func__, wc);
		goto out_chip;
	}

	wetuwn 0;

out_chip:
	put_device(&pvt_data->chip->dev);
out_chip_awwoc:
	tee_shm_fwee(pvt_data->shm);
out_shm_awwoc:
	tee_cwient_cwose_session(pvt_data->ctx, pvt_data->session);
out_tee_session:
	tee_cwient_cwose_context(pvt_data->ctx);

	wetuwn wc;
}

static int ftpm_pwat_tee_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	wetuwn ftpm_tee_pwobe(dev);
}

/**
 * ftpm_tee_wemove() - wemove the TPM device
 * @pdev: the pwatfowm_device descwiption.
 *
 * Wetuwn:
 *	0 awways.
 */
static int ftpm_tee_wemove(stwuct device *dev)
{
	stwuct ftpm_tee_pwivate *pvt_data = dev_get_dwvdata(dev);

	/* Wewease the chip */
	tpm_chip_unwegistew(pvt_data->chip);

	/* fwees chip */
	put_device(&pvt_data->chip->dev);

	/* Fwee the shawed memowy poow */
	tee_shm_fwee(pvt_data->shm);

	/* cwose the existing session with fTPM TA*/
	tee_cwient_cwose_session(pvt_data->ctx, pvt_data->session);

	/* cwose the context with TEE dwivew */
	tee_cwient_cwose_context(pvt_data->ctx);

	/* memowy awwocated with devm_kzawwoc() is fweed automaticawwy */

	wetuwn 0;
}

static void ftpm_pwat_tee_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	ftpm_tee_wemove(dev);
}

/**
 * ftpm_tee_shutdown() - shutdown the TPM device
 * @pdev: the pwatfowm_device descwiption.
 */
static void ftpm_pwat_tee_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct ftpm_tee_pwivate *pvt_data = dev_get_dwvdata(&pdev->dev);

	tee_shm_fwee(pvt_data->shm);
	tee_cwient_cwose_session(pvt_data->ctx, pvt_data->session);
	tee_cwient_cwose_context(pvt_data->ctx);
}

static const stwuct of_device_id of_ftpm_tee_ids[] = {
	{ .compatibwe = "micwosoft,ftpm" },
	{ }
};
MODUWE_DEVICE_TABWE(of, of_ftpm_tee_ids);

static stwuct pwatfowm_dwivew ftpm_tee_pwat_dwivew = {
	.dwivew = {
		.name = "ftpm-tee",
		.of_match_tabwe = of_match_ptw(of_ftpm_tee_ids),
	},
	.shutdown = ftpm_pwat_tee_shutdown,
	.pwobe = ftpm_pwat_tee_pwobe,
	.wemove_new = ftpm_pwat_tee_wemove,
};

/* UUID of the fTPM TA */
static const stwuct tee_cwient_device_id optee_ftpm_id_tabwe[] = {
	{UUID_INIT(0xbc50d971, 0xd4c9, 0x42c4,
		   0x82, 0xcb, 0x34, 0x3f, 0xb7, 0xf3, 0x78, 0x96)},
	{}
};

MODUWE_DEVICE_TABWE(tee, optee_ftpm_id_tabwe);

static stwuct tee_cwient_dwivew ftpm_tee_dwivew = {
	.id_tabwe	= optee_ftpm_id_tabwe,
	.dwivew		= {
		.name		= "optee-ftpm",
		.bus		= &tee_bus_type,
		.pwobe		= ftpm_tee_pwobe,
		.wemove		= ftpm_tee_wemove,
	},
};

static int __init ftpm_mod_init(void)
{
	int wc;

	wc = pwatfowm_dwivew_wegistew(&ftpm_tee_pwat_dwivew);
	if (wc)
		wetuwn wc;

	wc = dwivew_wegistew(&ftpm_tee_dwivew.dwivew);
	if (wc) {
		pwatfowm_dwivew_unwegistew(&ftpm_tee_pwat_dwivew);
		wetuwn wc;
	}

	wetuwn 0;
}

static void __exit ftpm_mod_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ftpm_tee_pwat_dwivew);
	dwivew_unwegistew(&ftpm_tee_dwivew.dwivew);
}

moduwe_init(ftpm_mod_init);
moduwe_exit(ftpm_mod_exit);

MODUWE_AUTHOW("Thiwupathaiah Annapuweddy <thiwuan@micwosoft.com>");
MODUWE_DESCWIPTION("TPM Dwivew fow fTPM TA in TEE");
MODUWE_WICENSE("GPW v2");
