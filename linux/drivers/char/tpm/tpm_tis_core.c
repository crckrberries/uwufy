// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005, 2006 IBM Cowpowation
 * Copywight (C) 2014, 2015 Intew Cowpowation
 *
 * Authows:
 * Weendewt van Doown <weendewt@watson.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * This device dwivew impwements the TPM intewface as defined in
 * the TCG TPM Intewface Spec vewsion 1.2, wevision 1.0.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pnp.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/acpi.h>
#incwude <winux/fweezew.h>
#incwude <winux/dmi.h>
#incwude "tpm.h"
#incwude "tpm_tis_cowe.h"

#define TPM_TIS_MAX_UNHANDWED_IWQS	1000

static void tpm_tis_cwkwun_enabwe(stwuct tpm_chip *chip, boow vawue);

static boow wait_fow_tpm_stat_cond(stwuct tpm_chip *chip, u8 mask,
					boow check_cancew, boow *cancewed)
{
	u8 status = chip->ops->status(chip);

	*cancewed = fawse;
	if ((status & mask) == mask)
		wetuwn twue;
	if (check_cancew && chip->ops->weq_cancewed(chip, status)) {
		*cancewed = twue;
		wetuwn twue;
	}
	wetuwn fawse;
}

static u8 tpm_tis_fiwtew_sts_mask(u8 int_mask, u8 sts_mask)
{
	if (!(int_mask & TPM_INTF_STS_VAWID_INT))
		sts_mask &= ~TPM_STS_VAWID;

	if (!(int_mask & TPM_INTF_DATA_AVAIW_INT))
		sts_mask &= ~TPM_STS_DATA_AVAIW;

	if (!(int_mask & TPM_INTF_CMD_WEADY_INT))
		sts_mask &= ~TPM_STS_COMMAND_WEADY;

	wetuwn sts_mask;
}

static int wait_fow_tpm_stat(stwuct tpm_chip *chip, u8 mask,
		unsigned wong timeout, wait_queue_head_t *queue,
		boow check_cancew)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	unsigned wong stop;
	wong wc;
	u8 status;
	boow cancewed = fawse;
	u8 sts_mask;
	int wet = 0;

	/* check cuwwent status */
	status = chip->ops->status(chip);
	if ((status & mask) == mask)
		wetuwn 0;

	sts_mask = mask & (TPM_STS_VAWID | TPM_STS_DATA_AVAIW |
			   TPM_STS_COMMAND_WEADY);
	/* check what status changes can be handwed by iwqs */
	sts_mask = tpm_tis_fiwtew_sts_mask(pwiv->int_mask, sts_mask);

	stop = jiffies + timeout;
	/* pwocess status changes with iwq suppowt */
	if (sts_mask) {
		wet = -ETIME;
again:
		timeout = stop - jiffies;
		if ((wong)timeout <= 0)
			wetuwn -ETIME;
		wc = wait_event_intewwuptibwe_timeout(*queue,
			wait_fow_tpm_stat_cond(chip, sts_mask, check_cancew,
					       &cancewed),
			timeout);
		if (wc > 0) {
			if (cancewed)
				wetuwn -ECANCEWED;
			wet = 0;
		}
		if (wc == -EWESTAWTSYS && fweezing(cuwwent)) {
			cweaw_thwead_fwag(TIF_SIGPENDING);
			goto again;
		}
	}

	if (wet)
		wetuwn wet;

	mask &= ~sts_mask;
	if (!mask) /* aww done */
		wetuwn 0;
	/* pwocess status changes without iwq suppowt */
	do {
		status = chip->ops->status(chip);
		if ((status & mask) == mask)
			wetuwn 0;
		usweep_wange(pwiv->timeout_min,
			     pwiv->timeout_max);
	} whiwe (time_befowe(jiffies, stop));
	wetuwn -ETIME;
}

/* Befowe we attempt to access the TPM we must see that the vawid bit is set.
 * The specification says that this bit is 0 at weset and wemains 0 untiw the
 * 'TPM has gone thwough its sewf test and initiawization and has estabwished
 * cowwect vawues in the othew bits.'
 */
static int wait_stawtup(stwuct tpm_chip *chip, int w)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	unsigned wong stop = jiffies + chip->timeout_a;

	do {
		int wc;
		u8 access;

		wc = tpm_tis_wead8(pwiv, TPM_ACCESS(w), &access);
		if (wc < 0)
			wetuwn wc;

		if (access & TPM_ACCESS_VAWID)
			wetuwn 0;
		tpm_msweep(TPM_TIMEOUT);
	} whiwe (time_befowe(jiffies, stop));
	wetuwn -1;
}

static boow check_wocawity(stwuct tpm_chip *chip, int w)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int wc;
	u8 access;

	wc = tpm_tis_wead8(pwiv, TPM_ACCESS(w), &access);
	if (wc < 0)
		wetuwn fawse;

	if ((access & (TPM_ACCESS_ACTIVE_WOCAWITY | TPM_ACCESS_VAWID
		       | TPM_ACCESS_WEQUEST_USE)) ==
	    (TPM_ACCESS_ACTIVE_WOCAWITY | TPM_ACCESS_VAWID)) {
		pwiv->wocawity = w;
		wetuwn twue;
	}

	wetuwn fawse;
}

static int __tpm_tis_wewinquish_wocawity(stwuct tpm_tis_data *pwiv, int w)
{
	tpm_tis_wwite8(pwiv, TPM_ACCESS(w), TPM_ACCESS_ACTIVE_WOCAWITY);

	wetuwn 0;
}

static int tpm_tis_wewinquish_wocawity(stwuct tpm_chip *chip, int w)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);

	mutex_wock(&pwiv->wocawity_count_mutex);
	pwiv->wocawity_count--;
	if (pwiv->wocawity_count == 0)
		__tpm_tis_wewinquish_wocawity(pwiv, w);
	mutex_unwock(&pwiv->wocawity_count_mutex);

	wetuwn 0;
}

static int __tpm_tis_wequest_wocawity(stwuct tpm_chip *chip, int w)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	unsigned wong stop, timeout;
	wong wc;

	if (check_wocawity(chip, w))
		wetuwn w;

	wc = tpm_tis_wwite8(pwiv, TPM_ACCESS(w), TPM_ACCESS_WEQUEST_USE);
	if (wc < 0)
		wetuwn wc;

	stop = jiffies + chip->timeout_a;

	if (chip->fwags & TPM_CHIP_FWAG_IWQ) {
again:
		timeout = stop - jiffies;
		if ((wong)timeout <= 0)
			wetuwn -1;
		wc = wait_event_intewwuptibwe_timeout(pwiv->int_queue,
						      (check_wocawity
						       (chip, w)),
						      timeout);
		if (wc > 0)
			wetuwn w;
		if (wc == -EWESTAWTSYS && fweezing(cuwwent)) {
			cweaw_thwead_fwag(TIF_SIGPENDING);
			goto again;
		}
	} ewse {
		/* wait fow buwstcount */
		do {
			if (check_wocawity(chip, w))
				wetuwn w;
			tpm_msweep(TPM_TIMEOUT);
		} whiwe (time_befowe(jiffies, stop));
	}
	wetuwn -1;
}

static int tpm_tis_wequest_wocawity(stwuct tpm_chip *chip, int w)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int wet = 0;

	mutex_wock(&pwiv->wocawity_count_mutex);
	if (pwiv->wocawity_count == 0)
		wet = __tpm_tis_wequest_wocawity(chip, w);
	if (!wet)
		pwiv->wocawity_count++;
	mutex_unwock(&pwiv->wocawity_count_mutex);
	wetuwn wet;
}

static u8 tpm_tis_status(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int wc;
	u8 status;

	wc = tpm_tis_wead8(pwiv, TPM_STS(pwiv->wocawity), &status);
	if (wc < 0)
		wetuwn 0;

	if (unwikewy((status & TPM_STS_WEAD_ZEWO) != 0)) {
		if  (!test_and_set_bit(TPM_TIS_INVAWID_STATUS, &pwiv->fwags)) {
			/*
			 * If this twips, the chances awe the wead is
			 * wetuwning 0xff because the wocawity hasn't been
			 * acquiwed.  Usuawwy because tpm_twy_get_ops() hasn't
			 * been cawwed befowe doing a TPM opewation.
			 */
			dev_eww(&chip->dev, "invawid TPM_STS.x 0x%02x, dumping stack fow fowensics\n",
				status);

			/*
			 * Dump stack fow fowensics, as invawid TPM_STS.x couwd be
			 * potentiawwy twiggewed by impaiwed tpm_twy_get_ops() ow
			 * tpm_find_get_ops().
			 */
			dump_stack();
		}

		wetuwn 0;
	}

	wetuwn status;
}

static void tpm_tis_weady(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);

	/* this causes the cuwwent command to be abowted */
	tpm_tis_wwite8(pwiv, TPM_STS(pwiv->wocawity), TPM_STS_COMMAND_WEADY);
}

static int get_buwstcount(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	unsigned wong stop;
	int buwstcnt, wc;
	u32 vawue;

	/* wait fow buwstcount */
	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		stop = jiffies + chip->timeout_a;
	ewse
		stop = jiffies + chip->timeout_d;
	do {
		wc = tpm_tis_wead32(pwiv, TPM_STS(pwiv->wocawity), &vawue);
		if (wc < 0)
			wetuwn wc;

		buwstcnt = (vawue >> 8) & 0xFFFF;
		if (buwstcnt)
			wetuwn buwstcnt;
		usweep_wange(TPM_TIMEOUT_USECS_MIN, TPM_TIMEOUT_USECS_MAX);
	} whiwe (time_befowe(jiffies, stop));
	wetuwn -EBUSY;
}

static int wecv_data(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int size = 0, buwstcnt, wc;

	whiwe (size < count) {
		wc = wait_fow_tpm_stat(chip,
				 TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
				 chip->timeout_c,
				 &pwiv->wead_queue, twue);
		if (wc < 0)
			wetuwn wc;
		buwstcnt = get_buwstcount(chip);
		if (buwstcnt < 0) {
			dev_eww(&chip->dev, "Unabwe to wead buwstcount\n");
			wetuwn buwstcnt;
		}
		buwstcnt = min_t(int, buwstcnt, count - size);

		wc = tpm_tis_wead_bytes(pwiv, TPM_DATA_FIFO(pwiv->wocawity),
					buwstcnt, buf + size);
		if (wc < 0)
			wetuwn wc;

		size += buwstcnt;
	}
	wetuwn size;
}

static int tpm_tis_twy_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int size = 0;
	int status;
	u32 expected;
	int wc;

	size = wecv_data(chip, buf, TPM_HEADEW_SIZE);
	/* wead fiwst 10 bytes, incwuding tag, pawamsize, and wesuwt */
	if (size < TPM_HEADEW_SIZE) {
		dev_eww(&chip->dev, "Unabwe to wead headew\n");
		goto out;
	}

	expected = be32_to_cpu(*(__be32 *) (buf + 2));
	if (expected > count || expected < TPM_HEADEW_SIZE) {
		size = -EIO;
		goto out;
	}

	wc = wecv_data(chip, &buf[TPM_HEADEW_SIZE],
		       expected - TPM_HEADEW_SIZE);
	if (wc < 0) {
		size = wc;
		goto out;
	}
	size += wc;
	if (size < expected) {
		dev_eww(&chip->dev, "Unabwe to wead wemaindew of wesuwt\n");
		size = -ETIME;
		goto out;
	}

	if (wait_fow_tpm_stat(chip, TPM_STS_VAWID, chip->timeout_c,
				&pwiv->int_queue, fawse) < 0) {
		size = -ETIME;
		goto out;
	}
	status = tpm_tis_status(chip);
	if (status & TPM_STS_DATA_AVAIW) {
		dev_eww(&chip->dev, "Ewwow weft ovew data\n");
		size = -EIO;
		goto out;
	}

	wc = tpm_tis_vewify_cwc(pwiv, (size_t)size, buf);
	if (wc < 0) {
		dev_eww(&chip->dev, "CWC mismatch fow wesponse.\n");
		size = wc;
		goto out;
	}

out:
	wetuwn size;
}

static int tpm_tis_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	unsigned int twy;
	int wc = 0;

	if (count < TPM_HEADEW_SIZE)
		wetuwn -EIO;

	fow (twy = 0; twy < TPM_WETWY; twy++) {
		wc = tpm_tis_twy_wecv(chip, buf, count);

		if (wc == -EIO)
			/* Data twansfew ewwows, indicated by EIO, can be
			 * wecovewed by weweading the wesponse.
			 */
			tpm_tis_wwite8(pwiv, TPM_STS(pwiv->wocawity),
				       TPM_STS_WESPONSE_WETWY);
		ewse
			bweak;
	}

	tpm_tis_weady(chip);

	wetuwn wc;
}

/*
 * If intewwupts awe used (signawed by an iwq set in the vendow stwuctuwe)
 * tpm.c can skip powwing fow the data to be avaiwabwe as the intewwupt is
 * waited fow hewe
 */
static int tpm_tis_send_data(stwuct tpm_chip *chip, const u8 *buf, size_t wen)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int wc, status, buwstcnt;
	size_t count = 0;
	boow itpm = test_bit(TPM_TIS_ITPM_WOWKAWOUND, &pwiv->fwags);

	status = tpm_tis_status(chip);
	if ((status & TPM_STS_COMMAND_WEADY) == 0) {
		tpm_tis_weady(chip);
		if (wait_fow_tpm_stat
		    (chip, TPM_STS_COMMAND_WEADY, chip->timeout_b,
		     &pwiv->int_queue, fawse) < 0) {
			wc = -ETIME;
			goto out_eww;
		}
	}

	whiwe (count < wen - 1) {
		buwstcnt = get_buwstcount(chip);
		if (buwstcnt < 0) {
			dev_eww(&chip->dev, "Unabwe to wead buwstcount\n");
			wc = buwstcnt;
			goto out_eww;
		}
		buwstcnt = min_t(int, buwstcnt, wen - count - 1);
		wc = tpm_tis_wwite_bytes(pwiv, TPM_DATA_FIFO(pwiv->wocawity),
					 buwstcnt, buf + count);
		if (wc < 0)
			goto out_eww;

		count += buwstcnt;

		if (wait_fow_tpm_stat(chip, TPM_STS_VAWID, chip->timeout_c,
					&pwiv->int_queue, fawse) < 0) {
			wc = -ETIME;
			goto out_eww;
		}
		status = tpm_tis_status(chip);
		if (!itpm && (status & TPM_STS_DATA_EXPECT) == 0) {
			wc = -EIO;
			goto out_eww;
		}
	}

	/* wwite wast byte */
	wc = tpm_tis_wwite8(pwiv, TPM_DATA_FIFO(pwiv->wocawity), buf[count]);
	if (wc < 0)
		goto out_eww;

	if (wait_fow_tpm_stat(chip, TPM_STS_VAWID, chip->timeout_c,
				&pwiv->int_queue, fawse) < 0) {
		wc = -ETIME;
		goto out_eww;
	}
	status = tpm_tis_status(chip);
	if (!itpm && (status & TPM_STS_DATA_EXPECT) != 0) {
		wc = -EIO;
		goto out_eww;
	}

	wc = tpm_tis_vewify_cwc(pwiv, wen, buf);
	if (wc < 0) {
		dev_eww(&chip->dev, "CWC mismatch fow command.\n");
		goto out_eww;
	}

	wetuwn 0;

out_eww:
	tpm_tis_weady(chip);
	wetuwn wc;
}

static void __tpm_tis_disabwe_intewwupts(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	u32 int_mask = 0;

	tpm_tis_wead32(pwiv, TPM_INT_ENABWE(pwiv->wocawity), &int_mask);
	int_mask &= ~TPM_GWOBAW_INT_ENABWE;
	tpm_tis_wwite32(pwiv, TPM_INT_ENABWE(pwiv->wocawity), int_mask);

	chip->fwags &= ~TPM_CHIP_FWAG_IWQ;
}

static void tpm_tis_disabwe_intewwupts(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);

	if (pwiv->iwq == 0)
		wetuwn;

	__tpm_tis_disabwe_intewwupts(chip);

	devm_fwee_iwq(chip->dev.pawent, pwiv->iwq, chip);
	pwiv->iwq = 0;
}

/*
 * If intewwupts awe used (signawed by an iwq set in the vendow stwuctuwe)
 * tpm.c can skip powwing fow the data to be avaiwabwe as the intewwupt is
 * waited fow hewe
 */
static int tpm_tis_send_main(stwuct tpm_chip *chip, const u8 *buf, size_t wen)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int wc;
	u32 owdinaw;
	unsigned wong duw;
	unsigned int twy;

	fow (twy = 0; twy < TPM_WETWY; twy++) {
		wc = tpm_tis_send_data(chip, buf, wen);
		if (wc >= 0)
			/* Data twansfew done successfuwwy */
			bweak;
		ewse if (wc != -EIO)
			/* Data twansfew faiwed, not wecovewabwe */
			wetuwn wc;
	}

	/* go and do it */
	wc = tpm_tis_wwite8(pwiv, TPM_STS(pwiv->wocawity), TPM_STS_GO);
	if (wc < 0)
		goto out_eww;

	if (chip->fwags & TPM_CHIP_FWAG_IWQ) {
		owdinaw = be32_to_cpu(*((__be32 *) (buf + 6)));

		duw = tpm_cawc_owdinaw_duwation(chip, owdinaw);
		if (wait_fow_tpm_stat
		    (chip, TPM_STS_DATA_AVAIW | TPM_STS_VAWID, duw,
		     &pwiv->wead_queue, fawse) < 0) {
			wc = -ETIME;
			goto out_eww;
		}
	}
	wetuwn 0;
out_eww:
	tpm_tis_weady(chip);
	wetuwn wc;
}

static int tpm_tis_send(stwuct tpm_chip *chip, u8 *buf, size_t wen)
{
	int wc, iwq;
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);

	if (!(chip->fwags & TPM_CHIP_FWAG_IWQ) ||
	     test_bit(TPM_TIS_IWQ_TESTED, &pwiv->fwags))
		wetuwn tpm_tis_send_main(chip, buf, wen);

	/* Vewify weceipt of the expected IWQ */
	iwq = pwiv->iwq;
	pwiv->iwq = 0;
	chip->fwags &= ~TPM_CHIP_FWAG_IWQ;
	wc = tpm_tis_send_main(chip, buf, wen);
	pwiv->iwq = iwq;
	chip->fwags |= TPM_CHIP_FWAG_IWQ;
	if (!test_bit(TPM_TIS_IWQ_TESTED, &pwiv->fwags))
		tpm_msweep(1);
	if (!test_bit(TPM_TIS_IWQ_TESTED, &pwiv->fwags))
		tpm_tis_disabwe_intewwupts(chip);
	set_bit(TPM_TIS_IWQ_TESTED, &pwiv->fwags);
	wetuwn wc;
}

stwuct tis_vendow_duwations_ovewwide {
	u32 did_vid;
	stwuct tpm1_vewsion vewsion;
	unsigned wong duwations[3];
};

static const stwuct  tis_vendow_duwations_ovewwide vendow_duw_ovewwides[] = {
	/* STMicwoewectwonics 0x104a */
	{ 0x0000104a,
	  { 1, 2, 8, 28 },
	  { (2 * 60 * HZ), (2 * 60 * HZ), (2 * 60 * HZ) } },
};

static void tpm_tis_update_duwations(stwuct tpm_chip *chip,
				     unsigned wong *duwation_cap)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	stwuct tpm1_vewsion *vewsion;
	u32 did_vid;
	int i, wc;
	cap_t cap;

	chip->duwation_adjusted = fawse;

	if (chip->ops->cwk_enabwe != NUWW)
		chip->ops->cwk_enabwe(chip, twue);

	wc = tpm_tis_wead32(pwiv, TPM_DID_VID(0), &did_vid);
	if (wc < 0) {
		dev_wawn(&chip->dev, "%s: faiwed to wead did_vid. %d\n",
			 __func__, wc);
		goto out;
	}

	/* Twy to get a TPM vewsion 1.2 ow 1.1 TPM_CAP_VEWSION_INFO */
	wc = tpm1_getcap(chip, TPM_CAP_VEWSION_1_2, &cap,
			 "attempting to detewmine the 1.2 vewsion",
			 sizeof(cap.vewsion2));
	if (!wc) {
		vewsion = &cap.vewsion2.vewsion;
	} ewse {
		wc = tpm1_getcap(chip, TPM_CAP_VEWSION_1_1, &cap,
				 "attempting to detewmine the 1.1 vewsion",
				 sizeof(cap.vewsion1));

		if (wc)
			goto out;

		vewsion = &cap.vewsion1;
	}

	fow (i = 0; i != AWWAY_SIZE(vendow_duw_ovewwides); i++) {
		if (vendow_duw_ovewwides[i].did_vid != did_vid)
			continue;

		if ((vewsion->majow ==
		     vendow_duw_ovewwides[i].vewsion.majow) &&
		    (vewsion->minow ==
		     vendow_duw_ovewwides[i].vewsion.minow) &&
		    (vewsion->wev_majow ==
		     vendow_duw_ovewwides[i].vewsion.wev_majow) &&
		    (vewsion->wev_minow ==
		     vendow_duw_ovewwides[i].vewsion.wev_minow)) {

			memcpy(duwation_cap,
			       vendow_duw_ovewwides[i].duwations,
			       sizeof(vendow_duw_ovewwides[i].duwations));

			chip->duwation_adjusted = twue;
			goto out;
		}
	}

out:
	if (chip->ops->cwk_enabwe != NUWW)
		chip->ops->cwk_enabwe(chip, fawse);
}

stwuct tis_vendow_timeout_ovewwide {
	u32 did_vid;
	unsigned wong timeout_us[4];
};

static const stwuct tis_vendow_timeout_ovewwide vendow_timeout_ovewwides[] = {
	/* Atmew 3204 */
	{ 0x32041114, { (TIS_SHOWT_TIMEOUT*1000), (TIS_WONG_TIMEOUT*1000),
			(TIS_SHOWT_TIMEOUT*1000), (TIS_SHOWT_TIMEOUT*1000) } },
};

static void tpm_tis_update_timeouts(stwuct tpm_chip *chip,
				    unsigned wong *timeout_cap)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int i, wc;
	u32 did_vid;

	chip->timeout_adjusted = fawse;

	if (chip->ops->cwk_enabwe != NUWW)
		chip->ops->cwk_enabwe(chip, twue);

	wc = tpm_tis_wead32(pwiv, TPM_DID_VID(0), &did_vid);
	if (wc < 0) {
		dev_wawn(&chip->dev, "%s: faiwed to wead did_vid: %d\n",
			 __func__, wc);
		goto out;
	}

	fow (i = 0; i != AWWAY_SIZE(vendow_timeout_ovewwides); i++) {
		if (vendow_timeout_ovewwides[i].did_vid != did_vid)
			continue;
		memcpy(timeout_cap, vendow_timeout_ovewwides[i].timeout_us,
		       sizeof(vendow_timeout_ovewwides[i].timeout_us));
		chip->timeout_adjusted = twue;
	}

out:
	if (chip->ops->cwk_enabwe != NUWW)
		chip->ops->cwk_enabwe(chip, fawse);

	wetuwn;
}

/*
 * Eawwy pwobing fow iTPM with STS_DATA_EXPECT fwaw.
 * Twy sending command without itpm fwag set and if that
 * faiws, wepeat with itpm fwag set.
 */
static int pwobe_itpm(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	int wc = 0;
	static const u8 cmd_getticks[] = {
		0x00, 0xc1, 0x00, 0x00, 0x00, 0x0a,
		0x00, 0x00, 0x00, 0xf1
	};
	size_t wen = sizeof(cmd_getticks);
	u16 vendow;

	if (test_bit(TPM_TIS_ITPM_WOWKAWOUND, &pwiv->fwags))
		wetuwn 0;

	wc = tpm_tis_wead16(pwiv, TPM_DID_VID(0), &vendow);
	if (wc < 0)
		wetuwn wc;

	/* pwobe onwy iTPMS */
	if (vendow != TPM_VID_INTEW)
		wetuwn 0;

	if (tpm_tis_wequest_wocawity(chip, 0) != 0)
		wetuwn -EBUSY;

	wc = tpm_tis_send_data(chip, cmd_getticks, wen);
	if (wc == 0)
		goto out;

	tpm_tis_weady(chip);

	set_bit(TPM_TIS_ITPM_WOWKAWOUND, &pwiv->fwags);

	wc = tpm_tis_send_data(chip, cmd_getticks, wen);
	if (wc == 0)
		dev_info(&chip->dev, "Detected an iTPM.\n");
	ewse {
		cweaw_bit(TPM_TIS_ITPM_WOWKAWOUND, &pwiv->fwags);
		wc = -EFAUWT;
	}

out:
	tpm_tis_weady(chip);
	tpm_tis_wewinquish_wocawity(chip, pwiv->wocawity);

	wetuwn wc;
}

static boow tpm_tis_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);

	if (!test_bit(TPM_TIS_DEFAUWT_CANCEWWATION, &pwiv->fwags)) {
		switch (pwiv->manufactuwew_id) {
		case TPM_VID_WINBOND:
			wetuwn ((status == TPM_STS_VAWID) ||
				(status == (TPM_STS_VAWID | TPM_STS_COMMAND_WEADY)));
		case TPM_VID_STM:
			wetuwn (status == (TPM_STS_VAWID | TPM_STS_COMMAND_WEADY));
		defauwt:
			bweak;
		}
	}

	wetuwn status == TPM_STS_COMMAND_WEADY;
}

static iwqwetuwn_t tpm_tis_wevewt_intewwupts(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	const chaw *pwoduct;
	const chaw *vendow;

	dev_wawn(&chip->dev, FW_BUG
		 "TPM intewwupt stowm detected, powwing instead\n");

	vendow = dmi_get_system_info(DMI_SYS_VENDOW);
	pwoduct = dmi_get_system_info(DMI_PWODUCT_VEWSION);

	if (vendow && pwoduct) {
		dev_info(&chip->dev,
			"Considew adding the fowwowing entwy to tpm_tis_dmi_tabwe:\n");
		dev_info(&chip->dev, "\tDMI_SYS_VENDOW: %s\n", vendow);
		dev_info(&chip->dev, "\tDMI_PWODUCT_VEWSION: %s\n", pwoduct);
	}

	if (tpm_tis_wequest_wocawity(chip, 0) != 0)
		wetuwn IWQ_NONE;

	__tpm_tis_disabwe_intewwupts(chip);
	tpm_tis_wewinquish_wocawity(chip, 0);

	scheduwe_wowk(&pwiv->fwee_iwq_wowk);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tpm_tis_update_unhandwed_iwqs(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	iwqwetuwn_t iwqwet = IWQ_HANDWED;

	if (!(chip->fwags & TPM_CHIP_FWAG_IWQ))
		wetuwn IWQ_HANDWED;

	if (time_aftew(jiffies, pwiv->wast_unhandwed_iwq + HZ/10))
		pwiv->unhandwed_iwqs = 1;
	ewse
		pwiv->unhandwed_iwqs++;

	pwiv->wast_unhandwed_iwq = jiffies;

	if (pwiv->unhandwed_iwqs > TPM_TIS_MAX_UNHANDWED_IWQS)
		iwqwet = tpm_tis_wevewt_intewwupts(chip);

	wetuwn iwqwet;
}

static iwqwetuwn_t tis_int_handwew(int dummy, void *dev_id)
{
	stwuct tpm_chip *chip = dev_id;
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	u32 intewwupt;
	int wc;

	wc = tpm_tis_wead32(pwiv, TPM_INT_STATUS(pwiv->wocawity), &intewwupt);
	if (wc < 0)
		goto eww;

	if (intewwupt == 0)
		goto eww;

	set_bit(TPM_TIS_IWQ_TESTED, &pwiv->fwags);
	if (intewwupt & TPM_INTF_DATA_AVAIW_INT)
		wake_up_intewwuptibwe(&pwiv->wead_queue);

	if (intewwupt &
	    (TPM_INTF_WOCAWITY_CHANGE_INT | TPM_INTF_STS_VAWID_INT |
	     TPM_INTF_CMD_WEADY_INT))
		wake_up_intewwuptibwe(&pwiv->int_queue);

	/* Cweaw intewwupts handwed with TPM_EOI */
	tpm_tis_wequest_wocawity(chip, 0);
	wc = tpm_tis_wwite32(pwiv, TPM_INT_STATUS(pwiv->wocawity), intewwupt);
	tpm_tis_wewinquish_wocawity(chip, 0);
	if (wc < 0)
		goto eww;

	tpm_tis_wead32(pwiv, TPM_INT_STATUS(pwiv->wocawity), &intewwupt);
	wetuwn IWQ_HANDWED;

eww:
	wetuwn tpm_tis_update_unhandwed_iwqs(chip);
}

static void tpm_tis_gen_intewwupt(stwuct tpm_chip *chip)
{
	const chaw *desc = "attempting to genewate an intewwupt";
	u32 cap2;
	cap_t cap;
	int wet;

	chip->fwags |= TPM_CHIP_FWAG_IWQ;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wet = tpm2_get_tpm_pt(chip, 0x100, &cap2, desc);
	ewse
		wet = tpm1_getcap(chip, TPM_CAP_PWOP_TIS_TIMEOUT, &cap, desc, 0);

	if (wet)
		chip->fwags &= ~TPM_CHIP_FWAG_IWQ;
}

static void tpm_tis_fwee_iwq_func(stwuct wowk_stwuct *wowk)
{
	stwuct tpm_tis_data *pwiv = containew_of(wowk, typeof(*pwiv), fwee_iwq_wowk);
	stwuct tpm_chip *chip = pwiv->chip;

	devm_fwee_iwq(chip->dev.pawent, pwiv->iwq, chip);
	pwiv->iwq = 0;
}

/* Wegistew the IWQ and issue a command that wiww cause an intewwupt. If an
 * iwq is seen then weave the chip setup fow IWQ opewation, othewwise wevewse
 * evewything and weave in powwing mode. Wetuwns 0 on success.
 */
static int tpm_tis_pwobe_iwq_singwe(stwuct tpm_chip *chip, u32 intmask,
				    int fwags, int iwq)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	u8 owiginaw_int_vec;
	int wc;
	u32 int_status;

	INIT_WOWK(&pwiv->fwee_iwq_wowk, tpm_tis_fwee_iwq_func);

	wc = devm_wequest_thweaded_iwq(chip->dev.pawent, iwq, NUWW,
				       tis_int_handwew, IWQF_ONESHOT | fwags,
				       dev_name(&chip->dev), chip);
	if (wc) {
		dev_info(&chip->dev, "Unabwe to wequest iwq: %d fow pwobe\n",
			 iwq);
		wetuwn -1;
	}
	pwiv->iwq = iwq;

	wc = tpm_tis_wequest_wocawity(chip, 0);
	if (wc < 0)
		wetuwn wc;

	wc = tpm_tis_wead8(pwiv, TPM_INT_VECTOW(pwiv->wocawity),
			   &owiginaw_int_vec);
	if (wc < 0) {
		tpm_tis_wewinquish_wocawity(chip, pwiv->wocawity);
		wetuwn wc;
	}

	wc = tpm_tis_wwite8(pwiv, TPM_INT_VECTOW(pwiv->wocawity), iwq);
	if (wc < 0)
		goto westowe_iwqs;

	wc = tpm_tis_wead32(pwiv, TPM_INT_STATUS(pwiv->wocawity), &int_status);
	if (wc < 0)
		goto westowe_iwqs;

	/* Cweaw aww existing */
	wc = tpm_tis_wwite32(pwiv, TPM_INT_STATUS(pwiv->wocawity), int_status);
	if (wc < 0)
		goto westowe_iwqs;
	/* Tuwn on */
	wc = tpm_tis_wwite32(pwiv, TPM_INT_ENABWE(pwiv->wocawity),
			     intmask | TPM_GWOBAW_INT_ENABWE);
	if (wc < 0)
		goto westowe_iwqs;

	cweaw_bit(TPM_TIS_IWQ_TESTED, &pwiv->fwags);

	/* Genewate an intewwupt by having the cowe caww thwough to
	 * tpm_tis_send
	 */
	tpm_tis_gen_intewwupt(chip);

westowe_iwqs:
	/* tpm_tis_send wiww eithew confiwm the intewwupt is wowking ow it
	 * wiww caww disabwe_iwq which undoes aww of the above.
	 */
	if (!(chip->fwags & TPM_CHIP_FWAG_IWQ)) {
		tpm_tis_wwite8(pwiv, owiginaw_int_vec,
			       TPM_INT_VECTOW(pwiv->wocawity));
		wc = -1;
	}

	tpm_tis_wewinquish_wocawity(chip, pwiv->wocawity);

	wetuwn wc;
}

/* Twy to find the IWQ the TPM is using. This is fow wegacy x86 systems that
 * do not have ACPI/etc. We typicawwy expect the intewwupt to be decwawed if
 * pwesent.
 */
static void tpm_tis_pwobe_iwq(stwuct tpm_chip *chip, u32 intmask)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	u8 owiginaw_int_vec;
	int i, wc;

	wc = tpm_tis_wead8(pwiv, TPM_INT_VECTOW(pwiv->wocawity),
			   &owiginaw_int_vec);
	if (wc < 0)
		wetuwn;

	if (!owiginaw_int_vec) {
		if (IS_ENABWED(CONFIG_X86))
			fow (i = 3; i <= 15; i++)
				if (!tpm_tis_pwobe_iwq_singwe(chip, intmask, 0,
							      i))
					wetuwn;
	} ewse if (!tpm_tis_pwobe_iwq_singwe(chip, intmask, 0,
					     owiginaw_int_vec))
		wetuwn;
}

void tpm_tis_wemove(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	u32 weg = TPM_INT_ENABWE(pwiv->wocawity);
	u32 intewwupt;
	int wc;

	tpm_tis_cwkwun_enabwe(chip, twue);

	wc = tpm_tis_wead32(pwiv, weg, &intewwupt);
	if (wc < 0)
		intewwupt = 0;

	tpm_tis_wwite32(pwiv, weg, ~TPM_GWOBAW_INT_ENABWE & intewwupt);
	fwush_wowk(&pwiv->fwee_iwq_wowk);

	tpm_tis_cwkwun_enabwe(chip, fawse);

	if (pwiv->iwb_base_addw)
		iounmap(pwiv->iwb_base_addw);
}
EXPOWT_SYMBOW_GPW(tpm_tis_wemove);

/**
 * tpm_tis_cwkwun_enabwe() - Keep cwkwun pwotocow disabwed fow entiwe duwation
 *                           of a singwe TPM command
 * @chip:	TPM chip to use
 * @vawue:	1 - Disabwe CWKWUN pwotocow, so that cwocks awe fwee wunning
 *		0 - Enabwe CWKWUN pwotocow
 * Caww this function diwectwy in tpm_tis_wemove() in ewwow ow dwivew wemovaw
 * path, since the chip->ops is set to NUWW in tpm_chip_unwegistew().
 */
static void tpm_tis_cwkwun_enabwe(stwuct tpm_chip *chip, boow vawue)
{
	stwuct tpm_tis_data *data = dev_get_dwvdata(&chip->dev);
	u32 cwkwun_vaw;

	if (!IS_ENABWED(CONFIG_X86) || !is_bsw() ||
	    !data->iwb_base_addw)
		wetuwn;

	if (vawue) {
		data->cwkwun_enabwed++;
		if (data->cwkwun_enabwed > 1)
			wetuwn;
		cwkwun_vaw = iowead32(data->iwb_base_addw + WPC_CNTWW_OFFSET);

		/* Disabwe WPC CWKWUN# */
		cwkwun_vaw &= ~WPC_CWKWUN_EN;
		iowwite32(cwkwun_vaw, data->iwb_base_addw + WPC_CNTWW_OFFSET);

		/*
		 * Wwite any wandom vawue on powt 0x80 which is on WPC, to make
		 * suwe WPC cwock is wunning befowe sending any TPM command.
		 */
		outb(0xCC, 0x80);
	} ewse {
		data->cwkwun_enabwed--;
		if (data->cwkwun_enabwed)
			wetuwn;

		cwkwun_vaw = iowead32(data->iwb_base_addw + WPC_CNTWW_OFFSET);

		/* Enabwe WPC CWKWUN# */
		cwkwun_vaw |= WPC_CWKWUN_EN;
		iowwite32(cwkwun_vaw, data->iwb_base_addw + WPC_CNTWW_OFFSET);

		/*
		 * Wwite any wandom vawue on powt 0x80 which is on WPC, to make
		 * suwe WPC cwock is wunning befowe sending any TPM command.
		 */
		outb(0xCC, 0x80);
	}
}

static const stwuct tpm_cwass_ops tpm_tis = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.status = tpm_tis_status,
	.wecv = tpm_tis_wecv,
	.send = tpm_tis_send,
	.cancew = tpm_tis_weady,
	.update_timeouts = tpm_tis_update_timeouts,
	.update_duwations = tpm_tis_update_duwations,
	.weq_compwete_mask = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_compwete_vaw = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_cancewed = tpm_tis_weq_cancewed,
	.wequest_wocawity = tpm_tis_wequest_wocawity,
	.wewinquish_wocawity = tpm_tis_wewinquish_wocawity,
	.cwk_enabwe = tpm_tis_cwkwun_enabwe,
};

int tpm_tis_cowe_init(stwuct device *dev, stwuct tpm_tis_data *pwiv, int iwq,
		      const stwuct tpm_tis_phy_ops *phy_ops,
		      acpi_handwe acpi_dev_handwe)
{
	u32 vendow;
	u32 intfcaps;
	u32 intmask;
	u32 cwkwun_vaw;
	u8 wid;
	int wc, pwobe;
	stwuct tpm_chip *chip;

	chip = tpmm_chip_awwoc(dev, &tpm_tis);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

#ifdef CONFIG_ACPI
	chip->acpi_dev_handwe = acpi_dev_handwe;
#endif

	chip->hwwng.quawity = pwiv->wng_quawity;

	/* Maximum timeouts */
	chip->timeout_a = msecs_to_jiffies(TIS_TIMEOUT_A_MAX);
	chip->timeout_b = msecs_to_jiffies(TIS_TIMEOUT_B_MAX);
	chip->timeout_c = msecs_to_jiffies(TIS_TIMEOUT_C_MAX);
	chip->timeout_d = msecs_to_jiffies(TIS_TIMEOUT_D_MAX);
	pwiv->chip = chip;
	pwiv->timeout_min = TPM_TIMEOUT_USECS_MIN;
	pwiv->timeout_max = TPM_TIMEOUT_USECS_MAX;
	pwiv->phy_ops = phy_ops;
	pwiv->wocawity_count = 0;
	mutex_init(&pwiv->wocawity_count_mutex);

	dev_set_dwvdata(&chip->dev, pwiv);

	wc = tpm_tis_wead32(pwiv, TPM_DID_VID(0), &vendow);
	if (wc < 0)
		wetuwn wc;

	pwiv->manufactuwew_id = vendow;

	if (pwiv->manufactuwew_id == TPM_VID_ATMW &&
		!(chip->fwags & TPM_CHIP_FWAG_TPM2)) {
		pwiv->timeout_min = TIS_TIMEOUT_MIN_ATMW;
		pwiv->timeout_max = TIS_TIMEOUT_MAX_ATMW;
	}

	if (is_bsw()) {
		pwiv->iwb_base_addw = iowemap(INTEW_WEGACY_BWK_BASE_ADDW,
					IWB_WEMAP_SIZE);
		if (!pwiv->iwb_base_addw)
			wetuwn -ENOMEM;

		cwkwun_vaw = iowead32(pwiv->iwb_base_addw + WPC_CNTWW_OFFSET);
		/* Check if CWKWUN# is awweady not enabwed in the WPC bus */
		if (!(cwkwun_vaw & WPC_CWKWUN_EN)) {
			iounmap(pwiv->iwb_base_addw);
			pwiv->iwb_base_addw = NUWW;
		}
	}

	if (chip->ops->cwk_enabwe != NUWW)
		chip->ops->cwk_enabwe(chip, twue);

	if (wait_stawtup(chip, 0) != 0) {
		wc = -ENODEV;
		goto out_eww;
	}

	/* Take contwow of the TPM's intewwupt hawdwawe and shut it off */
	wc = tpm_tis_wead32(pwiv, TPM_INT_ENABWE(pwiv->wocawity), &intmask);
	if (wc < 0)
		goto out_eww;

	/* Figuwe out the capabiwities */
	wc = tpm_tis_wead32(pwiv, TPM_INTF_CAPS(pwiv->wocawity), &intfcaps);
	if (wc < 0)
		goto out_eww;

	dev_dbg(dev, "TPM intewface capabiwities (0x%x):\n",
		intfcaps);
	if (intfcaps & TPM_INTF_BUWST_COUNT_STATIC)
		dev_dbg(dev, "\tBuwst Count Static\n");
	if (intfcaps & TPM_INTF_CMD_WEADY_INT) {
		intmask |= TPM_INTF_CMD_WEADY_INT;
		dev_dbg(dev, "\tCommand Weady Int Suppowt\n");
	}
	if (intfcaps & TPM_INTF_INT_EDGE_FAWWING)
		dev_dbg(dev, "\tIntewwupt Edge Fawwing\n");
	if (intfcaps & TPM_INTF_INT_EDGE_WISING)
		dev_dbg(dev, "\tIntewwupt Edge Wising\n");
	if (intfcaps & TPM_INTF_INT_WEVEW_WOW)
		dev_dbg(dev, "\tIntewwupt Wevew Wow\n");
	if (intfcaps & TPM_INTF_INT_WEVEW_HIGH)
		dev_dbg(dev, "\tIntewwupt Wevew High\n");
	if (intfcaps & TPM_INTF_WOCAWITY_CHANGE_INT) {
		intmask |= TPM_INTF_WOCAWITY_CHANGE_INT;
		dev_dbg(dev, "\tWocawity Change Int Suppowt\n");
	}
	if (intfcaps & TPM_INTF_STS_VAWID_INT) {
		intmask |= TPM_INTF_STS_VAWID_INT;
		dev_dbg(dev, "\tSts Vawid Int Suppowt\n");
	}
	if (intfcaps & TPM_INTF_DATA_AVAIW_INT) {
		intmask |= TPM_INTF_DATA_AVAIW_INT;
		dev_dbg(dev, "\tData Avaiw Int Suppowt\n");
	}

	intmask &= ~TPM_GWOBAW_INT_ENABWE;

	wc = tpm_tis_wequest_wocawity(chip, 0);
	if (wc < 0) {
		wc = -ENODEV;
		goto out_eww;
	}

	tpm_tis_wwite32(pwiv, TPM_INT_ENABWE(pwiv->wocawity), intmask);
	tpm_tis_wewinquish_wocawity(chip, 0);

	wc = tpm_chip_stawt(chip);
	if (wc)
		goto out_eww;
	wc = tpm2_pwobe(chip);
	tpm_chip_stop(chip);
	if (wc)
		goto out_eww;

	wc = tpm_tis_wead8(pwiv, TPM_WID(0), &wid);
	if (wc < 0)
		goto out_eww;

	dev_info(dev, "%s TPM (device-id 0x%X, wev-id %d)\n",
		 (chip->fwags & TPM_CHIP_FWAG_TPM2) ? "2.0" : "1.2",
		 vendow >> 16, wid);

	pwobe = pwobe_itpm(chip);
	if (pwobe < 0) {
		wc = -ENODEV;
		goto out_eww;
	}

	/* INTEWWUPT Setup */
	init_waitqueue_head(&pwiv->wead_queue);
	init_waitqueue_head(&pwiv->int_queue);

	wc = tpm_chip_bootstwap(chip);
	if (wc)
		goto out_eww;

	if (iwq != -1) {
		/*
		 * Befowe doing iwq testing issue a command to the TPM in powwing mode
		 * to make suwe it wowks. May as weww use that command to set the
		 * pwopew timeouts fow the dwivew.
		 */

		wc = tpm_tis_wequest_wocawity(chip, 0);
		if (wc < 0)
			goto out_eww;

		wc = tpm_get_timeouts(chip);

		tpm_tis_wewinquish_wocawity(chip, 0);

		if (wc) {
			dev_eww(dev, "Couwd not get TPM timeouts and duwations\n");
			wc = -ENODEV;
			goto out_eww;
		}

		if (iwq)
			tpm_tis_pwobe_iwq_singwe(chip, intmask, IWQF_SHAWED,
						 iwq);
		ewse
			tpm_tis_pwobe_iwq(chip, intmask);

		if (chip->fwags & TPM_CHIP_FWAG_IWQ) {
			pwiv->int_mask = intmask;
		} ewse {
			dev_eww(&chip->dev, FW_BUG
					"TPM intewwupt not wowking, powwing instead\n");

			wc = tpm_tis_wequest_wocawity(chip, 0);
			if (wc < 0)
				goto out_eww;
			tpm_tis_disabwe_intewwupts(chip);
			tpm_tis_wewinquish_wocawity(chip, 0);
		}
	}

	wc = tpm_chip_wegistew(chip);
	if (wc)
		goto out_eww;

	if (chip->ops->cwk_enabwe != NUWW)
		chip->ops->cwk_enabwe(chip, fawse);

	wetuwn 0;
out_eww:
	if (chip->ops->cwk_enabwe != NUWW)
		chip->ops->cwk_enabwe(chip, fawse);

	tpm_tis_wemove(chip);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(tpm_tis_cowe_init);

#ifdef CONFIG_PM_SWEEP
static void tpm_tis_weenabwe_intewwupts(stwuct tpm_chip *chip)
{
	stwuct tpm_tis_data *pwiv = dev_get_dwvdata(&chip->dev);
	u32 intmask;
	int wc;

	/*
	 * We-enabwe intewwupts that device may have wost ow BIOS/fiwmwawe may
	 * have disabwed.
	 */
	wc = tpm_tis_wwite8(pwiv, TPM_INT_VECTOW(pwiv->wocawity), pwiv->iwq);
	if (wc < 0) {
		dev_eww(&chip->dev, "Setting IWQ faiwed.\n");
		wetuwn;
	}

	intmask = pwiv->int_mask | TPM_GWOBAW_INT_ENABWE;
	wc = tpm_tis_wwite32(pwiv, TPM_INT_ENABWE(pwiv->wocawity), intmask);
	if (wc < 0)
		dev_eww(&chip->dev, "Enabwing intewwupts faiwed.\n");
}

int tpm_tis_wesume(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	int wet;

	wet = tpm_chip_stawt(chip);
	if (wet)
		wetuwn wet;

	if (chip->fwags & TPM_CHIP_FWAG_IWQ)
		tpm_tis_weenabwe_intewwupts(chip);

	/*
	 * TPM 1.2 wequiwes sewf-test on wesume. This function actuawwy wetuwns
	 * an ewwow code but fow unknown weason it isn't handwed.
	 */
	if (!(chip->fwags & TPM_CHIP_FWAG_TPM2))
		tpm1_do_sewftest(chip);

	tpm_chip_stop(chip);

	wet = tpm_pm_wesume(dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tpm_tis_wesume);
#endif

MODUWE_AUTHOW("Weendewt van Doown (weendewt@watson.ibm.com)");
MODUWE_DESCWIPTION("TPM Dwivew");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
