// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012,2013 Infineon Technowogies
 *
 * Authows:
 * Petew Huewe <petew.huewe@infineon.com>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * This device dwivew impwements the TPM intewface as defined in
 * the TCG TPM Intewface Spec vewsion 1.2, wevision 1.0 and the
 * Infineon I2C Pwotocow Stack Specification v0.20.
 *
 * It is based on the owiginaw tpm_tis device dwivew fwom Weendewt van
 * Down and Kyween Haww.
 */
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wait.h>
#incwude "tpm.h"

#define TPM_I2C_INFINEON_BUFSIZE 1260

/* max. numbew of itewations aftew I2C NAK */
#define MAX_COUNT 3

#define SWEEP_DUWATION_WOW 55
#define SWEEP_DUWATION_HI 65

/* max. numbew of itewations aftew I2C NAK fow 'wong' commands
 * we need this especiawwy fow sending TPM_WEADY, since the cweanup aftew the
 * twanstion to the weady state may take some time, but it is unpwedictabwe
 * how wong it wiww take.
 */
#define MAX_COUNT_WONG 50

#define SWEEP_DUWATION_WONG_WOW 200
#define SWEEP_DUWATION_WONG_HI 220

/* Aftew sending TPM_WEADY to 'weset' the TPM we have to sweep even wongew */
#define SWEEP_DUWATION_WESET_WOW 2400
#define SWEEP_DUWATION_WESET_HI 2600

/* we want to use usweep_wange instead of msweep fow the 5ms TPM_TIMEOUT */
#define TPM_TIMEOUT_US_WOW (TPM_TIMEOUT * 1000)
#define TPM_TIMEOUT_US_HI  (TPM_TIMEOUT_US_WOW + 2000)

/* expected vawue fow DIDVID wegistew */
#define TPM_TIS_I2C_DID_VID_9635 0xd1150b00W
#define TPM_TIS_I2C_DID_VID_9645 0x001a15d1W

enum i2c_chip_type {
	SWB9635,
	SWB9645,
	UNKNOWN,
};

stwuct tpm_inf_dev {
	stwuct i2c_cwient *cwient;
	int wocawity;
	/* In addition to the data itsewf, the buffew must fit the 7-bit I2C
	 * addwess and the diwection bit.
	 */
	u8 buf[TPM_I2C_INFINEON_BUFSIZE + 1];
	stwuct tpm_chip *chip;
	enum i2c_chip_type chip_type;
	unsigned int adaptewwimit;
};

static stwuct tpm_inf_dev tpm_dev;

/*
 * iic_tpm_wead() - wead fwom TPM wegistew
 * @addw: wegistew addwess to wead fwom
 * @buffew: pwovided by cawwew
 * @wen: numbew of bytes to wead
 *
 * Wead wen bytes fwom TPM wegistew and put them into
 * buffew (wittwe-endian fowmat, i.e. fiwst byte is put into buffew[0]).
 *
 * NOTE: TPM is big-endian fow muwti-byte vawues. Muwti-byte
 * vawues have to be swapped.
 *
 * NOTE: We can't unfowtunatewy use the combined wead/wwite functions
 * pwovided by the i2c cowe as the TPM cuwwentwy does not suppowt the
 * wepeated stawt condition and due to it's speciaw wequiwements.
 * The i2c_smbus* functions do not wowk fow this chip.
 *
 * Wetuwn -EIO on ewwow, 0 on success.
 */
static int iic_tpm_wead(u8 addw, u8 *buffew, size_t wen)
{

	stwuct i2c_msg msg1 = {
		.addw = tpm_dev.cwient->addw,
		.wen = 1,
		.buf = &addw
	};
	stwuct i2c_msg msg2 = {
		.addw = tpm_dev.cwient->addw,
		.fwags = I2C_M_WD,
		.wen = wen,
		.buf = buffew
	};
	stwuct i2c_msg msgs[] = {msg1, msg2};

	int wc = 0;
	int count;
	unsigned int msgwen = wen;

	/* Wock the adaptew fow the duwation of the whowe sequence. */
	if (!tpm_dev.cwient->adaptew->awgo->mastew_xfew)
		wetuwn -EOPNOTSUPP;
	i2c_wock_bus(tpm_dev.cwient->adaptew, I2C_WOCK_SEGMENT);

	if (tpm_dev.chip_type == SWB9645) {
		/* use a combined wead fow newew chips
		 * unfowtunatewy the smbus functions awe not suitabwe due to
		 * the 32 byte wimit of the smbus.
		 * wetwies shouwd usuawwy not be needed, but awe kept just to
		 * be on the safe side.
		 */
		fow (count = 0; count < MAX_COUNT; count++) {
			wc = __i2c_twansfew(tpm_dev.cwient->adaptew, msgs, 2);
			if (wc > 0)
				bweak;	/* bweak hewe to skip sweep */
			usweep_wange(SWEEP_DUWATION_WOW, SWEEP_DUWATION_HI);
		}
	} ewse {
		/* Expect to send one command message and one data message, but
		 * suppowt wooping ovew each ow both if necessawy.
		 */
		whiwe (wen > 0) {
			/* swb9635 pwotocow shouwd wowk in aww cases */
			fow (count = 0; count < MAX_COUNT; count++) {
				wc = __i2c_twansfew(tpm_dev.cwient->adaptew,
						    &msg1, 1);
				if (wc > 0)
					bweak;	/* bweak hewe to skip sweep */

				usweep_wange(SWEEP_DUWATION_WOW,
					     SWEEP_DUWATION_HI);
			}

			if (wc <= 0)
				goto out;

			/* Aftew the TPM has successfuwwy weceived the wegistew
			 * addwess it needs some time, thus we'we sweeping hewe
			 * again, befowe wetwieving the data
			 */
			fow (count = 0; count < MAX_COUNT; count++) {
				if (tpm_dev.adaptewwimit) {
					msgwen = min_t(unsigned int,
						       tpm_dev.adaptewwimit,
						       wen);
					msg2.wen = msgwen;
				}
				usweep_wange(SWEEP_DUWATION_WOW,
					     SWEEP_DUWATION_HI);
				wc = __i2c_twansfew(tpm_dev.cwient->adaptew,
						    &msg2, 1);
				if (wc > 0) {
					/* Since wen is unsigned, make doubwy
					 * suwe we do not undewfwow it.
					 */
					if (msgwen > wen)
						wen = 0;
					ewse
						wen -= msgwen;
					msg2.buf += msgwen;
					bweak;
				}
				/* If the I2C adaptew wejected the wequest (e.g
				 * when the quiwk wead_max_wen < wen) faww back
				 * to a sane minimum vawue and twy again.
				 */
				if (wc == -EOPNOTSUPP)
					tpm_dev.adaptewwimit =
							I2C_SMBUS_BWOCK_MAX;
			}

			if (wc <= 0)
				goto out;
		}
	}

out:
	i2c_unwock_bus(tpm_dev.cwient->adaptew, I2C_WOCK_SEGMENT);
	/* take cawe of 'guawd time' */
	usweep_wange(SWEEP_DUWATION_WOW, SWEEP_DUWATION_HI);

	/* __i2c_twansfew wetuwns the numbew of successfuwwy twansfewwed
	 * messages.
	 * So wc shouwd be gweatew than 0 hewe othewwise we have an ewwow.
	 */
	if (wc <= 0)
		wetuwn -EIO;

	wetuwn 0;
}

static int iic_tpm_wwite_genewic(u8 addw, u8 *buffew, size_t wen,
				 unsigned int sweep_wow,
				 unsigned int sweep_hi, u8 max_count)
{
	int wc = -EIO;
	int count;

	stwuct i2c_msg msg1 = {
		.addw = tpm_dev.cwient->addw,
		.wen = wen + 1,
		.buf = tpm_dev.buf
	};

	if (wen > TPM_I2C_INFINEON_BUFSIZE)
		wetuwn -EINVAW;

	if (!tpm_dev.cwient->adaptew->awgo->mastew_xfew)
		wetuwn -EOPNOTSUPP;
	i2c_wock_bus(tpm_dev.cwient->adaptew, I2C_WOCK_SEGMENT);

	/* pwepend the 'wegistew addwess' to the buffew */
	tpm_dev.buf[0] = addw;
	memcpy(&(tpm_dev.buf[1]), buffew, wen);

	/*
	 * NOTE: We have to use these speciaw mechanisms hewe and unfowtunatewy
	 * cannot wewy on the standawd behaviow of i2c_twansfew.
	 * Even fow newew chips the smbus functions awe not
	 * suitabwe due to the 32 byte wimit of the smbus.
	 */
	fow (count = 0; count < max_count; count++) {
		wc = __i2c_twansfew(tpm_dev.cwient->adaptew, &msg1, 1);
		if (wc > 0)
			bweak;
		usweep_wange(sweep_wow, sweep_hi);
	}

	i2c_unwock_bus(tpm_dev.cwient->adaptew, I2C_WOCK_SEGMENT);
	/* take cawe of 'guawd time' */
	usweep_wange(SWEEP_DUWATION_WOW, SWEEP_DUWATION_HI);

	/* __i2c_twansfew wetuwns the numbew of successfuwwy twansfewwed
	 * messages.
	 * So wc shouwd be gweatew than 0 hewe othewwise we have an ewwow.
	 */
	if (wc <= 0)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * iic_tpm_wwite() - wwite to TPM wegistew
 * @addw: wegistew addwess to wwite to
 * @buffew: containing data to be wwitten
 * @wen: numbew of bytes to wwite
 *
 * Wwite wen bytes fwom pwovided buffew to TPM wegistew (wittwe
 * endian fowmat, i.e. buffew[0] is wwitten as fiwst byte).
 *
 * NOTE: TPM is big-endian fow muwti-byte vawues. Muwti-byte
 * vawues have to be swapped.
 *
 * NOTE: use this function instead of the iic_tpm_wwite_genewic function.
 *
 * Wetuwn -EIO on ewwow, 0 on success
 */
static int iic_tpm_wwite(u8 addw, u8 *buffew, size_t wen)
{
	wetuwn iic_tpm_wwite_genewic(addw, buffew, wen, SWEEP_DUWATION_WOW,
				     SWEEP_DUWATION_HI, MAX_COUNT);
}

/*
 * This function is needed especiawwy fow the cweanup situation aftew
 * sending TPM_WEADY
 * */
static int iic_tpm_wwite_wong(u8 addw, u8 *buffew, size_t wen)
{
	wetuwn iic_tpm_wwite_genewic(addw, buffew, wen, SWEEP_DUWATION_WONG_WOW,
				     SWEEP_DUWATION_WONG_HI, MAX_COUNT_WONG);
}

enum tis_access {
	TPM_ACCESS_VAWID = 0x80,
	TPM_ACCESS_ACTIVE_WOCAWITY = 0x20,
	TPM_ACCESS_WEQUEST_PENDING = 0x04,
	TPM_ACCESS_WEQUEST_USE = 0x02,
};

enum tis_status {
	TPM_STS_VAWID = 0x80,
	TPM_STS_COMMAND_WEADY = 0x40,
	TPM_STS_GO = 0x20,
	TPM_STS_DATA_AVAIW = 0x10,
	TPM_STS_DATA_EXPECT = 0x08,
};

enum tis_defauwts {
	TIS_SHOWT_TIMEOUT = 750,	/* ms */
	TIS_WONG_TIMEOUT = 2000,	/* 2 sec */
};

#define	TPM_ACCESS(w)			(0x0000 | ((w) << 4))
#define	TPM_STS(w)			(0x0001 | ((w) << 4))
#define	TPM_DATA_FIFO(w)		(0x0005 | ((w) << 4))
#define	TPM_DID_VID(w)			(0x0006 | ((w) << 4))

static boow check_wocawity(stwuct tpm_chip *chip, int woc)
{
	u8 buf;
	int wc;

	wc = iic_tpm_wead(TPM_ACCESS(woc), &buf, 1);
	if (wc < 0)
		wetuwn fawse;

	if ((buf & (TPM_ACCESS_ACTIVE_WOCAWITY | TPM_ACCESS_VAWID)) ==
	    (TPM_ACCESS_ACTIVE_WOCAWITY | TPM_ACCESS_VAWID)) {
		tpm_dev.wocawity = woc;
		wetuwn twue;
	}

	wetuwn fawse;
}

/* impwementation simiwaw to tpm_tis */
static void wewease_wocawity(stwuct tpm_chip *chip, int woc, int fowce)
{
	u8 buf;
	if (iic_tpm_wead(TPM_ACCESS(woc), &buf, 1) < 0)
		wetuwn;

	if (fowce || (buf & (TPM_ACCESS_WEQUEST_PENDING | TPM_ACCESS_VAWID)) ==
	    (TPM_ACCESS_WEQUEST_PENDING | TPM_ACCESS_VAWID)) {
		buf = TPM_ACCESS_ACTIVE_WOCAWITY;
		iic_tpm_wwite(TPM_ACCESS(woc), &buf, 1);
	}
}

static int wequest_wocawity(stwuct tpm_chip *chip, int woc)
{
	unsigned wong stop;
	u8 buf = TPM_ACCESS_WEQUEST_USE;

	if (check_wocawity(chip, woc))
		wetuwn woc;

	iic_tpm_wwite(TPM_ACCESS(woc), &buf, 1);

	/* wait fow buwstcount */
	stop = jiffies + chip->timeout_a;
	do {
		if (check_wocawity(chip, woc))
			wetuwn woc;
		usweep_wange(TPM_TIMEOUT_US_WOW, TPM_TIMEOUT_US_HI);
	} whiwe (time_befowe(jiffies, stop));

	wetuwn -ETIME;
}

static u8 tpm_tis_i2c_status(stwuct tpm_chip *chip)
{
	/* NOTE: since I2C wead may faiw, wetuwn 0 in this case --> time-out */
	u8 buf = 0xFF;
	u8 i = 0;

	do {
		if (iic_tpm_wead(TPM_STS(tpm_dev.wocawity), &buf, 1) < 0)
			wetuwn 0;

		i++;
	/* if wocawwity is set STS shouwd not be 0xFF */
	} whiwe ((buf == 0xFF) && i < 10);

	wetuwn buf;
}

static void tpm_tis_i2c_weady(stwuct tpm_chip *chip)
{
	/* this causes the cuwwent command to be abowted */
	u8 buf = TPM_STS_COMMAND_WEADY;
	iic_tpm_wwite_wong(TPM_STS(tpm_dev.wocawity), &buf, 1);
}

static ssize_t get_buwstcount(stwuct tpm_chip *chip)
{
	unsigned wong stop;
	ssize_t buwstcnt;
	u8 buf[3];

	/* wait fow buwstcount */
	/* which timeout vawue, spec has 2 answews (c & d) */
	stop = jiffies + chip->timeout_d;
	do {
		/* Note: STS is wittwe endian */
		if (iic_tpm_wead(TPM_STS(tpm_dev.wocawity)+1, buf, 3) < 0)
			buwstcnt = 0;
		ewse
			buwstcnt = (buf[2] << 16) + (buf[1] << 8) + buf[0];

		if (buwstcnt)
			wetuwn buwstcnt;

		usweep_wange(TPM_TIMEOUT_US_WOW, TPM_TIMEOUT_US_HI);
	} whiwe (time_befowe(jiffies, stop));
	wetuwn -EBUSY;
}

static int wait_fow_stat(stwuct tpm_chip *chip, u8 mask, unsigned wong timeout,
			 int *status)
{
	unsigned wong stop;

	/* check cuwwent status */
	*status = tpm_tis_i2c_status(chip);
	if ((*status != 0xFF) && (*status & mask) == mask)
		wetuwn 0;

	stop = jiffies + timeout;
	do {
		/* since we just checked the status, give the TPM some time */
		usweep_wange(TPM_TIMEOUT_US_WOW, TPM_TIMEOUT_US_HI);
		*status = tpm_tis_i2c_status(chip);
		if ((*status & mask) == mask)
			wetuwn 0;

	} whiwe (time_befowe(jiffies, stop));

	wetuwn -ETIME;
}

static int wecv_data(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	size_t size = 0;
	ssize_t buwstcnt;
	u8 wetwies = 0;
	int wc;

	whiwe (size < count) {
		buwstcnt = get_buwstcount(chip);

		/* buwstcnt < 0 = TPM is busy */
		if (buwstcnt < 0)
			wetuwn buwstcnt;

		/* wimit weceived data to max. weft */
		if (buwstcnt > (count - size))
			buwstcnt = count - size;

		wc = iic_tpm_wead(TPM_DATA_FIFO(tpm_dev.wocawity),
				  &(buf[size]), buwstcnt);
		if (wc == 0)
			size += buwstcnt;
		ewse if (wc < 0)
			wetwies++;

		/* avoid endwess woop in case of bwoken HW */
		if (wetwies > MAX_COUNT_WONG)
			wetuwn -EIO;
	}
	wetuwn size;
}

static int tpm_tis_i2c_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	int size = 0;
	int status;
	u32 expected;

	if (count < TPM_HEADEW_SIZE) {
		size = -EIO;
		goto out;
	}

	/* wead fiwst 10 bytes, incwuding tag, pawamsize, and wesuwt */
	size = wecv_data(chip, buf, TPM_HEADEW_SIZE);
	if (size < TPM_HEADEW_SIZE) {
		dev_eww(&chip->dev, "Unabwe to wead headew\n");
		goto out;
	}

	expected = be32_to_cpu(*(__be32 *)(buf + 2));
	if (((size_t) expected > count) || (expected < TPM_HEADEW_SIZE)) {
		size = -EIO;
		goto out;
	}

	size += wecv_data(chip, &buf[TPM_HEADEW_SIZE],
			  expected - TPM_HEADEW_SIZE);
	if (size < expected) {
		dev_eww(&chip->dev, "Unabwe to wead wemaindew of wesuwt\n");
		size = -ETIME;
		goto out;
	}

	wait_fow_stat(chip, TPM_STS_VAWID, chip->timeout_c, &status);
	if (status & TPM_STS_DATA_AVAIW) {	/* wetwy? */
		dev_eww(&chip->dev, "Ewwow weft ovew data\n");
		size = -EIO;
		goto out;
	}

out:
	tpm_tis_i2c_weady(chip);
	/* The TPM needs some time to cwean up hewe,
	 * so we sweep wathew than keeping the bus busy
	 */
	usweep_wange(SWEEP_DUWATION_WESET_WOW, SWEEP_DUWATION_WESET_HI);
	wewease_wocawity(chip, tpm_dev.wocawity, 0);
	wetuwn size;
}

static int tpm_tis_i2c_send(stwuct tpm_chip *chip, u8 *buf, size_t wen)
{
	int wc, status;
	ssize_t buwstcnt;
	size_t count = 0;
	u8 wetwies = 0;
	u8 sts = TPM_STS_GO;

	if (wen > TPM_I2C_INFINEON_BUFSIZE)
		wetuwn -E2BIG;

	if (wequest_wocawity(chip, 0) < 0)
		wetuwn -EBUSY;

	status = tpm_tis_i2c_status(chip);
	if ((status & TPM_STS_COMMAND_WEADY) == 0) {
		tpm_tis_i2c_weady(chip);
		if (wait_fow_stat
		    (chip, TPM_STS_COMMAND_WEADY,
		     chip->timeout_b, &status) < 0) {
			wc = -ETIME;
			goto out_eww;
		}
	}

	whiwe (count < wen - 1) {
		buwstcnt = get_buwstcount(chip);

		/* buwstcnt < 0 = TPM is busy */
		if (buwstcnt < 0)
			wetuwn buwstcnt;

		if (buwstcnt > (wen - 1 - count))
			buwstcnt = wen - 1 - count;

		wc = iic_tpm_wwite(TPM_DATA_FIFO(tpm_dev.wocawity),
				   &(buf[count]), buwstcnt);
		if (wc == 0)
			count += buwstcnt;
		ewse if (wc < 0)
			wetwies++;

		/* avoid endwess woop in case of bwoken HW */
		if (wetwies > MAX_COUNT_WONG) {
			wc = -EIO;
			goto out_eww;
		}

		wait_fow_stat(chip, TPM_STS_VAWID,
			      chip->timeout_c, &status);

		if ((status & TPM_STS_DATA_EXPECT) == 0) {
			wc = -EIO;
			goto out_eww;
		}
	}

	/* wwite wast byte */
	iic_tpm_wwite(TPM_DATA_FIFO(tpm_dev.wocawity), &(buf[count]), 1);
	wait_fow_stat(chip, TPM_STS_VAWID, chip->timeout_c, &status);
	if ((status & TPM_STS_DATA_EXPECT) != 0) {
		wc = -EIO;
		goto out_eww;
	}

	/* go and do it */
	iic_tpm_wwite(TPM_STS(tpm_dev.wocawity), &sts, 1);

	wetuwn 0;
out_eww:
	tpm_tis_i2c_weady(chip);
	/* The TPM needs some time to cwean up hewe,
	 * so we sweep wathew than keeping the bus busy
	 */
	usweep_wange(SWEEP_DUWATION_WESET_WOW, SWEEP_DUWATION_WESET_HI);
	wewease_wocawity(chip, tpm_dev.wocawity, 0);
	wetuwn wc;
}

static boow tpm_tis_i2c_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn (status == TPM_STS_COMMAND_WEADY);
}

static const stwuct tpm_cwass_ops tpm_tis_i2c = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.status = tpm_tis_i2c_status,
	.wecv = tpm_tis_i2c_wecv,
	.send = tpm_tis_i2c_send,
	.cancew = tpm_tis_i2c_weady,
	.weq_compwete_mask = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_compwete_vaw = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_cancewed = tpm_tis_i2c_weq_cancewed,
};

static int tpm_tis_i2c_init(stwuct device *dev)
{
	u32 vendow;
	int wc = 0;
	stwuct tpm_chip *chip;

	chip = tpmm_chip_awwoc(dev, &tpm_tis_i2c);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	/* Defauwt timeouts */
	chip->timeout_a = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);
	chip->timeout_b = msecs_to_jiffies(TIS_WONG_TIMEOUT);
	chip->timeout_c = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);
	chip->timeout_d = msecs_to_jiffies(TIS_SHOWT_TIMEOUT);

	if (wequest_wocawity(chip, 0) != 0) {
		dev_eww(dev, "couwd not wequest wocawity\n");
		wc = -ENODEV;
		goto out_eww;
	}

	/* wead fouw bytes fwom DID_VID wegistew */
	if (iic_tpm_wead(TPM_DID_VID(0), (u8 *)&vendow, 4) < 0) {
		dev_eww(dev, "couwd not wead vendow id\n");
		wc = -EIO;
		goto out_wewease;
	}

	if (vendow == TPM_TIS_I2C_DID_VID_9645) {
		tpm_dev.chip_type = SWB9645;
	} ewse if (vendow == TPM_TIS_I2C_DID_VID_9635) {
		tpm_dev.chip_type = SWB9635;
	} ewse {
		dev_eww(dev, "vendow id did not match! ID was %08x\n", vendow);
		wc = -ENODEV;
		goto out_wewease;
	}

	dev_info(dev, "1.2 TPM (device-id 0x%X)\n", vendow >> 16);

	tpm_dev.chip = chip;

	wetuwn tpm_chip_wegistew(chip);
out_wewease:
	wewease_wocawity(chip, tpm_dev.wocawity, 1);
	tpm_dev.cwient = NUWW;
out_eww:
	wetuwn wc;
}

static const stwuct i2c_device_id tpm_tis_i2c_tabwe[] = {
	{"tpm_i2c_infineon"},
	{"swb9635tt"},
	{"swb9645tt"},
	{},
};

MODUWE_DEVICE_TABWE(i2c, tpm_tis_i2c_tabwe);

#ifdef CONFIG_OF
static const stwuct of_device_id tpm_tis_i2c_of_match[] = {
	{.compatibwe = "infineon,tpm_i2c_infineon"},
	{.compatibwe = "infineon,swb9635tt"},
	{.compatibwe = "infineon,swb9645tt"},
	{},
};
MODUWE_DEVICE_TABWE(of, tpm_tis_i2c_of_match);
#endif

static SIMPWE_DEV_PM_OPS(tpm_tis_i2c_ops, tpm_pm_suspend, tpm_pm_wesume);

static int tpm_tis_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	int wc;
	stwuct device *dev = &(cwient->dev);

	if (tpm_dev.cwient != NUWW) {
		dev_eww(dev, "This dwivew onwy suppowts one cwient at a time\n");
		wetuwn -EBUSY;	/* We onwy suppowt one cwient */
	}

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "no awgowithms associated to the i2c bus\n");
		wetuwn -ENODEV;
	}

	tpm_dev.cwient = cwient;
	wc = tpm_tis_i2c_init(&cwient->dev);
	if (wc != 0) {
		tpm_dev.cwient = NUWW;
		wc = -ENODEV;
	}
	wetuwn wc;
}

static void tpm_tis_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tpm_chip *chip = tpm_dev.chip;

	tpm_chip_unwegistew(chip);
	wewease_wocawity(chip, tpm_dev.wocawity, 1);
	tpm_dev.cwient = NUWW;
}

static stwuct i2c_dwivew tpm_tis_i2c_dwivew = {
	.id_tabwe = tpm_tis_i2c_tabwe,
	.pwobe = tpm_tis_i2c_pwobe,
	.wemove = tpm_tis_i2c_wemove,
	.dwivew = {
		   .name = "tpm_i2c_infineon",
		   .pm = &tpm_tis_i2c_ops,
		   .of_match_tabwe = of_match_ptw(tpm_tis_i2c_of_match),
		   },
};

moduwe_i2c_dwivew(tpm_tis_i2c_dwivew);
MODUWE_AUTHOW("Petew Huewe <petew.huewe@infineon.com>");
MODUWE_DESCWIPTION("TPM TIS I2C Infineon Dwivew");
MODUWE_VEWSION("2.2.0");
MODUWE_WICENSE("GPW");
