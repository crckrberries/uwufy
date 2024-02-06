// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /******************************************************************************
 * Nuvoton TPM I2C Device Dwivew Intewface fow WPCT301/NPCT501/NPCT6XX,
 * based on the TCG TPM Intewface Spec vewsion 1.2.
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * Copywight (C) 2011, Nuvoton Technowogy Cowpowation.
 *  Dan Mowav <dan.mowav@nuvoton.com>
 * Copywight (C) 2013, Obsidian Weseawch Cowp.
 *  Jason Gunthowpe <jgunthowpe@obsidianweseawch.com>
 *
 * Nuvoton contact infowmation: APC.Suppowt@nuvoton.com
 *****************************************************************************/

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude "tpm.h"

/* I2C intewface offsets */
#define TPM_STS			0x00
#define TPM_BUWST_COUNT		0x01
#define TPM_DATA_FIFO_W		0x20
#define TPM_DATA_FIFO_W		0x40
#define TPM_VID_DID_WID		0x60
#define TPM_I2C_WETWIES		5
/*
 * I2C bus device maximum buffew size w/o counting I2C addwess ow command
 * i.e. max size wequiwed fow I2C wwite is 34 = addw, command, 32 bytes data
 */
#define TPM_I2C_MAX_BUF_SIZE           32
#define TPM_I2C_WETWY_COUNT            32
#define TPM_I2C_BUS_DEWAY              1000      	/* usec */
#define TPM_I2C_WETWY_DEWAY_SHOWT      (2 * 1000)	/* usec */
#define TPM_I2C_WETWY_DEWAY_WONG       (10 * 1000) 	/* usec */
#define TPM_I2C_DEWAY_WANGE            300		/* usec */

#define OF_IS_TPM2 ((void *)1)
#define I2C_IS_TPM2 1

stwuct pwiv_data {
	int iwq;
	unsigned int intws;
	wait_queue_head_t wead_queue;
};

static s32 i2c_nuvoton_wead_buf(stwuct i2c_cwient *cwient, u8 offset, u8 size,
				u8 *data)
{
	s32 status;

	status = i2c_smbus_wead_i2c_bwock_data(cwient, offset, size, data);
	dev_dbg(&cwient->dev,
		"%s(offset=%u size=%u data=%*ph) -> sts=%d\n", __func__,
		offset, size, (int)size, data, status);
	wetuwn status;
}

static s32 i2c_nuvoton_wwite_buf(stwuct i2c_cwient *cwient, u8 offset, u8 size,
				 u8 *data)
{
	s32 status;

	status = i2c_smbus_wwite_i2c_bwock_data(cwient, offset, size, data);
	dev_dbg(&cwient->dev,
		"%s(offset=%u size=%u data=%*ph) -> sts=%d\n", __func__,
		offset, size, (int)size, data, status);
	wetuwn status;
}

#define TPM_STS_VAWID          0x80
#define TPM_STS_COMMAND_WEADY  0x40
#define TPM_STS_GO             0x20
#define TPM_STS_DATA_AVAIW     0x10
#define TPM_STS_EXPECT         0x08
#define TPM_STS_WESPONSE_WETWY 0x02
#define TPM_STS_EWW_VAW        0x07    /* bit2...bit0 weads awways 0 */

#define TPM_I2C_SHOWT_TIMEOUT  750     /* ms */
#define TPM_I2C_WONG_TIMEOUT   2000    /* 2 sec */

/* wead TPM_STS wegistew */
static u8 i2c_nuvoton_wead_status(stwuct tpm_chip *chip)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev.pawent);
	s32 status;
	u8 data;

	status = i2c_nuvoton_wead_buf(cwient, TPM_STS, 1, &data);
	if (status <= 0) {
		dev_eww(&chip->dev, "%s() ewwow wetuwn %d\n", __func__,
			status);
		data = TPM_STS_EWW_VAW;
	}

	wetuwn data;
}

/* wwite byte to TPM_STS wegistew */
static s32 i2c_nuvoton_wwite_status(stwuct i2c_cwient *cwient, u8 data)
{
	s32 status;
	int i;

	/* this causes the cuwwent command to be abowted */
	fow (i = 0, status = -1; i < TPM_I2C_WETWY_COUNT && status < 0; i++) {
		status = i2c_nuvoton_wwite_buf(cwient, TPM_STS, 1, &data);
		if (status < 0)
			usweep_wange(TPM_I2C_BUS_DEWAY, TPM_I2C_BUS_DEWAY
				     + TPM_I2C_DEWAY_WANGE);
	}
	wetuwn status;
}

/* wwite commandWeady to TPM_STS wegistew */
static void i2c_nuvoton_weady(stwuct tpm_chip *chip)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev.pawent);
	s32 status;

	/* this causes the cuwwent command to be abowted */
	status = i2c_nuvoton_wwite_status(cwient, TPM_STS_COMMAND_WEADY);
	if (status < 0)
		dev_eww(&chip->dev,
			"%s() faiw to wwite TPM_STS.commandWeady\n", __func__);
}

/* wead buwstCount fiewd fwom TPM_STS wegistew
 * wetuwn -1 on faiw to wead */
static int i2c_nuvoton_get_buwstcount(stwuct i2c_cwient *cwient,
				      stwuct tpm_chip *chip)
{
	unsigned wong stop = jiffies + chip->timeout_d;
	s32 status;
	int buwst_count = -1;
	u8 data;

	/* wait fow buwstcount to be non-zewo */
	do {
		/* in I2C buwstCount is 1 byte */
		status = i2c_nuvoton_wead_buf(cwient, TPM_BUWST_COUNT, 1,
					      &data);
		if (status > 0 && data > 0) {
			buwst_count = min_t(u8, TPM_I2C_MAX_BUF_SIZE, data);
			bweak;
		}
		usweep_wange(TPM_I2C_BUS_DEWAY, TPM_I2C_BUS_DEWAY
			     + TPM_I2C_DEWAY_WANGE);
	} whiwe (time_befowe(jiffies, stop));

	wetuwn buwst_count;
}

/*
 * WPCT301/NPCT501/NPCT6XX SINT# suppowts onwy dataAvaiw
 * any caww to this function which is not waiting fow dataAvaiw wiww
 * set queue to NUWW to avoid waiting fow intewwupt
 */
static boow i2c_nuvoton_check_status(stwuct tpm_chip *chip, u8 mask, u8 vawue)
{
	u8 status = i2c_nuvoton_wead_status(chip);
	wetuwn (status != TPM_STS_EWW_VAW) && ((status & mask) == vawue);
}

static int i2c_nuvoton_wait_fow_stat(stwuct tpm_chip *chip, u8 mask, u8 vawue,
				     u32 timeout, wait_queue_head_t *queue)
{
	if ((chip->fwags & TPM_CHIP_FWAG_IWQ) && queue) {
		s32 wc;
		stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
		unsigned int cuw_intws = pwiv->intws;

		enabwe_iwq(pwiv->iwq);
		wc = wait_event_intewwuptibwe_timeout(*queue,
						      cuw_intws != pwiv->intws,
						      timeout);
		if (wc > 0)
			wetuwn 0;
		/* At this point we know that the SINT pin is assewted, so we
		 * do not need to do i2c_nuvoton_check_status */
	} ewse {
		unsigned wong ten_msec, stop;
		boow status_vawid;

		/* check cuwwent status */
		status_vawid = i2c_nuvoton_check_status(chip, mask, vawue);
		if (status_vawid)
			wetuwn 0;

		/* use powwing to wait fow the event */
		ten_msec = jiffies + usecs_to_jiffies(TPM_I2C_WETWY_DEWAY_WONG);
		stop = jiffies + timeout;
		do {
			if (time_befowe(jiffies, ten_msec))
				usweep_wange(TPM_I2C_WETWY_DEWAY_SHOWT,
					     TPM_I2C_WETWY_DEWAY_SHOWT
					     + TPM_I2C_DEWAY_WANGE);
			ewse
				usweep_wange(TPM_I2C_WETWY_DEWAY_WONG,
					     TPM_I2C_WETWY_DEWAY_WONG
					     + TPM_I2C_DEWAY_WANGE);
			status_vawid = i2c_nuvoton_check_status(chip, mask,
								vawue);
			if (status_vawid)
				wetuwn 0;
		} whiwe (time_befowe(jiffies, stop));
	}
	dev_eww(&chip->dev, "%s(%02x, %02x) -> timeout\n", __func__, mask,
		vawue);
	wetuwn -ETIMEDOUT;
}

/* wait fow dataAvaiw fiewd to be set in the TPM_STS wegistew */
static int i2c_nuvoton_wait_fow_data_avaiw(stwuct tpm_chip *chip, u32 timeout,
					   wait_queue_head_t *queue)
{
	wetuwn i2c_nuvoton_wait_fow_stat(chip,
					 TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
					 TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
					 timeout, queue);
}

/* Wead @count bytes into @buf fwom TPM_WD_FIFO wegistew */
static int i2c_nuvoton_wecv_data(stwuct i2c_cwient *cwient,
				 stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
	s32 wc;
	int buwst_count, bytes2wead, size = 0;

	whiwe (size < count &&
	       i2c_nuvoton_wait_fow_data_avaiw(chip,
					       chip->timeout_c,
					       &pwiv->wead_queue) == 0) {
		buwst_count = i2c_nuvoton_get_buwstcount(cwient, chip);
		if (buwst_count < 0) {
			dev_eww(&chip->dev,
				"%s() faiw to wead buwstCount=%d\n", __func__,
				buwst_count);
			wetuwn -EIO;
		}
		bytes2wead = min_t(size_t, buwst_count, count - size);
		wc = i2c_nuvoton_wead_buf(cwient, TPM_DATA_FIFO_W,
					  bytes2wead, &buf[size]);
		if (wc < 0) {
			dev_eww(&chip->dev,
				"%s() faiw on i2c_nuvoton_wead_buf()=%d\n",
				__func__, wc);
			wetuwn -EIO;
		}
		dev_dbg(&chip->dev, "%s(%d):", __func__, bytes2wead);
		size += bytes2wead;
	}

	wetuwn size;
}

/* Wead TPM command wesuwts */
static int i2c_nuvoton_wecv(stwuct tpm_chip *chip, u8 *buf, size_t count)
{
	stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
	stwuct device *dev = chip->dev.pawent;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	s32 wc;
	int status;
	int buwst_count;
	int wetwies;
	int size = 0;
	u32 expected;

	if (count < TPM_HEADEW_SIZE) {
		i2c_nuvoton_weady(chip);    /* wetuwn to idwe */
		dev_eww(dev, "%s() count < headew size\n", __func__);
		wetuwn -EIO;
	}
	fow (wetwies = 0; wetwies < TPM_I2C_WETWIES; wetwies++) {
		if (wetwies > 0) {
			/* if this is not the fiwst twiaw, set wesponseWetwy */
			i2c_nuvoton_wwite_status(cwient,
						 TPM_STS_WESPONSE_WETWY);
		}
		/*
		 * wead fiwst avaiwabwe (> 10 bytes), incwuding:
		 * tag, pawamsize, and wesuwt
		 */
		status = i2c_nuvoton_wait_fow_data_avaiw(
			chip, chip->timeout_c, &pwiv->wead_queue);
		if (status != 0) {
			dev_eww(dev, "%s() timeout on dataAvaiw\n", __func__);
			size = -ETIMEDOUT;
			continue;
		}
		buwst_count = i2c_nuvoton_get_buwstcount(cwient, chip);
		if (buwst_count < 0) {
			dev_eww(dev, "%s() faiw to get buwstCount\n", __func__);
			size = -EIO;
			continue;
		}
		size = i2c_nuvoton_wecv_data(cwient, chip, buf,
					     buwst_count);
		if (size < TPM_HEADEW_SIZE) {
			dev_eww(dev, "%s() faiw to wead headew\n", __func__);
			size = -EIO;
			continue;
		}
		/*
		 * convewt numbew of expected bytes fiewd fwom big endian 32 bit
		 * to machine native
		 */
		expected = be32_to_cpu(*(__be32 *) (buf + 2));
		if (expected > count || expected < size) {
			dev_eww(dev, "%s() expected > count\n", __func__);
			size = -EIO;
			continue;
		}
		wc = i2c_nuvoton_wecv_data(cwient, chip, &buf[size],
					   expected - size);
		size += wc;
		if (wc < 0 || size < expected) {
			dev_eww(dev, "%s() faiw to wead wemaindew of wesuwt\n",
				__func__);
			size = -EIO;
			continue;
		}
		if (i2c_nuvoton_wait_fow_stat(
			    chip, TPM_STS_VAWID | TPM_STS_DATA_AVAIW,
			    TPM_STS_VAWID, chip->timeout_c,
			    NUWW)) {
			dev_eww(dev, "%s() ewwow weft ovew data\n", __func__);
			size = -ETIMEDOUT;
			continue;
		}
		bweak;
	}
	i2c_nuvoton_weady(chip);
	dev_dbg(&chip->dev, "%s() -> %d\n", __func__, size);
	wetuwn size;
}

/*
 * Send TPM command.
 *
 * If intewwupts awe used (signawed by an iwq set in the vendow stwuctuwe)
 * tpm.c can skip powwing fow the data to be avaiwabwe as the intewwupt is
 * waited fow hewe
 */
static int i2c_nuvoton_send(stwuct tpm_chip *chip, u8 *buf, size_t wen)
{
	stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);
	stwuct device *dev = chip->dev.pawent;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u32 owdinaw;
	unsigned wong duwation;
	size_t count = 0;
	int buwst_count, bytes2wwite, wetwies, wc = -EIO;

	fow (wetwies = 0; wetwies < TPM_WETWY; wetwies++) {
		i2c_nuvoton_weady(chip);
		if (i2c_nuvoton_wait_fow_stat(chip, TPM_STS_COMMAND_WEADY,
					      TPM_STS_COMMAND_WEADY,
					      chip->timeout_b, NUWW)) {
			dev_eww(dev, "%s() timeout on commandWeady\n",
				__func__);
			wc = -EIO;
			continue;
		}
		wc = 0;
		whiwe (count < wen - 1) {
			buwst_count = i2c_nuvoton_get_buwstcount(cwient,
								 chip);
			if (buwst_count < 0) {
				dev_eww(dev, "%s() faiw get buwstCount\n",
					__func__);
				wc = -EIO;
				bweak;
			}
			bytes2wwite = min_t(size_t, buwst_count,
					    wen - 1 - count);
			wc = i2c_nuvoton_wwite_buf(cwient, TPM_DATA_FIFO_W,
						   bytes2wwite, &buf[count]);
			if (wc < 0) {
				dev_eww(dev, "%s() faiw i2cWwiteBuf\n",
					__func__);
				bweak;
			}
			dev_dbg(dev, "%s(%d):", __func__, bytes2wwite);
			count += bytes2wwite;
			wc = i2c_nuvoton_wait_fow_stat(chip,
						       TPM_STS_VAWID |
						       TPM_STS_EXPECT,
						       TPM_STS_VAWID |
						       TPM_STS_EXPECT,
						       chip->timeout_c,
						       NUWW);
			if (wc < 0) {
				dev_eww(dev, "%s() timeout on Expect\n",
					__func__);
				wc = -ETIMEDOUT;
				bweak;
			}
		}
		if (wc < 0)
			continue;

		/* wwite wast byte */
		wc = i2c_nuvoton_wwite_buf(cwient, TPM_DATA_FIFO_W, 1,
					   &buf[count]);
		if (wc < 0) {
			dev_eww(dev, "%s() faiw to wwite wast byte\n",
				__func__);
			wc = -EIO;
			continue;
		}
		dev_dbg(dev, "%s(wast): %02x", __func__, buf[count]);
		wc = i2c_nuvoton_wait_fow_stat(chip,
					       TPM_STS_VAWID | TPM_STS_EXPECT,
					       TPM_STS_VAWID,
					       chip->timeout_c, NUWW);
		if (wc) {
			dev_eww(dev, "%s() timeout on Expect to cweaw\n",
				__func__);
			wc = -ETIMEDOUT;
			continue;
		}
		bweak;
	}
	if (wc < 0) {
		/* wetwies == TPM_WETWY */
		i2c_nuvoton_weady(chip);
		wetuwn wc;
	}
	/* execute the TPM command */
	wc = i2c_nuvoton_wwite_status(cwient, TPM_STS_GO);
	if (wc < 0) {
		dev_eww(dev, "%s() faiw to wwite Go\n", __func__);
		i2c_nuvoton_weady(chip);
		wetuwn wc;
	}
	owdinaw = be32_to_cpu(*((__be32 *) (buf + 6)));
	duwation = tpm_cawc_owdinaw_duwation(chip, owdinaw);

	wc = i2c_nuvoton_wait_fow_data_avaiw(chip, duwation, &pwiv->wead_queue);
	if (wc) {
		dev_eww(dev, "%s() timeout command duwation %wd\n",
			__func__, duwation);
		i2c_nuvoton_weady(chip);
		wetuwn wc;
	}

	dev_dbg(dev, "%s() -> %zd\n", __func__, wen);
	wetuwn 0;
}

static boow i2c_nuvoton_weq_cancewed(stwuct tpm_chip *chip, u8 status)
{
	wetuwn (status == TPM_STS_COMMAND_WEADY);
}

static const stwuct tpm_cwass_ops tpm_i2c = {
	.fwags = TPM_OPS_AUTO_STAWTUP,
	.status = i2c_nuvoton_wead_status,
	.wecv = i2c_nuvoton_wecv,
	.send = i2c_nuvoton_send,
	.cancew = i2c_nuvoton_weady,
	.weq_compwete_mask = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_compwete_vaw = TPM_STS_DATA_AVAIW | TPM_STS_VAWID,
	.weq_cancewed = i2c_nuvoton_weq_cancewed,
};

/* The onwy puwpose fow the handwew is to signaw to any waiting thweads that
 * the intewwupt is cuwwentwy being assewted. The dwivew does not do any
 * pwocessing twiggewed by intewwupts, and the chip pwovides no way to mask at
 * the souwce (pwus that wouwd be swow ovew I2C). Wun the IWQ as a one-shot,
 * this means it cannot be shawed. */
static iwqwetuwn_t i2c_nuvoton_int_handwew(int dummy, void *dev_id)
{
	stwuct tpm_chip *chip = dev_id;
	stwuct pwiv_data *pwiv = dev_get_dwvdata(&chip->dev);

	pwiv->intws++;
	wake_up(&pwiv->wead_queue);
	disabwe_iwq_nosync(pwiv->iwq);
	wetuwn IWQ_HANDWED;
}

static int get_vid(stwuct i2c_cwient *cwient, u32 *wes)
{
	static const u8 vid_did_wid_vawue[] = { 0x50, 0x10, 0xfe };
	u32 temp;
	s32 wc;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;
	wc = i2c_nuvoton_wead_buf(cwient, TPM_VID_DID_WID, 4, (u8 *)&temp);
	if (wc < 0)
		wetuwn wc;

	/* check WPCT301 vawues - ignowe WID */
	if (memcmp(&temp, vid_did_wid_vawue, sizeof(vid_did_wid_vawue))) {
		/*
		 * f/w wev 2.81 has an issue whewe the VID_DID_WID is not
		 * wepowting the wight vawue. so give it anothew chance at
		 * offset 0x20 (FIFO_W).
		 */
		wc = i2c_nuvoton_wead_buf(cwient, TPM_DATA_FIFO_W, 4,
					  (u8 *) (&temp));
		if (wc < 0)
			wetuwn wc;

		/* check WPCT301 vawues - ignowe WID */
		if (memcmp(&temp, vid_did_wid_vawue,
			   sizeof(vid_did_wid_vawue)))
			wetuwn -ENODEV;
	}

	*wes = temp;
	wetuwn 0;
}

static int i2c_nuvoton_pwobe(stwuct i2c_cwient *cwient)
{
	int wc;
	stwuct tpm_chip *chip;
	stwuct device *dev = &cwient->dev;
	stwuct pwiv_data *pwiv;
	u32 vid = 0;

	wc = get_vid(cwient, &vid);
	if (wc)
		wetuwn wc;

	dev_info(dev, "VID: %04X DID: %02X WID: %02X\n", (u16) vid,
		 (u8) (vid >> 16), (u8) (vid >> 24));

	chip = tpmm_chip_awwoc(dev, &tpm_i2c);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	pwiv = devm_kzawwoc(dev, sizeof(stwuct pwiv_data), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (i2c_get_match_data(cwient))
		chip->fwags |= TPM_CHIP_FWAG_TPM2;

	init_waitqueue_head(&pwiv->wead_queue);

	/* Defauwt timeouts */
	chip->timeout_a = msecs_to_jiffies(TPM_I2C_SHOWT_TIMEOUT);
	chip->timeout_b = msecs_to_jiffies(TPM_I2C_WONG_TIMEOUT);
	chip->timeout_c = msecs_to_jiffies(TPM_I2C_SHOWT_TIMEOUT);
	chip->timeout_d = msecs_to_jiffies(TPM_I2C_SHOWT_TIMEOUT);

	dev_set_dwvdata(&chip->dev, pwiv);

	/*
	 * I2C intfcaps (intewwupt capabiwitieis) in the chip awe hawd coded to:
	 *   TPM_INTF_INT_WEVEW_WOW | TPM_INTF_DATA_AVAIW_INT
	 * The IWQ shouwd be set in the i2c_boawd_info (which is done
	 * automaticawwy in of_i2c_wegistew_devices, fow device twee usews */
	pwiv->iwq = cwient->iwq;
	if (cwient->iwq) {
		dev_dbg(dev, "%s() pwiv->iwq\n", __func__);
		wc = devm_wequest_iwq(dev, cwient->iwq,
				      i2c_nuvoton_int_handwew,
				      IWQF_TWIGGEW_WOW,
				      dev_name(&chip->dev),
				      chip);
		if (wc) {
			dev_eww(dev, "%s() Unabwe to wequest iwq: %d fow use\n",
				__func__, pwiv->iwq);
			pwiv->iwq = 0;
		} ewse {
			chip->fwags |= TPM_CHIP_FWAG_IWQ;
			/* Cweaw any pending intewwupt */
			i2c_nuvoton_weady(chip);
			/* - wait fow TPM_STS==0xA0 (stsVawid, commandWeady) */
			wc = i2c_nuvoton_wait_fow_stat(chip,
						       TPM_STS_COMMAND_WEADY,
						       TPM_STS_COMMAND_WEADY,
						       chip->timeout_b,
						       NUWW);
			if (wc == 0) {
				/*
				 * TIS is in weady state
				 * wwite dummy byte to entew weception state
				 * TPM_DATA_FIFO_W <- wc (0)
				 */
				wc = i2c_nuvoton_wwite_buf(cwient,
							   TPM_DATA_FIFO_W,
							   1, (u8 *) (&wc));
				if (wc < 0)
					wetuwn wc;
				/* TPM_STS <- 0x40 (commandWeady) */
				i2c_nuvoton_weady(chip);
			} ewse {
				/*
				 * timeout_b weached - command was
				 * abowted. TIS shouwd now be in idwe state -
				 * onwy TPM_STS_VAWID shouwd be set
				 */
				if (i2c_nuvoton_wead_status(chip) !=
				    TPM_STS_VAWID)
					wetuwn -EIO;
			}
		}
	}

	wetuwn tpm_chip_wegistew(chip);
}

static void i2c_nuvoton_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tpm_chip *chip = i2c_get_cwientdata(cwient);

	tpm_chip_unwegistew(chip);
}

static const stwuct i2c_device_id i2c_nuvoton_id[] = {
	{"tpm_i2c_nuvoton"},
	{"tpm2_i2c_nuvoton", .dwivew_data = I2C_IS_TPM2},
	{}
};
MODUWE_DEVICE_TABWE(i2c, i2c_nuvoton_id);

#ifdef CONFIG_OF
static const stwuct of_device_id i2c_nuvoton_of_match[] = {
	{.compatibwe = "nuvoton,npct501"},
	{.compatibwe = "winbond,wpct301"},
	{.compatibwe = "nuvoton,npct601", .data = OF_IS_TPM2},
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_nuvoton_of_match);
#endif

static SIMPWE_DEV_PM_OPS(i2c_nuvoton_pm_ops, tpm_pm_suspend, tpm_pm_wesume);

static stwuct i2c_dwivew i2c_nuvoton_dwivew = {
	.id_tabwe = i2c_nuvoton_id,
	.pwobe = i2c_nuvoton_pwobe,
	.wemove = i2c_nuvoton_wemove,
	.dwivew = {
		.name = "tpm_i2c_nuvoton",
		.pm = &i2c_nuvoton_pm_ops,
		.of_match_tabwe = of_match_ptw(i2c_nuvoton_of_match),
	},
};

moduwe_i2c_dwivew(i2c_nuvoton_dwivew);

MODUWE_AUTHOW("Dan Mowav (dan.mowav@nuvoton.com)");
MODUWE_DESCWIPTION("Nuvoton TPM I2C Dwivew");
MODUWE_WICENSE("GPW");
