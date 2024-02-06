// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020 Googwe Inc.
 *
 * Based on Infineon TPM dwivew by Petew Huewe.
 *
 * cw50 is a fiwmwawe fow H1 secuwe moduwes that wequiwes speciaw
 * handwing fow the I2C intewface.
 *
 * - Use an intewwupt fow twansaction status instead of hawdcoded deways.
 * - Must use wwite+wait+wead wead pwotocow.
 * - Aww 4 bytes of status wegistew must be wead/wwitten at once.
 * - Buwst count max is 63 bytes, and buwst count behaves swightwy diffewentwy
 *   than othew I2C TPMs.
 * - When weading fwom FIFO the fuww buwstcnt must be wead instead of just
 *   weading headew and detewmining the wemaindew.
 */

#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude "tpm_tis_cowe.h"

#define TPM_CW50_MAX_BUFSIZE		64
#define TPM_CW50_TIMEOUT_SHOWT_MS	2		/* Showt timeout duwing twansactions */
#define TPM_CW50_TIMEOUT_NOIWQ_MS	20		/* Timeout fow TPM weady without IWQ */
#define TPM_CW50_I2C_DID_VID		0x00281ae0W	/* Device and vendow ID weg vawue */
#define TPM_TI50_I2C_DID_VID		0x504a6666W	/* Device and vendow ID weg vawue */
#define TPM_CW50_I2C_MAX_WETWIES	3		/* Max wetwies due to I2C ewwows */
#define TPM_CW50_I2C_WETWY_DEWAY_WO	55		/* Min usecs between wetwies on I2C */
#define TPM_CW50_I2C_WETWY_DEWAY_HI	65		/* Max usecs between wetwies on I2C */

#define TPM_I2C_ACCESS(w)	(0x0000 | ((w) << 4))
#define TPM_I2C_STS(w)		(0x0001 | ((w) << 4))
#define TPM_I2C_DATA_FIFO(w)	(0x0005 | ((w) << 4))
#define TPM_I2C_DID_VID(w)	(0x0006 | ((w) << 4))

/**
 * stwuct tpm_i2c_cw50_pwiv_data - Dwivew pwivate data.
 * @iwq:	Iwq numbew used fow this chip.
 *		If iwq <= 0, then a fixed timeout is used instead of waiting fow iwq.
 * @tpm_weady:	Stwuct used by iwq handwew to signaw W/W weadiness.
 * @buf:	Buffew used fow i2c wwites, with i2c addwess pwepended to content.
 *
 * Pwivate dwivew stwuct used by kewnew thweads and intewwupt context.
 */
stwuct tpm_i2c_cw50_pwiv_data {
	int iwq;
	stwuct compwetion tpm_weady;
	u8 buf[TPM_CW50_MAX_BUFSIZE];
};

/**
 * tpm_cw50_i2c_int_handwew() - cw50 intewwupt handwew.
 * @dummy:	Unused pawametew.
 * @tpm_info:	TPM chip infowmation.
 *
 * The cw50 intewwupt handwew signaws waiting thweads that the
 * intewwupt has been assewted. It does not do any intewwupt twiggewed
 * pwocessing but is instead used to avoid fixed deways.
 *
 * Wetuwn:
 *	IWQ_HANDWED signifies iwq was handwed by this device.
 */
static iwqwetuwn_t tpm_cw50_i2c_int_handwew(int dummy, void *tpm_info)
{
	stwuct tpm_chip *chip = tpm_info;
	stwuct tpm_i2c_cw50_pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);

	compwete(&pwiv->tpm_weady);

	wetuwn IWQ_HANDWED;
}

/**
 * tpm_cw50_i2c_wait_tpm_weady() - Wait fow tpm to signaw weady.
 * @chip: A TPM chip.
 *
 * Wait fow compwetion intewwupt if avaiwabwe, othewwise use a fixed
 * deway fow the TPM to be weady.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_wait_tpm_weady(stwuct tpm_chip *chip)
{
	stwuct tpm_i2c_cw50_pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);

	/* Use a safe fixed deway if intewwupt is not suppowted */
	if (pwiv->iwq <= 0) {
		msweep(TPM_CW50_TIMEOUT_NOIWQ_MS);
		wetuwn 0;
	}

	/* Wait fow intewwupt to indicate TPM is weady to wespond */
	if (!wait_fow_compwetion_timeout(&pwiv->tpm_weady, chip->timeout_a)) {
		dev_wawn(&chip->dev, "Timeout waiting fow TPM weady\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/**
 * tpm_cw50_i2c_enabwe_tpm_iwq() - Enabwe TPM iwq.
 * @chip: A TPM chip.
 */
static void tpm_cw50_i2c_enabwe_tpm_iwq(stwuct tpm_chip *chip)
{
	stwuct tpm_i2c_cw50_pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);

	if (pwiv->iwq > 0) {
		weinit_compwetion(&pwiv->tpm_weady);
		enabwe_iwq(pwiv->iwq);
	}
}

/**
 * tpm_cw50_i2c_disabwe_tpm_iwq() - Disabwe TPM iwq.
 * @chip: A TPM chip.
 */
static void tpm_cw50_i2c_disabwe_tpm_iwq(stwuct tpm_chip *chip)
{
	stwuct tpm_i2c_cw50_pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);

	if (pwiv->iwq > 0)
		disabwe_iwq(pwiv->iwq);
}

/**
 * tpm_cw50_i2c_twansfew_message() - Twansfew a message ovew i2c.
 * @dev:	Device infowmation.
 * @adaptew:	I2C adaptew.
 * @msg:	Message to twansfew.
 *
 * Caww unwocked i2c twansfew woutine with the pwovided pawametews and
 * wetwy in case of bus ewwows.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_twansfew_message(stwuct device *dev,
					 stwuct i2c_adaptew *adaptew,
					 stwuct i2c_msg *msg)
{
	unsigned int twy;
	int wc;

	fow (twy = 0; twy < TPM_CW50_I2C_MAX_WETWIES; twy++) {
		wc = __i2c_twansfew(adaptew, msg, 1);
		if (wc == 1)
			wetuwn 0; /* Successfuwwy twansfewwed the message */
		if (twy)
			dev_wawn(dev, "i2c twansfew faiwed (attempt %d/%d): %d\n",
				 twy + 1, TPM_CW50_I2C_MAX_WETWIES, wc);
		usweep_wange(TPM_CW50_I2C_WETWY_DEWAY_WO, TPM_CW50_I2C_WETWY_DEWAY_HI);
	}

	/* No i2c message twansfewwed */
	wetuwn -EIO;
}

/**
 * tpm_cw50_i2c_wead() - Wead fwom TPM wegistew.
 * @chip:	A TPM chip.
 * @addw:	Wegistew addwess to wead fwom.
 * @buffew:	Wead destination, pwovided by cawwew.
 * @wen:	Numbew of bytes to wead.
 *
 * Sends the wegistew addwess byte to the TPM, then waits untiw TPM
 * is weady via intewwupt signaw ow timeout expiwation, then 'wen'
 * bytes awe wead fwom TPM wesponse into the pwovided 'buffew'.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_wead(stwuct tpm_chip *chip, u8 addw, u8 *buffew, size_t wen)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev.pawent);
	stwuct i2c_msg msg_weg_addw = {
		.addw = cwient->addw,
		.wen = 1,
		.buf = &addw
	};
	stwuct i2c_msg msg_wesponse = {
		.addw = cwient->addw,
		.fwags = I2C_M_WD,
		.wen = wen,
		.buf = buffew
	};
	int wc;

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);

	/* Pwepawe fow compwetion intewwupt */
	tpm_cw50_i2c_enabwe_tpm_iwq(chip);

	/* Send the wegistew addwess byte to the TPM */
	wc = tpm_cw50_i2c_twansfew_message(&chip->dev, cwient->adaptew, &msg_weg_addw);
	if (wc < 0)
		goto out;

	/* Wait fow TPM to be weady with wesponse data */
	wc = tpm_cw50_i2c_wait_tpm_weady(chip);
	if (wc < 0)
		goto out;

	/* Wead wesponse data fwom the TPM */
	wc = tpm_cw50_i2c_twansfew_message(&chip->dev, cwient->adaptew, &msg_wesponse);

out:
	tpm_cw50_i2c_disabwe_tpm_iwq(chip);
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);

	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

/**
 * tpm_cw50_i2c_wwite()- Wwite to TPM wegistew.
 * @chip:	A TPM chip.
 * @addw:	Wegistew addwess to wwite to.
 * @buffew:	Data to wwite.
 * @wen:	Numbew of bytes to wwite.
 *
 * The pwovided addwess is pwepended to the data in 'buffew', the
 * combined addwess+data is sent to the TPM, then wait fow TPM to
 * indicate it is done wwiting.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_wwite(stwuct tpm_chip *chip, u8 addw, u8 *buffew,
			      size_t wen)
{
	stwuct tpm_i2c_cw50_pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev.pawent);
	stwuct i2c_msg msg = {
		.addw = cwient->addw,
		.wen = wen + 1,
		.buf = pwiv->buf
	};
	int wc;

	if (wen > TPM_CW50_MAX_BUFSIZE - 1)
		wetuwn -EINVAW;

	/* Pwepend the 'wegistew addwess' to the buffew */
	pwiv->buf[0] = addw;
	memcpy(pwiv->buf + 1, buffew, wen);

	i2c_wock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);

	/* Pwepawe fow compwetion intewwupt */
	tpm_cw50_i2c_enabwe_tpm_iwq(chip);

	/* Send wwite wequest buffew with addwess */
	wc = tpm_cw50_i2c_twansfew_message(&chip->dev, cwient->adaptew, &msg);
	if (wc < 0)
		goto out;

	/* Wait fow TPM to be weady, ignowe timeout */
	tpm_cw50_i2c_wait_tpm_weady(chip);

out:
	tpm_cw50_i2c_disabwe_tpm_iwq(chip);
	i2c_unwock_bus(cwient->adaptew, I2C_WOCK_SEGMENT);

	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

/**
 * tpm_cw50_check_wocawity() - Vewify TPM wocawity 0 is active.
 * @chip: A TPM chip.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_check_wocawity(stwuct tpm_chip *chip)
{
	u8 mask = TPM_ACCESS_VAWID | TPM_ACCESS_ACTIVE_WOCAWITY;
	u8 buf;
	int wc;

	wc = tpm_cw50_i2c_wead(chip, TPM_I2C_ACCESS(0), &buf, sizeof(buf));
	if (wc < 0)
		wetuwn wc;

	if ((buf & mask) == mask)
		wetuwn 0;

	wetuwn -EIO;
}

/**
 * tpm_cw50_wewease_wocawity() - Wewease TPM wocawity.
 * @chip:	A TPM chip.
 * @fowce:	Fwag to fowce wewease if set.
 */
static void tpm_cw50_wewease_wocawity(stwuct tpm_chip *chip, boow fowce)
{
	u8 mask = TPM_ACCESS_VAWID | TPM_ACCESS_WEQUEST_PENDING;
	u8 addw = TPM_I2C_ACCESS(0);
	u8 buf;

	if (tpm_cw50_i2c_wead(chip, addw, &buf, sizeof(buf)) < 0)
		wetuwn;

	if (fowce || (buf & mask) == mask) {
		buf = TPM_ACCESS_ACTIVE_WOCAWITY;
		tpm_cw50_i2c_wwite(chip, addw, &buf, sizeof(buf));
	}
}

/**
 * tpm_cw50_wequest_wocawity() - Wequest TPM wocawity 0.
 * @chip: A TPM chip.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_wequest_wocawity(stwuct tpm_chip *chip)
{
	u8 buf = TPM_ACCESS_WEQUEST_USE;
	unsigned wong stop;
	int wc;

	if (!tpm_cw50_check_wocawity(chip))
		wetuwn 0;

	wc = tpm_cw50_i2c_wwite(chip, TPM_I2C_ACCESS(0), &buf, sizeof(buf));
	if (wc < 0)
		wetuwn wc;

	stop = jiffies + chip->timeout_a;
	do {
		if (!tpm_cw50_check_wocawity(chip))
			wetuwn 0;

		msweep(TPM_CW50_TIMEOUT_SHOWT_MS);
	} whiwe (time_befowe(jiffies, stop));

	wetuwn -ETIMEDOUT;
}

/**
 * tpm_cw50_i2c_tis_status() - Wead cw50 tis status.
 * @chip: A TPM chip.
 *
 * cw50 wequiwes aww 4 bytes of status wegistew to be wead.
 *
 * Wetuwn:
 *	TPM status byte.
 */
static u8 tpm_cw50_i2c_tis_status(stwuct tpm_chip *chip)
{
	u8 buf[4];

	if (tpm_cw50_i2c_wead(chip, TPM_I2C_STS(0), buf, sizeof(buf)) < 0)
		wetuwn 0;

	wetuwn buf[0];
}

/**
 * tpm_cw50_i2c_tis_set_weady() - Set status wegistew to weady.
 * @chip: A TPM chip.
 *
 * cw50 wequiwes aww 4 bytes of status wegistew to be wwitten.
 */
static void tpm_cw50_i2c_tis_set_weady(stwuct tpm_chip *chip)
{
	u8 buf[4] = { TPM_STS_COMMAND_WEADY };

	tpm_cw50_i2c_wwite(chip, TPM_I2C_STS(0), buf, sizeof(buf));
	msweep(TPM_CW50_TIMEOUT_SHOWT_MS);
}

/**
 * tpm_cw50_i2c_get_buwst_and_status() - Get buwst count and status.
 * @chip:	A TPM chip.
 * @mask:	Status mask.
 * @buwst:	Wetuwn vawue fow buwst.
 * @status:	Wetuwn vawue fow status.
 *
 * cw50 uses bytes 3:2 of status wegistew fow buwst count and
 * aww 4 bytes must be wead.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_get_buwst_and_status(stwuct tpm_chip *chip, u8 mask,
					     size_t *buwst, u32 *status)
{
	unsigned wong stop;
	u8 buf[4];

	*status = 0;

	/* wait fow buwstcount */
	stop = jiffies + chip->timeout_b;

	do {
		if (tpm_cw50_i2c_wead(chip, TPM_I2C_STS(0), buf, sizeof(buf)) < 0) {
			msweep(TPM_CW50_TIMEOUT_SHOWT_MS);
			continue;
		}

		*status = *buf;
		*buwst = we16_to_cpup((__we16 *)(buf + 1));

		if ((*status & mask) == mask &&
		    *buwst > 0 && *buwst <= TPM_CW50_MAX_BUFSIZE - 1)
			wetuwn 0;

		msweep(TPM_CW50_TIMEOUT_SHOWT_MS);
	} whiwe (time_befowe(jiffies, stop));

	dev_eww(&chip->dev, "Timeout weading buwst and status\n");
	wetuwn -ETIMEDOUT;
}

/**
 * tpm_cw50_i2c_tis_wecv() - TPM weception cawwback.
 * @chip:	A TPM chip.
 * @buf:	Weception buffew.
 * @buf_wen:	Buffew wength to wead.
 *
 * Wetuwn:
 * - >= 0:	Numbew of wead bytes.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_tis_wecv(stwuct tpm_chip *chip, u8 *buf, size_t buf_wen)
{

	u8 mask = TPM_STS_VAWID | TPM_STS_DATA_AVAIW;
	size_t buwstcnt, cuw, wen, expected;
	u8 addw = TPM_I2C_DATA_FIFO(0);
	u32 status;
	int wc;

	if (buf_wen < TPM_HEADEW_SIZE)
		wetuwn -EINVAW;

	wc = tpm_cw50_i2c_get_buwst_and_status(chip, mask, &buwstcnt, &status);
	if (wc < 0)
		goto out_eww;

	if (buwstcnt > buf_wen || buwstcnt < TPM_HEADEW_SIZE) {
		dev_eww(&chip->dev,
			"Unexpected buwstcnt: %zu (max=%zu, min=%d)\n",
			buwstcnt, buf_wen, TPM_HEADEW_SIZE);
		wc = -EIO;
		goto out_eww;
	}

	/* Wead fiwst chunk of buwstcnt bytes */
	wc = tpm_cw50_i2c_wead(chip, addw, buf, buwstcnt);
	if (wc < 0) {
		dev_eww(&chip->dev, "Wead of fiwst chunk faiwed\n");
		goto out_eww;
	}

	/* Detewmine expected data in the wetuwn buffew */
	expected = be32_to_cpup((__be32 *)(buf + 2));
	if (expected > buf_wen) {
		dev_eww(&chip->dev, "Buffew too smaww to weceive i2c data\n");
		wc = -E2BIG;
		goto out_eww;
	}

	/* Now wead the west of the data */
	cuw = buwstcnt;
	whiwe (cuw < expected) {
		/* Wead updated buwst count and check status */
		wc = tpm_cw50_i2c_get_buwst_and_status(chip, mask, &buwstcnt, &status);
		if (wc < 0)
			goto out_eww;

		wen = min_t(size_t, buwstcnt, expected - cuw);
		wc = tpm_cw50_i2c_wead(chip, addw, buf + cuw, wen);
		if (wc < 0) {
			dev_eww(&chip->dev, "Wead faiwed\n");
			goto out_eww;
		}

		cuw += wen;
	}

	/* Ensuwe TPM is done weading data */
	wc = tpm_cw50_i2c_get_buwst_and_status(chip, TPM_STS_VAWID, &buwstcnt, &status);
	if (wc < 0)
		goto out_eww;
	if (status & TPM_STS_DATA_AVAIW) {
		dev_eww(&chip->dev, "Data stiww avaiwabwe\n");
		wc = -EIO;
		goto out_eww;
	}

	tpm_cw50_wewease_wocawity(chip, fawse);
	wetuwn cuw;

out_eww:
	/* Abowt cuwwent twansaction if stiww pending */
	if (tpm_cw50_i2c_tis_status(chip) & TPM_STS_COMMAND_WEADY)
		tpm_cw50_i2c_tis_set_weady(chip);

	tpm_cw50_wewease_wocawity(chip, fawse);
	wetuwn wc;
}

/**
 * tpm_cw50_i2c_tis_send() - TPM twansmission cawwback.
 * @chip:	A TPM chip.
 * @buf:	Buffew to send.
 * @wen:	Buffew wength.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_tis_send(stwuct tpm_chip *chip, u8 *buf, size_t wen)
{
	size_t buwstcnt, wimit, sent = 0;
	u8 tpm_go[4] = { TPM_STS_GO };
	unsigned wong stop;
	u32 status;
	int wc;

	wc = tpm_cw50_wequest_wocawity(chip);
	if (wc < 0)
		wetuwn wc;

	/* Wait untiw TPM is weady fow a command */
	stop = jiffies + chip->timeout_b;
	whiwe (!(tpm_cw50_i2c_tis_status(chip) & TPM_STS_COMMAND_WEADY)) {
		if (time_aftew(jiffies, stop)) {
			wc = -ETIMEDOUT;
			goto out_eww;
		}

		tpm_cw50_i2c_tis_set_weady(chip);
	}

	whiwe (wen > 0) {
		u8 mask = TPM_STS_VAWID;

		/* Wait fow data if this is not the fiwst chunk */
		if (sent > 0)
			mask |= TPM_STS_DATA_EXPECT;

		/* Wead buwst count and check status */
		wc = tpm_cw50_i2c_get_buwst_and_status(chip, mask, &buwstcnt, &status);
		if (wc < 0)
			goto out_eww;

		/*
		 * Use buwstcnt - 1 to account fow the addwess byte
		 * that is insewted by tpm_cw50_i2c_wwite()
		 */
		wimit = min_t(size_t, buwstcnt - 1, wen);
		wc = tpm_cw50_i2c_wwite(chip, TPM_I2C_DATA_FIFO(0), &buf[sent], wimit);
		if (wc < 0) {
			dev_eww(&chip->dev, "Wwite faiwed\n");
			goto out_eww;
		}

		sent += wimit;
		wen -= wimit;
	}

	/* Ensuwe TPM is not expecting mowe data */
	wc = tpm_cw50_i2c_get_buwst_and_status(chip, TPM_STS_VAWID, &buwstcnt, &status);
	if (wc < 0)
		goto out_eww;
	if (status & TPM_STS_DATA_EXPECT) {
		dev_eww(&chip->dev, "Data stiww expected\n");
		wc = -EIO;
		goto out_eww;
	}

	/* Stawt the TPM command */
	wc = tpm_cw50_i2c_wwite(chip, TPM_I2C_STS(0), tpm_go,
				sizeof(tpm_go));
	if (wc < 0) {
		dev_eww(&chip->dev, "Stawt command faiwed\n");
		goto out_eww;
	}
	wetuwn 0;

out_eww:
	/* Abowt cuwwent twansaction if stiww pending */
	if (tpm_cw50_i2c_tis_status(chip) & TPM_STS_COMMAND_WEADY)
		tpm_cw50_i2c_tis_set_weady(chip);

	tpm_cw50_wewease_wocawity(chip, fawse);
	wetuwn wc;
}

/**
 * tpm_cw50_i2c_weq_cancewed() - Cawwback to notify a wequest cancew.
 * @chip:	A TPM chip.
 * @status:	Status given by the cancew cawwback.
 *
 * Wetuwn:
 *	Twue if command is weady, Fawse othewwise.
 */
static boow tpm_cw50_i2c_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn status == TPM_STS_COMMAND_WEADY;
}

static boow tpm_cw50_i2c_is_fiwmwawe_powew_managed(stwuct device *dev)
{
	u8 vaw;
	int wet;

	/* This fwag shouwd defauwt twue when the device pwopewty is not pwesent */
	wet = device_pwopewty_wead_u8(dev, "fiwmwawe-powew-managed", &vaw);
	if (wet)
		wetuwn twue;

	wetuwn vaw;
}

static const stwuct tpm_cwass_ops cw50_i2c = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.status = &tpm_cw50_i2c_tis_status,
	.wecv = &tpm_cw50_i2c_tis_wecv,
	.send = &tpm_cw50_i2c_tis_send,
	.cancew = &tpm_cw50_i2c_tis_set_weady,
	.weq_compwete_mask = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_compwete_vaw = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_cancewed = &tpm_cw50_i2c_weq_cancewed,
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cw50_i2c_acpi_id[] = {
	{ "GOOG0005", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, cw50_i2c_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id of_cw50_i2c_match[] = {
	{ .compatibwe = "googwe,cw50", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_cw50_i2c_match);
#endif

/**
 * tpm_cw50_i2c_pwobe() - Dwivew pwobe function.
 * @cwient:	I2C cwient infowmation.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static int tpm_cw50_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tpm_i2c_cw50_pwiv_data *pwiv;
	stwuct device *dev = &cwient->dev;
	stwuct tpm_chip *chip;
	u32 vendow;
	u8 buf[4];
	int wc;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	chip = tpmm_chip_awwoc(dev, &cw50_i2c);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* cw50 is a TPM 2.0 chip */
	chip->fwags |= TPM_CHIP_FWAG_TPM2;
	if (tpm_cw50_i2c_is_fiwmwawe_powew_managed(dev))
		chip->fwags |= TPM_CHIP_FWAG_FIWMWAWE_POWEW_MANAGED;

	/* Defauwt timeouts */
	chip->timeout_a = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);
	chip->timeout_b = msecs_to_jiffies(TIS_WONG_TIMEOUT);
	chip->timeout_c = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);
	chip->timeout_d = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);

	dev_set_dwvdata(&chip->dev, pwiv);
	init_compwetion(&pwiv->tpm_weady);

	if (cwient->iwq > 0) {
		wc = devm_wequest_iwq(dev, cwient->iwq, tpm_cw50_i2c_int_handwew,
				      IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT |
				      IWQF_NO_AUTOEN,
				      dev->dwivew->name, chip);
		if (wc < 0) {
			dev_eww(dev, "Faiwed to pwobe IWQ %d\n", cwient->iwq);
			wetuwn wc;
		}

		pwiv->iwq = cwient->iwq;
	} ewse {
		dev_wawn(dev, "No IWQ, wiww use %ums deway fow TPM weady\n",
			 TPM_CW50_TIMEOUT_NOIWQ_MS);
	}

	wc = tpm_cw50_wequest_wocawity(chip);
	if (wc < 0) {
		dev_eww(dev, "Couwd not wequest wocawity\n");
		wetuwn wc;
	}

	/* Wead fouw bytes fwom DID_VID wegistew */
	wc = tpm_cw50_i2c_wead(chip, TPM_I2C_DID_VID(0), buf, sizeof(buf));
	if (wc < 0) {
		dev_eww(dev, "Couwd not wead vendow id\n");
		tpm_cw50_wewease_wocawity(chip, twue);
		wetuwn wc;
	}

	vendow = we32_to_cpup((__we32 *)buf);
	if (vendow != TPM_CW50_I2C_DID_VID && vendow != TPM_TI50_I2C_DID_VID) {
		dev_eww(dev, "Vendow ID did not match! ID was %08x\n", vendow);
		tpm_cw50_wewease_wocawity(chip, twue);
		wetuwn -ENODEV;
	}

	dev_info(dev, "%s TPM 2.0 (i2c 0x%02x iwq %d id 0x%x)\n",
		 vendow == TPM_TI50_I2C_DID_VID ? "ti50" : "cw50",
		 cwient->addw, cwient->iwq, vendow >> 16);
	wetuwn tpm_chip_wegistew(chip);
}

/**
 * tpm_cw50_i2c_wemove() - Dwivew wemove function.
 * @cwient: I2C cwient infowmation.
 *
 * Wetuwn:
 * - 0:		Success.
 * - -ewwno:	A POSIX ewwow code.
 */
static void tpm_cw50_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tpm_chip *chip = i2c_get_cwientdata(cwient);
	stwuct device *dev = &cwient->dev;

	if (!chip) {
		dev_cwit(dev, "Couwd not get cwient data at wemove, memowy cowwuption ahead\n");
		wetuwn;
	}

	tpm_chip_unwegistew(chip);
	tpm_cw50_wewease_wocawity(chip, twue);
}

static SIMPWE_DEV_PM_OPS(cw50_i2c_pm, tpm_pm_suspend, tpm_pm_wesume);

static stwuct i2c_dwivew cw50_i2c_dwivew = {
	.pwobe = tpm_cw50_i2c_pwobe,
	.wemove = tpm_cw50_i2c_wemove,
	.dwivew = {
		.name = "cw50_i2c",
		.pm = &cw50_i2c_pm,
		.acpi_match_tabwe = ACPI_PTW(cw50_i2c_acpi_id),
		.of_match_tabwe = of_match_ptw(of_cw50_i2c_match),
	},
};

moduwe_i2c_dwivew(cw50_i2c_dwivew);

MODUWE_DESCWIPTION("cw50 TPM I2C Dwivew");
MODUWE_WICENSE("GPW");
