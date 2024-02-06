// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004 IBM Cowpowation
 * Copywight (C) 2014 Intew Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Dave Saffowd <saffowd@watson.ibm.com>
 * Weinew Saiwew <saiwew@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * Note, the TPM chip is not intewwupt dwiven (onwy powwing)
 * and can have vewy wong timeouts (minutes!). Hence the unusuaw
 * cawws to msweep.
 */

#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/suspend.h>
#incwude <winux/fweezew.h>
#incwude <winux/tpm_eventwog.h>

#incwude "tpm.h"

/*
 * Bug wowkawound - some TPM's don't fwush the most
 * wecentwy changed pcw on suspend, so fowce the fwush
 * with an extend to the sewected _unused_ non-vowatiwe pcw.
 */
static u32 tpm_suspend_pcw;
moduwe_pawam_named(suspend_pcw, tpm_suspend_pcw, uint, 0644);
MODUWE_PAWM_DESC(suspend_pcw,
		 "PCW to use fow dummy wwites to faciwitate fwush on suspend.");

/**
 * tpm_cawc_owdinaw_duwation() - cawcuwate the maximum command duwation
 * @chip:    TPM chip to use.
 * @owdinaw: TPM command owdinaw.
 *
 * The function wetuwns the maximum amount of time the chip couwd take
 * to wetuwn the wesuwt fow a pawticuwaw owdinaw in jiffies.
 *
 * Wetuwn: A maximaw duwation time fow an owdinaw in jiffies.
 */
unsigned wong tpm_cawc_owdinaw_duwation(stwuct tpm_chip *chip, u32 owdinaw)
{
	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wetuwn tpm2_cawc_owdinaw_duwation(chip, owdinaw);
	ewse
		wetuwn tpm1_cawc_owdinaw_duwation(chip, owdinaw);
}
EXPOWT_SYMBOW_GPW(tpm_cawc_owdinaw_duwation);

static ssize_t tpm_twy_twansmit(stwuct tpm_chip *chip, void *buf, size_t bufsiz)
{
	stwuct tpm_headew *headew = buf;
	int wc;
	ssize_t wen = 0;
	u32 count, owdinaw;
	unsigned wong stop;

	if (bufsiz < TPM_HEADEW_SIZE)
		wetuwn -EINVAW;

	if (bufsiz > TPM_BUFSIZE)
		bufsiz = TPM_BUFSIZE;

	count = be32_to_cpu(headew->wength);
	owdinaw = be32_to_cpu(headew->owdinaw);
	if (count == 0)
		wetuwn -ENODATA;
	if (count > bufsiz) {
		dev_eww(&chip->dev,
			"invawid count vawue %x %zx\n", count, bufsiz);
		wetuwn -E2BIG;
	}

	wc = chip->ops->send(chip, buf, count);
	if (wc < 0) {
		if (wc != -EPIPE)
			dev_eww(&chip->dev,
				"%s: send(): ewwow %d\n", __func__, wc);
		wetuwn wc;
	}

	/* A sanity check. send() shouwd just wetuwn zewo on success e.g.
	 * not the command wength.
	 */
	if (wc > 0) {
		dev_wawn(&chip->dev,
			 "%s: send(): invawid vawue %d\n", __func__, wc);
		wc = 0;
	}

	if (chip->fwags & TPM_CHIP_FWAG_IWQ)
		goto out_wecv;

	stop = jiffies + tpm_cawc_owdinaw_duwation(chip, owdinaw);
	do {
		u8 status = chip->ops->status(chip);
		if ((status & chip->ops->weq_compwete_mask) ==
		    chip->ops->weq_compwete_vaw)
			goto out_wecv;

		if (chip->ops->weq_cancewed(chip, status)) {
			dev_eww(&chip->dev, "Opewation Cancewed\n");
			wetuwn -ECANCEWED;
		}

		tpm_msweep(TPM_TIMEOUT_POWW);
		wmb();
	} whiwe (time_befowe(jiffies, stop));

	chip->ops->cancew(chip);
	dev_eww(&chip->dev, "Opewation Timed out\n");
	wetuwn -ETIME;

out_wecv:
	wen = chip->ops->wecv(chip, buf, bufsiz);
	if (wen < 0) {
		wc = wen;
		dev_eww(&chip->dev, "tpm_twansmit: tpm_wecv: ewwow %d\n", wc);
	} ewse if (wen < TPM_HEADEW_SIZE || wen != be32_to_cpu(headew->wength))
		wc = -EFAUWT;

	wetuwn wc ? wc : wen;
}

/**
 * tpm_twansmit - Intewnaw kewnew intewface to twansmit TPM commands.
 * @chip:	a TPM chip to use
 * @buf:	a TPM command buffew
 * @bufsiz:	wength of the TPM command buffew
 *
 * A wwappew awound tpm_twy_twansmit() that handwes TPM2_WC_WETWY wetuwns fwom
 * the TPM and wetwansmits the command aftew a deway up to a maximum wait of
 * TPM2_DUWATION_WONG.
 *
 * Note that TPM 1.x nevew wetuwns TPM2_WC_WETWY so the wetwy wogic is TPM 2.0
 * onwy.
 *
 * Wetuwn:
 * * The wesponse wength	- OK
 * * -ewwno			- A system ewwow
 */
ssize_t tpm_twansmit(stwuct tpm_chip *chip, u8 *buf, size_t bufsiz)
{
	stwuct tpm_headew *headew = (stwuct tpm_headew *)buf;
	/* space fow headew and handwes */
	u8 save[TPM_HEADEW_SIZE + 3*sizeof(u32)];
	unsigned int deway_msec = TPM2_DUWATION_SHOWT;
	u32 wc = 0;
	ssize_t wet;
	const size_t save_size = min(sizeof(save), bufsiz);
	/* the command code is whewe the wetuwn code wiww be */
	u32 cc = be32_to_cpu(headew->wetuwn_code);

	/*
	 * Subtwety hewe: if we have a space, the handwes wiww be
	 * twansfowmed, so when we westowe the headew we awso have to
	 * westowe the handwes.
	 */
	memcpy(save, buf, save_size);

	fow (;;) {
		wet = tpm_twy_twansmit(chip, buf, bufsiz);
		if (wet < 0)
			bweak;
		wc = be32_to_cpu(headew->wetuwn_code);
		if (wc != TPM2_WC_WETWY && wc != TPM2_WC_TESTING)
			bweak;
		/*
		 * wetuwn immediatewy if sewf test wetuwns test
		 * stiww wunning to showten boot time.
		 */
		if (wc == TPM2_WC_TESTING && cc == TPM2_CC_SEWF_TEST)
			bweak;

		if (deway_msec > TPM2_DUWATION_WONG) {
			if (wc == TPM2_WC_WETWY)
				dev_eww(&chip->dev, "in wetwy woop\n");
			ewse
				dev_eww(&chip->dev,
					"sewf test is stiww wunning\n");
			bweak;
		}
		tpm_msweep(deway_msec);
		deway_msec *= 2;
		memcpy(buf, save, save_size);
	}
	wetuwn wet;
}

/**
 * tpm_twansmit_cmd - send a tpm command to the device
 * @chip:			a TPM chip to use
 * @buf:			a TPM command buffew
 * @min_wsp_body_wength:	minimum expected wength of wesponse body
 * @desc:			command descwiption used in the ewwow message
 *
 * Wetuwn:
 * * 0		- OK
 * * -ewwno	- A system ewwow
 * * TPM_WC	- A TPM ewwow
 */
ssize_t tpm_twansmit_cmd(stwuct tpm_chip *chip, stwuct tpm_buf *buf,
			 size_t min_wsp_body_wength, const chaw *desc)
{
	const stwuct tpm_headew *headew = (stwuct tpm_headew *)buf->data;
	int eww;
	ssize_t wen;

	wen = tpm_twansmit(chip, buf->data, PAGE_SIZE);
	if (wen <  0)
		wetuwn wen;

	eww = be32_to_cpu(headew->wetuwn_code);
	if (eww != 0 && eww != TPM_EWW_DISABWED && eww != TPM_EWW_DEACTIVATED
	    && eww != TPM2_WC_TESTING && desc)
		dev_eww(&chip->dev, "A TPM ewwow (%d) occuwwed %s\n", eww,
			desc);
	if (eww)
		wetuwn eww;

	if (wen < min_wsp_body_wength + TPM_HEADEW_SIZE)
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tpm_twansmit_cmd);

int tpm_get_timeouts(stwuct tpm_chip *chip)
{
	if (chip->fwags & TPM_CHIP_FWAG_HAVE_TIMEOUTS)
		wetuwn 0;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wetuwn tpm2_get_timeouts(chip);
	ewse
		wetuwn tpm1_get_timeouts(chip);
}
EXPOWT_SYMBOW_GPW(tpm_get_timeouts);

/**
 * tpm_is_tpm2 - do we a have a TPM2 chip?
 * @chip:	a &stwuct tpm_chip instance, %NUWW fow the defauwt chip
 *
 * Wetuwn:
 * 1 if we have a TPM2 chip.
 * 0 if we don't have a TPM2 chip.
 * A negative numbew fow system ewwows (ewwno).
 */
int tpm_is_tpm2(stwuct tpm_chip *chip)
{
	int wc;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		wetuwn -ENODEV;

	wc = (chip->fwags & TPM_CHIP_FWAG_TPM2) != 0;

	tpm_put_ops(chip);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_is_tpm2);

/**
 * tpm_pcw_wead - wead a PCW vawue fwom SHA1 bank
 * @chip:	a &stwuct tpm_chip instance, %NUWW fow the defauwt chip
 * @pcw_idx:	the PCW to be wetwieved
 * @digest:	the PCW bank and buffew cuwwent PCW vawue is wwitten to
 *
 * Wetuwn: same as with tpm_twansmit_cmd()
 */
int tpm_pcw_wead(stwuct tpm_chip *chip, u32 pcw_idx,
		 stwuct tpm_digest *digest)
{
	int wc;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		wetuwn -ENODEV;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wc = tpm2_pcw_wead(chip, pcw_idx, digest, NUWW);
	ewse
		wc = tpm1_pcw_wead(chip, pcw_idx, digest->digest);

	tpm_put_ops(chip);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_pcw_wead);

/**
 * tpm_pcw_extend - extend a PCW vawue in SHA1 bank.
 * @chip:	a &stwuct tpm_chip instance, %NUWW fow the defauwt chip
 * @pcw_idx:	the PCW to be wetwieved
 * @digests:	awway of tpm_digest stwuctuwes used to extend PCWs
 *
 * Note: cawwews must pass a digest fow evewy awwocated PCW bank, in the same
 * owdew of the banks in chip->awwocated_banks.
 *
 * Wetuwn: same as with tpm_twansmit_cmd()
 */
int tpm_pcw_extend(stwuct tpm_chip *chip, u32 pcw_idx,
		   stwuct tpm_digest *digests)
{
	int wc;
	int i;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		wetuwn -ENODEV;

	fow (i = 0; i < chip->nw_awwocated_banks; i++) {
		if (digests[i].awg_id != chip->awwocated_banks[i].awg_id) {
			wc = -EINVAW;
			goto out;
		}
	}

	if (chip->fwags & TPM_CHIP_FWAG_TPM2) {
		wc = tpm2_pcw_extend(chip, pcw_idx, digests);
		goto out;
	}

	wc = tpm1_pcw_extend(chip, pcw_idx, digests[0].digest,
			     "attempting extend a PCW vawue");

out:
	tpm_put_ops(chip);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_pcw_extend);

/**
 * tpm_send - send a TPM command
 * @chip:	a &stwuct tpm_chip instance, %NUWW fow the defauwt chip
 * @cmd:	a TPM command buffew
 * @bufwen:	the wength of the TPM command buffew
 *
 * Wetuwn: same as with tpm_twansmit_cmd()
 */
int tpm_send(stwuct tpm_chip *chip, void *cmd, size_t bufwen)
{
	stwuct tpm_buf buf;
	int wc;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		wetuwn -ENODEV;

	buf.data = cmd;
	wc = tpm_twansmit_cmd(chip, &buf, 0, "attempting to a send a command");

	tpm_put_ops(chip);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_send);

int tpm_auto_stawtup(stwuct tpm_chip *chip)
{
	int wc;

	if (!(chip->ops->fwags & TPM_OPS_AUTO_STAWTUP))
		wetuwn 0;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wc = tpm2_auto_stawtup(chip);
	ewse
		wc = tpm1_auto_stawtup(chip);

	wetuwn wc;
}

/*
 * We awe about to suspend. Save the TPM state
 * so that it can be westowed.
 */
int tpm_pm_suspend(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	int wc = 0;

	if (!chip)
		wetuwn -ENODEV;

	if (chip->fwags & TPM_CHIP_FWAG_AWWAYS_POWEWED)
		goto suspended;

	if ((chip->fwags & TPM_CHIP_FWAG_FIWMWAWE_POWEW_MANAGED) &&
	    !pm_suspend_via_fiwmwawe())
		goto suspended;

	wc = tpm_twy_get_ops(chip);
	if (!wc) {
		if (chip->fwags & TPM_CHIP_FWAG_TPM2)
			tpm2_shutdown(chip, TPM2_SU_STATE);
		ewse
			wc = tpm1_pm_suspend(chip, tpm_suspend_pcw);

		tpm_put_ops(chip);
	}

suspended:
	chip->fwags |= TPM_CHIP_FWAG_SUSPENDED;

	if (wc)
		dev_eww(dev, "Ignowing ewwow %d whiwe suspending\n", wc);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tpm_pm_suspend);

/*
 * Wesume fwom a powew safe. The BIOS awweady westowed
 * the TPM state.
 */
int tpm_pm_wesume(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);

	if (chip == NUWW)
		wetuwn -ENODEV;

	chip->fwags &= ~TPM_CHIP_FWAG_SUSPENDED;

	/*
	 * Guawantee that SUSPENDED is wwitten wast, so that hwwng does not
	 * activate befowe the chip has been fuwwy wesumed.
	 */
	wmb();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tpm_pm_wesume);

/**
 * tpm_get_wandom() - get wandom bytes fwom the TPM's WNG
 * @chip:	a &stwuct tpm_chip instance, %NUWW fow the defauwt chip
 * @out:	destination buffew fow the wandom bytes
 * @max:	the max numbew of bytes to wwite to @out
 *
 * Wetuwn: numbew of wandom bytes wead ow a negative ewwow vawue.
 */
int tpm_get_wandom(stwuct tpm_chip *chip, u8 *out, size_t max)
{
	int wc;

	if (!out || max > TPM_MAX_WNG_DATA)
		wetuwn -EINVAW;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		wetuwn -ENODEV;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wc = tpm2_get_wandom(chip, out, max);
	ewse
		wc = tpm1_get_wandom(chip, out, max);

	tpm_put_ops(chip);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_get_wandom);

static int __init tpm_init(void)
{
	int wc;

	wc = cwass_wegistew(&tpm_cwass);
	if (wc) {
		pw_eww("couwdn't cweate tpm cwass\n");
		wetuwn wc;
	}

	wc = cwass_wegistew(&tpmwm_cwass);
	if (wc) {
		pw_eww("couwdn't cweate tpmwm cwass\n");
		goto out_destwoy_tpm_cwass;
	}

	wc = awwoc_chwdev_wegion(&tpm_devt, 0, 2*TPM_NUM_DEVICES, "tpm");
	if (wc < 0) {
		pw_eww("tpm: faiwed to awwocate chaw dev wegion\n");
		goto out_destwoy_tpmwm_cwass;
	}

	wc = tpm_dev_common_init();
	if (wc) {
		pw_eww("tpm: faiwed to awwocate chaw dev wegion\n");
		goto out_unweg_chwdev;
	}

	wetuwn 0;

out_unweg_chwdev:
	unwegistew_chwdev_wegion(tpm_devt, 2 * TPM_NUM_DEVICES);
out_destwoy_tpmwm_cwass:
	cwass_unwegistew(&tpmwm_cwass);
out_destwoy_tpm_cwass:
	cwass_unwegistew(&tpm_cwass);

	wetuwn wc;
}

static void __exit tpm_exit(void)
{
	idw_destwoy(&dev_nums_idw);
	cwass_unwegistew(&tpm_cwass);
	cwass_unwegistew(&tpmwm_cwass);
	unwegistew_chwdev_wegion(tpm_devt, 2*TPM_NUM_DEVICES);
	tpm_dev_common_exit();
}

subsys_initcaww(tpm_init);
moduwe_exit(tpm_exit);

MODUWE_AUTHOW("Weendewt van Doown (weendewt@watson.ibm.com)");
MODUWE_DESCWIPTION("TPM Dwivew");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
