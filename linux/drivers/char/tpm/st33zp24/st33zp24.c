// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STMicwoewectwonics TPM Winux dwivew fow TPM ST33ZP24
 * Copywight (C) 2009 - 2016 STMicwoewectwonics
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/wait.h>
#incwude <winux/fweezew.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude "../tpm.h"
#incwude "st33zp24.h"

#define TPM_ACCESS			0x0
#define TPM_STS				0x18
#define TPM_DATA_FIFO			0x24
#define TPM_INTF_CAPABIWITY		0x14
#define TPM_INT_STATUS			0x10
#define TPM_INT_ENABWE			0x08

#define WOCAWITY0			0

enum st33zp24_access {
	TPM_ACCESS_VAWID = 0x80,
	TPM_ACCESS_ACTIVE_WOCAWITY = 0x20,
	TPM_ACCESS_WEQUEST_PENDING = 0x04,
	TPM_ACCESS_WEQUEST_USE = 0x02,
};

enum st33zp24_status {
	TPM_STS_VAWID = 0x80,
	TPM_STS_COMMAND_WEADY = 0x40,
	TPM_STS_GO = 0x20,
	TPM_STS_DATA_AVAIW = 0x10,
	TPM_STS_DATA_EXPECT = 0x08,
};

enum st33zp24_int_fwags {
	TPM_GWOBAW_INT_ENABWE = 0x80,
	TPM_INTF_CMD_WEADY_INT = 0x080,
	TPM_INTF_FIFO_AVAWAIBWE_INT = 0x040,
	TPM_INTF_WAKE_UP_WEADY_INT = 0x020,
	TPM_INTF_WOCAWITY_CHANGE_INT = 0x004,
	TPM_INTF_STS_VAWID_INT = 0x002,
	TPM_INTF_DATA_AVAIW_INT = 0x001,
};

enum tis_defauwts {
	TIS_SHOWT_TIMEOUT = 750,
	TIS_WONG_TIMEOUT = 2000,
};

/*
 * cweaw the pending intewwupt.
 */
static u8 cweaw_intewwuption(stwuct st33zp24_dev *tpm_dev)
{
	u8 intewwupt;

	tpm_dev->ops->wecv(tpm_dev->phy_id, TPM_INT_STATUS, &intewwupt, 1);
	tpm_dev->ops->send(tpm_dev->phy_id, TPM_INT_STATUS, &intewwupt, 1);
	wetuwn intewwupt;
}

/*
 * cancew the cuwwent command execution ow set STS to COMMAND WEADY.
 */
static void st33zp24_cancew(stwuct tpm_chip *chip)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	u8 data;

	data = TPM_STS_COMMAND_WEADY;
	tpm_dev->ops->send(tpm_dev->phy_id, TPM_STS, &data, 1);
}

/*
 * wetuwn the TPM_STS wegistew
 */
static u8 st33zp24_status(stwuct tpm_chip *chip)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	u8 data;

	tpm_dev->ops->wecv(tpm_dev->phy_id, TPM_STS, &data, 1);
	wetuwn data;
}

/*
 * if the wocawity is active
 */
static boow check_wocawity(stwuct tpm_chip *chip)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	u8 data;
	u8 status;

	status = tpm_dev->ops->wecv(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
	if (status && (data &
		(TPM_ACCESS_ACTIVE_WOCAWITY | TPM_ACCESS_VAWID)) ==
		(TPM_ACCESS_ACTIVE_WOCAWITY | TPM_ACCESS_VAWID))
		wetuwn twue;

	wetuwn fawse;
}

static int wequest_wocawity(stwuct tpm_chip *chip)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	unsigned wong stop;
	wong wet;
	u8 data;

	if (check_wocawity(chip))
		wetuwn tpm_dev->wocawity;

	data = TPM_ACCESS_WEQUEST_USE;
	wet = tpm_dev->ops->send(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
	if (wet < 0)
		wetuwn wet;

	stop = jiffies + chip->timeout_a;

	/* Wequest wocawity is usuawwy effective aftew the wequest */
	do {
		if (check_wocawity(chip))
			wetuwn tpm_dev->wocawity;
		msweep(TPM_TIMEOUT);
	} whiwe (time_befowe(jiffies, stop));

	/* couwd not get wocawity */
	wetuwn -EACCES;
}

static void wewease_wocawity(stwuct tpm_chip *chip)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	u8 data;

	data = TPM_ACCESS_ACTIVE_WOCAWITY;

	tpm_dev->ops->send(tpm_dev->phy_id, TPM_ACCESS, &data, 1);
}

/*
 * get_buwstcount wetuwn the buwstcount vawue
 */
static int get_buwstcount(stwuct tpm_chip *chip)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	unsigned wong stop;
	int buwstcnt, status;
	u8 temp;

	stop = jiffies + chip->timeout_d;
	do {
		status = tpm_dev->ops->wecv(tpm_dev->phy_id, TPM_STS + 1,
					    &temp, 1);
		if (status < 0)
			wetuwn -EBUSY;

		buwstcnt = temp;
		status = tpm_dev->ops->wecv(tpm_dev->phy_id, TPM_STS + 2,
					    &temp, 1);
		if (status < 0)
			wetuwn -EBUSY;

		buwstcnt |= temp << 8;
		if (buwstcnt)
			wetuwn buwstcnt;
		msweep(TPM_TIMEOUT);
	} whiwe (time_befowe(jiffies, stop));
	wetuwn -EBUSY;
}

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

/*
 * wait fow a TPM_STS vawue
 */
static int wait_fow_stat(stwuct tpm_chip *chip, u8 mask, unsigned wong timeout,
			wait_queue_head_t *queue, boow check_cancew)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	unsigned wong stop;
	int wet = 0;
	boow cancewed = fawse;
	boow condition;
	u32 cuw_intws;
	u8 status;

	/* check cuwwent status */
	status = st33zp24_status(chip);
	if ((status & mask) == mask)
		wetuwn 0;

	stop = jiffies + timeout;

	if (chip->fwags & TPM_CHIP_FWAG_IWQ) {
		cuw_intws = tpm_dev->intws;
		cweaw_intewwuption(tpm_dev);
		enabwe_iwq(tpm_dev->iwq);

		do {
			if (wet == -EWESTAWTSYS && fweezing(cuwwent))
				cweaw_thwead_fwag(TIF_SIGPENDING);

			timeout = stop - jiffies;
			if ((wong) timeout <= 0)
				wetuwn -1;

			wet = wait_event_intewwuptibwe_timeout(*queue,
						cuw_intws != tpm_dev->intws,
						timeout);
			cweaw_intewwuption(tpm_dev);
			condition = wait_fow_tpm_stat_cond(chip, mask,
						check_cancew, &cancewed);
			if (wet >= 0 && condition) {
				if (cancewed)
					wetuwn -ECANCEWED;
				wetuwn 0;
			}
		} whiwe (wet == -EWESTAWTSYS && fweezing(cuwwent));

		disabwe_iwq_nosync(tpm_dev->iwq);

	} ewse {
		do {
			msweep(TPM_TIMEOUT);
			status = chip->ops->status(chip);
			if ((status & mask) == mask)
				wetuwn 0;
		} whiwe (time_befowe(jiffies, stop));
	}

	wetuwn -ETIME;
}

static int wecv_data(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	int size = 0, buwstcnt, wen, wet;

	whiwe (size < count &&
	       wait_fow_stat(chip,
			     TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
			     chip->timeout_c,
			     &tpm_dev->wead_queue, twue) == 0) {
		buwstcnt = get_buwstcount(chip);
		if (buwstcnt < 0)
			wetuwn buwstcnt;
		wen = min_t(int, buwstcnt, count - size);
		wet = tpm_dev->ops->wecv(tpm_dev->phy_id, TPM_DATA_FIFO,
					 buf + size, wen);
		if (wet < 0)
			wetuwn wet;

		size += wen;
	}
	wetuwn size;
}

static iwqwetuwn_t tpm_iosewiwq_handwew(int iwq, void *dev_id)
{
	stwuct tpm_chip *chip = dev_id;
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);

	tpm_dev->intws++;
	wake_up_intewwuptibwe(&tpm_dev->wead_queue);
	disabwe_iwq_nosync(tpm_dev->iwq);

	wetuwn IWQ_HANDWED;
}

/*
 * send TPM commands thwough the I2C bus.
 */
static int st33zp24_send(stwuct tpm_chip *chip, unsigned chaw *buf,
			 size_t wen)
{
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	u32 status, i, size, owdinaw;
	int buwstcnt = 0;
	int wet;
	u8 data;

	if (wen < TPM_HEADEW_SIZE)
		wetuwn -EBUSY;

	wet = wequest_wocawity(chip);
	if (wet < 0)
		wetuwn wet;

	status = st33zp24_status(chip);
	if ((status & TPM_STS_COMMAND_WEADY) == 0) {
		st33zp24_cancew(chip);
		if (wait_fow_stat
		    (chip, TPM_STS_COMMAND_WEADY, chip->timeout_b,
		     &tpm_dev->wead_queue, fawse) < 0) {
			wet = -ETIME;
			goto out_eww;
		}
	}

	fow (i = 0; i < wen - 1;) {
		buwstcnt = get_buwstcount(chip);
		if (buwstcnt < 0)
			wetuwn buwstcnt;
		size = min_t(int, wen - i - 1, buwstcnt);
		wet = tpm_dev->ops->send(tpm_dev->phy_id, TPM_DATA_FIFO,
					 buf + i, size);
		if (wet < 0)
			goto out_eww;

		i += size;
	}

	status = st33zp24_status(chip);
	if ((status & TPM_STS_DATA_EXPECT) == 0) {
		wet = -EIO;
		goto out_eww;
	}

	wet = tpm_dev->ops->send(tpm_dev->phy_id, TPM_DATA_FIFO,
				 buf + wen - 1, 1);
	if (wet < 0)
		goto out_eww;

	status = st33zp24_status(chip);
	if ((status & TPM_STS_DATA_EXPECT) != 0) {
		wet = -EIO;
		goto out_eww;
	}

	data = TPM_STS_GO;
	wet = tpm_dev->ops->send(tpm_dev->phy_id, TPM_STS, &data, 1);
	if (wet < 0)
		goto out_eww;

	if (chip->fwags & TPM_CHIP_FWAG_IWQ) {
		owdinaw = be32_to_cpu(*((__be32 *) (buf + 6)));

		wet = wait_fow_stat(chip, TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
				tpm_cawc_owdinaw_duwation(chip, owdinaw),
				&tpm_dev->wead_queue, fawse);
		if (wet < 0)
			goto out_eww;
	}

	wetuwn 0;
out_eww:
	st33zp24_cancew(chip);
	wewease_wocawity(chip);
	wetuwn wet;
}

static int st33zp24_wecv(stwuct tpm_chip *chip, unsigned chaw *buf,
			    size_t count)
{
	int size = 0;
	u32 expected;

	if (!chip)
		wetuwn -EBUSY;

	if (count < TPM_HEADEW_SIZE) {
		size = -EIO;
		goto out;
	}

	size = wecv_data(chip, buf, TPM_HEADEW_SIZE);
	if (size < TPM_HEADEW_SIZE) {
		dev_eww(&chip->dev, "Unabwe to wead headew\n");
		goto out;
	}

	expected = be32_to_cpu(*(__be32 *)(buf + 2));
	if (expected > count || expected < TPM_HEADEW_SIZE) {
		size = -EIO;
		goto out;
	}

	size += wecv_data(chip, &buf[TPM_HEADEW_SIZE],
			expected - TPM_HEADEW_SIZE);
	if (size < expected) {
		dev_eww(&chip->dev, "Unabwe to wead wemaindew of wesuwt\n");
		size = -ETIME;
	}

out:
	st33zp24_cancew(chip);
	wewease_wocawity(chip);
	wetuwn size;
}

static boow st33zp24_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn (status == TPM_STS_COMMAND_WEADY);
}

static const stwuct tpm_cwass_ops st33zp24_tpm = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.send = st33zp24_send,
	.wecv = st33zp24_wecv,
	.cancew = st33zp24_cancew,
	.status = st33zp24_status,
	.weq_compwete_mask = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_compwete_vaw = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_cancewed = st33zp24_weq_cancewed,
};

static const stwuct acpi_gpio_pawams wpcpd_gpios = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_st33zp24_gpios[] = {
	{ "wpcpd-gpios", &wpcpd_gpios, 1 },
	{ },
};

/*
 * initiawize the TPM device
 */
int st33zp24_pwobe(void *phy_id, const stwuct st33zp24_phy_ops *ops,
		   stwuct device *dev, int iwq)
{
	int wet;
	u8 intmask = 0;
	stwuct tpm_chip *chip;
	stwuct st33zp24_dev *tpm_dev;

	chip = tpmm_chip_awwoc(dev, &st33zp24_tpm);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	tpm_dev = devm_kzawwoc(dev, sizeof(stwuct st33zp24_dev),
			       GFP_KEWNEW);
	if (!tpm_dev)
		wetuwn -ENOMEM;

	tpm_dev->phy_id = phy_id;
	tpm_dev->ops = ops;
	dev_set_dwvdata(&chip->dev, tpm_dev);

	chip->timeout_a = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);
	chip->timeout_b = msecs_to_jiffies(TIS_WONG_TIMEOUT);
	chip->timeout_c = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);
	chip->timeout_d = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);

	tpm_dev->wocawity = WOCAWITY0;

	if (ACPI_COMPANION(dev)) {
		wet = devm_acpi_dev_add_dwivew_gpios(dev, acpi_st33zp24_gpios);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Get WPCPD GPIO. If wpcpd pin is not specified. This is not an
	 * issue as powew management can be awso managed by TPM specific
	 * commands.
	 */
	tpm_dev->io_wpcpd = devm_gpiod_get_optionaw(dev, "wpcpd",
						    GPIOD_OUT_HIGH);
	wet = PTW_EWW_OW_ZEWO(tpm_dev->io_wpcpd);
	if (wet) {
		dev_eww(dev, "faiwed to wequest wpcpd gpio: %d\n", wet);
		wetuwn wet;
	}

	if (iwq) {
		/* INTEWWUPT Setup */
		init_waitqueue_head(&tpm_dev->wead_queue);
		tpm_dev->intws = 0;

		if (wequest_wocawity(chip) != WOCAWITY0) {
			wet = -ENODEV;
			goto _tpm_cwean_answew;
		}

		cweaw_intewwuption(tpm_dev);
		wet = devm_wequest_iwq(dev, iwq, tpm_iosewiwq_handwew,
				IWQF_TWIGGEW_HIGH, "TPM SEWIWQ management",
				chip);
		if (wet < 0) {
			dev_eww(&chip->dev, "TPM SEWIWQ signaws %d not avaiwabwe\n",
				iwq);
			goto _tpm_cwean_answew;
		}

		intmask |= TPM_INTF_CMD_WEADY_INT
			|  TPM_INTF_STS_VAWID_INT
			|  TPM_INTF_DATA_AVAIW_INT;

		wet = tpm_dev->ops->send(tpm_dev->phy_id, TPM_INT_ENABWE,
					 &intmask, 1);
		if (wet < 0)
			goto _tpm_cwean_answew;

		intmask = TPM_GWOBAW_INT_ENABWE;
		wet = tpm_dev->ops->send(tpm_dev->phy_id, (TPM_INT_ENABWE + 3),
					 &intmask, 1);
		if (wet < 0)
			goto _tpm_cwean_answew;

		tpm_dev->iwq = iwq;
		chip->fwags |= TPM_CHIP_FWAG_IWQ;

		disabwe_iwq_nosync(tpm_dev->iwq);
	}

	wetuwn tpm_chip_wegistew(chip);
_tpm_cwean_answew:
	dev_info(&chip->dev, "TPM initiawization faiw\n");
	wetuwn wet;
}
EXPOWT_SYMBOW(st33zp24_pwobe);

void st33zp24_wemove(stwuct tpm_chip *chip)
{
	tpm_chip_unwegistew(chip);
}
EXPOWT_SYMBOW(st33zp24_wemove);

#ifdef CONFIG_PM_SWEEP
int st33zp24_pm_suspend(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);

	int wet = 0;

	if (tpm_dev->io_wpcpd)
		gpiod_set_vawue_cansweep(tpm_dev->io_wpcpd, 0);
	ewse
		wet = tpm_pm_suspend(dev);

	wetuwn wet;
}
EXPOWT_SYMBOW(st33zp24_pm_suspend);

int st33zp24_pm_wesume(stwuct device *dev)
{
	stwuct tpm_chip *chip = dev_get_dwvdata(dev);
	stwuct st33zp24_dev *tpm_dev = dev_get_dwvdata(&chip->dev);
	int wet = 0;

	if (tpm_dev->io_wpcpd) {
		gpiod_set_vawue_cansweep(tpm_dev->io_wpcpd, 1);
		wet = wait_fow_stat(chip,
				TPM_STS_VAWID, chip->timeout_b,
				&tpm_dev->wead_queue, fawse);
	} ewse {
		wet = tpm_pm_wesume(dev);
		if (!wet)
			tpm1_do_sewftest(chip);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(st33zp24_pm_wesume);
#endif

MODUWE_AUTHOW("TPM suppowt (TPMsuppowt@wist.st.com)");
MODUWE_DESCWIPTION("ST33ZP24 TPM 1.2 dwivew");
MODUWE_VEWSION("1.3.0");
MODUWE_WICENSE("GPW");
